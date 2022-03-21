#pragma once
#include "ScriptMgr.h"
#include "Player.h"
#include "Creature.h"
#include "Item.h"
#include "GossipDef.h"
#include "ScriptedGossip.h"
#include "DatabaseEnv.h"
#include "Chat.h"
#include "ObjectMgr.h"

struct MagicStoneMenu
{
    GossipOptionIcon Icon;
    std::string Text;
    std::string ExtraText;
    uint32 ActionID;
    uint32 ConditionID;
};

enum class ActionTypes
{
    None = 0,
    Menu = 1,
    Teleport = 2,
    CastSpell = 3,
    CloseMenu = 4,
    MonsterCredit = 5,
    SetHomebind = 6,
};

struct MagicStoneAction
{
    ActionTypes ActionType;
    uint32 Params[5];
    uint32 ConditionID;
};

class MagicStoneMgr
{
    public:
        MagicStoneMgr() { }

        static MagicStoneMgr* instance()
        {
            static MagicStoneMgr instance;
            return &instance;
        }

        void LoadFromDB()
        {
            m_MagicStoneMenus.clear();
            m_MagicStoneActions.clear();
            m_MagicStoneMenuTexts.clear();

            QueryResult result = WorldDatabase.Query("SELECT MenuID, `Text`, ExtraText, ActionID, GossipOptionIcon, ConditionID FROM z_magicstone_menus ORDER by ordering;");
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
                    l_Menu.Icon = static_cast<GossipOptionIcon>(fields[4].GetUInt32());
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


                    m_MagicStoneActions.insert({ ActionID , l_Action});

                } while (result->NextRow());
            }
        }

        std::multimap<uint32, MagicStoneMenu> m_MagicStoneMenus;
        std::multimap<uint32, MagicStoneAction> m_MagicStoneActions;
        std::unordered_map<uint32, uint32> m_MagicStoneMenuTexts;
};

#define sMagicStoneMgr MagicStoneMgr::instance()

