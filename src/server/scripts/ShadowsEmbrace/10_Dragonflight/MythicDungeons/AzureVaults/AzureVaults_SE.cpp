/// Copyright 2022-2023 Shadows Embrace
/// All Rights Reserved.
/// You may not share or personally use this code without explicit written permission
/// @author: Artamedes

#include "ScriptMgr.h"
#include "Player.h"
#include "ScriptedCreature.h"
#include "MotionMaster.h"
#include "GenericMovementGenerator.h"
#include "AreaTrigger.h"
#include "AreaTriggerAI.h"
#include "AzureVaults_SE.h"

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

            auto instance = me->GetInstanceScript();

            bool leymorDone = instance && instance->GetBossState(DATA_LEYMOR) == DONE;
            bool azurebladeDone = instance && instance->GetBossState(DATA_AZUREBLADE) == DONE;
            bool telashDone = instance && instance->GetBossState(DATA_TELASH_GREYWING) == DONE;

            if (leymorDone || player->IsGameMaster())
            {
                AddGossipItemFor(player, GossipOptionNpc::None, "Take me to the Arcane Conservatory.")->Callback = [player](std::string_view /*callback*/)
                {
                    player->CastSpell(player, eSindragosa::PortalToAzureBoss01, true);
                    CloseGossipMenuFor(player);
                };
            }
            if (azurebladeDone || player->IsGameMaster())
            {
                AddGossipItemFor(player, GossipOptionNpc::None, "Take me to the Mausoleum of Legends.")->Callback = [player](std::string_view /*callback*/)
                {
                    player->CastSpell(player, eSindragosa::PortalToAzureBoss02, true);
                    CloseGossipMenuFor(player);
                };
            }
            if (telashDone || player->IsGameMaster())
            {
                AddGossipItemFor(player, GossipOptionNpc::None, "Take me to the Crystal Chambers.")->Callback = [player](std::string_view /*callback*/)
                {
                    player->CastSpell(player, eSindragosa::PortalToAzureBoss03, true);
                    CloseGossipMenuFor(player);
                };
            }

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

        // @todo - handle it by 26445  areatrigger
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

/// Arcane Elemental - 186741
struct npc_se_arcane_elemental_186741 : public ScriptedAI
{
    public:
        npc_se_arcane_elemental_186741(Creature* creature) : ScriptedAI(creature) { }

        enum eArcaneElementals
        {
            ArcaneBolt = 371306,
            WakingBane = 386546,
        };

        void Reset() override
        {
            scheduler.CancelAll();
        }

        void JustEngagedWith(Unit* /*who*/) override
        {
            scheduler.Schedule(Seconds(1), [this](TaskContext context)
            {
                DoCastVictim(ArcaneBolt);

                context.Repeat(5s);
            });

            scheduler.Schedule(Seconds(3), [this](TaskContext context)
            {
                if (me->HasUnitState(UNIT_STATE_CASTING))
                {
                    context.Repeat(1ms);
                    return;
                }

                DoCastRandom(WakingBane, 40.0f);

                context.Repeat(20s);
            });
        }

        void UpdateAI(uint32 diff) override
        {
            if (!UpdateVictim())
                return;

            scheduler.Update(diff);

            DoMeleeAttackIfReady();
        }
};

/// Rune Seal Keeper - 187155
struct npc_se_rune_seal_keeper_187155 : public ScriptedAI
{
    public:
        npc_se_rune_seal_keeper_187155(Creature* creature) : ScriptedAI(creature) { }

        enum eRuneSealKeeper
        {
            CondensedFrost = 377503,
            IcyBindings    = 377488,
        };

        void Reset() override
        {
            scheduler.CancelAll();
        }

        void JustEngagedWith(Unit* /*who*/) override
        {
            scheduler.Schedule(3s, 5s, [this](TaskContext context)
            {
                DoCastVictim(CondensedFrost);
                context.Repeat(15s);
            });
            scheduler.Schedule(8s, 15s, [this](TaskContext context)
            {
                DoCastVictim(IcyBindings);
                context.Repeat(15s);
            });
        }

