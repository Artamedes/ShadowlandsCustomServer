/*
 * This file is part of the TrinityCore Project. See AUTHORS file for Copyright information
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
 * Scripts for spells with SPELLFAMILY_WARRIOR and SPELLFAMILY_GENERIC spells used by warrior players.
 * Ordered alphabetically using scriptname.
 * Scriptnames of files in this file should be prefixed with "spell_warr_".
 */

#include "ScriptMgr.h"
#include "Map.h"
#include "MoveSpline.h"
#include "PathGenerator.h"
#include "Player.h"
#include "SpellMgr.h"
#include "SpellAuraEffects.h"
#include "SpellHistory.h"
#include "SpellScript.h"

enum WarriorSpells
{
    SPELL_WARRIOR_BLADESTORM_PERIODIC_WHIRLWIND     = 50622,
    SPELL_WARRIOR_BLOODTHIRST_HEAL                  = 117313,
    SPELL_WARRIOR_BLOODTHIRST                       = 23885,
    SPELL_WARRIOR_BLOODTHIRST_DAMAGE                = 23881,
    SPELL_WARRIOR_CHARGE                            = 34846,
    SPELL_WARRIOR_CHARGE_EFFECT                     = 218104,
    SPELL_WARRIOR_CHARGE_EFFECT_BLAZING_TRAIL       = 198337,
    SPELL_WARRIOR_CHARGE_PAUSE_RAGE_DECAY           = 109128,
    SPELL_WARRIOR_CHARGE_ROOT_EFFECT                = 105771,
    SPELL_WARRIOR_CHARGE_SLOW_EFFECT                = 236027,
    SPELL_WARRIOR_COLOSSUS_SMASH                    = 167105,
    SPELL_WARRIOR_COLOSSUS_SMASH_EFFECT             = 208086,
    SPELL_WARRIOR_EXECUTE                           = 20647,
    SPELL_WARRIOR_GLYPH_OF_THE_BLAZING_TRAIL        = 123779,
    SPELL_WARRIOR_GLYPH_OF_HEROIC_LEAP              = 159708,
    SPELL_WARRIOR_GLYPH_OF_HEROIC_LEAP_BUFF         = 133278,
    SPELL_WARRIOR_HEROIC_LEAP_JUMP                  = 178368,
    SPELL_WARRIOR_IMPENDING_VICTORY                 = 202168,
    SPELL_WARRIOR_IMPENDING_VICTORY_HEAL            = 202166,
    SPELL_WARRIOR_IMPROVED_HEROIC_LEAP              = 157449,
    SPELL_WARRIOR_MORTAL_STRIKE                     = 12294,
    SPELL_WARRIOR_MORTAL_WOUNDS                     = 213667,
    SPELL_WARRIOR_RALLYING_CRY                      = 97463,
    SPELL_WARRIOR_SHOCKWAVE                         = 46968,
    SPELL_WARRIOR_SHOCKWAVE_STUN                    = 132168,
    SPELL_WARRIOR_STOICISM                          = 70845,
    SPELL_WARRIOR_STORM_BOLT_STUN                   = 132169,
    SPELL_WARRIOR_SWEEPING_STRIKES_EXTRA_ATTACK_1   = 12723,
    SPELL_WARRIOR_SWEEPING_STRIKES_EXTRA_ATTACK_2   = 26654,
    SPELL_WARRIOR_TAUNT                             = 355,
    SPELL_WARRIOR_TRAUMA_EFFECT                     = 215537,
    SPELL_WARRIOR_VICTORIOUS                        = 32216,
    SPELL_WARRIOR_VICTORY_RUSH_HEAL                 = 118779,
    SPELL_WARRIOR_ENRAGE_AURA                       = 184362,
    SPELL_WARRIOR_ALLOW_RAGING_BLOW                 = 131116,
    SPELL_WARRIOR_ANGER_MANAGEMENT                  = 152278,
    SPELL_WARRIOR_BERZERKER_RAGE_EFFECT             = 23691,
    //SPELL_WARRIOR_BLADESTORM_PERIODIC_WHIRLWIND     = 50622,
    //SPELL_WARRIOR_BLOODTHIRST                       = 23885,
    //SPELL_WARRIOR_BLOODTHIRST_DAMAGE                = 23881,
    //SPELL_WARRIOR_BLOODTHIRST_HEAL                  = 117313,
    SPELL_WARRIOR_BLOOD_AND_THUNDER                 = 84615,
    SPELL_WARRIOR_BOUNDING_STRIDE                   = 202163,
    SPELL_WARRIOR_BOUNDING_STRIDE_SPEED             = 202164,
    //SPELL_WARRIOR_CHARGE                            = 34846,
    //SPELL_WARRIOR_CHARGE_EFFECT                     = 218104,
    //SPELL_WARRIOR_CHARGE_EFFECT_BLAZING_TRAIL       = 198337,
    //SPELL_WARRIOR_CHARGE_PAUSE_RAGE_DECAY           = 109128,
    //SPELL_WARRIOR_CHARGE_ROOT_EFFECT                = 105771,
    //SPELL_WARRIOR_CHARGE_SLOW_EFFECT                = 236027,
    //SPELL_WARRIOR_COLOSSUS_SMASH                    = 167105,
    SPELL_WARRIOR_COLOSSUS_SMASH_BUFF               = 208086,
    SPELL_WARRIOR_DEEP_WOUNDS                       = 115767,
    SPELL_WARRIOR_DEEP_WOUNDS_PERIODIC              = 12721,
    SPELL_WARRIOR_DEEP_WOUNDS_RANK_1                = 12162,
    SPELL_WARRIOR_DEEP_WOUNDS_RANK_2                = 12850,
    SPELL_WARRIOR_DEEP_WOUNDS_RANK_3                = 12868,
    SPELL_WARRIOR_DEEP_WOUNDS_RANK_PERIODIC         = 12721,
    SPELL_WARRIOR_DEVASTATE                         = 20243,
    SPELL_WARRIOR_DOUBLE_TIME                       = 103827,
    SPELL_WARRIOR_DRAGON_ROAR_KNOCK_BACK            = 118895,
    SPELL_WARRIOR_ENRAGE                            = 184361,
    //SPELL_WARRIOR_ENRAGE_AURA                       = 184362,
    //SPELL_WARRIOR_EXECUTE                           = 163201,
    SPELL_WARRIOR_EXECUTE_PVP                       = 217955,
    SPELL_WARRIOR_FOCUSED_RAGE_ARMS                 = 207982,
    SPELL_WARRIOR_FOCUSED_RAGE_PROTECTION           = 204488,
    SPELL_WARRIOR_FURIOUS_SLASH                     = 100130,
    //SPELL_WARRIOR_GLYPH_OF_THE_BLAZING_TRAIL        = 123779,
    SPELL_WARRIOR_GLYPH_OF_EXECUTION                = 58367,
    //SPELL_WARRIOR_GLYPH_OF_HEROIC_LEAP              = 159708,
    //SPELL_WARRIOR_GLYPH_OF_HEROIC_LEAP_BUFF         = 133278,
    SPELL_WARRIOR_GLYPH_OF_HINDERING_STRIKES        = 58366,
    SPELL_WARRIOR_GLYPH_OF_MORTAL_STRIKE            = 58368,
    SPELL_WARRIOR_HEAVY_REPERCUSSIONS               = 203177,
    SPELL_WARRIOR_HEROIC_LEAP_DAMAGE                = 52174,
    //SPELL_WARRIOR_HEROIC_LEAP_JUMP                  = 94954,
    SPELL_WARRIOR_HEROIC_LEAP_SPEED                 = 133278,
    SPELL_WARRIOR_IGNORE_PAIN                       = 190456,
    //SPELL_WARRIOR_IMPENDING_VICTORY                 = 202168,
    //SPELL_WARRIOR_IMPROVED_HEROIC_LEAP              = 157449,
    SPELL_WARRIOR_INTERCEPT_STUN                    = 105771,
    SPELL_WARRIOR_INTERVENE_TRIGGER                 = 147833,
    SPELL_WARRIOR_ITEM_PVP_SET_4P_BONUS             = 133277,
    SPELL_WARRIOR_JUGGERNAUT_CRIT_BONUS_BUFF        = 65156,
    SPELL_WARRIOR_JUGGERNAUT_CRIT_BONUS_TALENT      = 64976,
    SPELL_WARRIOR_JUMP_TO_SKYHOLD_AURA              = 215997,
    SPELL_WARRIOR_JUMP_TO_SKYHOLD_JUMP              = 192085,
    SPELL_WARRIOR_JUMP_TO_SKYHOLD_TELEPORT          = 216016,
    SPELL_WARRIOR_LAST_STAND_TRIGGERED              = 12976,
    SPELL_WARRIOR_MASSACRE                          = 206315,
    SPELL_WARRIOR_MEAT_CLEAVER_PROC                 = 85739,
    SPELL_WARRIOR_MOCKING_BANNER_TAUNT              = 114198,
    //SPELL_WARRIOR_MORTAL_STRIKE                     = 12294,
    SPELL_WARRIOR_MORTAL_STRIKE_AURA                = 12294,
    //SPELL_WARRIOR_MORTAL_WOUNDS                     = 115804,
    SPELL_WARRIOR_NEW_BLADESTORM                    = 222634,
    SPELL_WARRIOR_OLD_BLADESTORM                    = 227847,
    SPELL_WARRIOR_OPPORTUNITY_STRIKE_DAMAGE         = 76858,
    SPELL_WARRIOR_OVERPOWER_PROC                    = 7384,
    //SPELL_WARRIOR_RALLYING_CRY                      = 97463,
    SPELL_WARRIOR_RALLYING_CRY_TRIGGER              = 97463,
    SPELL_WARRIOR_RAMPAGE                           = 184367,
    SPELL_WARRIOR_RAVAGER                           = 152277,
    SPELL_WARRIOR_RAVAGER_DAMAGE                    = 156287,
    SPELL_WARRIOR_RAVAGER_ENERGIZE                  = 248439,
    SPELL_WARRIOR_RAVAGER_PARRY                     = 227744,
    SPELL_WARRIOR_RAVAGER_SUMMON                    = 227876,
    SPELL_WARRIOR_REND                              = 94009,
    SPELL_WARRIOR_RENEWED_FURY                      = 202288,
    SPELL_WARRIOR_RENEWED_FURY_EFFECT               = 202289,
    SPELL_WARRIOR_RETALIATION_DAMAGE                = 22858,
    SPELL_WARRIOR_SEASONED_SOLDIER                  = 279423,
    SPELL_WARRIOR_SECOND_WIND_DAMAGED               = 202149,
    SPELL_WARRIOR_SECOND_WIND_HEAL                  = 202147,
    SPELL_WARRIOR_SHIELD_BLOCKC_TRIGGERED           = 132404,
    SPELL_WARRIOR_SHIELD_SLAM                       = 23922,
    //SPELL_WARRIOR_SHOCKWAVE                         = 46968,
    //SPELL_WARRIOR_SHOCKWAVE_STUN                    = 132168,
    SPELL_WARRIOR_SLAM                              = 50782,
    SPELL_WARRIOR_SLAM_ARMS                         = 1464,
    SPELL_WARRIOR_SLUGGISH                          = 129923,
    //SPELL_WARRIOR_STORM_BOLT_STUN                   = 132169,
    SPELL_WARRIOR_SUNDER_ARMOR                      = 58567,
    SPELL_WARRIOR_SWEEPING_STRIKES_EXTRA_ATTACK     = 26654,
    //SPELL_WARRIOR_SWEEPING_STRIKES_EXTRA_ATTACK_1   = 12723,
    //SPELL_WARRIOR_SWEEPING_STRIKES_EXTRA_ATTACK_2   = 26654,
    SPELL_WARRIOR_SWORD_AND_BOARD                   = 50227,
    SPELL_WARRIOR_TACTICIAN_CD                      = 199854,
    SPELL_WARRIOR_TASTE_FOR_BLOOD                   = 206333,
    SPELL_WARRIOR_TASTE_FOR_BLOOD_DAMAGE_DONE       = 125831,
    //SPELL_WARRIOR_TAUNT                             = 355,
    SPELL_WARRIOR_THUNDERSTRUCK                     = 199045,
    SPELL_WARRIOR_THUNDERSTRUCK_STUN                = 199042,
    SPELL_WARRIOR_THUNDER_CLAP                      = 6343,
    SPELL_WARRIOR_TRAUMA_DOT                        = 215537,
    SPELL_WARRIOR_UNCHACKLED_FURY                   = 76856,
    SPELL_WARRIOR_UNRELENTING_ASSAULT_RANK_1        = 46859,
    SPELL_WARRIOR_UNRELENTING_ASSAULT_RANK_2        = 46860,
    SPELL_WARRIOR_UNRELENTING_ASSAULT_TRIGGER_1     = 64849,
    SPELL_WARRIOR_UNRELENTING_ASSAULT_TRIGGER_2     = 64850,
    SPELL_WARRIOR_VENGEANCE                         = 76691,
    SPELL_WARRIOR_VENGEANCE_AURA                    = 202572,
    SPELL_WARRIOR_VENGEANCE_FOCUSED_RAGE            = 202573,
    SPELL_WARRIOR_VENGEANCE_IGNORE_PAIN             = 202574,
    SPELL_WARRIOR_VICTORIOUS_STATE                  = 32216,
    SPELL_WARRIOR_VICTORY_RUSH_DAMAGE               = 34428,
    //SPELL_WARRIOR_VICTORY_RUSH_HEAL                 = 118779,
    SPELL_WARRIOR_VIGILANCE_PROC                    = 50725,
    SPELL_WARRIOR_WAR_MACHINE_TALENT_AURA           = 215556,
    SPELL_WARRIOR_WAR_MACHINE_AURA                  = 215566,
    SPELL_WARRIOR_WARBRINGER                        = 103828,
    SPELL_WARRIOR_WARBRINGER_ROOT                   = 105771,
    SPELL_WARRIOR_WARBRINGER_SNARE                  = 137637,
    SPELL_WARRIOR_WEAKENED_BLOWS                    = 115798,
    SPELL_WARRIOR_WHIRLWIND                         = 190411,
    SPELL_WARRIOR_WHIRLWIND_ARMS                    = 1680,
    SPELL_WARRIOR_WHIRLWIND_MAINHAND                = 199667,
    SPELL_WARRIOR_WHIRLWIND_OFFHAND                 = 44949,
    SPELL_WARRIOR_WRECKING_BALL_EFFECT              = 215570,
    SPELL_WARRIOR_COMMANDING_SHOUT                  = 97463,
    //SPELL_WARRIOR_IMPENDING_VICTORY_HEAL            = 202166,
    SPELL_WARRIOR_KILLING_MACHINE_SPEED             = 262232,
    SPELL_WARRIOR_SUDDEN_DEATH                      = 52437,
    SPELL_WARRIOR_INTO_THE_FRAY_HASTE               = 202602,
    SPELL_WARRIOR_INTO_THE_FRAY                     = 202603,
    SPELL_WARRIOR_SAFEGUARD                         = 223657,
    SPELL_WARRIOR_SAFEGUARD_BUFF                    = 223658,
    SPELL_WARRIOR_SHIELD_SLAM_RANK2                 = 231834,
    SPELL_WARRIOR_SHILED_SLAM_INDICATOR             = 224324,
    SPELL_WARRIOR_TACTICIAN                         = 184783,
    SPELL_WARRIOR_FERVOR_OF_BATTLE                  = 202316,
    SPELL_WARRIOR_INTIMIDATING_SHOUT                = 5246,
    SPELL_WARRIOR_COLLATERAL_DAMAGE                 = 268243,
    SPELL_WARRIOR_COLLATERAL_DAMAGE_ENERGIZE        = 268344,
    SPELL_WARRIOR_SWEEPING_STRIKE                   = 260708,
    SPELL_WARRIOR_DEEP_WOUNDS_AURA                  = 262115,
    SPELL_WARRIOR_FURIOUS_CHARGE                    = 202224,
    SPELL_WARRIOR_FURIOUS_CHARGE_BUFF               = 202225,
	SPELL_WARRIOR_SUDDEN_DEATH_FURY					= 280776,
	SPELL_WARRIOR_SUDDEN_DEATH_ARMS_TALENT			= 29725,
    SPELL_WARRIOR_BATTLE_TRACE                      = 213858,
    SPELL_WARRIOR_RAGING_BLOW                       = 96103,
    SPELL_WARRIOR_BARBARIAN                         = 280745,
    SPELL_WARRIOR_BARBARIAN_BUFF                    = 280746,
    SPELL_WARRIOR_HEROIC_LEAP                       = 6544,
	SPELL_WARRIOR_SHARPEN_BLADE                     = 198817,
    SPELL_WARRIOR_SHARPEN_BLADE_DEBUFF              = 198819,
	SPELL_WARRIOR_MEAT_CLEAVER_ENERGIZE				= 280392,
	SPELL_WARRIOR_OVERPOWER							= 256357,
	SPELL_WARRIOR_SIEGEBREAKER						= 280772,
	SPELL_WARRIOR_IN_FOR_THE_KILL					= 248621,
	SPELL_WARRIOR_IN_FOR_THE_KILL_BUFF				= 248622,
	SPELL_WARRIOR_SHADOW_OF_THE_COLOSSUS			= 198807,
	SPELL_WARRIOR_DEATH_SENTENCE					= 198500,
	SPELL_WARRIOR_RUMBLING_EARTH					= 275339,
	SPELL_WARRIOR_LEAVE_NO_MAN_BEHIND				= 199037,
	SPELL_WARRIOR_LEAVE_NO_MAN_BEHIND_BUFF		    = 199038,
	SPELL_WARRIOR_BODYGUARD							= 213871,
    SPELL_WARRIOR_WARPATH                           = 199086,
	SPELL_WARRIOR_WARPATH_STUN                      = 199085,
    SPELL_WARRIOR_DRAGON_DAMAGE                     = 206579,
    SPELL_WARRIOR_WAR_BANNER_BUFF                   = 236321,
    SPELL_WARRIOR_DUEL_ENEMY                        = 236276,
    SPELL_WARRIOR_DUEL                              = 236273,
    SPELL_WARRIOR_WHIRLWIND_ENERGIZE                = 280715,
    SPELL_WARRIOR_ENDLESS_RAGE                      = 202296,
    SPELL_WARRIOR_ENDLESS_RAGE_ENERGIZE             = 280283,
    SPELL_WARRIOR_CRUSHING_ASSAULT_POWER            = 278751,
    SPELL_WARRIOR_CRUSHING_ASSAULT_BUFF             = 278826,
    SPELL_WARRIOR_EXECUTE_ARMS_RANK_2               = 231830,
    SPELL_WARRIOR_MASTERY_DEEP_WOUNDS               = 262111,
    SPELL_WARRIOR_SLAUGHTERHOUSE                    = 280747,
    SPELL_WARRIOR_EXECUTIONER_PRECISION_PROC        = 272870,
    SPELL_WARRIOR_INFINITE_FURY_POWER               = 277638,
    SPELL_WARRIOR_INFINITE_FURY_BUFF                = 278134,
    SPELL_WARRIOR_BLOODCRAZE                        = 273428,
    SPELL_WARRIOR_LORD_OF_WAR_POWER                 = 278752,
    SPELL_WARRIOR_LORD_OF_WAR_ENERGIZE              = 279203,
    SPELL_WARRIOR_BURY_THE_HATCHERY                 = 280128,
    SPELL_WARRIOR_BURY_THE_HATCHERY_ABSORB          = 280212,
    SPELL_WARRIOR_GATHERING_STORM_PERIODIC          = 273414,

