/*
 * This file is part of the TrinityCore Project. See AUTHORS file for Copyright information
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

#include "InstanceScript.h"
#include "AreaBoundary.h"
#include "ChallengeMode.h"
#include "ChallengeModeMgr.h"
#include "ChallengeModePackets.h"
#include "Creature.h"
#include "CreatureAI.h"
#include "CreatureAIImpl.h"
#include "DatabaseEnv.h"
#include "DB2Stores.h"
#include "GameEventSender.h"
#include "GameObject.h"
#include "Group.h"
#include "InstancePackets.h"
#include "InstanceScenario.h"
#include "InstanceScriptData.h"
#include "LFGMgr.h"
#include "Log.h"
#include "Map.h"
#include "ObjectMgr.h"
#include "PhasingHandler.h"
#include "Player.h"
#include "RBAC.h"
#include "ScriptedCreature.h"
#include "ScriptReloadMgr.h"
#include "SmartEnum.h"
#include "SpellMgr.h"
#include "World.h"
#include "WorldSession.h"
#include "WorldStateMgr.h"
#include <cstdarg>
#include "TemporarySummon.h"
#include "SpellHistory.h"
#include "SpellAuras.h"
#include "Spell.h"
#include "Item.h"
#include "ScenarioMgr.h"
#include "Guild.h"
#include "PlayerChallenge.h"

#ifdef TRINITY_API_USE_DYNAMIC_LINKING
#include "ScriptMgr.h"
#endif

BossBoundaryData::~BossBoundaryData()
{
    for (const_iterator it = begin(); it != end(); ++it)
        delete it->Boundary;
}

DungeonEncounterEntry const* BossInfo::GetDungeonEncounterForDifficulty(Difficulty difficulty) const
{
    auto itr = std::find_if(DungeonEncounters.begin(), DungeonEncounters.end(), [difficulty](DungeonEncounterEntry const* dungeonEncounter)
    {
        return dungeonEncounter && (dungeonEncounter->DifficultyID == 0 || Difficulty(dungeonEncounter->DifficultyID) == difficulty);
    });

    return itr != DungeonEncounters.end() ? *itr : nullptr;
}

InstanceScript::InstanceScript(InstanceMap* map) : instance(map), completedEncounters(0), _instanceSpawnGroups(sObjectMgr->GetInstanceSpawnGroupsForMap(map->GetId())),
_entranceId(0), _temporaryEntranceId(0), _combatResurrectionTimer(0), _combatResurrectionCharges(0), _combatResurrectionTimerStarted(false),
_disabledMask(0), _encounterTime(0), _challenge(nullptr), initDamageManager(false), emptyWarned(false)
{
#ifdef TRINITY_API_USE_DYNAMIC_LINKING
    uint32 scriptId = sObjectMgr->GetInstanceTemplate(map->GetId())->ScriptId;
    auto const scriptname = sObjectMgr->GetScriptName(scriptId);
    ASSERT(!scriptname.empty());
   // Acquire a strong reference from the script module
   // to keep it loaded until this object is destroyed.
    module_reference = sScriptMgr->AcquireModuleReferenceOfScriptName(scriptname);
#endif // #ifndef TRINITY_API_USE_DYNAMIC_LINKING
}

InstanceScript::~InstanceScript()
{
    if (_challenge)
    {
        /// InstanceScript will be set to nullptr in challenge's deconstructor
        delete _challenge;
        _challenge = nullptr;
    }
}

bool InstanceScript::IsEncounterInProgress() const
{
    for (std::vector<BossInfo>::const_iterator itr = bosses.begin(); itr != bosses.end(); ++itr)
        if (itr->state == IN_PROGRESS)
            return true;

    return false;
}

void InstanceScript::OnCreatureCreate(Creature* creature)
{
    AddObject(creature, true);
    AddMinion(creature, true);
}

void InstanceScript::OnCreatureRemove(Creature* creature)
{
    AddObject(creature, false);
    AddMinion(creature, false);
}

void InstanceScript::OnGameObjectCreate(GameObject* go)
{
    AddObject(go, true);
    AddDoor(go, true);
}

void InstanceScript::OnGameObjectRemove(GameObject* go)
{
    AddObject(go, false);
    AddDoor(go, false);
}

ObjectGuid InstanceScript::GetObjectGuid(uint32 type) const
{
    ObjectGuidMap::const_iterator i = _objectGuids.find(type);
    if (i != _objectGuids.end())
        return i->second;
    return ObjectGuid::Empty;
}

ObjectGuid InstanceScript::GetGuidData(uint32 type) const
{
    return GetObjectGuid(type);
}

void InstanceScript::TriggerGameEvent(uint32 gameEventId, WorldObject* source /*= nullptr*/, WorldObject* target /*= nullptr*/)
{
    if (source)
    {
        ZoneScript::TriggerGameEvent(gameEventId, source, target);
        return;
    }

    ProcessEvent(target, gameEventId, source);
    instance->DoOnPlayers([gameEventId](Player* player)
    {
        GameEvents::TriggerForPlayer(gameEventId, player);
    });

    GameEvents::TriggerForMap(gameEventId, instance);
}

Creature* InstanceScript::GetCreature(uint32 type)
{
    return instance->GetCreature(GetObjectGuid(type));
}

GameObject* InstanceScript::GetGameObject(uint32 type)
{
    return instance->GetGameObject(GetObjectGuid(type));
}

void InstanceScript::SetHeaders(std::string const& dataHeaders)
{
    headers = dataHeaders;
}

void InstanceScript::LoadBossBoundaries(BossBoundaryData const& data)
{
    for (BossBoundaryEntry const& entry : data)
        if (entry.BossId < bosses.size())
            bosses[entry.BossId].boundary.push_back(entry.Boundary);
}

void InstanceScript::LoadEntranceData(const EntranceData* data)
{
    while (data->WorldSafeLocId)
    {
        if (data->BossId < bosses.size())
            entrances[data->BossId] = data->WorldSafeLocId;

        ++data;
    }
    TC_LOG_DEBUG("scripts", "InstanceScript::LoadEntranceLocations: " UI64FMTD " entrances loaded.", uint64(entrances.size()));
}

void InstanceScript::LoadMinionData(MinionData const* data)
{
    while (data->entry)
    {
        if (data->bossId < bosses.size())
            minions.insert(std::make_pair(data->entry, MinionInfo(&bosses[data->bossId])));

        ++data;
    }
    TC_LOG_DEBUG("scripts", "InstanceScript::LoadMinionData: " UI64FMTD " minions loaded.", uint64(minions.size()));
}

void InstanceScript::LoadDoorData(DoorData const* data)
{
    while (data->entry)
    {
        if (data->bossId < bosses.size())
            doors.insert(std::make_pair(data->entry, DoorInfo(&bosses[data->bossId], data->type)));

        ++data;
    }
    TC_LOG_DEBUG("scripts", "InstanceScript::LoadDoorData: " UI64FMTD " doors loaded.", uint64(doors.size()));
}

void InstanceScript::LoadObjectData(ObjectData const* creatureData, ObjectData const* gameObjectData)
{
    if (creatureData)
        LoadObjectData(creatureData, _creatureInfo);

    if (gameObjectData)
        LoadObjectData(gameObjectData, _gameObjectInfo);

    TC_LOG_DEBUG("scripts", "InstanceScript::LoadObjectData: " SZFMTD " objects loaded.", _creatureInfo.size() + _gameObjectInfo.size());
}

void InstanceScript::LoadObjectData(ObjectData const* data, ObjectInfoMap& objectInfo)
{
    while (data->entry)
    {
        ASSERT(objectInfo.find(data->entry) == objectInfo.end());
        objectInfo[data->entry] = data->type;
        ++data;
    }
}

