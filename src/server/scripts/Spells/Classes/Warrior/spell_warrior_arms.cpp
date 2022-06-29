#include "SpellIncludes.h"

enum eArms
{
    MercilessBonegrinderConduit = 335260,
    MercilessBonegrinderProc    = 346574,
};

void ProcMercilessBonegrinder(Unit* caster)
{
    if (!IsSpec(caster, SimpleTalentSpecs::Arms))
        return;

    if (auto aur = caster->GetAuraEffect(MercilessBonegrinderConduit, EFFECT_0))
        if (aur->ConduitRankEntry)
            caster->CastSpell(caster, MercilessBonegrinderProc, CastSpellExtraArgs(true).AddSpellBP0(aur->ConduitRankEntry->AuraPointsOverride));
}

/// ID: 227847 Bladestorm
/// ID: 152277 Ravager
class spell_bladestorm : public AuraScript
{
    PrepareAuraScript(spell_bladestorm);

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (auto caster = GetCaster())
            ProcMercilessBonegrinder(caster);
    }

    void Register() override
    {
        if (m_scriptSpellId == 152277)
            OnEffectRemove += AuraEffectApplyFn(spell_bladestorm::HandleRemove, EFFECT_2, SPELL_AURA_PERIODIC_DUMMY, AURA_EFFECT_HANDLE_REAL);
        else
            OnEffectRemove += AuraEffectApplyFn(spell_bladestorm::HandleRemove, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL, AURA_EFFECT_HANDLE_REAL);
    }
};

void AddSC_spell_warrior_arms()
{
    RegisterSpellScript(spell_bladestorm);
}
