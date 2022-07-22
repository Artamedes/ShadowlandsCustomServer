#include "SpellIncludes.h"

enum eBrewmaster
{
    KegSmash = 121253,
};

/// ID: 366792 Keg of the Heavens
class spell_keg_of_the_heavens : public AuraScript
{
    PrepareAuraScript(spell_keg_of_the_heavens);

    enum eKegOfTheHeavens
    {
        KegHeal     = 366793,
        KegHealth   = 366794,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == KegSmash && eventInfo.GetDamageInfo() && eventInfo.GetDamageInfo()->GetDamage();
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();
        if (!eventInfo.GetDamageInfo())
            return;

        if (auto caster = GetCaster())
        {
            auto health = caster->GetMaxHealth();

            if (auto aur = caster->GetAuraEffect(KegHealth, EFFECT_0))
                health -= aur->GetAmount();


            auto amount = CalculatePct(eventInfo.GetDamageInfo()->GetDamage(), 66);
            caster->CastSpell(caster, KegHeal, CastSpellExtraArgs(true).AddSpellBP0(amount));
            caster->CastSpell(caster, KegHealth, CastSpellExtraArgs(true).AddSpellBP0(amount));

            if (auto aur = caster->GetAuraEffect(KegHealth, EFFECT_0))
            {
                if (aur->GetAmount() >= health)
                {
                    aur->ChangeAmount(health);
                }
            }
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_keg_of_the_heavens::CheckProc);
        OnProc += AuraProcFn(spell_keg_of_the_heavens::HandleProc);
    }
};

/// ID: 115203 Fortifying Brew
class spell_fortifying_brew : public SpellScript
{
    PrepareSpellScript(spell_fortifying_brew);

    enum eFortifyingBrew
    {
        FortifyingBrewBuff = 120954,
        FortifyingIngredients = 336853,
        FortifyingIngredientsProc = 336874,
    };

    void HandleDummy(SpellEffIndex /*eff*/)
    {
        if (auto caster = GetCaster())
        {
            caster->CastSpell(caster, FortifyingBrewBuff, true);

            if (auto eff = caster->GetAuraEffect(FortifyingIngredients, EFFECT_0))
            {
                if (eff->ConduitRankEntry)
                {
                    caster->CastSpell(caster, FortifyingIngredientsProc, CastSpellExtraArgs(true).AddSpellBP0(caster->CountPctFromMaxHealth((eff->ConduitRankEntry->AuraPointsOverride))));
                }
            }
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_fortifying_brew::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

void AddSC_spell_monk_brewmaster()
{
    RegisterSpellScript(spell_keg_of_the_heavens);
    RegisterSpellScript(spell_fortifying_brew);
}
