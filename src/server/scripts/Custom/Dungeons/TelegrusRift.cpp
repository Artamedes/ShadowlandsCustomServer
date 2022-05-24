#include "ScriptMgr.h"
#include "GameTime.h"
#include "Unit.h"
#include "MotionMaster.h"
#include "ScriptedCreature.h"
#include "Chat.h"
#include "GenericMovementGenerator.h"
#include "../CustomInstanceScript.h"
#include "Conversation.h"
#include "InstanceScenario.h"

struct instance_telegrusrift : public CustomInstanceScript
{
public:
    instance_telegrusrift(InstanceMap* map) : CustomInstanceScript(map)
    {
        ChestSpawn = { 1344.94f, 2836.89f, 63.25f, 0.985017f };
        Quad = { -0.0f, -0.0f, -0.472838f, -0.88115f };
    }

    void SummonChallengeGameObject(bool door) override
    {
        if (door)
        {
            if (auto go = instance->SummonGameObject(MYTHIC_DOOR_4, { 2174.02f, 3324.02f, 54.4243f, 3.39685f }, { -0.0f, -0.0f, -0.712643f, 0.701527f }, 0))
            {
                go->SetGoState(GOState::GO_STATE_READY);
                go->SetFlag(GameObjectFlags::GO_FLAG_NOT_SELECTABLE);
            }
        }
    }

    void OnCompletedCriteriaTree(CriteriaTree const* tree) override
    {
        if (InstanceScenario* instanceScenario = instance->GetInstanceScenario())
        {
            if (auto tree2 = sCriteriaMgr->GetCriteriaTree(300500))
                instanceScenario->IsCompletedCriteriaTree(tree2, nullptr);
        }
    }

    void OnCreatureCreate(Creature* creature) override
    {
        CustomInstanceScript::OnCreatureCreate(creature);

        // Nerf legion dungeon by 5%
        if (!creature->IsDungeonBoss())
            creature->SetMaxHealth(creature->GetMaxHealth() * 0.95);
    }
};

enum TelegrusRiftSpells
{
    BolsteringVisual = 359224,
};

struct npc_void_portal_700615 : public ScriptedAI
{
    public:
        npc_void_portal_700615(Creature* creature) : ScriptedAI(creature) { }

        void InitializeAI() override
        {
            me->SetReactState(REACT_PASSIVE);
        }

        bool m_EncounterStarted = false;

        void OnUnitRelocation(Unit* who) override
        {
            if (who->IsPlayer() && !m_EncounterStarted)
            {
                if (who->GetDistance2d(me) <= 15.0f)
                {
                    Talk(0);
                    DoCastSelf(367668, true); // Visual
                    m_EncounterStarted = true;

                    scheduler.Schedule(3s, [this](TaskContext context)
                    {
                            for (int i = 0; i < 3; ++i)
                            {
                                if (auto summ = DoSummon(700619, me, 5.0f, 30s, TEMPSUMMON_CORPSE_TIMED_DESPAWN))
                                {
                                    summ->CastSpell(summ, BolsteringVisual, true);
                                    summ->GetMotionMaster()->Move(0, MoveTypes::Forward, MOVE_RUN | MOVE_PATHFINDING, 12.0f);
                                }
                            }
                            needKills = 3;
                    });
                }
            }
        }

