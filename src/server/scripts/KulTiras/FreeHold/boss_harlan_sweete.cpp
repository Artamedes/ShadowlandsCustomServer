/*
 * Copyright (C) 2008-2020 TrinityCore <https://www.trinitycore.org/>
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
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

#include "free_hold.h"

enum HarlanSweeteSpells
{
    ///Harlan Sweete
    SPELL_DUAL_WIELD                    = 42459,

    SPELL_CANNON_BARRAGE_TARGET_ONE     = 257453,
    SPELL_CANNON_BARRAGE_TARGET_ALL     = 257304,
    SPELL_CANNON_BARRAGE_AURA           = 257305,
    SPELL_FLAMING_SHRAPNEL              = 257308,
    SPELL_CANNON_BARRAGE_CHOOSE_CANNON  = 258850,
    SPELL_CANNON_BARRAGE_MISSILE        = 257309,
    SPELL_FIERY_DEBRIS                  = 257460,

    SPELL_FACE_RANDOM_TARGET            = 256432,
    SPELL_SWIFTWIND_SABER               = 257278,
    SPELL_SWIFTWIND_SABER_ALL_HANDS     = 257454,
    SPELL_SWIFTWIND_SABER_SUMMON        = 257268,
    SPELL_SWIFTWIND_SABER_AT            = 257269,
    SPELL_SWIFTWIND_SABER_DMG           = 257293,

    SPELL_AVAST_YE                      = 257316,

    SPELL_LOADED_DICE_ALL_HANDS         = 257402,
    SPELL_LOADED_DICE_MAN_O_WAR         = 257458,

    ///Irontide Grenadiers
    SPELL_POWDER_BOMB_AT                = 257314,
    SPELL_POWDER_BOMB_DAMAGE            = 257315,
};

enum HarlanSweeteEvents
{
    EVENT_CANNON_BARRAGE = 1,
    EVENT_SWIFTWIND_SABER,
    EVENT_IRONTIDE_GRENADIER,
    EVENT_LOADED_DICE_ALL_HANDS,
    EVENT_LOADED_DICE_MAN_O_WAR,
};

enum HarlanTalk
{
    TALK_AGGRO,      //Think you can stand against me, swine? Allow me to educate you.
    TALK_60_PERCENT,
    TALK_JUST_DIED,
    TALK_AVAST_YE,
    TALK_CANNON_BARRAGE,
    TALK_30_PERCENT,
};

///< Npc Harlan Sweete - 126983
struct boss_harlan_sweete : public BossAI
{
    boss_harlan_sweete(Creature* creature) : BossAI(creature, FreeholdData::DATA_HARLAN_SWEETE)
    {
        ApplyAllImmunities(true);
        me->SetPowerType(POWER_ENERGY);
        me->SetPower(POWER_ENERGY, 100);
        me->SetMaxPower(POWER_ENERGY, 100);
	}

    void JustEngagedWith(Unit* who) override
    {
        Talk(HarlanTalk::TALK_AGGRO);
        _JustEngagedWith(who);

        events.ScheduleEvent(HarlanSweeteEvents::EVENT_SWIFTWIND_SABER, 10s);
        events.ScheduleEvent(HarlanSweeteEvents::EVENT_CANNON_BARRAGE, 20s);
        events.ScheduleEvent(HarlanSweeteEvents::EVENT_IRONTIDE_GRENADIER, 31s);
        damageEvents.ScheduleEventBelowHealthPct(HarlanSweeteEvents::EVENT_LOADED_DICE_ALL_HANDS, 60);
    }

    void JustSummoned(Creature* summon) override
    {
        if (summon && summon->GetEntry() == NPC_SWIFTWIND_SABER) { /*Nothing here*/ }
        else BossAI::JustSummoned(summon);
    }

    void ExecuteEvent(uint32 eventId) override
    {
        switch (eventId)
        {
        case HarlanSweeteEvents::EVENT_CANNON_BARRAGE:
            Talk(HarlanTalk::TALK_CANNON_BARRAGE);
            if (me->HasAura(HarlanSweeteSpells::SPELL_LOADED_DICE_ALL_HANDS))
                DoCastSelf(HarlanSweeteSpells::SPELL_CANNON_BARRAGE_TARGET_ALL);
            else
                DoCastSelf(HarlanSweeteSpells::SPELL_CANNON_BARRAGE_TARGET_ONE);
            events.Repeat(18s);
            break;

        case HarlanSweeteEvents::EVENT_SWIFTWIND_SABER:
            if (me->HasAura(HarlanSweeteSpells::SPELL_LOADED_DICE_ALL_HANDS))
            {
                DoCastSelf(HarlanSweeteSpells::SPELL_SWIFTWIND_SABER_ALL_HANDS);
                me->AttackStop();
                me->SetReactState(REACT_PASSIVE);
            }
            else
                DoCastSelf(HarlanSweeteSpells::SPELL_SWIFTWIND_SABER);
            events.Repeat(18s);
            break;

        case HarlanSweeteEvents::EVENT_IRONTIDE_GRENADIER:
            Talk(HarlanTalk::TALK_AVAST_YE);
            me->SummonCreature(FreeholdCreature::NPC_IRONTIDE_GRENADIER, GranadierSummonPos, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 5000ms);
            events.Repeat(20s);
            break;

        case HarlanSweeteEvents::EVENT_LOADED_DICE_ALL_HANDS:
            me->CastStop();
            Talk(HarlanTalk::TALK_60_PERCENT);
            DoCastSelf(HarlanSweeteSpells::SPELL_LOADED_DICE_ALL_HANDS);
            damageEvents.ScheduleEventBelowHealthPct(HarlanSweeteEvents::EVENT_LOADED_DICE_MAN_O_WAR, 30);
            break;

        case HarlanSweeteEvents::EVENT_LOADED_DICE_MAN_O_WAR:
            me->CastStop();
            Talk(HarlanTalk::TALK_30_PERCENT);
            DoCastSelf(HarlanSweeteSpells::SPELL_LOADED_DICE_MAN_O_WAR);
            break;

        default:
            break;
        }
    }

    void EnterEvadeMode(EvadeReason /*why*/) override
    {
        _EnterEvadeMode();
        if (instance)
        {
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            instance->SetBossState(DATA_HARLAN_SWEETE, FAIL);
        }
        _DespawnAtEvade();
    }

    void JustDied(Unit* /*killer*/) override
    {
        Talk(HarlanTalk::TALK_JUST_DIED);
        _JustDied();

        if (!instance || !instance->instance)
            return;

        switch (instance->instance->GetDifficultyID())
        {
        case Difficulty::DIFFICULTY_MYTHIC_KEYSTONE:
        case Difficulty::DIFFICULTY_MYTHIC:
            instance->DoCompleteAchievement(ACHIEVEMENT_FREEHOLD_MYTHIC);
        case Difficulty::DIFFICULTY_HEROIC:
            instance->DoCompleteAchievement(ACHIEVEMENT_FREEHOLD_HEROIC);
        case Difficulty::DIFFICULTY_NORMAL:
            instance->DoCompleteAchievement(ACHIEVEMENT_FREEHOLD_NORMAL);
            break;

        default:
            break;
        }
    }
};

