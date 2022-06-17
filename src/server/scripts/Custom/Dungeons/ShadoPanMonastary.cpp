#include "ScriptMgr.h"
#include "Player.h"
#include "Creature.h"
#include "ScriptedCreature.h"
#include "CustomInstanceScript.h"
#include "InstanceScenario.h"
#include "Scenario.h"

// 700704 - npc_portal_of_light_700704
struct npc_portal_of_light_700704 : public ScriptedAI
{
public:
    npc_portal_of_light_700704(Creature* creature) : ScriptedAI(creature) { }

    void InitializeAI() override
    {
        me->SetUnitFlag(UNIT_FLAG_UNINTERACTIBLE);
    }

    void OnSpellClick(Unit* clicker, bool spellClickHandled) override
    {
        if (clicker->IsPlayer())
        {
            auto player = clicker->ToPlayer();
            //clicker->CastSpell(clicker, 367044, true);
            auto clickerGuid = clicker->GetGUID();

            auto status = clicker->ToPlayer()->GetQuestStatus(700028);
            if (status != QUEST_STATUS_REWARDED)
            {
                if (status == QUEST_STATUS_COMPLETE)
                {
                    clicker->ToPlayer()->RewardQuest(sObjectMgr->GetQuestTemplate(700028), LootItemType::Item, 0, clicker);
                    clicker->ToPlayer()->AddQuestAndCheckCompletion(sObjectMgr->GetQuestTemplate(700029), clicker);

                }
                else
                    return;
            }

            //scheduler.Schedule(800ms, [this, clickerGuid](TaskContext context)
            //{
            if (auto player = ObjectAccessor::GetPlayer(*me, clickerGuid))
            {
                player->KilledMonsterCredit(me->GetEntry(), me->GetGUID());
                GameTele const* tele = sObjectMgr->GetGameTele(1903);
                if (tele)
                    player->TeleportTo(tele->mapId, tele->position_x, tele->position_y, tele->position_z, tele->orientation);
            }
            //});
        }
    }
};

// 700711 - npc_corrupted_light_700711
struct npc_corrupted_light_700711 : public ScriptedAI
{
public:
    npc_corrupted_light_700711(Creature* creature) : ScriptedAI(creature) { }

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
        events.ScheduleEvent(2, 25s, 30s);
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
                    DoCastAOE(365834);
                    events.Repeat(7s, 20s);
                    break;
                case 2:
                {
                    DoCastAOE(360145);

                    std::list<Player*> players;
                    Trinity::AnyPlayerInObjectRangeCheck checker(me, 50.0f);
                    Trinity::PlayerListSearcher<Trinity::AnyPlayerInObjectRangeCheck> searcher(me, players, checker);
                    Cell::VisitWorldObjects(me, searcher, 50.0f);

                    for (auto u : players)
                    {
                        if (u)
                            if (u->HasAura(365834))
                            {
                                uint32 dam = u->GetHealth();
                                Unit::DealDamage(me, u, dam);
                            }
                    }

                    events.Repeat(7s, 20s);
                    break;
                }
            }
        }
        DoMeleeAttackIfReady();
    }

    TaskScheduler scheduler;
    EventMap events;
};

// 700712 - npc_kang_dae_whitegarden_700712
struct npc_kang_dae_whitegarden_700712 : public ScriptedAI
{
public:
    npc_kang_dae_whitegarden_700712(Creature* creature) : ScriptedAI(creature)
    {
        ApplyAllImmunities(true);
    }

    enum eSpells
    {
        MindBlast = 314801,
        MindFlay = 310552,
        DarkSmite = 310845,
        SCK = 330901,
        ROP = 116844,
        FlyingSerpentKick = 127807,
        SkullCrack = 83933,
    };

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

