#include "ScriptMgr.h"
#include "Item.h"
#include "Player.h"
#include "Spell.h"
#include "Chat.h"
#include "DatabaseEnv.h"
#include "QuestPackets.h"
#include "QuestDef.h"
#include "DB2Stores.h"

enum class ItemUpgradeType
{
    ItemReplace = 0,
    BonusID     = 1,
};

// z_item_upgrade_materials
struct ItemRequiredMaterials
{
    QuestObjectiveType Type;
    uint32 RequiredID;
    uint32 RequiredAmount;
};

// z_item_upgrade
struct ItemUpgrade
{
    ItemUpgradeType Type;
    uint32 RequiredID;
    uint32 RequiredAmount;
    uint32 MaterialID;
    uint32 ReplaceItemID;
    uint32 ReplaceItemQuantity;
    std::vector<int32> ReplaceBonusIDList;
    std::vector<ItemRequiredMaterials> RequiredMaterials;
};

class ItemUpgradeStorage
{
    public:
        static ItemUpgradeStorage* instance()
        {
            static ItemUpgradeStorage l_Instance;
            return &l_Instance;
        }

        void LoadFromDB()
        {
            TC_LOG_INFO("server.loading", "Loading item upgrader");
            m_ItemUpgrades.clear();
            m_Materials.clear();

            QueryResult l_Query = WorldDatabase.Query("SELECT MaterialID, Type, RequiredID, RequiredAmount FROM z_item_upgrade_materials ORDER by Ordering");
            if (l_Query)
            {
                do
                {
                    Field* l_Fields = l_Query->Fetch();

                    ItemRequiredMaterials l_Materials;

                    l_Materials.Type            = static_cast<QuestObjectiveType>(l_Fields[1].GetUInt32());
                    l_Materials.RequiredID      = l_Fields[2].GetUInt32();
                    l_Materials.RequiredAmount  = l_Fields[3].GetUInt32();

                    if (l_Materials.Type == QuestObjectiveType::QUEST_OBJECTIVE_CURRENCY)
                        if (!sCurrencyTypesStore.LookupEntry(l_Materials.RequiredID))
                            continue;

                    m_Materials.insert({ l_Fields[0].GetUInt32(), l_Materials });

                } while (l_Query->NextRow());
            }

            l_Query = WorldDatabase.Query("SELECT EntryID, Type, RequiredID, RequiredAmount, MaterialID, ReplaceItemID, ReplaceItemQuantity, ReplaceBonusIDList FROM z_item_upgrade;");
            if (l_Query)
            {
                do
                {
                    Field* l_Fields = l_Query->Fetch();

                    ItemUpgrade l_Upgrade;

                    l_Upgrade.Type = static_cast<ItemUpgradeType>(l_Fields[1].GetUInt8());
                    l_Upgrade.RequiredID = l_Fields[2].GetUInt32();
                    l_Upgrade.RequiredAmount = l_Fields[3].GetUInt32();
                    l_Upgrade.MaterialID = l_Fields[4].GetUInt32();
                    l_Upgrade.ReplaceItemID = l_Fields[5].GetUInt32();
                    l_Upgrade.ReplaceItemQuantity = l_Fields[6].GetUInt32();

                    for (std::string_view token : Trinity::Tokenize(l_Fields[7].GetStringView(), ' ', false))
                        if (Optional<int32> bonusListID = Trinity::StringTo<int32>(token))
                            l_Upgrade.ReplaceBonusIDList.push_back(*bonusListID);

                    if (l_Upgrade.MaterialID > 0)
                    {
                        auto l_Itr = m_Materials.equal_range(l_Upgrade.MaterialID);

                        for (auto l_I = l_Itr.first; l_I != l_Itr.second; ++l_I)
                        {
                            l_Upgrade.RequiredMaterials.push_back(l_I->second);
                        }
                    }

                    m_ItemUpgrades.insert({ l_Fields[0].GetUInt32(), l_Upgrade } );

                } while (l_Query->NextRow());
            }
            TC_LOG_INFO("server.loading", "Loaded item upgrader %u upgrades %u materials", m_ItemUpgrades.size(), m_Materials.size());
        }

