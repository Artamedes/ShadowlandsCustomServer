#include "spell_druid.h"

using namespace Druid;

/// ID: 338661 Oneth's Clear Vision
class spell_oneths_clear_vision : public AuraScript
{
    PrepareAuraScript(spell_oneths_clear_vision);

    enum eOneths
    {
        OnethStarsurgeProc = 339797,
        OnethPerception,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && (eventInfo.GetSpellInfo()->Id == Starfall || eventInfo.GetSpellInfo()->Id == Starsurge);
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetSpellInfo())
        {
            if (eventInfo.GetSpellInfo()->Id == Starfall)
            {
                if (roll_chance_i(40))
                    if (auto caster = GetCaster())
                        caster->CastSpell(caster, OnethStarsurgeProc, true);
            }
            else if (eventInfo.GetSpellInfo()->Id == Starsurge)
            {
                if (roll_chance_i(20))
                    if (auto caster = GetCaster())
                        caster->CastSpell(caster, OnethPerception, true);
            }
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_oneths_clear_vision::CheckProc);
        OnProc += AuraProcFn(spell_oneths_clear_vision::HandleProc);
    }
};

/// ID: 339800 Oneth's Perception
class spell_oneths_perception : public AuraScript
{
    PrepareAuraScript(spell_oneths_perception);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == Starfall;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        Remove();
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_oneths_perception::CheckProc);
        OnProc += AuraProcFn(spell_oneths_perception::HandleProc);
    }
};

/// ID: 339797 Oneth's Clear Vision
class spell_oneths_clear_vision_proc : public AuraScript
{
    PrepareAuraScript(spell_oneths_clear_vision_proc);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == Starsurge;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        Remove();
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_oneths_clear_vision_proc::CheckProc);
        OnProc += AuraProcFn(spell_oneths_clear_vision_proc::HandleProc);
    }
};

/// ID: 338668 Primordial Arcanic Pulsar
class spell_primordial_arcanic_pulsar : public AuraScript
{
    PrepareAuraScript(spell_primordial_arcanic_pulsar);

    enum ePrimordialArcanicPulsar
    {
        PrimordialArcanicPulsarBuff = 338825,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetProcSpell() && eventInfo.GetProcSpell()->GetPowerCost(Powers::POWER_LUNAR_POWER);
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto caster = GetCaster())
        {
            if (auto power = eventInfo.GetProcSpell()->GetPowerCost(Powers::POWER_LUNAR_POWER))
            {
                if (auto buff = caster->GetAura(PrimordialArcanicPulsarBuff))
                {
                    buff->GetEffect(EFFECT_0)->ChangeAmount(buff->GetEffect(EFFECT_0)->GetAmount() + power->Amount / 10);
                    if (buff->GetEffect(EFFECT_0)->GetAmount() >= 300)
                    {
                        buff->GetEffect(EFFECT_0)->ChangeAmount(buff->GetEffect(EFFECT_0)->GetAmount() + -300);

                        uint32 currDuration = 0;

                        if (auto celes = caster->GetAura(CelestialAlignment))
                            currDuration += celes->GetDuration();

                        caster->CastSpell(caster, CelestialAlignment, CastSpellExtraArgs(TRIGGERED_FULL_MASK_NO_CD).AddSpellMod(SpellValueMod::SPELLVALUE_DURATION, 12000 + currDuration));
                    }
                }
                else
                    caster->CastSpell(caster, PrimordialArcanicPulsarBuff, CastSpellExtraArgs(true).AddSpellBP0(power->Amount / 10));
            }
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_primordial_arcanic_pulsar::CheckProc);
        OnProc += AuraProcFn(spell_primordial_arcanic_pulsar::HandleProc);
    }
};

/// ID: 339949 Timeworn Dreambinder
class spell_timeworn_dreambinder : public AuraScript
{
    PrepareAuraScript(spell_timeworn_dreambinder);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && (eventInfo.GetSpellInfo()->Id == Starfall || eventInfo.GetSpellInfo()->Id == Starsurge);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_timeworn_dreambinder::CheckProc);
    }
};

/// ID: 339139 Apex Predator's Craving
class spell_apex_predators_craving : public AuraScript
{
    PrepareAuraScript(spell_apex_predators_craving);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == Rip;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_apex_predators_craving::CheckProc);
    }
};

/// ID: 339140 Apex Predator's Craving
class spell_apex_predators_craving_proc : public AuraScript
{
    PrepareAuraScript(spell_apex_predators_craving_proc);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == FerociousBite;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        Remove();
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_apex_predators_craving_proc::CheckProc);
        OnProc += AuraProcFn(spell_apex_predators_craving_proc::HandleProc);
    }
};

/// ID: 339144 Cat-Eye Curio
class spell_cat_eye_curio : public AuraScript
{
    PrepareAuraScript(spell_cat_eye_curio);

