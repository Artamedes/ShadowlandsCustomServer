#include "SpellIncludes.h"
#include "TorghastDefines.h"

using namespace Torghast;

enum eTorghastSpells : uint32
{
    ObleronSpikes    = 294578, ///< Crit
    ObleronWinds     = 294592, ///< Haste
    ObleronTalisman  = 294597, ///< Mastery
    ObleronEphemera  = 294602, ///< Vers
    ObleronVenom     = 294609, ///< Crit Dmg and Healing
    ObleronEndurance = 293025, ///< Max Health
};

void ApplyTorghastStatBuff(Unit* caster, uint32 statBuff, uint32 basePoints)
{
    if (caster)
        caster->CastSpell(caster, statBuff, CastSpellExtraArgs(true).AddSpellMod(SpellValueMod::SPELLVALUE_AURA_STACK, basePoints));
}

/// ID: 294587 Obleron Spikes x2
class spell_obleron_spikes_x2_294587 : public SpellScript
{
    PrepareSpellScript(spell_obleron_spikes_x2_294587);

    void HandleDummy(SpellEffIndex /*eff*/)
    {
        ApplyTorghastStatBuff(GetCaster(), eTorghastSpells::ObleronSpikes, GetEffectInfo().BasePoints);
    }


    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_obleron_spikes_x2_294587::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

/// ID: 294588 Obleron Spikes x3
class spell_obleron_spikes_x3_294588 : public SpellScript
{
    PrepareSpellScript(spell_obleron_spikes_x3_294588);

    void HandleDummy(SpellEffIndex /*eff*/)
    {
        ApplyTorghastStatBuff(GetCaster(), eTorghastSpells::ObleronSpikes, GetEffectInfo().BasePoints);
    }


    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_obleron_spikes_x3_294588::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

/// ID: 294593 Obleron Winds x2
class spell_obleron_winds_x2_294593 : public SpellScript
{
    PrepareSpellScript(spell_obleron_winds_x2_294593);

    void HandleDummy(SpellEffIndex /*eff*/)
    {
        ApplyTorghastStatBuff(GetCaster(), eTorghastSpells::ObleronWinds, GetEffectInfo().BasePoints);
    }


    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_obleron_winds_x2_294593::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

/// ID: 294594 Obleron Winds x3
class spell_obleron_winds_x3_294594 : public SpellScript
{
    PrepareSpellScript(spell_obleron_winds_x3_294594);

    void HandleDummy(SpellEffIndex /*eff*/)
    {
        ApplyTorghastStatBuff(GetCaster(), eTorghastSpells::ObleronWinds, GetEffectInfo().BasePoints);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_obleron_winds_x3_294594::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

/// ID: 294600 Obleron Talisman x2
class spell_obleron_talisman_x2_294600 : public SpellScript
{
    PrepareSpellScript(spell_obleron_talisman_x2_294600);

    void HandleDummy(SpellEffIndex /*eff*/)
    {
        ApplyTorghastStatBuff(GetCaster(), eTorghastSpells::ObleronTalisman, GetEffectInfo().BasePoints);
    }


    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_obleron_talisman_x2_294600::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

/// ID: 294601 Obleron Talisman x3
class spell_obleron_talisman_x3_294601 : public SpellScript
{
    PrepareSpellScript(spell_obleron_talisman_x3_294601);

    void HandleDummy(SpellEffIndex /*eff*/)
    {
        ApplyTorghastStatBuff(GetCaster(), eTorghastSpells::ObleronTalisman, GetEffectInfo().BasePoints);
    }


    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_obleron_talisman_x3_294601::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

/// ID: 294603 Obleron Ephemera x2
class spell_obleron_ephemera_x2_294603 : public SpellScript
{
    PrepareSpellScript(spell_obleron_ephemera_x2_294603);

    void HandleDummy(SpellEffIndex /*eff*/)
    {
        ApplyTorghastStatBuff(GetCaster(), eTorghastSpells::ObleronEphemera, GetEffectInfo().BasePoints);
    }


    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_obleron_ephemera_x2_294603::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

/// ID: 294604 Obleron Ephemera x3
class spell_obleron_ephemera_x3_294604 : public SpellScript
{
    PrepareSpellScript(spell_obleron_ephemera_x3_294604);

    void HandleDummy(SpellEffIndex /*eff*/)
    {
        ApplyTorghastStatBuff(GetCaster(), eTorghastSpells::ObleronEphemera, GetEffectInfo().BasePoints);
    }


    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_obleron_ephemera_x3_294604::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

/// ID: 294610 Obleron Venom x2
class spell_obleron_venom_x2_294610 : public SpellScript
{
    PrepareSpellScript(spell_obleron_venom_x2_294610);

    void HandleDummy(SpellEffIndex /*eff*/)
    {
        ApplyTorghastStatBuff(GetCaster(), eTorghastSpells::ObleronVenom, GetEffectInfo().BasePoints);
    }


    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_obleron_venom_x2_294610::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

/// ID: 294611 Obleron Venom x3
class spell_obleron_venom_x3_294611 : public SpellScript
{
    PrepareSpellScript(spell_obleron_venom_x3_294611);

    void HandleDummy(SpellEffIndex /*eff*/)
    {
        ApplyTorghastStatBuff(GetCaster(), eTorghastSpells::ObleronVenom, GetEffectInfo().BasePoints);
    }


    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_obleron_venom_x3_294611::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

/// ID: 293026 Obleron Endurance x2
class spell_obleron_endurance_x2_293026 : public SpellScript
{
    PrepareSpellScript(spell_obleron_endurance_x2_293026);

    void HandleDummy(SpellEffIndex /*eff*/)
    {
        ApplyTorghastStatBuff(GetCaster(), eTorghastSpells::ObleronEndurance, GetEffectInfo().BasePoints);
    }


    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_obleron_endurance_x2_293026::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

/// ID: 293027 Obleron Endurance x3
class spell_obleron_endurance_x3_293027 : public SpellScript
{
    PrepareSpellScript(spell_obleron_endurance_x3_293027);

    void HandleDummy(SpellEffIndex /*eff*/)
    {
        ApplyTorghastStatBuff(GetCaster(), eTorghastSpells::ObleronEndurance, GetEffectInfo().BasePoints);
    }


    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_obleron_endurance_x3_293027::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

/// ID: 297576 Tremorbeast Tusk
class spell_tremorbeast_tusk_297576 : public AuraScript
{
    PrepareAuraScript(spell_tremorbeast_tusk_297576);

    enum eTremorbeastTusk
    {
        KnockbackSpell = 297579,
        CooldownSpell = 300318,
    };

    /// Damage should already be working from DB2
    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto caster = GetCaster())
        {
            if (auto target = eventInfo.GetProcTarget())
            {
                if (!target->HasAura(CooldownSpell, caster->GetGUID()))
                {
                    if (auto dmgInfo = eventInfo.GetDamageInfo())
                    {
                        if (_enemyDamages.find(target->GetGUID()) == _enemyDamages.end())
                            _enemyDamages[target->GetGUID()] = 0;

                        uint32& currDmg = _enemyDamages[target->GetGUID()];
                        currDmg += dmgInfo->GetDamage();
                        if (currDmg >= caster->CountPctFromMaxHealth(5))
                        {
                            currDmg = 0;
                            caster->CastSpell(target, KnockbackSpell, true);
                            caster->CastSpell(target, CooldownSpell, true);
                        }
                    }
                }
            }
        }
    }

    std::unordered_map<ObjectGuid, uint32> _enemyDamages;

    void Register() override
    {
        OnProc += AuraProcFn(spell_tremorbeast_tusk_297576::HandleProc);
    }
};

/// ID: 296141 Knowledge of Mortality
class spell_knowledge_of_mortality_296141 : public AuraScript
{
    PrepareAuraScript(spell_knowledge_of_mortality_296141);

    enum KnowledgeOfMortality
    {
        KnowMortality = 296146,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        /// Prevent proc from self.
        return !eventInfo.GetSpellInfo() || eventInfo.GetSpellInfo()->Id != KnowMortality;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_knowledge_of_mortality_296141::CheckProc);
    }
};

/// ID: 300730 Vitality Guillotine
class spell_vitality_guillotine_300730 : public AuraScript
{
    PrepareAuraScript(spell_vitality_guillotine_300730);

    enum eVitalityGuillotine
    {
        DamageSpell = 300731,
        HealthBuff = 300733,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        auto procTarget = eventInfo.GetProcTarget();

        return procTarget && procTarget->ToCreature() && procTarget->ToCreature()->GetCreatureTemplate()->rank > 0;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        --_amount;

        if (auto caster = GetCaster())
            if (auto target = eventInfo.GetProcTarget())
                caster->CastSpell(target, DamageSpell, true);

        if (_amount <= 0)
            Remove();
    }

    int32 _amount = 3;

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_vitality_guillotine_300730::CheckProc);
        OnProc += AuraProcFn(spell_vitality_guillotine_300730::HandleProc);
    }
};

/// ID: 300771 Blade of the Lifetaker
class spell_blade_of_the_lifetaker_300771 : public AuraScript
{
    PrepareAuraScript(spell_blade_of_the_lifetaker_300771);

    enum Lifetaker
    {
        BladeOfTheLifeTaker = 300772,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        /// Prevent proc from self.
        return !eventInfo.GetSpellInfo() || eventInfo.GetSpellInfo()->Id != BladeOfTheLifeTaker;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_blade_of_the_lifetaker_300771::CheckProc);
    }
};

/// ID: 297721 Subjugator's Manacles
class spell_subjugators_manacles_297721 : public AuraScript
{
    PrepareAuraScript(spell_subjugators_manacles_297721);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        auto procTarget = eventInfo.GetProcTarget();

        if (procTarget && !_attackedCreatures.count(procTarget->GetGUID()))
        {
            _attackedCreatures.insert(procTarget->GetGUID());
            return true;
        }

        return false;
    }

    GuidUnorderedSet _attackedCreatures;

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_subjugators_manacles_297721::CheckProc);
    }
};

/// ID: 299419 Flaming Lance
/// Anima Lance applies Flame Shock to enemies it strikes.
class spell_flaming_lance_299419 : public AuraScript
{
    PrepareAuraScript(spell_flaming_lance_299419);

    enum eFlamingLance
    {
        AnimaLance = 332988,
        FlameShock = 188389,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == AnimaLance;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto caster = GetCaster())
        {
            if (auto target = eventInfo.GetActionTarget())
            {
                caster->CastSpell(target, FlameShock, true);
            }
        }
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_flaming_lance_299419::CheckProc);
        OnProc += AuraProcFn(spell_flaming_lance_299419::HandleProc);
    }
};

/// ID: 296515 Mind Breach
class spell_mind_breach_296515 : public AuraScript
{
    PrepareAuraScript(spell_mind_breach_296515);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_mind_breach_296515::CheckProc);
        OnProc += AuraProcFn(spell_mind_breach_296515::HandleProc);
    }
};

/// ID: 295068 Abundance of Phantasma
class spell_abundance_of_phantasma_295068 : public AuraScript
{
    PrepareAuraScript(spell_abundance_of_phantasma_295068);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_abundance_of_phantasma_295068::CheckProc);
        OnProc += AuraProcFn(spell_abundance_of_phantasma_295068::HandleProc);
    }
};

/// ID: 294422 Bloating Fodder
/// @TODO: You cause Mawrats to explode on death, dealing $294423s1 Plague damage to all other nearby enemies.
class spell_bloating_fodder_294422 : public AuraScript
{
    PrepareAuraScript(spell_bloating_fodder_294422);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_bloating_fodder_294422::CheckProc);
        OnProc += AuraProcFn(spell_bloating_fodder_294422::HandleProc);
    }
};

/// ID: 295694 Secret Spices
class spell_secret_spices_295694 : public AuraScript
{
    PrepareAuraScript(spell_secret_spices_295694);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_secret_spices_295694::CheckProc);
        OnProc += AuraProcFn(spell_secret_spices_295694::HandleProc);
    }
};

/// ID: 295965 Curious Miasma
class spell_curious_miasma_295965 : public AuraScript
{
    PrepareAuraScript(spell_curious_miasma_295965);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        auto procTarget = eventInfo.GetProcTarget();

        if (procTarget && !_attackedCreatures.count(procTarget->GetGUID()))
        {
            _attackedCreatures.insert(procTarget->GetGUID());
            return true;
        }

        return false;
    }

    GuidUnorderedSet _attackedCreatures;

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_curious_miasma_295965::CheckProc);
    }
};

/// ID: 295969 Protective Phantasma
class spell_protective_phantasma_295969 : public AuraScript
{
    PrepareAuraScript(spell_protective_phantasma_295969);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_protective_phantasma_295969::CheckProc);
        OnProc += AuraProcFn(spell_protective_phantasma_295969::HandleProc);
    }
};

/// ID: 294887 Glutton's Kerchief
class spell_gluttons_kerchief_294887 : public AuraScript
{
    PrepareAuraScript(spell_gluttons_kerchief_294887);

    void HandlePeriodic1(AuraEffect const* /*aurEff*/)
    {
    }


    void HandlePeriodic2(AuraEffect const* /*aurEff*/)
    {
    }


    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_gluttons_kerchief_294887::HandlePeriodic1, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_gluttons_kerchief_294887::HandlePeriodic2, EFFECT_6, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
    }
};

/// ID: 298789 Astral Phantasma
class spell_astral_phantasma_298789 : public AuraScript
{
    PrepareAuraScript(spell_astral_phantasma_298789);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_astral_phantasma_298789::CheckProc);
        OnProc += AuraProcFn(spell_astral_phantasma_298789::HandleProc);
    }
};

/// ID: 298564 Might of the Worldsplitter
class spell_might_of_the_worldsplitter_298564 : public AuraScript
{
    PrepareAuraScript(spell_might_of_the_worldsplitter_298564);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_might_of_the_worldsplitter_298564::CheckProc);
        OnProc += AuraProcFn(spell_might_of_the_worldsplitter_298564::HandleProc);
    }
};

/// ID: 298576 Earthen Resonance
class spell_earthen_resonance_298576 : public AuraScript
{
    PrepareAuraScript(spell_earthen_resonance_298576);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_earthen_resonance_298576::CheckProc);
        OnProc += AuraProcFn(spell_earthen_resonance_298576::HandleProc);
    }
};

/// ID: 298685 Thermal Harmony
class spell_thermal_harmony_298685 : public AuraScript
{
    PrepareAuraScript(spell_thermal_harmony_298685);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_thermal_harmony_298685::CheckProc);
        OnProc += AuraProcFn(spell_thermal_harmony_298685::HandleProc);
    }
};

/// ID: 298891 All-Consuming Blaze
class spell_allconsuming_blaze_298891 : public AuraScript
{
    PrepareAuraScript(spell_allconsuming_blaze_298891);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_allconsuming_blaze_298891::CheckProc);
        OnProc += AuraProcFn(spell_allconsuming_blaze_298891::HandleProc);
    }
};

/// ID: 299388 Galvanizing Nimbus
class spell_galvanizing_nimbus_299388 : public AuraScript
{
    PrepareAuraScript(spell_galvanizing_nimbus_299388);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_galvanizing_nimbus_299388::CheckProc);
        OnProc += AuraProcFn(spell_galvanizing_nimbus_299388::HandleProc);
    }
};

/// ID: 298911 Molten Shock
class spell_molten_shock_298911 : public AuraScript
{
    PrepareAuraScript(spell_molten_shock_298911);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_molten_shock_298911::CheckProc);
        OnProc += AuraProcFn(spell_molten_shock_298911::HandleProc);
    }
};

/// ID: 298952 Ignan Oblation
class spell_ignan_oblation_298952 : public AuraScript
{
    PrepareAuraScript(spell_ignan_oblation_298952);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_ignan_oblation_298952::CheckProc);
        OnProc += AuraProcFn(spell_ignan_oblation_298952::HandleProc);
    }
};

/// ID: 298969 Magma Fist
class spell_magma_fist_298969 : public AuraScript
{
    PrepareAuraScript(spell_magma_fist_298969);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_magma_fist_298969::CheckProc);
        OnProc += AuraProcFn(spell_magma_fist_298969::HandleProc);
    }
};

/// ID: 300793 Open Doors
class spell_open_doors_300793 : public AuraScript
{
    PrepareAuraScript(spell_open_doors_300793);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_open_doors_300793::CheckProc);
        OnProc += AuraProcFn(spell_open_doors_300793::HandleProc);
    }
};

/// ID: 300796 Touch of the Unseen
class spell_touch_of_the_unseen_300796 : public AuraScript
{
    PrepareAuraScript(spell_touch_of_the_unseen_300796);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_touch_of_the_unseen_300796::CheckProc);
        OnProc += AuraProcFn(spell_touch_of_the_unseen_300796::HandleProc);
    }
};

/// ID: 299049 Heart of the Forge
class spell_heart_of_the_forge_299049 : public AuraScript
{
    PrepareAuraScript(spell_heart_of_the_forge_299049);

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
    }


    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_heart_of_the_forge_299049::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
    }
};

/// ID: 304992 Band of Deep Burns
class spell_band_of_deep_burns_304992 : public AuraScript
{
    PrepareAuraScript(spell_band_of_deep_burns_304992);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_band_of_deep_burns_304992::CheckProc);
        OnProc += AuraProcFn(spell_band_of_deep_burns_304992::HandleProc);
    }
};

/// ID: 304996 Frostchipper
class spell_frostchipper_304996 : public AuraScript
{
    PrepareAuraScript(spell_frostchipper_304996);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_frostchipper_304996::CheckProc);
        OnProc += AuraProcFn(spell_frostchipper_304996::HandleProc);
    }
};

/// ID: 304998 Stormcycle Peridot
class spell_stormcycle_peridot_304998 : public AuraScript
{
    PrepareAuraScript(spell_stormcycle_peridot_304998);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_stormcycle_peridot_304998::CheckProc);
        OnProc += AuraProcFn(spell_stormcycle_peridot_304998::HandleProc);
    }
};

/// ID: 305002 Shadowed Iris
class spell_shadowed_iris_305002 : public AuraScript
{
    PrepareAuraScript(spell_shadowed_iris_305002);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_shadowed_iris_305002::CheckProc);
        OnProc += AuraProcFn(spell_shadowed_iris_305002::HandleProc);
    }
};

/// ID: 305004 Words of Incomprehensible Glory
class spell_words_of_incomprehensible_glory_305004 : public AuraScript
{
    PrepareAuraScript(spell_words_of_incomprehensible_glory_305004);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_words_of_incomprehensible_glory_305004::CheckProc);
        OnProc += AuraProcFn(spell_words_of_incomprehensible_glory_305004::HandleProc);
    }
};