    NPC_WARRIOR_RAVAGER                             = 76168,
};

enum WarriorSpellIcons
{
    WARRIOR_ICON_ID_SUDDEN_DEATH                    = 1989
};


enum WarriorMisc
{
    SPELL_VISUAL_BLAZING_CHARGE = 26423,
    SPELL_PALADIN_BLESSING_OF_SANCTUARY             = 20911,
    SPELL_PALADIN_GREATER_BLESSING_OF_SANCTUARY     = 25899,
    SPELL_PRIEST_RENEWED_HOPE                       = 63944
};

// 23881 - Bloodthirst
class spell_warr_bloodthirst : public SpellScript
{

    PrepareSpellScript(spell_warr_bloodthirst);

    bool Load() override
    {
        return ValidateSpellInfo({ SPELL_WARRIOR_BLOODTHIRST_HEAL,  SPELL_WARRIOR_SLAUGHTERHOUSE });
    }

    void HandleCritChance(Unit const* /*victim*/, float& chance)
    {
        if (GetCaster())
            if (Player* player = GetCaster()->ToPlayer())
                if (AuraEffect* aurEff = player->GetAuraEffect(SPELL_WARRIOR_BLOODCRAZE, EFFECT_0))
                    chance += aurEff->GetAmount() * player->GetRatingMultiplier(CR_CRIT_SPELL);
    }

