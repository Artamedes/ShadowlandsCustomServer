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
  * Scripts for spells with SPELLFAMILY_SHAMAN and SPELLFAMILY_GENERIC spells used by shaman players.
  * Ordered alphabetically using scriptname.
  * Scriptnames of files in this file should be prefixed with "spell_sha_".
  */

#include "AreaTrigger.h"
#include "AreaTriggerAI.h"
#include "CellImpl.h"
#include "CreatureAIImpl.h"
#include "GridNotifiersImpl.h"
#include "PhasingHandler.h"
#include "Player.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "SpellScript.h"
#include "SpellHistory.h"
#include "SpellMgr.h"
#include "SpellAuraEffects.h"
#include "SpellAuras.h"
#include "Totem.h"
#include "Item.h"
#include "TotemAI.h"
#include "Group.h"
#include "SpellPackets.h"

enum ShamanSpells
{
    SPELL_CHAIN_HEAL                                        = 1064,
    SPELL_RIPTIDE                                           = 61295,
    SPELL_PET_NETHERWINDS_FATIGUED                          = 160455,
    SPELL_SHAMAN_ANCESTRAL_AWAKENING                        = 52759,
    SPELL_SHAMAN_ANCESTRAL_AWAKENING_PROC                   = 52752,
    SPELL_SHAMAN_ANCESTRAL_GUIDANCE                         = 108281,
    SPELL_SHAMAN_ANCESTRAL_GUIDANCE_HEAL                    = 114911,
    SPELL_SHAMAN_ASCENDANCE                                 = 114049,
    SPELL_SHAMAN_ASCENDANCE_ELEMENTAL                       = 114050,
    SPELL_SHAMAN_ASCENDANCE_ENHANCED                        = 114051,
    SPELL_SHAMAN_ASCENDANCE_RESTORATION                     = 114052,
    SPELL_SHAMAN_AT_EARTHEN_SHIELD_TOTEM                    = 198839,
    SPELL_SHAMAN_BIND_SIGHT                                 = 6277,
    SPELL_SHAMAN_CONDUCTIVITY_HEAL                          = 118800,
    SPELL_SHAMAN_CONDUCTIVITY_TALENT                        = 108282,
    SPELL_SHAMAN_CRASH_LIGHTNING_PROC                       = 195592,
    SPELL_SHAMAN_CRASH_LIGTHNING                            = 187874,
    SPELL_SHAMAN_CRASH_LIGTHNING_AURA                       = 187878,
    SPELL_SHAMAN_CRASHING_STORM_DUMMY                       = 192246,
    SPELL_SHAMAN_CRASHING_STORM_AT                          = 210797,
    SPELL_SHAMAN_CRASHING_STORM_DAMAGE                      = 210801,
    SPELL_SHAMAN_DOOM_WINDS                                 = 204945,
    SPELL_SHAMAN_EARTHBIND_FOR_EARTHGRAB_TOTEM              = 116947,
    SPELL_SHAMAN_EARTHEN_RAGE_DAMAGE                        = 170379,
    SPELL_SHAMAN_EARTHEN_RAGE_PASSIVE                       = 170374,
    SPELL_SHAMAN_EARTHEN_RAGE_PERIODIC                      = 170377,
    SPELL_SHAMAN_EARTHGRAB_IMMUNITY                         = 116946,
    SPELL_SHAMAN_EARTHQUAKE                                 = 61882,
    SPELL_SHAMAN_EARTHQUAKE_KNOCKING_DOWN                   = 77505,
    SPELL_SHAMAN_EARTHQUAKE_TICK                            = 77478,
    SPELL_SHAMAN_EARTH_ELEMENTAL_AGGRO                      = 235429,
    SPELL_SHAMAN_EARTH_ELEMENTAL_DUMMY                      = 198103,
    SPELL_SHAMAN_EARTH_ELEMENTAL_SUMMON                     = 188616,
    SPELL_SHAMAN_EARTH_SHIELD_HEAL                          = 379,
    SPELL_SHAMAN_EARTH_SHOCK                                = 8042,
    SPELL_SHAMAN_ECHO_OF_THE_ELEMENTS                       = 108283,
    SPELL_SHAMAN_ELEMENTAL_BLAST                            = 117014,
    SPELL_SHAMAN_ELEMENTAL_BLAST_CRIT                       = 118522,
    SPELL_SHAMAN_ELEMENTAL_BLAST_HASTE                      = 173183,
    SPELL_SHAMAN_ELEMENTAL_BLAST_MASTERY                    = 173184,
    SPELL_SHAMAN_ELEMENTAL_MASTERY                          = 16166,
    SPELL_SHAMAN_EXHAUSTION                                 = 57723,
    SPELL_SHAMAN_FERAL_LUNGE                                = 196884,
    SPELL_SHAMAN_FERAL_LUNGE_DAMAGE                         = 215802,
    SPELL_SHAMAN_FERAL_SPIRIT                               = 51533,
    SPELL_SHAMAN_FERAL_SPIRIT_SUMMON                        = 228562,
    SPELL_SHAMAN_FERAL_SPIRIT_ENERGIZE                      = 190185,
    SPELL_SHAMAN_FERAL_SPIRIT_ENERGIZE_DUMMY                = 231723,
    SPELL_SHAMAN_FIRE_ELEMENTAL_DUMMY                       = 198067,
    SPELL_SHAMAN_FIRE_ELEMENTAL_SUMMON                      = 188592,
    SPELL_SHAMAN_FIRE_NOVA                                  = 1535,
    SPELL_SHAMAN_FIRE_NOVA_TRIGGERED                        = 131786,
    SPELL_SHAMAN_FLAMETONGUE_ATTACK                         = 10444,
    SPELL_SHAMAN_FLAMETONGUE_WEAPON_PASSIVE                 = 10400,
    SPELL_SHAMAN_FLAME_SHOCK                                = 8050,
    SPELL_SHAMAN_FLAME_SHOCK_ELEM                           = 188389,
	SPELL_SHAMAN_FLAME_SHOCK_ELEM_RESTO                     = 188838,
    SPELL_SHAMAN_FROST_SHOCK_FREEZE                         = 63685,
    SPELL_SHAMAN_FROZEN_POWER                               = 63374,
    SPELL_SHAMAN_FULMINATION                                = 88766,
    SPELL_SHAMAN_FULMINATION_INFO                           = 95774,
    SPELL_SHAMAN_FULMINATION_TRIGGERED                      = 88767,
    SPELL_SHAMAN_FURY_OF_AIR                                = 197211,
    SPELL_SHAMAN_FURY_OF_AIR_EFFECT                         = 197385,
    SPELL_SHAMAN_GHOST_WOLF                                 = 2645,
    SPELL_SHAMAN_GLYPH_OF_HEALING_STREAM                    = 119523,
    SPELL_SHAMAN_GLYPH_OF_HEALING_STREAM_TOTEM              = 55456,
    SPELL_SHAMAN_GLYPH_OF_HEALING_STREAM_TOTEM_TRIGGERED    = 119523,
    SPELL_SHAMAN_GLYPH_OF_HEALING_WAVE                      = 55533,
    SPELL_SHAMAN_GLYPH_OF_LAKESTRIDER                       = 55448,
    SPELL_SHAMAN_GLYPH_OF_LAVA_LASH                         = 55444,
    SPELL_SHAMAN_GLYPH_OF_SHAMANISTIC_RAGE                  = 63280,
    SPELL_SHAMAN_GLYPH_OF_THUNDERSTORM                      = 62132,
    SPELL_SHAMAN_HEALING_RAIN                               = 73920,
    SPELL_SHAMAN_HEALING_RAIN_TICK                          = 73921,
    SPELL_SHAMAN_HEALING_STREAM                             = 52042,
    SPELL_SHAMAN_HEALING_STREAM_DUMMY                       = 98856,
    SPELL_SHAMAN_HIGH_TIDE                                  = 157154,
    SPELL_SHAMAN_HOT_HAND                                   = 215785,
    SPELL_SHAMAN_IMPROVED_LIGHTNING_SHIELD                  = 157774,
    SPELL_SHAMAN_ITEM_LIGHTNING_SHIELD                      = 23552,
    SPELL_SHAMAN_ITEM_LIGHTNING_SHIELD_DAMAGE               = 27635,
    SPELL_SHAMAN_ITEM_MANA_SURGE                            = 23571,
    SPELL_SHAMAN_ITEM_T14_4P                                = 123124,
    SPELL_SHAMAN_ITEM_T18_ELEMENTAL_2P_BONUS                = 185880,
    SPELL_SHAMAN_ITEM_T18_ELEMENTAL_4P_BONUS                = 185881,
    SPELL_SHAMAN_ITEM_T18_GATHERING_VORTEX                  = 189078,
    SPELL_SHAMAN_ITEM_T18_LIGHTNING_VORTEX                  = 189063,
    SPELL_SHAMAN_LAVA_BURST                                 = 51505,
    SPELL_SHAMAN_LAVA_LASH                                  = 60103,
    SPELL_SHAMAN_LAVA_LASH_SPREAD_FLAME_SHOCK               = 105792,
    SPELL_SHAMAN_LAVA_SURGE                                 = 77756,
    SPELL_SHAMAN_LAVA_SURGE_CAST_TIME                       = 77762,
    SPELL_SHAMAN_LIGHTNING_BOLT_ELEM                        = 188196,
    SPELL_SHAMAN_LIGHTNING_BOLT_ELEM_POWER                  = 214815,
    SPELL_SHAMAN_LIGHTNING_SHIELD                           = 324,
    SPELL_SHAMAN_LIGHTNING_SHIELD_AURA                      = 324,
    SPELL_SHAMAN_LIGHTNING_SHIELD_ORB_DAMAGE                = 26364,
    SPELL_SHAMAN_LIGHTNING_SHIELD_TRIGGER                   = 26364,
    SPELL_SHAMAN_LIQUID_MAGMA_DAMAGE                        = 192231,
    SPELL_SHAMAN_MAELSTROM_WEAPON                           = 187880,
    SPELL_SHAMAN_MAELSTROM_WEAPON_POWER                     = 187881,
    SPELL_SHAMAN_MAELSTROM_WEAPON_POWER_DUMMY               = 344179,
    SPELL_SHAMAN_MAIL_SPECIALISATION_INT                    = 86100,
    SPELL_SHAMAN_MAIL_SPECIALIZATION_AGI                    = 86099,
    SPELL_SHAMAN_MANA_TIDE                                  = 16191,
    SPELL_SHAMAN_NATURE_GUARDIAN_HEAL                       = 31616,
    SPELL_SHAMAN_OVERCHARGE                                 = 210727,
    SPELL_SHAMAN_PATH_OF_FLAMES_SPREAD                      = 210621,
    SPELL_SHAMAN_PATH_OF_FLAMES_TALENT                      = 201909,
    SPELL_SHAMAN_RAINFALL                                   = 215864,
    SPELL_SHAMAN_RAINFALL_HEAL                              = 215871,
    SPELL_SHAMAN_RESTORATIVE_MISTS                          = 114083,
    SPELL_SHAMAN_RIPTIDE                                    = 61295,
    SPELL_SHAMAN_ROLLING_THUNDER_AURA                       = 88764,
    SPELL_SHAMAN_ROLLING_THUNDER_ENERGIZE                   = 88765,
    SPELL_SHAMAN_RUSHING_STREAMS                            = 147074,
    SPELL_SHAMAN_SATED                                      = 57724,
    SPELL_SHAMAN_SEARING_FLAMES_DAMAGE_DONE                 = 77661,
    SPELL_SHAMAN_SOLAR_BEAM                                 = 113286,
    SPELL_SHAMAN_SOLAR_BEAM_SILENCE                         = 113288,
    SPELL_SHAMAN_STONE_BULWARK_ABSORB                       = 114893,
    SPELL_SHAMAN_STORMBRINGER                               = 201845,
    SPELL_SHAMAN_STORMBRINGER_PROC                          = 201846,
    SPELL_SHAMAN_STORMLASH                                  = 195255,
    SPELL_SHAMAN_STORMLASH_BUFF                             = 195222,
    SPELL_SHAMAN_STORMLASH_DAMAGE                           = 213307,
    SPELL_SHAMAN_STORMSTRIKE                                = 17364,
    SPELL_SHAMAN_STORMSTRIKE_MAIN                           = 32175,
    SPELL_SHAMAN_STORMSTRIKE_OFF_HAND                       = 32176,
    SPELL_SHAMAN_TIDAL_WAVES                                = 53390,
    SPELL_SHAMAN_TOTEM_HEALING_STREAM_HEAL                  = 52042,
    SPELL_SHAMAN_UNDULATION_PROC                            = 216251,
    SPELL_SHAMAN_UNLEASHED_FURY_EARTHLIVING                 = 118473,
    SPELL_SHAMAN_UNLEASHED_FURY_FLAMETONGUE                 = 118470,
    SPELL_SHAMAN_UNLEASHED_FURY_FROSTBRAND                  = 118474,
    SPELL_SHAMAN_UNLEASHED_FURY_ROCKBITER                   = 118475,
    SPELL_SHAMAN_UNLEASHED_FURY_TALENT                      = 117012,
    SPELL_SHAMAN_UNLEASHED_FURY_WINDFURY                    = 118472,
    SPELL_SHAMAN_UNLEASH_ELEMENTS                           = 73680,
    SPELL_SHAMAN_WATER_WALKING                              = 546,
    SPELL_SHAMAN_WELLSPRING_MISSILE                         = 198117,
    SPELL_SHAMAN_WINDFURY_ATTACK                            = 25504,
    SPELL_SHAMAN_WINDFURY_ATTACK_MAIN_HAND                  = 25504,
    SPELL_SHAMAN_WINDFURY_ATTACK_OFF_HAND                   = 33750,
    SPELL_SHAMAN_WINDFURY_WEAPON_PASSIVE                    = 33757,
    SPELL_SHAMAN_WIND_RUSH_TOTEM                            = 192077,
	SPELL_SHAMAN_MASTERY_ELEMENTAL_OVERLOAD                 = 168534,
	SPELL_SHAMAN_LIGHTNING_BOLT_OVERLOAD                    = 45284,
	SPELL_SHAMAN_LIGHTNING_BOLT_ENERGIZE_OVERLOAD           = 214816,
	SPELL_SHAMAN_CHAIN_LIGHTNING_ELEM                       = 188443,
	SPELL_SHAMAN_CHAIN_LIGHTNING_OVERLOAD                   = 45297,
	SPELL_SHAMAN_CHAIN_LIGHTNING_ENERGIZE_OVERLOAD          = 218558,
	SPELL_SHAMAN_LAVA_BURST_OVERLOAD                        = 77451,
	SPELL_SHAMAN_ICEFURY                                    = 210714,
	SPELL_SHAMAN_ICEFURY_OVERLOAD                           = 219271,
	SPELL_SHAMAN_ELEMENTAL_BLAST_OVERLOAD                   = 120588,
	SPELL_SHAMAN_MASTER_OF_THE_ELEMENTS                     = 260734,
    SPELL_SHAMAN_HIGH_VOLTAGE                               = 260890,
    SPELL_SHAMAN_UNLIMTED_POWER                             = 260895,
    SPELL_SHAMAN_UNLIMITED_POWER_HASTE                      = 272737,
    SPELL_SHAMAN_STORMKEEPER                                = 191634,
	SPELL_SHAMAN_SPIRIT_WOLF								= 260878,
	SPELL_SHAMAN_SPIRIT_WOLF_TRIGGER						= 260882,
	SPELL_SHAMAN_SPIRIT_WOLF_AURA							= 260881,
	SPELL_SHAMAN_FROST_SHOCK								= 196840,
    SPELL_SHAMAN_RESONANCE_TOTEM_ENCHA                      = 262417,
    SPELL_SHAMAN_STORM_TOTEM_ENCHA                          = 262397,
    SPELL_SHAMAN_EMBER_TOTEM_ENCHA                          = 262399,
    SPELL_SHAMAN_TAILWIND_TOTEM_ECHA                        = 262400,
	SPELL_SHAMAN_DELUGE										= 200076,
	SPELL_SHAMAN_FLASH_FLOOD								= 280614,
	SPELL_SHAMAN_FLASH_FLOOD_BUFF							= 280615,
	SPELL_SHAMAN_WELLSPRING									= 197995,
    SPELL_SHAMAN_FLAMETONGUE_BUFF                           = 194084,
    SPELL_SHAMAN_LIGTHNING_SHIELD_CHARGE                    = 192106,
    SPELL_SHAMAN_LIGTHNING_SHIELD_OVERCHARGE                = 273323,
    SPELL_SHAMAN_ROCKBITER                                  = 193786,
    SPELL_SHAMAN_LANDSLIDE_AURA                             = 202004,
    SPELL_SHAMAN_FORCEFUL_WINDS                             = 262647,
    SPELL_SHAMAN_FORCEFUL_WINDS_BUFF                        = 262652,
    SPELL_SHAMAN_STATIC_TOTEM                               = 192058,
    SPELL_SHAMAN_STATIC_CHARGE                              = 265046,
    SPELL_SHAMAN_STORMSTRIKE_ADD_DAMAGE                     = 67220,
	SPELL_SHAMAN_HAILSTORM                                  = 210853,
    SPELL_SHAMAN_HAILSTORM_DAMAGE                           = 210854,
    SPELL_SHAMAN_FROSTBRAND                                 = 196834,
    SPELL_SHAMAN_EXPOSED_ELEMENTS                           = 269808,
	SPELL_SHAMAN_SPECTRAL_RECOVERY							= 204261,
	SPELL_SHAMAN_SPECTRAL_RECOVERY_HEAL						= 204262,
    SPELL_SHAMAN_EARTHFURY                                  = 204398,
    SPELL_SHAMAN_EARTHFURY_STUN                             = 204399,
    SPELL_SHAMAN_CONTROL_OF_LAVA                            = 204393,
    SPELL_SHAMAN_CONTROL_OF_LAVA_PROC                       = 236746,
	SPELL_SHAMAN_EARTHEN_SHIELD_ABSORB						= 201633,
	SPELL_SHAMAN_EARTHEN_WALL_TOTEM							= 198838,
	SPELL_SHAMAN_EARTH_SHIELD								= 974,
	SPELL_SHAMAN_NATURE_GUARDIAN							= 30884,
	SPELL_SHAMAN_HEALING_SURGE_ENHACENMENT					= 190899,
    SPELL_SHAMAN_RIPPLING_WATERS                            = 204269,
    SPELL_SHAMAN_RIPPLING_WATERS_HEAL                       = 204281,
    SPELL_SHAMAN_SWELLING_WAVES                             = 204264,
    SPELL_SHAMAN_SWELLING_WAVES_HEAL                        = 204266,
	SPELL_SHAMAN_FORKED_LIGHTNING							= 204349,
	SPELL_SHAMAN_FORKED_LIGHTNING_DAMAGE					= 204350,
	SPELL_SHAMAN_ELECTROCUTE								= 206642,
	SPELL_SHAMAN_ELECTROCUTE_DAMAGE							= 206647,
    SPELL_SHAMAN_CRASHING_STORM                             = 192246,
    SPELL_SHAMAN_CRASHING_STORM_AREA                        = 210797,
    SPELL_SHAMAN_ELEMENTAL_SPIRITS                          = 262624,
    SPELL_SHAMAN_MOLTEN_WEAPON                              = 224125,
    SPELL_SHAMAN_ICE_EDGE                                   = 224126,
	SPELL_SHAMAN_CRACKLING_SURGE                            = 224127,
    SPELL_SHAMAN_MOLTEN_WEAPON_DAMAGE                       = 271924,
    SPELL_SHAMAN_ICY_EDGE_DAMAGE                            = 271920,
    SPELL_SHAMAN_HEALING_SURGE_WALKING                      = 190900,
    SPELL_SHAMAN_STATIC_CLING                               = 211062,
    SPELL_SHAMAN_STATIC_CLING_TARGET                        = 210927,
    SPELL_SHAMAN_STATIC_CLING_SHAMAN                        = 211400,
    SPELL_SHAMAN_STORM_ELEMENTAL_SUMMON                     = 157299,
    SPELL_SHAMAN_STORM_ELEMENTAL_BUFF                       = 263806,
    SPELL_SHAMAN_STORM_ELEMENTAL_EYE_TRIGGER                = 157375,
    SPELL_SHAMAN_FULMINATION_ENERGIZE                       = 190493,
    SPELL_SHAMAN_PRIMAL_ELEMENTALIST                        = 117013,
    SPELL_SHAMAN_PRIMAL_EARTH_ELEMENTAL_SUMMON              = 118323,
    SPELL_SHAMAN_PRIMAL_FIRE_ELEMENTAL_SUMMON               = 118291,
    SPELL_SHAMAN_PRIMAL_STORM_ELEMENTAL_SUMMON              = 157319,
    SPELL_SHAMAN_ELEMENTAL_SHAMAN                           = 137040,
    SPELL_SHAMAN_LAVA_SURGE_VISUAL                          = 174928,
    SPELL_SHAMAN_PURIFYING_WATERS                           = 204247,
    SPELL_SHAMAN_PURIFYING_WATERS_HEAL                      = 204248,
    SPELL_SHAMAN_CALMING_WATERS                             = 221677,
    SPELL_SHAMAN_CALMING_WATERS_PROC                        = 221678,
    SPELL_SHAMAN_HORDE_HEROIMS                              = 204361,
    SPELL_SHAMAN_ALLI_HEROISMS                              = 204362,
    SPELL_SHAMAN_AFTERSHOCK                                 = 273221,
    SPELL_SHAMAN_AFTERSHOCK_ENERGIZE                        = 210712,
    SPELL_SHAMAN_ROLLING_STORM_BUFF                         = 279515,
    SPELL_SHAMAN_FLAMETONGUE                                = 193796,
    SPELL_SHAMAN_SPIRIT_LINK_HEAL_DPS                       = 98021,
    SPELL_SHAMAN_SPIRIT_LINK_PVP_DAMAGE                     = 204314,
    SPELL_SHAMAN_ANCESTRAL_RESONANCE_POWER                  = 277666,
    SPELL_SHAMAN_ANCESTRAL_RESONANCE_PERIODIC               = 277942,
    SPELL_SHAMAN_PRIMAL_PRIMER_POWER                        = 272992,
    SPELL_SHAMAN_PRIMAL_PRIMER_BUFF                         = 273006,
    SPELL_SHAMAN_PACK_SPIRIT_POWER                          = 280021,
    SPELL_SHAMAN_PACK_SPIRIT_HEAL                           = 280205,
    SPELL_SHAMAN_THUNDERSTORM_ALLY_DAMAGE                   = 204408,
    SPELL_SHAMAN_THUNDERSTORM_ALLY_KNOCKBACK                = 228947,
    SPELL_SHAMAN_SPOUTING_SPIRITS_POWER                     = 278715,
    SPELL_SHAMAN_SPOUTING_SPIRITS_HEAL                      = 279505,
    SPELL_SHAMAN_OVERFLOWING_SHORES_POWER                   = 277658,
    SPELL_SHAMAN_OVERFLOWING_SHORES_HEAL                    = 278095,
    SPELL_SHAMAN_WINDFURY_ENCHANTMENT                       = 334302,
    SPELL_SHAMAN_WIND_RUSH                                  = 192082,
    SPELL_SHAMAN_FLAMETONGUE_WEAPON_ENCHANT                 = 334294,
    SPELL_SHAMAN_FLAMETONGUE_WEAPON_AURA                    = 319778,
}; 

enum TotemSpells
{
    SPELL_TOTEM_WIND_RUSH_EFFECT                            = 192082,
    SPELL_TOTEM_VOODOO_AT                                   = 196935,
    SPELL_TOTEM_VOODOO_EFFECT                               = 196942,
    SPELL_TOTEM_VOODOO_COOLDOWN                             = 202318,
    SPELL_TOTEM_LIGHTNING_SURGE_EFFECT                      = 118905,
    SPELL_TOTEM_RESONANCE_EFFECT                            = 202192,
    SPELL_TOTEM_LIQUID_MAGMA_EFFECT                         = 192226,
    SPELL_TOTEM_EARTH_GRAB_ROOT_EFFECT                      = 64695,
    SPELL_TOTEM_EARTH_GRAB_SLOW_EFFECT                      = 116947,
    SPELL_TOTEM_HEALING_TIDE_EFFECT                         = 114942,
    SPELL_TOTEM_TAIL_WIND_EFFECT                            = 210659,
    SPELL_TOTEM_EMBER_EFFECT                                = 210658,
    SPELL_TOTEM_STORM_EFFECT                                = 210652,
    SPELL_TOTEM_CLOUDBURST_EFFECT                           = 157504,
    SPELL_TOTEM_CLOUDBURST                                  = 157503,
    SPELL_TOTEM_ANCESTRAL_PROTECTION_AT                     = 207495,
    SPELL_TOTEM_TOTEMIC_REVIVAL                             = 207553,
    SPELL_TOTEM_SKYFURY_EFFECT                              = 208963,
    SPELL_TOTEM_GROUDING_TOTEM_EFFECT                       = 8178,
	SPELL_SHAMAN_EARTH_SHOCK_AURA                           = 190494,
	SPELL_SHAMAN_UNDULATION                                 = 200071,
    SPELL_TOTEM_STORM_EFFECT_ENCHA                          = 262397,
    SPELL_TOTEM_RESONANCE_EFFECT_ENCHA                      = 262417,
    SPELL_TOTEM_TAILWIND_EFFECT_ENCHA                       = 262400,
    SPELL_TOTEM_EMBER_EFFECT_ENCHA                          = 262399,
    SPELL_TOTEM_TREMOR_EFFECT                               = 8145,
    SPELL_TOTEM_EARTH_WALL_DAMAGE                           = 201657,
    SPELL_TOTEM_COUNTERSTRIKE_SUMMON                        = 204331,
    SPELL_TOTEM_COUNTERSTRIKE_EFFECT                        = 208990,
    SEPLL_TOTEM_COUNTERSTRIKE_AURA                          = 208997,
    SPELL_TOTEM_COUNTERSTRIKE_DAMAGE                        = 209031,
    SPELL_TOTEM_EARTHBIND_EFFECT                            = 6474,
    SPELL_TOTEM_SKYFURY_PASIVE                              = 208964,
};

enum ShamanSpellIcons
{
    SHAMAN_ICON_ID_SOOTHING_RAIN                            = 2011,
    SHAMAN_ICON_ID_SHAMAN_LAVA_FLOW                         = 3087
};

enum MiscSpells
{
    SPELL_HUNTER_INSANITY                                   = 95809,
    SPELL_MAGE_TEMPORAL_DISPLACEMENT                        = 80354
};

enum AncestralAwakeningProc
{
    SPELL_ANCESTRAL_AWAKENING_PROC                          = 52752,
};

enum ShamanNpcs
{
    NPC_RAINFALL                                            = 73400,
    NPC_HEALING_RAIN                                        = 73400, // Same as Rainfall at 7.3.5
};

class shaman_playerscript : PlayerScript
{
public:
    shaman_playerscript() : PlayerScript("shaman_playerscript") {}

    void OnModifyPower(Player* p_Player, Powers p_Power, int32 p_OldValue, int32& p_NewValue, bool p_Regen, bool p_After) override
    {
        if (!p_Player)
            return;

        if (p_Player->GetClass() != CLASS_SHAMAN || p_Power != POWER_MAELSTROM)
            return;

        if (p_Player->HasAura(SPELL_SHAMAN_EARTH_SHOCK_AURA) && p_Player->GetPower(POWER_MAELSTROM) < 60)
            p_Player->RemoveAura(SPELL_SHAMAN_EARTH_SHOCK_AURA);
    }

    // Removed in 9.1.0
    //void OnBeenDispelled(Player* player, Unit* unit) override
    //{
    //    if (!player)
    //        return;
    //
    //    if (player->HasAura(SPELL_SHAMAN_PURIFYING_WATERS))
    //        player->CastSpell(player, SPELL_SHAMAN_PURIFYING_WATERS_HEAL, true);
    //}
};

// Feral Lunge - 196884
class spell_sha_feral_lunge : public SpellScriptLoader
{
public:
    spell_sha_feral_lunge() : SpellScriptLoader("spell_sha_feral_lunge") {}

    class spell_sha_feral_lunge_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_sha_feral_lunge_SpellScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_SHAMAN_FERAL_LUNGE_DAMAGE))
                return false;
            return true;
        }

        void HandleDamage(SpellEffIndex /*effIndex*/)
        {
            Unit* caster = GetCaster();
            Unit* target = GetHitUnit();
            if (!caster || !target)
                return;

            caster->CastSpell(caster, SPELL_SHAMAN_GHOST_WOLF, true);
            caster->CastSpell(target, SPELL_SHAMAN_FERAL_LUNGE_DAMAGE, true);
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_sha_feral_lunge_SpellScript::HandleDamage, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_sha_feral_lunge_SpellScript();
    }
};

