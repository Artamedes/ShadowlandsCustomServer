#include "SpellDefines.h"
#include "AreaTriggerAI.h"

/// ID: 361469 Living Flame
class spell_living_flame : public SpellScript
{
    PrepareSpellScript(spell_living_flame);

    enum Spells
    {
        SPELL_LIVING_FLAME_DAMAGE = 361500,
        SPELL_LIVING_FLAME_HEALING = 361509,
    };

    void HandleDummy(SpellEffIndex /*eff*/)
    {
        if (Unit* caster = GetCaster())
        {
            if (Unit* target = GetHitUnit())
            {
                if (caster->IsValidAttackTarget(target))
                    caster->CastSpell(target, SPELL_LIVING_FLAME_DAMAGE, true);
                else
                    caster->CastSpell(target, SPELL_LIVING_FLAME_HEALING, true);
            }
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_living_flame::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

struct aretrigger_emerald_blossom_27633 : AreaTriggerAI
{
    aretrigger_emerald_blossom_27633(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger) { }

    enum Spells
    {
        SPELL_EMERALD_BLOSSOM_HEAL = 355916,
    };

    void OnRegisterRemove() override
    {
        Unit* caster = at->GetOwner();
        if (!caster)
            return;

        caster->CastSpell(at->GetPosition(), SPELL_EMERALD_BLOSSOM_HEAL, true);
    }
};

// 369372 
struct aretrigger_firestorm_28714 : AreaTriggerAI
{
    aretrigger_firestorm_28714(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger) { }

    enum Spells
    {
        SPELL_FIRESTORM_DAMAGE = 369374,
    };

    void OnCreate() override
    {
        at->SetPeriodicProcTimer(1000);
    }

    void OnPeriodicProc()
    {
        Unit* caster = at->GetCaster();
        if (!caster)
            return;

        caster->CastSpell(at->GetPosition(), SPELL_FIRESTORM_DAMAGE, true);
        return;
    }
};

/// ID: 375088 Dragonrage
class spell_dragonrage : public SpellScript
{
    PrepareSpellScript(spell_dragonrage);

    enum Spells
    {
        SPELL_PYRE = 357211,
    };

    void HandleDummy(SpellEffIndex /*eff*/)
    {
        Unit* caster = GetCaster();
        if (!caster)
            return;

        if (Unit* target = GetHitUnit())
        {
            caster->CastSpell(target, SPELL_PYRE, true);
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_dragonrage::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

/// ID: 357210 Deep Breath
class spell_deep_breath : public SpellScript
{
    PrepareSpellScript(spell_deep_breath);

    enum Spells
    {
        SPELL_DEEP_BREATH_FLY = 362010,
    };

    void HandleDummy(SpellEffIndex /*eff*/)
    {
        Unit* caster = GetCaster();

        if (const WorldLocation* location = GetExplTargetDest())
        {
            Position pos = location->GetPosition();
            caster->GetScheduler().Schedule(Milliseconds(900), [this, caster, pos](TaskContext task)
                {
                    if (caster) // doesn't caster already exist when he schedules this again?
                        caster->CastSpell(pos, SPELL_DEEP_BREATH_FLY, true);
                });
        }
    }

    void Register() override
    {
        OnEffectLaunch += SpellEffectFn(spell_deep_breath::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

// 362010
class spell_deep_breath_flight : public SpellScript
{
    PrepareSpellScript(spell_deep_breath_flight);

    enum Spells
    {
        SPELL_DEEP_BREATH_CANCEL = 362019,
    };

    void HandleJumpCharge(Optional<JumpArrivalCastArgs>& arrivalCast)
    {
        auto caster = GetCaster();
        if (!caster)
            return;

        if (!arrivalCast)
        {
            arrivalCast.emplace();
            arrivalCast->Target = caster->GetGUID();
            arrivalCast->SpellId = SPELL_DEEP_BREATH_CANCEL;
        }
    }

    void Register() override
    {
        OnJumpCharge += SpellJumpChargeFn(spell_deep_breath_flight::HandleJumpCharge);
    }
};

// landslide 358385 (dummy) 355689,363800, (areatrigger)
// glide 358733
// fire breath 382266

void AddSC_evoker_spell_scripts()
{
    RegisterSpellScript(spell_living_flame);
    RegisterAreaTriggerAI(aretrigger_emerald_blossom_27633);
    RegisterAreaTriggerAI(aretrigger_firestorm_28714);
    RegisterSpellScript(spell_dragonrage);
    RegisterSpellScript(spell_deep_breath);
    RegisterSpellScript(spell_deep_breath_flight);
}

/*
DELETE FROM spell_script_names WHERE spell_id = 361469;
INSERT INTO spell_script_names(spell_id, scriptname) VALUE(361469, 'spell_living_flame');
DELETE FROM spell_script_names WHERE spell_id = 375088;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (375088, 'spell_dragonrage');
DELETE FROM spell_script_names WHERE spell_id = 357210;
INSERT INTO spell_script_names(spell_id, scriptname) VALUE(357210, 'spell_deep_breath');
DELETE FROM spell_script_names WHERE spell_id = 362010;
INSERT INTO spell_script_names(spell_id, scriptname) VALUE(362010, 'spell_deep_breath_flight');
*/
