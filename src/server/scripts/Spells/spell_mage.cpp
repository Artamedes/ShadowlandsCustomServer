/*
 * Copyright (C) 2017-2018 AshamaneProject <https://github.com/AshamaneProject>
 * Copyright (C) 2008-2018 TrinityCore <https://www.trinitycore.org/>
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

/*
 * Scripts for spells with SPELLFAMILY_MAGE and SPELLFAMILY_GENERIC spells used by mage players.
 * Ordered alphabetically using scriptname.
 * Scriptnames of files in this file should be prefixed with "spell_mage_".
 */

#include "AreaTrigger.h"
#include "AreaTriggerAI.h"
#include "Creature.h"
#include "CombatAI.h"
#include "GridNotifiers.h"
#include "Group.h"
#include "MotionMaster.h"
#include "ObjectAccessor.h"
#include "PhasingHandler.h"
#include "Player.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "SpellAuraEffects.h"
#include "SpellHistory.h"
#include "SpellMgr.h"
#include "SpellScript.h"
#include "CellImpl.h"
#include "TemporarySummon.h"

enum MageSpells
{
    SPELL_MAGE_ALTER_TIME_AURA                   = 110909,
    SPELL_MAGE_ALTER_TIME_VISUAL                 = 347402,
    SPELL_MAGE_ARCANE_ALTER_TIME_AURA            = 342246,
    SPELL_MAGE_MASTER_OF_TIME                    = 342249,
    SPELL_MAGE_ARCANE_CHARGE                     = 36032,
    //7.3.2.25549
    SPELL_MAGE_COLD_SNAP                         = 235219,
    SPELL_MAGE_FROST_NOVA                        = 122,
    SPELL_MAGE_CONE_OF_COLD                      = 120,
    SPELL_MAGE_CONE_OF_COLD_SLOW                 = 212792,
    SPELL_MAGE_ICE_BARRIER                       = 11426,
    SPELL_MAGE_ICE_BLOCK                         = 45438,
    SPELL_MAGE_GLACIAL_INSULATION                = 235297,
    SPELL_MAGE_BONE_CHILLING                     = 205027,
    SPELL_MAGE_BONE_CHILLING_BUFF                = 205766,
    SPELL_MAGE_CHILLED                           = 205708,
    SPELL_MAGE_ICE_LANCE                         = 30455,
    SPELL_MAGE_ICE_LANCE_TRIGGER                 = 228598,
    SPELL_MAGE_THERMAL_VOID                      = 155149,
    SPELL_MAGE_ICY_VEINS                         = 12472,
    SPELL_MAGE_GLACIAL_SPIKE                     = 199786,
    SPELL_MAGE_ICICLE_PERIODIC_TRIGGER           = 148023,
    SPELL_MAGE_FLURRY_DEBUFF_PROC                = 228354,
    SPELL_MAGE_FLURRY                            = 44614,
    SPELL_MAGE_FLURRY_DAMAGE                     = 228672,
    SPELL_MAGE_FLURRY_CHILL_PROC                 = 228358,
    SPELL_MAGE_FLURRY_VISUAL                     = 228596,
    SPELL_MAGE_SHIELD_OF_ALODI                   = 195354,
    SPELL_MAGE_BRAIN_FREEZE                      = 190447,
    SPELL_MAGE_BRAIN_FREEZE_AURA                 = 190446,
    SPELL_MAGE_BRAIN_FREEZE_IMPROVED             = 231584,
    SPELL_MAGE_JOUSTER                           = 214626,
    SPELL_MAGE_CHILLED_TO_THE_CORE               = 195448,
    SPELL_MAGE_GLARITY_OF_THOUGHT                = 195351,
    SPELL_MAGE_ICE_NOVA                          = 157997,
    SPELL_MAGE_FROZEN_TOUCH                      = 205030,
    SPELL_MAGE_FROZEN_ORB                        = 84714,
    SPELL_MAGE_FROZEN_ORB_DAMAGE                 = 84721,
    SPELL_MAGE_BLIZZARD_RANK_2                   = 236662,
    SPELL_MAGE_UNSTABLE_MAGIC                    = 157976,
    SPELL_MAGE_UNSTABLE_MAGIC_DAMAGE_FIRE        = 157977,
    SPELL_MAGE_UNSTABLE_MAGIC_DAMAGE_FROST       = 157978,
    SPELL_MAGE_UNSTABLE_MAGIC_DAMAGE_ARCANE      = 157979,
    SPELL_MAGE_FINGERS_OF_FROST                  = 112965,
    SPELL_MAGE_FINGERS_OF_FROST_AURA             = 44544,
    SPELL_MAGE_FINGERS_OF_FROST_VISUAL_UI        = 126084,
    SPELL_MAGE_FROST_BOMB_AURA                   = 112948,
    SPELL_MAGE_FROST_BOMB_TRIGGERED              = 113092,
    SPELL_MAGE_FROSTBOLT                         = 116,
    SPELL_MAGE_FROSTBOLT_TRIGGER                 = 228597,
    SPELL_MAGE_RAY_OF_FROST                      = 205021,
    SPELL_MAGE_RAY_OF_FROST_DAMAGE_INCREASE      = 208141,
    SPELL_BLAZING_BARRIER_TRIGGER                = 235314,
    SPELL_MAGE_SCORCH                            = 2948,
    SPELL_MAGE_FIREBALL                          = 133,
    SPELL_MAGE_FIRE_BLAST                        = 108853,
    SPELL_MAGE_FLAMESTRIKE                       = 2120,
    SPELL_MAGE_PYROBLAST                         = 11366,
    SPELL_MAGE_PHOENIX_FLAMES                    = 257541,
    SPELL_MAGE_DRAGON_BREATH                     = 31661,
    SPELL_MAGE_PYROMANIAC                        = 205020,
    SPELL_MAGE_ALEXSTRASZAS_FURY                 = 235870,
    SPELL_MAGE_LIVING_BOMB_DAMAGE                = 44461,
    SPELL_MAGE_LIVING_BOMB_DOT                   = 217694,
    SPELL_MAGE_METEOR_DAMAGE                     = 153564,
    SPELL_MAGE_METEOR_TIMER                      = 177345,
    SPELL_MAGE_METEOR_VISUAL                     = 174556,
    SPELL_MAGE_METEOR_BURN                       = 155158,
    SPELL_MAGE_COMET_STORM                       = 153595,
    SPELL_MAGE_COMET_STORM_DAMAGE                = 153596,
    SPELL_MAGE_COMET_STORM_VISUAL                = 242210,
    SPELL_MAGE_POLYMORPH_CRITTERMORPH            = 120091,
    SPELL_MAGE_HEATING_UP                        = 48107,
    SPELL_MAGE_HOT_STREAK                        = 48108,
    SPELL_MAGE_ENHANCED_PYROTECHNICS_AURA        = 157644,
    SPELL_MAGE_TOUCH_OF_THE_MAGI_DAMAGE          = 210833,
    SPELL_MAGE_INCANTERS_FLOW_BUFF               = 116267,
    SPELL_MAGE_RUNE_OF_POWER_BUFF                = 116014,
    SPELL_MAGE_OVERPOWERED                       = 155147,
    SPELL_MAGE_ARCANE_POWER                      = 12042,
    SPELL_MAGE_CHRONO_SHIFT                      = 235711,
    SPELL_MAGE_CHRONO_SHIFT_SLOW                 = 236299,
    SPELL_MAGE_ARCANE_BLAST                      = 30451,
    SPELL_MAGE_ARCANE_BARRAGE                    = 44425,
    SPELL_MAGE_ARCANE_BARRAGE_TRIGGERED          = 241241,
    SPELL_MAGE_PRESENCE_OF_MIND                  = 205025,
    SPELL_MAGE_ARCANE_MISSILES_VISUAL_TWO        = 79808,
    SPELL_MAGE_ARCANE_MISSILES_VISUAL_ONE        = 170571,
    SPELL_MAGE_ARCANE_MISSILES_VISUAL_THREE      = 170572,
    SPELL_MAGE_ARCANE_MISSILES_TRIGGER           = 7268,
    SPELL_MAGE_ARCANE_MISSILES                   = 5143,
    SPELL_MAGE_ARCANE_MISSILES_POWER             = 208030,
    SPELL_MAGE_ARCANE_MISSILES_CHARGES           = 79683,
    SPELL_MAGE_ARCANE_ORB_DAMAGE                 = 153640,
    SPELL_MAGE_ARCANE_AMPLIFICATION              = 236628,
    SPELL_MAGE_GREATER_PYROBLAST                 = 203286,
    SPELL_MAGE_TUNNEL_OF_ICE_BUFF                = 277904,

    //7.3.2.25549 END
    SPELL_MAGE_RING_OF_FROST_FREEZE              = 82691,
    SPELL_MAGE_RING_OF_FROST_IMMUNE              = 91264,
    SPELL_MAGE_RING_OF_FROST                     = 113724,
    SPELL_MAGE_FIRE_MAGE_PASSIVE                 = 137019,
    SPELL_MAGE_FIRE_ON                           = 205029,
    SPELL_MAGE_FIRESTARTER                       = 205026,
    SPELL_MAGE_CAUTERIZE                         = 87023,
    SPELL_MAGE_MIRROR_IMAGE_LEFT                 = 58834,
    SPELL_MAGE_MIRROR_IMAGE_RIGHT                = 58833,
    SPELL_MAGE_MIRROR_IMAGE_FRONT                = 58831,
    SPELL_MAGE_COMBUSTION                        = 190319,
    SPELL_MAGE_WATER_JET                         = 135029,
    SPELL_MAGE_ICE_FLOES                         = 108839,
    SPELL_MAGE_CONJURE_REFRESHMENT_GROUP         = 167145,
    SPELL_MAGE_CONJURE_REFRESHMENT_SOLO          = 116136,
    SPELL_MAGE_HYPOTHERMIA                       = 41425,
    SPELL_INFERNO                                = 253220,
    SPELL_MAGE_BLAZING_BARRIER                   = 235313,
    SPELL_MAGE_BLAZING_SOUL                      = 235365,
    SPELL_MAGE_FLAME_PATCH                       = 205037,
    SPELL_MAGE_FLAME_PATCH_TRIGGER               = 205470,
    SPELL_MAGE_FLAME_PATCH_AOE_DMG               = 205472,
    SPELL_MAGE_CINDERSTORM                       = 198929,
    SPELL_MAGE_CINDERSTORM_DMG                   = 198928,
    SPELL_MAGE_IGNITE_DOT                        = 12654,
    SPELL_MAGE_REVERBERATE                       = 281482,
    SPELL_MAGE_RESONANCE                         = 205028,
    SPELL_MAGE_CLEARCASTING_BUFF                 = 277726, // Channel quicker
    SPELL_MAGE_CLEARCASTING_EFFECT               = 263725, // Removing the costs
    SPELL_MAGE_CLEARCASTING_PVP_STACK_EFFECT     = 276743, // Costs and is stackable
    SPELL_MAGE_ARCANE_EMPOWERMENT                = 276741,
    SPELL_MAGE_MANA_SHIELD_TALENT                = 235463,
    SPELL_MAGE_MANA_SHIELD_BURN                  = 235470,
    SPELL_MAGE_RULE_OF_THREES                    = 264354,
    SPELL_MAGE_RULE_OF_THREES_BUFF               = 264774,
    SPELL_MAGE_PHOENIX_FLAMES_AOE                 = 257542,
    SPELL_MAGE_ARCANE_FAMILIAR                   = 205022,
    SPELL_MAGE_ARCANE_FAMILIAR_MANA              = 210126,
    SPELL_MAGE_ARCANE_ASSAULT                    = 225119,
    SPELL_MAGE_TOUCH_OF_THE_MAGI                 = 210725,
    SPELL_MAGE_TOUCH_OF_THE_MAGI_DEBUFF          = 210824,
    SPELL_MAGE_FREEZING_RAIN                     = 270233,
    SPELL_MAGE_FREEZING_RAIN_BUFF                = 270232,
    SPELL_MAGE_DISPLACEMENT_BEACON               = 212799,
    SPELL_MAGE_SHIMMER                           = 212653,
    SPELL_MAGE_BLINK                             = 1953,
    SPELL_MAGE_FIREBLAST_CRIT                    = 231568,
    SPELL_MAGE_TIME_ANOMALY                         = 210808,
    SPELL_MAGE_TIME_ANOMALY_TALENT                 = 210805,
    SPELL_MAGE_EVOCATION                         = 12051,
    SPELL_MAGE_SLIPSTREAM                         = 236457,
    SPELL_MAGE_NETHER_STORM                         = 114923,
    SPELL_MAGE_NETHER_TEMPEST_AREA_EFFECT         = 114956,
    SPELL_MAGE_NETHER_TEMPEST_DAMAGE             = 114954,
    SPELL_MAGE_CHAIN_REACTION                     = 278309,
    SPELL_MAGE_CHAIN_REACTION_BUFF                 = 278310,
    SPELL_MAGE_SEARING_TOUCH                     = 269644,
    SPELL_MAGE_DISPLACEMENT_AURA                 = 62388,
    SPELL_MAGE_GREATER_INVISIBILITY_BUFF         = 113862,
    SPELL_MAGE_HOT_STREAK_PASSIVE                = 195283,
    SPELL_MAGE_TEMPORAL_RIPPLES                  = 198116,
    SPELL_MAGE_CHILLED_TO_THE_BONE                 = 198126,
    SPELL_MAGE_CHILLED_TO_THE_BONE_DAMAGE         = 198127,
    SPELL_MAGE_FROSTBITE                         = 198121,
    SPELL_MAGE_FREEZE                             = 33395,
    SPELL_MAGE_DEEP_SHATTER                         = 198123,
    SPELL_MAGE_FLAMECANNON_BUFF                     = 203285,
    SPELL_MAGE_RAY_OF_FROST_FINGERS_OF_FROST     = 269748,
    SPELL_MAGE_WHITEOUT_POWER                    = 278541,
    SPELL_MAGE_BLAST_WAVE_KNOCKBACK              = 268475,
    SPELL_MAGE_IGNITE                            = 12846,
    SPELL_MAGE_IGNITE_AURA                       = 12654,
    SPELL_MAGE_CONTROLLED_BURN                   = 280450,
    SPELL_MAGE_TINDER                            = 203275,
    SPELL_MAGE_TINDER_INDICATOR                  = 203277,
    SPELL_MAGE_TINDER_BLOCK                      = 203278,
    SPELL_MAGE_CAUTERIZE_BLINK_POWER             = 280015,
    SPELL_MAGE_CAUTERIZE_BLIBK_HEAL              = 280177,
    SPELL_MAGE_FROZEN_ORB_PVP                    = 198149,
    SPELL_MAGE_PRISMATIC_CLOAK                   = 198064,
    SPELL_MAGE_PISTMATIC_CLOAK_TRIGGER           = 198065,
    SPELL_MAGE_DISPLACEMENT                      = 195676,
    SPELL_MAGE_DISPLACEMENT_ARCANE               = 212801,
    SPELL_MAGE_CONCENTRATED_COLDNESS             = 198148,
    SPELL_MAGE_DAMPENED_MAGIC                    = 236788,
    SPELL_MAGE_FIREMIND_POWER                    = 278539,
    SPELL_MAGE_FIREMIND_BUFF                     = 279715,
    SPELL_MAGE_BLIZZARD_DAMAGE                   = 190357,
    SPELL_MAGE_PACKED_ICE                        = 272968,
    SPELL_MAGE_PACKED_ICE_AURA                   = 272970,
    SPELL_MAGE_ARCANE_PRESSURE                   = 274594,
    SPELL_MAGE_FLAMES_OF_ALACRITY_AURA           = 272934,
    SPELL_MAGE_MASTERY_ICICLES                   = 76613,
    SPELL_MAGE_ICICLE_DAMAGE                     = 148022,
    SPELL_MAGE_ICICLE_AURA                       = 205473,
    SPELL_MAGE_ICE_NINE                          = 214664,
    SPELL_MAGE_BLACK_ICE                         = 195615,
    SPELL_MAGE_GLACIAL_SPIKE_PROC                = 199844,
    SPELL_MAGE_GLACIAL_SPIKE_DAMAGE              = 228600,
    SPELL_MAGE_GLACIAL_SPIKE_AMOUNT              = 214325,
    SPELL_MAGE_FLURRY_DPS                        = 228354,
    SPELL_MAGE_PYROCLASM                         = 269650,
    SPELL_MAGE_PYROCLASM_PROC                    = 269651,
};

enum TemporalDisplacementSpells
{
    SPELL_MAGE_TEMPORAL_DISPLACEMENT             = 80354,
    SPELL_HUNTER_INSANITY                        = 95809,
    SPELL_PRIEST_SHADOW_WORD_DEATH               = 32409,
    SPELL_SHAMAN_EXHAUSTION                      = 57723,
    SPELL_SHAMAN_SATED                           = 57724,
    SPELL_PET_NETHERWINDS_FATIGUED               = 160455
};

enum eSpells
{
    AURA_ARCANIC_CHARGE = 36032,
};

enum Npcs
{
    NPC_WATER_ELEMENTAL = 78116,
};

class playerscript_mage_arcane : public PlayerScript
{
public:
    playerscript_mage_arcane() : PlayerScript("playerscript_mage_arcane") {}

    void OnModifyPower(Player* player, Powers power, int32 oldValue, int32& newValue, bool /*regen*/, bool after)
    {
        if (player->GetSpecializationId() != TALENT_SPEC_MAGE_ARCANE)
            return;

        if (power != POWER_ARCANE_CHARGES)
            return;

        if (!after)
            return;

        // Going up in charges is handled by aura 190427
        // Decreasing power seems weird clientside does not always match serverside power amount (client stays at 1, server is at 0)
        // Not sure if we need this.
        //if (oldValue >= newValue)
        //{
        //    player->RemoveAurasDueToSpell(AURA_ARCANIC_CHARGE);
        //    for (int32 i = 0; i < newValue; ++i)
        //        player->CastSpell(player, AURA_ARCANIC_CHARGE, true);
        //}
        if (player->HasAura(SPELL_MAGE_RULE_OF_THREES))
            if (newValue == 3 && oldValue == 2)
                player->CastSpell(player, SPELL_MAGE_RULE_OF_THREES_BUFF, true);
    }

    void OnUpdate(Player* player, uint32 diff)
    {
        if (timer <= diff)
        {
            timer = 500;

            if (!player || player->GetClass() != CLASS_MAGE)
                return;

            if (player->GetSpecializationId() != TALENT_SPEC_MAGE_ARCANE && player->HasAura(SPELL_MAGE_ARCANE_FAMILIAR_MANA))
                player->RemoveAura(SPELL_MAGE_ARCANE_FAMILIAR_MANA);
        }
        else
            timer -= diff;
    }

    void OnChanneledSpellSuccessfulCast(Player* player, Spell* spell) override
    {
        if (!player)
            return;

        if (player->GetSpecializationId() != TALENT_SPEC_MAGE_ARCANE)
            return;

        if (spell->GetSpellInfo()->Id == SPELL_MAGE_ARCANE_MISSILES)
            if (!player->HasAura(SPELL_MAGE_CLEARCASTING_PVP_STACK_EFFECT))
                player->RemoveAura(SPELL_MAGE_CLEARCASTING_BUFF);
	}

    void OnInterruptedSpellCast(Player* player, Spell* spell) override
    {
        if (!player)
            return;

        if (player->GetSpecializationId() != TALENT_SPEC_MAGE_ARCANE)
            return;

        if (spell->GetSpellInfo()->Id == SPELL_MAGE_ARCANE_MISSILES)
            if (!player->HasAura(SPELL_MAGE_CLEARCASTING_PVP_STACK_EFFECT))
                player->RemoveAura(SPELL_MAGE_CLEARCASTING_BUFF);
	}

private:
    uint32 timer = 500;
};

// 110909 - Alter Time Aura
// 342246 - Alter Time Aura
class spell_mage_alter_time_aura : public AuraScript
{
    PrepareAuraScript(spell_mage_alter_time_aura);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo
        ({
            SPELL_MAGE_ALTER_TIME_VISUAL,
            SPELL_MAGE_MASTER_OF_TIME,
            SPELL_MAGE_BLINK,
        });
    }

    void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Unit* unit = GetTarget();
        _health = unit->GetHealth();
        _pos = unit->GetPosition();
    }

    void AfterRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Unit* unit = GetTarget();
        if (unit->GetDistance(_pos) <= 100.0f && GetTargetApplication()->GetRemoveMode() == AURA_REMOVE_BY_EXPIRE)
        {
            unit->SetHealth(_health);
            unit->NearTeleportTo(_pos);

            if (unit->HasAura(SPELL_MAGE_MASTER_OF_TIME))
            {
                SpellInfo const* blink = sSpellMgr->AssertSpellInfo(SPELL_MAGE_BLINK, DIFFICULTY_NONE);
                unit->GetSpellHistory()->ResetCharges(blink->ChargeCategoryId);
            }
            unit->CastSpell(unit, SPELL_MAGE_ALTER_TIME_VISUAL);
            // Fixes alter time's cd clientside
            unit->GetSpellHistory()->StartCooldown(sSpellMgr->GetSpellInfo(108978), 0, nullptr, false, 60s);
        }
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_mage_alter_time_aura::OnApply, EFFECT_0, SPELL_AURA_OVERRIDE_ACTIONBAR_SPELLS, AURA_EFFECT_HANDLE_REAL);
        AfterEffectRemove += AuraEffectRemoveFn(spell_mage_alter_time_aura::AfterRemove, EFFECT_0, SPELL_AURA_OVERRIDE_ACTIONBAR_SPELLS, AURA_EFFECT_HANDLE_REAL);
    }

private:
    uint64 _health = 0;
    Position _pos;
};

// 127140 - Alter Time Active
// 342247 - Alter Time Active
class spell_mage_alter_time_active : public SpellScript
{
    PrepareSpellScript(spell_mage_alter_time_active);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo
        ({
            SPELL_MAGE_ALTER_TIME_AURA,
            SPELL_MAGE_ARCANE_ALTER_TIME_AURA,
        });
    }

    void RemoveAlterTimeAura(SpellEffIndex /*effIndex*/)
    {
        Unit* unit = GetCaster();
        unit->RemoveAura(SPELL_MAGE_ALTER_TIME_AURA, ObjectGuid::Empty, 0, AURA_REMOVE_BY_EXPIRE);
        unit->RemoveAura(SPELL_MAGE_ARCANE_ALTER_TIME_AURA, ObjectGuid::Empty, 0, AURA_REMOVE_BY_EXPIRE);
    }

    void Register() override
    {
        OnEffectHit += SpellEffectFn(spell_mage_alter_time_active::RemoveAlterTimeAura, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};


// Chrono Shift - 235711
class spell_mage_chrono_shift : public AuraScript
{
    PrepareAuraScript(spell_mage_chrono_shift);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        bool _spellCanProc = (eventInfo.GetSpellInfo()->Id == SPELL_MAGE_ARCANE_BARRAGE || eventInfo.GetSpellInfo()->Id == SPELL_MAGE_ARCANE_BARRAGE_TRIGGERED);

        if (_spellCanProc)
            return true;
        return false;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_mage_chrono_shift::CheckProc);
    }
};

