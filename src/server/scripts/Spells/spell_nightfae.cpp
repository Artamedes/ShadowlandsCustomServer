#include "SpellMgr.h"
#include "Unit.h"
#include "SpellScript.h"
#include "SpellHistory.h"
#include "CovenantMgr.h"
#include "GameTime.h"
#include "RestMgr.h"
#include "SpellAuras.h"
#include "SpellAuraEffects.h"
#include "AreaTrigger.h"
#include "AreaTriggerAI.h"

enum NightFae
{
    DeathsDue         = 324128,
    TheHunt           = 333762,
    ConvokeTheSpirits = 323764,
    WildSpirits       = 328231,
    ShiftingPower     = 314791,
    FaelineStomp      = 327276,
    BlessingOfSeasons = 328278,
    FaeGuardians      = 327661,
    Sepsis            = 328305,
    FaeTransfusion    = 328923,
    SoulRot           = 325640,
    AncientAftershock = 325886,

    Soulshape         = 310143,
    CunningDreams     = 352782,
    CunningDreamsSlow = 353472,
};

const std::unordered_map<uint32, float> GroveInvigorationRates =
{
    { DeathsDue        , 0.25f},
    { TheHunt          , 1.5f},
    { ConvokeTheSpirits, 2.0f},
    { WildSpirits      , 2.0f},
    { ShiftingPower    , 0.75f},
    { FaelineStomp     , 0.5f},
    { BlessingOfSeasons, 0.75f},
    { FaeGuardians     , 1.5f},
    { Sepsis           , 1.5f},
    { FaeTransfusion   , 2.0f},
    { SoulRot          , 1.0f},
    { AncientAftershock, 1.5f},
};

const std::unordered_map<uint32, float> FieldOfBlossomsRates =
{
    { DeathsDue        , 0.25f },
    { TheHunt          , 1.5f  },
    { ConvokeTheSpirits, 2.0f  },
    { WildSpirits      , 2.0f  },
    { ShiftingPower    , 1.0f },
    { FaelineStomp     , 0.5f  },
    { BlessingOfSeasons, 0.75f },
    { FaeGuardians     , 1.5f  },
    { Sepsis           , 1.5f  },
    { FaeTransfusion   , 2.0f  },
    { SoulRot          , 1.0f  },
    { AncientAftershock, 1.5f  },
};

inline const bool IsNFCovenantAbility(uint32 spellId)
{
    switch (spellId)
    {
        case SoulRot:
        case DeathsDue:
        case TheHunt:
        case ConvokeTheSpirits:
        case WildSpirits:
        case ShiftingPower:
        case FaelineStomp:
        case BlessingOfSeasons:
        case FaeGuardians:
        case Sepsis:
        case FaeTransfusion:
        case AncientAftershock:
            return true;
        default:
            return false;
    }
}

// 320221 
class spell_nightfae_podtender : public AuraScript
{
    PrepareAuraScript(spell_nightfae_podtender);

    enum PodTender
    {
        SpellPod = 320224,
        DepletedShell = 320227,
    };

    void OnAbsorb(AuraEffect* /*aurEff*/, DamageInfo& dmgInfo, uint32& /*absorbAmount*/)
    {
        if (Unit* caster = GetCaster())
        {
            if (!caster->HasAura(DepletedShell) && dmgInfo.GetDamage() >= caster->GetHealth())
            {
                dmgInfo.AbsorbDamage(dmgInfo.GetDamage());
                PreventDefaultAction();
                caster->CastSpell(caster, SpellPod, true);
                caster->CastSpell(caster, DepletedShell, true);
            }
        }
    }

    void Register() override
    {
        OnEffectAbsorb += AuraEffectAbsorbOverkillFn(spell_nightfae_podtender::OnAbsorb, EFFECT_0);
    }
};

struct npc_regenerating_wild_seed_164589 : public ScriptedAI
{
    public:
        npc_regenerating_wild_seed_164589(Creature* creature) : ScriptedAI(creature) { }

        enum Seed
        {
            SpellWildSeedDeath = 348121,
            DepletedShell = 320227,
        };

        void InitializeAI() override
        {
            me->SetReactState(REACT_PASSIVE);
        }

        void IsSummonedBy(WorldObject* o) override
        {
            if (!o)
                return;

            auto unit = o->ToUnit();
            if (!unit)
                return;

            me->SetLevel(unit->GetLevel());
            me->UpdateLevelDependantStats();
        }

        void JustDied(Unit* /*who*/) override
        {
            if (auto owner = me->GetOwner())
            {
                owner->CastSpell(owner, SpellWildSeedDeath, true);
                me->DespawnOrUnsummon();
            }
        }
};

class unit_script_nightfae : public UnitScript
{
public:
    unit_script_nightfae() : UnitScript("player_script_nightfae") { }

    enum eSpells
    {
        WildHuntTactics = 325066,
        WildHuntTacticsMS = 343594,
        Stratagem = 353286,
        StratagemHealer = 353793,
        StratagemDamage = 353254,

