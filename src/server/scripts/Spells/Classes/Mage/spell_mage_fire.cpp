#include "spell_mage.h"

using namespace Mage;

/// ID: 336821 Infernal Cascade
class spell_infernal_cascade : public AuraScript
{
    PrepareAuraScript(spell_infernal_cascade);

    enum eInfernalCascade
    {
        InfernalCascadeProc = 336832,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        auto caster = GetCaster();
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == FireBlast && caster && caster->HasAura(Combustion);
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto caster = GetCaster())
            if (auto eff = GetEffect(EFFECT_0))
                if (eff->ConduitRankEntry)
                    caster->CastSpell(caster, InfernalCascadeProc, CastSpellExtraArgs(true).AddSpellBP0(eff->ConduitRankEntry->AuraPointsOverride));
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_infernal_cascade::CheckProc);
        OnProc += AuraProcFn(spell_infernal_cascade::HandleProc);
    }
};

void AddSC_spell_mage_fire()
{
    RegisterSpellScript(spell_infernal_cascade);
}
