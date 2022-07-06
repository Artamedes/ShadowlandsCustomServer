#include "SpellIncludes.h"

enum eHunter
{
    Disengage   = 781,
    CounterShot = 147362,
    Carve       = 187708,
};

/// ID: 346747 Ambuscade
class spell_ambuscade : public AuraScript
{
    PrepareAuraScript(spell_ambuscade);

    enum eTrapAuras
    {
        FreezingTrapAura    = 3355,
        TarTrapAura         = 135299,
        SteelTrapAura       = 162480,

        // FreezingTrap    = 187650,
        FreezingTrap = 3355,
        // TarTrap         = 187698,
        TarTrap = 135299,
        // SteelTrap       = 162488,
        SteelTrap = 162496,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetSpellInfo())
            return false;

        if (auto spell = eventInfo.GetSpellInfo()->Id)
        {
            if (spell == FreezingTrap || spell == TarTrap || spell == SteelTrap)
                return true;
            //if (spell == TarTrap)
            //    return true;
            //if (spell == SteelTrap)
            //    return true;
        }

        return false;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto caster = GetCaster())
            if (auto eff = GetEffect(EFFECT_0))
                if (eff->ConduitRankEntry)
                {
                    // float cdr = eff->ConduitRankEntry->AuraPointsOverride;
                    // caster->GetSpellHistory()->ModifyCooldown(Disengage, - int32(cdr));
                    caster->GetSpellHistory()->ModifyCooldown(Disengage, - eff->ConduitRankEntry->AuraPointsOverride);
                }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_ambuscade::CheckProc);
        OnProc += AuraProcFn(spell_ambuscade::HandleProc);
    }
};

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
    // Needs fixing
    RegisterSpellScript(spell_ambuscade);

    RegisterSpellScript(spell_reversal_of_fortune);
    RegisterSpellScript(spell_brutal_projectiles);
    RegisterSpellScript(spell_flame_infusion);
}
