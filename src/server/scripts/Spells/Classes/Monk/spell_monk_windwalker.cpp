#include "SpellIncludes.h"

/// ID: 101546 Spinning Crane Kick
class spell_spinning_crane_kick : public AuraScript
{
    PrepareAuraScript(spell_spinning_crane_kick);

    enum eSpinningCraneKick
    {
        DanceOfChiJi = 325202,
    };

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        auto caster = GetCaster();
        if (!caster)
            return;

        caster->RemoveAurasDueToSpell(DanceOfChiJi);
    }

    void Register() override
    {
        OnEffectRemove += AuraEffectApplyFn(spell_spinning_crane_kick::HandleRemove, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL, AURA_EFFECT_HANDLE_REAL);
    }
};

void AddSC_spell_monk_windwalker()
{
    RegisterSpellScript(spell_spinning_crane_kick);
}
