/*
 * Copyright (C) 2008-2018 TrinityCore <https://www.trinitycore.org/>
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "Transport.h"
#include "Cell.h"
#include "CellImpl.h"
#include "Common.h"
#include "GameEventSender.h"
#include "GameObjectAI.h"
#include "GameObjectModel.h"
#include "Log.h"
#include "MapManager.h"
#include "ObjectMgr.h"
#include "PhasingHandler.h"
#include "Player.h"
#include "ScriptMgr.h"
#include "Spline.h"
#include "Totem.h"
#include "UpdateData.h"
#include "Vehicle.h"
#include "ZoneScript.h"
#include <G3D/Vector3.h>
#include "MMapFactory.h"
#include "GameObjectData.h"
#include "GameTime.h"
#include <G3D/Quat.h>
#include "G3DPosition.hpp"

void TransportBase::UpdatePassengerPosition(Map* map, WorldObject* passenger, float x, float y, float z, float o, bool setHomePosition)
{
    // transport teleported but passenger not yet (can happen for players)
    if (passenger->GetMap() != map)
        return;

    // if passenger is on vehicle we have to assume the vehicle is also on transport
    // and its the vehicle that will be updating its passengers
    if (Unit* unit = passenger->ToUnit())
        if (unit->GetVehicle())
            return;

    // Do not use Unit::UpdatePosition here, we don't want to remove auras
    // as if regular movement occurred
    switch (passenger->GetTypeId())
    {
        case TYPEID_UNIT:
        {
            Creature* creature = passenger->ToCreature();
            map->CreatureRelocation(creature, x, y, z, o, false);
            if (setHomePosition)
            {
                creature->GetTransportHomePosition(x, y, z, o);
                CalculatePassengerPosition(x, y, z, &o);
                creature->SetHomePosition(x, y, z, o);
            }
            break;
        }
        case TYPEID_PLAYER:
            //relocate only passengers in world and skip any player that might be still logging in/teleporting
            if (passenger->IsInWorld() && !passenger->ToPlayer()->IsBeingTeleported())
            {
                map->PlayerRelocation(passenger->ToPlayer(), x, y, z, o);
                passenger->ToPlayer()->SetFallInformation(0, passenger->GetPositionZ());
            }
            break;
        case TYPEID_GAMEOBJECT:
            map->GameObjectRelocation(passenger->ToGameObject(), x, y, z, o, false);
            passenger->ToGameObject()->RelocateStationaryPosition(x, y, z, o);
            break;
        case TYPEID_DYNAMICOBJECT:
            map->DynamicObjectRelocation(passenger->ToDynObject(), x, y, z, o);
            break;
        case TYPEID_AREATRIGGER:
            map->AreaTriggerRelocation(passenger->ToAreaTrigger(), x, y, z, o);
            break;
        default:
            break;
    }

    if (Unit* unit = passenger->ToUnit())
        if (Vehicle* vehicle = unit->GetVehicleKit())
            vehicle->RelocatePassengers();
}

Transport::Transport() : GameObject(),
_passengerTeleportItr(_passengers.begin()), _currentTransportTime(0), _destinationStopFrameTime(0), _pathProgress(0),
_alignmentTransportTime(0), _lastStopFrameTime(0), _isDynamicTransport(false), _initialRelocate(false),
_isLoop(false), _loopTimer(0), _moveDirection(TRANSPORT_MOVE_DIRECTION_STOPPED)
{
    m_updateFlag.ServerTime = true;
    m_updateFlag.Stationary = true;
    m_updateFlag.Rotation = true;
}

Transport::~Transport()
{
    UnloadStaticPassengers();
}

void Transport::CleanupsBeforeDelete(bool finalCleanup /*= true*/)
{
    while (!_passengers.empty())
    {
        WorldObject* obj = *_passengers.begin();
        RemovePassenger(obj);
    }

    // unload mmaps
    UnLoadMMaps();

    GameObject::CleanupsBeforeDelete(finalCleanup);
}

void Transport::AddPassenger(WorldObject* passenger)
{
    if (!IsInWorld())
        return;

    if (_passengers.insert(passenger).second)
    {
        TC_LOG_DEBUG("entities.transport", "Object %s added to transport %s.", passenger->GetName().c_str(), GetName().c_str());
        passenger->SetTransport(this);
        passenger->m_movementInfo.transport.guid = GetGUID();
        passenger->m_movementInfo.transport.time = GetPathProgress();

        if (Unit* unit = passenger->ToUnit())
        {
            if (!_mmapsLoaded)
                unit->AddUnitState(UNIT_STATE_IGNORE_PATHFINDING);
            if (Guardian* guardian = unit->GetGuardianPet())
            {
                if (!guardian->IsPet() || guardian->GetCharmInfo()->GetCommandState() == COMMAND_FOLLOW)
                {
                    if (Transport* oldTransport = dynamic_cast<Transport*>(guardian->GetTransport()))
                        oldTransport->RemovePassenger(guardian);

                    AddPassenger(guardian);
                }
            }
        }

        if (Player* plr = passenger->ToPlayer())
        {
            sScriptMgr->OnAddPassenger(this, plr);

            if (GetGoType() == GAMEOBJECT_TYPE_TRANSPORT)
                plr->SetTransportSpawnID(GetSpawnId());
        }
    }
}

