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
#include "MovementGenerator.h"
#include "GenericMovementGenerator.h"
#include "QuestAI.h"
#include "GameObjectAI.h"
#include "PlayerChallenge.h"
#include "InstanceSaveMgr.h"
#include "Pet.h"
#include "CustomObjectMgr.h"
#include "CustomInstanceScript.h"
#include "ReputationMgr.h"
#include "ChatPackets.h"

enum MallScript
{
    SpellChannel = 368481, // Druid Spiritualist
};

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

        void InitializeAI() override
        {
            me->SetEmoteState(Emote::EMOTE_STATE_DANCE);
        }

        void OnQuestAccept(Player* p_Player, Quest const* p_Quest) override
        {
            switch (p_Quest->GetQuestId())
            {
                case 700002:
                    Talk(0, p_Player);
                    break;
                case 700006:
                    Talk(3, p_Player);
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
            return (p_Player->GetQuestStatus(700000) == QUEST_STATUS_INCOMPLETE || p_Player->GetQuestStatus(700000) == QUEST_STATUS_NONE);
                //|| p_Player->GetQuestStatus(700001) == QUEST_STATUS_INCOMPLETE || p_Player->GetQuestStatus(700001) == QUEST_STATUS_NONE
                //|| p_Player->GetQuestStatus(700002) == QUEST_STATUS_INCOMPLETE || p_Player->GetQuestStatus(700002) == QUEST_STATUS_NONE
                //|| p_Player->GetQuestStatus(700003) == QUEST_STATUS_INCOMPLETE || p_Player->GetQuestStatus(700003) == QUEST_STATUS_NONE
                //|| p_Player->GetQuestStatus(700004) == QUEST_STATUS_INCOMPLETE || p_Player->GetQuestStatus(700004) == QUEST_STATUS_NONE
                //|| p_Player->GetQuestStatus(700005) == QUEST_STATUS_INCOMPLETE || p_Player->GetQuestStatus(700005) == QUEST_STATUS_NONE
                //|| p_Player->GetQuestStatus(700006) == QUEST_STATUS_INCOMPLETE || p_Player->GetQuestStatus(700006) == QUEST_STATUS_NONE);
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

                    for (uint32 l_Quest : {700000, 700006})
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
                        {
                            auto quest = l_QuestPtr;
                            auto player = p_Player;
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

                        }

                        if (l_Quest == 700000)
                        {
                            p_Player->CompleteQuest(700000);
                            p_Player->RewardQuest(l_QuestPtr, LootItemType::Item, 0, me);
                        }
                    }

                    p_Player->AddItem(700001, 1);
                    p_Player->AddItem(700000, 1);
                    GameTele const* tele = sObjectMgr->GetGameTele(1779);
                    if (!tele)
                    {
                        ChatHandler(p_Player).PSendSysMessage("Broken teleport in Robot!");
                        break;
                    }

                    p_Player->TeleportTo(tele->mapId, tele->position_x, tele->position_y, tele->position_z, tele->orientation);
                    p_Player->SetHomebind(WorldLocation(tele->mapId, tele->position_x, tele->position_y, tele->position_z, tele->orientation), 6719);

                    WorldPackets::Chat::Chat packet;
                    packet.Initialize(ChatMsg::CHAT_MSG_RAID_WARNING, Language::LANG_UNIVERSAL, p_Player, p_Player, "You have just skipped the intro!, Talk to Juno to continue with the storyline.");
                    p_Player->SendDirectMessage(packet.Write());
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

            if (p_Player->GetQuestStatus(700005) == QUEST_STATUS_REWARDED)
                AddGossipItemFor(p_Player, GossipOptionIcon::None, "Can you explain currencies again?", 0, 1);
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
            else if (p_Quest->GetQuestId() == 700003)
                Talk(2, p_Player);
            else if (p_Quest->GetQuestId() == 700005)
            {
                Talk(0, p_Player);
                p_Player->KilledMonsterCredit(700005, me->GetGUID());
            }
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
            AddGossipItemFor(p_Player, GossipOptionIcon::None, "|TInterface\\ICONS\\achievement_general.BLP:30:30:-28:0|tReset my talents.", 0, 0, [this, p_Player](std::string /*callback*/)
            {
                p_Player->ResetTalents(true);
                CloseGossipMenuFor(p_Player);
            });
            AddGossipItemFor(p_Player, GossipOptionIcon::None, "|TInterface\\ICONS\\inv_inscription_talenttome01.BLP:30:30:-28:0|tGive me 5 tomes.", 0, 0, [this, p_Player](std::string /*callback*/)
            {
                p_Player->AddItem(173049, 5);
                CloseGossipMenuFor(p_Player);
            });
            AddGossipItemFor(p_Player, GossipOptionIcon::None, "|TInterface\\ICONS\\inv_misc_enggizmos_32.BLP:30:30:-28:0|tGive me the Magic Stone.", 0, 0, [this, p_Player](std::string /*callback*/)
            {
                p_Player->AddItem(700001, 1);
                CloseGossipMenuFor(p_Player);
            });
            AddGossipItemFor(p_Player, GossipOptionIcon::None, "|TInterface\\ICONS\\inv_offhand_1h_ulduarraid_d_01.BLP:30:30:-28:0|tGive me the Item Upgrader.", 0, 0, [this, p_Player](std::string /*callback*/)
            {
                p_Player->AddItem(700000, 1);
                CloseGossipMenuFor(p_Player);
            });
            AddGossipItemFor(p_Player, GossipOptionIcon::None, "|TInterface\\ICONS\\inv_gizmo_manasyphon.BLP:30:30:-28:0|tGive me the Corruption Chisel.", 0, 0, [this, p_Player](std::string /*callback*/)
            {
                p_Player->AddItem(699998, 1);
                CloseGossipMenuFor(p_Player);
            });
            SendGossipMenuFor(p_Player, me->GetEntry(), me);
            return true;
        }
};

const uint32 questsToCompleteForStoryline[] = {
    700007, ///< The Magic Stone
    700008, ///< Enter the Maelstrom
    /// 700009, ///< Clear out the Mawsworn - REMOVED
    /// 700010, ///< DEPCREATED UNKNOWN ENTITY
    700011, ///< A Dire Warning
    700012, ///< Investigate Further
    700013, ///< A Load of Crap
    /// 700014, ///< You've gotta be kiddin' - DEPRECATED
    700015, ///< Less Money, More Problems.
    700016, ///< Secret Plan
    700017, ///< Betrayal For Power
    700018, ///< Legendary Dust?
    700019, ///< Choice of the Champion
    700020, ///< A Holy Call
    700021, ///< Purge the Temple
    700022, ///< Mysterious Portal
    700024, ///< Another Portal?
    700025, ///< Embrace the Void
    700026, ///< Avenging Our Allies
    700027, ///< Take Out The Trash
    700028, ///< Stop The Corruption
    700029, ///< Last Light At The End Of The Tunnel
    700030, ///< Am I Done Killing?
    700031, ///< Turn The Tide
    700032, ///< Time To Fight Back
    700033, ///< Clear The Way
    700034, ///< Battle Of The Mawsworn
    700035, ///< Betrayal
    700036, ///< Finish The Fight
};

struct npc_juno_700006 : public ScriptedAI
{
    public:
        npc_juno_700006(Creature* p_Creature) : ScriptedAI(p_Creature) { }

        bool OnGossipHello(Player* p_Player) override
        {
            ClearGossipMenuFor(p_Player);
            p_Player->PrepareQuestMenu(me->GetGUID());

            if (p_Player->HasAchieved(700000) && p_Player->GetQuestStatus(700006) == QUEST_STATUS_REWARDED)
            {
                AddGossipItemFor(p_Player, GossipOptionIcon::None, "I've heard this tale before.\n|cffFF0000<Skip to Thrall>", 0, 0, "Are you sure? This action cannot be undone.", 0, false, [p_Player, this](std::string /*callback*/)
                {
                    if (p_Player->HasAchieved(700000))
                    {
                        p_Player->Variables.Set("SEASON1SKIP", true);

                        for (auto questId : questsToCompleteForStoryline)
                        {
                            auto quest = sObjectMgr->GetQuestTemplate(questId);
                            if (!quest)
                                continue;

                            auto status = p_Player->GetQuestStatus(questId);
                            switch (status)
                            {
                                case QUEST_STATUS_NONE:
                                    p_Player->AddQuestAndCheckCompletion(quest, p_Player);
                                    p_Player->CompleteQuest(questId);
                                    p_Player->RewardQuest(quest, LootItemType::Item, 0, p_Player);
                                    break;
                                case QUEST_STATUS_INCOMPLETE:
                                    p_Player->CompleteQuest(questId);
                                    p_Player->RewardQuest(quest, LootItemType::Item, 0, p_Player);
                                    break;
                                case QUEST_STATUS_COMPLETE:
                                    p_Player->RewardQuest(quest, LootItemType::Item, 0, p_Player);
                                    break;
                            }
                        }

                        p_Player->ModifyCurrency(1813, -29000);
                        p_Player->AddItem(700316, 1);
                        p_Player->CastSpell(p_Player, 268065, true); ///< Fade to Black
                        p_Player->Variables.Remove("SEASON1SKIP");
                        p_Player->UpdateVisibilityForPlayer();
                        //me->DestroyForPlayer(p_Player);
                    }
                });
            }

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
                if (!player->Variables.Exist("SEASON1SKIP"))
                {
                    player->TeleportTo(2453, 2721.22f, 2099.52f, 317.48f, 3.14282f);
                    player->TeleportCallback = [player]()
                    {
                        Conversation::CreateConversation(700302, player, *player, player->GetGUID());
                    };
                }
            }
        }

        bool CanSeeOrDetect(WorldObject const* who) const override
        {
            if (who->IsPlayer())
            {
                auto player = who->ToPlayer();
                auto status = player->GetQuestStatus(700036); // 700036 finish the fight
                switch (status)
                {
                    case QUEST_STATUS_COMPLETE:
                    case QUEST_STATUS_REWARDED:
                        return false;
                    default:
                        return true;
                }
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

        bool CanSeeOrDetect(WorldObject const* who) const override
        {
            if (who->IsPlayer())
            {
                auto player = who->ToPlayer();

                if (player->IsGameMaster())
                    return true;

                auto status = player->GetQuestStatus(700019); // Choice of the champion
                switch (status)
                {
                    case QUEST_STATUS_NONE:
                        return false;
                    default:
                        return true;
                }
            }

            return false;
        }
};

struct npc_morpher_admin : public ScriptedAI
{
    public:
        npc_morpher_admin(Creature* creature) : ScriptedAI(creature), summons(creature) { }

        void InitializeAI() override
        {
            me->setActive(true);
        }

        uint32 startEntryId = 0;
        uint32 time = 250;
        uint32 max = 0;
        uint32 iterate = 9;
        bool pause = false;
        SummonList summons;
        std::string nameLike = "";

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
            AddGossipItemFor(player, GossipOptionIcon::None, "nameLike: " + nameLike, 0, 10, "", 0, true);
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
                if (!nameLike.empty())
                {
                    std::ostringstream ss;
                    ss << "%%" << nameLike << "%%";
                    auto query = WorldDatabase.PQuery("SELECT FileDataID FROM z_filedata_data WHERE FileName like '%s'", ss.str().c_str());
                    std::set<uint32> fileDataIds;
                    if (query)
                    {
                        do
                        {
                            auto fields = query->Fetch();
                            fileDataIds.insert(fields[0].GetUInt32());
                        } while (query->NextRow());
                    }

                    int x = 0;
                    for (uint32 i = 0; i < max; i ++)
                    {
                        auto displayId = startEntryId + i;
                        if (auto dispInfo = sCreatureDisplayInfoStore.LookupEntry(displayId))
                        {
                            if (auto model = sCreatureModelDataStore.LookupEntry(dispInfo->ModelID))
                            {
                                if (fileDataIds.count(model->FileDataID))
                                {
                                    float diff = x++;
                                    auto displayId = dispInfo->ID;
                                    float posX = me->GetPositionX() + float(x % iterate) * 10.0f;
                                    float posY = me->GetPositionY() + float((float)x / (float)iterate) * 10.0f;
                                    if (auto trigger = DoSummon(3, { posX, posY, me->GetPositionZ(), me->GetOrientation() }, 0s, TempSummonType::TEMPSUMMON_MANUAL_DESPAWN))
                                        trigger->SetDisplayId(displayId);
                                }
                            }
                        }
                    }
                }
                else
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

            switch (actionId)
            {
                case 10:
                    if (!code)
                        nameLike = "";
                    else
                        nameLike = std::string(code);
                    break;
            }

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

            if (me->isAnySummons())
                me->DespawnOrUnsummon();

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

            SendGossipMenuFor(player, me->GetEntry(), me);
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

            //if (actionId > 0)
            {
                if (actionId)
                {
                    player->CastSpell(player, actionId, true);
                    player->LearnSpell(actionId, false);
                }
                player->RestoreDisplayId();

                if (auto crea = player->GetSummonedCreatureByEntry(800300))
                {
                    if (auto tempSumm = crea->ToTempSummon())
                    {
                        tempSumm->InitStats(5000);
                        if (actionId)
                        {
                            for (auto spell : soulshapeModAuras)
                            {
                                //if (crea->HasSpell(spell))
                                //    crea->RemoveSpell(spell);
                                crea->RemoveAurasDueToSpell(spell);
                            }
                            crea->CastSpell(crea, actionId, true);
                        }
                        crea->AddAura(310143, crea); //< Soulshape
                        crea->RestoreDisplayId();
                        return OnGossipHello(player);
                    }
                }

                if (auto clone = player->SummonCreature(800300, { 41.3424f, -2781.91f, 63.6578f, 0.0426812f }, TEMPSUMMON_NO_OWNER_OR_TIMED_DESPAWN, 5s, 0, 0, player->GetGUID()))
                //if (auto clone = me->SummonPersonalClone(*me, TEMPSUMMON_NO_OWNER_OR_TIMED_DESPAWN, 5s, 0, 0, player))
                {
                    clone->SetUnitFlag(UnitFlags::UNIT_FLAG_UNINTERACTIBLE);
                    clone->SetOwnerGUID(player->GetGUID());
                    if (actionId)
                        clone->CastSpell(clone, actionId, true);
                    clone->AddAura(310143, clone); //< Soulshape
                    clone->RestoreDisplayId();
                    player->AddSummonedCreature(clone->GetGUID(), 800300);
                }
            }

            return OnGossipHello(player);
        }
};