        // Hunter
        WildSpirits = 328837,
        WildSpiritsDmg = 328757,
    };

    //void OnHeal(Unit* healer, Unit* reciever, uint32& gain) override
    //{
    //    if (!healer || !reciever)
    //        return;
    //
    //    if (reciever->HealthBelowPct(36))
    //    {
    //        if (healer->HasAura(WildHuntTactics))
    //        {
    //            AddPct(gain, 10);
    //            if (!healer->HasAura(Stratagem))
    //                healer->CastSpell(healer, Stratagem, true);
    //            if (!healer->HasAura(WildHuntTacticsMS))
    //                healer->CastSpell(healer, WildHuntTacticsMS, true);
    //            if (healer->HasAura(Stratagem))
    //                healer->CastSpell(reciever, StratagemHealer, true);
    //        }
    //    }
    //}

    void OnDamage(Unit* attacker, Unit* victim, uint32& damage, SpellInfo const* spellInfo)
    {
        if (!attacker || !victim)
            return;

        //if (victim->HealthAbovePct(69))
        //{
        //    if (attacker->HasAura(WildHuntTactics))
        //    {
        //        AddPct(damage, 10);
        //        if (!attacker->HasAura(Stratagem))
        //            attacker->CastSpell(attacker, Stratagem, true);
        //        if (!attacker->HasAura(WildHuntTacticsMS))
        //            attacker->CastSpell(attacker, WildHuntTacticsMS, true);
        //        if (attacker->HasAura(Stratagem))
        //            attacker->CastSpell(victim, StratagemDamage, true);
        //    }
        //}

        if (attacker->GetClass() == CLASS_HUNTER && attacker->IsPlayer() && spellInfo && spellInfo->Id != WildSpiritsDmg)
        {
            if (attacker->HasAura(WildSpirits))
            {
                auto areaTrigger = attacker->GetAreaTrigger(WildSpirits);
                if (areaTrigger)
                {
                    if (areaTrigger->GetInsideUnits().count(victim->GetGUID()))
                        attacker->CastSpell(victim, WildSpiritsDmg, true);
                }
            }
        }
    }
};

// 328837
class spell_hunter_wildspirits : public AuraScript
{
    PrepareAuraScript(spell_hunter_wildspirits);

    enum eSpells
    {
        // Hunter
        WildSpirits = 328837,
        WildSpiritsDmg = 328757,
    };
    
    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetActor())
            return false;

        if (!eventInfo.GetProcTarget())
            return false;

        if (!eventInfo.GetActor()->IsValidAttackTarget(eventInfo.GetProcTarget()))
            return false;

        if (eventInfo.GetSpellInfo())
        {
            switch (eventInfo.GetSpellInfo()->Id)
            {
                case WildSpiritsDmg:
                    return false;
                default:
                    break;
            }
        }

        return true;
    }

    void HandleProc(AuraEffect* /*aurEff*/, ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();
        if (auto attacker = eventInfo.GetActor())
        {
            if (auto victim = eventInfo.GetProcTarget())
            {
                auto areaTrigger = attacker->GetAreaTrigger(WildSpirits);
                if (areaTrigger)
                {
                    if (areaTrigger->GetInsideUnits().count(victim->GetGUID()))
                        attacker->CastSpell(victim, WildSpiritsDmg, true);
                }
            }
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_hunter_wildspirits::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_hunter_wildspirits::HandleProc, EFFECT_1, SPELL_AURA_DUMMY);
    }
};

// 310143 
class spell_nightfae_soulshape : public AuraScript
{
    PrepareAuraScript(spell_nightfae_soulshape);

    enum SoulShape
    {
        Flicker = 324701,
        RunWithoutTiring     = 342270,
        RunWithoutTiringBuff = 342309,
        HornOfTheWildHunt    = 325067,
        HornOfTheWildHuntBuff = 325268,
        HornOfTheWildHuntAT  = 325270,
    };

    void HandleApply(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        // Is this a soulbind? Check plz
        PreventDefaultAction();

        if (!GetCaster())
            return;

        GetCaster()->GetSpellHistory()->StartCooldown(sSpellMgr->GetSpellInfo(Flicker), 0, nullptr, false, 4s);

        if (GetCaster()->HasAura(RunWithoutTiring))
            GetCaster()->CastSpell(GetCaster(), RunWithoutTiring, true);

        if (GetCaster()->HasAura(CunningDreamsSlow))
            GetCaster()->CastSpell(GetCaster(), CunningDreamsSlow, true);

        if (GetCaster()->HasAura(HornOfTheWildHunt))
            GetCaster()->CastSpell(GetCaster(), HornOfTheWildHuntBuff, true);
    }

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (!GetCaster())
            return;

