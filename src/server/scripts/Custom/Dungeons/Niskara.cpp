#include "ScriptMgr.h"
#include "../CustomInstanceScript.h"
#include "ScriptedCreature.h"
#include "MotionMaster.h"
#include "CellImpl.h"
#include "GridNotifiersImpl.h"
#include "GenericMovementGenerator.h"

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

     void OnUnitRelocation(Unit* who) override
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

     void JustEngagedWith(Unit* who) override
     {
         scheduler.CancelAll();
         Talk(2);
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

     bool m_DidText = false;

     void OnUnitRelocation(Unit* who) override
     {
         if (who->IsPlayer() && !me->IsEngaged() && !m_DidText)
         {
             auto dist = who->GetDistance2d(me);
             if (dist <= 40.0f)
             {
                 m_DidText = true;
                 Talk(0);
                 scheduler.Schedule(5s, [this](TaskContext context)
                 {
                     if (auto baby = me->FindNearestCreature(700501, 15.0f))
                         baby->AI()->Talk(0);

                     scheduler.Schedule(5s, [this](TaskContext context)
                     {
                        Talk(1);
                     });
                 });
             }
         }
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

     void OnUnitRelocation(Unit* who) override
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

     void OnUnitRelocation(Unit* who) override
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

     void OnUnitRelocation(Unit* who) override
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

     void OnUnitRelocation(Unit* who) override
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

     void OnUnitRelocation(Unit* who) override
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

     void JustEngagedWith(Unit* who)
     {
         Talk(1);
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


     void KilledUnit(Unit* who) override
     {
         if (who->IsPlayer())
             Talk(2);
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

                                 scheduler.Schedule(1s, [this](TaskContext context)
                                     {
                                         std::list<Unit*> units;
                                         me->GetFriendlyUnitListInRange(units, 50.0f, true);

                                         for (auto unit : units)
                                         {
                                             if (unit->IsCreature())
                                             {
                                                 auto creature = unit->ToCreature();
                                                 if (creature->GetSpawnId() == 1051659)
                                                 {
                                                     auto demonEnforcer = creature;

                                                     demonEnforcer->AI()->Talk(0);
                                                     if (auto demonSlave = demonEnforcer->FindNearestCreature(700502, 50.0f))
                                                     {
                                                         auto guid = demonSlave->GetGUID();
                                                         scheduler.Schedule(3s, [this, guid](TaskContext context)
                                                             {
                                                                 if (auto demonSlave = ObjectAccessor::GetCreature(*me, guid))
                                                                 {
                                                                     demonSlave->AI()->Talk(0);
                                                                     demonSlave->SetEmoteState(EMOTE_STATE_COWER);

                                                                     //static Position points[3] = {
                                                                     //    { 483.366577f, 1576.726807f, -123.664726f },
                                                                     //    { 492.72219f, 1570.001587f, -124.411804f },
                                                                     //    { 491.478912f, 1566.103516f, -124.174370f },
                                                                     //};
                                                                     //
                                                                     //auto result = demonSlave->GetMotionMaster()->MoveSmoothPath(1, points, 3, true);
                                                                     //result->callbackFunc = [this, demonSlave]()
                                                                     //{
                                                                     //    demonSlave->Say("My callback worked!", LANG_UNIVERSAL);
                                                                     //};
                                                                 }
                                                             });
                                                     }

                                                     break;
                                                 }
                                             }
                                         }
                                     });
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


     void KilledUnit(Unit* who) override
     {
         if (who->IsPlayer())
             Talk(1);
     }

     void OnUnitRelocation(Unit* who) override
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
                DoCast(creature, 241024, true); // Drain
        }

        void Reset() override
        {
            /// TODO: Fill this function
            if (auto creature = me->FindNearestCreature(700509, 50.0f)) // Slave
                DoCast(creature, 241024, true); // Drain
        }

        void JustEngagedWith(Unit* who) override
        {
            me->RemoveAurasDueToSpell(241024);
            Talk(0);
        }

        void JustDied(Unit* who) override
        {
            Talk(1);
        }

        void KilledUnit(Unit* who) override
        {
            if (who->IsPlayer())
                Talk(2);
        }

        uint32 prevTarget = 0;

        void UpdateAI(uint32 diff) override
        {
            scheduler.Update(diff);

            if (!UpdateVictim())
            {
                if (!me->IsEngaged() && !me->GetCurrentSpell(CurrentSpellTypes::CURRENT_CHANNELED_SPELL))
                {
                    if (prevTarget == 700509)
                        prevTarget = 700505;
                    else
                        prevTarget = 700509;

                    if (auto creature = me->FindNearestCreature(prevTarget, 50.0f)) // Slave
                    {
                        prevTarget = creature->GetEntry();
                        me->SetFacingToObject(creature);
                        DoCast(creature, 241024, true); // Drain
                    }
                }
                return;
            }

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
         me->SetReactState(REACT_PASSIVE);
         me->SetUnitFlag(UNIT_FLAG_NON_ATTACKABLE);
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

     void OnUnitRelocation(Unit* who) override
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

     void KilledUnit(Unit* who) override
     {
         if (who->IsPlayer())
            Talk(0);
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

     void OnUnitRelocation(Unit* who) override
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

     void OnUnitRelocation(Unit* who) override
     {
        /// TODO: Fill this function
     }

     TaskScheduler scheduler;
     EventMap events;
};

// 700512 - legion_portal_700512
struct npc_harvester_700513 : public ScriptedAI
{
public:
    npc_harvester_700513(Creature* creature) : ScriptedAI(creature) { }

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
        events.ScheduleEvent(1, 2s, 10s);
    }

    void UpdateAI(uint32 diff) override
    {
        scheduler.Update(diff);

        if (!UpdateVictim())
        {
            if (!me->IsEngaged() && !me->GetCurrentSpell(CurrentSpellTypes::CURRENT_CHANNELED_SPELL))
            {
                if (auto creature = me->FindNearestCreature(700515, 10.0f)) // Slave
                {
                    me->SetFacingToObject(creature);
                    DoCast(creature, 241024, true); // Drain
                }
            }

            return;
        }

        events.Update(diff);

        if (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
                case 1:
                    DoCastVictim(211491);
                    events.Repeat(10s, 20s);
                    break;
            }
        }
        DoMeleeAttackIfReady();
    }

    void OnUnitRelocation(Unit* who) override
    {
        /// TODO: Fill this function
    }

    TaskScheduler scheduler;
    EventMap events;
};

const Position watcherOfDeathPos[] = {
    { 277.907f, 1910.15f, -24.0141f, 0.546515f },
    { 287.476f, 1915.97f, -27.6328f, 0.546515f },
    { 297.073f, 1921.74f, -30.1178f, 0.543242f },
    { 296.989f, 1924.93f, -30.9588f, 1.65262f },
    { 295.569f, 1928.5f, -31.9165f, 1.97659f },
    { 291.525f, 1933.74f, -33.3113f, 2.23512f },
    { 286.527f, 1937.57f, -35.6996f, 2.41838f },
    { 279.949f, 1943.4f, -40.8263f, 2.60819f },
    { 272.402f, 1947.0f, -45.54f, 2.69982f },
    { 266.903f, 1949.27f, -48.2273f, 2.76527f },
    { 261.902f, 1950.87f, -49.9608f, 2.87653f },
};

struct npc_watcher_of_death_700515 : public ScriptedAI
{
public:
    npc_watcher_of_death_700515(Creature* creature) : ScriptedAI(creature) { }

    void InitializeAI()
    {
        if (me->GetSpawnId() == 1053038)
        {
            scheduler.Schedule(1s, [this](TaskContext context)
                {
                    auto path = me->GetMotionMaster()->MoveSmoothPath(1, watcherOfDeathPos, 11, true);
                    path->callbackFunc = [this]() {
                        scheduler.Schedule(250ms, [this](TaskContext context)
                            {
                                me->SetEmoteState(Emote::EMOTE_ONESHOT_READY1H);
                            });
                        };
                });
        }
    }

    void JustEngagedWith(Unit* who)
    {
        me->SetEmoteState(Emote::EMOTE_STATE_NONE);
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
            case 1:
                DoCastVictim(211491);
                events.Repeat(10s, 20s);
                break;
            }
        }
        DoMeleeAttackIfReady();
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
    RegisterCreatureAI(npc_harvester_700513);
    RegisterCreatureAI(npc_watcher_of_death_700515);
}