        void SummonedCreatureDies(Creature* /*summon*/, Unit* /*killer*/)
        {
            if (needKills > 0)
            {
                --needKills;
                if (needKills == 0)
                {
                    switch (phase)
                    {
                        case 0:
                        {
                            Talk(1);
                            DoCastSelf(367668, true); // Visual
                            scheduler.Schedule(3s, [this](TaskContext context)
                                {
                                    for (int i = 0; i < 5; ++i)
                                    {
                                        if (auto summ = DoSummon(700619, me, 5.0f, 30s, TEMPSUMMON_CORPSE_TIMED_DESPAWN))
                                        {
                                            summ->CastSpell(summ, BolsteringVisual, true);
                                            summ->GetMotionMaster()->Move(0, MoveTypes::Forward, MOVE_RUN | MOVE_PATHFINDING, 12.0f);
                                        }
                                    }
                                    needKills = 5;
                                });
                            ++phase;
                            break;
                        }
                        case 1:
                        {
                            Talk(1);
                            DoCastSelf(367668, true); // Visual
                            scheduler.Schedule(3s, [this](TaskContext context)
                                {
                                    for (int i = 0; i < 8; ++i)
                                    {
                                        if (auto summ = DoSummon(700619, me, 5.0f, 30s, TEMPSUMMON_CORPSE_TIMED_DESPAWN))
                                        {
                                            summ->CastSpell(summ, BolsteringVisual, true);
                                            summ->GetMotionMaster()->Move(0, MoveTypes::Forward, MOVE_RUN | MOVE_PATHFINDING, 12.0f);
                                        }
                                    }
                                    needKills = 8;
                                });
                            ++phase;
                            break;
                        }
                        case 2:
                        {
                            Talk(1);
                            DoCastSelf(367668, true); // Visual
                            scheduler.Schedule(3s, [this](TaskContext context)
                                {
                                    for (int i = 0; i < 8; ++i)
                                    {
                                        if (auto summ = DoSummon(700619, me, 5.0f, 30s, TEMPSUMMON_CORPSE_TIMED_DESPAWN))
                                        {
                                            summ->CastSpell(summ, BolsteringVisual, true);
                                            summ->GetMotionMaster()->Move(0, MoveTypes::Forward, MOVE_RUN | MOVE_PATHFINDING, 12.0f);
                                        }
                                    }
                                    needKills = 8;
                                });
                            ++phase;
                            break;
                        }
                        case 3:
                        {
                            // Boss
                            DoCastSelf(367668, true); // Visual
                            scheduler.Schedule(3s, [this](TaskContext context)
                                {
                                    Talk(2);
                                    if (auto summ = DoSummon(700611, me, 5.0f, 30s, TEMPSUMMON_CORPSE_TIMED_DESPAWN)) // Big demon
                                    {
                                        summ->CastSpell(summ, BolsteringVisual, true);
                                        summ->GetMotionMaster()->Move(0, MoveTypes::Forward, MOVE_RUN | MOVE_PATHFINDING, 12.0f);
                                    }
                                });
                            me->DespawnOrUnsummon(5s);
                            break;
                        }
                    }
                }
            }
        }

        void UpdateAI(uint32 diff) override
        {
            scheduler.Update(diff);
        }

        TaskScheduler scheduler;
        uint32 phase = 0;
        uint32 needKills = 0;
};

const Position PathOne[11] = {
    { 2047.390381f, 3349.875732f, 62.898811f },
    { 1997.280151f, 3374.816406f, 61.401329f },
    //{ 1952.777344f, 3606.712646f, 69.262428f },
    { 1956.191772f, 3436.059814f, 77.006310f },
    { 1987.988159f, 3434.807129f, 84.482452f },
    { 2002.079834f, 3402.028320f, 97.690331f },
    { 1984.021118f, 3368.516357f, 101.813820f },
    { 1965.233398f, 3357.171875f, 109.872215f },
    {1937.832153f, 3341.113037f, 117.603920f},
    { 1898.497437f, 3317.688721f, 127.386253f, 3.675009f},
    { 1895.375000f, 3327.320801f, 105.055992f},
    {1895.345459f, 3327.104492f, 98.012650f},
};

using PathOneSize = std::extent<decltype(PathOne)>;

