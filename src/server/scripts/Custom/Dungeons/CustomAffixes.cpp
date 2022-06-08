#include "ScriptedCreature.h"
#include "../CustomInstanceScript.h"
#include "ScriptMgr.h"
#include "SpellScript.h"
#include "SpellAuras.h"
#include "SpellAuraEffects.h"

struct npc_beguiling_emissary_ai : public ScriptedAI
{
public:
    npc_beguiling_emissary_ai(Creature* creature) : ScriptedAI(creature) { }

    bool IsPhased = false;
    void DamageTaken(Unit* /*attacker*/, uint32& damage, DamageEffectType /*damageType*/, SpellInfo const* /*spellInfo = nullptr*/) override
    {
        if (damage >= me->GetHealth())
        {
            damage = 0;
            me->SetHealth(1);
            if (!IsPhased)
            {
                IsPhased = true;
                me->CastStop();
                me->SetUnitFlag(UnitFlags::UNIT_FLAG_IMMUNE_TO_PC);
                DoCastSelf(TeleportTheEternalPalace);
            }
        }
    }

    void EnterEvadeMode(EvadeReason why) override
    {
        if (!IsPhased)
            ScriptedAI::EnterEvadeMode(why);
    }
};

// 155432 - npc_enchanted_emissary_155432
struct npc_enchanted_emissary_155432 : public npc_beguiling_emissary_ai
{
public:
    npc_enchanted_emissary_155432(Creature* creature) : npc_beguiling_emissary_ai(creature) { me->SetRegenerateHealth(false); }

    void DoAction(int32 actionId) override
    {
        if (actionId == ActionSetActive)
        {
            DoCastSelf(SpellQueenDecreesBlowback);
            DoCastSelf(SpellEnchanted);
            DoCastSelf(295711); // Purple Visual
        }
    }

    void Reset() override
    {
        DoCastSelf(SpellQueenDecreesBlowback);
        DoCastSelf(SpellEnchanted);
        DoCastSelf(295711); // Purple Visual
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        DoMeleeAttackIfReady();
    }
};
// 155433 - npc_void_touched_emissary_155433
struct npc_void_touched_emissary_155433 : public npc_beguiling_emissary_ai
{
public:
    npc_void_touched_emissary_155433(Creature* creature) : npc_beguiling_emissary_ai(creature)
    {
        ApplyAllImmunities(true);
        SetCombatMovement(false);
        me->SetRegenerateHealth(false);
        DoCastSelf(177303); // Void Touched
    }

    void Reset() override
    {
        DoCastSelf(177303); // Void Touched
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        DoCast(SpellQueenDecreeHide);
    }
};

// 155434 - npc_emissary_of_the_tides_155434
struct npc_emissary_of_the_tides_155434 : public npc_beguiling_emissary_ai
{
public:
    npc_emissary_of_the_tides_155434(Creature* creature) : npc_beguiling_emissary_ai(creature) { me->SetRegenerateHealth(false); }

    void DoAction(int32 actionId) override
    {
        if (actionId == ActionSetActive)
        {
            DoCastSelf(SpellQueenDecreeUnstoppable);
            DoCastSelf(295709); // Water visual
        }
    }

    void Reset() override
    {
        DoCastSelf(295709); // Water visual
    }

    void UpdateAI(uint32 diff) override
    {
        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        if (!me->HasAura(SpellQueenDecreeUnstoppable))
            DoCastSelf(SpellQueenDecreeUnstoppable);

        if (!UpdateVictim())
            return;

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        DoMeleeAttackIfReady();
    }
};

/// ID - 302415 Teleport: The Eternal Palace
class spell_teleport_the_eternal_palace_302415 : public SpellScript
{
    PrepareSpellScript(spell_teleport_the_eternal_palace_302415);

