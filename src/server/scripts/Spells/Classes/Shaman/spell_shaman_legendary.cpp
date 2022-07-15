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

void AddSC_spell_shaman_legendary()
{
    RegisterSpellScript(spell_chains_of_devastation);
    RegisterSpellScript(spell_chains_of_devastation_chain_lightning);
    RegisterSpellScript(spell_chains_of_devastation_chain_heal);
    RegisterSpellScript(spell_deeply_rooted_elements);
    RegisterSpellScript(spell_echoes_of_great_sundering);
}
