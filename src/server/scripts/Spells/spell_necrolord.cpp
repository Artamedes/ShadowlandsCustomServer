#include "SpellMgr.h"
#include "Unit.h"
#include "SpellScript.h"
#include "SpellAuras.h"
#include "SpellAuraEffects.h"
#include "SpellHistory.h"

// 324631 
class spell_necrolord_fleshcraft : public AuraScript
{
    PrepareAuraScript(spell_necrolord_fleshcraft);

    enum Fleshcraft
    {
        FleshcraftAura = 324867,
        UltimateForm = 323095,
    };

    int32 amount = 0;

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
        Unit* target = GetTarget();
        if (!target)
            return;

        auto aura = target->GetAura(FleshcraftAura);
        if (!aura)
            aura = target->AddAura(FleshcraftAura);

        if (aura)
        {
            auto effect = aura->GetEffect(0);
            if (effect)
            {
                amount += target->GetMaxHealth() * 0.0666666666667;
                effect->SetAmount(amount);
                aura->SetNeedClientUpdateForTargets();
            }
        }
    }

    void HandleApply(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /* mode */)
    {
        if (GetCaster() && !GetCaster()->HasAura(UltimateForm))
            PreventDefaultAction();
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_necrolord_fleshcraft::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
        OnEffectApply += AuraEffectApplyFn(spell_necrolord_fleshcraft::HandleApply, EFFECT_2, SPELL_AURA_LINKED_2, AURA_EFFECT_HANDLE_REAL);
    }
};

// not needed
class spell_necrolord_fleshcraft_spellscript : public SpellScript
{
    PrepareSpellScript(spell_necrolord_fleshcraft_spellscript);

    enum Fleshcraft
    {
        FleshcraftAura = 324867,
        UltimateForm = 323095,
    };

    void HandleUltimateForm(SpellEffIndex eff)
    {
        if (GetCaster() && !GetCaster()->HasAura(UltimateForm))
            PreventHitEffect(eff);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_necrolord_fleshcraft_spellscript::HandleUltimateForm, EFFECT_2, SPELL_EFFECT_APPLY_AURA);
    }
};

/// ID - 323089 Travel with Bloop
class spell_travel_with_bloop : public AuraScript
{
    PrepareAuraScript(spell_travel_with_bloop);

    enum TravelWithBloop
    {
        SpeedSpell    = 323399,
        StackingSpell = 323396,
    };

    void HandlePeriodic(AuraEffect const* effect)
    {
        Unit* caster = GetCaster();
        if (!caster)
            return;

        if (caster->HasAura(SpeedSpell))
            return;

        if (!caster->isMoving())
        {
            bool grantSpeed = false;
            Aura* stackAura = caster->GetAura(StackingSpell);
            if (stackAura)
            {
                if (stackAura->GetStackAmount() >= 4)
                {
                    grantSpeed = true;
                }
            }

            caster->CastSpell(caster, StackingSpell, true);

            if (grantSpeed && stackAura)
            {
                stackAura->Remove();
                caster->CastSpell(caster, SpeedSpell, true);
            }
        }
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_travel_with_bloop::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
    }
};
/// ID: 323916 Sulfuric Emission
class spell_sulfuric_emission : public AuraScript
{
    PrepareAuraScript(spell_sulfuric_emission);

    enum SulfuricEmission
    {
        SulfuricEmissionFear = 324263,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetActor())
            return false;

        return !eventInfo.GetActionTarget()->GetSpellHistory()->HasCooldown(SulfuricEmissionFear);
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();
        if (!eventInfo.GetActor())
            return;

        eventInfo.GetActor()->GetSpellHistory()->AddCooldown(SulfuricEmissionFear, 0, 60s);
        eventInfo.GetActor()->CastSpell(eventInfo.GetActor(), SulfuricEmissionFear, true);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_sulfuric_emission::CheckProc);
        OnProc += AuraProcFn(spell_sulfuric_emission::HandleProc);
    }
};

void AddSC_spell_necrolord()
{
    RegisterSpellAndAuraScriptPairWithArgs(spell_necrolord_fleshcraft_spellscript, spell_necrolord_fleshcraft, "spell_necrolord_fleshcraft");
    RegisterSpellScript(spell_travel_with_bloop);
    RegisterSpellScript(spell_sulfuric_emission);
}
