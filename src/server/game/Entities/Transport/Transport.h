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

#ifndef TRANSPORTS_H
#define TRANSPORTS_H

#include "GameObject.h"
#include "TransportMgr.h"
#include "VehicleDefines.h"

struct CreatureData;
struct SummonPropertiesEntry;

class TC_GAME_API Transport : public GameObject, public TransportBase
{
    public:
        typedef std::set<WorldObject*> PassengerSet;

        Transport();
        ~Transport();

        bool Create(uint32 entry, Map* map, Position const& pos, QuaternionData const& rotation, uint32 animProgress, GOState goState, uint32 artKit, bool dynamic, ObjectGuid::LowType spawnid) override;
        //bool Create(ObjectGuid::LowType guidlow, uint32 entry, uint32 mapid, float x, float y, float z, float ang, uint32 animprogress);
        //bool Create(ObjectGuid::LowType guidlow, uint32 entry, uint32 mapid, float x, float y, float z, float ang, uint32 animprogress) override;
        //bool Create(uint32 entry, Map* map, Position const& pos, QuaternionData const& rotation, uint32 animprogress, GOState go_state, uint32 artKit = 0, bool dynamic = false, ObjectGuid::LowType spawnid = 0) override;
        bool CreateTransport(ObjectGuid::LowType guidlow, uint32 entry, uint32 mapid, Position const& pos, uint32 animprogress);

        void CleanupsBeforeDelete(bool finalCleanup = true) override;
        
        void AddPassenger(WorldObject* passenger) override;
        Transport* RemovePassenger(WorldObject* passenger) override;
        PassengerSet const& GetPassengers() const { return _passengers; }

        /// This method transforms supplied transport offsets into global coordinates
        void CalculatePassengerPosition(float& x, float& y, float& z, float* o = nullptr) const override
        {
            TransportBase::CalculatePassengerPosition(x, y, z, o, GetPositionX(), GetPositionY(), GetPositionZ(), GetTransportOrientation());
        }

        /// This method transforms supplied global coordinates into local offsets
        void CalculatePassengerOffset(float& x, float& y, float& z, float* o = nullptr) const override
        {
            TransportBase::CalculatePassengerOffset(x, y, z, o, GetPositionX(), GetPositionY(), GetPositionZ(), GetTransportOrientation());
        }

        int32 GetMapIdForSpawning() const override;

        void SetAutoCycleBetweenStopFrames(bool on)
        {
            _autoCycleBetweenStopFrames = on;
        }

        std::vector<uint32> const* GetPauseTimes() const
        {
            return &_stopFrames;
        }

        void Update(uint32 diff) override;

        bool IsDynamicTransport() const { return _isDynamicTransport; }

        virtual uint32 GetTransportPeriod() const;

        uint32 GetPathProgress() const { return _pathProgress; }
        void SetPathProgress(uint32 val) { _pathProgress = val; }

        void SetPeriod(uint32 period) { SetLevel(period); }
        uint32 GetTimer() const { return _pathProgress; }

        void SetTransportState(GOState state, bool instant = false);
        void SetTransportLoop(bool on);

        void SetDestinationStopFrameTime(uint32 time) { _destinationStopFrameTime = time; }
        uint32 GetDestinationStopFrameTime() const { return _destinationStopFrameTime; }

        void SetCurrentTransportTime(uint32 time) { _currentTransportTime = time; }
        uint32 GetCurrentTransportTime() const { return _currentTransportTime; }

        void SetLastTransportTime(uint32 time) { _lastTransportTime = time; }
        uint32 GetLastTransportTime() const { return _lastTransportTime; }

        void SetAlignmentTransportTime(uint32 time) { _alignmentTransportTime = time; }
        uint32 GetAlightmentTransportTime() const { return _alignmentTransportTime; }

        void SetLastStopFrameTime(uint32 time) { _lastStopFrameTime = time; }
        uint32 GetLastStopFrameTime() const { return _lastStopFrameTime; }

        uint32 GetLoopTimer() const { return _loopTimer; }
        TransportMoveDirection GetMoveDirection() const { return _moveDirection; }
        bool IsLoop() { return _isLoop; }

        //! Needed when transport moves from inactive to active grid
        void LoadStaticPassengers();

