#include "ScriptMgr.h"
#include "../CustomInstanceScript.h"

class instance_skyhold : public InstanceMapScript
{
    public:
        instance_skyhold() : InstanceMapScript("instance_skyhold", 2472) { }

        struct instance_skyhold_InstanceMapScript : public CustomInstanceScript
        {
            public:
                instance_skyhold_InstanceMapScript(InstanceMap* map) : CustomInstanceScript(map)
                {
                }
        };

        InstanceScript* GetInstanceScript(InstanceMap* map) const override
        {
            return new instance_skyhold_InstanceMapScript(map);
        }
};


void AddSC_Skyhold()
{
    new instance_skyhold();
}
