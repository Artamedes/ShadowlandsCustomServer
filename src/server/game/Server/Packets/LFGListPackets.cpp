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

#include "AchievementMgr.h"
#include "CriteriaHandler.h"
#include "LFGListPackets.h"
#include "LFGPackets.h"
#include "World.h"
#include "Group.h"
#include "Player.h"
#include "ObjectAccessor.h"
#include "ObjectMgr.h"
#include "SocialMgr.h"

ByteBuffer& operator>>(ByteBuffer& data, WorldPackets::LFG::ListJoinEntry& join)
{
    data >> join.GroupFinderActivityId;
    data >> join.RequiredItemLevel;
    data >> join.RequiredHonorLevel;

    uint16 nameLen = data.ReadBits(8);
    uint16 commentLen = data.ReadBits(11);
    uint16 vclen = data.ReadBits(8);

    join.AutoAccept = data.ReadBit();
    join.IsPrivate = data.ReadBit();
    join.HasQuest = data.ReadBit();

    data.ResetBitPos();

    join.Name = data.ReadString(nameLen);
    join.Comment = data.ReadString(commentLen);
    join.VoiceChat = data.ReadString(vclen);

    if (join.HasQuest)
        data >> join.QuestId;

    return data;
}

ByteBuffer& operator<<(ByteBuffer& data, WorldPackets::LFG::ListJoinEntry const& join)
{
    data << uint32(join.GroupFinderActivityId);
    data << float(join.RequiredItemLevel);
    data << uint32(join.RequiredHonorLevel);

    data.WriteBits(join.Name.length(), 8);
    data.WriteBits(join.Comment.length(), 11);
    data.WriteBits(join.VoiceChat.length(), 8);
    data.WriteBit(join.AutoAccept);
    data.WriteBit(join.IsPrivate);
    data.WriteBit(join.HasQuest);
    data.FlushBits();
    data.WriteString(join.Name);
    data.WriteString(join.Comment);
    data.WriteString(join.VoiceChat);

    if (join.HasQuest)
        data << uint32(join.QuestId);

    return data;
}

void WorldPackets::LFG::ListSearchEntry::Initialize(lfg::LFGListEntry* entry, Player* searcher)
{
    //ApplicationTicket = *(entry->GetRideTicket());
    //JoinRequest = *(entry->GetJoinEntry());
    //VirtualRealmAddress = GetVirtualRealmAddress();
    //
    //Group* group = entry->GetGroup();
    //if (!group)
    //    return;
    //
    //ObjectGuid guid = group->GetLeaderGUID();
    //
    //LeaderGUID = guid;
    //LastTouchedAnyGUID = guid;
    //LastTouchedNameGUID = guid;
    //LastTouchedCommentGUID = guid;
    //LastTouchedVoiceChatGUID = guid;
    //
    //PartyGUID = group->GetGUID();
    //
    ////ToDo
    ///*BNetFriends, AppStatus*/    
    //
    //Members.reserve(group->GetMemberSlots().size());
    //
    //for (Group::MemberSlot const& slot : group->GetMemberSlots())
    //{
    //    if (searcher)
    //    {
    //        if (searcher->GetSocial()->HasFriend(slot.guid))
    //            CharacterFriends.push_back(slot.guid);
    //
    //        if (Player* guildMater = ObjectAccessor::FindConnectedPlayer(slot.guid))
    //            if (searcher->GetGuildId() && searcher->GetGuildId() == guildMater->GetGuildId())
    //                GuildMates.push_back(slot.guid);
    //    }
    //
    //    Members.emplace_back(slot._class, group->GetLfgRoles(slot.guid));
    //}   
}

ByteBuffer& operator>>(ByteBuffer& data, WorldPackets::LFG::ListMemberEntry& entry)
{
    data >> entry.Class;
    data >> entry.Role;

    return data;
}

ByteBuffer& operator<<(ByteBuffer& data, WorldPackets::LFG::ListMemberEntry const& entry)
{
    data << uint8(entry.Class);
  //  data << uint8(sLFGListMgr->PlayerRole2TalentRole(entry.Role));

    return data;
}