void InstanceScript::LoadDungeonEncounterData(uint32 bossId, std::array<uint32, MAX_DUNGEON_ENCOUNTERS_PER_BOSS> const& dungeonEncounterIds)
{
    if (bossId < bosses.size())
        for (std::size_t i = 0; i < MAX_DUNGEON_ENCOUNTERS_PER_BOSS; ++i)
            bosses[bossId].DungeonEncounters[i] = sDungeonEncounterStore.LookupEntry(dungeonEncounterIds[i]);
}

void InstanceScript::UpdateDoorState(GameObject* door)
{
    DoorInfoMapBounds range = doors.equal_range(door->GetEntry());
    if (range.first == range.second)
        return;

    bool open = true;
    DoorType doorType = DOOR_TYPE_ROOM;
    for (; range.first != range.second && open; ++range.first)
    {
        DoorInfo const& info = range.first->second;
        switch (info.type)
        {
            case DOOR_TYPE_ROOM:
                open = (info.bossInfo->state != IN_PROGRESS);
                break;
            case DOOR_TYPE_PASSAGE:
                open = (info.bossInfo->state == DONE);
                break;
            case DOOR_TYPE_SPAWN_HOLE:
                open = (info.bossInfo->state == IN_PROGRESS);
                break;
            default:
                break;
        }
        if (!open)
            doorType = info.type;
    }
    
    // Delay Door closing, like retail
    if (!open)
    {
        ObjectGuid doorGuid = door->GetGUID();
        AddTimedDelayedOperation(5 * TimeConstants::IN_MILLISECONDS, [this, doorGuid, doorType]() -> void
        {
            if (GameObject* doorFinded = instance->GetGameObject(doorGuid))
            {
                // prev expasions bosses die really fast
                if (InstanceScript* instance = doorFinded->GetInstanceScript())
                    if (!instance->IsEncounterInProgress() && doorType == DOOR_TYPE_ROOM)
                        return;
            
                doorFinded->SetGoState(GOState::GO_STATE_READY);
            }
        });
    }
    else
        door->SetGoState(GOState::GO_STATE_ACTIVE);
}

void InstanceScript::UpdateMinionState(Creature* minion, EncounterState state)
{
    switch (state)
    {
        case NOT_STARTED:
            if (!minion->IsAlive())
                minion->Respawn();
            else if (minion->IsInCombat())
                minion->AI()->EnterEvadeMode();
            break;
        case IN_PROGRESS:
            if (!minion->IsAlive())
                minion->Respawn();
            else if (!minion->GetVictim())
                minion->AI()->DoZoneInCombat();
            break;
        default:
            break;
    }
}

void InstanceScript::UpdateSpawnGroups()
{
    if (!_instanceSpawnGroups)
        return;
    enum states { BLOCK, SPAWN, FORCEBLOCK };
    std::unordered_map<uint32, states> newStates;
    for (auto it = _instanceSpawnGroups->begin(), end = _instanceSpawnGroups->end(); it != end; ++it)
    {
        InstanceSpawnGroupInfo const& info = *it;
        states& curValue = newStates[info.SpawnGroupId]; // makes sure there's a BLOCK value in the map
        if (curValue == FORCEBLOCK) // nothing will change this
            continue;
        if (!((1 << GetBossState(info.BossStateId)) & info.BossStates))
            continue;
        if (((instance->GetTeamIdInInstance() == TEAM_ALLIANCE) && (info.Flags & InstanceSpawnGroupInfo::FLAG_HORDE_ONLY))
            || ((instance->GetTeamIdInInstance() == TEAM_HORDE) && (info.Flags & InstanceSpawnGroupInfo::FLAG_ALLIANCE_ONLY)))
            continue;
        if (info.Flags & InstanceSpawnGroupInfo::FLAG_BLOCK_SPAWN)
            curValue = FORCEBLOCK;
        else if (info.Flags & InstanceSpawnGroupInfo::FLAG_ACTIVATE_SPAWN)
            curValue = SPAWN;
    }
    for (auto const& pair : newStates)
    {
        uint32 const groupId = pair.first;
        bool const doSpawn = (pair.second == SPAWN);
        if (instance->IsSpawnGroupActive(groupId) == doSpawn)
            continue; // nothing to do here
        // if we should spawn group, then spawn it...
        if (doSpawn)
            instance->SpawnGroupSpawn(groupId);
        else // otherwise, set it as inactive so it no longer respawns (but don't despawn it)
            instance->SetSpawnGroupInactive(groupId);
    }
}

BossInfo* InstanceScript::GetBossInfo(uint32 id)
{
    ASSERT(id < bosses.size());
    return &bosses[id];
}

void InstanceScript::AddObject(Creature* obj, bool add)
{
    ObjectInfoMap::const_iterator j = _creatureInfo.find(obj->GetEntry());
    if (j != _creatureInfo.end())
        AddObject(obj, j->second, add);
}

void InstanceScript::AddObject(GameObject* obj, bool add)
{
    ObjectInfoMap::const_iterator j = _gameObjectInfo.find(obj->GetEntry());
    if (j != _gameObjectInfo.end())
        AddObject(obj, j->second, add);
}

void InstanceScript::AddObject(WorldObject* obj, uint32 type, bool add)
{
    if (add)
        _objectGuids[type] = obj->GetGUID();
    else
    {
        ObjectGuidMap::iterator i = _objectGuids.find(type);
        if (i != _objectGuids.end() && i->second == obj->GetGUID())
            _objectGuids.erase(i);
    }
}

void InstanceScript::AddDoor(GameObject* door, bool add)
{
    DoorInfoMapBounds range = doors.equal_range(door->GetEntry());
    if (range.first == range.second)
        return;

    for (; range.first != range.second; ++range.first)
    {
        DoorInfo const& data = range.first->second;

        if (add)
        {
            data.bossInfo->door[data.type].insert(door->GetGUID());
        }
        else
            data.bossInfo->door[data.type].erase(door->GetGUID());
    }

    if (add)
        UpdateDoorState(door);
}

void InstanceScript::AddMinion(Creature* minion, bool add)
{
    MinionInfoMap::iterator itr = minions.find(minion->GetEntry());
    if (itr == minions.end())
        return;

    if (add)
        itr->second.bossInfo->minion.insert(minion->GetGUID());
    else
        itr->second.bossInfo->minion.erase(minion->GetGUID());
}

