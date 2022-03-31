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
 * Scripts for spells with SPELLFAMILY_PRIEST and SPELLFAMILY_GENERIC spells used by priest players.
 * Ordered alphabetically using scriptname.
 * Scriptnames of files in this file should be prefixed with "spell_pri_".
 */

#include "AreaTrigger.h"
#include "AreaTriggerAI.h"
#include "Creature.h"
#include "CreatureAI.h"
#include "GridNotifiers.h"
#include "Player.h"
#include "ScriptMgr.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"
#include "SpellMgr.h"
#include "TemporarySummon.h"
#include "SpellHistory.h"
#include "Battleground.h"
#include "AreaTrigger.h"
#include "Containers.h"

enum PriestSpells
{
    SPELL_PRIEST_2P_S12_HEAL                        = 33333,
    SPELL_PRIEST_2P_S12_SHADOW                      = 92711,
    SPELL_PRIEST_4P_S12_HEAL                        = 131566,
    SPELL_PRIEST_4P_S12_SHADOW                      = 131556,
    SPELL_PRIEST_ABSOLUTION                         = 33167,
    SPELL_PRIEST_ANGELIC_FEATHER_AREATRIGGER        = 158624,
    SPELL_PRIEST_ANGELIC_FEATHER_AURA               = 121557,
    SPELL_PRIEST_ANGELIC_FEATHER_TRIGGER            = 121536,
    SPELL_PRIEST_ARCHANGEL                          = 81700,
    SPELL_PRIEST_ATONEMENT                          = 81749,
    SPELL_PRIEST_ATONEMENT_AURA                     = 194384,
    SPELL_PRIEST_ATONEMENT_HEAL                     = 81751,
    SPELL_PRIEST_BODY_AND_SOUL_AURA                 = 64129,
    SPELL_PRIEST_BODY_AND_SOUL_SPEED                = 65081,
    SPELL_PRIEST_CENSURE                            = 200199,
    SPELL_PRIEST_CONTRITION                         = 197419,
    SPELL_PRIEST_CONTRITION_HEAL                    = 270501,
    SPELL_PRIEST_CURE_DISEASE                       = 528,
    SPELL_PRIEST_DEVOURING_PLAGUE                   = 2944,
    SPELL_PRIEST_DEVOURING_PLAGUE_HEAL              = 127626,
    SPELL_PRIEST_DARK_ARCHANGEL_BUFF                = 197874,
    SPELL_PRIEST_DISPEL_MAGIC_FRIENDLY              = 97690,
    SPELL_PRIEST_DISPEL_MAGIC_HOSTILE               = 97691,
    SPELL_PRIEST_DISPERSION_SPRINT                  = 129960,
    SPELL_PRIEST_DIVINE_AEGIS                       = 47753,
    SPELL_PRIEST_DIVINE_INSIGHT_DISCIPLINE          = 123266,
    SPELL_PRIEST_DIVINE_INSIGHT_HOLY                = 123267,
    SPELL_PRIEST_DIVINE_INSIGHT_TALENT              = 109175,
    SPELL_PRIEST_DIVINE_STAR                        = 110744,
    SPELL_PRIEST_DIVINE_STAR_DAMAGE                 = 122128,
    SPELL_PRIEST_DIVINE_STAR_HEAL                   = 110745,
    SPELL_PRIEST_DIVINE_TOUCH                       = 63544,
    SPELL_PRIEST_ECHO_OF_LIGHT                      = 77485,
    SPELL_PRIEST_ECHO_OF_LIGHT_HEAL                 = 77489,
    SPELL_PRIEST_EMPOWERED_RENEW                    = 63544,
    SPELL_PRIEST_EVANGELISM_AURA                    = 81662,
    SPELL_PRIEST_EVANGELISM_STACK                   = 81661,
    SPELL_PRIEST_FOCUSED_WILL_BUFF                  = 45242,
    SPELL_PRIEST_GRACE                              = 271534,
    SPELL_PRIEST_GLYPH_OF_CIRCLE_OF_HEALING         = 55675,
    SPELL_PRIEST_GLYPH_OF_DISPEL_MAGIC              = 55677,
    SPELL_PRIEST_GLYPH_OF_DISPEL_MAGIC_HEAL         = 56131,
    SPELL_PRIEST_GLYPH_OF_LIGHTWELL                 = 55673,
    SPELL_PRIEST_GLYPH_OF_PRAYER_OF_HEALING_HEAL    = 56161,
    SPELL_PRIEST_GLYPH_OF_SHADOW                    = 107906,
    SPELL_PRIEST_GUARDIAN_SPIRIT_AURA               = 47788,
    SPELL_PRIEST_GUARDIAN_SPIRIT_HEAL               = 48153,
    SPELL_PRIEST_HALO_DAMAGE                        = 120696,
    SPELL_PRIEST_HALO_HEAL                          = 120692,
    SPELL_PRIEST_HOLY_FIRE                          = 14914,
    SPELL_PRIEST_HOLY_SPARK                         = 131567,
    SPELL_PRIEST_HOLY_WORD_CHASTISE                 = 88625,
    SPELL_PRIEST_HOLY_WORD_CHASTISE_STUN            = 200200,
    SPELL_PRIEST_HOLY_WORD_SANCTIFY                 = 34861,
    SPELL_PRIEST_HOLY_WORD_SANCTUARY_AREA           = 88685,
    SPELL_PRIEST_HOLY_WORD_SANCTUARY_HEAL           = 88686,
    SPELL_PRIEST_HOLY_WORD_SERENITY                 = 2050,
    SPELL_PRIEST_INNER_FIRE                         = 588,
    SPELL_PRIEST_INNER_FOCUS                        = 196773,
    SPELL_PRIEST_INNER_WILL                         = 73413,
    SPELL_PRIEST_ITEM_EFFICIENCY                    = 37595,
    SPELL_PRIEST_LEAP_OF_FAITH                      = 73325,
    SPELL_PRIEST_LEAP_OF_FAITH_EFFECT               = 92832,
    SPELL_PRIEST_LEAP_OF_FAITH_EFFECT_TRIGGER       = 92833,
    SPELL_PRIEST_LEAP_OF_FAITH_GLYPH                = 119850,
    SPELL_PRIEST_LEAP_OF_FAITH_JUMP                 = 110726,
    SPELL_PRIEST_LEAP_OF_FAITH_TRIGGERED            = 92572,
    SPELL_PRIEST_LEVITATE                           = 111758,
    SPELL_PRIEST_LEVITATE_AURA                      = 111759,
    SPELL_PRIEST_LEVITATE_TRIGGERED                 = 111758,
    SPELL_PRIEST_LIGHTSPRING_RENEW                  = 126154,
    SPELL_PRIEST_LIGHTWELL_CHARGES                  = 59907,
    SPELL_PRIEST_LINGERING_INSANITY                 = 197937,
    SPELL_PRIEST_MANA_LEECH_PROC                    = 34650,
    SPELL_PRIEST_MASOCHISM                          = 193063,
    SPELL_PRIEST_MASOCHISM_HEAL                     = 193065,
    SPELL_PRIEST_MIND_BLAST                         = 8092,
    SPELL_PRIEST_MIND_BOMB                          = 205369,
    SPELL_PRIEST_MIND_BOMB_STUN                     = 226943,
    SPELL_PRIEST_MIND_SEAR_INSANITY                 = 208232,
    SPELL_PRIEST_MISERY                             = 238558,
    SPELL_PRIEST_NPC_PSYFIEND                       = 59190,
    SPELL_PRIEST_NPC_SHADOWY_APPARITION             = 147193,
    SPELL_PRIEST_NPC_VOID_TENDRILS                  = 65282,
    SPELL_PRIEST_PENANCE                            = 47540,
    SPELL_PRIEST_PENANCE_DAMAGE                     = 47666,
    SPELL_PRIEST_PENANCE_HEAL                       = 47750,
    SPELL_PRIEST_PENANCE_TARGET_ALLY                = 47757,
    SPELL_PRIEST_PENANCE_TARGET_ENEMY               = 47758,
    SPELL_PRIEST_PHANTASM_AURA                      = 108942,
    SPELL_PRIEST_PHANTASM_PROC                      = 114239,
    SPELL_PRIEST_POWER_OF_THE_DARK_SIDE_AURA        = 198069,
    SPELL_PRIEST_POWER_OF_THE_DARK_SIDE_MARKER      = 225795,
    SPELL_PRIEST_PIETY                              = 197034,
    SPELL_PRIEST_POWER_WORD_BARRIER_BUFF            = 81782,
    SPELL_PRIEST_POWER_WORD_BARRIER_VISUAL          = 146810,
    SPELL_PRIEST_POWER_WORD_FORTITUDE               = 21562,
    SPELL_PRIEST_POWER_WORD_SHIELD                  = 17,
    SPELL_PRIEST_PRAYER_OF_MENDING                  = 33076,
    SPELL_PRIEST_PRAYER_OF_MENDING_BUFF             = 41635,
    SPELL_PRIEST_PRAYER_OF_MENDING_HEAL             = 33110,
    SPELL_PRIEST_PRAYER_OF_MENDING_RADIUS           = 123262,
    SPELL_PRIEST_PRAYER_OF_MENDING_TARGET_SELECTOR  = 155793,
    SPELL_PRIEST_POWER_WORD_RADIANCE                = 194509,
    SPELL_PRIEST_RAPID_RENEWAL_AURA                 = 95649,
    SPELL_PRIEST_PURGE_THE_WICKED                   = 204197,
    SPELL_PRIEST_PURGE_THE_WICKED_DOT               = 204213,
    SPELL_PRIEST_PURGE_THE_WICKED_SEARCHER          = 204215,
    SPELL_PRIEST_RAPTURE                            = 47536,
    SPELL_PRIEST_RAPTURE_ENERGIZE                   = 47755,
    SPELL_PRIEST_REFLECTIVE_SHIELD_R1               = 33201,
    SPELL_PRIEST_REFLECTIVE_SHIELD_TRIGGERED        = 33619,
    SPELL_PRIEST_SHADOWFORM                         = 165767,
    SPELL_PRIEST_SHADOWFORM_STANCE                  = 232698,
    SPELL_PRIEST_SHADOWFORM_VISUAL_WITHOUT_GLYPH    = 107903,
    SPELL_PRIEST_SHADOWFORM_VISUAL_WITH_GLYPH       = 107904,
    SPELL_PRIEST_SHADOW_MEND_AURA                   = 187464,
    SPELL_PRIEST_SHADOW_MEND_DAMAGE                 = 186439,
    SPELL_PRIEST_SHADOW_MEND_HEAL                   = 186263,
    SPELL_PRIEST_SHADOW_WORD_DEATH                  = 32379,
    SPELL_PRIEST_SHADOW_WORD_DEATH_ENERGIZE_KILL    = 190714,
    SPELL_PRIEST_SHADOW_WORD_INSANITY_ALLOWING_CAST = 130733,
    SPELL_PRIEST_SHADOW_WORD_INSANITY_DAMAGE        = 129249,
    SPELL_PRIEST_SHADOW_WORD_PAIN                   = 589,
    SPELL_PRIEST_SIN_AND_PUNISHMENT                 = 87204,
    SPELL_PRIEST_SMITE_ABSORB                       = 208771,
    SPELL_PRIEST_SMITE_AURA                         = 208772,
    SPELL_PRIEST_SOUL_OF_DIAMOND                    = 96219,
    SPELL_PRIEST_SPECTRAL_GUISE_CHARGES             = 119030,
    SPELL_PRIEST_SPIRIT_OF_REDEMPTION_FORM          = 27795,
    SPELL_PRIEST_SPIRIT_OF_REDEMPTION_IMMUNITY      = 62371,
    SPELL_PRIEST_SPIRIT_OF_REDEMPTION_SHAPESHIFT    = 27827,
    SPELL_PRIEST_SPIRIT_OF_REDEMPTION_UNTRANS_HERO  = 25100,
    SPELL_PRIEST_SPIRIT_SHELL_ABSORPTION            = 114908,
    SPELL_PRIEST_SPIRIT_SHELL_AURA                  = 109964,
    SPELL_PRIEST_STRENGTH_OF_SOUL                   = 197535,
    SPELL_PRIEST_STRENGTH_OF_SOUL_AURA              = 197548,
    SPELL_PRIEST_SURGE_OF_DARKNESS                  = 87160,
    SPELL_PRIEST_SURGE_OF_LIGHT                     = 109186,
    SPELL_PRIEST_T9_HEALING_2P                      = 67201,
    SPELL_PRIEST_TRAIN_OF_THOUGHT                   = 92297,
    SPELL_PRIEST_TWIN_DISCIPLINES_RANK_1            = 47586,
    SPELL_PRIEST_TWIST_OF_FATE_SHADOW               = 109142,
    SPELL_PRIEST_VAMPIRIC_EMBRACE_HEAL              = 199397,
    SPELL_PRIEST_VAMPIRIC_TOUCH                     = 34914,
    SPELL_PRIEST_VAMPIRIC_TOUCH_DISPEL              = 201146, // Fear
    SPELL_PRIEST_VOIDFORM                           = 228264,
    SPELL_PRIEST_VOIDFORM_BUFFS                     = 194249,
    SPELL_PRIEST_VOIDFORM_TENTACLES                 = 210196,
    SPELL_PRIEST_VOID_BOLT                          = 205448,
    SPELL_PRIEST_VOID_BOLT_DURATION                 = 231688,
    SPELL_PRIEST_VOID_ERUPTION                      = 228260,
    SPELL_PRIEST_VOID_ERUPTION_DAMAGE               = 228360,
    SPELL_PRIEST_VOID_SHIFT                         = 108968,
    SPELL_PRIEST_VOID_SHIFT_EFFECT                  = 118594,
    SPELL_PRIEST_VOID_TENDRILS_SUMMON               = 127665,
    SPELL_PRIEST_VOID_TENDRILS_TRIGGER              = 127665,
    SPELL_PRIEST_VOID_TORRENT_PREVENT_REGEN         = 262173,
    SPELL_PRIEST_WEAKENED_SOUL                      = 6788,
    SPELL_SHADOW_PRIEST_BASE_AURA                   = 137033,
	SPELL_PRIEST_FLASH_HEAL							= 2061,
	SPELL_PRIEST_HEAL								= 2060,
	SPELL_PRIEST_SMITE								= 585,
	SPELL_PRIEST_LIGHT_OF_THE_NAARU					= 196985,
	SPELL_PRIEST_HOLY_WORD_SALVATION				= 265202,
	SPELL_PRIEST_HOLY_FIRE_AURA						= 231687,
	SPELL_PRIEST_HOLY_FIRE_PROC						= 231403,
	SPELL_PRIEST_HOLY_NOVA							= 132157,
	SPELL_PRIEST_PSHYSHIC_SCREAM					= 8122,
    SPELL_PRIEST_RENEW                              = 139,
    SPELL_PRIEST_TRAIL_OF_LIGHT                     = 200128,
    SPELL_PRIEST_TRAIL_OF_LIGHT_HEAL                = 234946,
    SPELL_PRIEST_BENEDICTION                        = 193157,
    SPELL_PRIEST_APOTHEOSIS                         = 200183,
	SPELL_PRIEST_MANIA								= 193173,
    SPELL_PRIEST_MANIA_SPEED                        = 195290,
    SPELL_PRIEST_VOIDFORM_ACTIVATION                = 218413,
	SPELL_PRIEST_SHADOWY_INSIGHT					= 124430,
	SPELL_PRIEST_LINGERING_INSANITY_AURA			= 199849,
	SPELL_PRIEST_SINS_OF_THE_MANY					= 280398,
    SPELL_PRIEST_SHIELD_DISCIPLINE                  = 197045,
	SPELL_PRIEST_PERSEVERANCE                       = 235189,
    SPELL_PRIEST_COSMIC_RIPPLE                      = 238136,
    SPELL_PRIEST_COSMIC_RIPPLE_HEAL                 = 243241,
    SPELL_PRIEST_GUARDIAN_ANGEL                     = 200209,
    SPELL_PRIEST_ENDURING_RENEWAL                   = 200153,
    SPELL_PRIEST_EVANGELISM                         = 246287,
    SPELL_PRIEST_INNER_FOCUS_CRIT                   = 196762,
    SPELL_PRIEST_SURGE_OF_LIGHT_BUFF                = 114255,
    SPELL_PRIEST_LEGACY_OF_THE_VOID                 = 193225,
    SPELL_PRIEST_HOLY_WORD_CHASTISE_INCAPACITE      = 200196,
    SPELL_PRIEST_SEARING_LIGHT                      = 215768,
    SPELL_PRIEST_PURE_SHADOW                        = 199131,
    SPELL_PRIEST_MIND_TRAUMA                        = 199445,
    SPELL_PRIEST_MIND_TRAUMA_CASTER                 = 247776,
	SPELL_PRIEST_MIND_TRAUMA_TARGET                 = 247777,
    SPELL_PRIEST_MIND_FLAY                          = 15407,
    SPELL_PRIEST_PSYCHIC_LINK                       = 199484,
    SPELL_PRIEST_PSYCHIC_LINK_DAMAGE                = 199486,
	SPELL_PRIEST_SHADOW_COVENANT_ABSORTION			= 219521,
    SPELL_PRIEST_RAY_OF_HOPE_HEAL                   = 197336,
    SPELL_PRIEST_RAY_OF_HOPE_DAMAGE                 = 197341,
	SPELL_PRIEST_PURIFIED_RESOLVE					= 196439,
	SPELL_PRIEST_PURIFIED_RESOLVE_SHIELD			= 196440,
	SPELL_PRIEST_SURRENDER_TO_MADNESS				= 193223,
	SPELL_PRIEST_SURRENDER_TO_MADNESS_DAMAGE		= 263501,
	SPELL_PRIEST_SURRENDERED_TO_MADNESS				= 263406,
	SPELL_PRIEST_DARK_ASCENSION						= 280711,
	SPELL_PRIEST_DARK_ASCENSION_DAMAGE				= 280800,
    SPELL_PRIEST_SUSTAINED_SANITY                   = 281574,
    SPELL_PRIEST_PSYFIEND_SUMMON                    = 199824,
    SPELL_PRIEST_SPIRIT_OF_REDEMPTION_EFFECTS       = 27792,
    SPELL_PRIEST_PRAYERFUL_LITANY_POWER             = 275602,
    SPELL_PRIEST_SPITEFUL_APPARITIONS_POWER         = 277682,
    SPELL_PRIEST_CHORUS_OF_INSANITY_POWER           = 278661,
    SPELL_PRIEST_CHORUS_OF_INSANITY_BUFF            = 279572,
    SPELL_PRIEST_WEAL_AND_WOE_POWER                 = 273307,
    SPELL_PRIEST_WEAL                               = 273310,
    SPELL_PRIEST_WOE                                = 273312,
    SPELL_HOLY_CONCENTRATION_AURA                   = 221661,
    SPELL_HOLY_CONCENTRATION_BUFF                   = 221660, 
    SPELL_PRIEST_MIND_SEAR_DAMAGE                   = 49821,
    SPELL_PRIEST_SMITE_RANK_2                       = 231682,
    SPELL_PRIEST_TRINITY                            = 214205,
    SPELL_PRIEST_VOID_SHIELD                        = 280749,
    SPELL_PRIEST_MOMENT_OF_REPOSE_POWER             = 272775,
    SPELL_PRIEST_MOMENT_OF_REPOSE_HEAL              = 272776,
    SPELL_PRIEST_POWER_WORD_SOLACE                  = 129250,
    SPELL_PRIEST_POWER_WORD_SOLACE_ENERGIZE         = 129253,
    SPELL_PRIEST_SANCTUM_POWER                      = 274366,
    SPELL_PRIEST_SANCTUM_SHIELD                     = 274369,
    SPELL_PRIEST_PREMONITION                        = 209780,
    SPELL_PRIEST_PREMONITION_DAMAGE                 = 209885,
    SPELL_PRIEST_EVERLASTING_LIGHT                  = 277681,
    SPELL_PRIEST_SACRED_FLAME_POWER                 = 278655,
    SPELL_PRIEST_SACRED_FLAME_ENERGIZE              = 279434,
    SPELL_PRIST_GIFT_OF_FORGIVENESS                 = 277680,
};

enum PriestSpellIcons
{
    PRIEST_ICON_ID_BORROWED_TIME                    = 2899,
    PRIEST_ICON_ID_DIVINE_TOUCH_TALENT              = 3021,
    PRIEST_ICON_ID_PAIN_AND_SUFFERING               = 2874
};

enum MiscSpells
{
    SPELL_GEN_REPLENISHMENT                         = 57669
};

class priest_playerscript : PlayerScript
{
public:
    priest_playerscript() : PlayerScript("priest_playerscript") {}

    void OnSuccessfulSpellCast(Player* player, Spell* spell) override
    {
        if (!player || !spell)
            return;

        // Holy Priest
        if (player->GetSpecializationId() == TALENT_SPEC_PRIEST_HOLY)
        {
            // Renew doesn't work with spells hooks (Maybe due to instant cast?)
            if (spell->GetSpellInfo()->Id == SPELL_PRIEST_RENEW)
                player->GetSpellHistory()->ModifyCooldown(SPELL_PRIEST_HOLY_WORD_SANCTIFY, -2 * IN_MILLISECONDS);
        }
    }

    void OnChanneledSpellSuccessfulCast(Player* player, Spell* spell) override
    {
        if (!player || !spell)
            return;

        // Shadow Priest
        if (player->GetSpecializationId() == TALENT_SPEC_PRIEST_SHADOW)
        {
            if (player->HasAura(SPELL_PRIEST_MIND_TRAUMA) && spell->GetSpellInfo() && spell->GetSpellInfo()->Id == SPELL_PRIEST_MIND_FLAY)
            {
                bool apply = false;
                Unit* target = spell->m_targets.GetUnitTarget();
                if (target)
                {
                    Aura* mindTraumaTarget = target->GetAura(SPELL_PRIEST_MIND_TRAUMA_TARGET, player->GetGUID());
                    if (!mindTraumaTarget || (mindTraumaTarget && mindTraumaTarget->GetStackAmount() < 4))
                    {
                        player->CastSpell(target, SPELL_PRIEST_MIND_TRAUMA_TARGET, true);
                        apply = true;
                    }
                    if (apply)
                        player->CastSpell(player, SPELL_PRIEST_MIND_TRAUMA_CASTER, true);
                }
            }
        }
    }

