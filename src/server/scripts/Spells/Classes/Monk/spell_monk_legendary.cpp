#include "spell_monk.h"

using namespace Monk;

/// ID: 337298 Invoker's Delight
class spell_invokers_delight : public AuraScript
{
    PrepareAuraScript(spell_invokers_delight);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetSpellInfo())
            return false;

        switch (eventInfo.GetSpellInfo()->Id)
        {
            case InvokeNiuzaoTheBlackOx:
            case InvokeXuenThewhiteTiger:
            case InvokeYulonTheJadeSerpent:
                return true;
            default:
                return false;
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_invokers_delight::CheckProc);
    }
};

/// ID: 356592 Bountiful Brew
class spell_bountiful_brew : public AuraScript
{
    PrepareAuraScript(spell_bountiful_brew);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetSpellInfo())
            return false;

        switch (eventInfo.GetSpellInfo()->Id)
        {
            case InvokeNiuzaoTheBlackOx:
            case InvokeXuenThewhiteTiger:
            case InvokeYulonTheJadeSerpent:
                return false;
            default:
                return true;
        }
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto target = eventInfo.GetProcTarget())
        {
            if (auto caster = GetCaster())
            {
                caster->CastSpell(*target, BonedustBrew, true);
            }
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_bountiful_brew::CheckProc);
        OnProc += AuraProcFn(spell_bountiful_brew::HandleProc);
    }
};

/// ID: 338138 Charred Passions
class spell_charred_passions : public AuraScript
{
    PrepareAuraScript(spell_charred_passions);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == BreathOfFire;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_charred_passions::CheckProc);
    }
};

/// ID: 338140 Charred Passions
class spell_charred_passions_proc : public AuraScript
{
    PrepareAuraScript(spell_charred_passions_proc);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && (eventInfo.GetSpellInfo()->Id == BlackoutKick || eventInfo.GetSpellInfo()->Id == SpinningCraneKick);
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto target = eventInfo.GetProcTarget())
        {
            if (auto caster = GetCaster())
            {
                if (auto breathOfFire = target->GetAura(BreathOfFire, caster->GetGUID()))
                    breathOfFire->RefreshDuration();

                if (auto dmgInfo = eventInfo.GetDamageInfo())
                {
                    dmgInfo->ModifyDamage(CalculatePct(eventInfo.GetDamageInfo()->GetDamage(), 100));
                }
            }
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_charred_passions_proc::CheckProc);
        OnProc += AuraProcFn(spell_charred_passions_proc::HandleProc);
    }
};

/// ID: 337290 Mighty Pour
class spell_mighty_pour : public AuraScript
{
    PrepareAuraScript(spell_mighty_pour);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id ==PurifyingBrew;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_mighty_pour::CheckProc);
        OnProc += AuraProcFn(spell_mighty_pour::HandleProc);
    }
};

/// ID: 337172 Ancient Teachings of the Monastery
class spell_ancient_teachings_of_the_monastery : public AuraScript
{
    PrepareAuraScript(spell_ancient_teachings_of_the_monastery);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == EssenceFont;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto caster = GetCaster())
            caster->CastSpell(caster, eLegendary::AncientTeachesOfTheMonastary, true);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_ancient_teachings_of_the_monastery::CheckProc);
        OnProc += AuraProcFn(spell_ancient_teachings_of_the_monastery::HandleProc);
    }
};

/// ID: 337225 Yu'lon's Whisper
class spell_yulons_whisper : public AuraScript
{
    PrepareAuraScript(spell_yulons_whisper);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == ThunderFocusTea;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_yulons_whisper::CheckProc);
    }
};

/// ID: 337483 Jade Ignition
class spell_jade_ignition : public AuraScript
{
    PrepareAuraScript(spell_jade_ignition);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == FistsOfFury;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_jade_ignition::CheckProc);
    }
};

/// ID: 337292 Last Emperor's Capacitor
class spell_last_emperors_capacitor : public AuraScript
{
    PrepareAuraScript(spell_last_emperors_capacitor);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetProcSpell() && eventInfo.GetProcSpell()->GetPowerCost(Powers::POWER_CHI);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_last_emperors_capacitor::CheckProc);
    }
};

/// ID: 337481 Xuen's Battlegear
class spell_xuens_battlegear : public AuraScript
{
    PrepareAuraScript(spell_xuens_battlegear);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == RisingSunKick && eventInfo.GetHitMask() & ProcFlagsHit::PROC_HIT_CRITICAL;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto caster = GetCaster())
            caster->GetSpellHistory()->ModifyCooldown(FistsOfFury, -5000);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_xuens_battlegear::CheckProc);
        OnProc += AuraProcFn(spell_xuens_battlegear::HandleProc);
    }
};

void AddSC_spell_monk_legendary()
{
    RegisterSpellScript(spell_invokers_delight);
    RegisterSpellScript(spell_charred_passions);
    RegisterSpellScript(spell_charred_passions_proc);
    RegisterSpellScript(spell_yulons_whisper);
    RegisterSpellScript(spell_jade_ignition);
    RegisterSpellScript(spell_last_emperors_capacitor);
    RegisterSpellScript(spell_xuens_battlegear); 
}
