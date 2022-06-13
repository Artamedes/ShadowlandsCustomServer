#include "ScriptMgr.h"
#include "Creature.h"
#include "ScriptedCreature.h"
#include "GameTime.h"
#include "../CustomInstanceScript.h"
#include "InstanceScenario.h"

const Position ChestSpawnPos = { 1394.21f, 1325.69f, 176.738f, 2.15069f };
const QuaternionData ChestQuadrantOffset = { -0.0f, -0.0f, -0.879753f, -0.475431f };

const Position DoorPos = { 1234.53f, 1344.22f, 185.082f, 6.2773f };
const QuaternionData DoorOffset = { -0.0f, -0.0f, -0.712643f, 0.701527f };

const Position PortalSpawnPos = { 1400.830811f, 1343.949463f, 177.933823f, 3.118690f };

enum NetherlightTemple
{
    NetherlighTempleMapId = 1512,

    // game_tele
    TeleNiskara = 1793,

    NpcDemonPriest   = 700408,
    NpcDemonicPriest = 700409,
    NpcDerza         = 700402,
    NpcMevra         = 700401,
    NpcAllmus        = 700400,
    NpcVelen         = 700412,
    NpcWatcherOfDeath = 700411,
    NpcNiskaraPortal = 700415,

    // Spells
    DKShadowChannel  = 335247,
    ShadowWordPain   = 332707,
    Smite            = 266146,
    Empowered        = 137969,
    Shadowbolt       = 237890,
    ShadowboltVolley = 353769,
    FearsomeHowl     = 355212,
    DogDash          = 342963,
    Rake             = 319628,
    TripleBite       = 340289,
    MagisterSoulChannel = 345355,
    DrainSoul        = 242938,
    ConeOfDeath      = 364643,
    ShadowBlast      = 251028,
    Enrage           = 316133,
    CrushingSlam     = 278222,
    ShadowBolt       = 333298,
    DrainLife        = 345116,
    ChaosBolt        = 243300,
    ChargedSlam      = 368465,
    TachyonJump      = 342317,
    SelfStun         = 141480,
    MawLazerTeleport = 367044,
    Hologramify      = 167131,

    // Bosses
    BossMevra,
    BossAllmus,
    BossDerza,
    BossCount,

    // Actions
    ActionDerzaSummonWatcher = 1,
    ActionDerzaWatcherDefeated,
    ActionVelenEvent = 1,

    // Quests
    QuestMysteriousPortal = 700022,
};

class instance_netherlight_temple : public InstanceMapScript
{
public:
    instance_netherlight_temple() : InstanceMapScript("instance_netherlight_temple", NetherlighTempleMapId) { }

    struct instance_netherlight_temple_InstanceMapScript : public CustomInstanceScript
    {
    public:
        instance_netherlight_temple_InstanceMapScript(InstanceMap* map) : CustomInstanceScript(map)
        {
            ChestSpawn = ChestSpawnPos;
            Quad = ChestQuadrantOffset;
            SetBossNumber(BossCount);
        }

        void SummonChallengeGameObject(bool door) override
        {
            if (door)
            {
                if (auto go = instance->SummonGameObject(MYTHIC_DOOR_4, DoorPos, DoorOffset, 0))
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
                if (auto tree2 = sCriteriaMgr->GetCriteriaTree(300300))
                    instanceScenario->IsCompletedCriteriaTree(tree2, nullptr);
            }
        }

        void OnCreatureCreate(Creature* creature) override
        {
            CustomInstanceScript::OnCreatureCreate(creature);

            // Nerf legion dungeon by 5%
            if (!creature->IsDungeonBoss() && !IsChallenge())
                creature->SetMaxHealth(creature->GetMaxHealth() * 0.95);

            switch (creature->GetEntry())
            {
                case NpcDerza:
                    DerzaGuid = creature->GetGUID();
                    break;
                case NpcVelen:
                    if (IsChallenge())
                        creature->DespawnOrUnsummon();

                    VelenGuid = creature->GetGUID();

                    if (DerzaDead > 0)
                        creature->AI()->DoAction(ActionDerzaSummonWatcher);

                    break;
            }
        }