// Arcane Explosion - 1449
class spell_mage_arcane_explosion : public SpellScript
{
    PrepareSpellScript(spell_mage_arcane_explosion);

    int32 _hit;

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo(
            {
                SPELL_MAGE_REVERBERATE
            });
    }

    bool Load() override
    {
        _hit = 0;
        return true;
    }

    void CheckTargets(std::list<WorldObject*>& targets)
    {
        _hit = targets.size();
    }

    void Prevent(SpellEffIndex effIndex)
    {
        if (_hit == 0)
            PreventHitEffect(effIndex);
    }

    void PreventTalent(SpellEffIndex effIndex)
    {
        if (Aura* reverberate = GetCaster()->GetAura(SPELL_MAGE_REVERBERATE))
            if (_hit >= reverberate->GetEffect(EFFECT_1)->GetAmount() && roll_chance_i(reverberate->GetEffect(EFFECT_0)->GetAmount()))
                return;

        PreventHitEffect(effIndex);
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_mage_arcane_explosion::CheckTargets, EFFECT_1, TARGET_UNIT_SRC_AREA_ENEMY);
        OnEffectHit += SpellEffectFn(spell_mage_arcane_explosion::Prevent, EFFECT_0, SPELL_EFFECT_ENERGIZE);
        OnEffectHitTarget += SpellEffectFn(spell_mage_arcane_explosion::Prevent, EFFECT_0, SPELL_EFFECT_ENERGIZE);

        OnEffectHit += SpellEffectFn(spell_mage_arcane_explosion::PreventTalent, EFFECT_2, SPELL_EFFECT_ENERGIZE);
        OnEffectHitTarget += SpellEffectFn(spell_mage_arcane_explosion::PreventTalent, EFFECT_2, SPELL_EFFECT_ENERGIZE);
    }
};

// 5143 - Arcane Missiles
class spell_mage_arcane_missiles : public SpellScript
{
    PrepareSpellScript(spell_mage_arcane_missiles);

    void HandleCast()
    {
		if (Unit* caster = GetCaster())
		{
			caster->RemoveAura(SPELL_MAGE_CLEARCASTING_EFFECT);
            if (!caster->HasAura(SPELL_MAGE_SLIPSTREAM))
                caster->RemoveAura(SPELL_MAGE_CLEARCASTING_BUFF);
			if (Aura* pvpClearcast = caster->GetAura(SPELL_MAGE_CLEARCASTING_PVP_STACK_EFFECT))
				pvpClearcast->ModStackAmount(-1);

            caster->RemoveAura(SPELL_MAGE_RULE_OF_THREES_BUFF);
		}
    }

    void Register() override
    {
        OnCast += SpellCastFn(spell_mage_arcane_missiles::HandleCast);
    }
};

// Arcane Missiles Damage - 7268
class spell_mage_arcane_missiles_damage :public SpellScript
{
    PrepareSpellScript(spell_mage_arcane_missiles_damage);

    void CheckTarget(WorldObject*& target)
    {
        if (target == GetCaster())
            target = nullptr;
    }

    void Register() override
    {
        OnObjectTargetSelect += SpellObjectTargetSelectFn(spell_mage_arcane_missiles_damage::CheckTarget, EFFECT_0, TARGET_UNIT_CHANNEL_TARGET);
    }
};

// Clearcasting - 79684
class spell_mage_clearcasting : public AuraScript
{
    PrepareAuraScript(spell_mage_clearcasting);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (true)
        {
            auto eff0 = GetSpellInfo()->GetEffect(EFFECT_0);
            int32 reqManaToSpent = 0;
            int32 manaUsed = 0;

            // For each ${$c*100/$s1} mana you spend, you have a 1% chance
            // Means: I cast a spell which costs 1000 Mana, for every 500 mana used I have 1% chance =  2% chance to proc
            for (SpellPowerCost powerCost : GetSpellInfo()->CalcPowerCost(GetCaster(), GetSpellInfo()->GetSchoolMask()))
                if (powerCost.Power == POWER_MANA)
                    reqManaToSpent = powerCost.Amount * 100 / eff0.CalcValue();

            // Something changed in DBC, Clearcasting should cost 1% of base mana 8.0.1
            if (reqManaToSpent == 0)
                return false;

            for (SpellPowerCost powerCost : eventInfo.GetSpellInfo()->CalcPowerCost(GetCaster(), eventInfo.GetSpellInfo()->GetSchoolMask()))
                if (powerCost.Power == POWER_MANA)
                    manaUsed = powerCost.Amount;

            int32 chance = std::floor(manaUsed / reqManaToSpent) * 1;
            if (roll_chance_i(chance))
                if (Unit* caster = GetCaster())
                {
                    caster->Variables.Set<bool>("CLEARCASTING", true);
                    return true;
                }
        }

        return false;
    }

    void HandleProc(AuraEffect* /*aurEff*/, ProcEventInfo& eventInfo)
    {
		if (Unit* caster = GetCaster())
		{
			if (caster->HasAura(SPELL_MAGE_ARCANE_EMPOWERMENT))
				caster->CastSpell(caster, SPELL_MAGE_CLEARCASTING_PVP_STACK_EFFECT, true);
            else
            {
                caster->CastSpell(caster, SPELL_MAGE_CLEARCASTING_EFFECT, true);
                caster->CastSpell(caster, SPELL_MAGE_CLEARCASTING_BUFF, true);
            }
		}
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_mage_clearcasting::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_mage_clearcasting::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

// 30451 - Arcane Blast
class spell_mage_arcane_blast : public SpellScript
{
    PrepareSpellScript(spell_mage_arcane_blast);

    void HandleAfterCast()
    {
        if (Unit* caster = GetCaster())
            if (!caster->HasAura(SPELL_MAGE_ARCANE_EMPOWERMENT))
            {
                if (!caster->Variables.Exist("CLEARCASTING"))
                {
                    caster->RemoveAurasDueToSpell(SPELL_MAGE_CLEARCASTING_BUFF);
                    caster->RemoveAurasDueToSpell(SPELL_MAGE_CLEARCASTING_EFFECT);
                }
                else
                    caster->Variables.Remove("CLEARCASTING");
            }
    }

    void HandleOnCast()
    {
        if (Unit* caster = GetCaster())
            caster->RemoveAura(SPELL_MAGE_RULE_OF_THREES_BUFF);
    }

    void Register() override
    {
        AfterCast += SpellCastFn(spell_mage_arcane_blast::HandleAfterCast);
        OnCast += SpellCastFn(spell_mage_arcane_blast::HandleOnCast);
    }
};

// Presence of mind - 205025
class spell_mage_presence_of_mind : public AuraScript
{
    PrepareAuraScript(spell_mage_presence_of_mind);

    void HandleApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* caster = GetCaster())
            caster->RemoveAura(110960);
    }

    bool HandleProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetSpellInfo()->Id == SPELL_MAGE_ARCANE_BLAST)
            return true;
        return false;
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_mage_presence_of_mind::HandleApply, EFFECT_0, SPELL_AURA_ADD_PCT_MODIFIER, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
        DoCheckProc += AuraCheckProcFn(spell_mage_presence_of_mind::HandleProc);
    }
};

class CheckArcaneBarrageImpactPredicate
{
public:
    CheckArcaneBarrageImpactPredicate(Unit* caster, Unit* mainTarget) : _caster(caster), _mainTarget(mainTarget) {}

    bool operator()(Unit* target)
    {
        if (!_caster || !_mainTarget)
            return true;

        if (!_caster->IsValidAttackTarget(target))
            return true;

        if (!target->IsWithinLOSInMap(_caster))
            return true;

        if (!_caster->isInFront(target))
            return true;

        if (target->GetGUID() == _caster->GetGUID())
            return true;

        if (target->GetGUID() == _mainTarget->GetGUID())
            return true;

        return false;
    }

private:
    Unit * _caster;
    Unit* _mainTarget;
};

// 44425 - Arcane Barrage
class spell_mage_arcane_barrage : public SpellScript
{
    PrepareSpellScript(spell_mage_arcane_barrage);

    void CacheMainTarget(WorldObject*& target)
    {
        mainTarget = target;
    }

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        if (Unit* caster = GetCaster())
        {
            if (!mainTarget)
                return;

            CreatureList list = mainTarget->FindAllCreaturesInRange(8.0f);
            list.sort(Trinity::ObjectDistanceOrderPred(mainTarget));
            for (Unit* unit : list)
                targets.push_back(unit);

            targets.remove_if([caster](WorldObject* unit)
            {
                if (!unit->ToUnit())
                    return true;

                if (!caster->IsValidAttackTarget(unit->ToUnit()))
                    return true;

                return false;
            });

            uint8 stacks = 0;
            if (Aura* aura = caster->GetAura(AURA_ARCANIC_CHARGE))
                stacks = aura->GetStackAmount();
            else
                stacks = 0;

            if (targets.size() > stacks)
                targets.resize(stacks);
            counter = targets.size() + 1;
        }
    }

    void HandleTargetHit(SpellEffIndex effIndex)
    {
        Unit* caster = GetCaster();
        Unit* expTarget = GetExplTargetUnit();
        Unit* hitTarget = GetHitUnit();

        if (!expTarget || !hitTarget)
            return;

        int32 damage = GetHitDamage();

        // Resonance.
        if (caster->HasAura(SPELL_MAGE_RESONANCE))
            damage += CalculatePct(damage, sSpellMgr->GetSpellInfo(SPELL_MAGE_RESONANCE)->GetEffect(EFFECT_0).BasePoints * counter);

        // Secondary targets receive less damage.
        if (expTarget->GetGUID() != hitTarget->GetGUID())
            SetHitDamage(CalculatePct(damage, sSpellMgr->GetSpellInfo(SPELL_MAGE_ARCANE_BARRAGE)->GetEffect(EFFECT_1).BasePoints));

        // Chrono Shift.
        if (caster->HasAura(SPELL_MAGE_CHRONO_SHIFT))
            caster->CastSpell(hitTarget, SPELL_MAGE_CHRONO_SHIFT_SLOW, true);

        // Arcane Pressure.
        if (Aura* aura = caster->GetAura(SPELL_MAGE_ARCANE_PRESSURE))
            if (hitTarget->GetHealthPct() <= sSpellMgr->GetSpellInfo(SPELL_MAGE_ARCANE_PRESSURE)->GetEffect(EFFECT_1).BasePoints)
            {
                uint8 charges = caster->GetPower(POWER_ARCANE_CHARGES);
                SetHitDamage(damage + aura->GetEffect(0)->GetAmount() * charges);
            }
    }

    void RemoveCharges()
    {
        if (Unit* caster = GetCaster())
            caster->SetPower(POWER_ARCANE_CHARGES, 0);
    }

    void Register() override
    {
        OnObjectTargetSelect += SpellObjectTargetSelectFn(spell_mage_arcane_barrage::CacheMainTarget, EFFECT_0, TARGET_UNIT_TARGET_ENEMY);
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_mage_arcane_barrage::FilterTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ENEMY);
        AfterCast += SpellCastFn(spell_mage_arcane_barrage::RemoveCharges);
        OnEffectHitTarget += SpellEffectFn(spell_mage_arcane_barrage::HandleTargetHit, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }

    private:
        WorldObject* mainTarget;
        uint8 counter = 0;
};

// Prismatic Barrier (Arcane Barrier) - 235450
class spell_mage_arcane_barrier : public AuraScript
{
    PrepareAuraScript(spell_mage_arcane_barrier);

    void CalculateAmount(AuraEffect const* /*aurEff*/, int32& amount, bool& canBeRecalculated)
    {
        canBeRecalculated = false;
        if (Unit* caster = GetCaster())
            amount = int32(CalculatePct(caster->GetMaxHealth(), GetSpellInfo()->GetEffect(EFFECT_4).CalcValue()));
    }

    void CalcAbsorb(AuraEffect* aurEff, DamageInfo& dmgInfo, uint32& absorbAmount)
    {
        if (GetCaster())
        {
            if (AuraEffect const* eff0 = GetCaster()->GetAuraEffect(SPELL_MAGE_MANA_SHIELD_TALENT, EFFECT_0))
            {
                int32 manaBurned = CalculatePct(dmgInfo.GetDamage(), eff0->GetAmount());
                GetCaster()->CastCustomSpell(SPELL_MAGE_MANA_SHIELD_BURN, SPELLVALUE_BASE_POINT0, manaBurned, GetCaster(), TRIGGERED_FULL_MASK);
            }
        }
    }

    void Register() override
    {
        OnEffectAbsorb += AuraEffectAbsorbFn(spell_mage_arcane_barrier::CalcAbsorb, EFFECT_0);
        DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_mage_arcane_barrier::CalculateAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
    }
};

// Fire Blast - 108853
class spell_mage_fire_blast : public SpellScript
{
    PrepareSpellScript(spell_mage_fire_blast);

    void HandleCast()
    {
        if (Unit* caster = GetCaster())
        {
            caster->RemoveAura(66);
            caster->RemoveAura(32612);
        }
    }

    void HandleHit(SpellEffIndex /*effIndex*/)
    {
        // this is already handled by Pyroblast Clearcasting Driver - 44448
        bool procCheck = false;

        if (Unit* caster = GetCaster())
            if (caster->HasSpell(SPELL_MAGE_HOT_STREAK_PASSIVE))
            {

                if (!caster->HasAura(SPELL_MAGE_HEATING_UP) && !caster->HasAura(SPELL_MAGE_HOT_STREAK))
                {
                    caster->CastSpell(caster, SPELL_MAGE_HEATING_UP, true);
                    return;
                }

                if (caster->HasAura(SPELL_MAGE_HEATING_UP) && !caster->HasAura(SPELL_MAGE_HOT_STREAK))
                {
                    caster->RemoveAurasDueToSpell(SPELL_MAGE_HEATING_UP);
                    caster->CastSpell(caster, SPELL_MAGE_HOT_STREAK, true);
                    return;
                }
            }
    }

    void Register() override
    {
        OnCast += SpellCastFn(spell_mage_fire_blast::HandleCast);
        OnEffectHitTarget += SpellEffectFn(spell_mage_fire_blast::HandleHit, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

// Enhanced Pyrotechnics - 157642
class spell_mage_enhanced_pyrotechnics : public AuraScript
{
    PrepareAuraScript(spell_mage_enhanced_pyrotechnics);

    bool HandleProc(ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();

        if (eventInfo.GetSpellInfo()->Id == SPELL_MAGE_FIREBALL)
        {
            if ((eventInfo.GetHitMask() & PROC_HIT_CRITICAL))
            {
                if (caster->HasAura(SPELL_MAGE_ENHANCED_PYROTECHNICS_AURA))
                    caster->RemoveAurasDueToSpell(SPELL_MAGE_ENHANCED_PYROTECHNICS_AURA);
                return false;
            }
            return true;
        }
        return false;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_mage_enhanced_pyrotechnics::HandleProc);
    }
};

// Polymorph - 118
class spell_mage_polymorph : public AuraScript
{
    PrepareAuraScript(spell_mage_polymorph);

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (WorldObject* owner = GetOwner())
            if (owner->ToUnit())
                owner->ToUnit()->RemoveAura(GetAura());
    }

    void Register() override
    {
        OnProc += AuraProcFn(spell_mage_polymorph::HandleProc);
    }
};

// Comet Storm - 153595
class spell_mage_comet_storm : public SpellScript
{
    PrepareSpellScript(spell_mage_comet_storm);

    void HandleDummy()
    {
        Unit* caster = GetCaster();
        WorldLocation const* dest = GetExplTargetDest();

        if (!caster || !dest)
            return;

        Position targetPos = dest->GetPosition();

        for (uint8 i = 0; i < 7; ++i)
        {
            caster->GetScheduler().Schedule(Milliseconds(300 * i), [targetPos](TaskContext context)
            {
                GetContextUnit()->CastSpell(targetPos, SPELL_MAGE_COMET_STORM_VISUAL, true);

                // Damage come 1sec after visual
                context.Schedule(Milliseconds(1000), [targetPos](TaskContext context)
                {
                    GetContextUnit()->CastSpell(targetPos, SPELL_MAGE_COMET_STORM_DAMAGE, true);
                });
            });
        }
    }

    void Register() override
    {
        AfterCast += SpellCastFn(spell_mage_comet_storm::HandleDummy);
    }
};

// Meteor - 153561
class spell_mage_meteor : public SpellScript
{
    PrepareSpellScript(spell_mage_meteor);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_MAGE_METEOR_DAMAGE });
    }

    void HandleDummy()
    {
        Unit* caster = GetCaster();
        WorldLocation const* dest = GetExplTargetDest();
        if (!caster || !dest)
            return;

        caster->CastSpell(*dest, SPELL_MAGE_METEOR_TIMER, true);
    }

    void Register() override
    {
        AfterCast += SpellCastFn(spell_mage_meteor::HandleDummy);
    }
};

// Meteor Damage - 153564
class spell_mage_meteor_damage : public SpellScript
{
    PrepareSpellScript(spell_mage_meteor_damage);

    int32 _targets;
    std::list<WorldObject*> targetObjects;
    bool check = false;
    bool affected = false;

    void HandleBeforeHit(SpellMissInfo /*missInfo*/)
    {
        check = true;
        GetSpell()->SelectSpellTargets(false);
    }

    void HandleHit(SpellEffIndex /*effIndex*/)
    {
        if (!affected)
        {
            affected = true;
            if (Unit* caster = GetCaster())
            {
                for (auto targetWo : targetObjects)
                {
                    if (Unit* target = targetWo->ToUnit())
                    {
                        int32 hitDamage = GetHitDamage() / targetObjects.size();
                        SpellNonMeleeDamage damageLog = SpellNonMeleeDamage(caster, target, GetSpellInfo(), { GetSpellInfo()->GetSpellXSpellVisualId(), 0 }, GetSpellInfo()->GetSchoolMask());
                        damageLog.damage = hitDamage;
                        caster->CalculateSpellDamageTaken(&damageLog, damageLog.damage, GetSpellInfo());
                        caster->DealDamageMods(caster, target, damageLog.damage, &damageLog.absorb);
                        caster->SendSpellNonMeleeDamageLog(&damageLog);
                        caster->DealDamage(caster, target, hitDamage);
                    }
                }
            }
        }

        SetHitDamage(0);
    }

    void CountTargets(std::list<WorldObject*>& targets)
    {
        if (check)
        {
            if (Unit* caster = GetCaster())
            {
                targets.remove_if([caster](WorldObject* object)
                {
                    if (!object->ToUnit())
                        return true;

                    if (!caster->IsValidAttackTarget(object->ToUnit()))
                        return true;

                    return false;
                });

                targetObjects = targets;
            }
        }
    }

    void Register() override
    {
        BeforeHit += BeforeSpellHitFn(spell_mage_meteor_damage::HandleBeforeHit);
        OnEffectHitTarget += SpellEffectFn(spell_mage_meteor_damage::HandleHit, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_mage_meteor_damage::CountTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ENEMY);
    }
};

// Living Bomb - 44457
class spell_mage_living_bomb : public SpellScript
{
    PrepareSpellScript(spell_mage_living_bomb);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo
        ({
            SPELL_MAGE_LIVING_BOMB_DAMAGE,
            SPELL_MAGE_LIVING_BOMB_DOT
        });
    }

    void HandleOnHit(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!target || !caster)
            return;

        caster->CastCustomSpell(SPELL_MAGE_LIVING_BOMB_DOT, SPELLVALUE_BASE_POINT1, 1, target, TRIGGERED_FULL_MASK);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_mage_living_bomb::HandleOnHit, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

// Living Bomb Dot - 217694
class spell_mage_living_bomb_dot : public AuraScript
{
    PrepareAuraScript(spell_mage_living_bomb_dot);

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetTarget();
        if (!caster || !target)
            return;

        int32 check = GetAura()->GetEffect(EFFECT_1)->GetBaseAmount();
        caster->CastCustomSpell(SPELL_MAGE_LIVING_BOMB_DAMAGE, SPELLVALUE_BASE_POINT0, check, target, TRIGGERED_FULL_MASK);
    }

    void Register() override
    {
        AfterEffectRemove += AuraEffectRemoveFn(spell_mage_living_bomb_dot::HandleRemove, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE, AURA_EFFECT_HANDLE_REAL);
    }
};

// Living Bomb Damage - 44461
class spell_mage_living_bomb_spread : public SpellScript
{
    PrepareSpellScript(spell_mage_living_bomb_spread);

    void HandleHit(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        Unit* hitunit = GetHitUnit();
        Unit* explunit = GetExplTargetUnit();
        if (!caster || !hitunit || !explunit)
            return;

        int32 check = GetSpellValue()->EffectBasePoints[0];
        if (check && hitunit != explunit)
            caster->CastCustomSpell(SPELL_MAGE_LIVING_BOMB_DOT, SPELLVALUE_BASE_POINT1, 0, hitunit, TRIGGERED_FULL_MASK);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_mage_living_bomb_spread::HandleHit, EFFECT_1, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

// Frenetic Speed - 236058
class spell_mage_frenetic_speed : public AuraScript
{
    PrepareAuraScript(spell_mage_frenetic_speed);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == SPELL_MAGE_SCORCH;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_mage_frenetic_speed::CheckProc);
    }
};

// Conflagration - 205023
class spell_mage_conflagration : public AuraScript
{
    PrepareAuraScript(spell_mage_conflagration);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == SPELL_MAGE_FIREBALL;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_mage_conflagration::CheckProc);
    }
};

// Blazing Barrier - 235313
class spell_mage_blazing_barrier : public AuraScript
{
    PrepareAuraScript(spell_mage_blazing_barrier);

    bool Validate(SpellInfo const* /*spell*/) override
    {
        return ValidateSpellInfo({ SPELL_BLAZING_BARRIER_TRIGGER });
    }

    void CalculateAmount(AuraEffect const* /*aurEff*/, int32& amount, bool& canBeRecalculated)
    {
        canBeRecalculated = false;
        if (Unit* caster = GetCaster())
            amount = int32(CalculatePct(caster->GetMaxHealth(), GetSpellInfo()->GetEffect(EFFECT_1).CalcValue()));
    }

    void Register() override
    {
        DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_mage_blazing_barrier::CalculateAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
    }
};

// Pyroblast 11366
class spell_mage_pyroblast : public SpellScript
{
    PrepareSpellScript(spell_mage_pyroblast);

