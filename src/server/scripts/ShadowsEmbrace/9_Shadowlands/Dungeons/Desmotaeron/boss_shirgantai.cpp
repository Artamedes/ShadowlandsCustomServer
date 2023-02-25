#include "Desmotaeron.h"

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

const Position AnimaOrbPosition(4546.86f, 5900.87f, 4843.98f, 5.5123f);
const Position IsynthPosition(4468.4f, 5838.84f, 4947.85f, 0.458272f);
const Position GiebiPosition(4569.18f, 5989.06f, 4944.93f, 4.6341f);

enum eShirgantai
{
    NpcAnimaOrb   = 707035,
    NpcShirgantai = 707003,
    NpcIsynth     = 707020,
    NpcGielbi     = 707021,
};

enum eShirgantaiSpells
{
    // Dragons cast -
    FieryPhlegmCast     = 357640,
    DarkDischargeCast   = 357643,
    SaltySpittleCast    = 357644,
    DeadlyHunger        = 336838, ///< Cast every 10s, they have to walk out of melee
    CrushingBite        = 343722,
    CripplingBlow       = 166766, ///< Cast every 15s
    WingBlast           = 335853,
    SoulShift           = 357516,
};

void ApplySpellDamageIfNeed(Creature* me, Unit* who, SpellInfo const* spellInfo, DamageEffectType type,  uint32& damage)
{
    if (spellInfo && who)
    {
        switch (spellInfo->Id)
        {
            case 357620: ///< Salty Spittle
            case 357643: ///< Dark Discharge
            case 357619: ///< Fiery Plegm
                damage += 500000 + who->CountPctFromMaxHealth(50);
                ApplyChallengeDMGIncrease(me, damage, 5);
                break;


            case 357634: ///< Fiery Plegm
            case 357635: ///< Dark Discharge
            case 357636: ///< Salty Spittle
                damage += 150000 + who->CountPctFromMaxHealth(5);
                ApplyChallengeDMGIncrease(me, damage, 5);
                break;

            case CrushingBite: ///< Crushing Bite

                if (type == DamageEffectType::DOT)
                    damage += 100000 + who->CountPctFromMaxHealth(5);
                else
                    damage += 300000;

                ApplyChallengeDMGIncrease(me, damage, 5);

                break;

            case CripplingBlow:
                damage += 75000;
                ApplyChallengeDMGIncrease(me, damage, 5);
                break;
        }
    }
}

void SetupDragonSpells(TaskScheduler& scheduler, Creature* me, CreatureAI* ai)
{
    scheduler.Schedule(10s, [me, ai](TaskContext context)
    {
        if (me->IsWithinMeleeRange(me->GetVictim()))
        {
            ai->DoCastVictim(DeadlyHunger);
            context.Repeat(10s);
        }
        else
            context.Repeat(1s);
    });

    scheduler.Schedule(15s, [me, ai](TaskContext context)
    {
        if (me->IsWithinMeleeRange(me->GetVictim()))
        {
            ai->DoCastVictim(CripplingBlow);
            context.Repeat(15s);
        }
        else
            context.Repeat(1s);
    });

    scheduler.Schedule(25s, [me, ai](TaskContext context)
    {
        ai->DoCastVictim(WingBlast);
        context.Repeat(25s);
    });

    scheduler.Schedule(15s, [me, ai](TaskContext context)
    {
        ai->DoCastVictim(SoulShift);
        context.Repeat(15s);
    });

    scheduler.Schedule(20s, [me, ai](TaskContext context)
    {
        ai->DoCastVictim(CrushingBite);
        context.Repeat(35s);
    });

    switch (me->GetEntry())
    {
        case NpcShirgantai:
            scheduler.Schedule(5s, [me, ai](TaskContext context)
            {
                ai->DoCastVictim(DarkDischargeCast);
                context.Repeat(25s);
            });
            break;
        case NpcIsynth:
            scheduler.Schedule(5s, [me, ai](TaskContext context)
            {
                ai->DoCastVictim(SaltySpittleCast);
                context.Repeat(25s);
            });
            break;
        case NpcGielbi:
            scheduler.Schedule(5s, [me, ai](TaskContext context)
            {
                ai->DoCastVictim(FieryPhlegmCast);
                context.Repeat(25s);
            });
            break;
        default:
            break;
    }
}

