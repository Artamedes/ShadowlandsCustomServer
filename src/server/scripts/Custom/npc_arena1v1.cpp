
#include "ScriptMgr.h"
#include "Common.h"
#include "DisableMgr.h"
#include "BattlegroundMgr.h"
#include "Battleground.h"
#include "Language.h"
#include "Chat.h"
#include "DB2Stores.h"
#include "BattlegroundPackets.h"

struct npc_1v1arena : public ScriptedAI
{
public:
    npc_1v1arena(Creature* creature) : ScriptedAI(creature)
    {
    }

    bool JoinQueueArena(Player* player, Creature* me, bool isRated)
    {
        if (!player || !me)
            return false;

        uint8 arenatype = ARENA_TYPE_5v5;
        uint32 arenaRating = 0;
        uint32 matchmakerRating = 0;

        // ignore if we already in BG or BG queue
        if (player->InBattleground())
            return false;

        //check existance
        Battleground* bg = sBattlegroundMgr->GetBattlegroundTemplate(BATTLEGROUND_AA);
        if (!bg)
        {
            //TC_LOG_ERROR("network", "Battleground: template bg (all arenas) not found");
            return false;
        }

        if (DisableMgr::IsDisabledFor(DISABLE_TYPE_BATTLEGROUND, BATTLEGROUND_AA, NULL))
        {
            ChatHandler(player->GetSession()).PSendSysMessage(LANG_ARENA_DISABLED);
            return false;
        }

        BattlegroundTypeId bgTypeId = bg->GetTypeID();

        PVPDifficultyEntry const* bracketEntry = sDB2Manager.GetBattlegroundBracketByLevel(bg->GetMapId(), player->GetLevel());
        if (!bracketEntry)
            return false;

        // check if has free queue slots
        if (!player->HasFreeBattlegroundQueueId())
            return false;

        for (uint8 i = 0; i < PLAYER_MAX_BATTLEGROUND_QUEUES; ++i)
        {
            BattlegroundQueueTypeId bgQueueTypeId = player->GetBattlegroundQueueTypeId(i);
            BattlegroundTypeId bgTypeId = BattlegroundTypeId(bgQueueTypeId.BattlemasterListId);
            uint8 arenaType = bgQueueTypeId.TeamSize;

            if (bgTypeId == BattlegroundTypeId::BATTLEGROUND_AA)
            {
                if (arenaRating <= 0)
                    arenaRating = 1;
                if (matchmakerRating <= 0)
                    matchmakerRating = 1;


                BattlegroundQueue& bgQueue = sBattlegroundMgr->GetBattlegroundQueue(bgQueueTypeId);

                GroupQueueInfo* ginfo = bgQueue.AddGroup(player, nullptr, Team::TEAM_OTHER, bracketEntry, false, arenaRating, matchmakerRating);
                uint32 avgTime = bgQueue.GetAverageQueueWaitTime(ginfo, bracketEntry->GetBracketId());
                uint32 queueSlot = player->AddBattlegroundQueueId(bgQueueTypeId);

                // add joined time data
                //player->AddBattlegroundQueueJoinTime(bgTypeId, ginfo->JoinTime);

                WorldPackets::Battleground::BattlefieldStatusQueued battlefieldStatus;
                sBattlegroundMgr->BuildBattlegroundStatusQueued(&battlefieldStatus, bg, player, queueSlot, ginfo->JoinTime, bgQueueTypeId, avgTime, 0, false);
                player->SendDirectMessage(battlefieldStatus.Write());

                sBattlegroundMgr->ScheduleQueueUpdate(matchmakerRating, bgQueueTypeId, bracketEntry->GetBracketId());

                return true;
            }
        }
    }

    bool OnGossipHello(Player* player) override
    {
        if (!player)
            return true;

        //for (uint8 i = 0; i < PLAYER_MAX_BATTLEGROUND_QUEUES; ++i)
        //{
        //    BattlegroundQueueTypeId bgQueueTypeId = player->GetBattlegroundQueueTypeId(i);
        //    BattlegroundTypeId bgTypeId = BattlegroundTypeId(bgQueueTypeId.BattlemasterListId);
        //    uint8 arenaType = bgQueueTypeId.TeamSize;
        //
        //    // check if already in queue
        //    if (player->GetBattlegroundQueueIndex(bgQueueTypeId) < PLAYER_MAX_BATTLEGROUND_QUEUES)
        //        // player is already in this queue
        //        return true;
        //}

        AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/ICONS/achievement_arena_5v5_7.png:28:28:-16|tJoin The 1v1 Arena Queue", GOSSIP_SENDER_MAIN, 20);
        SendGossipMenuFor(player, 1, me);
        return true;
    }

    enum Cases
    {
        JOIN = 20,
        LEAVE = 3
    };


    bool OnGossipSelect(Player* player,uint32 /*menuId*/, uint32 gossipId) override
    {
        auto uiAction = player->PlayerTalkClass->GetGossipOptionAction(gossipId);
        player->PlayerTalkClass->ClearMenus();

        switch (uiAction)
        {
            case JOIN: // Join Queue Arena (unrated)
            {
                if (JoinQueueArena(player, me, false) == false)
                    ChatHandler(player->GetSession()).SendSysMessage("Something went wrong while join queue.");

                CloseGossipMenuFor(player);
                return true;
            }
            break;
        }

        OnGossipHello(player);
        return true;
    }
};

void AddSC_npc_1v1arena()
{
    RegisterCreatureAI(npc_1v1arena);
}
