#include "spell_warrior.h"

using namespace Warrior;

enum eArms
{
    MercilessBonegrinderConduit = 335260,
    MercilessBonegrinderProc    = 346574,
};

void ProcMercilessBonegrinder(Unit* caster)
{
    if (!IsSpec(caster, SimpleTalentSpecs::Arms))
        return;

    if (auto aur = caster->GetAuraEffect(MercilessBonegrinderConduit, EFFECT_0))
        if (aur->ConduitRankEntry)
            caster->CastSpell(caster, MercilessBonegrinderProc, CastSpellExtraArgs(true).AddSpellBP0(aur->ConduitRankEntry->AuraPointsOverride));
}

/// ID: 227847 Bladestorm
/// ID: 152277 Ravager
class spell_bladestorm : public AuraScript
{
    PrepareAuraScript(spell_bladestorm);

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (auto caster = GetCaster())
            ProcMercilessBonegrinder(caster);
    }

    void HandlePeriodic(AuraEffect const* aurEff)
    {
        auto caster = GetCaster();
        if (!caster)
            return;

        if (caster->HasAura(Unhinged))
        {
            if (_unhingedProcs > 0)
            {
                std::list<Unit*> randTargetsInMelee;
                caster->GetAttackableUnitListInRange(randTargetsInMelee, MELEE_RANGE);
                //randTargetsInMelee.remove_if([](Unit* unit) -> bool { return !unit->IsEngaged(); });
                if (!randTargetsInMelee.empty())
                {
                    --_unhingedProcs;

                    caster->CastAndGetSpell(*caster, UnhingedTargetFinder, true); ///< just casting here to maintain blizzlike packets
                    caster->CastSpell(Trinity::Containers::SelectRandomContainerElement(randTargetsInMelee), MortalStrike, TriggerCastFlags(TRIGGERED_FULL_MASK | TRIGGERED_DONT_CREATE_COOLDOWN | TRIGGERED_IGNORE_SPELL_AND_CATEGORY_CD));
                }

                //if (auto spell = caster->CastAndGetSpell(*caster, UnhingedTargetFinder, true))
                //{
                //    if (!spell->m_UniqueTargetInfo.empty())
                //    {
                //        auto randTargInfo = Trinity::Containers::SelectRandomContainerElement(spell->m_UniqueTargetInfo);
                //        if (caster->CastSpell(ObjectAccessor::GetUnit(*caster, randTargInfo.TargetGUID), MortalStrike, TriggerCastFlags(TRIGGERED_FULL_MASK | TRIGGERED_DONT_CREATE_COOLDOWN) == SPELL_FAILED_SUCCESS))
                //            --_unhingedProcs;
                //    }
                //}
            }
        }
    }

    uint32 _unhingedProcs = 2;

    void Register() override
    {
        if (m_scriptSpellId == Ravager)
        {
            OnEffectRemove += AuraEffectApplyFn(spell_bladestorm::HandleRemove, EFFECT_2, SPELL_AURA_PERIODIC_DUMMY, AURA_EFFECT_HANDLE_REAL);
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_bladestorm::HandlePeriodic, EFFECT_2, SPELL_AURA_PERIODIC_DUMMY);
        }
        else
        {
            OnEffectRemove += AuraEffectApplyFn(spell_bladestorm::HandleRemove, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL, AURA_EFFECT_HANDLE_REAL);
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_bladestorm::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
        }
    }
};

/// ID: 339386 Mortal Combo
class spell_mortal_combo : public AuraScript
{
    PrepareAuraScript(spell_mortal_combo);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == MortalStrike;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto caster = GetCaster())
        {
            if (auto target = eventInfo.GetActionTarget())
            {
                caster->CastSpell(target, MortalStrike, true);
            }
        }
    }

    void HandleCalcProc(ProcEventInfo& eventInfo, float& chance)
    {
        chance = 0.0f;
        if (auto eff = GetEffect(EFFECT_0))
        {
            if (eff->ConduitRankEntry)
            {
                chance = eff->ConduitRankEntry->AuraPointsOverride;
            }
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_mortal_combo::CheckProc);
        OnProc += AuraProcFn(spell_mortal_combo::HandleProc);
        OnCalcProcChance += AuraCalcProcChanceFn(spell_mortal_combo::HandleCalcProc);
    }
};

void AddSC_spell_warrior_arms()
{
    RegisterSpellScript(spell_bladestorm);
    RegisterSpellScript(spell_mortal_combo);
}