/// 707003
struct boss_shirgantai : public BossAI
{
public:
    boss_shirgantai(Creature* creature) : BossAI(creature, BossShirgantai)
    {
        ApplyAllImmunities(true);
    }

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

        if (instance && instance->GetBossState(BossShirgantai) != NOT_STARTED)
        {
            me->SetVisible(false);
            updateScheduler.Schedule(1s, [this](TaskContext context)
            {
                me->NearTeleportTo({ 4503.97f, 6036.34f, 4908.97f, 4.99994f }, true, true);
                me->SetVisible(true);

                if (auto orb = DoSummon(NpcAnimaOrb, AnimaOrbPosition, 0s, TEMPSUMMON_MANUAL_DESPAWN))
                    if (orb->AI())
                        orb->AI()->SetGUID(me->GetGUID(), ActionSetGuidShirgantai);
            });
        }
        else
        {
            me->GetMotionMaster()->MoveSmoothPath(PointFirst, ShirgantaiPathOne, ShirPathOneSize::value, false, true)->callbackFunc = [this]
            {
                Talk(TalkIntro);

                me->GetMotionMaster()->MoveSmoothPath(PointTwo, ShirgantaiPathTwo, ShirPathTwoSize::value, false, true)->callbackFunc = [this]
                {
                    me->GetMotionMaster()->MoveLand(PointLand, { 4503.01f, 6039.34f, 4908.97f, 5.01563f });
                    updateScheduler.Schedule(1s, [this](TaskContext /*context*/)
                    {
                        me->SetFacingTo(5.139766f);
                        updateScheduler.CancelAll();

                        if (auto orb = DoSummon(NpcAnimaOrb, AnimaOrbPosition, 0s, TEMPSUMMON_MANUAL_DESPAWN))
                            if (orb->AI())
                                orb->AI()->SetGUID(me->GetGUID(), ActionSetGuidShirgantai);
                    });
                };
            };

            updateScheduler.Schedule(1s, [this](TaskContext context)
            {
                uint32 chance = 100;

                float diff = 0.0f;

                while (roll_chance_i(chance))
                {
                    float x = me->GetPositionX() + frand(diff - 10.0f, 10.0f);
                    float y = me->GetPositionY() + frand(diff - 10.0f, 10.0f);
                    float z = me->GetPositionZ();

                    if (auto spawn = me->SummonCreature(NpcSpawnOfShirgantai, { x, y, z }, TEMPSUMMON_MANUAL_DESPAWN, 0))
                        if (spawn->AI())
                            spawn->AI()->SetGUID(me->GetGUID(), ActionSetGuidShirgantai);

                    chance -= 25;
                    diff += 5.0f;
                }
                context.Repeat(5s, 10s);
            });
        }
    }

    void DoAction(int32 actionId) override
    {
        if (actionId == ActionShirgantaiOrbClicked)
        {
            DoCastSelf(DisappearSpell);
            updateScheduler.Schedule(1s, [this](TaskContext /*context*/)
            {
                Talk(TalkChildrenEngaged);
                me->NearTeleportTo({ 4534.21f, 5912.86f, 4844.5f, 5.46151f }, true, true);
                DoCast(MawPortalIn);

                updateScheduler.Schedule(1s, [this](TaskContext /*context*/)
                {
                    me->SetReactState(REACT_AGGRESSIVE);
                    me->RemoveUnitFlag(UnitFlags::UNIT_FLAG_NON_ATTACKABLE);
                    DoZoneInCombat();
                });
            });
            //Talk(TalkIntro);
            //me->GetMotionMaster()->MoveTakeoff(PointTakeOff, { 4504.39f, 6029.07f, 4926.01f, 5.00777f });
            //
            //updateScheduler.Schedule(1s, [this](TaskContext /*context*/)
            //{
            //    me->GetMotionMaster()->MoveSmoothPath(PointFour, ShirgantaiPathFour, ShirPathFourSize::value, false, true)->callbackFunc = [this]
            //    {
            //        me->GetMotionMaster()->MoveLand(PointLand2, { 4580.08f, 5870.74f, 4843.83f, 5.71462f });
            //
            //        updateScheduler.Schedule(1s, [this](TaskContext /*context*/)
            //        {
            //            me->SetReactState(REACT_AGGRESSIVE);
            //            me->RemoveUnitFlag(UnitFlags::UNIT_FLAG_NON_ATTACKABLE);
            //        });
            //    };
            //});


        }
    }

    void JustEngagedWith(Unit* who) override
    {
        _JustEngagedWith(who);
        scheduler.CancelAll();

        DoSummon(NpcIsynth, IsynthPosition, 0s, TEMPSUMMON_MANUAL_DESPAWN);
        DoSummon(NpcGielbi, GiebiPosition, 0s, TEMPSUMMON_MANUAL_DESPAWN);
        SetupDragonSpells(scheduler, me, this);
    }

    void JustSummoned(Creature* summon) override
    {
        summons.Summon(summon);
    }

    void UpdateAI(uint32 diff) override
    {
        updateScheduler.Update(diff);

        if (!UpdateVictim())
            return;

        scheduler.Update(diff);

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        DoMeleeAttackIfReady();
    }

    void EnterEvadeMode(EvadeReason why) override
    {
        summons.DespawnAll(1s);
        _DespawnAtEvade(5s);
        BossAI::EnterEvadeMode(why);
    }

    void DamageDealt(Unit* victim, uint32& damage, DamageEffectType type, SpellInfo const* spellInfo /*= nullptr*/) override
    {
        ApplySpellDamageIfNeed(me, victim, spellInfo, type, damage);
    }

    TaskScheduler updateScheduler;
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
                {
                    if (shirgantai->IsEngaged())
                    {
                        me->SetReactState(REACT_AGGRESSIVE);
                        me->RemoveUnitFlag(UnitFlags::UNIT_FLAG_NON_ATTACKABLE);
                        DoZoneInCombat();
                    }
                }
                me->RemoveUnitFlag(UnitFlags::UNIT_FLAG_UNINTERACTIBLE);
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

