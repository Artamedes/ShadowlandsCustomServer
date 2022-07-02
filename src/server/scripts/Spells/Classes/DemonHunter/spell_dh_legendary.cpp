#include "spell_dh.h"

/***********************************************************
 * Shadowlands Demon Hunter legendaries progress
 * ========================================
 * General ================================
 * ========================================
 * Collective Anguish - Still interrupts eyebeam's channel. Need to debug why. Already implemented SPELL_ATTR12_ALLOW_DURING_SPELL_OVERRIDE
 * Darkest Hour - Not Implemented
 * Darkglare Medallion - Not Implemented
 * Blazing Slaughter - Not Implemented
 * Agony Gaze - Not Implemented
 * Blind Faith - Not Implemented
 * Demonic Oath - Not Implemented
 * Fel Bombardment - Not Implemented
 * ========================================
 * HAVOC ==================================
 * ========================================
 * Darker Nature - Not Implemented
 * Chaos Theory - Implemented
 * Erratic Fel Core - Should be handled by SPELL_AURA_CHARGE_RECOVERY_MULTIPLIER
 * Burning Wound - Not Implemented
 * ========================================
 * Vengeance ==============================
 * ========================================
 * Spirit of Darkness Flame - Not Implemented
 * Razelikh's Defilement - Not Implemented
 * Fel Flame Fortification - Not Implemented
 * Fiery Soul - Not Implemented
 **********************************************************/

using namespace DH;

/// ID: 337504 Collective Anguish
class spell_collective_anguish : public AuraScript
{
    PrepareAuraScript(spell_collective_anguish);

    enum eCollectiveAnguish
    {
        CollectiveEyeBeam = 346504,
        CollectiveFelDev = 346502,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetSpellInfo())
            return false;

        return eventInfo.GetSpellInfo()->Id == EyeBeam || eventInfo.GetSpellInfo()->Id == FelDevstation;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        auto caster = GetCaster();
        if (!caster)
            return;

        if (IsSpec(caster, SimpleTalentSpecs::Havoc))
            caster->CastSpell(caster, CollectiveFelDev, CastSpellExtraArgs(TRIGGERED_FULL_MASK | TRIGGERED_IGNORE_CAST_IN_PROGRESS));
        else
            caster->CastSpell(caster, CollectiveEyeBeam, CastSpellExtraArgs(TRIGGERED_FULL_MASK | TRIGGERED_IGNORE_CAST_IN_PROGRESS));
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_collective_anguish::CheckProc);
        OnProc += AuraProcFn(spell_collective_anguish::HandleProc);
    }
};

/// ID: 346504 Eye Beam
class spell_eye_beam_collective_anguish : public AuraScript
{
    PrepareAuraScript(spell_eye_beam_collective_anguish);

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
        auto caster = GetCaster();
        if (!caster)
            return;

        caster->CastSpell(caster, 346505, true);
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_eye_beam_collective_anguish::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
    }
};

/// ID: 337551 Chaos Theory
class spell_chaos_theory : public AuraScript
{
    PrepareAuraScript(spell_chaos_theory);

    enum eChaosTheory
    {
        ChaoticBlades = 337567,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetSpellInfo())
            return false;

        return eventInfo.GetSpellInfo()->Id == BladeDanceDmg || eventInfo.GetSpellInfo()->Id == DeathSweepDmg;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        auto caster = GetCaster();
        if (!caster)
            return;

        caster->CastSpell(caster, ChaoticBlades, true);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_chaos_theory::CheckProc);
        OnProc += AuraProcFn(spell_chaos_theory::HandleProc);
    }
};

/// ID: 346279 Burning Wound
class spell_burning_wound : public AuraScript
{
    PrepareAuraScript(spell_burning_wound);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetSpellInfo())
            return false;

        switch (eventInfo.GetSpellInfo()->Id)
        {
            case DemonBladesDmg:
            case Felblade:
            case DemonsBite:
                return true;
        }

        return false;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();
        auto caster = GetCaster();
        auto target = eventInfo.GetActionTarget();
        if (!caster || !target)
            return;

        caster->CastSpell(target, 346278, true);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_burning_wound::CheckProc);
        OnProc += AuraProcFn(spell_burning_wound::HandleProc);
    }
};

void AddSC_spell_dh_legendary()
{
    RegisterSpellScript(spell_collective_anguish);
    RegisterSpellScript(spell_eye_beam_collective_anguish);
    RegisterSpellScript(spell_chaos_theory);
    RegisterSpellScript(spell_burning_wound);
}
