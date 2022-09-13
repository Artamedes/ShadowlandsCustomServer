#include "SpellIncludes.h"

/// ID - 372608 Surge Forward (Dragonriding)
class spell_dragonriding_surge_forward : public SpellScript
{
    PrepareSpellScript(spell_dragonriding_surge_forward);

    void HandleDummy(SpellEffIndex /*eff*/)
    {
        if (auto player = GetCaster()->ToPlayer())
        {
            WorldPacket data(SMSG_MOVE_UNK_2E32, 16 + 4 + 4 + 4 + 4);
            data << uint32(player->m_movementCounter++);
            data << float(-16.5240516662597656f);
            data << float(6.688496589660644531f);
            data << float(-2.49394869804382324f);
            player->SendDirectMessage(&data);
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_dragonriding_surge_forward::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};


void AddSC_spell_dragonriding()
{
    RegisterSpellScript(spell_dragonriding_surge_forward);
}