/// ID: 305006 Scroll of Elchaver
class spell_scroll_of_elchaver_305006 : public AuraScript
{
    PrepareAuraScript(spell_scroll_of_elchaver_305006);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_scroll_of_elchaver_305006::CheckProc);
        OnProc += AuraProcFn(spell_scroll_of_elchaver_305006::HandleProc);
    }
};

/// ID: 305008 Hematoma Bat
class spell_hematoma_bat_305008 : public AuraScript
{
    PrepareAuraScript(spell_hematoma_bat_305008);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_hematoma_bat_305008::CheckProc);
        OnProc += AuraProcFn(spell_hematoma_bat_305008::HandleProc);
    }
};

/// ID: 305042 Finger of Frozen Fury
class spell_finger_of_frozen_fury_305042 : public AuraScript
{
    PrepareAuraScript(spell_finger_of_frozen_fury_305042);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_finger_of_frozen_fury_305042::CheckProc);
        OnProc += AuraProcFn(spell_finger_of_frozen_fury_305042::HandleProc);
    }
};

/// ID: 305044 Lightning Dust
class spell_lightning_dust_305044 : public AuraScript
{
    PrepareAuraScript(spell_lightning_dust_305044);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_lightning_dust_305044::CheckProc);
        OnProc += AuraProcFn(spell_lightning_dust_305044::HandleProc);
    }
};

/// ID: 305047 Corruption Antenna
class spell_corruption_antenna_305047 : public AuraScript
{
    PrepareAuraScript(spell_corruption_antenna_305047);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_corruption_antenna_305047::CheckProc);
        OnProc += AuraProcFn(spell_corruption_antenna_305047::HandleProc);
    }
};

/// ID: 305050 Watchful Lightfly
class spell_watchful_lightfly_305050 : public AuraScript
{
    PrepareAuraScript(spell_watchful_lightfly_305050);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_watchful_lightfly_305050::CheckProc);
        OnProc += AuraProcFn(spell_watchful_lightfly_305050::HandleProc);
    }
};

/// ID: 305052 Lens of Elchaver
class spell_lens_of_elchaver_305052 : public AuraScript
{
    PrepareAuraScript(spell_lens_of_elchaver_305052);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_lens_of_elchaver_305052::CheckProc);
        OnProc += AuraProcFn(spell_lens_of_elchaver_305052::HandleProc);
    }
};

/// ID: 305054 Yel'Shir's Powerglove
class spell_yelshirs_powerglove_305054 : public AuraScript
{
    PrepareAuraScript(spell_yelshirs_powerglove_305054);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_yelshirs_powerglove_305054::CheckProc);
        OnProc += AuraProcFn(spell_yelshirs_powerglove_305054::HandleProc);
    }
};

/// ID: 305266 Warden's Authority
class spell_wardens_authority_305266 : public AuraScript
{
    PrepareAuraScript(spell_wardens_authority_305266);

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
    }


    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_wardens_authority_305266::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
    }
};

/// ID: 305269 Pocketed Soulcage
class spell_pocketed_soulcage_305269 : public SpellScript
{
    PrepareSpellScript(spell_pocketed_soulcage_305269);

    void HandleDummy(SpellEffIndex /*eff*/)
    {
    }


    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_pocketed_soulcage_305269::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

/// ID: 305274 Dark Armaments
class spell_dark_armaments_305274 : public AuraScript
{
    PrepareAuraScript(spell_dark_armaments_305274);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_dark_armaments_305274::CheckProc);
        OnProc += AuraProcFn(spell_dark_armaments_305274::HandleProc);
    }
};

/// ID: 305282 Glasswing Charm
class spell_glasswing_charm_305282 : public AuraScript
{
    PrepareAuraScript(spell_glasswing_charm_305282);

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
    }


    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_glasswing_charm_305282::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

/// ID: 305293 Prisoner's Concord
class spell_prisoners_concord_305293 : public AuraScript
{
    PrepareAuraScript(spell_prisoners_concord_305293);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_prisoners_concord_305293::CheckProc);
        OnProc += AuraProcFn(spell_prisoners_concord_305293::HandleProc);
    }
};

/// ID: 306563 Kyrian Blessing
class spell_kyrian_blessing_306563 : public AuraScript
{
    PrepareAuraScript(spell_kyrian_blessing_306563);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_kyrian_blessing_306563::CheckProc);
        OnProc += AuraProcFn(spell_kyrian_blessing_306563::HandleProc);
    }
};

/// ID: 306571 Maldraxxian Repayment
class spell_maldraxxian_repayment_306571 : public AuraScript
{
    PrepareAuraScript(spell_maldraxxian_repayment_306571);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_maldraxxian_repayment_306571::CheckProc);
        OnProc += AuraProcFn(spell_maldraxxian_repayment_306571::HandleProc);
    }
};

/// ID: 306573 Gift of Ardenweald
class spell_gift_of_ardenweald_306573 : public AuraScript
{
    PrepareAuraScript(spell_gift_of_ardenweald_306573);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_gift_of_ardenweald_306573::CheckProc);
        OnProc += AuraProcFn(spell_gift_of_ardenweald_306573::HandleProc);
    }
};

/// ID: 306575 Venthyr's Gratitude
class spell_venthyrs_gratitude_306575 : public AuraScript
{
    PrepareAuraScript(spell_venthyrs_gratitude_306575);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_venthyrs_gratitude_306575::CheckProc);
        OnProc += AuraProcFn(spell_venthyrs_gratitude_306575::HandleProc);
    }
};

/// ID: 342027 Offer of Souls
class spell_offer_of_souls_342027 : public SpellScript
{
    PrepareSpellScript(spell_offer_of_souls_342027);

    void HandleDummy(SpellEffIndex /*eff*/)
    {
    }


    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_offer_of_souls_342027::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

/// ID: 306604 Boots of Bellaton
class spell_boots_of_bellaton_306604 : public AuraScript
{
    PrepareAuraScript(spell_boots_of_bellaton_306604);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_boots_of_bellaton_306604::CheckProc);
        OnProc += AuraProcFn(spell_boots_of_bellaton_306604::HandleProc);
    }
};

/// ID: 306609 Disemboweler's Hook
class spell_disembowelers_hook_306609 : public AuraScript
{
    PrepareAuraScript(spell_disembowelers_hook_306609);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_disembowelers_hook_306609::CheckProc);
        OnProc += AuraProcFn(spell_disembowelers_hook_306609::HandleProc);
    }
};

/// ID: 306615 Roots of the Dreamtree
class spell_roots_of_the_dreamtree_306615 : public AuraScript
{
    PrepareAuraScript(spell_roots_of_the_dreamtree_306615);

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
    }


    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_roots_of_the_dreamtree_306615::HandlePeriodic, EFFECT_4, SPELL_AURA_PERIODIC_DUMMY);
    }
};

/// ID: 308193 Lens of Elchaver
class spell_lens_of_elchaver_308193 : public AuraScript
{
    PrepareAuraScript(spell_lens_of_elchaver_308193);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_lens_of_elchaver_308193::CheckProc);
        OnProc += AuraProcFn(spell_lens_of_elchaver_308193::HandleProc);
    }
};

/// ID: 308194 Finger of Frozen Fury
class spell_finger_of_frozen_fury_308194 : public AuraScript
{
    PrepareAuraScript(spell_finger_of_frozen_fury_308194);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_finger_of_frozen_fury_308194::CheckProc);
        OnProc += AuraProcFn(spell_finger_of_frozen_fury_308194::HandleProc);
    }
};

/// ID: 308195 Lightning Dust
class spell_lightning_dust_308195 : public AuraScript
{
    PrepareAuraScript(spell_lightning_dust_308195);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_lightning_dust_308195::CheckProc);
        OnProc += AuraProcFn(spell_lightning_dust_308195::HandleProc);
    }
};

/// ID: 308196 Corruption Antenna
class spell_corruption_antenna_308196 : public AuraScript
{
    PrepareAuraScript(spell_corruption_antenna_308196);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_corruption_antenna_308196::CheckProc);
        OnProc += AuraProcFn(spell_corruption_antenna_308196::HandleProc);
    }
};

/// ID: 308201 Curious Miasma
class spell_curious_miasma_308201 : public AuraScript
{
    PrepareAuraScript(spell_curious_miasma_308201);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_curious_miasma_308201::CheckProc);
        OnProc += AuraProcFn(spell_curious_miasma_308201::HandleProc);
    }
};

/// ID: 313566 Hatred Core
class spell_hatred_core_313566 : public AuraScript
{
    PrepareAuraScript(spell_hatred_core_313566);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_hatred_core_313566::CheckProc);
        OnProc += AuraProcFn(spell_hatred_core_313566::HandleProc);
    }
};

/// ID: 313567 Piercing Vision of Corraph
class spell_piercing_vision_of_corraph_313567 : public AuraScript
{
    PrepareAuraScript(spell_piercing_vision_of_corraph_313567);

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
    }


    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_piercing_vision_of_corraph_313567::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
    }
};

/// ID: 314222 Zeal of the Aspirant
class spell_zeal_of_the_aspirant_314222 : public AuraScript
{
    PrepareAuraScript(spell_zeal_of_the_aspirant_314222);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_zeal_of_the_aspirant_314222::CheckProc);
        OnProc += AuraProcFn(spell_zeal_of_the_aspirant_314222::HandleProc);
    }
};

/// ID: 314235 Oppressor's Chain
class spell_oppressors_chain_314235 : public AuraScript
{
    PrepareAuraScript(spell_oppressors_chain_314235);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_oppressors_chain_314235::CheckProc);
        OnProc += AuraProcFn(spell_oppressors_chain_314235::HandleProc);
    }
};

/// ID: 314237 Mask of the Winged Dominator
class spell_mask_of_the_winged_dominator_314237 : public AuraScript
{
    PrepareAuraScript(spell_mask_of_the_winged_dominator_314237);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_mask_of_the_winged_dominator_314237::CheckProc);
        OnProc += AuraProcFn(spell_mask_of_the_winged_dominator_314237::HandleProc);
    }
};

/// ID: 314240 Sacrificial Soul-Ash
class spell_sacrificial_soulash_314240 : public AuraScript
{
    PrepareAuraScript(spell_sacrificial_soulash_314240);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_sacrificial_soulash_314240::CheckProc);
        OnProc += AuraProcFn(spell_sacrificial_soulash_314240::HandleProc);
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_sacrificial_soulash_314240::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

/// ID: 314253 Wizard's Prayer
class spell_wizards_prayer_314253 : public AuraScript
{
    PrepareAuraScript(spell_wizards_prayer_314253);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_wizards_prayer_314253::CheckProc);
        OnProc += AuraProcFn(spell_wizards_prayer_314253::HandleProc);
    }
};

/// ID: 327363 Torch of Humility
class spell_torch_of_humility_327363 : public AuraScript
{
    PrepareAuraScript(spell_torch_of_humility_327363);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_torch_of_humility_327363::CheckProc);
        OnProc += AuraProcFn(spell_torch_of_humility_327363::HandleProc);
    }
};

/// ID: 314295 Spearheads of Eternity
class spell_spearheads_of_eternity_314295 : public AuraScript
{
    PrepareAuraScript(spell_spearheads_of_eternity_314295);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_spearheads_of_eternity_314295::CheckProc);
        OnProc += AuraProcFn(spell_spearheads_of_eternity_314295::HandleProc);
    }
};

/// ID: 315266 Fleetwing Torch
class spell_fleetwing_torch_315266 : public AuraScript
{
    PrepareAuraScript(spell_fleetwing_torch_315266);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_fleetwing_torch_315266::CheckProc);
        OnProc += AuraProcFn(spell_fleetwing_torch_315266::HandleProc);
    }
};

/// ID: 315288 Frostbite Wand
class spell_frostbite_wand_315288 : public AuraScript
{
    PrepareAuraScript(spell_frostbite_wand_315288);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_frostbite_wand_315288::CheckProc);
        OnProc += AuraProcFn(spell_frostbite_wand_315288::HandleProc);
    }
};

/// ID: 316850 Unstable Phantasma Lure
class spell_unstable_phantasma_lure_316850 : public AuraScript
{
    PrepareAuraScript(spell_unstable_phantasma_lure_316850);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_unstable_phantasma_lure_316850::CheckProc);
        OnProc += AuraProcFn(spell_unstable_phantasma_lure_316850::HandleProc);
    }
};

/// ID: 319206 Elethium Diffuser
class spell_elethium_diffuser_319206 : public AuraScript
{
    PrepareAuraScript(spell_elethium_diffuser_319206);

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
    }


    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_elethium_diffuser_319206::HandlePeriodic, EFFECT_2, SPELL_AURA_PERIODIC_DUMMY);
    }
};

/// ID: 319605 Unlock Shortcut
class spell_unlock_shortcut_319605 : public SpellScript
{
    PrepareSpellScript(spell_unlock_shortcut_319605);

    void HandleDummy(SpellEffIndex /*eff*/)
    {
    }


    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_unlock_shortcut_319605::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

/// ID: 319649 Unlock Shortcut
class spell_unlock_shortcut_319649 : public SpellScript
{
    PrepareSpellScript(spell_unlock_shortcut_319649);

    void HandleDummy(SpellEffIndex /*eff*/)
    {
    }


    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_unlock_shortcut_319649::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

/// ID: 332206 Tainted Blood Vial
class spell_tainted_blood_vial_332206 : public AuraScript
{
    PrepareAuraScript(spell_tainted_blood_vial_332206);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_tainted_blood_vial_332206::CheckProc);
        OnProc += AuraProcFn(spell_tainted_blood_vial_332206::HandleProc);
    }
};

/// ID: 320931 Glutton's Guise
class spell_gluttons_guise_320931 : public AuraScript
{
    PrepareAuraScript(spell_gluttons_guise_320931);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_gluttons_guise_320931::CheckProc);
        OnProc += AuraProcFn(spell_gluttons_guise_320931::HandleProc);
    }
};

/// ID: 320932 Mark of Borrowed Power
class spell_mark_of_borrowed_power_320932 : public AuraScript
{
    PrepareAuraScript(spell_mark_of_borrowed_power_320932);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_mark_of_borrowed_power_320932::CheckProc);
        OnProc += AuraProcFn(spell_mark_of_borrowed_power_320932::HandleProc);
    }
};

/// ID: 332185 Blood-Stained Dagger
class spell_bloodstained_dagger_332185_AuraScript : public AuraScript
{
    PrepareAuraScript(spell_bloodstained_dagger_332185_AuraScript);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_bloodstained_dagger_332185_AuraScript::CheckProc);
        OnProc += AuraProcFn(spell_bloodstained_dagger_332185_AuraScript::HandleProc);
    }
};

class spell_bloodstained_dagger_332185_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_bloodstained_dagger_332185_SpellScript);

    void HandleDummy(SpellEffIndex /*eff*/)
    {
    }


    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_bloodstained_dagger_332185_SpellScript::HandleDummy, EFFECT_1, SPELL_EFFECT_DUMMY);
    }
};

/// ID: 320939 Dissolving Vial
class spell_dissolving_vial_320939 : public AuraScript
{
    PrepareAuraScript(spell_dissolving_vial_320939);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_dissolving_vial_320939::CheckProc);
        OnProc += AuraProcFn(spell_dissolving_vial_320939::HandleProc);
    }
};

/// ID: 332201 Smoking Shard of Teleportation
class spell_smoking_shard_of_teleportation_332201 : public AuraScript
{
    PrepareAuraScript(spell_smoking_shard_of_teleportation_332201);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_smoking_shard_of_teleportation_332201::CheckProc);
        OnProc += AuraProcFn(spell_smoking_shard_of_teleportation_332201::HandleProc);
    }
};

/// ID: 320941 Soulvoid Bag
class spell_soulvoid_bag_320941 : public AuraScript
{
    PrepareAuraScript(spell_soulvoid_bag_320941);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_soulvoid_bag_320941::CheckProc);
        OnProc += AuraProcFn(spell_soulvoid_bag_320941::HandleProc);
    }
};

/// ID: 332775 Bottled Shadow
class spell_bottled_shadow_332775 : public AuraScript
{
    PrepareAuraScript(spell_bottled_shadow_332775);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_bottled_shadow_332775::CheckProc);
        OnProc += AuraProcFn(spell_bottled_shadow_332775::HandleProc);
    }
};

/// ID: 320950 Sacrificial Vermin
class spell_sacrificial_vermin_320950 : public AuraScript
{
    PrepareAuraScript(spell_sacrificial_vermin_320950);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_sacrificial_vermin_320950::CheckProc);
        OnProc += AuraProcFn(spell_sacrificial_vermin_320950::HandleProc);
    }
};

/// ID: 320952 Visage of Lethality
class spell_visage_of_lethality_320952 : public AuraScript
{
    PrepareAuraScript(spell_visage_of_lethality_320952);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_visage_of_lethality_320952::CheckProc);
        OnProc += AuraProcFn(spell_visage_of_lethality_320952::HandleProc);
    }
};

/// ID: 320956 Disembodied Tongue
class spell_disembodied_tongue_320956 : public AuraScript
{
    PrepareAuraScript(spell_disembodied_tongue_320956);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_disembodied_tongue_320956::CheckProc);
        OnProc += AuraProcFn(spell_disembodied_tongue_320956::HandleProc);
    }
};

/// ID: 320868 Horrific Dictionary
class spell_horrific_dictionary_320868 : public AuraScript
{
    PrepareAuraScript(spell_horrific_dictionary_320868);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_horrific_dictionary_320868::CheckProc);
        OnProc += AuraProcFn(spell_horrific_dictionary_320868::HandleProc);
    }
};

/// ID: 329588 Fragments of Obscurity
class spell_fragments_of_obscurity_329588 : public AuraScript
{
    PrepareAuraScript(spell_fragments_of_obscurity_329588);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_fragments_of_obscurity_329588::CheckProc);
        OnProc += AuraProcFn(spell_fragments_of_obscurity_329588::HandleProc);
    }
};

/// ID: 329632 Light-Infused Egg
class spell_lightinfused_egg_329632 : public AuraScript
{
    PrepareAuraScript(spell_lightinfused_egg_329632);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_lightinfused_egg_329632::CheckProc);
        OnProc += AuraProcFn(spell_lightinfused_egg_329632::HandleProc);
    }
};

/// ID: 320872 Flashbox
class spell_flashbox_320872 : public AuraScript
{
    PrepareAuraScript(spell_flashbox_320872);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_flashbox_320872::CheckProc);
        OnProc += AuraProcFn(spell_flashbox_320872::HandleProc);
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_flashbox_320872::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

/// ID: 320874 Fallen Priest's Blessing
class spell_fallen_priests_blessing_320874 : public AuraScript
{
    PrepareAuraScript(spell_fallen_priests_blessing_320874);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_fallen_priests_blessing_320874::CheckProc);
        OnProc += AuraProcFn(spell_fallen_priests_blessing_320874::HandleProc);
    }
};

