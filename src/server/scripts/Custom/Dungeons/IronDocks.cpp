#include "CreatureAI.h"
#include "ScriptedCreature.h"
#include "Player.h"
#include "ScriptMgr.h"
#include "InstanceScript.h"
#include "GenericMovementGenerator.h"
#include "InstanceScenario.h"
#include "CustomInstanceScript.h"
#include "ReputationMgr.h"

enum IronDocks
{
    IronShot = 167365,
    IronShot2 = 174177,
    IncendorySlugs = 172802, // aura

    BossMarc = 0,
    BossFelloc,
    BossFleshEater,
    BossShulloc,
    BossSkulloc,
};

// 730609 - npc_beastmaster_730609
struct npc_beastmaster_730609 : public ScriptedAI
{
public:
    npc_beastmaster_730609(Creature* creature) : ScriptedAI(creature) { }

    void InitializeAI() override
    {
        /// TODO: Fill this function
    }
    void Reset() override
    {
        /// TODO: Fill this function
    }
    void JustEngagedWith(Unit* /*who*/) override
    {
        /// TODO: Fill this function
    }
    void UpdateAI(uint32 diff) override
    {
        scheduler.Update(diff);

        if (!UpdateVictim())
            return;

        events.Update(diff);

        if (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
            }
        }
        DoMeleeAttackIfReady();
    }

    void OnUnitRelocation(Unit* who) override
    {
        /// TODO: Fill this function
    }
    void DamageTaken(Unit* attacker, uint32& damage, DamageEffectType /*damageType*/, SpellInfo const* /*spellInfo = nullptr*/) override
    {
        /// TODO: Fill this function
    }

    TaskScheduler scheduler;
    EventMap events;
};

// 730610 - npc_flesh_eater_730610
// Mugarod boss
struct npc_flesh_eater_730610 : public BossAI
{
public:
    npc_flesh_eater_730610(Creature* creature) : BossAI(creature, BossFleshEater)
    {
        ApplyAllImmunities(true);
    }

    enum FleshEater
    {
        EventBladeStorm = 1,
        EventChainCleave,
        EventHackAndCleave,
        EventCharge,

        Bladestorm = 314316,
        ChainCleave = 343664,
        HackAndCleave = 326694,
        HeroicLeap = 178368,
        Charge = 361176,
    };

    void JustEngagedWith(Unit* who) override
    {
        BossAI::JustEngagedWith(who);
        didIntro = true;
        Talk(1);
        DoCast(who, Charge);
        //me->CastSpell(Position(6507.4f, -1108.37f, 4.95951f, 4.74936f), HeroicLeap, true);
        events.ScheduleEvent(EventBladeStorm, 5s, 30s);
        events.ScheduleEvent(EventChainCleave, 5s, 30s);
        events.ScheduleEvent(EventHackAndCleave, 5s, 30s);
        events.ScheduleEvent(EventCharge, 5s, 30s);
    }

    void UpdateAI(uint32 diff) override
    {
        scheduler.Update(diff);

        if (!UpdateVictim())
            return;

        events.Update(diff);

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        if (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EventBladeStorm:
                    DoCastVictim(Bladestorm);
                    events.Repeat(30s);
                    break;
                case EventChainCleave:
                    DoCastVictim(ChainCleave);
                    events.Repeat(15s);
                    break;
                case EventHackAndCleave:
                    DoCastVictim(HackAndCleave);
                    events.Repeat(8s);
                    break;
                case EventCharge:
                    DoCastVictim(Charge);
                    events.Repeat(8s);
                    break;
            }

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;
        }


        DoMeleeAttackIfReady();
    }

    void DamageDealt(Unit* victim, uint32& damage, DamageEffectType type, SpellInfo const* spellInfo /*= nullptr*/) override
    {
        if (spellInfo && victim)
        {
            switch (spellInfo->Id)
            {
                case Bladestorm:
                    damage += victim->CountPctFromMaxHealth(25);
                    break;
                case ChainCleave:
                {
                    uint32 addition = 5;

                    if (instance && instance->IsChallenge() && instance->GetChallenge())
                        addition *= instance->GetChallenge()->GetChallengeLevel();

                    damage += victim->CountPctFromMaxHealth(50 + addition);
                    break;
                }
                case HackAndCleave:
                {
                    damage += victim->CountPctFromMaxHealth(3);
                    break;
                }
            }
        }
    }

    bool didIntro = false;
    void OnUnitRelocation(Unit* who) override
    {
        /// TODO: Fill this function
        if (!didIntro && who->IsPlayer() && who->GetDistance2d(me) <= 50.0f)
        {
            didIntro = true;
            Talk(0);
        }
    }

    void EnterEvadeMode(EvadeReason why) override
    {
        BossAI::EnterEvadeMode(why);
        _DespawnAtEvade(3s);
    }

    void JustDied(Unit* who) override
    {
        Talk(2);
    }
};

// 730612 - npc_skulloc_730612
struct npc_skulloc_730612 : public BossAI
{
public:
    npc_skulloc_730612(Creature* creature) : BossAI(creature, BossSkulloc)
    {
        ApplyAllImmunities(true);
    }

    enum Skulloc
    {
        EventCannonBarrage = 1,
        EventBoulderToss,
        EventFireBreath,
        EventHeadButt,

        SpellWarHorn    = 170909,
        CannonBarrage   = 168511,
        BoulderToss     = 166207,
        FireBreath      = 342999,
        HeadButt        = 330393,
    };

    void JustEngagedWith(Unit* who) override
    {
        BossAI::JustEngagedWith(who);
        scheduler.CancelAll();
        Talk(1);
        DoCastAOE(SpellWarHorn);

        events.ScheduleEvent(EventCannonBarrage, 30s);
        events.ScheduleEvent(EventBoulderToss, 5s, 30s);
        events.ScheduleEvent(EventFireBreath, 5s, 30s);
        events.ScheduleEvent(EventHeadButt, 5s, 30s);
    }