        GetCaster()->RemoveAurasDueToSpell(RunWithoutTiringBuff);
        GetCaster()->RemoveAurasDueToSpell(HornOfTheWildHuntBuff);
        GetCaster()->RemoveAurasDueToSpell(HornOfTheWildHuntAT);
    }

    void HandleApply3(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        PreventDefaultAction();

        if (!GetCaster())
            return;

        if (!GetCaster()->HasAura(HornOfTheWildHunt))
            GetCaster()->CastSpell(GetCaster(), HornOfTheWildHuntAT, true);
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_nightfae_soulshape::HandleApply, EFFECT_5, SPELL_AURA_MOD_UNATTACKABLE, AURA_EFFECT_HANDLE_REAL);
        OnEffectApply += AuraEffectApplyFn(spell_nightfae_soulshape::HandleApply3, EFFECT_3, SPELL_AURA_LINKED_2, AURA_EFFECT_HANDLE_REAL);
        OnEffectRemove += AuraEffectApplyFn(spell_nightfae_soulshape::HandleRemove, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

// 322721
// ID - 342937 Grove Invigoration
class spell_nightfae_grove_invigoration : public AuraScript
{
    PrepareAuraScript(spell_nightfae_grove_invigoration);

    enum Grove
    {
        GroveInvigoration = 322721,
        RedirectedAnima = 342814,
        BondedHearts = 352503,
        BondedHeartsHeal = 352871,
        BondedHeartsBonus = 352881,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetActor())
            return false;

        if (eventInfo.GetSpellInfo())
        {
            switch (eventInfo.GetSpellInfo()->Id)
            {
                case RedirectedAnima:
                case GroveInvigoration:
                case BondedHearts:
                case BondedHeartsHeal:
                case BondedHeartsBonus:
                case 342937:
                case 356608:
                    return false;
                default:
                    break;
            }

            if (auto caster = GetCaster())
                if (auto aur = caster->GetAura(GetId()))
                    if (aur->GetStackAmount() >= 50)
                        return true;
        }

        return true;
    }

    void HandleProc(AuraEffect* /*aurEff*/, ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();
        if (auto actor = eventInfo.GetActor())
        {
            uint32 iterates = 1;
            if (eventInfo.GetSpellInfo())
            {
                if (IsNFCovenantAbility(eventInfo.GetSpellInfo()->Id) && !eventInfo.GetHitMask())
                {
                    iterates = 8;
                    auto it = GroveInvigorationRates.find(eventInfo.GetSpellInfo()->Id);
                    if (it != GroveInvigorationRates.end())
                        iterates *= it->second;
                }
            }

            for (uint32 i = 0; i < iterates; ++i)
                actor->CastSpell(actor, RedirectedAnima, true);

            //if (actor->HasAura(BondedHearts))
            //{
            //    std::list<Unit*> friends;
            //    actor->GetFriendlyUnitListInRange(friends, 40.0f);
            //    friends.sort(Trinity::HealthPctOrderPred());
            //    friends.remove_if([actor](Unit* unit)
            //    {
            //        return unit == actor;
            //    });
            //
            //    if (friends.size() > 5)
            //        friends.resize(5);
            //
            //    for (auto unit : friends)
            //    {
            //        actor->CastSpell(unit, BondedHeartsHeal, true);
            //        if (auto player = unit->ToPlayer())
            //        {
            //            if (player->GetCovenant()->GetCovenantID() == CovenantID::NightFae)
            //                actor->CastSpell(actor, BondedHeartsBonus, true);
            //        }
            //    }
            //}
        }
    }

    void OnCalcProc(ProcEventInfo& eventInfo, float& chance)
    {
        // need to disable periodic effects here and up. not sure how to check rn without hacks. not a big deal, just you might stack to 50 right away
        if (eventInfo.GetSpellInfo())
            if (IsNFCovenantAbility(eventInfo.GetSpellInfo()->Id))
                chance = 100.0f;
            else
                chance = 3.0f;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_nightfae_grove_invigoration::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_nightfae_grove_invigoration::HandleProc, EFFECT_0, SPELL_AURA_PROC_TRIGGER_SPELL);
        OnCalcProcChance += AuraCalcProcChanceFn(spell_nightfae_grove_invigoration::OnCalcProc);
    }
};

/// ID: 342814 Redirected Anima
class spell_redirected_anima : public SpellScript
{
    PrepareSpellScript(spell_redirected_anima);

    void HandleDummy(SpellEffIndex eff)
    {
        PreventHitEffect(eff);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_redirected_anima::HandleDummy, EFFECT_2, SPELL_EFFECT_TRIGGER_SPELL);
    }
};

// ID - 320659 Niya's Tools: Burrs
class spell_nightfae_niyas_tools_burrs : public AuraScript
{
    PrepareAuraScript(spell_nightfae_niyas_tools_burrs);

    enum Grove
    {
        BurrsDmg = 321659,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetActor())
            return false;

        return true;
    }

    void HandleProc(AuraEffect* /*aurEff*/, ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();
        if (auto actor = eventInfo.GetActor())
            if (auto hitUnit = eventInfo.GetProcTarget())
                actor->CastSpell(hitUnit, BurrsDmg, true);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_nightfae_niyas_tools_burrs::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_nightfae_niyas_tools_burrs::HandleProc, EFFECT_0, SPELL_AURA_PROC_TRIGGER_SPELL);
    }
};

