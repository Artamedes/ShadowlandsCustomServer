#include "spell_paladin.h"

using namespace Paladin;

/// ID: 337297 Relentless Inquisitor
class spell_relentless_inquisitor : public AuraScript
{
    PrepareAuraScript(spell_relentless_inquisitor);

    enum eRelentlessInquisitor
    {
        RelentlessInquisitor = 337315,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetProcSpell() && eventInfo.GetProcSpell()->GetPowerCost(Powers::POWER_HOLY_POWER);
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto caster = GetCaster())
            caster->CastSpell(caster, RelentlessInquisitor, true);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_relentless_inquisitor::CheckProc);
        OnProc += AuraProcFn(spell_relentless_inquisitor::HandleProc);
    }
};

void AddSC_spell_paladin_legendary()
{
    RegisterSpellScript(spell_relentless_inquisitor);
}
