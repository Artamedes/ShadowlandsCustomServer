#include "spell_rogue.h"

enum eFlagellation
{
    FlagellationDmg       = 345316,
    FlagellationAuraAfter = 345569,
    Obedience             = 354703,
};

// 323654
class spell_rog_flagellation : public AuraScript
{
    PrepareAuraScript(spell_rog_flagellation);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetProcSpell())
            return false;

        if (!eventInfo.GetActionTarget())
            return false;

        if (!eventInfo.GetActor())
            return false;

        return eventInfo.GetActionTarget()->HasAura(GetId(), eventInfo.GetActor()->GetGUID());
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetProcSpell())
            return;

        if (!eventInfo.GetActionTarget())
            return;

        if (!eventInfo.GetActor())
            return;

        auto powerCost = eventInfo.GetProcSpell()->GetPowerCost(Powers::POWER_COMBO_POINTS);
        if (!powerCost)
            return;

        if (auto flagellationAura = eventInfo.GetActor()->GetAura(GetId()))
        {
            flagellationAura->ModStackAmount(powerCost->Amount, AURA_REMOVE_BY_DEFAULT, false, false);

            auto damage = CalculatePct(eventInfo.GetActor()->GetTotalAttackPowerValue(BASE_ATTACK), 50);

            eventInfo.GetActor()->CastSpell(eventInfo.GetActionTarget(), FlagellationDmg, CastSpellExtraArgs(true).AddSpellBP0(damage * powerCost->Amount));
            if (eventInfo.GetActor()->HasAura(Obedience))
                eventInfo.GetActor()->GetSpellHistory()->ModifyCooldown(GetId(), -1000);
        }
    }

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        auto caster = GetCaster();
        if (!caster)
            return;

        caster->CastSpell(caster, FlagellationAuraAfter, CastSpellExtraArgs(true).AddSpellMod(SpellValueMod::SPELLVALUE_AURA_STACK, GetStackAmount()));
    }

    void CalculateAmount(AuraEffect const* /*aurEff*/, int32& amount, bool& /*canBeRecalculated*/)
    {
        if (auto caster = GetCaster())
            if (!caster->HasAura(Obedience))
                amount = 0;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_rog_flagellation::CheckProc);
        OnProc += AuraProcFn(spell_rog_flagellation::HandleProc);
        OnEffectRemove += AuraEffectApplyFn(spell_rog_flagellation::HandleRemove, EFFECT_2, SPELL_AURA_MELEE_SLOW, AURA_EFFECT_HANDLE_REAL);
        DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_rog_flagellation::CalculateAmount, EFFECT_4, SPELL_AURA_MOD_VERSATILITY);
    }
};
/// ID: 345569 Flagellation
class spell_flagellation_after : public AuraScript
{
    PrepareAuraScript(spell_flagellation_after);

    void CalculateAmount(AuraEffect const* /*aurEff*/, int32& amount, bool& /*canBeRecalculated*/)
    {
        if (auto caster = GetCaster())
            if (!caster->HasAura(Obedience))
                amount = 0;
    }

    void Register() override
    {
        DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_flagellation_after::CalculateAmount, EFFECT_1, SPELL_AURA_MOD_VERSATILITY);
    }
};

/// ID: 354703 Obedience
class spell_obedience : public AuraScript
{
    PrepareAuraScript(spell_obedience);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        // Handled by flagellation script
        return false;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_obedience::CheckProc);
    }
};

/// 323547
class spell_rog_echoing_reprimand : public SpellScript
{
    PrepareSpellScript(spell_rog_echoing_reprimand);

    void HandleOnHit()
    {
        static const uint32 buffs[] = { 354838,323559,323560,323558,354838 };

        GetCaster()->RemoveAurasByType(SPELL_AURA_SET_POWER_POINT_CHARGE);

        if (auto resoundingClarity = GetCaster()->GetAura(354837))
        {
            for (auto buff : buffs)
            {
                if (buff == 354838)
                    continue;

                GetCaster()->CastSpell(GetCaster(), buff, true);
            }
        }
        else
        {
            GetCaster()->CastSpell(GetCaster(), Trinity::Containers::SelectRandomContainerElement(buffs), true);
        }

    }

    void Register() override
    {
        AfterCast += SpellCastFn(spell_rog_echoing_reprimand::HandleOnHit);
    }
};

void AddSC_spell_rogue_covenant()
{
    RegisterSpellScript(spell_rog_flagellation);
    RegisterSpellScript(spell_flagellation_after);
    RegisterSpellScript(spell_obedience);
    RegisterSpellScript(spell_rog_echoing_reprimand);
}
