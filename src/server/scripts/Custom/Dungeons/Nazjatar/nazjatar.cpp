#include "MoveSpline.h"
#include "nazjatar.h"

enum eNazjatar
{
    Shadowdelving = 301168,
};

// 154074 - npc_void_orb_154074
struct npc_void_orb_154074 : public ScriptedAI
{
public:
    npc_void_orb_154074(Creature* creature) : ScriptedAI(creature)
    {
        me->SetUnitFlag(UnitFlags::UNIT_FLAG_UNINTERACTIBLE);
    }

    void UpdateAI(uint32 diff) override
    {
        //if (me->HasAura(Shadowdelving) && me->movespline->Finalized())
        //{
        //    float x, y, z;
        //    me->GetPosition(x, y, z);
        //    me->GetMotionMaster()->MoveCirclePath(x, y, z, frand(0.3f, 0.6f), false, 2);
        //}
    }
};

// 154990 - npc_hand_of_darkness_154990
struct npc_hand_of_darkness_154990 : public BaseCustomScriptedAI
{
public:
    npc_hand_of_darkness_154990(Creature* creature) : BaseCustomScriptedAI(creature)
    {
        SetCombatMovement(false);
    }

    enum eHandOfDarkness
    {
        SpewIchor = 304800,
    };

    void JustEngagedWith(Unit* /*who*/) override
    {
        scheduler.Schedule(1s, [this](TaskContext context)
        {
            DoCast(SpewIchor);
            context.Repeat(10s);
        });
    }
};

/// ID: 304804 Spew Ichor
class spell_spew_ichor : public SpellScript
{
    PrepareSpellScript(spell_spew_ichor);

    void HandleDummy(SpellEffIndex /*eff*/)
    {
        auto caster = GetCaster();
        if (!caster)
            return;

        std::list<Unit*> enemies;
        caster->GetAttackableUnitListInRange(enemies, 30.0f);

        for (auto enemy : enemies)
        {
            if (enemy->IsPlayer())
                caster->CastSpell(*enemy, 304806, true); ///< Spew ichor
        }
    }

    void Register() override
    {
        OnEffectLaunch += SpellEffectFn(spell_spew_ichor::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

// 145333 - npc_shirakess_apprentice_145333
struct npc_shirakess_apprentice_145333 : public BaseCustomCasterAI
{
public:
    npc_shirakess_apprentice_145333(Creature* creature) : BaseCustomCasterAI(creature, 303504) { } ///< Void Bolt

    void Reset() override
    {
        switch (me->GetSpawnId())
        {
            case 155355:
            case 155521:
            case 155538:
            case 155543:
            case 155557:
            case 155610:
            case 145333:
            case 155442:
            case 155504:
            case 155506:
            case 155510:
            case 155639:
                DoCast(237594);
                break;
            default:
                DoCast(301168);
                break;
        }
    }
};

// 152827 - npc_shirakess_voidreaver_152827
struct npc_shirakess_voidreaver_152827 : public BaseCustomScriptedAI
{
public:
    npc_shirakess_voidreaver_152827(Creature* creature) : BaseCustomScriptedAI(creature) { }

    void JustEngagedWith(Unit* /*who*/) override
    {
        DoCastSelf(303604); ///< hasten the end

        scheduler.Schedule(5s, [this](TaskContext context)
        {
            DoCastVictim(303611); ///< Soulcleave
            context.Repeat(15s, 20s);
        });
    }
};

// 149004 - npc_shirakess_overseer_149004
struct npc_shirakess_overseer_149004 : public BaseCustomCasterAI
{
public:
    npc_shirakess_overseer_149004(Creature* creature) : BaseCustomCasterAI(creature, 303504) { }

    void JustEngagedWith(Unit* /*who*/) override
    {
        scheduler.Schedule(5s, [this](TaskContext context)
        {
            DoCastVictim(303519); ///< collapsing shadows
            context.Repeat(30s, 40s);
        });
    }
};

// 152724 - npc_shirakess_subjugator_152724
struct npc_shirakess_subjugator_152724 : public BaseCustomScriptedAI
{
public:
    npc_shirakess_subjugator_152724(Creature* creature) : BaseCustomScriptedAI(creature) { }

    void JustEngagedWith(Unit* /*who*/) override
    {
        DoCastSelf(303604); ///< hasten the end
    }
};

// 152744 - npc_elder_mindbreaker_152744
struct npc_elder_mindbreaker_152744 : public BaseCustomScriptedAI
{
public:
    npc_elder_mindbreaker_152744(Creature* creature) : BaseCustomScriptedAI(creature) { }

    void InitalizeAI()
    {
        DoCastSelf(299145); ///< Shadowy Ghost Visual State, Purple
    }

    void JustEngagedWith(Unit* /*who*/) override
    {
        scheduler.Schedule(10s, [this](TaskContext context)
        {
            DoCastSelf(260237); ///< Dark shroud
            context.Repeat(30s);
        });

        scheduler.Schedule(5s, [this](TaskContext context)
        {
            DoCastVictim(303587); ///< Gift from below
            context.Repeat(30s);
        });

        scheduler.Schedule(2s, [this](TaskContext context)
        {
            DoCastVictim(303566); ///< Mind Flay
            context.Repeat(15s);
        });

        scheduler.Schedule(8s, [this](TaskContext context)
        {
            DoCastVictim(303563); ///< Void Splash
            context.Repeat(15s);
        });
    }
};

// 154992 - npc_dark_witness_154992
struct npc_dark_witness_154992 : public BaseCustomScriptedAI
{
public:
    npc_dark_witness_154992(Creature* creature) : BaseCustomScriptedAI(creature) { }

    void InitializeAI()
    {
        me->SetReactState(REACT_PASSIVE);

        scheduler.Schedule(1s, [this](TaskContext context)
        {
            DoCastSelf(301644);
            context.Repeat(12s);
        });
    }

    void UpdateAI(uint32 diff) override
    {
        scheduler.Update(diff);
    }
};

/// ID: 301644 Void Power
class spell_void_power : public AuraScript
{
    PrepareAuraScript(spell_void_power);

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
        PreventDefaultAction();

        auto caster = GetCaster();
        if (!caster)
            return;

        float x, y, z;
        caster->GetPosition(x, y, z);

        x += frand(-40.0f, 40.0f);
        y += frand(-40.0f, 40.0f);
        z = caster->GetMap()->GetWaterOrGroundLevel(caster->GetPhaseShift(), x, y, z, &z);

        caster->CastSpell(Position(x, y, z), 301643, true);
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_void_power::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
    }
};

void AddSC_nazjatar()
{
    RegisterCreatureAI(npc_void_orb_154074);
    RegisterCreatureAI(npc_hand_of_darkness_154990);
    RegisterSpellScript(spell_spew_ichor);
    RegisterCreatureAI(npc_shirakess_apprentice_145333);
    RegisterCreatureAI(npc_shirakess_voidreaver_152827);
    RegisterCreatureAI(npc_shirakess_overseer_149004);
    RegisterCreatureAI(npc_shirakess_subjugator_152724);
    RegisterCreatureAI(npc_elder_mindbreaker_152744);
    RegisterCreatureAI(npc_dark_witness_154992);
    RegisterSpellScript(spell_void_power);
}