// ID - 352786 Dream Delver
class spell_nightfae_dream_delver : public AuraScript
{
    PrepareAuraScript(spell_nightfae_dream_delver);

    enum DreamDelver
    {
        Dmg = 353354,
        Healing = 353353,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetActor())
            return false;

        if (!eventInfo.GetProcTarget())
            return false;

        return true;
    }

    void HandleProc(AuraEffect* /*aurEff*/, ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();
        if (auto actor = eventInfo.GetActor())
            if (auto hitUnit = eventInfo.GetProcTarget())
            {
                if (actor->IsValidAssistTarget(hitUnit))
                    actor->CastSpell(hitUnit, Healing, true);
                else if (actor->IsValidAttackTarget(hitUnit))
                    actor->CastSpell(hitUnit, Dmg, true);
            }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_nightfae_dream_delver::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_nightfae_dream_delver::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

// ID - 325066 Wild Hunt Tactics
class spell_nightfae_wild_hunt_tactics : public AuraScript
{
    PrepareAuraScript(spell_nightfae_wild_hunt_tactics);

    enum WildHuntE
    {
        WildHuntTactics = 325066,
        WildHuntTacticsMS = 343594,
        Stratagem = 353286,
        StratagemHealer = 353793,
        StratagemDamage = 353254,
    };

    // SPELL_AURA_MOD_DAMAGE_DONE_VERSUS_AURASTATE is double dipping.
    // probably just add a hack for it later

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetActor())
            return false;

        if (!eventInfo.GetProcTarget())
            return false;

        auto actor = eventInfo.GetActor();
        auto hitUnit = eventInfo.GetProcTarget();
        if (actor->IsValidAssistTarget(hitUnit) && eventInfo.GetHealInfo())
            return actor->HealthBelowPct(36);
        if (actor->IsValidAttackTarget(hitUnit) && eventInfo.GetDamageInfo())
            return actor->HealthAbovePct(75);

        return false;
    }

    void HandleProc(AuraEffect* /*aurEff*/, ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();
        if (auto actor = eventInfo.GetActor())
        {
            if (auto hitUnit = eventInfo.GetProcTarget())
            {
                if (actor->IsValidAttackTarget(hitUnit) && eventInfo.GetDamageInfo())
                {
                    auto dmgInfo = eventInfo.GetDamageInfo();
                    auto damage = dmgInfo->GetDamage();
                    AddPct(damage, 10);
                    dmgInfo->ModifyDamage(damage);

                    if (!actor->HasAura(Stratagem) && !actor->GetSpellHistory()->HasCooldown(Stratagem))
                    {
                        actor->CastSpell(actor, Stratagem, true);
                        actor->GetSpellHistory()->AddCooldown(Stratagem, 0, 2s);
                    }
                    if (!actor->HasAura(WildHuntTacticsMS) && !actor->GetSpellHistory()->HasCooldown(WildHuntTacticsMS))
                    {
                        actor->CastSpell(actor, WildHuntTacticsMS, true);
                        actor->GetSpellHistory()->AddCooldown(WildHuntTacticsMS, 0, 2s);
                    }
                    if (actor->HasAura(Stratagem) && !actor->GetSpellHistory()->HasCooldown(StratagemDamage))
                    {
                        actor->CastSpell(hitUnit, StratagemDamage, true);
                        actor->GetSpellHistory()->AddCooldown(StratagemDamage, 0, 2s);
                    }
                }
                else if (actor->IsValidAssistTarget(hitUnit) && eventInfo.GetHealInfo())
                {
                    auto healInfo = eventInfo.GetHealInfo();

                    //AddPct(gain, 10); - figure this out.. 
                    if (!actor->HasAura(Stratagem) && !actor->GetSpellHistory()->HasCooldown(Stratagem))
                    {
                        actor->CastSpell(actor, Stratagem, true);
                        actor->GetSpellHistory()->AddCooldown(Stratagem, 0, 2s);

                    }
                    if (!actor->HasAura(WildHuntTacticsMS) && !actor->GetSpellHistory()->HasCooldown(WildHuntTacticsMS))
                    {
                        actor->CastSpell(actor, WildHuntTacticsMS, true);
                        actor->GetSpellHistory()->AddCooldown(WildHuntTacticsMS, 0, 2s);
                    }
                    if (actor->HasAura(Stratagem) && !actor->GetSpellHistory()->HasCooldown(StratagemHealer))
                    {
                        actor->CastSpell(hitUnit, StratagemHealer, true);
                        actor->GetSpellHistory()->AddCooldown(StratagemHealer, 0, 2s);
                    }
                }
            }
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_nightfae_wild_hunt_tactics::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_nightfae_wild_hunt_tactics::HandleProc, EFFECT_3, SPELL_AURA_DUMMY);
    }
};

