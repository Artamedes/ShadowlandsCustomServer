#include "ScriptMgr.h"
#include "../CustomInstanceScript.h"
#include "Creature.h"
#include "ScriptedCreature.h"
#include "Player.h"
#include "MoveSpline.h"
#include "MoveSplineInit.h"
#include "TemporarySummon.h"
#include "ObjectAccessor.h"
#include "GenericMovementGenerator.h"
#include "InstanceScenario.h"
#include "ReputationMgr.h"

enum DreadscarRift
{
    BossBellatrix,
    BossDolgonir,
    BossKuryash,
    BossGoroth,

    NecoWarriorAdd = 703018,

    NpcPortalToGoroth = 703028,
    NpcFelConduit = 703027,
};

struct instance_dreadscarrift : public CustomInstanceScript
{
public:
    instance_dreadscarrift(InstanceMap* map) : CustomInstanceScript(map)
    {
        ChestSpawn = { 3424.07f, 1515.78f, 436.92f, 1.12574f };
        Quad = { -0.0f, -0.0f, -0.533614f, -0.845728f };
        EnemyForcesCriteriaTreeId = 300101;
    }

    void SummonChallengeGameObject(bool door) override
    {
        if (door)
        {
            if (auto go = instance->SummonGameObject(MYTHIC_DOOR_5, { 3085.94f, 822.591f, 243.666f, 1.38753f }, { -0.0f, -0.0f, -0.639438f, -0.768843f }, 0))
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
            if (auto tree2 = sCriteriaMgr->GetCriteriaTree(300100))
                instanceScenario->IsCompletedCriteriaTree(tree2, nullptr);
        }
    }

    bool SetBossState(uint32 bossId, EncounterState state, bool force = false) override
    {
        bool val = InstanceScript::SetBossState(bossId, state);

        if (bossId == BossDolgonir)
        {
            if (state == EncounterState::DONE)
            {
                instance->SummonCreature(NpcPortalToGoroth, { 3097.91f, 1095.91f, 284.311f, 0.847346f });
            }
        }

        return val;
    }

    void CreatureDiesForScript(Creature* creature, Unit* killer) override
    {
        CustomInstanceScript::CreatureDiesForScript(creature, killer);

        auto facEntry = sFactionStore.LookupEntry(LegionAssaultForceRep);
        if (!facEntry)
            return;

        auto shadowMilitia = sFactionStore.LookupEntry(ShadowMilitiaRep);
        if (!shadowMilitia)
            return;

        bool isBoss = creature->IsDungeonBoss();
        uint32 repAmount = isBoss ? 500 : 25;

        instance->DoOnPlayers([facEntry, repAmount, shadowMilitia, creature](Player* player)
        {
            player->GetReputationMgr().ModifyReputation(facEntry, repAmount);
            player->GetReputationMgr().ModifyReputation(shadowMilitia, repAmount);

            if (creature->GetFaction() != 35)
                if (creature->IsDungeonBoss() || roll_chance_i(50))
                    player->ModifyCurrency(InfernalCore, creature->IsDungeonBoss() ? 100 : urand(1, 3));
        });
    }
};
// 703000 - npc_adageor_703000
struct npc_adageor_703000 : public ScriptedAI
{
public:
    npc_adageor_703000(Creature* creature) : ScriptedAI(creature) { }
};

const Position FelConduitPos = { 3452.24f, 1554.11f, 436.707f, 3.18628f };

// 703001 - npc_goroth_703001
struct npc_goroth_703001 : public BossAI
{
public:
    npc_goroth_703001(Creature* creature) : BossAI(creature, BossGoroth)
    {
        ApplyAllImmunities(true);
    }

    enum Goroth
    {
        Berserk = 369884,

        EventFelBlast = 1,
        EventFelflameBolt,
        EventRoatingFlames,

        SpellFelBlast = 240381,
        FelFlameBolt = 361170,
        RoaringFlames = 358749,
        LumberingRoar = 356169, // aggro
    };

    void Reset() override
    {
        me->AddAura(Berserk, me);
        DoSummon(NpcFelConduit, FelConduitPos, 0s, TEMPSUMMON_DEAD_DESPAWN);
    }

    bool conduitUp = true;

    void JustEngagedWith(Unit* who) override
    {
        BossAI::JustEngagedWith(who);
        me->AddAura(Berserk, me);
        Talk(1);

        DoCastAOE(LumberingRoar);
        events.ScheduleEvent(EventFelBlast, 5s, 10s);
        events.ScheduleEvent(EventFelflameBolt, 5s, 10s);
        events.ScheduleEvent(EventRoatingFlames, 20s);
    }
    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        events.Update(diff);

