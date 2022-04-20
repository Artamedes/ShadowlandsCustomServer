#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "../CustomInstanceScript.h"
#include "MoveSpline.h"
#include "CriteriaHandler.h"
#include "Scenario.h"
#include "InstanceScenario.h"

enum Underrot
{
    NpcBloodBall = 701013,
    SpellDummyChannel = 363390,

    BossA = 701005,
    BossB = 701003,
    BossC = 701000,

    UnderrotCriteriaID = 300000,
};

struct instance_the_underrot : public CustomInstanceScript
{
public:
    instance_the_underrot(InstanceMap* map) : CustomInstanceScript(map)
    {
    }

    void OnCompletedCriteriaTree(CriteriaTree const* tree) override
    {
        if (InstanceScenario* instanceScenario = instance->GetInstanceScenario())
        {
            if (auto tree2 = sCriteriaMgr->GetCriteriaTree(UnderrotCriteriaID))
                instanceScenario->IsCompletedCriteriaTree(tree2, nullptr);
        }
    }

    // unneeded for now - handled internally
    //void CreatureDiesForScript(Creature* creature, Unit* killer) override
    //{
    //    // call parent so challenge updates (runs affixes)
    //    InstanceScript::CreatureDiesForScript(creature, killer);
    //
    //    if (creature->ToTempSummon())
    //        return;
    //
    //    switch (creature->GetEntry())
    //    {
    //        case BossA:
    //          //  DoUpdateCriteria(CriteriaType::DefeatDungeonEncounter, creature->GetEntry());
    //            break;
    //        case BossB:
    //         //   DoUpdateCriteria(CriteriaType::DefeatDungeonEncounter, creature->GetEntry());
    //            break;
    //        case BossC:
    //         //   DoUpdateCriteria(CriteriaType::DefeatDungeonEncounter, creature->GetEntry());
    //            break;
    //        default:
    //            break;
    //    }
    //}
};

// 701000 - npc_mister_doctor_701000
struct npc_mister_doctor_701000 : public ScriptedAI
{
public:
    npc_mister_doctor_701000(Creature* creature) : ScriptedAI(creature), summons(creature) { }

    SummonList summons;

    void JustSummoned(Creature* creature) override
    {
        summons.Summon(creature);
    }

    void InitializeAI() override
    {
        ApplyAllImmunities(true);
    }

    void Reset() override
    {
        phasing = false;
        didPhase = false;
        me->SetReactState(REACT_AGGRESSIVE);
        me->DeMorph();
        me->RemoveUnitFlag(UnitFlags::UNIT_FLAG_UNINTERACTIBLE);
        me->RemoveUnitFlag(UnitFlags::UNIT_FLAG_NON_ATTACKABLE_2);
        me->RemoveUnitFlag2(UnitFlags2::UNIT_FLAG2_HIDE_BODY);
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
        if (!didIntro && who->IsPlayer() && who->GetDistance2d(me) <= 30.0f && (!who->movespline || who->movespline->Finalized()))
        {
            didIntro = true;
            Talk(0);
        }
    }

    bool didPhase = false;
    bool didPhase2 = false;
    bool phasing = false;
    void DamageTaken(Unit* attacker, uint32& damage, DamageEffectType damageType, SpellInfo const* spell) override
    {
        if (phasing)
            damage = 0;

        if (!didPhase && me->HealthBelowPctDamaged(61, damage))
        {
            didPhase = true;
            Talk(1);
            me->SetReactState(REACT_PASSIVE);
            me->StopMoving();
            phasing = true;
            scheduler.Schedule(6s, [this](TaskContext context)
            {
                    phasing = false;
                    me->SetReactState(REACT_AGGRESSIVE);
                    Talk(2);
                    me->SetDisplayId(96240);
            });
        }

        // - At 5 % health, ONLY if he morphed(just in case he bugs outand doesnt drink or players find a way to interrupt), he basically does Zac's passive from League:
        //     - First he says : Creature_text entry : 701000 groupID 3, then an effect plays(I did not have time to find an effect before server crash, sorry - I'm typing this portion up as server is closed)
        //     - he dissappears and turns into about 5 or 10 Mister Slimes(ID: 701001)
        //     - You pick what seems like a better number here, should not be random as each slime accounts for a percentage of his full health
        //     - E.G if 5 slimes, they each equal 10 % of total health, if they all reform he goes back to 50 % health.If 10 slimes, they each equal 5 %, all reforming back to 50 % of his full health
        //     - When he turns into the slimes, they all separate around a circle, walking very slowly back to the center of where he was before turning to slimes, then player has to kill them all to finish the boss
        //     - If players do not kill all of them, he reforms when they hit the center.Each slime left equals a percentage of his health(see above)
        //     - When / if he is able to reform, he will say : Creature_text entry : 701000 groupID 4
        //     - This process repeats whenever he hits 5 % health
        if (!didPhase2 && me->HealthBelowPctDamaged(5, damage))
        {
            didPhase2 = true;
            phasing = true;
            Talk(3);
            me->SetUnitFlag(UnitFlags::UNIT_FLAG_UNINTERACTIBLE);
            me->SetUnitFlag(UnitFlags::UNIT_FLAG_NON_ATTACKABLE_2);
            me->SetUnitFlag2(UnitFlags2::UNIT_FLAG2_HIDE_BODY);


        }
    }

