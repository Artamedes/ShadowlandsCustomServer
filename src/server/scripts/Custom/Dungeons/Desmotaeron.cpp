#include "../CustomInstanceScript.h"
#include "MotionMaster.h"
#include "GenericMovementGenerator.h"
#include "ScriptedCreature.h"
#include "ScriptMgr.h"
#include "AreaTrigger.h"
#include "AreaTriggerAI.h"
#include "TemporarySummon.h"
#include "MovementGenerator.h"
#include "GameTime.h"
#include "SpellAuras.h"

enum Desmoteraon
{
    BossXarvius = 0,
    BossShirgantai,
    BossGeneralNephmir,
    BossEcidus,
    BossMaleakos,

    NpcSpawnOfShirgantai = 707033,
};

enum DesmotareonVisuals
{
    SpawnBlastAnim = 353961,
    MawPortalIn    = 360358,
    FadeInEffect   = 337464,
    DisappearSpell = 209026,
    AppearEffect   = 351925, // blue appear
    HideSpell      = 362717,

    StygianLaden = 337897,
    MawCosmetic = 326326,

    HologramSpawn = 253589, // spawns azeroth visual;
    HologramGreen = 231696,

    EmpoweredBrokerWeatherChange = 353689,
    TheMist = 312242,
    IceAge = 354529,
    HeavyFogRain = 305422, ///< Cast on enter

    TeleportSpell = 268256,
    TeleportSpell2 = 268270,
};

enum DesmotareonSpells
{
    VolatileFelBurst = 209019,

    // Dragons cast -
    FieryPhlegmCast = 357640,
    DarkDischargeCast = 357643,
    SaltySpittleCast = 357644,
    DeadlyHunger = 336838, ///< Cast every 10s, they have to walk out of melee
    CrushingBite = 343722,
    CripplingBlow = 166766, ///< Cast every 15s
    WingBlast     = 335853,
    SoulShift     = 357516,

    /// Maw Eye
    FocusedAnnihilation = 348757,

    /// Brutes / Guards
    ColossalSmash = 356088,
    DefilingDreadslam = 357364,
    BeastialHowl = 333929,
    BellowingRoar = 335485,
    BlazingInferno = 357181,
    TouchOfFlame = 346121, ///< Aura on spawn/Reset
    RisingHeat = 357194, ///< Ramp up on HP %

    ///< Guards
    IronShackles = 347163,

    /// Bosses
    RainOfDespair = 362391,

    /// General Nephmir
    OptimalCoreTemperature = 367555,
    SoulflameTorrent = 357327,
    GiantSlam = 218077,
    ChargedWeapons = 310835,
    Thunderclap = 277743,

    ///< End Boss
    EphemeralBody  = 339006,
    ResonatingBody = 339010,
    Deathorb = 297047,

    SpectralWingsGuard = 346495,

    MawInfused = 361640,
    PowerUp,
};

enum DesmotareonActions
{
    ActionShirgantaiChildrenEngaged = 1,
    ActionSetGuidShirgantai,
};

const Position ShirgantaiPathOne[] =
{
    { 4531.8f, 5907.99f, 4870.22f, 5.51599f },
    { 4573.52f, 5872.93f, 4887.38f, 5.65541f },
    { 4613.19f, 5852.68f, 4908.39f, 6.15805f },
    { 4655.3f, 5850.88f, 4915.36f, 0.000529766f },
    { 4698.97f, 5851.91f, 4911.2f, 6.13842f },
    { 4729.44f, 5849.57f, 4918.56f, 6.02454f },
    { 4768.66f, 5840.02f, 4917.48f, 6.04417f },
};

using ShirPathOneSize = std::extent<decltype(ShirgantaiPathOne)>;