//Called by Stormbringer - 201845
//Last Update 8.0.1 Build 28153
class spell_sha_stormbringer : public AuraScript
{
    PrepareAuraScript(spell_sha_stormbringer);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->EquippedItemClass <= 0)
            return false;

        if (eventInfo.GetDamageInfo() && (eventInfo.GetDamageInfo()->GetAttackType() == BASE_ATTACK || eventInfo.GetDamageInfo()->GetAttackType() == OFF_ATTACK))
            return true;

        return false;
    }

    void HandleProc(AuraEffect* /*aurEff*/, ProcEventInfo& /*eventInfo*/)
    {
        if (Unit* caster = GetCaster())
        {
            caster->CastSpell(caster, SPELL_SHAMAN_STORMBRINGER_PROC, true);
            caster->GetSpellHistory()->ResetCooldown(SPELL_SHAMAN_STORMSTRIKE, true);
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_sha_stormbringer::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_sha_stormbringer::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

// 187878 - Crash Lightning aura
class spell_sha_crash_lightning_aura : public SpellScriptLoader
{
public:
    spell_sha_crash_lightning_aura() : SpellScriptLoader("spell_sha_crash_lightning_aura") {}

    class spell_sha_crash_lightning_aura_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_sha_crash_lightning_aura_AuraScript);

        bool CheckProc(ProcEventInfo& eventInfo)
        {
            if (eventInfo.GetSpellInfo()->Id == SPELL_SHAMAN_STORMSTRIKE_MAIN || eventInfo.GetSpellInfo()->Id == SPELL_SHAMAN_LAVA_LASH)
                return true;
            return false;
        }

        void Register() override
        {
            DoCheckProc += AuraCheckProcFn(spell_sha_crash_lightning_aura_AuraScript::CheckProc);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_sha_crash_lightning_aura_AuraScript();
    }
};

// 187874 - Crash Lightning
class spell_sha_crash_lightning : public SpellScriptLoader
{
public:
    spell_sha_crash_lightning() : SpellScriptLoader("spell_sha_crash_lightning") {}

    class spell_sha_crash_lightning_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_sha_crash_lightning_SpellScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            return ValidateSpellInfo({ SPELL_SHAMAN_CRASH_LIGTHNING_AURA,  SPELL_SHAMAN_STORMSTRIKE_ADD_DAMAGE });
        }

        SpellCastResult CheckCast()
        {
            Unit* caster = GetCaster();
            Unit* target = ObjectAccessor::GetUnit(*caster, caster->GetTarget());
            if (!caster || !target)
                return SPELL_FAILED_DONT_REPORT;

            if (!caster->IsWithinMeleeRange(target))
                return SPELL_FAILED_OUT_OF_RANGE;

            caster->Variables.Set("targetsHit", 0);

            return SPELL_CAST_OK;
        }

        void HandleHit(SpellEffIndex /*effIndex*/)
        {
            if (Unit* caster = GetCaster())
            {
                auto targetsHit = caster->Variables.GetValue("targetsHit", 0);
                targetsHit++;
                caster->Variables.Set("targetsHit", targetsHit);
                if (targetsHit == 2)
                    caster->CastSpell(caster, SPELL_SHAMAN_CRASH_LIGTHNING_AURA, true);
            }
        }

        void HandleAfterCast()
        {
            if (Unit* caster = GetCaster())
            {
                auto targetsHit = caster->Variables.GetValue("targetsHit", 0);
                caster->CastCustomSpell(SPELL_SHAMAN_STORMSTRIKE_ADD_DAMAGE, SPELLVALUE_BASE_POINT0, sSpellMgr->GetSpellInfo(SPELL_SHAMAN_STORMSTRIKE_ADD_DAMAGE)->GetEffect(EFFECT_0).BasePoints * targetsHit, caster, true);

                // Crashing Storm
                if (caster->HasAura(SPELL_SHAMAN_CRASHING_STORM))
                    caster->CastSpell(caster, SPELL_SHAMAN_CRASHING_STORM_AREA, true);
            }
        }

        void Register() override
        {
            OnCheckCast += SpellCheckCastFn(spell_sha_crash_lightning_SpellScript::CheckCast);
            OnEffectHitTarget += SpellEffectFn(spell_sha_crash_lightning_SpellScript::HandleHit, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
            AfterCast += SpellCastFn(spell_sha_crash_lightning_SpellScript::HandleAfterCast);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_sha_crash_lightning_SpellScript();
    }
};

// 51533 - Feral Spirit
class spell_sha_feral_spirit : public SpellScriptLoader
{
public:
    spell_sha_feral_spirit() : SpellScriptLoader("spell_sha_feral_spirit") {}

    enum FeralSpirits
    {
        Periodic = 333957,
    };

    class spell_sha_feral_spirit_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_sha_feral_spirit_SpellScript);

        void HandleDummy(SpellEffIndex /*effIndex*/)
        {
            Unit* caster = GetCaster();
            Unit* target = GetHitUnit();
            if (!caster || !target)
                return;

            if (caster->IsValidAttackTarget(target))
                caster->SetInCombatWith(target);
            caster->CastSpell(caster, SPELL_SHAMAN_FERAL_SPIRIT_SUMMON, true);
            caster->CastSpell(caster, Periodic, true);
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_sha_feral_spirit_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_sha_feral_spirit_SpellScript();
    }
};

// -51556 - Ancestral Awakening
class spell_sha_ancestral_awakening : public SpellScriptLoader
{
public:
    spell_sha_ancestral_awakening() : SpellScriptLoader("spell_sha_ancestral_awakening") { }

    class spell_sha_ancestral_awakening_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_sha_ancestral_awakening_AuraScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_SHAMAN_TIDAL_WAVES))
                return false;
            return true;
        }

        void HandleEffectProc(AuraEffect* aurEff, ProcEventInfo& eventInfo)
        {
            PreventDefaultAction();
            int32 heal = int32(CalculatePct(eventInfo.GetHealInfo()->GetHeal(), aurEff->GetAmount()));

            GetTarget()->CastCustomSpell(SPELL_SHAMAN_ANCESTRAL_AWAKENING, SPELLVALUE_BASE_POINT0, heal, (Unit*)NULL, true, NULL, aurEff);
        }

        void Register() override
        {
            OnEffectProc += AuraEffectProcFn(spell_sha_ancestral_awakening_AuraScript::HandleEffectProc, EFFECT_0, SPELL_AURA_DUMMY);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_sha_ancestral_awakening_AuraScript();
    }
};

// 52759 - Ancestral Awakening
/// Updated 4.3.4
class spell_sha_ancestral_awakening_proc : public SpellScriptLoader
{
public:
    spell_sha_ancestral_awakening_proc() : SpellScriptLoader("spell_sha_ancestral_awakening_proc") { }

    class spell_sha_ancestral_awakening_proc_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_sha_ancestral_awakening_proc_SpellScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_SHAMAN_ANCESTRAL_AWAKENING_PROC))
                return false;
            return true;
        }

        void FilterTargets(std::list<WorldObject*>& targets)
        {
            if (targets.size() < 2)
                return;

            targets.sort(Trinity::HealthPctOrderPred());

            WorldObject* target = targets.front();
            targets.clear();
            targets.push_back(target);
        }

        void HandleDummy(SpellEffIndex /*effIndex*/)
        {
            GetCaster()->CastCustomSpell(SPELL_SHAMAN_ANCESTRAL_AWAKENING_PROC, SPELLVALUE_BASE_POINT0, GetEffectValue(), GetHitUnit(), true);
        }

        void Register() override
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_sha_ancestral_awakening_proc_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_CASTER_AREA_RAID);
            OnEffectHitTarget += SpellEffectFn(spell_sha_ancestral_awakening_proc_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_sha_ancestral_awakening_proc_SpellScript();
    }
};

// 2825 - Bloodlust
class spell_sha_bloodlust : public SpellScriptLoader
{
public:
    spell_sha_bloodlust() : SpellScriptLoader("spell_sha_bloodlust") { }

    class spell_sha_bloodlust_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_sha_bloodlust_SpellScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_SHAMAN_SATED)
                || !sSpellMgr->GetSpellInfo(SPELL_HUNTER_INSANITY)
                || !sSpellMgr->GetSpellInfo(SPELL_MAGE_TEMPORAL_DISPLACEMENT)
                || !sSpellMgr->GetSpellInfo(SPELL_PET_NETHERWINDS_FATIGUED))
                return false;
            return true;
        }

        void RemoveInvalidTargets(std::list<WorldObject*>& targets)
        {
            targets.remove_if(Trinity::UnitAuraCheck(true, SPELL_SHAMAN_SATED));
            targets.remove_if(Trinity::UnitAuraCheck(true, SPELL_HUNTER_INSANITY));
            targets.remove_if(Trinity::UnitAuraCheck(true, SPELL_MAGE_TEMPORAL_DISPLACEMENT));
        }

        void ApplyDebuff()
        {
            if (Unit* target = GetHitUnit())
                target->CastSpell(target, SPELL_SHAMAN_SATED, true);
        }

        void HandleOnCast()
        {
            if (Unit* caster = GetCaster())
                if (caster->HasAura(SPELL_SHAMAN_ANCESTRAL_RESONANCE_POWER))
                    caster->CastSpell(caster, SPELL_SHAMAN_ANCESTRAL_RESONANCE_PERIODIC, true);
        }

        void Register() override
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_sha_bloodlust_SpellScript::RemoveInvalidTargets, EFFECT_0, TARGET_UNIT_CASTER_AREA_RAID);
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_sha_bloodlust_SpellScript::RemoveInvalidTargets, EFFECT_1, TARGET_UNIT_CASTER_AREA_RAID);
            AfterHit += SpellHitFn(spell_sha_bloodlust_SpellScript::ApplyDebuff);
            OnCast += SpellCastFn(spell_sha_bloodlust_SpellScript::HandleOnCast);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_sha_bloodlust_SpellScript();
    }
};

// 1064 - Chain Heal
class spell_sha_chain_heal : public SpellScriptLoader
{
public:
    spell_sha_chain_heal() : SpellScriptLoader("spell_sha_chain_heal") { }

    class spell_sha_chain_heal_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_sha_chain_heal_SpellScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_SHAMAN_HIGH_TIDE))
                return false;
            return true;
        }

        void CatchInitialTarget(WorldObject*& target)
        {
            _primaryTarget = target;
        }

        void SelectAdditionalTargets(std::list<WorldObject*>& targets)
        {
            Unit* caster = GetCaster();
            AuraEffect const* highTide = caster->GetAuraEffect(SPELL_SHAMAN_HIGH_TIDE, EFFECT_1);
            if (!highTide)
                return;

            static float const range = 25.0f;
            SpellImplicitTargetInfo targetInfo(TARGET_UNIT_TARGET_CHAINHEAL_ALLY);
            ConditionContainer* conditions = GetSpellInfo()->GetEffect(EFFECT_0).ImplicitTargetConditions;

            uint32 containerTypeMask = GetSpell()->GetSearcherTypeMask(targetInfo.GetObjectType(), conditions);
            if (!containerTypeMask)
                return;

            std::list<WorldObject*> chainTargets;
            Trinity::WorldObjectSpellAreaTargetCheck check(25.0f, _primaryTarget, caster, caster, GetSpellInfo(), targetInfo.GetCheckType(), conditions, TARGET_OBJECT_TYPE_UNIT);
            Trinity::WorldObjectListSearcher<Trinity::WorldObjectSpellAreaTargetCheck> searcher(caster, chainTargets, check, containerTypeMask);
            Cell::VisitAllObjects(_primaryTarget, searcher, range);

            chainTargets.remove_if(Trinity::UnitAuraCheck(false, SPELL_SHAMAN_RIPTIDE, caster->GetGUID()));
            if (chainTargets.empty())
                return;

            chainTargets.sort();
            targets.sort();

            std::list<WorldObject*> extraTargets;
            std::set_difference(chainTargets.begin(), chainTargets.end(), targets.begin(), targets.end(), std::back_inserter(extraTargets));
            Trinity::Containers::RandomResize(extraTargets, uint32(highTide->GetAmount()));
            targets.splice(targets.end(), extraTargets);
        }

        void HandleEffectHit(SpellEffIndex /*effIndex*/)
        {
            Unit* caster = GetCaster();
            Unit* target = GetHitUnit();
            if (!caster || !target)
                return;


            if (caster->HasAura(SPELL_SHAMAN_DELUGE) && target->HasAura(SPELL_SHAMAN_HEALING_RAIN))
                SetHitHeal(GetHitHeal() + CalculatePct(GetHitHeal(), sSpellMgr->GetSpellInfo(SPELL_SHAMAN_DELUGE)->GetEffect(EFFECT_0).BasePoints));
        }

        void HandleAfterCast()
        {
            if (Unit* caster = GetCaster())
            {
                if (caster->HasAura(SPELL_SHAMAN_FLASH_FLOOD_BUFF))
                    caster->RemoveAurasDueToSpell(SPELL_SHAMAN_FLASH_FLOOD_BUFF);

                if (caster->HasAura(366779)) ///< Heal the soul
                    caster->RemoveAurasDueToSpell(366779);
            }
        }

        WorldObject* _primaryTarget = nullptr;

        void Register() override
        {
            OnObjectTargetSelect += SpellObjectTargetSelectFn(spell_sha_chain_heal_SpellScript::CatchInitialTarget, EFFECT_0, TARGET_UNIT_TARGET_CHAINHEAL_ALLY);
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_sha_chain_heal_SpellScript::SelectAdditionalTargets, EFFECT_0, TARGET_UNIT_TARGET_CHAINHEAL_ALLY);
            OnEffectHitTarget += SpellEffectFn(spell_sha_chain_heal_SpellScript::HandleEffectHit, EFFECT_0, SPELL_EFFECT_HEAL);
            AfterCast += SpellCastFn(spell_sha_chain_heal_SpellScript::HandleAfterCast);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_sha_chain_heal_SpellScript();
    }
};

// 974 - Earth Shield
class spell_sha_earth_shield : public SpellScriptLoader
{
public:
    spell_sha_earth_shield() : SpellScriptLoader("spell_sha_earth_shield") { }

    class spell_sha_earth_shield_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_sha_earth_shield_AuraScript);

        bool CheckProc(ProcEventInfo& eventInfo)
        {
            if (Unit* caster = GetCaster())
                //! HACK due to currenct proc system implementation
                if (eventInfo.GetDamageInfo() && eventInfo.GetDamageInfo()->GetDamage() > 0)
                    return true;

            return false;
        }

        void HandleProc(ProcEventInfo& /*eventInfo*/)
        {
            PreventDefaultAction();
            Unit* caster = GetCaster();
            Unit* target = GetUnitOwner();
            if (!caster || !target)
                return;

            caster->CastSpell(target, SPELL_SHAMAN_EARTH_SHIELD_HEAL, true);
        }

        void Register() override
        {
            DoCheckProc += AuraCheckProcFn(spell_sha_earth_shield_AuraScript::CheckProc);
            OnProc += AuraProcFn(spell_sha_earth_shield_AuraScript::HandleProc);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_sha_earth_shield_AuraScript();
    }
};

// 117014 - Elemental Blast
class spell_sha_elemental_blast : public SpellScript
{
    PrepareSpellScript(spell_sha_elemental_blast);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_SHAMAN_ELEMENTAL_BLAST_CRIT, SPELL_SHAMAN_ELEMENTAL_BLAST_HASTE, SPELL_SHAMAN_ELEMENTAL_BLAST_MASTERY });
    }

    void TriggerBuff()
    {
        Unit* caster = GetCaster();
        Unit* target = GetExplTargetUnit();
        if (!caster || !target)
            return;

        uint32 spellId = RAND(SPELL_SHAMAN_ELEMENTAL_BLAST_CRIT, SPELL_SHAMAN_ELEMENTAL_BLAST_HASTE, SPELL_SHAMAN_ELEMENTAL_BLAST_MASTERY);
        caster->CastSpell(caster, spellId, TRIGGERED_FULL_MASK);

        // Mastery : Elemental Overload
        if (Aura* aura = caster->GetAura(SPELL_SHAMAN_MASTERY_ELEMENTAL_OVERLOAD))
        {
            if (roll_chance_i(aura->GetEffect(EFFECT_0)->GetAmount()))
            {
                uint32 duration = sSpellMgr->GetSpellInfo(SPELL_SHAMAN_UNLIMITED_POWER_HASTE)->GetDuration();

                caster->GetScheduler().Schedule(500ms, [caster, target, &duration](TaskContext context)
                {
                    if (!caster || !target)
                        return;
                    if (!caster->IsInWorld() || caster->isDead() || !target->IsInWorld() || target->isDead())
                        return;

                    caster->CastSpell(target, SPELL_SHAMAN_ELEMENTAL_BLAST_OVERLOAD, true);
                    uint32 bonus = RAND(SPELL_SHAMAN_ELEMENTAL_BLAST_CRIT, SPELL_SHAMAN_ELEMENTAL_BLAST_HASTE, SPELL_SHAMAN_ELEMENTAL_BLAST_MASTERY);
                    caster->CastSpell(caster, bonus, TRIGGERED_FULL_MASK);
                    if (caster->HasAura(SPELL_SHAMAN_UNLIMTED_POWER))
                    {

                        if (Aura* unlimited_aura = caster->GetAura(SPELL_SHAMAN_UNLIMITED_POWER_HASTE))
                            duration = unlimited_aura->GetDuration();
                        caster->CastSpell(caster, SPELL_SHAMAN_UNLIMITED_POWER_HASTE, true);
                        if (Aura* unlimited_aura = caster->GetAura(SPELL_SHAMAN_UNLIMITED_POWER_HASTE))
                            unlimited_aura->SetDuration(duration);
                    }
                });
            }
        }
    }

    void Register() override
    {
        AfterCast += SpellCastFn(spell_sha_elemental_blast::TriggerBuff);
    }
};

// 1535 Fire Nova
class spell_sha_fire_nova : public SpellScriptLoader
{
public:
    spell_sha_fire_nova() : SpellScriptLoader("spell_sha_fire_nova") { }

    class spell_sha_fire_nova_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_sha_fire_nova_SpellScript);

        void HandleDummy(SpellEffIndex /*effIndex*/)
        {
            if (Unit* target = GetHitUnit())
                if (target->HasAura(SPELL_SHAMAN_FLAME_SHOCK))
                    GetCaster()->CastSpell(target, SPELL_SHAMAN_FIRE_NOVA_TRIGGERED, true);
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_sha_fire_nova_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_sha_fire_nova_SpellScript();
    }
};

// 10400 - Flametongue
// 194084 - Flametongue
class spell_sha_flametongue : public AuraScript
{
    PrepareAuraScript(spell_sha_flametongue);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_SHAMAN_FLAMETONGUE_ATTACK });
    }

    void HandleEffectProc(AuraEffect* aurEff, ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();
        Unit* caster = GetCaster();
        Unit* target = eventInfo.GetActionTarget();
        if (!caster || !target)
            return;

        caster->CastSpell(target, SPELL_SHAMAN_FLAMETONGUE_ATTACK, true);
    }

    void Register() override
    {
        OnEffectProc += AuraEffectProcFn(spell_sha_flametongue::HandleEffectProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

// 88766 - Fulmination
class spell_sha_fulmination : public SpellScriptLoader
{
public:
    spell_sha_fulmination() : SpellScriptLoader("spell_sha_fulmination") { }

    class spell_sha_fulmination_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_sha_fulmination_AuraScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_SHAMAN_FULMINATION))
                return false;
            if (!sSpellMgr->GetSpellInfo(SPELL_SHAMAN_FULMINATION_INFO))
                return false;
            if (!sSpellMgr->GetSpellInfo(SPELL_SHAMAN_IMPROVED_LIGHTNING_SHIELD))
                return false;
            SpellInfo const* lightningShield = sSpellMgr->GetSpellInfo(SPELL_SHAMAN_LIGHTNING_SHIELD);
            if (!lightningShield || !sSpellMgr->GetSpellInfo(lightningShield->GetEffect(EFFECT_0).TriggerSpell))
                return false;
            if (!sSpellMgr->GetSpellInfo(SPELL_SHAMAN_ITEM_T18_ELEMENTAL_2P_BONUS))
                return false;
            if (!sSpellMgr->GetSpellInfo(SPELL_SHAMAN_ITEM_T18_ELEMENTAL_4P_BONUS))
                return false;
            if (!sSpellMgr->GetSpellInfo(SPELL_SHAMAN_ITEM_T18_LIGHTNING_VORTEX))
                return false;
            return true;
        }

        bool CheckProc(ProcEventInfo& eventInfo)
        {
            // Lava Burst cannot add lightning shield stacks without Improved Lightning Shield
            if ((eventInfo.GetSpellInfo()->SpellFamilyFlags[1] & 0x00001000) && !eventInfo.GetActor()->HasAura(SPELL_SHAMAN_IMPROVED_LIGHTNING_SHIELD))
                return false;

            return eventInfo.GetActor()->HasAura(SPELL_SHAMAN_LIGHTNING_SHIELD);
        }

        void HandleEffectProc(AuraEffect* aurEff, ProcEventInfo& eventInfo)
        {
            Unit* caster = eventInfo.GetActor();
            Unit* target = eventInfo.GetActionTarget();
            if (Aura* aura = caster->GetAura(SPELL_SHAMAN_LIGHTNING_SHIELD))
            {
                // Earth Shock releases the charges
                if (eventInfo.GetSpellInfo()->SpellFamilyFlags[0] & 0x00100000)
                {
                    uint32 stacks = aura->GetCharges();
                    if (stacks > 1)
                    {
                        SpellInfo const* triggerSpell = sSpellMgr->AssertSpellInfo(aura->GetEffect(EFFECT_0)->GetSpellEffectInfo().TriggerSpell);
                        auto triggerEffect = triggerSpell->GetEffect(EFFECT_0);

                        uint32 damage;
                        damage = caster->SpellDamageBonusDone(target, triggerSpell, uint32(triggerEffect.CalcValue(caster)), SPELL_DIRECT_DAMAGE, triggerEffect, stacks - 1);
                        damage = target->SpellDamageBonusTaken(caster, triggerSpell, damage, SPELL_DIRECT_DAMAGE);

                        caster->CastCustomSpell(SPELL_SHAMAN_FULMINATION, SPELLVALUE_BASE_POINT0, int32(damage), target, TRIGGERED_FULL_MASK);
                        caster->RemoveAurasDueToSpell(SPELL_SHAMAN_FULMINATION_INFO);

                        if (AuraEffect const* t18_4p = caster->GetAuraEffect(SPELL_SHAMAN_ITEM_T18_ELEMENTAL_4P_BONUS, EFFECT_0))
                        {
                            if (Aura* gatheringVortex = caster->GetAura(SPELL_SHAMAN_ITEM_T18_GATHERING_VORTEX))
                            {
                                if (gatheringVortex->GetStackAmount() + stacks >= uint32(t18_4p->GetAmount()))
                                    caster->CastSpell(caster, SPELL_SHAMAN_ITEM_T18_LIGHTNING_VORTEX, TRIGGERED_FULL_MASK);

                                if (uint8 newStacks = uint8((gatheringVortex->GetStackAmount() + stacks) % t18_4p->GetAmount()))
                                    gatheringVortex->SetStackAmount(newStacks);
                                else
                                    gatheringVortex->Remove();
                            }
                            else
                                caster->CastCustomSpell(SPELL_SHAMAN_ITEM_T18_GATHERING_VORTEX, SPELLVALUE_AURA_STACK, stacks, caster, TRIGGERED_FULL_MASK);
                        }

                        if (AuraEffect const* t18_2p = caster->GetAuraEffect(SPELL_SHAMAN_ITEM_T18_ELEMENTAL_2P_BONUS, EFFECT_0))
                        {
                            if (roll_chance_i(t18_2p->GetAmount()))
                            {
                                caster->GetSpellHistory()->ResetCooldown(SPELL_SHAMAN_EARTH_SHOCK, true);
                                return;
                            }
                        }

                        aura->SetCharges(1);
                        aura->SetUsingCharges(false);
                    }
                }
                else
                {
                    aura->SetCharges(std::min<uint8>(aura->GetCharges() + 1, uint8(aurEff->GetAmount())));
                    aura->SetUsingCharges(false);
                    aura->RefreshDuration();

                    if (aura->GetCharges() == aurEff->GetAmount())
                        caster->CastSpell(caster, SPELL_SHAMAN_FULMINATION_INFO, TRIGGERED_FULL_MASK);
                }
            }
        }

        void Register() override
        {
            DoCheckProc += AuraCheckProcFn(spell_sha_fulmination_AuraScript::CheckProc);
            OnEffectProc += AuraEffectProcFn(spell_sha_fulmination_AuraScript::HandleEffectProc, EFFECT_0, SPELL_AURA_DUMMY);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_sha_fulmination_AuraScript();
    }
};

// 55440 - Glyph of Healing Wave
class spell_sha_glyph_of_healing_wave : public SpellScriptLoader
{
public:
    spell_sha_glyph_of_healing_wave() : SpellScriptLoader("spell_sha_glyph_of_healing_wave") { }

    class spell_sha_glyph_of_healing_wave_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_sha_glyph_of_healing_wave_AuraScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_SHAMAN_GLYPH_OF_HEALING_WAVE))
                return false;
            return true;
        }

        bool CheckProc(ProcEventInfo& eventInfo)
        {
            // Not proc from self heals
            return GetTarget() != eventInfo.GetProcTarget();
        }

        void HandleEffectProc(AuraEffect* aurEff, ProcEventInfo& eventInfo)
        {
            PreventDefaultAction();
            int32 heal = CalculatePct(int32(eventInfo.GetHealInfo()->GetHeal()), aurEff->GetAmount());

            GetTarget()->CastCustomSpell(SPELL_SHAMAN_GLYPH_OF_HEALING_WAVE, SPELLVALUE_BASE_POINT0, heal, (Unit*)NULL, true, NULL, aurEff);
        }

        void Register() override
        {
            DoCheckProc += AuraCheckProcFn(spell_sha_glyph_of_healing_wave_AuraScript::CheckProc);
            OnEffectProc += AuraEffectProcFn(spell_sha_glyph_of_healing_wave_AuraScript::HandleEffectProc, EFFECT_0, SPELL_AURA_DUMMY);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_sha_glyph_of_healing_wave_AuraScript();
    }
};

// 5394 - Healing Stream Totem
class spell_sha_healing_stream_totem : public SpellScriptLoader
{
public:
    spell_sha_healing_stream_totem() : SpellScriptLoader("spell_sha_healing_stream_totem") { }

    class spell_sha_healing_stream_totem_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_sha_healing_stream_totem_AuraScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            return sSpellMgr->GetSpellInfo(SPELL_SHAMAN_TOTEM_HEALING_STREAM_HEAL) != nullptr;
        }

        void HandleDummy(AuraEffect const* aurEff)
        {
            if (Creature* waterTotem = GetTarget()->GetMap()->GetCreature(GetTarget()->m_SummonSlot[3]))
                waterTotem->CastSpell(waterTotem->GetPosition(), SPELL_SHAMAN_TOTEM_HEALING_STREAM_HEAL, CastSpellExtraArgs(TRIGGERED_FULL_MASK).SetTriggeringAura(aurEff));
        }

        void Register() override
        {
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_sha_healing_stream_totem_AuraScript::HandleDummy, EFFECT_1, SPELL_AURA_PERIODIC_DUMMY);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_sha_healing_stream_totem_AuraScript();
    }
};

//192077 - Wind Rush Totem
class spell_sha_wind_rush_totem : public SpellScriptLoader
{
public:
    spell_sha_wind_rush_totem() : SpellScriptLoader("spell_sha_wind_rush_totem") { }

    class spell_sha_wind_rush_totem_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_sha_wind_rush_totem_AuraScript);

        void Register() override
        {

        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_sha_wind_rush_totem_AuraScript();
    }
};

// 52042 - Healing Stream Totem
class spell_sha_healing_stream_totem_heal : public SpellScriptLoader
{
public:
    spell_sha_healing_stream_totem_heal() : SpellScriptLoader("spell_sha_healing_stream_totem_heal") { }

    class spell_sha_healing_stream_totem_heal_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_sha_healing_stream_totem_heal_SpellScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_SHAMAN_RUSHING_STREAMS) ||
                !sSpellMgr->GetSpellInfo(SPELL_SHAMAN_GLYPH_OF_HEALING_STREAM_TOTEM) ||
                !sSpellMgr->GetSpellInfo(SPELL_SHAMAN_GLYPH_OF_HEALING_STREAM_TOTEM_TRIGGERED) ||
                !sSpellMgr->GetSpellInfo(SPELL_SHAMAN_HEALING_STREAM_DUMMY))
                return false;

            return true;
        }

        void SelectTargets(std::list<WorldObject*>& targets)
        {
            uint32 targetLimit = 1;
            if (GetOriginalCaster()->HasAura(SPELL_SHAMAN_RUSHING_STREAMS))
                targetLimit = 2;

            targets.remove_if([](WorldObject* target)
                {
                    return !target->ToUnit() || target->ToUnit()->IsFullHealth();
                });

            Trinity::Containers::RandomResize(targets, targetLimit);

            if (targets.empty())
                targets.push_back(GetOriginalCaster());
        }

        void HandleEffect(SpellEffIndex /*effIndex*/)
        {
            if (GetOriginalCaster()->HasAura(SPELL_SHAMAN_GLYPH_OF_HEALING_STREAM_TOTEM))
                GetCaster()->CastSpell(GetHitUnit(), SPELL_SHAMAN_GLYPH_OF_HEALING_STREAM_TOTEM_TRIGGERED, TRIGGERED_FULL_MASK);

            GetCaster()->CastSpell(GetHitUnit(), SPELL_SHAMAN_HEALING_STREAM_DUMMY, TRIGGERED_FULL_MASK);
        }

        void Register() override
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_sha_healing_stream_totem_heal_SpellScript::SelectTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ALLY);
            OnEffectHitTarget += SpellEffectFn(spell_sha_healing_stream_totem_heal_SpellScript::HandleEffect, EFFECT_0, SPELL_EFFECT_HEAL);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_sha_healing_stream_totem_heal_SpellScript();
    }
};

// 32182 - Heroism
class spell_sha_heroism : public SpellScriptLoader
{
public:
    spell_sha_heroism() : SpellScriptLoader("spell_sha_heroism") { }