    void HandleOnHit(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        if (!caster)
            return;

        if (caster->HasAura(SPELL_MAGE_HOT_STREAK))
        {
            caster->RemoveAurasDueToSpell(SPELL_MAGE_HOT_STREAK);
            if (caster->HasAura(SPELL_MAGE_PYROCLASM) && roll_chance_i(15))
                caster->CastSpell(caster, SPELL_MAGE_PYROCLASM_PROC, true);

            if (AuraEffect* auraEff = caster->GetAuraEffect(SPELL_MAGE_FIREMIND_POWER, EFFECT_0))
                caster->CastCustomSpell(SPELL_MAGE_FIREMIND_BUFF, SPELLVALUE_BASE_POINT0, auraEff->GetAmount(), caster, true);

            if (caster->HasAura(SPELL_MAGE_PYROMANIAC))
                if (AuraEffect* pyromaniacEff0 = caster->GetAuraEffect(SPELL_MAGE_PYROMANIAC, EFFECT_0))
                    if (roll_chance_i(pyromaniacEff0->GetAmount()))
                    {
                        if (caster->HasAura(SPELL_MAGE_HEATING_UP))
                            caster->RemoveAurasDueToSpell(SPELL_MAGE_HEATING_UP);

                        caster->CastSpell(caster, SPELL_MAGE_HOT_STREAK, true);
                    }
        }
        else if (caster->HasAura(SPELL_MAGE_PYROCLASM_PROC))
        {
            caster->RemoveAurasDueToSpell(SPELL_MAGE_PYROCLASM_PROC);
            auto dmg = GetHitDamage();
            AddPct(dmg, 240);
            SetHitDamage(dmg);
        }
    }

    void Register() override
    {
        OnEffectHit += SpellEffectFn(spell_mage_pyroblast::HandleOnHit, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

// Flamestrike 2120
class spell_mage_flamestrike : public SpellScript
{
    PrepareSpellScript(spell_mage_flamestrike);

    void HandleOnHit(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        if (caster->HasAura(SPELL_MAGE_HOT_STREAK))
        {
            caster->RemoveAurasDueToSpell(SPELL_MAGE_HOT_STREAK);
            if (caster->HasAura(SPELL_MAGE_PYROCLASM) && roll_chance_i(15))
                caster->CastSpell(caster, SPELL_MAGE_PYROCLASM_PROC, true);

            if (AuraEffect* auraEff = caster->GetAuraEffect(SPELL_MAGE_FIREMIND_POWER, EFFECT_0))
                caster->CastCustomSpell(SPELL_MAGE_FIREMIND_BUFF, SPELLVALUE_BASE_POINT0, auraEff->GetAmount(), caster, true);

            if (caster->HasAura(SPELL_MAGE_PYROMANIAC))
                if (AuraEffect* pyromaniacEff0 = caster->GetAuraEffect(SPELL_MAGE_PYROMANIAC, EFFECT_0))
                    if (roll_chance_i(pyromaniacEff0->GetAmount()))
                    {
                        if (caster->HasAura(SPELL_MAGE_HEATING_UP))
                            caster->RemoveAurasDueToSpell(SPELL_MAGE_HEATING_UP);

                        caster->CastSpell(caster, SPELL_MAGE_HOT_STREAK, true);
                    }
        }

        // Mastery
        const SpellInfo* igniteAura = sSpellMgr->GetSpellInfo(SPELL_MAGE_IGNITE_AURA);
        if (GetSpellInfo()->Id != SPELL_MAGE_IGNITE_AURA && igniteAura != nullptr && caster->IsPlayer())
        {
            float masteryValue = caster->ToPlayer()->m_activePlayerData->Mastery * 0.75f;

            int32 basePoints = GetHitDamage();
            if (basePoints)
            {
                basePoints = int32(CalculatePct(basePoints, masteryValue));

                if (igniteAura->GetEffect(EFFECT_0).Amplitude > 0)
                    basePoints = basePoints / (igniteAura->GetMaxDuration() / igniteAura->GetEffect(EFFECT_0).Amplitude);

                //if (Aura* previousIgnite = target->GetAura(SPELL_MAGE_IGNITE_AURA, caster->GetGUID()))
                //{
                //    if (AuraEffect* igniteEffect = previousIgnite->GetEffect(EFFECT_0))
                //    {
                //        if (uint32 amplitude = igniteEffect->GetPeriod())
                //            basePoints += (igniteEffect->GetAmount() * (previousIgnite->GetDuration() / amplitude)) / (previousIgnite->GetMaxDuration() / amplitude);
                //    }
                //}

                caster->CastCustomSpell(target, SPELL_MAGE_IGNITE_AURA, &basePoints, NULL, NULL, true);
            }
        }
    }

    void HandleDummy()
    {
        Unit* caster = GetCaster();
        WorldLocation const* dest = GetExplTargetDest();
        if (!caster || !dest)
            return;

        if (caster->HasAura(SPELL_MAGE_FLAME_PATCH))
            if (WorldLocation const* dest = GetExplTargetDest())
                caster->CastSpell(dest->GetPosition(), SPELL_MAGE_FLAME_PATCH_TRIGGER, true);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_mage_flamestrike::HandleOnHit, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
        AfterCast += SpellCastFn(spell_mage_flamestrike::HandleDummy);
    }
};

// Kindling - 155148
class spell_mage_kindling : public AuraScript
{
    PrepareAuraScript(spell_mage_kindling);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetSpellInfo() && (eventInfo.GetSpellInfo()->Id == SPELL_MAGE_FIREBALL || eventInfo.GetSpellInfo()->Id == SPELL_MAGE_FIRE_BLAST ||
            eventInfo.GetSpellInfo()->Id == SPELL_MAGE_PYROBLAST || eventInfo.GetSpellInfo()->Id == SPELL_MAGE_PHOENIX_FLAMES) && (eventInfo.GetHitMask() & PROC_HIT_CRITICAL))
            return true;
        return false;
    }

    void HandleProc(AuraEffect* aurEff, ProcEventInfo& /*eventInfo*/)
    {
        Unit* caster = GetCaster();
        if (!caster)
            return;

        caster->GetSpellHistory()->ModifyCooldown(SPELL_MAGE_COMBUSTION, -1);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_mage_kindling::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_mage_kindling::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

// Pyroblast Clearcasting Driver - 44448
class spell_mage_pyroblast_clearcasting_driver : public AuraScript
{
    PrepareAuraScript(spell_mage_pyroblast_clearcasting_driver);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (Unit* caster = GetCaster())
        {
            if (!caster->HasSpell(SPELL_MAGE_HOT_STREAK_PASSIVE))
                return false;

            bool _spellCanProc = (eventInfo.GetSpellInfo()->Id == SPELL_MAGE_SCORCH || eventInfo.GetSpellInfo()->Id == SPELL_MAGE_FIREBALL || eventInfo.GetSpellInfo()->Id == SPELL_MAGE_FLAMESTRIKE ||
                eventInfo.GetSpellInfo()->Id == SPELL_MAGE_PYROBLAST || eventInfo.GetSpellInfo()->Id == SPELL_MAGE_PHOENIX_FLAMES || eventInfo.GetSpellInfo()->Id == SPELL_MAGE_GREATER_PYROBLAST ||
                (eventInfo.GetSpellInfo()->Id == SPELL_MAGE_DRAGON_BREATH && caster->HasAura(SPELL_MAGE_ALEXSTRASZAS_FURY)));

            if (_spellCanProc)
                return true;
        }
        return false;
    }

    void HandleProc(AuraEffect* /*aurEff*/, ProcEventInfo& eventInfo)
    {
        bool procCheck = false;

        Unit* caster = GetCaster();

        if ((eventInfo.GetHitMask() & PROC_HIT_NORMAL))
        {
            if (caster->HasAura(SPELL_MAGE_HEATING_UP))
                caster->RemoveAurasDueToSpell(SPELL_MAGE_HEATING_UP);
            return;
        }

        if (!caster->HasAura(SPELL_MAGE_HEATING_UP) && !caster->HasAura(SPELL_MAGE_HOT_STREAK))
        {
            caster->CastSpell(caster, SPELL_MAGE_HEATING_UP, true);
            return;
        }

        if (caster->HasAura(SPELL_MAGE_HEATING_UP) && !caster->HasAura(SPELL_MAGE_HOT_STREAK))
        {
            caster->RemoveAurasDueToSpell(SPELL_MAGE_HEATING_UP);
            caster->CastSpell(caster, SPELL_MAGE_HOT_STREAK, true);
            return;
        }
    }

    void Register() override
    {
        OnEffectProc += AuraEffectProcFn(spell_mage_pyroblast_clearcasting_driver::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
        DoCheckProc += AuraCheckProcFn(spell_mage_pyroblast_clearcasting_driver::CheckProc);
    }
};

// Fireball 133
// Pyroblast 11366
class spell_mage_firestarter : public SpellScript
{
    PrepareSpellScript(spell_mage_firestarter);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo
        ({
            SPELL_MAGE_FIREBALL,
            SPELL_MAGE_PYROBLAST,
            SPELL_MAGE_FIRESTARTER
        });
    }

    void HandleCritChance(Unit const* victim, float& chance)
    {
        if (Aura* aura = GetCaster()->GetAura(SPELL_MAGE_FIRESTARTER))
            if (victim->GetHealthPct() >= aura->GetEffect(EFFECT_0)->GetAmount())
                chance = 100.0f;
    }

    void HandleAfterCast()
    {
        if (Unit* caster = GetCaster())
        {
            if (caster->HasAura(SPELL_MAGE_TINDER))
            {
                if (GetSpellInfo()->Id == SPELL_MAGE_FIREBALL)
                {
                    caster->CastSpell(caster, SPELL_MAGE_TINDER_BLOCK);
                    caster->RemoveAurasDueToSpell(SPELL_MAGE_TINDER_INDICATOR);
                    caster->Variables.Set<bool>("TINDER_RESET", true);
                }
            }
        }
    }

    void Register() override
    {
        AfterCast += SpellCastFn(spell_mage_firestarter::HandleAfterCast);
        OnCalcCritChance += SpellOnCalcCritChanceFn(spell_mage_firestarter::HandleCritChance);
    }
};

//235219 - Cold Snap
class spell_mage_cold_snap : public SpellScript
{
    PrepareSpellScript(spell_mage_cold_snap);

    void HandleOnHit(SpellEffIndex /*effIndex*/)
    {
        std::initializer_list<uint32> spells =
        {
            SPELL_MAGE_FROST_NOVA,
            SPELL_MAGE_CONE_OF_COLD,
            SPELL_MAGE_ICE_BARRIER,
            SPELL_MAGE_ICE_BLOCK
        };

        for (uint32 spellId : spells)
        {
            GetCaster()->GetSpellHistory()->ResetCooldown(spellId, true);

            if (SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(spellId))
                GetCaster()->GetSpellHistory()->ResetCharges(spellInfo->ChargeCategoryId);
        }
    }

    void Register() override
    {
        OnEffectHit += SpellEffectFn(spell_mage_cold_snap::HandleOnHit, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
    }
};

// Ice Block - 45438
class spell_mage_ice_block : public AuraScript
{
    PrepareAuraScript(spell_mage_ice_block);

    void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        GetTarget()->CastSpell(GetTarget(), SPELL_MAGE_HYPOTHERMIA, true);
    }

    void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (GetTarget()->HasAura(SPELL_MAGE_GLACIAL_INSULATION))
            GetTarget()->CastSpell(GetTarget(), SPELL_MAGE_ICE_BARRIER, true);
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_mage_ice_block::OnApply, EFFECT_2, SPELL_AURA_SCHOOL_IMMUNITY, AURA_EFFECT_HANDLE_REAL);
        OnEffectRemove += AuraEffectRemoveFn(spell_mage_ice_block::OnRemove, EFFECT_2, SPELL_AURA_SCHOOL_IMMUNITY, AURA_EFFECT_HANDLE_REAL);
    }
};

// Ice Barrier - 11426
class spell_mage_ice_barrier : public AuraScript
{
    PrepareAuraScript(spell_mage_ice_barrier);

    void CalculateAmount(AuraEffect const* /*aurEff*/, int32& amount, bool& canBeRecalculated)
    {
        canBeRecalculated = false;
        if (Unit* caster = GetCaster())
            amount = int32(CalculatePct(caster->GetMaxHealth(), GetSpellInfo()->GetEffect(EFFECT_1).CalcValue()));
    }

    void Absorb(AuraEffect* auraEffect, DamageInfo& dmgInfo, uint32& /*absorbAmount*/)
    {
        Unit* caster = auraEffect->GetCaster();
        Unit* target = dmgInfo.GetAttacker();
        if (!caster || !target)
            return;

        bool isHunter = (target->ToPlayer() && (target->ToPlayer()->GetSpecializationId() == TALENT_SPEC_HUNTER_MARKSMAN || target->ToPlayer()->GetSpecializationId() == TALENT_SPEC_HUNTER_BEASTMASTER));
        if ((dmgInfo.GetSpellInfo() && dmgInfo.GetSpellInfo()->RangeIndex == 2) || (!dmgInfo.GetSpellInfo() && !isHunter && (dmgInfo.GetAttackType() == BASE_ATTACK || dmgInfo.GetAttackType() == OFF_ATTACK)))
            caster->CastSpell(target, SPELL_MAGE_CHILLED, true);
    }

    void Register() override
    {
        DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_mage_ice_barrier::CalculateAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
        OnEffectAbsorb += AuraEffectAbsorbFn(spell_mage_ice_barrier::Absorb, EFFECT_0);
    }
};

// Chilled - 205708
class spell_mage_chilled : public AuraScript
{
    PrepareAuraScript(spell_mage_chilled);

    void HandleApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Unit* caster = GetCaster();
        if (!caster)
            return;
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_mage_chilled::HandleApply, EFFECT_0, SPELL_AURA_MOD_DECREASE_SPEED, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
    }
};

//Called By 205021 - Ray of Frost
//Last Update 8.0.1 Build 28153
class spell_mage_ray_of_frost : public SpellScript
{
    PrepareSpellScript(spell_mage_ray_of_frost);

    void HandlePrepare()
    {
        if (Unit* caster = GetCaster())
            caster->AddAura(SPELL_MAGE_RAY_OF_FROST_FINGERS_OF_FROST);
    }

    void Register() override
    {
        OnPrepare += SpellOnPrepareFn(spell_mage_ray_of_frost::HandlePrepare);
    }
};

//Called By 205021 - Ray of Frost
//Last Update 8.0.1 Build 28153
class aura_mage_ray_of_frost : public AuraScript
{
    PrepareAuraScript(aura_mage_ray_of_frost);

    void OnTick(AuraEffect const* /*auraEff*/)
    {
        if (Unit* caster = GetCaster())
        {
            caster->CastSpell(caster, SPELL_MAGE_RAY_OF_FROST_DAMAGE_INCREASE, true);

            if (AuraEffect* aurEff = GetAura()->GetEffect(EFFECT_1))
                aurEff->SetDamage(caster->SpellDamageBonusDone(GetTarget(), GetSpellInfo(), 0, DOT, aurEff->GetSpellEffectInfo(), GetStackAmount()) * aurEff->GetDonePct());

            if (Aura* aura = GetAura())
            {
                if (AuraEffect* aurEff = aura->GetEffect(0))
                    aurEff->RecalculateAmount();
            }
        }
    }

    void HandleRemove(AuraEffect const* /*aurEffect*/, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* caster = GetCaster())
            caster->RemoveAura(SPELL_MAGE_RAY_OF_FROST_FINGERS_OF_FROST);
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(aura_mage_ray_of_frost::OnTick, EFFECT_1, SPELL_AURA_PERIODIC_DAMAGE);
        OnEffectRemove += AuraEffectRemoveFn(aura_mage_ray_of_frost::HandleRemove, EFFECT_0, SPELL_AURA_MOD_DECREASE_SPEED, AURA_EFFECT_HANDLE_REAL);
    }
};

// Cone of Cold - 120
class spell_mage_cone_of_cold : public SpellScript
{
    PrepareSpellScript(spell_mage_cone_of_cold);

    void HandleOnHit(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!target || !caster)
            return;

        caster->CastSpell(target, SPELL_MAGE_CONE_OF_COLD_SLOW, true);

        if (caster->HasAura(SPELL_MAGE_BONE_CHILLING))
            caster->CastSpell(caster, SPELL_MAGE_BONE_CHILLING_BUFF, true);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_mage_cone_of_cold::HandleOnHit, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

// Ice Lance - 30455
class spell_mage_ice_lance : public SpellScript
{
    PrepareSpellScript(spell_mage_ice_lance);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_MAGE_THERMAL_VOID, SPELL_MAGE_WHITEOUT_POWER });
    }

    void HandlePrepare()
    {
        if (Unit* caster = GetCaster())
            if (caster->HasAura(SPELL_MAGE_FINGERS_OF_FROST_AURA))
                fingers = true;
    }

    void HandleAfterCast()
    {
        if (Unit* caster = GetCaster())
        {
            Aura* fingersOfFrost = caster->GetAura(SPELL_MAGE_FINGERS_OF_FROST_AURA);
            if (fingersOfFrost && fingersOfFrost->GetStackAmount() < 2)
                caster->RemoveAura(SPELL_MAGE_FINGERS_OF_FROST_VISUAL_UI);
        }
    }

    void HandleOnHit(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster && !target)
            return;

        // Fingers of Frost
        if (fingers || target->HasAuraState(AURA_STATE_FROZEN, NULL, caster))
        {
            int32 damage = caster->GetTotalSpellPowerValue(SPELL_SCHOOL_MASK_FROST, false) * 0.35f;
            caster->CastCustomSpell(SPELL_MAGE_ICE_LANCE_TRIGGER, SPELLVALUE_BASE_POINT0, damage * 2, target, true);
        }
        else
            caster->CastSpell(target, SPELL_MAGE_ICE_LANCE_TRIGGER, true);

        // Thermal Void
        if (caster->HasAura(SPELL_MAGE_THERMAL_VOID) && (target->HasAuraState(AURA_STATE_FROZEN, NULL, caster) || fingers))
        {
            if (Aura* icyVeins = caster->GetAura(SPELL_MAGE_ICY_VEINS))
            {
                if (SpellInfo const* thermalVoidInfo = sSpellMgr->GetSpellInfo(SPELL_MAGE_THERMAL_VOID))
                    //if (SpellEffectInfo const* eff0 = thermalVoidInfo->GetEffect(EFFECT_0))
                    {
                        int32 increaseDuration = thermalVoidInfo->GetEffect(EFFECT_0).CalcValue() * IN_MILLISECONDS;
                        int32 newDuration = (icyVeins->GetDuration() + increaseDuration);
                        icyVeins->SetDuration(newDuration);
                    }
            }
        }

        // Chain Reaction
        if (caster->HasAura(SPELL_MAGE_CHAIN_REACTION) && target->HasAuraState(AURA_STATE_FROZEN, NULL, caster))
            caster->CastSpell(caster, SPELL_MAGE_CHAIN_REACTION_BUFF, true);

        // Whiteout
        if (caster->HasAura(SPELL_MAGE_WHITEOUT_POWER))
            caster->GetSpellHistory()->ModifyCooldown(SPELL_MAGE_FROZEN_ORB, -500ms);

        // Packet Ice
        int32 extraDamage = 0;
        if (Aura* aura = caster->GetAura(SPELL_MAGE_PACKED_ICE))
            if (target->HasAura(SPELL_MAGE_PACKED_ICE_AURA, caster->GetGUID()))
                extraDamage = aura->GetEffect(EFFECT_0)->GetAmount();

        SetHitDamage(GetHitDamage() + extraDamage);
    }

    void HandleAfterHit()
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster && !target)
            return;

        if (target->IsAlive() && !caster->HasSpell(SPELL_MAGE_GLACIAL_SPIKE))
        {
            caster->Variables.Set("IciclesTarget", target->GetGUID());
            caster->CastSpell(caster, SPELL_MAGE_ICICLE_PERIODIC_TRIGGER, true);
        }
    }

    void Register() override
    {
        OnPrepare += SpellOnPrepareFn(spell_mage_ice_lance::HandlePrepare);
        AfterCast += SpellCastFn(spell_mage_ice_lance::HandleAfterCast);
        AfterHit += SpellHitFn(spell_mage_ice_lance::HandleAfterHit);
        OnEffectHitTarget += SpellEffectFn(spell_mage_ice_lance::HandleOnHit, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
    }

private:
    bool fingers = false;
};

// 31661
class spell_mage_dragon_breath : public AuraScript
{
    PrepareAuraScript(spell_mage_dragon_breath);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        // Dont proc with Living Bomb explosion
        SpellInfo const* spellInfo = eventInfo.GetSpellInfo();
        if (spellInfo && (spellInfo->ActiveIconFileDataId == 236220 || spellInfo->ActiveIconFileDataId == 135818) && spellInfo->SpellFamilyName == SPELLFAMILY_MAGE)
            return false;
        return true;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_mage_dragon_breath::CheckProc);
    }
};

// Flurry - 44614
class spell_mage_flurry : public SpellScript
{
    PrepareSpellScript(spell_mage_flurry);

    void HandleDummy(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        bool isImproved = false;
        if (!caster || !target)
            return;

        caster->Variables.Remove("BRAIN_FREEZE");
        if (caster->HasAura(SPELL_MAGE_BRAIN_FREEZE_AURA) && caster->GetCurrentSpellCastTime(SPELL_MAGE_FLURRY) == 0)
        {
            caster->RemoveAura(SPELL_MAGE_BRAIN_FREEZE_AURA);
            if (caster->HasSpell(SPELL_MAGE_BRAIN_FREEZE_IMPROVED))
                caster->Variables.Set<bool>("BRAIN_FREEZE", true);
        }

        ObjectGuid targetGuid = target->GetGUID();
        for (uint8 i = 0; i < GetEffectInfo(EFFECT_0).BasePoints - 1; ++i)
            caster->GetScheduler().Schedule(300ms * i, [targetGuid, isImproved](TaskContext context)
            {
                if (Unit* caster = GetContextUnit())
                    if (Unit* target = ObjectAccessor::GetUnit(*caster, targetGuid))
                        caster->CastSpell(target, SPELL_MAGE_FLURRY_VISUAL, false);
            });
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_mage_flurry::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

// Jouster - 214626
class spell_mage_jouster : public AuraScript
{
    PrepareAuraScript(spell_mage_jouster);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo()->Id == SPELL_MAGE_ICE_LANCE;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_mage_jouster::CheckProc);
    }
};

// Jouster Buff - 195391
class spell_mage_jouster_buff : public AuraScript
{
    PrepareAuraScript(spell_mage_jouster_buff);

    void CalculateAmount(AuraEffect const* /*aurEff*/, int32& amount, bool& /*canBeRecalculated*/)
    {
        Unit* caster = GetCaster();
        if (!caster)
            return;

        if (AuraEffect* jousterRank = caster->GetAuraEffect(SPELL_MAGE_JOUSTER, EFFECT_0))
            amount = jousterRank->GetAmount();
    }

    void Register() override
    {
        DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_mage_jouster_buff::CalculateAmount, EFFECT_0, SPELL_AURA_MOD_DAMAGE_PERCENT_TAKEN);
    }
};

// Chain Reaction - 195419
class spell_mage_chain_reaction : public AuraScript
{
    PrepareAuraScript(spell_mage_chain_reaction);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo()->Id == SPELL_MAGE_FROSTBOLT || eventInfo.GetSpellInfo()->Id == SPELL_MAGE_FROSTBOLT_TRIGGER;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_mage_chain_reaction::CheckProc);
    }
};

