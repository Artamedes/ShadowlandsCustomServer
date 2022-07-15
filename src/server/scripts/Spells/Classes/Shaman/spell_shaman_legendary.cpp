#include "spell_shaman.h"

using namespace Shaman;

/// ID: 336735 Chains of Devastation
class spell_chains_of_devastation : public AuraScript
{
    PrepareAuraScript(spell_chains_of_devastation);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && (eventInfo.GetSpellInfo()->Id == ChainHeal || eventInfo.GetSpellInfo()->Id == ChainLightning);
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetSpellInfo())
        {
            if (auto caster = GetCaster())
            {
                if (eventInfo.GetSpellInfo()->Id == ChainLightning)
                    caster->CastSpell(caster, ChainsOfDevastationChainHeal, true);
                else
                    caster->CastSpell(caster, ChainsOfDevastationChainLightning, true);
            }
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_chains_of_devastation::CheckProc);
        OnProc += AuraProcFn(spell_chains_of_devastation::HandleProc);
    }
};

/// ID: 336736 Chains of Devastation
class spell_chains_of_devastation_chain_lightning : public AuraScript
{
    PrepareAuraScript(spell_chains_of_devastation_chain_lightning);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == ChainLightning;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        Remove();
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_chains_of_devastation_chain_lightning::CheckProc);
        OnProc += AuraProcFn(spell_chains_of_devastation_chain_lightning::HandleProc);
    }
};

/// ID: 336737 Chains of Devastation
class spell_chains_of_devastation_chain_heal : public AuraScript
{
    PrepareAuraScript(spell_chains_of_devastation_chain_heal);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == ChainHeal;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        Remove();
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_chains_of_devastation_chain_heal::CheckProc);
        OnProc += AuraProcFn(spell_chains_of_devastation_chain_heal::HandleProc);
    }
};

/// ID: 336738 Deeply Rooted Elements
class spell_deeply_rooted_elements : public AuraScript
{
    PrepareAuraScript(spell_deeply_rooted_elements);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetSpellInfo()->Id)
            return false;

        auto caster = GetCaster();
        if (!caster)
            return false;

        if (IsSpec(caster, SimpleTalentSpecs::Enhancement))
            return eventInfo.GetSpellInfo()->Id == Stormstrike;
        if (IsSpec(caster, SimpleTalentSpecs::Elemental))
            return eventInfo.GetSpellInfo()->Id == LavaBurst;
        if (IsSpec(caster, SimpleTalentSpecs::RShaman))
            return eventInfo.GetSpellInfo()->Id == Riptide;

        return false;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        auto caster = GetCaster();
        if (!caster)
            return;

        uint32 ascendenceId = 0;

        switch (GetSpecializationId(caster))
        {
            case SimpleTalentSpecs::Enhancement:
                ascendenceId = AscendanceEnhance;
                break;
            case SimpleTalentSpecs::Elemental:
                ascendenceId = AscendenceEle;
                break;
            case SimpleTalentSpecs::RShaman:
                ascendenceId = AscendenceResto;
                break;
            default:
                return;
        }

        uint32 duration = 6000;

        auto aura = caster->GetAura(ascendenceId);
        if (aura)
            duration += aura->GetDuration();

        caster->CastSpell(caster, ascendenceId, CastSpellExtraArgs(true).AddSpellMod(SpellValueMod::SPELLVALUE_DURATION, duration));
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_deeply_rooted_elements::CheckProc);
        OnProc += AuraProcFn(spell_deeply_rooted_elements::HandleProc);
    }
};

/// ID: 336215 Echoes of Great Sundering
class spell_echoes_of_great_sundering : public AuraScript
{
    PrepareAuraScript(spell_echoes_of_great_sundering);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == EarthShock;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_echoes_of_great_sundering::CheckProc);
    }
};

