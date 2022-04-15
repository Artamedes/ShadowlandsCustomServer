/*
 * Copyright (C) 2017-2018 AshamaneProject <https://github.com/AshamaneProject>
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

#include "ChallengeModePackets.h"
#include "ChallengeModeMgr.h"
#include "ChallengeMode.h"
#include "Chat.h"
#include "InstanceScript.h"
#include "Item.h"
#include "Group.h"
#include "Log.h"
#include "Player.h"
#include "SharedDefines.h"
#include "WorldSession.h"
#include "GameObject.h"

void WorldSession::HandleChallengeModeStart(WorldPackets::ChallengeMode::StartRequest& start)
{
    if (!sWorld->getBoolConfig(CONFIG_CHALLENGE_ENABLED))
        return;

    GameObject* object = _player->GetGameObjectIfCanInteractWith(start.GobGUID, GAMEOBJECT_TYPE_KEYSTONE_RECEPTACLE);
    if (!object)
    {
        TC_LOG_DEBUG("network", "WORLD: HandleChallengeModeStart - %s not found or you can not interact with it.", start.GobGUID.ToString().c_str());
        return;
    }

    Item* key = _player->GetItemByPos(start.Bag, start.Slot);
    if (!key)
    {
        TC_LOG_DEBUG("network", "WORLD: HandleChallengeModeStart - item in Bag %u and Slot %u not found.", start.Bag, start.Slot);
        return;
    }

    if (key->GetTemplate()->GetClass() != ITEM_CLASS_REAGENT || key->GetTemplate()->GetSubClass() != ITEM_SUBCLASS_KEYSTONE)
    {
        TC_LOG_DEBUG("network", "WORLD: HandleChallengeModeStart - Tried to start a challenge with item %s which have class %u and subclass %u.",
            key->GetGUID().ToString().c_str(),
            key->GetTemplate()->GetClass(),
            key->GetTemplate()->GetSubClass());
        return;
    }

    uint32 challengeModeId      = key->GetModifier(ITEM_MODIFIER_CHALLENGE_MAP_CHALLENGE_MODE_ID);
    uint32 challengeModeLevel   = key->GetModifier(ITEM_MODIFIER_CHALLENGE_KEYSTONE_LEVEL);

    MapChallengeModeEntry const* entry = sMapChallengeModeStore.LookupEntry(challengeModeId);
    if (!entry || !challengeModeLevel || entry->MapID != _player->GetMapId())
    {
        TC_LOG_DEBUG("network", "WORLD: HandleChallengeModeStart - Tried to start a challenge with wrong challengeModeId %u and level %u.", challengeModeId, challengeModeLevel);
        return;
    }

    InstanceMap* inst = _player->GetMap()->ToInstanceMap();
    if (!inst)
    {
        ChatHandler(_player->GetSession()).PSendSysMessage("Error: Is not a Instance Map.");
        return;
    }

    Difficulty difficulty = DIFFICULTY_MYTHIC_KEYSTONE;

    if (inst->GetSpawnMode() == difficulty)
    {
        ChatHandler(_player->GetSession()).PSendSysMessage("Error: For run Mythic please rerun instance.");
        return;
    }

    if (_player->m_challengeKeyInfo.InstanceID)
    {
        ChatHandler(_player->GetSession()).PSendSysMessage("Error: Key allready run in other instance.");
        return;
    }

    if (_player->m_challengeKeyInfo.Level < MYTHIC_LEVEL_2)
    {
        _player->ChallengeKeyCharded(nullptr, _player->m_challengeKeyInfo.Level, false); // Deleted bugged key
        ChatHandler(_player->GetSession()).PSendSysMessage("Error: Key is bugged.");
        return;
    }

    if (!_player->IsAlive())
    {
        ChatHandler(_player->GetSession()).PSendSysMessage("Error: Player not found or die.");
        return;
    }

    if (_player->IsInCombat())
    {
        ChatHandler(_player->GetSession()).PSendSysMessage("Error: Player in combat.");
        return;
    }

    float x = 0.0f; float y = 0.0f; float z = 0.0f; float o = 0.0f;
    if (!sChallengeModeMgr->GetStartPosition(_player->GetMapId(), x, y, z, o, _player->GetGUID()))
    {
        ChatHandler(_player->GetSession()).PSendSysMessage("Error: Start position not found.");
        return;
    }    

    if (Group* group = _player->GetGroup())
    {    
        for (GroupReference* itr = group->GetFirstMember(); itr != nullptr; itr = itr->next())
        {
            Player* player = itr->GetSource();
            if (!player || !player->IsAlive())
            {
                ChatHandler(_player->GetSession()).PSendSysMessage("Error: Player not found or die.");
                return;
            }

            if (player->IsInCombat())
            {
                ChatHandler(_player->GetSession()).PSendSysMessage("Error: Player in combat.");
                return;
            }

            if (!player->GetMap() || player->GetMap()->ToInstanceMap() != inst)
            {
                ChatHandler(_player->GetSession()).PSendSysMessage("Error: Player in group not this map.");
                return;
            }
        }

        group->m_challengeEntry = sMapChallengeModeStore.LookupEntry(_player->m_challengeKeyInfo.ID);
        group->m_affixes.fill(0);

        MapChallengeModeEntry const* challengeEntry = sDB2Manager.GetChallengeModeByMapID(_player->GetMapId());
        if (!group->m_challengeEntry || !challengeEntry || challengeEntry->MapID != group->m_challengeEntry->MapID)
        {
            group->m_challengeEntry = nullptr;
            ChatHandler(_player->GetSession()).PSendSysMessage("Error: Is not this challenge.");
            return;
        }

        group->m_challengeOwner = _player->GetGUID();
        group->m_challengeItem = key->GetGUID();
        group->m_challengeLevel = _player->m_challengeKeyInfo.Level;

        if (group->m_challengeLevel > MYTHIC_LEVEL_1)
            group->m_affixes[0] = _player->m_challengeKeyInfo.Affix;
        if (group->m_challengeLevel > MYTHIC_LEVEL_3)
            group->m_affixes[1] = _player->m_challengeKeyInfo.Affix1;
        if (group->m_challengeLevel > MYTHIC_LEVEL_6)
            group->m_affixes[2] = _player->m_challengeKeyInfo.Affix2;
        if (group->m_challengeLevel > MYTHIC_LEVEL_9)
            group->m_affixes[3] = _player->m_challengeKeyInfo.Affix3;        

        WorldPackets::Instance::ChangePlayerDifficultyResult result;
        result.Result = AsUnderlyingType(ChangeDifficultyResult::DIFFICULTY_CHANGE_SET_COOLDOWN_S);
        result.CooldownReason = 2813862382;
        group->BroadcastPacket(result.Write(), true);

        WorldPackets::Instance::ChangePlayerDifficultyResult result2;
        result2.Result = AsUnderlyingType(ChangeDifficultyResult::DIFFICULTY_CHANGE_BY_PARTY_LEADER);
        result2.InstanceMapID = _player->GetMapId();
        result2.DifficultyRecID = difficulty;                
        
        group->SetDungeonDifficultyID(difficulty);
        _player->GetMap()->SetSpawnMode(difficulty);
        _player->SendDirectMessage(result2.Write());
        _player->TeleportToChallenge(_player->GetMapId(), x, y, z, o, _player);

        for (GroupReference* itr = group->GetFirstMember(); itr != nullptr; itr = itr->next())
        {
            if (Player* player = itr->GetSource())
            {
                if (player == _player)
                    continue;
                
                player->SendDirectMessage(result2.Write());
                player->TeleportToChallenge(_player->GetMapId(), x, y, z, o);               
                player->CastSpell(player, SPELL_CHALLENGER_BURDEN, true);
            }
        }        
    }
    else
    {
        _player->m_challengeKeyInfo.challengeEntry = sMapChallengeModeStore.LookupEntry(_player->m_challengeKeyInfo.ID);

        MapChallengeModeEntry const* challengeEntry = sDB2Manager.GetChallengeModeByMapID(_player->GetMapId());
        if (!_player->m_challengeKeyInfo.challengeEntry || !challengeEntry || challengeEntry->MapID != _player->m_challengeKeyInfo.challengeEntry->MapID)
        {
            _player->m_challengeKeyInfo.challengeEntry = nullptr;
            ChatHandler(_player->GetSession()).PSendSysMessage("Error: Is not this challenge.");
            return;
        }

        WorldPackets::Instance::ChangePlayerDifficultyResult result;
        result.Result = AsUnderlyingType(ChangeDifficultyResult::DIFFICULTY_CHANGE_SET_COOLDOWN_S);
        result.CooldownReason = 2813862382;
        SendPacket(result.Write(), true);

        WorldPackets::Instance::ChangePlayerDifficultyResult result2;
        result2.Result = AsUnderlyingType(ChangeDifficultyResult::DIFFICULTY_CHANGE_BY_PARTY_LEADER);
        result2.InstanceMapID = _player->GetMapId();
        result2.DifficultyRecID = difficulty;

        _player->GetMap()->SetSpawnMode(difficulty);
        _player->SetDungeonDifficultyID(difficulty);
        _player->SendDirectMessage(result2.Write());
        _player->TeleportToChallenge(_player->GetMapId(), x, y, z, o, _player);
        _player->CastSpell(_player, SPELL_CHALLENGER_BURDEN, true);
    }        

    object->SetGoState(GO_STATE_ACTIVE);
    object->SetFlag(GO_FLAG_NODESPAWN);
}

void WorldSession::HandleRequestLeaders(WorldPackets::ChallengeMode::RequestLeaders& leaders)
{
    WorldPackets::ChallengeMode::RequestLeadersResult result;

    result.MapID = leaders.MapId;
    result.ChallengeID = leaders.ChallengeID;
    result.LastGuildUpdate = leaders.LastGuildUpdate;
    result.LastRealmUpdate = leaders.LastRealmUpdate;

    if (auto bestGuild = sChallengeModeMgr->BestGuildChallenge(_player->GetGuildId(), leaders.ChallengeID))
    {
        for (auto itr = bestGuild->members.begin(); itr != bestGuild->members.end(); ++itr)
        {
            WorldPackets::ChallengeMode::ModeAttempt guildLeaders;
            guildLeaders.InstanceRealmAddress = GetVirtualRealmAddress();
            guildLeaders.AttemptID = bestGuild->ID;
            guildLeaders.CompletionTime = bestGuild->RecordTime;
            guildLeaders.CompletionDate = bestGuild->CompleteDate;
            guildLeaders.MedalEarned = bestGuild->ChallengeLevel;

            for (auto const& v : bestGuild->members)
            {
                WorldPackets::ChallengeMode::ModeAttempt::MemberAttempt memberData;
                memberData.VirtualRealmAddress = GetVirtualRealmAddress();
                memberData.NativeRealmAddress = GetVirtualRealmAddress();
                memberData.Guid = v.playerGuid;
                memberData.SpecializationID = v.specId;
                guildLeaders.Members.emplace_back(memberData);
            }

            result.GuildLeaders.emplace_back(guildLeaders);
        }
    }

    if (ChallengeData* bestServer = sChallengeModeMgr->BestServerChallenge(leaders.ChallengeID))
    {
        WorldPackets::ChallengeMode::ModeAttempt realmLeaders;
        realmLeaders.InstanceRealmAddress = GetVirtualRealmAddress();
        realmLeaders.AttemptID = bestServer->ID;
        realmLeaders.CompletionTime = bestServer->RecordTime;
        realmLeaders.CompletionDate = bestServer->CompleteDate;
        realmLeaders.MedalEarned = bestServer->ChallengeLevel;

        for (auto const& v : bestServer->members)
        {
            WorldPackets::ChallengeMode::ModeAttempt::MemberAttempt memberData;
            memberData.VirtualRealmAddress = GetVirtualRealmAddress();
            memberData.NativeRealmAddress = GetVirtualRealmAddress();
            memberData.Guid = v.playerGuid;
            memberData.SpecializationID = v.specId;
            realmLeaders.Members.emplace_back(memberData);
        }
        result.RealmLeaders.push_back(realmLeaders);
    }

    SendPacket(result.Write());
}

void WorldSession::HandleChallengeModeRequestMapStats(WorldPackets::ChallengeMode::RequestMapStats& /*mapStats*/)
{
    WorldPackets::ChallengeMode::AllMapStats stats;
    int8 seasonID = sWorld->getIntConfig(CONFIG_CHALLENGE_SEASON_ID);
    stats.CurrentSeason = seasonID;
    stats.SeasonID = seasonID;
    if (ChallengeByMap* last = sChallengeModeMgr->LastForMember(_player->GetGUID()))
    {        
        for (auto const& v : *last)
        {
            WorldPackets::ChallengeMode::ChallengeMapStat mapStat;            
            mapStat.ChallengeID = v.second->ChallengeID;
            mapStat.CompletedChallengeLevel = v.second->ChallengeLevel;

            if (ChallengeData* _lastData = sChallengeModeMgr->BestForMemberMap(_player->GetGUID(), v.second->ChallengeID))
                mapStat.BestCompletionMilliseconds = _lastData->RecordTime;
            else
                mapStat.BestCompletionMilliseconds = v.second->RecordTime;
           
            mapStat.StartTime = v.second->StartDate;
            mapStat.EndTime = v.second->CompleteDate;
            mapStat.Affixes = v.second->Affixes;

            for (auto const& member : v.second->members)
            {
                WorldPackets::ChallengeMode::MapStatMember memberStatData;
                memberStatData.VirtualRealmAddress = GetVirtualRealmAddress();
                memberStatData.NativeRealmAddress = GetVirtualRealmAddress();
                memberStatData.PlayerGuid = member.playerGuid;
                memberStatData.GuildGuid = member.guildGuid;
                memberStatData.SpecializationID = member.specId;
                memberStatData.Ilevel = member.Ilevel;
                memberStatData.Race = member.Race;
                mapStat.Members.push_back(memberStatData);
            }

            if(v.second->Expansion == EXPANSION_BATTLE_FOR_AZEROTH)
                stats.BFAChallengeModeMaps.push_back(mapStat);
            else
                stats.LegionChallengeModeMaps.push_back(mapStat);
        }

        //ToDo WeekAttempt
    }

    SendPacket(stats.Write());
}