///< Npc Swiftwind Saber - 129747
struct npc_swiftwind_saber : public ScriptedAI
{
    npc_swiftwind_saber(Creature* creature) : ScriptedAI(creature) {}

    void IsSummonedBy(WorldObject* summoner) override
    {
        me->DisableEvadeMode();
        me->SetReactState(REACT_PASSIVE);
        me->AddUnitState(UNIT_STATE_IGNORE_PATHFINDING);

        DoCastSelf(HarlanSweeteSpells::SPELL_SWIFTWIND_SABER_AT, true);

        me->AddDelayedEvent(2000, [this]()
        {
            Position target = me->GetPositionWithDistInFront(150.0f);
            Movement::MoveSplineInit init(me);
            init.Path().push_back(G3D::Vector3(me->GetPositionX(), me->GetPositionY(), me->GetPositionZ()));
            init.Path().push_back(G3D::Vector3(target.GetPositionX(), target.GetPositionY(), target.GetPositionZ()));
            init.SetVelocity(24.0f);
            init.SetFly();
            init.Launch();
        });
    }
};

///< Npc Irontide Granadier - 129758
struct npc_irontide_granadier : public ScriptedAI
{
    npc_irontide_granadier(Creature* creature) : ScriptedAI(creature) { }

    void IsSummonedBy(WorldObject* /*summoner*/) override
    {
        targetGUID = ObjectGuid::Empty;

        me->GetScheduler().Schedule(Milliseconds(500), [this](TaskContext context)
        {
            if (Unit* granadier = GetContextUnit())
                granadier->GetMotionMaster()->MoveJump({ -1583.95f, -555.13f, 71.0f }, 10.0f, 10.0f);
        });
    }

