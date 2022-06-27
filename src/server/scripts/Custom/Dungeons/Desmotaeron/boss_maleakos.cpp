#include "Desmotaeron.h"
#include "GossipDef.h"
#include "ScriptedGossip.h"

enum eMaleakos
{
    NpcJaina = 707036,
    NpcPortal = 707027,

    Feasting = 273717,

    /// Maleakos pre event
    ShadowTeleportEffect = 333617,

    /// Jaina spells
    ChannelDomination = 362464,

    ///< End Boss
    EphemeralBody  = 339006,
    ResonatingBody = 339010,
    Deathorb       = 297047,

    ActionStartEncounter = 1,
};

enum eAdds
{
    Axeguard = 707024,
    SoulHarvester = 707025,
    SpiritShepard = 707022,
};

const Position SpawnPos1({ 4464.16f, 6085.56f, 4854.81f, 0.807772f });
const Position SpawnPos2({ 4490.63f, 6109.33f, 4854.81f, 3.94609f });
const Position SpawnPos3({ 4472.88f, 6129.42f, 4854.81f, 3.92646f });
const Position SpawnPos4({ 4445.94f, 6103.59f, 4854.81f, 0.673604f });

// 707036 - npc_jaina_proudmoore_707036
struct npc_jaina_proudmoore_707036 : public ScriptedAI
{
public:
    npc_jaina_proudmoore_707036(Creature* creature) : ScriptedAI(creature) { }

    void InitializeAI() override
    {
        me->SetEmoteState(Emote::EMOTE_STATE_READY1H);
    }

    void UpdateAI(uint32 diff) override
    {
        scheduler.Update(diff);
    }

    bool OnGossipHello(Player* player) override
    {
        ClearGossipMenuFor(player);
        AddGossipItemFor(player, GossipOptionIcon::None, "Let's get out of here!", 0, 0, "Are you sure? This will start the encounter.", 0, false, [this](std::string /*callback*/)
        {
            me->RemoveNpcFlag(NPCFlags::UNIT_NPC_FLAG_GOSSIP);
            StartEncounter();
        });
        SendGossipMenuFor(player, me->GetEntry(), me);
        return true;
    }

    void StartEncounter()
    {
        Talk(0);

        if (auto maleakos = me->FindNearestCreature(707005, 50.0f))
            if (maleakos->AI())
                maleakos->AI()->DoAction(ActionStartEncounter);

        me->GetMotionMaster()->MovePoint(1, { 4454.58f, 6129.39f, 4857.82f, 3.15755f }, MOVE_RUN_MODE | MOVE_PATHFINDING, 3.15755f)->callbackFunc = [this]()
        {
            if (auto maleakos = me->FindNearestCreature(707005, 50.0f))
            {
                if (auto portal = maleakos->SummonCreature(NpcPortal, { 4446.51f, 6129.11f, 4857.82f, 2.36927f }, TEMPSUMMON_MANUAL_DESPAWN, 0s))
                {
                    portal->RemoveNpcFlag(NPCFlags::UNIT_NPC_FLAG_SPELLCLICK);
                    scheduler.Schedule(1s, [this](TaskContext /*context*/)
                    {
                        if (auto portal = me->FindNearestCreature(NpcPortal, 15.0f))
                            DoCast(portal, ChannelDomination);
                    });
                }
            }
        };
    }

    bool intro = false;

    void MoveInLineOfSight(Unit* who) override
    {
        if (who->IsPlayer() && who->GetDistance2d(me) <= 15.0f && !intro)
        {
            intro = true;
            Talk(1);
        }
    }

    TaskScheduler scheduler;
};

// 707005 - npc_maleakos_707005
struct npc_maleakos_707005 : public BossAI
{
public:
    npc_maleakos_707005(Creature* creature) : BossAI(creature, MalekosPart1)
    {
        SetCombatMovement(false);
        me->SetUnitFlag2(UnitFlags2::UNIT_FLAG2_CANNOT_TURN);
        me->SetVisible(false);
        me->SetUnitFlag(UnitFlags::UNIT_FLAG_NON_ATTACKABLE);

        remainingAdds = 36;
    }

    void InitializeAI()
    {
        DoSummon(NpcJaina, { 4468.81f, 6107.45f, 4854.81f, 5.48533f });
    }

