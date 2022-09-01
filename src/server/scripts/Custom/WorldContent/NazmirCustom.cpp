#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "TaskScheduler.h"
#include "Containers.h"
#include "CellImpl.h"
#include "GridNotifiersImpl.h"

const std::vector<Position> RandomEnemySpawnPoints
{
    //{ 870.697f, 790.95f, 2.19092f, 3.17389f },
    //{ 870.51f, 796.757f, 2.27256f, 3.17389f },
    //{ 870.383f, 800.683f, 2.66227f, 3.17389f },
    //{ 870.193f, 806.56f, 3.47527f, 3.17389f },
    //{ 870.078f, 810.128f, 3.72815f, 3.17389f },
    //{ 869.926f, 814.815f, 3.60836f, 3.17389f },
    //{ 865.239f, 814.664f, 4.36003f, 3.17389f },
    //{ 865.426f, 808.857f, 4.46773f, 3.17389f },
    //{ 865.564f, 804.589f, 4.40344f, 3.17389f },
    //{ 865.716f, 799.902f, 3.2752f, 3.17389f },
    //{ 865.867f, 795.214f, 2.4384f, 3.17389f },
    //{ 866.078f, 788.694f, 3.51372f, 3.17389f },
    //{ 861.46f, 788.545f, 3.37539f, 3.17389f },
    //{ 861.32f, 792.882f, 2.72017f, 3.17389f },
    //{ 861.17f, 797.505f, 3.97399f, 3.17389f },
    //{ 861.019f, 802.193f, 4.47406f, 3.17389f },
    //{ 860.8f, 808.979f, 4.47406f, 3.17389f },
    //{ 860.648f, 813.667f, 4.47406f, 3.17389f },
    { 700.5f, 789.843f, 3.57718f, 3.11826f },
    { 700.555f, 792.187f, 3.56063f, 3.11826f },
    { 700.609f, 794.497f, 3.5442f, 3.11826f },
    { 700.647f, 796.127f, 3.53278f, 3.11826f },
    { 700.672f, 797.177f, 3.52624f, 3.11826f },
    { 700.709f, 798.801f, 3.51494f, 3.11826f },
    { 700.756f, 800.781f, 3.49993f, 3.11826f },
    { 700.824f, 803.706f, 3.48017f, 3.11826f },
    { 700.873f, 805.806f, 3.46554f, 3.11826f },
    { 699.448f, 807.98f, 3.30372f, 3.11826f },
    { 696.222f, 808.055f, 2.98458f, 3.11826f },
    { 694.617f, 805.196f, 2.85274f, 3.11826f },
    { 693.397f, 802.356f, 2.78895f, 3.11826f },
    { 693.341f, 799.941f, 2.80737f, 3.11826f },
    { 693.271f, 796.939f, 2.83029f, 3.11826f },
    { 693.212f, 794.406f, 2.84969f, 3.11826f },
    { 693.147f, 791.641f, 2.87086f, 3.11826f },
    { 690.606f, 790.01f, 3.52672f, 3.11826f },
    { 688.7f, 792.366f, 3.38203f, 3.11826f },
    { 688.768f, 795.277f, 3.36163f, 3.11826f },
    { 688.862f, 799.315f, 3.33314f, 3.11826f },

};

const std::vector<Position> AllySpawnPositions
{
    { 512.042f, 806.736f, 36.4317f, 6.25984f },

    { 511.968f, 803.962f, 36.5017f, 6.25657f },
    { 511.819f, 798.357f, 36.1984f, 6.25657f },
    { 511.763f, 796.258f, 36.1625f, 6.25657f },
    { 511.639f, 791.605f, 35.8741f, 6.25657f },
    { 512.5f, 787.971f, 35.6844f, 6.25657f },
    { 515.768f, 787.884f, 34.5327f, 6.25657f },
    { 516.672f, 790.781f, 34.2918f, 6.25657f },
    { 516.731f, 792.999f, 34.3292f, 6.25657f },
    { 517.303f, 796.263f, 34.2154f, 6.25657f },
    { 518.063f, 800.049f, 34.049f, 6.25657f },
    { 518.137f, 802.848f, 34.0969f, 6.25657f },
    { 518.206f, 805.409f, 34.1402f, 6.25657f },
    { 522.326f, 806.18f, 32.7132f, 6.25657f },
    { 523.443f, 801.649f, 32.2004f, 6.25657f },
    { 524.335f, 797.953f, 31.7889f, 6.25657f },
    { 524.242f, 794.454f, 31.7288f, 6.25657f },
    { 525.029f, 789.818f, 31.3288f, 6.25657f },
    { 524.942f, 786.55f, 31.0685f, 6.25657f },
    { 528.333f, 789.431f, 30.1576f, 6.25657f },
    { 529.76f, 793.397f, 29.761f, 6.25657f },
    { 529.859f, 797.092f, 29.8189f, 6.25657f },
    { 530.91f, 801.839f, 29.285f, 6.25657f },
    { 532.057f, 806.412f, 28.5672f, 6.25657f },
    { 492.836f, 807.823f, 43.4626f, 5.76242f },
    { 491.234f, 802.638f, 43.9858f, 0.0126524f },
    { 492.848f, 797.654f, 43.3375f, 0.146825f },
    { 494.057f, 793.674f, 42.8472f, 0.146825f },
    { 494.552f, 790.323f, 42.6252f, 0.146825f },
};

