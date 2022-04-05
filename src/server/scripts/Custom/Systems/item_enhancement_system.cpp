#include "GossipDef.h"
#include "ScriptMgr.h"
#include "ScriptedGossip.h"
#include "Chat.h"
#include "Item.h"
#include "WorldSession.h"
#include "SpellPackets.h"
#include "Spell.h"

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

            // Allowing everything to be enhanced.
            //switch (item->GetEntry())
            //{
            //    case 46017:
            //    case 32838:
            //    case 32837:
            //    case 19019:
            //    case 49623:
            //    case 71352:
            //    case 71086:
            //    case 77949:
            //    case 77950:
            //    case 186414:
            //        break;
            //    default:
            //    {
            //        ChatHandler(player).SendSysMessage("|cffFF0000You can't enhance that item.");
            //        return true;
            //    }
            //}
            if (item->HasBonusId(BonusIDAward))
            {
                ChatHandler(player).PSendSysMessage("|cffFF0000You can't enhance that item with %s anymore.", Item::GetItemLink(upgrader->GetEntry()).c_str());
                return true;
            }

            std::ostringstream ss;

            ss << "Are you sure you want to enhance " << Item::GetItemLink(item->GetEntry()) << " with " << Item::GetItemLink(upgrader->GetEntry()) << "?\n\n|cffFF0000This will consume this enhancement permanently!";

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

            // Consume the scroll
            if (!itemTarget->HasBonusId(BonusIDAward))
            {
                player->DestroyItem(item->GetBagSlot(), item->GetSlot(), true);
                if (itemTarget->IsEquipped())
                    player->_ApplyItemMods(itemTarget, itemTarget->GetSlot(), false);
                itemTarget->AddBonuses(BonusIDAward);
                if (itemTarget->IsEquipped())
                    player->_ApplyItemMods(itemTarget, itemTarget->GetSlot(), true);
                ChatHandler(player).PSendSysMessage("|cff00FF00Succesfully enhanced %s!", Item::GetItemLink(itemTarget->GetEntry()).c_str());
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
                default:
                    OnGossipHello(player);
                    break;
            }
            return true;
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
    RegisterCreatureAI(npc_mother_700013);
}