/// ID: 329428 Scales of Trauma
class spell_scales_of_trauma_329428 : public AuraScript
{
    PrepareAuraScript(spell_scales_of_trauma_329428);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_scales_of_trauma_329428::CheckProc);
        OnProc += AuraProcFn(spell_scales_of_trauma_329428::HandleProc);
    }
};

/// ID: 329241 Volatile Phantasm
class spell_volatile_phantasm_329241 : public AuraScript
{
    PrepareAuraScript(spell_volatile_phantasm_329241);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_volatile_phantasm_329241::CheckProc);
        OnProc += AuraProcFn(spell_volatile_phantasm_329241::HandleProc);
    }
};

/// ID: 320884 Impulsor
class spell_impulsor_320884 : public AuraScript
{
    PrepareAuraScript(spell_impulsor_320884);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_impulsor_320884::CheckProc);
        OnProc += AuraProcFn(spell_impulsor_320884::HandleProc);
    }
};

/// ID: 329689 Wailing Visage
class spell_wailing_visage_329689 : public SpellScript
{
    PrepareSpellScript(spell_wailing_visage_329689);

    void HandleDummy(SpellEffIndex /*eff*/)
    {
    }


    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_wailing_visage_329689::HandleDummy, EFFECT_1, SPELL_EFFECT_DUMMY);
    }
};

/// ID: 320892 Puppetmaster's Strings
class spell_puppetmasters_strings_320892_AuraScript : public AuraScript
{
    PrepareAuraScript(spell_puppetmasters_strings_320892_AuraScript);

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
    }


    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_puppetmasters_strings_320892_AuraScript::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

class spell_puppetmasters_strings_320892_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_puppetmasters_strings_320892_SpellScript);

    void HandleDummy(SpellEffIndex /*eff*/)
    {
    }


    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_puppetmasters_strings_320892_SpellScript::HandleDummy, EFFECT_2, SPELL_EFFECT_DUMMY);
    }
};

/// ID: 320901 Whizzard Hat
class spell_whizzard_hat_320901 : public AuraScript
{
    PrepareAuraScript(spell_whizzard_hat_320901);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_whizzard_hat_320901::CheckProc);
        OnProc += AuraProcFn(spell_whizzard_hat_320901::HandleProc);
    }
};

/// ID: 320902 Bombardier's Etching
class spell_bombardiers_etching_320902 : public AuraScript
{
    PrepareAuraScript(spell_bombardiers_etching_320902);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_bombardiers_etching_320902::CheckProc);
        OnProc += AuraProcFn(spell_bombardiers_etching_320902::HandleProc);
    }
};

/// ID: 320906 Scroll of Explosure
class spell_scroll_of_explosure_320906 : public AuraScript
{
    PrepareAuraScript(spell_scroll_of_explosure_320906);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_scroll_of_explosure_320906::CheckProc);
        OnProc += AuraProcFn(spell_scroll_of_explosure_320906::HandleProc);
    }
};

/// ID: 320910 Constellation Shield
class spell_constellation_shield_320910 : public AuraScript
{
    PrepareAuraScript(spell_constellation_shield_320910);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_constellation_shield_320910::CheckProc);
        OnProc += AuraProcFn(spell_constellation_shield_320910::HandleProc);
    }
};

/// ID: 320914 Chronomancer's Hourglass
class spell_chronomancers_hourglass_320914 : public AuraScript
{
    PrepareAuraScript(spell_chronomancers_hourglass_320914);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_chronomancers_hourglass_320914::CheckProc);
        OnProc += AuraProcFn(spell_chronomancers_hourglass_320914::HandleProc);
    }
};

/// ID: 320916 Triune Ward
class spell_triune_ward_320916 : public AuraScript
{
    PrepareAuraScript(spell_triune_ward_320916);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_triune_ward_320916::CheckProc);
        OnProc += AuraProcFn(spell_triune_ward_320916::HandleProc);
    }
};

/// ID: 330745 Timeweaver's Needle
class spell_timeweavers_needle_330745 : public AuraScript
{
    PrepareAuraScript(spell_timeweavers_needle_330745);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_timeweavers_needle_330745::CheckProc);
        OnProc += AuraProcFn(spell_timeweavers_needle_330745::HandleProc);
    }
};

/// ID: 320925 Dimensional Blade
class spell_dimensional_blade_320925 : public AuraScript
{
    PrepareAuraScript(spell_dimensional_blade_320925);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_dimensional_blade_320925::CheckProc);
        OnProc += AuraProcFn(spell_dimensional_blade_320925::HandleProc);
    }
};

/// ID: 320927 Clouded Diamond
class spell_clouded_diamond_320927 : public AuraScript
{
    PrepareAuraScript(spell_clouded_diamond_320927);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_clouded_diamond_320927::CheckProc);
        OnProc += AuraProcFn(spell_clouded_diamond_320927::HandleProc);
    }
};

/// ID: 322026 Bladed Bulwark
class spell_bladed_bulwark_322026 : public AuraScript
{
    PrepareAuraScript(spell_bladed_bulwark_322026);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_bladed_bulwark_322026::CheckProc);
        OnProc += AuraProcFn(spell_bladed_bulwark_322026::HandleProc);
    }
};

/// ID: 329345 Signet of Tormented Kings
class spell_signet_of_tormented_kings_329345 : public AuraScript
{
    PrepareAuraScript(spell_signet_of_tormented_kings_329345);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_signet_of_tormented_kings_329345::CheckProc);
        OnProc += AuraProcFn(spell_signet_of_tormented_kings_329345::HandleProc);
    }
};

/// ID: 329283 Umbral Ear Trumpet
class spell_umbral_ear_trumpet_329283 : public AuraScript
{
    PrepareAuraScript(spell_umbral_ear_trumpet_329283);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_umbral_ear_trumpet_329283::CheckProc);
        OnProc += AuraProcFn(spell_umbral_ear_trumpet_329283::HandleProc);
    }
};

/// ID: 322032 Smoldering Inertia
class spell_smoldering_inertia_322032 : public AuraScript
{
    PrepareAuraScript(spell_smoldering_inertia_322032);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_smoldering_inertia_322032::CheckProc);
        OnProc += AuraProcFn(spell_smoldering_inertia_322032::HandleProc);
    }
};

/// ID: 322049 Periapt of Furor
class spell_periapt_of_furor_322049 : public AuraScript
{
    PrepareAuraScript(spell_periapt_of_furor_322049);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_periapt_of_furor_322049::CheckProc);
        OnProc += AuraProcFn(spell_periapt_of_furor_322049::HandleProc);
    }
};

/// ID: 322029 Fan of Longswords
class spell_fan_of_longswords_322029 : public AuraScript
{
    PrepareAuraScript(spell_fan_of_longswords_322029);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_fan_of_longswords_322029::CheckProc);
        OnProc += AuraProcFn(spell_fan_of_longswords_322029::HandleProc);
    }
};

/// ID: 329268 Misshapen Mirror
class spell_misshapen_mirror_329268 : public AuraScript
{
    PrepareAuraScript(spell_misshapen_mirror_329268);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_misshapen_mirror_329268::CheckProc);
        OnProc += AuraProcFn(spell_misshapen_mirror_329268::HandleProc);
    }
};

/// ID: 329275 Shrieking Flagon
class spell_shrieking_flagon_329275 : public AuraScript
{
    PrepareAuraScript(spell_shrieking_flagon_329275);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_shrieking_flagon_329275::CheckProc);
        OnProc += AuraProcFn(spell_shrieking_flagon_329275::HandleProc);
    }
};

/// ID: 329452 Ogundimu's Fist
class spell_ogundimus_fist_329452 : public AuraScript
{
    PrepareAuraScript(spell_ogundimus_fist_329452);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_ogundimus_fist_329452::CheckProc);
        OnProc += AuraProcFn(spell_ogundimus_fist_329452::HandleProc);
    }
};

/// ID: 329335 Gibbering Skull
class spell_gibbering_skull_329335 : public AuraScript
{
    PrepareAuraScript(spell_gibbering_skull_329335);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_gibbering_skull_329335::CheckProc);
        OnProc += AuraProcFn(spell_gibbering_skull_329335::HandleProc);
    }
};

/// ID: 329213 Voracious Culling Blade
class spell_voracious_culling_blade_329213 : public AuraScript
{
    PrepareAuraScript(spell_voracious_culling_blade_329213);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_voracious_culling_blade_329213::CheckProc);
        OnProc += AuraProcFn(spell_voracious_culling_blade_329213::HandleProc);
    }
};

/// ID: 322035 Pleonexian Command
class spell_pleonexian_command_322035 : public AuraScript
{
    PrepareAuraScript(spell_pleonexian_command_322035);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_pleonexian_command_322035::CheckProc);
        OnProc += AuraProcFn(spell_pleonexian_command_322035::HandleProc);
    }
};

/// ID: 322031 Spattered Soles
class spell_spattered_soles_322031 : public AuraScript
{
    PrepareAuraScript(spell_spattered_soles_322031);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_spattered_soles_322031::CheckProc);
        OnProc += AuraProcFn(spell_spattered_soles_322031::HandleProc);
    }
};

/// ID: 322043 Resonant Throatbands
class spell_resonant_throatbands_322043 : public AuraScript
{
    PrepareAuraScript(spell_resonant_throatbands_322043);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_resonant_throatbands_322043::CheckProc);
        OnProc += AuraProcFn(spell_resonant_throatbands_322043::HandleProc);
    }
};

/// ID: 322030 Hurricane Heart
class spell_hurricane_heart_322030 : public AuraScript
{
    PrepareAuraScript(spell_hurricane_heart_322030);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_hurricane_heart_322030::CheckProc);
        OnProc += AuraProcFn(spell_hurricane_heart_322030::HandleProc);
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_hurricane_heart_322030::HandlePeriodic, EFFECT_1, SPELL_AURA_PERIODIC_DUMMY);
    }
};

/// ID: 329857 Deathseer's Satchel
class spell_deathseers_satchel_329857 : public AuraScript
{
    PrepareAuraScript(spell_deathseers_satchel_329857);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_deathseers_satchel_329857::CheckProc);
        OnProc += AuraProcFn(spell_deathseers_satchel_329857::HandleProc);
    }
};

/// ID: 329595 Leeching Lilypad
class spell_leeching_lilypad_329595 : public AuraScript
{
    PrepareAuraScript(spell_leeching_lilypad_329595);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_leeching_lilypad_329595::CheckProc);
        OnProc += AuraProcFn(spell_leeching_lilypad_329595::HandleProc);
    }
};

/// ID: 329726 Rimeblood
class spell_rimeblood_329726 : public AuraScript
{
    PrepareAuraScript(spell_rimeblood_329726);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_rimeblood_329726::CheckProc);
        OnProc += AuraProcFn(spell_rimeblood_329726::HandleProc);
    }
};

/// ID: 329768 Chains of Devastation
class spell_chains_of_devastation_329768 : public AuraScript
{
    PrepareAuraScript(spell_chains_of_devastation_329768);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_chains_of_devastation_329768::CheckProc);
        OnProc += AuraProcFn(spell_chains_of_devastation_329768::HandleProc);
    }
};

/// ID: 329793 Mawrats on Ice
class spell_mawrats_on_ice_329793 : public AuraScript
{
    PrepareAuraScript(spell_mawrats_on_ice_329793);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_mawrats_on_ice_329793::CheckProc);
        OnProc += AuraProcFn(spell_mawrats_on_ice_329793::HandleProc);
    }
};

/// ID: 329789 Deathseer's Whip
class spell_deathseers_whip_329789 : public AuraScript
{
    PrepareAuraScript(spell_deathseers_whip_329789);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_deathseers_whip_329789::CheckProc);
        OnProc += AuraProcFn(spell_deathseers_whip_329789::HandleProc);
    }
};

/// ID: 329805 Shield of Spirits
class spell_shield_of_spirits_329805 : public AuraScript
{
    PrepareAuraScript(spell_shield_of_spirits_329805);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_shield_of_spirits_329805::CheckProc);
        OnProc += AuraProcFn(spell_shield_of_spirits_329805::HandleProc);
    }
};

/// ID: 330179 Heart of the Deathseer
class spell_heart_of_the_deathseer_330179 : public AuraScript
{
    PrepareAuraScript(spell_heart_of_the_deathseer_330179);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_heart_of_the_deathseer_330179::CheckProc);
        OnProc += AuraProcFn(spell_heart_of_the_deathseer_330179::HandleProc);
    }
};

/// ID: 329937 Deathseer Choker
class spell_deathseer_choker_329937 : public AuraScript
{
    PrepareAuraScript(spell_deathseer_choker_329937);

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
    }


    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_deathseer_choker_329937::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

/// ID: 329963 Deathseer's Reins
class spell_deathseers_reins_329963 : public AuraScript
{
    PrepareAuraScript(spell_deathseers_reins_329963);

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
    }


    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_deathseers_reins_329963::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

/// ID: 329811 Spike of the Ice Guardian
class spell_spike_of_the_ice_guardian_329811 : public AuraScript
{
    PrepareAuraScript(spell_spike_of_the_ice_guardian_329811);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_spike_of_the_ice_guardian_329811::CheckProc);
        OnProc += AuraProcFn(spell_spike_of_the_ice_guardian_329811::HandleProc);
    }
};

/// ID: 331463 Fogged Crystal
class spell_fogged_crystal_331463 : public AuraScript
{
    PrepareAuraScript(spell_fogged_crystal_331463);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_fogged_crystal_331463::CheckProc);
        OnProc += AuraProcFn(spell_fogged_crystal_331463::HandleProc);
    }
};

/// ID: 331367 Sigil of Skoldus
class spell_sigil_of_skoldus_331367 : public AuraScript
{
    PrepareAuraScript(spell_sigil_of_skoldus_331367);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_sigil_of_skoldus_331367::CheckProc);
        OnProc += AuraProcFn(spell_sigil_of_skoldus_331367::HandleProc);
    }
};

/// ID: 331365 Deadeye Satchel
class spell_deadeye_satchel_331365 : public AuraScript
{
    PrepareAuraScript(spell_deadeye_satchel_331365);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_deadeye_satchel_331365::CheckProc);
        OnProc += AuraProcFn(spell_deadeye_satchel_331365::HandleProc);
    }
};

/// ID: 331187 Cadaverous Cleats
class spell_cadaverous_cleats_331187 : public AuraScript
{
    PrepareAuraScript(spell_cadaverous_cleats_331187);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_cadaverous_cleats_331187::CheckProc);
        OnProc += AuraProcFn(spell_cadaverous_cleats_331187::HandleProc);
    }
};

/// ID: 342546 Mawrat Scent Gland
class spell_mawrat_scent_gland_342546 : public AuraScript
{
    PrepareAuraScript(spell_mawrat_scent_gland_342546);

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
    }


    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_mawrat_scent_gland_342546::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

/// ID: 331296 Forsworn Feather
class spell_forsworn_feather_331296 : public AuraScript
{
    PrepareAuraScript(spell_forsworn_feather_331296);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_forsworn_feather_331296::CheckProc);
        OnProc += AuraProcFn(spell_forsworn_feather_331296::HandleProc);
    }
};

/// ID: 331287 Bursting Tar
class spell_bursting_tar_331287 : public AuraScript
{
    PrepareAuraScript(spell_bursting_tar_331287);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_bursting_tar_331287::CheckProc);
        OnProc += AuraProcFn(spell_bursting_tar_331287::HandleProc);
    }
};

/// ID: 331283 Peltsman's Grit
class spell_peltsmans_grit_331283 : public AuraScript
{
    PrepareAuraScript(spell_peltsmans_grit_331283);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_peltsmans_grit_331283::CheckProc);
        OnProc += AuraProcFn(spell_peltsmans_grit_331283::HandleProc);
    }
};

/// ID: 331355 Craven Strategem
class spell_craven_strategem_331355 : public AuraScript
{
    PrepareAuraScript(spell_craven_strategem_331355);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_craven_strategem_331355::CheckProc);
        OnProc += AuraProcFn(spell_craven_strategem_331355::HandleProc);
    }
};

/// ID: 331194 Scaredy Rat
class spell_scaredy_rat_331194 : public AuraScript
{
    PrepareAuraScript(spell_scaredy_rat_331194);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_scaredy_rat_331194::CheckProc);
        OnProc += AuraProcFn(spell_scaredy_rat_331194::HandleProc);
    }
};

/// ID: 331455 Amplifying Mirror
class spell_amplifying_mirror_331455 : public AuraScript
{
    PrepareAuraScript(spell_amplifying_mirror_331455);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_amplifying_mirror_331455::CheckProc);
        OnProc += AuraProcFn(spell_amplifying_mirror_331455::HandleProc);
    }
};

/// ID: 331357 Hateful Shard-Ring
class spell_hateful_shardring_331357 : public AuraScript
{
    PrepareAuraScript(spell_hateful_shardring_331357);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_hateful_shardring_331357::CheckProc);
        OnProc += AuraProcFn(spell_hateful_shardring_331357::HandleProc);
    }
};

/// ID: 331183 Piercing Scope
class spell_piercing_scope_331183 : public AuraScript
{
    PrepareAuraScript(spell_piercing_scope_331183);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_piercing_scope_331183::CheckProc);
        OnProc += AuraProcFn(spell_piercing_scope_331183::HandleProc);
    }
};

/// ID: 343449 Flowing Potential Wraps
class spell_flowing_potential_wraps_343449 : public AuraScript
{
    PrepareAuraScript(spell_flowing_potential_wraps_343449);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_flowing_potential_wraps_343449::CheckProc);
        OnProc += AuraProcFn(spell_flowing_potential_wraps_343449::HandleProc);
    }
};

/// ID: 343450 Terror-laden Slumbersand
class spell_terrorladen_slumbersand_343450 : public AuraScript
{
    PrepareAuraScript(spell_terrorladen_slumbersand_343450);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_terrorladen_slumbersand_343450::CheckProc);
        OnProc += AuraProcFn(spell_terrorladen_slumbersand_343450::HandleProc);
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_terrorladen_slumbersand_343450::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

/// ID: 343451 Vein Rippers
class spell_vein_rippers_343451 : public AuraScript
{
    PrepareAuraScript(spell_vein_rippers_343451);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_vein_rippers_343451::CheckProc);
        OnProc += AuraProcFn(spell_vein_rippers_343451::HandleProc);
    }
};

/// ID: 343452 Muffled Metronome
class spell_muffled_metronome_343452 : public AuraScript
{
    PrepareAuraScript(spell_muffled_metronome_343452);

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
    }


    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_muffled_metronome_343452::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

/// ID: 343446 Quicksilver Mixture
class spell_quicksilver_mixture_343446 : public AuraScript
{
    PrepareAuraScript(spell_quicksilver_mixture_343446);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_quicksilver_mixture_343446::CheckProc);
        OnProc += AuraProcFn(spell_quicksilver_mixture_343446::HandleProc);
    }
};

