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
 * Scripts for spells with SPELLFAMILY_ROGUE and SPELLFAMILY_GENERIC spells used by rogue players.
 * Ordered alphabetically using scriptname.
 * Scriptnames of files in this file should be prefixed with "spell_rog_".
 */

#include "spell_rogue.h"

using namespace Rogue;

enum RogueSpells
{
    SPELL_ROGUE_ADRENALINE_RUSH                     = 13750,
    SPELL_ROGUE_ALACRITY                            = 193539,
    SPELL_ROGUE_ALACRITY_BUFF                       = 193538,
    SPELL_ROGUE_BLADE_FLURRY                        = 13877,
    SPELL_ROGUE_BLADE_FLURRY_EXTRA_ATTACK           = 22482,
    SPELL_ROGUE_CANNONBALL_BARRAGE_DAMAGE           = 185779,
    SPELL_ROGUE_CANNONBALL_BARRAGE_SLOW             = 185778,
    SPELL_ROGUE_CHEAT_DEATH_COOLDOWN                = 45181,
    SPELL_ROGUE_CHEAT_DEATH_REDUCE_DAMAGE           = 45182,
    SPELL_ROGUE_CRIMSON_TEMPEST_DOT                 = 122233,
    SPELL_ROGUE_CRIPPLING_POISON                    = 3408,
    SPELL_ROGUE_CRIPPLING_POISON_DEBUFF             = 3409,
    SPELL_ROGUE_CUT_TO_THE_CHASE_AURA               = 51667,
    SPELL_ROGUE_DEADLY_POISON                       = 2823,
    SPELL_ROGUE_DEADLY_POISON_DOT                   = 2818,
    SPELL_ROGUE_DEADLY_POISON_INSTANT_DAMAGE        = 113780,
    SPELL_ROGUE_DEATH_FROM_ABOVE_DAMAGE_BONUS       = 163786,
    SPELL_ROGUE_DEATH_FROM_ABOVE_JUMP               = 178153,
    SPELL_ROGUE_DEBILITATING_POISON                 = 115196,
    SPELL_ROGUE_DEEPENING_SHADOWS                   = 185314,
    SPELL_ROGUE_DEEPER_STRATAGEM                    = 193531,
    SPELL_ROGUE_ENERGETIC_RECOVERY_AURA             = 79152,
    SPELL_ROGUE_ENVELOPING_SHADOWS                  = 206237,
    SPELL_ROGUE_ENVENOM                             = 32645,
    SPELL_ROGUE_EVISCERATE                          = 196819,
    SPELL_ROGUE_FAN_OF_KNIVES                       = 51723,
    SPELL_ROGUE_GARROTE_DOT                         = 703,
    SPELL_ROGUE_GARROTE_SILENCE                     = 1330,
    SPELL_ROGUE_GLYPH_OF_EXPOSE_ARMOR               = 56803,
    SPELL_ROGUE_GLYPH_OF_HEMORRHAGE                 = 56807,
    SPELL_ROGUE_GLYPH_OF_PREPARATION                = 56819,
    SPELL_ROGUE_GLYPH_OF_REGENERATE                 = 146625,
    SPELL_ROGUE_GRAPPLING_HOOK_TRIGGER              = 227180,
    SPELL_ROGUE_HEMORRHAGE_DOT                      = 89775,
    SPELL_ROGUE_HONOR_AMONG_THIEVES                 = 51698,
    SPELL_ROGUE_HONOR_AMONG_THIEVES_PROC            = 51699,
    SPELL_ROGUE_KIDNEY_SHOT                         = 408,
    SPELL_ROGUE_KILLING_SPREE                       = 51690,
    SPELL_ROGUE_KILLING_SPREE_DMG_BUFF              = 61851,
    SPELL_ROGUE_KILLING_SPREE_TELEPORT              = 57840,
    SPELL_ROGUE_KILLING_SPREE_WEAPON_DMG            = 57841,
    SPELL_ROGUE_LEECHING_POISON                     = 108211,
    SPELL_ROGUE_LEECHING_POISON_DEBUFF              = 112961,
    SPELL_ROGUE_LEECH_VITALITY                      = 116921,
    SPELL_ROGUE_MASTERY_MAIN_GAUCHE_DAMAGE          = 86392,
    SPELL_ROGUE_MASTER_OF_SHADOWS                   = 196976,
    SPELL_ROGUE_MASTER_OF_SUBTLETY_DAMAGE_PERCENT   = 31665,
    SPELL_ROGUE_MASTER_OF_SUBTLETY_PASSIVE          = 31223,
    SPELL_ROGUE_MASTER_POISONER_AURA                = 58410,
    SPELL_ROGUE_MASTER_POISONER_DEBUFF              = 93068,
    SPELL_ROGUE_MIND_NUMBLING_POISON                = 5761,
    SPELL_ROGUE_MIND_PARALYSIS                      = 115194,
    SPELL_ROGUE_NERVE_STRIKE_AURA                   = 108210,
    SPELL_ROGUE_NERVE_STRIKE_REDUCE_DAMAGE_DONE     = 112947,
    SPELL_ROGUE_NIGHTBLADE                          = 195452,
    SPELL_ROGUE_NIGHTBLADE_SLOW                     = 206760,
    SPELL_ROGUE_NIGHTSTALKER_AURA                   = 14062,
    SPELL_ROGUE_NIGHTSTALKER_DAMAGE_DONE            = 130493,
    SPELL_ROGUE_OPPORTUNITY                         = 195627,
    SPELL_ROGUE_PARALYTIC_POISON                    = 108215,
    SPELL_ROGUE_PARALYTIC_POISON_DEBUFF             = 113952,
    SPELL_ROGUE_PARTIAL_PARALYSIS                   = 115197,
    SPELL_ROGUE_PISTOL_SHOT                         = 185763,
    SPELL_ROGUE_RECUPERATE                          = 73651,
    SPELL_ROGUE_REDIRECT                            = 73981,
    SPELL_ROGUE_RELENTLESS_STRIKES                  = 58423,
    SPELL_ROGUE_RELENTLESS_STRIKES_POWER            = 98440,
    SPELL_ROGUE_RESTLESS_BLADES                     = 79096,
    SPELL_ROGUE_RIPOSTE_DAMAGE                      = 199753,
    SPELL_ROGUE_ROLL_THE_BONES                      = 193316,
    SPELL_ROGUE_ROLL_THE_BONES_VISUAL               = 208244,
    SPELL_ROGUE_RUN_THROUGH                         = 2098,
    SPELL_ROGUE_RUPTURE                             = 1943,
    SPELL_ROGUE_RUPTURE_DOT                         = 1943,
    SPELL_ROGUE_SANCTUARY                           = 98877,
    SPELL_ROGUE_SANGUINARY_VEIN_DEBUFF              = 124271,
    SPELL_ROGUE_SERRATED_BLADES_R1                  = 14171,
    SPELL_ROGUE_SHADOWSTEP_LEAP                     = 36563,
    SPELL_ROGUE_SHADOWSTRIKE                        = 185438,
    SPELL_ROGUE_SHADOW_BLADES                       = 121471,
    SPELL_ROGUE_SHADOW_DANCE                        = 185313,
    SPELL_ROGUE_SHADOW_DANCE_AURA                   = 185422,
    SPELL_ROGUE_SHADOW_FOCUS                        = 108209,
    SPELL_ROGUE_SHADOW_FOCUS_COST_PCT               = 112942,
    SPELL_ROGUE_SHADOW_TENCHNIQUES_POWER            = 196911,
    SPELL_ROGUE_SHIV_TRIGGERED                      = 5940,
    SPELL_ROGUE_SHROUD_OF_CONCEALMENT_AURA          = 115834,
    SPELL_ROGUE_SHURIKEN_STORM                      = 197835,
    SPELL_ROGUE_SLICE_AND_DICE                      = 5171,
    SPELL_ROGUE_SMOKE_BOMB_AURA                     = 212183,
    SPELL_ROGUE_SMOKE_BOMB_VISUAL                   = 183859,
    SPELL_ROGUE_SPRINT                              = 2983,
    SPELL_ROGUE_STEALTH                             = 1784,
    SPELL_ROGUE_STEALTH_SHAPESHIFT_AURA             = 158188,
    SPELL_ROGUE_STEALTH_STEALTH_AURA                = 158185,
    SPELL_ROGUE_STRIKE_FROM_THE_SHADOWS             = 196951,
    SPELL_ROGUE_SUBTERFUGE                          = 108208,
    SPELL_ROGUE_SUBTERFUGE_AURA                     = 115192,
    SPELL_ROGUE_IRON_WIRE                           = 196861,
    SPELL_ROGUE_TOTAL_PARALYSIS                     = 113953,
    SPELL_ROGUE_TRICKS_OF_THE_TRADE_DMG_BOOST       = 57933,
    SPELL_ROGUE_TRICKS_OF_THE_TRADE_PROC            = 59628,
    SPELL_ROGUE_VANISH_AURA                         = 11327,
    SPELL_ROGUE_VENOMOUS_VIM_ENERGIZE               = 51637,
    SPELL_ROGUE_VENOMOUS_WOUNDS                     = 79134,
    SPELL_ROGUE_VENOMOUS_WOUND_DAMAGE               = 79136,
    SPELL_ROGUE_VENOM_RUSH                          = 152152,
    SPELL_ROGUE_WEAKENED_ARMOR                      = 113746,
    SPELL_ROGUE_WOUND_POISON                        = 8679,
	SPELL_ROGUE_STEALTH_BAR							= 158188,
    SPELL_ROGUE_BLINDSIDE                           = 111240,
	SPELL_ROGUE_BLINDSIDE_AURA                      = 121153,
    SPELL_ROGUE_TOXIC_BLADE                         = 245388,
    SPELL_ROGUE_SINISTER_STRIKE                     = 1752,
    SPELL_ROGUE_MUTILATE_MAINHAND                   = 5374,
    SPELL_ROGUE_MUTILATE_OFFHAND                    = 27576,
    SPELL_ROGUE_CRIMSON_TEMPEST                     = 121411,
    SPELL_ROGUE_MASTER_ASSASIN                      = 255989,
    SPELL_ROGUE_MASTER_ASSASIN_AURA                 = 256735,
	SPELL_ROGUE_WEAPONMASTER						= 200733,
	SPELL_ROGUE_LEECH_POISON_TALENT					= 280716,
	SPELL_ROGUE_LEECH_POISON						= 108211,
	SPELL_ROGUE_SHURIKEN_COMBO                      = 245640,
    SPELL_ROGUE_SHADOW_BLADE                        = 279043,
    SPELL_ROGUE_SECRET_TECHNIQUE                    = 280719,
    SPELL_ROGUE_GARROTE_RANK_2                      = 231719,
    SPELL_ROGUE_SHADOWSTRIKE_RANK_2                 = 231718,
    SPELL_ROGUE_SHADOWSTRIKE_BONUS                  = 245623,
    SPELL_ROGUE_WOUND_POISON_DOT                    = 8680,
    SPELL_ROGUE_INTERNAL_BLEEDING                   = 154904,
    SPELL_ROGUE_INTERNAL_BLEEDING_DOT               = 154953,
    SPELL_ROGUE_VENDETTA_ENERGIZE                   = 256495,
    SPELL_ROGUE_IRON_WIRE_DEBUFF                    = 256148,
    SPELL_ROGUE_PREY_ON_THE_WEAK                    = 131511,
	SPELL_ROGUE_PREY_ON_THE_WEAK_DEBUFF             = 255909,
    SPELL_ROGUE_DEADLY_BREW                         = 197044,
    SPELL_ROGUE_MINOR_WOUND_POISON                  = 197046,
	SPELL_ROGUE_INTENT_TO_KILL						= 197007,
	SPELL_ROGUE_VENDETTA							= 79140,
	SPELL_ROGUE_SHADOWSTEP							= 36554,
	SPELL_ROGUE_CREEPING_VENOM						= 198092,
	SPELL_ROGUE_CREEPING_VENOM_AURA					= 198097,
	SPELL_ROGUE_MIND_NUMBING_POISON					= 197050,
	SPELL_ROGUE_MIND_NUMBING_POISON_PROC			= 197051,
	SPELL_ROGUE_MIND_NUMBING_POISON_DAMAGE			= 197062,
	SPELL_ROGUE_VEIL_OF_THE_NIGHT					= 198952,
	SPELL_ROGUE_VEIL_OF_THE_NIGHT_BUFF				= 199027,
	SPELL_ROGUE_DAGGER_IN_THE_DARK_DEBUFF			= 198688,
	SPELL_ROGUE_COLD_BLOOD							= 213981,
	SPELL_ROGUE_COLD_BLOOD_DAMAGE					= 213983,
    SPELL_ROGUE_MANEUVERABILITY                     = 197000,
	SPELL_ROGUE_MANEUVERABILITY_BUFF                = 197003,
    SPELL_ROGUE_SHADOW_GRASP                        = 277950,
    SPELL_ROGUE_SHADOW_GRASP_SLOW                   = 206760,
    SPELL_ROGUE_NIGHT_TERRORS                       = 277953,
    SPELL_ROGUE_MASTER_OF_SHADOW_BUFF               = 196980,
    SPELL_ROGUE_CONTROL_IS_KING                     = 212217,
    SPELL_ROGUE_CONTROL_IS_KING_EFFECT              = 212219,
	SPELL_ROGUE_SHOT_IN_THE_DARK					= 257505,
	SPELL_ROGUE_SHOT_IN_THE_DARK_BUFF				= 257506,
	SPELL_ROGUE_CHEAP_SHOOT							= 1833,
    SPELL_ROGUE_SYSTEM_SHOCK                        = 198145,
    SPELL_ROGUE_SYSTEM_SHOCK_DAMAGE                 = 198222,
    SPELL_ROGUE_CHEAP_TRICK                         = 212035,
    SPELL_ROGUE_CHEAP_TRICK_MISS                    = 212150,
    SPELL_ROGUE_PARLEY                              = 199743,
    SPELL_ROGUE_HEMORRAGHE                          = 170116,
    SPELL_ROGUE_GHOSTLY_STRIKE                      = 196937,
    SPELL_ROGUE_BLADE_RUSH                          = 271877,
    SPELL_ROGUE_NIGHTS_VENGEANCE_BUFF               = 273424,
    SPELL_ROGUE_VENOM_RUSH_ENERGIZE                 = 256522,
    SPELL_ROGUE_BACKSTAB                            = 53,
    SPELL_ROGUE_GLOOMBLADE                          = 200758,
    SPELL_ROGUE_DEATH_FROM_ABOVE_BONUS              = 269512,
    SPELL_ROGUE_DEATH_FROM_ABOVE_FINAL_JUMP         = 156327,
    SPELL_ROGUE_DEATH_FROM_ABOVE_INITIAL_JUMP       = 178236,
    SPELL_ROGUE_SHADOWY_DUEL                        = 207736,
    SPELL_ROGUE_SHADOWY_DUEL_INVIS                  = 207756,
    SPELL_ROGUE_SHADOWY_DUEL_STALK                  = 210558,
    SPELL_ROGUE_SHROUDED_SUFFOCATION                = 278666,
    SPELL_ROGUE_SHROUDED_SUFFOCATION_ENERGIZE       = 279703,
    SPELL_ROGUE_HIDDEN_BLADES_BUFF                  = 270070,
    SPELL_ROGUE_ACE_UP_YOUR_SLEEVE                  = 278676,
    SPELL_ROGUE_SCENT_OF_BLOOD_AURA                 = 277679,
    SPELL_ROGUE_SCENT_OF_BLOOD_BUFF                 = 277731,
    SPELL_ROGUE_SHROUDED_MANTLE_POWER               = 280020,
    SPELL_ROGUE_SHROUDED_MANTLE_HOT                 = 280200,
    SPELL_ROGUE_SHROUDED_MANTLE_HEAL                = 280201,
    SPELL_ROGUE_WATER_WALKING                       = 61922,
    SPELL_ROGUE_BLACK_POWDER                        = 319175,

    /// Shadowlands
    SPELL_ROGUE_SEPSIS_AURA                         = 347037,
    SPELL_ROGUE_SHROUD_OF_CONCEALMENT               = 114018,
    SPELL_ROUGE_GRUDGE_MATCH                        = 363591,
    LeechingPoisonAura                              = 108211, ///< Leeching Poison talent Leech spell
    FadeToNothingConduit                            = 341532, ///< Conduit
    FadeToNothingConduitBuff                        = 341533, ///< Fade to Nothing conduit buff

};

enum RollTheBones
{
    SPELL_ROGUE_JOLLY_ROGER                         = 199603,
    SPELL_ROGUE_GRAND_MELEE                         = 193358,
    SPELL_ROGUE_SHARK_INFESTED_WATERS               = 193357,
    SPELL_ROGUE_TRUE_BEARING                        = 193359,
    SPELL_ROGUE_BURIED_TREASURE                     = 199600,
    SPELL_ROGUE_BROADSIDES                          = 193356,
    SPELL_ROGUE_MUTILATE                            = 1329,
};

enum RogueSpellIcons
{
    ICON_ROGUE_IMPROVED_RECUPERATE                  = 4819
};

enum CheatDeath
{
    SPELL_ROGUE_CHEAT_DEATH                         = 31230,
    SPELL_ROGUE_CHEAT_DEATH_ANIM                    = 31231,
    SPELL_ROGUE_CHEAT_DEATH_DMG_REDUC               = 45182,
    SPELL_ROGUE_CHEAT_DEATH_CD_AURA                 = 45181
};

enum TrueBearingIDs
{
    SPELL_ROGUE_BETWEEN_THE_EYES                    = 199804,
    SPELL_ROGUE_VANISH                              = 1856,
    SPELL_ROGUE_BLIND                               = 2094,
    SPELL_ROGUE_CLOAK_OF_SHADOWS                    = 31224,
    SPELL_ROGUE_RIPOSTE                             = 199754,
    SPELL_ROGUE_GRAPPLING_HOOK                      = 195457,
    SPELL_ROGUE_CANNONBALL_BARRAGE                  = 185767,
    SPELL_ROGUE_MARKED_FOR_DEATH                    = 137619,
    SPELL_ROGUE_DEATH_FROM_ABOVE                    = 152150
};

uint32 RogueComboPoints(WorldObject* Caster)
{
    return Caster->Variables.GetValue("RogueComboPoints", 0);
}

void Rogue::HandleGrudgeMatch(Unit* caster, Unit* target, uint32 auraId)
{
    if (target->HasAura(SPELL_ROGUE_VENDETTA, caster->GetGUID()))
    {
        if (caster->HasAura(SPELL_ROUGE_GRUDGE_MATCH))
        {
            if (auto dot = target->GetAura(auraId, caster->GetGUID()))
            {
                dot->SetMaxDuration(dot->GetDuration() / 2);
                dot->RefreshDuration();
                for (auto eff : dot->GetAuraEffects())
                {
                    if (eff && eff->GetAuraType() == AuraType::SPELL_AURA_PERIODIC_DAMAGE)
                    {
                        eff->IsDoublProcced = true;
                        eff->CalculatePeriodic(caster, false, false);
                    }
                }
            }
        }
    }
}

void Rogue::HandleGrudgeMatch(Unit* caster, Unit* target, Aura* dot)
{
    if (target->HasAura(SPELL_ROGUE_VENDETTA, caster->GetGUID()))
    {
        if (caster->HasAura(SPELL_ROUGE_GRUDGE_MATCH))
        {
            dot->SetMaxDuration(dot->GetDuration() / 2);
            dot->RefreshDuration();
            for (auto eff : dot->GetAuraEffects())
            {
                if (eff && eff->GetAuraType() == AuraType::SPELL_AURA_PERIODIC_DAMAGE)
                {
                    eff->IsDoublProcced = true;
                    eff->CalculatePeriodic(caster, false, false);
                }
            }
        }
    }
}

/// <summary>
/// Handles conduit or trait for Fade to Nothing
/// </summary>
/// <param name="caster"></param>
void HandleFadeToNothingConduit(Unit* caster)
{
    if (auto fadeToNothingAura = caster->GetAuraEffect(FadeToNothingConduit, EFFECT_0))
        caster->CastSpell(caster, FadeToNothingConduitBuff, CastSpellExtraArgs(true).AddSpellBP0(fadeToNothingAura->GetAmount()));

    if (auto fadeToNothingAura = caster->GetAuraEffect(Rogue::eSubtletyTraits::FadeToNothing, EFFECT_0))
        caster->CastSpell(caster, Rogue::eSubtletyTraits::FadeToNothingProc, true);
}

class rogue_playerscript : public PlayerScript
{
public:
    rogue_playerscript() : PlayerScript("rogue_playerscript") {}

    void OnModifyPower(Player* player, Powers power, int32 oldValue, int32& newValue, bool regen, bool after) override
    {
        if (!player || regen || after)
            return;

        if (player->GetClass() != CLASS_ROGUE)
            return;

        if (player->GetSpecializationId() != TALENT_SPEC_ROGUE_ASSASSINATION && player->GetSpecializationId() != TALENT_SPEC_ROGUE_COMBAT && player->GetSpecializationId() != TALENT_SPEC_ROGUE_SUBTLETY)
            return;

        // check echoing reprimand here?
        if (power == POWER_COMBO_POINTS && oldValue > newValue)
            player->Variables.Set("RogueComboPoints", oldValue);
    }