const Position ShirgantaiPathTwo[] =
{
    { 4768.0f, 5840.0f, 4917.0f, 5.93761f },
    { 4796.79f, 5834.92f, 4913.36f, 5.8473f },
    { 4811.7f, 5814.21f, 4910.22f, 5.19542f },
    { 4815.06f, 5783.91f, 4906.95f, 4.48857f },
    { 4798.42f, 5754.52f, 4905.34f, 3.97806f },
    { 4781.3f, 5741.83f, 4905.24f, 3.39294f },
    { 4749.32f, 5744.21f, 4906.15f, 2.90599f },
    { 4723.14f, 5757.22f, 4906.91f, 2.58791f },
    { 4704.3f, 5772.83f, 4905.76f, 2.44654f },
    { 4647.64f, 5809.2f, 4902.51f, 2.2227f },
    { 4586.18f, 5967.99f, 4916.21f, 1.56689f },
    { 4539.34f, 6006.27f, 4920.7f, 3.03166f },
    { 4480.25f, 6004.71f, 4927.11f, 3.18088f },
    { 4442.47f, 5987.86f, 4932.38f, 4.29615f },
    { 4425.33f, 5950.05f, 4932.5f, 4.41003f },
    { 4423.29f, 5912.76f, 4932.39f, 4.86555f },
    { 4444.43f, 5873.28f, 4932.14f, 5.53706f },
    { 4487.52f, 5851.48f, 4930.66f, 6.00044f },
    { 4525.29f, 5857.83f, 4926.8f, 0.180641f },
    { 4559.73f, 5855.57f, 4921.13f, 6.25962f },
    { 4607.24f, 5851.65f, 4913.82f, 6.23213f },
    { 4647.11f, 5830.41f, 4907.85f, 5.06582f },
    { 4632.49f, 5780.72f, 4903.07f, 4.02518f },
    { 4599.5f, 5766.63f, 4901.21f, 2.97667f },
    { 4554.25f, 5797.67f, 4905.37f, 2.30908f },
    { 4532.65f, 5837.55f, 4904.9f, 1.50405f },
    { 4546.63f, 5868.66f, 4902.02f, 1.01318f },
    { 4574.74f, 5876.0f, 4899.7f, 5.96119f },
    { 4601.31f, 5884.77f, 4900.66f, 0.73436f },
    { 4612.45f, 5961.72f, 4904.74f, 1.7004f },
    { 4598.82f, 5996.58f, 4906.25f, 2.12059f },
    { 4555.93f, 6028.93f, 4909.25f, 2.84315f },
    { 4504.89f, 6040.11f, 4918.2f, 4.99907f },
};

using ShirPathTwoSize = std::extent<decltype(ShirgantaiPathTwo)>;

const Position ShirgantaiPathThree[] =
{
    { 4531.8f, 5907.99f, 4870.22f, 5.51599f },
    { 4580.87f, 5860.27f, 4869.71f, 5.37462f },
    { 4593.74f, 5822.58f, 4871.0f, 5.00156f },
    { 4592.8f, 5771.61f, 4884.69f, 4.18868f },
    { 4532.76f, 5748.81f, 4893.19f, 3.26977f },
    { 4485.0f, 5765.16f, 4898.53f, 2.51971f },
    { 4448.17f, 5817.9f, 4913.45f, 1.39424f },
    { 4473.8f, 5853.43f, 4909.67f, 0.695234f },
    { 4527.44f, 5906.8f, 4880.51f, 6.00846f },
};

using ShirPathThreeSize = std::extent<decltype(ShirgantaiPathThree)>;

const Position ShirgantaiPathFour[] =
{
    { 4513.7f, 6007.27f, 4914.57f, 5.05883f },
    { 4523.9f, 5977.32f, 4905.89f, 4.99599f },
    { 4530.12f, 5951.71f, 4898.8f, 4.94495f },
    { 4535.24f, 5925.91f, 4891.58f, 4.98421f },
    { 4559.27f, 5906.3f, 4877.49f, 5.3612f },
    { 4574.94f, 5878.38f, 4865.38f, 5.29837f },
};

using ShirPathFourSize = std::extent<decltype(ShirgantaiPathFour)>;

/// 707003
struct boss_shirgantai : public BossAI
{
public:
    boss_shirgantai(Creature* creature) : BossAI(creature, BossShirgantai) { }