    class spell_sha_heroism_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_sha_heroism_SpellScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_SHAMAN_EXHAUSTION)
                || !sSpellMgr->GetSpellInfo(SPELL_HUNTER_INSANITY)
                || !sSpellMgr->GetSpellInfo(SPELL_MAGE_TEMPORAL_DISPLACEMENT)
                || !sSpellMgr->GetSpellInfo(SPELL_PET_NETHERWINDS_FATIGUED))
                return false;
            return true;
        }

        void RemoveInvalidTargets(std::list<WorldObject*>& targets)
        {
            targets.remove_if(Trinity::UnitAuraCheck(true, SPELL_SHAMAN_EXHAUSTION));
            targets.remove_if(Trinity::UnitAuraCheck(true, SPELL_HUNTER_INSANITY));
            targets.remove_if(Trinity::UnitAuraCheck(true, SPELL_MAGE_TEMPORAL_DISPLACEMENT));
        }

        void ApplyDebuff()
        {
            if (Unit* target = GetHitUnit())
                target->CastSpell(target, SPELL_SHAMAN_EXHAUSTION, true);
        }

        void HandleOnCast()
        {
            if (Unit* caster = GetCaster())
                if (caster->HasAura(SPELL_SHAMAN_ANCESTRAL_RESONANCE_POWER))
                    caster->CastSpell(caster, SPELL_SHAMAN_ANCESTRAL_RESONANCE_PERIODIC, true);
        }

        void Register() override
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_sha_heroism_SpellScript::RemoveInvalidTargets, EFFECT_0, TARGET_UNIT_CASTER_AREA_RAID);
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_sha_heroism_SpellScript::RemoveInvalidTargets, EFFECT_1, TARGET_UNIT_CASTER_AREA_RAID);
            AfterHit += SpellHitFn(spell_sha_heroism_SpellScript::ApplyDebuff);
            OnCast += SpellCastFn(spell_sha_heroism_SpellScript::HandleOnCast);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_sha_heroism_SpellScript();
    }
};

// 23551 - Lightning Shield
class spell_sha_item_lightning_shield : public SpellScriptLoader
{
public:
    spell_sha_item_lightning_shield() : SpellScriptLoader("spell_sha_item_lightning_shield") { }

    class spell_sha_item_lightning_shield_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_sha_item_lightning_shield_AuraScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_SHAMAN_ITEM_LIGHTNING_SHIELD))
                return false;
            return true;
        }

        void OnProc(AuraEffect* aurEff, ProcEventInfo& eventInfo)
        {
            PreventDefaultAction();
            GetTarget()->CastSpell(eventInfo.GetProcTarget(), SPELL_SHAMAN_ITEM_LIGHTNING_SHIELD, CastSpellExtraArgs(true).SetTriggeringAura(aurEff));
        }

        void Register() override
        {
            OnEffectProc += AuraEffectProcFn(spell_sha_item_lightning_shield_AuraScript::OnProc, EFFECT_0, SPELL_AURA_PROC_TRIGGER_SPELL);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_sha_item_lightning_shield_AuraScript();
    }
};

// 23552 - Lightning Shield
class spell_sha_item_lightning_shield_trigger : public SpellScriptLoader
{
public:
    spell_sha_item_lightning_shield_trigger() : SpellScriptLoader("spell_sha_item_lightning_shield_trigger") { }

    class spell_sha_item_lightning_shield_trigger_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_sha_item_lightning_shield_trigger_AuraScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_SHAMAN_ITEM_LIGHTNING_SHIELD_DAMAGE))
                return false;
            return true;
        }

        void OnProc(AuraEffect* aurEff, ProcEventInfo& /*eventInfo*/)
        {
            PreventDefaultAction();
            GetTarget()->CastSpell(GetTarget(), SPELL_SHAMAN_ITEM_LIGHTNING_SHIELD_DAMAGE, aurEff);
        }

        void Register() override
        {
            OnEffectProc += AuraEffectProcFn(spell_sha_item_lightning_shield_trigger_AuraScript::OnProc, EFFECT_0, SPELL_AURA_PROC_TRIGGER_SPELL);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_sha_item_lightning_shield_trigger_AuraScript();
    }
};

// 23572 - Mana Surge
class spell_sha_item_mana_surge : public SpellScriptLoader
{
public:
    spell_sha_item_mana_surge() : SpellScriptLoader("spell_sha_item_mana_surge") { }

    class spell_sha_item_mana_surge_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_sha_item_mana_surge_AuraScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_SHAMAN_ITEM_LIGHTNING_SHIELD_DAMAGE))
                return false;
            return true;
        }

        void OnProc(AuraEffect* aurEff, ProcEventInfo& eventInfo)
        {
            PreventDefaultAction();
            std::vector<SpellPowerCost> costs = eventInfo.GetDamageInfo()->GetSpellInfo()->CalcPowerCost(GetTarget(), eventInfo.GetDamageInfo()->GetSchoolMask());
            auto m = std::find_if(costs.begin(), costs.end(), [](SpellPowerCost const& cost) { return cost.Power == POWER_MANA; });
            if (m != costs.end())
            {
                int32 mana = CalculatePct(m->Amount, 35);
                if (mana > 0)
                    GetTarget()->CastCustomSpell(SPELL_SHAMAN_ITEM_MANA_SURGE, SPELLVALUE_BASE_POINT0, mana, GetTarget(), true, NULL, aurEff);
            }
        }

        void Register() override
        {
            OnEffectProc += AuraEffectProcFn(spell_sha_item_mana_surge_AuraScript::OnProc, EFFECT_0, SPELL_AURA_PROC_TRIGGER_SPELL);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_sha_item_mana_surge_AuraScript();
    }
};

// 70811 - Item - Shaman T10 Elemental 2P Bonus
class spell_sha_item_t10_elemental_2p_bonus : public SpellScriptLoader
{
public:
    spell_sha_item_t10_elemental_2p_bonus() : SpellScriptLoader("spell_sha_item_t10_elemental_2p_bonus") { }

    class spell_sha_item_t10_elemental_2p_bonus_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_sha_item_t10_elemental_2p_bonus_AuraScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_SHAMAN_ELEMENTAL_MASTERY))
                return false;
            return true;
        }

        void HandleEffectProc(AuraEffect* aurEff, ProcEventInfo& /*eventInfo*/)
        {
            PreventDefaultAction();
            if (Player* target = GetTarget()->ToPlayer())
                target->GetSpellHistory()->ModifyCooldown(SPELL_SHAMAN_ELEMENTAL_MASTERY, -aurEff->GetAmount());
        }

        void Register() override
        {
            OnEffectProc += AuraEffectProcFn(spell_sha_item_t10_elemental_2p_bonus_AuraScript::HandleEffectProc, EFFECT_0, SPELL_AURA_DUMMY);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_sha_item_t10_elemental_2p_bonus_AuraScript();
    }
};

// 189063 - Lightning Vortex (proc 185881 Item - Shaman T18 Elemental 4P Bonus)
class spell_sha_item_t18_elemental_4p_bonus : public SpellScriptLoader
{
public:
    spell_sha_item_t18_elemental_4p_bonus() : SpellScriptLoader("spell_sha_item_t18_elemental_4p_bonus") { }

    class spell_sha_item_t18_elemental_4p_bonus_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_sha_item_t18_elemental_4p_bonus_AuraScript);

        void DiminishHaste(AuraEffect const* aurEff)
        {
            PreventDefaultAction();
            if (AuraEffect* hasteBuff = GetEffect(EFFECT_0))
                hasteBuff->ChangeAmount(hasteBuff->GetAmount() - aurEff->GetAmount());
        }

        void Register() override
        {
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_sha_item_t18_elemental_4p_bonus_AuraScript::DiminishHaste, EFFECT_1, SPELL_AURA_PERIODIC_DUMMY);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_sha_item_t18_elemental_4p_bonus_AuraScript();
    }
};

// 105792 - Lava Lash
class spell_sha_lava_lash_spread_flame_shock : public SpellScriptLoader
{
public:
    spell_sha_lava_lash_spread_flame_shock() : SpellScriptLoader("spell_sha_lava_lash_spread_flame_shock") { }

    class spell_sha_lava_lash_spread_flame_shock_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_sha_lava_lash_spread_flame_shock_SpellScript);

        bool Load() override
        {
            return GetCaster()->GetTypeId() == TYPEID_PLAYER;
        }

        void HandleScript(SpellEffIndex /*effIndex*/)
        {
            if (!GetCaster())
                return;

            if (Unit* mainTarget = GetExplTargetUnit())
            {
                if (Aura* flameShock = mainTarget->GetAura(SPELL_SHAMAN_FLAME_SHOCK_ELEM, GetCaster()->GetGUID()))
                {
                    flameShock->RefreshDuration();
                }
            }
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_sha_lava_lash_spread_flame_shock_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_sha_lava_lash_spread_flame_shock_SpellScript();
    }
};

// 77756 - Lava Surge
class spell_sha_lava_surge : public AuraScript
{
    PrepareAuraScript(spell_sha_lava_surge);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_SHAMAN_LAVA_SURGE });
    }

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (Unit* caster = GetCaster())
            if (caster->HasAura(SPELL_SHAMAN_CONTROL_OF_LAVA))
                return false;

        if (eventInfo.GetSpellInfo() && (eventInfo.GetSpellInfo()->Id == SPELL_SHAMAN_FLAME_SHOCK_ELEM || eventInfo.GetSpellInfo()->Id == SPELL_SHAMAN_FLAME_SHOCK_ELEM_RESTO))
            return true;
        return false;
    }

    void HandleEffectProc(AuraEffect* /*aurEff*/, ProcEventInfo& /*eventInfo*/)
    {
        PreventDefaultAction();
        if (Unit* caster = GetCaster())
        {
            caster->CastSpell(caster, SPELL_SHAMAN_LAVA_SURGE_CAST_TIME, true);
            if (caster->HasAura(SPELL_SHAMAN_ECHO_OF_THE_ELEMENTS))
                caster->CastSpell(caster, SPELL_SHAMAN_LAVA_SURGE_VISUAL, true);
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_sha_lava_surge::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_sha_lava_surge::HandleEffectProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

// 77762 - Lava Surge
class spell_sha_lava_surge_proc : public AuraScript
{
    PrepareAuraScript(spell_sha_lava_surge_proc);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_SHAMAN_LAVA_BURST });
    }

    bool Load() override
    {
        if (auto caster = GetCaster())
            return caster->IsPlayer();
        return false;
    }

    void HandleApply(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        if (Unit* caster = GetCaster())
            caster->GetSpellHistory()->RestoreCharge(sSpellMgr->AssertSpellInfo(SPELL_SHAMAN_LAVA_BURST)->ChargeCategoryId);
    }

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();
        if (!caster && !eventInfo.GetSpellInfo())
            return false;

        if (caster->HasAura(SPELL_SHAMAN_CONTROL_OF_LAVA))
            return false;

        // Only proc when Lava Bust was instant one.
        if (eventInfo.GetSpellInfo()->Id == SPELL_SHAMAN_LAVA_BURST && GetCaster() && caster->GetCurrentSpellCastTime(SPELL_SHAMAN_LAVA_BURST) == 0)
        {
            caster->RemoveAurasDueToSpell(SPELL_SHAMAN_LAVA_SURGE_VISUAL);
            return true;
        }
        return false;
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_sha_lava_surge_proc::HandleApply, EFFECT_0, SPELL_AURA_ADD_PCT_MODIFIER, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
        DoCheckProc += AuraCheckProcFn(spell_sha_lava_surge_proc::CheckProc);
    }
};

// 324 - Lightning Shield
class spell_sha_lightning_shield : public SpellScriptLoader
{
public:
    spell_sha_lightning_shield() : SpellScriptLoader("spell_sha_lightning_shield") { }

    class spell_sha_lightning_shield_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_sha_lightning_shield_AuraScript);

        void UnsetUsingCharges(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            GetAura()->SetUsingCharges(false);
        }

        void Register() override
        {
            OnEffectApply += AuraEffectApplyFn(spell_sha_lightning_shield_AuraScript::UnsetUsingCharges, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_sha_lightning_shield_AuraScript();
    }
};

// 30884 - Nature's Guardian
class spell_sha_nature_guardian : public SpellScriptLoader
{
public:
    spell_sha_nature_guardian() : SpellScriptLoader("spell_sha_nature_guardian") { }

    class spell_sha_nature_guardian_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_sha_nature_guardian_AuraScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            return ValidateSpellInfo({ SPELL_SHAMAN_NATURE_GUARDIAN });
        }

        bool CheckProc(ProcEventInfo& eventInfo)
        {
            if (Unit* caster = GetCaster())
                if (eventInfo.GetDamageInfo() && eventInfo.GetDamageInfo()->GetDamage() > 0 &&
                    caster->HealthBelowPct(sSpellMgr->GetSpellInfo(SPELL_SHAMAN_NATURE_GUARDIAN)->GetEffect(EFFECT_0).BasePoints))
                    return true;

            return false;
        }

        void HandleProc(ProcEventInfo& eventInfo)
        {
            PreventDefaultAction();
            if (Unit* caster = GetCaster())
                caster->CastSpell(caster, SPELL_SHAMAN_NATURE_GUARDIAN_HEAL, true);
        }

        void Register() override
        {
            DoCheckProc += AuraCheckProcFn(spell_sha_nature_guardian_AuraScript::CheckProc);
            OnProc += AuraProcFn(spell_sha_nature_guardian_AuraScript::HandleProc);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_sha_nature_guardian_AuraScript();
    }
};

// 51490 - Thunderstorm
class spell_sha_thunderstorm : public SpellScriptLoader
{
public:
    spell_sha_thunderstorm() : SpellScriptLoader("spell_sha_thunderstorm") { }

    class spell_sha_thunderstorm_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_sha_thunderstorm_SpellScript);

        void HandleKnockBack(SpellEffIndex effIndex)
        {
            if (Unit* caster = GetCaster())
            {
                // Glyph of Thunderstorm
                if (caster->HasAura(SPELL_SHAMAN_GLYPH_OF_THUNDERSTORM))
                    PreventHitDefaultEffect(effIndex);

                if (Aura* aura = caster->GetAura(SPELL_SHAMAN_MASTER_OF_THE_ELEMENTS))
                {
                    SetHitDamage(GetHitDamage() + CalculatePct(GetHitDamage(), aura->GetEffect(EFFECT_0)->GetBaseAmount()));
                    caster->RemoveAurasDueToSpell(SPELL_SHAMAN_MASTER_OF_THE_ELEMENTS);
                }
            }
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_sha_thunderstorm_SpellScript::HandleKnockBack, EFFECT_1, SPELL_EFFECT_KNOCK_BACK);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_sha_thunderstorm_SpellScript();
    }
};

// 51564 - Tidal Waves
class spell_sha_tidal_waves : public AuraScript
{
    PrepareAuraScript(spell_sha_tidal_waves);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_SHAMAN_TIDAL_WAVES });
    }

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetSpellInfo())
            return false;

        switch (eventInfo.GetSpellInfo()->Id)
        {
            case SPELL_CHAIN_HEAL:
            case SPELL_RIPTIDE:
                return true;
            default:
                return false;
        }

        return false;
    }

    void HandleEffectProc(AuraEffect* /*aurEff*/, ProcEventInfo& /*eventInfo*/)
    {
        PreventDefaultAction();
        GetTarget()->CastSpell(GetTarget(), SPELL_SHAMAN_TIDAL_WAVES, true);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_sha_tidal_waves::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_sha_tidal_waves::HandleEffectProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

// 8232 - Windfury Weapon
class spell_shaman_windfury_weapon : public SpellScriptLoader
{
public:
    spell_shaman_windfury_weapon() : SpellScriptLoader("spell_shaman_windfury_weapon") {}

    class spell_shaman_windfury_weapon_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_shaman_windfury_weapon_SpellScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            return sSpellMgr->GetSpellInfo(SPELL_SHAMAN_WINDFURY_WEAPON_PASSIVE) != nullptr;
        }

        void HandleDummy(SpellEffIndex /*effIndex*/)
        {
            if (Unit* caster = GetCaster())
                if (AuraEffect* auraEffect = caster->GetAuraEffect(SPELL_SHAMAN_WINDFURY_WEAPON_PASSIVE, EFFECT_0))
                    auraEffect->SetAmount(GetEffectValue());
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_shaman_windfury_weapon_SpellScript::HandleDummy, EFFECT_1, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_shaman_windfury_weapon_SpellScript();
    }
};

// 61882 - Earthquake
class aura_sha_earthquake : public AuraScript
{
    PrepareAuraScript(aura_sha_earthquake);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_SHAMAN_EARTHQUAKE, SPELL_SHAMAN_ELEMENTAL_SHAMAN });
    }

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
        if (Unit* caster = GetCaster())
            if (AreaTrigger* at = caster->GetAreaTrigger(SPELL_SHAMAN_EARTHQUAKE))
            {
                // damage = $SPN * 0.25 * ($137040s1 + 100) / 100
                // $damage=${$SPN*0.391*$d/$t2*(1+$@versadmg)*(($137040s1+100)/100)*$<mawPower>}
                auto sp = caster->GetTotalSpellPowerValue(SPELL_SCHOOL_MASK_NATURE, false);
                int32 damage = sp * 0.391f * (sSpellMgr->GetSpellInfo(SPELL_SHAMAN_ELEMENTAL_SHAMAN)->GetEffect(EFFECT_0).BasePoints + 100) / 100;

                if (auto player = caster->ToPlayer())
                {
                    auto versa = player->m_activePlayerData->Versatility + player->m_activePlayerData->VersatilityBonus;
                    AddPct(damage, versa);
                }

                caster->CastSpell(*at, SPELL_SHAMAN_EARTHQUAKE_TICK, CastSpellExtraArgs(true).AddSpellBP0(damage));
            }
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(aura_sha_earthquake::HandlePeriodic, EFFECT_1, SPELL_AURA_PERIODIC_DUMMY);
    }
};

// 77478 - Earthquake Damage
class spell_sha_earthquake_tick : public SpellScript
{
    PrepareSpellScript(spell_sha_earthquake_tick);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_SHAMAN_EARTHQUAKE_TICK });
    }

    void HandleOnHit()
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        if (roll_chance_i(sSpellMgr->GetSpellInfo(SPELL_SHAMAN_EARTHQUAKE_TICK)->GetEffect(EFFECT_1).BasePoints))
            caster->CastSpell(target, SPELL_SHAMAN_EARTHQUAKE_KNOCKING_DOWN, true);
    }

    void Register() override
    {
        OnHit += SpellHitFn(spell_sha_earthquake_tick::HandleOnHit);
    }
};

class spell_sha_glyph_of_lakestrider : public SpellScriptLoader
{
public:
    spell_sha_glyph_of_lakestrider() : SpellScriptLoader("spell_sha_glyph_of_lakestrider") { }

    class spell_sha_glyph_of_lakestrider_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_sha_glyph_of_lakestrider_SpellScript);

        void HandleOnHit()
        {
            if (Player* _player = GetCaster()->ToPlayer())
                if (_player->HasAura(SPELL_SHAMAN_GLYPH_OF_LAKESTRIDER))
                    _player->CastSpell(_player, SPELL_SHAMAN_WATER_WALKING, true);
        }

        void Register() override
        {
            OnHit += SpellHitFn(spell_sha_glyph_of_lakestrider_SpellScript::HandleOnHit);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_sha_glyph_of_lakestrider_SpellScript();
    }
};

class spell_sha_healing_stream : public SpellScriptLoader
{
public:
    spell_sha_healing_stream() : SpellScriptLoader("spell_sha_healing_stream") { }

    class spell_sha_healing_stream_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_sha_healing_stream_SpellScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_SHAMAN_HEALING_STREAM))
                return false;
            return true;
        }

        void HandleOnHit()
        {
            if (!GetCaster()->GetOwner())
                return;

            if (Player* _player = GetCaster()->GetOwner()->ToPlayer())
                if (Unit* target = GetHitUnit())
                    // Glyph of Healing Stream Totem
                    if (target->GetGUID() != _player->GetGUID() && _player->HasAura(SPELL_SHAMAN_GLYPH_OF_HEALING_STREAM_TOTEM))
                        _player->CastSpell(target, SPELL_SHAMAN_GLYPH_OF_HEALING_STREAM, true);
        }

        void Register() override
        {
            OnHit += SpellHitFn(spell_sha_healing_stream_SpellScript::HandleOnHit);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_sha_healing_stream_SpellScript();
    }
};

//Called by 98020 Spirit link
//Last Update 8.0.1 Build 28153
class spell_sha_spirit_link : public SpellScript
{
    PrepareSpellScript(spell_sha_spirit_link);

    bool Load() override
    {
        averagePercentage = 0.0f;
        return true;
    }

    void FilterTargets(std::list<WorldObject*>& unitList)
    {
        uint32 targetCount = 0;
        for (std::list<WorldObject*>::const_iterator itr = unitList.begin(); itr != unitList.end(); ++itr)
        {
            if (Unit* target = (*itr)->ToUnit())
            {
                if (target->IsPlayer())
                {
                    targets[target->GetGUID()] = target->GetHealthPct();
                    averagePercentage += target->GetHealthPct();
                    ++targetCount;
                }
            }
        }

        if (targetCount)
            averagePercentage /= targetCount;
    }

    void HandleOnHit()
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        if (targets.find(target->GetGUID()) == targets.end())
            return;

        int32 bp0 = 0;
        int32 bp1 = 0;
        float percentage = targets[target->GetGUID()];
        int64 currentHp = target->CountPctFromMaxHealth(percentage);
        int64 desiredHp = target->CountPctFromMaxHealth(averagePercentage);
        if (desiredHp > currentHp)
            bp1 = desiredHp - currentHp;
        else
            bp0 = currentHp - desiredHp;
        caster->CastCustomSpell(target, SPELL_SHAMAN_SPIRIT_LINK_HEAL_DPS, &bp0, &bp1, NULL, false);
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_sha_spirit_link::FilterTargets, EFFECT_0, TARGET_UNIT_CASTER_AREA_RAID);
        OnHit += SpellHitFn(spell_sha_spirit_link::HandleOnHit);
    }

private:
    std::map<ObjectGuid, float> targets;
    float averagePercentage;
};

class spell_sha_spiritwalkers_grace : public SpellScriptLoader
{
public:
    spell_sha_spiritwalkers_grace() : SpellScriptLoader("spell_sha_spiritwalkers_grace") { }

    class spell_sha_spiritwalkers_grace_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_sha_spiritwalkers_grace_SpellScript);

        void HandleOnHit()
        {
            Unit* caster = GetCaster();
            if (caster->HasAura(159651))
                caster->CastSpell(caster, 159652, true);
        }

        void Register() override
        {
            OnHit += SpellHitFn(spell_sha_spiritwalkers_grace_SpellScript::HandleOnHit);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_sha_spiritwalkers_grace_SpellScript();
    }
};

enum Resurgence
{
    SPELL_WATER_SHIELD = 52127,  // Player must have this aura to let the spell proc
    SPELL_RESURGENCE = 16196,  // Dummy aura applied on the player (spec spell)
    SPELL_RESURGENCE_PROC = 101033, // Regenerate life according to the spell that triggered the proc

    /* Spells that can cause the proc  */
    SPELL_HEALING_WAVE = 331,
    SPELL_GREATER_HEALING_WAVE = 77472,
    SPELL_HEALING_SURGE = 8004,
    SPELL_UNLEASH_LIFE = 73685, // Triggered when Unleashed Elements is used on Earthliving Weapon
};

// Script to handle the dummy proc of 16196
class spell_sha_resurgence : public SpellScriptLoader
{
public:
    spell_sha_resurgence() : SpellScriptLoader("spell_sha_resurgence") { }

    class spell_sha_resurgence_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_sha_resurgence_AuraScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            return ValidateSpellInfo({ SPELL_WATER_SHIELD, SPELL_RESURGENCE, SPELL_RESURGENCE_PROC });
        }

        // Spell cannot proc if caster doesn't have aura 52127
        bool CheckDummyProc(ProcEventInfo& procInfo)
        {
            if (Unit* target = procInfo.GetActor())
                return target->HasAura(SPELL_WATER_SHIELD);

            return false;
        }

        void HandleDummyProc(ProcEventInfo& procInfo)
        {
            int32 healAmount = 0;
            if (Unit* target = procInfo.GetActor())
            {
                healAmount = target->CalculateSpellDamage(target, sSpellMgr->GetSpellInfo(SPELL_RESURGENCE_PROC)->GetEffect(EFFECT_0));
                if (healAmount)
                {
                    // Change heal amount accoring to the spell that triggered this one */
                    if (DamageInfo* damageInfo = procInfo.GetDamageInfo())
                    {
                        switch (damageInfo->GetSpellInfo()->Id)
                        {
                            // 100% on Healing Wave and Greater Healing Wave
                        case SPELL_HEALING_WAVE:
                        case SPELL_GREATER_HEALING_WAVE:
                            break;

                            // 60% on Riptide, Healing Surge and Unleash Life
                        case SPELL_RIPTIDE:
                        case SPELL_HEALING_SURGE:
                        case SPELL_UNLEASH_LIFE:
                            healAmount *= 0.6f;
                            break;

                            // 33% on Chain Heal
                        case SPELL_CHAIN_HEAL:
                            healAmount *= 0.33f;
                            break;

                            /*
                            * If we have something else here, we should assert, because it would not be
                            * logic (if spell_proc_event entry in DB is correct). But, since I cannot be
                            * sure that proc system is 100% correct, just return for now.
                            */
                        default:
                            return;
                        } // switch damageInfo->GetSpellInfo()->Id

                        target->CastCustomSpell(target, SPELL_RESURGENCE_PROC, &healAmount, NULL, NULL, true);
                    }   // if procInfo.GetDamageInfo()
                }   // if target->CalculateSpellDamage()
            }   // if procInfo.GetActor()
        }   // void HandleDummyProc

        void Register() override
        {
            DoCheckProc += AuraCheckProcFn(spell_sha_resurgence_AuraScript::CheckDummyProc);
            OnProc += AuraProcFn(spell_sha_resurgence_AuraScript::HandleDummyProc);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_sha_resurgence_AuraScript();
    }
};


// Spells used by the Earthgrab Totem of the Shaman
enum EarthgrabTotem
{
    // Applied on the totem, ticks every two seconds and roots all targets within 10 yards (64695)
    SPELL_EARTHGRAB = 116943,
    SPELL_EARTHGRAB_PERIODIC = 64695,

    // When Earthgrab already hit a target, this target cannot be rooted a second time, and is instead
    // slowed with this one. (Same as the one used by Earthbind Totem)
    SPELL_EARTHBIND = 3600,
};

typedef std::list<WorldObject*> WorldObjectList;
typedef WorldObjectList::const_iterator WorldObjectListCIter;

enum ShamanTotems
{
    /* Entries */
    NPC_TOTEM_MAGMA = 5929,
    NPC_TOTEM_HEALING_STREAM = 3527,
    NPC_TOTEM_HEALING_TIDE = 59764,
    NPC_CLOUDBURST_TOTEM = 78001,

    /* Spells */
    SPELL_MAGMA_TOTEM = 8188,     // Ticks every two seconds, inflicting damages to all the creatures in a 8 yards radius
    SPELL_HEALING_STREAM = 5672,     // Ticks every two seconds, targeting the group member with lowest hp in a 40 yards radius
    SPELL_HEALING_TIDE = 114941,   // Ticks every two seconds, targeting 5 / 12 group / raid members with lowest hp in a 40 yards radius
};

//188196 - Lightning bolt (Elemental)
class spell_sha_lightning_bolt_elem : public SpellScriptLoader
{
public:
    spell_sha_lightning_bolt_elem() : SpellScriptLoader("spell_sha_lightning_bolt_elem") {}

