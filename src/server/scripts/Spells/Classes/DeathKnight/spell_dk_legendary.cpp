#include "spell_dk.h"

using namespace DeathKnight;

/// ID: 335177 Phearomones
class spell_phearomones : public AuraScript
{
    PrepareAuraScript(spell_phearomones);

    enum ePhearomes
    {
        TrembleBeforeMe = 206961,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && (eventInfo.GetSpellInfo()->Id == DeathAndDecayDmg || eventInfo.GetSpellInfo()->Id == DefileDmg);
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto target = eventInfo.GetProcTarget())
            if (auto caster = GetCaster())
                caster->CastSpell(target, TrembleBeforeMe, true);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_phearomones::CheckProc);
        OnProc += AuraProcFn(spell_phearomones::HandleProc);
    }
};

void AddSC_spell_dk_legendary()
{
    RegisterSpellScript(spell_phearomones);
}
