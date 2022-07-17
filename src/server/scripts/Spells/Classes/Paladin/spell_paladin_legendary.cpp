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

void AddSC_spell_paladin_legendary()
{
    RegisterSpellScript(spell_relentless_inquisitor);
    RegisterSpellScript(spell_holy_avengers_engraved_sigil);
    RegisterCreatureAI(npc_guardian_of_the_forgotten_queen_114565);
}
