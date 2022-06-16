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
* Scripts for spells with SPELLFAMILY_PALADIN and SPELLFAMILY_GENERIC spells used by paladin players.
* Ordered alphabetically using scriptname.
* Scriptnames of files in this file should be prefixed with "spell_pal_".
*/

#include "AreaTrigger.h"
#include "AreaTriggerAI.h"
#include "Creature.h"
#include "Group.h"
#include "PhasingHandler.h"
#include "Player.h"
#include "ScriptedCreature.h"
#include "ScriptHelper.h"
#include "ScriptMgr.h"
#include "Spell.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"
#include "SpellHistory.h"
#include "SpellMgr.h"
#include "TemporarySummon.h"
#include "GridNotifiers.h"

enum PaladinSpells
{
    SPELL_PALADIN_ARCING_LIGHT_DAMAGE           = 114919,
    SPELL_PALADIN_ARCING_LIGHT_HEAL             = 119952,
    SPELL_PALADIN_ARDENT_DEFENDER               = 31850,
    SPELL_PALADIN_ARDENT_DEFENDER_HEAL          = 66235,
    SPELL_PALADIN_AVENGERS_SHIELD               = 31935,
    SPELL_PALADIN_AVENGING_WRATH                = 31884,
    SPELL_PALADIN_AURA_OF_SACRIFICE             = 183416,
    SPELL_PALADIN_AURA_OF_SACRIFICE_ALLY        = 210372,
    SPELL_PALADIN_AURA_OF_SACRIFICE_DAMAGE      = 210380,
    SPELL_PALADIN_AURA_OF_SACRIFICE_HEAL        = 210383,
    SPELL_PALADIN_BEACON_OF_FAITH               = 156910,
    SPELL_PALADIN_BEACON_OF_FAITH_PROC_AURA     = 177173,
    SPELL_PALADIN_BEACON_OF_LIGHT               = 53563,
    SPELL_PALADIN_BEACON_OF_LIGHT_HEAL          = 53652,
    SPELL_PALADIN_BEACON_OF_LIGHT_PROC_AURA     = 53651,
    SPELL_PALADIN_BEACON_OF_VIRTUE              = 200025,
    SPELL_PALADIN_BLADE_OF_JUSTICE              = 184575,
    SPELL_PALADIN_BLINDING_LIGHT_CONFUSE        = 105421,
    SPELL_PALADIN_CONSECRATED_GROUND            = 204054,
    SPELL_PALADIN_CONSECRATION                  = 26573,
    SPELL_PALADIN_CONSECRATION_DAMAGE           = 81297,
    SPELL_PALADIN_CONSECRATION_HEAL             = 204241,
    SPELL_PALADIN_CONSECRATION_INCREASE_SPEED   = 204242, // Need impentation
    SPELL_PALADIN_CRUSADERS_JUDGMENT            = 204023,
    SPELL_PALADIN_CRUSADERS_MIGHT               = 196926,
    SPELL_PALADIN_CRUSADER_STRIKE               = 35395,
    SPELL_PALADIN_DIVINE_INTERVENTION_HEAL      = 184250,
    SPELL_PALADIN_DIVINE_PURPOSE_HOLY           = 197646,
    SPELL_PALADIN_DIVINE_PURPOSE_HOLY_AURA_1    = 216411,
    SPELL_PALADIN_DIVINE_PURPOSE_HOLY_AURA_2    = 216413,
    SPELL_PALADIN_DIVINE_PURPOSE_RET            = 223817,
    SPELL_PALADIN_DIVINE_PURPOSE_RET_AURA       = 223819,
    SPELL_PALADIN_DIVINE_SHIELD                 = 642,
    SPELL_PALADIN_DIVINE_STEED_BLOODELF         = 221886,
    SPELL_PALADIN_DIVINE_STEED_DRAENEI          = 221887,
    SPELL_PALADIN_DIVINE_STEED_HUMAN            = 221883,
    SPELL_PALADIN_DIVINE_STEED_SPEED            = 220509,
    SPELL_PALADIN_DIVINE_STEED_TAUREN           = 221885,
    SPELL_PALADIN_DIVINE_STEED_DWARF            = 276111,
	SPELL_PALADIN_DIVINE_STEED_DARK_IRON_DWARF  = 276112,
    SPELL_PALADIN_DIVINE_STEED_AURA_GOLDEN      = 254474,
    SPELL_PALADIN_DIVINE_STEED_AURA_VENGEFUL    = 254472,
    SPELL_PALADIN_DIVINE_STEED_AURA_VALOROUS    = 254473,
    SPELL_PALADIN_DIVINE_STEED_AURA_VIGILANT    = 254471,
    SPELL_PALADIN_DIVINE_STEED_GOLDEN           = 254475,
    SPELL_PALADIN_DIVINE_STEED_VENGEFUL         = 254467,
    SPELL_PALADIN_DIVINE_STEED_VALOROUS         = 254465,
    SPELL_PALADIN_DIVINE_STEED_VIGILANT         = 254469,
    SPELL_PALADIN_DIVINE_STORM                  = 53385,
    SPELL_PALADIN_DIVINE_STORM_DAMAGE           = 224239,
    SPELL_PALADIN_EYE_FOR_AN_EYE_DAMAGE         = 205202,
    SPELL_PALADIN_FERVENT_MARTYR_BUFF           = 223316,
    SPELL_PALADIN_FINAL_STAND                   = 204077,
    SPELL_PALADIN_FINAL_STAND_TAUNT             = 204079,
    SPELL_PALADIN_FIRST_AVENGER                 = 203776,
    SPELL_PALADIN_FIST_OF_JUSTICE               = 198054,
    SPELL_PALADIN_FIST_OF_JUSTICE_RETRI         = 234299,
    SPELL_PALADIN_FORBEARANCE                   = 25771,
    SPELL_PALADIN_GRAND_CRUSADER                = 85043,
    SPELL_PALADIN_GRAND_CRUSADER_PROC           = 85416,
    SPELL_PALADIN_GREATER_BLESSING_OF_KINGS     = 203538,
    SPELL_PALADIN_GREATER_BLESSING_OF_WISDOM    = 203539,
    SPELL_PALADIN_HAMMER_OF_JUSTICE             = 853,
    SPELL_HAMMER_OF_RIGHTEOUS                   = 53595,
    SPELL_HAMMER_OF_RIGHTEOUS_LIGHT_WAVE        = 88263,
    SPELL_PALADIN_BLESSING_OF_SACRIFICE         = 6940,
    SPELL_PALADIN_HAND_OF_THE_PROTECTOR         = 213652,
    SPELL_PALADIN_HOLY_LIGHT                    = 82326,
    SPELL_PALADIN_HOLY_PRISM_ALLIES             = 114871,
    SPELL_PALADIN_HOLY_PRISM_DAMAGE_VISUAL      = 114862,
    SPELL_PALADIN_HOLY_PRISM_DAMAGE_VISUAL_2    = 114870,
    SPELL_PALADIN_HOLY_PRISM_ENNEMIES           = 114852,
    SPELL_PALADIN_HOLY_PRISM_HEAL_VISUAL        = 121551,
    SPELL_PALADIN_HOLY_PRISM_HEAL_VISUAL_2      = 121552,
    SPELL_PALADIN_HOLY_SHOCK_DAMAGE             = 25912,
    SPELL_PALADIN_HOLY_SHOCK_GENERIC            = 20473,
    SPELL_PALADIN_HOLY_SHOCK_HEAL               = 25914,
    SPELL_PALADIN_INFUSION_OF_LIGHT_AURA        = 54149,
    SPELL_PALADIN_JUDGMENT                      = 20271,
    SPELL_PALADIN_JUDGMENT_HOLY_DEBUFF          = 214222,
    SPELL_PALADIN_JUDGMENT_OF_LIGHT_HEAL        = 183811,
    SPELL_PALADIN_JUDGMENT_OF_LIGHT_TALENT      = 183778,
    SPELL_PALADIN_JUDGMENT_OF_LIGHT_TALENT_HEAL = 196941,
    SPELL_PALADIN_JUDGMENT_RETRI_DEBUFF         = 197277,
    SPELL_PALADIN_JUSTICARS_VENGEANCE           = 215661,
    SPELL_PALADIN_LIGHTS_HAMMER_TICK            = 114918,
    SPELL_PALADIN_LIGHT_HAMMER_COSMETIC         = 122257,
    SPELL_PALADIN_LIGHT_OF_DAWN                 = 85222,
    SPELL_PALADIN_LIGHT_OF_DAWN_TRIGGER         = 225311,
    SPELL_PALADIN_LIGHT_OF_THE_MARTYR           = 183998,
    SPELL_PALADIN_LIGHT_OF_THE_MARTYR_DAMAGE    = 196917,
    SPELL_PALADIN_LIGHT_OF_THE_PROTECTOR        = 184092,
    SPELL_PALADIN_RETRIBUTION_AURA_DAMAGE       = 204011,
    SPELL_PALADIN_RIGHTEOUS_PROTECTOR           = 204074,
    SPELL_PALADIN_RIGHTEOUS_VERDICT             = 267610,
    SPELL_PALADIN_RIGHTEOUS_VERDICT_PROC        = 267611,
    SPELL_PALADIN_SERAPHIM                      = 152262,
    SPELL_PALADIN_SHIELD_OF_THE_RIGHTEOUS       = 53600,
    SPELL_PALADIN_SHIELD_OF_THE_RIGHTEOUS_PROC  = 132403,
    SPELL_PALADIN_SHIELD_OF_VENGEANCE_DAMAGE    = 184689,
    SPELL_PALADIN_TEMPLARS_VERDICT              = 85256,
    SPELL_PALADIN_TEMPLARS_VERDICT_DAMAGE       = 224266,
    SPELL_PALADIN_THE_FIRES_OF_JUSTICE          = 209785,
    SPELL_PALADIN_WAKE_OF_ASHES                 = 255937,
    SPELL_PALADIN_WAKE_OF_ASHES_STUN            = 255941,
    SPELL_PALADIN_WORD_OF_GLORY                 = 210191,
    SPELL_PALADIN_WORD_OF_GLORY_HEAL            = 214894,
    SPELL_PALADIN_BLESSED_HAMMER                = 204019,
	SPELL_PALADIN_DEVOTION_AURA_TALENT			= 183425,
	SPELL_PALADIN_DEVOTION_AURA					= 210320,
	SPELL_PALADIN_RETRIBUTION					= 183436,
	SPELL_PALADIN_JUDGMENT_PROTE_RANK			= 231657,
    SPELL_PALADIN_AURA_OF_MERCY                 = 210291,
    SPELL_PALADIN_AURA_MASTERY                  = 31821,
    SPELL_PALADIN_ZEAL_BUFF                     = 269571,
    SPELL_PALADIN_ZEAL_DAMAGE                   = 269937,
    SPELL_PALADIN_CRUSADE                       = 231895,
    SPELL_PALADIN_JUDGMENT_HOLY                 = 275773,
    SPELL_PALADIN_AVENGING_CRUSADER             = 216331,
    SPELL_PALADIN_AVENGING_CRUSADER_HEAL        = 281465,
	SPELL_PALADIN_CONSEGRATION_AURA				= 188370,
	SPELL_PALADIN_AVENGERS_SHIELD_RANK2			= 231665,
    SPELL_PALADIN_HOLY_RITUAL                   = 199422,
	SPELL_PALADIN_HOLY_RITUAL_HEAL              = 199423,
    SPELL_PALADIN_DIVINE_PUNISHER_ENERGIZE      = 216762,
    SPELL_PALADIN_BEACON_OF_LIGTH_REFUND        = 231642,
    SPELL_PALADIN_FLASH_OF_LIGHT                = 19750,
    SPELL_PALADIN_HALLOWED_GROUND               = 216868,
    SPELL_PALADIN_HALLOWED_GROUND_INMUNITY      = 236198,
	SPELL_PALADIN_AVENGING_LIGHT				= 199441,
	SPELL_PALADIN_AVENGING_LIGHT_DAMAGE			= 199443,
    SPELL_PALADIN_JUDGMENT_ENERGIZE             = 220637,
	SPELL_PALADIN_DARKEST_BEFORE_THE_DAWN_BUFF	= 210391,
    SPELL_PALADIN_LIGHTBRINGER                  = 246806,
    SPELL_PALADIN_LIGHTBRINGER_DEBUFF           = 246807,
    SPELL_PALADIN_LIGHTBRINGER_DAMAGE           = 246867,
    SPELL_PALADIN_HAND_OF_HIDRANCE_SLOW         = 183218,
    SPELL_PALADIN_LAW_AND_ORDER                 = 204934,
    SPELL_PALADIN_DIVINE_HAMMER                 = 198034,
    SPELL_PALADIN_STEED_OF_GLORY                = 199542,
    SPELL_PALADIN_STEED_OF_GLORY_KNOCKBACK      = 199544,
    SPELL_PALADIN_STEED_OF_GLORY_IMMUNITY       = 199545,
	SPELL_PALADIN_SHIELD_OF_VENGANCE			= 184662,
	SPELL_PALADIN_HAMMER_OF_RECKONING			= 247675,
	SPELL_PALADIN_RECKONING						= 247677,
	SPELL_PALADIN_RECKONING_ACTIVATION			= 247676,
	SPELL_PALADIN_SELFESS_HEALER_AURA			= 114250,
	SPELL_PALADIN_ART_OF_WAR_PROC				= 231843,
    SPELL_BLADE_OF_WRATH                        = 231832,
    SPELL_BLADE_OF_WRATH_PROC                   = 281178,
	SPELL_PALADIN_LUMINESCENCE					= 199428,
	SPELL_PALADIN_LUMINESCENCE_HEAL				= 199435,
    SPELL_PALADIN_VENGEANCE_AURA_BUFF           = 210324,
    SPELL_PALADIN_AVENGER_MIGHT_POWER           = 272898,
    SPELL_PALADIN_AVENGER_MIGHT_BUFF            = 272903,
    SPELL_PALADIN_BEACONS_ENERGIZE              = 88852,
    SPELL_PALADIN_DIVINE_FAVOR_INTERRUPT        = 210303,
    SPELL_PALADIN_ULTIMATE_SACRIFICE_DAMAGE     = 199450,
    SPELL_PALADIN_AWAKENING                     = 248033,
    SPELL_PALADIN_AZERITE_INDOMITABLE_JUSTICE   = 275496,
    SPELL_PALADIN_DIVINE_JUDGMENT               = 271580,
    SPELL_PALADIN_DIVINE_JUDGMENT_AURA          = 271581,
    SPELL_PALADIN_SANCTIFIED_WRATH              = 53376,
    SPELL_PALADIN_LAST_DEFENDER                 = 203791,
    SPELL_PALADIN_GALLANT_STEED_POWER           = 280017,
    SPELL_PALADIN_GALLANT_STEED_AT              = 280191,
    SPELL_PALADIN_BREAKING_DAWN                 = 278594,
    SPELL_PALADIN_MOMENT_OF_COMPASSION          = 273513,
    SPELL_PALADIN_JUDGMENT_PROTECTION           = 275779,
    SPELL_PALADIN_AURA_OF_MERCY_AURA            = 183415,
    SPELL_PALADIN_CLEANSE_THE_WEAK              = 199330,
    SPELL_PALADIN_CLEANSE_THE_WEAK_DISPEL       = 199360,
    SPELL_PALADIN_SERAPHIMS_BLESSING_TRIGGER    = 210532,
    SPELL_PALADIN_SERAPHIMS_BLESSING_BUFF       = 248878,
    SPELL_PALADIN_SERAPHIMS_BLESSING_COOLDOWN   = 205069,
    SPELL_PALADIN_BLESSING_OF_FREEDOM           = 1044,
    SPELL_PALADIN_BLESSING_OF_PROTECTION        = 1022,
    SPELL_PALADIN_SPREADING_THE_WORD_PROTECTION = 199507,
    SPELL_PALADIN_SPREADING_THE_WORD_FREEDOM    = 199508,
    SPELL_PALADIN_BLESSING_OF_SACRIFICE_ULTI    = 199448,
    SPELL_PALADIN_PURE_OF_HEART_TRIGGER         = 210540,
    SPELL_PALADIN_PURE_OF_HEART_DISPEL          = 199427,
};

enum PaladinNPCs
{
    NPC_PALADIN_LIGHTS_HAMMER = 59738
};

enum PaladinSpellVisualKit
{
    PALADIN_VISUAL_KIT_DIVINE_STORM = 73892
};

class paladin_playerscript : public PlayerScript
{
public:
	paladin_playerscript() : PlayerScript("paladin_playerscript") {}

    void OnModifyPower(Player* player, Powers power, int32 oldValue, int32& newValue, bool regen, bool after) override
    {
        if (!player)
            return;

        // Retribution.
        if (player->GetSpecializationId() == TALENT_SPEC_PALADIN_RETRIBUTION)
        {
            if (oldValue <= newValue || regen || after)
                return;

            if (player->HasAura(SPELL_PALADIN_CRUSADE) && power == POWER_HOLY_POWER)
            {
                uint8 value = oldValue - newValue;
                Aura* aura = player->GetAura(SPELL_PALADIN_CRUSADE);
                if (aura->GetStackAmount() < 10)
                {
                    uint32 duration = aura->GetDuration();
                    player->GetAura(SPELL_PALADIN_CRUSADE)->ModStackAmount(value);
                    aura->SetDuration(duration);
                }
            }

            ///< Sanctified Wrath
            if (player->HasAura(317866) && power == POWER_HOLY_POWER && oldValue > newValue)
            {
                player->CastSpell(player, 326731, CastSpellExtraArgs(true));
            }
        }
    }

	void OnMapChanged(Player* player) 
	{
		if (!player)
			return;

		if (player->GetSpecializationId() == TALENT_SPEC_PALADIN_HOLY)
		{
			if (player->HasAura(SPELL_PALADIN_DEVOTION_AURA_TALENT))
                if (!player->GetAreaTrigger(SPELL_PALADIN_DEVOTION_AURA_TALENT))
				    player->AddAura(SPELL_PALADIN_DEVOTION_AURA_TALENT);
			else if (player->HasAura(SPELL_PALADIN_AURA_OF_SACRIFICE))
				if (!player->GetAreaTrigger(SPELL_PALADIN_AURA_OF_SACRIFICE))
				    player->AddAura(SPELL_PALADIN_AURA_OF_SACRIFICE);
		}
	}

    void OnSpellRemoved(Player* player, uint32 spellID) override
    {
        if (!player)
            return;

        // Holy Paladin
        if (player->GetSpecializationId() == TALENT_SPEC_PALADIN_HOLY)
        {
            if (spellID == SPELL_PALADIN_BEACON_OF_FAITH)
                player->RemoveAura(SPELL_PALADIN_BEACON_OF_FAITH_PROC_AURA);
        }

		// Retribution Paladin
		if (player->GetSpecializationId() == TALENT_SPEC_PALADIN_RETRIBUTION)
		{
			if (spellID == SPELL_PALADIN_HAMMER_OF_RECKONING)
				player->RemoveAura(SPELL_PALADIN_RECKONING);
		}
    }

    void OnSpellLearned(Player* player, uint32 spellID) override
    {
        if (!player)
            return;

        // Holy Paladin
        if (player->GetSpecializationId() == TALENT_SPEC_PALADIN_HOLY)
        {
            if (spellID == SPELL_PALADIN_BEACON_OF_VIRTUE)
                if (Aura* aura = player->GetAura(SPELL_PALADIN_BEACON_OF_LIGHT_PROC_AURA))
                {
                    Unit* owner = aura->GetCaster();
                    if (owner)
                        owner->RemoveAura(SPELL_PALADIN_BEACON_OF_LIGHT, player->GetGUID());
                    player->RemoveAura(SPELL_PALADIN_BEACON_OF_LIGHT_PROC_AURA);
                }
        }
    }

    void OnSuccessfulSpellCast(Player* player, Spell* spell) override
    {
        if (!player || !spell)
            return;

        if (player->GetSpecializationId() != TALENT_SPEC_PALADIN_RETRIBUTION)
            return;

        
        if (spell->GetSpellInfo() != nullptr)
        {
            AuraEffect* auraEffectFiresofJustice = player->GetAuraEffect(SPELL_PALADIN_THE_FIRES_OF_JUSTICE, EFFECT_0);
            AuraEffect* auraEffectDivinePurpose  = player->GetAuraEffect(SPELL_PALADIN_DIVINE_PURPOSE_RET_AURA, EFFECT_0);
            Aura*       auraDivinePurposePassive = player->GetAura(SPELL_PALADIN_DIVINE_PURPOSE_RET);

            if (auraEffectFiresofJustice != nullptr)
                if (auraEffectFiresofJustice->IsAffectingSpell(spell->GetSpellInfo()))
                    player->RemoveAura(SPELL_PALADIN_THE_FIRES_OF_JUSTICE);

            if (auraEffectDivinePurpose != nullptr)            
                if (auraEffectDivinePurpose->IsAffectingSpell(spell->GetSpellInfo()))
                    player->RemoveAura(SPELL_PALADIN_DIVINE_PURPOSE_RET_AURA);            

            if (auraDivinePurposePassive != nullptr)
                if (SpellPowerCost const* powerCost = spell->GetPowerCost(POWER_HOLY_POWER))
                    if (powerCost->Amount > 0)
                        if (SpellInfo const* spellInfo = auraDivinePurposePassive->GetSpellInfo())
                            if (roll_chance_i(spellInfo->GetEffect(EFFECT_0).BasePoints))
                                player->CastSpell(player, SPELL_PALADIN_DIVINE_PURPOSE_RET_AURA, true);
        }
    }
};

// Infusion of Light - 53576
class spell_pal_infusion_of_light : public AuraScript
{
    PrepareAuraScript(spell_pal_infusion_of_light);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        bool _spellCanProc = (eventInfo.GetSpellInfo()->Id == SPELL_PALADIN_HOLY_SHOCK_DAMAGE || eventInfo.GetSpellInfo()->Id == SPELL_PALADIN_HOLY_SHOCK_HEAL);

        if (_spellCanProc)
            return true;

