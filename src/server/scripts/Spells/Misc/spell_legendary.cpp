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

/// ID: 338743 Vitality Sacrifice
class spell_vitality_sacrifice : public AuraScript
{
    PrepareAuraScript(spell_vitality_sacrifice);

    enum eVitalitySacrifice
    {
        ProcSpell = 338746,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        auto caster = GetCaster();

        if (caster && caster->GetSpellHistory()->HasCooldown(ProcSpell))
            return false;

        return eventInfo.GetActor() && eventInfo.GetDamageInfo() && caster && eventInfo.GetDamageInfo()->GetDamage() >= caster->CountPctFromMaxHealth(5);
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        auto caster = GetCaster();
        if (!caster)
            return;

        auto dmgInfo = eventInfo.GetDamageInfo();
        if (!dmgInfo)
            return;

        uint32 amount = 3;

        amount = uint32(float(dmgInfo->GetDamage() / caster->GetMaxHealth()) * 100.0f);

        if (amount > 9)
            amount = 9;

        caster->CastSpell(caster, ProcSpell, CastSpellExtraArgs(true).AddSpellBP0(amount).AddSpellBP1(amount));
        caster->GetSpellHistory()->AddCooldown(ProcSpell, 0, 30s);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_vitality_sacrifice::CheckProc);
        OnProc += AuraProcFn(spell_vitality_sacrifice::HandleProc);
    }
};

/// ID: 339058 Third Eye of the Jailer
class spell_third_eye_of_the_jailer : public AuraScript
{
    PrepareAuraScript(spell_third_eye_of_the_jailer);

    enum eThirdEye
    {
        ThirdEye = 339970,
    };
    
    void HandleProc(ProcEventInfo& eventInfo)
    {
        auto caster = GetCaster();
        if (!caster)
            return;

        if (auto aur = caster->GetAura(ThirdEye))
        {
            aur->ModStackAmount(1, AURA_REMOVE_BY_DEFAULT, false, false);
            // TODO: check in maw
            aur->ModDuration(1000);
        }
        else
            caster->CastSpell(caster, ThirdEye, true);
    }

    void Register() override
    {
        OnProc += AuraProcFn(spell_third_eye_of_the_jailer::HandleProc);
    }
};

void AddSC_spell_legendary()
{
    RegisterSpellScript(spell_banshees_blight);
    RegisterSpellScript(spell_vitality_sacrifice);
    RegisterSpellScript(spell_third_eye_of_the_jailer);
}
