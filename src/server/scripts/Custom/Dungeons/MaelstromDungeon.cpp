#include "ScriptMgr.h"
#include "Creature.h"
#include "ScriptedCreature.h"
#include "AchievementMgr.h"
#include "ScenarioMgr.h"
#include "InstanceScenario.h"
#include "../CustomInstanceScript.h"
#include "Conversation.h"

enum MaelstromInvasion
{
    BOSS_CORRUPTED_GRANITE = 0,
    BOSS_UNKNOWN_ENTITY,
    BOSS_SIR_DUKE_IRO,

    // Npcs
    SirDukeIroEntry = 700112,
    MawswarnTormenter = 700111,
    MawswarnCaster = 700110,

    // Conversations
    ThrallConversationId = 700312,
};

struct npc_custom_thrall_700113 : public ScriptedAI
{
    public:
        npc_custom_thrall_700113(Creature* p_Creature) : ScriptedAI(p_Creature) { }

        void InitializeAI() override
        {
            // EMOTE_STATE_MEDITATE
            //me->AddAura(182726, me); // Injured
            me->SetEmoteState(EMOTE_STATE_MEDITATE);
        }

        void Reset() override
        {
           // me->SetEmoteState(EMOTE_STATE_COWER);
        }
};

struct npc_enormous_devourer_700102 : public ScriptedAI
{
    public:
        npc_enormous_devourer_700102(Creature* p_Creature) : ScriptedAI(p_Creature) { }

        void Reset() override
        {
            DoCastSelf(342538);
        }
};

struct boss_corrupted_granite_elemental_700105 : public BossAI
{
    public:
        boss_corrupted_granite_elemental_700105(Creature* p_Creature) : BossAI(p_Creature, BOSS_CORRUPTED_GRANITE) { }

        void Reset() override
        {
            BossAI::Reset();
        }

        void JustEngagedWith(Unit* p_Who) override
        {
            BossAI::JustEngagedWith(p_Who);
            m_Events.ScheduleEvent(1, 5s, 6s);
            m_Events.ScheduleEvent(2, 10s, 12s);
            m_Events.ScheduleEvent(3, 15s, 15s);
        }

        void UpdateAI(uint32 diff) override
        {
            if (!UpdateVictim())
                return;

            m_Events.Update(diff);

            while (uint32 eventId = m_Events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case 1:
                        DoCastSelf(365214);
                        m_Events.Repeat(10s, 15s);
                        break;
                    case 2:
                        DoCast(316837);
                        m_Events.Repeat(10s, 15s);
                        break;
                    case 3:
                        DoCastVictim(301889);
                        m_Events.Repeat(10s, 15s);
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }

    private:
        EventMap m_Events;
};

struct boss_corrupted_ghost_of_the_primus_700104 : public BossAI
{
    public:
        boss_corrupted_ghost_of_the_primus_700104(Creature* p_Creature) : BossAI(p_Creature, BOSS_UNKNOWN_ENTITY) { }

        void Reset() override
        {
            BossAI::Reset();
            DoCastSelf(367432);
        }

        void JustEngagedWith(Unit* p_Who) override
        {
            BossAI::JustEngagedWith(p_Who);
            me->RemoveAurasDueToSpell(367432);
            m_Events.ScheduleEvent(1, 5s, 6s);
            m_Events.ScheduleEvent(2, 10s, 12s);
            m_Events.ScheduleEvent(3, 15s, 15s);
        }

        void UpdateAI(uint32 diff) override
        {
            if (!UpdateVictim())
                return;

            m_Events.Update(diff);

            while (uint32 eventId = m_Events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case 1:
                        DoCastVictim(365834);
                        m_Events.Repeat(10s, 15s);
                        break;
                    case 2:
                        DoCastVictim(366182);
                        m_Events.Repeat(10s, 15s);
                        break;
                    case 3:
                        DoCastSelf(365168);
                        m_Events.Repeat(10s, 15s);
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }

    private:
        EventMap m_Events;
};

struct npc_sir_duke_iro_700112 : public BossAI
{
    public:
        npc_sir_duke_iro_700112(Creature* p_Creature) : BossAI(p_Creature, BOSS_SIR_DUKE_IRO) { }

