#include "SpellIncludes.h"

enum WarriorCovenant
{
    VeteransReputeAura = 339265,
    VeteransReputeStr = 339267,

    ExecuteDmg = 260798,
    CondemmnDmg = 317483,
};

/// ID: 324143 Conqueror's Banner
class spell_conquerors_banner : public AuraScript
{
    PrepareAuraScript(spell_conquerors_banner);

    void HandleApply(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        auto caster = GetCaster();
        if (!caster)
            return;

        if (caster->HasAura(VeteransReputeAura))
        {
            if (auto aurEff = caster->GetAuraEffect(VeteransReputeAura, EFFECT_0))
                caster->CastSpell(caster, VeteransReputeStr, CastSpellExtraArgs(true).AddSpellBP0(aurEff->GetAmount()));
        }
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_conquerors_banner::HandleApply, EFFECT_0, SPELL_AURA_MOD_RATING, AURA_EFFECT_HANDLE_REAL);
    }
};

/// ID: 335232 Ashen Juggernaut
class spell_ashen_juggernaut : public AuraScript
{
    PrepareAuraScript(spell_ashen_juggernaut);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetSpellInfo())
            return false;

        switch (eventInfo.GetSpellInfo()->Id)
        {
            case ExecuteDmg:
            case CondemmnDmg:
                return true;
            default:
                return false;
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_ashen_juggernaut::CheckProc);
    }
};


void AddSC_spell_warrior_covenant()
{
    RegisterSpellScript(spell_conquerors_banner);
    RegisterSpellScript(spell_ashen_juggernaut);
}
