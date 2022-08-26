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

#include "spell_warrior.h"

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
    SPELL_WARRIOR_EXECUTE                           = 163201,
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

        // Vicious Contempt conduit
        if (target->HealthBelowPct(36))
            if (auto eff = caster->GetAuraEffect(337302, EFFECT_0))
                if (eff->ConduitRankEntry)
                    AddPct(damage, eff->ConduitRankEntry->AuraPointsOverride);

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

// Heroic Leap (triggered by Heroic Leap (6544)) - 178368
class spell_warr_heroic_leap_jump : public SpellScript
{
    PrepareSpellScript(spell_warr_heroic_leap_jump);

    void HandleJumpCharge(Optional<JumpArrivalCastArgs>& arrivalCast)
    {
        auto caster = GetCaster();
        if (!caster)
            return;
        if (!arrivalCast.has_value())
        {
            arrivalCast.emplace();
            arrivalCast->Callbacks.push([caster]()
            {
                caster->CastSpell(*caster, SPELL_WARRIOR_HEROIC_LEAP_DAMAGE, true);
                if (caster->HasAura(SPELL_WARRIOR_GLYPH_OF_HEROIC_LEAP))
                    caster->CastSpell(caster, SPELL_WARRIOR_GLYPH_OF_HEROIC_LEAP_BUFF, true);
                if (caster->HasAura(SPELL_WARRIOR_IMPROVED_HEROIC_LEAP))
                    caster->GetSpellHistory()->ResetCooldown(SPELL_WARRIOR_TAUNT, true);

                if (caster->HasAura(SPELL_WARRIOR_BOUNDING_STRIDE))
                    caster->CastSpell(caster, SPELL_WARRIOR_BOUNDING_STRIDE_SPEED, true);
            });
        }
    }

    void Register() override
    {
        OnJumpCharge += SpellJumpChargeFn(spell_warr_heroic_leap_jump::HandleJumpCharge);
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

// kyrian spear - 307963  tether
// 17984
struct at_warr_kyrian_spear : AreaTriggerAI
{
    at_warr_kyrian_spear(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger) { }

    enum Spear
    {
        Tether = 307963,
        Visual = 308062,
    };

    ObjectGuid triggerGuid;

    void OnCreate() override
    {
        if (auto caster = at->GetOwner())
        {
            if (auto tempSumm = caster->SummonCreature(WORLD_TRIGGER, at->GetPosition(), TEMPSUMMON_TIMED_DESPAWN, 4s))
            {
                tempSumm->SetFaction(caster->GetFaction());
                tempSumm->SetOwnerGUID(caster->GetGUID());
                PhasingHandler::InheritPhaseShift(tempSumm, caster);
                triggerGuid = tempSumm->GetGUID();
            }
        }
    }

    void OnUnitEnter(Unit* unit) override
    {
        if (auto caster = at->GetOwner())
        {
            if (caster == unit)
                if (caster->HasAura(Warrior::eLegendary::ElysianMight))
                    caster->CastSpell(caster, Warrior::eLegendary::ElsyianMightCritBuff, CastSpellExtraArgs(true).AddSpellMod(SpellValueMod::SPELLVALUE_DURATION, at->GetDuration()));

            if (caster->IsValidAttackTarget(unit))
                if (auto trigger = ObjectAccessor::GetCreature(*at, triggerGuid))
                    unit->CastSpell(*trigger, Visual, true);
        }
    }

    void OnUnitExit(Unit* unit) override
    {
        if (auto caster = at->GetOwner())
        {
            if (caster->IsValidAttackTarget(unit))
                if (auto trigger = ObjectAccessor::GetCreature(*at, triggerGuid))
                    unit->CastSpell(trigger, Tether, true);

            caster->RemoveAurasDueToSpell(Warrior::eLegendary::ElsyianMightCritBuff);
        }
    }

    void OnRemove() override
    {
        for (auto guid : at->GetInsideUnits())
            if (auto unit = ObjectAccessor::GetCreature(*at, guid))
                unit->RemoveAurasDueToSpell(Visual);
    }
};

// 21902
struct at_warr_ancient_aftershock : public AreaTriggerAI
{
    at_warr_ancient_aftershock(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger) { }

    enum Aftershock
    {
        Stun = 326062,
        Energize = 326076,
    };

    int32 ticks = 0;

    void OnUpdate(uint32 diff)
    {
        if (ticks <= 0)
        {
            ticks = 100; ///< CUSTOM
            if (auto caster = at->GetOwner())
            {
                uint32 targetCount = 5;
                for (auto guid : at->GetInsideUnits())
                {
                    if (auto unit = ObjectAccessor::GetCreature(*at, guid))
                    {
                        if (!caster->IsValidAttackTarget(unit))
                            continue;

                        if (--targetCount == 0)
                            break;

                        caster->CastSpell(unit, Stun, true);
                        caster->CastSpell(caster, Energize, true);

                        if (caster->HasAura(Warrior::eLegendary::NaturesFury))
                            caster->CastSpell(unit, Warrior::eLegendary::NaturesFuryDmg, true);
                    }
                }
            }
        }
        else
            ticks -= diff;
    }
};

// 97462 Commanding Shout 7.3.5
class spell_warr_commanding_shout : public SpellScript
{
    PrepareSpellScript(spell_warr_commanding_shout);

    void HandleScript(SpellEffIndex /*effIndex*/)
    {
        if (Unit* target = GetHitUnit())
            GetCaster()->CastSpell(target, SPELL_WARRIOR_COMMANDING_SHOUT, true);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_warr_commanding_shout::HandleScript, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

// Jump to Skyhold Jump - 192085
class spell_warr_jump_to_skyhold : public SpellScriptLoader
{
public:
    spell_warr_jump_to_skyhold() : SpellScriptLoader("spell_warr_jump_to_skyhold") {}

    class spell_warr_jump_to_skyhold_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_warr_jump_to_skyhold_SpellScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_WARRIOR_JUMP_TO_SKYHOLD_TELEPORT))
                return false;
            return true;
        }

        void HandleJump(SpellEffIndex effIndex)
        {
            PreventHitDefaultEffect(effIndex);

            if (Unit* caster = GetCaster())
            {
                float pos_x = caster->GetPositionX();
                float pos_y = caster->GetPositionY();
                float pos_z = caster->GetPositionZ() + 30.0f;

                JumpArrivalCastArgs arrivalCast;
                arrivalCast.SpellId = SPELL_WARRIOR_JUMP_TO_SKYHOLD_TELEPORT;
                arrivalCast.Target = caster->GetGUID();
                caster->GetMotionMaster()->MoveJump(pos_x, pos_y, pos_z, caster->GetOrientation(), 20.f, 20.f, EVENT_JUMP, false, &arrivalCast);

                caster->RemoveAurasDueToSpell(SPELL_WARRIOR_JUMP_TO_SKYHOLD_AURA);
            }
        }

        void Register() override
        {
            OnEffectLaunch += SpellEffectFn(spell_warr_jump_to_skyhold_SpellScript::HandleJump, EFFECT_0, SPELL_EFFECT_JUMP_DEST);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_warr_jump_to_skyhold_SpellScript();
    }
};

// Whirlwind - 190411
class spell_warr_whirlwind : public SpellScript
{
    PrepareSpellScript(spell_warr_whirlwind);

    void HandleProc()
    {
        if (Unit* caster = GetCaster())
        {
            if (Aura* aura = caster->GetAura(SPELL_WARRIOR_MEAT_CLEAVER_PROC))
                aura->ModStackAmount(1);
            else
            {
                caster->CastSpell(caster, SPELL_WARRIOR_MEAT_CLEAVER_PROC, true);
                if (Aura* aura = caster->GetAura(SPELL_WARRIOR_MEAT_CLEAVER_PROC))
                    aura->ModStackAmount(1);
            }
        }
    }

    void HandleHit()
    {
        if (Unit* caster = GetCaster())
        {
            if (caster->HasAura(SPELL_WARRIOR_MEAT_CLEAVER_ENERGIZE))
                caster->RewardRage(1);
        }
    }

    void HandleAfterCast()
    {
        if (Unit* caster = GetCaster())
        {
            caster->CastCustomSpell(SPELL_WARRIOR_WHIRLWIND_ENERGIZE, SPELLVALUE_BASE_POINT0, 30, caster, true);
            caster->Variables.Set("rage", 30);
            if (caster->HasAura(SPELL_WARRIOR_WRECKING_BALL_EFFECT))
                caster->RemoveAura(SPELL_WARRIOR_WRECKING_BALL_EFFECT);
        }
    }

    void Register() override
    {
        OnCast += SpellCastFn(spell_warr_whirlwind::HandleProc);
        OnHit += SpellHitFn(spell_warr_whirlwind::HandleHit);
        AfterCast += SpellCastFn(spell_warr_whirlwind::HandleAfterCast);
    }
};

// Meat Cleaver - 12950
class spell_warr_meat_cleaver : public SpellScriptLoader
{
public:
    spell_warr_meat_cleaver() : SpellScriptLoader("spell_warr_meat_cleaver") {}

    class spell_warr_meat_cleaver_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_warr_meat_cleaver_AuraScript);

        bool CheckProc(ProcEventInfo& /*eventInfo*/)
        {
            return false;
        }

        void Register() override
        {
            DoCheckProc += AuraCheckProcFn(spell_warr_meat_cleaver_AuraScript::CheckProc);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_warr_meat_cleaver_AuraScript();
    }
};

// Taste for Blood - 206333
class spell_warr_taste_for_blood : public SpellScriptLoader
{
public:
    spell_warr_taste_for_blood() : SpellScriptLoader("spell_warr_taste_for_blood") {}

    class spell_warr_taste_for_blood_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_warr_taste_for_blood_AuraScript);

        bool CheckProc(ProcEventInfo& eventInfo)
        {
            if ((eventInfo.GetHitMask() & PROC_HIT_CRITICAL) &&
                eventInfo.GetSpellInfo()->Id == SPELL_WARRIOR_BLOODTHIRST_DAMAGE)
            {
                GetAura()->SetDuration(0);
                return true;
            }
            return false;
        }

        void Register() override
        {
            DoCheckProc += AuraCheckProcFn(spell_warr_taste_for_blood_AuraScript::CheckProc);
            //OnProc += AuraProcFn(spell_warr_taste_for_blood_AuraScript::HandleProc);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_warr_taste_for_blood_AuraScript();
    }
};

// Enrage Aura - 184362
class spell_warr_enrage_aura : public SpellScriptLoader
{
public:
    spell_warr_enrage_aura() : SpellScriptLoader("spell_warr_enrage_aura") {}

    class spell_warr_enrage_aura_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_warr_enrage_aura_AuraScript);

        void HandleApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if (Unit* caster = GetCaster())
                if (caster->HasAura(SPELL_WARRIOR_ENDLESS_RAGE))
                    caster->CastSpell(caster, SPELL_WARRIOR_ENDLESS_RAGE_ENERGIZE, true);
        }

        void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            Unit* caster = GetCaster();

            caster->RemoveAurasDueToSpell(SPELL_WARRIOR_UNCHACKLED_FURY);
        }

        void Register() override
        {
            OnEffectApply += AuraEffectApplyFn(spell_warr_enrage_aura_AuraScript::HandleApply, EFFECT_0, SPELL_AURA_MELEE_SLOW, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
            OnEffectRemove += AuraEffectRemoveFn(spell_warr_enrage_aura_AuraScript::HandleRemove, EFFECT_0, SPELL_AURA_MELEE_SLOW, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_warr_enrage_aura_AuraScript();
    }
};

// 59725 - Improved Spell Reflection
class spell_warr_improved_spell_reflection : public SpellScriptLoader
{
public:
    spell_warr_improved_spell_reflection() : SpellScriptLoader("spell_warr_improved_spell_reflection") { }

    class spell_warr_improved_spell_reflection_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_warr_improved_spell_reflection_SpellScript);

        void FilterTargets(std::list<WorldObject*>& unitList)
        {
            if (GetCaster())
                unitList.remove(GetCaster());
        }

        void Register() override
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_warr_improved_spell_reflection_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_CASTER_AREA_PARTY);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_warr_improved_spell_reflection_SpellScript();
    }
};

/// Updated 4.3.4
// 12975 - Last Stand
class spell_warr_last_stand : public SpellScriptLoader
{
public:
    spell_warr_last_stand() : SpellScriptLoader("spell_warr_last_stand") { }

    class spell_warr_last_stand_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_warr_last_stand_SpellScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_WARRIOR_LAST_STAND_TRIGGERED))
                return false;
            return true;
        }

        void HandleDummy(SpellEffIndex /*effIndex*/)
        {
            Unit* caster = GetCaster();
            int32 healthModSpellBasePoints0 = int32(caster->CountPctFromMaxHealth(GetEffectValue()));
            caster->CastCustomSpell(caster, SPELL_WARRIOR_LAST_STAND_TRIGGERED, &healthModSpellBasePoints0, NULL, NULL, true, NULL);
        }

        void Register() override
        {
            // add dummy effect spell handler to Last Stand
            OnEffectHit += SpellEffectFn(spell_warr_last_stand_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_warr_last_stand_SpellScript();
    }
};

// 7384 - Overpower
class spell_warr_overpower : public SpellScript
{
    PrepareSpellScript(spell_warr_overpower);

    void HandleEffect(SpellEffIndex /*effIndex*/)
    {
        if (!GetCaster())
            return;

        uint32 spellId = 0;
        if (GetCaster()->HasAura(SPELL_WARRIOR_UNRELENTING_ASSAULT_RANK_1))
            spellId = SPELL_WARRIOR_UNRELENTING_ASSAULT_TRIGGER_1;
        else if (GetCaster()->HasAura(SPELL_WARRIOR_UNRELENTING_ASSAULT_RANK_2))
            spellId = SPELL_WARRIOR_UNRELENTING_ASSAULT_TRIGGER_2;

        if (!spellId)
            return;

        if (Player* target = GetHitPlayer())
            if (target->IsNonMeleeSpellCast(false, false, true)) // UNIT_STATE_CASTING should not be used here, it's present during a tick for instant casts
                target->CastSpell(target, spellId, true);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_warr_overpower::HandleEffect, EFFECT_0, SPELL_EFFECT_ANY);
    }
};

// 7384 - Overpower Aura
class aura_warr_overpower : public AuraScript
{
    PrepareAuraScript(aura_warr_overpower);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == SPELL_WARRIOR_MORTAL_STRIKE)
            return true;

        return false;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_warr_overpower::CheckProc);
    }
};

