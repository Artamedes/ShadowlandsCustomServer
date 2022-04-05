#include "ScriptMgr.h"
#include "Player.h"
#include "Creature.h"
#include "ScriptedCreature.h"
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

// 700701 - npc_weapon_of_light_700701
struct npc_weapon_of_light_700701 : public ScriptedAI
{
public:
    npc_weapon_of_light_700701(Creature* creature) : ScriptedAI(creature) { }

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

// 700704 - npc_portal_of_light_700704
struct npc_portal_of_light_700704 : public ScriptedAI
{
public:
    npc_portal_of_light_700704(Creature* creature) : ScriptedAI(creature) { }

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

// 700711 - npc_corrupted_light_700711
struct npc_corrupted_light_700711 : public ScriptedAI
{
public:
    npc_corrupted_light_700711(Creature* creature) : ScriptedAI(creature) { }

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
        events.ScheduleEvent(1, 5s, 10s);
        events.ScheduleEvent(2, 25s, 30s);
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
                    DoCastAOE(365834);
                    events.Repeat(7s, 20s);
                    break;
                case 2:
                {
                    DoCastAOE(360145);

                    std::list<Player*> players;
                    Trinity::AnyPlayerInObjectRangeCheck checker(me, 50.0f);
                    Trinity::PlayerListSearcher<Trinity::AnyPlayerInObjectRangeCheck> searcher(me, players, checker);
                    Cell::VisitWorldObjects(me, searcher, 50.0f);

                    for (auto u : players)
                    {
                        if (u)
                            if (u->HasAura(365834))
                                Unit::DealDamage(me, u, u->GetHealth());
                    }

                    events.Repeat(7s, 20s);
                    break;
                }
            }
        }
        DoMeleeAttackIfReady();
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

// 700712 - npc_kang_dae_whitegarden_700712
struct npc_kang_dae_whitegarden_700712 : public ScriptedAI
{
public:
    npc_kang_dae_whitegarden_700712(Creature* creature) : ScriptedAI(creature) { }

    enum eSpells
    {
        MindBlast = 314801,
        MindFlay = 310552,
        DarkSmite = 310845,
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
    }

    void JustEngagedWith(Unit* who) override
    {
        events.Reset();

        events.ScheduleEvent(1, 1s, 10s);
        events.ScheduleEvent(2, 1s, 10s);
        events.ScheduleEvent(3, 1s, 10s);
        events.ScheduleEvent(4, 5s, 10s);
        events.ScheduleEvent(5, 25s, 30s);
        events.ScheduleEvent(6, 5s, 30s);
        events.ScheduleEvent(7, 25s, 40s);
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
                case 4:
                    DoCast(eSpells::SCK);
                    events.Repeat(5s, 10s);
                    break;
                case 5:
                    DoCast(eSpells::ROP);
                    events.Repeat(25s, 30s);
                    break;
                case 6:
                    DoCast(eSpells::FlyingSerpentKick);
                    events.Repeat(5s, 30s);
                    break;
                case 7:
                    DoCastVictim(eSpells::SkullCrack);
                    events.Repeat(25s, 40s);
                    break;
            }
        }
        DoMeleeAttackIfReady();
    }

    TaskScheduler scheduler;
    EventMap events;
};

// 700713 - npc_lord_darius_700713
struct npc_lord_darius_700713 : public ScriptedAI
{
public:
    npc_lord_darius_700713(Creature* creature) : ScriptedAI(creature) { }

    void InitializeAI() override
    {
        /// TODO: Fill this function
        me->SetUnitFlag(UNIT_FLAG_NON_ATTACKABLE);
        me->DeMorph();
    }

    void Reset() override
    {
        /// TODO: Fill this function
        me->DeMorph();
        phase = false;
    }

    void JustEngagedWith(Unit* who) override
    {
        me->DeMorph();
        phase = false;
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


    bool intro = false;
    void OnUnitRelocation(Unit* who) override
    {
        /// TODO: Fill this function
        if (!intro && who->IsPlayer() && who->GetDistance2d(me) <= 30.0f)
        {
            intro = true;
            Talk(0);
            scheduler.Schedule(3s, [this](TaskContext context)
                {

                    me->RemoveUnitFlag(UNIT_FLAG_NON_ATTACKABLE);
                });
        }
    }

    bool phase = false;
    void DamageTaken(Unit* attacker, uint32& damage, DamageEffectType damageType, SpellInfo const* spell) override
    {
        if (!phase && me->HealthBelowPctDamaged(51, damage))
        {
            phase = true;
            Talk(1);
            me->SetDisplayId(92451);
        }
    }

    void OnSpellClick(Unit* clicker, bool spellClickHandled) override
    {
        /// TODO: Fill this function
    }

    TaskScheduler scheduler;
    EventMap events;
};

// 700714 - npc_rehael_700714
struct npc_rehael_700714 : public ScriptedAI
{
public:
    npc_rehael_700714(Creature* creature) : ScriptedAI(creature) { }

    enum eSpells
    {
        HolySmite = 280939,
        Chastise = 200200,
        HolyFire = 242194,
    };

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
        Talk(1);
        events.ScheduleEvent(1, 5s, 10s);
        events.ScheduleEvent(2, 25s, 30s);
        events.ScheduleEvent(3, 5s, 30s);
    }