    void MovementInform(uint32 type, uint32 pointId) override
    {
        if (type == EFFECT_MOTION_TYPE && pointId == EVENT_JUMP)
        {
            if (TempSummon* tempMe = me->ToTempSummon())
            {
                if (auto summoner = tempMe->GetSummonerUnit())
                {
                    if (Unit* target = summoner->GetAI()->SelectTarget(SelectTargetMethod::Random))
                    {
                        me->CastSpell(target, HarlanSweeteSpells::SPELL_POWDER_BOMB_AT, true);
                        targetGUID = target->GetGUID();
                    }
                }
            }
        }
    }

    void OnAddThreat(Unit* victim, float& fThreat, SpellSchoolMask /*schoolMask*/, SpellInfo const* /*threatSpell*/)
    {
        fThreat = 0;
    }

    void UpdateAI(uint32 diff) override
    {
        if (!me->isMoving() && targetGUID != ObjectGuid::Empty)
        {
            if (Player* player = ObjectAccessor::GetPlayer(*me, targetGUID))
                me->GetMotionMaster()->MovePoint(0, player->GetPosition());
        }
    }

private:
    ObjectGuid targetGUID;
};

///< Spell Face Random Target - 256432
struct spell_face_random_target : public SpellScript
{
    PrepareSpellScript(spell_face_random_target);

    void HandleOnEffectHitTarget(SpellEffIndex effIndex)
    {
        if (Unit* caster = GetCaster())
            if (Unit* target = GetHitUnit())
                caster->SetFacingToObject(target);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_face_random_target::HandleOnEffectHitTarget, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

///< Spell Cannon Barrage Target Select - 257453 / 257304
struct spell_cannon_barrage_target_player : public SpellScript
{
    PrepareSpellScript(spell_cannon_barrage_target_player);

    void HandleDummy(SpellEffIndex /*effIndex*/)
    {
        if (Unit* caster = GetCaster())
            if (Unit* target = GetHitUnit())
                caster->CastSpell(target, HarlanSweeteSpells::SPELL_CANNON_BARRAGE_AURA, true);
    }

    void FilterTargets(std::list<WorldObject*> &targetsList)
    {
        targetsList.remove_if([targetsList](WorldObject* obj) -> bool
        {
            return !obj || (obj->ToPlayer()->GetRoleForGroup() == ROLE_TANK && targetsList.size() > 1);
        });
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_cannon_barrage_target_player::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_cannon_barrage_target_player::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
    }
};

///< Spell Cannon Barrage Aura - 257305 
struct spell_cannon_barrage_aura : public AuraScript
{
    PrepareAuraScript(spell_cannon_barrage_aura);

    void OnPeriodic(AuraEffect const* aurEff)
    {
        if (Unit* caster = GetCaster())
            if (Unit* target = GetTarget())
                caster->CastSpell(target, HarlanSweeteSpells::SPELL_FLAMING_SHRAPNEL, true);
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_cannon_barrage_aura::OnPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
    }
};

///< Spell Cannon Barrage - 258850
struct spell_cannon_barrage_target_cannon : public SpellScript
{
    PrepareSpellScript(spell_cannon_barrage_target_cannon);

    void HandleDummy(SpellEffIndex /*effIndex*/)
    {
        if (Unit* caster = GetCaster())
            if (Unit* target = GetHitUnit())
                target->CastSpell(caster, HarlanSweeteSpells::SPELL_CANNON_BARRAGE_MISSILE, true);
    }

    void FilterTargets(std::list<WorldObject*>& targetsList)
    {
        targetsList.remove_if([](WorldObject* obj) -> bool
        {
            return !obj || obj->GetEntry() != NPC_IRONTIDE_CANNON;
        });
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_cannon_barrage_target_cannon::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_cannon_barrage_target_cannon::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENTRY);
    }
};

///< Spell Swiftwind Saber - 257278
struct spell_swiftwind_saber : public SpellScript
{
    PrepareSpellScript(spell_swiftwind_saber);

