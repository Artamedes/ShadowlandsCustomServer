#include "ScriptMgr.h"
#include "Creature.h"
#include "ScriptedCreature.h"
#include "GameTime.h"
#include "../CustomInstanceScript.h"

struct npc_demon_priest_700408 : public ScriptedAI
{
    public:
        npc_demon_priest_700408(Creature* creature) : ScriptedAI(creature) { }

        void Reset() override
        {
            events.Reset();

            if (me->GetEntry() == 700408)
            {
                scheduler.Schedule(1s, [this](TaskContext conext)
                    {
                        if (auto voidWalker = me->FindNearestCreature(700403, 30.0f))
                        {
                            DoCast(voidWalker, 335247);
                        }
                    });
            }
        }

        void JustEngagedWith(Unit* unit)
        {
            events.Reset();
            me->RemoveAurasDueToSpell(335247);
            events.ScheduleEvent(1, 5s, 7s);
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
                    case 1:
                        DoCastVictim(332707);
                        events.Repeat(10s, 20s);
                        break;
                }
            }


            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            DoCastVictim(266146);
            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

           // DoMeleeAttackIfReady();
        }

    TaskScheduler scheduler;
    EventMap events;
};

struct npc_void_walker_700403 : public ScriptedAI
{
    public:
        npc_void_walker_700403(Creature* creature) : ScriptedAI(creature) { }

        void Reset() override
        {
            events.Reset();
        }

        void JustEngagedWith(Unit* who) override
        {
            DoCastSelf(354757);
            events.ScheduleEvent(1, 2s, 10s);
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
                    case 1:
                        DoCastVictim(353769);
                        events.Repeat(10s, 20s);
                        break;
                }
            }

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;
            DoCastVictim(237890);
            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;
           // DoMeleeAttackIfReady();
        }

        EventMap events;
};



struct npc_void_walker_700410 : public ScriptedAI
{
    public:
        npc_void_walker_700410(Creature* creature) : ScriptedAI(creature) { }

        void Reset() override
        {
            events.Reset();
        }

        void JustEngagedWith(Unit* who) override
        {
            events.ScheduleEvent(1, 2s, 10s);
            events.ScheduleEvent(2, 2s, 10s);
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
                    case 1:
                        DoCastVictim(353769);
                        events.Repeat(10s, 20s);
                        break;
                    case 2:
                        DoCastVictim(355212);
                        events.Repeat(10s, 20s);
                        break;
                }
            }

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;
            DoCastVictim(237890);
            //DoMeleeAttackIfReady();
        }

        EventMap events;
};


struct npc_void_hound_700407 : public ScriptedAI
{
    public:
        npc_void_hound_700407(Creature* creature) : ScriptedAI(creature) { }

        void Reset() override
        {
            events.Reset();
        }

        void JustEngagedWith(Unit* who) override
        {
            events.ScheduleEvent(1, 2s, 10s);
            events.ScheduleEvent(2, 2s, 10s);
        }

        void UpdateAI(uint32 diff) override
        {
            if (!UpdateVictim())
                return;
            events.Update(diff);
            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            if (!me->IsWithinMeleeRange(me->GetVictim()))
            {
                auto now = GameTime::Now();

                if (now >= dashTime)
                {
                    dashTime = now + Seconds(8);
                    DoCastVictim(342963); // Dash
                }

                return;
            }
            if (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case 1: // Rake
                        DoCastVictim(319628);
                        events.Repeat(10s, 20s);
                        break;
                    case 2: // Triple Bite
                        DoCastVictim(340289);
                        events.Repeat(10s, 20s);
                        break;
                }
            }

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;
            DoMeleeAttackIfReady();
        }

        EventMap events;
        TimePoint dashTime;
};


struct npc_derza_700402 : public ScriptedAI
{
    public:
        npc_derza_700402(Creature* creature) : ScriptedAI(creature) { }

        enum Talks
        {
            FirstEnter,
            BossesDefeated,
            WatcherDefeated,
            TalkEngaged,
            TalkDied,
        };

        void InitializeAI() override
        {
            me->SetReactState(REACT_PASSIVE);
            me->AddUnitFlag(UNIT_FLAG_NON_ATTACKABLE);
            me->AddUnitFlag(UNIT_FLAG_IMMUNE_TO_PC);
            DoCast(345355); // Channel
        }

        void Reset() override
        {
            events.Reset();
        }

        void JustEngagedWith(Unit* who) override
        {
            Talk(TalkEngaged);
            events.ScheduleEvent(1, 2s, 10s);
            events.ScheduleEvent(2, 5s, 30s);
        }

        void JustDied(Unit* who) override
        {
            Talk(TalkDied);
        }

        bool m_Talked = false;

        void OnUnitRelocation(Unit* unit) override
        {
            if (!m_Talked && unit->IsPlayer())
            {
                auto dist = unit->GetDistance2d(me);
                // unit->Say("Distance: " + std::to_string(dist), LANG_UNIVERSAL);
                if (dist <= 150.0f)
                {
                    Talk(FirstEnter);
                    m_Talked = true;
                }
            }
        }

