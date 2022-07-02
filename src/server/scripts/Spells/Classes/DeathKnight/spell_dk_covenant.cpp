#include "SpellIncludes.h"

enum eDeathKnightSpells
{
    Lichborne = 49039,
};

/// ID: 337972 Hardened Bones
class spell_hardened_bones : public AuraScript
{
    PrepareAuraScript(spell_hardened_bones);

    enum eHardenedBones
    {
        SpellProc = 337973,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetSpellInfo())
            return false;

        return eventInfo.GetSpellInfo()->Id == Lichborne;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto caster = GetCaster())
            if (auto effect = GetEffect(EFFECT_0))
                if (effect->ConduitRankEntry)
                    caster->CastSpell(caster, SpellProc, CastSpellExtraArgs(true).AddSpellBP0(effect->ConduitRankEntry->AuraPointsOverride));
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_hardened_bones::CheckProc);
        OnProc += AuraProcFn(spell_hardened_bones::HandleProc);
    }
};

void AddSC_spell_dk_covenant()
{
    RegisterSpellScript(spell_hardened_bones);
}
