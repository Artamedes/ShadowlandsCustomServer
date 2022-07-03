#include "SpellIncludes.h"
#include "SpellAuraEffects.h"

/// ID: 357595 Banshee's Blight
class spell_banshees_blight : public AuraScript
{
    PrepareAuraScript(spell_banshees_blight);

    enum eBansheesBlight
    {
        BanesheesBlightDmg = 358126,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetProcSpell() && eventInfo.GetProcSpell()->GetUsedComboPoints() > 0;
    }

    uint32 chance = 0;

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetProcSpell() && eventInfo.GetProcSpell()->GetUsedComboPoints() > 0)
        {
            chance += eventInfo.GetProcSpell()->GetUsedComboPoints() * 9;
            if (roll_chance_i(chance))
            {
                chance = 0;
                if (auto caster = GetCaster())
                    if (auto target = eventInfo.GetActionTarget())
                    {
                        int32 dam = GetSpellInfo()->GetEffect(EFFECT_0).CalcBaseValue(caster, target, GetAura()->GetCastItemId(), GetAura()->GetCastItemLevel());

                        caster->CastSpell(target, BanesheesBlightDmg, CastSpellExtraArgs(true).AddSpellBP0(dam));
                    }
            }
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_banshees_blight::CheckProc);
        OnProc += AuraProcFn(spell_banshees_blight::HandleProc);
    }
};

void AddSC_spell_legendary()
{
    RegisterSpellScript(spell_banshees_blight);
}