    void UpdateAI(uint32 diff) override
    {
        scheduler.Update(diff);

        if (!UpdateVictim())
            return;

        events.Update(diff);

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        if (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EventCannonBarrage:
                    DoCastVictim(CannonBarrage);
                    events.Repeat(30s);
                    break;
                case EventBoulderToss:
                    DoCastVictim(BoulderToss);
                    events.Repeat(5s, 20s);
                    break;
                case EventFireBreath:
                    DoCastVictim(FireBreath);
                    events.Repeat(20s, 30s);
                    break;
                case EventHeadButt:
                    DoCastVictim(HeadButt);
                    events.Repeat(20s, 30s);
                    break;
            }

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;
        }
        DoMeleeAttackIfReady();
    }

    bool didIntro = false;
    void OnUnitRelocation(Unit* who) override
    {
        if (!didIntro && who->IsPlayer() && who->GetDistance2d(me) <= 45.0f)
        {
            didIntro = true;
            Talk(0);

            scheduler.Schedule(5s, [this](TaskContext context)
            {
                DoZoneInCombat(me);
            });
        }
    }

    void EnterEvadeMode(EvadeReason why) override
    {
        BossAI::EnterEvadeMode(why);
        _DespawnAtEvade(3s);
    }

    void JustDied(Unit* who) override
    {
        Talk(2);
    }
};

// 730617 - npc_parc_730617
struct npc_parc_730617 : public ScriptedAI
{
public:
    npc_parc_730617(Creature* creature) : ScriptedAI(creature) { }

    void InitializeAI() override
    {
        /// TODO: Fill this function
    }
    void Reset() override
    {
        /// TODO: Fill this function
    }
    void JustEngagedWith(Unit* /*who*/) override
    {
        if (auto marc = me->FindNearestCreature(705008, 50.0f))
            DoZoneInCombat(marc);
    }
    void UpdateAI(uint32 diff) override
    {
        scheduler.Update(diff);

        if (!UpdateVictim())
            return;

        events.Update(diff);

        if (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
            }
        }
        DoMeleeAttackIfReady();
    }

    void OnUnitRelocation(Unit* who) override
    {
        /// TODO: Fill this function
    }
    void DamageTaken(Unit* attacker, uint32& damage, DamageEffectType /*damageType*/, SpellInfo const* /*spellInfo = nullptr*/) override
    {
        /// TODO: Fill this function
    }

    void JustDied(Unit* who) override
    {
        if (auto marc = me->FindNearestCreature(705008, 50.0f))
            if (marc->IsAlive())
                if (marc->AI())
                    marc->AI()->Talk(2);
    }

    TaskScheduler scheduler;
    EventMap events;
};

// 730619 - npc_iron_recruit_730619
struct npc_iron_recruit_730619 : public ScriptedAI
{
public:
    npc_iron_recruit_730619(Creature* creature) : ScriptedAI(creature) { }

    void InitializeAI() override
    {
        /// TODO: Fill this function
    }
    void Reset() override
    {
        /// TODO: Fill this function
    }
    void JustEngagedWith(Unit* /*who*/) override
    {
        /// TODO: Fill this function
    }

    void JustDied(Unit* /*killer*/) override
    {
        if (me->GetSpawnId() == 1052851)
        {
            if (auto overseer = me->FindNearestCreatureBySpawnId(1054847, 50.0f))
            {
                overseer->HandleEmoteCommand(Emote::EMOTE_ONESHOT_LAUGH);
                if (overseer->AI())
                    overseer->AI()->Talk(2);
            }
        }
    }

    void UpdateAI(uint32 diff) override
    {
        scheduler.Update(diff);

        if (!UpdateVictim())
            return;

        events.Update(diff);

        if (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
            }
        }
        DoMeleeAttackIfReady();
    }

    void OnUnitRelocation(Unit* who) override
    {
        /// TODO: Fill this function
    }
    void DamageTaken(Unit* attacker, uint32& damage, DamageEffectType /*damageType*/, SpellInfo const* /*spellInfo = nullptr*/) override
    {
        /// TODO: Fill this function
    }

    TaskScheduler scheduler;
    EventMap events;
};

// 730620 - npc_iron_horde_captain_730620
struct npc_iron_horde_captain_730620 : public ScriptedAI
{
public:
    npc_iron_horde_captain_730620(Creature* creature) : ScriptedAI(creature) { }

    void InitializeAI() override
    {
        /// TODO: Fill this function
    }
    void Reset() override
    {
        /// TODO: Fill this function
    }
    void JustEngagedWith(Unit* /*who*/) override
    {
        me->SetEmoteState(Emote::EMOTE_ONESHOT_NONE);
    }
    void UpdateAI(uint32 diff) override
    {
        scheduler.Update(diff);

        if (!UpdateVictim())
            return;

        events.Update(diff);

        if (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
            }
        }
        DoMeleeAttackIfReady();
    }

    void OnUnitRelocation(Unit* who) override
    {
        /// TODO: Fill this function
    }
    void DamageTaken(Unit* attacker, uint32& damage, DamageEffectType /*damageType*/, SpellInfo const* /*spellInfo = nullptr*/) override
    {
        /// TODO: Fill this function
    }

    TaskScheduler scheduler;
    EventMap events;
};

// 730621 - npc_iron_horde_general_730621
struct npc_iron_horde_general_730621 : public ScriptedAI
{
public:
    npc_iron_horde_general_730621(Creature* creature) : ScriptedAI(creature) { }

    void InitializeAI() override
    {
        /// TODO: Fill this function
    }
    void Reset() override
    {
        /// TODO: Fill this function
    }
    void JustEngagedWith(Unit* /*who*/) override
    {
        scheduler.CancelAll();

        if (me->GetSpawnId() == 1054631)
            Talk(4);
        else if (me->GetSpawnId() == 1054637)
            Talk(6);
        else if (me->GetSpawnId() == 1054663)
            Talk(7);
        else if (me->GetSpawnId() == 1052853)
            Talk(8);
    }

    void JustDied(Unit* who) override
    {
        scheduler.CancelAll();

        if (me->GetSpawnId() == 1054637) // todo achievement
        {
            // if using no weapons:
            // Talk(10);
            // else if they DID use weapons:
            // Talk(11);
        }
        else if (me->GetSpawnId() == 1052853)
            Talk(9);
    }