const Position PathOneBack[] = {
    { 1916.98f, 3319.28f, 102.207f, 6.0594f },
    { 1945.08f, 3312.78f, 103.259f, 6.03977f },
    { 1951.81f, 3319.68f, 99.0094f, 0.849593f },
    { 1955.03f, 3336.89f, 92.742f, 1.4321f },
    { 1951.48f, 3357.33f, 84.8967f, 1.7528f },
    { 1951.12f, 3378.13f, 77.6123f, 1.37646f },
    { 1962.12f, 3393.03f, 70.8201f, 0.695786f },
    { 1979.2f, 3395.54f, 64.3825f, 6.09867f },
    { 1996.76f, 3387.4f, 60.2091f, 5.62743f },
    { 2020.52f, 3378.6f, 72.7772f, 5.87614f },
    { 2047.45f, 3372.87f, 80.0509f, 6.10521f },
    { 2052.03f, 3370.71f, 68.736f, 5.30672f },
    { 2052.19f, 3367.61f, 65.2234f, 4.76349f },
    { 2052.21f, 3367.69f, 56.8458f, 4.75367f },
};

using PathOneBackSize = std::extent<decltype(PathOneBack)>;

const Position PathTwo[] = {
    { 1820.89f, 3284.69f, 88.8657f, 3.81899f },
    { 1813.99f, 3278.47f, 95.3469f, 3.87462f },
    { 1804.67f, 3268.1f, 94.1579f, 3.9957f },
    { 1806.98f, 3250.91f, 92.9369f, 5.05926f },
    { 1820.41f, 3241.78f, 93.1791f, 5.77594f },
    { 1830.84f, 3236.54f, 92.6398f, 5.80539f },
    { 1834.05f, 3222.16f, 89.9187f, 4.7451f },
    { 1838.8f, 3209.1f, 89.2911f, 5.05926f },
    { 1838.56f, 3196.32f, 88.0122f, 4.6142f },
    { 1832.12f, 3186.69f, 86.4722f, 4.05133f },
    { 1819.76f, 3183.67f, 85.0598f, 3.37065f },
    { 1804.69f, 3173.14f, 82.1118f, 3.71754f },
    { 1790.2f, 3164.22f, 64.4821f, 3.71754f },
    { 1785.0f, 3160.32f, 57.8196f, 3.79608f },
    { 1782.66f, 3158.2f, 34.2367f, 3.78953f },
};

using PathTwoSize = std::extent<decltype(PathTwo)>;

const Position PathTwoBack[] = {
    { 1799.23f, 3172.19f, 44.1004f, 5.90559f },
    { 1822.13f, 3163.91f, 46.3661f, 5.88595f },
    { 1831.1f, 3160.96f, 50.7946f, 5.96449f },
    { 1852.31f, 3157.97f, 62.6393f, 6.17066f },
    { 1863.16f, 3161.17f, 68.6489f, 0.309627f },
    { 1862.73f, 3169.02f, 70.6991f, 1.62517f },
    { 1851.36f, 3187.17f, 75.9844f, 2.40729f },
    { 1834.84f, 3194.53f, 80.4101f, 2.72473f },
    { 1816.64f, 3191.81f, 83.6555f, 3.28432f },
    { 1794.1f, 3183.45f, 87.5056f, 3.7392f },
    { 1794.15f, 3167.53f, 91.053f, 4.71767f },
    { 1805.87f, 3153.22f, 93.1858f, 5.48998f },
    { 1813.65f, 3150.71f, 93.7036f, 5.97758f },
    { 1828.29f, 3154.43f, 95.3322f, 0.253995f },
    { 1833.81f, 3161.75f, 96.9289f, 0.915038f },
    { 1833.86f, 3183.14f, 102.852f, 1.58263f },
    { 1835.21f, 3214.03f, 113.423f, 1.54008f },
    { 1831.53f, 3232.0f, 116.654f, 1.77243f },
    { 1831.16f, 3251.53f, 119.966f, 1.58917f },
    { 1832.68f, 3271.22f, 118.516f, 1.49754f },
    { 1834.23f, 3282.05f, 114.375f, 1.42882f },
    { 1835.96f, 3292.2f, 106.755f, 1.37319f },
    { 1835.81f, 3292.11f, 92.3892f, 1.37319f },
};

using PathTwoBackSize = std::extent<decltype(PathTwoBack)>;



