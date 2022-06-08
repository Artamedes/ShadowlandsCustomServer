#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "../CustomInstanceScript.h"
#include "MoveSpline.h"
#include "CriteriaHandler.h"
#include "Scenario.h"
#include "InstanceScenario.h"
#include "GenericMovementGenerator.h"
#include "AreaBoundary.h"
#include "QuestAI.h"
#include "TemporarySummon.h"
#include "ReputationMgr.h"

enum Underrot
{
    NpcBloodBall = 701013,
    SpellDummyChannel = 363390,

    BossA = 701005,
    BossB = 701003,
    BossC = 701000,

    UnderrotCriteriaID = 300000,

    BOSS_SPORECALLER_ZANCHA = 0,
    BOSS_ANDSID_THE_MECHANIC,
    BOSS_MISTER_DOCTOR,

    GobWebOne = 295356,
    GobWebTwo = 296385,

    PyramidWeb = 296384,

    UnderrotGateway = 253773,

    NpcPlagueDoctor = 701020,
};

BossBoundaryData const boundaries =
{
    { BOSS_SPORECALLER_ZANCHA,  new CircleBoundary({ 857.834f, 982.584f, 39.1488f, 4.15475f }, 200.0f)  },
    { BOSS_ANDSID_THE_MECHANIC, new CircleBoundary({ 1032.7f, 1059.12f, 33.3364f, 6.23278f }, 56.0f )},
    { BOSS_MISTER_DOCTOR,       new CircleBoundary({ 1199.37f, 1481.5f, -181.709f, 1.77237f }, 100.0f)  },
};

DoorData const doorData[] =
{
    { GobWebOne, BOSS_SPORECALLER_ZANCHA,  DOOR_TYPE_PASSAGE },
    { GobWebTwo, BOSS_ANDSID_THE_MECHANIC, DOOR_TYPE_PASSAGE },
    { PyramidWeb, BOSS_ANDSID_THE_MECHANIC, DOOR_TYPE_PASSAGE },
};
struct instance_the_underrot : public CustomInstanceScript
{
public:
    instance_the_underrot(InstanceMap* map) : CustomInstanceScript(map)
    {
        SetBossNumber(3);
        LoadBossBoundaries(boundaries);
        LoadDoorData(doorData);
        SetHeaders("UR");
        EnemyForcesCriteriaTreeId = 300004;
        ChestSpawn = { 1207.40f, 1433.150f,	-181.70f,1.78050f };
        Quad = { 0.0f, 0.0f, -0.606807f, 0.7948490f };
    }

    void SummonChallengeGameObject(bool door) override
    {
        if (door)
        {
            if (auto go = instance->SummonGameObject(MYTHIC_DOOR_4, { 636.715f,	1253.030f,	95.5464f, 0.0f }, { -0.0f, -0.0f, -0.639438f, -0.768843f }, 0))
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
            if (auto tree2 = sCriteriaMgr->GetCriteriaTree(UnderrotCriteriaID))
                instanceScenario->IsCompletedCriteriaTree(tree2, nullptr);
        }
    }

    ObjectGuid WebDoor;
    ObjectGuid WebWeb;
    ObjectGuid WebWebOne;
    // Creatures
    ObjectGuid PlagueDoctorGuid;

    void OnGameObjectCreate(GameObject* go) override
    {
        InstanceScript::OnGameObjectCreate(go);

        switch (go->GetEntry())
        {
            case PyramidWeb:
                WebDoor = go->GetGUID();
                break;
            case GobWebOne:
                WebWebOne = go->GetGUID();
                break;
            case GobWebTwo: 
                WebWeb = go->GetGUID();
                break;
        }
    }

    void OnCreatureCreate(Creature* creature) override
    {
        CustomInstanceScript::OnCreatureCreate(creature);

        switch (creature->GetEntry())
        {
            case NpcPlagueDoctor:
                PlagueDoctorGuid = creature->GetGUID();
                creature->setActive(true); // will be moved later and might be out of grid.
                break;
        }
    }

    bool SetBossState(uint32 id, EncounterState state, bool force = false) override
    {
        switch (state)
        {
            case EncounterState::DONE:
                switch (id)
                {
                    case BOSS_ANDSID_THE_MECHANIC:
                        if (auto door = instance->GetGameObject(WebDoor))
                            door->Delete();
                        if (auto door = instance->GetGameObject(WebWeb))
                            door->Delete();
                        if (auto door = instance->GetGameObject(WebWebOne))
                            door->Delete();
                        break;
                    case BOSS_MISTER_DOCTOR:
                        if (auto doctor = instance->GetCreature(PlagueDoctorGuid))
                        {
                            doctor->NearTeleportTo({ 1182.17f, 1460.16f, -181.56f, 0.924786f });
                            doctor->setActive(false); // Remove active
                        }
                        break;
                }
                break;
        }

        return InstanceScript::SetBossState(id, state);
    }