        ItemUpgrade const* GetItemUpgrade(Item* p_TargetItem)
        {
            auto l_Itr = m_ItemUpgrades.equal_range(p_TargetItem->GetEntry());

            for (auto l_I = l_Itr.first; l_I != l_Itr.second; ++l_I)
            {
                if (l_I->second.Type == ItemUpgradeType::ItemReplace)
                    return &l_I->second;

                if (l_I->second.Type == ItemUpgradeType::BonusID)
                {
                    uint32 RequiredBonusID = l_I->second.RequiredID;
                    uint32 RequiredAmount = l_I->second.RequiredAmount;

                    for (uint32 bonusId : *p_TargetItem->m_itemData->BonusListIDs)
                    {
                        if (bonusId == RequiredBonusID)
                        {
                            if (RequiredAmount == 0 || --RequiredAmount == 0)
                                return &l_I->second;
                        }
                    }
                }
            }


            return nullptr;
        }

    private:
        std::multimap<uint32, ItemUpgrade> m_ItemUpgrades;
        std::multimap<uint32, ItemRequiredMaterials> m_Materials;
};

#define sItemUpgrader ItemUpgradeStorage::instance()

// 700000
class item_upgrader : public ItemScript
{
    public:
        item_upgrader() : ItemScript("item_upgrader") { }

        std::unordered_map<ObjectGuid, ObjectGuid> m_PlayerItemTargets;