const std::vector<uint32> AllySpawnEntries
{
    720002,
    720001,
    720008,
    720009,
    720010,
    720011,
    720012,
    720013,
};

const std::vector<uint32> EnemySpawnEntries
{
    730030,
    730031,
    730032,
    730033,
    730034,
    730035,
    730036,
    730037,
};

struct npc_nazmir_custom_spawn_trigger : public ScriptedAI
{
    public:
        npc_nazmir_custom_spawn_trigger(Creature* creature) : ScriptedAI(creature) { }

        //uint32 m_AllySpawns = 0;
        //uint32 m_EnemySpawns = 0;

        void InitializeAI() override
        {
            if (!m_Started)
            {
                m_Started = true;
                me->setActive(true);
                DoSetup();
            }
        }

        void UpdateAI(uint32 diff)
        {
            scheduler.Update(diff);
        }

        // Called when the creature summon successfully other creature
        void JustSummoned(Creature* summon) override
        {
            //if (summon->GetEntry() >= 730030)
            //    m_EnemySpawns++;
            //else
            //    m_AllySpawns++;
        }

        void SummonedCreatureDies(Creature* summon, Unit* /*killer*/) override
        {
            bool isEnemy = summon->GetEntry() >= 730030;

            scheduler.Schedule(2s, 5s, [isEnemy, this](TaskContext context)
            {
                if (isEnemy)
                {
                    SummonNextEnemy();
                }
                else
                {
                    SummonNextAlly();
                }
            });
        }

        void SummonedCreatureDespawn(Creature* summon) override
        {
            if (summon->isDead())
                return;
            bool isEnemy = summon->GetEntry() >= 730030;

            scheduler.Schedule(2s, 5s, [isEnemy, this](TaskContext context)
            {
                if (isEnemy)
                {
                    SummonNextEnemy();
                }
                else
                {
                    SummonNextAlly();
                }
            });
        }

        void DoSetup()
        {
            for (int i = 0; i < 40; ++i)
            {
                scheduler.Schedule(2s, 5s, [this](TaskContext context)
                {
                    SummonNextEnemy();
                });
                scheduler.Schedule(2s, 5s, [this](TaskContext context)
                {
                    SummonNextAlly();
                });
            }
        }


