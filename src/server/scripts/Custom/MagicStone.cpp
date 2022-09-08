#include "MagicStone.h"
#include "ConditionMgr.h"
#include "ScriptMgr.h"
#include "Player.h"
#include "Creature.h"
#include "Item.h"
#include "GossipDef.h"
#include "ScriptedGossip.h"
#include "DatabaseEnv.h"
#include "Chat.h"
#include "ObjectMgr.h"
#include "MoveSpline.h"
#include "MoveSplineInit.h"
#include "CovenantMgr.h"
#include "CovenantPackets.h"

void MagicStoneMgr::LoadFromDB()
{
    m_MagicStoneMenus.clear();
    m_MagicStoneActions.clear();
    m_MagicStoneMenuTexts.clear();

    QueryResult result = WorldDatabase.Query("SELECT MenuID, `Text`, ExtraText, ActionID, GossipOptionNpc, ConditionID FROM z_magicstone_menus ORDER by ordering;");
    if (result)
    {
        do
        {
            Field* fields = result->Fetch();

            uint32 MenuID = fields[0].GetUInt32();

            MagicStoneMenu l_Menu;

            l_Menu.Text = fields[1].GetString();
            l_Menu.ExtraText = fields[2].GetString();
            l_Menu.ActionID = fields[3].GetUInt32();
            l_Menu.Icon = static_cast<GossipOptionNpc>(fields[4].GetUInt32());
            l_Menu.ConditionID = fields[5].GetUInt32();

            m_MagicStoneMenus.insert({ MenuID, l_Menu });

        } while (result->NextRow());
    }
    result = WorldDatabase.Query("SELECT MenuID, NPCTextId FROM z_magicstone_menu_texts;");
    if (result)
    {
        do
        {
            Field* fields = result->Fetch();

            uint32 MenuID = fields[0].GetUInt32();

            m_MagicStoneMenuTexts[MenuID] = fields[1].GetUInt32();

        } while (result->NextRow());
    }
    result = WorldDatabase.Query("SELECT ActionID, ActionType, Param1, Param2, Param3, Param4, Param5, ConditionID FROM z_magicstone_actions ORDER by ordering;");
    if (result)
    {
        do
        {
            Field* fields = result->Fetch();

            uint32 ActionID = fields[0].GetUInt32();

            MagicStoneAction l_Action;

            l_Action.ActionType = static_cast<ActionTypes>(fields[1].GetUInt32());
            l_Action.Params[0] = fields[2].GetUInt32();
            l_Action.Params[1] = fields[3].GetUInt32();
            l_Action.Params[2] = fields[4].GetUInt32();
            l_Action.Params[3] = fields[5].GetUInt32();
            l_Action.Params[4] = fields[6].GetUInt32();
            l_Action.ConditionID = fields[7].GetUInt32();


            m_MagicStoneActions.insert({ ActionID , l_Action });

        } while (result->NextRow());
    }
}

class MagicStone : public ItemScript
{
    public:
        MagicStone() : ItemScript("MagicStone") { }

        void DisplayMenu(Player* player, Item* item, uint32 menuId)
        {
            if ((player->IsSplineEnabled() && !player->movespline->Finalized()) || player->HasUnitState(UnitState::UNIT_STATE_STUNNED) || player->IsInCombat())
            {
                CloseGossipMenuFor(player);
                return;
            }

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
            // Remove rez sick
            player->RemoveAurasDueToSpell(15007);

            SendGossipMenuFor(player, l_NpcTextId, item->GetGUID());
        }

        bool OnUse(Player* player, Item* item, SpellCastTargets const& /*targets*/, ObjectGuid /*castId*/) override
        {
            DisplayMenu(player, item, 0);
            return true;
        }

        void OnGossipSelect(Player* player, Item* item, uint32 /*sender*/, uint32 action) override
        {
            if ((player->IsSplineEnabled() && !player->movespline->Finalized()) || player->HasUnitState(UnitState::UNIT_STATE_STUNNED) || player->IsInCombat())
            {
                CloseGossipMenuFor(player);
                return;
            }

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

                        if (tele->mapId != player->GetMapId() || player->GetDistance2d(tele->position_x, tele->position_y) >= 200.0f)
                        {
                            player->CastSpell(player, 367044, true);
                            player->GetScheduler().Schedule(800ms, 700000, [tele](TaskContext context)
                            {
                                auto player = GetContextPlayer();
                                if (!player->IsBeingTeleported())
                                {
                                    if ((player->IsSplineEnabled() && !player->movespline->Finalized()) || player->HasUnitState(UnitState::UNIT_STATE_STUNNED) || player->IsInCombat())
                                        return;

                                    player->TeleportTo(tele->mapId, tele->position_x, tele->position_y, tele->position_z, tele->orientation);
                                }
                            });
                        }
                        else
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
                    case ActionTypes::OpenForge:
                    {
                        CloseGossipMenuFor(player);
                        if (auto covenant = player->GetCovenant())
                            if (covenant->GetCovenantID() != CovenantID::None)
                            {
                                auto guid = ObjectGuid::Create<HighGuid::GameObject>(player->GetMap()->GetId(), 375677, 9999999999);
                                player->SendDirectMessage(WorldPackets::Covenant::OpenItemForge(guid).Write());
                            }
                        break;
                    }
                    case ActionTypes::SetCovenant:
                    {
                        CloseGossipMenuFor(player);
                        l_ShouldClose = false;
                        player->SendPlayerChoice(player->GetGUID(), 644);
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
