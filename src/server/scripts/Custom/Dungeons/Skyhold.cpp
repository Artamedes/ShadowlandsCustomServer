#include "ScriptMgr.h"
#include "CustomInstanceScript.h"
#include "ScriptedGossip.h"
#include "GameTime.h"
#include "Player.h"
#include "GameObjectAI.h"
#include "Conversation.h"
#include "InstanceScenario.h"

class instance_skyhold : public InstanceMapScript
{
    public:
        instance_skyhold() : InstanceMapScript("instance_skyhold", 2472) { }

        struct instance_skyhold_InstanceMapScript : public CustomInstanceScript
        {
            public:
                instance_skyhold_InstanceMapScript(InstanceMap* map) : CustomInstanceScript(map)
                {
                    ChestSpawn = { 817.872f, 7216.77f, 6.4894f, 1.54134f };
                    Quad = { -0.0f, -0.0f, -0.696618f, -0.717442f };
                }

                void Create() override
                {

                }

                void Load(char const* data) override
                {

                }

                void OnCompletedCriteriaTree(CriteriaTree const* /*tree*/) override
                {
                    if (InstanceScenario* instanceScenario = instance->GetInstanceScenario())
                    {
                        if (auto tree2 = sCriteriaMgr->GetCriteriaTree(301100))
                            instanceScenario->IsCompletedCriteriaTree(tree2, nullptr);
                    }
                }

                void SummonChallengeGameObject(bool door) override
                {
                    if (door)
                    {
                        if (auto go = instance->SummonGameObject(MYTHIC_DOOR_4, { 1028.66f, 7225.09f, -2.456146f, 3.13832f }, { -0.0f, -0.0f, -0.712643f, 0.701527f }, 0))
                        {
                            go->SetGoState(GOState::GO_STATE_READY);
                            go->SetFlag(GameObjectFlags::GO_FLAG_NOT_SELECTABLE);
                        }
                    }
                }
        };

        InstanceScript* GetInstanceScript(InstanceMap* map) const override
        {
            return new instance_skyhold_InstanceMapScript(map);
        }
};

struct npc_skyhold_sylvanas : public ScriptedAI
{
    public:
        npc_skyhold_sylvanas(Creature* c) : ScriptedAI(c) { }

        void Reset() override
        {

        }

        bool m_DidCorrupt = false;

        bool OnGossipHello(Player* player) override
        {
            ClearGossipMenuFor(player);
            player->PrepareQuestMenu(me->GetGUID());
            if (player->GetQuestStatus(700016) == QUEST_STATUS_REWARDED && player->GetQuestStatus(700017) != QUEST_STATUS_NONE && !m_DidCorrupt)
                AddGossipItemFor(player, GossipOptionIcon::None, "Wreak havoc", 0, 1);
            SendGossipMenuFor(player, me->GetEntry(), me);
            return true;
        }

        void OnQuestAccept(Player* player, Quest const* quest) override
        {
            if (quest->GetQuestId() == 700017)
            {
                Talk(2, player);
            }
        }

        Position const SylvPathOne[18] =
        {
            { 1022.469971f, 7230.910156f, -0.034910f },
            { 1027.974487f, 7225.186035f, 12.402938f, 4.705851f },
            { 1027.025635f, 7128.470215f, 6.201820f, 4.702578f },
            { 1024.731745f, 7053.938965f, 17.931179f },
            { 1029.782959f, 7288.708984f, 18.897751f },
            { 1029.897461f, 7332.517090f, 26.771141f, 4.682945f },
            { 1029.314575f, 7252.280762f, 25.272377f },
            { 1020.473389f, 7227.040039f, 17.650282f},
            { 1106.944214f, 7223.873535f, 18.789654f },
            { 960.054199f, 7225.549316f, 15.612448f},
            { 820.187866f, 7228.616211f, 18.086391f, 3.099066f},
            { 803.519470f, 7297.768066f, 18.493834f},
            { 820.187866f, 7228.616211f, 18.086391f, 3.099066f},
            { 800.049927f, 7160.696289f, 19.651564f},
            { 820.187866f, 7228.616211f, 18.086391f, 3.099066f},
            { 956.775513f, 7226.856445f, 16.581532f },
            { 1020.473389f, 7227.040039f, 17.650282f},
            { 1022.469971f, 7230.910156f, -0.034910f },
        };