    class spell_sha_lightning_bolt_elem_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_sha_lightning_bolt_elem_SpellScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            return ValidateSpellInfo({ SPELL_SHAMAN_LIGHTNING_BOLT_ELEM_POWER, SPELL_SHAMAN_MASTER_OF_THE_ELEMENTS, SPELL_SHAMAN_EXPOSED_ELEMENTS, SPELL_SHAMAN_FULMINATION_ENERGIZE });
        }

        void HandleHitTarget(SpellEffIndex /*eff*/)
        {
            Unit* caster = GetCaster();
            Unit* target = GetHitUnit();
            if (!caster || !target)
                return;

            uint32 extraBP = 0;

            if (auto conduit = caster->GetAuraEffect(338131, EFFECT_0)) ///< High voltage
                if (conduit->ConduitRankEntry)
                    if (roll_chance_f(conduit->ConduitRankEntry->AuraPointsOverride))
                        extraBP += 6;

            if (caster->HasAura(SPELL_SHAMAN_FULMINATION_ENERGIZE))
                caster->CastCustomSpell(SPELL_SHAMAN_LIGHTNING_BOLT_ELEM_POWER, SPELLVALUE_BASE_POINT0, sSpellMgr->GetSpellInfo(SPELL_SHAMAN_FULMINATION_ENERGIZE)->GetEffect(EFFECT_0).BasePoints + extraBP, caster, true);
            else
            {
                caster->CastSpell(caster, SPELL_SHAMAN_LIGHTNING_BOLT_ELEM_POWER, CastSpellExtraArgs(true).AddSpellBP0(extraBP));
            }

            if (Aura* aura = caster->GetAura(SPELL_SHAMAN_MASTER_OF_THE_ELEMENTS))
            {
                SetHitDamage(GetHitDamage() + CalculatePct(GetHitDamage(), aura->GetEffect(EFFECT_0)->GetBaseAmount()));
                caster->RemoveAurasDueToSpell(SPELL_SHAMAN_MASTER_OF_THE_ELEMENTS);
            }

            if (Aura* aura = target->GetAura(SPELL_SHAMAN_EXPOSED_ELEMENTS))
            {
                SetHitDamage(GetHitDamage() + CalculatePct(GetHitDamage(), aura->GetEffect(EFFECT_0)->GetBaseAmount()));
                target->RemoveAurasDueToSpell(SPELL_SHAMAN_EXPOSED_ELEMENTS);
            }
        }

        void HandleAfterCast()
        {
            Unit* caster = GetCaster();
            Unit* target = GetExplTargetUnit();
            if (!caster || !target)
                return;

            // Mastery : Elemental Overload
            if (Aura* aura = caster->GetAura(SPELL_SHAMAN_MASTERY_ELEMENTAL_OVERLOAD))
            {
                uint8 chance = aura->GetEffect(EFFECT_0)->GetAmount();
                if (Aura* stormkeeper = caster->GetAura(SPELL_SHAMAN_STORMKEEPER))
                {
                    stormkeeper->DropCharge();
                    chance = 100;
                }
                else if (Aura* totem = caster->GetAura(SPELL_TOTEM_STORM_EFFECT))
                    chance += CalculatePct(chance, totem->GetEffect(EFFECT_0)->GetBaseAmount());

                ObjectGuid targetGuid = target->GetGUID();
                if (roll_chance_i(chance))
                    caster->GetScheduler().Schedule(500ms, [targetGuid, chance](TaskContext context)
                        {
                            Unit* caster = context.GetUnit();
                            if (!caster)
                                return;
                            Unit* target = ObjectAccessor::GetUnit(*caster, targetGuid);
                            if (!target)
                                return;

                            caster->CastSpell(target, SPELL_SHAMAN_LIGHTNING_BOLT_OVERLOAD, true);
                            caster->CastSpell(caster, SPELL_SHAMAN_LIGHTNING_BOLT_ENERGIZE_OVERLOAD, true);
                            if (caster->HasAura(SPELL_SHAMAN_UNLIMTED_POWER))
                            {
                                uint32 duration = sSpellMgr->GetSpellInfo(SPELL_SHAMAN_UNLIMITED_POWER_HASTE)->GetDuration();
                                if (Aura* unlimited_aura = caster->GetAura(SPELL_SHAMAN_UNLIMITED_POWER_HASTE))
                                    duration = unlimited_aura->GetDuration();
                                caster->CastSpell(caster, SPELL_SHAMAN_UNLIMITED_POWER_HASTE, true);
                                if (Aura* unlimited_aura = caster->GetAura(SPELL_SHAMAN_UNLIMITED_POWER_HASTE))
                                    unlimited_aura->SetDuration(duration);
                            }
                            if (Aura* aura1 = caster->GetAura(SPELL_SHAMAN_HIGH_VOLTAGE))
                            {
                                uint8 additional_chance = CalculatePct(chance, aura1->GetEffect(EFFECT_0)->GetAmount());
                                if (roll_chance_i(additional_chance))
                                    caster->GetScheduler().Schedule(500ms, [caster, target](TaskContext context)
                                        {
                                            if (!caster->IsInWorld() || caster->isDead() || !target->IsInWorld() || target->isDead())
                                                return;

                                            caster->CastSpell(target, SPELL_SHAMAN_LIGHTNING_BOLT_OVERLOAD, true);
                                            caster->CastSpell(caster, SPELL_SHAMAN_LIGHTNING_BOLT_ENERGIZE_OVERLOAD, true);
                                            if (caster->HasAura(SPELL_SHAMAN_UNLIMTED_POWER))
                                            {
                                                uint32 duration = sSpellMgr->GetSpellInfo(SPELL_SHAMAN_UNLIMITED_POWER_HASTE)->GetDuration();
                                                if (Aura* unlimited_aura = caster->GetAura(SPELL_SHAMAN_UNLIMITED_POWER_HASTE))
                                                    duration = unlimited_aura->GetDuration();
                                                caster->CastSpell(caster, SPELL_SHAMAN_UNLIMITED_POWER_HASTE, true);
                                                if (Aura* unlimited_aura = caster->GetAura(SPELL_SHAMAN_UNLIMITED_POWER_HASTE))
                                                    unlimited_aura->SetDuration(duration);
                                            }
                                        });
                            }
                        });
            }
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_sha_lightning_bolt_elem_SpellScript::HandleHitTarget, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
            AfterCast += SpellCastFn(spell_sha_lightning_bolt_elem_SpellScript::HandleAfterCast);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_sha_lightning_bolt_elem_SpellScript();
    }
};

//187880 - Maelstrom Weapon
class spell_sha_maelstrom_weapon : public AuraScript
{
    PrepareAuraScript(spell_sha_maelstrom_weapon);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_SHAMAN_MAELSTROM_WEAPON_POWER });
    }

    void HandleEffectProc(AuraEffect* /*aurEff*/, ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();
        Unit* target = eventInfo.GetActionTarget();
        if (!caster || !target)
            return;

        if ((eventInfo.GetDamageInfo()->GetAttackType() == BASE_ATTACK || eventInfo.GetDamageInfo()->GetAttackType() == OFF_ATTACK) ||
            eventInfo.GetSpellInfo()->Id == SPELL_SHAMAN_WINDFURY_ATTACK)
            caster->CastSpell(caster, SPELL_SHAMAN_MAELSTROM_WEAPON_POWER, true);

        if ((eventInfo.GetDamageInfo()->GetAttackType() == BASE_ATTACK || eventInfo.GetDamageInfo()->GetAttackType() == OFF_ATTACK) &&
            caster->HasAura(SPELL_SHAMAN_HAILSTORM) && caster->HasAura(SPELL_SHAMAN_FROSTBRAND))
            caster->CastSpell(target, SPELL_SHAMAN_HAILSTORM_DAMAGE, true);
    }

    void Register() override
    {
        OnEffectProc += AuraEffectProcFn(spell_sha_maelstrom_weapon::HandleEffectProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

//197211 - Fury of Air
class spell_sha_fury_of_air : public SpellScriptLoader
{
public:
    spell_sha_fury_of_air() : SpellScriptLoader("spell_sha_fury_of_air") {}

    class spell_sha_fury_of_air_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_sha_fury_of_air_AuraScript);

        void HandlePeriodic(AuraEffect const* /*aurEff*/)
        {
            Unit* caster = GetCaster();
            if (!caster)
                return;

            if (caster->GetPower(POWER_MAELSTROM) >= 3)
                caster->SetPower(POWER_MAELSTROM, caster->GetPower(POWER_MAELSTROM) - 3);
            else
                Remove();
        }

        void Register() override
        {
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_sha_fury_of_air_AuraScript::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_sha_fury_of_air_AuraScript();
    }
};

// 192223 - Liquid Magma Totem Target Selector
class spell_sha_liquid_magma_effect : public SpellScriptLoader
{
public:
    spell_sha_liquid_magma_effect() : SpellScriptLoader("spell_sha_liquid_magma_effect") { }

    class spell_sha_liquid_magma_effect_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_sha_liquid_magma_effect_SpellScript);

        void HandleHit()
        {
            if (Unit* caster = GetCaster())
            {
                UnitList list;
                caster->GetAttackableUnitListInRange(list, 8.f);
                if (list.size() > 0)
                {
                    list.remove_if([caster](WorldObject* obj)
                        {
                            if (!obj->ToUnit())
                                return true;

                            if (!caster->IsValidAttackTarget(obj->ToUnit()))
                                return true;

                            return false;
                        });
                    std::vector<WorldObject*> targets{ std::make_move_iterator(std::begin(list)), std::make_move_iterator(std::end(list)) };
                    Trinity::Containers::RandomShuffle(targets);
                    caster->CastSpell(targets.front()->ToUnit(), SPELL_SHAMAN_LIQUID_MAGMA_DAMAGE, true);
                }
            }
        }

        void Register() override
        {
            OnHit += SpellHitFn(spell_sha_liquid_magma_effect_SpellScript::HandleHit);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_sha_liquid_magma_effect_SpellScript();
    }
};

//202192 - Resonance totem
class spell_sha_resonance_effect : public SpellScriptLoader
{
public:
    spell_sha_resonance_effect() : SpellScriptLoader("spell_sha_resonance_effect") {}

    class spell_sha_resonance_effect_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_sha_resonance_effect_AuraScript);

        void HandlePeriodic(AuraEffect const* /*aurEff*/)
        {
            Unit* caster = GetCaster();
            if (!caster)
                return;

            if (caster->GetOwner())
                caster->GetOwner()->ModifyPower(POWER_MAELSTROM, +1);
        }

        void Register() override
        {
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_sha_resonance_effect_AuraScript::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_ENERGIZE);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_sha_resonance_effect_AuraScript();
    }
};

//157504 - Cloudburst Totem
//Last Update 8.0.1 Build 28153
class spell_sha_cloudburst_effect : public AuraScript
{
    PrepareAuraScript(spell_sha_cloudburst_effect);

    void OnProc(AuraEffect* aurEff, ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();

        HealInfo* healInfo = eventInfo.GetHealInfo();

        if (!healInfo)
            return;

        if (sSpellMgr->GetSpellInfo(SPELL_TOTEM_CLOUDBURST))
        {
            SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(SPELL_TOTEM_CLOUDBURST);
            int32 bonus = CalculatePct(healInfo->GetHeal(), spellInfo->GetEffect(EFFECT_1).BasePoints);
            GetEffect(aurEff->GetEffIndex())->ChangeAmount(aurEff->GetAmount() + bonus);
        }
    }

    void OnRemove(AuraEffect const* aurEff, AuraEffectHandleModes /* mode */)
    {
        if (Unit* owner = GetOwner()->ToUnit())
        {
            if (int32 amount = aurEff->GetAmount())
            {
                owner->CastCustomSpell(owner, SPELL_TOTEM_CLOUDBURST, &amount, nullptr, nullptr, true);
                GetEffect(aurEff->GetEffIndex())->ChangeAmount(0);
            }
        }
    }

    void Register() override
    {
        OnEffectProc += AuraEffectProcFn(spell_sha_cloudburst_effect::OnProc, EFFECT_0, SPELL_AURA_DUMMY);
        OnEffectRemove += AuraEffectRemoveFn(spell_sha_cloudburst_effect::OnRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

//Cloudburst - 157503
//Last Update 8.0.1 Build 28153
class spell_sha_cloudburst : public SpellScript
{
    PrepareSpellScript(spell_sha_cloudburst);

    bool Load() override
    {
        targetCount = 0;
        return true;
    }

    void HandleHeal(SpellEffIndex /*p_EffIndex*/)
    {
        if (targetCount)
            SetHitHeal(GetHitHeal() / targetCount);
    }

    void CountTargets(std::list<WorldObject*>& targets)
    {
        targetCount = targets.size();
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_sha_cloudburst::CountTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ALLY);
        OnEffectHitTarget += SpellEffectFn(spell_sha_cloudburst::HandleHeal, EFFECT_0, SPELL_EFFECT_HEAL);
    }

    uint8 targetCount;
};

// 201764 - Recall Cloudburst Totem
//Last Update 8.0.1 Build 28153
class spell_sha_cloudburst_totem_recall : public SpellScript
{
    PrepareSpellScript(spell_sha_cloudburst_totem_recall);

    void HandleScriptEffect(SpellEffIndex /*effIndex*/)
    {
        if (Unit* caster = GetCaster())
        {
            if (caster->GetAura(SPELL_TOTEM_CLOUDBURST_EFFECT))
                caster->RemoveAurasDueToSpell(SPELL_TOTEM_CLOUDBURST_EFFECT);

            if (Unit* totem = caster->GetControlledCreature(NPC_CLOUDBURST_TOTEM))
                totem->ToTotem()->UnSummon();
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_sha_cloudburst_totem_recall::HandleScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
    }
};

// 108281 - Ancestral Guidance
class spell_sha_ancestral_guidance : public AuraScript
{
    PrepareAuraScript(spell_sha_ancestral_guidance);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_SHAMAN_ANCESTRAL_GUIDANCE_HEAL });
    }

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetHealInfo() && eventInfo.GetHealInfo()->GetSpellInfo()->Id == SPELL_SHAMAN_ANCESTRAL_GUIDANCE_HEAL;
    }

    void HandleEffectProc(AuraEffect* aurEff, ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();
        int32 bp0 = CalculatePct(int32(eventInfo.GetDamageInfo()->GetDamage()), aurEff->GetAmount());
        if (bp0)
            eventInfo.GetActor()->CastCustomSpell(SPELL_SHAMAN_ANCESTRAL_GUIDANCE_HEAL, SPELLVALUE_BASE_POINT0, bp0, eventInfo.GetActor(), true, NULL, aurEff);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_sha_ancestral_guidance::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_sha_ancestral_guidance::HandleEffectProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

// 114911 - Ancestral Guidance Heal
class spell_sha_ancestral_guidance_heal : public SpellScriptLoader
{
public:
    spell_sha_ancestral_guidance_heal() : SpellScriptLoader("spell_sha_ancestral_guidance_heal") { }

    class spell_sha_ancestral_guidance_heal_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_sha_ancestral_guidance_heal_SpellScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_SHAMAN_ANCESTRAL_GUIDANCE))
                return false;
            return true;
        }

        void ResizeTargets(std::list<WorldObject*>& targets)
        {
            Trinity::Containers::RandomResize(targets, 3);
        }

        void Register() override
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_sha_ancestral_guidance_heal_SpellScript::ResizeTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ALLY);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_sha_ancestral_guidance_heal_SpellScript();
    }
};

// Ascendance (Water) - 114052
//Last Update 8.0.1 Build 28153
class spell_sha_ascendance_water : public SpellScriptLoader
{
public:
    spell_sha_ascendance_water() : SpellScriptLoader("spell_sha_ascendance_water") { }

    class spell_sha_ascendance_water_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_sha_ascendance_water_AuraScript);

        void HandleProc(ProcEventInfo& eventInfo)
        {
            PreventDefaultAction();

            if (!GetCaster())
                return;

            Player* player = GetCaster()->ToPlayer();
            if (!player)
                return;

            if (eventInfo.GetActor()->GetGUID() != player->GetGUID())
                return;

            if (!eventInfo.GetHealInfo())
                return;

            if (!eventInfo.GetHealInfo()->GetHeal())
                return;

            if (eventInfo.GetHealInfo()->GetSpellInfo()->Id == SPELL_SHAMAN_RESTORATIVE_MISTS)
                return;

            if (Unit* target = eventInfo.GetActionTarget())
            {
                int32 bp = eventInfo.GetHealInfo()->GetHeal();

                if (bp > 0)
                    player->CastCustomSpell(target, SPELL_SHAMAN_RESTORATIVE_MISTS, &bp, NULL, NULL, true);
            }
        }

        void Register() override
        {
            OnProc += AuraProcFn(spell_sha_ascendance_water_AuraScript::HandleProc);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_sha_ascendance_water_AuraScript();
    }
};

// Ascendance (Water)(heal) - 114083
//Last Update 8.0.1 Build 28153
class spell_sha_ascendance_water_heal : public SpellScriptLoader
{
public:
    spell_sha_ascendance_water_heal() : SpellScriptLoader("spell_sha_ascendance_water_heal") { }

    class spell_sha_ascendance_water_heal_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_sha_ascendance_water_heal_SpellScript);

        uint32 targetSize = 0;

        void OnEffectHeal(SpellEffIndex /*effIndex*/)
        {
            SetHitHeal(GetHitHeal() / targetSize);
        }

        void FilterTargets(std::list<WorldObject*>& targets)
        {
            targetSize = targets.size();
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_sha_ascendance_water_heal_SpellScript::OnEffectHeal, EFFECT_0, SPELL_EFFECT_HEAL);
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_sha_ascendance_water_heal_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ALLY);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_sha_ascendance_water_heal_SpellScript();
    }
};

// 170374 - Earthen Rage (Passive)
class spell_sha_earthen_rage_passive : public SpellScriptLoader
{
public:
    spell_sha_earthen_rage_passive() : SpellScriptLoader("spell_sha_earthen_rage_passive") { }

    class spell_sha_earthen_rage_passive_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_sha_earthen_rage_passive_AuraScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            return ValidateSpellInfo({ SPELL_SHAMAN_EARTHEN_RAGE_PASSIVE, SPELL_SHAMAN_EARTHEN_RAGE_PERIODIC, SPELL_SHAMAN_EARTHEN_RAGE_DAMAGE });
        }

        void HandleEffectProc(AuraEffect* /*aurEff*/, ProcEventInfo& eventInfo)
        {
            PreventDefaultAction();

            if (!eventInfo.GetProcSpell())
                return;

            if (eventInfo.GetProcTarget() && eventInfo.GetActor())
            {
                switch (eventInfo.GetProcSpell()->GetSpellInfo()->Id)
                {
                    case SPELL_SHAMAN_EARTHEN_RAGE_PASSIVE:
                    case SPELL_SHAMAN_EARTHEN_RAGE_PERIODIC:
                    case SPELL_SHAMAN_EARTHEN_RAGE_DAMAGE:
                        return;
                    default:
                        break;
                }

                if (roll_chance_i(50))
                {
                    GetAura()->Variables.Set("procTargetGUID", eventInfo.GetProcTarget()->GetGUID());
                    eventInfo.GetActor()->CastSpell(eventInfo.GetActor(), SPELL_SHAMAN_EARTHEN_RAGE_PERIODIC, true);
                }
            }

        }

        void Register() override
        {
            OnEffectProc += AuraEffectProcFn(spell_sha_earthen_rage_passive_AuraScript::HandleEffectProc, EFFECT_0, SPELL_AURA_DUMMY);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new  spell_sha_earthen_rage_passive_AuraScript();
    }
};

// 170377 - Earthen Rage (Proc Aura)
class spell_sha_earthen_rage_proc_aura : public SpellScriptLoader
{
public:
    spell_sha_earthen_rage_proc_aura() : SpellScriptLoader("spell_sha_earthen_rage_proc_aura") { }

    class spell_sha_earthen_rage_proc_aura_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_sha_earthen_rage_proc_aura_AuraScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            return ValidateSpellInfo({ SPELL_SHAMAN_EARTHEN_RAGE_PASSIVE, SPELL_SHAMAN_EARTHEN_RAGE_PERIODIC, SPELL_SHAMAN_EARTHEN_RAGE_DAMAGE });
        }

        void HandleEffectPeriodic(AuraEffect const* /*aurEff*/)
        {
            PreventDefaultAction();
            if (auto caster = GetCaster())
            {
                if (Aura* aura = caster->GetAura(SPELL_SHAMAN_EARTHEN_RAGE_PASSIVE))
                {
                    ObjectGuid const procTargetGUID = aura->Variables.GetValue<ObjectGuid>("procTargetGUID");
                    if (Unit* procTarget = ObjectAccessor::GetUnit(*caster, procTargetGUID))
                    {
                        if (auto target = GetTarget())
                            target->CastSpell(procTarget, SPELL_SHAMAN_EARTHEN_RAGE_DAMAGE, true);
                    }
                }
            }
        }

        void CalcPeriodic(AuraEffect const* /*aurEff*/, bool& /*isPeriodic*/, int32& amplitude)
        {
            // On retail there have been 1-6 procs randomly distributed over the duration
            amplitude = urand(1000, 4000);
        }

        void Register() override
        {
            DoEffectCalcPeriodic += AuraEffectCalcPeriodicFn(spell_sha_earthen_rage_proc_aura_AuraScript::CalcPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_sha_earthen_rage_proc_aura_AuraScript::HandleEffectPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new  spell_sha_earthen_rage_proc_aura_AuraScript();
    }
};

//210643 Totem Mastery
class spell_sha_totem_mastery : public SpellScriptLoader
{
public:
    spell_sha_totem_mastery() : SpellScriptLoader("spell_sha_totem_mastery") { }

    class spell_sha_totem_mastery_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_sha_totem_mastery_SpellScript);

        void HandleSummon()
        {
            Unit* caster = GetCaster();
            if (!caster)
                return;

            Player* player = caster->ToPlayer();
            if (!player)
                return;
            uint32 t1, t2, t3, t4;

            if (player->GetSpecializationId() == TALENT_SPEC_SHAMAN_ELEMENTAL)
            {
                t1 = 102392;
                t2 = 106317;
                t3 = 106319;
                t4 = 106321;
            }
            else
            {
                t1 = 133525;
                t2 = 133514;
                t3 = 133515;
                t4 = 133516;
            }

            //Unsummon any Resonance Totem that the player already has.
            std::list<Creature*> totemResoList;
            player->GetCreatureListWithEntryInGrid(totemResoList, t1, 100.0f);

            for (std::list<Creature*>::iterator i = totemResoList.begin(); i != totemResoList.end(); ++i)
            {
                Unit* owner = (*i)->GetOwner();

                if (owner && owner == player && (*i)->IsSummon())
                    continue;

                i = totemResoList.erase(i);
            }

            if ((int32)totemResoList.size() >= 1)
                totemResoList.back()->ToTempSummon()->UnSummon();

            //Unsummon any Storm Totem that the player already has.
            std::list<Creature*> totemStormList;
            player->GetCreatureListWithEntryInGrid(totemStormList, t2, 100.0f);

            for (std::list<Creature*>::iterator i = totemStormList.begin(); i != totemStormList.end(); ++i)
            {
                Unit* owner = (*i)->GetOwner();

                if (owner && owner == player && (*i)->IsSummon())
                    continue;

                i = totemStormList.erase(i);
            }

            if ((int32)totemStormList.size() >= 1)
                totemStormList.back()->ToTempSummon()->UnSummon();

            //Unsummon any Ember Totem that the player already has.
            std::list<Creature*> totemEmberList;
            player->GetCreatureListWithEntryInGrid(totemEmberList, t3, 100.0f);

            for (std::list<Creature*>::iterator i = totemEmberList.begin(); i != totemEmberList.end(); ++i)
            {
                Unit* owner = (*i)->GetOwner();

                if (owner && owner == player && (*i)->IsSummon())
                    continue;

                i = totemEmberList.erase(i);
            }

            if ((int32)totemEmberList.size() >= 1)
                totemEmberList.back()->ToTempSummon()->UnSummon();

            //Unsummon any Tailwind Totem that the player already has.
            std::list<Creature*> totemTailwindList;
            player->GetCreatureListWithEntryInGrid(totemTailwindList, t4, 100.0f);

            for (std::list<Creature*>::iterator i = totemTailwindList.begin(); i != totemTailwindList.end(); ++i)
            {
                Unit* owner = (*i)->GetOwner();

                if (owner && owner == player && (*i)->IsSummon())
                    continue;

                i = totemTailwindList.erase(i);
            }

            if ((int32)totemTailwindList.size() >= 1)
                totemTailwindList.back()->ToTempSummon()->UnSummon();
        }

        void Register() override
        {
            OnCast += SpellCastFn(spell_sha_totem_mastery_SpellScript::HandleSummon);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_sha_totem_mastery_SpellScript();
    }
};

//NPC ID : 97285
//NPC NAME : Wind Rush Totem
struct npc_wind_rush_totem : public ScriptedAI
{
    npc_wind_rush_totem(Creature* creature) : ScriptedAI(creature) {}

    uint32 m_Timer;

    void Reset() override
    {
        m_Timer = 500;
    }

    void UpdateAI(const uint32 diff) override
    {
        if (m_Timer <= diff)
        {
            std::list<Unit*> unitList;
            me->GetFriendlyUnitListInRange(unitList, 10.0f, true);

            for (Unit* target : unitList)
                me->CastSpell(target, SPELL_TOTEM_WIND_RUSH_EFFECT, true);

            m_Timer = 500;
        }
        else
        {
            m_Timer -= diff;
        }
    }
};

//NPC ID : 100099
//NPC NAME : Voodoo Totem
struct npc_voodoo_totem : public ScriptedAI
{
    npc_voodoo_totem(Creature* creature) : ScriptedAI(creature) {}

    void Reset() override
    {
        me->CastSpell(nullptr, SPELL_TOTEM_VOODOO_AT, true);
    }
};

//NPC ID : 61245
//NPC NAME : Lightning Surge Totem
struct npc_lightning_surge_totem : public ScriptedAI
{
    npc_lightning_surge_totem(Creature* creature) : ScriptedAI(creature) {}

    void Reset() override
    {
        me->Variables.Set("stunnedCounter", 0);
        me->GetScheduler().CancelAll();
        me->GetScheduler().Schedule(2s, [this](TaskContext /*context*/)
            {
                me->CastSpell(me, SPELL_TOTEM_LIGHTNING_SURGE_EFFECT, true);
            });
    }
};

//NPC ID : 102392
struct npc_resonance_totem : public ScriptedAI
{
    npc_resonance_totem(Creature* creature) : ScriptedAI(creature) {}

    uint32 m_Timer;

    void Reset() override
    {
        m_Timer = 1000;
    }

    void UpdateAI(const uint32 diff) override
    {
        if (m_Timer <= diff)
        {
            me->CastSpell(me, SPELL_TOTEM_RESONANCE_EFFECT, true);
            m_Timer = 1000;
        }
        else
        {
            m_Timer -= diff;
        }
    }
};

//NPC ID : 133525
struct npc_resonance_totem_encha : public ScriptedAI
{
    npc_resonance_totem_encha(Creature* creature) : ScriptedAI(creature) {}

    void Reset() override
    {
        m_castTime = 0;
    }

    void UpdateAI(uint32 uiDiff) override
    {
        if (m_castTime <= uiDiff)
        {
            me->CastSpell(me, SPELL_TOTEM_RESONANCE_EFFECT_ENCHA, true);
            m_castTime = TimeConstants::IN_MILLISECONDS;
        }
        else
        {
            m_castTime -= uiDiff;
        }
    }
private:
    uint32 m_castTime;
};

//NPC ID : 97369
struct npc_liquid_magma_totem : public ScriptedAI
{
    npc_liquid_magma_totem(Creature* creature) : ScriptedAI(creature) {}

    void Reset() override
    {
        me->CastSpell(me, SPELL_TOTEM_LIQUID_MAGMA_EFFECT, true);
    }
};

//NPC ID : 60561
struct npc_earth_grab_totem : public ScriptedAI
{
    npc_earth_grab_totem(Creature* creature) : ScriptedAI(creature)
    {
        me->CastSpell(me, SPELL_EARTHGRAB, true);
    }
};

//NPC ID : 59764
struct npc_healing_tide_totem : public ScriptedAI
{
    npc_healing_tide_totem(Creature* creature) : ScriptedAI(creature) {}

    uint32 m_Timer;

    void Reset() override
    {
        m_Timer = 1900;
    }

    void UpdateAI(const uint32 diff) override
    {
        if (m_Timer <= diff)
        {
            me->CastSpell(me, SPELL_TOTEM_HEALING_TIDE_EFFECT, true);
            m_Timer = 1900;
        }
        else
        {
            m_Timer -= diff;
        }
    }
};

//NPC ID : 106321
struct npc_tailwind_totem : public ScriptedAI
{
    npc_tailwind_totem(Creature* creature) : ScriptedAI(creature) {}

    uint32 m_Timer;

    void Reset() override
    {
        m_Timer = 1000;
    }

    void UpdateAI(const uint32 diff) override
    {
        if (m_Timer <= diff)
        {
            me->CastSpell(me, SPELL_TOTEM_TAIL_WIND_EFFECT, true);
            m_Timer = 1000;
        }
        else
        {
            m_Timer -= diff;
        }
    }
};

//NPC ID : 133516
struct npc_tailwind_totem_encha : public ScriptedAI
{
    npc_tailwind_totem_encha(Creature* creature) : ScriptedAI(creature) {}

    uint32 m_Timer;

    void Reset() override
    {
        uint32 m_Timer = 1000;
    }

    void UpdateAI(const uint32 diff) override
    {
        if (m_Timer <= diff)
        {
            me->CastSpell(me, SPELL_TOTEM_TAILWIND_EFFECT_ENCHA, true);
            m_Timer = 1000;
        }
        else
        {
            m_Timer -= diff;
        }
    }
};

//NPC ID: 106317
struct npc_storm_totem : public ScriptedAI
{
    npc_storm_totem(Creature* creature) : ScriptedAI(creature) {}

    uint32 m_Timer;

    void Reset() override
    {
        uint32 m_Timer = 1000;
    }

    void UpdateAI(const uint32 diff) override
    {
        if (m_Timer <= diff)
        {
            me->CastSpell(me, SPELL_TOTEM_STORM_EFFECT, true);
            m_Timer = 1000;
        }
        else
        {
            m_Timer -= diff;
        }
    }
};

//NPC ID: 133514
struct npc_storm_totem_encha : public ScriptedAI
{
    npc_storm_totem_encha(Creature* creature) : ScriptedAI(creature) {}

    uint32 m_Timer;

    void Reset() override
    {
        m_Timer = 1000;
    }

    void UpdateAI(const uint32 diff) override
    {
        if (m_Timer <= diff)
        {
            me->CastSpell(me, SPELL_TOTEM_STORM_EFFECT_ENCHA, true);
            m_Timer = 1000;
        }
        else
        {
            m_Timer -= diff;
        }
    }
};

//NPC ID : 106319
struct npc_ember_totem : public ScriptedAI
{
    npc_ember_totem(Creature* creature) : ScriptedAI(creature) {}

    uint32 m_Timer;

    void Reset() override
    {
        m_Timer = 1000;
    }

    void UpdateAI(const uint32 diff) override
    {
        if (m_Timer <= diff)
        {
            me->CastSpell(me, SPELL_TOTEM_EMBER_EFFECT, true);
            m_Timer = 1000;
        }
        else
        {
            m_Timer -= diff;
        }
    }
};

//NPC ID : 133515
struct npc_ember_totem_encha : public ScriptedAI
{
    npc_ember_totem_encha(Creature* creature) : ScriptedAI(creature) {}

    uint32 m_Timer;

    void Reset() override
    {
        m_Timer = 1000;
    }

    void UpdateAI(const uint32 diff) override
    {
        if (m_Timer <= diff)
        {
            me->CastSpell(me, SPELL_TOTEM_EMBER_EFFECT_ENCHA, true);
            m_Timer = 1000;
        }
        else
        {
            m_Timer -= diff;
        }
    }
};

//NPC ID : 78001
struct npc_cloudburst_totem : public ScriptedAI
{
    npc_cloudburst_totem(Creature* creature) : ScriptedAI(creature) {}

    void Reset() override
    {
        if (me->GetOwner())
            me->CastSpell(me->GetOwner(), SPELL_TOTEM_CLOUDBURST_EFFECT, true);
    }
};

//NPC ID : 5913
struct npc_tremor_totem : public ScriptedAI
{
    npc_tremor_totem(Creature* creature) : ScriptedAI(creature) {}

    void Reset() override
    {
        me->CastSpell(me, SPELL_TOTEM_TREMOR_EFFECT, true);
    };
};