    void JustDied(Unit* who) override
    {
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
                case 1:
                    DoCast(eSpells::HolySmite);
                    events.Repeat(5s, 10s);
                    break;
                case 2:
                    DoCast(eSpells::HolyFire);
                    events.Repeat(25s, 30s);
                    break;
                case 3:
                    DoCast(eSpells::Chastise);
                    events.Repeat(5s, 30s);
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

// 700715 - npc_yofiel_700715
struct npc_yofiel_700715 : public ScriptedAI
{
public:
    npc_yofiel_700715(Creature* creature) : ScriptedAI(creature) { }

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

    bool dead = false;
    bool phase = false;
    void DamageTaken(Unit* attacker, uint32& damage, DamageEffectType damageType, SpellInfo const* spell) override
    {
        if (me->GetHealth() <= damage)
        {
            damage = 0;
            attacker->AttackStop();
            if (!dead)
            {
                dead = true;
                me->UpdateEntry(700727);
                EnterEvadeMode();
                me->SetFaction(35);
                me->SetReactState(REACT_PASSIVE);
                me->SetUnitFlag(UnitFlags::UNIT_FLAG_NON_ATTACKABLE);
            }
        }
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

// 700716 - npc_watcher_700716
struct npc_watcher_700716 : public ScriptedAI
{
public:
    npc_watcher_700716(Creature* creature) : ScriptedAI(creature) { }

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

// 700717 - npc_paladin_enforcer_700717
struct npc_paladin_enforcer_700717 : public ScriptedAI
{
public:
    npc_paladin_enforcer_700717(Creature* creature) : ScriptedAI(creature) { }

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

// 700718 - npc_high_priest_700718
struct npc_high_priest_700718 : public ScriptedAI
{
public:
    npc_high_priest_700718(Creature* creature) : ScriptedAI(creature) { }

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

    void OnSpellClick(Unit* clicker, bool spellClickHandled) override
    {
        /// TODO: Fill this function
    }

    TaskScheduler scheduler;
    EventMap events;
};

// 700719 - npc_inquisitor_700719
struct npc_inquisitor_700719 : public ScriptedAI
{
public:
    npc_inquisitor_700719(Creature* creature) : ScriptedAI(creature) { }

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

    void OnSpellClick(Unit* clicker, bool spellClickHandled) override
    {
        /// TODO: Fill this function
    }

    TaskScheduler scheduler;
    EventMap events;
};

// 700720 - npc_corrupted_priest_700720
struct npc_corrupted_priest_700720 : public ScriptedAI
{
public:
    npc_corrupted_priest_700720(Creature* creature) : ScriptedAI(creature) { }

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

    void OnSpellClick(Unit* clicker, bool spellClickHandled) override
    {
        /// TODO: Fill this function
    }

    TaskScheduler scheduler;
    EventMap events;
};


void AddSC_ShadoPanMonastary()
{
   //RegisterCreatureAI(npc_angelic_warrior_700703);
   //RegisterCreatureAI(npc_weapon_of_light_700701);
   //RegisterCreatureAI(npc_portal_of_light_700704);
   RegisterCreatureAI(npc_corrupted_light_700711);
 //  RegisterCreatureAI(npc_disciple_of_light_700702);
   RegisterCreatureAI(npc_kang_dae_whitegarden_700712);
   RegisterCreatureAI(npc_lord_darius_700713);
   RegisterCreatureAI(npc_rehael_700714);
   RegisterCreatureAI(npc_yofiel_700715);
 //  RegisterCreatureAI(npc_protector_of_light_700710);
   RegisterCreatureAI(npc_watcher_700716);
   RegisterCreatureAI(npc_paladin_enforcer_700717);
   RegisterCreatureAI(npc_high_priest_700718);
   RegisterCreatureAI(npc_inquisitor_700719);
   RegisterCreatureAI(npc_corrupted_priest_700720);
}
// 
// UPDATE creature_template set scriptname = 'npc_angelic_warrior_700703' where entry = 700703;
// UPDATE creature_template set scriptname = 'npc_weapon_of_light_700701' where entry = 700701;
// UPDATE creature_template set scriptname = 'npc_portal_of_light_700704' where entry = 700704;
// UPDATE creature_template set scriptname = 'npc_corrupted_light_700711' where entry = 700711;
// UPDATE creature_template set scriptname = 'npc_disciple_of_light_700702' where entry = 700702;
// UPDATE creature_template set scriptname = 'npc_kang_dae_whitegarden_700712' where entry = 700712;
// UPDATE creature_template set scriptname = 'npc_lord_darius_700713' where entry = 700713;
// UPDATE creature_template set scriptname = 'npc_rehael_700714' where entry = 700714;
// UPDATE creature_template set scriptname = 'npc_yofiel_700715' where entry = 700715;
// UPDATE creature_template set scriptname = 'npc_protector_of_light_700710' where entry = 700710;
// UPDATE creature_template set scriptname = 'npc_watcher_700716' where entry = 700716;
// UPDATE creature_template set scriptname = 'npc_paladin_enforcer_700717' where entry = 700717;
// UPDATE creature_template set scriptname = 'npc_high_priest_700718' where entry = 700718;
// UPDATE creature_template set scriptname = 'npc_inquisitor_700719' where entry = 700719;
// UPDATE creature_template set scriptname = 'npc_corrupted_priest_700720' where entry = 700720;