    void DoAction(int32 actionId) override
    {
        if (actionId == ActionStartEncounter)
        {
            if (instance)
                instance->SetBossState(MalekosPart1, EncounterState::IN_PROGRESS);
            DoZoneInCombat();
            scheduler.Schedule(5s, [this](TaskContext /*context*/)
            {
                DoSummon(eAdds::Axeguard, SpawnPos1, 3s, TempSummonType::TEMPSUMMON_DEAD_DESPAWN);
                DoSummon(eAdds::Axeguard, SpawnPos2, 3s, TempSummonType::TEMPSUMMON_DEAD_DESPAWN);
                DoSummon(eAdds::SpiritShepard, SpawnPos3, 3s, TempSummonType::TEMPSUMMON_DEAD_DESPAWN);
                DoSummon(eAdds::SoulHarvester, SpawnPos4, 3s, TempSummonType::TEMPSUMMON_DEAD_DESPAWN);
            });
            scheduler.Schedule(6s, [this](TaskContext /*context*/)
            {
                DoSummon(eAdds::Axeguard, SpawnPos1, 3s, TempSummonType::TEMPSUMMON_DEAD_DESPAWN);
                DoSummon(eAdds::Axeguard, SpawnPos2, 3s, TempSummonType::TEMPSUMMON_DEAD_DESPAWN);
                DoSummon(eAdds::SpiritShepard, SpawnPos3, 3s, TempSummonType::TEMPSUMMON_DEAD_DESPAWN);
                DoSummon(eAdds::SoulHarvester, SpawnPos4, 3s, TempSummonType::TEMPSUMMON_DEAD_DESPAWN);
            });
            scheduler.Schedule(7s, [this](TaskContext /*context*/)
            {
                DoSummon(eAdds::Axeguard, SpawnPos1, 3s, TempSummonType::TEMPSUMMON_DEAD_DESPAWN);
                DoSummon(eAdds::Axeguard, SpawnPos2, 3s, TempSummonType::TEMPSUMMON_DEAD_DESPAWN);
                DoSummon(eAdds::SpiritShepard, SpawnPos3, 3s, TempSummonType::TEMPSUMMON_DEAD_DESPAWN);
                DoSummon(eAdds::SoulHarvester, SpawnPos4, 3s, TempSummonType::TEMPSUMMON_DEAD_DESPAWN);
            });
            scheduler.Schedule(20s, [this](TaskContext /*context*/)
            {
                DoSummon(eAdds::Axeguard, SpawnPos1, 3s, TempSummonType::TEMPSUMMON_DEAD_DESPAWN);
                DoSummon(eAdds::Axeguard, SpawnPos2, 3s, TempSummonType::TEMPSUMMON_DEAD_DESPAWN);
                DoSummon(eAdds::SpiritShepard, SpawnPos3, 3s, TempSummonType::TEMPSUMMON_DEAD_DESPAWN);
                DoSummon(eAdds::SoulHarvester, SpawnPos4, 3s, TempSummonType::TEMPSUMMON_DEAD_DESPAWN);
            });
            scheduler.Schedule(21s, [this](TaskContext /*context*/)
            {
                DoSummon(eAdds::Axeguard, SpawnPos1, 3s, TempSummonType::TEMPSUMMON_DEAD_DESPAWN);
                DoSummon(eAdds::Axeguard, SpawnPos2, 3s, TempSummonType::TEMPSUMMON_DEAD_DESPAWN);
                DoSummon(eAdds::SpiritShepard, SpawnPos3, 3s, TempSummonType::TEMPSUMMON_DEAD_DESPAWN);
                DoSummon(eAdds::SoulHarvester, SpawnPos4, 3s, TempSummonType::TEMPSUMMON_DEAD_DESPAWN);
            });
            scheduler.Schedule(22s, [this](TaskContext /*context*/)
            {
                DoSummon(eAdds::Axeguard, SpawnPos1, 3s, TempSummonType::TEMPSUMMON_DEAD_DESPAWN);
                DoSummon(eAdds::Axeguard, SpawnPos2, 3s, TempSummonType::TEMPSUMMON_DEAD_DESPAWN);
                DoSummon(eAdds::SpiritShepard, SpawnPos3, 3s, TempSummonType::TEMPSUMMON_DEAD_DESPAWN);
                DoSummon(eAdds::SoulHarvester, SpawnPos4, 3s, TempSummonType::TEMPSUMMON_DEAD_DESPAWN);
            });
            scheduler.Schedule(42s, [this](TaskContext /*context*/)
            {
                DoSummon(eAdds::SpiritShepard, SpawnPos1, 3s, TempSummonType::TEMPSUMMON_DEAD_DESPAWN);
                DoSummon(eAdds::SpiritShepard, SpawnPos2, 3s, TempSummonType::TEMPSUMMON_DEAD_DESPAWN);
                DoSummon(eAdds::SpiritShepard, SpawnPos3, 3s, TempSummonType::TEMPSUMMON_DEAD_DESPAWN);
                DoSummon(eAdds::SpiritShepard, SpawnPos4, 3s, TempSummonType::TEMPSUMMON_DEAD_DESPAWN);
            });
            scheduler.Schedule(43s, [this](TaskContext /*context*/)
            {
                DoSummon(eAdds::SoulHarvester, SpawnPos1, 3s, TempSummonType::TEMPSUMMON_DEAD_DESPAWN);
                DoSummon(eAdds::SoulHarvester, SpawnPos2, 3s, TempSummonType::TEMPSUMMON_DEAD_DESPAWN);
                DoSummon(eAdds::SoulHarvester, SpawnPos3, 3s, TempSummonType::TEMPSUMMON_DEAD_DESPAWN);
                DoSummon(eAdds::SoulHarvester, SpawnPos4, 3s, TempSummonType::TEMPSUMMON_DEAD_DESPAWN);
            });
            scheduler.Schedule(44s, [this](TaskContext /*context*/)
            {
                DoSummon(eAdds::Axeguard, SpawnPos1, 3s, TempSummonType::TEMPSUMMON_DEAD_DESPAWN);
                DoSummon(eAdds::Axeguard, SpawnPos2, 3s, TempSummonType::TEMPSUMMON_DEAD_DESPAWN);
                DoSummon(eAdds::Axeguard, SpawnPos3, 3s, TempSummonType::TEMPSUMMON_DEAD_DESPAWN);
                DoSummon(eAdds::Axeguard, SpawnPos4, 3s, TempSummonType::TEMPSUMMON_DEAD_DESPAWN);
            });
        }
    }

