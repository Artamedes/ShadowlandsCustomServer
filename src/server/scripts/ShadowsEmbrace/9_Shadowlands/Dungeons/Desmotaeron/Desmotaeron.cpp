#include "Desmotaeron.h"

namespace FieryPlegm
{
    enum
    {
        DmgSpell = 357619,
        AtSpell = 357634,
    };

    /// ID: 357640  Fiery Phlegm
    class spell_fiery_phlegm : public SpellScript
    {
        PrepareSpellScript(spell_fiery_phlegm);

        void HandleDummy(SpellEffIndex /*eff*/)
        {
            if (auto caster = GetCaster())
            {
                caster->CastSpell(caster, DmgSpell);
            }
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_fiery_phlegm::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    /// 23499
    struct at_fiery_phlegm : public AreaTriggerAI
    {
    public:
        at_fiery_phlegm(AreaTrigger* at) : AreaTriggerAI(at) { }

        void OnUnitEnter(Unit* who)
        {
            auto caster = at->GetCaster();
            if (!caster)
                return;
            if (caster->IsValidAttackTarget(who))
            {
                caster->CastSpell(who, AtSpell, true);
            }
        }
        void OnUnitExit(Unit* who)
        {
            if (who->HasAura(AtSpell, at->GetCasterGuid()))
            {
                who->RemoveAurasDueToSpell(AtSpell, at->GetCasterGuid());
            }
        }
    };

    void Register()
    {
        RegisterSpellScript(spell_fiery_phlegm);
        RegisterAreaTriggerAI(at_fiery_phlegm);
    }
}

namespace DarkDischarge
{
    enum DarkDischarge
    {
        DmgSpell = 357643,
        AtSpell = 357635,
    };

    /// ID: 357643 Dark Discharge
    class spell_dark_discharge : public SpellScript
    {
        PrepareSpellScript(spell_dark_discharge);

        void HandleDummy(SpellEffIndex /*eff*/)
        {
            if (auto caster = GetCaster())
            {
                caster->CastSpell(caster, DmgSpell);
            }
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_dark_discharge::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    /// 23500
    struct at_dark_discharge : public AreaTriggerAI
    {
    public:
        at_dark_discharge(AreaTrigger* at) : AreaTriggerAI(at) { }

        void OnUnitEnter(Unit* who)
        {
            auto caster = at->GetCaster();
            if (!caster)
                return;
            if (caster->IsValidAttackTarget(who))
            {
                caster->CastSpell(who, AtSpell, true);
            }
        }
        void OnUnitExit(Unit* who)
        {
            if (who->HasAura(AtSpell, at->GetCasterGuid()))
            {
                who->RemoveAurasDueToSpell(AtSpell, at->GetCasterGuid());
            }
        }
    };

    void Register()
    {
        RegisterSpellScript(spell_dark_discharge);
        RegisterAreaTriggerAI(at_dark_discharge);
    }
}

namespace SaltySpittle
{
    enum SaltySpittle
    {
        DmgSpell = 357620,
        AtSpell = 357636,
    };

    /// ID - 357644 Salty Spittle
    class spell_salty_spittle : public SpellScript
    {
        PrepareSpellScript(spell_salty_spittle);

        void HandleDummy(SpellEffIndex /*eff*/)
        {
            if (auto caster = GetCaster())
            {
                caster->CastSpell(caster, DmgSpell);
            }
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_salty_spittle::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    /// 23501
    struct at_salty_spittle : public AreaTriggerAI
    {
    public:
        at_salty_spittle(AreaTrigger* at) : AreaTriggerAI(at) { }

        void OnUnitEnter(Unit* who)
        {
            auto caster = at->GetCaster();
            if (!caster)
                return;
            if (caster->IsValidAttackTarget(who))
            {
                caster->CastSpell(who, AtSpell, true);
            }
        }
        void OnUnitExit(Unit* who)
        {
            if (who->HasAura(AtSpell, at->GetCasterGuid()))
            {
                who->RemoveAurasDueToSpell(AtSpell, at->GetCasterGuid());
            }
        }
    };

    void Register()
    {
        RegisterSpellScript(spell_salty_spittle);
        RegisterAreaTriggerAI(at_salty_spittle);
    }
}

enum eDefilingDreadslam
{
    DreadslamDefile = 365174,
};

/// 23468
struct at_defiling_dreadslam : public AreaTriggerAI
{
public:
    at_defiling_dreadslam(AreaTrigger* at) : AreaTriggerAI(at) { }