bool InstanceScript::SetBossState(uint32 id, EncounterState state, bool forced /*= false*/)
{
    if (id < bosses.size())
    {
        BossInfo* bossInfo = &bosses[id];
        if (bossInfo->state == TO_BE_DECIDED) // loading
        {
            bossInfo->state = state;
            TC_LOG_DEBUG("scripts", "InstanceScript: Initialize boss %u state as %s (map %u, %u).", id, GetBossStateName(state), instance->GetId(), instance->GetInstanceId());
            return false;
        }
        else
        {
            if (bossInfo->state == state)
                return false;

            if (bossInfo->state == DONE && !forced)
            {
                TC_LOG_ERROR("map", "InstanceScript: Tried to set instance boss %u state from %s back to %s for map %u, instance id %u. Blocked!", id, GetBossStateName(bossInfo->state), GetBossStateName(state), instance->GetId(), instance->GetInstanceId());
                return false;
            }

            if (state == DONE)
                for (GuidSet::iterator i = bossInfo->minion.begin(); i != bossInfo->minion.end(); ++i)
                    if (Creature* minion = instance->GetCreature(*i))
                        if (minion->isWorldBoss() && minion->IsAlive())
                            return false;

            DungeonEncounterEntry const* dungeonEncounter = nullptr;
            switch (state)
            {
                case NOT_STARTED:
                {
                    if (bossInfo->state == IN_PROGRESS)
                    {
                        if (!IsChallenge())
                            ResetCombatResurrections();

                        SendEncounterEnd();
                    }
                    break;
                }
                case IN_PROGRESS:
                {
                    _encounterTime = uint32(time(nullptr));

                    uint32 resInterval = GetCombatResurrectionChargeInterval();
                    InitializeCombatResurrections(1, resInterval);
                    SendEncounterStart(_combatResurrectionCharges, IsChallenge() ? 5 : 9, resInterval, _combatResurrectionTimer);

                    instance->DoOnPlayers([](Player* player)
                    {
                        if (player->IsAlive())
                            Unit::ProcSkillsAndAuras(player, nullptr, PROC_FLAG_ENCOUNTER_START, PROC_FLAG_NONE, PROC_SPELL_TYPE_MASK_ALL, PROC_SPELL_PHASE_NONE, PROC_HIT_NONE, nullptr, nullptr, nullptr);
                    });
                    break;
                }
                case DONE:
                    if (!IsChallenge())
                        ResetCombatResurrections();

                    SendEncounterEnd();
                    dungeonEncounter = bossInfo->GetDungeonEncounterForDifficulty(instance->GetDifficultyID());
                    if (dungeonEncounter)
                    {
                        DoUpdateCriteria(CriteriaType::DefeatDungeonEncounter, dungeonEncounter->ID);
                        SendBossKillCredit(dungeonEncounter->ID);
                    }
                    SendCompleteGuildChallenge(id);
                    SetEntranceLocation(entrances.count(id) ? entrances[id] : GetEntranceLocation());

                    // This buff disappears immediately after killing the boss
                    DoRemoveAurasDueToSpellOnPlayers(eInstanceSpells::SpellDetermination);

                    _encounterTime = 0;

                    if (Creature* boss = GetCreature(id))
                        SendEncounterEnd(GetEncounterIDForBoss(boss), true);

                    if (instance->IsRaid())
                    {
                        // Bloodlust, Heroism, Temporal Displacement and Insanity debuffs are removed at the end of an encounter
                        DoRemoveAurasDueToSpellOnPlayers(eInstanceSpells::HunterInsanity);
                        DoRemoveAurasDueToSpellOnPlayers(eInstanceSpells::MageTemporalDisplacement);
                        DoRemoveAurasDueToSpellOnPlayers(eInstanceSpells::ShamanExhaustion);
                        DoRemoveAurasDueToSpellOnPlayers(eInstanceSpells::ShamanSated);

                        // Remove all cooldowns with a recovery time equal or superior than 3 minutes
                        DoRemoveSpellCooldownWithTimeOnPlayers(3 * TimeConstants::IN_MILLISECONDS * TimeConstants::MINUTE);
                        break;
                    }
                case FAIL:
                    if (!IsChallenge())
                        ResetCombatResurrections();
                    SendEncounterEnd();

                    // Now you have to fight for at least 3mins to get a stack.
                    // It was nerfed due to people intentionally reseting the boss to gain max stack to kill the boss faster.
                    if (_encounterTime && instance->IsLFR() && (time(nullptr) - _encounterTime) >= 3 * TimeConstants::MINUTE)
                        DoCastSpellOnPlayers(eInstanceSpells::SpellDetermination);

                    if (Creature* boss = GetCreature(id))
                        SendEncounterEnd(GetEncounterIDForBoss(boss), false);

                    // Remove all cooldowns with a recovery time equal or superior than 3 minutes
                    DoRemoveSpellCooldownWithTimeOnPlayers(3 * TimeConstants::IN_MILLISECONDS * TimeConstants::MINUTE);
                    break;
                default:
                    break;
            }

            bossInfo->state = state;
            if (dungeonEncounter)
                instance->UpdateInstanceLock({ dungeonEncounter, id, state });
        }

        for (uint32 type = 0; type < MAX_DOOR_TYPES; ++type)
            for (GuidSet::iterator i = bossInfo->door[type].begin(); i != bossInfo->door[type].end(); ++i)
                if (GameObject* door = instance->GetGameObject(*i))
                    UpdateDoorState(door);

        GuidSet minions = bossInfo->minion; // Copy to prevent iterator invalidation (minion might be unsummoned in UpdateMinionState)
        for (GuidSet::iterator i = minions.begin(); i != minions.end(); ++i)
            if (Creature* minion = instance->GetCreature(*i))
                UpdateMinionState(minion, state);

        UpdateSpawnGroups();
        return true;
    }
    return false;
}

bool InstanceScript::_SkipCheckRequiredBosses(Player const* player /*= nullptr*/) const
{
    return player && player->GetSession()->HasPermission(rbac::RBAC_PERM_SKIP_CHECK_INSTANCE_REQUIRED_BOSSES);
}

void InstanceScript::Create()
{
    for (size_t i = 0; i < bosses.size(); ++i)
        SetBossState(i, NOT_STARTED);
    UpdateSpawnGroups();
}

void InstanceScript::Load(char const* data)
{
    if (!data)
    {
        OUT_LOAD_INST_DATA_FAIL;
        return;
    }

    OUT_LOAD_INST_DATA(data);

    InstanceScriptDataReader reader(*this);
    if (reader.Load(data) == InstanceScriptDataReader::Result::Ok)
    {
        // in loot-based lockouts instance can be loaded with later boss marked as killed without preceding bosses
        // but we still need to have them alive
        for (uint32 i = 0; i < bosses.size(); ++i)
            if (bosses[i].state == DONE && !CheckRequiredBosses(i))
                bosses[i].state = NOT_STARTED;

        UpdateSpawnGroups();
        AfterDataLoad();
    }
    else
        OUT_LOAD_INST_DATA_FAIL;

    OUT_LOAD_INST_DATA_COMPLETE;
}

std::string InstanceScript::GetSaveData()
{
    OUT_SAVE_INST_DATA;

    InstanceScriptDataWriter writer(*this);

    writer.FillData();

    OUT_SAVE_INST_DATA_COMPLETE;

    return writer.GetString();
}

std::string InstanceScript::UpdateBossStateSaveData(std::string const& oldData, UpdateBossStateSaveDataEvent const& event)
{
    if (!instance->GetMapDifficulty()->IsUsingEncounterLocks())
        return GetSaveData();

    InstanceScriptDataWriter writer(*this);
    writer.FillDataFrom(oldData);
    writer.SetBossState(event);
    return writer.GetString();
}

std::string InstanceScript::UpdateAdditionalSaveData(std::string const& oldData, UpdateAdditionalSaveDataEvent const& event)
{
    if (!instance->GetMapDifficulty()->IsUsingEncounterLocks())
        return GetSaveData();

    InstanceScriptDataWriter writer(*this);
    writer.FillDataFrom(oldData);
    writer.SetAdditionalData(event);
    return writer.GetString();
}

Optional<uint32> InstanceScript::GetEntranceLocationForCompletedEncounters(uint32 completedEncountersMask) const
{
    if (!instance->GetMapDifficulty()->IsUsingEncounterLocks())
        return _entranceId;

    return ComputeEntranceLocationForCompletedEncounters(completedEncountersMask);
}

Optional<uint32> InstanceScript::ComputeEntranceLocationForCompletedEncounters(uint32 /*completedEncountersMask*/) const
{
    return { };
}

void InstanceScript::HandleGameObject(ObjectGuid guid, bool open, GameObject* go /*= nullptr*/)
{
    if (!go)
        go = instance->GetGameObject(guid);
    if (go)
        go->SetGoState(open ? GO_STATE_ACTIVE : GO_STATE_READY);
    else
        TC_LOG_DEBUG("scripts", "InstanceScript: HandleGameObject failed");
}

