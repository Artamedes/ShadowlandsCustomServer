#include "ScriptMgr.h"
#include "Creature.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "TemporarySummon.h"
#include "Chat.h"
#include "QuestDef.h"
#include "GameTime.h"
#include "Item.h"
#include "CollectionMgr.h"
#include "WorldSession.h"
#include "CovenantMgr.h"
#include "Conversation.h"
#include "Mail.h"

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
            //AddGossipItemFor(p_Player, GossipOptionIcon::None, "Nevermind", 0, 0);
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
                    if (me->GetEntry() == 700008)
                    {
                        me->SummonCreature(700001, { 738.073181f, -3414.861084f, 4.344868f, 2.140065f }, TempSummonType::TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30s, 0, 0, p_Player->GetGUID());
                        me->SummonCreature(700001, { 747.188782f, -3420.872070f, 4.344868f, 2.140065f }, TempSummonType::TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30s, 0, 0, p_Player->GetGUID());
                        me->SummonCreature(700001, { 738.937927f, -3425.946289f, 4.344868f, 2.064797f }, TempSummonType::TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30s, 0, 0, p_Player->GetGUID());
                    }
                    else
                    {
                        me->SummonCreature(700001, { 424.571991f, -3423.668457f, 4.344817f, 1.230315f }, TempSummonType::TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30s, 0, 0, p_Player->GetGUID());
                        me->SummonCreature(700001, { 414.650269f, -3416.539551f, 4.344817f, 1.030315f }, TempSummonType::TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30s, 0, 0, p_Player->GetGUID());
                        me->SummonCreature(700001, { 411.319611f, -3434.841064f, 4.344656f, 1.230315f }, TempSummonType::TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30s, 0, 0, p_Player->GetGUID());
                    }
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
          //  AddGossipItemFor(p_Player, GossipOptionIcon::None, "Nevermind", 0, 0);
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
            me->SetUnitFlag(UnitFlags::UNIT_FLAG_NON_ATTACKABLE);
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
                        me->GetMotionMaster()->Move(1, MoveTypes::Forward, MOVE_PATHFINDING, 10.0f);
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

        bool DidNotCompleteTutorialQuests(Player* p_Player)
        {
            return (p_Player->GetQuestStatus(700000) == QUEST_STATUS_INCOMPLETE || p_Player->GetQuestStatus(700000) == QUEST_STATUS_NONE
                || p_Player->GetQuestStatus(700001) == QUEST_STATUS_INCOMPLETE || p_Player->GetQuestStatus(700001) == QUEST_STATUS_NONE
                || p_Player->GetQuestStatus(700002) == QUEST_STATUS_INCOMPLETE || p_Player->GetQuestStatus(700002) == QUEST_STATUS_NONE
                || p_Player->GetQuestStatus(700003) == QUEST_STATUS_INCOMPLETE || p_Player->GetQuestStatus(700003) == QUEST_STATUS_NONE
                || p_Player->GetQuestStatus(700004) == QUEST_STATUS_INCOMPLETE || p_Player->GetQuestStatus(700004) == QUEST_STATUS_NONE
                || p_Player->GetQuestStatus(700005) == QUEST_STATUS_INCOMPLETE || p_Player->GetQuestStatus(700005) == QUEST_STATUS_NONE
                || p_Player->GetQuestStatus(700006) == QUEST_STATUS_INCOMPLETE || p_Player->GetQuestStatus(700006) == QUEST_STATUS_NONE);
        }

        bool OnGossipHello(Player* p_Player) override
        {
            ClearGossipMenuFor(p_Player);
            p_Player->PrepareQuestMenu(me->GetGUID());
            if (DidNotCompleteTutorialQuests(p_Player))
                AddGossipItemFor(p_Player, GossipOptionIcon::None, "Skip tutorial.", 0, 1, "Are you sure you want to skip these tutorial quests?", 0, false);
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

                        auto l_Status = p_Player->GetQuestStatus(l_Quest);

                        if (l_Status == QUEST_STATUS_REWARDED)
                            continue;

                        if (p_Player->GetQuestStatus(l_Quest) == QUEST_STATUS_NONE)
                            p_Player->AddQuest(l_QuestPtr, me);
                        if (p_Player->GetQuestStatus(l_Quest) == QUEST_STATUS_INCOMPLETE)
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
           // AddGossipItemFor(p_Player, GossipOptionIcon::None, "Nevermind", 0, 0);
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

        void OnQuestAccept(Player* p_Player, Quest const* p_Quest) override
        {
            if (p_Quest->GetQuestId() == 700006)
                Talk(1, p_Player);
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
            AddGossipItemFor(p_Player, GossipOptionIcon::None, "|TInterface\\ICONS\\inv_misc_enggizmos_32.BLP:30:30:-28:0|tGive me the Magic Stone.", 0, 3);
            AddGossipItemFor(p_Player, GossipOptionIcon::None, "|TInterface\\ICONS\\inv_offhand_1h_ulduarraid_d_01.BLP:30:30:-28:0|tGive me the Item Upgrader.", 0, 4);
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
                case 3:
                    p_Player->AddItem(700001, 1);
                    break;
                case 4:
                    p_Player->AddItem(700000, 1);
                    break;
            }
            return true;
        }
};