        void OnUnitDeath(Unit* unit) override
        {
            if (!unit->IsCreature())
                return;

            switch (unit->GetEntry())
            {
                case NpcMevra:
                case NpcAllmus:
                    if (RequiredBossKills > 0)
                    {
                        --RequiredBossKills;
                        if (RequiredBossKills == 0)
                        {
                            if (auto derza = instance->GetCreature(DerzaGuid))
                                derza->AI()->DoAction(ActionDerzaSummonWatcher);
                        }
                    }
                    break;
                case NpcWatcherOfDeath: // Watcher of death
                    if (auto derza = instance->GetCreature(DerzaGuid))
                        derza->AI()->DoAction(ActionDerzaWatcherDefeated);
                    break;
                case NpcDerza: // derza
                    DerzaDead = 1;
                    if (auto velen = instance->GetCreature(VelenGuid))
                        velen->AI()->DoAction(ActionVelenEvent);
                    SaveToDB();
                    break;
            }
        }

        uint32 DerzaDead = 0;

        void WriteSaveDataMore(std::ostringstream& data) override
        {
            data << DerzaDead;
        }

        void ReadSaveDataMore(std::istringstream& data) override
        {
            data >> DerzaDead;
        }

        uint32 RequiredBossKills = 2;
        ObjectGuid DerzaGuid;
        ObjectGuid VelenGuid;
    };

    InstanceScript* GetInstanceScript(InstanceMap* map) const override
    {
        return new instance_netherlight_temple_InstanceMapScript(map);
    }
};

/// 700408 Demon Priest, 700409 - Demonic Priest
struct npc_demon_priest_700408 : public ScriptedAI
{
    public:
        npc_demon_priest_700408(Creature* creature) : ScriptedAI(creature) { }

        void Reset() override
        {
            events.Reset();

            if (me->GetEntry() == NpcDemonPriest)
            {
                scheduler.Schedule(1s, [this](TaskContext conext)
                {
                    if (auto voidWalker = me->FindNearestCreature(700403, 30.0f))
                    {
                        DoCast(voidWalker, DKShadowChannel);
                    }
                });
            }
        }

        void JustEngagedWith(Unit* unit)
        {
            events.Reset();
            me->RemoveAurasDueToSpell(DKShadowChannel);
            events.ScheduleEvent(1, 5s, 7s);
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
                        DoCastVictim(ShadowWordPain);
                        events.Repeat(10s, 20s);
                        break;
                }
            }


            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            DoCastVictim(Smite);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            DoMeleeAttackIfReady();
        }

    TaskScheduler scheduler;
    EventMap events;
};

struct npc_void_walker_700403 : public ScriptedAI
{
    public:
        npc_void_walker_700403(Creature* creature) : ScriptedAI(creature) { }

        void Reset() override
        {
            events.Reset();
        }

        void JustEngagedWith(Unit* who) override
        {
            DoCastSelf(Empowered);
            events.ScheduleEvent(1, 2s, 10s);
        }

        void UpdateAI(uint32 diff) override
        {
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
                        DoCastVictim(Shadowbolt);
                        events.Repeat(10s, 20s);
                        break;
                }
            }

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            DoCastVictim(237890);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;
            DoMeleeAttackIfReady();
        }

        EventMap events;
};

struct npc_void_walker_700410 : public ScriptedAI
{
    public:
        npc_void_walker_700410(Creature* creature) : ScriptedAI(creature) { }

        void Reset() override
        {
            events.Reset();
        }

        void JustEngagedWith(Unit* who) override
        {
            events.Reset();
            events.ScheduleEvent(1, 2s, 10s);
            events.ScheduleEvent(2, 2s, 10s);
        }

        void UpdateAI(uint32 diff) override
        {
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
                        DoCastVictim(ShadowboltVolley);
                        events.Repeat(10s, 20s);
                        break;
                    case 2:
                        DoCastVictim(FearsomeHowl);
                        events.Repeat(10s, 20s);
                        break;
                }
            }

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            DoCastVictim(Shadowbolt);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            DoMeleeAttackIfReady();
        }

        EventMap events;
};

