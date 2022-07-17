#include "spell_druid.h"

using namespace Druid;

/// ID: 364365 Renewing Bloom
class spell_renewing_bloom : public AuraScript
{
    PrepareAuraScript(spell_renewing_bloom);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == Rejuvenation;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_renewing_bloom::CheckProc);
    }
};

void AddSC_spell_druid_restoration()
{
    RegisterSpellScript(spell_renewing_bloom);
}