    void UpdateAI(uint32 diff) override
    {
        scheduler.Update(diff);

        if (!UpdateVictim())
            return;

        events.Update(diff);

        if (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
            }
        }
        DoMeleeAttackIfReady();
    }

    bool didIntro = false;
    void OnUnitRelocation(Unit* who) override
    {
        if (!didIntro && who->IsPlayer()) ///< First one in dungeon
        {
            if (who->GetDistance2d(me) <= 68.0f)
            {
                if (me->GetSpawnId() == 1054663)
                {
                    didIntro = true;
                    Talk(0);
                    scheduler.Schedule(2s, [this](TaskContext context)
                    {
                        if (auto cap1 = me->FindNearestCreatureBySpawnId(1054735, 50.0f))
                            cap1->SetEmoteState(Emote::EMOTE_STATE_APPLAUD);
                        if (auto cap2 = me->FindNearestCreatureBySpawnId(1054737, 50.0f))
                            cap2->SetEmoteState(Emote::EMOTE_STATE_APPLAUD);

                        scheduler.Schedule(2s, [this](TaskContext context)
                        {
                            if (auto cap1 = me->FindNearestCreatureBySpawnId(1054735, 50.0f))
                                cap1->SetEmoteState(Emote::EMOTE_ONESHOT_NONE);
                            if (auto cap2 = me->FindNearestCreatureBySpawnId(1054737, 50.0f))
                                cap2->SetEmoteState(Emote::EMOTE_ONESHOT_NONE);

                        });
                    });
                }
                else if (me->GetSpawnId() == 1052853)
                {
                    didIntro = true;
                    Talk(1);

                    scheduler.Schedule(5s, [this](TaskContext context)
                    {
                        std::list<Unit*> ironRecruits;
                        me->GetFriendlyUnitListInRange(ironRecruits, 75.0f);
                        ironRecruits.remove_if([](Unit* who) {
                            return who->GetEntry() != 730619 || !who->IsAlive();
                        });
                        uint32 chance = 0;
                        for (auto recruit : ironRecruits)
                        {
                            if (roll_chance_i(5 + chance))
                            {
                                chance = 0;
                                if (auto c = recruit->ToCreature())
                                    if (c->AI())
                                        c->AI()->Talk(2);

                                ObjectGuid generalGuid;
                                if (auto general = recruit->FindNearestCreature(730620, 25.0f))
                                {
                                    generalGuid = general->GetGUID();
                                    if (general->AI())
                                        general->AI()->Talk(0);
                                }

                                scheduler.Schedule(5s, [generalGuid, this](TaskContext context)
                                {
                                    if (auto general = ObjectAccessor::GetCreature(*me, generalGuid))
                                        if (general->AI())
                                            general->AI()->Talk(1);

                                    scheduler.Schedule(5s, [generalGuid, this](TaskContext context)
                                    {
                                        if (auto general = ObjectAccessor::GetCreature(*me, generalGuid))
                                        {
                                            std::list<Unit*> ironRecruits;
                                            general->GetFriendlyUnitListInRange(ironRecruits, 25.0f);
                                            ironRecruits.remove_if([](Unit* who) {
                                                return who->GetEntry() != 730619 || !who->IsAlive();
                                            });

                                            for (auto recruit : ironRecruits)
                                            {
                                                if (auto c = recruit->ToCreature())
                                                    if (c->AI())
                                                        c->AI()->Talk(3);
                                            }
                                        }
                                    });
                                });

                                break;
                            }
                            else
                                chance += 5;
                        }
                    });

                    scheduler.Schedule(40s, [this](TaskContext context)
                    {
                        didIntro = false;
                    });
                }
            }

            if (me->GetSpawnId() == 1054631)
            {
                if (who->GetDistance2d(me) <= 32.0f)
                {
                    didIntro = true;
                    Talk(2);
                    scheduler.Schedule(4s, [this](TaskContext context)
                    {
                        Talk(3);
                        if (auto warlock = me->FindNearestCreatureBySpawnId(1054837, 50.0f))
                            DoZoneInCombat(warlock);
                        if (auto warlock = me->FindNearestCreatureBySpawnId(1054635, 50.0f))
                            DoZoneInCombat(warlock);
                    });
                }
            }
            else if (me->GetSpawnId() == 1054637)
            {
                if (who->GetDistance2d(me) <= 32.0f)
                {
                    didIntro = true;
                    Talk(5);
                    scheduler.Schedule(6s, [this](TaskContext context)
                    {
                        DoZoneInCombat();
                    });
                }
            }
        }
    }
    void DamageTaken(Unit* attacker, uint32& damage, DamageEffectType /*damageType*/, SpellInfo const* /*spellInfo = nullptr*/) override
    {
        /// TODO: Fill this function
    }

    TaskScheduler scheduler;
    EventMap events;
};

// 730624 - npc_iron_horde_brute_730624
struct npc_iron_horde_brute_730624 : public ScriptedAI
{
public:
    npc_iron_horde_brute_730624(Creature* creature) : ScriptedAI(creature) { }

    void InitializeAI() override
    {
        /// TODO: Fill this function
    }
    void Reset() override
    {
        /// TODO: Fill this function
    }
    void JustEngagedWith(Unit* /*who*/) override
    {
        /// TODO: Fill this function
    }
    void UpdateAI(uint32 diff) override
    {
        scheduler.Update(diff);

        if (!UpdateVictim())
            return;

        events.Update(diff);

        if (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
            }
        }
        DoMeleeAttackIfReady();
    }

    void OnUnitRelocation(Unit* who) override
    {
        /// TODO: Fill this function
    }
    void DamageTaken(Unit* attacker, uint32& damage, DamageEffectType /*damageType*/, SpellInfo const* /*spellInfo = nullptr*/) override
    {
        /// TODO: Fill this function
    }

    TaskScheduler scheduler;
    EventMap events;
};

// 730613 - npc_shulloc_730613
struct npc_shulloc_730613 : public BossAI
{
public:
    npc_shulloc_730613(Creature* creature) : BossAI(creature, BossShulloc)
    {
        ApplyAllImmunities(true);
    }

    enum Shulloc
    {
        EventThrowBoulder = 1,
        EventRoarOfTerror,
        EventBoulderThrow,
        EventTrample,
        EventEarthquake,
        EventCrushingSlam,

        ThrowBoulder = 282680,
        RoarOfTerror = 213657,
        BoulderThrow = 355464,
        Trample = 275594,
        Earthquake = 360577,
        CrushingSlam = 127480,
    };

    void JustEngagedWith(Unit* who) override
    {
        BossAI::JustEngagedWith(who);
        Talk(0);

        events.ScheduleEvent(EventThrowBoulder, 5s, 10s);
        events.ScheduleEvent(EventRoarOfTerror, 1s);
        events.ScheduleEvent(EventBoulderThrow, 5s, 10s);
        events.ScheduleEvent(EventTrample, 5s, 20s);
        events.ScheduleEvent(EventEarthquake, 5s, 20s);
        events.ScheduleEvent(EventCrushingSlam, 5s, 20s);
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        events.Update(diff);

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        if (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EventThrowBoulder:
                    DoCastVictim(ThrowBoulder);
                    events.Repeat(20s, 30s);
                    break;
                case EventRoarOfTerror:
                    DoCastVictim(RoarOfTerror);
                    events.Repeat(40s);
                    break;
                case EventBoulderThrow:
                    DoCastVictim(BoulderThrow);
                    events.Repeat(20s, 30s);
                    break;
                case EventTrample:
                    DoCastVictim(Trample);
                    events.Repeat(20s, 30s);
                    break;
                case EventEarthquake:
                    DoCastVictim(Earthquake);
                    events.Repeat(20s, 30s);
                    break;
                case EventCrushingSlam:
                    DoCastVictim(CrushingSlam);
                    events.Repeat(20s, 30s);
                    break;
            }

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
};

// 730608 - npc_barrel_730608
struct npc_barrel_730608 : public ScriptedAI
{
public:
    npc_barrel_730608(Creature* creature) : ScriptedAI(creature) { }

