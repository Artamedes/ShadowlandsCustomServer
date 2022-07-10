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

void AddSC_spell_priest_legendary()
{
    RegisterSpellScript(spell_measured_contemplation);
    RegisterSpellScript(spell_measured_contemplation_proc);
}
