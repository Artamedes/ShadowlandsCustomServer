#include "spell_druid.h"

using namespace Druid;

/// ID: 340540 Ursine Vigor
class spell_ursine_vigor : public AuraScript
{
    PrepareAuraScript(spell_ursine_vigor);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == BearForm;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_ursine_vigor::CheckProc);
    }
};
/// ID: 340555 Well-Honed Instincts
class spell_well_honed_instincts : public SpellScript
{
    PrepareSpellScript(spell_well_honed_instincts);

    enum eWellHonedInsticts
    {
        WellHonedConduit = 340553,
        CDAura = 340556,
        FrenziedRegen = 22842,
    };

    void HandleDummy(SpellEffIndex /*eff*/)
    {
        auto caster = GetCaster();
        if (!caster)
            return;

        if (caster->HasAura(CDAura))
            return;

        caster->CastSpell(caster, CDAura, true);

        if (auto cdAura = caster->GetAura(CDAura))
        {
            if (auto conduit = caster->GetAuraEffect(WellHonedConduit, EFFECT_0))
                if (conduit->ConduitRankEntry)
                    cdAura->SetDuration(conduit->ConduitRankEntry->AuraPointsOverride);
        }

        caster->AddAura(FrenziedRegen, caster);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_well_honed_instincts::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

/// ID: 323546 Ravenous Frenzy
class spell_ravenous_frenzy : public AuraScript
{
    PrepareAuraScript(spell_ravenous_frenzy);

    enum eRavenousFrenzy
    {
        SinfulHysteriaLegendary = 354109,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetProcSpell() && !eventInfo.GetProcSpell()->IsTriggered() && eventInfo.GetSpellInfo()->SpellFamilyName == SPELLFAMILY_DRUID;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        auto caster = GetCaster();
        if (!caster)
            return;

        bool hasLegendary = caster->HasAura(SinfulHysteriaLegendary);

        if (hasLegendary)
            _nextStunTime = GameTime::Now() + 3s;
        else
            _nextStunTime = GameTime::Now() + 2s;

        if (auto aur = GetAura())
        {
            aur->ModStackAmount(1, AURA_REMOVE_BY_DEFAULT, false, false);
            if (hasLegendary)
                aur->SetDuration(aur->GetDuration() + 100);
        }
    }

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
        auto now = GameTime::Now();

        if (now >= _nextStunTime)
        {
            auto caster = GetCaster();
            if (caster)
            {
                caster->CastSpell(caster, 323557, CastSpellExtraArgs(true).AddSpellBP0(GetStackAmount()));
                Remove();
            }
        }
    }

    void OnCalcProc(ProcEventInfo& eventInfo, float& chance)
    {
        chance = 100.0f;
    }

    TimePoint _nextStunTime;

    void Register() override
    {
        _nextStunTime = GameTime::Now() + 3s;
        DoCheckProc += AuraCheckProcFn(spell_ravenous_frenzy::CheckProc);
        OnProc += AuraProcFn(spell_ravenous_frenzy::HandleProc);
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_ravenous_frenzy::HandlePeriodic, EFFECT_2, SPELL_AURA_PERIODIC_DUMMY);
        OnCalcProcChance += AuraCalcProcChanceFn(spell_ravenous_frenzy::OnCalcProc);
    }
};

/// ID: 325727 Adaptive Swarm
class spell_adaptive_swarm : public SpellScript
{
    PrepareSpellScript(spell_adaptive_swarm);

    void HandleDummy1(SpellEffIndex /*eff*/)
    {
        auto unit = GetHitUnit();
        auto caster = GetCaster();
        if (!unit || !caster)
            return;

        if (caster->IsValidAttackTarget(unit))
        {
            caster->CastSpell(unit, 325733, true);
        }
        else
        {
            caster->CastSpell(unit, 325748, true);
        }
    }

    void HandleDummy2(SpellEffIndex /*eff*/)
    {
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_adaptive_swarm::HandleDummy1, EFFECT_0, SPELL_EFFECT_DUMMY);
        OnEffectHitTarget += SpellEffectFn(spell_adaptive_swarm::HandleDummy2, EFFECT_1, SPELL_EFFECT_DUMMY);
    }
};


void AddSC_spell_druid_covenant()
{
    RegisterSpellScript(spell_ursine_vigor);
    RegisterSpellScript(spell_well_honed_instincts);
    RegisterSpellScript(spell_ravenous_frenzy);
    RegisterSpellScript(spell_adaptive_swarm);
}