// 707035 - npc_anima_orb_707035
struct npc_anima_orb_707035 : public ScriptedAI
{
public:
    npc_anima_orb_707035(Creature* creature) : ScriptedAI(creature) { }

    bool wasUsed = false;

    void OnSpellClick(Unit* clicker, bool /*spellclickHandled*/) override
    {
        if (!wasUsed)
        {
            wasUsed = true;

            if (auto shirgantai = ObjectAccessor::GetCreature(*me, ShirgantaiGuid))
                if (shirgantai->AI())
                    shirgantai->AI()->DoAction(ActionShirgantaiOrbClicked);
            me->DespawnOrUnsummon();
        }
    }

    void SetGUID(ObjectGuid const& guid, int32 actionId) override
    {
        if (actionId == ActionSetGuidShirgantai)
        {
            ShirgantaiGuid = guid;
        }
    }

    ObjectGuid ShirgantaiGuid;
};

const Position GielbiPath[] =
{
    { 4569.18f, 5989.06f, 4944.93f, 4.6341f },
    { 4542.3f, 5931.87f, 4861.75f, 4.85416f },
};

using GielbiPathSize = std::extent<decltype(GielbiPath)>;

// 707021 - npc_gielbi_707021
struct npc_gielbi_707021 : public ScriptedAI
{
public:
    npc_gielbi_707021(Creature* creature) : ScriptedAI(creature)
    {
        scheduler.SetValidator([this]
        {
            return !me->HasUnitState(UNIT_STATE_CASTING);
        });

        ApplyAllImmunities(true);
    }

    void InitializeAI()
    { 
        DoCastSelf(HideSpell);
        DoCastSelf(MawPortalIn);
        me->SetReactState(REACT_PASSIVE);
        me->SetUnitFlag(UnitFlags::UNIT_FLAG_UNINTERACTIBLE);
        me->SetUnitFlag(UnitFlags::UNIT_FLAG_NON_ATTACKABLE);
        oocScheduler.Schedule(1s, [this](TaskContext /*context*/)
        {
            me->RemoveAurasDueToSpell(HideSpell);
            me->GetMotionMaster()->MoveSmoothPath(1, GielbiPath, GielbiPathSize::value, false, true)->callbackFunc = [this]
            {
                me->GetMotionMaster()->MoveLand(1, { 4542.28f, 5931.82f, 4845.31f, 4.83007f })->callbackFunc = [this]
                {
                    oocScheduler.Schedule(500ms, [this](TaskContext /*context*/)
                    {
                        me->SetReactState(REACT_AGGRESSIVE);
                        me->RemoveUnitFlag(UnitFlags::UNIT_FLAG_UNINTERACTIBLE);
                        me->RemoveUnitFlag(UnitFlags::UNIT_FLAG_NON_ATTACKABLE);
                        DoZoneInCombat();
                    });
                };
            };
        });
    }