ByteBuffer& operator<<(ByteBuffer& data, WorldPackets::LFG::ListSearchEntry const& entry)
{
    data << entry.ApplicationTicket;
    data << uint32(entry.SequenceNum);

    data << entry.LeaderGUID;
    data << entry.LastTouchedAnyGUID;
    data << entry.LastTouchedNameGUID;
    data << entry.LastTouchedCommentGUID;
    data << entry.LastTouchedVoiceChatGUID;

    data << uint32(entry.VirtualRealmAddress);

    data << uint32(entry.BNetFriends.size());
    data << uint32(entry.CharacterFriends.size());
    data << uint32(entry.GuildMates.size());
    data << uint32(entry.Members.size());

    data << uint32(entry.CompletedEncounters);
    data << uint32(entry.ApplicationTicket.Time);
    data << uint8(entry.AppStatus);

    data << entry.PartyGUID;
    
    for (ObjectGuid const& entryG : entry.BNetFriends)
        data << entryG;

    for (ObjectGuid const& entryG : entry.CharacterFriends)
        data << entryG;

    for (ObjectGuid const& entryG : entry.GuildMates)
        data << entryG;

    for (WorldPackets::LFG::ListMemberEntry const& entryM : entry.Members)
        data << entryM;

    data << entry.JoinRequest;

    return data;
}


ByteBuffer& operator>>(ByteBuffer& data, WorldPackets::LFG::ListActivityEntry& entry)
{
    data >> entry.GroupFinderActivityId;
    data >> entry.LockStatus;

    return data;
}

ByteBuffer& operator<<(ByteBuffer& data, WorldPackets::LFG::ListActivityEntry const& entry)
{
    data << uint32(entry.GroupFinderActivityId);
    data << uint32(entry.LockStatus);

    return data;
}

void WorldPackets::LFG::ListInviteApplicant::Read()
{
    _worldPacket >> LFGListRideTicket >> ApplicationRideTicket;

    uint32 countMembers = _worldPacket.read<uint32>();
    for (uint32 i = 0; i < countMembers; i++) 
    {
        WorldPackets::LFG::ListInviteApplicant::PlayerRoles member;
        _worldPacket >> member.PlayerGUID;
        _worldPacket >> member.Role;
        Members.push_back(member);
    }
}

void WorldPackets::LFG::ListDeclineApplicant::Read()
{
    _worldPacket >> LFGListRideTicket >> ApplicationRideTicket;
}

void WorldPackets::LFG::ListApplyToGroup::Read()
{
    _worldPacket >> RideTicket;
    _worldPacket >> GroupFinderActivityId;
    _worldPacket >> Role;

    uint16 len = _worldPacket.ReadBits(8);
    _worldPacket.ResetBitPos();
    Comment = _worldPacket.ReadString(len);
}

void WorldPackets::LFG::ListCancelApplication::Read()
{
    _worldPacket >> RideTicket;
}

void WorldPackets::LFG::ListJoin::Read()
{
    _worldPacket >> JoinRequest;
}

void WorldPackets::LFG::ListInviteResponse::Read()
{
    _worldPacket >> RideTicket;
    Accept = _worldPacket.ReadBit();
    _worldPacket.ResetBitPos();
}

void WorldPackets::LFG::ListLeave::Read()
{
    _worldPacket >> RideTicket;
}

void WorldPackets::LFG::ListUpdateRequest::Read()
{
    _worldPacket >> Ticket >> LFGListJoinRequest;
}

void WorldPackets::LFG::ListSearch::Read()
{
    uint8 len = _worldPacket.ReadBits(6);
    _worldPacket >> GroupFinderCategoryId;
    _worldPacket >> SubActivityGroupID;
    _worldPacket >> LFGListFilter;
    _worldPacket >> LanguageFilter;

    uint32 entryCount, guidCount;
    _worldPacket >> entryCount;
    _worldPacket >> guidCount;

    SearchFilter = _worldPacket.ReadString(len);

    for (uint32 i = 0; i < entryCount; ++i)
    {
        LFG::ListActivityEntry entry;
        _worldPacket >> entry;
        Entrys.push_back(entry);
    }

    for (uint32 i = 0; i < guidCount; ++i)
    {
        ObjectGuid guid;
        _worldPacket >> guid;
        unkGuides.push_back(guid);
    }
}

