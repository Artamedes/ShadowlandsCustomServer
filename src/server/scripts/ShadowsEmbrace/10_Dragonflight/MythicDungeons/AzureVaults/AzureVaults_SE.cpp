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

                player->GetMotionMaster()->MoveSmoothPath2(1, BookOfTranslocationPathOne, BookOfTranslocationPathOneSize::value, false, true, true, true, 22.0f)->_callbacks.push([player]()
                {
                    player->RemoveAurasDueToSpell(eBookOfTranslocation::Translocate);
                });
            };

            SendGossipMenuFor(player, 590026, me); ///< Verified 48069
            return true;
        }
};

Position const BookOfTranslocationPathTwo[9] =
{
    { -5337.512f, 1067.356f, 508.03104f },
    { -5337.4165f, 1087.4584f, 488.28918f },
    { -5319.3403f, 1089.3959f, 467.1379f },
    { -5300.6685f, 1069.1389f, 448.19083f },
    { -5310.837f, 1042.0209f, 441.6145f },
    { -5351.0557f, 1030.3785f, 437.05338f },
    { -5377.0747f, 1059.2344f, 435.65186f },
    { -5363.7954f, 1107.0173f, 428.52472f },
    { -5345.809f, 1120.3125f, 425.16507f }
};

using BookOfTranslocationPathTwoSize = std::extent<decltype(BookOfTranslocationPathTwo)>;

struct npc_se_book_of_translocation_194712 : public ScriptedAI
{
    public:
        npc_se_book_of_translocation_194712(Creature* creature) : ScriptedAI(creature) { }

        enum eBookOfTranslocation
        {
            Translocate = 384347, ///< Already has interrupt flags if they logout while on path.
        };

        bool OnGossipHello(Player* player) override
        {
            ClearGossipMenuFor(player);

            AddGossipItemFor(player, GossipOptionNpc::None, "Proceed onward.")->Callback = [player](std::string_view /*callback*/)
            {
                player->CastSpell(player, eBookOfTranslocation::Translocate, true);

                player->GetMotionMaster()->MoveSmoothPath2(1, BookOfTranslocationPathTwo, BookOfTranslocationPathTwoSize::value, false, true, true, true, 22.0f)->_callbacks.push([player]()
                {
                    player->RemoveAurasDueToSpell(eBookOfTranslocation::Translocate);
                });
            };

            SendGossipMenuFor(player, 590027, me); ///< Verified 48069
            return true;
        }
};

Position const BookOfTranslocationPathThree[4] =
{
    { -5337.212f, 1009.4636f, 430.3666f },
    { -5344.2397f, 985.07294f, 437.19678f },
    { -5344.9204f, 964.0278f, 435.74966f },
    { -5337.5415f, 947.16144f, 430.3666f }
};

using BookOfTranslocationPathThreeSize = std::extent<decltype(BookOfTranslocationPathThree)>;

struct npc_se_book_of_translocation_194713 : public ScriptedAI
{
    public:
        npc_se_book_of_translocation_194713(Creature* creature) : ScriptedAI(creature) { }

        enum eBookOfTranslocation
        {
            Translocate = 384348, ///< Already has interrupt flags if they logout while on path.
        };

        bool OnGossipHello(Player* player) override
        {
            ClearGossipMenuFor(player);

            AddGossipItemFor(player, GossipOptionNpc::None, "Proceed onward.")->Callback = [player](std::string_view /*callback*/)
            {
                player->CastSpell(player, eBookOfTranslocation::Translocate, true);

                player->GetMotionMaster()->MoveSmoothPath2(1, BookOfTranslocationPathThree, BookOfTranslocationPathThreeSize::value, false, true, true, true, 22.0f)->_callbacks.push([player]()
                {
                    player->RemoveAurasDueToSpell(eBookOfTranslocation::Translocate);
                });
            };

            SendGossipMenuFor(player, 590028, me); ///< Verified 48069
            return true;
        }
};