void InstanceScript::UpdateOperations(uint32 const diff)
{
    for (auto itr = timedDelayedOperations.begin(); itr != timedDelayedOperations.end(); itr++)
    {
        try
        {
            itr->first -= diff;

            if (itr->first < 0)
            {
                itr->second();
                itr->second = nullptr;
            }
        }
        catch (...)
        {
            itr = timedDelayedOperations.erase(itr);
        }
    }


    uint32 timedDelayedOperationCountToRemove = std::count_if(std::begin(timedDelayedOperations), std::end(timedDelayedOperations), [](const std::pair<int32, std::function<void()>> & pair) -> bool
    {
        return pair.second == nullptr;
    });

    for (uint32 i = 0; i < timedDelayedOperationCountToRemove; i++)
    {
        auto itr = std::find_if(std::begin(timedDelayedOperations), std::end(timedDelayedOperations), [](const std::pair<int32, std::function<void()>> & p_Pair) -> bool
        {
            return p_Pair.second == nullptr;
        });

        if (itr != std::end(timedDelayedOperations))
            timedDelayedOperations.erase(itr);
    }

    if (timedDelayedOperations.empty() && !emptyWarned)
    {
        emptyWarned = true;
        LastOperationCalled();
    }
}

void InstanceScript::DoUseDoorOrButton(ObjectGuid guid, uint32 withRestoreTime /*= 0*/, bool useAlternativeState /*= false*/)
{
    if (!guid)
        return;

    if (GameObject* go = instance->GetGameObject(guid))
    {
        if (go->GetGoType() == GAMEOBJECT_TYPE_DOOR || go->GetGoType() == GAMEOBJECT_TYPE_BUTTON)
        {
            if (go->getLootState() == GO_READY)
                go->UseDoorOrButton(withRestoreTime, useAlternativeState);
            else if (go->getLootState() == GO_ACTIVATED)
                go->ResetDoorOrButton();
        }
        else
            TC_LOG_ERROR("scripts", "InstanceScript: DoUseDoorOrButton can't use gameobject entry %u, because type is %u.", go->GetEntry(), go->GetGoType());
    }
    else
        TC_LOG_DEBUG("scripts", "InstanceScript: DoUseDoorOrButton failed");
}

void InstanceScript::DoCloseDoorOrButton(ObjectGuid guid)
{
    if (!guid)
        return;

    if (GameObject* go = instance->GetGameObject(guid))
    {
        if (go->GetGoType() == GAMEOBJECT_TYPE_DOOR || go->GetGoType() == GAMEOBJECT_TYPE_BUTTON)
        {
            if (go->getLootState() == GO_ACTIVATED)
                go->ResetDoorOrButton();
        }
        else
            TC_LOG_ERROR("scripts", "InstanceScript: DoCloseDoorOrButton can't use gameobject entry %u, because type is %u.", go->GetEntry(), go->GetGoType());
    }
    else
        TC_LOG_DEBUG("scripts", "InstanceScript: DoCloseDoorOrButton failed");
}

void InstanceScript::DoRespawnGameObject(ObjectGuid guid, Seconds timeToDespawn /*= 1min */)
{
    if (GameObject* go = instance->GetGameObject(guid))
    {
        switch (go->GetGoType())
        {
            case GAMEOBJECT_TYPE_DOOR:
            case GAMEOBJECT_TYPE_BUTTON:
            case GAMEOBJECT_TYPE_TRAP:
            case GAMEOBJECT_TYPE_FISHINGNODE:
                // not expect any of these should ever be handled
                TC_LOG_ERROR("scripts", "InstanceScript: DoRespawnGameObject can't respawn gameobject entry %u, because type is %u.", go->GetEntry(), go->GetGoType());
                return;
            default:
                break;
        }

        if (go->isSpawned())
            return;

        go->SetRespawnTime(timeToDespawn.count());
    }
    else
        TC_LOG_DEBUG("scripts", "InstanceScript: DoRespawnGameObject failed");
}

void InstanceScript::DoUpdateWorldState(int32 worldStateId, int32 value)
{
    sWorldStateMgr->SetValue(worldStateId, value, false, instance);
}

// Send Notify to all players in instance
void InstanceScript::DoSendNotifyToInstance(char const* format, ...)
{
    va_list ap;
    va_start(ap, format);
    char buff[1024];
    vsnprintf(buff, 1024, format, ap);
    va_end(ap);

    instance->DoOnPlayers([&buff](Player const* player)
    {
        player->GetSession()->SendNotification("%s", buff);
    });
}

// Update Achievement Criteria for all players in instance
void InstanceScript::DoUpdateCriteria(CriteriaType type, uint32 miscValue1 /*= 0*/, uint32 miscValue2 /*= 0*/, Unit* unit /*= nullptr*/)
{
    instance->DoOnPlayers([type, miscValue1, miscValue2, unit](Player* player)
    {
        player->UpdateCriteria(type, miscValue1, miscValue2, 0, unit);
    });
}

void InstanceScript::DoRemoveAurasDueToSpellOnPlayers(uint32 spell, bool includePets /*= false*/, bool includeControlled /*= false*/)
{
    instance->DoOnPlayers([this, spell, includePets, includeControlled](Player* player)
    {
        DoRemoveAurasDueToSpellOnPlayer(player, spell, includePets, includeControlled);
    });
}

void InstanceScript::DoRemoveAurasDueToSpellOnPlayer(Player* player, uint32 spell, bool includePets /*= false*/, bool includeControlled /*= false*/)
{
    if (!player)
        return;

    player->RemoveAurasDueToSpell(spell);

    if (!includePets)
        return;

    for (uint8 itr2 = 0; itr2 < MAX_SUMMON_SLOT; ++itr2)
    {
        ObjectGuid summonGUID = player->m_SummonSlot[itr2];
        if (!summonGUID.IsEmpty())
            if (Creature* summon = instance->GetCreature(summonGUID))
                summon->RemoveAurasDueToSpell(spell);
    }

    if (!includeControlled)
        return;

    for (auto itr2 = player->m_Controlled.begin(); itr2 != player->m_Controlled.end(); ++itr2)
    {
        if (Unit* controlled = *itr2)
            if (controlled->IsInWorld() && controlled->GetTypeId() == TYPEID_UNIT)
                controlled->RemoveAurasDueToSpell(spell);
    }
}

void InstanceScript::DoCastSpellOnPlayers(uint32 spell, bool includePets /*= false*/, bool includeControlled /*= false*/)
{
    instance->DoOnPlayers([this, spell, includePets, includeControlled](Player* player)
    {
        DoCastSpellOnPlayer(player, spell, includePets, includeControlled);
    });
}

void InstanceScript::DoCastSpellOnPlayer(Player* player, uint32 spell, bool includePets /*= false*/, bool includeControlled /*= false*/)
{
    if (!player)
        return;

    player->CastSpell(player, spell, true);

    if (!includePets)
        return;

    for (uint8 itr2 = 0; itr2 < MAX_SUMMON_SLOT; ++itr2)
    {
        ObjectGuid summonGUID = player->m_SummonSlot[itr2];
        if (!summonGUID.IsEmpty())
            if (Creature* summon = instance->GetCreature(summonGUID))
                summon->CastSpell(player, spell, true);
    }

    if (!includeControlled)
        return;

    for (auto itr2 = player->m_Controlled.begin(); itr2 != player->m_Controlled.end(); ++itr2)
    {
        if (Unit* controlled = *itr2)
            if (controlled->IsInWorld() && controlled->GetTypeId() == TYPEID_UNIT)
                controlled->CastSpell(player, spell, true);
    }
}

// Cast spell on all players in instance
void InstanceScript::DoPlayScenePackageIdOnPlayers(uint32 scenePackageId)
{
    Map::PlayerList const& PlayerList = instance->GetPlayers();

    if (!PlayerList.isEmpty())
        for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
            if (Player* player = i->GetSource())
                player->GetSceneMgr().PlaySceneByPackageId(scenePackageId, SceneFlag::None);
}

void InstanceScript::DoPlaySceneOnPlayers(uint32 sceneId)
{
    Map::PlayerList const& PlayerList = instance->GetPlayers();

    if (!PlayerList.isEmpty())
        for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
            if (Player* player = i->GetSource())
                player->GetSceneMgr().PlayScene(sceneId);
}