// Chilled to the Core - 195448
class spell_mage_chilled_to_the_core : public AuraScript
{
    PrepareAuraScript(spell_mage_chilled_to_the_core);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo()->Id == SPELL_MAGE_ICY_VEINS;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_mage_chilled_to_the_core::CheckProc);
    }
};

// Frostbolt - 228597
class spell_mage_frostbolt : public SpellScript
{
    PrepareSpellScript(spell_mage_frostbolt);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_MAGE_DEEP_SHATTER });
    }

    void HandleDummy(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        caster->CastSpell(target, SPELL_MAGE_CHILLED, true);

        if (caster->Variables.Exist("TARGET_TUNNEL_OF_ICE"))
        {
            if (target->GetGUID() != caster->Variables.GetValue<ObjectGuid>("TARGET_TUNNEL_OF_ICE"))
            {
                caster->Variables.Remove("TARGET_TUNNEL_OF_ICE");
                caster->RemoveAura(SPELL_MAGE_TUNNEL_OF_ICE_BUFF);
            }
        }

        // Brain Freeze
        if (caster->HasSpell(SPELL_MAGE_BRAIN_FREEZE))
        {
            int32 clarityOfThoughtChance = 0;
            float brainFreezeChance = sSpellMgr->GetSpellInfo(SPELL_MAGE_BRAIN_FREEZE)->GetEffect(EFFECT_0).CalcValue(caster);

            if (Aura* clarityOfThought = caster->GetAura(SPELL_MAGE_GLARITY_OF_THOUGHT))
            {
                clarityOfThoughtChance = (clarityOfThought->GetEffect(EFFECT_0)->GetAmount());
            }

            brainFreezeChance += clarityOfThoughtChance;

            if (roll_chance_i(brainFreezeChance))
                caster->CastSpell(caster, SPELL_MAGE_BRAIN_FREEZE_AURA, true);
        }

        // Fingers of Frost
        if (caster->HasSpell(SPELL_MAGE_FINGERS_OF_FROST))
        {
            float fingersFrostChance = sSpellMgr->GetSpellInfo(SPELL_MAGE_FINGERS_OF_FROST)->GetEffect(EFFECT_0).CalcValue(caster);

            if (caster->HasAura(SPELL_MAGE_FROZEN_TOUCH))
            {
                if (Aura* frozenTouchPct = caster->GetAura(SPELL_MAGE_FROZEN_TOUCH))
                {
                    int32 pct = frozenTouchPct->GetEffect(EFFECT_0)->GetAmount();
                    AddPct(fingersFrostChance, pct);
                }
            }

            if (roll_chance_f(fingersFrostChance))
            {
                if (caster->HasAura(SPELL_MAGE_FINGERS_OF_FROST_AURA))
                    caster->CastSpell(caster, SPELL_MAGE_FINGERS_OF_FROST_VISUAL_UI, true);
                caster->CastSpell(caster, SPELL_MAGE_FINGERS_OF_FROST_AURA, true);
            }
        }

        // Deep Shatter
        if (caster->HasAura(SPELL_MAGE_DEEP_SHATTER) && target->HasAuraState(AURA_STATE_FROZEN, NULL, caster))
        {
            int32 baseDamage = GetHitDamage();
            SetHitDamage(baseDamage + CalculatePct(baseDamage, sSpellMgr->GetSpellInfo(SPELL_MAGE_DEEP_SHATTER)->GetEffect(EFFECT_0).BasePoints));
        }

        Unit* pet = caster->GetGuardianPet();
        if (!pet)
            return;

        // Water Jet
        if (target->HasAura(SPELL_MAGE_WATER_JET, pet->GetGUID()))
        {
            if (caster->HasAura(SPELL_MAGE_FINGERS_OF_FROST_AURA))
                caster->CastSpell(caster, SPELL_MAGE_FINGERS_OF_FROST_VISUAL_UI, true);
            caster->CastSpell(caster, SPELL_MAGE_FINGERS_OF_FROST_AURA, true);
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_mage_frostbolt::HandleDummy, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

// Ice Nova | Supernova - 157997 | 157980
//Last Update 8.0.1 Build 28153
class spell_mage_nova_talent : public SpellScript
{
    PrepareSpellScript(spell_mage_nova_talent);

    void HandleDamage(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        Unit* explTarget = GetExplTargetUnit();
        if (!target || !caster || !explTarget)
            return;

        bool iceNova = GetSpellInfo()->Id == SPELL_MAGE_ICE_NOVA;
        SpellEffIndex effectIndex = iceNova ? EFFECT_2 : EFFECT_0;

       // if (SpellEffectInfo const* eff = GetSpellInfo()->GetEffect(effectIndex))
        {
            int32 dmg = GetHitDamage();
            if (target == explTarget)
            {
                if(iceNova)
                    dmg = CalculatePct(dmg, GetSpellInfo()->GetEffect(effectIndex).BasePoints);
                else
                    dmg += CalculatePct(dmg, GetSpellInfo()->GetEffect(effectIndex).BasePoints);
            }

            SetHitDamage(dmg);
        }
    }

    void Register() override
    {
        if(m_scriptSpellId == SPELL_MAGE_ICE_NOVA)
            OnEffectHitTarget += SpellEffectFn(spell_mage_nova_talent::HandleDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
        else
            OnEffectHitTarget += SpellEffectFn(spell_mage_nova_talent::HandleDamage, EFFECT_1, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

// Blizzard damge - 190357
class spell_mage_blizzard : public SpellScript
{
    PrepareSpellScript(spell_mage_blizzard);

    void HandleHit(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        caster->CastSpell(target, SPELL_MAGE_CHILLED, true);

        if (AuraEffect* eff0 = caster->GetAuraEffect(SPELL_MAGE_BLIZZARD_RANK_2, EFFECT_0))
        {
            caster->GetSpellHistory()->ModifyCooldown(SPELL_MAGE_FROZEN_ORB, eff0->GetAmount() * -10ms);
            caster->GetSpellHistory()->ModifyCooldown(SPELL_MAGE_FROZEN_ORB_PVP, eff0->GetAmount() * -10ms);
        }

        // Fingers of Frost
        if (caster->HasSpell(SPELL_MAGE_FINGERS_OF_FROST))
        {
            float fingersFrostChance = sSpellMgr->GetSpellInfo(SPELL_MAGE_FINGERS_OF_FROST)->GetEffect(EFFECT_0).CalcValue(caster);

            if (caster->HasAura(SPELL_MAGE_FROZEN_TOUCH))
            {
                if (Aura* frozenTouchPct = caster->GetAura(SPELL_MAGE_FROZEN_TOUCH))
                {
                    int32 pct = frozenTouchPct->GetEffect(EFFECT_0)->GetAmount();
                    AddPct(fingersFrostChance, pct);
                }
            }

            if (roll_chance_f(fingersFrostChance))
            {
                if (caster->HasAura(SPELL_MAGE_FINGERS_OF_FROST_AURA))
                    caster->CastSpell(caster, SPELL_MAGE_FINGERS_OF_FROST_VISUAL_UI, true);
                caster->CastSpell(caster, SPELL_MAGE_FINGERS_OF_FROST_AURA, true);
            }
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_mage_blizzard::HandleHit, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

// Frozen Orb (damage) - 84721
class spell_mage_frozen_orb : public SpellScript
{
    PrepareSpellScript(spell_mage_frozen_orb);

    void HandleHit(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        caster->CastSpell(target, SPELL_MAGE_CHILLED, true);

        // Fingers of Frost
        if (caster->HasSpell(SPELL_MAGE_FINGERS_OF_FROST))
        {
            float fingersFrostChance = sSpellMgr->GetSpellInfo(SPELL_MAGE_FINGERS_OF_FROST)->GetEffect(EFFECT_0).CalcValue(caster);

            if (caster->HasAura(SPELL_MAGE_FROZEN_TOUCH))
            {
                if (AuraEffect* frozenEff0 = caster->GetAuraEffect(SPELL_MAGE_FROZEN_TOUCH, EFFECT_0))
                {
                    int32 pct = frozenEff0->GetAmount();
                    AddPct(fingersFrostChance, pct);
                }
            }

            if (roll_chance_f(fingersFrostChance))
            {
                if (caster->HasAura(SPELL_MAGE_FINGERS_OF_FROST_AURA))
                    caster->CastSpell(caster, SPELL_MAGE_FINGERS_OF_FROST_VISUAL_UI, true);
                caster->CastSpell(caster, SPELL_MAGE_FINGERS_OF_FROST_AURA, true);
            }
        }
    }

    void HandleAfterCast()
    {
        if (Unit* caster = GetCaster())
            if (caster->HasAura(SPELL_MAGE_FREEZING_RAIN))
                caster->CastSpell(caster, SPELL_MAGE_FREEZING_RAIN_BUFF, true);
    }

    void Register() override
    {
        AfterCast += SpellCastFn(spell_mage_frozen_orb::HandleAfterCast);
        OnEffectHitTarget += SpellEffectFn(spell_mage_frozen_orb::HandleHit, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

//7.3.2.25549 END

// Combustion - 190319
class spell_mage_combustion : public SpellScriptLoader
{
public:
    spell_mage_combustion() : SpellScriptLoader("spell_mage_combustion") {}

    class spell_mage_combustion_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_mage_combustion_AuraScript);

        void CalcAmount(AuraEffect const* /*aurEff*/, int32& amount, bool& /*canBeRecalculated*/)
        {
            if (Unit* caster = GetCaster())
            {
                if (!caster->IsPlayer())
                    return;

                int32 crit = caster->ToPlayer()->m_activePlayerData->CombatRatings[CR_CRIT_SPELL];
                amount += CalculatePct(crit, sSpellMgr->GetSpellInfo(SPELL_MAGE_COMBUSTION)->GetEffect(EFFECT_2).BasePoints);
            }
        }

        void HandleRemove(AuraEffect const* /*aurEffect*/, AuraEffectHandleModes /*mode*/)
        {
            if (Unit* caster = GetCaster())
                caster->RemoveAurasDueToSpell(SPELL_INFERNO);
        }

        void Register() override
        {
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_mage_combustion_AuraScript::CalcAmount, EFFECT_1, SPELL_AURA_MOD_RATING);
            OnEffectRemove += AuraEffectRemoveFn(spell_mage_combustion_AuraScript::HandleRemove, EFFECT_1, SPELL_AURA_MOD_RATING, AURA_EFFECT_HANDLE_REAL);
        }
    };

    class spell_mage_combustion_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_mage_combustion_SpellScript);

        void HandleAfterCast()
        {
            if (Unit* caster = GetCaster())
                if (caster->HasSpell(116011)) // Rune of Power
                    caster->CastSpell(caster, 116011, CastSpellExtraArgs(TRIGGERED_DONT_CREATE_COOLDOWN | TRIGGERED_FULL_MASK));

        }

        void Register() override
        {
            AfterCast += SpellCastFn(spell_mage_combustion_SpellScript::HandleAfterCast);
        }

    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_mage_combustion_SpellScript();
    }

    AuraScript* GetAuraScript() const override
    {
        return new spell_mage_combustion_AuraScript();
    }
};

// Incanter's Flow - 1463
class spell_mage_incanters_flow : public SpellScriptLoader
{
public:
    spell_mage_incanters_flow() : SpellScriptLoader("spell_mage_incanters_flow") { }

    class spell_mage_incanters_flow_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_mage_incanters_flow_AuraScript);

        bool m_Up = true;
        bool m_Changed = false;

        void OnTick(AuraEffect const* /*auraEff*/)
        {
            if (Unit* caster = GetCaster())
            {
                /// Break the cycle if caster is out of combat
                if (!caster->IsInCombat())
                    return;

                if (caster->HasAura(SPELL_MAGE_INCANTERS_FLOW_BUFF))
                {
                    if (Aura* incantersFlow = caster->GetAura(SPELL_MAGE_INCANTERS_FLOW_BUFF))
                    {
                        m_Changed = false;

                        if (incantersFlow->GetStackAmount() == 5 && m_Up)
                        {
                            m_Up = false;
                            m_Changed = true;
                        }
                        else if (incantersFlow->GetStackAmount() == 1 && !m_Up)
                        {
                            m_Up = true;
                            m_Changed = true;
                        }

                        if (!m_Changed)
                            incantersFlow->ModStackAmount(m_Up ? 1 : -1);
                    }
                }
                else if (caster->IsInCombat())
                {
                    caster->CastSpell(caster, SPELL_MAGE_INCANTERS_FLOW_BUFF, true);
                    m_Up = true;
                    m_Changed = false;
                }
            }
        }

        void Register() override
        {
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_mage_incanters_flow_AuraScript::OnTick, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_mage_incanters_flow_AuraScript();
    }
};

// Time Warp - 80353
class spell_mage_time_warp : public SpellScriptLoader
{
    public:
        spell_mage_time_warp() : SpellScriptLoader("spell_mage_time_warp") { }

        class spell_mage_time_warp_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_mage_time_warp_SpellScript);

            std::vector<uint32> spellIds
            {
                SPELL_MAGE_TEMPORAL_DISPLACEMENT,
                SPELL_HUNTER_INSANITY,
                SPELL_SHAMAN_EXHAUSTION,
                SPELL_SHAMAN_SATED,
                SPELL_PET_NETHERWINDS_FATIGUED
            };

            bool Validate(SpellInfo const* /*spellInfo*/) override
            {
                for (uint32 spell : spellIds)
                {
                    if (!sSpellMgr->GetSpellInfo(spell))
                        return false;
                }
                return true;
            }

            SpellCastResult CheckCast()
            {
                if (GetCaster()->GetTypeId() != TYPEID_PLAYER)
                    return SPELL_FAILED_DONT_REPORT;
                Player* player = GetCaster()->ToPlayer();
                Group* grp = player->GetGroup();
                if (!grp)
                {
                    return HasSated(player) ? SPELL_FAILED_CANT_DO_THAT_RIGHT_NOW : SPELL_CAST_OK;
                }
                for (GroupReference* itr = grp->GetFirstMember(); itr != NULL; itr = itr->next())
                {
                    Player* member = itr->GetSource();

                    if (!member || !member->GetSession())
                        continue;

                    if (!HasSated(member))
                    {
                        return SPELL_CAST_OK; // we have at least one valid target
                    }
                }
                return SPELL_FAILED_CANT_DO_THAT_RIGHT_NOW;
            }

            bool HasSated(Unit* target)
            {
                for (uint32 spell : spellIds)
                {
                    if (target->HasAura(spell))
                        return true;
                }
                return false;
            }

            void RemoveInvalidTargets(std::list<WorldObject*>& targets)
            {
                for (uint32 spell : spellIds)
                {
                    targets.remove_if(Trinity::UnitAuraCheck(true, spell));
                }
            }

            void ApplyDebuff()
            {
                if (Unit* target = GetHitUnit())
                    target->CastSpell(target, SPELL_MAGE_TEMPORAL_DISPLACEMENT, true);
            }

            void Register() override
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_mage_time_warp_SpellScript::RemoveInvalidTargets, EFFECT_ALL, TARGET_UNIT_CASTER_AREA_RAID);
                AfterHit += SpellHitFn(spell_mage_time_warp_SpellScript::ApplyDebuff);
                OnCheckCast += SpellCheckCastFn(spell_mage_time_warp_SpellScript::CheckCast);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_mage_time_warp_SpellScript();
        }
};

// Fire mage (passive) - 137019
class spell_mage_fire_mage_passive : public SpellScriptLoader
{
public:
    spell_mage_fire_mage_passive() : SpellScriptLoader("spell_mage_fire_mage_passive") {}

    class spell_mage_fire_mage_passive_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_mage_fire_mage_passive_AuraScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_MAGE_FIRE_MAGE_PASSIVE) ||
                !sSpellMgr->GetSpellInfo(SPELL_MAGE_FIRE_BLAST))
                return false;
            return true;
        }

    public:

        spell_mage_fire_mage_passive_AuraScript() {}

    private:

        SpellModifierByClassMask* l_Mod = nullptr;

        void HandleApply(AuraEffect const* aurEffect, AuraEffectHandleModes /*mode*/)
        {
            Player* player = GetCaster()->ToPlayer();
            if (!player)
                return;

            auto l_Mod = new SpellModifierByClassMask(aurEffect->GetBase());
            l_Mod->op = SpellModOp::CritChance;
            l_Mod->type = SPELLMOD_FLAT;
            l_Mod->spellId = SPELL_MAGE_FIRE_MAGE_PASSIVE;
            l_Mod->value = 200;
            l_Mod->mask[0] = 0x2;
            player->AddSpellMod(l_Mod, true);
        }

        void HandleRemove(AuraEffect const* /*aurEffect*/, AuraEffectHandleModes /*mode*/)
        {
            Player* player = GetCaster()->ToPlayer();
            if (!player)
                return;

            // how does mem free here?
            if (l_Mod)
                player->AddSpellMod(l_Mod, false);
        }

        void Register() override
        {
            OnEffectApply += AuraEffectApplyFn(spell_mage_fire_mage_passive_AuraScript::HandleApply, EFFECT_4, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            OnEffectRemove += AuraEffectRemoveFn(spell_mage_fire_mage_passive_AuraScript::HandleRemove, EFFECT_4, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_mage_fire_mage_passive_AuraScript();
    }
};

// Ice Floes - 108839
class spell_mage_ice_floes : public AuraScript
{
    PrepareAuraScript(spell_mage_ice_floes);

    void HandleApply(AuraEffect const* aurEffect, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* caster = GetCaster())
        {
            caster->RemoveAura(66);
            caster->RemoveAura(32612);
        }
    }

    void HandleAfterProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->CalcCastTime())
            if (Unit* caster = GetCaster())
                if (Aura* iceFloes = caster->GetAura(SPELL_MAGE_ICE_FLOES))
                    iceFloes->ModStackAmount(-1);
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_mage_ice_floes::HandleApply, EFFECT_0, SPELL_AURA_CAST_WHILE_WALKING, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
        AfterProc += AuraProcFn(spell_mage_ice_floes::HandleAfterProc);
    }
};

// Flame On - 205029
class spell_mage_fire_on : public SpellScriptLoader
{
public:
    spell_mage_fire_on() : SpellScriptLoader("spell_mage_fire_on") { }

    class spell_mage_fire_on_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_mage_fire_on_SpellScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            return ValidateSpellInfo({
                    SPELL_MAGE_FIRE_ON,
                    SPELL_MAGE_FIRE_BLAST
                });
        }

        void HandleDummy(SpellEffIndex /*effIndex*/)
        {
            Unit* caster = GetCaster();
            Unit* target = GetHitUnit();
            if (!caster || !target || caster->GetTypeId() != TYPEID_PLAYER)
                return;

            caster->ToPlayer()->GetSpellHistory()->ResetCharges(sSpellMgr->GetSpellInfo(SPELL_MAGE_FIRE_BLAST)->ChargeCategoryId);
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_mage_fire_on_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_mage_fire_on_SpellScript();
    }
};

/// Mirror Image - 55342
/// Updated 9.2.0.43345
class spell_mage_mirror_image_summon : public SpellScript
{
    PrepareSpellScript(spell_mage_mirror_image_summon);

    enum MirrorImages
    {
        MirrorImageSummon    = 321686,
        MirrorImageSummonNpc = 31216,
        CloneMe              = 45204,
        MirrorImageAura      = 252206,
    };

    void HandleDummy(SpellEffIndex /*effIndex*/)
    {
        if (Unit* caster = GetCaster())
        {
            auto SummonMirrorImage([&](float angle)
            {
                caster->CastSpell(caster->GetNearPosition(3.0f, angle), MirrorImageSummon, true);
            });

            // cast - 321686 (MirrorImageSummon) at a location x3
            SummonMirrorImage(0.0f);
            SummonMirrorImage(90.0f);
            SummonMirrorImage(180.0f);

            // casted - 55342 (this spell)
        }
    }

    void HandleAfterCast()
    {
        if (Unit* caster = GetCaster())
        {
            float angle = 90.0f;
            caster->DoOnSummons([caster, &angle](Creature* creature)
            {
                if (creature->GetEntry() == MirrorImageSummonNpc)
                {
                    // cast clone me on target 31216
                    // cast 252206 Mirror Image on target 31216
                    caster->CastSpell(creature, CloneMe, true);
                    caster->CastSpell(creature, MirrorImageAura, true);

                    if (auto minion = creature->ToMinion())
                    {
                        minion->Variables.Set("DontUseCombatReach", true);
                        minion->SetFollowAngle(angle);
                        angle += 90.0f;
                        minion->GetMotionMaster()->MoveFollow(caster, PET_FOLLOW_DIST, minion->GetFollowAngle(), MovementSlot::MOTION_SLOT_ACTIVE);
                    }
                }
            });
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_mage_mirror_image_summon::HandleDummy, EFFECT_1, SPELL_EFFECT_DUMMY);
        AfterCast += SpellCastFn(spell_mage_mirror_image_summon::HandleAfterCast);
    }
};

// Cauterize - 86949
class spell_mage_cauterize : public SpellScriptLoader
{
public:
    spell_mage_cauterize() : SpellScriptLoader("spell_mage_cauterize") { }

    class spell_mage_cauterize_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_mage_cauterize_AuraScript);

        int32 healtPct;

        bool Load() override
        {
            healtPct = GetSpellInfo()->GetEffect(EFFECT_1).CalcValue(GetCaster()); // 35%
            return GetUnitOwner()->GetTypeId() == TYPEID_PLAYER;
        }

        void OnAbsorb(AuraEffect* /*aurEff*/, DamageInfo& dmgInfo, uint32& /*absorbAmount*/)
        {
            if (Unit* caster = GetCaster())
            {
                if (!caster->GetSpellHistory()->HasCooldown(SPELL_MAGE_CAUTERIZE) && dmgInfo.GetDamage() >= caster->GetHealth())
                {
                    PreventDefaultAction();
                    uint64 health7 = caster->CountPctFromMaxHealth(35);
                    HealInfo healInfo(caster, caster, health7, GetSpellInfo(), GetSpellInfo()->GetSchoolMask());
                    caster->HealBySpell(healInfo);
                    caster->CastSpell(caster, SPELL_MAGE_CAUTERIZE, true);
                    caster->CastSpell(caster, GetSpellInfo()->GetEffect(EFFECT_2).TriggerSpell, true); // blazing speed
                    caster->GetSpellHistory()->AddCooldown(SPELL_MAGE_CAUTERIZE, 0, std::chrono::minutes(2));
                }
            }
        }

        void Register() override
        {
            OnEffectAbsorb += AuraEffectAbsorbOverkillFn(spell_mage_cauterize_AuraScript::OnAbsorb, EFFECT_0);
        }
    };

    class spell_mage_cauterize_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_mage_cauterize_SpellScript);

        void PreventTrigger(SpellEffIndex effIndex)
        {
            PreventHitEffect(effIndex);
        }

        void Register() override
        {
            OnEffectHit += SpellEffectFn(spell_mage_cauterize_SpellScript::PreventTrigger, EFFECT_2, SPELL_EFFECT_TRIGGER_SPELL);
            OnEffectHitTarget += SpellEffectFn(spell_mage_cauterize_SpellScript::PreventTrigger, EFFECT_2, SPELL_EFFECT_TRIGGER_SPELL);
            OnEffectLaunch += SpellEffectFn(spell_mage_cauterize_SpellScript::PreventTrigger, EFFECT_2, SPELL_EFFECT_TRIGGER_SPELL);
            OnEffectLaunchTarget += SpellEffectFn(spell_mage_cauterize_SpellScript::PreventTrigger, EFFECT_2, SPELL_EFFECT_TRIGGER_SPELL);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_mage_cauterize_AuraScript();
    }

    SpellScript* GetSpellScript() const override
    {
        return new spell_mage_cauterize_SpellScript();
    }
};