        bool OnUse(Player* player, Item* item, SpellCastTargets const& targets, ObjectGuid /*castId*/) override
        {
            if (!targets.GetItemTarget())
                return true;

            auto l_ItemUpgrade = sItemUpgrader->GetItemUpgrade(targets.GetItemTarget());
            if (!l_ItemUpgrade)
            {
                ChatHandler(player->GetSession()).PSendSysMessage("%s |cffFF0000is not upgradeable.|R", targets.GetItemTarget()->GetTemplate()->GetName(LocaleConstant::LOCALE_enUS));

                if (player->GetQuestStatus(700002) == QUEST_STATUS_INCOMPLETE)
                {
                    auto l_Creature = player->FindNearestCreature(700003, 30.0f);
                    if (l_Creature && l_Creature->AI())
                    {
                        l_Creature->AI()->Talk(1, player);
                    }
                }

                return true;
            }

            m_PlayerItemTargets[player->GetGUID()] = targets.GetItemTarget()->GetGUID();


            if (player->GetQuestStatus(700002) == QUEST_STATUS_INCOMPLETE)
            {
                auto l_Creature = player->FindNearestCreature(700003, 30.0f);
                if (l_Creature && l_Creature->AI())
                {
                    l_Creature->AI()->Talk(2, player);
                }
            }
            
            auto BuildRequireLine([](std::string const& p_Text, std::string const& p_String) -> std::string
            {
                return "|cffCB4335+ |cff05B61D" + p_Text + " |cffE74C3C: " + p_String + "\n";
            });


            std::string questDetails;
            std::ostringstream l_SS;

            {
                uint32 l_CurrCount = player->GetItemCount(targets.GetItemTarget()->GetEntry());

                l_SS << Item::GetItemLink(targets.GetItemTarget()->GetEntry());

                if (l_ItemUpgrade->RequiredAmount > 0)
                {
                    if (l_CurrCount >= l_ItemUpgrade->RequiredAmount)
                        l_SS << " |cff09ff1b(" << l_CurrCount << "/" << l_ItemUpgrade->RequiredAmount;
                    else
                        l_SS << " |cffff0909(" << l_CurrCount << "/" << l_ItemUpgrade->RequiredAmount;
                }

                l_SS << ")";

                questDetails += BuildRequireLine("Source", l_SS.str());

                l_SS.clear();
                l_SS.str("");
            }

            questDetails += "\n";

            for (auto l_Item : l_ItemUpgrade->RequiredMaterials)
            {
                switch (l_Item.Type)
                {
                    case QuestObjectiveType::QUEST_OBJECTIVE_CURRENCY:

                        if (l_Item.RequiredID > 0)
                        {
                            uint32 l_CurrCount = player->GetCurrency(l_Item.RequiredID);

                            l_SS << sCurrencyTypesStore.LookupEntry(l_Item.RequiredID)->Name.Str[0];

                            if (l_CurrCount >= l_Item.RequiredAmount)
                                l_SS << " |cff09ff1b(" << l_CurrCount << "/" << l_Item.RequiredAmount;
                            else
                                l_SS << " |cffff0909(" << l_CurrCount << "/" << l_Item.RequiredAmount;

                            l_SS << ")";

                            ChatHandler(player).PSendSysMessage("%s", l_SS.str().c_str());

                            questDetails += BuildRequireLine("Require", l_SS.str());

                            l_SS.clear();
                            l_SS.str("");
                        }

                        break;
                    case QuestObjectiveType::QUEST_OBJECTIVE_ITEM:

                        if (l_Item.RequiredID > 0)
                        {
                            uint32 l_CurrCount = player->GetItemCount(l_Item.RequiredID);

                            l_SS << Item::GetItemLink(l_Item.RequiredID);

                            if (l_CurrCount >= l_Item.RequiredAmount)
                                l_SS << " |cff09ff1b(" << l_CurrCount << "/" << l_Item.RequiredAmount;
                            else
                                l_SS << " |cffff0909(" << l_CurrCount << "/" << l_Item.RequiredAmount;

                            l_SS << ")";

                            ChatHandler(player).PSendSysMessage("%s", l_SS.str().c_str());

                            questDetails += BuildRequireLine("Require", l_SS.str());

                            l_SS.clear();
                            l_SS.str("");
                        }
                        break;
                    case QuestObjectiveType::QUEST_OBJECTIVE_MONEY:
                        if (l_Item.RequiredAmount > 0)
                        {
                            uint32 l_CurrCount = player->GetMoney();

                            l_SS << "|cffE74C3C" << l_Item.RequiredAmount << " |cff05B61DGold";

                            if (l_CurrCount >= l_Item.RequiredAmount)
                                l_SS << " |cff09ff1b(" << l_CurrCount << "/" << l_Item.RequiredAmount;
                            else
                                l_SS << " |cffff0909(" << l_CurrCount << "/" << l_Item.RequiredAmount;

                            l_SS << ")";

                            ChatHandler(player).PSendSysMessage("%s", l_SS.str().c_str());

                            questDetails += BuildRequireLine("Require", l_SS.str());

                            l_SS.clear();
                            l_SS.str("");
                        }
                        break;
                }
            }

            questDetails += "\n";

            //if (l_UpgradeData->RequiredMG)
            //{
            //    l_SS << "|cffE74C3C" << l_UpgradeData->RequiredMG << " |cff05B61DMg";
            //    questDetails += BuildRequireLine("Require", l_SS.str());
            //
            //    l_SS.clear();
            //    l_SS.str("");
            //}

            //if (l_UpgradeData->RequiredGold)
            //{
            //    l_SS << "|cffE74C3C" << l_UpgradeData->RequiredGold << " |cff05B61DGold";
            //    questDetails += BuildRequireLine("Require", l_SS.str());
            //
            //    l_SS.clear();
            //    l_SS.str("");
            //}
            //
            //uint32 l_CalculatedChance = CalculateChance(p_Player, l_UpgradeData->Chance);
            //l_SS << "|cffE74C3C" << l_UpgradeData->Chance << ".00%";
            //
            //if (l_CalculatedChance > l_UpgradeData->Chance)
            //    l_SS << "|cffFFB109 +(" << (l_CalculatedChance - l_UpgradeData->Chance) << ".00%)";

            //questDetails += BuildRequireLine("Probability", l_SS.str());



            WorldPackets::Quest::QuestGiverQuestDetails packet;

            packet.QuestTitle = targets.GetItemTarget()->GetTemplate()->GetName(LocaleConstant::LOCALE_enUS);
            packet.LogDescription = "";
            packet.DescriptionText = questDetails;
            packet.PortraitGiverText = "";
            packet.PortraitGiverName = "";
            packet.PortraitTurnInText = "";
            packet.PortraitTurnInName = "";

            packet.QuestGiverGUID = item->GetGUID();
            packet.InformUnit = ObjectGuid::Empty;
            packet.QuestID = 591918;
            packet.QuestPackageID = 0;
            packet.PortraitGiver = 0;
            packet.PortraitGiverMount = 0;
            packet.PortraitGiverModelSceneID = 0;
            packet.PortraitTurnIn = 0;
            packet.QuestSessionBonus = 0; //quest->GetQuestSessionBonus(); // this is only sent while quest session is active
            packet.AutoLaunched = false;
            packet.DisplayPopup = false;
            packet.QuestFlags[0] = 0;
            packet.QuestFlags[1] = 0;
            packet.SuggestedPartyMembers = 0;


            packet.Rewards.ChoiceItemCount = 0;
            packet.Rewards.ItemCount = 0;
            packet.Rewards.Money = 0;
            packet.Rewards.XP = 0;
            packet.Rewards.ArtifactCategoryID = 0;
            packet.Rewards.Title = 0;
            packet.Rewards.FactionFlags = 0;

            packet.Rewards.SpellCompletionID = 0;
            packet.Rewards.SkillLineID = 0;
            packet.Rewards.NumSkillUps = 0;
            packet.Rewards.TreasurePickerID = 591918;

           //packet.Rewards.ChoiceItems[0].Item.ItemID = l_ItemUpgrade->ReplaceItemID ? l_ItemUpgrade->ReplaceItemID : targets.GetItemTarget()->GetEntry();
           //packet.Rewards.ChoiceItems[0].Quantity = l_ItemUpgrade->ReplaceItemQuantity ? l_ItemUpgrade->ReplaceItemQuantity : 1;
           //if (!l_ItemUpgrade->ReplaceBonusIDList.empty())
           //{
           //    packet.Rewards.ChoiceItems[0].Item.ItemBonus.emplace();
           //    packet.Rewards.ChoiceItems[0].Item.ItemBonus->Context = ItemContext::Torghast;
           //    for (int32 bonusId : l_ItemUpgrade->ReplaceBonusIDList)
           //        packet.Rewards.ChoiceItems[0].Item.ItemBonus->BonusListIDs.push_back(bonusId);
           //}

            for (uint32 i = 0; i < QUEST_REWARD_CHOICES_COUNT; ++i)
            {
               // packet.Rewards.ChoiceItems[i].LootItemType =;
                packet.Rewards.ChoiceItems[i].Item.ItemID = 0;
                packet.Rewards.ChoiceItems[i].Quantity = 0;
            }

            for (uint32 i = 0; i < QUEST_REWARD_ITEM_COUNT; ++i)
            {
                packet.Rewards.ItemID[i] = 0;
                packet.Rewards.ItemQty[i] = 0;
            }

            for (uint32 i = 0; i < QUEST_REWARD_REPUTATIONS_COUNT; ++i)
            {
                packet.Rewards.FactionID[i] = 0;
                packet.Rewards.FactionValue[i] = 0;
                packet.Rewards.FactionOverride[i] = 0;
                packet.Rewards.FactionCapIn[i] = 0;
            }

            for (uint32 i = 0; i < QUEST_REWARD_CURRENCY_COUNT; ++i)
            {
                packet.Rewards.CurrencyID[i] = 0;
                packet.Rewards.CurrencyQty[i] = 0;
            }

            //QuestObjectives const& objs = quest->GetObjectives();
            packet.Objectives.resize(l_ItemUpgrade->RequiredMaterials.size());
            for (uint32 i = 0; i < l_ItemUpgrade->RequiredMaterials.size(); ++i)
            {
                packet.Objectives[i].ID = l_ItemUpgrade->RequiredMaterials[i].RequiredID;
                packet.Objectives[i].ObjectID = i+100;
                packet.Objectives[i].Amount = l_ItemUpgrade->RequiredMaterials[i].RequiredAmount;
                packet.Objectives[i].Type = l_ItemUpgrade->RequiredMaterials[i].Type;
            }

            player->GetSession()->SendPacket(packet.Write());

            WorldPackets::Quest::TreasurePickerResponse l_Packet2;

            l_Packet2.QuestID = 591918;
            l_Packet2.TreasurePickerID = 591918;

            WorldPackets::Quest::TreasurePickItem l_Item;
            l_Item.Item.ItemID = l_ItemUpgrade->ReplaceItemID ? l_ItemUpgrade->ReplaceItemID : targets.GetItemTarget()->GetEntry();
            l_Item.Quantity = l_ItemUpgrade->ReplaceItemQuantity ? l_ItemUpgrade->ReplaceItemQuantity : 1;
            if (!l_ItemUpgrade->ReplaceBonusIDList.empty())
            {
                l_Item.Item.ItemBonus.emplace();
                l_Item.Item.ItemBonus->Context = ItemContext::Torghast;
                for (int32 bonusId : l_ItemUpgrade->ReplaceBonusIDList)
                    l_Item.Item.ItemBonus->BonusListIDs.push_back(bonusId);
            }

            l_Item.Quantity = 1;
            l_Packet2.Items.push_back(l_Item);
            player->GetSession()->SendPacket(l_Packet2.Write());

            return true;
        }

