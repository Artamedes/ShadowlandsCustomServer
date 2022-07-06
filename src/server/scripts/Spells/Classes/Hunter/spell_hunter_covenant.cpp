#include "spell_hunter.h"

using namespace Hunter;

/// ID: 339495 Reversal of Fortune
class spell_reversal_of_fortune : public AuraScript
{
    PrepareAuraScript(spell_reversal_of_fortune);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetSpellInfo())
            return false;

        return eventInfo.GetHitMask() & ProcFlagsHit::PROC_HIT_INTERRUPT && eventInfo.GetSpellInfo()->Id == CounterShot;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto caster = GetCaster())
            caster->ModifyPower(POWER_FOCUS, 5);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_reversal_of_fortune::CheckProc);
        OnProc += AuraProcFn(spell_reversal_of_fortune::HandleProc);
    }
};

/// ID: 339924 Brutal Projectiles
class spell_brutal_projectiles : public AuraScript
{
    PrepareAuraScript(spell_brutal_projectiles);

    enum eBrutalProjectile
    {
        // ProcSpell = 339929, - has infinite duration
        ProcSpell = 339928,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetSpellInfo())
            return false;

        return eventInfo.GetHitMask() & ProcFlagsHit::PROC_HIT_NORMAL;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto caster = GetCaster())
            if (auto effect = GetEffect(EFFECT_0))
                if (effect->ConduitRankEntry)
                    caster->CastSpell(caster, ProcSpell, CastSpellExtraArgs(true).AddSpellBP0(effect->ConduitRankEntry->AuraPointsOverride));
    }

    void OnCalcProc(ProcEventInfo& eventInfo, float& chance)
    {
        chance = 0.0f;
        if (auto eff = GetEffect(EFFECT_0))
            if (eff->ConduitRankEntry)
                chance = eff->ConduitRankEntry->AuraPointsOverride;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_brutal_projectiles::CheckProc);
        OnProc += AuraProcFn(spell_brutal_projectiles::HandleProc);
        OnCalcProcChance += AuraCalcProcChanceFn(spell_brutal_projectiles::OnCalcProc);
    }
};

/// ID: 341399 Flame Infusion
class spell_flame_infusion : public AuraScript
{
    PrepareAuraScript(spell_flame_infusion);

    enum eFlameInfusion
    {
        ProcSpell = 341401,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetSpellInfo())
            return false;

        return eventInfo.GetSpellInfo()->Id == Carve;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto caster = GetCaster())
            if (auto effect = GetEffect(EFFECT_0))
                if (effect->ConduitRankEntry)
                    caster->CastSpell(caster, ProcSpell, CastSpellExtraArgs(true).AddSpellBP0(effect->ConduitRankEntry->AuraPointsOverride));
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_flame_infusion::CheckProc);
        OnProc += AuraProcFn(spell_flame_infusion::HandleProc);
    }
};

void AddSC_spell_hunter_covenant()
{
    RegisterSpellScript(spell_reversal_of_fortune);
    RegisterSpellScript(spell_brutal_projectiles);
    RegisterSpellScript(spell_flame_infusion);
}