// 94009 - Rend
class spell_warr_rend : public SpellScriptLoader
{
public:
    spell_warr_rend() : SpellScriptLoader("spell_warr_rend") { }

    class spell_warr_rend_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_warr_rend_AuraScript);

        void CalculateAmount(AuraEffect const* aurEff, int32& amount, bool& canBeRecalculated)
        {
            if (Unit* caster = GetCaster())
            {
                canBeRecalculated = false;

                // $0.25 * (($MWB + $mwb) / 2 + $AP / 14 * $MWS) bonus per tick
                float ap = caster->GetTotalAttackPowerValue(BASE_ATTACK);
                int32 mws = caster->getAttackTimer(BASE_ATTACK);
                float mwbMin = caster->GetWeaponDamageRange(BASE_ATTACK, MINDAMAGE);
                float mwbMax = caster->GetWeaponDamageRange(BASE_ATTACK, MAXDAMAGE);
                float mwb = ((mwbMin + mwbMax) / 2 + ap * mws / 14000) * 0.25f;
                amount += int32(caster->ApplyEffectModifiers(GetSpellInfo(), aurEff->GetEffIndex(), mwb));
            }
        }

        void Register() override
        {
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_warr_rend_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_warr_rend_AuraScript();
    }
};

// 20230 - Retaliation
class spell_warr_retaliation : public SpellScriptLoader
{
public:
    spell_warr_retaliation() : SpellScriptLoader("spell_warr_retaliation") { }

    class spell_warr_retaliation_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_warr_retaliation_AuraScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_WARRIOR_RETALIATION_DAMAGE))
                return false;
            return true;
        }

        bool CheckProc(ProcEventInfo& eventInfo)
        {
            // check attack comes not from behind and warrior is not stunned
            return GetTarget()->isInFront(eventInfo.GetActor(), float(M_PI)) && !GetTarget()->HasUnitState(UNIT_STATE_STUNNED);
        }

        void HandleEffectProc(AuraEffect* aurEff, ProcEventInfo& eventInfo)
        {
            PreventDefaultAction();
            GetTarget()->CastSpell(eventInfo.GetProcTarget(), SPELL_WARRIOR_RETALIATION_DAMAGE, CastSpellExtraArgs(true).SetTriggeringAura(aurEff));
        }

        void Register() override
        {
            DoCheckProc += AuraCheckProcFn(spell_warr_retaliation_AuraScript::CheckProc);
            OnEffectProc += AuraEffectProcFn(spell_warr_retaliation_AuraScript::HandleEffectProc, EFFECT_0, SPELL_AURA_DUMMY);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_warr_retaliation_AuraScript();
    }
};

// 64380, 65941 - Shattering Throw
class spell_warr_shattering_throw : public SpellScriptLoader
{
public:
    spell_warr_shattering_throw() : SpellScriptLoader("spell_warr_shattering_throw") { }

    class spell_warr_shattering_throw_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_warr_shattering_throw_SpellScript);

        void HandleDamage(SpellEffIndex eff)
        {
            if (auto caster = GetCaster())
            {
                if (auto player = caster->ToPlayer())
                {
                    // $damage=${($AP*1.0)*(1+$@versadmg)}
                    auto attackPower = caster->GetTotalAttackPowerValue(BASE_ATTACK);
                    float vers = player->m_activePlayerData->Versatility + player->m_activePlayerData->VersatilityBonus;
                    AddPct(attackPower, vers);

                    SetHitDamage(attackPower);
                }
            }
        }

        void HandleScript(SpellEffIndex effIndex)
        {
            PreventHitDefaultEffect(effIndex);

            // remove shields, will still display immune to damage part
            if (Unit* target = GetHitUnit())
                target->RemoveAurasWithMechanic(1 << MECHANIC_IMMUNE_SHIELD, AURA_REMOVE_BY_ENEMY_SPELL);
        }

        void Register() override
        {
            if (m_scriptSpellId == 64382)
                OnEffectHitTarget += SpellEffectFn(spell_warr_shattering_throw_SpellScript::HandleDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
            else
                OnEffectHitTarget += SpellEffectFn(spell_warr_shattering_throw_SpellScript::HandleScript, EFFECT_1, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_warr_shattering_throw_SpellScript();
    }
};

// 1464 - Slam
class spell_warr_slam : public SpellScript
{
    PrepareSpellScript(spell_warr_slam);

    void HandleDummy(SpellEffIndex /*effIndex*/)
    {
        // Crushing Assault
        if (Unit* caster = GetCaster())
        {
            if (Aura* aura = caster->GetAura(SPELL_WARRIOR_CRUSHING_ASSAULT_POWER))
            {
                int32 damage = GetHitDamage();
                SetHitDamage(damage + aura->GetEffect(EFFECT_0)->GetAmount());
            }

            caster->RemoveAurasDueToSpell(SPELL_WARRIOR_CRUSHING_ASSAULT_BUFF);
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_warr_slam::HandleDummy, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

// 29838 - Second Wind
class aura_warr_second_wind : public AuraScript
{
    PrepareAuraScript(aura_warr_second_wind);

    void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* caster = GetCaster())
        {
            caster->RemoveAura(SPELL_WARRIOR_SECOND_WIND_DAMAGED);
            caster->CastSpell(caster, SPELL_WARRIOR_SECOND_WIND_HEAL, true);
        }
    }

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetDamageInfo() && eventInfo.GetDamageInfo()->GetDamage() > 0)
            return true;

        return false;
    }

    void HandleProc(ProcEventInfo& /*eventInfo*/)
    {
        if (Unit* caster = GetCaster())
            caster->CastSpell(caster, SPELL_WARRIOR_SECOND_WIND_DAMAGED, true);
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(aura_warr_second_wind::OnApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
        DoCheckProc += AuraCheckProcFn(aura_warr_second_wind::CheckProc);
        OnProc += AuraProcFn(aura_warr_second_wind::HandleProc);
    }
};

// 202149 - Second Wind Damage
class aura_warr_second_wind_damaged : public AuraScript
{
    PrepareAuraScript(aura_warr_second_wind_damaged);

    void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* caster = GetCaster())
            caster->RemoveAura(SPELL_WARRIOR_SECOND_WIND_HEAL);
    }

    void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* caster = GetCaster())
            caster->CastSpell(caster, SPELL_WARRIOR_SECOND_WIND_HEAL, true);
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(aura_warr_second_wind_damaged::OnApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
        OnEffectRemove += AuraEffectRemoveFn(aura_warr_second_wind_damaged::OnRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

// 29725 - Sudden Death Talent / 280721 - Sudden Death Talent Fury
class aura_warr_sudden_death_talent : public AuraScript
{
    PrepareAuraScript(aura_warr_sudden_death_talent);

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (Unit* caster = GetCaster())
            if (GetSpellInfo()->Id == SPELL_WARRIOR_SUDDEN_DEATH_ARMS_TALENT)
                caster->CastSpell(caster, SPELL_WARRIOR_SUDDEN_DEATH, true);
            else
                caster->CastSpell(caster, SPELL_WARRIOR_SUDDEN_DEATH_FURY, true);
    }

    void Register() override
    {
        OnProc += AuraProcFn(aura_warr_sudden_death_talent::HandleProc);
    }
};

// 52437 - Sudden Death / 280776 - Sudden Death Fury
class aura_warr_sudden_death : public AuraScript
{
    PrepareAuraScript(aura_warr_sudden_death);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_warr_sudden_death::CheckProc);
    }
};

// 32216 - Victorious
// 82368 - Victorious
class spell_warr_victorious : public SpellScriptLoader
{
public:
    spell_warr_victorious() : SpellScriptLoader("spell_warr_victorious") { }

    class spell_warr_victorious_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_warr_victorious_AuraScript);

        void HandleEffectProc(AuraEffect* /*aurEff*/, ProcEventInfo& /*eventInfo*/)
        {
            PreventDefaultAction();
            GetTarget()->RemoveAura(GetId());
        }

        void Register() override
        {
            OnEffectProc += AuraEffectProcFn(spell_warr_victorious_AuraScript::HandleEffectProc, EFFECT_0, SPELL_AURA_DUMMY);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_warr_victorious_AuraScript();
    }
};

// 50720 - Vigilance
class spell_warr_vigilance : public SpellScriptLoader
{
public:
    spell_warr_vigilance() : SpellScriptLoader("spell_warr_vigilance") { }

    class spell_warr_vigilance_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_warr_vigilance_AuraScript);

    public:
        spell_warr_vigilance_AuraScript()
        {
            _procTarget = nullptr;
        }

    private:
        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_WARRIOR_VENGEANCE))
                return false;
            return true;
        }

        bool Load() override
        {
            _procTarget = NULL;
            return true;
        }

        void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if (Unit* caster = GetCaster())
            {
                if (caster->HasAura(SPELL_WARRIOR_VENGEANCE))
                    caster->RemoveAurasDueToSpell(SPELL_WARRIOR_VENGEANCE);
            }
        }

        void Register() override
        {
            OnEffectRemove += AuraEffectRemoveFn(spell_warr_vigilance_AuraScript::HandleRemove, EFFECT_0, SPELL_AURA_PROC_TRIGGER_SPELL, AURA_EFFECT_HANDLE_REAL);
        }

    private:
        Unit* _procTarget;
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_warr_vigilance_AuraScript();
    }
};

// 50725 Vigilance
class spell_warr_vigilance_trigger : public SpellScriptLoader
{
public:
    spell_warr_vigilance_trigger() : SpellScriptLoader("spell_warr_vigilance_trigger") { }

    class spell_warr_vigilance_trigger_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_warr_vigilance_trigger_SpellScript);

        void HandleScript(SpellEffIndex effIndex)
        {
            PreventHitDefaultEffect(effIndex);

            // Remove Taunt cooldown
            if (Player* target = GetHitPlayer())
                target->GetSpellHistory()->ResetCooldown(SPELL_WARRIOR_TAUNT, true);
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_warr_vigilance_trigger_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_warr_vigilance_trigger_SpellScript();
    }
};

// 97462 - Rallying Cry
class spell_warr_rallying_cry : public SpellScriptLoader
{
public:
    spell_warr_rallying_cry() : SpellScriptLoader("spell_warr_rallying_cry") {}

    class spell_warr_rallying_cry_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_warr_rallying_cry_SpellScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            return sSpellMgr->GetSpellInfo(SPELL_WARRIOR_RALLYING_CRY_TRIGGER) != nullptr;
        }

        void HandleDummy(SpellEffIndex /*effIndex*/)
        {
            Unit* caster = GetCaster();
            Unit* target = GetHitUnit();
            if (!caster || !target)
                return;

            uint32 amount = CalculatePct(caster->GetMaxHealth(), GetEffectValue());
            caster->CastCustomSpell(SPELL_WARRIOR_RALLYING_CRY_TRIGGER, SPELLVALUE_BASE_POINT0, amount, target, true);
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_warr_rallying_cry_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_warr_rallying_cry_SpellScript();
    }
};

// 198304 - Intercept 
class spell_warr_intercept : public SpellScriptLoader
{
public:
    spell_warr_intercept() : SpellScriptLoader("spell_warr_intercept") {}

    class spell_warr_intercept_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_warr_intercept_SpellScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            return sSpellMgr->GetSpellInfo(SPELL_WARRIOR_INTERVENE_TRIGGER) != nullptr;
        }

        void HandleDummy(SpellEffIndex /*effIndex*/)
        {
            Unit* caster = GetCaster();
            Unit* target = GetHitUnit();
            if (!caster || !target)
                return;

            if (target->IsFriendlyTo(caster))
            {
                caster->CastSpell(target, SPELL_WARRIOR_INTERVENE_TRIGGER, true);
                if (caster->HasAura(SPELL_WARRIOR_LEAVE_NO_MAN_BEHIND))
                    caster->CastSpell(target, SPELL_WARRIOR_LEAVE_NO_MAN_BEHIND_BUFF, true);
            }
            else
            {
                caster->CastSpell(target, SPELL_WARRIOR_CHARGE_EFFECT, true);
                if (caster->HasAura(SPELL_WARRIOR_WARBRINGER))
                    caster->CastSpell(target, SPELL_WARRIOR_INTERCEPT_STUN, true);
                else
                    caster->CastSpell(target, SPELL_WARRIOR_WARBRINGER_ROOT, true);
            }
        }

        SpellCastResult CheckCast()
        {
            Unit* caster = GetCaster();
            Unit* target = GetExplTargetUnit();
            Position pos = target->GetPosition();

            if (caster->GetDistance(pos) < 8.0f && !caster->IsFriendlyTo(target))
            {
                return SPELL_FAILED_TOO_CLOSE;
            }
            return SPELL_CAST_OK;
        }

        void HandleAfterCast()
        {
            if (Unit* caster = GetCaster())
                if (caster->HasAura(SPELL_WARRIOR_SHADOW_OF_THE_COLOSSUS))
                    caster->GetSpellHistory()->ResetCharges(sSpellMgr->GetSpellInfo(SPELL_WARRIOR_OVERPOWER_PROC)->ChargeCategoryId);
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_warr_intercept_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            OnCheckCast += SpellCheckCastFn(spell_warr_intercept_SpellScript::CheckCast);
            AfterCast += SpellCastFn(spell_warr_intercept_SpellScript::HandleAfterCast);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_warr_intercept_SpellScript();
    }
};

class spell_warr_safeguard : public SpellScriptLoader
{
public:
    spell_warr_safeguard() : SpellScriptLoader("spell_warr_safeguard") {}

    class spell_warrior_intervene_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_warrior_intervene_SpellScript);

        void HandleOnHit()
        {
            Unit* caster = GetCaster();
            if (!caster)
                return;

            caster->RemoveMovementImpairingAuras(true);
        }

        void Register() override
        {
            OnHit += SpellHitFn(spell_warrior_intervene_SpellScript::HandleOnHit);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_warrior_intervene_SpellScript();
    }
};

//18499
class spell_warr_berzerker_rage : public SpellScriptLoader
{
public:
    spell_warr_berzerker_rage() : SpellScriptLoader("spell_warr_berzerker_rage") { }

    class spell_warr_berzerker_rage_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_warr_berzerker_rage_AuraScript);

        void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            Unit* caster = GetCaster();

            caster->RemoveAurasDueToSpell(SPELL_WARRIOR_UNCHACKLED_FURY);
        }

        void Register() override
        {
            OnEffectRemove += AuraEffectRemoveFn(spell_warr_berzerker_rage_AuraScript::HandleRemove, EFFECT_0, SPELL_AURA_ADD_PCT_MODIFIER, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_warr_berzerker_rage_AuraScript();
    }
};

