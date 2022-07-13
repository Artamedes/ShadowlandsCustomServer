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

void AddSC_spell_shaman_legendary()
{
    RegisterSpellScript(spell_chains_of_devastation);
    RegisterSpellScript(spell_chains_of_devastation_chain_lightning);
    RegisterSpellScript(spell_chains_of_devastation_chain_heal);

}
