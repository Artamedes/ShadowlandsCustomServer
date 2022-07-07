#include "spell_warlock.h"

using namespace Warlock;

/// ID: 325640 Soul Rot
class spell_soul_rot : public SpellScript
{
    PrepareSpellScript(spell_soul_rot);

    void HandleDummy(SpellEffIndex /*eff*/)
    {
        auto caster = GetCaster();
        if (!caster)
            return;

        if (caster->HasAura(eLegendary::DecayingSoulSatchel))
            caster->CastSpell(caster, eLegendary::DecayingSoulSatchelProc, true);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_soul_rot::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

void AddSC_spell_warlock_covenant()
{
    RegisterSpellScript(spell_soul_rot);
}
