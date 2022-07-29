#pragma once

#include "AnimaPower.h"
#include "CustomInstanceScript.h"
#include "GameObjectAI.h"

namespace Torghast
{
    enum eGameObjects : uint32
    {
        PlunderedAnima = 325740,
    };

    enum eSpells : uint32
    {
        CarryingChest = 295730,
        CreateChest = 295729,
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