struct npc_juno_700006 : public ScriptedAI
{
    public:
        npc_juno_700006(Creature* p_Creature) : ScriptedAI(p_Creature) { }

        bool OnGossipHello(Player* p_Player) override
        {
            ClearGossipMenuFor(p_Player);
            p_Player->PrepareQuestMenu(me->GetGUID());
            if (p_Player->GetQuestStatus(700007) == QUEST_STATUS_NONE)
                SendGossipMenuFor(p_Player, 7000060, me);
            else if (p_Player->GetQuestStatus(700008) != QUEST_STATUS_REWARDED)
                SendGossipMenuFor(p_Player, 7000061, me);
            else
                SendGossipMenuFor(p_Player, 700006, me);
            return true;
        }

        bool OnGossipSelect(Player* p_Player, uint32 p_MenuId, uint32 p_GossipId) override
        {
            uint32 l_ActionId = p_Player->PlayerTalkClass->GetGossipOptionAction(p_GossipId);
            CloseGossipMenuFor(p_Player);
            return true;
        }

        void OnQuestAccept(Player* player, Quest const* quest) override
        {
            if (quest->GetQuestId() == 700019)
            {
                player->TeleportTo(1116, 50.7495f, -2726.76f, 63.047f, 2.47065f);
                Conversation::CreateConversation(700302, player, *player, player->GetGUID());
            }
        }


        bool CanSeeOrDetect(WorldObject const* who) const override
        {
            if (who->IsPlayer())
            {
                auto player = who->ToPlayer();
                if (player->GetQuestStatus(700036) == QUEST_STATUS_REWARDED)
                    return false;
            }

            return true;
        }

        void OnUnitRelocation(Unit* p_Who) override
        {
            if (p_Who->IsPlayer())
            {
                auto l_Player = p_Who->ToPlayer();
                auto l_Itr = m_PlayerTalks.find(p_Who->GetGUID());
                auto l_Now = GameTime::Now();

                if (l_Itr == m_PlayerTalks.end() || l_Now >= l_Itr->second)
                {
                    if (l_Player->GetQuestStatus(700007) == QUEST_STATUS_NONE
                     && l_Player->GetQuestStatus(700006) == QUEST_STATUS_COMPLETE)
                    {
                        m_PlayerTalks[p_Who->GetGUID()] = l_Now + Hours(2);
                        Talk(0, p_Who);
                    }
                }
            }
        }
    private:
        std::unordered_map<ObjectGuid, TimePoint> m_PlayerTalks;
};

struct npc_mall_weapongiver : public ScriptedAI
{
    public:
        npc_mall_weapongiver(Creature* creature) : ScriptedAI(creature) { }

