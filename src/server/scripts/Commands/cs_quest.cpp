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

template <class T>
static std::string GetTextFromAny(std::string A, T any)
{
    std::ostringstream ss;
    ss << A << any;
    return ss.str();
}

static std::string GetTextFromAny(std::string A, bool any)
{
    std::ostringstream ss;
    ss << A;

    if (any)
        ss << "|cff00FF00" << "true";
    else
        ss << "|cffFF0000" << "false";

    return ss.str();
}

std::unordered_map<ObjectGuid::LowType, QuestPoiData> questPoiData;

class quest_poi_playerscript : public PlayerScript
{
    public:
        quest_poi_playerscript() : PlayerScript("quest_poi_playerscript") { }

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
            player->PlayerTalkClass->GetGossipMenu().SetMenuId(62767262);
            SendGossipMenuFor(player, 1, player);
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
                        DB2Manager::GetUiMapPosition(player->GetPositionX(), player->GetPositionY(), player->GetPositionZ(), player->GetMapId(), 0, 0, 0, UI_MAP_SYSTEM_WORLD, false, &uiMapId);
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
                        DB2Manager::GetUiMapPosition(player->GetPositionX(), player->GetPositionY(), player->GetPositionZ(), player->GetMapId(), 0, 0, 0, UI_MAP_SYSTEM_WORLD, false, &uiMapId);
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

struct QuestData
{
    uint32 ID = 0;                          // quest_template.id

    // creature_queststarter, ender
    uint32 QuestStarter = 0;                // creature_queststarter.quest
    uint32 QuestEnder = 0;                  // creature_questender.quest

    uint32 PrevQuestID = 0;                 // quest_template_addon.PrevQuestID
    uint32 NextQuestID = 0;                 // quest_template_addon.NextQuestID
    uint32 RewardNext = 0;                  // quest_template.RewardNext

    // Template
    uint32 QuestFlags = 0;                  // quest_template.Flags
    // Portraits
    uint32      QuestGiverPortrait = 0;     // quest_template.PortraitGiver
    uint32      QuestGiverPortraitMount = 0;// quest_template.PortraitGiverMount
    uint32      TurninPortrait = 0;         // quest_template.PortraitTurnIn
    // Texts
    std::string LogTitle;                   // quest_template.LogTitle
    std::string LogDescription;             // quest_template.LogDescription
    std::string QuestDescription;           // quest_template.QuestDescription
    std::string AreaDescription;            // quest_template.AreaDescription
    std::string PortraitGiverText;          // quest_template.PortraitGiverText
    std::string PortraitGiverName;          // quest_template.PortraitGiverName
    std::string PortraitTurnInText;         // quest_template.PortraitTurnInText
    std::string PortraitTurnInName;         // quest_template.PortraitTurnInName
    std::string QuestCompletionLog;         // quest_template.QuestCompletionLog
    std::string RewardText;                 // quest_offer_reward.RewardText
    // Objectives
    std::vector<QuestObjective> Objectives;
};

std::unordered_map<ObjectGuid::LowType, std::unique_ptr<QuestData>> questData;

class quest_create_playerscript : public PlayerScript
{
public:
    quest_create_playerscript() : PlayerScript("quest_create_playerscript") { }

    enum eQuestCreate
    {
        SenderMenu,
            MainMenu,
            FlagsMenu,
            TextMenu,
            PortraitsMenu,
            ObjectivesMenu,
        SenderUpdateAction,
            Commit,
            Entry,
            Starter,
            Ender,
            PrevQuestID,
            NextQuestID,
            RewardNext,
            // Flags
            NONE                    ,
            STAY_ALIVE              ,
            PARTY_ACCEPT            ,
            EXPLORATION             ,
            SHARABLE                ,
            HAS_CONDITION           ,
            HIDE_REWARD_POI         ,
            RAID                    ,
            WAR_MODE_REWARDS_OPT_IN ,
            NO_MONEY_FROM_XP        ,
            HIDDEN_REWARDS          ,
            TRACKING                ,
            DEPRECATE_REPUTATION    ,
            DAILY                   ,
            FLAGS_PVP               ,
            UNAVAILABLE             ,
            WEEKLY                  ,
            AUTOCOMPLETE            ,
            DISPLAY_ITEM_IN_TRACKER ,
            OBJ_TEXT                ,
            AUTO_ACCEPT             ,
            PLAYER_CAST_ON_ACCEPT   ,
            PLAYER_CAST_ON_COMPLETE ,
            UPDATE_PHASE_SHIFT      ,
            SOR_WHITELIST           ,
            LAUNCH_GOSSIP_COMPLETE  ,
            REMOVE_EXTRA_GET_ITEMS  ,
            HIDE_UNTIL_DISCOVERED   ,
            PORTRAIT_IN_QUEST_LOG   ,
            SHOW_ITEM_WHEN_COMPLETED,
            LAUNCH_GOSSIP_ACCEPT    ,
            ITEMS_GLOW_WHEN_DONE    ,
            FAIL_ON_LOGOUT          ,
            // Portraits
            QuestGiverPortraitName   ,
            QuestGiverPortraitDesc   ,
            QuestGiverPortrait       ,
            QuestGiverPortraitMount  ,
            TurnInPortraitName       ,
            TurnInPortraitDesc       ,
            TurninPortrait           ,
            TurninPortraitMount      ,
            // Texts
            LogTitle,
            LogDescription,
            QuestDescription,
            AreaDescription,
            PortraitGiverText,
            PortraitGiverName,
            PortraitTurnInText,
            PortraitTurnInName,
            QuestCompletionLog,
    };

