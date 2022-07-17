#include "spell_paladin.h"

using namespace Paladin;

/// ID: 337297 Relentless Inquisitor
class spell_relentless_inquisitor : public AuraScript
{
    PrepareAuraScript(spell_relentless_inquisitor);

    enum eRelentlessInquisitor
    {
        RelentlessInquisitor = 337315,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetProcSpell() && eventInfo.GetProcSpell()->GetPowerCost(Powers::POWER_HOLY_POWER);
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto caster = GetCaster())
            caster->CastSpell(caster, RelentlessInquisitor, true);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_relentless_inquisitor::CheckProc);
        OnProc += AuraProcFn(spell_relentless_inquisitor::HandleProc);
    }
};
/// ID: 337831 Holy Avenger's Engraved Sigil
class spell_holy_avengers_engraved_sigil : public AuraScript
{
    PrepareAuraScript(spell_holy_avengers_engraved_sigil);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == AvengersShield;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto caster = GetCaster())
            caster->GetSpellHistory()->ResetCooldown(AvengersShield, true);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_holy_avengers_engraved_sigil::CheckProc);
        OnProc += AuraProcFn(spell_holy_avengers_engraved_sigil::HandleProc);
    }
};

// 114565 - npc_guardian_of_the_forgotten_queen_114565
struct npc_guardian_of_the_forgotten_queen_114565 : public ScriptedAI
{
public:
    npc_guardian_of_the_forgotten_queen_114565(Creature* creature) : ScriptedAI(creature) { me->DespawnOrUnsummon(4s); me->SetControlled(true, UnitState::UNIT_STATE_ROOT); SetCombatMovement(false); }

    void Reset() override
    {
        me->SetReactState(REACT_PASSIVE);
        me->GetScheduler().Schedule(10ms, [this](TaskContext context)
        {
            me->SetFlying(true);

            Position l_Pos = me->GetPosition();
            l_Pos.m_positionZ += 5.0f;

            me->GetMotionMaster()->Clear();
            me->GetMotionMaster()->MoveTakeoff(0, l_Pos);
        });
    }

    void UpdateAI(uint32 diff) override
    {
        if (auto owner = me->GetOwner())
        {
            if (!me->GetCurrentSpell(CurrentSpellTypes::CURRENT_CHANNELED_SPELL))
                me->CastSpell(owner, 86657, true);
        }
    }
};

/// ID: 340459 Maraad's Dying Breath
class spell_maraads_dying_breath_proc : public AuraScript
{
    PrepareAuraScript(spell_maraads_dying_breath_proc);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == LightOfTheMartyr;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        ModStackAmount(-1);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_maraads_dying_breath_proc::CheckProc);
        OnProc += AuraProcFn(spell_maraads_dying_breath_proc::HandleProc);
    }
};

/// ID: 337825 Shock Barrier
class spell_shock_barrier : public AuraScript
{
    PrepareAuraScript(spell_shock_barrier);

    enum eShockBarrier
    {
        ShockBarrierShield = 337824,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == HolyShockHeal;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto healInfo = eventInfo.GetHealInfo())
            if (auto caster = GetCaster())
                if (auto target = eventInfo.GetProcTarget())
                    caster->CastSpell(target, ShockBarrierShield, CastSpellExtraArgs(true).AddSpellBP0(CalculatePct(healInfo->GetHeal(), 20)).AddSpellBP1(CalculatePct(healInfo->GetHeal(), 20)));
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_shock_barrier::CheckProc);
        OnProc += AuraProcFn(spell_shock_barrier::HandleProc);
    }
};

/// ID: 337824 Shock Barrier
class spell_shock_barrier_periodic : public AuraScript
{
    PrepareAuraScript(spell_shock_barrier_periodic);

    void HandlePeriodic(AuraEffect const* aurEff)
    {
        if (auto eff = GetEffect(EFFECT_1))
        {
            eff->ChangeAmount(aurEff->GetAmount());
        }
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_shock_barrier_periodic::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

void AddSC_spell_paladin_legendary()
{
    RegisterSpellScript(spell_relentless_inquisitor);
    RegisterSpellScript(spell_holy_avengers_engraved_sigil);
    RegisterCreatureAI(npc_guardian_of_the_forgotten_queen_114565);
    RegisterSpellScript(spell_maraads_dying_breath_proc);
    RegisterSpellScript(spell_shock_barrier);
    RegisterSpellScript(spell_shock_barrier_periodic);
}
