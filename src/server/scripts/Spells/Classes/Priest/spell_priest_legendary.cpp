#include "spell_priest.h"

using namespace Priest;

enum eMeasuredContemplation
{
    MeasuredContemplationProcAura = 341824,
    MeasuredContemplationVisual   = 343290,
};

/// ID: 341804 Measured Contemplation
class spell_measured_contemplation : public AuraScript
{
    PrepareAuraScript(spell_measured_contemplation);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && (eventInfo.GetSpellInfo()->Id == FlashHeal || eventInfo.GetSpellInfo()->Id == Shadowmend);
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        _nextCheckTime = GameTime::Now() + 15s;
    }

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
        auto now = GameTime::Now();

        if (now >= _nextCheckTime)
        {
            _nextCheckTime = GameTime::Now() + 15s;
            if (auto caster = GetCaster())
            {
                caster->CastSpell(caster, MeasuredContemplationProcAura, true);
                caster->CastSpell(caster, MeasuredContemplationVisual, true);
            }
        }
    }

    TimePoint _nextCheckTime;

    void Register() override
    {
        _nextCheckTime = GameTime::Now() + 15s;

        DoCheckProc += AuraCheckProcFn(spell_measured_contemplation::CheckProc);
        OnProc += AuraProcFn(spell_measured_contemplation::HandleProc);
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_measured_contemplation::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE);
    }
};

/// ID: 341824 Measured Contemplation
class spell_measured_contemplation_proc : public AuraScript
{
    PrepareAuraScript(spell_measured_contemplation_proc);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && (eventInfo.GetSpellInfo()->Id == FlashHeal || eventInfo.GetSpellInfo()->Id == Shadowmend);
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        ModStackAmount(-1);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_measured_contemplation_proc::CheckProc);
        OnProc += AuraProcFn(spell_measured_contemplation_proc::HandleProc);
    }
};

/// ID: 336067 Clarity of Mind
class spell_clarity_of_mind : public AuraScript
{
    PrepareAuraScript(spell_clarity_of_mind);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == SpiritShell;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        auto caster = GetCaster();
        if (!caster)
            return;

        std::list<Unit*> friendlies;
        caster->GetFriendlyUnitListInRange(friendlies, 40.0f);
        for (auto friendly : friendlies)
        {
            if (auto atonement = friendly->GetAura(AtonementAura, caster->GetGUID()))
                atonement->ModDuration(3000);
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_clarity_of_mind::CheckProc);
        OnProc += AuraProcFn(spell_clarity_of_mind::HandleProc);
    }
};

/// ID: 336011 The Penitent One
class spell_the_penitent_one : public AuraScript
{
    PrepareAuraScript(spell_the_penitent_one);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == PowerWordRadiance;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_the_penitent_one::CheckProc);
    }
};

/// ID: 336009 The Penitent One
class spell_the_penitent_one_proc : public AuraScript
{
    PrepareAuraScript(spell_the_penitent_one_proc);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == Penance;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        Remove();
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_the_penitent_one_proc::CheckProc);
        OnProc += AuraProcFn(spell_the_penitent_one_proc::HandleProc);
    }
};

void AddSC_spell_priest_legendary()
{
    RegisterSpellScript(spell_measured_contemplation);
    RegisterSpellScript(spell_measured_contemplation_proc);
    RegisterSpellScript(spell_clarity_of_mind);
    RegisterSpellScript(spell_the_penitent_one);
    RegisterSpellScript(spell_the_penitent_one_proc);
}