        void UpdateAI(uint32 diff) override
        {
            if (!UpdateVictim())
                return;

            if (!me->HasUnitState(UNIT_STATE_CASTING))
                scheduler.Update(diff);

            DoMeleeAttackIfReady();
        }
};

/// Astral Attendent - 189555
struct npc_se_astral_attendant_189555 : public ScriptedAI
{
    public:
        npc_se_astral_attendant_189555(Creature* creature) : ScriptedAI(creature) { }

        enum eSpells
        {
            UnstablePower   = 374874,
        };

        void Reset() override
        {
            scheduler.CancelAll();
        }

        void JustEngagedWith(Unit* /*who*/) override
        {
            scheduler.Schedule(3s, 5s, [this](TaskContext context)
            {
                DoCastRandom(UnstablePower, 40.0f);
                context.Repeat(7s);
            });
        }

        void UpdateAI(uint32 diff) override
        {
            if (!UpdateVictim())
                return;

            if (!me->HasUnitState(UNIT_STATE_CASTING))
                scheduler.Update(diff);

            DoMeleeAttackIfReady();
        }
};

/// Arcane Construct - 186740
struct npc_se_arcane_construct_186740 : public ScriptedAI
{
    public:
        npc_se_arcane_construct_186740(Creature* creature) : ScriptedAI(creature) { }

        enum eArcaneConstruct
        {
            ConjuredBarrier = 387122,
            ArcaneBash      = 387067,
        };

        void Reset() override
        {
            scheduler.CancelAll();
        }

        void JustEngagedWith(Unit* /*who*/) override
        {
            scheduler.Schedule(3s, 5s, [this](TaskContext context)
            {
                DoCastSelf(ConjuredBarrier);
                context.Repeat(24s);
            });
            scheduler.Schedule(3s, 5s, [this](TaskContext context)
            {
                DoCastVictim(ArcaneBash);
                context.Repeat(16s);
            });
        }

        void UpdateAI(uint32 diff) override
        {
            if (!UpdateVictim())
                return;

            if (!me->HasUnitState(UNIT_STATE_CASTING))
                scheduler.Update(diff);

            DoMeleeAttackIfReady();
        }
};

/// Crystal Fury - 196116, 187160
struct npc_se_crystal_fury_196116 : public ScriptedAI
{
    public:
        npc_se_crystal_fury_196116(Creature* creature) : ScriptedAI(creature) { }

        enum eCrystalFury
        {
            ArcaneFury     = 389686,
            PiercingShards = 370764,
        };

        void Reset() override
        {
            scheduler.CancelAll();
        }

        void JustEngagedWith(Unit* /*who*/) override
        {
            scheduler.Schedule(3s, 5s, [this](TaskContext context)
            {
                DoCastSelf(ArcaneFury);
                context.Repeat(24s);
            });
            scheduler.Schedule(3s, 5s, [this](TaskContext context)
            {
                DoCastVictim(PiercingShards);
                context.Repeat(16s);
            });
        }

        void UpdateAI(uint32 diff) override
        {
            if (!UpdateVictim())
                return;

            if (!me->HasUnitState(UNIT_STATE_CASTING))
                scheduler.Update(diff);

            DoMeleeAttackIfReady();
        }
};

/// Crystal Thrasher - 196117, 187139
struct npc_se_crystal_thrasher_196117 : public ScriptedAI
{
    public:
        npc_se_crystal_thrasher_196117(Creature* creature) : ScriptedAI(creature) { }
        
        enum eCrystalFury
        {
            CrystallineRupture = 370766,
        };

        void Reset() override
        {
            scheduler.CancelAll();
        }

        void JustEngagedWith(Unit* /*who*/) override
        {
            scheduler.Schedule(10s, [this](TaskContext context)
            {
                DoCastSelf(CrystallineRupture);
                context.Repeat(24s);
            });
        }

        void UpdateAI(uint32 diff) override
        {
            if (!UpdateVictim())
                return;

            if (!me->HasUnitState(UNIT_STATE_CASTING))
                scheduler.Update(diff);

            DoMeleeAttackIfReady();
        }
};