    void HandleAfterCast()
    {
        if (Unit* caster = GetCaster())
        {
            caster->CastSpell(caster, SPELL_FACE_RANDOM_TARGET, true);

            float x, y, z, o;
            caster->GetPosition(x, y, z, o);

            for (uint8 i = 0; i < 3; i++)
            {
                caster->SetOrientation(o + i * float(M_PI_2 / 3.0f));
                caster->CastSpell(Position(x, y, z), HarlanSweeteSpells::SPELL_SWIFTWIND_SABER_SUMMON, true);
            }
        }
    }

    void Register() override
    {
        AfterCast += SpellCastFn(spell_swiftwind_saber::HandleAfterCast);
    }
};

///< Swiftwind Saber All Hands - 257454
struct spell_swiftwind_saber_all_hands : public SpellScript
{
    PrepareSpellScript(spell_swiftwind_saber_all_hands);

    void HandleAfterCast()
    {
        if (Unit* caster = GetCaster())
        {
            caster->CastSpell(caster, SPELL_FACE_RANDOM_TARGET, true);
            float original_o = caster->GetOrientation();

            for (uint8 i = 0; i < 3; i++)
            {
                float o = original_o + i * float(M_PI / 6.0f);
                caster->SetOrientation(o);
                caster->CastSpell(caster, HarlanSweeteSpells::SPELL_SWIFTWIND_SABER_SUMMON, true);
            }

            original_o = frand(original_o - float(M_PI / 6.0f), original_o + float(M_PI / 6.0f));

            for (uint8 i = 1; i < 4; i++)
            {
                caster->AddDelayedEvent(500 * i, [caster, i, original_o]()
                {
                    if (caster->IsInWorld() && caster->IsAlive())
                    {
                        float o = original_o;

                        for (uint8 j = 0; j < 3; j++)
                        {
                            o = original_o + (3 * (i - 1) + j) * float(M_PI / 6.0f);
                            caster->SetOrientation(o);
                            caster->CastSpell(caster, HarlanSweeteSpells::SPELL_SWIFTWIND_SABER_SUMMON, true);
                        }
                        caster->SetFacingTo(o);
                    }
                });
            }

            caster->AddDelayedEvent(2100, [caster]()
            {
                if (caster->IsInWorld() && caster->IsAlive() && caster->IsCreature())
                {
                    caster->ToCreature()->SetReactState(REACT_AGGRESSIVE);
                    if (caster->ToCreature()->AI())
                        caster->ToCreature()->AI()->DoZoneInCombat();
                }
            });
        }
    }

    void Register() override
    {
        AfterCast += SpellCastFn(spell_swiftwind_saber_all_hands::HandleAfterCast);
    }
};

///< Spell Cannon Barrage Missile - 257310
struct spell_cannon_barrage_filter : public SpellScript
{
    PrepareSpellScript(spell_cannon_barrage_filter);

    void HandleTargets(std::list<WorldObject*>& targetsList)
    {
        targetsList.remove_if([this](WorldObject* obj)->bool
        {
            return !obj || !obj->IsPlayer();
        });
    }

    void FilterTargets(std::list<WorldObject*>& targetsList)
    {
        targetsList.remove_if([this](WorldObject* obj)->bool
        {
            return !obj || obj->GetEntry() != NPC_CHEST_O_BOOTY;
        });
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_cannon_barrage_filter::HandleTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ENTRY);
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_cannon_barrage_filter::FilterTargets, EFFECT_2, TARGET_UNIT_DEST_AREA_ENTRY);
    }
};

///< Spell Powder Bomb Aura - 257314
struct spell_freehold_bomb_aura : public AuraScript
{
    PrepareAuraScript(spell_freehold_bomb_aura);

    void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        AuraRemoveMode removeMode = GetTargetApplication()->GetRemoveMode();
        if (removeMode != AURA_REMOVE_BY_EXPIRE)
            return;

