#include "AreaTrigger.h"
#include "AreaTriggerAI.h"
#include "SpellMgr.h"
#include "Unit.h"
#include "SpellScript.h"
#include "SpellAuras.h"
#include "GameTime.h"
#include "SpellAuraEffects.h"

enum SpellVenthyr
{
    SwarmingMist           = 311648, ///< 1.0
    SinfulBrand            = 317009, ///< 1.0
    RavenousFrenzy         = 323546, ///< 3.0
    FlayedShot             = 324149, ///< 0.5
    MirrorsOfTorment       = 314793, ///< 1.5
    FallenOrder            = 326860, ///< 3.0
    AshenHallow            = 316958, ///< 4.0
    Mindgames              = 323673, ///< 0.8
    Flagellation           = 323654, ///< 1.5
    ChainHarvest           = 320674, ///< 1.4
    ImpendingCatasatrophe  = 321792, ///< 1.0
    Condemn                = 317320, ///< 1.0
};

const std::unordered_map<uint32,float> VenthyrWastelandProprietyRates =
{
    { SwarmingMist,           1.0f },
    { SinfulBrand,            1.0f },
    { RavenousFrenzy,         3.0f },
    { FlayedShot,             0.5f },
    { MirrorsOfTorment,       1.5f },
    { FallenOrder,            3.0f },
    { AshenHallow,            4.0f },
    { Mindgames,              0.8f },
    { Flagellation,           1.5f },
    { ChainHarvest,           1.4f },
    { ImpendingCatasatrophe,  1.0f },
    { Condemn,                1.0f },
};

// 300728
class spell_door_of_shadows : public SpellScript
{
    PrepareSpellScript(spell_door_of_shadows);

    enum DoorOfShadows
    {
        FancyFootworksAura  = 331577,
        AgentOfChaos        = 331576,
        AgentOfChaosTrigger = 331866,
        WatchTheShoes       = 336140,
        EnduringGloom       = 319978,
        EnduringGloomBuff   = 321012,
    };

    void HandleScript(SpellEffIndex /*eff*/)
    {
        if (GetCaster())
        {
            // TODO: add a way to callback on teleport
            GetCaster()->GetScheduler().Schedule(50ms, [](TaskContext context)
            {
                auto caster = context.GetUnit();
                if (caster->HasAura(AgentOfChaos))
                    caster->CastSpell(caster, AgentOfChaosTrigger, true);
                if (caster->HasAura(WatchTheShoes))
                    caster->RemoveAurasWithMechanic(1 << MECHANIC_ROOT);
                if (caster->HasAura(EnduringGloom))
                    caster->CastSpell(caster, EnduringGloomBuff, CastSpellExtraArgs(true).AddSpellBP0(caster->CountPctFromMaxHealth(20)));
            });
        }
    }

    void HandleDisorient(SpellEffIndex effIndex)
    {
        PreventHitDefaultEffect(effIndex);
    }

    void HandleTrigger(SpellEffIndex effIndex)
    {
        if (!GetCaster() || !GetCaster()->HasAura(FancyFootworksAura))
            PreventHitDefaultEffect(effIndex);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_door_of_shadows::HandleScript, EFFECT_0, SPELL_EFFECT_TELEPORT_UNITS);
        OnEffectLaunch += SpellEffectFn(spell_door_of_shadows::HandleDisorient, EFFECT_1, SPELL_EFFECT_TRIGGER_SPELL);
        OnEffectLaunch += SpellEffectFn(spell_door_of_shadows::HandleTrigger, EFFECT_2, SPELL_EFFECT_TRIGGER_SPELL);
    }
};

// ID - 331586 Thrill Seeker
class spell_thrill_seeker : public AuraScript
{
    PrepareAuraScript(spell_thrill_seeker);

    enum ThrillSeeker
    {
        ThrillSeekerCharge = 331939,
        ThrillSeekerHasteBuff = 331937,
    };

    void HandleDummy(AuraEffect const* /*aurEff*/)
    {
        if (auto caster = GetTarget())
        {
            if (caster->HasAura(ThrillSeekerHasteBuff))
                return;

            auto thrillSeekerAura = caster->GetAura(ThrillSeekerCharge);

            // lambda functions for easier access of the aura pointer
            auto addStackOrCreate([caster, thrillSeekerAura]()
            {
                if (thrillSeekerAura)
                    thrillSeekerAura->ModStackAmount(1);
                else
                    caster->AddAura(ThrillSeekerCharge, caster);
            });

            auto dropStack([thrillSeekerAura]() -> bool
            {
                if (thrillSeekerAura)
                    thrillSeekerAura->DropStack();

                return false;
            });

            auto getStacks([thrillSeekerAura]() -> uint32
            {
                if (thrillSeekerAura)
                    return thrillSeekerAura->GetStackAmount();

                return 0;
            });

            if (caster->IsInCombat())
            {
                if (getStacks() < 40)
                    addStackOrCreate();
                else
                {
                    caster->RemoveAurasDueToSpell(ThrillSeekerCharge); // remove all charges.
                    // grant haste buff
                    caster->CastSpell(caster, ThrillSeekerHasteBuff, true);
                }
            }
            else
            {
                // drop stack if needed
                dropStack();
            }
        }
    }

