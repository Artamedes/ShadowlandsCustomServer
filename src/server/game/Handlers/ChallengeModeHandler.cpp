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
#include "PlayerChallenge.h"
#include "MapManager.h"

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

    //if (inst->GetSpawnMode() == difficulty)
    //{
    //    ChatHandler(_player->GetSession()).PSendSysMessage("Error: To run this Mythic please rerun instance.");
    //    return;
    //}

    auto playerChallenge = _player->GetPlayerChallenge();
    auto challengeKeyInfo = playerChallenge->GetKeystoneInfo(key);
    if (!challengeKeyInfo)
    {
        ChatHandler(_player).PSendSysMessage("No keystone data found");
        return;
    }

    if (_player->GetGroup())
    {
        if (challengeKeyInfo->Type == KeystoneType::Solo)
        {
            ChatHandler(_player).PSendSysMessage("You can only run that key in solo");
            return;
        }
    }

    //if (challengeKeyInfo->InstanceID)
    //{
    //    ChatHandler(_player->GetSession()).PSendSysMessage("Error: Key allready run in other instance.");
    //    return;
    //}

    if (challengeKeyInfo->Level < MYTHIC_LEVEL_2)
    {
        _player->ChallengeKeyCharded(key, challengeKeyInfo->Level, false); // Deleted bugged key
        ChatHandler(_player->GetSession()).PSendSysMessage("Error: Key is bugged.");
        return;
    }

    if (!_player->IsAlive())
    {
        ChatHandler(_player->GetSession()).PSendSysMessage("Error: Player not found or is dead.");
        return;
    }

    if (_player->IsInCombat())
    {
        ChatHandler(_player->GetSession()).PSendSysMessage("Error: Player in combat.");
        return;
    }

    float x = 0.0f; float y = 0.0f; float z = 0.0f; float o = 0.0f;
    if (!sChallengeModeMgr->GetStartPosition(_player->GetInstanceScript(), x, y, z, o, _player->GetGUID()))
    {
        ChatHandler(_player->GetSession()).PSendSysMessage("Error: Start position not found.");
        return;
    }

    challengeKeyInfo->challengeEntry = sMapChallengeModeStore.LookupEntry(challengeKeyInfo->ID);

    if (Group* group = _player->GetGroup())
    {
        MapChallengeModeEntry const* challengeEntry = sDB2Manager.GetChallengeModeByMapID(_player->GetMapId());
        if (!challengeKeyInfo->challengeEntry || !challengeEntry || challengeEntry->MapID != challengeKeyInfo->challengeEntry->MapID)
        {
            challengeKeyInfo->challengeEntry = nullptr;
            ChatHandler(_player->GetSession()).PSendSysMessage("Error: Incorrect challenge.");
            return;
        }

        for (GroupReference* itr = group->GetFirstMember(); itr != nullptr; itr = itr->next())
        {
            Player* player = itr->GetSource();
            if (!player || !player->IsAlive())
            {
                ChatHandler(_player->GetSession()).PSendSysMessage("Error: Player not found or is dead.");
                return;
            }

            if (player->IsInCombat())
            {
                ChatHandler(_player->GetSession()).PSendSysMessage("Error: Player in combat.");
                return;
            }

            if (!player->GetMap() || player->GetMap()->ToInstanceMap() != inst)
            {
                ChatHandler(_player->GetSession()).PSendSysMessage("Error: Internal map error.");
                return;
            }

            if (player->GetScheduler().HasGroup(700000) || player->IsBeingTeleported())
            {
                ChatHandler(_player->GetSession()).PSendSysMessage("Error: player is teleporting");
                return;
            }
        }
    }
    else
    {
        MapChallengeModeEntry const* challengeEntry = sDB2Manager.GetChallengeModeByMapID(_player->GetMapId());
        if (!challengeKeyInfo->challengeEntry || !challengeEntry || challengeEntry->MapID != challengeKeyInfo->challengeEntry->MapID)
        {
            challengeKeyInfo->challengeEntry = nullptr;
            ChatHandler(_player->GetSession()).PSendSysMessage("Error: Incorrect challenge.");
            return;
        }

        if (_player->GetScheduler().HasGroup(700000) || _player->IsBeingTeleported())
        {
            ChatHandler(_player->GetSession()).PSendSysMessage("Error: player is teleporting");
            return;
        }
    }

    auto mapId = _player->GetMapId();
    Map* newMap = sMapMgr->CreateMap(mapId, _player, 0, true);

    if (!newMap)
    {
        ChatHandler(_player->GetSession()).PSendSysMessage("Error: Couldn't create challenge");
        return;
    }

    auto SendGroupKeystoneInfo([&](Player* player)
    {
        ChatHandler(player).PSendSysMessage("|cff35B3EEGroup Keystone %s|cff35B3EE started by %s|cff35B3EE!", Item::GetItemLink(key), _player->GetName().c_str());
    });

    auto SendTimewalkKeystoneInfo([&](Player* player)
    {
        ChatHandler(player).PSendSysMessage("|cff35B3EETimewalking Keystone %s|cff35B3EE started by %s|cff35B3EE!", Item::GetItemLink(key), _player->GetName().c_str());
    });

    if (Group* group = _player->GetGroup())
    {
        //WorldPackets::Instance::ChangePlayerDifficultyResult result;
        //result.Result = AsUnderlyingType(ChangeDifficultyResult::DIFFICULTY_CHANGE_SET_COOLDOWN_S);
        //result.CooldownReason = 18446744072059367961;
        //group->BroadcastPacket(result.Write(), true);
        //
        //WorldPackets::Instance::ChangePlayerDifficultyResult result2;
        //result2.Result = AsUnderlyingType(ChangeDifficultyResult::DIFFICULTY_CHANGE_BY_PARTY_LEADER);
        //result2.InstanceMapID = _player->GetMapId();
        //result2.DifficultyRecID = DIFFICULTY_MYTHIC_KEYSTONE;                
        //
        //_player->SendDirectMessage(result2.Write());
        _player->TeleportToChallenge(newMap, x, y, z, o, _player, challengeKeyInfo);

        for (GroupReference* itr = group->GetFirstMember(); itr != nullptr; itr = itr->next())
        {
            if (Player* player = itr->GetSource())
            {
                switch (challengeKeyInfo->Type)
                {
                    case KeystoneType::Solo:
                        ChatHandler(player).PSendSysMessage("PIGPIG! |cff35B3EESolo Keystone %s |cff35B3EEstarted!", Item::GetItemLink(key), _player->GetName().c_str());
                        break;
                    case KeystoneType::Group:
                        SendGroupKeystoneInfo(player);
                        break;
                    case KeystoneType::Timewalking:
                        SendTimewalkKeystoneInfo(player);
                        break;
                    default:
                        break;
                }
                if (player == _player)
                    continue;
                
             //   player->SendDirectMessage(result2.Write());
                player->TeleportToChallenge(newMap, x, y, z, o, nullptr, challengeKeyInfo);
                player->CastSpell(player, SPELL_CHALLENGER_BURDEN, true);
            }
        }        
    }
    else
    {
        //WorldPackets::Instance::ChangePlayerDifficultyResult result;
        //result.Result = AsUnderlyingType(ChangeDifficultyResult::DIFFICULTY_CHANGE_SET_COOLDOWN_S);
        //result.CooldownReason = 18446744072059367961;
        //SendPacket(result.Write(), true);
        //
        //WorldPackets::Instance::ChangePlayerDifficultyResult result2;
        //result2.Result = AsUnderlyingType(ChangeDifficultyResult::DIFFICULTY_CHANGE_BY_PARTY_LEADER);
        //result2.InstanceMapID = _player->GetMapId();
        //result2.DifficultyRecID = DIFFICULTY_MYTHIC_KEYSTONE;
        //
        //_player->SendDirectMessage(result2.Write());
        _player->TeleportToChallenge(newMap, x, y, z, o, _player, challengeKeyInfo);
        _player->CastSpell(_player, SPELL_CHALLENGER_BURDEN, true);

        switch (challengeKeyInfo->Type)
        {
            case KeystoneType::Solo:
                ChatHandler(_player).PSendSysMessage("|cff35B3EESolo Keystone %s |cff35B3EEstarted!", Item::GetItemLink(key), _player->GetName().c_str());
                break;
            case KeystoneType::Group:
                SendGroupKeystoneInfo(_player);
                break;
            case KeystoneType::Timewalking:
                SendTimewalkKeystoneInfo(_player);
                break;
            default:
                break;
        }
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
    int8 seasonID = 17;
    stats.Season = seasonID; // 7
    stats.SubSeason = seasonID; // 71
    if (ChallengeByMap* last = sChallengeModeMgr->LastForMember(_player->GetGUID()))
    {
        stats.Runs.reserve(last->size());
        for (auto const& v : *last)
        {
            WorldPackets::MythicPlus::MythicPlusRun mapStat;            
            mapStat.MapChallengeModeID = v.second->ChallengeID;
            mapStat.Level = v.second->ChallengeLevel;

            if (ChallengeData* _lastData = sChallengeModeMgr->BestForMemberMap(_player->GetGUID(), v.second->ChallengeID))
                mapStat.DurationMs = _lastData->RecordTime;
            else
                mapStat.DurationMs = v.second->RecordTime;
           
            mapStat.StartDate = v.second->StartDate;
            mapStat.CompletionDate = v.second->CompleteDate;
            mapStat.KeystoneAffixIDs = v.second->Affixes;

            for (auto const& member : v.second->members)
            {
                WorldPackets::MythicPlus::MythicPlusMember memberStatData;
                memberStatData.VirtualRealmAddress = GetVirtualRealmAddress();
                memberStatData.NativeRealmAddress = GetVirtualRealmAddress();
              //  memberStatData.BnetAccountGUID = member.BnetAccountGUID;
                memberStatData.GUID = member.playerGuid;
                memberStatData.GuildGUID = member.guildGuid;
                memberStatData.ChrSpecializationID = member.specId;
                memberStatData.ItemLevel = member.Ilevel;
                memberStatData.RaceID = member.Race;
                memberStatData.SoulbindID = 0;
                memberStatData.CovenantID = 0; // TODO
                mapStat.Members.push_back(memberStatData);
            }

            stats.Runs.emplace_back(mapStat);
        }

        // send rewards? blizz doesnt
    }

    SendPacket(stats.Write());
}

