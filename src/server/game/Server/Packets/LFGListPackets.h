/*
* Copyright (C) 2008-2019 TrinityCore <http://www.trinitycore.org/>
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

#ifndef LFGListPackets_h__
#define LFGListPackets_h__

#include "ObjectGuid.h"
#include "Packet.h"
#include "LFGPacketsCommon.h"

namespace lfg
{
    class LFGListEntry;
    struct ApplicationSlot;
}
namespace WorldPackets
{
    namespace LFG
    {
        struct RideTicket;

        struct ListActivityEntry
        {
            uint32 GroupFinderActivityId;
            uint32 LockStatus;
        };

        struct ListJoinEntry
        {
            uint32 GroupFinderActivityId;
            float  RequiredItemLevel;
            uint32 RequiredHonorLevel;

            bool AutoAccept = false;
            bool IsPrivate = false;
            bool HasQuest = false;

            std::string Name;
            std::string Comment;
            std::string VoiceChat;

            uint32 QuestId = 0;
        };

        struct ListMemberEntry
        {
            uint8 Class;
            uint8 Role;

        public:
            ListMemberEntry(uint8 _class, uint8 _role)
                : Class(_class), Role(_role) { }
        };

        struct ListSearchEntry
        {
            void Initialize(lfg::LFGListEntry* entry, Player* searcher);

            RideTicket ApplicationTicket;
            uint32 SequenceNum = 0;
            ObjectGuid LeaderGUID;
            ObjectGuid LastTouchedAnyGUID;
            ObjectGuid LastTouchedNameGUID;
            ObjectGuid LastTouchedCommentGUID;
            ObjectGuid LastTouchedVoiceChatGUID;
            uint32 VirtualRealmAddress;

            uint32 CompletedEncounters = 0;
            uint32 CreationTime = 0;
            uint8 AppStatus = 0;

            ObjectGuid PartyGUID;

            std::vector<ObjectGuid> BNetFriends;
            std::vector<ObjectGuid> CharacterFriends;
            std::vector<ObjectGuid> GuildMates;
            std::vector<ListMemberEntry> Members;

            ListJoinEntry JoinRequest;
        };

        class ListInviteApplicant final : public ClientPacket
        {
        public:
            struct PlayerRoles
            {
                ObjectGuid PlayerGUID;
                uint8 Role;
            };
            ListInviteApplicant(WorldPacket&& packet) : ClientPacket(CMSG_LFG_LIST_INVITE_APPLICANT, std::move(packet)) { }

            void Read() override;

            RideTicket LFGListRideTicket;
            RideTicket ApplicationRideTicket;
            std::vector<PlayerRoles> Members;
        };

        class ListDeclineApplicant final : public ClientPacket
        {
        public:
            ListDeclineApplicant(WorldPacket&& packet) : ClientPacket(CMSG_LFG_LIST_DECLINE_APPLICANT, std::move(packet)) { }

            void Read() override;

            RideTicket LFGListRideTicket;
            RideTicket ApplicationRideTicket;
        };

        class ListJoin final : public ClientPacket
        {
        public:
            ListJoin(WorldPacket&& packet) : ClientPacket(CMSG_LFG_LIST_JOIN, std::move(packet)) { }

            void Read() override;

            ListJoinEntry JoinRequest;
        };

        class ListUpdateRequest final : public ClientPacket
        {
        public:
            ListUpdateRequest(WorldPacket&& packet) : ClientPacket(CMSG_LFG_LIST_UPDATE_REQUEST, std::move(packet)) { }

            void Read() override;

            RideTicket Ticket;
            ListJoinEntry LFGListJoinRequest;
        };

        class ListInviteResponse final : public ClientPacket
        {
        public:
            ListInviteResponse(WorldPacket&& packet) : ClientPacket(CMSG_LFG_LIST_INVITE_RESPONSE, std::move(packet)) { }

            void Read() override;

            RideTicket RideTicket;
            bool Accept;
        };

        class ListApplyToGroup final : public ClientPacket
        {
        public:
            ListApplyToGroup(WorldPacket&& packet) : ClientPacket(CMSG_LFG_LIST_APPLY_TO_GROUP, std::move(packet)) { }

            void Read() override;

            RideTicket RideTicket;
            uint32 GroupFinderActivityId;
            uint8 Role;
            std::string Comment;
        };

        class ListCancelApplication final : public ClientPacket
        {
        public:
            ListCancelApplication(WorldPacket&& packet) : ClientPacket(CMSG_LFG_LIST_CANCEL_APPLICATION, std::move(packet)) { }

            void Read() override;

            RideTicket RideTicket;
        };

        class ListLeave final : public ClientPacket
        {
        public:
            ListLeave(WorldPacket&& packet) : ClientPacket(CMSG_LFG_LIST_LEAVE, std::move(packet)) { }

            void Read() override;

            RideTicket RideTicket;
        };

        class ListSearch final : public ClientPacket
        {
        public:
            ListSearch(WorldPacket&& packet) : ClientPacket(CMSG_LFG_LIST_SEARCH, std::move(packet)) { }

            void Read() override;

            uint32 GroupFinderCategoryId;
            uint32 SubActivityGroupID;
            uint32 LFGListFilter;
            uint32 LanguageFilter;

            std::string SearchFilter;

            std::vector<ListActivityEntry> Entrys;
            std::vector<ObjectGuid> unkGuides; // PartyMember?
        };

        class ListApplicantGroupInvite final : public WorldPackets::ServerPacket
        {
        public:
            ListApplicantGroupInvite() : WorldPackets::ServerPacket(SMSG_LFG_LIST_APPLICATION_STATUS_UPDATE, 42) { }

            WorldPacket const* Write() override;

            RideTicket ApplicationRideTicket;
            RideTicket LFGListRideTicket;
            uint32 InviteExpireTimer = 0;
            uint8 ResultId = 6;
            uint8 RoleMask;
            uint8 Status;
        };

        class ListApplyForGroupResult final : public WorldPackets::ServerPacket
        {
        public:
            ListApplyForGroupResult() : WorldPackets::ServerPacket(SMSG_LFG_LIST_APPLY_TO_GROUP_RESULT, 42) { }

            WorldPacket const* Write() override;

            RideTicket ApplicationRideTicket;
            RideTicket LFGListRideTicket;
            uint32 RemainingTimeoutTime;
            uint8 ResultId = 6;
            uint8 Role;
            ListSearchEntry LFGListEntry;
            uint8 Status;
        };

        class ListApplicantListUpdate final : public WorldPackets::ServerPacket
        {
        public:
            ListApplicantListUpdate() : WorldPackets::ServerPacket(SMSG_LFG_LIST_APPLICANT_LIST_UPDATE, 42) { }

            WorldPacket const* Write() override;
            lfg::LFGListEntry* entry;
            uint32 Result;
            std::vector<lfg::ApplicationSlot*> ApplicantInfos;
        };

        class ListUpdateExpiration final : public WorldPackets::ServerPacket
        {
        public:
            ListUpdateExpiration() : WorldPackets::ServerPacket(SMSG_LFG_LIST_UPDATE_EXPIRATION, 42) { }

            WorldPacket const* Write() override;
            RideTicket Ticket;
            uint32 TimeoutTime;
            uint8 Type;
        };

        class ListUpdateStatus final : public WorldPackets::ServerPacket
        {
        public:
            ListUpdateStatus() : WorldPackets::ServerPacket(SMSG_LFG_LIST_UPDATE_STATUS, 21) { }

            WorldPacket const* Write() override;

            RideTicket RideTicket;
            ListJoinEntry LFGListJoinRequest;
            uint32 RemainingTime;
            uint8 ResultId;
            bool Listed;
        };

        class ListSearchStatus final : public WorldPackets::ServerPacket
        {
        public:
            ListSearchStatus() : WorldPackets::ServerPacket(SMSG_LFG_LIST_SEARCH_STATUS, 21) { }

            WorldPacket const* Write() override;

            RideTicket RideTicket;
            uint8 Unk1;
            bool UnkBit;
        };

        class ListSearchResults final : public WorldPackets::ServerPacket
        {
        public:
            ListSearchResults() : WorldPackets::ServerPacket(SMSG_LFG_LIST_SEARCH_RESULTS, 6) { }

            WorldPacket const* Write() override;

            std::vector<ListSearchEntry> Entrys;
        };

        class ListJoinResult final : public WorldPackets::ServerPacket
        {
        public:
            ListJoinResult() : WorldPackets::ServerPacket(SMSG_LFG_LIST_JOIN_RESULT, 23) { }

            WorldPacket const* Write() override;

            RideTicket RideTicket;
            uint8 Status;
            uint8 Result;
        };

        class ListUpdateBlacklist final : public WorldPackets::ServerPacket
        {
        public:
            ListUpdateBlacklist() : WorldPackets::ServerPacket(SMSG_LFG_LIST_UPDATE_BLACKLIST, 4) { }

            WorldPacket const* Write() override;

            std::vector<ListActivityEntry> Entrys;
        };
        
        struct ListUpdateEntry
        {
        public:
            RideTicket Ticket;
            uint32 SequenceNum;
            std::vector<ListMemberEntry> Members;
            bool ChangeLeader;
            bool ChangeVirtualRealmAddress; // only true in combination with ChangeLeader // we dont need this until xrealms
            bool ChangeCompletedEncounters;
            bool Delisted;
            bool ChangeTitle = false;
            bool ChangeAny = false;
            bool ChangeName = false;
            bool ChangeComment = false;
            bool ChangeVoice = false;
            bool ChangeItemLevel = false;
            bool ChangeAutoAccept = false;
            bool ChangeHonorLevel = false; 
            bool ChangePrivate = false; 

            ListJoinEntry LFGListJoinRequest;

            ObjectGuid LeaderGUID;
            uint32 NewVirtualRealmAddress;
            uint32 CompletedEncountersMask;
            ObjectGuid LastTouchedAnyGUID;
            ObjectGuid LastTouchedNameGUID;
            ObjectGuid LastTouchedCommentGUID;
            ObjectGuid LastTouchedVoiceChatGUID;
        };

        class ListUpdateEntryStatus final : public WorldPackets::ServerPacket
        {
        public:
            ListUpdateEntryStatus() : WorldPackets::ServerPacket(SMSG_LFG_LIST_SEARCH_RESULTS_UPDATE, 53) { }

            WorldPacket const* Write() override;

            std::vector<ListUpdateEntry> Updates;
        };

    }
}
ByteBuffer& operator>>(ByteBuffer& data, WorldPackets::LFG::ListMemberEntry&);
ByteBuffer& operator<<(ByteBuffer& data, WorldPackets::LFG::ListMemberEntry const&);

ByteBuffer& operator<<(ByteBuffer& data, WorldPackets::LFG::ListSearchEntry const&);

ByteBuffer& operator>>(ByteBuffer& data, WorldPackets::LFG::ListJoinEntry&);
ByteBuffer& operator<<(ByteBuffer& data, WorldPackets::LFG::ListJoinEntry const&);

ByteBuffer& operator>>(ByteBuffer& data, WorldPackets::LFG::ListActivityEntry&);
ByteBuffer& operator<<(ByteBuffer& data, WorldPackets::LFG::ListActivityEntry const&);

#endif // LFGPackets_h__
