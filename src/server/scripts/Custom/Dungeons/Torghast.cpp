#include "SpellMgr.h"
#include "ScriptedCreature.h"
#include "Creature.h"
#include "ScriptedGossip.h"
#include "MotionMaster.h"
#include "Player.h"
#include "ScriptMgr.h"
#include "MoveSpline.h"
#include "GenericMovementGenerator.h"
#include "GameTime.h"
#include "../CustomInstanceScript.h"

// 700800 - npc_thrall_700800
struct npc_thrall_700800 : public ScriptedAI
{
public:
    npc_thrall_700800(Creature* creature) : ScriptedAI(creature) { }

    bool OnGossipHello(Player* player) override
    {
        if (player->GetQuestStatus(700031) == QUEST_STATUS_COMPLETE)
        {
            player->PlayerTalkClass->SendQuestGiverOfferReward(sObjectMgr->GetQuestTemplate(700031), me->GetGUID(), true);
            return true;
        }

        for (int i = 0; i < 5; i++)
        {
            if (player->GetQuestStatus(700031 + i) == QUEST_STATUS_REWARDED && player->GetQuestStatus(700032 + i) == QUEST_STATUS_NONE)
            {
                player->PlayerTalkClass->SendQuestGiverQuestDetails(sObjectMgr->GetQuestTemplate(700032 + i), me->GetGUID(), false, false);
                player->AddQuestAndCheckCompletion(sObjectMgr->GetQuestTemplate(700032 + i), me);
                return true;
            }
        }

        ClearGossipMenuFor(player);
        player->PrepareQuestMenu(me->GetGUID());
        SendGossipMenuFor(player, me->GetEntry(), me);
        return true;
    }

    bool CanSeeOrDetect(WorldObject const* who) const override
    {
        if (who->IsPlayer())
        {
            auto player = who->ToPlayer();
            auto status = player->GetQuestStatus(700036); // 700036 finish the fight
            switch (status)
            {
                case QUEST_STATUS_COMPLETE:
                case QUEST_STATUS_REWARDED:
                    return false;
                default:
                    return true;
            }
        }

        return true;
    }
};

// 700812 - npc_sir_duke_iro_700812
struct npc_sir_duke_iro_700812 : public ScriptedAI
{
public:
    npc_sir_duke_iro_700812(Creature* creature) : ScriptedAI(creature) { }

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
        events.ScheduleEvent(1, 5s, 6s);
        events.ScheduleEvent(2, 25s, 26s);
        events.ScheduleEvent(3, 25s, 26s);
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
                    DoCast(240006);
                    events.Repeat(10s, 11s);
                    break;
                case 2:
                    DoCastVictim(355872);
                    events.Repeat(10s, 20s);
                    break;
                case 3:
                    DoCastSelf(263848); // void barrier
                    Talk(1);
                    break;
            }
        }
        DoMeleeAttackIfReady();
    }


    TaskScheduler scheduler;
    EventMap events;
};

// 700813 - npc_mawsworn_annihilator_700813
struct npc_mawsworn_annihilator_700813 : public ScriptedAI
{
public:
    npc_mawsworn_annihilator_700813(Creature* creature) : ScriptedAI(creature) { }

    void InitializeAI() override
    {
        /// TODO: Fill this function
    }

    void JustDied(Unit* who) override
    {
        if (auto portal = me->FindNearestCreature(700819, 500.0f, true))
            portal->RemoveUnitFlag(UnitFlags::UNIT_FLAG_NON_ATTACKABLE);
    }

    void Reset() override
    {
        me->SetEmoteState(EMOTE_STATE_READY1H);
        events.Reset();
    }

    void JustEngagedWith(Unit* /*who*/) override
    {
        me->SetEmoteState(EMOTE_STATE_NONE);
        events.ScheduleEvent(1, 8s, 12s);
        events.ScheduleEvent(2, 7s);
        events.ScheduleEvent(3, 17s);
        events.ScheduleEvent(4, 15s);
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
                    DoCastVictim(364355);
                    events.Repeat(15s, 20s);
                    break;
                case 2:
                    DoCastSelf(356306);
                    events.Repeat(15s, 20s);
                    break;
                case 3:
                    DoCastSelf(294165);
                    events.Repeat(15s, 20s);
                    break;
                case 4:
                    DoCastSelf(292942);
                    events.Repeat(35s, 40s);
                    break;
            }
        }
        DoMeleeAttackIfReady();
    }


    TaskScheduler scheduler;
    EventMap events;
};

// 700808 - npc_mawsworn_seeker_700808
struct npc_mawsworn_seeker_700808 : public ScriptedAI
{
public:
    npc_mawsworn_seeker_700808(Creature* creature) : ScriptedAI(creature) { }

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
        me->SetEmoteState(Emote::EMOTE_ONESHOT_NONE);
        events.Reset();
        events.ScheduleEvent(1, 5s, 20s);
    }

    bool emoting = false;

    void UpdateAI(uint32 diff) override
    {
        scheduler.Update(diff);

        if (!UpdateVictim())
        {
            if (!me->IsEngaged() && !me->isDead())
            {
                auto axeguard = me->FindNearestCreature(700803, 10.0f);
                if (!axeguard && emoting)
                {
                    emoting = false;
                    me->SetEmoteState(Emote::EMOTE_ONESHOT_NONE);
                }
                if (axeguard && !emoting)
                {
                    me->SetEmoteState(Emote::EMOTE_ONESHOT_ATTACK1H);
                    emoting = true;
                }
            }

            return;
        }

        events.Update(diff);

        if (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
                case 1:
                    DoCastAOE(296523); // Defeaning howl
                    events.Repeat(25s, 30s);
                    break;
            }
        }
        DoMeleeAttackIfReady();
    }


    TaskScheduler scheduler;
    EventMap events;
};