    void OnPlayerPositionChange(Player* player) override
    {
        if (GetBossState(BOSS_ANDSID_THE_MECHANIC) != EncounterState::DONE)
            return;

       // if (player->GetMap()->GetId() == 1841 && newArea->GetId() == 9391 && oldArea->GetId() == 10021)
           // if (player->GetInstanceScript() && !player->GetInstanceScript()->GetGameObject(GO_PYRAMID_WEB))
        if (player->GetAreaId() == 9391)
            if (player->GetPositionX() > 1080.0f && player->GetPositionZ() > 0 && !player->HasAura(Underrot::UnderrotGateway))
            {
                /// dismount
                player->Dismount();
                player->CastSpell(player, Underrot::UnderrotGateway);
            }
    }

    void CreatureDiesForScript(Creature* creature, Unit* killer) override
    {
        CustomInstanceScript::CreatureDiesForScript(creature, killer);

        auto shadowMilitia = sFactionStore.LookupEntry(ShadowMilitiaRep);
        if (!shadowMilitia)
            return;

        bool isBoss = creature->IsDungeonBoss();
        uint32 repAmount = isBoss ? 500 : 25;

        instance->DoOnPlayers([creature, repAmount, shadowMilitia](Player* player)
        {
            player->GetReputationMgr().ModifyReputation(shadowMilitia, repAmount);

            if (creature->GetFaction() != 35)
                if (creature->IsDungeonBoss() || roll_chance_i(50))
                    player->ModifyCurrency(PlagueSample, creature->IsDungeonBoss() ? 100 : urand(1, 3));
        });
    }
    // unneeded for now - handled internally
    //void CreatureDiesForScript(Creature* creature, Unit* killer) override
    //{
    //    // call parent so challenge updates (runs affixes)
    //    InstanceScript::CreatureDiesForScript(creature, killer);
    //
    //    if (creature->ToTempSummon())
    //        return;
    //
    //    switch (creature->GetEntry())
    //    {
    //        case BossA:
    //          //  DoUpdateCriteria(CriteriaType::DefeatDungeonEncounter, creature->GetEntry());
    //            break;
    //        case BossB:
    //         //   DoUpdateCriteria(CriteriaType::DefeatDungeonEncounter, creature->GetEntry());
    //            break;
    //        case BossC:
    //         //   DoUpdateCriteria(CriteriaType::DefeatDungeonEncounter, creature->GetEntry());
    //            break;
    //        default:
    //            break;
    //    }
    //}
};

// 701000 - npc_mister_doctor_701000
struct npc_mister_doctor_701000 : public BossAI
{
public:
    npc_mister_doctor_701000(Creature* creature) : BossAI(creature, BOSS_MISTER_DOCTOR) { }

    enum eSpell
    {
        BeconSlime = 327604,
        PlagueBolt = 320120,
        BroodPlague = 341959,
        Barrel = 340441,
        Blasphemy = 361999,
        WateryAsphyxiate = 147834,
        PlagueChannel = 327487,
    };

    void JustSummoned(Creature* creature) override
    {
        summons.Summon(creature);

        ++ActiveSlimes;
        creature->SetReactState(REACT_PASSIVE);
        creature->GetMotionMaster()->MovePoint(1, *me, MOVE_WALK_MODE)->callbackFunc = [creature]()
        {
            creature->DespawnOrUnsummon();
        };
    }

    void EnterEvadeMode(EvadeReason /*why*/) override
    {
        _EnterEvadeMode();
        if (instance)
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
        events.Reset();
        _DespawnAtEvade(3s);
    }

    void SummonedCreatureDies(Creature* creature, Unit* /*killer*/) override
    {
        if (Slimes)
        {
            Slimes--;
            if (Slimes == 0)
            {
                //didPhase2 = false;
                phasing = false;
                me->KillSelf();
            }
        }
        if (ActiveSlimes)
        {
            ActiveSlimes--;

            if (ActiveSlimes == 0)
            {
                //didPhase2 = false;
                phasing = false;
                me->SetHealth(me->CountPctFromMaxHealth(7 * Slimes + 10));
                me->RemoveUnitFlag(UnitFlags::UNIT_FLAG_UNINTERACTIBLE);
                me->RemoveUnitFlag(UnitFlags::UNIT_FLAG_NON_ATTACKABLE_2);
                me->RemoveUnitFlag2(UnitFlags2::UNIT_FLAG2_HIDE_BODY);
                me->SetReactState(REACT_AGGRESSIVE);
                me->ResumeMovement();
                Talk(4);
            }
        }
    }

