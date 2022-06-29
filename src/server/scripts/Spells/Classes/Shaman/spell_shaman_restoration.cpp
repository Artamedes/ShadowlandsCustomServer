#include "SpellIncludes.h"

enum eRestoration
{
    ChainHeal = 1064,
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

void AddSC_spell_shaman_restoration()
{
    RegisterSpellScript(spell_heal_the_soul);
}