class spell_warr_siegebreaker : public SpellScriptLoader
{
public:
    spell_warr_siegebreaker() : SpellScriptLoader("spell_warr_siegebreaker") { }

    class spell_warr_siegebreaker_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_warr_siegebreaker_SpellScript);

        void HandleOnHit()
        {
            if (Player* _player = GetCaster()->ToPlayer())
                if (Unit* target = GetHitUnit())
                {
                    _player->CastCustomSpell(280773, SPELLVALUE_BASE_POINT0, 8.5f + _player->m_activePlayerData->Mastery, target, true);
                }
        }

        void Register() override
        {
            OnHit += SpellHitFn(spell_warr_siegebreaker_SpellScript::HandleOnHit);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_warr_siegebreaker_SpellScript();
    }
};

class spell_warr_dragon_roar : public SpellScriptLoader
{
public:
    spell_warr_dragon_roar() : SpellScriptLoader("spell_warr_dragon_roar") { }

    class spell_warr_dragon_roar_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_warr_dragon_roar_SpellScript);
        void HandleOnHit()
        {
            if (Player* _player = GetCaster()->ToPlayer())
                if (Unit* target = GetHitUnit())
                    _player->CastSpell(target, SPELL_WARRIOR_DRAGON_ROAR_KNOCK_BACK, true);
        }

        void Register() override
        {
            OnHit += SpellHitFn(spell_warr_dragon_roar_SpellScript::HandleOnHit);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_warr_dragon_roar_SpellScript();
    }
};

// Mortal Strike - 12294
class spell_warr_mortal_strike : public SpellScriptLoader
{
public:
    spell_warr_mortal_strike() : SpellScriptLoader("spell_warr_mortal_strike") { }

    class spell_warr_mortal_strike_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_warr_mortal_strike_SpellScript);

        void HandleOnHit()
        {
            Unit* caster = GetCaster();
            Unit* target = GetHitUnit();
            if (!caster || !target)
                return;

            if (!caster->HasAura(SPELL_WARRIOR_SHARPEN_BLADE))
                caster->AddAura(SPELL_WARRIOR_MORTAL_WOUNDS, target);
            else
            {
                caster->CastSpell(target, SPELL_WARRIOR_SHARPEN_BLADE_DEBUFF, true);
                caster->RemoveAurasDueToSpell(SPELL_WARRIOR_SHARPEN_BLADE);
            }

            caster->RemoveAurasDueToSpell(SPELL_WARRIOR_OVERPOWER_PROC);
        }

        void HandleOnHitTarget(SpellEffIndex /* effIndex */)
        {
            Unit* target = GetHitUnit();
            if (!target)
                return;

            if (AuraEffect* auraEff = target->GetAuraEffect(SPELL_WARRIOR_EXECUTIONER_PRECISION_PROC, EFFECT_0))
                SetHitDamage(GetHitDamage() + auraEff->GetAmount());
        }

        void HandleAfterHit()
        {
            Unit* caster = GetCaster();
            Unit* target = GetHitUnit();
            if (!caster || !target)
                return;

            if (Aura* aura = target->GetAura(SPELL_WARRIOR_EXECUTIONER_PRECISION_PROC))
                aura->DropStack();

            caster->RemoveAurasDueToSpell(Warrior::eLegendary::BattleLordProc);
        }

        void Register() override
        {
            OnHit += SpellHitFn(spell_warr_mortal_strike_SpellScript::HandleOnHit);
            OnEffectHitTarget += SpellEffectFn(spell_warr_mortal_strike_SpellScript::HandleOnHitTarget, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
            AfterHit += SpellHitFn(spell_warr_mortal_strike_SpellScript::HandleAfterHit);
        }
    };
    SpellScript* GetSpellScript() const override
    {
        return new spell_warr_mortal_strike_SpellScript();
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
                    caster->AddAura(SPELL_WARRIOR_ALLOW_RAGING_BLOW);
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

class spell_warr_shield_block : public SpellScriptLoader
{
public:
    spell_warr_shield_block() : SpellScriptLoader("spell_warr_shield_block") { }

    class spell_warr_shield_block_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_warr_shield_block_SpellScript);

        void HandleOnHit()
        {
            if (Player* _player = GetCaster()->ToPlayer())
                _player->CastSpell(_player, SPELL_WARRIOR_SHIELD_BLOCKC_TRIGGERED, true);
        }

        void Register() override
        {
            OnHit += SpellHitFn(spell_warr_shield_block_SpellScript::HandleOnHit);
        }
    };

    class spell_warr_shield_block_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_warr_shield_block_AuraScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_WARRIOR_SHIELD_BLOCKC_TRIGGERED))
                return false;
            return true;
        }

        void CalculateAmount(AuraEffect const* /*aurEff*/, int32& amount, bool& /*canBeRecalculated*/)
        {
            if (Unit* caster = GetCaster())
                if (caster->HasAura(SPELL_WARRIOR_HEAVY_REPERCUSSIONS))
                    amount += 30;
        }

        void Register() override
        {
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_warr_shield_block_AuraScript::CalculateAmount, EFFECT_1, SPELL_AURA_MOD_DAMAGE_PERCENT_DONE);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_warr_shield_block_SpellScript();
    }

    AuraScript* GetAuraScript() const override
    {
        return new spell_warr_shield_block_AuraScript();
    }
};

//107570
class spell_warr_storm_bolt : public SpellScriptLoader
{
public:
    spell_warr_storm_bolt() : SpellScriptLoader("spell_warr_storm_bolt") { }

    class spell_warr_storm_bolt_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_warr_storm_bolt_SpellScript);

        void HandleOnHitTarget(SpellEffIndex /* effIndex */)
        {
            Unit* caster = GetCaster();
            Unit* target = GetHitUnit();
            if (!caster || !target)
                return;

            caster->CastSpell(target, SPELL_WARRIOR_STORM_BOLT_STUN, true);
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_warr_storm_bolt_SpellScript::HandleOnHitTarget, EFFECT_1, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_warr_storm_bolt_SpellScript();
    }
};


class spell_warr_opportunity_strike : public SpellScriptLoader
{
public:
    spell_warr_opportunity_strike() : SpellScriptLoader("spell_warr_opportunity_strike") { }


    class spell_warr_opportunity_strike_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_warr_opportunity_strike_AuraScript);

        void HandleProc(ProcEventInfo& eventInfo)
        {
            if (!GetCaster())
                return;

            if (eventInfo.GetDamageInfo() && eventInfo.GetDamageInfo()->GetSpellInfo() && eventInfo.GetDamageInfo()->GetSpellInfo()->Id == SPELL_WARRIOR_OPPORTUNITY_STRIKE_DAMAGE)
                return;

            if (Unit* target = eventInfo.GetActionTarget())
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (Aura* aur = GetAura())
                    {
                        if (AuraEffect* eff = aur->GetEffect(0))
                        {
                            if (roll_chance_i(eff->GetAmount()))
                                _player->CastSpell(target, SPELL_WARRIOR_OPPORTUNITY_STRIKE_DAMAGE, true);
                        }
                    }
                }
            }
        }

        void Register() override
        {
            OnProc += AuraProcFn(spell_warr_opportunity_strike_AuraScript::HandleProc);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_warr_opportunity_strike_AuraScript();
    }
};

// 6343 - Thunder clap
class spell_warr_thunder_clap : public SpellScriptLoader
{
public:
    spell_warr_thunder_clap() : SpellScriptLoader("spell_warr_thunder_clap") { }

    class spell_warr_thunder_clap_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_warr_thunder_clap_SpellScript);

        uint32 m_ThunderlordLeft = 3;

        void HandleOnHit()
        {
            if (Player* _player = GetCaster()->ToPlayer())
            {
                if (Unit* target = GetHitUnit())
                {
                    _player->CastSpell(target, SPELL_WARRIOR_WEAKENED_BLOWS, true);

                    if (_player->HasAura(SPELL_WARRIOR_THUNDERSTRUCK))
                        _player->CastSpell(target, SPELL_WARRIOR_THUNDERSTRUCK_STUN, true);

                    if (_player->HasAura(Warrior::eLegendary::ThunderLord))
                    {
                        if (m_ThunderlordLeft > 0)
                        {
                            --m_ThunderlordLeft;
                            _player->GetSpellHistory()->ModifyCooldown(Warrior::eProtection::DemoralizingShout, -1500);
                        }
                    }
                }
            }
        }

        void HandleAfterCast()
        {
            if (Unit* caster = GetCaster())
                if (Aura* aura = caster->GetAura(SPELL_WARRIOR_SHIELD_SLAM_RANK2))
                    if (roll_chance_i(aura->GetEffect(EFFECT_0)->GetBaseAmount()))
                    {
                        caster->CastSpell(caster, SPELL_WARRIOR_SHILED_SLAM_INDICATOR, true);
                        caster->GetSpellHistory()->ResetCooldown(SPELL_WARRIOR_SHIELD_SLAM, true);
                    }
        }

        void Register() override
        {
            OnHit += SpellHitFn(spell_warr_thunder_clap_SpellScript::HandleOnHit);
            AfterCast += SpellCastFn(spell_warr_thunder_clap_SpellScript::HandleAfterCast);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_warr_thunder_clap_SpellScript();
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
            SPELL_WARRIOR_VICTORIOUS_STATE,
            SPELL_WARRIOR_VICTORY_RUSH_HEAL
            });
    }

    void HandleHit()
    {
        if (Unit* caster = GetCaster())
            if (Aura* aura = caster->GetAura(SPELL_WARRIOR_BURY_THE_HATCHERY))
                caster->CastCustomSpell(SPELL_WARRIOR_BURY_THE_HATCHERY_ABSORB, SPELLVALUE_BASE_POINT0, aura->GetEffect(EFFECT_0)->GetAmount(), caster, true);
    }

    void HandleHeal()
    {
        Unit* caster = GetCaster();
        caster->CastSpell(caster, SPELL_WARRIOR_VICTORY_RUSH_HEAL, true);
        caster->RemoveAurasDueToSpell(SPELL_WARRIOR_VICTORIOUS_STATE);
    }

    void Register() override
    {
        OnHit += SpellHitFn(spell_warr_victory_rush::HandleHit);
        AfterCast += SpellCastFn(spell_warr_victory_rush::HandleHeal);
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

    void HandleHit()
    {
        if (Unit* caster = GetCaster())
            if (Aura* aura = caster->GetAura(SPELL_WARRIOR_BURY_THE_HATCHERY))
                caster->CastCustomSpell(SPELL_WARRIOR_BURY_THE_HATCHERY_ABSORB, SPELLVALUE_BASE_POINT0, aura->GetEffect(EFFECT_0)->GetAmount(), caster, true);
    }

    void HandleAfterCast()
    {
        if (Unit* caster = GetCaster())
        {
            caster->CastSpell(caster, SPELL_WARRIOR_IMPENDING_VICTORY_HEAL, true);
            caster->RemoveAurasDueToSpell(SPELL_WARRIOR_VICTORIOUS_STATE);
        }
    }

    void Register() override
    {
        OnHit += SpellHitFn(spell_warr_impending_victory::HandleHit);
        AfterCast += SpellCastFn(spell_warr_impending_victory::HandleAfterCast);
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

    void HandleHit()
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        uint32 spellId = SPELL_WARRIOR_CHARGE_EFFECT;
        if (caster->HasAura(SPELL_WARRIOR_GLYPH_OF_THE_BLAZING_TRAIL))
            spellId = SPELL_WARRIOR_CHARGE_EFFECT_BLAZING_TRAIL;

        caster->CastSpell(GetHitUnit(), spellId, true);

        if (caster->HasAura(SPELL_WARRIOR_FURIOUS_CHARGE))
            caster->CastSpell(caster, SPELL_WARRIOR_FURIOUS_CHARGE_BUFF, true);
    }

    void HandleAfterCast()
    {
        if (Unit* caster = GetCaster())
            if (caster->HasAura(SPELL_WARRIOR_SHADOW_OF_THE_COLOSSUS))
                caster->GetSpellHistory()->ResetCharges(sSpellMgr->GetSpellInfo(SPELL_WARRIOR_OVERPOWER_PROC)->ChargeCategoryId);
    }

    SpellCastResult CheckCast()
    {
        if (Unit* target = GetExplTargetUnit())
        {
            auto unitCaster = GetCaster();
            if (!target->IsWithinLOSInMap(GetCaster())) //Do full LoS/Path check. Don't exclude m2
                return SPELL_FAILED_LINE_OF_SIGHT;

            float objSize = target->GetObjectSize();
            float range = GetSpellInfo()->GetMaxRange(true, unitCaster, this->GetSpell()) * 1.5f + objSize; // can't be overly strict

            bool hasTransport = unitCaster->GetTransport() && target->GetTransport();

            auto m_preGeneratedPath = std::make_unique<PathGenerator>(unitCaster, hasTransport);
            m_preGeneratedPath->SetPathLengthLimit(range);

            // first try with raycast, if it fails fall back to normal path
            float targetObjectSize = std::min(target->GetObjectSize(), 4.0f);
            bool result = m_preGeneratedPath->CalculatePath(target->GetPositionX(), target->GetPositionY(), target->GetPositionZ() + targetObjectSize, false, true);
            if (m_preGeneratedPath->GetPathType() & PATHFIND_SHORT)
                return SPELL_FAILED_NOPATH;
            else if (!result || m_preGeneratedPath->GetPathType() & (PATHFIND_NOPATH | PATHFIND_INCOMPLETE))
            {
                result = m_preGeneratedPath->CalculatePath(target->GetPositionX(), target->GetPositionY(), target->GetPositionZ() + targetObjectSize, false, false);
                if (m_preGeneratedPath->GetPathType() & PATHFIND_SHORT)
                    return SPELL_FAILED_OUT_OF_RANGE;
                else if (!result || m_preGeneratedPath->GetPathType() & (PATHFIND_NOPATH | PATHFIND_INCOMPLETE))
                    return SPELL_FAILED_NOPATH;
                else if (m_preGeneratedPath->IsInvalidDestinationZ(target)) // Check position z, if not in a straight line
                    return SPELL_FAILED_NOPATH;
            }
            else if (!hasTransport && m_preGeneratedPath->IsInvalidDestinationZ(target)) // Check position z, if in a straight line
                return SPELL_FAILED_NOPATH;
        }

        return SPELL_CAST_OK;
    }

    void Register() override
    {
        OnCheckCast += SpellCheckCastFn(spell_warr_charge::CheckCast);
        OnHit += SpellHitFn(spell_warr_charge::HandleHit);
        AfterCast += SpellCastFn(spell_warr_charge::HandleAfterCast);
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
            });
    }

    void HandleCharge(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        caster->CastCustomSpell(SPELL_WARRIOR_CHARGE_PAUSE_RAGE_DECAY, SPELLVALUE_BASE_POINT0, 0, caster, true);
        caster->CastSpell(target, SPELL_WARRIOR_CHARGE_ROOT_EFFECT, true);
        if (caster->HasAura(202224))
            caster->CastSpell(caster, 202225, true);
    }

    void Register() override
    {
        OnEffectLaunchTarget += SpellEffectFn(spell_warr_charge_effect::HandleCharge, EFFECT_0, SPELL_EFFECT_CHARGE);
    }
};