    // Private
    void DisplayObjectiveFlags(Player* player, QuestObjective* objective, size_t itr)
    {
        ClearGossipMenuFor(player);
        AddGossipItemFor(player, GossipOptionIcon::None, GetTextFromAny("tracked_on_minimap        ", (objective->Flags & QUEST_OBJECTIVE_FLAG_TRACKED_ON_MINIMAP       ) != 0), 0, 0, [this, player, objective, itr](std::string /*callback*/) { if ((objective->Flags & QUEST_OBJECTIVE_FLAG_TRACKED_ON_MINIMAP       ) == 0) objective->Flags |= QUEST_OBJECTIVE_FLAG_TRACKED_ON_MINIMAP       ; else objective->Flags &= ~QUEST_OBJECTIVE_FLAG_TRACKED_ON_MINIMAP       ; DisplayObjectiveFlags(player, objective, itr);});
        AddGossipItemFor(player, GossipOptionIcon::None, GetTextFromAny("sequenced                 ", (objective->Flags & QUEST_OBJECTIVE_FLAG_SEQUENCED                ) != 0), 0, 0, [this, player, objective, itr](std::string /*callback*/) { if ((objective->Flags & QUEST_OBJECTIVE_FLAG_SEQUENCED                ) == 0) objective->Flags |= QUEST_OBJECTIVE_FLAG_SEQUENCED                ; else objective->Flags &= ~QUEST_OBJECTIVE_FLAG_SEQUENCED                ; DisplayObjectiveFlags(player, objective, itr);});
        AddGossipItemFor(player, GossipOptionIcon::None, GetTextFromAny("optional                  ", (objective->Flags & QUEST_OBJECTIVE_FLAG_OPTIONAL                 ) != 0), 0, 0, [this, player, objective, itr](std::string /*callback*/) { if ((objective->Flags & QUEST_OBJECTIVE_FLAG_OPTIONAL                 ) == 0) objective->Flags |= QUEST_OBJECTIVE_FLAG_OPTIONAL                 ; else objective->Flags &= ~QUEST_OBJECTIVE_FLAG_OPTIONAL                 ; DisplayObjectiveFlags(player, objective, itr);});
        AddGossipItemFor(player, GossipOptionIcon::None, GetTextFromAny("hidden                    ", (objective->Flags & QUEST_OBJECTIVE_FLAG_HIDDEN                   ) != 0), 0, 0, [this, player, objective, itr](std::string /*callback*/) { if ((objective->Flags & QUEST_OBJECTIVE_FLAG_HIDDEN                   ) == 0) objective->Flags |= QUEST_OBJECTIVE_FLAG_HIDDEN                   ; else objective->Flags &= ~QUEST_OBJECTIVE_FLAG_HIDDEN                   ; DisplayObjectiveFlags(player, objective, itr);});
        AddGossipItemFor(player, GossipOptionIcon::None, GetTextFromAny("hide_credit_msg           ", (objective->Flags & QUEST_OBJECTIVE_FLAG_HIDE_CREDIT_MSG          ) != 0), 0, 0, [this, player, objective, itr](std::string /*callback*/) { if ((objective->Flags & QUEST_OBJECTIVE_FLAG_HIDE_CREDIT_MSG          ) == 0) objective->Flags |= QUEST_OBJECTIVE_FLAG_HIDE_CREDIT_MSG          ; else objective->Flags &= ~QUEST_OBJECTIVE_FLAG_HIDE_CREDIT_MSG          ; DisplayObjectiveFlags(player, objective, itr);});
        AddGossipItemFor(player, GossipOptionIcon::None, GetTextFromAny("preserve_quest_items      ", (objective->Flags & QUEST_OBJECTIVE_FLAG_PRESERVE_QUEST_ITEMS     ) != 0), 0, 0, [this, player, objective, itr](std::string /*callback*/) { if ((objective->Flags & QUEST_OBJECTIVE_FLAG_PRESERVE_QUEST_ITEMS     ) == 0) objective->Flags |= QUEST_OBJECTIVE_FLAG_PRESERVE_QUEST_ITEMS     ; else objective->Flags &= ~QUEST_OBJECTIVE_FLAG_PRESERVE_QUEST_ITEMS     ; DisplayObjectiveFlags(player, objective, itr);});
        AddGossipItemFor(player, GossipOptionIcon::None, GetTextFromAny("part_of_progress_bar      ", (objective->Flags & QUEST_OBJECTIVE_FLAG_PART_OF_PROGRESS_BAR     ) != 0), 0, 0, [this, player, objective, itr](std::string /*callback*/) { if ((objective->Flags & QUEST_OBJECTIVE_FLAG_PART_OF_PROGRESS_BAR     ) == 0) objective->Flags |= QUEST_OBJECTIVE_FLAG_PART_OF_PROGRESS_BAR     ; else objective->Flags &= ~QUEST_OBJECTIVE_FLAG_PART_OF_PROGRESS_BAR     ; DisplayObjectiveFlags(player, objective, itr);});
        AddGossipItemFor(player, GossipOptionIcon::None, GetTextFromAny("kill_players_same_faction ", (objective->Flags & QUEST_OBJECTIVE_FLAG_KILL_PLAYERS_SAME_FACTION) != 0), 0, 0, [this, player, objective, itr](std::string /*callback*/) { if ((objective->Flags & QUEST_OBJECTIVE_FLAG_KILL_PLAYERS_SAME_FACTION) == 0) objective->Flags |= QUEST_OBJECTIVE_FLAG_KILL_PLAYERS_SAME_FACTION; else objective->Flags &= ~QUEST_OBJECTIVE_FLAG_KILL_PLAYERS_SAME_FACTION; DisplayObjectiveFlags(player, objective, itr);});
        AddGossipItemFor(player, GossipOptionIcon::None, "<-- return", 0, 0, [this, player, objective, itr](std::string /*callback*/) { ShowObjective(player, objective, itr); });
        SendGossipMenuFor(player, 1, player);
    }

