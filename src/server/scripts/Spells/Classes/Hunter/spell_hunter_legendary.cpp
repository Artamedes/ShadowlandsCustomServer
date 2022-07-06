#include "spell_hunter.h"

using namespace Hunter;

/// ID: 336747 Craven Strategem
class spell_craven_strategem : public AuraScript
{
    PrepareAuraScript(spell_craven_strategem);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == FeignDeath;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_craven_strategem::CheckProc);
    }
};

/// ID: 356262 Pact of the Soulstalkers
class spell_pact_of_the_soulstalkers : public AuraScript
{
    PrepareAuraScript(spell_pact_of_the_soulstalkers);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == ResonatingArrowMissle;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_pact_of_the_soulstalkers::CheckProc);
    }
};

void AddSC_spell_hunter_legendary()
{
    RegisterSpellScript(spell_craven_strategem);
    RegisterSpellScript(spell_pact_of_the_soulstalkers);
}