        void InitializeAI() override
        {
            DoCastSelf(356889);
            switch (me->GetEntry())
            {
                case 800027: // Julius (Shield)
                    m_BonusListIds.reserve(4);
                    m_ItemEntries.reserve(1);
                    m_ItemEntries.emplace_back(113653);
                    m_BonusListIds.emplace_back(6606); // Mythic
                    m_BonusListIds.emplace_back(1660); // ItemLevel
                    m_BonusListIds.emplace_back(1610); // ItemLevel
                    m_BonusListIds.emplace_back(1602); // ItemLevel
                    AllowableClasses = 2 + 1;
                    break;
                case 800028: // Draka
                    m_BonusListIds.reserve(3);
                    m_ItemEntries.reserve(1);
                    m_ItemEntries.emplace_back(186398);
                    m_BonusListIds.emplace_back(6606); // Mythic
                    m_BonusListIds.emplace_back(1600); // ItemLevel
                    m_BonusListIds.emplace_back(1611); // ItemLevel
                    AllowableClasses = 8 + 1024;
                    break;
                case 800029: // Prophet
                    m_BonusListIds.reserve(3);
                    m_ItemEntries.reserve(1);
                    m_ItemEntries.emplace_back(189851);
                    m_BonusListIds.emplace_back(6606); // Mythic
                    m_BonusListIds.emplace_back(1610); // ItemLevel
                    m_BonusListIds.emplace_back(1601); // ItemLevel
                    AllowableClasses = 2 + 1 + 32;
                    break;
                case 800025: // Sylvanas
                    m_BonusListIds.reserve(3);
                    m_ItemEntries.reserve(1);
                    m_ItemEntries.emplace_back(186414);
                    m_BonusListIds.emplace_back(6606); // Mythic
                    m_BonusListIds.emplace_back(1610); // ItemLevel
                    m_BonusListIds.emplace_back(1601); // ItemLevel
                    AllowableClasses = 4; // Hunter
                    break;
                case 800023: // Wrathion
                    m_ItemEntries.reserve(2);
                    m_ItemEntries.emplace_back(77949);
                    m_ItemEntries.emplace_back(77950);
                    m_BonusListIds.reserve(4);
                    m_BonusListIds.emplace_back(6606); // Mythic
                    m_BonusListIds.emplace_back(1610); // ItemLevel
                    m_BonusListIds.emplace_back(1618); // ItemLevel
                    m_BonusListIds.emplace_back(1650); // ItemLevel
                    AllowableClasses = 8; // Rogue
                    break;
                case 800022: // Dragonwrath
                    //.add 71086 1 6606;1610;1618;1651
                    m_ItemEntries.reserve(1);
                    m_ItemEntries.emplace_back(71086);
                    m_BonusListIds.reserve(4);
                    m_BonusListIds.emplace_back(6606); // Mythic
                    m_BonusListIds.emplace_back(1610); // ItemLevel
                    m_BonusListIds.emplace_back(1618); // ItemLevel
                    m_BonusListIds.emplace_back(1651); // ItemLevel
                    AllowableClasses = CLASSMASK_WAND_USERS + 1024 + 64; // Casters
                    break;
                case 800021: // Sulfuras
                    //.add 71352 1 6606;1610;1618;1651
                    m_ItemEntries.reserve(1);
                    m_ItemEntries.emplace_back(71352);
                    m_BonusListIds.reserve(4);
                    m_BonusListIds.emplace_back(6606); // Mythic
                    m_BonusListIds.emplace_back(1610); // ItemLevel
                    m_BonusListIds.emplace_back(1618); // ItemLevel
                    m_BonusListIds.emplace_back(1651); // ItemLevel
                    AllowableClasses = 1 + 2 + 32;
                    break;
                case 800018: // Shadowmourne
                    //.add 49623 1 6606;1610;1618;1653
                    m_ItemEntries.reserve(1);
                    m_ItemEntries.emplace_back(49623);
                    m_BonusListIds.reserve(4);
                    m_BonusListIds.emplace_back(6606); // Mythic
                    m_BonusListIds.emplace_back(1610); // ItemLevel
                    m_BonusListIds.emplace_back(1618); // ItemLevel
                    m_BonusListIds.emplace_back(1653); // ItemLevel
                    AllowableClasses = 1 + 2 + 32;
                    break;
                case 800019: // Frostmourne
                    //.add 49623 1 6606;1610;1618;1653
                    //m_ItemEntries.reserve(1);
                    //m_ItemEntries.emplace_back(49623);
                    //m_BonusListIds.reserve(4);
                    //m_BonusListIds.emplace_back(6606); // Mythic
                    //m_BonusListIds.emplace_back(1610); // ItemLevel
                    //m_BonusListIds.emplace_back(1618); // ItemLevel
                    //m_BonusListIds.emplace_back(1653); // ItemLevel
                    //AllowableClasses = 1 + 2 + 32;
                    break;
                case 800020: // Highlord
                    //.add 19019 1 6606;1610;1618;1659
                    m_ItemEntries.reserve(1);
                    m_ItemEntries.emplace_back(19019);
                    m_BonusListIds.reserve(5);
                    m_BonusListIds.emplace_back(6606); // Mythic
                    m_BonusListIds.emplace_back(1610); // ItemLevel
                    m_BonusListIds.emplace_back(1618); // ItemLevel
                    m_BonusListIds.emplace_back(1659); // ItemLevel
                    m_BonusListIds.emplace_back(6403); // agil/crit
                    AllowableClasses = 1 + 2048 + 8 + 512 + 32;
                    break;
                case 800017: // Illidan
                    //.add 32837 1 6606;1610;1618;1655
                    //.add 32838 1 6606;1610;1618;1655
                    m_ItemEntries.reserve(2);
                    m_ItemEntries.emplace_back(32837);
                    m_ItemEntries.emplace_back(32838);
                    m_BonusListIds.reserve(5);
                    m_BonusListIds.emplace_back(6606); // Mythic
                    m_BonusListIds.emplace_back(1610); // ItemLevel
                    m_BonusListIds.emplace_back(1618); // ItemLevel
                    m_BonusListIds.emplace_back(1655); // ItemLevel
                    m_BonusListIds.emplace_back(6403); // agil/crit
                    AllowableClasses = 1 + 2048 + 8 + 512 + 32;
                    break;
                case 800024: // Magni
                    //.add [Val'anyr, Hammer of Ancient Kings] 1 6606;1610;1618;1653
                    m_ItemEntries.reserve(1);
                    m_ItemEntries.emplace_back(46017);
                    m_BonusListIds.reserve(4);
                    m_BonusListIds.emplace_back(6606); // Mythic
                    m_BonusListIds.emplace_back(1610); // ItemLevel
                    m_BonusListIds.emplace_back(1618); // ItemLevel
                    m_BonusListIds.emplace_back(1653); // ItemLevel
                    AllowableClasses = 1024 + 64 + 512; // Casters
                    break;
            }
        }

