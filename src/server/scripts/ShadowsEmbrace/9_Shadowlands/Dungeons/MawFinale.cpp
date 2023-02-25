#include "SpellMgr.h"
#include "ScriptedCreature.h"
#include "Creature.h"
#include "ScriptedGossip.h"
#include "MotionMaster.h"
#include "Player.h"
#include "ScriptMgr.h"
#include "MoveSpline.h"
#include "GenericMovementGenerator.h"
#include "GameTime.h"
#include "CustomInstanceScript.h"
#include "Unit.h"

enum MawFinale
{
    BossJuno = 0,
};


const Position playerWalkPos[] = {
    { 131.501f, -2707.79f, 63.8894f, 3.95512f },
    { 110.134f, -2729.69f, 63.7608f, 3.93221f },
    //{ 108.313f, -2731.53f, 63.9403f, 3.93221f },
    //{ 106.835f, -2733.02f, 63.8733f, 3.93221f },
    //{ 104.62f, -2735.26f, 62.6342f, 3.93221f },
    //{ 97.8248f, -2742.12f, 62.5294f, 3.93221f },
    //{ 80.9361f, -2759.19f, 62.5321f, 3.93221f },
    //{ 68.6758f, -2771.58f, 62.5278f, 3.93221f },
};

const Position voidPortalPos = { 85.855774f, -2754.084717f, 62.533619f, 0.797260f }; // 339515
struct npc_juno_mawfinale : public ScriptedAI
{
public:
    npc_juno_mawfinale(Creature* creature) : ScriptedAI(creature) { }

    void InitializeAI() override
    {
        me->SetReactState(REACT_PASSIVE);
        me->SetUnitFlag(UNIT_FLAG_NON_ATTACKABLE);
    }

    void Reset()
    {

    }

    bool m_DidIntro = false;

    void OnUnitRelocation(Unit* who) override
    {
        if (m_DidIntro)
            return;

        if (who && who->IsPlayer() && who->GetDistance2d(me) <= 141.0f)
        {
            auto player = who->ToPlayer();
            if (player->IsGameMaster())
                return;

            m_DidIntro = true;
            //who->GetMotionMaster()->MoveSmoothPath(0, playerWalkPos, 2, true);
            Talk(0);
             
            scheduler.Schedule(10s, [this](TaskContext context)
                {
                    Talk(1);

                    scheduler.Schedule(7s, [this](TaskContext context)
                        {
                            Talk(2);
                            scheduler.Schedule(7s, [this](TaskContext context)
                                {
                                    Talk(3);
                                    scheduler.Schedule(4s, [this](TaskContext context)
                                        {
                                            // 209026 - Disappear
                                            DoCastSelf(209026);

                                            scheduler.Schedule(2s, [this](TaskContext context)
                                                {
                                                    me->DespawnOrUnsummon(1s);
                                                    DoSummon(700836, voidPortalPos, 0s, TEMPSUMMON_MANUAL_DESPAWN);
                                                    me->SummonGameObject(339515, voidPortalPos, {0.0f, 0.0f, 0.0f, 0.0f}, 30h, GOSummonType::GO_SUMMON_TIMED_DESPAWN);
                                                });
                                        });
                                });
                        });
                });
        }
    }

    void UpdateAI(uint32 diff) override
    {
        scheduler.Update(diff);
    }

    TaskScheduler scheduler;
};

struct npc_helya_mawfinale : public BossAI
{
    public:
        npc_helya_mawfinale(Creature* creature) : BossAI(creature, BossJuno)
        {
            ApplyAllImmunities(true);
        }

        enum Helya
        {
            CorrossiveNova        = 228872, // Spam cast this if we not in melee
            CorruptedBreath       = 228565, // Frontal cone, needs to be scripted.
            Decay                 = 228127, // Put this on all players on combat i guess.
            Torrent               = 368452,
            HelyasBoon            = 356897, // Summons a tentacle, Needs to be scripted and tentacle shouldnt move
            ArcaneticDestruction  = 277281, // Cast betwene random times
            SolarDestruction      = 277279, // Same with this.
            NaturalDestruction    = 277277, // here as well


            EventCorruptedBreath = 1,
            EventTorrent,
            EventHelyasBoon,
            EventDestruction,
            EventSolarDestruction,
            EventNaturalDestruction,
        };

        void InitializeAI() override
        {
            BossAI::InitializeAI();
            me->SetReactState(REACT_PASSIVE);
            me->SetUnitFlag(UNIT_FLAG_NON_ATTACKABLE);
            SetCombatMovement(false);
            me->SetControlled(true, UnitState::UNIT_STATE_ROOT);

            scheduler.Schedule(5s, [this](TaskContext context)
                {
                    Talk(0);
                    scheduler.Schedule(10s, [this](TaskContext context)
                        {
                            Talk(1);

                            scheduler.Schedule(5s, [this](TaskContext context)
                                {
                                    me->RemoveUnitFlag(UNIT_FLAG_NON_ATTACKABLE);
                                });
                        });
                });
        }