        void DoAction(int32 action) override
        {
            if (action == 1)
            {
                Talk(BossesDefeated);
                DoSummon(700411, {1400.830811f, 1343.949463f, 177.933823f}, 0s, TempSummonType::TEMPSUMMON_MANUAL_DESPAWN);
            }
            else if (action == 2)
            {
                Talk(WatcherDefeated);
                me->SetReactState(REACT_AGGRESSIVE);
                me->RemoveUnitFlag(UNIT_FLAG_NON_ATTACKABLE);
                me->RemoveUnitFlag(UNIT_FLAG_IMMUNE_TO_PC);
            }
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
                    case 1: // Drain soul
                        DoCastVictim(242938);
                        events.Repeat(10s, 20s);
                        break;
                    case 2: // Cone of death
                        DoCast(364643);
                        events.Repeat(15s, 30s);
                        break;
                }
            }

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;
            DoCastVictim(251028);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;
           // DoMeleeAttackIfReady();
        }

        EventMap events;
};

struct npc_inquisitor_brute_700406 : public ScriptedAI
{
    public:
        npc_inquisitor_brute_700406(Creature* creature) : ScriptedAI(creature) { }

        void Reset() override
        {
            events.Reset();
        }

        void JustEngagedWith(Unit* who) override
        {
            events.ScheduleEvent(1, 2s, 10s);
            events.ScheduleEvent(3, Minutes(1));
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
                    case 1: // Slam
                        DoCastVictim(278222);
                        events.Repeat(20s, 30s);
                        break;
                    case 3:
                        DoCast(316133);
                        break;
                }
            }

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;
            DoMeleeAttackIfReady();
        }

        EventMap events;
};


struct npc_mevra_700401 : public ScriptedAI
{
    public:
        npc_mevra_700401(Creature* creature) : ScriptedAI(creature) { }


        void Reset() override
        {
            events.Reset();
        }

        void JustEngagedWith(Unit* who) override
        {
            events.ScheduleEvent(1, 2s, 10s);
            events.ScheduleEvent(2, 5s, 30s);
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
                    case 1: // Drain life
                        DoCastVictim(345116);
                        events.Repeat(10s, 20s);
                        break;
                    case 2: // Cone of death
                        DoCast(360861);
                        events.Repeat(15s, 30s);
                        break;
                }
            }

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;
            
            DoMeleeAttackIfReady();
        }

        EventMap events;
};

struct npc_demon_guy_700400 : public ScriptedAI
{
    public:
        npc_demon_guy_700400(Creature* creature) : ScriptedAI(creature) { }


        void Reset() override
        {
            events.Reset();
        }

        void JustEngagedWith(Unit* who) override
        {
            events.ScheduleEvent(1, 2s, 10s);
            events.ScheduleEvent(2, 5s, 30s);
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
                    case 1: // Charged Slam
                        DoCastVictim(368465);
                        events.Repeat(10s, 20s);
                        break;
                    case 2: // Teleport
                        DoCast(342317);
                        events.Repeat(15s, 30s);
                        break;
                }
            }

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;
            
            DoMeleeAttackIfReady();
        }

        EventMap events;
};

class instance_netherlight_temple : public InstanceMapScript
{
    public:
        instance_netherlight_temple() : InstanceMapScript("instance_netherlight_temple", 2472) { }

        struct instance_netherlight_temple_InstanceMapScript : public CustomInstanceScript
        {
            public:
                instance_netherlight_temple_InstanceMapScript(InstanceMap* map) : CustomInstanceScript(map)
                {
                }

                void OnCreatureCreate(Creature* creature) override
                {
                    switch (creature->GetEntry())
                    {
                        case 700402:
                            DerzaGuid = creature->GetGUID();
                            break;
                        case 700412:
                            VelenGuid = creature->GetGUID();
                            break;
                    }
                }

                void OnUnitDeath(Unit* unit) override
                {
                    if (!unit->IsCreature())
                        return;

                    switch (unit->GetEntry())
                    {
                        case 700401:
                        case 700400:
                            if (RequiredBossKills > 0)
                            {
                                --RequiredBossKills;
                                if (RequiredBossKills == 0)
                                {
                                    if (auto derza = instance->GetCreature(DerzaGuid))
                                        derza->AI()->DoAction(1);
                                }
                            }
                            break;
                        case 700411: // Watcher of death
                            if (auto derza = instance->GetCreature(DerzaGuid))
                                derza->AI()->DoAction(2);
                            break;
                        case 700402: // derza
                            if (auto velen = instance->GetCreature(VelenGuid))
                                velen->AI()->DoAction(1);
                            break;
                    }
                }

                uint32 RequiredBossKills = 2;
                ObjectGuid DerzaGuid;
                ObjectGuid VelenGuid;
        };

        InstanceScript* GetInstanceScript(InstanceMap* map) const override
        {
            return new instance_netherlight_temple_InstanceMapScript(map);
        }
};

struct npc_watcher_of_death : public ScriptedAI
{
    public:
        npc_watcher_of_death(Creature* creature) : ScriptedAI(creature) { }

