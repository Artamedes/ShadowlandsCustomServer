#include "spell_dh.h"

using namespace DH;

/// ID: 338835 Ravenous Consumption
class spell_ravenous_consumption : public AuraScript
{
    PrepareAuraScript(spell_ravenous_consumption);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetSpellInfo())
            return false;

        return eventInfo.GetSpellInfo()->Id == ConsumeMagic;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto caster = GetCaster())
            if (auto eff = GetEffect(EFFECT_0))
                if (eff->ConduitRankEntry)
                    if (auto target = eventInfo.GetActionTarget())
                        caster->CastSpell(target, ConsumeMagic, true);
    }

    void OnCalcProc(ProcEventInfo& eventInfo, float& chance)
    {
        chance = 0.0f;
        if (auto eff = GetEffect(EFFECT_0))
            if (eff->ConduitRankEntry)
                chance = eff->ConduitRankEntry->AuraPointsOverride;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_ravenous_consumption::CheckProc);
        OnProc += AuraProcFn(spell_ravenous_consumption::HandleProc);
        OnCalcProcChance += AuraCalcProcChanceFn(spell_ravenous_consumption::OnCalcProc);
    }
};

void AddSC_spell_dh_covenant()
{
    RegisterSpellScript(spell_ravenous_consumption);
}