// Spell Reflect
class spell_warr_spell_reflect : public SpellScriptLoader
{
public:
    spell_warr_spell_reflect() : SpellScriptLoader("spell_warr_spell_reflect") { }

    class spell_warr_spell_reflect_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_warr_spell_reflect_AuraScript);

        void OnApply(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            Unit* caster = GetCaster();
            if (!caster || caster->GetTypeId() != TYPEID_PLAYER)
                return;

            Item* item = caster->ToPlayer()->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND);
            if (item && item->GetTemplate()->GetInventoryType() == INVTYPE_SHIELD)
                caster->CastSpell(caster, 146120, true);
            else if (caster->GetFaction() == FACTION_ALLIANCE_GENERIC_WG) // Alliance
                caster->CastSpell(caster, 147923, true);
            else // Horde
                caster->CastSpell(caster, 146122, true);
        }

        void OnRemove(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            Unit* caster = GetCaster();
            if (!caster || caster->GetTypeId() != TYPEID_PLAYER)
                return;

            // Visuals
            caster->RemoveAura(146120);
            caster->RemoveAura(147923);
            caster->RemoveAura(146122);
        }

        void Register() override
        {
            OnEffectApply += AuraEffectApplyFn(spell_warr_spell_reflect_AuraScript::OnApply, EFFECT_0, SPELL_AURA_REFLECT_SPELLS, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
            OnEffectRemove += AuraEffectRemoveFn(spell_warr_spell_reflect_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_REFLECT_SPELLS, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_warr_spell_reflect_AuraScript();
    }
};

class spell_warr_shield_slam : public SpellScriptLoader
{
public:
    spell_warr_shield_slam() : SpellScriptLoader("spell_warr_shield_slam") { }

    class spell_warr_shield_slam_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_warr_shield_slam_SpellScript);

        void HandleDispel(SpellEffIndex effIndex)
        {
            // 6.0.3 HOTFIX: Shield Slam modified by Glyph of Shield Slam now only dispels 1 magical effect while the Warrior is in Defensive Stance.
            if (GetCaster()->GetShapeshiftForm() != FORM_DEFENSIVE_STANCE)
                PreventHitDefaultEffect(effIndex);
        }

        void HandlePassive(SpellEffIndex /*effIndex*/)
        {
            //Handles the passive bonuses
            if (Unit* caster = GetCaster())
                if (caster->HasAura(SPELL_WARRIOR_HEAVY_REPERCUSSIONS) && caster->HasAura(SPELL_WARRIOR_SHIELD_BLOCKC_TRIGGERED))
                    caster->GetAura(SPELL_WARRIOR_SHIELD_BLOCKC_TRIGGERED)->SetDuration(caster->GetAura(SPELL_WARRIOR_SHIELD_BLOCKC_TRIGGERED)->GetDuration() + 1500);
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_warr_shield_slam_SpellScript::HandleDispel, EFFECT_1, SPELL_EFFECT_DISPEL);
            OnEffectHitTarget += SpellEffectFn(spell_warr_shield_slam_SpellScript::HandlePassive, EFFECT_2, SPELL_EFFECT_ENERGIZE);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_warr_shield_slam_SpellScript();
    }
};

// Heroic leap - 6544
class spell_warr_heroic_leap : public SpellScriptLoader
{
public:
    spell_warr_heroic_leap() : SpellScriptLoader("spell_warr_heroic_leap") { }

    class spell_warr_heroic_leap_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_warr_heroic_leap_SpellScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_WARRIOR_HEROIC_LEAP_JUMP))
                return false;
            return true;
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

                    bool result = generatedPath.CalculatePath(dest->GetPositionX(), dest->GetPositionY(), dest->GetPositionZ(), false, true);
                    if (generatedPath.GetPathType() & PATHFIND_SHORT)
                        return SPELL_FAILED_OUT_OF_RANGE;
                    else if (!result || generatedPath.GetPathType() & PATHFIND_NOPATH)
                    {
                        result = generatedPath.CalculatePath(dest->GetPositionX(), dest->GetPositionY(), dest->GetPositionZ(), false, false);
                        if (generatedPath.GetPathType() & PATHFIND_SHORT)
                            return SPELL_FAILED_OUT_OF_RANGE;
                        else if (!result || generatedPath.GetPathType() & PATHFIND_NOPATH)
                            return SPELL_FAILED_NOPATH;
                    }
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
            {
                GetCaster()->CastSpell(*dest, SPELL_WARRIOR_HEROIC_LEAP_JUMP, true);
            }

            if (Unit* caster = GetCaster())
            {
                if (caster->ToPlayer()->GetSpecializationId() == TALENT_SPEC_WARRIOR_PROTECTION)
                    caster->GetSpellHistory()->ResetCooldown(355, true);

                if (caster->HasAura(SPELL_WARRIOR_BARBARIAN) && !caster->HasAura(SPELL_WARRIOR_BARBARIAN_BUFF))
                    caster->CastSpell(caster, SPELL_WARRIOR_BARBARIAN_BUFF, true);
                else
                    caster->RemoveAurasDueToSpell(SPELL_WARRIOR_BARBARIAN_BUFF);
            }
        }

        void HandleHitTarget(SpellEffIndex /*effIndex*/)
        {

        }

        void Register() override
        {
            OnCheckCast += SpellCheckCastFn(spell_warr_heroic_leap_SpellScript::CheckElevation);
            OnEffectHit += SpellEffectFn(spell_warr_heroic_leap_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_warr_heroic_leap_SpellScript();
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

//190456 - Ignore Pain
class spell_warr_ignore_pain : public SpellScript
{
    PrepareSpellScript(spell_warr_ignore_pain);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_WARRIOR_RENEWED_FURY, SPELL_WARRIOR_VENGEANCE_FOCUSED_RAGE });
    }

    void HandleDummy(SpellEffIndex /*effIndex*/)
    {
        if (Unit* caster = GetCaster())
        {
            if (caster->HasAura(SPELL_WARRIOR_RENEWED_FURY))
                caster->CastSpell(caster, SPELL_WARRIOR_RENEWED_FURY_EFFECT, true);
            if (caster->HasAura(SPELL_WARRIOR_VENGEANCE_AURA))
                caster->CastSpell(caster, SPELL_WARRIOR_VENGEANCE_FOCUSED_RAGE, true);
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_warr_ignore_pain::HandleDummy, EFFECT_1, SPELL_EFFECT_DUMMY);
    }
};

// 190456 - Ignore Pain
class aura_warr_ignore_pain : public AuraScript
{
    PrepareAuraScript(aura_warr_ignore_pain);

    void CalcAmountAbsorb(AuraEffect const* /*aurEff*/, int32& amount, bool& /*canBeRecalculated*/)
    {
        if (Unit* caster = GetCaster())
            amount = 1 + caster->GetTotalAttackPowerValue(BASE_ATTACK) * 3.5f;
    }

    void CalcAmount(AuraEffect const* /*aurEff*/, int32& amount, bool& /*canBeRecalculated*/)
    {
        amount = sSpellMgr->GetSpellInfo(SPELL_WARRIOR_IGNORE_PAIN)->GetEffect(EFFECT_1).BasePoints;
    }

    void Register() override
    {
        DoEffectCalcAmount += AuraEffectCalcAmountFn(aura_warr_ignore_pain::CalcAmountAbsorb, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
        DoEffectCalcAmount += AuraEffectCalcAmountFn(aura_warr_ignore_pain::CalcAmount, EFFECT_2, SPELL_AURA_MOD_BASE_RESISTANCE_PCT);
    }
};

//46968 - Shockwave
class spell_warr_shockwave : public SpellScriptLoader
{
public:
    spell_warr_shockwave() : SpellScriptLoader("spell_warr_shockwave") {}

    class spell_warr_shockwave_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_warr_shockwave_SpellScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            return ValidateSpellInfo({ SPELL_WARRIOR_RUMBLING_EARTH });
        }

        void HandleHit(SpellEffIndex /*effIndex*/)
        {
            Unit* caster = GetCaster();
            if (!caster)
                return;

            std::list<Unit*> targets;
            caster->GetAttackableUnitListInRange(targets, 10.0f);
            uint16 amount_of_targets = 0;

            for (auto itr : targets)
            {
                if (caster->IsValidAttackTarget(itr))
                {
                    caster->CastSpell(itr, SPELL_WARRIOR_SHOCKWAVE_STUN, true);
                    amount_of_targets++;
                }
            }

            if (caster->HasAura(SPELL_WARRIOR_RUMBLING_EARTH) && amount_of_targets >= sSpellMgr->GetSpellInfo(SPELL_WARRIOR_RUMBLING_EARTH)->GetEffect(EFFECT_0).BasePoints)
                caster->GetSpellHistory()->ModifyCooldown(SPELL_WARRIOR_SHOCKWAVE, -Milliseconds(sSpellMgr->GetSpellInfo(SPELL_WARRIOR_RUMBLING_EARTH)->GetEffect(EFFECT_1).BasePoints));
        }

        void Register() override
        {
            OnEffectHit += SpellEffectFn(spell_warr_shockwave_SpellScript::HandleHit, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_warr_shockwave_SpellScript();
    }
};

//204488 - Focused Rage
class spell_warr_focused_rage_prot : public SpellScriptLoader
{
public:
    spell_warr_focused_rage_prot() : SpellScriptLoader("spell_warr_focused_rage_prot") {}

    class spell_warr_focused_rage_prot_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_warr_focused_rage_prot_AuraScript);

        bool CheckProc(ProcEventInfo& eventInfo)
        {
            if (eventInfo.GetSpellInfo()->Id == SPELL_WARRIOR_SHIELD_SLAM)
                return true;
            return false;
        }

        void Register() override
        {
            DoCheckProc += AuraCheckProcFn(spell_warr_focused_rage_prot_AuraScript::CheckProc);
        }
    };

    class spell_warr_focused_rage_prot_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_warr_focused_rage_prot_SpellScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_WARRIOR_VENGEANCE_IGNORE_PAIN))
                return false;
            return true;
        }

        void HandleDummy(SpellEffIndex /*effIndex*/)
        {
            if (Unit* caster = GetCaster())
            {
                if (caster->HasAura(SPELL_WARRIOR_VENGEANCE_AURA))
                    caster->CastSpell(caster, SPELL_WARRIOR_VENGEANCE_IGNORE_PAIN, true);
            }
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_warr_focused_rage_prot_SpellScript::HandleDummy, EFFECT_1, SPELL_EFFECT_DUMMY);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_warr_focused_rage_prot_AuraScript();
    }

    SpellScript* GetSpellScript() const override
    {
        return new spell_warr_focused_rage_prot_SpellScript();
    }

};

//207982 - Focused Rage
class spell_warr_focused_rage_arms : public SpellScriptLoader
{
public:
    spell_warr_focused_rage_arms() : SpellScriptLoader("spell_warr_focused_rage_arms") {}

    class spell_warr_focused_rage_arms_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_warr_focused_rage_arms_AuraScript);

        bool CheckProc(ProcEventInfo& eventInfo)
        {
            if (eventInfo.GetSpellInfo()->Id == SPELL_WARRIOR_MORTAL_STRIKE)
                return true;
            return false;
        }

        void Register() override
        {
            DoCheckProc += AuraCheckProcFn(spell_warr_focused_rage_arms_AuraScript::CheckProc);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_warr_focused_rage_arms_AuraScript();
    }

};

//20243 - Devastate
class spell_warr_devastate : public SpellScriptLoader
{
public:
    spell_warr_devastate() : SpellScriptLoader("spell_warr_devastate") {}

    class spell_warr_devastate_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_warr_devastate_SpellScript);

        void HandleAfterCast()
        {
            if (Unit* caster = GetCaster())
                if (Aura* aura = caster->GetAura(SPELL_WARRIOR_SHIELD_SLAM_RANK2))
                    if (roll_chance_i(aura->GetEffect(EFFECT_0)->GetBaseAmount()))
                    {
                        caster->CastSpell(caster, SPELL_WARRIOR_SHILED_SLAM_INDICATOR, true);
                        caster->GetSpellHistory()->ResetCooldown(SPELL_WARRIOR_SHIELD_SLAM, true);
                    }
        }

        void Register() override
        {
            AfterCast += SpellCastFn(spell_warr_devastate_SpellScript::HandleAfterCast);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_warr_devastate_SpellScript();
    }
};

//214871 - Odyn's fury
class spell_warr_odyns_fury : public SpellScriptLoader
{
public:
    spell_warr_odyns_fury() : SpellScriptLoader("spell_warr_odyns_fury") { }

    class spell_warr_odyns_fury_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_warr_odyns_fury_AuraScript);

        void Absorb(AuraEffect* /* aurEff */, DamageInfo& /*dmgInfo*/, uint32& absorbAmount)
        {
            absorbAmount = 0;
        }

        void Register() override
        {
            OnEffectAbsorb += AuraEffectAbsorbFn(spell_warr_odyns_fury_AuraScript::Absorb, EFFECT_0);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_warr_odyns_fury_AuraScript();
    }
};

// 215570 - Wrecking Ball
class spell_warr_wrecking_ball_effect : public SpellScriptLoader
{
public:
    spell_warr_wrecking_ball_effect() : SpellScriptLoader("spell_warr_wrecking_ball_effect") { }

    class spell_warr_wrecking_ball_effect_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_warr_wrecking_ball_effect_AuraScript);

        void HandleProc(AuraEffect* /*aurEff*/, ProcEventInfo& /*procInfo*/)
        {
            if (Unit* caster = GetCaster())
            {
                if (caster->HasAura(SPELL_WARRIOR_WRECKING_BALL_EFFECT))
                    caster->RemoveAura(SPELL_WARRIOR_WRECKING_BALL_EFFECT);
            }
        }

        void Register() override
        {
            OnEffectProc += AuraEffectProcFn(spell_warr_wrecking_ball_effect_AuraScript::HandleProc, EFFECT_0, SPELL_AURA_ADD_PCT_MODIFIER);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_warr_wrecking_ball_effect_AuraScript();
    }
};

