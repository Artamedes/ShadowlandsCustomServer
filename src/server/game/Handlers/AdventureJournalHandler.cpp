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

#include "WorldSession.h"
#include "AdventureJournalPackets.h"
#include "DB2Stores.h"
#include "GossipDef.h"
#include "ObjectMgr.h"
#include "Player.h"

void WorldSession::HandleAdventureJournalOpenQuest(WorldPackets::AdventureJournal::AdventureJournalOpenQuest& openQuest)
{
    if (ChrClassUIDisplayEntry const* uiDisplay = sDB2Manager.GetUiDisplayForClass(Classes(_player->GetClass())))
        if (!_player->MeetPlayerCondition(uiDisplay->AdvGuidePlayerConditionID))
            return;

    AdventureJournalEntry const* adventureJournal = sAdventureJournalStore.LookupEntry(openQuest.AdventureJournalID);
    if (!adventureJournal)
        return;

    if (!_player->MeetPlayerCondition(adventureJournal->PlayerConditionID))
        return;

    Quest const* quest = sObjectMgr->GetQuestTemplate(adventureJournal->QuestID);
    if (!quest)
        return;

    if (_player->CanTakeQuest(quest, true))
        _player->PlayerTalkClass->SendQuestGiverQuestDetails(quest, _player->GetGUID(), true, false);
}

void WorldSession::HandleAdventureJournalUpdateSuggestions(WorldPackets::AdventureJournal::AdventureJournalUpdateSuggestions& updateSuggestions)
{
  //  if (ChrClassUIDisplayEntry const* uiDisplay = sDB2Manager.GetUiDisplayForClass(Classes(_player->GetClass())))
  //      if (!_player->MeetPlayerCondition(uiDisplay->AdvGuidePlayerConditionID))
  //          return;

    WorldPackets::AdventureJournal::AdventureJournalDataResponse response;
    response.OnLevelUp = updateSuggestions.OnLevelUp;

    //for (AdventureJournalEntry const* adventureJournal : sAdventureJournalStore)
    //{
    //    if (_player->MeetPlayerCondition(adventureJournal->PlayerConditionID))
    //    {
    //        WorldPackets::AdventureJournal::AdventureJournalEntry adventureJournalData;
    //        adventureJournalData.AdventureJournalID = int32(adventureJournal->ID);
    //        adventureJournalData.Priority = int32(adventureJournal->PriorityMax);
    //        response.Entries.push_back(adventureJournalData);
    //    }
    //}
    // pig for now - just filling out stupid trinity entries

    response.Entries.resize(11);
    response.Entries[0].AdventureJournalID = 27;
    response.Entries[0].Priority = 7;
    response.Entries[1].AdventureJournalID = 118;
    response.Entries[1].Priority = 3;
    response.Entries[2].AdventureJournalID = 196;
    response.Entries[2].Priority = 2;
    response.Entries[3].AdventureJournalID = 197;
    response.Entries[3].Priority = 6;
    response.Entries[4].AdventureJournalID = 208;
    response.Entries[4].Priority = 0;
    response.Entries[5].AdventureJournalID = 219;
    response.Entries[5].Priority = 1;
    response.Entries[6].AdventureJournalID = 540;
    response.Entries[6].Priority = 9;
    response.Entries[7].AdventureJournalID = 560;
    response.Entries[7].Priority = 7;
    response.Entries[8].AdventureJournalID = 567;
    response.Entries[8].Priority = 10;
    response.Entries[9].AdventureJournalID = 568;
    response.Entries[9].Priority = 14;
    response.Entries[10].AdventureJournalID = 365;
    response.Entries[10].Priority = 9;

    SendPacket(response.Write());
}
