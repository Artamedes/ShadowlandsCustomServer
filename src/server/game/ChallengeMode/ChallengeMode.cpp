/*
 * Copyright (C) 2008-2020 TrinityCore <http://www.trinitycore.org/>
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

#include "CellImpl.h"
#include "ChallengeMode.h"
#include "ChallengeModeMgr.h"
#include "ChallengeModePackets.h"
#include "Chat.h"
#include "DatabaseEnv.h"
#include "DB2Stores.h"
#include "GameTables.h"
#include "GridNotifiers.h"
#include "GridNotifiersImpl.h"
#include "GroupMgr.h"
#include "Guild.h"
#include "InstancePackets.h"
#include "Item.h"
#include "Map.h"
#include "MiscPackets.h"
#include "MotionMaster.h"
#include "ObjectMgr.h"
#include "WorldStatePackets.h"
#include "ObjectAccessor.h"
#include "TemporarySummon.h"
#include "PlayerChallenge.h"
#include "CustomObjectMgr.h"

Challenge::Challenge(InstanceMap* map, Player* player, Scenario* scenario, MythicKeystoneInfo* mythicKeystone)
    : InstanceScript(map), _instanceScript(map->GetInstanceScript()),
    _challengeLevel(mythicKeystone->Level), _challengeEntry(mythicKeystone->challengeEntry),
    _isKeyDepleted(false), _scenario(scenario)
{
    _checkStart = true;
    _canRun = true;
    _keyOwner = player->GetGUID();
    _challengeTimer = 0;
    _affixQuakingTimer = 0;
    _deathCount = 0;
    _complete = false;
    _run = false;
    _hordeSpawn = player->IsInHorde();
    m_itemGuid = mythicKeystone->KeystoneGUID;

    ASSERT(map);
    _map = map;
    _mapID = _map->GetId();

    _affixes.fill(0);
    if (_challengeLevel > MYTHIC_LEVEL_1)
        _affixes[0] = mythicKeystone->Affix;
    if (_challengeLevel > MYTHIC_LEVEL_3)
        _affixes[1] = mythicKeystone->Affix1;
    if (_challengeLevel > MYTHIC_LEVEL_6)
        _affixes[2] = mythicKeystone->Affix2;
    if (_challengeLevel > MYTHIC_LEVEL_9)
        _affixes[3] = mythicKeystone->Affix3;

    Group* group = player->GetGroup();
    if (group)
    {
        _groupGUID = group->GetGUID();

        for (GroupReference* itr = group->GetFirstMember(); itr != nullptr; itr = itr->next())
            if (Player* member = itr->GetSource())
                _challengers.insert(member->GetGUID());
    }

    if (!_challengeEntry)
    {
        ChatHandler(player->GetSession()).PSendSysMessage("Error: Is not a challenge map.");
        _canRun = false;
        return;
    }

    _challengers.insert(_keyOwner);

    _rewardLevel = CHALLENGE_NOT_IN_TIMER;

    for (auto const& affix : _affixes)
        _affixesTest.set(affix);

    for (uint8 i = 0; i < CHALLENGE_TIMER_LEVEL_3; i++)
        _chestTimers[i] = _challengeEntry->CriteriaCount[i];

    sCustomObjectMgr->SetChallengeLevelInfoIfNeed(mythicKeystone, _challengeLevelInfo);
}

Challenge::~Challenge()
{
    if (InstanceScript* script = GetInstanceScript())
        script->SetChallenge(nullptr);

    _instanceScript = nullptr;
}

void Challenge::OnPlayerEnterForScript(Player* player)
{
    if (!player)
        return;

    player->CastSpell(player, SPELL_CHALLENGER_BURDEN, true);

    m_Functions.AddFunction([player, this]() -> void
    {
        if (IsRunning() && !IsComplete())
        {
            SendChallengeModeStart(player);
            SendStartElapsedTimer(player);
        }
    }, m_Functions.CalculateTime(500));  
}

void Challenge::OnPlayerLeaveForScript(Player* player)
{
    if (!player)
        return;

    Player* keyOwner = ObjectAccessor::FindPlayer(_keyOwner);
    if (keyOwner && player == keyOwner)
    {
        if (auto playerChallenge = keyOwner->GetPlayerChallenge())
        {
            if (auto keyInfo = playerChallenge->GetKeystoneInfo(m_itemGuid))
            {
                keyInfo->InstanceID = 0;
                keyInfo->needUpdate = true;
            }
        }
    }

    player->SetDungeonDifficultyID(DIFFICULTY_MYTHIC);
    player->SendDungeonDifficulty();
    player->RemoveAura(SPELL_CHALLENGER_BURDEN);
}

void Challenge::OnPlayerDiesForScript(Player* /*player*/)
{
    ++_deathCount;
    ModChallengeTimer();

    SendStartElapsedTimer();

    WorldPackets::ChallengeMode::UpdateDeathCount packet;
    packet.DeathCount = _deathCount;
    BroadcastPacket(packet.Write());
}