        if (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EventFelBlast:
                    DoCastVictim(SpellFelBlast);
                    events.Repeat(10s, 15s);
                    break;
                case EventFelflameBolt:
                    DoCastVictim(FelFlameBolt);
                    events.Repeat(10s, 15s);
                    break;
                case EventRoatingFlames:
                    DoCastAOE(RoaringFlames);
                    events.Repeat(20s);
                    break;
            }
        }
        DoMeleeAttackIfReady();
    }

    void SummonedCreatureDies(Creature* creature, Unit* killer) override
    {
        BossAI::SummonedCreatureDies(creature, killer);

        if (creature->GetEntry() == NpcFelConduit)
        {
            conduitUp = false;
            me->RemoveAurasDueToSpell(Berserk);
        }
    }

    bool didText = false;

    void DamageTaken(Unit* attacker, uint32& damage, DamageEffectType /*damageType*/, SpellInfo const* /*spellInfo = nullptr*/) override
    {
        if (damage >= me->GetHealth() && conduitUp)
        {
            damage = 0;

            me->SetHealth(me->CountPctFromMaxHealth(20));

            if (!didText)
            {
                didText = true;
                Talk(2);
            }
        }
    }

    bool didIntro = false;
    void OnUnitRelocation(Unit* who) override
    {
        if (!didIntro && who->IsPlayer() && who->GetDistance2d(me) <= 80.0f && (!who->movespline || who->movespline->Finalized()))
        {
            didIntro = true;
            Talk(0);
        }
    }

    void EnterEvadeMode(EvadeReason why) override
    {
        didText = false;
        conduitUp = true;
        SetCombatMovement(true);
        _DespawnAtEvade(3s);
        scheduler.CancelAll();
        me->SetReactState(REACT_AGGRESSIVE);
        me->GetScheduler().CancelAll();
        summons.DespawnAll();
    }
};

// 703027 - npc_fel_conduit_703027
struct npc_fel_conduit_703027 : public ScriptedAI
{
public:
    npc_fel_conduit_703027(Creature* creature) : ScriptedAI(creature) { }

    void InitializeAI() override
    {
        SetCombatMovement(false);
        me->SetReactState(REACT_PASSIVE);
    }

    void UpdateAI(uint32 diff) override
    {
        if (me->isDead())
            return;

        if (me->GetCurrentSpell(CurrentSpellTypes::CURRENT_CHANNELED_SPELL))
            return;

        if (auto goroth = me->FindNearestCreature(703001, 100.0f))
            DoCast(goroth, 353401); // ID - 353401 Eye of the Jailer Channel
    }
};


// 703007 - npc_harvested_mana_crystal_703007
struct npc_harvested_mana_crystal_703007 : public ScriptedAI
{
public:
    npc_harvested_mana_crystal_703007(Creature* creature) : ScriptedAI(creature) { }

    void InitializeAI() override
    {
        me->SetReactState(REACT_PASSIVE);
        me->SetUnitFlag(UNIT_FLAG_NON_ATTACKABLE);
        SetCombatMovement(false);
    }
};

// 703009 - npc_moz_gar_703009
struct npc_moz_gar_703009 : public ScriptedAI
{
public:
    npc_moz_gar_703009(Creature* creature) : ScriptedAI(creature) { }

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
            }
        }
        DoMeleeAttackIfReady();
    }

    void OnUnitRelocation(Unit* who) override
    {
        /// TODO: Fill this function
    }

    TaskScheduler scheduler;
    EventMap events;
};

// 703011 - npc_arcane_voidwalker_703011
struct npc_arcane_voidwalker_703011 : public ScriptedAI
{
public:
    npc_arcane_voidwalker_703011(Creature* creature) : ScriptedAI(creature) { }

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
            }
        }
        DoMeleeAttackIfReady();
    }

    void OnUnitRelocation(Unit* who) override
    {
        /// TODO: Fill this function
    }

    TaskScheduler scheduler;
    EventMap events;
};

// 703012 - npc_dolgonir_703012
struct npc_dolgonir_703012 : public BossAI
{
public:
    npc_dolgonir_703012(Creature* creature) : BossAI(creature, BossDolgonir)
    {
        ApplyAllImmunities(true);
    }

    enum Dolgonir
    {
        EventEyeBeam = 1,
        EventFelNova,
        EventAnnilation,
        EventImmoAura,
        EventDeathSweep,

        EyeBeam = 264382, // cast victim
        FelNova = 223395,
        Anniliation = 307403,
        ImmolationAura = 360603,
        DeathSweep = 334107,
    };

    void InitializeAI() override
    {
        me->AddAura(ImmolationAura, me);
    }

    void JustEngagedWith(Unit* who) override
    {
        me->AddAura(ImmolationAura, me);
        BossAI::JustEngagedWith(who);
        Talk(1);
        events.ScheduleEvent(EventEyeBeam, 10s);
        events.ScheduleEvent(EventFelNova, 3s);
        events.ScheduleEvent(EventAnnilation, 20s);
        events.ScheduleEvent(EventDeathSweep, 5s);
    }