    void OnUpdate(Player* player, uint32 diff) override
    {
        if (!player)
            return;

        if (timer <= diff)
        {
            timer = 500;

            // Holy Priest
            if (player->GetSpecializationId() == TALENT_SPEC_PRIEST_HOLY)
            {
                if (player->HasAura(SPELL_PRIEST_COSMIC_RIPPLE))
                {
                    if (player->GetSpellHistory()->IsReady(sSpellMgr->GetSpellInfo(SPELL_PRIEST_HOLY_WORD_SERENITY)) && player->Variables.GetValue("CosmicRippleSerenity", false))
                    {
                        player->Variables.Set("CosmicRippleSerenity", false);
                        player->CastSpell(player, SPELL_PRIEST_COSMIC_RIPPLE_HEAL, true);
                    }
                    if (player->GetSpellHistory()->IsReady(sSpellMgr->GetSpellInfo(SPELL_PRIEST_HOLY_WORD_SANCTIFY)) && player->Variables.GetValue("CosmicRippleSantify", false))
                    {
                        player->Variables.Set("CosmicRippleSantify", false);
                        player->CastSpell(player, SPELL_PRIEST_COSMIC_RIPPLE_HEAL, true);
                    }
                }
            }
        }
        else
            timer -= diff;        
    }

	void OnModifyPower(Player* player, Powers power, int32 oldValue, int32& newValue, bool regen, bool after) override
	{ 
		if (!player || !after)
			return;

		// Shadow Priest
		if (player->GetSpecializationId() ==TALENT_SPEC_PRIEST_SHADOW)
		{
            uint8 treshold = (player->HasAura(SPELL_PRIEST_LEGACY_OF_THE_VOID)) ? 60 : 90;
			if (power == POWER_INSANITY && player->GetPower(power) / 100 < treshold)
				player->RemoveAura(SPELL_PRIEST_VOIDFORM_ACTIVATION);

			if (player->HasAura(SPELL_PRIEST_MANIA) && power == POWER_INSANITY && newValue != oldValue)
			{
				float speedPercent = player->GetPower(POWER_INSANITY) / 100;
				uint8 maxSpeed = sSpellMgr->GetSpellInfo(SPELL_PRIEST_MANIA)->GetEffect(EFFECT_0).BasePoints;
				player->RemoveAura(SPELL_PRIEST_MANIA_SPEED);
                player->CastSpell(player, SPELL_PRIEST_MANIA_SPEED, CastSpellExtraArgs(true).AddSpellBP0(CalculatePct(maxSpeed, speedPercent)));
			}
		}
	}

	void OnSummonCreatureDealsDamage(Player* player, Unit* creature, Unit* victim, int32 damage) override
	{
		if (!player || !victim || !creature)
			return;

		// Shadowfiend
		if (creature->GetEntry() == ENTRY_SHADOWFIEND)
		{
			if (player->GetSpecializationId() == TALENT_SPEC_PRIEST_SHADOW)
				player->ModifyPower(POWER_INSANITY, 300);
		}
		// Mindbender
		else if (creature->GetEntry() == ENTRY_MINDBENDER)
		{
			if (player->GetSpecializationId() == TALENT_SPEC_PRIEST_SHADOW)
				player->ModifyPower(POWER_INSANITY, 600);
			else
				player->ModifyPower(POWER_MANA, CalculatePct(player->GetMaxPower(POWER_MANA), 0.5f));
		}
	}

    void OnDealDamage(Player* player, Unit* /*target*/, uint32 damage, SpellSchoolMask /*schoolMask*/) override
    {
        if (player && player->GetClass() == CLASS_PRIEST && player->GetSpecializationId() == TALENT_SPEC_PRIEST_SHADOW)
        {
            if (player->HasAura(SPELL_PRIEST_VOID_SHIELD, player->GetGUID()))
            {
                if (Aura* aura = player->GetAura(SPELL_PRIEST_POWER_WORD_SHIELD, player->GetGUID()))
                {
                    if (player->Variables.Exist("SHIELD_ABSORBED_BASE"))
                    {
                        if (AuraEffect* effect = aura->GetEffect(EFFECT_0))
                        {
                            if (SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(SPELL_PRIEST_VOID_SHIELD))
                            {
                                int32 absorbedBase = player->Variables.GetValue<int32>("SHIELD_ABSORBED_BASE");
                                int32 pctDamage = CalculatePct(damage, spellInfo->GetEffect(EFFECT_0).BasePoints);
                                int32 amount = 0;
                                if(player->Variables.Exist("SHIELD_ABSORBED"))
                                    amount = player->Variables.GetValue<int32>("SHIELD_ABSORBED");

                                if (!player->Variables.Exist("SHIELD_ABSORBED_REMANENT"))
                                {
                                    if (absorbedBase <= (absorbedBase - amount + pctDamage))
                                        player->Variables.Set<int32>("SHIELD_ABSORBED_REMANENT", absorbedBase);
                                    else
                                        player->Variables.Set<int32>("SHIELD_ABSORBED_REMANENT", absorbedBase - amount + pctDamage);
                                }                        
                                else
                                {
                                    int32 remanentAbsorb = player->Variables.GetValue<int32>("SHIELD_ABSORBED_REMANENT") - amount + pctDamage;
                                    if(absorbedBase <= remanentAbsorb)
                                        player->Variables.Set<int32>("SHIELD_ABSORBED_REMANENT", absorbedBase);
                                    else
                                        player->Variables.Set<int32>("SHIELD_ABSORBED_REMANENT", remanentAbsorb);
                                }     
                                
                                effect->ChangeAmount((player->Variables.GetValue<int32>("SHIELD_ABSORBED_REMANENT"))); 
                                player->Variables.Remove("SHIELD_ABSORBED");
                            }
                        }
                    }
                }
            }
        }                          
    }

    private:
        uint32 timer = 500;
};

//Last Update 8.0.1 Build 28153
// 17 - Power Word: Shield
class spell_pri_power_word_shield : public SpellScript
{
    PrepareSpellScript(spell_pri_power_word_shield);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_PRIEST_TRINITY });
    }

    void HandleBeforeHit(SpellMissInfo missInfo)
    {
        if (Unit* caster = GetCaster())
        {
            if (Unit* target = GetExplTargetUnit())
            {
                if (caster == target)
                {
                    if (caster->Variables.Exist("SHIELD_ABSORBED_BASE"))
                        caster->Variables.Remove("SHIELD_ABSORBED_BASE");

                    if (caster->Variables.Exist("SHIELD_ABSORBED"))
                        caster->Variables.Remove("SHIELD_ABSORBED");

                    if (caster->Variables.Exist("SHIELD_ABSORBED_REMANENT"))
                        caster->Variables.Remove("SHIELD_ABSORBED_REMANENT");
                }
            }
        }
    }

    void OnHit(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        if (caster->HasAura(SPELL_PRIEST_ATONEMENT))
        {
            if (!caster->HasAura(SPELL_PRIEST_TRINITY))
                caster->CastSpell(target, SPELL_PRIEST_ATONEMENT_AURA, true);
            else
            {
                if (caster->GetTargetAuraApplications(SPELL_PRIEST_ATONEMENT_AURA).size() < 3 || target->HasAura(SPELL_PRIEST_ATONEMENT_AURA, caster->GetGUID()))
                {
                    caster->CastSpell(target, SPELL_PRIEST_ATONEMENT_AURA, true);
                    if (Aura* aura = target->GetAura(SPELL_PRIEST_ATONEMENT_AURA))
                        aura->ModDuration(sSpellMgr->GetSpellInfo(SPELL_PRIEST_TRINITY)->GetEffect(EFFECT_2).BasePoints * IN_MILLISECONDS);
                }
            }
        }
    }

    void HandleAfterHit()
    {
        Unit* caster = GetCaster();
        if (!caster)
            return;
        
        if (caster->HasAura(SPELL_PRIEST_VOID_SHIELD, caster->GetGUID()))
            if (Aura* aura = caster->GetAura(SPELL_PRIEST_POWER_WORD_SHIELD, caster->GetGUID()))
                if (AuraEffect* effect = aura->GetEffect(EFFECT_0))
                    caster->Variables.Set<int32>("SHIELD_ABSORBED_BASE", effect->GetAmount());
    }

    void Register() override
    {
        BeforeHit += BeforeSpellHitFn(spell_pri_power_word_shield::HandleBeforeHit);
        OnEffectHitTarget += SpellEffectFn(spell_pri_power_word_shield::OnHit, EFFECT_0, SPELL_EFFECT_APPLY_AURA);
        AfterHit += SpellHitFn(spell_pri_power_word_shield::HandleAfterHit);
    }
};

/*
$rapture=$?a47536[${(1+$47536s1/100)}][${1}]
$shadow=$?a137033[${1.36}][${1}]
$shield=${$SP*1.54*(1+$@versadmg)*$<rapture>*$<shadow>}
*/
class aura_pri_power_word_shield : public AuraScript
{
    PrepareAuraScript(aura_pri_power_word_shield);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_PRIEST_POWER_WORD_SHIELD, SPELL_PRIEST_RAPTURE, SPELL_SHADOW_PRIEST_BASE_AURA });
    }

    void CalculateAmount(AuraEffect const* /*aurEff*/, int32& amount, bool& /*canBeRecalculated*/)
    {
        if (Unit* caster = GetCaster())
        {
            if (Player* player = caster->ToPlayer())
            {
                int32 absorbAmount = int32(1.54f * player->SpellBaseHealingBonusDone(GetSpellInfo()->GetSchoolMask()));

                if (player->HasAura(SPELL_SHADOW_PRIEST_BASE_AURA))
                    absorbAmount *= 1.29f;

                if (Aura* rapture = player->GetAura(SPELL_PRIEST_RAPTURE))
                    if (AuraEffect* eff0 = rapture->GetEffect(EFFECT_0))
                        absorbAmount += CalculatePct(absorbAmount, eff0->GetAmount());

                if (Unit* target = GetUnitOwner())
                    if(target->HasAura(SPELL_PRIEST_ATONEMENT_AURA))
                        if(caster->HasAura(SPELL_PRIEST_GRACE))
                            absorbAmount += (absorbAmount * (player->m_activePlayerData->Mastery / 100.0f));

                amount += absorbAmount;

                // Weal
                if (Aura* aura = player->GetAura(SPELL_PRIEST_WEAL))
                {
                    amount += aura->GetEffect(EFFECT_0)->GetAmount();
                    caster->RemoveAurasDueToSpell(SPELL_PRIEST_WEAL);
                }
            }
        }
    }

    void Absorb(AuraEffect* /*aurEff*/, DamageInfo & dmgInfo, uint32 & absorbAmount)
    {
        if (Unit* caster = GetCaster())
            if (dmgInfo.GetDamage() >= absorbAmount)
                if (caster->HasAura(SPELL_PRIEST_SHIELD_DISCIPLINE))
                    caster->CastSpell(caster, SPELL_PRIEST_RAPTURE_ENERGIZE, true);
    }

    void AfterAbsorb(AuraEffect* aurEff, DamageInfo& /*dmgInfo*/, uint32& absorbAmount)
    {
        if (Unit* caster = GetCaster())
        {
            if (caster->Variables.Exist("SHIELD_ABSORBED"))
                caster->Variables.Set<int32>("SHIELD_ABSORBED", absorbAmount + caster->Variables.GetValue<int32>("SHIELD_ABSORBED"));
            else
                caster->Variables.Set<int32>("SHIELD_ABSORBED", absorbAmount);
        }       
    }

    void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetTarget();
        if (!caster || !target)
            return;

        if (caster->HasAura(SPELL_PRIEST_STRENGTH_OF_SOUL))
            caster->CastSpell(target, SPELL_PRIEST_STRENGTH_OF_SOUL_AURA, true);
    }

    void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetTarget();
        if (!caster || !target)
            return;

        target->RemoveAura(SPELL_PRIEST_STRENGTH_OF_SOUL_AURA, caster->GetGUID());

        if(caster->Variables.Exist("SHIELD_ABSORBED_BASE"))
            caster->Variables.Remove("SHIELD_ABSORBED_BASE");

        if (caster->Variables.Exist("SHIELD_ABSORBED"))
            caster->Variables.Remove("SHIELD_ABSORBED");

        if (caster->Variables.Exist("SHIELD_ABSORBED_REMANENT"))
            caster->Variables.Remove("SHIELD_ABSORBED_REMANENT");
    }

    void Register() override
    {
        OnEffectAbsorb += AuraEffectAbsorbFn(aura_pri_power_word_shield::Absorb, EFFECT_0);
        AfterEffectAbsorb += AuraEffectAbsorbFn(aura_pri_power_word_shield::AfterAbsorb, EFFECT_0);
        DoEffectCalcAmount += AuraEffectCalcAmountFn(aura_pri_power_word_shield::CalculateAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
        OnEffectApply += AuraEffectApplyFn(aura_pri_power_word_shield::OnApply, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
        OnEffectRemove += AuraEffectRemoveFn(aura_pri_power_word_shield::OnRemove, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB, AURA_EFFECT_HANDLE_REAL);
    }
};

// Clarity of Will - 152118
class spell_pri_clarity_of_will : public AuraScript
{
    PrepareAuraScript(spell_pri_clarity_of_will);

    void CalculateAmount(AuraEffect const* aurEff, int32& amount, bool& /*canBeRecalculated*/)
    {
        if (Unit* caster = aurEff->GetCaster())
        {
            if (Player* player = caster->ToPlayer())
            {
                int32 absorbamount = int32(9.0f * player->SpellBaseHealingBonusDone(GetSpellInfo()->GetSchoolMask()));
                amount += absorbamount;
            }
        }
    }

    void Register() override
    {
        DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_pri_clarity_of_will::CalculateAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
    }
};

// 109142 - Twist of Fate Shadow
class aura_pri_twist_of_fate_shadow : public AuraScript
{
    PrepareAuraScript(aura_pri_twist_of_fate_shadow);

	bool CheckProc(ProcEventInfo& eventInfo)
	{
		if (Unit* target = eventInfo.GetActionTarget())
			if (eventInfo.GetDamageInfo() && eventInfo.GetDamageInfo()->GetDamage() > 0 && target->HealthBelowPct(sSpellMgr->GetSpellInfo(SPELL_PRIEST_TWIST_OF_FATE_SHADOW)->GetEffect(EFFECT_0).BasePoints))
				return true;
		return false;
	}

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_pri_twist_of_fate_shadow::CheckProc);
    }
};

// 265259 - Twist of Fate Discipline
class aura_pri_twist_of_fate_discipline : public AuraScript
{
	PrepareAuraScript(aura_pri_twist_of_fate_discipline);

	bool CheckProc(ProcEventInfo& eventInfo)
	{
		if (Unit* target = eventInfo.GetActionTarget())
			if (eventInfo.GetHealInfo() && eventInfo.GetHealInfo()->GetHeal() > 0 && target->HealthBelowPct(sSpellMgr->GetSpellInfo(SPELL_PRIEST_TWIST_OF_FATE_SHADOW)->GetEffect(EFFECT_0).BasePoints))
				return true;
		return false;
	}

	void Register() override
	{
		DoCheckProc += AuraCheckProcFn(aura_pri_twist_of_fate_discipline::CheckProc);
	}
};

// 205369 - Mind Bomb
class spell_pri_mind_bomb : public AuraScript
{
    PrepareAuraScript(spell_pri_mind_bomb);

    void HandleEffectRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetTarget();
        if (!caster || !target)
            return;

        std::list<Unit*> targets;
        target->GetAttackableUnitListInRange(targets, 8.0f);

        for (auto itr : targets)
        {
            caster->CastSpell(itr, SPELL_PRIEST_MIND_BOMB_STUN, true);
        }
    }

    void Register() override
    {
        AfterEffectRemove += AuraEffectRemoveFn(spell_pri_mind_bomb::HandleEffectRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

// Holy Word: Chastise - 88625
class spell_pri_holy_word_chastise : public SpellScript
{
    PrepareSpellScript(spell_pri_holy_word_chastise);

    void HandleOnHit(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        if (caster->HasAura(SPELL_PRIEST_CENSURE))
            caster->CastSpell(target, SPELL_PRIEST_HOLY_WORD_CHASTISE_STUN, true);
        else
            caster->CastSpell(target, SPELL_PRIEST_HOLY_WORD_CHASTISE_INCAPACITE, true);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_pri_holy_word_chastise::HandleOnHit, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

// 32546 - Binding Heal
class spell_pri_binding_heal : public SpellScript
{
    PrepareSpellScript(spell_pri_binding_heal);

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        targets.remove(GetExplTargetUnit());
        targets.remove(GetCaster());
        targets.sort(Trinity::HealthPctOrderPred());
        if (targets.size() > 1)
            targets.resize(1);
        targets.push_back(GetExplTargetUnit());
        targets.push_back(GetCaster());
    }

    void HandleAfterCast()
    {
        Unit* caster = GetCaster();
        if (!caster)
            return;

        caster->GetSpellHistory()->ModifyCooldown(SPELL_PRIEST_HOLY_WORD_SANCTIFY, -3 * IN_MILLISECONDS);
        caster->GetSpellHistory()->ReduceChargeCooldown(sSpellMgr->GetSpellInfo(SPELL_PRIEST_HOLY_WORD_SERENITY)->ChargeCategoryId, 3 * IN_MILLISECONDS);
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_pri_binding_heal::FilterTargets, EFFECT_1, TARGET_UNIT_DEST_AREA_ALLY);
        AfterCast += SpellCastFn(spell_pri_binding_heal::HandleAfterCast);
    }
};

// 596 - Prayer of Healing
class spell_pri_prayer_of_healing : public SpellScript
{
    PrepareSpellScript(spell_pri_prayer_of_healing);

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        Unit* target = (GetExplTargetUnit() ? GetExplTargetUnit() : GetCaster());
        if (target)
        {
            targets.sort(Trinity::DistanceCompareOrderPred(target));
            if (targets.size() > 5)
                targets.resize(5);

            if (Unit* caster = GetCaster())
                if (targets.size() > 0 && caster->HasAura(SPELL_PRIEST_PRAYERFUL_LITANY_POWER))
                {
                    mostInjured = target->GetGUID();
                    for (WorldObject* wo : targets)
                        if (wo)
                            if (Unit* target = wo->ToUnit())
                                if (Unit* current = ObjectAccessor::GetUnit(*caster, mostInjured))
                                    if (target->GetHealth() < current->GetHealth())
                                        mostInjured = target->GetGUID();
                }
        }
    }

    void HandleEffectHit(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        if (Aura* aura = caster->GetAura(SPELL_PRIEST_PRAYERFUL_LITANY_POWER))
            if (mostInjured == target->GetGUID())
            {
                int32 heal = GetHitHeal();
                SetHitHeal(heal + aura->GetEffect(EFFECT_0)->GetAmount());
            }
    }

    void HandleAfterCast()
    {
        Unit* caster = GetCaster();
        if (!caster)
            return;

        caster->GetSpellHistory()->ModifyCooldown(SPELL_PRIEST_HOLY_WORD_SANCTIFY, -6 * IN_MILLISECONDS);
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_pri_prayer_of_healing::FilterTargets, EFFECT_1, TARGET_UNIT_DEST_AREA_ALLY);
        OnEffectHitTarget += SpellEffectFn(spell_pri_prayer_of_healing::HandleEffectHit, EFFECT_1, SPELL_EFFECT_HEAL);
        AfterCast += SpellCastFn(spell_pri_prayer_of_healing::HandleAfterCast);
    }

private:
    ObjectGuid mostInjured;
};

// Smite - 585
class spell_pri_smite : public SpellScript
{
    PrepareSpellScript(spell_pri_smite);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_PRIEST_SMITE_RANK_2 });
    }

    void HandleHit(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        int32 dmg = GetHitDamage();

        if (caster->HasAura(SPELL_PRIEST_SMITE_RANK_2))
        {
            // Formula: $shield=${($SPS * $231682s1 / 100) * (1+ $@versadmg)}
            int32 shield = caster->GetTotalSpellPowerValue(SPELL_SCHOOL_MASK_SHADOW, false) * sSpellMgr->GetSpellInfo(SPELL_PRIEST_SMITE_RANK_2)->GetEffect(EFFECT_0).BasePoints / 100;
            caster->CastSpell(target, SPELL_PRIEST_SMITE_AURA, CastSpellExtraArgs(true).AddSpellBP0(shield));
            caster->CastSpell(caster, SPELL_PRIEST_SMITE_ABSORB, CastSpellExtraArgs(true).AddSpellBP0(shield));
        }

        // Gift of forgiveness.
        if (Player* player = caster->ToPlayer())
            if (player->GetSpecializationId() == TALENT_SPEC_PRIEST_DISCIPLINE)
                if (Aura* aura = player->GetAura(SPELL_PRIST_GIFT_OF_FORGIVENESS))
                    if (player->GetTargetAuraApplications(SPELL_PRIEST_ATONEMENT_AURA).size() >= sSpellMgr->GetSpellInfo(SPELL_PRIST_GIFT_OF_FORGIVENESS)->GetEffect(EFFECT_1).BasePoints)
                        dmg += aura->GetEffect(EFFECT_0)->GetAmount();

        SetHitDamage(dmg);

        // Woe
        caster->RemoveAurasDueToSpell(SPELL_PRIEST_WOE);
    }

	void HandleAfterHit()
	{
		Unit* caster = GetCaster();
		if (!caster)
			return;

		if (roll_chance_i(sSpellMgr->GetSpellInfo(SPELL_PRIEST_HOLY_FIRE_AURA)->GetEffect(EFFECT_0).BasePoints) && caster->HasAura(SPELL_PRIEST_HOLY_FIRE_AURA))
		{
			caster->AddAura(SPELL_PRIEST_HOLY_FIRE_PROC, caster);
			caster->GetSpellHistory()->ResetCooldown(SPELL_PRIEST_HOLY_FIRE, true);
		}

		if (caster->HasAura(SPELL_PRIEST_SEARING_LIGHT))
			caster->GetSpellHistory()->ModifyCooldown(SPELL_PRIEST_PENANCE, -1s);
	}

    void CalcCritChance(Unit const* /*victim*/, float& chance)
    {
        if (Unit* caster = GetCaster())
            if (caster->HasAura(SPELL_PRIEST_INNER_FOCUS_CRIT))
                chance = 100;
    }

    void HandleAfterCast()
    {
        if (Unit* caster = GetCaster())
            caster->RemoveAurasDueToSpell(SPELL_PRIEST_INNER_FOCUS_CRIT);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_pri_smite::HandleHit, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
		AfterHit += SpellHitFn(spell_pri_smite::HandleAfterHit);
        OnCalcCritChance += SpellOnCalcCritChanceFn(spell_pri_smite::CalcCritChance);
        AfterCast += SpellCastFn(spell_pri_smite::HandleAfterCast);
    }
};
//7.3.2.25549 END

