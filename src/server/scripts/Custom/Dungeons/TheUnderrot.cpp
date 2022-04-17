#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "../CustomInstanceScript.h"

struct instance_the_underrot : public CustomInstanceScript
{
public:
    instance_the_underrot(InstanceMap* map) : CustomInstanceScript(map)
    {
    }
};

void AddSC_TheUnderrot()
{
    RegisterInstanceScript(instance_the_underrot, 1841);
}
