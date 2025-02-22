#include "GossipDef.h"
#include "ScriptMgr.h"
#include "ScriptedGossip.h"
#include "Chat.h"
#include "Item.h"
#include "WorldSession.h"
#include "SpellPackets.h"
#include "Spell.h"
#include "Conversation.h"
#include "DatabaseEnv.h"

struct CorruptionCostRefund
{
    std::string Icon;
    std::string Name;
    uint32 CurrencyID;
    uint32 RefundAmount;
};

enum eCorruptions : uint32
{
    Verastile1      = 6477,
    Masterful1      = 6471,
    Expedient1      = 6474,
    Severe1         = 6480,
    Avoidant1       = 6483,
    Siphoner1       = 6493,
    IneffableTruth1 = 6547,
    Versatile2      = 6478,
    Masterful2      = 6472,
    Expedient2      = 6475,
    Severe2         = 6481,
    Avoidant2       = 6484,
    Siphoner2       = 6494,
    IneffableTruth2 = 6548,
    Versatile3      = 6479,
    Masterful3      = 6473,
    Expedient3      = 6476,
    Severe3         = 6482,
    Avoidant3       = 6485,
    Siphoner3       = 6495,
    IneffableTruth3 = 6549,
    Empowerment1    = 1522,
    Empowerment2    = 1523,
    Empowerment3    = 1524,
};

const std::unordered_map<uint32, CorruptionCostRefund> CorruptionCostsRefunds =
{
    { Verastile1      , { "spell_arcane_arcanetactics",       "Versatile I",          10170, 50 } },
    { Masterful1      , { "ability_rogue_sinistercalling",    "Masterful I",          10170, 50 } },
    { Expedient1      , { "ability_mage_netherwindpresence",  "Expedient I",          10170, 50 } },
    { Severe1         , { "ability_priest_shadowyapparition", "Severe I",             10170, 50 } },
    { Avoidant1       , { "spell_warlock_demonsoul",          "Avoidant I",           10170, 50 } },
    { Siphoner1       , { "spell_shadow_lifedrain02_purple",  "Siphoner I",           10170, 50 } },
    { IneffableTruth1 , { "inv_wand_1h_nzothraid_d_01",       "Ineffable Truth I",    10170, 50 } },
    { Versatile2      , { "spell_arcane_arcanetactics",       "Versatile II",         10174, 50 } },
    { Masterful2      , { "ability_rogue_sinistercalling",    "Masterful II",         10174, 50 } },
    { Expedient2      , { "ability_mage_netherwindpresence",  "Expedient II",         10174, 50 } },
    { Severe2         , { "ability_priest_shadowyapparition", "Severe II",            10174, 50 } },
    { Avoidant2       , { "spell_warlock_demonsoul",          "Avoidant II",          10174, 50 } },
    { Siphoner2       , { "spell_shadow_lifedrain02_purple",  "Siphoner II",          10174, 50 } },
    { IneffableTruth2 , { "inv_wand_1h_nzothraid_d_01",       "Ineffable Truth II",   10174, 50 } },
    { Versatile3      , { "spell_arcane_arcanetactics",       "Versatile III",        10175, 50 } },
    { Masterful3      , { "ability_rogue_sinistercalling",    "Masterful III",        10175, 50 } },
    { Expedient3      , { "ability_mage_netherwindpresence",  "Expedient III",        10175, 50 } },
    { Severe3         , { "ability_priest_shadowyapparition", "Severe III",           10175, 50 } },
    { Avoidant3       , { "spell_warlock_demonsoul",          "Avoidant III",         10175, 50 } },
    { Siphoner3       , { "spell_shadow_lifedrain02_purple",  "Siphoner III",         10175, 50 } },
    { IneffableTruth3 , { "inv_wand_1h_nzothraid_d_01",       "Ineffable Truth III",  10175, 50 } },
    { Empowerment1    , { "spell_arcane_arcanetactics",       "Empowerment I",        10170, 50 } },
    { Empowerment2    , { "spell_arcane_arcanetactics",       "Empowerment II",       10174, 50 } },
    { Empowerment3    , { "spell_arcane_arcanetactics",       "Empowerment III",      10175, 50 } },
};

