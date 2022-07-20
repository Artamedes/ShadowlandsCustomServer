#include "spell_hunter.h"

using namespace Hunter;

/// ID: 260309 Master Marksman
class spell_master_marksman : public AuraScript
{
    PrepareAuraScript(spell_master_marksman);

    enum eMasterMarksman
    {
        MasterMarksmanDot = 269576,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetDamageInfo() && eventInfo.GetHitMask() & ProcFlagsHit::PROC_HIT_CRITICAL;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetDamageInfo())
            return;

        if (auto caster = GetCaster())
        {
            if (auto target = eventInfo.GetActionTarget())
            {
                caster->CastSpell(target, eMasterMarksman::MasterMarksmanDot, CastSpellExtraArgs(true).AddSpellBP0(CalculatePct(eventInfo.GetDamageInfo()->GetDamage(), 15)));
            }
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_master_marksman::CheckProc);
        OnProc += AuraProcFn(spell_master_marksman::HandleProc);
    }
};
/// ID: 321460 Dead Eye
class spell_dead_eye : public AuraScript
{
    PrepareAuraScript(spell_dead_eye);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == KillShot;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_dead_eye::CheckProc);
    }
};

void AddSC_spell_hunter_marksman()
{
    RegisterSpellScript(spell_master_marksman);
    RegisterSpellScript(spell_dead_eye);
}
