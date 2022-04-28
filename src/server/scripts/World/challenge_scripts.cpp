/*
 * Copyright (C) 2008-2012 TrinityCore <http://www.trinitycore.org/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "AreaTrigger.h"
#include "AreaTriggerAI.h"
#include "DB2Stores.h"
#include "ScriptMgr.h"
#include "ChallengeMode.h"
#include "ChallengeModeMgr.h"
#include "ScenarioMgr.h"
#include "GameTables.h"
#include "SpellAuraEffects.h"
#include "SpellMgr.h"

// 105877 - Volcanic Plume
//Last Update 8.0.1 Build 28153
struct npc_challenger_volcanic_plume : ScriptedAI
{
    npc_challenger_volcanic_plume(Creature* creature) : ScriptedAI(creature) {}

    EventMap events;

    void Reset() override
    {
        events.Reset();
        events.ScheduleEvent(1, 250ms);
    }

    void UpdateAI(uint32 diff) override
    {
        events.Update(diff);

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        while (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
            case 1:
                me->CastSpell(me, SPELL_CHALLENGER_VOLCANIC_PLUME, false);
                break;
            default:
                break;
            }
        }
    }
};

// 125656 - Explosives
//Last Update 8.0.1 Build 28153
struct  npc_challenger_explosives : ScriptedAI
{
    npc_challenger_explosives(Creature* creature) : ScriptedAI(creature)
    {
        me->AddUnitTypeMask(UNIT_MASK_TOTEM);
        me->SetReactState(REACT_PASSIVE);
        ApplyAllImmunities(true);
    }

    EventMap events;

    void IsSummonedBy(WorldObject* summoner) override
    {
        DoCast(me, SPELL_CHALLENGER_EXPLOSIVES_VISUAL, true);
        events.ScheduleEvent(1, 500ms);
    }

    void OnSpellCast(SpellInfo const* spellInfo) override
    {
        if (spellInfo->Id == SPELL_CHALLENGER_EXPLOSIVES_DMG)
            me->DespawnOrUnsummon(100ms);
    }

    void UpdateAI(uint32 diff) override
    {
        events.Update(diff);

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        while (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
            case 1:
                DoCast(SPELL_CHALLENGER_EXPLOSIVES_DMG);
                break;
            }
        }
    }
};

// 141851 - Spawn of G'huun
//Last Update 8.0.1 Build 28153
struct  npc_challenger_spawn_of_ghuun : ScriptedAI
{
    npc_challenger_spawn_of_ghuun(Creature* creature) : ScriptedAI(creature) { }

    EventMap events;
    ObjectGuid targetGuid;

    void SetGUID(ObjectGuid const& guid, int32 id) override
    {
        if (targetGuid.IsEmpty())
        {
            targetGuid = guid;
            events.ScheduleEvent(1, 500ms);
        }
    }

    void OnSpellCast(SpellInfo const* spellInfo) override
    {
        if (spellInfo->Id == SPELL_CHALLENGER_INFEST)
            me->DespawnOrUnsummon(100ms);
    }

    void JustDied(Unit* /*killer*/) override
    {
        me->StopMoving();
        me->GetMotionMaster()->Clear();
    }

    void UpdateAI(uint32 diff) override
    {
        events.Update(diff);

        if (me->HasUnitState(UNIT_STATE_CASTING) || me->isDead())
            return;

        if (!me->HasUnitState(UNIT_STATE_NOT_MOVE) && !me->isMoving() && !targetGuid.IsEmpty())
        {
            if (Creature* target = ObjectAccessor::GetCreature(*me, targetGuid))
            {
                me->GetMotionMaster()->MoveFollow(target, 1.0f, me->GetFollowAngle());
                events.RescheduleEvent(1, 500ms);
            }
        }

        while (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
            case 1:
                if (Creature* target = ObjectAccessor::GetCreature(*me, targetGuid))
                {
                    if (me->GetDistance(target) < 3.0f)
                    {
                        me->StopMoving();
                        me->GetMotionMaster()->Clear();
                        me->CastSpell(target, SPELL_CHALLENGER_INFEST, false);
                        break;
                    }
                }
                events.ScheduleEvent(1, 500ms);
                break;
            }
        }
    }
};

// 209859 - Bolster
//Last Update 8.0.1 Build 28153
class spell_challengers_bolster : public SpellScript
{
    PrepareSpellScript(spell_challengers_bolster);

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        if (targets.empty())
            return;