// Ring of Frost - 136511
class spell_mage_ring_of_frost : public AuraScript
{
    PrepareAuraScript(spell_mage_ring_of_frost);

    enum eNpc
    {
        NPC_RING_OF_FROST = 44199,
    };

    bool Validate(SpellInfo const* /*spell*/) override
    {
        return ValidateSpellInfo({ SPELL_MAGE_RING_OF_FROST, SPELL_MAGE_RING_OF_FROST_FREEZE });
    }

    void OnTick(AuraEffect const* /*aurEff*/)
    {
        if (Unit* caster = GetCaster())
        {
            if (Unit* frozenRing = caster->GetSummonedCreatureByEntry(NPC_RING_OF_FROST))
            {
                if (frozenRing->IsCreature())
                {
                    if (!frozenRing->HasUnitState(UNIT_STATE_ROOT))
                    {
                        frozenRing->ToCreature()->SetReactState(REACT_PASSIVE);
                        frozenRing->SetControlled(true, UNIT_STATE_ROOT);
                    }

                    caster->CastSpell(frozenRing->GetPosition(), SPELL_MAGE_RING_OF_FROST_FREEZE, true);
                }
            }
        }
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_mage_ring_of_frost::OnTick, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
    }
};

// Ring of Frost - 82691
class spell_mage_ring_of_frost_stun : public SpellScriptLoader
{
public:
    spell_mage_ring_of_frost_stun() : SpellScriptLoader("spell_mage_ring_of_frost_stun") { }

    class spell_mage_ring_of_frost_stun_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_mage_ring_of_frost_stun_AuraScript);

        void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            Unit* caster = GetCaster();
            Unit* target = GetTarget();
            if (!target || !caster)
                return;

            caster->CastSpell(target, SPELL_MAGE_RING_OF_FROST_IMMUNE, true);
        }

        void Register() override
        {
            OnEffectRemove += AuraEffectRemoveFn(spell_mage_ring_of_frost_stun_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_MOD_STUN, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_mage_ring_of_frost_stun_AuraScript();
    }

    class spell_mage_ring_of_frost_stun_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_mage_ring_of_frost_stun_SpellScript);

        void CheckTargets(std::list<WorldObject*>& targets)
        {
            // following the visual's size
            float radiusMin = 5.0f;
            float radiusMax = 6.5f;
            WorldLocation const* center = GetExplTargetDest();
            if (!center)
            {
                // should never happen
                targets.clear();
                return;
            }

            // prevent reapply at every 100ms or if it was just removed and immune for 2.5secs, also check inner/outer circle distance
            const SpellInfo* spell = GetSpellInfo();
            targets.remove_if([spell, radiusMin, radiusMax, center](WorldObject* obj) -> bool
            {
                if (Unit* unit = obj->ToUnit())
                {
                    if (unit->HasAura(spell->Id) || unit->HasAura(SPELL_MAGE_RING_OF_FROST_IMMUNE))
                        return true;
                    if (unit->GetPosition().GetExactDist(center->GetPosition()) >= radiusMin && unit->GetPosition().GetExactDist(center->GetPosition()) <= radiusMax)
                        return false;
                }
                return true;
            });
        }

        void Register() override
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_mage_ring_of_frost_stun_SpellScript::CheckTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ENEMY);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_mage_ring_of_frost_stun_SpellScript();
    }
};

// Freeze (Water Elemental's) - 33395
class spell_mage_pet_freeze : public AuraScript
{
    PrepareAuraScript(spell_mage_pet_freeze);

    void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* caster = GetCaster())
        {
            if (Unit* owner = caster->GetOwner())
            {
                if (Player* player = owner->ToPlayer())
                {
                    if (player->HasAura(SPELL_MAGE_FINGERS_OF_FROST_AURA))
                        player->CastSpell(player, SPELL_MAGE_FINGERS_OF_FROST_VISUAL_UI, true);
                    player->CastSpell(player, SPELL_MAGE_FINGERS_OF_FROST_AURA, true);
                }
            }
        }
    }

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetDamageInfo() && (eventInfo.GetDamageInfo()->GetDamageType() != HEAL && eventInfo.GetDamageInfo()->GetDamageType() != NODAMAGE))
        {

            Unit* caster = GetCaster();
            Unit* target = GetTarget();
            if (!caster || !target)
                return false;

            Aura* aura = GetAura();

            // Freeze will be removed if the damage if greater or equal to 10% of the target maximun health.
            uint32 ten = CalculatePct(target->GetMaxHealth(), 10);
            if (eventInfo.GetDamageInfo()->GetDamage() >= ten)
                return true;

            // We need to "save" the amount of damage.
            if (aura->Variables.Exist("DAMAGE"))
            {
                uint32 currentDamage = aura->Variables.GetValue<uint32>("DAMAGE");
                uint32 newDamage = currentDamage + eventInfo.GetDamageInfo()->GetDamage();
                aura->Variables.Set<uint32>("DAMAGE", newDamage);
                if (newDamage >= ten)
                    return true;
            }
            else
                aura->Variables.Set<uint32>("DAMAGE", eventInfo.GetDamageInfo()->GetDamage());
        }

        return false;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (WorldObject* owner = GetOwner())
            if (owner->ToUnit())
                owner->ToUnit()->RemoveAura(SPELL_MAGE_FREEZE);
    }

    void HandleRemove(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
    {
        Unit* caster = GetCaster();
        Unit* owner = GetUnitOwner();
        if (!caster || !owner)
            return;

        // This is a pet
        if (Unit* petOwner = caster->GetOwner())
            if (Player* player = petOwner->ToPlayer())
                if (player->HasAura(SPELL_MAGE_CHILLED_TO_THE_BONE))
                {
                    if (GetTargetApplication()->GetRemoveMode() == AURA_REMOVE_BY_DEATH)
                        return;

                    int32 baseDamage = player->GetTotalSpellPowerValue(SPELL_SCHOOL_MASK_FROST, false);
                    if (GetTargetApplication()->GetRemoveMode() == AURA_REMOVE_BY_ENEMY_SPELL)
                        player->CastCustomSpell(SPELL_MAGE_CHILLED_TO_THE_BONE_DAMAGE, SPELLVALUE_BASE_POINT0, baseDamage * 2, owner, true);
                    else
                        player->CastSpell(owner, SPELL_MAGE_CHILLED_TO_THE_BONE_DAMAGE, true);
                }
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_mage_pet_freeze::OnApply, EFFECT_0, SPELL_AURA_MOD_ROOT_2, AURA_EFFECT_HANDLE_REAL);
        DoCheckProc += AuraCheckProcFn(spell_mage_pet_freeze::CheckProc);
        OnProc += AuraProcFn(spell_mage_pet_freeze::HandleProc);
        OnEffectRemove += AuraEffectRemoveFn(spell_mage_pet_freeze::HandleRemove, EFFECT_0, SPELL_AURA_MOD_ROOT_2, AURA_EFFECT_HANDLE_REAL);
    }
};

// 1953 - Blink / 212653 - Shimmer (Arcane)
class spell_mage_blink : public SpellScript
{
    PrepareSpellScript(spell_mage_blink);

    void HandleOnCast()
    {
        if (Unit* caster = GetCaster())
        {
            if (caster->ToPlayer()->GetSpecializationId() == TALENT_SPEC_MAGE_ARCANE)
            {
                if (caster->HasSpell(SPELL_MAGE_DISPLACEMENT) || caster->HasSpell(SPELL_MAGE_DISPLACEMENT_ARCANE))
                {
                    caster->ToPlayer()->SaveBlinkPosition();
                    caster->ToPlayer()->GetSpellHistory()->ResetCooldown(SPELL_MAGE_DISPLACEMENT_BEACON, true);
                    caster->CastSpell(caster, SPELL_MAGE_DISPLACEMENT_BEACON, true);
                }
            }
            caster->RemoveAura(66); // Invisiblity
            caster->RemoveAura(32612); // Invisibility 
            caster->RemoveAura(110960); // 110960 Greater Invisibility

            // Cauterize
            if (Aura* aura = caster->GetAura(SPELL_MAGE_CAUTERIZE_BLINK_POWER))
                caster->CastCustomSpell(SPELL_MAGE_CAUTERIZE_BLIBK_HEAL, SPELLVALUE_BASE_POINT0, aura->GetEffect(0)->GetAmount() / 4, caster, true);

            // Prismatic Cloak
            if (GetSpellInfo()->Id == SPELL_MAGE_SHIMMER && caster->HasAura(SPELL_MAGE_PRISMATIC_CLOAK))
                caster->CastSpell(caster, SPELL_MAGE_PISTMATIC_CLOAK_TRIGGER, true);

            // Blazing Soul
            if (caster->HasAura(SPELL_MAGE_BLAZING_SOUL))
                caster->CastSpell(caster, SPELL_MAGE_BLAZING_BARRIER, true);
        }
    }

    void Register() override
    {
        OnCast += SpellCastFn(spell_mage_blink::HandleOnCast);
    }
};

// 195676, 212801 - Displacement
class spell_mage_displacement : public SpellScript
{
    PrepareSpellScript(spell_mage_displacement);

