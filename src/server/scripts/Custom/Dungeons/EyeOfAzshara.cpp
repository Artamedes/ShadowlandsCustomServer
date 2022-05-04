#include "ScriptMgr.h"
#include "SpellAuraEffects.h"
#include "ScriptedCreature.h"
#include "Creature.h"
#include "Player.h"
#include "../CustomInstanceScript.h"

// 702000 - npc_wrath_of_azshara_702000
struct npc_wrath_of_azshara_702000 : public ScriptedAI
{
public:
    npc_wrath_of_azshara_702000(Creature* creature) : ScriptedAI(creature) { }

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


    TaskScheduler scheduler;
    EventMap events;
};

// 702001 - npc_drak_thor_702001
struct npc_drak_thor_702001 : public ScriptedAI
{
public:
    npc_drak_thor_702001(Creature* creature) : ScriptedAI(creature) { }

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


    TaskScheduler scheduler;
    EventMap events;
};

// 702002 - npc_lady_hatecoil_702002
struct npc_lady_hatecoil_702002 : public ScriptedAI
{
public:
    npc_lady_hatecoil_702002(Creature* creature) : ScriptedAI(creature) { }

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


    TaskScheduler scheduler;
    EventMap events;
};

// 702003 - npc_warlord_parjesh_702003
struct npc_warlord_parjesh_702003 : public ScriptedAI
{
public:
    npc_warlord_parjesh_702003(Creature* creature) : ScriptedAI(creature) { }

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


    TaskScheduler scheduler;
    EventMap events;
};

// 702008 - npc_hatecoil_crestrider_702008
struct npc_hatecoil_crestrider_702008 : public ScriptedAI
{
public:
    npc_hatecoil_crestrider_702008(Creature* creature) : ScriptedAI(creature) { }

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


    TaskScheduler scheduler;
    EventMap events;
};

// 702010 - npc_seaspray_murloc_702010
struct npc_seaspray_murloc_702010 : public ScriptedAI
{
public:
    npc_seaspray_murloc_702010(Creature* creature) : ScriptedAI(creature) { }

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


    TaskScheduler scheduler;
    EventMap events;
};

// 702011 - npc_murloc_spearhunter_702011
struct npc_murloc_spearhunter_702011 : public ScriptedAI
{
public:
    npc_murloc_spearhunter_702011(Creature* creature) : ScriptedAI(creature) { }

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


    TaskScheduler scheduler;
    EventMap events;
};

// 702005 - npc_hatecoil_crusher_702005
struct npc_hatecoil_crusher_702005 : public ScriptedAI
{
public:
    npc_hatecoil_crusher_702005(Creature* creature) : ScriptedAI(creature) { }

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


    TaskScheduler scheduler;
    EventMap events;
};

// 702006 - npc_hatecoil_slaver_702006
struct npc_hatecoil_slaver_702006 : public ScriptedAI
{
public:
    npc_hatecoil_slaver_702006(Creature* creature) : ScriptedAI(creature) { }

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


    TaskScheduler scheduler;
    EventMap events;
};

// 702012 - npc_enraged_forest_spirit_702012
struct npc_enraged_forest_spirit_702012 : public ScriptedAI
{
public:
    npc_enraged_forest_spirit_702012(Creature* creature) : ScriptedAI(creature) { }

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


    TaskScheduler scheduler;
    EventMap events;
};

// 702013 - npc_enraged_forest_spirit_702013
struct npc_enraged_forest_spirit_702013 : public ScriptedAI
{
public:
    npc_enraged_forest_spirit_702013(Creature* creature) : ScriptedAI(creature) { }

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


    TaskScheduler scheduler;
    EventMap events;
};

// 702014 - npc_tree_spirit_702014
struct npc_tree_spirit_702014 : public ScriptedAI
{
public:
    npc_tree_spirit_702014(Creature* creature) : ScriptedAI(creature) { }

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

    bool didIntro = false;
    void OnUnitRelocation(Unit* who) override
    {
        if (who->IsPlayer() && !didIntro && me->GetSpawnId() == 1054054 && who->GetDistance2d(me) <= 20.0f)
        {
            didIntro = true;
            Talk(0);
        }
    }


    TaskScheduler scheduler;
    EventMap events;
};

