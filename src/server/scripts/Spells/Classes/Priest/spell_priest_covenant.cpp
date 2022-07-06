#include "SpellIncludes.h"

enum ePriest
{
    DesperatePrayer = 19236,
};

/// ID: 337748 Light's Inspiration
class spell_lights_inspiration : public AuraScript
{
    PrepareAuraScript(spell_lights_inspiration);

    enum eLightInspiration
    {
        ProcSpell = 337749,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetSpellInfo())
            return false;

        return eventInfo.GetSpellInfo()->Id == DesperatePrayer;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto caster = GetCaster())
            if (auto eff = GetEffect(EFFECT_0))
                if (eff->ConduitRankEntry)
                    caster->CastSpell(caster, ProcSpell, CastSpellExtraArgs(true).AddSpellBP0(eff->ConduitRankEntry->AuraPointsOverride));
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_lights_inspiration::CheckProc);
        OnProc += AuraProcFn(spell_lights_inspiration::HandleProc);
    }
};

void AddSC_spell_priest_covenant()
{
    RegisterSpellScript(spell_lights_inspiration);
}