/// ID: 343442 Draped Prism Shawl
class spell_draped_prism_shawl_343442 : public AuraScript
{
    PrepareAuraScript(spell_draped_prism_shawl_343442);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_draped_prism_shawl_343442::CheckProc);
        OnProc += AuraProcFn(spell_draped_prism_shawl_343442::HandleProc);
    }
};

/// ID: 343392 Shimmering Cloaktrails
class spell_shimmering_cloaktrails_343392 : public AuraScript
{
    PrepareAuraScript(spell_shimmering_cloaktrails_343392);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_shimmering_cloaktrails_343392::CheckProc);
        OnProc += AuraProcFn(spell_shimmering_cloaktrails_343392::HandleProc);
    }
};

/// ID: 333765 Distracting Charges
class spell_distracting_charges_333765 : public AuraScript
{
    PrepareAuraScript(spell_distracting_charges_333765);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_distracting_charges_333765::CheckProc);
        OnProc += AuraProcFn(spell_distracting_charges_333765::HandleProc);
    }
};

/// ID: 333763 Vial of Unseen Poison
class spell_vial_of_unseen_poison_333763 : public AuraScript
{
    PrepareAuraScript(spell_vial_of_unseen_poison_333763);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_vial_of_unseen_poison_333763::CheckProc);
        OnProc += AuraProcFn(spell_vial_of_unseen_poison_333763::HandleProc);
    }
};

/// ID: 333512 Restless Onyx Geodes
class spell_restless_onyx_geodes_333512 : public AuraScript
{
    PrepareAuraScript(spell_restless_onyx_geodes_333512);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_restless_onyx_geodes_333512::CheckProc);
        OnProc += AuraProcFn(spell_restless_onyx_geodes_333512::HandleProc);
    }
};

/// ID: 333506 Unceasing Chain Link
class spell_unceasing_chain_link_333506 : public AuraScript
{
    PrepareAuraScript(spell_unceasing_chain_link_333506);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_unceasing_chain_link_333506::CheckProc);
        OnProc += AuraProcFn(spell_unceasing_chain_link_333506::HandleProc);
    }
};

/// ID: 333505 Rupturing Spike
class spell_rupturing_spike_333505 : public AuraScript
{
    PrepareAuraScript(spell_rupturing_spike_333505);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_rupturing_spike_333505::CheckProc);
        OnProc += AuraProcFn(spell_rupturing_spike_333505::HandleProc);
    }
};

/// ID: 333502 Slippery Wraithcoil
class spell_slippery_wraithcoil_333502 : public AuraScript
{
    PrepareAuraScript(spell_slippery_wraithcoil_333502);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_slippery_wraithcoil_333502::CheckProc);
        OnProc += AuraProcFn(spell_slippery_wraithcoil_333502::HandleProc);
    }
};

/// ID: 333501 Pouch of Soul-Ash
class spell_pouch_of_soulash_333501 : public AuraScript
{
    PrepareAuraScript(spell_pouch_of_soulash_333501);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_pouch_of_soulash_333501::CheckProc);
        OnProc += AuraProcFn(spell_pouch_of_soulash_333501::HandleProc);
    }
};

/// ID: 343382 Shadowlaced Armaments
class spell_shadowlaced_armaments_343382 : public AuraScript
{
    PrepareAuraScript(spell_shadowlaced_armaments_343382);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_shadowlaced_armaments_343382::CheckProc);
        OnProc += AuraProcFn(spell_shadowlaced_armaments_343382::HandleProc);
    }
};

/// ID: 343461 Scales of Order
class spell_scales_of_order_343461 : public AuraScript
{
    PrepareAuraScript(spell_scales_of_order_343461);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_scales_of_order_343461::CheckProc);
        OnProc += AuraProcFn(spell_scales_of_order_343461::HandleProc);
    }
};

/// ID: 343822 Celestial Lasso
class spell_celestial_lasso_343822 : public AuraScript
{
    PrepareAuraScript(spell_celestial_lasso_343822);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_celestial_lasso_343822::CheckProc);
        OnProc += AuraProcFn(spell_celestial_lasso_343822::HandleProc);
    }
};

/// ID: 343793 Bottled Wind
class spell_bottled_wind_343793 : public AuraScript
{
    PrepareAuraScript(spell_bottled_wind_343793);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_bottled_wind_343793::CheckProc);
        OnProc += AuraProcFn(spell_bottled_wind_343793::HandleProc);
    }
};

/// ID: 343790 Cloud of Feathers
class spell_cloud_of_feathers_343790 : public AuraScript
{
    PrepareAuraScript(spell_cloud_of_feathers_343790);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_cloud_of_feathers_343790::CheckProc);
        OnProc += AuraProcFn(spell_cloud_of_feathers_343790::HandleProc);
    }
};

/// ID: 331834 Balance of the Ox
class spell_balance_of_the_ox_331834 : public AuraScript
{
    PrepareAuraScript(spell_balance_of_the_ox_331834);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_balance_of_the_ox_331834::CheckProc);
        OnProc += AuraProcFn(spell_balance_of_the_ox_331834::HandleProc);
    }
};

/// ID: 331830 Caught by the Dropkicks
class spell_caught_by_the_dropkicks_331830 : public AuraScript
{
    PrepareAuraScript(spell_caught_by_the_dropkicks_331830);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_caught_by_the_dropkicks_331830::CheckProc);
        OnProc += AuraProcFn(spell_caught_by_the_dropkicks_331830::HandleProc);
    }
};

/// ID: 331667 Tiger and Crane Figurines
class spell_tiger_and_crane_figurines_331667 : public AuraScript
{
    PrepareAuraScript(spell_tiger_and_crane_figurines_331667);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_tiger_and_crane_figurines_331667::CheckProc);
        OnProc += AuraProcFn(spell_tiger_and_crane_figurines_331667::HandleProc);
    }
};

/// ID: 331663 Rolling Tigers
class spell_rolling_tigers_331663 : public AuraScript
{
    PrepareAuraScript(spell_rolling_tigers_331663);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_rolling_tigers_331663::CheckProc);
        OnProc += AuraProcFn(spell_rolling_tigers_331663::HandleProc);
    }
};

/// ID: 331650 Flowing Chi Rolls
class spell_flowing_chi_rolls_331650 : public AuraScript
{
    PrepareAuraScript(spell_flowing_chi_rolls_331650);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_flowing_chi_rolls_331650::CheckProc);
        OnProc += AuraProcFn(spell_flowing_chi_rolls_331650::HandleProc);
    }
};

/// ID: 331647 Deathtouched Brew
class spell_deathtouched_brew_331647 : public AuraScript
{
    PrepareAuraScript(spell_deathtouched_brew_331647);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_deathtouched_brew_331647::CheckProc);
        OnProc += AuraProcFn(spell_deathtouched_brew_331647::HandleProc);
    }
};

/// ID: 331622 Hit Scheme
class spell_hit_scheme_331622 : public AuraScript
{
    PrepareAuraScript(spell_hit_scheme_331622);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_hit_scheme_331622::CheckProc);
        OnProc += AuraProcFn(spell_hit_scheme_331622::HandleProc);
    }
};

/// ID: 331528 Corrosive Dosage
class spell_corrosive_dosage_331528 : public AuraScript
{
    PrepareAuraScript(spell_corrosive_dosage_331528);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_corrosive_dosage_331528::CheckProc);
        OnProc += AuraProcFn(spell_corrosive_dosage_331528::HandleProc);
    }
};

/// ID: 322830 Dark Stalker's Draught
class spell_dark_stalkers_draught_322830 : public AuraScript
{
    PrepareAuraScript(spell_dark_stalkers_draught_322830);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_dark_stalkers_draught_322830::CheckProc);
        OnProc += AuraProcFn(spell_dark_stalkers_draught_322830::HandleProc);
    }
};

/// ID: 322837 Cadaverous Eye
class spell_cadaverous_eye_322837 : public AuraScript
{
    PrepareAuraScript(spell_cadaverous_eye_322837);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_cadaverous_eye_322837::CheckProc);
        OnProc += AuraProcFn(spell_cadaverous_eye_322837::HandleProc);
    }
};

/// ID: 322845 Heart-Piercing Spine
class spell_heartpiercing_spine_322845 : public AuraScript
{
    PrepareAuraScript(spell_heartpiercing_spine_322845);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_heartpiercing_spine_322845::CheckProc);
        OnProc += AuraProcFn(spell_heartpiercing_spine_322845::HandleProc);
    }
};

/// ID: 322851 Soulrender of Zovaal
class spell_soulrender_of_zovaal_322851 : public AuraScript
{
    PrepareAuraScript(spell_soulrender_of_zovaal_322851);

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
    }


    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_soulrender_of_zovaal_322851::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
    }
};

/// ID: 322823 Willbreaker
class spell_willbreaker_322823 : public AuraScript
{
    PrepareAuraScript(spell_willbreaker_322823);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_willbreaker_322823::CheckProc);
        OnProc += AuraProcFn(spell_willbreaker_322823::HandleProc);
    }
};

/// ID: 322826 Felborn Shield
class spell_felborn_shield_322826 : public AuraScript
{
    PrepareAuraScript(spell_felborn_shield_322826);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_felborn_shield_322826::CheckProc);
        OnProc += AuraProcFn(spell_felborn_shield_322826::HandleProc);
    }
};

/// ID: 322829 Fury Wrappings
class spell_fury_wrappings_322829 : public AuraScript
{
    PrepareAuraScript(spell_fury_wrappings_322829);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_fury_wrappings_322829::CheckProc);
        OnProc += AuraProcFn(spell_fury_wrappings_322829::HandleProc);
    }
};

/// ID: 322833 Shield of Unending Fury
class spell_shield_of_unending_fury_322833 : public AuraScript
{
    PrepareAuraScript(spell_shield_of_unending_fury_322833);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_shield_of_unending_fury_322833::CheckProc);
        OnProc += AuraProcFn(spell_shield_of_unending_fury_322833::HandleProc);
    }
};

/// ID: 322844 Blindfold of Focus
class spell_blindfold_of_focus_322844 : public AuraScript
{
    PrepareAuraScript(spell_blindfold_of_focus_322844);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_blindfold_of_focus_322844::CheckProc);
        OnProc += AuraProcFn(spell_blindfold_of_focus_322844::HandleProc);
    }
};

/// ID: 322847 Grim Tinder
class spell_grim_tinder_322847 : public AuraScript
{
    PrepareAuraScript(spell_grim_tinder_322847);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_grim_tinder_322847::CheckProc);
        OnProc += AuraProcFn(spell_grim_tinder_322847::HandleProc);
    }
};

/// ID: 322831 Phantasmal Iris
class spell_phantasmal_iris_322831 : public AuraScript
{
    PrepareAuraScript(spell_phantasmal_iris_322831);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_phantasmal_iris_322831::CheckProc);
        OnProc += AuraProcFn(spell_phantasmal_iris_322831::HandleProc);
    }
};

/// ID: 322832 Darkglare Medallion
class spell_darkglare_medallion_322832 : public AuraScript
{
    PrepareAuraScript(spell_darkglare_medallion_322832);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_darkglare_medallion_322832::CheckProc);
        OnProc += AuraProcFn(spell_darkglare_medallion_322832::HandleProc);
    }
};

/// ID: 322834 Ragehoof
class spell_ragehoof_322834 : public AuraScript
{
    PrepareAuraScript(spell_ragehoof_322834);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_ragehoof_322834::CheckProc);
        OnProc += AuraProcFn(spell_ragehoof_322834::HandleProc);
    }
};

/// ID: 322835 Mark of the Ogre
class spell_mark_of_the_ogre_322835 : public AuraScript
{
    PrepareAuraScript(spell_mark_of_the_ogre_322835);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_mark_of_the_ogre_322835::CheckProc);
        OnProc += AuraProcFn(spell_mark_of_the_ogre_322835::HandleProc);
    }
};

/// ID: 322839 Fleetwing
class spell_fleetwing_322839_AuraScript : public AuraScript
{
    PrepareAuraScript(spell_fleetwing_322839_AuraScript);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_fleetwing_322839_AuraScript::CheckProc);
        OnProc += AuraProcFn(spell_fleetwing_322839_AuraScript::HandleProc);
    }
};

class spell_fleetwing_322839_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_fleetwing_322839_SpellScript);

    void HandleDummy(SpellEffIndex /*eff*/)
    {
    }


    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_fleetwing_322839_SpellScript::HandleDummy, EFFECT_1, SPELL_EFFECT_DUMMY);
    }
};

/// ID: 322846 Resonant Mawfang
class spell_resonant_mawfang_322846 : public AuraScript
{
    PrepareAuraScript(spell_resonant_mawfang_322846);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_resonant_mawfang_322846::CheckProc);
        OnProc += AuraProcFn(spell_resonant_mawfang_322846::HandleProc);
    }
};

/// ID: 320800 Edgelurker
class spell_edgelurker_320800 : public AuraScript
{
    PrepareAuraScript(spell_edgelurker_320800);

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
    }


    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_edgelurker_320800::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

/// ID: 326579 Torghast Ambassador
class spell_torghast_ambassador_326579_AuraScript : public AuraScript
{
    PrepareAuraScript(spell_torghast_ambassador_326579_AuraScript);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_torghast_ambassador_326579_AuraScript::CheckProc);
        OnProc += AuraProcFn(spell_torghast_ambassador_326579_AuraScript::HandleProc);
    }
};

class spell_torghast_ambassador_326579_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_torghast_ambassador_326579_SpellScript);

    void HandleDummy(SpellEffIndex /*eff*/)
    {
    }


    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_torghast_ambassador_326579_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

/// ID: 329605 Power Overwhelming
class spell_power_overwhelming_329605 : public AuraScript
{
    PrepareAuraScript(spell_power_overwhelming_329605);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_power_overwhelming_329605::CheckProc);
        OnProc += AuraProcFn(spell_power_overwhelming_329605::HandleProc);
    }
};

/// ID: 330551 Spellweaver's Mojo
class spell_spellweavers_mojo_330551 : public AuraScript
{
    PrepareAuraScript(spell_spellweavers_mojo_330551);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_spellweavers_mojo_330551::CheckProc);
        OnProc += AuraProcFn(spell_spellweavers_mojo_330551::HandleProc);
    }
};

/// ID: 330630 Gravity Dynamo
class spell_gravity_dynamo_330630 : public AuraScript
{
    PrepareAuraScript(spell_gravity_dynamo_330630);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_gravity_dynamo_330630::CheckProc);
        OnProc += AuraProcFn(spell_gravity_dynamo_330630::HandleProc);
    }
};

/// ID: 329970 Orbit Breaker
class spell_orbit_breaker_329970 : public AuraScript
{
    PrepareAuraScript(spell_orbit_breaker_329970);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_orbit_breaker_329970::CheckProc);
        OnProc += AuraProcFn(spell_orbit_breaker_329970::HandleProc);
    }
};

/// ID: 329969 Sylvatican Charm
class spell_sylvatican_charm_329969 : public AuraScript
{
    PrepareAuraScript(spell_sylvatican_charm_329969);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_sylvatican_charm_329969::CheckProc);
        OnProc += AuraProcFn(spell_sylvatican_charm_329969::HandleProc);
    }
};

/// ID: 329960 Lycara's Bargain
class spell_lycaras_bargain_329960 : public AuraScript
{
    PrepareAuraScript(spell_lycaras_bargain_329960);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_lycaras_bargain_329960::CheckProc);
        OnProc += AuraProcFn(spell_lycaras_bargain_329960::HandleProc);
    }
};

/// ID: 330855 Creeping Freeze
class spell_creeping_freeze_330855 : public AuraScript
{
    PrepareAuraScript(spell_creeping_freeze_330855);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_creeping_freeze_330855::CheckProc);
        OnProc += AuraProcFn(spell_creeping_freeze_330855::HandleProc);
    }
};

/// ID: 331375 Revitalizing Spirit
class spell_revitalizing_spirit_331375 : public AuraScript
{
    PrepareAuraScript(spell_revitalizing_spirit_331375);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_revitalizing_spirit_331375::CheckProc);
        OnProc += AuraProcFn(spell_revitalizing_spirit_331375::HandleProc);
    }
};

/// ID: 332216 Chains of Anguish
class spell_chains_of_anguish_332216 : public AuraScript
{
    PrepareAuraScript(spell_chains_of_anguish_332216);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_chains_of_anguish_332216::CheckProc);
        OnProc += AuraProcFn(spell_chains_of_anguish_332216::HandleProc);
    }
};

/// ID: 332212 Occult Emitter
class spell_occult_emitter_332212 : public AuraScript
{
    PrepareAuraScript(spell_occult_emitter_332212);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_occult_emitter_332212::CheckProc);
        OnProc += AuraProcFn(spell_occult_emitter_332212::HandleProc);
    }
};

/// ID: 332199 Phearomones
class spell_phearomones_332199 : public AuraScript
{
    PrepareAuraScript(spell_phearomones_332199);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_phearomones_332199::CheckProc);
        OnProc += AuraProcFn(spell_phearomones_332199::HandleProc);
    }
};

/// ID: 332163 Hungerstone
class spell_hungerstone_332163 : public AuraScript
{
    PrepareAuraScript(spell_hungerstone_332163);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_hungerstone_332163::CheckProc);
        OnProc += AuraProcFn(spell_hungerstone_332163::HandleProc);
    }
};

/// ID: 331921 Tome of Swordplay
class spell_tome_of_swordplay_331921 : public AuraScript
{
    PrepareAuraScript(spell_tome_of_swordplay_331921);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_tome_of_swordplay_331921::CheckProc);
        OnProc += AuraProcFn(spell_tome_of_swordplay_331921::HandleProc);
    }
};

/// ID: 332532 Boundless Fortitude
class spell_boundless_fortitude_332532 : public AuraScript
{
    PrepareAuraScript(spell_boundless_fortitude_332532);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_boundless_fortitude_332532::CheckProc);
        OnProc += AuraProcFn(spell_boundless_fortitude_332532::HandleProc);
    }
};

/// ID: 332366 Ancient Drake Breath
class spell_ancient_drake_breath_332366 : public AuraScript
{
    PrepareAuraScript(spell_ancient_drake_breath_332366);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_ancient_drake_breath_332366::CheckProc);
        OnProc += AuraProcFn(spell_ancient_drake_breath_332366::HandleProc);
    }
};

/// ID: 332578 Bone Growing Juice
class spell_bone_growing_juice_332578 : public AuraScript
{
    PrepareAuraScript(spell_bone_growing_juice_332578);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_bone_growing_juice_332578::CheckProc);
        OnProc += AuraProcFn(spell_bone_growing_juice_332578::HandleProc);
    }
};

/// ID: 332685 Plaguebringer
class spell_plaguebringer_332685 : public AuraScript
{
    PrepareAuraScript(spell_plaguebringer_332685);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_plaguebringer_332685::CheckProc);
        OnProc += AuraProcFn(spell_plaguebringer_332685::HandleProc);
    }
};