    void HandleDamage(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        // $mult = ($max(0, $min($pl - 10, 10)) * 8 + 137) / 217
        float mult = (float)(std::max(0, std::min((int32)caster->GetLevel() - 10, 10)) * 8 + 137) / 217;
        int32 damage = 1 + GetHitDamage() * mult;
        int32 heal = sSpellMgr->GetSpellInfo(SPELL_WARRIOR_BLOODTHIRST_HEAL)->GetEffect(EFFECT_0).BasePoints;

        if (caster->HasAura(SPELL_WARRIOR_SLAUGHTERHOUSE) && target->GetHealthPct() <= sSpellMgr->GetSpellInfo(SPELL_WARRIOR_SLAUGHTERHOUSE)->GetEffect(EFFECT_2).BasePoints)
        {
            AddPct(damage, sSpellMgr->GetSpellInfo(SPELL_WARRIOR_SLAUGHTERHOUSE)->GetEffect(EFFECT_1).BasePoints);
            AddPct(heal, sSpellMgr->GetSpellInfo(SPELL_WARRIOR_SLAUGHTERHOUSE)->GetEffect(EFFECT_1).BasePoints);
            caster->GetSpellHistory()->ModifyCooldown(SPELL_WARRIOR_BLOODTHIRST_DAMAGE, int32(sSpellMgr->GetSpellInfo(SPELL_WARRIOR_SLAUGHTERHOUSE)->GetEffect(EFFECT_0).BasePoints) * -1s);
        }

        SetHitDamage(damage);

        CastSpellExtraArgs args(TRIGGERED_FULL_MASK);
        args.AddSpellBP0(heal);
        caster->CastSpell(target, SPELL_WARRIOR_BLOODTHIRST_HEAL, args);

        if (roll_chance_i(30))
        {
            if (Aura* enrage = caster->GetAura(SPELL_WARRIOR_ENRAGE_AURA))
                enrage->RefreshDuration();
            else
                caster->CastSpell(caster, SPELL_WARRIOR_ENRAGE_AURA, true);
        }
    }

