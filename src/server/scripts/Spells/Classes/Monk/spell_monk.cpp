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

#include "AreaTrigger.h"
#include "AreaTriggerAI.h"
#include "CellImpl.h"
#include "Containers.h"
#include "GridNotifiersImpl.h"
#include "ScriptMgr.h"
#include "SpellAuraEffects.h"
#include "SpellHistory.h"
#include "SpellMgr.h"
#include "SpellPackets.h"
#include "SpellScript.h"
#include "TemporarySummon.h"
#include "Util.h"
#include "spell_monk.h"

enum MonkSpells
{
    ITEM_MONK_T14_TANK_4P                               = 123159,
    MONK_NPC_BLACK_OX_STATUE                            = 61146,
    MONK_NPC_JADE_SERPENT_STATUE                        = 60849,
    SPELL_MONK_BLACKOUT_KICK_DOT                        = 128531,
    SPELL_MONK_BLACKOUT_KICK_HEAL                       = 128591,
    SPELL_MONK_BLACKOUT_STRIKE                          = 205523,
    SPELL_MONK_BLACK_OX_BREW                            = 115399,
    SPELL_MONK_BREATH_OF_FIRE                           = 115181,
    SPELL_MONK_BREATH_OF_FIRE_CONFUSED                  = 123393,
    SPELL_MONK_BREATH_OF_FIRE_DOT                       = 123725,
    SPELL_MONK_CHI_BURST_DAMAGE                         = 148135,
    SPELL_MONK_CHI_BURST_HEAL                           = 130654,
    SPELL_MONK_CHI_TORPEDO_DAMAGE                       = 117993,
    SPELL_MONK_CHI_TORPEDO_HEAL                         = 124040,
    SPELL_MONK_CHI_WAVE_DAMAGE                          = 132467,
    SPELL_MONK_CHI_WAVE_HEAL                            = 132463,
    SPELL_MONK_CHI_WAVE_HEALING_BOLT                    = 132464,
    SPELL_MONK_CHI_WAVE_TALENT_AURA                     = 115098,
    SPELL_MONK_CRACKLING_JADE_LIGHTNING_CHANNEL         = 117952,
    SPELL_MONK_CRACKLING_JADE_LIGHTNING_CHI_PROC        = 123333,
    SPELL_MONK_CRACKLING_JADE_LIGHTNING_KNOCKBACK       = 117962,
    SPELL_MONK_CRACKLING_JADE_LIGHTNING_KNOCKBACK_CD    = 117953,
    SPELL_MONK_CRACKLING_JADE_SHOCK_BUMP                = 117962,
    SPELL_MONK_CREATE_CHI_SPHERE                        = 121286,
    SPELL_MONK_DISABLE                                  = 116095,
    SPELL_MONK_DISABLE_ROOT                             = 116706,
    SPELL_MONK_ELUSIVE_BRAWLER                          = 195630,
    SPELL_MONK_IROSKIN_BREW                             = 115308,
    SPELL_MONK_ELUSIVE_BREW_STACKS                      = 128939,
    SPELL_MONK_EMINENCE_HEAL                            = 126890,
    SPELL_MONK_ENHANCED_ROLL                            = 157361,
    SPELL_MONK_ENVELOPING_MIST                          = 124682,
    SPELL_MONK_ESSENCE_FONT_HEAL                        = 191840,
    SPELL_MONK_FISTS_OF_FURY                            = 113656,
    SPELL_MONK_FISTS_OF_FURY_DAMAGE                     = 117418,
    SPELL_MONK_FLYING_SERPENT_KICK                      = 101545,
    SPELL_MONK_FLYING_SERPENT_KICK_AOE                  = 123586,
    SPELL_MONK_FLYING_SERPENT_KICK_NEW                  = 115057,
    SPELL_MONK_FORTIFYING_BREW                          = 115203,
    SPELL_MONK_GIFT_OF_THE_OX_AURA                      = 124502,
    SPELL_MONK_INNER_STRENG                             = 261767,
    SPELL_MONK_INNER_STRENG_BUFF                        = 261769,
    SPELL_MONK_GIFT_OF_THE_OX_AT_RIGHT                  = 124503,
    SPELL_MONK_GIFT_OF_THE_OX_AT_LEFT                   = 124506,
    SPELL_MONK_GLYPH_OF_BLACKOUT_KICK                   = 132005,
    SPELL_MONK_GLYPH_OF_RENEWING_MIST                   = 123334,
    SPELL_MONK_GLYPH_OF_ZEN_FLIGHT                      = 125893,
    SPELL_MONK_GRAPPLE_WEAPON_DPS_UPGRADE               = 123231,
    SPELL_MONK_GRAPPLE_WEAPON_HEAL_UPGRADE              = 123234,
    SPELL_MONK_GRAPPLE_WEAPON_TANK_UPGRADE              = 123232,
    SPELL_MONK_GUARD                                    = 115295,
    SPELL_MONK_HEALING_ELIXIRS_AURA                     = 122280,
    SPELL_MONK_HEALING_ELIXIRS_RESTORE_HEALTH           = 122281,
    SPELL_MONK_HEAVY_STAGGER                            = 124273,
    SPELL_MONK_ITEM_2_S12_MISTWEAVER                    = 131561,
    SPELL_MONK_ITEM_4_S12_MISTWEAVER                    = 124487,
    SPELL_MONK_ITEM_PVP_GLOVES_BONUS                    = 124489,
    SPELL_MONK_JADE_LIGHTNING_ENERGIZE                  = 123333,
    SPELL_MONK_KEG_SMASH_AURA                           = 121253,
    SPELL_MONK_KEG_SMASH_ENERGIZE                       = 127796,
    SPELL_MONK_KEG_SMASH_VISUAL                         = 123662,
    SPELL_MONK_LEGACY_OF_THE_EMPEROR                    = 117667,
    SPELL_MONK_LIFECYCLES_ENVELOPING_MIST               = 197919,
    SPELL_MONK_LIFECYCLES_VIVIFY                        = 197916,
    SPELL_MONK_LIGHT_STAGGER                            = 124275,
    SPELL_MONK_MANA_TEA_REGEN                           = 115294,
    SPELL_MONK_MANA_TEA_STACKS                          = 115867,
    SPELL_MONK_MEDITATE_VISUAL                          = 124416,
    SPELL_MONK_MODERATE_STAGGER                         = 124274,
    SPELL_MONK_MORTAL_WOUNDS                            = 115804,
    SPELL_MONK_PATH_OF_BLOSSOM_AREATRIGGER              = 122035,
    SPELL_MONK_PLUS_ONE_MANA_TEA                        = 123760,
    SPELL_MONK_POWER_STRIKES_TALENT                     = 121817,
    SPELL_MONK_POWER_STRIKES_AURA                       = 129914,
    SPELL_MONK_PROVOKE                                  = 118635,
    SPELL_MONK_PROVOKE_AOE                              = 118635,
    SPELL_MONK_PROVOKE_SINGLE_TARGET                    = 116189,
    SPELL_MONK_PURIFYING_BREW                           = 119582,
    SPELL_MONK_RENEWING_MIST_HOT                        = 119611,
    SPELL_MONK_RENEWING_MIST_JUMP_AURA                  = 119607,
    SPELL_MONK_RENEWING_MIST_PERIODIC                   = 119611,
    SPELL_MONK_RING_OF_PEACE_DISARM                     = 137461,
    SPELL_MONK_RING_OF_PEACE_SILENCE                    = 137460,
    SPELL_MONK_RISING_SUN_KICK                          = 107428,
    SPELL_MONK_RISING_THUNDER                           = 210804,
    SPELL_MONK_ROLL                                     = 109132,
    SPELL_MONK_ROLL_ANIMATION                           = 111396,
    SPELL_MONK_ROLL_BACKWARD                            = 109131,
    SPELL_MONK_ROLL_TRIGGER                             = 107427,
    SPELL_MONK_SHUFFLE                                  = 115307,
    SPELL_MONK_SONG_OF_CHIJI                            = 198909,
    SPELL_MONK_SOOTHING_MIST                            = 115175,
    SPELL_MONK_SOOTHING_MIST_AURA                       = 193884,
    SPELL_MONK_SOOTHING_MIST_ENERGIZE                   = 116335,
    SPELL_MONK_SOOTHING_MIST_VISUAL                     = 50239,
    SPELL_MONK_SPEAR_HAND_STRIKE_SILENCE                = 116709,
    SPELL_MONK_SPINNING_FIRE_BLOSSOM_MISSILE            = 118852,
    SPELL_MONK_SPINNING_FIRE_BLOSSOM_ROOT               = 123407,
    SPELL_MONK_SPIRIT_OF_THE_CRANE_AURA                 = 210802,
    SPELL_MONK_SPIRIT_OF_THE_CRANE_MANA                 = 210803,
    SPELL_MONK_STAGGER                                  = 124255,
    SPELL_MONK_STANCE_OF_THE_SPIRITED_CRANE             = 154436,
    SPELL_MONK_SURGING_MIST_HEAL                        = 116995,
    SPELL_MONK_TEACHINGS_OF_THE_MONASTERY               = 116645,
    SPELL_MONK_TEACHINGS_OF_THE_MONASTERY_AURA          = 202090,
    SPELL_MONK_THUNDER_FOCUS_TEA                        = 116680,
    SPELL_MONK_TIGEREYE_BREW                            = 116740,
    SPELL_MONK_TIGEREYE_BREW_STACKS                     = 125195,
    SPELL_MONK_TRANSCENDENCE_CLONE_TARGET               = 119051,
    SPELL_MONK_TRANSCENDENCE_VISUAL                     = 119053,
    SPELL_MONK_TOUCH_OF_DEATH                           = 115080,
    SPELL_MONK_TOUCH_OF_DEATH_DAMAGE                    = 229980,
    SPELL_MONK_TOUCH_OF_KARMA_REDIRECT_DAMAGE           = 124280,
    SPELL_MONK_UPLIFT_ALLOWING_CAST                     = 123757,
    SPELL_MONK_VIVIFY                                   = 116670,
    SPELL_MONK_WEAKENED_BLOWS                           = 115798,
    SPELL_MONK_WHIRLING_DRAGON_PUNCH                    = 152175,
    SPELL_MONK_WHIRLING_DRAGON_PUNCH_CASTER_AURA        = 196742,
    SPELL_MONK_WHIRLING_DRAGON_PUNCH_DAMAGE             = 158221,
    SPELL_MONK_WINDWALKER_AURA                          = 166646,
    SPELL_MONK_WINDWALKING                              = 157411,
    SPELL_MONK_XUEN_AURA                                = 123999,
    SPELL_MONK_ZEN_FLIGHT                               = 125883,
    SPELL_MONK_ZEN_FOCUS                                = 124488,
    SPELL_MONK_ZEN_PILGRIMAGE                           = 126892,
    SPELL_MONK_ZEN_PILGRIMAGE_RETURN                    = 126895,
    SPELL_MONK_ZEN_PULSE_DAMAGE                         = 124081,
    SPELL_MONK_ZEN_PULSE_HEAL                           = 198487,
    SPELL_MONK_CHI_WAVE_SELECTOR			            = 132466,
    SPELL_MONK_CHI_WAVE_DAMAGE_TARGET			        = 132467,
    SPELL_MONK_BLACK_OX_PROVOQUE			            = 163177,
    SPELL_MONK_INNER_STRENGTH				            = 261767,
    SPELL_MONK_INNER_STRENGTH_AURA			            = 261769,
    SPELL_MONK_BLACKOUT_KICK				            = 100784,
    SPELL_MONK_BLACKOUT_KICK_TRIGGERED                  = 228649,
    SPELL_MONK_SPINNING_CRANE_KICK			            = 101546,
    SPELL_MONK_MYSTIC_TOUCH_AURA			            = 113746,
    SPELL_MONK_TIGER_PALM                               = 100780,
    SPELL_MONK_SPITFIRE_RESET                           = 242581,
    SPELL_MONK_IRONSKIN_BREW_AURA                       = 215479,
    SPELL_MONK_VIVIFY_RANK                              = 274586,
    SPELL_MONK_ESSENCE_FONT_RANK                        = 231633,
	SPELL_MONK_LIFECYCLES                               = 197915,
    SPELL_MONK_FOCUS_THUNDER_TEA_RANK                   = 231876,
    SPELL_MONK_RENEWING_MIST                            = 115151,
    SPELL_MONK_RING_OF_PEACE_KNOCKBACK                  = 237371,
	SPELL_MONK_STAGGER_AURA								= 115069,
    SPELL_MONK_HIGH_TOLERANCE                           = 196737,
	SPELL_MONK_BREWMASTER_MONK							= 137023,
	SPELL_MONK_SUMMON_HEALING_SPHERE					= 117032,
	SPELL_MONK_SUMMON_CHI_SPHERE						= 163271,
	SPELL_MONK_HEALING_SPHERE_PROC						= 125355,
	SPELL_MONK_HEALING_CHI_PROC							= 163272,
	SPELL_MONK_CONTROL_THE_MIST_BUFF					= 233954,
	SPELL_MONK_CONTROL_THE_MIST_AURA					= 233765,
	SPELL_MONK_CONTROL_THE_MIST_DEBUFF					= 233766,
	SPELL_MONK_CELESTIAL_FORTUNE						= 216519,
	SPELL_MONK_CELESTIAL_FORTUNE_HEAL					= 216521,
	SPELL_MONK_GIFT_OF_THE_OX_HEAL						= 124507,
    SPELL_MONK_GIFT_OF_THE_OX_GREATER_HEAL              = 213464,
	SPELL_MONK_HEALING_SPHERE							= 224863,
	SPELL_MONK_EXPEL_HARM								= 115072,
	SPELL_MONK_EXPEL_HARM_DAMAGE						= 115129,
	SPELL_MONK_COUNTERATTACK_MAGIC						= 202428,
	SPELL_MONK_SOOTHING_MIST_STATUE						= 198533,
	SPELL_MONK_TOUCH_OF_DEATH_DAMAGE_AMPLIFIER			= 271233,
	SPELL_MONK_HOT_TRUB									= 202126,
	SPELL_MONK_HOT_TRUB_DAMAGE							= 202127,
	SPELL_MONK_AVERT_HARM								= 202162,
	SPELL_MONK_INCENDIARY_BREATH						= 202272,
	SPELL_MONK_INCENDIARY_BREATH_DISORIENTED			= 202274,
    SPELL_MONK_DOUBLE_BARREL                            = 202335,
    SPELL_MONK_DOUBLE_BARREL_STUN                       = 202346,
    SPELL_MONK_WAY_OF_THE_CRANE                         = 216113,
    SPELL_MONK_WAY_OF_THE_CRANE_HEAL                    = 281501,
    SPELL_MONK_SPHERE_HEALING_AT                        = 202531,
    SPELL_MONK_SPHERE_PVP_HEAL                          = 115464,
    SPELL_MNOK_ENVELOPING_MIST_INSTANT_HEAL             = 274062,
    SPELL_MONK_CYCLONE_STRIKES                          = 220358,
    SPELL_MONK_RUSHING_JADE_WIND                        = 261715,
    SPELL_MONK_RISING_SUN_KICK_DAMAGE                   = 185099,
    SPELL_MONK_CYCLONE_STRIKES_AURA                     = 220357,
    SPELL_MONK_HEAVY_HANDED_STRIKES                     = 232054,
    SPELL_MONK_HEAVY_HANDED_STRIKES_TRIGGER             = 201787,
    SPELL_FIST_OF_THE_WHITE_TIGER                       = 261947,
    SPELL_TIGER_PALM                                    = 100780,
    SPELL_CHI_BURST                                     = 123986,
    SPELL_MONK_BURST_OF_LIFE_POWER                      = 277667,
    SPELL_MONK_BURST_OF_LIFE_HEAL                       = 278564,
    SPELL_MONK_MASTERY_GUST_OF_MIST                     = 117907,
    SPELL_MONK_GUST_OF_MIST                             = 191894,
    SPELL_MONK_AFTERLIFE                                = 116092,
    SPELL_MONK_TIGER_BREW                               = 247483,
    SPELL_MONK_TIGER_BREW_TRIGGER                       = 248646,
    SPELL_MONK_TIGER_BREW_LIGHT_AURA                    = 248648,
    SPELL_MONK_TRASCENDENCE_ALLOW_CAST                  = 62388,
    SPELL_MONK_GIFT_OF_THE_OX_GREATER_HEALING_SPHERE    = 214418,
    SPELL_MONK_GIFT_OF_THE_OX_GREATER_HEALING_SPHERE_1  = 214420,
    SPELL_MONK_YULONS_GIFT                              = 159534,
    SPELL_MONK_YUKONS_GIFT_EFFECT                       = 159535,
    SPELL_MONK_GUST_OF_MIST_MASTERY                     = 117907,
};

enum StormEarthAndFireSpells
{
    SPELL_MONK_SEF                              = 137639,
    SPELL_MONK_SEF_STORM_VISUAL                 = 138080,
    SPELL_MONK_SEF_FIRE_VISUAL                  = 138081,
    SPELL_MONK_SEF_EARTH_VISUAL                 = 138083,
    SPELL_MONK_SEF_CHARGE                       = 138104,
    SPELL_MONK_SEF_SUMMON_EARTH                 = 138121,
    SPELL_MONK_SEF_SUMMON_FIRE                  = 138123,
    SPELL_MONK_SEF_SUMMONS_STATS                = 138130,
    SPELL_MONK_SEF_KICK_VISUAL                  = 178452,
    SPELL_MONK_SEF_JADE_LIGHTNING_VISUAL        = 178453,
    SPELL_MONK_SEF_CHARGE_TARGET                = 196860,
    SPELL_MONK_SEF_FIXATE                       = 221771,
    SPELL_MONK_OVERFLOW                         = 213180,

    NPC_FIRE_SPIRIT                             = 69791,
    NPC_EARTH_SPIRIT                            = 69792,
};

#define MONK_TRANSCENDENCE_GUID "MONK_TRANSCENDENCE_GUID"

// 109132 - Roll
class spell_monk_roll : public SpellScriptLoader
{
public:
    spell_monk_roll() : SpellScriptLoader("spell_monk_roll") { }

    class spell_monk_roll_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_monk_roll_SpellScript);

    private:
        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_MONK_ROLL) ||
                !sSpellMgr->GetSpellInfo(SPELL_MONK_ROLL_TRIGGER) ||
                !sSpellMgr->GetSpellInfo(SPELL_MONK_ROLL_BACKWARD))
                return false;
            return true;
        }

        void HandleCast()
        {
            if (Unit* caster = GetCaster())
                if (caster->HasAura(SPELL_MONK_YULONS_GIFT))
                    caster->CastSpell(caster, SPELL_MONK_YUKONS_GIFT_EFFECT, true);
        }

        void HandleAfterCast()
        {
            Unit* caster = GetCaster();
            if (!caster || caster->GetTypeId() != TYPEID_PLAYER)
                return;

            if (caster->HasAura(SPELL_MONK_ITEM_PVP_GLOVES_BONUS))
                caster->RemoveAurasByType(SPELL_AURA_MOD_DECREASE_SPEED);
        }

        void HandleDummy()
        {
            if (Unit* caster = GetCaster())
            {
                if (caster->HasUnitMovementFlag(MOVEMENTFLAG_BACKWARD))
                    caster->CastSpell(caster, SPELL_MONK_ROLL_BACKWARD, true);
                else
                    caster->CastSpell(caster, SPELL_MONK_ROLL_TRIGGER, true);
            }
        }

        void Register() override
        {
            OnCast += SpellCastFn(spell_monk_roll_SpellScript::HandleCast);
            AfterCast += SpellCastFn(spell_monk_roll_SpellScript::HandleAfterCast);
            AfterHit += SpellHitFn(spell_monk_roll_SpellScript::HandleDummy);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_monk_roll_SpellScript();
    }
};

// Roll trigger - 107427
class spell_monk_roll_trigger : public SpellScriptLoader
{
public:
    spell_monk_roll_trigger() : SpellScriptLoader("spell_monk_roll_trigger") {}

    class spell_monk_roll_trigger_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_monk_roll_trigger_AuraScript);

        void CalcSpeed(AuraEffect const* /*aurEff*/, int32& amount, bool& /*canBeRecalculated*/)
        {
            Unit* caster = GetCaster();
            if (!caster)
                return;

            if (caster->HasAura(SPELL_MONK_ENHANCED_ROLL))
                amount = 277;
        }

        void CalcSpeed2(AuraEffect const* /*aurEff*/, int32& amount, bool& /*canBeRecalculated*/)
        {
            Unit* caster = GetCaster();
            if (!caster)
                return;

            if (!caster->HasAura(SPELL_MONK_ENHANCED_ROLL))
                return;

            amount = 377;
        }

        void SendAmount(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            Unit* caster = GetCaster();
            if (!caster)
                return;

            if (!caster->HasAura(SPELL_MONK_ENHANCED_ROLL))
                return;

            Aura* aur = GetAura();
            if (!aur)
                return;

            aur->SetMaxDuration(600);
            aur->SetDuration(600);

            if (AuraApplication* aurApp = GetAura()->GetApplicationOfTarget(caster->GetGUID()))
                aurApp->ClientUpdate();
        }

        void Register() override
        {
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_monk_roll_trigger_AuraScript::CalcSpeed, EFFECT_0, SPELL_AURA_MOD_SPEED_NO_CONTROL);
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_monk_roll_trigger_AuraScript::CalcSpeed2, EFFECT_2, SPELL_AURA_MOD_MINIMUM_SPEED);
            AfterEffectApply += AuraEffectApplyFn(spell_monk_roll_trigger_AuraScript::SendAmount, EFFECT_4, SPELL_AURA_USE_NORMAL_MOVEMENT_SPEED, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_monk_roll_trigger_AuraScript();
    }
};

// Fists of Fury (stun effect) - 120086
class spell_monk_fists_of_fury_stun : public SpellScriptLoader
{
public:
    spell_monk_fists_of_fury_stun() : SpellScriptLoader("spell_monk_fists_of_fury_stun") { }

    class spell_monk_fists_of_fury_stun_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_monk_fists_of_fury_stun_SpellScript);

        void RemoveInvalidTargets(std::list<WorldObject*>& targets)
        {
            targets.remove_if(Trinity::UnitAuraCheck(true, GetSpellInfo()->Id));
        }

        void Register() override
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_monk_fists_of_fury_stun_SpellScript::RemoveInvalidTargets, EFFECT_0, TARGET_UNIT_CONE_ENEMY_24);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_monk_fists_of_fury_stun_SpellScript();
    }
};

// 115072 - Expel Harm
class spell_monk_expel_harm : public SpellScript
{
	PrepareSpellScript(spell_monk_expel_harm);

	void HandleHit(SpellEffIndex /*effIndex*/)
	{
		if (Unit* caster = GetCaster())
		{
			if (Aura* healingSphere = caster->GetAura(SPELL_MONK_HEALING_SPHERE))
			{
				int32 base = caster->GetTotalAttackPowerValue(BASE_ATTACK) * 1.5f;
				int32 amount = base;
				if (healingSphere->GetStackAmount() > 1)
				{
					amount = base * healingSphere->GetStackAmount() - base;
					caster->CastCustomSpell(SPELL_MONK_GIFT_OF_THE_OX_HEAL, SPELLVALUE_BASE_POINT0, amount, caster, true);
				}
				else
					caster->CastSpell(caster, SPELL_MONK_GIFT_OF_THE_OX_HEAL, true);

				// Apply damage
				amount = CalculatePct(amount, sSpellMgr->GetSpellInfo(SPELL_MONK_EXPEL_HARM)->GetEffect(EFFECT_1).BasePoints);
				caster->CastCustomSpell(SPELL_MONK_EXPEL_HARM_DAMAGE, SPELLVALUE_BASE_POINT0, amount, caster, true);
				std::vector<AreaTrigger*> areaTriggersLeft = caster->GetAreaTriggers(SPELL_MONK_GIFT_OF_THE_OX_AT_LEFT);
				std::vector<AreaTrigger*> areaTriggersRight = caster->GetAreaTriggers(SPELL_MONK_GIFT_OF_THE_OX_AT_RIGHT);
				for (AreaTrigger* areatrigger : areaTriggersLeft)
					areatrigger->SetDuration(0);
				for (AreaTrigger* areatrigger : areaTriggersRight)
					areatrigger->SetDuration(0);

				caster->RemoveAurasDueToSpell(SPELL_MONK_HEALING_SPHERE);
			}
		}
	}