        void EnterEvadeMode(EvadeReason) override
        {
            DoCastSelf(356889);
        }

        void Reset() override
        {
            DoCastSelf(356889);
            events.ScheduleEvent(1, 30s);
        }

        bool OnGossipHello(Player* player) override
        {
            ClearGossipMenuFor(player);

            if (player->HasItemCount(700316, 1))
            {
                if (AllowableClasses & player->GetClassMask())
                {
                    AddGossipItemFor(player, GossipOptionIcon::None, "Create Weapon", 0, 2, "|cffFF0000Accepting this will use |cffff8000[Legendary Dust]|cffFF0000x1|R", 0, false);
                }
            }

            AddGossipItemFor(player, GossipOptionIcon::None, "Preview Weapon", 0, 1);
            SendGossipMenuFor(player, 800017, me);
            return true;
        }

        bool OnGossipSelect(Player* player, uint32 menuId, uint32 gossipId) override
        {
            uint32 actionId = player->PlayerTalkClass->GetGossipOptionAction(gossipId);
            ClearGossipMenuFor(player);

            switch (actionId)
            {
                case 1:
                    for (auto entry : m_ItemEntries)
                    {
                        Item* item = Item::CreateItem(entry, 1, ItemContext::NONE, player);
                        if (item)
                        {
                            item->SetBonuses(m_BonusListIds);
                            ChatHandler(player).PSendSysMessage("%s", Item::GetItemLink(item).c_str());
                            delete item;
                        }
                    }
                    break;
                case 2:
                    // 700316 - Legendary Dust
                    if (player->HasItemCount(700316, 1) && !m_ItemEntries.empty())
                    {
                        if (player->GetQuestStatus(700019) == QUEST_STATUS_INCOMPLETE)
                        {
                            CloseGossipMenuFor(player);
                            player->CompleteQuest(700019);
                            player->RewardQuest(sObjectMgr->GetQuestTemplate(700019), LootItemType::Item, 0, me, true);
                            player->AddQuestAndCheckCompletion(sObjectMgr->GetQuestTemplate(700020), me);
                            player->GetScheduler().Schedule(100ms, [player](TaskContext context)
                                {
                                    Conversation::CreateConversation(700303, player, *player, player->GetGUID());
                                    player->PlayerTalkClass->SendQuestGiverQuestDetails(sObjectMgr->GetQuestTemplate(700020), player->GetGUID(), true, true);
                                });
                        }
                        player->DestroyItemCount(700316, 1, true);
                        for (auto entry : m_ItemEntries)
                        {
                            uint32 noSpaceForCount = 0;
                            ItemPosCountVec dest;
                            InventoryResult msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, entry, 1, &noSpaceForCount);
                            Item* item = Item::CreateItem(entry, 1, ItemContext::NONE, player);
                            item->SetBonuses(m_BonusListIds);
                            if (dest.empty())
                            {
                                /// @todo Send to mailbox if no space
                                ChatHandler(player).PSendSysMessage("You don't have any space in your bags, sent to mailbox.");
                                CharacterDatabaseTransaction trans = CharacterDatabase.BeginTransaction();
                                // save new item before send
                                item->SaveToDB(trans);                               // save for prevent lost at next mail load, if send fail then item will deleted

                                auto draft = MailDraft("Lost Item", "Recovered your lost item");
                                // item
                                draft.AddItem(item);
                                draft.SendMailTo(trans, player, MailSender(MAIL_CREATURE, uint64(me->GetEntry())));
                                CharacterDatabase.CommitTransaction(trans);
                                continue;
                            }

                            player->StoreItem(dest, item, true);
                            player->SendNewItem(item, 1, true, true, false);
                        }
                    }
                    break;
            }