Transport* Transport::RemovePassenger(WorldObject* passenger)
{
    bool erased = false;
    if (_passengerTeleportItr != _passengers.end())
    {
        PassengerSet::iterator itr = _passengers.find(passenger);
        if (itr != _passengers.end())
        {
            if (itr == _passengerTeleportItr)
                ++_passengerTeleportItr;

            _passengers.erase(itr);
            erased = true;
        }
    }
    else
        erased = _passengers.erase(passenger) > 0;

    if (erased || _staticPassengers.erase(passenger)) // static passenger can remove itself in case of grid unload
    {

        passenger->SetTransport(nullptr);
        passenger->m_movementInfo.transport.Reset();
        TC_LOG_DEBUG("entities.transport", "Object %s removed from MAPtransport %s.", passenger->GetName().c_str(), GetName().c_str());
        if (Unit* unit = passenger->ToUnit())
        {
            unit->ClearUnitState(UNIT_STATE_IGNORE_PATHFINDING);
            if (Guardian* guardian = unit->GetGuardianPet())
                if (!guardian->IsPet() || guardian->GetCharmInfo()->GetCommandState() == COMMAND_FOLLOW)
                {
                    if (guardian->GetTransGUID() == GetGUID())
                    {
                        RemovePassenger(guardian);
                    }
                }
        }

        if (Player* plr = passenger->ToPlayer())
        {
            sScriptMgr->OnRemovePassenger(this, plr);
            plr->SetTransportSpawnID(0);
            plr->SetFallInformation(0, plr->GetPositionZ());
        }
    }

    return this;
}

static constexpr Milliseconds PositionUpdateInterval = 50ms;

