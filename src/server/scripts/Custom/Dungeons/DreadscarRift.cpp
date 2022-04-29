#include "ScriptMgr.h"
#include "../CustomInstanceScript.h"

struct instance_dreadscarrift : public CustomInstanceScript
{
public:
    instance_dreadscarrift(InstanceMap* map) : CustomInstanceScript(map)
    {
    }
};
// 703000 - npc_adageor_703000
struct npc_adageor_703000 : public ScriptedAI
{
public:
    npc_adageor_703000(Creature* creature) : ScriptedAI(creature) { }

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

    TaskScheduler scheduler;
    EventMap events;
};

// 703001 - npc_goroth_703001
struct npc_goroth_703001 : public ScriptedAI
{
public:
    npc_goroth_703001(Creature* creature) : ScriptedAI(creature) { }

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

    TaskScheduler scheduler;
    EventMap events;
};

// 703007 - npc_harvested_mana_crystal_703007
struct npc_harvested_mana_crystal_703007 : public ScriptedAI
{
public:
    npc_harvested_mana_crystal_703007(Creature* creature) : ScriptedAI(creature) { }

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

    TaskScheduler scheduler;
    EventMap events;
};

// 703009 - npc_moz_gar_703009
struct npc_moz_gar_703009 : public ScriptedAI
{
public:
    npc_moz_gar_703009(Creature* creature) : ScriptedAI(creature) { }

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

    TaskScheduler scheduler;
    EventMap events;
};

// 703011 - npc_arcane_voidwalker_703011
struct npc_arcane_voidwalker_703011 : public ScriptedAI
{
public:
    npc_arcane_voidwalker_703011(Creature* creature) : ScriptedAI(creature) { }

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

    TaskScheduler scheduler;
    EventMap events;
};

// 703012 - npc_dolgonir_703012
struct npc_dolgonir_703012 : public ScriptedAI
{
public:
    npc_dolgonir_703012(Creature* creature) : ScriptedAI(creature) { }

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

    TaskScheduler scheduler;
    EventMap events;
};

// 703013 - npc_bellatrix_703013
struct npc_bellatrix_703013 : public ScriptedAI
{
public:
    npc_bellatrix_703013(Creature* creature) : ScriptedAI(creature) { }

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

    TaskScheduler scheduler;
    EventMap events;
};

// 703014 - npc_floating_books_703014
struct npc_floating_books_703014 : public ScriptedAI
{
public:
    npc_floating_books_703014(Creature* creature) : ScriptedAI(creature) { }

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

    TaskScheduler scheduler;
    EventMap events;
};

// 703017 - npc_kuryash_703017
struct npc_kuryash_703017 : public ScriptedAI
{
public:
    npc_kuryash_703017(Creature* creature) : ScriptedAI(creature) { }

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

    TaskScheduler scheduler;
    EventMap events;
};

// 703022 - npc_demon_larva_703022
struct npc_demon_larva_703022 : public ScriptedAI
{
public:
    npc_demon_larva_703022(Creature* creature) : ScriptedAI(creature) { }

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

    TaskScheduler scheduler;
    EventMap events;
};

// 703025 - npc_hellfire_infernal_703025
struct npc_hellfire_infernal_703025 : public ScriptedAI
{
public:
    npc_hellfire_infernal_703025(Creature* creature) : ScriptedAI(creature) { }

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

    TaskScheduler scheduler;
    EventMap events;
};

// 703021 - npc_demonic_tome_703021
struct npc_demonic_tome_703021 : public ScriptedAI
{
public:
    npc_demonic_tome_703021(Creature* creature) : ScriptedAI(creature) { }

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

    TaskScheduler scheduler;
    EventMap events;
};

// 703026 - npc_hellish_imp_703026
struct npc_hellish_imp_703026 : public ScriptedAI
{
public:
    npc_hellish_imp_703026(Creature* creature) : ScriptedAI(creature) { }

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

    TaskScheduler scheduler;
    EventMap events;
};

// 703024 - npc_condemned_demon_703024
struct npc_condemned_demon_703024 : public ScriptedAI
{
public:
    npc_condemned_demon_703024(Creature* creature) : ScriptedAI(creature) { }

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

    TaskScheduler scheduler;
    EventMap events;
};

// 703016 - npc_storm_voidwalker_703016
struct npc_storm_voidwalker_703016 : public ScriptedAI
{
public:
    npc_storm_voidwalker_703016(Creature* creature) : ScriptedAI(creature) { }

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

