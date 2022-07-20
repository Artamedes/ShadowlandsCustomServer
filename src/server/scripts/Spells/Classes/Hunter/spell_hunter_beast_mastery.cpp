#include "spell_hunter.h"

using namespace Hunter;

/// ID: 257944 Thrill of the Hunt
class spell_thrill_of_the_hunt : public AuraScript
{
    PrepareAuraScript(spell_thrill_of_the_hunt);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == BarbedShot;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_thrill_of_the_hunt::CheckProc);
    }
};

void AddSC_spell_hunter_beast_mastery()
{
    RegisterSpellScript(spell_thrill_of_the_hunt);
}
