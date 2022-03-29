#include "ScriptMgr.h"
#include "../CustomInstanceScript.h"
#include "ScriptedCreature.h"
#include "MotionMaster.h"
#include "CellImpl.h"
#include "GridNotifiersImpl.h"

struct instance_niskara : public CustomInstanceScript
{
    public:
        instance_niskara(InstanceMap* map) : CustomInstanceScript(map)
        {
        }

        void OnPlayerEnter(Player* player) override
        {
            player->CastSpell(player, 352467, true); // visual
            if (!m_FirstPlayerEntered)
            {
                m_FirstPlayerEntered = true;
                instance->SummonCreature(700499, { 230.551f, 1949.22f, -55.9595f, 0.448333f });
            }
        }

        bool m_FirstPlayerEntered = false;
};

struct npc_prophet_velen_700499 : public ScriptedAI
{
    public:
        npc_prophet_velen_700499(Creature* creature) : ScriptedAI(creature) { }

        void InitializeAI() override
        {
            scheduler.Schedule(100ms, [this](TaskContext context)
                {
                    DoCastSelf(367044, true);
                });

                scheduler.Schedule(1200ms, [this](TaskContext context)
                    {
                        me->GetMotionMaster()->MovePoint(1, { 245.263947f, 1966.496460f, -54.270882f, 4.329511f });
                        scheduler.Schedule(100ms, [this](TaskContext context)
                            {
                                Talk(0);
                            });
                    });
        }

        void MovementInform(uint32 type, uint32 point) override
        {
            scheduler.Schedule(100ms, [this](TaskContext context)
                {
                    me->SetFacingTo(4.054619f);

                    scheduler.Schedule(100ms, [this](TaskContext context)
                        {
                            Talk(1);

                            scheduler.Schedule(5s, [this](TaskContext context)
                                {
                                    Talk(2);

                                    scheduler.Schedule(5s, [this](TaskContext context)
                                        {
                                            DoCast(286210);

                                            scheduler.Schedule(100ms, [this](TaskContext context)
                                                {
                                                    me->DespawnOrUnsummon();
                                                });
                                        });
                                });
                        });
                });
        }

        void UpdateAI(uint32 diff) override
        {
            scheduler.Update(diff);
        }

        TaskScheduler scheduler;
};

// 700099 - bob_700099
struct npc_bob_700099 : public ScriptedAI
{
   public:
       npc_bob_700099(Creature* creature) : ScriptedAI(creature) { }

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

     TaskScheduler scheduler;
     EventMap events;
};

// 700500 - nazgrul_700500
struct npc_nazgrul_700500 : public ScriptedAI
{
   public:
       npc_nazgrul_700500(Creature* creature) : ScriptedAI(creature) { }

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

     TaskScheduler scheduler;
     EventMap events;
};

// 700501 - demonic_priest_700501
struct npc_demonic_priest_700501 : public ScriptedAI
{
   public:
       npc_demonic_priest_700501(Creature* creature) : ScriptedAI(creature) { }

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

     TaskScheduler scheduler;
     EventMap events;
};

// 700502 - demon_slave_700502
struct npc_demon_slave_700502 : public ScriptedAI
{
   public:
       npc_demon_slave_700502(Creature* creature) : ScriptedAI(creature) { }

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

     TaskScheduler scheduler;
     EventMap events;
};

// 700503 - demon_enforcer_700503
struct npc_demon_enforcer_700503 : public ScriptedAI
{
   public:
       npc_demon_enforcer_700503(Creature* creature) : ScriptedAI(creature) { }

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

     TaskScheduler scheduler;
     EventMap events;
};

// 700504 - fel_hunter_700504
struct npc_fel_hunter_700504 : public ScriptedAI
{
   public:
       npc_fel_hunter_700504(Creature* creature) : ScriptedAI(creature) { }

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

     TaskScheduler scheduler;
     EventMap events;
};

// 700505 - fading_demon_700505
struct npc_fading_demon_700505 : public ScriptedAI
{
   public:
       npc_fading_demon_700505(Creature* creature) : ScriptedAI(creature) { }

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

     TaskScheduler scheduler;
     EventMap events;
};