    void JustDied(Unit* who) override
    {
        BossAI::JustDied(who);
        Talk(2);
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
                case EventEyeBeam:
                    DoCastVictim(EyeBeam);
                    events.Repeat(20s);
                    break;
                case EventFelNova:
                    DoCastVictim(FelNova, true);
                    events.Repeat(5s, 10s);
                    break;
                case EventAnnilation:
                    DoCastVictim(Anniliation);
                    events.Repeat(30s, 40s);
                    break;
                case EventDeathSweep:
                    DoCastVictim(DeathSweep);
                    events.Repeat(5s, 7s);
                    break;

            }

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;
        }

        DoMeleeAttackIfReady();
    }

    bool didIntro = false;

    void OnUnitRelocation(Unit* who) override
    {
        if (!didIntro && who->IsPlayer() && who->GetDistance2d(me) <= 30.0f)
        {
            didIntro = true;
            Talk(0);
        }
    }

    void EnterEvadeMode(EvadeReason why) override
    {
        SetCombatMovement(true);
        _DespawnAtEvade(3s);
        scheduler.CancelAll();
        me->SetReactState(REACT_AGGRESSIVE);
        me->GetScheduler().CancelAll();
    }
};

// 703013 - npc_bellatrix_703013
struct npc_bellatrix_703013 : public BossAI
{
public:
    npc_bellatrix_703013(Creature* creature) : BossAI(creature, BossBellatrix)
    {
        ApplyAllImmunities(true);
    }

    enum Bellatrix
    {
        EventArmyOfDead = 1,
        EventAsphyxiate,
        EventDemonicCrash,

        SpellArmyOfTheDead = 362862, // trigger - 362863 - triggers - 362864
        SpellAsphyxiate = 221562,
        SpellDrainPower = 272445,
        SpellEmpowered = 354757,
        CurseOfWeakness = 315079,
        SpellDemonicCrash = 253089,
    };

    void InitializeAI() override
    {
        BossAI::InitializeAI();
    }

    void Reset() override
    {
        BossAI::Reset();
        summons.DespawnAll();
    }

    void JustEngagedWith(Unit* who) override
    {
        BossAI::JustEngagedWith(who);
        Talk(1);
        events.ScheduleEvent(EventArmyOfDead, 1ms);
        events.ScheduleEvent(EventAsphyxiate, 10s, 15s);
        events.ScheduleEvent(EventDemonicCrash, 10s, 15s);
    }

    bool setMovement = false;

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        events.Update(diff);

        if (me->IsEngaged() && !me->HasUnitState(UNIT_STATE_CASTING))
        {
            if (setMovement)
            {
                setMovement = false;
                SetCombatMovement(true);
                me->AttackStop();
                if (me->GetVictim())
                    AttackStart(me->GetVictim());
                return;
            }
        }

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        while (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EventArmyOfDead:
                    DoCast(SpellArmyOfTheDead);
                    events.Repeat(60s);
                    return;
                case EventAsphyxiate:
                    if (auto target = SelectTarget(SelectTargetMethod::Random, 0, 15.0f, true, false))
                    {
                        Talk(2);
                        DoCast(target, SpellAsphyxiate);
                        events.Repeat(20s);
                    }
                    else
                        events.Repeat(2s);
                    break;
                case EventDemonicCrash:
                    DoCastVictim(SpellDemonicCrash);
                    events.Repeat(15s);
                    break;
            }
            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;
        }

        DoMeleeAttackIfReady();
    }

    void ExecuteEvent(uint32 eventId) override
    {
    }

    bool didIntro = false;

    void MoveInLineOfSight(Unit* who) override
    {
        BossAI::MoveInLineOfSight(who);
        if (!didIntro && who->IsPlayer() && who->GetDistance2d(me) <= 50.0f)
        {
            didIntro = true;
            Talk(0);
        }
    }

    void EnterEvadeMode(EvadeReason why) override
    {
        SetCombatMovement(true);
        _DespawnAtEvade(3s);
        scheduler.CancelAll();
        me->SetReactState(REACT_AGGRESSIVE);
        me->GetScheduler().CancelAll();
        phased = false;
        phasing = false;
    }

    bool phased = false;
    bool phasing = false;

    void DamageTaken(Unit* attacker, uint32& damage, DamageEffectType /*damageType*/, SpellInfo const* /*spellInfo = nullptr*/) override
    {
        if (phasing)
        {
            if (attacker)
            {
                if (attacker->GetTarget() == me->GetGUID())
                    attacker->AttackStop();
            }
            damage = 0;
        }

        if (me->HealthBelowPctDamaged(51, damage) && !phased)
        {
            events.DelayEvents(10s);
            me->CastStop();
            phased = true;
            phasing = true;
            damage = 0;
            me->NearTeleportTo({ 3095.94f, 965.095f, 258.774f, 4.46698f });
            me->SetUnitFlag(UnitFlags::UNIT_FLAG_NON_ATTACKABLE);
            me->SetReactState(REACT_PASSIVE);
            me->GetScheduler().Schedule(500ms, [this](TaskContext context)
            {
                Talk(3);
                DoCastSelf(SpellDrainPower);
            });
            me->GetScheduler().Schedule(5s, [this](TaskContext context)
            {
                setMovement = true;
                me->CastStop();
                me->SetReactState(REACT_AGGRESSIVE);
                me->AddAura(SpellEmpowered, me);
                phasing = false;
                me->RemoveUnitFlag(UnitFlags::UNIT_FLAG_NON_ATTACKABLE);
                DoCastAOE(CurseOfWeakness, true);
            });
        }
    }
};