        using SylvPathOneSize = std::extent<decltype(SylvPathOne)>;

        void MovementInform(uint32 type, uint32 id) override
        {
            if (id == 1)
            {
                m_DidCorrupt = true;
                m_Flying = false;
                Talk(1);
                me->RemoveAurasDueToSpell(359361); // Banshee form
                me->SetObjectScale(2.0f);
                scheduler.Schedule(100ms, [this](TaskContext context)
                {
                    me->SetFacingTo(-0.034910f);
                    me->SetNpcFlag(UNIT_NPC_FLAG_GOSSIP);
                    me->SetNpcFlag(UNIT_NPC_FLAG_QUESTGIVER);
                });
            }
        }
        
        bool OnGossipSelect(Player* player, uint32 menuid, uint32 gossipid) override
        {
            uint32 action = player->PlayerTalkClass->GetGossipOptionAction(gossipid);
            CloseGossipMenuFor(player);
            switch (action)
            {
                case 1:
                    player->RewardPlayerAndGroupAtEvent(me->GetEntry(), me);
                    me->RemoveNpcFlag(UNIT_NPC_FLAG_GOSSIP);
                    me->RemoveNpcFlag(UNIT_NPC_FLAG_QUESTGIVER);
                    Talk(0);

                    scheduler.Schedule(1s, [this](TaskContext context)
                    {
                        DoCast(359361); // Banshee Form
                    });
                    scheduler.Schedule(5s, [this](TaskContext context)
                    {
                        me->GetMotionMaster()->MoveSmoothPath(1, SylvPathOne, SylvPathOneSize::value, false, true);
                        m_Flying = true;
                    });
                    break;
            }
            return true;
        }

        void UpdateAI(uint32 diff) override
        {
            scheduler.Update(diff);
            events.Update(diff);

            if (!m_Flying)
                return;

            std::list<Unit*> list;
            me->GetFriendlyUnitListInRange(list, 40.0f, true);

            list.remove_if([&](Unit* target)
            {
                return hitTargets.count(target->GetGUID()) || (target->GetEntry() <= 700300 || target->GetEntry() >= 700330);
            });

            for (Unit* creature : list)
            {
                hitTargets.emplace(creature->GetGUID());
                DoCast(creature, 357616);
                creature->SetFaction(168);
                creature->CastSpell(creature, 294036, true);
                creature->SetEmoteState(EMOTE_STATE_READY1H);
            }
        }

        TaskScheduler scheduler;
        EventMap events;
        std::unordered_set<ObjectGuid> hitTargets;
        bool m_Flying = false;
};


struct npc_odyn_700312 : public ScriptedAI
{
public:
    npc_odyn_700312(Creature* creature) : ScriptedAI(creature)
    {
        ApplyAllImmunities(true);
    }

    enum Talks
    {
        TalkAggro = 0,
        TalkEvade = 1,
        TalkFriend,
    };

    void Reset() override
    {

    }

    void JustEngagedWith(Unit* who) override
    {
        if (who->IsPlayer())
            wasEngaged = true;
        Talk(Talks::TalkAggro);
    }

    void EnterEvadeMode(EvadeReason why) override
    {
        ScriptedAI::EnterEvadeMode(why);
        if (wasEngaged)
        {
            Talk(Talks::TalkEvade);
            wasEngaged = false;
        }
    }

    bool m_Talked = false;

    void OnUnitRelocation(Unit* who) override
    {
        if (who->IsPlayer() && me->GetFaction() == 35 && !m_Talked && who->GetDistance(me) <= 55.0f)
        {
            Talk(TalkFriend, who);
            m_Talked = true;
        }
    }

    void JustDied(Unit* killer) override
    {
        me->SummonGameObject(700000, { 836.368f, 7228.57f , 6.49474f , 3.10886f }, { -0.0f, -0.0f,-0.999866f, -0.016364f }, Hours(12), GOSummonType::GO_SUMMON_TIMED_DESPAWN);
        if (auto map = me->GetMap())
        {
            map->DoOnPlayers([](Player* player)
            {
                Conversation::CreateConversation(700300, player, *player, player->GetGUID());
            });
        }
    }

    uint32 corpseTimer = 0;