// 700506 - oglaz_700506
struct npc_oglaz_700506 : public ScriptedAI
{
   public:
       npc_oglaz_700506(Creature* creature) : ScriptedAI(creature) { }

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
        // if (!m_Talked)
        // {
        //     Player* player = nullptr;
        //
        //     Trinity::PlayerAtMinimumRangeAway check(me, 100.0f);
        //     Trinity::PlayerSearcher<Trinity::PlayerAtMinimumRangeAway> searcher(me, player, check);
        //     Cell::VisitWorldObjects(me, searcher, 100.0f);
        //
        // }

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
         if (who->IsPlayer() && !m_Talked && who->GetDistance(me) <= 205.0f)
         {
             m_Talked = true;
             Talk(0);
             scheduler.Schedule(1s, [this](TaskContext context)
                 {
                     if (auto demonSlave = me->FindNearestCreature(700502, 50.0f))
                     {
                         demonSlave->GetMotionMaster()->MoveJumpWithGravity(*me, 15.0f, 55.0f);

                         scheduler.Schedule(1s, [this](TaskContext context)
                             {
                                 if (auto demonSlave = me->FindNearestCreature(700502, 50.0f))
                                 {
                                     demonSlave->CastSpell(demonSlave, 318123);
                                 }
                             });
                     }
                 });
         }
     }

     bool m_Talked = false;
     TaskScheduler scheduler;
     EventMap events;
};

// 700507 - jazgolluth_700507
struct npc_jazgolluth_700507 : public ScriptedAI
{
   public:
       npc_jazgolluth_700507(Creature* creature) : ScriptedAI(creature) { }

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
         if (who->IsPlayer() && !m_Talked && who->GetDistance(me) <= 25.0f)
         {
             m_Talked = true;
             Talk(0);
         }
     }

     bool m_Talked = false;
     TaskScheduler scheduler;
     EventMap events;
};

// 700508 - annaxin_700508
struct npc_annaxin_700508 : public ScriptedAI
{
    public:
        npc_annaxin_700508(Creature* creature) : ScriptedAI(creature) { }

        void InitializeAI() override
        {
            /// TODO: Fill this function
            if (auto creature = me->FindNearestCreature(700509, 50.0f)) // Slave
                DoCast(creature, 328785, true); // Drain
        }

        void Reset() override
        {
            /// TODO: Fill this function
            if (auto creature = me->FindNearestCreature(700509, 50.0f)) // Slave
                DoCast(creature, 328785, true); // Drain
        }

        void JustEngagedWith(Unit* who) override
        {
            me->RemoveAurasDueToSpell(328785);
            Talk(0);
        }

        void JustDied(Unit* who) override
        {
            Talk(1);
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

        TaskScheduler scheduler;
        EventMap events;
};

// 700509 - skyhold_slave_700509
struct npc_skyhold_slave_700509 : public ScriptedAI
{
   public:
       npc_skyhold_slave_700509(Creature* creature) : ScriptedAI(creature) { }

     void InitializeAI() override
     {
        /// TODO: Fill this function
         me->SetEmoteState(Emote::EMOTE_STATE_DROWNED);
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

     TaskScheduler scheduler;
     EventMap events;
};

// 700510 - zorith_700510
struct npc_zorith_700510 : public ScriptedAI
{
   public:
       npc_zorith_700510(Creature* creature) : ScriptedAI(creature) { }

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

     TaskScheduler scheduler;
     EventMap events;
};

// 700511 - xolmir_700511
struct npc_xolmir_700511 : public ScriptedAI
{
   public:
       npc_xolmir_700511(Creature* creature) : ScriptedAI(creature) { }

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

     TaskScheduler scheduler;
     EventMap events;
};

// 700512 - legion_portal_700512
struct npc_legion_portal_700512 : public ScriptedAI
{
   public:
       npc_legion_portal_700512(Creature* creature) : ScriptedAI(creature) { }

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

     TaskScheduler scheduler;
     EventMap events;
};

void AddSC_Niskara()
{
    RegisterInstanceScript(instance_niskara, 1604);
    RegisterCreatureAI(npc_prophet_velen_700499);

    RegisterCreatureAI(npc_bob_700099);
    RegisterCreatureAI(npc_nazgrul_700500);
    RegisterCreatureAI(npc_demonic_priest_700501);
    RegisterCreatureAI(npc_demon_slave_700502);
    RegisterCreatureAI(npc_demon_enforcer_700503);
    RegisterCreatureAI(npc_fel_hunter_700504);
    RegisterCreatureAI(npc_fading_demon_700505);
    RegisterCreatureAI(npc_oglaz_700506);
    RegisterCreatureAI(npc_jazgolluth_700507);
    RegisterCreatureAI(npc_annaxin_700508);
    RegisterCreatureAI(npc_skyhold_slave_700509);
    RegisterCreatureAI(npc_zorith_700510);
    RegisterCreatureAI(npc_xolmir_700511);
    RegisterCreatureAI(npc_legion_portal_700512);
}