// ID - 362864 Echoes of Andorhal
class spell_362864_echoes_of_andorhal : public SpellScript
{
    PrepareSpellScript(spell_362864_echoes_of_andorhal);

    void OverrideEntry(SpellEffIndex effIndex)
    {
        PreventHitDefaultEffect(effIndex);

        if (auto caster = GetCaster())
        {
            if (auto skelly = caster->SummonCreature(NecoWarriorAdd, *GetExplTargetDest(), TEMPSUMMON_NO_OWNER_DESPAWN))
            {
                skelly->SetOwnerGUID(caster->GetGUID());
                skelly->SetUnitFlag(UnitFlags::UNIT_FLAG_NON_ATTACKABLE);
             //   skelly->SetUnitFlag(UnitFlags::UNIT_FLAG_UNINTERACTIBLE);
                skelly->SetReactState(REACT_PASSIVE);
                skelly->SetControlled(true, UnitState::UNIT_STATE_ROOT);
                skelly->GetScheduler().Schedule(6s, [this, skelly](TaskContext context)
                {
                    skelly->SetControlled(false, UnitState::UNIT_STATE_ROOT);
                    skelly->RemoveUnitFlag(UnitFlags::UNIT_FLAG_NON_ATTACKABLE);
                    //skelly->RemoveUnitFlag(UnitFlags::UNIT_FLAG_UNINTERACTIBLE);
                    skelly->SetReactState(REACT_AGGRESSIVE);
                });
            }

        }
    }

    void Register() override
    {
        OnEffectHit += SpellEffectFn(spell_362864_echoes_of_andorhal::OverrideEntry, EFFECT_0, SPELL_EFFECT_SUMMON);
    }
};

// ID - 253089 Demonic Crash
class spell_demonic_crash : public SpellScript
{
    PrepareSpellScript(spell_demonic_crash);

    Position pos = { 3099.1f, 972.114f, 257.738f, 5.65488f };

    bool Load() override
    {
        // Definitely not a good thing, but currently the only way to do something at cast start
        // Should be replaced as soon as possible with a new hook: BeforeCastStart
        if (auto caster = GetCaster())
        {
            if (auto target = ObjectAccessor::GetUnit(*caster, caster->GetTarget()))
                pos = *target;

            Movement::MoveSplineInit init(caster);
            init.MoveTo(pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ(), true);
            init.SetParabolicVerticalAcceleration(25.0f, 0);
            init.SetUncompressed();
            init.SetVelocity(20.0f);
            Movement::SpellEffectExtraData extraData;
            extraData.SpellVisualId = 50217;
            extraData.ProgressCurveId = 1636;
            extraData.ParabolicCurveId = 0;

            init.SetSpellEffectExtraData(extraData);
           // init.SetAnimation(AnimTier::Hover);
            init.Launch();

            //if (hasOrientation)
            //    init.SetFacing(pos.GetOrientation());
        }
        return true;
    }


    void HandleBeforeCast()
    {
        if (auto caster = GetCaster())
        {
           // caster->GetMotionMaster()->MoveLand(1, pos);
        }
    }

    void Register() override
    {
        BeforeCast += SpellCastFn(spell_demonic_crash::HandleBeforeCast);
    }
};

// 703014 - npc_floating_books_703014
struct npc_floating_books_703014 : public ScriptedAI
{
public:
    npc_floating_books_703014(Creature* creature) : ScriptedAI(creature) { }

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

    TaskScheduler scheduler;
    EventMap events;
};

// 703017 - npc_kuryash_703017
struct npc_kuryash_703017 : public BossAI
{
public:
    npc_kuryash_703017(Creature* creature) : BossAI(creature, BossKuryash)
    {
        ApplyAllImmunities(true);
    }