const std::unordered_map<uint32, std::pair<uint32, uint32>> CorruptionsBlacklistMap
{
    { Verastile1      , { Versatile2      , Versatile3       } }, ///< T1
    { Masterful1      , { Masterful2      , Masterful3       } }, ///< T1
    { Expedient1      , { Expedient2      , Expedient3       } }, ///< T1
    { Severe1         , { Severe2         , Severe3          } }, ///< T1
    { Avoidant1       , { Avoidant2       , Avoidant3        } }, ///< T1
    { Siphoner1       , { Siphoner2       , Siphoner3        } }, ///< T1
    { IneffableTruth1 , { IneffableTruth2 , IneffableTruth3  } }, ///< T1

    { Versatile2      , { Versatile3      , 0 } }, ///< T2
    { Masterful2      , { Masterful3      , 0 } }, ///< T2
    { Expedient2      , { Expedient3      , 0 } }, ///< T2
    { Severe2         , { Severe3         , 0 } }, ///< T2
    { Avoidant2       , { Avoidant3       , 0 } }, ///< T2
    { Siphoner2       , { Siphoner3       , 0 } }, ///< T2
    { IneffableTruth2 , { IneffableTruth3 , 0 } }, ///< T2
};

const std::unordered_map<uint32, std::pair<uint32, uint32>> CorruptionsReplaceMap
{
    { Versatile3      , { Versatile2      , Verastile1       } }, ///< T3
    { Masterful3      , { Masterful2      , Masterful1       } }, ///< T3
    { Expedient3      , { Expedient2      , Expedient1       } }, ///< T3
    { Severe3         , { Severe2         , Severe1          } }, ///< T3
    { Avoidant3       , { Avoidant2       , Avoidant1        } }, ///< T3
    { Siphoner3       , { Siphoner2       , Siphoner1        } }, ///< T3
    { IneffableTruth3 , { IneffableTruth2 , IneffableTruth1  } }, ///< T3

    { Versatile2     , { Verastile1      , 0 } }, ///< T2
    { Masterful2     , { Masterful1      , 0 } }, ///< T2
    { Expedient2     , { Expedient1      , 0 } }, ///< T2
    { Severe2        , { Severe1         , 0 } }, ///< T2
    { Avoidant2      , { Avoidant1       , 0 } }, ///< T2
    { Siphoner2      , { Siphoner1       , 0 } }, ///< T2
    { IneffableTruth2, { IneffableTruth1 , 0 } }, ///< T2
};

const std::set<uint32> CorruptionSet
{
    Verastile1,
    Masterful1,
    Expedient1,
    Severe1,
    Avoidant1,
    Siphoner1,
    IneffableTruth1,
    Versatile2,
    Masterful2,
    Expedient2,
    Severe2,
    Avoidant2,
    Siphoner2,
    IneffableTruth2,
    Versatile3,
    Masterful3,
    Expedient3,
    Severe3,
    Avoidant3,
    Siphoner3,
    IneffableTruth3,
};

template<uint32 BonusIDAward>
class item_enhancement_system : public ItemScript
{
    public:
        item_enhancement_system(char const* ScriptName) : ItemScript(ScriptName) { }

        std::unordered_map<ObjectGuid::LowType, ObjectGuid> m_ItemTargets;