    void InitializeAI() override
    {
        SetCombatMovement(false);
        me->SetReactState(REACT_PASSIVE);
    }

    void JustDied(Unit* who) override
    {
        if (auto instance = me->GetInstanceScript())
            if (auto map = instance->instance)
                map->DoOnPlayers([](Player* player)
            {
                player->ModifyCurrency(1813, urand(20, 30));
            });
    }

    void UpdateAI(uint32 diff) override
    {
        scheduler.Update(diff);

        if (!UpdateVictim())
            return;

        events.Update(diff);

        if (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
            }
        }
        DoMeleeAttackIfReady();
    }

    TaskScheduler scheduler;
    EventMap events;
};

const Position elephantPath[] = {
    { 6511.64f, -822.694f, 4.93351f, 3.76764f },
    { 6484.66f, -852.841f, 4.94041f, 4.07199f },
    { 6481.16f, -868.294f, 4.9396f, 4.85411f },
    { 6497.43f, -893.261f, 4.95903f, 5.32862f },
    { 6505.73f, -935.216f, 4.95906f, 4.72976f },
    { 6504.0f, -961.255f, 4.95882f, 4.25851f },
    { 6480.77f, -958.792f, 4.95882f, 3.1655f },
    { 6462.25f, -986.277f, 4.9589f, 4.68394f },
    { 6464.72f, -1013.01f, 4.9589f, 5.27954f },
    { 6483.76f, -1016.32f, 4.95937f, 6.22529f },
    { 6503.74f, -1015.8f, 4.95937f, 0.0239156f },
    { 6517.74f, -1015.42f, 4.95926f, 0.0239156f },
};

// 705006 - npc_war_elephant_705006
struct npc_war_elephant_705006 : public ScriptedAI
{
public:
    npc_war_elephant_705006(Creature* creature) : ScriptedAI(creature) { }

    void InitializeAI() override
    {
        /// TODO: Fill this function
    }
    void Reset() override
    {
        /// TODO: Fill this function
    }
    void JustEngagedWith(Unit* /*who*/) override
    {
        /// TODO: Fill this function
    }
    void UpdateAI(uint32 diff) override
    {
        if (charging)
        {
            std::list<Unit*> inWayNpcs;
            me->GetFriendlyUnitListInRange(inWayNpcs, 7.0f, true);
            for (auto npc : inWayNpcs)
            {
                if (npc != me)
                    npc->KillSelf();
            }
        }

        scheduler.Update(diff);

        if (!UpdateVictim())
            return;

        events.Update(diff);

        if (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
            }
        }
        DoMeleeAttackIfReady();
    }

    bool charging = false;
    void DoAction(int32 actionId) override
    {
        if (actionId == 1)
        {
            if (!charging && me->IsAlive() && !me->IsInCombat())
            {
                DoCastSelf(310613);
                me->SetReactState(REACT_PASSIVE);
                charging = true;
                me->GetMotionMaster()->MoveSmoothPath(1, elephantPath, 12, false, false, 25.0f)->callbackFunc = [this]()
                {
                    charging = false;
                    me->KillSelf();
                };
            }
        }
    }

    void OnUnitRelocation(Unit* who) override
    {
        /// TODO: Fill this function
    }
    void DamageTaken(Unit* attacker, uint32& damage, DamageEffectType /*damageType*/, SpellInfo const* /*spellInfo = nullptr*/) override
    {
        /// TODO: Fill this function
    }

    TaskScheduler scheduler;
    EventMap events;
};

// 730604 - npc_fel_destroyer_730604
struct npc_fel_destroyer_730604 : public ScriptedAI
{
public:
    npc_fel_destroyer_730604(Creature* creature) : ScriptedAI(creature) { }

    void InitializeAI() override
    {
        /// TODO: Fill this function
    }
    void Reset() override
    {
        /// TODO: Fill this function
    }
    void JustEngagedWith(Unit* /*who*/) override
    {
        /// TODO: Fill this function
    }
    void UpdateAI(uint32 diff) override
    {
        scheduler.Update(diff);

        if (!UpdateVictim())
            return;

        events.Update(diff);

        if (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
            }
        }
        DoMeleeAttackIfReady();
    }

    void OnUnitRelocation(Unit* who) override
    {
        /// TODO: Fill this function
    }
    void DamageTaken(Unit* attacker, uint32& damage, DamageEffectType /*damageType*/, SpellInfo const* /*spellInfo = nullptr*/) override
    {
        /// TODO: Fill this function
    }

    TaskScheduler scheduler;
    EventMap events;
};

// 730601 - npc_iron_horde_warlock_730601
struct npc_iron_horde_warlock_730601 : public ScriptedAI
{
public:
    npc_iron_horde_warlock_730601(Creature* creature) : ScriptedAI(creature) { }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        if (!me->HasUnitState(UNIT_STATE_CASTING))
            DoCastVictim(235951); // Chaos bolt
    }
};

// 705011 - npc_iron_hound_705011
struct npc_iron_hound_705011 : public ScriptedAI
{
public:
    npc_iron_hound_705011(Creature* creature) : ScriptedAI(creature) { }

    void InitializeAI() override
    {
        /// TODO: Fill this function
    }
    void Reset() override
    {
        /// TODO: Fill this function
    }
    void JustEngagedWith(Unit* /*who*/) override
    {
        /// TODO: Fill this function
    }
    void UpdateAI(uint32 diff) override
    {
        scheduler.Update(diff);

        if (!UpdateVictim())
            return;

        events.Update(diff);

        if (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
            }
        }
        DoMeleeAttackIfReady();
    }

    void OnUnitRelocation(Unit* who) override
    {
        /// TODO: Fill this function
    }
    void DamageTaken(Unit* attacker, uint32& damage, DamageEffectType /*damageType*/, SpellInfo const* /*spellInfo = nullptr*/) override
    {
        /// TODO: Fill this function
    }

    TaskScheduler scheduler;
    EventMap events;
};

// 705010 - npc_felloc_705010
struct npc_felloc_705010 : public BossAI
{
public:
    npc_felloc_705010(Creature* creature) : BossAI(creature, BossFelloc)
    {
        ApplyAllImmunities(true);
    }