    void UpdateAI(uint32 diff) override
    {
        if (me->isDead())
        {
            corpseTimer += diff;
            if (corpseTimer >= 3000)
            {
                corpseTimer = 0;
                if (me->IsAllLooted())
                    me->DespawnOrUnsummon(0s, 999999s);
            }
        }

        if (!UpdateVictim())
            return;

        events.Update(diff);
        scheduler.Update(diff);

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        while (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {

            }
        }

        DoMeleeAttackIfReady();
    }

private:
    EventMap events;
    TaskScheduler scheduler;
    bool wasEngaged = false;
};

struct gobj_ancient_chest_700000 : public GameObjectAI
{
    public:
        gobj_ancient_chest_700000(GameObject* obj) : GameObjectAI(obj) { }

        bool m_Locked = false;
        TaskScheduler scheduler;

        // Called when a player opens a gossip dialog with the gameobject.
        bool OnGossipHello(Player* player) override
        {
            if (m_Locked)
                return true;
            ClearGossipMenuFor(player);
            AddGossipItemFor(player, GossipOptionIcon::None, "<Take the loot>", 0, 1);
            SendGossipMenuFor(player, 7000000, me->GetGUID());
            return true;
        }

        // Called when a player selects a gossip item in the gameobject's gossip menu.
        virtual bool OnGossipSelect(Player* player, uint32 /*menuId*/, uint32 gossipListId) override
        {
            uint32 actionId = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            CloseGossipMenuFor(player);
            if (actionId == 1)
            {
                me->SetFlag(GameObjectFlags::GO_FLAG_LOCKED);
                me->SetFlag(GameObjectFlags::GO_FLAG_NOT_SELECTABLE);
                m_Locked = true;
                // start the encounter..
                scheduler.Schedule(1s, [this](TaskContext context)
                {
                    if (auto instance = me->GetInstanceScript())
                        instance->DoCastSpellOnPlayers(365127);
                    me->SummonCreature(700316, { 836.420166f, 7234.518066f, 6.497904f, 4.732021f }, TEMPSUMMON_MANUAL_DESPAWN, 0);
                });
            }
            return true;
        }

        void UpdateAI(uint32 diff) override
        {
            scheduler.Update(diff);
        }

};

struct npc_dark_ascended_corrus : public ScriptedAI
{
    public:
        npc_dark_ascended_corrus(Creature* creature) : ScriptedAI(creature) { }

        void Reset()
        {
            events.Reset();
        }

        void InitializeAI() override
        {
            me->SetUnitFlag(UNIT_FLAG_NON_ATTACKABLE);
            me->SetReactState(REACT_PASSIVE);

            me->CastSpell(me, 332284);

            scheduler.Schedule(1s, [this](TaskContext context)
            {
                me->GetMap()->DoOnPlayers([this](Player* player)
                {
                    Talk(0, player);
                });

                me->CastSpell(me, 336193);
            });

            scheduler.Schedule(5s, [this](TaskContext context)
            {
                if (auto chest = me->FindNearestGameObject(700000, 30.0f))
                {
                    chest->DespawnOrUnsummon(5s);
                }
                Talk(1);
            });

            scheduler.Schedule(8s, [this](TaskContext context)
            {
                Talk(2);
            });

            scheduler.Schedule(10s, [this](TaskContext context)
            {
                me->RemoveAurasDueToSpell(336193);
                me->RemoveAurasDueToSpell(332284);
                me->RemoveUnitFlag(UNIT_FLAG_NON_ATTACKABLE);
                me->SetReactState(REACT_AGGRESSIVE);
                DoZoneInCombat();
            });
        }

        void JustEngagedWith(Unit* who) override
        {
            Talk(3);

            events.Reset();
            events.ScheduleEvent(1, 10s);
            events.ScheduleEvent(2, 15s, 20s);
            events.ScheduleEvent(3, 15s, 20s);
            events.ScheduleEvent(4, 5s, 20s);
        }

        void JustDied(Unit* who) override
        {
            Talk(4);
            me->GetMotionMaster()->MoveFall();
            if (auto map = me->GetMap())
            {
                map->DoOnPlayers([](Player* player)
                {
                    Conversation::CreateConversation(700301, player, *player, player->GetGUID());
                });
            }
        }

        void UpdateAI(uint32 diff) override
        {
            scheduler.Update(diff);

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
                        DoCast(299150); // Natural power
                        events.Repeat(10s);
                        break;
                    case 2:
                        DoCastVictim(304948); // Leap
                        events.Repeat(10s, 15s);
                        break;
                    case 3: // Shadow rip
                        DoCastVictim(304946);
                        events.Repeat(7s, 14s);
                        break;
                    case 4:
                        DoCastAOE(355769);
                        events.Repeat(5s, 30s);
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }

