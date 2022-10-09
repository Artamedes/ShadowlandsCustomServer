#include "ScriptMgr.h"
#include "Item.h"
#include "Player.h"
#include "Spell.h"
#include "Chat.h"
#include "DatabaseEnv.h"
#include "QuestPackets.h"
#include "QuestDef.h"
#include "DB2Stores.h"
#include "WorldSession.h"
#include "CollectionMgr.h"
#include "GameTime.h"
#include "ItemPackets.h"

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
    std::vector<int32> RemoveBonusIDList;
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

            l_Query = WorldDatabase.Query("SELECT EntryID, Type, RequiredID, RequiredAmount, MaterialID, ReplaceItemID, ReplaceItemQuantity, RemoveBonusIds, AddBonusIds FROM z_item_upgrade;");
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
                            l_Upgrade.RemoveBonusIDList.push_back(*bonusListID);

                    for (std::string_view token : Trinity::Tokenize(l_Fields[8].GetStringView(), ' ', false))
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

                    for (uint32 bonusId : p_TargetItem->m_itemData->Bonuses->BonusListIDs)
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

        struct ItemTarget
        {
        public:
            ItemTarget() { }
            ItemTarget(ObjectGuid itemGuid, uint32 lastItemUpgrade, TimePoint lastUpgradeTime, bool hadMaterials) : ItemGuid(itemGuid), LastItemUpgrade(lastItemUpgrade), LastUpgradeTime(lastUpgradeTime), HadMaterials(hadMaterials) { }

            ObjectGuid ItemGuid;
            uint32 LastItemUpgrade = 0;
            TimePoint LastUpgradeTime;
            bool HadMaterials = false;
        };

        std::unordered_map<ObjectGuid, ItemTarget> m_PlayerItemTargets;

        bool OnUse(Player* player, Item* item, SpellCastTargets const& targets, ObjectGuid /*castId*/) override
        {
            if (!targets.GetItemTarget())
                return true;

            if (auto instance = player->GetInstanceScript())
            {
                if (instance->IsChallenge())
                {
                    Conversation::CreateConversation(700309, player, *player, player->GetGUID());
                    return true;
                }
            }

            if (!BuildPackets(player, item, targets))
                return true;

            return true;
        }

        void DisplayItemUpgrade(Player* player, Item* itemTarget, ItemUpgrade const* itemUpgrade, bool hasMaterials = false)
        {
            auto itr = m_PlayerItemTargets.find(player->GetGUID());

            auto now = GameTime::Now();
            bool dispMsg = false;
            if (itr != m_PlayerItemTargets.end())
            {
                itr->second.ItemGuid = itemTarget->GetGUID();
                if (itr->second.LastUpgradeTime > now && itr->second.LastItemUpgrade == itemUpgrade->RequiredID && !hasMaterials && !itr->second.HadMaterials)
                    dispMsg = true;

                itr->second.LastUpgradeTime = now + 30s;
                itr->second.HadMaterials = hasMaterials;
            }
            else
                m_PlayerItemTargets[player->GetGUID()] = ItemTarget(itemTarget->GetGUID(), 0, now + 30s, hasMaterials);

            WorldPackets::Quest::DisplayPlayerChoice displayPlayerChoice;
            displayPlayerChoice.SenderGUID = itemTarget->GetGUID();
            displayPlayerChoice.ChoiceID = 682925852;
            displayPlayerChoice.Question = "Are you sure you want to upgrade?";
            displayPlayerChoice.CloseChoiceFrame = false;
            displayPlayerChoice.HideWarboardHeader = false;
            displayPlayerChoice.KeepOpenAfterChoice = false;
            displayPlayerChoice.UiTextureKitID = 5260;
            displayPlayerChoice.SoundKitID = 80244; // 80244 brwaler upgrade

            bool l_Good = true;

            for (int i = 0; i < 1; ++i)
            {
                WorldPackets::Quest::PlayerChoiceResponse playerChoiceResponse;

                playerChoiceResponse.ResponseID = 4412414;
                playerChoiceResponse.ResponseIdentifier = 335;
                playerChoiceResponse.ChoiceArtFileID = urand(0, 1) == 1 ? urand(3722245, 3722272) : urand(3718819, 3718827);
                playerChoiceResponse.UiTextureKitID = 5487;
                playerChoiceResponse.WidgetSetID = 120;
                playerChoiceResponse.Reward.emplace();
                playerChoiceResponse.RewardQuestID = 591918;

                if (i == 0)
                {
                    playerChoiceResponse.Header = "Requirements";
                    playerChoiceResponse.SubHeader = "Requirements";
                    playerChoiceResponse.Description = "Tip: Hover over Upgrade to see your reward";
                    playerChoiceResponse.ButtonTooltip = "Clicking this will consume the requirements!";
                    playerChoiceResponse.Confirmation = "Confirmation";
                    playerChoiceResponse.Answer = "Upgrade";
                    playerChoiceResponse.SubHeader = "Consumes";

                    std::ostringstream ss;

                    if (itemUpgrade->Type == ItemUpgradeType::BonusID)
                    {
                        playerChoiceResponse.Reward->Items.emplace_back();
                        WorldPackets::Quest::PlayerChoiceResponseRewardEntry& l_Item = playerChoiceResponse.Reward->Items.back();
                        l_Item.Item.Initialize(itemTarget);
                        l_Item.Quantity = 0;
                    }

                    for (auto const& l_I : itemUpgrade->RequiredMaterials)
                    {
                        switch (l_I.Type)
                        {
                            case QuestObjectiveType::QUEST_OBJECTIVE_CURRENCY:

                                if (l_I.RequiredID > 0)
                                {
                                    playerChoiceResponse.Reward->Currencies.emplace_back();
                                    WorldPackets::Quest::PlayerChoiceResponseRewardEntry& rewardEntry = playerChoiceResponse.Reward->Currencies.back();
                                    rewardEntry.Item.ItemID = l_I.RequiredID;
                                    rewardEntry.Quantity = l_I.RequiredAmount;

                                    bool l_Has = player->HasCurrency(l_I.RequiredID, l_I.RequiredAmount);
                                    if (!l_Has)
                                    {
                                        l_Good = false;
                                        ss << "|cffFF0000You don't have enough "
                                            << sCurrencyTypesStore.LookupEntry(l_I.RequiredID)->Name.Str[0]
                                            << "\n";
                                        //<< ", Need "
                                        //<< l_I.RequiredAmount
                                        //<< " but you only have "
                                        //<< player->GetCurrency(l_I.RequiredID)
                                        //<< ". Need "
                                        //<< l_I.RequiredAmount - player->GetCurrency(l_I.RequiredID)
                                        //<< " more\n";
                                    }
                                }

                                break;
                            case QuestObjectiveType::QUEST_OBJECTIVE_ITEM:

                                if (l_I.RequiredID > 0)
                                {
                                    // l_Item.RequiredID
                                    // l_Item.RequiredAmount
                                    playerChoiceResponse.Reward->Items.emplace_back();
                                    WorldPackets::Quest::PlayerChoiceResponseRewardEntry& rewardEntry = playerChoiceResponse.Reward->Items.back();
                                    rewardEntry.Item.ItemID = l_I.RequiredID;
                                    rewardEntry.Quantity = l_I.RequiredAmount;

                                    bool l_Has = player->HasItemCount(l_I.RequiredID, l_I.RequiredAmount);
                                    if (!l_Has)
                                    {
                                        l_Good = false;
                                        ss << "|cffFF0000You don't have enough "
                                            << Item::GetItemLink(l_I.RequiredID)
                                            << "\n";
                                        //<< ", Need "
                                        //<< l_I.RequiredAmount
                                        //<< " but you only have "
                                        //<< player->GetItemCount(l_I.RequiredID)
                                        //<< ". Need "
                                        //<< l_I.RequiredAmount - player->GetItemCount(l_I.RequiredID)
                                        //<< " more\n";
                                    }
                                }
                                break;
                            case QuestObjectiveType::QUEST_OBJECTIVE_MONEY:
                                if (l_I.RequiredAmount > 0)
                                {
                                    // todo: convert this to uint64
                                    playerChoiceResponse.Reward->Money = l_I.RequiredAmount;

                                    bool l_Has = player->HasEnoughMoney((int64)l_I.RequiredAmount);
                                    if (!l_Has)
                                    {
                                        l_Good = false;
                                        ss << "|cffFF0000You don't have enough gold\n";
                                        // << l_I.RequiredAmount / 10000
                                        // << "  but you only have "
                                        // << player->GetMoney() / 10000
                                        // << ". Need "
                                        // << (l_I.RequiredAmount - player->GetMoney()) / 10000
                                        // << " more\n";
                                    }
                                }
                                break;
                            }
                    }

                    if (!l_Good)
                    {
                        playerChoiceResponse.ButtonTooltip = std::string_view(ss.str().c_str());
                        playerChoiceResponse.Flags = 5;

                        if (itr != m_PlayerItemTargets.end())
                            itr->second.LastItemUpgrade = itemUpgrade->RequiredID;
                        if (dispMsg)
                        {
                            Conversation::CreateConversation(700308, player, *player, player->GetGUID());
                        }
                    }
                    else
                    {
                        if (itr != m_PlayerItemTargets.end())
                            itr->second.LastItemUpgrade = 0;
                        playerChoiceResponse.ButtonTooltip = "|cff00FBFFItem will be upgraded into";
                    }
                }
                else
                {
                    playerChoiceResponse.Header = "Rewards";
                    //playerChoiceResponse.SubHeader = "Rewards";
                    playerChoiceResponse.SubHeader = "Awards";
                    playerChoiceResponse.Answer = "Upgrade";
                    playerChoiceResponse.ButtonTooltip = "Are you sure you want to upgrade?";
                    playerChoiceResponse.Confirmation = "Confirmation";

                    playerChoiceResponse.Reward->Items.emplace_back();
                    WorldPackets::Quest::PlayerChoiceResponseRewardEntry& l_Item = playerChoiceResponse.Reward->Items.back();

                    l_Item.Item.ItemID = itemUpgrade->ReplaceItemID ? itemUpgrade->ReplaceItemID : itemTarget->GetEntry();
                    l_Item.Quantity = itemUpgrade->ReplaceItemQuantity ? itemUpgrade->ReplaceItemQuantity : 1;
                    if (itemUpgrade->Type == ItemUpgradeType::BonusID)
                    {
                        l_Item.Item.Initialize(itemTarget);
                        //l_Item.Item.ItemBonus->Context = ItemContext::Torghast;

                        //for (int32 bonusId : *itemTarget->m_itemData->Bonuses->BonusListIDs)
                        //{
                        //    if (bonusId != itemUpgrade->RequiredID)
                        //    {
                        //        if (std::find(itemUpgrade->RemoveBonusIDList.begin(), itemUpgrade->RemoveBonusIDList.end(), bonusId) == itemUpgrade->RemoveBonusIDList.end())
                        //            l_Item.Item.ItemBonus->BonusListIDs.push_back(bonusId);
                        //    }
                        //}

                        for (int32 bonusId : itemUpgrade->ReplaceBonusIDList)
                            l_Item.Item.ItemBonus->BonusListIDs.push_back(bonusId);
                    }

                    if (!l_Good)
                    {
                        playerChoiceResponse.Flags = 5;
                        playerChoiceResponse.ButtonTooltip = "You don't have the required materials!";
                    }
                }
                displayPlayerChoice.Responses.push_back(playerChoiceResponse);
            }


            OnItemQuestQueryResponse(player, itemTarget);
            OnQueryTreasurePicker(player, itemTarget);
            player->GetSession()->SendPacket(displayPlayerChoice.Write());
            player->PlayerTalkClass->GetInteractionData().Reset();
            player->PlayerTalkClass->GetInteractionData().PlayerChoiceId = 682925852;
        }

        bool BuildPackets(Player* player, Item* item, SpellCastTargets const& targets)
        {

            auto itemUpgrade = sItemUpgrader->GetItemUpgrade(targets.GetItemTarget());
            if (!itemUpgrade)
            {
                ChatHandler(player->GetSession()).PSendSysMessage("%s |cffFF0000is not upgradeable.|R", targets.GetItemTarget()->GetTemplate()->GetName(LocaleConstant::LOCALE_enUS));

                if (player->GetQuestStatus(700002) == QUEST_STATUS_INCOMPLETE)
                {
                    auto l_Creature = player->FindNearestCreature(700003, 30.0f);
                    if (!l_Creature)
                        l_Creature = player->FindNearestCreature(700010, 30.0f);
                    if (l_Creature && l_Creature->AI())
                    {
                        l_Creature->AI()->Talk(1, player);
                    }
                }

                return false;
            }

            auto itemTarget = targets.GetItemTarget();

            if (player->GetQuestStatus(700002) == QUEST_STATUS_INCOMPLETE)
            {
                auto l_Creature = player->FindNearestCreature(700003, 30.0f);
                if (!l_Creature)
                    l_Creature = player->FindNearestCreature(700010, 30.0f);
                if (l_Creature && l_Creature->AI())
                {
                    l_Creature->AI()->Talk(2, player);
                }
            }

            DisplayItemUpgrade(player, itemTarget, itemUpgrade, HasMaterialsForItemUpgrade(player, itemTarget, itemUpgrade));
            return true;
        }

        bool HasMaterialsForItemUpgrade(Player* player, Item* item, ItemUpgrade const* itemUpgrade)
        {
            for (auto const& l_I : itemUpgrade->RequiredMaterials)
            {
                switch (l_I.Type)
                {
                case QuestObjectiveType::QUEST_OBJECTIVE_CURRENCY:

                    if (l_I.RequiredID > 0)
                    {
                        bool l_Has = player->HasCurrency(l_I.RequiredID, l_I.RequiredAmount);
                        if (!l_Has)
                        {
                            return false;
                        }
                    }

                    break;
                case QuestObjectiveType::QUEST_OBJECTIVE_ITEM:

                    if (l_I.RequiredID > 0)
                    {
                        bool l_Has = player->HasItemCount(l_I.RequiredID, l_I.RequiredAmount);
                        if (!l_Has)
                        {
                            return false;
                        }
                    }
                    break;
                case QuestObjectiveType::QUEST_OBJECTIVE_MONEY:
                    if (l_I.RequiredAmount > 0)
                    {
                        bool l_Has = player->HasEnoughMoney((int64)l_I.RequiredAmount);
                        if (!l_Has)
                        {
                            return false;
                        }
                    }
                    break;
                }
            }

            return true;
        }

        bool OnQueryTreasurePicker(Player* p_Player, Item* p_Item) override
        {
            /*auto l_Itr = m_PlayerItemTargets.find(p_Player->GetGUID());
            if (l_Itr == m_PlayerItemTargets.end())
                return true;

            auto l_ItemTarget = p_Player->GetItemByGuid(l_Itr->second.ItemGuid);
            if (!l_ItemTarget)
                return true;

            auto l_ItemUpgrade = sItemUpgrader->GetItemUpgrade(l_ItemTarget);
            if (!l_ItemUpgrade)
                return true;

            WorldPackets::Quest::TreasurePickerResponse l_Packet2;

            l_Packet2.QuestID = 591918;
            l_Packet2.TreasurePickerID = l_ItemTarget->GetEntry();

            WorldPackets::Quest::TreasurePickItem l_Item;
            l_Item.Item.ItemID = l_ItemUpgrade->ReplaceItemID ? l_ItemUpgrade->ReplaceItemID : l_ItemTarget->GetEntry();
            l_Item.Quantity = l_ItemUpgrade->ReplaceItemQuantity ? l_ItemUpgrade->ReplaceItemQuantity : 1;
            if (l_ItemUpgrade->Type == ItemUpgradeType::BonusID)
            {
                l_Item.Item.Initialize(l_ItemTarget);
                //l_Item.Item.ItemBonus->Context = ItemContext::Torghast;

                if (!l_Item.Item.ItemBonus.has_value())
                    l_Item.Item.ItemBonus.emplace();

                l_Item.Item.ItemBonus->BonusListIDs.clear();

                for (int32 bonusId : l_ItemUpgrade->ReplaceBonusIDList)
                    l_Item.Item.ItemBonus->BonusListIDs.push_back(bonusId);

                for (int32 bonusId : l_ItemTarget->m_itemData->Bonuses->BonusListIDs)
                {
                    if (bonusId != l_ItemUpgrade->RequiredID)
                    {
                        if (std::find(l_ItemUpgrade->RemoveBonusIDList.begin(), l_ItemUpgrade->RemoveBonusIDList.end(), bonusId) == l_ItemUpgrade->RemoveBonusIDList.end())
                            l_Item.Item.ItemBonus->BonusListIDs.push_back(bonusId);
                    }
                }
            }


            l_Item.Quantity = 1;
            l_Packet2.Items.push_back(l_Item);

            p_Player->GetSession()->SendPacket(l_Packet2.Write());
            return true;
            */

            return true;
        }

        bool OnItemQuestQueryResponse(Player* p_Player, Item* p_Item) override
        {
            auto l_Itr = m_PlayerItemTargets.find(p_Player->GetGUID());
            if (l_Itr == m_PlayerItemTargets.end())
                return true;

            auto l_ItemTarget = p_Player->GetItemByGuid(l_Itr->second.ItemGuid);
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
            response.Info.PortraitGiverText = "";
            response.Info.PortraitGiverName = "";
            response.Info.PortraitTurnInText = "";
            response.Info.PortraitTurnInName = "";

            response.Info.QuestID = 591918;
            response.Info.TreasurePickerID = l_ItemTarget->GetEntry();

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
                response.Info.Objectives[i].ObjectID = i + 100;
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

        bool OnItemPlayerChoiceResponse(Player* p_Player, Item* p_Item) override
        {
            auto l_Itr = m_PlayerItemTargets.find(p_Player->GetGUID());
            if (l_Itr == m_PlayerItemTargets.end())
                return true;

            auto l_ItemTarget = p_Player->GetItemByGuid(l_Itr->second.ItemGuid);
            if (!l_ItemTarget)
                return true;

            auto itemUpgrade = sItemUpgrader->GetItemUpgrade(l_ItemTarget);
            if (!itemUpgrade)
                return true;

            bool l_Good = true;

            for (auto const& l_I : itemUpgrade->RequiredMaterials)
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
            
            for (auto const& l_I : itemUpgrade->RequiredMaterials)
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

            if (p_Player->GetQuestStatus(700002) == QUEST_STATUS_INCOMPLETE)
                p_Player->KilledMonsterCredit(700003);

            if (itemUpgrade->ReplaceItemID > 0)
            {
                uint32 l_Count = 1;
                p_Player->DestroyItemCount(l_ItemTarget, l_Count, true);
                if (!p_Player->AddItem(itemUpgrade->ReplaceItemID, itemUpgrade->ReplaceItemQuantity))
                    p_Player->SendItemRetrievalMail(itemUpgrade->ReplaceItemID, itemUpgrade->ReplaceItemQuantity, ItemContext::NONE);
                else
                {
                    // todo: display this someday :)
                    ///if (auto nextUpgrade = sItemUpgrader->GetItemUpgrade(l_ItemTarget))
                    ///    if (auto nextItemUpgrade = HasMaterialsForItemUpgrade(p_Player, l_ItemTarget, nextUpgrade))
                    ///        DisplayItemUpgrade(p_Player, l_ItemTarget, nextUpgrade);
                }

                ChatHandler(p_Player->GetSession()).PSendSysMessage("|cff00FF00Success");
            }
            else
            {
                //if (!itemUpgrade->ReplaceBonusIDList.empty())
                {
                    WorldPackets::Item::ItemChanged packet;
                    packet.PlayerGUID = p_Player->GetGUID();
                    packet.Before.Initialize(l_ItemTarget);

                    if (l_ItemTarget->IsEquipped())
                        p_Player->_ApplyItemMods(l_ItemTarget, l_ItemTarget->GetSlot(), false);

                    l_ItemTarget->RemoveBonus(itemUpgrade->RequiredID);

                    for (auto bonus : itemUpgrade->ReplaceBonusIDList)
                        l_ItemTarget->AddBonusesToFront(bonus, false);

                    for (auto bonus : itemUpgrade->RemoveBonusIDList)
                        l_ItemTarget->RemoveBonus(bonus);

                    packet.After.Initialize(l_ItemTarget);
                    p_Player->SendDirectMessage(packet.Write());

                    //p_Player->SendNewItem(l_ItemTarget, 1, true, false, true);
                    l_ItemTarget->SetState(ItemUpdateState::ITEM_CHANGED, p_Player);

                    if (l_ItemTarget->IsEquipped())
                        p_Player->_ApplyItemMods(l_ItemTarget, l_ItemTarget->GetSlot(), true);
                }

                l_ItemTarget->SetState(ITEM_CHANGED, p_Player);
                if (l_ItemTarget->GetSlot() < EQUIPMENT_SLOT_END)
                    p_Player->SetVisibleItemSlot(l_ItemTarget->GetSlot(), l_ItemTarget);
                l_ItemTarget->SetNotRefundable(p_Player);
                l_ItemTarget->ClearSoulboundTradeable(p_Player);
                p_Player->GetSession()->GetCollectionMgr()->AddItemAppearance(l_ItemTarget);
                ChatHandler(p_Player->GetSession()).PSendSysMessage("|cff00FF00Success");

                if (auto nextUpgrade = sItemUpgrader->GetItemUpgrade(l_ItemTarget))
                   // if (auto nextItemUpgrade = HasMaterialsForItemUpgrade(p_Player, l_ItemTarget, nextUpgrade))
                        DisplayItemUpgrade(p_Player, l_ItemTarget, nextUpgrade, HasMaterialsForItemUpgrade(p_Player, l_ItemTarget, nextUpgrade));
            }

            return true;
        }
};

void AddSC_item_upgrader()
{
    sItemUpgrader->LoadFromDB();
    new item_upgrader();
}