    void CheckOnSpellHitOnUnit(Unit* target, WorldObject const* /*caster*/, SpellMissInfo& spellMissInfo, SpellInfo const* spellInfo) override
    {
        if (target && spellInfo)
            if(Player* player = target->ToPlayer())
                if (player->GetClass() == CLASS_ROGUE)
                    if (player->HasAura(SPELL_ROGUE_CLOAK_OF_SHADOWS))
                        if (!spellInfo->IsPositive() && spellInfo->GetSchoolMask() & SPELL_SCHOOL_MASK_MAGIC && !spellInfo->HasAttribute(SPELL_ATTR8_NO_ATTACK_BLOCK))
                            spellMissInfo = SPELL_MISS_MISS;
    }
};

// Cannonball Barrage - 185767
class spell_rog_cannonball_barrage : public SpellScriptLoader
{
public:
    spell_rog_cannonball_barrage() : SpellScriptLoader("spell_rog_cannonball_barrage") {}

    class spell_rog_cannonball_barrage_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_rog_cannonball_barrage_AuraScript);

        bool Validate(SpellInfo const*) override
        {
            return ValidateSpellInfo(
            {
                SPELL_ROGUE_CANNONBALL_BARRAGE,
                SPELL_ROGUE_CANNONBALL_BARRAGE_DAMAGE,
                SPELL_ROGUE_CANNONBALL_BARRAGE_SLOW
            });
        }

        void HandlePeriodic(AuraEffect const* aurEff)
        {
            Unit* caster = aurEff->GetCaster();
            if (!caster)
                return;

            DynamicObject* barrage = caster->GetDynObject(SPELL_ROGUE_CANNONBALL_BARRAGE);
            if (!barrage)
                return;

            caster->CastSpell(barrage->GetPosition(), SPELL_ROGUE_CANNONBALL_BARRAGE_DAMAGE, true);
        }

        void Register() override
        {
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_rog_cannonball_barrage_AuraScript::HandlePeriodic, EFFECT_1, SPELL_AURA_PERIODIC_DUMMY);
        }
    };

    class spell_rog_cannonball_barrage_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_rog_cannonball_barrage_SpellScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            return ValidateSpellInfo(
            {
                SPELL_ROGUE_CANNONBALL_BARRAGE,
                SPELL_ROGUE_CANNONBALL_BARRAGE_DAMAGE,
                SPELL_ROGUE_CANNONBALL_BARRAGE_SLOW
            });
        }

        void HandleHit(SpellEffIndex /*effIndex*/)
        {
            Unit* caster = GetCaster();
            Unit* target = GetHitUnit();
            if (!target || !caster)
                return;

            caster->CastSpell(target, SPELL_ROGUE_CANNONBALL_BARRAGE_SLOW, true);
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_rog_cannonball_barrage_SpellScript::HandleHit, EFFECT_2, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_rog_cannonball_barrage_SpellScript();
    }

    AuraScript* GetAuraScript() const override
    {
        return new spell_rog_cannonball_barrage_AuraScript();
    }
};

// 199804 - Between the Eyes Update 8.0.1 Build 28153
class spell_rog_between_the_eyes :public SpellScript
{
	PrepareSpellScript(spell_rog_between_the_eyes);

	//void HandleTakePower(SpellPowerCost& powerCost)
	//{
	//	if (powerCost.Power == POWER_COMBO_POINTS)
    //        _cp = powerCost.Amount;
	//}

    void HandleBeforeHit(SpellMissInfo /*missInfo*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        uint32 _cp = GetSpell()->GetUsedComboPoints();
        
        int32 duration = _cp * IN_MILLISECONDS;

        // TODO: remove this, this was changed in SL BetweenTheEyes isn't a stun!
        DiminishingGroup const diminishGroup = GetSpellInfo()->GetDiminishingReturnsGroupForSpell();
        target->ApplyDiminishingToDuration(GetSpellInfo(), duration, caster, target->GetDiminishing(diminishGroup));
        duration = caster->ModSpellDuration(GetSpellInfo(), target, duration, false, 1 << EFFECT_1);
        caster->Variables.Set<int32>("Duration_Between_The_Eyes", duration);
    }

	void HandleHit(SpellEffIndex effIndex)
	{
        if (Unit* caster = GetCaster())
        {
            uint32 _cp = GetSpell()->GetUsedComboPoints();
            int32 damage = GetHitDamage() * _cp;
            if (AuraEffect* aura = caster->GetAuraEffect(SPELL_ROGUE_ACE_UP_YOUR_SLEEVE, EFFECT_0))
                damage += aura->GetAmount() * _cp;

            SetHitDamage(damage);

            if (auto aurEff = caster->GetAuraEffect(AceUpYourSleeve, EFFECT_0))
                if (roll_chance_i(_cp * aurEff->GetAmount()))
                    caster->CastSpell(caster, AceUpYourSleeveEnergize, true);
        }		
	}

	void HandleAfterHit()
	{
		Unit* caster = GetCaster();
		Unit* target = GetHitUnit();

		if (!caster || !target)
			return;

        // Prey on the Weak
		if (caster->HasAura(SPELL_ROGUE_PREY_ON_THE_WEAK))
			caster->CastSpell(target, SPELL_ROGUE_PREY_ON_THE_WEAK_DEBUFF, true);
	}

	void Register() override
	{
		//OnTakePower += SpellOnTakePowerFn(spell_rog_between_the_eyes::HandleTakePower);
        BeforeHit += BeforeSpellHitFn(spell_rog_between_the_eyes::HandleBeforeHit);
		OnEffectHitTarget += SpellEffectFn(spell_rog_between_the_eyes::HandleHit, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
		AfterHit += SpellHitFn(spell_rog_between_the_eyes::HandleAfterHit);
	}

private:
	//uint8 _cp = 0;
};

// 199804 - Between the Eyes Update 8.0.1 Build 28153
class aura_rog_between_the_eyes : public AuraScript
{
    PrepareAuraScript(aura_rog_between_the_eyes);

    void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* caster = GetCaster())
        {
            if (Unit* target = GetTarget())
            {
                int32 duration = caster->Variables.GetValue<int32>("Duration_Between_The_Eyes");
                SetDuration(duration);
                SetMaxDuration(duration);
            }
        }
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(aura_rog_between_the_eyes::OnApply, EFFECT_1, SPELL_AURA_MOD_STUN, AURA_EFFECT_HANDLE_REAL);
    }
};

enum eBladeFlurry
{
    BladFlurryStart = 331850,
};

/// Blade Flurry - 13877
class spell_rog_blade_flurry : public AuraScript
{
    PrepareAuraScript(spell_rog_blade_flurry);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetSpellInfo())
        {
            switch (eventInfo.GetSpellInfo()->Id)
            {
                case BladFlurryStart:
                case SPELL_ROGUE_BLADE_FLURRY_EXTRA_ATTACK:
                    return false;
                default:
                    break;
            }
        }

        if (!eventInfo.GetDamageInfo())
            return false;

        if (eventInfo.GetDamageInfo()->GetDamageType() == DOT)
            return false;

        return true;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();
        Unit* caster = GetCaster();
        Unit* target = eventInfo.GetActionTarget();
        if (!caster || !target)
            return;

        if (!eventInfo.GetDamageInfo())
            return;

        int32 damage = CalculatePct(eventInfo.GetDamageInfo()->GetDamage(), sSpellMgr->GetSpellInfo(SPELL_ROGUE_BLADE_FLURRY_EXTRA_ATTACK)->GetEffect(EFFECT_0).BonusCoefficient);

        if (auto preciseCuts = caster->GetAuraEffect(PreciseCuts, EFFECT_0))
        {
            std::list<Unit*> attackableUnits;
            caster->GetAttackableUnitListInRange(attackableUnits, MELEE_RANGE);
            if (auto spellInfo = sSpellMgr->GetSpellInfo(SPELL_ROGUE_BLADE_FLURRY_EXTRA_ATTACK))
            {
                int32 maxTargets = spellInfo->GetEffect(EFFECT_0).ChainTargets;
                if (Player* modOwner = caster->GetSpellModOwner())
                    modOwner->ApplySpellMod(spellInfo, SpellModOp::ChainTargets, maxTargets);

                if (attackableUnits.size() < maxTargets)
                {
                    uint32 diff = maxTargets - attackableUnits.size();

                    AddPct(damage, diff * preciseCuts->GetAmount());
                }
            }
        }

        CastSpellExtraArgs args(TRIGGERED_FULL_MASK);
        args.AddSpellBP0(damage);
        caster->CastSpell(target, SPELL_ROGUE_BLADE_FLURRY_EXTRA_ATTACK, args);
    }

    void HandleApply3(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Unit* caster = GetCaster();
        if (!caster || !caster->HasAura(Rogue::eOutlawTraits::LongArmOfTheOutlaw))
        {
            PreventDefaultAction();
            return;
        }
    }

    void Register()
    {
        DoCheckProc += AuraCheckProcFn(spell_rog_blade_flurry::CheckProc);
        OnProc += AuraProcFn(spell_rog_blade_flurry::HandleProc);
        OnEffectApply += AuraEffectApplyFn(spell_rog_blade_flurry::HandleApply3, EFFECT_3, SPELL_AURA_LINKED_2, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
    }
};

/// <summary>
///  13877
/// </summary>
class spell_rog_blade_flurry_dummy : public SpellScript
{
    PrepareSpellScript(spell_rog_blade_flurry_dummy);

    void HandleAfterCast()
    {
        Unit* caster = GetCaster();
        if (!caster)
            return;

        caster->CastSpell(caster, BladFlurryStart, true);
    }

    void Register() override
    {
        AfterCast += SpellCastFn(spell_rog_blade_flurry_dummy::HandleAfterCast);
    }
};

// 31230 - Cheat Death
class spell_rog_cheat_death : public SpellScriptLoader
{
    public:
        spell_rog_cheat_death() : SpellScriptLoader("spell_rog_cheat_death") { }

        class spell_rog_cheat_death_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_rog_cheat_death_AuraScript);

            bool Validate(SpellInfo const* /*spellInfo*/) override
            {
                return ValidateSpellInfo(
                {
                    SPELL_ROGUE_CHEAT_DEATH_COOLDOWN
                });
            }

            bool Load() override
            {
                return GetUnitOwner()->GetTypeId() == TYPEID_PLAYER;
            }

            void CalculateAmount(AuraEffect const* /*aurEff*/, int32& amount, bool & /*canBeRecalculated*/)
            {
                // Set absorbtion amount to unlimited
                amount = -1;
            }

            void Absorb(AuraEffect* /*aurEff*/, DamageInfo & dmgInfo, uint32 & absorbAmount)
            {
                Player* target = GetTarget()->ToPlayer();
                if (target->HasAura(SPELL_ROGUE_CHEAT_DEATH_DMG_REDUC))
                {
                    absorbAmount = CalculatePct(dmgInfo.GetDamage(), 85);
                    return;
                }
                else
                {
                    if (dmgInfo.GetDamage() < target->GetHealth() || target->HasAura(SPELL_ROGUE_CHEAT_DEATH_COOLDOWN))
                        return;

                    uint64 health7 = target->CountPctFromMaxHealth(7);
                    target->SetHealth(1);
                    HealInfo healInfo(target, target, health7, GetSpellInfo(), GetSpellInfo()->GetSchoolMask());
                    target->HealBySpell(healInfo);
                    target->CastSpell(target, SPELL_ROGUE_CHEAT_DEATH_ANIM, true);
                    target->CastSpell(target, SPELL_ROGUE_CHEAT_DEATH_DMG_REDUC, true);
                    target->CastSpell(target, SPELL_ROGUE_CHEAT_DEATH_COOLDOWN, true);
                    absorbAmount = dmgInfo.GetDamage();
                }
            }

            void Register() override
            {
                DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_rog_cheat_death_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
                OnEffectAbsorb += AuraEffectAbsorbFn(spell_rog_cheat_death_AuraScript::Absorb, EFFECT_0);
            }
        };

        AuraScript* GetAuraScript() const override
        {
            return new spell_rog_cheat_death_AuraScript();
        }
};

// 2818 - Deadly Poison
class aura_rog_deadly_poison_debuff : public AuraScript
{
	PrepareAuraScript(aura_rog_deadly_poison_debuff);

	void HandleApply(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /* mode */)
	{
		Unit* caster = GetCaster();
		Unit* target = GetUnitOwner();
		if (!caster || !target)
			return;

		caster->CastSpell(target, SPELL_ROGUE_DEADLY_POISON_INSTANT_DAMAGE, true);
	}

	void HandleAfterApply(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /* mode */)
	{
		Unit* caster = GetCaster();
		Unit* target = GetUnitOwner();
		if (!caster || !target)
			return;

		if (caster->HasAura(SPELL_ROGUE_DEADLY_BREW))
			caster->CastSpell(target, SPELL_ROGUE_MINOR_WOUND_POISON, true);

		// Mind Numbing Poison
		if (caster->HasAura(SPELL_ROGUE_MIND_NUMBING_POISON))
			caster->CastSpell(target, SPELL_ROGUE_MIND_NUMBING_POISON_PROC, true);
	}

	void Register() override
	{
		OnEffectApply += AuraEffectApplyFn(aura_rog_deadly_poison_debuff::HandleApply, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE, AURA_EFFECT_HANDLE_REAPPLY);
		AfterEffectApply += AuraEffectApplyFn(aura_rog_deadly_poison_debuff::HandleAfterApply, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
	}
};

// 51690 - Killing Spree
#define KillingSpreeScriptName "spell_rog_killing_spree"
class spell_rog_killing_spree : public SpellScriptLoader
{
    public:
        spell_rog_killing_spree() : SpellScriptLoader(KillingSpreeScriptName) { }

        class spell_rog_killing_spree_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_rog_killing_spree_SpellScript);

            void FilterTargets(std::list<WorldObject*>& targets)
            {
                if (targets.empty() || GetCaster()->GetVehicleBase())
                    FinishCast(SPELL_FAILED_OUT_OF_RANGE);
            }

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                if (Aura* aura = GetCaster()->GetAura(SPELL_ROGUE_KILLING_SPREE))
                {
                    if (spell_rog_killing_spree_AuraScript* script = dynamic_cast<spell_rog_killing_spree_AuraScript*>(aura->GetScriptByName(KillingSpreeScriptName)))
                        script->AddTarget(GetHitUnit());
                }
            }

            void Register() override
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_rog_killing_spree_SpellScript::FilterTargets, EFFECT_2, TARGET_UNIT_DEST_AREA_ENEMY);
                OnEffectHitTarget += SpellEffectFn(spell_rog_killing_spree_SpellScript::HandleDummy, EFFECT_1, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_rog_killing_spree_SpellScript();
        }

        class spell_rog_killing_spree_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_rog_killing_spree_AuraScript);

            bool Validate(SpellInfo const* /*spellInfo*/) override
            {
                return ValidateSpellInfo(
                {
                    SPELL_ROGUE_KILLING_SPREE_TELEPORT,
                    SPELL_ROGUE_KILLING_SPREE_WEAPON_DMG,
                    SPELL_ROGUE_KILLING_SPREE_DMG_BUFF
                });
            }

            void HandleApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                GetTarget()->CastSpell(GetTarget(), SPELL_ROGUE_KILLING_SPREE_DMG_BUFF, true);
            }

            void HandleEffectPeriodic(AuraEffect const* /*aurEff*/)
            {
                while (!_targets.empty())
                {
                    ObjectGuid guid = Trinity::Containers::SelectRandomContainerElement(_targets);
                    if (Unit* target = ObjectAccessor::GetUnit(*GetTarget(), guid))
                    {
                        GetTarget()->CastSpell(target, SPELL_ROGUE_KILLING_SPREE_TELEPORT, true);
                        GetTarget()->CastSpell(target, SPELL_ROGUE_KILLING_SPREE_WEAPON_DMG, true);
                        break;
                    }
                    else
                        _targets.remove(guid);
                }
            }

            void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                GetTarget()->RemoveAurasDueToSpell(SPELL_ROGUE_KILLING_SPREE_DMG_BUFF);
            }

            void Register() override
            {
                AfterEffectApply += AuraEffectApplyFn(spell_rog_killing_spree_AuraScript::HandleApply, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY, AURA_EFFECT_HANDLE_REAL);
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_rog_killing_spree_AuraScript::HandleEffectPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
                AfterEffectRemove += AuraEffectRemoveFn(spell_rog_killing_spree_AuraScript::HandleRemove, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY, AURA_EFFECT_HANDLE_REAL);
            }

        public:
            void AddTarget(Unit* target)
            {
                _targets.push_back(target->GetGUID());
            }

        private:
            GuidList _targets;
        };

        AuraScript* GetAuraScript() const override
        {
            return new spell_rog_killing_spree_AuraScript();
        }
};

// 1943 - Rupture
//Last Update 8.0.1 Build 28153
class spell_rog_rupture : public SpellScript
{
    PrepareSpellScript(spell_rog_rupture);

    void HandleTakePower(SpellPowerCost& powerCost)
    {
        if (powerCost.Power == POWER_COMBO_POINTS)
        {
            if (Unit* caster = GetCaster())
                caster->Variables.Set<uint8>("CP", powerCost.Amount);
        }
    }

    void HandleBeforeHit(SpellMissInfo missInfo)
    {
        if (missInfo == SPELL_MISS_NONE)
            if (Unit* caster = GetCaster())
                if (Unit* target = GetHitUnit())
                    if (!target->HasAura(GetSpellInfo()->Id, caster->GetGUID()))
                        if (AuraEffect* auraEff = caster->GetAuraEffect(SPELL_ROGUE_SCENT_OF_BLOOD_AURA, EFFECT_0))
                        {
                            CastSpellExtraArgs args(TRIGGERED_FULL_MASK);
                            args.AddSpellBP0(auraEff->GetAmount());
                            caster->CastSpell(caster, SPELL_ROGUE_SCENT_OF_BLOOD_BUFF, args);
                        }
    }

    void HandleAfterHit()
    {
        if (Unit* caster = GetCaster())
        {
            if (Unit* target = GetHitUnit())
            {
                if (Aura* ruptureAura = target->GetAura(GetSpellInfo()->Id))
                {
                    if (AuraEffect* effect = ruptureAura->GetEffect(EFFECT_0))
                    {
                        if (SpellPowerCost const* powerCost = GetSpell()->GetPowerCost(POWER_COMBO_POINTS))
                        {
                            uint32 cp = powerCost->Amount;

                            caster->Variables.Set<uint8>("CP", cp);
                            //int32 duration = 4 + (4 * cp);
                            //ruptureAura->SetDuration(duration * IN_MILLISECONDS);
                            //ruptureAura->SetMaxDuration(duration * IN_MILLISECONDS);
                            Rogue::HandleGrudgeMatch(GetCaster(), target, ruptureAura);

                            if (auto finality = caster->GetAura(FinalityRuptureLegendary))
                                finality->Remove();
                            if (auto finality = caster->GetAura(FinalityRupture))
                                finality->Remove();

                            if (!caster->HasAura(FinalityRupture))
                                caster->CastSpell(caster, FinalityRupture, true);
                        }
                    }
                }
            }
        }        
    }

    void Register() override
    {
        OnTakePower += SpellOnTakePowerFn(spell_rog_rupture::HandleTakePower);
        BeforeHit += BeforeSpellHitFn(spell_rog_rupture::HandleBeforeHit);
        AfterHit += SpellHitFn(spell_rog_rupture::HandleAfterHit);
    }
};

// 1943 - Rupture Aura
//Last Update 8.0.1 Build 28153
class aura_rog_rupture : public AuraScript
{
	PrepareAuraScript(aura_rog_rupture);

	void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
	{
        Unit* caster = GetCaster();
        if (!caster)
            return;

        if (Aura* bloodAura = caster->GetAura(SPELL_ROGUE_SCENT_OF_BLOOD_BUFF))
            bloodAura->DropStack();

        if (GetTargetApplication()->GetRemoveMode() != AURA_REMOVE_BY_DEATH)
            return;

        //https://www.askmrrobot.com/wow/theory/mechanic/spell/venomouswounds?spec=RogueAssassination&version=27101
        auto info = sSpellMgr->GetSpellInfo(SPELL_ROGUE_VENOMOUS_WOUNDS);
        int32 energyGain = info->GetEffect(EFFECT_1).BasePoints;
        uint32 energyRegen = energyGain * std::floor(GetDuration() / GetSpellInfo()->GetEffect(EFFECT_0).ApplyAuraPeriod);

        caster->EnergizeBySpell(caster, info, energyRegen, POWER_ENERGY);
	}

	void Register() override
	{
		OnEffectRemove += AuraEffectRemoveFn(aura_rog_rupture::HandleRemove, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE, AURA_EFFECT_HANDLE_REAL);
	}
};

// 1784 - Stealth
class spell_rog_stealth : public SpellScriptLoader
{
    public:
        spell_rog_stealth() : SpellScriptLoader("spell_rog_stealth") { }

