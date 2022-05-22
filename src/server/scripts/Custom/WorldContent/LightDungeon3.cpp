#include "ScriptMgr.h"
#include "Player.h"
#include "Creature.h"
#include "Containers.h"
#include "ScriptedCreature.h"
#include "../CustomInstanceScript.h"
#include "InstanceScenario.h"

// 700011 - npc_oogway_700011
struct npc_oogway_700011 : public ScriptedAI
{
public:
    npc_oogway_700011(Creature* creature) : ScriptedAI(creature) { }

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

    void OnUnitRelocation(Unit* who) override
    {
        /// TODO: Fill this function
    }
    void OnSpellClick(Unit* clicker, bool spellClickHandled) override
    {
        /// TODO: Fill this function
    }

    TaskScheduler scheduler;
    EventMap events;
};

const Position cornerPosErnoch[] = {
    { -4023.0f, -11007.6f, 715.225f, 3.01729f },
    { -4039.08f, -11022.4f, 715.225f, 1.81628f },
    { -4070.03f, -10994.7f, 715.227f, 6.12288f },
    { -4054.84f, -10978.9f, 715.227f, 4.91861f },
};
// 700721 - npc_ernoch_700721
struct npc_ernoch_700721 : public ScriptedAI
{
public:
    npc_ernoch_700721(Creature* creature) : ScriptedAI(creature), summons(creature) { }

    enum Ernoch
    {
        NormalModel = 70822,
        BlueModel = 70823,
        GreenModel = 70824,
        PurpleModel = 70825,

        SpinningCraneKick = 330901,
        BurningLegSweep = 227568,
        FistsOfFury = 283773,
        RisingSunKick = 282285,
    };

    bool isSummon = false;
    bool ClonePhase = false;
    SummonList summons;

    void JustEngagedWith(Unit* who) override
    {
        if (me->GetOwner() || isSummon)
            return;

        scheduler.CancelAll();
        events.ScheduleEvent(1, 5s, 10s);
        events.ScheduleEvent(2, 5s, 10s);
        events.ScheduleEvent(3, 5s, 10s);
    }

    void JustSummoned(Creature* who) override
    {
        summons.Summon(who);
    }

    void IsSummonedBy(WorldObject* o) override
    {
        if (!o)
            return;
        if (!o->IsUnit())
            return;
        isSummon = true;
        didPhase = true;
        ClonePhase = true;
        auto owner = o->ToUnit();
        me->SetReactState(REACT_PASSIVE);
    }

    void Reset() override
    {
        ClonePhase = false;
        me->SetReactState(REACT_AGGRESSIVE);
        me->SetControlled(false, UnitState::UNIT_STATE_ROOT);
        summons.DespawnAll();
        me->DeMorph();
    }

    void JustDied(Unit* who) override
    {
        if (isSummon)
            me->DespawnOrUnsummon();
        else
        {
            if (auto tome = me->FindNearestCreature(700729, 500.0f))
                tome->RemoveUnitFlag(UnitFlags::UNIT_FLAG_UNINTERACTIBLE);
        }

        scheduler.CancelAll();
        summons.DespawnAll();
    }

    void UpdateAI(uint32 diff) override
    {
        scheduler.Update(diff);

        if (ClonePhase && !me->isDead())
        {
            if (!me->GetCurrentSpell(CurrentSpellTypes::CURRENT_CHANNELED_SPELL))
                DoCast(SpinningCraneKick);
        }

        if (!UpdateVictim())
            return;

        events.Update(diff);

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        while (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
                case 1:
                    DoCast(BurningLegSweep);
                    events.Repeat(20s, 25s);
                    break;
                case 2:
                    DoCastVictim(FistsOfFury);
                    events.Repeat(10s, 20s);
                    break;
                case 3:
                    DoCastVictim(RisingSunKick);
                    events.Repeat(10s, 20s);
                    break;
            }
        }

