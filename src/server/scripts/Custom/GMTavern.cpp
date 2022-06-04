#include "ScriptMgr.h"

struct npc_gm_tailor : ScriptedAI
{
public:
    npc_gm_tailor(Creature* creature) : ScriptedAI(creature) {}

    bool OnGossipHello(Player* player) override
    {
        ClearGossipMenuFor(player);

        AddGossipItemFor(player, GossipOptionIcon::None, "Give me a set of GM clothes.", 0, 1);

        SendGossipMenuFor(player, 802000, me);

        return true;
    }

    bool OnGossipSelect(Player* player, uint32 menuid, uint32 gossipid) override
    {
        uint32 actionid = player->PlayerTalkClass->GetGossipOptionAction(gossipid);

        CloseGossipMenuFor(player);
        if (actionid == 1)
        {
            player->AddItem(2586, 1);
            player->AddItem(11508, 1);
            player->AddItem(12064, 1);
        }

        return true;
    }
};

void AddSC_GMTavern()
{
    RegisterCreatureAI(npc_gm_tailor);
}
