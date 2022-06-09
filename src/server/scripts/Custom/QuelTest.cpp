#include "ScriptMgr.h"
#include "ScriptedCreature.h"

enum DreadscarRift
{
    TestDummy,

    NpcTestConduit = 802002,
};

const Position TestConduitPos = { 3452.24f, 1554.11f, 436.707f, 3.18628f };

struct npc_live_dummy : ScriptedAI
{
public:
	npc_live_dummy(Creature* creature) : ScriptedAI(creature) {}

    bool conduitUp = true;

    void DamageTaken(Unit* attacker, uint32& damage, DamageEffectType /*damageType*/, SpellInfo const* /*spellInfo = nullptr*/) override
    {
        if (damage >= me->GetHealth())
        {
            damage = 0;

            me->SetHealth(me->CountPctFromMaxHealth(50));
        }
    }

    Position const DummyStartPos = {4267.54f, -2805.66f, 5.26688f, 5.40941f};

    void EnterEvadeMode(EvadeReason why) override
    {
        conduitUp = true;
        me->GetMotionMaster()->MovePoint(1, { 3452.24f, 1554.11f, 436.707f, 3.18628f });
        me->SetHealth(me->CountPctFromMaxHealth(100));
    }


};

struct npc_test_conduit : public ScriptedAI
{
public:
    npc_test_conduit(Creature* creature) : ScriptedAI(creature) { }

    void InitializeAI() override
    {
        SetCombatMovement(false);
        me->SetReactState(REACT_PASSIVE);
    }

    void UpdateAI(uint32 diff) override
    {
        if (me->isDead())
            return;

        if (auto livedummy = me->FindNearestCreature(802003, 100.0f))
            DoCast(livedummy, 353401); // ID - 353401 Eye of the Jailer Channel
    }

    void JustDied(Unit* unit) override
    {
        if (auto livedummy = me->FindNearestCreature(802003, 100.0f))
            livedummy->KillSelf();
    }

    void Reset() override
    {

    }
};

void AddSC_QuelTest()
{
	RegisterCreatureAI(npc_live_dummy);
    RegisterCreatureAI(npc_test_conduit);
}
