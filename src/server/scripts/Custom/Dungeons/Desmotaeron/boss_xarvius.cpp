#include "Desmotaeron.h"

enum eXarvius
{
    ChargerSummonText = 0,
    EngageText = 1,
};

// 707009
struct boss_xarvius : public BossAI
{
public:
    boss_xarvius(Creature* creature) : BossAI(creature, BossXarvius) { }

    void InitializeAI()
    {
        me->SetReactState(REACT_PASSIVE);
        me->SetUnitFlag(UNIT_FLAG_NON_ATTACKABLE);
        me->AddUnitState(UNIT_STATE_IGNORE_PATHFINDING);
    }

    void JustEngagedWith(Unit* who) override
    {
        _JustEngagedWith(who);

        Talk(EngageText);

        DoCastSelf(RainOfDespair);

        scheduler.Schedule(10s, 20s, [this](TaskContext context)
        {

        });
    }

    void UpdateAI(uint32 diff)
    {
        if (!UpdateVictim())
            return;

        scheduler.Update(diff);
        events.Update(diff);

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        while (uint32 eventId = events.ExecuteEvent())
        {
            ExecuteEvent(eventId);
            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;
        }

        DoMeleeAttackIfReady();
    }

    bool didIntro = false;

    void MoveInLineOfSight(Unit* who) override
    {
        BossAI::MoveInLineOfSight(who);

        if (!didIntro)
        {
            Talk(ChargerSummonText);
            didIntro = true;
            DoSummon(707023, { 4653.7f, 5849.3f, 4857.77f, 0.0190654f }, 0s, TEMPSUMMON_DEAD_DESPAWN);
            return;
        }
    }

    void EnterEvadeMode(EvadeReason why) override
    {
        summons.DespawnAll();
        BossAI::EnterEvadeMode(why);
        _DespawnAtEvade(3s);
    }
};

struct npc_charger_of_the_damned : public ScriptedAI
{
public:
    npc_charger_of_the_damned(Creature* creature) : ScriptedAI(creature) { }

    void InitializeAI()
    {
        me->SetReactState(REACT_PASSIVE);
        me->SetUnitFlag(UNIT_FLAG_NON_ATTACKABLE);
        me->GetMotionMaster()->MovePoint(1, { 4698.62f, 5856.69f, 4867.97f, 6.17266f })->callbackFunc = [this]
        {
            if (auto xarvius = me->FindNearestCreature(707009, 10.0f))
            {
                xarvius->CastSpell(me, 46598, true);
                xarvius->GetScheduler().Schedule(1100ms, [this, xarvius](TaskContext context)
                {
                    xarvius->RemoveAurasDueToSpell(46598);
                    me->DespawnOrUnsummon();
                    xarvius->Mount(98542, 0u, 0u);
                    xarvius->SetReactState(REACT_AGGRESSIVE);
                    xarvius->RemoveUnitFlag(UNIT_FLAG_NON_ATTACKABLE);
                });
            }
        };
    }
};

enum eSpiritHarvester
{
    HarvestSoul = 357085,
    GloomBolt = 364240,
};

// 707025 - npc_spirit_harvester_707025
struct npc_spirit_harvester_707025 : public BaseCustomCasterAI
{
public:
    npc_spirit_harvester_707025(Creature* creature) : BaseCustomCasterAI(creature, GloomBolt) { }

    void JustEngagedWith(Unit* who) override
    {
        scheduler.Schedule(1s, 10s, [this](TaskContext context)
        {
            DoCastVictim(HarvestSoul);
            context.Repeat(20s);
        });
    }

    void DamageDealt(Unit* victim, uint32& damage, DamageEffectType type, SpellInfo const* spellInfo /*= nullptr*/) override
    {
        if (spellInfo && victim)
        {
            switch (spellInfo->Id)
            {
                case 360259: ///< Gloom bolt
                    damage += 70000;
                    break;
                case HarvestSoul:
                    damage += 150000;
                    break;
            }
        }
    }
};

// 707024 - npc_mawsworn_axeguard_707024
struct npc_mawsworn_axeguard_707024 : public BaseCustomScriptedAI
{
public:
    npc_mawsworn_axeguard_707024(Creature* creature) : BaseCustomScriptedAI(creature) { }

    void JustEngagedWith(Unit* who) override
    {
        scheduler.Schedule(5s, [this](TaskContext context)
        {
            DoCastSelf(AccursedStrength);
            context.Repeat(20s);
        });
        scheduler.Schedule(6s, [this](TaskContext context)
        {
            DoCastSelf(MassiveStrike);
            context.Repeat(20s);
        });
    }

    void DamageDealt(Unit* victim, uint32& damage, DamageEffectType type, SpellInfo const* spellInfo /*= nullptr*/) override
    {
        if (spellInfo && victim)
        {
            switch (spellInfo->Id)
            {
                case MassiveStrike:
                    damage += 700000;
                    break;
            }
        }
    }
};
// 707022 - npc_spirit_shepherd_707022
struct npc_spirit_shepherd_707022 : public BaseCustomCasterAI
{
public:
    npc_spirit_shepherd_707022(Creature* creature) : BaseCustomCasterAI(creature, DominationBolt) { }

    void DamageDealt(Unit* victim, uint32& damage, DamageEffectType type, SpellInfo const* spellInfo /*= nullptr*/) override
    {
        if (spellInfo && victim)
        {
            switch (spellInfo->Id)
            {
                case DominationBolt:
                    damage += 75000;
                    break;
            }
        }
    }
};

void AddSC_boss_xarvius()
{
    RegisterCreatureAI(boss_xarvius);
    RegisterCreatureAI(npc_charger_of_the_damned);
    RegisterCreatureAI(npc_spirit_harvester_707025);
    RegisterCreatureAI(npc_mawsworn_axeguard_707024);
    RegisterCreatureAI(npc_spirit_shepherd_707022);
}
