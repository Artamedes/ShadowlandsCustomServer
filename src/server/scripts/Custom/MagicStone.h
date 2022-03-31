#pragma once

enum class GossipOptionIcon : int8;

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

        void LoadFromDB();

        std::multimap<uint32, MagicStoneMenu> m_MagicStoneMenus;
        std::multimap<uint32, MagicStoneAction> m_MagicStoneActions;
        std::unordered_map<uint32, uint32> m_MagicStoneMenuTexts;
};

#define sMagicStoneMgr MagicStoneMgr::instance()