        return false;
    }

    void HandleEffectProc(AuraEffect* /*aurEff*/, ProcEventInfo& /*eventInfo*/)
    {
        if(Unit* caster = GetCaster())
            caster->CastSpell(caster, SPELL_PALADIN_INFUSION_OF_LIGHT_AURA, true);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_pal_infusion_of_light::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_pal_infusion_of_light::HandleEffectProc, EFFECT_0, SPELL_AURA_PROC_TRIGGER_SPELL);
    }
};

// Holy Shock - 20473
class spell_pal_holy_shock : public SpellScript
{
    PrepareSpellScript(spell_pal_holy_shock);

    bool Validate(SpellInfo const* /*spell*/) override
    {
        return ValidateSpellInfo
        ({
            SPELL_PALADIN_HOLY_SHOCK_HEAL,
            SPELL_PALADIN_HOLY_SHOCK_DAMAGE
        });
    }

    SpellCastResult CheckCast()
    {
        Unit* caster = GetCaster();
        if (Unit* target = GetExplTargetUnit())
        {
            if (!caster->IsFriendlyTo(target))
            {
                if (!caster->IsValidAttackTarget(target))
                    return SPELL_FAILED_BAD_TARGETS;

                if (!caster->isInFront(target))
                    return SPELL_FAILED_UNIT_NOT_INFRONT;
            }
        }
        else
            return SPELL_FAILED_BAD_TARGETS;
        return SPELL_CAST_OK;
    }

    void HandleDummy(SpellEffIndex /*effIndex*/)
    {
        if (Player* caster = GetCaster()->ToPlayer())
        {
            if (Unit* unitTarget = GetHitUnit())
            {
                if (caster->IsFriendlyTo(unitTarget))
                    caster->CastSpell(unitTarget, SPELL_PALADIN_HOLY_SHOCK_HEAL, true);
                else
                    caster->CastSpell(unitTarget, SPELL_PALADIN_HOLY_SHOCK_DAMAGE, true);
            }
        }
    }

	void HandleAfterCast()
	{
		if (Unit* caster = GetCaster())
		{
			if (caster->HasAura(SPELL_PALADIN_DIVINE_PURPOSE_HOLY_AURA_1))
				caster->RemoveAurasDueToSpell(SPELL_PALADIN_DIVINE_PURPOSE_HOLY_AURA_1);

			if (Aura* aura = caster->GetAura(SPELL_PALADIN_DIVINE_PURPOSE_HOLY))
				if (roll_chance_i(aura->GetEffect(EFFECT_0)->GetAmount()))
				{
					caster->CastSpell(caster, SPELL_PALADIN_DIVINE_PURPOSE_HOLY_AURA_1, true);
					caster->GetSpellHistory()->ResetCooldown(SPELL_PALADIN_HOLY_SHOCK_GENERIC, true);
				}
		}
	}

    void Register() override
    {
        OnCheckCast += SpellCheckCastFn(spell_pal_holy_shock::CheckCast);
        OnEffectHitTarget += SpellEffectFn(spell_pal_holy_shock::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
		AfterCast += SpellCastFn(spell_pal_holy_shock::HandleAfterCast);
    }
};

// 19750 - Flash of Light / 82326 - Holy Light
class spell_pal_flash_of_light : public SpellScript
{
    PrepareSpellScript(spell_pal_flash_of_light);

    void HandleTakePower(SpellPowerCost& powerCost)
    {
        if (powerCost.Power == POWER_MANA)
            if (auto caster = GetCaster())
                caster->Variables.Set("HealCost", powerCost.Amount);
    }

    void HandleOnHit(SpellEffIndex /*effIndex*/)
    {
		Unit* caster = GetCaster();
		Unit* target = GetExplTargetUnit();
		if (!caster || !target)
			return;

        int32 heal = GetHitHeal();

        // Moment of Compassion.
        if (Aura* aura = caster->GetAura(SPELL_PALADIN_MOMENT_OF_COMPASSION))
            if (target->HasAura(SPELL_PALADIN_BEACON_OF_LIGHT, caster->GetGUID()) && GetSpellInfo()->Id == SPELL_PALADIN_FLASH_OF_LIGHT)
                SetHitHeal(heal + aura->GetEffect(EFFECT_0)->GetAmount());

        caster->RemoveAurasDueToSpell(SPELL_PALADIN_INFUSION_OF_LIGHT_AURA);
    }

	void HandleAfterCast()
	{
		if (Unit* caster = GetCaster())
			caster->RemoveAurasDueToSpell(SPELL_PALADIN_SELFESS_HEALER_AURA);
	}

    void Register() override
    {
        OnTakePower += SpellOnTakePowerFn(spell_pal_flash_of_light::HandleTakePower);
        OnEffectHitTarget += SpellEffectFn(spell_pal_flash_of_light::HandleOnHit, EFFECT_0, SPELL_EFFECT_HEAL);
		AfterCast += SpellCastFn(spell_pal_flash_of_light::HandleAfterCast);
    }
};

// Crusader Strike - 35395
class spell_pal_crusader_strike : public SpellScript
{
    PrepareSpellScript(spell_pal_crusader_strike);

    void HandleOnHit(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();

        if (caster->HasAura(SPELL_PALADIN_CRUSADERS_MIGHT))
        {
            if (caster->GetSpellHistory()->HasCooldown(SPELL_PALADIN_HOLY_SHOCK_GENERIC))
                caster->GetSpellHistory()->ModifyCooldown(SPELL_PALADIN_HOLY_SHOCK_GENERIC, -1.5 * IN_MILLISECONDS);

            if (caster->GetSpellHistory()->HasCooldown(SPELL_PALADIN_LIGHT_OF_DAWN))
                caster->GetSpellHistory()->ModifyCooldown(SPELL_PALADIN_LIGHT_OF_DAWN, -1.5 * IN_MILLISECONDS);
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_pal_crusader_strike::HandleOnHit, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

// Light of the Protector - 184092 and Hand of the Protector - 213652
class spell_pal_light_of_the_protector : public SpellScript
{
    PrepareSpellScript(spell_pal_light_of_the_protector);

    void HandleOnHit(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        uint32 heal;

        if (GetSpellInfo()->Id == SPELL_PALADIN_LIGHT_OF_THE_PROTECTOR)
        {
            float healthPct = 100.0f - caster->GetHealthPct();

			heal = GetHitHeal() + GetHitHeal() * ((healthPct * 2) / 100);

            if (caster->FindNearestCreature(43499, 8) && caster->HasAura(SPELL_PALADIN_CONSECRATION)) // if you are standing in your consecration, the heal is increased by 20%
                AddPct(heal, 20);
        }

        if (GetSpellInfo()->Id == SPELL_PALADIN_HAND_OF_THE_PROTECTOR)
        {
			float healthPct = 100.0f - caster->GetHealthPct();

			heal = GetHitHeal() + GetHitHeal() * ((healthPct * 2) / 100);
        }

        heal = std::max(heal, (uint32)0);

        SetHitHeal(heal);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_pal_light_of_the_protector::HandleOnHit, EFFECT_0, SPELL_EFFECT_HEAL);
    }
};

// 53600 - Shield of the Righteous
class spell_pal_shield_of_the_righteous : public SpellScript
{
    PrepareSpellScript(spell_pal_shield_of_the_righteous);

	bool Validate(SpellInfo const* /*spellInfo*/) override
	{
		return ValidateSpellInfo({ SPELL_PALADIN_SHIELD_OF_THE_RIGHTEOUS_PROC });
	}

	void HandleOnHit(SpellEffIndex /*effIndex*/)
	{
		Unit* caster = GetCaster();
		Unit* target = GetHitUnit();
		if (!caster || !target)
			return;

		targetHit = true;
		if (Aura* aura = caster->GetAura(SPELL_PALADIN_RIGHTEOUS_PROTECTOR)) //reduce the CD of Light of the Protector and Avenging Wrath by 3
		{
			int32 cooldownReduction = aura->GetEffect(EFFECT_0)->GetBaseAmount() * IN_MILLISECONDS;

			if (caster->HasSpell(SPELL_PALADIN_LIGHT_OF_THE_PROTECTOR))
				if (SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(SPELL_PALADIN_LIGHT_OF_THE_PROTECTOR))
					caster->GetSpellHistory()->ReduceChargeCooldown(spellInfo->ChargeCategoryId, cooldownReduction);

			if (caster->HasSpell(SPELL_PALADIN_HAND_OF_THE_PROTECTOR))
				if (SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(SPELL_PALADIN_HAND_OF_THE_PROTECTOR))
					caster->GetSpellHistory()->ReduceChargeCooldown(spellInfo->ChargeCategoryId, cooldownReduction);

            if (caster->GetSpellHistory()->HasCooldown(SPELL_PALADIN_AVENGING_WRATH))
                caster->GetSpellHistory()->ModifyCooldown(SPELL_PALADIN_AVENGING_WRATH, -cooldownReduction);
		}

        auto dmg = GetHitDamage();
        if (caster->Variables.Exist("EmpoweredShieldOfTheRighteous"))
            if (caster->Variables.GetValue("EmpoweredShieldOfTheRighteous", false))
                AddPct(dmg, 25);
        SetHitDamage(dmg);
	}

	void HandleAfterCast()
	{
		if (Unit* caster = GetCaster())
			if (targetHit)
				caster->CastSpell(caster, SPELL_PALADIN_SHIELD_OF_THE_RIGHTEOUS_PROC, true);
	}

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_pal_shield_of_the_righteous::HandleOnHit, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
		AfterCast += SpellCastFn(spell_pal_shield_of_the_righteous::HandleAfterCast);
    }

private:
	bool targetHit = false;
};

// Grand Crusader - 85416
// 204019 - Blessed Hammer / Hammer of the Righteous - 53595
class spell_pal_grand_crusader : public SpellScript
{
    PrepareSpellScript(spell_pal_grand_crusader);

    void HandleAfterCast()
    {
        Unit* caster = GetCaster();
        if (!caster)
            return;

        //if caster is standing in his consecration create a "wave of light"
        if (GetSpellInfo()->Id == SPELL_HAMMER_OF_RIGHTEOUS)
            if (caster->HasAura(SPELL_PALADIN_CONSEGRATION_AURA))
                caster->CastSpell(caster, SPELL_HAMMER_OF_RIGHTEOUS_LIGHT_WAVE, true);

        if (!caster->HasAura(SPELL_PALADIN_GRAND_CRUSADER))
            return;

        int32 grandCrusaderProcChance = 15;

        if (caster->HasAura(SPELL_PALADIN_FIRST_AVENGER))
            grandCrusaderProcChance += 10;

        if (roll_chance_i(grandCrusaderProcChance))
        {
            caster->CastSpell(caster, SPELL_PALADIN_GRAND_CRUSADER_PROC, true);
            caster->GetSpellHistory()->ResetCooldown(SPELL_PALADIN_AVENGERS_SHIELD, true);

            if (caster->HasAura(SPELL_PALADIN_CRUSADERS_JUDGMENT))
                caster->GetSpellHistory()->RestoreCharge(sSpellMgr->AssertSpellInfo(SPELL_PALADIN_JUDGMENT)->ChargeCategoryId);
        }
    }

    void Register() override
    {
        AfterCast += SpellCastFn(spell_pal_grand_crusader::HandleAfterCast);
    }
};

// 31935 - Avenger's Shield
class spell_pal_avengers_shield : public SpellScript
{
    PrepareSpellScript(spell_pal_avengers_shield);

    void HandleOnHit(SpellEffIndex /* effIndex */)
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
		Unit* mainTarget = GetExplTargetUnit();
        if (!caster || !target || !mainTarget)
            return;

        if (caster->HasAura(SPELL_PALADIN_GRAND_CRUSADER_PROC))
            caster->RemoveAurasDueToSpell(SPELL_PALADIN_GRAND_CRUSADER_PROC);

        int32 damage = GetHitDamage();

        if (caster->HasAura(SPELL_PALADIN_FIRST_AVENGER) && target->GetGUID() == mainTarget->GetGUID())
            AddPct(damage, 50);

        SetHitDamage(damage);
    }

	void HandleOnHitEffects(SpellEffIndex effIndex)
	{
		Unit* caster = GetCaster();
		Unit* target = GetHitUnit();
		if (!caster || !target)
			return;

		if (!caster->HasAura(SPELL_PALADIN_AVENGERS_SHIELD_RANK2) || target->IsPlayer())
			PreventHitAura();
	}

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_pal_avengers_shield::HandleOnHit, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
		OnEffectHitTarget += SpellEffectFn(spell_pal_avengers_shield::HandleOnHitEffects, EFFECT_2, SPELL_EFFECT_APPLY_AURA);
    }
};

// 205191 - Eye for an Eye
class spell_pal_eye_for_an_eye : public AuraScript
{
    PrepareAuraScript(spell_pal_eye_for_an_eye);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_PALADIN_EYE_FOR_AN_EYE_DAMAGE });
    }

    void HandleEffectProc(AuraEffect* /*aurEff*/, ProcEventInfo& eventInfo)
    {
        GetTarget()->CastSpell(eventInfo.GetProcTarget(), SPELL_PALADIN_EYE_FOR_AN_EYE_DAMAGE, true);
    }

    void Register() override
    {
        OnEffectProc += AuraEffectProcFn(spell_pal_eye_for_an_eye::HandleEffectProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

// 184662 - Shield of Vengeance
class spell_pal_shield_of_vengeance : public AuraScript
{
    PrepareAuraScript(spell_pal_shield_of_vengeance);

    int32 currentAbsorb;

    void CalculateAmount(AuraEffect const* /*aurEff*/, int32& amount, bool& canBeRecalculated)
    {
		canBeRecalculated = false;
		if (Unit* caster = GetCaster())
			amount = CalculatePct(caster->GetMaxHealth(), sSpellMgr->GetSpellInfo(SPELL_PALADIN_SHIELD_OF_VENGANCE)->GetEffect(EFFECT_1).BasePoints);
    }

    void Absorb(AuraEffect* /*aurEff*/, DamageInfo& dmgInfo, uint32& /*absorbAmount*/)
    {
        Unit* caster = GetCaster();
        if (!caster)
            return;

        currentAbsorb += dmgInfo.GetDamage();
    }

    void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Unit* caster = GetCaster();
        if (!caster || currentAbsorb == 0)
            return;

        std::list<Unit*> targets;
        caster->GetAttackableUnitListInRange(targets, 8.0f);

		if (uint32 targetSize = targets.size())
           currentAbsorb /= targetSize;

        caster->CastCustomSpell(SPELL_PALADIN_SHIELD_OF_VENGEANCE_DAMAGE, SPELLVALUE_BASE_POINT0, currentAbsorb, caster, true);
    }

    void Register() override
    {
        DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_pal_shield_of_vengeance::CalculateAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
        OnEffectRemove += AuraEffectRemoveFn(spell_pal_shield_of_vengeance::OnRemove, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB, AURA_EFFECT_HANDLE_REAL);
        OnEffectAbsorb += AuraEffectAbsorbFn(spell_pal_shield_of_vengeance::Absorb, EFFECT_0);
    }
};

// 85256 - Templar's Verdict
class spell_pal_templar_s_verdict : public SpellScript
{
    PrepareSpellScript(spell_pal_templar_s_verdict);

    bool Validate(SpellInfo const* /*spellEntry*/) override
    {
        return ValidateSpellInfo({ SPELL_PALADIN_TEMPLARS_VERDICT_DAMAGE });
    }

    void HandleOnHit(SpellEffIndex /*effIndex*/)
    {
        if (Unit* caster = GetCaster())
        {
            if (Unit* target = GetExplTargetUnit())
                caster->CastSpell(target, SPELL_PALADIN_TEMPLARS_VERDICT_DAMAGE, true);

            if (caster->HasAura(SPELL_PALADIN_RIGHTEOUS_VERDICT))
            {
                if (caster->HasAura(SPELL_PALADIN_RIGHTEOUS_VERDICT_PROC))
                    caster->RemoveAurasDueToSpell(SPELL_PALADIN_RIGHTEOUS_VERDICT_PROC);
                else
                    caster->CastSpell(caster, SPELL_PALADIN_RIGHTEOUS_VERDICT_PROC, true);
            }

            if (caster->HasAura(SPELL_PALADIN_DIVINE_JUDGMENT))
                caster->CastSpell(caster, SPELL_PALADIN_DIVINE_JUDGMENT_AURA, true);

            // $mult=${($max(0, $min($pl - 10, 10)) * 11 + 290) / 400}
            float mult = std::max(0, std::min(caster->GetLevel() - 10, 10) * 11 + 290) / 400;

            SetHitDamage(GetHitDamage() * mult);
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_pal_templar_s_verdict::HandleOnHit, EFFECT_0, SPELL_EFFECT_DUMMY);
    }

private:
    uint8 m_powerTaken = 0;
};

// 190784 - Divine Steed
class spell_pal_divine_steed : public SpellScript
{
    PrepareSpellScript(spell_pal_divine_steed);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo
        ({
            SPELL_PALADIN_DIVINE_STEED_SPEED,
            SPELL_PALADIN_DIVINE_STEED_HUMAN,
            SPELL_PALADIN_DIVINE_STEED_DRAENEI,
            SPELL_PALADIN_DIVINE_STEED_BLOODELF,
            SPELL_PALADIN_DIVINE_STEED_TAUREN,
            SPELL_PALADIN_DIVINE_STEED_DWARF,
            SPELL_PALADIN_DIVINE_STEED_DARK_IRON_DWARF,
            SPELL_PALADIN_DIVINE_STEED_AURA_GOLDEN,
            SPELL_PALADIN_DIVINE_STEED_AURA_VENGEFUL,
            SPELL_PALADIN_DIVINE_STEED_AURA_VALOROUS,
            SPELL_PALADIN_DIVINE_STEED_AURA_VIGILANT,
            SPELL_PALADIN_DIVINE_STEED_GOLDEN,
            SPELL_PALADIN_DIVINE_STEED_VENGEFUL,
            SPELL_PALADIN_DIVINE_STEED_VALOROUS,
            SPELL_PALADIN_DIVINE_STEED_VIGILANT
        });
    }

    void HandleOnHit()
    {
        if (Player* target = GetHitPlayer())
        {
            uint32 spellId = SPELL_PALADIN_DIVINE_STEED_HUMAN;
            //if you have aura Golden Charger's Bridle them
            if (target->HasAura(SPELL_PALADIN_DIVINE_STEED_GOLDEN))
                spellId = SPELL_PALADIN_DIVINE_STEED_AURA_GOLDEN;
            //if you have aura Vengeful Charger's Bridle them
            else if (target->HasAura(SPELL_PALADIN_DIVINE_STEED_VENGEFUL))
                spellId = SPELL_PALADIN_DIVINE_STEED_AURA_VENGEFUL;
            //if you have aura Valorous Charger's Bridle them
            else if (target->HasAura(SPELL_PALADIN_DIVINE_STEED_VALOROUS))
                spellId = SPELL_PALADIN_DIVINE_STEED_AURA_VALOROUS;
            //if you have aura Vigilant Charger's Bridle them
            else if (target->HasAura(SPELL_PALADIN_DIVINE_STEED_VIGILANT))
                spellId = SPELL_PALADIN_DIVINE_STEED_AURA_VIGILANT;

            if (spellId == SPELL_PALADIN_DIVINE_STEED_HUMAN)
            {
                switch (target->GetRace())
                {
                case RACE_HUMAN:
                    spellId = SPELL_PALADIN_DIVINE_STEED_HUMAN;
                    break;
                case RACE_DWARF:
                    spellId = SPELL_PALADIN_DIVINE_STEED_DWARF;
                    break;
                case RACE_DARK_IRON_DWARF:
                    spellId = SPELL_PALADIN_DIVINE_STEED_DARK_IRON_DWARF;
                    break;
                case RACE_DRAENEI:
                case RACE_LIGHTFORGED_DRAENEI:
                    spellId = SPELL_PALADIN_DIVINE_STEED_DRAENEI;
                    break;
                case RACE_BLOODELF:
                    spellId = SPELL_PALADIN_DIVINE_STEED_BLOODELF;
                    break;
                case RACE_TAUREN:
                    spellId = SPELL_PALADIN_DIVINE_STEED_TAUREN;
                    break;
                default:
                    break;
                }
            }

            target->CastSpell(target, spellId, true);
        }
    }

    void Register() override
    {
        OnHit += SpellHitFn(spell_pal_divine_steed::HandleOnHit);
    }
};

// Activate Forbearance
// Called by Blessing of Protection - 1022, Lay on Hands - 633, Blessing of Spellwarding - 204018
class spell_pal_activate_forbearance : public SpellScript
{
    PrepareSpellScript(spell_pal_activate_forbearance);

    bool Validate(SpellInfo const* /*spell*/) override
    {
        return ValidateSpellInfo({ SPELL_PALADIN_FORBEARANCE });
    }

    SpellCastResult CheckForbearance()
    {
        if (Unit* target = GetExplTargetUnit())
        {
            if (target->HasAura(SPELL_PALADIN_FORBEARANCE))
            {
                return SPELL_FAILED_TARGET_AURASTATE;
            }
        }
        return SPELL_CAST_OK;
    }

    void HandleOnHit()
    {
        if (Player* player = GetCaster()->ToPlayer())
            if (Unit* target = GetHitUnit())
                player->CastSpell(target, SPELL_PALADIN_FORBEARANCE, true);
    }

    void Register() override
    {
        OnCheckCast += SpellCheckCastFn(spell_pal_activate_forbearance::CheckForbearance);
        OnHit += SpellHitFn(spell_pal_activate_forbearance::HandleOnHit);
    }
};

// Divine Shield - 642
class spell_pal_divine_shield : public SpellScript
{
    PrepareSpellScript(spell_pal_divine_shield);

    bool Validate(SpellInfo const* /*spell*/) override
    {
        return ValidateSpellInfo({ SPELL_PALADIN_FORBEARANCE });
    }

    SpellCastResult CheckForbearance()
    {
        if (Unit* caster = GetCaster())
        {
            if (caster->HasAura(SPELL_PALADIN_FORBEARANCE))
                return SPELL_FAILED_TARGET_AURASTATE;
        }
        return SPELL_CAST_OK;
    }

    void HandleOnCast()
    {
        if (Player* player = GetCaster()->ToPlayer())
        {
            player->CastSpell(player, SPELL_PALADIN_FORBEARANCE, true);

            if (player->HasSpell(SPELL_PALADIN_FINAL_STAND))
                player->CastSpell(player, SPELL_PALADIN_FINAL_STAND_TAUNT, true);
        }
    }