//Pop all player to the graveyard more near in the instance
void InstanceScript::RepopPlayersAtGraveyard()
{
    if (!this || !instance)
        return;

    Map::PlayerList const& PlayerList = instance->GetPlayers();

    if (!PlayerList.isEmpty())
        for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
            if (Player* player = i->GetSource())
                player->RepopAtGraveyard();
}

bool InstanceScript::ServerAllowsTwoSideGroups()
{
    return sWorld->getBoolConfig(CONFIG_ALLOW_TWO_SIDE_INTERACTION_GROUP);
}

CreatureGroup* InstanceScript::SummonCreatureGroup(uint32 creatureGroupID, std::list<TempSummon*>* list /*= nullptr*/)
{
    bool createTempList = !list;
    if (createTempList)
        list = new std::list<TempSummon*>;

    instance->SummonCreatureGroup(creatureGroupID, list);

    for (TempSummon* summon : *list)
        summonBySummonGroupIDs[creatureGroupID].push_back(summon->GetGUID());

    if (createTempList)
    {
        delete list;
        list = nullptr;
    }

    return GetCreatureGroup(creatureGroupID);
}

CreatureGroup* InstanceScript::GetCreatureGroup(uint32 creatureGroupID)
{
    for (ObjectGuid guid : summonBySummonGroupIDs[creatureGroupID])
        if (Creature* summon = instance->GetCreature(guid))
            return summon->GetFormation();

    return nullptr;
}

void InstanceScript::DespawnCreatureGroup(uint32 creatureGroupID)
{
    for (ObjectGuid guid : summonBySummonGroupIDs[creatureGroupID])
        if (Creature* summon = instance->GetCreature(guid))
            summon->DespawnOrUnsummon();

    summonBySummonGroupIDs.erase(creatureGroupID);
}
 
DungeonEncounterEntry const* InstanceScript::GetBossDungeonEncounter(uint32 id) const
{
    return id < bosses.size() ? bosses[id].GetDungeonEncounterForDifficulty(instance->GetDifficultyID()) : nullptr;
}

DungeonEncounterEntry const* InstanceScript::GetBossDungeonEncounter(Creature const* creature) const
{
    if (BossAI const* bossAi = dynamic_cast<BossAI const*>(creature->GetAI()))
        return GetBossDungeonEncounter(bossAi->GetBossId());

    return nullptr;
}

bool InstanceScript::CheckAchievementCriteriaMeet(uint32 criteria_id, Player const* /*source*/, Unit const* /*target*/ /*= nullptr*/, uint32 /*miscvalue1*/ /*= 0*/)
{
    TC_LOG_ERROR("misc", "Achievement system call InstanceScript::CheckAchievementCriteriaMeet but instance script for map %u not have implementation for achievement criteria %u",
        instance->GetId(), criteria_id);
    return false;
}

// Add aura on all players in instance
void InstanceScript::DoAddAuraOnPlayers(uint32 spell)
{
    Map::PlayerList const& PlayerList = instance->GetPlayers();

    if (!PlayerList.isEmpty())
        for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
            if (Player* player = i->GetSource())
                player->AddAura(spell, player);
}

void InstanceScript::DoRemoveSpellCooldownOnPlayers(uint32 spellID)
{
    Map::PlayerList const& playerList = instance->GetPlayers();

    if (!playerList.isEmpty())
    {
        for (Map::PlayerList::const_iterator iter = playerList.begin(); iter != playerList.end(); ++iter)
        {
            if (Player* player = iter->GetSource())
            {
                if (player->GetSpellHistory()->HasCooldown(spellID))
                    player->GetSpellHistory()->ResetCooldown(spellID, true);
            }
        }
    }
}

void InstanceScript::DoRemoveSpellCooldownWithTimeOnPlayers(uint32 minRecoveryTime)
{
    Map::PlayerList const& playerList = instance->GetPlayers();
    if (playerList.isEmpty())
        return;

    for (Map::PlayerList::const_iterator iter = playerList.begin(); iter != playerList.end(); ++iter)
    {
        if (Player* player = iter->GetSource())
            player->GetSpellHistory()->RemoveSpellCooldownsWithTime(minRecoveryTime);
    }
}

void InstanceScript::DoCombatStopOnPlayers()
{
    Map::PlayerList const& playerList = instance->GetPlayers();
    if (playerList.isEmpty())
        return;

    for (Map::PlayerList::const_iterator iter = playerList.begin(); iter != playerList.end(); ++iter)
    {
        if (Player* player = iter->GetSource())
        {
            if (!player->IsInCombat())
                continue;

            player->CombatStop();
        }
    }
}

void InstanceScript::DoPlayConversation(uint32 conversationId)
{
    Map::PlayerList const& playerList = instance->GetPlayers();
    if (!playerList.isEmpty())
        for (Map::PlayerList::const_iterator i = playerList.begin(); i != playerList.end(); ++i)
            if (Player* player = i->GetSource())
                player->PlayConversation(conversationId);
}

void InstanceScript::DoCompleteAchievement(uint32 achievement)
{
    AchievementEntry const* achievementEntry = sAchievementStore.LookupEntry(achievement);
    if (!achievementEntry)
    {
        TC_LOG_ERROR("scripts", "DoCompleteAchievement called for not existing achievement %u", achievement);
        return;
    }

    Map::PlayerList const& playerList = instance->GetPlayers();
    if (!playerList.isEmpty())
        for (Map::PlayerList::const_iterator i = playerList.begin(); i != playerList.end(); ++i)
            if (Player* player = i->GetSource())
                player->CompletedAchievement(achievementEntry);
}

bool InstanceScript::IsEncounterCompleted(uint32 dungeonEncounterId) const
{
    for (std::size_t i = 0; i < bosses.size(); ++i)
        for (std::size_t j = 0; j < bosses[i].DungeonEncounters.size(); ++j)
            if (bosses[i].DungeonEncounters[j] && bosses[i].DungeonEncounters[j]->ID == dungeonEncounterId)
                return bosses[i].state == DONE;

    return false;
}

bool InstanceScript::IsEncounterCompletedInMaskByBossId(uint32 completedEncountersMask, uint32 bossId) const
{
    if (DungeonEncounterEntry const* dungeonEncounter = GetBossDungeonEncounter(bossId))
        if (completedEncountersMask & (1 << dungeonEncounter->Bit))
            return bosses[bossId].state == DONE;

    return false;
}

void InstanceScript::SetEntranceLocation(uint32 worldSafeLocationId)
{
    _entranceId = worldSafeLocationId;
    _temporaryEntranceId = 0;
}

void InstanceScript::SendEncounterUnit(uint32 type, Unit* unit /*= nullptr*/, uint8 priority)
{
    switch (type)
    {
        case ENCOUNTER_FRAME_ENGAGE:                    // SMSG_INSTANCE_ENCOUNTER_ENGAGE_UNIT
        {
            if (!unit)
                return;

            WorldPackets::Instance::InstanceEncounterEngageUnit encounterEngageMessage;
            encounterEngageMessage.Unit = unit->GetGUID();
            encounterEngageMessage.TargetFramePriority = priority;
            instance->SendToPlayers(encounterEngageMessage.Write());
            break;
        }
        case ENCOUNTER_FRAME_DISENGAGE:                 // SMSG_INSTANCE_ENCOUNTER_DISENGAGE_UNIT
        {
            if (!unit)
                return;

            WorldPackets::Instance::InstanceEncounterDisengageUnit encounterDisengageMessage;
            encounterDisengageMessage.Unit = unit->GetGUID();
            instance->SendToPlayers(encounterDisengageMessage.Write());
            break;
        }
        case ENCOUNTER_FRAME_UPDATE_PRIORITY:           // SMSG_INSTANCE_ENCOUNTER_CHANGE_PRIORITY
        {
            if (!unit)
                return;

            WorldPackets::Instance::InstanceEncounterChangePriority encounterChangePriorityMessage;
            encounterChangePriorityMessage.Unit = unit->GetGUID();
            encounterChangePriorityMessage.TargetFramePriority = priority;
            instance->SendToPlayers(encounterChangePriorityMessage.Write());
            break;
        }
        default:
            break;
    }
}