    void Register() override
    {
        OnCalcCritChance += SpellOnCalcCritChanceFn(spell_warr_bloodthirst::HandleCritChance);
        OnEffectHitTarget += SpellEffectFn(spell_warr_bloodthirst::HandleDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

// 100 - Charge
class spell_warr_charge : public SpellScript
{
    PrepareSpellScript(spell_warr_charge);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo
        ({
            SPELL_WARRIOR_CHARGE_EFFECT,
            SPELL_WARRIOR_CHARGE_EFFECT_BLAZING_TRAIL
        });
    }

    void HandleDummy(SpellEffIndex /*effIndex*/)
    {
        uint32 spellId = SPELL_WARRIOR_CHARGE_EFFECT;
        if (GetCaster()->HasAura(SPELL_WARRIOR_GLYPH_OF_THE_BLAZING_TRAIL))
            spellId = SPELL_WARRIOR_CHARGE_EFFECT_BLAZING_TRAIL;

        GetCaster()->CastSpell(GetHitUnit(), spellId, true);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_warr_charge::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

// 126661 - Warrior Charge Drop Fire Periodic
class spell_warr_charge_drop_fire_periodic : public AuraScript
{
    PrepareAuraScript(spell_warr_charge_drop_fire_periodic);

    void DropFireVisual(AuraEffect const* aurEff)
    {
        PreventDefaultAction();
        if (GetTarget()->IsSplineEnabled())
        {
            for (uint32 i = 0; i < 5; ++i)
            {
                int32 timeOffset = 6 * i * aurEff->GetPeriod() / 25;
                Movement::Location loc = GetTarget()->movespline->ComputePosition(timeOffset);
                GetTarget()->SendPlaySpellVisual(Position(loc.x, loc.y, loc.z), 0.f, SPELL_VISUAL_BLAZING_CHARGE, 0, 0, 1.f, true);
            }
        }
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_warr_charge_drop_fire_periodic::DropFireVisual, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
    }
};

// 198337 - Charge Effect (dropping Blazing Trail)
// 218104 - Charge Effect
class spell_warr_charge_effect : public SpellScript
{
    PrepareSpellScript(spell_warr_charge_effect);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo
        ({
            SPELL_WARRIOR_CHARGE_PAUSE_RAGE_DECAY,
            SPELL_WARRIOR_CHARGE_ROOT_EFFECT,
            SPELL_WARRIOR_CHARGE_SLOW_EFFECT
        });
    }

    void HandleCharge(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        caster->CastSpell(caster, SPELL_WARRIOR_CHARGE_PAUSE_RAGE_DECAY, CastSpellExtraArgs(TRIGGERED_FULL_MASK).AddSpellMod(SPELLVALUE_BASE_POINT0, 0));
        caster->CastSpell(target, SPELL_WARRIOR_CHARGE_ROOT_EFFECT, true);
        caster->CastSpell(target, SPELL_WARRIOR_CHARGE_SLOW_EFFECT, true);
    }

    void Register() override
    {
        OnEffectLaunchTarget += SpellEffectFn(spell_warr_charge_effect::HandleCharge, EFFECT_0, SPELL_EFFECT_CHARGE);
    }
};

// 167105 - Colossus Smash 7.1.5
class spell_warr_colossus_smash : public SpellScript
{
    PrepareSpellScript(spell_warr_colossus_smash);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_WARRIOR_COLOSSUS_SMASH_EFFECT });
    }