            return OnGossipHello(player);
        }

        void UpdateAI(uint32 diff) override
        {
            events.Update(diff);

            if (events.ExecuteEvent() == 1)
            {
                DoCastSelf(356889);
                events.Repeat(30s);
            }
        }

        std::vector<uint32> m_ItemEntries;
        std::vector<int32> m_BonusListIds;
        int32 AllowableClasses = -1;
        EventMap events;
};

struct npc_morpher_admin : public ScriptedAI
{
    public:
        npc_morpher_admin(Creature* creature) : ScriptedAI(creature), summons(creature) { }

        uint32 startEntryId = 0;
        uint32 time = 250;
        uint32 max = 0;
        uint32 iterate = 9;
        bool pause = false;
        SummonList summons;

        void JustSummoned(Creature* creature) override
        {
            summons.Summon(creature);
        }

        bool OnGossipHello(Player* player) override
        {
            ClearGossipMenuFor(player);
            AddGossipItemFor(player, GossipOptionIcon::None, "Set start display id " + std::to_string(startEntryId), 0, 1, "", 0, true);
            AddGossipItemFor(player, GossipOptionIcon::None, "Set max " + std::to_string(max), 0, 8, "", 0, true);
            AddGossipItemFor(player, GossipOptionIcon::None, "Set iterate " + std::to_string(iterate), 0, 9, "", 0, true);
            AddGossipItemFor(player, GossipOptionIcon::None, "Set time " + std::to_string(time), 0, 2, "", 0, true);
            AddGossipItemFor(player, GossipOptionIcon::None, "pause: " + std::string((pause ? "true" : "false")), 0, 3);
            AddGossipItemFor(player, GossipOptionIcon::None, "back: " + std::to_string(startEntryId - 1), 0, 4);
            AddGossipItemFor(player, GossipOptionIcon::None, "next: " + std::to_string(startEntryId + 1), 0, 5);
            AddGossipItemFor(player, GossipOptionIcon::None, "spiral: " + std::to_string(startEntryId + 1), 0, 7);
            AddGossipItemFor(player, GossipOptionIcon::None, "DESPAWN: ", 0, 9);
            AddGossipItemFor(player, GossipOptionIcon::None, "go ", 0, 6);
            SendGossipMenuFor(player, 1, me);
            return true;
        }

