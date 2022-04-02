#include "ScriptMgr.h"
#include "Player.h"
#include "ScriptedCreature.h"

struct npc_occularus_trigger_spawner : public ScriptedAI
{
    public:
        npc_occularus_trigger_spawner(Creature* creature) : ScriptedAI(creature) { }
};

void AddSC_Occularus()
{
    RegisterCreatureAI(npc_occularus_trigger_spawner);
}