        DoMeleeAttackIfReady();
    }

    bool didPhase = false;
    void DamageTaken(Unit* attacker, uint32& damage, DamageEffectType damageType, SpellInfo const* spell) override
    {
        if (didPhase && !isSummon && me->HealthBelowPctDamaged(91, damage) && ClonePhase)
        {
            summons.DespawnAll();
            me->SetReactState(REACT_AGGRESSIVE);
            ClonePhase = false;

            me->SetControlled(false, UnitState::UNIT_STATE_ROOT);
        }

        if (!didPhase && me->HealthBelowPctDamaged(51, damage) && !isSummon && me->GetVictim())
        {
            damage = 0;
            didPhase = true;
            attacker->SendClearTarget();
            me->DestroyForNearbyPlayers();
            if (attacker->IsPlayer())
                attacker->ToPlayer()->SetSelection(ObjectGuid::Empty);
            me->SendClearTarget();

            scheduler.Schedule(1s, [this](TaskContext context)
                {
                    std::vector<Position> positions;
                    std::vector<uint32> models = { NormalModel, BlueModel, GreenModel, PurpleModel };
                    positions.reserve(4);
                    for (auto p : cornerPosErnoch)
                        positions.emplace_back(p);

                    me->RemoveAllAuras();
                    me->SetFullHealth();
                    me->UpdateObjectVisibility();

                    Trinity::Containers::RandomShuffle(positions);
                    Trinity::Containers::RandomShuffle(models);

                    bool first = false;
                    int i = 0;


                    for (auto const& p : positions)
                    {
                        if (!first)
                        {
                            first = true;
                            me->NearTeleportTo(p);
                            ClonePhase = true;
                            DoCast(SpinningCraneKick);
                            me->SetControlled(true, UnitState::UNIT_STATE_ROOT);
                            me->SetDisplayId(models[i++]);
                            Talk(0);
                            continue;
                        }

                        if (auto summon = DoSummon(me->GetEntry(), p, 0s, TempSummonType::TEMPSUMMON_DEAD_DESPAWN))
                        {
                            summon->AI()->AttackStart(me->GetVictim());
                            summon->AI()->Talk(0);
                            summon->SetTarget(me->GetVictim()->GetGUID());
                            summon->SetLevel(me->GetLevel());
                            summon->SetReactState(REACT_PASSIVE);
                            summon->CastSpell(summon, SpinningCraneKick, true);
                            summon->SetControlled(true, UnitState::UNIT_STATE_ROOT);
                            summon->SetDisplayId(models[i++]);
                        }
                    }
                });
        }
    }

    TaskScheduler scheduler;
    EventMap events;
};

// 700722 - npc_kairos_700722
struct npc_kairos_700722 : public ScriptedAI
{
public:
    npc_kairos_700722(Creature* creature) : ScriptedAI(creature) { }

    void InitializeAI() override
    {
        /// TODO: Fill this function
    }

    void Reset() override
    {
        events.Reset();
    }

