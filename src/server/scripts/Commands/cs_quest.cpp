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

/* ScriptData
Name: quest_commandscript
%Complete: 100
Comment: All quest related commands
Category: commandscripts
EndScriptData */

#include "ScriptMgr.h"
#include "Chat.h"
#include "ChatCommand.h"
#include "DatabaseEnv.h"
#include "DB2Stores.h"
#include "DisableMgr.h"
#include "ObjectMgr.h"
#include "Player.h"
#include "RBAC.h"
#include "ReputationMgr.h"
#include "World.h"
#include "QueryPackets.h"
#include "GossipDef.h"

#if TRINITY_COMPILER == TRINITY_COMPILER_GNU
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif

struct QuestPoiData
{
    bool RetrieveData = true;
    float _poix;
    float _poiy;
    QuestPOIData PoiData;

    // internal fields
    uint32 CurrentObjectiveID = 0;

    void Reset(uint32 questId)
    {
        PoiData = QuestPOIData();
        PoiData.QuestID = questId;
        RetrieveData = true;
    }
};

std::unordered_map<ObjectGuid::LowType, QuestPoiData> questPoiData;

class quest_playerscript : public PlayerScript
{
    public:
        quest_playerscript() : PlayerScript("quest_playerscript") { }

        template <class T>
        static std::string GetTextFromAny(std::string A, T any)
        {
            std::ostringstream ss;
            ss << A << any;
            return ss.str();
        }

        enum Senders
        {
            SenderNone = 0,
            SenderObjectiveId = 40,
            SenderRemovePoint = 41,
            SenderAddPoint    = 42,
        };

        enum Actions
        {
            Commit = 1,
            Quest,
            PoiX,
            PoiY,
            SetCompletePOI,
            Back,
        };

        static void OnGossipHello(Player* player)
        {
            ClearGossipMenuFor(player);
            auto& Data = questPoiData[player->GetGUID().GetCounter()];
            Data.CurrentObjectiveID = 0;
            auto quest = sObjectMgr->GetQuestTemplate(Data.PoiData.QuestID);

            AddGossipItemFor(player, GossipOptionIcon::None, GetTextFromAny(quest ? quest->GetLogTitle() : "Plz set quest: ", Data.PoiData.QuestID), 0, Quest, "Editing this will reset all data", 0, true);
            AddGossipItemFor(player, GossipOptionIcon::None, GetTextFromAny("Set PoiX (Unimportant): ", Data._poix), 0, PoiX, "", 0, true);
            AddGossipItemFor(player, GossipOptionIcon::None, GetTextFromAny("Set PoiY (Unimportant): ", Data._poiy), 0, PoiY, "", 0, true);
            AddGossipItemFor(player, GossipOptionIcon::None, "Set Complete POI here", SenderNone, SetCompletePOI);

            if (quest)
            {
                for (auto const& objective : quest->GetObjectives())
                {
                    AddGossipItemFor(player, GossipOptionIcon::None, GetTextFromAny("Edit Objective POI for quest_objective: ", objective.ID), SenderObjectiveId, objective.ID);
                }
            }

            AddGossipItemFor(player, GossipOptionIcon::None, "Commit", 0, Commit, "Are you sure you're ready to commit?", 0, false);
            SendGossipMenuFor(player, 1, player);
            player->PlayerTalkClass->GetGossipMenu().SetMenuId(62767262);
        }


