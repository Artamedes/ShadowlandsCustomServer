#include "halls_of_attonement.h"
#include "AreaBoundary.h"

using namespace HallsOfAttonement;

DoorData const doorData[] =
{
    { HalkiasDoor1,          BossHalkias,                  DOOR_TYPE_PASSAGE },
    { HalkiasDoor2,          BossHalkias,                  DOOR_TYPE_PASSAGE },
    { EchelonEntrance1,      BossEchelon,                  DOOR_TYPE_ROOM    },
    { EchelonDoor,           BossEchelon,                  DOOR_TYPE_PASSAGE },
    { EheclonInvisibleDoor,  BossEchelon,                  DOOR_TYPE_PASSAGE },
    { AleezDoor1,            BossHighAdjusterAleez,        DOOR_TYPE_ROOM    },
    { AleezDoor2,            BossHighAdjusterAleez,        DOOR_TYPE_ROOM    },
    { LordChamberlainDoor,   BossLordChamberlain,          DOOR_TYPE_ROOM    },
    { 0,                    0,                             DOOR_TYPE_ROOM    } // END
};

ObjectData const creatureData[] =
{
    { NpcHalkias          ,  BossHalkias                  },
    { NpcEchelon          ,  BossEchelon                  },
    { NpcHighAdjusterAleez,  BossHighAdjusterAleez        },
    { NpcLordChamberlain  ,  BossLordChamberlain          },
    { 0,                   0                    } // END
};

ObjectData const gameobjectData[] =
{
    { 0,                  0                    } // END
};

BossBoundaryData const boundaries =
{
    { BossEchelon, new CircleBoundary(Position({ -2209.27f, 5480.29f, 4170.29f, 4.87498f }), 33.0f) },
    { BossHighAdjusterAleez, new CircleBoundary(Position(550.6178f, 253.5917f), 26.0f) },
    { BossLordChamberlain, new ZRangeBoundary(666.0f, 776.0f) },
};

struct instance_halls_of_attonement : public CustomInstanceScript
{
public:
    instance_halls_of_attonement(InstanceMap* map) : CustomInstanceScript(map)
    {
        SetBossNumber(MaxBosses);
        LoadDoorData(doorData);
        LoadObjectData(creatureData, gameobjectData);
        LoadBossBoundaries(boundaries);
    }
};

void AddSC_instance_halls_of_attonement()
{
    RegisterInstanceScript(instance_halls_of_attonement, 2287);
}