struct npc_void_hound_700407 : public ScriptedAI
{
    public:
        npc_void_hound_700407(Creature* creature) : ScriptedAI(creature) { }

        void Reset() override
        {
            events.Reset();
        }

        void JustEngagedWith(Unit* who) override
        {
            events.ScheduleEvent(1, 2s, 10s);
            events.ScheduleEvent(2, 2s, 10s);
        }

        void UpdateAI(uint32 diff) override
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            if (!me->IsWithinMeleeRange(me->GetVictim()))
            {
                auto now = GameTime::Now();

                if (now >= dashTime)
                {
                    dashTime = now + Seconds(18);
                    DoCastVictim(DogDash); // Dash
                }

                return;
            }
            if (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case 1: // Rake
                        DoCastVictim(Rake);
                        events.Repeat(10s, 20s);
                        break;
                    case 2: // Triple Bite
                        DoCastVictim(TripleBite);
                        events.Repeat(10s, 20s);
                        break;
                }
            }

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;
            DoMeleeAttackIfReady();
        }

        EventMap events;
        TimePoint dashTime;
};

///  ID - 342963 Dog Dash
class spell_dog_dash_342963 : public SpellScript
{
    PrepareSpellScript(spell_dog_dash_342963);

    void CountTargets(std::list<WorldObject*>& targets)
    {
        Unit* caster = GetCaster();
        if (!caster)
            return;

        targets.clear();
        std::list<Unit*> units;
        caster->GetAttackableUnitListInRange(units, 25.f);
        units.remove_if([caster](Unit* unit)
        {
            return !caster->HasInLine(unit, 6.f, caster->GetObjectScale());
        });

        for (Unit* unit : units)
            targets.push_back(unit);
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_dog_dash_342963::CountTargets, EFFECT_1, TARGET_UNIT_RECT_CASTER_ENEMY);
    }
};

struct npc_inquisitor_brute_700406 : public ScriptedAI
{
public:
    npc_inquisitor_brute_700406(Creature* creature) : ScriptedAI(creature) { }

    void Reset() override
    {
        events.Reset();
    }

    void JustEngagedWith(Unit* who) override
    {
        events.ScheduleEvent(1, 2s, 10s);
        events.ScheduleEvent(3, Minutes(1));
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        events.Update(diff);

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        if (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
                case 1: // Slam
                {
                    auto args = CastSpellExtraArgs();
                    args.SpecialDuration = 2500;
                    me->CastSpell(me->GetVictim(), CrushingSlam, args);
                    events.Repeat(20s, 30s);
                    break;
                }
                case 3:
                    DoCast(Enrage);
                    break;
            }
        }

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        DoMeleeAttackIfReady();
    }

    EventMap events;
};

/// Derza boss (final)
struct npc_derza_700402 : public BossAI
{
    public:
        npc_derza_700402(Creature* creature) : BossAI(creature, BossDerza)
        {
            ApplyAllImmunities(true);
        }

        enum Talks
        {
            FirstEnter,
            BossesDefeated,
            WatcherDefeated,
            TalkEngaged,
            TalkDied,
        };

        void InitializeAI() override
        {
            if (instance)
            {
                if (instance->GetBossState(BossDerza) == EncounterState::NOT_STARTED)
                {
                    me->SetReactState(REACT_PASSIVE);
                    me->SetUnitFlag(UNIT_FLAG_NON_ATTACKABLE);
                    me->SetUnitFlag(UNIT_FLAG_IMMUNE_TO_PC);
                    DoCast(MagisterSoulChannel); // Channel
                }
            }
        }

        void Reset() override
        {
            BossAI::Reset();
            events.Reset();
        }

        void JustEngagedWith(Unit* who) override
        {
            if (instance)
                instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
           // Talk(TalkEngaged);
            BossAI::JustEngagedWith(who);
            events.ScheduleEvent(1, 2s, 10s);
            events.ScheduleEvent(2, 5s, 30s);
        }