void WorldSession::HandleGetChallengeModeRewards(WorldPackets::ChallengeMode::GlobalGetChallengeModeRewards& modeRewards)
{
    //ObjectGuid lootOwnerGUID = GetPlayer()->GetGUID();
    //OploteLoot* oploteLoot = sChallengeModeMgr->GetOploteLoot(lootOwnerGUID);
    //WorldPackets::ChallengeMode::Rewards rewards;
    //rewards.IsWeeklyRewardAvailable = oploteLoot ? true : false;
    //rewards.LastWeekHighestKeyCompleted = oploteLoot ? oploteLoot->ChallengeLevel : 0;
    //rewards.LastWeekMapChallengeKeyEntry = oploteLoot ? oploteLoot->ChallengeID : 0;
    //rewards.CurrentWeekHighestKeyCompleted = sChallengeModeMgr->GetBestActualWeekChallengeLevel();
    //SendPacket(rewards.Write());
}

void WorldSession::HandleResetChallengeMode(WorldPackets::ChallengeMode::ResetChallengeMode& /*reset*/)
{
    // couldn't get this to trigger.
    //if (auto const& instanceScript = _player->GetInstanceScript())
    //    if (instanceScript->instance->IsChallengeMode())
    //        instanceScript->ResetChallengeMode(_player);
}

