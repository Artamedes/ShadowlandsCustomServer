#include "spell_mage.h"

using namespace Mage;

enum ArcaneOrb
{
    ArcaneOrbDmg = 153640,
};

/// Arcane Orb - 153626
/// AreaTriggerID - 1612
/// Last Update 9.2.5.44061
struct at_mage_arcane_orb : AreaTriggerAI
{
    at_mage_arcane_orb(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger) { }

    void OnUnitEnter(Unit* unit) override
    {
        if (Unit* caster = at->GetCaster())
            if (caster->IsValidAttackTarget(unit))
                caster->CastSpell(unit, ArcaneOrbDmg, true);
    }
};

/// ID: 363682 Arcane Lucidity
class spell_arcane_lucidity : public AuraScript
{
    PrepareAuraScript(spell_arcane_lucidity);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == TouchOfTheMagi;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_arcane_lucidity::CheckProc);
    }
};

void AddSC_spell_mage_arcane()
{
    RegisterAreaTriggerAI(at_mage_arcane_orb);
    RegisterSpellScript(spell_arcane_lucidity);
}
