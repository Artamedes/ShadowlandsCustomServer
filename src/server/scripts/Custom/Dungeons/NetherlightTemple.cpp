#include "ScriptMgr.h"
#include "Creature.h"
#include "ScriptedCreature.h"
#include "GameTime.h"

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

            DoCast(290097);
            DoMeleeAttackIfReady();
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
            DoCast(354757);
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
            DoCast(237890);
            DoMeleeAttackIfReady();
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
            DoCast(237890);
            DoMeleeAttackIfReady();
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
            events.ScheduleEvent(1, 2s, 10s);
            events.ScheduleEvent(2, 5s, 30s);
        }

        bool m_Talked = false;

        void MoveInLineOfSight(Unit* unit) override
        {
            if (unit->IsPlayer() && !m_Talked && unit->GetDistance(me) <= 120.0f)
            {
                Talk(FirstEnter);
                m_Talked = true;
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
            DoCast(251028);

            DoMeleeAttackIfReady();
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
}