    void SummonedCreatureDespawn(Creature* creature) override
    {
        if (!creature->isDead())
        {
            if (ActiveSlimes)
            {
                ActiveSlimes--;

                if (ActiveSlimes == 0)
                {
                    //didPhase2 = false;
                    phasing = false;
                    me->SetHealth(me->CountPctFromMaxHealth(7 * Slimes + 10));
                    me->RemoveUnitFlag(UnitFlags::UNIT_FLAG_UNINTERACTIBLE);
                    me->RemoveUnitFlag(UnitFlags::UNIT_FLAG_NON_ATTACKABLE_2);
                    me->RemoveUnitFlag2(UnitFlags2::UNIT_FLAG2_HIDE_BODY);
                    me->SetReactState(REACT_AGGRESSIVE);
                    me->ResumeMovement();
                    Talk(4);
                }
            }
        }
    }

    void InitializeAI() override
    {
        ApplyAllImmunities(true);
        me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_INTERRUPT, false);
    }

    void Reset() override
    {
        BossAI::Reset();
        summons.DespawnAll();
        Slimes = 10;
        phasing = false;
        didPhase = false;
        didPhase2 = false;
        me->SetReactState(REACT_AGGRESSIVE);
        me->DeMorph();
        me->SetObjectScale(2.0f);
        me->RemoveUnitFlag(UnitFlags::UNIT_FLAG_UNINTERACTIBLE);
        me->RemoveUnitFlag(UnitFlags::UNIT_FLAG_NON_ATTACKABLE_2);
        me->RemoveUnitFlag2(UnitFlags2::UNIT_FLAG2_HIDE_BODY);
        ActiveSlimes = 0;
    }

    void JustDied(Unit* who) override
    {
        scheduler.CancelAll();
        BossAI::JustDied(who);
        Talk(5);

        if (instance)
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);

        if (instance)
            if (auto scenario = instance->instance->GetInstanceScenario())
                if (auto criteriaTree = sCriteriaMgr->GetCriteriaTree(300003))
                    scenario->CompletedCriteriaTree(criteriaTree, nullptr);
    }

    void JustEngagedWith(Unit* who) override
    {
        if (instance)
            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
        BossAI::JustEngagedWith(who);
        events.Reset();
        events.ScheduleEvent(1, 5s);
        events.ScheduleEvent(2, 10s, 20s);
    }

    void UpdateAI(uint32 diff) override
    {
        scheduler.Update(diff);

        if (!UpdateVictim())
            return;

        if (phasing)
            return;

        events.Update(diff);

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        if (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
                case 1:
                    DoCastVictim(BroodPlague);
                    events.Repeat(35s);
                    break;
                case 2:
                    DoCastAOE(Barrel);
                    events.Repeat(15s, 25s);
                    break;
                case 3:
                    DoCastAOE(Blasphemy);
                    events.Repeat(15s, 30s);
                    break;
                case 4:
                    DoCastVictim(WateryAsphyxiate);
                    events.Repeat(30s);
                    break;
            }
        }

        if (!me->HasUnitState(UNIT_STATE_CASTING))
            DoCastVictim(PlagueBolt);
        DoMeleeAttackIfReady();
    }

    bool didIntro = false;
    void OnUnitRelocation(Unit* who) override
    {
        if (!didIntro && who->IsPlayer() && who->GetDistance2d(me) <= 30.0f && (!who->movespline || who->movespline->Finalized()) && me->IsValidAttackTarget(who))
        {
            didIntro = true;
            Talk(0);
            AttackStart(who);
        }
    }

    bool didPhase = false;
    bool didPhase2 = false;
    bool phasing = false;
    void DamageTaken(Unit* attacker, uint32& damage, DamageEffectType damageType, SpellInfo const* spell) override
    {
        if (phasing)
        {
            damage = 0;
            return;
        }

        if (!didPhase && me->HealthBelowPctDamaged(61, damage))
        {
            didPhase = true;
            Talk(1);
            me->SetReactState(REACT_PASSIVE);
            me->PauseMovement();
            phasing = true;
            damage = 0;
            me->InterruptSpell(CurrentSpellTypes::CURRENT_GENERIC_SPELL);
            me->CastStop();
            DoCastVictim(PlagueChannel);
            scheduler.Schedule(6s, [this](TaskContext context)
            {
                me->InterruptSpell(CurrentSpellTypes::CURRENT_CHANNELED_SPELL);
                me->ResumeMovement();
                phasing = false;
                me->SetReactState(REACT_AGGRESSIVE);
                Talk(2);
                me->SetDisplayId(96240, 4.0f);
                events.ScheduleEvent(3, 10s, 20s);
                events.ScheduleEvent(4, 10s, 20s);
            });
            return;
        }

        // - At 5 % health, ONLY if he morphed(just in case he bugs outand doesnt drink or players find a way to interrupt), he basically does Zac's passive from League:
        //     - First he says : Creature_text entry : 701000 groupID 3, then an effect plays(I did not have time to find an effect before server crash, sorry - I'm typing this portion up as server is closed)
        //     - he dissappears and turns into about 5 or 10 Mister Slimes(ID: 701001)
        //     - You pick what seems like a better number here, should not be random as each slime accounts for a percentage of his full health
        //     - E.G if 5 slimes, they each equal 10 % of total health, if they all reform he goes back to 50 % health.If 10 slimes, they each equal 5 %, all reforming back to 50 % of his full health
        //     - When he turns into the slimes, they all separate around a circle, walking very slowly back to the center of where he was before turning to slimes, then player has to kill them all to finish the boss
        //     - If players do not kill all of them, he reforms when they hit the center.Each slime left equals a percentage of his health(see above)
        //     - When / if he is able to reform, he will say : Creature_text entry : 701000 groupID 4
        //     - This process repeats whenever he hits 5 % health
        if (!didPhase2 && me->HealthBelowPctDamaged(5, damage) && !phasing)
        {
            if (Slimes > 0)
            {
                didPhase2 = true;
                phasing = true;
                Talk(3);
                me->SetUnitFlag(UnitFlags::UNIT_FLAG_UNINTERACTIBLE);
                me->SetUnitFlag(UnitFlags::UNIT_FLAG_NON_ATTACKABLE_2);
                me->SetUnitFlag2(UnitFlags2::UNIT_FLAG2_HIDE_BODY);
                me->SetReactState(REACT_PASSIVE);
                me->PauseMovement();
                me->CastStop();
                events.DelayEvents(5s);
                damage = 0;
                ActiveSlimes = 0;

                float orientation = 0.0f;

                int brokenSlimes = 0;

                for (int i = 0; i < Slimes; ++i)
                {
                    if (DoCast(me, BeconSlime, true) != SPELL_CAST_OK)
                        ++brokenSlimes;

                    orientation += 0.628;
                    me->SetFacingTo(orientation);
                }

                Slimes -= brokenSlimes;
                if (Slimes < 0)
                    Slimes = 0;
            }
        }
    }

    int32 Slimes = 10;
    uint32 ActiveSlimes = 0;
};

