#include "ScriptMgr.h"
#include "Creature.h"
#include "ScriptedCreature.h"
#include "../CustomInstanceScript.h";

struct npc_custom_thrall_700113 : public ScriptedAI
{
    public:
        npc_custom_thrall_700113(Creature* p_Creature) : ScriptedAI(p_Creature) { }

        void Reset() override
        {
            me->SetEmoteState(EMOTE_STATE_READY1H);
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

struct boss_corrupted_granite_elemental_700105 : public ScriptedAI
{
    public:
        boss_corrupted_granite_elemental_700105(Creature* p_Creature) : ScriptedAI(p_Creature) { }

        void Reset() override
        {

        }

        void JustEngagedWith(Unit* /*p_Who*/) override
        {
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

struct boss_corrupted_ghost_of_the_primus_700104 : public ScriptedAI
{
    public:
        boss_corrupted_ghost_of_the_primus_700104(Creature* p_Creature) : ScriptedAI(p_Creature) { }

        void Reset() override
        {
            DoCastSelf(367432);
        }

        void JustEngagedWith(Unit* /*p_Who*/) override
        {
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

struct npc_sir_duke_iro_700112 : public ScriptedAI
{
    public:
        npc_sir_duke_iro_700112(Creature* p_Creature) : ScriptedAI(p_Creature) { }

        void InitializeAI() override
        {
            me->SetUnitFlags(UnitFlags::UNIT_FLAG_NON_ATTACKABLE);
            me->SetReactState(ReactStates::REACT_PASSIVE);
        }

        void Reset() override
        {
            DoCast(353760);
        }

        void MoveInLineOfSight(Unit* p_Who) override
        {
            if (!p_Who)
                return;

            if (m_DidIntroText)
                return;

            if (p_Who->GetDistance(me) <= 20.0f)
            {
                m_DidIntroText = true;
                Talk(0);
            }
        }

        void JustEngagedWith(Unit* /*p_Who*/) override
        {
            me->RemoveAurasDueToSpell(353760);
            m_Events.ScheduleEvent(1, 5s, 6s);
            m_Events.ScheduleEvent(2, 25s, 26s);
        }

        void DoAction(int32 action) override
        {
            if (action == 1)
            {
                me->RemoveUnitFlag(UnitFlags::UNIT_FLAG_NON_ATTACKABLE);
                me->SetReactState(ReactStates::REACT_AGGRESSIVE);
                Talk(1);
            }
        }

        void UpdateAI(uint32 diff) override
        {
            if (!UpdateVictim())
                return;

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
        }

        void OnCreatureCreate(Creature* p_Creature) override
        {
            switch (p_Creature->GetEntry())
            {
                case 700112:
                    iroGuid = p_Creature->GetGUID();
                    break;
            }
        }

        void OnUnitDeath(Unit* p_Unit) override
        {
            if (p_Unit->IsCreature())
            {
                switch (p_Unit->GetEntry())
                {
                    case 700111:
                    case 700110:
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

        private:
            uint32 m_Kills = 0;
            ObjectGuid iroGuid;
    };

    InstanceScript* GetInstanceScript(InstanceMap* map) const override
    {
        return new instance_maelstrom_invasion_InstanceMapScript(map);
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
}
