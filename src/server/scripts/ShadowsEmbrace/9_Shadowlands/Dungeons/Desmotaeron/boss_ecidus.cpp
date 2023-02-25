#include "Desmotaeron.h"


// 707004 - npc_ecidus_707004
struct npc_ecidus_707004 : public BossAI
{
public:
    npc_ecidus_707004(Creature* creature) : BossAI(creature, BossEcidus) { ApplyAllImmunities(true); }

    enum eEcidus
    {
        /// Ecidus
        DeathWave = 357871,
        SoulEcho = 297024,
        SpellRitualOfSlaughter = 354240,

    };

    enum Talks
    {
        TalkAggro = 0,
        TalkDied,
        TalkKilled,
        TalkAwayWithYou,
    };

    void JustEngagedWith(Unit* who) override
    {
        _JustEngagedWith(who);
        scheduler.CancelAll();

        Talk(TalkAggro);

        scheduler.Schedule(15s, [this](TaskContext context)
        {
            NextIntruderDetectTime = 0;
            Talk(TalkAwayWithYou);
            DoCast(DeathWave);
            context.Repeat(30s, 40s);
        });

        scheduler.Schedule(1s, [this](TaskContext context)
        {
            DoCast(SoulEcho);
            context.Repeat(15s, 20s);
        });

        scheduler.Schedule(30s, [this](TaskContext context)
        {
            DoCast(ChargedWeapons);
        });
    }

    void JustDied(Unit* /*who*/) override
    {
        _JustDied();
        Talk(TalkDied);
    }

    void DamageDealt(Unit* victim, uint32& damage, DamageEffectType type, SpellInfo const* spellInfo /*= nullptr*/) override
    {
        if (spellInfo && victim)
        {
            switch (spellInfo->Id)
            {
                case DeathWave:
                case 297028: ///< Soul Echo Missle DMG
                    if (type != DamageEffectType::DOT)
                    {
                        damage += 300000;
                        damage += victim->CountPctFromMaxHealth(20);
                    }

                    if (instance)
                        if (auto challenge = instance->GetChallenge())
                            damage += 5 * challenge->GetChallengeLevel();
                    break;
                case 308864: ///< Charged Weapons
                    damage += victim->CountPctFromMaxHealth(30);

                    if (instance)
                        if (auto challenge = instance->GetChallenge())
                            damage += 5 * challenge->GetChallengeLevel();
                    break;
                case 330462:
                    damage = 150000;

                    if (instance)
                        if (auto challenge = instance->GetChallenge())
                            damage += 5 * challenge->GetChallengeLevel();
                    break;
                default:
                    break;
            }
        }
    }

    bool CanCastSpellWhileMoving(SpellInfo const* info) const
    {
        return info->Id == SoulEcho;
    }

    time_t NextKillTime;
    time_t NextIntruderDetectTime;

    void KilledUnit(Unit* who) override
    {
        BossAI::KilledUnit(who);
        if (who->IsPlayer())
        {
            auto now = GameTime::GetGameTime();
            if (now >= NextKillTime)
            {
                NextKillTime = now + 10;
                Talk(TalkKilled);
            }
        }
    }

    void UpdateAI(uint32 diff)
    {
        if (!UpdateVictim())
            return;

        scheduler.Update(diff);
        events.Update(diff);

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        while (uint32 eventId = events.ExecuteEvent())
        {
            ExecuteEvent(eventId);
            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;
        }

        DoMeleeAttackIfReady();
    }


    void EnterEvadeMode(EvadeReason why) override
    {
        BossAI::EnterEvadeMode(why);
        _DespawnAtEvade(3s);
    }

    void DamageTaken(Unit* attacker, uint32& damage, DamageEffectType /*damageType*/, SpellInfo const* /*spellInfo = nullptr*/) override
    {
        if (!phased && me->HealthBelowPctDamaged(51, damage))
        {
            phased = true;
            scheduler.DelayAll(5s);
            scheduler.Schedule(1s, [this](TaskContext /*context*/)
            {
                me->CastStop();
                me->CastSpell(me, PowerUp);
            });
        }
    }

    bool phased = false;
};

void AddSC_boss_ecidus()
{
    RegisterCreatureAI(npc_ecidus_707004);
}
