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
            if (auto rip = enemy->GetAura(DruidSpells::Rip, caster->GetGUID()))
            {
                if (rip->GetDuration() < ripBaseDuration)
                    rip->SetDuration(std::min(4000, rip->GetDuration()) + ripBaseDuration);
                continue;
            }

            if (auto rip = caster->AddAura(DruidSpells::Rip, enemy))
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
        if (!eventInfo.GetSpellInfo())
            return false;

        return IsFinisher(eventInfo.GetSpellInfo()->Id);
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();

        if (!eventInfo.GetSpellInfo())
            return;

        auto caster = GetCaster();
        if (!caster)
            return;

        if (!UniqueFinishers.count(eventInfo.GetSpellInfo()->Id))
            UniqueFinishers.insert(eventInfo.GetSpellInfo()->Id);

        switch (eventInfo.GetSpellInfo()->Id)
        {
            case Rip:
            case FerociousBite:
                /// Updated 9.2.5.44061
                /// Proc script isn't working, drop it here. Dmg shd be handled by ApplySpellMod
                if (auto bloodTalons = caster->GetAura(BloodTalonsProc))
                    bloodTalons->DropCharge();
                break;
            default:
                break;
        }

        if (UniqueFinishers.size() >= 3)
        {
            UniqueFinishers.clear();
            if (auto caster = GetCaster())
                caster->CastSpell(caster, BloodTalonsProc, true);
        }
    }

    std::unordered_set<uint32> UniqueFinishers;

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
        if (auto aur = GetAura())
            aur->DropStack();
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_bloodtalons_proc::CheckProc);
        OnProc += AuraProcFn(spell_bloodtalons_proc::HandleProc);
    }
};

void AddSC_spell_druid_feral()
{
    RegisterSpellScript(spell_primal_wrath);
    RegisterSpellScript(spell_bloodtalons);
    RegisterSpellScript(spell_bloodtalons_proc);
}