    enum Kuryash
    {
        EventArcaneOrbs = 1,
        EventArcaneExplosion,
        EventArcaneBarrage,
        EventArcaneMissles,

        ArcaneOrb = 153626,
        ArcaneOrbs = 298787,
        ArcaneExplosionBig = 225960,
        ArcaneBarrage = 224564,
        ArcaneMissles = 333820,
    };

    void InitializeAI() override
    {
        BossAI::InitializeAI();
    }

    void Reset() override
    {
        BossAI::Reset();
    }

    void JustEngagedWith(Unit* who) override
    {
        BossAI::JustEngagedWith(who);
        Talk(0);
        DoCastAOE(ArcaneOrbs);
        //events.ScheduleEvent(EventArcaneOrbs, 5s);
        events.ScheduleEvent(EventArcaneExplosion, 1s);
        events.ScheduleEvent(EventArcaneBarrage, 5s);
        events.ScheduleEvent(EventArcaneMissles, 5s, 7s);
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        scheduler.Update(diff);
        events.Update(diff);

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        if (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EventArcaneOrbs:
                    if (me->GetVictim())
                        me->CastSpell(*me->GetVictim(), ArcaneOrb, true);
                    events.Repeat(5s);
                    break;
                case EventArcaneExplosion:
                    if (phase)
                        Talk(1);
                    DoCastAOE(ArcaneExplosionBig);
                   // events.Repeat(15s, 20s);
                    break;
                case EventArcaneBarrage:
                    DoCastVictim(ArcaneBarrage);
                    events.Repeat(5s, 10s);
                    break;
                case EventArcaneMissles:
                    DoCastVictim(ArcaneMissles);
                    events.Repeat(15s, 20s);
                    break;
            }

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;
        }

        DoMeleeAttackIfReady();
    }

    bool phase = false;
    void DamageTaken(Unit* attacker, uint32& damage, DamageEffectType /*damageType*/, SpellInfo const* /*spellInfo = nullptr*/) override
    {
        if (me->HealthBelowPct(31) && !phase)
        {
            damage = 0;
            phase = true;
            events.ScheduleEvent(EventArcaneExplosion, 1s);
        }
    }

    void EnterEvadeMode(EvadeReason why) override
    {
        phase = false;
        SetCombatMovement(true);
        _DespawnAtEvade(3s);
        scheduler.CancelAll();
        me->SetReactState(REACT_AGGRESSIVE);
        me->GetScheduler().CancelAll();
    }

    TaskScheduler scheduler;
    EventMap events;
};

// 703022 - npc_demon_larva_703022
struct npc_demon_larva_703022 : public ScriptedAI
{
public:
    npc_demon_larva_703022(Creature* creature) : ScriptedAI(creature) { }

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

    TaskScheduler scheduler;
    EventMap events;
};

// 703025 - npc_hellfire_infernal_703025
struct npc_hellfire_infernal_703025 : public ScriptedAI
{
public:
    npc_hellfire_infernal_703025(Creature* creature) : ScriptedAI(creature) { }

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

    TaskScheduler scheduler;
    EventMap events;
};

// 703021 - npc_demonic_tome_703021
struct npc_demonic_tome_703021 : public ScriptedAI
{
public:
    npc_demonic_tome_703021(Creature* creature) : ScriptedAI(creature), summons(creature) { }

    void InitializeAI() override
    {
        me->SetReactState(REACT_PASSIVE);
        me->SetUnitFlag(UnitFlags::UNIT_FLAG_NON_ATTACKABLE);
        me->SetUnitFlag(UnitFlags::UNIT_FLAG_IMMUNE_TO_PC);
        me->SetUnitFlag(UnitFlags::UNIT_FLAG_IMMUNE_TO_NPC);
        me->RemoveNpcFlag(NPCFlags::UNIT_NPC_FLAG_SPELLCLICK);

        DoSummon(703025, { 3039.3f, 903.964f, 246.888f, 6.12611f }, 0s, TEMPSUMMON_MANUAL_DESPAWN);
        DoSummon(703025, { 3052.26f, 883.029f, 246.961f, 1.01775f }, 0s, TEMPSUMMON_MANUAL_DESPAWN);
    }

    SummonList summons;
    uint32 Summs = 0;

    void JustSummoned(Creature* creature) override
    {
        summons.Summon(creature);
        ++Summs;
    }

    void SummonedCreatureDies(Creature* summ, Unit* who) override
    {
        if (Summs > 0)
        {
            --Summs;
            if (Summs == 0)
            {
                me->RemoveUnitFlag(UnitFlags::UNIT_FLAG_IMMUNE_TO_PC);
                me->RemoveUnitFlag(UnitFlags::UNIT_FLAG_IMMUNE_TO_NPC);
                me->SetFaction(35);
                me->SetNpcFlag(NPCFlags::UNIT_NPC_FLAG_SPELLCLICK);
            }
        }
    }

