#include "SpellIncludes.h"
#include "spell_paladin.h"

using namespace Paladin;

enum ePaladin
{
    HolyLight = 82326,
};

/// ID: 328204 Vanquisher's Hammer
class spell_vanquishers_hammer : public AuraScript
{
    PrepareAuraScript(spell_vanquishers_hammer);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetSpellInfo())
            return false;

        auto caster = GetCaster();

        switch (GetSpecializationId(caster))
        {
            case SimpleTalentSpecs::HPally:
                return eventInfo.GetSpellInfo()->Id == PaladinSpells::WordOfGlory;
            case SimpleTalentSpecs::ProtPally:
                return eventInfo.GetSpellInfo()->Id == TemplarsVerdict || eventInfo.GetSpellInfo()->Id == 224266;
            case SimpleTalentSpecs::Retribution:
                return eventInfo.GetSpellInfo()->Id == PaladinSpells::WordOfGlory;
            default:
                return false;
        }
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();
        if (auto caster = GetCaster())
        {
            if (auto hitUnit = eventInfo.GetActionTarget())
            {
                //caster->ModifyPower(Powers::POWER_HOLY_POWER, 3);

                switch (GetSpecializationId(caster))
                {
                    case SimpleTalentSpecs::HPally:
                        caster->Variables.Set("EmpoweredLightOfDawn", true);
                        caster->CastSpell(hitUnit, PaladinSpells::LightOfDawn, CastSpellExtraArgs(TRIGGERED_FULL_MASK));
                        break;
                    case SimpleTalentSpecs::ProtPally:
                        caster->Variables.Set("EmpoweredShieldOfTheRighteous", true);
                        caster->CastSpell(hitUnit, PaladinSpells::ShieldOfTheRighteous, CastSpellExtraArgs(TRIGGERED_FULL_MASK));
                        break;
                    case SimpleTalentSpecs::Retribution:
                        caster->Variables.Set("EmpoweredDivineStorm", true);
                        caster->CastSpell(hitUnit, DivineStorm, CastSpellExtraArgs(TRIGGERED_FULL_MASK));
                        break;
                }
                if (auto aur = GetAura())
                    aur->Remove();
            }
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_vanquishers_hammer::CheckProc);
        OnProc += AuraProcFn(spell_vanquishers_hammer::HandleProc);
    }
};

/// ID: 340192 Righteous Might Conduit
class spell_righteous_might : public AuraScript
{
    PrepareAuraScript(spell_righteous_might);

    enum RighteousMight
    {
        RighteousMightHeal = 340193,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetDamageInfo() && eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == PaladinSpells::VanquishersHammer;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();

        if (!eventInfo.GetDamageInfo())
            return;

        if (auto caster = GetCaster())
            caster->CastSpell(caster, RighteousMightHeal, CastSpellExtraArgs(true).AddSpellBP0(eventInfo.GetDamageInfo()->GetDamage() * 0.50f));
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_righteous_might::CheckProc);
        OnProc += AuraProcFn(spell_righteous_might::HandleProc);
    }
};

// 304971
// 356890  Divine Resonance
class spell_pal_divine_toll : public SpellScript
{
    PrepareSpellScript(spell_pal_divine_toll);

    enum DivineToll
    {
        HolyShock = 20473,
        AvengersShield = 31935,
        Judgement = 20271,
    };

    void HandleDummy(SpellEffIndex /*eff*/)
    {
        if (auto caster = GetCaster())
        {
            if (auto target = GetHitUnit())
            {
                auto castFlags = TriggerCastFlags(TRIGGERED_DONT_CREATE_COOLDOWN | TRIGGERED_FULL_MASK | TRIGGERED_IGNORE_GCD | TRIGGERED_IGNORE_SPELL_AND_CATEGORY_CD | TRIGGERED_IGNORE_POWER_AND_REAGENT_COST);

                uint32 times = 1;

                if (target == GetExplTargetUnit())
                    if (auto eff = caster->GetAuraEffect(eConduits::RingingClarity, EFFECT_0))
                        if (eff->ConduitRankEntry)
                            if (roll_chance_f(eff->ConduitRankEntry->AuraPointsOverride))
                                times += 3;

                auto spec = GetSpecializationId(caster);

                for (uint32 i = 0u; i < times; ++i)
                {
                    switch (spec)
                    {
                        case SimpleTalentSpecs::HPally:
                            caster->CastSpell(target, DivineToll::HolyShock, castFlags);
                            break;
                        case SimpleTalentSpecs::ProtPally:
                            caster->CastSpell(target, DivineToll::AvengersShield, castFlags);
                            break;
                        case SimpleTalentSpecs::Retribution:
                            caster->CastSpell(target, DivineToll::Judgement, castFlags);
                            break;
                        default:
                            break;
                    }
                }
            }
        }
    }

