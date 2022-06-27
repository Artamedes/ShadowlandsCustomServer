#include "SpellIncludes.h"

enum eBlood
{
    // Blood DK Spells
    BloodBoil = 50842,
};

/// ID: 338516 Debilitating Malady
class spell_debilitating_malady : public AuraScript
{
    PrepareAuraScript(spell_debilitating_malady);

    enum eDebilitatingMalady
    {
        DebilitatingMalady = 338523,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {

        if (!eventInfo.GetSpellInfo())
            return false;

        return eventInfo.GetSpellInfo()->Id == BloodBoil;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();

        if (auto caster = GetCaster())
            if (auto target = eventInfo.GetActionTarget())
                if (auto effect = GetEffect(EFFECT_0))
                    if (effect->ConduitRankEntry)
                        caster->CastSpell(target, DebilitatingMalady, CastSpellExtraArgs(true).AddSpellBP0(effect->ConduitRankEntry->AuraPointsOverride));
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_debilitating_malady::CheckProc);
        OnProc += AuraProcFn(spell_debilitating_malady::HandleProc);
    }
};


void AddSC_spell_dk_blood()
{
    RegisterSpellScript(spell_debilitating_malady);
}