void InstanceScript::SendEncounterStart(uint32 inCombatResCount /*= 0*/, uint32 maxInCombatResCount /*= 0*/, uint32 inCombatResChargeRecovery /*= 0*/, uint32 nextCombatResChargeTime /*= 0*/, bool inProgress /*= true*/)
{
    WorldPackets::Instance::InstanceEncounterStart encounterStartMessage;
    encounterStartMessage.InCombatResCount = inCombatResCount;
    encounterStartMessage.MaxInCombatResCount = maxInCombatResCount;
    encounterStartMessage.CombatResChargeRecovery = inCombatResChargeRecovery;
    encounterStartMessage.NextCombatResChargeTime = nextCombatResChargeTime;
    encounterStartMessage.InProgress = inProgress;

    instance->SendToPlayers(encounterStartMessage.Write());
}

void InstanceScript::SendEncounterEnd()
{
    WorldPackets::Instance::InstanceEncounterEnd encounterEndMessage;
    instance->SendToPlayers(encounterEndMessage.Write());
}

void InstanceScript::SendBossKillCredit(uint32 encounterId)
{
    WorldPackets::Instance::BossKill bossKillCreditMessage;
    bossKillCreditMessage.DungeonEncounterID = encounterId;

    instance->SendToPlayers(bossKillCreditMessage.Write());
}

void InstanceScript::UpdateEncounterState(EncounterCreditType type, uint32 creditEntry, Unit* /*source*/, Unit* unit /*= nullptr*/)
{
    DungeonEncounterList const* encounters = sObjectMgr->GetDungeonEncounterList(instance->GetId(), instance->GetDifficultyID());
    if (!encounters)
        return;

    uint32 encounterId = 0;
    bool findCustomDungeon = false;
    Map::PlayerList const& players = instance->GetPlayers();

    ObjectGuid groupGuid;
    if (unit)
    {
        if (Player* player = unit->ToPlayer())
            if (Group* group = player->GetGroup())
                groupGuid = group->GetGUID();
    }
    else if (players.begin() != players.end())
    {
        if (Player* player = players.begin()->GetSource())
            if (Group* group = player->GetGroup())
                groupGuid = group->GetGUID();
    }

    uint32 dungeonId = sLFGMgr->GetDungeon(groupGuid);
    bool isLFGEncounter = false;
    uint32 fullEncounterIndex = 0;
    if (unit)
    {
        //if (lfg::LfgReward const* reward = sLFGMgr->GetDungeonReward(dungeonId, unit->getLevel()))
        //{
        //    if (reward->encounterMask)
        //    {
        //        isLFGEncounter = true;
        //        fullEncounterIndex = reward->encounterMask;
        //    }
        //}
    }

    for (DungeonEncounterList::const_iterator iter = encounters->begin(); iter != encounters->end(); ++iter)
    {
        auto encounter = iter;
        uint32 completedEncounter = 1 << encounter->dbcEntry->Bit;
        if (encounter->creditType == type && encounter->creditEntry == creditEntry)
        {
            if (!isLFGEncounter || (completedEncounter & fullEncounterIndex))
                completedEncounters |= completedEncounter;

            encounterId = encounter->dbcEntry->ID;

            if (type == ENCOUNTER_CREDIT_KILL_CREATURE)
                SendBossKillCredit(encounterId);

            if (InstanceScenario* scenario = instance->ToInstanceMap()->GetInstanceScenario())
                if (players.begin() != players.end())
                    scenario->UpdateCriteria(CriteriaType::DefeatDungeonEncounter, encounter->dbcEntry->ID, 0, 0, nullptr, players.begin()->GetSource());

            if (encounter->dbcEntry->CompleteWorldStateID)
                DoUpdateWorldState(encounter->dbcEntry->CompleteWorldStateID, 1);

            if (encounter->lastEncounterDungeon && !isLFGEncounter)
            {
                dungeonId = encounter->lastEncounterDungeon;
                findCustomDungeon = true;
                //TC_LOG_DEBUG("lfg", "UpdateEncounterState: Instance %s (instanceId %u) completed encounter %s. Credit Dungeon: %u",
                //    instance->GetMapName(), instance->GetInstanceId(), encounter->dbcEntry->Name->Str[sWorld->GetDefaultDbcLocale()], dungeonId);
                break;
            }
        }

        if (!isLFGEncounter)
            fullEncounterIndex |= completedEncounter;
    }

    if (dungeonId && (fullEncounterIndex == completedEncounters || findCustomDungeon)) // For auto find dungeonId disable find last encounter from base, need
    {
        uint8 count = 0;
        Map::PlayerList const& players = instance->GetPlayers();
        for (Map::PlayerList::const_iterator i = players.begin(); i != players.end(); ++i)
        {
            if (Player* player = i->GetSource())
            {
                if (Group* grp = player->GetGroup())
                {
                    if (grp->isRaidGroup())
                        player->UpdateCriteria(CriteriaType::RunInstance, instance->GetMapDifficulty() ? instance->GetMapDifficulty()->MaxPlayers : 1);

                    //After update the criteria then finish the dungeon
                    count++;
                    if (count >= instance->GetPlayersCountExceptGMs())
                    {
                       //if (player)
                       //    if (auto guild = player->GetGuild())
                       //        if (grp->IsGuildGroup())
                       //            guild->AddGuildNews(GUILD_NEWS_DUNGEON_ENCOUNTER, player->GetGUID(), 0, encounterId);

                        if (grp->isLFGGroup())
                        {
                            sLFGMgr->FinishDungeon(grp->GetGUID(), dungeonId, instance);
                            return;
                        }
                    }
                }
            }
        }
    }

    //if (!groupGuid.IsEmpty())
    //    sLFGMgr->SetCompletedMask(groupGuid, completedEncounters);
}

void InstanceScript::UpdateEncounterStateForKilledCreature(uint32 creatureId, Unit* source, Unit* player /*= nullptr*/)
{
    UpdateEncounterState(ENCOUNTER_CREDIT_KILL_CREATURE, creatureId, source, player);
}

void InstanceScript::UpdateEncounterStateForSpellCast(uint32 spellId, Unit* source, Unit* player /*= nullptr*/)
{
    UpdateEncounterState(ENCOUNTER_CREDIT_CAST_SPELL, spellId, source, player);
}

void InstanceScript::SetCompletedEncountersMask(uint32 newMask)
{
    completedEncounters = newMask;

    if (DungeonEncounterList const* encounters = sObjectMgr->GetDungeonEncounterList(instance->GetId(), instance->GetDifficultyID()))
        for (DungeonEncounter const& encounter : *encounters)
            if (completedEncounters & (1 << encounter.dbcEntry->Bit) && encounter.dbcEntry->CompleteWorldStateID)
                DoUpdateWorldState(encounter.dbcEntry->CompleteWorldStateID, 1);
}

void InstanceScript::UpdatePhasing()
{
    instance->DoOnPlayers([](Player const* player)
    {
        PhasingHandler::SendToPlayer(player);
    });
}

char const* InstanceScript::GetBossStateName(uint8 state)
{
    return EnumUtils::ToConstant(EncounterState(state));
}

void InstanceScript::UpdateCombatResurrection(uint32 diff)
{
    if (!_combatResurrectionTimerStarted)
        return;

    if (_combatResurrectionTimer <= diff)
        AddCombatResurrectionCharge();
    else
        _combatResurrectionTimer -= diff;
}

void InstanceScript::InitializeCombatResurrections(uint8 charges /*= 1*/, uint32 interval /*= 0*/)
{
    _combatResurrectionCharges = charges;
    if (!interval)
        return;

    _combatResurrectionTimer = interval;
    _combatResurrectionTimerStarted = true;
}