//100943
struct npc_earthen_shield_totem : public ScriptedAI
{
    npc_earthen_shield_totem(Creature* creature) : ScriptedAI(creature) {}

    void Reset() override
    {
        me->CastSpell(me, SPELL_SHAMAN_AT_EARTHEN_SHIELD_TOTEM, true);
    }
};

// 2630 - Earthbind Totem
struct npc_earthbind_totem : public ScriptedAI
{
    npc_earthbind_totem(Creature* creature) : ScriptedAI(creature)
    {
        me->CastSpell(me, SPELL_TOTEM_EARTHBIND_EFFECT, true);
    }
};

//105451 - CounterStrike Totem Last Update 8.0.1 Build 28153
struct npc_counterstrike_totem : public ScriptedAI
{
    npc_counterstrike_totem(Creature* creature) : ScriptedAI(creature) {}

    void Reset() override
    {
        me->CastSpell(me, SPELL_TOTEM_COUNTERSTRIKE_EFFECT, true);
    }
};

//AT ID : 6523
//Spell ID : 208990 Last Update 8.0.1 Build 28153
struct at_counterstrike_totem : AreaTriggerAI
{
    at_counterstrike_totem(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger) { }

    void OnUnitEnter(Unit* unit) override
    {
        Unit* caster = at->GetCaster();

        if (!caster || !unit)
            return;

        if (unit->IsTotem())
            return;

        if (caster->IsValidAttackTarget(unit))
            caster->CastSpell(unit, SEPLL_TOTEM_COUNTERSTRIKE_AURA, true);
    }

    void OnUnitExit(Unit* unit) override
    {
        Unit* caster = at->GetCaster();

        if (!caster || !unit)
            return;

        if (unit->IsTotem())
            return;

        if (unit->HasAura(SEPLL_TOTEM_COUNTERSTRIKE_AURA, caster->GetGUID()))
            unit->RemoveAura(SEPLL_TOTEM_COUNTERSTRIKE_AURA, caster->GetGUID());
    }
};

//AT ID : 5760
//Spell ID : 198839
struct at_earthen_shield_totem : AreaTriggerAI
{
    at_earthen_shield_totem(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger) { }

    void OnUnitEnter(Unit* unit) override
    {
        Unit* caster = at->GetCaster();

        if (!caster || !unit)
            return;

        if (unit->IsTotem())
            return;

        if (caster->IsValidAssistTarget(unit) || unit->GetGUID() == caster->GetGUID())
            caster->CastSpell(unit, SPELL_SHAMAN_EARTHEN_SHIELD_ABSORB, true);
    }

    void OnUnitExit(Unit* unit) override
    {
        Unit* caster = at->GetCaster();

        if (!caster || !unit)
            return;

        if (unit->IsTotem())
            return;

        if (unit->HasAura(SPELL_SHAMAN_EARTHEN_SHIELD_ABSORB, caster->GetGUID()))
            unit->RemoveAura(SPELL_SHAMAN_EARTHEN_SHIELD_ABSORB, caster->GetGUID());
    }
};

//201633 - Earthen Shield
class spell_sha_earthen_shield_absorb : public SpellScriptLoader
{
public:
    spell_sha_earthen_shield_absorb() : SpellScriptLoader("spell_sha_earthen_shield_absorb") { }

    class spell_sha_earthen_shield_absorb_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_sha_earthen_shield_absorb_AuraScript);

        void CalcAbsorb(AuraEffect const* /*aurEff*/, int32& amount, bool& /*canBeRecalculated*/)
        {
            Unit* caster = GetCaster();
            if (!caster || !caster->IsTotem())
                return;

            Unit* owner = caster->GetOwner();
            if (!owner)
                return;

            uint8 percentBase = sSpellMgr->GetSpellInfo(SPELL_SHAMAN_EARTHEN_WALL_TOTEM)->GetEffect(EFFECT_2).BasePoints;
            int32 value = percentBase * owner->GetTotalSpellPowerValue(SPELL_SCHOOL_MASK_NATURE, false) / 100;
            amount = -value;
        }

        void HandleAbsorb(AuraEffect* aurEff, DamageInfo& dmgInfo, uint32& absorbAmount)
        {
            Unit* caster = GetCaster();
            if (!caster || !caster->IsTotem())
                return;

            Unit* owner = caster->GetOwner();
            if (!owner)
                return;

            if (dmgInfo.GetDamage() <= 0)
                return;

            absorbAmount = (caster->GetHealth() - std::abs(aurEff->GetAmount())) >= 0 ? std::abs(aurEff->GetAmount()) : std::abs(aurEff->GetAmount()) - caster->GetHealth();

            //201657 - The damager
            caster->CastCustomSpell(SPELL_TOTEM_EARTH_WALL_DAMAGE, SPELLVALUE_BASE_POINT0, absorbAmount, caster, TRIGGERED_FULL_MASK);
        }

        void Register() override
        {
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_sha_earthen_shield_absorb_AuraScript::CalcAbsorb, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
            OnEffectAbsorb += AuraEffectAbsorbFn(spell_sha_earthen_shield_absorb_AuraScript::HandleAbsorb, EFFECT_0);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_sha_earthen_shield_absorb_AuraScript();
    }
};

//104818 - Ancestral Protection Totem
struct npc_ancestral_protection_totem : public ScriptedAI
{
    npc_ancestral_protection_totem(Creature* creature) : ScriptedAI(creature) {}

    void Reset() override
    {
        me->CastSpell(me, SPELL_TOTEM_ANCESTRAL_PROTECTION_AT, true);
    }
};


//AT ID : 6336
//Spell ID : 207495
class at_sha_ancestral_protection_totem : public AreaTriggerEntityScript
{
public:
    at_sha_ancestral_protection_totem() : AreaTriggerEntityScript("at_sha_ancestral_protection_totem") { }

    struct at_sha_ancestral_protection_totemAI : AreaTriggerAI
    {
        int32 timeInterval;

        at_sha_ancestral_protection_totemAI(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger) { }

        enum SpellsUsed
        {
            SPELL_SHAMAN_ANCESTRAL_PROTECTION_TOTEM_AURA = 207498
        };

        void OnCreate() override
        {
            Unit* caster = at->GetCaster();

            if (!caster)
                return;


            for (auto itr : at->GetInsideUnits())
            {
                Unit* target = ObjectAccessor::GetUnit(*caster, itr);
                if (caster->IsFriendlyTo(target) || target == caster->GetOwner())
                {
                    if (!target->IsTotem())
                        caster->CastSpell(target, SPELL_SHAMAN_ANCESTRAL_PROTECTION_TOTEM_AURA, true);
                }
            }
        }

        void OnUnitEnter(Unit* unit) override
        {
            Unit* caster = at->GetCaster();

            if (!caster || !unit)
                return;

            if (caster->IsFriendlyTo(unit) || unit == caster->GetOwner())
            {
                if (unit->IsTotem())
                    return;
                else
                    caster->CastSpell(unit, SPELL_SHAMAN_ANCESTRAL_PROTECTION_TOTEM_AURA, true);
            }
        }

        void OnUnitExit(Unit* unit) override
        {
            Unit* caster = at->GetCaster();

            if (!caster || !unit)
                return;

            if (unit->HasAura(SPELL_SHAMAN_ANCESTRAL_PROTECTION_TOTEM_AURA) && unit->GetAura(SPELL_SHAMAN_ANCESTRAL_PROTECTION_TOTEM_AURA)->GetCaster() == caster)
                unit->RemoveAura(SPELL_SHAMAN_ANCESTRAL_PROTECTION_TOTEM_AURA);
        }

        void OnRemove() override
        {
            Unit* caster = at->GetCaster();

            if (!caster)
                return;

            for (auto itr : at->GetInsideUnits())
            {
                Unit* target = ObjectAccessor::GetUnit(*caster, itr);
                if (!target->IsTotem())
                    if (target->HasAura(SPELL_SHAMAN_ANCESTRAL_PROTECTION_TOTEM_AURA))
                        target->RemoveAura(SPELL_SHAMAN_ANCESTRAL_PROTECTION_TOTEM_AURA);
            }
        }
    };

    AreaTriggerAI* GetAI(AreaTrigger* areatrigger) const override
    {
        return new at_sha_ancestral_protection_totemAI(areatrigger);
    }
};

//207498 ancestral protection
class spell_sha_ancestral_protection_totem_aura : public SpellScriptLoader
{
public:
    spell_sha_ancestral_protection_totem_aura() : SpellScriptLoader("spell_sha_ancestral_protection_totem_aura") { }

    class spell_sha_ancestral_protection_totem_aura_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_sha_ancestral_protection_totem_aura_AuraScript);

        void CalculateAmount(AuraEffect const* /*auraEffect*/, int32& amount, bool& /*canBeRecalculated*/)
        {
            amount = -1;
        }


        void HandleAfterRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if (GetTargetApplication()->GetRemoveMode() != AURA_REMOVE_BY_DEATH)
                return;

            Unit* totem = GetCaster();
            if (!totem)
                return;

            totem->CastSpell(GetTargetApplication()->GetTarget(), SPELL_TOTEM_TOTEMIC_REVIVAL, true);
            totem->KillSelf();
        }

        void Register() override
        {
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_sha_ancestral_protection_totem_aura_AuraScript::CalculateAmount, EFFECT_1, SPELL_AURA_SCHOOL_ABSORB);
            OnEffectRemove += AuraEffectRemoveFn(spell_sha_ancestral_protection_totem_aura_AuraScript::HandleAfterRemove, EFFECT_1, SPELL_AURA_SCHOOL_ABSORB, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_sha_ancestral_protection_totem_aura_AuraScript();
    }
};

//AT id : 3691
//Spell ID : 61882
class at_sha_earthquake_totem : public AreaTriggerEntityScript
{
public:
    at_sha_earthquake_totem() : AreaTriggerEntityScript("at_sha_earthquake_totem") { }

    struct at_sha_earthquake_totemAI : AreaTriggerAI
    {
        int32 timeInterval;

        enum UsedSpells
        {
            SPELL_SHAMAN_EARTHQUAKE_DAMAGE = 77478,
            SPELL_SHAMAN_EARTHQUAKE_STUN = 77505
        };

        at_sha_earthquake_totemAI(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger)
        {
            timeInterval = 200;
        }

        void OnUpdate(uint32 p_Time) override
        {
            Unit* caster = at->GetCaster();

            if (!caster)
                return;

            if (!caster->ToPlayer())
                return;

            // Check if we can handle actions
            timeInterval += p_Time;
            if (timeInterval < 1000)
                return;

            if (Creature* tempSumm = caster->SummonCreature(WORLD_TRIGGER, at->GetPosition(), TEMPSUMMON_TIMED_DESPAWN, 200ms))
            {
                tempSumm->SetFaction(caster->GetFaction());
                tempSumm->SetOwnerGUID(caster->GetGUID());
                PhasingHandler::InheritPhaseShift(tempSumm, caster);
                tempSumm->CastCustomSpell(SPELL_SHAMAN_EARTHQUAKE_DAMAGE, SPELLVALUE_BASE_POINT0, caster->GetTotalSpellPowerValue(SPELL_SCHOOL_MASK_NORMAL, false) * 0.3, caster, TRIGGERED_FULL_MASK);
            }

            timeInterval -= 1000;
        }
    };

    AreaTriggerAI* GetAI(AreaTrigger* areatrigger) const override
    {
        return new at_sha_earthquake_totemAI(areatrigger);
    }
};

//105427 Skyfury Totem
struct npc_skyfury_totem : public ScriptedAI
{
    npc_skyfury_totem(Creature* creature) : ScriptedAI(creature)
    {
        creature->CastSpell(creature, SPELL_TOTEM_SKYFURY_PASIVE, true);
    }
};

//5925
struct npc_grounding_totem : public ScriptedAI
{
    npc_grounding_totem(Creature* creature) : ScriptedAI(creature) {}

    void Reset() override
    {
        me->CastSpell(me, SPELL_TOTEM_GROUDING_TOTEM_EFFECT, true);
    }
};

// 285452  - Lava burst
class spell_sha_lava_burst : public SpellScriptLoader
{
public:
    spell_sha_lava_burst() : SpellScriptLoader("spell_sha_lava_burst") { }

    class spell_sha_lava_burst_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_sha_lava_burst_SpellScript);

        uint32 m_chargeCategoryId;
        int32 m_unlimitedPowerDuration;

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_SHAMAN_PATH_OF_FLAMES_TALENT))
                return false;
            if (!sSpellMgr->GetSpellInfo(SPELL_SHAMAN_PATH_OF_FLAMES_SPREAD))
                return false;
            if (!sSpellMgr->GetSpellInfo(SPELL_SHAMAN_UNLIMITED_POWER_HASTE))
                return false;

            return true;
        }

        bool Load() override
        {
            auto lavaBurstSpellIfo = sSpellMgr->GetSpellInfo(SPELL_SHAMAN_LAVA_BURST);
            ASSERT(lavaBurstSpellIfo);

            auto unlimitedPowerSpellIfo = sSpellMgr->GetSpellInfo(SPELL_SHAMAN_UNLIMITED_POWER_HASTE);
            ASSERT(unlimitedPowerSpellIfo);

            m_chargeCategoryId = lavaBurstSpellIfo->ChargeCategoryId;
            m_unlimitedPowerDuration = unlimitedPowerSpellIfo->GetDuration();

            return true;
        }

        void HandleScript(SpellEffIndex /*effIndex*/)
        {
            if (Unit* caster = GetCaster())
                if (Unit* target = GetExplTargetUnit())
                    if (caster->HasAura(SPELL_SHAMAN_PATH_OF_FLAMES_TALENT))
                        caster->CastSpell(target, SPELL_SHAMAN_PATH_OF_FLAMES_SPREAD, true);
        }

        void HandlePrepare()
        {
            if (Unit* caster = GetCaster())
                if (caster->HasAura(SPELL_SHAMAN_CONTROL_OF_LAVA_PROC))
                    caster->Variables.Set("controlProc", true);
        }

        void HandleAfterCast()
        {
            Unit* caster = GetCaster();
            Unit* target = GetExplTargetUnit();
            if (!caster || !target)
                return;

            if (caster->HasAura(SPELL_SHAMAN_LAVA_SURGE_CAST_TIME) && caster->GetCurrentSpellCastTime(SPELL_SHAMAN_LAVA_BURST) > 0)
                caster->GetSpellHistory()->RestoreCharge(m_chargeCategoryId);

            if (caster->HasAura(SPELL_SHAMAN_CONTROL_OF_LAVA_PROC) && !caster->Variables.GetValue("controlProc", false))
                caster->GetSpellHistory()->RestoreCharge(m_chargeCategoryId);

            auto targetGuid = target->GetGUID();
            auto duration = m_unlimitedPowerDuration;
            // Mastery : Elemental Overload
            if (Aura* aura = caster->GetAura(SPELL_SHAMAN_MASTERY_ELEMENTAL_OVERLOAD))
            {
                if (roll_chance_i(aura->GetEffect(EFFECT_0)->GetAmount()))
                    caster->GetScheduler().Schedule(500ms, [targetGuid, &duration](TaskContext context)
                {
                    auto _caster = GetContextUnit();
                    if (!_caster)
                        return;

                    auto _target = ObjectAccessor::GetUnit(*_caster, targetGuid);
                    if (!_target)
                        return;

                    if (!_caster->IsInWorld() || _caster->isDead() || !_target->IsInWorld() || _target->isDead())
                        return;

                    _caster->CastSpell(_target, SPELL_SHAMAN_LAVA_BURST_OVERLOAD, true);

                    if (_caster->HasAura(SPELL_SHAMAN_UNLIMTED_POWER))
                    {
                        if (Aura* unlimited_aura = _caster->GetAura(SPELL_SHAMAN_UNLIMITED_POWER_HASTE))
                            duration = unlimited_aura->GetDuration();
                        _caster->CastSpell(_caster, SPELL_SHAMAN_UNLIMITED_POWER_HASTE, true);
                        if (Aura* unlimited_aura = _caster->GetAura(SPELL_SHAMAN_UNLIMITED_POWER_HASTE))
                            unlimited_aura->SetDuration(duration);
                    }
                });
            }
        }

        void Register() override
        {
            OnPrepare += SpellOnPrepareFn(spell_sha_lava_burst_SpellScript::HandlePrepare);
            OnEffectHitTarget += SpellEffectFn(spell_sha_lava_burst_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
            AfterCast += SpellCastFn(spell_sha_lava_burst_SpellScript::HandleAfterCast);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_sha_lava_burst_SpellScript();
    }
};

// 210621 - Path of Flames Spread
class spell_sha_path_of_flames_spread : public SpellScriptLoader
{
public:
    spell_sha_path_of_flames_spread() : SpellScriptLoader("spell_sha_path_of_flames_spread") { }

    class spell_sha_path_of_flames_spread_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_sha_path_of_flames_spread_SpellScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_SHAMAN_FLAME_SHOCK))
                return false;
            return true;
        }

        void FilterTargets(std::list<WorldObject*>& targets)
        {
            targets.remove(GetExplTargetUnit());
            Trinity::Containers::RandomResize(targets, 1);
        }

        void HandleScript(SpellEffIndex /*effIndex*/)
        {
            if (Unit* mainTarget = GetExplTargetUnit())
            {
                if (Aura* flameShock = mainTarget->GetAura(SPELL_SHAMAN_FLAME_SHOCK, GetCaster()->GetGUID()))
                {
                    if (Aura* newAura = GetCaster()->AddAura(SPELL_SHAMAN_FLAME_SHOCK, GetHitUnit()))
                    {
                        newAura->SetDuration(flameShock->GetDuration());
                        newAura->SetMaxDuration(flameShock->GetDuration());
                    }
                }
            }
        }

        void Register() override
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_sha_path_of_flames_spread_SpellScript::FilterTargets, EFFECT_1, TARGET_UNIT_DEST_AREA_ENEMY);
            OnEffectHitTarget += SpellEffectFn(spell_sha_path_of_flames_spread_SpellScript::HandleScript, EFFECT_1, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_sha_path_of_flames_spread_SpellScript();
    }
};

//197995
class spell_sha_wellspring : public SpellScriptLoader
{
public:
    spell_sha_wellspring() : SpellScriptLoader("spell_sha_wellspring") { }

    class spell_sha_wellspring_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_sha_wellspring_SpellScript);

        void HandleHit(SpellEffIndex /*effIndex*/)
        {
            Unit* caster = GetCaster();
            Unit* target = GetHitUnit();

            if (!caster || !target)
                return;

            caster->CastSpell(target, SPELL_SHAMAN_WELLSPRING_MISSILE, true);
        }

        void HandleAfterCast()
        {
            if (Unit* caster = GetCaster())
                if (caster->HasAura(SPELL_SHAMAN_FLASH_FLOOD_BUFF))
                    caster->RemoveAurasDueToSpell(SPELL_SHAMAN_FLASH_FLOOD_BUFF);
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_sha_wellspring_SpellScript::HandleHit, EFFECT_0, SPELL_EFFECT_DUMMY);
            AfterCast += SpellCastFn(spell_sha_wellspring_SpellScript::HandleAfterCast);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_sha_wellspring_SpellScript();
    }
};

// Undulation
// 8004 Healing Surge
// 77472 Healing Wave
class spell_sha_undulation : public SpellScript
{
    PrepareSpellScript(spell_sha_undulation);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_SHAMAN_SWELLING_WAVES });
    }

    void HandleHitTarget()
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        if (caster->HasAura(SPELL_SHAMAN_UNDULATION_PROC))
        {
            caster->RemoveAurasDueToSpell(SPELL_SHAMAN_UNDULATION_PROC);
            return;
        }

        if (caster->HasAura(SPELL_SHAMAN_UNDULATION) && GetCaster()->Variables.IncrementOrProcCounter("spell_sha_undulation", 3))
            caster->CastSpell(caster, SPELL_SHAMAN_UNDULATION_PROC, true);

        if (caster->HasAura(SPELL_SHAMAN_SWELLING_WAVES) && caster->GetGUID() == target->GetGUID())
        {
            int32 heal = GetHitHeal();
            caster->GetScheduler().Schedule(3s, [caster, heal](TaskContext context)
                {
                    if (caster && caster->HasAura(SPELL_SHAMAN_SWELLING_WAVES))
                        caster->CastCustomSpell(SPELL_SHAMAN_SWELLING_WAVES_HEAL, SPELLVALUE_BASE_POINT0, CalculatePct(heal, sSpellMgr->GetSpellInfo(SPELL_SHAMAN_SWELLING_WAVES)->GetEffect(EFFECT_1).BasePoints), caster, true);
                });
        }
    }

    void HandleAfterCast()
    {
        if (Unit* caster = GetCaster())
            if (caster->HasAura(SPELL_SHAMAN_FLASH_FLOOD_BUFF))
                caster->RemoveAurasDueToSpell(SPELL_SHAMAN_FLASH_FLOOD_BUFF);
    }

    void Register() override
    {
        AfterHit += SpellHitFn(spell_sha_undulation::HandleHitTarget);
        AfterCast += SpellCastFn(spell_sha_undulation::HandleAfterCast);
    }
};

// 188443 Chain Lightning
class spell_sha_chain_lightning : public SpellScript
{
    PrepareSpellScript(spell_sha_chain_lightning);

    void HandleHitTarget(SpellEffIndex /*effIndex*/)
    {
        if (Unit* caster = GetCaster())
        {
            caster->ModifyPower(POWER_MAELSTROM, GetSpellInfo()->GetEffect(EFFECT_1).BasePoints);

            if (Aura* aura = caster->GetAura(SPELL_SHAMAN_MASTER_OF_THE_ELEMENTS))
            {
                SetHitDamage(GetHitDamage() + CalculatePct(GetHitDamage(), aura->GetEffect(EFFECT_0)->GetBaseAmount()));
                caster->RemoveAurasDueToSpell(SPELL_SHAMAN_MASTER_OF_THE_ELEMENTS);
            }

            if (Aura* aura = caster->GetAura(320137)) ///< Stormkeeper
            {
                SetHitDamage(GetHitDamage() + CalculatePct(GetHitDamage(), aura->GetEffect(EFFECT_1)->GetAmount()));
                aura->DropStack();
            }
        }
    }

    void HandleAfterCast()
    {
        Unit* caster = GetCaster();
        Unit* target = GetExplTargetUnit();
        if (!caster || !target)
            return;

        // Mastery : Elemental Overload
        if (Aura* aura = caster->GetAura(SPELL_SHAMAN_MASTERY_ELEMENTAL_OVERLOAD))
        {
            uint8 chance = aura->GetEffect(EFFECT_0)->GetAmount();
            if (Aura* stormkeeper = caster->GetAura(SPELL_SHAMAN_STORMKEEPER))
            {
                stormkeeper->DropCharge();
                chance = 100;
            }
            else if (Aura* totem = caster->GetAura(SPELL_TOTEM_STORM_EFFECT))
                chance += CalculatePct(chance, totem->GetEffect(EFFECT_0)->GetBaseAmount());

            if (roll_chance_i(chance))
                caster->GetScheduler().Schedule(500ms, [caster, target, aura, chance](TaskContext context)
                    {
                        if (!caster->IsInWorld() || caster->isDead() || !target->IsInWorld() || target->isDead())
                            return;

                        caster->CastSpell(target, SPELL_SHAMAN_CHAIN_LIGHTNING_OVERLOAD, true);
                        caster->CastSpell(caster, SPELL_SHAMAN_CHAIN_LIGHTNING_ENERGIZE_OVERLOAD, true);
                        if (caster->HasAura(SPELL_SHAMAN_UNLIMTED_POWER))
                        {
                            uint32 duration = sSpellMgr->GetSpellInfo(SPELL_SHAMAN_UNLIMITED_POWER_HASTE)->GetDuration();
                            if (Aura* unlimited_aura = caster->GetAura(SPELL_SHAMAN_UNLIMITED_POWER_HASTE))
                                duration = unlimited_aura->GetDuration();
                            caster->CastSpell(caster, SPELL_SHAMAN_UNLIMITED_POWER_HASTE, true);
                            if (Aura* unlimited_aura = caster->GetAura(SPELL_SHAMAN_UNLIMITED_POWER_HASTE))
                                unlimited_aura->SetDuration(duration);
                        }
                        if (Aura* aura1 = caster->GetAura(SPELL_SHAMAN_HIGH_VOLTAGE))
                        {
                            uint8 additional_chance = CalculatePct(chance, aura1->GetEffect(EFFECT_0)->GetAmount());
                            if (roll_chance_i(additional_chance))
                                caster->GetScheduler().Schedule(500ms, [caster, target](TaskContext context)
                                    {
                                        if (!caster || !target)
                                            return;
                                        if (!caster->IsInWorld() || caster->isDead() || !target->IsInWorld() || target->isDead())
                                            return;

                                        caster->CastSpell(target, SPELL_SHAMAN_CHAIN_LIGHTNING_OVERLOAD, true);
                                        caster->CastSpell(caster, SPELL_SHAMAN_CHAIN_LIGHTNING_ENERGIZE_OVERLOAD, true);
                                        if (caster->HasAura(SPELL_SHAMAN_UNLIMTED_POWER))
                                        {
                                            uint32 duration = sSpellMgr->GetSpellInfo(SPELL_SHAMAN_UNLIMITED_POWER_HASTE)->GetDuration();
                                            if (Aura* unlimited_aura = caster->GetAura(SPELL_SHAMAN_UNLIMITED_POWER_HASTE))
                                                duration = unlimited_aura->GetDuration();
                                            caster->CastSpell(caster, SPELL_SHAMAN_UNLIMITED_POWER_HASTE, true);
                                            if (Aura* unlimited_aura = caster->GetAura(SPELL_SHAMAN_UNLIMITED_POWER_HASTE))
                                                unlimited_aura->SetDuration(duration);
                                        }
                                    });
                        }
                    });
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_sha_chain_lightning::HandleHitTarget, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
        AfterCast += SpellCastFn(spell_sha_chain_lightning::HandleAfterCast);
    }
};

// 215864 Rainfall
class spell_sha_rainfall : public SpellScript
{
    PrepareSpellScript(spell_sha_rainfall);

    void HandleHitTarget(SpellEffIndex /*effIndex*/)
    {
        if (WorldLocation* pos = GetHitDest())
            GetCaster()->SummonCreature(NPC_RAINFALL, *pos);
    }

    void Register() override
    {
        OnEffectHit += SpellEffectFn(spell_sha_rainfall::HandleHitTarget, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

// 215864 Rainfall
class aura_sha_rainfall : public AuraScript
{
    PrepareAuraScript(aura_sha_rainfall);

    void HandleHealPeriodic(AuraEffect const* /*aurEff*/)
    {
        if (Unit* caster = GetCaster())
            if (Creature* rainfallTrigger = caster->GetSummonedCreatureByEntry(NPC_RAINFALL))
                caster->CastSpell(rainfallTrigger->GetPosition(), SPELL_SHAMAN_RAINFALL_HEAL, true);
    }

    void HandleAfterRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* caster = GetCaster())
            caster->UnsummonCreatureByEntry(NPC_RAINFALL);
    }

    void HandleProc(AuraEffect* /*aurEff*/, ProcEventInfo& /*eventInfo*/)
    {
        ModDuration(GetEffect(EFFECT_2)->GetBaseAmount() * IN_MILLISECONDS, GetEffect(EFFECT_3)->GetBaseAmount() * IN_MILLISECONDS);
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(aura_sha_rainfall::HandleHealPeriodic, EFFECT_1, SPELL_AURA_PERIODIC_DUMMY);
        OnEffectRemove += AuraEffectRemoveFn(aura_sha_rainfall::HandleAfterRemove, EFFECT_1, SPELL_AURA_PERIODIC_DUMMY, AURA_EFFECT_HANDLE_REAL);
        OnEffectProc += AuraEffectProcFn(aura_sha_rainfall::HandleProc, EFFECT_2, SPELL_AURA_DUMMY);
    }
};

// 73920 Healing Rain
class spell_sha_healing_rain : public SpellScript
{
    PrepareSpellScript(spell_sha_healing_rain);

    void HandleHitTarget(SpellEffIndex /*effIndex*/)
    {
        WorldLocation* pos = GetHitDest();
        Unit* caster = GetCaster();
        if (!pos || !caster)
            return;

        caster->SummonCreature(NPC_HEALING_RAIN, *pos);
    }

    void HandleAfterCast()
    {
        if (Unit* caster = GetCaster())
            if (caster->HasAura(SPELL_SHAMAN_FLASH_FLOOD_BUFF))
                caster->RemoveAurasDueToSpell(SPELL_SHAMAN_FLASH_FLOOD_BUFF);
    }

    void Register() override
    {
        OnEffectHit += SpellEffectFn(spell_sha_healing_rain::HandleHitTarget, EFFECT_0, SPELL_EFFECT_DUMMY);
        AfterCast += SpellCastFn(spell_sha_healing_rain::HandleAfterCast);
    }
};

// 73920 - Healing Rain
class aura_sha_healing_rain : public AuraScript
{
    PrepareAuraScript(aura_sha_healing_rain);

    void HandleApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* caster = GetCaster())
            if (Aura* aura = caster->GetAura(SPELL_SHAMAN_OVERFLOWING_SHORES_POWER))
                if (Creature* healingRainTrigger = caster->GetSummonedCreatureByEntry(NPC_HEALING_RAIN))
                {
                    int32 heal = aura->GetEffect(EFFECT_0)->GetAmount();
                    caster->CastCustomSpell(healingRainTrigger->GetPositionX(), healingRainTrigger->GetPositionY(), healingRainTrigger->GetPositionZ(), SPELL_SHAMAN_OVERFLOWING_SHORES_HEAL, &heal, nullptr, nullptr, true);
                }
    }

    void HandleHealPeriodic(AuraEffect const* /*aurEff*/)
    {
        if (Unit* caster = GetCaster())
            if (Creature* healingRainTrigger = caster->GetSummonedCreatureByEntry(NPC_HEALING_RAIN))
                caster->CastSpell(healingRainTrigger->GetPosition(), SPELL_SHAMAN_HEALING_RAIN_TICK, true);
    }

