#pragma once

#include "CustomInstanceScript.h"

namespace HallsOfAttonement
{
    enum eDatas
    {
        BossHalkias,
        BossEchelon,
        BossHighAdjusterAleez,
        BossLordChamberlain,
        MaxBosses = BossLordChamberlain,
    };

    enum eGameObjects
    {
        HalkiasDoor1 = 349936,
        HalkiasDoor2 = 349931,

        EchelonEntrance1 = 353178,
        EchelonDoor = 353179,
        EheclonInvisibleDoor = 355591,

        AleezDoor1 = 355592,
        AleezDoor2 = 355593,

        LordChamberlainDoor = 353180,
    };

    enum eNpcs
    {
        NpcHalkias           = 165408,
        NpcEchelon           = 164185,
        NpcHighAdjusterAleez = 165410,
        NpcLordChamberlain   = 164218,
    };
}
