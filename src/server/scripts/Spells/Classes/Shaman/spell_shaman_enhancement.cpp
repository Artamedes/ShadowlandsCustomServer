#include "spell_shaman.h"

using namespace Shaman;

/// ID: 334196 Hailstorm
class spell_hailstorm : public AuraScript
{
    PrepareAuraScript(spell_hailstorm);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == FrostShock;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        auto auraStacks = GetAura()->GetStackAmount();

        if (auto target = eventInfo.GetProcTarget())
            if (auto caster = GetCaster())
            {
                std::list<Unit*> targetsInMelee;
                caster->GetAttackableUnitListInRange(targetsInMelee, 40.0f);
                for (auto enemy : targetsInMelee)
                {
                    if (target == enemy)
                        continue;

                    caster->CastSpell(enemy, FrostShock, true);
                    auraStacks--;

                    if (auraStacks == 0)
                        break;
                }
            }

        Remove();
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_hailstorm::CheckProc);
        OnProc += AuraProcFn(spell_hailstorm::HandleProc);
    }
};


void AddSC_spell_shaman_enhancement()
{
    RegisterSpellScript(spell_hailstorm);
}