        class spell_rog_stealth_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_rog_stealth_AuraScript);

            bool Validate(SpellInfo const* /*spellInfo*/) override
            {
                return ValidateSpellInfo(
                {
                    SPELL_ROGUE_MASTER_OF_SUBTLETY_PASSIVE,
                    SPELL_ROGUE_MASTER_OF_SUBTLETY_DAMAGE_PERCENT,
                    SPELL_ROGUE_SANCTUARY,
                    SPELL_ROGUE_SHADOW_FOCUS,
                    SPELL_ROGUE_STEALTH_STEALTH_AURA,
                    SPELL_ROGUE_STEALTH_SHAPESHIFT_AURA,
                    SPELL_ROGUE_MASTER_ASSASIN,
					SPELL_ROGUE_MASTER_ASSASIN_AURA,
                });
            }

            bool CheckProc(ProcEventInfo& eventInfo)
            {
                if (eventInfo.GetDamageInfo() && (eventInfo.GetDamageInfo()->GetDamageType() != HEAL && eventInfo.GetDamageInfo()->GetDamageType() != NODAMAGE) && 
                    eventInfo.GetDamageInfo()->GetDamage() > 0 && eventInfo.GetDamageInfo()->GetDamage() > eventInfo.GetDamageInfo()->GetAbsorb())
                    return true;

                return false;
            }

            enum Stealth
            {
                CloakedInShadowsAuraConduit = 341529,
                CloakedInShadowsBuffConduit = 341530,
                MarkOfTheMasterAssassin = 340076,
                MasterAssassinsMark = 340094,
            };

            void HandleEffectApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Unit* target = GetTarget())
                {
                    // Master of Subtlety
                    if (target->HasAura(SPELL_ROGUE_MASTER_OF_SUBTLETY_PASSIVE))
                        target->CastSpell(target, SPELL_ROGUE_MASTER_OF_SUBTLETY_DAMAGE_PERCENT, TRIGGERED_FULL_MASK);

                    // Shadow Focus
                    if (target->HasAura(SPELL_ROGUE_SHADOW_FOCUS))
                        target->CastSpell(target, SPELL_ROGUE_SHADOW_FOCUS_COST_PCT, TRIGGERED_FULL_MASK);

                    // Master Assasin
                    if (target->HasAura(SPELL_ROGUE_MASTER_ASSASIN))
                        target->CastSpell(target, SPELL_ROGUE_MASTER_ASSASIN_AURA, true);

                    if (target->HasAura(MarkOfTheMasterAssassin))
                        target->CastSpell(target, MasterAssassinsMark, true);

                    if (target->HasAura(TakeEmbySuprise))
                        target->CastSpell(target, TakeEmbySupriseBuff, true);

                    if (target->HasAura(Rogue::eSubtletyTraits::Premeditation))
                        target->CastSpell(target, Rogue::eSubtletyTraits::PremeditationProcAura, true);

                    if (target->HasAura(Rogue::eSubtletyTraits::SilentStorm))
                        target->CastSpell(target, Rogue::eSubtletyTraits::SilentStormProcAura, true);

                    // Shadowstrike Rank 2
                    //if (target->HasAura(SPELL_ROGUE_SHADOWSTRIKE_RANK_2))
                        target->CastSpell(target, SPELL_ROGUE_SHADOWSTRIKE_BONUS, true);

                    target->RemoveAurasDueToSpell(SPELL_ROGUE_VANISH);
                    //target->RemoveAurasDueToSpell(SPELL_ROGUE_VANISH_AURA); - crashes server :)
                    target->RemoveAurasDueToSpell(SPELL_ROGUE_STEALTH_STEALTH_AURA);
                    target->RemoveAurasDueToSpell(SPELL_ROGUE_STEALTH_SHAPESHIFT_AURA);
                    target->RemoveAurasDueToSpell(SPELL_ROGUE_SUBTERFUGE_AURA);
                    target->CastSpell(target, SPELL_ROGUE_SANCTUARY, TRIGGERED_FULL_MASK);
                    target->CastSpell(target, SPELL_ROGUE_STEALTH_STEALTH_AURA, TRIGGERED_FULL_MASK);
                    target->CastSpell(target, SPELL_ROGUE_STEALTH_SHAPESHIFT_AURA, TRIGGERED_FULL_MASK);

                    if (target->HasAura(SPELL_ROGUE_MASTER_OF_SHADOWS))
                        target->CastSpell(target, SPELL_ROGUE_MASTER_OF_SHADOW_BUFF, true);

                    if (target->HasAura(SPELL_ROGUE_SHOT_IN_THE_DARK))
                        target->CastSpell(target, SPELL_ROGUE_SHOT_IN_THE_DARK_BUFF, true);

                    if (auto aurEff = target->GetAuraEffect(CloakedInShadowsAuraConduit, EFFECT_0))
                    {
                        auto health = CalculatePct(target->GetMaxHealth(), aurEff->GetAmount());
                        target->CastSpell(target, CloakedInShadowsBuffConduit, CastSpellExtraArgs(true).AddSpellBP0(health));
                    }

                    if (auto aurEff = target->GetAuraEffect(CloakedInShadows, EFFECT_0))
                    {
                        auto health = CalculatePct(target->GetMaxHealth(), aurEff->GetAmount());
                        target->CastSpell(target, CloakedInShadowsBuff, CastSpellExtraArgs(true).AddSpellBP0(health));
                    }

                    HandleFadeToNothingConduit(target);
                }
            }
        

            void HandleEffectRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Unit* target = GetTarget())
                {
                    // Master of Subtlety
                    if (AuraEffect* masterOfSubtletyPassive = GetTarget()->GetAuraEffect(SPELL_ROGUE_MASTER_OF_SUBTLETY_PASSIVE, EFFECT_0))
                    {
                        if (Aura* masterOfSubtletyAura = GetTarget()->GetAura(SPELL_ROGUE_MASTER_OF_SUBTLETY_DAMAGE_PERCENT))
                        {
                            masterOfSubtletyAura->SetMaxDuration(masterOfSubtletyPassive->GetAmount());
                            masterOfSubtletyAura->RefreshDuration();
                        }
                    }

                    // Master Assasin
                    if (Aura* aura = target->GetAura(SPELL_ROGUE_MASTER_ASSASIN_AURA))
                    {
                        aura->SetMaxDuration(3000);
                        aura->RefreshDuration();
                    }

                    if (Aura* aura = target->GetAura(MasterAssassinsMark))
                    {
                        aura->SetMaxDuration(4000);
                        aura->RefreshDuration();
                    }

                    if (Aura* aura = target->GetAura(TakeEmbySupriseBuff))
                    {
                        aura->SetMaxDuration(10000);
                        aura->RefreshDuration();
                    }

                    target->RemoveAurasDueToSpell(SPELL_ROGUE_SHADOW_FOCUS_COST_PCT);
                    target->RemoveAurasDueToSpell(SPELL_ROGUE_STEALTH_STEALTH_AURA);
                    target->RemoveAurasDueToSpell(SPELL_ROGUE_STEALTH_SHAPESHIFT_AURA);
                    target->RemoveAurasDueToSpell(SPELL_ROGUE_SHROUD_OF_CONCEALMENT);
                    target->RemoveAurasDueToSpell(Rogue::eSubtletyTraits::PremeditationProcAura);


                    if (target->HasAura(SPELL_ROGUE_SUBTERFUGE))
                        target->CastSpell(target, SPELL_ROGUE_SUBTERFUGE_AURA, true);
                    if (Aura* aur = target->GetAura(SPELL_ROGUE_MASTER_OF_SUBTLETY_DAMAGE_PERCENT))
                    {
                        aur->SetMaxDuration(6 * IN_MILLISECONDS);
                        aur->SetDuration(6 * IN_MILLISECONDS);
                    }

                    // Veil of the Night
                    if (target->HasAura(SPELL_ROGUE_VEIL_OF_THE_NIGHT))
                        target->CastSpell(target, SPELL_ROGUE_VEIL_OF_THE_NIGHT_BUFF, true);
                }
            }

            void Register() override
            {
                DoCheckProc += AuraCheckProcFn(spell_rog_stealth_AuraScript::CheckProc);
                AfterEffectApply += AuraEffectApplyFn(spell_rog_stealth_AuraScript::HandleEffectApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
                AfterEffectRemove += AuraEffectRemoveFn(spell_rog_stealth_AuraScript::HandleEffectRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const override
        {
            return new spell_rog_stealth_AuraScript();
        }
};

// 115192 - Subterfuge Aura
class spell_rog_subterfuge : public SpellScriptLoader
{
public:
    spell_rog_subterfuge() : SpellScriptLoader("spell_rog_subterfuge") {}

    class spell_rog_subterfuge_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_rog_subterfuge_AuraScript);

        void HandleApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            Unit* caster = GetCaster();
            if (!caster)
                return;
            caster->CastSpell(caster, SPELL_ROGUE_STEALTH_SHAPESHIFT_AURA, true);
        }

        void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if (Unit* caster = GetCaster())
                if (!caster->HasAura(SPELL_ROGUE_SHADOW_DANCE_AURA))
                    caster->RemoveAurasDueToSpell(SPELL_ROGUE_STEALTH_SHAPESHIFT_AURA);
        }

        void Register() override
        {
            OnEffectApply += AuraEffectApplyFn(spell_rog_subterfuge_AuraScript::HandleApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            OnEffectRemove += AuraEffectRemoveFn(spell_rog_subterfuge_AuraScript::HandleRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_rog_subterfuge_AuraScript();
    }
};

// 1856 - Vanish
class spell_rog_vanish : public SpellScriptLoader
{
    public:
        spell_rog_vanish() : SpellScriptLoader("spell_rog_vanish") { }

        class spell_rog_vanish_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_rog_vanish_SpellScript);

            bool Validate(SpellInfo const* /*spellInfo*/) override
            {
                return ValidateSpellInfo(
                {
                    SPELL_ROGUE_VANISH_AURA,
                    SPELL_ROGUE_STEALTH_SHAPESHIFT_AURA
                });
            }

            void OnLaunch()
            {
                Unit* caster = GetCaster();
                if (!caster)
                    return;

                caster->RemoveMovementImpairingAuras(true);
                caster->RemoveAurasByType(SPELL_AURA_MOD_STALKED, [](AuraApplication const* aurApp) -> bool
                {
                    return (aurApp->GetBase()->GetId() != SPELL_ROGUE_SHADOWY_DUEL_STALK && aurApp->GetBase()->GetId() != SPELL_ROGUE_VENDETTA);
                });

                caster->CastSpell(caster, SPELL_ROGUE_VANISH_AURA, true);
                caster->CastSpell(caster, SPELL_ROGUE_STEALTH_SHAPESHIFT_AURA, true);
            }

            void Register() override
            {
                OnHit += SpellHitFn(spell_rog_vanish_SpellScript::OnLaunch);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_rog_vanish_SpellScript();
        }
};

// 11327 - Vanish
class spell_rog_vanish_aura : public SpellScriptLoader
{
    public:
        spell_rog_vanish_aura() : SpellScriptLoader("spell_rog_vanish_aura") { }

        class spell_rog_vanish_aura_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_rog_vanish_aura_AuraScript);

            bool Validate(SpellInfo const* /*spellInfo*/) override
            {
                return ValidateSpellInfo(
                {
                    SPELL_ROGUE_STEALTH
                });
            }

            enum Vanish
            {
                MarkOfTheMasterAssassin = 340076,
                MasterAssassinsMark = 340094,
            };

            enum eSpells
            {
                WodPvpCombat4pBonus                 = 182303,
                WodPvpCombat4pBonusTrigger          = 182304,
                WodPvpAssassination4pBonus          = 170883,
                WodPvpAssassination4pBonusTrigger   = 170882,
                Stealth                             = 1784,
                StealthShapeshift                   = 158188,
                Subterfuge                          = 108208,
                StealthSubterfuge                   = 115191,
                StealthSubterfugeEffect             = 115192,
                MasterAssassinsInitiative           = 235022,
                MasterAssassinsCritical             = 235027
            };

            void HandleEffectApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*modes*/)
            {
                Unit* target = GetTarget();
                if (!target)
                    return;
                // Master of Subtlety
                if (target->HasAura(SPELL_ROGUE_MASTER_OF_SUBTLETY_PASSIVE))
                    target->CastSpell(target, SPELL_ROGUE_MASTER_OF_SUBTLETY_DAMAGE_PERCENT, TRIGGERED_FULL_MASK);

                // Shadow Focus
                if (target->HasAura(SPELL_ROGUE_SHADOW_FOCUS))
                    target->CastSpell(target, SPELL_ROGUE_SHADOW_FOCUS_COST_PCT, TRIGGERED_FULL_MASK);

                if (target->HasAura(Rogue::eSubtletyTraits::Premeditation))
                    target->CastSpell(target, Rogue::eSubtletyTraits::PremeditationProcAura, true);

                if (target->HasAura(Rogue::eSubtletyTraits::SilentStorm))
                    target->CastSpell(target, Rogue::eSubtletyTraits::SilentStormProcAura, true);

                // Master Assasin
                if (target->HasAura(SPELL_ROGUE_MASTER_ASSASIN))
                    target->CastSpell(target, SPELL_ROGUE_MASTER_ASSASIN_AURA, true);

                if (target->HasAura(MarkOfTheMasterAssassin))
                    target->CastSpell(target, MasterAssassinsMark, true);

                // Shadowstrike Rank 2
                //if (target->HasAura(SPELL_ROGUE_SHADOWSTRIKE_RANK_2))
                target->CastSpell(target, SPELL_ROGUE_SHADOWSTRIKE_BONUS, true);
                HandleFadeToNothingConduit(target);

                if (target->HasAura(InvigoratingShadowdustLegendary))
                {
                    target->GetSpellHistory()->ReduceCooldowns([target](SpellHistory::CooldownStorageType::iterator itr) -> bool
                    {
                        SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(itr->first, DIFFICULTY_NONE);
                        Milliseconds remainingCooldown = target->GetSpellHistory()->GetRemainingCooldown(spellInfo);

                        bool allow = spellInfo->SpellFamilyName == SPELLFAMILY_ROGUE;

                        if (!allow)
                        {
                            return false;
                            ///switch (spellInfo->Id)
                            ///{
                            ///        return true;
                            ///    default:
                            ///        return false;
                            ///}
                            /// 
                        }

                        return remainingCooldown > 0ms
                            && !itr->second.OnHold;
                    }, 20000);
                }
                if (auto dustEff = target->GetAuraEffect(InvigoratingShadowdust, EFFECT_0))
                {
                    target->GetSpellHistory()->ReduceCooldowns([target](SpellHistory::CooldownStorageType::iterator itr) -> bool
                    {
                        SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(itr->first, DIFFICULTY_NONE);
                        Milliseconds remainingCooldown = target->GetSpellHistory()->GetRemainingCooldown(spellInfo);

                        bool allow = spellInfo->SpellFamilyName == SPELLFAMILY_ROGUE;

                        if (!allow)
                        {
                            return false;
                            ///switch (spellInfo->Id)
                            ///{
                            ///        return true;
                            ///    default:
                            ///        return false;
                            ///}
                            /// 
                        }

                        return remainingCooldown > 0ms
                            && !itr->second.OnHold;
                    }, dustEff->GetAmount());
                }
            }

            void HandleEffectRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
				if (Unit* caster = GetCaster())
				{
                    /// Stealth should be applied just after Vanish buff remove
                    int32 l_CurrentStealthId = caster->HasAura(eSpells::Subterfuge) ? eSpells::StealthSubterfuge : eSpells::Stealth;

                    caster->GetSpellHistory()->ResetCooldown(l_CurrentStealthId, true);
                    caster->CastSpell(caster, l_CurrentStealthId, true);
                    caster->GetSpellHistory()->ResetCooldown(l_CurrentStealthId, true);

					// Veil of the Night
					if (caster->HasAura(SPELL_ROGUE_VEIL_OF_THE_NIGHT))
						caster->CastSpell(caster, SPELL_ROGUE_VEIL_OF_THE_NIGHT_BUFF, true);
                }
            }

            void Register() override
            {
                AfterEffectApply += AuraEffectRemoveFn(spell_rog_vanish_aura_AuraScript::HandleEffectApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
                AfterEffectRemove += AuraEffectRemoveFn(spell_rog_vanish_aura_AuraScript::HandleEffectRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const override
        {
            return new spell_rog_vanish_aura_AuraScript();
        }
};

class spell_rog_serrated_blades : public SpellScriptLoader
{
public:
    spell_rog_serrated_blades() : SpellScriptLoader("spell_rog_serrated_blades") { }

    class spell_rog_serrated_blades_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_rog_serrated_blades_SpellScript);

        void HandleHit()
        {
            if (AuraEffect* blade = GetCaster()->GetAuraEffectOfRankedSpell(SPELL_ROGUE_SERRATED_BLADES_R1, EFFECT_0))
            {
                uint32 combo = GetCaster()->ToPlayer()->GetComboPoints();

                if (roll_chance_i(blade->GetAmount() * combo))
                    if (Aura* dot = GetHitUnit()->GetAura(SPELL_ROGUE_RUPTURE, GetCaster()->GetGUID()))
                        dot->RefreshDuration();

            }
        }

        void Register() override
        {
            OnHit += SpellHitFn(spell_rog_serrated_blades_SpellScript::HandleHit);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_rog_serrated_blades_SpellScript();
    }
};

// Kidney Shot - 408
class spell_rog_kidney_shot :public SpellScript
{
    PrepareSpellScript(spell_rog_kidney_shot);

	bool Validate(SpellInfo const* /*spellInfo*/) override
	{
		return ValidateSpellInfo( { SPELL_ROGUE_KIDNEY_SHOT, SPELL_ROGUE_INTERNAL_BLEEDING, SPELL_ROGUE_INTERNAL_BLEEDING_DOT });
	}

    void HandleTakePower(SpellPowerCost& powerCost)
    {
        if (powerCost.Power == POWER_COMBO_POINTS)        
            _ct = powerCost.Amount;        
    }

    void HandleBeforeHit(SpellMissInfo /*missInfo*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        int32 duration = (_ct + 1) * IN_MILLISECONDS;

        DiminishingGroup const diminishGroup = GetSpellInfo()->GetDiminishingReturnsGroupForSpell();
        target->ApplyDiminishingToDuration(GetSpellInfo(), duration, caster, target->GetDiminishing(diminishGroup));
        duration = caster->ModSpellDuration(GetSpellInfo(), target, duration, false, 1 << EFFECT_0);
        caster->Variables.Set<int32>("Duration_Kidney_Shot", duration);
    }
    
    void HandleAfterHit()
    {
		Unit* caster = GetCaster();
		Unit* target = GetHitUnit();
		if (!caster || !target)
			return;

        // Internal Bleeding
		if (caster->HasAura(SPELL_ROGUE_INTERNAL_BLEEDING))
		{
			uint32 baseDamage = caster->GetTotalAttackPowerValue(BASE_ATTACK) * 0.0312;
			caster->CastSpell(target, SPELL_ROGUE_INTERNAL_BLEEDING_DOT, true);
			if (Aura* aura = target->GetAura(SPELL_ROGUE_INTERNAL_BLEEDING_DOT, caster->GetGUID()))
				aura->GetEffect(EFFECT_0)->SetDamage(baseDamage * _ct);
        }

        // Prey on the Weak
		if (caster->HasAura(SPELL_ROGUE_PREY_ON_THE_WEAK))
			caster->CastSpell(target, SPELL_ROGUE_PREY_ON_THE_WEAK_DEBUFF, true);
    }    

    void Register() override
    {
        OnTakePower += SpellOnTakePowerFn(spell_rog_kidney_shot::HandleTakePower);
        BeforeHit += BeforeSpellHitFn(spell_rog_kidney_shot::HandleBeforeHit);
        AfterHit += SpellHitFn(spell_rog_kidney_shot::HandleAfterHit);
    }

private:
    uint8 _ct;
};

// Kidney Shot - 408
class aura_rog_kidney_shot : public AuraScript
{
    PrepareAuraScript(aura_rog_kidney_shot);

    void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* caster = GetCaster())
        {
            if (Unit* target = GetTarget())
            {
                int32 duration = caster->Variables.GetValue<int32>("Duration_Kidney_Shot");
                SetDuration(duration);
                SetMaxDuration(duration);
            }
        }
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(aura_rog_kidney_shot::OnApply, EFFECT_0, SPELL_AURA_MOD_STUN, AURA_EFFECT_HANDLE_REAL);
    }
};


enum CombatPotency
{
    SPELL_ROGUE_COMBAT_POTENCY = 35551
};

// 35551 - Combat Potency
/// ID - 35551 Fatal Flourish
class spell_rogue_combat_potency : public SpellScriptLoader
{
public:
    spell_rogue_combat_potency() : SpellScriptLoader("spell_rogue_combat_potency") { }

    class spell_rogue_combat_potency_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_rogue_combat_potency_AuraScript);

        bool CheckProc(ProcEventInfo& eventInfo)
        {
            if (eventInfo.GetDamageInfo() && eventInfo.GetDamageInfo()->GetAttackType() == OFF_ATTACK &&
                roll_chance_i(GetEffect(EFFECT_0)->GetAmount()))
                return true;

            return false;
        }

        void Register() override
        {
            DoCheckProc += AuraCheckProcFn(spell_rogue_combat_potency_AuraScript::CheckProc);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_rogue_combat_potency_AuraScript();
    }
};

class spell_rog_deadly_throw : public SpellScriptLoader
{
public:
    spell_rog_deadly_throw() : SpellScriptLoader("spell_rog_deadly_throw") { }

    class spell_rog_deadly_throw_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_rog_deadly_throw_SpellScript);

        void HandleOnHit()
        {
            if (Unit* target = GetHitUnit())
                if (Player* caster = GetCaster()->ToPlayer())
                    if (caster->GetComboPoints() >= 5)
                        caster->CastSpell(target, 137576, true);
        }

        void Register() override
        {
            OnHit += SpellHitFn(spell_rog_deadly_throw_SpellScript::HandleOnHit);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_rog_deadly_throw_SpellScript();
    }
};

class spell_rog_nerve_strike : public SpellScriptLoader
{
public:
    spell_rog_nerve_strike() : SpellScriptLoader("spell_rog_nerve_strike") { }

    class spell_rog_combat_readiness_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_rog_combat_readiness_AuraScript);

        void HandleRemove(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /* mode */)
        {
            if (GetCaster() && GetTarget())
                if (GetCaster()->HasAura(SPELL_ROGUE_NERVE_STRIKE_AURA))
                    GetCaster()->CastSpell(GetTarget(), SPELL_ROGUE_NERVE_STRIKE_REDUCE_DAMAGE_DONE, true);
        }

        void Register() override
        {
            OnEffectRemove += AuraEffectRemoveFn(spell_rog_combat_readiness_AuraScript::HandleRemove, EFFECT_0, SPELL_AURA_MOD_STUN, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_rog_combat_readiness_AuraScript();
    }
};

class spell_rog_nerve_strike_aura : public SpellScriptLoader
{
public:
    spell_rog_nerve_strike_aura() : SpellScriptLoader("spell_rog_nerve_strike_aura") { }

    class spell_rog_nerve_strike_aura_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_rog_nerve_strike_aura_AuraScript);

        void CalculateAmount(AuraEffect const* /*aurEff*/, int32& amount, bool& /* canBeRecalculated */)
        {
            if (Unit* target = GetUnitOwner())
                if (target->GetTypeId() == TYPEID_PLAYER)
                    amount = 25;
        }

        void Register() override
        {
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_rog_nerve_strike_aura_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_MOD_DAMAGE_PERCENT_DONE);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_rog_nerve_strike_aura_AuraScript();
    }
};