const Position generalPath[] = {
    { 1871.39f, 4631.0f, 340.921f, 3.67226f },
    { 1874.57f, 4632.87f, 340.977f, 3.67226f },
    { 1878.27f, 4633.75f, 339.793f, 3.67226f },
    { 1882.13f, 4634.89f, 337.628f, 3.55446f },
    { 1883.67f, 4635.44f, 336.581f, 3.55446f },
    { 1886.16f, 4636.14f, 335.893f, 3.55446f },
    { 1892.34f, 4640.05f, 335.893f, 0.641938f },
    { 1898.92f, 4646.27f, 335.893f, 0.884102f },
    { 1899.65f, 4648.37f, 335.893f, 1.5386f },
    { 1898.88f, 4649.47f, 335.893f, 2.18655f },
    { 1897.58f, 4650.71f, 335.894f, 2.252f },
};

const Position generalPath2[] = {
    { 1897.58f, 4650.71f, 335.894f, 2.252f },
    { 1898.64f, 4646.6f, 335.894f, 4.76201f },
    { 1897.44f, 4642.41f, 335.894f, 4.08133f },
    { 1893.56f, 4639.61f, 335.894f, 3.61009f },
    { 1889.43f, 4638.06f, 335.894f, 3.48901f },
    { 1885.47f, 4636.29f, 335.894f, 3.53482f },
    { 1880.9f, 4634.33f, 338.359f, 3.55773f },
    { 1877.91f, 4633.34f, 340.063f, 3.47592f },
    { 1876.33f, 4632.79f, 340.885f, 3.47592f },
    { 1872.43f, 4631.43f, 340.971f, 3.47592f },
    { 1871.15f, 4630.95f, 340.91f, 3.76063f },
};

struct npc_general_700000 : public ScriptedAI
{
public:
    npc_general_700000(Creature* p_Creature) : ScriptedAI(p_Creature) { }

    void OnQuestAccept(Player* who, Quest const* quest) override
    {
        if (quest->GetQuestId() == 700000)
        {
            StartQuestEvent(who);
        }
    }

    void StartQuestEvent(Player* who)
    {
        if (auto clone = me->SummonPersonalClone(*me, TEMPSUMMON_NO_OWNER_DESPAWN, 0s, 0, 0, who))
        {
            clone->setActive(true);
            clone->SetOwnerGUID(who->GetGUID());
            if (clone->AI())
                clone->AI()->DoAction(1);
        }
    }

    bool OnGossipHello(Player* player) override
    {
        ClearGossipMenuFor(player);
        player->PrepareQuestMenu(me->GetGUID());
        if (player->GetQuestStatus(700000) == QUEST_STATUS_INCOMPLETE && !me->IsSummon() && me->HasNpcFlag(NPCFlags::UNIT_NPC_FLAG_QUESTGIVER))
        {
            AddGossipItemFor(player, GossipOptionIcon::None, "I'm ready", 0, 0, [this, player](std::string /*callback*/)
            {
                CloseGossipMenuFor(player);
                StartQuestEvent(player);
            });
        }
        SendGossipMenuFor(player, me->GetEntry(), me);
        return true;
    }

    bool didMagicStoneSay = false;
    void OnUnitRelocation(Unit* p_Who) override
    {
        if (p_Who->IsPlayer() && p_Who->GetDistance2d(me) <= 14.0f && !me->IsSummon() && me->IsInPhase(p_Who))
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
        if (p_Who->IsPlayer() && me->IsSummon() && !didMagicStoneSay && me->IsInPhase(p_Who) && p_Who->GetDistance2d(me) <= 14.0f && p_Who == me->GetOwner() && p_Who->ToPlayer()->GetQuestStatus(700006) == QUEST_STATUS_INCOMPLETE)
        {
            didMagicStoneSay = true;
            Talk(4, me->GetOwner());

            scheduler.Schedule(8s, [this](TaskContext context)
            {
                me->GetMotionMaster()->MovePoint(1, { 1871.18f, 4630.88f, 340.91f, 3.67503f }, MOVE_PATHFINDING, 3.67503f)->callbackFunc = [this]()
                {
                    me->DespawnOrUnsummon();
                };
            });
        }
    }

    void UpdateAI(uint32 diff) override
    {
        scheduler.Update(diff);
    }

    void DoAction(int32 action) override
    {
        if (action != 1)
            return;

        me->RemoveNpcFlag(NPCFlags::UNIT_NPC_FLAG_QUESTGIVER);
        TalkWithOwner(1);

        scheduler.Schedule(1s, [this](TaskContext context)
        {
            me->GetMotionMaster()->MoveSmoothPath(1, generalPath, 11, true, false, 5.0f)->callbackFunc = [this]()
            {
                TalkWithOwner(2);
                scheduler.Schedule(6s, [this](TaskContext context)
                {
                    if (auto covenantDummy = me->FindNearestCreature(700047, 50.0f))
                    {
                        if (auto clone = covenantDummy->SummonPersonalClone(*covenantDummy, TEMPSUMMON_NO_OWNER_DESPAWN, 0s, 0, 0, me->GetCharmerOrOwnerPlayerOrPlayerItself()))
                        {
                            clone->setActive(true);
                            clone->SetOwnerGUID(me->GetOwnerGUID());
                            if (auto ai = clone->AI())
                            {
                                ai->Talk(0, me->GetOwner());
                                ai->DoAction(1);
                            }
                        }

                        if (auto owner = me->GetOwner())
                            if (auto player = owner->ToPlayer())
                                player->KilledMonsterCredit(me->GetEntry());
                    }
                    me->GetMotionMaster()->MovePoint(1, { 1907.14f, 4633.52f, 335.897f, 0.438526f }, MOVE_PATHFINDING | MOVE_WALK_MODE, 0.265084f)->callbackFunc = [this]()
                    {
                        me->HandleEmoteCommand(Emote::EMOTE_ONESHOT_TALK, OwnerAsPlayer());
                        scheduler.Schedule(1s, [this](TaskContext context)
                        {
                            if (auto c = me->FindNearestCreature(700017, 50.0f))
                            {
                                c->HandleEmoteCommand(Emote::EMOTE_ONESHOT_TALK, OwnerAsPlayer());
                            }
                            scheduler.Schedule(1s, [this](TaskContext context)
                            {
                                me->GetMotionMaster()->MovePoint(1, { 1946.99f, 4693.16f, 335.893f, 1.73771f }, MOVE_PATHFINDING | MOVE_WALK_MODE, 1.73771f)->callbackFunc = [this]()
                                {
                                    me->HandleEmoteCommand(Emote::EMOTE_ONESHOT_TALK, OwnerAsPlayer());
                                    scheduler.Schedule(1s, [this](TaskContext context)
                                    {
                                        if (auto c = me->FindNearestCreature(700005, 50.0f))
                                        {
                                            c->HandleEmoteCommand(Emote::EMOTE_ONESHOT_TALK, OwnerAsPlayer());
                                        }

                                        scheduler.Schedule(1s, [this](TaskContext context)
                                        {
                                            me->GetMotionMaster()->MovePoint(1, { 1973.46f, 4699.25f, 335.893f, 1.27956f }, MOVE_PATHFINDING | MOVE_WALK_MODE, 1.27956f)->callbackFunc = [this]()
                                            {
                                                me->HandleEmoteCommand(Emote::EMOTE_ONESHOT_TALK, OwnerAsPlayer());
                                                scheduler.Schedule(1s, [this](TaskContext context)
                                                {
                                                    if (auto c = me->FindNearestCreature(700003, 50.0f))
                                                    {
                                                        c->HandleEmoteCommand(Emote::EMOTE_ONESHOT_TALK, OwnerAsPlayer());
                                                    }

                                                    scheduler.Schedule(1s, [this](TaskContext context)
                                                    {
                                                        me->GetMotionMaster()->MovePoint(1, { 2016.78f, 4682.53f, 339.811f, 6.20794f }, MOVE_PATHFINDING | MOVE_WALK_MODE, 6.20794f)->callbackFunc = [this]()
                                                        {
                                                            me->HandleEmoteCommand(Emote::EMOTE_ONESHOT_TALK, OwnerAsPlayer());
                                                            scheduler.Schedule(1s, [this](TaskContext context)
                                                            {
                                                                if (auto c = me->FindNearestCreature(700030, 50.0f))
                                                                {
                                                                    c->HandleEmoteCommand(Emote::EMOTE_ONESHOT_TALK, OwnerAsPlayer());
                                                                }

                                                                scheduler.Schedule(1s, [this](TaskContext context)
                                                                {
                                                                    me->GetMotionMaster()->MovePoint(1, { 2000.89f, 4673.6f, 339.882f, 3.09252f }, MOVE_PATHFINDING | MOVE_WALK_MODE, 3.09252f)->callbackFunc = [this]()
                                                                    {
                                                                    };
                                                                });
                                                            });
                                                        };
                                                    });
                                                });
                                            };
                                        });
                                    });
                                };
                            });
                        });
                    };
                });
            };
        });
    }

    void TalkWithOwner(uint32 talkId)
    {
        Talk(talkId, me->GetOwner());
    }

    Player* OwnerAsPlayer()
    {
        return me->GetCharmerOrOwnerPlayerOrPlayerItself();
    }

private:
    std::unordered_map<ObjectGuid, TimePoint> m_PlayerTalks;
    TaskScheduler scheduler;
};

struct npc_combat_testing_shaman : public ScriptedAI
{
public:
    npc_combat_testing_shaman(Creature* creature) : ScriptedAI(creature) { }

    bool OnGossipHello(Player* player) override
    {
        ClearGossipMenuFor(player);
        player->PrepareQuestMenu(me->GetGUID());

        if (player->GetQuestStatus(700001) == QUEST_STATUS_INCOMPLETE)
        {
            if (auto objective = player->GetQuestObjectiveStatusData(700001, QUEST_OBJECTIVE_MONSTER, 700047))
            {
                auto counter = player->GetQuestSlotCounter(objective->QuestStatusItr->second.Slot, objective->Objective->StorageIndex);
                if (counter > 0)
                    AddGossipItemFor(player, GossipOptionIcon::None, "|cffFF0000<Quest>|R Enter Incursion", 0, 1);
            }
        }
        SendGossipMenuFor(player, me->GetEntry(), me);
        return true;
    }

    void OnQuestAccept(Player* player, Quest const* quest) override
    {
        if (quest->GetQuestId() == 700001)
            Talk(0, player);
        else if (quest->GetQuestId() == 700004)
            Talk(3, player);
    }

    bool OnGossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
    {
        player->CastSpell(me, 313352); // activating
        CloseGossipMenuFor(player);
        return true;
    }
};

class npc_spirit_healer : public ScriptedAI
{
public:
    npc_spirit_healer(Creature* creature) : ScriptedAI(creature) { }

    bool OnGossipHello(Player* player) override
    {
        ClearGossipMenuFor(player);

        AddGossipItemFor(player, GossipOptionIcon::None, "Resurrect me, please.", 0, 1);

        SendGossipMenuFor(player, me->GetEntry(), me);
        return true;
    }

    bool OnGossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
    {
        player->ResurrectPlayer(100.0, false);
        CloseGossipMenuFor(player);
        return true;
    }
};

// 313352
class spell_activating_313352 : public SpellScript
{
    PrepareSpellScript(spell_activating_313352);

    void DoEffect(SpellEffIndex /*eff*/)
    {
        if (auto caster = GetCaster())
        {
            caster->CastSpell(caster, 313445, true); // nyalotha incursion
            if (auto player = caster->ToPlayer())
                player->KilledMonsterCredit(700017);
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_activating_313352::DoEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
    }
};

// make spell script for nyalotha incursion to periodically summon mobs
// spell_nyalotha_incursion
class spell_nyalotha_incursion : public AuraScript
{
    PrepareAuraScript(spell_nyalotha_incursion);

    bool spawnedBoss = false;