        void DisplayObjectiveData(Player* player)
        {
            auto& Data = questPoiData[player->GetGUID().GetCounter()];
            auto quest = sObjectMgr->GetQuestTemplate(Data.PoiData.QuestID);
            if (Data.CurrentObjectiveID > 0 && quest)
            {
                for (auto const& objective : quest->GetObjectives())
                {
                    if (objective.ID == Data.CurrentObjectiveID)
                    {
                        AddGossipItemFor(player, GossipOptionIcon::None, GetTextFromAny("Edit Objective POI for quest_objective: ", objective.ID), SenderObjectiveId, objective.ID);
                        for (int i = 0; i < Data.PoiData.Blobs.size(); ++i)
                        {
                            auto const& itr = Data.PoiData.Blobs[i];

                            if (itr.QuestObjectiveID == objective.ID)
                            {
                                for (int x = 0; x < itr.Points.size(); ++x)
                                {
                                    auto const& point = itr.Points[x];

                                    std::ostringstream ss;
                                    ss << "[" << x << "] Remove Point [X: " << point.X << " Y: " << point.Y << " Z: " << point.Z << "]";

                                    AddGossipItemFor(player, GossipOptionIcon::None, ss.str(), SenderRemovePoint, x);
                                }
                                break;
                            }
                        }
                        AddGossipItemFor(player, GossipOptionIcon::None, "Add Point at current position", SenderAddPoint, 0);
                        AddGossipItemFor(player, GossipOptionIcon::None, "back", 0, Back);
                        SendGossipMenuFor(player, 1, player);
                        break;
                    }
                }
            }
        }

