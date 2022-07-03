#include "SpellIncludes.h"

enum eDeathKnightSpells
{
    Lichborne       = 49039,
    BloodTap        = 194679,
    DancingRuneWep  = 49028,
    DeathsAdvance   = 48265,
    MindFreeze      = 47528,
    Apocalypse      = 275699,
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

/// ID: 338089 Fleeting Wind
class spell_fleeting_wind : public AuraScript
{
    PrepareAuraScript(spell_fleeting_wind);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetSpellInfo())
            return false;

        return eventInfo.GetSpellInfo()->Id == DeathsAdvance;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_fleeting_wind::CheckProc);
    }
};

/// ID: 337705 Spirit Drain
class spell_spirit_drain : public AuraScript
{
    PrepareAuraScript(spell_spirit_drain);

    enum eSpiritDrain
    {
        SpellProc = 337709,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetSpellInfo())
            return false;

        return eventInfo.GetHitMask() & ProcFlagsHit::PROC_HIT_INTERRUPT && eventInfo.GetSpellInfo()->Id == MindFreeze;
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
        DoCheckProc += AuraCheckProcFn(spell_spirit_drain::CheckProc);
        OnProc += AuraProcFn(spell_spirit_drain::HandleProc);
    }
};

/// ID: 338553 Convocation of the Dead
class spell_convocation_of_the_dead : public AuraScript
{
    PrepareAuraScript(spell_convocation_of_the_dead);

    enum eConvoDead
    {
        FesteringWound = 194311,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetSpellInfo())
            return false;

        return eventInfo.GetSpellInfo()->Id == FesteringWound;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto caster = GetCaster())
        {
            caster->GetSpellHistory()->ModifyCooldown(Apocalypse, -1000);
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_convocation_of_the_dead::CheckProc);
        OnProc += AuraProcFn(spell_convocation_of_the_dead::HandleProc);
    }
};

void AddSC_spell_dk_covenant()
{
    RegisterSpellScript(spell_hardened_bones);
    RegisterSpellScript(spell_blood_bond);
    RegisterSpellScript(spell_meat_shield);
    RegisterSpellScript(spell_fleeting_wind);
    RegisterSpellScript(spell_spirit_drain);
    RegisterSpellScript(spell_convocation_of_the_dead);
}