/// Unstable Curator - 187154
struct npc_se_unstable_curator_187154 : public ScriptedAI
{
    public:
        npc_se_unstable_curator_187154(Creature* creature) : ScriptedAI(creature) { }

        enum eSpells
        {
            HeavyTome = 389804,
        };

        void Reset() override
        {
            scheduler.CancelAll();
        }

        void JustEngagedWith(Unit* /*who*/) override
        {
            scheduler.Schedule(5s, 7s, [this](TaskContext context)
            {
                DoCastVictim(HeavyTome);
                context.Repeat(14s);
            });
        }

        void UpdateAI(uint32 diff) override
        {
            if (!UpdateVictim())
                return;

            if (!me->HasUnitState(UNIT_STATE_CASTING))
                scheduler.Update(diff);

            DoMeleeAttackIfReady();
        }
};

struct npc_se_shrieking_whelp_188100 : public ScriptedAI
{
    public:
        npc_se_shrieking_whelp_188100(Creature* creature) : ScriptedAI(creature) { }

        enum eSpells
        {
            RevealingGazeATAura = 397215,
            Shriek              = 370225,
        };

        void Reset() override
        {
            me->SetReactState(REACT_PASSIVE);
            scheduler.CancelAll();
            _engaged = false;

            scheduler.Schedule(1ms, [this](TaskContext context)
            {
                DoCastSelf(RevealingGazeATAura);
                context.Repeat(15s);
            });
        }

        void JustEngagedWith(Unit* /*who*/) override
        {
            scheduler.CancelAll();
        }

        void UpdateAI(uint32 diff) override
        {
            if (!me->HasUnitState(UNIT_STATE_CASTING))
            {
                scheduler.Update(diff);

                if (_engaged && me->GetReactState() == REACT_PASSIVE)
                {
                    me->SetReactState(REACT_AGGRESSIVE);
                }
            }

            if (!me->IsEngaged())
            {
                // @todo: figure this out
               //if (auto at = me->GetAreaTrigger(RevealingGazeATAura))
               //    at->OverrideRadiusTarget = 1.0f;
            }

            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }

        void OnUnitEnteredMe(Unit* /*who*/)
        {
            scheduler.CancelAll();
            DoZoneInCombat();

            DoCast(Shriek);
            _engaged = true;
        }

    private:
        bool _engaged = false;
};

// 24966, 28911
struct at_revealing_gaze_28931 : public AreaTriggerAI
{
    public:
        at_revealing_gaze_28931(AreaTrigger* at) : AreaTriggerAI(at) { }

        void OnUnitEnter(Unit* who) override
        {
            if (who->IsPlayer())
            {
                if (auto caster = at->GetCaster())
                {
                    if (auto creature = caster->ToCreature())
                    {
                        if (creature->IsAIEnabled())
                        {
                            if (auto ai = creature->AI())
                            {
                                if (auto whelp = CAST_AI(npc_se_shrieking_whelp_188100, ai))
                                {
                                    whelp->OnUnitEnteredMe(who);
                                }
                            }
                        }
                    }
                }
            }
        }
};

/// ID - 370225 Shriek
class spell_shriek_370225 : public SpellScript
{
    PrepareSpellScript(spell_shriek_370225);

    enum eShriek
    {
        NpcWhelping      = 188100,
        AuraReadyDefense = 375407,
    };

    void HandleScriptEffect(SpellEffIndex /*eff*/)
    {
        if (auto caster = GetCaster())
        {
            std::list<Unit*> friendlyTargetsToMe;
            caster->GetFriendlyUnitListInRange(friendlyTargetsToMe, 100.0f, true);

            for (auto unit : friendlyTargetsToMe)
            {
                auto unitCreature = unit->ToCreature();
                if (!unitCreature)
                    continue;
                
                if (unitCreature->GetEntry() == NpcWhelping)
                {
                    if (unitCreature->IsAIEnabled())
                        unitCreature->AI()->DoZoneInCombat();
                    continue;
                }

                if (unitCreature->HasAura(AuraReadyDefense))
                {
                    unitCreature->RemoveAurasDueToSpell(AuraReadyDefense);
                    unitCreature->SetReactState(REACT_PASSIVE);
                    unitCreature->RemoveUnitFlag(UNIT_FLAG_IMMUNE_TO_NPC);
                    unitCreature->RemoveUnitFlag(UNIT_FLAG_UNINTERACTIBLE);

                    unitCreature->GetScheduler().Schedule(1s, [unitCreature](TaskContext /*context*/)
                    {
                        unitCreature->SetReactState(REACT_AGGRESSIVE);
                        if (unitCreature->IsAIEnabled())
                                unitCreature->AI()->DoZoneInCombat();
                    });
                }
            }
        }
    }