        void JustDied(Unit* who) override
        {
            if (instance)
                instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);

            BossAI::JustDied(who);
            Talk(TalkDied);
        }

        void EnterEvadeMode(EvadeReason why) override
        {
            _EnterEvadeMode(why);

            _DespawnAtEvade(10s);

            if (instance)
                instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
        }

        bool m_Talked = false;
        bool m_SummonWatcher = false;

        void OnUnitRelocation(Unit* unit) override
        {
            if (!m_Talked && unit->IsPlayer())
            {
                auto dist = unit->GetDistance2d(me);
                if (dist <= 150.0f)
                {
                    Talk(FirstEnter);
                    m_Talked = true;
                }
            }

            if (m_SummonWatcher && unit->IsPlayer())
            {
                auto dist = unit->GetDistance2d(me);
                if (dist <= 75.0f)
                {
                    m_SummonWatcher = false;
                    Talk(BossesDefeated);
                    DoSummon(NpcWatcherOfDeath, PortalSpawnPos, 0s, TempSummonType::TEMPSUMMON_MANUAL_DESPAWN);
                }
            }
        }

        void DoAction(int32 action) override
        {
            if (action == ActionDerzaSummonWatcher)
            {
                m_SummonWatcher = true;
            }
            else if (action == ActionDerzaWatcherDefeated)
            {
                Talk(WatcherDefeated);
                me->SetReactState(REACT_AGGRESSIVE);
                me->RemoveUnitFlag(UNIT_FLAG_NON_ATTACKABLE);
                me->RemoveUnitFlag(UNIT_FLAG_IMMUNE_TO_PC);
                DoZoneInCombat();
            }
        }

        void UpdateAI(uint32 diff) override
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            if (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case 1: // Drain soul
                        DoCastVictim(DrainSoul);
                        events.Repeat(10s, 20s);
                        break;
                    case 2: // Cone of death
                        DoCast(ConeOfDeath);
                        events.Repeat(15s, 30s);
                        break;
                }
            }

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            DoCastVictim(ShadowBlast);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            DoMeleeAttackIfReady();
        }

        void DamageDealt(Unit* victim, uint32& damage, DamageEffectType type, SpellInfo const* spellInfo /*= nullptr*/) override
        {
            if (spellInfo && victim)
            {
                switch (spellInfo->Id)
                {
                    case DrainSoul:
                        damage += victim->CountPctFromMaxHealth(5);
                        break;
                    case ConeOfDeath:
                    {
                        uint32 addition = 5;

                        if (instance && instance->IsChallenge() && instance->GetChallenge())
                            addition *= instance->GetChallenge()->GetChallengeLevel();

                        damage += victim->CountPctFromMaxHealth(50 + addition);
                        break;
                    }
                    case ShadowBlast:
                    {
                        damage += victim->CountPctFromMaxHealth(3);
                        break;
                    }
                }
            }
        }
};

/// Mevra Boss
struct npc_mevra_700401 : public BossAI
{
    public:
        npc_mevra_700401(Creature* creature) : BossAI(creature, BossMevra)
        {
            ApplyAllImmunities(true);
        }

        void JustEngagedWith(Unit* who) override
        {
            BossAI::JustEngagedWith(who);
            events.ScheduleEvent(1, 2s, 10s);
            events.ScheduleEvent(2, 5s, 30s);

            if (instance)
                instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);

            Talk(0, who);
        }

        void EnterEvadeMode(EvadeReason why) override
        {
            _EnterEvadeMode(why);

            if (instance)
                instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
        }

        void JustDied(Unit* who) override
        {
            if (instance)
                instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);

            BossAI::JustDied(who);

            Talk(1);
        }

        void UpdateAI(uint32 diff) override
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            if (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case 1: // Drain life
                        DoCastVictim(DrainLife);
                        events.Repeat(10s, 20s);
                        break;
                    case 2: // Chaos Bolt
                        DoCastVictim(ChaosBolt);
                        events.Repeat(15s, 30s);
                        break;
                }
            }

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            DoCastVictim(ShadowBolt); // Shadow Bolt

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;
            
            DoMeleeAttackIfReady();
        }
};