        bool OnUse(Player* player, Item* upgrader, SpellCastTargets const& targets, ObjectGuid /*castId*/) override
        {
            if (!targets.GetItemTarget())
                return true;

            auto item = targets.GetItemTarget();

            if (!item)
                return true;

            if (item->GetScriptId() == upgrader->GetScriptId() || item == upgrader)
            {
                ChatHandler(player).SendSysMessage("|cffFF0000You can't enhance that item.");
                return true;
            }

            auto it = CorruptionsBlacklistMap.find(BonusIDAward);
            if (it != CorruptionsBlacklistMap.end())
            {
                auto it2 = it->second;

                if ((it2.first && item->HasBonusId(it2.first)) || (it2.second && item->HasBonusId(it2.second)))
                {
                    ChatHandler(player).PSendSysMessage("|cffFF0000You already have a more powerful corruption on %s.", Item::GetItemLink(item, player).c_str());
                    return true;
                }
            }

            // Allowing everything to be enhanced.
            if (item->HasBonusId(BonusIDAward))
            {
                ChatHandler(player).PSendSysMessage("|cffFF0000You can't enhance that item with %s anymore.", Item::GetItemLink(upgrader, player).c_str());
                return true;
            }

            if (CorruptionSet.count(BonusIDAward))
            {
                for (auto bonusId : CorruptionSet)
                {
                    if (item->HasBonusId(bonusId))
                    {
                        ChatHandler(player).PSendSysMessage("|cffFF0000%s is already corrupted with unique corruptions.", Item::GetItemLink(upgrader, player).c_str());
                        return true;
                    }
                }
            }

            if (!item->IsEquipped())
            {
                ChatHandler(player).PSendSysMessage("|cffFF0000%s must be equipped in order to add this corruption.", Item::GetItemLink(item, player).c_str());
                return true;
            }

            std::ostringstream ss;

            ss << "Are you sure you want to enhance " << Item::GetItemLink(item->GetEntry()) << " with " << Item::GetItemLink(upgrader, player) << "?\n\n|cffFF0000This will consume this enhancement permanently!";

            auto itr2 = CorruptionsReplaceMap.find(BonusIDAward);
            if (itr2 != CorruptionsReplaceMap.end())
            {
                bool has1 = item->HasBonusId(itr2->second.first);
                bool has2 = item->HasBonusId(itr2->second.second);

                if (has1 || has2)
                    ss << "\n\n|cffFF0000Previous levels of corruptions will be replaced!|R";

                if (has1)
                {
                    auto it3 = CorruptionCostsRefunds.find(itr2->second.first);
                    if (it3 != CorruptionCostsRefunds.end())
                    {
                        if (auto currency = sCurrencyTypesStore.LookupEntry(it3->second.CurrencyID))
                            ss << "\n\n|cff62CBF5You will recieve |cff8B00FF[" << currency->Name.Str[0] << "]|r |cff62CBF5x" << it3->second.RefundAmount << " as compensation";
                    }
                }

                if (has2)
                {
                    auto it4 = CorruptionCostsRefunds.find(itr2->second.second);
                    if (it4 != CorruptionCostsRefunds.end())
                    {
                        if (auto currency = sCurrencyTypesStore.LookupEntry(it4->second.CurrencyID))
                            ss << "\n\n|cff62CBF5You will recieve |cff8B00FF[" << currency->Name.Str[0] << "]|r |cff62CBF5x" << it4->second.RefundAmount << " as compensation";
                    }
                }
            }

            ClearGossipMenuFor(player);
            AddGossipItemFor(player, GossipOptionIcon::AdventureMap, "", 0, 1, ss.str().c_str(), 0, false);
            SendGossipMenuFor(player, 1, upgrader->GetGUID());
            m_ItemTargets[player->GetGUID().GetCounter()] = item->GetGUID();
            return true;
        }

        void OnGossipSelect(Player* player, Item* item, uint32 /*sender*/, uint32 /*action*/) override
        {
            CloseGossipMenuFor(player);
            auto itr = m_ItemTargets.find(player->GetGUID().GetCounter());
            if (itr == m_ItemTargets.end())
                return;

            auto itemTarget = player->GetItemByGuid(itr->second);
            if (!itemTarget)
                return;

            if (itemTarget->GetScriptId() == item->GetScriptId() || item == itemTarget)
            {
                ChatHandler(player).SendSysMessage("|cffFF0000You can't enhance that item.");
                return;
            }

            // Consume the scroll
            if (!itemTarget->HasBonusId(BonusIDAward))
            {
                if (itemTarget->IsEquipped())
                    player->_ApplyItemMods(itemTarget, itemTarget->GetSlot(), false);

                bool success = true;

                if (!itemTarget->AddBonuses(BonusIDAward))
                    success = false;

                itemTarget->SetState(ItemUpdateState::ITEM_CHANGED, player);

                if (success)
                {
                    std::vector<int32> bonusListIDs = itemTarget->m_itemData->BonusListIDs;

                    std::set<int32> corruptionsToRemove;
                    for (auto bonusId : bonusListIDs)
                    {
                        auto itr = CorruptionsReplaceMap.find(bonusId);
                        if (itr != CorruptionsReplaceMap.end())
                        {
                            if (itr->second.first)
                                corruptionsToRemove.insert(itr->second.first);
                            if (itr->second.second)
                                corruptionsToRemove.insert(itr->second.second);
                        }
                    }

                    if (!corruptionsToRemove.empty())
                    {
                        for (auto bonusId : corruptionsToRemove)
                        {
                            auto it = std::find(bonusListIDs.begin(), bonusListIDs.end(), bonusId);
                            if (it != bonusListIDs.end())
                            {
                                auto itr2 = CorruptionCostsRefunds.find(bonusId);
                                if (itr2 != CorruptionCostsRefunds.end())
                                {
                                    player->ModifyCurrency(itr2->second.CurrencyID, itr2->second.RefundAmount);
                                }

                                bonusListIDs.erase(it);
                            }
                        }
                    }

                    itemTarget->SetBonuses(bonusListIDs);
                }

                if (itemTarget->IsEquipped())
                    player->_ApplyItemMods(itemTarget, itemTarget->GetSlot(), true);
                player->SaveToDB();
                /// CharacterDatabaseTransaction trans = CharacterDatabase.BeginTransaction();
                /// itemTarget->SaveToDB(trans);
                /// CharacterDatabase.CommitTransaction(trans);
                if (success)
                {
                    ChatHandler(player).PSendSysMessage("|cff00FF00Succesfully enhanced %s", Item::GetItemLink(itemTarget, player).c_str());
                    player->DestroyItem(item->GetBagSlot(), item->GetSlot(), true);
                }
                else
                    ChatHandler(player).PSendSysMessage("|cff00FF00%s Internal error trying to upgrade", Item::GetItemLink(itemTarget, player).c_str());
            }
        }
};

