#include "ScriptMgr.h"
#include "ScriptedCreature.h"
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

        AddGossipItemFor(player, GossipOptionNpc::None, "I need a set of GM clothes.", 0, 1);

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

        AddGossipItemFor(player, GossipOptionNpc::None, "I want to join the GM Guild.", 0, 1, "Warning! This will remove you from any existing guilds!", 0, false);
        AddGossipItemFor(player, GossipOptionNpc::None, "Set my hearthstone here.", 0, 2);
        AddGossipItemFor(player, GossipOptionNpc::None, "Teleport me to the mall.", 0, 3);

        SendGossipMenuFor(player, 802001, me);

        return true;
    }

    bool OnGossipSelect(Player* player, uint32 menuid, uint32 gossipid) override
    {
        uint32 actionid = player->PlayerTalkClass->GetGossipOptionAction(gossipid);

        CloseGossipMenuFor(player);

        if (actionid == 1)
        {
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
        }

        if (actionid == 2)
        {
            GameTele const* tele = sObjectMgr->GetGameTele(1905);
            if (tele)
                player->SetHomebind(WorldLocation(tele->mapId, tele->position_x, tele->position_y, tele->position_z, tele->orientation), 10473);
            ChatHandler(player).SendSysMessage("Your hearthstone is now set to the GM Tavern.");
        }

        if (actionid == 3)
        {
            GameTele const* tele = sObjectMgr->GetGameTele(1779);
            if (tele)
                player->TeleportTo(tele->mapId, tele->position_x, tele->position_y, tele->position_z, tele->orientation);
        }


        return true;
    }
};

void AddSC_GMTavern()
{
    RegisterCreatureAI(npc_gm_tailor);
    RegisterCreatureAI(npc_gm_commander);

}
