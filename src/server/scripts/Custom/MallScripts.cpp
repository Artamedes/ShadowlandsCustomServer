#include "ScriptMgr.h"
#include "Creature.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "TemporarySummon.h"
#include "Chat.h"
#include "QuestDef.h"

struct npc_battle_training : public ScriptedAI
{
    public:
        npc_battle_training(Creature* p_Creature) : ScriptedAI(p_Creature) { }

        void OnQuestAccept(Player* p_Player, Quest const* p_Quest) override
        {
            switch (p_Quest->GetQuestId())
            {
                case 700001:
                    Talk(0, p_Player);
                    break;
            }
        }

        bool OnGossipHello(Player* p_Player) override
        {
            ClearGossipMenuFor(p_Player);
            p_Player->PrepareQuestMenu(me->GetGUID());
            if (p_Player->GetQuestStatus(700001) == QUEST_STATUS_INCOMPLETE)
                AddGossipItemFor(p_Player, GossipOptionIcon::BattleMaster, "Battle!", 0, 1);
            AddGossipItemFor(p_Player, GossipOptionIcon::None, "Nevermind", 0, 0);
            SendGossipMenuFor(p_Player, me->GetEntry(), me);
            return true;
        }

        bool OnGossipSelect(Player* p_Player, uint32 p_MenuId, uint32 p_GossipId) override
        {
            uint32 l_ActionId = p_Player->PlayerTalkClass->GetGossipOptionAction(p_GossipId);
            CloseGossipMenuFor(p_Player);
            switch (l_ActionId)
            {
                case 1:
                    me->SummonCreature(700001, { 424.571991f, -3423.668457f, 4.344817f, 1.230315f }, TempSummonType::TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30s, 0, 0, p_Player->GetGUID());
                    me->SummonCreature(700001, { 414.650269f, -3416.539551f, 4.344817f, 1.030315f }, TempSummonType::TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30s, 0, 0, p_Player->GetGUID());
                    me->SummonCreature(700001, { 411.319611f, -3434.841064f, 4.344656f, 1.230315f }, TempSummonType::TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30s, 0, 0, p_Player->GetGUID());
                    break;
            }
            return true;
        }
};

// 700003
struct npc_item_upgrade_tutorial : public ScriptedAI
{
    public:
        npc_item_upgrade_tutorial(Creature* p_Creature) : ScriptedAI(p_Creature) { }

        void OnQuestAccept(Player* p_Player, Quest const* p_Quest) override
        {
            switch (p_Quest->GetQuestId())
            {
                case 700002:
                    Talk(0, p_Player);
                    break;
            }
        }

        bool OnGossipHello(Player* p_Player) override
        {
            ClearGossipMenuFor(p_Player);
            p_Player->PrepareQuestMenu(me->GetGUID());
            if (p_Player->GetQuestStatus(700002) == QUEST_STATUS_INCOMPLETE)
                AddGossipItemFor(p_Player, GossipOptionIcon::BattleMaster, "How do you upgrade?", 0, 1);
            AddGossipItemFor(p_Player, GossipOptionIcon::None, "Nevermind", 0, 0);
            SendGossipMenuFor(p_Player, me->GetEntry(), me);
            return true;
        }

        bool OnGossipSelect(Player* p_Player, uint32 p_MenuId, uint32 p_GossipId) override
        {
            uint32 l_ActionId = p_Player->PlayerTalkClass->GetGossipOptionAction(p_GossipId);
            CloseGossipMenuFor(p_Player);
            switch (l_ActionId)
            {
                case 1:
                    Talk(0, p_Player);
                    break;
            }
            return true;
        }
};

struct npc_infernal_core_360607 : public ScriptedAI
{
    public:
        npc_infernal_core_360607(Creature* p_Creature) : ScriptedAI(p_Creature) { }