struct npc_mother_700013 : public ScriptedAI
{
    public:
        npc_mother_700013(Creature* creature) : ScriptedAI(creature) { }

        bool OnGossipHello(Player* player) override
        {
            ClearGossipMenuFor(player);
            AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/Icons/spell_fire_twilightfire.blp:30:30:-30:0|tShadow Essence Enhancements", 0, 1);
            AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/Icons/ability_paladin_toweroflight.blp:30:30:-30:0|tLight Essence Enhancements", 0, 2);
            AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/Icons/inv_maweye_black.blp:30:30:-30:0|tMaw Essence Enhancements", 0, 3);
            SendGossipMenuFor(player, 700013, me);
            return true;
        }

        bool OnGossipSelect(Player* player, uint32 /*menuId*/, uint32 gossipId) override
        {
            auto actionId = player->PlayerTalkClass->GetGossipOptionAction(gossipId);
            ClearGossipMenuFor(player);

            switch (actionId)
            {
                case 1:
                    player->GetSession()->SendListInventory(me->GetGUID(), 700013);
                    break;
                case 2:
                    player->GetSession()->SendListInventory(me->GetGUID(), 7000130);
                    break;
                case 3:
                    player->GetSession()->SendListInventory(me->GetGUID(), 7000131);
                    break;
                default:
                    OnGossipHello(player);
                    break;
            }
            return true;
        }
};

class item_enhancement_system_playerscript : public PlayerScript
{
    public:
        item_enhancement_system_playerscript() : PlayerScript("item_enhancement_system_playerscript") { }

        void OnPlayerModifyCurrency(Player* player, uint32 id, uint32 /*oldCount*/, int32 newCount)
        {
            if (id == 10170 && newCount >= 100) ///< Shadow Essence
            {
                if (player->GetQuestStatus(699999) == QUEST_STATUS_NONE)
                {
                    //player->SetQuestStatus(699999, QuestStatus::QUEST_STATUS_REWARDED, false);
                    auto q = sObjectMgr->GetQuestTemplate(699999);
                    player->AddQuest(q, player);
                    player->RewardQuest(q, LootItemType::Item, 0, player, false);
                    Conversation::CreateConversation(700013, player, *player, player->GetGUID());
                }
            }
        }
};

class item_enhancement_system_chisel : public ItemScript
{
public:
    item_enhancement_system_chisel() : ItemScript("item_enhancement_system_chisel") { }