/// ID - 320660 Niya's Tools: Poison
class spell_niyas_tools_poison : public AuraScript
{
    PrepareAuraScript(spell_niyas_tools_poison);

    enum Poison
    {
        ParalyticPoison = 321519,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return true;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();
        if (auto actor = eventInfo.GetActor())
        {
            if (auto hitUnit = eventInfo.GetProcTarget())
            {
                if (eventInfo.GetHitMask() & PROC_HIT_INTERRUPT)
                {
                    if (auto player = actor->ToPlayer())
                    {
                        // $pointsA = ${ $cond($gt($SP,$AP),$SP * 0.05,$AP * 0.05) * (1 + $@versadmg) }
                        // $pointsB = ${ $cond($gt($SP,$AP),$SP * 0.24,$AP * 0.24) * (1 + $@versadmg) }

                        auto sp = static_cast<float>(actor->GetTotalSpellPowerValue(SpellSchoolMask::SPELL_SCHOOL_MASK_ALL, false));
                        auto ap = actor->GetTotalAttackPowerValue(WeaponAttackType::BASE_ATTACK);

                        auto apSpMax = std::max(ap, sp);
                        auto versa = player->m_activePlayerData->Versatility + player->m_activePlayerData->VersatilityBonus;

                        float dmg = 0.0f;

                        if (hitUnit->HasAura(ParalyticPoison))
                            dmg = apSpMax * 0.24f * (1.0f + versa);
                        else
                            dmg = apSpMax * 0.05f * (1.0f + versa);

                        actor->CastSpell(hitUnit, ParalyticPoison, CastSpellExtraArgs(true).AddSpellBP0(dmg));
                    }
                }
            }
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_niyas_tools_poison::CheckProc);
        OnProc += AuraProcFn(spell_niyas_tools_poison::HandleProc);
    }
};

/// ID - 352779 Waking Dreams
class spell_waking_dreams : public AuraScript
{
    PrepareAuraScript(spell_waking_dreams);

    enum Poison
    {
        Shield = 353477,
        CDAura = 358122,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetActionTarget())
            return false;

        if (eventInfo.GetActionTarget()->HasAura(CDAura))
            return false;

        return eventInfo.GetActionTarget()->HealthBelowPct(81);
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto target = eventInfo.GetActionTarget())
        {
            target->CastSpell(target, CDAura, true);
            target->CastSpell(target, Shield, CastSpellExtraArgs(true).AddSpellBP0(target->CountPctFromMaxHealth(20)));
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_waking_dreams::CheckProc);
        OnProc += AuraProcFn(spell_waking_dreams::HandleProc);
    }
};

/// ID - 320687 Swift Patrol
class spell_swift_patrol : public AuraScript
{
    PrepareAuraScript(spell_swift_patrol);

    enum SwiftPatrol
    {
        SwiftPatrolId = 320687,
        SpeedAura = 321527,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetActor())
            return false;

        return true;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto target = eventInfo.GetActor())
        {
            target->CastSpell(target, SpeedAura, true);
            target->GetScheduler().Schedule(100ms, SwiftPatrolId, [](TaskContext context)
            {
                auto targ = context.GetUnit();
                if (targ->HasAura(SpeedAura))
                {
                    if (targ->IsInCombat())
                        targ->RemoveAurasDueToSpell(SpeedAura);
                    else
                        context.Repeat(100ms);
                }
            });
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_swift_patrol::CheckProc);
        OnProc += AuraProcFn(spell_swift_patrol::HandleProc);
    }
};

/// ID - 352502 Survivor's Rally
class spell_survivors_rally : public AuraScript
{
    PrepareAuraScript(spell_survivors_rally);

    enum SurvivorsRally
    {
        SurvivorsRallyId = 352502,
        ShieldAura = 352857,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetActionTarget())
            return false;

        if (eventInfo.GetActionTarget()->GetSpellHistory()->HasCooldown(SurvivorsRallyId))
            return false;

        return eventInfo.GetActionTarget()->HealthBelowPct(51);
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto target = eventInfo.GetActionTarget())
        {
            target->GetSpellHistory()->AddCooldown(SurvivorsRallyId, 0, 60s);
            target->CastSpell(target, ShieldAura, CastSpellExtraArgs(true).AddSpellBP0(target->CountPctFromMaxHealth(21)));
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_survivors_rally::CheckProc);
        OnProc += AuraProcFn(spell_survivors_rally::HandleProc);
    }
};

/// ID - 321467 Stay on the Move
class spell_stay_on_the_move : public SpellScript
{
    PrepareSpellScript(spell_stay_on_the_move);