// ID - 327603 Beckon Slime
class spell_beckon_slime_underrot : public SpellScript
{
    PrepareSpellScript(spell_beckon_slime_underrot);

    void HandleSummon(SpellEffIndex effIndex)
    {
        PreventHitDefaultEffect(effIndex);
        uint32 entry = 701001;

        if (!GetCaster())
            return;

        if (GetExplTargetDest())
        {
            if (auto slime = GetCaster()->SummonCreature(entry, *GetExplTargetDest(), TEMPSUMMON_MANUAL_DESPAWN))
            {
                slime->SetMaxHealth(GetCaster()->CountPctFromMaxHealth(5));
                slime->SetFullHealth();
            }
         //   GetCaster()->Say((*GetExplTargetDest()).ToString(), LANG_UNIVERSAL, nullptr);
        }


        //if (auto creature = GetCaster()->ToCreature())
        //    if (auto ai = creature->AI())
    }

    void Register() override
    {
        OnEffectHit += SpellEffectFn(spell_beckon_slime_underrot::HandleSummon, EFFECT_0, SPELL_EFFECT_SUMMON);
    }
};

// 701001 - npc_mister_slime_701001
struct npc_mister_slime_701001 : public ScriptedAI
{
public:
    npc_mister_slime_701001(Creature* creature) : ScriptedAI(creature) { }

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

// 701002 - npc_plague_tentacle_701002
struct npc_plague_tentacle_701002 : public ScriptedAI
{
public:
    npc_plague_tentacle_701002(Creature* creature) : ScriptedAI(creature) { }

    void InitializeAI() override
    {
        me->SetReactState(REACT_PASSIVE);
        me->SetUnitFlag(UnitFlags::UNIT_FLAG_NON_ATTACKABLE);
        SetCombatMovement(false);
    }
};

// 701003 - npc_ansid_the_mechanic_701003
struct npc_ansid_the_mechanic_701003 : public BossAI
{
public:
    npc_ansid_the_mechanic_701003(Creature* creature) : BossAI(creature, BOSS_ANDSID_THE_MECHANIC)
    {
        ApplyAllImmunities(true);
    }

    enum Ansid
    {
        EventGroundSmash = 1,
        EventBloodthirstyLeap,
        EventThrowVial,

        GroundSmash = 341441,
        BloodthirstyLeap = 225962,
        ThrowVial = 211994,
        FeedinfFrenzy = 297896, // aura
    };

    void Reset() override
    {
        DoCastSelf(FeedinfFrenzy);
    }

    void JustEngagedWith(Unit* who) override
    {
        BossAI::JustEngagedWith(who);
        if (instance)
            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
        DoCastSelf(FeedinfFrenzy);

        events.ScheduleEvent(EventGroundSmash, 1s, 10s);
        events.ScheduleEvent(EventBloodthirstyLeap, 1s, 10s);
        events.ScheduleEvent(EventThrowVial, 1s, 10s);

        Talk(0);
    }