    void ShowObjective(Player* player, QuestObjective* objective, size_t itr)
    {
        ClearGossipMenuFor(player);
        // AddGossipItemFor(player, GossipOptionIcon::None, GetTextFromAny("ID: ", objective.ID), 0, 0, "", 0, true, [this](std::string callback)
        // {
        //     objective.ID = atol(callback);
        //     ShowObjective(player, objective);
        // });
        // AddGossipItemFor(player, GossipOptionIcon::None, GetTextFromAny("QuestID: ", objective.QuestID), 0, 0, "", 0, true, [this](std::string callback)
        // {
        //     objective.QuestID = atol(callback);
        //     ShowObjective(player, objective);
        // });
        AddGossipItemFor(player, GossipOptionIcon::None, GetTextFromAny("Type: ", objective->TypeToString()), 0, 0, [this, player, objective, itr](std::string /*callback*/)
        {
            ClearGossipMenuFor(player);
            AddGossipItemFor(player, GossipOptionIcon::None, "monster"               , 0, 0, [this, player, objective, itr](std::string /*callback*/)  {  objective->Type = QUEST_OBJECTIVE_MONSTER                 ; ShowObjective(player, objective, itr); });
            AddGossipItemFor(player, GossipOptionIcon::None, "item"                  , 0, 0, [this, player, objective, itr](std::string /*callback*/)  {  objective->Type = QUEST_OBJECTIVE_ITEM                    ; ShowObjective(player, objective, itr); });
            AddGossipItemFor(player, GossipOptionIcon::None, "gameobject"            , 0, 0, [this, player, objective, itr](std::string /*callback*/)  {  objective->Type = QUEST_OBJECTIVE_GAMEOBJECT              ; ShowObjective(player, objective, itr); });
            AddGossipItemFor(player, GossipOptionIcon::None, "talkto"                , 0, 0, [this, player, objective, itr](std::string /*callback*/)  {  objective->Type = QUEST_OBJECTIVE_TALKTO                  ; ShowObjective(player, objective, itr); });
            AddGossipItemFor(player, GossipOptionIcon::None, "currency"              , 0, 0, [this, player, objective, itr](std::string /*callback*/)  {  objective->Type = QUEST_OBJECTIVE_CURRENCY                ; ShowObjective(player, objective, itr); });
            AddGossipItemFor(player, GossipOptionIcon::None, "learnspell"            , 0, 0, [this, player, objective, itr](std::string /*callback*/)  {  objective->Type = QUEST_OBJECTIVE_LEARNSPELL              ; ShowObjective(player, objective, itr); });
            AddGossipItemFor(player, GossipOptionIcon::None, "min_reputation"        , 0, 0, [this, player, objective, itr](std::string /*callback*/)  {  objective->Type = QUEST_OBJECTIVE_MIN_REPUTATION          ; ShowObjective(player, objective, itr); });
            AddGossipItemFor(player, GossipOptionIcon::None, "max_reputation"        , 0, 0, [this, player, objective, itr](std::string /*callback*/)  {  objective->Type = QUEST_OBJECTIVE_MAX_REPUTATION          ; ShowObjective(player, objective, itr); });
            AddGossipItemFor(player, GossipOptionIcon::None, "money"                 , 0, 0, [this, player, objective, itr](std::string /*callback*/)  {  objective->Type = QUEST_OBJECTIVE_MONEY                   ; ShowObjective(player, objective, itr); });
            AddGossipItemFor(player, GossipOptionIcon::None, "playerkills"           , 0, 0, [this, player, objective, itr](std::string /*callback*/)  {  objective->Type = QUEST_OBJECTIVE_PLAYERKILLS             ; ShowObjective(player, objective, itr); });
            AddGossipItemFor(player, GossipOptionIcon::None, "areatrigger"           , 0, 0, [this, player, objective, itr](std::string /*callback*/)  {  objective->Type = QUEST_OBJECTIVE_AREATRIGGER             ; ShowObjective(player, objective, itr); });
            AddGossipItemFor(player, GossipOptionIcon::None, "winpetbattleagainstnpc", 0, 0, [this, player, objective, itr](std::string /*callback*/)  {  objective->Type = QUEST_OBJECTIVE_WINPETBATTLEAGAINSTNPC  ; ShowObjective(player, objective, itr); });
            AddGossipItemFor(player, GossipOptionIcon::None, "defeatbattlepet"       , 0, 0, [this, player, objective, itr](std::string /*callback*/)  {  objective->Type = QUEST_OBJECTIVE_DEFEATBATTLEPET         ; ShowObjective(player, objective, itr); });
            AddGossipItemFor(player, GossipOptionIcon::None, "winpvppetbattles"      , 0, 0, [this, player, objective, itr](std::string /*callback*/)  {  objective->Type = QUEST_OBJECTIVE_WINPVPPETBATTLES        ; ShowObjective(player, objective, itr); });
            AddGossipItemFor(player, GossipOptionIcon::None, "criteria_tree"         , 0, 0, [this, player, objective, itr](std::string /*callback*/)  {  objective->Type = QUEST_OBJECTIVE_CRITERIA_TREE           ; ShowObjective(player, objective, itr); });
            AddGossipItemFor(player, GossipOptionIcon::None, "progress_bar"          , 0, 0, [this, player, objective, itr](std::string /*callback*/)  {  objective->Type = QUEST_OBJECTIVE_PROGRESS_BAR            ; ShowObjective(player, objective, itr); });
            AddGossipItemFor(player, GossipOptionIcon::None, "have_currency"         , 0, 0, [this, player, objective, itr](std::string /*callback*/)  {  objective->Type = QUEST_OBJECTIVE_HAVE_CURRENCY           ; ShowObjective(player, objective, itr); });
            AddGossipItemFor(player, GossipOptionIcon::None, "obtain_currency"       , 0, 0, [this, player, objective, itr](std::string /*callback*/)  {  objective->Type = QUEST_OBJECTIVE_OBTAIN_CURRENCY         ; ShowObjective(player, objective, itr); });
            AddGossipItemFor(player, GossipOptionIcon::None, "increase_reputation"   , 0, 0, [this, player, objective, itr](std::string /*callback*/)  {  objective->Type = QUEST_OBJECTIVE_INCREASE_REPUTATION     ; ShowObjective(player, objective, itr); });
            AddGossipItemFor(player, GossipOptionIcon::None, "area_trigger_enter"    , 0, 0, [this, player, objective, itr](std::string /*callback*/)  {  objective->Type = QUEST_OBJECTIVE_AREA_TRIGGER_ENTER      ; ShowObjective(player, objective, itr); });
            AddGossipItemFor(player, GossipOptionIcon::None, "area_trigger_exit"     , 0, 0, [this, player, objective, itr](std::string /*callback*/)  {  objective->Type = QUEST_OBJECTIVE_AREA_TRIGGER_EXIT       ; ShowObjective(player, objective, itr); });
            AddGossipItemFor(player, GossipOptionIcon::None, "<-- return"            , 0, 0, [this, player, objective, itr](std::string /*callback*/)  { ShowObjective(player, objective, itr); });
            SendGossipMenuFor(player, 1, player);
        });
        AddGossipItemFor(player, GossipOptionIcon::None, GetTextFromAny("StorageIndex: ", (int32)objective->StorageIndex), 0, 0, "", 0, true, [this, player, objective, itr](std::string callback)
        {
            objective->StorageIndex = (int8)std::stoi(callback);
            ShowObjective(player, objective, itr);
        });
        AddGossipItemFor(player, GossipOptionIcon::None, GetTextFromAny("ObjectID: ", objective->ObjectID), 0, 0, "", 0, true, [this, player, objective, itr](std::string callback)
        {
            objective->ObjectID = std::stoi(callback);
            ShowObjective(player, objective, itr);
        });
        AddGossipItemFor(player, GossipOptionIcon::None, GetTextFromAny("Amount: ", objective->Amount), 0, 0, "", 0, true, [this, player, objective, itr](std::string callback)
        {
            objective->Amount = std::stoi(callback);
            ShowObjective(player, objective, itr);
        });
        AddGossipItemFor(player, GossipOptionIcon::None, GetTextFromAny("Flags: ", objective->Flags), 0, 0, [this, player, objective, itr](std::string callback)
        {
            DisplayObjectiveFlags(player, objective, itr);
        });
        AddGossipItemFor(player, GossipOptionIcon::None, GetTextFromAny("Flags2: ", objective->Flags2), 0, 0, "", 0, true, [this, player, objective, itr](std::string callback)
        {
            objective->Flags2 = std::stoi(callback);
            ShowObjective(player, objective, itr);
        });
        AddGossipItemFor(player, GossipOptionIcon::None, GetTextFromAny("ProgressBarWeight: ", objective->ProgressBarWeight), 0, 0, "", 0, true, [this, player, objective, itr](std::string callback)
        {
            objective->ProgressBarWeight = std::stof(callback);
            ShowObjective(player, objective, itr);
        });
        AddGossipItemFor(player, GossipOptionIcon::None, GetTextFromAny("Description: ", objective->Description), 0, 0, "", 0, true, [this, player, objective, itr](std::string callback)
        {
            objective->Description = callback;
            ShowObjective(player, objective, itr);
        });

        AddGossipItemFor(player, GossipOptionIcon::None, "Remove objective", 0, 0, [this, player, objective, itr](std::string /*callback*/)
        {
            auto itr2 = questData.find(player->GetGUID().GetCounter());
            if (itr2 == questData.end())
                return;

            auto data = itr2->second.get();
            auto it = data->Objectives.begin();
            std::advance(it, itr);
            data->Objectives.erase(it);
            OnGossipSelect(player, 62767263, SenderMenu, ObjectivesMenu);
        });

        AddGossipItemFor(player, GossipOptionIcon::None, "<-- Return", SenderMenu, MainMenu, [this, player](std::string /*callback*/)
        {
            OnGossipSelect(player, 62767263, SenderMenu, ObjectivesMenu);
        });
        SendGossipMenuFor(player, 1, player);
    }