    void HandleUpdate(uint32 diff)
    {
        if (Unit* caster = GetCaster())
        {
            switch (caster->GetMapId())
            {
                case 1116:
                    break;
                default:
                    return;
            }

            if (auto player = caster->ToPlayer())
            {
                if (!spawnedBoss)
                {
                    if (auto objective = player->GetQuestObjectiveStatusData(700001, QUEST_OBJECTIVE_MONSTER, 700040))
                    {
                        auto counter = player->GetQuestSlotCounter(objective->QuestStatusItr->second.Slot, objective->Objective->StorageIndex);
                        if (counter >= 5)
                        {
                            spawnedBoss = true;
                            if (auto spawn = player->SummonCreature(700065, { 1946.01f, 4652.43f, 335.893f, 3.45576f }, TEMPSUMMON_CORPSE_DESPAWN, 3s, 0, 0, player->GetGUID()))
                            {
                                if (auto ai = spawn->AI())
                                {
                                    ai->AttackStart(player);
                                }
                            }
                        }
                    }
                }

                if (player->GetQuestStatus(700001) == QUEST_STATUS_COMPLETE)
                    player->CastSpell(player, 313613, true); // Leave nyalotha
            }
        }
    }

    void Register() override
    {
        OnAuraUpdate += AuraUpdateFn(spell_nyalotha_incursion::HandleUpdate);
    }
};

class spell_leave_nyalotha : public SpellScript
{
    PrepareSpellScript(spell_leave_nyalotha);

    void DoEffect(SpellEffIndex /*eff*/)
    {
        if (auto caster = GetCaster())
        {
            if (auto player = caster->ToPlayer())
            {
                if (player->GetQuestStatus(700001) == QUEST_STATUS_COMPLETE)
                {
                    caster->CastSpell(caster, 365581, true); // Fade to black
                    player->NearTeleportTo({ 1907.97f, 4634.35f, 335.899f, 0.333813f }, true, true);
                    player->GetScheduler().Schedule(4s, [](TaskContext context)
                    {
                        auto player1 = context.GetUnit()->ToPlayer();
                        if (player1->GetQuestStatus(700001) == QUEST_STATUS_COMPLETE)
                            if (auto creature = player1->FindNearestCreature(700017, 50.0f, true))
                            {
                                if (auto ai = creature->AI())
                                    ai->Talk(1, player1);
                            }
                    });
                }
            }
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_leave_nyalotha::DoEffect, EFFECT_0, SPELL_EFFECT_REMOVE_AURA);
    }
};

// 365581
class spell_fade_to_black_365581 : public AuraScript
{
    PrepareAuraScript(spell_fade_to_black_365581);

    void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        PreventDefaultAction();
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_fade_to_black_365581::OnApply, EFFECT_1, SPELL_AURA_MOD_ROOT, AURA_EFFECT_HANDLE_REAL);
    }
};

class spell_fade_to_black_365581_spellscript : public SpellScript
{
    PrepareSpellScript(spell_fade_to_black_365581_spellscript);

    void PreventTrigger(SpellEffIndex effIndex)
    {
        PreventHitEffect(effIndex);
    }

    void Register() override
    {
        OnEffectHit += SpellEffectFn(spell_fade_to_black_365581_spellscript::PreventTrigger, EFFECT_2, SPELL_EFFECT_TRIGGER_SPELL);
    }
};

struct npc_sensei_700043 : public ScriptedAI
{
public:
    npc_sensei_700043(Creature* creature) : ScriptedAI(creature) { }

    void InitializeAI() override
    {
        me->SetEmoteState(Emote::EMOTE_STATE_READY1H);
        events.ScheduleEvent(1, 5s);
    }

    void UpdateAI(uint32 diff) override
    {
        events.Update(diff);
        scheduler.Update(diff);

        if (uint32 eventId = events.ExecuteEvent())
        {
            if (eventId == 1)
            {
                Emote randomEmote = RAND(Emote::EMOTE_ONESHOT_DODGE, Emote::EMOTE_ONESHOT_KICK, EMOTE_ONESHOT_MONKOFFENSE_ATTACKUNARMED, EMOTE_ONESHOT_MONKOFFENSE_SPECIALUNARMED, EMOTE_ONESHOT_MONKOFFENSE_PARRYUNARMED);

                me->HandleEmoteCommand(randomEmote);

                scheduler.Schedule(2s, [this, randomEmote](TaskContext context)
                    {
                        std::list<Unit*> trainees;
                        me->GetFriendlyUnitListInRange(trainees, 50.0f, true);
                        for (auto u : trainees)
                        {
                            if (u->GetEntry() == 700041)
                                u->HandleEmoteCommand(randomEmote);
                        }
                    });

                events.Repeat(5s);
            }
        }
    }

    TaskScheduler scheduler;
    EventMap events;
};


struct npc_recruit_700041 : public ScriptedAI
{
    public:
        npc_recruit_700041(Creature* creature) : ScriptedAI(creature) { }

        void InitializeAI() override
        {
            me->SetEmoteState(Emote::EMOTE_STATE_READY1H);
        }
};
// 700032 - npc_blacksmith_apprentice_700032
struct npc_blacksmith_apprentice_700032 : public ScriptedAI
{
   public:
      npc_blacksmith_apprentice_700032(Creature* creature) : ScriptedAI(creature) { }

     void InitializeAI() override
     {
         events.ScheduleEvent(1, 2s);
     }

     void Reset() override
     {
        /// TODO: Fill this function
     }

     void UpdateAI(uint32 diff) override
     {
        scheduler.Update(diff);
        events.Update(diff);

        if (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
                case 1:
                {
                    me->SetEmoteState(Emote::EMOTE_ONESHOT_NONE);
                    me->GetMotionMaster()->MovePoint(1, { 1971.99f, 4717.81f, 335.894f, 2.01259f }, MOVE_PATHFINDING | MOVE_WALK_MODE, 2.01259f)->callbackFunc = [this]()
                    {
                        me->SetEmoteState(Emote::EMOTE_STATE_WORK_MINING);
                    };
                    events.ScheduleEvent(2, 15s, 20s);
                    break;
                }
                case 2:
                {
                    me->SetEmoteState(Emote::EMOTE_ONESHOT_NONE);
                    me->GetMotionMaster()->MovePoint(1, me->GetHomePosition(), MOVE_PATHFINDING | MOVE_WALK_MODE, me->GetHomePosition().GetOrientation())->callbackFunc = [this]()
                    {
                        me->SetEmoteState(Emote::EMOTE_STATE_USE_STANDING);
                    };
                    events.ScheduleEvent(3, 3s, 6s);
                    break;
                }
                case 3:
                {
                    me->SetEmoteState(Emote::EMOTE_ONESHOT_NONE);
                    me->GetMotionMaster()->MovePoint(1, { 1976.03f, 4718.24f, 335.893f, 1.47747f }, MOVE_PATHFINDING | MOVE_WALK_MODE, 1.47747f)->callbackFunc = [this]()
                    {
                        me->SetEmoteState(Emote::EMOTE_STATE_USE_STANDING);
                    };
                    events.ScheduleEvent(1, 10s, 12s);
                    break;
                }
            }
        }
        if (UpdateVictim())
            DoMeleeAttackIfReady();
     }

     TaskScheduler scheduler;
     EventMap events;
};

// 700035 - npc_blacksmith_apprentice_700035
struct npc_blacksmith_apprentice_700035 : public ScriptedAI
{
public:
    npc_blacksmith_apprentice_700035(Creature* creature) : ScriptedAI(creature) { }

    void InitializeAI() override
    {
        DoCastSelf(350558); // Sleep cosmetic zzz
        me->SetStandState(UnitStandStateType::UNIT_STAND_STATE_SIT_HIGH_CHAIR);
    }

    void Reset() override
    {
        /// TODO: Fill this function
    }

    void UpdateAI(uint32 diff) override
    {
        scheduler.Update(diff);

        if (!UpdateVictim())
            return;

        events.Update(diff);

        if (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
            }
        }
        DoMeleeAttackIfReady();
    }

    TaskScheduler scheduler;
    EventMap events;
};

// 700060 - npc_dummy_700060
struct npc_dummy_700060 : public ScriptedAI
{
public:
    npc_dummy_700060(Creature* creature) : ScriptedAI(creature) { }

    void InitializeAI() override
    {
        me->SetStandState(UnitStandStateType::UNIT_STAND_STATE_SIT_HIGH_CHAIR);
    }

    void Reset() override
    {
        /// TODO: Fill this function
    }

    void UpdateAI(uint32 diff) override
    {
        scheduler.Update(diff);

        if (!UpdateVictim())
            return;

        events.Update(diff);

        if (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
            }
        }
        DoMeleeAttackIfReady();
    }


    TaskScheduler scheduler;
    EventMap events;
};
// 700056 - npc_dummy_700056
struct npc_dummy_700056 : public ScriptedAI
{
public:
    npc_dummy_700056(Creature* creature) : ScriptedAI(creature) { }

    void InitializeAI() override
    {
        me->SetStandState(UnitStandStateType::UNIT_STAND_STATE_SIT_HIGH_CHAIR);
    }

    void Reset() override
    {
        /// TODO: Fill this function
    }

    void UpdateAI(uint32 diff) override
    {
        scheduler.Update(diff);

        if (!UpdateVictim())
            return;

        events.Update(diff);

        if (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
            }
        }
        DoMeleeAttackIfReady();
    }


    TaskScheduler scheduler;
    EventMap events;
};
// 700059 - npc_dummy_700059
struct npc_dummy_700059 : public ScriptedAI
{
public:
    npc_dummy_700059(Creature* creature) : ScriptedAI(creature) { }

    void InitializeAI() override
    {
        me->SetStandState(UnitStandStateType::UNIT_STAND_STATE_SIT_HIGH_CHAIR);
    }

    void Reset() override
    {
        /// TODO: Fill this function
    }

    void UpdateAI(uint32 diff) override
    {
        scheduler.Update(diff);

        if (!UpdateVictim())
            return;

        events.Update(diff);

        if (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
            }
        }
        DoMeleeAttackIfReady();
    }


    TaskScheduler scheduler;
    EventMap events;
};
// 700057 - npc_dummy_700057
struct npc_dummy_700057 : public ScriptedAI
{
public:
    npc_dummy_700057(Creature* creature) : ScriptedAI(creature) { }

    void InitializeAI() override
    {
        me->SetStandState(UnitStandStateType::UNIT_STAND_STATE_SIT_HIGH_CHAIR);
    }

    void Reset() override
    {
        /// TODO: Fill this function
    }

    void UpdateAI(uint32 diff) override
    {
        scheduler.Update(diff);

        if (!UpdateVictim())
            return;

        events.Update(diff);

        if (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
            }
        }
        DoMeleeAttackIfReady();
    }


    TaskScheduler scheduler;
    EventMap events;
};
// 700058 - npc_general_yelnats_700058
struct npc_general_yelnats_700058 : public ScriptedAI
{
public:
    npc_general_yelnats_700058(Creature* creature) : ScriptedAI(creature) { }

    void InitializeAI() override
    {
        /// TODO: Fill this function
    }

    void Reset() override
    {
        /// TODO: Fill this function
    }

    void UpdateAI(uint32 diff) override
    {
        scheduler.Update(diff);

        if (!UpdateVictim())
            return;

        events.Update(diff);

        if (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
            }
        }
        DoMeleeAttackIfReady();
    }


    TaskScheduler scheduler;
    EventMap events;
};
// 700039 - npc_pandaren_scribe_700039
struct npc_pandaren_scribe_700039 : public ScriptedAI
{
public:
    npc_pandaren_scribe_700039(Creature* creature) : ScriptedAI(creature) { }

    void InitializeAI() override
    {
        me->SetEmoteState(Emote::EMOTE_STATE_READ);
    }

    void Reset() override
    {
        /// TODO: Fill this function
    }

    void UpdateAI(uint32 diff) override
    {
        scheduler.Update(diff);

        if (!UpdateVictim())
            return;

        events.Update(diff);

        if (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
            }
        }
        DoMeleeAttackIfReady();
    }


    TaskScheduler scheduler;
    EventMap events;
};
// 700044 - npc_bank_security_700044
struct npc_bank_security_700044 : public ScriptedAI
{
public:
    npc_bank_security_700044(Creature* creature) : ScriptedAI(creature) { }

    void InitializeAI() override
    {
        /// TODO: Fill this function
    }

    void Reset() override
    {
        /// TODO: Fill this function
    }

    void UpdateAI(uint32 diff) override
    {
        scheduler.Update(diff);

        if (!UpdateVictim())
            return;

        events.Update(diff);

        if (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
            }
        }
        DoMeleeAttackIfReady();
    }


    TaskScheduler scheduler;
    EventMap events;
};
// 700063 - npc_captain_myra_700063
struct npc_captain_myra_700063 : public ScriptedAI
{
public:
    npc_captain_myra_700063(Creature* creature) : ScriptedAI(creature) { }

    struct PlayerDataz
    {
        TimePoint Point;
        uint32 GroupId = 0;
    };

    std::unordered_map<ObjectGuid::LowType, PlayerDataz> m_playerRelocations;

    Unit* GetReciever(ObjectGuid const& guid)
    {
        return ObjectAccessor::GetUnit(*me, guid);
    }