    void HandleOnHit()
    {
        if (Unit* target = GetHitUnit())
            GetCaster()->CastSpell(target, SPELL_WARRIOR_COLOSSUS_SMASH_EFFECT, true);
    }

    void Register() override
    {
        OnHit += SpellHitFn(spell_warr_colossus_smash::HandleOnHit);
    }
};

// 6544 - Heroic leap
class spell_warr_heroic_leap : public SpellScript
{
    PrepareSpellScript(spell_warr_heroic_leap);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_WARRIOR_HEROIC_LEAP_JUMP });
    }

    SpellCastResult CheckElevation()
    {
        if (WorldLocation const* dest = GetExplTargetDest())
        {
            if (GetCaster()->HasUnitMovementFlag(MOVEMENTFLAG_ROOT))
                return SPELL_FAILED_ROOTED;

            if (GetCaster()->GetMap()->Instanceable())
            {
                float range = GetSpellInfo()->GetMaxRange(true, GetCaster()) * 1.5f;

                PathGenerator generatedPath(GetCaster());
                generatedPath.SetPathLengthLimit(range);

                bool result = generatedPath.CalculatePath(dest->GetPositionX(), dest->GetPositionY(), dest->GetPositionZ(), false);
                if (generatedPath.GetPathType() & PATHFIND_SHORT)
                    return SPELL_FAILED_OUT_OF_RANGE;
                else if (!result || generatedPath.GetPathType() & PATHFIND_NOPATH)
                    return SPELL_FAILED_NOPATH;
            }
            else if (dest->GetPositionZ() > GetCaster()->GetPositionZ() + 4.0f)
                return SPELL_FAILED_NOPATH;

            return SPELL_CAST_OK;
        }

        return SPELL_FAILED_NO_VALID_TARGETS;
    }

    void HandleDummy(SpellEffIndex /*effIndex*/)
    {
        if (WorldLocation* dest = GetHitDest())
            GetCaster()->CastSpell(*dest, SPELL_WARRIOR_HEROIC_LEAP_JUMP, true);

        // Bounding Stride
        if (GetCaster()->HasAura(202163))
            GetCaster()->CastSpell(GetCaster(), 202164, true);
    }

    void Register() override
    {
        OnCheckCast += SpellCheckCastFn(spell_warr_heroic_leap::CheckElevation);
        OnEffectHit += SpellEffectFn(spell_warr_heroic_leap::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

// Heroic Leap (triggered by Heroic Leap (6544)) - 178368
class spell_warr_heroic_leap_jump : public SpellScript
{
    PrepareSpellScript(spell_warr_heroic_leap_jump);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo(
        {
            SPELL_WARRIOR_GLYPH_OF_HEROIC_LEAP,
            SPELL_WARRIOR_GLYPH_OF_HEROIC_LEAP_BUFF,
            SPELL_WARRIOR_IMPROVED_HEROIC_LEAP,
            SPELL_WARRIOR_TAUNT
        });
    }

    void AfterJump(SpellEffIndex /*effIndex*/)
    {
        if (GetCaster()->HasAura(SPELL_WARRIOR_GLYPH_OF_HEROIC_LEAP))
            GetCaster()->CastSpell(GetCaster(), SPELL_WARRIOR_GLYPH_OF_HEROIC_LEAP_BUFF, true);
        if (GetCaster()->HasAura(SPELL_WARRIOR_IMPROVED_HEROIC_LEAP))
            GetCaster()->GetSpellHistory()->ResetCooldown(SPELL_WARRIOR_TAUNT, true);
    }

    void Register() override
    {
        OnEffectHit += SpellEffectFn(spell_warr_heroic_leap_jump::AfterJump, EFFECT_1, SPELL_EFFECT_JUMP_DEST);
    }
};

// 202168 - Impending Victory
class spell_warr_impending_victory : public SpellScript
{
    PrepareSpellScript(spell_warr_impending_victory);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_WARRIOR_IMPENDING_VICTORY_HEAL });
    }

    void HandleAfterCast()
    {
        Unit* caster = GetCaster();
        caster->CastSpell(caster, SPELL_WARRIOR_IMPENDING_VICTORY_HEAL, true);
        caster->RemoveAurasDueToSpell(SPELL_WARRIOR_VICTORIOUS);
    }

    void Register() override
    {
        AfterCast += SpellCastFn(spell_warr_impending_victory::HandleAfterCast);
    }
};