    void HandleAfterRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* caster = GetCaster())
            caster->UnsummonCreatureByEntry(NPC_HEALING_RAIN);
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(aura_sha_healing_rain::HandleApply, EFFECT_2, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        OnEffectPeriodic += AuraEffectPeriodicFn(aura_sha_healing_rain::HandleHealPeriodic, EFFECT_1, SPELL_AURA_PERIODIC_DUMMY);
        OnEffectRemove += AuraEffectRemoveFn(aura_sha_healing_rain::HandleAfterRemove, EFFECT_1, SPELL_AURA_PERIODIC_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

// 188070 - Healing Surge
class spell_sha_healing_surge : public SpellScript
{
    PrepareSpellScript(spell_sha_healing_surge);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_SHAMAN_SWELLING_WAVES });
    }

    void HandleCalcCastTime(int32& castTime)
    {
        if (Unit* caster = GetCaster())
        {
            int32 requiredMaelstrom = GetEffectInfo(EFFECT_2).BasePoints;
            if (caster->HasAura(SPELL_SHAMAN_HEALING_SURGE_ENHACENMENT) && caster->GetPower(POWER_MAELSTROM) >= requiredMaelstrom)
            {
                castTime = 0;
                _takenPower = requiredMaelstrom;
            }
            else
                caster->RemoveAurasDueToSpell(SPELL_SHAMAN_HEALING_SURGE_WALKING);
        }
    }

    void HandleEnergize(SpellEffIndex /*effIndex*/)
    {
        SetEffectValue(-_takenPower);

        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        if (caster->HasAura(SPELL_SHAMAN_SWELLING_WAVES) && caster->GetGUID() == target->GetGUID())
        {
            int32 heal = GetHitHeal();
            caster->GetScheduler().Schedule(3s, [caster, heal](TaskContext context)
                {
                    if (caster && caster->HasAura(SPELL_SHAMAN_SWELLING_WAVES))
                        caster->CastCustomSpell(SPELL_SHAMAN_SWELLING_WAVES_HEAL, SPELLVALUE_BASE_POINT0, CalculatePct(heal, sSpellMgr->GetSpellInfo(SPELL_SHAMAN_SWELLING_WAVES)->GetEffect(EFFECT_1).BasePoints), caster, true);
                });
        }
    }

    void Register() override
    {
        OnCalcCastTime += SpellOnCalcCastTimeFn(spell_sha_healing_surge::HandleCalcCastTime);
        OnEffectHitTarget += SpellEffectFn(spell_sha_healing_surge::HandleEnergize, EFFECT_1, SPELL_EFFECT_ENERGIZE);
    }
private:
    int32 _takenPower = 0;
};

// 8042 Earth Shock
class spell_sha_earth_shock : public SpellScript
{
    PrepareSpellScript(spell_sha_earth_shock);

    void HandleTakePower(SpellPowerCost& powerCost)
    {
        takenPower = powerCost.Amount;
    }

    void HandleCalcDamage(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        int32 damage = GetHitDamage();
        if (Aura* aura = caster->GetAura(SPELL_SHAMAN_MASTER_OF_THE_ELEMENTS))
        {
            damage += CalculatePct(damage, aura->GetEffect(EFFECT_0)->GetBaseAmount());
            caster->RemoveAurasDueToSpell(SPELL_SHAMAN_MASTER_OF_THE_ELEMENTS);
        }

        // Earthfury
        if (caster->HasAura(SPELL_SHAMAN_EARTHFURY) && (caster->GetPower(POWER_MAELSTROM) + takenPower) >= 100)
            caster->CastSpell(target, SPELL_SHAMAN_EARTHFURY_STUN, true);

        SetHitDamage(damage);
    }

    void Register() override
    {
        OnTakePower += SpellOnTakePowerFn(spell_sha_earth_shock::HandleTakePower);
        OnEffectHitTarget += SpellEffectFn(spell_sha_earth_shock::HandleCalcDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
private:
    int32 takenPower = 0;
};

// 198103 - Greater Earth Elemental
class spell_sha_earth_elemental : public SpellScript
{
    PrepareSpellScript(spell_sha_earth_elemental);

    void HandleSummon(SpellEffIndex /*effIndex*/)
    {
        if (Unit* caster = GetCaster())
            if (caster->HasAura(SPELL_SHAMAN_PRIMAL_ELEMENTALIST))
                caster->CastSpell(caster, SPELL_SHAMAN_PRIMAL_EARTH_ELEMENTAL_SUMMON, true);
            else
                caster->CastSpell(caster, SPELL_SHAMAN_EARTH_ELEMENTAL_SUMMON, true);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_sha_earth_elemental::HandleSummon, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

// 198067 - Greater Fire Elemental
class spell_sha_fire_elemental : public SpellScript
{
    PrepareSpellScript(spell_sha_fire_elemental);

    void HandleSummon(SpellEffIndex /*effIndex*/)
    {
        if (Unit* caster = GetCaster())
            if (caster->HasAura(SPELL_SHAMAN_PRIMAL_ELEMENTALIST))
                caster->CastSpell(caster, SPELL_SHAMAN_PRIMAL_FIRE_ELEMENTAL_SUMMON, true);
            else
                caster->CastSpell(caster, SPELL_SHAMAN_FIRE_ELEMENTAL_SUMMON, true);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_sha_fire_elemental::HandleSummon, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

// 187837 - Lightning Bolt
class spell_sha_enhancement_lightning_bolt : public SpellScript
{
    PrepareSpellScript(spell_sha_enhancement_lightning_bolt);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_SHAMAN_OVERCHARGE });
    }

    void HandleTakePower(SpellPowerCost& powerCost)
    {
        _maxTakenPower = 0;
        _maxDamagePercent = 0;

        if (Aura* overcharge = GetCaster()->GetAura(SPELL_SHAMAN_OVERCHARGE))
        {
            _maxTakenPower = overcharge->GetEffect(EFFECT_0)->GetSpellEffectInfo().BasePoints;
            _maxDamagePercent = overcharge->GetEffect(EFFECT_1)->GetSpellEffectInfo().BasePoints;
        }

        _takenPower = powerCost.Amount = std::min(GetCaster()->GetPower(POWER_MAELSTROM), _maxTakenPower);
    }

    void HandleDamage(SpellEffIndex /*effIndex*/)
    {
        if (_maxTakenPower > 0)
        {
            int32 increasedDamagePercent = CalculatePct(_maxDamagePercent, float(_takenPower) / float(_maxTakenPower) * 100.f);
            int32 hitDamage = CalculatePct(GetHitDamage(), 100 + increasedDamagePercent);
            SetHitDamage(hitDamage);
        }
    }

    void Register() override
    {
        OnTakePower += SpellOnTakePowerFn(spell_sha_enhancement_lightning_bolt::HandleTakePower);
        OnEffectHitTarget += SpellEffectFn(spell_sha_enhancement_lightning_bolt::HandleDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }

private:
    int32 _takenPower;
    int32 _maxTakenPower;
    int32 _maxDamagePercent;
};

// 195255 - Stormlash
class aura_sha_stormlash : public AuraScript
{
    PrepareAuraScript(aura_sha_stormlash);

    void HandleProc(AuraEffect* /*aurEff*/, ProcEventInfo& /*eventInfo*/)
    {
        if (Unit* caster = GetCaster())
            caster->CastSpell(caster, SPELL_SHAMAN_STORMLASH_BUFF, true);
    }

    void Register() override
    {
        OnEffectProc += AuraEffectProcFn(aura_sha_stormlash::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

// 195222 - Stormlash Buff
class aura_sha_stormlash_buff : public AuraScript
{
    PrepareAuraScript(aura_sha_stormlash_buff);

    void HandleProc(AuraEffect* /*aurEff*/, ProcEventInfo& eventInfo)
    {
        eventInfo.GetActor()->CastSpell(eventInfo.GetActionTarget(), SPELL_SHAMAN_STORMLASH_DAMAGE, true);
    }

    void Register() override
    {
        OnEffectProc += AuraEffectProcFn(aura_sha_stormlash_buff::HandleProc, EFFECT_1, SPELL_AURA_DUMMY);
    }
};

// Spell 210797 - Crashing Storm
// AT - 11353
class at_sha_crashing_storm : public AreaTriggerAI
{
public:
    at_sha_crashing_storm(AreaTrigger* areaTrigger) : AreaTriggerAI(areaTrigger) { }

    void OnCreate() override
    {
        if (Unit* caster = at->GetCaster())
        {
            caster->GetScheduler().Schedule(0ms, SPELL_SHAMAN_CRASHING_STORM_AT, [this](TaskContext context)
                {
                    GetContextUnit()->CastSpell(at->GetPosition(), SPELL_SHAMAN_CRASHING_STORM_DAMAGE, true);

                    if (context.GetRepeatCounter() < 7)
                        context.Repeat(1s);
                });
        }
    }

    void OnRemove() override
    {
        if (Unit* caster = at->GetCaster())
            caster->GetScheduler().CancelGroup(SPELL_SHAMAN_CRASHING_STORM_AT);
    }
};

// 29264
struct npc_feral_spirit : public ScriptedAI
{
    npc_feral_spirit(Creature* p_Creature) : ScriptedAI(p_Creature) { }

    void IsSummonedBy(WorldObject* o) override
    {
        if (!o)
            return;
        auto owner = o->ToUnit();
        if (!owner)
            return;

        if (owner->GetVictim())
            targetGUID = owner->GetVictim()->GetGUID();

        if (owner->HasAura(SPELL_SHAMAN_ELEMENTAL_SPIRITS))
        {
            // Generate ramdon spirit wolf
            uint8 element = urand(1, 3);
            if (element == 1)
            {
                // Fire
                me->SetDisplayId(66843);
                owner->CastSpell(owner, SPELL_SHAMAN_MOLTEN_WEAPON, true);
            }
            else if (element == 2)
            {
                // Ice
                me->SetDisplayId(66844);
                owner->CastSpell(owner, SPELL_SHAMAN_ICE_EDGE, true);
            }
            else
            {
                // Thunder
                me->SetDisplayId(66845);
                owner->CastSpell(owner, SPELL_SHAMAN_CRACKLING_SURGE, true);
            }
        }
        else
            me->SetDisplayId(55290);
    }

    void UpdateAI(uint32 diff) override
    {
        Unit* owner = me->GetOwner();
        if (!owner)
            return;

        Unit* target = GetTarget();
        ObjectGuid newtargetGUID = owner->GetTarget();
        if ((newtargetGUID.IsEmpty() || newtargetGUID == targetGUID) && (target && me->IsValidAttackTarget(target)))
        {
            me->GetAI()->AttackStart(target);
            DoMeleeAttackIfReady();
            return;
        }

        if (Unit* newTarget = ObjectAccessor::GetUnit(*me, newtargetGUID))
        {
            if (target != newTarget && me->IsValidAttackTarget(newTarget) && owner->IsInCombat())
                target = newTarget;
            me->GetAI()->AttackStart(target);
            DoMeleeAttackIfReady();
            return;
        }

        EnterEvadeMode(EVADE_REASON_NO_HOSTILES);
    }

    //void DamageDealt(Unit* /*victim*/, uint32& /*damage*/, DamageEffectType /*damageType*/, SpellInfo const* /*spellInfo = nullptr*/) override
    //{
    //    if (Unit* owner = me->GetOwner())
    //        if (owner->HasAura(SPELL_SHAMAN_FERAL_SPIRIT_ENERGIZE_DUMMY))
    //            owner->ModifyPower(POWER_MAELSTROM, +5);
    //}

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
            me->FollowTarget(owner);
        }
    }

private:
    Unit* GetTarget() const
    {
        return ObjectAccessor::GetUnit(*me, targetGUID);
    }

    ObjectGuid targetGUID;
};

// Spell 196935 - Voodoo Totem
// AT - 11577
class at_sha_voodoo_totem : public AreaTriggerAI
{
public:
    at_sha_voodoo_totem(AreaTrigger* areaTrigger) : AreaTriggerAI(areaTrigger) { }

    void OnUnitEnter(Unit* unit) override
    {
        Unit* caster = at->GetCaster();
        if (!caster || !unit)
            return;

        if (caster->IsValidAttackTarget(unit))
        {
            caster->CastSpell(unit, SPELL_TOTEM_VOODOO_EFFECT, true);
            caster->CastSpell(unit, SPELL_TOTEM_VOODOO_COOLDOWN, true);
        }
    }

    void OnUnitExit(Unit* unit) override
    {
        unit->RemoveAurasDueToSpell(SPELL_TOTEM_VOODOO_EFFECT, at->GetCasterGuid());
    }
};

// 208964 - Skyfury Totem Passive
// AreaTriggerID - 6518
struct at_sha_skyfury : AreaTriggerAI
{
    at_sha_skyfury(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger) { }

    void OnUnitEnter(Unit* unit) override
    {
        if (Unit* caster = at->GetCaster())
            if (Unit* owner = caster->GetOwner())
                if (unit && (owner->IsValidAssistTarget(unit) || unit->GetGUID() == owner->GetGUID()) && !unit->HasAura(SPELL_TOTEM_SKYFURY_EFFECT, owner->GetGUID()))
                    owner->CastSpell(unit, SPELL_TOTEM_SKYFURY_EFFECT, true);
    }

    void OnUnitExit(Unit* unit) override
    {
        if (Unit* caster = at->GetCaster())
            if (Unit* owner = caster->GetOwner())
                if (unit && unit->HasAura(SPELL_TOTEM_SKYFURY_EFFECT, owner->GetGUID()))
                    unit->RemoveAura(SPELL_TOTEM_SKYFURY_EFFECT, owner->GetGUID());
    }
};

// Greater Storm Elemental
struct npc_greater_storm_elemental : public ScriptedAI
{
    enum StormElementalSpells
    {
        SPELL_WIND_GUST = 157331,
        SPELL_CALL_LIGHTNING = 157348,
        SPELL_THE_EYE_OF_THE_STORM = 157375,
    };

    enum VilefiendEvents
    {
        EVENT_WIND = 1,
        EVENT_LIGHTNING = 2,
    };

public:
    npc_greater_storm_elemental(Creature* creature) : ScriptedAI(creature) {}

    EventMap events;

    void IsSummonedBy(WorldObject* o) override
    {
        if (!o)
            return;
        auto owner = o->ToUnit();
        if (!owner)
            return;

        targetGUID = owner->Variables.GetValue("currentTarget", ObjectGuid::Empty);
        events.ScheduleEvent(EVENT_WIND, 1s);
        events.ScheduleEvent(EVENT_LIGHTNING, 5s);
    }

    void UpdateAI(uint32 diff) override
    {
        Unit* owner = me->GetOwner();
        if (!owner)
            return;

        if (me->IsInEvadeMode() && !owner->IsInCombat())
            return;

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        events.Update(diff);

        Unit* target = GetTarget();
        ObjectGuid newtargetGUID = owner->GetTarget();
        while (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
            case EVENT_LIGHTNING:
                CastSpellOnTarget(owner, target, SPELL_CALL_LIGHTNING);
                events.ScheduleEvent(EVENT_LIGHTNING, 10s);
                return;
            case EVENT_WIND:
            default:
                if (target && me->IsValidAttackTarget(target))
                {
                    UnitList targets;
                    target->GetFriendlyUnitListInRange(targets, 8, false);
                    if (!me->GetSpellHistory()->HasCooldown(SPELL_THE_EYE_OF_THE_STORM) && targets.size() > 2)
                        CastSpellOnTarget(owner, target, SPELL_THE_EYE_OF_THE_STORM);
                    else
                        CastSpellOnTarget(owner, target, SPELL_WIND_GUST);

                    events.ScheduleEvent(EVENT_WIND, 1s);
                    return;
                }
                else if (newtargetGUID != ObjectGuid::Empty)
                {
                    if (Unit* newTarget = ObjectAccessor::GetUnit(*me, newtargetGUID))
                        if (newTarget && me->IsValidAttackTarget(newTarget))
                        {
                            targetGUID = newtargetGUID;
                            UnitList targets;
                            newTarget->GetFriendlyUnitListInRange(targets, 8, false);
                            if (!me->GetSpellHistory()->HasCooldown(SPELL_THE_EYE_OF_THE_STORM) && targets.size() > 2)
                                CastSpellOnTarget(owner, newTarget, SPELL_THE_EYE_OF_THE_STORM);
                            else
                                CastSpellOnTarget(owner, newTarget, SPELL_WIND_GUST);
                        }

                    events.ScheduleEvent(EVENT_WIND, 1s);
                    return;
                }
            }
        }

        events.ScheduleEvent(EVENT_WIND, 1s);
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
            me->FollowTarget(owner);
        }
    }

    void IncrementBuff()
    {
        damageBuffCounter++;
    }

    uint8 GetIncrementBuff()
    {
        return damageBuffCounter;
    }

private:
    Unit* GetTarget() const
    {
        return ObjectAccessor::GetUnit(*me, targetGUID);
    }

    void CastSpellOnTarget(Unit* owner, Unit* target, uint32 spell)
    {
        if (target && me->IsValidAttackTarget(target))
        {
            targetGUID = target->GetGUID();
            me->SetTarget(targetGUID);
            if (me->GetDistance(target->GetPosition()) > 40.f)
            {
                me->GetMotionMaster()->MoveChase(target);
                return;
            }
            me->CastSpell(target, spell, false);
        }
    }

    ObjectGuid targetGUID;
    uint8 damageBuffCounter = 0;
};

// 216251 - Undulation Proc
class aura_sha_undulation_proc : public AuraScript
{
    PrepareAuraScript(aura_sha_undulation_proc);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_sha_undulation_proc::CheckProc);
    }
};

// 16166 - Master of the Elements
class aura_sha_master_of_the_elements : public AuraScript
{
    PrepareAuraScript(aura_sha_master_of_the_elements);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetSpellInfo() && (eventInfo.GetSpellInfo()->Id == SPELL_SHAMAN_LAVA_BURST || eventInfo.GetSpellInfo()->Id == SPELL_SHAMAN_LAVA_BURST_OVERLOAD))
            return true;

        return false;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_sha_master_of_the_elements::CheckProc);
    }
};

// 210714 - Icefury
class spell_sha_icefury : public SpellScript
{
    PrepareSpellScript(spell_sha_icefury);

    void HandleEffectHit(SpellEffIndex effIndex)
    {
        if (Unit* caster = GetCaster())
        {
            if (Aura* aura = caster->GetAura(SPELL_SHAMAN_MASTER_OF_THE_ELEMENTS))
            {
                SetHitDamage(GetHitDamage() + CalculatePct(GetHitDamage(), aura->GetEffect(EFFECT_0)->GetBaseAmount()));
                caster->RemoveAurasDueToSpell(SPELL_SHAMAN_MASTER_OF_THE_ELEMENTS);
            }
        }
    }

    void HandleAfterCast()
    {
        Unit* caster = GetCaster();
        Unit* target = GetExplTargetUnit();
        if (!caster || !target)
            return;

        // Mastery : Elemental Overload
        if (Aura* aura = caster->GetAura(SPELL_SHAMAN_MASTERY_ELEMENTAL_OVERLOAD))
        {
            if (roll_chance_i(aura->GetEffect(EFFECT_0)->GetAmount()))
                caster->GetScheduler().Schedule(500ms, [caster, target](TaskContext context)
            {
                if (!caster || !target)
                    return;
                if (!caster->IsInWorld() || caster->isDead() || !target->IsInWorld() || target->isDead())
                    return;

                caster->CastSpell(target, SPELL_SHAMAN_ICEFURY_OVERLOAD, true);
                if (caster->HasAura(SPELL_SHAMAN_UNLIMTED_POWER))
                {
                    uint32 duration = sSpellMgr->GetSpellInfo(SPELL_SHAMAN_UNLIMITED_POWER_HASTE)->GetDuration();
                    if (Aura* unlimited_aura = caster->GetAura(SPELL_SHAMAN_UNLIMITED_POWER_HASTE))
                        duration = unlimited_aura->GetDuration();
                    caster->CastSpell(caster, SPELL_SHAMAN_UNLIMITED_POWER_HASTE, true);
                    if (Aura* unlimited_aura = caster->GetAura(SPELL_SHAMAN_UNLIMITED_POWER_HASTE))
                        unlimited_aura->SetDuration(duration);
                }
            });
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_sha_icefury::HandleEffectHit, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
        AfterCast += SpellCastFn(spell_sha_icefury::HandleAfterCast);
    }
};

// 210714 - Icefury aura
class aura_sha_icefury : public AuraScript
{
    PrepareAuraScript(aura_sha_icefury);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == SPELL_SHAMAN_FROST_SHOCK)
            return true;

        return false;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_sha_icefury::CheckProc);
    }
};

// 196840 - Frost Shock
class spell_sha_frost_shock : public SpellScript
{
    PrepareSpellScript(spell_sha_frost_shock);

    void HandleEffectHit(SpellEffIndex effIndex)
    {
        if (Unit* caster = GetCaster())
        {
            if (Aura* aura = caster->GetAura(SPELL_SHAMAN_MASTER_OF_THE_ELEMENTS))
            {
                SetHitDamage(GetHitDamage() + CalculatePct(GetHitDamage(), aura->GetEffect(EFFECT_0)->GetBaseAmount()));
                caster->RemoveAurasDueToSpell(SPELL_SHAMAN_MASTER_OF_THE_ELEMENTS);
            }
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_sha_frost_shock::HandleEffectHit, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

// Overload Spells
// 45284 - Lighting Overload, 45297 - Chain Lighting Overload, 77451 - Lava Burst Overload, 219271 - Icefury Overload, 120588 - Elemental Blast Overload
class spell_sha_overload_spells : public SpellScript
{
    PrepareSpellScript(spell_sha_overload_spells);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_SHAMAN_MASTERY_ELEMENTAL_OVERLOAD });
    }

    void HandleDamage(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();

        if (!caster || !target)
            return;

        uint8 percent = sSpellMgr->GetSpellInfo(SPELL_SHAMAN_MASTERY_ELEMENTAL_OVERLOAD)->GetEffect(EFFECT_1).BasePoints;
        uint32 damage = CalculatePct(GetHitDamage(), percent);
        SetHitDamage(damage);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_sha_overload_spells::HandleDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

// 260895 - Unlimited Power
class aura_sha_unlimited_power : public AuraScript
{
    PrepareAuraScript(aura_sha_unlimited_power);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_sha_unlimited_power::CheckProc);
    }
};

// 2645 - Ghost Wolf
class aura_sha_ghost_wolf : public AuraScript
{
    PrepareAuraScript(aura_sha_ghost_wolf);

    void CalculateAmount(AuraEffect const* /*aurEff*/, int32& amount, bool& /*canBeRecalculated*/)
    {
        amount = 100;
    }

    void HandleApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* caster = GetCaster())
        {
            if (caster->HasAura(SPELL_SHAMAN_SPIRIT_WOLF))
                caster->CastSpell(caster, SPELL_SHAMAN_SPIRIT_WOLF_TRIGGER, true);

            if (AuraEffect* aurEff = caster->GetAuraEffect(SPELL_SHAMAN_PACK_SPIRIT_POWER, EFFECT_0))
                caster->CastCustomSpell(SPELL_SHAMAN_PACK_SPIRIT_HEAL, SPELLVALUE_BASE_POINT0, aurEff->GetAmount(), caster, true);

            if (caster->HasAura(SPELL_SHAMAN_SPECTRAL_RECOVERY))
                caster->CastSpell(caster, SPELL_SHAMAN_SPECTRAL_RECOVERY_HEAL, true);
        }
    }

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* caster = GetCaster())
        {
            if (caster->HasAura(SPELL_SHAMAN_SPIRIT_WOLF))
            {
                caster->RemoveAura(SPELL_SHAMAN_SPIRIT_WOLF_TRIGGER);
                caster->RemoveAura(SPELL_SHAMAN_SPIRIT_WOLF_AURA);
                caster->RemoveAura(SPELL_SHAMAN_SPECTRAL_RECOVERY_HEAL);
            }

            if (caster->HasAura(SPELL_SHAMAN_PACK_SPIRIT_HEAL))
                caster->RemoveAura(SPELL_SHAMAN_PACK_SPIRIT_HEAL);
        }
    }

    void Register() override
    {
        DoEffectCalcAmount += AuraEffectCalcAmountFn(aura_sha_ghost_wolf::CalculateAmount, EFFECT_2, SPELL_AURA_MOD_MINIMUM_SPEED);
        OnEffectApply += AuraEffectApplyFn(aura_sha_ghost_wolf::HandleApply, EFFECT_0, SPELL_AURA_MOD_SHAPESHIFT, AURA_EFFECT_HANDLE_REAL);
        OnEffectRemove += AuraEffectRemoveFn(aura_sha_ghost_wolf::HandleRemove, EFFECT_0, SPELL_AURA_MOD_SHAPESHIFT, AURA_EFFECT_HANDLE_REAL);
    }
};

// 260878 - Spirit Wolf
class aura_sha_spirit_wolf : public AuraScript
{
    PrepareAuraScript(aura_sha_spirit_wolf);

    void HandleApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* caster = GetCaster())
            if (caster->HasAura(SPELL_SHAMAN_GHOST_WOLF))
                caster->CastSpell(caster, SPELL_SHAMAN_SPIRIT_WOLF_TRIGGER, true);
    }

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* caster = GetCaster())
            if (caster->HasAura(SPELL_SHAMAN_GHOST_WOLF))
            {
                caster->RemoveAura(SPELL_SHAMAN_SPIRIT_WOLF_TRIGGER);
                caster->RemoveAura(SPELL_SHAMAN_SPIRIT_WOLF_AURA);
            }
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(aura_sha_spirit_wolf::HandleApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        OnEffectRemove += AuraEffectRemoveFn(aura_sha_spirit_wolf::HandleRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

// 53390 - Tidal Waves Buff Last Update 8.0.1 Build 28153
class aura_shaman_tidal_waves_buff : public AuraScript
{
    PrepareAuraScript(aura_shaman_tidal_waves_buff);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetSpellInfo() && (eventInfo.GetSpellInfo()->Id == SPELL_GREATER_HEALING_WAVE || eventInfo.GetSpellInfo()->Id == SPELL_HEALING_SURGE))
            return true;

        return false;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (Unit* caster = GetCaster())
        {
            caster->GetAura(SPELL_SHAMAN_TIDAL_WAVES)->ModStackAmount(-1);
            if (caster->HasAura(SPELL_SHAMAN_FLASH_FLOOD))
                caster->CastSpell(caster, SPELL_SHAMAN_FLASH_FLOOD_BUFF, true);
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_shaman_tidal_waves_buff::CheckProc);
        OnProc += AuraProcFn(aura_shaman_tidal_waves_buff::HandleProc);
    }
};

// 10444 - Flametongue Attack
class spell_sha_flametongue_attack : public SpellScript
{
    PrepareSpellScript(spell_sha_flametongue_attack);

    void HandleOnEffectHitTarget(SpellEffIndex /*effIndex*/)
    {
        if (Unit* caster = GetCaster())
            SetHitDamage(caster->GetTotalAttackPowerValue(BASE_ATTACK) * 0.04f);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_sha_flametongue_attack::HandleOnEffectHitTarget, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

// 201900 - Hot Hand
class aura_sha_hot_hand : public AuraScript
{
    PrepareAuraScript(aura_sha_hot_hand);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (Unit* caster = GetCaster())
            if (caster->HasAura(SPELL_SHAMAN_FLAMETONGUE_WEAPON_AURA))
                return true;

        return false;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (Unit* caster = GetCaster())
        {
            caster->CastSpell(caster, SPELL_SHAMAN_HOT_HAND, true);
            
            // ServerToClient: SMSG_UPDATE_COOLDOWN (0x2758) Length: 12 ConnIdx: 1 Time: 06/14/2022 01:39:09.445 Number: 9122
            // SpellId: 60103
            // SpeedRate: 4
            // SpeedRate2: 1

            caster->GetSpellHistory()->ModifyCooldown(60103, -8000);

            //if (auto player = caster->ToPlayer())
            //{
            //    WorldPackets::Spells::UpdateCooldown cooldown;
            //    cooldown.SpellID = 60103;
            //    cooldown.ModRate = 4.0f;
            //    player->SendDirectMessage(cooldown.Write());
            //}

        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_sha_hot_hand::CheckProc);
        OnProc += AuraProcFn(aura_sha_hot_hand::HandleProc);
    }
};

//  17364 - Stormstrike
class spell_sha_stormstrike : public SpellScript
{
    PrepareSpellScript(spell_sha_stormstrike);

    void HandleAfterCast()
    {
        if (Unit* caster = GetCaster())
        {
            caster->RemoveAurasDueToSpell(SPELL_SHAMAN_LANDSLIDE_AURA);
            caster->RemoveAurasDueToSpell(SPELL_SHAMAN_STORMSTRIKE_ADD_DAMAGE);

            // Forked Lightning
            if (caster->HasAura(SPELL_SHAMAN_FORKED_LIGHTNING))
                caster->CastSpell(caster, SPELL_SHAMAN_FORKED_LIGHTNING_DAMAGE, true);
        }
    }

    void Register() override
    {
        AfterCast += SpellCastFn(spell_sha_stormstrike::HandleAfterCast);
    }
};

// 192106 - Lightning Shield
class spell_lightning_shield : public SpellScript
{
    PrepareSpellScript(spell_lightning_shield);

    void HandlePrepare()
    {
        if (Unit* caster = GetCaster())
            if (Aura* aura = caster->GetAura(SPELL_SHAMAN_LIGTHNING_SHIELD_CHARGE))
                charges = aura->GetStackAmount();
    }

    void HandleHit()
    {
        if (Unit* caster = GetCaster())
            if (Aura* aura = caster->GetAura(SPELL_SHAMAN_LIGTHNING_SHIELD_CHARGE))
                aura->SetStackAmount(charges);
    }