        if (Unit* caster = GetCaster())
            caster->CastSpell(caster, HarlanSweeteSpells::SPELL_POWDER_BOMB_DAMAGE, true);
    }

    void Register() override
    {
        OnEffectRemove += AuraEffectRemoveFn(spell_freehold_bomb_aura::OnRemove, EFFECT_1, SPELL_AURA_AREA_TRIGGER, AURA_EFFECT_HANDLE_REAL);
    }
};

///< Areatriger Cannon Barrage - SpellId: 257310, AtID: 16728
struct at_cannon_barrage : AreaTriggerAI
{
    at_cannon_barrage(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger) {}

    void OnUnitEnter(Unit* unit) override
    {
        if (Unit* caster = at->GetCaster())
            if (unit && caster->IsValidAttackTarget(unit))
                caster->CastSpell(unit, HarlanSweeteSpells::SPELL_FIERY_DEBRIS, true);
    }

    void OnUnitExit(Unit* unit) override
    {
        if (Unit* caster = at->GetCaster())
        {
            if (unit && unit->HasAura(HarlanSweeteSpells::SPELL_FIERY_DEBRIS, caster->GetGUID()))
                unit->RemoveAurasDueToSpell(HarlanSweeteSpells::SPELL_FIERY_DEBRIS, caster->GetGUID());
        }
    }
};

///< Areatriger Swiftwind Saber - SpellID: 257269, AtID: 16715
struct at_swiftwind_saber : AreaTriggerAI
{
    at_swiftwind_saber(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger) {}

    void OnUnitEnter(Unit* unit) override
    {
        if (Unit* caster = at->GetCaster())
            if (unit && caster->IsValidAttackTarget(unit))
                caster->CastSpell(unit, HarlanSweeteSpells::SPELL_SWIFTWIND_SABER_DMG, true);
    }
};

///< Areatrigger Powder Bomb - SpellID: 257314, AtID: 16718
struct at_freehold_powder_bomb : AreaTriggerAI
{
    at_freehold_powder_bomb(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger) {}

    void OnUnitEnter(Unit* unit) override
    {
        if (Unit* caster = at->GetCaster())
        {
            if (unit && caster->IsValidAttackTarget(unit))
            {
                caster->CastSpell(unit, HarlanSweeteSpells::SPELL_POWDER_BOMB_DAMAGE, true);

                if (caster->IsCreature())
                    caster->ToCreature()->DespawnOrUnsummon(1s);
            }
        }
    }

    void OnRemove() override
    {
        if (Unit* caster = at->GetCaster())
            if (caster->IsAlive())
                caster->CastSpell(caster, HarlanSweeteSpells::SPELL_POWDER_BOMB_DAMAGE, true);
    }
};

//12998
struct achievement_the_sweety_booty : public AchievementCriteriaScript
{
public:
    achievement_the_sweety_booty() : AchievementCriteriaScript("achievement_the_sweety_booty") {}

    bool OnCheck(Player* /*player*/, Unit* /*target*/) override
    {
        //ACHIEVEMENT_THAT_SWEETY_BOOTY
        return false;
    }
};


void AddSC_boss_harlan_sweete()
{
    //Creatures
    RegisterCreatureAI(boss_harlan_sweete);
    RegisterCreatureAI(npc_swiftwind_saber);
    RegisterCreatureAI(npc_irontide_granadier);

    //Spells
    RegisterSpellScript(spell_face_random_target);
    RegisterSpellScript(spell_cannon_barrage_target_player);
    RegisterSpellScript(spell_cannon_barrage_target_cannon);
    RegisterSpellScript(spell_swiftwind_saber);
    RegisterSpellScript(spell_swiftwind_saber_all_hands);
    RegisterSpellScript(spell_cannon_barrage_filter);

    //Auras
    RegisterSpellScript(spell_cannon_barrage_aura);
    RegisterSpellScript(spell_freehold_bomb_aura);

    //Areatriggers
    RegisterAreaTriggerAI(at_cannon_barrage);
    RegisterAreaTriggerAI(at_swiftwind_saber);
    RegisterAreaTriggerAI(at_freehold_powder_bomb);

    //Achievements
    new achievement_the_sweety_booty();
}
