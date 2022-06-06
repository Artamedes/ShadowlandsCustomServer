#include "SpellMgr.h"
#include "Unit.h"
#include "SpellScript.h"
#include "SpellAuras.h"
#include "SpellAuraEffects.h"
#include "SpellHistory.h"
#include "Cell.h"
#include "CellImpl.h"
#include "GridNotifiers.h"
#include "AreaTrigger.h"
#include "AreaTriggerAI.h"

enum Necrolord
{
    Fleshcraft             = 324631,
    FleshcraftPeriodicAura = 350228, ///< Used in fleshcraft to eat the corpses to reduce CD.
    FleshcraftMissle       = 331180,

    VolatileSolventHumanoid     = 323491,
    VolatileSolventAberration   = 323497,
    VolatileSolventBeast        = 323498,
    VolatileSolventDemon        = 323500,
    VolatileSolventDragonkin    = 323502,
    VolatileSolventElemental    = 323504,
    VolatileSolventGiant        = 323506,
    VolatileSolventMechanical   = 323507,
    VolatileSolventUndeadAura   = 323510,

    AbominationLimb             = 315443,
    FodderToTheFlame            = 329554,
    AdaptiveSwarm               = 325727,
    DeathChakram                = 325028,
    Deathborne                  = 324220,
    BonedustBrew                = 325216,
    VanquishersHammer           = 328204,
    UnholyNova                  = 344481,
    SerratedBoneSpike           = 328547,
    PrimordialWave              = 326059,
    DecimatingBolt              = 325289,
    ConquerorsBanner            = 324143,

    NpcKevin = 178601,
};

const std::unordered_map<uint32, float> KevinRates
{
    { AbominationLimb  , 2.0f },
    { FodderToTheFlame , 2.0f },
    { AdaptiveSwarm    , 0.4f },
    { DeathChakram     , 0.75f },
    { Deathborne       , 3.0f },
    { BonedustBrew     , 1.0f },
    { VanquishersHammer, 0.5f },
    { UnholyNova       , 1.0f },
    { SerratedBoneSpike, 0.5f },
    { PrimordialWave   , 0.75f },
    { DecimatingBolt   , 0.75f },
    { ConquerorsBanner , 2.0f },
};

inline const bool IsCovenantSpell(uint32 spellId)
{
    switch (spellId)
    {
        case AbominationLimb:
        case FodderToTheFlame:
        case AdaptiveSwarm:
        case DeathChakram:
        case Deathborne:
        case BonedustBrew:
        case VanquishersHammer:
        case UnholyNova:
        case SerratedBoneSpike:
        case PrimordialWave:
        case DecimatingBolt:
        case ConquerorsBanner:
            return true;
        default:
            return false;
    }
}

// 324631 
class spell_necrolord_fleshcraft : public AuraScript
{
    PrepareAuraScript(spell_necrolord_fleshcraft);

    enum eFleshcraft
    {
        FleshcraftAura = 324867,
        UltimateForm = 323095,
        EmenisMagnificntSkin = 323921,
        MagnificentSkin = 328210,
    };

    int32 amount = 0;

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
        Unit* target = GetTarget();
        if (!target)
            return;

        auto aura = target->GetAura(FleshcraftAura);
        if (!aura)
            aura = target->AddAura(FleshcraftAura);

        if (aura)
        {
            auto effect = aura->GetEffect(0);
            if (effect)
            {
                amount += target->GetMaxHealth() * 0.0666666666667;
                effect->SetAmount(amount);
                aura->SetNeedClientUpdateForTargets();
            }
        }
    }

    void HandleApply(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /* mode */)
    {
        if (!GetCaster())
            return;

        if (!GetCaster()->HasAura(UltimateForm))
            PreventDefaultAction();

        GetCaster()->CastSpell(GetCaster(), FleshcraftPeriodicAura, true);

        if (GetCaster()->HasAura(EmenisMagnificntSkin))
            GetCaster()->CastSpell(GetCaster(), MagnificentSkin, true);
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_necrolord_fleshcraft::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
        OnEffectApply += AuraEffectApplyFn(spell_necrolord_fleshcraft::HandleApply, EFFECT_2, SPELL_AURA_LINKED_2, AURA_EFFECT_HANDLE_REAL);
    }
};