void InstanceScript::AddCombatResurrectionCharge()
{
    ++_combatResurrectionCharges;
    _combatResurrectionTimer = GetCombatResurrectionChargeInterval();

    WorldPackets::Instance::InstanceEncounterGainCombatResurrectionCharge gainCombatResurrectionCharge;
    gainCombatResurrectionCharge.InCombatResCount = _combatResurrectionCharges;
    gainCombatResurrectionCharge.CombatResChargeRecovery = _combatResurrectionTimer;
    instance->SendToPlayers(gainCombatResurrectionCharge.Write());
}

void InstanceScript::UseCombatResurrection()
{
    --_combatResurrectionCharges;

    instance->SendToPlayers(WorldPackets::Instance::InstanceEncounterInCombatResurrection().Write());
}

void InstanceScript::ResetCombatResurrections()
{
    _combatResurrectionCharges = 0;
    _combatResurrectionTimer = 0;
    _combatResurrectionTimerStarted = false;
}

uint32 InstanceScript::GetCombatResurrectionChargeInterval() const
{
    uint32 interval = 0;
    if (uint32 playerCount = instance->GetPlayers().getSize())
        interval = 90 * MINUTE * IN_MILLISECONDS / playerCount;

    return interval;
}

PersistentInstanceScriptValueBase::PersistentInstanceScriptValueBase(InstanceScript& instance, char const* name, std::variant<int64, double> value)
    : _instance(instance), _name(name), _value(std::move(value))
{
    _instance.RegisterPersistentScriptValue(this);
}

PersistentInstanceScriptValueBase::~PersistentInstanceScriptValueBase() = default;

void PersistentInstanceScriptValueBase::NotifyValueChanged()
{
    _instance.instance->UpdateInstanceLock(CreateEvent());
}

bool InstanceHasScript(WorldObject const* obj, char const* scriptName)
{
    if (InstanceMap* instance = obj->GetMap()->ToInstanceMap())
        return instance->GetScriptName() == scriptName;

    return false;
}

void InstanceScript::SendCompleteGuildChallenge(uint32 id)
{
    InstanceMap::PlayerList const& playersMap = instance->GetPlayers();
    for (InstanceMap::PlayerList::const_iterator itr = playersMap.begin(); itr != playersMap.end(); ++itr)
    {
        if (Player* player = itr->GetSource())
        {
            //if (player->GetGroup() && player->GetGroup()->CanRecieveGuildChallengeCredit())
            //{
            //    if (Guild* guild = player->GetGuild())
            //    {
            //        if (instance->IsRaid())
            //            guild->CompleteGuildChallenge(GuildChallengeType::ChallengeRaid, player);
            //        else if (instance->IsDungeon() && id == (bosses.size() - 1))
            //            guild->CompleteGuildChallenge(GuildChallengeType::ChallengeDungeon, player);
            //        break;
            //    }
            //}
        }
    }
}

void InstanceScript::BuildPlayerDatas(WorldPackets::Instance::EncounterStart& packet)
{
    Map::PlayerList const& playerList = instance->GetPlayers();
    if (playerList.isEmpty())
        return;

    uint8 count = 0;

    for (Map::PlayerList::const_iterator iter = playerList.begin(); iter != playerList.end(); ++iter)
    {
        if (Player* player = iter->GetSource())
        {
            if (!player->IsInWorld())
                continue;

            packet.PlayerDatas[count].PlayerGuid = player->GetGUID();

            for (uint8 i = 0; i < MAX_STATS; ++i)
                packet.PlayerDatas[count].Stats.push_back(player->GetStat(Stats(i)));

            for (uint32 rating = 0; rating < MAX_COMBAT_RATING; ++rating)
                packet.PlayerDatas[count].CombatRatings.push_back(player->GetRatingBonusValue(CombatRating(rating)));

            uint32 secondCount = 0;
            Unit::AuraApplicationMap& itsAuras = player->GetAppliedAuras();
            for (Unit::AuraApplicationMap::iterator i = itsAuras.begin(); i != itsAuras.end();)
            {
                Aura const* aura = i->second->GetBase();
                packet.PlayerDatas[count].AuraInfos[secondCount].CasterGuid = aura->GetCasterGUID();
                packet.PlayerDatas[count].AuraInfos[secondCount].SpellID = aura->GetId();
                secondCount++;
            }

            packet.PlayerDatas[count].SpecID = player->GetSpecializationId();

            // @TODO: NEW TALENTS
          //PlayerTalentMap const* talents = player->GetTalentMap(player->GetActiveTalentGroup());
          //for (PlayerTalentMap::value_type const& v : *talents)
          //{
          //    if (v.second.state != PLAYERSPELL_REMOVED)
          //        packet.PlayerDatas[count].Talents.push_back(v.first);
          //}
          //
          //PlayerPvpTalentMap const& pvpTalents = player->GetPvpTalentMap(player->GetActiveTalentGroup());
          //for (std::size_t i = 0; i < pvpTalents.size(); ++i)
          //    packet.PlayerDatas[count].PvpTalents[i] = pvpTalents[i];

            //ToDo send Azerite Power Data

            secondCount = 0;
            for (EquipmentSlots i = EQUIPMENT_SLOT_HEAD; i < EQUIPMENT_SLOT_TABARD; i = (EquipmentSlots)(int(i) + 1))
            {
                if (i == EQUIPMENT_SLOT_BODY) // skip shirt
                    continue;
                if (i == EQUIPMENT_SLOT_RANGED) // ranged slot was removed in MOP
                    continue;

                if (Item* item = player->GetEquippedItem(i))
                {
                    packet.PlayerDatas[count].EncounterItemInfos[secondCount].ItemID = item->GetEntry();
                    packet.PlayerDatas[count].EncounterItemInfos[secondCount].ItemLevel = item->GetItemLevel(player);
                    packet.PlayerDatas[count].EncounterItemInfos[secondCount].ItemBonusListIDs.reserve(item->m_itemData->Bonuses->BonusListIDs.size());
                    for (int32 bonusId : item->m_itemData->Bonuses->BonusListIDs)
                        packet.PlayerDatas[count].EncounterItemInfos[secondCount].ItemBonusListIDs.emplace_back(bonusId);

                    for (uint32 enchant_slot = PERM_ENCHANTMENT_SLOT; enchant_slot < MAX_ENCHANTMENT_SLOT; ++enchant_slot)
                        packet.PlayerDatas[count].EncounterItemInfos[secondCount].EnchantmentIDs.push_back(item->GetEnchantmentId(EnchantmentSlot(enchant_slot)));

                    //ToDo send Gem Data
                    //for (ItemDynamicFieldGems const& gemData : item->GetGems())
                    //{

                    //}

                    secondCount++;
                }
            }
        }
    }
}

void InstanceScript::SendEncounterStart(uint32 encounterID)
{
    if (!encounterID)
        return;

    WorldPackets::Instance::EncounterStart encounterStar;
    encounterStar.EncounterID = encounterID;
    encounterStar.DifficultyID = instance->GetDifficultyID();
    encounterStar.GroupSize = instance->GetPlayers().getSize();
    //BuildPlayerDatas(encounterStar); Why blizard sent in all sniff 0 in this struct???
    instance->SendToPlayers(encounterStar.Write());
}

void InstanceScript::SendEncounterEnd(uint32 encounterID, bool success)
{
    if (!encounterID)
        return;

    WorldPackets::Instance::EncounterEnd encounterEnd;
    encounterEnd.EncounterID = encounterID;
    encounterEnd.DifficultyID = instance->GetDifficultyID();
    encounterEnd.GroupSize = instance->GetPlayers().getSize();
    encounterEnd.Success = success;
    instance->SendToPlayers(encounterEnd.Write());
}

