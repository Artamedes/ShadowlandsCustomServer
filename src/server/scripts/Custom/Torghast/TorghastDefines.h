#pragma once

#include "Torghast/AnimaPower.h"
#include "CustomInstanceScript.h"
#include "GameObjectAI.h"

namespace Torghast
{
    enum eSpells : uint32
    {
        CarryingChest = 295730,
        CreateChest = 295729,

        CarryingChestHoard = 326785,
        CreateChestHoard   = 326785,

        NextFloorBlackout = 295040,

        RunicDomination = 355752, ///< Activates Shards of Domination
        MawOverrideSpellPowerByAP, ///< Cast on Melee Classes as blizz does

        TheJailersChains = 338906, ///< PRevents Equipment/talent swapping - Needs to be scripted
        SoulSaverProc = 324720, ///< Unsure but has proc flags of taken positive spell hit, taken magic spell dmg, or looted smthing
        Visuals = 338943, ///< Casted by 173236
        Timer = 170724, ///< Casted by 173236 - has SPELL_AURA_PERIODIC_DUMMY, not sure what it's for, maybe spawning tarrague?
    };

    /// Per Floor Lights
    namespace eLightParams
    {
        enum : uint32
        {
            SkoldusHall = 325755,
            FractureChambers = 325759,
            Soulforges = 325760,
            ColdheartInterstia = 325761,
            Mortregar = 325762,
            UpperReaches = 325766,
            Lobby = 333183,
            AdamantVaults = 357642,
        };
    }

    enum eCurrencies
    {
        Phantasma      = 1728,
        TowerKnowledge = 1904,
    };

    enum eRarityColors : uint32
    {
        Common   = 0xFFFFFFFF,
        Uncommon = 0xFF1EFF00,
        Rare     = 0xFF0070DD,
        Epic     = 0xFFA335EE,
    };

    enum eWorldStates
    {
        NextFloor    = 19143,
        CurrentFloor = 19812,
        TorghastLevel = 19811,
        TorghastType = 19207
    };

    namespace JailersTowerType
    {
        enum : uint32
        {
            TwistingCorridors = 0,
            SkoldusHalls,
            FractureChambers,
            Soulforges,
            Coldheart,
            Mortregar,
            UpperReaches,
            ArkobanHall,
            TormentChamberJaina,
            TormentChamberThrall,
            TormentChamberAnduin,
            AdamantVaults,
            ForgottenCatacombs,
            Ossuary,
            BossRush,
        };
    }

    namespace NpcEntries
    {
        enum : uint32
        {

        };
    }

    enum eDatas : uint32
    {
        GotoNextFloor = 1,
    };

    void SendAnimaPowerChoiceToPlayer(Player* player);
}