    bool OnUse(Player* player, Item* upgrader, SpellCastTargets const& targets, ObjectGuid /*castId*/) override
    {
        if (!targets.GetItemTarget())
            return true;

        auto item = targets.GetItemTarget();

        if (!item)
            return true;

        if (item->GetScriptId() == upgrader->GetScriptId() || item == upgrader)
        {
            ChatHandler(player).SendSysMessage("|cffFF0000You can't use the chisel on that item.");
            return true;
        }

        ClearGossipMenuFor(player);

        std::ostringstream ss;
        std::ostringstream ss2;

        bool hasCorruptions = false;

        for (auto itr = CorruptionCostsRefunds.begin(); itr != CorruptionCostsRefunds.end(); ++itr)
        {
            if (item->HasBonusId(itr->first))
            {
                if (auto currency = sCurrencyTypesStore.LookupEntry(itr->second.CurrencyID))
                {
                    ss << "|TInterface/Icons/" << itr->second.Icon << ":30:30:-23:0|t Remove |cff762DEE" << itr->second.Name;
                    ss2 << "|cff62CBF5Are you sure you want to remove |cff762DEE" << itr->second.Name << "|R?";
                    ss2 << "\n\n|cff62CBF5You will recieve |cff8B00FF[" << currency->Name.Str[0] << "]|r |cff62CBF5x" << itr->second.RefundAmount << " as compensation";

                    std::string corruption = itr->second.Name;
                    uint32 bonusToRemove = itr->first;
                    uint32 currencyId = itr->second.CurrencyID;
                    uint32 refundAmount = itr->second.RefundAmount;

                    ObjectGuid itemGuid = item->GetGUID();

                    AddGossipItemFor(player, GossipOptionIcon::None, ss.str(), 0, 0, ss2.str(), 0, false, [this, player, upgrader, targets, corruption, bonusToRemove, itemGuid, currencyId, refundAmount](std::string /*callback*/)
                    {
                        if (auto item = player->GetItemByGuid(itemGuid))
                        {
                            if (item->IsEquipped())
                                player->_ApplyItemMods(item, item->GetSlot(), false);

                            if (item->RemoveBonus(bonusToRemove))
                            {
                                player->ModifyCurrency(currencyId, refundAmount);
                                ChatHandler(player).PSendSysMessage("%s |cff62CBF5has been updated! |cff62CBF5%s|R |cff62CBF5has been removed", item->GetItemLink(item, player).c_str(), corruption.c_str());
                                item->SetState(ItemUpdateState::ITEM_CHANGED, player);
                                player->SaveToDB();
                                CloseGossipMenuFor(player);
                                //OnUse(player, upgrader, targets, ObjectGuid::Empty);
                                if (item->IsEquipped())
                                    player->_ApplyItemMods(item, item->GetSlot(), true);
                                return;
                            }
                            if (item->IsEquipped())
                                player->_ApplyItemMods(item, item->GetSlot(), true);
                        }

                        CloseGossipMenuFor(player);
                    });

                    ss.clear();
                    ss.str("");
                    ss2.clear();
                    ss2.str("");
                    hasCorruptions = true;
                }

            }
        }

        if (hasCorruptions)
            SendGossipMenuFor(player, 688881, upgrader->GetGUID());
        else
        {
            ChatHandler(player).PSendSysMessage("%s |cff62CBF5has no corruptions to remove!", item->GetItemLink(item, player).c_str());
            CloseGossipMenuFor(player);
        }
        return true;
    }
};

void AddSC_item_enhancement_system()
{
    new item_enhancement_system<Verastile1>("item_enhancement_system_t1_versatile");
    new item_enhancement_system<Masterful1>("item_enhancement_system_t1_masterful");
    new item_enhancement_system<Expedient1>("item_enhancement_system_t1_expident");
    new item_enhancement_system<Severe1>("item_enhancement_system_t1_severe");
    new item_enhancement_system<Avoidant1>("item_enhancement_system_t1_avoidant");
    new item_enhancement_system<Siphoner1>("item_enhancement_system_t1_siphoner");
    new item_enhancement_system<IneffableTruth1>("item_enhancement_system_t1_ineffable_truth");
    new item_enhancement_system<Empowerment1>("item_enhancement_system_t1_50_ilvls");

    new item_enhancement_system<Versatile2>("item_enhancement_system_t2_versatile");
    new item_enhancement_system<Masterful2>("item_enhancement_system_t2_masterful");
    new item_enhancement_system<Expedient2>("item_enhancement_system_t2_expident");
    new item_enhancement_system<Severe2>("item_enhancement_system_t2_severe");
    new item_enhancement_system<Avoidant2>("item_enhancement_system_t2_avoidant");
    new item_enhancement_system<Siphoner2>("item_enhancement_system_t2_siphoner");
    new item_enhancement_system<IneffableTruth2 >("item_enhancement_system_t2_ineffable_truth");
    new item_enhancement_system<Empowerment2>("item_enhancement_system_t2_50_ilvls");

    new item_enhancement_system<Versatile3>("item_enhancement_system_t3_versatile");
    new item_enhancement_system<Masterful3>("item_enhancement_system_t3_masterful");
    new item_enhancement_system<Expedient3>("item_enhancement_system_t3_expident");
    new item_enhancement_system<Severe3>("item_enhancement_system_t3_severe");
    new item_enhancement_system<Avoidant3>("item_enhancement_system_t3_avoidant");
    new item_enhancement_system<Siphoner3>("item_enhancement_system_t3_siphoner");
    new item_enhancement_system<IneffableTruth3>("item_enhancement_system_t3_ineffable_truth");
    new item_enhancement_system<Empowerment3>("item_enhancement_system_t3_50_ilvls");

    RegisterCreatureAI(npc_mother_700013);

    new item_enhancement_system_playerscript();
    new item_enhancement_system_chisel();
}