        Talk(0);
        events.ScheduleEvent(1, 1s, 10s);
        events.ScheduleEvent(2, 1s, 10s);
        events.ScheduleEvent(3, 1s, 10s);
        events.ScheduleEvent(4, 5s, 10s);
        events.ScheduleEvent(5, 25s, 30s);
        events.ScheduleEvent(6, 5s, 30s);
        events.ScheduleEvent(7, 25s, 40s);
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
                    DoCastVictim(MindBlast);
                    events.Repeat(5s, 15s);
                    break;
                case 2:
                    DoCastVictim(MindFlay);
                    events.Repeat(5s, 15s);
                    break;
                case 3:
                    DoCastVictim(DarkSmite);
                    events.Repeat(10s, 25s);
                    break;
                case 4:
                    DoCast(eSpells::SCK);
                    events.Repeat(5s, 10s);
                    break;
                case 5:
                    DoCast(eSpells::ROP);
                    events.Repeat(25s, 30s);
                    break;
                case 6:
                    DoCast(eSpells::FlyingSerpentKick);
                    events.Repeat(5s, 30s);
                    break;
                case 7:
                    DoCastVictim(eSpells::SkullCrack);
                    events.Repeat(25s, 40s);
                    break;
            }
        }
        DoMeleeAttackIfReady();
    }

    TaskScheduler scheduler;
    EventMap events;
};

// 700713 - npc_lord_darius_700713
struct npc_lord_darius_700713 : public ScriptedAI
{
public:
    npc_lord_darius_700713(Creature* creature) : ScriptedAI(creature)
    {
        ApplyAllImmunities(true);
    }

    void InitializeAI() override
    {
        /// TODO: Fill this function
        me->SetUnitFlag(UNIT_FLAG_NON_ATTACKABLE);
        me->DeMorph();
    }

    void Reset() override
    {
        /// TODO: Fill this function
        me->DeMorph();
        phase = false;
        phase = false;
        isPhasing = false;
        me->SetReactState(REACT_AGGRESSIVE);

    }