class spell_rog_nightstalker : public SpellScriptLoader
{
public:
    spell_rog_nightstalker() : SpellScriptLoader("spell_rog_nightstalker") { }

    class spell_rog_nightstalker_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_rog_nightstalker_AuraScript);

        void HandleApply(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /* mode */)
        {
            if (Unit* caster = GetCaster())
            {
                if (caster->HasAura(SPELL_ROGUE_NIGHTSTALKER_AURA))
                    caster->CastSpell(caster, SPELL_ROGUE_NIGHTSTALKER_DAMAGE_DONE, true);

                if (caster->HasAura(SPELL_ROGUE_SHADOW_FOCUS))
                    caster->CastSpell(caster, SPELL_ROGUE_SHADOW_FOCUS_COST_PCT, true);
            }
        }

        void HandleRemove(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /* mode */)
        {
            if (GetCaster())
            {
                if (GetCaster()->HasAura(SPELL_ROGUE_NIGHTSTALKER_DAMAGE_DONE))
                    GetCaster()->RemoveAura(SPELL_ROGUE_NIGHTSTALKER_DAMAGE_DONE);

                if (GetCaster()->HasAura(SPELL_ROGUE_SHADOW_FOCUS_COST_PCT))
                    GetCaster()->RemoveAura(SPELL_ROGUE_SHADOW_FOCUS_COST_PCT);
            }
        }

        void Register() override
        {
            OnEffectApply += AuraEffectApplyFn(spell_rog_nightstalker_AuraScript::HandleApply, EFFECT_0, SPELL_AURA_MOD_SHAPESHIFT, AURA_EFFECT_HANDLE_REAL);
            OnEffectRemove += AuraEffectRemoveFn(spell_rog_nightstalker_AuraScript::HandleRemove, EFFECT_0, SPELL_AURA_MOD_SHAPESHIFT, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_rog_nightstalker_AuraScript();
    }
};

class spell_rog_dirty_tricks : public SpellScriptLoader
{
public:
    spell_rog_dirty_tricks() : SpellScriptLoader("spell_rog_dirty_tricks") { }

    class spell_rog_dirty_tricks_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_rog_dirty_tricks_AuraScript);

        bool CheckProc(ProcEventInfo& eventInfo)
        {
            const SpellInfo* spellInfo = eventInfo.GetDamageInfo()->GetSpellInfo();
            if (!spellInfo)
                return true;

            if (eventInfo.GetActor()->GetGUID() != GetCasterGUID())
                return true;

            if (spellInfo->Mechanic == MECHANIC_BLEED || spellInfo->GetAllEffectsMechanicMask() & MECHANIC_BLEED || spellInfo->Dispel == DISPEL_POISON)
                if (eventInfo.GetActor()->HasAura(108216))
                    return false;

            return true;
        }

        void Register() override
        {
            DoCheckProc += AuraCheckProcFn(spell_rog_dirty_tricks_AuraScript::CheckProc);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_rog_dirty_tricks_AuraScript();
    }
};

class spell_rog_cloak_and_dagger : public SpellScriptLoader
{
public:
    spell_rog_cloak_and_dagger() : SpellScriptLoader("spell_rog_cloak_and_dagger") { }

    class spell_rog_cloak_and_dagger_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_rog_cloak_and_dagger_SpellScript);

        SpellCastResult CheckCast()
        {
            if (Unit* caster = GetCaster())
                if (caster->HasAuraType(SPELL_AURA_MOD_STEALTH))
                    if (caster->HasAura(138106))
                        if (Unit* target = GetExplTargetUnit())
                            caster->CastSpell(target, 138916, true);

            return SPELL_CAST_OK;
        }

        void Register() override
        {
            OnCheckCast += SpellCheckCastFn(spell_rog_cloak_and_dagger_SpellScript::CheckCast);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_rog_cloak_and_dagger_SpellScript();
    }
};

/// ID: 315496 Slice and Dice
class spell_slice_and_dice_sl : public AuraScript
{
    PrepareAuraScript(spell_slice_and_dice_sl);

    enum eSliceAndDice
    {
        Celerity = 340087,
        AdrenalineRush = 13750,
    };

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
        Unit* caster = GetCaster();
        if (!caster)
            return;

        if (IsSpec(caster, SimpleTalentSpecs::Outlaw))
        {
            chance += 8;

            if (chance > 100)
                chance = 100;

            if (roll_chance_i(chance))
            {
                caster->CastSpell(caster, AdrenalineRush, CastSpellExtraArgs(true).AddSpellMod(SpellValueMod::SPELLVALUE_DURATION, 3000));
                chance = 0;
            }
        }
    }

    uint32 chance = 0;

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_slice_and_dice_sl::HandlePeriodic, EFFECT_0, SPELL_AURA_OBS_MOD_HEALTH);
    }
};

// 51701 - Honor Among Thieves
class spell_rog_honor_among_thieves : public SpellScriptLoader
{
public:
    spell_rog_honor_among_thieves() : SpellScriptLoader("spell_rog_honor_among_thieves") { }

    class spell_rog_honor_among_thieves_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_rog_honor_among_thieves_AuraScript);

        void HandleProc(AuraEffect* aurEff, ProcEventInfo& /*eventInfo*/)
        {
            PreventDefaultAction();

            Unit* target = GetUnitOwner();
            target->CastSpell(target, SPELL_ROGUE_HONOR_AMONG_THIEVES_PROC, TRIGGERED_FULL_MASK);// , nullptr, aurEff);
        }

        void Register() override
        {
            OnEffectProc += AuraEffectProcFn(spell_rog_honor_among_thieves_AuraScript::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_rog_honor_among_thieves_AuraScript();
    }
};

// 32645 - Envenom
class spell_rog_envenom : public SpellScript
{
    PrepareSpellScript(spell_rog_envenom);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_ROGUE_ENVENOM });
    }

	void HandleTakePower(SpellPowerCost& powerCost)
	{
        if (powerCost.Power == POWER_COMBO_POINTS)        
            cp = powerCost.Amount;        
	}

    void CalculateDamage(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        if (!caster)
            return;

        int32 damage = GetHitDamage();

        if (caster->Variables.Exist("DFA_ComboPoints"))
            cp = caster->Variables.GetValue<uint8>("DFA_ComboPoints");
        

        cp = GetSpell()->GetUsedComboPoints();

        caster->Variables.Set<uint8>("CP", cp);

        damage *= cp;

        // Cut to the chase
        if (GetCaster()->HasAura(51667))
        {
            int32 amount = 4000 * (uint32)cp;
            if (Aura* aura = GetCaster()->GetAura(SPELL_ROGUE_SLICE_AND_DICE))
            {
                aura->SetDuration(aura->GetDuration() + amount);
                aura->SetMaxDuration(aura->GetMaxDuration() + amount);
            }
        }
        caster->Variables.Remove("DFA_ComboPoints");
        SetHitDamage(damage);        
    }

    void HandleAfterHit()
    {
		Unit* caster = GetCaster();
		Unit* target = GetHitUnit();
		if (!caster || !target)
			return;

		caster->CastSpell(caster, SPELL_ROGUE_ENVENOM, true);
        if (Aura* envenomAura = caster->GetAura(GetSpellInfo()->Id))
			envenomAura->SetDuration((cp + 1) * IN_MILLISECONDS);

		// Creeping Venom
		if (caster->HasAura(SPELL_ROGUE_CREEPING_VENOM))
			caster->CastSpell(target, SPELL_ROGUE_CREEPING_VENOM_AURA, true);

        // System Shock
		if (caster->HasAura(SPELL_ROGUE_SYSTEM_SHOCK) && cp == 5 && (target->HasAura(SPELL_ROGUE_GARROTE_DOT, caster->GetGUID()) || target->HasAura(SPELL_ROGUE_RUPTURE, caster->GetGUID()) ||
			target->HasAura(SPELL_ROGUE_WOUND_POISON_DOT, caster->GetGUID()) || target->HasAura(SPELL_ROGUE_DEADLY_POISON_DOT, caster->GetGUID())))
			caster->CastSpell(target, SPELL_ROGUE_SYSTEM_SHOCK_DAMAGE, true);
    }

    void Register() override
    {
		OnTakePower += SpellOnTakePowerFn(spell_rog_envenom::HandleTakePower);
        OnEffectHitTarget += SpellEffectFn(spell_rog_envenom::CalculateDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
        AfterHit += SpellHitFn(spell_rog_envenom::HandleAfterHit);
    }

private:
	uint8 cp = 0;
};

// Shuriken Storm - 197835
class spell_rog_shuriken_storm : public SpellScriptLoader
{
public:
    spell_rog_shuriken_storm() : SpellScriptLoader("spell_rog_shuriken_storm") {}

    class spell_rog_shuriken_storm_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_rog_shuriken_storm_SpellScript);

    public:
        spell_rog_shuriken_storm_SpellScript()
        {
            _stealthed = false;
            _canApplyShurikenCombo = false;
        }

    private:

        bool _canApplyShurikenCombo;
        bool _stealthed;

        bool Load() override
        {
            Unit* caster = GetCaster();
            if (caster->HasAuraType(SPELL_AURA_MOD_STEALTH) || caster->HasAura(SPELL_ROGUE_SHADOW_DANCE))
                _stealthed = true;
            return true;
        }

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            return ValidateSpellInfo(
                {
                    SPELL_ROGUE_SHURIKEN_STORM
                });
        }

        void RemoveKS()
        {
            Unit* target = GetHitUnit();
            if (target->HasAura(51690)) //Killing spree debuff #1
                target->RemoveAura(51690);
            if (target->HasAura(61851)) //Killing spree debuff #2
                target->RemoveAura(61851);
        }

        void HandleOnHit()
        {
            if (Unit* caster = GetCaster())
            {
                Unit* target = GetHitUnit();
                if (!caster || !target)
                    return;

                uint8 cp = caster->GetPower(POWER_COMBO_POINTS);
                if (_stealthed)
                {
                    int32 dmg = GetHitDamage();
                    SetHitDamage(dmg + CalculatePct(dmg, 50)); //Shuriken Storm deals 50% damage from stealth
                }
                if (cp < caster->GetMaxPower(POWER_COMBO_POINTS))
                {
                    caster->SetPower(POWER_COMBO_POINTS, cp + 1);
                }

              // if (IsHitCrit())
              //     caster->CastSpell(target, )


                if (IsHitCrit() && caster->HasAura(Rogue::eSubtletyTraits::ImprovedShurikenStorm))
                    caster->CastSpell(target, Rogue::eSubtlety::FindWeaknesDebuff, true);

                // Night Terrors
                if (caster->HasAura(SPELL_ROGUE_NIGHT_TERRORS))
                    caster->CastSpell(target, SPELL_ROGUE_SHADOW_GRASP_SLOW, true);

                // 245640 Shuriken Storm
                if (_canApplyShurikenCombo)
                    ;// caster->CastSpell(caster, SPELL_ROGUE_SHURIKEN_COMBO, true);
                else
                    _canApplyShurikenCombo = true;
            }
        }

        void Register() override
        {
            OnHit += SpellHitFn(spell_rog_shuriken_storm_SpellScript::HandleOnHit); //add 1 combo points for each target (hook called for each target in map)
            AfterHit += SpellHitFn(spell_rog_shuriken_storm_SpellScript::RemoveKS);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_rog_shuriken_storm_SpellScript();
    }
};

// Fan of Knives - 51723
class spell_rog_fan_of_knives : public SpellScriptLoader
{
public:
    spell_rog_fan_of_knives() : SpellScriptLoader("spell_rog_fan_of_knives") {}

    class spell_rog_fan_of_knives_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_rog_fan_of_knives_SpellScript);

    public:

        spell_rog_fan_of_knives_SpellScript()
        {
            _hit = false;
        }

    private:

        bool _hit;

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            return ValidateSpellInfo(
            {
                SPELL_ROGUE_FAN_OF_KNIVES
            });
        }

        bool Load() override
        {
            return true;
        }

        void AddCp()
        {
            if (!GetCaster())
                return;
            if (!_hit)
            {
                uint8 cp = GetCaster()->GetPower(POWER_COMBO_POINTS);
                if (cp < GetCaster()->GetMaxPower(POWER_COMBO_POINTS))
                {
                    GetCaster()->SetPower(POWER_COMBO_POINTS, cp + 1);
                }
                _hit = true;
            }
        }

        void RemoveKS()
        {
            Unit* target = GetHitUnit();
            if (!target)
                return;
            if (target->HasAura(51690)) //Killing spree debuff #1
                target->RemoveAura(51690);
            if (target->HasAura(61851)) //Killing spree debuff #2
                target->RemoveAura(61851);
        }

        void HandleDmg(SpellEffIndex /*eff*/)
        {
            if (!GetCaster())
                return;

            if (auto hiddenBlades = GetCaster()->GetAura(SPELL_ROGUE_HIDDEN_BLADES_BUFF))
            {
                auto dmg = GetHitDamage();
                AddPct(dmg, hiddenBlades->GetStackAmount() * 20);
                SetHitDamage(dmg);
                hiddenBlades->Remove();
            }
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_rog_fan_of_knives_SpellScript::HandleDmg, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
            OnHit += SpellHitFn(spell_rog_fan_of_knives_SpellScript::AddCp);
            AfterHit += SpellHitFn(spell_rog_fan_of_knives_SpellScript::RemoveKS);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_rog_fan_of_knives_SpellScript();
    }
};

// Shadowstrike - 185438
class spell_rog_shadowstrike : public SpellScriptLoader
{
public:
    spell_rog_shadowstrike() : SpellScriptLoader("spell_rog_shadowstrike") {}

    class spell_rog_shadowstrike_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_rog_shadowstrike_SpellScript);

        enum UsedSpells
        {
            SPELL_ROGUE_STRIKE_FROM_THE_SHADOWS_SLOW = 222775,
            SPELL_ROGUE_STRIKE_FROM_THE_SHADOWS_STUN = 196958,

            ImmortalTechnique = 364557,
        };

        bool Validate(SpellInfo const* /*SpellInfo*/) override
        {
            return ValidateSpellInfo(
            {
                SPELL_ROGUE_SHADOWSTRIKE,
                SPELL_ROGUE_SHADOWSTEP_LEAP,
				SPELL_ROGUE_COLD_BLOOD_DAMAGE
            });
        }

        void HandleBeforeCast()
        {
            Unit* caster = GetCaster();
            Unit* target = GetExplTargetUnit();
            if (!caster || !target)
                return;

            if (caster->HasAura(SPELL_ROGUE_SHADOWSTRIKE_BONUS))
                if (!caster->IsWithinMeleeRange(target))
                    GetCaster()->CastSpell(target, SPELL_ROGUE_SHADOWSTEP_LEAP, true);
        }

        void HandleHitTarget(SpellEffIndex /*effIndex*/)
        {
            Unit* caster = GetCaster();
            Unit* target = GetHitUnit();
            if (!caster || !target)
                return;

            if (caster->HasAura(SPELL_ROGUE_STRIKE_FROM_THE_SHADOWS))
            {
                if (target->GetTypeId() == TYPEID_PLAYER)
                    caster->CastSpell(target, SPELL_ROGUE_STRIKE_FROM_THE_SHADOWS_SLOW, true);
                else
                    caster->CastSpell(target, SPELL_ROGUE_STRIKE_FROM_THE_SHADOWS_STUN, true);
            }

            // Cold Blood
            if (caster->HasAura(SPELL_ROGUE_COLD_BLOOD))
            {
                caster->CastSpell(target, SPELL_ROGUE_COLD_BLOOD_DAMAGE, true);
                caster->RemoveAurasDueToSpell(SPELL_ROGUE_COLD_BLOOD);
            }

            if (caster->HasSpell(SPELL_ROGUE_SHADOW_GRASP))
                caster->CastSpell(target, SPELL_ROGUE_SHADOW_GRASP_SLOW, true);

            if(caster->HasAura(SPELL_ROGUE_SHADOWSTRIKE_BONUS))
                caster->RemoveAurasDueToSpell(SPELL_ROGUE_SHADOWSTRIKE_BONUS);

            if (auto aur = caster->GetAura(ImmortalTechnique))
            {
                if (roll_chance_i(15))
                {
                    uint32 AddDuration = 5000;

                    if (auto shadowBlades = caster->GetAura(SPELL_ROGUE_SHADOW_BLADES))
                        shadowBlades->ModDuration(AddDuration);
                    else if (auto shadowBlades = caster->AddAura(SPELL_ROGUE_SHADOW_BLADES))
                    {
                        shadowBlades->SetDuration(AddDuration);
                    }
                }
            }
        }

        void Register() override
        {
            BeforeCast += SpellCastFn(spell_rog_shadowstrike_SpellScript::HandleBeforeCast);
            OnEffectHitTarget += SpellEffectFn(spell_rog_shadowstrike_SpellScript::HandleHitTarget, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_rog_shadowstrike_SpellScript();
    }
};