// 194249 - Voidform
class spell_pri_voidform : public SpellScriptLoader
{
public:
    spell_pri_voidform() : SpellScriptLoader("spell_pri_voidform") {}

    class spell_pri_voidform_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_pri_voidform_AuraScript);

        void HandleApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if (Unit* caster = GetCaster())
            {
                caster->RemoveAurasDueToSpell(SPELL_PRIEST_LINGERING_INSANITY);
                if (Aura* aura = caster->GetAura(SPELL_PRIEST_SHADOWFORM_STANCE))
                    caster->RemoveAura(aura, AURA_REMOVE_BY_CANCEL);

                //Insanity Equation first stack
                GetAura()->GetEffect(EFFECT_2)->SetAmount((-5.33f - 0.66f) * 500);
            }
        }

        void HandlePeriodic(AuraEffect const* aurEff)
        {
            Unit* caster = GetCaster();
            if (!caster)
                return;

            // This spell must end when insanity hit 0
            if (caster->GetPower(POWER_INSANITY) == 0)
            {
                caster->RemoveAura(aurEff->GetBase());
                return;
            }

			uint8 stacks = GetAura()->GetStackAmount();
			
			switch (stacks)
			{
				case 3:
					caster->CastSpell(caster, SPELL_PRIEST_VOIDFORM_TENTACLES, true);
					break;
				case 6:
					caster->CastSpell(caster, SPELL_PRIEST_VOIDFORM_TENTACLES + 1, true);
					break;
				case 9:
					caster->CastSpell(caster, SPELL_PRIEST_VOIDFORM_TENTACLES + 2, true);
					break;
				case 12:
					caster->CastSpell(caster, SPELL_PRIEST_VOIDFORM_TENTACLES + 3, true);
					break;
			}

            // Void Torrent prevent the internal TICK to keep going.
            if (!caster->HasAura(SPELL_PRIEST_VOID_TORRENT_PREVENT_REGEN) && !caster->HasAura(SPELL_PRIEST_SUSTAINED_SANITY))
                stacks++;

            GetAura()->ModStackAmount(1, AURA_REMOVE_BY_DEFAULT, false, false);
            // This keep the time constant on every stack.
            GetAura()->GetEffect(EFFECT_2)->SetAmount((-5.33f - 0.66f * stacks) * 500);
        }

        void HandleRemove(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
        {
            Unit* caster = GetCaster();
            if (!caster)
                return;

            for (int i = 0; i < 4; ++i)
                caster->RemoveAurasDueToSpell(SPELL_PRIEST_VOIDFORM_TENTACLES + i);

            // Lingering Insanity
			if (caster->HasAura(SPELL_PRIEST_LINGERING_INSANITY_AURA))
			{
				int32 haste = aurEff->GetAmount();
                CastSpellExtraArgs mod(true);
                mod.AddSpellMod(SPELLVALUE_AURA_STACK, GetAura()->GetStackAmount());

				if (AuraEffect* aEff = caster->GetAuraEffectOfRankedSpell(SPELL_PRIEST_VOIDFORM_BUFFS, EFFECT_3, caster->GetGUID()))
					mod.AddSpellMod(SPELLVALUE_BASE_POINT1, aEff->GetAmount());

				caster->CastSpell(caster, SPELL_PRIEST_LINGERING_INSANITY, mod);
			}

            // Chorus of Insanity
            if (Aura* aura = caster->GetAura(SPELL_PRIEST_CHORUS_OF_INSANITY_POWER))
            {
                CastSpellExtraArgs mod(true);
                mod.AddSpellMod(SPELLVALUE_BASE_POINT0, aura->GetEffect(EFFECT_0)->GetAmount());
                mod.AddSpellMod(SPELLVALUE_AURA_STACK, aurEff->GetBase()->GetStackAmount());
                caster->CastSpell(caster, SPELL_PRIEST_CHORUS_OF_INSANITY_BUFF, mod);
            }

            // TODO: Figure out whats going on here and why this won't work.
            //caster->AddAura(SPELL_PRIEST_SHADOWFORM_STANCE);
            caster->m_Events.AddEventAtOffset([caster]() {
                caster->CastSpell(caster, SPELL_PRIEST_SHADOWFORM_STANCE, true);
                }, 100ms);
        }

		//void CalculateAmount(AuraEffect const* /*aurEff*/, int32& amount, bool& /*canBeRecalculated*/)
		//{
		//	if (Unit* caster = GetCaster())
		//		if (Aura* aura = caster->GetAura(SPELL_PRIEST_VOIDFORM_BUFFS))
		//			aura->GetEffect(EFFECT_3)->SetDonePct(0.5f);
		//}

        void Register() override
        {
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_pri_voidform_AuraScript::HandlePeriodic, EFFECT_4, SPELL_AURA_PERIODIC_DUMMY);
            AfterEffectRemove += AuraEffectRemoveFn(spell_pri_voidform_AuraScript::HandleRemove, EFFECT_3, SPELL_AURA_MOD_SPELL_CRIT_CHANCE, AURA_EFFECT_HANDLE_REAL);
			//DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_pri_voidform_AuraScript::CalculateAmount, EFFECT_3, SPELL_AURA_MOD_SPELL_CRIT_CHANCE);
            AfterEffectApply += AuraEffectApplyFn(spell_pri_voidform_AuraScript::HandleApply, EFFECT_4, SPELL_AURA_PERIODIC_DUMMY, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_pri_voidform_AuraScript();
    }
};

// Void Eruption - 228260
class spell_pri_void_eruption : public SpellScript
{
    PrepareSpellScript(spell_pri_void_eruption);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_PRIEST_VOID_ERUPTION, SPELL_PRIEST_VOID_ERUPTION_DAMAGE });
    }

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        Unit* caster = GetCaster();
        if (!caster)
            return;

        targets.remove_if([caster](WorldObject* target)
        {
            Unit* targ = target->ToUnit(); //Remove all non-unit targets
            if (!targ)
                return true;

			return false;
        });
    }

    void HandleTakePower(SpellPowerCost& powerCost)
    {
        powerCost.Amount = 0;
    }

    void HandleDummy(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        int8 spellid = std::rand() % 2; //there are two animations which should be random
        caster->CastSpell(target, SPELL_PRIEST_VOID_ERUPTION_DAMAGE + spellid, true);
    }

    void EnterVoidform()
    {
        Unit* caster = GetCaster();
        if (!caster)
            return;

        caster->CastSpell(caster, SPELL_PRIEST_VOIDFORM_BUFFS, true);
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_pri_void_eruption::FilterTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ENEMY);
        OnTakePower += SpellOnTakePowerFn(spell_pri_void_eruption::HandleTakePower);
        OnEffectHitTarget += SpellEffectFn(spell_pri_void_eruption::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
        AfterCast += SpellCastFn(spell_pri_void_eruption::EnterVoidform);
    }
};

class PowerCheck
{
    public:
        explicit PowerCheck(Powers const power) : _power(power) { }

        bool operator()(WorldObject* obj) const
        {
            if (Unit* target = obj->ToUnit())
                return target->GetPowerType() != _power;

            return true;
        }

    private:
        Powers const _power;
};

class RaidCheck
{
    public:
        explicit RaidCheck(Unit const* caster) : _caster(caster) { }

        bool operator()(WorldObject* obj) const
        {
            if (Unit* target = obj->ToUnit())
                return !_caster->IsInRaidWith(target);

            return true;
        }

    private:
        Unit const* _caster;
};

// 228360 - Void Eruption Damage
// 228361 - Void Eruption Damage
class spell_pri_void_eruption_damage : public SpellScript
{
    PrepareSpellScript(spell_pri_void_eruption_damage);

    void HandleHitEffect(SpellEffIndex /*effIndex*/)
    {
        //Releases an explosive blast of pure void energy, activating Voidform and causing ${$228360s1*2} Shadow damage to all enemies within $a1 yds of your target.
        SetHitDamage(GetHitDamage() * 2.0f);            
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_pri_void_eruption_damage::HandleHitEffect, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

// 34861 - Holy Word: Sanctify
class spell_pri_holy_word_sanctify : public SpellScript
{
    PrepareSpellScript(spell_pri_holy_word_sanctify);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_PRIEST_HOLY_WORD_SALVATION });
    }

    void HandleAfterCast()
    {
        if (Unit* caster = GetCaster())
        {
            caster->GetSpellHistory()->ModifyCooldown(SPELL_PRIEST_HOLY_WORD_SALVATION, -30s);

            // Cosmic Ripple
            if (caster->HasAura(SPELL_PRIEST_COSMIC_RIPPLE))
                caster->Variables.Set("CosmicRippleSantify", true);
        }
    }

    void Register() override
    {
        AfterCast += SpellCastFn(spell_pri_holy_word_sanctify::HandleAfterCast);
    }
};

// 64844 - Divine Hymn
class spell_pri_divine_hymn : public SpellScriptLoader
{
    public:
        spell_pri_divine_hymn() : SpellScriptLoader("spell_pri_divine_hymn") { }

        class spell_pri_divine_hymn_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_pri_divine_hymn_SpellScript);

            void FilterTargets(std::list<WorldObject*>& targets)
            {
                targets.remove_if(RaidCheck(GetCaster()));

                uint32 const maxTargets = 3;

                if (targets.size() > maxTargets)
                {
                    targets.sort(Trinity::HealthPctOrderPred());
                    targets.resize(maxTargets);
                }
            }

            void Register() override
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_pri_divine_hymn_SpellScript::FilterTargets, EFFECT_ALL, TARGET_UNIT_SRC_AREA_ALLY);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_pri_divine_hymn_SpellScript();
        }
};

class spell_pri_improved_power_word_shield : public SpellScriptLoader
{
    public:
        spell_pri_improved_power_word_shield() : SpellScriptLoader("spell_pri_improved_power_word_shield") { }

        class spell_pri_improved_power_word_shield_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_pri_improved_power_word_shield_AuraScript);

            void HandleEffectCalcSpellMod(AuraEffect const* aurEff, SpellModifier*& spellMod)
            {
                if (!spellMod)
                {
                    auto smbcm = new SpellModifierByClassMask(GetAura());
                    smbcm->op = SpellModOp(aurEff->GetMiscValue());
                    smbcm->type = SPELLMOD_PCT;
                    smbcm->spellId = GetId();
                    smbcm->mask = GetSpellInfo()->GetEffect(aurEff->GetEffIndex()).SpellClassMask;
                    smbcm->value = aurEff->GetAmount();
                    spellMod = smbcm;
                }
                // hmmm...
                //if (auto mod = reinterpret_cast<SpellModifierByClassMask*>(spellMod))
                //    mod->value = aurEff->GetAmount();
            }

            void Register() override
            {
                DoEffectCalcSpellMod += AuraEffectCalcSpellModFn(spell_pri_improved_power_word_shield_AuraScript::HandleEffectCalcSpellMod, EFFECT_0, SPELL_AURA_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const override
        {
            return new spell_pri_improved_power_word_shield_AuraScript();
        }
};

// 37594 - Greater Heal Refund
class spell_pri_item_greater_heal_refund : public SpellScriptLoader
{
    public:
        spell_pri_item_greater_heal_refund() : SpellScriptLoader("spell_pri_item_greater_heal_refund") { }

        class spell_pri_item_greater_heal_refund_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_pri_item_greater_heal_refund_AuraScript);

            bool Validate(SpellInfo const* /*spellInfo*/) override
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_PRIEST_ITEM_EFFICIENCY))
                    return false;
                return true;
            }

            void OnProc(AuraEffect* aurEff, ProcEventInfo& /*eventInfo*/)
            {
                PreventDefaultAction();
                GetTarget()->CastSpell(GetTarget(), SPELL_PRIEST_ITEM_EFFICIENCY, CastSpellExtraArgs(aurEff).SetTriggerFlags(TriggerCastFlags::TRIGGERED_FULL_MASK));
            }

            void Register() override
            {
                OnEffectProc += AuraEffectProcFn(spell_pri_item_greater_heal_refund_AuraScript::OnProc, EFFECT_0, SPELL_AURA_PROC_TRIGGER_SPELL);
            }
        };

        AuraScript* GetAuraScript() const override
        {
            return new spell_pri_item_greater_heal_refund_AuraScript();
        }
};

// 47788 - Guardian Spirit
class spell_pri_guardian_spirit : public AuraScript
{
    PrepareAuraScript(spell_pri_guardian_spirit);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo( { SPELL_PRIEST_GUARDIAN_SPIRIT_HEAL, SPELL_PRIEST_GUARDIAN_SPIRIT_AURA });
    }

    void CalculateAmount(AuraEffect const* /*aurEff*/, int32& amount, bool & /*canBeRecalculated*/)
    {
        // Set absorbtion amount to unlimited
        amount = -1;
    }

    void Absorb(AuraEffect* /*aurEff*/, DamageInfo & dmgInfo, uint32 & absorbAmount)
    {
        Unit* target = GetTarget();
        if (dmgInfo.GetDamage() < target->GetHealth())
            return;

        int32 healAmount = int32(target->CountPctFromMaxHealth(sSpellMgr->GetSpellInfo(SPELL_PRIEST_GUARDIAN_SPIRIT_AURA)->GetEffect(EFFECT_1).BasePoints));
        // remove the aura now, we don't want 40% healing bonus
        Remove(AURA_REMOVE_BY_ENEMY_SPELL);
        target->CastSpell(target, SPELL_PRIEST_GUARDIAN_SPIRIT_HEAL, CastSpellExtraArgs(true).AddSpellBP0(healAmount));
        absorbAmount = dmgInfo.GetDamage();
    }

    void HandleRemove(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        if (Unit* caster = GetCaster())
            if (caster->HasAura(SPELL_PRIEST_GUARDIAN_ANGEL) && IsExpired())
                caster->GetSpellHistory()->ModifyCooldown(SPELL_PRIEST_GUARDIAN_SPIRIT_AURA, -sSpellMgr->GetSpellInfo(SPELL_PRIEST_GUARDIAN_ANGEL)->GetEffect(EFFECT_0).BasePoints * IN_MILLISECONDS);
    }

    void Register() override
    {
        DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_pri_guardian_spirit::CalculateAmount, EFFECT_2, SPELL_AURA_SCHOOL_ABSORB);
        OnEffectAbsorb += AuraEffectAbsorbFn(spell_pri_guardian_spirit::Absorb, EFFECT_2);
        OnEffectRemove += AuraEffectRemoveFn(spell_pri_guardian_spirit::HandleRemove, EFFECT_0, SPELL_AURA_MOD_HEALING_PCT, AURA_EFFECT_HANDLE_REAL);
    }
};

// 64904 - Hymn of Hope
class spell_pri_hymn_of_hope : public SpellScriptLoader
{
    public:
        spell_pri_hymn_of_hope() : SpellScriptLoader("spell_pri_hymn_of_hope") { }

        class spell_pri_hymn_of_hope_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_pri_hymn_of_hope_SpellScript);

            void FilterTargets(std::list<WorldObject*>& targets)
            {
                targets.remove_if(PowerCheck(POWER_MANA));
                targets.remove_if(RaidCheck(GetCaster()));

                uint32 const maxTargets = 3;

                if (targets.size() > maxTargets)
                {
                    targets.sort(Trinity::PowerPctOrderPred(POWER_MANA));
                    targets.resize(maxTargets);
                }
            }

            void Register() override
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_pri_hymn_of_hope_SpellScript::FilterTargets, EFFECT_ALL, TARGET_UNIT_SRC_AREA_ALLY);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_pri_hymn_of_hope_SpellScript();
        }
};

// 92833 - Leap of Faith
class spell_pri_leap_of_faith_effect_trigger : public SpellScriptLoader
{
    public:
        spell_pri_leap_of_faith_effect_trigger() : SpellScriptLoader("spell_pri_leap_of_faith_effect_trigger") { }

        class spell_pri_leap_of_faith_effect_trigger_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_pri_leap_of_faith_effect_trigger_SpellScript);

            bool Validate(SpellInfo const* /*spellInfo*/) override
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_PRIEST_LEAP_OF_FAITH_EFFECT))
                    return false;
                return true;
            }

            void HandleEffectDummy(SpellEffIndex /*effIndex*/)
            {
                Position destPos = GetHitDest()->GetPosition();

                SpellCastTargets targets;
                targets.SetDst(destPos);
                targets.SetUnitTarget(GetCaster());
                CastSpellTargetArg t;
                t.Targets.emplace(std::move(targets));
                GetHitUnit()->CastSpell(t, sSpellMgr->GetSpellInfo(GetEffectValue())->Id);
            }

            void Register() override
            {
                OnEffectHitTarget += SpellEffectFn(spell_pri_leap_of_faith_effect_trigger_SpellScript::HandleEffectDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_pri_leap_of_faith_effect_trigger_SpellScript();
        }
};

// 7001 - Lightwell Renew
class spell_pri_lightwell_renew : public SpellScriptLoader
{
    public:
        spell_pri_lightwell_renew() : SpellScriptLoader("spell_pri_lightwell_renew") { }

        class spell_pri_lightwell_renew_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_pri_lightwell_renew_AuraScript);

            void CalculateAmount(AuraEffect const* /*aurEff*/, int32& amount, bool& /*canBeRecalculated*/)
            {
                if (Unit* caster = GetCaster())
                {
                    // Bonus from Glyph of Lightwell
                    if (AuraEffect* modHealing = caster->GetAuraEffect(SPELL_PRIEST_GLYPH_OF_LIGHTWELL, EFFECT_0))
                        AddPct(amount, modHealing->GetAmount());
                }
            }

            void Register() override
            {
                DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_pri_lightwell_renew_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_PERIODIC_HEAL);
            }
        };

        AuraScript* GetAuraScript() const override
        {
            return new spell_pri_lightwell_renew_AuraScript();
        }
};

// 8122 - Pshychic Scream
class aura_priest_pshychic_scream : public AuraScript
{
	PrepareAuraScript(aura_priest_pshychic_scream);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetDamageInfo() && (eventInfo.GetDamageInfo()->GetDamageType() != HEAL && eventInfo.GetDamageInfo()->GetDamageType() != NODAMAGE))
        {

            Unit* caster = GetCaster();
            Unit* target = GetTarget();
            if (!caster || !target)
                return false;

            Aura* aura = GetAura();

            // Fear will be removed if the damage if greater or equal to 10% of the target maximun health.
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
				owner->ToUnit()->RemoveAura(SPELL_PRIEST_PSHYSHIC_SCREAM);
	}

	void Register() override
	{
		DoCheckProc += AuraCheckProcFn(aura_priest_pshychic_scream::CheckProc);
		OnProc += AuraProcFn(aura_priest_pshychic_scream::HandleProc);
	}
};

// 28305 - Mana Leech (Passive) (Priest Pet Aura)
class spell_pri_mana_leech : public SpellScriptLoader
{
    public:
        spell_pri_mana_leech() : SpellScriptLoader("spell_pri_mana_leech") { }

        class spell_pri_mana_leech_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_pri_mana_leech_AuraScript);

        public:
            spell_pri_mana_leech_AuraScript()
            {
                _procTarget = nullptr;
            }

        private:
            bool Validate(SpellInfo const* /*spellInfo*/) override
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_PRIEST_MANA_LEECH_PROC))
                    return false;
                return true;
            }

            bool CheckProc(ProcEventInfo& /*eventInfo*/)
            {
                _procTarget = GetTarget()->GetOwner();
                return _procTarget != nullptr;
            }

            void HandleProc(AuraEffect* aurEff, ProcEventInfo& /*eventInfo*/)
            {
                PreventDefaultAction();
                GetTarget()->CastSpell(_procTarget, SPELL_PRIEST_MANA_LEECH_PROC, CastSpellExtraArgs(aurEff).SetTriggerFlags(TriggerCastFlags::TRIGGERED_FULL_MASK));
            }

            void Register() override
            {
                DoCheckProc += AuraCheckProcFn(spell_pri_mana_leech_AuraScript::CheckProc);
                OnEffectProc += AuraEffectProcFn(spell_pri_mana_leech_AuraScript::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
            }

        private:
            Unit* _procTarget;
        };

        AuraScript* GetAuraScript() const override
        {
            return new spell_pri_mana_leech_AuraScript();
        }
};

// 49821 - Mind Sear
class spell_pri_mind_sear : public SpellScript
{
	PrepareSpellScript(spell_pri_mind_sear);

	void HandleInsanity(SpellEffIndex /*effIndex*/)
	{
		if (Unit* caster = GetCaster())
			caster->CastSpell(caster, SPELL_PRIEST_MIND_SEAR_INSANITY, true);
	}

	void Register() override
	{
		OnEffectHitTarget += SpellEffectFn(spell_pri_mind_sear::HandleInsanity, EFFECT_1, SPELL_EFFECT_SCHOOL_DAMAGE);
	}
};

// 47948 - Pain and Suffering (Proc)
class spell_pri_pain_and_suffering_proc : public SpellScriptLoader
{
    public:
        spell_pri_pain_and_suffering_proc() : SpellScriptLoader("spell_pri_pain_and_suffering_proc") { }

