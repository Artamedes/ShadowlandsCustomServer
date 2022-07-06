#include "SpellIncludes.h"

enum ePriest
{
    DesperatePrayer = 19236,
};

enum eHolyWords
{
    Salvation   = 265202,
    Chastise    = 88625,
    Sanctify    = 34861,
    Serenity    = 2050
};

/// ID: 337748 Light's Inspiration
class spell_lights_inspiration : public AuraScript
{
    PrepareAuraScript(spell_lights_inspiration);

    enum eLightInspiration
    {
        ProcSpell = 337749,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetSpellInfo())
            return false;

        return eventInfo.GetSpellInfo()->Id == DesperatePrayer;
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
        DoCheckProc += AuraCheckProcFn(spell_lights_inspiration::CheckProc);
        OnProc += AuraProcFn(spell_lights_inspiration::HandleProc);
    }
};

/// ID: 337947 Resonant Words
class spell_resonant_words : public AuraScript
{
    PrepareAuraScript(spell_resonant_words);

    enum eResonantWords
    {
        ProcSpell = 337948,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetSpellInfo())
            return false;

        if (auto spell = eventInfo.GetSpellInfo()->Id)
            if (spell == Salvation || spell == Chastise || spell == Sanctify || spell == Serenity)
                return true;

        return false;
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
        DoCheckProc += AuraCheckProcFn(spell_resonant_words::CheckProc);
        OnProc += AuraProcFn(spell_resonant_words::HandleProc);
    }
};

void AddSC_spell_priest_covenant()
{
    RegisterSpellScript(spell_lights_inspiration);
    RegisterSpellScript(spell_resonant_words);
}