    void Register() override
    {
        OnPrepare += SpellOnPrepareFn(spell_lightning_shield::HandlePrepare);
        OnHit += SpellHitFn(spell_lightning_shield::HandleHit);
    }

private:
    uint8 charges = 1;
};

// 192106 - Lightning Shield
class aura_lightning_shield : public AuraScript
{
    PrepareAuraScript(aura_lightning_shield);

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (Unit* caster = GetCaster())
        {
            if (eventInfo.GetSpellInfo())
            {
                if (eventInfo.GetSpellInfo()->Id == SPELL_SHAMAN_STORMSTRIKE_MAIN)
                    if (Aura* aura = caster->GetAura(SPELL_SHAMAN_LIGTHNING_SHIELD_CHARGE))
                    {
                        uint32 currentDuration = aura->GetDuration();
                        aura->ModStackAmount(+2);
                        aura->SetDuration(currentDuration);
                        if (aura->GetStackAmount() == 20)
                        {
                            caster->Variables.Set<uint32>("SHIELD_DURATION", aura->GetDuration());
                            caster->CastSpell(caster, SPELL_SHAMAN_LIGTHNING_SHIELD_OVERCHARGE, true);
                            aura->SetStackAmount(1);
                        }
                    }
                return;
            }
            if (Aura* aura = caster->GetAura(SPELL_SHAMAN_LIGTHNING_SHIELD_CHARGE))
            {
                uint32 currentDuration = aura->GetDuration();
                aura->ModStackAmount(+1);
                aura->SetDuration(currentDuration);
                if (aura->GetStackAmount() == 20)
                {
                    caster->Variables.Set<uint32>("SHIELD_DURATION", aura->GetDuration());
                    caster->CastSpell(caster, SPELL_SHAMAN_LIGTHNING_SHIELD_OVERCHARGE, true);
                    aura->SetStackAmount(1);
                }
            }
        }
    }

    void Register() override
    {
        OnProc += AuraProcFn(aura_lightning_shield::HandleProc);
    }
};

// 197992 - Landslide
class aura_sha_landslide : public AuraScript
{
    PrepareAuraScript(aura_sha_landslide);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == SPELL_SHAMAN_ROCKBITER)
            return true;

        return false;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_sha_landslide::CheckProc);
    }
};

// 202004 - Landslide Aura
class aura_sha_landslide_aura : public AuraScript
{
    PrepareAuraScript(aura_sha_landslide_aura);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_sha_landslide_aura::CheckProc);
    }
};

// 118905 - Static Charge
class aura_sha_static_charge : public AuraScript
{
    PrepareAuraScript(aura_sha_static_charge);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_SHAMAN_STATIC_CHARGE, SPELL_SHAMAN_STATIC_TOTEM });
    }

    void HandleApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Unit* caster = GetCaster();
        if (!caster)
            return;

        auto current = caster->Variables.GetValue("stunnedCounter", 0);
        if (caster && caster->GetOwner() && caster->GetOwner()->HasAura(SPELL_SHAMAN_STATIC_CHARGE) && current < 4)
        {
            caster->Variables.Set("stunnedCounter", current++);
            caster->GetOwner()->GetSpellHistory()->ModifyCooldown(SPELL_SHAMAN_STATIC_TOTEM, -1s * (int32)sSpellMgr->GetSpellInfo(SPELL_SHAMAN_STATIC_CHARGE)->GetEffect(EFFECT_0).BasePoints);
        }
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(aura_sha_static_charge::HandleApply, EFFECT_0, SPELL_AURA_MOD_STUN, AURA_EFFECT_HANDLE_REAL);
    }
};

// 260694 - Exposed Elements
class aura_sha_exposed_elements : public AuraScript
{
    PrepareAuraScript(aura_sha_exposed_elements);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == SPELL_SHAMAN_EARTH_SHOCK)
            return true;

        return false;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_sha_exposed_elements::CheckProc);
    }
};

// 188389 - Flame Shock Aura
class aura_sha_flame_shock_aura : public AuraScript
{
    PrepareAuraScript(aura_sha_flame_shock_aura);

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
        if (Unit* caster = GetCaster())
            if (caster->GetSummonedCreatureByEntry(95061))
                caster->ModifyPower(POWER_MAELSTROM, +3);
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(aura_sha_flame_shock_aura::HandlePeriodic, EFFECT_1, SPELL_AURA_PERIODIC_DAMAGE);
    }
};

// 204261 - Spectral Recovery
class aura_sha_spectral_recovery : public AuraScript
{
    PrepareAuraScript(aura_sha_spectral_recovery);

    void HandleApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* caster = GetCaster())
            if (caster->HasAura(SPELL_SHAMAN_GHOST_WOLF))
                caster->CastSpell(caster, SPELL_SHAMAN_SPECTRAL_RECOVERY_HEAL, true);
    }

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* caster = GetCaster())
            caster->RemoveAura(SPELL_SHAMAN_SPECTRAL_RECOVERY_HEAL);
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(aura_sha_spectral_recovery::HandleApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        OnEffectRemove += AuraEffectRemoveFn(aura_sha_spectral_recovery::HandleRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

// 204393 - Control of Lava
class aura_sha_control_of_lava : public AuraScript
{
    PrepareAuraScript(aura_sha_control_of_lava);

    void HandleApply(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        if (auto caster = GetCaster())
            caster->Variables.Set("controlProc", false);
    }

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == SPELL_SHAMAN_FLAME_SHOCK_ELEM)
            return true;
        return false;
    }

    void HandleEffectProc(AuraEffect* /*aurEff*/, ProcEventInfo& /*eventInfo*/)
    {
        PreventDefaultAction();
        GetTarget()->CastSpell(GetTarget(), SPELL_SHAMAN_CONTROL_OF_LAVA_PROC, true);
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(aura_sha_control_of_lava::HandleApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        DoCheckProc += AuraCheckProcFn(aura_sha_control_of_lava::CheckProc);
        OnEffectProc += AuraEffectProcFn(aura_sha_control_of_lava::HandleEffectProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

// 236746 - Control of Lava Proc
class aura_sha_control_of_lava_proc : public AuraScript
{
    PrepareAuraScript(aura_sha_control_of_lava_proc);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_SHAMAN_LAVA_BURST });
    }

    bool Load() override
    {
        if (auto caster = GetCaster())
            return caster->IsPlayer();
        return false;
    }

    void HandleApply(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        if (Unit* caster = GetCaster())
            caster->GetSpellHistory()->RestoreCharge(sSpellMgr->AssertSpellInfo(SPELL_SHAMAN_LAVA_BURST)->ChargeCategoryId);
    }

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();
        if (!caster && !eventInfo.GetSpellInfo())
            return false;

        if (eventInfo.GetSpellInfo()->Id == SPELL_SHAMAN_LAVA_BURST && caster->Variables.GetValue("controlProc", false))
            return true;
        return false;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();
        if (Unit* caster = GetCaster())
            caster->RemoveAura(GetAura());
    }

    void HandleRemove(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        if (auto caster = GetCaster())
            caster->Variables.Set("controlProc", false);
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(aura_sha_control_of_lava_proc::HandleApply, EFFECT_0, SPELL_AURA_ADD_PCT_MODIFIER, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
        DoCheckProc += AuraCheckProcFn(aura_sha_control_of_lava_proc::CheckProc);
        OnProc += AuraProcFn(aura_sha_control_of_lava_proc::HandleProc);
        OnEffectRemove += AuraEffectRemoveFn(aura_sha_control_of_lava_proc::HandleRemove, EFFECT_0, SPELL_AURA_ADD_PCT_MODIFIER, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
    }
};

// 208997 - Counterstrike Totem Last Update 8.0.1 Build 28153
class aura_sha_counterstrike_totem : public AuraScript
{
    PrepareAuraScript(aura_sha_counterstrike_totem);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();
        Unit* target = GetUnitOwner();
        if (!caster || !target)
            return false;

        if (Unit* owner = caster->GetOwner())
            if (eventInfo.GetDamageInfo() && eventInfo.GetDamageInfo()->GetDamage() > 0 &&
                (eventInfo.GetDamageInfo()->GetDamageType() == DIRECT_DAMAGE || eventInfo.GetDamageInfo()->GetDamageType() == SPELL_DIRECT_DAMAGE) && owner->IsValidAttackTarget(target))
                return true;

        return false;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        DamageInfo* damageInfo = eventInfo.GetDamageInfo();
        Unit* caster = GetCaster();
        Unit* target = GetUnitOwner();
        if (!caster || !target || !damageInfo)
            return;

        Unit* owner = caster->GetOwner();
        if (!owner)
            return;

        SpellInfo const* counterstrikeTotem = sSpellMgr->GetSpellInfo(SPELL_TOTEM_COUNTERSTRIKE_SUMMON);

        if (!counterstrikeTotem)
            return;

        int32 damage = damageInfo->GetDamage();
        if (!damage)
            return;

        std::list<Unit*> targets;
        target->GetFriendlyUnitListInRange(targets, counterstrikeTotem->GetEffect(EFFECT_1).BasePoints);

        // No appropriate targets
        if (targets.empty())
            return;

        targets.sort(Trinity::HealthPctOrderPred(true));

        if (Unit* victim = targets.front())
            caster->CastCustomSpell(victim, SPELL_TOTEM_COUNTERSTRIKE_DAMAGE, &damage, nullptr, nullptr, true);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_sha_counterstrike_totem::CheckProc);
        OnProc += AuraProcFn(aura_sha_counterstrike_totem::HandleProc);
    }
};

// 61295 - Riptide
class aura_sha_riptide : public AuraScript
{
    PrepareAuraScript(aura_sha_riptide);

    void HandleApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Unit* caster = GetCaster();
        Unit* owner = GetUnitOwner();
        if (!caster || !owner)
            return;

        if (caster->HasAura(SPELL_SHAMAN_RIPPLING_WATERS))
            caster->CastSpell(owner, SPELL_SHAMAN_RIPPLING_WATERS_HEAL, true);
    }

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Unit* caster = GetCaster();
        Unit* owner = GetUnitOwner();
        if (!caster || !owner)
            return;

        if (caster->HasAura(SPELL_SHAMAN_RIPPLING_WATERS) && (GetTargetApplication()->GetRemoveMode() == AURA_REMOVE_BY_EXPIRE || GetTargetApplication()->GetRemoveMode() == AURA_REMOVE_BY_ENEMY_SPELL))
            caster->CastSpell(owner, SPELL_SHAMAN_RIPPLING_WATERS_HEAL, true);
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(aura_sha_riptide::HandleApply, EFFECT_1, SPELL_AURA_PERIODIC_HEAL, AURA_EFFECT_HANDLE_REAPPLY);
        OnEffectRemove += AuraEffectRemoveFn(aura_sha_riptide::HandleRemove, EFFECT_1, SPELL_AURA_PERIODIC_HEAL, AURA_EFFECT_HANDLE_REAL);
    }
};

// 204350 - Forked Lightning Damage
class spell_sha_forked_lightning : public SpellScript
{
    PrepareSpellScript(spell_sha_forked_lightning);

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        if (Unit* caster = GetCaster())
            if (targets.size() > 0)
            {
                targets.sort(Trinity::DistanceCompareOrderPred(caster, false));
                if (targets.size() > 2)
                    targets.resize(2);
            }
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_sha_forked_lightning::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
    }
};

// 192087 - Searing Assault
class aura_sha_searing_assault : public AuraScript
{
    PrepareAuraScript(aura_sha_searing_assault);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == SPELL_SHAMAN_FLAMETONGUE)
            return true;

        return false;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_sha_searing_assault::CheckProc);
    }
};

// 204357 - Ride the Lightning
class aura_sha_ride_the_lightning : public AuraScript
{
    PrepareAuraScript(aura_sha_ride_the_lightning);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == SPELL_SHAMAN_STORMSTRIKE)
            return true;

        return false;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_sha_ride_the_lightning::CheckProc);
    }
};

// 370 - Purge
class spell_sha_purge : public SpellScript
{
    PrepareSpellScript(spell_sha_purge);

    void OnSuccessfulDispel(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        if (caster->HasAura(SPELL_SHAMAN_ELECTROCUTE))
            caster->CastSpell(target, SPELL_SHAMAN_ELECTROCUTE_DAMAGE, true);

        if (caster->HasAura(SPELL_SHAMAN_PURIFYING_WATERS))
            caster->CastSpell(caster, SPELL_SHAMAN_PURIFYING_WATERS_HEAL, true);
    }

    void Register() override
    {
        OnEffectSuccessfulDispel += SpellEffectFn(spell_sha_purge::OnSuccessfulDispel, EFFECT_0, SPELL_EFFECT_DISPEL);
    }
};

// 51514 - Hex
class aura_sha_hex : public AuraScript
{
    PrepareAuraScript(aura_sha_hex);

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
                owner->ToUnit()->RemoveAura(GetAura());
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_sha_hex::CheckProc);
        OnProc += AuraProcFn(aura_sha_hex::HandleProc);
    }
};

// 224125 - Molten Weapon
class aura_sha_molten_weapon : public AuraScript
{
    PrepareAuraScript(aura_sha_molten_weapon);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == SPELL_SHAMAN_LAVA_LASH)
            return true;

        return false;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();
        Unit* target = eventInfo.GetActionTarget();
        if (!caster || !target)
            return;

        if (eventInfo.GetDamageInfo() && eventInfo.GetDamageInfo()->GetDamage() > 0)
            caster->CastCustomSpell(SPELL_SHAMAN_MOLTEN_WEAPON_DAMAGE, SPELLVALUE_BASE_POINT0, CalculatePct(eventInfo.GetDamageInfo()->GetDamage(), 35), target, true);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_sha_molten_weapon::CheckProc);
        OnProc += AuraProcFn(aura_sha_molten_weapon::HandleProc);
    }
};

// 224126 - Icy Edge
class aura_sha_icy_edge : public AuraScript
{
    PrepareAuraScript(aura_sha_icy_edge);

    void HandleProc(ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();
        Unit* target = eventInfo.GetActionTarget();
        if (!caster || !target)
            return;

        caster->CastSpell(target, SPELL_SHAMAN_ICY_EDGE_DAMAGE, true);
    }

    void Register() override
    {
        OnProc += AuraProcFn(aura_sha_icy_edge::HandleProc);
    }
};

// 190899 - Healing Surge Bonus
class aura_healing_surge_bonus : public AuraScript
{
    PrepareAuraScript(aura_healing_surge_bonus);

    void HandleRemove(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /* mode */)
    {
        if (Unit* caster = GetCaster())
            caster->RemoveAura(SPELL_SHAMAN_HEALING_SURGE_WALKING);
    }

    void Register() override
    {
        OnEffectRemove += AuraEffectRemoveFn(aura_healing_surge_bonus::HandleRemove, EFFECT_0, SPELL_AURA_TRIGGER_SPELL_ON_POWER_AMOUNT, AURA_EFFECT_HANDLE_REAL);
    }
};

// 211062 - Static Cling
class aura_static_cling : public AuraScript
{
    PrepareAuraScript(aura_static_cling);

    uint8 castCount = 0;

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        DamageInfo const* damageInfo = eventInfo.GetDamageInfo();
        if (!damageInfo)
            return false;

        Spell const* spell = eventInfo.GetProcSpell();
        SpellInfo const* spellInfo = damageInfo->GetSpellInfo();
        if (!spellInfo || !spell)
            return false;

        if (spell->IsTriggered() && spellInfo->Id != SPELL_SHAMAN_STORMSTRIKE_MAIN)
            return false;

        if (spellInfo->Id == SPELL_SHAMAN_STORMSTRIKE)
            return false;

        castCount = (spellInfo->Id == SPELL_SHAMAN_STORMSTRIKE_MAIN) ? castCount + 1 : 0;
        if (castCount != 2)
            return false;

        castCount = 0;
        return true;
    }

    void HandleOnProc(ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();
        DamageInfo* damageInfo = eventInfo.GetDamageInfo();
        if (!caster || !damageInfo)
            return;

        Unit* target = damageInfo->GetVictim();
        if (!target)
            return;

        caster->CastSpell(target, SPELL_SHAMAN_STATIC_CLING_TARGET, true);
        caster->CastSpell(caster, SPELL_SHAMAN_STATIC_CLING_SHAMAN, true);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_static_cling::CheckProc);
        OnProc += AuraProcFn(aura_static_cling::HandleOnProc);
    }
};

// 210927 - Static Cling Target
class aura_static_cling_target : public AuraScript
{
    PrepareAuraScript(aura_static_cling_target);

    void OnTick(AuraEffect const* /*aurEff*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetTarget();
        SpellInfo const* spellInfo = GetSpellInfo();
        if (!caster || !caster->IsPlayer() || !target || !spellInfo || !spellInfo->RangeEntry)
            return;

        if (caster->ToPlayer()->GetSpecializationId() == TALENT_SPEC_SHAMAN_ENHANCEMENT && caster->IsInCombat() && target->IsInCombat() && caster->GetDistance(target) < spellInfo->GetMaxRange())
            return;

        caster->RemoveAura(SPELL_SHAMAN_STATIC_CLING_SHAMAN);
        SetDuration(0);
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(aura_static_cling_target::OnTick, EFFECT_1, SPELL_AURA_PERIODIC_DUMMY);
    }
};

// 192249 - Greater Storm Elemental
class spell_sha_storm_elemental : public SpellScript
{
    PrepareSpellScript(spell_sha_storm_elemental);

    void HandleHit()
    {
        Unit* caster = GetCaster();
        Unit* target = GetExplTargetUnit();
        if (!caster || !target)
            return;

        caster->Variables.Set("currentTarget", target->GetGUID());
        if (caster->HasAura(SPELL_SHAMAN_PRIMAL_ELEMENTALIST))
            caster->CastSpell(caster, SPELL_SHAMAN_PRIMAL_STORM_ELEMENTAL_SUMMON, true);
        else
            caster->CastSpell(caster, SPELL_SHAMAN_STORM_ELEMENTAL_SUMMON, true);
    }

    void Register() override
    {
        OnHit += SpellHitFn(spell_sha_storm_elemental::HandleHit);
    }
};

// 157299 / 157319 - Storm Elemental Buff
class aura_sha_storm_elemental_buff : public AuraScript
{
    PrepareAuraScript(aura_sha_storm_elemental_buff);

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* caster = GetCaster())
            caster->RemoveAura(SPELL_SHAMAN_STORM_ELEMENTAL_BUFF);
    }

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetSpellInfo() && (eventInfo.GetSpellInfo()->Id == SPELL_SHAMAN_LIGHTNING_BOLT_ELEM || eventInfo.GetSpellInfo()->Id == SPELL_SHAMAN_CHAIN_LIGHTNING_ELEM))
            return true;

        return false;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (Unit* caster = GetCaster())
        {
            caster->CastSpell(caster, SPELL_SHAMAN_STORM_ELEMENTAL_BUFF, true);
            if (Aura* aura = caster->GetAura(SPELL_SHAMAN_STORM_ELEMENTAL_BUFF))
                aura->ModStackAmount(-1);
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_sha_storm_elemental_buff::CheckProc);
        OnProc += AuraProcFn(aura_sha_storm_elemental_buff::HandleProc);
        OnEffectRemove += AuraEffectRemoveFn(aura_sha_storm_elemental_buff::HandleRemove, EFFECT_1, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

// 269005 - Eye of the Storm Damage
class spell_sha_eye_of_the_storm_damage : public SpellScript
{
    PrepareSpellScript(spell_sha_eye_of_the_storm_damage);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ npc_greater_storm_elemental::SPELL_THE_EYE_OF_THE_STORM });
    }

    void HandleHit()
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        if (npc_greater_storm_elemental* elemental = (npc_greater_storm_elemental*)caster)
        {
            elemental->IncrementBuff();
            SetHitDamage(GetHitDamage() + CalculatePct(GetHitDamage(), sSpellMgr->GetSpellInfo(npc_greater_storm_elemental::SPELL_THE_EYE_OF_THE_STORM)->GetEffect(EFFECT_1).BasePoints * elemental->GetIncrementBuff()));
        }
    }

    void Register() override
    {
        OnHit += SpellHitFn(spell_sha_eye_of_the_storm_damage::HandleHit);
    }
};

// 64695 - Earthgrab
class spell_sha_earthgrab : public SpellScript
{
    PrepareSpellScript(spell_sha_earthgrab);

    void FilterTargets(std::list<WorldObject*>& unitList)
    {
        Unit* caster = GetCaster();
        SpellInfo const* spellInfo = GetSpellInfo();

        if (!caster || !spellInfo)
            return;

        unitList.remove_if(Trinity::UnitAuraCheck(true, spellInfo->Id));

        if (!unitList.empty())
        {
            for (auto object : unitList)
            {
                if (Unit* unit = object->ToUnit())
                {
                    if (unit->HasAura(SPELL_SHAMAN_EARTHGRAB_IMMUNITY, caster->GetGUID()))
                    {
                        caster->CastSpell(unit, SPELL_SHAMAN_EARTHBIND_FOR_EARTHGRAB_TOTEM, true);
                        unitList.remove(object);
                    }
                }
            }
        }
    }

    void HandleHit()
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        caster->CastSpell(target, SPELL_SHAMAN_EARTHGRAB_IMMUNITY, true);
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_sha_earthgrab::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
        OnHit += SpellHitFn(spell_sha_earthgrab::HandleHit);
    }
};

// 64695 - Earthgrab Aura
class aura_warl_earthgrab : public AuraScript
{
    PrepareAuraScript(aura_warl_earthgrab);

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

    void HandleRemove(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /* mode */)
    {
        Unit* caster = GetCaster();
        Unit* target = GetTarget();
        if (!caster || !target)
            return;

        caster->CastSpell(target, SPELL_SHAMAN_EARTHGRAB_IMMUNITY, true);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_warl_earthgrab::CheckProc);
        OnProc += AuraProcFn(aura_warl_earthgrab::HandleProc);
        OnEffectRemove += AuraEffectRemoveFn(aura_warl_earthgrab::HandleRemove, EFFECT_0, SPELL_AURA_MOD_ROOT_2, AURA_EFFECT_HANDLE_REAL);
    }
};

// 221678 - Calming Waters Last Update 8.0.1 Build 28153
class aura_shaman_calming_waters : public AuraScript
{
    PrepareAuraScript(aura_shaman_calming_waters);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();

        if (!caster)
            return false;

        if (caster->HasAura(SPELL_SHAMAN_CALMING_WATERS))
            return false;

        if (!(eventInfo.GetHitMask() & PROC_HIT_INTERRUPT))
            return false;

        return true;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (Unit* caster = GetCaster())
            caster->Variables.Set<bool>("CalmingWatersProc", true);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_shaman_calming_waters::CheckProc);
        OnProc += AuraProcFn(aura_shaman_calming_waters::HandleProc);
    }
};

// 221677 - Calming Waters Last Update 8.0.1 Build 28153
class aura_shaman_calming_waters_buff : public AuraScript
{
    PrepareAuraScript(aura_shaman_calming_waters_buff);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();

        if (!caster)
            return false;

        if (!eventInfo.GetSpellInfo()->HasEffectMechanic(MECHANIC_SILENCE) && !eventInfo.GetSpellInfo()->HasEffectMechanic(MECHANIC_INTERRUPT))
            return false;

        if (caster->Variables.Exist("CalmingWatersProc") && caster->Variables.GetValue<bool>("CalmingWatersProc"))
        {
            caster->Variables.Set<bool>("CalmingWatersProc", false);
            return false;
        }

        return true;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (WorldObject* owner = GetOwner())
            if (owner->ToUnit())
                owner->ToUnit()->RemoveAura(GetAura());
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_shaman_calming_waters_buff::CheckProc);
        OnProc += AuraProcFn(aura_shaman_calming_waters_buff::HandleProc);
    }
};

// 215785 - Hot Hand
class aura_sha_hot_hand_aura : public AuraScript
{
    PrepareAuraScript(aura_sha_hot_hand_aura);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == SPELL_SHAMAN_LAVA_LASH)
            return true;

        return false;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_sha_hot_hand_aura::CheckProc);
    }
};

// 193876 - Shamanism
class spell_aura_shamanism : public AuraScript
{
    PrepareAuraScript(spell_aura_shamanism);

    void CalculateAmount(AuraEffect const* /*aurEff*/, int32& amount, bool& /*canBeRecalculated*/)
    {
        if (Unit* caster = GetCaster())
            if (Player* player = caster->ToPlayer())
                if (player->GetTeamId() == TEAM_ALLIANCE)
                    amount = SPELL_SHAMAN_ALLI_HEROISMS;
                else
                    amount = SPELL_SHAMAN_HORDE_HEROIMS;
    }

    void Register() override
    {
        DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_aura_shamanism::CalculateAmount, EFFECT_1, SPELL_AURA_OVERRIDE_ACTIONBAR_SPELLS);
    }
};

// 201846 - Stormbringer
class aura_sha_stormbringer : public AuraScript
{
    PrepareAuraScript(aura_sha_stormbringer);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == SPELL_SHAMAN_STORMSTRIKE)
            return true;

        return false;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_sha_stormbringer::CheckProc);
    }
};

// 190488 - Maelstrom Controller
class aura_sha_malestrom_controller : public AuraScript
{
    PrepareAuraScript(aura_sha_malestrom_controller);

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (Unit* caster = GetCaster())
            if (!caster->HasSpell(SPELL_SHAMAN_EARTH_SHOCK))
                PreventDefaultAction();
    }

    void Register() override
    {
        OnProc += AuraProcFn(aura_sha_malestrom_controller::HandleProc);
    }
};

// 191634 - Stormkeeper
class aura_sha_stormkeeper : public AuraScript
{
    PrepareAuraScript(aura_sha_stormkeeper);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_sha_stormkeeper::CheckProc);
    }
};

// 273221 - Aftershock
class aura_sha_aftershock : public AuraScript
{
    PrepareAuraScript(aura_sha_aftershock);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_SHAMAN_AFTERSHOCK });
    }

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (Spell const* procSpell = eventInfo.GetProcSpell())
            if (SpellPowerCost const* powerCost = procSpell->GetPowerCost(POWER_MAELSTROM))
            {
                uint8 percent = sSpellMgr->GetSpellInfo(SPELL_SHAMAN_AFTERSHOCK)->GetEffect(EFFECT_0).BasePoints;
                if (roll_chance_i(percent))
                    return true;
            }

        return false;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (Unit* caster = GetCaster())
            if (Spell const* procSpell = eventInfo.GetProcSpell())
                if (SpellPowerCost const* powerCost = procSpell->GetPowerCost(POWER_MAELSTROM))
                    caster->CastCustomSpell(SPELL_SHAMAN_AFTERSHOCK_ENERGIZE, SPELLVALUE_BASE_POINT0, powerCost->Amount, caster, true);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_sha_aftershock::CheckProc);
        OnProc += AuraProcFn(aura_sha_aftershock::HandleProc);
    }
};

// 32175 - Stormstrike Main
class spell_sha_stormstrike_main : public SpellScript
{
    PrepareSpellScript(spell_sha_stormstrike_main);

    void HandleHit()
    {
        if (Unit* caster = GetCaster())
            if (Aura* aura = caster->GetAura(SPELL_SHAMAN_ROLLING_STORM_BUFF))
            {
                SetHitDamage(GetHitDamage() + aura->GetEffect(EFFECT_0)->GetAmount());
                caster->RemoveAurasDueToSpell(SPELL_SHAMAN_ROLLING_STORM_BUFF);
            }
    }

    void Register() override
    {
        OnHit += SpellHitFn(spell_sha_stormstrike_main::HandleHit);
    }
};

// Called by Spirit Link (PvP Talent) - 204293
// Last Update 8.0.1 Build 28153
class spell_sha_spirit_link_pvp_aura : public AuraScript
{
    PrepareAuraScript(spell_sha_spirit_link_pvp_aura);

    void AfterApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* caster = GetCaster())
        {
            if (Unit* target = GetTarget())
            {
                if (caster == target)
                    return;

                targets.push_back(target->GetGUID());
            }
        }
    }

    void AfterRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* caster = GetCaster())
        {
            if (Unit* target = GetTarget())
            {
                if (caster == target)
                    return;

                targets.remove(target->GetGUID());
            }
        }
    }

    void CalculateAmount(AuraEffect const* /*aurEff*/, int32& amount, bool& /*canBeRecalculated*/)
    {
        amount = -1;
    }

    void OnAbsorb(AuraEffect* /*aurEff*/, DamageInfo& dmgInfo, uint32& absorbAmount)
    {
        if (Unit* caster = GetCaster())
        {
            if (Unit* target = GetTarget())
            {
                if (dmgInfo.GetSpellInfo() && dmgInfo.GetSpellInfo()->Id == SPELL_SHAMAN_SPIRIT_LINK_PVP_DAMAGE)
                    return;

                // Redirects the damage on linked targets
                int32 amount = CalculatePct(dmgInfo.GetDamage(), GetSpellInfo()->GetEffect(EFFECT_1).BasePoints);

                absorbAmount = amount;

                std::list<ObjectGuid> redirectTargets;
                for (ObjectGuid guid : targets)
                {
                    if (target->GetGUID() == guid)
                        continue;

                    redirectTargets.push_back(guid);
                }

                if (target != caster)
                    redirectTargets.push_back(caster->GetGUID());

                if (!redirectTargets.empty())
                    amount /= int32(redirectTargets.size());

                for (ObjectGuid guid : redirectTargets)
                    if (Unit* unit = ObjectAccessor::GetUnit(*target, guid))
                        target->CastCustomSpell(unit, SPELL_SHAMAN_SPIRIT_LINK_PVP_DAMAGE, &amount, nullptr, nullptr, true);
            }
        }
    }