/// Allmus Boss
struct npc_demon_guy_700400 : public BossAI
{
    public:
        npc_demon_guy_700400(Creature* creature) : BossAI(creature, BossAllmus)
        {
            ApplyAllImmunities(true);
        }

        void JustEngagedWith(Unit* who) override
        {
            events.ScheduleEvent(1, 2s, 10s);
            events.ScheduleEvent(2, 5s, 30s);

            if (instance)
                instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);

            Talk(0);
        }

        void EnterEvadeMode(EvadeReason why) override
        {
            _EnterEvadeMode(why);

            if (instance)
                instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
        }

        void JustDied(Unit* killer) override
        {
            if (instance)
                instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);

            BossAI::JustDied(killer);

            scheduler.Schedule(1s, [this](TaskContext context)
            {
                me->SetDisplayId(82018);
            });

            Talk(1);
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
                    case 1: // Charged Slam
                        DoCastVictim(ChargedSlam);
                        events.Repeat(10s, 20s);
                        break;
                    case 2: // Teleport
                        DoCast(TachyonJump);
                        events.Repeat(15s, 30s);
                        break;
                }
            }

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;
            
            DoMeleeAttackIfReady();
        }

        void DamageDealt(Unit* victim, uint32& damage, DamageEffectType type, SpellInfo const* spellInfo /*= nullptr*/) override
        {
            if (spellInfo && victim)
            {
                switch (spellInfo->Id)
                {
                    case ChargedSlam:
                        damage += victim->CountPctFromMaxHealth(50);
                        break;
                }
            }
        }
};

struct npc_watcher_of_death : public ScriptedAI
{
    public:
        npc_watcher_of_death(Creature* creature) : ScriptedAI(creature) { }

        void InitializeAI() override
        {
            me->SetObjectScale(3.0f);
            me->SetDisplayId(101302); // Portal displayid
            me->SetReactState(REACT_PASSIVE);
            me->SetUnitFlag(UNIT_FLAG_NON_ATTACKABLE);
            me->SetUnitFlag(UNIT_FLAG_UNINTERACTIBLE);
            scheduler.Schedule(100ms, [this](TaskContext context)
            {
                me->AddAura(Hologramify, me);
                me->SetFacingTo(3.118690f);
            });
            scheduler.Schedule(5s, [this](TaskContext context)
            {
                me->RemoveAurasDueToSpell(Hologramify);
                me->DeMorph();
                me->SetReactState(REACT_AGGRESSIVE);
                me->RemoveUnitFlag(UNIT_FLAG_NON_ATTACKABLE);
                me->RemoveUnitFlag(UNIT_FLAG_UNINTERACTIBLE);
                DoZoneInCombat();
            });
        }

