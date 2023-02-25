#include "ScriptMgr.h"
#include "Player.h"
#include "Creature.h"
#include "ScriptedCreature.h"
#include "CustomInstanceScript.h"
#include "GameTime.h"
#include "SpellHistory.h"
#include "InstanceScenario.h"
#include "ReputationMgr.h"

struct npc_soul_of_a_frozen_one : public ScriptedAI
{
public:
    npc_soul_of_a_frozen_one(Creature* creature) : ScriptedAI(creature) { }

    void InitializeAI() override
    {
        me->SetReactState(REACT_PASSIVE);
        me->SetDisplayId(29286);
        me->SetUnitFlag(UNIT_FLAG_NON_ATTACKABLE);
        me->SetUnitFlag(UNIT_FLAG_UNINTERACTIBLE);
    }

    void Reset() override
    {
        me->SetReactState(REACT_PASSIVE);
        me->SetDisplayId(29286);
        me->SetUnitFlag(UNIT_FLAG_NON_ATTACKABLE);
        me->SetUnitFlag(UNIT_FLAG_UNINTERACTIBLE);
    }

    bool m_DidIntro = false;
    void OnUnitRelocation(Unit* who) override
    {
        if (!m_DidIntro && who->IsPlayer() && who->GetDistance2d(me) <= 20.0f)
        {
            m_DidIntro = true;
            me->SetReactState(REACT_AGGRESSIVE);
            me->DeMorph();
            me->SetFacingToObject(who);
            scheduler.Schedule(1s, [this](TaskContext context)
                {
                    me->SetReactState(REACT_AGGRESSIVE);
                    me->GetMotionMaster()->Move(0, MoveTypes::Forward, MOVE_PATHFINDING, 5.0f);
                    me->RemoveUnitFlag(UNIT_FLAG_NON_ATTACKABLE);
                    me->RemoveUnitFlag(UNIT_FLAG_UNINTERACTIBLE);
                });
        }
    }

    void JustEngagedWith(Unit* /*who*/)
    {
        me->SetReactState(REACT_AGGRESSIVE);
        me->DeMorph();
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

// 730503 - npc_soul_of_a_frozen_one_730503
struct npc_soul_of_a_frozen_one_730503 : public npc_soul_of_a_frozen_one
{
public:
    npc_soul_of_a_frozen_one_730503(Creature* creature) : npc_soul_of_a_frozen_one(creature) { }

};

// 730502 - npc_soul_of_a_frozen_one_730502
struct npc_soul_of_a_frozen_one_730502 : public npc_soul_of_a_frozen_one
{
public:
    npc_soul_of_a_frozen_one_730502(Creature* creature) : npc_soul_of_a_frozen_one(creature) { }
};

// 730505 - npc_vision_of_jaina_730505
struct npc_vision_of_jaina_730505 : public ScriptedAI
{
public:
    npc_vision_of_jaina_730505(Creature* creature) : ScriptedAI(creature)
    {
        ApplyAllImmunities(true);
    }

    enum JSpells
    {
        FrostBolt = 351173,
        FrostNova = 287456,
        Blink = 295236,
        KyrianVision = 343156,
        IceBlock = 290049,
        Deathborne = 324220,
    };

    void InitializeAI() override
    {
        DoCastSelf(KyrianVision);
        scheduler.Schedule(1s, [this](TaskContext context)
            {
                DoCastSelf(KyrianVision);
            });
    }

    void Reset() override
    {
        _canFrostNova = true;
        _isBlinking = false;
        phase = false;
        DoCastSelf(KyrianVision);
    }

    void JustEngagedWith(Unit* who) override
    {
        scheduler.CancelAll();
        me->CastStop();
        DoCast(Deathborne);

        Talk(0);
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        scheduler.Update(diff);
        events.Update(diff);

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        if (me->HasAura(IceBlock))
            return;

        auto victim = me->GetVictim();
        if (!victim)
            return;

        if (_canFrostNova && me->IsWithinMeleeRange(victim))
        {
            DoCastAOE(FrostNova);
            _canFrostNova = false;
            _isBlinking = true;
            scheduler.Schedule(250ms, [this](TaskContext context)
            {
                _isBlinking = false;
                me->SetFacingTo(3.959f);
                DoCast(Blink);
            });
            scheduler.Schedule(40s, [this](TaskContext context)
            {
                _canFrostNova = true;
            });
        }

        if (_isBlinking)
            return;

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        if (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
            }
            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;
        }

        DoCastVictim(FrostBolt);

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;
        DoMeleeAttackIfReady();
    }

    bool phase = false;

    void DamageTaken(Unit* attacker, uint32& damage, DamageEffectType /*damageType*/, SpellInfo const* /*spellInfo = nullptr*/) override
    {
        if (me->HealthBelowPctDamaged(51, damage) && !phase)
        {
            phase = true;
            me->CastStop();
            _canFrostNova = true;
            _isBlinking = false;
            scheduler.CancelAll();
            DoCastSelf(IceBlock);
        }
    }

    TaskScheduler scheduler;
    EventMap events;

    bool _canFrostNova = true;
    bool _isBlinking = false;
};

// 730500 - npc_two_headed_beast_730500
struct npc_two_headed_beast_730500 : public ScriptedAI
{
public:
    npc_two_headed_beast_730500(Creature* creature) : ScriptedAI(creature) { }

