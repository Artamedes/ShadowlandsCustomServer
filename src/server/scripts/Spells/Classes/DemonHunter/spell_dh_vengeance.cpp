#include "spell_dh.h"

using namespace DH;

/// ID: 204490 Sigil of Silence
class spell_sigil_of_silence : public AuraScript
{
    PrepareAuraScript(spell_sigil_of_silence);

    enum eDemonMuzzleConduit
    {
        DemonicMuzzle = 339587,
        ProcSpell = 339589,
    };

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (auto caster = GetCaster())
            if (auto eff = caster->GetAuraEffect(DemonicMuzzle, EFFECT_0))
                if (auto target = GetTarget())
                    caster->CastSpell(target, ProcSpell, CastSpellExtraArgs(true).AddSpellBP0(eff->ConduitRankEntry->AuraPointsOverride));
    }

    void Register() override
    {
        OnEffectRemove += AuraEffectRemoveFn(spell_sigil_of_silence::HandleRemove, EFFECT_0, SPELL_AURA_MOD_SILENCE, AURA_EFFECT_HANDLE_REAL);
    }
};

void AddSC_spell_dh_vengeance()
{
    RegisterSpellScript(spell_sigil_of_silence);
}