    enum Felloc
    {
        EventThrowBoulder = 1,
        EventRoarOfTerror,
        EventBoulderThrow,
        EventTrample,
        EventEarthquake,
        EventCrushingSlam,
        EventFelfireVolley,

        ThrowBoulder = 282680,
        RoarOfTerror = 213657,
        BoulderThrow = 355464,
        Trample = 275594,
        Earthquake = 360577,
        CrushingSlam = 127480,
        FelfireVolley = 340793,
    };

    void JustEngagedWith(Unit* who) override
    {
        BossAI::JustEngagedWith(who);
        Talk(0);

        events.ScheduleEvent(EventThrowBoulder, 5s, 10s);
        events.ScheduleEvent(EventRoarOfTerror, 1s);
        events.ScheduleEvent(EventBoulderThrow, 5s, 10s);
        events.ScheduleEvent(EventTrample, 5s, 20s);
        events.ScheduleEvent(EventEarthquake, 5s, 20s);
        events.ScheduleEvent(EventCrushingSlam, 5s, 20s);
        events.ScheduleEvent(EventFelfireVolley, 5s, 20s);
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        events.Update(diff);

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        if (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EventThrowBoulder:
                    DoCastVictim(ThrowBoulder);
                    events.Repeat(20s, 30s);
                    break;
                case EventRoarOfTerror:
                    DoCastVictim(RoarOfTerror);
                    events.Repeat(40s);
                    break;
                case EventBoulderThrow:
                    DoCastVictim(BoulderThrow);
                    events.Repeat(20s, 30s);
                    break;
                case EventTrample:
                    DoCastVictim(Trample);
                    events.Repeat(20s, 30s);
                    break;
                case EventEarthquake:
                    DoCastVictim(Earthquake);
                    events.Repeat(20s, 30s);
                    break;
                case EventCrushingSlam:
                    DoCastVictim(CrushingSlam);
                    events.Repeat(20s, 30s);
                    break;
                case EventFelfireVolley:
                    DoCastVictim(FelfireVolley);
                    events.Repeat(6s, 10s);
                    break;
            }

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

    void JustDied(Unit* who) override
    {
        Talk(1);
    }
};

// 705009 - npc_iron_dock_overseer_705009
struct npc_iron_dock_overseer_705009 : public ScriptedAI
{
public:
    npc_iron_dock_overseer_705009(Creature* creature) : ScriptedAI(creature) { }

    void InitializeAI() override
    {
        /// TODO: Fill this function
    }
    void Reset() override
    {
        /// TODO: Fill this function
    }
    void JustEngagedWith(Unit* /*who*/) override
    {
        scheduler.CancelAll();
    }
    void JustDied(Unit* /*k*/) override
    {
        scheduler.CancelAll();
    }
    void UpdateAI(uint32 diff) override
    {
        scheduler.Update(diff);

        if (!UpdateVictim())
            return;

        events.Update(diff);

        if (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
            }
        }
        DoMeleeAttackIfReady();
    }

    bool didIntro = false;
    bool didIntro2 = false;
    bool didIntro3 = false;

    void OnUnitRelocation(Unit* who) override
    {
        if (!me->IsAlive())
            return;

        if (!didIntro && who->IsPlayer() && who->GetDistance2d(me) <= 50.0f && me->GetSpawnId() == 1054847)
        {
            didIntro = true;
            if (auto recruit = me->FindNearestCreatureBySpawnId(1052851, 10.0f))
            {
                if (recruit->AI())
                    recruit->AI()->Talk(0);
                scheduler.Schedule(3s, [this](TaskContext context)
                {
                    Talk(0);
                    me->HandleEmoteCommand(Emote::EMOTE_ONESHOT_LAUGH);

                    if (auto recruit = me->FindNearestCreatureBySpawnId(1052851, 10.0f))
                        recruit->HandleEmoteCommand(Emote::EMOTE_ONESHOT_CRY);
                    scheduler.Schedule(1s, [this](TaskContext context)
                    {
                        if (auto recruit = me->FindNearestCreatureBySpawnId(1052851, 10.0f))
                        {
                            recruit->HandleEmoteCommand(Emote::EMOTE_ONESHOT_BEG);
                            if (recruit->AI())
                                recruit->AI()->Talk(1);
                        }
                    });
                });
            }
        }

        if (!didIntro2 && who->IsPlayer() && who->GetDistance2d(me) <= 25.0f && me->GetSpawnId() == 1054847)
        {
            didIntro = true;
            scheduler.CancelAll();
            didIntro2 = true;
            Talk(1);
            me->SetReactState(REACT_DEFENSIVE);

            if (auto recruit = me->FindNearestCreatureBySpawnId(1052851, 10.0f))
                DoZoneInCombat(recruit);
        }

        if (!didIntro3 && who->IsPlayer() && who->GetDistance2d(me) <= 63.0f && me->GetSpawnId() == 1054914)
        {
            didIntro3 = true;
            Talk(3);

            scheduler.Schedule(6s, [this](TaskContext context)
            {
                if (auto bm = me->FindNearestCreatureBySpawnId(1054717, 25.0f))
                {
                    if (bm->AI())
                        bm->AI()->Talk(0);
                }
                scheduler.Schedule(6s, [this](TaskContext context)
                {
                    if (auto bm = me->FindNearestCreatureBySpawnId(1054718, 25.0f))
                    {
                        if (bm->AI())
                            bm->AI()->Talk(1);
                    }
                    scheduler.Schedule(3s, [this](TaskContext context)
                    {
                        Talk(4);
                        scheduler.Schedule(6s, [this](TaskContext context)
                        {
                            if (auto bm = me->FindNearestCreatureBySpawnId(1054717, 25.0f))
                            {
                                if (bm->AI())
                                    bm->AI()->Talk(2);
                            }
                        });
                    });
                });
            });
        }
    }
    void DamageTaken(Unit* attacker, uint32& damage, DamageEffectType /*damageType*/, SpellInfo const* /*spellInfo = nullptr*/) override
    {
        /// TODO: Fill this function
    }

    TaskScheduler scheduler;
    EventMap events;
};

// 705008 - npc_marc_705008
struct npc_marc_705008 : public BossAI
{
public:
    npc_marc_705008(Creature* creature) : BossAI(creature, BossMarc)
    {
        ApplyAllImmunities(true);
    }