// 700801 - npc_mawsworn_tormentor_700801
struct npc_mawsworn_tormentor_700801 : public ScriptedAI
{
public:
    npc_mawsworn_tormentor_700801(Creature* creature) : ScriptedAI(creature) { }

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
        events.Reset();
        events.ScheduleEvent(1, 5s, 20s);
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
                DoCastAOE(347404); // Harrow
                events.Repeat(25s, 30s);
                break;
            }
        }
        DoMeleeAttackIfReady();
    }



    TaskScheduler scheduler;
    EventMap events;
};

// 700807 - npc_mawsworn_regulator_700807
struct npc_mawsworn_regulator_700807 : public ScriptedAI
{
public:
    npc_mawsworn_regulator_700807(Creature* creature) : ScriptedAI(creature) { }

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
        events.Reset();
        events.ScheduleEvent(1, 5s, 20s);
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
                DoCastVictim(355872); // Gavel
                events.Repeat(25s, 30s);
                break;
            }
        }
        DoMeleeAttackIfReady();
    }


    TaskScheduler scheduler;
    EventMap events;
};

// 700803 - npc_mawsworn_axeguard_700803
struct npc_mawsworn_axeguard_700803 : public ScriptedAI
{
public:
    npc_mawsworn_axeguard_700803(Creature* creature) : ScriptedAI(creature) { }

    void InitializeAI() override
    {
        me->SetEmoteState(Emote::EMOTE_STATE_READY1H);
    }

    void Reset() override
    {
        /// TODO: Fill this function
    }

    void JustEngagedWith(Unit* who) override
    {
        me->SetEmoteState(Emote::EMOTE_ONESHOT_NONE);
    }

    bool emoting = false;

