#include "spell_warrior.h"

using namespace Warrior;

/// ID: 871 Shield Wall
class spell_shield_wall : public AuraScript
{
    PrepareAuraScript(spell_shield_wall);

    void HandleApply(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        auto caster = GetCaster();
        if (!caster)
            return;

        if (caster->HasAura(UnbreakableWill))
            caster->CastSpell(caster, UnbreakableWillProc, true);
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_shield_wall::HandleApply, EFFECT_0, SPELL_AURA_MOD_DAMAGE_PERCENT_TAKEN, AURA_EFFECT_HANDLE_REAL);
    }
};

void AddSC_spell_warrior_protection()
{
    RegisterSpellScript(spell_shield_wall);
}
