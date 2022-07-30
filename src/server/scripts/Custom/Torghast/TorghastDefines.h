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
    };

    /// Per Floor Lights
    enum eLightParams
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
    };

    void SendAnimaPowerChoiceToPlayer(Player* player);
}
