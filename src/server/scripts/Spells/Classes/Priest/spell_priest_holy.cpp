#include "spell_priest.h"

using namespace Priest;

/// ID: 204883 Circle of Healing
class spell_circle_of_healing : public SpellScript
{
    PrepareSpellScript(spell_circle_of_healing);

    void HandleAfterCast()
    {
        auto caster = GetCaster();
        if (!caster)
            return;

        if (caster->HasAura(Priest::eLegendary::HarmoniousApparatus))
            caster->GetSpellHistory()->ModifyCooldown(Priest::eHoly::HolyWordSanctify, -4000);
    }

    void Register() override
    {
        AfterCast += SpellCastFn(spell_circle_of_healing::HandleAfterCast);
    }
};

/// ID: 27795 Spirit of Redemption
class spell_spirit_of_redemption_spirit : public AuraScript
{
    PrepareAuraScript(spell_spirit_of_redemption_spirit);

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        auto target = GetTarget();
        if (!target)
            return;

        if (target->HasAura(ArchbishopBenedictusRestitution))
            return;

        if (target->HasAura(XanashiReturnOfArchbishopBenedictus))
        {
            if (target->IsPlayer())
                target->ToPlayer()->ResurrectPlayer(5.0f);
            target->CastSpell(target, ArchbishopBenedictusRestitution, true);
            PreventDefaultAction();
            return;
        }
    }

    void Register() override
    {
        OnEffectRemove += AuraEffectRemoveFn(spell_spirit_of_redemption_spirit::HandleRemove, EFFECT_1, SPELL_AURA_SPIRIT_OF_REDEMPTION, AURA_EFFECT_HANDLE_REAL);
    }
};

void AddSC_spell_priest_holy()
{
    RegisterSpellScript(spell_circle_of_healing);
    RegisterSpellScript(spell_spirit_of_redemption_spirit);
}