Position const BookOfTranslocationPathFour[4] =
{
    { -5413.002f, 991.00696f, 346.43228f },
    { -5405.328f, 1008.5521f, 351.44327f },
    { -5383.4272f, 1032.1459f, 348.3228f },
    { -5366.299f, 1040.7935f, 341.58167f }
};

using BookOfTranslocationPathFourSize = std::extent<decltype(BookOfTranslocationPathFour)>;

struct npc_se_book_of_translocation_194714 : public ScriptedAI
{
    public:
        npc_se_book_of_translocation_194714(Creature* creature) : ScriptedAI(creature) { }

        enum eBookOfTranslocation
        {
            Translocate = 384349, ///< Already has interrupt flags if they logout while on path.
        };

        bool OnGossipHello(Player* player) override
        {
            ClearGossipMenuFor(player);

            AddGossipItemFor(player, GossipOptionNpc::None, "Proceed onward.")->Callback = [player](std::string_view /*callback*/)
            {
                player->CastSpell(player, eBookOfTranslocation::Translocate, true);

                player->GetMotionMaster()->MoveSmoothPath2(1, BookOfTranslocationPathFour, BookOfTranslocationPathFourSize::value, false, true, true, true, 22.0f)->_callbacks.push([player]()
                {
                    player->RemoveAurasDueToSpell(eBookOfTranslocation::Translocate);
                });
            };

            SendGossipMenuFor(player, 590029, me); ///< Verified 48069
            return true;
        }
};


Position const BookOfTranslocationPathFive[13] =
{
    { -5336.8003f, 1068.0348f, 346.8186f },
    { -5345.0747f, 1077.6216f, 322.03543f },
    { -5345.3975f, 1047.8281f, 263.0053f },
    { -5327.186f, 1048.0868f, 223.00484f },
    { -5314.4307f, 1063.5504f, 188.28706f },
    { -5314.915f, 1086.5173f, 176.62357f },
    { -5327.868f, 1112.7517f, 175.95555f },
    { -5357.9497f, 1122.1423f, 175.95555f },
    { -5388.0537f, 1098.1841f, 175.95555f },
    { -5393.3613f, 1043.4497f, 175.95555f },
    { -5355.752f, 1009.5226f, 175.95555f },
    { -5321.3335f, 1022.658f, 162.84392f },
    { -5329.5415f, 1044.618f, 160.78316f }
};

using BookOfTranslocationPathFiveSize = std::extent<decltype(BookOfTranslocationPathFive)>;

struct npc_se_book_of_translocation_194715 : public ScriptedAI
{
    public:
        npc_se_book_of_translocation_194715(Creature* creature) : ScriptedAI(creature) { }

        enum eBookOfTranslocation
        {
            Translocate = 384350, ///< Already has interrupt flags if they logout while on path.
        };

        bool OnGossipHello(Player* player) override
        {
            ClearGossipMenuFor(player);

            AddGossipItemFor(player, GossipOptionNpc::None, "Proceed onward.")->Callback = [player](std::string_view /*callback*/)
            {
                player->CastSpell(player, eBookOfTranslocation::Translocate, true);

                player->GetMotionMaster()->MoveSmoothPath2(1, BookOfTranslocationPathFive, BookOfTranslocationPathFiveSize::value, false, true, true, true, 22.0f)->_callbacks.push([player]()
                {
                    player->RemoveAurasDueToSpell(eBookOfTranslocation::Translocate);
                });
            };

            SendGossipMenuFor(player, 590030, me); ///< Verified 48069
            return true;
        }
};

void AddSC_AzureVaults_SE()
{
    RegisterCreatureAI(npc_se_sindragosa_197081);
    RegisterCreatureAI(npc_se_polymorphic_rune_195638);
    RegisterCreatureAI(npc_se_book_of_translocation_194602);
    RegisterCreatureAI(npc_se_book_of_translocation_194712);
    RegisterCreatureAI(npc_se_book_of_translocation_194713);
    RegisterCreatureAI(npc_se_book_of_translocation_194714);
    RegisterCreatureAI(npc_se_book_of_translocation_194715);
}