void Challenge::OnCreatureCreateForScript(Creature* creature)
{
    if (!creature || creature->IsTrigger() || creature->IsControlledByPlayer())
        return;

    Unit* owner = creature->GetAnyOwner();
    if (owner && owner->IsPlayer())
        return;

    creature->AddAura(SPELL_CHALLENGER_MIGHT, creature);
}

void Challenge::OnCreatureUpdateDifficulty(Creature* creature)
{
    if (!creature || creature->IsTrigger() || creature->IsControlledByPlayer())
        return;

    Unit* owner = creature->GetAnyOwner();
    if (owner && owner->IsPlayer())
        return;

    creature->AddAura(SPELL_CHALLENGER_MIGHT, creature);

    if (!creature->IsDungeonBoss())
    {
        if (HasAffix(Infested) && !creature->IsSummon() && roll_chance_f(30.0f)) // Only for real creature summon copy
        {
            std::list<Creature*> creatures;
            Trinity::UnitAuraCheck check(true, SPELL_CHALLENGER_SIMBIOTE_OF_GHUUN);
            Trinity::CreatureListSearcher<Trinity::UnitAuraCheck> searcher(creature, creatures, check);
            Cell::VisitAllObjects(creature, searcher, 20.0f);

            if(creatures.empty())
                creature->CastSpell(creature, SPELL_CHALLENGER_SIMBIOTE_OF_GHUUN, true);
        }            
    }       
}

void Challenge::OnCreatureRemoveForScript(Creature* /*creature*/) { }

void Challenge::EnterCombatForScript(Creature* creature, Unit* /*enemy*/)
{
    if (!creature || creature->IsTrigger() || creature->IsControlledByPlayer())
        return;

    Unit* owner = creature->GetAnyOwner();
    if (owner && owner->IsPlayer())
        return;

    if (!creature->HasAura(SPELL_CHALLENGER_MIGHT))
        creature->AddAura(SPELL_CHALLENGER_MIGHT, creature);
}

void Challenge::CreatureDiesForScript(Creature* creature, Unit* killer)
{
    if (!creature || !killer || !killer->IsPlayer() || creature->IsTrigger() || creature->isAnySummons() || creature->IsControlledByPlayer() || creature->IsDungeonBoss())
        return;

    if (creature->IsOnVehicle())
        return;

    Unit* owner = creature->GetAnyOwner();
    if (owner && owner->IsPlayer())
        return;

    if (creature->GetCreatureType() != CREATURE_TYPE_CRITTER)
    {
        if (HasAffix(Affixes::Bolstering))
            creature->CastSpell(creature, SPELL_CHALLENGER_BOLSTERING, true);

        if (HasAffix(Affixes::Sanguine))
            creature->CastSpell(creature, SPELL_CHALLENGER_SANGUINE, true);

        if (HasAffix(Affixes::Bursting))
            creature->CastSpell(creature, SPELL_CHALLENGER_BURSTING, true);
    }

    if (HasAffix(Affixes::Infested) && creature->HasAura(SPELL_CHALLENGER_SIMBIOTE_OF_GHUUN))
    {
        std::list<Creature*> creatures;
       // creature->GetCreatureListInGrid(creatures, 500.0f);
        if (!creatures.empty())
        {
            creatures.remove_if([creature](Creature* object) -> bool
            {
                if (object == nullptr)
                    return true;

                if (object == creature)
                    return true;

                if (!creature->IsValidAssistTarget(object))
                    return true;

                if (object->IsTrigger() || object->IsControlledByPlayer() || !object->IsHostileToPlayers() || object->GetCreatureType() == CREATURE_TYPE_CRITTER)
                    return true;

                if (object->IsDungeonBoss())
                    return true;

                if (object->isAnySummons())
                    return true;

                if (object->HasAura(SPELL_CHALLENGER_SIMBIOTE_OF_GHUUN))
                    return true;                

                return false;
            });

            if (!creatures.empty())
            {
                creatures.sort(Trinity::ObjectDistanceOrderPred(creature));
                Creature* creatureSelected = creatures.front();
                
                for (uint8 i = 0; i < 2; i++)
                {
                    if (auto spawn = creature->SummonCreature(NPC_SPAWN_OF_GHUUN, creature->GetRandomNearPosition(2.0f), TEMPSUMMON_MANUAL_DESPAWN))
                    {
                        spawn->SetReactState(REACT_PASSIVE);
                        m_Functions.AddFunction([spawn, creatureSelected]() -> void
                        {
                            if (!spawn || !creatureSelected)
                                return;

                            spawn->FollowTarget(creatureSelected);
                            spawn->GetAI()->SetGUID(creatureSelected->GetGUID());

                        }, m_Functions.CalculateTime(3.5f * IN_MILLISECONDS));
                    }
                }
            }
        }
    }    
}

