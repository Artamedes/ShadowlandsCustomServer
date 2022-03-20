#include "ScriptMgr.h"
#include "Creature.h"
#include "ScriptedCreature.h"

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
            DoCastSelf(364949);
        }

        void JustEngagedWith(Unit* /*p_Who*/) override
        {
            me->RemoveAurasDueToSpell(364949);
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
                        DoCastVictim(361613);
                        m_Events.Repeat(10s, 15s);
                        break;
                    case 2:
                        DoCastVictim(350588);
                        m_Events.Repeat(10s, 15s);
                        break;
                    case 3:
                        DoCastSelf(347064);
                        m_Events.Repeat(10s, 15s);
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }

    private:
        EventMap m_Events;
};

void AddSC_MaelstromDungeon()
{
    RegisterCreatureAI(npc_custom_thrall_700113);
    RegisterCreatureAI(npc_enormous_devourer_700102);
    RegisterCreatureAI(boss_corrupted_granite_elemental_700105);
    RegisterCreatureAI(boss_corrupted_ghost_of_the_primus_700104);
}