        void InitializeAI() override
        {
            me->SetUnitFlag(UnitFlags::UNIT_FLAG_NON_ATTACKABLE);
            me->SetReactState(ReactStates::REACT_PASSIVE);
            DoCastSelf(159965);
            DoCastSelf(355291);
        }

        void Reset() override
        {
            BossAI::Reset();
            DoCast(353760);
        }

        void OnUnitRelocation(Unit* p_Who) override
        {
            if (!p_Who)
                return;

            if (m_DidIntroText)
                return;

            if (p_Who->IsPlayer() && p_Who->GetDistance(me) <= 40.0f && me->IsVisible())
            {
                m_DidIntroText = true;
                Talk(0);
                if (instance)
                    instance->instance->DoOnPlayers([](Player* player)
                {
                    Conversation::CreateConversation(ThrallConversationId, player, *player, player->GetGUID());
                });
            }
        }

        void JustEngagedWith(Unit* p_Who) override
        {
            BossAI::JustEngagedWith(p_Who);
            me->RemoveAurasDueToSpell(353760);
            m_Events.ScheduleEvent(1, 5s, 6s);
            m_Events.ScheduleEvent(2, 25s, 26s);
        }

        bool doneIntro = false;

        void DoAction(int32 action) override
        {
            if (action == 1)
            {
                doneIntro = true;
                me->RemoveAurasDueToSpell(159965);
                me->RemoveAurasDueToSpell(345192);
                me->RemoveUnitFlag(UnitFlags::UNIT_FLAG_NON_ATTACKABLE);
                me->SetReactState(ReactStates::REACT_AGGRESSIVE);
                Talk(1);
            }
        }