void WorldSession::HandleRequestChallengeModeAffixes(WorldPackets::ChallengeMode::RequestChallengeModeAffixes& /*modeAffixes*/)
{
    // ServerToClient: SMSG_MYTHIC_PLUS_CURRENT_AFFIXES (0x2606) Length: 52 ConnIdx: 1 Time: 04/17/2022 04:20:35.602 Number: 2789
    // [0].KeystoneAffixID   = 9  ;
    // [0].RequiredSeason    = 0  ;
    // [1].KeystoneAffixID   = 11 ;
    // [1].RequiredSeason    = 0  ;
    // [2].KeystoneAffixID   = 3  ;
    // [2].RequiredSeason    = 0  ;
    // [3].KeystoneAffixID   = 121;
    // [3].RequiredSeason    = 5  ;
    // [4].KeystoneAffixID   = 128;
    // [4].RequiredSeason    = 6  ;
    // [5].KeystoneAffixID   = 130;
    // [5].RequiredSeason    = 7  ;
    // [6].KeystoneAffixID   = 131;
    // [6].RequiredSeason    = 8  ;
    WorldPackets::ChallengeMode::MythicPlusCurrentAffixes affixes;
    /// affixes.Affixes.push_back(sWorldStateMgr->GetValue(WS_CHALLENGE_AFFIXE1_RESET_TIME));
    /// affixes.Affixes.push_back(sWorldStateMgr->GetValue(WS_CHALLENGE_AFFIXE2_RESET_TIME));
    /// affixes.Affixes.push_back(sWorldStateMgr->GetValue(WS_CHALLENGE_AFFIXE3_RESET_TIME));
    /// affixes.Affixes.push_back(sWorldStateMgr->GetValue(WS_CHALLENGE_AFFIXE4_RESET_TIME));


    // TODO: Add correct affixes
    affixes.Affixes.resize(7);
    affixes.Affixes[0].KeystoneAffixID = 9;
    affixes.Affixes[0].RequiredSeason = 0;
    affixes.Affixes[1].KeystoneAffixID = 11;
    affixes.Affixes[1].RequiredSeason = 0;
    affixes.Affixes[2].KeystoneAffixID = 3;
    affixes.Affixes[2].RequiredSeason = 0;
    affixes.Affixes[3].KeystoneAffixID = 121;
    affixes.Affixes[3].RequiredSeason = 5;
    affixes.Affixes[4].KeystoneAffixID = 128;
    affixes.Affixes[4].RequiredSeason = 6;
    affixes.Affixes[5].KeystoneAffixID = 130;
    affixes.Affixes[5].RequiredSeason = 7;
    affixes.Affixes[6].KeystoneAffixID = 131;
    affixes.Affixes[6].RequiredSeason = 8;

    SendPacket(affixes.Write());
}

void WorldSession::HandleResetChallengeModeCheat(WorldPackets::ChallengeMode::ResetChallengeModeCheat& /*resetModeCheat*/)
{

}

void WorldSession::HandleRequestMythicPlusSeasonData(WorldPackets::ChallengeMode::RequestMythicPlusSeasonData& packet)
{
    WorldPacket data(SMSG_MYTHIC_PLUS_SEASON_DATA, 1);
    data.WriteBit(1);
    data.FlushBits();
    SendPacket(&data);
}
