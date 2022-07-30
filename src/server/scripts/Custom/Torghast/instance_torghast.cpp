#include "TorghastDefines.h"

using namespace Torghast;

struct instance_torghast : public InstanceScript
{
public:
    instance_torghast(InstanceMap* map) : InstanceScript(map) { }

    void OnPlayerEnter(Player* player) override
    {
        player->SetJailerTowerLevel(5);
        player->SetJailerTowerLevelMax(5);

        player->CastSpell(player, eLightParams::UpperReaches, true);
    }

    void OnPlayerLeave(Player* player) override
    {
        player->SetJailerTowerLevel(0);
        player->SetJailerTowerLevelMax(0);
    }
};

void AddSC_instance_torghast()
{
    RegisterInstanceScript(instance_torghast, 2162);
}