        void InitializeAI() override
        {
            me->SetUnitFlags(UnitFlags::UNIT_FLAG_NON_ATTACKABLE);
            m_Events.ScheduleEvent(1, 100ms);
        }

        void JustSummoned(Creature* p_Summoner) override
        {
        }

        void MovementInform(uint32 p_Type, uint32 p_Point) override
        {
            if (p_Type == POINT_MOTION_TYPE && p_Point == 1)
            {
                DoCast(270296);
             //   me->HandleEmoteCommand(EMOTE_ONESHOT_ROAR);
            }
        }

        void UpdateAI(uint32 p_Diff) override
        {
            m_Events.Update(p_Diff);

            while (uint32 eventId = m_Events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case 1:
                    {
                        DoCast(360607); // Infernal Portal
                        //DoCast(255472);
                        m_Events.ScheduleEvent(2, 200ms);
                        Position pos = *me;
                        pos.m_positionX += 6.0f;
                        pos.m_positionY += 15.0f;
                        me->GetMotionMaster()->MovePoint(1, pos);
                        break;
                    }
                    case 2:
                        me->RemoveUnitFlag(UnitFlags::UNIT_FLAG_NON_ATTACKABLE);
                        break;
                }
            }

            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }
    private:
        EventMap m_Events;
};

struct npc_skipbot_3000 : public ScriptedAI
{
    public:
        npc_skipbot_3000(Creature* p_Creature) : ScriptedAI(p_Creature) { }

        bool OnGossipHello(Player* p_Player) override
        {
            ClearGossipMenuFor(p_Player);
            p_Player->PrepareQuestMenu(me->GetGUID());
            if (p_Player->GetQuestStatus(700000) == QUEST_STATUS_INCOMPLETE || p_Player->GetQuestStatus(700000) == QUEST_STATUS_NONE
                || p_Player->GetQuestStatus(700001) == QUEST_STATUS_INCOMPLETE || p_Player->GetQuestStatus(700001) == QUEST_STATUS_NONE
                || p_Player->GetQuestStatus(700002) == QUEST_STATUS_INCOMPLETE || p_Player->GetQuestStatus(700002) == QUEST_STATUS_NONE
                || p_Player->GetQuestStatus(700003) == QUEST_STATUS_INCOMPLETE || p_Player->GetQuestStatus(700003) == QUEST_STATUS_NONE
                || p_Player->GetQuestStatus(700004) == QUEST_STATUS_INCOMPLETE || p_Player->GetQuestStatus(700004) == QUEST_STATUS_NONE
                || p_Player->GetQuestStatus(700005) == QUEST_STATUS_INCOMPLETE || p_Player->GetQuestStatus(700005) == QUEST_STATUS_NONE
                || p_Player->GetQuestStatus(700006) == QUEST_STATUS_INCOMPLETE || p_Player->GetQuestStatus(700006) == QUEST_STATUS_NONE)
                AddGossipItemFor(p_Player, GossipOptionIcon::AdventureMap, "Skip tutorial.", 0, 1);
            AddGossipItemFor(p_Player, GossipOptionIcon::None, "Nevermind", 0, 0);
            SendGossipMenuFor(p_Player, me->GetEntry(), me);
            return true;
        }
        

