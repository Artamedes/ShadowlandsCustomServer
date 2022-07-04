#include "halls_of_attonement.h"

enum eTalks
{
    TalkAggro = 0,
    TalkSpectralProcession,
    TalkVolleyOfPower,
    TalkDeath,
};

enum eActions
{
    ActionRemoveAnimaVessel = 1,
};

enum eSpells
{
    AnimaFountain      = 329340,
    BoltOfPower        = 323538,
    VolleyOfPower      = 323552,
    SpectralProcession = 323743,
};

// 165410
struct boss_high_adjudicator_aleez : public BossAI
{
public:
    boss_high_adjudicator_aleez(Creature* creature) : BossAI(creature, HallsOfAttonement::BossHighAdjusterAleez)
    {
        ApplyAllImmunities(true);
        me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_INTERRUPT, false);
    }

    void JustEngagedWith(Unit* who) override
    {
        _JustEngagedWith(who);

        if (instance)
            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);

        Talk(TalkAggro);

        scheduler.Schedule(5s, [this](TaskContext context)
        {
            DoCastVictim(BoltOfPower);
            context.Repeat(15s);
        });

        scheduler.Schedule(7s, [this](TaskContext context)
        {
            DoCastVictim(VolleyOfPower);
            context.Repeat(15s);
        });

        scheduler.Schedule(7s, [this](TaskContext context)
        {
            Talk(TalkSpectralProcession);
            DoCastVictim(SpectralProcession);
            context.Repeat(15s);
        });

        scheduler.Schedule(30s, [this](TaskContext context)
        {
            DoCastSelf(AnimaFountain);
            context.Repeat(30s);
        });
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

        Talk(TalkDeath);
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

// 166034 - npc_empty_anima_vessel_166034
struct npc_empty_anima_vessel_166034 : public ScriptedAI
{
public:
    npc_empty_anima_vessel_166034(Creature* creature) : ScriptedAI(creature)
    {
        SetCombatMovement(false);
    }

    void DoAction(int32 action) override
    {
        if (action == ActionRemoveAnimaVessel)
        {
            me->HandleEmoteCommand(Emote::EMOTE_ONESHOT_OPEN);

            scheduler.Schedule(300ms, [this](TaskContext context)
            {
                me->SetEmoteState(Emote::EMOTE_STATE_OPENED);
            });
        }
    }

    void UpdateAI(uint32 diff) override
    {
        scheduler.Update(diff);
    }

    TaskScheduler scheduler;
};

/// ID: 329340 Anima Fountain
class spell_anima_fountain : public AuraScript
{
    PrepareAuraScript(spell_anima_fountain);

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
        auto caster = GetCaster();
        if (!caster)
            return;

        std::list<Unit*> enemies;
        caster->GetAttackableUnitListInRange(enemies, 30.0f);
        enemies.remove_if([caster](Unit* who)
        {
            return !who->IsPlayer() || !who->IsWithinLOSInMap(caster);
        });

        if (!enemies.empty())
            caster->CastSpell(Trinity::Containers::SelectRandomContainerElement(enemies), 327473, true);
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_anima_fountain::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

void AddSC_boss_high_adjudicator_aleez()
{
    RegisterCreatureAI(boss_high_adjudicator_aleez);
    RegisterCreatureAI(npc_empty_anima_vessel_166034);
    RegisterSpellScript(spell_anima_fountain);
}
