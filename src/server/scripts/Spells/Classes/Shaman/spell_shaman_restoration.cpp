#include "SpellIncludes.h"

enum eRestoration
{
    HealingWave  = 77472,
    HealingSurge = 8004,
    Riptide      = 61295,
    ChainHeal    = 1064,
};

/// ID: 364470 Heal the Soul
class spell_heal_the_soul_proc : public AuraScript
{
    PrepareAuraScript(spell_heal_the_soul_proc);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetHitMask() & ProcFlagsHit::PROC_HIT_CRITICAL;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_heal_the_soul_proc::CheckProc);
    }
};

/// ID: 366779 Heal the Soul
class spell_heal_the_soul : public AuraScript
{
    PrepareAuraScript(spell_heal_the_soul);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == ChainHeal;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        Remove();
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_heal_the_soul::CheckProc);
        OnProc += AuraProcFn(spell_heal_the_soul::HandleProc);
    }
};
/// ID: 207401 Ancestral Vigor
class spell_ancestral_vigor : public AuraScript
{
    PrepareAuraScript(spell_ancestral_vigor);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetSpellInfo())
            return false;

        switch (eventInfo.GetSpellInfo()->Id)
        {
            case HealingWave:
            case HealingSurge:
            case Riptide:
                return true;
            default:
                return false;
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_ancestral_vigor::CheckProc);
    }
};


void AddSC_spell_shaman_restoration()
{
    RegisterSpellScript(spell_heal_the_soul_proc);
    RegisterSpellScript(spell_heal_the_soul);
    RegisterSpellScript(spell_ancestral_vigor);
}
