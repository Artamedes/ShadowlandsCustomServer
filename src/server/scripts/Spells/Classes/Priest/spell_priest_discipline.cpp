#include "spell_priest.h"

using namespace Priest;

/// ID: 204213 Purge the Wicked
class spell_purge_the_wicked : public AuraScript
{
    PrepareAuraScript(spell_purge_the_wicked);

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        auto caster = GetCaster();
        auto target = GetTarget();
        if (!caster || !target)
            return;

        if (caster->HasAura(CauterizingShadows))
            caster->CastSpell(*target, CauterizingShadowsHeal, true);
    }

    void Register() override
    {
        OnEffectRemove += AuraEffectApplyFn(spell_purge_the_wicked::HandleRemove, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE, AURA_EFFECT_HANDLE_REAL);
    }
};

void AddSC_spell_priest_discipline()
{
    RegisterSpellScript(spell_purge_the_wicked);
}