// 703 - Garrote
// Last Update 8.0.1 Build 28153
class spell_rog_garrote : public SpellScript
{
    PrepareSpellScript(spell_rog_garrote);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo(
            {
                SPELL_ROGUE_GARROTE_DOT,
                SPELL_ROGUE_GARROTE_SILENCE,
                SPELL_ROGUE_SUBTERFUGE,
                SPELL_ROGUE_SUBTERFUGE_AURA
            });
    }

    bool Load() override
    {
        if (Unit* caster = GetCaster())
            if (caster->HasAuraType(SPELL_AURA_MOD_STEALTH) || caster->HasAura(SPELL_ROGUE_SUBTERFUGE_AURA))
                _stealthed = true;
        return true;
    }

    void HandleOnHit(SpellEffIndex /*index*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        uint32 damage = GetHitDamage();
        if (_stealthed && caster->HasAura(SPELL_ROGUE_GARROTE_RANK_2))
        {
            caster->CastSpell(target, SPELL_ROGUE_GARROTE_SILENCE, true);

            // Shrouded Suffocation
            if (Aura* aura = caster->GetAura(SPELL_ROGUE_SHROUDED_SUFFOCATION))            
                caster->CastSpell(caster, SPELL_ROGUE_SHROUDED_SUFFOCATION_ENERGIZE, true);            

            // Iron Wire
            if (caster->HasAura(SPELL_ROGUE_IRON_WIRE))
                caster->CastSpell(target, SPELL_ROGUE_IRON_WIRE_DEBUFF, true);
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_rog_garrote::HandleOnHit, EFFECT_0, SPELL_EFFECT_APPLY_AURA);
    }

private:
    bool _stealthed = false;
};

// 703 - Garrote
// Last Update 8.0.1 Build 28153
class aura_rog_garrote : public AuraScript
{
    PrepareAuraScript(aura_rog_garrote);

    void HandleApply(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* caster = GetCaster())
        {
            if (Unit* target = GetTarget())
            {
                if (AuraEffect* effect = GetAura()->GetEffect(EFFECT_0))
                {
                    effect->SetDonePct(caster->SpellDamagePctDone(target, GetSpellInfo(), DOT, effect->GetSpellEffectInfo())); // Calculate done percentage first!
                    int32 damage = caster->SpellDamageBonusDone(target, GetSpellInfo(), 0, DOT, effect->GetSpellEffectInfo(), GetStackAmount());

                    // Shrouded Suffocation
                    if (Aura* aura = caster->GetAura(SPELL_ROGUE_SHROUDED_SUFFOCATION))
                        damage += aura->GetEffect(EFFECT_0)->GetAmount();                    

                    if (caster->HasAura(SPELL_ROGUE_SUBTERFUGE_AURA))
                        damage += CalculatePct(damage, sSpellMgr->GetSpellInfo(SPELL_ROGUE_SUBTERFUGE_AURA)->GetEffect(EFFECT_1).BasePoints);

                    effect->SetDamage(damage * effect->GetDonePct());

                    Rogue::HandleGrudgeMatch(caster, target, GetAura());
                }
            }
        }
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(aura_rog_garrote::HandleApply, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE, AURA_EFFECT_HANDLE_REAL);
    }
};

// True Bearing - 193359
class spell_rog_true_bearing : public SpellScriptLoader
{
public:
    spell_rog_true_bearing() : SpellScriptLoader("spell_rog_true_bearing") {}

    class spell_rog_true_bearing_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_rog_true_bearing_AuraScript);

        bool CheckProc(ProcEventInfo& eventInfo)
        {
            std::vector<uint32> finishers{ SPELL_ROGUE_BETWEEN_THE_EYES, SPELL_ROGUE_ROLL_THE_BONES, SPELL_ROGUE_EVISCERATE };
            for (uint32 finisher : finishers)
                if (eventInfo.GetSpellInfo()->Id == finisher)
                    return true;
            return false;
        }

        void HandleProc(AuraEffect* /*aurEff*/, ProcEventInfo& /*eventInfo*/)
        {
            Unit* caster = GetCaster();
            if (!caster)
                return;

            int32 cp = caster->GetPower(POWER_COMBO_POINTS) + 1;

            std::vector<uint32> spellIds{ SPELL_ROGUE_ADRENALINE_RUSH, SPELL_ROGUE_SPRINT, SPELL_ROGUE_BETWEEN_THE_EYES,
                                          SPELL_ROGUE_VANISH, SPELL_ROGUE_BLIND, SPELL_ROGUE_CLOAK_OF_SHADOWS,
                                          SPELL_ROGUE_RIPOSTE, SPELL_ROGUE_GRAPPLING_HOOK, SPELL_ROGUE_CANNONBALL_BARRAGE,
                                          SPELL_ROGUE_KILLING_SPREE, SPELL_ROGUE_MARKED_FOR_DEATH, SPELL_ROGUE_DEATH_FROM_ABOVE };

            for (uint32 spell : spellIds)
            {
                if (caster->HasSpell(spell))
                    caster->GetSpellHistory()->ModifyCooldown(spell, -2000 * cp);
            }
        }

        void Register() override
        {
            DoCheckProc += AuraCheckProcFn(spell_rog_true_bearing_AuraScript::CheckProc);
            OnEffectProc += AuraEffectProcFn(spell_rog_true_bearing_AuraScript::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_rog_true_bearing_AuraScript();
    }
};

/// ID: 14161 Ruthlessness
class spell_rog_ruthlessness : public SpellScriptLoader
{
public:
    spell_rog_ruthlessness() : SpellScriptLoader("spell_rog_ruthlessness") { }

    class spell_rog_ruthlessness_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_rog_ruthlessness_AuraScript);

        bool CheckProc(ProcEventInfo& eventInfo)
        {
            if (auto spell = eventInfo.GetProcSpell())
                if (auto comboPoints = spell->GetUsedComboPoints())
                    return roll_chance_i(20 * comboPoints);

            return false;
        }

        void HandleProc(ProcEventInfo& /*procInfo*/)
        {
            // @todo: find if this energize is a spell!
            if (Unit* caster = GetCaster())
                caster->ModifyPower(POWER_COMBO_POINTS, + 1);
        }

        void Register() override
        {
            DoCheckProc += AuraCheckProcFn(spell_rog_ruthlessness_AuraScript::CheckProc);
            OnProc += AuraProcFn(spell_rog_ruthlessness_AuraScript::HandleProc);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_rog_ruthlessness_AuraScript();
    }
};

//199754
class spell_rog_riposte : public SpellScriptLoader
{
public:
    spell_rog_riposte() : SpellScriptLoader("spell_rog_riposte") { }

    class spell_rog_riposte_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_rog_riposte_AuraScript);

        void HandleProc(AuraEffect* /*aurEff*/, ProcEventInfo& procInfo)
        {
            PreventDefaultAction();

            Unit* caster = GetCaster();
            if(!caster)
                return;

            Unit* target = procInfo.GetActionTarget();
            if(!target)
                return;
            caster->CastSpell(target, SPELL_ROGUE_RIPOSTE_DAMAGE, true);
        }

        void Register() override
        {
            OnEffectProc += AuraEffectProcFn(spell_rog_riposte_AuraScript::HandleProc, EFFECT_1, SPELL_AURA_PROC_TRIGGER_SPELL);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_rog_riposte_AuraScript();
    }
};

//185313 shadow dance
class spell_rog_shadow_dance : public SpellScript
{
    PrepareSpellScript(spell_rog_shadow_dance);

        void HandleHit(SpellEffIndex /*effIndex*/)
        {
            if (Unit* caster = GetCaster())
            {
                if (caster->HasAura(SPELL_ROGUE_MASTER_OF_SHADOWS))
                    caster->CastSpell(caster, SPELL_ROGUE_MASTER_OF_SHADOW_BUFF, true);

			    caster->CastSpell(caster, SPELL_ROGUE_STEALTH_BAR);
			    caster->CastSpell(caster, SPELL_ROGUE_SHADOW_DANCE_AURA, true);

                if (caster->HasAura(Rogue::eSubtletyTraits::TheFirstDance))
                    caster->EnergizeBySpell(caster, sSpellMgr->GetSpellInfo(Rogue::eSubtletyTraits::TheFirstDance), 4, Powers::POWER_COMBO_POINTS);

                HandleFadeToNothingConduit(caster);
            }
        }

        void Register() override
        {
        OnEffectHit += SpellEffectFn(spell_rog_shadow_dance::HandleHit, EFFECT_0, SPELL_EFFECT_APPLY_AURA);
        }
    };

class aura_rog_shadow_dance_effect : public AuraScript
{
    PrepareAuraScript(aura_rog_shadow_dance_effect);

    void HandleApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
		if (Unit* caster = GetCaster())
		{
			if (caster->HasAura(SPELL_ROGUE_SHADOW_FOCUS))
				caster->CastSpell(caster, SPELL_ROGUE_SHADOW_FOCUS_COST_PCT, true);

			if (caster->HasAura(SPELL_ROGUE_SHOT_IN_THE_DARK))
				caster->CastSpell(caster, SPELL_ROGUE_SHOT_IN_THE_DARK_BUFF, true);

            if (caster->HasAura(Rogue::eSubtletyTraits::Premeditation))
                caster->CastSpell(caster, Rogue::eSubtletyTraits::PremeditationProcAura, true);

            if (caster->HasAura(Rogue::eSubtletyTraits::SilentStorm))
                caster->CastSpell(caster, Rogue::eSubtletyTraits::SilentStormProcAura, true);

            if (caster->HasAura(Rogue::eSubtletyTraits::DanseMacabre))
                caster->CastSpell(caster, Rogue::eSubtletyTraits::DanseMacabreProc, true);
		}
    }

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* caster = GetCaster())
        {
            caster->RemoveAura(SPELL_ROGUE_SHADOW_FOCUS_COST_PCT);
            caster->RemoveAura(SPELL_ROGUE_STEALTH_BAR);
            caster->RemoveAura(SPELL_ROGUE_SHADOW_DANCE_AURA);
            caster->RemoveAurasDueToSpell(SPELL_ROGUE_SHROUD_OF_CONCEALMENT);
            caster->RemoveAurasDueToSpell(Rogue::eSubtletyTraits::PremeditationProcAura);
            caster->RemoveAurasDueToSpell(Rogue::eSubtletyTraits::DanseMacabreProc);
        }
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(aura_rog_shadow_dance_effect::HandleApply, EFFECT_0, SPELL_AURA_MOD_TOTAL_THREAT, AURA_EFFECT_HANDLE_REAL);
        OnEffectRemove += AuraEffectRemoveFn(aura_rog_shadow_dance_effect::HandleRemove, EFFECT_0, SPELL_AURA_MOD_TOTAL_THREAT, AURA_EFFECT_HANDLE_REAL);
    }
};

// Backstab - 53
class spell_rog_backstab : public SpellScriptLoader
{
public:
    spell_rog_backstab() : SpellScriptLoader("spell_rog_backstab") {}

    class spell_rog_backstab_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_rog_backstab_SpellScript);

        void HandleDamage(SpellEffIndex /*effIndex*/)
        {
            Unit* target = GetHitUnit();
            Unit* caster = GetCaster();
            if (!target || !caster)
                return;

            int32 dmg = GetHitDamage();
            if (!target->isInFront(caster))
                AddPct(dmg, 20);

            SetHitDamage(dmg);

			if (caster->HasSpell(SPELL_ROGUE_SHADOW_GRASP))
				caster->CastSpell(target, SPELL_ROGUE_SHADOW_GRASP_SLOW, true);
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_rog_backstab_SpellScript::HandleDamage, EFFECT_1, SPELL_EFFECT_SCHOOL_DAMAGE);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_rog_backstab_SpellScript();
    }
};

// Nightblade - 195452
class spell_rog_nightblade : public SpellScriptLoader
{
public:
    spell_rog_nightblade() : SpellScriptLoader("spell_rog_nightblade") {}

    class spell_rog_nightblade_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_rog_nightblade_AuraScript);

        bool CheckProc(ProcEventInfo& eventInfo)
        {
            if (eventInfo.GetDamageInfo()->GetAttackType() == BASE_ATTACK ||
                eventInfo.GetDamageInfo()->GetAttackType() == OFF_ATTACK)
            {
                Unit* caster = eventInfo.GetActor();
                Unit* target = eventInfo.GetActionTarget();
                if (!caster || !target)
                    return false;

                caster->CastSpell(target, SPELL_ROGUE_NIGHTBLADE_SLOW, true);
                return true;
            }
            return false;
        }

        void Register() override
        {
            DoCheckProc += AuraCheckProcFn(spell_rog_nightblade_AuraScript::CheckProc);
        }
    };

    class spell_rog_nightblade_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_rog_nightblade_SpellScript);

        int32 m_ComboPoints = 0;

        void HandleTakePower(SpellPowerCost& powerCost)
        {
            if (powerCost.Power == POWER_COMBO_POINTS)
                m_ComboPoints = GetSpell()->GetPowerCost(POWER_COMBO_POINTS)->Amount;
        }

        void HandleAfterHit()
        {
            if (Unit* caster = GetCaster())
            {
                int32 maxcp = caster->HasAura(SPELL_ROGUE_DEEPER_STRATAGEM) ? 6 : 5;
                m_ComboPoints = std::min(m_ComboPoints, maxcp);

                if (Unit* target = GetHitUnit())
                {
                    if (Aura* aura = target->GetAura(SPELL_ROGUE_NIGHTBLADE))
                    {
                        int32 duration = aura->GetDuration() + 2000 * m_ComboPoints;
                        aura->SetDuration(duration);
                        aura->SetMaxDuration(duration);
                    }
                }

                if (Unit* caster = GetCaster())
                    caster->ModifyPower(POWER_COMBO_POINTS, -1 * (m_ComboPoints - 1));

                if (Unit* caster = GetCaster())
                    if (caster->HasAura(SPELL_ROGUE_RELENTLESS_STRIKES) && roll_chance_i(20 * m_ComboPoints))
                        caster->CastSpell(caster, SPELL_ROGUE_RELENTLESS_STRIKES_POWER, true);

                if (GetCaster()->HasAura(SPELL_ROGUE_ALACRITY) && roll_chance_i(20 * m_ComboPoints))
                    GetCaster()->CastSpell(GetCaster(), SPELL_ROGUE_ALACRITY_BUFF, true);
            }
        }

        void HandleLaunch(SpellEffIndex /*effIndex*/)
        {
            Unit* caster = GetCaster();
            Unit* target = GetHitUnit();
            if (!caster || !target)
                return;

            target->RemoveAurasDueToSpell(SPELL_ROGUE_NIGHTBLADE, caster->GetGUID());
        }

        void Register() override
        {
            OnTakePower += SpellOnTakePowerFn(spell_rog_nightblade_SpellScript::HandleTakePower);
            OnEffectLaunchTarget += SpellEffectFn(spell_rog_nightblade_SpellScript::HandleLaunch, EFFECT_0, SPELL_EFFECT_APPLY_AURA);
            AfterHit += SpellHitFn(spell_rog_nightblade_SpellScript::HandleAfterHit);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_rog_nightblade_SpellScript();
    }

    AuraScript* GetAuraScript() const override
    {
        return new spell_rog_nightblade_AuraScript();
    }
};

/// 185314 - Deepening Shadows - Updated 10.0.2.45596
class spell_rog_deepening_shadows : public AuraScript
{
    PrepareAuraScript(spell_rog_deepening_shadows);

    enum Shadow
    {
        ShadowDanceChargeID = 1615,
        EnvelopingShadows = 238104,
        ImmortalTechnique = 363949,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (auto procSpell = eventInfo.GetProcSpell())
            return procSpell->GetUsedComboPoints();

        return false;
    }

    void HandleProc(AuraEffect* aurEff, ProcEventInfo& eventInfo)
    {
        if (auto spell = eventInfo.GetProcSpell())
        {
            if (Unit* caster = GetCaster())
            {
                uint32 CDR = 1000;

                if (caster->HasAura(EnvelopingShadows))
                    CDR += 500;

                auto cp = spell->GetUsedComboPoints();

                // 4 set bonus
                /// TODO: move this to proc spell script
                if (caster->HasAura(ImmortalTechnique))
                {
                    if (roll_chance_i(cp * 3))
                    {
                        std::list<Unit*> attackUnits;
                        caster->GetAttackableUnitListInRange(attackUnits, 15.0f);
                        attackUnits.remove_if([caster](Unit* who) {
                            return !who->IsInCombat();
                        });

                        if (!attackUnits.empty())
                        {
                            bool hasLeapBonus = caster->HasAura(SPELL_ROGUE_SHADOWSTRIKE_BONUS);
                            if (hasLeapBonus)
                                caster->RemoveAurasDueToSpell(SPELL_ROGUE_SHADOWSTRIKE_BONUS);

                            for (auto unit : attackUnits)
                            {
                                caster->CastSpell(unit, SPELL_ROGUE_SHADOWSTRIKE, CastSpellExtraArgs(TriggerCastFlags(TRIGGERED_IGNORE_POWER_AND_REAGENT_COST | TRIGGERED_IGNORE_SPELL_AND_CATEGORY_CD | TRIGGERED_IGNORE_GCD)));
                            }

                            if (hasLeapBonus)
                                caster->CastSpell(caster, SPELL_ROGUE_SHADOWSTRIKE_BONUS, true);
                        }

                    }
                }

                caster->GetSpellHistory()->ReduceChargeCooldown(
                    ShadowDanceChargeID,
                    cp * CDR);
            }
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_rog_deepening_shadows::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_rog_deepening_shadows::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

// Shadow Techniques - 196912 Update for 8.0.1 build 28153
class spell_rog_shadow_techniques : public SpellScriptLoader
{
public:
    spell_rog_shadow_techniques() : SpellScriptLoader("spell_rog_shadow_techniques") {}

    class spell_rog_shadow_techniques_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_rog_shadow_techniques_AuraScript);

        enum eShadowTechniques
        {
            StilettoStaccatoConduit = 341559,
        };

        bool CheckProc(ProcEventInfo& eventInfo)
        {
            if (eventInfo.GetDamageInfo() && eventInfo.GetDamageInfo()->GetDamageType() == DIRECT_DAMAGE)
                return true;
            return false;
        }

        //https://www.wowhead.com/spell=196912/shadow-techniques
        void HandleProc(AuraEffect* /*aurEff*/, ProcEventInfo& /*eventInfo*/)
        {
            Unit* caster = GetCaster();
            if (!caster)
                return;

            uint8 count = 0;

            if(caster->Variables.Exist("ShadowTechniques"))
                count = caster->Variables.GetValue<uint8>("ShadowTechniques");

            count++;

            caster->Variables.Set<uint8>("ShadowTechniques", count);

            auto ApplyEffects([&]() -> void
            {
                if (auto eff = caster->GetAuraEffect(StilettoStaccatoConduit, EFFECT_0))
                    if (eff->ConduitRankEntry)
                        caster->GetSpellHistory()->ModifyCooldown(SPELL_ROGUE_SHADOW_BLADES, -(eff->ConduitRankEntry->AuraPointsOverride * 1000.0f));

                if (auto eff = caster->GetAuraEffect(Rogue::eSubtletyTraits::StiletoStaccato, EFFECT_0))
                    caster->GetSpellHistory()->ModifyCooldown(SPELL_ROGUE_SHADOW_BLADES, -(eff->GetAmount() * 1000));

                caster->CastSpell(caster, SPELL_ROGUE_SHADOW_TENCHNIQUES_POWER, true);
                caster->Variables.Remove("ShadowTechniques");
            });

            if (count == 4)
            {
                if (roll_chance_i(50))
                {
                    ApplyEffects();
                }
            }
            else if (count > 4)
            {
                ApplyEffects();
            }
        }

        void Register() override
        {
            DoCheckProc += AuraCheckProcFn(spell_rog_shadow_techniques_AuraScript::CheckProc);
            OnEffectProc += AuraEffectProcFn(spell_rog_shadow_techniques_AuraScript::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_rog_shadow_techniques_AuraScript();
    }
};

// Weaponmaster - 193537
class spell_rog_weaponmaster : public SpellScriptLoader
{
    public:
        spell_rog_weaponmaster() : SpellScriptLoader("spell_rog_weaponmaster") {}

        class spell_rog_weaponmaster_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_rog_weaponmaster_AuraScript);

            bool CheckProc(ProcEventInfo& eventInfo)
            {
                Unit* caster = eventInfo.GetActor();
                Unit* target = eventInfo.GetActionTarget();
                if (!target || !caster)
                    return false;

                SpellInfo const* triggerSpell = eventInfo.GetSpellInfo();
                if (!triggerSpell)
                    return false;

                if (!roll_chance_i(GetEffect(EFFECT_0)->GetAmount()))
                    return false;

                // SPELL_AURA_PROC_TRIGGER_SPELL_COPY maybe can handle automatically. Not sure rn since only 3 spells use it as of patch 10.0.2.45569
                caster->CastSpell(target, triggerSpell->Id, true);
                return true;
            }

            void Register() override
            {
                DoCheckProc += AuraCheckProcFn(spell_rog_weaponmaster_AuraScript::CheckProc);
            }
        };

        AuraScript* GetAuraScript() const override
        {
            return new spell_rog_weaponmaster_AuraScript();
        }
};

// Alacrity - 193539
class spell_rog_alacrity : public SpellScriptLoader
{
public:
    spell_rog_alacrity() : SpellScriptLoader("spell_rog_alacrity") {}

    class spell_rog_alacrity_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_rog_alacrity_AuraScript);

        enum eAlacrity
        {
            AlacrityProc = 193538,
        };

        void HandleProc(AuraEffect* /*aurEff*/, ProcEventInfo& eventInfo)
        {
            PreventDefaultAction();
            Unit* caster = GetCaster();
            if (!caster)
                return;

            if (auto procSpell = eventInfo.GetProcSpell())
                if (auto comboPoints = procSpell->GetUsedComboPoints())
                    if (roll_chance_i(std::min(100.0f, static_cast<float>(GetEffect(EFFECT_1)->GetAmount()) * comboPoints)))
                        caster->CastSpell(caster, AlacrityProc, true);
        }

        void Register() override
        {
            OnEffectProc += AuraEffectProcFn(spell_rog_alacrity_AuraScript::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_rog_alacrity_AuraScript();
    }
};

// 137619 - Mark for Death
class aura_rog_marked_for_death : public AuraScript
{
    PrepareAuraScript(aura_rog_marked_for_death);

    void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Unit* caster = GetCaster();
        Unit* owner = GetUnitOwner();
        if (!caster || !owner)
            return;

        AuraRemoveMode removeMode = GetTargetApplication()->GetRemoveMode();
        if (removeMode == AURA_REMOVE_BY_DEATH)
            caster->GetSpellHistory()->ResetCooldown(SPELL_ROGUE_MARKED_FOR_DEATH, true);
    }

    void Register()
    {
        OnEffectRemove += AuraEffectRemoveFn(aura_rog_marked_for_death::OnRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

class spell_rog_beetween_the_eyes : public SpellScript
{
    PrepareSpellScript(spell_rog_beetween_the_eyes);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ 199804 });
    }

