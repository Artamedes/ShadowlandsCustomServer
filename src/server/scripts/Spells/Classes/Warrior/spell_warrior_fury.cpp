#include "spell_warrior.h"

using namespace Warrior;

/// ID: 1719 Recklessness
class spell_recklessness : public AuraScript
{
    PrepareAuraScript(spell_recklessness);

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        auto caster = GetCaster();
        if (!caster)
            return;

        if (caster->HasAura(WillOfTheBerserker))
            caster->CastSpell(caster, WillOfTheBerserkerProc, true);
    }

    void Register() override
    {
        OnEffectRemove += AuraEffectApplyFn(spell_recklessness::HandleRemove, EFFECT_0, SPELL_AURA_ADD_FLAT_MODIFIER, AURA_EFFECT_HANDLE_REAL);
    }
};

void AddSC_spell_warrior_fury()
{
    RegisterSpellScript(spell_recklessness);
}