// 702015 - npc_forest_guardian_702015
struct npc_forest_guardian_702015 : public ScriptedAI
{
public:
    npc_forest_guardian_702015(Creature* creature) : ScriptedAI(creature) { }

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


    TaskScheduler scheduler;
    EventMap events;
};

// 702004 - npc_hatecoil_harpooner_702004
struct npc_hatecoil_harpooner_702004 : public ScriptedAI
{
public:
    npc_hatecoil_harpooner_702004(Creature* creature) : ScriptedAI(creature) { }

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


    TaskScheduler scheduler;
    EventMap events;
};

// 702016 - npc_awakened_plant_702016
struct npc_awakened_plant_702016 : public ScriptedAI
{
public:
    npc_awakened_plant_702016(Creature* creature) : ScriptedAI(creature) { }

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


    TaskScheduler scheduler;
    EventMap events;
};

// 702017 - npc_angered_cave_spirit_702017
struct npc_angered_cave_spirit_702017 : public ScriptedAI
{
public:
    npc_angered_cave_spirit_702017(Creature* creature) : ScriptedAI(creature) { }

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


    TaskScheduler scheduler;
    EventMap events;
};

// 702018 - npc_earth_spirit_702018
struct npc_earth_spirit_702018 : public ScriptedAI
{
public:
    npc_earth_spirit_702018(Creature* creature) : ScriptedAI(creature) { }

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


    TaskScheduler scheduler;
    EventMap events;
};

// 702019 - npc_aged_viking_spirit_702019
struct npc_aged_viking_spirit_702019 : public ScriptedAI
{
public:
    npc_aged_viking_spirit_702019(Creature* creature) : ScriptedAI(creature) { }

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


    TaskScheduler scheduler;
    EventMap events;
};

// 702007 - npc_hatecoil_shellbreaker_702007
struct npc_hatecoil_shellbreaker_702007 : public ScriptedAI
{
public:
    npc_hatecoil_shellbreaker_702007(Creature* creature) : ScriptedAI(creature) { }

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


    TaskScheduler scheduler;
    EventMap events;
};

// 702009 - npc_hatecoil_arcanist_702009
struct npc_hatecoil_arcanist_702009 : public ScriptedAI
{
public:
    npc_hatecoil_arcanist_702009(Creature* creature) : ScriptedAI(creature) { }

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


    TaskScheduler scheduler;
    EventMap events;
};

// 702020 - npc_larnae_stormleaf_702020
struct npc_larnae_stormleaf_702020 : public ScriptedAI
{
public:
    npc_larnae_stormleaf_702020(Creature* creature) : ScriptedAI(creature) { }

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


    TaskScheduler scheduler;
    EventMap events;
};

void AddSC_EyeOfAzshara()
{
    RegisterCreatureAI(npc_wrath_of_azshara_702000);
    RegisterCreatureAI(npc_drak_thor_702001);
    RegisterCreatureAI(npc_lady_hatecoil_702002);
    RegisterCreatureAI(npc_warlord_parjesh_702003);
    RegisterCreatureAI(npc_hatecoil_crestrider_702008);
    RegisterCreatureAI(npc_seaspray_murloc_702010);
    RegisterCreatureAI(npc_murloc_spearhunter_702011);
    RegisterCreatureAI(npc_hatecoil_crusher_702005);
    RegisterCreatureAI(npc_hatecoil_slaver_702006);
    RegisterCreatureAI(npc_enraged_forest_spirit_702012);
    RegisterCreatureAI(npc_enraged_forest_spirit_702013);
    RegisterCreatureAI(npc_tree_spirit_702014);
    RegisterCreatureAI(npc_forest_guardian_702015);
    RegisterCreatureAI(npc_hatecoil_harpooner_702004);
    RegisterCreatureAI(npc_awakened_plant_702016);
    RegisterCreatureAI(npc_angered_cave_spirit_702017);
    RegisterCreatureAI(npc_earth_spirit_702018);
    RegisterCreatureAI(npc_aged_viking_spirit_702019);
    RegisterCreatureAI(npc_hatecoil_shellbreaker_702007);
    RegisterCreatureAI(npc_hatecoil_arcanist_702009);
    RegisterCreatureAI(npc_larnae_stormleaf_702020);
}