    void Register() override
    {
        OnCheckCast += SpellCheckCastFn(spell_pal_divine_shield::CheckForbearance);
        OnCast += SpellCastFn(spell_pal_divine_shield::HandleOnCast);
    }
};

// Justicar's Vengeance - 215661
class spell_pal_justicars_vengeance : public SpellScript
{
    PrepareSpellScript(spell_pal_justicars_vengeance);

    void HandleHit()
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!target)
            return;

        if (target->HasAuraType(SPELL_AURA_MOD_STUN) || target->HasAuraWithMechanic(1 << MECHANIC_STUN))
        {
            int32 damage = GetHitDamage();
            AddPct(damage, GetEffectInfo(EFFECT_1).BasePoints);

            SetHitDamage(damage);
            SetEffectValue(damage);
        }

        if (caster->HasAura(SPELL_PALADIN_DIVINE_JUDGMENT))
            caster->CastSpell(caster, SPELL_PALADIN_DIVINE_STORM_DAMAGE, true);
    }


    void Register() override
    {
        AfterHit += SpellHitFn(spell_pal_justicars_vengeance::HandleHit);
    }

private:
    uint8 m_powerTaken = 0;
};


// The fires of Justice - 203316
class spell_pal_the_fire_of_justice : public AuraScript
{
    PrepareAuraScript(spell_pal_the_fire_of_justice);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetSpellInfo()->Id == SPELL_PALADIN_CRUSADER_STRIKE)
            return true;

        return false;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_pal_the_fire_of_justice::CheckProc);
    }
};

// 210191 - Word of Glory
class spell_pal_word_of_glory : public SpellScript
{
    PrepareSpellScript(spell_pal_word_of_glory);

    WorldObject* m_mainTarget;

    void HandleDummy(SpellEffIndex effIndex)
    {
        m_mainTarget = GetHitUnit();
    }

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        uint32 const maxTargets = uint32(GetSpellInfo()->GetEffect(EFFECT_0).CalcValue(GetCaster()));

        if (m_mainTarget)
            targets.remove(m_mainTarget);

        if (targets.size() > maxTargets)
        {
            targets.sort(Trinity::HealthPctOrderPred());
            targets.resize(maxTargets);
        }

        if (m_mainTarget)
            targets.push_back(m_mainTarget);

        _targets = targets;
    }

    void SetTargets(std::list<WorldObject*>& targets)
    {
        targets = _targets;
    }
    
    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_pal_word_of_glory::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }

private:
    std::list<WorldObject*> _targets;
};

// 152262 - Seraphim
class spell_pal_seraphim : public SpellScript
{
    PrepareSpellScript(spell_pal_seraphim);

    bool Validate(SpellInfo const* /*spell*/) override
    {
        return ValidateSpellInfo({ SPELL_PALADIN_SERAPHIM, SPELL_PALADIN_SHIELD_OF_THE_RIGHTEOUS });
    }

    SpellCastResult CheckCast()
    {
        uint32 ChargeCategoryId = sSpellMgr->GetSpellInfo(SPELL_PALADIN_SHIELD_OF_THE_RIGHTEOUS)->ChargeCategoryId;
        if (!GetCaster()->GetSpellHistory()->HasCharge(ChargeCategoryId))
            return SPELL_FAILED_NO_POWER;

        return SPELL_FAILED_SUCCESS;
    }

    void HandleDummy(SpellEffIndex effIndex)
    {
        uint32 ChargeCategoryId = sSpellMgr->GetSpellInfo(SPELL_PALADIN_SHIELD_OF_THE_RIGHTEOUS)->ChargeCategoryId;
        SpellHistory* spellHistory = GetCaster()->GetSpellHistory();

        int32 useCharges = std::min((int32)GetSpellInfo()->GetEffect(effIndex).BasePoints, spellHistory->GetChargeCount(ChargeCategoryId));

        for (uint8 i = 0; i < useCharges; ++i)
            spellHistory->ConsumeCharge(ChargeCategoryId);

        if (Aura* seraphimAura = GetCaster()->GetAura(SPELL_PALADIN_SERAPHIM))
            seraphimAura->SetDuration(GetSpellInfo()->GetMaxDuration() * useCharges);

        spellHistory->ForceSendSpellCharge(sSpellCategoryStore.LookupEntry(ChargeCategoryId));
    }

    void Register() override
    {
        OnCheckCast += SpellCheckCastFn(spell_pal_seraphim::CheckCast);
        OnEffectHitTarget += SpellEffectFn(spell_pal_seraphim::HandleDummy, EFFECT_1, SPELL_EFFECT_DUMMY);
    }
};

// 20271 - Judgement (vindict)
//275773 - Judgement (holy)
//275779 - Judgement (prot)
class spell_pal_judgment : public SpellScript
{
    PrepareSpellScript(spell_pal_judgment);

    void HandleDummy(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetExplTargetUnit();
        if (!caster || !target)
            return;

        Player* player = caster->ToPlayer();
        if (!player)
            return;

        uint32 spec = player->GetSpecializationId();
        if (player->HasAura(SPELL_PALADIN_JUDGMENT_OF_LIGHT_TALENT))
            player->CastSpell(target, SPELL_PALADIN_JUDGMENT_OF_LIGHT_TALENT_HEAL, true);
        switch (spec)
        {
            case TALENT_SPEC_PALADIN_RETRIBUTION:
            {
                player->CastSpell(target, SPELL_PALADIN_JUDGMENT_RETRI_DEBUFF, true);
                if (player->HasAura(SPELL_PALADIN_LIGHTBRINGER))
                {
                    player->CastSpell(player, SPELL_PALADIN_LIGHTBRINGER_DAMAGE, true);
                    player->CastSpell(target, SPELL_PALADIN_LIGHTBRINGER_DEBUFF, true);
                }

                if (Aura* aura = player->GetAura(SPELL_PALADIN_AZERITE_INDOMITABLE_JUSTICE))
                    if (player->GetHealthPct() > target->GetHealthPct())
                    {
                        int32 damage = GetHitDamage();
                        SetHitDamage(damage + aura->GetEffect(EFFECT_0)->GetAmount());
                    }
                break;
            }
            case TALENT_SPEC_PALADIN_HOLY:
                player->CastSpell(target, SPELL_PALADIN_JUDGMENT_HOLY_DEBUFF);
                break;
            case TALENT_SPEC_PALADIN_PROTECTION:
            {
				if (Aura* aura = player->GetAura(SPELL_PALADIN_JUDGMENT_PROTE_RANK))
				{
					auto effect = sSpellMgr->GetSpellInfo(SPELL_PALADIN_JUDGMENT_PROTE_RANK)->GetEffect(EFFECT_0);
					uint8 reduction = (IsHitCrit()) ? effect.BasePoints * 2 : effect.BasePoints;
					player->GetSpellHistory()->ReduceChargeCooldown(sSpellMgr->GetSpellInfo(SPELL_PALADIN_SHIELD_OF_THE_RIGHTEOUS)->ChargeCategoryId, reduction * IN_MILLISECONDS);
				}
                break;
            }
        }
    }

    void HandleAfterCaster()
    {
        if (Unit* caster = GetCaster())
            if (GetSpellInfo()->Id == SPELL_PALADIN_JUDGMENT)
                caster->CastSpell(caster, SPELL_PALADIN_JUDGMENT_ENERGIZE, true);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_pal_judgment::HandleDummy, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
        AfterCast += SpellCastFn(spell_pal_judgment::HandleAfterCaster);
    }
};

//7.3.2.25549 END

// 216860 - Judgement of the Pure
class spell_pal_judgement_of_the_pure : public SpellScriptLoader
{
public:
    spell_pal_judgement_of_the_pure() : SpellScriptLoader("spell_pal_judgement_of_the_pure") {}

    class spell_pal_judgement_of_the_pure_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_pal_judgement_of_the_pure_AuraScript);

        bool HandleProc(ProcEventInfo& eventInfo)
        {
            if (eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == SPELL_PALADIN_JUDGMENT)
                return true;
            return false;
        }

        void Register() override
        {
            DoCheckProc += AuraCheckProcFn(spell_pal_judgement_of_the_pure_AuraScript::HandleProc);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_pal_judgement_of_the_pure_AuraScript();
    }
};

// 6940 - Hand of Sacrifice
class spell_pal_hand_of_sacrifice : public AuraScript
{
    PrepareAuraScript(spell_pal_hand_of_sacrifice);

    void Split(AuraEffect* /*aurEff*/, DamageInfo& dmgInfo, uint32& splitAmount)
    {
        Unit* caster = GetCaster();
        Unit* target = GetTarget();
        if (!caster || !target)
            return;

        uint64 health = caster->GetHealth();
        if (health - splitAmount <= CalculatePct(caster->GetMaxHealth(), sSpellMgr->GetSpellInfo(SPELL_PALADIN_BLESSING_OF_SACRIFICE)->GetEffect(EFFECT_2).BasePoints))
            target->RemoveAura(SPELL_PALADIN_BLESSING_OF_SACRIFICE, caster->GetGUID());

        if (health - splitAmount <= 0)
            target->RemoveAura(SPELL_PALADIN_BLESSING_OF_SACRIFICE, caster->GetGUID());
    }

    void Register() override
    {
        OnEffectSplit += AuraEffectSplitFn(spell_pal_hand_of_sacrifice::Split, EFFECT_0);
    }
};

// Holy Prism - 114165
class spell_pal_holy_prism : public SpellScriptLoader
{
public:
    spell_pal_holy_prism() : SpellScriptLoader("spell_pal_holy_prism") { }

    class spell_pal_holy_prism_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_pal_holy_prism_SpellScript);

        void HandleOnHit()
        {
            if (Player* player = GetCaster()->ToPlayer())
            {
                if (Unit* target = GetHitUnit())
                {
                    if (player->IsValidAttackTarget(target))
                    {
                        player->CastSpell(target, SPELL_PALADIN_HOLY_PRISM_DAMAGE_VISUAL, true);
                        player->CastSpell(target, SPELL_PALADIN_HOLY_PRISM_DAMAGE_VISUAL_2, true);
                    }
                    else
                    {
                        player->CastSpell(target, SPELL_PALADIN_HOLY_PRISM_HEAL_VISUAL, true);
                        player->CastSpell(target, SPELL_PALADIN_HOLY_PRISM_HEAL_VISUAL_2, true);
                    }
                }
            }
        }

        void Register() override
        {
            OnHit += SpellHitFn(spell_pal_holy_prism_SpellScript::HandleOnHit);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_pal_holy_prism_SpellScript();
    }
};

// Holy Prism (damage) - 114852 or Holy Prism (heal) - 114871
// Called by Holy Prism (visual damage) - 114862 or Holy Prism (visual heal) - 121551
class spell_pal_holy_prism_effect : public SpellScriptLoader
{
public:
    spell_pal_holy_prism_effect() : SpellScriptLoader("spell_pal_holy_prism_effect") { }

    class spell_pal_holy_prism_effect_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_pal_holy_prism_effect_SpellScript);

        void HandleOnHit()
        {
            if (Player* player = GetCaster()->ToPlayer())
            {
                if (Unit* target = GetHitUnit())
                {
                    // damage
                    if (GetSpellInfo()->Id == 114862)
                        player->CastSpell(target, SPELL_PALADIN_HOLY_PRISM_ENNEMIES, true);
                    // heal
                    else if (GetSpellInfo()->Id == 121551)
                        player->CastSpell(target, SPELL_PALADIN_HOLY_PRISM_ALLIES, true);
                }
            }
        }

        void Register() override
        {
            OnHit += SpellHitFn(spell_pal_holy_prism_effect_SpellScript::HandleOnHit);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_pal_holy_prism_effect_SpellScript();
    }
};

// Called by Holy Prism (heal) - 114852 or Holy Prism (damage) - 114871
class spell_pal_holy_prism_visual : public SpellScriptLoader
{
public:
    spell_pal_holy_prism_visual() : SpellScriptLoader("spell_pal_holy_prism_visual") { }

    class spell_pal_holy_prism_visual_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_pal_holy_prism_visual_SpellScript);

        void HandleOnHit()
        {
            if (Player* player = GetCaster()->ToPlayer())
            {
                if (Unit* target = GetHitUnit())
                {
                    if (player->IsValidAttackTarget(target))
                    {
                        player->CastSpell(target, SPELL_PALADIN_HOLY_PRISM_DAMAGE_VISUAL_2, true);
                        player->CastSpell(target, SPELL_PALADIN_HOLY_PRISM_DAMAGE_VISUAL_2, true);
                    }
                    else
                    {
                        player->CastSpell(target, SPELL_PALADIN_HOLY_PRISM_HEAL_VISUAL_2, true);
                        player->CastSpell(target, SPELL_PALADIN_HOLY_PRISM_HEAL_VISUAL_2, true);
                    }
                }
            }
        }

        void Register() override
        {
            OnHit += SpellHitFn(spell_pal_holy_prism_visual_SpellScript::HandleOnHit);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_pal_holy_prism_visual_SpellScript();
    }
};

// Light of the Martyr - 183998
//Last Update 8.0.1 Build 28153
class spell_pal_light_of_the_martyr : public SpellScript
{
    PrepareSpellScript(spell_pal_light_of_the_martyr);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        if (!sSpellMgr->GetSpellInfo(SPELL_PALADIN_LIGHT_OF_THE_MARTYR_DAMAGE))
            return false;
        return true;
    }

    void HandleOnHit(SpellEffIndex /*effIndex*/)
    {
        if (Unit* caster = GetCaster())
            if (caster->HasAura(SPELL_PALADIN_FERVENT_MARTYR_BUFF))
                caster->RemoveAurasDueToSpell(SPELL_PALADIN_FERVENT_MARTYR_BUFF);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_pal_light_of_the_martyr::HandleOnHit, EFFECT_0, SPELL_EFFECT_HEAL);
    }
};

// 219562 - Light of the Martyr
//Last Update 8.0.1 Build 28153
class aura_pal_light_of_the_martyr : public AuraScript
{
    PrepareAuraScript(aura_pal_light_of_the_martyr);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo
        ({
            SPELL_PALADIN_LIGHT_OF_THE_MARTYR,
            SPELL_PALADIN_LIGHT_OF_THE_MARTYR_DAMAGE
            });
    }

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetHealInfo() && eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == SPELL_PALADIN_LIGHT_OF_THE_MARTYR;
    }

    void OnProc(AuraEffect* aurEff, ProcEventInfo& eventInfo)
    {
        int32 damage = CalculatePct(eventInfo.GetHealInfo()->GetHeal(), aurEff->GetAmount());
        GetTarget()->CastCustomSpell(GetTarget(), SPELL_PALADIN_LIGHT_OF_THE_MARTYR_DAMAGE, &damage, nullptr, nullptr, true);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_pal_light_of_the_martyr::CheckProc);
        OnEffectProc += AuraEffectProcFn(aura_pal_light_of_the_martyr::OnProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

// Bastion of Light - 204035
class spell_pal_bastion_of_light : public SpellScriptLoader
{
public:
    spell_pal_bastion_of_light() : SpellScriptLoader("spell_pal_bastion_of_light") {}

    class spell_pal_bastion_of_light_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_pal_bastion_of_light_SpellScript);

        void HandleOnHit(SpellEffIndex /*effIndex*/)
        {
            Unit* caster = GetCaster();

            caster->GetSpellHistory()->ResetCharges(sSpellMgr->GetSpellInfo(SPELL_PALADIN_SHIELD_OF_THE_RIGHTEOUS)->ChargeCategoryId);
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_pal_bastion_of_light_SpellScript::HandleOnHit, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_pal_bastion_of_light_SpellScript();
    }
};

// Light of Dawn - 85222
class spell_pal_light_of_dawn : public SpellScriptLoader
{
public:
    spell_pal_light_of_dawn() : SpellScriptLoader("spell_pal_light_of_dawn") {}

    class spell_pal_light_of_dawn_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_pal_light_of_dawn_SpellScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_PALADIN_LIGHT_OF_DAWN_TRIGGER))
                return false;
            return true;
        }

		void FilterTargets(std::list<WorldObject*>& targets)
		{
			if (Unit* caster = GetCaster())
			{
                if (caster->HasAura(SPELL_PALADIN_BREAKING_DAWN))
                {
                    targets.clear();
                    return;
                }
				targets.remove(caster);
				targets.sort(Trinity::HealthPctOrderPred());
				uint8 maxTargets = sSpellMgr->GetSpellInfo(SPELL_PALADIN_LIGHT_OF_DAWN)->GetEffect(EFFECT_0).BasePoints;
				if (targets.size() > maxTargets)
					Trinity::Containers::RandomResize(targets, maxTargets);
			}
		}

        void FilterTargetsLong(std::list<WorldObject*>& targets)
        {
            if (Unit* caster = GetCaster())
            {
                if (!caster->HasAura(SPELL_PALADIN_BREAKING_DAWN))
                {
                    targets.clear();
                    return;
                }
                targets.remove(caster);
                targets.sort(Trinity::HealthPctOrderPred());
                uint8 maxTargets = sSpellMgr->GetSpellInfo(SPELL_PALADIN_LIGHT_OF_DAWN)->GetEffect(EFFECT_0).BasePoints;
                if (targets.size() > maxTargets)
                    Trinity::Containers::RandomResize(targets, maxTargets);
            }
        }

		void FilterTargetsExtra(std::list<WorldObject*>& targets)
		{
			targets.clear();
		}

		void HandleHitTarget(SpellEffIndex effIndex)
		{
			Unit* caster = GetCaster();
			Unit* target = GetHitUnit();
			if (!caster || !target)
				return;

            if (!caster->HasAura(SPELL_PALADIN_BREAKING_DAWN))
                caster->CastSpell(target, SPELL_PALADIN_LIGHT_OF_DAWN_TRIGGER, true);
		}

        void HandleHitTargetLong(SpellEffIndex effIndex)
        {
            Unit* caster = GetCaster();
            Unit* target = GetHitUnit();
            if (!caster || !target)
                return;

            if (caster->HasAura(SPELL_PALADIN_BREAKING_DAWN))
                caster->CastSpell(target, SPELL_PALADIN_LIGHT_OF_DAWN_TRIGGER, true);
        }

        void HandleAfterCast()
        {
            if (Unit* caster = GetCaster())
            {
				if (caster->HasAura(SPELL_PALADIN_DIVINE_PURPOSE_HOLY_AURA_2))
					caster->RemoveAurasDueToSpell(SPELL_PALADIN_DIVINE_PURPOSE_HOLY_AURA_2);

				if (Aura* aura = caster->GetAura(SPELL_PALADIN_DIVINE_PURPOSE_HOLY))
					if (roll_chance_i(aura->GetEffect(EFFECT_0)->GetAmount()))
					{
						caster->CastSpell(caster, SPELL_PALADIN_DIVINE_PURPOSE_HOLY_AURA_2, true);
						caster->GetSpellHistory()->ResetCooldown(SPELL_PALADIN_LIGHT_OF_DAWN, true);
					}

				caster->RemoveAurasDueToSpell(SPELL_PALADIN_DARKEST_BEFORE_THE_DAWN_BUFF);

                if (caster->Variables.Exist("EmpoweredLightOfDawn"))
                    caster->Variables.Remove("EmpoweredLightOfDawn");
            }
        }

        void Register() override
        {
			OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_pal_light_of_dawn_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_CONE_ALLY);
			OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_pal_light_of_dawn_SpellScript::FilterTargetsLong, EFFECT_2, TARGET_UNIT_CONE_ALLY);
			OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_pal_light_of_dawn_SpellScript::FilterTargetsExtra, EFFECT_1, TARGET_UNIT_SRC_AREA_ALLY);
			OnEffectHitTarget += SpellEffectFn(spell_pal_light_of_dawn_SpellScript::HandleHitTarget, EFFECT_0, SPELL_EFFECT_DUMMY);
            OnEffectHitTarget += SpellEffectFn(spell_pal_light_of_dawn_SpellScript::HandleHitTargetLong, EFFECT_2, SPELL_EFFECT_DUMMY);
            AfterCast += SpellCastFn(spell_pal_light_of_dawn_SpellScript::HandleAfterCast);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_pal_light_of_dawn_SpellScript();
    }
};

