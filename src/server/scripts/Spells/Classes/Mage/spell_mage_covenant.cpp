#include "SpellIncludes.h"

enum eMage
{
    Counterspell = 2139,
    Invisibility = 66,
    ArcaneBarrage = 44425,

    GreaterInvisibility = 110959,
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
                {
                    float cdr = eff->ConduitRankEntry->AuraPointsOverride * 100;
                    caster->GetSpellHistory()->ModifyCooldown(Counterspell, -int32(cdr));
                }
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
        return eventInfo.GetSpellInfo()->Id == Invisibility || eventInfo.GetSpellInfo()->Id == GreaterInvisibility;
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

/// ID: 337240 Artifice of the Archmage
class spell_artifice_of_the_archmage : public AuraScript
{
    PrepareAuraScript(spell_artifice_of_the_archmage);

    enum eArtificeofArch
    {
        ProcSpell = 337244,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetSpellInfo())
            return false;

        return eventInfo.GetSpellInfo()->Id == ArcaneBarrage;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto caster = GetCaster())
            if (auto eff = GetEffect(EFFECT_0))
                if (eff->ConduitRankEntry)
                    caster->CastSpell(caster, ProcSpell, CastSpellExtraArgs(true).AddSpellBP0(eff->ConduitRankEntry->AuraPointsOverride));
    }

    void OnCalcProc(ProcEventInfo& eventInfo, float& chance)
    {
        chance = 0.0f;
        if (auto eff = GetEffect(EFFECT_0))
        {
            if (eff->ConduitRankEntry)
            {
                chance = eff->ConduitRankEntry->AuraPointsOverride / 10.0f;
            }
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_artifice_of_the_archmage::CheckProc);
        OnProc += AuraProcFn(spell_artifice_of_the_archmage::HandleProc);
        OnCalcProcChance += AuraCalcProcChanceFn(spell_artifice_of_the_archmage::OnCalcProc);
    }
};

void AddSC_spell_mage_covenant()
{
    RegisterSpellScript(spell_grounding_surge);
    RegisterSpellScript(spell_incantation_of_swiftness);
    RegisterSpellScript(spell_artifice_of_the_archmage);
}
