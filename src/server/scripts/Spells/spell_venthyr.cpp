#include "SpellMgr.h"
#include "Unit.h"
#include "SpellScript.h"
#include "SpellAuras.h"

// 300728
class spell_door_of_shadows : public SpellScript
{
    PrepareSpellScript(spell_door_of_shadows);

    enum DoorOfShadows
    {
        FancyFootworksAura = 331577,
        AgentOfChaos = 331576,
        AgentOfChaosTrigger = 331866,
        WatchTheShoes = 336140,
    };

    void HandleScript(SpellEffIndex /*eff*/)
    {
        if (GetCaster() && GetCaster()->HasAura(AgentOfChaos))
        {
            // TODO: add a way to callback on teleport
            GetCaster()->GetScheduler().Schedule(50ms, [this](TaskContext context)
            {
                GetCaster()->CastSpell(GetCaster(), AgentOfChaosTrigger, true);

                if (GetCaster()->HasAura(WatchTheShoes))
                    GetCaster()->RemoveAurasWithMechanic(1 << MECHANIC_ROOT);
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

void AddSC_spell_venthyr()
{
    RegisterSpellScript(spell_door_of_shadows);
    RegisterSpellScript(spell_thrill_seeker);
    RegisterSpellScript(spell_thrill_seeker_haste);
}