    enum eCatEyeCurio
    {
        CatEyeCurioEnergize = 339145,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && IsAffectedByClearcasting(eventInfo.GetSpellInfo()->Id);
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto caster = GetCaster())
        {
            if (auto spell = eventInfo.GetProcSpell())
            {
                if (auto energyCost = spell->GetPowerCost(Powers::POWER_ENERGY))
                {
                    caster->CastSpell(caster, CatEyeCurioEnergize, CastSpellExtraArgs(true).AddSpellBP0(CalculatePct(energyCost->Amount, 25)));
                }
            }
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_cat_eye_curio::CheckProc);
        OnProc += AuraProcFn(spell_cat_eye_curio::HandleProc);
    }
};
/// ID: 339141 Eye of Fearful Symmetry
class spell_eye_of_fearful_symmetry : public AuraScript
{
    PrepareAuraScript(spell_eye_of_fearful_symmetry);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == TigersFury;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_eye_of_fearful_symmetry::CheckProc);
    }
};
/// ID: 339142 Eye of Fearful Symmetry
class spell_eye_of_fearful_symmetry_proc : public AuraScript
{
    PrepareAuraScript(spell_eye_of_fearful_symmetry_proc);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetProcSpell() && eventInfo.GetProcSpell()->GetPowerCost(Powers::POWER_COMBO_POINTS);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_eye_of_fearful_symmetry_proc::CheckProc);
    }
};

/// ID: 340053 Frenzyband
class spell_frenzyband : public AuraScript
{
    PrepareAuraScript(spell_frenzyband);

    enum eFrenzyBand
    {
        FrenziedAssault = 340056,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetProcSpell() && eventInfo.GetProcSpell()->m_comboPointsEnergized;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto caster = GetCaster())
        {
            caster->GetSpellHistory()->ModifyCooldown(IncarninationKindOfTheJungle, -200);
            caster->GetSpellHistory()->ModifyCooldown(Berserk, -200);

            if (auto dmgInfo = eventInfo.GetDamageInfo())
            {
                if (auto target = eventInfo.GetProcTarget())
                {
                    caster->CastSpell(target, FrenziedAssault, CastSpellExtraArgs(true).AddSpellBP0(dmgInfo->GetDamage()));
                }
            }
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_frenzyband::CheckProc);
        OnProc += AuraProcFn(spell_frenzyband::HandleProc);
    }
};

/// ID: 339056 Ursoc's Fury Remembered
class spell_ursocs_fury_remembered : public AuraScript
{
    PrepareAuraScript(spell_ursocs_fury_remembered);

    enum eUrsocsFury
    {
        UrsocFuryShield = 345048,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == ThrashBear;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto caster = GetCaster())
        {
            if (auto dmgInfo = eventInfo.GetDamageInfo())
            {
                caster->CastSpell(caster, UrsocFuryShield, CastSpellExtraArgs(true).AddSpellBP0(CalculatePct(dmgInfo->GetDamage(), 75)));
                if (dmgInfo->GetDamageType() != DOT)
                {
                    if (roll_chance_i(15))
                        caster->CastSpell(caster, ThrashBear, CastSpellExtraArgs(TRIGGERED_FULL_MASK_NO_CD));
                }
            }
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_ursocs_fury_remembered::CheckProc);
        OnProc += AuraProcFn(spell_ursocs_fury_remembered::HandleProc);
    }
};

/// ID: 338829 Verdant Infusion
class spell_verdant_infusion : public AuraScript
{
    PrepareAuraScript(spell_verdant_infusion);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == Swiftmend;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto caster = GetCaster())
        {
            if (auto target = eventInfo.GetProcTarget())
            {
                if (auto aur = target->GetAura(Druid::eDruid::Regrowth, caster->GetGUID()))
                    aur->ModDuration(10000);
                if (auto aur = target->GetAura(Druid::eRestoration::WildGrowth, caster->GetGUID()))
                    aur->ModDuration(10000);
                if (auto aur = target->GetAura(Druid::eRestoration::Rejuvenation, caster->GetGUID()))
                    aur->ModDuration(10000);
            }
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_verdant_infusion::CheckProc);
        OnProc += AuraProcFn(spell_verdant_infusion::HandleProc);
    }
};

/// ID: 338832 Vision of Unending Growth
class spell_vision_of_unending_growth : public AuraScript
{
    PrepareAuraScript(spell_vision_of_unending_growth);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == Rejuvenation;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto caster = GetCaster())
        {
            if (auto target = eventInfo.GetProcTarget())
            {
                std::list<Unit*> randUnits;
                target->GetFriendlyUnitListInRange(randUnits, 40.0f, true);
                randUnits.remove_if([caster](Unit* who) -> bool
                {
                    return who->HasAura(Rejuvenation, caster->GetGUID());
                });

                if (!randUnits.empty())
                {
                    caster->CastSpell(Trinity::Containers::SelectRandomContainerElement(randUnits), Rejuvenation, true);
                }
            }
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_vision_of_unending_growth::CheckProc);
        OnProc += AuraProcFn(spell_vision_of_unending_growth::HandleProc);
    }
};
/// ID: 339064 Memory of the Mother Tree
class spell_memory_of_the_mother_tree : public AuraScript
{
    PrepareAuraScript(spell_memory_of_the_mother_tree);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == WildGrowth;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_memory_of_the_mother_tree::CheckProc);
    }
};

