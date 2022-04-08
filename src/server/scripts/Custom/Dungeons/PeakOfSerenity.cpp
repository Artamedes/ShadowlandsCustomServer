#include "ScriptMgr.h"
#include "Player.h"
#include "Creature.h"
#include "ScriptedCreature.h"
// 700700 - npc_avatar_of_the_light_700700
struct npc_avatar_of_the_light_700700 : public ScriptedAI
{
public:
    npc_avatar_of_the_light_700700(Creature* creature) : ScriptedAI(creature) { }

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
    void OnSpellClick(Unit* clicker, bool spellClickHandled) override
    {
        /// TODO: Fill this function
    }

    TaskScheduler scheduler;
    EventMap events;
};

// 700701 - npc_weapon_of_light_700701
struct npc_weapon_of_light_700701 : public ScriptedAI
{
public:
    npc_weapon_of_light_700701(Creature* creature) : ScriptedAI(creature) { }

    void InitializeAI() override
    {
        /// TODO: Fill this function'
        me->SetUnitFlag2(UNIT_FLAG2_UNTARGETABLE_BY_CLIENT);
        me->SetUnitFlag2(UNIT_FLAG2_UNINTERACTIBLE_IF_HOSTILE);
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

    bool done = false;

    void OnSpellClick(Unit* clicker, bool spellClickHandled) override
    {
        if (!done)
        {
            done = true;
            me->DespawnOrUnsummon(2500ms);
            scheduler.Schedule(100ms, [this](TaskContext)
                {
                    DoCastSelf(367667);
                });
        }
    }

    TaskScheduler scheduler;
    EventMap events;
};

// 700702 - npc_disciple_of_light_700702
struct npc_disciple_of_light_700702 : public ScriptedAI
{
public:
    npc_disciple_of_light_700702(Creature* creature) : ScriptedAI(creature) { }

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
    void OnSpellClick(Unit* clicker, bool spellClickHandled) override
    {
        /// TODO: Fill this function
    }

    TaskScheduler scheduler;
    EventMap events;
};

// 700703 - npc_angelic_warrior_700703
struct npc_angelic_warrior_700703 : public ScriptedAI
{
public:
    npc_angelic_warrior_700703(Creature* creature) : ScriptedAI(creature) { }

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
    void OnSpellClick(Unit* clicker, bool spellClickHandled) override
    {
        /// TODO: Fill this function
    }

    TaskScheduler scheduler;
    EventMap events;
};

// 700705 - npc_betzalel_700705
struct npc_betzalel_700705 : public ScriptedAI
{
public:
    npc_betzalel_700705(Creature* creature) : ScriptedAI(creature) { }

    void InitializeAI() override
    {
        /// TODO: Fill this function
        //scheduler.Schedule(1s, [this](TaskContext context)
        //    {
        //        if (auto beacon = me->FindNearestCreature(700709, 50.0f))
        //            DoCast(beacon, 319728, true);
        //    });

       // if (auto channel = me->GetCurrentSpell(CurrentSpellTypes::CURRENT_CHANNELED_SPELL))
    }

    void Reset() override
    {
        phase = false;
        isPhasing = false;
        /// TODO: Fill this function
       // scheduler.Schedule(1s, [this](TaskContext context)
       //     {
       //         if (auto beacon = me->FindNearestCreature(700709, 50.0f))
       //             DoCast(beacon, 319728, true);
       //     });
        me->RemoveUnitFlag(UNIT_FLAG_NON_ATTACKABLE);
        me->RemoveAurasDueToSpell(317535); // Enrage
        me->SetReactState(REACT_AGGRESSIVE);
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

    bool phase = false;
    bool isPhasing = false;

    void DamageTaken(Unit* attacker, uint32& damage, DamageEffectType /*damageType*/, SpellInfo const* /*spellInfo = nullptr*/) override
    {
        if (isPhasing)
        {
            attacker->AttackStop();
            damage = 0;
        }

        if (!phase && me->HealthBelowPctDamaged(51, damage))
        {
            phase = true;
            me->SetUnitFlag(UNIT_FLAG_NON_ATTACKABLE);
            me->AttackStop();
            me->SetReactState(REACT_PASSIVE);
            isPhasing = true;

            scheduler.Schedule(500ms, [this](TaskContext context)
                {
                    if (auto beacon = me->FindNearestCreature(700709, 50.0f))
                        me->SetFacingToObject(beacon);
                });
            scheduler.Schedule(1s, [this](TaskContext context)
                {
                    if (auto beacon = me->FindNearestCreature(700709, 50.0f))
                        DoCast(beacon, 331027, true);
                });


            me->RemoveAllAuras();
            scheduler.Schedule(3s, [this](TaskContext context)
            {
                    me->RemoveUnitFlag(UNIT_FLAG_NON_ATTACKABLE);

                    scheduler.Schedule(2s, [this](TaskContext context)
                    {
                            isPhasing = false;
                            if (me->GetCurrentSpell(CURRENT_CHANNELED_SPELL) != nullptr)
                            {
                                DoCastSelf(317535, true); // Enrage
                            }
                            me->SetReactState(REACT_AGGRESSIVE);
                    });
            });
        }
    }

    TaskScheduler scheduler;
    EventMap events;
};

// 700706 - npc_ju_won_brightdraft_700706
struct npc_ju_won_brightdraft_700706 : public ScriptedAI
{
public:
    npc_ju_won_brightdraft_700706(Creature* creature) : ScriptedAI(creature) { }

