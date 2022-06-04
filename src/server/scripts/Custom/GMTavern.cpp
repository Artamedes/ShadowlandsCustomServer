#include "ScriptMgr.h"
#include "WorldSession.h"
#include "Guild.h"
#include "GuildMgr.h"
#include "Chat.h"

struct npc_gm_tailor : ScriptedAI
{
public:
    npc_gm_tailor(Creature* creature) : ScriptedAI(creature) {}

    bool OnGossipHello(Player* player) override
    {
        ClearGossipMenuFor(player);

        AddGossipItemFor(player, GossipOptionIcon::None, "I need a set of GM clothes.", 0, 1);

        SendGossipMenuFor(player, 802000, me);

        return true;
    }

    bool OnGossipSelect(Player* player, uint32 menuid, uint32 gossipid) override
    {
        uint32 actionid = player->PlayerTalkClass->GetGossipOptionAction(gossipid);

        CloseGossipMenuFor(player);
        if (actionid == 1 && player->GetSession()->GetSecurity()>=SEC_GAMEMASTER)
        {
            player->AddItem(2586, 1);
            player->AddItem(11508, 1);
            player->AddItem(12064, 1);

        ChatHandler(player).SendSysMessage("Do not give these robes to ANY non-GM players. This WILL result in a loss of GM privileges, and possibly a ban.");
        }

        return true;
    }
};

struct npc_gm_commander : ScriptedAI
{
public:
    npc_gm_commander(Creature* creature) : ScriptedAI(creature) {}

    bool OnGossipHello(Player* player) override
    {
        ClearGossipMenuFor(player);

        AddGossipItemFor(player, GossipOptionIcon::None, "I want to join the GM Guild.", 0, 1, "Warning! This will remove you from any existing guilds!", 0, false);

        SendGossipMenuFor(player, 802001, me);

        return true;
    }

    bool OnGossipSelect(Player* player, uint32 menuid, uint32 gossipid) override
    {
        uint32 actionid = player->PlayerTalkClass->GetGossipOptionAction(gossipid);

        CloseGossipMenuFor(player);

        if (player->GetSession()->GetSecurity() < SEC_GAMEMASTER)
        {
            ChatHandler(player).SendSysMessage("You are not eligible to join this guild!");
            return true;
        }

        if (Guild* guild = player->GetGuild())
        {
            if (guild->GetName() == "GM")
            {
                ChatHandler(player).SendSysMessage("You are already in the GM Guild!");
                return true;
            }

            guild->HandleLeaveMember(player->GetSession());
        }

        Guild* gmGuild = sGuildMgr->GetGuildByName("GM");
        if (gmGuild)
            gmGuild->HandleAcceptMember(player->GetSession());

        return true;
    }
};

void AddSC_GMTavern()
{
    RegisterCreatureAI(npc_gm_tailor);
    RegisterCreatureAI(npc_gm_commander);

}