// not needed
class spell_necrolord_fleshcraft_spellscript : public SpellScript
{
    PrepareSpellScript(spell_necrolord_fleshcraft_spellscript);

    enum Fleshcraft
    {
        FleshcraftAura = 324867,
        UltimateForm = 323095,
    };

    void HandleUltimateForm(SpellEffIndex eff)
    {
        if (GetCaster() && !GetCaster()->HasAura(UltimateForm))
            PreventHitEffect(eff);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_necrolord_fleshcraft_spellscript::HandleUltimateForm, EFFECT_2, SPELL_EFFECT_APPLY_AURA);
    }
};

/// ID - 323089 Travel with Bloop
class spell_travel_with_bloop : public AuraScript
{
    PrepareAuraScript(spell_travel_with_bloop);

    enum TravelWithBloop
    {
        SpeedSpell    = 323399,
        StackingSpell = 323396,
    };

    void HandlePeriodic(AuraEffect const* /*effect*/)
    {
        Unit* caster = GetCaster();
        if (!caster)
            return;

        if (caster->HasAura(SpeedSpell))
            return;

        if (!caster->isMoving())
        {
            bool grantSpeed = false;
            Aura* stackAura = caster->GetAura(StackingSpell);
            if (stackAura)
            {
                if (stackAura->GetStackAmount() >= 4)
                {
                    grantSpeed = true;
                }
            }

            caster->CastSpell(caster, StackingSpell, true);

            if (grantSpeed && stackAura)
            {
                stackAura->Remove();
                caster->CastSpell(caster, SpeedSpell, true);
            }
        }
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_travel_with_bloop::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
    }
};
/// ID: 323916 Sulfuric Emission
class spell_sulfuric_emission : public AuraScript
{
    PrepareAuraScript(spell_sulfuric_emission);

    enum SulfuricEmission
    {
        SulfuricEmissionFear = 324263,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetActionTarget())
            return false;

        if (!eventInfo.GetActionTarget()->HealthBelowPct(21))
            return false;

        return !eventInfo.GetActionTarget()->GetSpellHistory()->HasCooldown(SulfuricEmissionFear);
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();
        if (!eventInfo.GetActionTarget())
            return;

        eventInfo.GetActionTarget()->GetSpellHistory()->AddCooldown(SulfuricEmissionFear, 0, 60s);
        eventInfo.GetActionTarget()->CastSpell(eventInfo.GetActor(), SulfuricEmissionFear, true);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_sulfuric_emission::CheckProc);
        OnProc += AuraProcFn(spell_sulfuric_emission::HandleProc);
    }
};
    
class AnyUnitInRange
{
    public:
        AnyUnitInRange(WorldObject const* obj, float range, bool check3D = true) : i_obj(obj), i_range(range), i_check3D(check3D) { }

        bool operator()(Object* u) const;

    private:
        WorldObject const* i_obj;
        float i_range;
        bool i_check3D;
};

bool AnyUnitInRange::operator()(Object* u) const
{
    if (!u->IsUnit())
        return false;

    if (i_obj->IsWithinDistInMap(u->ToUnit(), i_range, i_check3D))
        return true;
    return false;
}

/// ID: 350228 Fleshcraft
class spell_fleshcraft_consume : public AuraScript
{
    PrepareAuraScript(spell_fleshcraft_consume);

    enum FleshcraftConsume
    {
        VolatileSolvent = 323074,
    };

    GuidUnorderedSet consumedCorpses;

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
        auto caster = GetCaster();
        if (!caster)
            return;

        if (caster->GetChannelSpellId() != Necrolord::Fleshcraft)
        {
            Remove();
            return;
        }

        std::list<Unit*> enemyCorpses;
        AnyUnitInRange check(caster, 10.0f, true);
        Trinity::UnitListSearcher<AnyUnitInRange> searcher(caster, enemyCorpses, check);
        Cell::VisitAllObjects(caster, searcher, 10.0f);
        enemyCorpses.remove_if([this, caster](Unit* unit)
        {
            return unit->IsFriendlyTo(caster) || unit->IsAlive() || consumedCorpses.count(unit->GetGUID());
        });

        bool volatileSolvent = caster->HasAura(VolatileSolvent);

