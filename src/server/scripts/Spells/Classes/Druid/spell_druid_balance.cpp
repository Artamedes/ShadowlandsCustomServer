#include "spell_druid.h"

using namespace Druid;

/// ID: 79577 Eclipse
class spell_eclipse : public AuraScript
{
    PrepareAuraScript(spell_eclipse);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && (eventInfo.GetSpellInfo()->Id == Starfire || eventInfo.GetSpellInfo()->Id == Wrath);
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetSpellInfo())
            return;

        if (auto caster = GetCaster())
        {
            switch (eventInfo.GetSpellInfo()->Id)
            {
                case Wrath:
                {
                    if (auto eclipseCount = caster->GetAura(EclipseLunarCount))
                    {
                        if (eclipseCount->ModStackAmount(-1))
                        {
                            caster->CastSpell(caster, EclipseLunar, true);

                            if (caster->HasAura(BalanceOfAllThings))
                                caster->CastSpell(caster, BalanceOfAllThingsArcane, CastSpellExtraArgs(true).AddSpellBP0(24));
                        }
                    }
                    break;
                }
                case Starfire:
                {
                    if (auto eclipseCount = caster->GetAura(EclipseSolarCount))
                    {
                        if (eclipseCount->ModStackAmount(-1))
                        {
                            caster->CastSpell(caster, EclipseSolar, true);

                            if (caster->HasAura(BalanceOfAllThings))
                                caster->CastSpell(caster, BalanceOfAllThingsNature, CastSpellExtraArgs(true).AddSpellBP0(24));
                        }
                    }
                    break;
                }
                default:
                    break;
            }
        }
    }

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (auto caster = GetCaster())
        {
            caster->RemoveAura(EclipseLunarCount);
            caster->RemoveAura(EclipseSolarCount);
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_eclipse::CheckProc);
        OnProc += AuraProcFn(spell_eclipse::HandleProc);
        OnEffectRemove += AuraEffectRemoveFn(spell_eclipse::HandleRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
    }
};

/// ID: 48518 Eclipse (Lunar)
class spell_eclipse_lunar : public AuraScript
{
    PrepareAuraScript(spell_eclipse_lunar);

    void HandleApply(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (auto caster = GetCaster())
        {
            caster->RemoveAura(EclipseLunarCount);
            caster->RemoveAura(EclipseSolarCount);
        }
    }

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (auto caster = GetCaster())
        {
            caster->CastSpell(caster, EclipseSolarCount, CastSpellExtraArgs(true).AddSpellMod(SpellValueMod::SPELLVALUE_AURA_STACK, 2));
        }
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_eclipse_lunar::HandleApply, EFFECT_0, SPELL_AURA_ADD_PCT_MODIFIER, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
        OnEffectRemove += AuraEffectRemoveFn(spell_eclipse_lunar::HandleRemove, EFFECT_0, SPELL_AURA_ADD_PCT_MODIFIER, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
    }
};

/// ID: 48517 Eclipse (Solar)
class spell_eclipse_solar : public AuraScript
{
    PrepareAuraScript(spell_eclipse_solar);

    void HandleApply(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (auto caster = GetCaster())
        {
            caster->RemoveAura(EclipseLunarCount);
            caster->RemoveAura(EclipseSolarCount);
        }
    }

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (auto caster = GetCaster())
        {
            caster->CastSpell(caster, EclipseLunarCount, CastSpellExtraArgs(true).AddSpellMod(SpellValueMod::SPELLVALUE_AURA_STACK, 2));
        }
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_eclipse_solar::HandleApply, EFFECT_0, SPELL_AURA_ADD_PCT_MODIFIER, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
        OnEffectRemove += AuraEffectRemoveFn(spell_eclipse_solar::HandleRemove, EFFECT_0, SPELL_AURA_ADD_PCT_MODIFIER, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
    }
};

/// ID: 339943 Balance of All Things
/// ID: 339946 Balance of All Things
class spell_balance_of_all_things : public AuraScript
{
    PrepareAuraScript(spell_balance_of_all_things);

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
        auto eff = GetEffect(EFFECT_0);
        if (eff->GetAmount() > 0)
            eff->ChangeAmount(eff->GetAmount() - 3);
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_balance_of_all_things::HandlePeriodic, EFFECT_1, SPELL_AURA_PERIODIC_DUMMY);
    }
};

void AddSC_spell_druid_balance()
{
    RegisterSpellScript(spell_eclipse);
    RegisterSpellScript(spell_eclipse_lunar);
    RegisterSpellScript(spell_eclipse_solar);
    RegisterSpellScript(spell_balance_of_all_things);
}
