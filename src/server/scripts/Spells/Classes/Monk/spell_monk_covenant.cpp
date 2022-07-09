#include "SpellIncludes.h"

enum eMonk
{
    Vivify = 116670,
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

void AddSC_spell_monk_covenant()
{
    RegisterSpellScript(spell_grounding_breath);
}