/// ID: 332592 Theory of Justice
class spell_theory_of_justice_332592 : public AuraScript
{
    PrepareAuraScript(spell_theory_of_justice_332592);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_theory_of_justice_332592::CheckProc);
        OnProc += AuraProcFn(spell_theory_of_justice_332592::HandleProc);
    }
};

/// ID: 332799 Blood Beacon
class spell_blood_beacon_332799_AuraScript : public AuraScript
{
    PrepareAuraScript(spell_blood_beacon_332799_AuraScript);

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
    }


    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_blood_beacon_332799_AuraScript::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

class spell_blood_beacon_332799_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_blood_beacon_332799_SpellScript);

    void HandleDummy(SpellEffIndex /*eff*/)
    {
    }


    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_blood_beacon_332799_SpellScript::HandleDummy, EFFECT_1, SPELL_EFFECT_DUMMY);
    }
};

/// ID: 332800 Pendrake's Visor
class spell_pendrakes_visor_332800 : public AuraScript
{
    PrepareAuraScript(spell_pendrakes_visor_332800);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_pendrakes_visor_332800::CheckProc);
        OnProc += AuraProcFn(spell_pendrakes_visor_332800::HandleProc);
    }
};

/// ID: 332803 Gavel of True Judgment
class spell_gavel_of_true_judgment_332803 : public AuraScript
{
    PrepareAuraScript(spell_gavel_of_true_judgment_332803);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_gavel_of_true_judgment_332803::CheckProc);
        OnProc += AuraProcFn(spell_gavel_of_true_judgment_332803::HandleProc);
    }
};

/// ID: 332806 Badge of the Mad Paragon
class spell_badge_of_the_mad_paragon_332806 : public AuraScript
{
    PrepareAuraScript(spell_badge_of_the_mad_paragon_332806);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_badge_of_the_mad_paragon_332806::CheckProc);
        OnProc += AuraProcFn(spell_badge_of_the_mad_paragon_332806::HandleProc);
    }
};

/// ID: 332939 Mark of Conk-quest
class spell_mark_of_conkquest_332939 : public AuraScript
{
    PrepareAuraScript(spell_mark_of_conkquest_332939);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_mark_of_conkquest_332939::CheckProc);
        OnProc += AuraProcFn(spell_mark_of_conkquest_332939::HandleProc);
    }
};

/// ID: 333093 Unstable Containment Crystal
class spell_unstable_containment_crystal_333093 : public AuraScript
{
    PrepareAuraScript(spell_unstable_containment_crystal_333093);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_unstable_containment_crystal_333093::CheckProc);
        OnProc += AuraProcFn(spell_unstable_containment_crystal_333093::HandleProc);
    }
};

/// ID: 332887 Smoking Ash Pile
class spell_smoking_ash_pile_332887 : public AuraScript
{
    PrepareAuraScript(spell_smoking_ash_pile_332887);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_smoking_ash_pile_332887::CheckProc);
        OnProc += AuraProcFn(spell_smoking_ash_pile_332887::HandleProc);
    }
};

/// ID: 333029 Accursed Hand Wraps
class spell_accursed_hand_wraps_333029 : public AuraScript
{
    PrepareAuraScript(spell_accursed_hand_wraps_333029);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_accursed_hand_wraps_333029::CheckProc);
        OnProc += AuraProcFn(spell_accursed_hand_wraps_333029::HandleProc);
    }
};

/// ID: 333334 Fossilized Bone Fragments
class spell_fossilized_bone_fragments_333334 : public AuraScript
{
    PrepareAuraScript(spell_fossilized_bone_fragments_333334);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_fossilized_bone_fragments_333334::CheckProc);
        OnProc += AuraProcFn(spell_fossilized_bone_fragments_333334::HandleProc);
    }
};

/// ID: 333352 Seeds of Rampant Growth
class spell_seeds_of_rampant_growth_333352 : public AuraScript
{
    PrepareAuraScript(spell_seeds_of_rampant_growth_333352);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_seeds_of_rampant_growth_333352::CheckProc);
        OnProc += AuraProcFn(spell_seeds_of_rampant_growth_333352::HandleProc);
    }
};

/// ID: 333357 Elemental Conduit
class spell_elemental_conduit_333357 : public AuraScript
{
    PrepareAuraScript(spell_elemental_conduit_333357);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_elemental_conduit_333357::CheckProc);
        OnProc += AuraProcFn(spell_elemental_conduit_333357::HandleProc);
    }
};

/// ID: 333366 Crystallized Elemental Heart
class spell_crystallized_elemental_heart_333366 : public AuraScript
{
    PrepareAuraScript(spell_crystallized_elemental_heart_333366);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_crystallized_elemental_heart_333366::CheckProc);
        OnProc += AuraProcFn(spell_crystallized_elemental_heart_333366::HandleProc);
    }
};

/// ID: 333598 Pridebreaker's Anvil
class spell_pridebreakers_anvil_333598 : public AuraScript
{
    PrepareAuraScript(spell_pridebreakers_anvil_333598);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_pridebreakers_anvil_333598::CheckProc);
        OnProc += AuraProcFn(spell_pridebreakers_anvil_333598::HandleProc);
    }
};

/// ID: 333620 Distillation of Sin
class spell_distillation_of_sin_333620 : public AuraScript
{
    PrepareAuraScript(spell_distillation_of_sin_333620);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_distillation_of_sin_333620::CheckProc);
        OnProc += AuraProcFn(spell_distillation_of_sin_333620::HandleProc);
    }
};

/// ID: 333937 Livingwood Pommel
class spell_livingwood_pommel_333937 : public AuraScript
{
    PrepareAuraScript(spell_livingwood_pommel_333937);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_livingwood_pommel_333937::CheckProc);
        OnProc += AuraProcFn(spell_livingwood_pommel_333937::HandleProc);
    }
};

/// ID: 333949 Petrified Wildseed
class spell_petrified_wildseed_333949 : public AuraScript
{
    PrepareAuraScript(spell_petrified_wildseed_333949);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_petrified_wildseed_333949::CheckProc);
        OnProc += AuraProcFn(spell_petrified_wildseed_333949::HandleProc);
    }
};

/// ID: 334005 Perpetual Sinstone
class spell_perpetual_sinstone_334005 : public AuraScript
{
    PrepareAuraScript(spell_perpetual_sinstone_334005);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_perpetual_sinstone_334005::CheckProc);
        OnProc += AuraProcFn(spell_perpetual_sinstone_334005::HandleProc);
    }
};

/// ID: 334393 Draught of Waning Twilight
class spell_draught_of_waning_twilight_334393 : public AuraScript
{
    PrepareAuraScript(spell_draught_of_waning_twilight_334393);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_draught_of_waning_twilight_334393::CheckProc);
        OnProc += AuraProcFn(spell_draught_of_waning_twilight_334393::HandleProc);
    }
};

/// ID: 334592 Soulborne Clasp
class spell_soulborne_clasp_334592 : public AuraScript
{
    PrepareAuraScript(spell_soulborne_clasp_334592);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_soulborne_clasp_334592::CheckProc);
        OnProc += AuraProcFn(spell_soulborne_clasp_334592::HandleProc);
    }
};

/// ID: 334992 Thread of Beads
class spell_thread_of_beads_334992 : public AuraScript
{
    PrepareAuraScript(spell_thread_of_beads_334992);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_thread_of_beads_334992::CheckProc);
        OnProc += AuraProcFn(spell_thread_of_beads_334992::HandleProc);
    }
};

/// ID: 335054 Faintly Glowing Ember
class spell_faintly_glowing_ember_335054 : public AuraScript
{
    PrepareAuraScript(spell_faintly_glowing_ember_335054);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_faintly_glowing_ember_335054::CheckProc);
        OnProc += AuraProcFn(spell_faintly_glowing_ember_335054::HandleProc);
    }
};

/// ID: 335069 Negative Energy Token
class spell_negative_energy_token_335069 : public AuraScript
{
    PrepareAuraScript(spell_negative_energy_token_335069);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_negative_energy_token_335069::CheckProc);
        OnProc += AuraProcFn(spell_negative_energy_token_335069::HandleProc);
    }
};

/// ID: 335095 Shard of Milkglass
class spell_shard_of_milkglass_335095 : public AuraScript
{
    PrepareAuraScript(spell_shard_of_milkglass_335095);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_shard_of_milkglass_335095::CheckProc);
        OnProc += AuraProcFn(spell_shard_of_milkglass_335095::HandleProc);
    }
};

/// ID: 332808 Pendrake's Shattered Aegis
class spell_pendrakes_shattered_aegis_332808 : public AuraScript
{
    PrepareAuraScript(spell_pendrakes_shattered_aegis_332808);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_pendrakes_shattered_aegis_332808::CheckProc);
        OnProc += AuraProcFn(spell_pendrakes_shattered_aegis_332808::HandleProc);
    }
};

/// ID: 335566 Bag of Munitions
class spell_bag_of_munitions_335566 : public AuraScript
{
    PrepareAuraScript(spell_bag_of_munitions_335566);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_bag_of_munitions_335566::CheckProc);
        OnProc += AuraProcFn(spell_bag_of_munitions_335566::HandleProc);
    }
};

/// ID: 336485 Undead Bone Ash
class spell_undead_bone_ash_336485 : public AuraScript
{
    PrepareAuraScript(spell_undead_bone_ash_336485);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_undead_bone_ash_336485::CheckProc);
        OnProc += AuraProcFn(spell_undead_bone_ash_336485::HandleProc);
    }
};

/// ID: 336615 Darkened Ember
class spell_darkened_ember_336615 : public AuraScript
{
    PrepareAuraScript(spell_darkened_ember_336615);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_darkened_ember_336615::CheckProc);
        OnProc += AuraProcFn(spell_darkened_ember_336615::HandleProc);
    }
};

/// ID: 336625 Tome of the Vanquished
class spell_tome_of_the_vanquished_336625 : public AuraScript
{
    PrepareAuraScript(spell_tome_of_the_vanquished_336625);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_tome_of_the_vanquished_336625::CheckProc);
        OnProc += AuraProcFn(spell_tome_of_the_vanquished_336625::HandleProc);
    }
};

/// ID: 337585 The Stone Ward
class spell_the_stone_ward_337585 : public AuraScript
{
    PrepareAuraScript(spell_the_stone_ward_337585);

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
    }


    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_the_stone_ward_337585::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

/// ID: 337613 Erratic Howler
class spell_erratic_howler_337613 : public AuraScript
{
    PrepareAuraScript(spell_erratic_howler_337613);

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
    }


    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_erratic_howler_337613::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

/// ID: 337620 Unstable Form
class spell_unstable_form_337620 : public AuraScript
{
    PrepareAuraScript(spell_unstable_form_337620);

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
    }


    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_unstable_form_337620::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

/// ID: 337657 The Fifth Skull
class spell_the_fifth_skull_337657 : public AuraScript
{
    PrepareAuraScript(spell_the_fifth_skull_337657);

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
    }


    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_the_fifth_skull_337657::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

/// ID: 337719 Heart-Seeking Fang
class spell_heartseeking_fang_337719 : public AuraScript
{
    PrepareAuraScript(spell_heartseeking_fang_337719);

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
    }


    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_heartseeking_fang_337719::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

/// ID: 337728 Kerim's Amulet of Laceration
class spell_kerims_amulet_of_laceration_337728 : public AuraScript
{
    PrepareAuraScript(spell_kerims_amulet_of_laceration_337728);

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
    }


    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_kerims_amulet_of_laceration_337728::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

/// ID: 337765 Reinforced Lure Casing
class spell_reinforced_lure_casing_337765 : public AuraScript
{
    PrepareAuraScript(spell_reinforced_lure_casing_337765);

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
    }


    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_reinforced_lure_casing_337765::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

/// ID: 337878 Dark Fortress
class spell_dark_fortress_337878 : public AuraScript
{
    PrepareAuraScript(spell_dark_fortress_337878);

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
    }


    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_dark_fortress_337878::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

/// ID: 337881 Fallen Armaments
class spell_fallen_armaments_337881 : public AuraScript
{
    PrepareAuraScript(spell_fallen_armaments_337881);

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
    }


    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_fallen_armaments_337881::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

/// ID: 337928 Potent Acid Gland
class spell_potent_acid_gland_337928 : public AuraScript
{
    PrepareAuraScript(spell_potent_acid_gland_337928);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_potent_acid_gland_337928::CheckProc);
        OnProc += AuraProcFn(spell_potent_acid_gland_337928::HandleProc);
    }
};

/// ID: 337938 Lumbering Form
class spell_lumbering_form_337938 : public AuraScript
{
    PrepareAuraScript(spell_lumbering_form_337938);

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
    }


    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_lumbering_form_337938::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

/// ID: 338023 Irritating Moth Dust
class spell_irritating_moth_dust_338023 : public AuraScript
{
    PrepareAuraScript(spell_irritating_moth_dust_338023);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_irritating_moth_dust_338023::CheckProc);
        OnProc += AuraProcFn(spell_irritating_moth_dust_338023::HandleProc);
    }
};

/// ID: 338029 Shimmering Wingcape
class spell_shimmering_wingcape_338029 : public AuraScript
{
    PrepareAuraScript(spell_shimmering_wingcape_338029);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_shimmering_wingcape_338029::CheckProc);
        OnProc += AuraProcFn(spell_shimmering_wingcape_338029::HandleProc);
    }
};

/// ID: 338072 Gruul's Shattered Toenail
class spell_gruuls_shattered_toenail_338072 : public AuraScript
{
    PrepareAuraScript(spell_gruuls_shattered_toenail_338072);

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
    }


    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_gruuls_shattered_toenail_338072::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

/// ID: 338446 Coffer of Spectral Whispers
class spell_coffer_of_spectral_whispers_338446 : public AuraScript
{
    PrepareAuraScript(spell_coffer_of_spectral_whispers_338446);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_coffer_of_spectral_whispers_338446::CheckProc);
        OnProc += AuraProcFn(spell_coffer_of_spectral_whispers_338446::HandleProc);
    }
};

/// ID: 338512 Gaze of Death
class spell_gaze_of_death_338512 : public AuraScript
{
    PrepareAuraScript(spell_gaze_of_death_338512);

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
    }


    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_gaze_of_death_338512::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
    }
};

/// ID: 338596 Defiance of Death
class spell_defiance_of_death_338596 : public SpellScript
{
    PrepareSpellScript(spell_defiance_of_death_338596);

    void HandleDummy(SpellEffIndex /*eff*/)
    {
    }


    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_defiance_of_death_338596::HandleDummy, EFFECT_1, SPELL_EFFECT_DUMMY);
    }
};

/// ID: 338616 Pulsing Rot-hive
class spell_pulsing_rothive_338616 : public AuraScript
{
    PrepareAuraScript(spell_pulsing_rothive_338616);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_pulsing_rothive_338616::CheckProc);
        OnProc += AuraProcFn(spell_pulsing_rothive_338616::HandleProc);
    }
};

/// ID: 338922 Soulward Clasp
class spell_soulward_clasp_338922 : public AuraScript
{
    PrepareAuraScript(spell_soulward_clasp_338922);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_soulward_clasp_338922::CheckProc);
        OnProc += AuraProcFn(spell_soulward_clasp_338922::HandleProc);
    }
};

/// ID: 338948 V'lara's Cape of Subterfuge
class spell_vlaras_cape_of_subterfuge_338948 : public AuraScript
{
    PrepareAuraScript(spell_vlaras_cape_of_subterfuge_338948);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_vlaras_cape_of_subterfuge_338948::CheckProc);
        OnProc += AuraProcFn(spell_vlaras_cape_of_subterfuge_338948::HandleProc);
    }
};

/// ID: 340451 Form of Darkness
class spell_form_of_darkness_340451 : public AuraScript
{
    PrepareAuraScript(spell_form_of_darkness_340451);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_form_of_darkness_340451::CheckProc);
        OnProc += AuraProcFn(spell_form_of_darkness_340451::HandleProc);
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_form_of_darkness_340451::HandlePeriodic, EFFECT_1, SPELL_AURA_PERIODIC_DUMMY);
    }
};

/// ID: 341137 Writhing Shadow-Tendrils
class spell_writhing_shadowtendrils_341137 : public AuraScript
{
    PrepareAuraScript(spell_writhing_shadowtendrils_341137);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_writhing_shadowtendrils_341137::CheckProc);
        OnProc += AuraProcFn(spell_writhing_shadowtendrils_341137::HandleProc);
    }
};

/// ID: 340725 Engorged Limb
class spell_engorged_limb_340725 : public AuraScript
{
    PrepareAuraScript(spell_engorged_limb_340725);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_engorged_limb_340725::CheckProc);
        OnProc += AuraProcFn(spell_engorged_limb_340725::HandleProc);
    }
};

/// ID: 340928 Formless Executioner
class spell_formless_executioner_340928 : public AuraScript
{
    PrepareAuraScript(spell_formless_executioner_340928);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_formless_executioner_340928::CheckProc);
        OnProc += AuraProcFn(spell_formless_executioner_340928::HandleProc);
    }
};

/// ID: 341324 Uncontrolled Darkness
class spell_uncontrolled_darkness_341324_AuraScript : public AuraScript
{
    PrepareAuraScript(spell_uncontrolled_darkness_341324_AuraScript);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_uncontrolled_darkness_341324_AuraScript::CheckProc);
        OnProc += AuraProcFn(spell_uncontrolled_darkness_341324_AuraScript::HandleProc);
    }
};

class spell_uncontrolled_darkness_341324_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_uncontrolled_darkness_341324_SpellScript);

    void HandleDummy(SpellEffIndex /*eff*/)
    {
    }


    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_uncontrolled_darkness_341324_SpellScript::HandleDummy, EFFECT_1, SPELL_EFFECT_DUMMY);
    }
};

/// ID: 342387 Baroness' Lost Plagueloop
class spell_baroness_lost_plagueloop_342387 : public AuraScript
{
    PrepareAuraScript(spell_baroness_lost_plagueloop_342387);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_baroness_lost_plagueloop_342387::CheckProc);
        OnProc += AuraProcFn(spell_baroness_lost_plagueloop_342387::HandleProc);
    }
};

/// ID: 342390 Maldo's Soul Exploder
class spell_maldos_soul_exploder_342390 : public AuraScript
{
    PrepareAuraScript(spell_maldos_soul_exploder_342390);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_maldos_soul_exploder_342390::CheckProc);
        OnProc += AuraProcFn(spell_maldos_soul_exploder_342390::HandleProc);
    }
};

/// ID: 342412 Earworm
class spell_earworm_342412 : public AuraScript
{
    PrepareAuraScript(spell_earworm_342412);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_earworm_342412::CheckProc);
        OnProc += AuraProcFn(spell_earworm_342412::HandleProc);
    }
};