	void Register() override
	{
		OnEffectHitTarget += SpellEffectFn(spell_monk_expel_harm::HandleHit, EFFECT_1, SPELL_EFFECT_DUMMY);
	}
};

// 115129 - Expel Harm Damage
class spell_monk_expel_harm_damage : public SpellScript
{
	PrepareSpellScript(spell_monk_expel_harm_damage);

	void FilterTargets(std::list<WorldObject*>& targets)
	{
		if (Unit* caster = GetCaster())
			targets.sort(Trinity::DistanceCompareOrderPred(caster));
	}

	void Register() override
	{
		OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_monk_expel_harm_damage::FilterTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ENEMY);
	}
};

// 132464 - Chi Wave (heal missile)
class aura_monk_chi_wave_heal_missile : public AuraScript
{
	PrepareAuraScript(aura_monk_chi_wave_heal_missile);

	void OnRemove(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
	{
		Unit* caster = GetCaster();
		Unit* target = GetTarget();
		if (!target || !caster)
			return;

		caster->CastSpell(target, SPELL_MONK_CHI_WAVE_HEAL, true);
		if (caster->Variables.GetValue("chiWaveJumps", 0) < 7)
			caster->CastCustomSpell(SPELL_MONK_CHI_WAVE_SELECTOR, SPELLVALUE_BASE_POINT1, aurEff->GetAmount() - 1, target, true, NULL, aurEff);
	}

	void Register() override
	{
		OnEffectRemove += AuraEffectRemoveFn(aura_monk_chi_wave_heal_missile::OnRemove, EFFECT_1, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
	}
};

// 132464 - Chi Wave (heal missile)
class spell_monk_chi_wave_heal_missile : public SpellScriptLoader
{
public:
    spell_monk_chi_wave_heal_missile() : SpellScriptLoader("spell_monk_chi_wave_heal_missile") {}

    class spell_monk_chi_wave_heal_missile_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_monk_chi_wave_heal_missile_AuraScript);

        void OnRemove(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
        {
            Unit* caster = GetCaster();
            Unit* target = GetTarget();
            if (!target || !caster)
                return;

            caster->CastSpell(target, 132463, true);
            // rerun target selector
            caster->CastCustomSpell(132466, SPELLVALUE_BASE_POINT1, aurEff->GetAmount() - 1, target, true, NULL, aurEff);
        }

        void Register() override
        {
            OnEffectRemove += AuraEffectRemoveFn(spell_monk_chi_wave_heal_missile_AuraScript::OnRemove, EFFECT_1, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_monk_chi_wave_heal_missile_AuraScript();
    }
};

// 132467 - Chi Wave (damage missile)
class aura_monk_chi_wave_damage_missile : public AuraScript
{
	PrepareAuraScript(aura_monk_chi_wave_damage_missile);

	void OnRemove(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
	{
		Unit* caster = GetCaster();
		Unit* target = GetTarget();
		if (!target || !caster)
			return;

		// rerun target selector
		if (caster->Variables.GetValue("chiWaveJumps", 0) < 7)
			caster->CastCustomSpell(SPELL_MONK_CHI_WAVE_SELECTOR, SPELLVALUE_BASE_POINT1, aurEff->GetAmount() - 1, target, true, NULL, aurEff);
	}

	void Register() override
	{
		OnEffectRemove += AuraEffectRemoveFn(aura_monk_chi_wave_damage_missile::OnRemove, EFFECT_1, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
	}
};

// 132466 - Chi Wave (target selector)
class spell_monk_chi_wave_target_selector : public SpellScriptLoader
{
public:
	spell_monk_chi_wave_target_selector() : SpellScriptLoader("spell_monk_chi_wave_target_selector") {}

	class DamageUnitCheck
	{
	public:
		DamageUnitCheck(Unit const* source, float range) : m_source(source), m_range(range) {}
		bool operator()(WorldObject* object)
		{
			Unit* unit = object->ToUnit();
			if (!unit)
				return true;

			if (m_source->IsValidAttackTarget(unit) && unit->isTargetableForAttack() && m_source->IsWithinDistInMap(unit, m_range))
			{
				m_range = m_source->GetDistance(unit);
				return false;
			}

			return true;
		}
	private:
		Unit const* m_source;
		float m_range;
	};

	class HealUnitCheck
	{
	public:
		HealUnitCheck(Unit const* source) : m_source(source) {}
		bool operator()(WorldObject* object)
		{
			Unit* unit = object->ToUnit();
			if (!unit)
				return true;

			if (m_source->IsFriendlyTo(unit))
				return false;

			return true;
		}
	private:
		Unit const* m_source;
	};

	class spell_monk_chi_wave_target_selector_SpellScript : public SpellScript
	{
		PrepareSpellScript(spell_monk_chi_wave_target_selector_SpellScript);

		bool Load() override
		{
			m_shouldHeal = true; // just for initializing
			return true;
		}

		void SelectTarget(std::list<WorldObject*>& targets)
		{
			if (targets.empty())
				return;

			SpellInfo const* spellInfo = GetTriggeringSpell();
			if (spellInfo->Id == SPELL_MONK_CHI_WAVE_DAMAGE_TARGET) // Triggered by damage, so we need heal selector
			{
				targets.remove_if(HealUnitCheck(GetCaster()));
				targets.sort(Trinity::HealthPctOrderPred(false)); // Reverse order due to target is selected via std::list back
				m_shouldHeal = true;
			}
			else if (spellInfo->Id == SPELL_MONK_CHI_WAVE_HEALING_BOLT) // Triggered by heal, so we need damage selector
			{
				targets.remove_if(DamageUnitCheck(GetCaster(), 25.0f));
				m_shouldHeal = false;
			}

			if (targets.empty())
				return;

			WorldObject* target = targets.back();
			if (!target)
				return;

			targets.clear();
			targets.push_back(target);
		}

		void HandleDummy(SpellEffIndex /*effIndex*/)
		{
			//if (!GetEffectValue()) // Ran out of bounces
			//    return;

			if (!GetExplTargetUnit() || !GetOriginalCaster())
				return;

			Unit* target = GetHitUnit();
            int jumps = GetOriginalCaster()->Variables.GetValue("chiWaveJumps", 0);
			if (m_shouldHeal)
			{
				jumps++;
				GetExplTargetUnit()->SendPlaySpellVisual(target->GetGUID(), 38379, 0, 0, 20);
				GetExplTargetUnit()->CastCustomSpell(SPELL_MONK_CHI_WAVE_HEALING_BOLT, SPELLVALUE_BASE_POINT1, GetEffectValue(), target, true, NULL, NULL, GetOriginalCaster()->GetGUID());
			}
			else
			{
                jumps++;
				GetExplTargetUnit()->SendPlaySpellVisual(target->GetGUID(), 38378, 0, 0, 20);
				GetExplTargetUnit()->CastCustomSpell(SPELL_MONK_CHI_WAVE_DAMAGE_TARGET, SPELLVALUE_BASE_POINT1, GetEffectValue(), target, true, NULL, NULL, GetOriginalCaster()->GetGUID());
			}
            GetOriginalCaster()->Variables.Set("chiWaveJumps", jumps);
		}

		void Register() override
		{
			OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_monk_chi_wave_target_selector_SpellScript::SelectTarget, EFFECT_1, TARGET_UNIT_DEST_AREA_ENTRY);
			OnEffectHitTarget += SpellEffectFn(spell_monk_chi_wave_target_selector_SpellScript::HandleDummy, EFFECT_1, SPELL_EFFECT_DUMMY);
		}

		bool m_shouldHeal;
	};

	SpellScript* GetSpellScript() const override
	{
		return new spell_monk_chi_wave_target_selector_SpellScript();
	}
};

// Zen Flight - 125883
class spell_monk_zen_flight_check : public SpellScriptLoader
{
public:
    spell_monk_zen_flight_check() : SpellScriptLoader("spell_monk_zen_flight_check") { }

    class spell_monk_zen_flight_check_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_monk_zen_flight_check_SpellScript);

        SpellCastResult CheckTarget()
        {
            if (Player* _player = GetCaster()->ToPlayer())
            {
                if (_player->GetMap()->IsBattlegroundOrArena())
                    return SPELL_FAILED_NOT_IN_BATTLEGROUND;

                // In Kalimdor or Eastern Kingdom with Flight Master's License
                if (!_player->HasSpell(90267) && (_player->GetMapId() == 1 || _player->GetMapId() == 0))
                    return SPELL_FAILED_NOT_HERE;

                // In Pandaria with Wisdom of the Four Winds
                if (!_player->HasSpell(115913) && (_player->GetMapId() == 870))
                    return SPELL_FAILED_NOT_HERE;

                if (AreaTableEntry const* area = sAreaTableStore.LookupEntry(_player->GetAreaId()))
                    if (area->Flags[0] & AREA_FLAG_NO_FLY_ZONE)
                        return SPELL_FAILED_NOT_HERE;

                if (_player->GetMap()->Instanceable())
                    return SPELL_FAILED_NOT_HERE;
            }

            return SPELL_CAST_OK;
        }

        void Register() override
        {
            OnCheckCast += SpellCheckCastFn(spell_monk_zen_flight_check_SpellScript::CheckTarget);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_monk_zen_flight_check_SpellScript();
    }

    class spell_monk_zen_flight_check_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_monk_zen_flight_check_AuraScript);

        bool Load() override
        {
            return GetCaster() && GetCaster()->GetTypeId() == TYPEID_PLAYER;
        }

        void CalculateAmount(AuraEffect const* /*aurEff*/, int32& amount, bool & /*canBeRecalculated*/)
        {
            if (!GetCaster())
                return;

            if (Player* caster = GetCaster()->ToPlayer())
                if (caster->GetSkillValue(SKILL_RIDING) >= 375)
                    amount = 310;
        }

        void Register() override
        {
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_monk_zen_flight_check_AuraScript::CalculateAmount, EFFECT_1, SPELL_AURA_MOD_INCREASE_VEHICLE_FLIGHT_SPEED);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_monk_zen_flight_check_AuraScript();
    }
};

// Crackling Jade Lightning - 117952
class spell_monk_crackling_jade_lightning : public SpellScriptLoader
{
public:
    spell_monk_crackling_jade_lightning() : SpellScriptLoader("spell_monk_crackling_jade_lightning") { }

    class spell_monk_crackling_jade_lightning_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_monk_crackling_jade_lightning_AuraScript);

        void OnTick(AuraEffect const* /* aurEff */)
        {
            if (Unit* caster = GetCaster())
                if (roll_chance_i(25))
                    caster->CastSpell(caster, SPELL_MONK_JADE_LIGHTNING_ENERGIZE, true);
        }

        void OnProc(AuraEffect* /* aurEff */, ProcEventInfo& eventInfo)
        {
            PreventDefaultAction();

            if (!GetCaster())
                return;

            if (eventInfo.GetActor()->GetGUID() != GetTarget()->GetGUID())
                return;

            /*if (GetCaster()->ToPlayer())
            {
                ;
            }*/
        }

        void Register() override
        {
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_monk_crackling_jade_lightning_AuraScript::OnTick, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE);
            OnEffectProc += AuraEffectProcFn(spell_monk_crackling_jade_lightning_AuraScript::OnProc, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_monk_crackling_jade_lightning_AuraScript();
    }
};

// Path of Blossom - 124336
class spell_monk_path_of_blossom : public AuraScript
{
    PrepareAuraScript(spell_monk_path_of_blossom);

    void OnTick(AuraEffect const* /* aurEff */)
    {
        if (GetCaster())
            GetCaster()->CastSpell(GetCaster(), SPELL_MONK_PATH_OF_BLOSSOM_AREATRIGGER, true);
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_monk_path_of_blossom::OnTick, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

class spell_monk_mana_tea : public SpellScriptLoader
{
public:
    spell_monk_mana_tea() : SpellScriptLoader("spell_monk_mana_tea") { }

    class spell_monk_mana_tea_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_monk_mana_tea_SpellScript);

        SpellModifierByClassMask* mod = nullptr;

        void HandleBeforeCast()
        {
            if (Player* _player = GetCaster()->ToPlayer())
            {
                int32 stacks = 0;

                if (Aura* manaTeaStacks = _player->GetAura(SPELL_MONK_MANA_TEA_STACKS))
                {
                    stacks = manaTeaStacks->GetStackAmount();

                    int32 newDuration = stacks * IN_MILLISECONDS;

                    mod = new SpellModifierByClassMask(manaTeaStacks);
                    mod->op = SpellModOp::Duration;
                    mod->type = SPELLMOD_FLAT;
                    mod->spellId = SPELL_MONK_MANA_TEA_REGEN;
                    mod->value = newDuration;
                    mod->mask[1] = 0x200000;
                    mod->mask[2] = 0x1;

                    _player->AddSpellMod(mod, true);
                }
            }
        }

        void HandleAfterCast()
        {
            if (mod)
                if (Player* _player = GetCaster()->ToPlayer())
                    _player->AddSpellMod(mod, false);
        }

        void Register() override
        {
            BeforeCast += SpellCastFn(spell_monk_mana_tea_SpellScript::HandleBeforeCast);
            AfterCast += SpellCastFn(spell_monk_mana_tea_SpellScript::HandleAfterCast);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_monk_mana_tea_SpellScript();
    }

    class spell_monk_mana_tea_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_monk_mana_tea_AuraScript);

        void OnTick(const AuraEffect* /*aurEff*/)
        {
            if (GetCaster())
            {
                // remove one charge per tick instead of remove aura on cast
                // "Cancelling the channel will not waste stacks"
                if (Aura* manaTea = GetCaster()->GetAura(SPELL_MONK_MANA_TEA_STACKS))
                {
                    if (manaTea->GetStackAmount() > 1)
                        manaTea->SetStackAmount(manaTea->GetStackAmount() - 1);
                    else
                        GetCaster()->RemoveAura(SPELL_MONK_MANA_TEA_STACKS);
                }
            }
        }

        void Register() override
        {
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_monk_mana_tea_AuraScript::OnTick, EFFECT_0, SPELL_AURA_OBS_MOD_POWER);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_monk_mana_tea_AuraScript();
    }
};

// Brewing : Mana Tea - 123766
class spell_monk_mana_tea_stacks : public SpellScriptLoader
{
public:
    spell_monk_mana_tea_stacks() : SpellScriptLoader("spell_monk_mana_tea_stacks") { }

    class spell_monk_mana_tea_stacks_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_monk_mana_tea_stacks_AuraScript);

        uint32 chiConsumed;

        void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            chiConsumed = 0;
        }

        void SetData(uint32 /* type */, uint32 data)
        {
            while ((chiConsumed += data) >= 4)
            {
                chiConsumed = 0;
                data = data > 4 ? data - 4 : 0;

                if (GetCaster())
                {
                    GetCaster()->CastSpell(GetCaster(), SPELL_MONK_MANA_TEA_STACKS, true);
                    GetCaster()->CastSpell(GetCaster(), SPELL_MONK_PLUS_ONE_MANA_TEA, true);
                }
            }
        }

        void Register() override
        {
            AfterEffectApply += AuraEffectApplyFn(spell_monk_mana_tea_stacks_AuraScript::OnApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_monk_mana_tea_stacks_AuraScript();
    }
};

// NOTE: this script is causing a server crash and almost everything
// is optimized away. DO NOT remove this unless you fix the crash
#pragma optimize("", off)
// 124682 - Enveloping Mist
class spell_monk_enveloping_mist : public SpellScriptLoader
{
public:
    spell_monk_enveloping_mist() : SpellScriptLoader("spell_monk_enveloping_mist") { }

    class spell_monk_enveloping_mist_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_monk_enveloping_mist_SpellScript);

        void HandleAfterCast()
        {
			Unit* caster = GetCaster();
			Unit* target = GetExplTargetUnit();
			if (!caster || !target)
				return;

            if (caster->HasAura(SPELL_MONK_THUNDER_FOCUS_TEA))
                caster->CastSpell(target, SPELL_MNOK_ENVELOPING_MIST_INSTANT_HEAL, true);

			if (caster->HasAura(SPELL_MONK_LIFECYCLES))
				caster->CastSpell(caster, SPELL_MONK_LIFECYCLES_VIVIFY, true);

			if ((GetSpell()->GetTriggeredCastFlags() & TRIGGERED_CAST_DIRECTLY) && caster->HasAura(SPELL_MONK_LIFECYCLES_ENVELOPING_MIST))
				caster->RemoveAurasDueToSpell(SPELL_MONK_LIFECYCLES_ENVELOPING_MIST);

            // Thunder Tea.
            if (Aura* aura = caster->GetAura(SPELL_MONK_THUNDER_FOCUS_TEA))
                aura->ModStackAmount(-1);
        }

        void HadlePrepare()
        {
            if (Unit* caster = GetCaster())
                if (Spell* spell = GetSpell())
                {
                    if (spell->GetTriggeredCastFlags() & TRIGGERED_CAST_DIRECTLY)
                        return;

                    if (Spell* currentSpell = caster->GetCurrentSpell(CURRENT_CHANNELED_SPELL))
                        if (currentSpell->GetSpellInfo()->Id == SPELL_MONK_SOOTHING_MIST)
                        {
                            Unit* target = currentSpell->GetUnitTarget();
                            Unit* selfTarget = spell->GetUnitTarget();
                            if (!target || !selfTarget)
                                return;

                            if (!target->IsInWorld() || !selfTarget->IsInWorld())
                                return;

                            if (target->GetGUID() == selfTarget->GetGUID())
                            {
                                TriggerCastFlags flags = TriggerCastFlags(spell->GetTriggeredCastFlags() | TRIGGERED_CAST_DIRECTLY);
                                spell->SetTriggerCastFlags(flags);
                            }
                        }
                }
        }

        void Register() override
        {
			OnPrepare += SpellOnPrepareFn(spell_monk_enveloping_mist_SpellScript::HadlePrepare);
            AfterCast += SpellCastFn(spell_monk_enveloping_mist_SpellScript::HandleAfterCast);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_monk_enveloping_mist_SpellScript();
    }
};
#pragma optimize("", on)

// Zen Pulse - 124081
class spell_monk_zen_pulse : public SpellScriptLoader
{
public:
    spell_monk_zen_pulse() : SpellScriptLoader("spell_monk_zen_pulse") {}

    class spell_monk_zen_pulse_SpellScript : public SpellScript
    {

        PrepareSpellScript(spell_monk_zen_pulse_SpellScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_MONK_ZEN_PULSE_DAMAGE))
                return false;
            return true;
        }

        void OnHit(SpellEffIndex /*effIndex*/)
        {
            GetCaster()->CastSpell(GetCaster(), SPELL_MONK_ZEN_PULSE_HEAL, true);
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_monk_zen_pulse_SpellScript::OnHit, EFFECT_1, SPELL_EFFECT_SCHOOL_DAMAGE);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_monk_zen_pulse_SpellScript();
    }
};

// Flying Serpent Kick - 115057
class spell_monk_flying_serpent_kick : public SpellScriptLoader
{
public:
    spell_monk_flying_serpent_kick() : SpellScriptLoader("spell_monk_flying_serpent_kick") { }

    class spell_monk_flying_serpent_kick_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_monk_flying_serpent_kick_SpellScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_MONK_FLYING_SERPENT_KICK_NEW))
                return false;
            return true;
        }

        void HandleOnCast()
        {
            if (Unit* caster = GetCaster())
            {
                if (Player* _player = caster->ToPlayer())
                {
                    if (_player->HasAura(SPELL_MONK_FLYING_SERPENT_KICK))
                        _player->RemoveAura(SPELL_MONK_FLYING_SERPENT_KICK);

                    if (caster->HasAura(SPELL_MONK_ITEM_PVP_GLOVES_BONUS))
                        caster->RemoveAurasByType(SPELL_AURA_MOD_DECREASE_SPEED);

                    _player->CastSpell(_player, SPELL_MONK_FLYING_SERPENT_KICK_AOE, true);
                }
            }
        }

        void Register() override
        {
            OnCast += SpellCastFn(spell_monk_flying_serpent_kick_SpellScript::HandleOnCast);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_monk_flying_serpent_kick_SpellScript();
    }
};

// 119582 - Purifying Brew
class spell_monk_purifying_brew : public SpellScript
{
    PrepareSpellScript(spell_monk_purifying_brew);

    SpellCastResult CheckCast()
    {
        if (Unit* caster = GetCaster())
            if (!caster->HasAura(SPELL_MONK_STAGGER))
                return SPELL_FAILED_CASTER_AURASTATE;

        return SPELL_CAST_OK;
    }

    void HandleOnHit()
    {
        if (Unit* caster = GetCaster())
        {
            Aura* visualAura = caster->GetAura(SPELL_MONK_LIGHT_STAGGER);
            Aura* staggerAura = caster->GetAura(SPELL_MONK_STAGGER);

            if (!visualAura)
                visualAura = caster->GetAura(SPELL_MONK_MODERATE_STAGGER);
            if (!visualAura)
                visualAura = caster->GetAura(SPELL_MONK_HEAVY_STAGGER);

            if (visualAura && staggerAura)
            {
                int32 newStagger = RoundingFloatValue(visualAura->GetEffect(EFFECT_1)->GetAmount() * 0.5f);
                uint32 remainingTicks = RoundingFloatValue((visualAura->GetMaxDuration() - visualAura->GetDuration()) / 500);
                int32 staggerPerTick = 1;
                if (remainingTicks > 0)
                    staggerPerTick = std::max(RoundingFloatValue(newStagger / remainingTicks), 1);

                // Update visual.
                uint32 staggerVisualSpellId;

                uint8 healthPercent = (uint8)RoundingFloatValue(newStagger * 100 / caster->GetMaxHealth());
                if (healthPercent >= 60)
                    staggerVisualSpellId = SPELL_MONK_HEAVY_STAGGER;
                else if (healthPercent > 30 && healthPercent <= 59)
                    staggerVisualSpellId = SPELL_MONK_MODERATE_STAGGER;
                else
                    staggerVisualSpellId = SPELL_MONK_LIGHT_STAGGER;

                if (staggerVisualSpellId == visualAura->GetSpellInfo()->Id)
                {
                    visualAura->GetEffect(EFFECT_0)->ChangeAmount(staggerPerTick);
                    visualAura->GetEffect(EFFECT_1)->ChangeAmount(newStagger);
                }
                else
                {
                    caster->RemoveAura(visualAura);
                    caster->CastCustomSpell(caster, staggerVisualSpellId, &staggerPerTick, &newStagger, 0, true);
                }

                // Update DOT amount.
                staggerAura->GetEffect(EFFECT_0)->SetDamage(staggerPerTick);
                staggerAura->GetEffect(EFFECT_1)->ChangeAmount(newStagger);

                // Hot Trub
                if (Aura* aura = caster->GetAura(SPELL_MONK_HOT_TRUB))
                    caster->CastCustomSpell(SPELL_MONK_HOT_TRUB_DAMAGE, SPELLVALUE_BASE_POINT10, CalculatePct(newStagger, aura->GetEffect(EFFECT_0)->GetBaseAmount()), caster, true);
            }
        }
    }

