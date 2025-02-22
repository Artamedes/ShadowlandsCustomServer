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

#ifndef ChallengeModePackets_h__
#define ChallengeModePackets_h__

#include "Packet.h"
#include "WorldSession.h"
#include "MythicPlusPacketsCommon.h"
#include "InstancePackets.h"

namespace WorldPackets
{
    namespace Instance
    {
        struct InstancePlayerData;
    }

    namespace ChallengeMode
    {
        struct ModeAttempt
        {
            struct MemberAttempt
            {
                ObjectGuid Guid = ObjectGuid::Empty;
                uint32 VirtualRealmAddress = 0;
                uint32 NativeRealmAddress = 0;
                uint16 SpecializationID = 0;
            };

            uint32 InstanceRealmAddress = 0;
            uint32 AttemptID = 0;
            uint32 CompletionTime = 0;
            time_t CompletionDate = time(nullptr);
            uint32 MedalEarned = 0;
            std::vector<MemberAttempt> Members;
        };

        class StartRequest final : public ClientPacket
        {
        public:
            StartRequest(WorldPacket&& packet) : ClientPacket(CMSG_START_CHALLENGE_MODE, std::move(packet)) { }

            void Read() override;

            uint8 Bag;
            uint32 Slot;
            ObjectGuid GobGUID;
        };

        class RequestLeaders final : public ClientPacket
        {
        public:
            RequestLeaders(WorldPacket&& packet) : ClientPacket(CMSG_CHALLENGE_MODE_REQUEST_LEADERS, std::move(packet)) { }

            void Read() override;

            uint32 MapId = 0;
            uint32 ChallengeID = 0;
            time_t LastGuildUpdate = time(nullptr);
            time_t LastRealmUpdate = time(nullptr);            
        };

        class RequestLeadersResult final : public ServerPacket
        {
        public:
            RequestLeadersResult() : ServerPacket(SMSG_CHALLENGE_MODE_REQUEST_LEADERS_RESULT, 20 + 8) { }

            WorldPacket const* Write() override;

            uint32 MapID = 0;
            uint32 ChallengeID = 0;
            time_t LastGuildUpdate = time(nullptr);
            time_t LastRealmUpdate = time(nullptr);
            std::vector<ModeAttempt> GuildLeaders;
            std::vector<ModeAttempt> RealmLeaders;
        };

        class RequestMapStats final : public ClientPacket
        {
        public:
            RequestMapStats(WorldPacket&& packet) : ClientPacket(CMSG_MYTHIC_PLUS_REQUEST_MAP_STATS, std::move(packet)) { }

            void Read() override { }
        };

        class RequestChallengeModeAffixes final : public ClientPacket
        {
        public:
            RequestChallengeModeAffixes(WorldPacket&& packet) : ClientPacket(CMSG_REQUEST_MYTHIC_PLUS_AFFIXES, std::move(packet)) { }

            void Read() override { }
        };

        struct Affix
        {
            uint32 KeystoneAffixID = 0;
            uint32 RequiredSeason;
        };

        class MythicPlusCurrentAffixes final : public ServerPacket
        {
        public:
            MythicPlusCurrentAffixes() : ServerPacket(SMSG_MYTHIC_PLUS_CURRENT_AFFIXES) { }

            WorldPacket const* Write() override;

            std::vector<Affix> Affixes;
        };

        class AllMapStats final : public ServerPacket
        {
        public:
            AllMapStats() : ServerPacket(SMSG_MYTHIC_PLUS_ALL_MAP_STATS, 10000) { }

            WorldPacket const* Write() override;
            
            uint32 Season = 0;
            uint32 SubSeason = 0;
            std::vector<MythicPlus::MythicPlusRun> Runs;
            std::vector<MythicPlus::Reward> Rewards;
        };

        class Rewards final : public ServerPacket
        {
        public:
            Rewards() : ServerPacket(SMSG_WEEKLY_REWARDS_RESULT, 13) { }