    void HandleDummy(SpellEffIndex /*eff*/)
    {
        if (auto caster = GetCaster())
            caster->GetSpellHistory()->ModifyCooldown(310143, -1000);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_stay_on_the_move::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

/// ID - 319216 Somnambulist
class spell_somnambulist : public AuraScript
{
    PrepareAuraScript(spell_somnambulist);

    enum Somnambulist
    {
        SpeedBuff = 320235,
    };

    void HandleDummy(AuraEffect const* /*aurEff*/)
    {
        if (auto caster = GetTarget())
        {
            if (auto player = caster->ToPlayer())
            {
                if (player->HasPlayerFlag(PLAYER_FLAGS_RESTING))
                {
                    auto gameTime = GameTime::GetGameTime();

                    if (StartRestTime == 0)
                        StartRestTime = gameTime;
                    else
                    {
                        auto diff = gameTime - StartRestTime;
                        if (diff >= 60 && !player->HasAura(SpeedBuff))
                            player->CastSpell(player, SpeedBuff, true);
                    }
                }
                else if (StartRestTime > 0)
                    StartRestTime = 0;
            }
        }
    }

    time_t StartRestTime = 0;

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_somnambulist::HandleDummy, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

/// ID - 352806 Hunt's Exhilaration
class spell_hunts_exhilaration : public AuraScript
{
    PrepareAuraScript(spell_hunts_exhilaration);

    enum HuntsExhilaration
    {
        LeechSpell = 353203,
    };

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto target = eventInfo.GetActor())
        {
            target->CastSpell(target, LeechSpell, true);
        }
    }

    void Register() override
    {
        OnProc += AuraProcFn(spell_hunts_exhilaration::HandleProc);
    }
};

/// ID: 319213 Empowered Chrysalis
class spell_empowered_chrysalis : public AuraScript
{
    PrepareAuraScript(spell_empowered_chrysalis);

    enum EmpoweredChrysalis
    {
        Shield = 320009,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetActor())
            return false;

        if (!eventInfo.GetActionTarget())
            return false;

        if (!eventInfo.GetHealInfo())
            return false;

        //if (eventInfo.GetActionTarget()->HasAura(Shield))
        //    return false;

        auto healInfo = eventInfo.GetHealInfo();

        return int32(healInfo->GetHeal() - healInfo->GetEffectiveHeal()) > 0;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetActor())
            return;

        if (!eventInfo.GetActionTarget())
            return;

        if (!eventInfo.GetHealInfo())
            return;

        auto healInfo = eventInfo.GetHealInfo();
        auto overHeal = float(healInfo->GetHeal() - healInfo->GetEffectiveHeal());

        overHeal *= 0.10f;

        eventInfo.GetActor()->CastSpell(eventInfo.GetActionTarget(), Shield, CastSpellExtraArgs(true).AddSpellBP0(overHeal));
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_empowered_chrysalis::CheckProc);
        OnProc += AuraProcFn(spell_empowered_chrysalis::HandleProc);
    }
};

/// ID: 320267 Soothing Voice
class spell_soothing_voice : public AuraScript
{
    PrepareAuraScript(spell_soothing_voice);

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
        if (auto aura = GetAura())
            if (auto eff1 = aura->GetEffect(EFFECT_0))
                if (eff1->GetAmount() >= 20)
                    eff1->SetAmount(eff1->GetAmount() - 20);
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_soothing_voice::HandlePeriodic, EFFECT_1, SPELL_AURA_PERIODIC_DUMMY);
    }
};

/// ID: 319191 Field of Blossoms
class spell_field_of_blossoms : public AuraScript
{
    PrepareAuraScript(spell_field_of_blossoms);

    enum FieldOfBlossoms
    {
        FieldOfBlossomsAreaTriggerSpawn = 342761,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetActor() || !eventInfo.GetSpellInfo())
            return false;

        return IsNFCovenantAbility(eventInfo.GetSpellInfo()->Id);
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetSpellInfo())
            return;

        if (auto actor = eventInfo.GetActor())
        {
            actor->CastSpell(actor, FieldOfBlossomsAreaTriggerSpawn, true);

            if (auto areaTrigger = actor->GetAreaTrigger(FieldOfBlossomsAreaTriggerSpawn))
            {
                auto normalDuration = areaTrigger->GetDuration();
                auto it = FieldOfBlossomsRates.find(eventInfo.GetSpellInfo()->Id);
                if (it != FieldOfBlossomsRates.end())
                {
                    normalDuration *= it->second;
                    areaTrigger->SetDuration(normalDuration);
                }
            }
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_field_of_blossoms::CheckProc);
        OnProc += AuraProcFn(spell_field_of_blossoms::HandleProc);
    }
};

/// 21827
struct at_field_of_blossoms : public AreaTriggerAI
{
public:
    at_field_of_blossoms(AreaTrigger* at) : AreaTriggerAI(at) { }

    enum FieldOfBlossoms
    {
        FieldOfBlossomsHaste = 342774,
    };

    void OnUnitEnter(Unit* who) override
    {
        if (who == at->GetOwner())
        {
            if (auto aur = who->GetAura(FieldOfBlossomsHaste))
                aur->SetDuration(at->GetDuration());
            else if (auto aur = who->AddAura(FieldOfBlossomsHaste, who))
                    aur->SetDuration(at->GetDuration());
        }
    }