    void Register() override
    {
        OnCheckCast += SpellCheckCastFn(spell_monk_purifying_brew::CheckCast);
        OnHit += SpellHitFn(spell_monk_purifying_brew::HandleOnHit);
    }
};

// 115308 - Ironskin Brew
class spell_monk_ironskin_brew : public SpellScript
{
	PrepareSpellScript(spell_monk_ironskin_brew);

	void HandleEffectHit(SpellEffIndex effIndex)
	{
		if (Unit* caster = GetCaster())
			caster->CastSpell(caster, SPELL_MONK_IRONSKIN_BREW_AURA, true);
	}

	void Register() override
	{
		OnEffectHitTarget += SpellEffectFn(spell_monk_ironskin_brew::HandleEffectHit, EFFECT_0, SPELL_EFFECT_DUMMY);
	}
};

// 115175 - Soothing Mist
class aura_monk_soothing_mist : public AuraScript
{
	PrepareAuraScript(aura_monk_soothing_mist);

	void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
	{
		Unit* caster = GetCaster();
		Unit* target = GetUnitOwner();
		if (!caster || !target)
			return;

		Creature* creature = caster->GetSummonedCreatureByEntry(MONK_NPC_JADE_SERPENT_STATUE);
		if (creature && creature->ToUnit())
		{
			Unit* statue = creature->ToUnit();
            if (statue)
            {
                statue->CastStop();
                statue->CastSpell(target, SPELL_MONK_SOOTHING_MIST_STATUE, false);
                statue->SendPlaySpellVisual(target->GetGUID(), 24208, 0, 0, 15);
            }
		}
        else
            caster->SendPlaySpellVisual(target->GetGUID(), 24208, 0, 0, 15);
	}

	void OnRemove(AuraEffect const* /* aurEff */, AuraEffectHandleModes /*mode*/)
	{
		Unit* caster = GetCaster();
		Unit* target = GetUnitOwner();
		if (!caster || !target)
			return;

		if (target->HasAura(SPELL_MONK_SOOTHING_MIST_VISUAL))
			target->RemoveAura(SPELL_MONK_SOOTHING_MIST_VISUAL);
	}

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetTarget();
        if (!caster || !target)
            return;

        caster->SendPlaySpellVisual(target->GetGUID(), 24208, 0, 0, 15);

        if (caster->HasAura(SPELL_MONK_GUST_OF_MIST_MASTERY) && caster->IsPlayer())
        {
            uint32 mastery = caster->ToPlayer()->m_activePlayerData->Mastery;
            if (roll_chance_i(mastery))
            {
                float coeff = sSpellMgr->GetSpellInfo(SPELL_MONK_GUST_OF_MIST_MASTERY)->GetEffect(EFFECT_0).BonusCoefficient;
                int32 heal = CalculatePct(caster->GetTotalSpellPowerValue(SPELL_SCHOOL_MASK_NATURE, true), mastery * coeff);
                caster->CastCustomSpell(SPELL_MONK_GUST_OF_MIST, SPELLVALUE_BASE_POINT0, heal, target, true);
                if (target->HasAura(SPELL_MONK_ESSENCE_FONT_HEAL, caster->GetGUID()))
                    caster->CastCustomSpell(SPELL_MONK_GUST_OF_MIST, SPELLVALUE_BASE_POINT0, heal, target, true);
            }
        }
    }

	void Register() override
	{
		AfterEffectApply += AuraEffectApplyFn(aura_monk_soothing_mist::OnApply, EFFECT_0, SPELL_AURA_PERIODIC_HEAL, AURA_EFFECT_HANDLE_REAL);
		AfterEffectRemove += AuraEffectRemoveFn(aura_monk_soothing_mist::OnRemove, EFFECT_0, SPELL_AURA_PERIODIC_HEAL, AURA_EFFECT_HANDLE_REAL);
        OnEffectPeriodic += AuraEffectPeriodicFn(aura_monk_soothing_mist::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_HEAL);
	}
};

// Disable - 116095
class spell_monk_disable : public SpellScript
{
    PrepareSpellScript(spell_monk_disable);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_MONK_DISABLE, SPELL_MONK_DISABLE_ROOT });
    }

    void HandleOnEffectHitTarget(SpellEffIndex /*effectIndex*/)
    {
        if (Unit* target = GetExplTargetUnit())
            if (target->HasAuraType(SPELL_AURA_MOD_DECREASE_SPEED))
                GetCaster()->CastSpell(target, SPELL_MONK_DISABLE_ROOT, true);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_monk_disable::HandleOnEffectHitTarget, EFFECT_0, SPELL_EFFECT_APPLY_AURA);
    }
};

// Disable - 116095 Last Update 8.0.1 Build 28153
class aura_monk_disable : public AuraScript
{
    PrepareAuraScript(aura_monk_disable);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (DamageInfo* damageInfo = eventInfo.GetDamageInfo())
        {
            if ((damageInfo->GetAttackType() == BASE_ATTACK ||
                 damageInfo->GetAttackType() == OFF_ATTACK) &&
                damageInfo->GetAttacker() == GetCaster())                         
                return true;            
        }
        return false;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (Unit* target = eventInfo.GetActionTarget())
        {
            if (Aura* aura = GetAura())
            {
                uint32 duration = GetSpellInfo()->GetMaxDuration();
                if (target->IsPlayer()) //PVP DR for Snare Mechanic little hack because we change the duration here
                    duration = 8 * IN_MILLISECONDS;
                aura->SetDuration(duration);
                aura->SetMaxDuration(duration);
            }
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_monk_disable::CheckProc);
        AfterProc += AuraProcFn(aura_monk_disable::HandleProc);
    }
};

//232054 Heavy-Handed Strikes Last Update 8.0.1 Build 28153
class aura_heavy_handed_strikes : public AuraScript
{
    PrepareAuraScript(aura_heavy_handed_strikes);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == SPELL_MONK_FISTS_OF_FURY_DAMAGE;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_heavy_handed_strikes::CheckProc);
    }
};

// Zen Pilgrimage - 126892 and Zen Pilgrimage : Return - 126895
class spell_monk_zen_pilgrimage : public SpellScriptLoader
{
public:
    spell_monk_zen_pilgrimage() : SpellScriptLoader("spell_monk_zen_pilgrimage") { }

    class spell_monk_zen_pilgrimage_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_monk_zen_pilgrimage_SpellScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_MONK_ZEN_PILGRIMAGE) || !sSpellMgr->GetSpellInfo(SPELL_MONK_ZEN_PILGRIMAGE_RETURN))
                return false;
            return true;
        }

        void HandleDummy(SpellEffIndex effIndex)
        {
            PreventHitDefaultEffect(effIndex);
            PreventHitEffect(effIndex);

            if (Unit* caster = GetCaster())
            {
                if (Player* _player = caster->ToPlayer())
                {
                    if (GetSpellInfo()->Id == SPELL_MONK_ZEN_PILGRIMAGE)
                    {
                        _player->SaveRecallPosition();
                        //Class Order Hall
                        if (_player->GetLevel() >= 20)
                            _player->TeleportTo(1514, 882.933f, 3605.61f, 192.218f, _player->GetOrientation());
                        else
                            _player->TeleportTo(870, 3818.55f, 1793.18f, 950.35f, _player->GetOrientation());
                    }
                }
            }
        }

        void HandleScriptEffect(SpellEffIndex effIndex)
        {
            PreventHitDefaultEffect(effIndex);
            PreventHitEffect(effIndex);

            if (Unit* caster = GetCaster())
            {
                if (Player* _player = caster->ToPlayer())
                {
                    if (GetSpellInfo()->Id == SPELL_MONK_ZEN_PILGRIMAGE_RETURN)
                    {
                        _player->Recall();
                        _player->RemoveAura(126896);
                    }
                }
            }
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_monk_zen_pilgrimage_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_TELEPORT_UNITS);
            OnEffectHitTarget += SpellEffectFn(spell_monk_zen_pilgrimage_SpellScript::HandleScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_monk_zen_pilgrimage_SpellScript();
    }
};

// Last Update 8.0.1 Build 28153
// 115080 - Touch of Death
class spell_monk_touch_of_death : public SpellScript
{
    PrepareSpellScript(spell_monk_touch_of_death);

    void HandleBeforeHit(SpellMissInfo /*missInfo*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        uint32 damagePct = GetEffectInfo(EFFECT_1).BasePoints;

        if (target->IsPlayer())
            damagePct *= 0.5f;

        int32 damage = CalculatePct(caster->GetMaxHealth(), damagePct);
        if (damage)
            caster->CastCustomSpell(target, SPELL_MONK_TOUCH_OF_DEATH_DAMAGE_AMPLIFIER, &damage, nullptr, nullptr, true);
    }

    void Register() override
    {
        BeforeHit += BeforeSpellHitFn(spell_monk_touch_of_death::HandleBeforeHit);
    }
};

// Last Update 8.0.1 Build 28153
// 115080 - Touch of Death
class aura_monk_touch_of_death : public AuraScript
{
    PrepareAuraScript(aura_monk_touch_of_death);

    void OnTick(AuraEffect const* /*aurEff*/)
    {
		Unit* caster = GetCaster();
		Unit* target = GetUnitOwner();
		if (!caster || !target)
			return;

        int32 damage = GetAura()->GetEffect(EFFECT_0)->GetAmount();
        caster->CastCustomSpell(SPELL_MONK_TOUCH_OF_DEATH_DAMAGE, SPELLVALUE_BASE_POINT0, damage, target, true);
    }

	void CalculateAmount(AuraEffect const* aurEff, int32& amount, bool& canBeRecalculated)
	{
		canBeRecalculated = true;
		Unit* caster = GetCaster();
		Unit* target = GetUnitOwner();
		if (!caster || !target)
			return;

		if (Aura* aura = target->GetAura(SPELL_MONK_TOUCH_OF_DEATH_DAMAGE_AMPLIFIER, caster->GetGUID()))
			amount = aura->GetEffect(EFFECT_0)->GetAmount();
	}

    void Register() override
    {
		DoEffectCalcAmount += AuraEffectCalcAmountFn(aura_monk_touch_of_death::CalculateAmount, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
        OnEffectPeriodic += AuraEffectPeriodicFn(aura_monk_touch_of_death::OnTick, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

// 271233 - Touch of Death Amplifier
class aura_monk_touch_of_death_amplifer : public AuraScript
{
	PrepareAuraScript(aura_monk_touch_of_death_amplifer);

	bool CheckProc(ProcEventInfo& eventInfo)
	{
		if (Unit* caster = GetCaster())
			if (eventInfo.GetDamageInfo() && eventInfo.GetDamageInfo()->GetDamage() > 0 && eventInfo.GetDamageInfo()->GetAttacker() &&
				eventInfo.GetDamageInfo()->GetAttacker()->GetGUID() == caster->GetGUID())
				return true;

		return false;
	}

	void HandleProc(ProcEventInfo& eventInfo)
	{
		Unit* caster = GetCaster();
		Unit* target = GetUnitOwner();
		if (!caster || !target)
			return;

		uint32 damage = CalculatePct(eventInfo.GetDamageInfo()->GetDamage(), 10);
		if (Aura* aura = target->GetAura(SPELL_MONK_TOUCH_OF_DEATH, caster->GetGUID()))
		{
			uint32 currentAmount = aura->GetEffect(EFFECT_0)->GetAmount() + damage;
			GetAura()->GetEffect(EFFECT_0)->SetAmount(currentAmount);
			aura->GetEffect(EFFECT_0)->RecalculateAmount();
		}
	}

	void Register() override
	{
		DoCheckProc += AuraCheckProcFn(aura_monk_touch_of_death_amplifer::CheckProc);
		OnProc += AuraProcFn(aura_monk_touch_of_death_amplifer::HandleProc);
	}
};

// Fortifying brew - 115203
/// DISABLED, why is this casting itself?
class spell_monk_fortifying_brew : public SpellScriptLoader
{
public:
    spell_monk_fortifying_brew() : SpellScriptLoader("spell_monk_fortifying_brew") { }

    class spell_monk_fortifying_brew_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_monk_fortifying_brew_SpellScript);

        void HandleDummy(SpellEffIndex /*effIndex*/)
        {
            Unit* caster = GetCaster();
            if (caster && caster->GetTypeId() == TYPEID_PLAYER)
                caster->CastSpell(caster, SPELL_MONK_FORTIFYING_BREW, true);
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_monk_fortifying_brew_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_monk_fortifying_brew_SpellScript();
    }
};

// Legacy of the Emperor - 115921
class spell_monk_legacy_of_the_emperor : public SpellScriptLoader
{
public:
    spell_monk_legacy_of_the_emperor() : SpellScriptLoader("spell_monk_legacy_of_the_emperor") { }

    class spell_monk_legacy_of_the_emperor_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_monk_legacy_of_the_emperor_SpellScript);

        void HandleDummy(SpellEffIndex /*effIndex*/)
        {
            if (Player* plr = GetCaster()->ToPlayer())
            {
                std::list<Unit*> groupList;

                plr->GetPartyMembers(groupList);
                if (!groupList.empty())
                    for (auto itr : groupList)
                        plr->CastSpell(itr, SPELL_MONK_LEGACY_OF_THE_EMPEROR, true);
            }
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_monk_legacy_of_the_emperor_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_monk_legacy_of_the_emperor_SpellScript();
    }
};

// Brewing : Tigereye Brew - 123980
class spell_monk_tigereye_brew_stacks : public SpellScriptLoader
{
public:
    spell_monk_tigereye_brew_stacks() : SpellScriptLoader("spell_monk_tigereye_brew_stacks") { }

    class spell_monk_tigereye_brew_stacks_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_monk_tigereye_brew_stacks_AuraScript);

        uint32 chiConsumed;

        void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            chiConsumed = 0;
        }

        void SetData(uint32 /* type */, uint32 data)
        {
            while ((chiConsumed += data) >= 4)
            {
                chiConsumed = 0;
                data = data > 4 ? data - 4 : 0;

                if (GetCaster())
                    GetCaster()->CastSpell(GetCaster(), SPELL_MONK_TIGEREYE_BREW_STACKS, true);
            }
        }

        void Register() override
        {
            AfterEffectApply += AuraEffectApplyFn(spell_monk_tigereye_brew_stacks_AuraScript::OnApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_monk_tigereye_brew_stacks_AuraScript();
    }
};

// 117959 - Crackling Jade Lightning
class spell_monk_crackling_jade_lightning_knockback_proc_aura : public SpellScriptLoader
{
public:
    spell_monk_crackling_jade_lightning_knockback_proc_aura() : SpellScriptLoader("spell_monk_crackling_jade_lightning_knockback_proc_aura") { }

    class spell_monk_crackling_jade_lightning_aura_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_monk_crackling_jade_lightning_aura_AuraScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_MONK_CRACKLING_JADE_LIGHTNING_KNOCKBACK))
                return false;
            if (!sSpellMgr->GetSpellInfo(SPELL_MONK_CRACKLING_JADE_LIGHTNING_KNOCKBACK_CD))
                return false;
            return true;
        }

        bool CheckProc(ProcEventInfo& eventInfo)
        {
            Unit* target = GetTarget();

            if (target->HasAura(SPELL_MONK_CRACKLING_JADE_LIGHTNING_KNOCKBACK_CD))
                return false;

            auto channelObjects = target->GetChannelObjects();
            if (Unit* channelTarget = (channelObjects.size() == 1 ? ObjectAccessor::GetUnit(*target, *channelObjects.begin()) : nullptr))
                if (eventInfo.GetActor()->GetGUID() != channelTarget->GetGUID())
                    return false;

            Spell* currentChanneledSpell = target->GetCurrentSpell(CURRENT_CHANNELED_SPELL);
            if (!currentChanneledSpell || currentChanneledSpell->GetSpellInfo()->Id != SPELL_MONK_CRACKLING_JADE_LIGHTNING_CHANNEL)
                return false;

            return true;
        }

        void HandleProc(AuraEffect* /*aurEff*/, ProcEventInfo& eventInfo)
        {
            GetTarget()->CastSpell(eventInfo.GetActor(), SPELL_MONK_CRACKLING_JADE_LIGHTNING_KNOCKBACK, TRIGGERED_FULL_MASK);
            GetTarget()->CastSpell(GetTarget(), SPELL_MONK_CRACKLING_JADE_LIGHTNING_KNOCKBACK_CD, TRIGGERED_FULL_MASK);
        }

        void Register() override
        {
            DoCheckProc += AuraCheckProcFn(spell_monk_crackling_jade_lightning_aura_AuraScript::CheckProc);
            OnEffectProc += AuraEffectProcFn(spell_monk_crackling_jade_lightning_aura_AuraScript::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_monk_crackling_jade_lightning_aura_AuraScript();
    }
};

class spell_monk_breath_of_fire : public SpellScriptLoader
{
public:
    spell_monk_breath_of_fire() : SpellScriptLoader("spell_monk_breath_of_fire") { }

    class spell_monk_breath_of_fire_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_monk_breath_of_fire_SpellScript);

		void HandleAfterHit()
		{
			Unit* caster = GetCaster();
			Unit* target = GetHitUnit();
			if (!caster || !target)
				return;

			if (target->HasAura(SPELL_MONK_KEG_SMASH_AURA, caster->GetGUID()))
				caster->CastSpell(target, SPELL_MONK_BREATH_OF_FIRE_DOT, true);

			if (caster->HasAura(SPELL_MONK_INCENDIARY_BREATH))
				caster->CastSpell(target, SPELL_MONK_INCENDIARY_BREATH_DISORIENTED, true);
		}

        void Register() override
        {
            AfterHit += SpellHitFn(spell_monk_breath_of_fire_SpellScript::HandleAfterHit);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_monk_breath_of_fire_SpellScript();
    }
};

enum CracklingJade
{
    SPELL_MONK_CRACKLING_JADE_LIGHTNING                     = 117952,
    SPELL_MONK_CRACKLING_JADE_LIGHTNING_CHI_PROC_DRIVER     = 123332,
    SPELL_MONK_CRACKLING_JADE_LIGHTNING_KNOCK_BACK_DRIVER   = 117959,
    SPELL_MONK_CRACKLING_JADE_LIGHTNING_KNOCK_BACK          = 117962,
    SPELL_MONK_CRACKLING_JADE_LIGHTNING_TALENT              = 125648,
    SPELL_MONK_CRACKLING_JAD_LIGHTNING_TALENT_SPEED         = 125647,
};

// 117962 - crackling jade lightning knockback
class spell_monk_crackling_jade_knockback : public SpellScriptLoader
{
public:
    spell_monk_crackling_jade_knockback() : SpellScriptLoader("spell_monk_crackling_jade_knockback") { }

    class spell_monk_crackling_jade_knockback_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_monk_crackling_jade_knockback_SpellScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            return sSpellMgr->GetSpellInfo(SPELL_MONK_CRACKLING_JADE_LIGHTNING_KNOCK_BACK) != nullptr;
        }

        void Hit()
        {
            Unit* target = GetHitUnit();
            Unit* caster = GetCaster();
            if (caster && target && caster->HasAura(SPELL_MONK_CRACKLING_JADE_LIGHTNING_TALENT))
                caster->CastSpell(target, SPELL_MONK_CRACKLING_JAD_LIGHTNING_TALENT_SPEED, true);
        }

        void Register() override
        {
            AfterHit += SpellHitFn(spell_monk_crackling_jade_knockback_SpellScript::Hit);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_monk_crackling_jade_knockback_SpellScript();
    }
};

class spell_monk_power_strikes : public SpellScriptLoader
{
public:
    spell_monk_power_strikes() : SpellScriptLoader("spell_monk_power_strikes") { }

    class spell_monk_power_strikes_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_monk_power_strikes_SpellScript);

        void HandleOnHit()
        {
            if (Player* _player = GetCaster()->ToPlayer())
            {
                if (Unit* target = GetHitUnit())
                {
                    if (target->GetGUID() != _player->GetGUID())
                    {
                        if (_player->HasAura(SPELL_MONK_POWER_STRIKES_TALENT))
                        {
                            if (!_player->GetSpellHistory()->HasCooldown(SPELL_MONK_POWER_STRIKES_TALENT))
                            {
                                if (_player->GetPower(POWER_CHI) < _player->GetMaxPower(POWER_CHI))
                                {
                                    _player->EnergizeBySpell(_player, GetSpellInfo(), 1, POWER_CHI);
                                    _player->GetSpellHistory()->AddCooldown(SPELL_MONK_POWER_STRIKES_TALENT, 0, std::chrono::seconds(20));
                                }
                                else
                                    _player->CastSpell(_player, SPELL_MONK_CREATE_CHI_SPHERE, true);
                            }
                        }
                    }
                }
            }
        }

        void Register() override
        {
            OnHit += SpellHitFn(spell_monk_power_strikes_SpellScript::HandleOnHit);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_monk_power_strikes_SpellScript();
    }
};

class spell_monk_spear_hand_strike : public SpellScriptLoader
{
public:
    spell_monk_spear_hand_strike() : SpellScriptLoader("spell_monk_spear_hand_strike") { }

    class spell_monk_spear_hand_strike_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_monk_spear_hand_strike_SpellScript);

        void HandleOnHit()
        {
            if (Player* _player = GetCaster()->ToPlayer())
            {
                if (Unit* target = GetHitUnit())
                {
                    if (target->isInFront(_player))
                    {
                        _player->CastSpell(target, SPELL_MONK_SPEAR_HAND_STRIKE_SILENCE, true);
                        _player->GetSpellHistory()->AddCooldown(116705, 0, std::chrono::seconds(15));
                    }
                }
            }
        }

        void Register() override
        {
            OnHit += SpellHitFn(spell_monk_spear_hand_strike_SpellScript::HandleOnHit);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_monk_spear_hand_strike_SpellScript();
    }
};

// 124273 - Heavy Stagger
// 124274 - Moderate Stagger
// 124275 - Light Stagger
class spell_monk_stagger_visual : public AuraScript
{
    PrepareAuraScript(spell_monk_stagger_visual);

