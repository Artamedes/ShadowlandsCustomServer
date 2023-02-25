/// Copyright 2022-2023 Shadows Embrace
/// All Rights Reserved.
/// You may not share or personally use this code without explicit written permission
/// @author: Artamedes

#include "ScriptMgr.h"
#include "Player.h"
#include "ScriptedCreature.h"
#include "MotionMaster.h"
#include "GenericMovementGenerator.h"

/// NPC: Sindragosa - 197081
struct npc_se_sindragosa_197081 : public ScriptedAI
{
    public:
        npc_se_sindragosa_197081(Creature* creature) : ScriptedAI(creature) { }

        enum eSindragosa
        {
            PortalToAzureBoss01 = 393902,
            PortalToAzureBoss02 = 389770,
            PortalToAzureBoss03 = 389773,
        };

        bool OnGossipHello(Player* player) override
        {
            ClearGossipMenuFor(player);

            AddGossipItemFor(player, GossipOptionNpc::None, "Take me to the Arcane Conservatory.")->Callback = [player](std::string_view /*callback*/)
            {
                player->CastSpell(player, eSindragosa::PortalToAzureBoss01, true);
                CloseGossipMenuFor(player);
            };
            AddGossipItemFor(player, GossipOptionNpc::None, "Take me to the Mausoleum of Legends.")->Callback = [player](std::string_view /*callback*/)
            {
                player->CastSpell(player, eSindragosa::PortalToAzureBoss02, true);
                CloseGossipMenuFor(player);
            };
            AddGossipItemFor(player, GossipOptionNpc::None, "Take me to the Crystal Chambers.")->Callback = [player](std::string_view /*callback*/)
            {
                player->CastSpell(player, eSindragosa::PortalToAzureBoss03, true);
                CloseGossipMenuFor(player);
            };

            SendGossipMenuFor(player, 590032, me); ///< Sindragosa TextID - Verified 48069
            return true;
        }
};

/// NPC - Polymorphic Rune - 195638
struct npc_se_polymorphic_rune_195638 : public ScriptedAI
{
    public:
        npc_se_polymorphic_rune_195638(Creature* creature) : ScriptedAI(creature)
        {
            me->SetReactState(REACT_PASSIVE);
            me->SetUnitFlag(UNIT_FLAG_NON_ATTACKABLE);
        }

        enum ePolymorphicRune
        {
            Polymorphed = 386368,
        };

        void UpdateAI(uint32 /*diff*/) override
        {
            if (_didPolymorph && !me->HasUnitState(UNIT_STATE_CASTING))
            {
                me->DespawnOrUnsummon();
            }
        }

        void OnUnitRelocation(Unit* who) override
        {
            if (_didPolymorph)
                return;

            if (!who->IsPlayer())
                return;

            if (who->GetDistance2d(me) > 0.66f)
                return;

            me->CastSpell(me, Polymorphed);
            _didPolymorph = true;
        }

        bool _didPolymorph = false;
};

Position const BookOfTranslocationPathOne[4] =
{
    { -5303.6753f, 1191.0173f, 515.0979f },
    { -5311.243f, 1167.6875f, 522.0624f },
    { -5312.632f, 1139.7882f, 519.5894f },
    { -5312.578f, 1119.7812f, 509.12387f },
};

using BookOfTranslocationPathOneSize = std::extent<decltype(BookOfTranslocationPathOne)>;

// NPC - Book of Translocation - 194602
struct npc_se_book_of_translocation_194602 : public ScriptedAI
{
    public:
        npc_se_book_of_translocation_194602(Creature* creature) : ScriptedAI(creature) { }

        enum eBookOfTranslocation
        {
            Translocate = 384106, ///< Already has interrupt flags if they logout while on path.
        };

        bool OnGossipHello(Player* player) override
        {
            ClearGossipMenuFor(player);

            AddGossipItemFor(player, GossipOptionNpc::None, "Proceed onward.")->Callback = [player](std::string_view /*callback*/)
            {
                // cast 384106

                // (MovementMonsterSpline)(MovementSpline)Flags: 6294016 (Flying, Catmullrom, CanSwim, UncompressedPath)

                //Points : X : -5303.6753f, 1191.0173f, 515.0979 f
                //Points : X : -5311.243 f, 1167.6875f, 522.0624 f
                //Points : X : -5312.632 f, 1139.7882f, 519.5894 f
                //Points : X : -5312.578 f, 1119.7812f, 509.12387f

                player->CastSpell(player, eBookOfTranslocation::Translocate, true);

                player->GetMotionMaster()->MoveSmoothPath2(1, BookOfTranslocationPathOne, BookOfTranslocationPathOneSize::value, false, true, true, true)->_callbacks.push([player]()
                {
                    player->RemoveAurasDueToSpell(eBookOfTranslocation::Translocate);
                });
            };

            SendGossipMenuFor(player, 590026, me); ///< Verified 48069
            return true;
        }
};

void AddSC_AzureVaults_SE()
{
    RegisterCreatureAI(npc_se_sindragosa_197081);
    RegisterCreatureAI(npc_se_polymorphic_rune_195638);
    RegisterCreatureAI(npc_se_book_of_translocation_194602);
}
