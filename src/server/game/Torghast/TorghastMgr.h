#pragma once

#include "Common.h"
#include "EnumFlag.h"
#include <map>

class Player;

namespace Torghast
{
    namespace VenariUpgradesQuests
    {
        enum : uint32
        {
            VesselOfUnfortunateSpirits = 63202, ///< NYI Makes it so your first death in Torghast is not applied to your death counter.
            ExtradimensionalPockets    = 63183, ///< NYI Gain extra storage space while in Torghast, allowing Obleron Armaments to be found in higher amounts.
            BangleofSeniority          = 63193, ///< NYI While in Torghast, Broker vendors will have a chance to offer you Uncommon options.
            RitualPrismofFortune       = 63204, ///< While in Torghast, your chance of receiving Epic Anima Powers is permanently increased.
            LoupeofUnusualCharm        = 63201, ///< NYI While in Torghast, a Broker vendor may offer you discounted Anima Hoards.
            RankInsigniaAcquisitionist = 63200, ///< NYI While in Torghast, Broker vendors will have a chance to offer you one Rare option.
            PossibilityMatrix          = 61144, ///< Come to a better understanding of the infinite possibilities of Anima, expanding your selection of powers within Torghast. You will always see at least two choices when using an Anima Hoard.
        };
    }
}

enum class eMawPowerRarity
{
    Any      = 0,
    Common   = 1,
    Uncommon = 2,
    Rare     = 3,
    Epic     = 4,
};

enum class MawPowerFlags : uint32
{
    None     = 0x0,
    Common   = 0x1,
    Uncommon = 0x2,
    Rare     = 0x4,
    Epic     = 0x8,
};

DEFINE_ENUM_FLAG(MawPowerFlags);

struct MawPowerDB
{
    uint32 MawPowerID;
    uint32 ClassID;
    eMawPowerRarity RarityID;
    uint32 CovenantID;
    uint32 RequiredFloor;
    uint32 RequiredNpc;
    uint32 RequiredAura;
    uint32 RequiredQuest;
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
    void ChooseMawPower(Player* player, std::vector<MawPowerDB*>& powers, uint32 amount = 3, EnumFlag<MawPowerFlags> rarity = MawPowerFlags::None, uint32 RequiredNpc = 0, bool classOnly = false);

private:
    std::vector<MawPowerDB*> _mawPowersDB;
    std::unordered_multimap<uint32, MawPowerDB*> _mawPowersByNpcEntry;
    std::unordered_multimap<uint32, MawPowerDB*> _mawPowersByCovenant;
    std::unordered_multimap<uint32, MawPowerDB*> _mawPowersByClass;
    std::unordered_multimap<eMawPowerRarity, MawPowerDB*> _mawPowersByRarity;
};

#define sTorghastMgr TorghastMgr::instance()
