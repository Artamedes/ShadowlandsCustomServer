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

const std::unordered_map<uint32, CorruptionCostRefund> CorruptionCostsRefunds =
{
    { 6477, { "spell_arcane_arcanetactics",       "Versatile I",          10170, 50 } },
    { 6471, { "ability_rogue_sinistercalling",    "Masterful I",          10170, 50 } },
    { 6474, { "ability_mage_netherwindpresence",  "Expedient I",          10170, 50 } },
    { 6480, { "ability_priest_shadowyapparition", "Severe I",             10170, 50 } },
    { 6483, { "spell_warlock_demonsoul",          "Avoidant I",           10170, 50 } },
    { 6493, { "spell_shadow_lifedrain02_purple",  "Siphoner I",           10170, 50 } },
    { 6547, { "inv_wand_1h_nzothraid_d_01",       "Ineffable Truth I",    10170, 50 } },
    { 6478, { "spell_arcane_arcanetactics",       "Versatile II",         10174, 50 } },
    { 6472, { "ability_rogue_sinistercalling",    "Masterful II",         10174, 50 } },
    { 6475, { "ability_mage_netherwindpresence",  "Expedient II",         10174, 50 } },
    { 6481, { "ability_priest_shadowyapparition", "Severe II",            10174, 50 } },
    { 6484, { "spell_warlock_demonsoul",          "Avoidant II",          10174, 50 } },
    { 6494, { "spell_shadow_lifedrain02_purple",  "Siphoner II",          10174, 50 } },
    { 6548, { "inv_wand_1h_nzothraid_d_01",       "Ineffable Truth II",   10174, 50 } },
    { 6479, { "spell_arcane_arcanetactics",       "Versatile III",        10175, 50 } },
    { 6473, { "ability_rogue_sinistercalling",    "Masterful III",        10175, 50 } },
    { 6476, { "ability_mage_netherwindpresence",  "Expedient III",        10175, 50 } },
    { 6482, { "ability_priest_shadowyapparition", "Severe III",           10175, 50 } },
    { 6485, { "spell_warlock_demonsoul",          "Avoidant III",         10175, 50 } },
    { 6495, { "spell_shadow_lifedrain02_purple",  "Siphoner III",         10175, 50 } },
    { 6549, { "inv_wand_1h_nzothraid_d_01",       "Ineffable Truth III",  10175, 50 } },
};

const std::unordered_map<uint32, std::pair<uint32, uint32>> CorruptionsBlacklistMap
{
    { 6477, { 6478, 6479 } }, ///< T1
    { 6471, { 6472, 6473 } }, ///< T1
    { 6474, { 6475, 6476 } }, ///< T1
    { 6480, { 6481, 6482 } }, ///< T1
    { 6483, { 6484, 6485 } }, ///< T1
    { 6493, { 6494, 6495 } }, ///< T1
    { 6547, { 6548, 6549 } }, ///< T1

    { 6478, { 6479, 0 } }, ///< T2
    { 6472, { 6473, 0 } }, ///< T2
    { 6475, { 6476, 0 } }, ///< T2
    { 6481, { 6482, 0 } }, ///< T2
    { 6484, { 6485, 0 } }, ///< T2
    { 6494, { 6495, 0 } }, ///< T2
    { 6548, { 6549, 0 } }, ///< T2
};