        void SummonNextAlly()
        {
            if (AllyQueue.empty())
            {
                std::vector<uint32> vecCopy = AllySpawnEntries;
                Trinity::Containers::RandomShuffle(vecCopy);

                for (uint32 entry : vecCopy)
                    AllyQueue.push(entry);
            }

            if (AllyPosQue.empty())
            {
                std::vector<Position> vecCopy = AllySpawnPositions;
                Trinity::Containers::RandomShuffle(vecCopy);

                for (auto entry : vecCopy)
                    AllyPosQue.push(entry);
            }

            uint32 nextEntry = AllyQueue.front();
            auto pos = AllyPosQue.front();
            me->MovePositionToFirstCollision(pos, 3.0f * (float)rand_norm(), (float)rand_norm() * static_cast<float>(2 * M_PI));

            DoSummon(nextEntry, pos);

            AllyQueue.pop();
            AllyPosQue.pop();
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
                std::vector<Position> vecCopy = RandomEnemySpawnPoints;
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
        bool m_Started = false;
        std::queue<uint32> EnemyQueue;
        std::queue<Position> EnemyPosQue;
        std::queue<uint32> AllyQueue;
        std::queue<Position> AllyPosQue;
};

std::vector<Position> fortPositions =
{
    { 600.217f, 807.28f, 8.03345f, 6.26965f },
    { 600.187f, 805.073f, 8.16059f, 6.26965f },
    { 600.157f, 802.89f, 8.28588f, 6.26965f },
    { 600.115f, 799.789f, 8.46401f, 6.26965f },
    { 600.533f, 795.947f, 8.60333f, 6.26965f },
    { 600.483f, 792.255f, 8.81575f, 6.26965f },
    { 601.336f, 787.877f, 8.90506f, 6.26965f },
    { 604.955f, 787.828f, 8.26114f, 6.26965f },
    { 607.479f, 791.431f, 7.61131f, 6.26965f },
    { 608.442f, 795.712f, 7.20286f, 6.26965f },
    { 609.271f, 799.627f, 6.73704f, 6.26965f },
    { 610.831f, 803.335f, 5.9102f, 6.26965f },
    { 608.046f, 809.696f, 6.50116f, 0.00283146f },
    { 585.604f, 808.096f, 13.2332f, 6.1813f },
    { 585.978f, 803.291f, 13.302f, 0.130462f },
    { 585.928f, 799.33f, 13.4348f, 6.21402f },
    { 585.722f, 796.348f, 13.5723f, 6.21402f },
    { 585.56f, 794.023f, 13.6795f, 6.21402f },
    { 585.345f, 790.908f, 13.8231f, 6.21402f },
    { 585.889f, 787.177f, 13.8228f, 6.21402f },
};

struct npc_nazmir_general_fighter : public ScriptedAI
{
    public:
        npc_nazmir_general_fighter(Creature* creature) : ScriptedAI(creature) { }


        void InitializeAI() override
        {
            me->SetEmoteState(Emote::EMOTE_STATE_READY1H);

            scheduler.Schedule(100ms, [this](TaskContext context)
                {
                    me->GetMotionMaster()->MovePoint(0, Trinity::Containers::SelectRandomContainerElement(fortPositions));
                });
            me->SetRegenerateHealth(false);
        }

        bool didReset = false;

        void Reset()
        {
            didReset = true;
            me->SetEmoteState(Emote::EMOTE_STATE_READY1H);

            scheduler.Schedule(100ms, [this](TaskContext context)
                {
                    me->GetMotionMaster()->MovePoint(0, Trinity::Containers::SelectRandomContainerElement(fortPositions));
                });
        }

        bool CanAIAttack(Unit const* who) const override
        {
            if (who->IsCreature())
            {
                return who->GetEntry() >= 730030 && who->GetEntry() <= 730090;
            }

            return ScriptedAI::CanAIAttack(who);
        }

        void UpdateAI(uint32 diff) override
        {
            scheduler.Update(diff);

            if (!UpdateVictimCrapopolis())
                return;

            DoMeleeAttackIfReady();
        }

        bool UpdateVictimCrapopolis()
        {
            if (me->isDead())
            {
                if (me->IsSplineEnabled())
                    me->GetMotionMaster()->Clear();
                return false;
            }

            if (!me->GetVictim())
            {
                if (!me->HasReactState(REACT_PASSIVE))
                    if (Unit* victim = SelectVictimCrap())
                        if (victim != me->GetVictim())
                            AttackStart(victim);

                if (!didReset && me->GetVictim() == nullptr)
                {
                    EngagementOver();
                    Reset();
                }

                return false;
            }

            if (!me->IsAlive())
            {
                EngagementOver();
                return false;
            }

            if (!me->HasReactState(REACT_PASSIVE))
            {
                if (Unit* victim = me->SelectVictim())
                    if (victim != me->GetVictim())
                        AttackStart(victim);

                if (!didReset && me->GetVictim() == nullptr)
                {
                    EngagementOver();
                    Reset();
                }

                return me->GetVictim() != nullptr;
            }
            else if (me->GetVictim())
                me->AttackStop();

            return true;
        }

        Unit* SelectVictimCrap()
        {
            Unit* target = me->SelectNearbyTarget(nullptr, 25.0f);
            return target;
        }

        void JustEngagedWith(Unit* who) override
        {
            me->GetMotionMaster()->Clear();
        }

        // Override to not reset.
        void EnterEvadeMode(EvadeReason why) override
        {
            switch (why)
            {
                case EVADE_REASON_BOUNDARY:
                case EVADE_REASON_NO_PATH:
                    me->DespawnOrUnsummon();
                    break;
            }
        }