    void OnUnitRelocation(Unit* who) override
    {
        if (who->IsPlayer() && who->GetDistance2d(me) <= 25.0f && !me->isDead() && me->IsInPhase(who))
        {
            auto now = GameTime::Now();
            auto itr = m_playerRelocations.find(who->GetGUID().GetCounter());
            bool contains = itr != m_playerRelocations.end();
            if (!contains || now >= itr->second.Point)
            {
                if (!contains)
                {
                    PlayerDataz data;
                    data.Point = now + 10s;
                    m_playerRelocations[who->GetGUID().GetCounter()] = data;
                }

                auto& data = m_playerRelocations[who->GetGUID().GetCounter()];
                data.Point = now + 10s;
                ObjectGuid const& guid = who->GetGUID();

                switch (data.GroupId)
                {
                    case 0:
                        scheduler.Schedule(1s, [this, guid](TaskContext)
                        {
                            Talk(0, GetReciever(guid));
                            scheduler.Schedule(5s, [this, guid](TaskContext context)
                            {
                                if (auto scout = me->FindNearestCreature(700061, 50.0f))
                                    if (auto ai = scout->AI())
                                        ai->Talk(0, GetReciever(guid));
                            });
                        });
                        data.GroupId++;
                        break;
                    case 1:
                        Talk(1, GetReciever(guid));
                        scheduler.Schedule(5s, [this, guid](TaskContext context)
                        {
                            if (auto scout = me->FindNearestCreature(700062, 50.0f))
                                if (auto ai = scout->AI())
                                    ai->Talk(0, GetReciever(guid));
                        });
                        data.GroupId++;
                        break;
                    case 2:
                        Talk(2, GetReciever(guid));
                        scheduler.Schedule(5s, [this, guid](TaskContext context)
                        {
                            if (auto scout = me->FindNearestCreature(700062, 50.0f))
                                if (auto ai = scout->AI())
                                    ai->Talk(1, GetReciever(guid));
                            scheduler.Schedule(5s, [this, guid](TaskContext context)
                            {
                                if (auto scout = me->FindNearestCreature(700061, 50.0f))
                                    if (auto ai = scout->AI())
                                        ai->Talk(1, GetReciever(guid));
                            });
                        });
                        data.GroupId++;
                        break;
                    case 3: // nothing left.
                        data.Point = now + 900000s;
                        break;
                }
            }
        }
    }

    void UpdateAI(uint32 diff) override
    {
        scheduler.Update(diff);

        if (!UpdateVictim())
            return;

        DoMeleeAttackIfReady();
    }


    TaskScheduler scheduler;
};

// 700062 - npc_scout_700062
struct npc_scout_700062 : public ScriptedAI
{
public:
    npc_scout_700062(Creature* creature) : ScriptedAI(creature) { }

    void InitializeAI() override
    {
        /// TODO: Fill this function
    }

    void Reset() override
    {
        /// TODO: Fill this function
    }

    void UpdateAI(uint32 diff) override
    {
        scheduler.Update(diff);

        if (!UpdateVictim())
            return;

        events.Update(diff);

        if (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
            }
        }
        DoMeleeAttackIfReady();
    }


    TaskScheduler scheduler;
    EventMap events;
};
// 700061 - npc_scout_700061
struct npc_scout_700061 : public ScriptedAI
{
public:
    npc_scout_700061(Creature* creature) : ScriptedAI(creature) { }

    void InitializeAI() override
    {
        /// TODO: Fill this function
    }

    void Reset() override
    {
        /// TODO: Fill this function
    }

    void UpdateAI(uint32 diff) override
    {
        scheduler.Update(diff);

        if (!UpdateVictim())
            return;

        events.Update(diff);

        if (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
            }
        }
        DoMeleeAttackIfReady();
    }


    TaskScheduler scheduler;
    EventMap events;
};

const Position longcloudPath[] = {
    { 1927.58f, 4673.83f, 335.894f, 5.92453f },
    { 1956.02f, 4658.9f, 335.894f, 5.5351f },
    { 1963.45f, 4647.04f, 335.909f, 5.21767f },
    { 1967.43f, 4638.14f, 335.968f, 4.87733f },
    { 1967.42f, 4635.29f, 335.915f, 5.20131f },
    { 1969.95f, 4633.09f, 335.909f, 5.59728f },
};

// 700051 - npc_galara_longcloud_700051
struct npc_galara_longcloud_700051 : public ScriptedAI
{
public:
    npc_galara_longcloud_700051(Creature* creature) : ScriptedAI(creature) { }

    void InitializeAI() override
    {
        if (!me->IsSummon())
            events.ScheduleEvent(1, 1s);
        else
            events.ScheduleEvent(2, 2s);
    }

    void Reset() override
    {
    }

    void UpdateAI(uint32 diff) override
    {
        scheduler.Update(diff);

        events.Update(diff);

        if (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
                case 1:
                    if (urand(0, 5) == 1)
                        me->HandleEmoteCommand(Emote::EMOTE_ONESHOT_EXCLAMATION);
                    else
                        me->HandleEmoteCommand(Emote::EMOTE_ONESHOT_TALK);
                    events.Repeat(5s);
                    break;
                case 2:
                    Talk(0, me->GetOwner());
                    scheduler.Schedule(3s, [this](TaskContext context)
                    {
                        me->GetMotionMaster()->MoveSmoothPath(1, longcloudPath, 6, true)->callbackFunc = [this]()
                        {
                            me->GetMotionMaster()->MovePoint(1, { 1970.85f, 4633.2f, 335.91f, 3.98382f }, MOVE_FORCE_DESTINATION, 3.98328f)->callbackFunc = [this]()
                            {
                                me->SetStandState(UnitStandStateType::UNIT_STAND_STATE_SIT_HIGH_CHAIR);
                                me->NearTeleportTo(*me);
                            };
                        };
                    });
                    break;
            }
        }

        if (!UpdateVictim())
            return;

        DoMeleeAttackIfReady();
    }

    GuidSet personals;

    void OnUnitRelocation(Unit* who) override
    {
        if (who->IsPlayer() && who->GetDistance2d(me) <= 15.0f && !me->IsSummon() && me->IsInPhase(who))
        {
            if (!personals.count(who->GetGUID()))
            {
                personals.insert(who->GetGUID());
                if (auto clone = me->SummonPersonalClone(*me, TEMPSUMMON_NO_OWNER_DESPAWN, 0s, 0, 0, who->ToPlayer()))
                {
                    clone->setActive(true);
                    clone->SetOwnerGUID(who->GetGUID());
                }

                if (auto jinjin = me->FindNearestCreatureBySpawnId(1054589, 50.0f)) // Jinjin
                    if (auto clone = jinjin->SummonPersonalClone(*jinjin, TEMPSUMMON_NO_OWNER_DESPAWN, 0s, 0, 0, who->ToPlayer()))
                    {
                        clone->setActive(true);
                        clone->SetOwnerGUID(who->GetGUID());
                    }
            }
        }
    }


    TaskScheduler scheduler;
    EventMap events;
};

const Position jinjinPath[] = {
    { 1929.82f, 4676.12f, 335.894f, 5.80213f },
    { 1946.97f, 4668.35f, 335.894f, 5.86758f },
    { 1958.25f, 4660.89f, 335.894f, 5.36034f },
    { 1964.06f, 4647.4f, 335.908f, 5.16399f },
    { 1967.44f, 4637.32f, 335.949f, 4.96764f },
    { 1968.95f, 4633.13f, 335.905f, 4.12661f },
};
// 700050 - npc_jinjin_700050
struct npc_jinjin_700050 : public ScriptedAI
{
public:
    npc_jinjin_700050(Creature* creature) : ScriptedAI(creature) { }

    void InitializeAI() override
    {
        if (!me->IsSummon())
            events.ScheduleEvent(1, 3s);
        else
            events.ScheduleEvent(2, 5500ms);
    }

    void Reset() override
    {
    }

    void UpdateAI(uint32 diff) override
    {
        scheduler.Update(diff);
        events.Update(diff);

        if (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
                case 1:
                    if (urand(0, 5) == 1)
                        me->HandleEmoteCommand(Emote::EMOTE_ONESHOT_EXCLAMATION);
                    else
                        me->HandleEmoteCommand(Emote::EMOTE_ONESHOT_TALK);
                    events.Repeat(5s);
                    break;
                case 2:
                    me->GetMotionMaster()->MoveSmoothPath(1, jinjinPath, 6, true)->callbackFunc = [this]()
                    {
                        me->GetMotionMaster()->MovePoint(1, { 1969.73f, 4634.2f, 335.903f, 3.94335f }, MOVE_FORCE_DESTINATION, 3.98328f)->callbackFunc = [this]()
                        {
                            me->SetStandState(UnitStandStateType::UNIT_STAND_STATE_SIT_HIGH_CHAIR);
                            me->NearTeleportTo(*me);
                        };
                    };
                    break;
            }
        }

        if (!UpdateVictim())
            return;

        DoMeleeAttackIfReady();
    }


    TaskScheduler scheduler;
    EventMap events;
};
// 700045 - npc_gordo_remsay_700045
struct npc_gordo_remsay_700045 : public ScriptedAI
{
public:
    npc_gordo_remsay_700045(Creature* creature) : ScriptedAI(creature) { }

    void InitializeAI() override
    {
    }

    void Reset() override
    {
    }

    void UpdateAI(uint32 diff) override
    {
        scheduler.Update(diff);

        if (!UpdateVictim())
            return;

        events.Update(diff);

        if (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
            }
        }
        DoMeleeAttackIfReady();
    }

    GuidSet personals;

    void OnUnitRelocation(Unit* who) override
    {
        if (who->IsPlayer() && who->GetDistance2d(me) <= 15.0f && !personals.count(who->GetGUID()) && me->IsInPhase(who))
        {
            personals.insert(who->GetGUID());
            me->HandleEmoteCommand(Emote::EMOTE_ONESHOT_WAVE, who->ToPlayer());
        }
    }

    TaskScheduler scheduler;
    EventMap events;
};
// 700048 - npc_hye_gyo_giftview_700048
struct npc_hye_gyo_giftview_700048 : public ScriptedAI
{
public:
    npc_hye_gyo_giftview_700048(Creature* creature) : ScriptedAI(creature) { }

    void InitializeAI() override
    {
    }

    void Reset() override
    {
    }

    void UpdateAI(uint32 diff) override
    {
        scheduler.Update(diff);

        if (!UpdateVictim())
            return;

        events.Update(diff);

        if (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
            }
        }
        DoMeleeAttackIfReady();
    }

    GuidSet personals;

    void OnUnitRelocation(Unit* who) override
    {
        if (who->IsPlayer() && who->GetDistance2d(me) <= 9.0f && !personals.count(who->GetGUID()) && me->IsInPhase(who))
        {
            personals.insert(who->GetGUID());
            Talk(0, who->ToPlayer());
        }
    }

    TaskScheduler scheduler;
    EventMap events;
};
// 700054 - npc_captain_flametalon_700054
struct npc_captain_flametalon_700054 : public ScriptedAI
{
public:
    npc_captain_flametalon_700054(Creature* creature) : ScriptedAI(creature) { }

    void UpdateAI(uint32 diff) override
    {
        scheduler.Update(diff);

        if (!UpdateVictim())
            return;

        events.Update(diff);

        if (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
            }
        }
        DoMeleeAttackIfReady();
    }

    void SetGUID(ObjectGuid const& guid, int32 id) override
    {
        if (id == 1)
            _RecruitOne = guid;
        else if (id == 2)
            _RecruitTwo = guid;
    }

    void DoAction(int32 action) override
    {
        if (action == 1)
        {
            scheduler.Schedule(3s, [this](TaskContext context)
            {
                if (auto recruit = ObjectAccessor::GetCreature(*me, _RecruitOne))
                    if (recruit->AI())
                    {
                        recruit->AI()->SetGUID(_RecruitTwo, 1);
                        recruit->AI()->SetGUID(me->GetGUID(), 2);
                    }
                if (auto recruit = ObjectAccessor::GetCreature(*me, _RecruitTwo))
                    if (recruit->AI())
                    {
                        recruit->AI()->SetGUID(_RecruitOne, 1);
                        recruit->AI()->SetGUID(me->GetGUID(), 2);
                    }
            });
        }
    }

    ObjectGuid _RecruitOne;
    ObjectGuid _RecruitTwo;
    GuidUnorderedSet seers;

    void OnUnitRelocation(Unit* who) override
    {
        if (who->IsPlayer() && !seers.count(who->GetGUID()) && who->GetDistance2d(me) <= 15.0f && !me->IsSummon() && me->IsInPhase(who))
        {
            seers.insert(who->GetGUID());
            ObjectGuid RecruitOne;
            ObjectGuid RecruitTwo;

            if (auto recruit = me->FindNearestCreatureBySpawnId(1054591, 50.0f))
                if (auto clone = recruit->SummonPersonalClone(*recruit, TEMPSUMMON_NO_OWNER_OR_TIMED_DESPAWN, 120s, 0, 0, who->ToPlayer()))
                {
                    clone->setActive(true);
                    clone->SetOwnerGUID(who->GetGUID());
                    RecruitOne = clone->GetGUID();
                }
            if (auto recruit = me->FindNearestCreatureBySpawnId(1054592, 50.0f))
                if (auto clone = recruit->SummonPersonalClone(*recruit, TEMPSUMMON_NO_OWNER_OR_TIMED_DESPAWN, 120s, 0, 0, who->ToPlayer()))
                {
                    clone->setActive(true);
                    clone->SetOwnerGUID(who->GetGUID());
                    RecruitTwo = clone->GetGUID();
                }

            if (auto clone = me->SummonPersonalClone(*me, TEMPSUMMON_NO_OWNER_OR_TIMED_DESPAWN, 120s, 0, 0, who->ToPlayer()))
            {
                clone->setActive(true);
                clone->SetOwnerGUID(who->GetGUID());
                if (auto ai = clone->AI())
                {
                    ai->Talk(0, who);
                    ai->DoAction(1);
                    ai->SetGUID(RecruitOne, 1);
                    ai->SetGUID(RecruitTwo, 2);
                }
            }
        }
    }

    TaskScheduler scheduler;
    EventMap events;
};