    void Register() override
    {
        OnEffectHit += SpellEffectFn(spell_shriek_370225::HandleScriptEffect, EFFECT_0,  SPELL_EFFECT_SCRIPT_EFFECT);
    }
};

struct npc_se_bubbling_sappling_191313 : public ScriptedAI
{
    public:
        npc_se_bubbling_sappling_191313(Creature* creature) : ScriptedAI(creature) { }

        enum eSpells
        {
            SpellSappyBurst = 375591,
        };

        void DamageTaken(Unit* /*done_by*/, uint32& damage, DamageEffectType /*damageType*/, SpellInfo const* /*spellInfo = nullptr*/) override
        {
            if (damage >= me->GetHealth())
            {
                damage = 0;
                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                DoCastSelf(SpellSappyBurst);
            }
        }
};

/// ID - 375591 Sappy Burst
class spell_sappy_burst_375591 : public SpellScript
{
    PrepareSpellScript(spell_sappy_burst_375591);

    void HandleScriptEffect(SpellEffIndex /*eff*/)
    {
        if (auto caster = GetCaster())
            caster->KillSelf();
    }

    void Register() override
    {
        OnEffectHit += SpellEffectFn(spell_sappy_burst_375591::HandleScriptEffect, EFFECT_2, SPELL_EFFECT_SCRIPT_EFFECT);
    }
};

/// 191164, 196115
struct npc_se_arcane_tender_191164 : public ScriptedAI
{
    public:
        npc_se_arcane_tender_191164(Creature* creature) : ScriptedAI(creature) { }

        enum eSpells
        {
            SpellStasisRitual = 375732,
            SpellErraticGrowth = 375596,
            SpellWildEruptionMissle = 375652,
        };

        void Reset() override
        {
            switch (me->GetSpawnId())
            {
                case 9001823:
                case 9001816:
                case 9001856:
                    _isBossChannelMob = true;
                    break;
                default:
                    break;
            }
        }

        void JustEngagedWith(Unit* who) override
        {
            scheduler.CancelAll();
            me->RemoveAurasDueToSpell(SpellStasisRitual);

            scheduler.Schedule(5s, 7s, [this](TaskContext context)
            {
                DoCastRandom(SpellErraticGrowth, 40.0f);

                context.Repeat(15s, 20s);
            });

            scheduler.Schedule(5s, 10s, [this](TaskContext context)
            {
                DoCastRandom(SpellWildEruptionMissle, 40.0f);
                context.Repeat(10s);
            });
        }

        void UpdateAI(uint32 diff) override
        {
            if (!IsEngaged() && _isBossChannelMob && !me->HasUnitState(UNIT_STATE_CASTING))
            {
                DoCastSelf(SpellStasisRitual);
            }

            if (!me->HasUnitState(UNIT_STATE_CASTING))
                scheduler.Update(diff);

            DoMeleeAttackIfReady();
        }

    private:
        bool _isBossChannelMob = false;
};

/// ID - 375652 Wild Eruption
class spell_wild_eruption_375652 : public SpellScript
{
    PrepareSpellScript(spell_wild_eruption_375652);

    enum eWildEruption
    {
        SpellWildEruptionMissle = 375650,
    };

    void HandleDummy(SpellEffIndex /*eff*/)
    {
        if (auto caster = GetCaster())
        {
            std::list<Unit*> enemyPlayers;
            caster->GetAttackableUnitListInRange(enemyPlayers, 40.0f);
            for (auto unit : enemyPlayers)
            {
                if (unit->IsPlayer())
                {
                    caster->CastSpell(caster, SpellWildEruptionMissle, true);
                }
            }
        }
    }

