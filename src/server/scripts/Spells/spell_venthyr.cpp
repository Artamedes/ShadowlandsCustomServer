#include "SpellMgr.h"
#include "Unit.h"
#include "SpellScript.h"

// 300728
class spell_door_of_shadows : public SpellScript
{
    PrepareSpellScript(spell_door_of_shadows);

    enum DoorOfShadows
    {
        FancyFootworksAura = 331577,
        AgentOfChaos = 331576,
        AgentOfChaosTrigger = 331866,
    };

    void HandleScript(SpellEffIndex /*eff*/)
    {
        if (GetCaster() && GetCaster()->HasAura(AgentOfChaos))
        {
            // TODO: add a way to callback on teleport
            GetCaster()->GetScheduler().Schedule(50ms, [this](TaskContext context)
            {
                GetCaster()->CastSpell(GetCaster(), AgentOfChaosTrigger, true);
            });
        }
    }

    void HandleDisorient(SpellEffIndex effIndex)
    {
        PreventHitDefaultEffect(effIndex);
    }

    void HandleTrigger(SpellEffIndex effIndex)
    {
        if (!GetCaster() || !GetCaster()->HasAura(FancyFootworksAura))
            PreventHitDefaultEffect(effIndex);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_door_of_shadows::HandleScript, EFFECT_0, SPELL_EFFECT_TELEPORT_UNITS);
        OnEffectLaunch += SpellEffectFn(spell_door_of_shadows::HandleDisorient, EFFECT_1, SPELL_EFFECT_TRIGGER_SPELL);
        OnEffectLaunch += SpellEffectFn(spell_door_of_shadows::HandleTrigger, EFFECT_2, SPELL_EFFECT_TRIGGER_SPELL);
    }
};

void AddSC_spell_venthyr()
{
    RegisterSpellScript(spell_door_of_shadows);
}