enum RecruitSpells
{
    Charge = 361176,
    MortalStrike = 303161,
    Stormbolt = 93814,
    BladeStorm = 222634,
    LayOnHands = 348503,
};

// 700052 - npc_horde_recruit_700052
struct npc_horde_recruit_700052 : public ScriptedAI
{
public:
    npc_horde_recruit_700052(Creature* creature) : ScriptedAI(creature) { }

    bool m_Dueling = false;
    ObjectGuid DuelGuid;
    ObjectGuid CaptainGuid;

    bool CanForceAttack(Unit const* who) const override
    {
        if (!me->IsSummon())
            return false;

        return m_Dueling && who->GetGUID() == DuelGuid;
    }

    void SetGUID(ObjectGuid const& guid, int32 actionId) override
    {
        if (actionId == 1)
        {
            DuelGuid = guid;
            m_Dueling = true;
            if (auto d = ObjectAccessor::GetCreature(*me, guid))
            {
                AttackStart(d);
                EngagementStart(d);
            }
        }
        else if (actionId == 2)
            CaptainGuid = guid;
    }

    void JustEngagedWith(Unit* who) override
    {
        events.Reset();

        DoCast(who, Charge);
        events.ScheduleEvent(1, 2s, 5s);
        events.ScheduleEvent(2, 2s, 5s);
        events.ScheduleEvent(3, 2s, 5s);
    }

    void UpdateAI(uint32 diff) override
    {
        scheduler.Update(diff);

        if (!UpdateVictim())
            return;

        events.Update(diff);

        if (me->HasUnitState(UNIT_STATE_CASTING) || me->HasUnitState(UNIT_STATE_STUNNED))
            return;

        if (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
                case 1:
                    DoCastVictim(MortalStrike);
                    events.Repeat(4s, 8s);
                    break;
                case 2:
                    DoCastVictim(Stormbolt);
                    events.Repeat(20s, 30s);
                    break;
                case 3:
                    DoCast(BladeStorm);
                    events.Repeat(60s);
                    break;
            }
        }
        DoMeleeAttackIfReady();
    }

    void DoAction(int32 actionId) override
    {
        if (actionId == 2)
        {
            me->RemoveAllAuras();
            m_Dueling = false;
            EnterEvadeMode(EVADE_REASON_OTHER);

            scheduler.Schedule(3s, [this](TaskContext context)
            {
                me->HandleEmoteCommand(Emote::EMOTE_ONESHOT_BOW);
            });

            me->DespawnOrUnsummon(4s);
        }
    }

    void DamageTaken(Unit* attacker, uint32& damage, DamageEffectType damageType, SpellInfo const* spell) override
    {
        if (damage >= me->GetHealth() || me->HealthBelowPctDamaged(2, damage))
        {
            damage = 0;
            if (m_Dueling)
            {
                DoAction(2);

                if (auto dueler = ObjectAccessor::GetCreature(*me, DuelGuid))
                    if (auto ai = dueler->AI())
                    {
                        ai->DoAction(2);
                        dueler->HandleEmoteCommand(Emote::EMOTE_ONESHOT_CHEER);
                    }

                Talk(0, me->GetOwner());
                me->SetStandState(UnitStandStateType::UNIT_STAND_STATE_KNEEL);

                scheduler.Schedule(2s, [this](TaskContext context)
                {
                    DoCastSelf(LayOnHands);
                    if (auto leader = ObjectAccessor::GetCreature(*me, CaptainGuid))
                        if (leader->AI())
                            leader->AI()->Talk(1, me->GetOwner());
                });
            }
        }
    }

    void EnterEvadeMode(EvadeReason why) override
    {
        if (!CreatureAI::_EnterEvadeMode(why))
            return;

        me->AddUnitState(UNIT_STATE_EVADE);
        me->GetMotionMaster()->MoveTargetedHomeForce();

        Reset();
    }

    TaskScheduler scheduler;
    EventMap events;
};
// 700053 - npc_alliance_recruit_700053
struct npc_alliance_recruit_700053 : public ScriptedAI
{
public:
    npc_alliance_recruit_700053(Creature* creature) : ScriptedAI(creature) { }

    bool m_Dueling = false;
    ObjectGuid DuelGuid;
    ObjectGuid CaptainGuid;

    bool CanForceAttack(Unit const* who) const override
    {
        if (!me->IsSummon())
            return false;

        return m_Dueling && who->GetGUID() == DuelGuid;
    }

    void SetGUID(ObjectGuid const& guid, int32 actionId) override
    {
        if (actionId == 1)
        {
            DuelGuid = guid;
            m_Dueling = true;
            if (auto d = ObjectAccessor::GetCreature(*me, guid))
            {
                AttackStart(d);
                EngagementStart(d);
            }
        }
        else if (actionId == 2)
            CaptainGuid = guid;
    }

    void JustEngagedWith(Unit* who) override
    {
        events.Reset();

        DoCast(who, Charge);
        events.ScheduleEvent(1, 2s, 5s);
        events.ScheduleEvent(2, 2s, 5s);
        events.ScheduleEvent(3, 2s, 5s);
    }

    void UpdateAI(uint32 diff) override
    {
        scheduler.Update(diff);

        if (!UpdateVictim())
            return;

        events.Update(diff);

        if (me->HasUnitState(UNIT_STATE_CASTING) || me->HasUnitState(UNIT_STATE_STUNNED))
            return;

        if (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
                case 1:
                    DoCastVictim(MortalStrike);
                    events.Repeat(4s, 8s);
                    break;
                case 2:
                    DoCastVictim(Stormbolt);
                    events.Repeat(20s, 30s);
                    break;
                case 3:
                    DoCast(BladeStorm);
                    events.Repeat(60s);
                    break;
            }
        }
        DoMeleeAttackIfReady();
    }

    void DoAction(int32 actionId) override
    {
        if (actionId == 2)
        {
            me->RemoveAllAuras();
            m_Dueling = false;
            EnterEvadeMode(EVADE_REASON_OTHER);

            scheduler.Schedule(3s, [this](TaskContext context)
            {
                me->HandleEmoteCommand(Emote::EMOTE_ONESHOT_BOW);
            });

            me->DespawnOrUnsummon(9s);
        }
    }

    void DamageTaken(Unit* attacker, uint32& damage, DamageEffectType damageType, SpellInfo const* spell) override
    {
        if (damage >= me->GetHealth() || me->HealthBelowPctDamaged(2, damage))
        {
            damage = 0;
            if (m_Dueling)
            {
                DoAction(2);

                if (auto dueler = ObjectAccessor::GetCreature(*me, DuelGuid))
                    if (auto ai = dueler->AI())
                    {
                        ai->DoAction(2);
                        dueler->HandleEmoteCommand(Emote::EMOTE_ONESHOT_CHEER);
                    }

                Talk(0, me->GetOwner());
                me->HandleEmoteCommand(Emote::EMOTE_ONESHOT_KNEEL);

                scheduler.Schedule(2s, [this](TaskContext context)
                {
                    if (auto leader = ObjectAccessor::GetCreature(*me, CaptainGuid))
                        if (leader->AI())
                            leader->AI()->Talk(2, me->GetOwner());
                    DoCastSelf(LayOnHands);
                });
            }
        }
    }

    void EnterEvadeMode(EvadeReason why) override
    {
        if (!CreatureAI::_EnterEvadeMode(why))
            return;

        me->AddUnitState(UNIT_STATE_EVADE);
        me->GetMotionMaster()->MoveTargetedHomeForce();

        Reset();
    }

    TaskScheduler scheduler;
    EventMap events;
};
// 700047 - npc_uvrel_forgefall_700047
struct npc_uvrel_forgefall_700047 : public ScriptedAI
{
public:
    npc_uvrel_forgefall_700047(Creature* creature) : ScriptedAI(creature) { }

    void UpdateAI(uint32 diff) override
    {
        scheduler.Update(diff);

        if (!UpdateVictim())
            return;

        events.Update(diff);

        if (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
            }
        }
        DoMeleeAttackIfReady();
    }

    void DoAction(int32 actionId) override
    {
        if (actionId == 1)
        {
            me->RemoveNpcFlag(NPCFlags::UNIT_NPC_FLAG_QUESTGIVER);
            scheduler.Schedule(2s, [this](TaskContext context)
            {
                Talk(1, me->GetOwner());
                me->SetFacingTo(3.671757f);
                me->HandleEmoteCommand(Emote::EMOTE_ONESHOT_POINT);
                scheduler.Schedule(3s, [this](TaskContext context)
                {
                    Talk(2, me->GetOwner());
                    me->DespawnOrUnsummon();
                });
            });
        }
        else if (actionId == 2)
        {
            me->RemoveNpcFlag(NPCFlags::UNIT_NPC_FLAG_QUESTGIVER);
            scheduler.Schedule(1s, [this](TaskContext context)
            {
                Talk(3, me->GetOwner());

                scheduler.Schedule(4s, [this](TaskContext context)
                {
                    me->GetMotionMaster()->MovePoint(1, { 1906.86f, 4634.61f, 335.897f, 0.199639f }, MOVE_PATHFINDING | MOVE_WALK_MODE, 0.199639f)->callbackFunc = [this]()
                    {
                        Talk(4, me->GetOwner());

                        scheduler.Schedule(3s, [this](TaskContext context)
                        {
                            if (auto player = me->GetCharmerOrOwnerPlayerOrPlayerItself())
                                player->KilledMonsterCredit(me->GetEntry(), me->GetGUID());

                            if (auto c = me->FindNearestCreature(700017, 50.0f))
                            {
                                if (auto ai = c->AI())
                                    ai->Talk(0, me->GetOwner());

                                auto ownerGuid = me->GetOwnerGUID();
                                c->GetScheduler().Schedule(2s, [c, ownerGuid](TaskContext context)
                                {
                                    if (auto ai = c->AI())
                                        ai->Talk(2, ObjectAccessor::GetUnit(*c, ownerGuid));
                                });
                            }

                            scheduler.Schedule(3s, [this](TaskContext context)
                            {
                                me->GetMotionMaster()->MovePoint(1, { 1895.14f, 4653.82f, 335.896f, 5.42581f }, MOVE_PATHFINDING | MOVE_WALK_MODE, 5.42851f)->callbackFunc = [this]()
                                {
                                    me->DespawnOrUnsummon();
                                };
                            });
                        });
                    };
                });
            });
        }
    }

    void OnQuestAccept(Player* player, Quest const* quest) override
    {
        if (quest->GetQuestId() == 700001)
        {
            StartQuestEvent(player);
        }
    }

    void StartQuestEvent(Player* player)
    {
        if (auto clone = me->SummonPersonalClone(*me, TEMPSUMMON_NO_OWNER_OR_TIMED_DESPAWN, 30s, 0, 0, player))
        {
            clone->SetOwnerGUID(player->GetGUID());
            if (auto ai = clone->AI())
            {
                ai->DoAction(2);
            }
        }
    }

    bool OnGossipHello(Player* player) override
    {
        ClearGossipMenuFor(player);
        player->PrepareQuestMenu(me->GetGUID());
        if (player->GetQuestStatus(700001) == QUEST_STATUS_INCOMPLETE && !me->IsSummon() && me->HasNpcFlag(NPCFlags::UNIT_NPC_FLAG_QUESTGIVER))
        {
            AddGossipItemFor(player, GossipOptionIcon::None, "I'm ready", 0, 0, [this, player](std::string /*callback*/)
            {
                CloseGossipMenuFor(player);
                StartQuestEvent(player);
            });
        }
        SendGossipMenuFor(player, me->GetEntry(), me);
        return true;
    }

    TaskScheduler scheduler;
    EventMap events;
};

// 700065 - npc_spawn_of_n_zoth_700065
struct npc_spawn_of_n_zoth_700065 : public ScriptedAI
{
public:
    npc_spawn_of_n_zoth_700065(Creature* creature) : ScriptedAI(creature) { }

    void InitializeAI() override
    {
    }

    void Reset() override
    {
    }

    void UpdateAI(uint32 diff) override
    {
        scheduler.Update(diff);

        if (!UpdateVictim())
            return;

        events.Update(diff);

        if (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
            }
        }
        DoMeleeAttackIfReady();
    }


    TaskScheduler scheduler;
    EventMap events;
};
// 700030 - npc_medivh_700030
struct npc_medivh_700030 : public ScriptedAI
{
public:
    npc_medivh_700030(Creature* creature) : ScriptedAI(creature) { }

    std::unordered_map<ObjectGuid::LowType, TimePoint> plrTexts;