    void OnUnitEnter(Unit* who)
    {
        auto caster = at->GetCaster();
        if (!caster)
            return;
        if (caster->IsValidAttackTarget(who))
        {
            caster->CastSpell(who, DreadslamDefile, true);
        }
    }
    void OnUnitExit(Unit* who)
    {
        if (who->HasAura(DreadslamDefile, at->GetCasterGuid()))
        {
            who->RemoveAurasDueToSpell(DreadslamDefile, at->GetCasterGuid());
        }
    }
};

/// ID: 357181 Blazing Inferno
class spell_blazing_inferno : public SpellScript
{
    PrepareSpellScript(spell_blazing_inferno);

    enum eBlazing
    {
        BlazingInfernoMissle = 357182,
    };

    void HandleDummy(SpellEffIndex /*eff*/)
    {
        auto caster = GetCaster();
        if (!caster)
            return;

        std::list<Unit*> enemies;
        caster->GetAttackableUnitListInRange(enemies, 40.0f);
        for (auto enemy : enemies)
        {
            caster->CastSpell(enemy, BlazingInfernoMissle, true);
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_blazing_inferno::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

/// ID: 297025 Soul Echo
class spell_soul_echo : public SpellScript
{
    PrepareSpellScript(spell_soul_echo);

    enum eSoulEcho
    {
        SoulEchoMissle = 297026,
    };

    void HandleAfter()
    {
        auto caster = GetCaster();
        if (!caster)
            return;

        std::list<Unit*> enemies;
        caster->GetAttackableUnitListInRange(enemies, 40.0f);
        for (auto enemy : enemies)
        {
            caster->CastSpell(enemy, SoulEchoMissle, true);
        }
    }

    void Register() override
    {
        AfterCast += SpellCastFn(spell_soul_echo::HandleAfter);
    }
};
/// ID: 354240 Ritual of Slaughter
class spell_ritual_of_slaughter : public AuraScript
{
    PrepareAuraScript(spell_ritual_of_slaughter);

    enum eRitualOfSlaughter
    {
        MissleOne   = 354246,
        MissleTwo   = 354247,
        MissleThree = 354248,
    };

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
        auto caster = GetCaster();
        if (!caster)
            return;

        if (NextCastSpell.empty())
        {
            NextCastSpell.push_back(MissleOne);
            NextCastSpell.push_back(MissleTwo);
            NextCastSpell.push_back(MissleThree);

            Trinity::Containers::RandomShuffle(NextCastSpell);
        }

        caster->CastSpell(caster, NextCastSpell.front(), true);
        NextCastSpell.pop_front();
    }

    std::deque<uint32> NextCastSpell;

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_ritual_of_slaughter::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

/// 21138
struct at_death_orb : public AreaTriggerAI
{
public:
    at_death_orb(AreaTrigger* at) : AreaTriggerAI(at) { }

    enum eDeathOrb
    {
        DeathOrbDmg = 297111,
    };

    void OnUnitEnter(Unit* who) override
    {
        if (auto caster = at->GetCaster())
            if (caster->IsValidAttackTarget(who))
            {
                caster->CastSpell(who, DeathOrbDmg, true);
                at->Remove();
            }
    }
};

/// ID: 297111 Death Orb
class spell_death_orb : public SpellScript
{
    PrepareSpellScript(spell_death_orb);

    void HandleDmg(SpellEffIndex /*eff*/)
    {
        if (auto caster = GetCaster())
        {
            if (auto hitUnit = GetHitUnit())
            {
                if (auto challenge = caster->GetInstanceScript())
                {
                    if (caster->IsCreature() && challenge->IsChallenge())
                    {
                        auto level = challenge->GetChallenge()->GetChallengeLevel();
                        auto dmg = level * 5 + 50;

                        if (dmg > 100)
                            dmg = 100;

                        SetHitDamage(hitUnit->CountPctFromMaxHealth(dmg));
                        return; // incase we give this to players at some point
                    }
                }
            }
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_death_orb::HandleDmg, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

// 707027 - npc_portal_707027
struct npc_portal_707027 : public ScriptedAI
{
public:
    npc_portal_707027(Creature* creature) : ScriptedAI(creature) { }

    void OnSpellClick(Unit* clicker, bool /*spellClickHandled*/) override
    {
        clicker->GetScheduler().CancelGroup(707027);
        clicker->GetScheduler().Schedule(1s, 707027, [](TaskContext context)
        {
            auto u = context.GetUnit();
            u->NearTeleportTo({ 4295.89f, 6174.89f, 4744.31f, 5.43584f }, true, false);
        });
    }
};

// 708018 - npc_soul_portal_708018
struct npc_soul_portal_708018 : public ScriptedAI
{
public:
    npc_soul_portal_708018(Creature* creature) : ScriptedAI(creature) { }

    void InitializeAI() override
    {
        me->SetReactState(REACT_PASSIVE);
        me->SetUnitFlag(UnitFlags::UNIT_FLAG_NON_ATTACKABLE);
        me->SetUnitFlag(UnitFlags::UNIT_FLAG_UNINTERACTIBLE);
    }
};

const Position SoulHarvesterTriggerSpawnPositions[] =
{
    { 4108.63f, 5982.22f, 4851.27f, 4.73133f },
    { 4124.73f, 5973.73f, 4851.27f, 3.5611f },
    { 4120.09f, 5954.48f, 4851.27f, 2.40656f },
    { 4105.59f, 5949.23f, 4851.27f, 1.38947f },
    { 4093.78f, 5968.21f, 4851.27f, 6.0783f },
};

// 708010 - npc_soul_harvester_trigger_708010
struct npc_soul_harvester_trigger_708010 : public ScriptedAI
{
public:
    npc_soul_harvester_trigger_708010(Creature* creature) : ScriptedAI(creature), summons(creature) { }

    void InitializeAI() override
    {
        for (auto const& pos : SoulHarvesterTriggerSpawnPositions)
        {
            DoSummon(708006, pos);
        }
    }

    void UpdateAI(uint32 diff) override
    {
        summons.DoOnSummons([this](Creature* creature)
        {
            if (!creature->IsEngaged() && !creature->isDead())
            {
                if (!creature->GetCurrentSpell(CurrentSpellTypes::CURRENT_CHANNELED_SPELL))
                    creature->CastSpell(me, 287547, true);
            }
        });
    }

    void JustSummoned(Creature* creature) override
    {
        summons.Summon(creature);
    }

    void SummonedCreatureDespawn(Creature* creature) override
    {
        summons.Despawn(creature);
    }

    SummonList summons;
};

/// ID: 357329 Soulflame Torrent
class spell_soulflame_torrent : public SpellScript
{
    PrepareSpellScript(spell_soulflame_torrent);

    enum eSoulEcho
    {
        SoulFlameMissle = 357331,
    };

    void HandleAfter()
    {
        auto caster = GetCaster();
        if (!caster)
            return;

        std::list<Unit*> enemies;
        caster->GetAttackableUnitListInRange(enemies, 40.0f);
        for (auto enemy : enemies)
        {
            caster->CastSpell(enemy, SoulFlameMissle, true);
        }
    }

    void Register() override
    {
        AfterCast += SpellCastFn(spell_soulflame_torrent::HandleAfter);
    }
};

// 708019 - npc_vicious_souleater_708019
struct npc_vicious_souleater_708019 : public ScriptedAI
{
public:
    npc_vicious_souleater_708019(Creature* creature) : ScriptedAI(creature) { }

    void InitializeAI() override
    {
        me->SetReactState(REACT_PASSIVE);
        me->SetUnitFlag(UnitFlags::UNIT_FLAG_NON_ATTACKABLE);
        DoCastSelf(SpectralWingsGuard);
        DoPath();
    }

    void DoPath()
    {
        me->GetMotionMaster()->MoveCirclePath(me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), frand(18.0f, 25.0f), true, 15)->callbackFunc = [this]()
        {
            DoPath();
        };
    }
};

const Position UnboundShadeMongrelPathOne[] =
{
    { 4430.86f, 5817.04f, 4784.69f, 2.53783f },
    { 4407.82f, 5830.98f, 4784.69f, 2.50248f },
    { 4394.71f, 5848.27f, 4784.69f, 2.21974f },
    { 4383.55f, 5865.14f, 4784.69f, 2.1844f },
    { 4375.72f, 5876.59f, 4784.08f, 1.75243f },
    { 4371.11f, 5894.01f, 4784.45f, 1.94093f },
    { 4356.94f, 5911.34f, 4784.06f, 2.31006f },
    { 4341.17f, 5925.21f, 4786.24f, 2.42002f },
    { 4331.18f, 5938.62f, 4789.42f, 2.20011f },
    { 4316.96f, 5962.5f, 4795.42f, 2.09015f },
    { 4309.46f, 5975.14f, 4795.75f, 2.13335f },
    { 4289.49f, 5986.17f, 4795.36f, 2.85199f },
    { 4262.99f, 5987.65f, 4807.47f, 3.10724f },
    { 4252.5f, 5987.76f, 4814.74f, 3.1308f },
    { 4224.44f, 5996.74f, 4815.34f, 1.85453f },
    { 4214.65f, 6027.4f, 4815.24f, 1.91344f },
    { 4204.21f, 6045.17f, 4815.23f, 2.37682f },
    { 4194.07f, 6053.77f, 4823.46f, 2.49856f },
    { 4182.69f, 6061.92f, 4832.57f, 2.52212f },
    { 4160.4f, 6076.99f, 4833.97f, 2.62422f },
};

using UnboundShadeMongrelPathSizeOne = std::extent<decltype(UnboundShadeMongrelPathOne)>;

const Position UnboundShadeMongrelPathTwo[] =
{
    { 4146.49f, 6078.07f, 4836.24f, 3.06404f },
    { 4123.65f, 6079.35f, 4844.37f, 3.16222f },
    { 4111.13f, 6079.79f, 4847.29f, 3.19756f },
    { 4095.99f, 6070.54f, 4847.93f, 4.23036f },
    { 4093.1f, 6059.26f, 4848.35f, 4.48561f },
    { 4092.23f, 6009.72f, 4852.68f, 4.7173f },
    { 4058.39f, 5952.26f, 4855.36f, 4.08899f },
    { 4086.53f, 5901.49f, 4854.84f, 5.24744f },
    { 4102.44f, 5856.89f, 4856.1f, 4.92544f },
    { 4106.98f, 5833.85f, 4853.44f, 5.12964f },
    { 4114.17f, 5826.21f, 4850.98f, 5.5027f },
    { 4130.75f, 5818.09f, 4846.71f, 0.248382f },
    { 4147.35f, 5825.46f, 4842.6f, 0.507564f },
    { 4154.81f, 5832.85f, 4840.25f, 1.3126f },
    { 4156.72f, 5846.71f, 4836.67f, 1.4147f },
    { 4160.31f, 5885.72f, 4836.09f, 1.52858f },
    { 4161.54f, 5905.27f, 4836.09f, 1.46968f },
    { 4168.44f, 5925.74f, 4832.44f, 1.07305f },
    { 4190.47f, 5939.59f, 4826.96f, 0.232673f },
    { 4215.94f, 5950.11f, 4820.71f, 0.664642f },
    { 4219.53f, 5965.81f, 4817.09f, 1.34794f },
    { 4230.64f, 5985.86f, 4815.49f, 0.868846f },
    { 4247.33f, 5987.48f, 4815.06f, 0.00490713f },
    { 4251.53f, 5987.5f, 4815.07f, 0.00490713f },
    { 4280.22f, 5986.97f, 4795.85f, 0.000979424f },
    { 4337.3f, 5973.96f, 4797.64f, 6.05247f },
    { 4370.35f, 5969.64f, 4801.74f, 6.23704f },
    { 4395.49f, 5967.97f, 4818.85f, 6.18206f },
    { 4399.43f, 5963.06f, 4819.29f, 5.271f },
    { 4405.13f, 5952.1f, 4819.74f, 4.8783f },
    { 4403.64f, 5932.58f, 4819.74f, 4.572f },
    { 4401.15f, 5909.64f, 4819.74f, 4.71337f },
    { 4407.1f, 5888.96f, 4819.74f, 5.11785f },
    { 4417.43f, 5869.89f, 4819.74f, 5.271f },
    { 4431.01f, 5856.8f, 4819.75f, 5.62835f },
    { 4420.31f, 5865.64f, 4819.74f, 2.25899f },
};

using UnboundShadeMongrelPathSizeTwo = std::extent<decltype(UnboundShadeMongrelPathTwo)>;

const Position UnboundShadeMongrelPathThree[] =
{
    { 4420.31f, 5865.64f, 4819.74f, 2.1883f },
    { 4413.64f, 5878.73f, 4819.74f, 2.02337f },
    { 4405.59f, 5896.59f, 4819.74f, 1.90949f },
    { 4402.77f, 5913.13f, 4819.74f, 1.71314f },
    { 4403.25f, 5931.32f, 4819.74f, 1.52857f },
    { 4404.55f, 5941.74f, 4819.74f, 1.59925f },
};

using UnboundShadeMongrelPathSizeThree = std::extent<decltype(UnboundShadeMongrelPathThree)>;

// 708016 - npc_unbound_shademongrel_708016
struct npc_unbound_shademongrel_708016 : public BaseCustomScriptedAI
{
public:
    npc_unbound_shademongrel_708016(Creature* creature) : BaseCustomScriptedAI(creature) { }

    enum eUnboundShademongrel
    {
        HollowBite = 336803,
        Rake = 319628,
    };

    void InitializeAI() override
    {
        if (me->GetSpawnId() == 1056047)
            DoPath();
    }

    void Reset() override
    {
        BaseCustomScriptedAI::Reset();

        if (me->GetSpawnId() == 1056047)
            DoPath();
    }

    void JustEngagedWith(Unit* who) override
    {
        scheduler.Schedule(1s, 4s, [this](TaskContext context)
        {
            DoCastVictim(HollowBite);
            context.Repeat(10s, 15s);
        });
        scheduler.Schedule(1s, 4s, [this](TaskContext context)
        {
            DoCastVictim(Rake);
            context.Repeat(10s, 15s);
        });
    }

    void UpdateAI(uint32 diff) override
    {
        if (me->GetSpawnId() == 1056047 && !me->IsEngaged() && !PathDone)
            me->SignalFormationMovement();

        BaseCustomScriptedAI::UpdateAI(diff);
    }

    bool PathDone = false;

    void DoPath()
    {
        if (PathDone)
            return;

        me->GetMotionMaster()->MoveSmoothPath(0, UnboundShadeMongrelPathOne, UnboundShadeMongrelPathSizeOne::value)->callbackFunc = [this]
        {
            me->GetMotionMaster()->MoveSmoothPath(0, UnboundShadeMongrelPathTwo, UnboundShadeMongrelPathSizeTwo::value)->callbackFunc = [this]
            {
                PathDone = true;
            };
        };
    }

    void OnUnitRelocation(Unit* who) override
    {
        if (who->IsPlayer() && PathDone && who->GetDistance2d(me) <= 50.0f)
        {
            me->GetMotionMaster()->MoveSmoothPath(0, UnboundShadeMongrelPathThree, UnboundShadeMongrelPathSizeThree::value)->callbackFunc = [this]
            {

            };
        }
    }
};

// 707019 - npc_bagnok_the_infernal_707019
struct npc_bagnok_the_infernal_707019 : public BaseCustomScriptedAI
{
public:
    npc_bagnok_the_infernal_707019(Creature* creature) : BaseCustomScriptedAI(creature) { }

    void Reset() override
    {
        BaseCustomScriptedAI::Reset();
        DidPhase90Pct = false;
        DidPhase80Pct = false;
        DidPhase70Pct = false;
        DidPhase60Pct = false;
        DidPhase50Pct = false;
        DidPhase40Pct = false;
        DidPhase30Pct = false;
        DidPhase20Pct = false;
        DidPhase10Pct = false;

        DoCastSelf(TouchOfFlame);
    }

    void JustEngagedWith(Unit* /*who*/) override
    {
        scheduler.Schedule(1s, 11s, [this](TaskContext context)
        {
            DoCastVictim(BeastialHowl);
            context.Repeat(10s, 15s);
        });
        scheduler.Schedule(1s, 14s, [this](TaskContext context)
        {
            DoCastVictim(BellowingRoar);
            context.Repeat(10s, 15s);
        });
        scheduler.Schedule(1s, 14s, [this](TaskContext context)
        {
            DoCastVictim(BlazingInferno);
            context.Repeat(10s, 15s);
        });
    }

    void DamageDealt(Unit* victim, uint32& damage, DamageEffectType type, SpellInfo const* spellInfo /*= nullptr*/) override
    {
        if (spellInfo && victim)
        {
            switch (spellInfo->Id)
            {
                case 357179: ///< Blazing Inferno DMG
                    damage += victim->CountPctFromMaxHealth(70);
                    ApplyChallengeDMGIncrease(me, damage, 5);
                    break;
                case BellowingRoar:
                    damage += victim->CountPctFromMaxHealth(30);
                    ApplyChallengeDMGIncrease(me, damage, 5);
                    break;
            }
        }
    }

    bool DidPhase90Pct = false;
    bool DidPhase80Pct = false;
    bool DidPhase70Pct = false;
    bool DidPhase60Pct = false;
    bool DidPhase50Pct = false;
    bool DidPhase40Pct = false;
    bool DidPhase30Pct = false;
    bool DidPhase20Pct = false;
    bool DidPhase10Pct = false;

    void DamageTaken(Unit* attacker, uint32& damage, DamageEffectType /*damageType*/, SpellInfo const* /*spellInfo = nullptr*/) override
    {
        auto CheckHealthAndDoPhaseIfNeed([&](uint32 healthPct, bool& phaseVar)
        {
            if (me->HealthBelowPctDamaged(healthPct, damage) && !phaseVar)
            {
                phaseVar = true;
                DoCastSelf(RisingHeat);
            }
        });

        CheckHealthAndDoPhaseIfNeed(91, DidPhase90Pct);
        CheckHealthAndDoPhaseIfNeed(81, DidPhase80Pct);
        CheckHealthAndDoPhaseIfNeed(71, DidPhase70Pct);
        CheckHealthAndDoPhaseIfNeed(61, DidPhase60Pct);
        CheckHealthAndDoPhaseIfNeed(51, DidPhase50Pct);
        CheckHealthAndDoPhaseIfNeed(41, DidPhase40Pct);
        CheckHealthAndDoPhaseIfNeed(31, DidPhase30Pct);
        CheckHealthAndDoPhaseIfNeed(21, DidPhase20Pct);
        CheckHealthAndDoPhaseIfNeed(11, DidPhase10Pct);
    }
};

// 707012 - npc_prison_guard_707012
struct npc_prison_guard_707012 : public BaseCustomScriptedAI
{
public:
    npc_prison_guard_707012(Creature* creature) : BaseCustomScriptedAI(creature) { }

    void JustEngagedWith(Unit* /*who*/) override
    {
        scheduler.Schedule(1s, 11s, [this](TaskContext context)
        {
            DoCastVictim(ColossalSmash);
            context.Repeat(10s, 15s);
        });
        scheduler.Schedule(1s, 14s, [this](TaskContext context)
        {
            DoCastVictim(DefilingDreadslam);
            context.Repeat(10s, 15s);
        });
        scheduler.Schedule(1s, 14s, [this](TaskContext context)
        {
            DoCastVictim(IronShackles);
            context.Repeat(10s, 15s);
        });
    }

    void DamageDealt(Unit* victim, uint32& damage, DamageEffectType type, SpellInfo const* spellInfo /*= nullptr*/) override
    {
        if (spellInfo && victim)
        {
            switch (spellInfo->Id)
            {
                case ColossalSmash: ///< Collosal Smash
                    damage += 50000;
                    damage += victim->CountPctFromMaxHealth(70);
                    ApplyChallengeDMGIncrease(me, damage, 5);
                    break;
                case DreadslamDefile:
                    damage += 50000;
                    damage += victim->CountPctFromMaxHealth(30);
                    ApplyChallengeDMGIncrease(me, damage, 5);
                    break;
            }
        }
    }
};

enum eLicethDovarax
{
    MawChanneling = 350480,
    SoulBolt = 357086,
    SoulBoltVolley = 357402,
    BurningDesacration = 353443,
};
// 707008 - npc_liceth_dovarax_707008
struct npc_liceth_dovarax_707008 : public BaseCustomCasterAI
{
public:
    npc_liceth_dovarax_707008(Creature* creature) : BaseCustomCasterAI(creature, SoulBolt) { }

    void Reset() override
    {
        BaseCustomScriptedAI::Reset();
        DoCastSelf(MawChanneling);
    }

    void JustEngagedWith(Unit* /*who*/) override
    {
        scheduler.Schedule(1s, 11s, [this](TaskContext context)
        {
            DoCastVictim(SoulBoltVolley);
            context.Repeat(10s, 15s);
        });
        scheduler.Schedule(1s, 20s, [this](TaskContext context)
        {
            DoCastVictim(BurningDesacration);
            context.Repeat(30s, 45s);
        });
    }

    void DamageDealt(Unit* victim, uint32& damage, DamageEffectType type, SpellInfo const* spellInfo /*= nullptr*/) override
    {
        if (spellInfo && victim)
        {
            switch (spellInfo->Id)
            {
                case SoulBoltVolley:
                    damage += victim->CountPctFromMaxHealth(30);
                    ApplyChallengeDMGIncrease(me, damage, 5);
                    break;
                case SoulBolt:
                    damage += victim->CountPctFromMaxHealth(25);
                    ApplyChallengeDMGIncrease(me, damage, 5);
                    break;
                case 353444: ///< Burning Desacration
                    damage += victim->CountPctFromMaxHealth(25);
                    ApplyChallengeDMGIncrease(me, damage, 5);
                    break;
            }
        }
    }
};

const Position EyeOfTheMawPath[] =
{
    { 4602.16f, 5988.48f, 4866.89f, 5.45865f },
    { 4614.94f, 5864.77f, 4971.97f, 4.84538f },
    { 4658.12f, 5653.61f, 5078.09f, 4.80061f },
};

struct npc_eye_of_the_maw_707018 : public ScriptedAI
{
public:
    npc_eye_of_the_maw_707018(Creature* creature) : ScriptedAI(creature) { }

    enum eTalks
    {
        TalkAnnoyance = 0,
        TalkSpace,
    };

    void InitializeAI()
    {
        scheduler.Schedule(1s, [this](TaskContext context)
        {
            Talk(TalkAnnoyance);
            context.Repeat(10s, 20s);
        });
    }

    bool phased = false;
    TaskScheduler scheduler;

    void UpdateAI(uint32 diff) override
    {
        scheduler.Update(diff);
        if (!UpdateVictim() || phased)
            return;

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        DoMeleeAttackIfReady();
    }

    void DamageTaken(Unit* /*attacker*/, uint32& damage, DamageEffectType /*damageType*/, SpellInfo const* /*spellInfo = nullptr*/) override
    {
        if (phased)
        {
            damage = 0;
            return;
        }

        if (damage >= me->GetHealth())
        {
            scheduler.CancelAll();
            Talk(TalkSpace);
            damage = 0;
            phased = true;
            me->SetReactState(REACT_PASSIVE);
            me->SetUnitFlag(UnitFlags::UNIT_FLAG_IMMUNE_TO_PC);
            me->GetMotionMaster()->MoveSmoothPath(1, EyeOfTheMawPath, 3, false, true, 25.0f)->callbackFunc = [this]
            {
                me->DespawnOrUnsummon();
            };
        }
    }

    void EnterEvadeMode(EvadeReason why) override
    {
        if (!phased)
            ScriptedAI::EnterEvadeMode(why);
    }
};

void AddSC_Desmotareon()
{
    RegisterCreatureAI(npc_portal_707027);
    RegisterCreatureAI(npc_soul_portal_708018);
    RegisterCreatureAI(npc_soul_harvester_trigger_708010);
    RegisterCreatureAI(npc_vicious_souleater_708019);
    RegisterCreatureAI(npc_unbound_shademongrel_708016);
    RegisterCreatureAI(npc_bagnok_the_infernal_707019);
    RegisterCreatureAI(npc_prison_guard_707012);
    RegisterCreatureAI(npc_liceth_dovarax_707008);
    RegisterCreatureAI(npc_eye_of_the_maw_707018);

    FieryPlegm::Register();
    DarkDischarge::Register();
    SaltySpittle::Register();

    RegisterSpellScript(spell_blazing_inferno);
    RegisterSpellScript(spell_soul_echo);
    RegisterSpellScript(spell_ritual_of_slaughter);
    RegisterSpellScript(spell_death_orb);
    RegisterSpellScript(spell_soulflame_torrent);

    RegisterAreaTriggerAI(at_death_orb);
    RegisterAreaTriggerAI(at_defiling_dreadslam);
}

void DoDelayedMawPortalSpawn(Creature* who, float dist)
{
    who->SetUnitFlag(UnitFlags::UNIT_FLAG_NON_ATTACKABLE);
    who->SetUnitFlag(UnitFlags::UNIT_FLAG_IMMUNE_TO_PC);
    who->GetScheduler().Schedule(100ms, [](TaskContext context)
    {
        auto unit = context.GetUnit();
        unit->CastSpell(unit, MawPortalIn, true);
        unit->CastSpell(unit, HideSpell, true);
    });

    who->GetScheduler().Schedule(300ms, [](TaskContext context)
    {
        auto unit = context.GetUnit();
        unit->RemoveAurasDueToSpell(HideSpell);
        unit->CastSpell(unit, AppearEffect, true);
    });

    who->GetScheduler().Schedule(900ms, [dist](TaskContext context)
    {
        auto unit = context.GetUnit();
        unit->GetMotionMaster()->Move(0, MoveTypes::Forward, MOVE_PATHFINDING, dist);
    });

    who->GetScheduler().Schedule(2s, [](TaskContext context)
    {
        auto unit = context.GetUnit()->ToCreature();

        unit->RemoveUnitFlag(UnitFlags::UNIT_FLAG_NON_ATTACKABLE);
        unit->RemoveUnitFlag(UnitFlags::UNIT_FLAG_IMMUNE_TO_PC);

        if (unit->AI())
            unit->AI()->DoZoneInCombat();
    });
}