void Challenge::OnGameObjectCreateForScript(GameObject* go)
{
}

void Challenge::OnGameObjectRemoveForScript(GameObject* go)
{
}

void Challenge::OnUnitCharmed(Unit* unit, Unit* /*charmer*/)
{
    if (!unit || !unit->ToCreature())
        return;

    unit->RemoveAura(SPELL_CHALLENGER_BOLSTERING);
    unit->RemoveAura(SPELL_CHALLENGER_RAGING);
    unit->RemoveAura(SPELL_CHALLENGER_MIGHT);
}

void Challenge::OnUnitRemoveCharmed(Unit* unit, Unit* /*charmer*/)
{
    if (!unit || !unit->ToCreature())
        return;

    unit->AddAura(SPELL_CHALLENGER_MIGHT, unit);
}

void Challenge::Update(uint32 diff)
{
    m_Functions.Update(diff);

    if (IsComplete()) // Stop update if complete
        return;

    if (!IsRunning() && CanCheckStart())
    {
        if (CanStart())
        {
            Start();
            SummonGobject(true);
        }
        return;
    }

    _challengeTimer += diff;

    if (_affixQuakingTimer)
    {
        if (_affixQuakingTimer <= diff)
        {
            _map->DoOnPlayers([&](Player* plr)
            {
                if (plr->IsInWorld() && !plr->HasAura(SPELL_CHALLENGER_QUAKE) && !plr->HasUnitFlag2(UNIT_FLAG2_NO_ACTIONS) && !plr->IsOnVehicle())
                    plr->AddAura(SPELL_CHALLENGER_QUAKE, plr);
            });
            _affixQuakingTimer = 20 * IN_MILLISECONDS;
        }
        else
            _affixQuakingTimer -= diff;
    }      

    if (!_isKeyDepleted && GetChallengeTimer() > (uint32)_challengeEntry->CriteriaCount[0])
    {
        _isKeyDepleted = true;

        if (Group* group = sGroupMgr->GetGroupByGUID(_groupGUID))
        {
            group->SetDungeonDifficultyID(DIFFICULTY_MYTHIC);
        }

        Item* keystone = nullptr;
        Player* keyOwner = ObjectAccessor::FindPlayer(_keyOwner);
        if (keyOwner)
            keystone = keyOwner->GetItemByGuid(m_itemGuid);

        if (keystone)
            keyOwner->ChallengeKeyCharded(keystone, _challengeLevel);
        else
        {
            if (keyOwner = ObjectAccessor::FindPlayer(_keyOwner))
            {
                if (keystone = keyOwner->GetItemByGuid(m_itemGuid))
                    keyOwner->ChallengeKeyCharded(keystone, _challengeLevel);
                else
                    CharacterDatabase.PExecute("UPDATE challenge_key SET KeyIsCharded = 0, InstanceID = 0 WHERE guid = %u and itemid = %u", _keyOwner.GetCounter(), m_itemGuid.GetCounter());
            }
            else
                CharacterDatabase.PExecute("UPDATE challenge_key SET KeyIsCharded = 0, InstanceID = 0 WHERE guid = %u and itemid = %u", _keyOwner.GetCounter(), m_itemGuid.GetCounter());
        }
    }
}

bool Challenge::CanStart()
{
    if (IsRunning())
        return true;

    return _map->GetPlayerCount() == _challengers.size(); // wait when group complete
}