    bool OnGossipHello(Player* player) override
    {
        ClearGossipMenuFor(player);

        if (player->GetQuestStatus(700006) == QUEST_STATUS_NONE)
        {
            SendGossipMenuFor(player, me->GetEntry(), me);
            return true;
        }

        if (player->GetQuestStatus(700006) == QUEST_STATUS_INCOMPLETE && !player->HasItemCount(700001))
            AddGossipItemFor(player, GossipOptionIcon::None, "I'll test the Magic Stone!", 0, 1);
        else if (player->GetQuestStatus(700006) == QUEST_STATUS_INCOMPLETE)
        {
            CloseGossipMenuFor(player);

            auto now = GameTime::Now();
            auto itr = plrTexts.find(player->GetGUID().GetCounter());
            bool allow = true;
            if (itr != plrTexts.end() && itr->second >= now)
                allow = false;

            if (allow)
            {
                plrTexts[player->GetGUID().GetCounter()] = now + 5s;
                Talk(1, player);
            }
            return true;
        }
        SendGossipMenuFor(player, 7000300, me);
        return true;
    }

    bool OnGossipSelect(Player* player, uint32 menuId, uint32 gossipId) override
    {
        player->AddItem(700001, 1);
        player->KilledMonsterCredit(700030, me->GetGUID());
        Talk(0, player);
        CloseGossipMenuFor(player);
        return true;
    }

    TaskScheduler scheduler;
    EventMap events;
};

struct questscript_incursion : public QuestAI
{
public:
    questscript_incursion(Quest const* quest, Player* player) : QuestAI(quest, player) { }

    void OnQuestAbandon() override
    {
        player->CastSpell(player, 313613, true); // Leave nyalotha
    }

    void OnQuestComplete() override
    {
        player->CastSpell(player, 313613, true); // Leave nyalotha
    }

    bool spawnedBoss = false;
    void OnQuestProgressUpdate(QuestObjectiveType /*objectiveType*/, int32 objectId, int64 /*addCount*/, ObjectGuid /*victimGuid*/, uint16 logSlot, QuestObjective const& questObjective) override
    {
        if (objectId == 700040 && player->GetMapId() == 1116)
        {
            auto counter = player->GetQuestSlotCounter(logSlot, questObjective.StorageIndex);
            if (counter >= 5)
            {
                spawnedBoss = true;
                if (auto spawn = player->SummonCreature(700065, { 1946.01f, 4652.43f, 335.893f, 3.45576f }, TEMPSUMMON_CORPSE_DESPAWN, 3s, 0, 0, player->GetGUID()))
                {
                    if (auto ai = spawn->AI())
                    {
                        ai->AttackStart(player);
                    }
                }
            }
        }
    }
};

struct go_golden_treasure_chest_218889 : public GameObjectAI
{
public:
    go_golden_treasure_chest_218889(GameObject* go) : GameObjectAI(go) { }

    bool OnReportUse(Player* player) override
    {
        if (auto bankSecurity = me->FindNearestCreature(700044, 15.0f))
        {
            bankSecurity->CastSpell(player, 360247, true);
            if (bankSecurity->AI())
                bankSecurity->AI()->Talk(0, player);
        }

        return false;
    }
};

// 800030
struct npc_keystone_master : public ScriptedAI
{
public:
    npc_keystone_master(Creature* creature) : ScriptedAI(creature) { }

    bool OnGossipHello(Player* player) override
    {
        auto status = player->GetQuestStatus(800030);

        ClearGossipMenuFor(player);
        player->PrepareQuestMenu(me->GetGUID());
        if (status == QUEST_STATUS_REWARDED || status == QUEST_STATUS_COMPLETE)
        {
            if (!player->HasItemCount(158923, 1, true))
                AddGossipItemFor(player, GossipOptionIcon::None, "I need a Keystone.", 0, 1);
            else
                AddGossipItemFor(player, GossipOptionIcon::None, "Can you drop my keystone?", 0, 5);
            if (!player->HasItemCount(180653, 1, true))
                AddGossipItemFor(player, GossipOptionIcon::None, "I need a Mini-Keystone", 0, 2);
            else
                AddGossipItemFor(player, GossipOptionIcon::None, "Can you drop my mini-keystone?", 0, 6);

            AddGossipItemFor(player, GossipOptionIcon::None, "Can you tell me about Keystones again?", 0, 3);
        }

        if (status == QUEST_STATUS_INCOMPLETE)
            AddGossipItemFor(player, GossipOptionIcon::None, "Can you tell me about Keystones?", 0, 3);
        SendGossipMenuFor(player, me->GetEntry(), me);
        return true;
    }

    bool OnGossipSelect(Player* player, uint32 menuId, uint32 gossipId) override
    {
        uint32 action = player->PlayerTalkClass->GetGossipOptionAction(gossipId);
        switch (action)
        {
            case 1:
                player->AddItem(158923, 1);
                break;
            case 2:
                player->AddItem(180653, 1);
                break;
            case 3:
                ClearGossipMenuFor(player);
                AddGossipItemFor(player, GossipOptionIcon::None, "Okay", 0, 4);
                SendGossipMenuFor(player, 8000031, me);
                player->KilledMonsterCredit(me->GetEntry(), me->GetGUID());
                return true;
            case 4:
                return OnGossipHello(player);
            case 5:
                if (auto item = player->GetItemByEntry(158923))
                {
                    auto keystoneInfo = player->GetPlayerChallenge()->GetKeystoneInfo(item);
                    if (keystoneInfo)
                    {
                        player->GetPlayerChallenge()->ResetMythicKeystoneTo(item, keystoneInfo->Level, false);
                        ChatHandler(player).PSendSysMessage("Keystone dropped to %u", keystoneInfo->Level);
                    }
                }
                return OnGossipHello(player);
            case 6:
                if (auto item = player->GetItemByEntry(180653))
                {
                    auto keystoneInfo = player->GetPlayerChallenge()->GetKeystoneInfo(item);
                    if (keystoneInfo)
                    {
                        player->GetPlayerChallenge()->ResetMythicKeystoneTo(item, keystoneInfo->Level, false);
                        ChatHandler(player).PSendSysMessage("Mini-keystone dropped to %u", keystoneInfo->Level);
                    }
                }
                return OnGossipHello(player);
        }
        CloseGossipMenuFor(player);
        return true;
    }
};
// 800032 - npc_garan_800032
struct npc_garan_800032 : public ScriptedAI
{
public:
    npc_garan_800032(Creature* creature) : ScriptedAI(creature) { }

    bool OnGossipHello(Player* player) override
    {
        player->PrepareQuestMenu(me->GetGUID());
        SendGossipMenuFor(player, 800032, me);
        return true;
    }
};
// 800007 - npc_innkeeper_bobkin_800007
struct npc_innkeeper_bobkin_800007 : public ScriptedAI
{
public:
    npc_innkeeper_bobkin_800007(Creature* creature) : ScriptedAI(creature) { }

    bool CanSeeOrDetect(WorldObject const* who) const override
    {
        if (who->IsPlayer() && !me->isAnySummons())
        {
            auto player = who->ToPlayer();
            if (player->GetQuestStatus(800032) == QUEST_STATUS_REWARDED || player->IsGameMaster())
                return true;
        }

        return false;
    }
};
// 800001 - npc_jon_bovi_800001
struct npc_jon_bovi_800001 : public ScriptedAI
{
public:
    npc_jon_bovi_800001(Creature* creature) : ScriptedAI(creature) { }

    bool CanSeeOrDetect(WorldObject const* who) const override
    {
        if (who->IsPlayer() && !me->isAnySummons())
        {
            auto player = who->ToPlayer();
            if (player->GetQuestStatus(800033) == QUEST_STATUS_REWARDED || player->IsGameMaster())
                return true;
        }

        return false;
    }
};
// 800044 - npc_nura_800044
struct npc_nura_800044 : public ScriptedAI
{
public:
    npc_nura_800044(Creature* creature) : ScriptedAI(creature) { }

    bool OnGossipHello(Player* player) override
    {
        ClearGossipMenuFor(player);
        player->PrepareQuestMenu(me->GetGUID());
        AddGossipItemFor(player, GossipOptionIcon::None, "Reset all Instances", 0, 0, [this, player](std::string /*callback*/)
        {
            uint32 mapId = 0;
            uint32 counter = 0;
            for (DifficultyEntry const* difficulty : sDifficultyStore)
            {
                auto binds = player->GetBoundInstances(Difficulty(difficulty->ID));
                if (binds != player->m_boundInstances.end())
                {
                    for (auto itr = binds->second.begin(); itr != binds->second.end();)
                    {
                        InstanceSave const* save = itr->second.save;
                        if (itr->first != player->GetMapId())
                        {
                            std::string timeleft = secsToTimeString(save->GetResetTime() - GameTime::GetGameTime(), TimeFormat::ShortText);
                            //handler->PSendSysMessage(LANG_COMMAND_INST_UNBIND_UNBINDING, itr->first, save->GetInstanceId(), itr->second.perm ? "yes" : "no", save->GetDifficultyID(), save->CanReset() ? "yes" : "no", timeleft.c_str());
                            player->UnbindInstance(itr, binds);
                            counter++;
                        }
                        else
                            ++itr;
                    }
                }
            }

            if (counter > 0)
            {
                Talk(0, player);
            }
            else
                Talk(1, player);
            CloseGossipMenuFor(player);
        });
        SendGossipMenuFor(player, me->GetEntry(), me);
        return true;
    }
};

// 800034 - npc_asculo_800034
struct npc_asculo_800034 : public ScriptedAI
{
public:
    npc_asculo_800034(Creature* creature) : ScriptedAI(creature) { }

    bool OnGossipHello(Player* player) override
    {
        ClearGossipMenuFor(player);
        player->PrepareQuestMenu(me->GetGUID());
        AddGossipItemFor(player, GossipOptionIcon::None, "Enter a code", 0, 0, "", 0, true, [this, player](std::string callback)
        {
            Talk(1, player);
            CloseGossipMenuFor(player);
        });
        SendGossipMenuFor(player, me->GetEntry(), me);
        return true;
    }
};

// 800209 - npc_druid_spiritualist_800209
struct npc_druid_spiritualist_800209 : public ScriptedAI
{
public:
    npc_druid_spiritualist_800209(Creature* creature) : ScriptedAI(creature) { }

    void UpdateAI(uint32 diff) override
    {
        if (me->GetCurrentSpell(CurrentSpellTypes::CURRENT_CHANNELED_SPELL))
            return;

        DoCastSelf(MallScript::SpellChannel);
    }
};
// 800059 - npc_thrall_800059
struct npc_thrall_800059 : public ScriptedAI
{
public:
    npc_thrall_800059(Creature* creature) : ScriptedAI(creature) { }

    bool OnGossipHello(Player* player) override
    {
        if (player->GetQuestStatus(700036) == QUEST_STATUS_COMPLETE)
        {
            player->PlayerTalkClass->SendQuestGiverOfferReward(sObjectMgr->GetQuestTemplate(700036), me->GetGUID(), true);
            return true;
        }

        ClearGossipMenuFor(player);
        player->PrepareQuestMenu(me->GetGUID());
        SendGossipMenuFor(player, me->GetEntry(), me);
        return true;
    }

    bool CanSeeOrDetect(WorldObject const* who) const override
    {
        if (who->IsPlayer())
        {
            auto player = who->ToPlayer();
            auto status = player->GetQuestStatus(700036); // 700036 finish the fight
            switch (status)
            {
                case QUEST_STATUS_COMPLETE:
                case QUEST_STATUS_REWARDED:
                    return true;
                default:
                    return false;
            }
        }

        return false;
    }
};
// 800053 - npc_scrappie_800053
struct npc_scrappie_800053 : public ScriptedAI
{
public:
    npc_scrappie_800053(Creature* creature) : ScriptedAI(creature) { }

    bool CanSeeOrDetect(WorldObject const* who) const override
    {
        if (who->IsPlayer() && !me->isAnySummons())
        {
            auto player = who->ToPlayer();
            if (player->IsGameMaster())
                return true;
            if (player->GetQuestStatus(800055) == QUEST_STATUS_REWARDED)
                return true;
        }

        return false;
    }
};
// 700016 - npc_pakgu_700016
struct npc_pakgu_700016 : public ScriptedAI
{
public:
    npc_pakgu_700016(Creature* creature) : ScriptedAI(creature) { }

    bool OnGossipHello(Player* player) override
    {
        ShowMainMenu(player, me);
        return true;
    }