        class spell_pri_pain_and_suffering_proc_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_pri_pain_and_suffering_proc_SpellScript);

            void HandleEffectScriptEffect(SpellEffIndex /*effIndex*/)
            {
                Unit* caster = GetCaster();
                // Refresh Shadow Word: Pain on target
                if (Unit* target = GetHitUnit())
                    if (AuraEffect* aur = target->GetAuraEffect(SPELL_AURA_PERIODIC_DAMAGE, SPELLFAMILY_PRIEST, flag128(0x8000, 0, 0), caster->GetGUID()))
                    {
                        uint32 damage = std::max(aur->GetAmount(), 0);
                        sScriptMgr->ModifyPeriodicDamageAurasTick(target, caster, damage);
                        aur->SetDamage(caster->SpellDamageBonusDone(target, aur->GetSpellInfo(), damage, DOT, aur->GetSpellEffectInfo()) * aur->GetDonePct());
                        aur->CalculatePeriodic(caster, false, false);
                        aur->GetBase()->RefreshDuration();
                    }
            }

            void Register() override
            {
                OnEffectHitTarget += SpellEffectFn(spell_pri_pain_and_suffering_proc_SpellScript::HandleEffectScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_pri_pain_and_suffering_proc_SpellScript;
        }
};

// 47540 - Penance
class spell_pri_penance : public SpellScript
{
    PrepareSpellScript(spell_pri_penance);

    bool Load() override
    {
        return GetCaster()->GetTypeId() == TYPEID_PLAYER;
    }

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo(
            {
                SPELL_PRIEST_PENANCE_TARGET_ALLY,
                SPELL_PRIEST_PENANCE_TARGET_ENEMY,
                SPELL_PRIEST_PURGE_THE_WICKED_DOT,
                SPELL_PRIEST_PURGE_THE_WICKED_SEARCHER
            });
    }

    void HandleDummy(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();

        if (Unit* target = GetExplTargetUnit())
        {
            if (!caster->IsFriendlyTo(target))
                caster->CastSpell(target, SPELL_PRIEST_PENANCE_TARGET_ENEMY, TriggerCastFlags(TRIGGERED_FULL_MASK & ~TRIGGERED_DISALLOW_PROC_EVENTS));
            else
                caster->CastSpell(target, SPELL_PRIEST_PENANCE_TARGET_ALLY, TriggerCastFlags(TRIGGERED_FULL_MASK & ~TRIGGERED_DISALLOW_PROC_EVENTS));
        }

        if (target->HasAura(SPELL_PRIEST_PURGE_THE_WICKED_DOT, GetCaster()->GetGUID()))
            caster->CastSpell(target, SPELL_PRIEST_PURGE_THE_WICKED_SEARCHER, true);
    }

    SpellCastResult CheckCast()
    {
        Player* caster = GetCaster()->ToPlayer();

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

        return SPELL_CAST_OK;
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_pri_penance::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
        OnCheckCast += SpellCheckCastFn(spell_pri_penance::CheckCast);
    }
};

class DelayedAuraRemoveEvent : public BasicEvent
{
public:
    DelayedAuraRemoveEvent(Unit* owner, uint32 spellId) : _owner(owner), _spellId(spellId) {}

    bool Execute(uint64 /*time*/, uint32 /*diff*/) override
    {
        _owner->RemoveAurasDueToSpell(_spellId);
        return true;
    }

private:
    Unit* _owner;
    uint32 _spellId;
};

// 204215 - Purge the Wicked
class spell_pri_purge_the_wicked_selector : public SpellScript
{
    PrepareSpellScript(spell_pri_purge_the_wicked_selector);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo(
            {
                SPELL_PRIEST_PURGE_THE_WICKED_DOT,
                SPELL_PRIEST_PURGE_THE_WICKED
            });
    }

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        targets.remove_if(Trinity::UnitAuraCheck(true, SPELL_PRIEST_PURGE_THE_WICKED_DOT, GetCaster()->GetGUID()));
        targets.sort(Trinity::ObjectDistanceOrderPred(GetExplTargetUnit()));
        if (targets.size() > 1)
            targets.resize(1);
    }

    void HandleDummy(SpellEffIndex /*effIndex*/)
    {
        GetCaster()->AddAura(SPELL_PRIEST_PURGE_THE_WICKED_DOT, GetHitUnit());
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_pri_purge_the_wicked_selector::FilterTargets, EFFECT_1, TARGET_UNIT_DEST_AREA_ENEMY);
        OnEffectHitTarget += SpellEffectFn(spell_pri_purge_the_wicked_selector::HandleDummy, EFFECT_1, SPELL_EFFECT_DUMMY);
    }
};

// 47757 - Penance
// 47758 - Penance
class spell_pri_penance_triggered : public AuraScript
{
    PrepareAuraScript(spell_pri_penance_triggered);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo(
            {
                SPELL_PRIEST_POWER_OF_THE_DARK_SIDE_AURA,
                SPELL_PRIEST_POWER_OF_THE_DARK_SIDE_MARKER
            });
    }

    void ApplyEffect(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* caster = GetCaster())
        {
            if (caster->HasAura(SPELL_PRIEST_POWER_OF_THE_DARK_SIDE_AURA))
            {
                caster->RemoveAurasDueToSpell(SPELL_PRIEST_POWER_OF_THE_DARK_SIDE_AURA);
                caster->CastSpell(caster, SPELL_PRIEST_POWER_OF_THE_DARK_SIDE_MARKER, true);
            }
        }
    }

    void RemoveEffect(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* caster = GetCaster()) // Penance has travel time we need to delay the aura remove a little bit...
            caster->m_Events.AddEvent(new DelayedAuraRemoveEvent(caster, SPELL_PRIEST_POWER_OF_THE_DARK_SIDE_MARKER), caster->m_Events.CalculateTime(1000ms));
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_pri_penance_triggered::ApplyEffect, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        OnEffectRemove += AuraEffectRemoveFn(spell_pri_penance_triggered::RemoveEffect, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

// 47750 - Penance
// 47666 - Penance
class spell_pri_penance_heal_damage : public SpellScript
{
    PrepareSpellScript(spell_pri_penance_heal_damage);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo(
            {
                SPELL_PRIEST_POWER_OF_THE_DARK_SIDE_MARKER,
                SPELL_PRIEST_PENANCE_HEAL
            });
    }

    void HandleHit()
    {
        if (Unit* caster = GetCaster())
        {
            if (AuraEffect* powerOfTheDarkSide = caster->GetAuraEffect(SPELL_PRIEST_POWER_OF_THE_DARK_SIDE_MARKER, EFFECT_0))
            {
                if (GetSpellInfo()->Id == SPELL_PRIEST_PENANCE_HEAL)
                {
                    int32 heal = GetHitHeal();
                    AddPct(heal, powerOfTheDarkSide->GetAmount());
                    SetHitHeal(heal);
                }
                else
                {
                    int32 damage = GetHitDamage();
                    AddPct(damage, powerOfTheDarkSide->GetAmount());
                    SetHitDamage(damage);
                }
            }

            // Weal and Woe
            if (GetSpellInfo()->Id == SPELL_PRIEST_PENANCE_HEAL)
            {
                if (caster->GetAuraEffect(SPELL_PRIEST_CONTRITION, EFFECT_0))
                    for (AuraApplication* auApp : GetCaster()->GetTargetAuraApplications(SPELL_PRIEST_ATONEMENT_AURA))
                        caster->CastSpell(auApp->GetTarget(), SPELL_PRIEST_CONTRITION_HEAL, true);

                if (Aura* aura = caster->GetAura(SPELL_PRIEST_WEAL_AND_WOE_POWER))
                    caster->CastSpell(caster, SPELL_PRIEST_WOE, CastSpellExtraArgs(true).AddSpellBP0(aura->GetEffect(EFFECT_0)->GetAmount()));
            }
            else
                if (Aura* aura = caster->GetAura(SPELL_PRIEST_WEAL_AND_WOE_POWER))
                    caster->CastSpell(caster, SPELL_PRIEST_WEAL, CastSpellExtraArgs(true).AddSpellBP0(aura->GetEffect(EFFECT_1)->GetAmount()));
        }
    }

    void Register() override
    {
        OnHit += SpellHitFn(spell_pri_penance_heal_damage::HandleHit);
    }
};

// 197862 - Archangel
class spell_pri_archangel : public SpellScript
{
    PrepareSpellScript(spell_pri_archangel);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo(
            {
                SPELL_PRIEST_ATONEMENT_AURA
            });
    }

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        targets.remove_if(Trinity::UnitAuraCheck(false, SPELL_PRIEST_ATONEMENT_AURA, GetCaster()->GetGUID()));
    }

    void HandleScriptEffect(SpellEffIndex /*effIndex*/)
    {
        if (Aura* aura = GetHitUnit()->GetAura(SPELL_PRIEST_ATONEMENT_AURA, GetCaster()->GetGUID()))
            aura->RefreshDuration();
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_pri_archangel::HandleScriptEffect, EFFECT_2, SPELL_EFFECT_SCRIPT_EFFECT);
    }
};

// 197871 - Dark Archangel
class spell_pri_dark_archangel : public SpellScript
{
    PrepareSpellScript(spell_pri_dark_archangel);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo(
            {
                SPELL_PRIEST_DARK_ARCHANGEL_BUFF
            });
    }

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        targets.remove(GetCaster());
        targets.remove_if(Trinity::UnitAuraCheck(false, SPELL_PRIEST_ATONEMENT_AURA, GetCaster()->GetGUID()));
    }

    void HandleScriptEffect(SpellEffIndex /*effIndex*/)
    {
        GetCaster()->CastSpell(GetHitUnit(), SPELL_PRIEST_DARK_ARCHANGEL_BUFF, true);
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_pri_dark_archangel::FilterTargets, EFFECT_1, TARGET_UNIT_DEST_AREA_ALLY);
        OnEffectHitTarget += SpellEffectFn(spell_pri_dark_archangel::HandleScriptEffect, EFFECT_1, SPELL_EFFECT_SCRIPT_EFFECT);
    }
};

// 139 - Renew Aura
class aura_pri_renew : public AuraScript
{
    PrepareAuraScript(aura_pri_renew);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        if (!sSpellMgr->GetSpellInfo(SPELL_PRIEST_PERSEVERANCE))
            return false;
        return true;
    }

	void CalculateAmount(AuraEffect const* /*aurEff*/, int32& amount, bool& canBeRecalculated)
	{
		Unit* caster = GetCaster();
		Unit* target = GetUnitOwner();
		amount = 0;

		if (caster && target && (caster->GetGUID() == target->GetGUID()) && caster->HasAura(SPELL_PRIEST_PERSEVERANCE))
			amount = -10;
	}

    void Register() override
    {
		DoEffectCalcAmount += AuraEffectCalcAmountFn(aura_pri_renew::CalculateAmount, EFFECT_2, SPELL_AURA_MOD_DAMAGE_PERCENT_TAKEN);
    }
};


// 32379 - Shadow Word Death
class spell_pri_shadow_word_death : public SpellScript
{
    PrepareSpellScript(spell_pri_shadow_word_death);

    void HandleDamage(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        uint8 energize = (target->GetHealth() < uint64(GetHitDamage())) ? GetSpellInfo()->GetEffect(EFFECT_3).BasePoints : GetSpellInfo()->GetEffect(EFFECT_2).BasePoints;
        caster->ModifyPower(POWER_INSANITY, caster->GetPower(POWER_INSANITY) + energize);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_pri_shadow_word_death::HandleDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

// 232698 - Shadowform
class spell_pri_shadowform : public SpellScriptLoader
{
    public:
        spell_pri_shadowform() : SpellScriptLoader("spell_pri_shadowform") { }

        class spell_pri_shadowform_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_pri_shadowform_AuraScript);

            bool Validate(SpellInfo const* /*spellInfo*/) override
            {
                return ValidateSpellInfo({ SPELL_PRIEST_SHADOWFORM_VISUAL_WITHOUT_GLYPH, SPELL_PRIEST_SHADOWFORM_VISUAL_WITH_GLYPH });
            }

            void HandleEffectApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Unit* caster = GetCaster())
                {
                    caster->CastSpell(caster, caster->HasAura(SPELL_PRIEST_GLYPH_OF_SHADOW) ? SPELL_PRIEST_SHADOWFORM_VISUAL_WITH_GLYPH : SPELL_PRIEST_SHADOWFORM_VISUAL_WITHOUT_GLYPH, true);
                    if (caster->HasAura(SPELL_PRIEST_VOIDFORM_BUFFS))
                        caster->RemoveAura(GetAura());
                }
            }

            void HandleEffectRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Unit* caster = GetCaster())
                    caster->RemoveAurasDueToSpell(caster->HasAura(SPELL_PRIEST_GLYPH_OF_SHADOW) ? SPELL_PRIEST_SHADOWFORM_VISUAL_WITH_GLYPH : SPELL_PRIEST_SHADOWFORM_VISUAL_WITHOUT_GLYPH);
            }

            void Register() override
            {
                AfterEffectApply += AuraEffectApplyFn(spell_pri_shadowform_AuraScript::HandleEffectApply, EFFECT_0, SPELL_AURA_ADD_PCT_MODIFIER, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
                AfterEffectRemove += AuraEffectRemoveFn(spell_pri_shadowform_AuraScript::HandleEffectRemove, EFFECT_0, SPELL_AURA_ADD_PCT_MODIFIER, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
            }
        };

        AuraScript* GetAuraScript() const override
        {
            return new spell_pri_shadowform_AuraScript();
        }
};

// 15286 - Vampiric Embrace Last Update 8.0.1 Build 28153
class spell_pri_vampiric_embrace : public AuraScript
{
    PrepareAuraScript(spell_pri_vampiric_embrace);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_PRIEST_VAMPIRIC_EMBRACE_HEAL });
    }

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetDamageInfo())
            return false;

        if (!eventInfo.GetDamageInfo()->GetSpellInfo())
            return false;

        if (!eventInfo.GetDamageInfo()->GetDamage())
            return false;

        // Not proc from Mind Sear
        return eventInfo.GetDamageInfo()->GetSpellInfo()->Id != SPELL_PRIEST_MIND_SEAR_DAMAGE;
    }

    void HandleEffectProc(AuraEffect* aurEff, ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();
        int32 bp = int32(CalculatePct(eventInfo.GetDamageInfo()->GetDamage(), aurEff->GetAmount()));
        if(Unit* target = GetTarget())
            target->CastSpell(target, SPELL_PRIEST_VAMPIRIC_EMBRACE_HEAL, CastSpellExtraArgs(true).AddSpellBP0(bp).SetTriggeringAura(aurEff));
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_pri_vampiric_embrace::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_pri_vampiric_embrace::HandleEffectProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

// 34914 - Vampiric Touch
class spell_pri_vampiric_touch : public AuraScript
{
    PrepareAuraScript(spell_pri_vampiric_touch);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_PRIEST_VAMPIRIC_TOUCH_DISPEL, SPELL_GEN_REPLENISHMENT, SPELL_PRIEST_MISERY, SPELL_PRIEST_SHADOW_WORD_PAIN });
    }

    void HandleDispel(DispelInfo* /*dispelInfo*/)
    {
        if (Unit* caster = GetCaster())
            if (Unit* target = GetUnitOwner())
                caster->CastSpell(target, SPELL_PRIEST_VAMPIRIC_TOUCH_DISPEL, true);
    }

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetProcTarget() == GetCaster();
    }

    void HandleEffectProc(AuraEffect* aurEff, ProcEventInfo& eventInfo)
    {
        eventInfo.GetProcTarget()->CastSpell(nullptr, SPELL_GEN_REPLENISHMENT, CastSpellExtraArgs(aurEff));
    }

    void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* caster = GetCaster())
            if (caster->HasAura(SPELL_PRIEST_MISERY))
                caster->CastSpell(GetTarget(), SPELL_PRIEST_SHADOW_WORD_PAIN, true);
    }

    void Register() override
    {
        AfterDispel += AuraDispelFn(spell_pri_vampiric_touch::HandleDispel);
        DoCheckProc += AuraCheckProcFn(spell_pri_vampiric_touch::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_pri_vampiric_touch::HandleEffectProc, EFFECT_2, SPELL_AURA_DUMMY);
        AfterEffectApply += AuraEffectApplyFn(spell_pri_vampiric_touch::OnApply, EFFECT_1, SPELL_AURA_PERIODIC_LEECH, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
    }
};

// 73325
class spell_pri_leap_of_faith : public SpellScriptLoader
{

public:
    spell_pri_leap_of_faith() : SpellScriptLoader("spell_pri_leap_of_faith") {}

    class spell_pri_leap_of_faith_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_pri_leap_of_faith_SpellScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            return sSpellMgr->GetSpellInfo(SPELL_PRIEST_LEAP_OF_FAITH_GLYPH)
                && sSpellMgr->GetSpellInfo(SPELL_PRIEST_LEAP_OF_FAITH_EFFECT);
        }

        void HandleScript(SpellEffIndex /* effIndex */)
        {
            Unit* caster = GetCaster();
            if (!caster)
                return;

            if (caster->HasAura(SPELL_PRIEST_LEAP_OF_FAITH_GLYPH))
                GetHitUnit()->RemoveMovementImpairingAuras(true);

            GetHitUnit()->CastSpell(caster, SPELL_PRIEST_LEAP_OF_FAITH_EFFECT, true);
        }

        void HandleOnHit()
        {
            if (Player* _player = GetCaster()->ToPlayer())
            {
                if (Unit* target = GetHitUnit())
                {
                    target->CastSpell(_player, SPELL_PRIEST_LEAP_OF_FAITH_JUMP, true);

                    if (_player->HasAura(SPELL_PRIEST_BODY_AND_SOUL_AURA)) _player->CastSpell(target, SPELL_PRIEST_BODY_AND_SOUL_SPEED, true);
                }
            }
        }

        void Register() override
        {
            OnHit += SpellHitFn(spell_pri_leap_of_faith_SpellScript::HandleOnHit);
            OnEffectHitTarget += SpellEffectFn(spell_pri_leap_of_faith_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_pri_leap_of_faith_SpellScript();
    }
};

// 1706
class spell_pri_levitate : public SpellScriptLoader
{
public:
    spell_pri_levitate() : SpellScriptLoader("spell_pri_levitate") { }

    class spell_pri_levitate_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_pri_levitate_SpellScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_PRIEST_LEVITATE_AURA))
                return false;
            return true;
        }

        void HandleDummy(SpellEffIndex /*effIndex*/)
        {
            if (Unit* caster = GetCaster())
                if (Unit* target = GetHitUnit())
                    caster->CastSpell(target, SPELL_PRIEST_LEVITATE_AURA, true);
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_pri_levitate_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_pri_levitate_SpellScript;
    }
};

// Void Tendrils - 108920
class spell_pri_void_tendrils : public SpellScriptLoader
{
public:
    spell_pri_void_tendrils() : SpellScriptLoader("spell_pri_void_tendrils") { }

    class spell_pri_void_tendrils_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_pri_void_tendrils_SpellScript);

        void HandleOnHit()
        {
            if (Player* _player = GetCaster()->ToPlayer())
                if (Unit* target = GetHitUnit())
                    _player->CastSpell(target, SPELL_PRIEST_VOID_TENDRILS_SUMMON, true);
        }

        void Register() override
        {
            OnHit += SpellHitFn(spell_pri_void_tendrils_SpellScript::HandleOnHit);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_pri_void_tendrils_SpellScript();
    }
};

// 129250 - Power Word: Solace
class spell_pri_power_word_solace : public SpellScript
{
    PrepareSpellScript(spell_pri_power_word_solace);

    void HandleOnHit()
    {
        if (Unit* caster = GetCaster())
        {
            // $mana = $m2 / 100
            // But the mana energize pct spell are divided in the effect, so we need to send the full non-divided value.
            uint8 manaPercent = sSpellMgr->GetSpellInfo(SPELL_PRIEST_POWER_WORD_SOLACE)->GetEffect(EFFECT_1).BasePoints;
            caster->CastSpell(caster, SPELL_PRIEST_POWER_WORD_SOLACE_ENERGIZE, CastSpellExtraArgs(true).AddSpellBP0(manaPercent));
        }
    }

    void Register() override
    {
        OnHit += SpellHitFn(spell_pri_power_word_solace::HandleOnHit);
    }
};

class spell_pri_shadowfiend : public SpellScriptLoader
{
public:
    spell_pri_shadowfiend() : SpellScriptLoader("spell_pri_shadowfiend") { }

    class spell_pri_shadowfiend_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_pri_shadowfiend_SpellScript);

        void HandleAfterHit()
        {
            if (Player* _player = GetCaster()->ToPlayer())
            {
                if (Unit* target = GetExplTargetUnit())
                {
                    if (Guardian* pet = _player->GetGuardianPet())
                    {
                        pet->InitCharmInfo();
                        pet->SetReactState(REACT_DEFENSIVE);
                        pet->ToCreature()->AI()->AttackStart(target);
                    }
                }
            }
        }

        void Register() override
        {
            AfterHit += SpellHitFn(spell_pri_shadowfiend_SpellScript::HandleAfterHit);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_pri_shadowfiend_SpellScript();
    }
};

class spell_pri_spirit_shell : public SpellScriptLoader
{
public:
    spell_pri_spirit_shell() : SpellScriptLoader("spell_pri_spirit_shell") { }

    class spell_pri_spirit_shell_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_pri_spirit_shell_SpellScript);

        void HandleOnHit()
        {
            if (Player* _player = GetCaster()->ToPlayer())
            {
                if (Unit* target = GetHitUnit())
                {
                    if (_player->HasAura(SPELL_PRIEST_SPIRIT_SHELL_AURA))
                    {
                        int32 bp = GetHitHeal();

                        SetHitHeal(0);

                        if (AuraEffect* shell = _player->GetAuraEffect(114908, EFFECT_0))
                            shell->SetAmount(std::min(shell->GetAmount() + bp, (int32)_player->CountPctFromMaxHealth(60)));
                        else
                            _player->CastSpell(target, SPELL_PRIEST_POWER_WORD_SOLACE_ENERGIZE, CastSpellExtraArgs(true).AddSpellBP0(bp));
                    }
                }
            }
        }

        void Register() override
        {
            OnHit += SpellHitFn(spell_pri_spirit_shell_SpellScript::HandleOnHit);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_pri_spirit_shell_SpellScript();
    }
};

class spell_pri_strength_of_soul : public SpellScriptLoader
{
public:
    spell_pri_strength_of_soul() : SpellScriptLoader("spell_pri_strength_of_soul") { }