/// ID: 342632 Malevolent Stitching
class spell_malevolent_stitching_342632 : public AuraScript
{
    PrepareAuraScript(spell_malevolent_stitching_342632);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_malevolent_stitching_342632::CheckProc);
        OnProc += AuraProcFn(spell_malevolent_stitching_342632::HandleProc);
    }
};

/// ID: 342757 Clinging Fog
class spell_clinging_fog_342757 : public AuraScript
{
    PrepareAuraScript(spell_clinging_fog_342757);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_clinging_fog_342757::CheckProc);
        OnProc += AuraProcFn(spell_clinging_fog_342757::HandleProc);
    }
};

/// ID: 342779 Crystallized Dreams
class spell_crystallized_dreams_342779 : public AuraScript
{
    PrepareAuraScript(spell_crystallized_dreams_342779);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_crystallized_dreams_342779::CheckProc);
        OnProc += AuraProcFn(spell_crystallized_dreams_342779::HandleProc);
    }
};

/// ID: 342793 Murmuring Shawl
class spell_murmuring_shawl_342793 : public AuraScript
{
    PrepareAuraScript(spell_murmuring_shawl_342793);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_murmuring_shawl_342793::CheckProc);
        OnProc += AuraProcFn(spell_murmuring_shawl_342793::HandleProc);
    }
};

/// ID: 342799 Gnarled Key
class spell_gnarled_key_342799 : public AuraScript
{
    PrepareAuraScript(spell_gnarled_key_342799);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_gnarled_key_342799::CheckProc);
        OnProc += AuraProcFn(spell_gnarled_key_342799::HandleProc);
    }
};

/// ID: 347962 The Stone Ward
class spell_the_stone_ward_347962 : public AuraScript
{
    PrepareAuraScript(spell_the_stone_ward_347962);

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
    }


    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_the_stone_ward_347962::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

/// ID: 347969 Elethium Diffuser
class spell_elethium_diffuser_347969 : public AuraScript
{
    PrepareAuraScript(spell_elethium_diffuser_347969);

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
    }


    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_elethium_diffuser_347969::HandlePeriodic, EFFECT_2, SPELL_AURA_PERIODIC_DUMMY);
    }
};

/// ID: 347972 Huddled Carvings
class spell_huddled_carvings_347972 : public AuraScript
{
    PrepareAuraScript(spell_huddled_carvings_347972);

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
    }


    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_huddled_carvings_347972::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
    }
};

/// ID: 347975 Tremorbeast Heart
class spell_tremorbeast_heart_347975 : public AuraScript
{
    PrepareAuraScript(spell_tremorbeast_heart_347975);

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
    }


    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_tremorbeast_heart_347975::HandlePeriodic, EFFECT_1, SPELL_AURA_PERIODIC_HEAL);
    }
};

/// ID: 347976 Blade of the Lifetaker
class spell_blade_of_the_lifetaker_347976 : public AuraScript
{
    PrepareAuraScript(spell_blade_of_the_lifetaker_347976);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_blade_of_the_lifetaker_347976::CheckProc);
        OnProc += AuraProcFn(spell_blade_of_the_lifetaker_347976::HandleProc);
    }
};

/// ID: 347980 Unstable Form
class spell_unstable_form_347980 : public AuraScript
{
    PrepareAuraScript(spell_unstable_form_347980);

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
    }


    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_unstable_form_347980::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

/// ID: 347985 V'lara's Cape of Subterfuge
class spell_vlaras_cape_of_subterfuge_347985 : public AuraScript
{
    PrepareAuraScript(spell_vlaras_cape_of_subterfuge_347985);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_vlaras_cape_of_subterfuge_347985::CheckProc);
        OnProc += AuraProcFn(spell_vlaras_cape_of_subterfuge_347985::HandleProc);
    }
};

/// ID: 347988 Ten of Towers
class spell_ten_of_towers_347988 : public AuraScript
{
    PrepareAuraScript(spell_ten_of_towers_347988);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_ten_of_towers_347988::CheckProc);
        OnProc += AuraProcFn(spell_ten_of_towers_347988::HandleProc);
    }
};

/// ID: 348025 Potent Acid Gland
class spell_potent_acid_gland_348025 : public AuraScript
{
    PrepareAuraScript(spell_potent_acid_gland_348025);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_potent_acid_gland_348025::CheckProc);
        OnProc += AuraProcFn(spell_potent_acid_gland_348025::HandleProc);
    }
};

/// ID: 348027 Erratic Howler
class spell_erratic_howler_348027 : public AuraScript
{
    PrepareAuraScript(spell_erratic_howler_348027);

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
    }


    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_erratic_howler_348027::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

/// ID: 348043 Lumbering Form
class spell_lumbering_form_348043 : public AuraScript
{
    PrepareAuraScript(spell_lumbering_form_348043);

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
    }


    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_lumbering_form_348043::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

/// ID: 348048 Heart-Seeking Fang
class spell_heartseeking_fang_348048 : public AuraScript
{
    PrepareAuraScript(spell_heartseeking_fang_348048);

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
    }


    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_heartseeking_fang_348048::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

/// ID: 348059 Twisted Samophlange
class spell_twisted_samophlange_348059 : public AuraScript
{
    PrepareAuraScript(spell_twisted_samophlange_348059);

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
    }


    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_twisted_samophlange_348059::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

/// ID: 348063 Disembodied Mystic Hands
class spell_disembodied_mystic_hands_348063 : public AuraScript
{
    PrepareAuraScript(spell_disembodied_mystic_hands_348063);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_disembodied_mystic_hands_348063::CheckProc);
        OnProc += AuraProcFn(spell_disembodied_mystic_hands_348063::HandleProc);
    }
};

/// ID: 348482 Notched Axe Head
class spell_notched_axe_head_348482 : public AuraScript
{
    PrepareAuraScript(spell_notched_axe_head_348482);

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
    }


    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_notched_axe_head_348482::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
    }
};

/// ID: 348483 Tarnished Medallion
class spell_tarnished_medallion_348483 : public AuraScript
{
    PrepareAuraScript(spell_tarnished_medallion_348483);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_tarnished_medallion_348483::CheckProc);
        OnProc += AuraProcFn(spell_tarnished_medallion_348483::HandleProc);
    }
};

/// ID: 348511 Bloodgorged Leech
class spell_bloodgorged_leech_348511 : public AuraScript
{
    PrepareAuraScript(spell_bloodgorged_leech_348511);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_bloodgorged_leech_348511::CheckProc);
        OnProc += AuraProcFn(spell_bloodgorged_leech_348511::HandleProc);
    }
};

/// ID: 348541 Refilling Elixir of Life
class spell_refilling_elixir_of_life_348541 : public AuraScript
{
    PrepareAuraScript(spell_refilling_elixir_of_life_348541);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_refilling_elixir_of_life_348541::CheckProc);
        OnProc += AuraProcFn(spell_refilling_elixir_of_life_348541::HandleProc);
    }
};

/// ID: 348545 Orb of Replenishment
class spell_orb_of_replenishment_348545 : public AuraScript
{
    PrepareAuraScript(spell_orb_of_replenishment_348545);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_orb_of_replenishment_348545::CheckProc);
        OnProc += AuraProcFn(spell_orb_of_replenishment_348545::HandleProc);
    }
};

/// ID: 348908 Ethereal Wildseed
class spell_ethereal_wildseed_348908 : public AuraScript
{
    PrepareAuraScript(spell_ethereal_wildseed_348908);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_ethereal_wildseed_348908::CheckProc);
        OnProc += AuraProcFn(spell_ethereal_wildseed_348908::HandleProc);
    }
};

/// ID: 349916 Weathered Runestone
class spell_weathered_runestone_349916 : public AuraScript
{
    PrepareAuraScript(spell_weathered_runestone_349916);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_weathered_runestone_349916::CheckProc);
        OnProc += AuraProcFn(spell_weathered_runestone_349916::HandleProc);
    }
};

/// ID: 349944 Thorium Hairpin
class spell_thorium_hairpin_349944 : public AuraScript
{
    PrepareAuraScript(spell_thorium_hairpin_349944);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_thorium_hairpin_349944::CheckProc);
        OnProc += AuraProcFn(spell_thorium_hairpin_349944::HandleProc);
    }
};

/// ID: 350007 Gargolmar's Shattered Hand
class spell_gargolmars_shattered_hand_350007 : public AuraScript
{
    PrepareAuraScript(spell_gargolmars_shattered_hand_350007);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_gargolmars_shattered_hand_350007::CheckProc);
        OnProc += AuraProcFn(spell_gargolmars_shattered_hand_350007::HandleProc);
    }
};

/// ID: 350060 Ancient Rubble
class spell_ancient_rubble_350060 : public AuraScript
{
    PrepareAuraScript(spell_ancient_rubble_350060);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_ancient_rubble_350060::CheckProc);
        OnProc += AuraProcFn(spell_ancient_rubble_350060::HandleProc);
    }
};

/// ID: 350065 Blade of the Tideskorn
class spell_blade_of_the_tideskorn_350065 : public AuraScript
{
    PrepareAuraScript(spell_blade_of_the_tideskorn_350065);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_blade_of_the_tideskorn_350065::CheckProc);
        OnProc += AuraProcFn(spell_blade_of_the_tideskorn_350065::HandleProc);
    }
};

/// ID: 350117 Soul of an Archon
class spell_soul_of_an_archon_350117 : public AuraScript
{
    PrepareAuraScript(spell_soul_of_an_archon_350117);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_soul_of_an_archon_350117::CheckProc);
        OnProc += AuraProcFn(spell_soul_of_an_archon_350117::HandleProc);
    }
};

/// ID: 350129 Dark Technique
class spell_dark_technique_350129 : public AuraScript
{
    PrepareAuraScript(spell_dark_technique_350129);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_dark_technique_350129::CheckProc);
        OnProc += AuraProcFn(spell_dark_technique_350129::HandleProc);
    }
};

/// ID: 350248 Depleted Tesla Coil
class spell_depleted_tesla_coil_350248 : public AuraScript
{
    PrepareAuraScript(spell_depleted_tesla_coil_350248);

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
    }


    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_depleted_tesla_coil_350248::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

/// ID: 332543 Entropic Pool
class spell_entropic_pool_332543 : public AuraScript
{
    PrepareAuraScript(spell_entropic_pool_332543);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_entropic_pool_332543::CheckProc);
        OnProc += AuraProcFn(spell_entropic_pool_332543::HandleProc);
    }
};

/// ID: 353743 Soulward Clasp
class spell_soulward_clasp_353743 : public AuraScript
{
    PrepareAuraScript(spell_soulward_clasp_353743);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_soulward_clasp_353743::CheckProc);
        OnProc += AuraProcFn(spell_soulward_clasp_353743::HandleProc);
    }
};

/// ID: 353747 Pulsing Rot-hive
class spell_pulsing_rothive_353747 : public AuraScript
{
    PrepareAuraScript(spell_pulsing_rothive_353747);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_pulsing_rothive_353747::CheckProc);
        OnProc += AuraProcFn(spell_pulsing_rothive_353747::HandleProc);
    }
};

/// ID: 354487 Unhindered Soul
class spell_unhindered_soul_354487 : public SpellScript
{
    PrepareSpellScript(spell_unhindered_soul_354487);

    void HandleDummy1(SpellEffIndex /*eff*/)
    {
    }


    void HandleDummy2(SpellEffIndex /*eff*/)
    {
    }


    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_unhindered_soul_354487::HandleDummy1, EFFECT_0, SPELL_EFFECT_DUMMY);
        OnEffectHitTarget += SpellEffectFn(spell_unhindered_soul_354487::HandleDummy2, EFFECT_1, SPELL_EFFECT_DUMMY);
    }
};

/// ID: 354460 Mawsworn Strength
class spell_mawsworn_strength_354460 : public SpellScript
{
    PrepareSpellScript(spell_mawsworn_strength_354460);

    void HandleDummy1(SpellEffIndex /*eff*/)
    {
    }


    void HandleDummy2(SpellEffIndex /*eff*/)
    {
    }


    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_mawsworn_strength_354460::HandleDummy1, EFFECT_0, SPELL_EFFECT_DUMMY);
        OnEffectHitTarget += SpellEffectFn(spell_mawsworn_strength_354460::HandleDummy2, EFFECT_1, SPELL_EFFECT_DUMMY);
    }
};

/// ID: 354483 Spectral Assassin
class spell_spectral_assassin_354483 : public SpellScript
{
    PrepareSpellScript(spell_spectral_assassin_354483);

    void HandleDummy1(SpellEffIndex /*eff*/)
    {
    }


    void HandleDummy2(SpellEffIndex /*eff*/)
    {
    }


    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_spectral_assassin_354483::HandleDummy1, EFFECT_0, SPELL_EFFECT_DUMMY);
        OnEffectHitTarget += SpellEffectFn(spell_spectral_assassin_354483::HandleDummy2, EFFECT_1, SPELL_EFFECT_DUMMY);
    }
};

/// ID: 354480 Portal To The Unknown
class spell_portal_to_the_unknown_354480 : public SpellScript
{
    PrepareSpellScript(spell_portal_to_the_unknown_354480);

    void HandleDummy1(SpellEffIndex /*eff*/)
    {
    }


    void HandleDummy2(SpellEffIndex /*eff*/)
    {
    }


    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_portal_to_the_unknown_354480::HandleDummy1, EFFECT_0, SPELL_EFFECT_DUMMY);
        OnEffectHitTarget += SpellEffectFn(spell_portal_to_the_unknown_354480::HandleDummy2, EFFECT_1, SPELL_EFFECT_DUMMY);
    }
};

/// ID: 354478 Impressive Size
class spell_impressive_size_354478 : public SpellScript
{
    PrepareSpellScript(spell_impressive_size_354478);

    void HandleDummy1(SpellEffIndex /*eff*/)
    {
    }


    void HandleDummy2(SpellEffIndex /*eff*/)
    {
    }


    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_impressive_size_354478::HandleDummy1, EFFECT_0, SPELL_EFFECT_DUMMY);
        OnEffectHitTarget += SpellEffectFn(spell_impressive_size_354478::HandleDummy2, EFFECT_1, SPELL_EFFECT_DUMMY);
    }
};

/// ID: 354481 Inner Child
class spell_inner_child_354481 : public SpellScript
{
    PrepareSpellScript(spell_inner_child_354481);

    void HandleDummy1(SpellEffIndex /*eff*/)
    {
    }


    void HandleDummy2(SpellEffIndex /*eff*/)
    {
    }


    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_inner_child_354481::HandleDummy1, EFFECT_0, SPELL_EFFECT_DUMMY);
        OnEffectHitTarget += SpellEffectFn(spell_inner_child_354481::HandleDummy2, EFFECT_1, SPELL_EFFECT_DUMMY);
    }
};

/// ID: 354482 Black Tie Affair
class spell_black_tie_affair_354482 : public SpellScript
{
    PrepareSpellScript(spell_black_tie_affair_354482);

    void HandleDummy1(SpellEffIndex /*eff*/)
    {
    }


    void HandleDummy2(SpellEffIndex /*eff*/)
    {
    }


    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_black_tie_affair_354482::HandleDummy1, EFFECT_0, SPELL_EFFECT_DUMMY);
        OnEffectHitTarget += SpellEffectFn(spell_black_tie_affair_354482::HandleDummy2, EFFECT_1, SPELL_EFFECT_DUMMY);
    }
};

/// ID: 354569 Potent Potion
class spell_potent_potion_354569 : public AuraScript
{
    PrepareAuraScript(spell_potent_potion_354569);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_potent_potion_354569::CheckProc);
        OnProc += AuraProcFn(spell_potent_potion_354569::HandleProc);
    }
};

/// ID: 357609 Dagger of Necrotic Wounding
class spell_dagger_of_necrotic_wounding_357609 : public AuraScript
{
    PrepareAuraScript(spell_dagger_of_necrotic_wounding_357609);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_dagger_of_necrotic_wounding_357609::CheckProc);
        OnProc += AuraProcFn(spell_dagger_of_necrotic_wounding_357609::HandleProc);
    }
};

/// ID: 357839 The Fifth Skull
class spell_the_fifth_skull_357839 : public AuraScript
{
    PrepareAuraScript(spell_the_fifth_skull_357839);

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
    }


    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_the_fifth_skull_357839::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

/// ID: 357864 Raging Battle-Axe
class spell_raging_battleaxe_357864 : public AuraScript
{
    PrepareAuraScript(spell_raging_battleaxe_357864);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_raging_battleaxe_357864::CheckProc);
        OnProc += AuraProcFn(spell_raging_battleaxe_357864::HandleProc);
    }
};

/// ID: 357575 Champion's Brand
class spell_champions_brand_357575 : public AuraScript
{
    PrepareAuraScript(spell_champions_brand_357575);

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
    }


    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_champions_brand_357575::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
    }
};

/// ID: 357706 Volcanic Plumage
class spell_volcanic_plumage_357706 : public AuraScript
{
    PrepareAuraScript(spell_volcanic_plumage_357706);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_volcanic_plumage_357706::CheckProc);
        OnProc += AuraProcFn(spell_volcanic_plumage_357706::HandleProc);
    }
};

/// ID: 356359 Sanguine Defense
class spell_sanguine_defense_356359 : public AuraScript
{
    PrepareAuraScript(spell_sanguine_defense_356359);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_sanguine_defense_356359::CheckProc);
        OnProc += AuraProcFn(spell_sanguine_defense_356359::HandleProc);
    }
};

/// ID: 356389 Claws of Sath'zuul
class spell_claws_of_sathzuul_356389 : public AuraScript
{
    PrepareAuraScript(spell_claws_of_sathzuul_356389);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_claws_of_sathzuul_356389::CheckProc);
        OnProc += AuraProcFn(spell_claws_of_sathzuul_356389::HandleProc);
    }
};

/// ID: 356685 Dreadbugs
class spell_dreadbugs_356685 : public SpellScript
{
    PrepareSpellScript(spell_dreadbugs_356685);

    void HandleDummy(SpellEffIndex /*eff*/)
    {
    }


    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_dreadbugs_356685::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

/// ID: 356506 Sweet Dreams
class spell_sweet_dreams_356506_AuraScript : public AuraScript
{
    PrepareAuraScript(spell_sweet_dreams_356506_AuraScript);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_sweet_dreams_356506_AuraScript::CheckProc);
        OnProc += AuraProcFn(spell_sweet_dreams_356506_AuraScript::HandleProc);
    }
};

class spell_sweet_dreams_356506_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_sweet_dreams_356506_SpellScript);

    void HandleDummy1(SpellEffIndex /*eff*/)
    {
    }


    void HandleDummy2(SpellEffIndex /*eff*/)
    {
    }


    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_sweet_dreams_356506_SpellScript::HandleDummy1, EFFECT_1, SPELL_EFFECT_DUMMY);
        OnEffectHitTarget += SpellEffectFn(spell_sweet_dreams_356506_SpellScript::HandleDummy2, EFFECT_2, SPELL_EFFECT_DUMMY);
    }
};