    void JustDied(Unit* who) override
    {
        BossAI::JustDied(who);
        if (instance)
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
    }

    void EnterEvadeMode(EvadeReason /*why*/) override
    {
        _EnterEvadeMode();
        if (instance)
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
        events.Reset();
        _DespawnAtEvade(3s);
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
                case EventGroundSmash:
                    DoCastVictim(GroundSmash);
                    events.Repeat(10s, 20s);
                    break;
                case EventBloodthirstyLeap:
                    DoCastVictim(BloodthirstyLeap);
                    events.Repeat(10s, 20s);
                    break;
                case EventThrowVial:
                    DoCastVictim(ThrowVial);
                    events.Repeat(10s, 20s);
                    break;
            }

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;
        }
        DoMeleeAttackIfReady();
    }
};

// 701004 - npc_ansid_s_helper_701004
struct npc_ansid_s_helper_701004 : public ScriptedAI
{
public:
    npc_ansid_s_helper_701004(Creature* creature) : ScriptedAI(creature) { }

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

// 701005 - npc_sporecaller_zancha_701005
struct npc_sporecaller_zancha_701005 : public BossAI
{
public:
    npc_sporecaller_zancha_701005(Creature* creature) : BossAI(creature, BOSS_SPORECALLER_ZANCHA)
    {
        ApplyAllImmunities(true);
    }

    enum eSpells
    {
        NecroticUpheaval = 333216,
        DinnerTime = 99693,
        CrashingCharge = 368060,
        ImminentDestruction = 360876,
    };

    void Reset() override
    {
        BossAI::Reset();
    }

    void EnterEvadeMode(EvadeReason /*why*/) override
    {
        _EnterEvadeMode();
        if (instance)
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
        events.Reset();
        _DespawnAtEvade(3s);
    }

    void JustEngagedWith(Unit* who) override
    {
        if (instance)
            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
        BossAI::JustEngagedWith(who);
        events.Reset();
        Talk(1);
        events.ScheduleEvent(1, 10s, 20s);
        events.ScheduleEvent(2, 10s, 20s);
        events.ScheduleEvent(3, 10s, 20s);
        events.ScheduleEvent(4, 10s, 20s);
    }

    void JustDied(Unit* killer) override
    {
        BossAI::JustDied(killer);
        if (instance)
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
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
                    DoCastVictim(NecroticUpheaval);
                    events.Repeat(10s, 20s);
                    break;
                case 2:
                    DoCastVictim(DinnerTime);
                    events.Repeat(30s, 40s);
                    break;
                case 3:
                    DoCastVictim(CrashingCharge);
                    events.Repeat(50s);
                    break;
                case 4:
                    DoCastVictim(ImminentDestruction);
                    events.Repeat(10s, 20s);
                    break;
            }
        }
        DoMeleeAttackIfReady();
    }

    bool didIntro = false;
    void OnUnitRelocation(Unit* who) override
    {
        if (!didIntro && who->IsPlayer() && who->GetDistance2d(me) <= 40.0f)
        {
            didIntro = true;
            Talk(0);
        }
    }
};

// 701006 - npc_plague_witch_701006
struct npc_plague_witch_701006 : public ScriptedAI
{
public:
    npc_plague_witch_701006(Creature* creature) : ScriptedAI(creature) { }

    void InitializeAI() override
    {
        /// TODO: Fill this function
    }

    void Reset() override
    {
        /// TODO: Fill this function
    }

    void JustEngagedWith(Unit* /*who*/) override
    {
        scheduler.CancelAll();
        me->RemoveAurasDueToSpell(SpellDummyChannel);
    }

    void UpdateAI(uint32 diff) override
    {
        scheduler.Update(diff);

        if (!UpdateVictim())
        {
            if (!me->isDead() && !me->IsEngaged() && !me->GetCurrentSpell(CurrentSpellTypes::CURRENT_CHANNELED_SPELL))
            {
                if (auto bloodBoil = me->FindNearestCreature(NpcBloodBall, 6.0f))
                    DoCast(bloodBoil, SpellDummyChannel, true);
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

        if (!me->HasUnitState(UNIT_STATE_CASTING))
            DoCastVictim(326829); // Wicked Bolt

        DoMeleeAttackIfReady();
    }

    bool didTalk = false;

    void OnUnitRelocation(Unit* who) override
    {
        if (who->IsPlayer() && !didTalk && me->GetSpawnId() == 1053659 && who->GetDistance2d(me) <= 35.0f)
        {
            didTalk = true;
            Talk(0);
            scheduler.Schedule(5s, [this](TaskContext context)
            {
                if (auto secondCreature = me->FindNearestCreatureBySpawnId(1053658, 30.0f))
                {
                    if (auto ai = secondCreature->AI())
                        ai->Talk(1);
                }
                
                scheduler.Schedule(5s, [this](TaskContext context)
                {
                    Talk(2);
                });
            });
        }
    }


    TaskScheduler scheduler;
    EventMap events;
};

// 701007 - npc_timmothy_701007
struct npc_timmothy_701007 : public ScriptedAI
{
public:
    npc_timmothy_701007(Creature* creature) : ScriptedAI(creature) { }

    void InitializeAI() override
    {
        me->SetUnitFlag(UnitFlags::UNIT_FLAG_UNINTERACTIBLE);
        me->SetStandState(UnitStandStateType::UNIT_STAND_STATE_SLEEP);
    }
};

// 701008 - npc_fetid_maggot_701008
struct npc_fetid_maggot_701008 : public ScriptedAI
{
public:
    npc_fetid_maggot_701008(Creature* creature) : ScriptedAI(creature) { }

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

        if (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
                case 1:
                    DoCastVictim(265540);
                    events.Repeat(20s, 30s);
                    break;
            }
        }
        DoMeleeAttackIfReady();
    }


