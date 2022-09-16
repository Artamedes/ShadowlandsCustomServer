#include "spell_rogue.h"

using namespace Rogue;

enum eSubtlety
{
    Eviscerate = 196819,
    EviscerateShadowDmg = 328082,
    BlackPowder = 319175,
    SymbolsOfDeath = 212283,
    Backstab = 53,
    Shadowstrike = 185438,

    /// Debuffs
    FindWeakness = 316220,

    /// Conduits
    DeeperDaggers = 341549,
    DeeperDaggersProc = 341550,
};

/// ID: 341549 Deeper Daggers
class spell_deeper_daggers : public AuraScript
{
    PrepareAuraScript(spell_deeper_daggers);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && (eventInfo.GetSpellInfo()->Id == Eviscerate || eventInfo.GetSpellInfo()->Id == BlackPowder);
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();
        if (auto caster = GetCaster())
        {
            if (auto eff = GetEffect(EFFECT_0))
                if (eff->ConduitRankEntry)
                    caster->CastSpell(caster, DeeperDaggersProc, CastSpellExtraArgs(true).AddSpellBP0(eff->ConduitRankEntry->AuraPointsOverride));
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_deeper_daggers::CheckProc);
        OnProc += AuraProcFn(spell_deeper_daggers::HandleProc);
    }
};

/// ID: 319175 Black Powder
class spell_black_powder : public SpellScript
{
    PrepareSpellScript(spell_black_powder);

    enum eBlackPowder
    {
        BlackPowderFindWeaknessDmg = 319190,
    };

    void HandleDummy(SpellEffIndex /*eff*/)
    {
        if (auto caster = GetCaster())
        {
            if (auto spell = GetSpell())
            {
                int32 damage = GetHitDamage();
                damage *= GetSpell()->GetUsedComboPoints();
                SetHitDamage(damage);

                if (damage)
                {
                    if (auto hitUnit = GetHitUnit())
                    {
                        if (auto shadowedFinishers = caster->GetAuraEffect(ShadowedFinishers, EFFECT_0))
                        {
                            if (hitUnit->HasAura(FindWeakness, caster->GetGUID()))
                            {
                                caster->CastSpell(hitUnit, BlackPowderFindWeaknessDmg, CastSpellExtraArgs(true).AddSpellBP0(CalculatePct(damage, shadowedFinishers->GetAmount())));
                            }
                        }
                    }
                }
            }
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_black_powder::HandleDummy, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

enum eFinality
{
    FinalityEviscerate  = 340600,
    FinalityBlackPowder = 340603,
};

/// ID: 340089 Finality
class spell_finality : public AuraScript
{
    PrepareAuraScript(spell_finality);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetSpellInfo())
            return false;

        switch (eventInfo.GetSpellInfo()->Id)
        {
            case BlackPowder:
            case Rupture:
            case Eviscerate:
                return true;
            default:
                return false;
        }
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();
        if (!eventInfo.GetSpellInfo())
            return;

        auto caster = GetCaster();
        if (!caster)
            return;

        switch (eventInfo.GetSpellInfo()->Id)
        {
            case BlackPowder:
            {
                if (!caster->HasAura(FinalityBlackPowder))
                    caster->CastSpell(caster, FinalityBlackPowder, true);
                break;
            }
            case Rupture:
            {
                if (!caster->HasAura(FinalityRupture))
                    caster->CastSpell(caster, FinalityRupture, true);
                break;
            }
            case Eviscerate:
            {
                if (!caster->HasAura(FinalityEviscerate))
                    caster->CastSpell(caster, FinalityEviscerate, true);
                break;
            }
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_finality::CheckProc);
        OnProc += AuraProcFn(spell_finality::HandleProc);
    }
};

/// ID: 340600 Finality: Eviscerate
class spell_finality_eviscerate : public AuraScript
{
    PrepareAuraScript(spell_finality_eviscerate);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == Eviscerate;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();
        Remove();
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_finality_eviscerate::CheckProc);
        OnProc += AuraProcFn(spell_finality_eviscerate::HandleProc);
    }
};

/// ID: 340603 Finality: Black Powder
class spell_finality_black_powder : public AuraScript
{
    PrepareAuraScript(spell_finality_black_powder);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == BlackPowder;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();
        Remove();
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_finality_black_powder::CheckProc);
        OnProc += AuraProcFn(spell_finality_black_powder::HandleProc);
    }
};

/// ID: 340091 The Rotten
class spell_the_rotten : public AuraScript
{
    PrepareAuraScript(spell_the_rotten);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == SymbolsOfDeath;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_the_rotten::CheckProc);
    }
};