//206315
class spell_warr_massacre : public SpellScriptLoader
{
public:
    spell_warr_massacre() : SpellScriptLoader("spell_warr_massacre") { }

    class spell_warr_massacre_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_warr_massacre_AuraScript);

        bool CheckProc(ProcEventInfo& procInfo)
        {
            if (procInfo.GetSpellInfo()->Id == SPELL_WARRIOR_EXECUTE)
                if (procInfo.GetHitMask() & PROC_HIT_CRITICAL)
                    return true;

            return false;
        }

        void Register() override
        {
            DoCheckProc += AuraCheckProcFn(spell_warr_massacre_AuraScript::CheckProc);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_warr_massacre_AuraScript();
    }
};

// BloodBath - 12292
class spell_warr_blood_bath : public SpellScriptLoader
{
public:
    spell_warr_blood_bath() : SpellScriptLoader("spell_warr_blood_bath") { }

    class spell_warr_blood_bath_Aurascript : public AuraScript
    {
        PrepareAuraScript(spell_warr_blood_bath_Aurascript);

        enum eSpells
        {
            BloodBath = 12292,
            BloodBathDamage = 113344
        };

        void HandleOnProc(AuraEffect* aurEff, ProcEventInfo& p_ProcInfo)
        {
            PreventDefaultAction();

            if (!p_ProcInfo.GetDamageInfo() || !p_ProcInfo.GetDamageInfo()->GetDamage() || !p_ProcInfo.GetDamageInfo()->GetSpellInfo())
                return;

            if (p_ProcInfo.GetDamageInfo()->GetSpellInfo()->Id == eSpells::BloodBathDamage)
                return;

            Unit* l_Target = p_ProcInfo.GetActionTarget();
            Unit* caster = GetCaster();
            if (l_Target == nullptr || caster == nullptr || l_Target == caster)
                return;

            SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(eSpells::BloodBath);
            SpellInfo const* l_SpellInfoDamage = sSpellMgr->GetSpellInfo(eSpells::BloodBathDamage);

            if (spellInfo == nullptr || l_SpellInfoDamage == nullptr)
                return;

            int32 l_Damage = CalculatePct(p_ProcInfo.GetDamageInfo()->GetDamage(), aurEff->GetBaseAmount());

            int32 l_PreviousTotalDamage = 0;

            if (AuraEffect* l_PreviousBloodBath = l_Target->GetAuraEffect(eSpells::BloodBathDamage, EFFECT_0, caster->GetGUID()))
            {
                int32 l_PeriodicDamage = l_PreviousBloodBath->GetAmount();
                int32 l_Duration = l_Target->GetAura(eSpells::BloodBathDamage, caster->GetGUID())->GetDuration();
                int32 l_Amplitude = l_PreviousBloodBath->GetSpellEffectInfo().Amplitude;

                if (l_Amplitude)
                    l_PreviousTotalDamage = l_PeriodicDamage * ((l_Duration / l_Amplitude) + 1);

                l_PreviousTotalDamage /= (l_SpellInfoDamage->GetMaxDuration() / l_SpellInfoDamage->GetEffect(EFFECT_0).Amplitude);
            }

            if (l_SpellInfoDamage->GetEffect(EFFECT_0).Amplitude)
                l_Damage /= (l_SpellInfoDamage->GetMaxDuration() / l_SpellInfoDamage->GetEffect(EFFECT_0).Amplitude);

            l_Damage += l_PreviousTotalDamage;

            if (l_Target->HasAura(eSpells::BloodBathDamage, caster->GetGUID()))
            {
                if (Aura* l_ActualBloodBath = l_Target->GetAura(eSpells::BloodBathDamage, caster->GetGUID()))
                    l_ActualBloodBath->SetDuration(l_ActualBloodBath->GetMaxDuration());
            }
            else
                caster->CastSpell(l_Target, eSpells::BloodBathDamage, true);

            if (AuraEffect* l_NewBloodBath = l_Target->GetAuraEffect(eSpells::BloodBathDamage, EFFECT_0, caster->GetGUID()))
                l_NewBloodBath->SetAmount(l_Damage);
        }

        void Register() override
        {
            OnEffectProc += AuraEffectProcFn(spell_warr_blood_bath_Aurascript::HandleOnProc, EFFECT_0, SPELL_AURA_DUMMY);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_warr_blood_bath_Aurascript();
    }
};

//206313 Frenzy
class spell_warr_frenzy : public SpellScriptLoader
{
public:
    spell_warr_frenzy() : SpellScriptLoader("spell_warr_frenzy") { }

    class spell_warr_frenzy_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_warr_frenzy_AuraScript);

        bool CheckProc(ProcEventInfo& procInfo)
        {
            if (procInfo.GetSpellInfo()->Id == SPELL_WARRIOR_FURIOUS_SLASH)
                return true;
            return false;
        }

        void Register() override
        {
            DoCheckProc += AuraCheckProcFn(spell_warr_frenzy_AuraScript::CheckProc);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_warr_frenzy_AuraScript();
    }
};

//200860 Unrivaled Strenght
class spell_warr_unrivaled_strenght : public SpellScriptLoader
{
public:
    spell_warr_unrivaled_strenght() : SpellScriptLoader("spell_warr_unrivaled_strenght") { }

    class spell_warr_unrivaled_strenght_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_warr_unrivaled_strenght_AuraScript);

        void HandleProc(AuraEffect* aurEff, ProcEventInfo& /*procInfo*/)
        {
            GetCaster()->CastSpell(GetCaster(), 200977, true);
            if (GetCaster()->HasAura(200977))
                GetCaster()->GetAura(200977)->GetEffect(EFFECT_0)->SetAmount(aurEff->GetBaseAmount());
        }

        void Register() override
        {
            OnEffectProc += AuraEffectProcFn(spell_warr_unrivaled_strenght_AuraScript::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_warr_unrivaled_strenght_AuraScript();
    }
};

// Defensive Stance - 71
class spell_warr_defensive_stance : public SpellScriptLoader
{
public:
    spell_warr_defensive_stance() : SpellScriptLoader("spell_warr_defensive_stance") {}

    class spell_warr_defensive_stance_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_warr_defensive_stance_AuraScript);

        int32 damageTaken = 0;

        void HandleProc(ProcEventInfo& eventInfo)
        {
            Unit* caster = GetCaster();
            if (!caster)
                return;

            damageTaken = eventInfo.GetDamageInfo() ? eventInfo.GetDamageInfo()->GetDamage() : 0;
            if (damageTaken <= 0)
                return;

            int32 rageAmount = (50.0f * (float)damageTaken) / (float)caster->GetMaxHealth();
            caster->ModifyPower(POWER_RAGE, 10 * uint32(rageAmount));
        }

        void Register() override
        {
            OnProc += AuraProcFn(spell_warr_defensive_stance_AuraScript::HandleProc);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_warr_defensive_stance_AuraScript();
    }
};

// 184783 - Tactician
class spell_warr_tactician : public SpellScriptLoader
{
public:
    spell_warr_tactician() : SpellScriptLoader("spell_warr_tactician") { }

    class spell_warr_tactician_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_warr_tactician_AuraScript);

        bool CheckProc(ProcEventInfo& eventInfo)
        {
            if (eventInfo.GetDamageInfo())
                return true;

            return false;
        }

        void HandleProc(ProcEventInfo& procInfo)
        {
            PreventDefaultAction();
            int32 rageSpent = 0;

            if (Unit* caster = GetCaster())
                if (procInfo.GetSpellInfo())
                {
                    for (SpellPowerCost cost : procInfo.GetSpellInfo()->CalcPowerCost(caster, procInfo.GetSpellInfo()->GetSchoolMask()))
                    {
                        if (cost.Power != POWER_RAGE)
                            continue;

                        rageSpent = cost.Amount / 10;
                    }

                    if (roll_chance_f(sSpellMgr->GetSpellInfo(SPELL_WARRIOR_TACTICIAN)->GetEffect(EFFECT_0).BasePoints / 100 * rageSpent))
                    {
                        caster->GetSpellHistory()->ResetCharges(sSpellMgr->GetSpellInfo(SPELL_WARRIOR_OVERPOWER_PROC)->ChargeCategoryId);
                        caster->CastSpell(caster, SPELL_WARRIOR_TACTICIAN_CD, true);
                    }
                }
        }

        void Register() override
        {
            DoCheckProc += AuraCheckProcFn(spell_warr_tactician_AuraScript::CheckProc);
            OnProc += AuraProcFn(spell_warr_tactician_AuraScript::HandleProc);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_warr_tactician_AuraScript();
    }
};

//215538
class spell_warr_trauma : public SpellScriptLoader
{
public:
    spell_warr_trauma() : SpellScriptLoader("spell_warr_trauma") { }

    class spell_warr_trauma_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_warr_trauma_AuraScript);

        bool CheckProc(ProcEventInfo& eventInfo)
        {
            if (eventInfo.GetSpellInfo()->Id == SPELL_WARRIOR_SLAM_ARMS || eventInfo.GetSpellInfo()->Id == SPELL_WARRIOR_WHIRLWIND_ARMS)
            {
                Unit* caster = GetCaster();
                if (!caster)
                    return false;

                Unit* target = eventInfo.GetActionTarget();
                if (!target)
                    return false;


                uint32 bonusDamage = eventInfo.GetDamageInfo() ? eventInfo.GetDamageInfo()->GetDamage() : 0;
                bonusDamage *= 0.2f;
                //If the target already has the dot
                if (target->HasAura(SPELL_WARRIOR_TRAUMA_DOT))
                {

                    Aura* currentDot = target->GetAura(SPELL_WARRIOR_TRAUMA_DOT);
                    uint32 currentDamage = currentDot->GetEffect(EFFECT_0)->GetAmount();

                    //Get the current total damage left
                    currentDamage *= ((3 - currentDot->GetEffect(EFFECT_0)->GetTickNumber()));

                    //Add the bonus and the current
                    bonusDamage += currentDamage;
                    //Divide by number of ticks
                    bonusDamage /= 3;

                    //Cast the DoT
                    caster->CastCustomSpell(SPELL_WARRIOR_TRAUMA_DOT, SPELLVALUE_BASE_POINT0, bonusDamage, target, true);
                }
                else
                {
                    caster->CastCustomSpell(SPELL_WARRIOR_TRAUMA_DOT, SPELLVALUE_BASE_POINT0, bonusDamage, target, true);
                }
                return true;

            }

            return false;
        }

        void Register() override
        {
            DoCheckProc += AuraCheckProcFn(spell_warr_trauma_AuraScript::CheckProc);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_warr_trauma_AuraScript();
    }
};

// Overpower Proc Enabler - 60503
class spell_warrior_overpower_proc : public SpellScriptLoader
{
public:
    spell_warrior_overpower_proc() : SpellScriptLoader("spell_warrior_overpower_proc") {}

    class spell_warrior_overpower_proc_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_warrior_overpower_proc_AuraScript);

        bool CheckProc(ProcEventInfo& eventInfo)
        {
            //"Your other melee abilities have a chance to activate Overpower."
            //According to sources it should only proc on Whirlwind, Colossus Smash, Mortal Strike and Slam with a 5% chance.
            uint32 _spellId = eventInfo.GetSpellInfo()->Id;
            std::vector<uint32> spellList = { 1680, 167105, 12294, 1464 };
            for (auto id : spellList)
                if (_spellId == id)
                    return true;

            return false;
        }

        void HandleProc(AuraEffect* /*aurEff*/, ProcEventInfo& /*eventInfo*/)
        {
            Unit* caster = GetCaster();

            if (!caster->HasAura(SPELL_WARRIOR_OVERPOWER_PROC))
                caster->CastSpell(caster, SPELL_WARRIOR_OVERPOWER_PROC, true);
        }

        void Register() override
        {
            OnEffectProc += AuraEffectProcFn(spell_warrior_overpower_proc_AuraScript::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
            DoCheckProc += AuraCheckProcFn(spell_warrior_overpower_proc_AuraScript::CheckProc);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_warrior_overpower_proc_AuraScript();
    }
};

// Ravager - 152277
// Ravager - 228920
class spell_warr_ravager : public SpellScript
{
    PrepareSpellScript(spell_warr_ravager);

    void HandleOnHit(SpellEffIndex /* effIndex */)
    {
        if (WorldLocation const* dest = GetExplTargetDest())
            GetCaster()->CastSpell(dest->GetPosition(), SPELL_WARRIOR_RAVAGER_SUMMON, true);
    }

    void Register() override
    {
        OnEffectHit += SpellEffectFn(spell_warr_ravager::HandleOnHit, EFFECT_1, SPELL_EFFECT_DUMMY);
    }
};

// Ravager - 152277
// Ravager - 228920
class aura_warr_ravager : public AuraScript
{
    PrepareAuraScript(aura_warr_ravager);