    class spell_pri_strength_of_soul_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_pri_strength_of_soul_SpellScript);

        void HandleOnHit()
        {
            // TODO
        }

        void Register() override
        {
            OnHit += SpellHitFn(spell_pri_strength_of_soul_SpellScript::HandleOnHit);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_pri_strength_of_soul_SpellScript();
    }
};

// 108945 - Angelic Bulwark
class spell_priest_angelic_bulwark : public SpellScriptLoader
{
public:
    spell_priest_angelic_bulwark() : SpellScriptLoader("spell_priest_angelic_bulwark")
    {
    }

    class spell_priest_angelic_bulwark_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_priest_angelic_bulwark_AuraScript);

        bool CheckProc(ProcEventInfo& procInfo)
        {
            auto damageInfo = procInfo.GetDamageInfo();
            Unit* target = procInfo.GetActionTarget();
            auto auraEffect = GetEffect(EFFECT_0);

            if (!damageInfo || !damageInfo->GetDamage() || !target || !auraEffect)
                return false;

            if (target->HasAura(114216))
                return false;

            uint32 health = target->GetHealth();
            uint32 threashold = CalculatePct(target->GetMaxHealth(), auraEffect->GetAmount());

            return (health - damageInfo->GetDamage() < threashold);
        }

        void HandleEffectProc(AuraEffect* aurEff , ProcEventInfo& eventInfo)
        {
            Unit* target = eventInfo.GetActionTarget();
            int64 bp0 = CalculatePct(target->GetMaxHealth(), GetSpellInfo()->GetEffect(EFFECT_1).BasePoints);
            target->CastSpell(target, 114214, CastSpellExtraArgs(true).AddSpellBP0(bp0).SetTriggeringAura(aurEff));
            target->CastSpell(target, 114216, true);
        }

        void Register() override
        {
            DoCheckProc += AuraCheckProcFn(spell_priest_angelic_bulwark_AuraScript::CheckProc);
            OnEffectProc += AuraEffectProcFn(spell_priest_angelic_bulwark_AuraScript::HandleEffectProc, EFFECT_0, SPELL_AURA_PROC_TRIGGER_SPELL);
        }
    };

    AuraScript *GetAuraScript() const override
    {
        return new spell_priest_angelic_bulwark_AuraScript();
    }
};

//586 Fade
//Last Update 8.0.1 Build 28153
class spell_pri_fade : public SpellScriptLoader
{
public:
    spell_pri_fade() : SpellScriptLoader("spell_pri_fade") { }

    class spell_pri_fade_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_pri_fade_SpellScript);

        void HandleOnHit()
        {
            if (Unit* caster = GetCaster())
                if (AuraEffect* auraEff = caster->GetAuraEffect(SPELL_PRIEST_SANCTUM_POWER, EFFECT_0))
                    caster->CastSpell(caster, SPELL_PRIEST_SANCTUM_SHIELD, CastSpellExtraArgs(true).AddSpellBP0(auraEff->GetAmount()));
        }

        void Register() override
        {
            OnHit += SpellHitFn(spell_pri_fade_SpellScript::HandleOnHit);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_pri_fade_SpellScript();
    }
};

// Glyph of Shadow - 107906
class spell_pri_glyph_of_shadow : public SpellScriptLoader
{
public:
    spell_pri_glyph_of_shadow() : SpellScriptLoader("spell_pri_glyph_of_shadow") {}

    class spell_pri_glyph_of_shadow_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_pri_glyph_of_shadow_AuraScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_PRIEST_SHADOWFORM_VISUAL_WITH_GLYPH))
                return false;
            return true;
        }

        void HandleApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            Unit* caster = GetCaster();
            if (!caster)
                return;

            caster->RemoveAurasDueToSpell(SPELL_PRIEST_SHADOWFORM_VISUAL_WITHOUT_GLYPH);
            caster->CastSpell(caster, SPELL_PRIEST_SHADOWFORM_VISUAL_WITH_GLYPH, true);
        }

        void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            Unit* caster = GetCaster();
            if (!caster)
                return;

            caster->RemoveAurasDueToSpell(SPELL_PRIEST_SHADOWFORM_VISUAL_WITH_GLYPH);
            caster->CastSpell(caster, SPELL_PRIEST_SHADOWFORM_VISUAL_WITHOUT_GLYPH, true);
        }

        void Register() override
        {
            OnEffectApply += AuraEffectApplyFn(spell_pri_glyph_of_shadow_AuraScript::HandleApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            OnEffectRemove += AuraEffectRemoveFn(spell_pri_glyph_of_shadow_AuraScript::HandleRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_pri_glyph_of_shadow_AuraScript();
    }
};

// Shadow Mend heal - 186263
class spell_pri_shadow_mend : public SpellScript
{
    PrepareSpellScript(spell_pri_shadow_mend);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_PRIEST_SHADOW_MEND_AURA });
    }

    void ApplyAura(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        if (caster->HasAura(SPELL_PRIEST_ATONEMENT) && !caster->HasAura(SPELL_PRIEST_TRINITY))
            caster->CastSpell(target, SPELL_PRIEST_ATONEMENT_AURA, true);

        if (caster->GetGUID() == target->GetGUID() && caster->HasAura(SPELL_PRIEST_MASOCHISM))
        {
            //50% of Heal of Shadow Mend and 10 ticks
            caster->CastCustomSpell(SPELL_PRIEST_MASOCHISM_HEAL, SPELLVALUE_BASE_POINT0, GetHitHeal() * 0.5f / 10, caster, TRIGGERED_FULL_MASK);
            return;
        }

		if (target->IsInCombat())
			caster->CastCustomSpell(SPELL_PRIEST_SHADOW_MEND_AURA, SPELLVALUE_BASE_POINT0, GetHitHeal() * 0.5f, target, TRIGGERED_FULL_MASK);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_pri_shadow_mend::ApplyAura, EFFECT_0, SPELL_EFFECT_HEAL);
    }
};

// Shadow Mend aura - 187464
class spell_pri_shadow_mend_aura : public AuraScript
{
	PrepareAuraScript(spell_pri_shadow_mend_aura);

	int32 damageThreshold = 0;

	bool CheckProc(ProcEventInfo& eventInfo)
	{
		Unit* target = eventInfo.GetActionTarget();

		if (!target)
			return false;

		if (!eventInfo.GetDamageInfo())
			return false;

		damageThreshold -= eventInfo.GetDamageInfo()->GetDamage();

		if (Aura* shadowMendAura = GetAura())
			if (damageThreshold <= 0)
				shadowMendAura->SetDuration(1);

		return true;
	}

	void HandlePeriodic(AuraEffect const* aurEff)
	{
		Unit* caster = GetCaster();
		Unit* target = GetTarget();
		if (!caster || !target)
			return;

		if (!target->IsInCombat())
			GetAura()->Remove();
		else
			target->CastCustomSpell(SPELL_PRIEST_SHADOW_MEND_DAMAGE, SPELLVALUE_BASE_POINT0, aurEff->GetAmount(), target, TRIGGERED_FULL_MASK, NULL, NULL, caster->GetGUID());
	}

	void CalcDamage(AuraEffect const* /*aurEff*/, int32& amount, bool& /*canBeRecalculated*/)
	{
		// Remaining damage gets added.
		damageThreshold += amount;
		amount = damageThreshold / 10;
	}

	void Register() override
	{
		DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_pri_shadow_mend_aura::CalcDamage, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
		DoCheckProc += AuraCheckProcFn(spell_pri_shadow_mend_aura::CheckProc);
		OnEffectPeriodic += AuraEffectPeriodicFn(spell_pri_shadow_mend_aura::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
	}
};

// Power Word: Radiance - 194509
class spell_pri_power_word_radiance : public SpellScriptLoader
{
public:
    spell_pri_power_word_radiance() : SpellScriptLoader("spell_pri_power_word_radiance") {}

    class spell_pri_power_word_radiance_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_pri_power_word_radiance_SpellScript);

        void ApplyAtonement(SpellEffIndex /*effIndex*/)
        {
            Unit* caster = GetCaster();
            Unit* target = GetHitUnit();
            if (!caster || !target)
                return;

            if (caster->HasAura(SPELL_PRIEST_ATONEMENT) && !caster->HasAura(SPELL_PRIEST_TRINITY))
                if (SpellInfo const* atonementInfo = sSpellMgr->GetSpellInfo(SPELL_PRIEST_ATONEMENT_AURA))
                {
                    auto eff3 = GetSpellInfo()->GetEffect(EFFECT_3);
                    int32 newDuration = CalculatePct(atonementInfo->GetDuration(), eff3.CalcValue());
                    caster->CastCustomSpell(SPELL_PRIEST_ATONEMENT_AURA, SPELLVALUE_DURATION, newDuration, target, TRIGGERED_FULL_MASK);
                }
        }

        void FilterTargets(std::list<WorldObject*>& targets)
        {
            auto eff2 = GetSpellInfo()->GetEffect(EFFECT_2);

            if (int32(targets.size()) > eff2.CalcValue())
                targets.resize(std::max(1, eff2.CalcValue()));
        }

        void Register() override
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_pri_power_word_radiance_SpellScript::FilterTargets, EFFECT_1, TARGET_UNIT_DEST_AREA_ALLY);
            OnEffectHitTarget += SpellEffectFn(spell_pri_power_word_radiance_SpellScript::ApplyAtonement, EFFECT_1, SPELL_EFFECT_HEAL);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_pri_power_word_radiance_SpellScript();
    }
};

// 20711 - Spirit of Redemption
class spell_pri_spirit_of_redemption : public AuraScript
{
    PrepareAuraScript(spell_pri_spirit_of_redemption);

    void CalculateAmount(AuraEffect const* /*auraEffect*/, int32& amount, bool& canBeRecalculated)
    {
        canBeRecalculated = true;
        amount = -1;
    }

    void Absorb(AuraEffect* /*auraEffect*/, DamageInfo& dmgInfo, uint32& absorbAmount)
    {
        Unit* caster = GetCaster();
        if (!caster || !caster->IsPlayer())
            return;

        if (dmgInfo.GetDamage() < caster->GetHealth())
        {
            absorbAmount = 0;
            return;
        }

        if (caster->HasAura(SPELL_PRIEST_SPIRIT_OF_REDEMPTION_SHAPESHIFT))
        {
            absorbAmount = 0;
            return;
        }

        absorbAmount = dmgInfo.GetDamage();
        //All spell are handle in Shapeshift Spell Aura Effect, incluse the remove stuff
        caster->CastSpell(caster, SPELL_PRIEST_SPIRIT_OF_REDEMPTION_UNTRANS_HERO, true);
        caster->CastSpell(caster, SPELL_PRIEST_SPIRIT_OF_REDEMPTION_SHAPESHIFT, true);

        if (Battleground* bg = caster->ToPlayer()->GetBattleground())
            if (Unit* attacker = dmgInfo.GetAttacker())
                if (attacker->IsPlayer())
                    bg->HandleKillPlayer(caster->ToPlayer(), attacker->ToPlayer());
    }

    void Register() override
    {
        DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_pri_spirit_of_redemption::CalculateAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
        OnEffectAbsorb += AuraEffectAbsorbFn(spell_pri_spirit_of_redemption::Absorb, EFFECT_0);
    }
};

// Atonement - 81749
class spell_pri_atonement : public AuraScript
{
    PrepareAuraScript(spell_pri_atonement);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_PRIEST_ATONEMENT_AURA, SPELL_PRIEST_ATONEMENT_HEAL });
    }

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetDamageInfo() && (eventInfo.GetDamageInfo()->GetDamageType() != HEAL && eventInfo.GetDamageInfo()->GetDamageType() != NODAMAGE))
            return true;

        return false;
    }

    void HandleProc(AuraEffect* aurEff, ProcEventInfo& eventInfo)
    {
		PreventDefaultAction();
        Unit* caster = GetCaster();
        if (!caster)
            return;

        uint32 heal = CalculatePct(eventInfo.GetDamageInfo()->GetDamage(), GetAura()->GetEffect(EFFECT_0)->CalculateAmount(caster));

		std::list<Unit*> units;
		caster->GetFriendlyUnitListInRange(units, 100.f);
		units.remove_if([caster](Unit* unit) 
		{
			return (!unit->HasAura(SPELL_PRIEST_ATONEMENT_AURA, caster->GetGUID()));
		});

		for (Unit* unit : units)
			caster->CastCustomSpell(SPELL_PRIEST_ATONEMENT_HEAL, SPELLVALUE_BASE_POINT0, heal, unit, TRIGGERED_FULL_MASK);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_pri_atonement::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_pri_atonement::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

// Atonement Aura - 194384
class spell_pri_atonement_aura : public AuraScript
{
    PrepareAuraScript(spell_pri_atonement_aura);

    void HandleApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* caster = GetCaster())
        {
            // Sins of the many
            if (Aura* aura = caster->GetAura(SPELL_PRIEST_SINS_OF_THE_MANY))
                aura->RecalculateAmountOfEffects();
        }
    }

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* caster = GetCaster())
        {
            // Sins of the many
            if (Aura* aura = caster->GetAura(SPELL_PRIEST_SINS_OF_THE_MANY))
                aura->RecalculateAmountOfEffects();
        }
    }

    void Register() override
    {
        AfterEffectApply += AuraEffectApplyFn(spell_pri_atonement_aura::HandleApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        AfterEffectRemove += AuraEffectRemoveFn(spell_pri_atonement_aura::HandleRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

// Angelic Feather - 121536
class spell_pri_angelic_feather : public SpellScriptLoader
{
public:
    spell_pri_angelic_feather() : SpellScriptLoader("spell_pri_angelic_feather") {}

    class spell_pri_angelic_feather_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_pri_angelic_feather_SpellScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            return ValidateSpellInfo({ SPELL_PRIEST_ANGELIC_FEATHER_TRIGGER, SPELL_PRIEST_ANGELIC_FEATHER_AREATRIGGER });
        }

        void HandleEffectDummy(SpellEffIndex /*effIndex*/)
        {
            Position destPos = GetHitDest()->GetPosition();
            float radius = GetEffectInfo().CalcRadius();

            // Caster is prioritary
            if (GetCaster()->IsWithinDist2d(&destPos, radius))
            {
                GetCaster()->CastSpell(GetCaster(), SPELL_PRIEST_ANGELIC_FEATHER_AURA, true);
            }
            else
            {
                GetCaster()->CastSpell(destPos, sSpellMgr->GetSpellInfo(SPELL_PRIEST_ANGELIC_FEATHER_AREATRIGGER)->Id, true);
            }
        }

        void Register() override
        {
            OnEffectHit += SpellEffectFn(spell_pri_angelic_feather_SpellScript::HandleEffectDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_pri_angelic_feather_SpellScript();
    }
};

// Smite Absorb - 208771
class spell_pri_smite_absorb : public SpellScriptLoader
{
public:
    spell_pri_smite_absorb() : SpellScriptLoader("spell_pri_smite_absorb") {}

    class spell_pri_smite_absorb_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_pri_smite_absorb_AuraScript);

        void HandleAbsorb(AuraEffect* /*aurEff*/, DamageInfo& dmgInfo, uint32& absorbAmount)
        {
            Unit* caster = GetCaster();
            Unit* attacker = dmgInfo.GetAttacker();
            if (!caster || !attacker)
                return;

            if (!attacker->HasAura(SPELL_PRIEST_SMITE_AURA, caster->GetGUID()))
                absorbAmount = 0;
            else
            {
                if (Aura* aur = attacker->GetAura(SPELL_PRIEST_SMITE_AURA, caster->GetGUID()))
                {
                    if (AuraEffect* aurEff = aur->GetEffect(EFFECT_0))
                    {
                        aurEff->SetAmount(aurEff->GetAmount() - dmgInfo.GetDamage());
                        aur->SetNeedClientUpdateForTargets();
                        if (aurEff->GetAmount() <= 0)
                            aur->SetDuration(1);
                    }
                }
            }
        }

        void Register() override
        {
            OnEffectAbsorb += AuraEffectAbsorbFn(spell_pri_smite_absorb_AuraScript::HandleAbsorb, EFFECT_0);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_pri_smite_absorb_AuraScript();
    }
};

// Focused Will - 45243
class spell_pri_focused_will : public SpellScriptLoader
{
public:
    spell_pri_focused_will() : SpellScriptLoader("spell_pri_focused_will") {}

    class spell_pri_focused_will_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_pri_focused_will_AuraScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_PRIEST_FOCUSED_WILL_BUFF))
                return false;
            return true;
        }

        bool HandleProc(ProcEventInfo& eventInfo)
        {
            Unit* caster = GetCaster();
            if (!caster)
                return false;
            if (auto damageInfo = eventInfo.GetDamageInfo())
            {
                switch (damageInfo->GetAttackType())
                {
                case BASE_ATTACK:
                case OFF_ATTACK:
                    caster->CastSpell(caster, SPELL_PRIEST_FOCUSED_WILL_BUFF, true);
                    return true;
                default:
                    break;
                }
            }

            return false;
        }

        void PreventAction(AuraEffect* /*aurEff*/, ProcEventInfo& /*eventInfo*/)
        {
            PreventDefaultAction();
        }

        void Register() override
        {
            DoCheckProc += AuraCheckProcFn(spell_pri_focused_will_AuraScript::HandleProc);
            OnEffectProc += AuraEffectProcFn(spell_pri_focused_will_AuraScript::PreventAction, EFFECT_0, SPELL_AURA_PROC_TRIGGER_SPELL);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_pri_focused_will_AuraScript();
    }
};

// Void Bolt - 234746
class spell_pri_void_bolt : public SpellScript
{
    PrepareSpellScript(spell_pri_void_bolt);

    void HandleEffectScriptEffect(SpellEffIndex /*effIndex*/)
    {
        if (Aura* voidBoltDurationBuffAura = GetCaster()->GetAura(SPELL_PRIEST_VOID_BOLT_DURATION))
        {
            if (Unit* unit = GetHitUnit())
            {
                uint32 durationIncreaseMs = voidBoltDurationBuffAura->GetEffect(EFFECT_0)->GetBaseAmount();

                if (Aura* pain = unit->GetAura(SPELL_PRIEST_SHADOW_WORD_PAIN, GetCaster()->GetGUID()))
                    pain->ModDuration(durationIncreaseMs);

                if (Aura* vampiricTouch = unit->GetAura(SPELL_PRIEST_VAMPIRIC_TOUCH, GetCaster()->GetGUID()))
                    vampiricTouch->ModDuration(durationIncreaseMs);
            }
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_pri_void_bolt::HandleEffectScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
    }
};

// 263165 - Void Torrent
class aura_pri_void_torrent : public AuraScript
{
    PrepareAuraScript(aura_pri_void_torrent);

    void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* caster = GetCaster())
            caster->CastSpell(caster, SPELL_PRIEST_VOID_TORRENT_PREVENT_REGEN, true);
    }

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* caster = GetCaster())
            caster->RemoveAurasDueToSpell(SPELL_PRIEST_VOID_TORRENT_PREVENT_REGEN);
    }

    void Register() override
    {
        AfterEffectApply += AuraEffectApplyFn(aura_pri_void_torrent::OnApply, EFFECT_1, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        AfterEffectRemove += AuraEffectRemoveFn(aura_pri_void_torrent::HandleRemove, EFFECT_1, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

// 198068 - Power Of The Dark Side
class spell_pri_power_of_the_dark_side : public AuraScript
{
    PrepareAuraScript(spell_pri_power_of_the_dark_side);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && (eventInfo.GetSpellInfo()->Id == SPELL_PRIEST_SHADOW_WORD_PAIN || eventInfo.GetSpellInfo()->Id == SPELL_PRIEST_PURGE_THE_WICKED);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_pri_power_of_the_dark_side::CheckProc);
    }
};


// Angelic Feather areatrigger - created by SPELL_PRIEST_ANGELIC_FEATHER_AREATRIGGER
// AreaTriggerID - 337
struct at_pri_angelic_feather : AreaTriggerAI
{
    at_pri_angelic_feather(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger) { }

    void OnInitialize() override
    {
        if (Unit* caster = at->GetCaster())
        {
            std::vector<AreaTrigger*> areaTriggers = caster->GetAreaTriggers(SPELL_PRIEST_ANGELIC_FEATHER_AREATRIGGER);

            if (areaTriggers.size() >= 3)
                areaTriggers.front()->SetDuration(0);
        }
    }

    void OnUnitEnter(Unit* unit) override
    {
        if (Unit* caster = at->GetCaster())
        {
            if (caster->IsFriendlyTo(unit) && unit->IsPlayer())
            {
                // If target already has aura, increase duration to max 130% of initial duration
                caster->CastSpell(unit, SPELL_PRIEST_ANGELIC_FEATHER_AURA, true);
                at->SetDuration(0);
            }
        }
    }
};

// Power Word: Barrier - 62618
// AreaTriggerID - 1489
struct at_pri_power_word_barrier : AreaTriggerAI
{
    at_pri_power_word_barrier(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger) { }

    void OnUnitEnter(Unit* unit) override
    {
        Unit* caster = at->GetCaster();

        if (!caster || !unit)
            return;

        if (!caster->ToPlayer())
            return;

        if (caster->IsFriendlyTo(unit))
            caster->CastSpell(unit, SPELL_PRIEST_POWER_WORD_BARRIER_BUFF, true);
    }

    void OnUnitExit(Unit* unit) override
    {
        Unit* caster = at->GetCaster();

        if (!caster || !unit)
            return;

        if (!caster->ToPlayer())
            return;

        if (unit->HasAura(SPELL_PRIEST_POWER_WORD_BARRIER_BUFF, caster->GetGUID()))
            unit->RemoveAurasDueToSpell(SPELL_PRIEST_POWER_WORD_BARRIER_BUFF, caster->GetGUID());
    }
};

// 120517 - Halo
// AreaTriggerID - 3921
struct at_pri_halo : AreaTriggerAI
{
    at_pri_halo(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger) { }

    void OnUnitEnter(Unit* unit) override
    {
        if (Unit* caster = at->GetCaster())
        {
            if (caster->IsValidAssistTarget(unit))
                caster->CastSpell(unit, SPELL_PRIEST_HALO_HEAL, true);
            else if (caster->IsValidAttackTarget(unit))
                caster->CastSpell(unit, SPELL_PRIEST_HALO_DAMAGE, true);
        }
    }
};

// 110744 - Divine Star
// AreaTriggerID - 6700
struct at_pri_divine_star : AreaTriggerAI
{
    at_pri_divine_star(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger) { }

    void OnInitialize() override
    {
        Unit* caster = at->GetCaster();
        if (!caster)
            return;
        
        Position pos = caster->GetPosition();

        returnAt = false;
        at->MovePositionToFirstCollision(pos, 24.0f, 0.0f);
        at->SetDestination(pos, 1000);        
    }

    void OnUnitEnter(Unit* unit) override
    {
        if (Unit* caster = at->GetCaster())
        {
            if (caster->IsValidAssistTarget(unit))
                caster->CastSpell(unit, SPELL_PRIEST_DIVINE_STAR_HEAL, true);
            else if (caster->IsValidAttackTarget(unit))
                caster->CastSpell(unit, SPELL_PRIEST_DIVINE_STAR_DAMAGE, true);
        }
    }

    void OnDestinationReached() override
    {
        Unit* caster = at->GetCaster();
        if (!caster)
            return;

        //Return To Caster
        if (!returnAt)
        {
            returnAt = true;
            Position pos = caster->GetPosition();
            at->SetDestination(pos, at->GetDuration());
        }
    }

private:
    bool returnAt;
};

// 78203 - Shadowy Apparitions
class aura_pri_shadowy_apparitions : public AuraScript
{
    PrepareAuraScript(aura_pri_shadowy_apparitions);

    bool CheckPro(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == SPELL_PRIEST_SHADOW_WORD_PAIN && (eventInfo.GetHitMask() & PROC_HIT_CRITICAL))
            return true;

        return false;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();
        Unit* target = eventInfo.GetProcTarget();

        if (!caster || !target)
            return;

		if (caster->GetRaceMask() == RACE_PANDAREN_ALLIANCE || caster->GetRaceMask() == RACE_PANDAREN_HORDE || caster->GetRaceMask() == RACE_DARK_IRON_DWARF)
			caster->SendPlaySpellVisual(target->GetGUID(), 33589, 0, 0, 6.f, false);
        else if (caster->GetRaceMask() == RACE_GNOME || caster->GetRaceMask() == RACE_GOBLIN)
            caster->SendPlaySpellVisual(target->GetGUID(), 33577, 0, 0, 6.f, false);
		else
			caster->SendPlaySpellVisual(target->GetGUID(), 33573, 0, 0, 6.f, false);
        caster->CastSpell(target, SPELL_PRIEST_NPC_SHADOWY_APPARITION, true);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_pri_shadowy_apparitions::CheckPro);
        OnProc += AuraProcFn(aura_pri_shadowy_apparitions::HandleProc);
    }
};