/// ID: 356600 Calculated Assault
class spell_calculated_assault_356600 : public AuraScript
{
    PrepareAuraScript(spell_calculated_assault_356600);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_calculated_assault_356600::CheckProc);
        OnProc += AuraProcFn(spell_calculated_assault_356600::HandleProc);
    }
};

/// ID: 356662 Refractive Shield
class spell_refractive_shield_356662 : public AuraScript
{
    PrepareAuraScript(spell_refractive_shield_356662);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_refractive_shield_356662::CheckProc);
        OnProc += AuraProcFn(spell_refractive_shield_356662::HandleProc);
    }
};

/// ID: 356779 Fool's Wager
class spell_fools_wager_356779_AuraScript : public AuraScript
{
    PrepareAuraScript(spell_fools_wager_356779_AuraScript);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_fools_wager_356779_AuraScript::CheckProc);
        OnProc += AuraProcFn(spell_fools_wager_356779_AuraScript::HandleProc);
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_fools_wager_356779_AuraScript::HandlePeriodic, EFFECT_1, SPELL_AURA_PERIODIC_DUMMY);
    }
};

class spell_fools_wager_356779_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_fools_wager_356779_SpellScript);

    void HandleDummy(SpellEffIndex /*eff*/)
    {
    }


    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_fools_wager_356779_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

/// ID: 357524 The Stone Ward
class spell_the_stone_ward_357524 : public AuraScript
{
    PrepareAuraScript(spell_the_stone_ward_357524);

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
    }


    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_the_stone_ward_357524::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
    }
};

/// ID: 356827 Tiny Dancing Shoes
class spell_tiny_dancing_shoes_356827 : public AuraScript
{
    PrepareAuraScript(spell_tiny_dancing_shoes_356827);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_tiny_dancing_shoes_356827::CheckProc);
        OnProc += AuraProcFn(spell_tiny_dancing_shoes_356827::HandleProc);
    }
};

/// ID: 356828 Dripping Fang
class spell_dripping_fang_356828 : public AuraScript
{
    PrepareAuraScript(spell_dripping_fang_356828);

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
    }


    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_dripping_fang_356828::HandlePeriodic, EFFECT_1, SPELL_AURA_PERIODIC_DUMMY);
    }
};

/// ID: 357604 Siegebreaker's Stand
class spell_siegebreakers_stand_357604 : public AuraScript
{
    PrepareAuraScript(spell_siegebreakers_stand_357604);

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
    }


    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_siegebreakers_stand_357604::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

/// ID: 357747 Overflowing Chalice
class spell_overflowing_chalice_357747 : public AuraScript
{
    PrepareAuraScript(spell_overflowing_chalice_357747);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_overflowing_chalice_357747::CheckProc);
        OnProc += AuraProcFn(spell_overflowing_chalice_357747::HandleProc);
    }
};

/// ID: 357814 Regenerative Fungus
class spell_regenerative_fungus_357814 : public AuraScript
{
    PrepareAuraScript(spell_regenerative_fungus_357814);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_regenerative_fungus_357814::CheckProc);
        OnProc += AuraProcFn(spell_regenerative_fungus_357814::HandleProc);
    }
};

/// ID: 357815 Satchel of the Hunt
class spell_satchel_of_the_hunt_357815 : public AuraScript
{
    PrepareAuraScript(spell_satchel_of_the_hunt_357815);

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
    }


    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_satchel_of_the_hunt_357815::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

/// ID: 357817 Huntsman's Horn
class spell_huntsmans_horn_357817 : public AuraScript
{
    PrepareAuraScript(spell_huntsmans_horn_357817);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_huntsmans_horn_357817::CheckProc);
        OnProc += AuraProcFn(spell_huntsmans_horn_357817::HandleProc);
    }
};

/// ID: 357829 Gavel of Judgement
class spell_gavel_of_judgement_357829 : public AuraScript
{
    PrepareAuraScript(spell_gavel_of_judgement_357829);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_gavel_of_judgement_357829::CheckProc);
        OnProc += AuraProcFn(spell_gavel_of_judgement_357829::HandleProc);
    }
};

/// ID: 357834 Handbook of Uncivil Etiquette
class spell_handbook_of_uncivil_etiquette_357834 : public AuraScript
{
    PrepareAuraScript(spell_handbook_of_uncivil_etiquette_357834);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_handbook_of_uncivil_etiquette_357834::CheckProc);
        OnProc += AuraProcFn(spell_handbook_of_uncivil_etiquette_357834::HandleProc);
    }
};

/// ID: 357847 Stabilizing Diamond Alembic
class spell_stabilizing_diamond_alembic_357847 : public AuraScript
{
    PrepareAuraScript(spell_stabilizing_diamond_alembic_357847);

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
    }


    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_stabilizing_diamond_alembic_357847::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

/// ID: 357863 The Stygian King's Barbs
class spell_the_stygian_kings_barbs_357863_AuraScript : public AuraScript
{
    PrepareAuraScript(spell_the_stygian_kings_barbs_357863_AuraScript);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_the_stygian_kings_barbs_357863_AuraScript::CheckProc);
        OnProc += AuraProcFn(spell_the_stygian_kings_barbs_357863_AuraScript::HandleProc);
    }
};

class spell_the_stygian_kings_barbs_357863_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_the_stygian_kings_barbs_357863_SpellScript);

    void HandleDummy(SpellEffIndex /*eff*/)
    {
    }


    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_the_stygian_kings_barbs_357863_SpellScript::HandleDummy, EFFECT_1, SPELL_EFFECT_DUMMY);
    }
};

/// ID: 357889 Pedestal of Utter Hubris
class spell_pedestal_of_utter_hubris_357889 : public AuraScript
{
    PrepareAuraScript(spell_pedestal_of_utter_hubris_357889);

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
    }


    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_pedestal_of_utter_hubris_357889::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

/// ID: 357897 Crumbling Bulwark
class spell_crumbling_bulwark_357897 : public AuraScript
{
    PrepareAuraScript(spell_crumbling_bulwark_357897);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_crumbling_bulwark_357897::CheckProc);
        OnProc += AuraProcFn(spell_crumbling_bulwark_357897::HandleProc);
    }
};

/// ID: 357900 Bottle of Sanguine Ichor
class spell_bottle_of_sanguine_ichor_357900 : public AuraScript
{
    PrepareAuraScript(spell_bottle_of_sanguine_ichor_357900);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_bottle_of_sanguine_ichor_357900::CheckProc);
        OnProc += AuraProcFn(spell_bottle_of_sanguine_ichor_357900::HandleProc);
    }
};

/// ID: 363726 Looping Torment
class spell_looping_torment_363726 : public AuraScript
{
    PrepareAuraScript(spell_looping_torment_363726);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_looping_torment_363726::CheckProc);
        OnProc += AuraProcFn(spell_looping_torment_363726::HandleProc);
    }
};

/// ID: 363741 Cosmic Alacrity
class spell_cosmic_alacrity_363741 : public AuraScript
{
    PrepareAuraScript(spell_cosmic_alacrity_363741);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_cosmic_alacrity_363741::CheckProc);
        OnProc += AuraProcFn(spell_cosmic_alacrity_363741::HandleProc);
    }
};

/// ID: 363888 Analyze Offenses
class spell_analyze_offenses_363888_AuraScript : public AuraScript
{
    PrepareAuraScript(spell_analyze_offenses_363888_AuraScript);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_analyze_offenses_363888_AuraScript::CheckProc);
        OnProc += AuraProcFn(spell_analyze_offenses_363888_AuraScript::HandleProc);
    }
};

class spell_analyze_offenses_363888_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_analyze_offenses_363888_SpellScript);

    void HandleDummy(SpellEffIndex /*eff*/)
    {
    }


    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_analyze_offenses_363888_SpellScript::HandleDummy, EFFECT_1, SPELL_EFFECT_DUMMY);
    }
};

/// ID: 363994 Cosmic Tremor
class spell_cosmic_tremor_363994_AuraScript : public AuraScript
{
    PrepareAuraScript(spell_cosmic_tremor_363994_AuraScript);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_cosmic_tremor_363994_AuraScript::CheckProc);
        OnProc += AuraProcFn(spell_cosmic_tremor_363994_AuraScript::HandleProc);
    }
};

class spell_cosmic_tremor_363994_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_cosmic_tremor_363994_SpellScript);

    void HandleDummy(SpellEffIndex /*eff*/)
    {
    }


    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_cosmic_tremor_363994_SpellScript::HandleDummy, EFFECT_1, SPELL_EFFECT_DUMMY);
    }
};

/// ID: 364048 Terraform
class spell_terraform_364048 : public AuraScript
{
    PrepareAuraScript(spell_terraform_364048);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_terraform_364048::CheckProc);
        OnProc += AuraProcFn(spell_terraform_364048::HandleProc);
    }
};

/// ID: 364516 Zovaal's Versatile Vittles x 2
class spell_zovaals_versatile_vittles_x_2_364516 : public SpellScript
{
    PrepareSpellScript(spell_zovaals_versatile_vittles_x_2_364516);

    void HandleDummy(SpellEffIndex /*eff*/)
    {
    }


    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_zovaals_versatile_vittles_x_2_364516::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

/// ID: 364517 Zovaal's Versatile Vittles x 3
class spell_zovaals_versatile_vittles_x_3_364517 : public SpellScript
{
    PrepareSpellScript(spell_zovaals_versatile_vittles_x_3_364517);

    void HandleDummy(SpellEffIndex /*eff*/)
    {
    }


    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_zovaals_versatile_vittles_x_3_364517::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

/// ID: 364518 Zovaal's Versatile Vittles x 4
class spell_zovaals_versatile_vittles_x_4_364518 : public SpellScript
{
    PrepareSpellScript(spell_zovaals_versatile_vittles_x_4_364518);

    void HandleDummy(SpellEffIndex /*eff*/)
    {
    }


    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_zovaals_versatile_vittles_x_4_364518::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

/// ID: 364542 Sharpshooter's Insight x 2
class spell_sharpshooters_insight_x_2_364542 : public SpellScript
{
    PrepareSpellScript(spell_sharpshooters_insight_x_2_364542);

    void HandleDummy(SpellEffIndex /*eff*/)
    {
    }


    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_sharpshooters_insight_x_2_364542::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

/// ID: 364543 Sharpshooter's Insight x 3
class spell_sharpshooters_insight_x_3_364543 : public SpellScript
{
    PrepareSpellScript(spell_sharpshooters_insight_x_3_364543);

    void HandleDummy(SpellEffIndex /*eff*/)
    {
    }


    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_sharpshooters_insight_x_3_364543::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

/// ID: 364545 Sharpshooter's Insight x 4
class spell_sharpshooters_insight_x_4_364545 : public SpellScript
{
    PrepareSpellScript(spell_sharpshooters_insight_x_4_364545);

    void HandleDummy(SpellEffIndex /*eff*/)
    {
    }


    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_sharpshooters_insight_x_4_364545::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

/// ID: 365200 Inversion Prism
class spell_inversion_prism_365200 : public AuraScript
{
    PrepareAuraScript(spell_inversion_prism_365200);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_inversion_prism_365200::CheckProc);
        OnProc += AuraProcFn(spell_inversion_prism_365200::HandleProc);
    }
};

/// ID: 365267 Virulent Spores
class spell_virulent_spores_365267_AuraScript : public AuraScript
{
    PrepareAuraScript(spell_virulent_spores_365267_AuraScript);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }


    void HandleProc(ProcEventInfo& eventInfo)
    {
    }


    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_virulent_spores_365267_AuraScript::CheckProc);
        OnProc += AuraProcFn(spell_virulent_spores_365267_AuraScript::HandleProc);
    }
};

class spell_virulent_spores_365267_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_virulent_spores_365267_SpellScript);

    void HandleDummy(SpellEffIndex /*eff*/)
    {
    }


    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_virulent_spores_365267_SpellScript::HandleDummy, EFFECT_1, SPELL_EFFECT_DUMMY);
    }
};