    void InitializeAI() override
    {
        me->SetReactState(REACT_PASSIVE);
        me->SetEmoteState(Emote::EMOTE_STATE_SLEEP);
        DoCastSelf(353814); // Sleeping
        me->SetFlying(true);

        RepeatPath();
    }

    void RepeatPath()
    {
        scheduler.Schedule(10s, 15s, [this](TaskContext context)
            {
                //me->PlayOneShotAnimKitId();
                auto pos = me->GetPosition();
                pos.m_positionZ + urand(20, 30);
                me->GetMotionMaster()->MoveTakeoff(0, pos);
                scheduler.Schedule(2s, [this](TaskContext context)
                    {
                        me->RemoveAurasDueToSpell(353814); // Sleeping
                        me->SetEmoteState(Emote::EMOTE_STATE_NONE);
                        auto pos = me->GetPosition();
                        pos.m_positionZ + urand(20, 30);
                        me->SetFlying(true);
                        me->GetMotionMaster()->MoveCirclePath(pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ(), urand(30, 40), urand(0, 1) == 0 ? true : false, 50);

                        scheduler.Schedule(10s, 50s, [this](TaskContext context)
                            {
                                me->GetMotionMaster()->MoveTargetedHome();
                                scheduler.Schedule(10s, [this](TaskContext context)
                                    {
                                        DoCastSelf(353814); // Sleeping
                                        me->SetEmoteState(Emote::EMOTE_STATE_SLEEP);
                                        RepeatPath();
                                    });
                            });
                    });
            });
    }

    void JustEngagedWith(Unit* /*who*/) override
    {
        events.Reset();
        me->SetReactState(REACT_AGGRESSIVE);
        me->SetEmoteState(Emote::EMOTE_STATE_SLEEP);
        me->RemoveAurasDueToSpell(353814); // Sleeping
    }