        bool OnItemQuestQueryResponse(Player* p_Player, Item* p_Item) override
        {
            auto l_Itr = m_PlayerItemTargets.find(p_Player->GetGUID());
            if (l_Itr == m_PlayerItemTargets.end())
                return true;

            auto l_ItemTarget = p_Player->GetItemByGuid(l_Itr->second);
            if (!l_ItemTarget)
                return true;

            auto l_ItemUpgrade = sItemUpgrader->GetItemUpgrade(l_ItemTarget);
            if (!l_ItemUpgrade)
                return true;


            WorldPackets::Quest::QueryQuestInfoResponse response;

            response.Allow = true;
            response.QuestID = 591918;

            response.Info.LogTitle = "Title";
            response.Info.LogDescription = "logDescription";
            response.Info.QuestDescription = "QuestDescription";
            response.Info.AreaDescription = "";
            response.Info.QuestCompletionLog = "";
            response.Info.PortraitGiverText  = "";
            response.Info.PortraitGiverName  = "";
            response.Info.PortraitTurnInText = "";
            response.Info.PortraitTurnInName = "";

            response.Info.QuestID = 591918;

            for (uint8 i = 0; i < QUEST_ITEM_DROP_COUNT; ++i)
            {
                response.Info.ItemDrop[i] = 0;
                response.Info.ItemDropQuantity[i] = 0;
            }

            for (uint8 i = 0; i < QUEST_REWARD_ITEM_COUNT; ++i)
            {
                response.Info.RewardItems[i] = 0;
                response.Info.RewardAmount[i] = 0;
            }

            response.Info.UnfilteredChoiceItems[0].ItemID = l_ItemUpgrade->ReplaceItemID ? l_ItemUpgrade->ReplaceItemID : l_ItemTarget->GetEntry();
            response.Info.UnfilteredChoiceItems[0].Quantity = l_ItemUpgrade->ReplaceItemQuantity ? l_ItemUpgrade->ReplaceItemQuantity : 1;


            for (uint8 i = 1; i < QUEST_REWARD_CHOICES_COUNT; ++i)
            {
                response.Info.UnfilteredChoiceItems[i].ItemID = 0;
                response.Info.UnfilteredChoiceItems[i].Quantity = 0;
            }

            for (uint8 i = 0; i < QUEST_REWARD_REPUTATIONS_COUNT; ++i)
            {
                response.Info.RewardFactionID[i] = 0;
                response.Info.RewardFactionValue[i] = 0;
                response.Info.RewardFactionOverride[i] = 0;
                response.Info.RewardFactionCapIn[i] = 0;
            }


            response.Info.Objectives.resize(l_ItemUpgrade->RequiredMaterials.size());
            for (uint32 i = 0; i < l_ItemUpgrade->RequiredMaterials.size(); ++i)
            {
                response.Info.Objectives[i].ID = l_ItemUpgrade->RequiredMaterials[i].RequiredID;
                response.Info.Objectives[i].ObjectID = i+100;
                response.Info.Objectives[i].Amount = l_ItemUpgrade->RequiredMaterials[i].RequiredAmount;
                response.Info.Objectives[i].Type = l_ItemUpgrade->RequiredMaterials[i].Type;
            }

            for (uint32 i = 0; i < QUEST_REWARD_CURRENCY_COUNT; ++i)
            {
                response.Info.RewardCurrencyID[i] = 0;
                response.Info.RewardCurrencyQty[i] = 0;
            }


            p_Player->GetSession()->SendPacket(response.Write());

            return true;
        }

