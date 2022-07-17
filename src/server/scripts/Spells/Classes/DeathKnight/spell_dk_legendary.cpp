#include "spell_dk.h"
#include "ScriptedCreature.h"

using namespace DeathKnight;

/// ID: 335177 Phearomones
class spell_phearomones : public AuraScript
{
    PrepareAuraScript(spell_phearomones);

    enum ePhearomes
    {
        TrembleBeforeMe = 206961,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && (eventInfo.GetSpellInfo()->Id == DeathAndDecayDmg || eventInfo.GetSpellInfo()->Id == DefileDmg);
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto target = eventInfo.GetProcTarget())
            if (auto caster = GetCaster())
                caster->CastSpell(target, TrembleBeforeMe, true);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_phearomones::CheckProc);
        OnProc += AuraProcFn(spell_phearomones::HandleProc);
    }
};

/// ID: 334501 Bryndaor's Might
class spell_bryndaors_might : public AuraScript
{
    PrepareAuraScript(spell_bryndaors_might);

    enum eBryndaorsMight
    {
        EnergizeSpell = 334502,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == DeathStrike;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto procSpell = eventInfo.GetProcSpell())
        {
            if (auto caster = GetCaster())
            {
                if (auto healInfo = eventInfo.GetHealInfo())
                {
                    if (healInfo->GetHeal() >= caster->CountPctFromMaxHealth(10))
                    {
                        if (auto runicPower = procSpell->GetPowerCost(Powers::POWER_RUNIC_POWER))
                        {
                            uint32 totalRunicPoewr = runicPower->Amount + runicPower->OptionalAmount;
                            totalRunicPoewr = CalculatePct(totalRunicPoewr, 15) * 10;
                            caster->CastSpell(caster, EnergizeSpell, CastSpellExtraArgs(true).AddSpellBP0(totalRunicPoewr));
                        }
                    }
                }
            }
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_bryndaors_might::CheckProc);
        OnProc += AuraProcFn(spell_bryndaors_might::HandleProc);
    }
};

/// ID: 334583 Koltira's Favor
class spell_koltiras_favor : public AuraScript
{
    PrepareAuraScript(spell_koltiras_favor);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == Obliterate;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_koltiras_favor::CheckProc);
    }
};
/// ID: 341724 Rage of the Frozen Champion
class spell_rage_of_the_frozen_champion : public AuraScript
{
    PrepareAuraScript(spell_rage_of_the_frozen_champion);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == Obliterate;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto caster = GetCaster())
            caster->CastSpell(caster, Rime, true);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_rage_of_the_frozen_champion::CheckProc);
        OnProc += AuraProcFn(spell_rage_of_the_frozen_champion::HandleProc);
    }
};

/// ID: 334949 Deadliest Coil
class spell_deadliest_coil : public AuraScript
{
    PrepareAuraScript(spell_deadliest_coil);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == DeathCoil;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        auto caster = GetCaster();
        if (!caster)
            return;

        if (auto pet = caster->GetControlledCreature(26125))
        {
            if (auto aur = pet->GetAura(DarkTransformation))
                aur->ModDuration(1000);
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_deadliest_coil::CheckProc);
        OnProc += AuraProcFn(spell_deadliest_coil::HandleProc);
    }
};

/// ID: 334898 Death's Certainty
class spell_deaths_certainty : public AuraScript
{
    PrepareAuraScript(spell_deaths_certainty);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && (eventInfo.GetSpellInfo()->Id == DeathCoil || eventInfo.GetSpellInfo()->Id == DeathStrike);
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto caster = GetCaster())
        {
            caster->GetSpellHistory()->ModifyCooldown(DeathAndDecay, -2000);
            caster->GetSpellHistory()->ModifyCooldown(Defile, -2000);
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_deaths_certainty::CheckProc);
        OnProc += AuraProcFn(spell_deaths_certainty::HandleProc);
    }
};

enum eReanimedShambler
{
    SummonReanimedShamblingHorror = 334837,
    Necroblast = 334851,
};

/// ID: 334836 Reanimated Shambler
class spell_reanimated_shambler : public AuraScript
{
    PrepareAuraScript(spell_reanimated_shambler);

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto caster = GetCaster())
        {
            if (eventInfo.GetProcTarget())
                caster->CastSpell(eventInfo.GetProcTarget(), SummonReanimedShamblingHorror, true);
        }
    }

    void Register() override
    {
        OnProc += AuraProcFn(spell_reanimated_shambler::HandleProc);
    }
};

// 171587 - npc_reanimated_shambling_horror_171587
struct npc_reanimated_shambling_horror_171587 : public ScriptedAI
{
public:
    npc_reanimated_shambling_horror_171587(Creature* creature) : ScriptedAI(creature) { }

    void UpdateAI(const uint32 /*p_Diff*/) override
    {
        Unit* l_Owner = me->GetOwner();
        if (!l_Owner)
            return;

        Unit* l_Victim = l_Owner->GetVictim();
        if (!l_Victim || me->GetDistance(l_Victim) <= 1.f)
        {
            me->CastSpell(me, Necroblast, false);
            me->DespawnOrUnsummon(1ms);
        }
        else if (l_Victim)
        {
            if (!me->IsEngaged())
                AttackStart(l_Victim);
        }
    }
};

void AddSC_spell_dk_legendary()
{
    RegisterSpellScript(spell_phearomones);
    RegisterSpellScript(spell_bryndaors_might);
    RegisterSpellScript(spell_koltiras_favor);
    RegisterSpellScript(spell_rage_of_the_frozen_champion);
    RegisterSpellScript(spell_deadliest_coil);
    RegisterSpellScript(spell_deaths_certainty);
    RegisterSpellScript(spell_reanimated_shambler);
    RegisterCreatureAI(npc_reanimated_shambling_horror_171587);
}