    bool OnGossipSelect(Player* player, uint32 /*menuId*/, uint32 gossipId) override
    {
        uint32 pet_id = 0;
        uint32 action = player->PlayerTalkClass->GetGossipOptionAction(gossipId);
        player->PlayerTalkClass->ClearMenus();
        switch (action)
        {
            case 1215:
            {
                AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface\\icons\\Ability_Hunter_Pet_Chimera:25|t Chimera", GOSSIP_SENDER_MAIN, 1241);
                AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface\\icons\\Ability_Hunter_Pet_CoreHound:25|t Core Hound", GOSSIP_SENDER_MAIN, 1243);
                AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface\\icons\\Ability_Hunter_Pet_Devilsaur:25|t Devilsaur", GOSSIP_SENDER_MAIN, 1246);
                AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface\\icons\\Spell_shaman_astralshift:25|t Spirit Beast", GOSSIP_SENDER_MAIN, 1247);
                AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface\\icons\\Ability_Hunter_Pet_Rhino:25|t Rhino", GOSSIP_SENDER_MAIN, 1248);
                AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface\\icons\\Ability_Hunter_Pet_Worm:25|t Worm", GOSSIP_SENDER_MAIN, 1249);
                AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface\\icons\\Ability_Hunter_Pet_Silithid:25|t Silithid", GOSSIP_SENDER_MAIN, 1250);
                AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface\\icons\\inv_pet_waterstrider:25|t Water Strider", GOSSIP_SENDER_MAIN, 1251);
                AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface\\icons\\achievement_moguraid_01:25|t Quilen", GOSSIP_SENDER_MAIN, 1262);
                AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface\\icons\\ability_hunter_pet_rhino:25|t Clefthoof", GOSSIP_SENDER_MAIN, 1263);
                AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface\\icons\\inv_pet_waterstrider:25|t Water Strider", GOSSIP_SENDER_MAIN, 1264);
                AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface\\icons\\Ability_Hunter_Pet_Spider:25|t Shale Spider", GOSSIP_SENDER_MAIN, 1265);
                SendGossipMenuFor(player, 1, me);
                break;
            }
            case 1216:
            {
                AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface\\icons\\Ability_Hunter_Pet_Bat:25|t Bat", GOSSIP_SENDER_MAIN, 1217);
                AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface\\icons\\Ability_Hunter_Pet_Owl:25|t Owl", GOSSIP_SENDER_MAIN, 1218);
                // exotic       AddGossipItemFor(player,  9, "Chimera", GOSSIP_SENDER_MAIN, 1216);
                AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface\\icons\\Ability_Hunter_Pet_Dragonhawk:25|t Dragonhawk", GOSSIP_SENDER_MAIN, 1219);
                AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface\\icons\\Ability_Hunter_Pet_NetherRay:25|t Nether ray", GOSSIP_SENDER_MAIN, 1220);
                AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface\\icons\\Ability_Hunter_Pet_Ravager:25|t Ravager", GOSSIP_SENDER_MAIN, 1221);
                // exotic       AddGossipItemFor(player,  9, "Silitid", GOSSIP_SENDER_MAIN, 1216);
                AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface\\icons\\Ability_Hunter_Pet_Spider:25|t Spider", GOSSIP_SENDER_MAIN, 1223);
                AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface\\icons\\Ability_Hunter_Pet_Sporebat:25|t Sporebat", GOSSIP_SENDER_MAIN, 1242);
                AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface\\icons\\Ability_Hunter_Pet_WindSerpent:25|t Wind serpent", GOSSIP_SENDER_MAIN, 1225);
                AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface\\icons\\Ability_Hunter_Pet_Cat:25|t Cat", GOSSIP_SENDER_MAIN, 1227);
                // exotic       AddGossipItemFor(player,  9, "Core Hound", GOSSIP_SENDER_MAIN, 1216);
                AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface\\icons\\Ability_Hunter_Pet_Hyena:25|t Hyena", GOSSIP_SENDER_MAIN, 1228);
                // exotic       AddGossipItemFor(player,  11, "Moth", GOSSIP_SENDER_MAIN, 1229);
                AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface\\icons\\Ability_Hunter_Pet_Raptor:25|t Raptor", GOSSIP_SENDER_MAIN, 1229);
                AddGossipItemFor(player, GossipOptionIcon::None, "More pets?", GOSSIP_SENDER_MAIN, 1300);
                SendGossipMenuFor(player, 1, me);
                break;
            }
            case 1300:
            {
                AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface\\icons\\Ability_Hunter_Pet_TallStrider:25|t Tallstrider", GOSSIP_SENDER_MAIN, 1230);
                // AddGossipItemFor(player,  11, "Wasp", GOSSIP_SENDER_MAIN, 1231);
                AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface\\icons\\Ability_Hunter_Pet_Wolf:25|t Wolf", GOSSIP_SENDER_MAIN, 1232);
                AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface\\icons\\Ability_Hunter_Pet_Bear:25|t Bear", GOSSIP_SENDER_MAIN, 1233);
                AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface\\icons\\Ability_Hunter_Pet_Boar:25|t Boar", GOSSIP_SENDER_MAIN, 1234);
                AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface\\icons\\Ability_Hunter_Pet_Crab:25|t Crab", GOSSIP_SENDER_MAIN, 1235);
                AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface\\icons\\Ability_Hunter_Pet_Crocolisk:25|t Crocolisk", GOSSIP_SENDER_MAIN, 1236);
                AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface\\icons\\Ability_Hunter_Pet_Gorilla:25|t Gorilla", GOSSIP_SENDER_MAIN, 1237);
                AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface\\icons\\Ability_Hunter_Pet_Scorpid:25|t Scorpid", GOSSIP_SENDER_MAIN, 1238);
                AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface\\icons\\Ability_Hunter_Pet_Turtle:25|t Turtle", GOSSIP_SENDER_MAIN, 1239);
                AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface\\icons\\Ability_Hunter_Pet_WarpStalker:25|t Warp stalker", GOSSIP_SENDER_MAIN, 1240);
                AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface\\icons\\Ability_Hunter_Pet_Moth:25|t Moth", GOSSIP_SENDER_MAIN, 1244);
                AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface\\icons\\Ability_Hunter_Pet_Wasp:25|t Wasp", GOSSIP_SENDER_MAIN, 1251);
                AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface\\icons\\Spell_Nature_GuardianWard:25|t Serpent", GOSSIP_SENDER_MAIN, 1252);
                AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface\\icons\\Ability_Hunter_Pet_Worm:25|t Snowdrift Jormungar", GOSSIP_SENDER_MAIN, 1253);
                AddGossipItemFor(player, GossipOptionIcon::None, "More pets?", GOSSIP_SENDER_MAIN, 1301);
                AddGossipItemFor(player, GossipOptionIcon::None, "Back", GOSSIP_SENDER_MAIN, 1216);
                SendGossipMenuFor(player, 1, me);
                break;
            }
            case 1301:
            {
                AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface\\icons\\inv_pet_direhorn:25|t Direhorn", GOSSIP_SENDER_MAIN, 1254);
                AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface\\icons\\ability_mount_goatmountwhite:25|t Goat", GOSSIP_SENDER_MAIN, 1255);
                AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface\\icons\\inv_pet_porcupine:25|t Porcupine", GOSSIP_SENDER_MAIN, 1256);
                AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface\\icons\\Ability_Hunter_Pet_Crocolisk:25|t Gorgonite", GOSSIP_SENDER_MAIN, 1257);
                AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface\\icons\\inv_misc_ahnqirajtrinket_01:25|t Beetle", GOSSIP_SENDER_MAIN, 1258);
                AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface\\icons\\inv_pet_monkey:25|t Monkey", GOSSIP_SENDER_MAIN, 1259);
                AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface\\icons\\ability_hunter_aspectofthefox:25|t Fox", GOSSIP_SENDER_MAIN, 1260);
                AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface\\icons\\inv_pet_mastiff:25|t Dog", GOSSIP_SENDER_MAIN, 1261);
                AddGossipItemFor(player, GossipOptionIcon::None, "Back", GOSSIP_SENDER_MAIN, 1300);
                SendGossipMenuFor(player, 1, me);
                break;
            }
            case 1217:
            {
                pet_id = 8601;
                break; //bat
            }
            case 1218:
            {
                pet_id = 1995;
                break; //owl
            }
            case 1219:
            {
                pet_id = 20502;
                break; //dragonhawk
            }
            case 1220:
            {
                pet_id = 21901;
                break; //nether ray
            }
            case 1221:
            {
                pet_id = 23326;
                break; //ravager
            }
            case 1223:
            {
                pet_id = 11921;
                break; //spider
            }
            case 1242:
            {
                pet_id = 18129;
                break; //sporebat
            }
            case 1225:
            {
                pet_id = 26806;
                break; //Wind serpent
            }
            case 1227:
            {
                pet_id = 24530;
                break; //cat
            }
            case 1228:
            {
                pet_id = 5426;
                break;    //hyena
            }
            case 1229:
            {
                pet_id = 20728;
                break; //raptor
            }
            case 1230:
            {
                pet_id = 3244;
                break; //tallstrider
            }
            case 1232:
            {
                pet_id = 2753;
                break; //wolf
            }
            case 1233:
            {
                pet_id = 8956;
                break; //bear
            }
            case 1234:
            {
                pet_id = 4511;
                break; //boar
            }
            case 1235:
            {
                pet_id = 17217;
                break; //crab
            }
            case 1236:
            {
                pet_id = 24047;
                break; //crocolisk
            }
            case 1237:
            {
                pet_id = 51661;
                break; //Gorilla
            }
            case 1238:
            {
                pet_id = 3126;
                break; //scorpid
            }
            case 1239:
            {
                pet_id = 4824;
                break; //turtle
            }
            case 1240:
            {
                pet_id = 23219;
                break; //warp stalker
            }
            case 1243:
            {
                const uint32 pets[3] = { 21102, 11672, 17447 };
                pet_id = pets[urand(0, 2)];
                break; // core hound
            }
            case 1246:
            {
                const uint32 pets[4] = { 20931, 32485, 6584, 6498 };
                pet_id = pets[urand(0, 3)];
                break; // Devilsaur
            }
            case 1247:
            {
                const uint32 pets[4] = { 38453,35189,33776,32517 };
                pet_id = pets[urand(0, 3)];
                break; // Spirit beast
            }
            case 1244:
            {
                const uint32 pets[2] = { 17350, 18468 };
                pet_id = pets[urand(0, 1)];
                break; // Moth
            }
            case 1248:
            {
                const uint32 pets[3] = { 25489, 30447, 28009 };
                pet_id = pets[urand(0, 2)];
                break; // Rhino
            }
            case 1249:
            {
                const uint32 pets[3] = { 30422, 11320, 11740 };
                pet_id = pets[urand(0, 2)];
                break; //Worm
            }
            case 1250:
            {
                const uint32 pets[3] = { 8205, 6582, 4132 };
                pet_id = pets[urand(0, 2)];
                break; //Silithid
            }
            case 1241:
            {
                const uint32 pets[4] = { 12800, 11497, 21879, 20932 };
                pet_id = pets[urand(0, 3)];
                break; //Chimera
            }
            case 1251:
            {
                const uint32 pets[3] = { 28086, 28085, 18283 };
                pet_id = pets[urand(0, 2)];
                break; //Wasp
            }
            case 1252:
            {
                pet_id = 28358;
                break; //Serpent
            }
            case 1253:
            {
                // Snowdrift Jormungar 
                pet_id = 29390;
                break;
            }
            case 1254:
            {
                // Primal Direhorn Hatchling
                pet_id = 70012;
                break;
            }
            case 1255:
            {
                // Battle Goat
                pet_id = 60010;
                break;
            }
            case 1256:
            {
                // Smoky Porcupine
                pet_id = 59772;
                break;
            }
            case 1257:
            {
                // Gorgonite
                pet_id = 43339;
                break;
            }
            case 1258:
            {
                // Whitefisher Crane
                pet_id = 56752;
                break;
            }
            case 1259:
            {
                // Blistering Scarab
                pet_id = 40310;
                break;
            }
            case 1260:
            {
                // Sly Fox
                pet_id = 58548;
                break;
            }
            case 1261:
            {
                // Bullmastiff
                pet_id = 44476;
                break;
            }
            case 1262:
            {
                // Primal Direhorn Hatchling
                pet_id = 700012;
                break;
            }
            case 1263:
            {
                // Wooly Rhino Bull
                pet_id = 25489;
                break;
            }
            case 1264:
            {
                // Hexapos
                pet_id = 50960;
                break;
            }
            case 1265:
            {
                // Elementium Spinner
                pet_id = 46580;
                break;
            }
            default:break;
        }
        if (pet_id)
        {
            CloseGossipMenuFor(player);
            player->UnsummonPetTemporaryIfAny();
            if (!player->GetPet())
            {
                Creature* tempPet = me->SummonCreature(pet_id, *me, TempSummonType::TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 10s, 0, 0, player->GetGUID());
                if (!tempPet)
                    return false;

                uint8 level = player->GetLevel();

                if (tempPet)
                    tempPet->SetLevel(level);

                Pet* pet = player->CreateTamedPetFrom(tempPet, 13481);
                if (!pet)                                               // in very specific state like near world end/etc.
                {
                    // "kill" original creature
                    if (tempPet)
                        tempPet->DespawnOrUnsummon();
                    return false;
                }

                // "kill" original creature
                if (tempPet)
                    tempPet->DespawnOrUnsummon();

                // prepare visual effect for levelup
                pet->SetLevel(level - 1);

                // add to world
                pet->GetMap()->AddToMap(pet->ToCreature());

                // visual effect for levelup
                pet->SetLevel(level);

                // caster have pet now
                player->SetMinion(pet, true);

                pet->SavePetToDB(PetSaveMode::PET_SAVE_FIRST_ACTIVE_SLOT);
                player->PetSpellInitialize();
                player->GetSession()->SendStablePet(ObjectGuid::Empty);
            }
        }
        return true;
    }


