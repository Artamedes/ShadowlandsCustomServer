#include "halls_of_attonement.h"

using namespace HallsOfAttonement;

struct instance_halls_of_attonement : public CustomInstanceScript
{
public:
    instance_halls_of_attonement(InstanceMap* map) : CustomInstanceScript(map)
    {
        SetBossNumber(MaxBosses);
    }
};

void AddSC_instance_halls_of_attonement()
{
    RegisterInstanceScript(instance_halls_of_attonement, 2287);
}
