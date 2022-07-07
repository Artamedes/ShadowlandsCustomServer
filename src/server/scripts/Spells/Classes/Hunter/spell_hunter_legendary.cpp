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

/// ID: 336830 Qa'pla, Eredun War Order
class spell_qapla_eredun_war_order : public AuraScript
{
    PrepareAuraScript(spell_qapla_eredun_war_order);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == BarbedShot;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto caster = GetCaster())
            caster->GetSpellHistory()->ModifyCooldown(KillCommandBM, -5000);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_qapla_eredun_war_order::CheckProc);
        OnProc += AuraProcFn(spell_qapla_eredun_war_order::HandleProc);
    }
};

/// ID: 336849 Eagletalon's True Focus
class spell_eagletalons_true_focus : public AuraScript
{
    PrepareAuraScript(spell_eagletalons_true_focus);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == Trueshot;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_eagletalons_true_focus::CheckProc);
    }
};

/// ID: 336878 Secrets of the Unblinking Vigil
class spell_secrets_of_the_unblinking_vigil : public AuraScript
{
    PrepareAuraScript(spell_secrets_of_the_unblinking_vigil);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == TrickShotsProc;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_secrets_of_the_unblinking_vigil::CheckProc);
    }
};

void AddSC_spell_hunter_legendary()
{
    RegisterSpellScript(spell_craven_strategem);
    RegisterSpellScript(spell_pact_of_the_soulstalkers);
    RegisterSpellScript(spell_flamewakers_cobra_sting);
    RegisterSpellScript(spell_flamewakers_cobra_sting_proc);
    RegisterSpellScript(spell_qapla_eredun_war_order);
    RegisterSpellScript(spell_eagletalons_true_focus);
}
