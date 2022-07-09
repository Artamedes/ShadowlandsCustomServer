#include "SpellIncludes.h"

enum eMonk
{
    Vivify = 116670,
};

/// ID: 336632 Grounding Breath
class spell_grounding_breath : public AuraScript
{
    PrepareAuraScript(spell_grounding_breath);

    enum eGroundBreath
    {
        ProcSpell           = 342330,
        ManaRefundSpell     = 336637,
        EnergyRefundSpell   = 336638,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetSpellInfo())
            return false;

        return eventInfo.GetSpellInfo()->Id == Vivify;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto caster = GetCaster())
            if (auto eff = GetEffect(EFFECT_0))
                if (eff->ConduitRankEntry)
                    if (eventInfo.GetActionTarget() == caster)
                    {
                        caster->CastSpell(caster, ProcSpell, CastSpellExtraArgs(true).AddSpellBP0(eff->ConduitRankEntry->AuraPointsOverride));

                        int chance = 0;
                        chance = eff->ConduitRankEntry->AuraPointsOverride;
                        
                        if (roll_chance_i(100))
                        {
                            if (IsSpec(caster, SimpleTalentSpecs::Mistweaver))
                            {
                                caster->CastSpell(caster, ManaRefundSpell, CastSpellExtraArgs(true).AddSpellBP0(eff->ConduitRankEntry->AuraPointsOverride));
                            }
                            else
                                caster->CastSpell(caster, EnergyRefundSpell, CastSpellExtraArgs(true).AddSpellBP0(eff->ConduitRankEntry->AuraPointsOverride));
                        }
                    }

    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_grounding_breath::CheckProc);
        OnProc += AuraProcFn(spell_grounding_breath::HandleProc);
    }
};

void AddSC_spell_monk_covenant()
{
    RegisterSpellScript(spell_grounding_breath);
}
