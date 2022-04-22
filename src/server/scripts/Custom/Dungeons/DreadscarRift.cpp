#include "ScriptMgr.h"
#include "../CustomInstanceScript.h"

struct instance_dreadscarrift : public CustomInstanceScript
{
public:
    instance_dreadscarrift(InstanceMap* map) : CustomInstanceScript(map)
    {
    }
};

void AddSC_DreadscarRift()
{
    RegisterInstanceScript(instance_dreadscarrift, 1107);
}
