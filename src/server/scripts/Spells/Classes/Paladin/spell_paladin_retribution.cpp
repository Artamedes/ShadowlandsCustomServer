#include "SpellIncludes.h"
#include "spell_paladin.h"

using namespace Paladin;

enum eRetribution
{
    DivineTempest = 186775, ///< Areatrigger - 4366
    DivineStormDmg = 224239,
    TempestOfTheLightbringer = 337257,
};

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

    void HandleBeforeCast()
    {
        auto caster = GetCaster();
        if (!caster)
            return;

        if (caster->Variables.Exist("DivineStormDamage"))
            caster->Variables.Remove("DivineStormDamage");
    }

    void HandleAfterCast()
    {
        auto caster = GetCaster();
        if (!caster)
            return;

        if (caster->Variables.Exist("EmpoweredDivineStorm"))
            caster->Variables.Remove("EmpoweredDivineStorm");

        if (caster->HasAura(TempestOfTheLightbringer))
            caster->CastSpell(caster, DivineTempest, true);
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
        BeforeCast += SpellCastFn(spell_pal_divine_storm::HandleBeforeCast);
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

/// ID: 336872 Final Verdict
class spell_final_verdict : public SpellScript
{
    PrepareSpellScript(spell_final_verdict);

    enum eFinalVerdict
    {
        FinalVerdictHammerOfWrathProc = 337228,
    };

    void HandleDummy(SpellEffIndex /*eff*/)
    {
        if (auto caster = GetCaster())
        {
            if (roll_chance_i(15))
                caster->CastSpell(caster, FinalVerdictHammerOfWrathProc, true);
        }

    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_final_verdict::HandleDummy, EFFECT_1, SPELL_EFFECT_DUMMY);
    }
};

/// ID: 337228 Final Verdict
class spell_final_verdict_proc : public AuraScript
{
    PrepareAuraScript(spell_final_verdict_proc);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == 24275; ///< Hammer of wrath
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_final_verdict_proc::CheckProc);
    }
};

/// ID: 339374 Truth's Wake
class spell_truths_wake : public AuraScript
{
    PrepareAuraScript(spell_truths_wake);

    enum eTruthsWake
    {
        TruthsWakeDot = 339376,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == 255937 && eventInfo.GetDamageInfo(); ///< Wake of ashes
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto caster = GetCaster())
        {
            if (auto target = eventInfo.GetActionTarget())
            {
                if (auto aurEff = GetEffect(EFFECT_0))
                    if (aurEff->ConduitRankEntry)
                        if (eventInfo.GetDamageInfo())
                        {
                            auto dam = eventInfo.GetDamageInfo()->GetDamage();
                            dam = CalculatePct(dam, aurEff->ConduitRankEntry->AuraPointsOverride);
                            caster->CastSpell(target, TruthsWakeDot, CastSpellExtraArgs(true).AddSpellBP0(dam));
                        }
            }
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_truths_wake::CheckProc);
        OnProc += AuraProcFn(spell_truths_wake::HandleProc);
    }
};

enum eVirtousCommandConduit
{
    VirtousCommandConduit = 339518,
    VirtousCommandProc = 339664,
    VirtousCommandDmg = 339669,
};

/// ID: 339518 Virtuous Command
class spell_virtuous_command : public AuraScript
{
    PrepareAuraScript(spell_virtuous_command);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == PaladinSpells::Judgement && eventInfo.GetDamageInfo() && eventInfo.GetDamageInfo()->GetDamage() > 0;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto caster = GetCaster())
            caster->CastSpell(caster, VirtousCommandProc, true);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_virtuous_command::CheckProc);
        OnProc += AuraProcFn(spell_virtuous_command::HandleProc);
    }
};

/// ID: 339664 Virtuous Command
class spell_virtuous_command_proc : public AuraScript
{
    PrepareAuraScript(spell_virtuous_command_proc);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetDamageInfo())
            return false;

        if (!eventInfo.GetDamageInfo()->GetDamage())
            return false;

        if (eventInfo.GetSpellInfo())
        {
            switch (eventInfo.GetSpellInfo()->Id)
            {
                case 336872: ///< Final verdict
                case TemplarsVerdict:
                case BladeOfJustice:
                case CrusaderStrike:
                    return true;

                default:
                    return false;
            }
        }

        return true;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto caster = GetCaster())
        {
            if (auto target = eventInfo.GetActionTarget())
            {
                if (eventInfo.GetDamageInfo())
                {
                    if (auto aurEff = caster->GetAuraEffect(VirtousCommandConduit, EFFECT_0))
                    {
                        if (aurEff->ConduitRankEntry)
                        {
                            auto dmg = eventInfo.GetDamageInfo()->GetDamage();
                            dmg = CalculatePct(dmg, aurEff->ConduitRankEntry->AuraPointsOverride);
                            caster->CastSpell(target, eVirtousCommandConduit::VirtousCommandDmg, CastSpellExtraArgs(true).AddSpellBP0(dmg));
                        }
                    }
                }
            }
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_virtuous_command_proc::CheckProc);
        OnProc += AuraProcFn(spell_virtuous_command_proc::HandleProc);
    }
};

/// ID: 339531 Templar's Vindication
class spell_templars_vindication : public AuraScript
{
    PrepareAuraScript(spell_templars_vindication);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetSpellInfo())
            return false;

        switch (eventInfo.GetSpellInfo()->Id)
        {
            case TemplarsVerdict:
            case 336872: ///< Final verdict
                return roll_chance_i(GetEffect(EFFECT_0)->GetAmount());
            default:
                return false;
        }
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto caster = GetCaster())
        {
            if (auto target = eventInfo.GetActionTarget())
            {
                if (auto spellInfo = eventInfo.GetSpellInfo())
                {
                    caster->CastSpell(target, spellInfo->Id, true);
                }
            }
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_templars_vindication::CheckProc);
        OnProc += AuraProcFn(spell_templars_vindication::HandleProc);
    }
};

// 4366
struct at_divine_tempest : public AreaTriggerAI
{
public:
    at_divine_tempest(AreaTrigger* at) : AreaTriggerAI(at)
    {

    }

    void OnUnitEnter(Unit* who) override
    {
        if (auto caster = at->GetCaster())
        {
            if (caster->IsValidAttackTarget(who))
            {
                caster->CastSpell(who, DivineStormDmg, CastSpellExtraArgs(TRIGGERED_FULL_MASK | TRIGGERED_CASTED_BY_AREATRIGGER));
            }
        }
    }
};

void AddSC_spell_paladin_retribution()
{
    RegisterSpellScript(spell_pal_divine_storm);
    RegisterSpellScript(spell_expurgation);
    RegisterSpellScript(spell_execution_sentence);
    //RegisterSpellScript(spell_execution_sentence_dmg);
    RegisterSpellScript(spell_final_verdict);
    RegisterSpellScript(spell_final_verdict_proc);
    RegisterSpellScript(spell_truths_wake);
    RegisterSpellScript(spell_virtuous_command);
    RegisterSpellScript(spell_virtuous_command_proc);
    RegisterSpellScript(spell_templars_vindication);

    RegisterAreaTriggerAI(at_divine_tempest);
}