        TaskScheduler scheduler;
};

const std::vector<Position> RandomEndPoints = {
    { 522.033f, 788.778f, 32.3543f, 3.10844f },
    { 522.202f, 793.404f, 32.4177f, 3.10517f },
    { 522.413f, 799.21f, 32.4974f, 3.10517f },
    { 522.37f, 798.021f, 32.4814f, 3.10517f },
    { 522.582f, 803.837f, 32.561f, 3.10517f },
    { 522.707f, 807.265f, 32.608f, 3.10517f },
};

struct npc_nazmir_general_enemy : public ScriptedAI
{
    public:
        npc_nazmir_general_enemy(Creature* creature) : ScriptedAI(creature) { }

        void InitializeAI() override
        {
            me->SetEmoteState(Emote::EMOTE_STATE_READY1H);

            scheduler.Schedule(100ms, [this](TaskContext context)
                {
                    me->GetMotionMaster()->MovePoint(0, Trinity::Containers::SelectRandomContainerElement(RandomEndPoints));
                });
            me->SetRegenerateHealth(false);
        }

        bool didReset = false;

        void Reset()
        {
            didReset = true;
            me->SetEmoteState(Emote::EMOTE_STATE_READY1H);

            scheduler.Schedule(100ms, [this](TaskContext context)
                {
                    me->GetMotionMaster()->MovePoint(0, Trinity::Containers::SelectRandomContainerElement(RandomEndPoints));
                });
        }

        bool CanAIAttack(Unit const* who) const override
        {
            if (who->IsCreature())
            {
                return who->GetEntry() >= 720001 && who->GetEntry() <= 720024;
            }

            return ScriptedAI::CanAIAttack(who);
        }

        void JustEngagedWith(Unit* who) override
        {
            me->GetMotionMaster()->Clear();
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
                    u->KilledMonsterCredit(720000, me->GetGUID());
            }
        }

        void UpdateAI(uint32 diff) override
        {
            scheduler.Update(diff);

            if (!UpdateVictimCrapopolis())
                return;

            DoMeleeAttackIfReady();
        }

        bool UpdateVictimCrapopolis()
        {
            if (me->isDead())
            {
                if (me->IsSplineEnabled())
                    me->GetMotionMaster()->Clear();
                return false;
            }

            if (!me->GetVictim())
            {
                if (!me->HasReactState(REACT_PASSIVE))
                    if (Unit* victim = SelectVictimCrap())
                        if (victim != me->GetVictim())
                            AttackStart(victim);

                if (!didReset && me->GetVictim() == nullptr)
                {
                    EngagementOver();
                    Reset();
                }

                return false;
            }

            if (!me->IsAlive())
            {
                EngagementOver();
                return false;
            }

            if (!me->HasReactState(REACT_PASSIVE))
            {
                if (Unit* victim = me->SelectVictim())
                    if (victim != me->GetVictim())
                        AttackStart(victim);

                if (!didReset && me->GetVictim() == nullptr)
                {
                    EngagementOver();
                    Reset();
                }

                return me->GetVictim() != nullptr;
            }
            else if (me->GetVictim())
                me->AttackStop();

            return true;
        }

        Unit* SelectVictimCrap()
        {
            Unit* target = me->SelectNearbyTarget(nullptr, 25.0f);
            return target;
        }

        // Override to not reset.
        void EnterEvadeMode(EvadeReason why) override
        {
            switch (why)
            {
                case EVADE_REASON_BOUNDARY:
                case EVADE_REASON_NO_PATH:
                    me->DespawnOrUnsummon();
                    break;
            }
        }

        TaskScheduler scheduler;
};

struct npc_princess_talanji_720000 : public ScriptedAI
{
    public:
        npc_princess_talanji_720000(Creature* creature) : ScriptedAI(creature) { }

        bool OnGossipHello(Player* player) override
        {
            ClearGossipMenuFor(player);
            player->PrepareQuestMenu(me->GetGUID());
            SendGossipMenuFor(player, 720000, me);
            return true;
        }
};

void AddSC_NazmirCustom()
{
    RegisterCreatureAI(npc_nazmir_custom_spawn_trigger);
    RegisterCreatureAI(npc_nazmir_general_fighter);
    RegisterCreatureAI(npc_nazmir_general_enemy);
    RegisterCreatureAI(npc_princess_talanji_720000);
}