void AddSC_TorghastSpells()
{
    RegisterSpellScript(spell_obleron_spikes_x2_294587);
    RegisterSpellScript(spell_obleron_spikes_x3_294588);
    RegisterSpellScript(spell_obleron_winds_x2_294593);
    RegisterSpellScript(spell_obleron_winds_x3_294594);
    RegisterSpellScript(spell_obleron_talisman_x2_294600);
    RegisterSpellScript(spell_obleron_talisman_x3_294601);
    RegisterSpellScript(spell_obleron_ephemera_x2_294603);
    RegisterSpellScript(spell_obleron_ephemera_x3_294604);
    RegisterSpellScript(spell_obleron_venom_x2_294610);
    RegisterSpellScript(spell_obleron_venom_x3_294611);
    RegisterSpellScript(spell_obleron_endurance_x2_293026);
    RegisterSpellScript(spell_obleron_endurance_x3_293027);
    RegisterSpellScript(spell_tremorbeast_tusk_297576);
    RegisterSpellScript(spell_knowledge_of_mortality_296141);
    RegisterSpellScript(spell_vitality_guillotine_300730);
    RegisterSpellScript(spell_blade_of_the_lifetaker_300771);
    RegisterSpellScript(spell_subjugators_manacles_297721);
    RegisterSpellScript(spell_flaming_lance_299419);
    RegisterSpellScript(spell_mind_breach_296515);
    RegisterSpellScript(spell_abundance_of_phantasma_295068);
    RegisterSpellScript(spell_bloating_fodder_294422);
    RegisterSpellScript(spell_secret_spices_295694);
    RegisterSpellScript(spell_curious_miasma_295965);
    RegisterSpellScript(spell_protective_phantasma_295969);
    RegisterSpellScript(spell_gluttons_kerchief_294887);
    RegisterSpellScript(spell_astral_phantasma_298789);
    RegisterSpellScript(spell_might_of_the_worldsplitter_298564);
    RegisterSpellScript(spell_earthen_resonance_298576);
    RegisterSpellScript(spell_thermal_harmony_298685);
    RegisterSpellScript(spell_allconsuming_blaze_298891);
    RegisterSpellScript(spell_galvanizing_nimbus_299388);
    RegisterSpellScript(spell_molten_shock_298911);
    RegisterSpellScript(spell_ignan_oblation_298952);
    RegisterSpellScript(spell_magma_fist_298969);
    RegisterSpellScript(spell_open_doors_300793);
    RegisterSpellScript(spell_touch_of_the_unseen_300796);
    RegisterSpellScript(spell_heart_of_the_forge_299049);
    RegisterSpellScript(spell_band_of_deep_burns_304992);
    RegisterSpellScript(spell_frostchipper_304996);
    RegisterSpellScript(spell_stormcycle_peridot_304998);
    RegisterSpellScript(spell_shadowed_iris_305002);
    RegisterSpellScript(spell_words_of_incomprehensible_glory_305004);
    RegisterSpellScript(spell_scroll_of_elchaver_305006);
    RegisterSpellScript(spell_hematoma_bat_305008);
    RegisterSpellScript(spell_finger_of_frozen_fury_305042);
    RegisterSpellScript(spell_lightning_dust_305044);
    RegisterSpellScript(spell_corruption_antenna_305047);
    RegisterSpellScript(spell_watchful_lightfly_305050);
    RegisterSpellScript(spell_lens_of_elchaver_305052);
    RegisterSpellScript(spell_yelshirs_powerglove_305054);
    RegisterSpellScript(spell_wardens_authority_305266);
    RegisterSpellScript(spell_pocketed_soulcage_305269);
    RegisterSpellScript(spell_dark_armaments_305274);
    RegisterSpellScript(spell_glasswing_charm_305282);
    RegisterSpellScript(spell_prisoners_concord_305293);
    RegisterSpellScript(spell_kyrian_blessing_306563);
    RegisterSpellScript(spell_maldraxxian_repayment_306571);
    RegisterSpellScript(spell_gift_of_ardenweald_306573);
    RegisterSpellScript(spell_venthyrs_gratitude_306575);
    RegisterSpellScript(spell_offer_of_souls_342027);
    RegisterSpellScript(spell_boots_of_bellaton_306604);
    RegisterSpellScript(spell_disembowelers_hook_306609);
    RegisterSpellScript(spell_roots_of_the_dreamtree_306615);
    RegisterSpellScript(spell_lens_of_elchaver_308193);
    RegisterSpellScript(spell_finger_of_frozen_fury_308194);
    RegisterSpellScript(spell_lightning_dust_308195);
    RegisterSpellScript(spell_corruption_antenna_308196);
    RegisterSpellScript(spell_curious_miasma_308201);
    RegisterSpellScript(spell_hatred_core_313566);
    RegisterSpellScript(spell_piercing_vision_of_corraph_313567);
    RegisterSpellScript(spell_zeal_of_the_aspirant_314222);
    RegisterSpellScript(spell_oppressors_chain_314235);
    RegisterSpellScript(spell_mask_of_the_winged_dominator_314237);
    RegisterSpellScript(spell_sacrificial_soulash_314240);
    RegisterSpellScript(spell_wizards_prayer_314253);
    RegisterSpellScript(spell_torch_of_humility_327363);
    RegisterSpellScript(spell_spearheads_of_eternity_314295);
    RegisterSpellScript(spell_fleetwing_torch_315266);
    RegisterSpellScript(spell_frostbite_wand_315288);
    RegisterSpellScript(spell_unstable_phantasma_lure_316850);
    RegisterSpellScript(spell_elethium_diffuser_319206);
    RegisterSpellScript(spell_unlock_shortcut_319605);
    RegisterSpellScript(spell_unlock_shortcut_319649);
    RegisterSpellScript(spell_tainted_blood_vial_332206);
    RegisterSpellScript(spell_gluttons_guise_320931);
    RegisterSpellScript(spell_mark_of_borrowed_power_320932);
    RegisterSpellAndAuraScriptPairWithArgs(spell_bloodstained_dagger_332185_AuraScript, spell_bloodstained_dagger_332185_SpellScript, "spell_bloodstained_dagger_332185");
    RegisterSpellScript(spell_dissolving_vial_320939);
    RegisterSpellScript(spell_smoking_shard_of_teleportation_332201);
    RegisterSpellScript(spell_soulvoid_bag_320941);
    RegisterSpellScript(spell_bottled_shadow_332775);
    RegisterSpellScript(spell_sacrificial_vermin_320950);
    RegisterSpellScript(spell_visage_of_lethality_320952);
    RegisterSpellScript(spell_disembodied_tongue_320956);
    RegisterSpellScript(spell_horrific_dictionary_320868);
    RegisterSpellScript(spell_fragments_of_obscurity_329588);
    RegisterSpellScript(spell_lightinfused_egg_329632);
    RegisterSpellScript(spell_flashbox_320872);
    RegisterSpellScript(spell_fallen_priests_blessing_320874);
    RegisterSpellScript(spell_scales_of_trauma_329428);
    RegisterSpellScript(spell_volatile_phantasm_329241);
    RegisterSpellScript(spell_impulsor_320884);
    RegisterSpellScript(spell_wailing_visage_329689);
    RegisterSpellAndAuraScriptPairWithArgs(spell_puppetmasters_strings_320892_AuraScript, spell_puppetmasters_strings_320892_SpellScript, "spell_puppetmasters_strings_320892");
    RegisterSpellScript(spell_whizzard_hat_320901);
    RegisterSpellScript(spell_bombardiers_etching_320902);
    RegisterSpellScript(spell_scroll_of_explosure_320906);
    RegisterSpellScript(spell_constellation_shield_320910);
    RegisterSpellScript(spell_chronomancers_hourglass_320914);
    RegisterSpellScript(spell_triune_ward_320916);
    RegisterSpellScript(spell_timeweavers_needle_330745);
    RegisterSpellScript(spell_dimensional_blade_320925);
    RegisterSpellScript(spell_clouded_diamond_320927);
    RegisterSpellScript(spell_bladed_bulwark_322026);
    RegisterSpellScript(spell_signet_of_tormented_kings_329345);
    RegisterSpellScript(spell_umbral_ear_trumpet_329283);
    RegisterSpellScript(spell_smoldering_inertia_322032);
    RegisterSpellScript(spell_periapt_of_furor_322049);
    RegisterSpellScript(spell_fan_of_longswords_322029);
    RegisterSpellScript(spell_misshapen_mirror_329268);
    RegisterSpellScript(spell_shrieking_flagon_329275);
    RegisterSpellScript(spell_ogundimus_fist_329452);
    RegisterSpellScript(spell_gibbering_skull_329335);
    RegisterSpellScript(spell_voracious_culling_blade_329213);
    RegisterSpellScript(spell_pleonexian_command_322035);
    RegisterSpellScript(spell_spattered_soles_322031);
    RegisterSpellScript(spell_resonant_throatbands_322043);
    RegisterSpellScript(spell_hurricane_heart_322030);
    RegisterSpellScript(spell_deathseers_satchel_329857);
    RegisterSpellScript(spell_leeching_lilypad_329595);
    RegisterSpellScript(spell_rimeblood_329726);
    RegisterSpellScript(spell_chains_of_devastation_329768);
    RegisterSpellScript(spell_mawrats_on_ice_329793);
    RegisterSpellScript(spell_deathseers_whip_329789);
    RegisterSpellScript(spell_shield_of_spirits_329805);
    RegisterSpellScript(spell_heart_of_the_deathseer_330179);
    RegisterSpellScript(spell_deathseer_choker_329937);
    RegisterSpellScript(spell_deathseers_reins_329963);
    RegisterSpellScript(spell_spike_of_the_ice_guardian_329811);
    RegisterSpellScript(spell_fogged_crystal_331463);
    RegisterSpellScript(spell_sigil_of_skoldus_331367);
    RegisterSpellScript(spell_deadeye_satchel_331365);
    RegisterSpellScript(spell_cadaverous_cleats_331187);
    RegisterSpellScript(spell_mawrat_scent_gland_342546);
    RegisterSpellScript(spell_forsworn_feather_331296);
    RegisterSpellScript(spell_bursting_tar_331287);
    RegisterSpellScript(spell_peltsmans_grit_331283);
    RegisterSpellScript(spell_craven_strategem_331355);
    RegisterSpellScript(spell_scaredy_rat_331194);
    RegisterSpellScript(spell_amplifying_mirror_331455);
    RegisterSpellScript(spell_hateful_shardring_331357);
    RegisterSpellScript(spell_piercing_scope_331183);
    RegisterSpellScript(spell_flowing_potential_wraps_343449);
    RegisterSpellScript(spell_terrorladen_slumbersand_343450);
    RegisterSpellScript(spell_vein_rippers_343451);
    RegisterSpellScript(spell_muffled_metronome_343452);
    RegisterSpellScript(spell_quicksilver_mixture_343446);
    RegisterSpellScript(spell_draped_prism_shawl_343442);
    RegisterSpellScript(spell_shimmering_cloaktrails_343392);
    RegisterSpellScript(spell_distracting_charges_333765);
    RegisterSpellScript(spell_vial_of_unseen_poison_333763);
    RegisterSpellScript(spell_restless_onyx_geodes_333512);
    RegisterSpellScript(spell_unceasing_chain_link_333506);
    RegisterSpellScript(spell_rupturing_spike_333505);
    RegisterSpellScript(spell_slippery_wraithcoil_333502);
    RegisterSpellScript(spell_pouch_of_soulash_333501);
    RegisterSpellScript(spell_shadowlaced_armaments_343382);
    RegisterSpellScript(spell_scales_of_order_343461);
    RegisterSpellScript(spell_celestial_lasso_343822);
    RegisterSpellScript(spell_bottled_wind_343793);
    RegisterSpellScript(spell_cloud_of_feathers_343790);
    RegisterSpellScript(spell_balance_of_the_ox_331834);
    RegisterSpellScript(spell_caught_by_the_dropkicks_331830);
    RegisterSpellScript(spell_tiger_and_crane_figurines_331667);
    RegisterSpellScript(spell_rolling_tigers_331663);
    RegisterSpellScript(spell_flowing_chi_rolls_331650);
    RegisterSpellScript(spell_deathtouched_brew_331647);
    RegisterSpellScript(spell_hit_scheme_331622);
    RegisterSpellScript(spell_corrosive_dosage_331528);
    RegisterSpellScript(spell_dark_stalkers_draught_322830);
    RegisterSpellScript(spell_cadaverous_eye_322837);
    RegisterSpellScript(spell_heartpiercing_spine_322845);
    RegisterSpellScript(spell_soulrender_of_zovaal_322851);
    RegisterSpellScript(spell_willbreaker_322823);
    RegisterSpellScript(spell_felborn_shield_322826);
    RegisterSpellScript(spell_fury_wrappings_322829);
    RegisterSpellScript(spell_shield_of_unending_fury_322833);
    RegisterSpellScript(spell_blindfold_of_focus_322844);
    RegisterSpellScript(spell_grim_tinder_322847);
    RegisterSpellScript(spell_phantasmal_iris_322831);
    RegisterSpellScript(spell_darkglare_medallion_322832);
    RegisterSpellScript(spell_ragehoof_322834);
    RegisterSpellScript(spell_mark_of_the_ogre_322835);
    RegisterSpellAndAuraScriptPairWithArgs(spell_fleetwing_322839_AuraScript, spell_fleetwing_322839_SpellScript, "spell_fleetwing_322839");
    RegisterSpellScript(spell_resonant_mawfang_322846);
    RegisterSpellScript(spell_edgelurker_320800);
    RegisterSpellAndAuraScriptPairWithArgs(spell_torghast_ambassador_326579_AuraScript, spell_torghast_ambassador_326579_SpellScript, "spell_torghast_ambassador_326579");
    RegisterSpellScript(spell_power_overwhelming_329605);
    RegisterSpellScript(spell_spellweavers_mojo_330551);
    RegisterSpellScript(spell_gravity_dynamo_330630);
    RegisterSpellScript(spell_orbit_breaker_329970);
    RegisterSpellScript(spell_sylvatican_charm_329969);
    RegisterSpellScript(spell_lycaras_bargain_329960);
    RegisterSpellScript(spell_creeping_freeze_330855);
    RegisterSpellScript(spell_revitalizing_spirit_331375);
    RegisterSpellScript(spell_chains_of_anguish_332216);
    RegisterSpellScript(spell_occult_emitter_332212);
    RegisterSpellScript(spell_phearomones_332199);
    RegisterSpellScript(spell_hungerstone_332163);
    RegisterSpellScript(spell_tome_of_swordplay_331921);
    RegisterSpellScript(spell_boundless_fortitude_332532);
    RegisterSpellScript(spell_ancient_drake_breath_332366);
    RegisterSpellScript(spell_bone_growing_juice_332578);
    RegisterSpellScript(spell_plaguebringer_332685);
    RegisterSpellScript(spell_theory_of_justice_332592);
    RegisterSpellAndAuraScriptPairWithArgs(spell_blood_beacon_332799_AuraScript, spell_blood_beacon_332799_SpellScript, "spell_blood_beacon_332799");
    RegisterSpellScript(spell_pendrakes_visor_332800);
    RegisterSpellScript(spell_gavel_of_true_judgment_332803);
    RegisterSpellScript(spell_badge_of_the_mad_paragon_332806);
    RegisterSpellScript(spell_mark_of_conkquest_332939);
    RegisterSpellScript(spell_unstable_containment_crystal_333093);
    RegisterSpellScript(spell_smoking_ash_pile_332887);
    RegisterSpellScript(spell_accursed_hand_wraps_333029);
    RegisterSpellScript(spell_fossilized_bone_fragments_333334);
    RegisterSpellScript(spell_seeds_of_rampant_growth_333352);
    RegisterSpellScript(spell_elemental_conduit_333357);
    RegisterSpellScript(spell_crystallized_elemental_heart_333366);
    RegisterSpellScript(spell_pridebreakers_anvil_333598);
    RegisterSpellScript(spell_distillation_of_sin_333620);
    RegisterSpellScript(spell_livingwood_pommel_333937);
    RegisterSpellScript(spell_petrified_wildseed_333949);
    RegisterSpellScript(spell_perpetual_sinstone_334005);
    RegisterSpellScript(spell_draught_of_waning_twilight_334393);
    RegisterSpellScript(spell_soulborne_clasp_334592);
    RegisterSpellScript(spell_thread_of_beads_334992);
    RegisterSpellScript(spell_faintly_glowing_ember_335054);
    RegisterSpellScript(spell_negative_energy_token_335069);
    RegisterSpellScript(spell_shard_of_milkglass_335095);
    RegisterSpellScript(spell_pendrakes_shattered_aegis_332808);
    RegisterSpellScript(spell_bag_of_munitions_335566);
    RegisterSpellScript(spell_undead_bone_ash_336485);
    RegisterSpellScript(spell_darkened_ember_336615);
    RegisterSpellScript(spell_tome_of_the_vanquished_336625);
    RegisterSpellScript(spell_the_stone_ward_337585);
    RegisterSpellScript(spell_erratic_howler_337613);
    RegisterSpellScript(spell_unstable_form_337620);
    RegisterSpellScript(spell_the_fifth_skull_337657);
    RegisterSpellScript(spell_heartseeking_fang_337719);
    RegisterSpellScript(spell_kerims_amulet_of_laceration_337728);
    RegisterSpellScript(spell_reinforced_lure_casing_337765);
    RegisterSpellScript(spell_dark_fortress_337878);
    RegisterSpellScript(spell_fallen_armaments_337881);
    RegisterSpellScript(spell_potent_acid_gland_337928);
    RegisterSpellScript(spell_lumbering_form_337938);
    RegisterSpellScript(spell_irritating_moth_dust_338023);
    RegisterSpellScript(spell_shimmering_wingcape_338029);
    RegisterSpellScript(spell_gruuls_shattered_toenail_338072);
    RegisterSpellScript(spell_coffer_of_spectral_whispers_338446);
    RegisterSpellScript(spell_gaze_of_death_338512);
    RegisterSpellScript(spell_defiance_of_death_338596);
    RegisterSpellScript(spell_pulsing_rothive_338616);
    RegisterSpellScript(spell_soulward_clasp_338922);
    RegisterSpellScript(spell_vlaras_cape_of_subterfuge_338948);
    RegisterSpellScript(spell_form_of_darkness_340451);
    RegisterSpellScript(spell_writhing_shadowtendrils_341137);
    RegisterSpellScript(spell_engorged_limb_340725);
    RegisterSpellScript(spell_formless_executioner_340928);
    RegisterSpellAndAuraScriptPairWithArgs(spell_uncontrolled_darkness_341324_AuraScript, spell_uncontrolled_darkness_341324_SpellScript, "spell_uncontrolled_darkness_341324");
    RegisterSpellScript(spell_baroness_lost_plagueloop_342387);
    RegisterSpellScript(spell_maldos_soul_exploder_342390);
    RegisterSpellScript(spell_earworm_342412);
    RegisterSpellScript(spell_malevolent_stitching_342632);
    RegisterSpellScript(spell_clinging_fog_342757);
    RegisterSpellScript(spell_crystallized_dreams_342779);
    RegisterSpellScript(spell_murmuring_shawl_342793);
    RegisterSpellScript(spell_gnarled_key_342799);
    RegisterSpellScript(spell_the_stone_ward_347962);
    RegisterSpellScript(spell_elethium_diffuser_347969);
    RegisterSpellScript(spell_huddled_carvings_347972);
    RegisterSpellScript(spell_tremorbeast_heart_347975);
    RegisterSpellScript(spell_blade_of_the_lifetaker_347976);
    RegisterSpellScript(spell_unstable_form_347980);
    RegisterSpellScript(spell_vlaras_cape_of_subterfuge_347985);
    RegisterSpellScript(spell_ten_of_towers_347988);
    RegisterSpellScript(spell_potent_acid_gland_348025);
    RegisterSpellScript(spell_erratic_howler_348027);
    RegisterSpellScript(spell_lumbering_form_348043);
    RegisterSpellScript(spell_heartseeking_fang_348048);
    RegisterSpellScript(spell_twisted_samophlange_348059);
    RegisterSpellScript(spell_disembodied_mystic_hands_348063);
    RegisterSpellScript(spell_notched_axe_head_348482);
    RegisterSpellScript(spell_tarnished_medallion_348483);
    RegisterSpellScript(spell_bloodgorged_leech_348511);
    RegisterSpellScript(spell_refilling_elixir_of_life_348541);
    RegisterSpellScript(spell_orb_of_replenishment_348545);
    RegisterSpellScript(spell_ethereal_wildseed_348908);
    RegisterSpellScript(spell_weathered_runestone_349916);
    RegisterSpellScript(spell_thorium_hairpin_349944);
    RegisterSpellScript(spell_gargolmars_shattered_hand_350007);
    RegisterSpellScript(spell_ancient_rubble_350060);
    RegisterSpellScript(spell_blade_of_the_tideskorn_350065);
    RegisterSpellScript(spell_soul_of_an_archon_350117);
    RegisterSpellScript(spell_dark_technique_350129);
    RegisterSpellScript(spell_depleted_tesla_coil_350248);
    RegisterSpellScript(spell_entropic_pool_332543);
    RegisterSpellScript(spell_soulward_clasp_353743);
    RegisterSpellScript(spell_pulsing_rothive_353747);
    RegisterSpellScript(spell_unhindered_soul_354487);
    RegisterSpellScript(spell_mawsworn_strength_354460);
    RegisterSpellScript(spell_spectral_assassin_354483);
    RegisterSpellScript(spell_portal_to_the_unknown_354480);
    RegisterSpellScript(spell_impressive_size_354478);
    RegisterSpellScript(spell_inner_child_354481);
    RegisterSpellScript(spell_black_tie_affair_354482);
    RegisterSpellScript(spell_potent_potion_354569);
    RegisterSpellScript(spell_dagger_of_necrotic_wounding_357609);
    RegisterSpellScript(spell_the_fifth_skull_357839);
    RegisterSpellScript(spell_raging_battleaxe_357864);
    RegisterSpellScript(spell_champions_brand_357575);
    RegisterSpellScript(spell_volcanic_plumage_357706);
    RegisterSpellScript(spell_sanguine_defense_356359);
    RegisterSpellScript(spell_claws_of_sathzuul_356389);
    RegisterSpellScript(spell_dreadbugs_356685);
    RegisterSpellAndAuraScriptPairWithArgs(spell_sweet_dreams_356506_AuraScript, spell_sweet_dreams_356506_SpellScript, "spell_sweet_dreams_356506");
    RegisterSpellScript(spell_calculated_assault_356600);
    RegisterSpellScript(spell_refractive_shield_356662);
    RegisterSpellAndAuraScriptPairWithArgs(spell_fools_wager_356779_AuraScript, spell_fools_wager_356779_SpellScript, "spell_fools_wager_356779");
    RegisterSpellScript(spell_the_stone_ward_357524);
    RegisterSpellScript(spell_tiny_dancing_shoes_356827);
    RegisterSpellScript(spell_dripping_fang_356828);
    RegisterSpellScript(spell_siegebreakers_stand_357604);
    RegisterSpellScript(spell_overflowing_chalice_357747);
    RegisterSpellScript(spell_regenerative_fungus_357814);
    RegisterSpellScript(spell_satchel_of_the_hunt_357815);
    RegisterSpellScript(spell_huntsmans_horn_357817);
    RegisterSpellScript(spell_gavel_of_judgement_357829);
    RegisterSpellScript(spell_handbook_of_uncivil_etiquette_357834);
    RegisterSpellScript(spell_stabilizing_diamond_alembic_357847);
    RegisterSpellAndAuraScriptPairWithArgs(spell_the_stygian_kings_barbs_357863_AuraScript, spell_the_stygian_kings_barbs_357863_SpellScript, "spell_the_stygian_kings_barbs_357863");
    RegisterSpellScript(spell_pedestal_of_utter_hubris_357889);
    RegisterSpellScript(spell_crumbling_bulwark_357897);
    RegisterSpellScript(spell_bottle_of_sanguine_ichor_357900);
    RegisterSpellScript(spell_looping_torment_363726);
    RegisterSpellScript(spell_cosmic_alacrity_363741);
    RegisterSpellAndAuraScriptPairWithArgs(spell_analyze_offenses_363888_AuraScript, spell_analyze_offenses_363888_SpellScript, "spell_analyze_offenses_363888");
    RegisterSpellAndAuraScriptPairWithArgs(spell_cosmic_tremor_363994_AuraScript, spell_cosmic_tremor_363994_SpellScript, "spell_cosmic_tremor_363994");
    RegisterSpellScript(spell_terraform_364048);
    RegisterSpellScript(spell_zovaals_versatile_vittles_x_2_364516);
    RegisterSpellScript(spell_zovaals_versatile_vittles_x_3_364517);
    RegisterSpellScript(spell_zovaals_versatile_vittles_x_4_364518);
    RegisterSpellScript(spell_sharpshooters_insight_x_2_364542);
    RegisterSpellScript(spell_sharpshooters_insight_x_3_364543);
    RegisterSpellScript(spell_sharpshooters_insight_x_4_364545);
    RegisterSpellScript(spell_inversion_prism_365200);
    RegisterSpellAndAuraScriptPairWithArgs(spell_virulent_spores_365267_AuraScript, spell_virulent_spores_365267_SpellScript, "spell_virulent_spores_365267");
}