/// ID: 336734 Skybreaker's Fiery Demise
class spell_skybreakers_fiery_demise : public AuraScript
{
    PrepareAuraScript(spell_skybreakers_fiery_demise);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == FlameShock;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto caster = GetCaster())
        {
            caster->GetSpellHistory()->ModifyCooldown(FireElemental, 1000);
            caster->GetSpellHistory()->ModifyCooldown(StormElemental, 1000);
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_skybreakers_fiery_demise::CheckProc);
        OnProc += AuraProcFn(spell_skybreakers_fiery_demise::HandleProc);
    }
};

/// ID: 336063 Windspeaker's Lava Resurgence
class spell_windspeakers_lava_resurgence : public AuraScript
{
    PrepareAuraScript(spell_windspeakers_lava_resurgence);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == EarthShock;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_windspeakers_lava_resurgence::CheckProc);
    }
};

/// ID: 336065 Windspeaker's Lava Resurgence
class spell_windspeakers_lava_resurgence_proc : public AuraScript
{
    PrepareAuraScript(spell_windspeakers_lava_resurgence_proc);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == LavaBurst;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        Remove();
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_windspeakers_lava_resurgence_proc::CheckProc);
        OnProc += AuraProcFn(spell_windspeakers_lava_resurgence_proc::HandleProc);
    }
};

/// ID: 335902 Doom Winds
class spell_doom_winds : public AuraScript
{
    PrepareAuraScript(spell_doom_winds);

    enum eDoomWinds
    {
        DoomWindsCD = 335904,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        auto caster = GetCaster();
        return caster && eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == WindfuryTotem && !caster->HasAura(DoomWindsCD);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_doom_winds::CheckProc);
    }
};

/// ID: 335901 Legacy of the Frost Witch
class spell_legacy_of_the_frost_witch : public AuraScript
{
    PrepareAuraScript(spell_legacy_of_the_frost_witch);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == Stormstrike;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        Remove();
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_legacy_of_the_frost_witch::CheckProc);
        OnProc += AuraProcFn(spell_legacy_of_the_frost_witch::HandleProc);
    }
};

/// ID: 335895 Primal Lava Actuators
class spell_primal_lava_actuators : public AuraScript
{
    PrepareAuraScript(spell_primal_lava_actuators);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == FlameShock;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto caster = GetCaster())
            caster->CastSpell(caster, 347819, true);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_primal_lava_actuators::CheckProc);
        OnProc += AuraProcFn(spell_primal_lava_actuators::HandleProc);
    }
};

/// ID: 335896 Primal Lava Actuators
class spell_primal_lava_actuators_proc : public AuraScript
{
    PrepareAuraScript(spell_primal_lava_actuators_proc);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == LavaLash;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        Remove();
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_primal_lava_actuators_proc::CheckProc);
        OnProc += AuraProcFn(spell_primal_lava_actuators_proc::HandleProc);
    }
};

/// ID: 335886 Earthen Harmony
class spell_earthen_harmony : public AuraScript
{
    PrepareAuraScript(spell_earthen_harmony);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetSpellInfo())
            return false;

        return eventInfo.GetSpellInfo()->Id == EarthShieldHeal || eventInfo.GetSpellInfo()->Id == HealingWave;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetSpellInfo())
            return;

        auto caster = GetCaster();
        if (!caster)
            return;

        if (eventInfo.GetSpellInfo()->Id == EarthShieldHeal && eventInfo.GetProcTarget() && eventInfo.GetProcTarget()->HealthBelowPct(75))
        {
            if (auto healInfo = eventInfo.GetHealInfo())
            {
                healInfo->SetEffectiveHeal(healInfo->GetHeal() * 1.5f);
            }
        }
        else if (eventInfo.GetSpellInfo()->Id == HealingWave && eventInfo.GetProcTarget())
        {
            if (auto earthShield = eventInfo.GetProcTarget()->GetAura(EarthShield, caster->GetGUID()))
            {
                if (earthShield->GetStackAmount() < 9)
                    earthShield->ModStackAmount(1);
            }
            else
                caster->CastSpell(eventInfo.GetProcTarget(), EarthShield, CastSpellExtraArgs(true).AddSpellMod(SpellValueMod::SPELLVALUE_AURA_STACK, 1));
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_earthen_harmony::CheckProc);
        OnProc += AuraProcFn(spell_earthen_harmony::HandleProc);
    }
};