WorldPacket const* WorldPackets::LFG::ListSearchResults::Write()
{
    uint32 count = Entrys.size();
    _worldPacket << uint16(count);

   // if (count > LFG_LIST_MAX_SEARCH_RESULT) //Blizzard only show 100 premade checked in sniff
   //     count = LFG_LIST_MAX_SEARCH_RESULT;

    _worldPacket << uint32(count);
    for (uint8 i = 0; i < count; i++)
        _worldPacket << Entrys[i];

    return &_worldPacket;
}

WorldPacket const* WorldPackets::LFG::ListJoinResult::Write()
{
    _worldPacket << RideTicket;
    _worldPacket << uint8(Status);
    _worldPacket << uint8(Result);

    return &_worldPacket;
}

WorldPacket const* WorldPackets::LFG::ListUpdateStatus::Write()
{
    _worldPacket << RideTicket;
    _worldPacket << uint32(RemainingTime);
    _worldPacket << uint8(ResultId);
    _worldPacket << LFGListJoinRequest;
    _worldPacket.WriteBit(Listed);
    _worldPacket.FlushBits();
    return &_worldPacket;
}

WorldPacket const* WorldPackets::LFG::ListSearchStatus::Write()
{
    _worldPacket << RideTicket;
    _worldPacket << uint8(Unk1);
    _worldPacket.WriteBit(UnkBit);
    _worldPacket.FlushBits();
    return &_worldPacket;
}

WorldPacket const* WorldPackets::LFG::ListUpdateBlacklist::Write()
{
    _worldPacket << uint32(Entrys.size());
    for (auto& e : Entrys)    
        _worldPacket << e;    

    return &_worldPacket;
}

WorldPacket const* WorldPackets::LFG::ListApplicantGroupInvite::Write()
{
    _worldPacket << ApplicationRideTicket;
    _worldPacket << LFGListRideTicket;
    _worldPacket << uint32(InviteExpireTimer);
    _worldPacket << uint8(ResultId);
    _worldPacket << uint8(RoleMask);
    _worldPacket.WriteBits(Status, 4);
    _worldPacket.FlushBits();
    return &_worldPacket;
}

WorldPacket const* WorldPackets::LFG::ListApplyForGroupResult::Write()
{
    _worldPacket << ApplicationRideTicket;
    _worldPacket << LFGListRideTicket;
    _worldPacket << uint32(RemainingTimeoutTime);
    _worldPacket << uint8(ResultId);
    _worldPacket << uint8(Role);

    _worldPacket << LFGListEntry;
    _worldPacket.WriteBits(Status, 4);
    _worldPacket.FlushBits();
    return &_worldPacket;
}