    enum Points
    {
        PointFirst = 1,
        PointTwo,
        PointLand,
        PointTakeOff,
        PointFour,
        PointLand2,
    };

    enum Talks
    {
        TalkIntro = 0,
        TalkChildrenEngaged,
    };

    void InitializeAI() override
    {
        DoCastSelf(StygianLaden);
        DoCastSelf(MawCosmetic);
        me->SetReactState(REACT_PASSIVE);
        me->SetUnitFlag(UnitFlags::UNIT_FLAG_NON_ATTACKABLE);
        me->GetMotionMaster()->MoveSmoothPath(PointFirst, ShirgantaiPathOne, ShirPathOneSize::value, false, true)->callbackFunc = [this]
        {
            Talk(TalkIntro);

            me->GetMotionMaster()->MoveSmoothPath(PointTwo, ShirgantaiPathTwo, ShirPathTwoSize::value, false, true)->callbackFunc = [this]
            {
                me->GetMotionMaster()->MoveLand(PointLand, { 4503.01f, 6039.34f, 4908.97f, 5.01563f });
                scheduler.Schedule(1s, [this](TaskContext /*context*/)
                {
                    me->SetFacingTo(5.139766f);
                    scheduler.CancelAll();
                });
            };
        };

        scheduler.Schedule(1s, [this](TaskContext context)
        {
            uint32 chance = 100;

            float diff = 0.0f;

            while (roll_chance_i(chance))
            {
                float x = me->GetPositionX() + frand(diff - 10.0f, 10.0f);
                float y = me->GetPositionY() + frand(diff - 10.0f, 10.0f);
                float z = me->GetPositionZ();

                if (auto spawn = me->SummonCreature(NpcSpawnOfShirgantai, { x, y, z }, TEMPSUMMON_MANUAL_DESPAWN))
                    if (spawn->AI())
                        spawn->AI()->SetGUID(me->GetGUID(), ActionSetGuidShirgantai);

                chance -= 25;
                diff += 5.0f;
            }
            context.Repeat(5s, 10s);
        });
    }

    void DoAction(int32 actionId) override
    {
        if (actionId == ActionShirgantaiChildrenEngaged)
        {
            Talk(TalkIntro);
            me->GetMotionMaster()->MoveTakeoff(PointTakeOff, { 4504.39f, 6029.07f, 4926.01f, 5.00777f });

            scheduler.Schedule(1s, [this](TaskContext /*context*/)
            {
                me->GetMotionMaster()->MoveSmoothPath(PointFour, ShirgantaiPathFour, ShirPathFourSize::value, false, true)->callbackFunc = [this]
                {
                    me->GetMotionMaster()->MoveLand(PointLand2, { 4580.08f, 5870.74f, 4843.83f, 5.71462f });

                    scheduler.Schedule(1s, [this](TaskContext /*context*/)
                    {
                        me->SetReactState(REACT_AGGRESSIVE);
                        me->RemoveUnitFlag(UnitFlags::UNIT_FLAG_NON_ATTACKABLE);
                    });
                };
            });
        }
    }

    void JustEngagedWith(Unit* who) override
    {
        _JustEngagedWith(who);
        scheduler.CancelAll();
    }

    void UpdateAI(uint32 diff) override
    {
        scheduler.Update(diff);

        if (!UpdateVictim())
            return;

        DoMeleeAttackIfReady();
    }

    void EnterEvadeMode(EvadeReason why) override
    {
        summons.DespawnAll(1s);
        BossAI::EnterEvadeMode(why);
    }
};

/// 707033
struct npc_spawn_of_shirgantai : public ScriptedAI
{
public:
    npc_spawn_of_shirgantai(Creature* creature) : ScriptedAI(creature) { }