/// ID: 335893 Jonat's Natural Focus
class spell_jonats_natural_focus : public AuraScript
{
    PrepareAuraScript(spell_jonats_natural_focus);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && (eventInfo.GetSpellInfo()->Id == HealingSurge || eventInfo.GetSpellInfo()->Id == HealingWave);
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto caster = GetCaster())
            caster->CastSpell(caster, 347815, true); // Visual
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_jonats_natural_focus::CheckProc);
        OnProc += AuraProcFn(spell_jonats_natural_focus::HandleProc);
    }
};

/// ID: 335894 Jonat's Natural Focus
class spell_jonats_natural_focus_proc : public AuraScript
{
    PrepareAuraScript(spell_jonats_natural_focus_proc);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == ChainHeal;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        Remove();
        if (auto caster = GetCaster())
            caster->RemoveAurasDueToSpell(347815); // Visual
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_jonats_natural_focus_proc::CheckProc);
        OnProc += AuraProcFn(spell_jonats_natural_focus_proc::HandleProc);
    }
};
/// ID: 335889 Primal Tide Core
class spell_primal_tide_core : public AuraScript
{
    PrepareAuraScript(spell_primal_tide_core);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == Riptide;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        ++_riptides;

        if (_riptides == 4)
        {
            _riptides = 0;

            if (auto caster = GetCaster())
            {
                std::list<Unit*> friendlies;
                caster->GetFriendlyUnitListInRange(friendlies, 40.0f);

                if (!friendlies.empty())
                {
                    friendlies.sort(Trinity::HealthPctOrderPred());
                    caster->CastSpell(Trinity::Containers::SelectRandomContainerElement(friendlies), Riptide, true);
                }
            }
        }
    }

    uint32 _riptides = 0;

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_primal_tide_core::CheckProc);
        OnProc += AuraProcFn(spell_primal_tide_core::HandleProc);
    }
};

/// ID: 335891 Spiritwalker's Tidal Totem
class spell_spiritwalkers_tidal_totem : public AuraScript
{
    PrepareAuraScript(spell_spiritwalkers_tidal_totem);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == ManaTideTotem;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_spiritwalkers_tidal_totem::CheckProc);
    }
};

/// ID: 335892 Spiritwalker's Tidal Totem
class spell_spiritwalkers_tidal_totem_proc : public AuraScript
{
    PrepareAuraScript(spell_spiritwalkers_tidal_totem_proc);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && (eventInfo.GetSpellInfo()->Id == ChainHeal || eventInfo.GetSpellInfo()->Id == HealingWave);
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        Remove();
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_spiritwalkers_tidal_totem_proc::CheckProc);
        OnProc += AuraProcFn(spell_spiritwalkers_tidal_totem_proc::HandleProc);
    }
};

void AddSC_spell_shaman_legendary()
{
    RegisterSpellScript(spell_chains_of_devastation);
    RegisterSpellScript(spell_chains_of_devastation_chain_lightning);
    RegisterSpellScript(spell_chains_of_devastation_chain_heal);
    RegisterSpellScript(spell_deeply_rooted_elements);
    RegisterSpellScript(spell_echoes_of_great_sundering);
    RegisterSpellScript(spell_skybreakers_fiery_demise);
    RegisterSpellScript(spell_windspeakers_lava_resurgence);
    RegisterSpellScript(spell_windspeakers_lava_resurgence_proc);
    RegisterSpellScript(spell_doom_winds);
    RegisterSpellScript(spell_legacy_of_the_frost_witch);
    RegisterSpellScript(spell_primal_lava_actuators);
    RegisterSpellScript(spell_primal_lava_actuators_proc);
    RegisterSpellScript(spell_earthen_harmony);
    RegisterSpellScript(spell_jonats_natural_focus);
    RegisterSpellScript(spell_jonats_natural_focus_proc);
    RegisterSpellScript(spell_primal_tide_core);
    RegisterSpellScript(spell_spiritwalkers_tidal_totem);
    RegisterSpellScript(spell_spiritwalkers_tidal_totem_proc);
}
