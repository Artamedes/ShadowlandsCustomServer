#include "ScriptMgr.h"
#include "Player.h"
#include "Creature.h"
#include "ScriptedCreature.h"

// 700011 - npc_oogway_700011
struct npc_oogway_700011 : public ScriptedAI
{
public:
    npc_oogway_700011(Creature* creature) : ScriptedAI(creature) { }

    void InitializeAI() override
    {
        /// TODO: Fill this function
    }

    void Reset() override
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

    void MoveInLineOfSight(Unit* who) override
    {
        /// TODO: Fill this function
    }
    void OnSpellClick(Unit* clicker, bool spellClickHandled) override
    {
        /// TODO: Fill this function
    }

    TaskScheduler scheduler;
    EventMap events;
};

// 700721 - npc_ernoch_700721
struct npc_ernoch_700721 : public ScriptedAI
{
public:
    npc_ernoch_700721(Creature* creature) : ScriptedAI(creature) { }

    void InitializeAI() override
    {
        /// TODO: Fill this function
    }

    void Reset() override
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

    void MoveInLineOfSight(Unit* who) override
    {
        /// TODO: Fill this function
    }
    void OnSpellClick(Unit* clicker, bool spellClickHandled) override
    {
        /// TODO: Fill this function
    }

    TaskScheduler scheduler;
    EventMap events;
};

// 700722 - npc_kairos_700722
struct npc_kairos_700722 : public ScriptedAI
{
public:
    npc_kairos_700722(Creature* creature) : ScriptedAI(creature) { }

    void InitializeAI() override
    {
        /// TODO: Fill this function
    }

    void Reset() override
    {
        events.Reset();
    }

    void JustEngagedWith(Unit* who) override
    {
        events.Reset();
        events.ScheduleEvent(1, 5s, 10s);
        events.ScheduleEvent(2, 5s, 10s);
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
                    DoCast(365834); // Fear of the Unknowwn
                    events.Repeat(10s, 20s);
                    break;
                case 2:
                    DoCastVictim(317959, true); // Dark Lash
                    events.Repeat(2s, 5s);
                    break;
            }
        }
        DoMeleeAttackIfReady();
    }

    bool didIntro = false;
    void MoveInLineOfSight(Unit* who) override
    {
        if (didIntro)
            return;

        if (who->IsPlayer() && who->GetDistance2d(me) <= 20.0f)
        {
            me->SetDisplayId(80096);
            didIntro = true;
        }
    }
    void OnSpellClick(Unit* clicker, bool spellClickHandled) override
    {
        /// TODO: Fill this function
    }

    TaskScheduler scheduler;
    EventMap events;
};

// 700723 - npc_allmus_700723
struct npc_allmus_700723 : public ScriptedAI
{
public:
    npc_allmus_700723(Creature* creature) : ScriptedAI(creature) { }

    void InitializeAI() override
    {
        /// TODO: Fill this function
    }

    void Reset() override
    {
        events.Reset();
    }

    void JustEngagedWith(Unit* who) override
    {
        Talk(0);
        events.Reset();
        events.ScheduleEvent(1, 2s, 10s);
        events.ScheduleEvent(2, 5s, 30s);
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
        DoMeleeAttackIfReady();
    }

    void MoveInLineOfSight(Unit* who) override
    {
        /// TODO: Fill this function
    }
    void OnSpellClick(Unit* clicker, bool spellClickHandled) override
    {
        /// TODO: Fill this function
    }

    TaskScheduler scheduler;
    EventMap events;
};

// 700724 - npc_torzas_700724
struct npc_torzas_700724 : public ScriptedAI
{
public:
    npc_torzas_700724(Creature* creature) : ScriptedAI(creature) { }

    void InitializeAI() override
    {
        /// TODO: Fill this function
    }

    void Reset() override
    {
        /// TODO: Fill this function
    }

    void JustEngagedWith(Unit* who) override
    {
        events.Reset();
        events.ScheduleEvent(1, 5s, 15s);
        events.ScheduleEvent(2, 5s, 15s);
        events.ScheduleEvent(3, 5s, 15s);
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
                    DoCastVictim(360908); // Feeding Time
                    events.Repeat(10s, 30s);
                    break;
                case 2:
                    DoCastVictim(347087); // Ravage
                    events.Repeat(10s, 30s);
                    break;
                case 3:
                    DoCastVictim(337785); // Cleanse pain
                    events.Repeat(10s, 30s);
                    break;
            }
        }
        DoMeleeAttackIfReady();
    }

    void MoveInLineOfSight(Unit* who) override
    {
        /// TODO: Fill this function
    }
    void OnSpellClick(Unit* clicker, bool spellClickHandled) override
    {
        /// TODO: Fill this function
    }

    TaskScheduler scheduler;
    EventMap events;
};

// 700725 - npc_mawsworn_warden_700725
struct npc_mawsworn_warden_700725 : public ScriptedAI
{
public:
    npc_mawsworn_warden_700725(Creature* creature) : ScriptedAI(creature) { }

    void InitializeAI() override
    {
        /// TODO: Fill this function
    }

    void Reset() override
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

    void MoveInLineOfSight(Unit* who) override
    {
        /// TODO: Fill this function
    }
    void OnSpellClick(Unit* clicker, bool spellClickHandled) override
    {
        /// TODO: Fill this function
    }

    TaskScheduler scheduler;
    EventMap events;
};

// 700726 - npc_watcher_of_death_700726
struct npc_watcher_of_death_700726 : public ScriptedAI
{
public:
    npc_watcher_of_death_700726(Creature* creature) : ScriptedAI(creature) { }

    void InitializeAI() override
    {
        /// TODO: Fill this function
    }

    void Reset() override
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

    void MoveInLineOfSight(Unit* who) override
    {
        /// TODO: Fill this function
    }
    void OnSpellClick(Unit* clicker, bool spellClickHandled) override
    {
        /// TODO: Fill this function
    }

    TaskScheduler scheduler;
    EventMap events;
};


void AddSC_LightDungeon3()
{
   RegisterCreatureAI(npc_ernoch_700721);
   RegisterCreatureAI(npc_kairos_700722);
   RegisterCreatureAI(npc_allmus_700723);
   RegisterCreatureAI(npc_torzas_700724);
   RegisterCreatureAI(npc_mawsworn_warden_700725);
   RegisterCreatureAI(npc_watcher_of_death_700726);
}
