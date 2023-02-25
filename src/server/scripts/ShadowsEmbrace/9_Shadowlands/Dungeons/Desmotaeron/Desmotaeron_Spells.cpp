#include "Desmotaeron.h"

/// 11987
struct at_rain_of_decay : public AreaTriggerAI
{
public:
    at_rain_of_decay(AreaTrigger* at) : AreaTriggerAI(at) { }

    enum eRainOfDecay
    {
        RainOfDecay = 257065,
    };

    void OnUnitEnter(Unit* who) override
    {
        if (auto caster = at->GetCaster())
            if (caster->IsValidAttackTarget(who))
            {
                if (auto aura = who->AddAura(RainOfDecay, who))
                {
                    aura->Variables.Set("AreaTriggerCaster", at->GetGUID());
                }
            }
    }

    void OnUnitExit(Unit* who) override
    {
        for (auto iter = who->GetOwnedAuras().lower_bound(RainOfDecay); iter != who->GetOwnedAuras().upper_bound(RainOfDecay);)
        {
            Aura* aura = iter->second;
            if (aura->Variables.Exist("AreaTriggerCaster") && aura->Variables.GetValue("AreaTriggerCaster", ObjectGuid::Empty) == at->GetGUID())
            {
                who->RemoveAura(aura);
                iter = who->GetOwnedAuras().lower_bound(RainOfDecay);
            }
            else
                ++iter;
        }
    }
};

/// ID - 11208 Blistering Wave
struct at_blistering_wave : public AreaTriggerAI
{
public:
    at_blistering_wave(AreaTrigger* at) : AreaTriggerAI(at) { }

    enum eBlisteringWave
    {
        WaveDmgAura = 249882,
    };

    void OnUnitEnter(Unit* who) override
    {
        if (auto caster = at->GetCaster())
            if (caster->IsValidAttackTarget(who))
                who->CastSpell(who, WaveDmgAura, true);
    }

    void OnUnitExit(Unit* who) override
    {
        who->RemoveAurasDueToSpell(WaveDmgAura);
    }
};

/// ID: 249879 Blistering Wave
class spell_blistering_wave : public SpellScript
{
    PrepareSpellScript(spell_blistering_wave);

    enum eBlisteringWave
    {
        WaveMissle = 249880,
    };

    void HandleDummy(SpellEffIndex /*eff*/)
    {
        if (auto caster = GetCaster())
        {
            for (int i = 0; i < 5; ++i)
            {
                caster->GetScheduler().Schedule(Milliseconds(i * 300), [i](TaskContext context)
                {
                    auto caster = context.GetUnit();
                    Position pos = caster->GetPosition();
                    float radius = frand(6.0f, 11.0f) * i;
                    //caster->MovePosition(pos, radius, 0.0f);
                    //caster->MovePosition(pos, frand(5.0f, 7.0f) * (float)rand_norm(), ((float)rand_norm() * static_cast<float>(2 * M_PI)) - caster->GetOrientation());
                    caster->CastSpell(pos, WaveMissle, true);
                });
            }
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_blistering_wave::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

void AddSC_Desmotaeron_Spells()
{
    RegisterAreaTriggerAI(at_rain_of_decay);
    RegisterAreaTriggerAI(at_blistering_wave);
    RegisterSpellScript(spell_blistering_wave);
}
