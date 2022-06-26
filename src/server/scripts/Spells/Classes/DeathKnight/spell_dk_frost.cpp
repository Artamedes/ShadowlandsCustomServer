#include "SpellIncludes.h"

enum eFrost
{
    /// Frost DK Spells
    Obliterate = 49020,
    FrostStrike = 49143,
    RemorselessWinterDam = 196771,

    /// Conduits
    EradicatingBlowBuff = 337936,
};

/// ID: 337934 Eradicating Blow
class spell_eradicating_blow_conduit : public AuraScript
{
    PrepareAuraScript(spell_eradicating_blow_conduit);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetSpellInfo())
            return false;

        return eventInfo.GetSpellInfo()->Id == Obliterate;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto caster = GetCaster())
        {
            if (auto eff = GetEffect(EFFECT_0))
                if (eff->ConduitRankEntry)
                    caster->CastSpell(caster, EradicatingBlowBuff, CastSpellExtraArgs(true).AddSpellBP0(eff->ConduitRankEntry->AuraPointsOverride));
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_eradicating_blow_conduit::CheckProc);
        OnProc += AuraProcFn(spell_eradicating_blow_conduit::HandleProc);
    }
};

/// ID: 338492 Unleashed Frenzy
class spell_unleashed_frenzy : public AuraScript
{
    PrepareAuraScript(spell_unleashed_frenzy);

    enum eUnleashedFrenzy
    {
        FrenzyProc = 338501,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetSpellInfo())
            return false;

        return eventInfo.GetSpellInfo()->Id == FrostStrike;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();

        if (auto caster = GetCaster())
            if (auto effect = GetEffect(EFFECT_0))
                if (effect->ConduitRankEntry)
                    caster->CastSpell(caster, FrenzyProc, CastSpellExtraArgs(true).AddSpellBP0(effect->ConduitRankEntry->AuraPointsOverride));
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_unleashed_frenzy::CheckProc);
        OnProc += AuraProcFn(spell_unleashed_frenzy::HandleProc);
    }
};

/// ID: 337988 Everfrost
class spell_everfrost : public AuraScript
{
    PrepareAuraScript(spell_everfrost);

    enum eEverFrost
    {
        EverFrostProc = 337989,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetSpellInfo())
            return false;

        return eventInfo.GetSpellInfo()->Id == RemorselessWinterDam;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto caster = GetCaster())
            if (auto target = eventInfo.GetActionTarget())
                if (auto effect = GetEffect(EFFECT_0))
                    if (effect->ConduitRankEntry)
                        caster->CastSpell(target, EverFrostProc, CastSpellExtraArgs(true).AddSpellBP0(effect->ConduitRankEntry->AuraPointsOverride));
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_everfrost::CheckProc);
        OnProc += AuraProcFn(spell_everfrost::HandleProc);
    }
};

void AddSC_spell_dk_frost()
{
    RegisterSpellScript(spell_eradicating_blow_conduit);
    RegisterSpellScript(spell_unleashed_frenzy);
    RegisterSpellScript(spell_everfrost);
}