        void InitializeAI()
        {
            me->SetObjectScale(3.0f);
            me->SetDisplayId(101302);
            me->SetReactState(REACT_PASSIVE);
            me->AddUnitFlag(UNIT_FLAG_NON_ATTACKABLE);
            me->AddUnitFlag(UNIT_FLAG_UNINTERACTIBLE);
            scheduler.Schedule(100ms, [this](TaskContext context)
                {
                    me->SetFacingTo(3.118690f);
                });
            scheduler.Schedule(5s, [this](TaskContext context)
            {
                me->DeMorph();
                me->SetReactState(REACT_AGGRESSIVE);
                me->RemoveUnitFlag(UNIT_FLAG_NON_ATTACKABLE);
                me->RemoveUnitFlag(UNIT_FLAG_UNINTERACTIBLE);
            });
        }

        void Reset()
        {

        }

        void UpdateAI(uint32 diff) override
        {
            scheduler.Update(diff);

            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }

        TaskScheduler scheduler;
};

struct npc_prophet_velen_700412 : public ScriptedAI
{
    public:
        npc_prophet_velen_700412(Creature* creature) : ScriptedAI(creature) { }

        void Reset() override
        {

        }

        void DoAction(int32 action) override
        {
            if (action == 1)
            {
                scheduler.Schedule(1s, [this](TaskContext context)
                {
                    Talk(0);
                });

                me->RemoveNpcFlag(NPCFlags::UNIT_NPC_FLAG_GOSSIP);
                me->RemoveNpcFlag(NPCFlags::UNIT_NPC_FLAG_QUESTGIVER);
                me->GetMotionMaster()->MovePoint(1, { 1385.790894f, 1344.201538f, 176.737656f });
            }
        }

        void MovementInform(uint32 type, uint32 id) override
        {
            if (id == 1)
            {
                me->AddNpcFlag(NPCFlags::UNIT_NPC_FLAG_GOSSIP);
                me->AddNpcFlag(NPCFlags::UNIT_NPC_FLAG_QUESTGIVER);

                scheduler.Schedule(1s, [this](TaskContext context)
                {
                    Talk(1);
                    DoCast(365837);
                    scheduler.Schedule(5s, [this](TaskContext context)
                    {
                        Talk(2);
                        me->RemoveAurasDueToSpell(365837);
                        DoSummon(700415, {1400.830811f, 1343.949463f, 177.933823f}, 0s, TempSummonType::TEMPSUMMON_MANUAL_DESPAWN);
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

struct npc_mawswarn_portal_700415 : public ScriptedAI
{
    public:
        npc_mawswarn_portal_700415(Creature* creature) : ScriptedAI(creature) { }

        void InitializeAI() override
        {
            me->AddUnitFlag(UnitFlags::UNIT_FLAG_UNINTERACTIBLE);
        }

        void UpdateAI(uint32 diff) override
        {
            std::list<Unit*> players;
            me->GetFriendlyUnitListInRange(players, 2.0f, true);
            players.remove_if([&](Unit* unit)
            {
                return !unit->IsPlayer() || unit->IsInCombat() || unit->ToPlayer()->IsBeingTeleported() || m_PlayersToTele.count(unit->GetGUID());
            });

            auto now = GameTime::Now();

            for (auto player : players)
            {
                player->CastSpell(player, 141480, true);
                player->CastSpell(player, 367044, true);
                m_PlayersToTele[player->GetGUID()] = now + Milliseconds(800);
            }

            for (auto it = m_PlayersToTele.cbegin(); it != m_PlayersToTele.cend();)
            {
                auto player = ObjectAccessor::GetPlayer(*me, it->first);
                if (!player || !player->GetSession() || player->IsBeingTeleported())
                    continue;

                if (now >= it->second)
                {
                    player->RemoveAurasDueToSpell(141480);
                    GameTele const* tele = sObjectMgr->GetGameTele(1793);
                    player->KilledMonsterCredit(me->GetEntry(), me->GetGUID());
                    if (tele)
                        player->TeleportTo(tele->mapId, tele->position_x, tele->position_y, tele->position_z, tele->orientation);

                    m_PlayersToTele.erase(it++);
                }
                else
                {
                    ++it;
                }
            }
        }

        std::unordered_map<ObjectGuid, TimePoint> m_PlayersToTele;
};

void AddSC_NetherlightTemple()
{
    RegisterCreatureAI(npc_demon_priest_700408);
    RegisterCreatureAI(npc_void_walker_700403);
    RegisterCreatureAI(npc_void_walker_700410);
    RegisterCreatureAI(npc_void_hound_700407);
    RegisterCreatureAI(npc_derza_700402);
    RegisterCreatureAI(npc_inquisitor_brute_700406);
    RegisterCreatureAI(npc_mevra_700401);
    RegisterCreatureAI(npc_demon_guy_700400);
    RegisterCreatureAI(npc_watcher_of_death);
    RegisterCreatureAI(npc_prophet_velen_700412);
    RegisterCreatureAI(npc_mawswarn_portal_700415);
    new instance_netherlight_temple();
}