    void Register() override
    {
        OnEffectHit += SpellEffectFn(spell_wild_eruption_375652::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

// 375649
struct at_wild_eruption_25515 : public AreaTriggerAI
{
    public:
        at_wild_eruption_25515(AreaTrigger* at) : AreaTriggerAI(at) { }

        enum eSpells
        {
            InfusedGround = 375649,
        };

        void OnUnitEnter(Unit* who) override
        {
            if (auto caster = at->GetCaster())
                caster->CastSpell(who, InfusedGround, true);
        }

        void OnUnitExit(Unit* who) override
        {
            // @todo: prevent abuse here.
            who->RemoveAurasDueToSpell(InfusedGround);
        }
};

struct npc_se_conjured_lashed_196102 : public ScriptedAI
{
    public:
        npc_se_conjured_lashed_196102(Creature* creature) : ScriptedAI(creature) { }

        enum eSpells
        {
            MysticVapors = 387564,
        };

        void Reset() override
        {
            scheduler.CancelAll();
        }

        void JustEngagedWith(Unit* /*who*/) override
        {
            scheduler.Schedule(4s, [this](TaskContext context)
            {
                DoCast(MysticVapors);
                context.Repeat(8s);
            });
        }

        void UpdateAI(uint32 diff) override
        {
            if (!UpdateVictim())
                return;

            if (!me->HasUnitState(UNIT_STATE_CASTING))
                scheduler.Update(diff);

            DoMeleeAttackIfReady();
        }
};

struct npc_se_vault_guard_190510 : public ScriptedAI
{
    public:
        npc_se_vault_guard_190510(Creature* creature) : ScriptedAI(creature) { }

        enum eSpells
        {
            MageHuntersFervor = 378065,
            IceCutter = 377105,
        };

        void Reset() override
        {
            DoCastSelf(MageHuntersFervor);
            scheduler.CancelAll();
        }

        void JustEngagedWith(Unit* /*who*/) override
        {
            scheduler.Schedule(3s, 5s, [this](TaskContext context)
            {
                DoCastVictim(IceCutter);
                context.Repeat(17s);
            });
        }

        void UpdateAI(uint32 diff) override
        {
            if (!UpdateVictim())
                return;

            if (!me->HasUnitState(UNIT_STATE_CASTING))
                scheduler.Update(diff);

            DoMeleeAttackIfReady();
        }
};

struct npc_se_scalebane_lieutenant_191739 : public ScriptedAI
{
    public:
        npc_se_scalebane_lieutenant_191739(Creature* creature) : ScriptedAI(creature) { }

        enum eSpells
        {
            MageHuntersFervorATAura = 377980,
            SpellfrostBreath        = 391118,
        };

        void Reset() override
        {
            me->RemoveAurasDueToSpell(MageHuntersFervorATAura);
            DoCastSelf(MageHuntersFervorATAura);
            scheduler.CancelAll();
        }

        void JustEngagedWith(Unit* /*who*/) override
        {
            scheduler.Schedule(3s, 5s, [this](TaskContext context)
            {
                DoCastVictim(SpellfrostBreath);
                context.Repeat(17s);
            });
        }

        void UpdateAI(uint32 diff) override
        {
            if (!UpdateVictim())
                return;

            if (!me->HasUnitState(UNIT_STATE_CASTING))
                scheduler.Update(diff);

            DoMeleeAttackIfReady();
        }
};

struct at_se_mage_hunters_fervor_25806 : public AreaTriggerAI
{
    public:
        at_se_mage_hunters_fervor_25806(AreaTrigger* at) : AreaTriggerAI(at) { }

        enum eSpells
        {
            HunterFervor = 378065,
        };

        void OnUnitEnter(Unit* who) override
        {
            if (auto caster = at->GetCaster())
                caster->CastSpell(who, HunterFervor, true);
        }

        void OnUnitExit(Unit* who) override
        {
            who->RemoveAurasDueToSpell(HunterFervor);
        }
};

struct npc_se_drakonid_breaker_187240 : public ScriptedAI
{
    public:
        npc_se_drakonid_breaker_187240(Creature* creature) : ScriptedAI(creature) { }

        enum eSpells
        {
            ShoulderSlam = 391143,
            BestialRoar = 396991,
        };

        void Reset() override
        {
            scheduler.CancelAll();
        }

        void JustEngagedWith(Unit* /*who*/) override
        {
            scheduler.Schedule(3s, 5s, [this](TaskContext context)
            {
                DoCastRandom(ShoulderSlam, 40.0f);
                context.Repeat(17s);
            });
            scheduler.Schedule(7s, [this](TaskContext context)
            {
                DoCastVictim(BestialRoar);
                context.Repeat(17s);
            });
        }

        void UpdateAI(uint32 diff) override
        {
            if (!UpdateVictim())
                return;

            if (!me->HasUnitState(UNIT_STATE_CASTING))
                scheduler.Update(diff);

            DoMeleeAttackIfReady();
        }
};

struct npc_se_nullmagic_hornswog_187246 : public ScriptedAI
{
    public:
        npc_se_nullmagic_hornswog_187246(Creature* creature) : ScriptedAI(creature) { }

        
        enum eSpells
        {
            NullStomp = 386526,
        };

        void Reset() override
        {
            scheduler.CancelAll();
        }

        void JustEngagedWith(Unit* /*who*/) override
        {
            scheduler.Schedule(3s, 5s, [this](TaskContext context)
            {
                DoCastRandom(NullStomp, 40.0f);
                context.Repeat(13s);
            });
        }

        void UpdateAI(uint32 diff) override
        {
            if (!UpdateVictim())
                return;

            if (!me->HasUnitState(UNIT_STATE_CASTING))
                scheduler.Update(diff);

            DoMeleeAttackIfReady();
        }
};

/// ID - 386526 Null Stomp
class spell_null_stomp_386526 : public SpellScript
{
    PrepareSpellScript(spell_null_stomp_386526);

    enum eSpells
    {
        NullStompDmg = 386536,
    };

    void HandleJumpCharge(Optional<JumpArrivalCastArgs>& arrivalCast)
    {
        auto caster = GetCaster();
        if (!caster)
            return;
        if (!arrivalCast.has_value())
        {
            arrivalCast.emplace();
            arrivalCast->Callbacks.push([caster]()
            {
                caster->CastSpell(caster, NullStompDmg, true);
            });
        }
    }

    void Register() override
    {
        OnJumpCharge += SpellJumpChargeFn(spell_null_stomp_386526::HandleJumpCharge);
    }
};

struct npc_se_tarasek_looter_187242 : public ScriptedAI
{
    public:
        npc_se_tarasek_looter_187242(Creature* creature) : ScriptedAI(creature) { }

        enum eSpells
        {
            TearFlesh = 386640,
        };

        void Reset() override
        {
            scheduler.CancelAll();
        }

        void JustEngagedWith(Unit* /*who*/) override
        {
            if (roll_chance_i(50))
                Talk(urand(0, 3));

            scheduler.Schedule(3s, 5s, [this](TaskContext context)
            {
                DoCastVictim(TearFlesh);
                context.Repeat(13s);
            });
        }

        void UpdateAI(uint32 diff) override
        {
            if (!UpdateVictim())
                return;

            if (!me->HasUnitState(UNIT_STATE_CASTING))
                scheduler.Update(diff);

            DoMeleeAttackIfReady();
        }
};

Position const Segment0[16] =
{
    { -5271.6035f , 877.4934f , 389.1697f },
    { -5271.8535f , 883.4934f , 389.1697f },
    { -5271.8535f , 885.2434f , 389.1697f },
    { -5271.8535f , 885.9934f , 389.1697f },
    { -5272.1035f , 886.7434f , 389.1697f },
    { -5272.3535f , 894.4934f , 389.4197f },
    { -5272.3535f , 895.7434f , 389.4197f },
    { -5272.3535f , 896.2434f , 388.9197f },
    { -5272.6035f , 896.9934f , 388.9197f },
    { -5274.8535f , 898.9934f , 388.9197f },
    { -5280.1035f , 898.9934f , 388.9197f },
    { -5280.3535f , 898.9934f , 388.9197f },
    { -5280.6035f , 898.9934f , 388.9197f },
    { -5281.1035f , 898.9934f , 388.9197f },
    { -5281.8535f , 899.2434f , 388.9197f },
    { -5282.6763f , 899.1369f , 388.53488f },
};

using Segment0Size = std::extent<decltype(Segment0)>;

Position const Segment1[8] =
{
    { -5287.8374f , 899.0867f , 388.74695f },
    { -5288.5874f , 899.3367f , 388.74695f },
    { -5289.5874f , 899.3367f , 388.99695f },
    { -5292.0874f , 898.3367f , 388.99695f },
    { -5293.8374f , 897.8367f , 388.74695f },
    { -5297.3374f , 897.0867f , 388.49695f },
    { -5302.8374f , 896.0867f , 386.99695f },
    { -5312.88f , 895.42926f , 383.80222f },
};

using Segment1Size = std::extent<decltype(Segment1)>;

Position const Segment2[7] =
{
    { -5316.1953f , 895.686f , 382.65985f },
    { -5318.9453f , 895.436f , 381.65985f },
    { -5324.9453f , 895.186f , 379.15985f },
    { -5327.4453f , 895.686f , 378.15985f },
    { -5333.4453f , 896.186f , 375.40985f },
    { -5335.1953f , 896.436f , 374.40985f },
    { -5341.4233f , 897.0098f , 371.26483f },
};

using Segment2Size = std::extent<decltype(Segment2)>;

Position const Segment3[8] =
{
    { -5351.1597f , 898.49536f , 366.96686f },
    { -5357.4097f , 899.24536f , 363.71686f },
    { -5357.6597f , 899.24536f , 363.46686f },
    { -5363.1597f , 900.49536f , 360.21686f },
    { -5363.4097f , 900.49536f , 360.21686f },
    { -5363.6597f , 900.49536f , 359.96686f },
    { -5364.4097f , 900.74536f , 359.71686f },
    { -5368.9414f , 901.4527f , 357.04053f },
};

using Segment3Size = std::extent<decltype(Segment3)>;

Position const Segment4[13] =
{
    { -5372.9727f , 902.6864f , 355.18616f },
    { -5376.9727f , 903.4364f , 353.18616f },
    { -5378.2227f , 903.6864f , 352.68616f },
    { -5380.4727f , 904.1864f , 351.43616f },
    { -5380.7227f , 904.1864f , 351.68616f },
    { -5380.9727f , 904.4364f , 351.43616f },
    { -5383.7227f , 904.6864f , 350.18616f },
    { -5384.7227f , 904.9364f , 350.18616f },
    { -5393.2227f , 906.9364f , 347.18616f },
    { -5393.4727f , 906.9364f , 347.18616f },
    { -5393.9727f , 906.9364f , 346.93616f },
    { -5396.2227f , 907.4364f , 346.18616f },
    { -5396.8003f , 907.49194f , 345.523f },
};

using Segment4Size = std::extent<decltype(Segment4)>;

Position const Segment5[13] =
{
    { -5398.343f , 907.5663f , 345.17737f },
    { -5400.093f , 907.5663f , 344.67737f },
    { -5400.843f , 907.5663f , 344.17737f },
    { -5404.593f , 907.8163f , 344.17737f },
    { -5405.593f , 907.8163f , 343.67737f },
    { -5412.593f , 907.8163f , 343.67737f },
    { -5417.343f , 906.0663f , 343.67737f },
    { -5417.593f , 905.5663f , 343.67737f },
    { -5418.343f , 904.5663f , 343.92737f },
    { -5425.843f , 894.8163f , 343.67737f },
    { -5427.843f , 892.0663f , 343.67737f },
    { -5431.093f , 888.0663f , 343.67737f },
    { -5435.8853f , 881.6406f , 343.33176f },
};

using Segment5Size = std::extent<decltype(Segment5)>;

struct npc_se_telash_greywing_199614 : public ScriptedAI
{
    public:
        npc_se_telash_greywing_199614(Creature* creature) : ScriptedAI(creature) { }

        enum eSpells
        {
            RPSceneRansackingTheVault = 397107,
        };

        void JustEngagedWith(Unit* /*who*/) override
        {
        }

        void OnUnitRelocation(Unit* who) override
        {
            if (_didIntro)
                return;

            if (who->IsPlayer())
            {
                if (who->GetDistance(me) <= 78.0f)
                {
                    _didIntro = true;
                    DoCastSelf(RPSceneRansackingTheVault);

                    // does it 4 times, maybe cause of 4 players?
                    me->HandleEmoteCommand(Emote::EMOTE_ONESHOT_TALK_EXCLAMATION);
                    me->HandleEmoteCommand(Emote::EMOTE_ONESHOT_TALK_EXCLAMATION);
                    me->HandleEmoteCommand(Emote::EMOTE_ONESHOT_TALK_EXCLAMATION);
                    me->HandleEmoteCommand(Emote::EMOTE_ONESHOT_TALK_EXCLAMATION);

                    me->GetMotionMaster()->MoveSmoothPath2(1, Segment0, Segment0Size::value, false, false, false, false)->_callbacks.push([this]()
                    {
                    me->GetMotionMaster()->MoveSmoothPath2(1, Segment1, Segment1Size::value, false, false, false, false)->_callbacks.push([this]()
                    {
                    me->GetMotionMaster()->MoveSmoothPath2(1, Segment2, Segment2Size::value, false, false, false, false)->_callbacks.push([this]()
                    {
                    me->GetMotionMaster()->MoveSmoothPath2(1, Segment3, Segment3Size::value, false, false, false, false)->_callbacks.push([this]()
                    {
                    me->GetMotionMaster()->MoveSmoothPath2(1, Segment4, Segment4Size::value, false, false, false, false)->_callbacks.push([this]()
                    {
                    me->GetMotionMaster()->MoveSmoothPath2(1, Segment5, Segment5Size::value, false, false, false, false)->_callbacks.push([this]()
                    {
                        me->DespawnOrUnsummon();
                    });
                    });
                    });
                    });
                    });
                    });
                }
            }
        }

    private:
        bool _didIntro = false;
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
    RegisterCreatureAI(npc_se_arcane_elemental_186741);
    RegisterCreatureAI(npc_se_rune_seal_keeper_187155);
    RegisterCreatureAI(npc_se_astral_attendant_189555);
    RegisterCreatureAI(npc_se_arcane_construct_186740);
    RegisterCreatureAI(npc_se_crystal_fury_196116);
    RegisterCreatureAI(npc_se_crystal_thrasher_196117);
    RegisterCreatureAI(npc_se_unstable_curator_187154);
    RegisterCreatureAI(npc_se_shrieking_whelp_188100);
    RegisterCreatureAI(npc_se_bubbling_sappling_191313);
    RegisterCreatureAI(npc_se_arcane_tender_191164);
    RegisterCreatureAI(npc_se_conjured_lashed_196102);
    RegisterCreatureAI(npc_se_vault_guard_190510);
    RegisterCreatureAI(npc_se_scalebane_lieutenant_191739);
    RegisterCreatureAI(npc_se_drakonid_breaker_187240);
    RegisterCreatureAI(npc_se_nullmagic_hornswog_187246);
    RegisterCreatureAI(npc_se_tarasek_looter_187242);
    RegisterCreatureAI(npc_se_telash_greywing_199614);

    RegisterAreaTriggerAI(at_revealing_gaze_28931);
    RegisterAreaTriggerAI(at_wild_eruption_25515);
    RegisterAreaTriggerAI(at_se_mage_hunters_fervor_25806);

    RegisterSpellScript(spell_shriek_370225);
    RegisterSpellScript(spell_sappy_burst_375591);
    RegisterSpellScript(spell_wild_eruption_375652);
    RegisterSpellScript(spell_null_stomp_386526);
}