    void JustEngagedWith(Unit* who) override
    {
        me->DeMorph();
        phase = false;
        phase = false;
        isPhasing = false;
        me->SetReactState(REACT_AGGRESSIVE);

        events.Reset();
        events.ScheduleEvent(1, 10s, 20s);
        events.ScheduleEvent(2, 10s, 20s);
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
                    DoCastVictim(361209); // Furious slam
                    events.Repeat(5s, 15s);
                    break;
                case 2:
                    DoCastSelf(367554); // dark purge
                    events.Repeat(30s, 40s);
                    break;
                case 3:
                    DoCastSelf(364248); // dark zeal
                    events.Repeat(10s, 30s);
                    break;
            }
        }
        DoMeleeAttackIfReady();
    }


    bool intro = false;
    void OnUnitRelocation(Unit* who) override
    {
        /// TODO: Fill this function
        if (!intro && who->IsPlayer() && who->GetDistance2d(me) <= 30.0f)
        {
            intro = true;
            Talk(0);
            scheduler.Schedule(500ms, [this](TaskContext context)
                {
                    events.ScheduleEvent(3, 1s, 5s);
                    me->RemoveUnitFlag(UNIT_FLAG_NON_ATTACKABLE);

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

    bool phase = false;
    bool isPhasing = false;
    void DamageTaken(Unit* attacker, uint32& damage, DamageEffectType damageType, SpellInfo const* spell) override
    {
        if (isPhasing)
        {
            damage = 0;
            attacker->AttackStop();
        }

        if (!phase && me->HealthBelowPctDamaged(51, damage))
        {
            phase = true;
            isPhasing = true;
            me->SetReactState(REACT_PASSIVE);
            DoCast(366165);
            scheduler.Schedule(1s, [this](TaskContext context)
                {
                    Talk(1);
                    me->SetDisplayId(92451);
                    me->SetReactState(REACT_AGGRESSIVE);
                    isPhasing = false;
                });
        }
    }

    void JustDied(Unit* who) override
    {
        if (auto portal = me->FindNearestCreature(700704, 50.0f, true))
        {
            portal->RemoveUnitFlag(UNIT_FLAG_UNINTERACTIBLE);
        }
    }

    void OnSpellClick(Unit* clicker, bool spellClickHandled) override
    {
        /// TODO: Fill this function
    }

    TaskScheduler scheduler;
    EventMap events;
};

// 700714 - npc_rehael_700714
struct npc_rehael_700714 : public ScriptedAI
{
public:
    npc_rehael_700714(Creature* creature) : ScriptedAI(creature)
    {
        ApplyAllImmunities(true);
    }

    enum eSpells
    {
        HolySmite = 280939,
        Chastise = 200200,
        HolyFire = 242194,
    };

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
        Talk(1);
        events.ScheduleEvent(1, 5s, 10s);
        events.ScheduleEvent(2, 25s, 30s);
        events.ScheduleEvent(3, 5s, 30s);
    }

    void JustDied(Unit* who) override
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
                case 1:
                    DoCast(eSpells::HolySmite);
                    events.Repeat(5s, 10s);
                    break;
                case 2:
                    DoCast(eSpells::HolyFire);
                    events.Repeat(25s, 30s);
                    break;
                case 3:
                    DoCast(eSpells::Chastise);
                    events.Repeat(5s, 30s);
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

// 700715 - npc_yofiel_700715
struct npc_yofiel_700715 : public ScriptedAI
{
public:
    npc_yofiel_700715(Creature* creature) : ScriptedAI(creature)
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

    void JustEngagedWith(Unit* who) override
    {
        events.Reset();
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
                    DoCastVictim(368168, true);
                    DoCastVictim(368168, true);
                    events.Repeat(10s, 20s);
                    break;
            }
        }
        DoMeleeAttackIfReady();
    }

    bool dead = false;
    bool phase = false;
    void DamageTaken(Unit* attacker, uint32& damage, DamageEffectType damageType, SpellInfo const* spell) override
    {
        if (me->GetHealth() <= damage)
        {
            damage = 0;
            if (attacker)
                attacker->AttackStop();
            if (!dead)
            {
                Talk(0);
                dead = true;
                me->UpdateEntry(700727);
                EnterEvadeMode();
                me->SetFaction(35);
                me->SetReactState(REACT_PASSIVE);
                me->SetUnitFlag(UnitFlags::UNIT_FLAG_NON_ATTACKABLE);

                if (auto instanceMap = me->GetMap()->ToInstanceMap())
                {
                    instanceMap->DoOnPlayers([this](Player* player)
                    {
                        player->KilledMonsterCredit(700715, me->GetGUID());
                    });

                    if (auto scenario = instanceMap->GetInstanceScenario())
                    {
                        scenario->UpdateCriteria(CriteriaType::DefeatDungeonEncounter, 700715, 0, 0, me, attacker->ToPlayer());
                        if (CriteriaTree const* tree = sCriteriaMgr->GetCriteriaTree(300708))
                            scenario->CompletedCriteriaTree(tree, nullptr);
                    }
                }
            }
        }
    }

    TaskScheduler scheduler;
    EventMap events;
};

// 700716 - npc_watcher_700716
struct npc_watcher_700716 : public ScriptedAI
{
public:
    npc_watcher_700716(Creature* creature) : ScriptedAI(creature) { }

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

// 700717 - npc_paladin_enforcer_700717
struct npc_paladin_enforcer_700717 : public ScriptedAI
{
public:
    npc_paladin_enforcer_700717(Creature* creature) : ScriptedAI(creature) { }

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

// 700718 - npc_high_priest_700718
struct npc_high_priest_700718 : public ScriptedAI
{
public:
    npc_high_priest_700718(Creature* creature) : ScriptedAI(creature) { }

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
                    DoCastVictim(273770);
                    events.Repeat(20s);
                    break;
            }
        }

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        DoCastVictim(172673);

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        DoMeleeAttackIfReady();
    }

    void OnSpellClick(Unit* clicker, bool spellClickHandled) override
    {
        /// TODO: Fill this function
    }

    TaskScheduler scheduler;
    EventMap events;
};

// 700719 - npc_inquisitor_700719
struct npc_inquisitor_700719 : public ScriptedAI
{
public:
    npc_inquisitor_700719(Creature* creature) : ScriptedAI(creature) { }

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

    void OnSpellClick(Unit* clicker, bool spellClickHandled) override
    {
        /// TODO: Fill this function
    }

    TaskScheduler scheduler;
    EventMap events;
};

// 700720 - npc_corrupted_priest_700720
struct npc_corrupted_priest_700720 : public ScriptedAI
{
public:
    npc_corrupted_priest_700720(Creature* creature) : ScriptedAI(creature) { }

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
                    DoCastVictim(316711);
                    events.Repeat(10s);
                    break;
            }
        }

        if (me->GetCurrentSpell(CurrentSpellTypes::CURRENT_CHANNELED_SPELL))
            return;

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        DoCastVictim(314592);

        DoMeleeAttackIfReady();
    }

    void OnSpellClick(Unit* clicker, bool spellClickHandled) override
    {
        /// TODO: Fill this function
    }

    TaskScheduler scheduler;
    EventMap events;
};