/// ID: 341134 The Rotten
class spell_the_rotten_proc : public AuraScript
{
    PrepareAuraScript(spell_the_rotten_proc);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && (eventInfo.GetSpellInfo()->Id == Shadowstrike || eventInfo.GetSpellInfo()->Id == Backstab);
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        Remove();
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_the_rotten_proc::CheckProc);
        OnProc += AuraProcFn(spell_the_rotten_proc::HandleProc);
    }
};

/// 196819 - Eviscerate
class spell_rog_eviscerate : public SpellScript
{
    PrepareSpellScript(spell_rog_eviscerate);

    void CalculateDamage(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        if (!caster)
            return;
        if (!GetSpell())
            return;

        int32 damage = GetHitDamage();
        damage *= GetSpell()->GetUsedComboPoints();
        SetHitDamage(damage);

        if (auto hitUnit = GetHitUnit())
        {
            if (auto shadowedFinishers = caster->GetAuraEffect(ShadowedFinishers, EFFECT_0))
            {
                if (hitUnit->HasAura(FindWeakness, caster->GetGUID()))
                {
                    caster->CastSpell(hitUnit, EviscerateShadowDmg, CastSpellExtraArgs(true).AddSpellBP0(CalculatePct(damage, shadowedFinishers->GetAmount())));
                }
            }
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_rog_eviscerate::CalculateDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

/// ID - 382518 Perforated Veins
class spell_perforated_veins_382518 : public AuraScript
{
    PrepareAuraScript(spell_perforated_veins_382518);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == Shadowstrike;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_perforated_veins_382518::CheckProc);
    }
};

/// ID - 341572 Perforated Veins
class spell_perforated_veins_341572 : public AuraScript
{
    PrepareAuraScript(spell_perforated_veins_341572);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && (eventInfo.GetSpellInfo()->Id == Shadowstrike || eventInfo.GetSpellInfo()->Id == Backstab);
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        Remove();
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_perforated_veins_341572::CheckProc);
        OnProc += AuraProcFn(spell_perforated_veins_341572::HandleProc);
    }
};

/// ID - 319949 Improved Backstab
class spell_improved_backstab_319949 : public AuraScript
{
    PrepareAuraScript(spell_improved_backstab_319949);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && (eventInfo.GetSpellInfo()->Id == Shadowstrike || eventInfo.GetSpellInfo()->Id == Backstab)
            && eventInfo.GetProcTarget() && GetCaster()
            && !eventInfo.GetProcTarget()->isInFront(GetCaster());
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto caster = GetCaster())
            if (auto procTarget = eventInfo.GetProcTarget())
                caster->CastSpell(procTarget, FindWeaknesDebuff, true);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_improved_backstab_319949::CheckProc);
        OnProc += AuraProcFn(spell_improved_backstab_319949::HandleProc);
    }
};

/// ID - 343173 Premeditation
class spell_premeditation_343173 : public AuraScript
{
    PrepareAuraScript(spell_premeditation_343173);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == Shadowstrike;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto caster = GetCaster())
        {
            auto aura = caster->GetAura(SliceAndDice);
            uint32 oldSndDuration = [&]() -> uint32
            {
                if (aura)
                    return aura->GetDuration();

                return 0;
            }();

            auto newDurataion = caster->CalcSpellDuration(sSpellMgr->GetSpellInfo(SliceAndDice), true, nullptr, oldSndDuration, false);

            if (aura)
                aura->SetDuration(newDurataion);
            else if (auto newAura = caster->AddAura(SliceAndDice, caster))
                newAura->SetDuration(newDurataion);

            caster->CastSpell(caster, PremeditationEnergize, true);
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_premeditation_343173::CheckProc);
        OnProc += AuraProcFn(spell_premeditation_343173::HandleProc);
    }
};

/// ID - 385727 Silent Storm
class spell_silent_storm_385727 : public AuraScript
{
    PrepareAuraScript(spell_silent_storm_385727);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == ShurikenStorm;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        Remove();
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_silent_storm_385727::CheckProc);
        OnProc += AuraProcFn(spell_silent_storm_385727::HandleProc);
    }
};

void AddSC_spell_rogue_subtlety()
{
    RegisterSpellScript(spell_deeper_daggers);
    RegisterSpellScript(spell_black_powder);
    RegisterSpellScript(spell_finality);
    RegisterSpellScript(spell_finality_eviscerate);
    RegisterSpellScript(spell_finality_black_powder);
    RegisterSpellScript(spell_the_rotten);
    RegisterSpellScript(spell_the_rotten_proc);
    RegisterSpellScript(spell_rog_eviscerate);
    RegisterSpellScript(spell_perforated_veins_382518);
    RegisterSpellScript(spell_perforated_veins_341572);
    RegisterSpellScript(spell_improved_backstab_319949);
    RegisterSpellScript(spell_premeditation_343173);
    RegisterSpellScript(spell_silent_storm_385727);
}
