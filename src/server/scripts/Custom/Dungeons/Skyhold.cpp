#include "ScriptMgr.h"
#include "../CustomInstanceScript.h"
#include "ScriptedGossip.h"

class instance_skyhold : public InstanceMapScript
{
    public:
        instance_skyhold() : InstanceMapScript("instance_skyhold", 2472) { }

        struct instance_skyhold_InstanceMapScript : public CustomInstanceScript
        {
            public:
                instance_skyhold_InstanceMapScript(InstanceMap* map) : CustomInstanceScript(map)
                {
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

        bool OnGossipHello(Player* player) override
        {
            ClearGossipMenuFor(player);
            AddGossipItemFor(player, GossipOptionIcon::None, "Wreak havoc", 0, 1);
            SendGossipMenuFor(player, me->GetEntry(), me);
            return true;
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
                m_Flying = false;
                Talk(1);
                me->RemoveAurasDueToSpell(359361); // Banshee form
                me->SetObjectScale(2.0f);
                scheduler.Schedule(100ms, [this](TaskContext context)
                {
                    me->SetFacingTo(-0.034910f);
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


void AddSC_Skyhold()
{
    new instance_skyhold();
    RegisterCreatureAI(npc_skyhold_sylvanas);
}