void Challenge::Start()
{
    if (!CanRun())
        return;

    Player* keyOwner = ObjectAccessor::FindPlayer(_keyOwner);
    if (!keyOwner)
        return;

    Item* keystone = keyOwner->GetItemByGuid(m_itemGuid);
    if (!keystone)
        return;

    if (auto playerChallenge = keyOwner->GetPlayerChallenge())
    {
        if (auto keyInfo = playerChallenge->GetKeystoneInfo(keystone))
        {
            keyInfo->InstanceID = keyOwner->GetInstanceId();
            keyInfo->needUpdate = true;
        }
    }

    _isKeyDepleted = false;

    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
    float o = 0.0f;

    if(!sChallengeModeMgr->GetStartPosition(keyOwner->GetInstanceScript(), x, y, z, o, _keyOwner))
        return;

    _map->DoOnPlayers([&](Player* player)
    {
         player->TeleportTo(_map->GetId(), x, y, z, o);
         _scenario->SendScenarioState(player);
    });

    SendChallengeInstanceEncounterStart();
    BroadcastPacket(WorldPackets::ChallengeMode::Reset(_mapID).Write());
    SendStartTimer();
    SendChallengeModeStart();    

    if (InstanceScript* script = GetInstanceScript())
    {
        if (GameObject* challengeOrb = _map->GetGameObject(script->GetChallengeModeOrb()))
        {
            challengeOrb->SetGoState(GO_STATE_ACTIVE);
            challengeOrb->SetFlag(GO_FLAG_NODESPAWN);
        }
    }

    m_Functions.AddFunction([this]() -> void
    {
        if (!this)
            return;

        _challengeTimer = 0;

        SendStartElapsedTimer();

        if (InstanceScript* script = GetInstanceScript())
        {
            if (GameObject* challengeDoor = _map->GetGameObject(script->GetChallengeModeDoor()))
                challengeDoor->Delete();

            if (GameObject* chest = _map->GetGameObject(script->GetChallengeModeChest()))
                chest->Delete();

            script->OnChallengeStart();
        }

        _run = true;

    }, m_Functions.CalculateTime(10 * IN_MILLISECONDS));

    _checkStart = false;

    if (HasAffix(Affixes::Quaking))
        _affixQuakingTimer = 20 * IN_MILLISECONDS;
}