    void UpdateAI(uint32 diff) override
    {
        scheduler.Update(diff);

        if (!UpdateVictim())
        {
            if (!me->IsEngaged() && !me->isDead() && (!me->movespline || me->movespline->Finalized()))
            {
                auto dog = me->FindNearestCreature(700808, 10.0f);
                if (!dog && emoting)
                {
                    emoting = false;
                    me->SetEmoteState(Emote::EMOTE_ONESHOT_NONE);
                }
                if (dog && !emoting)
                {
                    me->SetEmoteState(Emote::EMOTE_STATE_READY2H);
                    emoting = true;
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

// 700814 - npc_mawsworn_elite_700814
struct npc_mawsworn_elite_700814 : public ScriptedAI
{
public:
    npc_mawsworn_elite_700814(Creature* creature) : ScriptedAI(creature) { }

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

// 700815 - npc_maw_guardian_700815
struct npc_maw_guardian_700815 : public ScriptedAI
{
public:
    npc_maw_guardian_700815(Creature* creature) : ScriptedAI(creature)
    {
        ApplyAllImmunities(true);
    }

    void InitializeAI() override
    {
        /// TODO: Fill this function
    }

    void Reset() override
    {
        /// TODO: Fill this function
    }

    void JustDied(Unit* who) override
    {
        if (auto portal = me->FindNearestCreature(700820, 500.0f, true))
            portal->RemoveUnitFlag(UnitFlags::UNIT_FLAG_NON_ATTACKABLE);
    }

    void JustEngagedWith(Unit* who) override
    {
        Talk(0);
        me->RemoveAurasDueToSpell(346815); // Channel visual

        events.Reset();
        events.ScheduleEvent(1, 5s, 10s);
        events.ScheduleEvent(2, 5s, 10s);
        events.ScheduleEvent(3, 15s, 20s);
    }

    void UpdateAI(uint32 diff) override
    {
        scheduler.Update(diff);

        if (!UpdateVictim())
        {
           //if (!me->isDead() && !me->IsEngaged() && !me->GetCurrentSpell(CurrentSpellTypes::CURRENT_CHANNELED_SPELL))
           //    DoCastSelf(346815); // Channel visual
            return;
        }

        events.Update(diff);

        if (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
                case 1:
                    DoCastAOE(362317); // Shock
                    events.Repeat(5s, 7s);
                    break;
                case 2:
                    DoCastAOE(355645); // Shock Spear
                    events.Repeat(10s, 20s);
                    break;
                case 3:
                    DoCastAOE(362317); // Shock Mines
                    events.Repeat(30s);
                    break;
            }
        }
        DoMeleeAttackIfReady();
    }


    TaskScheduler scheduler;
    EventMap events;
};
const Position PositionPortalOne = { 10618.4f, -4657.81f, -0.114514f, 6.25309f };
const Position PositionPortalTwo = { 10710.5f, -4657.25f, -0.178392f, 3.1344f };
const Position PositionPortalThree = { 10618.6f, -4732.78f, -0.0964871f, 0.0414607f };
const Position PositionPortalFour = { 10709.7f, -4733.37f, -0.0569076f, 3.16669f };

// 700816 - npc_urgoz_700816
struct npc_urgoz_700816 : public ScriptedAI
{
public:
    npc_urgoz_700816(Creature* creature) : ScriptedAI(creature)
    {
        ApplyAllImmunities(true);
    }

    void InitializeAI() override
    {
        me->SetReactState(REACT_PASSIVE);
        me->SetUnitFlag(UnitFlags::UNIT_FLAG_NON_ATTACKABLE);
    }

    void Reset() override
    {
        /// TODO: Fill this function
    }

    void JustEngagedWith(Unit* who) override
    {
        phase = false;
        phase1 = false;
        me->RemoveAllAuras();
        events.Reset();
        events.ScheduleEvent(1, 20s, 30s);
        events.ScheduleEvent(2, 1s, 30s);
    }

    void UpdateAI(uint32 diff) override
    {
        scheduler.Update(diff);

        if (!UpdateVictim())
            return;

        events.Update(diff);

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        if (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
                case 1:
                    DoCastAOE(367554);
                    events.Repeat(30s, 50s);
                    break;
                case 2:
                    DoCastVictim(212262);
                    events.Repeat(20s, 30s);
                    break;
                case 3:
                    break;
            }
        }
        DoMeleeAttackIfReady();
    }

    bool phase = false;
    bool phase1 = false;

    void DamageTaken(Unit* attacker, uint32& damage, DamageEffectType /*damageType*/, SpellInfo const* /*spellInfo = nullptr*/) override
    {
        if (!phase && me->HealthBelowPctDamaged(61, damage))
        {
            DoSummon(700803, PositionPortalThree);
            DoSummon(700803, PositionPortalThree);
            DoSummon(700808, PositionPortalFour);
            DoCast(367314);
            phase = true;
            Talk(10);
        }
        if (!phase1 && me->HealthBelowPctDamaged(21, damage))
        {
            DoSummon(700803, PositionPortalThree);
            DoSummon(700803, PositionPortalThree);
            DoSummon(700803, PositionPortalThree);
            DoSummon(700803, PositionPortalThree);
            DoSummon(700803, PositionPortalThree);
            DoSummon(700803, PositionPortalThree);
            DoSummon(700808, PositionPortalFour);
            DoSummon(700808, PositionPortalFour);
            DoCast(367314);
            phase1 = true;
            Talk(11);
        }
    }

    void JustSummoned(Creature* summ) override
    {
        if (summ->GetEntry() == 700818)
            return;

        summ->SetReactState(REACT_AGGRESSIVE);
        if (auto victim = SelectVictimCrap())
        {
            if (victim != summ->GetVictim())
                summ->AI()->AttackStart(victim);
        }
    }

    void JustDied(Unit* who) override
    {
        // dont run in challenge
        if (auto inst = me->GetInstanceScript())
            if (inst->IsChallenge())
                return;

        if (auto portal = me->FindNearestCreature(700835, 500.0f, true))
            portal->RemoveUnitFlag(UnitFlags::UNIT_FLAG_NON_ATTACKABLE);
    }

    bool didIntro = false;
    void OnUnitRelocation(Unit* unit) override
    {
        if (!didIntro && unit->GetDistance2d(me) <= 167.0f && unit->IsPlayer() && !unit->ToPlayer()->IsGameMaster())
        {
            didIntro = true;
            Talk(0);

            scheduler.Schedule(8s, [this](TaskContext context)
                {
                    Talk(1);
                    scheduler.Schedule(3s, [this](TaskContext context)
                        {
                            if (auto dezgor = me->FindNearestCreature(700817, 500.0f))
                            {
                                dezgor->AI()->DoAction(1);
                            }
                        });
                });
        }
    }

    void DoAction(int32 action) override
    {
        if (action == 1)
        {
            if (auto instance = me->GetInstanceScript())
                instance->DoCastSpellOnPlayers(139844, true, true); // 139844 freeze all player
            Talk(5); // enough of this

            scheduler.Schedule(2s, [this](TaskContext context)
                {
                    DoSummon(700818, { 10671.700195f, -4801.020020f, 6.193414f, 2.121900f }); // Juno summon

                    scheduler.Schedule(5s, [this](TaskContext context)
                        {
                            Talk(6);  // Nothing, Lord Commander! My servants are just weaker than I hoped. I will deal with this myself, don't worry!

                            scheduler.Schedule(5s, [this](TaskContext context)
                                {
                                    if (auto juno = me->FindNearestCreature(700818, 50.0f))
                                        juno->AI()->Talk(1);

                                    scheduler.Schedule(2s, [this](TaskContext context)
                                        {
                                            if (auto juno = me->FindNearestCreature(700818, 50.0f))
                                            {
                                                juno->CastSpell(juno, 367044, true);
                                                juno->DespawnOrUnsummon(200ms);
                                            }

                                            Talk(7); // this wont take long
                                            DoCast(365837); // channel spell

                                            scheduler.Schedule(10s, [this](TaskContext context)
                                                {
                                                    me->GetMap()->DoOnPlayers([](Player* player)
                                                    {
                                                        if (player->GetQuestStatus(700034) == QUEST_STATUS_INCOMPLETE || player->GetQuestStatus(700034) == QUEST_STATUS_COMPLETE)
                                                        {
                                                            player->CompleteQuest(700034);
                                                            player->RewardQuest(sObjectMgr->GetQuestTemplate(700034), LootItemType::Item, 0, player);
                                                            if (player->GetQuestStatus(700035) == QUEST_STATUS_NONE)
                                                                player->AddQuestAndCheckCompletion(sObjectMgr->GetQuestTemplate(700035), player);
                                                            player->PlayerTalkClass->SendQuestGiverQuestDetails(sObjectMgr->GetQuestTemplate(700035), player->GetGUID(), true, true);
                                                            player->RemoveAurasDueToSpell(139844);
                                                        }
                                                    });
                                                    Talk(8); // What is this??
                                                    me->RemoveUnitFlag(UNIT_FLAG_NON_ATTACKABLE);
                                                    me->SetReactState(REACT_AGGRESSIVE);

                                                    if (auto victim = SelectVictimCrap())
                                                    {
                                                        if (victim != me->GetVictim())
                                                            AttackStart(victim);
                                                    }
                                                });
                                        });
                                });
                        });
                });
        }
    }

    Unit* SelectVictimCrap()
    {
        Unit* target = me->SelectNearestTargetInAttackDistance(55.0f);

        if (target && me->_IsTargetAcceptable(target) && me->CanCreatureAttack(target))
        {
            if (!me->HasSpellFocus())
                me->SetInFront(target);
            return target;
        }

        return nullptr;
    }

    TaskScheduler scheduler;
    EventMap events;
};


const std::vector<uint32> TrashToSpawn = {
    700801,
    700802,
    700803,
    700807,
    700808,
    700810,
    700830,
    700826,
};

const std::vector<uint32> ElitesToSpawn = {
    700814,
    700822,
    700821,
    700825,
    700828,
};

// 700817 - npc_dezgor_700817
struct npc_dezgor_700817 : public ScriptedAI
{
public:
    npc_dezgor_700817(Creature* creature) : ScriptedAI(creature), summons(creature)
    {
        ApplyAllImmunities(true);
    }

    void InitializeAI() override
    {
        me->SetUnitFlag(UnitFlags::UNIT_FLAG_NON_ATTACKABLE);
        me->SetReactState(REACT_PASSIVE);
    }

    void Reset() override
    {
        /// TODO: Fill this function
    }

    uint32 phase = 0;
    uint32 totalSummons = 0;

    void JustSummoned(Creature* summ) override
    {
        summons.Summon(summ);
        totalSummons++;
        summ->SetReactState(REACT_AGGRESSIVE);

        DoZoneInCombat(summ);
    }

    void SummonedCreatureDies(Creature* summ, Unit* killer) override
    {
        if (totalSummons > 0)
            --totalSummons;
        if (totalSummons == 0)
        {
            switch (phase)
            {
                case 0:
                    if (auto urgoz = me->FindNearestCreature(700816, 500.0f))
                        urgoz->AI()->Talk(2);


                    scheduler.Schedule(1s, [this](TaskContext context)
                        {
                            for (int i = 0; i < 2; ++i)
                            {
                                scheduler.Schedule(250ms * i, [this](TaskContext context)
                                    {
                                        DoSummon(Trinity::Containers::SelectRandomContainerElement(TrashToSpawn), PositionPortalOne);
                                    });
                            }
                            for (int i = 0; i < 2; ++i)
                            {
                                scheduler.Schedule(250ms * i, [this](TaskContext context)
                                    {
                                        DoSummon(Trinity::Containers::SelectRandomContainerElement(TrashToSpawn), PositionPortalTwo);
                                    });

                            }
                            for (int i = 0; i < 2; ++i)
                            {
                                scheduler.Schedule(250ms * i, [this](TaskContext context)
                                    {
                                        DoSummon(Trinity::Containers::SelectRandomContainerElement(TrashToSpawn), PositionPortalThree);
                                    });

                            }

                            scheduler.Schedule(10s, [this](TaskContext context)
                                {
                                    DoSummon(Trinity::Containers::SelectRandomContainerElement(ElitesToSpawn), PositionPortalOne);
                                    //DoSummon(Trinity::Containers::SelectRandomContainerElement(ElitesToSpawn), PositionPortalTwo);
                                    DoSummon(Trinity::Containers::SelectRandomContainerElement(ElitesToSpawn), PositionPortalThree);
                                });
                        });
                    phase++;
                    break;
                case 1:

                    if (auto urgoz = me->FindNearestCreature(700816, 500.0f))
                        urgoz->AI()->Talk(3);
                    scheduler.Schedule(1s, [this](TaskContext context)
                        {
                            for (int i = 0; i < 2; ++i)
                            {
                                scheduler.Schedule(250ms * i, [this](TaskContext context)
                                    {
                                        DoSummon(Trinity::Containers::SelectRandomContainerElement(TrashToSpawn), PositionPortalOne);
                                    });
                            }
                            for (int i = 0; i < 2; ++i)
                            {
                                scheduler.Schedule(250ms * i, [this](TaskContext context)
                                    {
                                        DoSummon(Trinity::Containers::SelectRandomContainerElement(TrashToSpawn), PositionPortalTwo);
                                    });

                            }
                            // for (int i = 0; i < 2; ++i)
                            // {
                            //     scheduler.Schedule(250ms * i, [this](TaskContext context)
                            //         {
                            //             DoSummon(Trinity::Containers::SelectRandomContainerElement(TrashToSpawn), PositionPortalThree);
                            //         });
                            // 
                            // }
                            // for (int i = 0; i < 2; ++i)
                            // {
                            //     scheduler.Schedule(250ms * i, [this](TaskContext context)
                            //         {
                            //             DoSummon(Trinity::Containers::SelectRandomContainerElement(TrashToSpawn), PositionPortalFour);
                            //         });
                            // 
                            // }

                            scheduler.Schedule(10s, [this](TaskContext context)
                                {
                                    DoSummon(Trinity::Containers::SelectRandomContainerElement(ElitesToSpawn), PositionPortalOne);
                                    //DoSummon(Trinity::Containers::SelectRandomContainerElement(ElitesToSpawn), PositionPortalTwo);
                                    DoSummon(Trinity::Containers::SelectRandomContainerElement(ElitesToSpawn), PositionPortalThree);
                                    DoSummon(Trinity::Containers::SelectRandomContainerElement(ElitesToSpawn), PositionPortalFour);
                                });
                        });

                    phase++;
                    break;
                case 2:
                    if (auto urgoz = me->FindNearestCreature(700816, 500.0f))
                        urgoz->AI()->Talk(4);
                    phase++;
                    me->RemoveUnitFlag(UnitFlags::UNIT_FLAG_NON_ATTACKABLE);
                    me->SetReactState(REACT_AGGRESSIVE);
                    if (auto victim = SelectVictimCrap(me))
                        AttackStart(victim);
                    break;
            }
        }
    }

    void JustDied(Unit* who) override
    {
        if (auto urgoz = me->FindNearestCreature(700816, 500.0f))
        {
            urgoz->AI()->DoAction(1);

            //if (auto victim = SelectVictimCrap(urgoz))
        }
    }

    Unit* SelectVictimCrap(Creature* who = nullptr)
    {
        if (!who)
            who = me;

        Unit* target = who->SelectNearestTargetInAttackDistance(155.0f);

        if (target && who->_IsTargetAcceptable(target) && who->CanCreatureAttack(target))
        {
            if (!who->HasSpellFocus())
                who->SetInFront(target);
            return target;
        }

        return nullptr;
    }

    SummonList summons;
    bool StartEncounter = false;

    void DoAction(int32 action) override
    {
        if (action == 1)
        {
            StartEncounter = true;

            scheduler.Schedule(1s, [this](TaskContext context)
                {
                    for (int i = 0; i < 2; ++i)
                    {
                        scheduler.Schedule(250ms * i, [this](TaskContext context)
                            {
                                DoSummon(Trinity::Containers::SelectRandomContainerElement(TrashToSpawn), PositionPortalOne);
                            });
                    }
                    for (int i = 0; i < 2; ++i)
                    {
                        scheduler.Schedule(250ms * i, [this](TaskContext context)
                            {
                                DoSummon(Trinity::Containers::SelectRandomContainerElement(TrashToSpawn), PositionPortalTwo);
                            });
                    }
                });
        }
    }

    void JustEngagedWith(Unit* who) override
    {
        events.Reset();
        events.ScheduleEvent(1, 20s, 30s);
        events.ScheduleEvent(2, 5s, 15s);
        events.ScheduleEvent(3, 5s, 15s);
        events.ScheduleEvent(4, 5s, 15s);
    }

    void UpdateAI(uint32 diff) override
    {
        scheduler.Update(diff);

        if (!UpdateVictim())
            return;

        events.Update(diff);

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        if (uint32 eventId = events.ExecuteEvent())
        {
            if (me->GetVictim())
            if (eventId == 4 && me->GetDistance2d(me->GetVictim()) >= 30.0f)
                return;

            switch (eventId)
            {
                case 1:
                    DoCastSelf(367038);
                    switch (urand(0, 3))
                    {
                        case 0:
                            me->NearTeleportTo(PositionPortalOne);
                            break;
                        case 1:
                            me->NearTeleportTo(PositionPortalTwo);
                            break;
                        case 2:
                            me->NearTeleportTo(PositionPortalThree);
                            break;
                        case 3:
                            me->NearTeleportTo(PositionPortalFour);
                            break;
                    }
                    DoCastVictim(304475);
                    events.Repeat(20s, 30s);
                    break;
                case 2:
                    DoCastVictim(333820); // arcane missles
                    events.Repeat(5s, 15s);
                    break;
                case 3:
                    DoCastVictim(301891); // arcane beam
                    events.Repeat(5s, 15s);
                    break;
                case 4:
                    DoCastVictim(304180); // arcane fury
                    events.Repeat(5s, 15s);
                    break;
            }
        }
        DoMeleeAttackIfReady();
    }

    TaskScheduler scheduler;
    EventMap events;
};

// 700818 - npc_juno_700818
struct npc_juno_700818 : public ScriptedAI
{
public:
    npc_juno_700818(Creature* creature) : ScriptedAI(creature) { }

    void InitializeAI() override
    {
        me->SetReactState(REACT_PASSIVE);
        me->SetUnitFlag(UnitFlags::UNIT_FLAG_NON_ATTACKABLE);
        scheduler.Schedule(1s, [this](TaskContext context)
            {
                Talk(0);
            });
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

const Position skoldusHallPortalPath[] = {
    { 8735.39f, -1093.25f, 31.5539f, 1.52562f },
    { 8735.66f, -1090.03f, 31.4898f, 1.48635f },
    { 8735.82f, -1087.37f, 31.4854f, 1.51253f },
    { 8735.96f, -1084.85f, 31.4854f, 0.206803f },
    { 8739.13f, -1084.26f, 31.4854f, 0.0824485f },
    { 8743.17f, -1083.93f, 31.5555f, 0.0824485f },
};
// 700819 - npc_mawsworn_portal_700819
struct npc_mawsworn_portal_700819 : public ScriptedAI
{
public:
    npc_mawsworn_portal_700819(Creature* creature) : ScriptedAI(creature) { }

    void InitializeAI() override
    {
        me->SetUnitFlag(UnitFlags::UNIT_FLAG_UNINTERACTIBLE);
        me->SetUnitFlag(UnitFlags::UNIT_FLAG_NON_ATTACKABLE);
    }

    void Reset() override
    {
        /// TODO: Fill this function
    }

    void UpdateAI(uint32 diff) override
    {
        if (me->HasUnitFlag(UNIT_FLAG_NON_ATTACKABLE))
            return;

        std::list<Unit*> players;
        me->GetFriendlyUnitListInRange(players, 2.0f, true);
        players.remove_if([&](Unit* unit)
        {
            return !unit->IsPlayer() || unit->IsInCombat() || unit->ToPlayer()->IsBeingTeleported() || !unit->movespline || !unit->movespline->Finalized();
        });

        for (auto unit : players)
        {
            unit->CastSpell(unit, 369445, true); // Fade to black
            auto path = unit->GetMotionMaster()->MoveSmoothPath(1, skoldusHallPortalPath, 6, true, false, 2.5f);

            unit->ToPlayer()->KilledMonsterCredit(me->GetEntry(), me->GetGUID());
            unit->GetScheduler().Schedule(2s, [unit](TaskContext context)
            {
                unit->StopMoving();

                unit->GetScheduler().Schedule(100ms, [unit](TaskContext context)
                {
                    if (unit->ToPlayer()->GetQuestStatus(700032) == QUEST_STATUS_COMPLETE)
                    {
                        unit->ToPlayer()->RewardQuest(sObjectMgr->GetQuestTemplate(700032), LootItemType::Item, 0, unit);
                        unit->ToPlayer()->AddQuestAndCheckCompletion(sObjectMgr->GetQuestTemplate(700033), unit);
                        unit->ToPlayer()->PlayerTalkClass->SendQuestGiverQuestDetails(sObjectMgr->GetQuestTemplate(700033), unit->GetGUID(), true, true);
                    }

                    GameTele const* tele = sObjectMgr->GetGameTele(1928);
                    if (tele)
                        unit->ToPlayer()->TeleportTo(tele->mapId, tele->position_x, tele->position_y, tele->position_z, tele->orientation);
                });

            });

            SetCheckpointId(me, 1);
        }
    }
};

const Position upperReachesPortalPath[] = {
    { 10718.5f, -2301.55f, 6.00558f, 4.70081f },
    { 10718.9f, -2303.75f, 6.21278f, 1.51189f },
    { 10718.7f, -2308.69f, 9.30903f, 1.57407f },
    { 10718.8f, -2312.14f, 11.6957f, 1.54789f },
    { 10718.7f, -2315.83f, 14.3713f, 1.55116f },
    { 10718.7f, -2318.76f, 16.0725f, 1.54789f },
    { 10718.5f, -2323.34f, 16.0051f, 1.54789f },
    { 10718.4f, -2328.47f, 15.9347f, 1.54789f },
};
// 700820 - npc_mawsworn_portal_700820
struct npc_mawsworn_portal_700820 : public ScriptedAI
{
public:
    npc_mawsworn_portal_700820(Creature* creature) : ScriptedAI(creature) { }

    void InitializeAI() override
    {
        me->SetUnitFlag(UnitFlags::UNIT_FLAG_UNINTERACTIBLE);
        me->SetUnitFlag(UnitFlags::UNIT_FLAG_NON_ATTACKABLE);
    }

    void Reset() override
    {
        /// TODO: Fill this function
    }

    void UpdateAI(uint32 diff) override
    {
        if (me->HasUnitFlag(UNIT_FLAG_NON_ATTACKABLE))
            return;

        std::list<Unit*> players;
        me->GetFriendlyUnitListInRange(players, 5.0f, true);
        players.remove_if([&](Unit* unit)
        {
            return !unit->IsPlayer() || unit->IsInCombat() || unit->ToPlayer()->IsBeingTeleported() || !unit->movespline || !unit->movespline->Finalized();
        });

        for (auto unit : players)
        {
            unit->CastSpell(unit, 339763, true); // Fade to black
            auto path = unit->GetMotionMaster()->MoveSmoothPath(1, upperReachesPortalPath, 8, true, false, 2.5f);

            unit->ToPlayer()->KilledMonsterCredit(me->GetEntry(), me->GetGUID());
            unit->GetScheduler().Schedule(2s, [unit](TaskContext context)
            {
                if (unit->ToPlayer()->GetQuestStatus(700033) == QUEST_STATUS_COMPLETE)
                {
                    unit->ToPlayer()->RewardQuest(sObjectMgr->GetQuestTemplate(700033), LootItemType::Item, 0, unit);
                    unit->ToPlayer()->AddQuestAndCheckCompletion(sObjectMgr->GetQuestTemplate(700034), unit);
                    unit->ToPlayer()->PlayerTalkClass->SendQuestGiverQuestDetails(sObjectMgr->GetQuestTemplate(700034), unit->GetGUID(), true, true);
                }

                unit->StopMoving();

                unit->GetScheduler().Schedule(100ms, [unit](TaskContext context)
                {
                    GameTele const* tele = sObjectMgr->GetGameTele(1929);
                    if (tele)
                        unit->ToPlayer()->TeleportTo(tele->mapId, tele->position_x, tele->position_y, tele->position_z, tele->orientation);
                });

            });
            SetCheckpointId(me, 2);
        }
    }
};

const Position owlPortalPath[] = {
    { 10666.1f, -4838.8f, 16.1923f, 4.71829f },
    { 10666.1f, -4841.32f, 16.1923f, 4.71829f },
    { 10666.1f, -4843.98f, 16.1246f, 4.71829f },
    { 10666.8f, -4847.74f, 16.1225f, 5.53968f },
    { 10669.8f, -4848.24f, 16.1226f, 6.18436f },
    { 10672.f, -4848.47f, 16.1256f, 6.18436f },
};
// 700835  - npc_mawsworn_portal_700835 
struct npc_mawsworn_portal_700835 : public ScriptedAI
{
public:
    npc_mawsworn_portal_700835(Creature* creature) : ScriptedAI(creature) { }

    void InitializeAI() override
    {
        me->SetUnitFlag(UnitFlags::UNIT_FLAG_UNINTERACTIBLE);
        me->SetUnitFlag(UnitFlags::UNIT_FLAG_NON_ATTACKABLE);
    }

    void Reset() override
    {
        /// TODO: Fill this function
    }

    void UpdateAI(uint32 diff) override
    {
        if (me->HasUnitFlag(UNIT_FLAG_NON_ATTACKABLE))
            return;

        std::list<Unit*> players;
        me->GetFriendlyUnitListInRange(players, 5.0f, true);
        players.remove_if([&](Unit* unit)
        {
            return !unit->IsPlayer() || unit->IsInCombat() || unit->ToPlayer()->IsBeingTeleported() || !unit->movespline || !unit->movespline->Finalized();
        });

        for (auto unit : players)
        {
            unit->CastSpell(unit, 339763, true); // Fade to black
            auto path = unit->GetMotionMaster()->MoveSmoothPath(1, owlPortalPath, 6, true, false, 2.5f);

            unit->ToPlayer()->KilledMonsterCredit(me->GetEntry(), me->GetGUID());
            unit->GetScheduler().Schedule(2s, [unit](TaskContext context)
            {
                if (unit->ToPlayer()->GetQuestStatus(700035) == QUEST_STATUS_COMPLETE)
                {
                    unit->ToPlayer()->RewardQuest(sObjectMgr->GetQuestTemplate(700035), LootItemType::Item, 0, unit);
                    unit->ToPlayer()->AddQuestAndCheckCompletion(sObjectMgr->GetQuestTemplate(700036), unit);
                    unit->ToPlayer()->PlayerTalkClass->SendQuestGiverQuestDetails(sObjectMgr->GetQuestTemplate(700036), unit->GetGUID(), true, true);
                }

                unit->StopMoving();

                unit->GetScheduler().Schedule(100ms, [unit](TaskContext context)
                {
                    GameTele const* tele = sObjectMgr->GetGameTele(1935);
                    if (tele)
                        unit->ToPlayer()->TeleportTo(tele->mapId, tele->position_x, tele->position_y, tele->position_z, tele->orientation);
                });

            });
        }
    }
};

// 700802 - npc_torghast_antagonizer_700802
struct npc_torghast_antagonizer_700802 : public ScriptedAI
{
public:
    npc_torghast_antagonizer_700802(Creature* creature) : ScriptedAI(creature) { }

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

// 700810 - npc_mawsworn_acolyte_700810
struct npc_mawsworn_acolyte_700810 : public ScriptedAI
{
public:
    npc_mawsworn_acolyte_700810(Creature* creature) : ScriptedAI(creature) { }

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
        events.Reset();
        events.ScheduleEvent(1, 5s, 20s);
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
                DoCastAOE(347404); // Harrow
                events.Repeat(25s, 30s);
                break;
            }
        }
        DoMeleeAttackIfReady();
    }

    TaskScheduler scheduler;
    EventMap events;
};

// 700821 - npc_deathspeaker_700821
struct npc_deathspeaker_700821 : public ScriptedAI
{
public:
    npc_deathspeaker_700821(Creature* creature) : ScriptedAI(creature) { }

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
                    DoCastVictim(294362);
                    events.Repeat(10s, 15s);
                    break;
                case 2:
                    DoCastVictim(304093);
                    events.Repeat(10s, 15s);
                    break;
            }
        }
        DoMeleeAttackIfReady();
    }


    TaskScheduler scheduler;
    EventMap events;
};

// 700822 - npc_lord_of_torment_700822
struct npc_lord_of_torment_700822 : public ScriptedAI
{
public:
    npc_lord_of_torment_700822(Creature* creature) : ScriptedAI(creature) { }

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
        events.Reset();
        events.ScheduleEvent(1, 5s, 10s);
        events.ScheduleEvent(2, 5s, 10s);
    }

