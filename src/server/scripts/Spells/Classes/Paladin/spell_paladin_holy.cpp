#include "SpellIncludes.h"
#include "spell_paladin.h"

/// ID: 225311 Light of Dawn
class spell_light_of_dawn_heal : public SpellScript
{
    PrepareSpellScript(spell_light_of_dawn_heal);

    void HandleHeal(SpellEffIndex /*eff*/)
    {
        auto heal = GetHitHeal();

        auto caster = GetCaster();
        if (!caster)
            return;

        if (caster->Variables.Exist("EmpoweredLightOfDawn"))
            if (caster->Variables.GetValue("EmpoweredLightOfDawn", false))
                AddPct(heal, 25);

        SetHitHeal(heal);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_light_of_dawn_heal::HandleHeal, EFFECT_0, SPELL_EFFECT_HEAL);
    }
};

void AddSC_spell_paladin_holy()
{
    RegisterSpellScript(spell_light_of_dawn_heal);
}
