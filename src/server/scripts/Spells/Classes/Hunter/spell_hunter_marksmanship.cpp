#include "SpellIncludes.h"

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

void AddSC_spell_hunter_marksman()
{
    RegisterSpellScript(spell_master_marksman);
}
