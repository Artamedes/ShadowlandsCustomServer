#include "ScriptMgr.h"
#include "Spell.h"
#include "SpellMgr.h"
#include "SpellAuraEffects.h"
#include "Spell.h"
#include "SpellScript.h"
#include "AreaTrigger.h"
#include "AreaTriggerAI.h"
#include "TemporarySummon.h"
#include "SpellHistory.h"
#include "Player.h"

enum SpellCorruptions
{
    CascadingDisaster = 315857, ///< Being struct by thing from beyond will cause grasping tendrils and eye of corruption to hit you
    GrandDelusions = 315185, ///< Proc Spell
    ThingFromBeyond = 315186, ///< Spawn Spell
    FixateSpell = 319695,
    EyeOfCorrptionDmg = 315161,
    MSReduction = 315176,
    EyeOfCorruption = 315154,
    EyeOfCorruptionAura = 315169,
};

/// ID: 315175 Grasping Tendrils
class spell_grasping_tendrils : public AuraScript
{
    PrepareAuraScript(spell_grasping_tendrils);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        auto caster = GetCaster();
        if (!caster)
            return false;

        return eventInfo.GetDamageInfo() && caster->IsInCombat() && !caster->HasAura(MSReduction) && !caster->GetSpellHistory()->HasCooldown(MSReduction);
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();
        auto caster = GetCaster();
        if (!caster)
            return;

        auto player = caster->ToPlayer();
        if (!player)
            return;

        auto corruptionAmount = player->GetEffectiveCorruption();
        auto slowAmount = std::min<int32>(99, corruptionAmount + 10.0f);
        player->CastSpell(player, MSReduction, CastSpellExtraArgs(true).AddSpellBP0(-slowAmount));
        player->GetSpellHistory()->AddCooldown(MSReduction, 0, 15s);

        player->UpdateSpeed(MOVE_RUN);
        player->UpdateSpeed(MOVE_SWIM);
        player->UpdateSpeed(MOVE_FLIGHT);
        player->UpdateSpeed(MOVE_RUN_BACK);
        player->UpdateSpeed(MOVE_SWIM_BACK);
        player->UpdateSpeed(MOVE_FLIGHT_BACK);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_grasping_tendrils::CheckProc);
        OnProc += AuraProcFn(spell_grasping_tendrils::HandleProc);
    }
};

/// ID: 315169 Eye of Corruption
class spell_eye_of_corruption : public AuraScript
{
    PrepareAuraScript(spell_eye_of_corruption);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        auto caster = GetCaster();
        if (!caster)
            return false;
        return eventInfo.GetDamageInfo() && caster->IsInCombat() && !caster->GetSpellHistory()->HasCooldown(EyeOfCorruptionAura);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_eye_of_corruption::CheckProc);
    }
};

/// ID: 315184 Grand Delusions
class spell_grand_delusions : public AuraScript
{
    PrepareAuraScript(spell_grand_delusions);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        auto caster = GetCaster();
        if (!caster)
            return false;
        return eventInfo.GetDamageInfo() && !caster->HasAura(FixateSpell) && !caster->GetSpellHistory()->HasCooldown(GrandDelusions) && caster->IsInCombat();
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();

        auto caster = GetCaster();
        if (!caster)
            return;

        caster->CastSpell(caster, ThingFromBeyond, true);
        caster->GetSpellHistory()->AddCooldown(GrandDelusions, 0, 30s);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_grand_delusions::CheckProc);
        OnProc += AuraProcFn(spell_grand_delusions::HandleProc);
    }
};

/// ID: 337612 Inescapable Consequences
class spell_inescapable_consequences : public AuraScript
{
    PrepareAuraScript(spell_inescapable_consequences);

    enum InescapableConsequences
    {
        NZothDmg = 337816,
    };

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
        auto caster = GetCaster();
        if (!caster)
            return;

        if (caster->IsInCombat())
            caster->CastSpell(caster, NZothDmg, true);
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_inescapable_consequences::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
    }
};

struct at_eye_of_corruption : public AreaTriggerAI
{
public:
    at_eye_of_corruption(AreaTrigger* at) : AreaTriggerAI(at) { }

    void OnCreate() override
    {
        if (auto caster = at->GetCaster())
        {
            if (auto player = caster->ToPlayer())
            {
                at->SetObjectScale(player->GetEffectiveCorruption());
                at->SetXSpellVisualID(281880);
                at->SetPeriodicProcTimer(1000);
                player->GetSpellHistory()->AddCooldown(EyeOfCorruptionAura, 0, 15s);
            }
        }
    }