struct instance_lightdng2 : public CustomInstanceScript
{
public:
    instance_lightdng2(InstanceMap* map) : CustomInstanceScript(map)
    {
        ChestSpawn = { 3853.49f, 2586.39f, 754.541f, 1.25613f };
        Quad = { -0.0f, -0.0f, -0.587579f, -0.809167f };
    }

    void SummonChallengeGameObject(bool door) override
    {
        if (door)
        {
            if (auto go = instance->SummonGameObject(MYTHIC_DOOR_0, { 3682.15f, 2628.64f, 771.248f, 0.460913f }, { -0.0f, -0.0f, -0.228422f, -0.973562f }, 0))
            {
                go->SetGoState(GOState::GO_STATE_READY);
                go->SetFlag(GameObjectFlags::GO_FLAG_NOT_SELECTABLE);
            }
        }
    }

    void OnCompletedCriteriaTree(CriteriaTree const* /*tree*/) override
    {
        if (InstanceScenario* instanceScenario = instance->GetInstanceScenario())
        {
            if (auto tree2 = sCriteriaMgr->GetCriteriaTree(300700))
                instanceScenario->IsCompletedCriteriaTree(tree2, nullptr);
        }
    }

    void OnCreatureCreate(Creature* creature) override
    {
        CustomInstanceScript::OnCreatureCreate(creature);

        // Nerf light dungeon by 7%
        if (!creature->IsDungeonBoss())
            creature->SetMaxHealth(creature->GetMaxHealth() * 0.93);
    }

    void OnPlayerEnter(Player* player) override
    {
        CustomInstanceScript::OnPlayerEnter(player);

        if (player->GetQuestStatus(700028) == QUEST_STATUS_INCOMPLETE)
        {
            player->KilledMonsterCredit(700699);
        }
    }
};


void AddSC_ShadoPanMonastary()
{
   RegisterCreatureAI(npc_portal_of_light_700704);
   RegisterCreatureAI(npc_corrupted_light_700711);
   RegisterCreatureAI(npc_kang_dae_whitegarden_700712);
   RegisterCreatureAI(npc_lord_darius_700713);
   RegisterCreatureAI(npc_rehael_700714);
   RegisterCreatureAI(npc_yofiel_700715);
   RegisterCreatureAI(npc_watcher_700716);
   RegisterCreatureAI(npc_paladin_enforcer_700717);
   RegisterCreatureAI(npc_high_priest_700718);
   RegisterCreatureAI(npc_inquisitor_700719);
   RegisterCreatureAI(npc_corrupted_priest_700720);
   RegisterInstanceScript(instance_lightdng2, 959);
}
// 
// UPDATE creature_template set scriptname = 'npc_angelic_warrior_700703' where entry = 700703;
// UPDATE creature_template set scriptname = 'npc_weapon_of_light_700701' where entry = 700701;
// UPDATE creature_template set scriptname = 'npc_portal_of_light_700704' where entry = 700704;
// UPDATE creature_template set scriptname = 'npc_corrupted_light_700711' where entry = 700711;
// UPDATE creature_template set scriptname = 'npc_disciple_of_light_700702' where entry = 700702;
// UPDATE creature_template set scriptname = 'npc_kang_dae_whitegarden_700712' where entry = 700712;
// UPDATE creature_template set scriptname = 'npc_lord_darius_700713' where entry = 700713;
// UPDATE creature_template set scriptname = 'npc_rehael_700714' where entry = 700714;
// UPDATE creature_template set scriptname = 'npc_yofiel_700715' where entry = 700715;
// UPDATE creature_template set scriptname = 'npc_protector_of_light_700710' where entry = 700710;
// UPDATE creature_template set scriptname = 'npc_watcher_700716' where entry = 700716;
// UPDATE creature_template set scriptname = 'npc_paladin_enforcer_700717' where entry = 700717;
// UPDATE creature_template set scriptname = 'npc_high_priest_700718' where entry = 700718;
// UPDATE creature_template set scriptname = 'npc_inquisitor_700719' where entry = 700719;
// UPDATE creature_template set scriptname = 'npc_corrupted_priest_700720' where entry = 700720;