    void SummonedCreatureDies(Creature* creature, Unit* /*killer*/) override
    {
        if (remainingAdds > 0)
        {
            --remainingAdds;
            if (remainingAdds == 0)
            {
                if (instance)
                    instance->SetBossState(MalekosPart1, EncounterState::DONE);

                if (auto jaina = me->FindNearestCreature(NpcJaina, 50.0f))
                {
                    jaina->CastStop();
                    jaina->CastSpell(jaina, DisappearSpell, true);
                    jaina->DespawnOrUnsummon(1200ms);
                    scheduler.Schedule(1200ms, [this](TaskContext context)
                    {
                        me->SetIsNewObject(true);
                        me->SetVisible(true);

                        scheduler.Schedule(3500ms, [this](TaskContext context)
                        {
                            Talk(0);

                            scheduler.Schedule(2500ms, [this](TaskContext context)
                            {
                                DoCastSelf(ShadowTeleportEffect);
                                scheduler.Schedule(300ms, [this](TaskContext context)
                                {
                                    if (auto portal = me->FindNearestCreature(NpcPortal, 50.0f))
                                        portal->SetNpcFlag(NPCFlags::UNIT_NPC_FLAG_SPELLCLICK);

                                    me->DespawnOrUnsummon();
                                });
                            });
                        });
                    });
                }
            }
        }
    }

    void UpdateAI(uint32 diff) override
    {
        scheduler.Update(diff);

        if (!UpdateVictim())
            return;
    }

    void EnterEvadeMode(EvadeReason /*why*/) override
    {
        summons.DespawnAll();
        _DespawnAtEvade(5s);
    }

    TaskScheduler scheduler;
    uint32 remainingAdds;
};

// 707037 - npc_portal_to_jaina_707037
struct npc_portal_to_jaina_707037 : public ScriptedAI
{
public:
    npc_portal_to_jaina_707037(Creature* creature) : ScriptedAI(creature) { }