void Challenge::Complete()
{
    if (IsComplete())
        return;

    _complete = true;

    Player* keyOwner = ObjectAccessor::FindPlayer(_keyOwner);
    Item* keystone = nullptr;
    if (keyOwner)
        keystone = keyOwner->GetItemByGuid(m_itemGuid);

    HitTimer();

    WorldPackets::Misc::StopElapsedTimer stopElapsedTimer;
    stopElapsedTimer.TimerID = WorldPackets::Misc::StartTimer::TimerType::ChallengeMode;
    BroadcastPacket(stopElapsedTimer.Write());

    if (_challengeEntry)
    {
        WorldPackets::ChallengeMode::Complete complete;
        complete.Run.MapChallengeModeID = _mapID;
        complete.Run.DurationMs = _challengeTimer;
        complete.Run.Level = _challengeLevel;
        complete.Run.MapChallengeModeID = _challengeEntry->ID;
        complete.IsCompletedInTimer = _rewardLevel > CHALLENGE_NOT_IN_TIMER;
        BroadcastPacket(complete.Write());
    }

    if (Group* group = sGroupMgr->GetGroupByGUID(_groupGUID))
    {
        group->SetDungeonDifficultyID(DIFFICULTY_MYTHIC);

        //if(keyOwner)
        //    if(group->IsGuildGroup() && group->CanRecieveGuildChallengeCredit())
        //        if (Guild* guild = keyOwner->GetGuild())
        //            guild->CompleteGuildChallenge(GuildChallengeType::ChallengeDungeonChallenge, keyOwner);
    }

    // Reward part
    if (keystone)
    {
        if (!_isKeyDepleted)
        {
            if (_challengeEntry)
            {
                if (auto keyInfo = keyOwner->GetPlayerChallenge()->GetKeystoneInfo(keystone))
                {
                    keyInfo->GenerateNewDungeon();
                    keyInfo->Level = std::min(_challengeLevel + _rewardLevel, sWorld->getIntConfig(CONFIG_CHALLENGE_LEVEL_LIMIT));
                    keystone->SetModifier(ITEM_MODIFIER_CHALLENGE_MAP_CHALLENGE_MODE_ID, keyInfo->ID);
                    keystone->SetModifier(ITEM_MODIFIER_CHALLENGE_KEYSTONE_LEVEL, keyInfo->Level);
                }
            }            
        }
        else
            keyOwner->ChallengeKeyCharded(keystone, _challengeLevel);

        keyOwner->UpdateChallengeKey(keystone);
        keystone->SetState(ITEM_CHANGED, keyOwner);
    }
    else
    {
        if (keyOwner = ObjectAccessor::FindPlayer(_keyOwner))
        {
            if (keystone = keyOwner->GetItemByGuid(m_itemGuid))
                keyOwner->ChallengeKeyCharded(keystone, _challengeLevel);
            else
                CharacterDatabase.PExecute("UPDATE challenge_key SET KeyIsCharded = 0, InstanceID = 0 WHERE guid = %u and itemid = %u", _keyOwner.GetCounter(), m_itemGuid.GetCounter());
        }
        else
            CharacterDatabase.PExecute("UPDATE challenge_key SET KeyIsCharded = 0, InstanceID = 0 WHERE guid = %u and itemid = %u", _keyOwner.GetCounter(), m_itemGuid.GetCounter());
    }

    auto challengeData = new ChallengeData;
    ObjectGuid::LowType guid = sObjectMgr->GenerateScenarioId();
    challengeData->ID = ObjectGuid::Create<HighGuid::Scenario>(_mapID, _challengeEntry->ID, guid).GetCounter();
    challengeData->MapID = _mapID;
    challengeData->RecordTime = _challengeTimer;
    challengeData->StartDate = time(nullptr) - GetChallengeTimerToNow();
    challengeData->CompleteDate = time(nullptr);
    challengeData->ChallengeLevel = _challengeLevel;
    challengeData->TimerLevel = _rewardLevel;
    challengeData->ChallengeID = _challengeEntry ? _challengeEntry->ID : 0;
    challengeData->Affixes = _affixes;
    challengeData->GuildID = 0;
    challengeData->Expansion = 9; // shadowwlands
    if (InstanceScript* script = GetInstanceScript())
        challengeData->ChestID = script->GetChallengeModeChest().GetEntry();
    else
        challengeData->ChestID = 0;

    std::map<ObjectGuid::LowType /*guild*/, uint32> guildCounter;
    _map->DoOnPlayers([&](Player* player)
    {
        ChallengeMember member;
        member.playerGuid = player->GetGUID();
        member.specId = player->GetSpecializationId();
        member.CompleteDate = time(nullptr);
        member.ChallengeLevel = _challengeLevel;
        if (InstanceScript* script = GetInstanceScript())
            member.ChestID = script->GetChallengeModeChest().GetEntry();
        else
            member.ChestID = 0;

        if (Guild* guild = player->GetGuild())
            member.guildGuid = guild->GetGUID();

        member.Ilevel = player->GetAverageItemLevel();
        member.Race = player->GetRace();

        if (player->GetGuildId())
            guildCounter[player->GetGuildId()]++;

        SendChallengeBonusLootPrompt(player);

        challengeData->members.insert(member);
        if (sChallengeModeMgr->CheckBestMemberMapId(member.playerGuid, challengeData))
            SendChallengeModeNewPlayerRecord(player);

        sChallengeModeMgr->GenerateAchievementByMythicLevel(player, _challengeLevel);
        player->UpdateCriteria(CriteriaType::CompleteChallengeMode, _mapID, _rewardLevel);
        player->UpdateCriteria(CriteriaType::CompleteAnyChallengeMode, _challengeLevel);

        player->RemoveAura(SPELL_CHALLENGER_BURDEN);
        player->CombatStop();
    });

    for (auto const& v : guildCounter)
        if (v.second >= 3)
            challengeData->GuildID = v.first;

    sChallengeModeMgr->SetChallengeMapData(challengeData->ID, challengeData);
    sChallengeModeMgr->CheckBestMapId(challengeData);
    sChallengeModeMgr->CheckBestGuildMapId(challengeData);
    sChallengeModeMgr->SaveChallengeToDB(challengeData);

    if (GetInstanceScript())
        GetInstanceScript()->OnChallengeComplete();
}

