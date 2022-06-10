#include "SpellIncludes.h"

// 53385 - Divine Storm
class spell_pal_divine_storm : public SpellScript
{
    PrepareSpellScript(spell_pal_divine_storm);

    uint32 holyPower = 0;

    void HandleTakePower(SpellPowerCost& powerCost)
    {
        if (powerCost.Power == POWER_HOLY_POWER)
            holyPower = powerCost.Amount;
    }

    void HandleAfterCast()
    {
        auto caster = GetCaster();
        if (!caster)
            return;

        if (caster->Variables.Exist("EmpoweredDivineStorm"))
            caster->Variables.Remove("EmpoweredDivineStorm");
    }

    void HandleDmg(SpellEffIndex /*eff*/)
    {
        auto caster = GetCaster();
        if (!caster)
            return;

        auto dmg = GetHitDamage();

        /// Vanquishers Hammer variable
        if (caster->Variables.Exist("EmpoweredDivineStorm"))
        {
            if (caster->Variables.GetValue("EmpoweredDivineStorm", false))
            {
               // holyPower = 3;
            }
        }

        //if (!holyPower)
        //    holyPower = 3;

        //dmg *= holyPower;

        if (caster->Variables.Exist("EmpoweredDivineStorm"))
        {
            if (caster->Variables.GetValue("EmpoweredDivineStorm", false))
            {
                AddPct(dmg, 25);
            }
        }

        SetHitDamage(dmg);
    }

    void Register() override
    {
        OnTakePower += SpellOnTakePowerFn(spell_pal_divine_storm::HandleTakePower);
        OnEffectHitTarget += SpellEffectFn(spell_pal_divine_storm::HandleDmg, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
        AfterCast += SpellCastFn(spell_pal_divine_storm::HandleAfterCast);
    }
};

void AddSC_spell_paladin_retribution()
{
    RegisterSpellScript(spell_pal_divine_storm);
}