    void InitializeAI() override
    {
        DoCastSelf(HideSpell);
        DoCastSelf(MawPortalIn);
        DoCastSelf(StygianLaden);
        DoCastSelf(MawCosmetic);
        me->SetReactState(REACT_PASSIVE);
        me->SetUnitFlag(UnitFlags::UNIT_FLAG_UNINTERACTIBLE);
        me->SetUnitFlag(UnitFlags::UNIT_FLAG_NON_ATTACKABLE);
        scheduler.Schedule(1s, [this](TaskContext /*context*/)
        {
            me->RemoveAurasDueToSpell(HideSpell);
            scheduler.Schedule(1s, [this](TaskContext /*context*/)
            {
                if (auto shirgantai = me->GetMap()->GetCreature(ShirgantaiGuid))
                    if (shirgantai->IsEngaged())
                    {
                        me->SetReactState(REACT_AGGRESSIVE);
                        me->RemoveUnitFlag(UnitFlags::UNIT_FLAG_NON_ATTACKABLE);
                    }
                me->RemoveUnitFlag(UnitFlags::UNIT_FLAG_UNINTERACTIBLE);
                //
            });
        });
    }

    void FadeOut()
    {
        Despawning = true;
        scheduler.Schedule(30ms, [this](TaskContext context)
        {
            auto pos = Position(*me);
            pos.m_positionZ -= 300.0f;
            me->StopMoving();
            me->NearTeleportTo(pos, true, true);
        });
        me->DespawnOrUnsummon(3s);
        me->SetUnitFlag(UnitFlags::UNIT_FLAG_NON_ATTACKABLE);
        me->StopMoving();
        DoCastSelf(DisappearSpell);
        DoCastSelf(MawPortalIn);
    }

    void SetGUID(ObjectGuid const& guid, int32 actionId) override
    {
        if (actionId == ActionSetGuidShirgantai)
        {
            ShirgantaiGuid = guid;

            if (auto shirgantai = me->GetMap()->GetCreature(ShirgantaiGuid))
                me->GetMotionMaster()->MoveFollow(shirgantai, 5.0f, me->GetAngle(*shirgantai));
        }
    }

    void JustDied(Unit* /*killer*/) override
    {
        me->DespawnOrUnsummon(2s);
    }

    void Reset() override
    {

    }

    void UpdateAI(uint32 diff) override
    {
        scheduler.Update(diff);

        if (Despawning)
            return;

        if (!me->IsEngaged())
        {
            DespawnTimer += diff;
            if (DespawnTimer >= 10000)
            {
                FadeOut();
            }
        }
        else
            DespawnTimer = 0;

        if (!UpdateVictim())
            return;

        DoMeleeAttackIfReady();
    }

    bool Despawning = false;
    uint32 DespawnTimer = 0;
    TaskScheduler scheduler;
    ObjectGuid ShirgantaiGuid;
};

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

struct boss_xarvius : public BossAI
{
public:
    boss_xarvius(Creature* creature) : BossAI(creature, BossXarvius) { }

    enum Talks
    {

    };

    void InitializeAI()
    {
        me->SetReactState(REACT_PASSIVE);
        me->SetUnitFlag(UNIT_FLAG_NON_ATTACKABLE);
    }

    void JustEngagedWith(Unit* who) override
    {
        _JustEngagedWith(who);

        DoCastSelf(RainOfDespair);

        scheduler.Schedule(1s, [this](TaskContext context)
        {

        });
    }

    void UpdateAI(uint32 diff)
    {
        if (!UpdateVictim())
            return;

        scheduler.Update(diff);
        events.Update(diff);

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        while (uint32 eventId = events.ExecuteEvent())
        {
            ExecuteEvent(eventId);
            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;
        }

        DoMeleeAttackIfReady();
    }

    bool didIntro = false;

    void MoveInLineOfSight(Unit* who) override
    {
        BossAI::MoveInLineOfSight(who);

        if (!didIntro)
        {
            didIntro = true;
            DoSummon(707023, { 4653.7f, 5849.3f, 4857.77f, 0.0190654f }, 0s, TEMPSUMMON_DEAD_DESPAWN);
            return;
        }
    }