        std::list<WorldObject*> temp;
        for (auto object : targets)
        {
            if (auto unit = object->ToUnit())
            {
                if (!unit->IsInCombat() || unit->IsPlayer())
                    continue;

                auto owner = unit->GetAnyOwner();
                if (owner && owner->IsPlayer())
                    continue;

                if (Creature* creature = unit->ToCreature())
                    if (creature->IsDungeonBoss())
                        continue;

                temp.push_back(object);
            }
        }
        targets = temp;
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_challengers_bolster::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ALLY);
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_challengers_bolster::FilterTargets, EFFECT_1, TARGET_UNIT_SRC_AREA_ALLY);
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_challengers_bolster::FilterTargets, EFFECT_2, TARGET_UNIT_SRC_AREA_ALLY);
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_challengers_bolster::FilterTargets, EFFECT_3, TARGET_UNIT_SRC_AREA_ALLY);
    }
};

//277567 Infest
//Last Update 8.0.1 Build 28153
class spell_challenger_infest : public SpellScript
{
public:
    PrepareSpellScript(spell_challenger_infest);

    void HandleScript(SpellEffIndex /**/)
    {
        if (Unit* unit = GetHitUnit())
            unit->CastSpell(unit, SPELL_CHALLENGER_SIMBIOTE_OF_GHUUN, true);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_challenger_infest::HandleScript, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
    }
};

// 206150 - Challenger's Might
// Last Update 8.0.1 Build 28153
class aura_challengers_might : public AuraScript
{
    PrepareAuraScript(aura_challengers_might);

    uint8 volcanicTimer = 0;
    uint8 volcanicTick = 0;
    uint32 explosivesTimer = 0;
    uint32 necroticProcDelay = 0;

    void CalculateAmount(AuraEffect const* aurEff, int32& amount, bool& /*canBeRecalculated*/)
    {
        Unit* caster = GetCaster();
        if (!caster)
            return;

        InstanceScript* instance = caster->GetInstanceScript();
        if (!instance)
            return;

        auto const& challenge = instance->GetChallenge();
        if (!challenge)
            return;

        uint32 challengeLevel = challenge->GetChallengeLevel();
        float modHealth = challenge->GetHealthMultiplier(challengeLevel);
        float modDamage = challenge->GetDamageMultiplier(challengeLevel);

        modHealth = round((modHealth - 1.0f) * 100.0f);
        modDamage = round((modDamage - 1.0f) * 100.0f);

        bool isDungeonBoss = false;
        if (Creature* creature = caster->ToCreature())
            if (creature->IsDungeonBoss())
                isDungeonBoss = true;

        if (isDungeonBoss)
        {
            if (challenge->HasAffix(Tyrannical))
            {
                modHealth += 40.0f;
                modDamage += 15.0f;
            }
        }
        else if (challenge->HasAffix(Fortified))
        {
            modHealth += 20.0f;
            modDamage += 30.0f;
        }

        switch (aurEff->GetEffIndex())
        {
        case EFFECT_0:
            amount = modHealth;
            break;
        case EFFECT_1:
            amount = modDamage;
            break;
        case EFFECT_2:
            amount = challenge->HasAffix(Raging) && !isDungeonBoss ? 1 : 0;
            break;
        case EFFECT_3:
            amount = challenge->HasAffix(Bolstering) ? 1 : 0;
            break;
        case EFFECT_4:
            amount = challenge->HasAffix(Tyrannical) && isDungeonBoss ? 1 : 0;
            break;
        case EFFECT_7:
            amount = challenge->HasAffix(Volcanic) ? 1 : 0;
            volcanicTick = urand(3, 10);
            break;
        case EFFECT_8:
            amount = challenge->HasAffix(Necrotic) ? 1 : 0;
            break;
        case EFFECT_9:
            amount = challenge->HasAffix(Fortified) && !isDungeonBoss ? 1 : 0;
            break;
        case EFFECT_10:
            amount = challenge->HasAffix(Sanguine) ? 1 : 0;
            break;
        case EFFECT_11:
            amount = challenge->HasAffix(Quaking) ? 1 : 0;
            break;
        case EFFECT_12:
            amount = challenge->HasAffix(Explosive) ? 1 : 0;
            explosivesTimer = urandms(2, 10);
            break;
        case EFFECT_13:
            amount = challenge->HasAffix(Bursting) ? 1 : 0;
            break;
        default:
            break;
        }
    }