    void HandleRemove(AuraEffect const* /*auraEffect*/, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* target = GetTarget())
            target->RemoveAura(SPELL_MONK_STAGGER);
    }

    void Register() override
    {
        OnEffectRemove += AuraEffectRemoveFn(spell_monk_stagger_visual::HandleRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

// 115069 - Stagger
class aura_monk_stagger : public AuraScript
{
    PrepareAuraScript(aura_monk_stagger);

    void CalculateAmount(const AuraEffect* /*aurEff*/, int32& amount, bool & /*canBeRecalculated*/)
    {
        amount = -1;
    }

    void HandleAbsorb(AuraEffect* auraEffect, DamageInfo& dmgInfo, uint32& absorbAmount)
    {
        if (dmgInfo.GetSpellInfo() && dmgInfo.GetSpellInfo()->Id == SPELL_MONK_STAGGER)
            return;

        if (Unit* caster = GetCaster())
        {
            // Stagger Reduction = Base Stagger / (Base Stagger + K)
            // Base Stagger = 1.4 * Agility
            // Spells are 35% only.
            uint8 eff = (auraEffect->GetEffIndex() == EFFECT_1) ? 100 : 35;

            int32 K = sDB2Manager.EvaluateExpectedStat(ExpectedStatType::ArmorConstant, caster->GetLevel(), -2, 0, Classes(caster->GetClass()));
            // Modifiers
            uint8 modifier = 0;
            if (caster->HasAura(SPELL_MONK_IRONSKIN_BREW_AURA))
                modifier = 250;
            if (caster->HasAura(SPELL_MONK_HIGH_TOLERANCE))
                modifier = 40;
            if (caster->HasAura(SPELL_MONK_FORTIFYING_BREW))
                modifier = 10;

            float baseStagger = CalculatePct(caster->GetStat(STAT_AGILITY), sSpellMgr->GetSpellInfo(SPELL_MONK_STAGGER_AURA)->GetEffect(EFFECT_0).BasePoints + modifier);
            float staggerPct = baseStagger / (baseStagger + K) * 100;

            // Stagger Reduction
            int32 staggerAmount = CalculatePct(dmgInfo.GetDamage(), staggerPct);

            // Stagger Eff (35% only for spells)
            staggerAmount = CalculatePct(staggerAmount, eff);

            absorbAmount = staggerAmount;

            int32 duration = sSpellMgr->GetSpellInfo(SPELL_MONK_HEAVY_STAGGER)->GetMaxDuration();
            int32 ticks = duration / 500;

            uint8 healthPercent = RoundingFloatValue(staggerAmount * 100 / caster->GetMaxHealth());

            uint32 staggerVisualSpellId;
            if (healthPercent >= 60)
                staggerVisualSpellId = SPELL_MONK_HEAVY_STAGGER;
            else if (healthPercent > 30 && healthPercent < 60)
                staggerVisualSpellId = SPELL_MONK_MODERATE_STAGGER;
            else
                staggerVisualSpellId = SPELL_MONK_LIGHT_STAGGER;

            int32 staggerPerTick = std::max(RoundingFloatValue(staggerAmount / ticks), 1);

            if (Aura* damageAura = caster->GetAura(SPELL_MONK_STAGGER))
            {
                int32 currentTotalAmount = 0;
                Aura* visualAura = nullptr;

                if (caster->HasAura(SPELL_MONK_LIGHT_STAGGER))
                    visualAura = caster->GetAura(SPELL_MONK_LIGHT_STAGGER);
                else if (caster->HasAura(SPELL_MONK_MODERATE_STAGGER))
                    visualAura = caster->GetAura(SPELL_MONK_MODERATE_STAGGER);
                else if (caster->HasAura(SPELL_MONK_HEAVY_STAGGER))
                    visualAura = caster->GetAura(SPELL_MONK_HEAVY_STAGGER);

                if (!visualAura)
                    return;

                currentTotalAmount = visualAura->GetEffect(EFFECT_1)->GetAmount();
                uint32 remainingTicks = RoundingFloatValue((duration - visualAura->GetDuration()) / 500);

                staggerAmount += currentTotalAmount;
                if (remainingTicks > 0)
                    staggerPerTick = std::max(RoundingFloatValue(staggerAmount / remainingTicks), 1);
                else
                    staggerPerTick = 1;

                uint8 healthPercent = (uint8)RoundingFloatValue(staggerAmount * 100 / caster->GetMaxHealth());

                uint32 staggerVisualSpellId;

                if (healthPercent >= 60)
                    staggerVisualSpellId = SPELL_MONK_HEAVY_STAGGER;
                else if (healthPercent > 30 && healthPercent < 60)
                    staggerVisualSpellId = SPELL_MONK_MODERATE_STAGGER;
                else
                    staggerVisualSpellId = SPELL_MONK_LIGHT_STAGGER;

                if (staggerVisualSpellId == visualAura->GetSpellInfo()->Id)
                {
                    visualAura->GetEffect(EFFECT_0)->ChangeAmount(staggerPerTick);
                    visualAura->GetEffect(EFFECT_1)->ChangeAmount(staggerAmount);
                }
                else
                {
                    caster->RemoveAura(visualAura);
                    caster->CastCustomSpell(caster, staggerVisualSpellId, &staggerPerTick, &staggerAmount, 0, true);
                }

                // Update DOT amount.
                damageAura->GetEffect(EFFECT_0)->SetDamage(staggerPerTick);
                damageAura->GetEffect(EFFECT_1)->ChangeAmount(staggerAmount);
            }
            else
            {
                caster->CastCustomSpell(caster, staggerVisualSpellId, &staggerPerTick, &staggerAmount, 0, true);
                caster->CastCustomSpell(caster, SPELL_MONK_STAGGER, &staggerPerTick, &staggerAmount, 0, true);
            }
        }
    }

    void Register() override
    {
        DoEffectCalcAmount += AuraEffectCalcAmountFn(aura_monk_stagger::CalculateAmount, EFFECT_1, SPELL_AURA_SCHOOL_ABSORB);
        DoEffectCalcAmount += AuraEffectCalcAmountFn(aura_monk_stagger::CalculateAmount, EFFECT_2, SPELL_AURA_SCHOOL_ABSORB);
        OnEffectAbsorb += AuraEffectAbsorbFn(aura_monk_stagger::HandleAbsorb, EFFECT_1);
        OnEffectAbsorb += AuraEffectAbsorbFn(aura_monk_stagger::HandleAbsorb, EFFECT_2);
    }
};

// 124255 - Stagger Damage
class aura_monk_stagger_damage : public AuraScript
{
    PrepareAuraScript(aura_monk_stagger_damage);

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
        if (Unit* caster = GetCaster())
        {
            if (!caster->HasAura(SPELL_MONK_LIGHT_STAGGER) && !caster->HasAura(SPELL_MONK_MODERATE_STAGGER) && !caster->HasAura(SPELL_MONK_HEAVY_STAGGER))
            {
                    PreventDefaultAction();
                    caster->RemoveAura(SPELL_MONK_STAGGER);
            }

            Aura* visualAura = nullptr;
            if (caster->HasAura(SPELL_MONK_LIGHT_STAGGER))
                visualAura = caster->GetAura(SPELL_MONK_LIGHT_STAGGER);
            else if (caster->HasAura(SPELL_MONK_MODERATE_STAGGER))
                visualAura = caster->GetAura(SPELL_MONK_MODERATE_STAGGER);
            else if (caster->HasAura(SPELL_MONK_HEAVY_STAGGER))
                visualAura = caster->GetAura(SPELL_MONK_HEAVY_STAGGER);

            if (!visualAura || !visualAura->GetEffect(EFFECT_1)->GetAmount() || !visualAura->GetEffect(EFFECT_0)->GetAmount())
                return;

            int32 newAmount = (visualAura->GetEffect(EFFECT_1)->GetAmount() - visualAura->GetEffect(EFFECT_0)->GetAmount());
            if (newAmount <= 0)
            {
                caster->RemoveAura(SPELL_MONK_LIGHT_STAGGER);
                caster->RemoveAura(SPELL_MONK_MODERATE_STAGGER);
                caster->RemoveAura(SPELL_MONK_HEAVY_STAGGER);
                caster->RemoveAura(SPELL_MONK_STAGGER);
            }
    		else
	    		visualAura->GetEffect(EFFECT_1)->ChangeAmount(newAmount);
        }
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(aura_monk_stagger_damage::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE);
    }
};

enum TigerLust
{
    SPELL_MONK_TIGER_LUST = 116841,
};

// 116841 - tiger's lust
class spell_monk_tiger_lust : public SpellScriptLoader
{
public:
    spell_monk_tiger_lust() : SpellScriptLoader("spell_monk_tiger_lust") {}

    class spell_monk_tiger_lust_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_monk_tiger_lust_SpellScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            return sSpellMgr->GetSpellInfo(SPELL_MONK_TIGER_LUST) != nullptr;
        }

        void HandleDummy(SpellEffIndex /*effIndex*/)
        {
            if (Unit* target = GetHitUnit())
                target->RemoveMovementImpairingAuras(true);
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_monk_tiger_lust_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_APPLY_AURA);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_monk_tiger_lust_SpellScript();
    }
};

//Called by 122470 Touch of Karma
//Last update 8.0.1 Build 28153
class spell_monk_touch_of_karma : public SpellScriptLoader
{
public:
    spell_monk_touch_of_karma() : SpellScriptLoader("spell_monk_touch_of_karma") { }

    class spell_monk_touch_of_karma_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_monk_touch_of_karma_AuraScript);

        bool fullyAbsorbed = false;
        uint32 totalAbsorbAmount = 0;
        uint32 maxAbsorbAmount = 0;
        ObjectGuid targetGuid;

        bool Load() override
        {
            totalAbsorbAmount = 0;
            targetGuid = ObjectGuid::Empty;
            return true;
        }

        void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if (Unit* caster = GetCaster())
                if (Unit* target = GetTarget())
                    targetGuid = target->GetGUID();
        }

        void AfterRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if (Unit* caster = GetCaster())
                if (Unit* target = ObjectAccessor::GetUnit(*caster, targetGuid))
                    if (target->HasAura(GetSpellInfo()->Id, caster->GetGUID()))
                        target->RemoveAura(GetSpellInfo()->Id);
        }

        void CalculateAmount(const AuraEffect* /*aurEff*/, int32& amount, bool & /*canBeRecalculated*/)
        {
            if (GetCaster())
            {
                amount = CalculatePct(GetCaster()->GetMaxHealth(), GetSpellInfo()->GetEffect(EFFECT_2).BasePoints);
                maxAbsorbAmount = CalculatePct(amount, 70);
            }
        }

        void AfterAbsorb(AuraEffect* aurEff, DamageInfo& dmgInfo, uint32& absorbAmount)
        {
            if (fullyAbsorbed)
                return;

            if (Unit* caster = dmgInfo.GetVictim())
            {
                if (Player* player = caster->ToPlayer())
                {   
                    if (Unit* attacker = dmgInfo.GetAttacker())
                    {
                        if (attacker->HasAura(aurEff->GetSpellInfo()->Id, caster->GetGUID()))
                        {
                            totalAbsorbAmount += absorbAmount;

                            if (totalAbsorbAmount >= maxAbsorbAmount)
                            {
                                totalAbsorbAmount = maxAbsorbAmount;
                                fullyAbsorbed = true;
                            }

                            if (totalAbsorbAmount)
                            {
                                caster->CastSpell(attacker, SPELL_MONK_TOUCH_OF_KARMA_REDIRECT_DAMAGE, CastSpellExtraArgs(true).AddSpellBP0(totalAbsorbAmount));
                            }
                        }                        
                    }
                }
            }
        }

        void Register() override
        {
            OnEffectApply += AuraEffectApplyFn(spell_monk_touch_of_karma_AuraScript::OnApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            AfterEffectRemove += AuraEffectRemoveFn(spell_monk_touch_of_karma_AuraScript::AfterRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_monk_touch_of_karma_AuraScript::CalculateAmount, EFFECT_1, SPELL_AURA_SCHOOL_ABSORB);
            AfterEffectAbsorb += AuraEffectAbsorbFn(spell_monk_touch_of_karma_AuraScript::AfterAbsorb, EFFECT_1);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_monk_touch_of_karma_AuraScript();
    }
};

// 101643
class spell_monk_transcendence : public SpellScript
{
public:
    PrepareSpellScript(spell_monk_transcendence);

    void HandleSummon(Creature* creature)
    {
		if (!creature)
			return;

		if (Unit* caster = GetCaster())
		{
			DespawnSpirit(caster);
			caster->CastSpell(creature, SPELL_MONK_TRANSCENDENCE_CLONE_TARGET, true);
            creature->CastSpell(creature, SPELL_MONK_MEDITATE_VISUAL, true);
			caster->Variables.Set(MONK_TRANSCENDENCE_GUID, creature->GetGUID());
            caster->CastSpell(caster, SPELL_MONK_TRASCENDENCE_ALLOW_CAST, true);
        }
    }

    static Creature* GetSpirit(Unit* caster)
    {
        ObjectGuid spiritGuid = caster->Variables.GetValue<ObjectGuid>(MONK_TRANSCENDENCE_GUID, ObjectGuid::Empty);

        if (spiritGuid.IsEmpty())
            return nullptr;

        return ObjectAccessor::GetCreature(*caster, spiritGuid);
    }

    static void DespawnSpirit(Unit* caster)
    {
        // Remove previous one if any
        if (Creature* spirit = GetSpirit(caster))
            spirit->DespawnOrUnsummon();

        caster->Variables.Remove(MONK_TRANSCENDENCE_GUID);
    }

    void Register() override
    {
        OnEffectSummon += SpellOnEffectSummonFn(spell_monk_transcendence::HandleSummon);
    }
};

// 101643
class aura_monk_transcendence : public AuraScript
{
    PrepareAuraScript(aura_monk_transcendence);

    void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
		if (Unit* caster = GetCaster())
		{
			caster->RemoveAura(SPELL_MONK_TRASCENDENCE_ALLOW_CAST);
			spell_monk_transcendence::DespawnSpirit(caster);
        }
    }

    void Register() override
    {
        OnEffectRemove += AuraEffectRemoveFn(aura_monk_transcendence::OnRemove, EFFECT_1, SPELL_AURA_PERIODIC_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

// 119996 - Transcendence: Transfer
class spell_monk_transcendence_transfer : public SpellScript
{
    PrepareSpellScript(spell_monk_transcendence_transfer);

    SpellCastResult CheckCast()
    {
        Unit* caster = GetCaster();

        if (!caster)
            return SPELL_FAILED_ERROR;

        Unit* spirit = spell_monk_transcendence::GetSpirit(caster);
        if (!spirit)
            return SPELL_FAILED_NO_PET;

        if (!spirit->IsWithinDist(caster, GetSpellInfo()->GetMaxRange(true, caster, GetSpell())))
            return SPELL_FAILED_OUT_OF_RANGE;

        return SPELL_CAST_OK;
    }

    void HandleOnCast()
    {
        Unit* caster = GetCaster();
        if (!caster)
            return;

        Unit* spirit = spell_monk_transcendence::GetSpirit(caster);
        if (!spirit)
            return;

        caster->NearTeleportTo(*spirit, true);
        spirit->NearTeleportTo(*caster, true);
    }

	void HandleAfterCast()
	{
		if (Unit* caster = GetCaster())
			caster->RemoveAura(SPELL_MONK_TRASCENDENCE_ALLOW_CAST);
	}

    void Register() override
    {
        OnCheckCast += SpellCheckCastFn(spell_monk_transcendence_transfer::CheckCast);
        OnCast += SpellCastFn(spell_monk_transcendence_transfer::HandleOnCast);
		AfterCast += SpellCastFn(spell_monk_transcendence_transfer::HandleAfterCast);
    }
};

// 100780
class spell_monk_jab : public SpellScriptLoader
{
public:
    spell_monk_jab() : SpellScriptLoader("spell_monk_jab") { }

    class spell_monk_jab_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_monk_jab_SpellScript);

    public:
        spell_monk_jab_SpellScript() : SpellScript() { }

        void HandleProc()
        {
            Unit* caster = GetCaster();
            if (AuraEffect* comboBreaker = caster->GetAuraEffect(137384, EFFECT_0))
            {
                if (roll_chance_i(comboBreaker->GetAmount()))
                {
                    uint32 spellId = 116768;
                    if (roll_chance_i(50))
                        spellId = 118864;

                    caster->CastSpell(caster, spellId, true);
                }
            }
        }

        void Register() override
        {
            OnHit += SpellHitFn(spell_monk_jab_SpellScript::HandleProc);
        }

    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_monk_jab_SpellScript();
    }
};

// 115098 - Chi Wave
class spell_monk_chi_wave : public SpellScript
{
	PrepareSpellScript(spell_monk_chi_wave);

	void HandleDummy(SpellEffIndex /*effIndex*/)
	{
		Unit* caster = GetCaster();
		Unit* target = GetHitUnit();
		if (!target)
			return;

        caster->Variables.Remove("chiWaveJumps");
		if (caster->IsFriendlyTo(target))
		{
			caster->SendPlaySpellVisual(target->GetGUID(), 38379, 0, 0, 20);
			caster->CastCustomSpell(SPELL_MONK_CHI_WAVE_HEALING_BOLT, SPELLVALUE_BASE_POINT1, GetEffectValue(), target, true);
		}
		else if (caster->IsValidAttackTarget(target))
		{
			caster->SendPlaySpellVisual(target->GetGUID(), 38378, 0, 0, 20);
			caster->CastCustomSpell(SPELL_MONK_CHI_WAVE_DAMAGE_TARGET, SPELLVALUE_BASE_POINT1, GetEffectValue(), target, true);
		}
	}

	void Register() override
	{
		OnEffectHitTarget += SpellEffectFn(spell_monk_chi_wave::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
	}
};

class spell_monk_fists_of_fury_visual_filter : public SpellScriptLoader
{
public:
    spell_monk_fists_of_fury_visual_filter() : SpellScriptLoader("spell_monk_fists_of_fury_visual_filter") { }

    class spell_monk_fists_of_fury_visual_filter_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_monk_fists_of_fury_visual_filter_SpellScript);

        void RemoveInvalidTargets(std::list<WorldObject*>& targets)
        {
            targets.remove_if(Trinity::UnitAuraCheck(true, 123154, GetCaster()->GetGUID()));
        }

        void Register() override
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_monk_fists_of_fury_visual_filter_SpellScript::RemoveInvalidTargets, EFFECT_1, TARGET_UNIT_CONE_ENEMY_24);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_monk_fists_of_fury_visual_filter_SpellScript();
    }
};

class spell_monk_fists_of_fury_visual : public SpellScriptLoader
{
public:
    spell_monk_fists_of_fury_visual() : SpellScriptLoader("spell_monk_fists_of_fury_visual") { }

    class spell_monk_fists_of_fury_visual_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_monk_fists_of_fury_visual_AuraScript);

        void OnApply(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            SetMaxDuration(1000); //The spell doesn't have a duration on WoWHead and never ends if we don't give it one, so one sec should be good
            SetDuration(1000);    //Same as above
        }

        void Register() override
        {
            OnEffectApply += AuraEffectApplyFn(spell_monk_fists_of_fury_visual_AuraScript::OnApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_monk_fists_of_fury_visual_AuraScript();
    }
};

// 115546 - Provoke
class spell_monk_provoke : public SpellScriptLoader
{
public:
    spell_monk_provoke() : SpellScriptLoader("spell_monk_provoke") { }

    class spell_monk_provoke_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_monk_provoke_SpellScript);

        static uint32 const BlackOxStatusEntry = 61146;

        bool Validate(SpellInfo const* spellInfo) override
        {
            if (!(spellInfo->GetExplicitTargetMask() & TARGET_FLAG_UNIT_MASK)) // ensure GetExplTargetUnit() will return something meaningful during CheckCast
                return false;
            if (!sSpellMgr->GetSpellInfo(SPELL_MONK_PROVOKE_SINGLE_TARGET))
                return false;
            if (!sSpellMgr->GetSpellInfo(SPELL_MONK_PROVOKE_AOE))
                return false;
            return true;
        }

        SpellCastResult CheckExplicitTarget()
        {
            if (GetExplTargetUnit()->GetEntry() != BlackOxStatusEntry)
            {
                SpellInfo const* singleTarget = sSpellMgr->AssertSpellInfo(SPELL_MONK_PROVOKE_SINGLE_TARGET);
                SpellCastResult singleTargetExplicitResult = singleTarget->CheckExplicitTarget(GetCaster(), GetExplTargetUnit());
                if (singleTargetExplicitResult != SPELL_CAST_OK)
                    return singleTargetExplicitResult;
            }
            else if (GetExplTargetUnit()->GetOwnerGUID() != GetCaster()->GetGUID())
                return SPELL_FAILED_BAD_TARGETS;

            return SPELL_CAST_OK;
        }

        void HandleDummy(SpellEffIndex effIndex)
        {
			PreventHitDefaultEffect(effIndex);
			Unit* target = GetHitUnit();
			Unit* expTarget = GetExplTargetUnit();
			if (!target && !expTarget)
				return;

			if (Unit* caster = GetCaster())
			{
				if (expTarget->GetEntry() != BlackOxStatusEntry)
					caster->CastSpell(GetHitUnit(), SPELL_MONK_PROVOKE_SINGLE_TARGET, true);
				else
					expTarget->CastSpell(GetHitUnit(), SPELL_MONK_PROVOKE_AOE, true);
			}
        }

        void Register() override
        {
            OnCheckCast += SpellCheckCastFn(spell_monk_provoke_SpellScript::CheckExplicitTarget);
            OnEffectHitTarget += SpellEffectFn(spell_monk_provoke_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_monk_provoke_SpellScript();
    }
};

// 227344 - Surging Mist
class spell_monk_surging_mist : public SpellScript
{
	PrepareSpellScript(spell_monk_surging_mist);

    void HandlePrepare()
    {
        if (Unit* caster = GetCaster())
            if (Spell* spell = GetSpell())
            {
                if (spell->GetTriggeredCastFlags() & TRIGGERED_CAST_DIRECTLY)
                    return;

                if (Spell* currentSpell = caster->GetCurrentSpell(CURRENT_CHANNELED_SPELL))
                    if (currentSpell->GetSpellInfo()->Id == SPELL_MONK_SOOTHING_MIST)
                    {
                        Unit* target = currentSpell->GetUnitTarget();
                        Unit* selfTarget = spell->GetUnitTarget();
                        if (!target || !selfTarget)
                            return;

                        if (!target->IsInWorld() || !selfTarget->IsInWorld())
                            return;

                        if (target->GetGUID() == selfTarget->GetGUID())
                        {
                            TriggerCastFlags flags = TriggerCastFlags(spell->GetTriggeredCastFlags() | TRIGGERED_CAST_DIRECTLY);
                            spell->SetTriggerCastFlags(flags);
                        }
                    }
            }
    }

	void Register() override
	{
		OnPrepare += SpellOnPrepareFn(spell_monk_surging_mist::HandlePrepare);
	}
};

// 123273 - Surging Mist (Glyphed)
class spell_monk_surging_mist_glyphed : public SpellScriptLoader
{
public:
    spell_monk_surging_mist_glyphed() : SpellScriptLoader("spell_monk_surging_mist_glyphed") { }

    class spell_monk_surging_mist_glyphed_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_monk_surging_mist_glyphed_SpellScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_MONK_SURGING_MIST_HEAL))
                return false;
            if (!sSpellMgr->GetSpellInfo(SPELL_MONK_SOOTHING_MIST))
                return false;
            return true;
        }

        void SelectTarget(std::list<WorldObject*>& targets)
        {
            Unit* caster = GetCaster();
            if (caster->GetChannelSpellId() == SPELL_MONK_SOOTHING_MIST)
            {
                targets.clear();
                auto channelObjects = caster->GetChannelObjects();

                if (Unit* soothingMistTarget = (channelObjects.size() == 1 ? ObjectAccessor::GetUnit(*caster, *channelObjects.begin()) : nullptr))
                    targets.push_back(soothingMistTarget);
            }
            else
            {
                targets.remove_if([caster](WorldObject* target)
                {
                    return target->GetTypeId() != TYPEID_UNIT || !target->ToUnit()->IsInRaidWith(caster);
                });
                targets.sort(Trinity::HealthPctOrderPred());
                if (!targets.empty())
                    targets.resize(1);
            }

            if (targets.empty())
                targets.push_back(caster);
        }

        void HandleDummy(SpellEffIndex effIndex)
        {
            PreventHitDefaultEffect(effIndex);
            GetCaster()->CastSpell(GetHitUnit(), SPELL_MONK_SURGING_MIST_HEAL, true);
        }

        void Register() override
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_monk_surging_mist_glyphed_SpellScript::SelectTarget, EFFECT_0, TARGET_UNIT_SRC_AREA_ALLY);
            OnEffectHitTarget += SpellEffectFn(spell_monk_surging_mist_glyphed_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_monk_surging_mist_glyphed_SpellScript();
    }
};

// Rising Thunder - 210804
class spell_monk_rising_thunder : public SpellScriptLoader
{
public:
    spell_monk_rising_thunder() : SpellScriptLoader("spell_monk_rising_thunder") { }

    class spell_monk_rising_thunder_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_monk_rising_thunder_AuraScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_MONK_RISING_THUNDER))
                return false;
            return true;
        }

        void HandleEffectProc(AuraEffect* /*aurEff*/, ProcEventInfo& /*eventInfo*/)
        {
            Unit* caster = GetCaster();

            caster->ToPlayer()->GetSpellHistory()->ResetCooldown(SPELL_MONK_THUNDER_FOCUS_TEA, true);
        }

        void Register() override
        {
            OnEffectProc += AuraEffectProcFn(spell_monk_rising_thunder_AuraScript::HandleEffectProc, EFFECT_0, SPELL_AURA_DUMMY);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_monk_rising_thunder_AuraScript();
    }
};

