#include "spell_monk.h"

using namespace Monk;

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

// 325216
class spell_monk_bonedust_brew : public AuraScript
{
    PrepareAuraScript(spell_monk_bonedust_brew);

    enum eBonedustBrew
    {
        BonedustDmg = 325217,
        BonedustHeal = 325218,
        BonedustEnergize = 328296,
        GustsOfMistsBonedust = 328748,
        BoneMarrowHops = 337295,
    };

    void HandleProc(ProcEventInfo& eventInfo)
    {
        auto ApplyBoneMarrowHops([](Unit* caster, uint32& damage) -> void
        {
            if (auto eff = caster->GetAuraEffect(BoneMarrowHops, EFFECT_0))
            {
                if (eff->ConduitRankEntry)
                {
                    AddPct(damage, eff->ConduitRankEntry->AuraPointsOverride);
                    caster->GetSpellHistory()->ModifyCooldown(BonedustBrew, -500);
                }
            }
        });

        if (Unit* target = eventInfo.GetActionTarget())
            if (GetCaster() == eventInfo.GetProcTarget())
        {
            if (DamageInfo* damageInfo = eventInfo.GetDamageInfo())
            {
                if (auto caster = GetCaster())
                {
                    uint32 damage = CalculatePct(damageInfo->GetDamage(), 40);
                    ApplyBoneMarrowHops(caster, damage);
                    caster->CastSpell(target, BonedustDmg, CastSpellExtraArgs(true).AddSpellBP0(damage));

                    if (eventInfo.GetSpellInfo())
                    {
                        switch (eventInfo.GetSpellInfo()->Id)
                        {
                            case Monk::eMonk::SpinningCraneKickDmg:
                                if (IsSpec(caster, SimpleTalentSpecs::Windwalker))
                                    caster->CastSpell(caster, BonedustEnergize, true);
                                break;
                            case Monk::eMonk::TigerPalm:
                            case Monk::eBrewmaster::KegSmash:
                                // Reduce brews
                                caster->GetSpellHistory()->ModifyCooldown(Monk::eMonk::FortifyingBrew, -1000);
                                caster->GetSpellHistory()->ModifyCooldown(Monk::eBrewmaster::CelestialBrew, -1000);
                                caster->GetSpellHistory()->ModifyCooldown(Monk::eBrewmaster::PurifyingBrew, -1000);
                                break;
                            default:
                                break;
                        }
                    }
                }
            }
            if (HealInfo* healInfo = eventInfo.GetHealInfo())
            {
                if (auto caster = GetCaster())
                {
                    uint32 damage = CalculatePct(healInfo->GetHeal(), 40);
                    ApplyBoneMarrowHops(caster, damage);
                    caster->CastSpell(target, BonedustHeal, CastSpellExtraArgs(true).AddSpellBP0(damage));

                    if (eventInfo.GetSpellInfo())
                    {
                        switch (eventInfo.GetSpellInfo()->Id)
                        {
                            case Monk::eMistweaver::GustOfMists:
                                caster->CastSpell(target, GustsOfMistsBonedust, true);
                                break;
                            default:
                                break;
                        }
                    }
                }
            }
        }
    }

    void Register() override
    {
        OnProc += AuraProcFn(spell_monk_bonedust_brew::HandleProc);
    }
};

void AddSC_spell_monk_covenant()
{
    RegisterSpellScript(spell_grounding_breath);
    RegisterSpellScript(spell_rising_sun_revival);
    RegisterSpellScript(spell_monk_bonedust_brew);
}