const Position PathThree[] = {
    { 1521.97f, 2969.52f, 23.6317f, 2.764f },
    { 1499.97f, 2972.3f, 24.4476f, 2.9898f },
    { 1478.34f, 2975.68f, 32.2476f, 2.98653f },
    { 1469.29f, 2995.21f, 40.9894f, 1.90333f },
    { 1481.74f, 3009.89f, 45.698f, 0.852865f },
    { 1499.54f, 3009.38f, 51.2359f, 6.19357f },
    { 1516.66f, 2997.38f, 58.3929f, 5.59143f },
    { 1523.04f, 2982.17f, 64.2227f, 5.08747f },
    { 1516.04f, 2963.81f, 71.4935f, 4.30862f },
    { 1500.91f, 2952.36f, 77.2028f, 3.78174f },
    { 1476.98f, 2942.86f, 84.578f, 3.49049f },
    { 1450.97f, 2933.21f, 88.2706f, 3.52322f },
    { 1433.89f, 2921.19f, 90.5315f, 3.75556f },
    { 1408.32f, 2899.05f, 89.1762f, 3.87665f },
    { 1402.68f, 2888.08f, 85.7529f, 4.26607f },
    { 1397.79f, 2873.28f, 80.9456f, 4.3937f },
    { 1392.68f, 2863.94f, 71.9221f, 4.17772f },
    { 1392.68f, 2863.95f, 57.0672f, 4.18753f },
};

using PathThreeSize = std::extent<decltype(PathThree)>;

const Position PathThreeBack[] = {
    { 1422.82f, 2873.95f, 67.9642f, 5.48344f },
    { 1450.55f, 2861.56f, 68.8554f, 5.86305f },
    { 1475.67f, 2857.19f, 71.1593f, 6.16412f },
    { 1496.54f, 2867.04f, 73.7421f, 0.463442f },
    { 1500.42f, 2892.4f, 76.0684f, 1.41901f },
    { 1485.22f, 2910.07f, 76.4404f, 2.35822f },
    { 1475.47f, 2915.99f, 61.5525f, 2.30586f },
    { 1483.39f, 2927.34f, 52.8039f, 0.865958f },
    { 1527.1f, 2974.82f, 42.3685f, 0.826688f },
    { 1533.31f, 2981.56f, 40.3473f, 0.826688f },
    { 1533.1f, 2981.4f, 16.7373f, 0.898683f },
};

using PathThreeBackSize = std::extent<decltype(PathThreeBack)>;

struct npc_portal_to_next_700628 : public ScriptedAI
{

    public:
        npc_portal_to_next_700628(Creature* creature) : ScriptedAI(creature) { }

        void UpdateAI(uint32 diff) override
        {
            scheduler.Update(diff);

            auto now = GameTime::Now();

            std::list<Unit*> unitsInRange;
            me->GetFriendlyUnitListInRange(unitsInRange, 2.0f, true);
            unitsInRange.remove_if([this](Unit* unit) {
                return !unit->IsPlayer() || m_UnitCD.count(unit->GetGUID().GetCounter()) || unit->IsInCombat();
            });

            for (auto unit : unitsInRange)
            {
                m_UnitCD[unit->GetGUID().GetCounter()] = now + Seconds(2);
                unit->Dismount();
                unit->RemoveAurasByShapeShift();

                GenericMovementGenerator* result = nullptr;

                switch (me->GetSpawnId())
                {
                    case 1051811:
                        result = unit->GetMotionMaster()->MoveSmoothPath(1, PathOne, PathOneSize::value, false, true, 80.0f);
                        break;
                    case 1051815:
                        result = unit->GetMotionMaster()->MoveSmoothPath(1, PathOneBack, PathOneBackSize::value, false, true, 80.0f);
                        break;
                    case 1051816:
                        result = unit->GetMotionMaster()->MoveSmoothPath(1, PathTwo, PathTwoSize::value, false, true, 80.0f);
                        break;
                    case 1051817:
                        result = unit->GetMotionMaster()->MoveSmoothPath(1, PathTwoBack, PathTwoBackSize::value, false, true, 80.0f);
                        break;
                    case 1051818:
                        result = unit->GetMotionMaster()->MoveSmoothPath(1, PathThree, PathThreeSize::value, false, true, 80.0f);
                        break;
                    case 1051821:
                        result = unit->GetMotionMaster()->MoveSmoothPath(1, PathThreeBack, PathThreeBackSize::value, false, true, 80.0f);
                        break;
                }

                if (!result)
                {
                    ChatHandler(unit->ToPlayer()).PSendSysMessage("Fix %u", me->GetSpawnId());
                    break;
                }

                unit->SetDisplayId(76239);
                unit->CastSpell(unit, 163091, true);
                result->callbackFunc = [this, unit]()
                {
                    if (unit)
                    {
                        unit->DeMorph();
                        //unit->SetSpeed(MOVE_RUN, oldSpeed);
                        unit->RemoveAurasDueToSpell(163091);
                    }
                };

            }


            for (auto it = m_UnitCD.cbegin(); it != m_UnitCD.cend();)
            {
                if (now >= it->second)
                {
                    m_UnitCD.erase(it++);
                }
                else
                {
                    ++it;
                }
            }
        }