    enum eSpells
    {
        SCK = 330901,
        ROP = 116844,
        FlyingSerpentKick = 127807,
        SkullCrack = 83933,
    };

    void InitializeAI() override
    {
        /// TODO: Fill this function
    }

    void Reset() override
    {
        /// TODO: Fill this function
        events.Reset();
    }

    void JustEngagedWith(Unit* who) override
    {
        events.ScheduleEvent(1, 5s, 10s);
        events.ScheduleEvent(2, 25s, 30s);
        events.ScheduleEvent(3, 5s, 30s);
        events.ScheduleEvent(4, 25s, 40s);
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
                    DoCast(eSpells::SCK);
                    events.Repeat(5s, 10s);
                    break;
                case 2:
                    DoCast(eSpells::ROP);
                    events.Repeat(25s, 30s);
                    break;
                case 3:
                    DoCast(eSpells::FlyingSerpentKick);
                    events.Repeat(5s, 30s);
                    break;
                case 4:
                    DoCastVictim(eSpells::SkullCrack);
                    events.Repeat(25s, 40s);
                    break;
            }
        }
        DoMeleeAttackIfReady();
    }

    void OnUnitRelocation(Unit* who) override
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

// 700707 - npc_yin_li_loudlight_700707
struct npc_yin_li_loudlight_700707 : public ScriptedAI
{
public:
    npc_yin_li_loudlight_700707(Creature* creature) : ScriptedAI(creature) { }

    enum eSpells
    {
        MindBlast = 284409,
        MindFlay = 310552,
    };

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
        events.ScheduleEvent(1, 1s, 10s);
        events.ScheduleEvent(2, 1s, 10s);
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
                    DoCastVictim(MindBlast);
                    events.Repeat(5s, 10s);
                    break;
                case 2:
                    DoCastVictim(MindFlay);
                    events.Repeat(5s, 10s);
                    break;
            }
        }
        DoMeleeAttackIfReady();
    }

    void OnUnitRelocation(Unit* who) override
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

// 700708 - npc_zaphiel_700708
struct npc_zaphiel_700708 : public ScriptedAI
{
public:
    npc_zaphiel_700708(Creature* creature) : ScriptedAI(creature) { }
    
    enum eSpells
    {
        MindBlast = 314801,
        MindFlay = 310552,
        DarkSmite = 310845,
    };

    void InitializeAI() override
    {
        /// TODO: Fill this function
    }

    void Reset() override
    {
        /// TODO: Fill this function
        events.Reset();
    }

    void JustEngagedWith(Unit* who) override
    {
        events.Reset();

        events.ScheduleEvent(1, 1s, 10s);
        events.ScheduleEvent(2, 1s, 10s);
        events.ScheduleEvent(3, 1s, 10s);
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
                    DoCastVictim(MindBlast);
                    events.Repeat(5s, 15s);
                    break;
                case 2:
                    DoCastVictim(MindFlay);
                    events.Repeat(5s, 15s);
                    break;
                case 3:
                    DoCastVictim(DarkSmite);
                    events.Repeat(10s, 25s);
                    break;
            }
        }
        DoMeleeAttackIfReady();
    }

    TaskScheduler scheduler;
    EventMap events;
};

// 700709 - npc_beacon_of_light_700709
struct npc_beacon_of_light_700709 : public ScriptedAI
{
public:
    npc_beacon_of_light_700709(Creature* creature) : ScriptedAI(creature) { }

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
    void OnSpellClick(Unit* clicker, bool spellClickHandled) override
    {
        /// TODO: Fill this function
    }

    TaskScheduler scheduler;
    EventMap events;
};

// 700710 - npc_protector_of_light_700710
struct npc_protector_of_light_700710 : public ScriptedAI
{
public:
    npc_protector_of_light_700710(Creature* creature) : ScriptedAI(creature) { }

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
    void OnSpellClick(Unit* clicker, bool spellClickHandled) override
    {
        /// TODO: Fill this function
    }

    TaskScheduler scheduler;
    EventMap events;
};


void AddSC_PeakOfSerenity()
{
   RegisterCreatureAI(npc_avatar_of_the_light_700700);
   RegisterCreatureAI(npc_weapon_of_light_700701);
   RegisterCreatureAI(npc_disciple_of_light_700702);
   RegisterCreatureAI(npc_angelic_warrior_700703);
   RegisterCreatureAI(npc_betzalel_700705);
   RegisterCreatureAI(npc_ju_won_brightdraft_700706);
   RegisterCreatureAI(npc_yin_li_loudlight_700707);
   RegisterCreatureAI(npc_zaphiel_700708);
   RegisterCreatureAI(npc_beacon_of_light_700709);
   RegisterCreatureAI(npc_protector_of_light_700710);
}