// 203538 - Greater Blessing of Kings
//Last Update 8.0.1 Build 28153
class spell_pal_greater_blessing_of_kings : public AuraScript
{
    PrepareAuraScript(spell_pal_greater_blessing_of_kings);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_PALADIN_GREATER_BLESSING_OF_KINGS });
    }

    bool Load() override
    {
        return GetUnitOwner()->IsPlayer();
    }

    void HandleApply(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /* mode */)
    {
        Unit* caster = GetCaster();
        Unit* target = GetTarget();
        if (!caster || !target)
            return;

        if (Aura* aura = target->GetAura(SPELL_PALADIN_GREATER_BLESSING_OF_KINGS))
        {
            if (aura != target->GetAura(SPELL_PALADIN_GREATER_BLESSING_OF_KINGS, caster->GetGUID()))
                aura->Remove();
        }

        if (caster->HasAura(SPELL_PALADIN_HOLY_RITUAL) && caster->GetGUID() != target->GetGUID())
            caster->CastSpell(target, SPELL_PALADIN_HOLY_RITUAL_HEAL, true);
    }

    void OnTick(AuraEffect const* aurEff)
    {
        const_cast<AuraEffect*>(aurEff)->SetAmount(aurEff->GetDamage());
        if (AuraEffect const* aurEff1 = GetEffect(EFFECT_1))
            const_cast<AuraEffect*>(aurEff1)->SetDamage(aurEff->GetAmount());
        GetAura()->SetNeedClientUpdateForTargets();
    }

    void CalculateAmountEff1(AuraEffect const* /*aurEff*/, int32 & amount, bool & /*canBeRecalculated*/)
    {
        // Set absorbtion amount to unlimited
        amount = -1;
    }

    void CalculateAuraAmount(AuraEffect const* aurEff, int32& amount, bool& canBeRecalculated)
    {
        canBeRecalculated = true;
        if (Unit* caster = GetCaster())
        {
            if (Player* player = caster->ToPlayer())
            {                
                amount = player->SpellBaseDamageBonusDone(SPELL_SCHOOL_MASK_HOLY) * 0.675f;
                const_cast<AuraEffect*>(aurEff)->SetDamage(amount);
            }
        }
    }

    void Absorb(AuraEffect* aurEff, DamageInfo& dmgInfo, uint32& absorbAmount)
    {
        if (AuraEffect const* aurEff0 = GetEffect(EFFECT_0))
        {
            absorbAmount = std::min(uint32(aurEff0->GetAmount()), dmgInfo.GetDamage());
            const_cast<AuraEffect*>(aurEff0)->SetAmount(std::max(aurEff0->GetAmount() - int32(absorbAmount), 0));
            aurEff->SetDamage(aurEff0->GetAmount());
        }
    }

    void HandleRemove(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /* mode */)
    {
        Unit* caster = GetCaster();
        Unit* target = GetTarget();
        if (!caster || !target)
            return;

        if (caster->HasAura(SPELL_PALADIN_HOLY_RITUAL) && caster->GetGUID() != target->GetGUID())
            caster->CastSpell(target, SPELL_PALADIN_HOLY_RITUAL_HEAL, true);

        if (!caster->HasSpell(SPELL_PALADIN_HAMMER_OF_RECKONING))
            caster->RemoveAura(SPELL_PALADIN_RECKONING);
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (Unit* caster = GetCaster())
        {
            if (!caster->HasSpell(SPELL_PALADIN_HAMMER_OF_RECKONING) || !eventInfo.GetDamageInfo() ||
                (eventInfo.GetDamageInfo() && (eventInfo.GetDamageInfo()->GetDamageType() == HEAL || eventInfo.GetDamageInfo()->GetDamageType() == NODAMAGE)))
                return;

            caster->CastSpell(caster, SPELL_PALADIN_RECKONING, true);
            if (Aura* aura = caster->GetAura(SPELL_PALADIN_RECKONING))
                if (aura->GetStackAmount() == 50)
                    caster->CastSpell(caster, SPELL_PALADIN_RECKONING_ACTIVATION, true);
        }
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_pal_greater_blessing_of_kings::HandleApply, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY, AURA_EFFECT_HANDLE_REAL);
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_pal_greater_blessing_of_kings::OnTick, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
        DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_pal_greater_blessing_of_kings::CalculateAmountEff1, EFFECT_1, SPELL_AURA_SCHOOL_ABSORB);
        OnEffectAbsorb += AuraEffectAbsorbFn(spell_pal_greater_blessing_of_kings::Absorb, EFFECT_1);
        DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_pal_greater_blessing_of_kings::CalculateAuraAmount, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
        OnEffectRemove += AuraEffectRemoveFn(spell_pal_greater_blessing_of_kings::HandleRemove, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY, AURA_EFFECT_HANDLE_REAL);
        OnProc += AuraProcFn(spell_pal_greater_blessing_of_kings::HandleProc);
    }
};
    
// 203539 - Greater Blessing of Wisdom
class spell_pal_greater_blessing_of_wisdom : public AuraScript
{
    PrepareAuraScript(spell_pal_greater_blessing_of_wisdom);

    void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* caster = GetCaster())
        {
            if (Unit* target = GetTarget())
            {
                if (Aura* aura = target->GetAura(SPELL_PALADIN_GREATER_BLESSING_OF_WISDOM))
                {
                    if (aura != target->GetAura(SPELL_PALADIN_GREATER_BLESSING_OF_WISDOM, caster->GetGUID()))
                        aura->Remove();
                }
            }
        }
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_pal_greater_blessing_of_wisdom::OnApply, EFFECT_2, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};


// 185984 - Light of Dawn aoe heal
class spell_pal_light_of_dawn_trigger : public SpellScriptLoader
{
public:
    spell_pal_light_of_dawn_trigger() : SpellScriptLoader("spell_pal_light_of_dawn_trigger") {}

    class spell_pal_light_of_dawn_trigger_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_pal_light_of_dawn_trigger_SpellScript);

        void FilterTargets(std::list<WorldObject*>& targets)
        {
            Unit* caster = GetCaster();
            uint8 limit = 5;

            targets.remove_if([caster](WorldObject* target)
            {
                Position pos = target->GetPosition();
                return !(caster->IsWithinDist2d(&pos, 15.0f) && caster->isInFront(target, float(M_PI / 3))); //must be in a cone in 15 yards
            });

            Trinity::Containers::RandomResize(targets, limit); //max 5 targets.
        }

        void HandleOnHit(SpellEffIndex /*effIndex*/)
        {
            int32 dmg = GetHitHeal();

            dmg += GetCaster()->m_unitData->AttackPower * 1.8f;

            SetHitHeal(dmg);
        }

        void Register() override
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_pal_light_of_dawn_trigger_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ALLY);
            OnEffectHitTarget += SpellEffectFn(spell_pal_light_of_dawn_trigger_SpellScript::HandleOnHit, EFFECT_0, SPELL_EFFECT_HEAL);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_pal_light_of_dawn_trigger_SpellScript();
    }
};

// Blinding Light - 115750
class spell_pal_blinding_light : public SpellScriptLoader
{
public:
    spell_pal_blinding_light() : SpellScriptLoader("spell_pal_blinding_light") { }

    class spell_pal_blinding_light_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_pal_blinding_light_SpellScript);

        void HandleOnHit()
        {
            if (Player* player = GetCaster()->ToPlayer())
            {
                if (Unit* target = GetHitUnit())
                {
                    player->CastSpell(target, SPELL_PALADIN_BLINDING_LIGHT_CONFUSE, true);
                }
            }
        }

        void Register() override
        {
            OnHit += SpellHitFn(spell_pal_blinding_light_SpellScript::HandleOnHit);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_pal_blinding_light_SpellScript();
    }
};

// Holy Shield - 152261
//Last Update 8.0.1 Build 28153
class spell_pal_holy_shield : public AuraScript
{
    PrepareAuraScript(spell_pal_holy_shield);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetHitMask() & PROC_HIT_BLOCK)
            return true;

        return false;
    }

    void CalculateAmount(AuraEffect const* /*aurEff*/, int32& amount, bool& /*canBeRecalculated*/)
    {
        amount = -1;
    }

    void HandleEffectProc(AuraEffect* /*aurEff*/, ProcEventInfo& eventInfo)
    {
        // Proc part is only for melee blocks used
        if (eventInfo.GetSpellInfo())
            PreventDefaultAction();
    }

    void HandleAbsorb(AuraEffect* /*aurEff*/, DamageInfo& dmgInfo, uint32& absorbAmount)
    {
        if (!dmgInfo.GetSpellInfo() || dmgInfo.GetDamageType() == DOT)
            return;

        if (dmgInfo.GetSchoolMask() & SPELL_SCHOOL_MASK_MAGIC)
        {
            if (dmgInfo.GetAttacker()->isSpellBlocked(GetTarget(), dmgInfo.GetSpellInfo(), dmgInfo.GetAttackType()))
            {
                absorbAmount = CalculatePct(dmgInfo.GetDamage(), GetTarget()->GetBlockPercent(60));
                GetTarget()->CastSpell(dmgInfo.GetAttacker(), GetSpellInfo()->GetEffect(EFFECT_1).TriggerSpell, true);
            }
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_pal_holy_shield::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_pal_holy_shield::HandleEffectProc, EFFECT_1, SPELL_AURA_PROC_TRIGGER_SPELL);
        OnEffectAbsorb += AuraEffectAbsorbFn(spell_pal_holy_shield::HandleAbsorb, EFFECT_2);
        DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_pal_holy_shield::CalculateAmount, EFFECT_2, SPELL_AURA_SCHOOL_ABSORB);
    }
};

// Light's Hammer - 122773
class spell_pal_lights_hammer : public SpellScriptLoader
{
public:
    spell_pal_lights_hammer() : SpellScriptLoader("spell_pal_lights_hammer") { }

    class spell_pal_lights_hammer_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_pal_lights_hammer_SpellScript);

        void HandleAfterCast()
        {
            if (Unit* caster = GetCaster())
            {
                std::list<Creature*> tempList;
                std::list<Creature*> LightsHammerlist;

                caster->GetCreatureListWithEntryInGrid(LightsHammerlist, NPC_PALADIN_LIGHTS_HAMMER, 200.0f);

                tempList = LightsHammerlist;

                for (std::list<Creature*>::iterator i = tempList.begin(); i != tempList.end(); ++i)
                {
                    Unit* owner = (*i)->GetOwner();
                    if (owner != nullptr && owner->GetGUID() == caster->GetGUID() && (*i)->IsSummon())
                        continue;

                    LightsHammerlist.remove((*i));
                }

                for (std::list<Creature*>::iterator itr = LightsHammerlist.begin(); itr != LightsHammerlist.end(); ++itr)
                    (*itr)->CastSpell((*itr), SPELL_PALADIN_LIGHTS_HAMMER_TICK, true);
            }
        }

        void Register() override
        {
            AfterCast += SpellCastFn(spell_pal_lights_hammer_SpellScript::HandleAfterCast);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_pal_lights_hammer_SpellScript();
    }
};

// Light's Hammer (Periodic Dummy) - 114918
class spell_pal_lights_hammer_tick : public SpellScriptLoader
{
public:
    spell_pal_lights_hammer_tick() : SpellScriptLoader("spell_pal_lights_hammer_tick") { }

    class spell_pal_lights_hammer_tick_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_pal_lights_hammer_tick_AuraScript);

        void OnTick(AuraEffect const* /*aurEff*/)
        {
            if (Unit* caster = GetCaster())
            {
                if (caster->GetOwner())
                {
                    CastSpellTargetArg targets(caster->GetPosition());
                    caster->CastSpell(targets, SPELL_PALADIN_ARCING_LIGHT_HEAL, true);
                    caster->CastSpell(targets, SPELL_PALADIN_ARCING_LIGHT_DAMAGE, true);
                }
            }
        }

        void Register() override
        {
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_pal_lights_hammer_tick_AuraScript::OnTick, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_pal_lights_hammer_tick_AuraScript();
    }
};

// 31850 - ardent defender
class spell_pal_ardent_defender : public AuraScript
{
    PrepareAuraScript(spell_pal_ardent_defender);

public:
    spell_pal_ardent_defender()
    {
        absorbPct   = 0;
        healPct     = 0;
    }

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_PALADIN_ARDENT_DEFENDER });
    }

    bool Load() override
    {
        absorbPct   = GetSpellInfo()->GetEffect(EFFECT_0).CalcValue();
        healPct     = GetSpellInfo()->GetEffect(EFFECT_1).CalcValue();
        return GetUnitOwner()->IsPlayer();
    }

    void CalculateAmount(AuraEffect const* /*aurEff*/, int32& amount, bool& /*canBeRecalculated*/)
    {
        amount = -1;
    }

    void Absorb(AuraEffect* aurEff, DamageInfo& dmgInfo, uint32& absorbAmount)
    {
        absorbAmount = CalculatePct(dmgInfo.GetDamage(), absorbPct);

        Unit* target = GetTarget();
        if (dmgInfo.GetDamage() < target->GetHealth())
            return;

        int32 healAmount = int32(target->CountPctFromMaxHealth(healPct));
        target->CastCustomSpell(target, SPELL_PALADIN_ARDENT_DEFENDER_HEAL, &healAmount, NULL, NULL, true, NULL, aurEff);
        aurEff->GetBase()->Remove();
    }

    void Register() override
    {
        DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_pal_ardent_defender::CalculateAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
        OnEffectAbsorb += AuraEffectAbsorbFn(spell_pal_ardent_defender::Absorb, EFFECT_0);
    }

private:
    uint32 absorbPct;
    uint32 healPct;
};

// 231895 - Crusader
class spell_pal_crusade : public AuraScript
{
    PrepareAuraScript(spell_pal_crusade);

    void HandleApply(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /* mode */)
    {
        if (Unit* caster = GetCaster())
            if (Aura* aura = caster->GetAura(SPELL_PALADIN_AVENGER_MIGHT_POWER))
            {
                caster->CastCustomSpell(SPELL_PALADIN_AVENGER_MIGHT_BUFF, SPELLVALUE_BASE_POINT0, aura->GetEffect(EFFECT_0)->GetAmount(), caster, true);
                if (Aura* aze = caster->GetAura(SPELL_PALADIN_AVENGER_MIGHT_BUFF))
                    aze->SetDuration(GetAura()->GetMaxDuration());
            }
    }

    void HandleRemove(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /* mode */)
    {
        if (Unit* caster = GetCaster())
            caster->RemoveAura(SPELL_PALADIN_AVENGER_MIGHT_BUFF);
    }

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }

    void CalculateAmount(AuraEffect const* /*aurEff*/, int32& amount, bool& /*canBeRecalculated*/)
    {
        amount /= 10;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_pal_crusade::CheckProc);
        DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_pal_crusade::CalculateAmount, EFFECT_0, SPELL_AURA_ADD_PCT_MODIFIER);
        DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_pal_crusade::CalculateAmount, EFFECT_1, SPELL_AURA_ADD_PCT_MODIFIER);
        DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_pal_crusade::CalculateAmount, EFFECT_2, SPELL_AURA_MELEE_SLOW);
        DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_pal_crusade::CalculateAmount, EFFECT_4, SPELL_AURA_MOD_AUTOATTACK_DAMAGE);
        OnEffectApply += AuraEffectApplyFn(spell_pal_crusade::HandleApply, EFFECT_0, SPELL_AURA_ADD_PCT_MODIFIER, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
        OnEffectRemove += AuraEffectRemoveFn(spell_pal_crusade::HandleRemove, EFFECT_0, SPELL_AURA_ADD_PCT_MODIFIER, AURA_EFFECT_HANDLE_REAL);
    }
};

// Light's Hammer
// NPC Id - 59738
class npc_pal_lights_hammer : public ScriptedAI
{
public:

    npc_pal_lights_hammer(Creature* creature) : ScriptedAI(creature) {}

    void Reset() override
    {
        me->CastSpell(me, SPELL_PALADIN_LIGHT_HAMMER_COSMETIC, true);
        me->SetUnitFlag(UNIT_FLAG_NON_ATTACKABLE);
        me->SetUnitFlag(UNIT_FLAG_UNINTERACTIBLE);
        me->SetUnitFlag(UNIT_FLAG_REMOVE_CLIENT_CONTROL);
    }
};

// Consecration - 26573 (retribution)
// Consecration - 205228 (protection)
class spell_pal_consecration : public SpellScript
{
    PrepareSpellScript(spell_pal_consecration);

    void HandlePrepare()
    {
        if (Unit* caster = GetCaster())
            if (AreaTrigger* at = caster->GetAreaTrigger(GetSpellInfo()->Id))
                if (at)
                    at->Remove();
    }

    void Register() override
    {
        OnPrepare += SpellOnPrepareFn(spell_pal_consecration::HandlePrepare);
    }
};

// Consecration - 26573 (retribution)
// Consecration - 205228 (protection)
class aura_pal_consecration : public AuraScript
{
    PrepareAuraScript(aura_pal_consecration);

    void OnTick(AuraEffect const* /*auraEff*/)
    {
        if (Unit* caster = GetCaster())
        {
            AreaTrigger* at = caster->GetAreaTrigger(GetSpellInfo()->Id);
            if (at)
                caster->CastSpell(at->GetPosition(), SPELL_PALADIN_CONSECRATION_DAMAGE, true);
        }
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(aura_pal_consecration::OnTick, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

// Aura of Sacrifice - 183416
// AreaTriggerID - 100102 (custom)
struct at_pal_aura_of_sacrifice : AreaTriggerAI
{
    at_pal_aura_of_sacrifice(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger)
    {
        at->SetPeriodicProcTimer(1000);
    }

    void OnUnitEnter(Unit* unit) override
    {
		if (Unit* caster = at->GetCaster())
		{
			if (caster->GetGUID() == unit->GetGUID())
				return;

			if (unit->IsPlayer() && caster->IsPlayer())
				if (caster->IsValidAssistTarget(unit) && caster->ToPlayer()->IsInSameRaidWith(unit->ToPlayer()))
					caster->CastSpell(unit, SPELL_PALADIN_AURA_OF_SACRIFICE_ALLY, true);
		}
    }

	void OnPeriodicProc() override
	{
		if (Unit* caster = at->GetCaster())
		{
			Player* player = caster->ToPlayer();
			GuidUnorderedSet list = at->GetInsideUnits();
			if (!list.empty())
			{
				for (ObjectGuid guid : list)
				{
					Unit* unit = ObjectAccessor::GetUnit(*player, guid);
					if (!unit->ToPlayer())
						continue;

					if (caster->GetGUID() == unit->GetGUID())
						continue;

					if (!unit->HasAura(SPELL_PALADIN_AURA_OF_SACRIFICE_ALLY) && player->IsInSameRaidWith(unit->ToPlayer()) && player->IsValidAssistTarget(unit))
						caster->AddAura(SPELL_PALADIN_AURA_OF_SACRIFICE_ALLY, unit);
					else if (unit->HasAura(SPELL_PALADIN_AURA_OF_SACRIFICE_ALLY, player->GetGUID()) && !player->IsInSameRaidWith(unit->ToPlayer()))
						unit->RemoveAura(SPELL_PALADIN_AURA_OF_SACRIFICE_ALLY, player->GetGUID());
				}
			}
		}
	}

    void OnUnitExit(Unit* unit) override
    {
		if (Unit* caster = at->GetCaster())
		{
			if (unit->HasAura(SPELL_PALADIN_AURA_OF_SACRIFICE_ALLY, caster->GetGUID()))
				unit->RemoveAura(SPELL_PALADIN_AURA_OF_SACRIFICE_ALLY, caster->GetGUID());
		}
    }
};

// 210372 - Aura of Sacrifice (Ally)
class spell_pal_aura_of_sacrifice_ally : public AuraScript
{
    PrepareAuraScript(spell_pal_aura_of_sacrifice_ally);

    bool Load() override
    {
        return ValidateSpellInfo({ SPELL_PALADIN_AURA_OF_SACRIFICE });
    }

    void CalcAmount(AuraEffect const* /*aurEff*/, int32& amount, bool& /*canBeRecalculated*/)
    {
        amount = -1;
    }

    void OnAbsorb(AuraEffect* /*aurEff*/, DamageInfo& dmgInfo, uint32& absorbAmount)
    {
		Unit* caster = GetCaster();
		Unit* owner = GetUnitOwner();
		if (!caster || !owner)
			return;

		SpellInfo const* auraOfSacrificeInfo = sSpellMgr->GetSpellInfo(SPELL_PALADIN_AURA_OF_SACRIFICE);

		if (!caster->IsValidAssistTarget(owner) || caster->GetHealthPct() < auraOfSacrificeInfo->GetEffect(EFFECT_2).BasePoints)
		{
			absorbAmount = 0;
			return;
		}

		uint8 percent = caster->HasAura(SPELL_PALADIN_AURA_MASTERY) ? auraOfSacrificeInfo->GetEffect(EFFECT_3).BasePoints : auraOfSacrificeInfo->GetEffect(EFFECT_0).BasePoints;
		absorbAmount = CalculatePct(dmgInfo.GetDamage(), percent);

		// Deal damages to the paladin
		float reduction = caster->HasAura(SPELL_PALADIN_AURA_MASTERY) ? 0.75f : 0.5f;
		owner->CastCustomSpell(SPELL_PALADIN_AURA_OF_SACRIFICE_DAMAGE, SPELLVALUE_BASE_POINT0, absorbAmount * reduction, caster, true);
    }

    void Register() override
    {
        DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_pal_aura_of_sacrifice_ally::CalcAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
        OnEffectAbsorb += AuraEffectAbsorbFn(spell_pal_aura_of_sacrifice_ally::OnAbsorb, EFFECT_0);
    }
};

// Last Update 8.0.1 Build 28153
// 267344 - Art of War
class spell_pal_art_of_war : public AuraScript
{
    PrepareAuraScript(spell_pal_art_of_war);

    enum eArtOfWar
    {
        AshestoAshes2pc = 363677,
        AshesToAshes4pc = 364370,
    };

    void OnCalcProc(ProcEventInfo& eventInfo, float& chance)
    {
        //Blade of Wrath Chance of Art of War x 2
        if(Unit* caster = GetCaster())
            if (Unit* target = eventInfo.GetActionTarget())
                if (Aura* bladeOfWrath = caster->GetAura(SPELL_BLADE_OF_WRATH))
                    AddPct(chance, bladeOfWrath->GetSpellInfo()->GetEffect(EFFECT_0).BasePoints);
    }

    void OnProc(AuraEffect* /*aurEff*/, ProcEventInfo& /*eventInfo*/)
    {
		if (Unit* caster = GetCaster())
		{
            if(!caster->HasAura(SPELL_BLADE_OF_WRATH))
                caster->CastSpell(caster, SPELL_PALADIN_ART_OF_WAR_PROC, true);
            else
                caster->CastSpell(caster, SPELL_BLADE_OF_WRATH_PROC, true);

            if (!caster->HasAura(AshesToAshes4pc))
			    caster->GetSpellHistory()->ResetCooldown(SPELL_PALADIN_BLADE_OF_JUSTICE, true);
            else
            {
                if (roll_chance_i(50))
                {
                    caster->GetSpellHistory()->ResetCooldown(SPELL_PALADIN_WAKE_OF_ASHES, true);
                }
                else
                    caster->GetSpellHistory()->ResetCooldown(SPELL_PALADIN_BLADE_OF_JUSTICE, true);
            }

            if (caster->HasAura(AshestoAshes2pc))
            {
                if (Aura* seraphimAura = caster->GetAura(SPELL_PALADIN_SERAPHIM))
                {
                    auto dur = seraphimAura->GetDuration();
                    dur += 3000;
                    if (dur >= seraphimAura->GetMaxDuration())
                        dur = seraphimAura->GetMaxDuration();
                    seraphimAura->SetDuration(dur);
                }
                else
                {
                    if (auto seraphim = caster->AddAura(SPELL_PALADIN_SERAPHIM, caster))
                    {
                        seraphim->SetDuration(3000);
                    }
                }
            }
		}
    }

    void Register() override
    {
        OnCalcProcChance += AuraCalcProcChanceFn(spell_pal_art_of_war::OnCalcProc);
        OnEffectProc += AuraEffectProcFn(spell_pal_art_of_war::OnProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

// 85804 - Selfless Healer
class spell_pal_proc_from_holy_power_consumption : public AuraScript
{
    PrepareAuraScript(spell_pal_proc_from_holy_power_consumption);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetSpellInfo() && eventInfo.GetDamageInfo())
            if (Spell const* procSpell = eventInfo.GetProcSpell())
                if (SpellPowerCost const* powerCost = procSpell->GetPowerCost(POWER_HOLY_POWER))
                if (powerCost->Amount > 0)
                    return true;

        return false;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_pal_proc_from_holy_power_consumption::CheckProc);
    }
};

// 84963  - Inquisition
class spell_pal_inquisition : public SpellScript
{
    PrepareSpellScript(spell_pal_inquisition);

    uint8 powerTaken = 0;

    void HandleTakePower(SpellPowerCost& powerCost)
    {
		if (powerCost.Power == POWER_HOLY_POWER)
			powerTaken = powerCost.Amount;
    }

    void HandleAfterHit()
    {
		if (Unit* caster = GetCaster())
			if (Aura* aura = caster->GetAura(GetSpellInfo()->Id))
				aura->SetDuration(aura->GetDuration() * powerTaken);
    }

    void Register() override
    {
        OnTakePower += SpellOnTakePowerFn(spell_pal_inquisition::HandleTakePower);
        AfterHit += SpellHitFn(spell_pal_inquisition::HandleAfterHit);
    }
};

// 267610 - Righteous Verdict
class spell_pal_righteous_verdict : public AuraScript
{
    PrepareAuraScript(spell_pal_righteous_verdict);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_pal_righteous_verdict::CheckProc);
    }
};

// 205290 - Wake of Ashes
class spell_pal_wake_of_ashes : public SpellScript
{
    PrepareSpellScript(spell_pal_wake_of_ashes);