    // Volcanic
    void OnTick(AuraEffect const* aurEff)
    {
        if (!aurEff->GetAmount() || !GetCaster()->IsInCombat())
            return;

        if (volcanicTimer == volcanicTick)
            volcanicTimer = 0;
        else
        {
            ++volcanicTimer;
            return;
        }

        auto caster = GetCaster()->ToCreature();
        if (!caster || (caster->AI() && caster->AI()->IsInControl()) || !caster->IsHostileToPlayers())
            return;

        if (auto owner = caster->GetAnyOwner())
        {
            if (owner->IsPlayer())
                return;

            if (owner->IsCreature() && !owner->ToCreature()->IsDungeonBoss() && !roll_chance_f(20.0f))
                return;
        }

        auto _map = caster->GetMap();
        if (!_map)
            return;

        Map::PlayerList const& players = _map->GetPlayers();
        for (Map::PlayerList::const_iterator itr = players.begin(); itr != players.end(); ++itr)
        {
            if (auto player = itr->GetSource())
            {
                if (player->IsInCombat() && player->IsValidAttackTarget(caster))
                    if (!caster->IsWithinMeleeRange(player)&& caster->GetDistance(player) < 60.0f) // Offlike 10m
                        player->CastSpell(player, SPELL_CHALLENGER_SUMMON_VOLCANIC_PLUME, true);
            }
        }
    }

    void OnNecroticProc(AuraEffect* auraEffect, ProcEventInfo& eventInfo)
    {
        if (necroticProcDelay || !auraEffect->GetAmount())
            return;
        else
            necroticProcDelay = 1000;

        if (Unit* caster = GetCaster())
            if (Unit* target = eventInfo.GetActionTarget())
                caster->CastSpell(target, SPELL_CHALLENGER_NECROTIC, true);
    }

    void OnEnragingProc(AuraEffect* auraEffect, ProcEventInfo& eventInfo)
    {
        if (Unit* caster = GetCaster())       
            if(caster->HasAura(SPELL_CHALLENGER_RAGING) || caster->HealthAbovePct(30) || !auraEffect->GetAmount())
                PreventDefaultAction();            
    }

    //Explosives
    void OnUpdate(uint32 diff, AuraEffect* aurEff)
    {
        if (necroticProcDelay)
        {
            if (necroticProcDelay <= diff)
                necroticProcDelay = 0;
            else
                necroticProcDelay -= diff;
        }

        if (aurEff->GetEffIndex() != EFFECT_12)
            return;

        if (!aurEff->GetAmount() || !GetCaster()->IsInCombat())
        {
            if(!explosivesTimer)
                explosivesTimer = urandms(2, 10);
            return;
        }   

        if (explosivesTimer <= diff)
            explosivesTimer = urandms(8, 16);
        else
        {
            explosivesTimer -= diff;
            return;
        }

        auto caster = GetCaster()->ToCreature();
        if (!caster || (caster->AI() && caster->AI()->IsInControl()) || !caster->IsHostileToPlayers())
            return;

        if (auto owner = caster->GetAnyOwner())
        {
            if (owner->IsPlayer())
                return;

            if (owner->IsCreature() && !owner->ToCreature()->IsDungeonBoss())
                return;

            //For boss that have summon this summon has less chance for spawn
            if (owner->IsCreature() && owner->ToCreature()->IsDungeonBoss() && !roll_chance_f(20.0f))
                return;
        }

        auto _map = caster->GetMap();
        if (!_map)
            return;

        Map::PlayerList const& players = _map->GetPlayers();
        for (Map::PlayerList::const_iterator itr = players.begin(); itr != players.end(); ++itr)
        {
            if (auto player = itr->GetSource())
            {
                if (player->IsInCombat() && player->IsValidAttackTarget(caster))
                    if (caster->GetDistance(player) < 60.0f)
                    {
                        caster->CastSpell(player, SPELL_CHALLENGER_EXPLOSIVES_SUMMON, true);
                        return;
                    }
            }
        }
    }

