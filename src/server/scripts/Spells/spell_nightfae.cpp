#include "SpellMgr.h"
#include "Unit.h"
#include "SpellScript.h"
#include "SpellHistory.h"
#include "CovenantMgr.h"

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
    };

    void HandleApply(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /* mode */)
    {
        // Is this a soulbind? Check plz
        PreventDefaultAction();

        GetCaster()->GetSpellHistory()->StartCooldown(sSpellMgr->GetSpellInfo(Flicker), 0, nullptr, false, 4s);
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_nightfae_soulshape::HandleApply, EFFECT_5, SPELL_AURA_MOD_UNATTACKABLE, AURA_EFFECT_HANDLE_REAL);
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
        if (auto actor = eventInfo.GetActor())
        {
            actor->CastSpell(actor, RedirectedAnima, true);

            if (actor->HasAura(BondedHearts))
            {
                std::list<Unit*> friends;
                actor->GetFriendlyUnitListInRange(friends, 40.0f);
                friends.sort(Trinity::HealthPctOrderPred());
                friends.remove_if([actor](Unit* unit)
                {
                    return unit == actor;
                });

                if (friends.size() > 5)
                    friends.resize(5);

                for (auto unit : friends)
                {
                    actor->CastSpell(unit, BondedHeartsHeal, true);
                    if (auto player = unit->ToPlayer())
                    {
                        if (player->GetCovenant()->GetCovenantID() == CovenantID::NightFae)
                            actor->CastSpell(actor, BondedHeartsBonus, true);
                    }
                }
            }
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_nightfae_grove_invigoration::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_nightfae_grove_invigoration::HandleProc, EFFECT_0, SPELL_AURA_PROC_TRIGGER_SPELL);
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

    RegisterCreatureAI(npc_regenerating_wild_seed_164589);

    new unit_script_nightfae();
}
