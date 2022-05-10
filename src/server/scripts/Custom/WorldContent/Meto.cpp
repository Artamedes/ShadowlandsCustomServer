#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "TemporarySummon.h"
#include "GossipDef.h"
#include "ScriptedGossip.h"

enum Meto
{
    Stealthed = 343019,
    DrainSoul = 346562,
    MushroomEntry = 730200,
    CosmeticDead = 366705,

    // Boss
    ShadowNova = 353782,
    ShadowBoltVolley = 353769,
};

struct MetoSpawnPoint
{
    MetoSpawnPoint(Position pos) : Pos(pos) { }

    ObjectGuid SummonGuid;
    Position Pos;
};

// 730250 - npc_giant_fungal_warrior_730250
struct npc_giant_fungal_warrior_730250 : public ScriptedAI
{
public:
    npc_giant_fungal_warrior_730250(Creature* creature) : ScriptedAI(creature), summons(creature) { }

    std::vector<MetoSpawnPoint> RandomSpawnPoints =
    {
        MetoSpawnPoint({ 5614.93f, -1445.16f, 4.90798f, 1.28661f }),
        MetoSpawnPoint({ 5619.62f, -1491.93f, 2.3739f, 5.4394f }),
        MetoSpawnPoint({ 5648.21f, -1492.6f, 1.54633f, 0.049607f }),
        MetoSpawnPoint({ 5669.24f, -1482.98f, 4.45732f, 1.44696f }),
        MetoSpawnPoint({ 5661.01f, -1462.03f, 8.10927f, 2.31417f }),
        MetoSpawnPoint({ 5642.57f, -1453.34f, 7.10141f, 3.14866f }),
        MetoSpawnPoint({ 5573.46f, -1471.0f, 8.20591f, 3.8686f }),
        MetoSpawnPoint({ 5575.52f, -1510.39f, 5.90205f, 5.16451f }),
        MetoSpawnPoint({ 5590.18f, -1541.86f, 2.72986f, 5.88446f }),
        MetoSpawnPoint({ 5622.46f, -1549.38f, -0.00288625f, 6.2608f }),
        MetoSpawnPoint({ 5653.98f, -1537.67f, 1.62901f, 0.592843f }),
        MetoSpawnPoint({ 5671.49f, -1515.87f, 5.08798f, 1.21789f }),
        MetoSpawnPoint({ 5655.0f, -1515.42f, 1.48184f, 2.16037f }),
        MetoSpawnPoint({ 5638.54f, -1503.98f, 2.06477f, 2.7396f }),
        MetoSpawnPoint({ 5670.5f, -1470.99f, 7.00435f, 2.46798f }),
        MetoSpawnPoint({ 5653.2f, -1456.67f, 7.32306f, 3.32865f }),
        MetoSpawnPoint({ 5591.2f, -1468.39f, 5.99539f, 4.36603f }),
        MetoSpawnPoint({ 5581.21f, -1562.61f, 2.95951f, 5.90737f }),
        MetoSpawnPoint({ 5593.88f, -1625.98f, 2.09018f, 5.57031f }),
        MetoSpawnPoint({ 5656.54f, -1624.07f, 2.34041f, 1.17208f }),
        MetoSpawnPoint({ 5688.06f, -1585.63f, 3.27082f, 1.49933f }),
        MetoSpawnPoint({ 5691.01f, -1533.77f, 5.45183f, 2.0262f }),
        MetoSpawnPoint({ 5688.92f, -1486.71f, 6.94226f, 2.99485f }),
        MetoSpawnPoint({ 5663.97f, -1527.62f, 4.07816f, 3.50209f }),
        MetoSpawnPoint({ 5633.23f, -1579.11f, 1.07865f, 3.3941f }),
        MetoSpawnPoint({ 5584.88f, -1569.63f, 2.52827f, 1.50914f }),
        MetoSpawnPoint({ 5581.96f, -1530.38f, 4.65476f, 0.969183f }),
        MetoSpawnPoint({ 5582.95f, -1493.02f, 7.00832f, 6.2608f }),
        MetoSpawnPoint({ 5569.45f, -1572.36f, 4.29265f, 5.73393f }),
        MetoSpawnPoint({ 5644.28f, -1633.49f, 1.69224f, 0.615756f }),
        MetoSpawnPoint({ 5685.3f, -1629.0f, 6.01307f, 1.62696f }),
        MetoSpawnPoint({ 5662.99f, -1597.97f, 1.13991f, 1.7284f }),
        MetoSpawnPoint({ 5692.62f, -1513.62f, 7.46428f, 1.67605f }),
        MetoSpawnPoint({ 5695.98f, -1562.46f, 4.5086f, 2.55636f }),
        MetoSpawnPoint({ 5663.81f, -1572.17f, 0.912731f, 2.37637f }),
        MetoSpawnPoint({ 5641.05f, -1611.38f, 0.94582f, 3.62319f }),
        MetoSpawnPoint({ 5622.59f, -1648.45f, 1.3898f, 1.72187f }),
        MetoSpawnPoint({ 5606.78f, -1632.06f, 1.11116f, 1.78078f }),
        MetoSpawnPoint({ 5605.1f, -1599.25f, -0.034813f, 1.77751f }),
        MetoSpawnPoint({ 5606.74f, -1570.02f, -0.283996f, 1.66951f }),
        MetoSpawnPoint({ 5634.13f, -1469.34f, 3.05233f, 6.00557f }),
    };