    TaskScheduler scheduler;
    EventMap events;
};

// 701001 - npc_mister_slime_701001
struct npc_mister_slime_701001 : public ScriptedAI
{
public:
    npc_mister_slime_701001(Creature* creature) : ScriptedAI(creature) { }

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

// 701002 - npc_plague_tentacle_701002
struct npc_plague_tentacle_701002 : public ScriptedAI
{
public:
    npc_plague_tentacle_701002(Creature* creature) : ScriptedAI(creature) { }

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

// 701003 - npc_ansid_the_mechanic_701003
struct npc_ansid_the_mechanic_701003 : public ScriptedAI
{
public:
    npc_ansid_the_mechanic_701003(Creature* creature) : ScriptedAI(creature) { }

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


    TaskScheduler scheduler;
    EventMap events;
};

// 701004 - npc_ansid_s_helper_701004
struct npc_ansid_s_helper_701004 : public ScriptedAI
{
public:
    npc_ansid_s_helper_701004(Creature* creature) : ScriptedAI(creature) { }

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

// 701005 - npc_sporecaller_zancha_701005
struct npc_sporecaller_zancha_701005 : public ScriptedAI
{
public:
    npc_sporecaller_zancha_701005(Creature* creature) : ScriptedAI(creature) { }

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

    bool didIntro = false;
    void OnUnitRelocation(Unit* who) override
    {
        if (!didIntro && who->IsPlayer() && who->GetDistance2d(me) <= 40.0f)
        {
            didIntro = true;
            Talk(0);
        }
    }


    TaskScheduler scheduler;
    EventMap events;
};

// 701006 - npc_plague_witch_701006
struct npc_plague_witch_701006 : public ScriptedAI
{
public:
    npc_plague_witch_701006(Creature* creature) : ScriptedAI(creature) { }

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
        me->RemoveAurasDueToSpell(SpellDummyChannel);
    }