    TaskScheduler scheduler;
    EventMap events;
};

// 701009 - npc_spore_covered_scavenger_701009
struct npc_spore_covered_scavenger_701009 : public ScriptedAI
{
public:
    npc_spore_covered_scavenger_701009(Creature* creature) : ScriptedAI(creature) { }

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

// 701010 - npc_rockjaw_fungus_flinger_701010
struct npc_rockjaw_fungus_flinger_701010 : public ScriptedAI
{
public:
    npc_rockjaw_fungus_flinger_701010(Creature* creature) : ScriptedAI(creature) { }

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

// 701011 - npc_plague_covered_fungo_701011
struct npc_plague_covered_fungo_701011 : public ScriptedAI
{
public:
    npc_plague_covered_fungo_701011(Creature* creature) : ScriptedAI(creature) { }

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

// 701012 - npc_gloomshade_fungi_701012
struct npc_gloomshade_fungi_701012 : public ScriptedAI
{
public:
    npc_gloomshade_fungi_701012(Creature* creature) : ScriptedAI(creature) { }

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
                    DoCastVictim(32065); // Fungal decay
                    events.Repeat(10s, 20s);
                    break;
                case 2:
                    DoCastAOE(15550); // Trample
                    events.Repeat(10s, 20s);
                    break;
            }
        }
        DoMeleeAttackIfReady();
    }


    TaskScheduler scheduler;
    EventMap events;
};

// 701013 - npc_blood_ball_701013
struct npc_blood_ball_701013 : public ScriptedAI
{
public:
    npc_blood_ball_701013(Creature* creature) : ScriptedAI(creature) { }

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

// 701014 - npc_damaged_defense_bot_701014
struct npc_damaged_defense_bot_701014 : public ScriptedAI
{
public:
    npc_damaged_defense_bot_701014(Creature* creature) : ScriptedAI(creature) { }

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

// 701015 - npc_defense_bot_701015
struct npc_defense_bot_701015 : public ScriptedAI
{
public:
    npc_defense_bot_701015(Creature* creature) : ScriptedAI(creature) { }

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

// 701016 - npc_dusty_sporewing_701016
struct npc_dusty_sporewing_701016 : public ScriptedAI
{
public:
    npc_dusty_sporewing_701016(Creature* creature) : ScriptedAI(creature) { }

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

// 701017 - npc_lord_fungo_701017
struct npc_lord_fungo_701017 : public ScriptedAI
{
public:
    npc_lord_fungo_701017(Creature* creature) : ScriptedAI(creature) { }

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
        me->CallForHelp(30.0f);
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

// 701018 - npc_fungo_warrior_701018
struct npc_fungo_warrior_701018 : public ScriptedAI
{
public:
    npc_fungo_warrior_701018(Creature* creature) : ScriptedAI(creature) { }

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

// 701019 - npc_sporeling_701019
struct npc_sporeling_701019 : public ScriptedAI
{
public:
    npc_sporeling_701019(Creature* creature) : ScriptedAI(creature) { }

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

// 701020 - npc_plague_doctor_701020
struct npc_plague_doctor_701020 : public ScriptedAI
{
public:
    npc_plague_doctor_701020(Creature* creature) : ScriptedAI(creature) { }

