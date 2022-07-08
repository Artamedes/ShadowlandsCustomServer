#include "spell_warlock.h"

using namespace Warlock;

/// ID: 337122 Malefic Wrath
class spell_malefic_wrath : public AuraScript
{
    PrepareAuraScript(spell_malefic_wrath);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == MaleficRapture;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_malefic_wrath::CheckProc);
    }
};
/// ID: 337159 Balespider's Burning Core
class spell_balespiders_burning_core : public AuraScript
{
    PrepareAuraScript(spell_balespiders_burning_core);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == Demonbolt;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_balespiders_burning_core::CheckProc);
    }
};

/// ID: 337141 Grim Inquisitor's Dread Calling
class spell_grim_inquisitors_dread_calling : public AuraScript
{
    PrepareAuraScript(spell_grim_inquisitors_dread_calling);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == HandOfGuldan;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto caster = GetCaster())
        {
            if (auto spell = eventInfo.GetProcSpell())
            {
                if (auto powerCost = spell->GetPowerCost(Powers::POWER_SOUL_SHARDS))
                {
                    caster->CastSpell(caster, 342997, CastSpellExtraArgs(true).AddSpellMod(SpellValueMod::SPELLVALUE_AURA_STACK, powerCost->Amount));
                }
            }
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_grim_inquisitors_dread_calling::CheckProc);
        OnProc += AuraProcFn(spell_grim_inquisitors_dread_calling::HandleProc);
    }
};

/// ID: 337169 Madness of the Azj'Aqir
class spell_madness_of_the_azjaqir : public AuraScript
{
    PrepareAuraScript(spell_madness_of_the_azjaqir);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == ChaosBolt;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_madness_of_the_azjaqir::CheckProc);
    }
};
/// ID: 337163 Odr, Shawl of the Ymirjar
class spell_odr_shawl_of_the_ymirjar : public AuraScript
{
    PrepareAuraScript(spell_odr_shawl_of_the_ymirjar);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == Havoc;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_odr_shawl_of_the_ymirjar::CheckProc);
    }
};


void AddSC_spell_warlock_legendary()
{
    RegisterSpellScript(spell_malefic_wrath);
    RegisterSpellScript(spell_balespiders_burning_core);
    RegisterSpellScript(spell_grim_inquisitors_dread_calling);
    RegisterSpellScript(spell_madness_of_the_azjaqir);
    RegisterSpellScript(spell_odr_shawl_of_the_ymirjar);
}