            WorldPacket const* Write() override;

            bool IsWeeklyRewardAvailable;
            uint32 LastWeekHighestKeyCompleted;
            uint32 LastWeekMapChallengeKeyEntry;
            uint32 CurrentWeekHighestKeyCompleted;
        };

        class Start final : public ServerPacket
        {
        public:
            Start() : ServerPacket(SMSG_CHALLENGE_MODE_START, 33) { }

            WorldPacket const* Write() override;

            uint32 MapID;
            uint32 ChallengeId;
            uint32 ChallengeLevel;
            std::array<int32, 4> Affixes;
            uint32 DeathCount = 0;
            std::vector<Instance::InstancePlayerData> PlayerDatas;
            bool IsKeyCharged = false;
        };

        class Reset final : public ServerPacket
        {
        public:
            Reset(uint32 mapId = 0) : ServerPacket(SMSG_CHALLENGE_MODE_RESET, 4), MapId(mapId) { }

            WorldPacket const* Write() override;

            uint32 MapId;
        };

        class UpdateDeathCount final : public ServerPacket
        {
        public:
            UpdateDeathCount(uint32 deathCount = 0) : ServerPacket(SMSG_CHALLENGE_MODE_UPDATE_DEATH_COUNT, 4), DeathCount(deathCount) { }

            WorldPacket const* Write() override;

            uint32 DeathCount;
        };

        struct ChallengeCompleteMembers
        {
            ObjectGuid Member;
            std::string Name;
        };

        class Complete final : public ServerPacket
        {
        public:
            Complete() : ServerPacket(SMSG_CHALLENGE_MODE_COMPLETE, 4) { }

            WorldPacket const* Write() override;

            WorldPackets::MythicPlus::MythicPlusRun Run;
            bool IsCompletedInTimer = false;
            uint32 UnkInt = 1127717072;
            std::vector< ChallengeCompleteMembers> Members;
        };

        class NewPlayerRecord final : public ServerPacket
        {
        public:
            NewPlayerRecord() : ServerPacket(SMSG_MYTHIC_PLUS_NEW_WEEK_RECORD, 12) { }

            WorldPacket const* Write() override;

            uint32 ChallengeId;
            uint32 Duration;
            uint32 ChallengeLevel;
        };

        class NewPlayerSeasonRecord final : public ServerPacket
        {
        public:
            NewPlayerSeasonRecord() : ServerPacket(SMSG_MYTHIC_PLUS_SEASON_DATA, 4) { }

            WorldPacket const* Write() override;

            uint32 ChallengeId;
            uint32 BestDuration;
            uint32 StartedChallengeLevel;
        };

        class ResetChallengeMode final : public ClientPacket
        {
        public:
            ResetChallengeMode(WorldPacket&& packet) : ClientPacket(CMSG_RESET_CHALLENGE_MODE, std::move(packet)) { }

            void Read() override { }
        };

        class ResetChallengeModeCheat final : public ClientPacket
        {
        public:
            ResetChallengeModeCheat(WorldPacket&& packet) : ClientPacket(CMSG_RESET_CHALLENGE_MODE_CHEAT, std::move(packet)) { }

            void Read() override { }
        };        

        class GlobalGetChallengeModeRewards final : public ClientPacket
        {
        public:
            GlobalGetChallengeModeRewards(WorldPacket&& packet) : ClientPacket(CMSG_REQUEST_WEEKLY_REWARDS, std::move(packet)) { }

            void Read() override { }
        };

        class RequestMythicPlusSeasonData final : public ClientPacket
        {
        public:
            RequestMythicPlusSeasonData(WorldPacket&& packet) : ClientPacket(CMSG_REQUEST_MYTHIC_PLUS_SEASON_DATA, std::move(packet)) { }

            void Read() override { }
        };
    }
}

#endif // ChallengeModePackets_h__