// 148859 - Shadowy Apparitions Damage
class spell_pri_shadowy_apparitions_damage : public SpellScript
{
    PrepareSpellScript(spell_pri_shadowy_apparitions_damage);

    void HandleHitEffect(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        if (Aura* aura = caster->GetAura(SPELL_PRIEST_SPITEFUL_APPARITIONS_POWER))
            if (target->HasAura(SPELL_PRIEST_VAMPIRIC_TOUCH, caster->GetGUID()))
            {
                int32 damage = GetHitDamage();
                SetHitDamage(damage + aura->GetEffect(EFFECT_0)->GetAmount());
            }
    }
    
    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_pri_shadowy_apparitions_damage::HandleHitEffect, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

// 63733 - Holy Words
class aura_pri_holy_words : public AuraScript
{
	PrepareAuraScript(aura_pri_holy_words);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_PRIEST_HOLY_WORD_SERENITY, SPELL_PRIEST_HOLY_WORD_CHASTISE });
    }

	bool CheckProc(ProcEventInfo& eventInfo)
	{
		Unit* caster = GetCaster();
		if (!caster)
			return false;

		if (eventInfo.GetSpellInfo() && (eventInfo.GetSpellInfo()->Id == SPELL_PRIEST_FLASH_HEAL || eventInfo.GetSpellInfo()->Id == SPELL_PRIEST_HEAL || eventInfo.GetSpellInfo()->Id == SPELL_PRIEST_SMITE))
			return true;

		return false;
	}

	void HandleProc(ProcEventInfo& eventInfo)
	{
		Unit* caster = GetCaster();
		if (!caster)
			return;

        uint32 reduction = 0;
        if (Aura* aura = caster->GetAura(SPELL_PRIEST_LIGHT_OF_THE_NAARU))
            reduction = aura->GetEffect(EFFECT_0)->GetBaseAmount();
        else if (Aura* aura = caster->GetAura(SPELL_PRIEST_APOTHEOSIS))
            reduction = aura->GetEffect(EFFECT_0)->GetBaseAmount();

		uint32 serenity_base = sSpellMgr->GetSpellInfo(SPELL_PRIEST_HOLY_WORD_SERENITY)->GetEffect(EFFECT_1).BasePoints;
		uint32 chastice_base = sSpellMgr->GetSpellInfo(SPELL_PRIEST_HOLY_WORD_CHASTISE)->GetEffect(EFFECT_1).BasePoints;

        uint32 serenity = serenity_base + CalculatePct(serenity_base, reduction);
        uint32 chastice = chastice_base + CalculatePct(chastice_base, reduction);

		if (eventInfo.GetSpellInfo() && (eventInfo.GetSpellInfo()->Id == SPELL_PRIEST_FLASH_HEAL || eventInfo.GetSpellInfo()->Id == SPELL_PRIEST_HEAL))
			caster->GetSpellHistory()->ReduceChargeCooldown(sSpellMgr->GetSpellInfo(SPELL_PRIEST_HOLY_WORD_SERENITY)->ChargeCategoryId, serenity * IN_MILLISECONDS);

		if (eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == SPELL_PRIEST_SMITE)
			caster->GetSpellHistory()->ModifyCooldown(SPELL_PRIEST_HOLY_WORD_CHASTISE, chastice * -1s);
	}

	void Register() override
	{
		DoCheckProc += AuraCheckProcFn(aura_pri_holy_words::CheckProc);
		OnProc += AuraProcFn(aura_pri_holy_words::HandleProc);
	}
};


// 132157 - Holy Nova
class spell_pri_holy_nova : public SpellScript
{
	PrepareSpellScript(spell_pri_holy_nova);

	bool Validate(SpellInfo const* /*spellInfo*/) override
	{
		return ValidateSpellInfo({ SPELL_PRIEST_HOLY_FIRE_AURA });
	}

	void HandleAfterHit()
	{
		Unit* caster = GetCaster();
		if (!caster)
			return;

		if (roll_chance_i(sSpellMgr->GetSpellInfo(SPELL_PRIEST_HOLY_FIRE_AURA)->GetEffect(EFFECT_0).BasePoints) && caster->HasAura(SPELL_PRIEST_HOLY_FIRE_AURA))
		{
			caster->AddAura(SPELL_PRIEST_HOLY_FIRE_PROC, caster);
			caster->GetSpellHistory()->ResetCooldown(SPELL_PRIEST_HOLY_FIRE, true);
		}
	}

	void Register() override
	{
		AfterHit += SpellHitFn(spell_pri_holy_nova::HandleAfterHit);
	}
};

// 33076 - Prayer of Mending
class spell_pri_prayer_of_mending : public SpellScript
{
    PrepareSpellScript(spell_pri_prayer_of_mending);

    void HandleOnCast()
    {
        Unit* caster = GetCaster();
        Unit* target = GetExplTargetUnit();
        if (!caster || !target)
            return;

        caster->SendPlaySpellVisual(target->GetGUID(), 38945, 0, 0, 40);
    }

    void HandleEffectHit(SpellEffIndex effIndex)
    {
        Unit* caster = GetCaster();
        Player* target = GetHitPlayer();

        if (!caster || !target)
            return;

        caster->CastSpell(target, SPELL_PRIEST_PRAYER_OF_MENDING_BUFF, true);
        if (Aura* aura = target->GetAura(SPELL_PRIEST_PRAYER_OF_MENDING_BUFF))
            aura->SetStackAmount(5);
    }

    void Register() override
    {
        OnCast += SpellCastFn(spell_pri_prayer_of_mending::HandleOnCast);
        OnEffectHitTarget += SpellEffectFn(spell_pri_prayer_of_mending::HandleEffectHit, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

// 155793 - Prayer of Mending Target Selector
class spell_pri_prayer_of_mending_target_selector : public SpellScript
{
    PrepareSpellScript(spell_pri_prayer_of_mending_target_selector);

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        Unit* caster = GetCaster();
        if (!caster)
            return;

        if (targets.size() > 0)
        {
            targets.remove_if([caster](WorldObject* unit)
            {
                if (!unit->ToUnit())
                    return true;

                if (!unit->ToPlayer())
                    return true;

                if (unit->GetGUID() == caster->GetGUID())
                    return true;

                if (!caster->IsValidAssistTarget(unit->ToUnit()))
                    return true;

                return false;
            });
            if (targets.size() > 1)
                Trinity::Containers::RandomResize(targets, 1);
        }
    }

    void HandleHit(SpellEffIndex effIndex)
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();

        if (!caster || !target)
            return;

        caster->SendPlaySpellVisual(target->GetGUID(), 38945, 0, 0, 40);
        caster->CastSpell(target, SPELL_PRIEST_PRAYER_OF_MENDING_BUFF, true);
        if (Aura* aura = target->GetAura(SPELL_PRIEST_PRAYER_OF_MENDING_BUFF))
            aura->SetStackAmount(GetSpellValue()->EffectBasePoints[0]);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_pri_prayer_of_mending_target_selector::HandleHit, EFFECT_0, SPELL_EFFECT_DUMMY);
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_pri_prayer_of_mending_target_selector::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ALLY);
    }
};

// 41635 - Prayer of Mending Aura
class aura_pri_prayer_of_mending_aura : public AuraScript
{
    PrepareAuraScript(aura_pri_prayer_of_mending_aura);

    void HandleApply(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        if (Unit* caster = GetCaster())
            GetAura()->GetEffect(EFFECT_0)->SetAmount(caster->GetTotalSpellPowerValue(SPELL_SCHOOL_MASK_HOLY, true) * 0.616f);
    }

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetDamageInfo() && (eventInfo.GetDamageInfo()->GetDamageType() != HEAL && eventInfo.GetDamageInfo()->GetDamageType() != NODAMAGE))
            return true;

        return false;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();

        Unit* caster = GetCaster();
        Unit* target = GetUnitOwner();
        if (!caster || !target)
            return;

        if (target->ToPlayer())
        {
            caster->CastSpell(target, SPELL_PRIEST_PRAYER_OF_MENDING_HEAL, true);
            if (Aura* aura = caster->GetAura(SPELL_PRIEST_BENEDICTION))
                if (roll_chance_i(aura->GetEffect(EFFECT_0)->GetBaseAmount()))
                    caster->CastSpell(target, SPELL_PRIEST_RENEW, true);

            // Find another raid or group member to jump.
            if (target->HasAura(SPELL_PRIEST_PRAYER_OF_MENDING_BUFF, caster->GetGUID()))
            {
                uint8 stacks = target->GetAura(SPELL_PRIEST_PRAYER_OF_MENDING_BUFF)->GetStackAmount() - 1;
                if (stacks > 0)
                    target->CastCustomSpell(SPELL_PRIEST_PRAYER_OF_MENDING_TARGET_SELECTOR, SPELLVALUE_BASE_POINT0, stacks, target, true, NULL, NULL, caster->GetGUID());
                target->RemoveAura(SPELL_PRIEST_PRAYER_OF_MENDING_BUFF);
            }
        }
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(aura_pri_prayer_of_mending_aura::HandleApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
        DoCheckProc += AuraCheckProcFn(aura_pri_prayer_of_mending_aura::CheckProc);
        OnProc += AuraProcFn(aura_pri_prayer_of_mending_aura::HandleProc);
    }
};

// 200128 - Trail of Light
class aura_pri_trail_of_light : public AuraScript
{
    PrepareAuraScript(aura_pri_trail_of_light);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == SPELL_PRIEST_FLASH_HEAL)
            return true;

        return false;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
		if (!GetAura() || !eventInfo.GetActionTarget())
			return;

		if (!GetAura()->Variables.Exist("LastFlashHealTarget"))
		{
			GetAura()->Variables.Set("LastFlashHealTarget", eventInfo.GetActionTarget()->GetGUID());
			return;
		}

		if (!eventInfo.GetHealInfo())
			return;

        if (Unit* caster = GetCaster())
            if(int32 heal = CalculatePct(eventInfo.GetHealInfo()->GetHeal(), GetAura()->GetEffect(EFFECT_0)->GetBaseAmount()))
			{
				ObjectGuid LastFlashHealTarget = GetAura()->Variables.GetValue<ObjectGuid>("LastFlashHealTarget");
				if (LastFlashHealTarget != ObjectGuid::Empty)
					if (Unit* target = ObjectAccessor::GetUnit(*caster, LastFlashHealTarget))
						if (caster->IsValidAssistTarget(target) && caster->IsWithinLOSInMap(target))
							caster->CastCustomSpell(SPELL_PRIEST_TRAIL_OF_LIGHT_HEAL, SPELLVALUE_BASE_POINT0, heal, target, true);
				GetAura()->Variables.Set("LastFlashHealTarget", eventInfo.GetActionTarget()->GetGUID());
			}
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_pri_trail_of_light::CheckProc);
        OnProc += AuraProcFn(aura_pri_trail_of_light::HandleProc);
    }
};

// 265202 - Holy Word: Salvation
class spell_pri_holy_word_salvation : public SpellScript
{
    PrepareSpellScript(spell_pri_holy_word_salvation);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_PRIEST_RENEW, SPELL_PRIEST_PRAYER_OF_MENDING_BUFF });
    }

    void HandleHit()
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();

        if (!caster || !target)
            return;

        caster->CastSpell(target, SPELL_PRIEST_RENEW, true);
        caster->SendPlaySpellVisual(target->GetGUID(), 38945, 0, 0, 40);
        caster->CastSpell(target, SPELL_PRIEST_PRAYER_OF_MENDING_BUFF, true);
        if (Aura* aura = target->GetAura(SPELL_PRIEST_PRAYER_OF_MENDING_BUFF, caster->GetGUID()))
            aura->SetStackAmount(sSpellMgr->GetSpellInfo(SPELL_PRIEST_HOLY_WORD_SALVATION)->GetEffect(EFFECT_1).BasePoints);
    }

    void Register() override
    {
        OnHit += SpellHitFn(spell_pri_holy_word_salvation::HandleHit);
    }
};

// 2050 - Holy Word: Serenity
class spell_pri_holy_word_serenity : public SpellScript
{
    PrepareSpellScript(spell_pri_holy_word_serenity);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_PRIEST_HOLY_WORD_SALVATION });
    }

    void HandleHit()
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        if (caster->HasAura(SPELL_PRIEST_ENDURING_RENEWAL) && target->HasAura(SPELL_PRIEST_RENEW, caster->GetGUID()))
        {
            Aura* aura = target->GetAura(SPELL_PRIEST_RENEW, caster->GetGUID());
            if (aura)
                aura->SetDuration(aura->GetMaxDuration());
        }
    }

    void HandleAfterCast()
    {
        if (Unit* caster = GetCaster())
        {
            caster->GetSpellHistory()->ModifyCooldown(SPELL_PRIEST_HOLY_WORD_SALVATION, -30s);

            // Cosmic Ripple
            if (caster->HasAura(SPELL_PRIEST_COSMIC_RIPPLE))
                caster->Variables.Set("CosmicRippleSerenity", true);

            caster->RemoveAurasDueToSpell(SPELL_PRIEST_INNER_FOCUS_CRIT);
        }
    }

    void CalcCritChance(Unit const* /*victim*/, float& chance)
    {
        if (Unit* caster = GetCaster())
            if (caster->HasAura(SPELL_PRIEST_INNER_FOCUS_CRIT))
                chance = 100;
    }

    void Register() override
    {
        OnHit += SpellHitFn(spell_pri_holy_word_serenity::HandleHit);
        AfterCast += SpellCastFn(spell_pri_holy_word_serenity::HandleAfterCast);
        OnCalcCritChance += SpellOnCalcCritChanceFn(spell_pri_holy_word_serenity::CalcCritChance);
    }
};

// 162452 - Shadowy Insight
class aura_pri_shadowy_insigth : public AuraScript
{
	PrepareAuraScript(aura_pri_shadowy_insigth);

	bool Validate(SpellInfo const* /*spellInfo*/) override
	{
		return ValidateSpellInfo({ SPELL_PRIEST_MIND_BLAST });
	}

	bool CheckPro(ProcEventInfo& eventInfo)
	{
		if (eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == SPELL_PRIEST_SHADOW_WORD_PAIN && (eventInfo.GetDamageInfo() && (eventInfo.GetDamageInfo()->GetDamageType() & DOT)))
			return true;

		return false;
	}

	void HandleProc(ProcEventInfo& eventInfo)
	{
		if (Unit* caster = GetCaster())
			caster->GetSpellHistory()->ResetCharges(sSpellMgr->GetSpellInfo(SPELL_PRIEST_MIND_BLAST)->ChargeCategoryId);
	}

	void Register() override
	{
		DoCheckProc += AuraCheckProcFn(aura_pri_shadowy_insigth::CheckPro);
		OnProc += AuraProcFn(aura_pri_shadowy_insigth::HandleProc);
	}
};

// 8092 - Mind Blast
class spell_pri_mind_blast : public SpellScript
{
	PrepareSpellScript(spell_pri_mind_blast);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_PRIEST_PSYCHIC_LINK });
    }

    void HandleEffectHit(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetExplTargetUnit();
        if (!caster || !target)
            return;

        if (caster->HasAura(SPELL_PRIEST_PSYCHIC_LINK))
        {
            int32 damage = GetHitDamage();
            caster->CastCustomSpell(SPELL_PRIEST_PSYCHIC_LINK_DAMAGE, SPELLVALUE_BASE_POINT0, CalculatePct(damage, sSpellMgr->GetSpellInfo(SPELL_PRIEST_PSYCHIC_LINK)->GetEffect(EFFECT_0).BasePoints), target, true);
        }
    }

	void HandleAfterCast()
	{
		if (Unit* caster = GetCaster())
            if (caster->HasAura(SPELL_PRIEST_SHADOWY_INSIGHT) && caster->GetCurrentSpellCastTime(SPELL_PRIEST_MIND_BLAST) > 0)
                caster->GetSpellHistory()->RestoreCharge(sSpellMgr->GetSpellInfo(SPELL_PRIEST_MIND_BLAST)->ChargeCategoryId);
            else
			    caster->RemoveAurasDueToSpell(SPELL_PRIEST_SHADOWY_INSIGHT);
	}

	void Register() override
	{
        OnEffectHitTarget += SpellEffectFn(spell_pri_mind_blast::HandleEffectHit, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
		AfterCast += SpellCastFn(spell_pri_mind_blast::HandleAfterCast);
	}
};

// 280391 - Sins of the many
class aura_pri_sins_of_the_many : public AuraScript
{
	PrepareAuraScript(aura_pri_sins_of_the_many);

	void HandleApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
	{
		if (Unit* caster = GetCaster())
			caster->CastSpell(caster, SPELL_PRIEST_SINS_OF_THE_MANY, true);
	}

	void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
	{
		if (Unit* caster = GetCaster())
			caster->RemoveAura(SPELL_PRIEST_SINS_OF_THE_MANY);
	}

