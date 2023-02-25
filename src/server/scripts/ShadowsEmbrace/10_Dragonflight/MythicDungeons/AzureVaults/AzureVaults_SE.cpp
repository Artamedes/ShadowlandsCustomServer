/// Copyright 2022-2023 Shadows Embrace
/// All Rights Reserved.
/// You may not share or personally use this code without explicit written permission
/// @author: Artamedes

#include "ScriptMgr.h"
#include "Player.h"
#include "ScriptedCreature.h"

/// NPC: Sindragosa - 197081
struct npc_se_sindragosa_197081 : public ScriptedAI
{
    public:
        npc_se_sindragosa_197081(Creature* creature) : ScriptedAI(creature) { }

        bool OnGossipHello(Player* player) override
        {
            ClearGossipMenuFor(player);

            AddGossipItemFor(player, GossipOptionNpc::None, "Take me to the Arcane Conservatory.");

            SendGossipMenuFor(player, 590032, me); ///< Sindragosa TextID - Verified 48069
        }
};

void AddSC_AzureVaults_SE()
{
    RegisterCreatureAI(npc_se_sindragosa_197081);
}
