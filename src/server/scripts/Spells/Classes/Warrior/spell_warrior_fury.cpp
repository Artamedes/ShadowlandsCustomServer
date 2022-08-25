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
/// ID: 202751 Reckless Abandon
class spell_reckless_abandon : public AuraScript
{
    PrepareAuraScript(spell_reckless_abandon);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == Recklessness;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();
        //if (auto caster = GetCaster())
        //    caster->CastSpell(caster, 0, true);
    }

    void HandleApply(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        PreventDefaultAction();
        if (auto caster = GetCaster())
            caster->CastSpell(caster, 335101, true); ///< Replaces the spells with override
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_reckless_abandon::CheckProc);
        OnProc += AuraProcFn(spell_reckless_abandon::HandleProc);
        OnEffectApply += AuraEffectApplyFn(spell_reckless_abandon::HandleApply, EFFECT_1, SPELL_AURA_PROC_TRIGGER_SPELL, AURA_EFFECT_HANDLE_REAL);
    }
};

void AddSC_spell_warrior_fury()
{
    RegisterSpellScript(spell_recklessness);
    RegisterSpellScript(spell_reckless_abandon);
}