    static void ShowMenu(Player* player)
    {
        auto itr = questData.find(player->GetGUID().GetCounter());
        if (itr == questData.end())
            return;

        auto data = itr->second.get();

        ClearGossipMenuFor(player);

        AddGossipItemFor(player, GossipOptionIcon::None, GetTextFromAny("Entry: ", data->ID), SenderUpdateAction, Entry, "", 0, true, [player, data](std::string callback)
        {
            data->ID = std::stoi(callback);
            ShowMenu(player);
        });
        AddGossipItemFor(player, GossipOptionIcon::None, "Edit Flags", SenderMenu, FlagsMenu);
        AddGossipItemFor(player, GossipOptionIcon::None, "Edit Text", SenderMenu, TextMenu);
        AddGossipItemFor(player, GossipOptionIcon::None, "Edit Flags", SenderMenu, FlagsMenu);
        AddGossipItemFor(player, GossipOptionIcon::None, "Edit Portraits", SenderMenu, PortraitsMenu);
        AddGossipItemFor(player, GossipOptionIcon::None, GetTextFromAny("Edit Objectives: ", data->Objectives.size()), SenderMenu, ObjectivesMenu);
        AddGossipItemFor(player, GossipOptionIcon::None, GetTextFromAny("Quest Starter: ", data->QuestStarter), SenderUpdateAction, Starter, "", 0, true, [player, data](std::string callback)
        {
            data->QuestStarter = std::stoi(callback);
            ShowMenu(player);
        });
        AddGossipItemFor(player, GossipOptionIcon::None, GetTextFromAny("Quest Ender: ", data->QuestEnder), SenderUpdateAction, Ender, "", 0, true, [player, data](std::string callback)
        {
            data->QuestEnder = std::stoi(callback);
            ShowMenu(player);
        });
        AddGossipItemFor(player, GossipOptionIcon::None, GetTextFromAny("PrevQuestID: ", data->PrevQuestID), SenderUpdateAction, PrevQuestID, "", 0, true, [player, data](std::string callback)
        {
            data->PrevQuestID = std::stoi(callback);
            ShowMenu(player);
        });
        AddGossipItemFor(player, GossipOptionIcon::None, GetTextFromAny("NextQuestID: ", data->NextQuestID), SenderUpdateAction, NextQuestID, "", 0, true, [player, data](std::string callback)
        {
            data->NextQuestID = std::stoi(callback);
            ShowMenu(player);
        });
        AddGossipItemFor(player, GossipOptionIcon::None, GetTextFromAny("RewardNext: ", data->RewardNext), SenderUpdateAction, RewardNext, "", 0, true, [player, data](std::string callback)
        {
            data->RewardNext = std::stoi(callback);
            ShowMenu(player);
        });
        AddGossipItemFor(player, GossipOptionIcon::None, "Commit", SenderUpdateAction, Commit, [player, data](std::string /*callback*/)
        {
            if (!data->ID || sObjectMgr->GetQuestTemplate(data->ID))
            {
                CloseGossipMenuFor(player);
                ChatHandler(player).PSendSysMessage("Bad ID %s [%u]", data->LogTitle.c_str(), data->ID);
                return;
            }

            auto stmt = WorldDatabase.GetPreparedStatement(WORLD_REP_CREATURE_QUESTSTARTER);
            stmt->setUInt32(0, data->ID);
            stmt->setUInt32(1, data->QuestStarter);
            WorldDatabase.Query(stmt);

            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            stmt = WorldDatabase.GetPreparedStatement(WORLD_REP_CREATURE_QUESTENDER);
            stmt->setUInt32(0, data->ID);
            stmt->setUInt32(1, data->QuestEnder);
            WorldDatabase.Query(stmt);

            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            stmt = WorldDatabase.GetPreparedStatement(WORLD_REP_QUEST_TEMPLATE);
            stmt->setUInt32(0,  data->ID);// ID
            stmt->setUInt32(1,  2);// QuestType,
            stmt->setUInt32(2,  2057);// ContentTuningID,
            stmt->setUInt32(3,  6719);// QuestSortID,
            stmt->setUInt32(4,  0);// QuestInfoID,
            stmt->setUInt32(5,  data->QuestFlags);// Flags,
            stmt->setString(6,  data->LogTitle);// LogTitle,
            stmt->setString(7,  data->LogDescription);// LogDescription,
            stmt->setString(8,  data->QuestDescription);// QuestDescription,
            stmt->setString(9,  data->AreaDescription);// AreaDescription,
            stmt->setString(10, data->PortraitGiverText);// PortraitGiverText,
            stmt->setString(11, data->PortraitGiverName);// PortraitGiverName,
            stmt->setString(12, data->PortraitTurnInText);// PortraitTurnInText,
            stmt->setString(13, data->PortraitTurnInName);// PortraitTurnInName,
            stmt->setString(14, data->QuestCompletionLog);// QuestCompletionLog,
            stmt->setUInt32(15, data->QuestGiverPortrait);// PortraitGiver,
            stmt->setUInt32(16, data->QuestGiverPortraitMount);// PortraitGiverMount
            stmt->setUInt32(17, data->TurninPortrait);// PortraitTurnIn
            stmt->setUInt64(18, 18446744073709551615);// AllowableRaces
            WorldDatabase.Query(stmt);

            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            stmt = WorldDatabase.GetPreparedStatement(WORLD_REP_QUEST_TEMPLATE_ADDON);
            // ID, PrevQuestID, NextQuestID
            stmt->setUInt32(0, data->ID);
            stmt->setUInt32(1, data->PrevQuestID);
            stmt->setUInt32(2, data->NextQuestID);
            WorldDatabase.Query(stmt);

            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            if (!data->Objectives.empty())
            {
                uint32 startId = data->ID * 10;
                uint32 i = 0;
                for (auto& objective : data->Objectives)
                {
                    // REPLACE INTO quest_objectives (ID, QuestID, Type, Order, StorageIndex, ObjectID, Amount, Flags, Flags2, ProgressBarWeight, Description) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)
                    stmt = WorldDatabase.GetPreparedStatement(WORLD_REP_QUEST_OBJECTIVES);
                    stmt->setUInt32(0, startId++); // ID
                    stmt->setUInt32(1, objective.QuestID); // QuestID
                    stmt->setUInt8(2, objective.Type); // Type
                    stmt->setUInt32(3, i); // Order
                    stmt->setInt8(4, i); // StorageIndex
                    stmt->setInt32(5, objective.ObjectID); // ObjectID
                    stmt->setInt32(6, objective.Amount); // Amount
                    stmt->setUInt32(7, objective.Flags); // Flags
                    stmt->setUInt32(8, objective.Flags2); // Flags2
                    stmt->setFloat(9, objective.ProgressBarWeight); // ProgressBarWeight
                    stmt->setString(10, objective.Description); // Description
                    WorldDatabase.Query(stmt);
                    ++i;
                }
            }

            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            if (!data->RewardText.empty())
            {
                stmt = WorldDatabase.GetPreparedStatement(WORLD_REP_QUEST_OFFER_REWARD);
                stmt->setUInt32(0, data->ID);
                stmt->setString(1, data->RewardText);
                WorldDatabase.Query(stmt);
            }

            CloseGossipMenuFor(player);
            ChatHandler(player).PSendSysMessage("Commited %s [%u]", data->LogTitle.c_str(), data->ID);
            sObjectMgr->LoadQuests();
            player->AddQuestAndCheckCompletion(sObjectMgr->GetQuestTemplate(data->ID), player);
        });

        player->PlayerTalkClass->GetGossipMenu().SetMenuId(62767263);
        SendGossipMenuFor(player, 1, player);
    }

    void OnGossipSelect(Player* player, uint32 menuId, uint32 sender, uint32 action) override
    {
        if (menuId != 62767263)
            return;

        OnGossipSelectCode(player, menuId, sender, action, nullptr);
    }