    void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (Player* player = GetTarget()->ToPlayer())
            if (player->GetSpecializationId() == TALENT_SPEC_WARRIOR_PROTECTION)
                player->CastSpell(player, SPELL_WARRIOR_RAVAGER_PARRY, true);
    }

    void OnTick(AuraEffect const* /*aurEff*/)
    {
        if (Creature* creature = GetTarget()->GetSummonedCreatureByEntry(NPC_WARRIOR_RAVAGER))
            GetTarget()->CastSpell(creature->GetPosition(), SPELL_WARRIOR_RAVAGER_DAMAGE, true);
    }

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* caster = GetCaster())
            if (caster->HasAura(SPELL_WARRIOR_GATHERING_STORM_PERIODIC))
                caster->RemoveAura(SPELL_WARRIOR_GATHERING_STORM_PERIODIC);
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(aura_warr_ravager::OnApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
        OnEffectPeriodic += AuraEffectPeriodicFn(aura_warr_ravager::OnTick, EFFECT_2, SPELL_AURA_PERIODIC_DUMMY);
        OnEffectRemove += AuraEffectRemoveFn(aura_warr_ravager::HandleRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

// Ravager Damage - 156287
class spell_warr_ravager_damage : public SpellScript
{
    PrepareSpellScript(spell_warr_ravager_damage);

    void HandleOnHitTarget(SpellEffIndex /*effIndex*/)
    {
        if (!_alreadyProc)
        {
            GetCaster()->CastSpell(GetCaster(), SPELL_WARRIOR_RAVAGER_ENERGIZE, true);
            _alreadyProc = true;
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_warr_ravager_damage::HandleOnHitTarget, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }

private:
    bool _alreadyProc = false;
};

// 163201  - Execute
// 217955  - Execute
// 281000  - Execute
// 330334 - Condemn
class spell_warr_execute : public SpellScript
{
    PrepareSpellScript(spell_warr_execute);

    void HandleTakePower(SpellPowerCost& powerCost)
    {
        if (Unit* caster = GetCaster())
        {
            if (caster->HasAura(SPELL_WARRIOR_SUDDEN_DEATH))
                caster->Variables.Set<float>("EXECUTE_MULTIPLIER", 2.f);
            else
            {
                float dmgMultiplier = float(powerCost.Amount) / 20.0f;
                caster->Variables.Set<float>("EXECUTE_MULTIPLIER", dmgMultiplier);
                caster->Variables.Set<int32>("POWER_TAKEN", powerCost.Amount);
            }
        }
    }

    void HandleBeforeCast()
    {
        Unit* caster = GetCaster();
        Unit* target = GetExplTargetUnit();
        if (!caster || !target)
            return;

        if (caster->HasAura(SPELL_WARRIOR_DEATH_SENTENCE) && !caster->HasAura(Warrior::ePvpTalents::DeathSentenceCD))
        {
            caster->CastSpell(caster, Warrior::ePvpTalents::DeathSentenceCD, true);
            caster->CastSpell(target, SPELL_WARRIOR_CHARGE_EFFECT, true);
        }
    }

    void HandleAfterCast()
    {
        if (Unit* caster = GetCaster())
            caster->RemoveAura(SPELL_WARRIOR_SUDDEN_DEATH);
    }

    void Register() override
    {
        OnTakePower += SpellOnTakePowerFn(spell_warr_execute::HandleTakePower);
        BeforeCast += SpellCastFn(spell_warr_execute::HandleBeforeCast);
        AfterCast += SpellCastFn(spell_warr_execute::HandleAfterCast);
    }
};

// 260798  - Executes damages
class spell_warr_execute_damages : public SpellScript
{
    PrepareSpellScript(spell_warr_execute_damages);

    void HandleDamage(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        float damageMultiplier = caster->Variables.GetValue<float>("EXECUTE_MULTIPLIER", 1.f);
        SetHitDamage(GetHitDamage() * damageMultiplier);
        if (caster->HasAura(SPELL_WARRIOR_MASTERY_DEEP_WOUNDS))
            caster->CastSpell(target, SPELL_WARRIOR_DEEP_WOUNDS_AURA, true);
    }

    void HandleAfterHit()
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        if (target->IsAlive() && caster->Variables.Exist("POWER_TAKEN") && caster->HasAura(SPELL_WARRIOR_EXECUTE_ARMS_RANK_2))
            caster->ModifyPower(POWER_RAGE, CalculatePct(caster->Variables.GetValue<int32>("POWER_TAKEN"), 20));

        caster->Variables.Remove("EXECUTE_MULTIPLIER");
        caster->Variables.Remove("POWER_TAKEN");
    }


    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_warr_execute_damages::HandleDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
        AfterHit += SpellHitFn(spell_warr_execute_damages::HandleAfterHit);
    }
};

// Ravager - 76168
struct npc_warr_ravager : public ScriptedAI
{
    npc_warr_ravager(Creature* creature) : ScriptedAI(creature) { }

    enum eDatas
    {
        RAVAGER_DISPLAYID = 55644,
        SPELL_RAVAGER_VISUAL = 153709
    };

    void IsSummonedBy(WorldObject* summoner)
    {
        me->SetDisplayId(RAVAGER_DISPLAYID);
        me->CastSpell(me, SPELL_RAVAGER_VISUAL, true);
        me->SetReactState(ReactStates::REACT_PASSIVE);
        me->AddUnitState(UnitState::UNIT_STATE_ROOT);
        me->SetUnitFlag(UNIT_FLAG_UNINTERACTIBLE |
            UNIT_FLAG_CAN_SWIM |
            UNIT_FLAG_PLAYER_CONTROLLED);

        if (summoner == nullptr || !summoner->IsPlayer())
            return;

        if (Player* player = summoner->ToPlayer())
        {
            if (Item* item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EquipmentSlots::EQUIPMENT_SLOT_MAINHAND))
            {
                if (ItemTemplate const* l_Proto = sObjectMgr->GetItemTemplate(item->GetModifier(ITEM_MODIFIER_TRANSMOG_APPEARANCE_ALL_SPECS)))
                    me->SetVirtualItem(0, l_Proto->GetId());
                else
                    me->SetVirtualItem(0, item->GetTemplate()->GetId());
            }

            if (Item* item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EquipmentSlots::EQUIPMENT_SLOT_OFFHAND))
            {
                if (ItemTemplate const* l_Proto = sObjectMgr->GetItemTemplate(item->GetModifier(ITEM_MODIFIER_TRANSMOG_APPEARANCE_ALL_SPECS)))
                    me->SetVirtualItem(2, l_Proto->GetId());
                else
                    me->SetVirtualItem(2, item->GetTemplate()->GetId());
            }
        }
    }
};

// 262304 - Deep Wounds
class aura_warr_deep_wounds : public AuraScript
{
    PrepareAuraScript(aura_warr_deep_wounds);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetDamageInfo())
            return false;

        if (!eventInfo.GetDamageInfo()->GetDamage())
            return false;

        if (eventInfo.GetSpellInfo() && (eventInfo.GetSpellInfo()->Id == SPELL_WARRIOR_MORTAL_STRIKE || eventInfo.GetSpellInfo()->Id == SPELL_WARRIOR_EXECUTE ||
            eventInfo.GetSpellInfo()->Id == SPELL_WARRIOR_EXECUTE_PVP || eventInfo.GetSpellInfo()->Id == SPELL_WARRIOR_BLADESTORM_PERIODIC_WHIRLWIND))
            return true;

        return false;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_warr_deep_wounds::CheckProc);
    }
};

// 262231 - War Machine
class aura_warr_war_machine : public AuraScript
{
    PrepareAuraScript(aura_warr_war_machine);

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (Unit* caster = GetCaster())
            caster->CastSpell(caster, SPELL_WARRIOR_KILLING_MACHINE_SPEED, true);
    }

    void Register() override
    {
        OnProc += AuraProcFn(aura_warr_war_machine::HandleProc);
    }
};

// 202603 - Into the Fray
// AreaTriggerID - 5839
struct at_warr_into_the_fray : AreaTriggerAI
{
    at_warr_into_the_fray(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger) { }

    void OnUnitEnter(Unit* unit) override
    {
        if (Unit* caster = at->GetCaster())
        {
            if (unit->GetGUID() == caster->GetGUID())
                return;

            if (caster->IsValidAttackTarget(unit) || (caster->IsValidAssistTarget(unit) && unit->IsPlayer()))
                caster->CastSpell(caster, SPELL_WARRIOR_INTO_THE_FRAY_HASTE, true);
        }
    }

    void OnUnitExit(Unit* unit) override
    {
        if (Unit* caster = at->GetCaster())
        {
            GuidUnorderedSet list = at->GetInsideUnits();
            uint8 counter = 0;
            for (ObjectGuid guid : list)
            {
                Unit* target = ObjectAccessor::GetUnit(*caster, guid);
                if (target && (caster->IsValidAttackTarget(target) || (caster->IsValidAssistTarget(target) && target->IsPlayer())))
                    counter++;
            }

            if (caster->IsValidAttackTarget(unit) || caster->IsValidAssistTarget(unit) && counter < 5)
                if (Aura* aura = caster->GetAura(SPELL_WARRIOR_INTO_THE_FRAY_HASTE))
                    aura->ModStackAmount(-1);
        }
    }
};

// 206572 - Dragon Charge
// AreaTriggerID - 6242
struct at_warr_dragon_charge : AreaTriggerAI
{
    at_warr_dragon_charge(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger) { }

    void OnUnitEnter(Unit* unit) override
    {
        if (Unit* caster = at->GetCaster())
            if (caster->IsValidAttackTarget(unit))
                caster->CastSpell(unit, SPELL_WARRIOR_DRAGON_DAMAGE, true);
    }
};

// 236273 - Duel
// AreaTriggerID - 9761 / 9864
struct at_warr_duel : AreaTriggerAI
{
    at_warr_duel(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger) { }

    void OnUnitEnter(Unit* unit) override
    {
        Unit* caster = at->GetCaster();
        Unit* target = at->GetTarget();
        if (!caster || !target)
            return;

        if (unit->HasAura(SPELL_WARRIOR_DUEL, caster->GetGUID()))
            return;

        if (target->IsValidAttackTarget(unit))
            target->CastSpell(unit, SPELL_WARRIOR_DUEL_ENEMY, true);
    }

    void OnUnitExit(Unit* unit) override
    {
        if (Unit* target = at->GetTarget())
            unit->RemoveAura(SPELL_WARRIOR_DUEL_ENEMY, target->GetGUID());
    }
};

// 275334 - Punish
class aura_warr_punish : public AuraScript
{
    PrepareAuraScript(aura_warr_punish);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == SPELL_WARRIOR_SHIELD_SLAM)
            return true;

        return false;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_warr_punish::CheckProc);
    }
};

// 32215 - Victorius state
class aura_warr_victorius_state : public AuraScript
{
    PrepareAuraScript(aura_warr_victorius_state);

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (Unit* caster = GetCaster())
        {
            caster->CastSpell(caster, SPELL_WARRIOR_VICTORIOUS, true);
            if (caster->HasSpell(SPELL_WARRIOR_IMPENDING_VICTORY))
            {
                PreventDefaultAction();
                caster->GetSpellHistory()->ResetCooldown(SPELL_WARRIOR_IMPENDING_VICTORY, true);
            }
        }
    }

    void Register() override
    {
        OnProc += AuraProcFn(aura_warr_victorius_state::HandleProc);
    }
};

// 5301 - Revenge Trigger
class aura_warr_revenge_trigger : public AuraScript
{
    PrepareAuraScript(aura_warr_revenge_trigger);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if ((eventInfo.GetHitMask() & PROC_HIT_BLOCK) || (eventInfo.GetHitMask() & PROC_HIT_DODGE))
            return true;

        return false;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_warr_revenge_trigger::CheckProc);
    }
};

// 147833 - Intervene
class aura_warr_intervene : public AuraScript
{
    PrepareAuraScript(aura_warr_intervene);

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (GetTargetApplication()->GetRemoveMode() != AURA_REMOVE_BY_DEFAULT)
            return;

        Unit* caster = GetCaster();
        Unit* target = GetUnitOwner();
        if (!caster || !target)
            return;

        if (caster->HasAura(SPELL_WARRIOR_SAFEGUARD))
            caster->CastSpell(target, SPELL_WARRIOR_SAFEGUARD_BUFF, true);
    }

    void Register() override
    {
        OnEffectRemove += AuraEffectRemoveFn(aura_warr_intervene::HandleRemove, EFFECT_1, 111, AURA_EFFECT_HANDLE_REAL);
    }
};

// 6572 - Revenge
class spell_warr_revenge : public SpellScript
{
    PrepareSpellScript(spell_warr_revenge);

    void HandleHit()
    {
        if (Unit* caster = GetCaster())
            if (caster->HasAura(SPELL_WARRIOR_VENGEANCE_AURA))
                caster->CastSpell(caster, SPELL_WARRIOR_VENGEANCE_IGNORE_PAIN, true);
    }

    void HandleAfterCast()
    {
        if (Unit* caster = GetCaster())
            if (Aura* aura = caster->GetAura(SPELL_WARRIOR_SHIELD_SLAM_RANK2))
                if (roll_chance_i(aura->GetEffect(EFFECT_0)->GetBaseAmount()))
                {
                    caster->CastSpell(caster, SPELL_WARRIOR_SHILED_SLAM_INDICATOR, true);
                    caster->GetSpellHistory()->ResetCooldown(SPELL_WARRIOR_SHIELD_SLAM, true);
                }
    }

    void Register() override
    {
        AfterCast += SpellCastFn(spell_warr_revenge::HandleAfterCast);
        OnHit += SpellHitFn(spell_warr_revenge::HandleHit);
    }
};

// 199658 - Whirlwind Arms
class spell_warr_whirlind_arms : public SpellScript
{
    PrepareSpellScript(spell_warr_whirlind_arms);

    void HandleHit()
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;
        Unit* expTarget = ObjectAccessor::GetUnit(*caster, caster->GetTarget());
        if (!expTarget)
            return;

        if (caster->HasAura(SPELL_WARRIOR_FERVOR_OF_BATTLE) && target->GetGUID() == expTarget->GetGUID())
            caster->CastSpell(expTarget, SPELL_WARRIOR_SLAM_ARMS, true);
    }

    void Register() override
    {
        OnHit += SpellHitFn(spell_warr_whirlind_arms::HandleHit);
    }
};

// 167105 - Colossus Smash
//Last Update 8.0.1 Build 28153
class spell_warr_colossus_smash : public SpellScript
{
    PrepareSpellScript(spell_warr_colossus_smash);

    void HandleCast()
    {
        Unit* caster = GetCaster();
        if (!caster)
            return;

        if (AuraEffect* auraEff = caster->GetAuraEffect(SPELL_WARRIOR_LORD_OF_WAR_POWER, EFFECT_0))
            caster->CastCustomSpell(SPELL_WARRIOR_LORD_OF_WAR_ENERGIZE, SPELLVALUE_BASE_POINT0, auraEff->GetAmount(), caster);
    }

    void HandleHitTarget(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        caster->CastSpell(target, SPELL_WARRIOR_COLOSSUS_SMASH_BUFF, true);

        // In For the Kill
        if (caster->HasAura(SPELL_WARRIOR_IN_FOR_THE_KILL))
            if (target->HealthBelowPct(20))
                caster->CastCustomSpell(SPELL_WARRIOR_IN_FOR_THE_KILL_BUFF, SPELLVALUE_BASE_POINT0, 20, caster, true);
            else
                caster->CastSpell(caster, SPELL_WARRIOR_IN_FOR_THE_KILL_BUFF, true);
    }