    void HandleDummy(SpellEffIndex /*effIndex*/)
    {
        if (Unit* caster = GetCaster())
        {
            if (caster->HasSpell(SPELL_MAGE_SHIMMER))
                caster->GetSpellHistory()->ResetCharges(sSpellMgr->GetSpellInfo(SPELL_MAGE_SHIMMER)->ChargeCategoryId);
            else
                caster->GetSpellHistory()->ResetCharges(sSpellMgr->GetSpellInfo(SPELL_MAGE_BLINK)->ChargeCategoryId);
            caster->ToPlayer()->RecallBlink(); // recall back
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_mage_displacement::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

// Conjure Refreshment - 190336
class spell_mage_conjure_refreshment : public SpellScriptLoader
{
public:
    spell_mage_conjure_refreshment() : SpellScriptLoader("spell_mage_conjure_refreshment") { }

    class spell_mage_conjure_refreshment_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_mage_conjure_refreshment_SpellScript);

        void HandleOnHit()
        {
            if (Player* player = GetCaster()->ToPlayer())
            {
                if (Group* group = player->GetGroup())
                    player->CastSpell(player, SPELL_MAGE_CONJURE_REFRESHMENT_GROUP, true);
                else
                    player->CastSpell(player, SPELL_MAGE_CONJURE_REFRESHMENT_SOLO, true);
            }
        }

        void Register() override
        {
            OnHit += SpellHitFn(spell_mage_conjure_refreshment_SpellScript::HandleOnHit);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_mage_conjure_refreshment_SpellScript();
    }
};


// Meteor - 177345
// AreaTriggerID - 3467
class at_mage_meteor_timer : public AreaTriggerEntityScript
{
public:
    at_mage_meteor_timer() : AreaTriggerEntityScript("at_mage_meteor_timer") {}

    struct at_mage_meteor_timerAI : AreaTriggerAI
    {
        at_mage_meteor_timerAI(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger) { }

        void OnCreate() override
        {
            Unit* caster = at->GetCaster();
            if (!caster)
                return;

            if (TempSummon* tempSumm = caster->SummonCreature(WORLD_TRIGGER, at->GetPosition(), TEMPSUMMON_TIMED_DESPAWN, 3s))
            {
                tempSumm->SetFaction(caster->GetFaction());
                tempSumm->SetOwnerGUID(caster->GetGUID());
                PhasingHandler::InheritPhaseShift(tempSumm, caster);

                caster->CastSpell(tempSumm, SPELL_MAGE_METEOR_VISUAL, true);
				Position pos = tempSumm->GetPosition();
                caster->GetScheduler().Schedule(Milliseconds(1500), [caster, this, pos](TaskContext context)
                {
                    if (caster && at)
                        caster->CastSpell(pos, SPELL_MAGE_METEOR_DAMAGE, true);
                });
            }
        }
    };

    AreaTriggerAI* GetAI(AreaTrigger* areatrigger) const override
    {
        return new at_mage_meteor_timerAI(areatrigger);
    }
};

// Meteor Burn - 175396
// AreaTriggerID - 1712
class at_mage_meteor_burn : public AreaTriggerEntityScript
{
public:
    at_mage_meteor_burn() : AreaTriggerEntityScript("at_mage_meteor_burn") { }

    struct at_mage_meteor_burnAI : AreaTriggerAI
    {
        at_mage_meteor_burnAI(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger) { }

        void OnUnitEnter(Unit* unit) override
        {
            Unit* caster = at->GetCaster();

            if (!caster || !unit)
                return;

            if (caster->GetTypeId() != TYPEID_PLAYER)
                return;

            if (caster->IsValidAttackTarget(unit))
            {
                caster->CastSpell(unit, SPELL_MAGE_METEOR_BURN, true);
                caster->CastSpell(unit, SPELL_MAGE_IGNITE_DOT, true);
            }
        }

        void OnUnitExit(Unit* unit) override
        {
            Unit* caster = at->GetCaster();

            if (!caster || !unit)
                return;

            if (caster->GetTypeId() != TYPEID_PLAYER)
                return;

            if (Aura* meteor = unit->GetAura(SPELL_MAGE_METEOR_BURN, caster->GetGUID()))
                meteor->SetDuration(0);
        }
    };

    AreaTriggerAI* GetAI(AreaTrigger* areatrigger) const override
    {
        return new at_mage_meteor_burnAI(areatrigger);
    }
};

// Blizzard - 190356
// AreaTriggerID - 4658
class at_mage_blizzard : public AreaTriggerEntityScript
{
public:
    at_mage_blizzard() : AreaTriggerEntityScript("at_mage_blizzard") { }

    struct at_mage_blizzardAI : AreaTriggerAI
    {
        at_mage_blizzardAI(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger)
        {
            timeInterval = 1000;
        }

        int32 timeInterval;

        enum UsingSpells
        {
            SPELL_MAGE_BLIZZARD_DAMAGE = 190357
        };

        void OnCreate() override
        {
            if (Unit* caster = at->GetCaster())
                if (caster->HasAura(SPELL_MAGE_FREEZING_RAIN_BUFF))
                    caster->RemoveAurasDueToSpell(SPELL_MAGE_FREEZING_RAIN_BUFF);
        }

        void OnUpdate(uint32 diff) override
        {
            Unit* caster = at->GetCaster();

            if (!caster)
                return;

            if (caster->GetTypeId() != TYPEID_PLAYER)
                return;

            timeInterval += diff;
            if (timeInterval < 1000)
                return;

            if (Creature* tempSumm = caster->SummonCreature(WORLD_TRIGGER, at->GetPosition(), TEMPSUMMON_TIMED_DESPAWN, 200ms))
            {
                tempSumm->SetFaction(caster->GetFaction());
                tempSumm->SetOwnerGUID(caster->GetGUID());
                PhasingHandler::InheritPhaseShift(tempSumm, caster);
                caster->CastSpell(tempSumm, SPELL_MAGE_BLIZZARD_DAMAGE, true);
            }

            timeInterval -= 1000;
        }
    };

    AreaTriggerAI* GetAI(AreaTrigger* areatrigger) const override
    {
        return new at_mage_blizzardAI(areatrigger);
    }
};

// Rune of Power - 116011
// AreaTriggerID - 2947
struct at_mage_rune_of_power : AreaTriggerAI
{
    at_mage_rune_of_power(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger) { }

    enum UsingSpells
    {
        SPELL_MAGE_RUNE_OF_POWER_AURA = 116014
    };

    void OnCreate() override
    {
        at->SetXSpellVisualID(25943);
    }

    void OnUnitEnter(Unit* unit) override
    {
        if (Unit* caster = at->GetCaster())
            if (unit->GetGUID() == caster->GetGUID())
                caster->CastSpell(unit, SPELL_MAGE_RUNE_OF_POWER_AURA, true);
    }

    void OnUnitExit(Unit* unit) override
    {
        // todo: check for other rune of powers on the ground
        if (unit->HasAura(SPELL_MAGE_RUNE_OF_POWER_AURA))
            unit->RemoveAurasDueToSpell(SPELL_MAGE_RUNE_OF_POWER_AURA);
    }
};

// Frozen Orb - 84714
// AreaTriggerID - 8661 / 8800
struct at_mage_frozen_orb : AreaTriggerAI
{
    at_mage_frozen_orb(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger)
    {
        damageInterval = 100;
    }

    uint32 damageInterval;
    bool procDone = false;

    void OnInitialize() override
    {
        Unit* caster = at->GetCaster();
        if (!caster)
            return;

		if (!caster->HasAura(SPELL_MAGE_CONCENTRATED_COLDNESS))
		{
			Position pos = caster->GetPosition();

            at->MovePositionToFirstCollision(pos, 40.0f, 0.0f);
            at->SetDestination(pos, 4000);
        }
    }

    void OnCreate() override
    {
        at->SetXSpellVisualID(40291);
    }

    void OnUpdate(uint32 diff) override
    {
        Unit* caster = at->GetCaster();
        if (!caster || !caster->IsPlayer())
            return;

        if (damageInterval <= diff)
        {
            if (!procDone)
            {
                for (ObjectGuid guid : at->GetInsideUnits())
                {
                    if (Unit* unit = ObjectAccessor::GetUnit(*caster, guid))
                    {
                        if (caster->IsValidAttackTarget(unit))
                        {
                            if (caster->HasAura(SPELL_MAGE_FINGERS_OF_FROST_AURA))
                                caster->CastSpell(caster, SPELL_MAGE_FINGERS_OF_FROST_VISUAL_UI, true);

                            caster->CastSpell(caster, SPELL_MAGE_FINGERS_OF_FROST_AURA, true);

                            at->UpdateTimeToTarget(8000);
                            procDone = true;
                            break;
                        }
                    }
                }
            }

            caster->CastSpell(at->GetPosition(), SPELL_MAGE_FROZEN_ORB_DAMAGE, true);
            damageInterval = 100; // custom
        }
        else
            damageInterval -= diff;
    }
};

// Arcane Orb - 153626
// AreaTriggerID - 1612
struct at_mage_arcane_orb : AreaTriggerAI
{
    at_mage_arcane_orb(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger) { }

    void OnUnitEnter(Unit* unit) override
    {
        if (Unit* caster = at->GetCaster())
            if (caster->IsValidAttackTarget(unit))
                caster->CastSpell(unit, SPELL_MAGE_ARCANE_ORB_DAMAGE, true);
    }
};

// 31216 - Mirror Image
class npc_mirror_image : public CreatureScript
{
public:
    npc_mirror_image() : CreatureScript("npc_mirror_image") { }

    enum eSpells
    {
        SPELL_MAGE_FROSTBOLT        = 59638,
        SPELL_MAGE_FIREBALL         = 133,
        SPELL_MAGE_ARCANE_BLAST     = 30451,
        SPELL_MAGE_GLYPH            = 63093,
        SPELL_INITIALIZE_IMAGES     = 102284,
        SPELL_CLONE_CASTER          = 45204, // changed to clone me 9.2.0.43345
        SPELL_INHERIT_MASTER_THREAT = 58838, // good 9.2.0.43345 - sent after spawn
        SpellMirrorImage252212      = 252212, // casted after threat list
        SpellMirrorImage252217      = 252217, // called after last
    };

    struct npc_mirror_imageAI : CasterAI
    {
        npc_mirror_imageAI(Creature* creature) : CasterAI(creature) { }

        EventMap events;

        void IsSummonedBy(WorldObject* o) override
        {
            if (!o || !o->IsPlayer())
                return;

            auto owner = o->ToPlayer();

            //if (!me->HasUnitState(UnitState::UNIT_STATE_FOLLOW))
            //{
            //    me->GetMotionMaster()->Clear();
            //    me->GetMotionMaster()->MoveFollow(owner, PET_FOLLOW_DIST, me->GetFollowAngle(), MovementSlot::MOTION_SLOT_ACTIVE);
            //}

            me->SetMaxPower(me->GetPowerType(), owner->GetMaxPower(me->GetPowerType()));
            me->SetFullPower(me->GetPowerType());
            me->SetMaxHealth(owner->GetMaxHealth());
            me->SetHealth(owner->GetHealth());
            me->SetReactState(ReactStates::REACT_DEFENSIVE);
            me->SetSpeed(MOVE_RUN, owner->GetSpeed(MOVE_RUN));

            me->CastSpell(owner, SPELL_INHERIT_MASTER_THREAT, true); // cast flags 10, ex: 1048576
            me->CastSpell(owner, SpellMirrorImage252212, true); // cast flags 10, ex: 1048576
            me->CastSpell(owner, SpellMirrorImage252217, true); // cast flags 10, ex: 1048576

            // here mirror image casts on summoner spell (not present in client dbc) 49866
            // here should be auras (not present in client dbc): 35657, 35658, 35659, 35660 selfcasted by mirror images (stats related?)

            for (uint32 attackType = 0; attackType < WeaponAttackType::MAX_ATTACK; ++attackType)
            {
                WeaponAttackType attackTypeEnum = static_cast<WeaponAttackType>(attackType);
                me->SetBaseWeaponDamage(attackTypeEnum, WeaponDamageRange::MAXDAMAGE, owner->GetWeaponDamageRange(attackTypeEnum, WeaponDamageRange::MAXDAMAGE));
                me->SetBaseWeaponDamage(attackTypeEnum, WeaponDamageRange::MINDAMAGE, owner->GetWeaponDamageRange(attackTypeEnum, WeaponDamageRange::MINDAMAGE));
            }

            me->UpdateAttackPowerAndDamage();
        }

        void JustEngagedWith(Unit* /*who*/) override
        {
            Unit* owner = me->GetOwner();
            if (!owner)
                return;

            Player* ownerPlayer = owner->ToPlayer();
            if (!ownerPlayer)
                return;

            eSpells spellId = eSpells::SPELL_MAGE_FROSTBOLT;
            switch (ownerPlayer->GetSpecializationId())
            {
                case TALENT_SPEC_MAGE_ARCANE:
                    spellId = eSpells::SPELL_MAGE_ARCANE_BLAST;
                    break;
                case TALENT_SPEC_MAGE_FIRE:
                    spellId = eSpells::SPELL_MAGE_FIREBALL;
                    break;
                default:
                    break;
            }

            events.ScheduleEvent(spellId, 10ms); ///< Schedule cast
            me->GetMotionMaster()->Clear();
        }

        void EnterEvadeMode(EvadeReason /*reason*/) override
        {
            if (me->IsInEvadeMode() || !me->IsAlive())
                return;

            Unit* owner = me->GetOwner();

            me->CombatStop(true);
            if (owner && !me->HasUnitState(UNIT_STATE_FOLLOW))
            {
                me->GetMotionMaster()->Clear();
                me->GetMotionMaster()->MoveFollow(owner, PET_FOLLOW_DIST, me->GetFollowAngle(), MovementSlot::MOTION_SLOT_ACTIVE);
            }
        }

        void Reset() override
        {
            if (Unit* owner = me->GetOwner())
            {
                owner->CastSpell(me, SPELL_INITIALIZE_IMAGES, true);
                owner->CastSpell(me, SPELL_CLONE_CASTER, true);
            }
        }

        bool CanAIAttack(Unit const* target) const override
        {
            /// Am I supposed to attack this target? (ie. do not attack polymorphed target)
            return target && !target->HasBreakableByDamageCrowdControlAura();
        }

        void UpdateAI(uint32 diff) override
        {
            events.Update(diff);

            Unit* l_Victim = me->GetVictim();
            if (l_Victim)
            {
                if (CanAIAttack(l_Victim))
                {
                    /// If not already casting, cast! ("I'm a cast machine")
                    if (!me->HasUnitState(UNIT_STATE_CASTING))
                    {
                        if (uint32 spellId = events.ExecuteEvent())
                        {
                            DoCast(spellId);
                            Milliseconds castTime = Milliseconds(me->GetCurrentSpellCastTime(spellId));
                            events.ScheduleEvent(spellId, (castTime > 0ms ? castTime : 500ms) + Milliseconds(sSpellMgr->GetSpellInfo(spellId)->ProcCooldown));
                        }
                    }
                }
                else
                {
                    /// My victim has changed state, I shouldn't attack it anymore
                    if (me->HasUnitState(UNIT_STATE_CASTING))
                        me->CastStop();

                    me->AI()->EnterEvadeMode();
                }
            }
            else
            {
                /// Let's choose a new target
                Unit* target = me->SelectVictim();
                if (!target)
                {
                    /// No target? Let's see if our owner has a better target for us
                    if (Unit* owner = me->GetOwner())
                    {
                        Unit* ownerVictim = owner->GetVictim();
                        if (ownerVictim && me->CanCreatureAttack(ownerVictim))
                            target = ownerVictim;
                    }
                }

                if (target)
                    me->AI()->AttackStart(target);
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_mirror_imageAI(creature);
    }
};

// Flame Patch
// AreaTriggerID - 10801
struct at_mage_flame_patch : AreaTriggerAI
{
    at_mage_flame_patch(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger) { }


    void OnCreate() override
    {
        Unit* caster = at->GetCaster();
        if (!caster)
            timeInterval = 1000;
        else
        {
            timeInterval = 100; // custom HASTE
        }
    }

    int32 timeInterval;

    void OnUpdate(uint32 diff) override
    {
        Unit* caster = at->GetCaster();

        if (!caster)
            return;

        if (caster->GetTypeId() != TYPEID_PLAYER)
            return;

        timeInterval += diff;
        if (timeInterval < 100)
            return;

        caster->CastSpell(at->GetPosition(), SPELL_MAGE_FLAME_PATCH_AOE_DMG, true);

        timeInterval -= 100;
    }
};

// Cinderstorm - 198929
// AreaTriggerID - 10194
struct at_mage_cinderstorm : AreaTriggerAI
{
    at_mage_cinderstorm(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger) { }

    void OnUnitEnter(Unit* unit) override
    {
        if (Unit* caster = at->GetCaster())
            if (caster->IsValidAttackTarget(unit))
                caster->CastSpell(unit, SPELL_MAGE_CINDERSTORM_DMG, true);
    }
};

// Cinderstorm - 198928
class spell_mage_cinderstorm : public SpellScript
{
    PrepareSpellScript(spell_mage_cinderstorm);

    void HandleDamage(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        if (target->HasAura(SPELL_MAGE_IGNITE_DOT))
        {
            int32 pct = sSpellMgr->GetSpellInfo(SPELL_MAGE_CINDERSTORM)->GetEffect(EFFECT_0).CalcValue(caster);
            int32 dmg = GetHitDamage();
            AddPct(dmg, pct);
            SetHitDamage(dmg);
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_mage_cinderstorm::HandleDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

//Scorch 2948 Last Update 8.0.1 Build 28153
class spell_mage_scorch : public SpellScript
{
    PrepareSpellScript(spell_mage_scorch);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_MAGE_SEARING_TOUCH });
    }

    void HandleCritChance(Unit const* victim, float& chance)
    {
        if (Unit* caster = GetCaster())
            if (caster->HasAura(SPELL_MAGE_SEARING_TOUCH))
                if (victim && victim->HealthBelowPct(sSpellMgr->GetSpellInfo(SPELL_MAGE_SEARING_TOUCH)->GetEffect(EFFECT_0).BasePoints))
                    chance = 100.f;
    }

    void HandleDamage(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        if (caster->HasAura(SPELL_MAGE_SEARING_TOUCH))
        {
            if (target->HealthBelowPct(sSpellMgr->GetSpellInfo(SPELL_MAGE_SEARING_TOUCH)->GetEffect(EFFECT_0).BasePoints))
            {
                int32 pct = sSpellMgr->GetSpellInfo(SPELL_MAGE_SEARING_TOUCH)->GetEffect(EFFECT_1).BasePoints;
                int32 dmg = GetHitDamage();
                AddPct(dmg, pct);
                SetHitDamage(dmg);
            }
        }
    }

    void Register() override
    {
        OnCalcCritChance += SpellOnCalcCritChanceFn(spell_mage_scorch::HandleCritChance);
        OnEffectHitTarget += SpellEffectFn(spell_mage_scorch::HandleDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

class spell_mage_greater_pyro : public SpellScript
{
    PrepareSpellScript(spell_mage_greater_pyro);

    void HandleDamage(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        int32 pct = (target->GetMaxHealth() / 100) * 35;
        int32 dmg = GetHitDamage();
        AddPct(dmg, pct);
        SetHitDamage(dmg);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_mage_greater_pyro::HandleDamage, EFFECT_0, SPELL_EFFECT_DAMAGE_FROM_MAX_HEALTH_PCT);
    }
};

class spell_mage_ebonbolt : public SpellScript
{
    PrepareSpellScript(spell_mage_ebonbolt);

    void HandleDamage(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        caster->CastSpell(target, 257538, true);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_mage_ebonbolt::HandleDamage, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

class spell_mage_conf_damage : public AuraScript
{
    PrepareAuraScript(spell_mage_conf_damage);

    void OnTick(AuraEffect const* /*auraEff*/)
    {
        Unit* target = GetTarget();
        Unit* caster = GetCaster();
        if (!target || !caster)
            return;

        if (target->HasAura(SPELL_MAGE_IGNITE_DOT) || target->HasAura(226757))
        {
            if (roll_chance_i(10))
                caster->CastSpell(target, 205345, true);
        }

    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_mage_conf_damage::OnTick, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE);
    }
};

// 257541 - Phoenix Flames Last Update 8.0.1 Build 28153
class spell_mage_phoenix_flames : public SpellScript
{
    PrepareSpellScript(spell_mage_phoenix_flames);

    void HandleCritChance(Unit const* victim, float& chance)
    {
        chance = 100.f;
    }

    void HandleHit(SpellEffIndex effIndex)
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();

        if (!caster || !target)
            return;

        caster->Variables.Set("PhoenixFlameMainTarget", target->GetGUID());
        caster->CastSpell(target, SPELL_MAGE_PHOENIX_FLAMES_AOE, true);
    }

    void Register() override
    {
        OnCalcCritChance += SpellOnCalcCritChanceFn(spell_mage_phoenix_flames::HandleCritChance);
        OnEffectHitTarget += SpellEffectFn(spell_mage_phoenix_flames::HandleHit, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

// 257542 - Phoenix Flames AOE Last Update 8.0.1 Build 28153
class spell_mage_phoenix_flames_aoe : public SpellScript
{
    PrepareSpellScript(spell_mage_phoenix_flames_aoe);

    void HandleCritChance(Unit const* victim, float& chance)
    {
        chance = 100.f;
    }

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        if (Unit* caster = GetCaster())
            if (caster->Variables.Exist("PhoenixFlameMainTarget"))
                targets.remove(ObjectAccessor::GetUnit(*caster, caster->Variables.GetValue<ObjectGuid>("PhoenixFlameMainTarget")));
    }

    void Register() override
    {
        OnCalcCritChance += SpellOnCalcCritChanceFn(spell_mage_phoenix_flames_aoe::HandleCritChance);
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_mage_phoenix_flames_aoe::FilterTargets, EFFECT_1, TARGET_UNIT_DEST_AREA_ENEMY);
    }
};

// 210126 - Arcane Familiar - Mana
class spell_mage_arcane_familiar_mana : public AuraScript
{
    PrepareAuraScript(spell_mage_arcane_familiar_mana);

    void HandleRemove(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        if (Unit* caster = GetCaster())
            caster->RemoveAura(SPELL_MAGE_ARCANE_FAMILIAR);
    }

    void Register() override
    {
        OnEffectRemove += AuraEffectRemoveFn(spell_mage_arcane_familiar_mana::HandleRemove, EFFECT_0, 178, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
    }
};

// 205022 - Arcane Familiar
class spell_mage_arcane_familiar : public AuraScript
{
    PrepareAuraScript(spell_mage_arcane_familiar);

    void HandleRemove(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        if (Unit* caster = GetCaster())
            caster->RemoveAura(SPELL_MAGE_ARCANE_FAMILIAR_MANA);
    }

    void HandleUpdate(uint32 diff)
    {
        if (Unit* caster = GetCaster())
        {
            uint32 baseCastTime = 2500;
            if (shotTimer >= CalculatePct(baseCastTime, 100 - caster->m_unitData->ModHasteRegen))
            {
                Unit* target = ObjectAccessor::GetUnit(*caster, caster->GetTarget());
                if (target && caster->IsValidAttackTarget(target) && caster->IsInCombat() && !caster->HasInvisibilityAura() && !caster->HasStealthAura())
                {
                    caster->CastSpell(target, SPELL_MAGE_ARCANE_ASSAULT, true);
                    shotTimer = 0;
                }
                else
                    shotTimer = 0;
            }
            else
                shotTimer += diff;
        }
    }

    void Register() override
    {
        OnAuraUpdate += AuraUpdateFn(spell_mage_arcane_familiar::HandleUpdate);
        OnEffectRemove += AuraEffectRemoveFn(spell_mage_arcane_familiar::HandleRemove, EFFECT_1, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
    }

private:
    uint32 shotTimer = 0;
};

// 210725 Touc of the magi aura
class aura_mage_touch_of_the_magi_aura : public AuraScript
{
    PrepareAuraScript(aura_mage_touch_of_the_magi_aura);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == SPELL_MAGE_ARCANE_BLAST)
            return true;

        return false;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_mage_touch_of_the_magi_aura::CheckProc);
    }
};

// 210824 - Touch of the magi
//Last Update 8.0.1 Build 28153
class aura_mage_touch_of_the_magi : public AuraScript
{
    PrepareAuraScript(aura_mage_touch_of_the_magi);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (Unit* caster = GetCaster())
            if (eventInfo.GetDamageInfo() && eventInfo.GetDamageInfo()->GetAttacker()->GetGUID() == caster->GetGUID() && eventInfo.GetDamageInfo()->GetDamage() > 0)
                return true;

        return false;
    }

    uint32 damage = 0;

    void HandleProc(ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();
        Unit* owner = GetUnitOwner();
        if (!caster || !owner)
            return;

        damage += CalculatePct(eventInfo.GetDamageInfo()->GetDamage(), sSpellMgr->GetSpellInfo(SPELL_MAGE_TOUCH_OF_THE_MAGI)->GetEffect(EFFECT_0).BasePoints);
        if (AuraApplication* app = owner->GetAuraApplication(SPELL_MAGE_TOUCH_OF_THE_MAGI_DEBUFF, caster->GetGUID()))
            app->GetBase()->GetEffect(EFFECT_0)->ChangeAmount(damage);
    }

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetUnitOwner();
        if (!caster || !target)
            return;

        caster->CastCustomSpell(SPELL_MAGE_TOUCH_OF_THE_MAGI_DAMAGE, SPELLVALUE_BASE_POINT0, damage, target, true);
        damage = 0;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_mage_touch_of_the_magi::CheckProc);
        OnProc += AuraProcFn(aura_mage_touch_of_the_magi::HandleProc);
        OnEffectRemove += AuraEffectRemoveFn(aura_mage_touch_of_the_magi::HandleRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

// 270233 - Freezing Rain
class aura_mage_freezing_rain : public AuraScript
{
    PrepareAuraScript(aura_mage_freezing_rain);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_mage_freezing_rain::CheckProc);
    }
};

// 210805 - Time Anomaly
class aura_mage_time_anomaly : public AuraScript
{
    PrepareAuraScript(aura_mage_time_anomaly);

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
        if (Unit* caster = GetCaster())
        {
            // 6% chance to cause TA
            if (!roll_chance_i(6))
                return;

            // Try to apply a random effect. This will fail under some conditions.
            uint32 spell = 0;    // Zero means energize.
            uint8 chance = (uint8)rand_chance();
            if (chance > 0 && chance <= 30)
                spell = SPELL_MAGE_EVOCATION;
            if (chance > 31 && chance <= 60)
                spell = SPELL_MAGE_ARCANE_POWER;

            if (spell == SPELL_MAGE_EVOCATION && !caster->HasAura(SPELL_MAGE_EVOCATION))
            {
                caster->CastSpell(caster, SPELL_MAGE_TIME_ANOMALY, true);
                caster->AddAura(SPELL_MAGE_EVOCATION);
                if (Aura* aura = caster->GetAura(SPELL_MAGE_EVOCATION))
                    aura->SetDuration(sSpellMgr->GetSpellInfo(SPELL_MAGE_TIME_ANOMALY_TALENT)->GetEffect(EFFECT_1).BasePoints * IN_MILLISECONDS);
            }
            else if (spell == SPELL_MAGE_ARCANE_POWER && !caster->HasAura(SPELL_MAGE_ARCANE_POWER))
            {
                caster->CastSpell(caster, SPELL_MAGE_TIME_ANOMALY, true);
                caster->AddAura(SPELL_MAGE_ARCANE_POWER);
                if (Aura* aura = caster->GetAura(SPELL_MAGE_ARCANE_POWER))
                    aura->SetDuration(sSpellMgr->GetSpellInfo(SPELL_MAGE_TIME_ANOMALY_TALENT)->GetEffect(EFFECT_0).BasePoints * IN_MILLISECONDS);
            }
            else if (spell == 0 && caster->GetPower(POWER_ARCANE_CHARGES) < 4)
            {
                caster->CastSpell(caster, SPELL_MAGE_TIME_ANOMALY, true);
                caster->SetPower(POWER_ARCANE_CHARGES, 4);
            }
        }
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(aura_mage_time_anomaly::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

// 114923 - Nether Tempest
//Last Update 8.0.1 Build 28153
class aura_mage_nether_tempest : public AuraScript
{
    PrepareAuraScript(aura_mage_nether_tempest);

    void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Unit* caster = GetCaster();
        if (!caster)
            return;

        if (Aura* aura = caster->GetAura(AURA_ARCANIC_CHARGE))
            if (AuraEffect* aurEff = GetAura()->GetEffect(EFFECT_0))
                aurEff->SetDamage(aurEff->GetDamage() + CalculatePct(aurEff->GetDamage(), aura->GetStackAmount() * sSpellMgr->GetSpellInfo(AURA_ARCANIC_CHARGE)->GetEffect(EFFECT_0).BasePoints));
    }

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetUnitOwner();
        if (!caster || !target)
            return;

        GetAura()->RecalculateAmountOfEffects();
        target->CastSpell(target, SPELL_MAGE_NETHER_TEMPEST_AREA_EFFECT, true);
        caster->CastSpell(target, SPELL_MAGE_NETHER_TEMPEST_DAMAGE, true);       
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(aura_mage_nether_tempest::OnApply, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
        OnEffectPeriodic += AuraEffectPeriodicFn(aura_mage_nether_tempest::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE);
    }
};

// 114954 - Nether Tempest AOE Damage
//Last Update 8.0.1 Build 28153
class spell_mage_nether_tempest_aoe_damage : public SpellScript
{
    PrepareSpellScript(spell_mage_nether_tempest_aoe_damage);

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        if (Unit* caster = GetCaster())
        {
            targets.remove_if([caster](WorldObject* object)
            {
                if (!object->ToUnit())
                    return true;

                if (!caster->IsValidAttackTarget(object->ToUnit()))
                    return true;

                if (object->ToUnit()->HasAura(SPELL_MAGE_NETHER_STORM, caster->GetGUID()))
                    return true;

                return false;
            });
        }
    }

    void HandleHitDamage(SpellEffIndex /*effIndex*/)
    {
        if (Unit* caster = GetCaster())
        {
            if (Aura* aura = caster->GetAura(AURA_ARCANIC_CHARGE))
            {
                int32 damage = GetHitDamage();
                SetHitDamage(damage + CalculatePct(damage, aura->GetStackAmount() * sSpellMgr->GetSpellInfo(AURA_ARCANIC_CHARGE)->GetEffect(EFFECT_0).BasePoints));
            }
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_mage_nether_tempest_aoe_damage::HandleHitDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_mage_nether_tempest_aoe_damage::FilterTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ENEMY);
    }
};

// 257537 - Ebonbolt
//Last Update 8.0.1 Build 28153
class spell_mage_embolt : public SpellScript
{
    PrepareSpellScript(spell_mage_embolt);

    void HandleAfterCast()
    {
        if (Unit* caster = GetCaster())
            if (caster->HasAura(SPELL_MAGE_BRAIN_FREEZE) || caster->HasAura(SPELL_MAGE_BRAIN_FREEZE_IMPROVED))
                caster->CastSpell(caster, SPELL_MAGE_BRAIN_FREEZE_AURA, true);
    }

    void Register() override
    {
        AfterCast += SpellCastFn(spell_mage_embolt::HandleAfterCast);
    }
};

// 206431 - Burst of Cold
class aura_mage_burst_of_cold : public AuraScript
{
    PrepareAuraScript(aura_mage_burst_of_cold);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == SPELL_MAGE_FROST_NOVA)
            return true;

        return false;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_mage_burst_of_cold::CheckProc);
    }
};

// 206432 - Burst of Cold Aura
class spell_mage_burst_of_cold : public SpellScript
{
    PrepareSpellScript(spell_mage_burst_of_cold);

    void HandleHit()
    {
        if (Unit* caster = GetCaster())
            caster->GetSpellHistory()->ResetCooldown(SPELL_MAGE_CONE_OF_COLD, true);
    }

    void Register() override
    {
        OnHit += SpellHitFn(spell_mage_burst_of_cold::HandleHit);
    }
};

// 212799 - Displacement Beacon Aura
class aura_mage_displacement_beacon_aura : public AuraScript
{
    PrepareAuraScript(aura_mage_displacement_beacon_aura);

    void HandleApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes mode)
    {
        if (Unit* caster = GetCaster())
            caster->CastSpell(caster, SPELL_MAGE_DISPLACEMENT_AURA, true);
    }

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes mode)
    {
        if (Unit* caster = GetCaster())
            caster->RemoveAura(SPELL_MAGE_DISPLACEMENT_AURA);
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(aura_mage_displacement_beacon_aura::HandleApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
        OnEffectRemove += AuraEffectRemoveFn(aura_mage_displacement_beacon_aura::HandleRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
    }
};

// 198064 - Prismatic Cloak
class aura_mage_prismatic_clock : public AuraScript
{
    PrepareAuraScript(aura_mage_prismatic_clock);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetSpellInfo() && (eventInfo.GetSpellInfo()->Id == SPELL_MAGE_BLINK || eventInfo.GetSpellInfo()->Id == SPELL_MAGE_SHIMMER))
            return true;

        return false;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_mage_prismatic_clock::CheckProc);
    }
};

// 276743 - Clearcasting PVP
class aura_mage_clearcasting_pvp : public AuraScript
{
    PrepareAuraScript(aura_mage_clearcasting_pvp);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == SPELL_MAGE_ARCANE_MISSILES)
            return true;

        return false;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();
        if (Unit* caster = GetCaster())
            if (Aura* aura = caster->GetAura(SPELL_MAGE_CLEARCASTING_PVP_STACK_EFFECT))
                aura->ModStackAmount(-1);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_mage_clearcasting_pvp::CheckProc);
        OnProc += AuraProcFn(aura_mage_clearcasting_pvp::HandleProc);
    }
};

// 110960 - Greater Invisibility
class aura_mage_greater_invisibility : public AuraScript
{
    PrepareAuraScript(aura_mage_greater_invisibility);

    void HandleApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes mode)
    {
        if (Unit* caster = GetCaster())
            caster->CastSpell(caster, SPELL_MAGE_GREATER_INVISIBILITY_BUFF, true);
    }

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes mode)
    {
        if (Unit* caster = GetCaster())
            if (Aura* aura = caster->GetAura(SPELL_MAGE_GREATER_INVISIBILITY_BUFF))
                aura->SetDuration(3 * IN_MILLISECONDS);
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(aura_mage_greater_invisibility::HandleApply, EFFECT_1, SPELL_AURA_MOD_INVISIBILITY, AURA_EFFECT_HANDLE_REAL);
        OnEffectRemove += AuraEffectRemoveFn(aura_mage_greater_invisibility::HandleRemove, EFFECT_1, SPELL_AURA_MOD_INVISIBILITY, AURA_EFFECT_HANDLE_REAL);
    }
};

// 198111 - Temporal Shield
class aura_mage_temporal_shield : public AuraScript
{
    PrepareAuraScript(aura_mage_temporal_shield);

