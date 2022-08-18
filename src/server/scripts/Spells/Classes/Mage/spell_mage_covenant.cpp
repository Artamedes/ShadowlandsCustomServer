#include "SpellIncludes.h"
#include "spell_mage.h"

using namespace Mage;

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

/// ID: 324220 Deathborne
class spell_deathborne : public AuraScript
{
    PrepareAuraScript(spell_deathborne);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetSpellInfo())
            return false;

        switch (eventInfo.GetSpellInfo()->Id)
        {
            case Frostbolt:
            case Fireball:
            case ArcaneBlast:
            case FrostboltDmg:
                return true;
            default:
                return false;
        }
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto caster = GetCaster())
            if (caster->HasAura(eLegendary::DeathsFathom))
                if (auto eff = GetEffect(EFFECT_1))
                    eff->ChangeAmount(eff->GetAmount() + 1);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_deathborne::CheckProc);
        OnProc += AuraProcFn(spell_deathborne::HandleProc);
    }
};

/// ID: 354294 Death's Fathom
class spell_deaths_fathom : public AuraScript
{
    PrepareAuraScript(spell_deaths_fathom);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetSpellInfo())
            return false;

        switch (eventInfo.GetSpellInfo()->Id)
        {
            case Frostbolt:
            case Fireball:
            case ArcaneBlast:
            case FrostboltDmg:
                return true;
            default:
                return false;
        }
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto caster = GetCaster())
        {
            uint32 duration = [&]() -> uint32
            {
                if (auto aura = caster->GetAura(Deathborne))
                    return aura->GetDuration() + 8000;
                return 8000;
            }();

            caster->CastSpell(caster, Deathborne, CastSpellExtraArgs(true).AddSpellMod(SpellValueMod::SPELLVALUE_DURATION, duration));
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_deaths_fathom::CheckProc);
        OnProc += AuraProcFn(spell_deaths_fathom::HandleProc);
    }
};

void AddSC_spell_mage_covenant()
{
    RegisterSpellScript(spell_grounding_surge);
    RegisterSpellScript(spell_incantation_of_swiftness);
    RegisterSpellScript(spell_artifice_of_the_archmage);
    RegisterSpellScript(spell_deathborne);
    RegisterSpellScript(spell_deaths_fathom);
}
