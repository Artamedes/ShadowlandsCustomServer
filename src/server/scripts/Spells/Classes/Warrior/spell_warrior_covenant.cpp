#include "SpellIncludes.h"

enum WarriorCovenant
{
    VeteransReputeAura  = 339265,
    VeteransReputeStr   = 339267,

    ExecuteDmg  = 260798,
    CondemmnDmg = 317483,

    DeepWounds = 115767,
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

/// ID: 337214 Hack and Slash
class spell_hack_and_slash : public AuraScript
{
    PrepareAuraScript(spell_hack_and_slash);

    enum eHackAndSlash
    {
        RagingBlowCharge    = 1672,
        RampageDamage       = 184367,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetSpellInfo())
            return false;

        return eventInfo.GetSpellInfo()->Id == RampageDamage;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto caster = GetCaster())
            caster->GetSpellHistory()->RestoreCharge(RagingBlowCharge);
    }

    void HandleCalcProc(ProcEventInfo& eventInfo, float& chance)
    {
        chance = 0.0f;
        if (auto eff = GetEffect(EFFECT_0))
        {
            if (eff->ConduitRankEntry)
            {
                chance = eff->ConduitRankEntry->AuraPointsOverride / 10;
            }
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_hack_and_slash::CheckProc);
        OnProc += AuraProcFn(spell_hack_and_slash::HandleProc);
        OnCalcProcChance += AuraCalcProcChanceFn(spell_hack_and_slash::HandleCalcProc);
    }
};

/// ID: 347213 Fueled by Violence
class spell_fueled_by_violence : public AuraScript
{
    PrepareAuraScript(spell_fueled_by_violence);

    enum eFueledViolence
    {
        SpellProc = 347214,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetSpellInfo())
            return false;

        return eventInfo.GetSpellInfo()->Id == DeepWounds;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto caster = GetCaster())
            if (auto effect = GetEffect(EFFECT_0))
                if (effect->ConduitRankEntry)
                    if (eventInfo.GetDamageInfo())
                        caster->CastSpell(caster, SpellProc, CastSpellExtraArgs(true).AddSpellBP0(CalculatePct(eventInfo.GetDamageInfo()->GetDamage(), effect->ConduitRankEntry->AuraPointsOverride)));
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_fueled_by_violence::CheckProc);
        OnProc += AuraProcFn(spell_fueled_by_violence::HandleProc);
    }
};

void AddSC_spell_warrior_covenant()
{
    RegisterSpellScript(spell_conquerors_banner);
    RegisterSpellScript(spell_ashen_juggernaut);
    RegisterSpellScript(spell_indelible_victory);
    RegisterSpellScript(spell_hack_and_slash);
    RegisterSpellScript(spell_fueled_by_violence);
}
