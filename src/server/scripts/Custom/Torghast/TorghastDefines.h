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
        DefenderOfTorghast = 311180,
    };

    /// Per Floor Lights
    namespace eLightParams
    {
        enum : uint32
        {
            SkoldusHall         = 325755,
            FractureChambers    = 325759,
            Soulforges          = 325760,
            ColdheartInterstia  = 325761,
            Mortregar           = 325762,
            UpperReaches        = 325766,
            Lobby               = 333183,
            AdamantVaults       = 357642,
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
        enum JailerTower: uint32
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
            EmpoweredFlameforgeEnforcer       = 168001,
            EmpoweredMawswornShackler         = 168002,
            EmpoweredColdheartAscendant       = 168003,
            EmpoweredImperialConsular         = 168004,
            EmpoweredDeadsoulShambler         = 168005,
            EmpoweredMawswornSoulbinder       = 168007,
            EmpoweredColdheartAgent           = 168098,
            EmpoweredColdheartJavelineer      = 168099,
            EmpoweredDeadsoulShade            = 168101,
            EmpoweredDeadsoulEcho             = 168102,
            EmpoweredFlameforgeMaster         = 168104,
            EmpoweredMawswornFlametender      = 168105,
            EmpoweredMawswornGuard            = 168106,
            EmpoweredMawswornInterceptor      = 168107,
            EmpoweredLumberingCreation        = 168108,
            EmpoweredMawswornRitualist        = 168109,
            EmpoweredImperialDuelist          = 168110,
            EmpoweredImperialCurator          = 168111,
            EmpoweredBroker                   = 174791,
            EmpoweredRavager                  = 177187,
            EmpoweredMawswornSoulwarden       = 178957,
            EmpoweredMawswornWoebringer       = 178964,
            EmpoweredMawswornCremator         = 179080,
            EmpoweredRavager2                 = 180318,
            EmpoweredMawswornGuard2           = 181941,
            EmpoweredGuardian                 = 183947,
            EmpoweredWorldbreaker             = 183985,
            EmpoweredAttendant                = 183988,
            NextFloor                         = 156480,
        };
    }

    enum eDatas : uint32
    {
        GotoNextFloor = 1,
    };

    void SendAnimaPowerChoiceToPlayer(Player* player);
}