bool Transport::Create(uint32 entry, Map* map, Position const& pos, QuaternionData const& rotation, uint32 animProgress, GOState goState, uint32 artKit, bool dynamic, ObjectGuid::LowType spawnid)
{
    if (!Transport::CreateTransport(map->GenerateLowGuid<HighGuid::Transport>(), entry, map->GetId(), pos, animProgress))
        return false;

    SetZoneScript();
    if (GetZoneScript())
    {
        entry = GetZoneScript()->GetGameObjectEntry(m_spawnId, entry);
        if (!entry)
            return false;
    }

    if (m_goInfo->type != GAMEOBJECT_TYPE_TRANSPORT)
    {
        TC_LOG_ERROR("entities.transport", "Transport (Spawn id: %u Entry: %u) not created.", GetSpawnId(), entry);
        return false;
    }

    m_stationaryPosition.Relocate(pos);

    GameObjectAddon const* gameObjectAddon = sObjectMgr->GetGameObjectAddon(GetSpawnId());

    SetLocalRotation(0.0f, 0.0f, 0.0f, 1.0f);
    SetParentRotation(QuaternionData());

    // For most of gameobjects is (0, 0, 0, 1) quaternion, there are only some transports with not standard rotation
    QuaternionData parentRotation;
    if (gameObjectAddon)
        parentRotation = gameObjectAddon->ParentRotation;

    SetParentRotation(parentRotation);

    _animationInfo = sTransportMgr->GetTransportAnimInfo(entry);
    _stateChangeTime = GameTime::GetGameTimeMS();
    _pathProgress = GameTime::GetGameTimeMS() % GetTransportPeriod();
    _stateChangeTime = GameTime::GetGameTimeMS();
    _stateChangeProgress = _pathProgress;
    SetDestinationStopFrameTime(0); // EndTime
    SetCurrentTransportTime(0); // CurrentTimeIndex

    GameObjectTemplate const* goInfo = GetGOInfo();
    if (goInfo->transport.Timeto2ndfloor > 0)
    {
        _stopFrames.push_back(goInfo->transport.Timeto2ndfloor);
        if (goInfo->transport.Timeto3rdfloor > 0)
        {
            _stopFrames.push_back(goInfo->transport.Timeto3rdfloor);
            if (goInfo->transport.Timeto4thfloor > 0)
            {
                _stopFrames.push_back(goInfo->transport.Timeto4thfloor);
                if (goInfo->transport.Timeto5thfloor > 0)
                {
                    _stopFrames.push_back(goInfo->transport.Timeto5thfloor);
                    if (goInfo->transport.Timeto6thfloor > 0)
                    {
                        _stopFrames.push_back(goInfo->transport.Timeto6thfloor);
                        if (goInfo->transport.Timeto7thfloor > 0)
                        {
                            _stopFrames.push_back(goInfo->transport.Timeto7thfloor);
                            if (goInfo->transport.Timeto8thfloor > 0)
                            {
                                _stopFrames.push_back(goInfo->transport.Timeto8thfloor);
                                if (goInfo->transport.Timeto9thfloor > 0)
                                {
                                    _stopFrames.push_back(goInfo->transport.Timeto9thfloor);
                                    if (goInfo->transport.Timeto10thfloor > 0)
                                        _stopFrames.push_back(goInfo->transport.Timeto10thfloor);
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    _positionUpdateTimer.Reset(PositionUpdateInterval);

    _isDynamicTransport = _stopFrames.empty();

    if (!IsDynamicTransport())
        SetTransportState(GOState(GO_STATE_TRANSPORT_FLOOR_1 + m_goInfo->transport.startOpen), true); // startOpen is actually starting floor-1

    if (gameObjectAddon && gameObjectAddon->InvisibilityValue)
    {
        m_invisibility.AddFlag(gameObjectAddon->invisibilityType);
        m_invisibility.AddValue(gameObjectAddon->invisibilityType, gameObjectAddon->InvisibilityValue);
    }

    LoadStaticPassengers();

    LastUsedScriptID = GetGOInfo()->ScriptId;
    AIM_Initialize();

    if (goInfo->transport.startOpen)
        SetGoState(GO_STATE_TRANSPORT_STOPPED);
    else
        SetGoState(GO_STATE_TRANSPORT_ACTIVE);

    SetGoAnimProgress(animProgress);
    setActive(true);

    return true;
}

bool Transport::CreateTransport(ObjectGuid::LowType guidlow, uint32 entry, uint32 mapid, Position const& pos, uint32 animprogress)
{
    Relocate(pos);

    if (!IsPositionValid())
    {
        TC_LOG_ERROR("entities.transport", "Transport (Entry: %u) not created. Suggested coordinates isn't valid %s",
            entry, pos.ToString().c_str());
        return false;
    }

    GameObjectTemplate const* goinfo = sObjectMgr->GetGameObjectTemplate(entry);
    if (!goinfo)
    {
        TC_LOG_ERROR("sql.sql", "Transport not created: entry in `gameobject_template` not found, entry: %u map: %u (Position: %s) ang: %f", entry, mapid, pos.ToString().c_str());
        return false;
    }

    m_goInfo = goinfo;

    Object::_Create(ObjectGuid::Create<HighGuid::Transport>(guidlow));

    m_goTemplateAddon = sObjectMgr->GetGameObjectTemplateAddon(entry);

    if (m_goTemplateAddon)
    {
        SetFaction(m_goTemplateAddon->Faction);
        ReplaceAllFlags(GameObjectFlags(m_goTemplateAddon->Flags));
    }

    _pathProgress = 0;
    SetObjectScale(goinfo->size);
    SetEntry(goinfo->entry);
    SetDisplayId(goinfo->displayId);
    SetGoType(GameobjectTypes(goinfo->type));
    SetGoAnimProgress(animprogress);
    SetName(goinfo->name);

    CreateModel();
    if (m_model && m_model->isMapObject())
        SetFlag(GO_FLAG_MAP_OBJECT);

    SetFlag(GO_FLAG_TRANSPORT | GO_FLAG_NODESPAWN);

    // load mmaps for transport
    LoadMMaps();

    return true;
}

int32 Transport::GetMapIdForSpawning() const
{
    return GetGOInfo()->transport.SpawnMap;
}

void Transport::Update(uint32 diff)
{
    GameObject::Update(diff);

    if (!IsInWorld())
        return;


    if (!_animationInfo)
        return;

    _positionUpdateTimer.Update(diff);
    if (!_positionUpdateTimer.Passed())
        return;

    _positionUpdateTimer.Reset(PositionUpdateInterval);

    uint32 now = GameTime::GetGameTimeMS();
    uint32 period = GetTransportPeriod();
    uint32 newProgress = 0;
    if (_stopFrames.empty())
        newProgress = now % period;
    else
    {
        int32 stopTargetTime = 0;
        if (GetGoState() == GO_STATE_TRANSPORT_ACTIVE)
            stopTargetTime = 0;
        else
            stopTargetTime = _stopFrames[GetGoState() - GO_STATE_TRANSPORT_STOPPED];

        if (now < uint32(*m_gameObjectData->Level))
        {
            int32 timeToStop = m_gameObjectData->Level - _stateChangeTime;
            float stopSourcePathPct = float(_stateChangeProgress) / float(period);
            float stopTargetPathPct = float(stopTargetTime) / float(period);
            float timeSinceStopProgressPct = float(now - _stateChangeTime) / float(timeToStop);

            float progressPct;
            if (!HasDynamicFlag(GO_DYNFLAG_LO_INVERTED_MOVEMENT))
            {
                if (GetGoState() == GO_STATE_TRANSPORT_ACTIVE)
                    stopTargetPathPct = 1.0f;

                float pathPctBetweenStops = stopTargetPathPct - stopSourcePathPct;
                if (pathPctBetweenStops < 0.0f)
                    pathPctBetweenStops += 1.0f;

                progressPct = pathPctBetweenStops * timeSinceStopProgressPct + stopSourcePathPct;
                if (progressPct > 1.0f)
                    progressPct = progressPct - 1.0f;
            }
            else
            {
                float pathPctBetweenStops = stopSourcePathPct - stopTargetPathPct;
                if (pathPctBetweenStops < 0.0f)
                    pathPctBetweenStops += 1.0f;

                progressPct = stopSourcePathPct - pathPctBetweenStops * timeSinceStopProgressPct;
                if (progressPct < 0.0f)
                    progressPct += 1.0f;
            }

            newProgress = uint32(float(period) * progressPct) % period;
        }
        else
            newProgress = stopTargetTime;

        if (int32(newProgress) == stopTargetTime && newProgress != _pathProgress)
        {
            uint32 eventId = [&]()
            {
                switch (GetGoState() - GO_STATE_TRANSPORT_ACTIVE)
                {
                    case 0:
                        return GetGOInfo()->transport.Reached1stfloor;
                    case 1:
                        return GetGOInfo()->transport.Reached2ndfloor;
                    case 2:
                        return GetGOInfo()->transport.Reached3rdfloor;
                    case 3:
                        return GetGOInfo()->transport.Reached4thfloor;
                    case 4:
                        return GetGOInfo()->transport.Reached5thfloor;
                    case 5:
                        return GetGOInfo()->transport.Reached6thfloor;
                    case 6:
                        return GetGOInfo()->transport.Reached7thfloor;
                    case 7:
                        return GetGOInfo()->transport.Reached8thfloor;
                    case 8:
                        return GetGOInfo()->transport.Reached9thfloor;
                    case 9:
                        return GetGOInfo()->transport.Reached10thfloor;
                    default:
                        return 0u;
                }
            }();
            if (eventId)
                GameEvents::Trigger(eventId, this, nullptr);

            if (_autoCycleBetweenStopFrames)
            {
                GOState currentState = GetGoState();
                GOState newState;
                if (currentState == GO_STATE_TRANSPORT_ACTIVE)
                    newState = GO_STATE_TRANSPORT_STOPPED;
                else if (currentState - GO_STATE_TRANSPORT_ACTIVE == int32(_stopFrames.size()))
                    newState = GOState(currentState - 1);
                else if (HasDynamicFlag(GO_DYNFLAG_LO_INVERTED_MOVEMENT))
                    newState = GOState(currentState - 1);
                else
                    newState = GOState(currentState + 1);

                SetGoState(newState);
            }
        }
    }

    if (_pathProgress == newProgress)
        return;

    _pathProgress = newProgress;

    TransportAnimationEntry const* oldAnimation = _animationInfo->GetPrevAnimNode(newProgress);
    TransportAnimationEntry const* newAnimation = _animationInfo->GetNextAnimNode(newProgress);
    if (oldAnimation && newAnimation)
    {
        G3D::Matrix3 pathRotation = G3D::Quat(m_gameObjectData->ParentRotation->x, m_gameObjectData->ParentRotation->y,
            m_gameObjectData->ParentRotation->z, m_gameObjectData->ParentRotation->w).toRotationMatrix();

        G3D::Vector3 prev(oldAnimation->Pos.X, oldAnimation->Pos.Y, oldAnimation->Pos.Z);
        G3D::Vector3 next(newAnimation->Pos.X, newAnimation->Pos.Y, newAnimation->Pos.Z);

        float animProgress = float(newProgress - oldAnimation->TimeIndex) / float(newAnimation->TimeIndex - oldAnimation->TimeIndex);

        G3D::Vector3 dst = prev.lerp(next, animProgress) * pathRotation;

        dst += PositionToVector3(&GetStationaryPosition());

        GetMap()->GameObjectRelocation(this, dst.x, dst.y, dst.z, GetOrientation());
    }

    TransportRotationEntry const* oldRotation = _animationInfo->GetPrevAnimRotation(newProgress);
    TransportRotationEntry const* newRotation = _animationInfo->GetNextAnimRotation(newProgress);
    if (oldRotation && newRotation)
    {
        G3D::Quat prev(oldRotation->Rot[0], oldRotation->Rot[1], oldRotation->Rot[2], oldRotation->Rot[3]);
        G3D::Quat next(newRotation->Rot[0], newRotation->Rot[1], newRotation->Rot[2], newRotation->Rot[3]);

        float animProgress = float(newProgress - oldRotation->TimeIndex) / float(newRotation->TimeIndex - oldRotation->TimeIndex);

        G3D::Quat rotation = prev.slerp(next, animProgress);

        SetLocalRotation(rotation.x, rotation.y, rotation.z, rotation.w);
        UpdateModelPosition();
    }

    // update progress marker for client
    SetPathProgressForClient(float(_pathProgress) / float(period));
}

uint32 Transport::GetTransportPeriod() const
{
    if (_animationInfo)
        return _animationInfo->TotalTime;

    return 1;
}

void Transport::UpdatePassengerPositions(PassengerSet const& passengers)
{
    if (!IsInWorld() || !FindMap())
        return;

    for (WorldObject* passenger : passengers)
    {
        float x, y, z, o;
        passenger->m_movementInfo.transport.pos.GetPosition(x, y, z, o);
        CalculatePassengerPosition(x, y, z, &o);
        UpdatePassengerPosition(GetMap(), passenger, x, y, z, o, true);
    }
}

void Transport::SetTransportState(GOState newState, bool instant /*= false*/)
{
    auto oldState = GetGoState();
    ASSERT(newState >= GO_STATE_TRANSPORT_ACTIVE);

    // transports without stop frames just keep animating in state 24
    if (_stopFrames.empty())
    {
        if (newState != GO_STATE_TRANSPORT_ACTIVE)
            SetGoState(GO_STATE_TRANSPORT_ACTIVE);
        return;
    }

    int32 stopPathProgress = 0;

    if (newState != GO_STATE_TRANSPORT_ACTIVE)
    {
        ASSERT(newState < GOState(GO_STATE_TRANSPORT_STOPPED + MAX_GO_STATE_TRANSPORT_STOP_FRAMES));
        uint32 stopFrame = newState - GO_STATE_TRANSPORT_STOPPED;
        ASSERT(stopFrame < _stopFrames.size());
        stopPathProgress = _stopFrames[stopFrame];
    }

    _stateChangeTime = GameTime::GetGameTimeMS();
    _stateChangeProgress = _pathProgress;
    uint32 timeToStop = std::abs(int32(_pathProgress) - stopPathProgress);
    SetLevel(GameTime::GetGameTimeMS() + timeToStop);
    SetPathProgressForClient(float(_pathProgress) / float(GetTransportPeriod()));

    if (oldState == GO_STATE_ACTIVE || oldState == newState)
    {
        // initialization
        if (int32(_pathProgress) > stopPathProgress)
            SetDynamicFlag(GO_DYNFLAG_LO_INVERTED_MOVEMENT);
        else
            RemoveDynamicFlag(GO_DYNFLAG_LO_INVERTED_MOVEMENT);

        return;
    }

    int32 pauseTimesCount = _stopFrames.size();
    int32 newToOldStateDelta = newState - oldState;
    if (newToOldStateDelta < 0)
        newToOldStateDelta += pauseTimesCount + 1;

    int32 oldToNewStateDelta = oldState - newState;
    if (oldToNewStateDelta < 0)
        oldToNewStateDelta += pauseTimesCount + 1;

    if (oldToNewStateDelta < newToOldStateDelta)
        SetDynamicFlag(GO_DYNFLAG_LO_INVERTED_MOVEMENT);
    else
        RemoveDynamicFlag(GO_DYNFLAG_LO_INVERTED_MOVEMENT);
}

void Transport::SetTransportLoop(bool on)
{
    if (IsDynamicTransport())
    {
        TC_LOG_ERROR("entities.transport", "Transport %s has no stop frames, SetTransportLoop() can not be used", GetGUID().ToString().c_str());
        return;
    }

    SetLoop(on);
    if (!on)
        return; // movement will stop after reaching current destination floor (if moving), no need to do anything here

    if (GetMoveDirection() == TRANSPORT_MOVE_DIRECTION_STOPPED)
    {
        uint32 state = GetGoState();
        if (state - GO_STATE_TRANSPORT_FLOOR_1 >= _stopFrames.size()) // at last floor, go to 1st floor
        {
            SetTransportState(GO_STATE_TRANSPORT_FLOOR_1);
        }
        else // go to next
        {
            SetTransportState(GOState(state + 1));
        }
    }
}

MapTransport::MapTransport() : Transport(),
_transportInfo(nullptr), _isMoving(true), _pendingStop(false),
_triggeredArrivalEvent(false), _triggeredDepartureEvent(false),
_delayedAddModel(false), _delayedTeleport(false)
{
}

MapTransport::~MapTransport()
{
    UnloadStaticPassengers();
}

bool MapTransport::CreateMapTransport(ObjectGuid::LowType guidlow, uint32 entry, uint32 mapid, float x, float y, float z, float ang, uint32 animprogress)
{
    if (!Transport::CreateTransport(guidlow, entry, mapid, Position(x, y, z, ang), animprogress))
        return false;

    TransportTemplate const* tInfo = sTransportMgr->GetTransportTemplate(entry);
    if (!tInfo)
    {
        TC_LOG_ERROR("sql.sql", "Transport %u (name: %s) will not be created, missing `transport_template` entry.", entry, m_goInfo->name.c_str());
        return false;
    }

    _transportInfo = tInfo;

    // initialize waypoints
    _nextFrame = tInfo->keyFrames.begin();
    _currentFrame = _nextFrame++;
    _triggeredArrivalEvent = false;
    _triggeredDepartureEvent = false;

    SetPathProgress(0);
    SetPeriod(tInfo->pathTime);
    SetGoState(!m_goInfo->moTransport.allowstopping ? GO_STATE_READY : GO_STATE_ACTIVE);
    //SetWorldRotation(0.0f, 0.0f, 0.0f, 1.0f);
    SetParentRotation(QuaternionData());

    CreateModel();
    return true;
}

void MapTransport::CleanupsBeforeDelete(bool finalCleanup /*= true*/)
{
    UnloadStaticPassengers();
    Transport::CleanupsBeforeDelete(finalCleanup);
}

void MapTransport::Update(uint32 diff)
{
    uint32 const positionUpdateDelay = 200;

    if (AI())
        AI()->UpdateAI(diff);
    else if (!AIM_Initialize())
        TC_LOG_ERROR("entities.transport", "Could not initialize GameObjectAI for Transport");

    if (GetKeyFrames().size() <= 1)
        return;

    if (IsMoving() || !_pendingStop)
        _pathProgress += diff;

    uint32 timer = _pathProgress % GetTransportPeriod();
    bool justStopped = false;

    // Set current waypoint
    // Desired outcome: _currentFrame->DepartureTime < timer < _nextFrame->ArriveTime
    // ... arrive | ... delay ... | departure
    //      event /         event /
    for (;;)
    {
        if (timer >= _currentFrame->ArriveTime)
        {
            if (!_triggeredArrivalEvent)
            {
                DoEventIfAny(*_currentFrame, false);
                _triggeredArrivalEvent = true;
            }

            if (timer < _currentFrame->DepartureTime)
            {
                SetMoving(false);
                justStopped = true;
                if (_pendingStop && GetGoState() != GO_STATE_READY)
                {
                    SetGoState(GO_STATE_READY);
                    _pathProgress = (_pathProgress / GetTransportPeriod());
                    _pathProgress *= GetTransportPeriod();
                    _pathProgress += _currentFrame->ArriveTime;
                }
                break;  // its a stop frame and we are waiting
            }
        }

        if (timer >= _currentFrame->DepartureTime && !_triggeredDepartureEvent)
        {
            DoEventIfAny(*_currentFrame, true); // departure event
            _triggeredDepartureEvent = true;
        }

        // not waiting anymore
        SetMoving(true);

        // Enable movement
        if (GetGOInfo()->moTransport.allowstopping)
            SetGoState(GO_STATE_ACTIVE);

        if (timer >= _currentFrame->DepartureTime && timer < _currentFrame->NextArriveTime)
            break;  // found current waypoint

        MoveToNextWaypoint();

        sScriptMgr->OnRelocate(this, _currentFrame->Node->NodeIndex, _currentFrame->Node->ContinentID, _currentFrame->Node->Loc.X, _currentFrame->Node->Loc.Y, _currentFrame->Node->Loc.Z);

        TC_LOG_DEBUG("entities.transport", "Transport %u (%s) moved to node %u %u %f %f %f", GetEntry(), GetName().c_str(), _currentFrame->Node->NodeIndex, _currentFrame->Node->ContinentID, _currentFrame->Node->Loc.X, _currentFrame->Node->Loc.Y, _currentFrame->Node->Loc.Z);

        // Departure event
        if (_currentFrame->IsTeleportFrame())
            if (TeleportTransport(_nextFrame->Node->ContinentID, _nextFrame->Node->Loc.X, _nextFrame->Node->Loc.Y, _nextFrame->Node->Loc.Z, _nextFrame->InitialOrientation))
                return; // Update more in new map thread
    }

    // Add model to map after we are fully done with moving maps
    if (_delayedAddModel)
    {
        _delayedAddModel = false;
        if (m_model)
            GetMap()->InsertGameObjectModel(*m_model);
    }

    // Set position
    _positionChangeTimer.Update(diff);
    if (_positionChangeTimer.Passed())
    {
        _positionChangeTimer.Reset(positionUpdateDelay);
        if (IsMoving())
        {
            float t = !justStopped ? CalculateSegmentPos(float(timer) * 0.001f) : 1.0f;
            G3D::Vector3 pos, dir;
            _currentFrame->Spline->evaluate_percent(_currentFrame->Index, t, pos);
            _currentFrame->Spline->evaluate_derivative(_currentFrame->Index, t, dir);
            UpdatePosition(pos.x, pos.y, pos.z, std::atan2(dir.y, dir.x) + float(M_PI));
        }
        else if (justStopped)
            UpdatePosition(_currentFrame->Node->Loc.X, _currentFrame->Node->Loc.Y, _currentFrame->Node->Loc.Z, _currentFrame->InitialOrientation);
        else
        {
            /* There are four possible scenarios that trigger loading/unloading passengers:
              1. transport moves from inactive to active grid
              2. the grid that transport is currently in becomes active
              3. transport moves from active to inactive grid
              4. the grid that transport is currently in unloads
            */
            bool gridActive = GetMap()->IsGridLoaded(GetPositionX(), GetPositionY());

            if (_staticPassengers.empty() && gridActive) // 2.
                LoadStaticPassengers();
            else if (!_staticPassengers.empty() && !gridActive)
                // 4. - if transports stopped on grid edge, some passengers can remain in active grids
                //      unload all static passengers otherwise passengers won't load correctly when the grid that transport is currently in becomes active
                UnloadStaticPassengers();
        }
    }

    sScriptMgr->OnTransportUpdate(this, diff);
}

void MapTransport::DelayedUpdate(uint32 /*diff*/)
{
    if (GetKeyFrames().size() <= 1)
        return;

    DelayedTeleportTransport();
}

Creature* Transport::CreateNPCPassenger(ObjectGuid::LowType guid, CreatureData const* data)
{
    Map* map = GetMap();

    Creature* creature = Creature::CreateCreatureFromDB(guid, map, false);
    if (!creature)
        return nullptr;

    ASSERT(data);

    float x = data->spawnPoint.GetPositionX();
    float y = data->spawnPoint.GetPositionY();
    float z = data->spawnPoint.GetPositionZ();
    float o = data->spawnPoint.GetOrientation();

    creature->SetTransport(this);
    creature->m_movementInfo.transport.guid = GetGUID();
    creature->m_movementInfo.transport.time = GetPathProgress();
    creature->m_movementInfo.transport.pos.Relocate(x, y, z, o);
    creature->m_movementInfo.transport.seat = -1;
    CalculatePassengerPosition(x, y, z, &o);
    creature->Relocate(x, y, z, o);
    creature->SetHomePosition(creature->GetPositionX(), creature->GetPositionY(), creature->GetPositionZ(), creature->GetOrientation());
    creature->SetTransportHomePosition(creature->m_movementInfo.transport.pos);
    TC_LOG_DEBUG("entities.transport", "created npc pessenger %s for %s", creature->GetName().c_str(), GetName().c_str());
    /// @HACK - transport models are not added to map's dynamic LoS calculations
    ///         because the current GameObjectModel cannot be moved without recreating
    if (!_mmapsLoaded)
        creature->AddUnitState(UNIT_STATE_IGNORE_PATHFINDING);

    if (!creature->IsPositionValid())
    {
        TC_LOG_ERROR("entities.transport", "Passenger %s not created. Suggested coordinates aren't valid (X: %f Y: %f)", creature->GetGUID().ToString().c_str(), creature->GetPositionX(), creature->GetPositionY());
        delete creature;
        return nullptr;
    }

    PhasingHandler::InitDbPhaseShift(creature->GetPhaseShift(), data->phaseUseFlags, data->phaseId, data->phaseGroup);
    PhasingHandler::InitDbVisibleMapId(creature->GetPhaseShift(), data->terrainSwapMap);

    if (!map->AddToMap(creature))
    {
        delete creature;
        return nullptr;
    }

    _staticPassengers.insert(creature);
    sScriptMgr->OnAddCreaturePassenger(this, creature);
    return creature;
}

GameObject* Transport::CreateGOPassenger(ObjectGuid::LowType guid, GameObjectData const* data)
{
    ASSERT(data);

    Map* map = GetMap();

	if (!guid)
		return nullptr;

    // The grid contains the transport and the passengers
    // and it will try to load the transport as a passenger
    // of it self, this shoul fix it
	if (m_spawnId == guid)
		return nullptr;

    GameObject* go = GameObject::CreateGameObjectFromDB(guid, map, false);
    if (!go)
        return nullptr;

    ASSERT(data);

    float x = data->spawnPoint.GetPositionX();
    float y = data->spawnPoint.GetPositionY();
    float z = data->spawnPoint.GetPositionZ();
    float o = data->spawnPoint.GetOrientation();

    go->SetTransport(this);
    go->m_movementInfo.transport.guid = GetGUID();
    go->m_movementInfo.transport.pos.Relocate(x, y, z, o);
    go->m_movementInfo.transport.seat = -1;
    CalculatePassengerPosition(x, y, z, &o);
    go->Relocate(x, y, z, o);
    go->RelocateStationaryPosition(x, y, z, o);

    if (!go->IsPositionValid())
    {
        TC_LOG_ERROR("entities.transport", "Passenger %s not created. Suggested coordinates aren't valid (X: %f Y: %f)", go->GetGUID().ToString().c_str(), go->GetPositionX(), go->GetPositionY());
        delete go;
        return nullptr;
    }

    PhasingHandler::InitDbPhaseShift(go->GetPhaseShift(), data->phaseUseFlags, data->phaseId, data->phaseGroup);
    PhasingHandler::InitDbVisibleMapId(go->GetPhaseShift(), data->terrainSwapMap);

    if (!map->AddToMap(go))
    {
        delete go;
        return nullptr;
    }

    _staticPassengers.insert(go);
    return go;
}

TempSummon* Transport::SummonPassenger(uint32 entry, Position const& pos, TempSummonType summonType, SummonPropertiesEntry const* properties /*= NULL*/, uint32 duration /*= 0*/, Unit* summoner /*= NULL*/, uint32 spellId /*= 0*/, uint32 vehId /*= 0*/)
{
    Map* map = FindMap();
    if (!map)
        return NULL;

    uint32 mask = UNIT_MASK_SUMMON;
    if (properties)
    {
        switch (properties->Control)
        {
            case SUMMON_CATEGORY_PET:
                mask = UNIT_MASK_GUARDIAN;
                break;
            case SUMMON_CATEGORY_PUPPET:
                mask = UNIT_MASK_PUPPET;
                break;
            case SUMMON_CATEGORY_VEHICLE:
                mask = UNIT_MASK_MINION;
                break;
            case SUMMON_CATEGORY_WILD:
            case SUMMON_CATEGORY_ALLY:
            case SUMMON_CATEGORY_UNK:
            {
                switch (SummonTitle(properties->Title))
                {
                    case SummonTitle::Minion:
                    case SummonTitle::Guardian:
                    case SummonTitle::Runeblade:
                        mask = UNIT_MASK_GUARDIAN;
                        break;
                    case SummonTitle::Totem:
                    case SummonTitle::Lightwell:
                        mask = UNIT_MASK_TOTEM;
                        break;
                    case SummonTitle::Vehicle:
                    case SummonTitle::Mount:
                        mask = UNIT_MASK_SUMMON;
                        break;
                    case SummonTitle::Companion:
                        mask = UNIT_MASK_MINION;
                        break;
                    default:
                        if (properties->Flags & 512) // Mirror Image, Summon Gargoyle
                            mask = UNIT_MASK_GUARDIAN;
                        break;
                }
                break;
            }
            default:
                return NULL;
        }
    }

    TempSummon* summon = nullptr;
    switch (mask)
    {
        case UNIT_MASK_SUMMON:
            summon = new TempSummon(properties, summoner, false);
            break;
        case UNIT_MASK_GUARDIAN:
            summon = new Guardian(properties, summoner, false);
            break;
        case UNIT_MASK_PUPPET:
            summon = new Puppet(properties, summoner);
            break;
        case UNIT_MASK_TOTEM:
            summon = new Totem(properties, summoner);
            break;
        case UNIT_MASK_MINION:
            summon = new Minion(properties, summoner, false);
            break;
    }

    float x, y, z, o;
    pos.GetPosition(x, y, z, o);
    CalculatePassengerPosition(x, y, z, &o);

    if (!summon->Create(map->GenerateLowGuid<HighGuid::Creature>(), map, entry, { x, y, z, o }, nullptr, vehId))
    {
        delete summon;
        return nullptr;
    }

    PhasingHandler::InheritPhaseShift(summon, summoner ? static_cast<WorldObject*>(summoner) : static_cast<WorldObject*>(this));

    summon->SetCreatedBySpell(spellId);

    summon->SetTransport(this);
    summon->m_movementInfo.transport.guid = GetGUID();
    summon->m_movementInfo.transport.pos.Relocate(pos);
    summon->m_movementInfo.transport.time = GetPathProgress();
    summon->Relocate(x, y, z, o);
    summon->SetHomePosition(x, y, z, o);
    summon->SetTransportHomePosition(pos);

    /// @HACK - transport models are not added to map's dynamic LoS calculations
    ///         because the current GameObjectModel cannot be moved without recreating
    if (!_mmapsLoaded)
        summon->AddUnitState(UNIT_STATE_IGNORE_PATHFINDING);

    summon->InitStats(duration);

    if (!map->AddToMap<Creature>(summon))
    {
        delete summon;
        return nullptr;
    }

    _staticPassengers.insert(summon);

    summon->InitSummon();
    summon->SetTempSummonType(summonType);

    return summon;
}

int32 MapTransport::GetMapIdForSpawning() const
{
    return GetGOInfo()->moTransport.SpawnMap;
}

void MapTransport::UpdatePosition(float x, float y, float z, float o)
{
    bool newActive = GetMap()->IsGridLoaded(x, y);
    Cell oldCell(GetPositionX(), GetPositionY());

    Relocate(x, y, z, o);
    m_stationaryPosition.SetOrientation(o);
    UpdateModelPosition();

    UpdatePassengerPositions(_passengers);

    /* There are four possible scenarios that trigger loading/unloading passengers:
      1. transport moves from inactive to active grid
      2. the grid that transport is currently in becomes active
      3. transport moves from active to inactive grid
      4. the grid that transport is currently in unloads
    */
    if (_staticPassengers.empty() && newActive) // 1.
        LoadStaticPassengers();
    else if (!_staticPassengers.empty() && !newActive && oldCell.DiffGrid(Cell(GetPositionX(), GetPositionY()))) // 3.
        UnloadStaticPassengers();
    else
        UpdatePassengerPositions(_staticPassengers);
    // 4. is handed by grid unload
}

void Transport::LoadStaticPassengers()
{
    uint32 mapId = GetGOInfo()->type == GAMEOBJECT_TYPE_TRANSPORT ? GetGOInfo()->transport.SpawnMap : GetGOInfo()->moTransport.SpawnMap;
    if (mapId)
    {
        CellObjectGuidsMap const& cells = sObjectMgr->GetMapObjectGuids(mapId, GetMap()->GetDifficultyID());
        CellGuidSet::const_iterator guidEnd;
        for (CellObjectGuidsMap::const_iterator cellItr = cells.begin(); cellItr != cells.end(); ++cellItr)
        {
            // Creatures on transport
            guidEnd = cellItr->second.creatures.end();
            for (CellGuidSet::const_iterator guidItr = cellItr->second.creatures.begin(); guidItr != guidEnd; ++guidItr)
                CreateNPCPassenger(*guidItr, sObjectMgr->GetCreatureData(*guidItr));

            // GameObjects on transport
            guidEnd = cellItr->second.gameobjects.end();
            for (CellGuidSet::const_iterator guidItr = cellItr->second.gameobjects.begin(); guidItr != guidEnd; ++guidItr)
                CreateGOPassenger(*guidItr, sObjectMgr->GetGameObjectData(*guidItr));
        }
    }
}

void Transport::UnloadStaticPassengers()
{
    // map unload or transport remove does this already
    while (!_staticPassengers.empty())
    {
        WorldObject* obj = *_staticPassengers.begin();
        obj->AddObjectToRemoveList();   // also removes from _staticPassengers
    }
}

void MapTransport::EnableMovement(bool enabled)
{
    if (!GetGOInfo()->moTransport.allowstopping)
        return;

    _pendingStop = !enabled;
}

void MapTransport::MoveToNextWaypoint()
{
    // Clear events flagging
    _triggeredArrivalEvent = false;
    _triggeredDepartureEvent = false;

    // Set frames
    _currentFrame = _nextFrame++;
    if (_nextFrame == GetKeyFrames().end())
        _nextFrame = GetKeyFrames().begin();
}

float MapTransport::CalculateSegmentPos(float now)
{
    KeyFrame const& frame = *_currentFrame;
    const float speed = float(m_goInfo->moTransport.moveSpeed);
    const float accel = float(m_goInfo->moTransport.accelRate);
    float timeSinceStop = frame.TimeFrom + (now - (1.0f/IN_MILLISECONDS) * frame.DepartureTime);
    float timeUntilStop = frame.TimeTo - (now - (1.0f/IN_MILLISECONDS) * frame.DepartureTime);
    float segmentPos, dist;
    float accelTime = _transportInfo->accelTime;
    float accelDist = _transportInfo->accelDist;
    // calculate from nearest stop, less confusing calculation...
    if (timeSinceStop < timeUntilStop)
    {
        if (timeSinceStop < accelTime)
            dist = 0.5f * accel * timeSinceStop * timeSinceStop;
        else
            dist = accelDist + (timeSinceStop - accelTime) * speed;
        segmentPos = dist - frame.DistSinceStop;
    }
    else
    {
        if (timeUntilStop < _transportInfo->accelTime)
            dist = 0.5f * accel * timeUntilStop * timeUntilStop;
        else
            dist = accelDist + (timeUntilStop - accelTime) * speed;
        segmentPos = frame.DistUntilStop - dist;
    }

    return segmentPos / frame.NextDistFromPrev;
}

bool MapTransport::TeleportTransport(uint32 newMapid, float x, float y, float z, float o)
{
    Map const* oldMap = GetMap();

    if (oldMap->GetId() != newMapid)
    {
        _delayedTeleport = true;
        UnLoadMMaps();
        return true;
    }
    else
    {
        UpdatePosition(x, y, z, o);

        return false;
    }
}

void MapTransport::DelayedTeleportTransport()
{
    if (!_delayedTeleport)
        return;

    _delayedTeleport = false;
    Map* newMap = sMapMgr->CreateBaseMap(_nextFrame->Node->ContinentID);
    GetMap()->RemoveFromMap<MapTransport>(this, false);
    SetMap(newMap);

    float x = _nextFrame->Node->Loc.X,
          y = _nextFrame->Node->Loc.Y,
          z = _nextFrame->Node->Loc.Z,
          o =_nextFrame->InitialOrientation;

    for (_passengerTeleportItr = _passengers.begin(); _passengerTeleportItr != _passengers.end();)
    {
        WorldObject* obj = (*_passengerTeleportItr++);

        float destX, destY, destZ, destO;
        obj->m_movementInfo.transport.pos.GetPosition(destX, destY, destZ, destO);
        TransportBase::CalculatePassengerPosition(destX, destY, destZ, &destO, x, y, z, o);

        switch (obj->GetTypeId())
        {
            case TYPEID_PLAYER:
                if (!obj->ToPlayer()->TeleportTo(_nextFrame->Node->ContinentID, destX, destY, destZ, destO, TELE_TO_NOT_LEAVE_TRANSPORT, 0, this))
                    RemovePassenger(obj);
                break;
            case TYPEID_DYNAMICOBJECT:
            case TYPEID_AREATRIGGER:
                obj->AddObjectToRemoveList();
                break;
            default:
                RemovePassenger(obj);
                break;
        }
    }

    // Unload the static passengers, will reload when added to new map and/or grid is activated
    UnloadStaticPassengers();

    Relocate(x, y, z, o);
    GetMap()->AddToMap<MapTransport>(this);
    LoadMMaps();
}

void MapTransport::DoEventIfAny(KeyFrame const& node, bool departure)
{
    if (uint32 eventid = departure ? node.Node->DepartureEventID : node.Node->ArrivalEventID)
    {
        TC_LOG_DEBUG("maps.script", "Taxi %s event %u of node %u of %s path", departure ? "departure" : "arrival", eventid, node.Node->NodeIndex, GetName().c_str());
        GameEvents::Trigger(eventid, this, this);
    }
}

void MapTransport::BuildUpdate(UpdateDataMapType& data_map)
{
    Map::PlayerList const& players = GetMap()->GetPlayers();
    if (players.isEmpty())
        return;

    for (Map::PlayerList::const_iterator itr = players.begin(); itr != players.end(); ++itr)
        BuildFieldsUpdate(itr->GetSource(), data_map);

    ClearUpdateMask(true);
}

void Transport::LoadMMaps()
{
    uint32 modelID = GetDisplayId();

    _mmapsLoaded = MMAP::MMapFactory::createOrGetMMapManager()->loadTransportMap(sWorld->GetDataPath(), modelID);

    if (_mmapsLoaded)
        TC_LOG_DEBUG("mmaps", "Transport MMAP loaded modelID: %d", modelID);
    else
        TC_LOG_DEBUG("mmaps", "Could not load transport MMAP modelID: %d", modelID);
}

void Transport::UnLoadMMaps()
{
    MMAP::MMapFactory::createOrGetMMapManager()->unloadTransportMap(GetDisplayId());

    _mmapsLoaded = false;
}