    void HandleProc(AuraEffect* /*aurEff*/, ProcEventInfo& /*eventInfo*/)
    {
        if (Unit* caster = GetCaster())
        {
            // grand 4 stacks on a kill
            auto thrillSeekerAura = caster->GetAura(ThrillSeekerCharge);
            if (thrillSeekerAura)
                thrillSeekerAura->ModStackAmount(4);
            else
            {
                if (auto aura = caster->AddAura(ThrillSeekerCharge, caster))
                    aura->ModStackAmount(4);
            }
        }
    }

    void Register() override
    {
        OnEffectProc += AuraEffectProcFn(spell_thrill_seeker::HandleProc, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_thrill_seeker::HandleDummy, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

// ID - 331937 Euphoria
class spell_thrill_seeker_haste : public AuraScript
{
    PrepareAuraScript(spell_thrill_seeker_haste);

    enum ThrillSeeker
    {
        FatalFlawConduit = 352373,
        FatalFlawCrit = 354053,
        FatalFlawVers = 354054,
    };

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* caster = GetCaster())
        {
            if (auto player = caster->ToPlayer())
            {
                if (player->HasAura(FatalFlawConduit))
                {
                    if (player->m_activePlayerData->Versatility >= player->m_activePlayerData->CritPercentage)
                        player->CastSpell(player, FatalFlawVers, true);
                    else
                        player->CastSpell(player, FatalFlawCrit, true);
                }
            }
        }
    }

    void Register() override
    {
        OnEffectRemove += AuraEffectRemoveFn(spell_thrill_seeker_haste::HandleRemove, EFFECT_0, SPELL_AURA_MELEE_SLOW, AURA_EFFECT_HANDLE_REAL);
    }
};

/// ID - 21260, Soothing Shade
struct at_soothing_shade : AreaTriggerAI
{
    at_soothing_shade(AreaTrigger* at) : AreaTriggerAI(at)
    {
    }

    enum SoothingShade
    {
        SoothingShadeBuff = 336885,
        ItsAlwaysTeaTime = 351747,
        ItsAlwaysTeaTimeProc = 353334,
    };

    void OnUnitEnter(Unit* unit) override
    {
        Unit* caster = at->GetCaster();

        if (caster && caster == unit)
        {
            if (auto aura = caster->AddAura(SoothingShadeBuff, caster))
            {
                aura->SetDuration(at->GetDuration());
                if (at->GetCaster()->HasAura(ItsAlwaysTeaTime))
                    at->GetCaster()->CastSpell(at->GetCaster(), ItsAlwaysTeaTimeProc, true);
            }
        }
    }

    void OnUnitExit(Unit* unit) override
    {
        Unit* caster = at->GetCaster();

        if (caster && caster == unit)
        {
            caster->RemoveAurasDueToSpell(SoothingShadeBuff);
            caster->RemoveAurasDueToSpell(ItsAlwaysTeaTimeProc);
        }
    }
};

/// ID - 336245 Token of Appreciation
class spell_token_of_appreciation : public AuraScript
{
    PrepareAuraScript(spell_token_of_appreciation);

    enum TokenOfApperication
    {
        CooldownAura = 337471,
        ShieldAura   = 337470,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetActionTarget() == nullptr || eventInfo.GetActor() == nullptr)
            return false;

        if (eventInfo.GetActionTarget() == eventInfo.GetActor())
            return false;

        if (eventInfo.GetActor()->HasAura(CooldownAura, eventInfo.GetActionTarget()->GetGUID()))
            return false;

        return true;
    }

    void HandleProc(AuraEffect* /*aurEff*/, ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetActor())
            return;