        bool OnGossipSelect(Player* player, uint32 menuId, uint32 gossipId) override
        {
            auto actionId = player->PlayerTalkClass->GetGossipOptionAction(gossipId);
            ClearGossipMenuFor(player);

            if (actionId == 3)
                pause = !pause;
            else if (actionId == 4)
            {
                startEntryId--;
                AnnounceDisplay();
            }
            else if (actionId == 5)
            {
                startEntryId++;
                AnnounceDisplay();
            }
            else if (actionId == 6)
            {
                events.Reset();
                events.ScheduleEvent(1, 100ms);
            }
            else if (actionId == 7)
            {
                for (int i = 0; i < (max + 1); i += 1.0f)
                {
                    auto displayId = startEntryId + i;
                    float posX = me->GetPositionX() + float(i % iterate) * 10.0f;
                    float posY = me->GetPositionY() + float((float)i / (float)iterate) * 10.0f;
                    if (auto trigger = DoSummon(3, { posX, posY, me->GetPositionZ(), me->GetOrientation() }, 0s, TempSummonType::TEMPSUMMON_MANUAL_DESPAWN))
                        trigger->SetDisplayId(displayId);
                }
            }
            else if (actionId == 9)
            {
                summons.DespawnAll();
            }

            return OnGossipHello(player);
        }

        bool OnGossipSelectCode(Player* player, uint32 menuId, uint32 gossipId, char const* code) override
        {
            auto actionId = player->PlayerTalkClass->GetGossipOptionAction(gossipId);
            ClearGossipMenuFor(player);

            if (code)
            {
                switch (actionId)
                {
                    case 1:
                        startEntryId = atol(code);
                        break;
                    case 2:
                        time = atol(code);
                        break;
                    case 8:
                        max = atol(code);
                        break;
                    case 9:
                        iterate = atol(code);
                        iterate = std::max(1u, iterate);
                        break;
                }
            }

            return OnGossipHello(player);
        }

        void AnnounceDisplay()
        {
            std::ostringstream ss;
            ss << "model: " << startEntryId;
            me->Say(ss.str(), LANG_UNIVERSAL);
            me->SetDisplayId(startEntryId);
        }

        void UpdateAI(uint32 diff) override
        {
            if (pause)
                return;

            events.Update(diff);

            if (uint32 eventId = events.ExecuteEvent())
            {
                if (eventId == 1)
                {
                    ++startEntryId;
                    AnnounceDisplay();
                    events.Repeat(Milliseconds(time));
                }
            }
        }

        EventMap events;
};


const std::vector<uint32> t3entries =
{
    22498,
    22499,
    22496,
    22501,
    22502,
    22497,
    22500,
    39514,
    22515,
    22512,
    22517,
    22518,
    22513,
    22516,
    22506,
    22507,
    22504,
    30668,
    22510,
    22505,
    22508,
    22478,
    22479,
    22476,
    22481,
    22482,
    22477,
    22480,
    30674,
    22490,
    22491,
    22488,
    22493,
    22494,
    22489,
    22492,
    22438,
    22439,
    22436,
    22441,
    22442,
    22437,
    22440,
    22418,
    22419,
    22416,
    22421,
    22422,
    22417,
    22420,
    22428,
    22429,
    22425,
    22426,
    22431,
    22427,
    22430,
    22466,
    22467,
    22464,
    22469,
    22470,
    22465,
    22468,
};

struct npc_kazzik_t3_transmogs : public ScriptedAI
{
    public:
        npc_kazzik_t3_transmogs(Creature* creature) : ScriptedAI(creature) { }

        bool OnGossipHello(Player* player) override
        {
            ClearGossipMenuFor(player);
            AddGossipItemFor(player, GossipOptionIcon::None, "Give me my tier 3", 0, 0);
            SendGossipMenuFor(player, 1, me);
            return true;
        }