    void OnGossipSelectCode(Player* player, uint32 menuId, uint32 sender, uint32 action, char const* code) override
    {
        if (menuId != 62767263)
            return;

        auto itr = questData.find(player->GetGUID().GetCounter());
        if (itr == questData.end())
            return;

        auto data = itr->second.get();

        ClearGossipMenuFor(player);


        switch (sender)
        {
            case SenderMenu:
            {
                switch (action)
                {
                    case MainMenu:
                    {
                        ShowMenu(player);
                        break;
                    }
                    case FlagsMenu:
                    {
                        AddGossipItemFor(player, GossipOptionIcon::None, GetTextFromAny("Stay Alive: ", (data->QuestFlags & QUEST_FLAGS_STAY_ALIVE) != 0), SenderUpdateAction, STAY_ALIVE);
                        AddGossipItemFor(player, GossipOptionIcon::None, GetTextFromAny("Party Accept: ", (data->QuestFlags & QUEST_FLAGS_PARTY_ACCEPT) != 0), SenderUpdateAction, PARTY_ACCEPT);
                        AddGossipItemFor(player, GossipOptionIcon::None, GetTextFromAny("Exploration: ", (data->QuestFlags & QUEST_FLAGS_EXPLORATION) != 0), SenderUpdateAction, EXPLORATION);
                        AddGossipItemFor(player, GossipOptionIcon::None, GetTextFromAny("Sharable: ", (data->QuestFlags & QUEST_FLAGS_SHARABLE) != 0), SenderUpdateAction, SHARABLE);
                        AddGossipItemFor(player, GossipOptionIcon::None, GetTextFromAny("Has Condition: ", (data->QuestFlags & QUEST_FLAGS_HAS_CONDITION) != 0), SenderUpdateAction, HAS_CONDITION);
                        AddGossipItemFor(player, GossipOptionIcon::None, GetTextFromAny("Hide Reward Poi: ", (data->QuestFlags & QUEST_FLAGS_HIDE_REWARD_POI) != 0), SenderUpdateAction, HIDE_REWARD_POI);
                        AddGossipItemFor(player, GossipOptionIcon::None, GetTextFromAny("Raid: ", (data->QuestFlags & QUEST_FLAGS_RAID) != 0), SenderUpdateAction, RAID);
                        AddGossipItemFor(player, GossipOptionIcon::None, GetTextFromAny("War Mode Rewards Opt In: ", (data->QuestFlags & QUEST_FLAGS_WAR_MODE_REWARDS_OPT_IN) != 0), SenderUpdateAction, WAR_MODE_REWARDS_OPT_IN);
                        AddGossipItemFor(player, GossipOptionIcon::None, GetTextFromAny("No Money From Xp: ", (data->QuestFlags & QUEST_FLAGS_NO_MONEY_FROM_XP) != 0), SenderUpdateAction, NO_MONEY_FROM_XP);
                        AddGossipItemFor(player, GossipOptionIcon::None, GetTextFromAny("Hidden Rewards: ", (data->QuestFlags & QUEST_FLAGS_HIDDEN_REWARDS) != 0), SenderUpdateAction, HIDDEN_REWARDS);
                        AddGossipItemFor(player, GossipOptionIcon::None, GetTextFromAny("Tracking: ", (data->QuestFlags & QUEST_FLAGS_TRACKING) != 0), SenderUpdateAction, TRACKING);
                        AddGossipItemFor(player, GossipOptionIcon::None, GetTextFromAny("Deprecate Reputation: ", (data->QuestFlags & QUEST_FLAGS_DEPRECATE_REPUTATION) != 0), SenderUpdateAction, DEPRECATE_REPUTATION);
                        AddGossipItemFor(player, GossipOptionIcon::None, GetTextFromAny("Daily: ", (data->QuestFlags & QUEST_FLAGS_DAILY) != 0), SenderUpdateAction, DAILY);
                        AddGossipItemFor(player, GossipOptionIcon::None, GetTextFromAny("Flags Pvp: ", (data->QuestFlags & QUEST_FLAGS_FLAGS_PVP) != 0), SenderUpdateAction, FLAGS_PVP);
                        //AddGossipItemFor(player, GossipOptionIcon::None, GetTextFromAny("Unavailable: ", (data->QuestFlags & QUEST_FLAGS_UNAVAILABLE) != 0), SenderUpdateAction, UNAVAILABLE);
                        AddGossipItemFor(player, GossipOptionIcon::None, GetTextFromAny("Weekly: ", (data->QuestFlags & QUEST_FLAGS_WEEKLY) != 0), SenderUpdateAction, WEEKLY);
                        AddGossipItemFor(player, GossipOptionIcon::None, GetTextFromAny("Autocomplete: ", (data->QuestFlags & QUEST_FLAGS_AUTOCOMPLETE) != 0), SenderUpdateAction, AUTOCOMPLETE);
                        AddGossipItemFor(player, GossipOptionIcon::None, GetTextFromAny("Display Item In Tracker: ", (data->QuestFlags & QUEST_FLAGS_DISPLAY_ITEM_IN_TRACKER) != 0), SenderUpdateAction, DISPLAY_ITEM_IN_TRACKER);
                        AddGossipItemFor(player, GossipOptionIcon::None, GetTextFromAny("Obj Text: ", (data->QuestFlags & QUEST_FLAGS_OBJ_TEXT) != 0), SenderUpdateAction, OBJ_TEXT);
                        AddGossipItemFor(player, GossipOptionIcon::None, GetTextFromAny("Auto Accept: ", (data->QuestFlags & QUEST_FLAGS_AUTO_ACCEPT) != 0), SenderUpdateAction, AUTO_ACCEPT);
                        AddGossipItemFor(player, GossipOptionIcon::None, GetTextFromAny("Player Cast On Accept: ", (data->QuestFlags & QUEST_FLAGS_PLAYER_CAST_ON_ACCEPT) != 0), SenderUpdateAction, PLAYER_CAST_ON_ACCEPT);
                        AddGossipItemFor(player, GossipOptionIcon::None, GetTextFromAny("Player Cast On Complete: ", (data->QuestFlags & QUEST_FLAGS_PLAYER_CAST_ON_COMPLETE) != 0), SenderUpdateAction, PLAYER_CAST_ON_COMPLETE);
                        AddGossipItemFor(player, GossipOptionIcon::None, GetTextFromAny("Update Phase Shift: ", (data->QuestFlags & QUEST_FLAGS_UPDATE_PHASE_SHIFT) != 0), SenderUpdateAction, UPDATE_PHASE_SHIFT);
                        AddGossipItemFor(player, GossipOptionIcon::None, GetTextFromAny("Sor Whitelist: ", (data->QuestFlags & QUEST_FLAGS_SOR_WHITELIST) != 0), SenderUpdateAction, SOR_WHITELIST);
                        AddGossipItemFor(player, GossipOptionIcon::None, GetTextFromAny("Launch Gossip Complete: ", (data->QuestFlags & QUEST_FLAGS_LAUNCH_GOSSIP_COMPLETE) != 0), SenderUpdateAction, LAUNCH_GOSSIP_COMPLETE);
                        AddGossipItemFor(player, GossipOptionIcon::None, GetTextFromAny("Remove Extra Get Items: ", (data->QuestFlags & QUEST_FLAGS_REMOVE_EXTRA_GET_ITEMS) != 0), SenderUpdateAction, REMOVE_EXTRA_GET_ITEMS);
                        AddGossipItemFor(player, GossipOptionIcon::None, GetTextFromAny("Hide Until Discovered: ", (data->QuestFlags & QUEST_FLAGS_HIDE_UNTIL_DISCOVERED) != 0), SenderUpdateAction, HIDE_UNTIL_DISCOVERED);
                        AddGossipItemFor(player, GossipOptionIcon::None, GetTextFromAny("Portrait In Quest Log: ", (data->QuestFlags & QUEST_FLAGS_PORTRAIT_IN_QUEST_LOG) != 0), SenderUpdateAction, PORTRAIT_IN_QUEST_LOG);
                        AddGossipItemFor(player, GossipOptionIcon::None, GetTextFromAny("Show Item When Completed: ", (data->QuestFlags & QUEST_FLAGS_SHOW_ITEM_WHEN_COMPLETED) != 0), SenderUpdateAction, SHOW_ITEM_WHEN_COMPLETED);
                        AddGossipItemFor(player, GossipOptionIcon::None, GetTextFromAny("Launch Gossip Accept: ", (data->QuestFlags & QUEST_FLAGS_LAUNCH_GOSSIP_ACCEPT) != 0), SenderUpdateAction, LAUNCH_GOSSIP_ACCEPT);
                        AddGossipItemFor(player, GossipOptionIcon::None, GetTextFromAny("Items Glow When Done: ", (data->QuestFlags & QUEST_FLAGS_ITEMS_GLOW_WHEN_DONE) != 0), SenderUpdateAction, ITEMS_GLOW_WHEN_DONE);
                        AddGossipItemFor(player, GossipOptionIcon::None, GetTextFromAny("Fail On Logout: ", (data->QuestFlags & QUEST_FLAGS_FAIL_ON_LOGOUT) != 0), SenderUpdateAction, FAIL_ON_LOGOUT);
                        AddGossipItemFor(player, GossipOptionIcon::None, "Return", SenderMenu, MainMenu);

                        SendGossipMenuFor(player, 1, player);
                        break;
                    }
                    case TextMenu:
                    {
                        AddGossipItemFor(player, GossipOptionIcon::None, GetTextFromAny("LogTitle: ", data->LogTitle), SenderUpdateAction, LogTitle, "", 0, true, [this, player, &data](std::string arg)
                        {
                            data->LogTitle = arg;
                            OnGossipSelect(player, 62767263, SenderMenu, TextMenu);
                        });
                        AddGossipItemFor(player, GossipOptionIcon::None, GetTextFromAny("LogDescription: ", data->LogDescription), SenderUpdateAction, LogDescription, "", 0, true, [this, player, data](std::string arg)
                        {
                            data->LogDescription = arg;
                            OnGossipSelect(player, 62767263, SenderMenu, TextMenu);
                        });
                        AddGossipItemFor(player, GossipOptionIcon::None, GetTextFromAny("QuestDescription: ", data->QuestDescription), SenderUpdateAction, QuestDescription, "", 0, true, [this, player, data](std::string arg)
                        {
                            data->QuestDescription = arg;
                            OnGossipSelect(player, 62767263, SenderMenu, TextMenu);
                        });
                        AddGossipItemFor(player, GossipOptionIcon::None, GetTextFromAny("AreaDescription: ", data->AreaDescription), SenderUpdateAction, AreaDescription, "", 0, true, [this, player, data](std::string arg)
                        {
                            data->AreaDescription = arg;
                            OnGossipSelect(player, 62767263, SenderMenu, TextMenu);
                        });
                        AddGossipItemFor(player, GossipOptionIcon::None, GetTextFromAny("PortraitGiverText: ", data->PortraitGiverText), SenderUpdateAction, PortraitGiverText, "", 0, true, [this, player, data](std::string arg)
                        {
                            data->PortraitGiverText = arg;
                            OnGossipSelect(player, 62767263, SenderMenu, TextMenu);
                        });
                        AddGossipItemFor(player, GossipOptionIcon::None, GetTextFromAny("PortraitGiverName: ", data->PortraitGiverName), SenderUpdateAction, PortraitGiverName, "", 0, true, [this, player, data](std::string arg)
                        {
                            data->PortraitGiverName = arg;
                            OnGossipSelect(player, 62767263, SenderMenu, TextMenu);
                        });
                        AddGossipItemFor(player, GossipOptionIcon::None, GetTextFromAny("PortraitTurnInText: ", data->PortraitTurnInText), SenderUpdateAction, PortraitTurnInText, "", 0, true, [this, player, data](std::string arg)
                        {
                            data->PortraitTurnInText = arg;
                            OnGossipSelect(player, 62767263, SenderMenu, TextMenu);
                        });
                        AddGossipItemFor(player, GossipOptionIcon::None, GetTextFromAny("PortraitTurnInName: ", data->PortraitTurnInName), SenderUpdateAction, PortraitTurnInName, "", 0, true, [this, player, data](std::string arg)
                        {
                            data->PortraitTurnInName = arg;
                            OnGossipSelect(player, 62767263, SenderMenu, TextMenu);
                        });
                        AddGossipItemFor(player, GossipOptionIcon::None, GetTextFromAny("QuestCompletionLog: ", data->QuestCompletionLog), SenderUpdateAction, QuestCompletionLog, "", 0, true, [this, player, data](std::string arg)
                        {
                            data->QuestCompletionLog = arg;
                            OnGossipSelect(player, 62767263, SenderMenu, TextMenu);
                        });
                        AddGossipItemFor(player, GossipOptionIcon::None, GetTextFromAny("RewardText: ", data->RewardText), 0, 0, "", 0, true, [this, player, data](std::string arg)
                        {
                            data->RewardText = arg;
                            OnGossipSelect(player, 62767263, SenderMenu, TextMenu);
                        });
                        AddGossipItemFor(player, GossipOptionIcon::None, "Return", SenderMenu, MainMenu);
                        SendGossipMenuFor(player, 1, player);

                        break;
                    }
                    case PortraitsMenu:
                    {
                        //AddGossipItemFor(player, GossipOptionIcon::None, GetTextFromAny("QuestGiverPortraitName: ", data->QuestGiverPortraitName), SenderUpdateAction, QuestGiverPortraitName, "", 0, true, [this, player, data](std::string arg)
                        //{
                        //    data->QuestGiverPortraitName = arg;
                        //    OnGossipSelect(player, 62767263, SenderMenu, PortraitsMenu);
                        //});
                        //AddGossipItemFor(player, GossipOptionIcon::None, GetTextFromAny("QuestGiverPortraitDesc: ",   data->QuestGiverPortraitDesc   ), SenderUpdateAction, QuestGiverPortraitDesc, "", 0, true, [this, player, data](std::string arg)
                        //{
                        //    data->QuestGiverPortraitDesc = arg;
                        //    OnGossipSelect(player, 62767263, SenderMenu, PortraitsMenu);
                        //});
                        AddGossipItemFor(player, GossipOptionIcon::None, GetTextFromAny("QuestGiverPortrait: ",       data->QuestGiverPortrait       ), SenderUpdateAction, QuestGiverPortrait, "", 0, true, [this, player, data](std::string arg)
                        {
                            data->QuestGiverPortrait = std::stoi(arg);
                            OnGossipSelect(player, 62767263, SenderMenu, PortraitsMenu);
                        });
                        AddGossipItemFor(player, GossipOptionIcon::None, GetTextFromAny("QuestGiverPortraitMount: ",  data->QuestGiverPortraitMount  ), SenderUpdateAction, QuestGiverPortraitMount, "", 0, true, [this, player, data](std::string arg)
                        {
                            data->QuestGiverPortraitMount = std::stoi(arg);
                            OnGossipSelect(player, 62767263, SenderMenu, PortraitsMenu);
                        });
                        // AddGossipItemFor(player, GossipOptionIcon::None, GetTextFromAny("TurnInPortraitName: ",       data->TurnInPortraitName       ), SenderUpdateAction, TurnInPortraitName, "", 0, true, [this, player, data](std::string arg)
                        // {
                        //     data->TurnInPortraitName = arg;
                        //     OnGossipSelect(player, 62767263, SenderMenu, PortraitsMenu);
                        // });
                        // AddGossipItemFor(player, GossipOptionIcon::None, GetTextFromAny("TurnInPortraitDesc: ",       data->TurnInPortraitDesc       ), SenderUpdateAction, TurnInPortraitDesc, "", 0, true, [this, player, data](std::string arg)
                        // {
                        //     data->TurnInPortraitDesc = arg;
                        //     OnGossipSelect(player, 62767263, SenderMenu, PortraitsMenu);
                        // });
                        AddGossipItemFor(player, GossipOptionIcon::None, GetTextFromAny("TurninPortrait: ",           data->TurninPortrait           ), SenderUpdateAction, TurninPortrait, "", 0, true, [this, player, data](std::string arg)
                        {
                            data->TurninPortrait = std::stoi(arg);
                            OnGossipSelect(player, 62767263, SenderMenu, PortraitsMenu);
                        });
                        // AddGossipItemFor(player, GossipOptionIcon::None, GetTextFromAny("TurninPortraitMount: ",      data->TurninPortraitMount      ), SenderUpdateAction, TurninPortraitMount, "", 0, true, [this, player, data](std::string arg)
                        // {
                        //     data->TurninPortraitMount = std::stoi(arg);
                        //     OnGossipSelect(player, 62767263, SenderMenu, PortraitsMenu);
                        // });
                        AddGossipItemFor(player, GossipOptionIcon::None, "Return", SenderMenu, MainMenu);

                        SendGossipMenuFor(player, 1, player);

                        break;
                    }
                    case ObjectivesMenu:
                    {
                        for (size_t i = 0; i < data->Objectives.size(); ++i)
                        {
                            AddGossipItemFor(player, GossipOptionIcon::None, GetTextFromAny("Edit Objective: ", i + 1), 0, 0, [this, player, data, i](std::string /*callback*/)
                            {
                                auto& objective = data->Objectives[i];

                                ShowObjective(player, &objective, i);
                            });
                        }

                        AddGossipItemFor(player, GossipOptionIcon::None, "New Objective", 0, 0, [this, player, data](std::string /*callback*/)
                        {
                            QuestObjective objective;
                            objective.QuestID = data->ID;
                            data->Objectives.emplace_back(objective);
                            OnGossipSelect(player, 62767263, SenderMenu, ObjectivesMenu);
                        });

                        AddGossipItemFor(player, GossipOptionIcon::None, "Return", SenderMenu, MainMenu);
                        SendGossipMenuFor(player, 1, player);
                        break;
                    }

                }
                break;
            }
            case SenderUpdateAction:
            {
                switch (action)
                {
                    case NONE                    :    if ((data->QuestFlags & QUEST_FLAGS_NONE                    ) == 0) data->QuestFlags |= QUEST_FLAGS_NONE                    ;else data->QuestFlags &= ~QUEST_FLAGS_NONE                     ;     OnGossipSelect(player, 62767263, SenderMenu, FlagsMenu); break;
                    case STAY_ALIVE              :    if ((data->QuestFlags & QUEST_FLAGS_STAY_ALIVE              ) == 0) data->QuestFlags |= QUEST_FLAGS_STAY_ALIVE              ;else data->QuestFlags &= ~QUEST_FLAGS_STAY_ALIVE               ;     OnGossipSelect(player, 62767263, SenderMenu, FlagsMenu); break;
                    case PARTY_ACCEPT            :    if ((data->QuestFlags & QUEST_FLAGS_PARTY_ACCEPT            ) == 0) data->QuestFlags |= QUEST_FLAGS_PARTY_ACCEPT            ;else data->QuestFlags &= ~QUEST_FLAGS_PARTY_ACCEPT             ;     OnGossipSelect(player, 62767263, SenderMenu, FlagsMenu); break;
                    case EXPLORATION             :    if ((data->QuestFlags & QUEST_FLAGS_EXPLORATION             ) == 0) data->QuestFlags |= QUEST_FLAGS_EXPLORATION             ;else data->QuestFlags &= ~QUEST_FLAGS_EXPLORATION              ;     OnGossipSelect(player, 62767263, SenderMenu, FlagsMenu); break;
                    case SHARABLE                :    if ((data->QuestFlags & QUEST_FLAGS_SHARABLE                ) == 0) data->QuestFlags |= QUEST_FLAGS_SHARABLE                ;else data->QuestFlags &= ~QUEST_FLAGS_SHARABLE                 ;     OnGossipSelect(player, 62767263, SenderMenu, FlagsMenu); break;
                    case HAS_CONDITION           :    if ((data->QuestFlags & QUEST_FLAGS_HAS_CONDITION           ) == 0) data->QuestFlags |= QUEST_FLAGS_HAS_CONDITION           ;else data->QuestFlags &= ~QUEST_FLAGS_HAS_CONDITION            ;     OnGossipSelect(player, 62767263, SenderMenu, FlagsMenu); break;
                    case HIDE_REWARD_POI         :    if ((data->QuestFlags & QUEST_FLAGS_HIDE_REWARD_POI         ) == 0) data->QuestFlags |= QUEST_FLAGS_HIDE_REWARD_POI         ;else data->QuestFlags &= ~QUEST_FLAGS_HIDE_REWARD_POI          ;     OnGossipSelect(player, 62767263, SenderMenu, FlagsMenu); break;
                    case RAID                    :    if ((data->QuestFlags & QUEST_FLAGS_RAID                    ) == 0) data->QuestFlags |= QUEST_FLAGS_RAID                    ;else data->QuestFlags &= ~QUEST_FLAGS_RAID                     ;     OnGossipSelect(player, 62767263, SenderMenu, FlagsMenu); break;
                    case WAR_MODE_REWARDS_OPT_IN :    if ((data->QuestFlags & QUEST_FLAGS_WAR_MODE_REWARDS_OPT_IN ) == 0) data->QuestFlags |= QUEST_FLAGS_WAR_MODE_REWARDS_OPT_IN ;else data->QuestFlags &= ~QUEST_FLAGS_WAR_MODE_REWARDS_OPT_IN  ;     OnGossipSelect(player, 62767263, SenderMenu, FlagsMenu); break;
                    case NO_MONEY_FROM_XP        :    if ((data->QuestFlags & QUEST_FLAGS_NO_MONEY_FROM_XP        ) == 0) data->QuestFlags |= QUEST_FLAGS_NO_MONEY_FROM_XP        ;else data->QuestFlags &= ~QUEST_FLAGS_NO_MONEY_FROM_XP         ;     OnGossipSelect(player, 62767263, SenderMenu, FlagsMenu); break;
                    case HIDDEN_REWARDS          :    if ((data->QuestFlags & QUEST_FLAGS_HIDDEN_REWARDS          ) == 0) data->QuestFlags |= QUEST_FLAGS_HIDDEN_REWARDS          ;else data->QuestFlags &= ~QUEST_FLAGS_HIDDEN_REWARDS           ;     OnGossipSelect(player, 62767263, SenderMenu, FlagsMenu); break;
                    case TRACKING                :    if ((data->QuestFlags & QUEST_FLAGS_TRACKING                ) == 0) data->QuestFlags |= QUEST_FLAGS_TRACKING                ;else data->QuestFlags &= ~QUEST_FLAGS_TRACKING                 ;     OnGossipSelect(player, 62767263, SenderMenu, FlagsMenu); break;
                    case DEPRECATE_REPUTATION    :    if ((data->QuestFlags & QUEST_FLAGS_DEPRECATE_REPUTATION    ) == 0) data->QuestFlags |= QUEST_FLAGS_DEPRECATE_REPUTATION    ;else data->QuestFlags &= ~QUEST_FLAGS_DEPRECATE_REPUTATION     ;     OnGossipSelect(player, 62767263, SenderMenu, FlagsMenu); break;
                    case DAILY                   :    if ((data->QuestFlags & QUEST_FLAGS_DAILY                   ) == 0) data->QuestFlags |= QUEST_FLAGS_DAILY                   ;else data->QuestFlags &= ~QUEST_FLAGS_DAILY                    ;     OnGossipSelect(player, 62767263, SenderMenu, FlagsMenu); break;
                    case FLAGS_PVP               :    if ((data->QuestFlags & QUEST_FLAGS_FLAGS_PVP               ) == 0) data->QuestFlags |= QUEST_FLAGS_FLAGS_PVP               ;else data->QuestFlags &= ~QUEST_FLAGS_FLAGS_PVP                ;     OnGossipSelect(player, 62767263, SenderMenu, FlagsMenu); break;
                    case UNAVAILABLE             :    if ((data->QuestFlags & QUEST_FLAGS_UNAVAILABLE             ) == 0) data->QuestFlags |= QUEST_FLAGS_UNAVAILABLE             ;else data->QuestFlags &= ~QUEST_FLAGS_UNAVAILABLE              ;     OnGossipSelect(player, 62767263, SenderMenu, FlagsMenu); break;
                    case WEEKLY                  :    if ((data->QuestFlags & QUEST_FLAGS_WEEKLY                  ) == 0) data->QuestFlags |= QUEST_FLAGS_WEEKLY                  ;else data->QuestFlags &= ~QUEST_FLAGS_WEEKLY                   ;     OnGossipSelect(player, 62767263, SenderMenu, FlagsMenu); break;
                    case AUTOCOMPLETE            :    if ((data->QuestFlags & QUEST_FLAGS_AUTOCOMPLETE            ) == 0) data->QuestFlags |= QUEST_FLAGS_AUTOCOMPLETE            ;else data->QuestFlags &= ~QUEST_FLAGS_AUTOCOMPLETE             ;     OnGossipSelect(player, 62767263, SenderMenu, FlagsMenu); break;
                    case DISPLAY_ITEM_IN_TRACKER :    if ((data->QuestFlags & QUEST_FLAGS_DISPLAY_ITEM_IN_TRACKER ) == 0) data->QuestFlags |= QUEST_FLAGS_DISPLAY_ITEM_IN_TRACKER ;else data->QuestFlags &= ~QUEST_FLAGS_DISPLAY_ITEM_IN_TRACKER  ;     OnGossipSelect(player, 62767263, SenderMenu, FlagsMenu); break;
                    case OBJ_TEXT                :    if ((data->QuestFlags & QUEST_FLAGS_OBJ_TEXT                ) == 0) data->QuestFlags |= QUEST_FLAGS_OBJ_TEXT                ;else data->QuestFlags &= ~QUEST_FLAGS_OBJ_TEXT                 ;     OnGossipSelect(player, 62767263, SenderMenu, FlagsMenu); break;
                    case AUTO_ACCEPT             :    if ((data->QuestFlags & QUEST_FLAGS_AUTO_ACCEPT             ) == 0) data->QuestFlags |= QUEST_FLAGS_AUTO_ACCEPT             ;else data->QuestFlags &= ~QUEST_FLAGS_AUTO_ACCEPT              ;     OnGossipSelect(player, 62767263, SenderMenu, FlagsMenu); break;
                    case PLAYER_CAST_ON_ACCEPT   :    if ((data->QuestFlags & QUEST_FLAGS_PLAYER_CAST_ON_ACCEPT   ) == 0) data->QuestFlags |= QUEST_FLAGS_PLAYER_CAST_ON_ACCEPT   ;else data->QuestFlags &= ~QUEST_FLAGS_PLAYER_CAST_ON_ACCEPT    ;     OnGossipSelect(player, 62767263, SenderMenu, FlagsMenu); break;
                    case PLAYER_CAST_ON_COMPLETE :    if ((data->QuestFlags & QUEST_FLAGS_PLAYER_CAST_ON_COMPLETE ) == 0) data->QuestFlags |= QUEST_FLAGS_PLAYER_CAST_ON_COMPLETE ;else data->QuestFlags &= ~QUEST_FLAGS_PLAYER_CAST_ON_COMPLETE  ;     OnGossipSelect(player, 62767263, SenderMenu, FlagsMenu); break;
                    case UPDATE_PHASE_SHIFT      :    if ((data->QuestFlags & QUEST_FLAGS_UPDATE_PHASE_SHIFT      ) == 0) data->QuestFlags |= QUEST_FLAGS_UPDATE_PHASE_SHIFT      ;else data->QuestFlags &= ~QUEST_FLAGS_UPDATE_PHASE_SHIFT       ;     OnGossipSelect(player, 62767263, SenderMenu, FlagsMenu); break;
                    case SOR_WHITELIST           :    if ((data->QuestFlags & QUEST_FLAGS_SOR_WHITELIST           ) == 0) data->QuestFlags |= QUEST_FLAGS_SOR_WHITELIST           ;else data->QuestFlags &= ~QUEST_FLAGS_SOR_WHITELIST            ;     OnGossipSelect(player, 62767263, SenderMenu, FlagsMenu); break;
                    case LAUNCH_GOSSIP_COMPLETE  :    if ((data->QuestFlags & QUEST_FLAGS_LAUNCH_GOSSIP_COMPLETE  ) == 0) data->QuestFlags |= QUEST_FLAGS_LAUNCH_GOSSIP_COMPLETE  ;else data->QuestFlags &= ~QUEST_FLAGS_LAUNCH_GOSSIP_COMPLETE   ;     OnGossipSelect(player, 62767263, SenderMenu, FlagsMenu); break;
                    case REMOVE_EXTRA_GET_ITEMS  :    if ((data->QuestFlags & QUEST_FLAGS_REMOVE_EXTRA_GET_ITEMS  ) == 0) data->QuestFlags |= QUEST_FLAGS_REMOVE_EXTRA_GET_ITEMS  ;else data->QuestFlags &= ~QUEST_FLAGS_REMOVE_EXTRA_GET_ITEMS   ;     OnGossipSelect(player, 62767263, SenderMenu, FlagsMenu); break;
                    case HIDE_UNTIL_DISCOVERED   :    if ((data->QuestFlags & QUEST_FLAGS_HIDE_UNTIL_DISCOVERED   ) == 0) data->QuestFlags |= QUEST_FLAGS_HIDE_UNTIL_DISCOVERED   ;else data->QuestFlags &= ~QUEST_FLAGS_HIDE_UNTIL_DISCOVERED    ;     OnGossipSelect(player, 62767263, SenderMenu, FlagsMenu); break;
                    case PORTRAIT_IN_QUEST_LOG   :    if ((data->QuestFlags & QUEST_FLAGS_PORTRAIT_IN_QUEST_LOG   ) == 0) data->QuestFlags |= QUEST_FLAGS_PORTRAIT_IN_QUEST_LOG   ;else data->QuestFlags &= ~QUEST_FLAGS_PORTRAIT_IN_QUEST_LOG    ;     OnGossipSelect(player, 62767263, SenderMenu, FlagsMenu); break;
                    case SHOW_ITEM_WHEN_COMPLETED:    if ((data->QuestFlags & QUEST_FLAGS_SHOW_ITEM_WHEN_COMPLETED) == 0) data->QuestFlags |= QUEST_FLAGS_SHOW_ITEM_WHEN_COMPLETED;else data->QuestFlags &= ~QUEST_FLAGS_SHOW_ITEM_WHEN_COMPLETED ;     OnGossipSelect(player, 62767263, SenderMenu, FlagsMenu); break;
                    case LAUNCH_GOSSIP_ACCEPT    :    if ((data->QuestFlags & QUEST_FLAGS_LAUNCH_GOSSIP_ACCEPT    ) == 0) data->QuestFlags |= QUEST_FLAGS_LAUNCH_GOSSIP_ACCEPT    ;else data->QuestFlags &= ~QUEST_FLAGS_LAUNCH_GOSSIP_ACCEPT     ;     OnGossipSelect(player, 62767263, SenderMenu, FlagsMenu); break;
                    case ITEMS_GLOW_WHEN_DONE    :    if ((data->QuestFlags & QUEST_FLAGS_ITEMS_GLOW_WHEN_DONE    ) == 0) data->QuestFlags |= QUEST_FLAGS_ITEMS_GLOW_WHEN_DONE    ;else data->QuestFlags &= ~QUEST_FLAGS_ITEMS_GLOW_WHEN_DONE     ;     OnGossipSelect(player, 62767263, SenderMenu, FlagsMenu); break;
                    case FAIL_ON_LOGOUT          :    if ((data->QuestFlags & QUEST_FLAGS_FAIL_ON_LOGOUT          ) == 0) data->QuestFlags |= QUEST_FLAGS_FAIL_ON_LOGOUT          ;else data->QuestFlags &= ~QUEST_FLAGS_FAIL_ON_LOGOUT           ;     OnGossipSelect(player, 62767263, SenderMenu, FlagsMenu); break;
                }
                break;
            }
        }
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
            { "create",   rbac::RBAC_PERM_COMMAND_DEV,            false, &HandleQuestCreateCommand,   "" },
        };
        static std::vector<ChatCommand> commandTable =
        {
            { "quest", rbac::RBAC_PERM_COMMAND_QUEST,  false, nullptr, "", questCommandTable },
        };
        return commandTable;
    }

    static bool HandleQuestCreateCommand(ChatHandler* handler, Optional<uint32> questId)
    {
        auto player = handler->GetPlayer();

        auto data = questData.find(player->GetGUID().GetCounter());
        if (data == questData.end())
            questData[player->GetGUID().GetCounter()] = std::make_unique<QuestData>();

        if (questId.has_value())
        {
            questData[player->GetGUID().GetCounter()] = std::make_unique<QuestData>();
            questData[player->GetGUID().GetCounter()]->ID = *questId;
        }

        if (auto selection = handler->getSelectedCreature())
        {
            questData[player->GetGUID().GetCounter()]->QuestEnder = selection->GetEntry();
            questData[player->GetGUID().GetCounter()]->QuestStarter = selection->GetEntry();
        }

        quest_create_playerscript::ShowMenu(player);

        return true;
    }

    static bool HandleQuestModPoi(ChatHandler* handler, Optional<uint32> questId)
    {
        auto player = handler->GetPlayer();

        if (questId.has_value())
            questPoiData[player->GetGUID().GetCounter()].Reset(questId.value_or(0));
        quest_poi_playerscript::OnGossipHello(player);

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
    new quest_poi_playerscript();
    new quest_create_playerscript();
}
