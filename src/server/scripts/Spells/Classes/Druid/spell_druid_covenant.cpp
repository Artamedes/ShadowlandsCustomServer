#include "spell_druid.h"

using namespace Druid;

/// ID: 340540 Ursine Vigor
class spell_ursine_vigor : public AuraScript
{
    PrepareAuraScript(spell_ursine_vigor);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == BearForm;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_ursine_vigor::CheckProc);
    }
};
/// ID: 340555 Well-Honed Instincts
class spell_well_honed_instincts : public SpellScript
{
    PrepareSpellScript(spell_well_honed_instincts);

    enum eWellHonedInsticts
    {
        WellHonedConduit = 340553,
        CDAura = 340556,
        FrenziedRegen = 22842,
    };

    void HandleDummy(SpellEffIndex /*eff*/)
    {
        auto caster = GetCaster();
        if (!caster)
            return;

        if (caster->HasAura(CDAura))
            return;

        caster->CastSpell(caster, CDAura, true);

        if (auto cdAura = caster->GetAura(CDAura))
        {
            if (auto conduit = caster->GetAuraEffect(WellHonedConduit, EFFECT_0))
                if (conduit->ConduitRankEntry)
                    cdAura->SetDuration(conduit->ConduitRankEntry->AuraPointsOverride);
        }

        caster->AddAura(FrenziedRegen, caster);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_well_honed_instincts::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

void AddSC_spell_druid_covenant()
{
    RegisterSpellScript(spell_ursine_vigor);
    RegisterSpellScript(spell_well_honed_instincts);
}