	void Register() override
	{
		OnEffectApply += AuraEffectApplyFn(aura_pri_sins_of_the_many::HandleApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
		OnEffectRemove += AuraEffectRemoveFn(aura_pri_sins_of_the_many::HandleRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
	}
};

// 280398 - Sins of the many buff
class aura_pri_sins_of_the_many_buff : public AuraScript
{
	PrepareAuraScript(aura_pri_sins_of_the_many_buff);

	void CalculateAmount(AuraEffect const* /*aurEff*/, int32& amount, bool& canBeRecalculated)
	{
		canBeRecalculated = true;

		if (Unit* caster = GetCaster())
		{
            counter = 0;
			uint8 base = 12;
			UnitList list;
			caster->GetFriendlyUnitListInRange(list, 100.f, true);
            for (Unit* unit : list)
                if (unit->HasAura(SPELL_PRIEST_ATONEMENT_AURA, caster->GetGUID()))
                    counter++;

            if (counter > 12)
                amount = 0;
            else
                amount = base - counter;
		}
	}

    void Register() override
    {
        DoEffectCalcAmount += AuraEffectCalcAmountFn(aura_pri_sins_of_the_many_buff::CalculateAmount, EFFECT_0, SPELL_AURA_ADD_PCT_MODIFIER);
        DoEffectCalcAmount += AuraEffectCalcAmountFn(aura_pri_sins_of_the_many_buff::CalculateAmount, EFFECT_1, SPELL_AURA_ADD_PCT_MODIFIER);
        DoEffectCalcAmount += AuraEffectCalcAmountFn(aura_pri_sins_of_the_many_buff::CalculateAmount, EFFECT_2, SPELL_AURA_MOD_SUMMON_DAMAGE);
    }

private:
    uint8 counter = 0;
};

// 238136 - Cosmic Ripple
class aura_pri_cosmic_ripple : public AuraScript
{
    PrepareAuraScript(aura_pri_cosmic_ripple);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_PRIEST_HOLY_WORD_SERENITY, SPELL_PRIEST_HOLY_WORD_SANCTIFY });
    }

    void HandleApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* caster = GetCaster())
        {
            if (!caster->GetSpellHistory()->IsReady(sSpellMgr->GetSpellInfo(SPELL_PRIEST_HOLY_WORD_SERENITY)))
                caster->Variables.Set("CosmicRippleSerenity", true);
            if (!caster->GetSpellHistory()->IsReady(sSpellMgr->GetSpellInfo(SPELL_PRIEST_HOLY_WORD_SANCTIFY)))
                caster->Variables.Set("CosmicRippleSantify", true);
        }
    }

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* caster = GetCaster())
        {
            caster->Variables.Set("CosmicRippleSantify", false);
            caster->Variables.Set("CosmicRippleSerenity", false);
        }
    }

    void Register() override
    {
        AfterEffectRemove += AuraEffectRemoveFn(aura_pri_cosmic_ripple::HandleRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        AfterEffectApply += AuraEffectApplyFn(aura_pri_cosmic_ripple::HandleApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

// 243241 - Cosmic Ripple Heal
class spell_pri_cosmic_ripple_heal : public SpellScript
{
    PrepareSpellScript(spell_pri_cosmic_ripple_heal);

    void HandleOnObjectAreaTargetSelect(std::list<WorldObject*>& targets)
    {
        if (Unit* caster = GetCaster())
        {
            targets.remove_if([caster](WorldObject* obj)
            {
                if (caster->GetGUID() == obj->GetGUID())
                    return true;

                return false;
            });

            targets.sort(Trinity::ObjectDistanceOrderPred(caster));
            if (targets.size() > 5)
                targets.resize(5);
        }
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_pri_cosmic_ripple_heal::HandleOnObjectAreaTargetSelect, EFFECT_0, TARGET_UNIT_DEST_AREA_ALLY);
    }
};

// 2060 - Heal / 2061 - Flash Heal
class spell_pri_heal : public SpellScript
{
    PrepareSpellScript(spell_pri_heal);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_PRIEST_ENDURING_RENEWAL, SPELL_PRIEST_RENEW, SPELL_PRIEST_INNER_FOCUS_CRIT, SPELL_PRIEST_SURGE_OF_LIGHT_BUFF });
    }

    void HandleHit()
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        int32 heal = GetHitHeal();
        if (caster->HasAura(SPELL_PRIEST_ENDURING_RENEWAL) && target->HasAura(SPELL_PRIEST_RENEW, caster->GetGUID()))
        {
            Aura* aura = target->GetAura(SPELL_PRIEST_RENEW, caster->GetGUID());
            if (aura)
                aura->SetDuration(aura->GetMaxDuration());
        }

        // Everlasting Light.
        if (Aura* aura = caster->GetAura(SPELL_PRIEST_EVERLASTING_LIGHT))
        {
            float maxMana = caster->GetMaxPower(POWER_MANA);
            float currentMana = caster->GetPower(POWER_MANA);
            uint32 maxHeal = aura->GetEffect(EFFECT_0)->GetAmount();
            uint32 currentHeal = uint32(maxHeal * (1.f - currentMana / maxMana));
            SetHitHeal(heal + currentHeal);
        }
    }

    void CalcCritChance(Unit const* /*victim*/, float& chance)
    {
        if (Unit* caster = GetCaster())
            if (caster->HasAura(SPELL_PRIEST_INNER_FOCUS_CRIT))
                chance = 100;
    }

    void HandleAfterCast()
    {
        if (Unit* caster = GetCaster())
            caster->RemoveAurasDueToSpell(SPELL_PRIEST_INNER_FOCUS_CRIT);
    }

    void Register() override
    {
        OnHit += SpellHitFn(spell_pri_heal::HandleHit);
        OnCalcCritChance += SpellOnCalcCritChanceFn(spell_pri_heal::CalcCritChance);
        AfterCast += SpellCastFn(spell_pri_heal::HandleAfterCast);
    }
};

// 246287 - Evangelism
class spell_prist_evangelism : public SpellScript
{
    PrepareSpellScript(spell_prist_evangelism);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_PRIEST_EVANGELISM, SPELL_PRIEST_ATONEMENT_AURA });
    }

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        if (Unit* caster = GetCaster())
            targets.remove_if(Trinity::UnitAuraCheck(false, SPELL_PRIEST_ATONEMENT_AURA, caster->GetGUID()));
    }

    void HandleHit()
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        if (Aura* aura = target->GetAura(SPELL_PRIEST_ATONEMENT_AURA, caster->GetGUID()))
            aura->ModDuration(sSpellMgr->GetSpellInfo(SPELL_PRIEST_EVANGELISM)->GetEffect(EFFECT_0).BasePoints * IN_MILLISECONDS);
    }

    void Register() override
    {
        OnHit += SpellHitFn(spell_prist_evangelism::HandleHit);
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_prist_evangelism::FilterTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ALLY);
    }
};

// 271466 - Luminous Barrier
class aura_pri_luminous_barrier : public AuraScript
{
    PrepareAuraScript(aura_pri_luminous_barrier);

    void CalculateAmount(AuraEffect const* /*aurEff*/, int32& amount, bool& /*canBeRecalculated*/)
    {
        if (Unit* caster = GetCaster())
        {
            int32 absorbAmount = int32(2.8f * caster->SpellBaseHealingBonusDone(GetSpellInfo()->GetSchoolMask()));
            amount += absorbAmount;
        }
    }

    void Register() override
    {
        DoEffectCalcAmount += AuraEffectCalcAmountFn(aura_pri_luminous_barrier::CalculateAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
    }
};

// 196762 - Inner Focus
class spell_pri_inner_focus : public SpellScript
{
    PrepareSpellScript(spell_pri_inner_focus);

    void HandleOnHit()
    {
        if (Unit* caster = GetCaster())
            caster->CastSpell(caster, SPELL_PRIEST_INNER_FOCUS, true);
    }

    void Register() override
    {
        OnHit += SpellHitFn(spell_pri_inner_focus::HandleOnHit);
    }
};

// 14914 - Holy Fire
class spell_pri_holy_fire : public SpellScript
{
    PrepareSpellScript(spell_pri_holy_fire);

    void CalcCritChance(Unit const* /*victim*/, float& chance)
    {
        if (Unit* caster = GetCaster())
            if (caster->HasAura(SPELL_PRIEST_INNER_FOCUS_CRIT))
                chance = 100;
    }

    void HandleAfterCast()
    {
        if (Unit* caster = GetCaster())
            caster->RemoveAurasDueToSpell(SPELL_PRIEST_INNER_FOCUS_CRIT);
    }

    void Register() override
    {
        OnCalcCritChance += SpellOnCalcCritChanceFn(spell_pri_holy_fire::CalcCritChance);
        AfterCast += SpellCastFn(spell_pri_holy_fire::HandleAfterCast);
    }
};

// 14914 - Holy Fire (Aura)
class aura_pri_holy_fire : public AuraScript
{
    PrepareAuraScript(aura_pri_holy_fire);

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
        // Sacred Flame.
        if (Unit* caster = GetCaster())
            if (Aura* aura = caster->GetAura(SPELL_PRIEST_SACRED_FLAME_POWER))
                caster->CastCustomSpell(SPELL_PRIEST_SACRED_FLAME_ENERGIZE, SPELLVALUE_BASE_POINT0, aura->GetEffect(EFFECT_1)->GetAmount(), caster, true);
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(aura_pri_holy_fire::HandlePeriodic, EFFECT_1, SPELL_AURA_PERIODIC_DAMAGE);
    }
};

// 109186 - Surge of Light Aura
class aura_pri_surge_of_light_aura : public AuraScript
{
    PrepareAuraScript(aura_pri_surge_of_light_aura);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_PRIEST_SURGE_OF_LIGHT, SPELL_PRIEST_SMITE, SPELL_PRIEST_SURGE_OF_LIGHT_BUFF });
    }

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        uint8 chance = sSpellMgr->GetSpellInfo(SPELL_PRIEST_SURGE_OF_LIGHT)->GetEffect(EFFECT_0).BasePoints;
        if (eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == SPELL_PRIEST_SMITE && roll_chance_i(chance))
            return true;

        if (eventInfo.GetHealInfo() && eventInfo.GetHealInfo()->GetHeal() > 0 && roll_chance_i(chance))
            return true;

        return false;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (Unit* caster = GetCaster())
            caster->CastSpell(caster, SPELL_PRIEST_SURGE_OF_LIGHT_BUFF, true);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_pri_surge_of_light_aura::CheckProc);
        OnProc += AuraProcFn(aura_pri_surge_of_light_aura::HandleProc);
    }
};

// 64129 - Body and Soul
class aura_pri_body_and_soul : public AuraScript
{
    PrepareAuraScript(aura_pri_body_and_soul);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetSpellInfo() && (eventInfo.GetSpellInfo()->Id == SPELL_PRIEST_POWER_WORD_SHIELD || eventInfo.GetSpellInfo()->Id == SPELL_PRIEST_LEAP_OF_FAITH))
            return true;

        return false;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_pri_body_and_soul::CheckProc);
    }
};

// Shadowfiend / Mindbender - 19668 / 62982
class npc_pet_priest_fiend : public ScriptedAI
{
public:
	npc_pet_priest_fiend(Creature* creature) : ScriptedAI(creature) {}

	void IsSummonedBy(WorldObject* owner) override
	{
		if (!owner || !owner->IsUnit())
			return;

        // Shadowform visual
        me->CastSpell(me, 63359, true);

        if (!owner->ToUnit()->GetTarget().IsEmpty())
        {
            targetGUID = owner->ToUnit()->GetTarget();
            me->GetAI()->AttackStart(ObjectAccessor::GetUnit(*owner, targetGUID));
        }
	}

	void UpdateAI(uint32 diff) override
	{
		Unit* owner = me->GetOwner();
		if (!owner)
			return;

		if (me->IsInEvadeMode() && !owner->IsInCombat())
			return;

		Unit* target = GetTarget();
		ObjectGuid newtargetGUID = owner->GetTarget();
        if (newtargetGUID.IsEmpty() || newtargetGUID == targetGUID)
            if (me->IsValidAttackTarget(target) && me->CanSeeOrDetect(target))
            {
                me->GetAI()->AttackStart(target);
                DoMeleeAttackIfReady();
                return;
            }

		if (Unit* newTarget = ObjectAccessor::GetUnit(*me, newtargetGUID))
            if (target != newTarget && me->IsValidAttackTarget(newTarget) && me->CanSeeOrDetect(newTarget) && owner->IsInCombat())
            {
                target = newTarget;
                me->GetAI()->AttackStart(target);
                DoMeleeAttackIfReady();
                return;
            }

        EnterEvadeMode(EVADE_REASON_NO_HOSTILES);
	}

	void EnterEvadeMode(EvadeReason /*reason*/) override
	{
		if (me->IsInEvadeMode() || !me->IsAlive())
			return;

		Unit* owner = me->GetOwner();

		me->SetReactState(REACT_ASSIST);
		me->CombatStop(true);
		if (owner && !me->HasUnitState(UNIT_STATE_FOLLOW))
		{
			me->GetMotionMaster()->Clear();
			me->GetMotionMaster()->MoveFollow(owner, PET_FOLLOW_DIST, me->GetFollowAngle(), MovementSlot::MOTION_SLOT_ACTIVE);
		}
	}

private:
	Unit * GetTarget() const
	{
		return ObjectAccessor::GetUnit(*me, targetGUID);
	}

	ObjectGuid targetGUID;
};

// 211522 - Psyfiend
class spell_pri_psyfiend : public SpellScript
{
	PrepareSpellScript(spell_pri_psyfiend);

	void HandleTargetHit(SpellEffIndex /*effIndex*/)
	{
		Unit* caster = GetCaster();
		Unit* target = GetExplTargetUnit();
		if (!caster || !target)
			return;

        caster->Variables.Set<ObjectGuid>("CurrentTarget", target->GetGUID());
		caster->CastSpell(caster, SPELL_PRIEST_PSYFIEND_SUMMON, true);
	}

	void Register() override
	{
		OnEffectHit += SpellEffectFn(spell_pri_psyfiend::HandleTargetHit, EFFECT_0, SPELL_EFFECT_APPLY_AURA);
	}
};

// Psyfiend - 101398
class npc_pet_priest_psyfiend : public ScriptedAI
{
public:
    npc_pet_priest_psyfiend(Creature* creature) : ScriptedAI(creature) {}

    enum Spells
    {
        SPELL_PSYFLAY = 199845
    };

    void IsSummonedBy(WorldObject* owner) override
    {
        if (!owner)
            return;

        me->SetMaxHealth(10);

        // Set the target.
		targetGUID = owner->Variables.GetValue("CurrentTarget", ObjectGuid::Empty);
    }

    void UpdateAI(uint32 /*diff*/) override
    {
        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        Unit* target = GetTarget();
        if (target && me->IsValidAttackTarget(target) && (target->IsPlayer() || me->GetMap()->IsBattlegroundOrArena())) //Can be used in Alterac Valley agains boss
            me->CastSpell(target, SPELL_PSYFLAY, CastSpellExtraArgs(false).AddSpellBP0(1));
    }

private:
    Unit * GetTarget() const
    {
        return ObjectAccessor::GetUnit(*me, targetGUID);
    }

    ObjectGuid targetGUID;
};

// 263346 - Dark Void
class spell_pri_dark_void : public SpellScript
{
    PrepareSpellScript(spell_pri_dark_void);

    void HandleEffectHit(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        caster->CastSpell(target, SPELL_PRIEST_SHADOW_WORD_PAIN, true);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_pri_dark_void::HandleEffectHit, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

// 213634 - Purify Disease / 527 - Purify Last Update 8.0.1 Build 28153
class spell_pri_purify : public SpellScript
{
	PrepareSpellScript(spell_pri_purify);

	void OnSuccessfulDispel(SpellEffIndex /*effIndex*/)
	{
		Unit* caster = GetCaster();
		Unit* target = GetHitUnit();
		if (!caster || !target || !caster->IsPlayer())
			return;

        if (caster->HasAura(SPELL_PRIEST_PURIFIED_RESOLVE))
        {
            int32 bp = CalculatePct(target->GetMaxHealth(), sSpellMgr->GetSpellInfo(SPELL_PRIEST_PURIFIED_RESOLVE)->GetEffect(EFFECT_0).BasePoints);

            if (target->HasAura(SPELL_PRIEST_ATONEMENT_AURA))
                if (caster->HasAura(SPELL_PRIEST_GRACE))
                    bp += (bp * (caster->ToPlayer()->m_activePlayerData->Mastery / 100.0f));

            caster->CastCustomSpell(SPELL_PRIEST_PURIFIED_RESOLVE_SHIELD, SPELLVALUE_BASE_POINT0, bp, target, true);
        }			
	}

	void Register() override
	{
		OnEffectSuccessfulDispel += SpellEffectFn(spell_pri_purify::OnSuccessfulDispel, EFFECT_0, SPELL_EFFECT_DISPEL);
		OnEffectSuccessfulDispel += SpellEffectFn(spell_pri_purify::OnSuccessfulDispel, EFFECT_1, SPELL_EFFECT_DISPEL);
	}
};

// 199259 - Driven to Madness
class aura_pri_driven_to_madness : public AuraScript
{
	PrepareAuraScript(aura_pri_driven_to_madness);

	bool CheckProc(ProcEventInfo& eventInfo)
	{
		if (Unit* caster = GetCaster())
			if (!caster->HasAura(SPELL_PRIEST_VOIDFORM_BUFFS))
				return true;

		return false;
	}

	void Register() override
	{
		DoCheckProc += AuraCheckProcFn(aura_pri_driven_to_madness::CheckProc);
	}
};

// 47585 - Dispersion
class aura_pri_dispersion : public AuraScript
{
	PrepareAuraScript(aura_pri_dispersion);

	void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
	{
		if (Unit* caster = GetCaster())
			if (caster->HasAura(SPELL_PRIEST_PURE_SHADOW))
				caster->CastSpell(caster, SPELL_PRIEST_SUSTAINED_SANITY, true);
	}

    void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (Unit * caster = GetCaster())
            caster->RemoveMovementImpairingAuras(true);
    }

	void Register() override
	{
        OnEffectApply += AuraEffectApplyFn(aura_pri_dispersion::OnApply, EFFECT_1, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
		AfterEffectRemove += AuraEffectRemoveFn(aura_pri_dispersion::HandleRemove, EFFECT_1, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
	}
};

// 199486 - Psychic Link Damage
class spell_pri_psychic_link : public SpellScript
{
    PrepareSpellScript(spell_pri_psychic_link);

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        if (Unit* caster = GetCaster())
        {
            targets.remove_if(Trinity::UnitAuraCheck(false, SPELL_PRIEST_VAMPIRIC_TOUCH, caster->GetGUID()));
        }
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_pri_psychic_link::FilterTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ENEMY);
    }
};

// 204065 - Shadow Covenant
class spell_pri_shadow_covenant : public SpellScript
{
	PrepareSpellScript(spell_pri_shadow_covenant);

	void CacheMainTarget(WorldObject*& target)
	{
		if (target)
			mainTarget = target;
	}

	void FilterTargets(std::list<WorldObject*>& targets)
	{
		if (Unit* caster = GetCaster())
			if (Player* player = caster->ToPlayer())
			{
				if (mainTarget)
					targets.remove(mainTarget);
				targets.remove_if([player](WorldObject* target)
				{
					if (!target)
						return true;

					if (!target->ToUnit())
						return true;

					if (!target->ToPlayer())
						return true;

					if (!player->IsInSameGroupWith(target->ToPlayer()) && !player->IsInSameRaidWith(target->ToPlayer()))
						return true;

					if (target->ToUnit()->GetHealthPct() == 100)
						return true;

					return false;
				});
				if (targets.size() > 4)
					Trinity::Containers::RandomResize(targets, 4);
				targets.push_front(mainTarget);
			}
	}

	void HandleHit()
	{
		if (GetHitHeal() > 0)
			heal = GetHitHeal();
	}

	void HandleHitTarget()
	{
		Unit* caster = GetCaster();
		Unit* target = GetHitUnit();
		if (!caster || !target)
			return;

		caster->CastCustomSpell(SPELL_PRIEST_SHADOW_COVENANT_ABSORTION, SPELLVALUE_BASE_POINT0, heal * 0.5f, target, true);
	}

	void Register() override
	{
		OnObjectTargetSelect += SpellObjectTargetSelectFn(spell_pri_shadow_covenant::CacheMainTarget, EFFECT_0, TARGET_UNIT_TARGET_ALLY);
		OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_pri_shadow_covenant::FilterTargets, EFFECT_1, TARGET_UNIT_DEST_AREA_ALLY);
		OnHit += SpellHitFn(spell_pri_shadow_covenant::HandleHit);
		AfterHit += SpellHitFn(spell_pri_shadow_covenant::HandleHitTarget);
	}

private:
	WorldObject* mainTarget;
	int32 heal = 0;
};

// 197268 - Ray of Hope
class aura_pri_ray_of_hope : public AuraScript
{
    PrepareAuraScript(aura_pri_ray_of_hope);

    void HandleCalculateAbsorb(AuraEffect const* /*aurEff*/, int32& amount, bool& /*canBeRecalculated*/)
    {
        amount= -1;
    }

    void HandleCalculateAbsorb2(AuraEffect const* /*aurEff*/, int32& amount, bool& /*canBeRecalculated*/)
    {
        amount = -1;
    }

    void HandleAbsorbDamage(AuraEffect* /*aurEff*/, DamageInfo& dmgInfo, uint32& absorbAmount)
    {
        if (dmgInfo.GetDamage() > 0)
        {
            damageAbsorbed += dmgInfo.GetDamage();
            absorbAmount = dmgInfo.GetDamage();
        }
    }

    void HandleAbsorbHeal(AuraEffect* /*aurEff*/, DamageInfo& dmgInfo, uint32& absorbAmount)
    {
        if (dmgInfo.GetDamage() > 0)
        {
            healAbsorbed += dmgInfo.GetDamage();
            absorbAmount = dmgInfo.GetDamage();
        }
    }

    void HandleRemove(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /* mode */)
    {
        Unit* caster = GetCaster();
        Unit* owner = GetUnitOwner();
        if (!caster || !owner)
            return;

        caster->CastCustomSpell(SPELL_PRIEST_RAY_OF_HOPE_DAMAGE, SPELLVALUE_BASE_POINT0, damageAbsorbed, owner, true);
        caster->CastCustomSpell(SPELL_PRIEST_RAY_OF_HOPE_HEAL, SPELLVALUE_BASE_POINT0, healAbsorbed + CalculatePct(healAbsorbed, 50), owner, true);
    }

    void Register() override
    {
        DoEffectCalcAmount += AuraEffectCalcAmountFn(aura_pri_ray_of_hope::HandleCalculateAbsorb, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
        DoEffectCalcAmount += AuraEffectCalcAmountFn(aura_pri_ray_of_hope::HandleCalculateAbsorb2, EFFECT_1, SPELL_AURA_SCHOOL_HEAL_ABSORB);
        OnEffectAbsorb += AuraEffectAbsorbFn(aura_pri_ray_of_hope::HandleAbsorbDamage, EFFECT_0);
        OnEffectAbsorb += AuraEffectAbsorbFn(aura_pri_ray_of_hope::HandleAbsorbHeal, EFFECT_1);
        OnEffectRemove += AuraEffectRemoveFn(aura_pri_ray_of_hope::HandleRemove, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB, AURA_EFFECT_HANDLE_REAL);
    }

private:
    int32 healAbsorbed = 0;
    int32 damageAbsorbed = 0;
};

// 193223 - Surrender to Madness
class aura_pri_surrender_to_madness : public AuraScript
{
	PrepareAuraScript(aura_pri_surrender_to_madness);

	bool Validate(SpellInfo const* /*spellInfo*/) override
	{
		return ValidateSpellInfo({ SPELL_PRIEST_SURRENDER_TO_MADNESS });
	}

	void HandleRemove(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /* mode */)
	{
		if (Unit* caster = GetCaster())
		{
			caster->CastCustomSpell(SPELL_PRIEST_SURRENDER_TO_MADNESS_DAMAGE, SPELLVALUE_BASE_POINT0, CalculatePct(caster->GetMaxHealth(), sSpellMgr->GetSpellInfo(SPELL_PRIEST_SURRENDER_TO_MADNESS)->GetEffect(EFFECT_2).BasePoints), caster, true);
			caster->CastSpell(caster, SPELL_PRIEST_SURRENDERED_TO_MADNESS, true);
		}
	}