    void ShowMainMenu(Player* player, Creature* creature)
    {
        ClearGossipMenuFor(player);
        if (player->GetClass() == CLASS_HUNTER)
        {
            PetStable& petStable = player->GetOrInitPetStable();
            auto freeActiveSlotItr = std::find_if(petStable.ActivePets.begin(), petStable.ActivePets.end(), [](Optional<PetStable::PetInfo> const& petInfo)
            {
                return !petInfo.has_value();
            });

            if (freeActiveSlotItr == petStable.ActivePets.end())
            {
                Talk(0, player);
                return;
            }

            AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface\\icons\\Ability_Hunter_BeastSoothe:25|t [Pets] ->", GOSSIP_SENDER_MAIN, 1216);
            if (player->GetSpecializationId() == TALENT_SPEC_HUNTER_BEASTMASTER)
                AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface\\icons\\Ability_Hunter_BeastMastery:25|t [Exotic pets] ->", GOSSIP_SENDER_MAIN, 1215);
            SendGossipMenuFor(player, 700016, me);
            return;
        }
        SendGossipMenuFor(player, 7000160, me);
    }
};

// 800039 - npc_viltro_800039
struct npc_viltro_800039 : public ScriptedAI
{
public:
    npc_viltro_800039(Creature* creature) : ScriptedAI(creature) { }

    bool OnGossipHello(Player* player) override
    {
        ClearGossipMenuFor(player);
        player->PrepareQuestMenu(me->GetGUID());
        SendGossipMenuFor(player, me->GetEntry(), me);
        return true;
    }
};

// 800033 - npc_iron_richard_800033
struct npc_iron_richard_800033 : public ScriptedAI
{
public:
    npc_iron_richard_800033(Creature* creature) : ScriptedAI(creature) { }

    bool OnGossipHello(Player* player) override
    {
        ClearGossipMenuFor(player);
        player->PrepareQuestMenu(me->GetGUID());
        SendGossipMenuFor(player, me->GetEntry(), me);
        return true;
    }
};

// 800037 - npc_velalus_800037
struct npc_velalus_800037 : public ScriptedAI
{
public:
    npc_velalus_800037(Creature* creature) : ScriptedAI(creature) { }

    bool OnGossipHello(Player* player) override
    {
        ClearGossipMenuFor(player);
        player->PrepareQuestMenu(me->GetGUID());
        SendGossipMenuFor(player, me->GetEntry(), me);
        return true;
    }
};

// 800047 - npc_galirt_goldcheek_800047
struct npc_galirt_goldcheek_800047 : public ScriptedAI
{
public:
    npc_galirt_goldcheek_800047(Creature* creature) : ScriptedAI(creature) { }

    bool OnGossipHello(Player* player) override
    {
        ClearGossipMenuFor(player);
        player->PrepareQuestMenu(me->GetGUID());
        SendGossipMenuFor(player, me->GetEntry(), me);
        return true;
    }
};

// 800042 - npc_damion_800042
struct npc_damion_800042 : public ScriptedAI
{
public:
    npc_damion_800042(Creature* creature) : ScriptedAI(creature) { }

    bool OnGossipHello(Player* player) override
    {
        ClearGossipMenuFor(player);
        player->PrepareQuestMenu(me->GetGUID());
        SendGossipMenuFor(player, me->GetEntry(), me);
        return true;
    }
};

// Move to UTIL
std::string FirstWord(const std::string& line)
{
    return line.substr(0, line.find(' '));
}

struct npc_transmog_vendor_generic : public ScriptedAI
{
public:
    npc_transmog_vendor_generic(Creature* creature) : ScriptedAI(creature) { }

    bool OnGossipHello(Player* player) override
    {
        ClearGossipMenuFor(player);

        std::ostringstream ss;
        std::ostringstream costSS;

        auto range = sCustomObjectMgr->_customTransmogVendorData.equal_range(me->GetEntry());

        for (auto itr = range.first; itr != range.second; ++itr)
        {
            auto transmogSet = sTransmogSetStore.LookupEntry(itr->second.TransmogSet);
            if (!transmogSet)
                continue;

            if ((itr->second.ClassMask & player->GetClassMask()) == 0)
                continue;

            if (itr->second.Flags & 0x8) /// Horde only
                if (player->GetTeamId() != TeamId::TEAM_HORDE)
                    continue;
            if (itr->second.Flags & 0x4) /// Ally only
                if (player->GetTeamId() != TeamId::TEAM_ALLIANCE)
                    continue;

            if (itr->second.Flags & 0x1)// Disabled
                continue;

            if (transmogSet->PlayerConditionID && !player->MeetPlayerCondition(transmogSet->PlayerConditionID))
                continue;

            auto str = transmogSet->Name.Str[0]; // FirstWord(transmogSet->Name.Str[0]);

            if (std::string(str).empty())
                continue;

            ss.clear();
            ss.str("");
            costSS.clear();
            costSS.str("");

            if (player->GetSession()->GetCollectionMgr()->IsSetCompleted(transmogSet->ID))
                ss << "|cff0083FF|T" << itr->second.Icon << ":20:20:-28:0|t" << str << " ";
            else
                ss << "|cffFF0000|T" << itr->second.Icon << ":20:20:-28:0|t" << str << " ";

            if (transmogSet->ItemNameDescriptionID)
            {
                ss << "(";
                if (auto itemNameDesc = sItemNameDescriptionStore.LookupEntry(transmogSet->ItemNameDescriptionID))
                    ss << itemNameDesc->Description.Str[0];
                ss << ")";
            }

            int32 tokenCost = static_cast<int32>(itr->second.TransmogTokenCost);
            costSS << "This will cost " << tokenCost << " Transmog Tokens";

            AddGossipItemFor(player, GossipOptionIcon::None, ss.str(), 0, 0, costSS.str(), 0, false, [this, player, transmogSet, tokenCost](std::string /*callback*/)
            {
                if (!player->GetSession()->GetCollectionMgr()->IsSetCompleted(transmogSet->ID))
                {
                    if (player->GetCurrency(TransmogToken) >= tokenCost)
                    {
                        player->ModifyCurrency(TransmogToken, -tokenCost);
                        player->GetSession()->GetCollectionMgr()->AddTransmogSet(transmogSet->ID);
                    }
                    else
                        ChatHandler(player).PSendSysMessage("|cffFF0000Not enough transmog tokens!");

                }
                OnGossipHello(player);
            });
        }

        SendGossipMenuFor(player, me->GetEntry(), me);
        return true;
    }
};

// 180509 - npc_runecarver_180509
struct npc_runecarver_180509 : public ScriptedAI
{
public:
    npc_runecarver_180509(Creature* creature) : ScriptedAI(creature) { }

    void InitializeAI() override
    {
        me->SetNpcFlag2(UNIT_NPC_FLAG_2_RUNECARVER);
        me->SetUnitFlag2(UNIT_FLAG2_CANNOT_TURN | UNIT_FLAG2_REGENERATE_POWER);
    }

    bool OnGossipHello(Player* player) override
    {
        ClearGossipMenuFor(player);

        /// PIGPIGPIG
        auto status = player->GetQuestStatus(60272);
        if (status == QUEST_STATUS_INCOMPLETE)
        {
            player->CompleteQuest(60272);
            player->RewardQuest(sObjectMgr->GetQuestTemplate(60272), LootItemType::Item, 0, me, true);
        }
        else if (status == QUEST_STATUS_NONE)
        {
            player->AddQuest(sObjectMgr->GetQuestTemplate(60272), me);
            player->CompleteQuest(60272);
            player->RewardQuest(sObjectMgr->GetQuestTemplate(60272), LootItemType::Item, 0, me, true);
        }
        else if (status == QUEST_STATUS_COMPLETE)
        {
            player->RewardQuest(sObjectMgr->GetQuestTemplate(60272), LootItemType::Item, 0, me, true);
        }

        static const uint32 legendaries[] = { 500, 501, 502, 503, 504, 505, 506 };

        for (uint32 legendary : legendaries)
            if (!player->GetSession()->GetCollectionMgr()->HasRuneforgeMemory(legendary))
                player->GetSession()->GetCollectionMgr()->AddRuneforgeMemory(legendary);

        AddGossipItemFor(player, GossipOptionIcon::None, "I'd like to craft a legendary item.", 0, 0, [this, player](std::string callback)
        {
            /// MOVE TO WORLDPACKETS CLASS
            WorldPacket data(SMSG_RUNEFORGE_LEGENDARY_CRAFTING_OPEN_NPC, 17);
            data << me->GetGUID();
            data.WriteBit(0);
            data.FlushBits();
            player->GetSession()->SendPacket(&data);
        });
        AddGossipItemFor(player, GossipOptionIcon::None, "I'd like to upgrade my legendary item.", 0, 0, [this, player](std::string callback)
        {
            WorldPacket data(SMSG_RUNEFORGE_LEGENDARY_CRAFTING_OPEN_NPC, 17);
            data << me->GetGUID();
            data.WriteBit(1);
            data.FlushBits();
            player->GetSession()->SendPacket(&data);
        });

        SendGossipMenuFor(player, 40538, me);
        return true;
    }
};

// 800065 - npc_runecarver_s_portal_800065
struct npc_runecarver_s_portal_800065 : public ScriptedAI
{
public:
    npc_runecarver_s_portal_800065(Creature* creature) : ScriptedAI(creature) { }

    void InitializeAI() override
    {
        //me->SetUnitFlag(UNIT_FLAG_UNINTERACTIBLE);
    }

    void OnSpellClick(Unit* clicker, bool spellClickHandled) override
    {
        clicker->GetScheduler().CancelGroup(800065);
        clicker->GetScheduler().Schedule(1s, 800065, [](TaskContext context)
        {
            auto player = GetContextPlayer();

            if (player->GetMapId() == 1116)
                player->TeleportTo(2453, 2737.32f, 2099.82f, 320.26f, 3.14028f);
            else
                player->TeleportTo(1116, 85.9699f, -2753.94f, 62.5325f, 3.93367f);
        });
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
    RegisterCreatureAI(npc_juno_700006);
    RegisterCreatureAI(npc_mall_weapongiver);
    RegisterCreatureAI(npc_morpher_admin);
    RegisterCreatureAI(npc_kazzik_t3_transmogs);
    RegisterCreatureAI(npc_sturzah_800005);
    RegisterCreatureAI(npc_covenant_swapper);
    RegisterCreatureAI(npc_soulshape_picker);
    RegisterCreatureAI(npc_general_700000);
    RegisterCreatureAI(npc_combat_testing_shaman);
    RegisterCreatureAI(npc_sensei_700043);
    RegisterCreatureAI(npc_recruit_700041);
    RegisterCreatureAI(npc_blacksmith_apprentice_700032);
    RegisterCreatureAI(npc_blacksmith_apprentice_700035);
    RegisterCreatureAI(npc_dummy_700060);
    RegisterCreatureAI(npc_dummy_700056);
    RegisterCreatureAI(npc_dummy_700059);
    RegisterCreatureAI(npc_dummy_700057);
    RegisterCreatureAI(npc_general_yelnats_700058);
    RegisterCreatureAI(npc_pandaren_scribe_700039);
    RegisterCreatureAI(npc_bank_security_700044);
    RegisterCreatureAI(npc_captain_myra_700063);
    RegisterCreatureAI(npc_scout_700062);
    RegisterCreatureAI(npc_scout_700061);
    RegisterCreatureAI(npc_galara_longcloud_700051);
    RegisterCreatureAI(npc_jinjin_700050);
    RegisterCreatureAI(npc_gordo_remsay_700045);
    RegisterCreatureAI(npc_hye_gyo_giftview_700048);
    RegisterCreatureAI(npc_captain_flametalon_700054);
    RegisterCreatureAI(npc_horde_recruit_700052);
    RegisterCreatureAI(npc_alliance_recruit_700053);
    RegisterCreatureAI(npc_uvrel_forgefall_700047);
    RegisterCreatureAI(npc_spawn_of_n_zoth_700065);
    RegisterCreatureAI(npc_medivh_700030);
    RegisterCreatureAI(npc_keystone_master);
    RegisterCreatureAI(npc_garan_800032);
    RegisterCreatureAI(npc_innkeeper_bobkin_800007);    
    RegisterCreatureAI(npc_jon_bovi_800001);
    RegisterCreatureAI(npc_nura_800044);
    RegisterCreatureAI(npc_asculo_800034);
    RegisterCreatureAI(npc_druid_spiritualist_800209);
    RegisterCreatureAI(npc_thrall_800059);
    RegisterCreatureAI(npc_scrappie_800053);
    RegisterCreatureAI(npc_pakgu_700016);
    RegisterCreatureAI(npc_viltro_800039);
    RegisterCreatureAI(npc_iron_richard_800033);
    RegisterCreatureAI(npc_velalus_800037);
    RegisterCreatureAI(npc_galirt_goldcheek_800047);
    RegisterCreatureAI(npc_damion_800042);
    RegisterCreatureAI(npc_transmog_vendor_generic);
    RegisterCreatureAI(npc_spirit_healer);
    RegisterCreatureAI(npc_runecarver_180509);
    RegisterCreatureAI(npc_runecarver_s_portal_800065);

    RegisterSpellScript(spell_activating_313352);
   // RegisterSpellScript(spell_nyalotha_incursion);
    RegisterSpellScript(spell_leave_nyalotha);
    RegisterSpellAndAuraScriptPair(spell_fade_to_black_365581, spell_fade_to_black_365581_spellscript);

    RegisterQuestAI(questscript_incursion);
    RegisterGameObjectAI(go_golden_treasure_chest_218889);
}
