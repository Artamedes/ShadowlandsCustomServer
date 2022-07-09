#include "SpellIncludes.h"

enum eMonk
{
    Vivify = 116670,
    RisingSunKick = 107428,
    Revival = 115310,
};

/// ID: 336632 Grounding Breath
class spell_grounding_breath : public AuraScript
{
    PrepareAuraScript(spell_grounding_breath);

    enum eGroundBreath
    {
        ManaRefundSpell     = 336637,
        EnergyRefundSpell   = 336638,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetSpellInfo())
            return false;

        return eventInfo.GetSpellInfo()->Id == Vivify;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto caster = GetCaster())
        {
            if (auto eff = GetEffect(EFFECT_0))
            {
                if (eff->ConduitRankEntry)
                {
                    if (eventInfo.GetActionTarget() == caster)
                    {
                        if (auto spell = eventInfo.GetProcSpell())
                        {
                            if (auto healInfo = eventInfo.GetHealInfo())
                            {
                                /// Add extra heal
                                auto heal = healInfo->GetEffectiveHeal();
                                AddPct(heal, eff->ConduitRankEntry->AuraPointsOverride);
                                healInfo->SetEffectiveHeal(heal);

                                /// 30% chance to give power back
                                if (roll_chance_i(30))
                                {
                                    if (IsSpec(caster, SimpleTalentSpecs::Mistweaver))
                                    {
                                        if (auto cost = spell->GetPowerCost(POWER_MANA))
                                            caster->CastSpell(caster, ManaRefundSpell, CastSpellExtraArgs(true).AddSpellBP0(cost->Amount));
                                    }
                                    else
                                    {
                                        if (auto cost = spell->GetPowerCost(POWER_ENERGY))
                                            caster->CastSpell(caster, EnergyRefundSpell, CastSpellExtraArgs(true).AddSpellBP0(cost->Amount));
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_grounding_breath::CheckProc);
        OnProc += AuraProcFn(spell_grounding_breath::HandleProc);
    }
};

/// ID: 337099 Rising Sun Revival
class spell_rising_sun_revival : public AuraScript
{
    PrepareAuraScript(spell_rising_sun_revival);

    enum eRisingRevival
    {
        ProcSpell = 337101,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetSpellInfo())
            return false;

        return eventInfo.GetSpellInfo()->Id == RisingSunKick || eventInfo.GetSpellInfo()->Id == Revival;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto caster = GetCaster())
            if (auto eff = GetEffect(EFFECT_0))
                if (eff->ConduitRankEntry)
                {
                    if (eventInfo.GetSpellInfo()->Id == RisingSunKick)
                        caster->GetSpellHistory()->ModifyCooldown(Revival, -1000);
                    else if (eventInfo.GetSpellInfo()->Id == Revival)
                    {
                        if (auto healInfo = eventInfo.GetHealInfo())
                            if (auto effectiveHeal = healInfo->GetEffectiveHeal())
                                caster->CastSpell(caster, ProcSpell, CastSpellExtraArgs(true).AddSpellBP0(CalculatePct(effectiveHeal, eff->ConduitRankEntry->AuraPointsOverride)));
                    }
                }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_rising_sun_revival::CheckProc);
        OnProc += AuraProcFn(spell_rising_sun_revival::HandleProc);
    }
};


void AddSC_spell_monk_covenant()
{
    RegisterSpellScript(spell_grounding_breath);
    RegisterSpellScript(spell_rising_sun_revival);
}