WorldPacket const* WorldPackets::LFG::ListApplicantListUpdate::Write()
{
    //_worldPacket << *(entry->GetRideTicket());
    //_worldPacket << uint32(ApplicantInfos.size());
    //_worldPacket << uint32(Result);
    //
    //for (lfg::ApplicationSlot* slot : ApplicantInfos)
    //{
    //    uint32 countPlayers = uint32(slot->Listed ? slot->Members.size() : 0);
    //    _worldPacket << slot->Ticket;
    //    _worldPacket << slot->ApplierGUID;
    //    _worldPacket << uint32(countPlayers);
    //
    //    Player* memberPlr = nullptr;
    //    if (countPlayers > 0)
    //    {
    //        for (lfg::ApplicationSlotMember& member : slot->Members)
    //        {
    //            memberPlr = ObjectAccessor::FindConnectedPlayer(member.PlayerGUID);
    //            _worldPacket << member.PlayerGUID;
    //            _worldPacket << uint32(member.VirtualRealmAddress);
    //            _worldPacket << float(1.0f);// sLFGListMgr->GetPlayerItemLevelForActivity(entry->GetActivityEntry(), memberPlr));
    //            _worldPacket << uint32(memberPlr ? memberPlr->GetLevel() : 0);
    //            _worldPacket << uint32(memberPlr ? memberPlr->GetHonorLevel() : 0);
    //            _worldPacket << uint8(member.QueuedRoleMask);
    //            _worldPacket << uint8(member.AssignedRoleMask);
    //
    //            if (memberPlr)
    //            {
    //                _worldPacket << uint32(MAX_RANK);
    //                for (uint32 i = (ProvingGroundsRankCriteria)DAMAGER_BRONZE; i <= (ProvingGroundsRankCriteria)HEALER_GOLD; i++)
    //                {
    //                    _worldPacket << uint32(i);
    //                    _worldPacket << uint32(0); //1 If is achieved
    //                }
    //            }
    //            else
    //                _worldPacket << uint32(0);
    //        }
    //    }
    //
    //    _worldPacket.WriteBits(slot->Status, 4);
    //    _worldPacket.WriteBit(slot->Listed);
    //    _worldPacket.WriteBits(slot->Comment.length(), 8);
    //    _worldPacket.FlushBits();
    //    _worldPacket.WriteString(slot->Comment);
    //}
    return &_worldPacket;
}

WorldPacket const* WorldPackets::LFG::ListUpdateExpiration::Write()
{
    _worldPacket << Ticket;
    _worldPacket << uint32(TimeoutTime);
    _worldPacket << uint8(Type);
    return &_worldPacket;
}

WorldPacket const* WorldPackets::LFG::ListUpdateEntryStatus::Write()
{
    _worldPacket << uint32(Updates.size());
    for (ListUpdateEntry& entry : Updates)
    {
        _worldPacket << entry.Ticket;
        _worldPacket << uint32(entry.SequenceNum);
        _worldPacket << uint32(entry.Members.size());
        for (ListMemberEntry const& member : entry.Members)
        {
            _worldPacket << uint8(member.Class);
            _worldPacket << uint8(member.Role);
        }
        _worldPacket.WriteBit(!entry.LeaderGUID.IsEmpty());
        _worldPacket.WriteBit(entry.NewVirtualRealmAddress > 0);
        _worldPacket.WriteBit(entry.ChangeCompletedEncounters);
        _worldPacket.WriteBit(entry.Delisted);
        _worldPacket.WriteBit(entry.ChangeTitle);
        _worldPacket.WriteBit(entry.ChangeAny);
        _worldPacket.WriteBit(entry.ChangeName);
        _worldPacket.WriteBit(entry.ChangeComment);
        _worldPacket.WriteBit(entry.ChangeVoice);
        _worldPacket.WriteBit(entry.ChangeItemLevel);
        _worldPacket.WriteBit(entry.ChangeAutoAccept);
        _worldPacket.WriteBit(entry.ChangeHonorLevel);
        _worldPacket.WriteBit(entry.ChangePrivate);
        _worldPacket.FlushBits();

        _worldPacket << entry.LFGListJoinRequest;
        
        if (!entry.LeaderGUID.IsEmpty())
            _worldPacket << entry.LeaderGUID;
        if (entry.NewVirtualRealmAddress > 0)
            _worldPacket << uint32(entry.NewVirtualRealmAddress);
        if (entry.CompletedEncountersMask > 0)
            _worldPacket << uint32(entry.CompletedEncountersMask);
        if (entry.ChangeAny)
            _worldPacket << entry.LastTouchedAnyGUID;
        if (entry.ChangeName)
            _worldPacket << entry.LastTouchedNameGUID;
        if (entry.ChangeComment)
            _worldPacket << entry.LastTouchedCommentGUID;
        if (entry.ChangeVoice)
            _worldPacket << entry.LastTouchedVoiceChatGUID;
    }

    return &_worldPacket;
}