        void OnGossipSelect(Player* player, uint32 menuId, uint32 sender, uint32 action) override
        {
            if (menuId != 62767262)
                return;

            ClearGossipMenuFor(player);

            auto& Data = questPoiData[player->GetGUID().GetCounter()];

            bool handled = false;

            switch (sender)
            {
                case SenderAddPoint:
                {
                    bool found = false;
                    for (int i = 0; i < Data.PoiData.Blobs.size(); ++i)
                    {
                        auto& itr = Data.PoiData.Blobs[i];

                        if (itr.QuestObjectiveID == Data.CurrentObjectiveID)
                        {
                            ChatHandler(player).PSendSysMessage("added poi point for objective %u", Data.CurrentObjectiveID);
                            itr.Points.push_back(QuestPOIBlobPoint(player->GetPositionX(), player->GetPositionY(), player->GetPositionZ()));
                            found = true;
                            break;
                        }
                    }
                    if (!found)
                    {
                        Data.PoiData.Blobs.emplace_back();
                        auto& itr = Data.PoiData.Blobs.back();

                        itr.ObjectiveIndex = 0;
                        itr.MapID = player->GetMapId();
                        itr.QuestObjectiveID = Data.CurrentObjectiveID;

                        int32 uiMapId = 0;
                        // try to retrieve to ui map id
                        DB2Manager::GetUiMapPosition(player->GetPositionX(), player->GetPositionY(), player->GetPositionZ(), player->GetMapId(), 0, 0, 0, UI_MAP_SYSTEM_ADVENTURE, false, &uiMapId);
                        itr.UiMapID = uiMapId;
                        itr.Points.push_back(QuestPOIBlobPoint(player->GetPositionX(), player->GetPositionY(), player->GetPositionZ()));
                        ChatHandler(player).PSendSysMessage("added poi point and blob for objective %u", Data.CurrentObjectiveID);
                    }
                    DisplayObjectiveData(player);
                    handled = true;
                    break;
                }
                case SenderRemovePoint:
                {
                    auto quest = sObjectMgr->GetQuestTemplate(Data.PoiData.QuestID);
                    for (int i = 0; i < Data.PoiData.Blobs.size(); ++i)
                    {
                        auto& itr = Data.PoiData.Blobs[i];

                        if (itr.QuestObjectiveID == Data.CurrentObjectiveID)
                        {
                            if (action < itr.Points.size())
                                itr.Points.erase(itr.Points.begin() + action);
                            ChatHandler(player).PSendSysMessage("remove poi point %u and blob for objective %u", action, Data.CurrentObjectiveID);
                        }
                        break;
                    }
                    DisplayObjectiveData(player);
                    handled = true;
                    break;
                }
                case SenderObjectiveId:
                {
                    Data.CurrentObjectiveID = action;
                    DisplayObjectiveData(player);
                    return;
                }
            }

            switch (action)
            {
                case SetCompletePOI:
                {
                    bool found = false;
                    for (int i = 0; i < Data.PoiData.Blobs.size(); ++i)
                    {
                        auto& itr = Data.PoiData.Blobs[i];

                        if (itr.ObjectiveIndex == -1)
                        {
                            found = true;
                            itr.Points.clear();
                            itr.Points.push_back(QuestPOIBlobPoint(player->GetPositionX(), player->GetPositionY(), player->GetPositionZ()));
                            ChatHandler(player).PSendSysMessage("Updated complete poi");
                            break;
                        }
                    }

                    if (!found)
                    {
                        Data.PoiData.Blobs.emplace_back();
                        auto& itr = Data.PoiData.Blobs.back();

                        itr.ObjectiveIndex = -1;
                        itr.MapID = player->GetMapId();

                        int32 uiMapId = 0;
                        // try to retrieve to ui map id
                        DB2Manager::GetUiMapPosition(player->GetPositionX(), player->GetPositionY(), player->GetPositionZ(), player->GetMapId(), 0, 0, 0, UI_MAP_SYSTEM_ADVENTURE, false, &uiMapId);
                        itr.UiMapID = uiMapId;
                        itr.Points.push_back(QuestPOIBlobPoint(player->GetPositionX(), player->GetPositionY(), player->GetPositionZ()));
                        ChatHandler(player).PSendSysMessage("set complete poi");
                    }

                    break;
                }
                case Commit:
                {
                    uint32 questId = Data.PoiData.QuestID;
                    WorldDatabase.PQuery("DELETE FROM quest_poi WHERE QuestID = %u", Data.PoiData.QuestID);
                    WorldDatabase.PQuery("DELETE FROM quest_poi_points WHERE QuestID = %u", Data.PoiData.QuestID);
                    WorldDatabase.PQuery("UPDATE quest_template set PoiX = %f, PoiY = %f where id = %u", Data._poix, Data._poiy, questId);

                    for (int i = 0; i < Data.PoiData.Blobs.size(); ++i)
                    {
                        auto const& itr = Data.PoiData.Blobs[i];

                        for (int x = 0; x < itr.Points.size(); ++x)
                        {
                            auto const& point = itr.Points[x];

                            auto stmt = WorldDatabase.GetPreparedStatement(WORLD_INS_QUEST_POI_POINTS);
                            stmt->setInt32(0, questId);
                            stmt->setInt32(1, i); // Idx1
                            stmt->setInt32(2, x); // Idx2
                            stmt->setInt32(3, point.X); // X
                            stmt->setInt32(4, point.Y); // Y
                            stmt->setInt32(5, point.Z); // Z
                            WorldDatabase.Query(stmt);
                        }

                        auto stmt = WorldDatabase.GetPreparedStatement(WORLD_INS_QUEST_POI);
                        stmt->setInt32(0, questId);
                        stmt->setInt32(1, itr.BlobIndex); // BlobIndex
                        stmt->setInt32(2, i); // Idx1
                        stmt->setInt32(3, itr.ObjectiveIndex); // ObjectiveIndex
                        stmt->setInt32(4, itr.QuestObjectiveID); // QuestObjectiveID
                        stmt->setInt32(5, itr.QuestObjectID); // QuestObjectID
                        stmt->setInt32(6, itr.MapID); // MapID
                        stmt->setInt32(7, itr.UiMapID); // UiMapID
                        stmt->setInt32(8, itr.Priority); // Priority
                        stmt->setInt32(9, itr.Flags); // Flags
                        stmt->setInt32(10, itr.WorldEffectID); // WorldEffectID
                        stmt->setInt32(11, itr.PlayerConditionID); // PlayerConditionID
                        stmt->setInt32(12, itr.NavigationPlayerConditionID); // NavigationPlayerConditionID
                        stmt->setInt32(13, itr.SpawnTrackingID); // SpawnTrackingID
                        stmt->setInt32(14, itr.AlwaysAllowMergingBlobs); // AlwaysAllowMergingBlobs
                        WorldDatabase.Query(stmt);

                    }

                    sObjectMgr->LoadQuestPOI();

                    WorldPackets::Query::QuestPOIQueryResponse response;

                    if (player->FindQuestSlot(questId) != MAX_QUEST_LOG_SIZE)
                        if (QuestPOIData const* poiData = sObjectMgr->GetQuestPOIData(questId))
                            response.QuestPOIDataStats.push_back(poiData);

                    player->GetSession()->SendPacket(response.Write());

                    ChatHandler(player).SendSysMessage("Retake the quest for update POI");
                    break;
                }
            }

            if (!handled)
                OnGossipHello(player);
        }
        