/// ID: 189877 Memory of the Mother Tree
class spell_memory_of_the_mother_tree_proc : public AuraScript
{
    PrepareAuraScript(spell_memory_of_the_mother_tree_proc);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && (eventInfo.GetSpellInfo()->Id == Rejuvenation || eventInfo.GetSpellInfo()->Id == Regrowth);
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetSpellInfo())
            return;

        if (auto caster = GetCaster())
        {
            if (auto target = eventInfo.GetActionTarget())
            {
                std::list<Unit*> randUnits;
                target->GetFriendlyUnitListInRange(randUnits, 40.0f, true);

                if (!randUnits.empty())
                {
                    Trinity::Containers::RandomResize(randUnits, 3);

                    for (auto unit : randUnits)
                        caster->CastSpell(unit, eventInfo.GetSpellInfo()->Id, true);
                }
            }
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_memory_of_the_mother_tree_proc::CheckProc);
        OnProc += AuraProcFn(spell_memory_of_the_mother_tree_proc::HandleProc);
    }
};
/// ID: 340059 Lycara's Fleeting Glimpse
class spell_lycaras_fleeting_glimpse : public AuraScript
{
    PrepareAuraScript(spell_lycaras_fleeting_glimpse);

    void HandleProc(ProcEventInfo& eventInfo)
    {
        _nextAllowedTime = GameTime::Now();
    }

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
        auto caster = GetCaster();
        if (!caster)
            return;

        if (caster->IsInCombat())
        {
            auto now = GameTime::Now();
            if (now >= _nextAllowedTime)
            {
                _nextAllowedTime = now + 45s;

                switch (caster->GetShapeshiftForm())
                {
                    default:
                    case ShapeshiftForm::FORM_NONE:
                        caster->CastSpell(caster, WildGrowth, CastSpellExtraArgs(TRIGGERED_FULL_MASK_NO_CD));
                        break;
                    case ShapeshiftForm::FORM_CAT_FORM:
                    {
                        auto prevComboPoints = caster->GetComboPoints();
                        caster->SetPower(Powers::POWER_COMBO_POINTS, 5, false);
                        caster->CastSpell(caster, PrimalWrath, CastSpellExtraArgs(TRIGGERED_FULL_MASK_NO_CD));
                        caster->SetPower(Powers::POWER_COMBO_POINTS, prevComboPoints, false);
                        break;
                    }
                    case ShapeshiftForm::FORM_BEAR_FORM:
                        caster->CastSpell(caster, Barskin, CastSpellExtraArgs(TRIGGERED_FULL_MASK_NO_CD));
                        break;
                    case ShapeshiftForm::FORM_MOONKIN_FORM:
                        caster->CastSpell(caster, Starfall, CastSpellExtraArgs(TRIGGERED_FULL_MASK_NO_CD));
                        break;
                    case ShapeshiftForm::FORM_TRAVEL_FORM:
                        caster->CastSpell(caster, StampedingRoar, CastSpellExtraArgs(TRIGGERED_FULL_MASK_NO_CD));
                        break;
                }
            }
        }
    }

    TimePoint _nextAllowedTime;

    void Register() override
    {
        _nextAllowedTime = GameTime::Now();
        OnProc += AuraProcFn(spell_lycaras_fleeting_glimpse::HandleProc);
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_lycaras_fleeting_glimpse::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

void AddSC_spell_druid_legendary()
{
    RegisterSpellScript(spell_oneths_clear_vision);
    RegisterSpellScript(spell_oneths_perception);
    RegisterSpellScript(spell_oneths_clear_vision_proc);
    RegisterSpellScript(spell_primordial_arcanic_pulsar);
    RegisterSpellScript(spell_timeworn_dreambinder);
    RegisterSpellScript(spell_apex_predators_craving);
    RegisterSpellScript(spell_apex_predators_craving_proc);
    RegisterSpellScript(spell_cat_eye_curio);
    RegisterSpellScript(spell_eye_of_fearful_symmetry);
    RegisterSpellScript(spell_eye_of_fearful_symmetry_proc);
    RegisterSpellScript(spell_frenzyband);
    RegisterSpellScript(spell_ursocs_fury_remembered);
    RegisterSpellScript(spell_verdant_infusion);
    RegisterSpellScript(spell_vision_of_unending_growth);
    RegisterSpellScript(spell_memory_of_the_mother_tree);
    RegisterSpellScript(spell_memory_of_the_mother_tree_proc);
    RegisterSpellScript(spell_lycaras_fleeting_glimpse);
}
