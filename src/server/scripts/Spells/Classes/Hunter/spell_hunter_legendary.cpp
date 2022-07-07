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

/// ID: 336822 Flamewaker's Cobra Sting
class spell_flamewakers_cobra_sting : public AuraScript
{
    PrepareAuraScript(spell_flamewakers_cobra_sting);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == CobraShot;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_flamewakers_cobra_sting::CheckProc);
    }
};

/// ID: 336826 Flamewaker's Cobra Sting
class spell_flamewakers_cobra_sting_proc : public AuraScript
{
    PrepareAuraScript(spell_flamewakers_cobra_sting_proc);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == KillCommandBM;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        Remove();
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_flamewakers_cobra_sting_proc::CheckProc);
        OnProc += AuraProcFn(spell_flamewakers_cobra_sting_proc::HandleProc);
    }
};

void AddSC_spell_hunter_legendary()
{
    RegisterSpellScript(spell_craven_strategem);
    RegisterSpellScript(spell_pact_of_the_soulstalkers);
    RegisterSpellScript(spell_flamewakers_cobra_sting);
    RegisterSpellScript(spell_flamewakers_cobra_sting_proc);
}
