#include "SpellIncludes.h"

/// ID - 372608 Surge Forward (Dragonriding)
class spell_dragonriding_surge_forward : public SpellScript
{
    PrepareSpellScript(spell_dragonriding_surge_forward);

    void HandleDummy(SpellEffIndex /*eff*/)
    {
        if (auto player = GetCaster()->ToPlayer())
        {
            WorldPacket data(SMSG_MOVE_UPDATE_APPLY_IMPULSE, 16 + 4 + 4 + 4 + 4);
            data << player->GetGUID();
            data << uint32(player->m_movementCounter++);
            float vcos = std::cos(player->GetOrientation());
            float vsin = std::sin(player->GetOrientation());
            float motionZ = player->m_movementInfo.pitch * 15.0f;
            data << float(15.0f * vcos);
            data << float(15.0f * vsin);
            data << float(motionZ); // some kind of calculation involving pitch, current speed
            player->SendDirectMessage(&data);
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_dragonriding_surge_forward::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};


/// ID - 372610 Skyward Ascent (Dragonriding)
class spell_dragonriding_skyward_ascent : public SpellScript
{
    PrepareSpellScript(spell_dragonriding_skyward_ascent);

    void HandleDummy(SpellEffIndex /*eff*/)
    {
        if (auto player = GetCaster()->ToPlayer())
        {
            WorldPacket data(SMSG_MOVE_UPDATE_APPLY_IMPULSE, 16 + 4 + 4 + 4 + 4);
            data << player->GetGUID();
            data << uint32(player->m_movementCounter++);
            float vcos = std::cos(player->GetOrientation());
            float vsin = std::sin(player->GetOrientation());
            data << float(5.0f * vcos);
            data << float(5.0f * vsin);
            data << float(49);
            player->SendDirectMessage(&data);
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_dragonriding_skyward_ascent::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

void AddSC_spell_dragonriding()
{
    RegisterSpellScript(spell_dragonriding_surge_forward);
    RegisterSpellScript(spell_dragonriding_skyward_ascent);
}