    TaskScheduler scheduler;
    EventMap events;
};

// 703005 - npc_soul_bound_brute_703005
struct npc_soul_bound_brute_703005 : public ScriptedAI
{
public:
    npc_soul_bound_brute_703005(Creature* creature) : ScriptedAI(creature) { }

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

    TaskScheduler scheduler;
    EventMap events;
};

// 703004 - npc_soul_bound_warrior_703004
struct npc_soul_bound_warrior_703004 : public ScriptedAI
{
public:
    npc_soul_bound_warrior_703004(Creature* creature) : ScriptedAI(creature) { }

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

    TaskScheduler scheduler;
    EventMap events;
};

// 703019 - npc_vampiric_slave_703019
struct npc_vampiric_slave_703019 : public ScriptedAI
{
public:
    npc_vampiric_slave_703019(Creature* creature) : ScriptedAI(creature) { }

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

    TaskScheduler scheduler;
    EventMap events;
};

// 703020 - npc_vampiric_warrior_703020
struct npc_vampiric_warrior_703020 : public ScriptedAI
{
public:
    npc_vampiric_warrior_703020(Creature* creature) : ScriptedAI(creature) { }

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

    TaskScheduler scheduler;
    EventMap events;
};

// 703018 - npc_necromantic_warrior_703018
struct npc_necromantic_warrior_703018 : public ScriptedAI
{
public:
    npc_necromantic_warrior_703018(Creature* creature) : ScriptedAI(creature) { }

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

    TaskScheduler scheduler;
    EventMap events;
};

// 703010 - npc_fel_bound_mech_703010
struct npc_fel_bound_mech_703010 : public ScriptedAI
{
public:
    npc_fel_bound_mech_703010(Creature* creature) : ScriptedAI(creature) { }

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

    TaskScheduler scheduler;
    EventMap events;
};

// 703002 - npc_bound_earth_spirit_703002
struct npc_bound_earth_spirit_703002 : public ScriptedAI
{
public:
    npc_bound_earth_spirit_703002(Creature* creature) : ScriptedAI(creature) { }

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

    TaskScheduler scheduler;
    EventMap events;
};

// 703003 - npc_arcane_hound_703003
struct npc_arcane_hound_703003 : public ScriptedAI
{
public:
    npc_arcane_hound_703003(Creature* creature) : ScriptedAI(creature) { }

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

    TaskScheduler scheduler;
    EventMap events;
};

// 703008 - npc_mana_bound_golem_703008
struct npc_mana_bound_golem_703008 : public ScriptedAI
{
public:
    npc_mana_bound_golem_703008(Creature* creature) : ScriptedAI(creature) { }

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

    TaskScheduler scheduler;
    EventMap events;
};

// 703015 - npc_arcane_researcher_703015
struct npc_arcane_researcher_703015 : public ScriptedAI
{
public:
    npc_arcane_researcher_703015(Creature* creature) : ScriptedAI(creature) { }

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

    TaskScheduler scheduler;
    EventMap events;
};

// 703006 - npc_anivia_703006
struct npc_anivia_703006 : public ScriptedAI
{
public:
    npc_anivia_703006(Creature* creature) : ScriptedAI(creature) { }

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

    TaskScheduler scheduler;
    EventMap events;
};

// 703023 - npc_demonfly_acidmaw_703023
struct npc_demonfly_acidmaw_703023 : public ScriptedAI
{
public:
    npc_demonfly_acidmaw_703023(Creature* creature) : ScriptedAI(creature) { }

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

    TaskScheduler scheduler;
    EventMap events;
};

// 703027 - npc_fel_conduit_703027
struct npc_fel_conduit_703027 : public ScriptedAI
{
public:
    npc_fel_conduit_703027(Creature* creature) : ScriptedAI(creature) { }

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

    TaskScheduler scheduler;
    EventMap events;
};

