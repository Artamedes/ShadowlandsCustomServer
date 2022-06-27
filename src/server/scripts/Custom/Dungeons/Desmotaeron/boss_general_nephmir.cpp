#include "Desmotaeron.h"
#include "SpellScript.h"

// 707000 - npc_general_nephmir_707000
struct npc_general_nephmir_707000 : public BossAI
{
public:
    npc_general_nephmir_707000(Creature* creature) : BossAI(creature, BossGeneralNephmir) { ApplyAllImmunities(true); }

    enum Talks
    {
        TalkEngingHostileEntities = 0,   ///< Used
        TalkSecurityMeasuresActivated,   ///< Used
        TalkIntruderDetected,            ///< Used
        TalkArmingWeapons,               ///< Used
        TalkAggressionProtocolInitiated, ///< Used
        TalkDeath,                       ///< Used
        TalkKilled,                      ///< Used
        TalkIdle,                        ///< Used
    };

    void JustEngagedWith(Unit* who) override
    {
        _JustEngagedWith(who);
        scheduler.CancelAll();

        Talk(TalkEngingHostileEntities);

        scheduler.Schedule(15s, [this](TaskContext context)
        {
            NextIntruderDetectTime = 0;
            Talk(TalkSecurityMeasuresActivated);
            DoCast(SoulflameTorrent);
            scheduler.Schedule(3s, [this](TaskContext context)
            {
                Talk(TalkIdle);
            });
            context.Repeat(30s, 40s);
        });

        scheduler.Schedule(4s, [this](TaskContext context)
        {
            DoCast(GiantSlam);
            context.Repeat(15s, 20s);
        });

        scheduler.Schedule(30s, [this](TaskContext context)
        {
            Talk(TalkArmingWeapons);
            DoCast(ChargedWeapons);
        });

        scheduler.Schedule(30s, [this](TaskContext context)
        {
            DoCast(Thunderclap);
            context.Repeat(15s, 20s);
        });
    }

    void JustDied(Unit* /*who*/) override
    {
        _JustDied();
        Talk(TalkDeath);
    }

    void DamageDealt(Unit* victim, uint32& damage, DamageEffectType type, SpellInfo const* spellInfo /*= nullptr*/) override
    {
        if (spellInfo && spellInfo->Id == 357333 && type != DamageEffectType::DOT)
        {
            auto now = GameTime::GetGameTime();
            if (now >= NextIntruderDetectTime)
            {
                NextIntruderDetectTime = now + 60;
                Talk(TalkIntruderDetected);
            }
        }

        if (spellInfo && victim)
        {
            switch (spellInfo->Id)
            {
                case 357333: ///< Soulflame Torrent
                    if (type != DamageEffectType::DOT)
                        damage += victim->CountPctFromMaxHealth(50);
                    else
                        damage += 100000 + victim->CountPctFromMaxHealth(5);

                    if (instance)
                        if (auto challenge = instance->GetChallenge())
                            damage += 5 * challenge->GetChallengeLevel();
                    break;
                case GiantSlam:
                    damage += 500000;
                    damage += victim->CountPctFromMaxHealth(50);

                    if (instance)
                        if (auto challenge = instance->GetChallenge())
                            damage += 5 * challenge->GetChallengeLevel();
                    break;
                case 308864: ///< Charged Weapons
                    damage += 100000;
                    damage += victim->CountPctFromMaxHealth(30);

                    if (instance)
                        if (auto challenge = instance->GetChallenge())
                            damage += 5 * challenge->GetChallengeLevel();
                    break;
            }
        }
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
                me->CastSpell(me, OptimalCoreTemperature, CastSpellExtraArgs(true).AddSpellBP0(50));
                Talk(TalkAggressionProtocolInitiated);
            });
        }
    }

    bool phased = false;
};

/// ID: 310835 Charged Weapons
class spell_charged_weapons : public AuraScript
{
    PrepareAuraScript(spell_charged_weapons);

    enum ChargedWeapon
    {
        ChargedWeaponStun = 306875,
        ChargedWeaponDmg = 308864,
        ChargedWeaponStacks = 308864,
    };

    void HandleProc(ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();

        if (auto caster = GetCaster())
        {
            if (auto target = eventInfo.GetActionTarget())
            {
                if (auto aur = target->GetAura(ChargedWeaponStacks))
                {
                    if (aur->GetStackAmount() >= 9)
                    {
                        aur->Remove();
                        caster->CastSpell(target, ChargedWeaponStun, true);
                        caster->CastSpell(target, ChargedWeaponDmg, true);
                    }
                }
            }
        }
    }

    void Register() override
    {
        OnProc += AuraProcFn(spell_charged_weapons::HandleProc);
    }
};

void AddSC_boss_general_nephmir()
{
    RegisterCreatureAI(npc_general_nephmir_707000);
    RegisterSpellScript(spell_charged_weapons);
}