void WorldSession::HandleGetChallengeModeRewards(WorldPackets::ChallengeMode::GlobalGetChallengeModeRewards& modeRewards)
{
    ObjectGuid lootOwnerGUID = GetPlayer()->GetGUID();
    OploteLoot* oploteLoot = sChallengeModeMgr->GetOploteLoot(lootOwnerGUID);
    WorldPackets::ChallengeMode::Rewards rewards;
    rewards.IsWeeklyRewardAvailable = oploteLoot ? true : false;
    rewards.LastWeekHighestKeyCompleted = oploteLoot ? oploteLoot->ChallengeLevel : 0;
    rewards.LastWeekMapChallengeKeyEntry = oploteLoot ? oploteLoot->ChallengeID : 0;
    rewards.CurrentWeekHighestKeyCompleted = sChallengeModeMgr->GetBestActualWeekChallengeLevel();
    SendPacket(rewards.Write());
}

void WorldSession::HandleResetChallengeMode(WorldPackets::ChallengeMode::ResetChallengeMode& /*reset*/)
{
    if (auto const& instanceScript = _player->GetInstanceScript())
        if (instanceScript->instance->IsChallengeMode())
            instanceScript->ResetChallengeMode(_player);
}

void WorldSession::HandleRequestChallengeModeAffixes(WorldPackets::ChallengeMode::RequestChallengeModeAffixes& /*modeAffixes*/)
{
    WorldPackets::ChallengeMode::Affixes affixes;
    affixes.affixesFileDatas.push_back(sWorld->getWorldState(WS_CHALLENGE_AFFIXE1_RESET_TIME));
    affixes.affixesFileDatas.push_back(sWorld->getWorldState(WS_CHALLENGE_AFFIXE2_RESET_TIME));
    affixes.affixesFileDatas.push_back(sWorld->getWorldState(WS_CHALLENGE_AFFIXE3_RESET_TIME));
    affixes.affixesFileDatas.push_back(sWorld->getWorldState(WS_CHALLENGE_AFFIXE4_RESET_TIME));
    SendPacket(affixes.Write());
}

void WorldSession::HandleResetChallengeModeCheat(WorldPackets::ChallengeMode::ResetChallengeModeCheat& /*resetModeCheat*/)
{

}