    void HandleDamages(SpellEffIndex /*effIndex*/)
    {
        if (Creature* target = GetHitCreature())
            if (CreatureTemplate const* creTemplate = target->GetCreatureTemplate())
                if (creTemplate->type == CREATURE_TYPE_DEMON || creTemplate->type == CREATURE_TYPE_UNDEAD)
                    GetCaster()->CastSpell(target, SPELL_PALADIN_WAKE_OF_ASHES_STUN, true);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_pal_wake_of_ashes::HandleDamages, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

// 248033 - Awakening
class spell_pal_awakening : public AuraScript
{
    PrepareAuraScript(spell_pal_awakening);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == SPELL_PALADIN_LIGHT_OF_DAWN)
            return roll_chance_i(GetEffectInfo(EFFECT_0).BasePoints);

        return false;
    }

    void OnProc(AuraEffect* /*aurEff*/, ProcEventInfo& /*eventInfo*/)
    {
        if (Unit* caster = GetCaster())
        {
            caster->CastSpell(caster, SPELL_PALADIN_AVENGING_WRATH, true);
            if (Aura* aura = caster->GetAura(SPELL_PALADIN_AVENGING_WRATH))
                aura->ModDuration(GetEffectInfo(EFFECT_1).BasePoints * -IN_MILLISECONDS);
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_pal_awakening::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_pal_awakening::OnProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

// 210320 - Devotion Aura
//Last Update 8.0.1 Build 28153
class aura_pal_devotion_aura : public AuraScript
{
	PrepareAuraScript(aura_pal_devotion_aura);

	void CalcAmount(AuraEffect const* /*aurEff*/, int32& amount, bool& canBeRecalculated)
	{
		canBeRecalculated = true;
		if (Unit* caster = GetCaster())
            if(SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(SPELL_PALADIN_DEVOTION_AURA_TALENT))
                amount = (caster->HasAura(SPELL_PALADIN_AURA_MASTERY)) ? GetSpellInfo()->GetEffect(EFFECT_0).BasePoints : spellInfo->GetEffect(EFFECT_0).BasePoints / (caster->Variables.GetValue("DevotionTargetCounter", 0) == 0 ? 1 : caster->Variables.GetValue("DevotionTargetCounter", 1));
	}

	void Register() override
	{
		DoEffectCalcAmount += AuraEffectCalcAmountFn(aura_pal_devotion_aura::CalcAmount, EFFECT_0, SPELL_AURA_MOD_DAMAGE_PERCENT_TAKEN);
	}
};

// 183425 - Aura of Devotion
// AreaTriggerID - 6770 (custom)
//Last Update 8.0.1 Build 28153
struct at_pal_aura_of_devotion : AreaTriggerAI
{
	at_pal_aura_of_devotion(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger)
	{
		// How often should the action be executed
		areatrigger->SetPeriodicProcTimer(1000);
	}

	void OnUnitEnter(Unit* unit) override
	{
		if (!unit->ToPlayer())
			return;

        if (Unit* caster = at->GetCaster())
            if (Player* player = unit->ToPlayer())
                if (caster->GetGUID() == unit->GetGUID() || (player->IsInSameRaidWith(caster->ToPlayer()) && player->IsValidAssistTarget(unit)))
                    caster->CastSpell(player, SPELL_PALADIN_DEVOTION_AURA, true);
	}

	void OnPeriodicProc() override
	{
		if (Unit* caster = at->GetCaster())
		{
            if (Player* player = caster->ToPlayer())
            {
                GuidUnorderedSet list = at->GetInsideUnits();
                if (!list.empty())
                {
                    caster->Variables.Set("DevotionTargetCounter", 0);
                    for (ObjectGuid guid : list)
                    {
                        Unit* unit = ObjectAccessor::GetUnit(*player, guid);
                        if (!unit->ToPlayer())
                            continue;

                        if (unit->HasAura(SPELL_PALADIN_DEVOTION_AURA, player->GetGUID()) && player->IsInSameRaidWith(unit->ToPlayer()))
                            caster->Variables.Set("DevotionTargetCounter", caster->Variables.GetValue("DevotionTargetCounter", 0) + 1);
                        else if (!unit->HasAura(SPELL_PALADIN_DEVOTION_AURA) && (player->GetGUID() == unit->GetGUID() || player->IsInSameRaidWith(unit->ToPlayer()) && player->IsValidAssistTarget(unit)))
                            caster->AddAura(SPELL_PALADIN_DEVOTION_AURA, unit);
                        else if (unit->HasAura(SPELL_PALADIN_DEVOTION_AURA, player->GetGUID()) && !player->IsInSameRaidWith(unit->ToPlayer()))
                            unit->RemoveAura(SPELL_PALADIN_DEVOTION_AURA, player->GetGUID());
                    }

                    for (ObjectGuid guid : list)
                    {
                        Unit* unit = ObjectAccessor::GetUnit(*player, guid);
                        if (!unit->ToPlayer())
                            continue;

                        if (unit->HasAura(SPELL_PALADIN_DEVOTION_AURA, player->GetGUID()) && (player->GetGUID() == unit->GetGUID() || player->IsInSameRaidWith(unit->ToPlayer()) && player->IsValidAssistTarget(unit)))
                            unit->GetAura(SPELL_PALADIN_DEVOTION_AURA, player->GetGUID())->RecalculateAmountOfEffects(true, true);
                    }
                }
            }			
		}
	}

	void OnUnitExit(Unit* unit) override
	{
        if (Unit* caster = at->GetCaster())
            if (unit->HasAura(SPELL_PALADIN_DEVOTION_AURA, caster->GetGUID()))
                unit->RemoveAura(SPELL_PALADIN_DEVOTION_AURA, caster->GetGUID());
	}
};

// 26573 - Consecration
// AreaTriggerID - 4488
struct at_pal_consegration: AreaTriggerAI
{
	at_pal_consegration(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger) { }

	void OnUnitEnter(Unit* unit) override
	{
		if (Unit* caster = at->GetCaster())
		{
			if (unit->GetGUID() == caster->GetGUID() && caster->ToPlayer() && caster->ToPlayer()->GetSpecializationId() == TALENT_SPEC_PALADIN_PROTECTION)
				caster->CastSpell(caster, SPELL_PALADIN_CONSEGRATION_AURA, true);

            if (caster->HasAura(SPELL_PALADIN_HALLOWED_GROUND) && caster->IsValidAssistTarget(unit))
                caster->CastSpell(unit, SPELL_PALADIN_HALLOWED_GROUND_INMUNITY, true);
		}
	}

	void OnUnitExit(Unit* unit) override
	{
		if (Unit* caster = at->GetCaster())
		{
			if (unit->GetGUID() == caster->GetGUID())
				caster->RemoveAura(SPELL_PALADIN_CONSEGRATION_AURA);

            if (caster->HasAura(SPELL_PALADIN_HALLOWED_GROUND) && caster->IsValidAssistTarget(unit) && unit->HasAura(SPELL_PALADIN_HALLOWED_GROUND_INMUNITY, caster->GetGUID()))
                unit->RemoveAura(SPELL_PALADIN_HALLOWED_GROUND_INMUNITY, caster->GetGUID());
		}
	}
};

// 199542 - Steed of Glory
// AreaTriggerID - 5546
struct at_pal_steed_of_glory : AreaTriggerAI
{
    at_pal_steed_of_glory(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger) { }

    void OnUnitEnter(Unit* unit) override
    {
        if (Unit* caster = at->GetCaster())
            if (caster->IsValidAttackTarget(unit))
                caster->CastSpell(unit, SPELL_PALADIN_STEED_OF_GLORY_KNOCKBACK, true);
    }
};

// 203791 - Last Defender
struct at_pal_last_defender_dps : AreaTriggerAI
{
    at_pal_last_defender_dps(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger) { }

    void OnUnitEnter(Unit* unit) override
    {
        if (Unit* caster = at->GetCaster())
            if (caster->IsValidAttackTarget(unit))
                if (Aura* aura = caster->GetAura(SPELL_PALADIN_LAST_DEFENDER))
                {
                    uint8 base = sSpellMgr->GetSpellInfo(SPELL_PALADIN_LAST_DEFENDER)->GetEffect(EFFECT_1).BasePoints;
                    uint32 amount = aura->GetEffect(4)->GetAmount();
                    for (uint8 i = 4; i < 7; i++)
                        aura->GetEffect(i)->SetAmount(amount + base);
                }
    }

    void OnUnitExit(Unit* unit) override
    {
        if (Unit* caster = at->GetCaster())
            if (!caster->IsValidAssistTarget(unit))
                if (Aura* aura = caster->GetAura(SPELL_PALADIN_LAST_DEFENDER))
                {
                    uint8 base = sSpellMgr->GetSpellInfo(SPELL_PALADIN_LAST_DEFENDER)->GetEffect(EFFECT_1).BasePoints;
                    uint32 amount = aura->GetEffect(4)->GetAmount();
                    if (amount > 0)
                        for (uint8 i = 4; i < 7; i++)
                            aura->GetEffect(i)->SetAmount(amount - base);
                }
    }
};

// 204927 - Seraphim's Blessing
// AreaTriggerID - 6801
struct at_pal_seraphims_blessing : AreaTriggerAI
{
    at_pal_seraphims_blessing(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger) { }

    void OnUnitEnter(Unit* unit) override
    {
        if (Unit* caster = at->GetCaster())
            if (unit && (caster->IsValidAssistTarget(unit) || unit->GetGUID() == caster->GetGUID()))
                caster->CastSpell(unit, SPELL_PALADIN_SERAPHIMS_BLESSING_TRIGGER, true);
    }

    void OnUnitExit(Unit* unit) override
    {
        if (Unit* caster = at->GetCaster())
            if (unit && unit->HasAura(SPELL_PALADIN_SERAPHIMS_BLESSING_TRIGGER, caster->GetGUID()))
                unit->RemoveAura(SPELL_PALADIN_SERAPHIMS_BLESSING_TRIGGER, caster->GetGUID());
    }
};

// 199424 - Pure of Heart
// AreaTriggerID - 6804
struct at_pal_pure_of_heart : AreaTriggerAI
{
    at_pal_pure_of_heart(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger) { }

    void OnUnitEnter(Unit* unit) override
    {
        if (Unit* caster = at->GetCaster())
            if (unit && (caster->IsValidAssistTarget(unit) || unit->GetGUID() == caster->GetGUID()))
                caster->CastSpell(unit, SPELL_PALADIN_PURE_OF_HEART_TRIGGER, true);
    }

    void OnUnitExit(Unit* unit) override
    {
        if (Unit* caster = at->GetCaster())
            if (unit && unit->HasAura(SPELL_PALADIN_PURE_OF_HEART_TRIGGER, caster->GetGUID()))
                unit->RemoveAura(SPELL_PALADIN_PURE_OF_HEART_TRIGGER, caster->GetGUID());
    }
};

// 105421 - Blinding Light Aura
class aura_pal_blinding_light : public AuraScript
{
	PrepareAuraScript(aura_pal_blinding_light);

	bool CheckProc(ProcEventInfo& eventInfo)
	{
		if (eventInfo.GetDamageInfo() && eventInfo.GetDamageInfo()->GetSchoolMask() != SpellSchoolMask::SPELL_SCHOOL_MASK_HOLY)
			return true;

		return false;
	}

	void Register() override
	{
		DoCheckProc += AuraCheckProcFn(aura_pal_blinding_light::CheckProc);
	}
};

// 183435 - Retribution
class aura_pal_retribution : public AuraScript
{
	PrepareAuraScript(aura_pal_retribution);

	void HandleProc(ProcEventInfo& eventInfo)
	{
		if (Unit* caster = GetCaster())
			caster->AddAura(SPELL_PALADIN_RETRIBUTION);
	}

	void Register() override
	{
		OnProc += AuraProcFn(aura_pal_retribution::HandleProc);
	}
};

// 203797 - Retribution Aura
class aura_pal_retribution_aura : public AuraScript
{
	PrepareAuraScript(aura_pal_retribution_aura);

	void HandleProc(ProcEventInfo& eventInfo)
	{
		if (eventInfo.GetDamageInfo())
		{
			Unit* caster = GetCaster();
			Unit* target = eventInfo.GetDamageInfo()->GetAttacker();
			if (!caster || !target)
				return;

			caster->CastSpell(target, SPELL_PALADIN_RETRIBUTION_AURA_DAMAGE, true);
		}
	}

	void Register() override
	{
		OnProc += AuraProcFn(aura_pal_retribution_aura::HandleProc);
	}
};

// 255937 - Wake of the Ashes
class spell_pal_wake_of_the_ashes : public SpellScript
{
	PrepareSpellScript(spell_pal_wake_of_the_ashes);

	void HandleHit()
	{
		Unit* caster = GetCaster();
		Unit* target = GetHitUnit();
		if (!caster || !target)
			return;

		if (target->GetCreatureType() == CREATURE_TYPE_DEMON || target->GetCreatureType() == CREATURE_TYPE_UNDEAD)
			caster->CastSpell(target, SPELL_PALADIN_WAKE_OF_ASHES_STUN, true);
	}

	void Register() override
	{
		OnHit += SpellHitFn(spell_pal_wake_of_the_ashes::HandleHit);
	}
};

// 234299 - Fist of Fury Retri
class aura_pal_fist_of_fury : public AuraScript
{
	PrepareAuraScript(aura_pal_fist_of_fury);

	bool CheckProc(ProcEventInfo& eventInfo)
	{
        if (Unit* caster = GetCaster())
            if (Spell const* procSpell = eventInfo.GetProcSpell())
            {
                if (procSpell->GetCaster()->GetGUID() == caster->GetGUID())
                    if (SpellPowerCost const* powerCost = procSpell->GetPowerCost(POWER_HOLY_POWER))
                        if (powerCost->Amount > 0)
                        {
                            holyPower = powerCost->Amount;
                            return true;
                        }
            }

        return false;
	}

	void HandleProc(ProcEventInfo& eventInfo)
	{
		if (Unit* caster = GetCaster())
            if (caster->GetSpellHistory()->HasCooldown(SPELL_PALADIN_HAMMER_OF_JUSTICE))
            {
                uint32 seconds = sSpellMgr->GetSpellInfo(SPELL_PALADIN_FIST_OF_JUSTICE_RETRI)->GetEffect(EFFECT_0).BasePoints / 10;
                caster->GetSpellHistory()->ModifyCooldown(SPELL_PALADIN_HAMMER_OF_JUSTICE, holyPower * seconds * -1s);
            }
	}

	void Register() override
	{
		DoCheckProc += AuraCheckProcFn(aura_pal_fist_of_fury::CheckProc);
		OnProc += AuraProcFn(aura_pal_fist_of_fury::HandleProc);
	}

private:
    int32 holyPower;
};

// 196941 - Judgment of light
class aura_pal_judgment_of_light : public AuraScript
{
	PrepareAuraScript(aura_pal_judgment_of_light);

    bool HandleCheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetDamageInfo())
            return false;

        Unit* attacker = eventInfo.GetDamageInfo()->GetAttacker();
        if (!attacker)
            return false;

        if (attacker->IsFullHealth())
            return false;

        if (!CheckAndUpdateCooldownFor(attacker->GetGUID().GetCounter()))
            return false;

        return true;
    }

    void OnProc(AuraEffect* aurEff, ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();

        Unit* caster = GetCaster();
        Unit* attacker = eventInfo.GetDamageInfo()->GetAttacker();

        if (attacker == nullptr || caster == nullptr)
            return;

        caster->CastSpell(attacker, aurEff->GetTriggerSpell(), true);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_pal_judgment_of_light::HandleCheckProc);
        OnEffectProc += AuraEffectProcFn(aura_pal_judgment_of_light::OnProc, EFFECT_0, SPELL_AURA_PROC_TRIGGER_SPELL);
    }

private:

    bool CheckAndUpdateCooldownFor(uint64 guid)
    {
        auto itr = m_CooldownsMap.find(guid);
        if (itr != m_CooldownsMap.end() && itr->second > time(nullptr))
            return false;

        m_CooldownsMap[guid] = time(nullptr) + 1;

        return true;
    }

private:

    std::map<uint64 /*guid*/, time_t /*time*/> m_CooldownsMap;
};

// 210291 - Aura of Mercy (Heal)
class spell_pala_aura_of_mercy : public SpellScript
{
	PrepareSpellScript(spell_pala_aura_of_mercy);

	void HandleOnObjectAreaTargetSelect(std::list<WorldObject*>& targets)
	{
		if (Unit* caster = GetCaster())
		{
			targets.remove_if([caster](WorldObject* unit)
			{
				if (!unit->ToUnit())
					return true;

				if (!unit->ToPlayer())
					return true;

				if (caster->GetGUID() == unit->GetGUID())
					return true;

				if (!caster->IsValidAssistTarget(unit->ToUnit()))
					return true;

				if (!caster->ToPlayer()->IsInSameRaidWith(unit->ToPlayer()))
					return true;

				return false;
			});

			if (!caster->HasAura(SPELL_PALADIN_AURA_MASTERY))
			{
				uint8 count = sSpellMgr->GetSpellInfo(SPELL_PALADIN_AURA_OF_MERCY)->GetEffect(EFFECT_1).BasePoints;
				targets.sort(Trinity::HealthPctOrderPred());
				if (targets.size() > count)
					Trinity::Containers::RandomResize(targets, count);
			}
		}
	}

	void Register() override
	{
		OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_pala_aura_of_mercy::HandleOnObjectAreaTargetSelect, EFFECT_0, TARGET_UNIT_DEST_AREA_ALLY);
	}
};

// 269569 - Zeal
class aura_pal_zeal : public AuraScript
{
	PrepareAuraScript(aura_pal_zeal);

	bool CheckProc(ProcEventInfo& eventInfo)
	{
		if (eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == SPELL_PALADIN_JUDGMENT)
			return true;

		return false;
	}

	void HandleProc(ProcEventInfo& eventInfo)
	{
		PreventDefaultAction();
		if (Unit* caster = GetCaster())
			for (uint8 i = 0; i < 3; i++)
				caster->CastSpell(caster, SPELL_PALADIN_ZEAL_BUFF, true);
	}

	void Register() override
	{
		DoCheckProc += AuraCheckProcFn(aura_pal_zeal::CheckProc);
		OnProc += AuraProcFn(aura_pal_zeal::HandleProc);
	}
};

// 269571 - Zeal Aura
class aura_pal_zeal_aura : public AuraScript
{
	PrepareAuraScript(aura_pal_zeal_aura);

	bool CheckProc(ProcEventInfo& eventInfo)
	{
		Unit* caster = GetCaster();
		Unit* target = eventInfo.GetActionTarget();
		if (!caster || !target)
			return false;

		if (eventInfo.GetDamageInfo() && (eventInfo.GetDamageInfo()->GetAttackType() == BASE_ATTACK || eventInfo.GetDamageInfo()->GetAttackType() == OFF_ATTACK))
		{
			if (Aura* aura = caster->GetAura(SPELL_PALADIN_ZEAL_BUFF))
				aura->ModStackAmount(-1);
			caster->CastSpell(eventInfo.GetActionTarget(), SPELL_PALADIN_ZEAL_DAMAGE, true);
		}

		return false;
	}

	void Register() override
	{
		DoCheckProc += AuraCheckProcFn(aura_pal_zeal_aura::CheckProc);
	}
};

// 216331 - Avenging Crusader
class aura_pal_avengin_crusader : public AuraScript
{
    PrepareAuraScript(aura_pal_avengin_crusader);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetSpellInfo() && (eventInfo.GetSpellInfo()->Id == SPELL_PALADIN_JUDGMENT_HOLY || eventInfo.GetSpellInfo()->Id == SPELL_PALADIN_CRUSADER_STRIKE))
            return true;

        return false;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetDamageInfo())
            if (Unit* caster = GetCaster())
            {
                int32 damage = eventInfo.GetDamageInfo()->GetDamage();
                uint8 percent = sSpellMgr->GetSpellInfo(SPELL_PALADIN_AVENGING_CRUSADER)->GetEffect(EFFECT_0).BasePoints;
                caster->CastCustomSpell(SPELL_PALADIN_AVENGING_CRUSADER_HEAL, SPELLVALUE_BASE_POINT0, CalculatePct(damage, percent), caster, true);
            }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_pal_avengin_crusader::CheckProc);
        OnProc += AuraProcFn(aura_pal_avengin_crusader::HandleProc);
    }
};