    void JustEngagedWith(Unit* who) override
    {
        BossAI::JustEngagedWith(who);
        Talk(0);

        if (auto parc = me->FindNearestCreature(730617, 50.0f))
        {
            DoZoneInCombat(parc);

            scheduler.Schedule(3s, [this](TaskContext context)
            {
                if (auto parc = me->FindNearestCreature(730617, 50.0f))
                {
                    if (parc->AI())
                    {
                        parc->AI()->Talk(0);

                        scheduler.Schedule(3s, [this](TaskContext context)
                        {
                            Talk(1);
                        });
                    }
                }
            });
        }
    }

    void UpdateAI(uint32 diff) override
    {
        scheduler.Update(diff);

        if (!UpdateVictim())
            return;

        events.Update(diff);

        if (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
            }
        }
        DoMeleeAttackIfReady();
    }

    void JustDied(Unit* who) override
    {
        if (auto parc = me->FindNearestCreature(730617, 50.0f))
            if (parc->IsAlive())
                if (parc->AI())
                    parc->AI()->Talk(1);
    }
};

// 705007 - npc_iron_dock_worker_705007
struct npc_iron_dock_worker_705007 : public ScriptedAI
{
public:
    npc_iron_dock_worker_705007(Creature* creature) : ScriptedAI(creature) { }

    void InitializeAI() override
    {
        if (me->GetSpawnId() == 1054684)
        {
            me->SetReactState(REACT_PASSIVE);
            me->SetEmoteState(Emote::EMOTE_ONESHOT_SLEEP);
            DoCastSelf(353814); // Sleep
            me->SetUnitFlag(UnitFlags::UNIT_FLAG_IMMUNE_TO_PC);
            me->SetUnitFlag(UnitFlags::UNIT_FLAG_NON_ATTACKABLE);
        }
        else
            me->SetEmoteState(Emote::EMOTE_STATE_WORK_CHOPWOOD);
    }
    void Reset() override
    {
        if (me->GetSpawnId() != 1054684)
            me->SetEmoteState(Emote::EMOTE_STATE_WORK_CHOPWOOD);
    }
    void JustEngagedWith(Unit* /*who*/) override
    {
        /// TODO: Fill this function
    }
    void UpdateAI(uint32 diff) override
    {
        scheduler.Update(diff);

        if (!UpdateVictim())
            return;

        events.Update(diff);

        if (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
            }
        }
        DoMeleeAttackIfReady();
    }

    void OnUnitRelocation(Unit* who) override
    {
        /// TODO: Fill this function
    }
    void DamageTaken(Unit* attacker, uint32& damage, DamageEffectType /*damageType*/, SpellInfo const* /*spellInfo = nullptr*/) override
    {
        /// TODO: Fill this function
    }

    TaskScheduler scheduler;
    EventMap events;
};

// 705004 - npc_iron_archer_705004
struct npc_iron_archer_705004 : public ScriptedAI
{
public:
    npc_iron_archer_705004(Creature* creature) : ScriptedAI(creature) { }

    void InitializeAI() override
    {
        me->AddAura(IncendorySlugs, me);
        scheduler.Schedule(1s, [this](TaskContext context)
        {
            Position pos = *me;
            me->MovePositionToFirstCollision(pos, 30.0f, me->GetOrientation());
            me->CastSpell(WorldLocation(me->GetMapId(), pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ(), pos.GetOrientation()), IronShot, false);
            context.Repeat(2s, 3s);
        });
    }
    void Reset() override
    {
        me->AddAura(IncendorySlugs, me);
    }
    void JustEngagedWith(Unit* /*who*/) override
    {
        scheduler.CancelAll();
    }
    void UpdateAI(uint32 diff) override
    {
        scheduler.Update(diff);

        if (!UpdateVictim())
            return;

        events.Update(diff);

        if (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
            }
        }
        DoMeleeAttackIfReady();
    }

    void OnUnitRelocation(Unit* who) override
    {
        /// TODO: Fill this function
    }
    void DamageTaken(Unit* attacker, uint32& damage, DamageEffectType /*damageType*/, SpellInfo const* /*spellInfo = nullptr*/) override
    {
        /// TODO: Fill this function
    }

    TaskScheduler scheduler;
    EventMap events;
};

// 730603 - npc_iron_horde_slaver_730603
struct npc_iron_horde_slaver_730603 : public ScriptedAI
{
public:
    npc_iron_horde_slaver_730603(Creature* creature) : ScriptedAI(creature) { }

    void InitializeAI() override
    {
        /// TODO: Fill this function
    }
    void Reset() override
    {
        /// TODO: Fill this function
    }
    void JustEngagedWith(Unit* /*who*/) override
    {
        /// TODO: Fill this function
    }
    void UpdateAI(uint32 diff) override
    {
        scheduler.Update(diff);

        if (!UpdateVictim())
            return;

        events.Update(diff);

        if (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
            }
        }
        DoMeleeAttackIfReady();
    }

    void OnUnitRelocation(Unit* who) override
    {
        /// TODO: Fill this function
    }
    void DamageTaken(Unit* attacker, uint32& damage, DamageEffectType /*damageType*/, SpellInfo const* /*spellInfo = nullptr*/) override
    {
        /// TODO: Fill this function
    }

    TaskScheduler scheduler;
    EventMap events;
};

// 705012 - npc_slave_705012
struct npc_slave_705012 : public ScriptedAI
{
public:
    npc_slave_705012(Creature* creature) : ScriptedAI(creature) { }

    void InitializeAI() override
    {
        /// TODO: Fill this function
    }
    void Reset() override
    {
        /// TODO: Fill this function
    }
    void JustEngagedWith(Unit* /*who*/) override
    {
        /// TODO: Fill this function
    }
    void UpdateAI(uint32 diff) override
    {
        scheduler.Update(diff);

        if (!UpdateVictim())
            return;

        events.Update(diff);

        if (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
            }
        }
        DoMeleeAttackIfReady();
    }

    void OnUnitRelocation(Unit* who) override
    {
        /// TODO: Fill this function
    }
    void DamageTaken(Unit* attacker, uint32& damage, DamageEffectType /*damageType*/, SpellInfo const* /*spellInfo = nullptr*/) override
    {
        /// TODO: Fill this function
    }

    TaskScheduler scheduler;
    EventMap events;
};

const Position explosiveChickPath[] = {
    { 6561.49f, -830.954f, 4.93407f, 2.51099f },
    { 6504.14f, -788.871f, 4.94036f, 2.51427f },
};

// 705013 - npc_explosive_chicken_705013
struct npc_explosive_chicken_705013 : public ScriptedAI
{
public:
    npc_explosive_chicken_705013(Creature* creature) : ScriptedAI(creature) { }