    void JustEngagedWith(Unit* /*who*/) override
    {
        scheduler.CancelAll();
        SetupDragonSpells(scheduler, me, this);
    }

    void UpdateAI(uint32 diff) override
    {
        oocScheduler.Update(diff);

        if (!UpdateVictim())
            return;

        scheduler.Update(diff);

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        DoMeleeAttackIfReady();
    }

    void DamageDealt(Unit* victim, uint32& damage, DamageEffectType type, SpellInfo const* spellInfo /*= nullptr*/) override
    {
        ApplySpellDamageIfNeed(me, victim, spellInfo, type, damage);
    }

    TaskScheduler scheduler;
    TaskScheduler oocScheduler;
};

const Position IsynthPath[] =
{
    { 4468.4f, 5838.84f, 4947.85f, 0.458272f },
    { 4525.2f, 5885.7f, 4865.38f, 0.556324f },
};

using IsynthPathSize = std::extent<decltype(IsynthPath)>;

// 707020 - npc_isynth_707020
struct npc_isynth_707020 : public ScriptedAI
{
public:
    npc_isynth_707020(Creature* creature) : ScriptedAI(creature)
    {
        scheduler.SetValidator([this]
        {
            return !me->HasUnitState(UNIT_STATE_CASTING);
        });

        ApplyAllImmunities(true);
    }

    void InitializeAI()
    { 
        DoCastSelf(HideSpell);
        DoCastSelf(MawPortalIn);
        me->SetReactState(REACT_PASSIVE);
        me->SetUnitFlag(UnitFlags::UNIT_FLAG_UNINTERACTIBLE);
        me->SetUnitFlag(UnitFlags::UNIT_FLAG_NON_ATTACKABLE);
        oocScheduler.Schedule(1s, [this](TaskContext /*context*/)
        {
            me->RemoveAurasDueToSpell(HideSpell);
            me->GetMotionMaster()->MoveSmoothPath(1, IsynthPath, IsynthPathSize::value, false, true)->callbackFunc = [this]
            {
                me->GetMotionMaster()->MoveLand(1, { 4525.15f, 5885.67f, 4842.89f, 0.163625f })->callbackFunc = [this]
                {
                    oocScheduler.Schedule(500ms, [this](TaskContext /*context*/)
                    {
                        me->SetReactState(REACT_AGGRESSIVE);
                        me->RemoveUnitFlag(UnitFlags::UNIT_FLAG_UNINTERACTIBLE);
                        me->RemoveUnitFlag(UnitFlags::UNIT_FLAG_NON_ATTACKABLE);
                        DoZoneInCombat();
                    });
                };
            };
        });
    }

    void JustEngagedWith(Unit* /*who*/) override
    {
        scheduler.CancelAll();
        SetupDragonSpells(scheduler, me, this);
    }

    void UpdateAI(uint32 diff) override
    {
        oocScheduler.Update(diff);

        if (!UpdateVictim())
            return;

        scheduler.Update(diff);

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        DoMeleeAttackIfReady();
    }

    void DamageDealt(Unit* victim, uint32& damage, DamageEffectType type, SpellInfo const* spellInfo /*= nullptr*/) override
    {
        ApplySpellDamageIfNeed(me, victim, spellInfo, type, damage);
    }

    TaskScheduler scheduler;
    TaskScheduler oocScheduler;
};

void AddSC_boss_shirgantai()
{
    RegisterCreatureAI(boss_shirgantai);
    RegisterCreatureAI(npc_spawn_of_shirgantai);
    RegisterCreatureAI(npc_anima_orb_707035);
    RegisterCreatureAI(npc_gielbi_707021);
    RegisterCreatureAI(npc_isynth_707020);
}
