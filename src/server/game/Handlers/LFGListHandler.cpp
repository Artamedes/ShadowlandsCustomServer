///*
// * Copyright (C) 2008-2019 TrinityCore <http://www.trinitycore.org/>
// *
// * This program is free software; you can redistribute it and/or modify it
// * under the terms of the GNU General Public License as published by the
// * Free Software Foundation; either version 2 of the License, or (at your
// * option) any later version.
// *
// * This program is distributed in the hope that it will be useful, but WITHOUT
// * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
// * more details.
// *
// * You should have received a copy of the GNU General Public License along
// * with this program. If not, see <http://www.gnu.org/licenses/>.
// */
//
//#include "LFGMgr.h"
//#include "Opcodes.h"
//#include "WorldPacket.h"
//#include "WorldSession.h"
//#include "LFGPackets.h"
//#include "LFGListPackets.h"
//#include "DB2Stores.h"
//#include "LFG.h"
//#include "LFGListMgr.h"
//#include "Log.h"
//#include "Group.h"
//#include "Player.h"
//
//void WorldSession::HandleLfgListInviteApplicant(WorldPackets::LFG::ListInviteApplicant& packet)
//{
//    lfg::LFGListEntry* entry = sLFGListMgr->GetEntrybyID(packet.LFGListRideTicket.Id);
//
//    if (!entry)
//        return;
//
//    Group* group = entry->GetGroup();
//    if (group && (!group->IsAssistant(GetPlayer()->GetGUID())) && !group->IsLeader(GetPlayer()->GetGUID()))
//        return;
//
//    if (lfg::ApplicationSlot* slot = entry->GetApplicant(packet.ApplicationRideTicket.Id))
//    {
//        for (uint8 i = 0; i < slot->Members.size(); i++)
//        {
//            if (packet.Members[i].PlayerGUID != slot->Members[i].PlayerGUID)
//                continue;
//
//            slot->Members[i].AssignedRoleMask = packet.Members[i].Role;
//        }
//        entry->InviteApplication(*slot);
//    }
//}
//
//void WorldSession::HandleLfgListDeclineApplicant(WorldPackets::LFG::ListDeclineApplicant& packet) 
//{
//    auto entry = sLFGListMgr->GetEntrybyID(packet.LFGListRideTicket.Id);
//
//    if (!entry)
//        return;
//
//    auto group = entry->GetGroup();
//    if (group && (!group->IsAssistant(GetPlayer()->GetGUID())) && !group->IsLeader(GetPlayer()->GetGUID()))
//        return;
//
//    entry->DeclineApplication(packet.ApplicationRideTicket.Id);
//}
//void WorldSession::HandleLfgListGetStatus(WorldPacket& /*recvData*/)
//{
//    //Blizz don´t answer this WTF???
//}
//
//void WorldSession::HandleRequestLfgListBlacklist(WorldPacket& /*recvData*/)
//{
//    WorldPackets::LFG::ListUpdateBlacklist Blacklist;
//    for (uint32 activityId = 0; activityId < sGroupFinderActivityStore.GetNumRows(); ++activityId)
//    {
//        GroupFinderActivityEntry const* activityEntry = sGroupFinderActivityStore.LookupEntry(activityId);
//        if (!activityEntry)
//            continue;
//
//        WorldPackets::LFG::ListActivityEntry listActivityEntry;
//        listActivityEntry.LockStatus = 0;
//
//        if(_player->getLevel() < activityEntry->MinLevel)
//            listActivityEntry.LockStatus = (uint32)lfg::LFG_LOCKSTATUS_TOO_LOW_LEVEL;
//        else if (_player->getLevel() > 90 && (activityEntry->Difficulty == DIFFICULTY_3_MAN_SCENARIO_HC || activityEntry->Difficulty == DIFFICULTY_3_MAN_SCENARIO_N))
//            listActivityEntry.LockStatus = (uint32)lfg::LFG_LOCKSTATUS_TOO_HIGH_LEVEL;
//        else if (activityEntry->Difficulty > DIFFICULTY_NORMAL && _player->GetBoundInstance(activityEntry->MapID, Difficulty(activityEntry->Difficulty)))
//            listActivityEntry.LockStatus = (uint32)lfg::LFG_LOCKSTATUS_RAID_LOCKED;
//        else if (activityEntry->RequiredILvl < 350 && activityEntry->RequiredILvl > _player->GetAverageItemLevelEquipped())
//            listActivityEntry.LockStatus = (uint32)lfg::LFG_LOCKSTATUS_TOO_LOW_GEAR_SCORE;
//
//        if (listActivityEntry.LockStatus)
//        {
//            listActivityEntry.GroupFinderActivityId = activityEntry->ID;
//            Blacklist.Entrys.push_back(listActivityEntry);
//        }       
//    }
//
//    SendPacket(Blacklist.Write());
//}
//
//void WorldSession::HandleLfgListSearch(WorldPackets::LFG::ListSearch& packet)
//{
//    TC_LOG_INFO("lfg", "ListSearch: receive ActivityCategoryID = %u, parentActivityGroupID = %u, LFGListFilter = %u, LanguageFilter = %u", packet.GroupFinderCategoryId, packet.SubActivityGroupID, packet.LFGListFilter, packet.LanguageFilter);
//    TC_LOG_INFO("lfg", "ListSearch: receive searchFilter = %s", packet.SearchFilter.c_str());
//
//    WorldPackets::LFG::ListSearchResults result;
//
//    if (packet.GroupFinderCategoryId && packet.GroupFinderCategoryId < MAX_LFG_LIST_ACTIVITY_CATEGORY)
//        sLFGListMgr->GetFilteredList(GetPlayer(), result.Entrys, packet);
//
//    SendPacket(result.Write());
//}
//
//void WorldSession::HandleLfgListApplyToGroup(WorldPackets::LFG::ListApplyToGroup& packet)
//{
//    sLFGListMgr->OnPlayerApplyToGroup(GetPlayer(), packet);
//}
//
//void WorldSession::HandleLfgListCancelApplication(WorldPackets::LFG::ListCancelApplication& packet)
//{
//    if (lfg::LFGListEntry* entry = sLFGListMgr->GetEntrybyApplicationID(packet.RideTicket.Id))
//        entry->AbortApplication(packet.RideTicket.Id);
//}
//
//void WorldSession::HandleLfgListInviteResponse(WorldPackets::LFG::ListInviteResponse& packet)
//{
//    lfg::LFGListEntry* entry = sLFGListMgr->GetEntrybyApplicationID(packet.RideTicket.Id);
//    if (entry)
//    {
//        if(packet.Accept)
//            entry->AcceptApplication(packet.RideTicket.Id);
//        else
//            entry->AbortApplication(packet.RideTicket.Id);
//    } 
//}
//
//void WorldSession::HandleLfgListLeave(WorldPackets::LFG::ListLeave& packet)
//{
//    auto entry = sLFGListMgr->GetEntrybyID(packet.RideTicket.Id);
//
//    if (!entry)
//        return;
//
//    auto group = entry->GetGroup();
//    if (group && (!group->isRaidGroup() || !group->IsAssistant(GetPlayer()->GetGUID())) && !group->IsLeader(GetPlayer()->GetGUID()))
//        return;
//
//    sLFGListMgr->Remove(packet.RideTicket.Id, true, true);
//}
//
//void WorldSession::HandleLfgListUpdateRequest(WorldPackets::LFG::ListUpdateRequest& packet)
//{
//    auto entry = sLFGListMgr->GetEntrybyID(packet.Ticket.Id);
//
//    if (!entry)
//        return;
//
//    auto group = entry->GetGroup();
//    if (!group || !group->IsLeader(GetPlayer()->GetGUID()))
//        return;
//
//    sLFGListMgr->AutoInviteApplicantsIfPossible(packet.LFGListJoinRequest);
//    entry->UpdateJoin(std::move(packet.LFGListJoinRequest));
//}
//
//void WorldSession::HandleLfgListJoin(WorldPackets::LFG::ListJoin& packet)
//{
//    //Force Auto Accept update 
//    WorldPackets::LFG::ListJoinEntry JoinRequest = packet.JoinRequest;
//    JoinRequest.AutoAccept = GetPlayer()->IsAutoAccepted();
//    // only sent by leader while to start creating a premade group
//    sLFGListMgr->Join(GetPlayer(), JoinRequest);
//}
//
//
//void WorldSession::SendLfgListJoinResult(uint8 error, WorldPackets::LFG::RideTicket* ticket)
//{
//    WorldPackets::LFG::ListJoinResult result;
//
//    if (ticket)
//        result.RideTicket = *ticket;
//    else {
//        result.RideTicket.Time = time(nullptr);
//    }
//
//    result.RideTicket.Type = WorldPackets::LFG::RideType::PremadeGroupFinder2;
//    result.Status = error;
//
//    SendPacket(result.Write());
//}
//
//void WorldSession::SendLfgListApplicantGroupInviteResponse(lfg::LFGListEntry* entry, lfg::ApplicationSlot& slot)
//{
//    WorldPackets::LFG::ListApplicantGroupInvite inviteResponse;
//
//    inviteResponse.ApplicationRideTicket = slot.Ticket;
//    inviteResponse.LFGListRideTicket = *(entry->GetRideTicket());
//    inviteResponse.ResultId = slot.Error;
//    for (lfg::ApplicationSlotMember& member : slot.Members)
//        if (member.PlayerGUID == GetPlayer()->GetGUID())
//        {
//            inviteResponse.RoleMask = member.AssignedRoleMask;
//            break;
//        }
//    inviteResponse.Status = slot.Status;
//
//    SendPacket(inviteResponse.Write());
//}
//
//void WorldSession::SendLfgListApplyForGroupResult(lfg::LFGListEntry* entry, lfg::ApplicationSlot& slot)
//{
//    WorldPackets::LFG::ListApplyForGroupResult groupResponse;
//
//    groupResponse.ApplicationRideTicket = slot.Ticket;
//    groupResponse.LFGListRideTicket = *(entry->GetRideTicket());
//    groupResponse.LFGListEntry.Initialize(entry, _player);
//    groupResponse.RemainingTimeoutTime = slot.Timeout;
//    //groupResponse.ResultId = ; //Error_:CODE
//    groupResponse.Role = 0;
//    groupResponse.Status = slot.Status;
//
//    SendPacket(groupResponse.Write());
//}
//