    void HandleHeal(SpellEffIndex /*eff*/)
    {
        if (auto caster = GetCaster())
        {
            if (auto target = GetHitUnit())
            {
                auto castFlags = TriggerCastFlags(TRIGGERED_DONT_CREATE_COOLDOWN | TRIGGERED_FULL_MASK | TRIGGERED_IGNORE_GCD | TRIGGERED_IGNORE_SPELL_AND_CATEGORY_CD | TRIGGERED_IGNORE_POWER_AND_REAGENT_COST);

                uint32 times = 1;

                if (target == GetExplTargetUnit())
                    if (auto eff = caster->GetAuraEffect(eConduits::RingingClarity, EFFECT_0))
                        if (eff->ConduitRankEntry)
                            if (roll_chance_f(eff->ConduitRankEntry->AuraPointsOverride))
                                times += 3;

                auto spec = GetSpecializationId(caster);

                for (uint32 i = 0u; i < times; ++i)
                {
                    switch (spec)
                    {
                        case SimpleTalentSpecs::HPally:
                            caster->CastSpell(target, DivineToll::HolyShock, castFlags);
                            break;
                        default:
                            break;
                    }
                }
            }
        }
    }

    void Register() override
    {
        if (m_scriptSpellId == 356890)
        {
            OnEffectHitTarget += SpellEffectFn(spell_pal_divine_toll::HandleHeal, EFFECT_0, SPELL_EFFECT_DUMMY);
            OnEffectHitTarget += SpellEffectFn(spell_pal_divine_toll::HandleDummy, EFFECT_2, SPELL_EFFECT_DUMMY);
        }
        else
        {
            OnEffectHitTarget += SpellEffectFn(spell_pal_divine_toll::HandleDummy, EFFECT_1, SPELL_EFFECT_DUMMY);
            OnEffectHitTarget += SpellEffectFn(spell_pal_divine_toll::HandleHeal, EFFECT_2, SPELL_EFFECT_DUMMY);
        }
    }
};

enum PaladinCovenantSpells
{
    AshenHollowAreaTriggerId = 19042,
    SPELL_PALADIN_ASHEN_HALLOW                   = 316958,
    SPELL_PALADIN_ASHEN_HALLOW_DAMAGE            = 317221,
    SPELL_PALADIN_ASHEN_HALLOW_HEAL              = 317223,
    SPELL_PALADIN_ASHEN_HALLOW_ALLOW_HAMMER      = 330382,

    HallowedDiscernment = 340212,
};

// 19042 - Ashen Hallow
struct areatrigger_pal_ashen_hallow : AreaTriggerAI
{
    areatrigger_pal_ashen_hallow(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger)
    {
        areatrigger->SetPeriodicProcTimer(100);
    }

    void OnPeriodicProc() override
    {
        if (Unit* caster = at->GetCaster())
        {
            caster->CastSpell(at->GetPosition(), SPELL_PALADIN_ASHEN_HALLOW_HEAL, true);
            caster->CastSpell(at->GetPosition(), SPELL_PALADIN_ASHEN_HALLOW_DAMAGE, true);

            if (auto hallowedDiscerment = caster->GetAuraEffect(HallowedDiscernment, EFFECT_0))
            {
                Unit* lowestFriendly = nullptr;
                float currPctFriendly = 101.0f;
                Unit* lowestEnemy = nullptr;
                float currPctEnemy = 101.0f;

                for (auto guid : at->GetInsideUnits())
                {
                    auto unit = ObjectAccessor::GetUnit(*caster, guid);
                    if (unit)
                    {
                        if (unit->IsValidAttackTarget(caster))
                        {
                            if (unit->GetHealthPct() < currPctEnemy)
                            {
                                currPctEnemy = unit->GetHealthPct();
                                lowestEnemy = unit;
                            }
                        }
                        else if (caster->IsValidAssistTarget(unit))
                        {
                            if (unit->GetHealthPct() < currPctFriendly)
                            {
                                currPctFriendly = unit->GetHealthPct();
                                lowestFriendly = unit;
                            }
                        }
                    }
                }

                if (lowestEnemy)
                    caster->CastSpell(lowestEnemy, 340203, CastSpellExtraArgs(true).AddSpellBP0(hallowedDiscerment->GetAmount()));
                if (lowestFriendly)
                    caster->CastSpell(lowestFriendly, 340214, CastSpellExtraArgs(true).AddSpellBP0(hallowedDiscerment->GetAmount()));
            }
        }
    }