    void Register() override
    {
        OnCast += SpellCastFn(spell_warr_colossus_smash::HandleCast);
        OnEffectHitTarget += SpellEffectFn(spell_warr_colossus_smash::HandleHitTarget, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

// 262161 - Warbreaker
//Last Update 8.0.1 Build 28153
class spell_warr_warbraker : public SpellScript
{
    PrepareSpellScript(spell_warr_warbraker);

    void HandleCast()
    {
        Unit* caster = GetCaster();
        if (!caster)
            return;

        if (AuraEffect* auraEff = caster->GetAuraEffect(SPELL_WARRIOR_LORD_OF_WAR_POWER, EFFECT_0))
            caster->CastCustomSpell(SPELL_WARRIOR_LORD_OF_WAR_ENERGIZE, SPELLVALUE_BASE_POINT0, auraEff->GetAmount(), caster);
    }

    void HandleHitTarget(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        caster->CastSpell(target, SPELL_WARRIOR_COLOSSUS_SMASH_BUFF, true);

        // In For the Kill
        if (caster->HasAura(SPELL_WARRIOR_IN_FOR_THE_KILL))
            if (target->HealthBelowPct(20))
                caster->CastCustomSpell(SPELL_WARRIOR_IN_FOR_THE_KILL_BUFF, SPELLVALUE_BASE_POINT0, 20, caster, true);
            else
                caster->CastSpell(caster, SPELL_WARRIOR_IN_FOR_THE_KILL_BUFF, true);
    }

    void Register() override
    {
        OnCast += SpellCastFn(spell_warr_warbraker::HandleCast);
        OnEffectHitTarget += SpellEffectFn(spell_warr_warbraker::HandleHitTarget, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

// 5246 - Intimidating Shout
class aura_warr_intimidating_shout : public AuraScript
{
    PrepareAuraScript(aura_warr_intimidating_shout);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetDamageInfo())
            return false;

        Aura* aura = GetAura();
        int chance = 25;
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
                owner->ToUnit()->RemoveAura(SPELL_WARRIOR_INTIMIDATING_SHOUT);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_warr_intimidating_shout::CheckProc);
        OnProc += AuraProcFn(aura_warr_intimidating_shout::HandleProc);
    }
};

// 268243 - Collateral Damage
class aura_warr_collateral_damage : public AuraScript
{
    PrepareAuraScript(aura_warr_collateral_damage);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_WARRIOR_COLLATERAL_DAMAGE, SPELL_WARRIOR_COLLATERAL_DAMAGE_ENERGIZE });
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        int32 rageSpent = 0;
        if (Unit* caster = GetCaster())
        {
            if (!caster->HasAura(SPELL_WARRIOR_SWEEPING_STRIKE))
                return;

            if (eventInfo.GetSpellInfo())
                for (SpellPowerCost cost : eventInfo.GetSpellInfo()->CalcPowerCost(caster, eventInfo.GetSpellInfo()->GetSchoolMask()))
                {
                    if (cost.Power != POWER_RAGE)
                        continue;

                    rageSpent = cost.Amount;
                }

            if (rageSpent == 0)
                return;

            if (Unit* target = ObjectAccessor::GetUnit(*caster, caster->GetTarget()))
                if (target->GetGUID() != eventInfo.GetActionTarget()->GetGUID())
                {
                    uint8 percent = sSpellMgr->GetSpellInfo(SPELL_WARRIOR_COLLATERAL_DAMAGE)->GetEffect(EFFECT_0).BasePoints;
                    caster->CastCustomSpell(SPELL_WARRIOR_COLLATERAL_DAMAGE_ENERGIZE, SPELLVALUE_BASE_POINT0, CalculatePct(rageSpent, percent), caster, true);
                }
        }
    }

    void Register() override
    {
        OnProc += AuraProcFn(aura_warr_collateral_damage::HandleProc);
    }
};

// 845 - Cleave
class spell_warr_cleave : public SpellScript
{
    PrepareSpellScript(spell_warr_cleave);

    void HandleHit()
    {
        if (Unit* target = GetHitUnit())
            targets.push_back(target->GetGUID());
    }

    void HandleAfterCast()
    {
        if (Unit* caster = GetCaster())
            if (targets.size() >= 3)
                for (ObjectGuid guid : targets)
                {
                    Unit* target = ObjectAccessor::GetUnit(*caster, guid);
                    if (caster->IsValidAttackTarget(target))
                        caster->CastSpell(target, SPELL_WARRIOR_DEEP_WOUNDS_AURA, true);
                }
    }

    void Register() override
    {
        OnHit += SpellHitFn(spell_warr_cleave::HandleHit);
        AfterCast += SpellCastFn(spell_warr_cleave::HandleAfterCast);
    }

private:
    std::list<ObjectGuid> targets;
};

// 202225 - Furious Charge
class aura_warr_furious_charge : public AuraScript
{
    PrepareAuraScript(aura_warr_furious_charge);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == SPELL_WARRIOR_BLOODTHIRST_DAMAGE)
            return true;

        return false;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_warr_furious_charge::CheckProc);
    }
};

// 215571 - Frothing Berserker
class aura_warr_frothing_berserker : public AuraScript
{
    PrepareAuraScript(aura_warr_frothing_berserker);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == SPELL_WARRIOR_RAMPAGE)
            return true;

        return false;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_warr_frothing_berserker::CheckProc);
    }
};

// 5308 - Execute (Fury)
class spell_warr_execute_fury : public SpellScript
{
    PrepareSpellScript(spell_warr_execute_fury);

    void HandleAfterCast()
    {
        if (Unit* caster = GetCaster())
            caster->RemoveAura(SPELL_WARRIOR_SUDDEN_DEATH_FURY);
    }

    void Register() override
    {
        AfterCast += SpellCastFn(spell_warr_execute_fury::HandleAfterCast);
    }
};

// 213857 - Battle Trance
class aura_warr_battle_trance : public AuraScript
{
    PrepareAuraScript(aura_warr_battle_trance);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == SPELL_WARRIOR_RAGING_BLOW)
            return true;

        return false;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();
        Unit* target = eventInfo.GetActionTarget();
        if (!caster || !target)
            return;

        if (caster->Variables.Exist("BATTE_TRANCE_TARGET"))
            if (caster->Variables.GetValue<ObjectGuid>("BATTE_TRANCE_TARGET") == target->GetGUID())
            {
                caster->CastSpell(caster, SPELL_WARRIOR_BATTLE_TRACE, true);
                caster->Variables.Remove("BATTE_TRANCE_TARGET");
                caster->Variables.Set<ObjectGuid>("LAST_BATTLE_TRANCE_TARGET", target->GetGUID());
                return;
            }

        caster->Variables.Set<ObjectGuid>("BATTE_TRANCE_TARGET", target->GetGUID());
        if (caster->Variables.Exist("LAST_BATTLE_TRANCE_TARGET") && caster->Variables.GetValue<ObjectGuid>("LAST_BATTLE_TRANCE_TARGET") != target->GetGUID())
        {
            caster->RemoveAurasDueToSpell(SPELL_WARRIOR_BATTLE_TRACE);
            caster->Variables.Remove("LAST_BATTLE_TRANCE_TARGET");
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_warr_battle_trance::CheckProc);
        OnProc += AuraProcFn(aura_warr_battle_trance::HandleProc);
    }
};

// 280745 - Barbarian
class aura_warr_barbarian : public AuraScript
{
    PrepareAuraScript(aura_warr_barbarian);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_warr_barbarian::CheckProc);
    }
};

// 280746 - Barbarian Buff
class aura_warr_barbarian_buff : public AuraScript
{
    PrepareAuraScript(aura_warr_barbarian_buff);

    void HandleApply(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /* mode */)
    {
        if (Unit* caster = GetCaster())
            caster->GetSpellHistory()->ResetCharges(sSpellMgr->GetSpellInfo(SPELL_WARRIOR_HEROIC_LEAP)->ChargeCategoryId);
    }

    void HandleRemove(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /* mode */)
    {
        if (Unit* caster = GetCaster())
        {
            int32 cooldown = caster->GetSpellHistory()->GetChargeRecoveryTime(sSpellMgr->GetSpellInfo(SPELL_WARRIOR_HEROIC_LEAP)->ChargeCategoryId);
            caster->GetSpellHistory()->StartCooldownROG(sSpellMgr->GetSpellInfo(SPELL_WARRIOR_HEROIC_LEAP), 0, NULL, false, true, cooldown);
        }
    }

    void Register() override
    {
        AfterEffectApply += AuraEffectApplyFn(aura_warr_barbarian_buff::HandleApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        OnEffectRemove += AuraEffectRemoveFn(aura_warr_barbarian_buff::HandleRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

// 198817 - Sharpen Blade
class aura_warr_sharpen_blade : public AuraScript
{
    PrepareAuraScript(aura_warr_sharpen_blade);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_warr_sharpen_blade::CheckProc);
    }
};

// 85739 - Whirlwind
class aura_warr_whirlwind_fury : public AuraScript
{
    PrepareAuraScript(aura_warr_whirlwind_fury);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetSpellInfo() && (eventInfo.GetSpellInfo()->Id == SPELL_WARRIOR_FURIOUS_SLASH || eventInfo.GetSpellInfo()->Id == SPELL_WARRIOR_RAGING_BLOW ||
            eventInfo.GetSpellInfo()->Id == SPELL_WARRIOR_BLOODTHIRST_DAMAGE || eventInfo.GetSpellInfo()->Id == SPELL_WARRIOR_RAGING_BLOW || eventInfo.GetSpellInfo()->Id == SPELL_WARRIOR_IMPENDING_VICTORY ||
            eventInfo.GetSpellInfo()->Id == SPELL_WARRIOR_EXECUTE || eventInfo.GetSpellInfo()->Id == SPELL_WARRIOR_EXECUTE_PVP || eventInfo.GetSpellInfo()->Id == SPELL_WARRIOR_VICTORY_RUSH_DAMAGE ||
            eventInfo.GetSpellInfo()->Id == SPELL_WARRIOR_OVERPOWER || eventInfo.GetSpellInfo()->Id == SPELL_WARRIOR_SIEGEBREAKER))
        {
            GetAura()->ModStackAmount(-1);
            return true;
        }

        return false;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_warr_whirlwind_fury::CheckProc);
    }
};

// 107574 - Avatar
class spell_warr_avatar : public SpellScript
{
    PrepareSpellScript(spell_warr_avatar);

    void HandleHit()
    {
        if (Unit* caster = GetCaster())
            caster->RemoveMovementImpairingAuras(true);
    }

    void Register() override
    {
        OnHit += SpellHitFn(spell_warr_avatar::HandleHit);
    }
};

// 236282 - Devastator Damage
class spell_warr_devastator_damage : public SpellScript
{
    PrepareSpellScript(spell_warr_devastator_damage);

    void HandleHit()
    {
        if (Unit* caster = GetCaster())
            if (roll_chance_i(20))
            {
                caster->GetSpellHistory()->ResetCooldown(SPELL_WARRIOR_SHIELD_SLAM, true);
                caster->CastSpell(caster, SPELL_WARRIOR_SHILED_SLAM_INDICATOR, true);
            }
    }

    void Register() override
    {
        OnHit += SpellHitFn(spell_warr_devastator_damage::HandleHit);
    }
};

// 213871 - Bodyguard
class aura_warr_bodyguard : public AuraScript
{
    PrepareAuraScript(aura_warr_bodyguard);

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetTarget();
        if (!caster || !target)
            return;

        if (caster->GetDistance(target) > sSpellMgr->GetSpellInfo(SPELL_WARRIOR_BODYGUARD)->GetEffect(EFFECT_1).BasePoints)
            target->RemoveAura(SPELL_WARRIOR_BODYGUARD, caster->GetGUID());
    }

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetDamageInfo() && eventInfo.GetDamageInfo()->GetSchoolMask() == SPELL_SCHOOL_MASK_NORMAL)
            return true;

        return false;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (Unit* caster = GetCaster())
        {
            caster->GetSpellHistory()->ResetCooldown(SPELL_WARRIOR_SHIELD_SLAM, true);
            caster->CastSpell(caster, SPELL_WARRIOR_SHILED_SLAM_INDICATOR, true);
        }
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(aura_warr_bodyguard::HandlePeriodic, EFFECT_1, SPELL_AURA_PERIODIC_DUMMY);
        DoCheckProc += AuraCheckProcFn(aura_warr_bodyguard::CheckProc);
        OnProc += AuraProcFn(aura_warr_bodyguard::HandleProc);
    }
};

// 52174 - Heroic Leap Damage
class spell_warr_heroic_leap_damage : public SpellScript
{
    PrepareSpellScript(spell_warr_heroic_leap_damage);

    void HandleHit()
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        if (caster->HasAura(SPELL_WARRIOR_WARPATH))
            caster->CastSpell(target, SPELL_WARRIOR_WARPATH_STUN, true);
    }

    void Register() override
    {
        OnHit += SpellHitFn(spell_warr_heroic_leap_damage::HandleHit);
    }
};

// War Banner - 119052
class npc_warrior_war_banner : public ScriptedAI
{
public:
    npc_warrior_war_banner(Creature* creature) : ScriptedAI(creature) {}

    void Reset() override
    {
        if (Unit* owner = me->GetOwner())
        {
            me->SetReactState(REACT_PASSIVE);
            me->AddUnitState(UNIT_STATE_ROOT);
            me->SetHealth(owner->CountPctFromMaxHealth(5));
            me->SetMaxHealth(owner->CountPctFromMaxHealth(5));
        }
    }

    void UpdateAI(uint32 diff) override
    {
        if (timer <= diff)
        {
            timer = 1000;

            Unit* owner = me->GetOwner();
            if (!owner)
                return;

            UnitList targets;
            me->GetFriendlyUnitListInRange(targets, 30.f, true);
            targets.remove_if([owner](Unit* target)
            {
                if (!owner->IsValidAssistTarget(target))
                    return true;

                if (!target->ToPlayer())
                    return true;

                if (!owner->ToPlayer()->IsInSameGroupWith(target->ToPlayer()) && !owner->ToPlayer()->IsInSameRaidWith(target->ToPlayer()))
                    return true;

                return false;
            });

            for (Unit* target : targets)
                if (!target->HasAura(SPELL_WARRIOR_WAR_BANNER_BUFF, me->GetGUID()))
                    me->AddAura(SPELL_WARRIOR_WAR_BANNER_BUFF, target);
        }
        else timer -= diff;
    }

private:
    uint32 timer;
};

// 236321 - War Banner
class aura_war_war_banner : public AuraScript
{
    PrepareAuraScript(aura_war_war_banner);