    uint32 temporalDamage = 0;

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetDamageInfo() && eventInfo.GetDamageInfo()->GetDamage() > 0)
            temporalDamage += eventInfo.GetDamageInfo()->GetDamage();
    }

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes mode)
    {
        if (Unit* caster = GetCaster())
        {
            caster->CastCustomSpell(SPELL_MAGE_TEMPORAL_RIPPLES, SPELLVALUE_BASE_POINT0, temporalDamage, caster, true);
            temporalDamage = 0;
        }
    }

    void Register() override
    {
        OnProc += AuraProcFn(aura_mage_temporal_shield::HandleProc);
        OnEffectRemove += AuraEffectRemoveFn(aura_mage_temporal_shield::HandleRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

// 122 - Frost Nova
class aura_mage_frost_nova : public AuraScript
{
    PrepareAuraScript(aura_mage_frost_nova);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetDamageInfo() && (eventInfo.GetDamageInfo()->GetDamageType() != HEAL && eventInfo.GetDamageInfo()->GetDamageType() != NODAMAGE))
        {

            Unit* caster = GetCaster();
            Unit* target = GetTarget();
            if (!caster || !target)
                return false;

            Aura* aura = GetAura();

            // Freeze will be removed if the damage if greater or equal to 10% of the target maximun health.
            uint32 ten = CalculatePct(target->GetMaxHealth(), 10);
            if (eventInfo.GetDamageInfo()->GetDamage() >= ten)
                return true;

            // We need to "save" the amount of damage.
            if (aura->Variables.Exist("DAMAGE"))
            {
                uint32 currentDamage = aura->Variables.GetValue<uint32>("DAMAGE");
                uint32 newDamage = currentDamage + eventInfo.GetDamageInfo()->GetDamage();
                aura->Variables.Set<uint32>("DAMAGE", newDamage);
                if (newDamage >= ten)
                    return true;
            }
            else
                aura->Variables.Set<uint32>("DAMAGE", eventInfo.GetDamageInfo()->GetDamage());
        }

        return false;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (WorldObject* owner = GetOwner())
            if (owner->ToUnit())
                owner->ToUnit()->RemoveAura(SPELL_MAGE_FROST_NOVA);
    }

    void HandleRemove(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
    {
        Unit* caster = GetCaster();
        Unit* owner = GetUnitOwner();
        if (!caster || !owner)
            return;

        if (caster->HasAura(SPELL_MAGE_CHILLED_TO_THE_BONE))
        {
            if (GetTargetApplication()->GetRemoveMode() == AURA_REMOVE_BY_DEATH)
                return;

            int32 baseDamage = caster->GetTotalSpellPowerValue(SPELL_SCHOOL_MASK_FROST, false);
            if (GetTargetApplication()->GetRemoveMode() == AURA_REMOVE_BY_ENEMY_SPELL)
                caster->CastCustomSpell(SPELL_MAGE_CHILLED_TO_THE_BONE_DAMAGE, SPELLVALUE_BASE_POINT0, baseDamage * 2, owner, true);
            else
                caster->CastSpell(owner, SPELL_MAGE_CHILLED_TO_THE_BONE_DAMAGE, true);
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_mage_frost_nova::CheckProc);
        OnProc += AuraProcFn(aura_mage_frost_nova::HandleProc);
        OnEffectRemove += AuraEffectApplyFn(aura_mage_frost_nova::HandleRemove, EFFECT_1, SPELL_AURA_MOD_ROOT_2, AURA_EFFECT_HANDLE_REAL);
    }
};

// 198120 - Frostbite Aura
// Last Update 8.0.1 Build 28153
class aura_mage_frostbite_aura: public AuraScript
{
    PrepareAuraScript(aura_mage_frostbite_aura);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetSpellInfo() && (eventInfo.GetSpellInfo()->Id == SPELL_MAGE_FROSTBOLT || eventInfo.GetSpellInfo()->Id == SPELL_MAGE_BLIZZARD_DAMAGE ||
            eventInfo.GetSpellInfo()->Id == SPELL_MAGE_FLURRY_DAMAGE || eventInfo.GetSpellInfo()->Id == SPELL_MAGE_CONE_OF_COLD ||
            eventInfo.GetSpellInfo()->Id == SPELL_MAGE_FROZEN_ORB_DAMAGE || eventInfo.GetSpellInfo()->Id == SPELL_MAGE_RAY_OF_FROST))
            return true;

        return false;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_mage_frostbite_aura::CheckProc);
    }
};

// 198121 - Frostbite
// Last Update 8.0.1 Build 28153
class aura_mage_frostbite : public AuraScript
{
    PrepareAuraScript(aura_mage_frostbite);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetDamageInfo())
            return false;

        Aura* aura = GetAura();
        int chance = 50;
        // Blizzard mech.
        if (aura && aura->GetDuration() / 1000 >= aura->GetMaxDuration() / 2000 && roll_chance_i(chance))
            return true;
        else if (aura && aura->GetDuration() / 1000 < aura->GetMaxDuration() / 2000)
        {
            uint32 chanceAdd = (aura->GetMaxDuration() / 2000 - aura->GetDuration() / 1000) * 5 + 5;
            chance += chanceAdd;
            if (roll_chance_i(chance))
                return true;
        }

        return false;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (WorldObject* owner = GetOwner())
            if (owner->ToUnit())
                owner->ToUnit()->RemoveAura(SPELL_MAGE_FROSTBITE);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_mage_frostbite::CheckProc);
        OnProc += AuraProcFn(aura_mage_frostbite::HandleProc);
    }
};

// 203284 - Flamecannon
class aura_mage_flamecannon : public AuraScript
{
    PrepareAuraScript(aura_mage_flamecannon);

    void HandleApply(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /* mode */)
    {
        if (Unit* caster = GetCaster())
            lastPosition = caster->GetPosition();
    }

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
        if (Unit* caster = GetCaster())
        {
            counter--;
            if (counter == 0)
            {
                counter = 2;
                if (caster->IsInCombat() && caster->GetPosition() == lastPosition)
                    caster->CastSpell(caster, SPELL_MAGE_FLAMECANNON_BUFF, true);
                lastPosition = caster->GetPosition();
            }
        }
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(aura_mage_flamecannon::HandleApply, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY, AURA_EFFECT_HANDLE_REAL);
        OnEffectPeriodic += AuraEffectPeriodicFn(aura_mage_flamecannon::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }

private:
    uint8 counter = 2;
    Position lastPosition;
};

// 44544 - Fingers of Frost
class aura_fingers_of_frost : public AuraScript
{
    PrepareAuraScript(aura_fingers_of_frost);

    void HandleApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* caster = GetCaster())
            if (Aura* aura = caster->GetAura(SPELL_MAGE_FINGERS_OF_FROST_AURA))
                if (aura->GetStackAmount() == 2)
                    caster->CastSpell(caster, SPELL_MAGE_FINGERS_OF_FROST_VISUAL_UI, true);
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(aura_fingers_of_frost::HandleApply, EFFECT_1, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
    }
};

// 31661 - Dragon's Breath
class aura_mage_dragon_breath : public AuraScript
{
    PrepareAuraScript(aura_mage_dragon_breath);

    void HandleProc(ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();
        Unit* target = GetTarget();
        if (!caster || !target)
            return;

        target->RemoveAura(SPELL_MAGE_DRAGON_BREATH, caster->GetGUID());
    }

    void Register() override
    {
        OnProc += AuraProcFn(aura_mage_dragon_breath::HandleProc);
    }
};

// 205024  - Lonely Winter
class spell_mage_lonely_winter : public AuraScript
{
    PrepareAuraScript(spell_mage_lonely_winter);

    void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Unit* caster = GetCaster();
        if (!caster)
            return;

        if (Creature* elemental = caster->GetGuardianPet())
            if (elemental->GetEntry() == NPC_WATER_ELEMENTAL)
                if (Player* player = caster->ToPlayer())
                    if (Pet* pet = elemental->ToPet())
                        player->RemovePet(pet, PET_SAVE_AS_DELETED);
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_mage_lonely_winter::OnApply, EFFECT_0, SPELL_AURA_ADD_PCT_MODIFIER, AURA_EFFECT_HANDLE_REAL);
    }
};

// ---------------
// AZERITE SPELLS
// ---------------
// 157981 - Blast Wave
class spell_mage_blast_wave : public SpellScript
{
    PrepareSpellScript(spell_mage_blast_wave);

    void HandleHitTarget(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        caster->CastSpell(target, SPELL_MAGE_BLAST_WAVE_KNOCKBACK, true);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_mage_blast_wave::HandleHitTarget, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

// 203275 - Tinder
class aura_mage_tinder : public AuraScript
{
    PrepareAuraScript(aura_mage_tinder);

    void HandleApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* caster = GetCaster())
            caster->CastSpell(caster, SPELL_MAGE_TINDER_BLOCK, true);
    }

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* caster = GetCaster())
        {
            caster->RemoveAura(SPELL_MAGE_TINDER_BLOCK);
            caster->RemoveAura(SPELL_MAGE_TINDER_INDICATOR);
        }
    }

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
        if (Unit* caster = GetCaster())
        {
            // Reset tick on Fireball
            if (caster->Variables.Exist("TINDER_RESET"))
            {
                tick = 0;
                caster->Variables.Remove("TINDER_RESET");
            }

            if (tick == 8)
            {
                caster->RemoveAura(SPELL_MAGE_TINDER_BLOCK);
                caster->CastSpell(caster, SPELL_MAGE_TINDER_INDICATOR, true);
                tick = 0;
            }
            else
                tick++;
        }
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(aura_mage_tinder::HandleApply, EFFECT_0, SPELL_AURA_ADD_PCT_MODIFIER, AURA_EFFECT_HANDLE_REAL);
        OnEffectRemove += AuraEffectRemoveFn(aura_mage_tinder::HandleRemove, EFFECT_0, SPELL_AURA_ADD_PCT_MODIFIER, AURA_EFFECT_HANDLE_REAL);
        OnEffectPeriodic += AuraEffectPeriodicFn(aura_mage_tinder::HandlePeriodic, EFFECT_2, SPELL_AURA_PERIODIC_DUMMY);
    }

private:
    uint8 tick = 0;
};

// 203286 Greater Pyroblast Update 8.0.1 Build 28153
class spell_mage_greater_pyroblast : public SpellScript
{
    PrepareSpellScript(spell_mage_greater_pyroblast);

    void HandleTargetHit(SpellEffIndex effIndex)
    {
        Unit* hitTarget = GetHitUnit();
        Unit* caster = GetCaster();
        if (!caster || !hitTarget)
            return;

        uint32 damage = 0;

        if (hitTarget->IsPlayer())
        {
            damage = CalculatePct(hitTarget->GetMaxHealth(), GetSpellInfo()->GetEffect(EFFECT_1).BasePoints);
            // Reduce the damage based on mod aura.
            int32 reduction = hitTarget->GetTotalAuraModifier(SPELL_AURA_MOD_DAMAGE_PERCENT_TAKEN);
            if (reduction < 0)
                damage -= CalculatePct(damage, std::abs(reduction));
        }
        else
            damage = CalculatePct(caster->GetMaxHealth(), GetSpellInfo()->GetEffect(EFFECT_1).BasePoints);

        SetHitDamage(damage);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_mage_greater_pyroblast::HandleTargetHit, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

// 228354 - Flurry Damage
class spell_mage_flurry_damage : public SpellScript
{
    PrepareSpellScript(spell_mage_flurry_damage);

    void HandleHit()
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        int32 damage = GetHitDamage();
        if (caster->Variables.GetValue<bool>("BRAIN_FREEZE"))
        {
            AddPct(damage, sSpellMgr->GetSpellInfo(SPELL_MAGE_BRAIN_FREEZE_AURA)->GetEffect(EFFECT_1).BasePoints);
            caster->CastSpell(target, SPELL_MAGE_FLURRY_CHILL_PROC, true);
        }

        SetHitDamage(damage);
    }

    void Register() override
    {
        OnHit += SpellHitFn(spell_mage_flurry_damage::HandleHit);
    }
};

// 190446 - Brain Freeze Aura
class aura_mage_brain_freeze_aura : public AuraScript
{
    PrepareAuraScript(aura_mage_brain_freeze_aura);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_mage_brain_freeze_aura::CheckProc);
    }
};

// 236788 - Dampened Magic
class aura_mage_dampened_magic : public AuraScript
{
    PrepareAuraScript(aura_mage_dampened_magic);

    void CalculateAmount(AuraEffect const* /*aurEff*/, int32& amount, bool& /*canBeRecalculated*/)
    {
        amount = -1;
    }

    void HandleAbsorb(AuraEffect* /*aurEff*/, DamageInfo& dmgInfo, uint32& absorbAmount)
    {
        if (dmgInfo.GetDamageType() != DOT)
            return;

        uint8 percent = sSpellMgr->GetSpellInfo(SPELL_MAGE_DAMPENED_MAGIC)->GetEffect(EFFECT_1).BasePoints;
        absorbAmount = CalculatePct(dmgInfo.GetDamage(), percent);
    }

    void Register() override
    {
        DoEffectCalcAmount += AuraEffectCalcAmountFn(aura_mage_dampened_magic::CalculateAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
        AfterEffectAbsorb += AuraEffectAbsorbFn(aura_mage_dampened_magic::HandleAbsorb, EFFECT_0);
    }
};

// 264774 - Rule of Threes Aura
class aura_mage_rule_of_threes_aura : public AuraScript
{
    PrepareAuraScript(aura_mage_rule_of_threes_aura);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_mage_rule_of_threes_aura::CheckProc);
    }
};

// 263725 - Clearcasting Proc
class aura_mage_clearcasting_proc : public AuraScript
{
    PrepareAuraScript(aura_mage_clearcasting_proc);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_mage_clearcasting_proc::CheckProc);
    }
};

// 203283 - Firestarter
// Last update 8.0.1 Build 28153
class aura_mage_firestarter_proc : public AuraScript
{
    PrepareAuraScript(aura_mage_firestarter_proc);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetSpellInfo()->Id == SPELL_MAGE_FIREBALL)
            return true;
        return false;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if(Unit* caster = GetCaster())
            caster->GetSpellHistory()->ModifyCooldown(SPELL_MAGE_COMBUSTION, -GetSpellInfo()->GetEffect(EFFECT_0).BasePoints * IN_MILLISECONDS);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_mage_firestarter_proc::CheckProc);
        OnProc += AuraProcFn(aura_mage_firestarter_proc::HandleProc);
    }
};

// 205027 - Bone Chilling
// Last update 8.0.1 Build 28153
class aura_bone_chilling : public AuraScript
{
    PrepareAuraScript(aura_bone_chilling);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetSpellInfo() && eventInfo.GetDamageInfo() && (eventInfo.GetSpellInfo()->Id == SPELL_MAGE_FROSTBOLT ||
            eventInfo.GetSpellInfo()->Id == SPELL_MAGE_BLIZZARD_DAMAGE || eventInfo.GetSpellInfo()->Id == SPELL_MAGE_FLURRY_DAMAGE ||
            eventInfo.GetSpellInfo()->Id == SPELL_MAGE_CONE_OF_COLD || eventInfo.GetSpellInfo()->Id == SPELL_MAGE_FROZEN_ORB_DAMAGE ||
            eventInfo.GetSpellInfo()->Id == SPELL_MAGE_RAY_OF_FROST))
            return true;

        return false;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_bone_chilling::CheckProc);
    }
};

// 205766 - Bone Chilling Aura
// Last update 8.0.1 Build 28153
class aura_bone_chilling_aura : public AuraScript
{
    PrepareAuraScript(aura_bone_chilling_aura);

    void HandleApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (Aura* aura = GetAura())
        {
            // Resets.
            for (auto effect : aura->GetAuraEffects())
                effect->SetAmount(aura->GetStackAmount());

            // Sets.
            for (auto effect : aura->GetAuraEffects())
                effect->SetDonePct(0.5f);
        }
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(aura_bone_chilling_aura::HandleApply, EFFECT_0, SPELL_AURA_ADD_PCT_MODIFIER, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
    }
};

// 157644 - Enhanced Pyrotechnics
class aura_mage_enhaced_pyrotechnics : public AuraScript
{
    PrepareAuraScript(aura_mage_enhaced_pyrotechnics);

    void HandleRemove(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /* mode */)
    {
        if (Unit* caster = GetCaster())
            if (caster->HasAura(SPELL_MAGE_FLAMES_OF_ALACRITY_AURA))
                caster->RemoveAura(SPELL_MAGE_FLAMES_OF_ALACRITY_AURA);
    }

    void Register() override
    {
        OnEffectRemove += AuraEffectRemoveFn(aura_mage_enhaced_pyrotechnics::HandleRemove, EFFECT_0, SPELL_AURA_ADD_FLAT_MODIFIER, AURA_EFFECT_HANDLE_REAL);
    }
};

// 314791 
class spell_mage_shifting_power : public AuraScript
{
    PrepareAuraScript(spell_mage_shifting_power);

    enum Shift
    {
        ShiftingPowerSpell = 325130,
        GroveInvigoration = 322721,
        RedirectedAnima = 342814,
    };

    // effect 3
    void HandleApply(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /* mode */)
    {
        PreventDefaultAction();

        if (!GetCaster())
            return;

        if (auto grove = GetCaster()->GetAura(GroveInvigoration))
        {
            if (auto anima = GetCaster()->GetAura(RedirectedAnima))
            {
                anima->ModStackAmount(6);
            }
            else
            {
                GetCaster()->CastSpell(GetCaster(), RedirectedAnima, true);
                if (auto anima = GetCaster()->GetAura(RedirectedAnima))
                    anima->ModStackAmount(5);
            }
        }
    }

    // 342373 Fae Tendrils
    // Shifting Power entangles enemies it hits, rooting them in place for $342373d.
    void OnTick(AuraEffect const* /*aurEff*/)
    {
        PreventDefaultAction();
    }

    void HandleUpdate(uint32 diff)
    {
        if (Unit* caster = GetCaster())
        {
            if (timer <= 0)
            {
                timer = 500;
                //caster->CastSpell(caster, 325130, true); - gonna let it scale with haste, will handle CDR part here
                auto spellHistory = caster->GetSpellHistory();
                // Need add conduit supp
                spellHistory->ReduceCooldowns([caster](SpellHistory::CooldownStorageType::iterator itr) -> bool
                {
                    SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(itr->first, DIFFICULTY_NONE);
                    Milliseconds remainingCooldown = caster->GetSpellHistory()->GetRemainingCooldown(spellInfo);

                    bool allow = spellInfo->SpellFamilyName == SPELLFAMILY_MAGE;

                    if (!allow)
                    {
                        switch (spellInfo->Id)
                        {
                            case 1953: // Blink
                            case 310143: // Soulshape

                                return true;
                            default:
                                return false;
                        }
                    }

                    return remainingCooldown > 0ms
                        && !itr->second.OnHold;
                }, 1000);
            }
            else
                timer -= diff;
        }
    }

    int32 timer = 0;

    void Register() override
    {
        //OnEffectApply += AuraEffectPeriodicFn(spell_mage_shifting_power::OnTick, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL, AURA_EFFECT_HANDLE_REAL);
        OnEffectApply += AuraEffectApplyFn(spell_mage_shifting_power::HandleApply, EFFECT_3, SPELL_AURA_PERIODIC_TRIGGER_SPELL, AURA_EFFECT_HANDLE_REAL);
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_mage_shifting_power::OnTick, EFFECT_3, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
        OnAuraUpdate += AuraUpdateFn(spell_mage_shifting_power::HandleUpdate);
    }
};

// Mastery: Ignite - 12846
class IgniteOrderPred
{
public:
    IgniteOrderPred(Unit const* base, bool ascending = true) : _ascending(ascending), _base(base) { }

    bool operator()(Unit const* objA, Unit const* objB) const
    {
        float valA = 0;
        float valB = 0;
        if (AuraEffect* eff = objA->GetAuraEffect(SPELL_MAGE_IGNITE_AURA, EFFECT_0, _base->GetGUID()))
            valA = eff->GetDamage();
        if (AuraEffect* eff = objB->GetAuraEffect(SPELL_MAGE_IGNITE_AURA, EFFECT_0, _base->GetGUID()))
            valB = eff->GetDamage();
        return _ascending ? valA < valB : valA > valB;
    }

private:
    bool const _ascending;
    Unit const* _base;
};

class spell_mage_mastery_ignite : public AuraScript
{
    PrepareAuraScript(spell_mage_mastery_ignite);

    void HandleEffectPeriodic(AuraEffect const* /*aurEff*/)
    {
        Unit* caster = GetCaster();
        if (!caster)
            return;

        float dist = INTERACTION_DISTANCE;
        std::list<Unit*> targetList;
        std::list<Unit*> targetsWithIgnite;
        std::list<Unit*> targetsWithouthIgnite;

        Trinity::AnyUnitInObjectRangeCheck check(caster, caster->GetVisibilityRange());
        Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(caster, targetList, check);
        Cell::VisitGridObjects(GetCaster(), searcher, caster->GetVisibilityRange());

        for (Unit* unit : targetList)
        {
            if (unit->IsTotem() || caster->IsFriendlyTo(unit))
                continue;

            if (unit->HasAura(SPELL_MAGE_IGNITE_AURA, caster->GetGUID()))
            {
                targetsWithIgnite.emplace_back(unit);
            }
            else
            {
                targetsWithouthIgnite.emplace_back(unit);
            }
        }
        for (Unit* igniter : targetsWithIgnite)
        {
            if (Aura* srcIgnite = igniter->GetAura(SPELL_MAGE_IGNITE_AURA, caster->GetGUID()))
            {
                std::list<Unit*> targetsToIgnite;
                std::list<Unit*> targetsToReIgnite;
                for (Unit* target : targetsWithouthIgnite)
                {
                    if (igniter->GetDistance(target) <= dist)
                    {
                        if (target->HasAura(SPELL_MAGE_IGNITE_AURA, caster->GetGUID()))
                            targetsToReIgnite.emplace_back(target);
                        else
                            targetsToIgnite.emplace_back(target);
                    }
                }
                Unit* target = nullptr;
                if (!targetsToIgnite.empty())
                {
                    Trinity::Containers::RandomResize(targetsToIgnite, 1);
                    target = targetsToIgnite.front();
                }
                else if (!targetsToReIgnite.empty())
                {
                    targetsToReIgnite.sort(IgniteOrderPred(caster));
                    target = targetsToReIgnite.front();
                }
                if (target)
                    if ((caster->HasAura(SPELL_MAGE_CONTROLLED_BURN) && caster->HasAura(SPELL_MAGE_COMBUSTION)) || !caster->HasAura(SPELL_MAGE_CONTROLLED_BURN))
                    {
                        // copy values of base dot
                        caster->CastSpell(target, SPELL_MAGE_IGNITE_AURA);
                        //caster->AddAura(SPELL_MAGE_IGNITE_AURA, target);
                        if (Aura* ignite = target->GetAura(SPELL_MAGE_IGNITE_AURA, caster->GetGUID()))
                        {
                            ignite->SetMaxDuration(srcIgnite->GetMaxDuration());
                            ignite->SetDuration(srcIgnite->GetDuration());
                            for (AuraEffect* eff : ignite->GetAuraEffects())
                            {
                                if (!eff)
                                    continue;
                                if (AuraEffect* baseEff = srcIgnite->GetEffect(eff->GetEffIndex()))
                                {
                                    eff->SetPeriodicTimer(baseEff->GetPeriodicTimer());
                                    eff->SetDamage(baseEff->GetDamage());
                                    eff->ChangeAmount(baseEff->GetAmount());
                                }
                            }
                        }
                    }
            }
        }
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_mage_mastery_ignite::HandleEffectPeriodic, EFFECT_2, SPELL_AURA_PERIODIC_DUMMY);
    }
};

