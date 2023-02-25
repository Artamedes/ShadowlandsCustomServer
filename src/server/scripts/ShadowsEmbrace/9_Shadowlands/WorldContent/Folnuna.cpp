#include "ScriptMgr.h"
#include "ScriptedCreature.h"

enum Folnuna
{
    LegionPortal = 236791,
    SpellFirePortal = 99564,
    TimePortal = 282513,

    // Bosses
    SpawnOfBethilac = 730300,
    PuppyOfNerzhul = 730301,
    EmpoweredLivingScorch = 730303,
    Judo                = 730304,
    Nudo                = 730305,
    Kudo                = 730306,
    Dudo                = 730307,
    Pudo                = 730308,
    RhyolithOffspring   = 730311,
    SonOfRhyolith       = 730312,
    Baleroc             = 730313,
    ScorchedBoneSlayer  = 730314,
    
    // Trash
    EmpoweredFirelandsScorpion = 730302,
    MoltenLord = 730309,
    LivingSpiderling = 730310,
};

const Position CenterSpawnPos = { 4397.08f, 6486.88f, 40.3439f, 1.18831f };

// 730315 - npc_sabrina_730315
struct npc_sabrina_730315 : public ScriptedAI
{
public:
    npc_sabrina_730315(Creature* creature) : ScriptedAI(creature), summons(creature) { }

    void InitializeAI()
    {
        me->setActive(true);
        scheduler.Schedule(5s, [this](TaskContext context)
        {
            DoSummon(SpawnOfBethilac, CenterSpawnPos, 5s, TempSummonType::TEMPSUMMON_CORPSE_TIMED_DESPAWN);
        });
    }

    bool OnGossipHello(Player* player)
    {
        ClearGossipMenuFor(player);
        player->PrepareQuestMenu(me->GetGUID());
        SendGossipMenuFor(player, me->GetEntry(), me);
        return true;
    }

    void JustSummoned(Creature* summ) override
    {
        summons.Summon(summ);
    }

    void SummonedCreatureDespawn(Creature* summoned) override
    {
        summons.Despawn(summoned);
    }

    void SummonedCreatureDies(Creature* creature, Unit* killer) override
    {
        phase++;

        if (phase > 7)
            phase = 0;

        scheduler.Schedule(8s, [this](TaskContext context)
        {
            switch (phase)
            {
                case 0:
                    DoSummon(SpawnOfBethilac, CenterSpawnPos, 5s, TempSummonType::TEMPSUMMON_CORPSE_TIMED_DESPAWN);
                    break;
                case 1:
                    DoSummon(PuppyOfNerzhul, CenterSpawnPos, 5s, TempSummonType::TEMPSUMMON_CORPSE_TIMED_DESPAWN);
                    break;
                case 2:
                    DoSummon(Judo, CenterSpawnPos, 5s, TempSummonType::TEMPSUMMON_CORPSE_TIMED_DESPAWN);
                    break;
                case 3:
                    DoSummon(EmpoweredLivingScorch, CenterSpawnPos, 5s, TempSummonType::TEMPSUMMON_CORPSE_TIMED_DESPAWN);
                    break;
                case 4:
                    DoSummon(RhyolithOffspring, CenterSpawnPos, 5s, TempSummonType::TEMPSUMMON_CORPSE_TIMED_DESPAWN);
                    break;
                case 5:
                    DoSummon(SonOfRhyolith, CenterSpawnPos, 5s, TempSummonType::TEMPSUMMON_CORPSE_TIMED_DESPAWN);
                    break;
                case 6:
                    DoSummon(Baleroc, CenterSpawnPos, 5s, TempSummonType::TEMPSUMMON_CORPSE_TIMED_DESPAWN);
                    break;
                case 7:
                    DoSummon(ScorchedBoneSlayer, CenterSpawnPos, 5s, TempSummonType::TEMPSUMMON_CORPSE_TIMED_DESPAWN);
                    break;
            }
        });
    }

    void UpdateAI(uint32 diff) override
    {
        scheduler.Update(diff);
    }

    SummonList summons;
    TaskScheduler scheduler;
    EventMap events;
    uint32 phase = 0;
};

struct npc_folnuna_base_ai : public ScriptedAI
{
public:
    npc_folnuna_base_ai(Creature* creature) : ScriptedAI(creature) { }