    void JustEngagedWith(Unit* who) override
    {
        events.Reset();
        events.ScheduleEvent(1, 5s, 10s);
        events.ScheduleEvent(2, 5s, 10s);
        events.ScheduleEvent(3, 15s, 40s);
        events.ScheduleEvent(4, 15s, 40s);
        events.ScheduleEvent(5, 15s, 40s);
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
                    DoCast(365834); // Fear of the Unknowwn
                    events.Repeat(10s, 20s);
                    break;
                case 2:
                    DoCastVictim(317959, true); // Dark Lash
                    events.Repeat(2s, 5s);
                    break;
                case 3:
                    DoCast(364248); // dark zeal
                    events.Repeat(12s, 35s);
                    break;
                case 4:
                    DoCastVictim(345306); // Void Bolt
                    events.Repeat(12s, 35s);
                    break;
                case 5:
                    DoCastVictim(341176); // Void Frenzy
                    events.Repeat(12s, 35s);
                    break;
            }
        }
        DoMeleeAttackIfReady();
    }

    bool didIntro = false;
    void OnUnitRelocation(Unit* who) override
    {
        if (didIntro)
            return;

        if (who->IsPlayer() && who->GetDistance2d(me) <= 20.0f)
        {
            DoCast(366165);
            didIntro = true;
            scheduler.Schedule(500ms, [this](TaskContext context)
                {
                    me->SetDisplayId(80096);

                    if (auto victim = SelectVictimCrap())
                    {
                        if (victim != me->GetVictim())
                            AttackStart(victim);
                    }

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

// 700723 - npc_allmus_700723
struct npc_allmus_700723 : public ScriptedAI
{
public:
    npc_allmus_700723(Creature* creature) : ScriptedAI(creature) { }

    void InitializeAI() override
    {
        /// TODO: Fill this function
    }

    void Reset() override
    {
        events.Reset();
    }

    void JustEngagedWith(Unit* who) override
    {
        Talk(0);
        events.Reset();
        events.ScheduleEvent(1, 2s, 10s);
        events.ScheduleEvent(2, 5s, 30s);
    }

    void JustDied(Unit* killer) override
    {
        scheduler.Schedule(1s, [this](TaskContext context)
        {
            me->SetDisplayId(82018);
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
                case 1: // Charged Slam
                    DoCastVictim(368465);
                    events.Repeat(10s, 20s);
                    break;
                case 2: // Teleport
                    DoCast(342317);
                    events.Repeat(15s, 30s);
                    break;
            }
        }
        DoMeleeAttackIfReady();
    }

    void OnUnitRelocation(Unit* who) override
    {
        /// TODO: Fill this function
    }
    void OnSpellClick(Unit* clicker, bool spellClickHandled) override
    {
        /// TODO: Fill this function
    }

    TaskScheduler scheduler;
    EventMap events;
};

// 700724 - npc_torzas_700724
struct npc_torzas_700724 : public ScriptedAI
{
public:
    npc_torzas_700724(Creature* creature) : ScriptedAI(creature) { }

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
        events.ScheduleEvent(1, 5s, 15s);
        events.ScheduleEvent(2, 5s, 15s);
        events.ScheduleEvent(3, 5s, 15s);
        events.ScheduleEvent(4, 15s, 16s);
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
                    DoCastVictim(360908); // Feeding Time
                    events.Repeat(10s, 30s);
                    break;
                case 2:
                    DoCastVictim(347087); // Ravage
                    events.Repeat(10s, 30s);
                    break;
                case 3:
                    DoCastVictim(337785); // Cleanse pain
                    events.Repeat(10s, 30s);
                    break;
                case 4:
                    DoCastVictim(212262); // hand of gul'dan
                    events.Repeat(30s, 40s);
                    break;
            }
        }
        DoMeleeAttackIfReady();
    }

    void OnUnitRelocation(Unit* who) override
    {
        /// TODO: Fill this function
    }
    void OnSpellClick(Unit* clicker, bool spellClickHandled) override
    {
        /// TODO: Fill this function
    }

    TaskScheduler scheduler;
    EventMap events;
};

// 700725 - npc_mawsworn_warden_700725
struct npc_mawsworn_warden_700725 : public ScriptedAI
{
public:
    npc_mawsworn_warden_700725(Creature* creature) : ScriptedAI(creature) { }

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

    void OnUnitRelocation(Unit* who) override
    {
        /// TODO: Fill this function
    }
    void OnSpellClick(Unit* clicker, bool spellClickHandled) override
    {
        /// TODO: Fill this function
    }

    TaskScheduler scheduler;
    EventMap events;
};

// 700726 - npc_watcher_of_death_700726
struct npc_watcher_of_death_700726 : public ScriptedAI
{
public:
    npc_watcher_of_death_700726(Creature* creature) : ScriptedAI(creature) { }

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

    void OnUnitRelocation(Unit* who) override
    {
        /// TODO: Fill this function
    }
    void OnSpellClick(Unit* clicker, bool spellClickHandled) override
    {
        /// TODO: Fill this function
    }

    TaskScheduler scheduler;
    EventMap events;
};


struct instance_lightdng3 : public CustomInstanceScript
{
public:
    instance_lightdng3(InstanceMap* map) : CustomInstanceScript(map)
    {
        ChestSpawn = { -4085.43f, -11044.5f, 721.728f, 0.8607f };
        Quad = { -0.0f, -0.0f, -0.417189f, -0.90882f };
    }

    void SummonChallengeGameObject(bool door) override
    {
        if (door)
        {
            if (auto go = instance->SummonGameObject(MYTHIC_DOOR_4, { -3929.89f, -10671.3f, 751.396f, 4.00557f }, { -0.0f, -0.0f, -0.712643f, 0.701527f }, 0))
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
            if (auto tree2 = sCriteriaMgr->GetCriteriaTree(300800))
                instanceScenario->IsCompletedCriteriaTree(tree2, nullptr);
        }
    }
};

class lightdng3_playerscript : public PlayerScript
{
public:
    lightdng3_playerscript() : PlayerScript("lightdng3_playerscript") { }


    void OnQuestStatusChange(Player* player, uint32 questId)
    {
        if (player->GetMapId() != 1712)
            return;

        if (questId == 700030 && player->GetQuestStatus(questId) == QUEST_STATUS_COMPLETE)
        {
            Conversation::CreateConversation(700307, player, *player, player->GetGUID());
        }
    }
};
// 700729 - npc_tome_of_corruption_700729
struct npc_tome_of_corruption_700729 : public ScriptedAI
{
public:
    npc_tome_of_corruption_700729(Creature* creature) : ScriptedAI(creature) { }

    bool CanSeeOrDetect(WorldObject const* who) const override
    {
        if (who->IsPlayer())
        {
            auto player = who->ToPlayer();
            auto status = player->GetQuestStatus(700030); // 700036 finish the fight
            switch (status)
            {
                case QUEST_STATUS_INCOMPLETE:
                    return true;
                default:
                    return false;
            }
        }

        return false;
    }

    void OnSpellClick(Unit* clicker, bool spellClickHandled) override
    {
        if (clicker->IsPlayer())
            clicker->ToPlayer()->KilledMonsterCredit(me->GetEntry(), me->GetGUID());

        me->UpdateObjectVisibility();
    }
};


void AddSC_LightDungeon3()
{
   RegisterCreatureAI(npc_ernoch_700721);
   RegisterCreatureAI(npc_kairos_700722);
   RegisterCreatureAI(npc_allmus_700723);
   RegisterCreatureAI(npc_torzas_700724);
   RegisterCreatureAI(npc_mawsworn_warden_700725);
   RegisterCreatureAI(npc_watcher_of_death_700726);
   RegisterInstanceScript(instance_lightdng3, 1712);
   RegisterCreatureAI(npc_tome_of_corruption_700729);

   new lightdng3_playerscript();
}