// Teachings of the Monastery - 116645
//Last Update 8.0.1 Build 28153
class aura_monk_teachings_of_the_monastery : public AuraScript
{
    PrepareAuraScript(aura_monk_teachings_of_the_monastery);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        if (!sSpellMgr->GetSpellInfo(SPELL_MONK_TEACHINGS_OF_THE_MONASTERY_AURA))
            return false;
        return true;
    }

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetSpellInfo()->Id == SPELL_MONK_TIGER_PALM)
            return true;

        return false;
    }

    void HandleProc(AuraEffect* aurEff, ProcEventInfo& eventInfo)
    {
        if(Unit* target = GetTarget())
            target->CastSpell(target, SPELL_MONK_TEACHINGS_OF_THE_MONASTERY_AURA, true);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_monk_teachings_of_the_monastery::CheckProc);
        OnEffectProc += AuraEffectProcFn(aura_monk_teachings_of_the_monastery::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

// 202090 - Teachings of the monastery (Buff)
//Last Update 8.0.1 Build 28153
class aura_monk_teachings_of_the_monastery_buff : public AuraScript
{
    PrepareAuraScript(aura_monk_teachings_of_the_monastery_buff);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!GetTarget()->HasAura(SPELL_MONK_TEACHINGS_OF_THE_MONASTERY))
            return false;

        if (eventInfo.GetSpellInfo()->Id != SPELL_MONK_BLACKOUT_KICK)
            return false;

        return true;
    }

    void HandleProc(AuraEffect* /*aurEff*/, ProcEventInfo& eventInfo)
    {
        if (Aura* monasteryBuff = GetAura())
        {
            for (uint8 i = 0; i < monasteryBuff->GetStackAmount(); ++i)
                GetTarget()->CastSpell(eventInfo.GetProcTarget(), SPELL_MONK_BLACKOUT_KICK_TRIGGERED, true);
            monasteryBuff->Remove();
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_monk_teachings_of_the_monastery_buff::CheckProc);
        OnEffectProc += AuraEffectProcFn(aura_monk_teachings_of_the_monastery_buff::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

// Rising Sun Kick - 107428
class spell_monk_rising_sun_kick : public SpellScriptLoader
{
public:
    spell_monk_rising_sun_kick() : SpellScriptLoader("spell_monk_rising_sun_kick") { }

    class spell_monk_rising_sun_kick_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_monk_rising_sun_kick_SpellScript);

        void HandleOnHit(SpellEffIndex /*effIndex*/)
        {
            Unit* caster = GetCaster();
            Unit* target = GetHitUnit();
            if (!target || !caster)
                return;

            if (caster->HasAura(SPELL_MONK_RISING_THUNDER))
                caster->GetSpellHistory()->ResetCooldown(SPELL_MONK_THUNDER_FOCUS_TEA, true);

            if (caster->ToPlayer() && caster->ToPlayer()->GetSpecializationId() == TALENT_SPEC_MONK_BATTLEDANCER)
                caster->CastSpell(target, SPELL_MONK_MORTAL_WOUNDS, true);

            // Thunder Tea.
            if (Aura* aura = caster->GetAura(SPELL_MONK_THUNDER_FOCUS_TEA))
                aura->ModStackAmount(-1);

            if (caster->HasAura(SPELL_MONK_CYCLONE_STRIKES_AURA))
            {
                for (ObjectGuid guid : caster->damagedTargets)
                    if (guid == target->GetGUID())
                        return;

                // Target is not in the list, push the target
                caster->damagedTargets.push_back(target->GetGUID());

                uint32 currentDuration = 0;
                if (Aura* aura = caster->GetAura(SPELL_MONK_CYCLONE_STRIKES))
                    currentDuration = aura->GetDuration();
                else
                    currentDuration = 15 * IN_MILLISECONDS;

                caster->CastSpell(caster, SPELL_MONK_CYCLONE_STRIKES, true);
                if (Aura* aura = caster->GetAura(SPELL_MONK_CYCLONE_STRIKES))
                    aura->SetDuration(currentDuration);
            }
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_monk_rising_sun_kick_SpellScript::HandleOnHit, EFFECT_0, SPELL_EFFECT_TRIGGER_SPELL);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_monk_rising_sun_kick_SpellScript();
    }
};

// Blackout Kick - 100784
class spell_monk_blackout_kick : public SpellScriptLoader
{
public:
    spell_monk_blackout_kick() : SpellScriptLoader("spell_monk_blackout_kick") { }

    class spell_monk_blackout_kick_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_monk_blackout_kick_SpellScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            return ValidateSpellInfo({
                SPELL_MONK_BLACKOUT_KICK,
                SPELL_MONK_FISTS_OF_FURY,
                SPELL_MONK_RISING_SUN_KICK,
                SPELL_MONK_TEACHINGS_OF_THE_MONASTERY,
                SPELL_MONK_TEACHINGS_OF_THE_MONASTERY_AURA });
        }

        void HandleOnHit(SpellEffIndex /*effIndex*/)
        {
            Unit* caster = GetCaster();

            if (!caster)
                return;

            Unit* target = GetHitUnit();

            if (!target)
                return;            

            if (Player* player = caster->ToPlayer())
            {
                if (player->GetSpecializationId() == TALENT_SPEC_MONK_BATTLEDANCER)
                {
                    if (auto spellHistory = player->GetSpellHistory())
                    {
                        spellHistory->ModifyCooldown(SPELL_MONK_FISTS_OF_FURY, -1s);
                        spellHistory->ModifyCooldown(SPELL_MONK_RISING_SUN_KICK, -1s);
                    }
                }

                if (AuraEffect* aurEff = caster->GetAuraEffect(SPELL_MONK_TEACHINGS_OF_THE_MONASTERY, EFFECT_0))
                {
                    if (roll_chance_i(aurEff->GetAmount()))
                    {
                        if (auto spellHistory = player->GetSpellHistory())
                        {
                            spellHistory->ResetCooldown(SPELL_MONK_RISING_SUN_KICK, true);
                            spellHistory->ResetCharges(sSpellMgr->GetSpellInfo(SPELL_MONK_RISING_SUN_KICK)->ChargeCategoryId);
                        }
                    }
                }
            }

            if (auto aura = caster->GetAura(SPELL_MONK_TEACHINGS_OF_THE_MONASTERY_AURA))
            {
                if (caster->HasAura(SPELL_MONK_SPIRIT_OF_THE_CRANE_AURA)) //Spirit of the Crane
                {
                    int32 amount = int32(0.65f * aura->GetStackAmount());
                    caster->CastCustomSpell(caster, SPELL_MONK_SPIRIT_OF_THE_CRANE_MANA, &amount, NULL, NULL, true); //Spirit of the Crane refunds mana
                }
            }
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_monk_blackout_kick_SpellScript::HandleOnHit, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_monk_blackout_kick_SpellScript();
    }
};

//191840 - Essence Font (Heal)
class spell_monk_essence_font_heal : public SpellScriptLoader
{
public:
    spell_monk_essence_font_heal() : SpellScriptLoader("spell_monk_essence_font_heal") { }

    class spell_monk_essence_font_heal_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_monk_essence_font_heal_SpellScript);

        void FilterTargets(std::list<WorldObject*>& targets)
        {
            if (Unit* caster = GetCaster())
            {
                targets.remove_if([caster](WorldObject* object) -> bool
                {
                    if(object == nullptr || object->ToUnit() == nullptr)
                        return true;

                    Unit* unit = object->ToUnit();

                    if (unit == caster)
                        return true;
                    //If the target has the aura and the aura has more than 5 second duration (meaning it was cast less than 1 second ago) we dont keep it
                    if(unit->HasAura(SPELL_MONK_ESSENCE_FONT_HEAL) && unit->GetAura(SPELL_MONK_ESSENCE_FONT_HEAL)->GetDuration() > 5 * IN_MILLISECONDS)
                        return true;

                    return false;
                });

                if (targets.size() > 6)
                {
                    targets.sort(Trinity::HealthPctOrderPred());
                    targets.resize(6);
                }
            }
        }

		void FilterTargetsAura(std::list<WorldObject*>& targets)
		{
			if (Unit* caster = GetCaster())
			{
				if (!caster->HasAura(SPELL_MONK_ESSENCE_FONT_RANK))
				{
					targets.clear();
					return;
				}

				targets.remove_if([caster](WorldObject* object) -> bool
				{
					if (object == nullptr || object->ToUnit() == nullptr)
						return true;

					Unit* unit = object->ToUnit();

					if (unit == caster)
						return true;

					//If the target has the aura and the aura has more than 5 second duration (meaning it was cast less than 1 second ago) we dont keep it
					if (unit->HasAura(SPELL_MONK_ESSENCE_FONT_HEAL) && unit->GetAura(SPELL_MONK_ESSENCE_FONT_HEAL)->GetDuration() > 5 * IN_MILLISECONDS)
						return true;

					return false;
				});

				if (targets.size() > 6)
				{
					targets.sort(Trinity::HealthPctOrderPred());
					targets.resize(6);
				}
			}
		}

        void Register() override
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_monk_essence_font_heal_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ALLY);
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_monk_essence_font_heal_SpellScript::FilterTargetsAura, EFFECT_1, TARGET_UNIT_DEST_AREA_ALLY);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_monk_essence_font_heal_SpellScript();
    }
};

//115313 - Summon Jade Serpent Statue
class spell_monk_jade_serpent_statue : public SpellScriptLoader
{
public:
    spell_monk_jade_serpent_statue() : SpellScriptLoader("spell_monk_jade_serpent_statue") { }

    class spell_monk_jade_serpent_statue_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_monk_jade_serpent_statue_SpellScript);

        void HandleSummon()
        {
            Unit* caster = GetCaster();
            if (!caster)
                return;

            Player* player = caster->ToPlayer();
            if (!player)
                return;

            std::list<Creature*> serpentStatueList;
            player->GetCreatureListWithEntryInGrid(serpentStatueList, MONK_NPC_JADE_SERPENT_STATUE, 500.0f);

            for (std::list<Creature*>::iterator i = serpentStatueList.begin(); i != serpentStatueList.end(); ++i)
            {
                Unit* owner = (*i)->GetOwner();

                if (owner && owner == player && (*i)->IsSummon())
                    continue;

                i = serpentStatueList.erase(i);
            }

            if ((int32)serpentStatueList.size() >= 1)
                serpentStatueList.back()->ToTempSummon()->UnSummon();
        }

        void Register() override
        {
            OnCast += SpellCastFn(spell_monk_jade_serpent_statue_SpellScript::HandleSummon);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_monk_jade_serpent_statue_SpellScript();
    }
};

// 115151 - Renewing Mist
class spell_monk_renewing_mist : public SpellScriptLoader
{
public:
    spell_monk_renewing_mist() : SpellScriptLoader("spell_monk_renewing_mist") { }

    class spell_monk_renewing_mist_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_monk_renewing_mist_SpellScript);

        void HandleHit(SpellEffIndex /*eff*/)
        {
			Unit* caster = GetCaster();
			Unit* target = GetHitUnit();
			Unit* mainTarget = GetExplTargetUnit();
			if (!caster || !target || !mainTarget)
				return;

			caster->CastSpell(target, SPELL_MONK_RENEWING_MIST_PERIODIC);

            // Thunder Tea.
            if (Aura* aura = caster->GetAura(SPELL_MONK_THUNDER_FOCUS_TEA))
                aura->ModStackAmount(-1);
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_monk_renewing_mist_SpellScript::HandleHit, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_monk_renewing_mist_SpellScript();
    }
};

//119611 Renewing Mist
class spell_monk_renewing_mist_periodic : public SpellScriptLoader
{
public:
    spell_monk_renewing_mist_periodic() : SpellScriptLoader("spell_monk_renewing_mist_periodic") { }

    class spell_monk_renewing_mist_periodic_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_monk_renewing_mist_periodic_AuraScript);

        void OnTick(AuraEffect const* /*aurEff*/)
        {
			Unit* caster = GetCaster();
			Unit* target = GetTarget();
			if (!caster || !target)
				return;

			if (target->GetHealthPct() >= 100 && target->HasAura(SPELL_MONK_RENEWING_MIST_PERIODIC))
			{
				int32 remainingDuration = target->GetAura(SPELL_MONK_RENEWING_MIST_PERIODIC)->GetDuration();
				std::list<Unit*> targets;
				Trinity::AnyFriendlyUnitInObjectRangeCheck check(target, target, 25.0f);
				Trinity::UnitListSearcher<Trinity::AnyFriendlyUnitInObjectRangeCheck> searcher(target, targets, check);
				Cell::VisitAllObjects(target, searcher, 25.0f);

                if (!targets.size())
                    return;

				targets.sort(Trinity::HealthPctOrderPred());
                if (targets.size() > 1)
                    targets.resize(1);

				caster->CastSpell(targets.front(), SPELL_MONK_RENEWING_MIST_PERIODIC, true);

				if (targets.front()->HasAura(SPELL_MONK_RENEWING_MIST_PERIODIC))
				{
					targets.front()->GetAura(SPELL_MONK_RENEWING_MIST_PERIODIC)->SetDuration(remainingDuration);
					target->RemoveAura(SPELL_MONK_RENEWING_MIST_PERIODIC);
				}
			}
        }

        void Register() override
        {
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_monk_renewing_mist_periodic_AuraScript::OnTick, EFFECT_0, SPELL_AURA_PERIODIC_HEAL);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_monk_renewing_mist_periodic_AuraScript();
    }
};


// 116849 - Life Cocoon
class spell_monk_life_cocoon : public SpellScriptLoader
{
public:
    spell_monk_life_cocoon() : SpellScriptLoader("spell_monk_life_cocoon") { }

    class spell_monk_life_cocoon_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_monk_life_cocoon_AuraScript);

        void CalcAbsorb(AuraEffect const* /*aurEff*/, int32& amount, bool& canBeRecalculated)
        {
            // Formula:  [(((Spell power * 11) + 0)) * (1 + $versadmg)]
            // Simplified to : [(Spellpower * 11)]
            // Versatility will be taken into account at a later date.
            if (Unit* caster = GetCaster())
                amount += caster->GetTotalSpellPowerValue(GetSpellInfo()->GetSchoolMask(), true) * 11;
    
            canBeRecalculated = false;
        }

        void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if (GetTargetApplication()->GetRemoveMode() != AURA_REMOVE_BY_EXPIRE)
                return;

            Unit* caster = GetCaster();
            Unit* target = GetTarget();
            if (!caster || !target)
                return;

            if (Aura* aura = caster->GetAura(SPELL_MONK_BURST_OF_LIFE_POWER))
            {
                UnitList list;
                target->GetFriendlyUnitListInRange(list, 8.0f);
                uint8 count = list.size();
                uint32 healing = (count > 0) ? aura->GetEffect(EFFECT_0)->GetAmount() / count : aura->GetEffect(EFFECT_0)->GetAmount();
                caster->CastCustomSpell(SPELL_MONK_BURST_OF_LIFE_HEAL, SPELLVALUE_BASE_POINT1, healing, target, true);
            }
        }

        void Register() override
        {
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_monk_life_cocoon_AuraScript::CalcAbsorb, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
            OnEffectRemove += AuraEffectRemoveFn(spell_monk_life_cocoon_AuraScript::HandleRemove, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_monk_life_cocoon_AuraScript();
    }
};

// Windwalking - 157411
// AreaTriggerID - 2763
struct at_monk_windwalking : AreaTriggerAI
{
    at_monk_windwalking(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger) { }

    void OnUnitEnter(Unit* unit) override
    {
        Unit* caster = at->GetCaster();

        if (!caster || !unit)
            return;

        if (!caster->ToPlayer())
            return;

        if (Aura* aur = unit->GetAura(SPELL_MONK_WINDWALKER_AURA))
            aur->SetDuration(-1);
        else if (caster->IsFriendlyTo(unit))
            caster->CastSpell(unit, SPELL_MONK_WINDWALKER_AURA, true);
    }

    void OnUnitExit(Unit* unit) override
    {
        Unit* caster = at->GetCaster();

        if (!caster || !unit)
            return;

        if (!caster->ToPlayer())
            return;

        if (unit->HasAura(SPELL_MONK_WINDWALKING) && unit != caster) // Don't remove from other WW monks.
            return;

        if (Aura* aur = unit->GetAura(SPELL_MONK_WINDWALKER_AURA, caster->GetGUID()))
        {
            aur->SetMaxDuration(10 * IN_MILLISECONDS);
            aur->SetDuration(10 * IN_MILLISECONDS);
        }
    }

    void OnRemove() override
    {
        Unit* caster = at->GetCaster();

        if (!caster)
            return;

        if (!caster->ToPlayer())
            return;

        for (auto guid : at->GetInsideUnits())
        {
            if (Unit* unit = ObjectAccessor::GetUnit(*caster, guid))
            {
                if (unit->HasAura(SPELL_MONK_WINDWALKING) && unit != caster) // Don't remove from other WW monks.
                    continue;

                if (Aura* aur = unit->GetAura(SPELL_MONK_WINDWALKER_AURA, caster->GetGUID()))
                {
                    aur->SetMaxDuration(10 * IN_MILLISECONDS);
                    aur->SetDuration(10 * IN_MILLISECONDS);
                }
            }
        }
    }
};

// Gift of the Ox: 124503 / 124506 / 214418/ 214420
// Areatrigger ID: 373 or 11692
//Last Update 8.0.1 Build 28153
struct at_monk_gift_of_the_ox : AreaTriggerAI
{
	at_monk_gift_of_the_ox(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger) 
	{ 
		//areatrigger->SetVisibleBySummonerOnly(true);
	}

	void OnCreate() override
	{
		if (Unit* caster = at->GetCaster())
			caster->CastSpell(caster, SPELL_MONK_HEALING_SPHERE, true);
	}

	void OnUnitEnter(Unit* unit) override
	{
		Player* player = unit->ToPlayer();
		if (!player)
			return;

        uint32 spellId = 0;
        if (at->GetSpellId() == SPELL_MONK_GIFT_OF_THE_OX_GREATER_HEALING_SPHERE || at->GetSpellId() == SPELL_MONK_GIFT_OF_THE_OX_GREATER_HEALING_SPHERE_1)
            spellId = SPELL_MONK_GIFT_OF_THE_OX_GREATER_HEAL;
        else
            spellId = SPELL_MONK_GIFT_OF_THE_OX_HEAL;

        if(spellId)
            player->CastSpell(player, spellId, true);

        at->SetDuration(0);
	}

	void OnRemove() override
	{
		if (Unit* caster = at->GetCaster())
			if (Aura* healingSphere = caster->GetAura(SPELL_MONK_HEALING_SPHERE))
			{
				if (healingSphere->GetStackAmount() > 1)
					healingSphere->ModStackAmount(-1);
				else
					caster->RemoveAura(SPELL_MONK_HEALING_SPHERE);
			}
	}
};

//Last Update 8.0.1 Build 28153
class playerScript_monk_class : public PlayerScript
{
public:
    playerScript_monk_class() : PlayerScript("playerScript_monk_class") {}

	void OnMapChanged(Player* player)
	{
		if (!player)
			return;

		if (player->GetSpecializationId() == TALENT_SPEC_MONK_BATTLEDANCER)
		{
			if (player->HasAura(SPELL_MONK_WINDWALKING))
				if (!player->GetAreaTrigger(SPELL_MONK_WINDWALKING))
					player->AddAura(SPELL_MONK_WINDWALKING);
		}
	}
};

// 261767 - Inner Streng
class playerScript_monk_inner_streng : public PlayerScript
{
public:
    playerScript_monk_inner_streng() : PlayerScript("playerScript_monk_inner_streng") {}

    void OnModifyPower(Player * player, Powers power, int32 oldValue, int32& newValue, bool /*regen*/, bool after)
    {
        if (player->GetClass() != CLASS_MONK || power != POWER_CHI || !player->HasAura(SPELL_MONK_INNER_STRENG))
            return;

        if (after && oldValue > newValue)
        {
            for (size_t i = 0; i < oldValue - newValue; i++)
                player->CastSpell(player, SPELL_MONK_INNER_STRENG_BUFF, true);
        }
    }
};

// 117906 - Mastery : Elusive Brawler
class spell_monk_elusive_brawler_mastery : public AuraScript
{
    PrepareAuraScript(spell_monk_elusive_brawler_mastery);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetTypeMask() & TAKEN_HIT_PROC_FLAG_MASK)
            return true;

        return eventInfo.GetProcSpell() &&
              (eventInfo.GetProcSpell()->GetSpellInfo()->Id == SPELL_MONK_BLACKOUT_STRIKE ||
               eventInfo.GetProcSpell()->GetSpellInfo()->Id == SPELL_MONK_BREATH_OF_FIRE);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_monk_elusive_brawler_mastery::CheckProc);
    }
};

// 195630 - Elusive Brawler
class spell_monk_elusive_brawler_stacks : public AuraScript
{
    PrepareAuraScript(spell_monk_elusive_brawler_stacks);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!(eventInfo.GetHitMask() & PROC_HIT_DODGE))
            return false;

        if (Aura* elusiveBrawler = GetCaster()->GetAura(SPELL_MONK_ELUSIVE_BRAWLER, GetCaster()->GetGUID()))
            elusiveBrawler->SetDuration(0);

        return true;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_monk_elusive_brawler_stacks::CheckProc);
    }
};

// Dampen Harm - 122278
class spell_monk_dampen_harm : public SpellScriptLoader
{
public:
    spell_monk_dampen_harm() : SpellScriptLoader("spell_monk_dampen_harm") { }
    class spell_monk_dampen_harm_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_monk_dampen_harm_AuraScript);
        int32 healthPct;

        bool Load() override
        {
            healthPct = GetSpellInfo()->GetEffect(EFFECT_0).CalcValue(GetCaster());
            return GetUnitOwner()->ToPlayer();
        }

        void CalculateAmount(AuraEffect const* /*auraEffect*/, int32& amount, bool& /*canBeRecalculated*/)
        {
            amount = -1;
        }

        void Absorb(AuraEffect* auraEffect, DamageInfo& dmgInfo, uint32& absorbAmount)
        {
            Unit* target = GetTarget();
            uint32 health = target->CountPctFromMaxHealth(healthPct);
            if (dmgInfo.GetDamage() < health)
                return;

            absorbAmount = dmgInfo.GetDamage() * (GetSpellInfo()->GetEffect(EFFECT_0).CalcValue(GetCaster()) / 100);
            auraEffect->GetBase()->DropCharge();
        }
        void Register() override
        {
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_monk_dampen_harm_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
            OnEffectAbsorb += AuraEffectAbsorbFn(spell_monk_dampen_harm_AuraScript::Absorb, EFFECT_0);
        }
    };
    AuraScript* GetAuraScript() const override
    {
        return new spell_monk_dampen_harm_AuraScript();
    }
};

// Chi Burst damage - 123986
// AreaTriggerID - 5302
struct at_monk_chi_burst_damage : AreaTriggerAI
{
    at_monk_chi_burst_damage(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger) { }

    uint8 l_HittedUnits = 0;

    void OnUnitEnter(Unit* unit) override
    {
        if (Unit* l_Caster = at->GetCaster())
        {
            if (l_Caster->IsValidAttackTarget(unit))
            {
                l_Caster->CastSpell(unit, SPELL_MONK_CHI_BURST_DAMAGE, true);

                if (l_HittedUnits < 2)
                {
                    l_Caster->ModifyPower(POWER_CHI, 1);
                    l_HittedUnits++;
                }               
            }
        }
    }
};