        TaskScheduler scheduler;
        EventMap events;
};

struct npc_valajar_aspirant : public ScriptedAI
{
    public:
        npc_valajar_aspirant(Creature* creature) : ScriptedAI(creature) { }

        void Reset() override
        {
            events.Reset();

            if (me->GetFaction() == 168)
                DoCastSelf(294036, true);
        }

        void JustEngagedWith(Unit* who) override
        {
            events.ScheduleEvent(1, 5s, 7s);
            events.ScheduleEvent(2, 10s, 15s);
        }

        void UpdateAI(uint32 diff) override
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            auto victim = me->GetVictim();
            if (!victim)
                return;

            if (!me->IsWithinMeleeRange(me->GetVictim()))
            {
                auto now = GameTime::Now();
                if (now >= NextAllowedChargeTime)
                {
                    NextAllowedChargeTime = now + Seconds(8);
                    DoCastVictim(259831); // Leap
                }
                return;
            }

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case 1:
                        DoCastVictim(340174, true);
                        events.Repeat(5s, 10s);
                        break;
                    case 2:
                        DoCastVictim(329310, true);
                        events.Repeat(15s, 20s);
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }

        EventMap events;
        TimePoint NextAllowedChargeTime;
};

struct npc_go_to_herald_of_odyn : public ScriptedAI
{
    public:
        npc_go_to_herald_of_odyn(Creature* creature) : ScriptedAI(creature) { }

        void UpdateAI(uint32 diff)
        {
            std::list<Unit*> players;
            me->GetFriendlyUnitListInRange(players, 2.0f, true);
            players.remove_if([&](Unit* unit)
            {
                return !unit->IsPlayer() || unit->IsInCombat() || unit->GetPositionZ() <= -3.f;
            });

            auto now = GameTime::Now();

            for (auto unit : players)
            {
                auto itr = m_MovedPlayers.find(unit->GetGUID());
                if (itr == m_MovedPlayers.end() || now >= itr->second)
                {
                    unit->GetMotionMaster()->MoveJumpWithGravity({ 1026.066528f, 7108.098633f, -6.717453f, 4.689483f }, 5.f, 15.f);
                    m_MovedPlayers[unit->GetGUID()] = now + 3s;
                }
            }
        }

        std::unordered_map<ObjectGuid, TimePoint> m_MovedPlayers;
};

struct npc_herald_of_odyn : public ScriptedAI
{
    public:
        npc_herald_of_odyn(Creature* creature) : ScriptedAI(creature)
        {
            ApplyAllImmunities(true);
        }

        void Reset() override
        {

        }

        void JustDied(Unit* killer) override
        {
            Talk(1);
        }

        void JustEngagedWith(Unit* unit) override
        {
            Talk(0);
            events.ScheduleEvent(1, 5s, 7s);
            events.ScheduleEvent(2, 15s, 17s);
            events.ScheduleEvent(3, 10s, 15s);
        }

        void UpdateAI(uint32 diff) override
        {
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
                        DoCast(363523);
                        events.Repeat(20s, 30s);
                        break;
                    case 2:
                        DoCast(358410);
                        events.Repeat(15s, 30s);
                        break;
                    case 3:
                        DoCast(361023);
                        events.Repeat(10s, 20s);
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }


        EventMap events;
};

struct npc_god_king_skovald : public ScriptedAI
{
    public:
        npc_god_king_skovald(Creature* creature) : ScriptedAI(creature)
        {
            ApplyAllImmunities(true);
        }

        void Reset() override
        {

        }

        void JustDied(Unit* killer) override
        {
            Talk(2);
        }

        void JustEngagedWith(Unit* unit) override
        {
            Talk(0);
            events.ScheduleEvent(1, 5s, 7s);
            events.ScheduleEvent(2, 15s, 17s);
            events.ScheduleEvent(3, 10s, 15s);
        }

        void UpdateAI(uint32 diff) override
        {
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
                        DoCast(193668);
                        events.Repeat(20s, 30s);
                        Talk(1);
                        break;
                    case 2:
                        DoCast(222036);
                        events.Repeat(15s, 30s);
                        break;
                    case 3:
                        DoCast(85691);
                        events.Repeat(10s, 20s);
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }


        EventMap events;
};

struct npc_volynd_stormbringer : public ScriptedAI
{
    public:
        npc_volynd_stormbringer(Creature* creature) : ScriptedAI(creature) { }

        void Reset() override
        {

        }

        void JustDied(Unit* killer) override
        {
        }

        void JustEngagedWith(Unit* unit) override
        {
            events.ScheduleEvent(1, 5s, 7s);
            events.ScheduleEvent(2, 15s, 17s);
            events.ScheduleEvent(3, 10s, 15s);
        }

        void UpdateAI(uint32 diff) override
        {
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
                        DoCast(358896);
                        events.Repeat(5s, 10s);
                        break;
                    case 2:
                        DoCast(305485);
                        events.Repeat(15s, 30s);
                        break;
                    case 3:
                        DoCast(309666);
                        events.Repeat(10s, 20s);
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }


        EventMap events;
};


struct npc_valajar_thundercaller : public ScriptedAI
{
public:
    npc_valajar_thundercaller(Creature* creature) : ScriptedAI(creature) { }

    void Reset() override
    {

    }

    void JustDied(Unit* killer) override
    {
    }

    void JustEngagedWith(Unit* unit) override
    {
        events.ScheduleEvent(1, 5s, 7s);
        events.ScheduleEvent(2, 15s, 17s);
    }

    void UpdateAI(uint32 diff) override
    {
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
                DoCast(198595);
                events.Repeat(5s, 10s);
                break;
            case 2:
                DoCast(198599);
                events.Repeat(15s, 30s);
                break;
            }
        }

        DoMeleeAttackIfReady();
    }


    EventMap events;
};

struct npc_valajar_falconer : public ScriptedAI
{
public:
    npc_valajar_falconer(Creature* creature) : ScriptedAI(creature) { }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        DoMeleeAttackIfReady();
        //DoRangedAttackIfReady();
    }

    void DoRangedAttackIfReady()
    {
        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        if (!me->isAttackReady(RANGED_ATTACK))
            return;

        Unit* victim = me->GetVictim();
        if (!victim)
            return;

        uint32 rangedAttackSpell = 145759;
        SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(rangedAttackSpell, me->GetMap()->GetDifficultyID());
        if (!spellInfo)
            return;

        Spell* spell = new Spell(me, spellInfo, TRIGGERED_CAST_DIRECTLY);
        if (spell->CheckPetCast(victim) != SPELL_CAST_OK)
        {
            delete spell;
            return;
        }

        SpellCastTargets targets;
        targets.SetUnitTarget(victim);
        spell->prepare(targets);

        me->resetAttackTimer(RANGED_ATTACK);
    }
};


class skyhold_dungeon_player_script : public PlayerScript
{
public:
    skyhold_dungeon_player_script() : PlayerScript("skyhold_dungeon_player_script") { }

    void OnQuestStatusChange(Player* player, uint32 questId) override
    {
        //if (player->GetMapId() != 2472)
        //    return;

        switch (questId)
        {
            case 700017: // Betrayal For Power
            {

                auto status = player->GetQuestStatus(questId);

                if (status == QUEST_STATUS_REWARDED)
                {
                    player->AddQuestAndCheckCompletion(sObjectMgr->GetQuestTemplate(700018), player);
                    player->PlayerTalkClass->SendQuestGiverQuestDetails(sObjectMgr->GetQuestTemplate(700018), player->GetGUID(), true, true);
                }

                break;

            }
        }
    }
};


void AddSC_Skyhold()
{
    new instance_skyhold();
    RegisterCreatureAI(npc_skyhold_sylvanas);
    RegisterCreatureAI(npc_odyn_700312);
    RegisterGameObjectAI(gobj_ancient_chest_700000);
    RegisterCreatureAI(npc_valajar_aspirant);
    RegisterCreatureAI(npc_go_to_herald_of_odyn);
    RegisterCreatureAI(npc_herald_of_odyn);
    RegisterCreatureAI(npc_god_king_skovald);
    RegisterCreatureAI(npc_volynd_stormbringer);
    RegisterCreatureAI(npc_valajar_thundercaller);
    RegisterCreatureAI(npc_valajar_falconer);
    RegisterCreatureAI(npc_dark_ascended_corrus);
    new skyhold_dungeon_player_script();
}