        void OnGossipSelectCode(Player* player, uint32 menuId, uint32 sender, uint32 action, char const* code) override
        {
            if (menuId != 62767262)
                return;

            ClearGossipMenuFor(player);

            if (code)
            {
                auto& Data = questPoiData[player->GetGUID().GetCounter()];

                switch (action)
                {
                    case Quest:
                    {
                        Data.Reset(atol(code));
                        break;
                    }
                    case PoiX:
                    {
                        Data._poix = atof(code);
                        break;
                    }
                    case PoiY:
                    {
                        Data._poiy = atof(code);
                        break;
                    }
                }
            }
            OnGossipHello(player);
        }
};

class quest_commandscript : public CommandScript
{
public:
    quest_commandscript() : CommandScript("quest_commandscript") { }

    std::vector<ChatCommand> GetCommands() const override
    {
        static std::vector<ChatCommand> questCommandTable =
        {
            { "add",      rbac::RBAC_PERM_COMMAND_QUEST_ADD,      false, &HandleQuestAdd,      "" },
            { "complete", rbac::RBAC_PERM_COMMAND_QUEST_COMPLETE, false, &HandleQuestComplete, "" },
            { "remove",   rbac::RBAC_PERM_COMMAND_QUEST_REMOVE,   false, &HandleQuestRemove,   "" },
            { "reward",   rbac::RBAC_PERM_COMMAND_QUEST_REWARD,   false, &HandleQuestReward,   "" },
            { "modpoi",   rbac::RBAC_PERM_COMMAND_DEV,            false, &HandleQuestModPoi,   "" },
        };
        static std::vector<ChatCommand> commandTable =
        {
            { "quest", rbac::RBAC_PERM_COMMAND_QUEST,  false, nullptr, "", questCommandTable },
        };
        return commandTable;
    }

    static bool HandleQuestModPoi(ChatHandler* handler, Optional<uint32> questId)
    {
        auto player = handler->GetPlayer();

        questPoiData[player->GetGUID().GetCounter()].Reset(questId.value_or(0));
        quest_playerscript::OnGossipHello(player);

        return true;
    }