        bool OnGossipSelect(Player* player, uint32 menuId, uint32 GossipId) override
        {
            CloseGossipMenuFor(player);

            for (auto entry : t3entries)
            {
                auto temp = sObjectMgr->GetItemTemplate(entry);
              //  sObjectMgr->Getitemapp
                if (!temp)
                    continue;
                //if (player->CanUseItem(temp))
                  //  if (!player->GetSession()->GetCollectionMgr()->HasItemAppearance(temp->)

                    player->AddItem(entry, 1);
            }

            return true;
        }
};

struct npc_sturzah_800005 : public ScriptedAI
{
    public:
        npc_sturzah_800005(Creature* creature) : ScriptedAI(creature) { }

        void Reset() override
        {

        }

        bool OnGossipHello(Player* player) override
        {
            ClearGossipMenuFor(player);
            AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/Icons/achievement_pvp_h_01.blp:30:30:-28:0|tTier 1", 0, 1);
            AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/Icons/achievement_pvp_h_02.blp:30:30:-28:0|tTier 2", 0, 2);
            AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/Icons/achievement_pvp_h_03.blp:30:30:-28:0|tTier 3", 0, 3);
            AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/Icons/achievement_pvp_h_05.blp:30:30:-28:0|tTier 4", 0, 4);
            //AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/Icons/achievement_pvp_h_05.blp:30:30:-28:0|tTier 5", 0, 5);
            SendGossipMenuFor(player, 800005, me);
            return true;
        }

        bool OnGossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
        {
            uint32 actionId = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);

            switch (actionId)
            {
                case 1: player->GetSession()->SendListInventory(me->GetGUID(), me->GetEntry()); break;
                case 2: player->GetSession()->SendListInventory(me->GetGUID(), 8000051); break;
                case 3: player->GetSession()->SendListInventory(me->GetGUID(), 8000052); break;
                case 4: player->GetSession()->SendListInventory(me->GetGUID(), 8000053); break;
                case 5: player->GetSession()->SendListInventory(me->GetGUID(), 8000054); break;
                default: CloseGossipMenuFor(player); break;
            }

            return true;
        }
};

struct npc_covenant_swapper : public ScriptedAI
{
    public:
        npc_covenant_swapper(Creature* creature) : ScriptedAI(creature) { }

        void Reset() override
        {

        }

        bool OnGossipHello(Player* player) override
        {
            CloseGossipMenuFor(player);
            player->SendPlayerChoice(GetGUID(), 644);
            return true;
        }
};

const uint32 soulshapeModAuras[] = { 333206,326215,326212,326209,326207,326204,326202,326200,326197,326195,326191,326184,326181,326168,326165,326161,326157,326153,326152,349209,349213,349215,249217,349219,349221,349222,349225,321080 };

struct npc_soulshape_picker : public ScriptedAI
{
    public:
        npc_soulshape_picker(Creature* creature) : ScriptedAI(creature) { }

        void Reset() override
        {

        }