        void Reset() override
        {

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

struct npc_prophet_velen_700412 : public ScriptedAI
{
    public:
        npc_prophet_velen_700412(Creature* creature) : ScriptedAI(creature) { }

        enum Velen
        {
            MawChannelDirected = 365837,
        };

        void Reset() override
        {

        }

        void DoAction(int32 action) override
        {
            if (action == ActionVelenEvent)
            {
                if (auto instance = me->GetInstanceScript())
                {
                    // Don't do event in challenge.
                    if (instance->IsChallenge())
                        return;
                }

                scheduler.Schedule(1s, [this](TaskContext context)
                {
                    Talk(0);
                });

                me->RemoveNpcFlag(NPCFlags::UNIT_NPC_FLAG_GOSSIP);
                me->RemoveNpcFlag(NPCFlags::UNIT_NPC_FLAG_QUESTGIVER);
                me->GetMotionMaster()->MovePoint(1, { 1385.790894f, 1344.201538f, 176.737656f });
            }
        }

        void MovementInform(uint32 type, uint32 id) override
        {
            if (id == 1)
            {
                me->SetNpcFlag(NPCFlags::UNIT_NPC_FLAG_GOSSIP);
                me->SetNpcFlag(NPCFlags::UNIT_NPC_FLAG_QUESTGIVER);

                scheduler.Schedule(1s, [this](TaskContext context)
                {
                    Talk(1);
                    DoCast(MawChannelDirected);
                    scheduler.Schedule(5s, [this](TaskContext context)
                    {
                        Talk(2);
                        me->RemoveAurasDueToSpell(MawChannelDirected);
                        DoSummon(NpcNiskaraPortal, PortalSpawnPos, 0s, TempSummonType::TEMPSUMMON_MANUAL_DESPAWN);

                        //if (auto map = me->GetMap())
                        //{
                        //    map->DoOnPlayers([](Player* player)
                        //    {
                        //        Conversation::CreateConversation(700304, player, *player, player->GetGUID());
                        //    });
                        //}

                    });
                });
            }
        }

        void UpdateAI(uint32 diff) override
        {
            scheduler.Update(diff);
        }

        TaskScheduler scheduler;
};

struct npc_mawswarn_portal_700415 : public ScriptedAI
{
    public:
        npc_mawswarn_portal_700415(Creature* creature) : ScriptedAI(creature) { }

        void InitializeAI() override
        {
            me->SetUnitFlag(UnitFlags::UNIT_FLAG_UNINTERACTIBLE);
        }

        void UpdateAI(uint32 diff) override
        {
            std::list<Unit*> players;
            me->GetFriendlyUnitListInRange(players, 2.0f, true);
            players.remove_if([&](Unit* unit)
            {
                return !unit->IsPlayer() || unit->IsInCombat() || unit->ToPlayer()->IsBeingTeleported() || m_PlayersToTele.count(unit->GetGUID());
            });

            auto now = GameTime::Now();

            for (auto player : players)
            {
                if (player->ToPlayer()->GetQuestStatus(QuestMysteriousPortal) == QUEST_STATUS_NONE)
                    continue;

                //player->CastSpell(player, SelfStun, true);
                player->CastSpell(player, MawLazerTeleport, true);
                m_PlayersToTele[player->GetGUID()] = now + Milliseconds(800);
            }

            for (auto it = m_PlayersToTele.cbegin(); it != m_PlayersToTele.cend();)
            {
                auto player = ObjectAccessor::GetPlayer(*me, it->first);
                if (!player || !player->GetSession() || player->IsBeingTeleported())
                {
                    ++it;
                    continue;
                }

                if (now >= it->second)
                {
                    player->RemoveAurasDueToSpell(MawLazerTeleport);
                    GameTele const* tele = sObjectMgr->GetGameTele(TeleNiskara);
                    player->KilledMonsterCredit(me->GetEntry(), me->GetGUID());

                    if (player->ToPlayer()->GetQuestStatus(QuestMysteriousPortal) == QUEST_STATUS_COMPLETE)
                        player->RewardQuest(sObjectMgr->GetQuestTemplate(QuestMysteriousPortal), LootItemType::Item, 0, player);

                    if (tele)
                        player->TeleportTo(tele->mapId, tele->position_x, tele->position_y, tele->position_z, tele->orientation);

                    m_PlayersToTele.erase(it++);
                }
                else
                {
                    ++it;
                }
            }
        }

        std::unordered_map<ObjectGuid, TimePoint> m_PlayersToTele;
};

void AddSC_NetherlightTemple()
{
    RegisterCreatureAI(npc_demon_priest_700408);
    RegisterCreatureAI(npc_void_walker_700403);
    RegisterCreatureAI(npc_void_walker_700410);
    RegisterCreatureAI(npc_void_hound_700407);
    RegisterCreatureAI(npc_derza_700402);
    RegisterCreatureAI(npc_inquisitor_brute_700406);
    RegisterCreatureAI(npc_mevra_700401);
    RegisterCreatureAI(npc_demon_guy_700400);
    RegisterCreatureAI(npc_watcher_of_death);
    RegisterCreatureAI(npc_prophet_velen_700412);
    RegisterCreatureAI(npc_mawswarn_portal_700415);

    RegisterSpellScript(spell_dog_dash_342963);

    new instance_netherlight_temple();
}