        bool OnQueryTreasurePicker(Player* p_Player, Item* p_Item) override
        {
            auto l_Itr = m_PlayerItemTargets.find(p_Player->GetGUID());
            if (l_Itr == m_PlayerItemTargets.end())
                return true;

            auto l_ItemTarget = p_Player->GetItemByGuid(l_Itr->second);
            if (!l_ItemTarget)
                return true;

            auto l_ItemUpgrade = sItemUpgrader->GetItemUpgrade(l_ItemTarget);
            if (!l_ItemUpgrade)
                return true;

            WorldPackets::Quest::TreasurePickerResponse l_Packet2;

            l_Packet2.QuestID = 591918;
            l_Packet2.TreasurePickerID = 591918;

            WorldPackets::Quest::TreasurePickItem l_Item;
            l_Item.Item.ItemID = l_ItemUpgrade->ReplaceItemID ? l_ItemUpgrade->ReplaceItemID : l_ItemTarget->GetEntry();
            l_Item.Quantity = l_ItemUpgrade->ReplaceItemQuantity ? l_ItemUpgrade->ReplaceItemQuantity : 1;
            if (!l_ItemUpgrade->ReplaceBonusIDList.empty())
            {
                l_Item.Item.ItemBonus.emplace();
                l_Item.Item.ItemBonus->Context = ItemContext::Torghast;
                for (int32 bonusId : l_ItemUpgrade->ReplaceBonusIDList)
                    l_Item.Item.ItemBonus->BonusListIDs.push_back(bonusId);
            }

            l_Item.Quantity = 1;
            l_Packet2.Items.push_back(l_Item);
            p_Player->GetSession()->SendPacket(l_Packet2.Write());
            return true;
        }