    void OnUnitExit(Unit* who) override
    {
        if (who == at->GetOwner())
        {
            who->RemoveAurasDueToSpell(FieldOfBlossomsHaste);
        }
    }
};

/// ID: 324701 Flicker
class spell_flicker : public SpellScript
{
    PrepareSpellScript(spell_flicker);

    void HandleDummy(SpellEffIndex /*eff*/)
    {
        if (!GetCaster())
            return;

        if (GetCaster()->HasAura(CunningDreamsSlow))
            GetCaster()->CastSpell(GetCaster(), CunningDreamsSlow, true);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_flicker::HandleDummy, EFFECT_1, SPELL_EFFECT_DUMMY);
    }
};

/// ID: 325065 Wild Hunt's Charge
class spell_wild_hunts_charge : public AuraScript
{
    PrepareAuraScript(spell_wild_hunts_charge);

    enum WildHuntCharge
    {
        WildHuntsChargeBuff = 325305,
    };

    void HandleApply(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (GetCaster())
            HandleCombat(GetCaster()->IsInCombat());
    }

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (GetCaster())
            GetCaster()->RemoveAurasDueToSpell(WildHuntsChargeBuff);
    }

    void HandleCombat(bool combat)
    {
        if (!GetCaster())
            return;

        if (combat)
            GetCaster()->RemoveAurasDueToSpell(WildHuntsChargeBuff);
        else if (!GetCaster()->HasAura(WildHuntsChargeBuff))
            GetCaster()->CastSpell(GetCaster(), WildHuntsChargeBuff, true);
    }


    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_wild_hunts_charge::HandleApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        OnEffectRemove += AuraEffectApplyFn(spell_wild_hunts_charge::HandleRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        OnEnterLeaveCombat += AuraEnterLeaveCombatFn(spell_wild_hunts_charge::HandleCombat);
    }
};

/// ID: 325072 Vorkai Sharpening Techniques
class spell_vorkai_sharpening_techniques : public AuraScript
{
    PrepareAuraScript(spell_vorkai_sharpening_techniques);

    enum Vorkai
    {
        VorkaisSharpeningTechniquesMH = 325485,
        VorkaisSharpeningTechniquesOH = 325486,

    };

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
        if (!GetCaster())
            return;

        GetCaster()->CastSpell(GetCaster(), VorkaisSharpeningTechniquesMH, true);
        GetCaster()->CastSpell(GetCaster(), VorkaisSharpeningTechniquesOH, true);
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_vorkai_sharpening_techniques::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
    }
};

/// ID: 325073 Get In Formation
class spell_get_in_formation : public AuraScript
{
    PrepareAuraScript(spell_get_in_formation);

    enum GetInFormation
    {
        MountBuff = 325443,
    };

    void HandleApply(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (GetCaster())
        {
            GetCaster()->CastSpell(GetCaster(), MountBuff, true);
        }
    }

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (GetCaster())
        {
            GetCaster()->RemoveAurasDueToSpell(MountBuff);
        }
    }

    // requires areatrigger 348392 (20032 )

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_get_in_formation::HandleApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        OnEffectRemove += AuraEffectApplyFn(spell_get_in_formation::HandleRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

/// ID: 325068 Face Your Foes
class spell_face_your_foes : public AuraScript
{
    PrepareAuraScript(spell_face_your_foes);

    enum FaceYourFoes
    {
        FaceYourFoesDebuff = 325437,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetActor() || !eventInfo.GetActionTarget())
            return false;

        return eventInfo.GetActor()->isInFront(eventInfo.GetActionTarget());
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetActor() || !eventInfo.GetActionTarget())
            return;

        eventInfo.GetActor()->CastSpell(eventInfo.GetActionTarget(), FaceYourFoesDebuff, true);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_face_your_foes::CheckProc);
        OnProc += AuraProcFn(spell_face_your_foes::HandleProc);
    }
};

/// ID: 325601 Hold the Line
class spell_hold_the_line : public AuraScript
{
    PrepareAuraScript(spell_hold_the_line);

    enum HoldTheLine
    {
        DefenseAura = 325612,
    };

    time_t LastMoveTime = 0;

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
        auto target = GetCaster();
        if (!target)
            return;

        auto CurrTime = GameTime::GetGameTime();

        if (target->isMoving())
        {
            LastMoveTime = CurrTime;
        }

        if (!LastMoveTime)
            LastMoveTime = CurrTime;
        else
        {
            auto diff = CurrTime - LastMoveTime;
            if (diff >= 5)
            {
                if (!target->HasAura(DefenseAura))
                    target->CastSpell(target, DefenseAura, true);
            }
        }
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_hold_the_line::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
    }
};

/// ID: 352800 Vorkai Ambush
class spell_vorkai_ambush : public AuraScript
{
    PrepareAuraScript(spell_vorkai_ambush);

    enum VorkaiAmbush
    {
        VorkaiAmbushAura = 353077,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetSpellInfo())
            return false;