// 281465 - Avenging Crusader Heal
class spell_pal_avengin_crusader_heal : public SpellScript
{
    PrepareSpellScript(spell_pal_avengin_crusader_heal);

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        if (Unit* caster = GetCaster())
        {
            targets.remove_if([caster](WorldObject* unit)
            {
                if (!unit->ToUnit())
                    return true;

                if (!unit->ToUnit()->ToPlayer())
                    return true;

                if (!caster->IsValidAssistTarget(unit->ToUnit()))
                    return true;

                return false;
            });

            targets.sort(Trinity::HealthPctOrderPred());
            if (targets.size() > sSpellMgr->GetSpellInfo(SPELL_PALADIN_AVENGING_CRUSADER)->GetEffect(EFFECT_1).BasePoints)
                targets.resize(sSpellMgr->GetSpellInfo(SPELL_PALADIN_AVENGING_CRUSADER)->GetEffect(EFFECT_1).BasePoints);
        }
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_pal_avengin_crusader_heal::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ALLY);
    }
};

// 203539 - Greater Blessing of Wisdom
class aura_pal_greater_blessing_of_wisdom : public AuraScript
{
	PrepareAuraScript(aura_pal_greater_blessing_of_wisdom);

	void HandleApply(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /* mode */)
	{
		Unit* caster = GetCaster();
		Unit* target = GetTarget();
		if (!caster || !target)
			return;

		if (caster->HasAura(SPELL_PALADIN_HOLY_RITUAL) && caster->GetGUID() != target->GetGUID())
			caster->CastSpell(target, SPELL_PALADIN_HOLY_RITUAL_HEAL, true);
	}

	void HandleRemove(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /* mode */)
	{
		Unit* caster = GetCaster();
		Unit* target = GetTarget();
		if (!caster || !target)
			return;

		if (caster->HasAura(SPELL_PALADIN_HOLY_RITUAL) && caster->GetGUID() != target->GetGUID())
			caster->CastSpell(target, SPELL_PALADIN_HOLY_RITUAL_HEAL, true);

		if (!caster->HasSpell(SPELL_PALADIN_HAMMER_OF_RECKONING))
			caster->RemoveAura(SPELL_PALADIN_RECKONING);
	}

	void HandleProc(ProcEventInfo& eventInfo)
	{
		if (Unit* caster = GetCaster())
		{
			if (!caster->HasSpell(SPELL_PALADIN_HAMMER_OF_RECKONING) || !eventInfo.GetDamageInfo() || 
				(eventInfo.GetDamageInfo() && (eventInfo.GetDamageInfo()->GetDamageType() == HEAL || eventInfo.GetDamageInfo()->GetDamageType() == NODAMAGE)))
				return;

			caster->CastSpell(caster, SPELL_PALADIN_RECKONING, true);
			if (Aura* aura = caster->GetAura(SPELL_PALADIN_RECKONING))
				if (aura->GetStackAmount() == 50)
					caster->CastSpell(caster, SPELL_PALADIN_RECKONING_ACTIVATION, true);
		}
	}

	void Register() override
	{
		OnEffectApply += AuraEffectApplyFn(aura_pal_greater_blessing_of_wisdom::HandleApply, EFFECT_0, SPELL_AURA_OBS_MOD_POWER, AURA_EFFECT_HANDLE_REAL);
		OnEffectRemove += AuraEffectRemoveFn(aura_pal_greater_blessing_of_wisdom::HandleRemove, EFFECT_0, SPELL_AURA_OBS_MOD_POWER, AURA_EFFECT_HANDLE_REAL);
		OnProc += AuraProcFn(aura_pal_greater_blessing_of_wisdom::HandleProc);
	}
};

// 1022 - Blessing of Protection
class spell_pal_blessing_of_proteccion : public SpellScript
{
	PrepareSpellScript(spell_pal_blessing_of_proteccion);

	bool Validate(SpellInfo const* /*spell*/) override
	{
		return ValidateSpellInfo({ SPELL_PALADIN_FORBEARANCE });
	}

	SpellCastResult CheckForbearance()
	{
		if (Unit* target = GetExplTargetUnit())
		{
			if (target->HasAura(SPELL_PALADIN_FORBEARANCE))
			{
				return SPELL_FAILED_TARGET_AURASTATE;
			}
		}
		return SPELL_CAST_OK;
	}

	void HandleOnHit()
	{
		if (Player* player = GetCaster()->ToPlayer())
			if (Unit* target = GetHitUnit())
				player->CastSpell(target, SPELL_PALADIN_FORBEARANCE, true);
	}

	void Register() override
	{
		OnCheckCast += SpellCheckCastFn(spell_pal_blessing_of_proteccion::CheckForbearance);
		OnHit += SpellHitFn(spell_pal_blessing_of_proteccion::HandleOnHit);
	}
};

// 1022 - Blessing of Protection
class aura_pal_blessing_of_proteccion : public AuraScript
{
	PrepareAuraScript(aura_pal_blessing_of_proteccion);

	void HandleApply(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /* mode */)
	{
		Unit* caster = GetCaster();
		Unit* target = GetTarget();
		if (!caster || !target)
			return;

		if (caster->HasAura(SPELL_PALADIN_HOLY_RITUAL) && caster->GetGUID() != target->GetGUID())
			caster->CastSpell(target, SPELL_PALADIN_HOLY_RITUAL_HEAL, true);
	}

	void HandleRemove(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /* mode */)
	{
		Unit* caster = GetCaster();
		Unit* target = GetTarget();
		if (!caster || !target)
			return;

		if (caster->HasAura(SPELL_PALADIN_HOLY_RITUAL) && caster->GetGUID() != target->GetGUID())
			caster->CastSpell(target, SPELL_PALADIN_HOLY_RITUAL_HEAL, true);
	}

	void Register() override
	{
		OnEffectApply += AuraEffectApplyFn(aura_pal_blessing_of_proteccion::HandleApply, EFFECT_0, SPELL_AURA_SCHOOL_IMMUNITY, AURA_EFFECT_HANDLE_REAL);
		OnEffectRemove += AuraEffectRemoveFn(aura_pal_blessing_of_proteccion::HandleRemove, EFFECT_0, SPELL_AURA_SCHOOL_IMMUNITY, AURA_EFFECT_HANDLE_REAL);
	}
};

// 1044 - Blessing of Freedom
class aura_pal_blessing_of_freedom : public AuraScript
{
	PrepareAuraScript(aura_pal_blessing_of_freedom);

	void HandleApply(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /* mode */)
	{
		Unit* caster = GetCaster();
		Unit* target = GetTarget();
		if (!caster || !target)
			return;

		if (caster->HasAura(SPELL_PALADIN_HOLY_RITUAL) && caster->GetGUID() != target->GetGUID())
			caster->CastSpell(target, SPELL_PALADIN_HOLY_RITUAL_HEAL, true);
	}

	void HandleRemove(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /* mode */)
	{
		Unit* caster = GetCaster();
		Unit* target = GetTarget();
		if (!caster || !target)
			return;

		if (caster->HasAura(SPELL_PALADIN_HOLY_RITUAL) && caster->GetGUID() != target->GetGUID())
			caster->CastSpell(target, SPELL_PALADIN_HOLY_RITUAL_HEAL, true);
	}

	void Register() override
	{
		OnEffectApply += AuraEffectApplyFn(aura_pal_blessing_of_freedom::HandleApply, EFFECT_0, SPELL_AURA_MECHANIC_IMMUNITY, AURA_EFFECT_HANDLE_REAL);
		OnEffectRemove += AuraEffectRemoveFn(aura_pal_blessing_of_freedom::HandleRemove, EFFECT_0, SPELL_AURA_MECHANIC_IMMUNITY, AURA_EFFECT_HANDLE_REAL);
	}
};

// 210256 - Blessing of Sanctuary
class aura_pal_blessing_of_sanctuary : public AuraScript
{
	PrepareAuraScript(aura_pal_blessing_of_sanctuary);

	void HandleApply(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /* mode */)
	{
		Unit* caster = GetCaster();
		Unit* target = GetTarget();
		if (!caster || !target)
			return;

		if (caster->HasAura(SPELL_PALADIN_HOLY_RITUAL) && caster->GetGUID() != target->GetGUID())
			caster->CastSpell(target, SPELL_PALADIN_HOLY_RITUAL_HEAL, true);
	}

	void HandleRemove(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /* mode */)
	{
		Unit* caster = GetCaster();
		Unit* target = GetTarget();
		if (!caster || !target)
			return;

		if (caster->HasAura(SPELL_PALADIN_HOLY_RITUAL) && caster->GetGUID() != target->GetGUID())
			caster->CastSpell(target, SPELL_PALADIN_HOLY_RITUAL_HEAL, true);
	}

	void Register() override
	{
		OnEffectApply += AuraEffectApplyFn(aura_pal_blessing_of_sanctuary::HandleApply, EFFECT_1, SPELL_AURA_MECHANIC_DURATION_MOD, AURA_EFFECT_HANDLE_REAL);
		OnEffectRemove += AuraEffectRemoveFn(aura_pal_blessing_of_sanctuary::HandleRemove, EFFECT_1, SPELL_AURA_MECHANIC_DURATION_MOD, AURA_EFFECT_HANDLE_REAL);
	}
};

// 204914 - Divine Punisher
class aura_pal_divine_punisher : public AuraScript
{
	PrepareAuraScript(aura_pal_divine_punisher);

	bool CheckProc(ProcEventInfo& eventInfo)
	{
		if (eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == SPELL_PALADIN_JUDGMENT)
			return true;

		return false;
	}

	void HandleProc(ProcEventInfo& eventInfo)
	{
		Unit* caster = GetCaster();
		Unit* target = eventInfo.GetActionTarget();
		if (!caster || !target)
			return;

		if (caster->Variables.GetValue("DivinePunisherTarget", ObjectGuid::Empty) == target->GetGUID())
		{
            if (caster->Variables.Exist("DivinePunisherTarget"))
                caster->Variables.Remove("DivinePunisherTarget");
			caster->CastSpell(caster, SPELL_PALADIN_DIVINE_PUNISHER_ENERGIZE, true);
		}
		else
            caster->Variables.Set("DivinePunisherTarget", target->GetGUID());
	}

	void Register() override
	{
		DoCheckProc += AuraCheckProcFn(aura_pal_divine_punisher::CheckProc);
		OnProc += AuraProcFn(aura_pal_divine_punisher::HandleProc);
	}
};

// 197646 - Divine Purpose (Holy)
class aura_pal_divine_purpose_holy : public AuraScript
{
	PrepareAuraScript(aura_pal_divine_purpose_holy);

	bool CheckProc(ProcEventInfo& eventInfo)
	{
		return false;
	}

	void Register() override
	{
		DoCheckProc += AuraCheckProcFn(aura_pal_divine_purpose_holy::CheckProc);
	}
};

// 216327 - Light's Grace
class aura_pal_lights_grace : public AuraScript
{
    PrepareAuraScript(aura_pal_lights_grace);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == SPELL_PALADIN_HOLY_LIGHT)
            return true;

        return false;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_pal_lights_grace::CheckProc);
    }
};

// 216868 - Hallowed Ground
class aura_pal_hallowed_ground : public AuraScript
{
    PrepareAuraScript(aura_pal_hallowed_ground);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == SPELL_PALADIN_CONSECRATION)
            return true;

        return false;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_pal_hallowed_ground::CheckProc);
    }
};

// 119952 - Arcing Light
class spell_pal_arcing_light : public SpellScript
{
	PrepareSpellScript(spell_pal_arcing_light);

	void FilterTargets(std::list<WorldObject*>& targets)
	{
		if (Unit* caster = GetCaster())
		{
			targets.remove(caster);
			targets.sort(Trinity::HealthPctOrderPred());
			if (targets.size() > 6)
				Trinity::Containers::RandomResize(targets, 6);
		}
	}

	void Register() override
	{
		OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_pal_arcing_light::FilterTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ALLY);
	}
};

// 200025 - Beacon of Virtue
class spell_pal_beacon_of_virtude : public SpellScript
{
    PrepareSpellScript(spell_pal_beacon_of_virtude);

    SpellCastResult CheckCast()
    {
        Unit* caster = GetCaster();
        Unit* target = GetExplTargetUnit();
        if (!caster || !target)
            return SPELL_FAILED_DONT_REPORT;

        Player* casterPlayer = caster->ToPlayer();
        if (!casterPlayer)
            return SPELL_FAILED_DONT_REPORT;

        Player* targetPlayer = target->ToPlayer();
        if (!targetPlayer)
            return SPELL_FAILED_BAD_TARGETS;

        if (!targetPlayer->IsInPartyWith(casterPlayer) && !targetPlayer->IsInRaidWith(casterPlayer))
            return SPELL_FAILED_TARGET_NOT_IN_PARTY;

        return SPELL_CAST_OK;
    }

    void CacheMainTarget(WorldObject*& target)
    {
        if (target)
        {
            UnitList list;
            Unit* unit = target->ToUnit();
            if (!unit)
                return;

            if (Unit* caster = GetCaster())
            {
                unit->GetFriendlyUnitListInRange(list, 30.f, true);
                list.remove_if([caster](Unit* unit)
                {
                    if (!unit->ToPlayer())
                        return true;

                    if (!unit->ToPlayer()->IsInPartyWith(caster) && !unit->ToPlayer()->IsInRaidWith(caster))
                        return true;

                    return false;
                });

                if (list.size() > 0)
                {
                    list.sort(Trinity::HealthPctOrderPred());
                    uint8 maxTargets = sSpellMgr->GetSpellInfo(SPELL_PALADIN_BEACON_OF_VIRTUE)->GetEffect(EFFECT_1).BasePoints;
                    if (list.size() > maxTargets)
                        Trinity::Containers::RandomResize(list, maxTargets);
                }
                list.push_back(unit);
            }

            units = list;
        }
    }

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        targets.clear();

        for (Unit* unit : units)
            targets.push_back(unit);
    }

    void HandleHit()
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        caster->CastCustomSpell(caster, SPELL_PALADIN_BEACON_OF_LIGHT_PROC_AURA, 0, NULL, NULL, true, nullptr, nullptr, target->GetGUID());
        if (Aura* virtue = caster->GetAura(SPELL_PALADIN_BEACON_OF_LIGHT_PROC_AURA, target->GetGUID()))
            virtue->SetDuration(8 * IN_MILLISECONDS);
    }

    void Register() override
    {
        OnCheckCast += SpellCheckCastFn(spell_pal_beacon_of_virtude::CheckCast);
        OnObjectTargetSelect += SpellObjectTargetSelectFn(spell_pal_beacon_of_virtude::CacheMainTarget, EFFECT_0, TARGET_UNIT_TARGET_ALLY);
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_pal_beacon_of_virtude::FilterTargets, EFFECT_1, TARGET_UNIT_DEST_AREA_ALLY);
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_pal_beacon_of_virtude::FilterTargets, EFFECT_2, TARGET_UNIT_DEST_AREA_ALLY);
        OnHit += SpellHitFn(spell_pal_beacon_of_virtude::HandleHit);
    }

private:
    UnitList units;
};

// 216855 - Guarded by the Light
class aura_pal_guarded_by_the_light : public AuraScript
{
	PrepareAuraScript(aura_pal_guarded_by_the_light);

	bool CheckProc(ProcEventInfo& eventInfo)
	{
		if (eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == SPELL_PALADIN_FLASH_OF_LIGHT)
			return true;

		return false;
	}

	void Register() override
	{
		DoCheckProc += AuraCheckProcFn(aura_pal_guarded_by_the_light::CheckProc);
	}
};

// 210294 - Divine Favor
class aura_pal_divine_favor : public AuraScript
{
	PrepareAuraScript(aura_pal_divine_favor);

    void HandleApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* caster = GetCaster())
            caster->CastSpell(caster, SPELL_PALADIN_DIVINE_FAVOR_INTERRUPT, true);
    }

	bool CheckProc(ProcEventInfo& eventInfo)
	{
		if (eventInfo.GetSpellInfo() && (eventInfo.GetSpellInfo()->Id == SPELL_PALADIN_HOLY_LIGHT || eventInfo.GetSpellInfo()->Id == SPELL_PALADIN_FLASH_OF_LIGHT))
			return true;

		return false;
	}

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* caster = GetCaster())
            caster->RemoveAura(SPELL_PALADIN_DIVINE_FAVOR_INTERRUPT);
    }

	void Register() override
	{
        OnEffectApply += AuraEffectApplyFn(aura_pal_divine_favor::HandleApply, EFFECT_0, SPELL_AURA_ADD_PCT_MODIFIER, AURA_EFFECT_HANDLE_REAL);
		DoCheckProc += AuraCheckProcFn(aura_pal_divine_favor::CheckProc);
        OnEffectRemove += AuraEffectRemoveFn(aura_pal_divine_favor::HandleRemove, EFFECT_0, SPELL_AURA_ADD_PCT_MODIFIER, AURA_EFFECT_HANDLE_REAL);
	}
};

// 210378 - Darkest before the Dawn
class aura_pal_darkest_before_the_dawn : public AuraScript
{
	PrepareAuraScript(aura_pal_darkest_before_the_dawn);

	void HandlePeriodic(AuraEffect const* aurEff)
	{
		if (Unit* caster = GetCaster())
			if (!caster->GetSpellHistory()->HasCooldown(SPELL_PALADIN_LIGHT_OF_DAWN))
				caster->CastSpell(caster, SPELL_PALADIN_DARKEST_BEFORE_THE_DAWN_BUFF, true);
	}

	void Register() override
	{
		OnEffectPeriodic += AuraEffectPeriodicFn(aura_pal_darkest_before_the_dawn::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
	}
};

// 210391 - Darkest before the Dawn Buff
class aura_pal_darkest_before_the_dawn_buff : public AuraScript
{
	PrepareAuraScript(aura_pal_darkest_before_the_dawn_buff);

	bool CheckProc(ProcEventInfo& eventInfo)
	{
		return false;
	}

	void Register() override
	{
		DoCheckProc += AuraCheckProcFn(aura_pal_darkest_before_the_dawn_buff::CheckProc);
	}
};

// 246867 - Lawbringer Damage
class spell_pal_lawbringer_damage : public SpellScript
{
    PrepareSpellScript(spell_pal_lawbringer_damage);

    void FilterTarget(std::list<WorldObject*>& targets)
    {
        if (Unit* caster = GetCaster())
            targets.remove_if(Trinity::UnitAuraCheck(false, SPELL_PALADIN_LIGHTBRINGER_DEBUFF, caster->GetGUID()));
    }

    void HandleHitTarget(SpellEffIndex /*effIndex*/)
    {
        if (Unit* caster = GetCaster())
        {
            if (Unit* target = GetHitUnit())
            {
                uint8 pct = GetSpellInfo()->GetEffect(EFFECT_1).BasePoints;
                SetHitDamage(CalculatePct(target->IsPlayer() ? target->GetMaxHealth() : caster->GetMaxHealth(), pct));
            }
        }
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_pal_lawbringer_damage::FilterTarget, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
        OnEffectHitTarget += SpellEffectFn(spell_pal_lawbringer_damage::HandleHitTarget, EFFECT_0, SPELL_EFFECT_DAMAGE_FROM_MAX_HEALTH_PCT);
    }
};

// 204934 - Law and Order
// Last Update 8.0.1 Build 28153
class aura_pal_law_and_order : public AuraScript
{
    PrepareAuraScript(aura_pal_law_and_order);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetSpellInfo() && (eventInfo.GetSpellInfo()->Id == SPELL_PALADIN_BLADE_OF_JUSTICE || eventInfo.GetSpellInfo()->Id == SPELL_PALADIN_DIVINE_HAMMER))
            return true;

        return false;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();
        Unit* target = eventInfo.GetActionTarget();
        if (!caster || !target)
            return;

		if (caster->GetGUID() == target->GetGUID())
			return;

        if (Aura* aura = target->GetAura(SPELL_PALADIN_HAND_OF_HIDRANCE_SLOW, caster->GetGUID()))
        {
            int32 duration = aura->GetDuration() + 3 * IN_MILLISECONDS;
            //Diminish Return for Snare case, the max time in pvp is 8 seconds
            if (target->IsPlayer() && duration > 8 * IN_MILLISECONDS)
                duration = 8 * IN_MILLISECONDS;
            else if(!target->IsPlayer() && duration > 10 * IN_MILLISECONDS)
                duration = 10 * IN_MILLISECONDS;

            aura->SetDuration(duration);
            aura->SetMaxDuration(duration);
        }
        else if (Aura* aura = caster->AddAura(SPELL_PALADIN_HAND_OF_HIDRANCE_SLOW, target))
        {
            aura->SetDuration(3 * IN_MILLISECONDS);
            aura->SetMaxDuration(3 * IN_MILLISECONDS);
        }            
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_pal_law_and_order::CheckProc);
        OnProc += AuraProcFn(aura_pal_law_and_order::HandleProc);
    }
};

// 183218 - Hand of Hindrance Slow
// Last Update 8.0.1 Build 28153
class aura_pal_hand_of_hidrance_slow : public AuraScript
{
    PrepareAuraScript(aura_pal_hand_of_hidrance_slow);

    void HandleRemove(AuraEffect const* /*aurEffect*/, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* caster = GetCaster())
        {
            if (!caster->HasAura(SPELL_PALADIN_LAW_AND_ORDER))
                return;

            if (GetTargetApplication()->GetRemoveMode() == AURA_REMOVE_BY_EXPIRE || GetTargetApplication()->GetRemoveMode() == AURA_REMOVE_BY_DEATH)
                return;
            
            caster->GetSpellHistory()->ModifyCooldown(SPELL_PALADIN_HAND_OF_HIDRANCE_SLOW, -1 * IN_MILLISECONDS * (int32)sSpellMgr->GetSpellInfo(SPELL_PALADIN_LAW_AND_ORDER)->GetEffect(EFFECT_0).BasePoints);
        }
    }

    void Register() override
    {
        OnEffectRemove += AuraEffectRemoveFn(aura_pal_hand_of_hidrance_slow::HandleRemove, EFFECT_0, SPELL_AURA_MOD_DECREASE_SPEED, AURA_EFFECT_HANDLE_REAL);
    }
};

// 199542 - Steed of Glory (Applies to every Paladin steed)
class aura_steed_of_glory : public AuraScript
{
    PrepareAuraScript(aura_steed_of_glory);