    void InitializeAI()
    {
        DoCast(Stealthed);
        for (auto& spawnPoint : RandomSpawnPoints)
        {
            if (auto summ = DoSummon(730212, spawnPoint.Pos, 5s, TEMPSUMMON_CORPSE_TIMED_DESPAWN))
            {
                spawnPoint.SummonGuid = summ->GetGUID();
            }
        }
    }

    void JustSummoned(Creature* summ) override
    {
        summons.Summon(summ);
    }

    void SummonedCreatureDespawn(Creature* summoned) override
    {
        summons.Despawn(summoned);

        for (auto& spawnPoint : RandomSpawnPoints)
        {
            if (spawnPoint.SummonGuid == summoned->GetGUID())
            {
                spawnPoint.SummonGuid.Clear();
                break;
            }
        }

        ++totalDead;

        if (totalDead < 5)
            return;

        scheduler.Schedule(10s, [this](TaskContext context)
        {
            for (int i = 0; i < totalDead; ++i)
            {
                for (auto& spawnPoint : RandomSpawnPoints)
                {
                    if (spawnPoint.SummonGuid.IsEmpty())
                    {
                        if (auto summ = DoSummon(730212, spawnPoint.Pos, 5s, TEMPSUMMON_CORPSE_TIMED_DESPAWN))
                        {
                            spawnPoint.SummonGuid = summ->GetGUID();
                            break;
                        }
                    }
                }
            }
            totalDead = 0;
        });
    }

    bool OnGossipHello(Player* player) override
    {
        ClearGossipMenuFor(player);
        player->PrepareQuestMenu(me->GetGUID());
        SendGossipMenuFor(player, me->GetEntry(), me);
        return true;
    }

    void UpdateAI(uint32 diff) override
    {
        scheduler.Update(diff);
    }

    TaskScheduler scheduler;
    SummonList summons;
    uint32 totalDead = 0;
};

// 730212 - npc_mushroom_sapper_730212
struct npc_mushroom_sapper_730212 : public ScriptedAI
{
public:
    npc_mushroom_sapper_730212(Creature* creature) : ScriptedAI(creature) { }

    void InitializeAI() override
    {
        if (auto mushroom = DoSummon(MushroomEntry, me, 10.0f, 0s, TEMPSUMMON_MANUAL_DESPAWN))
        {
          //  mushroom->SetFacingToObject(me);
            MushroomGuid = mushroom->GetGUID();
        }
    }

    void JustDied(Unit* killer) override
    {
        if (auto mushroom = ObjectAccessor::GetCreature(*me, MushroomGuid))
        {
            if (mushroom->AI())
                mushroom->AI()->DoAction(1);
        }
    }

    ObjectGuid MushroomGuid;

    void UpdateAI(uint32 diff) override
    {
        scheduler.Update(diff);

        if (!UpdateVictim())
        {
            if (!me->isDead() && !me->IsEngaged())
            {
                if (!me->GetCurrentSpell(CurrentSpellTypes::CURRENT_CHANNELED_SPELL))
                {
                    if (auto mushroom = ObjectAccessor::GetCreature(*me, MushroomGuid))
                        DoCast(mushroom, Meto::DrainSoul);
                }
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

    TaskScheduler scheduler;
    EventMap events;
};

// 730200 - npc_mushroom_civilian_730200
struct npc_mushroom_civilian_730200 : public ScriptedAI
{
public:
    npc_mushroom_civilian_730200(Creature* creature) : ScriptedAI(creature) { }

    void InitializeAI()
    {
        DoCastSelf(CosmeticDead);
        me->SetEmoteState(Emote::EMOTE_STATE_DROWNED);
    }

    void UpdateAI(uint32 diff) override
    {
        scheduler.Update(diff);
    }

    void DoAction(int32 actionId) override
    {
        if (actionId == 1)
        {
            scheduler.Schedule(1s, [this](TaskContext context)
            {
                me->RemoveAllAuras();
                me->SetEmoteState(Emote::EMOTE_ONESHOT_NONE);
                scheduler.Schedule(1s, [this](TaskContext context)
                {
                    Talk(0);
                    scheduler.Schedule(1s, [this](TaskContext context)
                    {
                        DoCastSelf(367044, true);
                        scheduler.Schedule(500ms, [this](TaskContext context)
                        {
                            me->DestroyForNearbyPlayers();
                            me->DespawnOrUnsummon();
                        });
                    });
                });
            });

        }
    }

    TaskScheduler scheduler;
};

// 730213 - npc_spawn_of_n_zoth_730213
struct npc_spawn_of_n_zoth_730213 : public ScriptedAI
{
public:
    npc_spawn_of_n_zoth_730213(Creature* creature) : ScriptedAI(creature) { }

    void JustEngagedWith(Unit* who) override
    {
        events.Reset();
        events.ScheduleEvent(1, 5s, 10s);
        events.ScheduleEvent(2, 5s, 10s);
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
                    DoCastAOE(ShadowBoltVolley);
                    events.Repeat(10s, 20s);
                    break;
                case 2:
                    DoCastAOE(ShadowNova);
                    events.Repeat(10s, 20s);
                    break;
            }
        }
        DoMeleeAttackIfReady();
    }

    TaskScheduler scheduler;
    EventMap events;
};

void AddSC_Meto()
{
    RegisterCreatureAI(npc_giant_fungal_warrior_730250);
    RegisterCreatureAI(npc_mushroom_sapper_730212);
    RegisterCreatureAI(npc_mushroom_civilian_730200);
    RegisterCreatureAI(npc_spawn_of_n_zoth_730213);
}