    void EnterEvadeMode(EvadeReason why) override
    {
        BossAI::EnterEvadeMode(why);
        _DespawnAtEvade(3s);
    }
};

struct npc_charger_of_the_damned : public ScriptedAI
{
public:
    npc_charger_of_the_damned(Creature* creature) : ScriptedAI(creature) { }

    void InitializeAI()
    {
        me->SetReactState(REACT_PASSIVE);
        me->SetUnitFlag(UNIT_FLAG_NON_ATTACKABLE);
        me->GetMotionMaster()->MovePoint(1, { 4698.62f, 5856.69f, 4867.97f, 6.17266f })->callbackFunc = [this]
        {
            if (auto xarvius = me->FindNearestCreature(707009, 10.0f))
            {
                xarvius->CastSpell(me, 46598, true);
                xarvius->GetScheduler().Schedule(1100ms, [this, xarvius](TaskContext context)
                {
                    xarvius->RemoveAurasDueToSpell(46598);
                    me->DespawnOrUnsummon();
                    xarvius->Mount(98542, 0u, 0u);
                    xarvius->SetReactState(REACT_AGGRESSIVE);
                    xarvius->RemoveUnitFlag(UNIT_FLAG_NON_ATTACKABLE);
                });
            }
        };
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

// 707000 - npc_general_nephmir_707000
struct npc_general_nephmir_707000 : public BossAI
{
public:
    npc_general_nephmir_707000(Creature* creature) : BossAI(creature, BossGeneralNephmir) { ApplyAllImmunities(true); }

    enum Talks
    {
        TalkEngingHostileEntities = 0,   ///< Used
        TalkSecurityMeasuresActivated,   ///< Used
        TalkIntruderDetected,            ///< Used
        TalkArmingWeapons,               ///< Used
        TalkAggressionProtocolInitiated, ///< Used
        TalkDeath,                       ///< Used
        TalkKilled,                      ///< Used
        TalkIdle,                        ///< Used
    };

    void JustEngagedWith(Unit* who) override
    {
        _JustEngagedWith(who);
        scheduler.CancelAll();

        Talk(TalkEngingHostileEntities);

        scheduler.Schedule(15s, [this](TaskContext context)
        {
            NextIntruderDetectTime = 0;
            Talk(TalkSecurityMeasuresActivated);
            DoCast(SoulflameTorrent);
            scheduler.Schedule(3s, [this](TaskContext context)
            {
                Talk(TalkIdle);
            });
            context.Repeat(30s, 40s);
        });

        scheduler.Schedule(4s, [this](TaskContext context)
        {
            DoCast(GiantSlam);
            context.Repeat(15s, 20s);
        });

        scheduler.Schedule(30s, [this](TaskContext context)
        {
            Talk(TalkArmingWeapons);
            DoCast(ChargedWeapons);
        });

        scheduler.Schedule(30s, [this](TaskContext context)
        {
            DoCast(Thunderclap);
            context.Repeat(15s, 20s);
        });
    }

    void JustDied(Unit* /*who*/) override
    {
        _JustDied();
        Talk(TalkDeath);
    }

    void DamageDealt(Unit* victim, uint32& damage, DamageEffectType type, SpellInfo const* spellInfo /*= nullptr*/) override
    {
        if (spellInfo && spellInfo->Id == 357333 && type != DamageEffectType::DOT)
        {
            auto now = GameTime::GetGameTime();
            if (now >= NextIntruderDetectTime)
            {
                NextIntruderDetectTime = now + 60;
                Talk(TalkIntruderDetected);
            }
        }

        if (spellInfo && victim)
        {
            switch (spellInfo->Id)
            {
                case 357333: ///< Soulflame Torrent
                    if (type != DamageEffectType::DOT)
                        damage = victim->CountPctFromMaxHealth(50);

                    if (instance)
                        if (auto challenge = instance->GetChallenge())
                            damage += 5 * challenge->GetChallengeLevel();
                    break;
                case GiantSlam:
                    damage = victim->CountPctFromMaxHealth(50);

                    if (instance)
                        if (auto challenge = instance->GetChallenge())
                            damage += 5 * challenge->GetChallengeLevel();
                    break;
                case 308864: ///< Charged Weapons
                    damage = victim->CountPctFromMaxHealth(30);

                    if (instance)
                        if (auto challenge = instance->GetChallenge())
                            damage += 5 * challenge->GetChallengeLevel();
                    break;
            }
        }
    }

    time_t NextKillTime;
    time_t NextIntruderDetectTime;

    void KilledUnit(Unit* who) override
    {
        BossAI::KilledUnit(who);
        if (who->IsPlayer())
        {
            auto now = GameTime::GetGameTime();
            if (now >= NextKillTime)
            {
                NextKillTime = now + 10;
                Talk(TalkKilled);
            }
        }
    }

    void UpdateAI(uint32 diff)
    {
        if (!UpdateVictim())
            return;

        scheduler.Update(diff);
        events.Update(diff);

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        while (uint32 eventId = events.ExecuteEvent())
        {
            ExecuteEvent(eventId);
            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;
        }

        DoMeleeAttackIfReady();
    }

    void EnterEvadeMode(EvadeReason why) override
    {
        BossAI::EnterEvadeMode(why);
        _DespawnAtEvade(3s);
    }

    void DamageTaken(Unit* attacker, uint32& damage, DamageEffectType /*damageType*/, SpellInfo const* /*spellInfo = nullptr*/) override
    {
        if (!phased && me->HealthBelowPctDamaged(51, damage))
        {
            phased = true;
            scheduler.DelayAll(5s);
            scheduler.Schedule(1s, [this](TaskContext /*context*/)
            {
                me->CastSpell(me, OptimalCoreTemperature, CastSpellExtraArgs(true).AddSpellBP0(50));
                Talk(TalkAggressionProtocolInitiated);
            });
        }
    }

    bool phased = false;
};

/// ID: 310835 Charged Weapons
class spell_charged_weapons : public AuraScript
{
    PrepareAuraScript(spell_charged_weapons);

    enum ChargedWeapon
    {
        ChargedWeaponStun = 306875,
        ChargedWeaponDmg = 308864,
        ChargedWeaponStacks = 308864,
    };

    void HandleProc(ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();

        if (auto caster = GetCaster())
        {
            if (auto target = eventInfo.GetActionTarget())
            {
                if (auto aur = target->GetAura(ChargedWeaponStacks))
                {
                    if (aur->GetStackAmount() >= 9)
                    {
                        aur->Remove();
                        caster->CastSpell(target, ChargedWeaponStun, true);
                        caster->CastSpell(target, ChargedWeaponDmg, true);
                    }
                }
            }
        }
    }

    void Register() override
    {
        OnProc += AuraProcFn(spell_charged_weapons::HandleProc);
    }
};

// 708019 - npc_vicious_souleater_708019
struct npc_vicious_souleater_708019 : public ScriptedAI
{
public:
    npc_vicious_souleater_708019(Creature* creature) : ScriptedAI(creature) { }

    void InitializeAI() override
    {
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

// 707004 - npc_ecidus_707004
struct npc_ecidus_707004 : public BossAI
{
public:
    npc_ecidus_707004(Creature* creature) : BossAI(creature, BossEcidus) { ApplyAllImmunities(true); }

    enum eEcidus
    {
        /// Ecidus
        DeathWave = 357871,
        SoulEcho = 297024,
        SpellRitualOfSlaughter = 354240,

    };

    enum Talks
    {
        TalkAggro = 0,
        TalkDied,
        TalkKilled,
        TalkAwayWithYou,
    };

    void JustEngagedWith(Unit* who) override
    {
        _JustEngagedWith(who);
        scheduler.CancelAll();

        Talk(TalkAggro);

        scheduler.Schedule(15s, [this](TaskContext context)
        {
            NextIntruderDetectTime = 0;
            Talk(TalkAwayWithYou);
            DoCast(DeathWave);
            context.Repeat(30s, 40s);
        });

        scheduler.Schedule(1s, [this](TaskContext context)
        {
            DoCast(SoulEcho);
            context.Repeat(15s, 20s);
        });

        scheduler.Schedule(30s, [this](TaskContext context)
        {
            DoCast(ChargedWeapons);
        });
    }

    void JustDied(Unit* /*who*/) override
    {
        _JustDied();
        Talk(TalkDied);
    }

    void DamageDealt(Unit* victim, uint32& damage, DamageEffectType type, SpellInfo const* spellInfo /*= nullptr*/) override
    {
        if (spellInfo && victim)
        {
            switch (spellInfo->Id)
            {
                case DeathWave:
                case 297028: ///< Soul Echo Missle DMG
                    if (type != DamageEffectType::DOT)
                        damage = victim->CountPctFromMaxHealth(80);

                    if (instance)
                        if (auto challenge = instance->GetChallenge())
                            damage += 5 * challenge->GetChallengeLevel();
                    break;
                case 308864: ///< Charged Weapons
                    damage = victim->CountPctFromMaxHealth(30);

                    if (instance)
                        if (auto challenge = instance->GetChallenge())
                            damage += 5 * challenge->GetChallengeLevel();
                    break;
                default:
                    break;
            }
        }
    }

    bool CanCastSpellWhileMoving(SpellInfo const* info) const
    {
        return info->Id == SoulEcho;
    }

    time_t NextKillTime;
    time_t NextIntruderDetectTime;

    void KilledUnit(Unit* who) override
    {
        BossAI::KilledUnit(who);
        if (who->IsPlayer())
        {
            auto now = GameTime::GetGameTime();
            if (now >= NextKillTime)
            {
                NextKillTime = now + 10;
                Talk(TalkKilled);
            }
        }
    }

    void UpdateAI(uint32 diff)
    {
        if (!UpdateVictim())
            return;

        scheduler.Update(diff);
        events.Update(diff);

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        while (uint32 eventId = events.ExecuteEvent())
        {
            ExecuteEvent(eventId);
            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;
        }

        DoMeleeAttackIfReady();
    }


    void EnterEvadeMode(EvadeReason why) override
    {
        BossAI::EnterEvadeMode(why);
        _DespawnAtEvade(3s);
    }

    void DamageTaken(Unit* attacker, uint32& damage, DamageEffectType /*damageType*/, SpellInfo const* /*spellInfo = nullptr*/) override
    {
        if (!phased && me->HealthBelowPctDamaged(51, damage))
        {
            phased = true;
            scheduler.DelayAll(5s);
            scheduler.Schedule(1s, [this](TaskContext /*context*/)
            {
                me->CastStop();
                me->CastSpell(me, PowerUp);
            });
        }
    }

    bool phased = false;
};

void AddSC_Desmotareon()
{
    RegisterCreatureAI(boss_shirgantai);
    RegisterCreatureAI(npc_spawn_of_shirgantai);
    RegisterCreatureAI(npc_portal_707027);
    RegisterCreatureAI(boss_xarvius);
    RegisterCreatureAI(npc_charger_of_the_damned);
    RegisterCreatureAI(npc_soul_portal_708018);
    RegisterCreatureAI(npc_soul_harvester_trigger_708010);
    RegisterCreatureAI(npc_general_nephmir_707000);
    RegisterCreatureAI(npc_vicious_souleater_708019);
    RegisterCreatureAI(npc_ecidus_707004);

    FieryPlegm::Register();
    DarkDischarge::Register();
    SaltySpittle::Register();

    RegisterSpellScript(spell_blazing_inferno);
    RegisterSpellScript(spell_soul_echo);
    RegisterSpellScript(spell_ritual_of_slaughter);
    RegisterSpellScript(spell_death_orb);
    RegisterSpellScript(spell_soulflame_torrent);
    RegisterSpellScript(spell_charged_weapons);

    RegisterAreaTriggerAI(at_death_orb);
    RegisterAreaTriggerAI(at_defiling_dreadslam);
}
