#include "spell_paladin.h"

using namespace Paladin;

/// ID: 364304 Glorious Purpose
class spell_glorious_purpose_2pc : public AuraScript
{
    PrepareAuraScript(spell_glorious_purpose_2pc);

    enum eGloriousPurpose
    {
        ProcSpell = 364305,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == ShieldOfTheRighteous;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto caster = GetCaster())
            caster->CastSpell(caster, ProcSpell, true);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_glorious_purpose_2pc::CheckProc);
        OnProc += AuraProcFn(spell_glorious_purpose_2pc::HandleProc);
    }
};

/// ID: 363675 Glorious Purpose
class spell_glorious_purpose_4pc : public AuraScript
{
    PrepareAuraScript(spell_glorious_purpose_4pc);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetActor() && eventInfo.GetActionTarget() && eventInfo.GetActor()->IsValidAttackTarget(eventInfo.GetActionTarget());
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetActor())
            return;
        if (!eventInfo.GetActionTarget())
            return;

        eventInfo.GetActionTarget()->CastSpell(eventInfo.GetActor(), JudgementProt, CastSpellExtraArgs(TRIGGERED_FULL_MASK | TRIGGERED_DONT_CREATE_COOLDOWN));
    }

    void HandleCalcProc(ProcEventInfo& eventInfo, float& chance)
    {
        chance = 0.0f;
        if (auto caster = GetCaster())
            if (auto target = eventInfo.GetActor())
                chance = std::min(100.0f, caster->GetBlockPercent(target->GetLevel()) * 100.0f);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_glorious_purpose_4pc::CheckProc);
        OnProc += AuraProcFn(spell_glorious_purpose_4pc::HandleProc);
        OnCalcProcChance += AuraCalcProcChanceFn(spell_glorious_purpose_4pc::HandleCalcProc);
    }
};

void AddSC_spell_paladin_protection()
{
    RegisterSpellScript(spell_glorious_purpose_2pc);
    RegisterSpellScript(spell_glorious_purpose_4pc);
}