void Challenge::HitTimer()
{
    if (GetChallengeTimer() < _chestTimers[2])
        _rewardLevel = CHALLENGE_TIMER_LEVEL_3; // 3 chests + 3 levels
    else if (GetChallengeTimer() < _chestTimers[1])
        _rewardLevel = CHALLENGE_TIMER_LEVEL_2; // 2 chests + 2 levels
    else if (GetChallengeTimer() < _chestTimers[0])
        _rewardLevel = CHALLENGE_TIMER_LEVEL_1; // 1 chest + 1 level
    else
        _rewardLevel = CHALLENGE_NOT_IN_TIMER;

    if (!_map)
        return;

    for (auto const& guid : _challengers)
        _countItems[guid] = 0;

    switch (_rewardLevel)
    {
        case CHALLENGE_TIMER_LEVEL_3: // 3 chests + 3 levels
        case CHALLENGE_TIMER_LEVEL_2: // 2 chests + 2 levels
        case CHALLENGE_TIMER_LEVEL_1: // 1 chest + 1 level
        case CHALLENGE_NOT_IN_TIMER:  // 0 chest
        {
            if (InstanceScript* script = GetInstanceScript())
            {
                SummonGobject(false);

                float _chance = sChallengeModeMgr->GetChanceItem(_rewardLevel, _challengeLevel);
                auto countItems = int32(_chance / 100.0f);
                _chance -= countItems * 100.0f;

                if (roll_chance_f(_chance))
                    countItems++;

                while (countItems > 0)
                {
                    GuidVector temp;
                    temp.reserve(_challengers.size());
                    for (auto c : _challengers)
                        temp.emplace_back(c);
                    //auto _tempList = _challengers;
                    Trinity::Containers::RandomResize(temp, countItems);

                    for (auto const& guid : temp)
                    {
                        countItems--;
                        _countItems[guid] += 1;
                    }
                }
            }
        }
        default:
            break;
    }
}

std::array<int32, 4> Challenge::GetAffixes() const
{
    return _affixes;
}

bool Challenge::HasAffix(Affixes affix)
{
    return _affixesTest.test(size_t(affix));
}

uint32 Challenge::GetChallengeTimerToNow() const
{
    return (getMSTime() - _challengeTimer) / IN_MILLISECONDS;
}

void Challenge::BroadcastPacket(WorldPacket const* data) const
{
    _map->DoOnPlayers([&](Player* player)
    {
        player->SendDirectMessage(data);
    });
}

uint32 Challenge::GetChallengeTimer()
{
    if (!_challengeTimer)
        return 0;

    return _challengeTimer / IN_MILLISECONDS;
}

void Challenge::ModChallengeTimer()
{
    _challengeTimer += 5 * IN_MILLISECONDS;
}

void Challenge::ResetGo()
{
    SummonGobject(true);

    if (InstanceScript* script = GetInstanceScript())
    {
        if (GameObject* challengeOrb = _map->GetGameObject(script->GetChallengeModeOrb()))
        {
            challengeOrb->SetGoState(GO_STATE_READY);
            challengeOrb->RemoveFlag(GO_FLAG_NODESPAWN);
        }
    }
}

void Challenge::SendStartTimer(Player* player)
{
    WorldPackets::Misc::StartTimer packet;
    packet.Type      = WorldPackets::Misc::StartTimer::TimerType::ChallengeMode;
    packet.TimeLeft  = 9s;
    packet.TotalTime = 10s;
    if (player)
        player->SendDirectMessage(packet.Write());
    else
        BroadcastPacket(packet.Write());
}

void Challenge::SendStartElapsedTimer(Player* player)
{
    WorldPackets::Misc::StartElapsedTimer packet;

    packet.Timer.TimerID         = WorldPackets::Misc::StartTimer::TimerType::ChallengeMode;
    packet.Timer.CurrentDuration = GetChallengeTimer();

    if (player)
        player->SendDirectMessage(packet.Write());
    else
        BroadcastPacket(packet.Write());
}

void Challenge::SendChallengeModeStart(Player* player /*= nullptr*/)
{
    if (!_challengeEntry)
        return;

    WorldPackets::ChallengeMode::Start packet;
    packet.MapID                 = _mapID;
    packet.ChallengeId           = _challengeEntry->ID;
    packet.ChallengeLevel        = _challengeLevel;
    packet.Affixes               = _affixes;
    packet.IsKeyCharged          = true; //Always true since 735

    if (player)
        player->SendDirectMessage(packet.Write());
    else
        BroadcastPacket(packet.Write());
}