        bool OnQuestAccept(Player* p_Player, Item* p_Item, Quest const* /*p_Quest*/) override
        {
            auto l_Itr = m_PlayerItemTargets.find(p_Player->GetGUID());
            if (l_Itr == m_PlayerItemTargets.end())
                return true;

            auto l_ItemTarget = p_Player->GetItemByGuid(l_Itr->second);
            if (!l_ItemTarget)
                return true;

            auto l_ItemUpgrade = sItemUpgrader->GetItemUpgrade(l_ItemTarget);
            if (!l_ItemUpgrade)
                return true;

            bool l_Good = true;

            for (auto const& l_I : l_ItemUpgrade->RequiredMaterials)
            {
                switch (l_I.Type)
                {
                    case QUEST_OBJECTIVE_ITEM:
                    {
                        bool l_Has = p_Player->HasItemCount(l_I.RequiredID, l_I.RequiredAmount);
                        if (!l_Has)
                        {
                            l_Good = false;
                            ChatHandler(p_Player->GetSession()).PSendSysMessage(
                                "You don't have enough %s, Need %u but you only have %u. Need %u more",
                                Item::GetItemLink(l_I.RequiredID),
                                l_I.RequiredAmount,
                                p_Player->GetItemCount(l_I.RequiredID),
                                l_I.RequiredAmount - p_Player->GetItemCount(l_I.RequiredID)
                            );
                        }
                        break;
                    }
                    case QUEST_OBJECTIVE_CURRENCY:
                    {
                        bool l_Has = p_Player->HasCurrency(l_I.RequiredID, l_I.RequiredAmount);
                        if (!l_Has)
                        {
                            l_Good = false;
                            ChatHandler(p_Player->GetSession()).PSendSysMessage(
                                "You don't have enough %s, Need %u but you only have %u. Need %u more",
                                sCurrencyTypesStore.LookupEntry(l_I.RequiredID)->Name.Str[0],
                                l_I.RequiredAmount,
                                p_Player->GetCurrency(l_I.RequiredID),
                                l_I.RequiredAmount - p_Player->GetCurrency(l_I.RequiredID)
                            );
                        }
                        break;
                    }
                    case QUEST_OBJECTIVE_MONEY:
                    {
                        bool l_Has = p_Player->HasEnoughMoney((int64)l_I.RequiredAmount);
                        if (!l_Has)
                        {
                            l_Good = false;
                            ChatHandler(p_Player->GetSession()).PSendSysMessage(
                                "You don't have enough gold, Need %u but you only have %u. Need %u more",
                                l_I.RequiredAmount / 10000,
                                p_Player->GetMoney() / 10000,
                                (l_I.RequiredAmount - p_Player->GetMoney()) / 10000
                            );
                        }
                        break;
                    }
                }
            }

            if (!l_Good)
                return false;
            
            for (auto const& l_I : l_ItemUpgrade->RequiredMaterials)
            {
                switch (l_I.Type)
                {
                    case QUEST_OBJECTIVE_ITEM:
                    {
                        p_Player->DestroyItemCount(l_I.RequiredID, l_I.RequiredAmount, true);
                        break;
                    }
                    case QUEST_OBJECTIVE_CURRENCY:
                    {
                        p_Player->ModifyCurrency(l_I.RequiredID, -((int32)l_I.RequiredAmount));
                        break;
                    }
                    case QUEST_OBJECTIVE_MONEY:
                    {
                        p_Player->ModifyMoney(-((int64)l_I.RequiredAmount));
                        break;
                    }
                }
            }

            if (l_ItemUpgrade->ReplaceItemID > 0)
            {
                uint32 l_Count = 1;
                p_Player->DestroyItemCount(l_ItemTarget, l_Count, true);
            }

            if (!l_ItemUpgrade->ReplaceBonusIDList.empty())
            {
                l_ItemTarget->ClearBonuses();
                l_ItemTarget->SetBonuses(l_ItemUpgrade->ReplaceBonusIDList);
                p_Player->SendNewItem(l_ItemTarget, 1, true, false, true);
            }

            ChatHandler(p_Player->GetSession()).PSendSysMessage("|cff00FF00Success");

            if (p_Player->GetQuestStatus(700002) == QUEST_STATUS_INCOMPLETE)
                p_Player->KilledMonsterCredit(700003);
            return true;
        }

};

void AddSC_item_upgrader()
{
    sItemUpgrader->LoadFromDB();
    new item_upgrader();
}