    void OnPeriodicProc()
    {
        auto caster = at->GetCaster();
        if (at->GetInsideUnits().count(caster->GetGUID()))
        {
            caster->CastSpell(*at, EyeOfCorrptionDmg, true);
        }
    }
};

// 161895 - npc_thing_from_beyond_161895
struct npc_thing_from_beyond_161895 : public ScriptedAI
{
public:
    npc_thing_from_beyond_161895(Creature* creature) : ScriptedAI(creature) { }

    enum ThingFromBeyond
    {
        DmgOwnerSpell = 315197,
        SpawnSpell = 318392,
        EndAura = 319701,
    };

    void InitializeAI() override
    {
        if (!me->ToTempSummon())
            return;

        if (auto summoner = me->ToTempSummon()->GetSummonerUnit())
        {
            me->SetMaxHealth(summoner->GetMaxHealth());
            me->SetHealth(summoner->GetMaxHealth());
            DoCastSelf(SpawnSpell, true);
            DoCast(summoner, FixateSpell, true);
            //AttackStart(summoner);
        }
    }

    void JustDied(Unit* who) override
    {
        DoCastSelf(EndAura, true);
    }

    void UpdateAI(uint32 diff) override
    {
        if (!me->ToTempSummon())
            return;
        auto summoner = me->ToTempSummon()->GetSummonerUnit();
        if (!summoner)
        {
            //me->DespawnOrUnsummon();
            return;
        }

        if (summoner->isDead())
        {
            //me->DespawnOrUnsummon();
            return;
        }

        if (!UpdateVictim())
        {
            AttackStart(summoner);
            //me->GetMotionMaster()->MoveFollow(summoner, 1.0f, ChaseAngle(me->GetFollowAngle()));
            return;
        }

        if (me->IsWithinMeleeRange(summoner))
        {
            // explode
            me->CastSpell(summoner, DmgOwnerSpell, true);
            DoCastSelf(EndAura, true);

            if (summoner->HasAura(CascadingDisaster))
            {
                auto player = summoner->ToPlayer();
                if (player)
                {
                    auto corruptionAmount = player->GetEffectiveCorruption();
                    auto slowAmount = std::min<int32>(99, corruptionAmount + 10.0f);
                    player->GetSpellHistory()->ResetCooldown(MSReduction);
                    player->CastSpell(player, MSReduction, CastSpellExtraArgs(true).AddSpellBP0(-slowAmount));
                }

                summoner->CastSpell(summoner, EyeOfCorruption, true);
            }

            me->DespawnOrUnsummon();
        }
        DoMeleeAttackIfReady();
    }
};
/// ID: 318392 Grand Delusions
class spell_grand_delusions_spawn : public SpellScript
{
    PrepareSpellScript(spell_grand_delusions_spawn);

    enum GrandDelusions
    {
        CloneSpell = 318393,
    };

    void HandleDummy(SpellEffIndex eff)
    {
        PreventHitDefaultEffect(eff);
        if (auto hitUnit = GetHitUnit())
        {
            if (auto caster = GetCaster())
            {
                hitUnit->CastSpell(caster, CloneSpell, true);
            }
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_grand_delusions_spawn::HandleDummy, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
    }
};

/// ID: 315161 Eye of Corruption
class spell_eye_of_corruption_dmg : public SpellScript
{
    PrepareSpellScript(spell_eye_of_corruption_dmg);

    void HandleDmg(SpellEffIndex /*eff*/)
    {
        if (auto caster = GetCaster())
        {
            if (auto hitUnit = GetHitUnit())
            {
                uint32 damage = caster->CountPctFromMaxHealth(5);
                if (auto stacks = hitUnit->GetAura(EyeOfCorrptionDmg))
                    AddPct(damage, stacks->GetStackAmount() * 15);
                SetHitDamage(damage);
            }
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_eye_of_corruption_dmg::HandleDmg, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

void AddSC_spell_corruption()
{
    RegisterSpellScript(spell_grasping_tendrils);
    RegisterSpellScript(spell_eye_of_corruption);
    RegisterSpellScript(spell_grand_delusions);
    RegisterSpellScript(spell_inescapable_consequences);
    RegisterSpellScript(spell_grand_delusions_spawn);
    RegisterSpellScript(spell_eye_of_corruption_dmg);

    RegisterAreaTriggerAI(at_eye_of_corruption);

    RegisterCreatureAI(npc_thing_from_beyond_161895);
}
