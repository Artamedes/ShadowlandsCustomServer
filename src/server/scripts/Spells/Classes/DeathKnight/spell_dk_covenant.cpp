#include "SpellIncludes.h"

enum eDeathKnightSpells
{
    Lichborne   = 49039,
    BloodTap    = 194679,
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

void AddSC_spell_dk_covenant()
{
    RegisterSpellScript(spell_hardened_bones);
    RegisterSpellScript(spell_blood_bond);
}