        if (Unit* caster = GetCaster())
        {
            if (auto player = caster->ToPlayer())
            {
                // $points=${$cond($gt($SP,$AP),$SP*1.5,$AP*1.5)*(1+$@versadmg)}
                auto result = eventInfo.GetActor()->CountPctFromMaxHealth(5);

                caster->CastSpell(eventInfo.GetActor(), ShieldAura, CastSpellExtraArgs(true).AddSpellBP0(result));
                caster->CastSpell(eventInfo.GetActor(), CooldownAura, CastSpellExtraArgs(true).SetOriginalCaster(caster->GetGUID()));
            }
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_token_of_appreciation::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_token_of_appreciation::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

/// ID - 319983 Wasteland Propriety
class spell_wasteland_propriety : public AuraScript
{
    PrepareAuraScript(spell_wasteland_propriety);

    enum WastelandPropriety
    {
        Proc = 333218,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetSpellInfo())
            return false;

        switch (eventInfo.GetSpellInfo()->Id)
        {
            case SwarmingMist:
            case SinfulBrand:
            case RavenousFrenzy:
            case FlayedShot:
            case MirrorsOfTorment:
            case FallenOrder:
            case AshenHallow:
            case Mindgames:
            case Flagellation:
            case ChainHarvest:
            case ImpendingCatasatrophe:
            case Condemn:
                break;

            default:
                return false;
        }

        return true;
    }

    void HandleProc(AuraEffect* /*aurEff*/, ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetSpellInfo())
            return;

        if (Unit* caster = GetCaster())
        {
            if (auto player = caster->ToPlayer())
            {
                auto it = VenthyrWastelandProprietyRates.find(eventInfo.GetSpellInfo()->Id);
                if (it != VenthyrWastelandProprietyRates.end())
                {
                    auto duration = 10.0f * it->second;

                    std::list<Unit*> friendlies;
                    caster->GetFriendlyUnitListInRange(friendlies, 40.0f);
                    friendlies.sort(Trinity::DistanceOrderPred(caster));

                    for (auto friendly : friendlies)
                    {
                        caster->CastSpell(friendly, Proc, true);

                        if (auto aura = friendly->GetAura(Proc))
                            aura->SetDuration(duration);
                    }
                }
            }
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_wasteland_propriety::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_wasteland_propriety::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

/// ID - 351750 Party Favors
class spell_party_favors : public AuraScript
{
    PrepareAuraScript(spell_party_favors);

    enum PartyFavors
    {
        PartyFavorsItem = 187917,
    };

    void HandleApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (auto caster = GetCaster())
        {
            if (auto player = caster->ToPlayer())
            {
                if (!player->HasItemCount(PartyFavorsItem, 1))
                    player->AddItem(PartyFavorsItem, 1);
            }
        }
    }

    void HandleAfterRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (auto caster = GetCaster())
        {
            if (auto player = caster->ToPlayer())
            {
                player->DestroyItemCount(PartyFavorsItem, 1, true);
            }
        }
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_party_favors::HandleApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        OnEffectRemove += AuraEffectRemoveFn(spell_party_favors::HandleAfterRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

constexpr uint32 PartyFavorAuras[] = { 353266, 354016, 354017, 354018 };

/// ID - 359040 Party Favors
class spell_party_favors_item : public SpellScript
{
    PrepareSpellScript(spell_party_favors_item);

    void HandleDummy(SpellEffIndex /*eff*/)
    {
        auto caster = GetCaster();
        if (!caster)
            return;

        for (auto aura : PartyFavorAuras)
            caster->RemoveAurasDueToSpell(aura);

        caster->CastSpell(caster, Trinity::Containers::SelectRandomContainerElement(PartyFavorAuras), true);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_party_favors_item::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

/// ID - 319973 Built for War
class spell_built_for_war : public AuraScript
{
    PrepareAuraScript(spell_built_for_war);

    enum BuiltForWar
    {
        BuiltForWarAura = 332842,
    };

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
        if (auto caster = GetCaster())
        {
            if (caster->HealthAbovePct(80))
                caster->CastSpell(caster, BuiltForWarAura, true);
        }
    }

    void HandleAfterRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (auto caster = GetCaster())
        {
            caster->RemoveAurasDueToSpell(BuiltForWarAura);
        }
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_built_for_war::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
        OnEffectRemove += AuraEffectRemoveFn(spell_built_for_war::HandleAfterRemove, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

///  ID - 332753 Superior Tactics
class spell_superior_tactics : public AuraScript
{
    PrepareAuraScript(spell_superior_tactics);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return (eventInfo.GetHitMask() & PROC_HIT_INTERRUPT) != 0;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_superior_tactics::CheckProc);
    }
};

/// ID - 331584 Dauntless Duelist
class spell_dauntless_duelist : public AuraScript
{
    PrepareAuraScript(spell_dauntless_duelist);

    enum DauntlessDuelist
    {
        DmgAura = 331934,
    };

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetActor())
            return;

        CheckAndClearDauntlessTargetIfNeed();

        if (!CurrentDauntlessTarget.IsEmpty())
            return;

        if (auto target = eventInfo.GetActionTarget())
        {
            CurrentDauntlessTarget = target->GetGUID();
            eventInfo.GetActor()->CastSpell(target, DmgAura, true);
        }
    }

    Unit* GetDauntlessTarget()
    {
        if (GetCaster())
            return ObjectAccessor::GetUnit(*GetCaster(), CurrentDauntlessTarget);
        return nullptr;
    }

    void CheckAndClearDauntlessTargetIfNeed()
    {
        auto caster = GetCaster();
        if (!caster)
            return;
        auto targ = GetDauntlessTarget();
        if (targ == nullptr || caster->IsValidAssistTarget(targ) || targ->isDead() || !targ->HasAura(DmgAura))
            CurrentDauntlessTarget.Clear();
    }

    void Register() override
    {
        OnProc += AuraProcFn(spell_dauntless_duelist::HandleProc);
    }

    ObjectGuid CurrentDauntlessTarget;
};

/// ID - 332754 Hold Your Ground
class spell_hold_your_ground : public AuraScript
{
    PrepareAuraScript(spell_hold_your_ground);

    enum HoldYourGround
    {
        HoldYourGroundAura = 333089,
    };

    // we need a way to tell when last move was. this is a tempfix for now
    uint32 LastMovingTime = 0;

    void HandleApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* caster = GetCaster())
        {
            LastMovingTime = GameTime::GetGameTimeMS();

            caster->GetScheduler().Schedule(1s, GetId(), [this](TaskContext context)
            {
                // this can be garbage if aura is remove while this executes.
                auto unit = context.GetUnit();
                auto CurrTimeMS = GameTime::GetGameTimeMS();
                bool isMoving = unit->isMoving();

                if (isMoving)
                {
                    LastMovingTime = CurrTimeMS;

                    if (auto aur = unit->GetAura(HoldYourGroundAura))
                    {
                        if (aur->GetDuration() < 0)
                        {
                            aur->SetDuration(6000);
                            aur->SetMaxDuration(6000);
                            aur->SetNeedClientUpdateForTargets();
                        }
                    }
                }

                context.Repeat(100ms);
            });
        }
    }

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* caster = GetCaster())
        {
            caster->GetScheduler().CancelGroup(GetId());
            LastMovingTime = 0;
            caster->RemoveAurasDueToSpell(HoldYourGroundAura);
        }
    }

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
        Unit* target = GetTarget();
        if (!target)
            return;

        auto CurrTimeMS = GameTime::GetGameTimeMS();
        auto diff = CurrTimeMS - LastMovingTime;

        if (diff >= 4000)
        {
            target->CastSpell(target, HoldYourGroundAura, true);
        }
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_hold_your_ground::HandleApply, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY, AURA_EFFECT_HANDLE_REAL);
        OnEffectRemove += AuraEffectApplyFn(spell_hold_your_ground::HandleRemove, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY, AURA_EFFECT_HANDLE_REAL);
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_hold_your_ground::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