        if (!eventInfo.GetActionTarget() || !eventInfo.GetActor())
            return false;

        return eventInfo.GetHitMask() & PROC_HIT_INTERRUPT;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetActionTarget() || !eventInfo.GetActor())
            return;

        eventInfo.GetActor()->CastSpell(eventInfo.GetActionTarget(), VorkaiAmbushAura, true);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_vorkai_ambush::CheckProc);
        OnProc += AuraProcFn(spell_vorkai_ambush::HandleProc);
    }
};

/// ID: 325069 First Strike
class spell_first_strike : public AuraScript
{
    PrepareAuraScript(spell_first_strike);

    enum FirstStrike
    {
        Buff = 325381,
    };

    GuidUnorderedSet ProccedUnits;

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetActionTarget() || !eventInfo.GetActor())
            return false;

        // check hit us
        if (ProccedUnits.count(eventInfo.GetActionTarget()->GetGUID()) || ProccedUnits.count(eventInfo.GetActionTarget()->GetGUID()))
            return false;

        return true;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetActionTarget() || !eventInfo.GetActor())
            return;

        if (auto caster = GetCaster())
        {
            caster->CastSpell(caster, Buff, true);

            ProccedUnits.insert(eventInfo.GetActionTarget()->GetGUID());
            ProccedUnits.insert(eventInfo.GetActor()->GetGUID());
        }
    }

    uint32 updateMS = 0;

    void HandleUpdate(const uint32 diff)
    {
        if (updateMS >= 5000)
        {
            updateMS = 0;

            if (auto target = GetCaster())
            {
                for (auto it = ProccedUnits.begin(); it != ProccedUnits.end(); )
                {
                    auto unit = ObjectAccessor::GetUnit(*target, *it);
                    if (!unit || unit->isDead() || !unit->IsInCombatWith(target))
                    {
                        it = ProccedUnits.erase(it);
                    }
                    else
                    {
                        ++it;
                    }
                }
            }
        }
        else
            updateMS += diff;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_first_strike::CheckProc);
        OnProc += AuraProcFn(spell_first_strike::HandleProc);
        OnAuraUpdate += AuraUpdateFn(spell_first_strike::HandleUpdate);
    }
};

/// Horn of the wild hunt
struct at_horn_of_the_wild_hunt : public AreaTriggerAI
{
public:
    at_horn_of_the_wild_hunt(AreaTrigger* at) : AreaTriggerAI(at) { }

    enum HornOfTheWild
    {
        HornOfTheWildHuntBuff = 325268,
    };

    GuidUnorderedSet BuffTargs;

    void OnUnitEnter(Unit* who) override
    {
        if (at->GetOwner())
        {
            if (who->IsFriendlyTo(at->GetOwner()))
            {
                who->CastSpell(who, HornOfTheWildHuntBuff, true);
                BuffTargs.insert(who->GetGUID());
            }
        }
    }

    void OnUnitExit(Unit* who) override
    {
        if (BuffTargs.count(who->GetGUID()))
            who->RemoveAurasDueToSpell(HornOfTheWildHuntBuff);
    }
};


void AddSC_spell_nightfae()
{
    RegisterSpellScript(spell_nightfae_podtender);
  //  RegisterSpellScript(spell_hunter_wildspirits);
    RegisterSpellScript(spell_nightfae_soulshape);
    RegisterSpellScript(spell_nightfae_grove_invigoration);
    RegisterSpellScript(spell_nightfae_niyas_tools_burrs);
    RegisterSpellScript(spell_nightfae_dream_delver);
    RegisterSpellScript(spell_nightfae_wild_hunt_tactics);
    RegisterSpellScript(spell_niyas_tools_poison);
    RegisterSpellScript(spell_waking_dreams);
    RegisterSpellScript(spell_swift_patrol);
    RegisterSpellScript(spell_survivors_rally);
    RegisterSpellScript(spell_stay_on_the_move);
    RegisterSpellScript(spell_somnambulist);
    RegisterSpellScript(spell_hunts_exhilaration);
    RegisterSpellScript(spell_empowered_chrysalis);
    RegisterSpellScript(spell_soothing_voice);
    RegisterSpellScript(spell_field_of_blossoms);
    RegisterSpellScript(spell_flicker);
    RegisterSpellScript(spell_wild_hunts_charge);
    RegisterSpellScript(spell_vorkai_sharpening_techniques);
    RegisterSpellScript(spell_get_in_formation);
    RegisterSpellScript(spell_face_your_foes);
    RegisterSpellScript(spell_hold_the_line);
    RegisterSpellScript(spell_vorkai_ambush);
    RegisterSpellScript(spell_first_strike);
    RegisterSpellScript(spell_redirected_anima);

    RegisterCreatureAI(npc_regenerating_wild_seed_164589);

    RegisterAreaTriggerAI(at_field_of_blossoms);
    RegisterAreaTriggerAI(at_horn_of_the_wild_hunt);

    new unit_script_nightfae();
}
