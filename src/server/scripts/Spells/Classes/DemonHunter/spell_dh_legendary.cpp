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
 * Agony Gaze - Implemented
 * Blind Faith - Not Implemented
 * Demonic Oath - Not Implemented
 * Fel Bombardment - Not Implemented
 * ========================================
 * HAVOC ==================================
 * ========================================
 * Darker Nature - Not Implemented
 * Chaos Theory - Implemented
 * Erratic Fel Core - Should be handled by SPELL_AURA_CHARGE_RECOVERY_MULTIPLIER
 * Burning Wound - Done
 * ========================================
 * Vengeance ==============================
 * ========================================
 * Spirit of Darkness Flame - Implemented
 * Razelikh's Defilement - Implemented
 * Fel Flame Fortification - Implemented
 * Fiery Soul - Implemented
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

/// ID: 337541 Spirit of the Darkness Flame
class spell_spirit_of_the_darkness_flame : public AuraScript
{
    PrepareAuraScript(spell_spirit_of_the_darkness_flame);

    enum eSpiritOfTheDarknessFlame
    {
        HealPeriodic = 337543,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == FieryBrand && eventInfo.GetDamageInfo();
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        auto caster = GetCaster();
        if (!caster)
            return;

        if (!eventInfo.GetDamageInfo())
            return;

        caster->CastSpell(caster, HealPeriodic, CastSpellExtraArgs(true).AddSpellBP0(eventInfo.GetDamageInfo()->GetDamage()));
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_spirit_of_the_darkness_flame::CheckProc);
        OnProc += AuraProcFn(spell_spirit_of_the_darkness_flame::HandleProc);
    }
};

/// ID: 337542 Spirit of the Darkness Flame
class spell_spirit_of_the_darkness_flame_proc : public AuraScript
{
    PrepareAuraScript(spell_spirit_of_the_darkness_flame_proc);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == FieryBrand;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        Remove();
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_spirit_of_the_darkness_flame_proc::CheckProc);
        OnProc += AuraProcFn(spell_spirit_of_the_darkness_flame_proc::HandleProc);
    }
};

/// ID: 337544 Razelikh's Defilement
class spell_razelikhs_defilement : public AuraScript
{
    PrepareAuraScript(spell_razelikhs_defilement);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == SoulCleave;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        auto caster = GetCaster();
        if (!caster)
            return;

        std::vector<uint32> spells;

        spells.emplace_back(SigilOfFlame);
        spells.emplace_back(SigilOfMisery);
        spells.emplace_back(SigilOfSilence);
        spells.emplace_back(ElysianDecree);
        spells.emplace_back(SigilOfChains);

        Trinity::Containers::RandomShuffle(spells);

        size_t spellsToCheck = spells.size();

        while (spellsToCheck > 0)
        {
            uint32 spellId = spells[spellsToCheck];

            if (caster->GetSpellHistory()->HasCooldown(spellId))
            {
                caster->GetSpellHistory()->ModifyCooldown(spellId, spellId == ElysianDecree ? -2000 : -8000);
                break;
            }

            --spellsToCheck;
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_razelikhs_defilement::CheckProc);
        OnProc += AuraProcFn(spell_razelikhs_defilement::HandleProc);
    }
};

/// ID: 355886 Agony Gaze
class spell_agony_gaze : public AuraScript
{
    PrepareAuraScript(spell_agony_gaze);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && (eventInfo.GetSpellInfo()->Id == EyeBeamDmg || eventInfo.GetSpellInfo()->Id == FelDevstationDmg || eventInfo.GetSpellInfo()->Id == 346505 || eventInfo.GetSpellInfo()->Id == 346503);
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto procTarget = eventInfo.GetProcTarget())
        {
            if (auto caster = GetCaster())
            {
                if (auto sinfulBrand = procTarget->GetAura(SinfulBrand, caster->GetGUID()))
                {
                    if (sinfulBrand->GetDuration() <= 16000)
                        sinfulBrand->ModDuration(750);
                }
            }
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_agony_gaze::CheckProc);
        OnProc += AuraProcFn(spell_agony_gaze::HandleProc);
    }
};

void AddSC_spell_dh_legendary()
{
    RegisterSpellScript(spell_collective_anguish);
    RegisterSpellScript(spell_eye_beam_collective_anguish);
    RegisterSpellScript(spell_chaos_theory);
    RegisterSpellScript(spell_burning_wound);
    RegisterSpellScript(spell_spirit_of_the_darkness_flame);
    RegisterSpellScript(spell_spirit_of_the_darkness_flame_proc);
    RegisterSpellScript(spell_razelikhs_defilement);
}