    void HandleDummy(SpellEffIndex /*eff*/)
    {
        if (auto creature = GetCaster()->ToCreature())
        {
            creature->DespawnOrUnsummon();
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_teleport_the_eternal_palace_302415::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};
// 173729 - npc_manifestation_of_pride_173729
struct npc_manifestation_of_pride_173729 : public ScriptedAI
{
public:
    npc_manifestation_of_pride_173729(Creature* creature) : ScriptedAI(creature)
    {
        ApplyAllImmunities(true);
        me->SetRegenerateHealth(false);
    }

    enum ManifiestationOfPrideful
    {
        PrideAura = 340382,
        PrideVisual = 340383,
        BurstingWithPride = 340873,
        BelligerentBoastAura = 342466,
        PridefulBuff = 340880,
    };

    uint32 PrideTimer = 0;
    uint32 BoastTimer = 0;

    void InitializeAI() override
    {
        DoCastSelf(PrideAura);
        me->SetReactState(REACT_PASSIVE);
        me->SetUnitFlag(UnitFlags::UNIT_FLAG_IMMUNE_TO_PC);

        if (auto map = me->GetMap())
        {
            map->DoOnPlayers([this](Player* player)
            {
                me->CastSpell(player, PrideVisual, true);
            });
        }

        scheduler.Schedule(3s, [this](TaskContext context)
        {
            me->RemoveAurasDueToSpell(PrideAura);
            scheduler.Schedule(1s, [this](TaskContext context)
            {
                me->RemoveAurasDueToSpell(PrideVisual);
                me->RemoveAura(PrideVisual);

                if (auto map = me->GetMap())
                {
                    map->DoOnPlayers([this](Player* player)
                    {
                        me->RemoveAurasDueToSpell(PrideVisual);
                        me->RemoveAura(PrideVisual);
                    });
                }

                me->RemoveUnitFlag(UnitFlags::UNIT_FLAG_IMMUNE_TO_PC);
                me->SetReactState(REACT_AGGRESSIVE);
                DoCastSelf(BurstingWithPride);
                DoZoneInCombat();
            });
        });
    }

    void JustEngagedWith(Unit* who) override
    {
        DoCastSelf(BurstingWithPride);
    }

    void JustDied(Unit* who) override
    {
        if (auto map = me->GetMap())
        {
            map->DoOnPlayers([this](Player* player)
            {
                me->CastSpell(player, PridefulBuff, true);
            });
            me->DespawnOrUnsummon(5s);
        }
    }

    void UpdateAI(uint32 diff) override
    {
        scheduler.Update(diff);

        if (!UpdateVictim())
            return;

        PrideTimer += diff;
        if (PrideTimer >= 2000)
        {
            PrideTimer = 0;
            DoCastSelf(BurstingWithPride);
        }

        BoastTimer += diff;
        if (BoastTimer >= 7000)
        {
            BoastTimer = 0;
            if (auto randTarget = SelectTarget(SelectTargetMethod::Random, 0, 40.0f, true, true))
                DoCast(randTarget, BelligerentBoastAura, true);
        }

        DoMeleeAttackIfReady();
    }

    TaskScheduler scheduler;
    EventMap events;
};

/// ID - 342332 Bursting With Pride
class spell_bursting_with_pride_342332 : public SpellScript
{
    PrepareSpellScript(spell_bursting_with_pride_342332);

    enum BurstingWithPride
    {
        BurstingWithPrideAura = 340873,
    };

    void HandleDamage(SpellEffIndex /*eff*/)
    {
        if (auto caster = GetCaster())
            if (auto aura = caster->GetAura(BurstingWithPrideAura))
            {
                auto challengeLevel = 1u;
                if (auto instance = caster->GetInstanceScript())
                    if (auto challenge = instance->GetChallenge())
                        challengeLevel = challenge->GetChallengeLevel();

                auto dmg = GetHitDamage() * aura->GetStackAmount();

                if (challengeLevel > 1)
                    AddPct(dmg, challengeLevel * 30);

                //aura->GetEffect(EFFECT_0)->SetAmount(dmg);
                SetHitDamage(dmg);
            }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_bursting_with_pride_342332::HandleDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

void AddSC_CustomAffixes()
{
    RegisterCreatureAI(npc_enchanted_emissary_155432);
    RegisterCreatureAI(npc_void_touched_emissary_155433);
    RegisterCreatureAI(npc_emissary_of_the_tides_155434);
    RegisterCreatureAI(npc_manifestation_of_pride_173729);

    RegisterSpellScript(spell_teleport_the_eternal_palace_302415);
    RegisterSpellScript(spell_bursting_with_pride_342332);
}
// UPDATE creature_template set ScriptName = 'npc_enchanted_emissary_155432' WHERE entry = 155432;
// UPDATE creature_template set ScriptName = 'npc_void_touched_emissary_155433' WHERE entry = 155433;
// UPDATE creature_template set ScriptName = 'npc_emissary_of_the_tides_155434' WHERE entry = 155434;