// 5246 - Intimidating Shout
class spell_warr_intimidating_shout : public SpellScript
{
    PrepareSpellScript(spell_warr_intimidating_shout);

    void FilterTargets(std::list<WorldObject*>& unitList)
    {
        unitList.remove(GetExplTargetWorldObject());
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_warr_intimidating_shout::FilterTargets, EFFECT_1, TARGET_UNIT_SRC_AREA_ENEMY);
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_warr_intimidating_shout::FilterTargets, EFFECT_2, TARGET_UNIT_SRC_AREA_ENEMY);
    }
};

// 70844 - Item - Warrior T10 Protection 4P Bonus
class spell_warr_item_t10_prot_4p_bonus : public AuraScript
{
    PrepareAuraScript(spell_warr_item_t10_prot_4p_bonus);

    bool Validate(SpellInfo const* spellInfo) override
    {
        return ValidateSpellInfo({ SPELL_WARRIOR_STOICISM })
            && spellInfo->GetEffects().size() > EFFECT_1;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();

        Unit* target = eventInfo.GetActionTarget();
        int32 bp0 = CalculatePct(target->GetMaxHealth(), GetEffectInfo(EFFECT_1).CalcValue());
        CastSpellExtraArgs args(TRIGGERED_FULL_MASK);
        args.AddSpellBP0(bp0);
        target->CastSpell(nullptr, SPELL_WARRIOR_STOICISM, args);
    }

    void Register() override
    {
        OnProc += AuraProcFn(spell_warr_item_t10_prot_4p_bonus::HandleProc);
    }
};

// 12294 - Mortal Strike 7.1.5
class spell_warr_mortal_strike : public SpellScript
{
    PrepareSpellScript(spell_warr_mortal_strike);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_WARRIOR_MORTAL_WOUNDS });
    }

    void HandleDummy(SpellEffIndex /*effIndex*/)
    {
        if (Unit* target = GetHitUnit())
            GetCaster()->CastSpell(target, SPELL_WARRIOR_MORTAL_WOUNDS, true);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_warr_mortal_strike::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

// 97462 - Rallying Cry
class spell_warr_rallying_cry : public SpellScript
{
    PrepareSpellScript(spell_warr_rallying_cry);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_WARRIOR_RALLYING_CRY });
    }

    bool Load() override
    {
        return GetCaster()->GetTypeId() ==  TYPEID_PLAYER;
    }

    void HandleScript(SpellEffIndex /*effIndex*/)
    {
        CastSpellExtraArgs args(TRIGGERED_FULL_MASK);
        args.AddSpellMod(SPELLVALUE_BASE_POINT0, int32(GetHitUnit()->CountPctFromMaxHealth(GetEffectValue())));

        GetCaster()->CastSpell(GetHitUnit(), SPELL_WARRIOR_RALLYING_CRY, args);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_warr_rallying_cry::HandleScript, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

// 46968 - Shockwave
class spell_warr_shockwave : public SpellScript
{
    PrepareSpellScript(spell_warr_shockwave);

    bool Validate(SpellInfo const* spellInfo) override
    {
        if (!ValidateSpellInfo({ SPELL_WARRIOR_SHOCKWAVE, SPELL_WARRIOR_SHOCKWAVE_STUN }))
            return false;

        return spellInfo->GetEffects().size() > EFFECT_3;
    }

    bool Load() override
    {
        return GetCaster()->GetTypeId() == TYPEID_PLAYER;
    }

    void HandleStun(SpellEffIndex /*effIndex*/)
    {
        GetCaster()->CastSpell(GetHitUnit(), SPELL_WARRIOR_SHOCKWAVE_STUN, true);
        ++_targetCount;
    }

    // Cooldown reduced by 20 sec if it strikes at least 3 targets.
    void HandleAfterCast()
    {
        if (_targetCount >= uint32(GetEffectInfo(EFFECT_0).CalcValue()))
            GetCaster()->ToPlayer()->GetSpellHistory()->ModifyCooldown(GetSpellInfo()->Id, Seconds(-GetEffectInfo(EFFECT_3).CalcValue()));
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_warr_shockwave::HandleStun, EFFECT_0, SPELL_EFFECT_DUMMY);
        AfterCast += SpellCastFn(spell_warr_shockwave::HandleAfterCast);
    }

    uint32 _targetCount = 0;
};

// 107570 - Storm Bolt
    class spell_warr_storm_bolt : public SpellScript
    {
        PrepareSpellScript(spell_warr_storm_bolt);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            return ValidateSpellInfo
            ({
                SPELL_WARRIOR_STORM_BOLT_STUN
            });
        }

        void HandleOnHit(SpellEffIndex /*effIndex*/)
        {
            GetCaster()->CastSpell(GetHitUnit(), SPELL_WARRIOR_STORM_BOLT_STUN, true);
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_warr_storm_bolt::HandleOnHit, EFFECT_1, SPELL_EFFECT_DUMMY);
        }
    };