    void DoAction(int32 actionId) override
    {
        if (actionId == 40)
        {
            if (me->HasNpcFlag(NPCFlags::UNIT_NPC_FLAG_SPELLCLICK))
            {
                me->RemoveNpcFlag(NPCFlags::UNIT_NPC_FLAG_SPELLCLICK);
                DoCastSelf(312216, true); // Fade out

                if (auto instance = me->GetInstanceScript())
                {
                    if (auto map = instance->instance)
                    {
                        map->DoOnPlayers([](Player* player)
                        {
                            player->ModifyCurrency(1813, urand(500, 750));
                        });
                    }
                }

                me->DespawnOrUnsummon(1s);
            }
        }
    }

    void Reset() override
    {
        /// TODO: Fill this function
    }
    void JustEngagedWith(Unit* /*who*/) override
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

    TaskScheduler scheduler;
    EventMap events;
};

// 703026 - npc_hellish_imp_703026
struct npc_hellish_imp_703026 : public ScriptedAI
{
public:
    npc_hellish_imp_703026(Creature* creature) : ScriptedAI(creature) { }

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

    TaskScheduler scheduler;
    EventMap events;
};

// 703024 - npc_condemned_demon_703024
struct npc_condemned_demon_703024 : public ScriptedAI
{
public:
    npc_condemned_demon_703024(Creature* creature) : ScriptedAI(creature) { }

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

    bool didIntro = false;

    void MoveInLineOfSight(Unit* who) override
    {
        ScriptedAI::MoveInLineOfSight(who);
        if (!didIntro && who->IsPlayer() && who->GetDistance2d(me) <= 30.0f)
        {
            if (me->GetSpawnId() == 1054306)
            {
                didIntro = true;
                Talk(0);
                scheduler.Schedule(3s, [this](TaskContext context)
                {
                    if (auto demon = me->FindNearestCreatureBySpawnId(1054307, 30.0f))
                    {
                        if (demon->AI())
                            demon->AI()->Talk(1);
                    }
                });
            }
        }
    }

    TaskScheduler scheduler;
    EventMap events;
};

// 703016 - npc_storm_voidwalker_703016
struct npc_storm_voidwalker_703016 : public ScriptedAI
{
public:
    npc_storm_voidwalker_703016(Creature* creature) : ScriptedAI(creature) { }

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

    TaskScheduler scheduler;
    EventMap events;
};

// 703005 - npc_soul_bound_brute_703005
struct npc_soul_bound_brute_703005 : public ScriptedAI
{
public:
    npc_soul_bound_brute_703005(Creature* creature) : ScriptedAI(creature) { }

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

    TaskScheduler scheduler;
    EventMap events;
};

// 703004 - npc_soul_bound_warrior_703004
struct npc_soul_bound_warrior_703004 : public ScriptedAI
{
public:
    npc_soul_bound_warrior_703004(Creature* creature) : ScriptedAI(creature) { }

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

    TaskScheduler scheduler;
    EventMap events;
};

// 703019 - npc_vampiric_slave_703019
struct npc_vampiric_slave_703019 : public ScriptedAI
{
public:
    npc_vampiric_slave_703019(Creature* creature) : ScriptedAI(creature) { }

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

    TaskScheduler scheduler;
    EventMap events;
};

// 703020 - npc_vampiric_warrior_703020
struct npc_vampiric_warrior_703020 : public ScriptedAI
{
public:
    npc_vampiric_warrior_703020(Creature* creature) : ScriptedAI(creature) { }

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

    TaskScheduler scheduler;
    EventMap events;
};

// 703018 - npc_necromantic_warrior_703018
struct npc_necromantic_warrior_703018 : public ScriptedAI
{
public:
    npc_necromantic_warrior_703018(Creature* creature) : ScriptedAI(creature) { }

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

    TaskScheduler scheduler;
    EventMap events;
};

// 703010 - npc_fel_bound_mech_703010
struct npc_fel_bound_mech_703010 : public ScriptedAI
{
public:
    npc_fel_bound_mech_703010(Creature* creature) : ScriptedAI(creature) { }

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

    TaskScheduler scheduler;
    EventMap events;
};

// 703002 - npc_bound_earth_spirit_703002
struct npc_bound_earth_spirit_703002 : public ScriptedAI
{
public:
    npc_bound_earth_spirit_703002(Creature* creature) : ScriptedAI(creature) { }

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

    TaskScheduler scheduler;
    EventMap events;
};

// 703003 - npc_arcane_hound_703003
struct npc_arcane_hound_703003 : public ScriptedAI
{
public:
    npc_arcane_hound_703003(Creature* creature) : ScriptedAI(creature) { }

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

