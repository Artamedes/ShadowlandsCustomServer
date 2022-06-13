#include "SpellIncludes.h"

enum eShadow
{
    MindFlay = 15407,
    MindSear = 48045,
    MindBlast = 8092,
    DevouringPlague = 335467,

    DarkThoughtProc = 341207,
};

/// ID: 341205 Dark Thoughts
class spell_dark_thoughts : public AuraScript
{
    PrepareAuraScript(spell_dark_thoughts);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetSpellInfo())
            return false;

        switch (eventInfo.GetSpellInfo()->Id)
        {
            case eShadow::MindFlay:
            case eShadow::MindSear:
                return true;
            default:
                return false;
        }
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();

        if (auto caster = GetCaster())
        {
            caster->CastSpell(caster, DarkThoughtProc, true);
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_dark_thoughts::CheckProc);
        OnProc += AuraProcFn(spell_dark_thoughts::HandleProc);
    }
};

/// ID: 341207 Dark Thought
class spell_dark_thought : public AuraScript
{
    PrepareAuraScript(spell_dark_thought);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetSpellInfo())
            return false;

        switch (eventInfo.GetSpellInfo()->Id)
        {
            case eShadow::MindBlast:
                return true;
            default:
                return false;
        }
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();
        if (auto aur = GetAura())
            aur->Remove();
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_dark_thought::CheckProc);
        OnProc += AuraProcFn(spell_dark_thought::HandleProc);
    }
};

/// ID: 364424 Darkened Mind
class spell_darkened_mind : public AuraScript
{
    PrepareAuraScript(spell_darkened_mind);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetSpellInfo())
            return false;

        switch (eventInfo.GetSpellInfo()->Id)
        {
            case eShadow::DevouringPlague:
                return roll_chance_i(40);
            default:
                return false;
        }
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();

        if (auto caster = GetCaster())
        {
            caster->CastSpell(caster, DarkThoughtProc, true);
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_darkened_mind::CheckProc);
        OnProc += AuraProcFn(spell_darkened_mind::HandleProc);
    }
};

/// ID: 363469 Living Shadow
class spell_living_shadow : public AuraScript
{
    PrepareAuraScript(spell_living_shadow);

    enum eLivingShadow
    {
        LivingShadowProc = 363574,
        TormentMind = 363656,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        auto caster = GetCaster();
        if (!caster)
            return false;

        return caster && eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == MindBlast && caster->HasAura(DarkThoughtProc) && eventInfo.GetActionTarget();
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();
        auto caster = GetCaster();
        auto actionTarget = eventInfo.GetActionTarget();

        if (!caster || !actionTarget)
            return;

        //caster->Variables.Set("LivingShadowTarget", actionTarget->GetGUID());
        caster->CastSpell(caster, LivingShadowProc, true);
        caster->CastSpell(actionTarget, TormentMind, true);
        //std::list<Unit*> targetList;
        //caster->GetAttackableUnitListInRangeFromCenterObj(actionTarget, targetList, 10.0f);
        //
        //for (auto target : targetList)
        //{
        //    if (target->IsWithinLOSInMap(actionTarget) && target->IsWithinLOSInMap(caster))
        //        caster->CastSpell(target, TormentMind, CastSpellExtraArgs(true));
        //}
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_living_shadow::CheckProc);
        OnProc += AuraProcFn(spell_living_shadow::HandleProc);
    }
};

/// ID: 363656 Torment Mind
class spell_torment_mind : public AuraScript
{
    PrepareAuraScript(spell_torment_mind);

    enum eLivingShadow
    {
        TormentMindDam = 366971,
    };

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
        auto target = GetTarget();
        if (!target)
            return;
        auto caster = GetCaster();
        if (!caster)
            return;

        //auto dam = caster->GetTotalSpellPowerValue(SpellSchoolMask::SPELL_SCHOOL_MASK_SHADOW, false) * 0.173f;
        caster->CastSpell(target, TormentMindDam, true);
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_torment_mind::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
    }
};

void AddSC_spell_priest_shadow()
{
    RegisterSpellScript(spell_dark_thoughts);
    RegisterSpellScript(spell_dark_thought);
    RegisterSpellScript(spell_darkened_mind);
    RegisterSpellScript(spell_living_shadow);
    RegisterSpellScript(spell_torment_mind);
}