const std::unordered_map<uint32, std::pair<uint32, uint32>> CorruptionsReplaceMap
{
    { 6479, { 6478, 6477 } }, ///< T3
    { 6473, { 6472, 6471 } }, ///< T3
    { 6476, { 6475, 6474 } }, ///< T3
    { 6482, { 6481, 6480 } }, ///< T3
    { 6485, { 6484, 6483 } }, ///< T3
    { 6495, { 6494, 6493 } }, ///< T3
    { 6549, { 6548, 6547 } }, ///< T3

    { 6478, { 6477, 0 } }, ///< T2
    { 6472, { 6471, 0 } }, ///< T2
    { 6475, { 6474, 0 } }, ///< T2
    { 6481, { 6480, 0 } }, ///< T2
    { 6484, { 6483, 0 } }, ///< T2
    { 6494, { 6493, 0 } }, ///< T2
    { 6548, { 6547, 0 } }, ///< T2
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

                if (itemTarget->IsEquipped())
                    player->_ApplyItemMods(itemTarget, itemTarget->GetSlot(), true);

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

                        itemTarget->SetBonuses(bonusListIDs);

                        if (itemTarget->IsEquipped())
                        {
                            player->_ApplyItemMods(itemTarget, itemTarget->GetSlot(), false);
                            player->_ApplyItemMods(itemTarget, itemTarget->GetSlot(), true);
                        }
                    }
                }

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
                            if (item->RemoveBonus(bonusToRemove))
                            {
                                player->ModifyCurrency(currencyId, refundAmount);
                                ChatHandler(player).PSendSysMessage("%s |cff62CBF5has been updated! |cff62CBF5%s|R |cff62CBF5has been removed", item->GetItemLink(item, player).c_str(), corruption.c_str());
                                item->SetState(ItemUpdateState::ITEM_CHANGED, player);
                                player->SaveToDB();
                                OnUse(player, upgrader, targets, ObjectGuid::Empty);
                                return;
                            }
                        }

                        CloseGossipMenuFor(player);
                    });

                    ss.clear();
                    ss.str("");
                    ss2.clear();
                    ss2.str("");
                }

            }
        }
        SendGossipMenuFor(player, 688881, upgrader->GetGUID());
        //if (hasCorruptions)
        //    SendGossipMenuFor(player, 688881, upgrader->GetGUID());
        //else
        //{
        //    ChatHandler(player).PSendSysMessage("%s |cff62CBF5has no corruptions to remove!", item->GetItemLink(item, player).c_str());
        //    CloseGossipMenuFor(player);
        //}
    }
};

void AddSC_item_enhancement_system()
{
    new item_enhancement_system<6477>("item_enhancement_system_t1_versatile");
    new item_enhancement_system<6471>("item_enhancement_system_t1_masterful");
    new item_enhancement_system<6474>("item_enhancement_system_t1_expident");
    new item_enhancement_system<6480>("item_enhancement_system_t1_severe");
    new item_enhancement_system<6483>("item_enhancement_system_t1_avoidant");
    new item_enhancement_system<6493>("item_enhancement_system_t1_siphoner");
    new item_enhancement_system<6547>("item_enhancement_system_t1_ineffable_truth");
    new item_enhancement_system<1522>("item_enhancement_system_t1_50_ilvls");

    new item_enhancement_system<6478>("item_enhancement_system_t2_versatile");
    new item_enhancement_system<6472>("item_enhancement_system_t2_masterful");
    new item_enhancement_system<6475>("item_enhancement_system_t2_expident");
    new item_enhancement_system<6481>("item_enhancement_system_t2_severe");
    new item_enhancement_system<6484>("item_enhancement_system_t2_avoidant");
    new item_enhancement_system<6494>("item_enhancement_system_t2_siphoner");
    new item_enhancement_system<6548>("item_enhancement_system_t2_ineffable_truth");
    new item_enhancement_system<1523>("item_enhancement_system_t2_50_ilvls");

    new item_enhancement_system<6479>("item_enhancement_system_t3_versatile");
    new item_enhancement_system<6473>("item_enhancement_system_t3_masterful");
    new item_enhancement_system<6476>("item_enhancement_system_t3_expident");
    new item_enhancement_system<6482>("item_enhancement_system_t3_severe");
    new item_enhancement_system<6485>("item_enhancement_system_t3_avoidant");
    new item_enhancement_system<6495>("item_enhancement_system_t3_siphoner");
    new item_enhancement_system<6549>("item_enhancement_system_t3_ineffable_truth");
    new item_enhancement_system<1524>("item_enhancement_system_t3_50_ilvls");
    RegisterCreatureAI(npc_mother_700013);

    new item_enhancement_system_playerscript();
    new item_enhancement_system_chisel();
}