uint32 InstanceScript::GetEncounterIDForBoss(Creature* boss) const
{
    if (!boss)
        return 0;

    DungeonEncounterList const* encounters = sObjectMgr->GetDungeonEncounterList(instance->GetId(), instance->GetDifficultyID());
    if (!encounters || encounters->empty())
        return 0;

    for (DungeonEncounterList::const_iterator iter = encounters->begin(); iter != encounters->end(); ++iter)
    {
        if (iter->creditEntry == boss->GetEntry())
            return iter->dbcEntry->ID;
    }

    return 0;
}

void InstanceScript::AddToDamageManager(Creature* creature, uint8 pullNum)
{
    if (!creature || !creature->IsAlive())
        return;

    SetPullDamageManager(creature->GetGUID(), pullNum);

    DamageManager manager;
    manager.entry = creature->GetEntry();
    manager.creature = creature;
    manager.guid = creature->GetGUID();

    damageManager[pullNum].push_back(manager);
    initDamageManager = true;
}

bool InstanceScript::CheckDamageManager()
{
    return initDamageManager;
}

void InstanceScript::UpdateDamageManager(ObjectGuid caller, int32 damage, bool heal)
{
    if (!damage)
        return;

    int8 pullNum = GetPullDamageManager(caller);
    if (pullNum < 0)
        return;

    DamageManagerMap::const_iterator itr = damageManager.find(pullNum);
    if (itr == damageManager.end())
        return;

    std::vector<DamageManager> const* manager = &itr->second;
    if (manager->empty())
        return;

    for (auto const& itr2 : *manager)
    {
        // Creature* pull = itr->creature; // If crashed comment this
        if (Creature* pull = instance->GetCreature(itr2.guid)) // If crashed uncomment this
        {
            if (!pull->IsAlive() || itr2.guid == caller)
                continue;

            if (!heal && damage >= pull->GetHealth())
                pull->Kill(pull, pull, true);
            else
                pull->SetHealth(pull->GetHealth() - damage);
        }
    }
}

void InstanceScript::SetPullDamageManager(ObjectGuid guid, uint8 pullId)
{
    pullDamageManager[guid] = pullId;
}

int8 InstanceScript::GetPullDamageManager(ObjectGuid guid) const
{
    if (pullDamageManager.empty())
        return -1;

    auto itr = pullDamageManager.find(guid);
    if (itr == pullDamageManager.end())
        return -1;

    return itr->second;
}

void InstanceScript::ResetChallengeMode(Player* player)
{
    if (!player || !player->GetGroup())
        if (_challenge)
            _challenge->ResetGo();

    instance->m_respawnChallenge = time(nullptr); // For respawn all mobs  
    RepopPlayersAtGraveyard();    
    //CreateChallenge(player);
}

void InstanceScript::AddChallengeModeChest(ObjectGuid chestGuid)
{
    _challengeChest = chestGuid;
}

void InstanceScript::AddChallengeModeDoor(ObjectGuid doorGuid)
{
    _challengeDoorGuid = doorGuid;
}

void InstanceScript::AddChallengeModeOrb(ObjectGuid orbGuid)
{
    _challengeOrbGuid = orbGuid;
}

void InstanceScript::SetChallenge(Challenge* challenge)
{
    _challenge = challenge;
}

Challenge* InstanceScript::GetChallenge() const
{
    return _challenge;
}

bool InstanceScript::IsChallenge() const
{
    return _challenge != nullptr;
}

// Redirect query to challenge
void InstanceScript::OnCreatureCreateForScript(Creature* creature)
{
    if (_challenge)
        _challenge->OnCreatureCreateForScript(creature);
}

void InstanceScript::OnCreatureRemoveForScript(Creature* creature)
{
    if (_challenge)
        _challenge->OnCreatureRemoveForScript(creature);
}

void InstanceScript::OnCreatureUpdateDifficulty(Creature* creature)
{
    if (_challenge)
        _challenge->OnCreatureUpdateDifficulty(creature);
}

void InstanceScript::EnterCombatForScript(Creature* creature, Unit* enemy)
{
    if (_challenge)
        _challenge->EnterCombatForScript(creature, enemy);
}

void InstanceScript::CreatureDiesForScript(Creature* creature, Unit* killer)
{
    if (_challenge)
        _challenge->CreatureDiesForScript(creature, killer);
}

void InstanceScript::OnPlayerEnterForScript(Player* player)
{
    if (_challenge)
        _challenge->OnPlayerEnterForScript(player);
}

void InstanceScript::OnPlayerLeaveForScript(Player* player)
{
    // just incase
    player->RemoveAura(SPELL_CHALLENGER_BURDEN);
    if (_challenge)
        _challenge->OnPlayerLeaveForScript(player);
}

void InstanceScript::OnPlayerDiesForScript(Player* player)
{
    if (_challenge)
        _challenge->OnPlayerDiesForScript(player);
}

void InstanceScript::OnUnitCharmed(Unit* unit, Unit* charmer)
{
    if (_challenge)
        _challenge->OnUnitCharmed(unit, charmer);
}

void InstanceScript::OnUnitRemoveCharmed(Unit* unit, Unit* charmer)
{
    if (_challenge)
        _challenge->OnUnitRemoveCharmed(unit, charmer);
}

void InstanceScript::OnGameObjectCreateForScript(GameObject* go)
{
    if (_challenge)
        _challenge->OnGameObjectCreateForScript(go);

    if (sChallengeModeMgr->IsChest(go->GetEntry()))    
        AddChallengeModeChest(go->GetGUID());

    if (sChallengeModeMgr->IsDoor(go->GetEntry()))    
        AddChallengeModeDoor(go->GetGUID());     

    if (go->GetEntry() == ChallengeModeOrb)
        AddChallengeModeOrb(go->GetGUID());
}

void InstanceScript::OnGameObjectRemoveForScript(GameObject* go)
{
    if (_challenge)
        _challenge->OnGameObjectRemoveForScript(go);
}

void InstanceScript::BroadcastPacket(WorldPacket const* data) const
{
    if (!this || !instance)
        return;

    instance->DoOnPlayers([data](Player* player)
    {
        player->SendDirectMessage(data);
    });
}

void InstanceScript::CreateChallenge(Player* player, MythicKeystoneInfo* keystoneInfo)
{
    InstanceMap* instanceMap = instance->ToInstanceMap();
    uint32 instanceID = instanceMap->GetInstanceId();

    if (!instanceMap || !instanceID)
        return;

    MapChallengeModeEntry const* m_challengeEntry = keystoneInfo ? keystoneInfo->challengeEntry : nullptr;
    if (!m_challengeEntry)
        return;

    uint32 scenarioId = 0;
    if (ScenarioDBData const* scenarioData = sScenarioMgr->GetScenarioOnMap(player->GetMap()->GetId(), DIFFICULTY_MYTHIC_KEYSTONE))
    {
        if (player->GetTeamId() == TEAM_ALLIANCE)
            scenarioId = scenarioData->Scenario_A;
        else
            scenarioId = scenarioData->Scenario_H;
    }

    bool canChallengeWithTeeming = false;

    // todo
    if (ScenarioData const* scenarioData = sScenarioMgr->GetScenarioData(scenarioId, player->GetTeamId(), sChallengeModeMgr->IsTeemingAffixInRotation() && canChallengeWithTeeming))
        instanceMap->SetInstanceScenario(new InstanceScenario(instanceMap, scenarioData));

    Scenario* scenario = instanceMap->GetInstanceScenario();
    if (!scenario)
        return;

    _challenge = new Challenge(instanceMap, player, scenario, keystoneInfo);

    if (!_challenge->CanRun())
    {
        delete _challenge;
        return;
    }

    // Remove all cooldowns with a recovery time equal or superior than 2 minutes
    DoRemoveSpellCooldownWithTimeOnPlayers(2 * TimeConstants::IN_MILLISECONDS * TimeConstants::MINUTE);
    SetChallenge(_challenge);
}