    void OnSpellClick(Unit* clicker, bool spellClickHandled) override
    {
        clicker->NearTeleportTo({ 4489.44f, 6086.04f, 4857.82f, 2.36184f }, true, true);
    }
};
// 707028 - npc_maleakos_707028
struct boss_maleakos : public BossAI
{
public:
    boss_maleakos(Creature* creature) : BossAI(creature, BossMaleakos)
    {
    }

    void JustEngagedWith(Unit* who) override
    {
        BossAI::JustEngagedWith(who);
        Talk(0);

        me->SetDisplayId(98490);

        scheduler.CancelAll();

        scheduler.Schedule(5s, [this](TaskContext context)
        {
            DoCastSelf(EphemeralBody);
            context.Repeat(30s);
        });

        scheduler.Schedule(15s, [this](TaskContext context)
        {
            DoCastSelf(ResonatingBody);
            context.Repeat(30s);
        });

        scheduler.Schedule(7s, [this](TaskContext context)
        {
            me->SetReactState(REACT_PASSIVE);
            Talk(2);
            scheduler.Schedule(1000ms, [this](TaskContext context)
            {
                me->SetFacingTo(0.0f);
                DoCast(Deathorb);

                scheduler.Schedule(100ms, [this](TaskContext context)
                {
                    me->SetFacingTo(1.0f);
                    DoCast(Deathorb);
                    scheduler.Schedule(100ms, [this](TaskContext context)
                    {
                        me->SetFacingTo(2.0f);
                        DoCast(Deathorb);
                        scheduler.Schedule(100ms, [this](TaskContext context)
                        {
                            me->SetFacingTo(3.0f);
                            DoCast(Deathorb);
                            scheduler.Schedule(100ms, [this](TaskContext context)
                            {
                                me->SetFacingTo(4.0f);
                                DoCast(Deathorb);
                                scheduler.Schedule(100ms, [this](TaskContext context)
                                {
                                    me->SetFacingTo(5.0f);
                                    DoCast(Deathorb);
                                    scheduler.Schedule(100ms, [this](TaskContext context)
                                    {
                                        me->SetFacingTo(6.0f);
                                        DoCast(Deathorb);

                                        scheduler.Schedule(1000ms, [this](TaskContext context)
                                        {
                                            me->SetFacingTo(0.0f);
                                            DoCast(Deathorb);

                                            scheduler.Schedule(100ms, [this](TaskContext context)
                                            {
                                                me->SetFacingTo(1.0f);
                                                DoCast(Deathorb);
                                                scheduler.Schedule(100ms, [this](TaskContext context)
                                                {
                                                    me->SetFacingTo(2.0f);
                                                    DoCast(Deathorb);
                                                    scheduler.Schedule(100ms, [this](TaskContext context)
                                                    {
                                                        me->SetFacingTo(3.0f);
                                                        DoCast(Deathorb);
                                                        scheduler.Schedule(100ms, [this](TaskContext context)
                                                        {
                                                            me->SetFacingTo(4.0f);
                                                            DoCast(Deathorb);
                                                            scheduler.Schedule(100ms, [this](TaskContext context)
                                                            {
                                                                me->SetFacingTo(5.0f);
                                                                DoCast(Deathorb);
                                                                scheduler.Schedule(100ms, [this](TaskContext context)
                                                                {
                                                                    me->SetReactState(REACT_AGGRESSIVE);
                                                                    me->SetFacingTo(6.0f);
                                                                    DoCast(Deathorb);
                                                                });
                                                            });
                                                        });
                                                    });
                                                });
                                            });
                                        });
                                    });
                                });
                            });
                        });
                    });
                });
            });
            context.Repeat(30s);
        });
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
        {
            if (!me->IsEngaged())
            {
                if (!me->HasAura(Feasting))
                    DoCastSelf(Feasting);
            }

            return;
        }

        scheduler.Update(diff);

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        DoMeleeAttackIfReady();
    }
};

void AddSC_boss_maleakos()
{
    RegisterCreatureAI(npc_jaina_proudmoore_707036);
    RegisterCreatureAI(npc_maleakos_707005);
    RegisterCreatureAI(npc_portal_to_jaina_707037);
    RegisterCreatureAI(boss_maleakos);
}