    void CalcDamage(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        if (!caster)
            return;

        Unit* owner = caster->GetOwner();
        if (!owner)
            return;

        Unit* target = GetExplTargetUnit();
        if (!target)
            return;

        // (26% * (rap) * lowNerf * (1 + versability))
        int32 dmg = (owner->m_unitData->AttackPower / 100) * 18.0999f;
        int32 lowNerf = ((owner->m_unitData->AttackPower + owner->m_unitData->OffHandWeaponAttackPower) * 2 / 3) / (owner->m_unitData->AttackPower * owner->GetPower(POWER_COMBO_POINTS));
        dmg *= lowNerf;

        dmg = caster->SpellDamageBonusDone(target, GetSpellInfo(), dmg, SPELL_DIRECT_DAMAGE, GetEffectInfo(EFFECT_0));
        dmg = target->SpellDamageBonusTaken(caster, GetSpellInfo(), dmg, SPELL_DIRECT_DAMAGE);

        SetHitDamage(dmg);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_rog_beetween_the_eyes::CalcDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

class spell_rog_internal_bleeding_damage : public SpellScriptLoader
{
public:
    spell_rog_internal_bleeding_damage() : SpellScriptLoader("spell_rog_internal_bleeding_damage") { }

    class spell_rog_internal_bleeding_damage_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_rog_internal_bleeding_damage_SpellScript);

        uint8 m_NbComboPoint = 0;

        void HandleOnHit()
        {
            Unit* caster = GetCaster();

            m_NbComboPoint = caster->GetPower(POWER_COMBO_POINTS);
        }

        void HandleAfterHit()
        {
            Unit* caster = GetCaster();
            Unit* target = GetHitUnit();

            if (target == nullptr)
                return;

            if (AuraEffect* l_AurEff = target->GetAuraEffect(SPELL_ROGUE_INTERNAL_BLEEDING_DOT, EFFECT_0, caster->GetGUID()))
                l_AurEff->SetAmount(l_AurEff->GetAmount() * m_NbComboPoint);
        }

        void Register()
        {
            OnHit += SpellHitFn(spell_rog_internal_bleeding_damage_SpellScript::HandleOnHit);
            AfterHit += SpellHitFn(spell_rog_internal_bleeding_damage_SpellScript::HandleAfterHit);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_rog_internal_bleeding_damage_SpellScript();
    }
};

// 185422 - Shadow Dance Aura
class aura_rog_shadow_dance : public AuraScript
{
	PrepareAuraScript(aura_rog_shadow_dance);

	void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
	{
		if (Unit* caster = GetCaster())
			caster->RemoveAura(SPELL_ROGUE_STEALTH_BAR);
	}

	void Register() override
	{
		OnEffectRemove += AuraEffectRemoveFn(aura_rog_shadow_dance::HandleRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
	}
};

// 14190 - Seal Fate
class aura_rog_seal_fate : public AuraScript
{
	PrepareAuraScript(aura_rog_seal_fate);

	bool CheckProc(ProcEventInfo& eventInfo)
	{
        if (!eventInfo.GetProcSpell())
            return false;

        if (!(eventInfo.GetHitMask() & PROC_HIT_CRITICAL))
            return false;

        return eventInfo.GetProcSpell()->GetUsedComboPoints() > 0;
	}

	void Register() override
	{
		DoCheckProc += AuraCheckProcFn(aura_rog_seal_fate::CheckProc);
	}
};

// 193640 - Elaborate Planning
class aura_rog_elaborate_planning : public AuraScript
{
	PrepareAuraScript(aura_rog_elaborate_planning);

	bool CheckProc(ProcEventInfo& eventInfo)
	{
        if (!eventInfo.GetSpellInfo())
            return false;

        switch (eventInfo.GetSpellInfo()->Id)
        {
            case SPELL_ROGUE_ENVENOM:
            case SPELL_ROGUE_RUPTURE:
            case SPELL_ROGUE_KIDNEY_SHOT:
            case SPELL_ROGUE_CRIMSON_TEMPEST:
            case SPELL_ROGUE_BLINDSIDE:
                return true;
            default:
                return false;
        }
	}

	void Register() override
	{
		DoCheckProc += AuraCheckProcFn(aura_rog_elaborate_planning::CheckProc);
	}
};

// 1329 - Mutilate
class spell_rog_mutilate : public SpellScript
{
	PrepareSpellScript(spell_rog_mutilate);

	bool Validate(SpellInfo const* /*spellInfo*/) override
	{
		return ValidateSpellInfo({ SPELL_ROGUE_BLINDSIDE, SPELL_ROGUE_BLINDSIDE_AURA });
	}

	void HandleHit()
	{
		Unit* caster = GetCaster();
		Unit* target = GetHitUnit();
		if (!caster || !target)
			return;

		if (caster->HasSpell(SPELL_ROGUE_BLINDSIDE) && roll_chance_i(sSpellMgr->GetSpellInfo(SPELL_ROGUE_BLINDSIDE)->GetEffect(EFFECT_4).BasePoints))
			caster->CastSpell(caster, SPELL_ROGUE_BLINDSIDE_AURA, true);

        // Venom Rush
        if (Aura* aura = caster->GetAura(SPELL_ROGUE_VENOM_RUSH))
            if (target->HasAura(SPELL_ROGUE_DEADLY_POISON_DOT, caster->GetGUID()) || target->HasAura(SPELL_ROGUE_WOUND_POISON_DOT, caster->GetGUID()) ||
                target->HasAura(SPELL_ROGUE_CRIPPLING_POISON_DEBUFF, caster->GetGUID()))
                caster->CastSpell(caster, SPELL_ROGUE_VENOM_RUSH_ENERGIZE, true);
	}

	void Register() override
	{
		OnHit += SpellHitFn(spell_rog_mutilate::HandleHit);
	}
};

// 280716 - Leeching Poison
class aura_rog_leeching_poison : public AuraScript
{
	PrepareAuraScript(aura_rog_leeching_poison);

	void HandleApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
	{
        if (Unit* caster = GetCaster())
            if (caster->HasAura(SPELL_ROGUE_DEADLY_POISON) || caster->HasAura(SPELL_ROGUE_WOUND_POISON))
                caster->CastSpell(caster, LeechingPoisonAura, true);
	}

	void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
	{
        if (Unit* caster = GetCaster())
            if (caster->HasAura(SPELL_ROGUE_DEADLY_POISON) || caster->HasAura(SPELL_ROGUE_WOUND_POISON))
                caster->RemoveAurasDueToSpell(LeechingPoisonAura);
	}

	void Register() override
	{
		OnEffectApply += AuraEffectApplyFn(aura_rog_leeching_poison::HandleApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
		OnEffectRemove += AuraEffectRemoveFn(aura_rog_leeching_poison::HandleRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
	}
};

// 2823 - Deadly Poison
class aura_rog_deadly_poison : public AuraScript
{
	PrepareAuraScript(aura_rog_deadly_poison);

	void HandleApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
	{
		if (Unit* caster = GetCaster())
		{
			if (caster->HasAura(SPELL_ROGUE_WOUND_POISON))
				caster->RemoveAura(SPELL_ROGUE_WOUND_POISON);
			if (caster->HasAura(SPELL_ROGUE_LEECH_POISON_TALENT))
                caster->CastSpell(caster, LeechingPoisonAura, true);
            if (auto target = GetUnitOwner())
                Rogue::HandleGrudgeMatch(caster, target, SPELL_ROGUE_DEADLY_POISON_DOT);
		}
	}

	void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
	{
        if (Unit* caster = GetCaster())
            caster->RemoveAurasDueToSpell(LeechingPoisonAura);
	}

	void Register() override
	{
		OnEffectApply += AuraEffectApplyFn(aura_rog_deadly_poison::HandleApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
		OnEffectRemove += AuraEffectRemoveFn(aura_rog_deadly_poison::HandleRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
	}
};

// 8679 - Wound Poison
class aura_rog_wound_poison : public AuraScript
{
	PrepareAuraScript(aura_rog_wound_poison);

	void HandleApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
	{
		if (Unit* caster = GetCaster())
		{
			if (caster->HasAura(SPELL_ROGUE_DEADLY_POISON))
				caster->RemoveAura(SPELL_ROGUE_DEADLY_POISON);
			if (caster->HasAura(SPELL_ROGUE_LEECH_POISON_TALENT))
                caster->CastSpell(caster, LeechingPoisonAura, true);
		}
	}

	void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
	{
		if (Unit* caster = GetCaster())
            caster->RemoveAurasDueToSpell(LeechingPoisonAura);
	}

	void Register() override
	{
		OnEffectApply += AuraEffectApplyFn(aura_rog_wound_poison::HandleApply, EFFECT_0, SPELL_AURA_PROC_TRIGGER_SPELL, AURA_EFFECT_HANDLE_REAL);
		OnEffectRemove += AuraEffectRemoveFn(aura_rog_wound_poison::HandleRemove, EFFECT_0, SPELL_AURA_PROC_TRIGGER_SPELL, AURA_EFFECT_HANDLE_REAL);
	}
};

// 121411 - Crimson Tempest
class spell_rog_cimson_tempest :public SpellScript
{
	PrepareSpellScript(spell_rog_cimson_tempest);


	void HandleHit(SpellEffIndex effIndex)
	{
		SetHitDamage(GetHitDamage() * (GetSpell()->GetUsedComboPoints() + 1));
	}

	void HandleAfterHit()
	{
        if (Unit* target = GetHitUnit())
        {
			if (Aura* aura = target->GetAura(SPELL_ROGUE_CRIMSON_TEMPEST, GetCaster()->GetGUID()))
            {
                Rogue::HandleGrudgeMatch(GetCaster(), target, aura);
            }
        }
	}

	void Register() override
	{
		OnEffectHitTarget += SpellEffectFn(spell_rog_cimson_tempest::HandleHit, EFFECT_1, SPELL_EFFECT_SCHOOL_DAMAGE);
		AfterHit += SpellHitFn(spell_rog_cimson_tempest::HandleAfterHit);
	}
};

// 121471 - Shadow Blades
class aura_rog_shadow_blades : public AuraScript
{
    PrepareAuraScript(aura_rog_shadow_blades);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_ROGUE_SHADOW_BLADES });
    }

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetProcSpell())
            return false;

        switch (eventInfo.GetSpellInfo()->Id)
        {
            case 1329  : ///< - Mutilate
            case 5374  : ///< - Mutilate
            case 1776  : ///< - Gouge
            case 1833  : ///< - Cheap Shot
            case 8676  : ///< - Ambush
            case 30998 : ///< - Cheap Shot(SERVERSIDE)
            case 34242 : ///< - Cheap Shot(SERVERSIDE)
            case 107079: ///< - Quaking Palm(Racial)
            case 114014: ///< - Shuriken Toss
            case 131511: ///< - Prey on the Weak
            case 185438: ///< - Shadowstrike
            case 185565: ///< - Poisoned Knife
            case 185763: ///< - Pistol Shot
            case 193315: ///< - Sinister Strike
            case 194429: ///< - Ambush
            case 197834: ///< - Sinister Strike
            case 200758: ///< - Gloomblade
            case 255909: ///< - Prey on the Weak
            case 291354: ///< - Mutilate
            case 323654: ///< - Flagellation(Venthyr)
            case 341541: ///< - Sinister Strike
            case 345121: ///< - Shadowstrike
            case 53:     ///< - Backstab
            case 703:    ///< - Garrote
            case 5938:   ///< - Shiv
            case 291356: ///< - Backstab
            case 323547: ///< - Echoing Reprimand(Kyrian)
            case 323558: ///< - Echoing Reprimand(Kyrian)
            case 323559: ///< - Echoing Reprimand(Kyrian)
            case 323560: ///< - Echoing Reprimand(Kyrian)
            case 354835: ///< - Echoing Reprimand(Kyrian)
            case 354838: ///< - Echoing Reprimand(Kyrian)
            case 234278: ///< - Fan of Knives
            case 51723:  ///< - Fan of Knives
                return true;
            default:
                return eventInfo.GetProcSpell()->m_comboPointsEnergized;
        }
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();
        Unit* target = eventInfo.GetActionTarget();
        if (!caster || !target)
            return;

        auto damage = 500;

        if (eventInfo.GetDamageInfo() && eventInfo.GetDamageInfo()->GetDamage() > 0)
            damage = eventInfo.GetDamageInfo()->GetDamage();

        int32 damageAmount = CalculatePct(damage, sSpellMgr->GetSpellInfo(SPELL_ROGUE_SHADOW_BLADES)->GetEffect(EFFECT_0).BasePoints);
        caster->CastSpell(target, SPELL_ROGUE_SHADOW_BLADE, CastSpellExtraArgs(true).AddSpellBP0(damageAmount));
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_rog_shadow_blades::CheckProc);
        OnProc += AuraProcFn(aura_rog_shadow_blades::HandleProc);
    }
};

// 280719 Secret Technique
class spell_rog_secret_technique : public SpellScript
{
    PrepareSpellScript(spell_rog_secret_technique);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_ROGUE_SECRET_TECHNIQUE });
    }

    void HandleTakePower(SpellPowerCost& powerCost)
    {
        if (powerCost.Power == POWER_COMBO_POINTS)
        {
            if (Spell* spell = GetSpell())
            {
                if (SpellPowerCost const* cost = spell->GetPowerCost(POWER_COMBO_POINTS))
                {
                    m_ComboPoints = cost->Amount;
                }
            }
        }
    }

    void HandleAfterCast()
    {
        if (Unit* caster = GetCaster())
        {
            if (SpellHistory* spellHistory = caster->GetSpellHistory())
            {
                if (spellHistory->HasCooldown(SPELL_ROGUE_SECRET_TECHNIQUE))
                {
                    if (SpellInfo const* spellInfo = GetSpellInfo())
                    {
                        spellHistory->ModifyCooldown(SPELL_ROGUE_SECRET_TECHNIQUE, spellInfo->GetEffect(EFFECT_4).BasePoints * m_ComboPoints * (-1) * IN_MILLISECONDS);
                    }
                }
            }
        }
    }

    void Register() override
    {
        OnTakePower += SpellOnTakePowerFn(spell_rog_secret_technique::HandleTakePower);
        AfterCast += SpellCastFn(spell_rog_secret_technique::HandleAfterCast);
    }

private:
    int32 m_ComboPoints = 0;
};

// 185565 - Poison Knife
class spell_rog_poison_knife : public SpellScript
{
	PrepareSpellScript(spell_rog_poison_knife);

	void HandleEffectHit(SpellEffIndex /*effIndex*/)
	{
		Unit* caster = GetCaster();
		Unit* target = GetHitUnit();
		if (!caster || !target)
			return;

		if (caster->HasAura(SPELL_ROGUE_DEADLY_POISON))
			caster->CastSpell(target, SPELL_ROGUE_DEADLY_POISON_DOT, true);
        if (caster->HasAura(SPELL_ROGUE_CRIPPLING_POISON))
			caster->CastSpell(target, SPELL_ROGUE_CRIPPLING_POISON_DEBUFF, true);
		if (caster->HasAura(SPELL_ROGUE_WOUND_POISON))
			caster->CastSpell(target, SPELL_ROGUE_WOUND_POISON_DOT, true);
	}

	void Register() override
	{
		OnEffectHitTarget += SpellEffectFn(spell_rog_poison_knife::HandleEffectHit, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
	}
};

// 207777 - Dismantle
class spell_rog_dismantle : public SpellScript
{
	PrepareSpellScript(spell_rog_dismantle);

	void HandleAfterHit()
	{
		Unit* caster = GetCaster();
		Unit* target = GetHitUnit();
		if (!caster || !target)
			return;

		// Prey on the Weak
		if (caster->HasAura(SPELL_ROGUE_PREY_ON_THE_WEAK))
			caster->CastSpell(target, SPELL_ROGUE_PREY_ON_THE_WEAK_DEBUFF, true);
	}

	void Register() override
	{
		AfterHit += SpellHitFn(spell_rog_dismantle::HandleAfterHit);
	}
};

// 1833 - Cheap Shot
class spell_rog_cheap_shot : public SpellScript
{
	PrepareSpellScript(spell_rog_cheap_shot);

	bool Validate(SpellInfo const* /*spellInfo*/) override
	{
		return ValidateSpellInfo({ SPELL_ROGUE_COLD_BLOOD_DAMAGE });
	}

	void HandleAfterHit()
	{
		Unit* caster = GetCaster();
		Unit* target = GetHitUnit();
		if (!caster || !target)
			return;

		// Prey on the Weak
		if (caster->HasAura(SPELL_ROGUE_PREY_ON_THE_WEAK))
			caster->CastSpell(target, SPELL_ROGUE_PREY_ON_THE_WEAK_DEBUFF, true);

		// Cold Blood
		if (caster->HasAura(SPELL_ROGUE_COLD_BLOOD))
		{
            caster->CastSpell(target, SPELL_ROGUE_COLD_BLOOD_DAMAGE, true); 
			caster->RemoveAurasDueToSpell(SPELL_ROGUE_COLD_BLOOD);
	}
	}

	void HandleAfterCast()
	{
		if (Unit* caster = GetCaster())
			caster->RemoveAurasDueToSpell(SPELL_ROGUE_SHOT_IN_THE_DARK_BUFF);
	}

	void Register() override
	{
		AfterHit += SpellHitFn(spell_rog_cheap_shot::HandleAfterHit);
		AfterCast += SpellCastFn(spell_rog_cheap_shot::HandleAfterCast);
	}
};

// 36554 - Shadowstep
class spell_rog_shadowstep : public SpellScript
{
	PrepareSpellScript(spell_rog_shadowstep);

	bool Validate(SpellInfo const* /*spellInfo*/) override
	{
		return ValidateSpellInfo({ SPELL_ROGUE_INTENT_TO_KILL });
	}

	void HandleHitTarget(SpellEffIndex /*effIndex*/)
	{
		Unit* caster = GetCaster();
		Unit* target = GetExplTargetUnit();
		if (!caster || !target)
			return;

		if (caster->HasAura(SPELL_ROGUE_INTENT_TO_KILL) && target->HasAura(SPELL_ROGUE_VENDETTA, caster->GetGUID()))
			caster->GetSpellHistory()->ReduceChargeCooldown(sSpellMgr->GetSpellInfo(SPELL_ROGUE_SHADOWSTEP)->ChargeCategoryId, CalculatePct(30, sSpellMgr->GetSpellInfo(SPELL_ROGUE_INTENT_TO_KILL)->GetEffect(EFFECT_0).BasePoints) * IN_MILLISECONDS);
	}

	void Register() override
	{
		OnEffectHitTarget += SpellEffectFn(spell_rog_shadowstep::HandleHitTarget, EFFECT_0, SPELL_EFFECT_TRIGGER_SPELL);
	}
};

// 198097 - Creeping Venom
class aura_rog_creeping_venom : public AuraScript
{
	PrepareAuraScript(aura_rog_creeping_venom);

	void HandlePeriodic(AuraEffect const* /*aurEff*/)
	{
		Unit* owner = GetUnitOwner();
		Unit* caster = GetCaster();
		if (!caster || !owner)
			return;

		if (owner->Variables.Exist("LAST_POSITION") && owner->Variables.GetValue<Position>("LAST_POSITION") != owner->GetPosition())
			if (Aura* aura = owner->GetAura(SPELL_ROGUE_CREEPING_VENOM_AURA, caster->GetGUID()))
			{
				aura->RefreshDuration();
				owner->Variables.Set<Position>("LAST_POSITION", owner->GetPosition());
			}
	}

	void HandleApply(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /* mode */)
	{
		if (Unit* owner = GetUnitOwner())
			owner->Variables.Set<Position>("LAST_POSITION", owner->GetPosition());
	}

	void Register() override
	{
		OnEffectApply += AuraEffectApplyFn(aura_rog_creeping_venom::HandleApply, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
		OnEffectPeriodic += AuraEffectPeriodicFn(aura_rog_creeping_venom::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE);
	}
};

// 197051 - Mind-Numbing Poison
class aura_mind_numbing_poison : public AuraScript
{
	PrepareAuraScript(aura_mind_numbing_poison);

	void HandleProc(ProcEventInfo& eventInfo)
	{
		Unit* caster = GetCaster();
		Unit* target = eventInfo.GetActionTarget();
		if (!caster || !target)
			return;

		caster->CastSpell(target, SPELL_ROGUE_MIND_NUMBING_POISON_DAMAGE, true);

	}

	void Register() override
	{
		OnProc += AuraProcFn(aura_mind_numbing_poison::HandleProc);
	}
};

// 6951 - Smoke Bomb
//Last Update 8.0.1 Build 28153
struct at_rog_smoke_bomb : AreaTriggerAI
{
    at_rog_smoke_bomb(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger) { }

	void OnUnitEnter(Unit* unit) override
	{
		if (Unit* caster = at->GetCaster())
            caster->CastSpell(unit, SPELL_ROGUE_SMOKE_BOMB_AURA, true);
	}

	void OnUnitExit(Unit* unit) override
	{
		if (Unit* caster = at->GetCaster())
			if (unit && unit->HasAura(SPELL_ROGUE_SMOKE_BOMB_AURA, caster->GetGUID()))
				unit->RemoveAura(SPELL_ROGUE_SMOKE_BOMB_AURA, caster->GetGUID());
	}
};

// 212217 - Control is King
// AT - 6952
//Last Update 8.0.1 Build 28153
struct at_rog_control_is_king : AreaTriggerAI
{
    at_rog_control_is_king(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger) { }

    void OnInitialize() override
    {
        // How often should the action be executed
        at->SetPeriodicProcTimer(1000);
    }

    void OnUnitEnter(Unit* unit) override
    {
        if (Unit* caster = at->GetCaster())
            if (unit && unit->ToPlayer() && caster->IsValidAttackTarget(unit))
                if (!unit->HasAura(SPELL_ROGUE_CONTROL_IS_KING_EFFECT, caster->GetGUID()))
                    caster->CastSpell(unit, SPELL_ROGUE_CONTROL_IS_KING_EFFECT, true);
    }