        bool OnGossipSelect(Player* p_Player, uint32 p_MenuId, uint32 p_GossipId) override
        {
            uint32 l_ActionId = p_Player->PlayerTalkClass->GetGossipOptionAction(p_GossipId);
            CloseGossipMenuFor(p_Player);
            switch (l_ActionId)
            {
                case 1:
                {
                    Talk(0, p_Player);

                    for (uint32 l_Quest : {700000, 700001, 700002, 700003, 700004, 700005, 700006})
                    {
                        auto l_QuestPtr = sObjectMgr->GetQuestTemplate(l_Quest);
                        if (!l_QuestPtr)
                            break;
                        p_Player->AddQuest(l_QuestPtr, me);
                        p_Player->CompleteQuest(l_Quest);
                        p_Player->RewardQuest(l_QuestPtr, LootItemType::Item, 0, me);
                    }

                    GameTele const* tele = sObjectMgr->GetGameTele(1779);
                    if (!tele)
                    {
                        ChatHandler(p_Player).PSendSysMessage("Broken teleport in Robot!");
                        break;
                    }

                    p_Player->TeleportTo(tele->mapId, tele->position_x, tele->position_y, tele->position_z, tele->orientation);
                    p_Player->SetHomebind(WorldLocation(tele->mapId, tele->position_x, tele->position_y, tele->position_z, tele->orientation), 6719);

                   //auto l_QuestPtr = sObjectMgr->GetQuestTemplate(700007);
                   //if (!l_QuestPtr)
                   //    break;
                   //p_Player->AddQuest(l_QuestPtr, me);

                    break;
                }
            }
            return true;
        }
};

struct npc_currency_guy : public ScriptedAI
{
    public:
        npc_currency_guy(Creature* p_Creature) : ScriptedAI(p_Creature) { }

        bool OnGossipHello(Player* p_Player) override
        {
            ClearGossipMenuFor(p_Player);
            p_Player->PrepareQuestMenu(me->GetGUID());
            if (p_Player->GetQuestStatus(700005) == QUEST_STATUS_INCOMPLETE)
                AddGossipItemFor(p_Player, GossipOptionIcon::AdventureMap, "What are currencies for?", 0, 1);
            AddGossipItemFor(p_Player, GossipOptionIcon::None, "Nevermind", 0, 0);
            SendGossipMenuFor(p_Player, me->GetEntry(), me);
            return true;
        }

        bool OnGossipSelect(Player* p_Player, uint32 p_MenuId, uint32 p_GossipId) override
        {
            uint32 l_ActionId = p_Player->PlayerTalkClass->GetGossipOptionAction(p_GossipId);
            CloseGossipMenuFor(p_Player);
            switch (l_ActionId)
            {
                case 1:
                    Talk(0, p_Player);
                    p_Player->KilledMonsterCredit(700005, me->GetGUID());
                    break;
            }
            return true;
        }
};

// Char services
struct npc_char_services : public ScriptedAI
{
    public:
        npc_char_services(Creature* p_Creature) : ScriptedAI(p_Creature) { }

        bool OnGossipHello(Player* p_Player) override
        {
            ClearGossipMenuFor(p_Player);
            p_Player->PrepareQuestMenu(me->GetGUID());
            AddGossipItemFor(p_Player, GossipOptionIcon::None, "|TInterface\\ICONS\\achievement_general.BLP:30:30:-28:0|tReset my talents.", 0, 2);
            AddGossipItemFor(p_Player, GossipOptionIcon::None, "|TInterface\\ICONS\\inv_inscription_talenttome01.BLP:30:30:-28:0|tGive me 5 tomes.", 0, 1);
            SendGossipMenuFor(p_Player, me->GetEntry(), me);
            return true;
        }

        bool OnGossipSelect(Player* p_Player, uint32 p_MenuId, uint32 p_GossipId) override
        {
            uint32 l_ActionId = p_Player->PlayerTalkClass->GetGossipOptionAction(p_GossipId);
            CloseGossipMenuFor(p_Player);
            switch (l_ActionId)
            {
                case 1:
                    p_Player->AddItem(173049, 5);
                    break;
                case 2:
                    p_Player->ResetTalents(true);
                    break;
            }
            return true;
        }
};

void AddSC_MallScripts()
{
    RegisterCreatureAI(npc_battle_training);
    RegisterCreatureAI(npc_infernal_core_360607);
    RegisterCreatureAI(npc_item_upgrade_tutorial);
    RegisterCreatureAI(npc_skipbot_3000);
    RegisterCreatureAI(npc_currency_guy);
    RegisterCreatureAI(npc_char_services);
}