        for (auto enemy : enemyCorpses)
        {
            consumedCorpses.insert(enemy->GetGUID());
            caster->CastSpell(enemy, FleshcraftMissle, true);

            if (volatileSolvent)
            {
                uint32 volatileSolventAura = 0;
                if (enemy->IsPlayer())
                {
                    volatileSolventAura = VolatileSolventHumanoid;
                }
                else if (auto creature = enemy->ToCreature())
                {
                    switch (creature->GetCreatureType())
                    {
                        case CREATURE_TYPE_BEAST:       volatileSolventAura = VolatileSolventBeast; break;
                        case CREATURE_TYPE_DRAGONKIN:   volatileSolventAura = VolatileSolventDragonkin; break;
                        case CREATURE_TYPE_DEMON:       volatileSolventAura = VolatileSolventDemon; break;
                        case CREATURE_TYPE_ELEMENTAL:   volatileSolventAura = VolatileSolventElemental; break;
                        case CREATURE_TYPE_GIANT:       volatileSolventAura = VolatileSolventGiant; break;
                        case CREATURE_TYPE_MECHANICAL:  volatileSolventAura = VolatileSolventMechanical; break;
                        case CREATURE_TYPE_ABERRATION:  volatileSolventAura = VolatileSolventAberration; break;
                        case CREATURE_TYPE_UNDEAD:
                            volatileSolventAura = VolatileSolventUndeadAura;
                            break;
                        case CREATURE_TYPE_CRITTER: // nothing for critters
                        case CREATURE_TYPE_NON_COMBAT_PET: // or this
                        case CREATURE_TYPE_GAS_CLOUD: // or this
                        case CREATURE_TYPE_WILD_PET: // or this
                        case CREATURE_TYPE_NOT_SPECIFIED: // or this
                            break;
                        case CREATURE_TYPE_HUMANOID:
                        default:
                            volatileSolventAura = VolatileSolventHumanoid;
                            break;

                    }
                }

                if (volatileSolventAura)
                    caster->CastSpell(caster, volatileSolventAura, true);
            }
        }
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_fleshcraft_consume::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

/// ID: 350229 Fleshcraft
class spell_fleshcraft_cdr : public SpellScript
{
    PrepareSpellScript(spell_fleshcraft_cdr);