        void JustEngagedWith(Unit* who) override
        {
            BossAI::JustEngagedWith(who);
            me->SetReactState(REACT_AGGRESSIVE);
            Talk(2);
            DoCastAOE(Decay);
            events.ScheduleEvent(EventCorruptedBreath, 10s, 15s);
            events.ScheduleEvent(EventHelyasBoon, 30s);
            events.ScheduleEvent(EventDestruction, 20s);
            canMelee = true;
        }

        bool canMelee = false;

        void UpdateAI(uint32 diff) override
        {
            scheduler.Update(diff);

            if (!UpdateVictim())
                return;

            events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            auto victim = me->GetVictim();
            if (!me->IsWithinMeleeRange(me->GetVictim()))
            {
                DoCastAOE(CorrossiveNova);
                return;
            }

            if (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EventCorruptedBreath:
                        DoCastVictim(CorruptedBreath);
                        events.Repeat(30s);
                        break;
                    case EventTorrent:
                        DoCastAOE(Torrent);
                        events.Repeat(20s);
                        break;
                    case EventHelyasBoon:
                        DoCastVictim(HelyasBoon);
                        events.Repeat(30s, 45s);
                        break;
                    case EventDestruction:
                        canMelee = false;
                        DoCastVictim(ArcaneticDestruction);
                        events.ScheduleEvent(EventSolarDestruction, 3s);
                        events.Repeat(40s);

                        break;
                    case EventSolarDestruction:
                        DoCastVictim(SolarDestruction);
                        events.ScheduleEvent(EventNaturalDestruction, 3s);
                        break;
                    case EventNaturalDestruction:
                        DoCastVictim(NaturalDestruction);
                        canMelee = true;
                        break;
                }

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;
            }

            if (canMelee)
                DoMeleeAttackIfReady();
        }

        void JustDied(Unit* who) override
        {
            BossAI::JustDied(who);

            if (instance)
            instance->instance->DoOnPlayers([](Player* player)
            {
                player->CastSpell(player, 366997, true); // Fade to black

                player->GetScheduler().Schedule(1500ms, [](TaskContext context)
                {
                    auto player = context.GetUnit()->ToPlayer();
                    player->AddAura(326726, player); // sleep
                    player->TeleportTo(WorldLocation(1116, *player));
                });
            });
        }

        //void EnterEvadeMode(EvadeReason why)
        //{
        //    BossAI::EnterEvadeMode(why);
        //    _DespawnAtEvade(3s);
        //    summons.DespawnAll();
        //}

        TaskScheduler scheduler;
        EventMap events;
};

// 180331
struct npc_helyas_boon : public ScriptedAI
{
public:
    npc_helyas_boon(Creature* creature) : ScriptedAI(creature) { }

    void InitializeAI()
    {
        SetCombatMovement(false);
        me->SetControlled(true, UnitState::UNIT_STATE_ROOT);
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        if (!me->HasUnitState(UNIT_STATE_CASTING))
            DoCastAOE(356886); // Smash

        DoMeleeAttackIfReady();
    }

    void IsSummonedBy(WorldObject* who) override
    {
        if (!who)
            return;
        auto unit = who->ToUnit();
        if (!unit)
            return;

        me->SetLevel(unit->GetLevel());
        me->SetFaction(unit->GetFaction());
        if (unit->GetVictim())
            AttackStart(unit->GetVictim());
        me->SetMaxHealth(250000);
        me->SetFullHealth();
    }

    void DamageDealt(Unit* victim, uint32& damage, DamageEffectType type, SpellInfo const* spellInfo /*= nullptr*/) override
    {
        if (spellInfo)
        {
            if (spellInfo->Id == 356886)
                damage = 30000;
        }
    }
};

struct instance_mawfinale : public CustomInstanceScript
{
public:
    instance_mawfinale(InstanceMap* map) : CustomInstanceScript(map)
    {
    }

    bool SetBossState(uint32 bossId, EncounterState state, bool force = false) override
    {
        bool val = InstanceScript::SetBossState(bossId, state);

        if (bossId == BossJuno)
        {
            if (state == EncounterState::DONE)
            {
            }
        }

        return val;
    }
};

void AddSC_MawFinale()
{
    RegisterCreatureAI(npc_juno_mawfinale);
    RegisterCreatureAI(npc_helya_mawfinale);
    RegisterCreatureAI(npc_helyas_boon);
    RegisterInstanceScript(instance_mawfinale, 1277);
}
