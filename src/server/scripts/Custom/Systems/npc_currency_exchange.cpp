#include "Player.h"
#include "GossipDef.h"
#include "ScriptedGossip.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"

struct npc_currency_exchange : public ScriptedAI
{
    public:
        npc_currency_exchange(Creature* p_Creature) : ScriptedAI(p_Creature) { }

        bool OnGossipHello(Player* p_Player) override
        {
            ClearGossipMenuFor(p_Player);
            p_Player->PrepareQuestMenu(me->GetGUID());
            AddGossipItemFor(p_Player, GossipOptionNpc::None, "|TInterface\\ICONS\\inv_inscription_talenttome01.BLP:30:30:-28:0|tExchange 1.", 0, 1, "", 0, true);
            AddGossipItemFor(p_Player, GossipOptionNpc::None, "|TInterface\\ICONS\\inv_inscription_talenttome01.BLP:30:30:-28:0|tExchange 2.", 0, 1, "", 0, true);
            AddGossipItemFor(p_Player, GossipOptionNpc::None, "|TInterface\\ICONS\\inv_inscription_talenttome01.BLP:30:30:-28:0|tExchange 3.", 0, 1, "", 0, true);
            SendGossipMenuFor(p_Player, me->GetEntry(), me);
            return true;
        }

        bool OnGossipSelect(Player* p_Player, uint32 p_MenuId, uint32 p_GossipId) override
        {
            uint32 l_ActionId = p_Player->PlayerTalkClass->GetGossipOptionAction(p_GossipId);
            CloseGossipMenuFor(p_Player);
            switch (l_ActionId)
            {
            }
            return true;
        }

        bool OnGossipSelectCode(Player* p_Player, uint32 p_MenuId, uint32 p_GossipId, char const* p_Code) override
        {
            uint32 l_ActionId = p_Player->PlayerTalkClass->GetGossipOptionAction(p_GossipId);
            CloseGossipMenuFor(p_Player);
            switch (l_ActionId)
            {
            }
            return true;
        }
};

void AddSC_npc_currency_exchange()
{
    RegisterCreatureAI(npc_currency_exchange);
}
