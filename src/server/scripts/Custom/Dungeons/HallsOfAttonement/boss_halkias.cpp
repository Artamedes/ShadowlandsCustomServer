#include "halls_of_attonement.h"

struct boss_halkias : public BossAI
{
public:
    boss_halkias(Creature* creature) : BossAI(creature, HallsOfAttonement::BossHalkias)
    {
        ApplyAllImmunities(true);
    }

    void JustEngagedWith(Unit* who) override
    {
        _JustEngagedWith(who);

        if (instance)
            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
    }

    void EnterEvadeMode(EvadeReason why) override
    {
        _EnterEvadeMode(why);
        _DespawnAtEvade(10s);

        if (instance)
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
    }

    void JustDied(Unit* who) override
    {
        _JustDied();

        if (instance)
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        scheduler.Update(diff);

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        DoMeleeAttackIfReady();
    }
};

void AddSC_boss_halkias()
{
    RegisterCreatureAI(boss_halkias);
}