    void InitializeAI() override
    {
        /// TODO: Fill this function
    }
    void Reset() override
    {
        /// TODO: Fill this function
    }
    void JustEngagedWith(Unit* /*who*/) override
    {
        /// TODO: Fill this function
    }
    void UpdateAI(uint32 diff) override
    {
        scheduler.Update(diff);

        if (!UpdateVictim())
            return;

        events.Update(diff);

        if (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
            }
        }
        DoMeleeAttackIfReady();
    }

    bool inProg = false;
    void DoAction(int32 actionId) override
    {
        if (actionId == 1)
        {
            if (!inProg)
            {
                inProg = true;
                me->SetUnitFlag(UnitFlags::UNIT_FLAG_UNINTERACTIBLE);
                DoCast(259463);
                me->GetMotionMaster()->MoveSmoothPath(1, explosiveChickPath, 2, false, false, 15.0f);
            }
        }
        else if (actionId == 2)
        {
            me->KillSelf();
            DoCastSelf(317961, true);
        }
    }

    void OnUnitRelocation(Unit* who) override
    {
        /// TODO: Fill this function
    }
    void DamageTaken(Unit* attacker, uint32& damage, DamageEffectType /*damageType*/, SpellInfo const* /*spellInfo = nullptr*/) override
    {
        /// TODO: Fill this function
    }

    TaskScheduler scheduler;
    EventMap events;
};

// 705014 - npc_siegemaker_705014
struct npc_siegemaker_705014 : public ScriptedAI
{
public:
    npc_siegemaker_705014(Creature* creature) : ScriptedAI(creature) { }

    void InitializeAI() override
    {
        /// TODO: Fill this function
    }
    void Reset() override
    {
        /// TODO: Fill this function
    }
    void JustEngagedWith(Unit* /*who*/) override
    {
        /// TODO: Fill this function
    }
    void UpdateAI(uint32 diff) override
    {
        scheduler.Update(diff);

        if (!UpdateVictim())
            return;

        events.Update(diff);

        if (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
            }
        }
        DoMeleeAttackIfReady();
    }

    void OnUnitRelocation(Unit* who) override
    {
        /// TODO: Fill this function
    }
    void DamageTaken(Unit* attacker, uint32& damage, DamageEffectType /*damageType*/, SpellInfo const* /*spellInfo = nullptr*/) override
    {
        /// TODO: Fill this function
    }

    TaskScheduler scheduler;
    EventMap events;
};

// 705015 - npc_muzgonk_705015
struct npc_muzgonk_705015 : public ScriptedAI
{
public:
    npc_muzgonk_705015(Creature* creature) : ScriptedAI(creature) { }

    void InitializeAI() override
    {
        /// TODO: Fill this function
    }
    void Reset() override
    {
        /// TODO: Fill this function
    }
    void JustEngagedWith(Unit* /*who*/) override
    {
        /// TODO: Fill this function
    }
    void UpdateAI(uint32 diff) override
    {
        scheduler.Update(diff);

        if (!UpdateVictim())
            return;

        events.Update(diff);

        if (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
            }
        }
        DoMeleeAttackIfReady();
    }

    void OnUnitRelocation(Unit* who) override
    {
        /// TODO: Fill this function
    }
    void DamageTaken(Unit* attacker, uint32& damage, DamageEffectType /*damageType*/, SpellInfo const* /*spellInfo = nullptr*/) override
    {
        /// TODO: Fill this function
    }

    TaskScheduler scheduler;
    EventMap events;
};

// ID - 363754 Activate
class spell_activate_363754 : public SpellScript
{
    PrepareSpellScript(spell_activate_363754);

    void HandleAfterCast()
    {
        auto caster = GetCaster();
        if (!caster)
            return;

        if (auto chicken = caster->FindNearestCreature(705013, 50.0f))
        {
            if (chicken->AI())
                chicken->AI()->DoAction(1);
        }
    }

    void Register() override
    {
        AfterCast += SpellCastFn(spell_activate_363754::HandleAfterCast);
    }
};

// ID - 259463 T-Rex Explode
class spell_t_rex_explode_259463 : public SpellScript
{
    PrepareSpellScript(spell_t_rex_explode_259463);

    void HandleAfterCast()
    {
        auto caster = GetCaster();
        if (!caster)
            return;

        if (auto siege1 = caster->FindNearestCreatureBySpawnId(1054918, 50.0f))
            siege1->KillSelf();

        if (auto siege1 = caster->FindNearestCreatureBySpawnId(1054919, 50.0f))
            siege1->KillSelf();

        if (auto worker1 = caster->FindNearestCreatureBySpawnId(1054920, 50.0f))
        {
            worker1->CastSpell(worker1, 317961, true);
            worker1->KillSelf();
        }

        if (auto worker1 = caster->FindNearestCreatureBySpawnId(1054755, 50.0f))
        {
            worker1->CastSpell(worker1, 317961, true);
            worker1->KillSelf();
        }

        if (auto bm = caster->FindNearestCreatureBySpawnId(1054718, 50.0f))
        {
            bm->CastSpell(bm, 317961, true);
            bm->KillSelf();
        }

        if (auto bm = caster->FindNearestCreatureBySpawnId(1054717, 50.0f))
        {
            bm->CastSpell(bm, 317961, true);
            bm->KillSelf();
        }

        if (auto over = caster->FindNearestCreatureBySpawnId(1054914, 50.0f))
        {
            over->CastSpell(over, 317961, true);
            over->KillSelf();
        }

        if (auto elephant = caster->FindNearestCreatureBySpawnId(1054547, 50.0f))
        {
            if (elephant->AI())
                elephant->AI()->DoAction(1);
        }

        if (auto chicken = caster->FindNearestCreature(705013, 50.0f))
        {
            if (chicken->AI())
                chicken->AI()->DoAction(2);
        }
    }

    void Register() override
    {
        AfterCast += SpellCastFn(spell_t_rex_explode_259463::HandleAfterCast);
    }
};



struct instance_irondocks : public CustomInstanceScript
{
public:
    instance_irondocks(InstanceMap* map) : CustomInstanceScript(map)
    {
        ChestSpawn = { 6728.14f, -977.656f, 23.0463f, 6.16439f };
        Quad = { -0.0f, -0.0f, -0.0593638f, 0.998236f };
        EnemyForcesCriteriaTreeId = 301401;
    }

    void SummonChallengeGameObject(bool door) override
    {
        if (door)
        {
            if (auto go = instance->SummonGameObject(MYTHIC_DOOR_4, { 6746.76f, -546.786f, 4.92545f, 5.52298f }, { -0.0f, -0.0f, -0.712643f, 0.701527f }, 0))
            {
                go->SetGoState(GOState::GO_STATE_READY);
                go->SetFlag(GameObjectFlags::GO_FLAG_NOT_SELECTABLE);
            }
        }
    }