//Update 8.0.1 Build 28153
// 12846 - Mastery : Ignite
// Called by Fireball - 133, Inferno Blast - 108853, Scorch - 2948, Pyroblast - 11366, Meteor - 153564, Flamestrike - 2120, Phoenix Flames - 257541
class spell_mastery_ignite : public SpellScriptLoader
{
public:
    spell_mastery_ignite() : SpellScriptLoader("spell_mastery_ignite") { }

    class spell_mastery_ignite_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_mastery_ignite_SpellScript);

        bool hotStreak = false;

        enum eSpell
        {
            SPELL_MAGE_HOT_STREAK = 48108,
            SPELL_MAGE_PYROBLAST = 11366,
            SPELL_MAGE_FLAMESTRIKE = 2120
        };

        void HandleBeforeCast()
        {
            if (Unit* caster = GetCaster())
            {
                SpellInfo const* spellInfo = GetSpellInfo();
                if (spellInfo && (spellInfo->Id == SPELL_MAGE_PYROBLAST || spellInfo->Id == SPELL_MAGE_FLAMESTRIKE))
                {
                    if (caster->HasAura(SPELL_MAGE_HOT_STREAK))
                        hotStreak = true;
                }
            }
        }

        void HandleAfterHit()
        {
            if (Unit* caster = GetCaster())
            {
                if (caster->IsPlayer())
                if (Unit* target = GetHitUnit())
                {
                    if (caster->GetTypeId() == TYPEID_PLAYER && caster->HasAura(SPELL_MAGE_IGNITE))
                    {
                        const SpellInfo* igniteAura = sSpellMgr->GetSpellInfo(SPELL_MAGE_IGNITE_AURA);
                        if (GetSpellInfo()->Id != SPELL_MAGE_IGNITE_AURA && igniteAura != nullptr)
                        {
                            float masteryValue = caster->ToPlayer()->m_activePlayerData->Mastery * (hotStreak ? 1.5f : 0.75f);
                            hotStreak = false;

                            int32 basePoints = GetHitDamage();// +GetAbsorbedDamage();
                            if (basePoints)
                            {
                                basePoints = int32(CalculatePct(basePoints, masteryValue));

                                if (igniteAura->GetEffect(EFFECT_0).ApplyAuraPeriod != 0)
                                    basePoints = basePoints / (igniteAura->GetMaxDuration() / igniteAura->GetEffect(EFFECT_0).ApplyAuraPeriod);

                                // rollover disabled, cause too op
                                //if (Aura* previousIgnite = target->GetAura(SPELL_MAGE_IGNITE_AURA, caster->GetGUID()))
                                //{
                                //    if (AuraEffect* igniteEffect = previousIgnite->GetEffect(EFFECT_0))
                                //    {
                                //        if (uint32 amplitude = igniteEffect->GetPeriod())
                                //            basePoints += (igniteEffect->GetAmount() * (previousIgnite->GetDuration() / amplitude)) / (previousIgnite->GetMaxDuration() / amplitude);
                                //    }
                                //}

                                caster->CastCustomSpell(target, SPELL_MAGE_IGNITE_AURA, &basePoints, NULL, NULL, true);
                            }
                        }
                    }
                }
            }
        }

        void Register() override
        {
            BeforeCast += SpellCastFn(spell_mastery_ignite_SpellScript::HandleBeforeCast);
            AfterHit += SpellHitFn(spell_mastery_ignite_SpellScript::HandleAfterHit);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_mastery_ignite_SpellScript();
    }
};


const int IcicleAuras[5] = { 214124, 214125, 214126, 214127, 214130 };
const int IcicleHits[5] = { 148017, 148018, 148019, 148020, 148021 };

// Mastery: Icicles - 76613
//Last Update 8.0.1 Build 28153
class spell_mastery_icicles_proc : public AuraScript
{
    PrepareAuraScript(spell_mastery_icicles_proc);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetDamageInfo() == nullptr)
            return false;
        if (eventInfo.GetSpellInfo() && (eventInfo.GetSpellInfo()->Id == SPELL_MAGE_FROSTBOLT || eventInfo.GetSpellInfo()->Id == SPELL_MAGE_FROSTBOLT_TRIGGER ||
            eventInfo.GetSpellInfo()->Id == SPELL_MAGE_FLURRY))
            return true;
        return false;
    }

    void OnProc(AuraEffect* /*aurEff*/, ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetDamageInfo() == nullptr)
            return;

        Unit* target = eventInfo.GetDamageInfo()->GetVictim();
        Unit* caster = eventInfo.GetDamageInfo()->GetAttacker();
        if (!target || !caster)
            return;

        Player* player = caster->ToPlayer();

        if (!player)
            return;

        // Calculate damage
        int32 hitDamage = eventInfo.GetDamageInfo()->GetDamage() + eventInfo.GetDamageInfo()->GetAbsorb();

        if (eventInfo.GetSpellInfo()->Id == SPELL_MAGE_FLURRY)
        {
            if (SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(SPELL_MAGE_FLURRY_DPS))
            {
                auto const& spellEffect = spellInfo->GetEffect(EFFECT_1);
                
                {
                    hitDamage = player->CalculateSpellDamage(target, spellEffect);
                    hitDamage = player->SpellDamageBonusDone(target, spellInfo, hitDamage, SPELL_DIRECT_DAMAGE, spellEffect);
                    hitDamage = target->SpellDamageBonusTaken(player, spellInfo, hitDamage, SPELL_DIRECT_DAMAGE);
                }
            }
        }

        // if hitDamage == 0 we have a miss, so we need to except this variant
        if (hitDamage != 0)
        {
            bool icilesAddSecond = false;

            if (caster->HasAura(SPELL_MAGE_ICE_NINE))
            {
                if (roll_chance_i(20))
                    icilesAddSecond = true;
            }

            hitDamage *= (player->m_activePlayerData->Mastery * 2.25f) / 100.0f;

            // Prevent huge hits on player after hitting low level creatures
            if (player->GetLevel() > target->GetLevel())
                hitDamage = std::min(int32(hitDamage), int32(target->GetMaxHealth()));

            // We need to get the first free icicle slot
            int8 icicleFreeSlot = -1; // -1 means no free slot
            int8 icicleSecondFreeSlot = -1; // -1 means no free slot
            for (int i = 0; i < 5; ++i)
            {
                if (!player->HasAura(IcicleAuras[i]))
                {
                    icicleFreeSlot = i;
                    if (icilesAddSecond)
                        icicleSecondFreeSlot = i + 1;
                    break;
                }
            }

            switch (icicleFreeSlot)
            {
            case -1:
            {
                // We need to find the icicle with the smallest duration.
                int8 smallestIcicle = 0;
                int32 minDuration = 0xFFFFFF;
                for (int8 i = 0; i < 5; i++)
                {
                    if (Aura* tmpCurrentAura = player->GetAura(IcicleAuras[i]))
                    {
                        if (minDuration > tmpCurrentAura->GetDuration())
                        {
                            minDuration = tmpCurrentAura->GetDuration();
                            smallestIcicle = i;
                        }
                    }
                }

                // Launch the icicle with the smallest duration
                if (AuraEffect* currentIcicleAuraEffect = player->GetAuraEffect(IcicleAuras[smallestIcicle], EFFECT_0))
                {
                    int32 basePoints = currentIcicleAuraEffect->GetAmount();

                    if (caster->HasAura(SPELL_MAGE_BLACK_ICE))
                    {
                        if (roll_chance_i(20))
                            basePoints *= 2;
                    }

                    player->CastSpell(target, IcicleHits[smallestIcicle], true);
                    player->CastCustomSpell(target, SPELL_MAGE_ICICLE_DAMAGE, &basePoints, NULL, NULL, true);
                    player->RemoveAura(IcicleAuras[smallestIcicle]);
                }

                icicleFreeSlot = smallestIcicle;
                // No break because we'll add the icicle in the next case
            }
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
            {

                if (Aura* currentIcicleAura = player->AddAura(IcicleAuras[icicleFreeSlot], player))
                {
                    if (AuraEffect* effect = currentIcicleAura->GetEffect(EFFECT_0))
                        effect->SetAmount(hitDamage);

                    player->AddAura(SPELL_MAGE_ICICLE_AURA, player);

                    if (caster->HasSpell(SPELL_MAGE_GLACIAL_SPIKE))
                    {
                        if (Aura* glacialSpikeProc = player->GetAura(SPELL_MAGE_ICICLE_AURA))
                        {
                            if (glacialSpikeProc->GetStackAmount() == 5)
                                player->CastSpell(player, SPELL_MAGE_GLACIAL_SPIKE_PROC, true);
                        }
                    }
                }
                break;
            }
            }

            switch (icicleSecondFreeSlot)
            {
            case -1:
            {
                if (icilesAddSecond)
                {
                    // We need to find the icicle with the smallest duration.
                    int8 smallestIcicle = 0;
                    int32 minDuration = 0xFFFFFF;
                    for (int8 i = 0; i < 5; i++)
                    {
                        if (Aura* tmpCurrentAura = player->GetAura(IcicleAuras[i]))
                        {
                            if (minDuration > tmpCurrentAura->GetDuration())
                            {
                                minDuration = tmpCurrentAura->GetDuration();
                                smallestIcicle = i;
                            }
                        }
                    }

                    // Launch the icicle with the smallest duration
                    if (AuraEffect* currentIcicleAuraEffect = player->GetAuraEffect(IcicleAuras[smallestIcicle], EFFECT_0))
                    {
                        int32 basePoints = currentIcicleAuraEffect->GetAmount();

                        if (caster->HasAura(SPELL_MAGE_BLACK_ICE))
                        {
                            if (roll_chance_i(20))
                                basePoints *= 2;
                        }

                        player->CastSpell(target, IcicleHits[smallestIcicle], true);
                        player->CastCustomSpell(target, SPELL_MAGE_ICICLE_DAMAGE, &basePoints, NULL, NULL, true);
                        player->RemoveAura(IcicleAuras[smallestIcicle]);
                    }

                    icicleSecondFreeSlot = smallestIcicle;
                    // No break because we'll add the icicle in the next case
                }
            }
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
            {
                if (Aura* currentIcicleAura = player->AddAura(IcicleAuras[icicleSecondFreeSlot], player))
                {
                    if (AuraEffect* effect = currentIcicleAura->GetEffect(EFFECT_0))
                        effect->SetAmount(hitDamage);

                    player->AddAura(SPELL_MAGE_ICICLE_AURA, player);

                    if (caster->HasSpell(SPELL_MAGE_GLACIAL_SPIKE))
                    {
                        if (Aura* glacialSpikeProc = player->GetAura(SPELL_MAGE_ICICLE_AURA))
                        {
                            if (glacialSpikeProc->GetStackAmount() == 5)
                                player->CastSpell(player, SPELL_MAGE_GLACIAL_SPIKE_PROC, true);
                        }
                    }
                }
                break;
            }
            }
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_mastery_icicles_proc::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_mastery_icicles_proc::OnProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

// Icicles (Aura Remove) - (214124, 214125, 214126, 214127, 214130) 
class spell_mastery_icicles_mod_aura : public AuraScript
{
    PrepareAuraScript(spell_mastery_icicles_mod_aura);

    void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Unit* caster = GetCaster();
        if (!caster)
            return;

        if (Aura* aur = caster->GetAura(SPELL_MAGE_ICICLE_AURA))
            aur->ModStackAmount(-1);

        if (caster->HasAura(SPELL_MAGE_GLACIAL_SPIKE_PROC))
            caster->RemoveAura(SPELL_MAGE_GLACIAL_SPIKE_PROC);
    }

    void Register() override
    {
        OnEffectRemove += AuraEffectRemoveFn(spell_mastery_icicles_mod_aura::OnRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

// Icicles (periodic) - 148023
class spell_mastery_icicles_periodic : public AuraScript
{
    PrepareAuraScript(spell_mastery_icicles_periodic);

    uint32 icicles[5];
    int32 icicleCount;

    void OnApply(AuraEffect const* /*l_AurEff*/, AuraEffectHandleModes /*l_Mode*/)
    {
        icicleCount = 0;
        if (Unit* caster = GetCaster())
        {
            for (uint32 i = 0; i < 5; ++i)
            {
                if (caster->HasAura(IcicleAuras[i]))
                    icicles[icicleCount++] = IcicleAuras[i];
            }
        }
    }

    void OnTick(AuraEffect const* /*aurEff*/)
    {
        if (Unit* caster = GetCaster())
        {
            if (AuraEffect* aura = caster->GetAuraEffect(GetSpellInfo()->Id, EFFECT_0))
            {
                // Maybe not the good target selection ...
                if (Unit* target = ObjectAccessor::GetUnit(*caster, caster->Variables.GetValue<ObjectGuid>("IciclesTarget")))
                {
                    if (target->IsAlive())
                    {
                        int32 amount = aura->GetAmount();
                        if (Aura* currentIcicleAura = caster->GetAura(icicles[amount]))
                        {
                            int32 basePoints = currentIcicleAura->GetEffect(0)->GetAmount();

                            if (caster->HasAura(SPELL_MAGE_BLACK_ICE))
                            {
                                if (roll_chance_i(20))
                                    basePoints *= 2;
                            }

                            caster->CastSpell(target, IcicleHits[amount], true);
                            caster->CastCustomSpell(target, SPELL_MAGE_ICICLE_DAMAGE, &basePoints, NULL, NULL, true);
                            caster->RemoveAura(IcicleAuras[amount]);
                        }

                        if (++amount >= icicleCount)
                            caster->RemoveAura(aura->GetBase());
                        else
                            aura->SetAmount(amount);
                    }
                    else
                        caster->RemoveAura(aura->GetBase());
                }
            }
        }
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_mastery_icicles_periodic::OnApply, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY, AURA_EFFECT_HANDLE_REAL);
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_mastery_icicles_periodic::OnTick, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

// Glacial Spike - 199786
class spell_mastery_icicles_glacial_spike : public SpellScript
{
    PrepareSpellScript(spell_mastery_icicles_glacial_spike);

    int32 IcicleDamage;

    void HandleOnCast()
    {
        Player* player = GetCaster()->ToPlayer();

        if (!player)
            return;

        // Remove aura with visual icicle and get damage per stored icicle
        for (int8 i = 0; i < 5; ++i)
        {
            if (Aura* currentIcicleAura = player->GetAura(IcicleAuras[i]))
            {
                int32 basePoints = currentIcicleAura->GetEffect(0)->GetAmount();
                player->RemoveAura(IcicleAuras[i]);

                IcicleDamage += basePoints;
            }
        }
    }

    void HandleOnHit(SpellEffIndex /*effIndex*/)
    {

        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        int32 damage = GetHitDamage();
        damage += IcicleDamage;

        caster->CastCustomSpell(target, SPELL_MAGE_GLACIAL_SPIKE_DAMAGE, &damage, NULL, NULL, true);

        if (caster->HasAura(SPELL_MAGE_ICICLE_AURA))
            caster->RemoveAurasDueToSpell(SPELL_MAGE_ICICLE_AURA);

        if (caster->HasAura(SPELL_MAGE_GLACIAL_SPIKE_PROC))
            caster->RemoveAurasDueToSpell(SPELL_MAGE_GLACIAL_SPIKE_PROC);
    }

    void Register() override
    {
        OnCast += SpellCastFn(spell_mastery_icicles_glacial_spike::HandleOnCast);
        OnEffectHitTarget += SpellEffectFn(spell_mastery_icicles_glacial_spike::HandleOnHit, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};
// 195302 - Arcane Charge
class spell_mage_arcane_charge_clear : public SpellScript
{
    PrepareSpellScript(spell_mage_arcane_charge_clear);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_MAGE_ARCANE_CHARGE });
    }

    void RemoveArcaneCharge(SpellEffIndex /*effIndex*/)
    {
        GetHitUnit()->RemoveAurasDueToSpell(SPELL_MAGE_ARCANE_CHARGE);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_mage_arcane_charge_clear::RemoveArcaneCharge, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

void AddSC_mage_spell_scripts()
{
    new playerscript_mage_arcane();

    new spell_mage_combustion();
    new spell_mage_incanters_flow();
    RegisterSpellScript(spell_mage_polymorph);
    new spell_mage_time_warp();
    new spell_mage_fire_mage_passive();
    new spell_mage_fire_on();
    RegisterSpellScript(spell_mage_mirror_image_summon);
    new spell_mage_cauterize();
    new spell_mage_conjure_refreshment();
    RegisterSpellScript(spell_mage_dragon_breath);
    RegisterSpellScript(spell_mage_ice_floes);
    RegisterSpellScript(spell_mage_displacement);
    RegisterSpellScript(spell_mage_blink);
    RegisterSpellScript(spell_mage_ebonbolt);
    RegisterSpellScript(spell_mage_greater_pyro);
    RegisterSpellScript(spell_mage_scorch);
    RegisterSpellScript(spell_mage_conf_damage);

    //7.3.2.25549
    RegisterSpellScript(spell_mage_cold_snap);
    RegisterSpellScript(spell_mage_cone_of_cold);
    RegisterSpellScript(spell_mage_ice_lance);
    RegisterSpellScript(spell_mage_flurry);
    RegisterSpellScript(spell_mage_nova_talent);
    RegisterSpellScript(spell_mage_frostbolt);
    RegisterSpellScript(spell_mage_blizzard);
    RegisterSpellScript(spell_mage_frozen_orb);
    RegisterSpellScript(spell_mage_firestarter);
    RegisterSpellScript(spell_mage_pyroblast);
    RegisterSpellScript(spell_mage_living_bomb);
    RegisterSpellScript(spell_mage_living_bomb_spread);
    RegisterSpellScript(spell_mage_meteor);
    RegisterSpellScript(spell_mage_meteor_damage);
    RegisterSpellScript(spell_mage_comet_storm);
    RegisterSpellScript(spell_mage_fire_blast);
    RegisterSpellScript(spell_mage_arcane_barrage);
    RegisterSpellScript(spell_mage_arcane_missiles_damage);
    RegisterSpellScript(spell_mage_arcane_explosion);

    RegisterSpellScript(spell_mage_chrono_shift);
    RegisterSpellScript(spell_mage_arcane_missiles);
    RegisterSpellScript(spell_mage_arcane_barrier);
    RegisterSpellScript(spell_mage_conflagration);
    RegisterSpellScript(spell_mage_enhanced_pyrotechnics);
    RegisterSpellScript(spell_mage_frenetic_speed);
    RegisterSpellScript(spell_mage_living_bomb_dot);
    RegisterSpellScript(spell_mage_blazing_barrier);
    RegisterSpellScript(spell_mage_kindling);
    RegisterSpellScript(spell_mage_pyroblast_clearcasting_driver);
    RegisterSpellScript(spell_mage_chilled_to_the_core);
    RegisterSpellScript(spell_mage_chain_reaction);
    RegisterSpellScript(spell_mage_jouster);
    RegisterSpellScript(spell_mage_jouster_buff);
    RegisterSpellScript(spell_mage_ice_barrier);
    RegisterSpellScript(spell_mage_ice_block);
    RegisterSpellScript(spell_mage_chilled);
    RegisterSpellAndAuraScriptPair(spell_mage_ray_of_frost, aura_mage_ray_of_frost);
    //7.3.2.25549 END

    RegisterSpellScript(spell_mage_flamestrike);
    RegisterSpellScript(spell_mage_ring_of_frost);
    new spell_mage_ring_of_frost_stun();
    RegisterSpellScript(spell_mage_cinderstorm);
    RegisterSpellScript(spell_mage_clearcasting);
    RegisterSpellScript(spell_mage_presence_of_mind);
    RegisterSpellScript(spell_mage_arcane_blast);
    RegisterSpellScript(spell_mage_phoenix_flames);
    RegisterSpellScript(spell_mage_phoenix_flames_aoe);
    RegisterSpellScript(spell_mage_arcane_familiar);
    RegisterSpellScript(spell_mage_arcane_familiar_mana);
    RegisterSpellScript(aura_mage_touch_of_the_magi);
    RegisterSpellScript(aura_mage_touch_of_the_magi_aura);
    RegisterSpellScript(aura_mage_freezing_rain);
    RegisterSpellScript(aura_mage_time_anomaly);
    RegisterSpellScript(aura_mage_nether_tempest);
    RegisterSpellScript(spell_mage_nether_tempest_aoe_damage);
    RegisterSpellScript(spell_mage_embolt);
    RegisterSpellScript(aura_mage_burst_of_cold);
    RegisterSpellScript(spell_mage_burst_of_cold);
    RegisterSpellScript(aura_mage_displacement_beacon_aura);
    RegisterSpellScript(aura_mage_prismatic_clock);
    RegisterSpellScript(aura_mage_clearcasting_pvp);
    RegisterSpellScript(aura_mage_greater_invisibility);
    RegisterSpellScript(aura_mage_temporal_shield);
    RegisterSpellScript(aura_mage_frost_nova);
    RegisterSpellScript(aura_mage_frostbite);
    RegisterSpellScript(aura_mage_flamecannon);
    RegisterSpellScript(aura_fingers_of_frost);
    RegisterSpellScript(aura_mage_dragon_breath);
    RegisterSpellScript(spell_mage_lonely_winter);
    RegisterSpellScript(spell_mage_blast_wave);
    RegisterSpellScript(aura_mage_tinder);
    RegisterSpellScript(spell_mage_greater_pyroblast);
    RegisterSpellScript(spell_mage_flurry_damage);
    RegisterSpellScript(aura_mage_brain_freeze_aura);
    RegisterSpellScript(aura_mage_dampened_magic);
    RegisterSpellScript(aura_mage_rule_of_threes_aura);
    RegisterSpellScript(aura_mage_clearcasting_proc);
    RegisterSpellScript(aura_mage_firestarter_proc);
    RegisterSpellScript(aura_mage_frostbite_aura);
    RegisterSpellScript(aura_bone_chilling);
    RegisterSpellScript(aura_bone_chilling_aura);
    RegisterSpellScript(aura_mage_enhaced_pyrotechnics);
    RegisterSpellScript(spell_mage_alter_time_aura);
    RegisterSpellScript(spell_mage_alter_time_active);
    RegisterSpellScript(spell_mage_shifting_power);
    RegisterSpellScript(spell_mastery_icicles_proc);
    RegisterSpellScript(spell_mastery_icicles_periodic);
    RegisterSpellScript(spell_mastery_icicles_mod_aura);
    RegisterSpellScript(spell_mage_mastery_ignite);
    new spell_mastery_ignite();
    RegisterSpellScript(spell_mage_arcane_charge_clear);
    RegisterSpellScript(spell_mastery_icicles_glacial_spike);

    // Spell Pet scripts
    RegisterSpellScript(spell_mage_pet_freeze);

    // AreaTrigger scripts
    new at_mage_meteor_timer();
    new at_mage_meteor_burn();
    new at_mage_blizzard();
    RegisterAreaTriggerAI(at_mage_rune_of_power);
    RegisterAreaTriggerAI(at_mage_frozen_orb);
    RegisterAreaTriggerAI(at_mage_arcane_orb);
    RegisterAreaTriggerAI(at_mage_flame_patch);
    RegisterAreaTriggerAI(at_mage_cinderstorm);

    // NPC Scripts
    new npc_mirror_image();
}