	void Register() override
	{
		OnEffectRemove += AuraEffectRemoveFn(aura_pri_surrender_to_madness::HandleRemove, EFFECT_2, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
	}
};

// 200196 - Holy Word: Chastise (Incapacitate)
class aura_pri_holy_word_chastise : public AuraScript
{
	PrepareAuraScript(aura_pri_holy_word_chastise);

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
		DoCheckProc += AuraCheckProcFn(aura_pri_holy_word_chastise::CheckProc);
		OnProc += AuraProcFn(aura_pri_holy_word_chastise::HandleProc);
	}
};

// 280711 - Dark Ascension
class spell_pri_dark_ascension : public SpellScript
{
	PrepareSpellScript(spell_pri_dark_ascension);

	bool Validate(SpellInfo const* /*spellInfo*/) override
	{
		return ValidateSpellInfo({ SPELL_PRIEST_DARK_ASCENSION });
	}

	void HandleCast()
	{
		if (Unit* caster = GetCaster())
		{
			caster->ModifyPower(POWER_INSANITY, sSpellMgr->GetSpellInfo(SPELL_PRIEST_DARK_ASCENSION)->GetEffect(EFFECT_1).BasePoints);
			if (!caster->HasAura(SPELL_PRIEST_VOIDFORM_BUFFS))
				caster->CastSpell(caster, SPELL_PRIEST_VOIDFORM_BUFFS, true);
			if (Player* player = caster->ToPlayer())
				if (Unit* target = player->GetSelectedUnit())
					if (caster->IsValidAttackTarget(target))
					{
						UnitList list;
						target->GetFriendlyUnitListInRange(list, 10);
						for (Unit* t : list)
							if (t && caster->IsValidAttackTarget(t))
								caster->CastSpell(t, SPELL_PRIEST_DARK_ASCENSION_DAMAGE, true);
					}
		}
	}

	void Register() override
	{
		OnCast += SpellCastFn(spell_pri_dark_ascension::HandleCast);
	}
};

// 193173 - Mania
class aura_pri_mania : public AuraScript
{
	PrepareAuraScript(aura_pri_mania);

	void HandleRemove(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /* mode */)
	{
		if (Unit* caster = GetCaster())
			caster->RemoveAura(SPELL_PRIEST_MANIA_SPEED);
	}

	void Register() override
	{
		OnEffectRemove += AuraEffectRemoveFn(aura_pri_mania::HandleRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
	}
};

// 280750 - Shadow Mania
class aura_pri_shadow_mania : public AuraScript
{
	PrepareAuraScript(aura_pri_shadow_mania);

	bool CheckProc(ProcEventInfo& eventInfo)
	{
		if (Unit* caster = GetCaster())
		{
			const SpellInfo* spellInfo = eventInfo.GetSpellInfo();
			if (spellInfo && caster->HasAura(SPELL_PRIEST_VOIDFORM_BUFFS) && !caster->HasAura(SPELL_PRIEST_SUSTAINED_SANITY))
			{
				for (auto effect : spellInfo->GetEffects())
				{
					if (effect.ApplyAuraName == SPELL_AURA_MOD_STUN || effect.ApplyAuraName == SPELL_AURA_MOD_FEAR ||
						effect.ApplyAuraName == SPELL_AURA_MOD_FEAR_2 || effect.ApplyAuraName == SPELL_AURA_MOD_SILENCE ||
						effect.Mechanic == MECHANIC_FEAR || effect.Mechanic == MECHANIC_STUN || effect.Mechanic == MECHANIC_SILENCE)
						return true;
				}
			}
		}

		return false;
	}

    void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Unit* caster = GetCaster();
        if (!caster)
            return;

        caster->RemoveAura(SPELL_PRIEST_SUSTAINED_SANITY);
    }

	void Register() override
	{
        DoCheckProc += AuraCheckProcFn(aura_pri_shadow_mania::CheckProc);
        OnEffectRemove += AuraEffectRemoveFn(aura_pri_shadow_mania::OnRemove, EFFECT_0, SPELL_AURA_PROC_TRIGGER_SPELL, AURA_EFFECT_HANDLE_REAL);
	}
};

// 281574 - Sustained Sanity
class aura_pri_sustained_sanity : public AuraScript
{
	PrepareAuraScript(aura_pri_sustained_sanity);

	void HandlePeriodic(AuraEffect const* /*aurEff*/)
	{
		if (Unit* caster = GetCaster())
            if (!caster->HasUnitState(UNIT_STATE_STUNNED) && !caster->HasUnitState(UNIT_STATE_FLEEING) && !caster->HasUnitFlag(UNIT_FLAG_SILENCED))
                Remove();		
	}

	void Register() override
	{
		OnEffectPeriodic += AuraEffectPeriodicFn(aura_pri_sustained_sanity::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
	}
};

// 215960 - Greater Heal
class aura_pri_greater_heal : public AuraScript
{
    PrepareAuraScript(aura_pri_greater_heal);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == SPELL_PRIEST_HEAL)
            return true;

        return false;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_pri_greater_heal::CheckProc);
    }
};

// 108968 - Void Shift
class spell_pri_void_shift : public SpellScript
{
    PrepareSpellScript(spell_pri_void_shift);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        if (!sSpellMgr->GetSpellInfo(SPELL_PRIEST_VOID_SHIFT))
            return false;
        return true;
    }

    SpellCastResult CheckTarget()
    {
        if (GetExplTargetUnit())
            if (GetExplTargetUnit()->GetTypeId() != TYPEID_PLAYER)
                return SPELL_FAILED_BAD_TARGETS;

        return SPELL_CAST_OK;
    }

    void HandleOnHit()
    {
        Unit* caster = GetCaster();
        Unit* target = GetExplTargetUnit();
        if (!caster || !target)
            return;

        SpellInfo const* spellInfo = GetSpellInfo();
        if (!spellInfo)
            return;

        uint8 percent = spellInfo->GetEffect(EFFECT_0).BasePoints;
        uint32 targetHealthPct = static_cast<int32>(target->GetHealthPct());
        uint32 casterHealthPct = static_cast<int32>(caster->GetHealthPct());

        if (casterHealthPct < percent || targetHealthPct < percent)
        {
            if (casterHealthPct < targetHealthPct)
                casterHealthPct = percent;
            else
                targetHealthPct = percent;
        }

        CastSwap(caster, target, static_cast<int32>(target->GetHealthPct()), casterHealthPct);
        CastSwap(caster, caster, static_cast<int32>(caster->GetHealthPct()), targetHealthPct);
    }

    void CastSwap(Unit* caster, Unit* target, int32 currentPct, int32 destPct)
    {
        int32 damage = 0;
        int32 heal = 0;

        if (currentPct < destPct)
            heal = CalculatePct(target->GetMaxHealth(), destPct - currentPct);
        else
            damage = CalculatePct(target->GetMaxHealth(), currentPct - destPct);

        caster->CastCustomSpell(target, SPELL_PRIEST_VOID_SHIFT_EFFECT, &damage, &heal, nullptr, true);
    }

    void Register() override
    {
        OnCheckCast += SpellCheckCastFn(spell_pri_void_shift::CheckTarget);
        OnHit += SpellHitFn(spell_pri_void_shift::HandleOnHit);
    }
};

// Last Update 8.0.1 28153
// Called by Holy Ward  213610
class spell_pri_holy_ward : public AuraScript
{
    PrepareAuraScript(spell_pri_holy_ward);

    bool HandleCheckProc(ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();
        DamageInfo* damageInfo = eventInfo.GetDamageInfo();
        if (!caster || !damageInfo)
            return false;

        SpellInfo const* spellInfo = damageInfo->GetSpellInfo();
        if (!spellInfo || !spellInfo->IsLossOfControl())
            return false;

        return true;
    }

    void HandleOnProc(ProcEventInfo& /* eventInfo */)
    {
        Unit* caster = GetCaster();
        Aura* aura = GetAura();
        if (!caster || !aura)
            return;

        aura->Remove();
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_pri_holy_ward::HandleCheckProc);
        OnProc += AuraProcFn(spell_pri_holy_ward::HandleOnProc);
    }
};

// Last Update 8.0.1 28153
// Called by 221661 Holy Concentration
class PlayerScript_Holy_Concentration : public PlayerScript
{
public:
    PlayerScript_Holy_Concentration() :PlayerScript("PlayerScript_Holy_Concentration") { }

    void OnSpellInterrupt(Player* player, Unit* source, Spell* spell, Spell* interruptingSpell)
    {
        if (!player)
            return;

        if (player->GetSpecializationId() != TALENT_SPEC_PRIEST_HOLY)
            return;

        if (!player->HasAura(SPELL_HOLY_CONCENTRATION_AURA))
            return;

        if (!interruptingSpell || !interruptingSpell->GetSpellInfo()->HasEffectMechanic(Mechanics::MECHANIC_INTERRUPT))
            return;

        if (!player->HasAura(SPELL_HOLY_CONCENTRATION_BUFF))
            player->CastSpell(player, SPELL_HOLY_CONCENTRATION_BUFF, true);
    }
};

// 32375 - Mass Dispel
class spell_pri_mass_dispel : public SpellScript
{
    PrepareSpellScript(spell_pri_mass_dispel);

    enum Spells
    {
        MASS_DISPELL_MECHANIC = 39897,
        MASS_DISPEL = 32375,
    };

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        if (!sSpellMgr->GetSpellInfo(MASS_DISPEL) || !sSpellMgr->GetSpellInfo(MASS_DISPELL_MECHANIC))
            return false;
        return true;
    }

    void HandleOnCast()
    {
        if (Player * player = GetCaster()->ToPlayer())
        {
            const WorldLocation* loc = GetExplTargetDest();
            player->CastSpell(Position(loc->GetPositionX(), loc->GetPositionY(), loc->GetPositionZ()), MASS_DISPELL_MECHANIC, true);
        }
    }

    void Register() override
    {
        OnCast += SpellCastFn(spell_pri_mass_dispel::HandleOnCast);
    }
};

// Last Update 8.0.1 28153
//Called by Lingering Insanity - 197937
class spell_pri_lingering_insanity : public AuraScript
{
    PrepareAuraScript(spell_pri_lingering_insanity);

    void OnTick(AuraEffect const* /*aurEff*/)
    {
        if (Unit* caster = GetCaster())
            if (AuraEffect const* aurEff = caster->GetAuraEffect(199849, EFFECT_0))
                GetAura()->ModStackAmount(-aurEff->GetAmount());
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_pri_lingering_insanity::OnTick, EFFECT_1, SPELL_AURA_PERIODIC_DUMMY);
    }
};

// 33206 - Pain Suppression
class aura_pri_pain_suppression : public AuraScript
{
    PrepareAuraScript(aura_pri_pain_suppression);

    void HandleApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetTarget();
        if (!caster || !target)
            return;

        if (Aura* aura = caster->GetAura(SPELL_PRIEST_MOMENT_OF_REPOSE_POWER))
        {
            caster->CastSpell(target, SPELL_PRIEST_ATONEMENT_AURA, true);
            caster->CastCustomSpell(SPELL_PRIEST_MOMENT_OF_REPOSE_HEAL, SPELLVALUE_BASE_POINT0, aura->GetEffect(EFFECT_0)->GetAmount(), target, true);
        }
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(aura_pri_pain_suppression::HandleApply, EFFECT_0, SPELL_AURA_MOD_DAMAGE_PERCENT_TAKEN, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
    }
};

// 64901 - Symbol of Hope
//Last Update 8.0.1 Build 28153
class spell_pri_symbol_of_hope : public SpellScript
{
    PrepareSpellScript(spell_pri_symbol_of_hope);

    bool Load() override
    {
        return GetCaster()->GetTypeId() == TYPEID_PLAYER;
    }

    void SelectTarget(std::list<WorldObject*>& targets)
    {
        Player* caster = GetCaster()->ToPlayer();
        targets.remove_if([caster](WorldObject* target) -> bool
        {
            if (Player* playerTarget = target->ToPlayer())
                return !(caster->IsInSameRaidWith(playerTarget) && playerTarget->GetRole() == TALENT_ROLE_HEALER);
            return true;
        });
    }

    void Register() override
    {       
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_pri_symbol_of_hope::SelectTarget, EFFECT_0, TARGET_UNIT_DEST_AREA_ALLY);
    }
};

// 64901 - Symbol of Hope
//Last Update 8.0.1 Build 28153
class aura_pri_symbol_of_hope : public AuraScript
{
    PrepareAuraScript(aura_pri_symbol_of_hope);

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
        Unit* target = GetTarget();
        if (!target)
            return;

        uint32 curValue = target->GetPower(POWER_MANA);
        uint32 maxValue = target->GetMaxPower(POWER_MANA);

        if (curValue >= maxValue)
            return;

        uint32 value = 0;

        if (SpellInfo const* spellInfo = GetSpellInfo())
            if ( spellInfo->GetEffect(EFFECT_1).BasePoints)
                value = CalculatePct(maxValue - curValue, spellInfo->GetEffect(EFFECT_1).BasePoints);

        if(value)
            GetAura()->GetEffect(EFFECT_0)->ChangeAmount(value);
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(aura_pri_symbol_of_hope::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_ENERGIZE);
    }
};

// 209780 - Premonition
//Last Update 8.0.1 Build 28153
class spell_pri_premonition : public SpellScript
{
    PrepareSpellScript(spell_pri_premonition);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo
        ({
            SPELL_PRIEST_PREMONITION_DAMAGE,
            SPELL_PRIEST_ATONEMENT_AURA
            });
    }

    void HandleDummy(SpellEffIndex /*effIndex*/)
    {
        if (Unit* caster = GetCaster())
        {
            int32 damage = int32(caster->GetTargetAuraApplications(SPELL_PRIEST_ATONEMENT_AURA).size()) * int32(caster->SpellBaseDamageBonusDone(SPELL_SCHOOL_MASK_MAGIC) * GetEffectInfo().BonusCoefficient);
            caster->CastSpell(caster, SPELL_PRIEST_ATONEMENT_AURA, true);

            if (!damage)
                return;

            caster->AddDelayedEvent(1500, [caster, damage]()->void
            {
                if (caster->IsInWorld() && caster->IsAlive())                
                    caster->CastCustomSpell(SPELL_PRIEST_PREMONITION_DAMAGE, SPELLVALUE_BASE_POINT1, damage, caster, TRIGGERED_FULL_MASK);                
            });            
        }        
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_pri_premonition::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

// 209885 - Premonition
//Last Update 8.0.1 Build 28153
class spell_pri_premonition_damage : public SpellScript
{
    PrepareSpellScript(spell_pri_premonition_damage);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo
        ({
            SPELL_PRIEST_PREMONITION,
            SPELL_PRIEST_ATONEMENT_AURA
            });
    }

    void HandleDummy(SpellEffIndex /*effIndex*/)
    {
        if (Aura* atonement = GetHitUnit()->GetAura(SPELL_PRIEST_ATONEMENT_AURA, GetCaster()->GetGUID()))
        {
            int32 newDuration = atonement->GetDuration();
            newDuration += sSpellMgr->AssertSpellInfo(SPELL_PRIEST_PREMONITION)->GetEffect(EFFECT_0).BasePoints;

            if (newDuration > atonement->GetMaxDuration())
                atonement->SetMaxDuration(newDuration);
            atonement->SetDuration(newDuration);
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_pri_premonition_damage::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

// 341374 : Damnation
class spell_priest_damnation : public SpellScript
{
    PrepareSpellScript(spell_priest_damnation);

    void HandleDummy(SpellEffIndex /*effIndex*/)
    {
        if (Unit* caster = GetCaster())
            if (Unit* target = GetHitUnit())
            {
                caster->CastSpell(target, 335467, true); // Devouring Plague
                caster->CastSpell(target, 34914, true); // Vampirc Touch
                caster->CastSpell(target, 589, true); // Shadow word: Pain
            }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_priest_damnation::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

void AddSC_priest_spell_scripts()
{
    // Areatriggers
    RegisterAreaTriggerAI(at_pri_angelic_feather);
    RegisterAreaTriggerAI(at_pri_power_word_barrier);
    RegisterAreaTriggerAI(at_pri_halo);
    RegisterAreaTriggerAI(at_pri_divine_star);
      
    //Auras
    RegisterSpellScript(spell_pri_atonement);
    RegisterSpellScript(spell_pri_atonement_aura);
    RegisterSpellScript(aura_priest_pshychic_scream);
    RegisterSpellScript(spell_pri_shadow_mend_aura);
    RegisterSpellScript(spell_pri_penance_triggered);
    RegisterSpellScript(aura_pri_renew);
    RegisterSpellScript(spell_pri_vampiric_embrace);
    RegisterSpellScript(spell_pri_vampiric_touch);
    RegisterSpellScript(spell_pri_power_of_the_dark_side);
    RegisterSpellScript(spell_pri_spirit_of_redemption);
    RegisterSpellScript(spell_pri_clarity_of_will);
    RegisterSpellScript(aura_pri_twist_of_fate_shadow);
    RegisterSpellScript(aura_pri_twist_of_fate_discipline);
    RegisterSpellScript(spell_pri_mind_bomb);
    RegisterSpellScript(aura_pri_void_torrent);
    RegisterSpellScript(aura_pri_holy_words);
    RegisterSpellScript(aura_pri_shadowy_apparitions);
    RegisterSpellScript(aura_pri_prayer_of_mending_aura);
    RegisterSpellScript(aura_pri_trail_of_light);
    RegisterSpellScript(aura_pri_shadowy_insigth);
    RegisterSpellScript(aura_pri_sins_of_the_many);
    RegisterSpellScript(aura_pri_sins_of_the_many_buff);
    RegisterSpellScript(aura_pri_cosmic_ripple);
    RegisterSpellScript(aura_pri_luminous_barrier);
    RegisterSpellScript(aura_pri_surge_of_light_aura);
    RegisterSpellScript(aura_pri_body_and_soul);
    RegisterSpellScript(aura_pri_driven_to_madness);
    RegisterSpellScript(aura_pri_dispersion);
    RegisterSpellScript(aura_pri_ray_of_hope);
    RegisterSpellScript(aura_pri_surrender_to_madness);
    RegisterSpellScript(aura_pri_holy_word_chastise);
    RegisterSpellScript(aura_pri_mania);
    RegisterSpellScript(aura_pri_shadow_mania);
    RegisterSpellScript(aura_pri_sustained_sanity);
    RegisterSpellScript(aura_pri_greater_heal);
    RegisterSpellScript(spell_pri_holy_ward);
    RegisterSpellScript(spell_pri_lingering_insanity);

    //Spells
    new spell_pri_power_word_radiance();
    new spell_pri_smite_absorb();
    new spell_pri_focused_will();
    new spell_pri_angelic_feather();
    new spell_pri_divine_hymn();
    new spell_pri_fade();
    new spell_pri_glyph_of_shadow();
    RegisterSpellScript(spell_pri_guardian_spirit);
    new spell_pri_hymn_of_hope();
    new spell_pri_item_greater_heal_refund();
    new spell_pri_leap_of_faith();
    new spell_pri_leap_of_faith_effect_trigger();
    new spell_pri_levitate();
    new spell_pri_lightwell_renew();
    new spell_pri_mana_leech();
    RegisterSpellScript(spell_pri_power_word_solace);
    new spell_pri_pain_and_suffering_proc();
    new spell_pri_shadowfiend();
    new spell_pri_shadowform();
    new spell_pri_spirit_shell();
    new spell_pri_strength_of_soul();
    new spell_pri_void_tendrils();
    new spell_pri_voidform();
    new spell_priest_angelic_bulwark();
    RegisterSpellScript(spell_pri_mass_dispel);
    RegisterSpellScript(spell_pri_shadow_mend);
	RegisterSpellScript(spell_pri_mind_sear);
    RegisterSpellScript(spell_pri_penance);
    RegisterSpellScript(spell_pri_penance_heal_damage);
    RegisterSpellScript(spell_pri_purge_the_wicked_selector);
    RegisterSpellScript(spell_pri_shadow_word_death);
    RegisterSpellScript(spell_pri_void_eruption);
    RegisterSpellScript(spell_pri_void_eruption_damage);
    RegisterSpellScript(spell_pri_holy_word_chastise);
    RegisterSpellScript(spell_pri_smite);
    RegisterSpellScript(spell_pri_prayer_of_healing);
    RegisterSpellScript(spell_pri_binding_heal);
    RegisterSpellScript(spell_pri_void_bolt);
    RegisterSpellScript(spell_pri_archangel);
    RegisterSpellScript(spell_pri_dark_archangel);
	RegisterSpellScript(spell_pri_holy_nova);
    RegisterSpellAndAuraScriptPair(spell_pri_power_word_shield, aura_pri_power_word_shield);
    RegisterSpellScript(spell_pri_prayer_of_mending);
    RegisterSpellScript(spell_pri_prayer_of_mending_target_selector);
    RegisterSpellScript(spell_pri_holy_word_sanctify);
    RegisterSpellScript(spell_pri_holy_word_serenity);
    RegisterSpellScript(spell_pri_holy_word_salvation);
    RegisterSpellScript(spell_pri_mind_blast);
    RegisterSpellScript(spell_pri_cosmic_ripple_heal);
    RegisterSpellScript(spell_pri_heal);
    RegisterSpellScript(spell_prist_evangelism);
    RegisterSpellScript(spell_pri_inner_focus);
    RegisterSpellAndAuraScriptPair(spell_pri_holy_fire, aura_pri_holy_fire);
    RegisterSpellScript(spell_pri_dark_void);
    RegisterSpellScript(spell_pri_purify);
    RegisterSpellScript(spell_pri_dark_ascension);
    RegisterSpellScript(spell_pri_psychic_link);
    RegisterSpellScript(spell_pri_psyfiend);
    RegisterSpellScript(spell_pri_shadow_covenant);
    RegisterSpellScript(spell_pri_void_shift);
    RegisterSpellScript(spell_pri_shadowy_apparitions_damage);
    RegisterSpellScript(aura_pri_pain_suppression);
    RegisterSpellAndAuraScriptPair(spell_pri_symbol_of_hope, aura_pri_symbol_of_hope);
    RegisterSpellScript(spell_pri_premonition);
    RegisterSpellScript(spell_pri_premonition_damage);
    RegisterSpellScript(spell_priest_damnation);

    // PlayerScripts
    new priest_playerscript();
    new PlayerScript_Holy_Concentration();

	/// NPC scripts
	RegisterCreatureAI(npc_pet_priest_fiend);
    RegisterCreatureAI(npc_pet_priest_psyfiend);
}