// Chi Burst heal - 123986
// AreaTriggerID - 5300
struct at_monk_chi_burst_heal : AreaTriggerAI
{
    at_monk_chi_burst_heal(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger) { }

    void OnUnitEnter(Unit* unit) override
    {
        if (Unit* caster = at->GetCaster())
            if (caster->IsValidAssistTarget(unit))
                caster->CastSpell(unit, SPELL_MONK_CHI_BURST_HEAL, true);
    }
};

//5484
struct at_monk_song_of_chiji : AreaTriggerAI
{
    at_monk_song_of_chiji(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger) { }

    void OnUnitEnter(Unit* unit) override
    {
        Unit* caster = at->GetCaster();

        if (!caster || !unit)
            return;

        if (!caster->ToPlayer())
            return;

        if(unit != caster && caster->IsValidAttackTarget(unit))
            caster->CastSpell(unit, SPELL_MONK_SONG_OF_CHIJI, true);
    }
};

// 137639 - Storm, Earth, and Fire 
class spell_monk_storm_earth_and_fire : public AuraScript
{
    PrepareAuraScript(spell_monk_storm_earth_and_fire);

    void HandleApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Unit* target = GetTarget();
        target->CastSpell(target, SPELL_MONK_SEF_STORM_VISUAL, true);
        target->CastSpell(target, SPELL_MONK_SEF_SUMMON_EARTH, true);
        target->CastSpell(target, SPELL_MONK_SEF_SUMMON_FIRE,  true);
        if (Unit* caster = GetCaster())
        {
            caster->CastSpell(caster, SPELL_MONK_SEF_KICK_VISUAL, true);
            caster->CastSpell(caster, SPELL_MONK_SEF_JADE_LIGHTNING_VISUAL, true);
        }
    }

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* caster = GetCaster())
        {
            caster->RemoveAurasDueToSpell(SPELL_MONK_SEF_STORM_VISUAL);

            if (Creature* fireSpirit = caster->GetSummonedCreatureByEntry(NPC_FIRE_SPIRIT))
                if (TempSummon* summon = fireSpirit->ToTempSummon())
                    summon->DespawnOrUnsummon();

            if (Creature* earthSpirit = caster->GetSummonedCreatureByEntry(NPC_EARTH_SPIRIT))
                if (TempSummon* summon = earthSpirit->ToTempSummon())
                    summon->DespawnOrUnsummon();

            caster->RemoveAura(SPELL_MONK_SEF_KICK_VISUAL);
            caster->RemoveAura(SPELL_MONK_SEF_JADE_LIGHTNING_VISUAL);
        }
    }

    void Register() override
    {
        OnEffectApply  +=  AuraEffectApplyFn(spell_monk_storm_earth_and_fire::HandleApply,  EFFECT_0, SPELL_AURA_ADD_PCT_MODIFIER, AURA_EFFECT_HANDLE_REAL);
        OnEffectRemove += AuraEffectRemoveFn(spell_monk_storm_earth_and_fire::HandleRemove, EFFECT_0, SPELL_AURA_ADD_PCT_MODIFIER, AURA_EFFECT_HANDLE_REAL);
    }
};

// 69791 - Fire Spirit / 69792 - Earth Spirit
struct npc_monk_sef_spirit : public ScriptedAI
{
    npc_monk_sef_spirit(Creature* creature) : ScriptedAI(creature) {}

    void IsSummonedBy(WorldObject* o) override
    {
        if (!o || !o->IsPlayer())
        {
            me->DespawnOrUnsummon();
            return;
        }

        auto owner = o->ToPlayer();

        m_Timer = 500;

        Player* player = owner->ToPlayer();

        // Spirit initialization.
        me->SetLevel(owner->GetLevel());
        me->SetMaxHealth(owner->GetMaxHealth());
        me->SetHealth(owner->GetHealth());
        me->SetPowerType(POWER_ENERGY);
        me->SetMaxPower(POWER_ENERGY, 100);
        me->SetFaction(owner->GetFaction());
        me->SetReactState(REACT_ASSIST);

        me->SetModCastingSpeed(owner->m_unitData->ModCastingSpeed);
        me->SetModSpellHaste(owner->m_unitData->ModSpellHaste);

        // Clone the target.
        owner->CastSpell(me, SPELL_MONK_TRANSCENDENCE_CLONE_TARGET, true);
        me->CastSpell(me, me->GetEntry() == NPC_FIRE_SPIRIT ? SPELL_MONK_SEF_FIRE_VISUAL : SPELL_MONK_SEF_EARTH_VISUAL, true);
        me->CastSpell(me, SPELL_MONK_SEF_SUMMONS_STATS, true);

        // Fly to owner target, if is a valid target.
        if (Unit* target = player->GetSelectedUnit())
            if (owner->IsValidAttackTarget(target))
            {
                me->CastSpell(target, SPELL_MONK_SEF_CHARGE, true);
                targetGUID = target->GetGUID();
                follow = true;
            }

        if (!follow)
        {            
            me->FollowTarget(owner);
        }
    }

    void MovementInform(uint32 type, uint32 ID) override
    {
        if (ID == EVENT_CHARGE || ID == EVENT_CHARGE_PREPATH)
        {
            if (Unit* currentTarget = ObjectAccessor::GetUnit(*me, targetGUID))
            {
                follow = false;
                attackTarget = true;
                DoActions();
            }                
        }
    }

    void UpdateAI(uint32 diff) override
    {
        if (m_Timer <= diff)
        {
            DoActions();
            m_Timer = 500;
        }
        else
        {
            m_Timer -= diff;
        }
    }

    void FixateTarget(ObjectGuid newTarget)
    {
        if (newTarget != ObjectGuid::Empty)
        {
            if (Unit* target = ObjectAccessor::GetUnit(*me, newTarget))
            {
                if (me->GetOwner() && me->GetOwner()->IsValidAttackTarget(target))
                {
                    targetGUID = newTarget;
                    me->GetAI()->AttackStart(target);
                    attackTarget = false;
                    me->CombatStop(true);
                    me->CastSpell(target, SPELL_MONK_SEF_CHARGE, true);
                }
            }
        }
    }

    Unit * GetTarget() const
    {
        return ObjectAccessor::GetUnit(*me, targetGUID);
    }

    void DoActions()
    {
        Unit* owner = me->GetOwner();
        if (!owner)
            return;

        if (me->HasUnitState(UNIT_STATE_CASTING) || owner->HasUnitState(UNIT_STATE_CASTING))
            return;

        Unit* target = GetTarget();
        if (target && owner->IsValidAttackTarget(target))
        {
            AttackStart(target);
            DoMeleeAttackIfReady();
            return;
        }

        if (owner->IsInCombat())
        {
            if (Unit* target = ObjectAccessor::GetUnit(*me, owner->GetTarget()))
            {
                if (owner->IsValidAttackTarget(target))
                {
                    targetGUID = target->GetGUID();
                    AttackStart(target);
                    DoMeleeAttackIfReady();
                    return;
                }
            }
        }
    }

private:
    void EnterEvadeMode(EvadeReason /*reason*/) override
    {
        if (me->IsInEvadeMode() || !me->IsAlive())
            return;

        Unit* owner = me->GetOwner();

        me->SetReactState(REACT_ASSIST);
        me->CombatStop(true);
        if (owner && !me->HasUnitState(UNIT_STATE_FOLLOW) && !follow)
        {
            me->GetMotionMaster()->Clear();
            me->FollowTarget(owner);
        }
    }

    ObjectGuid targetGUID;
    bool attackTarget = false;
    bool follow = false;
    uint32 m_Timer;
};

// 113656 - Fist of Fury
class spell_monk_fists_of_fury : public SpellScript
{
    PrepareSpellScript(spell_monk_fists_of_fury);

    void HandleDamage(SpellEffIndex /*effIndex*/)
    {
        SetHitDamage(0);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_monk_fists_of_fury::HandleDamage, EFFECT_4, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

// 113656 - Fist of Fury
class aura_monk_fists_of_fury : public AuraScript
{
    PrepareAuraScript(aura_monk_fists_of_fury);

    void HandlePeriodic(AuraEffect const* aurEff)
    {
        PreventDefaultAction();

        if (Unit* caster = GetCaster())
        {
            if (caster->IsPlayer())
            {
                caster->CastSpell(caster, SPELL_MONK_FISTS_OF_FURY_DAMAGE, true);

                if (Creature* fireSpirit = caster->GetSummonedCreatureByEntry(NPC_FIRE_SPIRIT))
                {
                    if (Unit* target = ((npc_monk_sef_spirit*)fireSpirit->GetAI())->GetTarget())
                        fireSpirit->CastSpell(fireSpirit, SPELL_MONK_FISTS_OF_FURY_DAMAGE, true);
                }

                if (Creature* earthSpirit = caster->GetSummonedCreatureByEntry(NPC_EARTH_SPIRIT))
                {
                    if (Unit* target = ((npc_monk_sef_spirit*)earthSpirit->GetAI())->GetTarget())
                        earthSpirit->CastSpell(earthSpirit, SPELL_MONK_FISTS_OF_FURY_DAMAGE, true);
                }
            }
        }
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(aura_monk_fists_of_fury::HandlePeriodic, EFFECT_2, SPELL_AURA_PERIODIC_DUMMY);
    }
};

// 117418 - Fists of Fury Damage
class spell_monk_fists_of_fury_damage : public SpellScript
{
    PrepareSpellScript(spell_monk_fists_of_fury_damage);

    void HandleOnObjectAreaTargetSelect(std::list<WorldObject*>& targets)
    {
        SpellInfo const* spellInfo = GetSpellInfo();
        auto spellEffectInfo = GetSpellInfo()->GetEffect(EFFECT_0);
        Unit* caster = GetCaster();
        if (!spellInfo || !caster || caster->IsPlayer()) //Only for copy of monk
            return;

        std::list<Unit*> targetList;
        Trinity::AnyUnfriendlyUnitInObjectRangeCheck u_check(caster, caster, spellEffectInfo.MaxRadiusEntry->RadiusMax);
        Trinity::UnitListSearcher<Trinity::AnyUnfriendlyUnitInObjectRangeCheck> searcher(caster, targetList, u_check);
        Cell::VisitAllObjects(caster, searcher, spellEffectInfo.MaxRadiusEntry->RadiusMax);

        if (!targetList.empty())
        {
            targetList.remove_if([caster, spellInfo](WorldObject* object) -> bool
            {
                if (object == nullptr || object->ToUnit() == nullptr)
                    return true;

                Unit* unit = object->ToUnit();

                if (unit == caster)
                    return true;

                if(!caster->HasInArc(DegToRad(spellInfo->ConeAngle), unit))
                    return true;

                return false;
            });

            if (!targetList.empty())
            {
                targets.clear();
                for(auto target : targetList)
                    targets.push_back(target);
            }
        }        
    }

    void HandleDamage(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        if (caster->GetGUID() == target->GetGUID())
            return;

        if (!target->IsAlive())
            return;

        int32 damage = 0;

        // Fists of Fury deals full damage to the main target and half damage to nearby targets.
        if (target->GetGUID() == caster->GetTarget())
            damage = caster->GetTotalAttackPowerValue(BASE_ATTACK) * 1.2075f;
        else
            damage = caster->GetTotalAttackPowerValue(BASE_ATTACK) * 1.2075f * sSpellMgr->GetSpellInfo(SPELL_MONK_FISTS_OF_FURY)->GetEffect(EFFECT_5).BasePoints / 100;

        if (caster->HasAura(SPELL_MONK_SEF_STORM_VISUAL) || caster->HasAura(SPELL_MONK_SEF_FIRE_VISUAL) || caster->HasAura(SPELL_MONK_SEF_EARTH_VISUAL))
            damage *= 0.55;

        if (caster->HasAura(SPELL_MONK_HEAVY_HANDED_STRIKES))
        {
            if (SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(SPELL_MONK_HEAVY_HANDED_STRIKES_TRIGGER))
            {
                caster->CastSpell(target, SPELL_MONK_HEAVY_HANDED_STRIKES_TRIGGER, true);

                if (!caster->GetSpellHistory()->HasCooldown(spellInfo))
                    caster->GetSpellHistory()->StartCooldownROG(spellInfo, 0, NULL, false, true, 1 * IN_MILLISECONDS);
            }
        }

        SetHitDamage(damage);
        target->RemoveAurasDueToSpell(123154);
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_monk_fists_of_fury_damage::HandleOnObjectAreaTargetSelect, EFFECT_0, TARGET_UNIT_CONE_ENEMY_24);
        OnEffectHitTarget += SpellEffectFn(spell_monk_fists_of_fury_damage::HandleDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

// 221771 - Storm, Earth, and Fire: Fixate
class spell_monk_storm_earth_fire_fixate : public SpellScript
{
    PrepareSpellScript(spell_monk_storm_earth_fire_fixate);

    void HandleHit(SpellEffIndex effIndex)
    {
        if (Unit* caster = GetCaster())
        {
            if (caster->GetTarget() == ObjectGuid::Empty)
                return;

            if (Creature* fireSpirit = caster->GetSummonedCreatureByEntry(NPC_FIRE_SPIRIT))
                ((npc_monk_sef_spirit*)fireSpirit->GetAI())->FixateTarget(caster->GetTarget());

            if (Creature* fireSpirit = caster->GetSummonedCreatureByEntry(NPC_EARTH_SPIRIT))
                ((npc_monk_sef_spirit*)fireSpirit->GetAI())->FixateTarget(caster->GetTarget());
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_monk_storm_earth_fire_fixate::HandleHit, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

// 54569
struct npc_monk_transcendence_spirit : public ScriptedAI
{
	enum TranscendenceSpiritSpells
	{
		SPELL_VISUAL_SPIRIT = 119053,
	};

	npc_monk_transcendence_spirit(Creature* creature) : ScriptedAI(creature) 
	{
		me->SetReactState(REACT_PASSIVE);
	}

	void Reset()
	{
		me->SetUnitMovementFlags(MOVEMENTFLAG_ROOT);
		me->SetUnitFlag(UNIT_FLAG_UNINTERACTIBLE | UNIT_FLAG_NON_ATTACKABLE);
		me->SetUnitFlag2(UNIT_FLAG2_CANNOT_TURN);
        me->GetMotionMaster()->Clear();
        me->SetControlled(true, UnitState::UNIT_STATE_ROOT);
	}

    void IsSummonedBy(WorldObject* o) override
    {
        if (!o || !o->IsPlayer())
            return;

        auto owner = o->ToPlayer();

		me->CastSpell(me, SPELL_VISUAL_SPIRIT, true);
	}

    void UpdateAI(uint32 /*diff*/) override
    {

    }
};

// 63508
struct npc_monk_xuen : public ScriptedAI
{
    npc_monk_xuen(Creature* creature) : ScriptedAI(creature) {}

    void IsSummonedBy(WorldObject* o) override
    {
        if (!o || !o->IsPlayer())
            return;

        auto owner = o->ToPlayer(); 

        me->CastSpell(me, SPELL_MONK_XUEN_AURA, true);
        me->SetReactState(REACT_ASSIST);
        if (Unit* victim = ObjectAccessor::GetUnit(*me, owner->GetTarget()))
            if (victim != o)
                if (me->IsValidAssistTarget(victim))
                    AttackStart(victim);
    }

    void UpdateAI(uint32 diff) override
    {
        if (aoe <= 0)
        {
            aoe = 1000;
            DoCastVictim(123996, CastSpellExtraArgs(true).SetOriginalCaster(me->GetOwnerGUID()));
        }
        else aoe -= diff;

        DoMeleeAttackIfReady();
    }

    int32 aoe = 0;
};

class playerScript_monk_earth_fire_storm : public PlayerScript
{
public:
    playerScript_monk_earth_fire_storm() : PlayerScript("playerScript_monk_earth_fire_storm") {}
    
    void OnSuccessfulSpellCast(Player* player, Spell* spell) override
    {
        static uint32 spellID[9] = { SPELL_MONK_BLACKOUT_KICK, SPELL_FIST_OF_THE_WHITE_TIGER, SPELL_MONK_FISTS_OF_FURY,
            SPELL_MONK_RISING_SUN_KICK, SPELL_TIGER_PALM, SPELL_MONK_SPINNING_CRANE_KICK, SPELL_MONK_WHIRLING_DRAGON_PUNCH,
            SPELL_CHI_BURST, SPELL_MONK_RUSHING_JADE_WIND };

        if (SpellInfo const* spellInfo = spell->GetSpellInfo())
        {
            if (player->HasAura(SPELL_MONK_SEF))
            {
                for (uint8 i = 0; i < 9; i++)
                {
                    if (spellInfo->Id == spellID[i])
                    {
                        if (Creature* fireSpirit = player->GetSummonedCreatureByEntry(NPC_FIRE_SPIRIT))
                        {
                            fireSpirit->CombatStop();
                            if (Unit* target = ((npc_monk_sef_spirit*)fireSpirit->GetAI())->GetTarget())
                                fireSpirit->CastSpell(target, spellInfo->Id, true);
                        }

                        if (Creature* earthSpirit = player->GetSummonedCreatureByEntry(NPC_EARTH_SPIRIT))
                        {
                            earthSpirit->CombatStop();
                            if (Unit* target = ((npc_monk_sef_spirit*)earthSpirit->GetAI())->GetTarget())
                                earthSpirit->CastSpell(target, spellInfo->Id, true);
                        }
                    }
                }
            }
        }        
    }
};

/*
END OF STORM EARTH AND FIRE
*/

//115399
class spell_monk_black_ox_brew : public SpellScriptLoader
{
public:
    spell_monk_black_ox_brew() : SpellScriptLoader("spell_monk_black_ox_brew") { }

    class spell_monk_black_ox_brew_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_monk_black_ox_brew_SpellScript);

        void HandleHit(SpellEffIndex /*effIndex*/)
        {
            Unit* caster = GetCaster();
            if (!caster)
                return;

            caster->GetSpellHistory()->ResetCharges(sSpellMgr->GetSpellInfo(SPELL_MONK_PURIFYING_BREW)->ChargeCategoryId);
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_monk_black_ox_brew_SpellScript::HandleHit, EFFECT_0, SPELL_EFFECT_ENERGIZE);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_monk_black_ox_brew_SpellScript();
    }
};

//122280
class spell_monk_healing_elixirs_aura : public SpellScriptLoader
{
public:
    spell_monk_healing_elixirs_aura() : SpellScriptLoader("spell_monk_healing_elixirs_aura") { }
    class spell_monk_healing_elixirs_aura_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_monk_healing_elixirs_aura_AuraScript);
        void OnProc(AuraEffect* /*aurEff*/, ProcEventInfo& eventInfo)
        {
            PreventDefaultAction();
            if (!GetCaster())
                return;
            if (!eventInfo.GetDamageInfo())
                return;
            if (!eventInfo.GetDamageInfo()->GetDamage())
                return;
            if (Unit* caster = GetCaster())
            {
                if (caster->HealthBelowPctDamaged(35, eventInfo.GetDamageInfo()->GetDamage()))
                {
                    caster->CastSpell(caster, SPELL_MONK_HEALING_ELIXIRS_RESTORE_HEALTH, true);
                    caster->GetSpellHistory()->ConsumeCharge(SPELL_MONK_HEALING_ELIXIRS_RESTORE_HEALTH);
                }
            }
        }
        void Register() override
        {
            OnEffectProc += AuraEffectProcFn(spell_monk_healing_elixirs_aura_AuraScript::OnProc, EFFECT_0, SPELL_AURA_PROC_TRIGGER_SPELL);
        }
    };
    AuraScript* GetAuraScript() const override
    {
        return new spell_monk_healing_elixirs_aura_AuraScript();
    }
};

// Whirling Dragon Punch - 152175
class playerScript_monk_whirling_dragon_punch : public PlayerScript
{
public:
    playerScript_monk_whirling_dragon_punch() : PlayerScript("playerScript_monk_whirling_dragon_punch") {}

    void OnCooldownStart(Player* player, SpellInfo const* spellInfo, uint32 /*itemId*/, int32& cooldown, uint32& /*categoryId*/, int32& /*categoryCooldown*/) override
    {
        if (spellInfo->Id == SPELL_MONK_FISTS_OF_FURY || spellInfo->Id == SPELL_MONK_RISING_SUN_KICK)
        {
            SpellInfo const* l_SecondSpellInfo  = sSpellMgr->GetSpellInfo(spellInfo->Id == SPELL_MONK_FISTS_OF_FURY ? SPELL_MONK_RISING_SUN_KICK : SPELL_MONK_FISTS_OF_FURY);
            ApplyCasterAura(player, cooldown, player->GetSpellHistory()->GetRemainingCooldown(l_SecondSpellInfo).count());
        }
    }

private:
    void ApplyCasterAura(Player* player, int32 cooldown1, int32 cooldown2)
    {
        if (cooldown1 > 0 && cooldown2 > 0)
        {
            if (Aura* l_Aura = player->AddAura(SPELL_MONK_WHIRLING_DRAGON_PUNCH_CASTER_AURA))
                l_Aura->SetDuration(std::min(cooldown1, cooldown2));
        }
    }
};

// Whirling Dragon Punch - 152175
class spell_monk_whirling_dragon_punch : public AuraScript
{
    PrepareAuraScript(spell_monk_whirling_dragon_punch);

    void OnTick(AuraEffect const* /*aurEff*/)
    {
        if (GetCaster())
            GetCaster()->CastSpell(GetCaster(), SPELL_MONK_WHIRLING_DRAGON_PUNCH_DAMAGE, true);
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_monk_whirling_dragon_punch::OnTick, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

// 100780
class spell_monk_tiger_palm : public SpellScript
{
    PrepareSpellScript(spell_monk_tiger_palm);

    void HandleDmg(SpellEffIndex /*eff*/)
    {
        if (Unit* caster = GetCaster())
        {
            if (caster->HasAura(Monk::eLegendary::ShaoHaosMight))
            {
                if (roll_chance_i(40))
                {
                    auto dmg = GetHitDamage();
                    AddPct(dmg, 250);
                    SetHitDamage(dmg);
                }
            }
        }
    }

    void HandleHit(SpellEffIndex /*effIndex*/)
    {
        if (Unit* caster = GetCaster())
        {
            if (Aura* powerStrikes = caster->GetAura(SPELL_MONK_POWER_STRIKES_AURA))
            {
                SetEffectValue(GetEffectValue() + powerStrikes->GetEffect(EFFECT_0)->GetBaseAmount());
                powerStrikes->Remove();
            }

            if (caster->HasAura(SPELL_MONK_BREWMASTER_MONK))
            {
                // Reduce the cooldown of the brews.
                caster->GetSpellHistory()->ModifyCooldown(SPELL_MONK_FORTIFYING_BREW, -1s);
                caster->GetSpellHistory()->ReduceChargeCooldown(sSpellMgr->GetSpellInfo(SPELL_MONK_PURIFYING_BREW)->ChargeCategoryId, IN_MILLISECONDS);
                caster->GetSpellHistory()->ReduceChargeCooldown(sSpellMgr->GetSpellInfo(SPELL_MONK_IROSKIN_BREW)->ChargeCategoryId, IN_MILLISECONDS);

                if (caster->HasAura(Monk::eLegendary::ShaoHaosMight))
                {
                    caster->GetSpellHistory()->ModifyCooldown(SPELL_MONK_FORTIFYING_BREW, -1s);
                    caster->GetSpellHistory()->ReduceChargeCooldown(sSpellMgr->GetSpellInfo(SPELL_MONK_PURIFYING_BREW)->ChargeCategoryId, IN_MILLISECONDS);
                    caster->GetSpellHistory()->ReduceChargeCooldown(sSpellMgr->GetSpellInfo(SPELL_MONK_IROSKIN_BREW)->ChargeCategoryId, IN_MILLISECONDS);
                }
            }
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_monk_tiger_palm::HandleDmg, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
        OnEffectHitTarget += SpellEffectFn(spell_monk_tiger_palm::HandleHit, EFFECT_1, SPELL_EFFECT_ENERGIZE);
    }
};

// 61146 NPC - Black Ox Statue
struct npc_monk_black_ox_statue : public CreatureAI
{
public:
	npc_monk_black_ox_statue(Creature* creature) : CreatureAI(creature) {}

	void IsSummonedBy(WorldObject* owner) override
	{
		if (!owner)
			return;

        if (owner->IsUnit())
		    owner->ToUnit()->AddAura(SPELL_MONK_BLACK_OX_PROVOQUE, me);
	}

	void UpdateAI(uint32 diff) override {}
};

// 261767 - Inner Strength
class aura_dru_inner_strength : public AuraScript
{
	PrepareAuraScript(aura_dru_inner_strength);

	bool CheckProc(ProcEventInfo& eventInfo)
	{
		if (eventInfo.GetSpellInfo() && (eventInfo.GetSpellInfo()->Id == SPELL_MONK_RISING_SUN_KICK || eventInfo.GetSpellInfo()->Id == SPELL_MONK_BLACKOUT_KICK ||
			eventInfo.GetSpellInfo()->Id == SPELL_MONK_FISTS_OF_FURY || eventInfo.GetSpellInfo()->Id == SPELL_MONK_SPINNING_CRANE_KICK))
			return true;

		return false;
	}

	void HandleProc(ProcEventInfo& eventInfo)
	{
		Unit* caster = GetCaster();
		if (!caster)
			return;

		if (eventInfo.GetSpellInfo())
		{
			uint8 chi = 1;
			switch (eventInfo.GetSpellInfo()->Id)
			{
				case SPELL_MONK_RISING_SUN_KICK:
					chi = 2;
					break;
				case SPELL_MONK_FISTS_OF_FURY:
					chi = 3;
				case SPELL_MONK_SPINNING_CRANE_KICK:
					chi = 2;
					break;
			}
			
			for (uint8 i = 0; i < chi; i++)
				caster->CastSpell(caster, SPELL_MONK_INNER_STRENGTH_AURA, true);
		}
	}

	void Register() override
	{
		DoCheckProc += AuraCheckProcFn(aura_dru_inner_strength::CheckProc);
		OnProc += AuraProcFn(aura_dru_inner_strength::HandleProc);
	}
};

// 8647 - Mystic Touch
class aura_monk_mystic_touch : public AuraScript
{
	PrepareAuraScript(aura_monk_mystic_touch);

	bool CheckProc(ProcEventInfo& eventInfo)
	{
		if (eventInfo.GetDamageInfo() && (eventInfo.GetDamageInfo()->GetDamageType() != HEAL && eventInfo.GetDamageInfo()->GetDamageType() != NODAMAGE))
			return true;

		return false;
	}

	void HandleProc(ProcEventInfo& eventInfo)
	{
		Unit* caster = GetCaster();
		if (!caster)
			return;

		if (eventInfo.GetActionTarget())
			caster->CastSpell(eventInfo.GetActionTarget(), SPELL_MONK_MYSTIC_TOUCH_AURA, true);
	}

	void Register() override
	{
		DoCheckProc += AuraCheckProcFn(aura_monk_mystic_touch::CheckProc);
		OnProc += AuraProcFn(aura_monk_mystic_touch::HandleProc);
	}
};

// 242580 - Spitfire
class aura_monk_spitfire : public AuraScript
{
    PrepareAuraScript(aura_monk_spitfire);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == SPELL_MONK_TIGER_PALM)
            return true;

        return false;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();

        if (Unit* caster = GetCaster())
        {
            caster->GetSpellHistory()->ResetCooldown(SPELL_MONK_BREATH_OF_FIRE, true);
            caster->AddAura(SPELL_MONK_SPITFIRE_RESET);
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_monk_spitfire::CheckProc);
        OnProc += AuraProcFn(aura_monk_spitfire::HandleProc);
    }
};

// 242581 - Spitfire Aura
class aura_monk_spitfire_aura : public AuraScript
{
    PrepareAuraScript(aura_monk_spitfire_aura);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == SPELL_MONK_BREATH_OF_FIRE)
            return true;

        return false;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_monk_spitfire_aura::CheckProc);
    }
};

// 116670 - Vivify
class spell_monk_vivify : public SpellScript
{
	PrepareSpellScript(spell_monk_vivify);