void AddSC_DreadscarRift()
{
    RegisterInstanceScript(instance_dreadscarrift, 1107);
    RegisterCreatureAI(npc_adageor_703000);
    RegisterCreatureAI(npc_goroth_703001);
    RegisterCreatureAI(npc_harvested_mana_crystal_703007);
    RegisterCreatureAI(npc_moz_gar_703009);
    RegisterCreatureAI(npc_arcane_voidwalker_703011);
    RegisterCreatureAI(npc_dolgonir_703012);
    RegisterCreatureAI(npc_bellatrix_703013);
    RegisterCreatureAI(npc_floating_books_703014);
    RegisterCreatureAI(npc_kuryash_703017);
    RegisterCreatureAI(npc_demon_larva_703022);
    RegisterCreatureAI(npc_hellfire_infernal_703025);
    RegisterCreatureAI(npc_demonic_tome_703021);
    RegisterCreatureAI(npc_hellish_imp_703026);
    RegisterCreatureAI(npc_condemned_demon_703024);
    RegisterCreatureAI(npc_storm_voidwalker_703016);
    RegisterCreatureAI(npc_soul_bound_brute_703005);
    RegisterCreatureAI(npc_soul_bound_warrior_703004);
    RegisterCreatureAI(npc_vampiric_slave_703019);
    RegisterCreatureAI(npc_vampiric_warrior_703020);
    RegisterCreatureAI(npc_necromantic_warrior_703018);
    RegisterCreatureAI(npc_fel_bound_mech_703010);
    RegisterCreatureAI(npc_bound_earth_spirit_703002);
    RegisterCreatureAI(npc_arcane_hound_703003);
    RegisterCreatureAI(npc_mana_bound_golem_703008);
    RegisterCreatureAI(npc_arcane_researcher_703015);
    RegisterCreatureAI(npc_anivia_703006);
    RegisterCreatureAI(npc_demonfly_acidmaw_703023);
    RegisterCreatureAI(npc_fel_conduit_703027);
}

// UPDATE creature_template set ScriptName = 'npc_adageor_703000' WHERE entry = 703000;
// UPDATE creature_template set ScriptName = 'npc_goroth_703001' WHERE entry = 703001;
// UPDATE creature_template set ScriptName = 'npc_harvested_mana_crystal_703007' WHERE entry = 703007;
// UPDATE creature_template set ScriptName = 'npc_moz_gar_703009' WHERE entry = 703009;
// UPDATE creature_template set ScriptName = 'npc_arcane_voidwalker_703011' WHERE entry = 703011;
// UPDATE creature_template set ScriptName = 'npc_dolgonir_703012' WHERE entry = 703012;
// UPDATE creature_template set ScriptName = 'npc_bellatrix_703013' WHERE entry = 703013;
// UPDATE creature_template set ScriptName = 'npc_floating_books_703014' WHERE entry = 703014;
// UPDATE creature_template set ScriptName = 'npc_kuryash_703017' WHERE entry = 703017;
// UPDATE creature_template set ScriptName = 'npc_demon_larva_703022' WHERE entry = 703022;
// UPDATE creature_template set ScriptName = 'npc_hellfire_infernal_703025' WHERE entry = 703025;
// UPDATE creature_template set ScriptName = 'npc_demonic_tome_703021' WHERE entry = 703021;
// UPDATE creature_template set ScriptName = 'npc_hellish_imp_703026' WHERE entry = 703026;
// UPDATE creature_template set ScriptName = 'npc_condemned_demon_703024' WHERE entry = 703024;
// UPDATE creature_template set ScriptName = 'npc_storm_voidwalker_703016' WHERE entry = 703016;
// UPDATE creature_template set ScriptName = 'npc_soul_bound_brute_703005' WHERE entry = 703005;
// UPDATE creature_template set ScriptName = 'npc_soul_bound_warrior_703004' WHERE entry = 703004;
// UPDATE creature_template set ScriptName = 'npc_vampiric_slave_703019' WHERE entry = 703019;
// UPDATE creature_template set ScriptName = 'npc_vampiric_warrior_703020' WHERE entry = 703020;
// UPDATE creature_template set ScriptName = 'npc_necromantic_warrior_703018' WHERE entry = 703018;
// UPDATE creature_template set ScriptName = 'npc_fel_bound_mech_703010' WHERE entry = 703010;
// UPDATE creature_template set ScriptName = 'npc_bound_earth_spirit_703002' WHERE entry = 703002;
// UPDATE creature_template set ScriptName = 'npc_arcane_hound_703003' WHERE entry = 703003;
// UPDATE creature_template set ScriptName = 'npc_mana_bound_golem_703008' WHERE entry = 703008;
// UPDATE creature_template set ScriptName = 'npc_arcane_researcher_703015' WHERE entry = 703015;
// UPDATE creature_template set ScriptName = 'npc_anivia_703006' WHERE entry = 703006;
// UPDATE creature_template set ScriptName = 'npc_demonfly_acidmaw_703023' WHERE entry = 703023;
// UPDATE creature_template set ScriptName = 'npc_fel_conduit_703027' WHERE entry = 703027;