    void OnPeriodicProc() override
    {
        if (Unit* caster = at->GetCaster())
        {
            GuidUnorderedSet list = at->GetInsideUnits();
            if (!list.empty())
            {
                for (ObjectGuid guid : list)
                {
                    Unit* unit = ObjectAccessor::GetUnit(*caster, guid);
                    if (!unit->ToPlayer())
                        continue;

                    if (!unit->HasAura(SPELL_ROGUE_CONTROL_IS_KING_EFFECT, caster->GetGUID()) && caster->IsValidAttackTarget(unit))
                        caster->AddAura(SPELL_ROGUE_CONTROL_IS_KING_EFFECT, unit);
                }
            }
        }
    }

    void OnUnitExit(Unit* unit) override
    {
        if (Unit* caster = at->GetCaster())
            if (unit && unit->HasAura(SPELL_ROGUE_CONTROL_IS_KING_EFFECT, caster->GetGUID()))
                unit->RemoveAura(SPELL_ROGUE_CONTROL_IS_KING_EFFECT, caster->GetGUID());
    }
};

// 212219 Control is King
//Last Update 8.0.1 Build 28153
class aura_rog_control_is_king_effect : public AuraScript
{
    PrepareAuraScript(aura_rog_control_is_king_effect);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();
        if (!caster)
            return false;

        Unit* target = GetTarget();
        if (!target || caster->IsFriendlyTo(target))
            return false;

        if (caster->GetGUID() != eventInfo.GetActor()->GetGUID())
            return false;

        Aura* aura = caster->GetAura(SPELL_ROGUE_CONTROL_IS_KING, caster->GetGUID());
        if (!aura)
            return false;

        DamageInfo* damageInfo = eventInfo.GetDamageInfo();
        if (!damageInfo)
            return false;

        SpellInfo const* spellInfo = damageInfo->GetSpellInfo();
        if (!spellInfo)
            return false;

        bool match = false;

        // Check global spell mechanic first
        switch (spellInfo->Mechanic)
        {
        case Mechanics::MECHANIC_SILENCE:
        case Mechanics::MECHANIC_POLYMORPH:
        case Mechanics::MECHANIC_STUN:
            match = true;
            break;
        }

        // Then check effect mechanic if needed
        if (!match)
        {
            for (SpellEffectInfo const& effect : spellInfo->GetEffects())
            {
                switch (effect.Mechanic)
                {
                case Mechanics::MECHANIC_SILENCE:
                case Mechanics::MECHANIC_POLYMORPH:
                case Mechanics::MECHANIC_STUN:
                    match = true;
                    break;
                default:
                    break;
                }
            }
        }

        if (!match)
            return false;

        uint32 duration = 0;
        if (!caster->HasAura(SPELL_ROGUE_ADRENALINE_RUSH))
            caster->AddAura(SPELL_ROGUE_ADRENALINE_RUSH, caster);
        else
            duration = caster->GetAura(SPELL_ROGUE_ADRENALINE_RUSH)->GetDuration();

        //This never gonna happens
        Aura* auraAdrenaline = caster->GetAura(SPELL_ROGUE_ADRENALINE_RUSH);
        if (!auraAdrenaline)
            return false;

        SpellInfo const* controlIsKing = aura->GetSpellInfo();
        if (controlIsKing)
        {
            auraAdrenaline->SetDuration(duration + controlIsKing->GetEffect(EFFECT_1).BasePoints * IN_MILLISECONDS);
            auraAdrenaline->SetMaxDuration(duration + controlIsKing->GetEffect(EFFECT_1).BasePoints * IN_MILLISECONDS);
        }

        return false;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_rog_control_is_king_effect::CheckProc);
    }
};

// 198675 - Dagger in the Dark
class aura_dagger_in_the_dark : public AuraScript
{
	PrepareAuraScript(aura_dagger_in_the_dark);

	void HandlePeriodic(AuraEffect const* aurEff)
	{
		if (Unit* caster = GetCaster())
			if (caster->HasAura(SPELL_ROGUE_STEALTH))
				caster->CastSpell(caster, SPELL_ROGUE_DAGGER_IN_THE_DARK_DEBUFF, true);
	}

	void Register() override
	{
		OnEffectPeriodic += AuraEffectPeriodicFn(aura_dagger_in_the_dark::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
	}
};

// 198688 - Dagger in the Dark Debuff
class aura_dagger_in_the_dark_debuff : public AuraScript
{
	PrepareAuraScript(aura_dagger_in_the_dark_debuff);

	bool CheckProc(ProcEventInfo& eventInfo)
	{
		if (eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == SPELL_ROGUE_SHADOWSTRIKE)
			return true;

		return false;
	}

	void Register() override
	{
		DoCheckProc += AuraCheckProcFn(aura_dagger_in_the_dark_debuff::CheckProc);
	}
};

// 213981 - Cold Blood
class aura_rog_cold_blood : public AuraScript
{
	PrepareAuraScript(aura_rog_cold_blood);

	bool CheckProc(ProcEventInfo& eventInfo)
	{
		return false;
	}

	void Register() override
	{
		DoCheckProc += AuraCheckProcFn(aura_rog_cold_blood::CheckProc);
	}
};

// 2983 - Sprint
class spell_rog_sprint : public SpellScript
{
	PrepareSpellScript(spell_rog_sprint);

	void HandleHit()
	{
		if (Unit* caster = GetCaster())
			if (caster->HasAura(SPELL_ROGUE_MANEUVERABILITY))
				caster->CastSpell(caster, SPELL_ROGUE_MANEUVERABILITY_BUFF, true);
	}

	void Register() override
	{
		OnHit += SpellHitFn(spell_rog_sprint::HandleHit);
	}
};

// 5938 - Shiv
class spell_rog_shiv : public SpellScript
{
	PrepareSpellScript(spell_rog_shiv);

    enum Shiv
    {
        ShivAssaDebuff = 319504,
        GrudgeMatch = 364667,
        GrudgeMatchProc = 364668,
    };

	void OnHitTarget(SpellEffIndex /*index*/)
	{
        if (auto caster = GetCaster())
            if (auto player = caster->ToPlayer())
            {
                if (player->GetSpecializationId() == TALENT_SPEC_ROGUE_ASSASSINATION)
                {
                    if (auto target = GetHitUnit())
                    {
                        GetCaster()->CastSpell(target, ShivAssaDebuff, true);
                        std::list<Unit*> attackableUnitsInRange;
                        caster->GetAttackableUnitListInRange(attackableUnitsInRange, 15.0f);
                        for (auto unit : attackableUnitsInRange)
                        {
                            caster->CastSpell(unit, 364668, true);
                        }
                    }
                }
            }

	}

	void Register() override
	{
        OnEffectHitTarget += SpellEffectFn(spell_rog_shiv::OnHitTarget, EFFECT_1, SPELL_EFFECT_DUMMY);
	}
};

// 198265 - Take Your Cut
class aura_rog_take_your_cut : public AuraScript
{
	PrepareAuraScript(aura_rog_take_your_cut);

	bool CheckProc(ProcEventInfo& eventInfo)
	{
		if (eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == SPELL_ROGUE_ROLL_THE_BONES)
			return true;

		return false;
	}

	void Register() override
	{
		DoCheckProc += AuraCheckProcFn(aura_rog_take_your_cut::CheckProc);
	}
};

// 209752 - Boarding Party
class aura_rog_boarding_party : public AuraScript
{
	PrepareAuraScript(aura_rog_boarding_party);

	bool CheckProc(ProcEventInfo& eventInfo)
	{
		if (eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == SPELL_ROGUE_BETWEEN_THE_EYES)
			return true;

		return false;
	}

	void Register() override
	{
		DoCheckProc += AuraCheckProcFn(aura_rog_boarding_party::CheckProc);
	}
};

// 209754 - Boarding Party Bonus
class spell_rog_boarding_party_bonus : public SpellScript
{
	PrepareSpellScript(spell_rog_boarding_party_bonus);

	void HandleOnObjectAreaTargetSelect(std::list<WorldObject*>& targets)
	{
		if (Unit* caster = GetCaster())
		{
			targets.remove_if([caster](WorldObject* target)
			{
				if (!target->ToPlayer())
					return true;

				if (!caster->ToPlayer()->IsInSameGroupWith(target->ToPlayer()) && !caster->ToPlayer()->IsInSameRaidWith(target->ToPlayer()))
					return true;

				return false;
			});
		}
	}

	void Register() override
	{
		OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_rog_boarding_party_bonus::HandleOnObjectAreaTargetSelect, EFFECT_0, TARGET_UNIT_SRC_AREA_ALLY);
	}
};

// 257506 - Shot in the Dark Buff
class aura_shot_in_the_dark_buff : public AuraScript
{
	PrepareAuraScript(aura_shot_in_the_dark_buff);

	bool CheckProc(ProcEventInfo& eventInfo)
	{
		return false;
	}

	void Register() override
	{
		DoCheckProc += AuraCheckProcFn(aura_shot_in_the_dark_buff::CheckProc);
	}
};

// 277925 - Shuriken Tornado
class aura_rog_shuriken_tornado : public AuraScript
{
    PrepareAuraScript(aura_rog_shuriken_tornado);

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
        if (Unit* caster = GetCaster())
            caster->CastSpell(caster, SPELL_ROGUE_SHURIKEN_STORM, true);
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(aura_rog_shuriken_tornado::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
    }
};

// 2094 / 199743 - Blind / Parley
class aura_rog_blind : public AuraScript
{
    PrepareAuraScript(aura_rog_blind);

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (GetTargetApplication()->GetRemoveMode() == AURA_REMOVE_BY_DEATH)
            return;

        Unit* caster = GetCaster();
        Unit* target = GetTarget();
        if (!caster || !target)
            return;

        if (caster->HasAura(SPELL_ROGUE_CHEAP_TRICK))
            caster->CastSpell(target, SPELL_ROGUE_CHEAP_TRICK_MISS, true);
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (Unit* owner = GetTarget())
            owner->RemoveAura(SPELL_ROGUE_BLIND);
    }

    void Register() override
    {
        OnProc += AuraProcFn(aura_rog_blind::HandleProc);
        OnEffectRemove += AuraEffectRemoveFn(aura_rog_blind::HandleRemove, EFFECT_0, SPELL_AURA_MOD_DECREASE_SPEED, AURA_EFFECT_HANDLE_REAL);
    }
};

// 212035 - Cheap Tricks
class aura_rog_cheap_tricks : public AuraScript
{
    PrepareAuraScript(aura_rog_cheap_tricks);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == SPELL_ROGUE_BETWEEN_THE_EYES)
            return true;

        return false;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_rog_cheap_tricks::CheckProc);
    }
};

// 58423 - Relentless Strikes
class aura_rog_relentless_strikes : public AuraScript
{
    PrepareAuraScript(aura_rog_relentless_strikes);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (auto procSpell = eventInfo.GetProcSpell())
            return procSpell->GetUsedComboPoints();

        return false;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (Unit* caster = GetCaster())
            if (auto procSpell = eventInfo.GetProcSpell())
                if (auto comboPoints = procSpell->GetUsedComboPoints())
                    caster->CastSpell(caster, SPELL_ROGUE_RELENTLESS_STRIKES_POWER, CastSpellExtraArgs(true).AddSpellBP0(6 * comboPoints));
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_rog_relentless_strikes::CheckProc);
        OnProc += AuraProcFn(aura_rog_relentless_strikes::HandleProc);
    }
};

// 91023 - Find Weakness
class aura_rog_find_weakness : public AuraScript
{
    PrepareAuraScript(aura_rog_find_weakness);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetSpellInfo() && (eventInfo.GetSpellInfo()->Id == SPELL_ROGUE_SHADOWSTRIKE || eventInfo.GetSpellInfo()->Id == SPELL_ROGUE_CHEAP_SHOOT || eventInfo.GetSpellInfo()->Id == SPELL_ROGUE_SHURIKEN_STORM || eventInfo.GetSpellInfo()->Id == SPELL_ROGUE_BACKSTAB))
            return true;

        return false;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_rog_find_weakness::CheckProc);
    }
};

// Last Update 8.0.1 Build 28153
// Death from Above (Jump to target) - 156327, 178236 
class spell_rog_death_from_above_return : public SpellScriptLoader
{
public:
    spell_rog_death_from_above_return() : SpellScriptLoader("spell_rog_death_from_above_return") { }

    class spell_rog_death_from_above_return_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_rog_death_from_above_return_SpellScript);

        void ChangeJumpDestination(SpellEffIndex effIndex)
        {
            if (Unit* caster = GetCaster())
            {
                PreventHitDefaultEffect(effIndex);

                SpellInfo const* spellInfo = GetSpellInfo();
                if (Unit* target = GetExplTargetUnit())
                {
                    if (spellInfo->Id == SPELL_ROGUE_DEATH_FROM_ABOVE_FINAL_JUMP)
                    {
                        float orientation = target->GetAngle(caster);
                        float contact = target->GetObjectScale() + CONTACT_DISTANCE;
                        float x = target->GetPositionX() + (contact * cos(orientation));
                        float y = target->GetPositionY() + (contact * sin(orientation));
                        float z = target->GetPositionZ();

                        orientation += float(M_PI);

                        float speedXY, speedZ;

                        if (spellInfo->GetEffect(effIndex).MiscValue)
                            speedZ = float(spellInfo->GetEffect(effIndex).MiscValue) / 10;
                        else if (spellInfo->GetEffect(effIndex).MiscValueB)
                            speedZ = float(spellInfo->GetEffect(effIndex).MiscValueB) / 10;
                        else
                            speedZ = 10.0f;

                        if (spellInfo->GetEffect(effIndex).Amplitude)
                            speedXY = spellInfo->GetEffect(effIndex).Amplitude;
                        else
                            speedXY = caster->GetExactDist2d(x, y) * 10.0f / speedZ;

                        uint32 spellID = 0;

                        if (Player* player = caster->ToPlayer())
                        {
                            switch (player->GetSpecializationId())
                            {
                            case TALENT_SPEC_ROGUE_SUBTLETY:
                                spellID = SPELL_ROGUE_EVISCERATE;
                                break;
                            case TALENT_SPEC_ROGUE_COMBAT:
                                spellID = SPELL_ROGUE_RUN_THROUGH; 
                                break;
                            case TALENT_SPEC_ROGUE_ASSASSINATION:
                                spellID = SPELL_ROGUE_ENVENOM;
                                break;
                            }
                        }

                        JumpArrivalCastArgs arrivalCast;
                        arrivalCast.SpellId = spellID;
                        arrivalCast.Target = target->GetGUID();
                        //arrivalCast.Caster = caster->GetGUID();
                        caster->GetMotionMaster()->MoveJump(x, y, z, orientation, speedXY, speedZ, spellInfo->Id, false, &arrivalCast);
                    }
                }

                if (spellInfo->Id == SPELL_ROGUE_DEATH_FROM_ABOVE_INITIAL_JUMP)
                {
                    float x = caster->GetPositionX();
                    float y = caster->GetPositionY();
                    float z = caster->GetPositionZ() + 10.0f;


                    float speedXY, speedZ;

                    if (spellInfo->GetEffect(effIndex).MiscValue)
                        speedZ = float(spellInfo->GetEffect(effIndex).MiscValue) / 10;
                    else if (spellInfo->GetEffect(effIndex).MiscValueB)
                        speedZ = float(spellInfo->GetEffect(effIndex).MiscValueB) / 10;
                    else
                        speedZ = 10.0f;

                    if (spellInfo->GetEffect(effIndex).Amplitude)
                        speedXY = spellInfo->GetEffect(effIndex).Amplitude;
                    else
                        speedXY = caster->GetExactDist2d(x, y) * 10.0f / speedZ;

                    caster->GetMotionMaster()->MoveJump(x, y, z, caster->GetOrientation(), speedXY, speedZ, spellInfo->Id);
                }
            }
        }

        void Register()
        {
            if (m_scriptSpellId == SPELL_ROGUE_DEATH_FROM_ABOVE_FINAL_JUMP)
                OnEffectLaunch += SpellEffectFn(spell_rog_death_from_above_return_SpellScript::ChangeJumpDestination, EFFECT_1, SPELL_EFFECT_JUMP);
            else
                OnEffectLaunch += SpellEffectFn(spell_rog_death_from_above_return_SpellScript::ChangeJumpDestination, EFFECT_0, SPELL_EFFECT_JUMP_DEST);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_rog_death_from_above_return_SpellScript();
    }
};

// Last Update 8.0.1 Build 28153
// Death from Above - 269513
class spell_rog_death_from_above : public SpellScriptLoader
{
public:
    spell_rog_death_from_above() : SpellScriptLoader("spell_rog_death_from_above") { }

    class spell_rog_death_from_above_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_rog_death_from_above_SpellScript);

        SpellCastResult CheckCast()
        {
            Unit* caster = GetCaster();
            Unit* target = GetExplTargetUnit();


            if (target == nullptr)
                return SPELL_FAILED_BAD_IMPLICIT_TARGETS;

            if (!caster->IsWithinLOSInMap(target))
                return SPELL_FAILED_LINE_OF_SIGHT;

            caster->Variables.Set<uint8>("DFA_ComboPoints", caster->GetPower(POWER_COMBO_POINTS));
            caster->Variables.Set<ObjectGuid>("DFA_Target", target->GetGUID());

            return SPELL_CAST_OK;
        }

        void HandleBeforeCast()
        {
            if (Unit* caster = GetCaster())
                caster->CastSpell(caster, SPELL_ROGUE_DEATH_FROM_ABOVE_INITIAL_JUMP, true);
        }

        void HandleAfterCast()
        {
            if (Unit* caster = GetCaster())
                caster->CastSpell(caster, SPELL_ROGUE_DEATH_FROM_ABOVE_BONUS, true);
        }

        void Register()
        {
            OnCheckCast += SpellCheckCastFn(spell_rog_death_from_above_SpellScript::CheckCast);
            BeforeCast += SpellCastFn(spell_rog_death_from_above_SpellScript::HandleBeforeCast);
            AfterCast += SpellCastFn(spell_rog_death_from_above_SpellScript::HandleAfterCast);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_rog_death_from_above_SpellScript();
    }

    class spell_rog_death_from_above_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_rog_death_from_above_AuraScript);

        void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if (Unit* target = GetTarget())
            {
                target->ApplySpellImmune(GetId(), IMMUNITY_MECHANIC, MECHANIC_SNARE, true);
                target->ApplySpellImmune(GetId(), IMMUNITY_MECHANIC, MECHANIC_ROOT, true);
                target->ApplySpellImmune(GetId(), IMMUNITY_MECHANIC, MECHANIC_FEAR, true);
                target->ApplySpellImmune(GetId(), IMMUNITY_MECHANIC, MECHANIC_STUN, true);
                target->ApplySpellImmune(GetId(), IMMUNITY_MECHANIC, MECHANIC_SLEEP, true);
                target->ApplySpellImmune(GetId(), IMMUNITY_MECHANIC, MECHANIC_CHARM, true);
                target->ApplySpellImmune(GetId(), IMMUNITY_MECHANIC, MECHANIC_SAPPED, true);
                target->ApplySpellImmune(GetId(), IMMUNITY_MECHANIC, MECHANIC_HORROR, true);
                target->ApplySpellImmune(GetId(), IMMUNITY_MECHANIC, MECHANIC_POLYMORPH, true);
                target->ApplySpellImmune(GetId(), IMMUNITY_MECHANIC, MECHANIC_DISORIENTED, true);
                target->ApplySpellImmune(GetId(), IMMUNITY_MECHANIC, MECHANIC_FREEZE, true);
                target->ApplySpellImmune(GetId(), IMMUNITY_MECHANIC, MECHANIC_TURN, true);
            }
        }

        void OnRemove(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
        {
            if (GetCaster() == nullptr)
                return;

            if (Player* player = GetCaster()->ToPlayer())
            {
                if (player->Variables.Exist("DFA_Target"))
                    if(Unit* target = ObjectAccessor::GetUnit(*player, player->Variables.GetValue<ObjectGuid>("DFA_Target")))
                        player->CastSpell(target, SPELL_ROGUE_DEATH_FROM_ABOVE_FINAL_JUMP, true);

                player->ApplySpellImmune(GetId(), IMMUNITY_MECHANIC, MECHANIC_SNARE, false);
                player->ApplySpellImmune(GetId(), IMMUNITY_MECHANIC, MECHANIC_ROOT, false);
                player->ApplySpellImmune(GetId(), IMMUNITY_MECHANIC, MECHANIC_FEAR, false);
                player->ApplySpellImmune(GetId(), IMMUNITY_MECHANIC, MECHANIC_STUN, false);
                player->ApplySpellImmune(GetId(), IMMUNITY_MECHANIC, MECHANIC_SLEEP, false);
                player->ApplySpellImmune(GetId(), IMMUNITY_MECHANIC, MECHANIC_CHARM, false);
                player->ApplySpellImmune(GetId(), IMMUNITY_MECHANIC, MECHANIC_SAPPED, false);
                player->ApplySpellImmune(GetId(), IMMUNITY_MECHANIC, MECHANIC_HORROR, false);
                player->ApplySpellImmune(GetId(), IMMUNITY_MECHANIC, MECHANIC_POLYMORPH, false);
                player->ApplySpellImmune(GetId(), IMMUNITY_MECHANIC, MECHANIC_DISORIENTED, false);
                player->ApplySpellImmune(GetId(), IMMUNITY_MECHANIC, MECHANIC_FREEZE, false);
                player->ApplySpellImmune(GetId(), IMMUNITY_MECHANIC, MECHANIC_TURN, false);
            }
        }

        void Register()
        {
            AfterEffectApply += AuraEffectApplyFn(spell_rog_death_from_above_AuraScript::OnApply, EFFECT_2, SPELL_AURA_DISABLE_CASTING_EXCEPT_ABILITIES, AURA_EFFECT_HANDLE_REAL);
            AfterEffectRemove += AuraEffectApplyFn(spell_rog_death_from_above_AuraScript::OnRemove, EFFECT_2, SPELL_AURA_DISABLE_CASTING_EXCEPT_ABILITIES, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_rog_death_from_above_AuraScript();
    }
};

// 207736 - Shadowy Duel
//Last Update 8.0.1 Build 28153
class spell_rog_shadowy_duel : public SpellScript
{
    PrepareSpellScript(spell_rog_shadowy_duel);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo
        ({
            SPELL_ROGUE_SHADOWY_DUEL_INVIS,
            SPELL_ROGUE_SHADOWY_DUEL_STALK
            });
    }

    void OnTriggerTarget(SpellEffIndex effIndex)
    {
        PreventHitEffect(effIndex);
    }

    void OnHitTarget(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        // Weird Spell Blizz, you trigger on urself with ENEMY target
        caster->CastSpell(target, SPELL_ROGUE_SHADOWY_DUEL_STALK, true);
        target->CastSpell(caster, SPELL_ROGUE_SHADOWY_DUEL_STALK, true);
        caster->CastSpell(caster, SPELL_ROGUE_SHADOWY_DUEL_INVIS, true);
        target->CastSpell(target, SPELL_ROGUE_SHADOWY_DUEL_INVIS, true);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_rog_shadowy_duel::OnTriggerTarget, EFFECT_2, SPELL_EFFECT_TRIGGER_SPELL);
        OnEffectHitTarget += SpellEffectFn(spell_rog_shadowy_duel::OnHitTarget, EFFECT_0, SPELL_EFFECT_APPLY_AURA);
    } 
};

