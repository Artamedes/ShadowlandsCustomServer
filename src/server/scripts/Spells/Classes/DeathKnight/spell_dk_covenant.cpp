#include "SpellIncludes.h"

enum eDeathKnightSpells
{
    Lichborne       = 49039,
    BloodTap        = 194679,
    DancingRuneWep  = 49028,
};

/// ID: 337972 Hardened Bones
class spell_hardened_bones : public AuraScript
{
    PrepareAuraScript(spell_hardened_bones);

    enum eHardenedBones
    {
        SpellProc = 337973,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetSpellInfo())
            return false;

        return eventInfo.GetSpellInfo()->Id == Lichborne;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto caster = GetCaster())
            if (auto effect = GetEffect(EFFECT_0))
                if (effect->ConduitRankEntry)
                    caster->CastSpell(caster, SpellProc, CastSpellExtraArgs(true).AddSpellBP0(effect->ConduitRankEntry->AuraPointsOverride));
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_hardened_bones::CheckProc);
        OnProc += AuraProcFn(spell_hardened_bones::HandleProc);
    }
};

/// ID: 337957 Blood Bond
class spell_blood_bond : public AuraScript
{
    PrepareAuraScript(spell_blood_bond);

    enum eBloodBond
    {
        SpellProc = 337960,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetSpellInfo())
            return false;

        return eventInfo.GetSpellInfo()->Id == BloodTap;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto caster = GetCaster())
            if (auto effect = GetEffect(EFFECT_0))
                if (effect->ConduitRankEntry)
                    caster->CastSpell(caster, SpellProc, CastSpellExtraArgs(true).AddSpellBP0(effect->ConduitRankEntry->AuraPointsOverride));
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_blood_bond::CheckProc);
        OnProc += AuraProcFn(spell_blood_bond::HandleProc);
    }
};

/// ID: 338435 Meat Shield
class spell_meat_shield : public AuraScript
{
    PrepareAuraScript(spell_meat_shield);

    enum eMeatShield
    {
        SpellProc       = 338438,
        DancingRuneAura = 81256,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        auto caster = GetCaster();

        if (!caster)
            return false;

        return eventInfo.GetHitMask() & ProcFlagsHit::PROC_HIT_PARRY && caster->HasAura(DancingRuneAura);
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto caster = GetCaster())
            if (auto effect = GetEffect(EFFECT_0))
                if (effect->ConduitRankEntry)
                    caster->CastSpell(caster, SpellProc, CastSpellExtraArgs(true).AddSpellBP0(effect->ConduitRankEntry->AuraPointsOverride));
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_meat_shield::CheckProc);
        OnProc += AuraProcFn(spell_meat_shield::HandleProc);
    }
};

void AddSC_spell_dk_covenant()
{
    RegisterSpellScript(spell_hardened_bones);
    RegisterSpellScript(spell_blood_bond);
    RegisterSpellScript(spell_meat_shield);
}