        void UpdateAI(uint32 diff) override
        {
            if (!UpdateVictim())
            {
                if (!me->isDead() && !me->IsEngaged() && !doneIntro)
                {
                    if (!me->GetCurrentSpell(CurrentSpellTypes::CURRENT_CHANNELED_SPELL))
                        DoCast(345192); // channel
                }

                return;
            }

            m_Events.Update(diff);

            while (uint32 l_EventId = m_Events.ExecuteEvent())
            {
                switch (l_EventId)
                {
                    case 1:
                        DoCast(240006);
                        m_Events.Repeat(10s, 11s);
                        break;
                    case 2:
                        //DoCastVictim();
                        m_Events.Repeat(30s);
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }

    private:
        EventMap m_Events;
        bool m_DidIntroText = false;
};

class instance_maelstrom_invasion : public InstanceMapScript
{
public:
    instance_maelstrom_invasion() : InstanceMapScript("instance_maelstrom_invasion", 1469) { }

    struct instance_maelstrom_invasion_InstanceMapScript : public CustomInstanceScript
    {
        instance_maelstrom_invasion_InstanceMapScript(InstanceMap* map) : CustomInstanceScript(map)
        {
            // SetHeaders(DataHeader);
            // SetBossNumber(EncounterCount);
            ChestSpawn = { 1161.27, 1052.53, 3.89255, 2.49364 };
            Quad = { 0, 0, -0.947977f, -0.318339f };
        }

        void OnCompletedCriteriaTree(CriteriaTree const* tree) override
        {
            if (InstanceScenario* instanceScenario = instance->GetInstanceScenario())
            {
                if (auto tree2 = sCriteriaMgr->GetCriteriaTree(300200))
                    instanceScenario->IsCompletedCriteriaTree(tree2, nullptr);
            }
        }

        GuidSet mawswarnGuids;

        void OnCreatureCreate(Creature* p_Creature) override
        {
            CustomInstanceScript::OnCreatureCreate(p_Creature);
            switch (p_Creature->GetEntry())
            {
                case SirDukeIroEntry:
                    iroGuid = p_Creature->GetGUID();
                    p_Creature->SetReactState(REACT_PASSIVE);
                    p_Creature->SetVisible(false);
                    break;
                case MawswarnTormenter:
                case MawswarnCaster:
                    mawswarnGuids.insert(p_Creature->GetGUID());
                    p_Creature->SetReactState(REACT_PASSIVE);
                    p_Creature->SetVisible(false);
                    break;
            }
        }

        bool SetBossState(uint32 id, EncounterState state, bool forced) override
        {
            if (id == BOSS_CORRUPTED_GRANITE && state == EncounterState::DONE)
            {
                auto activateCreature([&](Creature* creature, ReactStates react = ReactStates::REACT_AGGRESSIVE)
                {
                    if (creature)
                    {
                        creature->SetReactState(react);
                        creature->SetVisible(true);
                    }
                });

                activateCreature(instance->GetCreature(iroGuid), REACT_PASSIVE);

                for (auto const& guid : mawswarnGuids)
                    activateCreature(instance->GetCreature(guid));
            }

            return CustomInstanceScript::SetBossState(id, state, forced);
        }

        void OnUnitDeath(Unit* p_Unit) override
        {
            InstanceScript::OnUnitDeath(p_Unit);
            if (p_Unit->IsCreature())
            {
                switch (p_Unit->GetEntry())
                {
                    case MawswarnTormenter:
                    case MawswarnCaster:
                        m_Kills++;

                        if (m_Kills == 5)
                        {
                            if (auto l_Iro = p_Unit->GetMap()->GetCreature(iroGuid))
                                if (l_Iro->AI())
                                    l_Iro->AI()->DoAction(1);
                        }
                        break;
                }
            }
        }

        void OnPlayerPositionChange(Player* player) override
        {
            InstanceScript::OnPlayerPositionChange(player);
            if (player->GetPositionZ() <= -6.0f)
            {
                player->EnvironmentalDamage(EnviromentalDamage::DAMAGE_FALL, player->GetMaxHealth());
                if (!player->IsGameMaster())
                    player->Kill(player, player);

                if (auto respawnData = sCustomInstanceRespawn->GetRespawnData(instance->GetId(), m_CheckpointId))
                {
                    player->TeleportTo(WorldLocation(instance->GetId(), respawnData->Pos), 0);
                    player->RemovePlayerFlag(PLAYER_FLAGS_IS_OUT_OF_BOUNDS);
                }
            }
        }

        void SummonChallengeGameObject(bool door) override
        {
            if (door)
            {
                if (auto go = instance->SummonGameObject(MYTHIC_DOOR_9, { 825.677f, 1030.75f, 48.3032f, 1.47262f }, {}, 0))
                {
                    go->SetGoState(GOState::GO_STATE_READY);
                    go->SetFlag(GameObjectFlags::GO_FLAG_NOT_SELECTABLE);
                }
            }
        }

        private:
            uint32 m_Kills = 0;
            ObjectGuid iroGuid;
    };

    InstanceScript* GetInstanceScript(InstanceMap* map) const override
    {
        return new instance_maelstrom_invasion_InstanceMapScript(map);
    }
};

class maelstrom_dungeon_player_script : public PlayerScript
{
    public:
        maelstrom_dungeon_player_script() : PlayerScript("maelstrom_dungeon_player_script") { }

        void OnQuestStatusChange(Player* player, uint32 questId) override
        {
            if (player->GetMapId() != 1469)
                return;

            switch (questId)
            {
                case 700008: // maeslstrom invasion
                {

                    auto status = player->GetQuestStatus(questId);

                    if (status == QUEST_STATUS_REWARDED)
                    {
                     //   player->AddQuestAndCheckCompletion(sObjectMgr->GetQuestTemplate(700009), player);
                        player->AddQuestAndCheckCompletion(sObjectMgr->GetQuestTemplate(700011), player);
                        player->PlayerTalkClass->SendQuestGiverQuestDetails(sObjectMgr->GetQuestTemplate(700011), player->GetGUID(), true, true);
                    }

                    break;

                }
            }
        }
};

void AddSC_MaelstromDungeon()
{
    RegisterCreatureAI(npc_custom_thrall_700113);
    RegisterCreatureAI(npc_enormous_devourer_700102);
    RegisterCreatureAI(boss_corrupted_granite_elemental_700105);
    RegisterCreatureAI(boss_corrupted_ghost_of_the_primus_700104);
    RegisterCreatureAI(npc_sir_duke_iro_700112);
    new instance_maelstrom_invasion();
    new maelstrom_dungeon_player_script();
}