private:
    std::list<ObjectGuid> targets;

    void Register() override
    {
        AfterEffectApply += AuraEffectApplyFn(spell_sha_spirit_link_pvp_aura::AfterApply, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
        AfterEffectRemove += AuraEffectRemoveFn(spell_sha_spirit_link_pvp_aura::AfterRemove, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
        DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_sha_spirit_link_pvp_aura::CalculateAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
        OnEffectAbsorb += AuraEffectAbsorbFn(spell_sha_spirit_link_pvp_aura::OnAbsorb, EFFECT_0);
    }
};

// 60103 - Lava Lash
//LastUpdate 8.0.1 Build 28153
class spell_sha_lava_lash : public SpellScript
{
    PrepareSpellScript(spell_sha_lava_lash);

    void HandleDamage(SpellEffIndex /*effIndex*/)
    {
        if (Unit* caster = GetCaster())
        {
            if (Unit* target = GetHitUnit())
            {
                if (caster->HasAura(SPELL_SHAMAN_PRIMAL_PRIMER_POWER))
                    if (AuraEffect* aurEff = target->GetAuraEffect(SPELL_SHAMAN_PRIMAL_PRIMER_BUFF, EFFECT_0, caster->GetGUID()))
                        SetHitDamage(GetHitDamage() + (aurEff->GetAmount() * 0.5f));

                if (caster->HasAura(SPELL_SHAMAN_FLAMETONGUE_WEAPON_AURA))
                    caster->CastSpell(target, SPELL_SHAMAN_LAVA_LASH_SPREAD_FLAME_SHOCK, true);

                if (Aura* flameShock = target->GetAura(SPELL_SHAMAN_FLAME_SHOCK_ELEM, GetCaster()->GetGUID()))
                {
                    std::list<Unit*> list;
                    GetCaster()->GetAttackableUnitListInRangeFromCenterObj(target, list, MELEE_RANGE);

                    auto limit = 0;

                    for (auto unit : list)
                    {
                        if (!unit->HasAura(SPELL_SHAMAN_FLAME_SHOCK_ELEM, GetCaster()->GetGUID()))
                        {
                            ++limit;
                            GetCaster()->CastSpell(unit, SPELL_SHAMAN_FLAME_SHOCK_ELEM, true);
                        }

                        if (limit >= 3)
                            break;
                    }
                }
            }
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_sha_lava_lash::HandleDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

// 207778 - Downpour
//LastUpdate 8.0.1 Build 28153
class spell_sha_downpour : public SpellScript
{
    PrepareSpellScript(spell_sha_downpour);

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        affectedCount = targets.size();
        targets.sort(Trinity::HealthPctOrderPred());
        if (targets.size() > 6)
        {
            targets.resize(6);
            affectedCount = 6;
        }
    }

    void HandleAfterCast()
    {
        if (!affectedCount)
            return;

        Unit* caster = GetCaster();
        if (!caster)
            return;

        caster->GetSpellHistory()->StartCooldownROG(GetSpellInfo(), 0, nullptr, false, true, GetSpellInfo()->GetEffect(EFFECT_1).BasePoints * IN_MILLISECONDS * affectedCount);
    }

private:
    uint8 affectedCount = 0;

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_sha_downpour::FilterTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ALLY);
        AfterCast += SpellCastFn(spell_sha_downpour::HandleAfterCast);
    }
};

// 204406 - Thunderstorm (ally target)
//Last Update 8.0.1 Build 28153
class spell_sha_thunderstorm_ally : public SpellScript
{
    PrepareSpellScript(spell_sha_thunderstorm_ally);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo
        ({
            SPELL_SHAMAN_THUNDERSTORM_ALLY_DAMAGE,
            SPELL_SHAMAN_THUNDERSTORM_ALLY_KNOCKBACK
            });
    }

    void HandleDummy(SpellEffIndex /*effIndex*/)
    {
        if (Unit* caster = GetCaster())
        {
            if (Unit* target = GetHitUnit())
            {
                caster->CastSpell(target->GetPosition(), SPELL_SHAMAN_THUNDERSTORM_ALLY_DAMAGE, true);
                caster->CastSpell(target->GetPosition(), SPELL_SHAMAN_THUNDERSTORM_ALLY_KNOCKBACK, true);
            }
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_sha_thunderstorm_ally::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

// 98008 - Spirit Link Totem
// Last Update 8.0.1 Build 28153
class spell_sha_spirit_link_totem : public SpellScript
{
    PrepareSpellScript(spell_sha_spirit_link_totem);

    void HandleAfterCast()
    {
        if (Unit* caster = GetCaster())
            if (Aura* aura = caster->GetAura(SPELL_SHAMAN_SPOUTING_SPIRITS_POWER))
                caster->GetScheduler().Schedule(1s, [aura](TaskContext context)
                    {
                        if (Unit* caster = GetContextUnit())
                        {
                            Creature* totem = caster->GetSummonedCreatureByEntry(53006);
                            if (totem && aura)
                            {
                                int32 heal = aura->GetEffect(EFFECT_0)->GetAmount();
                                caster->CastCustomSpell(totem->GetPositionX(), totem->GetPositionY(), totem->GetPositionZ(), SPELL_SHAMAN_SPOUTING_SPIRITS_HEAL, &heal, nullptr, nullptr, true);
                            }
                        }
                    });
    }

    void Register() override
    {
        AfterCast += SpellCastFn(spell_sha_spirit_link_totem::HandleAfterCast);
    }
};


// 33757 - Windfury Weapon
class spell_sha_windfury_weapon : public SpellScript
{
    PrepareSpellScript(spell_sha_windfury_weapon);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_SHAMAN_WINDFURY_ENCHANTMENT });
    }

    bool Load() override
    {
        return GetCaster()->IsPlayer();
    }

    void HandleEffect(SpellEffIndex effIndex)
    {
        PreventHitDefaultEffect(effIndex);

        if (Item* mainHand = GetCaster()->ToPlayer()->GetWeaponForAttack(BASE_ATTACK, false))
            GetCaster()->CastSpell(mainHand, SPELL_SHAMAN_WINDFURY_ENCHANTMENT, GetSpell());
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_sha_windfury_weapon::HandleEffect, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

// 319773 - Windfury Weapon (proc)
class spell_sha_windfury_weapon_proc : public AuraScript
{
    PrepareAuraScript(spell_sha_windfury_weapon_proc);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_SHAMAN_WINDFURY_ATTACK });
    }

    void HandleEffectProc(AuraEffect* aurEff, ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();

        auto caster = GetCaster();
        if (!caster)
            return;
        auto target = eventInfo.GetProcTarget();
        if (!target)
            return;

        for (uint32 i = 0; i < 2; ++i)
        {
            eventInfo.GetActor()->CastSpell(eventInfo.GetProcTarget(), SPELL_SHAMAN_WINDFURY_ATTACK, aurEff);

            if (caster->HasAura(SPELL_SHAMAN_FORCEFUL_WINDS) && !caster->HasAura(SPELL_SHAMAN_FORCEFUL_WINDS_BUFF) && i == 1)
            {
                caster->CastSpell(caster, SPELL_SHAMAN_FORCEFUL_WINDS_BUFF, true);
            }
            else if (caster->HasAura(SPELL_SHAMAN_FORCEFUL_WINDS) && caster->HasAura(SPELL_SHAMAN_FORCEFUL_WINDS_BUFF))
            {
                int32 duration = 0;
                if (Aura* aura = caster->GetAura(SPELL_SHAMAN_FORCEFUL_WINDS_BUFF))
                {
                    duration = aura->GetDuration();
                    caster->CastSpell(caster, SPELL_SHAMAN_FORCEFUL_WINDS_BUFF, true);
                    aura->SetDuration(duration);
                }
            }
        }
    }

    void Register() override
    {
        OnEffectProc += AuraEffectProcFn(spell_sha_windfury_weapon_proc::HandleEffectProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

// 192078 - Wind Rush Totem (Spell)
//  12676 - AreaTriggerId
struct areatrigger_sha_wind_rush_totem : AreaTriggerAI
{
    static constexpr uint32 REFRESH_TIME = 4500;

    areatrigger_sha_wind_rush_totem(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger), _refreshTimer(REFRESH_TIME) { }

    void OnUpdate(uint32 diff) override
    {
        _refreshTimer -= diff;
        if (_refreshTimer <= 0)
        {
            if (Unit* caster = at->GetCaster())
            {
                for (ObjectGuid const& guid : at->GetInsideUnits())
                {
                    if (Unit* unit = ObjectAccessor::GetUnit(*caster, guid))
                    {
                        if (!caster->IsFriendlyTo(unit))
                            continue;

                        caster->CastSpell(unit, SPELL_SHAMAN_WIND_RUSH, true);
                    }
                }
            }
            _refreshTimer += REFRESH_TIME;
        }
    }

    void OnUnitEnter(Unit* unit) override
    {
        if (Unit* caster = at->GetCaster())
        {
            if (!caster->IsFriendlyTo(unit))
                return;

            caster->CastSpell(unit, SPELL_SHAMAN_WIND_RUSH, true);
        }
    }
private:
    int32 _refreshTimer;
};

// 318038 - Flametongue Weapon
class spell_sha_flametongue_weapon : public SpellScript
{
    PrepareSpellScript(spell_sha_flametongue_weapon);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_SHAMAN_FLAMETONGUE_WEAPON_ENCHANT });
    }

    bool Load() override
    {
        return GetCaster()->GetTypeId() == TYPEID_PLAYER;
    }

    void HandleEffectHitTarget(SpellEffIndex /*effIndex*/)
    {
        Player* player = GetCaster()->ToPlayer();
        uint8 slot = EQUIPMENT_SLOT_MAINHAND;
        if (player->GetPrimarySpecialization() == TALENT_SPEC_SHAMAN_ENHANCEMENT)
            slot = EQUIPMENT_SLOT_OFFHAND;

        Item* targetItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, slot);
        if (!targetItem || !targetItem->GetTemplate()->IsWeapon())
            return;

        player->CastSpell(targetItem, SPELL_SHAMAN_FLAMETONGUE_WEAPON_ENCHANT, true);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_sha_flametongue_weapon::HandleEffectHitTarget, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

// 319778  - Flametongue - SPELL_SHAMAN_FLAMETONGUE_WEAPON_AURA
class spell_sha_flametongue_weapon_aura : public AuraScript
{
    PrepareAuraScript(spell_sha_flametongue_weapon_aura);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_SHAMAN_FLAMETONGUE_ATTACK });
    }

    void HandleEffectProc(AuraEffect* aurEff, ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();

        Unit* attacker = eventInfo.GetActor();
        CastSpellExtraArgs args(aurEff);
        args.AddSpellMod(SPELLVALUE_BASE_POINT0, std::max(1, int32(attacker->GetTotalAttackPowerValue(BASE_ATTACK) * 0.0264f)));
        attacker->CastSpell(eventInfo.GetActionTarget(), SPELL_SHAMAN_FLAMETONGUE_ATTACK, args);
    }

    void Register() override
    {
        OnEffectProc += AuraEffectProcFn(spell_sha_flametongue_weapon_aura::HandleEffectProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

// 320674 chain harvset
class spell_sha_chain_harvest : public SpellScript
{
    PrepareSpellScript(spell_sha_chain_harvest);

    // chain harvest - dummy visual 320762
    // visual 2 - (return ? 321310 ) (321311  script effect)
    // 321595  inital target?
    // 368583  - energize
    enum ChainHarvest
    {
        Jump = 320762,
        VisualReturn = 321310,
        Heal = 320751,
        Dmg = 320752,
        ScriptEffect = 321311,
        Energize = 368583,
    };

    void HandleDamage(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        int hitUnits = 0;

        caster->CastSpell(target, Jump, true);

        if (caster->IsFriendlyTo(target))
        {
            std::list<Unit*> friendlyList;
            target->GetFriendlyUnitListInRange(friendlyList, 40.0f);
            friendlyList.sort(Trinity::HealthPctOrderPred());

            uint32 max = 5;

            for (auto unit : friendlyList)
            {
                if (--max == 5)
                    break;

                if (target != unit)
                    target->CastSpell(unit, Jump, true);
                caster->CastSpell(unit, Heal, true);
                ++hitUnits;
            }

            std::list<Unit*> enemyList;
            target->GetAttackableUnitListInRange(enemyList, 40.0f);
            enemyList.sort(Trinity::HealthPctOrderPred());
            max = 5;

            for (auto unit : enemyList)
            {
                if (--max == 5)
                    break;

                if (target != unit)
                    target->CastSpell(unit, Jump, true);
                caster->CastSpell(unit, Dmg, true);
                ++hitUnits;
            }
        }
        else
        {
            std::list<Unit*> friendlyList;
            caster->GetFriendlyUnitListInRange(friendlyList, 40.0f);
            friendlyList.sort(Trinity::HealthPctOrderPred());

            uint32 max = 5;

            for (auto unit : friendlyList)
            {
                if (--max == 5)
                    break;

                if (target != unit)
                    target->CastSpell(unit, Jump, true);
                caster->CastSpell(unit, Heal, true);
                ++hitUnits;
            }

            std::list<Unit*> enemyList;
            caster->GetAttackableUnitListInRange(enemyList, 40.0f);
            enemyList.sort(Trinity::HealthPctOrderPred());
            max = 5;

            for (auto unit : enemyList)
            {
                if (--max == 5)
                    break;

                if (target != unit)
                    target->CastSpell(unit, Jump, true);
                caster->CastSpell(unit, Dmg, true);
                ++hitUnits;
            }
        }


        caster->CastSpell(target, VisualReturn, true); // add energize to this spellscript in the future.

        for (int i = 0; i < hitUnits; ++i)
            caster->CastSpell(caster, Energize, true);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_sha_chain_harvest::HandleDamage, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

// ID - 8512 Windfury Totem
class spell_sha_windfury_totem : public SpellScript
{
    PrepareSpellScript(spell_sha_windfury_totem);

    void HandleBeforeCast()
    {
        if (auto caster = GetCaster())
        {
            if (Creature* totem = caster->GetControlledCreature(6112))
                if (totem->ToTotem())
                {
                    if (totem->AI())
                        totem->AI()->DoAction(3);
                    totem->ToTotem()->UnSummon();
                }
        }
    }

    void Register()
    {
        BeforeCast += SpellCastFn(spell_sha_windfury_totem::HandleBeforeCast);
    }
};

struct npc_shaman_windfury_totem : public TotemAI
{
public:
    npc_shaman_windfury_totem(Creature* creature) : TotemAI(creature) { }

    GuidUnorderedSet wfUsers;

    void DoAction(int32 action) override
    {
        if (action == 3)
        {
            for (auto it = wfUsers.begin(); it != wfUsers.end(); ++it)
            {
                auto obj = ObjectAccessor::GetUnit(*me, *it);
                if (obj)
                    obj->RemoveAurasDueToSpell(327942, me->GetGUID());
            }
        }
    }

    void UpdateAI(uint32 diff) override
    {
        TotemAI::UpdateAI(diff);

        for (auto it = wfUsers.begin(); it != wfUsers.end();)
        {
            auto obj = ObjectAccessor::GetUnit(*me, *it);
            bool remove = obj == nullptr || obj->GetDistance2d(me) > 30.0f;

            if (remove)
            {
                if (obj)
                    obj->RemoveAurasDueToSpell(327942, me->GetGUID());

                it = wfUsers.erase(it);
            }
            else
            {
                ++it;

                if (!obj->HasAura(327942))
                    me->AddAura(327942, obj);
            }
        }

        if (wfUsers.size() == 5)
            return;

        if (auto owner = me->GetCharmerOrOwnerPlayerOrPlayerItself())
        {
            std::list<Unit*> friendlies;
            me->GetFriendlyUnitListInRange(friendlies, 30.0f);
            for (auto u : friendlies)
            {
                if (auto player = u->ToPlayer())
                {
                    if (player->IsInSameGroupWith(owner) && !wfUsers.count(player->GetGUID()))
                    {
                        wfUsers.insert(player->GetGUID());
                        me->AddAura(327942, player);
                    }
                }
            }
        }
    }
};

// ID - 333957 Feral Spirit
class spell_sha_feral_spirit_aura : public AuraScript
{
    PrepareAuraScript(spell_sha_feral_spirit_aura);

    void HandleDummy(AuraEffect const* /*aurEff*/)
    {
        if (auto caster = GetCaster())
            caster->CastSpell(caster, SPELL_SHAMAN_MAELSTROM_WEAPON_POWER, true);
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_sha_feral_spirit_aura::HandleDummy, EFFECT_1, SPELL_AURA_PERIODIC_DUMMY);
    }
};

// ID - 187881 Maelstrom Weapon
class spelL_sha_maelstrom_weapon_187881 : public AuraScript
{
    PrepareAuraScript(spelL_sha_maelstrom_weapon_187881);

    void HandleApply(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        if (auto caster = GetCaster())
            caster->CastSpell(caster, SPELL_SHAMAN_MAELSTROM_WEAPON_POWER_DUMMY, true);
    }

    void HandleRemove(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spelL_sha_maelstrom_weapon_187881::HandleApply, EFFECT_0, SPELL_AURA_ADD_PCT_MODIFIER, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
        OnEffectRemove += AuraEffectRemoveFn(spelL_sha_maelstrom_weapon_187881::HandleRemove, EFFECT_0, SPELL_AURA_ADD_PCT_MODIFIER, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
    }
};

// ID - 344179 Maelstrom Weapon
class spell_sha_maelstrom_weapon_proc : public AuraScript
{
    PrepareAuraScript(spell_sha_maelstrom_weapon_proc);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetSpellInfo())
            return false;

        switch (eventInfo.GetSpellInfo()->Id)
        {
            case 1064:  // - Chain Heal
            case 8004: // - Healing Surge
            case 117014: // - Elemental Blast
            case 126371: // - Deluge
            case 188160: // - Earthen Smash
            case 188196: // - Lightning Bolt
            case 188443: // - Chain Lightning
            case 191634: // - Stormkeeper
            case 204266: // - Swelling Waves
            case 206427: // - Lava Bolt
            case 211094: // - Chain Lightning(PvP Talent)
            case 214815: // - Lightning Bolt
            case 214816: // - Lightning Bolt Overload
            case 320137: // - Stormkeeper
            case 320674: // - Chain Harvest(Venthyr)
            case 326059: // - Primordial Wave(Necrolord)
            case 350247: // - Stormkeeper
                return true;
            default:
                return false;
        }
    }

    void HandleProc(AuraEffect* /*aurEff*/, ProcEventInfo& /*eventInfo*/)
    {
        if (Unit* caster = GetCaster())
        {
            caster->RemoveAurasDueToSpell(SPELL_SHAMAN_MAELSTROM_WEAPON_POWER);
            if (auto aur = caster->GetAura(SPELL_SHAMAN_MAELSTROM_WEAPON_POWER_DUMMY))
            {
                int32 stacks = std::min(5, (int32)aur->GetStackAmount());
                aur->ModStackAmount(-stacks);
            }
        }
    }

    void HandleRemove(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        if (Unit* caster = GetCaster())
        {
            caster->RemoveAurasDueToSpell(SPELL_SHAMAN_MAELSTROM_WEAPON_POWER);
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_sha_maelstrom_weapon_proc::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_sha_maelstrom_weapon_proc::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
        OnEffectRemove += AuraEffectRemoveFn(spell_sha_maelstrom_weapon_proc::HandleRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

/// ID - 342240 Ice Strike
class spell_sha_ice_strike : public SpellScript
{
    PrepareSpellScript(spell_sha_ice_strike);

    void HandleDamage(SpellEffIndex eff)
    {
        if (auto caster = GetCaster())
        {
            caster->GetSpellHistory()->ResetCooldown(SPELL_SHAMAN_FLAME_SHOCK);
            caster->GetSpellHistory()->ResetCooldown(SPELL_SHAMAN_FROST_SHOCK);
        }
    }

    void Register()
    {
        OnEffectHitTarget += SpellEffectFn(spell_sha_ice_strike::HandleDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

/// ID - 333974 Fire Nova
class spell_sha_fire_nova_enhance : public SpellScript
{
    PrepareSpellScript(spell_sha_fire_nova_enhance);

    enum FireNova
    {
        FireNovaDmg = 333977,
    };

    void HandleDamage(SpellEffIndex eff)
    {
        if (auto caster = GetCaster())
        {
            std::list<Unit*> targets;
            if (!targets.empty())
            {
                caster->GetAttackableUnitListInRange(targets, 40.0f);
                targets.sort(Trinity::ObjectDistanceOrderPred(caster));
                Trinity::Containers::RandomResize(targets, 6);

                for (auto targ : targets)
                {
                    caster->CastSpell(targ, FireNovaDmg, true);
                }
            }
        }
    }

    void Register()
    {
        OnEffectHitTarget += SpellEffectFn(spell_sha_fire_nova_enhance::HandleDamage, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

void AddSC_shaman_spell_scripts()
{
    new shaman_playerscript();
    new at_sha_earthquake_totem();
    new at_sha_ancestral_protection_totem();
    RegisterAreaTriggerAI(at_earthen_shield_totem);
    RegisterSpellScript(spell_sha_ancestral_guidance);
    new spell_sha_ancestral_guidance_heal();
    new spell_sha_ancestral_protection_totem_aura();
    new spell_sha_ascendance_water();
    new spell_sha_ascendance_water_heal();
    new spell_sha_bloodlust();
    new spell_sha_chain_heal();
    RegisterSpellScript(spell_sha_cloudburst);
    RegisterSpellScript(spell_sha_cloudburst_effect);
    RegisterSpellScript(spell_sha_cloudburst_totem_recall);
    new spell_sha_crash_lightning();
    new spell_sha_crash_lightning_aura();
    new spell_sha_earth_shield();
    new spell_sha_earthen_shield_absorb();
    new spell_sha_earthen_rage_passive();
    new spell_sha_earthen_rage_proc_aura();
    RegisterSpellScript(aura_sha_earthquake);
    RegisterSpellScript(spell_sha_earthquake_tick);
    RegisterSpellScript(spell_sha_elemental_blast);
    new spell_sha_feral_lunge();
    new spell_sha_feral_spirit();
    new spell_sha_fire_nova();
    RegisterSpellScript(spell_sha_flametongue);
    new spell_sha_fulmination();
    new spell_sha_fury_of_air();
    new spell_sha_glyph_of_healing_wave();
    new spell_sha_glyph_of_lakestrider();
    new spell_sha_healing_stream();
    new spell_sha_healing_stream_totem();
    new spell_sha_healing_stream_totem_heal();
    new spell_sha_heroism();
    new spell_sha_item_lightning_shield();
    new spell_sha_item_lightning_shield_trigger();
    new spell_sha_item_mana_surge();
    new spell_sha_item_t10_elemental_2p_bonus();
    new spell_sha_item_t18_elemental_4p_bonus();
    new spell_sha_lava_burst();
    new spell_sha_lava_lash_spread_flame_shock();
    RegisterSpellScript(spell_sha_lava_surge);
    RegisterSpellScript(spell_sha_lava_surge_proc);
    new spell_sha_lightning_bolt_elem();
    new spell_sha_lightning_shield();
    new spell_sha_liquid_magma_effect();
    RegisterSpellScript(spell_sha_maelstrom_weapon);
    new spell_sha_nature_guardian();
    new spell_sha_path_of_flames_spread();
    new spell_sha_resonance_effect();
    new spell_sha_resurgence();
    RegisterSpellScript(spell_sha_spirit_link);
    new spell_sha_spiritwalkers_grace();
    RegisterSpellScript(spell_sha_stormbringer);
    new spell_sha_thunderstorm();
    RegisterSpellScript(spell_sha_tidal_waves);
    new spell_sha_totem_mastery();
    new spell_sha_wellspring();
    new spell_shaman_windfury_weapon();
    RegisterSpellScript(spell_sha_undulation);
    RegisterSpellScript(spell_sha_chain_lightning);
    RegisterSpellAndAuraScriptPair(spell_sha_rainfall, aura_sha_rainfall);
    RegisterSpellAndAuraScriptPair(spell_sha_healing_rain, aura_sha_healing_rain);
    RegisterSpellScript(spell_sha_healing_surge);
    RegisterSpellScript(spell_sha_earth_shock);
    RegisterSpellScript(spell_sha_earth_elemental);
    RegisterSpellScript(spell_sha_fire_elemental);
    RegisterSpellScript(spell_sha_enhancement_lightning_bolt);
    RegisterSpellScript(aura_sha_stormlash);
    RegisterSpellScript(aura_sha_stormlash_buff);
    RegisterAreaTriggerAI(at_sha_crashing_storm);
    RegisterCreatureAI(npc_feral_spirit);
    RegisterAreaTriggerAI(at_sha_voodoo_totem);
    RegisterSpellScript(aura_sha_undulation_proc);
    RegisterSpellScript(aura_sha_master_of_the_elements);
    RegisterSpellAndAuraScriptPair(spell_sha_icefury, aura_sha_icefury);
    RegisterSpellScript(spell_sha_frost_shock);
    RegisterSpellScript(spell_sha_overload_spells);
    RegisterSpellScript(aura_sha_unlimited_power);
    RegisterSpellScript(aura_sha_ghost_wolf);
    RegisterSpellScript(aura_sha_spirit_wolf);
    RegisterSpellScript(aura_shaman_tidal_waves_buff);
    RegisterSpellScript(spell_sha_flametongue_attack);
    RegisterSpellScript(aura_sha_hot_hand);
    RegisterSpellScript(spell_sha_stormstrike);
    RegisterSpellAndAuraScriptPair(spell_lightning_shield, aura_lightning_shield);
    RegisterSpellScript(aura_sha_landslide);
    RegisterSpellScript(aura_sha_landslide_aura);
    RegisterSpellScript(aura_sha_static_charge);
    RegisterSpellScript(aura_sha_exposed_elements);
    RegisterSpellScript(aura_sha_flame_shock_aura);
    RegisterSpellScript(aura_sha_spectral_recovery);
    RegisterSpellScript(aura_sha_control_of_lava);
    RegisterSpellScript(aura_sha_control_of_lava_proc);
    RegisterAreaTriggerAI(at_counterstrike_totem);
    RegisterSpellScript(aura_sha_counterstrike_totem);
    RegisterSpellScript(aura_sha_riptide);
    RegisterSpellScript(spell_sha_forked_lightning);
    RegisterSpellScript(aura_sha_searing_assault);
    RegisterSpellScript(aura_sha_ride_the_lightning);
    RegisterSpellScript(spell_sha_purge);
    RegisterSpellScript(aura_sha_hex);
    RegisterSpellScript(aura_sha_molten_weapon);
    RegisterSpellScript(aura_sha_icy_edge);
    RegisterSpellScript(aura_healing_surge_bonus);
    RegisterSpellScript(aura_static_cling);
    RegisterSpellScript(aura_static_cling_target);
    RegisterSpellScript(spell_sha_storm_elemental);
    RegisterSpellScript(aura_sha_storm_elemental_buff);
    RegisterSpellScript(spell_sha_eye_of_the_storm_damage);
    RegisterSpellAndAuraScriptPair(spell_sha_earthgrab, aura_warl_earthgrab);
    RegisterSpellScript(aura_shaman_calming_waters);
    RegisterSpellScript(aura_shaman_calming_waters_buff);
    RegisterSpellScript(aura_sha_hot_hand_aura);
    RegisterSpellScript(spell_aura_shamanism);
    RegisterSpellScript(aura_sha_stormbringer);
    RegisterSpellScript(aura_sha_malestrom_controller);
    RegisterSpellScript(aura_sha_stormkeeper);
    RegisterSpellScript(aura_sha_aftershock);
    RegisterSpellScript(spell_sha_stormstrike_main);
    RegisterSpellScript(spell_sha_spirit_link_pvp_aura);
    RegisterSpellScript(spell_sha_lava_lash);
    RegisterSpellScript(spell_sha_downpour);
    RegisterSpellScript(spell_sha_thunderstorm_ally);
    RegisterSpellScript(spell_sha_spirit_link_totem);
    RegisterAreaTriggerAI(at_sha_skyfury);
    RegisterSpellScript(spell_sha_windfury_weapon);
    RegisterSpellScript(spell_sha_windfury_weapon_proc);
    RegisterSpellScript(spell_sha_flametongue_weapon);
    RegisterSpellScript(spell_sha_flametongue_weapon_aura);
    RegisterSpellScript(spell_sha_chain_harvest);
    RegisterSpellScript(spell_sha_windfury_totem);
    RegisterSpellScript(spell_sha_feral_spirit_aura);
    RegisterSpellScript(spelL_sha_maelstrom_weapon_187881);
    RegisterSpellScript(spell_sha_maelstrom_weapon_proc);
    RegisterSpellScript(spell_sha_ice_strike);
    RegisterSpellScript(spell_sha_fire_nova_enhance);

    RegisterCreatureAI(npc_ancestral_protection_totem);
    RegisterCreatureAI(npc_cloudburst_totem);
    RegisterCreatureAI(npc_earth_grab_totem);
    RegisterCreatureAI(npc_earthen_shield_totem);
    RegisterCreatureAI(npc_ember_totem);
    RegisterCreatureAI(npc_grounding_totem);
    RegisterCreatureAI(npc_healing_tide_totem);
    RegisterCreatureAI(npc_lightning_surge_totem);
    RegisterCreatureAI(npc_liquid_magma_totem);
    RegisterCreatureAI(npc_resonance_totem);
    RegisterCreatureAI(npc_skyfury_totem);
    RegisterCreatureAI(npc_tailwind_totem);
    RegisterCreatureAI(npc_storm_totem);
    RegisterCreatureAI(npc_voodoo_totem);
    RegisterCreatureAI(npc_wind_rush_totem);
    RegisterCreatureAI(npc_storm_totem_encha);
    RegisterCreatureAI(npc_resonance_totem_encha);
    RegisterCreatureAI(npc_tailwind_totem_encha);
    RegisterCreatureAI(npc_ember_totem_encha);
    RegisterCreatureAI(npc_tremor_totem);
    RegisterCreatureAI(npc_counterstrike_totem);
    RegisterCreatureAI(npc_earthbind_totem);
    RegisterCreatureAI(npc_greater_storm_elemental);
    RegisterCreatureAI(npc_shaman_windfury_totem);
}
