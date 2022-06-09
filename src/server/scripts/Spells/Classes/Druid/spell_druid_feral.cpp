#include "SpellIncludes.h"
#include "spell_druid.h"

using namespace Druid;

/// ID: 285381 Primal Wrath
class spell_primal_wrath : public SpellScript
{
    PrepareSpellScript(spell_primal_wrath);

    void HandleOnTakePower(SpellPowerCost& powerCost)
    {
        if (powerCost.Power == POWER_COMBO_POINTS)
        {
            comboPoints = powerCost.Amount;
        }
    }

    void HandleDmg(SpellEffIndex /*eff*/)
    {
        SetHitDamage(GetHitDamage() * comboPoints);
    }

    void HandleAfterHit()
    {
        auto caster = GetCaster();
        if (!caster)
            return;

        uint32 ripBaseDuration = comboPoints * 2000 + 4000;

        std::list<Unit*> enemies;
        caster->GetAttackableUnitListInRange(enemies, 11.0f);
        for (auto enemy : enemies)
        {
            if (auto rip = enemy->GetAura(DruidSpells::Rip, caster->GetGUID()))
            {
                if (rip->GetDuration() < ripBaseDuration)
                    rip->SetDuration(std::min(4000, rip->GetDuration()) + ripBaseDuration);
                continue;
            }

            if (auto rip = caster->AddAura(DruidSpells::Rip, enemy))
            {
                rip->SetMaxDuration(ripBaseDuration);
                rip->RefreshDuration();
            }
        }
    }

    int32 comboPoints = 0;

    void Register() override
    {
        OnTakePower += SpellOnTakePowerFn(spell_primal_wrath::HandleOnTakePower);
        OnEffectHitTarget += SpellEffectFn(spell_primal_wrath::HandleDmg, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
        AfterHit += SpellHitFn(spell_primal_wrath::HandleAfterHit);
        // spell has no hit unit so this isnt called.
        //OnEffectHitTarget += SpellEffectFn(spell_primal_wrath::HandleDummy, EFFECT_1, SPELL_EFFECT_DUMMY);
    }
};

void AddSC_spell_druid_feral()
{
    RegisterSpellScript(spell_primal_wrath);
}
