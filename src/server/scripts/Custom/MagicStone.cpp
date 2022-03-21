#include "MagicStone.h"
#include "ConditionMgr.h"

class MagicStone : public ItemScript
{
    public:
        MagicStone() : ItemScript("MagicStone") { }

        void DisplayMenu(Player* player, Item* item, uint32 menuId)
        {
            ClearGossipMenuFor(player);

            auto l_Itr = sMagicStoneMgr->m_MagicStoneMenus.equal_range(menuId);

            for (auto l_I = l_Itr.first; l_I != l_Itr.second; ++l_I)
            {
                auto l_Menu = &l_I->second;

                if (!sConditionMgr->IsObjectMeetingNotGroupedConditions(ConditionSourceType::CONDITION_SOURCE_TYPE_MAGIC_STONE_MENU, l_I->second.ConditionID, player))
                    continue;

                if (l_Menu->ExtraText.empty())
                    AddGossipItemFor(player, l_Menu->Icon, l_Menu->Text, 0, l_Menu->ActionID);
                else
                    AddGossipItemFor(player, l_Menu->Icon, l_Menu->Text, 0, l_Menu->ActionID, l_Menu->ExtraText, 0, false);
            }

            auto l_NpcTextId = 1;
            auto l_Itr1 = sMagicStoneMgr->m_MagicStoneMenuTexts.find(menuId);
            if (l_Itr1 != sMagicStoneMgr->m_MagicStoneMenuTexts.end())
                l_NpcTextId = l_Itr1->second;

            SendGossipMenuFor(player, l_NpcTextId, item->GetGUID());
        }

        bool OnUse(Player* player, Item* item, SpellCastTargets const& /*targets*/, ObjectGuid /*castId*/) override
        {
            DisplayMenu(player, item, 0);
            return true;
        }

        void OnGossipSelect(Player* player, Item* item, uint32 sender, uint32 action) override
        {
            ClearGossipMenuFor(player);
            bool l_ShouldClose = true;

            auto l_Itr = sMagicStoneMgr->m_MagicStoneActions.equal_range(action);
            for (auto l_I = l_Itr.first; l_I != l_Itr.second; ++l_I)
            {
                if (l_I->second.ConditionID > 0)
                {
                    if (!sConditionMgr->IsObjectMeetingNotGroupedConditions(ConditionSourceType::CONDITION_SOURCE_TYPE_MAGIC_STONE_ACTION, l_I->second.ConditionID, player))
                        continue;
                }

                switch (l_I->second.ActionType)
                {
                    case ActionTypes::Menu:
                        DisplayMenu(player, item, l_I->second.Params[0]);
                        l_ShouldClose = false;
                        break;
                    case ActionTypes::Teleport:
                    {
                        GameTele const* tele = sObjectMgr->GetGameTele(l_I->second.Params[0]);
                        if (!tele)
                        {
                            ChatHandler(player).PSendSysMessage("Broken teleport %u in MagicStone!", l_I->second.Params[0]);
                            continue;
                        }

                        player->TeleportTo(tele->mapId, tele->position_x, tele->position_y, tele->position_z, tele->orientation);
                        break;
                    }
                    case ActionTypes::CastSpell:
                    {
                        player->CastSpell(player, l_I->second.Params[0], true);
                        break;
                    }
                    case ActionTypes::CloseMenu:
                        CloseGossipMenuFor(player);
                        l_ShouldClose = false;
                        break;
                    case ActionTypes::MonsterCredit:
                        player->KilledMonsterCredit(l_I->second.Params[0]);
                        break;

                    case ActionTypes::SetHomebind:
                    {
                        GameTele const* tele = sObjectMgr->GetGameTele(l_I->second.Params[0]);
                        if (!tele)
                        {
                            ChatHandler(player).PSendSysMessage("Broken teleport %u in MagicStone!", l_I->second.Params[0]);
                            continue;
                        }

                        player->SetHomebind(WorldLocation(tele->mapId, tele->position_x, tele->position_y, tele->position_z, tele->orientation), 6719);
                        break;
                    }
                }
            }

            if (l_ShouldClose)
                CloseGossipMenuFor(player);

        }
};

void AddSC_MagicStone()
{
    sMagicStoneMgr->LoadFromDB();
    new MagicStone();
}
