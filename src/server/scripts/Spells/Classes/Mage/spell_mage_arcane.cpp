#include "SpellIncludes.h"

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

void AddSC_spell_mage_arcane()
{
    RegisterAreaTriggerAI(at_mage_arcane_orb);
}