    void Register() override
    {
        DoEffectCalcAmount += AuraEffectCalcAmountFn(aura_challengers_might::CalculateAmount, EFFECT_0, SPELL_AURA_MOD_INCREASE_HEALTH_PERCENT);
        DoEffectCalcAmount += AuraEffectCalcAmountFn(aura_challengers_might::CalculateAmount, EFFECT_1, SPELL_AURA_MOD_DAMAGE_PERCENT_DONE);
        DoEffectCalcAmount += AuraEffectCalcAmountFn(aura_challengers_might::CalculateAmount, EFFECT_2, SPELL_AURA_DUMMY);
        DoEffectCalcAmount += AuraEffectCalcAmountFn(aura_challengers_might::CalculateAmount, EFFECT_3, SPELL_AURA_DUMMY);
        DoEffectCalcAmount += AuraEffectCalcAmountFn(aura_challengers_might::CalculateAmount, EFFECT_4, SPELL_AURA_DUMMY);
        DoEffectCalcAmount += AuraEffectCalcAmountFn(aura_challengers_might::CalculateAmount, EFFECT_7, SPELL_AURA_PERIODIC_DUMMY);
        DoEffectCalcAmount += AuraEffectCalcAmountFn(aura_challengers_might::CalculateAmount, EFFECT_8, SPELL_AURA_DUMMY);
        DoEffectCalcAmount += AuraEffectCalcAmountFn(aura_challengers_might::CalculateAmount, EFFECT_9, SPELL_AURA_DUMMY);
        DoEffectCalcAmount += AuraEffectCalcAmountFn(aura_challengers_might::CalculateAmount, EFFECT_10, SPELL_AURA_DUMMY);
        DoEffectCalcAmount += AuraEffectCalcAmountFn(aura_challengers_might::CalculateAmount, EFFECT_11, SPELL_AURA_DUMMY);
        DoEffectCalcAmount += AuraEffectCalcAmountFn(aura_challengers_might::CalculateAmount, EFFECT_12, SPELL_AURA_DUMMY);
        DoEffectCalcAmount += AuraEffectCalcAmountFn(aura_challengers_might::CalculateAmount, EFFECT_13, SPELL_AURA_DUMMY);       
        OnEffectPeriodic += AuraEffectPeriodicFn(aura_challengers_might::OnTick, EFFECT_7, SPELL_AURA_PERIODIC_DUMMY);
        OnEffectProc += AuraEffectProcFn(aura_challengers_might::OnNecroticProc, EFFECT_8, SPELL_AURA_DUMMY);
        OnEffectProc += AuraEffectProcFn(aura_challengers_might::OnEnragingProc, EFFECT_2, SPELL_AURA_DUMMY);
        OnEffectUpdate += AuraEffectUpdateFn(aura_challengers_might::OnUpdate, EFFECT_11, SPELL_AURA_DUMMY);
        OnEffectUpdate += AuraEffectUpdateFn(aura_challengers_might::OnUpdate, EFFECT_12, SPELL_AURA_DUMMY);
    }
};

// 206151 - Challenger's Burden
//Last Update 8.0.1 Build 28153
class aura_challengers_burden : public AuraScript
{
    PrepareAuraScript(aura_challengers_burden);

    void CalculateAmount(AuraEffect const* aurEff, int32& amount, bool& /*canBeRecalculated*/)
    {
        Unit* caster = GetCaster();
        if (!caster)
            return;

        Player* player = GetCaster()->ToPlayer();
        if (!player)
            return;

        InstanceScript* instance = caster->GetInstanceScript();
        if (!instance)
            return;

        auto const& challenge = instance->GetChallenge();
        if (!challenge)
            return;

        switch (aurEff->GetEffIndex())
        {
        case EFFECT_1:
        case EFFECT_3:
            amount = challenge->HasAffix(Grievous);
            break;
        case EFFECT_2:
            if (!challenge->HasAffix(Skittish) || !player->IsActiveSpecTankSpec())
                amount = 0;
            break;
        default:
            break;
        }
    }

    // Grievous
    void OnTick(AuraEffect const* aurEff)
    {
        if (!aurEff->GetAmount() || !GetUnitOwner() || !GetUnitOwner()->IsAlive())
            return;

        if (GetUnitOwner()->HealthBelowPct(90))
        {
            if (!GetUnitOwner()->HasAura(SPELL_CHALLENGER_GRIEVOUS_WOUND))
            {
                if (SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(SPELL_CHALLENGER_GRIEVOUS_WOUND))
                {
                    int32 bp = round(spellInfo->GetEffect(EFFECT_0).BasePoints / 10);
                    if(bp)
                        GetUnitOwner()->CastCustomSpell(SPELL_CHALLENGER_GRIEVOUS_WOUND, SPELLVALUE_BASE_POINT0, bp, GetUnitOwner(), true);
                }                    
            }
        }
        else
            GetUnitOwner()->RemoveAurasDueToSpell(SPELL_CHALLENGER_GRIEVOUS_WOUND);
    }