    static bool HandleQuestAdd(ChatHandler* handler, char const* args)
    {
        Player* player = handler->getSelectedPlayerOrSelf();
        if (!player)
        {
            handler->SendSysMessage(LANG_NO_CHAR_SELECTED);
            handler->SetSentErrorMessage(true);
            return false;
        }

        // .addquest #entry'
        // number or [name] Shift-click form |color|Hquest:quest_id:quest_level:min_level:max_level:scaling_faction|h[name]|h|r
        char* cId = handler->extractKeyFromLink((char*)args, "Hquest");
        if (!cId)
            return false;

        uint32 entry = atoul(cId);

        Quest const* quest = sObjectMgr->GetQuestTemplate(entry);

        if (!quest || DisableMgr::IsDisabledFor(DISABLE_TYPE_QUEST, entry, nullptr))
        {
            handler->PSendSysMessage(LANG_COMMAND_QUEST_NOTFOUND, entry);
            handler->SetSentErrorMessage(true);
            return false;
        }

        // check item starting quest (it can work incorrectly if added without item in inventory)
        ItemTemplateContainer const& itc = sObjectMgr->GetItemTemplateStore();
        auto itr = std::find_if(std::begin(itc), std::end(itc), [quest](ItemTemplateContainer::value_type const& value)
        {
            return value.second.GetStartQuest() == quest->GetQuestId();
        });

        if (itr != std::end(itc))
        {
            handler->PSendSysMessage(LANG_COMMAND_QUEST_STARTFROMITEM, entry, itr->first);
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (player->IsActiveQuest(entry))
            return false;

        // ok, normal (creature/GO starting) quest
        if (player->CanAddQuest(quest, true))
            player->AddQuestAndCheckCompletion(quest, nullptr);

        return true;
    }

    static bool HandleQuestRemove(ChatHandler* handler, char const* args)
    {
        Player* player = handler->getSelectedPlayer();
        if (!player)
        {
            handler->SendSysMessage(LANG_NO_CHAR_SELECTED);
            handler->SetSentErrorMessage(true);
            return false;
        }

        // .removequest #entry'
        // number or [name] Shift-click form |color|Hquest:quest_id:quest_level:min_level:max_level:scaling_faction|h[name]|h|r
        char* cId = handler->extractKeyFromLink((char*)args, "Hquest");
        if (!cId)
            return false;

        uint32 entry = atoul(cId);

        Quest const* quest = sObjectMgr->GetQuestTemplate(entry);

        if (!quest)
        {
            handler->PSendSysMessage(LANG_COMMAND_QUEST_NOTFOUND, entry);
            handler->SetSentErrorMessage(true);
            return false;
        }

        QuestStatus oldStatus = player->GetQuestStatus(entry);

        if (player->GetQuestStatus(entry) != QUEST_STATUS_NONE)
        {
            // remove all quest entries for 'entry' from quest log
            for (uint8 slot = 0; slot < MAX_QUEST_LOG_SIZE; ++slot)
            {
                uint32 logQuest = player->GetQuestSlotQuestId(slot);
                if (logQuest == entry)
                {
                    player->SetQuestSlot(slot, 0);

                    // we ignore unequippable quest items in this case, its' still be equipped
                    player->TakeQuestSourceItem(logQuest, false);

                    if (quest->HasFlag(QUEST_FLAGS_FLAGS_PVP))
                    {
                        player->pvpInfo.IsHostile = player->pvpInfo.IsInHostileArea || player->HasPvPForcingQuest();
                        player->UpdatePvPState();
                    }
                }
            }
            player->RemoveActiveQuest(entry, false);
            player->RemoveRewardedQuest(entry);

            sScriptMgr->OnQuestStatusChange(player, entry);
            sScriptMgr->OnQuestStatusChange(player, quest, oldStatus, QUEST_STATUS_NONE);

            handler->SendSysMessage(LANG_COMMAND_QUEST_REMOVED);
            return true;
        }
        else
        {
            handler->PSendSysMessage(LANG_COMMAND_QUEST_NOTFOUND, entry);
            handler->SetSentErrorMessage(true);
            return false;
        }
    }

    static bool HandleQuestComplete(ChatHandler* handler, char const* args)
    {
        Player* player = handler->getSelectedPlayerOrSelf();
        if (!player)
        {
            handler->SendSysMessage(LANG_NO_CHAR_SELECTED);
            handler->SetSentErrorMessage(true);
            return false;
        }

        // .quest complete #entry
        // number or [name] Shift-click form |color|Hquest:quest_id:quest_level:min_level:max_level:scaling_faction|h[name]|h|r
        char* cId = handler->extractKeyFromLink((char*)args, "Hquest");
        if (!cId)
            return false;

        uint32 entry = atoul(cId);

        Quest const* quest = sObjectMgr->GetQuestTemplate(entry);

        // If player doesn't have the quest
        if (!quest || player->GetQuestStatus(entry) == QUEST_STATUS_NONE
            || DisableMgr::IsDisabledFor(DISABLE_TYPE_QUEST, entry, nullptr))
        {
            handler->PSendSysMessage(LANG_COMMAND_QUEST_NOTFOUND, entry);
            handler->SetSentErrorMessage(true);
            return false;
        }

        for (uint32 i = 0; i < quest->Objectives.size(); ++i)
        {
            QuestObjective const& obj = quest->Objectives[i];

            switch (obj.Type)
            {
                case QUEST_OBJECTIVE_ITEM:
                {
                    uint32 curItemCount = player->GetItemCount(obj.ObjectID, true);
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, obj.ObjectID, obj.Amount - curItemCount);
                    if (msg == EQUIP_ERR_OK)
                    {
                        Item* item = player->StoreNewItem(dest, obj.ObjectID, true);
                        player->SendNewItem(item, obj.Amount - curItemCount, true, false);
                    }
                    break;
                }
                case QUEST_OBJECTIVE_MONSTER:
                {
                    if (CreatureTemplate const* creatureInfo = sObjectMgr->GetCreatureTemplate(obj.ObjectID))
                        for (uint16 z = 0; z < obj.Amount; ++z)
                            player->KilledMonster(creatureInfo, ObjectGuid::Empty);
                    break;
                }
                case QUEST_OBJECTIVE_GAMEOBJECT:
                {
                    for (uint16 z = 0; z < obj.Amount; ++z)
                        player->KillCreditGO(obj.ObjectID);
                    break;
                }
                case QUEST_OBJECTIVE_MIN_REPUTATION:
                {
                    uint32 curRep = player->GetReputationMgr().GetReputation(obj.ObjectID);
                    if (curRep < uint32(obj.Amount))
                        if (FactionEntry const* factionEntry = sFactionStore.LookupEntry(obj.ObjectID))
                            player->GetReputationMgr().SetReputation(factionEntry, obj.Amount);
                    break;
                }
                case QUEST_OBJECTIVE_MAX_REPUTATION:
                {
                    uint32 curRep = player->GetReputationMgr().GetReputation(obj.ObjectID);
                    if (curRep > uint32(obj.Amount))
                        if (FactionEntry const* factionEntry = sFactionStore.LookupEntry(obj.ObjectID))
                            player->GetReputationMgr().SetReputation(factionEntry, obj.Amount);
                    break;
                }
                case QUEST_OBJECTIVE_MONEY:
                {
                    player->ModifyMoney(obj.Amount);
                    break;
                }
                case QUEST_OBJECTIVE_PLAYERKILLS:
                {
                    for (uint16 z = 0; z < obj.Amount; ++z)
                        player->KilledPlayerCredit(ObjectGuid::Empty);
                    break;
                }
            }
        }

        if (sWorld->getBoolConfig(CONFIG_QUEST_ENABLE_QUEST_TRACKER)) // check if Quest Tracker is enabled
        {
            // prepare Quest Tracker datas
            CharacterDatabasePreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_UPD_QUEST_TRACK_GM_COMPLETE);
            stmt->setUInt32(0, quest->GetQuestId());
            stmt->setUInt64(1, player->GetGUID().GetCounter());

            // add to Quest Tracker
            CharacterDatabase.Execute(stmt);
        }