        TaskScheduler scheduler;
        std::unordered_map<ObjectGuid::LowType, TimePoint> m_UnitCD;
};


// 700607 - npc_void_reaper_700607
struct npc_void_reaper_700607 : public ScriptedAI
{
public:
    npc_void_reaper_700607(Creature* creature) : ScriptedAI(creature)
    {
        ApplyAllImmunities(true);
    }

    void InitializeAI() override
    {
        /// TODO: Fill this function
        DoCastSelf(335134); // Void Channel
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
// 700630 - npc_demon_monster_trigger_700630
struct npc_demon_monster_trigger_700630 : public ScriptedAI
{
public:
    npc_demon_monster_trigger_700630(Creature* creature) : ScriptedAI(creature) { }

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

    bool m_SummonedBoss = false;

    void OnUnitRelocation(Unit* who) override
    {
        /// TODO: Fill this function
        if (who->IsPlayer() && !m_SummonedBoss && who->GetDistance2d(me) <= 20.0f)
        {
            m_SummonedBoss = true;

            if (auto riftPortal = me->FindNearestCreature(700605, 50.0f))
                riftPortal->DespawnOrUnsummon();

            me->DespawnOrUnsummon(5s);
            DoSummon(700620, { 1661.6f, 3073.82f, 31.3123f, 0.556322f });
        }
    }

    TaskScheduler scheduler;
    EventMap events;
};

// 700630 - npc_demon_monster_trigger_700631
struct npc_demon_monster_trigger_700631 : public ScriptedAI
{
public:
    npc_demon_monster_trigger_700631(Creature* creature) : ScriptedAI(creature) { }

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

    bool m_SummonedBoss = false;

    void OnUnitRelocation(Unit* who) override
    {
        /// TODO: Fill this function
        if (who->IsPlayer() && !m_SummonedBoss && who->GetDistance2d(me) <= 10.0f)
        {
            m_SummonedBoss = true;
            DoSummon(700626, { 1607.15f, 3053.69f, 27.1007f, 0.40906f });
            me->DespawnOrUnsummon(5s);
            if (auto riftPortal = me->FindNearestCreature(700605, 50.0f))
                riftPortal->DespawnOrUnsummon();
        }
    }

    TaskScheduler scheduler;
    EventMap events;
};

// 700620 - npc_agony_700620
struct npc_agony_700620 : public ScriptedAI
{
public:
    npc_agony_700620(Creature* creature) : ScriptedAI(creature)
    {
        ApplyAllImmunities(true);
    }

    void InitializeAI() override
    {
        Talk(0);
    }

    void Reset() override
    {
        /// TODO: Fill this function
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

    void OnUnitRelocation(Unit* who) override
    {
        /// TODO: Fill this function
    }

    TaskScheduler scheduler;
    EventMap events;
};


struct npc_final_boss_void_portal_700632 : public ScriptedAI
{
    public:
        npc_final_boss_void_portal_700632(Creature* creature) : ScriptedAI(creature) { }

        void InitializeAI() override
        {
            me->SetReactState(REACT_PASSIVE);
        }

        bool m_EncounterStarted = false;

        void OnUnitRelocation(Unit* who) override
        {
            if (who->IsPlayer() && !m_EncounterStarted)
            {
                if (who->GetDistance2d(me) <= 15.0f)
                {
                    Talk(0);
                    DoCastSelf(367668, true); // Visual
                    m_EncounterStarted = true;

                    scheduler.Schedule(3s, [this](TaskContext context)
                    {
                            for (int i = 0; i < 3; ++i)
                            {
                                if (auto summ = DoSummon(700619, me, 5.0f, 30s, TEMPSUMMON_CORPSE_TIMED_DESPAWN))
                                {
                                    summ->CastSpell(summ, BolsteringVisual, true);
                                    summ->GetMotionMaster()->Move(0, MoveTypes::Forward, MOVE_RUN | MOVE_PATHFINDING, 12.0f);
                                }
                            }
                            needKills = 3;
                    });
                }
            }
        }

        void SummonedCreatureDies(Creature* /*summon*/, Unit* /*killer*/)
        {
            if (needKills > 0)
            {
                --needKills;
                if (needKills == 0)
                {
                    switch (phase)
                    {
                        case 0:
                        {
                            Talk(1);
                            DoCastSelf(367668, true); // Visual
                            scheduler.Schedule(3s, [this](TaskContext context)
                                {
                                    for (int i = 0; i < 5; ++i)
                                    {
                                        if (auto summ = DoSummon(700619, me, 5.0f, 30s, TEMPSUMMON_CORPSE_TIMED_DESPAWN))
                                        {
                                            summ->CastSpell(summ, BolsteringVisual, true);
                                            summ->GetMotionMaster()->Move(0, MoveTypes::Forward, MOVE_RUN | MOVE_PATHFINDING, 12.0f);
                                        }
                                    }
                                    needKills = 5;
                                });
                            ++phase;
                            break;
                        }
                        case 1:
                        {
                            Talk(1);
                            DoCastSelf(367668, true); // Visual
                            scheduler.Schedule(3s, [this](TaskContext context)
                                {
                                    for (int i = 0; i < 8; ++i)
                                    {
                                        if (auto summ = DoSummon(700619, me, 5.0f, 30s, TEMPSUMMON_CORPSE_TIMED_DESPAWN))
                                        {
                                            summ->CastSpell(summ, BolsteringVisual, true);
                                            summ->GetMotionMaster()->Move(0, MoveTypes::Forward, MOVE_RUN | MOVE_PATHFINDING, 12.0f);
                                        }
                                    }
                                    needKills = 8;
                                });
                            ++phase;
                            break;
                        }
                        case 2:
                        {
                            Talk(1);
                            DoCastSelf(367668, true); // Visual
                            scheduler.Schedule(3s, [this](TaskContext context)
                                {
                                    for (int i = 0; i < 8; ++i)
                                    {
                                        if (auto summ = DoSummon(700619, me, 5.0f, 30s, TEMPSUMMON_CORPSE_TIMED_DESPAWN))
                                        {
                                            summ->CastSpell(summ, BolsteringVisual, true);
                                            summ->GetMotionMaster()->Move(0, MoveTypes::Forward, MOVE_RUN | MOVE_PATHFINDING, 12.0f);
                                        }
                                    }
                                    needKills = 8;
                                });
                            ++phase;
                            break;
                        }
                        case 3:
                        {
                            // Boss
                            DoCastSelf(367668, true); // Visual
                            scheduler.Schedule(3s, [this](TaskContext context)
                                {
                                    Talk(2);
                                    if (auto summ = DoSummon(700611, me, 5.0f, 30s, TEMPSUMMON_CORPSE_TIMED_DESPAWN)) // Big demon
                                    {
                                        summ->CastSpell(summ, BolsteringVisual, true);
                                        summ->GetMotionMaster()->Move(0, MoveTypes::Forward, MOVE_RUN | MOVE_PATHFINDING, 12.0f);
                                    }
                                    needKills = 1;
                                });
                            ++phase;
                            break;
                        }
                        case 4:
                        {
                            // Boss
                            DoCastSelf(367668, true); // Visual
                            scheduler.Schedule(3s, [this](TaskContext context)
                                {
                                    Talk(2);
                                    if (auto summ = DoSummon(700616, me, 5.0f, 30s, TEMPSUMMON_CORPSE_TIMED_DESPAWN)) // Big demon
                                    {
                                        summ->CastSpell(summ, BolsteringVisual, true);
                                        summ->GetMotionMaster()->Move(0, MoveTypes::Forward, MOVE_RUN | MOVE_PATHFINDING, 3.0f);
                                    }
                                    needKills = 1;
                                });
                            ++phase;
                            me->DespawnOrUnsummon(5s);
                            break;
                        }
                    }
                }
            }
        }

        void UpdateAI(uint32 diff) override
        {
            scheduler.Update(diff);
        }

        TaskScheduler scheduler;
        uint32 phase = 0;
        uint32 needKills = 0;
};

// 700616 - npc_sunshine_700616
struct npc_sunshine_700616 : public ScriptedAI
{
public:
    npc_sunshine_700616(Creature* creature) : ScriptedAI(creature)
    {
        ApplyAllImmunities(true);
    }

    void InitializeAI() override
    {
        /// TODO: Fill this function
        Talk(0);
    }

    void Reset() override
    {
        /// TODO: Fill this function
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

    void OnUnitRelocation(Unit* who) override
    {
        /// TODO: Fill this function
    }

    TaskScheduler scheduler;
    EventMap events;
};
// 700600 - npc_vivian_700600
struct npc_vivian_700600 : public ScriptedAI
{
public:
    npc_vivian_700600(Creature* creature) : ScriptedAI(creature) { }

    bool OnGossipHello(Player* player) override
    {
        ClearGossipMenuFor(player);
        player->PrepareQuestMenu(me->GetGUID());
        SendGossipMenuFor(player, 700600, me);
        return true;
    }

    void InitializeAI() override
    {
        /// TODO: Fill this function
        DoCastSelf(349927);
        me->SetEmoteState(Emote::EMOTE_STATE_READY1H);
        scheduler.Schedule(1s, [this](TaskContext context)
            {
                DoCastSelf(349927);
            });
    }

    void Reset() override
    {
        /// TODO: Fill this function
        DoCastSelf(349927);

        scheduler.Schedule(1s, [this](TaskContext context)
            {
                DoCastSelf(349927);
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

class telegros_rift_playerscript : public PlayerScript
{
public:
    telegros_rift_playerscript() : PlayerScript("telegros_rift_playerscript") { }


    void OnQuestStatusChange(Player* player, uint32 questId)
    {
        if (player->GetMapId() != 1622)
            return;

        if (questId == 700025 && player->GetQuestStatus(questId) == QUEST_STATUS_COMPLETE)
        {
            Conversation::CreateConversation(700306, player, *player, player->GetGUID());
        }
    }
};


void AddSC_TelegrusRift()
{
    RegisterCreatureAI(npc_void_portal_700615);
    RegisterCreatureAI(npc_portal_to_next_700628);
    RegisterCreatureAI(npc_void_reaper_700607);
    RegisterCreatureAI(npc_demon_monster_trigger_700630);
    RegisterCreatureAI(npc_demon_monster_trigger_700631);
    RegisterCreatureAI(npc_agony_700620);
    RegisterCreatureAI(npc_final_boss_void_portal_700632);
    RegisterCreatureAI(npc_sunshine_700616);
    RegisterCreatureAI(npc_vivian_700600);

    RegisterInstanceScript(instance_telegrusrift, 1622);
    new telegros_rift_playerscript();
}