// 52437 - Sudden Death
class spell_warr_sudden_death : public AuraScript
{
    PrepareAuraScript(spell_warr_sudden_death);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_WARRIOR_COLOSSUS_SMASH });
    }

    void HandleApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        // Remove cooldown on Colossus Smash
        if (Player* player = GetTarget()->ToPlayer())
            player->GetSpellHistory()->ResetCooldown(SPELL_WARRIOR_COLOSSUS_SMASH, true);
    }

    void Register() override
    {
        AfterEffectApply += AuraEffectRemoveFn(spell_warr_sudden_death::HandleApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL); // correct?
    }
};

// 12328, 18765, 35429 - Sweeping Strikes
class spell_warr_sweeping_strikes : public AuraScript
{
    PrepareAuraScript(spell_warr_sweeping_strikes);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_WARRIOR_SWEEPING_STRIKES_EXTRA_ATTACK_1, SPELL_WARRIOR_SWEEPING_STRIKES_EXTRA_ATTACK_2 });
    }

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        _procTarget = eventInfo.GetActor()->SelectNearbyTarget(eventInfo.GetProcTarget());
        return _procTarget != nullptr;
    }

    void HandleProc(AuraEffect* aurEff, ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();
        if (DamageInfo* damageInfo = eventInfo.GetDamageInfo())
        {
            SpellInfo const* spellInfo = damageInfo->GetSpellInfo();
            if (spellInfo && (spellInfo->Id == SPELL_WARRIOR_BLADESTORM_PERIODIC_WHIRLWIND || (spellInfo->Id == SPELL_WARRIOR_EXECUTE && !_procTarget->HasAuraState(AURA_STATE_WOUNDED_20_PERCENT))))
            {
                // If triggered by Execute (while target is not under 20% hp) or Bladestorm deals normalized weapon damage
                GetTarget()->CastSpell(_procTarget, SPELL_WARRIOR_SWEEPING_STRIKES_EXTRA_ATTACK_2, aurEff);
            }
            else
            {
                CastSpellExtraArgs args(aurEff);
                args.AddSpellMod(SPELLVALUE_BASE_POINT0, damageInfo->GetDamage());
                GetTarget()->CastSpell(_procTarget, SPELL_WARRIOR_SWEEPING_STRIKES_EXTRA_ATTACK_1, args);
            }
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_warr_sweeping_strikes::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_warr_sweeping_strikes::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }

    Unit* _procTarget = nullptr;
};

// 215538 - Trauma
class spell_warr_trauma : public AuraScript
{
    PrepareAuraScript(spell_warr_trauma);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_WARRIOR_TRAUMA_EFFECT });
    }

    void HandleProc(AuraEffect* aurEff, ProcEventInfo& eventInfo)
    {
        Unit* target = eventInfo.GetActionTarget();
        //Get 25% of damage from the spell casted (Slam & Whirlwind) plus Remaining Damage from Aura
        int32 damage = int32(CalculatePct(eventInfo.GetDamageInfo()->GetDamage(), aurEff->GetAmount()) / sSpellMgr->AssertSpellInfo(SPELL_WARRIOR_TRAUMA_EFFECT, GetCastDifficulty())->GetMaxTicks());
        CastSpellExtraArgs args(TRIGGERED_FULL_MASK);
        args.AddSpellMod(SPELLVALUE_BASE_POINT0, damage);
        GetCaster()->CastSpell(target, SPELL_WARRIOR_TRAUMA_EFFECT, args);
    }

    void Register() override
    {
        OnEffectProc += AuraEffectProcFn(spell_warr_trauma::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

// 28845 - Cheat Death
class spell_warr_t3_prot_8p_bonus : public AuraScript
{
    PrepareAuraScript(spell_warr_t3_prot_8p_bonus);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetActionTarget()->HealthBelowPct(20))
            return true;

        DamageInfo* damageInfo = eventInfo.GetDamageInfo();
        if (damageInfo && damageInfo->GetDamage())
            if (GetTarget()->HealthBelowPctDamaged(20, damageInfo->GetDamage()))
                return true;

        return false;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_warr_t3_prot_8p_bonus::CheckProc);
    }
};

// 32215 - Victorious State
class spell_warr_victorious_state : public AuraScript
{
    PrepareAuraScript(spell_warr_victorious_state);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_WARRIOR_IMPENDING_VICTORY });
    }

    void HandleOnProc(AuraEffect* /*aurEff*/, ProcEventInfo& procInfo)
    {
        if (procInfo.GetActor()->GetTypeId() == TYPEID_PLAYER && procInfo.GetActor()->ToPlayer()->GetPrimarySpecialization() == TALENT_SPEC_WARRIOR_FURY)
            PreventDefaultAction();

        procInfo.GetActor()->GetSpellHistory()->ResetCooldown(SPELL_WARRIOR_IMPENDING_VICTORY, true);
    }

    void Register() override
    {
        OnEffectProc += AuraEffectProcFn(spell_warr_victorious_state::HandleOnProc, EFFECT_0, SPELL_AURA_PROC_TRIGGER_SPELL);
    }
};

// 34428 - Victory Rush
class spell_warr_victory_rush : public SpellScript
{
    PrepareSpellScript(spell_warr_victory_rush);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo
        ({
            SPELL_WARRIOR_VICTORIOUS,
            SPELL_WARRIOR_VICTORY_RUSH_HEAL
        });
    }

    void HandleHeal()
    {
        Unit* caster = GetCaster();
        caster->CastSpell(caster, SPELL_WARRIOR_VICTORY_RUSH_HEAL, true);
        caster->RemoveAurasDueToSpell(SPELL_WARRIOR_VICTORIOUS);
    }

    void Register() override
    {
        AfterCast += SpellCastFn(spell_warr_victory_rush::HandleHeal);
    }
};
// Enrage - 184361
class spell_warr_enrage : public SpellScriptLoader
{
public:
    spell_warr_enrage() : SpellScriptLoader("spell_warr_enrage") {}