    void OnCompletedCriteriaTree(CriteriaTree const* /*tree*/) override
    {
        if (InstanceScenario* instanceScenario = instance->GetInstanceScenario())
        {
            if (auto tree2 = sCriteriaMgr->GetCriteriaTree(301400))
                instanceScenario->IsCompletedCriteriaTree(tree2, nullptr);
        }
    }

    void CreatureDiesForScript(Creature* creature, Unit* killer) override
    {
        CustomInstanceScript::CreatureDiesForScript(creature, killer);

        auto shadowMilitia = sFactionStore.LookupEntry(ShadowMilitiaRep);
        if (!shadowMilitia)
            return;

        bool isBoss = creature->IsDungeonBoss();
        uint32 repAmount = isBoss ? 500 : 25;

        instance->DoOnPlayers([repAmount, shadowMilitia, creature](Player* player)
        {
            player->GetReputationMgr().ModifyReputation(shadowMilitia, repAmount);

            if (creature->GetFaction() != 35)
                if (creature->IsDungeonBoss() || roll_chance_i(50))
                    player->ModifyCurrency(Gunpowder, creature->IsDungeonBoss() ? 100 : urand(1, 3));
        });
    }
};
// 800063 - npc_diamond_bar_800063
struct npc_diamond_bar_800063 : public ScriptedAI
{
public:
    npc_diamond_bar_800063(Creature* creature) : ScriptedAI(creature) { }

    bool OnGossipHello(Player* player) override
    {
        CloseGossipMenuFor(player);
        player->KilledMonsterCredit(me->GetEntry(), me->GetGUID());
        me->UpdateObjectVisibility();
        return true;
    }

    bool CanSeeOrDetect(WorldObject const* who) const override
    {
        if (who->IsPlayer())
        {
            auto player = who->ToPlayer();
            auto questStatus = player->GetQuestStatus(700103);
            if (questStatus == QUEST_STATUS_INCOMPLETE)
                return true;
        }

        return false;
    }
};


void AddSC_IronDocks()
{
    RegisterCreatureAI(npc_beastmaster_730609);
    RegisterCreatureAI(npc_flesh_eater_730610);
    RegisterCreatureAI(npc_skulloc_730612);
    RegisterCreatureAI(npc_parc_730617);
    RegisterCreatureAI(npc_iron_recruit_730619);
    RegisterCreatureAI(npc_iron_horde_captain_730620);
    RegisterCreatureAI(npc_iron_horde_general_730621);
    RegisterCreatureAI(npc_iron_horde_brute_730624);
    RegisterCreatureAI(npc_shulloc_730613);
    RegisterCreatureAI(npc_barrel_730608);
    RegisterCreatureAI(npc_war_elephant_705006);
    RegisterCreatureAI(npc_fel_destroyer_730604);
    RegisterCreatureAI(npc_iron_horde_warlock_730601);
    RegisterCreatureAI(npc_iron_hound_705011);
    RegisterCreatureAI(npc_felloc_705010);
    RegisterCreatureAI(npc_iron_dock_overseer_705009);
    RegisterCreatureAI(npc_marc_705008);
    RegisterCreatureAI(npc_iron_dock_worker_705007);
    RegisterCreatureAI(npc_iron_archer_705004);
    RegisterCreatureAI(npc_iron_horde_slaver_730603);
    RegisterCreatureAI(npc_slave_705012);
    RegisterCreatureAI(npc_explosive_chicken_705013);
    RegisterCreatureAI(npc_siegemaker_705014);
    RegisterCreatureAI(npc_muzgonk_705015);
    RegisterCreatureAI(npc_diamond_bar_800063);

    RegisterSpellScript(spell_activate_363754);
    RegisterSpellScript(spell_t_rex_explode_259463);

    RegisterInstanceScript(instance_irondocks, 1195);
}
// UPDATE creature_template set ScriptName = 'npc_beastmaster_730609' WHERE entry = 730609;
// UPDATE creature_template set ScriptName = 'npc_flesh_eater_730610' WHERE entry = 730610;
// UPDATE creature_template set ScriptName = 'npc_skulloc_730612' WHERE entry = 730612;
// UPDATE creature_template set ScriptName = 'npc_parc_730617' WHERE entry = 730617;
// UPDATE creature_template set ScriptName = 'npc_iron_recruit_730619' WHERE entry = 730619;
// UPDATE creature_template set ScriptName = 'npc_iron_horde_captain_730620' WHERE entry = 730620;
// UPDATE creature_template set ScriptName = 'npc_iron_horde_general_730621' WHERE entry = 730621;
// UPDATE creature_template set ScriptName = 'npc_iron_horde_brute_730624' WHERE entry = 730624;
// UPDATE creature_template set ScriptName = 'npc_shulloc_730613' WHERE entry = 730613;
// UPDATE creature_template set ScriptName = 'npc_barrel_730608' WHERE entry = 730608;
// UPDATE creature_template set ScriptName = 'npc_war_elephant_705006' WHERE entry = 705006;
// UPDATE creature_template set ScriptName = 'npc_fel_destroyer_730604' WHERE entry = 730604;
// UPDATE creature_template set ScriptName = 'npc_iron_horde_warlock_730601' WHERE entry = 730601;
// UPDATE creature_template set ScriptName = 'npc_iron_hound_705011' WHERE entry = 705011;
// UPDATE creature_template set ScriptName = 'npc_felloc_705010' WHERE entry = 705010;
// UPDATE creature_template set ScriptName = 'npc_iron_dock_overseer_705009' WHERE entry = 705009;
// UPDATE creature_template set ScriptName = 'npc_marc_705008' WHERE entry = 705008;
// UPDATE creature_template set ScriptName = 'npc_iron_dock_worker_705007' WHERE entry = 705007;
// UPDATE creature_template set ScriptName = 'npc_iron_archer_705004' WHERE entry = 705004;
// UPDATE creature_template set ScriptName = 'npc_iron_horde_slaver_730603' WHERE entry = 730603;
// UPDATE creature_template set ScriptName = 'npc_slave_705012' WHERE entry = 705012;
// UPDATE creature_template set ScriptName = 'npc_explosive_chicken_705013' WHERE entry = 705013;
// UPDATE creature_template set ScriptName = 'npc_siegemaker_705014' WHERE entry = 705014;
// UPDATE creature_template set ScriptName = 'npc_muzgonk_705015' WHERE entry = 705015;
