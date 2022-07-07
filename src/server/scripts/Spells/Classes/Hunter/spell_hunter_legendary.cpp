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
/// ID: 336892 Secrets of the Unblinking Vigil
class spell_secrets_of_the_unblinking_vigil_proc : public AuraScript
{
    PrepareAuraScript(spell_secrets_of_the_unblinking_vigil_proc);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == AimedShot;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        Remove();
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_secrets_of_the_unblinking_vigil_proc::CheckProc);
        OnProc += AuraProcFn(spell_secrets_of_the_unblinking_vigil_proc::HandleProc);
    }
};

/// ID: 336867 Surging Shots
class spell_surging_shots : public AuraScript
{
    PrepareAuraScript(spell_surging_shots);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == AimedShot;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto caster = GetCaster())
            caster->GetSpellHistory()->ResetCooldown(RapidFire);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_surging_shots::CheckProc);
        OnProc += AuraProcFn(spell_surging_shots::HandleProc);
    }
};

/// ID: 336907 Butcher's Bone Fragments
class spell_butchers_bone_fragments : public AuraScript
{
    PrepareAuraScript(spell_butchers_bone_fragments);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && (eventInfo.GetSpellInfo()->Id == RaptorStrike || eventInfo.GetSpellInfo()->Id == MongooseBite);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_butchers_bone_fragments::CheckProc);
    }
};

/// ID: 336902 Latent Poison Injectors
class spell_latent_poison_injectors : public AuraScript
{
    PrepareAuraScript(spell_latent_poison_injectors);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == SerpentSting;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_latent_poison_injectors::CheckProc);
    }
};

/// ID: 336901 Rylakstalker's Confounding Strikes
class spell_rylakstalkers_confounding_strikes : public AuraScript
{
    PrepareAuraScript(spell_rylakstalkers_confounding_strikes);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && (eventInfo.GetSpellInfo()->Id == MongooseBite || eventInfo.GetSpellInfo()->Id == RaptorStrike);
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto caster = GetCaster())
            caster->GetSpellHistory()->ResetCooldown(WildfireBomb);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_rylakstalkers_confounding_strikes::CheckProc);
        OnProc += AuraProcFn(spell_rylakstalkers_confounding_strikes::HandleProc);
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
    RegisterSpellScript(spell_secrets_of_the_unblinking_vigil_proc);
    RegisterSpellScript(spell_surging_shots);
    RegisterSpellScript(spell_butchers_bone_fragments);
    RegisterSpellScript(spell_rylakstalkers_confounding_strikes);
}