    void OnUnitEnter(Unit* unit) override
    {
        if (unit->GetGUID() == at->GetCasterGuid())
            unit->CastSpell(unit, SPELL_PALADIN_ASHEN_HALLOW_ALLOW_HAMMER, true);
    }

    void OnUnitExit(Unit* unit) override
    {
        if (unit->GetGUID() == at->GetCasterGuid())
            unit->RemoveAura(SPELL_PALADIN_ASHEN_HALLOW_ALLOW_HAMMER);
    }
};

/// ID: 316958 Ashen Hallow
class spell_ashen_hallow : public AuraScript
{
    PrepareAuraScript(spell_ashen_hallow);

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (auto caster = GetCaster())
        {
            if (auto at = caster->GetAreaTrigger(GetId()))
                if (caster->HasAura(RadiantEmbers))
                {
                    if (at->GetTotalDuration())
                    {
                        auto diff = 1.0f - float(at->GetDuration() / at->GetTotalDuration());

                        auto cdr = std::min(0.5f, diff) * 240.0f;

                        caster->GetSpellHistory()->ModifyCooldown(AshenHallow, -int32(cdr * 1000));
                    }
                }


            caster->RemoveAreaTrigger(GetEffect(EFFECT_1));
        }
    }

    void Register() override
    {
        OnEffectRemove += AuraEffectApplyFn(spell_ashen_hallow::HandleRemove, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

/// ID: 338787 Shielding Words
class spell_shielding_words : public AuraScript
{
    PrepareAuraScript(spell_shielding_words);

    enum eShieldingWords
    {
        ProcSpell = 338788,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetSpellInfo())
            return false;

        return eventInfo.GetSpellInfo()->Id == PaladinSpells::WordOfGlory;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto caster = GetCaster())
            if (auto eff = GetEffect(EFFECT_0))
                if (eff->ConduitRankEntry)
                    if (eventInfo.GetHealInfo())
                        caster->CastSpell(caster, ProcSpell, CastSpellExtraArgs(true).AddSpellBP0(CalculatePct(eventInfo.GetHealInfo()->GetHeal(), eff->ConduitRankEntry->AuraPointsOverride)));
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_shielding_words::CheckProc);
        OnProc += AuraProcFn(spell_shielding_words::HandleProc);
    }
};

/// ID: 339712 Resplendent Light
class spell_resplendent_light : public AuraScript
{
    PrepareAuraScript(spell_resplendent_light);

    enum eRespLight
    {
        ProcSpell = 339744,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetSpellInfo())
            return false;

        return eventInfo.GetSpellInfo()->Id == HolyLight;
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
        DoCheckProc += AuraCheckProcFn(spell_resplendent_light::CheckProc);
        OnProc += AuraProcFn(spell_resplendent_light::HandleProc);
    }
};

/// ID: 357902 Adaptive Armor Fragment
class spell_adaptive_armor_fragment : public AuraScript
{
    PrepareAuraScript(spell_adaptive_armor_fragment);

    enum eAdapArmorFrag
    {
        ProcSpell = 357972,
        CDSpell = 357973,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        auto caster = GetCaster();
        if (!caster || caster->HasAura(CDSpell))
            return false;
        auto friendly = eventInfo.GetActor();

        if (!friendly || !friendly->IsPlayer())
            return false;

        if (eventInfo.GetHealInfo())
            return true;

        return false;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto caster = GetCaster())
            if (auto eff = GetEffect(EFFECT_0))
                if (eff->ConduitRankEntry)
                {
                    caster->CastSpell(caster, ProcSpell, CastSpellExtraArgs(true).AddSpellBP0(eff->ConduitRankEntry->AuraPointsOverride));
                    caster->CastSpell(caster, CDSpell, true);
                }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_adaptive_armor_fragment::CheckProc);
        OnProc += AuraProcFn(spell_adaptive_armor_fragment::HandleProc);
    }
};

void AddSC_spell_paladin_covenant()
{
    RegisterSpellScript(spell_vanquishers_hammer);
    RegisterSpellScript(spell_righteous_might);
    RegisterSpellScript(spell_pal_divine_toll);
    RegisterSpellScript(spell_ashen_hallow);
    RegisterSpellScript(spell_shielding_words);
    RegisterSpellScript(spell_resplendent_light);
    RegisterSpellScript(spell_adaptive_armor_fragment);

    RegisterAreaTriggerAI(areatrigger_pal_ashen_hallow);
}