	void HandleOnObjectAreaTargetSelect(std::list<WorldObject*>& targets)
	{
		if (Unit* caster = GetCaster())
		{
			if (!caster->HasAura(SPELL_MONK_VIVIFY_RANK))
			{
				targets.clear();
				return;
			}

			targets.remove_if(Trinity::UnitAuraCheck(false, SPELL_MONK_RENEWING_MIST_HOT, caster->GetGUID()));
		}
	}

    void HadlePrepare()
    {
        if (Unit* caster = GetCaster())
			if (Spell* spell = GetSpell())
			{
                if (spell->GetTriggeredCastFlags() & TRIGGERED_CAST_DIRECTLY)
                    return;

                if (Spell* currentSpell = caster->GetCurrentSpell(CURRENT_CHANNELED_SPELL))
                    if (currentSpell->GetSpellInfo()->Id == SPELL_MONK_SOOTHING_MIST)
                    {
                        Unit* target = currentSpell->GetUnitTarget();
                        Unit* selfTarget = spell->GetUnitTarget();
                        if (!target || !selfTarget)
                            return;

                        if (!target->IsInWorld() || !selfTarget->IsInWorld())
                            return;

                        if (target->GetGUID() == selfTarget->GetGUID())
                        {
                            TriggerCastFlags flags = TriggerCastFlags(spell->GetTriggeredCastFlags() | TRIGGERED_CAST_DIRECTLY);
                            spell->SetTriggerCastFlags(flags);
                        }
                    }
			} 
	}

	void HandleTakePower(SpellPowerCost& powerCost)
	{
		if (Unit* caster = GetCaster())
			if (powerCost.Power == POWER_ENERGY && caster->HasAura(SPELL_MONK_CONTROL_THE_MIST_BUFF))
				powerCost.Amount = 0;
	}

	void HandleAfterCast()
	{
		if (Unit* caster = GetCaster())
		{
			if (caster->HasAura(SPELL_MONK_LIFECYCLES))
				caster->CastSpell(caster, SPELL_MONK_LIFECYCLES_ENVELOPING_MIST, true);
            if (auto spell = GetSpell())
            {
                if ((spell->GetTriggeredCastFlags() & TRIGGERED_CAST_DIRECTLY) && caster->HasAura(SPELL_MONK_LIFECYCLES_VIVIFY))
                    caster->RemoveAurasDueToSpell(SPELL_MONK_LIFECYCLES_VIVIFY);
            }

            // Thunder Tea.
            if (Aura* aura = caster->GetAura(SPELL_MONK_THUNDER_FOCUS_TEA))
                aura->ModStackAmount(-1);
		}
	}

	void Register() override
	{
		OnPrepare += SpellOnPrepareFn(spell_monk_vivify::HadlePrepare);
		OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_monk_vivify::HandleOnObjectAreaTargetSelect, EFFECT_1, TARGET_UNIT_DEST_AREA_ALLY);
		OnTakePower += SpellOnTakePowerFn(spell_monk_vivify::HandleTakePower);
        AfterCast += SpellCastFn(spell_monk_vivify::HandleAfterCast);
	}
};

// 197915 - Lifecycles
class aura_monk_lifecycles : public AuraScript
{
	PrepareAuraScript(aura_monk_lifecycles);

	bool CheckProc(ProcEventInfo& eventInfo)
	{
		return false;
	}

	void Register() override
	{
		DoCheckProc += AuraCheckProcFn(aura_monk_lifecycles::CheckProc);
	}
};

// 197916 - Lifecycles (Vivify)
class aura_monk_lifecycles_vivify : public AuraScript
{
	PrepareAuraScript(aura_monk_lifecycles_vivify);

	bool CheckProc(ProcEventInfo& eventInfo)
	{
		if (eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == SPELL_MONK_VIVIFY)
		    return true;

		return false;
	}

	void Register() override
	{
		DoCheckProc += AuraCheckProcFn(aura_monk_lifecycles_vivify::CheckProc);
	}
};

// 197919 - Lifecycles (Enveloping Mist)
class aura_monk_lifecycles_enveloping_mist : public AuraScript
{
	PrepareAuraScript(aura_monk_lifecycles_enveloping_mist);

	bool CheckProc(ProcEventInfo& eventInfo)
	{
		if (eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == SPELL_MONK_ENVELOPING_MIST)
			return true;

		return false;
	}

	void Register() override
	{
		DoCheckProc += AuraCheckProcFn(aura_monk_lifecycles_enveloping_mist::CheckProc);
	}
};

// 116680 - Thunder Focus Tea
class aura_monk_thunder_focus_tea : public AuraScript
{
	PrepareAuraScript(aura_monk_thunder_focus_tea);

    void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (Aura* aura = GetAura())
            aura->SetMaxStackAmount();
    }

	bool CheckProc(ProcEventInfo& eventInfo)
	{
		return false;
	}

	void Register() override
	{
        OnEffectApply += AuraEffectApplyFn(aura_monk_thunder_focus_tea::OnApply, EFFECT_0, SPELL_AURA_ADD_FLAT_MODIFIER, AURA_EFFECT_HANDLE_REAL);
        DoCheckProc += AuraCheckProcFn(aura_monk_thunder_focus_tea::CheckProc);
	}
};

// Ring of Peace: 237371 
// Areatrigger ID: 3983
struct at_monk_ring_of_peace : AreaTriggerAI
{
	at_monk_ring_of_peace(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger) { }

    uint32 diff = IN_MILLISECONDS;

    void OnCreate() override
    {
        if (Unit* caster = at->GetCaster())        
            caster->CastSpell(at->GetPosition(), SPELL_MONK_RING_OF_PEACE_KNOCKBACK, true);
    }

    void OnUpdate(uint32 time) override
    {
        if (diff <= time)
        {
            diff = 100;
            if (Unit* caster = at->GetCaster())
            {
                std::list<Unit*> playerList;
                Trinity::AnyUnitInObjectRangeCheck check(at, at->GetRadius());
                Trinity::PlayerListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(at, playerList, check);
                Cell::VisitAllObjects(at, searcher, at->GetRadius());

                if (!playerList.empty())
                {
                    for (auto itr = playerList.begin(); itr != playerList.end(); ++itr)
                    {
                        if (!(*itr) || !caster->IsValidAttackTarget((*itr)))
                            continue;

                        if (!(*itr)->IsPlayer() || !(*itr)->ToPlayer()->GetKnockBackTime())
                        {
                            caster->CastSpell(at->GetPosition(), SPELL_MONK_RING_OF_PEACE_KNOCKBACK, true);
                            return;
                        }
                    }
                }
            }              
        }
        else
            diff -= time;
    }

	void OnUnitEnter(Unit* unit) override
	{
		Unit* caster = at->GetCaster();

		if (!caster || !unit)
			return;

		if (unit != caster && caster->IsValidAttackTarget(unit))
			caster->CastSpell(at->GetPosition(), SPELL_MONK_RING_OF_PEACE_KNOCKBACK, true);
	}
};

// Healing Sphere - 117032
// AreaTriggerID - 3319
struct at_monk_heal_sphere : AreaTriggerAI
{
	at_monk_heal_sphere(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger) { }

	void OnUnitEnter(Unit* unit) override
	{
		if (unit == at->GetCaster())
		{
            unit->CastSpell(unit, SPELL_MONK_HEALING_SPHERE_PROC, true);
            at->Remove();
		}
	}
};

// Chi Sphere - 163271
// AreaTriggerID - 7020
struct at_monk_chi_sphere : AreaTriggerAI
{
	at_monk_chi_sphere(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger) { }

	void OnUnitEnter(Unit* unit) override
	{
        if (unit == at->GetCaster())
		{
            unit->CastSpell(unit, SPELL_MONK_HEALING_CHI_PROC, true);
            at->Remove();
		}
	}
};

// Healing Sphere PVP - 115464
// AreaTriggerID - 228
struct at_monk_heal_sphere_pvp : AreaTriggerAI
{
    at_monk_heal_sphere_pvp(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger) { }

    void OnUnitEnter(Unit* unit) override
    {
        if (Unit* caster = at->GetCaster())
            if (unit && caster->IsValidAssistTarget(unit) && unit->IsPlayer())
            {
                caster->CastSpell(unit, SPELL_MONK_SPHERE_PVP_HEAL, true);

                // Remove all harmfull periodic auras.
                std::list<uint32> auras;

                auto appliedAuras = unit->GetAppliedAuras();
                for (auto aura : appliedAuras)
                    if (AuraApplication* app = aura.second)
                        if (!app->IsPositive())
                            if (Aura* auraBase = app->GetBase())
                            {
                                auto effects = auraBase->GetAuraEffects();
                                for (auto effect : effects)
                                {
                                    if (effect && effect->IsPeriodic() && effect->IsEffect())
                                    {
                                        auras.push_back(auraBase->GetId());
                                        break;
                                    }
                                }
                            }

                // Remove all found.
                for (uint32 id : auras)
                    unit->RemoveAurasDueToSpell(id);

                at->SetDuration(0);
            }
    }
};

// 196730 - Special Delivery
class aura_monk_special_delivery : public AuraScript
{
	PrepareAuraScript(aura_monk_special_delivery);

	bool CheckProc(ProcEventInfo& eventInfo)
	{
		if (eventInfo.GetSpellInfo() && (eventInfo.GetSpellInfo()->Id == SPELL_MONK_PURIFYING_BREW || eventInfo.GetSpellInfo()->Id == SPELL_MONK_IROSKIN_BREW))
			return true;

		return false;
	}

	void Register() override
	{
		DoCheckProc += AuraCheckProcFn(aura_monk_special_delivery::CheckProc);
	}
};

// 116092 - Afterlife
class aura_monk_afterlife : public AuraScript
{
	PrepareAuraScript(aura_monk_afterlife);

	void HandleProc(ProcEventInfo& eventInfo)
	{
		PreventDefaultAction();
		Unit* caster = GetCaster();
		Unit* target = eventInfo.GetActionTarget();
		if (!caster || !target)
			return;

        Position pos;
        GetRandPosFromCenterInDist(target, 8.f, pos);
        if (eventInfo.GetDamageInfo() && eventInfo.GetDamageInfo()->GetSpellInfo() && eventInfo.GetDamageInfo()->GetSpellInfo()->Id == SPELL_MONK_BLACKOUT_KICK)
        {
            if (roll_chance_i(sSpellMgr->GetSpellInfo(SPELL_MONK_AFTERLIFE)->GetEffect(EFFECT_1).BasePoints))
                caster->CastSpell(caster, SPELL_MONK_SUMMON_CHI_SPHERE, true);
        }
		else
			caster->CastSpell(pos, SPELL_MONK_SUMMON_HEALING_SPHERE, true);
	}

	void Register() override
	{
		OnProc += AuraProcFn(aura_monk_afterlife::HandleProc);
	}
};

// 233766 - Control of Mists Debuff
class aura_monk_control_of_mists_debuff : public AuraScript
{
	PrepareAuraScript(aura_monk_control_of_mists_debuff);

	void HandleRemove(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /* mode */)
	{
		if (Unit* caster = GetCaster())
			caster->CastSpell(caster, SPELL_MONK_CONTROL_THE_MIST_BUFF, true);
	}

	bool CheckProc(ProcEventInfo& eventInfo)
	{
		if (Spell const* procSpell = eventInfo.GetProcSpell())
			if (SpellPowerCost const* powerCost = procSpell->GetPowerCost(POWER_CHI))
				if (powerCost->Amount > 0)
				{
					chiValue = powerCost->Amount;
					return true;
				}

		return false;
	}

	void HandleProc(ProcEventInfo& eventInfo)
	{
		if (Unit* caster = GetCaster())
			if (Aura* aura = caster->GetAura(SPELL_MONK_CONTROL_THE_MIST_DEBUFF))
			{
				aura->ModDuration(-chiValue * 2 * IN_MILLISECONDS);
				if (aura->GetDuration() <= 0)
					caster->RemoveAura(aura);
			}
	}

	void Register() override
	{
		OnEffectRemove += AuraEffectRemoveFn(aura_monk_control_of_mists_debuff::HandleRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
		DoCheckProc += AuraCheckProcFn(aura_monk_control_of_mists_debuff::CheckProc);
		OnProc += AuraProcFn(aura_monk_control_of_mists_debuff::HandleProc);
	}

private:
	uint8 chiValue = 0;
};

// 233765 - Control the Mists
class aura_monk_control_of_mists : public AuraScript
{
	PrepareAuraScript(aura_monk_control_of_mists);

	void HandleApply(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /* mode */)
	{
		if (Unit* caster = GetCaster())
			caster->CastSpell(caster, SPELL_MONK_CONTROL_THE_MIST_DEBUFF, true);
	}

	void HandleRemove(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /* mode */)
	{
		if (Unit* caster = GetCaster())
		{
			caster->RemoveAura(SPELL_MONK_CONTROL_THE_MIST_DEBUFF);
			caster->RemoveAura(SPELL_MONK_CONTROL_THE_MIST_BUFF);
		}
	}

	void Register() override
	{
		OnEffectApply += AuraEffectApplyFn(aura_monk_control_of_mists::HandleApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
		OnEffectRemove += AuraEffectRemoveFn(aura_monk_control_of_mists::HandleRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
	}
};

// 233954 - Control the Mists Buff
class aura_monk_control_of_mists_buff : public AuraScript
{
	PrepareAuraScript(aura_monk_control_of_mists_buff);

	bool CheckProc(ProcEventInfo& eventInfo)
	{
		if (Unit* caster = GetCaster())
			if (eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == SPELL_MONK_VIVIFY && caster->GetCurrentSpellCastTime(SPELL_MONK_VIVIFY) == 0)
				return true;

		return false;
	}

	void Register() override
	{
		DoCheckProc += AuraCheckProcFn(aura_monk_control_of_mists_buff::CheckProc);
	}

private:
	uint8 chiValue = 0;
};

// 216519 - Celestial Fortune
class aura_monk_celestial_fortune : public AuraScript
{
	PrepareAuraScript(aura_monk_celestial_fortune);

	bool Validate(SpellInfo const* /*spellInfo*/) override
	{
		return ValidateSpellInfo({ SPELL_MONK_CELESTIAL_FORTUNE });
	}

	bool CheckProc(ProcEventInfo& eventInfo)
	{
		if (Unit* caster = GetCaster())
            if (auto player = caster->ToPlayer())
			if (eventInfo.GetHealInfo() && eventInfo.GetHealInfo()->GetHeal() > 0 && roll_chance_i(player->m_activePlayerData->CritPercentage))
				return true;

		return false;
	}

	void HandleProc(ProcEventInfo& eventInfo)
	{
		if (Unit* caster = GetCaster())
		{
			int32 base = eventInfo.GetHealInfo()->GetHeal();
			caster->CastCustomSpell(SPELL_MONK_CELESTIAL_FORTUNE_HEAL, SPELLVALUE_BASE_POINT0, CalculatePct(base, sSpellMgr->GetSpellInfo(SPELL_MONK_CELESTIAL_FORTUNE)->GetEffect(EFFECT_0).BasePoints), caster,  true);
		}
	}

	void Register()
	{
		DoCheckProc += AuraCheckProcFn(aura_monk_celestial_fortune::CheckProc);
		OnProc += AuraProcFn(aura_monk_celestial_fortune::HandleProc);
	}
};

// 198533 - Soothing Mist Statue
class aura_soothing_mist_statue : public AuraScript
{
	PrepareAuraScript(aura_soothing_mist_statue);

	void HandlePeriodic(AuraEffect const* /*aurEff*/)
	{
		Unit* caster = GetCaster();
		Unit* target = GetTarget();
		if (!caster || !target)
			return;

		Creature* creature = caster->GetSummonedCreatureByEntry(MONK_NPC_JADE_SERPENT_STATUE);
		if (creature && creature->ToUnit())
		{
			Unit* statue = creature->ToUnit();
            if (statue)            
                statue->SendPlaySpellVisual(target->GetGUID(), 24208, 0, 0, 15);            
		}
	}

	void Register() override
	{
		OnEffectPeriodic += AuraEffectPeriodicFn(aura_soothing_mist_statue::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_HEAL);
	}
};

// 196607 - Eye of the Tiger
class aura_monk_eye_of_the_tiger : public AuraScript
{
	PrepareAuraScript(aura_monk_eye_of_the_tiger);

	bool CheckProc(ProcEventInfo& eventInfo)
	{
		if (eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == SPELL_MONK_TIGER_PALM)
			return true;

		return false;
	}

	void Register() override
	{
		DoCheckProc += AuraCheckProcFn(aura_monk_eye_of_the_tiger::CheckProc);
	}
};

// 202162 - Avert Harm
class aura_monk_avert_harm : public AuraScript
{
	PrepareAuraScript(aura_monk_avert_harm);

	bool Validate(SpellInfo const* /*spell*/) override
	{
		return ValidateSpellInfo({ SPELL_MONK_AVERT_HARM });
	}

	void CalculateAmount(AuraEffect const* /*aurEff*/, int32& amount, bool& /*canBeRecalculated*/)
	{
		amount = -1;
	}

	void HandleAbsorb(AuraEffect* /*auraEffect*/, DamageInfo& dmgInfo, uint32& absorbAmount)
	{
		if (dmgInfo.GetDamage() && dmgInfo.GetDamage() <= 0)
			return;

		if (Unit* caster = GetCaster())
		{
			uint8 percent = sSpellMgr->GetSpellInfo(SPELL_MONK_AVERT_HARM)->GetEffect(EFFECT_1).BasePoints;
			absorbAmount = CalculatePct(dmgInfo.GetDamage(), percent);
			caster->Variables.Set<uint32>("ADD_STAGGER", absorbAmount);
		}
	}

	void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
	{
		if (Unit* caster = GetCaster())
			caster->Variables.Remove("ADD_STAGGER");
	}

	void Register() override
	{
		OnEffectAbsorb += AuraEffectAbsorbFn(aura_monk_avert_harm::HandleAbsorb, EFFECT_0);
		DoEffectCalcAmount += AuraEffectCalcAmountFn(aura_monk_avert_harm::CalculateAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
		OnEffectRemove += AuraEffectRemoveFn(aura_monk_avert_harm::HandleRemove, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB, AURA_EFFECT_HANDLE_REAL);
	}
};

// 202274 - Incendiary Brew
class aura_monk_incendiary_brew : public AuraScript
{
	PrepareAuraScript(aura_monk_incendiary_brew);

	bool CheckProc(ProcEventInfo& eventInfo)
	{
		if (!eventInfo.GetDamageInfo())
			return false;

		Aura* aura = GetAura();

		if (Unit* caster = GetCaster())
		{
			float chance = 50;
			// Blizzard mech.
			if (aura && aura->GetDuration() / 1000 >= aura->GetMaxDuration() / 2000 && roll_chance_f(chance))
				return true;
			else if (aura && aura->GetDuration() / 1000 < aura->GetMaxDuration() / 2000)
			{
				uint32 chanceAdd = (aura->GetMaxDuration() / 2000 - aura->GetDuration() / 1000) * 5 + 5;
				chance += chanceAdd;
				if (roll_chance_f(chance))
					return true;
			}
		}

		return false;
	}

	void HandleProc(ProcEventInfo& eventInfo)
	{
		if (WorldObject* owner = GetOwner())
			if (owner->ToUnit())
				owner->ToUnit()->RemoveAura(GetAura());
	}

	void Register() override
	{
		DoCheckProc += AuraCheckProcFn(aura_monk_incendiary_brew::CheckProc);
		OnProc += AuraProcFn(aura_monk_incendiary_brew::HandleProc);
	}
};

// 121253 - Keg Smash
class spell_monk_keg_smash : public SpellScript
{
    PrepareSpellScript(spell_monk_keg_smash);

    void HandleOnEffectHit(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        Unit* explTarget = GetExplTargetUnit();
        Unit* target = GetHitUnit();
        if (!caster || !target || !explTarget)
            return;

        if (caster->HasAura(SPELL_MONK_DOUBLE_BARREL) && explTarget->GetGUID() == target->GetGUID())
        {
            caster->CastSpell(explTarget, SPELL_MONK_DOUBLE_BARREL_STUN, true);
            caster->RemoveAurasDueToSpell(SPELL_MONK_DOUBLE_BARREL);
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_monk_keg_smash::HandleOnEffectHit, EFFECT_1, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

// 216113 - Way of the Crane
class aura_monk_way_of_the_crane : public AuraScript
{
    PrepareAuraScript(aura_monk_way_of_the_crane);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetDamageInfo() && (eventInfo.GetDamageInfo()->GetDamageType() != HEAL && eventInfo.GetDamageInfo()->GetDamageType() != NODAMAGE))
            return true;

        return false;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (Unit* caster = GetCaster())
        {
            int32 damage = eventInfo.GetDamageInfo()->GetDamage();
            uint8 percent = sSpellMgr->GetSpellInfo(SPELL_MONK_WAY_OF_THE_CRANE)->GetEffect(EFFECT_3).BasePoints;
            caster->CastCustomSpell(SPELL_MONK_WAY_OF_THE_CRANE_HEAL, SPELLVALUE_BASE_POINT0, CalculatePct(damage, percent), caster, true);
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_monk_way_of_the_crane::CheckProc);
        OnProc += AuraProcFn(aura_monk_way_of_the_crane::HandleProc);
    }
};

// 281501 - Way of the Crane Heal
class spell_monk_way_of_the_crane_heal : public SpellScript
{
    PrepareSpellScript(spell_monk_way_of_the_crane_heal);

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        if (Unit* caster = GetCaster())
        {
            targets.remove(caster);
            targets.remove_if([caster](WorldObject* obj)
            {
                if (!obj->ToPlayer())
                    return true;

                if (!caster->ToPlayer()->IsInSameGroupWith(obj->ToPlayer()) && !caster->ToPlayer()->IsInSameRaidWith(obj->ToPlayer()))
                    return true;

                return false;
            });
            targets.sort(Trinity::ObjectDistanceOrderPred(caster));
            if (targets.size() > 3)
                targets.resize(3);
        }
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_monk_way_of_the_crane_heal::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ALLY);
    }
};

// 205234 - Healing Sphere
class class_monk_healing_sphere : public SpellScript
{
    PrepareSpellScript(class_monk_healing_sphere);

    void HandleAfterCast()
    {
        if (Unit* caster = GetCaster())
        {
            auto ats = caster->GetAreaTriggers(SPELL_MONK_SPHERE_HEALING_AT);
            if (ats.size() == 3)
                for (auto at : ats)
                {
                    at->SetDuration(0);
                    break;
                }

            Position pos = GetExplTargetDest()->GetPosition();
            caster->GetScheduler().Schedule(1500ms, [caster, pos](TaskContext context)
            {
                if (caster)
                    caster->CastSpell(pos, SPELL_MONK_SPHERE_HEALING_AT, true);
            });
        }
    }

    void Register() override
    {
        AfterCast += SpellCastFn(class_monk_healing_sphere::HandleAfterCast);
    }
};

// 220357 - Cyclone Strikes
class aura_monk_cyclone_strikes : public AuraScript
{
    PrepareAuraScript(aura_monk_cyclone_strikes);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (auto caster = GetCaster())
        {
            if (Unit* target = eventInfo.GetActionTarget())
                if (eventInfo.GetSpellInfo() && (eventInfo.GetSpellInfo()->Id == SPELL_MONK_TIGER_PALM || eventInfo.GetSpellInfo()->Id == SPELL_MONK_BLACKOUT_KICK ||
                    eventInfo.GetSpellInfo()->Id == SPELL_MONK_RUSHING_JADE_WIND) && (eventInfo.GetDamageInfo() && eventInfo.GetDamageInfo()->GetDamageType() != NODAMAGE))
                {
                    // Check if the target is in the list.
                    for (ObjectGuid guid : caster->damagedTargets)
                        if (guid == target->GetGUID())
                            return false;

                    // Target is not in the list, push the target
                    caster->damagedTargets.push_back(target->GetGUID());
                    return true;
                }
        }

        return false;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (Unit* caster = GetCaster())
        {
            uint32 currentDuration = 0;
            if (Aura* aura = caster->GetAura(SPELL_MONK_CYCLONE_STRIKES))
                currentDuration = aura->GetDuration();
            else
                currentDuration = 15 * IN_MILLISECONDS;

            caster->CastSpell(caster, SPELL_MONK_CYCLONE_STRIKES, true);
            if (Aura* aura = caster->GetAura(SPELL_MONK_CYCLONE_STRIKES))
                aura->SetDuration(currentDuration);
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_monk_cyclone_strikes::CheckProc);
        OnProc += AuraProcFn(aura_monk_cyclone_strikes::HandleProc);
    }
};

// 220358 - Cyclone Strikes Buff
class aura_monk_cyclone_strikes_buff : public AuraScript
{
    PrepareAuraScript(aura_monk_cyclone_strikes_buff);

