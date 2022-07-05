#include "SpellIncludes.h"

enum eMage
{
    Counterspell = 2139,
    Invisibility = 66,
};

/// ID: 357888 Condensed Anima Sphere
class spell_condensed_anima_sphere : public AuraScript
{
    PrepareAuraScript(spell_condensed_anima_sphere);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetSpellInfo())
            return false;

        if (auto caster = GetCaster())
            return caster->GetAura(43234);
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_condensed_anima_sphere::CheckProc);
        OnProc += AuraProcFn(spell_condensed_anima_sphere::HandleProc);
    }
};

/// ID: 336777 Grounding Surge
class spell_grounding_surge : public AuraScript
{
    PrepareAuraScript(spell_grounding_surge);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetSpellInfo())
            return false;

        return eventInfo.GetHitMask() & ProcFlagsHit::PROC_HIT_INTERRUPT && eventInfo.GetSpellInfo()->Id == Counterspell;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto caster = GetCaster())
            if (auto eff = GetEffect(EFFECT_0))
                if (eff->ConduitRankEntry)
                    caster->GetSpellHistory()->ModifyCooldown(Counterspell, - eff->ConduitRankEntry->AuraPointsOverride / 10);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_grounding_surge::CheckProc);
        OnProc += AuraProcFn(spell_grounding_surge::HandleProc);
    }
};

/// ID: 337275 Incantation of Swiftness
class spell_incantation_of_swiftness : public AuraScript
{
    PrepareAuraScript(spell_incantation_of_swiftness);

    enum eIncantSwiftness
    {
        ProcSpell = 337278,
        InvisibilityAura = 32612,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetSpellInfo())
            return false;

        // Unsure if movement speed should be rewarded during 'Fading' portion, or complete Invis
        // return eventInfo.GetSpellInfo()->Id == InvisibilityAura;
        return eventInfo.GetSpellInfo()->Id == Invisibility;
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
        DoCheckProc += AuraCheckProcFn(spell_incantation_of_swiftness::CheckProc);
        OnProc += AuraProcFn(spell_incantation_of_swiftness::HandleProc);
    }
};

void AddSC_spell_mage_covenant()
{
    // Needs to be fixed before registering these spells
    // 
    // RegisterSpellScript(spell_condensed_anima_sphere);
    // RegisterSpellScript(spell_grounding_surge);
    RegisterSpellScript(spell_incantation_of_swiftness);
}