    TimePoint CanTalk;

    void UpdateAI(uint32 diff) override
    {
        scheduler.Update(diff);

        if (!UpdateVictim())
        {
            if (!me->IsEngaged() && !me->isDead())
            {
                auto now = GameTime::Now();
                if (now >= CanTalk)
                {
                    if (auto deathSpeeker = me->FindNearestCreature(700821, 20.0f))
                    {
                        me->HandleEmoteCommand(Emote::EMOTE_ONESHOT_TALK);
                        scheduler.Schedule(1s, [this](TaskContext context)
                        {
                            if (auto deathSpeeker = me->FindNearestCreature(700821, 20.0f))
                                deathSpeeker->HandleEmoteCommand(Emote::EMOTE_ONESHOT_TALK);
                        });
                    }
                    CanTalk = now + 2s;
                }
            }

            return;
        }

        events.Update(diff);

        if (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
                case 1:
                    DoCastVictim(294362);
                    events.Repeat(10s, 15s);
                    break;
                case 2:
                    DoCastVictim(292926);
                    events.Repeat(10s, 15s);
                    break;
            }
        }
        DoMeleeAttackIfReady();
    }


    TaskScheduler scheduler;
    EventMap events;
};

// 700823 - npc_oddly_large_mawrat_700823
struct npc_oddly_large_mawrat_700823 : public ScriptedAI
{
public:
    npc_oddly_large_mawrat_700823(Creature* creature) : ScriptedAI(creature) { }

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

// 700824 - npc_mawrat_700824
struct npc_mawrat_700824 : public ScriptedAI
{
public:
    npc_mawrat_700824(Creature* creature) : ScriptedAI(creature) { }

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

// 154018 - npc_prisonbreak_mauler_154018
struct npc_prisonbreak_mauler_154018 : public ScriptedAI
{
public:
    npc_prisonbreak_mauler_154018(Creature* creature) : ScriptedAI(creature) { }

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

// 157149 - npc_heartseeker_157149
struct npc_heartseeker_157149 : public ScriptedAI
{
public:
    npc_heartseeker_157149(Creature* creature) : ScriptedAI(creature) { }

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

// 700825 - npc_stonewing_ravager_700825
struct npc_stonewing_ravager_700825 : public ScriptedAI
{
public:
    npc_stonewing_ravager_700825(Creature* creature) : ScriptedAI(creature) { }

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

// 700826 - npc_prisonbreak_mauler_700826
struct npc_prisonbreak_mauler_700826 : public ScriptedAI
{
public:
    npc_prisonbreak_mauler_700826(Creature* creature) : ScriptedAI(creature) { }

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

// 700827 - npc_patrician_cromwell_700827
struct npc_patrician_cromwell_700827 : public ScriptedAI
{
public:
    npc_patrician_cromwell_700827(Creature* creature) : ScriptedAI(creature) { }

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

// 700828 - npc_lord_of_torment_700828
struct npc_lord_of_torment_700828 : public ScriptedAI
{
public:
    npc_lord_of_torment_700828(Creature* creature) : ScriptedAI(creature) { }

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

// 700830 - npc_imperial_censor_700830
struct npc_imperial_censor_700830 : public ScriptedAI
{
public:
    npc_imperial_censor_700830(Creature* creature) : ScriptedAI(creature) { }

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

// 700831 - npc_ashen_phylactery_700831
struct npc_ashen_phylactery_700831 : public ScriptedAI
{
public:
    npc_ashen_phylactery_700831(Creature* creature) : ScriptedAI(creature)
    {
        SetCombatMovement(false);
        me->SetReactState(REACT_PASSIVE);
    }

