#include "SpellIncludes.h"
#include "spell_paladin.h"

using namespace Paladin;

// 53385 - Divine Storm
class spell_pal_divine_storm : public SpellScript
{
    PrepareSpellScript(spell_pal_divine_storm);

    uint32 holyPower = 0;

    void HandleTakePower(SpellPowerCost& powerCost)
    {
        if (powerCost.Power == POWER_HOLY_POWER)
            holyPower = powerCost.Amount;
    }

    void HandleAfterCast()
    {
        auto caster = GetCaster();
        if (!caster)
            return;

        if (caster->Variables.Exist("EmpoweredDivineStorm"))
            caster->Variables.Remove("EmpoweredDivineStorm");
    }

    void HandleDmg(SpellEffIndex /*eff*/)
    {
        auto caster = GetCaster();
        if (!caster)
            return;

        auto dmg = GetHitDamage();

        /// Vanquishers Hammer variable
        if (caster->Variables.Exist("EmpoweredDivineStorm"))
        {
            if (caster->Variables.GetValue("EmpoweredDivineStorm", false))
            {
               // holyPower = 3;
            }
        }

        //if (!holyPower)
        //    holyPower = 3;

        //dmg *= holyPower;

        if (caster->Variables.Exist("EmpoweredDivineStorm"))
        {
            if (caster->Variables.GetValue("EmpoweredDivineStorm", false))
            {
                AddPct(dmg, 25);
            }
        }

        SetHitDamage(dmg);
    }

    void Register() override
    {
        OnTakePower += SpellOnTakePowerFn(spell_pal_divine_storm::HandleTakePower);
        OnEffectHitTarget += SpellEffectFn(spell_pal_divine_storm::HandleDmg, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
        AfterCast += SpellCastFn(spell_pal_divine_storm::HandleAfterCast);
    }
};

/// ID: 339371 Expurgation
class spell_expurgation : public AuraScript
{
    PrepareAuraScript(spell_expurgation);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == BladeOfJustice && eventInfo.GetDamageInfo() && eventInfo.GetActionTarget();
    }

    enum eExpurgation
    {
        ExpuragionDmg = 344067,
    };

    void HandleProc(ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();
        auto caster = eventInfo.GetActor();
        auto target = eventInfo.GetActionTarget();

        if (!caster || !target)
            return;

        if (!eventInfo.GetDamageInfo())
            return;

        if (auto aurEff = caster->GetAuraEffect(GetId(), EFFECT_0))
            if (aurEff->ConduitRankEntry)
                caster->CastSpell(target, ExpuragionDmg, CastSpellExtraArgs(true).AddSpellBP0((aurEff->ConduitRankEntry->AuraPointsOverride / 100.0f) * eventInfo.GetDamageInfo()->GetDamage()));
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_expurgation::CheckProc);
        OnProc += AuraProcFn(spell_expurgation::HandleProc);
    }
};

/// ID: 343527 Execution Sentence
class spell_execution_sentence : public AuraScript
{
    PrepareAuraScript(spell_execution_sentence);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetDamageInfo() || !eventInfo.GetSpellInfo())
            return false;

        return eventInfo.GetDamageInfo()->GetDamage() > 0;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        auto caster = eventInfo.GetActor();
        auto target = eventInfo.GetActionTarget();
        if (auto dmgInfo = eventInfo.GetDamageInfo())
        {
            //damage += dmgInfo->GetDamage();

            if (auto aur = GetAura())
                if (auto eff = aur->GetEffect(EFFECT_0))
                {
                    eff->SetDamage(eff->GetDamage() + (dmgInfo->GetDamage() * 0.20f));
                    eff->SetAmount(eff->GetDamage());
                    aur->SetNeedClientUpdateForTargets();
                }

            //caster->Variables.Set("ExecutionSentenceDmg", damage);
        }
    }

    //uint32 damage = 0;

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_execution_sentence::CheckProc);
        OnProc += AuraProcFn(spell_execution_sentence::HandleProc);
    }
};

/// ID: 343527 Execution Sentence
//class spell_execution_sentence_dmg : public SpellScript
//{
//    PrepareSpellScript(spell_execution_sentence_dmg);
//
//    void HandleDummy(SpellEffIndex /*eff*/)
//    {
//        auto caster = GetCaster();
//        if (!caster)
//        {
//            auto dmg = GetHitDamage();
//            if (caster->Variables.Exist("ExecutionSentenceDmg"))
//                dmg += caster->Variables.GetValue("ExecutionSentenceDmg", 0);
//            SetHitDamage(dmg);
//        }
//    }
//
//    void Register() override
//    {
//        OnEffectHitTarget += SpellEffectFn(spell_execution_sentence_dmg::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
//    }
//};

void AddSC_spell_paladin_retribution()
{
    RegisterSpellScript(spell_pal_divine_storm);
    RegisterSpellScript(spell_expurgation);
    RegisterSpellScript(spell_execution_sentence);
    //RegisterSpellScript(spell_execution_sentence_dmg);
}
