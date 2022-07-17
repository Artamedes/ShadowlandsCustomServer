#include "spell_mage.h"

using namespace Mage;

/// ID: 363535 Frost Storm
class spell_frost_storm : public AuraScript
{
    PrepareAuraScript(spell_frost_storm);

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto caster = GetCaster())
        {
            if (auto procTarget = eventInfo.GetProcTarget())
            {
                caster->CastSpell(procTarget, CometStorm, CastSpellExtraArgs(TRIGGERED_FULL_MASK_NO_CD));
            }
        }
    }

    void Register() override
    {
        OnProc += AuraProcFn(spell_frost_storm::HandleProc);
    }
};

/// ID: 153596 Comet Storm
class spell_comet_storm_dmg : public SpellScript
{
    PrepareSpellScript(spell_comet_storm_dmg);

    void HandleDmg(SpellEffIndex /*eff*/)
    {
        if (auto caster = GetCaster())
        {
            if (auto procTarget = GetHitUnit())
            {
                if (caster->HasAura(FrostStorm4pc))
                    caster->CastSpell(procTarget, FrostStormDebuff, true);
            }
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_comet_storm_dmg::HandleDmg, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

void AddSC_spell_mage_frost()
{
    RegisterSpellScript(spell_frost_storm);
    RegisterSpellScript(spell_comet_storm_dmg);
}