    void Reset() override
    {
        /// TODO: Fill this function
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

// 730504 - npc_icehowl_730504
struct npc_icehowl_730504 : public ScriptedAI
{
public:
    npc_icehowl_730504(Creature* creature) : ScriptedAI(creature)
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

// 730501 - npc_ice_dragon_730501
struct npc_ice_dragon_730501 : public ScriptedAI
{
public:
    npc_ice_dragon_730501(Creature* creature) : ScriptedAI(creature)
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

    bool m_Intro = false;

    void OnUnitRelocation(Unit* who) override
    {
        if (m_Intro)
            return;

        if (who->IsPlayer() && who->GetDistance2d(me) <= 50.0f)
        {
            m_Intro = true;
            DoCast(189302); // Dragon's roar
            Talk(0);
        }
    }

    TaskScheduler scheduler;
    EventMap events;
};

// 730508 - npc_black_ice_dragonkin_730508
struct npc_black_ice_dragonkin_730508 : public ScriptedAI
{
public:
    npc_black_ice_dragonkin_730508(Creature* creature) : ScriptedAI(creature) { }

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

    TaskScheduler scheduler;
    EventMap events;
};

// 730509 - npc_black_ice_dragonkin_730509
struct npc_black_ice_dragonkin_730509 : public ScriptedAI
{
public:
    npc_black_ice_dragonkin_730509(Creature* creature) : ScriptedAI(creature) { }

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

    TaskScheduler scheduler;
    EventMap events;
};

// 730511 - npc_ice_golem_730511
struct npc_ice_golem_730511 : public ScriptedAI
{
public:
    npc_ice_golem_730511(Creature* creature) : ScriptedAI(creature) { }

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

    TaskScheduler scheduler;
    EventMap events;
};

// 730512 - npc_ice_whisp_730512
struct npc_ice_whisp_730512 : public ScriptedAI
{
public:
    npc_ice_whisp_730512(Creature* creature) : ScriptedAI(creature) { }

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

    TaskScheduler scheduler;
    EventMap events;
};

// 730507 - npc_ice_elemental_730507
struct npc_ice_elemental_730507 : public ScriptedAI
{
public:
    npc_ice_elemental_730507(Creature* creature) : ScriptedAI(creature) { }

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

    TaskScheduler scheduler;
    EventMap events;
};

// 730506 - npc_water_elemental_730506
struct npc_water_elemental_730506 : public ScriptedAI
{
public:
    npc_water_elemental_730506(Creature* creature) : ScriptedAI(creature) { }

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

    TaskScheduler scheduler;
    EventMap events;
};

// slow aura - 287993
// 314884 - ice aura
struct instance_lost_glacier : public CustomInstanceScript
{
    public:
        instance_lost_glacier(InstanceMap* map) : CustomInstanceScript(map)
        {
            ChestSpawn = { 3084.71f, -217.456f, -31.9818f, 5.00364f };
            Quad = { -0.0f, -0.0f, -0.0593638f, 0.998236f };
            EnemyForcesCriteriaTreeId = 301301;
        }

        void SummonChallengeGameObject(bool door) override
        {
            if (door)
            {
                if (auto go = instance->SummonGameObject(MYTHIC_DOOR_4, { 2177.58f, 192.1f, 20.4789f, 5.50106f }, { -0.0f, -0.0f, -0.712643f, 0.701527f }, 0))
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
                if (auto tree2 = sCriteriaMgr->GetCriteriaTree(301300))
                    instanceScenario->IsCompletedCriteriaTree(tree2, nullptr);
            }
        }

        enum eLostGlacier
        {
            SlowAura = 287993,
            IceAura = 314884,
        };

        void CreatureDiesForScript(Creature* creature, Unit* killer) override
        {
            CustomInstanceScript::CreatureDiesForScript(creature, killer);

            auto shadowMilitia = sFactionStore.LookupEntry(ShadowMilitiaRep);
            if (!shadowMilitia)
                return;

            bool isBoss = creature->IsDungeonBoss();
            uint32 repAmount = isBoss ? 500 : 25;

            instance->DoOnPlayers([repAmount, shadowMilitia, creature](Player* player)
            {
                player->GetReputationMgr().ModifyReputation(shadowMilitia, repAmount);

                if (creature->GetFaction() != 35)
                    if (creature->IsDungeonBoss() || roll_chance_i(50))
                        player->ModifyCurrency(IceFragment, creature->IsDungeonBoss() ? 100 : urand(1, 3));
            });
        }

        void Update(uint32 diff) override
        {
            Map::PlayerList const& players = instance->GetPlayers();
            auto now = GameTime::Now();
            for (auto const& ref : players)
            {
                if (Player* player = ref.GetSource())
                {
                    auto diff = now - player->GetSession()->LastMoveTime;

                    if (diff >= 5s)
                    {
                        if (!player->GetSpellHistory()->HasCooldown(eLostGlacier::SlowAura) && !player->IsGameMaster())
                        {
                            player->CastSpell(player, eLostGlacier::SlowAura, true);
                            player->GetSpellHistory()->AddCooldown(eLostGlacier::SlowAura, 0, 1s);
                        }
                    }
                }
            }
        }
};
// 800060 - npc_box_of_jewelry_800060
struct npc_box_of_jewelry_800060 : public ScriptedAI
{
public:
    npc_box_of_jewelry_800060(Creature* creature) : ScriptedAI(creature) { }

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
            auto questStatus = player->GetQuestStatus(700100);
            if (questStatus == QUEST_STATUS_INCOMPLETE)
                return true;
        }

        return false;
    }
};

void AddSC_LostGlacier()
{
    RegisterCreatureAI(npc_soul_of_a_frozen_one_730503);
    RegisterCreatureAI(npc_soul_of_a_frozen_one_730502);
    RegisterCreatureAI(npc_vision_of_jaina_730505);
    RegisterCreatureAI(npc_two_headed_beast_730500);
    RegisterCreatureAI(npc_icehowl_730504);
    RegisterCreatureAI(npc_ice_dragon_730501);
    RegisterCreatureAI(npc_black_ice_dragonkin_730508);
    RegisterCreatureAI(npc_black_ice_dragonkin_730509);
    RegisterCreatureAI(npc_ice_golem_730511);
    RegisterCreatureAI(npc_ice_whisp_730512);
    RegisterCreatureAI(npc_ice_elemental_730507);
    RegisterCreatureAI(npc_water_elemental_730506);
    RegisterCreatureAI(npc_box_of_jewelry_800060);
    RegisterInstanceScript(instance_lost_glacier, 1738);
}