    void HandleApply(AuraEffect const* /*aurEffect*/, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* caster = GetCaster())
            if (caster->HasAura(SPELL_PALADIN_STEED_OF_GLORY))
                caster->CastSpell(caster, SPELL_PALADIN_STEED_OF_GLORY_IMMUNITY, true);
    }

    void HandleRemove(AuraEffect const* /*aurEffect*/, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* caster = GetCaster())
            caster->RemoveAura(SPELL_PALADIN_STEED_OF_GLORY_IMMUNITY);
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(aura_steed_of_glory::HandleApply, EFFECT_2, SPELL_AURA_MOUNTED, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
        OnEffectRemove += AuraEffectRemoveFn(aura_steed_of_glory::HandleRemove, EFFECT_2, SPELL_AURA_MOUNTED, AURA_EFFECT_HANDLE_REAL);
    }
};

// 247675 - Hammer of Reckoning
class spell_pal_hammer_of_reckoning : public SpellScript
{
	PrepareSpellScript(spell_pal_hammer_of_reckoning);

	void HandleAfterCast()
	{
		if (Unit* caster = GetCaster())
		{
			caster->RemoveAurasDueToSpell(SPELL_PALADIN_RECKONING);
			if (caster->HasSpell(SPELL_PALADIN_CRUSADE))
			{
				caster->AddAura(SPELL_PALADIN_CRUSADE);
				if (Aura* aura = caster->GetAura(SPELL_PALADIN_CRUSADE))
					aura->SetDuration(12 * IN_MILLISECONDS);
			}
			else
			{
				caster->AddAura(SPELL_PALADIN_AVENGING_WRATH);
				if (Aura* aura = caster->GetAura(SPELL_PALADIN_AVENGING_WRATH))
					aura->SetDuration(6 * IN_MILLISECONDS);
			}
		}
	}

	void Register() override
	{
		AfterCast += SpellCastFn(spell_pal_hammer_of_reckoning::HandleAfterCast);
	}
};

// 247677 - Reckoning
class aura_pal_reckoning : public AuraScript
{
	PrepareAuraScript(aura_pal_reckoning);

	void HandleRemove(AuraEffect const* aurEff, AuraEffectHandleModes mode)
	{
		if (Unit* caster = GetTarget())
			caster->RemoveAura(SPELL_PALADIN_RECKONING_ACTIVATION);
	}

	void Register() override
	{
		OnEffectRemove += AuraEffectRemoveFn(aura_pal_reckoning::HandleRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
	}
};

// 199428 - Luminescence
class aura_pal_luminescence : public AuraScript
{
	PrepareAuraScript(aura_pal_luminescence);

	bool Validate(SpellInfo const* /*spellInfo*/) override
	{
		return ValidateSpellInfo({ SPELL_PALADIN_LUMINESCENCE });
	}

	bool CheckProc(ProcEventInfo& eventInfo)
	{
		if (Unit* caster = GetCaster())
			if ((eventInfo.GetHealInfo() && eventInfo.GetHealInfo()->GetHeal() > 0 && eventInfo.GetHealInfo()->GetHealer() && caster->GetGUID() != eventInfo.GetHealInfo()->GetHealer()->GetGUID()) ||
				(eventInfo.GetDamageInfo() && (eventInfo.GetDamageInfo()->GetDamageType() == HEAL && eventInfo.GetDamageInfo()->GetDamage() > 0 && eventInfo.GetDamageInfo()->GetAttacker() && caster->GetGUID() != eventInfo.GetDamageInfo()->GetAttacker()->GetGUID())))
					return true;

		return false;
	}

	void HandleProc(ProcEventInfo& eventInfo)
	{
		if (Unit* caster = GetCaster())
		{
			int32 value = 0;
			if (eventInfo.GetHealInfo() && eventInfo.GetHealInfo()->GetHeal() > 0)
				value = CalculatePct(eventInfo.GetHealInfo()->GetHeal(), sSpellMgr->GetSpellInfo(SPELL_PALADIN_LUMINESCENCE)->GetEffect(EFFECT_0).BasePoints);
			else if (eventInfo.GetDamageInfo()->GetDamageType() == HEAL && eventInfo.GetDamageInfo()->GetDamage() > 0)
				value = CalculatePct(eventInfo.GetDamageInfo()->GetDamage(), sSpellMgr->GetSpellInfo(SPELL_PALADIN_LUMINESCENCE)->GetEffect(EFFECT_0).BasePoints);

			caster->CastCustomSpell(SPELL_PALADIN_LUMINESCENCE_HEAL, SPELLVALUE_BASE_POINT0, value, caster, true);
		}
	}

	void Register() override
	{
		DoCheckProc += AuraCheckProcFn(aura_pal_luminescence::CheckProc);
		OnProc += AuraProcFn(aura_pal_luminescence::HandleProc);
	}
};

// 199435 - Luminescence Heal
class spell_pal_luminescence_heal : public SpellScript
{
	PrepareSpellScript(spell_pal_luminescence_heal);

	void FilterTargets(std::list<WorldObject*>& targets)
	{
		if (Unit* caster = GetCaster())
			targets.remove(caster);
	}

	void Register() override
	{
		OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_pal_luminescence_heal::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ALLY);
	}
};

// 210323 - Vengeance Aura
class aura_pal_vengeance_aura : public AuraScript
{
	PrepareAuraScript(aura_pal_vengeance_aura);

	bool CheckProc(ProcEventInfo& eventInfo)
	{
        if (!eventInfo.GetSpellInfo())
            return false;

		Unit* caster = GetCaster();
		Unit* owner = GetTarget();
		if (!caster || !owner)
			return false;

		if (!owner->HasAura(SPELL_PALADIN_GREATER_BLESSING_OF_KINGS, caster->GetGUID()) && !owner->HasAura(SPELL_PALADIN_GREATER_BLESSING_OF_WISDOM, caster->GetGUID()))
			return false;

		const SpellInfo* spellInfo = eventInfo.GetSpellInfo();
		if (spellInfo)
		{
			for (auto effect : spellInfo->GetEffects())
					if (effect.ApplyAuraName == SPELL_AURA_MOD_STUN || effect.ApplyAuraName == SPELL_AURA_MOD_FEAR || effect.ApplyAuraName == SPELL_AURA_MOD_FEAR_2 ||
						effect.ApplyAuraName == SPELL_AURA_MOD_CHARM || effect.ApplyAuraName == SPELL_AURA_MOD_CONFUSE || effect.ApplyAuraName == SPELL_AURA_MOD_STUN_DISABLE_GRAVITY)
						return true;
		}

		return false;
	}

	void HandleProc(ProcEventInfo& eventInfo)
	{
		if (Unit* caster = GetCaster())
			caster->CastSpell(caster, SPELL_PALADIN_VENGEANCE_AURA_BUFF, true);
	}

	void Register() override
	{
		DoCheckProc += AuraCheckProcFn(aura_pal_vengeance_aura::CheckProc);
		OnProc += AuraProcFn(aura_pal_vengeance_aura::HandleProc);
	}
};

// 197277 - Judgment Aura
class aura_judgment_aura : public AuraScript
{
    PrepareAuraScript(aura_judgment_aura);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (Unit* caster = GetCaster())
            if (Spell const* procSpell = eventInfo.GetProcSpell())
            {
                if (procSpell->GetCaster()->GetGUID() == caster->GetGUID())
                    if (SpellPowerCost const* powerCost = procSpell->GetPowerCost(POWER_HOLY_POWER))
                        if (powerCost->Amount > 0)
                            return true;
            }

        return false;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();
        Unit* target = GetTarget();
        if (!caster || !target)
            return;

        target->RemoveAurasDueToSpell(SPELL_PALADIN_JUDGMENT_RETRI_DEBUFF, caster->GetGUID());
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_judgment_aura::CheckProc);
        OnProc += AuraProcFn(aura_judgment_aura::HandleProc);
    }
};

// Last Update 8.0.1 Build 28153
// Call by Divine Steed Mounts - 221883 - 221885 - 221886 - 221887 - 254474
//276111 - 276112 - 254472 - 254473 - 254471
class spell_pal_divine_steed_mount : public AuraScript
{
    PrepareAuraScript(spell_pal_divine_steed_mount);

    void OnApply(AuraEffect const* /*auraEffect*/, AuraEffectHandleModes /*modes*/)
    {
        Unit* caster = GetCaster();
        if (!caster)
            return;

        Player* player = caster->ToPlayer();
        if (!player)
            return;

        player->SetUnitFlag3(UnitFlags3::UNIT_FLAG3_CAN_FIGHT_WITHOUT_DISMOUNT);

        if (player->HasAura(SPELL_PALADIN_GALLANT_STEED_POWER))
            player->CastSpell(player, SPELL_PALADIN_GALLANT_STEED_AT, true);
    }

    void OnRemove(AuraEffect const* /*auraEffect*/, AuraEffectHandleModes /*modes*/)
    {
        Unit* caster = GetCaster();
        if (!caster)
            return;

        Player* player = caster->ToPlayer();
        if (!player)
            return;

        player->RemoveUnitFlag3(UnitFlags3::UNIT_FLAG3_CAN_FIGHT_WITHOUT_DISMOUNT);
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_pal_divine_steed_mount::OnApply, EFFECT_2, SPELL_AURA_MOUNTED, AURA_EFFECT_HANDLE_REAL);
        OnEffectRemove += AuraEffectRemoveFn(spell_pal_divine_steed_mount::OnRemove, EFFECT_2, SPELL_AURA_MOUNTED, AURA_EFFECT_HANDLE_REAL);
    }
};

// 31884 - Avenging Wrath
class aura_pal_avenging_wrath : public AuraScript
{
    PrepareAuraScript(aura_pal_avenging_wrath);

    void HandleApply(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /* mode */)
    {
        if (Unit* caster = GetCaster())
            if (Aura* aura = caster->GetAura(SPELL_PALADIN_AVENGER_MIGHT_POWER))
                caster->CastCustomSpell(SPELL_PALADIN_AVENGER_MIGHT_BUFF, SPELLVALUE_BASE_POINT0, aura->GetEffect(EFFECT_0)->GetAmount(), caster, true);
    }

    void HandleRemove(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /* mode */)
    {
        if (Unit* caster = GetCaster())
            caster->RemoveAura(SPELL_PALADIN_AVENGER_MIGHT_BUFF);
    }

    void CalculateAmount(AuraEffect const* /*aurEff*/, int32& amount, bool& /*canBeRecalculated*/)
    {
        if (Unit* caster = GetCaster())
            if (Aura* aura = caster->GetAura(SPELL_PALADIN_SANCTIFIED_WRATH))
                amount = aura->GetEffect(EFFECT_1)->GetAmount();
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(aura_pal_avenging_wrath::HandleApply, EFFECT_0, SPELL_AURA_ADD_PCT_MODIFIER, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
        OnEffectRemove += AuraEffectRemoveFn(aura_pal_avenging_wrath::HandleRemove, EFFECT_0, SPELL_AURA_ADD_PCT_MODIFIER, AURA_EFFECT_HANDLE_REAL);
        DoEffectCalcAmount += AuraEffectCalcAmountFn(aura_pal_avenging_wrath::CalculateAmount, EFFECT_5, SPELL_AURA_ADD_PCT_MODIFIER);
    }
};

// 53563 - Beacon of Light / 156910 - Beacon of Faith
class spell_pal_beacon_of_light : public SpellScript
{
    PrepareSpellScript(spell_pal_beacon_of_light);

    SpellCastResult CheckCast()
    {
        Unit* caster = GetCaster();
        Unit* target = GetExplTargetUnit();
        if (!caster || !target)
            return SPELL_FAILED_DONT_REPORT;

        Player* casterPlayer = caster->ToPlayer();
        if (!casterPlayer)
            return SPELL_FAILED_DONT_REPORT;

        Player* targetPlayer = target->ToPlayer();
        if (!targetPlayer)
            return SPELL_FAILED_BAD_TARGETS;

        if (!targetPlayer->IsInPartyWith(casterPlayer) && !targetPlayer->IsInRaidWith(casterPlayer))
            return SPELL_FAILED_TARGET_NOT_IN_PARTY;

        if (GetSpellInfo()->Id == SPELL_PALADIN_BEACON_OF_LIGHT && targetPlayer->HasAura(SPELL_PALADIN_BEACON_OF_FAITH, casterPlayer->GetGUID()))
            return SPELL_FAILED_BAD_TARGETS;

        if (GetSpellInfo()->Id == SPELL_PALADIN_BEACON_OF_FAITH && targetPlayer->HasAura(SPELL_PALADIN_BEACON_OF_LIGHT, casterPlayer->GetGUID()))
            return SPELL_FAILED_BAD_TARGETS;

        return SPELL_CAST_OK;
    }

    void Register() override
    {
        OnCheckCast += SpellCheckCastFn(spell_pal_beacon_of_light::CheckCast);
    }
};

// 53563 - Beacon of Light / 156910 - Beacon of Faith
class aura_pal_beacon_of_light : public AuraScript
{
    PrepareAuraScript(aura_pal_beacon_of_light);

    void HandleApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetTarget();
        if (!caster || !target)
            return;

        if (GetSpellInfo()->Id == SPELL_PALADIN_BEACON_OF_LIGHT)
            caster->CastCustomSpell(caster, SPELL_PALADIN_BEACON_OF_LIGHT_PROC_AURA, 0, NULL, NULL, true, nullptr, nullptr, target->GetGUID());
        else
            caster->CastCustomSpell(caster, SPELL_PALADIN_BEACON_OF_FAITH_PROC_AURA, 0, NULL, NULL, true, nullptr, nullptr, target->GetGUID());

        if (caster->GetGUID() != target->GetGUID())
            caster->RemoveAura(SPELL_PALADIN_BEACON_OF_LIGHT_PROC_AURA, caster->GetGUID());
    }

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetTarget();
        if (!caster || !target)
            return;

        if (GetSpellInfo()->Id == SPELL_PALADIN_BEACON_OF_LIGHT)
            caster->RemoveAura(SPELL_PALADIN_BEACON_OF_LIGHT_PROC_AURA, target->GetGUID());
        else
            caster->RemoveAura(SPELL_PALADIN_BEACON_OF_FAITH_PROC_AURA, target->GetGUID());
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(aura_pal_beacon_of_light::HandleApply, EFFECT_2, SPELL_AURA_MOD_HEALING_RECEIVED, AURA_EFFECT_HANDLE_REAL);
        OnEffectRemove += AuraEffectRemoveFn(aura_pal_beacon_of_light::HandleRemove, EFFECT_2, SPELL_AURA_MOD_HEALING_RECEIVED, AURA_EFFECT_HANDLE_REAL);
    }
};

// 53651 - Beacon of Light Proc / 177173 - Beacon of Faith Proc
class aura_pal_beacon_of_light_proc : public AuraScript
{
    PrepareAuraScript(aura_pal_beacon_of_light_proc);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        Unit* ownerOfBeacon = GetCaster();
        Unit* targetOfBeacon = GetTarget();
        if (!ownerOfBeacon || !targetOfBeacon)
            return false;

        if (eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id != SPELL_PALADIN_BEACON_OF_LIGHT_HEAL &&
            eventInfo.GetSpellInfo()->Id != SPELL_PALADIN_LIGHT_OF_THE_MARTYR && targetOfBeacon->IsWithinLOSInMap(ownerOfBeacon))
            return true;

        return false;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();
        Unit* ownerOfBeacon = GetCaster();
        Unit* targetOfBeacon = GetTarget();
        if (!ownerOfBeacon || !targetOfBeacon)
            return;

        if (GetSpellInfo()->Id == SPELL_PALADIN_BEACON_OF_LIGHT_PROC_AURA &&
           (!ownerOfBeacon->HasAura(SPELL_PALADIN_BEACON_OF_LIGHT, targetOfBeacon->GetGUID()) && !ownerOfBeacon->HasAura(SPELL_PALADIN_BEACON_OF_VIRTUE, targetOfBeacon->GetGUID())))
        {
            targetOfBeacon->RemoveAura(SPELL_PALADIN_BEACON_OF_LIGHT_PROC_AURA);
            return;
        }

        if (GetSpellInfo()->Id == SPELL_PALADIN_BEACON_OF_FAITH_PROC_AURA && !ownerOfBeacon->HasAura(SPELL_PALADIN_BEACON_OF_FAITH, targetOfBeacon->GetGUID()))
        {
            targetOfBeacon->RemoveAura(SPELL_PALADIN_BEACON_OF_FAITH_PROC_AURA);
            return;
        }

        Unit* targetOfHeal = eventInfo.GetActionTarget();
        if (!targetOfHeal)
            return;

        if (!targetOfHeal->IsInRaidWith(targetOfBeacon) && !targetOfHeal->IsInPartyWith(targetOfBeacon))
            return;

        if (targetOfHeal->GetGUID() == ownerOfBeacon->GetGUID())
        {
            if (eventInfo.GetSpellInfo() && (eventInfo.GetSpellInfo()->Id == SPELL_PALADIN_FLASH_OF_LIGHT || eventInfo.GetSpellInfo()->Id == SPELL_PALADIN_HOLY_LIGHT))
            {
                // Refund mana.
                uint32 percent = sSpellMgr->GetSpellInfo(SPELL_PALADIN_BEACON_OF_LIGTH_REFUND)->GetEffect(EFFECT_0).BasePoints;
                uint32 cost = eventInfo.GetSpellInfo()->CalcPowerCost(targetOfBeacon, SPELL_SCHOOL_MASK_HOLY)[0].Amount;
                targetOfBeacon->CastCustomSpell(SPELL_PALADIN_BEACONS_ENERGIZE, SPELLVALUE_BASE_POINT0, CalculatePct(cost, percent), targetOfBeacon, true);
            }
        }
        else
        {
            HealInfo* healInfo = eventInfo.GetHealInfo();
            if (!healInfo)
                return;

            int32 heal = CalculatePct(healInfo->GetHeal(), (targetOfBeacon->HasSpell(SPELL_PALADIN_BEACON_OF_FAITH)) ? 30 : 40);
            targetOfBeacon->CastCustomSpell(SPELL_PALADIN_BEACON_OF_LIGHT_HEAL, SPELLVALUE_BASE_POINT0, heal, ownerOfBeacon, true);
        }
    }

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes mode)
    {
        Unit* ownerOfBeacon = GetCaster();
        Unit* targetOfBeacon = GetTarget();
        if (!ownerOfBeacon || !targetOfBeacon)
            return;

        if (GetSpellInfo()->Id == SPELL_PALADIN_BEACON_OF_FAITH_PROC_AURA)
            ownerOfBeacon->RemoveAura(SPELL_PALADIN_BEACON_OF_FAITH, targetOfBeacon->GetGUID());
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_pal_beacon_of_light_proc::CheckProc);
        OnProc += AuraProcFn(aura_pal_beacon_of_light_proc::HandleProc);
        OnEffectRemove += AuraEffectRemoveFn(aura_pal_beacon_of_light_proc::HandleRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

//Called by 197561 Avenger's Valor 
//Last Update 8.0.1 Build 28153
class aura_pal_avenger_of_valor_proc : public AuraScript
{
    PrepareAuraScript(aura_pal_avenger_of_valor_proc);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();
        if (!caster)
            return false;

        if (eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == SPELL_PALADIN_SHIELD_OF_THE_RIGHTEOUS)
            return true;

        return false;
    }    

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_pal_avenger_of_valor_proc::CheckProc);
    }
};

// Last Update 8.0.1 Build 28153
// Called by Blessing of Sacrifice - 199448
class aura_pal_ultimate_sacrifice : public AuraScript
{
    PrepareAuraScript(aura_pal_ultimate_sacrifice);

    int32 damageAcumulated;

    void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* caster = GetCaster())
            if (caster->IsPlayer())
                caster->ToPlayer()->GetSpellHistory()->StartCooldownROG(GetSpellInfo(), 0, nullptr, false, true, 120 * IN_MILLISECONDS);
    }

    void CalculateAmount(AuraEffect const* /*aurEff*/, int32 & amount, bool & canBeRecalculated)
    {
        // Set absorbtion amount to unlimited
        amount = -1;
    }

    void HandleOnEffectAbsorb(AuraEffect* aurEff, DamageInfo& dmgInfo, uint32& absorbAmount)
    {
        if (Unit* caster = GetCaster())
        {
            if (SpellInfo const* spellInfo = GetSpellInfo())
                absorbAmount = CalculatePct(dmgInfo.GetDamage(), spellInfo->GetEffect(EFFECT_0).BasePoints);

            if (!absorbAmount)
                return;

            int32 bp0 = absorbAmount;

            SpellInfo const* spellInfoDamage = sSpellMgr->GetSpellInfo(SPELL_PALADIN_ULTIMATE_SACRIFICE_DAMAGE);
            if (!spellInfoDamage)
                return;

            SpellDurationEntry const* durationEntry = spellInfoDamage->DurationEntry;
            if (!durationEntry)
                return;

            if (spellInfoDamage->GetEffect(EFFECT_0).ApplyAuraPeriod != 0)
                bp0 /= durationEntry->Duration / spellInfoDamage->GetEffect(EFFECT_0).ApplyAuraPeriod;

            damageAcumulated += bp0;

            caster->CastCustomSpell(SPELL_PALADIN_ULTIMATE_SACRIFICE_DAMAGE, SPELLVALUE_BASE_POINT0, damageAcumulated, caster, true);
        }
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(aura_pal_ultimate_sacrifice::OnApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        DoEffectCalcAmount += AuraEffectCalcAmountFn(aura_pal_ultimate_sacrifice::CalculateAmount, EFFECT_2, SPELL_AURA_SCHOOL_ABSORB);
        OnEffectAbsorb += AuraEffectAbsorbFn(aura_pal_ultimate_sacrifice::HandleOnEffectAbsorb, EFFECT_2);
    }
};

// Last Update 8.0.1 Build 28153
// Called by Blessing of Sanctuary - 210256
class spell_pal_blessing_of_sanctuary : public SpellScript
{
    PrepareSpellScript(spell_pal_blessing_of_sanctuary);

    void HandleAfterCast()
    {
        Unit* target = GetExplTargetUnit();
        if (!target)
            return;

        target->RemoveAurasWithMechanic(((1 << MECHANIC_STUN) | (1 << MECHANIC_SILENCE) | (1 << MECHANIC_FEAR) | (1 << MECHANIC_HORROR)));
    }