    void UpdateAI(uint32 diff) override
    {
        scheduler.Update(diff);

        if (!UpdateVictim())
        {
            if (!me->isDead() && !me->IsEngaged() && !me->GetCurrentSpell(CurrentSpellTypes::CURRENT_CHANNELED_SPELL))
            {
                if (auto bloodBoil = me->FindNearestCreature(NpcBloodBall, 6.0f))
                    DoCast(bloodBoil, SpellDummyChannel, true);
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

    bool didTalk = false;

    void OnUnitRelocation(Unit* who) override
    {
        if (who->IsPlayer() && !didTalk && me->GetSpawnId() == 1053659 && who->GetDistance2d(me) <= 35.0f)
        {
            didTalk = true;
            Talk(0);
            scheduler.Schedule(5s, [this](TaskContext context)
            {
                if (auto secondCreature = me->FindNearestCreatureBySpawnId(1053658, 30.0f))
                {
                    if (auto ai = secondCreature->AI())
                        ai->Talk(1);
                }
                
                scheduler.Schedule(5s, [this](TaskContext context)
                {
                    Talk(2);
                });
            });
        }
    }


    TaskScheduler scheduler;
    EventMap events;
};

// 701007 - npc_timmothy_701007
struct npc_timmothy_701007 : public ScriptedAI
{
public:
    npc_timmothy_701007(Creature* creature) : ScriptedAI(creature) { }

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

// 701008 - npc_fetid_maggot_701008
struct npc_fetid_maggot_701008 : public ScriptedAI
{
public:
    npc_fetid_maggot_701008(Creature* creature) : ScriptedAI(creature) { }

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

// 701009 - npc_spore_covered_scavenger_701009
struct npc_spore_covered_scavenger_701009 : public ScriptedAI
{
public:
    npc_spore_covered_scavenger_701009(Creature* creature) : ScriptedAI(creature) { }

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

// 701010 - npc_rockjaw_fungus_flinger_701010
struct npc_rockjaw_fungus_flinger_701010 : public ScriptedAI
{
public:
    npc_rockjaw_fungus_flinger_701010(Creature* creature) : ScriptedAI(creature) { }

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

// 701011 - npc_plague_covered_fungo_701011
struct npc_plague_covered_fungo_701011 : public ScriptedAI
{
public:
    npc_plague_covered_fungo_701011(Creature* creature) : ScriptedAI(creature) { }

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

// 701012 - npc_gloomshade_fungi_701012
struct npc_gloomshade_fungi_701012 : public ScriptedAI
{
public:
    npc_gloomshade_fungi_701012(Creature* creature) : ScriptedAI(creature) { }

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

// 701013 - npc_blood_ball_701013
struct npc_blood_ball_701013 : public ScriptedAI
{
public:
    npc_blood_ball_701013(Creature* creature) : ScriptedAI(creature) { }

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

// 701014 - npc_damaged_defense_bot_701014
struct npc_damaged_defense_bot_701014 : public ScriptedAI
{
public:
    npc_damaged_defense_bot_701014(Creature* creature) : ScriptedAI(creature) { }

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

// 701015 - npc_defense_bot_701015
struct npc_defense_bot_701015 : public ScriptedAI
{
public:
    npc_defense_bot_701015(Creature* creature) : ScriptedAI(creature) { }

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

// 701016 - npc_dusty_sporewing_701016
struct npc_dusty_sporewing_701016 : public ScriptedAI
{
public:
    npc_dusty_sporewing_701016(Creature* creature) : ScriptedAI(creature) { }

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

// 701017 - npc_lord_fungo_701017
struct npc_lord_fungo_701017 : public ScriptedAI
{
public:
    npc_lord_fungo_701017(Creature* creature) : ScriptedAI(creature) { }

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
        Talk(0);
        me->CallForHelp(30.0f);
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

// 701018 - npc_fungo_warrior_701018
struct npc_fungo_warrior_701018 : public ScriptedAI
{
public:
    npc_fungo_warrior_701018(Creature* creature) : ScriptedAI(creature) { }

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

// 701019 - npc_sporeling_701019
struct npc_sporeling_701019 : public ScriptedAI
{
public:
    npc_sporeling_701019(Creature* creature) : ScriptedAI(creature) { }

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

// 701020 - npc_plague_doctor_701020
struct npc_plague_doctor_701020 : public ScriptedAI
{
public:
    npc_plague_doctor_701020(Creature* creature) : ScriptedAI(creature) { }

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

void AddSC_TheUnderrot()
{
    RegisterInstanceScript(instance_the_underrot, 1841);
    RegisterCreatureAI(npc_mister_doctor_701000);
    RegisterCreatureAI(npc_mister_slime_701001);
    RegisterCreatureAI(npc_plague_tentacle_701002);
    RegisterCreatureAI(npc_ansid_the_mechanic_701003);
    RegisterCreatureAI(npc_ansid_s_helper_701004);
    RegisterCreatureAI(npc_sporecaller_zancha_701005);
    RegisterCreatureAI(npc_plague_witch_701006);
    RegisterCreatureAI(npc_timmothy_701007);
    RegisterCreatureAI(npc_fetid_maggot_701008);
    RegisterCreatureAI(npc_spore_covered_scavenger_701009);
    RegisterCreatureAI(npc_rockjaw_fungus_flinger_701010);
    RegisterCreatureAI(npc_plague_covered_fungo_701011);
    RegisterCreatureAI(npc_gloomshade_fungi_701012);
    RegisterCreatureAI(npc_blood_ball_701013);
    RegisterCreatureAI(npc_damaged_defense_bot_701014);
    RegisterCreatureAI(npc_defense_bot_701015);
    RegisterCreatureAI(npc_dusty_sporewing_701016);
    RegisterCreatureAI(npc_lord_fungo_701017);
    RegisterCreatureAI(npc_fungo_warrior_701018);
    RegisterCreatureAI(npc_sporeling_701019);
    RegisterCreatureAI(npc_plague_doctor_701020);
}