    class spell_warr_enrage_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_warr_enrage_AuraScript);

        bool CheckProc(ProcEventInfo& eventInfo)
        {
            if (eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == SPELL_WARRIOR_BLOODTHIRST_DAMAGE && roll_chance_i(sSpellMgr->GetSpellInfo(SPELL_WARRIOR_ENRAGE_AURA)->GetEffect(EFFECT_0).BasePoints))
                return true;

            return false;
        }

        void HandleProc(ProcEventInfo& eventInfo)
        {
            if (Unit* caster = GetCaster())
                caster->CastSpell(caster, SPELL_WARRIOR_ENRAGE_AURA, true);
        }

        void Register() override
        {
            OnProc += AuraProcFn(spell_warr_enrage_AuraScript::HandleProc);
            DoCheckProc += AuraCheckProcFn(spell_warr_enrage_AuraScript::CheckProc);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_warr_enrage_AuraScript();
    }
};

// Rampage damage dealers - 218617, 184707, 184709, 201364, 201363
class spell_warr_rampage : public SpellScriptLoader
{
public:
    spell_warr_rampage() : SpellScriptLoader("spell_warr_rampage") { }

    class spell_warr_rampage_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_warr_rampage_SpellScript);

        void HandleAuras()
        {
            Unit* caster = GetCaster();
            if (!caster)
                return;

            if (Aura* enrage = caster->GetAura(SPELL_WARRIOR_ENRAGE_AURA))
                enrage->RefreshDuration();
            else
                caster->CastSpell(caster, SPELL_WARRIOR_ENRAGE_AURA, true);
        }

        void Register() override
        {
            OnCast += SpellCastFn(spell_warr_rampage_SpellScript::HandleAuras);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_warr_rampage_SpellScript();
    }
};

class spell_warr_raging_blow : public SpellScriptLoader
{
public:
    spell_warr_raging_blow() : SpellScriptLoader("spell_warr_raging_blow") { }

    class spell_warr_raging_blow_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_warr_raging_blow_SpellScript);

        void HandleOnHit()
        {
            if (Unit* caster = GetCaster())
            {
                if (roll_chance_i(GetSpellInfo()->GetEffect(EFFECT_0).BasePoints))
                {
                    caster->GetSpellHistory()->RestoreCharge(GetSpellInfo()->ChargeCategoryId);
                    caster->CastSpell(caster, SPELL_WARRIOR_ALLOW_RAGING_BLOW, true);
                }
            }
        }

        void Register() override
        {
            OnHit += SpellHitFn(spell_warr_raging_blow_SpellScript::HandleOnHit);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_warr_raging_blow_SpellScript();
    }
};


// 95738 - Bladestorm Offhand
class spell_warr_bladestorm_offhand : public SpellScriptLoader
{
public:
	spell_warr_bladestorm_offhand() : SpellScriptLoader("spell_warr_bladestorm_offhand") { }

	class spell_warr_bladestorm_offhand_SpellScript : public SpellScript
	{
		PrepareSpellScript(spell_warr_bladestorm_offhand_SpellScript);

		void HandleOnHit(SpellEffIndex effIndex)
		{
            if (!GetCaster()->ToPlayer())
                return;

            uint32 _spec = GetCaster()->ToPlayer()->GetSpecializationId();
			if (_spec != TALENT_SPEC_WARRIOR_FURY) //only fury warriors should deal damage with offhand
			{
				PreventHitDamage();
				PreventHitDefaultEffect(effIndex);
				PreventHitEffect(effIndex);
			}
		}

		void Register() override
		{
			OnEffectHitTarget += SpellEffectFn(spell_warr_bladestorm_offhand_SpellScript::HandleOnHit, EFFECT_0, SPELL_EFFECT_NORMALIZED_WEAPON_DMG);
			OnEffectHitTarget += SpellEffectFn(spell_warr_bladestorm_offhand_SpellScript::HandleOnHit, EFFECT_1, SPELL_EFFECT_WEAPON_PERCENT_DAMAGE);
		}
	};

	SpellScript* GetSpellScript() const override
	{
		return new spell_warr_bladestorm_offhand_SpellScript();
	}
};

// 227847 - Bladestorm
// Last Update 8.0.1 Build 28153
class aura_warr_bladestorm : public AuraScript
{
    PrepareAuraScript(aura_warr_bladestorm);

    void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* caster = GetCaster())
            if (caster->HasAura(SPELL_WARRIOR_GATHERING_STORM_PERIODIC))
                caster->RemoveAura(SPELL_WARRIOR_GATHERING_STORM_PERIODIC);
    }

    void Register() override
    {
        OnEffectRemove += AuraEffectRemoveFn(aura_warr_bladestorm::OnRemove, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL, AURA_EFFECT_HANDLE_REAL);
    }
};

void AddSC_warrior_spell_scripts()
{
    RegisterSpellScript(spell_warr_bloodthirst);
    RegisterSpellScript(spell_warr_charge);
    RegisterSpellScript(spell_warr_charge_drop_fire_periodic);
    RegisterSpellScript(spell_warr_charge_effect);
    RegisterSpellScript(spell_warr_colossus_smash);
    RegisterSpellScript(spell_warr_heroic_leap);
    RegisterSpellScript(spell_warr_heroic_leap_jump);
    RegisterSpellScript(spell_warr_impending_victory);
    RegisterSpellScript(spell_warr_intimidating_shout);
    RegisterSpellScript(spell_warr_item_t10_prot_4p_bonus);
    RegisterSpellScript(spell_warr_mortal_strike);
    RegisterSpellScript(spell_warr_rallying_cry);
    RegisterSpellScript(spell_warr_shockwave);
    RegisterSpellScript(spell_warr_storm_bolt);
    RegisterSpellScript(spell_warr_sudden_death);
    RegisterSpellScript(spell_warr_sweeping_strikes);
    RegisterSpellScript(spell_warr_trauma);
    RegisterSpellScript(spell_warr_t3_prot_8p_bonus);
    RegisterSpellScript(spell_warr_victorious_state);
    RegisterSpellScript(spell_warr_victory_rush);
    new spell_warr_enrage();
    new spell_warr_rampage();
    new spell_warr_raging_blow();
    new spell_warr_bladestorm_offhand();
    RegisterSpellScript(aura_warr_bladestorm);
}