        player->CompleteQuest(entry);
        return true;
    }

    static bool HandleQuestReward(ChatHandler* handler, char const* args)
    {
        Player* player = handler->getSelectedPlayer();
        if (!player)
        {
            handler->SendSysMessage(LANG_NO_CHAR_SELECTED);
            handler->SetSentErrorMessage(true);
            return false;
        }

        // .quest reward #entry
        // number or [name] Shift-click form |color|Hquest:quest_id:quest_level:min_level:max_level:scaling_faction|h[name]|h|r
        char* cId = handler->extractKeyFromLink((char*)args, "Hquest");
        if (!cId)
            return false;

        uint32 entry = atoul(cId);

        Quest const* quest = sObjectMgr->GetQuestTemplate(entry);

        // If player doesn't have the quest
        if (!quest || player->GetQuestStatus(entry) != QUEST_STATUS_COMPLETE
            || DisableMgr::IsDisabledFor(DISABLE_TYPE_QUEST, entry, nullptr))
        {
            handler->PSendSysMessage(LANG_COMMAND_QUEST_NOTFOUND, entry);
            handler->SetSentErrorMessage(true);
            return false;
        }

        player->RewardQuest(quest, LootItemType::Item, 0, player);
        return true;
    }
};

void AddSC_quest_commandscript()
{
    new quest_commandscript();
    new quest_playerscript();
}
