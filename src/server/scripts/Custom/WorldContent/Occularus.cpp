#include "ScriptMgr.h"
#include "Player.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "GossipDef.h"
#include "SpellAuras.h"
#include "MotionMaster.h"

const std::vector<Position> EnemySpawnPoints
{
    { -9911.87f, 2671.7f, -1.43507f, 1.68529f },
    { -9934.11f, 2678.42f, 0.640097f, 1.70493f },
    { -9925.56f, 2700.49f, 2.18097f, 1.43331f },
    { -9929.86f, 2725.45f, 3.90477f, 1.79329f },
    { -9946.35f, 2740.18f, 6.05249f, 2.2907f },
    { -9902.78f, 2733.54f, 2.44064f, 2.81758f },
    { -9882.05f, 2729.24f, 1.49485f, 2.59505f },
    { -9856.57f, 2723.89f, -0.174483f, 2.09763f },
    { -9874.09f, 2702.97f, 0.459886f, 2.91248f },
    { -9898.86f, 2693.5f, -0.545337f, 2.71613f },
    { -9912.99f, 2702.63f, 1.17556f, 2.52633f },
    { -9891.82f, 2712.21f, 0.453974f, 2.05182f },
    { -9917.61f, 2715.25f, 2.39206f, 2.80776f },
    { -9936.25f, 2696.85f, 2.9244f, 2.67686f },
    { -9914.24f, 2671.42f, -1.33583f, 0.922805f },
    { -9910.51f, 2693.7f, -0.00680418f, 2.41833f },
    { -9910.3f, 2715.62f, 1.71301f, 2.60159f },
    { -9888.95f, 2711.24f, 0.384617f, 2.53942f },
    { -9899.78f, 2716.68f, 0.987552f, 2.83067f },
    { -9911.72f, 2712.32f, 1.65005f, 3.12192f },
    { -9923.72f, 2708.31f, 2.59187f, 2.66377f },
    { -9908.52f, 2697.57f, 0.32928f, 0.824632f },
    { -9887.89f, 2688.67f, -0.531976f, 2.55251f },
    { -9887.02f, 2704.06f, -0.0135609f, 2.49688f },
    { -9896.68f, 2709.39f, 0.466785f, 2.71286f },
};

const std::vector<uint32> EnemySpawnEntries
{
    730101,
    730102,
    730103,
    730104,
    730105,
    730106,
    730107,
    730108,
};

enum OccurlarusSpells
{
    PortalIn = 360358,
    Hide = 362717,
    Frozen = 335952,
};

struct npc_jaina_proudmoore_730100 : public ScriptedAI
{
    public:
        npc_jaina_proudmoore_730100(Creature* creature) : ScriptedAI(creature), summons(creature) { }

        SummonList summons;

        void JustSummoned(Creature* creature) override
        {
            summons.Summon(creature);
        }

        bool _setup = false;

        void InitializeAI() override
        {
            if (!_setup)
            {
                _setup = true;

                for (int i = 0; i < 15; ++i)
                    SummonNextEnemy();
            }
        }

        bool OnGossipHello(Player* player) override
        {
            ClearGossipMenuFor(player);
            player->PrepareQuestMenu(me->GetGUID());
            SendGossipMenuFor(player, 730100, me);
            return true;
        }

        void SummonedCreatureDespawn(Creature* summon) override
        {
            if (summon->isDead())
                return;

            scheduler.Schedule(2s, 5s, [this](TaskContext context)
                {
                    SummonNextEnemy();
                });
        }

        void SummonedCreatureDies(Creature* summon, Unit* /*killer*/) override
        {
            scheduler.Schedule(2s, 5s, [this](TaskContext context)
                {
                    SummonNextEnemy();
                });
        }

        void UpdateAI(uint32 diff) override
        {
            if (!me->GetCurrentSpell(CurrentSpellTypes::CURRENT_CHANNELED_SPELL))
                DoCast(342538);

            scheduler.Update(diff);
        }

        void SummonNextEnemy()
        {
            if (EnemyQueue.empty())
            {
                std::vector<uint32> vecCopy = EnemySpawnEntries;
                Trinity::Containers::RandomShuffle(vecCopy);

                for (uint32 entry : vecCopy)
                    EnemyQueue.push(entry);
            }

            if (EnemyPosQue.empty())
            {
                std::vector<Position> vecCopy = EnemySpawnPoints;
                Trinity::Containers::RandomShuffle(vecCopy);

                for (auto entry : vecCopy)
                    EnemyPosQue.push(entry);
            }

            uint32 nextEntry = EnemyQueue.front();
            auto pos = EnemyPosQue.front();

            DoSummon(nextEntry, pos);

            EnemyQueue.pop();
            EnemyPosQue.pop();
        }

        TaskScheduler scheduler;
        std::queue<uint32> EnemyQueue;
        std::queue<Position> EnemyPosQue;
};

struct npc_occularus_coldheart_generic : public ScriptedAI
{
    public:
        npc_occularus_coldheart_generic(Creature* creature) : ScriptedAI(creature) { }

        void InitializeAI() override
        {
            me->SetReactState(REACT_PASSIVE);
            me->SetUnitFlag(UnitFlags::UNIT_FLAG_UNINTERACTIBLE);
            me->SetUnitFlag(UnitFlags::UNIT_FLAG_NON_ATTACKABLE);

            scheduler.Schedule(100ms, [this](TaskContext context)
            {
                DoCastSelf(PortalIn);
                scheduler.Schedule(100ms, [this](TaskContext context)
                {
                    me->GetMotionMaster()->MovePoint(1, { -9949.61f, 2741.01f, 6.5752f, 2.41506f });
                    scheduler.Schedule(1s, [this](TaskContext context)
                    {
                        me->RemoveUnitFlag(UnitFlags::UNIT_FLAG_UNINTERACTIBLE);
                        me->RemoveUnitFlag(UnitFlags::UNIT_FLAG_NON_ATTACKABLE);
                        me->GetMotionMaster()->Clear();

                        if (auto aura = me->AddAura(Frozen))
                        {
                            aura->SetMaxDuration(3600000);
                            aura->SetDuration(3600000);
                        }
                    });
                });
            });
        }

        void JustDied(Unit* who) override
        {
            UnitList list;

            std::list<Player*> players;
            Trinity::AnyPlayerInObjectRangeCheck checker(me, 50.0f);
            Trinity::PlayerListSearcher<Trinity::AnyPlayerInObjectRangeCheck> searcher(me, players, checker);
            Cell::VisitWorldObjects(me, searcher, 50.0f);

            for (auto u : players)
            {
                if (u && me->isTappedBy(u))
                    u->KilledMonsterCredit(720001, me->GetGUID());
            }
        }

        void JustEngagedWith(Unit* who) override
        {
            scheduler.CancelAll();
            me->SetReactState(REACT_AGGRESSIVE);
            me->RemoveAurasDueToSpell(Frozen);
        }

        void UpdateAI(uint32 diff) override
        {
            scheduler.Update(diff);

            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }

        TaskScheduler scheduler;
};

void AddSC_Occularus()
{
    RegisterCreatureAI(npc_jaina_proudmoore_730100);
    RegisterCreatureAI(npc_occularus_coldheart_generic);
}