    void Register() override
    {
        AfterCast += SpellCastFn(spell_pal_blessing_of_sanctuary::HandleAfterCast);
    }
};

// 271580 - Divine Judgment Aura
class aura_pal_divine_judgment_aura : public AuraScript
{
    PrepareAuraScript(aura_pal_divine_judgment_aura);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_pal_divine_judgment_aura::CheckProc);
    }
};

// 271581 - Divine Judgment Buff
class aura_pal_divine_judgment : public AuraScript
{
    PrepareAuraScript(aura_pal_divine_judgment);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == SPELL_PALADIN_JUDGMENT)
            return true;

        return false;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (Unit* caster = GetCaster())
            caster->RemoveAura(GetAura());
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_pal_divine_judgment::CheckProc);
        OnProc += AuraProcFn(aura_pal_divine_judgment::HandleProc);
    }
};

// 224239 - Divine Storm Damage
class spell_divine_storm_damage : public SpellScript
{
    PrepareSpellScript(spell_divine_storm_damage);

    void HandleHitTarget(SpellEffIndex /*effIndex*/)
    {
        if (Unit* caster = GetCaster())
            if (caster->HasAura(SPELL_PALADIN_DIVINE_JUDGMENT))
                caster->CastSpell(caster, SPELL_PALADIN_DIVINE_JUDGMENT_AURA, true);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_divine_storm_damage::HandleHitTarget, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

// 203791 - Last Defender
class aura_pal_last_defender : public AuraScript
{
    PrepareAuraScript(aura_pal_last_defender);

    void CalculateAmount(AuraEffect const* /*aurEff*/, int32& amount, bool& /*canBeRecalculated*/)
    {
        // Set absorbtion amount to unlimited
        amount = -1;
    }

    void HandleAbsorb(AuraEffect* /*aurEff*/, DamageInfo& dmgInfo, uint32& absorbAmount)
    {
        if (dmgInfo.GetDamage() <= 0)
            return;

        // Really simple to get any of the amount effects (4, 5 or 6).
        absorbAmount = CalculatePct(dmgInfo.GetDamage(), GetEffect(4)->GetAmount());
    }

    void Register() override
    {
        DoEffectCalcAmount += AuraEffectCalcAmountFn(aura_pal_last_defender::CalculateAmount, EFFECT_3, SPELL_AURA_SCHOOL_ABSORB);
        OnEffectAbsorb += AuraEffectAbsorbFn(aura_pal_last_defender::HandleAbsorb, EFFECT_3);
    }
};

// 198054 - Fist of Justice Protection
class aura_fist_of_fury_protection : public AuraScript
{
    PrepareAuraScript(aura_fist_of_fury_protection);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetSpellInfo() && (eventInfo.GetSpellInfo()->Id == SPELL_PALADIN_JUDGMENT_PROTECTION || eventInfo.GetSpellInfo()->Id == SPELL_PALADIN_JUDGMENT_HOLY))
            return true;

        return false;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (Unit* caster = GetCaster())
            if (Player* player = caster->ToPlayer())
                if (player->GetSpellHistory()->HasCooldown(SPELL_PALADIN_HAMMER_OF_JUSTICE))
                    if (SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(SPELL_PALADIN_FIST_OF_JUSTICE))
                    {
                        uint32 seconds = (player->GetSpecializationId() == TALENT_SPEC_PALADIN_HOLY) ? spellInfo->GetEffect(EFFECT_0).BasePoints : spellInfo->GetEffect(EFFECT_1).BasePoints;
                        player->GetSpellHistory()->ModifyCooldown(SPELL_PALADIN_HAMMER_OF_JUSTICE, seconds * -1s);
                    }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_fist_of_fury_protection::CheckProc);
        OnProc += AuraProcFn(aura_fist_of_fury_protection::HandleProc);
    }
};

// 4987 - Cleanse
class spell_pal_cleanse : public SpellScript
{
    PrepareSpellScript(spell_pal_cleanse);

    void OnSuccessfulDispel1(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        effect_0 = 0;
        if (caster->HasAura(SPELL_PALADIN_CLEANSE_THE_WEAK) && (target->HasAura(SPELL_PALADIN_DEVOTION_AURA, caster->GetGUID()) ||
            target->HasAura(SPELL_PALADIN_AURA_OF_SACRIFICE_ALLY, caster->GetGUID()) || target->HasAura(SPELL_PALADIN_AURA_OF_MERCY_AURA, caster->GetGUID())))
                effect_0 = 1;
    }

    void OnSuccessfulDispel2(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        effect_1 = 0;
        if (caster->HasAura(SPELL_PALADIN_CLEANSE_THE_WEAK) && (target->HasAura(SPELL_PALADIN_DEVOTION_AURA, caster->GetGUID()) ||
            target->HasAura(SPELL_PALADIN_AURA_OF_SACRIFICE_ALLY, caster->GetGUID()) || target->HasAura(SPELL_PALADIN_AURA_OF_MERCY_AURA, caster->GetGUID())))
        {
            CastSpellExtraArgs args(TRIGGERED_FULL_MASK);
            args.AddSpellBP0(0);
            args.AddSpellBP1(100);
            args.AddSpellBP2(0);
            caster->CastSpell(caster, SPELL_PALADIN_CLEANSE_THE_WEAK_DISPEL,args);
        }
    }

    void OnSuccessfulDispel3(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        effect_2 = 0;
        if (caster->HasAura(SPELL_PALADIN_CLEANSE_THE_WEAK) && (target->HasAura(SPELL_PALADIN_DEVOTION_AURA, caster->GetGUID()) ||
            target->HasAura(SPELL_PALADIN_AURA_OF_SACRIFICE_ALLY, caster->GetGUID()) || target->HasAura(SPELL_PALADIN_AURA_OF_MERCY_AURA, caster->GetGUID())))
            effect_2 = 1;
    }

    void HandleAfterHit()
    {
        if (Unit* caster = GetCaster())
            if (effect_0 || effect_1 || effect_2)
            {
                CastSpellExtraArgs args(TRIGGERED_FULL_MASK);
                args.AddSpellBP0(100 * effect_0);
                args.AddSpellBP1(100 * effect_1);
                args.AddSpellBP2(100 * effect_2);
                caster->GetSpellHistory()->ResetCharges(sSpellMgr->GetSpellInfo(SPELL_PALADIN_CLEANSE_THE_WEAK_DISPEL)->ChargeCategoryId);
                caster->CastSpell(caster, SPELL_PALADIN_CLEANSE_THE_WEAK_DISPEL, args);
            }
    }

    void Register() override
    {
        OnEffectSuccessfulDispel += SpellEffectFn(spell_pal_cleanse::OnSuccessfulDispel1, EFFECT_0, SPELL_EFFECT_DISPEL);
        OnEffectSuccessfulDispel += SpellEffectFn(spell_pal_cleanse::OnSuccessfulDispel2, EFFECT_1, SPELL_EFFECT_DISPEL);
        OnEffectSuccessfulDispel += SpellEffectFn(spell_pal_cleanse::OnSuccessfulDispel3, EFFECT_2, SPELL_EFFECT_DISPEL);
        AfterHit += SpellHitFn(spell_pal_cleanse::HandleAfterHit);
    }

private:
    uint8 effect_0;
    uint8 effect_1;
    uint8 effect_2;
};
 
// 199360 - Cleanse the Weak Dispel
class spell_pal_cleanse_the_weak_dispel : public SpellScript
{
    PrepareSpellScript(spell_pal_cleanse_the_weak_dispel);

    void HandleOnObjectAreaTargetSelect(std::list<WorldObject*>& targets)
    {
        if (Unit* caster = GetCaster())
            targets.remove_if([caster](WorldObject* target) 
            {
                if (!target->ToUnit())
                    return true;

                if (!target->ToUnit()->HasAura(SPELL_PALADIN_DEVOTION_AURA, caster->GetGUID()) &&
                    !target->ToUnit()->HasAura(SPELL_PALADIN_AURA_OF_SACRIFICE_ALLY, caster->GetGUID()) &&
                    !target->ToUnit()->HasAura(SPELL_PALADIN_AURA_OF_MERCY_AURA, caster->GetGUID()))
                    return true;

                return false;
            });
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_pal_cleanse_the_weak_dispel::HandleOnObjectAreaTargetSelect, EFFECT_0, TARGET_UNIT_SRC_AREA_ALLY);
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_pal_cleanse_the_weak_dispel::HandleOnObjectAreaTargetSelect, EFFECT_1, TARGET_UNIT_SRC_AREA_ALLY);
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_pal_cleanse_the_weak_dispel::HandleOnObjectAreaTargetSelect, EFFECT_2, TARGET_UNIT_SRC_AREA_ALLY);
    }
};

// 225057 - Seraphim's Blessing
class spell_pal_seraphims_blessing : public SpellScript
{
    PrepareSpellScript(spell_pal_seraphims_blessing);

    void HandleCast()
    {
        if (Unit* caster = GetCaster())
        {
            if (caster->HasAura(SPELL_PALADIN_SERAPHIMS_BLESSING_BUFF) || caster->HasAura(SPELL_PALADIN_SERAPHIMS_BLESSING_COOLDOWN))
                return;

            caster->CastSpell(caster, SPELL_PALADIN_SERAPHIMS_BLESSING_BUFF, true);
            caster->CastSpell(caster, SPELL_PALADIN_SERAPHIMS_BLESSING_COOLDOWN, true);
        }
    }

    void Register() override
    {
        OnCast += SpellCastFn(spell_pal_seraphims_blessing::HandleCast);
    }
};

// 248878 - Seraphim's Blessing Buff
class aura_pal_seraphims_blessing_buff : public AuraScript
{
    PrepareAuraScript(aura_pal_seraphims_blessing_buff);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == SPELL_PALADIN_FLASH_OF_LIGHT)
            return true;

        return false;
    }

    void HandleProc(ProcEventInfo& /*eventInfo*/)
    {
        if (Unit* caster = GetCaster())
            caster->RemoveAurasDueToSpell(GetAura()->GetId());
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_pal_seraphims_blessing_buff::CheckProc);
        OnProc += AuraProcFn(aura_pal_seraphims_blessing_buff::HandleProc);
    }
};

// 199456 - Spreading the Word
class aura_pal_spreading_the_word : public AuraScript
{
    PrepareAuraScript(aura_pal_spreading_the_word);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetSpellInfo() && (eventInfo.GetSpellInfo()->Id == SPELL_PALADIN_BLESSING_OF_FREEDOM || eventInfo.GetSpellInfo()->Id == SPELL_PALADIN_BLESSING_OF_PROTECTION))
            return true;

        return false;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (Unit* caster = GetCaster())
            if (eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == SPELL_PALADIN_BLESSING_OF_FREEDOM)
                caster->CastSpell(caster, SPELL_PALADIN_SPREADING_THE_WORD_FREEDOM, true);
            else
                caster->CastSpell(caster, SPELL_PALADIN_SPREADING_THE_WORD_PROTECTION, true);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_pal_spreading_the_word::CheckProc);
        OnProc += AuraProcFn(aura_pal_spreading_the_word::HandleProc);
    }
};

// 199507 - Spreading The Word: Protection / 199508 - Spreading The Word: Freedom
class spell_pal_spreading_the_word_all : public SpellScript
{
    PrepareSpellScript(spell_pal_spreading_the_word_all);

    void HandleOnObjectAreaTargetSelect(std::list<WorldObject*>& targets)
    {
        if (Unit* caster = GetCaster())
            targets.remove_if([caster](WorldObject* target)
            {
                if (!target->ToUnit())
                    return true;

                if (!target->ToUnit()->HasAura(SPELL_PALADIN_DEVOTION_AURA, caster->GetGUID()) &&
                    !target->ToUnit()->HasAura(SPELL_PALADIN_AURA_OF_SACRIFICE_ALLY, caster->GetGUID()) &&
                    !target->ToUnit()->HasAura(SPELL_PALADIN_AURA_OF_MERCY_AURA, caster->GetGUID()))
                    return true;

                return false;
            });
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_pal_spreading_the_word_all::HandleOnObjectAreaTargetSelect, EFFECT_0, TARGET_UNIT_SRC_AREA_ALLY);
    }
};

// 210540 - Pure of Heart Trigger
class aura_pal_pure_of_heart_trigger : public AuraScript
{
    PrepareAuraScript(aura_pal_pure_of_heart_trigger);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetHealInfo() && eventInfo.GetHealInfo()->GetHeal() > 0)
            return true;

        return false;
    }

    void HandleProc(ProcEventInfo& /*eventInfo*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetTarget();
        if (!caster || !target)
            return;

        caster->CastSpell(target, SPELL_PALADIN_PURE_OF_HEART_DISPEL, true);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_pal_pure_of_heart_trigger::CheckProc);
        OnProc += AuraProcFn(aura_pal_pure_of_heart_trigger::HandleProc);
    }
};

// 199441 - Avenging Light
class aura_pal_avening_light : public AuraScript
{
    PrepareAuraScript(aura_pal_avening_light);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == SPELL_PALADIN_HOLY_LIGHT)
            return true;

        return false;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();
        Unit* target = eventInfo.GetActionTarget();
        if (!caster || !target)
            return;

        if (eventInfo.GetHealInfo() && eventInfo.GetHealInfo()->GetHeal() > 0)
        {
            uint8 percent = sSpellMgr->GetSpellInfo(SPELL_PALADIN_AVENGING_LIGHT)->GetEffect(EFFECT_0).BasePoints;
            uint32 damage = CalculatePct(eventInfo.GetHealInfo()->GetHeal(), percent);
            caster->CastCustomSpell(SPELL_PALADIN_AVENGING_LIGHT_DAMAGE, SPELLVALUE_BASE_POINT0, damage, target, true);
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_pal_avening_light::CheckProc);
        OnProc += AuraProcFn(aura_pal_avening_light::HandleProc);
    }
};

// 199443 - Avenging Light Damage
class spell_pal_avenging_light_damage : public SpellScript
{
    PrepareSpellScript(spell_pal_avenging_light_damage);

    void HandlePrepare()
    {
        if (Unit* target = GetExplTargetUnit())
            mainTarget = target->GetGUID();
    }

    void HandleOnObjectAreaTargetSelect(std::list<WorldObject*>& targets)
    {
        if (Unit* caster = GetCaster())
            if (mainTarget != ObjectGuid::Empty)
            {
                Unit* currentTarget = ObjectAccessor::GetUnit(*caster, mainTarget);
                if (currentTarget)
                {
                    targets.remove_if([caster, currentTarget](WorldObject* target)
                    {
                        if (!target->ToUnit())
                            return true;

                        if (currentTarget->GetDistance(target->GetPosition()) > 12.f)
                            return true;

                        return false;
                    });
                }
            }
            else
                targets.clear();
    }

    void Register() override
    {
        OnPrepare += SpellOnPrepareFn(spell_pal_avenging_light_damage::HandlePrepare);
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_pal_avenging_light_damage::HandleOnObjectAreaTargetSelect, EFFECT_0, TARGET_UNIT_DEST_AREA_ENEMY);
    }

private:
    ObjectGuid mainTarget;
};

void AddSC_paladin_spell_scripts()
{
    new spell_pal_bastion_of_light();
    new spell_pal_blinding_light();
    new spell_pal_holy_prism();
    new spell_pal_holy_prism_effect();
    new spell_pal_holy_prism_visual();
    new spell_pal_judgement_of_the_pure();
    new spell_pal_lights_hammer();
    new spell_pal_lights_hammer_tick();
    new spell_pal_light_of_dawn();
    new spell_pal_light_of_dawn_trigger();

    RegisterSpellScript(spell_pal_hand_of_sacrifice);
    RegisterSpellScript(spell_pal_holy_shock);
    RegisterSpellScript(spell_pal_templar_s_verdict);
    RegisterSpellScript(spell_pal_seraphim);
    RegisterSpellScript(spell_pal_divine_steed);
    RegisterSpellScript(spell_pal_divine_shield);
    RegisterSpellScript(spell_pal_activate_forbearance);
    RegisterSpellScript(spell_pal_word_of_glory);
    RegisterSpellScript(spell_pal_justicars_vengeance);
    RegisterSpellScript(spell_pal_judgment);
    RegisterSpellScript(spell_pal_grand_crusader);
    RegisterSpellScript(spell_pal_avengers_shield);
    RegisterSpellScript(spell_pal_shield_of_the_righteous);
    RegisterSpellScript(spell_pal_light_of_the_protector);
    RegisterSpellScript(spell_pal_flash_of_light);
    RegisterSpellScript(spell_pal_crusader_strike);
    RegisterSpellScript(spell_pal_inquisition);
    RegisterSpellScript(spell_pal_wake_of_ashes);
	RegisterSpellScript(aura_pal_fist_of_fury);
    RegisterSpellScript(spell_pal_infusion_of_light);
    RegisterSpellScript(spell_pal_eye_for_an_eye);
    RegisterSpellScript(spell_pal_shield_of_vengeance);
    RegisterSpellScript(spell_pal_the_fire_of_justice);
    RegisterSpellScript(spell_pal_ardent_defender);
    RegisterSpellScript(spell_pal_crusade);
    RegisterSpellAndAuraScriptPair(spell_pal_consecration, aura_pal_consecration);
    RegisterSpellScript(spell_pal_aura_of_sacrifice_ally);
    RegisterSpellScript(spell_pal_art_of_war);
    RegisterSpellScript(spell_pal_proc_from_holy_power_consumption);
    RegisterSpellScript(spell_pal_righteous_verdict);
    RegisterSpellScript(spell_pal_awakening);
	RegisterSpellScript(aura_pal_devotion_aura);
	RegisterSpellScript(aura_pal_blinding_light);
	RegisterSpellScript(aura_pal_retribution);
	RegisterSpellScript(aura_pal_retribution_aura);
	RegisterSpellScript(spell_pal_wake_of_the_ashes);
    RegisterSpellScript(aura_pal_judgment_of_light);
	RegisterSpellScript(spell_pala_aura_of_mercy);
	RegisterSpellScript(aura_pal_zeal);
	RegisterSpellScript(aura_pal_zeal_aura);
    RegisterSpellScript(aura_pal_avengin_crusader);
    RegisterSpellScript(spell_pal_avengin_crusader_heal);
	RegisterSpellScript(aura_pal_greater_blessing_of_wisdom);
	RegisterSpellAndAuraScriptPair(spell_pal_blessing_of_proteccion, aura_pal_blessing_of_proteccion);
	RegisterSpellScript(aura_pal_blessing_of_freedom);
	RegisterSpellScript(aura_pal_blessing_of_sanctuary);
	RegisterSpellScript(aura_pal_divine_punisher);
	RegisterSpellScript(aura_pal_divine_purpose_holy);
    RegisterSpellScript(aura_pal_lights_grace);
    RegisterSpellScript(aura_pal_hallowed_ground);
	RegisterSpellScript(spell_pal_arcing_light);
    RegisterSpellScript(spell_pal_beacon_of_virtude);
    RegisterSpellScript(spell_pal_greater_blessing_of_wisdom);
	RegisterSpellScript(aura_pal_guarded_by_the_light);
	RegisterSpellScript(aura_pal_divine_favor);
	RegisterSpellScript(aura_pal_darkest_before_the_dawn);
	RegisterSpellScript(aura_pal_darkest_before_the_dawn_buff);
    RegisterSpellScript(spell_pal_lawbringer_damage);
    RegisterSpellScript(aura_pal_law_and_order);
    RegisterSpellScript(aura_pal_hand_of_hidrance_slow);
    RegisterSpellScript(aura_steed_of_glory);
	RegisterSpellScript(spell_pal_hammer_of_reckoning);
	RegisterSpellScript(aura_pal_reckoning);
	RegisterSpellScript(aura_pal_luminescence);
	RegisterSpellScript(spell_pal_luminescence_heal);
	RegisterSpellScript(aura_pal_vengeance_aura);
    RegisterSpellScript(aura_judgment_aura);
    RegisterSpellScript(spell_pal_divine_steed_mount);
    RegisterSpellScript(aura_pal_avenging_wrath);
    RegisterSpellAndAuraScriptPair(spell_pal_beacon_of_light, aura_pal_beacon_of_light);
    RegisterSpellScript(aura_pal_beacon_of_light_proc);
    RegisterSpellScript(aura_pal_avenger_of_valor_proc);
    RegisterSpellScript(aura_pal_ultimate_sacrifice);
    RegisterSpellScript(spell_pal_blessing_of_sanctuary); 
    RegisterSpellScript(aura_pal_divine_judgment_aura);
    RegisterSpellScript(aura_pal_divine_judgment);
    RegisterSpellScript(spell_divine_storm_damage);
    RegisterSpellScript(spell_pal_light_of_the_martyr);
    RegisterSpellScript(aura_pal_light_of_the_martyr);
    RegisterSpellScript(spell_pal_holy_shield);
    RegisterSpellScript(aura_pal_last_defender);
    RegisterSpellScript(spell_pal_greater_blessing_of_kings);
    RegisterSpellScript(aura_fist_of_fury_protection);
    RegisterSpellScript(spell_pal_cleanse);
    RegisterSpellScript(spell_pal_cleanse_the_weak_dispel);
    RegisterSpellScript(spell_pal_seraphims_blessing);
    RegisterSpellScript(aura_pal_seraphims_blessing_buff);
    RegisterSpellScript(aura_pal_spreading_the_word);
    RegisterSpellScript(spell_pal_spreading_the_word_all);
    RegisterSpellScript(aura_pal_pure_of_heart_trigger);
    RegisterSpellScript(aura_pal_avening_light);
    RegisterSpellScript(spell_pal_avenging_light_damage);

    // NPC Scripts
    RegisterCreatureAI(npc_pal_lights_hammer);

    // Area Trigger scripts
    RegisterAreaTriggerAI(at_pal_aura_of_sacrifice);
	RegisterAreaTriggerAI(at_pal_aura_of_devotion);
	RegisterAreaTriggerAI(at_pal_consegration);
    RegisterAreaTriggerAI(at_pal_steed_of_glory);
    RegisterAreaTriggerAI(at_pal_last_defender_dps);
    RegisterAreaTriggerAI(at_pal_seraphims_blessing);
    RegisterAreaTriggerAI(at_pal_pure_of_heart);

    // Playerscript
	new paladin_playerscript();
}