    TaskScheduler scheduler;
    EventMap events;
};

// 703008 - npc_mana_bound_golem_703008
struct npc_mana_bound_golem_703008 : public ScriptedAI
{
public:
    npc_mana_bound_golem_703008(Creature* creature) : ScriptedAI(creature) { }

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

    TaskScheduler scheduler;
    EventMap events;
};

// 703015 - npc_arcane_researcher_703015
struct npc_arcane_researcher_703015 : public ScriptedAI
{
public:
    npc_arcane_researcher_703015(Creature* creature) : ScriptedAI(creature) { }

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

    TaskScheduler scheduler;
    EventMap events;
};

// 703006 - npc_anivia_703006
struct npc_anivia_703006 : public ScriptedAI
{
public:
    npc_anivia_703006(Creature* creature) : ScriptedAI(creature) { }

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

    TaskScheduler scheduler;
    EventMap events;
};

// 703023 - npc_demonfly_acidmaw_703023
struct npc_demonfly_acidmaw_703023 : public ScriptedAI
{
public:
    npc_demonfly_acidmaw_703023(Creature* creature) : ScriptedAI(creature) { }

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

    TaskScheduler scheduler;
    EventMap events;
};

// ID - 369260 Destroying
class spell_destroying_369260 : public SpellScript
{
    PrepareSpellScript(spell_destroying_369260);

    void HandleDummy(SpellEffIndex /*effIndex*/)
    {
        Creature* target = GetHitCreature();
        if (!target || !target->IsAIEnabled())
            return;

        target->AI()->DoAction(40);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_destroying_369260::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

const Position gorothPortalPath[] =
{
    { 3097.2f, 1095.18f, 290.47f, 3.99875f },
    { 3079.34f, 1063.3f, 296.177f, 4.29982f },
    { 3071.81f, 1026.87f, 307.821f, 4.61071f },
    { 3078.16f, 995.567f, 321.419f, 5.1834f },
    { 3105.26f, 974.107f, 336.417f, 5.89353f },
    { 3140.43f, 969.273f, 352.167f, 0.0521354f },
    { 3180.66f, 986.297f, 373.925f, 0.634639f },
    { 3201.18f, 1010.63f, 388.335f, 0.955344f },
    { 3221.31f, 1046.53f, 405.758f, 1.14515f },
    { 3241.1f, 1092.63f, 423.376f, 1.18115f },
    { 3276.8f, 1173.26f, 445.354f, 1.07315f },
    { 3302.04f, 1219.36f, 453.597f, 1.06988f },
    { 3368.47f, 1340.69f, 475.195f, 1.06988f },
    { 3427.75f, 1436.37f, 488.366f, 0.781902f },
    { 3465.78f, 1473.13f, 470.315f, 1.24987f },
    { 3473.99f, 1494.19f, 451.932f, 2.03527f },
    { 3474.13f, 1504.01f, 437.722f, 2.40505f },
};

// 703028 - npc_portal_to_goroth_703028
struct npc_portal_to_goroth_703028 : public ScriptedAI
{
public:
    npc_portal_to_goroth_703028(Creature* creature) : ScriptedAI(creature) { }

    bool OnGossipHello(Player* player) override
    {
        CloseGossipMenuFor(player);
        player->SetDisplayId((urand(0, 1) == 1) ? 75922 : 74041);
        player->GetMotionMaster()->MoveSmoothPath(1, gorothPortalPath, 17, false, true, 90.0f)->callbackFunc = [this, player]()
        {
            player->RestoreDisplayId();
        };
        return true;
    }

    TaskScheduler scheduler;
    EventMap events;
};
// 800062 - npc_ruby_necklace_800062
struct npc_ruby_necklace_800062 : public ScriptedAI
{
public:
    npc_ruby_necklace_800062(Creature* creature) : ScriptedAI(creature) { }

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
            auto questStatus = player->GetQuestStatus(700102);
            if (questStatus == QUEST_STATUS_INCOMPLETE)
                return true;
        }

        return false;
    }
};