        bool OnGossipHello(Player* player) override
        {
            auto covenant = player->GetCovenant();
            ClearGossipMenuFor(player);

            if (covenant->GetCovenantID() == CovenantID::NightFae)
            {
                AddGossipItemFor(player, GossipOptionIcon::None, "Vulpin", 0, 0);
                AddGossipItemFor(player, GossipOptionIcon::None, "Toad", 0, 333206);
                AddGossipItemFor(player, GossipOptionIcon::None, "Wyvern", 0, 326215);
                AddGossipItemFor(player, GossipOptionIcon::None, "Gryphon", 0, 326212);
                AddGossipItemFor(player, GossipOptionIcon::None, "Hippogryph", 0, 326209);
                AddGossipItemFor(player, GossipOptionIcon::None, "Wolfhawk", 0, 326207);
                AddGossipItemFor(player, GossipOptionIcon::None, "Feathered Drake", 0, 326204);
                AddGossipItemFor(player, GossipOptionIcon::None, "Wolf", 0, 326202);
                AddGossipItemFor(player, GossipOptionIcon::None, "Moose", 0, 326200);
                AddGossipItemFor(player, GossipOptionIcon::None, "Bear", 0, 326197);
                AddGossipItemFor(player, GossipOptionIcon::None, "Raptor", 0, 326195);
                AddGossipItemFor(player, GossipOptionIcon::None, "Shadowstalker", 0, 326191);
                AddGossipItemFor(player, GossipOptionIcon::None, "Stag", 0, 326184);
                AddGossipItemFor(player, GossipOptionIcon::None, "Dragon Turtle", 0, 326181);
                AddGossipItemFor(player, GossipOptionIcon::None, "Tiger", 0, 326168);
                AddGossipItemFor(player, GossipOptionIcon::None, "Lion", 0, 326165);
                AddGossipItemFor(player, GossipOptionIcon::None, "Crane", 0, 326161);
                AddGossipItemFor(player, GossipOptionIcon::None, "Shrieker", 0, 326157);
                AddGossipItemFor(player, GossipOptionIcon::None, "Horned Horse", 0, 326153);
                AddGossipItemFor(player, GossipOptionIcon::None, "Moth", 0, 326152);
                AddGossipItemFor(player, GossipOptionIcon::None, "Direhorn", 0, 349209);
                AddGossipItemFor(player, GossipOptionIcon::None, "Hippo", 0, 349213);
                AddGossipItemFor(player, GossipOptionIcon::None, "Kodo", 0, 349215);
                AddGossipItemFor(player, GossipOptionIcon::None, "Mammoth", 0, 249217);
                AddGossipItemFor(player, GossipOptionIcon::None, "Saurolisk", 0, 349219);
                AddGossipItemFor(player, GossipOptionIcon::None, "Shoveltusk", 0, 349221);
                AddGossipItemFor(player, GossipOptionIcon::None, "Spider", 0, 349222);
                AddGossipItemFor(player, GossipOptionIcon::None, "Yak", 0, 349225);
                AddGossipItemFor(player, GossipOptionIcon::None, "Runestag", 0, 321080);
            }


            SendGossipMenuFor(player, 1, me);
            return true;
        }

        bool OnGossipSelect(Player* player, uint32 menuId, uint32 gossipId) override
        {
            uint32 actionId = player->PlayerTalkClass->GetGossipOptionAction(gossipId);

            for (auto spell : soulshapeModAuras)
            {
                if (player->HasSpell(spell))
                    player->RemoveSpell(spell);
                player->RemoveAurasDueToSpell(spell);
            }

            if (actionId > 0)
            {
                player->CastSpell(player, actionId, true);
                player->LearnSpell(actionId, false);
                player->RestoreDisplayId();
            }

            return OnGossipHello(player);
        }
};

struct npc_general_700000 : public ScriptedAI
{
public:
    npc_general_700000(Creature* p_Creature) : ScriptedAI(p_Creature) { }

    void OnUnitRelocation(Unit* p_Who) override
    {
        if (p_Who->IsPlayer() && p_Who->GetDistance2d(me) <= 14.0f)
        {
            auto l_Player = p_Who->ToPlayer();
            auto l_Itr = m_PlayerTalks.find(p_Who->GetGUID());
            auto l_Now = GameTime::Now();

            if (l_Itr == m_PlayerTalks.end() || l_Now >= l_Itr->second)
            {
                if (l_Player->GetQuestStatus(700000) == QUEST_STATUS_NONE)
                {
                    m_PlayerTalks[p_Who->GetGUID()] = l_Now + Hours(2);
                    Talk(0, p_Who);
                }
            }
        }
    }
private:
    std::unordered_map<ObjectGuid, TimePoint> m_PlayerTalks;
};


void AddSC_MallScripts()
{
    RegisterCreatureAI(npc_battle_training);
    RegisterCreatureAI(npc_infernal_core_360607);
    RegisterCreatureAI(npc_item_upgrade_tutorial);
    RegisterCreatureAI(npc_skipbot_3000);
    RegisterCreatureAI(npc_currency_guy);
    RegisterCreatureAI(npc_char_services);
    RegisterCreatureAI(npc_juno_700006);
    RegisterCreatureAI(npc_mall_weapongiver);
    RegisterCreatureAI(npc_morpher_admin);
    RegisterCreatureAI(npc_kazzik_t3_transmogs);
    RegisterCreatureAI(npc_sturzah_800005);
    RegisterCreatureAI(npc_covenant_swapper);
    RegisterCreatureAI(npc_soulshape_picker);
    RegisterCreatureAI(npc_general_700000);
}