    void UpdateAI(uint32 diff) override
    {
    }
};


// 700832 - npc_maw_guardian_battery_700832
struct npc_maw_guardian_battery_700832 : public ScriptedAI
{
public:
    npc_maw_guardian_battery_700832(Creature* creature) : ScriptedAI(creature) { }

    void InitializeAI() override
    {
        /// TODO: Fill this function
        me->SetReactState(REACT_PASSIVE);
    }

    void Reset() override
    {
        /// TODO: Fill this function
    }

    void JustDied(Unit* unit) override
    {
        if (auto guardian = me->FindNearestCreature(700815, 500.0f))
        {
            unit->DealDamage(unit, guardian, guardian->CountPctFromMaxHealth(25));
            guardian->CastSpell(guardian, 368631, true);
            guardian->AI()->Talk(1);
        }
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

// 2162
// UPDATE instance_template SET script = 'instance_torghast' WHERE map = 2162
struct instance_torghast : public CustomInstanceScript
{
public:
    instance_torghast(InstanceMap* map) : CustomInstanceScript(map)
    {
        ChestSpawn = { 10677.3f, -4763.18f, -0.00701382f, 2.24102f };
        Quad = { -0.0f, -0.0f, -0.900322f, -0.435225f };
    }

    void SummonChallengeGameObject(bool door) override
    {
        if (door)
        {
            if (auto go = instance->SummonGameObject(MYTHIC_DOOR_0, { 8735.17, -1353.49, 11.5555, 4.69667 }, { -0.0f, -0.0f, -0.712643f, 0.701527f}, 0))
            {
                go->SetGoState(GOState::GO_STATE_READY);
                go->SetFlag(GameObjectFlags::GO_FLAG_NOT_SELECTABLE);
            }
        }
    }

    void OnCreatureCreate(Creature* creature) override
    {
        CustomInstanceScript::OnCreatureCreate(creature);

        // Nerf torghast dungeon by 7%
        if (!creature->IsDungeonBoss())
            creature->SetMaxHealth(creature->GetMaxHealth() * 0.93);
    }
};

void AddSC_Torghast()
{
   RegisterCreatureAI(npc_thrall_700800);
   RegisterCreatureAI(npc_sir_duke_iro_700812);
   RegisterCreatureAI(npc_mawsworn_annihilator_700813);
   RegisterCreatureAI(npc_mawsworn_seeker_700808);
   RegisterCreatureAI(npc_mawsworn_tormentor_700801);
   RegisterCreatureAI(npc_mawsworn_regulator_700807);
   RegisterCreatureAI(npc_mawsworn_axeguard_700803);
   RegisterCreatureAI(npc_mawsworn_elite_700814);
   RegisterCreatureAI(npc_maw_guardian_700815);
   RegisterCreatureAI(npc_urgoz_700816);
   RegisterCreatureAI(npc_dezgor_700817);
   RegisterCreatureAI(npc_juno_700818);
   RegisterCreatureAI(npc_mawsworn_portal_700819);
   RegisterCreatureAI(npc_mawsworn_portal_700820);
   RegisterCreatureAI(npc_torghast_antagonizer_700802);
   RegisterCreatureAI(npc_mawsworn_acolyte_700810);
   RegisterCreatureAI(npc_deathspeaker_700821);
   RegisterCreatureAI(npc_lord_of_torment_700822);
   RegisterCreatureAI(npc_oddly_large_mawrat_700823);
   RegisterCreatureAI(npc_mawrat_700824);
   RegisterCreatureAI(npc_prisonbreak_mauler_154018);
   RegisterCreatureAI(npc_heartseeker_157149);
   RegisterCreatureAI(npc_stonewing_ravager_700825);
   RegisterCreatureAI(npc_prisonbreak_mauler_700826);
   RegisterCreatureAI(npc_patrician_cromwell_700827);
   RegisterCreatureAI(npc_lord_of_torment_700828);
   RegisterCreatureAI(npc_imperial_censor_700830);
   RegisterCreatureAI(npc_ashen_phylactery_700831);
   RegisterCreatureAI(npc_maw_guardian_battery_700832);
   RegisterCreatureAI(npc_mawsworn_portal_700835);
   RegisterInstanceScript(instance_torghast, 2162);
}
// UPDATE creature_template set scriptname = 'npc_thrall_700800' where entry = 700800;
// UPDATE creature_template set scriptname = 'npc_sir_duke_iro_700812' where entry = 700812;
// UPDATE creature_template set scriptname = 'npc_mawsworn_annihilator_700813' where entry = 700813;
// UPDATE creature_template set scriptname = 'npc_mawsworn_seeker_700808' where entry = 700808;
// UPDATE creature_template set scriptname = 'npc_mawsworn_tormentor_700801' where entry = 700801;
// UPDATE creature_template set scriptname = 'npc_mawsworn_regulator_700807' where entry = 700807;
// UPDATE creature_template set scriptname = 'npc_mawsworn_axeguard_700803' where entry = 700803;
// UPDATE creature_template set scriptname = 'npc_mawsworn_elite_700814' where entry = 700814;
// UPDATE creature_template set scriptname = 'npc_maw_guardian_700815' where entry = 700815;
// UPDATE creature_template set scriptname = 'npc_urgoz_700816' where entry = 700816;
// UPDATE creature_template set scriptname = 'npc_dezgor_700817' where entry = 700817;
// UPDATE creature_template set scriptname = 'npc_juno_700818' where entry = 700818;
// UPDATE creature_template set scriptname = 'npc_mawsworn_portal_700819' where entry = 700819;
// UPDATE creature_template set scriptname = 'npc_mawsworn_portal_700820' where entry = 700820;
// UPDATE creature_template set scriptname = 'npc_torghast_antagonizer_700802' where entry = 700802;
// UPDATE creature_template set scriptname = 'npc_mawsworn_acolyte_700810' where entry = 700810;
// UPDATE creature_template set scriptname = 'npc_deathspeaker_700821' where entry = 700821;
// UPDATE creature_template set scriptname = 'npc_lord_of_torment_700822' where entry = 700822;
// UPDATE creature_template set scriptname = 'npc_oddly_large_mawrat_700823' where entry = 700823;
// UPDATE creature_template set scriptname = 'npc_mawrat_700824' where entry = 700824;
// UPDATE creature_template set scriptname = 'npc_prisonbreak_mauler_154018' where entry = 154018;
// UPDATE creature_template set scriptname = 'npc_heartseeker_157149' where entry = 157149;
// UPDATE creature_template set scriptname = 'npc_stonewing_ravager_700825' where entry = 700825;
// UPDATE creature_template set scriptname = 'npc_prisonbreak_mauler_700826' where entry = 700826;
// UPDATE creature_template set scriptname = 'npc_patrician_cromwell_700827' where entry = 700827;
// UPDATE creature_template set scriptname = 'npc_lord_of_torment_700828' where entry = 700828;
// UPDATE creature_template set scriptname = 'npc_imperial_censor_700830' where entry = 700830;
// UPDATE creature_template set scriptname = 'npc_ashen_phylactery_700831' where entry = 700831;