    bool OnGossipHello(Player* player) override
    {
        ClearGossipMenuFor(player);
        player->PrepareQuestMenu(me->GetGUID());

        if (auto instance = me->GetInstanceScript())
        {
            if (instance->GetBossState(BOSS_MISTER_DOCTOR) == EncounterState::DONE)
            {
                AddGossipItemFor(player, GossipOptionIcon::None, "Teleport me back to the entrance", 0, 0, [this, player](std::string /*callback*/)
                {
                    player->TeleportTo(WorldLocation(1841, { 625.044f, 1253.41f, 99.8346f, 6.27532f }));
                });

                SendGossipMenuFor(player, 7010200, me);
                return true;
            }
        }

        SendGossipMenuFor(player, me->GetEntry(), me);
        return true;
    }
};

const Position player_gateway_positions[] =
{
    { 1102.52f, 1333.68f, 5.84308f, 0.865922f },
    { 1114.7883f, 1350.4313f, 11.04261f },
    { 1122.7559f, 1363.1124f, 12.79088f },
    { 1154.0913f, 1411.2205f, -11.0111f },
    { 1174.4086f, 1443.4255f, -27.0167f },
    { 1199.6218f, 1481.5396f, -42.7930f },
    { 1199.6218f, 1481.5396f, -100.145f },
    { 1199.41f, 1481.78f, -181.708f, 2.9505f },
};

// 253773
struct spell_underrot_gateway : public AuraScript
{
    PrepareAuraScript(spell_underrot_gateway);

    void HandleOnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* caster = GetCaster())
        {
            caster->GetMotionMaster()->MoveSmoothPath(1, player_gateway_positions, 8, false, true, 35.0f)->callbackFunc = [caster]()
            {
                caster->RemoveAurasDueToSpell(253773); // Gateway
            };
        }
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_underrot_gateway::HandleOnApply, EFFECT_0, SPELL_AURA_FLY, AURA_EFFECT_HANDLE_REAL);
    }
};
// 800055 - npc_scrappie_800055
struct npc_scrappie_800055 : public ScriptedAI
{
public:
    npc_scrappie_800055(Creature* creature) : ScriptedAI(creature) { }

    void InitializeAI() override
    {
        me->AddAura(343980, me); // Frozen
        me->AddAura(327490, me); // Slime
        if (!me->IsSummon())
        {
            me->RemoveNpcFlag(NPCFlags::UNIT_NPC_FLAG_SPELLCLICK);
        }
    }

    bool OnGossipHello(Player* player)
    {
        //player->KilledMonsterCredit(me->GetEntry(), me->GetGUID());

        auto status = player->GetQuestStatus(800055);
        if (status == QUEST_STATUS_INCOMPLETE)
        {
          //  player->KilledMonsterCredit(me->GetEntry(), me->GetGUID());
            player->PlayerTalkClass->SendQuestGiverQuestDetails(sObjectMgr->GetQuestTemplate(800055), me->GetGUID(), false, false);
        }
        else if (status == QUEST_STATUS_NONE)
        {
            player->AddQuestAndCheckCompletion(sObjectMgr->GetQuestTemplate(800055), me);
          //  player->KilledMonsterCredit(me->GetEntry(), me->GetGUID());
            player->PlayerTalkClass->SendQuestGiverQuestDetails(sObjectMgr->GetQuestTemplate(800055), me->GetGUID(), false, false);
        }
        else if (status == QUEST_STATUS_COMPLETE)
        {
            player->PlayerTalkClass->SendQuestGiverOfferReward(sObjectMgr->GetQuestTemplate(800055), me->GetGUID(), false);
        }
        return true;
    }

    void OnQuestAccept(Player* player, Quest const* quest) override
    {
        //player->KilledMonsterCredit(me->GetEntry(), me->GetGUID());

        players.insert(player->GetGUID());
        if (auto clone = me->SummonPersonalClone(*me, TEMPSUMMON_MANUAL_DESPAWN, 0s, 0, 0, player))
        {
            clone->SetNpcFlag(NPCFlags::UNIT_NPC_FLAG_SPELLCLICK);
            clone->RemoveNpcFlag(NPCFlags::UNIT_NPC_FLAG_QUESTGIVER);
            if (auto ai = clone->AI())
                ai->Talk(0, player);
        }
    }

    bool CanSeeOrDetect(WorldObject const* who) const override
    {
        if (who->IsPlayer() && !me->isAnySummons())
        {
            auto player = who->ToPlayer();
            if (player->IsGameMaster())
                return true;
            if (player->GetQuestStatus(800055) == QUEST_STATUS_REWARDED)
                return false;
        }

        return true;
    }

    // handled by spellscript
    void OnSpellClick(Unit* clicker, bool spellClickHandled) override
    {
    }

    void DoAction(int32 actionId) override
    {
        if (actionId == 1)
        {
            me->RemoveAllAuras();
            me->SetNpcFlag(NPCFlags::UNIT_NPC_FLAG_QUESTGIVER);
            me->RemoveNpcFlag(NPCFlags::UNIT_NPC_FLAG_SPELLCLICK);
           // me->DespawnOrUnsummon();
        }
    }

    uint32 checkTimer = 0;