        //! Needed when transport enters inactive grid
        void UnloadStaticPassengers();
        PassengerSet const& GetStaticPassengers() const { return _staticPassengers; }

        Creature* CreateNPCPassenger(ObjectGuid::LowType guid, CreatureData const* data);
        GameObject* CreateGOPassenger(ObjectGuid::LowType guid, GameObjectData const* data);
        TempSummon* SummonPassenger(uint32 entry, Position const& pos, TempSummonType summonType, SummonPropertiesEntry const* properties = NULL, uint32 duration = 0, Unit* summoner = NULL, uint32 spellId = 0, uint32 vehId = 0);

        ObjectGuid GetTransportGUID() const override { return GetGUID(); }

        float GetTransportOrientation() const override { return GetOrientation(); }

        void LoadMMaps();
        void UnLoadMMaps();

        bool MMapsLoaded() const { return _mmapsLoaded; }

    private:
        void SetLoopTimer(uint32 time) { _loopTimer = time; }
        void SetMoveDirection(TransportMoveDirection dir) { _moveDirection = dir; }
        void SetLoop(bool loop) { _isLoop = loop; }

        bool _mmapsLoaded;

    protected:
        void UpdatePassengerPositions(PassengerSet const& passengers);

        PassengerSet _passengers;
        PassengerSet::iterator _passengerTeleportItr;

        PassengerSet _staticPassengers;

        uint32 _destinationStopFrameTime;
        uint32 _currentTransportTime;
        uint32 _lastTransportTime;
        uint32 _alignmentTransportTime;
        uint32 _lastStopFrameTime;
        bool _isDynamicTransport;
        bool _initialRelocate;

        bool _isLoop;
        uint32 _loopTimer; // wait 5000ms on every floor, blizzlike value
        TransportMoveDirection _moveDirection; // 0 stopped, 1 up, 2 down
        uint32 _pathProgress;

        TransportAnimation const* _animationInfo;
        uint32 _stateChangeTime;
        uint32 _stateChangeProgress;
        std::vector<uint32> _stopFrames;
        bool _autoCycleBetweenStopFrames;
        TimeTracker _positionUpdateTimer;
};

class TC_GAME_API MapTransport : public Transport
{
        friend MapTransport* TransportMgr::CreateTransport(uint32, ObjectGuid::LowType, Map*, uint8, uint32, uint32);

        MapTransport();
    public:
        ~MapTransport();

        bool CreateMapTransport(ObjectGuid::LowType guidlow, uint32 entry, uint32 mapid, float x, float y, float z, float ang, uint32 animprogress);
        void CleanupsBeforeDelete(bool finalCleanup = true) override;

        void Update(uint32 diff) override;
        void DelayedUpdate(uint32 diff);

        void BuildUpdate(UpdateDataMapType& data_map) override;

        KeyFrameVec const& GetKeyFrames() const { return _transportInfo->keyFrames; }

        void UpdatePosition(float x, float y, float z, float o);

        void EnableMovement(bool enabled);

        void SetDelayedAddModelToMap() { _delayedAddModel = true; }

        TransportTemplate const* GetTransportTemplate() const { return _transportInfo; }

        int32 GetMapIdForSpawning() const override;


    private:
        void MoveToNextWaypoint();
        float CalculateSegmentPos(float perc);
        bool TeleportTransport(uint32 newMapid, float x, float y, float z, float o);
        void DelayedTeleportTransport();
        void DoEventIfAny(KeyFrame const& node, bool departure);

        //! Helpers to know if stop frame was reached
        bool IsMoving() const { return _isMoving; }
        void SetMoving(bool val) { _isMoving = val; }

        uint32 GetTransportPeriod() const override { return m_gameObjectData->Level; }

        TransportTemplate const* _transportInfo;

        KeyFrameVec::const_iterator _currentFrame;
        KeyFrameVec::const_iterator _nextFrame;
        TimeTracker _positionChangeTimer;
        bool _isMoving;
        bool _pendingStop;

        //! These are needed to properly control events triggering only once for each frame
        bool _triggeredArrivalEvent;
        bool _triggeredDepartureEvent;

        bool _delayedAddModel;
        bool _delayedTeleport;
};

#endif
