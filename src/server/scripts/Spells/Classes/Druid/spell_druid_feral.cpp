#include "SpellIncludes.h"
#include "spell_druid.h"

using namespace Druid;

/// ID: 285381 Primal Wrath
class spell_primal_wrath : public SpellScript
{
    PrepareSpellScript(spell_primal_wrath);

    void HandleOnTakePower(SpellPowerCost& powerCost)
    {
        if (powerCost.Power == POWER_COMBO_POINTS)
        {
            comboPoints = powerCost.Amount;
        }
    }

    void HandleDmg(SpellEffIndex /*eff*/)
    {
        SetHitDamage(GetHitDamage() * comboPoints);
    }

    void HandleAfterHit()
    {
        auto caster = GetCaster();
        if (!caster)
            return;

        uint32 ripBaseDuration = comboPoints * 2000 + 4000;

        std::list<Unit*> enemies;
        caster->GetAttackableUnitListInRange(enemies, 11.0f);
        for (auto enemy : enemies)
        {
            if (auto rip = enemy->GetAura(Rip, caster->GetGUID()))
            {
                if (rip->GetDuration() < ripBaseDuration)
                    rip->SetDuration(std::min(4000, rip->GetDuration()) + ripBaseDuration);
                continue;
            }

            if (auto rip = caster->AddAura(Rip, enemy))
            {
                rip->SetMaxDuration(ripBaseDuration);
                rip->RefreshDuration();
            }
        }
    }

    int32 comboPoints = 0;

    void Register() override
    {
        OnTakePower += SpellOnTakePowerFn(spell_primal_wrath::HandleOnTakePower);
        OnEffectHitTarget += SpellEffectFn(spell_primal_wrath::HandleDmg, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
        AfterHit += SpellHitFn(spell_primal_wrath::HandleAfterHit);
        // spell has no hit unit so this isnt called.
        //OnEffectHitTarget += SpellEffectFn(spell_primal_wrath::HandleDummy, EFFECT_1, SPELL_EFFECT_DUMMY);
    }
};

/// ID: 319439 Bloodtalons
class spell_bloodtalons : public AuraScript
{
    PrepareAuraScript(spell_bloodtalons);

    enum eBloodTalons
    {
        BloodTalonsProc = 145152,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetProcSpell())
            return false;

        // trash
        if (eventInfo.GetSpellInfo()->Id == 106830)
            return true;

        return eventInfo.GetProcSpell()->m_comboPointsEnergized > 0;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();

        if (!eventInfo.GetSpellInfo())
            return;

        auto caster = GetCaster();
        if (!caster)
            return;

        if (!UniqueBuilders.count(eventInfo.GetSpellInfo()->Id))
            UniqueBuilders.insert(eventInfo.GetSpellInfo()->Id);

        ///switch (eventInfo.GetSpellInfo()->Id)
        ///{
        ///    case Rip:
        ///    case FerociousBite:
        ///        /// Updated 9.2.5.44061
        ///        /// Proc script isn't working, drop it here. Dmg shd be handled by ApplySpellMod
        ///        if (auto bloodTalons = caster->GetAura(BloodTalonsProc))
        ///            bloodTalons->DropCharge();
        ///        break;
        ///    default:
        ///        break;
        ///}

        if (UniqueBuilders.size() >= 3)
        {
            UniqueBuilders.clear();
            if (auto caster = GetCaster())
                caster->CastSpell(caster, BloodTalonsProc, true);
        }
    }

    std::unordered_set<uint32> UniqueBuilders;

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_bloodtalons::CheckProc);
        OnProc += AuraProcFn(spell_bloodtalons::HandleProc);
    }
};

/// ID: 145152 Bloodtalons
class spell_bloodtalons_proc : public AuraScript
{
    PrepareAuraScript(spell_bloodtalons_proc);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetSpellInfo())
            return false;

        switch (eventInfo.GetSpellInfo()->Id)
        {
            case Rip:
            case FerociousBite:
                return true;
        }

        return false;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_bloodtalons_proc::CheckProc);
        OnProc += AuraProcFn(spell_bloodtalons_proc::HandleProc);
    }
};

/// ID: 364416 Heart of the Lion
class spell_heart_of_the_lion : public AuraScript
{
    PrepareAuraScript(spell_heart_of_the_lion);

    enum eHeartOfTheLion
    {
        Berserk               = 106951,
        IncarnKingOfTheJungle = 102543,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetProcSpell())
            return false;

        if (eventInfo.GetProcSpell()->GetUsedComboPoints() > 0)
            return true;

        return false;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto caster = GetCaster())
        {
            if (auto spell = eventInfo.GetProcSpell())
            {
                if (auto comboPoints = spell->GetUsedComboPoints())
                {
                    int32 cdr = 700 * comboPoints;
                    caster->GetSpellHistory()->ModifyCooldown(Berserk, -cdr);
                    caster->GetSpellHistory()->ModifyCooldown(IncarnKingOfTheJungle, -cdr);
                }
            }
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_heart_of_the_lion::CheckProc);
        OnProc += AuraProcFn(spell_heart_of_the_lion::HandleProc);
    }
};

/// ID: 106951 Berserk
class spell_berserk : public AuraScript
{
    PrepareAuraScript(spell_berserk);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetProcSpell())
            return false;

        if (!eventInfo.GetDamageInfo())
            return false;

        if (!eventInfo.GetDamageInfo()->GetDamage())
            return false;

        if (int32 comboPoints = eventInfo.GetProcSpell()->GetUsedComboPoints())
        {
            if (eventInfo.GetProcSpell()->Variables.Exist("BerserkProcced"))
                return false;

            const_cast<Spell*>(eventInfo.GetProcSpell())->Variables.Set("BerserkProcced", true); ///< PIGPIGPIG
            return roll_chance_i(comboPoints * 20);
        }

        return false;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_berserk::CheckProc);
    }
};

/// ID: 340686 Incessant Hunter
class spell_incessant_hunter : public AuraScript
{
    PrepareAuraScript(spell_incessant_hunter);

    enum eIncessantHunter
    {
        Rip = 1079,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetSpellInfo())
            return false;

        return eventInfo.GetSpellInfo()->Id == Rip;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_incessant_hunter::CheckProc);
    }
};

/// ID: 340694 Sudden Ambush
class spell_sudden_ambush : public AuraScript
{
    PrepareAuraScript(spell_sudden_ambush);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetProcSpell())
            return false;

        if (!eventInfo.GetDamageInfo())
            return false;

        if (!eventInfo.GetDamageInfo()->GetDamage())
            return false;

        if (int32 comboPoints = eventInfo.GetProcSpell()->GetUsedComboPoints())
        {
            if (auto eff = GetEffect(EFFECT_0))
                if (eff->ConduitRankEntry)
                    return roll_chance_f((float)comboPoints * eff->ConduitRankEntry->AuraPointsOverride);
        }

        return false;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_sudden_ambush::CheckProc);
    }
};

void AddSC_spell_druid_feral()
{
    RegisterSpellScript(spell_primal_wrath);
    RegisterSpellScript(spell_bloodtalons);
    RegisterSpellScript(spell_bloodtalons_proc);
    RegisterSpellScript(spell_heart_of_the_lion);
    RegisterSpellScript(spell_berserk);
    RegisterSpellScript(spell_incessant_hunter);
    RegisterSpellScript(spell_sudden_ambush);
}
