#include "spell_warlock.h"

using namespace Warlock;

/// ID: 339673 Carnivorous Stalkers
class spell_carnivorous_stalkers : public AuraScript
{
    PrepareAuraScript(spell_carnivorous_stalkers);

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto caster = GetCaster())
        {
            caster->CastSpell(caster, Dreadbite, true);
        }
    }

    void HandleCalcProcChance(ProcEventInfo& eventInfo, float& chance)
    {
        chance = 0.0f;

        if (GetEffect(EFFECT_0) && GetEffect(EFFECT_0)->ConduitRankEntry)
            chance = GetEffect(EFFECT_0)->ConduitRankEntry->AuraPointsOverride;
    }

    void Register() override
    {
        OnProc += AuraProcFn(spell_carnivorous_stalkers::HandleProc);
        OnCalcProcChance += AuraCalcProcChanceFn(spell_carnivorous_stalkers::HandleCalcProcChance);
    }
};

void AddSC_spell_warlock_demonology()
{
    RegisterSpellScript(spell_carnivorous_stalkers);
}