    void HandleRemove(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /* mode */)
    {
        // Clear list.
        if (GetCaster())
            GetCaster()->damagedTargets.clear();
    }

    void Register() override
    {
        OnEffectRemove += AuraEffectRemoveFn(aura_monk_cyclone_strikes_buff::HandleRemove, EFFECT_0, SPELL_AURA_ADD_PCT_MODIFIER, AURA_EFFECT_HANDLE_REAL);
    }
};

// 261715 - Rushing Jade Wind
class aura_monk_rushing_jade_wind : public AuraScript
{
    PrepareAuraScript(aura_monk_rushing_jade_wind);

    void HandleApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* caster = GetCaster())
            caster->GetScheduler().Schedule(1s, 1, [caster, this](TaskContext context)
        {
            if (caster)
                if (caster->GetPower(POWER_ENERGY) > 0)
                {
                    caster->SetPower(POWER_ENERGY, caster->GetPower(POWER_ENERGY) - 3);
                    context.Repeat();
                }
                else
                {
                    caster->GetScheduler().CancelGroup(1);
                    caster->RemoveAura(GetAura());
                }
        });
    }

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* caster = GetCaster())
            caster->GetScheduler().CancelGroup(1);
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(aura_monk_rushing_jade_wind::HandleApply, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL, AURA_EFFECT_HANDLE_REAL);
        OnEffectRemove += AuraEffectRemoveFn(aura_monk_rushing_jade_wind::HandleRemove, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL, AURA_EFFECT_HANDLE_REAL);
    }
};

// Last Update 8.0.1 Build 28153
// 247483 - Tigereye Brew
class playerScript_tiger_brew : public PlayerScript
{
public:
    playerScript_tiger_brew() : PlayerScript("playerScript_tiger_brew") {}

    void OnModifyPower(Player * player, Powers power, int32 oldValue, int32& newValue, bool /*regen*/, bool after)
    {
        if (player->GetClass() != CLASS_MONK || power != POWER_CHI || !player->HasSpell(SPELL_MONK_TIGER_BREW))
            return;

        if (!after || oldValue == newValue || oldValue < newValue)
            return;

        SpellInfo const * spellInfo = sSpellMgr->GetSpellInfo(SPELL_MONK_TIGER_BREW);
        if (!spellInfo)
            return;

        int32 chiConsume = player->Variables.Exist("CHI_CONSUME") ? player->Variables.GetValue<int32>("CHI_CONSUME") : 0;
        chiConsume += oldValue - newValue;
        player->Variables.Set<int32>("CHI_CONSUME", chiConsume);

        if (chiConsume >= spellInfo->GetEffect(EFFECT_2).BasePoints)
        {
            player->Variables.Remove("CHI_CONSUME");
            player->CastSpell(player, SPELL_MONK_TIGER_BREW_TRIGGER, true);

            if (!player->HasAura(SPELL_MONK_TIGER_BREW_LIGHT_AURA))
            {
                if (Aura* aur = player->GetAura(SPELL_MONK_TIGER_BREW_TRIGGER))
                {
                    if (aur->GetStackAmount() >= spellInfo->GetEffect(EFFECT_1).BasePoints)
                        player->CastSpell(player, SPELL_MONK_TIGER_BREW_LIGHT_AURA, true);
                }
            }
        }
    }
};

// Last Update 8.0.1 Build 28153
// 247483 - Tigereye Brew
class spell_tiger_brew : public SpellScript
{
    PrepareSpellScript(spell_tiger_brew);

    void HandleAfterHit()
    {
        if (Unit* caster = GetCaster())
        {
            uint32 stack = 0;
            if (Aura* aur = caster->GetAura(SPELL_MONK_TIGER_BREW_TRIGGER))
                stack = aur->GetStackAmount();

            if (Aura* aur = caster->GetAura(GetSpellInfo()->Id))
            {
                int32 duration = aur->GetMaxDuration();
                aur->SetMaxDuration(duration * stack);
                aur->SetDuration(duration * stack);             
            }

            caster->RemoveAura(SPELL_MONK_TIGER_BREW_TRIGGER);
            caster->RemoveAura(SPELL_MONK_TIGER_BREW_LIGHT_AURA);
        }
    }

    void Register() override
    {
        AfterHit += SpellHitFn(spell_tiger_brew::HandleAfterHit);
    }
};

// 124502 - Gift of the Ox
//Last Update 8.0.1 Build 28153
class spell_monk_gift_of_the_ox : public AuraScript
{
    PrepareAuraScript(spell_monk_gift_of_the_ox);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo(
            {
                SPELL_MONK_GIFT_OF_THE_OX_AT_RIGHT,
                SPELL_MONK_GIFT_OF_THE_OX_AT_LEFT,
            });
    }

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        // can't proc off Stagger
        if (SpellInfo const* spellInfo = eventInfo.GetSpellInfo())
            if (spellInfo->Id == SPELL_MONK_STAGGER)
                return false;

        return eventInfo.GetDamageInfo() && eventInfo.GetDamageInfo()->GetDamage();
    }

    void HandleProc(AuraEffect* /*aurEff*/, ProcEventInfo& eventInfo)
    {
        Unit* owner = GetUnitOwner();
        uint64 peekDamage = eventInfo.GetDamageInfo()->GetDamage();
        if (!owner || !peekDamage)
            return;

        _procChance = (float(CalculatePct(peekDamage, 75.f)) / float(owner->GetMaxHealth())) * (3.f - 2.f * owner->GetHealthPct() / 100.0f);

        if (roll_chance_f(_procChance * 100.f))
        {
            _procChance = 0;

            static const uint32 sphere[] = { SPELL_MONK_GIFT_OF_THE_OX_AT_RIGHT, SPELL_MONK_GIFT_OF_THE_OX_AT_LEFT };
            static const uint32 greaterSphere[] = { SPELL_MONK_GIFT_OF_THE_OX_GREATER_HEALING_SPHERE, SPELL_MONK_GIFT_OF_THE_OX_GREATER_HEALING_SPHERE_1 };

            uint32 spellId = Trinity::Containers::SelectRandomContainerElement(sphere);

            // Overflow (Artifact trait)
            if (AuraEffect const* overflow = owner->GetAuraEffect(SPELL_MONK_OVERFLOW, EFFECT_0))
                if (roll_chance_i(overflow->GetAmount()))
                    spellId = Trinity::Containers::SelectRandomContainerElement(greaterSphere);

            owner->CastSpell(owner, spellId, true);
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_monk_gift_of_the_ox::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_monk_gift_of_the_ox::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
private:
    float _procChance = 0.f;
};

// 178173 - Gift of the Ox (when healing sphere expires before being used)
// 214417 - Greater Gift of the Ox
//Last Update 8.0.1 Build 28153
class spell_monk_gift_of_the_ox_healing_sphere_expired : public SpellScript
{
    PrepareSpellScript(spell_monk_gift_of_the_ox_healing_sphere_expired);

    void HandleTarget(std::list<WorldObject*>& targets)
    {
        Unit* caster = GetCaster();
        targets.remove_if([caster](WorldObject* target)
        {
            return caster->GetGUID() != target->GetGUID();
        });
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_monk_gift_of_the_ox_healing_sphere_expired::HandleTarget, EFFECT_0, TARGET_UNIT_DEST_AREA_ALLY);
    }
};

// 122783 - Diffuse Magic
// Last Update 8.0.1 Build 28153
class spell_monk_diffuse_magic : public SpellScript
{
    PrepareSpellScript(spell_monk_diffuse_magic);

    void HandleOnHit()
    {
        if (Player* monk = GetCaster()->ToPlayer())
        {
            Unit::AuraApplicationMap auraList = monk->GetAppliedAuras();
            for (Unit::AuraApplicationMap::iterator iter = auraList.begin(); iter != auraList.end(); ++iter)
            {
                Aura* aura = iter->second->GetBase();
                if (!aura)
                    continue;

                Unit* caster = aura->GetCaster();
                if (!caster || caster->GetGUID() == monk->GetGUID())
                    continue;

                if (!caster->IsWithinDist(monk, 40.0f))
                    continue;

                if (aura->GetSpellInfo()->IsPositive())
                    continue;

                if (!(aura->GetSpellInfo()->GetSchoolMask() & SPELL_SCHOOL_MASK_MAGIC))
                    continue;

                if (!(aura->GetSpellInfo()->GetDispelMask() & 1 << DISPEL_MAGIC))
                    continue;

                monk->AddAura(aura->GetSpellInfo()->Id, caster);

                if (Aura* targetAura = caster->GetAura(aura->GetSpellInfo()->Id, monk->GetGUID()))
                {
                    for (int i = 0; i < MAX_SPELL_EFFECTS; ++i)
                    {
                        if (targetAura->GetEffect(i) && aura->GetEffect(i))
                        {
                            AuraEffect const* auraEffect = monk->GetAuraEffect(aura->GetSpellInfo()->Id, i);
                            if (!auraEffect)
                                continue;

                            int32 damage = auraEffect->GetAmount();

                            if (auraEffect->GetAuraType() == SPELL_AURA_PERIODIC_DAMAGE ||
                                auraEffect->GetAuraType() == SPELL_AURA_PERIODIC_DAMAGE_PERCENT)
                                damage = caster->SpellDamageBonusDone(monk, aura->GetSpellInfo(), damage, DOT, auraEffect->GetSpellEffectInfo(), auraEffect->GetBase()->GetStackAmount());

                            targetAura->SetDuration(aura->GetDuration());
                            targetAura->GetEffect(i)->SetAmount(damage);
                        }
                    }
                }

                monk->RemoveAura(aura);
            }
        }
    }

    void Register() override
    {
        OnHit += SpellHitFn(spell_monk_diffuse_magic::HandleOnHit);
    }
};

// 115008 - Chi Torpedo
class spell_monk_chi_torpedo : public SpellScript
{
    PrepareSpellScript(spell_monk_chi_torpedo);

    void HandleCast()
    {
        if (Unit* caster = GetCaster())
            if (caster->HasAura(SPELL_MONK_YULONS_GIFT))
                caster->CastSpell(caster, SPELL_MONK_YUKONS_GIFT_EFFECT, true);
    }

    void Register() override
    {
        OnCast += SpellCastFn(spell_monk_chi_torpedo::HandleCast);
    }
};

// 325216
class spell_monk_bonedust_brew : public AuraScript
{
    PrepareAuraScript(spell_monk_bonedust_brew);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (DamageInfo* damageInfo = eventInfo.GetDamageInfo())
        {
            if (damageInfo->GetDamage())
                return true;
        }
        return false;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (DamageInfo* damageInfo = eventInfo.GetDamageInfo())
        {
            if (Unit* target = eventInfo.GetActionTarget())
            {
                if (auto caster = GetCaster())
                {
                    uint32 damage = (damageInfo->GetDamage() * 0.5f);
                    SpellNonMeleeDamage damageLog = SpellNonMeleeDamage(caster, target, GetSpellInfo(), { GetSpellInfo()->GetSpellXSpellVisualId(), 0 }, GetSpellInfo()->GetSchoolMask());
                    damageLog.damage = damage;
                    caster->CalculateSpellDamageTaken(&damageLog, damageLog.damage, GetSpellInfo());
                    caster->DealDamageMods(caster, target, damageLog.damage, &damageLog.absorb);
                    caster->SendSpellNonMeleeDamageLog(&damageLog);
                    caster->DealDamage(caster, target, damage);
                }
            }
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_monk_bonedust_brew::CheckProc);
        AfterProc += AuraProcFn(spell_monk_bonedust_brew::HandleProc);
    }
};

void AddSC_monk_spell_scripts()
{
    new spell_monk_black_ox_brew();
    new spell_monk_blackout_kick();
    new spell_monk_breath_of_fire();
	RegisterSpellScript(spell_monk_chi_wave);
	RegisterSpellScript(aura_monk_chi_wave_damage_missile);
	RegisterSpellScript(aura_monk_chi_wave_heal_missile);
	new spell_monk_chi_wave_target_selector();
    new spell_monk_crackling_jade_knockback();
    new spell_monk_crackling_jade_lightning();
    new spell_monk_crackling_jade_lightning_knockback_proc_aura();
    new spell_monk_dampen_harm();
    RegisterSpellAndAuraScriptPair(spell_monk_disable, aura_monk_disable);
    RegisterSpellScript(aura_heavy_handed_strikes);    
    RegisterSpellScript(spell_monk_elusive_brawler_mastery);
    RegisterSpellScript(spell_monk_elusive_brawler_stacks);
    new spell_monk_enveloping_mist();
    new spell_monk_essence_font_heal();
	RegisterSpellScript(spell_monk_expel_harm);
    RegisterSpellAndAuraScriptPair(spell_monk_fists_of_fury, aura_monk_fists_of_fury);
    RegisterSpellScript(spell_monk_fists_of_fury_damage);
    //new spell_monk_fists_of_fury_stun();
    new spell_monk_fists_of_fury_visual();
    new spell_monk_fists_of_fury_visual_filter();
    new spell_monk_flying_serpent_kick();
    new spell_monk_fortifying_brew();
    new spell_monk_healing_elixirs_aura();
    new spell_monk_jab();
    new spell_monk_jade_serpent_statue();
    new spell_monk_legacy_of_the_emperor();
    new spell_monk_life_cocoon();
    new spell_monk_mana_tea();
    new spell_monk_mana_tea_stacks();
    RegisterSpellScript(spell_monk_path_of_blossom);
    new spell_monk_power_strikes();
    new spell_monk_provoke();
    RegisterSpellScript(spell_monk_purifying_brew);
    new spell_monk_renewing_mist();
    new spell_monk_renewing_mist_periodic();
    new spell_monk_rising_sun_kick();
    new spell_monk_rising_thunder();
    new spell_monk_roll();
    new spell_monk_roll_trigger();
    RegisterSpellScript(aura_monk_soothing_mist);
    new spell_monk_spear_hand_strike();
    RegisterSpellScript(aura_monk_stagger_damage);
    RegisterSpellScript(spell_monk_stagger_visual);
    RegisterSpellScript(aura_monk_stagger);
    RegisterSpellScript(spell_monk_storm_earth_and_fire);
	RegisterSpellScript(spell_monk_surging_mist);
    new spell_monk_surging_mist_glyphed();
    new spell_monk_tiger_lust();
    new spell_monk_tigereye_brew_stacks();
    RegisterSpellAndAuraScriptPair(spell_monk_touch_of_death, aura_monk_touch_of_death);
    new spell_monk_touch_of_karma();
    RegisterSpellAndAuraScriptPair(spell_monk_transcendence, aura_monk_transcendence);
    RegisterSpellScript(spell_monk_transcendence_transfer);
    new spell_monk_zen_flight_check();
    new spell_monk_zen_pilgrimage();
    new spell_monk_zen_pulse();
    RegisterSpellScript(spell_monk_whirling_dragon_punch);
    RegisterSpellScript(spell_monk_tiger_palm);
    RegisterSpellScript(aura_dru_inner_strength);
    RegisterSpellScript(aura_monk_mystic_touch);
    RegisterSpellScript(aura_monk_spitfire);
    RegisterSpellScript(aura_monk_spitfire_aura);
    RegisterSpellScript(spell_monk_ironskin_brew);
	RegisterSpellScript(spell_monk_vivify);
	RegisterSpellScript(aura_monk_lifecycles);
	RegisterSpellScript(aura_monk_lifecycles_vivify);
	RegisterSpellScript(aura_monk_lifecycles_enveloping_mist);
	RegisterSpellScript(aura_monk_thunder_focus_tea);
	RegisterSpellScript(aura_monk_special_delivery);
	RegisterSpellScript(aura_monk_afterlife);
	RegisterSpellScript(aura_monk_control_of_mists_debuff);
	RegisterSpellScript(aura_monk_control_of_mists);
	RegisterSpellScript(aura_monk_control_of_mists_buff);
	RegisterSpellScript(aura_monk_celestial_fortune);
	RegisterSpellScript(spell_monk_expel_harm_damage);
    RegisterSpellScript(spell_monk_storm_earth_fire_fixate);
	RegisterSpellScript(aura_soothing_mist_statue);
	RegisterSpellScript(aura_monk_eye_of_the_tiger);
	RegisterSpellScript(aura_monk_touch_of_death_amplifer);
	RegisterSpellScript(aura_monk_incendiary_brew);
    RegisterSpellScript(spell_monk_keg_smash);
    RegisterSpellScript(aura_monk_way_of_the_crane);
    RegisterSpellScript(spell_monk_way_of_the_crane_heal);
    RegisterSpellScript(class_monk_healing_sphere);
    RegisterSpellScript(aura_monk_cyclone_strikes);
    RegisterSpellScript(aura_monk_cyclone_strikes_buff);
    RegisterSpellScript(aura_monk_rushing_jade_wind);
    RegisterSpellScript(spell_tiger_brew);
    RegisterSpellScript(spell_monk_gift_of_the_ox);
    RegisterSpellScript(spell_monk_gift_of_the_ox_healing_sphere_expired);
    RegisterSpellScript(spell_monk_diffuse_magic);
    RegisterSpellScript(spell_monk_chi_torpedo);
    RegisterSpellScript(aura_monk_teachings_of_the_monastery);
    RegisterSpellScript(aura_monk_teachings_of_the_monastery_buff);
    RegisterSpellScript(spell_monk_bonedust_brew);

    RegisterCreatureAI(npc_monk_sef_spirit);
    RegisterCreatureAI(npc_monk_xuen);
	RegisterCreatureAI(npc_monk_black_ox_statue);
	RegisterCreatureAI(npc_monk_transcendence_spirit);

    // Register Area Triggers
	RegisterAreaTriggerAI(at_monk_gift_of_the_ox);
	RegisterAreaTriggerAI(at_monk_windwalking);
	RegisterAreaTriggerAI(at_monk_chi_burst_damage);
	RegisterAreaTriggerAI(at_monk_chi_burst_heal);
	RegisterAreaTriggerAI(at_monk_song_of_chiji);
	RegisterAreaTriggerAI(at_monk_ring_of_peace);
	RegisterAreaTriggerAI(at_monk_chi_sphere);
	RegisterAreaTriggerAI(at_monk_heal_sphere);
    RegisterAreaTriggerAI(at_monk_heal_sphere_pvp);

    // Playerscript
    new playerScript_monk_earth_fire_storm();
    new playerScript_monk_whirling_dragon_punch();
    new playerScript_monk_class();
    new playerScript_monk_inner_streng();
    new playerScript_tiger_brew();
}
