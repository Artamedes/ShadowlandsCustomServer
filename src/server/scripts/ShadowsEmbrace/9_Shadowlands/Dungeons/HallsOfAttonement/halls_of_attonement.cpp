#include "halls_of_attonement.h"

// 165515 - npc_depraved_darkblade_165515
struct npc_depraved_darkblade_165515 : public BaseCustomScriptedAI
{
public:
    npc_depraved_darkblade_165515(Creature* creature) : BaseCustomScriptedAI(creature) { }

    void InitializeAI() override
    {
        if (me->GetSpawnId() == 459047)
        {
            me->GetMotionMaster()->MovePoint(1, { -2205.5278, 5069.771, 4140.6597 }, MOVE_PATHFINDING | MOVE_RUN_MODE)->callbackFunc = [this]
            {
                me->SetEmoteState(Emote::EMOTE_STATE_READY2H);
            };
        }
        else if (me->GetSpawnId() == 459050)
        {
            me->GetMotionMaster()->MovePoint(1, { -2212.448, 5069.567, 4140.6597 }, MOVE_PATHFINDING | MOVE_RUN_MODE)->callbackFunc = [this]
            {
                me->SetEmoteState(Emote::EMOTE_STATE_READY2H);
            };
        }
    }

    void JustEngagedWith(Unit* /*who*/) override
    {
        scheduler.Schedule(5s, 10s, [this](TaskContext context)
        {
            DoCastVictim(325523); ///< deadly thrust
            context.Repeat(15s, 20s);
        });
    }
};

// 164562 - npc_depraved_houndmaster_164562
struct npc_depraved_houndmaster_164562 : public BaseCustomCasterAI
{
public:
    npc_depraved_houndmaster_164562(Creature* creature) : BaseCustomCasterAI(creature, 325535)
    {
        creature->Variables.Set("NoSmoothWP", true);
    }

    void JustEngagedWith(Unit* /*who*/) override
    {
        scheduler.Schedule(10s, [this](TaskContext context)
        {
            DoCastVictim(325793);
            context.Repeat(25s);
        });
    }

    bool phased = false;

    void DamageTaken(Unit* /*doneBy*/, uint32& damage, DamageEffectType /*damageType*/, SpellInfo const* /*spellInfo = nullptr*/) override
    {
        if (!phased && me->HealthBelowPctDamaged(51, damage))
        {
            phased = true;
            scheduler.Schedule(1s, [this](TaskContext context)
            {
                DoCast(326450);
            });
        }
    }
};

// 165414 - npc_depraved_obliterator_165414
struct npc_depraved_obliterator_165414 : public BaseCustomCasterAI
{
public:
    npc_depraved_obliterator_165414(Creature* creature) : BaseCustomCasterAI(creature, 338003) { }

    void JustEngagedWith(Unit* /*who*/) override
    {
        scheduler.Schedule(5s, [this](TaskContext context)
        {
            if (auto randTarget = SelectTarget(SelectTargetMethod::Random, 0, 20.0f, true))
                DoCast(randTarget, 325876);
            context.Repeat(20s);
        });
    }
};

// 165529 - npc_depraved_collector_165529
struct npc_depraved_collector_165529 : public BaseCustomScriptedAI
{
public:
    npc_depraved_collector_165529(Creature* creature) : BaseCustomScriptedAI(creature) { }

    void UpdateAI(uint32 diff) override
    {
        BaseCustomScriptedAI::UpdateAI(diff);

        if (!me->IsEngaged() && !me->isDead() && !me->GetCurrentSpell(CurrentSpellTypes::CURRENT_CHANNELED_SPELL))
        {
            switch (me->GetSpawnId())
            {
                case 459059:
                case 459122:
                case 459114:
                    if (auto halkias = me->FindNearestCreature(164557, 5.0f))
                        DoCast(halkias, 322476);
                    break;
            }
        }
    }

    void JustEngagedWith(Unit* /*who*/) override
    {
        scheduler.Schedule(5s, [this](TaskContext context)
        {
            if (auto randTarget = SelectTarget(SelectTargetMethod::Random, 0, 20.0f, true))
                DoCast(randTarget, 325700);
            context.Repeat(20s);
        });

        scheduler.Schedule(10s, [this](TaskContext context)
        {
            if (auto randTarget = SelectTarget(SelectTargetMethod::Random, 0, 20.0f, true))
                DoCast(randTarget, 325701);
            context.Repeat(20s);
        });
    }
};


void AddSC_halls_of_attonement()
{
    RegisterCreatureAI(npc_depraved_darkblade_165515);
    RegisterCreatureAI(npc_depraved_houndmaster_164562);
    RegisterCreatureAI(npc_depraved_obliterator_165414);
}