// 270061 - Hidden Blades
class aura_rog_hidden_blades : public AuraScript
{
    PrepareAuraScript(aura_rog_hidden_blades);

    void OnTick(const AuraEffect* /*aurEff*/)
    {
        if (Unit* caster = GetCaster())
            caster->CastSpell(caster, SPELL_ROGUE_HIDDEN_BLADES_BUFF, true);
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(aura_rog_hidden_blades::OnTick, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

// 270070 - Hidden Blades Aura
class aura_rog_hidden_blades_aura : public AuraScript
{
    PrepareAuraScript(aura_rog_hidden_blades_aura);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == SPELL_ROGUE_FAN_OF_KNIVES)
            return true;

        return false;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        Remove();
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_rog_hidden_blades_aura::CheckProc);
        OnProc += AuraProcFn(aura_rog_hidden_blades_aura::HandleProc);
    }
};

// 31224 - Cloak of Shadows
//Last Update 8.0.1 Build 28153
class spell_rog_cloak_of_shadows : public SpellScript
{
    PrepareSpellScript(spell_rog_cloak_of_shadows);

    void HandleEffectLaunchTarget(SpellEffIndex effIndex)
    {
        Unit* target = GetHitUnit();
        PreventHitDefaultEffect(effIndex);

        if (AuraEffect* auraEff = target->GetAuraEffect(SPELL_ROGUE_SHROUDED_MANTLE_POWER, EFFECT_0))
            target->CastSpell(target, SPELL_ROGUE_SHROUDED_MANTLE_HOT, CastSpellExtraArgs(true).AddSpellBP0(auraEff->GetAmount()));

        uint32 dispelMask = SpellInfo::GetDispelMask(DISPEL_ALL);
        Unit::AuraApplicationMap& Auras = target->GetAppliedAuras();
        for (Unit::AuraApplicationMap::iterator itr = Auras.begin(); itr != Auras.end();)
        {
            // remove all harmful spells on you...
            SpellInfo const* spellInfo = itr->second->GetBase()->GetSpellInfo();
            if (((spellInfo->DmgClass == SPELL_DAMAGE_CLASS_MAGIC && spellInfo->GetSchoolMask() != SPELL_SCHOOL_MASK_NORMAL) // only affect magic spells
                || (spellInfo->GetDispelMask() & dispelMask)) &&
                // ignore positive and passive auras
                !itr->second->IsPositive() && !itr->second->GetBase()->IsPassive())
            {
                if (AuraEffect* auraEff = target->GetAuraEffect(SPELL_ROGUE_SHROUDED_MANTLE_POWER, EFFECT_1))
                    target->CastSpell(target, SPELL_ROGUE_SHROUDED_MANTLE_HEAL, CastSpellExtraArgs(true).AddSpellBP0(auraEff->GetAmount()));

                target->RemoveAura(itr);                
            }
            else
                ++itr;
        }
    }

    void Register() override
    {
        OnEffectLaunchTarget += SpellEffectFn(spell_rog_cloak_of_shadows::HandleEffectLaunchTarget, EFFECT_0, SPELL_EFFECT_APPLY_AURA);
    }
};

// 213983 Cold Blood
//Last Update 8.0.1 Build 28153
class spell_rog_cold_blood_damage : public SpellScript
{
    PrepareSpellScript(spell_rog_cold_blood_damage);

    void HandleHitTarget(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetOriginalCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        uint8 pct = GetSpellInfo()->GetEffect(EFFECT_1).BasePoints;
        SetHitDamage(CalculatePct(target->IsPlayer() ? target->GetMaxHealth() : caster->GetMaxHealth(), pct));
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_rog_cold_blood_damage::HandleHitTarget, EFFECT_0, SPELL_EFFECT_DAMAGE_FROM_MAX_HEALTH_PCT);
    }
};

// 245751 - Sprint Subtly
class aura_rog_sprint_subtly : public AuraScript
{
    PrepareAuraScript(aura_rog_sprint_subtly);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == SPELL_ROGUE_SPRINT)
            return true;

        return false;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_rog_sprint_subtly::CheckProc);
    }
};

// 245752 - Sprint Trigger
class aura_rog_sprint_trigger : public AuraScript
{
    PrepareAuraScript(aura_rog_sprint_trigger);

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
        if (Unit* caster = GetCaster())
            caster->CastSpell(caster, SPELL_ROGUE_WATER_WALKING, true);
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(aura_rog_sprint_trigger::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

// 6770 - Sap
class spell_rog_sap : public SpellScript
{
    PrepareSpellScript(spell_rog_sap);

    void HandleHit()
    {
        if (Unit* target = GetHitUnit())
            target->RemoveAurasByType(SPELL_AURA_MOD_STEALTH);
    }

    void Register() override
    {
        OnHit += SpellHitFn(spell_rog_sap::HandleHit);
    }
};

class spell_rog_blade_rush : public SpellScript
{
    PrepareSpellScript(spell_rog_blade_rush);

    void HandleHit(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!target || !caster)
            return;

        caster->CastSpell(target, 271878, true); // Blade Rush path
        caster->CastSpell(target, 271881, true); // Blade rush damage
        caster->CastSpell(target, 271896, true); // Regen
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_rog_blade_rush::HandleHit, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

// 324073 
class spell_rog_serrated_bone_spike : public AuraScript
{
    PrepareAuraScript(spell_rog_serrated_bone_spike);

    enum SBS
    {
        SBSDot = 328547,
        SBSMain = 324073,
    };

    ObjectGuid CasterGuid;

    void HandleApply(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /* mode */)
    {
        Unit* caster = GetCaster();
        Unit* target = GetUnitOwner();
        if (!caster || !target)
            return;

        CasterGuid = caster->GetGUID();
    }

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetUnitOwner();

        if (!target)
            return;

        if ((!caster || !caster->IsInCombatWith(target) || caster->GetDistance(target) >= 60.0f))
        {
            target->RemoveAurasDueToSpell(SBSMain, CasterGuid);
            target->RemoveAurasDueToSpell(SBSDot, CasterGuid);
            return;
        }
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_rog_serrated_bone_spike::HandleApply, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE, AURA_EFFECT_HANDLE_REAL);
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_rog_serrated_bone_spike::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE);
    }
};

// 79140
class spell_rog_vendetta : public AuraScript
{
    PrepareAuraScript(spell_rog_vendetta);

    void HandleApply(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /* mode */)
    {
        Unit* caster = GetCaster();
        Unit* target = GetUnitOwner();
        if (!caster || !target)
            return;

        if (target->HasAura(SPELL_ROGUE_VENDETTA, caster->GetGUID()))
        {
            if (caster->HasAura(SPELL_ROUGE_GRUDGE_MATCH))
            {
                static const uint32 dotAuras[] = { 703, 121411, 1943, 328305, 2818 }; ///< Garrote, Crimson Tempest, Rupture, Sepsis, Deadly Poison

                for (auto aura : dotAuras)
                {
                    if (auto dot = target->GetAura(aura, caster->GetGUID()))
                    {
                        dot->SetMaxDuration(dot->GetDuration() / 2);
                        dot->RefreshDuration();
                        for (auto eff : dot->GetAuraEffects())
                        {
                            if (eff && eff->GetAuraType() == AuraType::SPELL_AURA_PERIODIC_DAMAGE)
                            {
                                eff->IsDoublProcced = true;
                                eff->CalculatePeriodic(caster, false, false);
                            }
                        }
                    }
                }
            }
        }
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_rog_vendetta::HandleApply, EFFECT_0, SPELL_AURA_MOD_SPELL_DAMAGE_FROM_CASTER, AURA_EFFECT_HANDLE_REAL);
    }
};

/// ID: 200806 Exsanguinate
class spell_exsanguinate : public SpellScript
{
    PrepareSpellScript(spell_exsanguinate);

    void HandleDummy(SpellEffIndex /*eff*/)
    {
        if (auto caster = GetCaster())
        {
            if (auto target = GetHitUnit())
            {
                auto ExsanguinateBleed([caster, target](uint32 spellId)
                {
                    if (auto bleed = target->GetAura(spellId, caster->GetGUID()))
                    {
                        bleed->SetDuration(bleed->GetDuration() / 2);
                        for (auto eff : bleed->GetAuraEffects())
                        {
                            if (eff && eff->GetAuraType() == AuraType::SPELL_AURA_PERIODIC_DAMAGE)
                            {
                                /// CUSTOM FIX
                                eff->SetAmount(eff->GetAmount() * 2);
                                //eff->SetPeriodicTimer(eff->GetPeriodicTimer() / 2);
                            }
                        }
                        bleed->SetNeedClientUpdateForTargets();
                    }
                });

                ExsanguinateBleed(SPELL_ROGUE_INTERNAL_BLEEDING_DOT);
                ExsanguinateBleed(SPELL_ROGUE_DEADLY_POISON_DOT);
                ExsanguinateBleed(SPELL_ROGUE_GARROTE_DOT);
                ExsanguinateBleed(SPELL_ROGUE_RUPTURE_DOT);
            }
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_exsanguinate::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

/// ID: 115834 Shroud of Concealment
class spell_shroud_of_concealment : public AuraScript
{
    PrepareAuraScript(spell_shroud_of_concealment);

    void HandleApply(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (!GetCaster())
            return;

        HandleFadeToNothingConduit(GetCaster());
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_shroud_of_concealment::HandleApply, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

/// ID: 3408 Crippling Poison
class spell_crippling_poison : public AuraScript
{
    PrepareAuraScript(spell_crippling_poison);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetDamageInfo();
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_crippling_poison::CheckProc);
    }
};

/// ID: 315584 Instant Poison
/// ID - 2823 Deadly Poison
class spell_instant_poison : public AuraScript
{
    PrepareAuraScript(spell_instant_poison);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetDamageInfo();
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_instant_poison::CheckProc);
    }
};
/// ID: 341535 Prepared for All
class spell_prepared_for_all : public AuraScript
{
    PrepareAuraScript(spell_prepared_for_all);

    enum PreparedForAll
    {
        Cloak = 31224,
        Evasion = 5277,
    };

    void HandleProc(ProcEventInfo& eventInfo)
    {
        auto caster = GetCaster();
        if (!caster)
            return;

        if (auto aur = GetAura())
        {
            if (auto eff = aur->GetEffect(EFFECT_0))
            {
                int32 baseCdDodge = 2000;
                int32 baseCdInterrupt = 4000;

                if (eff->ConduitRankEntry != nullptr)
                {
                    /// Formula comes from spell tooltip
                    baseCdDodge = int32(eff->ConduitRankEntry->AuraPointsOverride * 1000.0f);
                    baseCdInterrupt = int32(eff->ConduitRankEntry->AuraPointsOverride * 2000.0f);
                }

                if (eventInfo.GetHitMask() & ProcFlagsHit::PROC_HIT_DODGE)
                {
                    caster->GetSpellHistory()->ModifyCooldown(Evasion, -baseCdDodge);
                }

                if (eventInfo.GetHitMask() & ProcFlagsHit::PROC_HIT_INTERRUPT)
                {
                    caster->GetSpellHistory()->ModifyCooldown(Cloak, -baseCdInterrupt);
                }

            }
        }
    }

    void Register() override
    {
        OnProc += AuraProcFn(spell_prepared_for_all::HandleProc);
    }
};

/// ID: 340092 Deathly Shadows
class spell_deathly_shadows : public AuraScript
{
    PrepareAuraScript(spell_deathly_shadows);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == Vanish;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();
        if (auto caster = GetCaster())
        {
            if (IsSpec(caster, SimpleTalentSpecs::Outlaw))
                caster->CastSpell(caster, DeathlyShadowsOutlaw, true);
            else
                caster->CastSpell(caster, DeathlyShadowsOutlaw, true);
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_deathly_shadows::CheckProc);
        OnProc += AuraProcFn(spell_deathly_shadows::HandleProc);
    }
};

/// ID: 340079 Essence of Bloodfang
class spell_essence_of_bloodfang : public AuraScript
{
    PrepareAuraScript(spell_essence_of_bloodfang);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetSpellInfo())
            return false;

        switch (eventInfo.GetSpellInfo()->Id)
        {
            case SPELL_ROGUE_SHURIKEN_STORM:
                return true;
            default:
                break;
        }

        return eventInfo.GetProcSpell() && eventInfo.GetProcSpell()->m_comboPointsEnergized > 0;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_essence_of_bloodfang::CheckProc);
    }
};

/// ID - 385616 Echoing Reprimand
class spell_echoing_reprimand_385616 : public SpellScript
{
    PrepareSpellScript(spell_echoing_reprimand_385616);

    enum eEchoingReprimand
    {
        EchoingReprimand3 = 394136,
        EchoingReprimand4 = 394138,
        EchoingReprimand2 = 394140,
        ResoundingClarity = 381622,
    };

    void HandleDummy(SpellEffIndex /*eff*/)
    {
        if (auto caster = GetCaster())
        {
            caster->RemoveAurasDueToSpell(EchoingReprimand2);
            caster->RemoveAurasDueToSpell(EchoingReprimand3);
            caster->RemoveAurasDueToSpell(EchoingReprimand4);

            if (caster->HasAura(ResoundingClarity))
            {
                caster->CastSpell(caster, EchoingReprimand2, true);
                caster->CastSpell(caster, EchoingReprimand3, true);
                caster->CastSpell(caster, EchoingReprimand4, true);
            }
            else
            {
                caster->CastSpell(caster, RAND(
                    EchoingReprimand2,
                    EchoingReprimand3,
                    EchoingReprimand4
                ), true);
            }
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_echoing_reprimand_385616::HandleDummy, EFFECT_1, SPELL_EFFECT_DUMMY);
    }
};

void AddSC_rogue_spell_scripts()
{
    // SpellScripts
    new spell_rog_alacrity();
    new spell_rog_backstab();
    RegisterSpellAndAuraScriptPair(spell_rog_between_the_eyes, aura_rog_between_the_eyes);    
    RegisterSpellAndAuraScriptPair(spell_rog_blade_flurry, spell_rog_blade_flurry_dummy);
    new spell_rog_cannonball_barrage();
    new spell_rog_cheat_death();
    new spell_rog_cloak_and_dagger();
    new spell_rog_deadly_throw();
    RegisterSpellScript(spell_rog_deepening_shadows);
    new spell_rog_dirty_tricks();
    RegisterSpellScript(spell_rog_envenom);
    new spell_rog_fan_of_knives();
    RegisterSpellAndAuraScriptPair(spell_rog_garrote, aura_rog_garrote);
    RegisterSpellAndAuraScriptPair(spell_rog_kidney_shot, aura_rog_kidney_shot);
    new spell_rog_killing_spree();
    new spell_rog_nerve_strike();
    new spell_rog_nerve_strike_aura();
    new spell_rog_nightblade();
    new spell_rog_nightstalker();
    new spell_rog_riposte();
    new spell_rog_ruthlessness();
    RegisterSpellAndAuraScriptPair(spell_rog_rupture, aura_rog_rupture);
    new spell_rog_serrated_blades();
    new spell_rog_shadowstrike();
    RegisterSpellAndAuraScriptPair(spell_rog_shadow_dance, aura_rog_shadow_dance_effect);
    new spell_rog_shadow_techniques();
    new spell_rog_shuriken_storm();
    RegisterSpellScript(spell_slice_and_dice_sl);
    new spell_rog_stealth();
    new spell_rog_subterfuge();
    new spell_rog_true_bearing();
    new spell_rog_vanish();
    new spell_rog_vanish_aura();
    new spell_rogue_combat_potency();
    new spell_rog_weaponmaster();
	RegisterSpellScript(aura_rog_marked_for_death);
    RegisterSpellScript(spell_rog_beetween_the_eyes);
    new spell_rog_internal_bleeding_damage();
    new spell_rog_death_from_above_return();
    new spell_rog_death_from_above();
	RegisterSpellScript(aura_rog_shadow_dance);
	RegisterSpellScript(aura_rog_seal_fate);
	RegisterSpellScript(aura_rog_elaborate_planning);
	RegisterSpellScript(spell_rog_mutilate);
	RegisterSpellScript(aura_rog_leeching_poison);
	RegisterSpellScript(aura_rog_deadly_poison);
	RegisterSpellScript(aura_rog_wound_poison);
	RegisterSpellScript(spell_rog_cimson_tempest);
    RegisterSpellScript(aura_rog_shadow_blades);
    RegisterSpellScript(spell_rog_secret_technique);
	RegisterSpellScript(spell_rog_poison_knife);
	RegisterSpellScript(spell_rog_dismantle);
	RegisterSpellScript(spell_rog_cheap_shot);
	RegisterSpellScript(aura_rog_deadly_poison_debuff);
	RegisterSpellScript(spell_rog_shadowstep);
	RegisterSpellScript(aura_rog_creeping_venom);
	RegisterSpellScript(aura_mind_numbing_poison);
	RegisterSpellScript(aura_dagger_in_the_dark);
	RegisterSpellScript(aura_dagger_in_the_dark_debuff);
	RegisterSpellScript(aura_rog_cold_blood);
	RegisterSpellScript(spell_rog_sprint);
	RegisterSpellScript(spell_rog_shiv);
	RegisterSpellScript(aura_rog_take_your_cut);
	RegisterSpellScript(aura_rog_boarding_party);
	RegisterSpellScript(spell_rog_boarding_party_bonus);
	RegisterSpellScript(aura_shot_in_the_dark_buff);
    RegisterSpellScript(aura_rog_shuriken_tornado);
    RegisterSpellScript(aura_rog_blind);
    RegisterSpellScript(aura_rog_cheap_tricks);
    RegisterSpellScript(aura_rog_relentless_strikes);
    RegisterSpellScript(aura_rog_find_weakness);
    RegisterSpellScript(aura_rog_control_is_king_effect);
    RegisterSpellScript(spell_rog_shadowy_duel);  
    RegisterSpellScript(aura_rog_hidden_blades);
    RegisterSpellScript(aura_rog_hidden_blades_aura);
    RegisterSpellScript(spell_rog_cloak_of_shadows);
    RegisterSpellScript(spell_rog_cold_blood_damage);
    RegisterSpellScript(aura_rog_sprint_subtly);
    RegisterSpellScript(aura_rog_sprint_trigger);
    RegisterSpellScript(spell_rog_sap);
    RegisterSpellScript(spell_rog_blade_rush);
    RegisterSpellScript(spell_rog_serrated_bone_spike);
    RegisterSpellScript(spell_rog_vendetta);
    RegisterSpellScript(spell_exsanguinate);
    RegisterSpellScript(spell_shroud_of_concealment);
    RegisterSpellScript(spell_crippling_poison);
    RegisterSpellScript(spell_instant_poison);
    RegisterSpellScript(spell_prepared_for_all);
    RegisterSpellScript(spell_essence_of_bloodfang);
    RegisterSpellScript(spell_echoing_reprimand_385616);

	// Areatrigger
    RegisterAreaTriggerAI(at_rog_smoke_bomb);    // 11451
    RegisterAreaTriggerAI(at_rog_control_is_king); // 6952

    // Playerscript
    new rogue_playerscript();
}