    void InitializeAI() override
    {
        me->setActive(true);
        me->SetReactState(REACT_PASSIVE);
        me->SetUnitFlag(UnitFlags::UNIT_FLAG_NON_ATTACKABLE);
        me->SetUnitFlag(UnitFlags::UNIT_FLAG_IMMUNE_TO_PC);
        DoCastSelf(Folnuna::TimePortal);
        me->GetMotionMaster()->Move(0, MoveTypes::Forward, MOVE_PATHFINDING | MOVE_WALK_MODE, 5.0f);

        scheduler.Schedule(1500ms, [this](TaskContext context)
        {
            me->SetReactState(REACT_AGGRESSIVE);
            me->RemoveAurasDueToSpell(Folnuna::TimePortal);
            me->HandleEmoteCommand(Emote::EMOTE_ONESHOT_BATTLE_ROAR);
            me->RemoveUnitFlag(UnitFlags::UNIT_FLAG_NON_ATTACKABLE);
            me->RemoveUnitFlag(UnitFlags::UNIT_FLAG_IMMUNE_TO_PC);
        });
    }

    void UpdateAI(uint32 diff) override
    {
        scheduler.Update(diff);

        if (!UpdateVictim())
            return;

        events.Update(diff);

        if (uint32 eventId = events.ExecuteEvent())
        {
            HandleCombatEvent(eventId);
        }
        DoMeleeAttackIfReady();
    }

    virtual void HandleCombatEvent(uint32 eventId)
    {

    }

    TaskScheduler scheduler;
    EventMap events;
};

// 730300 - npc_spawn_of_beth_tilac_730300
struct npc_spawn_of_beth_tilac_730300 : public npc_folnuna_base_ai
{
public:
    npc_spawn_of_beth_tilac_730300(Creature* creature) : npc_folnuna_base_ai(creature) { }

};
// 730301 - npc_puppy_of_ner_zul_730301
struct npc_puppy_of_ner_zul_730301 : public npc_folnuna_base_ai
{
public:
    npc_puppy_of_ner_zul_730301(Creature* creature) : npc_folnuna_base_ai(creature) { }

};

// 730302 - npc_empowered_firelands_scorpion_730302
struct npc_empowered_firelands_scorpion_730302 : public npc_folnuna_base_ai
{
public:
    npc_empowered_firelands_scorpion_730302(Creature* creature) : npc_folnuna_base_ai(creature) { }

};
// 730303 - npc_empowered_living_scorch_730303
struct npc_empowered_living_scorch_730303 : public npc_folnuna_base_ai
{
public:
    npc_empowered_living_scorch_730303(Creature* creature) : npc_folnuna_base_ai(creature) { }


    TaskScheduler scheduler;
    EventMap events;
};

// 730304 - npc_judo_730304
struct npc_judo_730304 : public npc_folnuna_base_ai
{
public:
    npc_judo_730304(Creature* creature) : npc_folnuna_base_ai(creature) { }


    TaskScheduler scheduler;
    EventMap events;
};
// 730305 - npc_nudo_730305
struct npc_nudo_730305 : public npc_folnuna_base_ai
{
public:
    npc_nudo_730305(Creature* creature) : npc_folnuna_base_ai(creature) { }


    TaskScheduler scheduler;
    EventMap events;
};

// 730306 - npc_kudo_730306
struct npc_kudo_730306 : public npc_folnuna_base_ai
{
public:
    npc_kudo_730306(Creature* creature) : npc_folnuna_base_ai(creature) { }


    TaskScheduler scheduler;
    EventMap events;
};

// 730307 - npc_dudo_730307
struct npc_dudo_730307 : public npc_folnuna_base_ai
{
public:
    npc_dudo_730307(Creature* creature) : npc_folnuna_base_ai(creature) { }


    TaskScheduler scheduler;
    EventMap events;
};

// 730308 - npc_pudo_730308
struct npc_pudo_730308 : public npc_folnuna_base_ai
{
public:
    npc_pudo_730308(Creature* creature) : npc_folnuna_base_ai(creature) { }


    TaskScheduler scheduler;
    EventMap events;
};

// 730309 - npc_molten_lord_730309
struct npc_molten_lord_730309 : public npc_folnuna_base_ai
{
public:
    npc_molten_lord_730309(Creature* creature) : npc_folnuna_base_ai(creature) { }