    void Register() override
    {
        DoEffectCalcAmount += AuraEffectCalcAmountFn(aura_challengers_burden::CalculateAmount, EFFECT_1, SPELL_AURA_DUMMY);
        DoEffectCalcAmount += AuraEffectCalcAmountFn(aura_challengers_burden::CalculateAmount, EFFECT_2, SPELL_AURA_MOD_THREAT);
        DoEffectCalcAmount += AuraEffectCalcAmountFn(aura_challengers_burden::CalculateAmount, EFFECT_3, SPELL_AURA_PERIODIC_DUMMY);
        OnEffectPeriodic += AuraEffectPeriodicFn(aura_challengers_burden::OnTick, EFFECT_3, SPELL_AURA_PERIODIC_DUMMY);       
    }
};

//240443 Burst
//Last Update 8.0.1 Build 28153
class aura_challengers_burst : public AuraScript
{
    PrepareAuraScript(aura_challengers_burst);

    void OnTick(AuraEffect const* /*aurEff*/)
    {
        Unit* target = GetTarget();
        if (!target)
            return;

        if (SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(SPELL_CHALLENGER_BURSTING_DAMAGE))
        {
            int32 bp = spellInfo->GetEffect(EFFECT_0).BasePoints * target->GetAuraCount(GetId());
            target->CastCustomSpell(target, SPELL_CHALLENGER_BURSTING_DAMAGE, &bp, nullptr, nullptr, true);
        }
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(aura_challengers_burst::OnTick, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

//240559 Grievous Wound
//Last Update 8.0.1 Build 28153
class aura_challengers_grievous_wound : public AuraScript
{
    PrepareAuraScript(aura_challengers_grievous_wound);

    void OnTick(AuraEffect const* aurEff)
    {
        if ((aurEff->GetTickNumber() - 1) > 0 && (aurEff->GetTickNumber() - 1) % 2)
            if (auto aura = aurEff->GetBase())
                aura->ModStackAmount(1, AURA_REMOVE_BY_DEFAULT, false, false);
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(aura_challengers_grievous_wound::OnTick, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE_PERCENT);
    }
};

//226489 Sanguine Ichor
//Last Update 8.0.1 Build 28153
struct at_sanguine_ichor : AreaTriggerAI
{
    at_sanguine_ichor(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger) {}

    void OnUnitEnter(Unit* unit) override
    {
        if (Unit* caster = at->GetCaster())
        {
            if (caster->IsValidAttackTarget(unit))
                unit->CastSpell(unit, SPELL_CHALLENGER_SANGUINE_DMG, true);
            else
                unit->CastSpell(unit, SPELL_CHALLENGER_SANGUINE_HEAL, true);
        }
    }

    void OnUnitExit(Unit* unit) override
    {
        unit->RemoveAura(SPELL_CHALLENGER_SANGUINE_DMG);
        unit->RemoveAura(SPELL_CHALLENGER_SANGUINE_HEAL);
    }
};

//277242 Symbiote of G'huun
//Last Update 8.0.1 Build 28153
struct at_symbiote_of_ghuun : AreaTriggerAI
{
    at_symbiote_of_ghuun(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger) {}

    void OnUnitEnter(Unit* unit) override
    {
        if (Unit* caster = at->GetCaster())
            if (caster != unit)
                if (!caster->IsValidAttackTarget(unit))
                    unit->CastSpell(unit, SPELL_CHALLENGER_REGENERATIVE_BLOOD_AURA, true);
    }

    void OnUnitExit(Unit* unit) override
    {
        unit->RemoveAura(SPELL_CHALLENGER_REGENERATIVE_BLOOD_AURA);
    }
};

void AddSC_challenge_scripts()
{
    RegisterCreatureAI(npc_challenger_volcanic_plume);
    RegisterCreatureAI(npc_challenger_explosives);
    RegisterCreatureAI(npc_challenger_spawn_of_ghuun);
    RegisterSpellScript(spell_challengers_bolster);
    RegisterSpellScript(spell_challenger_infest);    
    RegisterSpellScript(aura_challengers_might);
    RegisterSpellScript(aura_challengers_burden);
    RegisterSpellScript(aura_challengers_burst);
    RegisterSpellScript(aura_challengers_grievous_wound);
    RegisterAreaTriggerAI(at_sanguine_ichor);
    RegisterAreaTriggerAI(at_symbiote_of_ghuun);    
}
