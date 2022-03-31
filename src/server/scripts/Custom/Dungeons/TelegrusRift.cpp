#include "ScriptMgr.h"
#include "GameTime.h"
#include "Unit.h"
#include "MotionMaster.h"
#include "ScriptedCreature.h"
#include "GenericMovementGenerator.h"

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

        void MoveInLineOfSight(Unit* who) override
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
                                    if (auto summ = DoSummon(700607, me, 5.0f, 30s, TEMPSUMMON_CORPSE_TIMED_DESPAWN))
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
                return !unit->IsPlayer() || m_UnitCD.count(unit->GetGUID().GetCounter());
            });

            for (auto unit : unitsInRange)
            {
                m_UnitCD[unit->GetGUID().GetCounter()] = now + Seconds(2);

                static Position points[11] = {
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

                unit->SetDisplayId(76239);
               // auto oldSpeed = unit->GetSpeed(MOVE_RUN);
               // unit->SetSpeed(MOVE_RUN, 10.0f);
                auto result = unit->GetMotionMaster()->MoveSmoothPath(1, points, 11, false, true, 80.0f);
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

void AddSC_TelegrusRift()
{
    RegisterCreatureAI(npc_void_portal_700615);
    RegisterCreatureAI(npc_portal_to_next_700628);
}