void AddSC_DreadscarRift()
{
    RegisterInstanceScript(instance_dreadscarrift, 1107);
    RegisterCreatureAI(npc_adageor_703000);
    RegisterCreatureAI(npc_goroth_703001);
    RegisterCreatureAI(npc_harvested_mana_crystal_703007);
    RegisterCreatureAI(npc_moz_gar_703009);
    RegisterCreatureAI(npc_arcane_voidwalker_703011);
    RegisterCreatureAI(npc_dolgonir_703012);
    RegisterCreatureAI(npc_bellatrix_703013);
    RegisterCreatureAI(npc_floating_books_703014);
    RegisterCreatureAI(npc_kuryash_703017);
    RegisterCreatureAI(npc_demon_larva_703022);
    RegisterCreatureAI(npc_hellfire_infernal_703025);
    RegisterCreatureAI(npc_demonic_tome_703021);
    RegisterCreatureAI(npc_hellish_imp_703026);
    RegisterCreatureAI(npc_condemned_demon_703024);
    RegisterCreatureAI(npc_storm_voidwalker_703016);
    RegisterCreatureAI(npc_soul_bound_brute_703005);
    RegisterCreatureAI(npc_soul_bound_warrior_703004);
    RegisterCreatureAI(npc_vampiric_slave_703019);
    RegisterCreatureAI(npc_vampiric_warrior_703020);
    RegisterCreatureAI(npc_necromantic_warrior_703018);
    RegisterCreatureAI(npc_fel_bound_mech_703010);
    RegisterCreatureAI(npc_bound_earth_spirit_703002);
    RegisterCreatureAI(npc_arcane_hound_703003);
    RegisterCreatureAI(npc_mana_bound_golem_703008);
    RegisterCreatureAI(npc_arcane_researcher_703015);
    RegisterCreatureAI(npc_anivia_703006);
    RegisterCreatureAI(npc_demonfly_acidmaw_703023);
    RegisterCreatureAI(npc_fel_conduit_703027);
    RegisterCreatureAI(npc_portal_to_goroth_703028);
    RegisterCreatureAI(npc_ruby_necklace_800062);

    RegisterSpellScript(spell_destroying_369260);
    RegisterSpellScript(spell_362864_echoes_of_andorhal);
    RegisterSpellScript(spell_demonic_crash);
}

// UPDATE creature_template set ScriptName = 'npc_adageor_703000' WHERE entry = 703000;
// UPDATE creature_template set ScriptName = 'npc_goroth_703001' WHERE entry = 703001;
// UPDATE creature_template set ScriptName = 'npc_harvested_mana_crystal_703007' WHERE entry = 703007;
// UPDATE creature_template set ScriptName = 'npc_moz_gar_703009' WHERE entry = 703009;
// UPDATE creature_template set ScriptName = 'npc_arcane_voidwalker_703011' WHERE entry = 703011;
// UPDATE creature_template set ScriptName = 'npc_dolgonir_703012' WHERE entry = 703012;
// UPDATE creature_template set ScriptName = 'npc_bellatrix_703013' WHERE entry = 703013;
// UPDATE creature_template set ScriptName = 'npc_floating_books_703014' WHERE entry = 703014;
// UPDATE creature_template set ScriptName = 'npc_kuryash_703017' WHERE entry = 703017;
// UPDATE creature_template set ScriptName = 'npc_demon_larva_703022' WHERE entry = 703022;
// UPDATE creature_template set ScriptName = 'npc_hellfire_infernal_703025' WHERE entry = 703025;
// UPDATE creature_template set ScriptName = 'npc_demonic_tome_703021' WHERE entry = 703021;
// UPDATE creature_template set ScriptName = 'npc_hellish_imp_703026' WHERE entry = 703026;
// UPDATE creature_template set ScriptName = 'npc_condemned_demon_703024' WHERE entry = 703024;
// UPDATE creature_template set ScriptName = 'npc_storm_voidwalker_703016' WHERE entry = 703016;
// UPDATE creature_template set ScriptName = 'npc_soul_bound_brute_703005' WHERE entry = 703005;
// UPDATE creature_template set ScriptName = 'npc_soul_bound_warrior_703004' WHERE entry = 703004;
// UPDATE creature_template set ScriptName = 'npc_vampiric_slave_703019' WHERE entry = 703019;
// UPDATE creature_template set ScriptName = 'npc_vampiric_warrior_703020' WHERE entry = 703020;
// UPDATE creature_template set ScriptName = 'npc_necromantic_warrior_703018' WHERE entry = 703018;
// UPDATE creature_template set ScriptName = 'npc_fel_bound_mech_703010' WHERE entry = 703010;
// UPDATE creature_template set ScriptName = 'npc_bound_earth_spirit_703002' WHERE entry = 703002;
// UPDATE creature_template set ScriptName = 'npc_arcane_hound_703003' WHERE entry = 703003;
// UPDATE creature_template set ScriptName = 'npc_mana_bound_golem_703008' WHERE entry = 703008;
// UPDATE creature_template set ScriptName = 'npc_arcane_researcher_703015' WHERE entry = 703015;
// UPDATE creature_template set ScriptName = 'npc_anivia_703006' WHERE entry = 703006;
// UPDATE creature_template set ScriptName = 'npc_demonfly_acidmaw_703023' WHERE entry = 703023;
// UPDATE creature_template set ScriptName = 'npc_fel_conduit_703027' WHERE entry = 703027;