    void HandleDummy(SpellEffIndex /*eff*/)
    {
        if (auto caster = GetCaster())
        {
            caster->GetSpellHistory()->ModifyCooldown(Fleshcraft, -1000);
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_fleshcraft_cdr::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

/// ID: 323510 Volatile Solvent: Undead
class spell_volatile_solvent_undead : public AuraScript
{
    PrepareAuraScript(spell_volatile_solvent_undead);

    bool CheckProc(ProcEventInfo& /*eventInfo*/)
    {
        // invalid - spell works different than i thought.
        return true;
        //if (!eventInfo.GetActor())
        //    return false;
        //auto actionTarget = eventInfo.GetActionTarget();
        //if (!actionTarget)
        //    return false;
        //
        //if (!actionTarget->IsCreature())
        //    return false;
        //
        //return actionTarget->ToCreature()->GetCreatureType() == CREATURE_TYPE_UNDEAD;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_volatile_solvent_undead::CheckProc);
    }
};

/// ID: 323074 Volatile Solvent
class spell_volatile_solvent : public AuraScript
{
    PrepareAuraScript(spell_volatile_solvent);

    enum VolatileSolvent
    {
        VolatileSolventUndeadHeal = 323509, // seems it's handled serperately (in it's own script) - TODO Move before commt
    };

    void HandleApply(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (!GetCaster())
            return;

        //GetCaster()->CastSpell(GetCaster(), VolatileSolventUndeadAura, true);
    }

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (!GetCaster())
            return;

        GetCaster()->RemoveAurasDueToSpell(VolatileSolventHumanoid);
        GetCaster()->RemoveAurasDueToSpell(VolatileSolventAberration);
        GetCaster()->RemoveAurasDueToSpell(VolatileSolventBeast);
        GetCaster()->RemoveAurasDueToSpell(VolatileSolventDemon);
        GetCaster()->RemoveAurasDueToSpell(VolatileSolventDragonkin);
        GetCaster()->RemoveAurasDueToSpell(VolatileSolventElemental);
        GetCaster()->RemoveAurasDueToSpell(VolatileSolventGiant);
        GetCaster()->RemoveAurasDueToSpell(VolatileSolventMechanical);
        GetCaster()->RemoveAurasDueToSpell(VolatileSolventUndeadAura);
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_volatile_solvent::HandleApply, EFFECT_1, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        OnEffectRemove += AuraEffectApplyFn(spell_volatile_solvent::HandleRemove, EFFECT_1, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

/// ID: 323090 Plaguey's Preemptive Strike
class spell_plagueys_preemptive_strike : public AuraScript
{
    PrepareAuraScript(spell_plagueys_preemptive_strike);

    enum Plaguey
    {
        StrikeBuff = 323416,
    };

    GuidUnorderedSet ProccedUnits;

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetActionTarget() || !eventInfo.GetActor())
            return false;

        // check hit us
        if (ProccedUnits.count(eventInfo.GetActionTarget()->GetGUID()) || ProccedUnits.count(eventInfo.GetActionTarget()->GetGUID()))
            return false;

        return eventInfo.GetActionTarget() != eventInfo.GetActor();
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetActionTarget() || !eventInfo.GetActor())
            return;

        if (auto caster = GetCaster())
        {
            caster->CastSpell(eventInfo.GetActionTarget(), StrikeBuff, true);

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
        DoCheckProc += AuraCheckProcFn(spell_plagueys_preemptive_strike::CheckProc);
        OnProc += AuraProcFn(spell_plagueys_preemptive_strike::HandleProc);
    }
};

/// ID: 352108 Viscous Trail
class spell_viscous_trail : public AuraScript
{
    PrepareAuraScript(spell_viscous_trail);

    enum ViscousTrail
    {
        ProcSpell = 352427,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetSpellInfo())
            return false;

        if (eventInfo.GetSpellInfo()->HasEffectMechanic(Mechanics::MECHANIC_SNARE))
            return true;

        return false;
    }

    void HandleProc(ProcEventInfo& /*eventInfo*/)
    {
        PreventDefaultAction();
        if (auto caster = GetCaster())
        {
            caster->CastSpell(caster, ProcSpell, true);
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_viscous_trail::CheckProc);
        OnProc += AuraProcFn(spell_viscous_trail::HandleProc);
    }
};

/// ID: 22903
struct at_viscous_trail : public AreaTriggerAI
{
public:
    at_viscous_trail(AreaTrigger* at) : AreaTriggerAI(at) { }

    enum Viscoustrail
    {
        Slow = 352448,
    };

    void OnUnitEnter(Unit* who) override
    {
        if (auto caster = at->GetCaster())
        {
            if (caster->IsValidAttackTarget(who))
                caster->CastSpell(who, Slow, true);
        }
    }
};

/// ID: 352110 Kevin's Oozeling
class spell_kevins_oozeling : public AuraScript
{
    PrepareAuraScript(spell_kevins_oozeling);

    enum KevinsOozeling
    {
        KevinProc = 352500,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetSpellInfo())
            return false;

        return IsCovenantSpell(eventInfo.GetSpellInfo()->Id);
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetSpellInfo())
            return;

        if (auto caster = GetCaster())
        {
            if (!caster->HasAura(KevinProc))
                caster->CastSpell(caster, KevinProc, true);

            if (auto kevinProc = caster->GetAura(KevinProc))
            {
                auto it = KevinRates.find(eventInfo.GetSpellInfo()->Id);
                if (it != KevinRates.end())
                {
                    auto duration = 20000.0f * it->second;
                    if (kevinProc->GetDuration() == -1)
                    {
                        kevinProc->SetDuration(duration);
                        kevinProc->SetMaxDuration(duration);
                    }
                    else
                        kevinProc->ModDuration(duration);
                }
            }
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_kevins_oozeling::CheckProc);
        OnProc += AuraProcFn(spell_kevins_oozeling::HandleProc);
    }
};

/// ID: 352500 Kevin's Oozeling
class spell_kevins_oozeling_proc : public AuraScript
{
    PrepareAuraScript(spell_kevins_oozeling_proc);

    void HandleApply(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (!GetCaster())
            return;
    }

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (!GetCaster())
            return;