void Challenge::SendChallengeInstanceEncounterStart()
{
    InstanceScript* script = GetInstanceScript();
    if (!script)
        return;

    uint32 resInterval = script->GetCombatResurrectionChargeInterval();
    script->InitializeCombatResurrections(1, resInterval);
    script->SendEncounterStart(1, 5, resInterval, resInterval, false);
}

void Challenge::SendChallengeModeNewPlayerRecord(Player* player)
{
    WorldPackets::ChallengeMode::NewPlayerRecord newRecord;

    newRecord.ChallengeId    = _challengeEntry->ID;
    newRecord.Duration       = _challengeTimer;
    newRecord.ChallengeLevel = _challengeLevel;

    player->SendDirectMessage(newRecord.Write());
}

void Challenge::SummonGobject(bool door)
{
    float x, y, z, o, rot0, rot1, rot2, rot3;
    if (sChallengeModeMgr->GetChallengeDoorOrChestPosition(_mapID, x, y, z, o, rot0, rot1, rot2, rot3, door, IsHordeChallenge()))
    {
        if (uint32 entry = sChallengeModeMgr->GetDoorOrChestByMap(_mapID, door, IsHordeChallenge()))
            if (InstanceScript* script = GetInstanceScript())
                script->instance->SummonGameObject(entry, Position(x, y, z, o), QuaternionData(rot0, rot1, rot2, rot3), 0);
    }
    else
    {
        if (auto script = GetInstanceScript())
            script->SummonChallengeGameObject(door);
        // let instance script handle it.
    }
}

void Challenge::SetInstanceScript(InstanceScript* instanceScript)
{
    _instanceScript = instanceScript;
}

InstanceScript* Challenge::GetInstanceScript() const
{
    return _instanceScript;
}

uint8 Challenge::GetItemCount(ObjectGuid guid) const
{
    auto itr = _countItems.find(guid);
    if (itr == _countItems.end())
        return 0;

    return itr->second;
}

uint8 Challenge::GetLevelBonus() const
{
    switch (_rewardLevel)
    {
        case CHALLENGE_TIMER_LEVEL_3: // 3 chests + 3 levels
            return 2;
        case CHALLENGE_TIMER_LEVEL_2: // 2 chests + 2 levels
            return 1;
        case CHALLENGE_TIMER_LEVEL_1: // 1 chest + 1 level
        case CHALLENGE_NOT_IN_TIMER:  // 0 chest
        default:
            return 0;
    }
}

float Challenge::GetDamageMultiplier(uint8 challengeLevel)
{
    if (_challengeLevelInfo)
    {
        uint32 challengers = _challengers.size();
        return _challengeLevelInfo->BaseDmgScaling + (_challengeLevelInfo->DMGScalingPerPlayer * (float)challengers);
    }

    if (GtChallengeModeDamage const* challengeDamage = sChallengeModeDamage.GetRow(challengeLevel))
        return challengeDamage->Scalar;

    return 1.0f;
}

float Challenge::GetHealthMultiplier(uint8 challengeLevel)
{
    if (_challengeLevelInfo)
    {
        uint32 challengers = _challengers.size();
        return _challengeLevelInfo->BaseHPScaling + (_challengeLevelInfo->HPScalingPerPlayer * (float)challengers);
    }

    if (GtChallengeModeHealth const* challengeHealth = sChallengeModeHealth.GetRow(challengeLevel))
        return challengeHealth->Scalar;

    return 1.0f;
}

void Challenge::SendChallengeBonusLootPrompt(Player* player)
{
    if (!player)
        return;

    //BonusRollEntry const* entry = sDB2Manager.GetBonusRollIDByMap(_mapID);
    //if (!entry)
    //    return;
    //
    //CustomSpellValues mod;
    //mod.AddSpellMod(SPELLVALUE_BASE_POINT0, entry->ID);
    //mod.AddSpellMod(SPELLVALUE_BASE_POINT1, player->GetCurrency(entry->CurrencyTypeID));
    //mod.AddSpellMod(SPELLVALUE_BASE_POINT2, GetChallengeLevel());
    //player->CastCustomSpell(SPELL_CHALLENGE_BONUS_LOOT, mod, player, TRIGGERED_FULL_MASK);
}