    void Update(uint32 diff)
    {
        if (Unit* target = GetUnitOwner())
            if (tick <= diff)
            {
                tick = 1 * IN_MILLISECONDS;
                if (Unit* caster = GetCaster())
                {
                    if (caster->GetDistance(target) > 30.f)
                        target->RemoveAura(SPELL_WARRIOR_WAR_BANNER_BUFF, caster->GetGUID());
                }
                else
                    target->RemoveAura(SPELL_WARRIOR_WAR_BANNER_BUFF);
            }
            else
                tick -= diff;
    }

    void Register() override
    {
        OnAuraUpdate += AuraUpdateFn(aura_war_war_banner::Update);
    }

private:
    uint32 tick = 1 * IN_MILLISECONDS;
};

// 199667 - Whirlwind Main Hand
class spell_warr_whirlwind_main_hand : public SpellScript
{
    PrepareSpellScript(spell_warr_whirlwind_main_hand);

    void HandleHitTarget(SpellEffIndex /*effIndex*/)
    {
        if (Unit* caster = GetCaster())
        {
            auto rage = caster->Variables.GetValue("rage", 0);
            if (rage < 80)
            {
                caster->CastCustomSpell(SPELL_WARRIOR_WHIRLWIND_ENERGIZE, SPELLVALUE_BASE_POINT0, 10, caster, true);

                caster->Variables.Set("rage", rage + 10);
            }
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_warr_whirlwind_main_hand::HandleHitTarget, EFFECT_1, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

// 202296 - Endless Rage
class aura_warr_endless_rage : public AuraScript
{
    PrepareAuraScript(aura_warr_endless_rage);

    bool CheckProc(ProcEventInfo& /*eventInfo*/)
    {
        return false;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_warr_endless_rage::CheckProc);
    }
};

// 199202 - Thirst for Battle
class aura_warr_thrist_for_battle : public AuraScript
{
    PrepareAuraScript(aura_warr_thrist_for_battle);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == SPELL_WARRIOR_BLOODTHIRST_DAMAGE)
            return true;

        return false;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_warr_thrist_for_battle::CheckProc);
    }
};

// 236308 - Storm of Destruction
class aura_warr_storm_of_destruction : public AuraScript
{
    PrepareAuraScript(aura_warr_storm_of_destruction);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetSpellInfo() && (eventInfo.GetSpellInfo()->Id == SPELL_WARRIOR_BLADESTORM_PERIODIC_WHIRLWIND || eventInfo.GetSpellInfo()->Id == SPELL_WARRIOR_RAVAGER_DAMAGE))
            return true;

        return false;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_warr_storm_of_destruction::CheckProc);
    }
};

// 152278 - Anger Management
class aura_warr_anger_management : public AuraScript
{
    PrepareAuraScript(aura_warr_anger_management);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (Unit* caster = GetCaster())
            if (Player* player = caster->ToPlayer())
                if (Spell const* procSpell = eventInfo.GetProcSpell())
                    if (SpellPowerCost const* powerCost = procSpell->GetPowerCost(POWER_RAGE))
                        if (powerCost->Amount > 0)
                        {
                            const SpellInfo* info = sSpellMgr->GetSpellInfo(SPELL_WARRIOR_ANGER_MANAGEMENT);
                            int32 rage = (player->GetSpecializationId() == TALENT_SPEC_WARRIOR_PROTECTION) ? info->GetEffect(EFFECT_1).BasePoints : info->GetEffect(EFFECT_0).BasePoints;
                            if (powerCost->Amount >= rage)
                            {
                                cost = (int32)(powerCost->Amount * 0.1f);
                                return true;
                            }
                        }

        return false;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (cost == 0)
            return;

        if (Unit* caster = GetCaster())
            if (Player* player = caster->ToPlayer())
            {
                const SpellInfo* info = sSpellMgr->GetSpellInfo(SPELL_WARRIOR_ANGER_MANAGEMENT);
                uint32 rage = (player->GetSpecializationId() == TALENT_SPEC_WARRIOR_PROTECTION) ? info->GetEffect(EFFECT_1).BasePoints : info->GetEffect(EFFECT_0).BasePoints;
                // Modify lots of cooldowns.
                for (uint8 i = 0; i < 8; i++)
                {
                    // Avatar only resets on Protection.
                    if (spellsAffectedByAngerManagement[i] == 107574 && player->GetSpecializationId() != TALENT_SPEC_WARRIOR_PROTECTION)
                        continue;

                    caster->GetSpellHistory()->ModifyCooldown(spellsAffectedByAngerManagement[i], (int32)(cost / rage) * -1s);
                }
            }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_warr_anger_management::CheckProc);
        OnProc += AuraProcFn(aura_warr_anger_management::HandleProc);
    }

private:
    int32 cost = 0;

    uint32 spellsAffectedByAngerManagement[8] =
    {
        // Arms
        227847, // Bladestorm
        167105, // Colossus Smash
        262161, // Warbreaker
        // Fury 
        1719,   // Recklessness
        // Protection 
        107574, // Avatar
        12975,  // Last Stand
        871,    // Shield Wall
        1160,   // Demoralizing Shout
    };
};

// Last Update 8.0.1 Build 28153
// Called By Enduring Rage - 198877
class aura_warr_enduring_rage : public AuraScript
{
    PrepareAuraScript(aura_warr_enduring_rage);

    void HandleOnProc(ProcEventInfo& procEventInfo)
    {
        SpellInfo const* baseSpellInfo = GetSpellInfo();
        if (!baseSpellInfo)
            return;

        DamageInfo* damageInfo = procEventInfo.GetDamageInfo();
        Unit* caster = GetCaster();
        if (!damageInfo || !caster)
            return;

        SpellInfo const* spellInfo = damageInfo->GetSpellInfo();
        if (!spellInfo || spellInfo->Id != SPELL_WARRIOR_RAGING_BLOW)
            return;

        Aura* aura = caster->GetAura(SPELL_WARRIOR_ENRAGE_AURA);
        if (!aura)
            return;

        aura->SetDuration(aura->GetDuration() + baseSpellInfo->GetEffect(EFFECT_2).BasePoints);
        aura->SetMaxDuration(aura->GetDuration() + baseSpellInfo->GetEffect(EFFECT_2).BasePoints);
    }

    void Register() override
    {
        OnProc += AuraProcFn(aura_warr_enduring_rage::HandleOnProc);
    }
};

//1719 Recklessness
// Last Update 8.0.1 Build 28153
class aura_warr_recklessness : public AuraScript
{
    PrepareAuraScript(aura_warr_recklessness);

    void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Unit* caster = GetCaster();
        if (!caster)
            return;

        if (AuraEffect* auraEff = caster->GetAuraEffect(SPELL_WARRIOR_INFINITE_FURY_POWER, EFFECT_0))
            caster->CastCustomSpell(SPELL_WARRIOR_INFINITE_FURY_BUFF, SPELLVALUE_BASE_POINT0, auraEff->GetAmount(), caster);
    }

    void Register() override
    {
        OnEffectRemove += AuraEffectRemoveFn(aura_warr_recklessness::OnRemove, EFFECT_0, SPELL_AURA_ADD_FLAT_MODIFIER, AURA_EFFECT_HANDLE_REAL);
    }
};

/// ID: 3411 Intervene
class spell_intervene : public SpellScript
{
    PrepareSpellScript(spell_intervene);

    enum Intervene
    {
        InterveneTrigger = 34784,
    };

    SpellCastResult CheckWay()
    {
        Unit* caster = GetCaster();
        if (!caster)
            return SPELL_FAILED_DONT_REPORT;

        if (!GetExplTargetUnit())
            return SPELL_FAILED_NO_VALID_TARGETS;

        if (Unit* target = GetExplTargetUnit())
        {
            Position const& pos = target->GetPosition();
            if (!caster->IsWithinLOS(pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ()))
                return SPELL_FAILED_LINE_OF_SIGHT;
        }

        return SPELL_CAST_OK;
    }


    void HandleDummy(SpellEffIndex /*eff*/)
    {
        if (Unit* caster = GetCaster())
        {
            if (Unit* target = GetHitUnit())
                caster->CastSpell(target, InterveneTrigger, true);
        }
    }

    void Register() override
    {
        OnCheckCast += SpellCheckCastFn(spell_intervene::CheckWay);
        OnEffectHitTarget += SpellEffectFn(spell_intervene::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};
/// ID: 115768 Deep Wounds
class spell_deep_wounds_115768 : public AuraScript
{
    PrepareAuraScript(spell_deep_wounds_115768);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (auto spellInfo = eventInfo.GetSpellInfo())
        {
            if (spellInfo->Id == 262115 || spellInfo->Id == 115767)
                return false;
        }

        return true;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_deep_wounds_115768::CheckProc);
    }
};

void AddSC_warrior_spell_scripts()
{
    RegisterSpellScript(spell_warr_bloodthirst);
    RegisterSpellScript(spell_warr_colossus_smash);
    new spell_warr_heroic_leap();
    RegisterSpellScript(spell_warr_heroic_leap_jump);
    RegisterSpellScript(spell_warr_impending_victory);
    RegisterSpellScript(spell_warr_item_t10_prot_4p_bonus);
    new spell_warr_mortal_strike();
    new spell_warr_rallying_cry();
    new spell_warr_shockwave();
    new spell_warr_storm_bolt();
    RegisterSpellScript(spell_warr_sudden_death);
    RegisterSpellScript(spell_warr_sweeping_strikes);
    new spell_warr_trauma();
    RegisterSpellScript(spell_warr_t3_prot_8p_bonus);
    RegisterSpellScript(spell_warr_victorious_state);
    RegisterSpellScript(spell_warr_victory_rush);
    new spell_warr_enrage();
    new spell_warr_rampage();
    new spell_warr_raging_blow();
    new spell_warr_bladestorm_offhand();
    RegisterSpellScript(aura_warr_bladestorm);
    RegisterAreaTriggerAI(at_warr_kyrian_spear);
    RegisterAreaTriggerAI(at_warr_ancient_aftershock);

    new spell_warr_berzerker_rage();
    new spell_warr_blood_bath();
    RegisterSpellScript(spell_warr_charge);
    RegisterSpellScript(spell_warr_charge_drop_fire_periodic);
    RegisterSpellScript(spell_warr_charge_effect);
    new spell_warr_siegebreaker();
    new spell_warr_defensive_stance();
    new spell_warr_devastate();
    new spell_warr_dragon_roar();
    new spell_warr_enrage_aura();
    new spell_warr_focused_rage_arms();
    new spell_warr_focused_rage_prot();
    new spell_warr_frenzy();
    RegisterSpellAndAuraScriptPair(spell_warr_ignore_pain, aura_warr_ignore_pain);
    new spell_warr_improved_spell_reflection();
    new spell_warr_intercept();
    RegisterSpellAndAuraScriptPair(spell_warr_intimidating_shout, aura_warr_intimidating_shout);
    new spell_warr_last_stand();
    new spell_warr_massacre();
    new spell_warr_meat_cleaver();
    new spell_warr_odyns_fury();
    new spell_warr_opportunity_strike();
    RegisterSpellAndAuraScriptPair(spell_warr_overpower, aura_warr_overpower);
    new spell_warr_rend();
    new spell_warr_retaliation();
    new spell_warr_safeguard();
    new spell_warr_shattering_throw();
    new spell_warr_shield_block();
    new spell_warr_shield_slam();
    RegisterSpellScript(spell_warr_slam);
    new spell_warr_spell_reflect();
    new spell_warr_tactician();
    new spell_warr_taste_for_blood();
    new spell_warr_thunder_clap();
    new spell_warr_unrivaled_strenght();
    new spell_warr_victorious();
    new spell_warr_vigilance();
    new spell_warr_vigilance_trigger();
    RegisterSpellScript(spell_warr_whirlwind);
    new spell_warr_wrecking_ball_effect();
    new spell_warr_jump_to_skyhold();
    RegisterSpellScript(spell_warr_commanding_shout);
    RegisterSpellAndAuraScriptPair(spell_warr_ravager, aura_warr_ravager);
    RegisterSpellScript(spell_warr_ravager_damage);
    RegisterSpellScript(spell_warr_execute);
    RegisterSpellScript(spell_warr_execute_damages);
    RegisterSpellScript(aura_warr_deep_wounds);
    RegisterCreatureAI(npc_warr_ravager);
    RegisterSpellScript(aura_warr_war_machine);
    RegisterSpellScript(aura_warr_sudden_death_talent);
    RegisterSpellScript(aura_warr_sudden_death);
    RegisterSpellScript(aura_warr_punish);
    RegisterSpellScript(aura_warr_victorius_state);
    RegisterSpellScript(aura_warr_revenge_trigger);
    RegisterSpellScript(aura_warr_intervene);
    RegisterSpellScript(spell_warr_revenge);
    RegisterSpellScript(spell_warr_whirlind_arms);
    RegisterSpellScript(spell_warr_warbraker);
    RegisterSpellScript(aura_warr_collateral_damage);
    RegisterSpellScript(spell_warr_cleave);
    RegisterSpellScript(aura_warr_furious_charge);
    RegisterSpellScript(aura_warr_frothing_berserker);
    RegisterSpellScript(spell_warr_execute_fury);
    RegisterSpellScript(aura_warr_battle_trance);
    RegisterSpellScript(aura_warr_barbarian);
    RegisterSpellScript(aura_warr_barbarian_buff);
    RegisterSpellScript(aura_warr_sharpen_blade);
    RegisterSpellScript(aura_warr_whirlwind_fury);
    RegisterSpellScript(spell_warr_avatar);
    RegisterSpellScript(spell_warr_devastator_damage);
    RegisterSpellScript(aura_warr_bodyguard);
    RegisterSpellScript(spell_warr_heroic_leap_damage);
    RegisterSpellScript(aura_war_war_banner);
    RegisterSpellScript(spell_warr_whirlwind_main_hand);
    RegisterSpellScript(aura_warr_endless_rage);
    RegisterSpellScript(aura_warr_thrist_for_battle);
    RegisterSpellScript(aura_warr_storm_of_destruction);
    RegisterSpellScript(aura_warr_anger_management);
    RegisterSpellScript(aura_warr_enduring_rage);
    RegisterSpellScript(aura_warr_recklessness);
    RegisterSpellScript(aura_warr_second_wind);
    RegisterSpellScript(aura_warr_second_wind_damaged);
    RegisterSpellScript(spell_intervene);
    RegisterSpellScript(spell_deep_wounds_115768);

    // Area Trigger scripts
    RegisterAreaTriggerAI(at_warr_into_the_fray);
    RegisterAreaTriggerAI(at_warr_dragon_charge);
    RegisterAreaTriggerAI(at_warr_duel);

    // Npcs scripts
    RegisterCreatureAI(npc_warrior_war_banner);
}