    void UpdateAI(uint32 diff)
    {
        if (me->isAnySummons())
            return;

        checkTimer += diff;

        if (checkTimer >= 250)
        {
            checkTimer = 0;
            std::list<Unit*> unitsInRange;
            me->GetFriendlyUnitListInRange(unitsInRange, 15.0f);
            for (auto who : unitsInRange)
            {
                if (who->IsPlayer() && who->GetDistance2d(me) <= 15.0f && !players.count(who->GetGUID()) && CanSeeOrDetect(who))
                {
                    players.insert(who->GetGUID());
                    auto status = who->ToPlayer()->GetQuestStatus(800055);
                    if (status == QUEST_STATUS_INCOMPLETE)
                    {
                        if (auto clone = me->SummonPersonalClone(*me, TEMPSUMMON_MANUAL_DESPAWN, 0s, 0, 0, who->ToPlayer()))
                        {
                            clone->RemoveNpcFlag(NPCFlags::UNIT_NPC_FLAG_QUESTGIVER);
                            if (auto ai = clone->AI())
                                ai->Talk(0, who->ToPlayer());
                        }
                    }
                }
            }
        }
    }

    GuidSet players;

    void MoveInLineOfSight(Unit* who) override
    {
    }
};

/// ID - 361487 Cleansing
class spell_361487_cleansing : public SpellScript
{
    PrepareSpellScript(spell_361487_cleansing);

    void HandleDummy(SpellEffIndex /*effIndex*/)
    {
        Creature* target = GetHitCreature();
        if (!target || !target->IsAIEnabled() || target->GetEntry() != 800055)
            return;

        if (auto caster = GetCaster())
            if (auto player = caster->ToPlayer())
                player->KilledMonsterCredit(800055, target->GetGUID());
        target->AI()->DoAction(1);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_361487_cleansing::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

struct quest_scrappie : public QuestAI
{
public:
    quest_scrappie(Quest const* quest, Player* player) : QuestAI(quest, player) { }

    void OnQuestReward(Object* questGiver) override
    {
        if (questGiver && questGiver->IsCreature())
        {
            auto creature = questGiver->ToCreature();
            if (creature->ToTempSummon())
            {
                creature->CastSpell(creature, 367044, true);
                creature->DespawnOrUnsummon(700ms);
            }
            creature->UpdateObjectVisibility();
        }
    }
};
// 800061 - npc_gold_token_800061
struct npc_gold_token_800061 : public ScriptedAI
{
public:
    npc_gold_token_800061(Creature* creature) : ScriptedAI(creature) { }

    bool OnGossipHello(Player* player) override
    {
        CloseGossipMenuFor(player);
        player->KilledMonsterCredit(me->GetEntry(), me->GetGUID());
        me->UpdateObjectVisibility();
        return true;
    }

    bool CanSeeOrDetect(WorldObject const* who) const override
    {
        if (who->IsPlayer())
        {
            auto player = who->ToPlayer();
            auto questStatus = player->GetQuestStatus(700101);
            if (questStatus == QUEST_STATUS_INCOMPLETE)
                return true;
        }

        return false;
    }
};



void AddSC_TheUnderrot()
{
    RegisterInstanceScript(instance_the_underrot, 1841);

    RegisterCreatureAI(npc_mister_doctor_701000);
    RegisterCreatureAI(npc_mister_slime_701001);
    RegisterCreatureAI(npc_plague_tentacle_701002);
    RegisterCreatureAI(npc_ansid_the_mechanic_701003);
    RegisterCreatureAI(npc_ansid_s_helper_701004);
    RegisterCreatureAI(npc_sporecaller_zancha_701005);
    RegisterCreatureAI(npc_plague_witch_701006);
    RegisterCreatureAI(npc_timmothy_701007);
    RegisterCreatureAI(npc_fetid_maggot_701008);
    RegisterCreatureAI(npc_spore_covered_scavenger_701009);
    RegisterCreatureAI(npc_rockjaw_fungus_flinger_701010);
    RegisterCreatureAI(npc_plague_covered_fungo_701011);
    RegisterCreatureAI(npc_gloomshade_fungi_701012);
    RegisterCreatureAI(npc_blood_ball_701013);
    RegisterCreatureAI(npc_damaged_defense_bot_701014);
    RegisterCreatureAI(npc_defense_bot_701015);
    RegisterCreatureAI(npc_dusty_sporewing_701016);
    RegisterCreatureAI(npc_lord_fungo_701017);
    RegisterCreatureAI(npc_fungo_warrior_701018);
    RegisterCreatureAI(npc_sporeling_701019);
    RegisterCreatureAI(npc_plague_doctor_701020);
    RegisterCreatureAI(npc_scrappie_800055);
    RegisterCreatureAI(npc_gold_token_800061);

    RegisterQuestAI(quest_scrappie);

    RegisterSpellScript(spell_beckon_slime_underrot);
    RegisterSpellScript(spell_underrot_gateway);
    RegisterSpellScript(spell_361487_cleansing);
}
