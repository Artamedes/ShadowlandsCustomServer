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

/// ID: 336191 Indelible Victory
class spell_indelible_victory : public AuraScript
{
    PrepareAuraScript(spell_indelible_victory);

    enum eIndelibleVictory
    {
        VictoryRush         = 34428,
        ImpendingVictory    = 202168,
        ProcSpell           = 336642,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetSpellInfo())
            return false;

        switch (eventInfo.GetSpellInfo()->Id)
        {
            case VictoryRush:
            case ImpendingVictory:
                return true;
            default:
                return false;
        }
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto caster = GetCaster())
            if (auto eff = GetEffect(EFFECT_0))
                if (eff->ConduitRankEntry)
                    caster->CastSpell(caster, ProcSpell, CastSpellExtraArgs(true).AddSpellBP0(eff->ConduitRankEntry->AuraPointsOverride));
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_indelible_victory::CheckProc);
        OnProc += AuraProcFn(spell_indelible_victory::HandleProc);
    }
};


void AddSC_spell_warrior_covenant()
{
    RegisterSpellScript(spell_conquerors_banner);
    RegisterSpellScript(spell_ashen_juggernaut);
    RegisterSpellScript(spell_indelible_victory);
}