    TaskScheduler scheduler;
    EventMap events;
};

// 730310 - npc_living_spiderling_730310
struct npc_living_spiderling_730310 : public npc_folnuna_base_ai
{
public:
    npc_living_spiderling_730310(Creature* creature) : npc_folnuna_base_ai(creature) { }


    TaskScheduler scheduler;
    EventMap events;
};

// 730311 - npc_rhyolith_offspring_730311
struct npc_rhyolith_offspring_730311 : public npc_folnuna_base_ai
{
public:
    npc_rhyolith_offspring_730311(Creature* creature) : npc_folnuna_base_ai(creature) { }


    TaskScheduler scheduler;
    EventMap events;
};

// 730312 - npc_son_of_rhyolith_730312
struct npc_son_of_rhyolith_730312 : public npc_folnuna_base_ai
{
public:
    npc_son_of_rhyolith_730312(Creature* creature) : npc_folnuna_base_ai(creature) { }


    TaskScheduler scheduler;
    EventMap events;
};

// 730313 - npc_baleroc_730313
struct npc_baleroc_730313 : public npc_folnuna_base_ai
{
public:
    npc_baleroc_730313(Creature* creature) : npc_folnuna_base_ai(creature) { }


    TaskScheduler scheduler;
    EventMap events;
};

// 730314 - npc_scorched_bone_slayer_730314
struct npc_scorched_bone_slayer_730314 : public npc_folnuna_base_ai
{
public:
    npc_scorched_bone_slayer_730314(Creature* creature) : npc_folnuna_base_ai(creature) { }


    TaskScheduler scheduler;
    EventMap events;
};

void AddSC_Folnuna()
{
    RegisterCreatureAI(npc_sabrina_730315);
    RegisterCreatureAI(npc_spawn_of_beth_tilac_730300);
    RegisterCreatureAI(npc_puppy_of_ner_zul_730301);
    RegisterCreatureAI(npc_empowered_firelands_scorpion_730302);
    RegisterCreatureAI(npc_scorched_bone_slayer_730314);
    RegisterCreatureAI(npc_baleroc_730313);
    RegisterCreatureAI(npc_son_of_rhyolith_730312);
    RegisterCreatureAI(npc_rhyolith_offspring_730311);
    RegisterCreatureAI(npc_living_spiderling_730310);
    RegisterCreatureAI(npc_pudo_730308);
    RegisterCreatureAI(npc_molten_lord_730309);
    RegisterCreatureAI(npc_dudo_730307);
    RegisterCreatureAI(npc_kudo_730306);
    RegisterCreatureAI(npc_empowered_living_scorch_730303);
    RegisterCreatureAI(npc_judo_730304);
    RegisterCreatureAI(npc_nudo_730305);
}
// UPDATE creature_template set ScriptName = 'npc_puppy_of_ner_zul_730301' WHERE entry = 730301;
// UPDATE creature_template set ScriptName = 'npc_empowered_firelands_scorpion_730302' WHERE entry = 730302;
// UPDATE creature_template set ScriptName = 'npc_scorched_bone_slayer_730314' WHERE entry = 730314;
// UPDATE creature_template set ScriptName = 'npc_baleroc_730313' WHERE entry = 730313;
// UPDATE creature_template set ScriptName = 'npc_son_of_rhyolith_730312' WHERE entry = 730312;
// UPDATE creature_template set ScriptName = 'npc_rhyolith_offspring_730311' WHERE entry = 730311;
// UPDATE creature_template set ScriptName = 'npc_living_spiderling_730310' WHERE entry = 730310;
// UPDATE creature_template set ScriptName = 'npc_molten_lord_730309' WHERE entry = 730309;
// UPDATE creature_template set ScriptName = 'npc_pudo_730308' WHERE entry = 730308;
// UPDATE creature_template set ScriptName = 'npc_dudo_730307' WHERE entry = 730307;
// UPDATE creature_template set ScriptName = 'npc_kudo_730306' WHERE entry = 730306;
// UPDATE creature_template set ScriptName = 'npc_nudo_730305' WHERE entry = 730305;
// UPDATE creature_template set ScriptName = 'npc_judo_730304' WHERE entry = 730304;
// UPDATE creature_template set ScriptName = 'npc_empowered_living_scorch_730303' WHERE entry = 730303;
