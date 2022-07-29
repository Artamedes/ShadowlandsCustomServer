#pragma once

#include "Common.h"
#include <map>

class Player;

enum class eMawPowerRarity
{
    Any      = 0,
    Common   = 1,
    Uncommon = 2,
    Rare     = 3,
    Epic     = 4,
};

struct MawPowerDB
{
    uint32 MawPowerID;
    uint32 ClassID;
    eMawPowerRarity RarityID;
    uint32 CovenantID;
    uint32 RequiredFloor;
    uint32 RequiredNpc;
};

class TC_GAME_API TorghastMgr
{
public:
    static TorghastMgr* instance()
    {
        static TorghastMgr instance;
        return &instance;
    }

    ~TorghastMgr();

    void LoadFromDB();
    void ChooseMawPower(Player* player, std::vector<MawPowerDB*>& powers, uint32 amount = 3, eMawPowerRarity rarity = eMawPowerRarity::Any, uint32 RequiredNpc = 0, bool classOnly = false);

private:
    std::vector<MawPowerDB*> _mawPowersDB;
    std::unordered_multimap<uint32, MawPowerDB*> _mawPowersByNpcEntry;
    std::unordered_multimap<uint32, MawPowerDB*> _mawPowersByCovenant;
    std::unordered_multimap<uint32, MawPowerDB*> _mawPowersByClass;
    std::unordered_multimap<eMawPowerRarity, MawPowerDB*> _mawPowersByRarity;
};

#define sTorghastMgr TorghastMgr::instance()