        GetCaster()->UnsummonCreatureByEntry(NpcKevin);
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_kevins_oozeling_proc::HandleApply, EFFECT_1, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        OnEffectRemove += AuraEffectApplyFn(spell_kevins_oozeling_proc::HandleRemove, EFFECT_1, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

// 178601 - npc_kevin_s_oozeling_178601
struct npc_kevin_s_oozeling_178601 : public ScriptedAI
{
public:
    npc_kevin_s_oozeling_178601(Creature* creature) : ScriptedAI(creature) { }

    enum KevinaOoze
    {
        KevinsWrath = 352528,
    };

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        if (me->IsWithinMeleeRange(me->GetVictim()))
            if (!me->GetVictim()->HasAura(KevinsWrath))
                if (me->GetOwner())
                    me->GetOwner()->CastSpell(me->GetVictim(), KevinsWrath, true);

        DoMeleeAttackIfReady();
    }
};

/// ID: 323918 Gristled Toes
class spell_gristled_toes : public AuraScript
{
    PrepareAuraScript(spell_gristled_toes);

    enum GristledToes
    {
        Buff = 324463,
    };

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
        if (!GetCaster())
            return;

        std::list<Unit*> enemies;
        GetCaster()->GetAttackableUnitListInRange(enemies, 10.0f);
        if (!enemies.empty())
        {
            uint32 count = enemies.size();

            if (auto buff = GetCaster()->GetAura(Buff))
                buff->SetStackAmount(count);
            else if (auto buff = GetCaster()->AddAura(Buff, GetCaster()))
                buff->SetStackAmount(count);
        }
        else if (GetCaster()->HasAura(Buff))
            GetCaster()->RemoveAurasDueToSpell(Buff);
    }

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (GetCaster())
            GetCaster()->RemoveAurasDueToSpell(Buff);
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_gristled_toes::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
        OnEffectRemove += AuraEffectApplyFn(spell_gristled_toes::HandleRemove, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

/// ID: 351093 Resilient Stitching
class spell_resilient_stitching : public AuraScript
{
    PrepareAuraScript(spell_resilient_stitching);

    enum ResilientStiching
    {
        Shield = 351921,
        CDAura = 351922,
    };

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
        if (!GetCaster())
            return;

        if (!GetCaster()->HealthAbovePct(90))
            return;

        if (GetCaster()->isDead())
            return;

        if (GetCaster()->HasAura(CDAura))
            return;

        auto hp = GetCaster()->GetMaxHealth() * 0.16f;
        GetCaster()->CastSpell(GetCaster(), Shield, CastSpellExtraArgs(true).AddSpellBP0(hp));
        //GetCaster()->CastSpell(GetCaster(), CDAura, true);
    }

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (!GetCaster())
            return;

        GetCaster()->RemoveAura(Shield);
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_resilient_stitching::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
        OnEffectRemove += AuraEffectApplyFn(spell_resilient_stitching::HandleRemove, EFFECT_1, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

/// ID: 323919 Gnashing Chompers
class spell_gnashing_chompers : public AuraScript
{
    PrepareAuraScript(spell_gnashing_chompers);

    enum GnashingChompers
    {
        HasteBuff = 324242,
    };

    void HandleProc(ProcEventInfo& /*eventInfo*/)
    {
        if (auto caster = GetCaster())
        {
            caster->CastSpell(caster, HasteBuff, true);
        }
    }

    void Register() override
    {
        OnProc += AuraProcFn(spell_gnashing_chompers::HandleProc);
    }
};

void AddSC_spell_necrolord()
{
    RegisterSpellAndAuraScriptPairWithArgs(spell_necrolord_fleshcraft_spellscript, spell_necrolord_fleshcraft, "spell_necrolord_fleshcraft");
    RegisterSpellScript(spell_travel_with_bloop);
    RegisterSpellScript(spell_sulfuric_emission);
    RegisterSpellScript(spell_fleshcraft_consume);
    RegisterSpellScript(spell_fleshcraft_cdr);
    RegisterSpellScript(spell_volatile_solvent_undead);
    RegisterSpellScript(spell_volatile_solvent);
    RegisterSpellScript(spell_plagueys_preemptive_strike);
    RegisterSpellScript(spell_viscous_trail);
    RegisterSpellScript(spell_kevins_oozeling);
    RegisterSpellScript(spell_kevins_oozeling_proc);
    RegisterSpellScript(spell_gristled_toes);
    RegisterSpellScript(spell_resilient_stitching);
    RegisterSpellScript(spell_gnashing_chompers);

    RegisterAreaTriggerAI(at_viscous_trail);

    RegisterCreatureAI(npc_kevin_s_oozeling_178601);
}