/// ID: 319982 Move As One
class spell_move_as_one : public AuraScript
{
    PrepareAuraScript(spell_move_as_one);

    enum MoveAsOne
    {
        MoveAsOneSpeedAura = 333104,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetSpellInfo())
            return false;

        return eventInfo.GetSpellInfo()->HasAura(AuraType::SPELL_AURA_MOD_INCREASE_SPEED) && eventInfo.GetActionTarget();
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        auto caster = GetCaster();
        if (!caster)
            return;

        if (!eventInfo.GetSpellInfo())
            return;

        if (!eventInfo.GetActionTarget())
            return;

        if (auto aur = eventInfo.GetActionTarget()->GetAura(eventInfo.GetSpellInfo()->Id))
        {
            for (auto eff : aur->GetAuraEffects())
            {
                if (eff->GetAuraType() == SPELL_AURA_MOD_INCREASE_SPEED)
                {
                    auto speed = std::min(30, eff->GetAmount());
                    caster->CastSpell(caster, MoveAsOneSpeedAura, CastSpellExtraArgs(true).AddSpellBP0(speed));
                    break;
                }
            }
        }

    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_move_as_one::CheckProc);
        OnProc += AuraProcFn(spell_move_as_one::HandleProc);
    }
};

void AddSC_spell_venthyr()
{
    RegisterSpellScript(spell_door_of_shadows);
    RegisterSpellScript(spell_thrill_seeker);
    RegisterSpellScript(spell_thrill_seeker_haste);
    RegisterSpellScript(spell_token_of_appreciation);
    RegisterSpellScript(spell_wasteland_propriety);
    RegisterSpellScript(spell_party_favors);
    RegisterSpellScript(spell_party_favors_item);
    RegisterSpellScript(spell_built_for_war);
    RegisterSpellScript(spell_dauntless_duelist);
    RegisterSpellScript(spell_hold_your_ground);
    RegisterSpellScript(spell_move_as_one);

    RegisterAreaTriggerAI(at_soothing_shade);
}
