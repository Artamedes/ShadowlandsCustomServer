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
* Scripts for spells with SPELLFAMILY_WARLOCK and SPELLFAMILY_GENERIC spells used by warlock players.
* Ordered alphabetically using scriptname.
* Scriptnames of files in this file should be prefixed with "spell_warl_".
*/

#include "spell_warlock.h"

enum WarlockSpells
{
    SPELL_WARLOCK_ABSOLUTE_CORRUPTION               = 196103,
    SPELL_WARLOCK_AFTERMATH_STUN                    = 85387,
    SPELL_WARLOCK_AGONY                             = 980,
    SPELL_WARLOCK_AGONY_ENERGIZE                    = 17941,
    SPELL_WARLOCK_ARCHIMONDES_VENGEANCE_COOLDOWN    = 116405,
    SPELL_WARLOCK_ARCHIMONDES_VENGEANCE_DAMAGE      = 124051,
    SPELL_WARLOCK_ARCHIMONDES_VENGEANCE_PASSIVE     = 116403,
    SPELL_WARLOCK_BACKDRAFT                         = 117828,
    SPELL_WARLOCK_BACKDRAFT_AURA                    = 196406,
    SPELL_WARLOCK_BANE_OF_DOOM_EFFECT               = 18662,
    SPELL_WARLOCK_BURNING_RUSH                      = 111400,
    SPELL_WARLOCK_CALL_DREADSTALKERS                = 104316,
    SPELL_WARLOCK_CALL_DREADSTALKERS_SUMMON         = 193331,
    SPELL_WARLOCK_CHANNEL_DEMONFIRE_ACTIVATOR       = 228312,
    SPELL_WARLOCK_CHANNEL_DEMONFIRE_DAMAGE          = 196448,
    SPELL_WARLOCK_CONFLAGRATE                       = 17962,
    SPELL_WARLOCK_ROARING_BLAZE_DOT                 = 265931,
    SPELL_WARLOCK_CONFLAGRATE_FIRE_AND_BRIMSTONE    = 108685,
    SPELL_WARLOCK_CORRUPTION                        = 172,
    SPELL_WARLOCK_CORRUPTION_DAMAGE                 = 146739,
    SPELL_WARLOCK_CREATE_HEALTHSTONE                = 23517,
    SPELL_WARLOCK_CURSE_OF_DOOM_EFFECT              = 18662,
    SPELL_WARLOCK_DARK_BARGAIN_DOT                  = 110914,
    SPELL_WARLOCK_DARKGLARE_EYE_BEAM                = 205231,
    SPELL_WARLOCK_DARKGLARE_SUMMON                  = 205180,
    SPELL_WARLOCK_DARK_REGENERATION                 = 108359,
    SPELL_WARLOCK_DARK_SOUL_INSTABILITY             = 113858,
    SPELL_WARLOCK_DARK_SOUL_KNOWLEDGE               = 113861,
    SPELL_WARLOCK_DARK_SOUL_MISERY                  = 113860,
    SPELL_WARLOCK_DECIMATE_AURA                     = 108869,
    SPELL_WARLOCK_DEMON_SOUL_FELGUARD               = 79452,
    SPELL_WARLOCK_DEMON_SOUL_FELHUNTER              = 79460,
    SPELL_WARLOCK_DEMON_SOUL_IMP                    = 79459,
    SPELL_WARLOCK_DEMON_SOUL_SUCCUBUS               = 79453,
    SPELL_WARLOCK_DEMON_SOUL_VOIDWALKER             = 79454,
    SPELL_WARLOCK_DEMONBOLT                         = 264178,
    SPELL_WARLOCK_DEMONBOLT_ENERGIZE                = 280127,
    SPELL_WARLOCK_DEMONIC_CALL                      = 114925,
    SPELL_WARLOCK_DEMONIC_CALLING                   = 205145,
    SPELL_WARLOCK_DEMONIC_CALLING_TRIGGER           = 205146,
    SPELL_WARLOCK_DEMONIC_CIRCLE_ALLOW_CAST         = 62388,
    SPELL_WARLOCK_DEMONIC_CIRCLE_SUMMON             = 48018,
    SPELL_WARLOCK_DEMONIC_CIRCLE_TELEPORT           = 48020,
    SPELL_WARLOCK_DEMONIC_EMPOWERMENT_FELGUARD      = 54508,
    SPELL_WARLOCK_DEMONIC_EMPOWERMENT_FELHUNTER     = 54509,
    SPELL_WARLOCK_DEMONIC_EMPOWERMENT_IMP           = 54444,
    SPELL_WARLOCK_DEMONIC_EMPOWERMENT_SUCCUBUS      = 54435,
    SPELL_WARLOCK_DEMONIC_EMPOWERMENT_VOIDWALKER    = 54443,
    SPELL_WARLOCK_DEMONIC_GATEWAY_PERIODIC_CHARGE   = 113901,
    SPELL_WARLOCK_DEMONIC_GATEWAY_SUMMON_GREEN      = 113886,
    SPELL_WARLOCK_DEMONIC_GATEWAY_SUMMON_PURPLE     = 113890,
    SPELL_WARLOCK_DEMONIC_GATEWAY_TELEPORT_GREEN    = 113896,
    SPELL_WARLOCK_DEMONIC_GATEWAY_TELEPORT_PURPLE   = 120729,
    SPELL_WARLOCK_DEMONIC_LEAP_JUMP                 = 109163,
    SPELL_WARLOCK_DEMONOLOGY_WARLOCK                = 137044,
    SPELL_WARLOCK_DEMONSKIN                         = 219272,
    SPELL_WARLOCK_DESTRUCTION_PASSIVE               = 137046,
    SPELL_WARLOCK_DEVOUR_MAGIC_HEAL                 = 19658,
    SPELL_WARLOCK_DISRUPTED_NETHER                  = 114736,
    SPELL_WARLOCK_DOOM                              = 265412,
    SPELL_WARLOCK_DOOM_SOUL_SHARD                   = 272728,
    SPELL_WARLOCK_DRAIN_SOUL_ENERGIZE               = 205292,
    SPELL_WARLOCK_DRAIN_LIFE_HEAL                   = 234153,
    SPELL_WARLOCK_ERADICATION                       = 196412,
    SPELL_WARLOCK_ERADICATION_DEBUFF                = 196414,
    SPELL_WARLOCK_EYE_LASER                         = 205231,
    SPELL_WARLOCK_FEAR                              = 5782,
    SPELL_WARLOCK_FEAR_BUFF                         = 118699,
    SPELL_WARLOCK_FEAR_EFFECT                       = 118699,
    SPELL_WARLOCK_FEL_FIREBOLT                      = 104318,
    SPELL_WARLOCK_FEL_SYNERGY_HEAL                  = 54181,
    SPELL_WARLOCK_FIRE_AND_BRIMSTONE                = 196408,
    SPELL_WARLOCK_GLYPH_OF_CONFLAGRATE              = 56235,
    SPELL_WARLOCK_GLYPH_OF_DEMON_TRAINING           = 56249,
    SPELL_WARLOCK_GLYPH_OF_FEAR                     = 56244,
    SPELL_WARLOCK_GLYPH_OF_FEAR_EFFECT              = 130616,
    SPELL_WARLOCK_GLYPH_OF_SHADOWFLAME              = 63311,
    SPELL_WARLOCK_SIPHON_LIFE                       = 63106,
    SPELL_WARLOCK_GLYPH_OF_SOULWELL                 = 58094,
    SPELL_WARLOCK_GLYPH_OF_SOULWELL_VISUAL          = 34145,
    SPELL_WARLOCK_GRIMOIRE_FELGUARD                 = 111898,
    SPELL_WARLOCK_GRIMOIRE_FELHUNTER                = 111897,
    SPELL_WARLOCK_GRIMOIRE_IMP                      = 111859,
    SPELL_WARLOCK_GRIMOIRE_OF_SYNERGY_BUFF          = 171982,
    SPELL_WARLOCK_GRIMOIRE_SUCCUBUS                 = 111896,
    SPELL_WARLOCK_GRIMOIRE_VOIDWALKER               = 111895,
    SPELL_WARLOCK_HAND_OF_DOOM                      = 196283,
    SPELL_WARLOCK_HAND_OF_GULDAN_DAMAGE             = 86040,
    SPELL_WARLOCK_HAND_OF_GULDAN_SUMMON             = 279910,
    SPELL_WARLOCK_HARVEST_LIFE_HEAL                 = 125314,
    SPELL_WARLOCK_HAUNT                             = 48181,
    SPELL_WARLOCK_HAVOC                             = 80240,
    SPELL_WARLOCK_HEALTH_FUNNEL_HEAL                = 217979,
    SPELL_WARLOCK_IMMOLATE                          = 348,
    SPELL_WARLOCK_IMMOLATE_DOT                      = 157736,
    SPELL_WARLOCK_IMMOLATE_FIRE_AND_BRIMSTONE       = 108686,
    SPELL_WARLOCK_IMMOLATE_PROC                     = 193541,
    SPELL_WARLOCK_IMMOLATE_ENERGIZE                 = 193540,
    SPELL_WARLOCK_IMPENDING_DOOM                    = 196270,
    SPELL_WARLOCK_IMPENDING_DOOM_SUMMON             = 196271,
    SPELL_WARLOCK_IMPLOSION_DAMAGE                  = 196278,
    SPELL_WARLOCK_IMPLOSION_JUMP                    = 205205,
    SPELL_WARLOCK_IMPROVED_DREADSTALKERS            = 196272,
    SPELL_WARLOCK_IMPROVED_SOUL_FIRE_PCT            = 85383,
    SPELL_WARLOCK_IMPROVED_SOUL_FIRE_STATE          = 85385,
    SPELL_WARLOCK_INCINERATE                        = 29722,
    SPELL_WARLOCK_INCINERATE_ENERGIZE               = 244670,
    SPELL_WARLOCK_ITEM_S12_TIER_4                   = 131632,
    SPELL_WARLOCK_KIL_JAEDENS_CUNNING_PASSIVE       = 108507,
    SPELL_WARLOCK_LIFE_TAP_ENERGIZE                 = 31818,
    SPELL_WARLOCK_LIFE_TAP_ENERGIZE_2               = 32553,
    SPELL_WARLOCK_METAMORPHOSIS                     = 103958,
    SPELL_WARLOCK_MOLTEN_CORE                       = 122355,
    SPELL_WARLOCK_MOLTEN_CORE_AURA                  = 122351,
    SPELL_WARLOCK_NETHER_TALENT                     = 91713,
    SPELL_WARLOCK_NETHER_WARD                       = 91711,
    SPELL_WARLOCK_NIGHTFALL                         = 108558,
    SPELL_WARLOCK_PHANTOMATIC_SINGULARITY           = 205179,
    SPELL_WARLOCK_PHANTOMATIC_SINGULARITY_DAMAGE    = 205246,
    SPELL_WARLOCK_POWER_TRIP                        = 196605,
    SPELL_WARLOCK_POWER_TRIP_ENERGIZE               = 216125,
    SPELL_WARLOCK_PYROCLASM                         = 123686,
    SPELL_WARLOCK_RAIN_OF_FIRE_DAMAGE               = 42223,
    SPELL_WARLOCK_ROARING_BLAZE                     = 205184,
    SPELL_WARLOCK_CONFLAGRATE_ENERGIZE              = 245330,
    SPELL_WARLOCK_SEED_OF_CURRUPTION                = 27243,
    SPELL_WARLOCK_SEED_OF_CURRUPTION_DAMAGE         = 27285,
    SPELL_WARLOCK_SHADOW_BOLT                       = 686,
    SPELL_WARLOCK_SHADOW_BOLT_SHOULSHARD            = 194192,
    SPELL_WARLOCK_SHADOW_EMBRACE                    = 32388,
    SPELL_WARLOCK_SHADOW_EMBRACE_BUFF               = 32390,
    SPELL_WARLOCK_SHADOW_TRANCE                     = 17941,
    SPELL_WARLOCK_SHADOW_WARD                       = 6229,
    SPELL_WARLOCK_SHADOWFLAME                       = 47960,
    SPELL_WARLOCK_SHADOWY_INSPIRATION               = 196269,
    SPELL_WARLOCK_SHADOWY_INSPIRATION_EFFECT        = 196606,
    SPELL_WARLOCK_SHIELD_OF_SHADOW                  = 115232,
    SPELL_WARLOCK_SIPHON_LIFE_HEAL                  = 63106,
    SPELL_WARLOCK_SOUL_LEECH                        = 228974,
    SPELL_WARLOCK_SOUL_LEECH_ABSORB                 = 108366,
    SPELL_WARLOCK_SOUL_LEECH_AURA                   = 108370,
    SPELL_WARLOCK_SOUL_LINK_DUMMY_AURA              = 108446,
    SPELL_WARLOCK_SOUL_SWAP_AURA                    = 86211,
    SPELL_WARLOCK_SOUL_SWAP_CD_MARKER               = 94229,
    SPELL_WARLOCK_SOUL_SWAP_DOT_MARKER              = 92795,
    SPELL_WARLOCK_SOUL_SWAP_MOD_COST                = 92794,
    SPELL_WARLOCK_SOUL_SWAP_OVERRIDE                = 86211,
    SPELL_WARLOCK_SOUL_SWAP_VISUAL                  = 92795,
    SPELL_WARLOCK_SOULWELL_CREATE_HEALTHSTONE       = 34130,
    SPELL_WARLOCK_SOW_THE_SEEDS                     = 196226,
    SPELL_WARLOCK_SPAWN_PURPLE_DEMONIC_GATEWAY      = 113890,
    SPELL_WARLOCK_SUMMON_DREADSTALKER               = 193332,
    SPELL_WARLOCK_DOOM_SUMMON_DOOMGUARD             = 280365,
    SPELL_WARLOCK_THREATENING_PRESENCE              = 112042,
    SPELL_WARLOCK_TWILIGHT_WARD_METAMORPHOSIS_S12   = 131624,
    SPELL_WARLOCK_TWILIGHT_WARD_S12                 = 131623,
    SPELL_WARLOCK_UNSTABLE_AFFLICTION               = 30108,
    SPELL_WARLOCK_UNSTABLE_AFFLICTION_DAMAGE_1      = 233490,
    SPELL_WARLOCK_UNSTABLE_AFFLICTION_DAMAGE_2      = 233496,
    SPELL_WARLOCK_UNSTABLE_AFFLICTION_DAMAGE_3      = 233497,
    SPELL_WARLOCK_UNSTABLE_AFFLICTION_DAMAGE_4      = 233498,
    SPELL_WARLOCK_UNSTABLE_AFFLICTION_DAMAGE_5      = 233499,
    SPELL_WARLOCK_UNSTABLE_AFFLICTION_DISPEL        = 196364,
    SPELL_WARLOCK_WRITHE_IN_AGONY                   = 196102,
    SPELL_WARLOCK_UNSTABLE_AFFLICTION_ENERGIZE      = 31117,
    SPELL_WARLOCK_HAND_OF_GULDAN_PROJECTILE         = 270215,
	SPELL_WARLOCK_DEMONFIRE							= 270481,
    SPELL_WARLOCK_DEMONIC_POWER                     = 265273,
    SPELL_WARLOCK_DEMONIC_CORE                      = 267102,
    SPELL_WARLOCK_DEMONIC_CORE_PET                  = 270171,
    SPELL_WARLOCK_DEMONIC_CORE_BUFF                 = 264173,
    SPELL_WARLOCK_SOUL_STRIKE_DAMAGE                = 267964,
    SPELL_WARLOCK_SOUL_STRIKE_ENERGIZE              = 270557,
    SPELL_WARLOCK_SACRIFICED_SOULS                  = 267214,
    SPELL_WARLOCK_SACRIFICED_SOULS_AURA             = 272591,
    SPELL_WARLOCK_NIGHTFALL_PROC                    = 264571,
    SPELL_WARLOCK_SHADOW_BOLT_AFFLI                 = 232670,
	SPELL_WARLOCK_FROM_THE_SHADOWS					= 267170,
    SPELL_WARLOCK_SHADOWBURN_ENERGIZE               = 245731,
    SPELL_WARLOCK_SHADOWBURN                        = 17877,
    SPELL_WARLOCK_CASTING_CIRCLE_AURA               = 221705,
	SPELL_WARLOCK_FROM_THE_SHADOWS_AURA				= 270569,
    SPELL_WARLOCK_DREADLASH                         = 264078,
    SPELL_WARLOCK_FELGUARD_CHARGE                   = 30151,
    SPELL_WARLOCK_FELGUARD_FELSTORM                 = 89751,
    SPELL_WARLOCK_DEMONIC_STRENGTH                  = 267171,
    SPELL_WARLOCK_SOUL_LINK_WARLOCK                 = 108415,
	SPELL_WARLOCK_SOUL_LINK_HEAL                    = 108447,
    SPELL_WARLOCK_INNER_DEMONS                      = 267216,
    SPELL_WARLOCK_BILESCOURGE_BOMBERS_START         = 282248,
    SPELL_WARLOCK_BILESCOURGE_BOMBERS_FINISH        = 267211,
    SPELL_WARLOCK_BILESCOURGE_MISSILE               = 267212,
    SPELL_WARLOCK_NETHER_PORTAL_AURA                = 267218,
	SPELL_WARLOCK_SOUL_CONDUIT                      = 215941,
	SPELL_WARLOCK_SOUL_CONDUIT_ENERGIZE             = 215942,
	SPELL_WARLOCK_FLASHOVER							= 267115,
	SPELL_WARLOCK_CHAOS_BOLT						= 116858,
	SPELL_WARLOCK_SOUL_FIRE							= 6353,
	SPELL_WARLOCK_SOUL_FIRE_ENERGIZE				= 281490,
	SPELL_WARLOCK_INTERNAL_COMBUSTION				= 266134,
	SPELL_WARLOCK_INTERNAL_COMBUSTION_DAMAGE		= 266136,
	SPELL_WARLOCK_INFERNO							= 270545,
	SPELL_WARLOCK_GRIMOIRE_OF_SUPREMACY				= 266086,
	SPELL_WARLOCK_GRIMOIRE_OF_SUPREMACY_BUFF		= 266091,
	SPELL_WARLOCK_DEATHBOLT							= 264106,
	SPELL_WARLOCK_DRAIN_SOUL						= 198590,
    SPELL_WARLOCK_FEL_FISSURE_EFFECT                = 200587,
    SPELL_WARLOCK_BANE_OF_HAVOC_TALENT              = 200546,
    SPELL_WARLOCK_BANE_OF_HAVOC                     = 200548,
    SPELL_WARLOCK_ESSENCE_DRAIN                     = 221715,
    SPELL_WARLOCK_CURSE_OF_THE_SHADOW               = 234877,
    SPELL_WARLOCK_CURSE_OF_THE_SHADOW_DAMAGE        = 236615,
    SPELL_WARLOCK_OBSERVER_AURA                     = 212580,
    SPELL_WARLOCK_LASERBEAM                         = 212529,
	SPELL_WARLOCK_CHANNEL_DEMONFIRE					= 281362,
	SPELL_WARLOCK_ROT_AND_DECAY						= 212371,
	SPELL_WARLOCK_SOULSHATTER						= 212356,
	SPELL_WARLOCK_SOULSHATTER_ENERGIZE				= 212921,
	SPELL_WARLOCK_SOULSHATTER_HASTE					= 236471,
    SPELL_WARLOCK_FOCUSED_CHAOS                     = 233577,
	SPELL_WARLOCK_DEMONIC_CONSUMPTION				= 267215,
	SPELL_WARLOCK_DEMONIC_CONSUMPTION_BUFF			= 267972,
    SPELL_WARLOCK_GRIMOIRE_OF_SACRIFICE             = 196099,
    SPELL_WARLOCK_SOULSTONE_RANK2                   = 231811,
    SPELL_WARLOCK_SOULSTONE_RESURRECTION            = 95750,
    SPELL_WARLOCK_DOOM_DAMAGE                       = 265469,
    SPELL_WARLOCK_DOOM_BOLT                         = 85692,
    SPELL_WARLOCK_WRACKING_BRILLIANCE_POWER         = 272891,
    SPELL_WARLOCK_WRACKING_BRILLIANCE_BUFF          = 272893,
    SPELL_WARLOCK_CHAOTIC_INFERNO_POWER             = 278748,
    SPELL_WARLOCK_CHAOTIC_INFERNO_PROC              = 279673,
    SPELL_WARLOCK_SUPREME_COMMANDER                 = 279878,
    SPELL_WARLOCK_SUPREME_COMMANDER_BUFF            = 279885,
    SPELL_WARLOCK_DEMONIC_METEOR                    = 278737,
    SPELL_WARLOCK_CRASHING_CHAOS                    = 277644,
    SPELL_WARLOCK_CRASHING_CHAOS_BUFF               = 277706,
    SPELL_WARLOCK_SHADOWS_BITE_POWER                = 272944,
    SPELL_WARLOCK_SHADOWS_BITE_BUFF                 = 272945,
    SPELL_WARLOCK_GATEWAY_MASTERY                   = 248855,
    SPELL_WARLOCK_UNSTABLE_AFLICTION_CONTAGION      = 233494,
    SPELL_WARLOCK_FLASHPOINT_POWER                  = 275425,
    SPELL_WARLOCK_FLASHPOINT_BUFF                   = 275429,
    SPELL_WARLOCK_SUDDEN_ONSET                      = 278721,
    SPELL_WARLOCK_ACCELERANT_POWER                  = 272955,
    SPELL_WARLOCK_ACCELERANT_BUFF                   = 272957,
    SPELL_WARLOCK_ROLLING_HAVOC_POWER               = 278747,
    SPELL_WARLOCK_ROLLING_HAVOC_BUFF                = 278931,
    SPELL_WARLOCK_DREADFUL_CALLING                  = 278727,
};

enum WarlockSpellIcons
{
    WARLOCK_ICON_ID_IMPROVED_LIFE_TAP   = 208,
    WARLOCK_ICON_ID_MANA_FEED           = 1982
};

enum MiscSpells
{
    SPELL_GEN_REPLENISHMENT         = 57669,
    SPELL_PRIEST_SHADOW_WORD_DEATH  = 32409
};

enum eGatewaySpells
{
    PortalVisual            = 113900,
    GatewayInteract         = 113902,
    CooldownMarker          = 113942,
    TeleportVisualGreen     = 236762,
    TeleportVisualPurple    = 236671
};

enum eGatewayNpc
{
    GreenGate   = 59262,
    PurpleGate  = 59271
};

struct InnerDemonPoolEntry
{
public:
    InnerDemonPoolEntry(uint32 entry, uint8 amount, float chance) { Entry = entry; Amount = amount; Chance = chance; }
    InnerDemonPoolEntry() { }

    uint32 Entry;
    uint8 Amount;
    float Chance;
};

struct WarlockGlobalVariables
{
    // PIGPIGPIG
    // Variables
    ObjectGuid ExplicitTarget;
    Position LastPosition;
    float LastOrientation = 0.0f;
    uint8 WildImpCount = 0;
    Position positions[16];
    Position innerDemonPositions[8];
    bool WildImpSlots[16] = { false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false };
    bool InnerLeft = false;
    Position LastPositionInner;
    float LastOrientationInner = 0.0f;

    // Slots for InnerDemons
    // EOG   - Eyes of Guldan
    // B     - Bilescourges
    // Other demons spwans directly next to the target
    // ------------------------------------------------------------------------------------------------
    //                           EOG    EOG    EOG    EOG    EOG     B      B      B 
    // ------------------------------------------------------------------------------------------------
    bool InnerDemonsSlots[8] = { false, false, false, false, false, false, false, false };
    uint8 souldShards = 1;

    // Inner Demons pool
    InnerDemonPoolEntry InnerDemonsPool[10];
    uint32 checkTimer = 0;
};

std::unordered_map<ObjectGuid::LowType, WarlockGlobalVariables> m_WarlockGuidMap;


WarlockGlobalVariables* GetVariables(Unit* caster)
{
    auto itr = m_WarlockGuidMap.find(caster->GetGUID().GetCounter());
    if (itr == m_WarlockGuidMap.end())
    {
        WarlockGlobalVariables newVars;
        m_WarlockGuidMap[caster->GetGUID().GetCounter()] = newVars;
        itr = m_WarlockGuidMap.find(caster->GetGUID().GetCounter()); // refind should be there now
    }

    return &itr->second;
}

class warlock_playerscript : public PlayerScript
{
public:
    warlock_playerscript() : PlayerScript("warlock_playerscript") {}

    void OnLogout(Player* player) override
    {
        auto guidLow = player->GetGUID().GetCounter();
        if (m_WarlockGuidMap.count(guidLow))
            m_WarlockGuidMap.erase(guidLow);
    }

	void OnModifyPower(Player* player, Powers power, int32 oldValue, int32& newValue, bool regen, bool after) override
	{ 
		if (!player || regen || after)
			return;

		// Destro Warlock
		if (player->GetSpecializationId() == TALENT_SPEC_WARLOCK_DESTRUCTION)
		{
			// Soul Fire
			if (player->HasSpell(SPELL_WARLOCK_SOUL_FIRE) && power == POWER_SOUL_SHARDS && newValue < oldValue)
			{
				uint8 shards = std::floor((oldValue - newValue) / 10);
				player->GetSpellHistory()->ModifyCooldown(SPELL_WARLOCK_SOUL_FIRE, -sSpellMgr->GetSpellInfo(SPELL_WARLOCK_SOUL_FIRE)->GetEffect(EFFECT_1).BasePoints * shards);
			}

            if (player->HasAura(SPELL_WARLOCK_GRIMOIRE_OF_SUPREMACY) && power == POWER_SOUL_SHARDS && newValue < oldValue && player->GetSummonedCreatureByEntry(89))
            {
                uint8 stacks = 0;
                if (Aura* aura = player->GetAura(SPELL_WARLOCK_GRIMOIRE_OF_SUPREMACY_BUFF))
                    stacks = aura->GetStackAmount();
                player->Variables.Set<uint8>("GRIMOIRE_OF_SUPREMACY_STACK", (oldValue - newValue) / 10 + stacks);
            }
		}
	}

    void OnSummonCreatureDealsDamage(Player* player, Unit* creature, Unit* victim, int32 damage) override
    {
        if (!player || !creature || !victim || damage <= 0)
            return;

        if (creature->GetCreatureType() != CREATURE_TYPE_DEMON)
            return;

        if (Aura* aura = player->GetAura(SPELL_WARLOCK_SOUL_LEECH_AURA))
        {
            int32 basePoints = aura->GetEffect(EFFECT_0)->GetAmount();
            int32 absorb = CalculatePct(damage, basePoints);

            int32 absorbCaster = 0;
            int32 absorbPet = 0;

            // Add remaining amount if already applied
            if (Aura* aur = player->GetAura(SPELL_WARLOCK_SOUL_LEECH_ABSORB))
                if (AuraEffect* aurEff = aur->GetEffect(EFFECT_0))
                    absorbCaster = aurEff->GetAmount();

            if (Guardian* pet = player->GetGuardianPet())
                if (Aura* aur = pet->GetAura(SPELL_WARLOCK_SOUL_LEECH_ABSORB))
                    if (AuraEffect* aurEff = aur->GetEffect(EFFECT_0))
                        absorbPet = aurEff->GetAmount();

            // Cannot go over 10% (or 20% with Demonskin) max health
            int32 basePointNormal = aura->GetEffect(EFFECT_1)->GetAmount();
            int32 basePointDS = sSpellMgr->GetSpellInfo(SPELL_WARLOCK_DEMONSKIN)->GetEffect(EFFECT_1).BasePoints;
            int32 totalBP = player->HasAura(SPELL_WARLOCK_DEMONSKIN) ? basePointDS : basePointNormal;
            int32 threshold = CalculatePct(player->GetMaxHealth(), totalBP);

            if (absorb > 0)
            {
                player->CastCustomSpell(SPELL_WARLOCK_SOUL_LEECH_ABSORB, SPELLVALUE_BASE_POINT0, std::min(absorb + absorbCaster, threshold), player, TRIGGERED_FULL_MASK);
                if (Guardian* pet = player->GetGuardianPet())
                    player->CastCustomSpell(SPELL_WARLOCK_SOUL_LEECH_ABSORB, SPELLVALUE_BASE_POINT0, std::min(absorb + absorbPet, threshold), pet, TRIGGERED_FULL_MASK);

                if (player->HasSpell(SPELL_WARLOCK_SOUL_LINK_WARLOCK))
                    if (Guardian* guardian = player->GetGuardianPet())
                    {
                        CastSpellExtraArgs values(TRIGGERED_FULL_MASK);
                        values.AddSpellBP0(CalculatePct(absorb, sSpellMgr->GetSpellInfo(SPELL_WARLOCK_SOUL_LINK_DUMMY_AURA)->GetEffect(EFFECT_1).BasePoints));
                        values.AddSpellBP1(CalculatePct(absorb, sSpellMgr->GetSpellInfo(SPELL_WARLOCK_SOUL_LINK_DUMMY_AURA)->GetEffect(EFFECT_2).BasePoints));
                        player->CastSpell(player, SPELL_WARLOCK_SOUL_LINK_HEAL, values);
                    }
            }
        }
    }

	void OnInterruptedSpellCast(Player* player, Spell* spell) override
	{
		if (!player)
			return;

		if (player->GetSpecializationId() != TALENT_SPEC_WARLOCK_AFFLICTION && player->GetSpecializationId() != TALENT_SPEC_WARLOCK_DESTRUCTION && player->GetSpecializationId() != TALENT_SPEC_WARLOCK_DEMONOLOGY)
			return;

		int32 visual = 0;
		switch (spell->GetSpellInfo()->Id)
		{
				// Felguard, Vilefiend
			case 30146:
			case 264119:
				visual = 81019;
				break;
				// Imp
			case 688:
				visual = 81024;
				break;
				// Voidwalker
			case 697:
				visual = 81022;
				break;
				// Succubus
			case 712:
				visual = 81023;
				break;
				// Felhunter
			case 691:
				visual = 81021;
				break;
			default:
				break;
		}

		player->SendCancelOrphanSpellVisual(visual);
	}

    void OnCreatureSummoned(Player* player, Creature* creature) override
    {
        if (!player || !creature)
            return;

        // Demonoly Warlock
        if (player->GetSpecializationId() == TALENT_SPEC_WARLOCK_DEMONOLOGY)
        {
            if (!player->HasAura(SPELL_WARLOCK_SACRIFICED_SOULS))
                return;

            if (creature->isDead() || creature->GetCreatureType() != CREATURE_TYPE_DEMON)
                return;

            player->CastSpell(player, SPELL_WARLOCK_SACRIFICED_SOULS_AURA, true);
        }
    }

    void OnCreatureUnsummoned(Player* player, Creature* creature) override
    {
        if (!player || !creature)
            return;

        // Demonoly Warlock
        if (player->GetSpecializationId() == TALENT_SPEC_WARLOCK_DEMONOLOGY)
        {
            if (!player->HasAura(SPELL_WARLOCK_SACRIFICED_SOULS))
                return;

            if (creature->GetCreatureType() != CREATURE_TYPE_DEMON)
                return;

            if (Aura* aura = player->GetAura(SPELL_WARLOCK_SACRIFICED_SOULS_AURA))
                aura->ModStackAmount(-1);
        }
    }
};

// 264178 - Demonbolt
class spell_warl_demonbolt : public SpellScript
{
    PrepareSpellScript(spell_warl_demonbolt);

    void DoCast()
    {
        // Generates 2 Soul Shards (Hardcoded number)
        GetCaster()->CastSpell(GetCaster(), SPELL_WARLOCK_DEMONBOLT_ENERGIZE, true);
        GetCaster()->CastSpell(GetCaster(), SPELL_WARLOCK_DEMONBOLT_ENERGIZE, true);
    }

    void HandleAfterCast()
    {
        if (Unit* caster = GetCaster())
            if (Aura* aura = caster->GetAura(SPELL_WARLOCK_DEMONIC_CORE_BUFF))
                aura->ModStackAmount(-1);
    }


    void Register() override
    {
        OnCast += SpellCastFn(spell_warl_demonbolt::DoCast);
        AfterCast += SpellCastFn(spell_warl_demonbolt::HandleAfterCast);
    }
};

// Immolate Dot - 157736
class spell_warl_immolate_dot : public AuraScript
{
    PrepareAuraScript(spell_warl_immolate_dot);

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
        Unit* caster = GetCaster();
        if (!caster)
            return;

        caster->CastSpell(caster, SPELL_WARLOCK_CHANNEL_DEMONFIRE_ACTIVATOR, true);
        caster->CastSpell(caster, SPELL_WARLOCK_IMMOLATE_PROC, true);
        
        if (caster->HasAura(SPELL_WARLOCK_FLASHPOINT_POWER))
            if (Unit* target = GetUnitOwner())
                if (target->HealthAbovePct(80))
                    if (AuraEffect* aurEff = caster->GetAuraEffect(SPELL_WARLOCK_FLASHPOINT_POWER, EFFECT_0))
                        caster->CastCustomSpell(SPELL_WARLOCK_FLASHPOINT_BUFF, SPELLVALUE_BASE_POINT0, aurEff->GetAmount(), caster, true);
    }

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Unit* caster = GetCaster();
        if (!caster)
            return;

        std::list<Unit*> enemies;
        caster->GetAttackableUnitListInRange(enemies, 100.0f);
        enemies.remove_if(Trinity::UnitAuraCheck(false, SPELL_WARLOCK_IMMOLATE_DOT, caster->GetGUID()));
        if (enemies.empty())
            if (Aura* aur = caster->GetAura(SPELL_WARLOCK_CHANNEL_DEMONFIRE_ACTIVATOR))
                aur->SetDuration(0);
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_warl_immolate_dot::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE);
        AfterEffectRemove += AuraEffectRemoveFn(spell_warl_immolate_dot::HandleRemove, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE, AURA_EFFECT_HANDLE_REAL);
    }
};

// Immolate proc - 193541
class spell_warl_immolate_aura : public AuraScript
{
    PrepareAuraScript(spell_warl_immolate_aura);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == SPELL_WARLOCK_IMMOLATE_DOT;
    }

    void OnProc(AuraEffect* aurEff, ProcEventInfo& procInfo)
    {
        procInfo.GetActor()->CastSpell(procInfo.GetActor(), SPELL_WARLOCK_IMMOLATE_ENERGIZE, true);
        if (procInfo.GetHitMask() & PROC_HIT_CRITICAL && roll_chance_i(aurEff->GetAmount()))
            procInfo.GetActor()->CastSpell(procInfo.GetActor(), SPELL_WARLOCK_IMMOLATE_ENERGIZE, true);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_warl_immolate_aura::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_warl_immolate_aura::OnProc, EFFECT_0, SPELL_AURA_DUMMY);

    }
};

// Shadow Bolt - 686 / 232670
class spell_warl_shadow_bolt : public SpellScript
{
    PrepareSpellScript(spell_warl_shadow_bolt);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_WARLOCK_SHADOW_BOLT_SHOULSHARD, SPELL_WARLOCK_SHADOW_EMBRACE, SPELL_WARLOCK_SHADOW_EMBRACE_BUFF });
    }

    void DoEffectHitTarget()
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        // Avoid the mod if the cast wasn't the instant one.
        if (caster->HasAura(SPELL_WARLOCK_NIGHTFALL_PROC) && caster->GetCurrentSpellCastTime(SPELL_WARLOCK_SHADOW_BOLT_AFFLI) == 0)
        {
            int32 damage = GetHitDamage() + CalculatePct(GetHitDamage(), sSpellMgr->GetSpellInfo(SPELL_WARLOCK_NIGHTFALL_PROC)->GetEffect(EFFECT_1).BasePoints);
            SetHitDamage(damage);
            caster->RemoveAurasDueToSpell(SPELL_WARLOCK_NIGHTFALL_PROC);
        }

        if (caster->HasAura(SPELL_WARLOCK_SHADOW_EMBRACE))
            caster->CastSpell(target, SPELL_WARLOCK_SHADOW_EMBRACE_BUFF, true);
   }

	void HandleAfterCast()
	{
		if (Unit* caster = GetCaster())
		{
			if (GetSpellInfo()->Id == SPELL_WARLOCK_SHADOW_BOLT)
				caster->CastSpell(caster, SPELL_WARLOCK_SHADOW_BOLT_SHOULSHARD, true);
		}
	}

    void Register() override
    {
        OnHit += SpellHitFn(spell_warl_shadow_bolt::DoEffectHitTarget);
		AfterCast += SpellCastFn(spell_warl_shadow_bolt::HandleAfterCast);
    }
};

// 710 - Banish
class spell_warl_banish : public SpellScript
{
    PrepareSpellScript(spell_warl_banish);

    void HandleBanish(SpellMissInfo missInfo)
    {
        if (missInfo != SPELL_MISS_IMMUNE)
            return;

        if (Unit* target = GetHitUnit())
        {
            // Casting Banish on a banished target will remove applied aura
            if (Aura * banishAura = target->GetAura(GetSpellInfo()->Id, GetCaster()->GetGUID()))
                banishAura->Remove();
        }
    }

    void Register() override
    {
        BeforeHit += BeforeSpellHitFn(spell_warl_banish::HandleBanish);
    }
};

// 17962 - Conflagrate
class spell_warl_conflagrate : public SpellScript
{
    PrepareSpellScript(spell_warl_conflagrate);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_WARLOCK_IMMOLATE });
    }

    void HandleHit(SpellEffIndex /*effindex*/)
    {
        Unit* caster = GetCaster();
        if (!caster)
            return;

        caster->CastSpell(caster, SPELL_WARLOCK_CONFLAGRATE_ENERGIZE, true);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_warl_conflagrate::HandleHit, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

// 205184 - Roaring Blaze
class spell_warr_roaring_blaze : public AuraScript
{
    PrepareAuraScript(spell_warr_roaring_blaze);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == SPELL_WARLOCK_CONFLAGRATE;
    }

    void OnProc(AuraEffect* /*aurEff*/, ProcEventInfo& procInfo)
    {
        procInfo.GetActor()->CastSpell(procInfo.GetActionTarget(), SPELL_WARLOCK_ROARING_BLAZE_DOT, true);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_warr_roaring_blaze::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_warr_roaring_blaze::OnProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

// 196406 - Back Draft Aura
class spell_warl_back_draft_aura : public AuraScript
{
    PrepareAuraScript(spell_warl_back_draft_aura);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == SPELL_WARLOCK_CONFLAGRATE;
    }

    void OnProc(AuraEffect* /*aurEff*/, ProcEventInfo& procInfo)
    {
		if (Unit* caster = GetCaster())
		{
			uint8 stacks = 1;
			if (caster->HasAura(SPELL_WARLOCK_FLASHOVER))
				stacks = 2;
			for (uint8 i = 0; i < stacks; i++)
				caster->CastSpell(caster, SPELL_WARLOCK_BACKDRAFT, true);
    }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_warl_back_draft_aura::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_warl_back_draft_aura::OnProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

// 6201 - Create Healthstone
class spell_warl_create_healthstone : public SpellScript
{
    PrepareSpellScript(spell_warl_create_healthstone);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_WARLOCK_CREATE_HEALTHSTONE });
    }

    bool Load() override
    {
        if (auto caster = GetCaster())
            return caster->IsPlayer();
        return false;
    }

    void HandleScriptEffect(SpellEffIndex /*effIndex*/)
    {
        GetCaster()->CastSpell(GetCaster(), SPELL_WARLOCK_CREATE_HEALTHSTONE, true);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_warl_create_healthstone::HandleScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
    }
};

// 265412 - Doom
class spell_warl_doom : public AuraScript
{
    PrepareAuraScript(spell_warl_doom);

    void HandleRemove(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /* mode */)
    {
        if (Unit* caster = GetCaster())
            if(Unit* target = GetTarget())
                if (GetTargetApplication()->GetRemoveMode() == AURA_REMOVE_BY_EXPIRE)
                    caster->CastSpell(target, SPELL_WARLOCK_DOOM_DAMAGE, true);
    }

    void Register() override
    {
        OnEffectRemove += AuraEffectApplyFn(spell_warl_doom::HandleRemove, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE, AURA_EFFECT_HANDLE_REAL);
    }
};

// 265469 - Doom Damage
class spell_warl_doom_damage : public SpellScript
{
    PrepareSpellScript(spell_warl_doom_damage);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_WARLOCK_DOOM });
    }

    void HandleHit()
    {
        if (Unit* caster = GetCaster())
            caster->CastSpell(caster, SPELL_WARLOCK_DOOM_SOUL_SHARD, true);
    }

    void HandleAfterHit()
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        if (target->isDead())
        {
            uint8 chance = sSpellMgr->GetSpellInfo(SPELL_WARLOCK_DOOM)->GetEffect(EFFECT_1).BasePoints;
            if (roll_chance_i(chance))
                caster->CastSpell(caster, SPELL_WARLOCK_DOOM_SUMMON_DOOMGUARD, true);
        }
    }

    void Register() override
    {
        OnHit += SpellHitFn(spell_warl_doom_damage::HandleHit);
        AfterHit += SpellHitFn(spell_warl_doom_damage::HandleAfterHit);
    }
};

// 48018 - Demonic Circle: Summon
/// Updated 4.3.4
class spell_warl_demonic_circle_summon : public AuraScript
{
    PrepareAuraScript(spell_warl_demonic_circle_summon);

    bool firstTick = true;

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes mode)
    {
		if (Unit* caster = GetCaster())
		{
        // If effect is removed by expire remove the summoned demonic circle too.
        if (!(mode & AURA_EFFECT_HANDLE_REAPPLY))
				caster->RemoveGameObject(GetId(), true);

			caster->RemoveAura(SPELL_WARLOCK_DEMONIC_CIRCLE_ALLOW_CAST);
    }
    }

    void HandleDummyTick(AuraEffect const* /*aurEff*/)
    {
		Unit* caster = GetCaster();
            SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(SPELL_WARLOCK_DEMONIC_CIRCLE_TELEPORT);
        if (!caster || !spellInfo)
                return;

        GameObject* circle = caster->GetGameObject(GetId());
            if (!circle)
            {
                if (firstTick)
                    GetAura()->SetDuration(0);

                return;
            }

            // Here we check if player is in demonic circle teleport range, if so add
            // WARLOCK_DEMONIC_CIRCLE_ALLOW_CAST; allowing him to cast the WARLOCK_DEMONIC_CIRCLE_TELEPORT.
        if (caster->IsWithinDist(circle, spellInfo->GetMaxRange(true)))
			caster->AddAura(SPELL_WARLOCK_DEMONIC_CIRCLE_ALLOW_CAST);
            else
			caster->RemoveAura(SPELL_WARLOCK_DEMONIC_CIRCLE_ALLOW_CAST);
        }

    void Register() override
    {
        OnEffectRemove += AuraEffectApplyFn(spell_warl_demonic_circle_summon::HandleRemove, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_warl_demonic_circle_summon::HandleDummyTick, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

// 48020 - Demonic Circle: Teleport
/// Updated 4.3.4
class spell_warl_demonic_circle_teleport : public AuraScript
{
    PrepareAuraScript(spell_warl_demonic_circle_teleport);

    void HandleTeleport(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (Player* player = GetTarget()->ToPlayer())
        {
            if (GameObject* circle = player->GetGameObject(SPELL_WARLOCK_DEMONIC_CIRCLE_SUMMON))
            {
                player->NearTeleportTo(circle->GetPositionX(), circle->GetPositionY(), circle->GetPositionZ(), circle->GetOrientation());
                player->RemoveMovementImpairingAuras(true);
            }
        }
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_warl_demonic_circle_teleport::HandleTeleport, EFFECT_0, SPELL_AURA_MECHANIC_IMMUNITY, AURA_EFFECT_HANDLE_REAL);
    }
};

// 67518, 19505 - Devour Magic
class spell_warl_devour_magic : public SpellScript
{
    PrepareSpellScript(spell_warl_devour_magic);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_WARLOCK_GLYPH_OF_DEMON_TRAINING, SPELL_WARLOCK_DEVOUR_MAGIC_HEAL });
    }

    void OnSuccessfulDispel(SpellEffIndex /*effIndex*/)
    {
        //if (SpellEffectInfo const* effect = GetSpellInfo()->GetEffect(EFFECT_1))
        {
            Unit* caster = GetCaster();
            int32 heal_amount = GetSpellInfo()->GetEffect(EFFECT_1).CalcValue(caster);

            caster->CastCustomSpell(caster, SPELL_WARLOCK_DEVOUR_MAGIC_HEAL, &heal_amount, nullptr, nullptr, true);

            // Glyph of Felhunter
            if (Unit* owner = caster->GetOwner())
                if (owner->GetAura(SPELL_WARLOCK_GLYPH_OF_DEMON_TRAINING))
                    owner->CastCustomSpell(owner, SPELL_WARLOCK_DEVOUR_MAGIC_HEAL, &heal_amount, nullptr, nullptr, true);
        }
    }

    void Register() override
    {
        OnEffectSuccessfulDispel += SpellEffectFn(spell_warl_devour_magic::OnSuccessfulDispel, EFFECT_0, SPELL_EFFECT_DISPEL);
    }
};

// 48181 - Haunt
class aura_warl_haunt : public AuraScript
{
    PrepareAuraScript(aura_warl_haunt);

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Unit* caster = GetCaster();
        if (!caster || GetTargetApplication()->GetRemoveMode() != AURA_REMOVE_BY_DEATH)
            return;

        caster->GetSpellHistory()->ResetCooldown(SPELL_WARLOCK_HAUNT, true);
    }

    void Register() override
    {
        OnEffectRemove += AuraEffectApplyFn(aura_warl_haunt::HandleRemove, EFFECT_1, SPELL_AURA_MOD_SCHOOL_MASK_DAMAGE_FROM_CASTER, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
    }
};

// 755 - Health Funnel
/// Updated 4.3.4
class spell_warl_health_funnel : public AuraScript
{
    PrepareAuraScript(spell_warl_health_funnel);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_WARLOCK_HEALTH_FUNNEL_HEAL });
    }

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
        Unit* target = GetUnitOwner();
        Unit* caster = GetCaster();
        if (!target || !caster)
            return;

        CastSpellExtraArgs values(TRIGGERED_FULL_MASK);
        int32 damage = caster->CountPctFromMaxHealth(4);
        values.AddSpellBP0(damage);
        values.AddSpellBP1(damage * 2);

        caster->CastSpell(target, SPELL_WARLOCK_HEALTH_FUNNEL_HEAL, values);
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_warl_health_funnel::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

// 6262 - Healthstone
class spell_warl_healthstone_heal : public SpellScript
{
    PrepareSpellScript(spell_warl_healthstone_heal);

    void HandeHeal(SpellEffIndex /*effIndex*/)
    {
        /*if (GetCaster()->HasAura(SPELL_HUNTER_EXHILARATION_PET_AURA))
            GetCaster()->CastSpell(nullptr, SPELL_HUNTER_EXHILARATION_PET, true);*/
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_warl_healthstone_heal::HandeHeal, EFFECT_0, SPELL_EFFECT_HEAL_PCT);
    }
};

// 27243 - Seed of Corruption
class spell_warl_seed_of_corruption : public SpellScript
{
    PrepareSpellScript(spell_warl_seed_of_corruption);

    void HandleBeforeCast()
    {
        _maxAdditionalTargets = 0;

        if (Aura* aura = GetCaster()->GetAura(SPELL_WARLOCK_SOW_THE_SEEDS))
            _maxAdditionalTargets += aura->GetEffect(EFFECT_0)->GetSpellEffectInfo().CalcValue();
    }

    void CorrectTargets(std::list<WorldObject*>& targets)
    {
        std::list<WorldObject*> correctedTargets;
        for (WorldObject* obj : targets)
        {
            if (obj == GetExplTargetUnit())
            {
                correctedTargets.push_back(obj);
                continue;
            }

            if (_maxAdditionalTargets)
            {
                correctedTargets.push_back(obj);
                --_maxAdditionalTargets;
            }
        }

        targets = correctedTargets;
    }

	void HandleHit(SpellMissInfo missInfo)
	{
		Unit* target = GetHitUnit();
		Unit* caster = GetCaster();

		if (!caster || !target)
			return;

		if (target->HasAura(SPELL_WARLOCK_SEED_OF_CURRUPTION, caster->GetGUID()))
			target->RemoveAurasDueToSpell(SPELL_WARLOCK_SEED_OF_CURRUPTION, caster->GetGUID());
	}

    void Register() override
    {
		BeforeHit += BeforeSpellHitFn(spell_warl_seed_of_corruption::HandleHit);
        BeforeCast += SpellCastFn(spell_warl_seed_of_corruption::HandleBeforeCast);
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_warl_seed_of_corruption::CorrectTargets, EFFECT_1, TARGET_UNIT_DEST_AREA_ENEMY);
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_warl_seed_of_corruption::CorrectTargets, EFFECT_2, TARGET_UNIT_DEST_AREA_ENEMY);
    }

private:
    uint8 _maxAdditionalTargets;
};

// 27243 - Seed of Corruption
class aura_warl_seed_of_corruption : public AuraScript
{
	PrepareAuraScript(aura_warl_seed_of_corruption);

	bool Validate(SpellInfo const* /*spellInfo*/) override
	{
		return ValidateSpellInfo({ SPELL_WARLOCK_SEED_OF_CURRUPTION_DAMAGE });
	}

	bool HandleCheckProc(ProcEventInfo& eventInfo)
	{
		if (Unit* caster = GetCaster())
		{
			if (eventInfo.GetDamageInfo() && eventInfo.GetDamageInfo()->GetSpellInfo() && eventInfo.GetDamageInfo()->GetAttacker()->GetGUID() == caster->GetGUID())
			{
				int32 explosionDamage = caster->ToPlayer()->SpellBaseDamageBonusDone(SPELL_SCHOOL_MASK_SHADOW) * 0.5f;
				damage += eventInfo.GetDamageInfo()->GetDamage();
				if (damage >= explosionDamage)
					return true;
			}

            if (eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == SPELL_WARLOCK_SEED_OF_CURRUPTION_DAMAGE)
                return true;
		}

		return false;
	}

	void HandleProc(ProcEventInfo& eventInfo)
	{
		if (Unit* caster = GetCaster())
		{
			if (Unit* owner = GetUnitOwner())
			{
				owner->RemoveAura(SPELL_WARLOCK_SEED_OF_CURRUPTION, caster->GetGUID());
				caster->CastSpell(owner->GetPosition(), SPELL_WARLOCK_SEED_OF_CURRUPTION_DAMAGE, true);
			}
		}
	}

	void HandlePeriodic(AuraEffect const* aurEff)
	{
		Unit* target = GetTarget();
		if (!target)
			return;

		aurEff->GetBase()->Remove(AURA_REMOVE_BY_EXPIRE);
		if (Unit* caster = GetCaster())
			caster->CastSpell(target->GetPosition(), SPELL_WARLOCK_SEED_OF_CURRUPTION_DAMAGE, true);
	}

	void Register() override
	{
		OnProc += AuraProcFn(aura_warl_seed_of_corruption::HandleProc);
		DoCheckProc += AuraCheckProcFn(aura_warl_seed_of_corruption::HandleCheckProc);
		OnEffectPeriodic += AuraEffectPeriodicFn(aura_warl_seed_of_corruption::HandlePeriodic, EFFECT_1, SPELL_AURA_PERIODIC_DAMAGE);
	}

private:
	int32 damage = 0;
};

// 27285 - Seed of Corruption damages
class spell_warl_seed_of_corruption_damage : public SpellScript
{
    PrepareSpellScript(spell_warl_seed_of_corruption_damage);

    void HandleOnHit(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        caster->CastSpell(target, SPELL_WARLOCK_CORRUPTION_DAMAGE, true);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_warl_seed_of_corruption_damage::HandleOnHit, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

// Soul Leech aura - 228974
class spell_warl_soul_leech_aura : public AuraScript
{
    PrepareAuraScript(spell_warl_soul_leech_aura);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_WARLOCK_DEMONSKIN });
    }

    bool OnCheckProc(ProcEventInfo& eventInfo)
    {
		if (eventInfo.GetDamageInfo() && eventInfo.GetDamageInfo()->GetDamageType() != HEAL && !eventInfo.GetDamageInfo()->GetSpellInfo() && eventInfo.GetDamageInfo()->GetDamage() > 0)
			return true;

		if (eventInfo.GetDamageInfo() && eventInfo.GetDamageInfo()->GetDamageType() != HEAL && (eventInfo.GetDamageInfo()->GetDamage() > 0 || (eventInfo.GetDamageInfo()->GetSpellInfo() &&
            eventInfo.GetDamageInfo()->GetDamage() > 0 && !eventInfo.GetDamageInfo()->GetSpellInfo()->IsTargetingArea() && !eventInfo.GetDamageInfo()->GetSpellInfo()->IsAffectingArea())))
			return true;

		return false;
	}

	void HandleProc(ProcEventInfo& eventInfo)
	{
        Unit* caster = GetCaster();
        if (!caster)
			return;

		int32 basePoints = sSpellMgr->GetSpellInfo(SPELL_WARLOCK_SOUL_LEECH_AURA)->GetEffect(EFFECT_0).BasePoints;
        int32 absorb = CalculatePct(eventInfo.GetDamageInfo()->GetDamage(), basePoints);
        int32 absorbCaster = 0;
        int32 absorbPet = 0;

        // Add remaining amount if already applied
        if (Aura* aur = caster->GetAura(SPELL_WARLOCK_SOUL_LEECH_ABSORB))
            if (AuraEffect* aurEff = aur->GetEffect(EFFECT_0))
                absorbCaster = aurEff->GetAmount();

        if (Guardian* pet = caster->GetGuardianPet())
            if (Aura* aur = pet->GetAura(SPELL_WARLOCK_SOUL_LEECH_ABSORB))
                if (AuraEffect* aurEff = aur->GetEffect(EFFECT_0))
                    absorbPet = aurEff->GetAmount();

		// Cannot go over 10% (or 20% with Demonskin) max health
		int32 basePointNormal = GetSpellInfo()->GetEffect(EFFECT_1).BasePoints;
		int32 basePointDS = sSpellMgr->GetSpellInfo(SPELL_WARLOCK_DEMONSKIN)->GetEffect(EFFECT_1).BasePoints;
        int32 totalBP = caster->HasAura(SPELL_WARLOCK_DEMONSKIN) ? basePointDS : basePointNormal;
        int32 threshold = CalculatePct(caster->GetMaxHealth(), totalBP);

		if (absorb > 0)
		{
			caster->CastCustomSpell(SPELL_WARLOCK_SOUL_LEECH_ABSORB, SPELLVALUE_BASE_POINT0, std::min(absorb + absorbCaster, threshold), caster, TRIGGERED_FULL_MASK);
			if (Guardian* pet = caster->GetGuardianPet())
				caster->CastCustomSpell(SPELL_WARLOCK_SOUL_LEECH_ABSORB, SPELLVALUE_BASE_POINT0, std::min(absorb + absorbPet, threshold), pet, TRIGGERED_FULL_MASK);

			if (caster->HasSpell(SPELL_WARLOCK_SOUL_LINK_WARLOCK))
				if (Guardian* guardian = caster->GetGuardianPet())
				{
					CastSpellExtraArgs values(TRIGGERED_FULL_MASK);
					values.AddSpellBP0(CalculatePct(absorb, sSpellMgr->GetSpellInfo(SPELL_WARLOCK_SOUL_LINK_DUMMY_AURA)->GetEffect(EFFECT_1).BasePoints));
					values.AddSpellBP1(CalculatePct(absorb, sSpellMgr->GetSpellInfo(SPELL_WARLOCK_SOUL_LINK_DUMMY_AURA)->GetEffect(EFFECT_2).BasePoints));
					caster->CastSpell(caster, SPELL_WARLOCK_SOUL_LINK_HEAL, values);
    }
		}
	}

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_warl_soul_leech_aura::OnCheckProc);
		OnProc += AuraProcFn(spell_warl_soul_leech_aura::HandleProc);
    }
};

const uint32 damageSpells[5] =
{
    SPELL_WARLOCK_UNSTABLE_AFFLICTION_DAMAGE_1,
    SPELL_WARLOCK_UNSTABLE_AFFLICTION_DAMAGE_2,
    SPELL_WARLOCK_UNSTABLE_AFFLICTION_DAMAGE_3,
    SPELL_WARLOCK_UNSTABLE_AFFLICTION_DAMAGE_4,
    SPELL_WARLOCK_UNSTABLE_AFFLICTION_DAMAGE_5,
};

// 30108 Unstable Affliction
//Last Update 8.0.1 Build 28153
class spell_warl_unstable_affliction : public SpellScript
{
    PrepareSpellScript(spell_warl_unstable_affliction);

    void HandleOnHitTarget(SpellEffIndex /*effIndex*/)
    {
        if (Unit* caster = GetCaster())
        {
            if (Unit* target = GetHitUnit())
            {
                for (uint8 i = 0; i < 5; ++i)
                {
                    if (target->HasAura(damageSpells[i], caster->GetGUID()))
                        continue;

                    caster->CastSpell(target, damageSpells[i], true);
                    caster->CastSpell(target, SPELL_WARLOCK_UNSTABLE_AFLICTION_CONTAGION, true);
                    break;
                }
            }
        }
    }

    void HandleCast()
    {
        if (Unit* caster = GetCaster())
            if (caster->HasAura(SPELL_WARLOCK_DREADFUL_CALLING))
                caster->GetSpellHistory()->ModifyCooldown(SPELL_WARLOCK_DARKGLARE_SUMMON, -1s);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_warl_unstable_affliction::HandleOnHitTarget, EFFECT_0, SPELL_EFFECT_DUMMY);
        OnCast += SpellCastFn(spell_warl_unstable_affliction::HandleCast);
    }
};

// 233490 - 233496 - 233497 - 233498 - 233499 - Unstable Affliction
//Last Update 8.0.1 Build 28153
class aura_warl_unstable_affliction : public AuraScript
{
    PrepareAuraScript(aura_warl_unstable_affliction);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_WARLOCK_UNSTABLE_AFFLICTION_DISPEL, SPELL_WARLOCK_UNSTABLE_AFFLICTION });
    }

    void HandleDispel(DispelInfo* dispelInfo)
    {
        Unit* caster = GetCaster();
        auto dispeller = dispelInfo->GetDispeller();
        bool remove = false;
        if (!caster || !dispeller)
            return;

        // Backfire damage and silence.
        // $233490s1 * $s1 / 100}
        //if (SpellEffectInfo const* eff0Ua = sSpellMgr->GetSpellInfo(SPELL_WARLOCK_UNSTABLE_AFFLICTION)->GetEffect(EFFECT_0))
        {
            if (AuraEffect* eff0 = GetAura()->GetEffect(EFFECT_0))
            {
                int32 damage = int32(eff0->GetDamage() * eff0->GetSpellEffectInfo().BasePoints / 100.0f);
                caster->CastSpell(dispeller, SPELL_WARLOCK_UNSTABLE_AFFLICTION_DISPEL, CastSpellExtraArgs(true).AddSpellBP0(damage));
            }
        }
    }

    void HandleRemove(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /* mode */)
    {
        if (Unit* caster = GetCaster())
        {
            if (Unit* target = GetTarget())
            {
                bool remove = false;

                for (uint8 i = 0; i < 5; ++i)
                {
                    if (GetSpellInfo()->Id == damageSpells[i])
                        continue;

                    if (target->HasAura(damageSpells[i], caster->GetGUID()))
                    {
                        remove = false;
                        break;
                    }

                    remove = true;
                }

                if (remove)
                    target->RemoveAura(SPELL_WARLOCK_UNSTABLE_AFLICTION_CONTAGION, caster->GetGUID());
            }            

            if (GetTargetApplication()->GetRemoveMode() == AURA_REMOVE_BY_DEATH)
                caster->CastSpell(caster, SPELL_WARLOCK_UNSTABLE_AFFLICTION_ENERGIZE, true);
        }      
    }

    void Register() override
    {
        AfterDispel += AuraDispelFn(aura_warl_unstable_affliction::HandleDispel);
        OnEffectRemove += AuraEffectApplyFn(aura_warl_unstable_affliction::HandleRemove, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE, AURA_EFFECT_HANDLE_REAL);
    }
};

enum lifeTap
{
    SPELL_WARLOCK_LIFE_TAP = 1454,
    SPELL_WARLOCK_LIFE_TAP_GLYPH = 63320,
};

// Life Tap - 1454
class spell_warl_life_tap : public SpellScriptLoader
{
public:
    spell_warl_life_tap() : SpellScriptLoader("spell_warl_life_tap") { }

    class spell_warl_life_tap_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_warl_life_tap_SpellScript);

        SpellCastResult CheckLife()
        {
            if (GetCaster()->GetHealthPct() > 15.0f || GetCaster()->HasAura(SPELL_WARLOCK_LIFE_TAP_GLYPH))
                return SPELL_CAST_OK;
            return SPELL_FAILED_FIZZLE;
        }

        void HandleOnHitTarget(SpellEffIndex effIndex)
        {
            PreventHitDefaultEffect(effIndex);
            if (!GetCaster()->HasAura(SPELL_WARLOCK_LIFE_TAP_GLYPH))
                GetCaster()->EnergizeBySpell(GetCaster(), GetSpellInfo(), int32(GetCaster()->GetMaxHealth() * GetSpellInfo()->GetEffect(EFFECT_0).CalcValue() / 100), POWER_MANA);
        }

        void Register() override
        {
            OnCheckCast += SpellCheckCastFn(spell_warl_life_tap_SpellScript::CheckLife);
            OnEffectHitTarget += SpellEffectFn(spell_warl_life_tap_SpellScript::HandleOnHitTarget, EFFECT_0, SPELL_EFFECT_ENERGIZE);
        }
    };

    class spell_warl_life_tap_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_warl_life_tap_AuraScript);

        void CalculateAmount(AuraEffect const* /* aurEff */, int32& amount, bool& /* canBeRecalculated */)
        {
            if (GetCaster()->HasAura(SPELL_WARLOCK_LIFE_TAP_GLYPH))
                amount *= GetCaster()->GetMaxHealth();
            else
                amount = 0;
        }

        void Register() override
        {
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_warl_life_tap_AuraScript::CalculateAmount, EFFECT_2, SPELL_AURA_SCHOOL_HEAL_ABSORB);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_warl_life_tap_SpellScript();
    }

    AuraScript* GetAuraScript() const override
    {
        return new spell_warl_life_tap_AuraScript();
    }
};

// 980 - Agony
class spell_warlock_agony : public SpellScriptLoader
{
public:
    spell_warlock_agony() : SpellScriptLoader("spell_warlock_agony") {}

    class spell_warlock_agony_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_warlock_agony_AuraScript);

        void HandleApply(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /* mode */)
        {
            if (Unit* caster = GetCaster())
                if(caster->HasAura(SPELL_WARLOCK_SUDDEN_ONSET))
                    if(SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(SPELL_WARLOCK_SUDDEN_ONSET))
                        SetStackAmount(spellInfo->GetEffect(EFFECT_1).BasePoints);
        }

        void HandleDummyPeriodic(AuraEffect const* auraEffect)
        {
            Unit* caster = GetCaster();
            if (!caster)
                return;

            if (auto corruptingLeer = caster->GetAuraEffect(339455, EFFECT_0))
                if (corruptingLeer->ConduitRankEntry)
                    if (roll_chance_i(corruptingLeer->ConduitRankEntry->AuraPointsOverride))
                        caster->GetSpellHistory()->ModifyCooldown(205180, -5000);

            // Blizz: When you have no Agonies out, the accumulator is cleared. When you next cast one, it's reset to a random value from 0 to 0.99.
            float soulShardAgonyTick = caster->Variables.GetValue<float>("SoulShardAgonyTick", frand(0.0f, 99.0f) + (caster->HasAura(Warlock::eLegendary::PerpetualAgonyOfAzjAqir) ? 20.0f : 0.0f));
            // Blizz: The added value per tick is currently 0.16 on average, with some variance (we'll try to remember to update this since there's no way to see it in-game).
            int32 amountAgonies = caster->GetTargetAuraApplications(SPELL_WARLOCK_AGONY).size();
            // Blizz: Each added amount is divided by the square root of the number of Agonies you currently have active.
            soulShardAgonyTick += 16.0f / sqrtf(std::max(1, amountAgonies));
            // Blizz: When it exceeds 1.....
            if (soulShardAgonyTick >= 100.0f)
            {
                // .....it generates a shard and rolls over the remainder to start the next one.
                soulShardAgonyTick = soulShardAgonyTick - 100.0f;
                caster->CastSpell(caster, SPELL_WARLOCK_AGONY_ENERGIZE, true);
                if (Aura* aura = caster->GetAura(SPELL_WARLOCK_WRACKING_BRILLIANCE_POWER))
                    caster->CastCustomSpell(SPELL_WARLOCK_WRACKING_BRILLIANCE_BUFF, SPELLVALUE_BASE_POINT0, aura->GetEffect(EFFECT_0)->GetAmount(), caster, true);
            }

            caster->Variables.Set("SoulShardAgonyTick", soulShardAgonyTick);

            // If we have more than maxStackAmount, dont do anything
            if (GetStackAmount() >= auraEffect->GetBase()->GetMaxStackAmount())
                return;

            SetStackAmount(GetStackAmount() + 1);
        }

        void OnRemove(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            // If last agony removed, remove tick counter
            if (Unit* caster = GetCaster())
                if (!caster->GetOwnedAura(SPELL_WARLOCK_AGONY))
                    caster->Variables.Remove("SoulShardAgonyTick");
        }

        void Register() override
        {
            OnEffectApply += AuraEffectApplyFn(spell_warlock_agony_AuraScript::HandleApply, EFFECT_1, SPELL_AURA_PERIODIC_DUMMY, AURA_EFFECT_HANDLE_REAL);
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_warlock_agony_AuraScript::HandleDummyPeriodic, EFFECT_1, SPELL_AURA_PERIODIC_DUMMY);
            AfterEffectRemove += AuraEffectRemoveFn(spell_warlock_agony_AuraScript::OnRemove, EFFECT_1, SPELL_AURA_PERIODIC_DUMMY, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_warlock_agony_AuraScript();
    }
};

// Burning Rush - 111400
class spell_warl_burning_rush : public SpellScript
{
    PrepareSpellScript(spell_warl_burning_rush);

    bool _isRemove = false;

    SpellCastResult CheckCast()
    {
        Unit* caster = GetCaster();
        if (!caster)
            return SPELL_FAILED_CANT_DO_THAT_RIGHT_NOW;

        if (caster->HealthBelowPct(5))
            return SPELL_FAILED_CANT_DO_THAT_RIGHT_NOW;

        return SPELL_CAST_OK;
    }

    void HandleBeforeCast()
    {
        Unit* caster = GetCaster();
        if (!caster)
            return;

        if (caster->HasAura(SPELL_WARLOCK_BURNING_RUSH))
            _isRemove = true;
    }

    void HandleHit()
    {
        if (_isRemove)
            GetCaster()->RemoveAurasDueToSpell(SPELL_WARLOCK_BURNING_RUSH);
    }

    void Register() override
    {
        BeforeCast += SpellCastFn(spell_warl_burning_rush::HandleBeforeCast);
        AfterHit += SpellHitFn(spell_warl_burning_rush::HandleHit);
        OnCheckCast += SpellCheckCastFn(spell_warl_burning_rush::CheckCast);
    }
};

class aura_warl_burning_rush : public AuraScript
{
    PrepareAuraScript(aura_warl_burning_rush);

    void OnTick(const AuraEffect* /* aurEff */)
    {
        if (GetCaster())
        {
            // This way if the current tick takes you below 4%, next tick won't execute
            uint64 basepoints = GetCaster()->CountPctFromMaxHealth(4);
            if (GetCaster()->GetHealth() <= basepoints ||
                GetCaster()->GetHealth() - basepoints <= basepoints)
                GetAura()->SetDuration(0);
        }
    }
    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(aura_warl_burning_rush::OnTick, EFFECT_1, SPELL_AURA_PERIODIC_DAMAGE_PERCENT);
    }
};

// Chaos Bolt - 116858 and 215279
class spell_warl_chaos_bolt : public SpellScript
{
    PrepareSpellScript(spell_warl_chaos_bolt);

    void HandleCritChance(Unit const* /*victim*/, float& chance)
    {
        chance = 100.f;
    }

    void HandleOnLaunch(SpellEffIndex effIndex)
    {
        if (Unit* caster = GetCaster())
        {
            if (auto player = caster->ToPlayer())
            {
                if (Unit* target = GetHitUnit())
                {
                    PreventHitDefaultEffect(effIndex);
                    uint32 damage = 0;
                    damage = caster->SpellDamageBonusDone(target, GetSpellInfo(), (uint32)damage, SPELL_DIRECT_DAMAGE, GetEffectInfo(effIndex));
                    damage = target->SpellDamageBonusTaken(caster, GetSpellInfo(), (uint32)damage, SPELL_DIRECT_DAMAGE);
                    float crit = player->m_activePlayerData->CritPercentage;
                    AddPct(damage, crit);
                    SetHitDamage(damage);
                }
            }

            if (caster->Variables.Exist("GRIMOIRE_OF_SUPREMACY_STACK"))
            {
                caster->RemoveAura(SPELL_WARLOCK_GRIMOIRE_OF_SUPREMACY_BUFF);
                caster->CastCustomSpell(SPELL_WARLOCK_GRIMOIRE_OF_SUPREMACY_BUFF, SPELLVALUE_AURA_STACK, caster->Variables.GetValue<uint8>("GRIMOIRE_OF_SUPREMACY_STACK"), caster, true);
            }
        }                
    }

    void HandleOnHit(SpellEffIndex /*effIndex*/)
    {
		Unit* caster = GetOriginalCaster();
		Unit* target = GetHitUnit();
		if (!caster || !target)
			return;

		// Internal Combustion
		if (caster->HasAura(SPELL_WARLOCK_INTERNAL_COMBUSTION))
            if (Aura* aura = target->GetAura(SPELL_WARLOCK_IMMOLATE_DOT, caster->GetGUID()))
            {
                uint8 duration = 5;
                if (aura->GetDuration() * 0.001f <= duration)
                {
                    duration = (uint8)std::ceil(aura->GetDuration() * 0.001f);
                    target->RemoveAura(SPELL_WARLOCK_IMMOLATE_DOT);
                }
                else
                    aura->ModDuration(-duration * IN_MILLISECONDS);
                int32 baseDamage = caster->GetTotalSpellPowerValue(SPELL_SCHOOL_MASK_FIRE, false) * 0.225f;
                caster->CastCustomSpell(SPELL_WARLOCK_INTERNAL_COMBUSTION_DAMAGE, SPELLVALUE_BASE_POINT0, baseDamage * duration, target, true);
            }

        // Chaotic Inferno
        if (caster->HasAura(SPELL_WARLOCK_CHAOTIC_INFERNO_POWER) && roll_chance_i(25))
            caster->CastSpell(caster, SPELL_WARLOCK_CHAOTIC_INFERNO_PROC, true);
    }

	void HandleAfterCast()
	{
        if (Unit* caster = GetCaster())
        {
            if (Aura* aura = caster->GetAura(SPELL_WARLOCK_BACKDRAFT))
                aura->ModStackAmount(-1);

            if (Aura* aura = caster->GetAura(SPELL_WARLOCK_CRASHING_CHAOS_BUFF))
                aura->ModCharges(-1);
        }
	}

    void Register() override
    {
        OnCalcCritChance += SpellOnCalcCritChanceFn(spell_warl_chaos_bolt::HandleCritChance);
        OnEffectLaunchTarget += SpellEffectFn(spell_warl_chaos_bolt::HandleOnLaunch, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
        OnEffectHitTarget += SpellEffectFn(spell_warl_chaos_bolt::HandleOnHit, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
		AfterCast += SpellCastFn(spell_warl_chaos_bolt::HandleAfterCast);
    }
};

class spell_warl_conflagrate_aura : public SpellScript
{
    PrepareSpellScript(spell_warl_conflagrate_aura);

    void HandleOnHit()
    {
        if (Player* _player = GetCaster()->ToPlayer())
        {
            if (Unit* target = GetHitUnit())
            {
                if (!target->HasAura(SPELL_WARLOCK_IMMOLATE) && !_player->HasAura(SPELL_WARLOCK_GLYPH_OF_CONFLAGRATE))
                    if (target->GetAura(SPELL_WARLOCK_CONFLAGRATE))
                        target->RemoveAura(SPELL_WARLOCK_CONFLAGRATE);

                if (!target->HasAura(SPELL_WARLOCK_IMMOLATE_FIRE_AND_BRIMSTONE))
                    if (target->GetAura(SPELL_WARLOCK_CONFLAGRATE_FIRE_AND_BRIMSTONE))
                        target->RemoveAura(SPELL_WARLOCK_CONFLAGRATE_FIRE_AND_BRIMSTONE);
            }
        }
    }

    void Register() override
    {
        OnHit += SpellHitFn(spell_warl_conflagrate_aura::HandleOnHit);
    }
};

class spell_warl_dark_regeneration : public AuraScript
{
    PrepareAuraScript(spell_warl_dark_regeneration);

    void HandleApply(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /* mode */)
    {
        if (GetTarget())
            if (Guardian* pet = GetTarget()->GetGuardianPet())
                pet->CastSpell(pet, SPELL_WARLOCK_DARK_REGENERATION, true);
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_warl_dark_regeneration::HandleApply, EFFECT_0, SPELL_AURA_OBS_MOD_HEALTH, AURA_EFFECT_HANDLE_REAL);
    }
};

class spell_warl_demonic_call : public SpellScript
{
    PrepareSpellScript(spell_warl_demonic_call);

    void HandleOnHit()
    {
        if (Player* _player = GetCaster()->ToPlayer())
        {
            if (GetHitUnit())
            {
                if (_player->HasAura(SPELL_WARLOCK_DEMONIC_CALL) && !_player->HasAura(SPELL_WARLOCK_DISRUPTED_NETHER))
                {
                    _player->CastSpell(_player, SPELL_WARLOCK_HAND_OF_GULDAN_SUMMON, true);
                    _player->RemoveAura(SPELL_WARLOCK_DEMONIC_CALL);
                }
            }
        }
    }

    void Register() override
    {
        OnHit += SpellHitFn(spell_warl_demonic_call::HandleOnHit);
    }
};

// Demonic Gateway - 111771 v8.0.1
class spell_warl_demonic_gateway : public SpellScript
{
    PrepareSpellScript(spell_warl_demonic_gateway);

    SpellCastResult CheckElevation()
    {
        if (!GetCaster() || !GetCaster()->ToPlayer())
            return SPELL_FAILED_DONT_REPORT;

        Player* player = GetCaster()->ToPlayer();

        WorldLocation* spellDest = const_cast<WorldLocation*>(GetExplTargetDest());
        if (!spellDest)
            return SPELL_FAILED_DONT_REPORT;

        Map* map = player->GetMap();
        if (map == nullptr)
            return SPELL_FAILED_SUCCESS;

        if ((spellDest->GetPositionZ() >= player->GetPosition().GetPositionZ() + 10) || (spellDest->GetPositionZ() <= player->GetPosition().GetPositionZ() - 10))
            return SPELL_FAILED_NOPATH;

        return SPELL_CAST_OK;
    }

    void HandleSummon()
    {
        Unit* caster = GetCaster();
        if (!caster)
            return;

        Player* player = caster->ToPlayer();
        if (!player)
            return;

        std::list<Creature*> gatewayPurpleList;
        player->GetCreatureListWithEntryInGrid(gatewayPurpleList, 59271, 500.0f);

        for (std::list<Creature*>::iterator i = gatewayPurpleList.begin(); i != gatewayPurpleList.end(); ++i)
        {
            Unit* owner = (*i)->GetOwner();

            if (owner && owner == player && (*i)->IsSummon())
                continue;

            i = gatewayPurpleList.erase(i);
        }

        if ((int32)gatewayPurpleList.size() >= 1)
            gatewayPurpleList.back()->ToTempSummon()->UnSummon();

        std::list<Creature*> gatewayGreenList;
        player->GetCreatureListWithEntryInGrid(gatewayGreenList, 59262, 500.0f);

        for (std::list<Creature*>::iterator i = gatewayGreenList.begin(); i != gatewayGreenList.end(); ++i)
        {
            Unit* owner = (*i)->GetOwner();

            if (owner && owner == player && (*i)->IsSummon())
                continue;

            i = gatewayGreenList.erase(i);
        }

        if ((int32)gatewayGreenList.size() >= 1)
            gatewayGreenList.back()->ToTempSummon()->UnSummon();

        WorldLocation const* dest = GetExplTargetDest();
        if (!dest)
            return;

        caster->CastSpell(*dest, SPELL_WARLOCK_DEMONIC_GATEWAY_SUMMON_GREEN, true);
        caster->CastSpell(caster->GetPosition(), SPELL_WARLOCK_DEMONIC_GATEWAY_SUMMON_PURPLE, true);
    }

    void Register() override
    {
        OnCheckCast += SpellCheckCastFn(spell_warl_demonic_gateway::CheckElevation);
        OnCast += SpellCastFn(spell_warl_demonic_gateway::HandleSummon);
    }
};

// 198590 - Drain Soul
class spell_warl_drain_soul : public AuraScript
{
    PrepareAuraScript(spell_warl_drain_soul);

    void HandleApply(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /* mode */)
    {
        if (Unit* caster = GetCaster())
            if (caster && caster->HasAura(SPELL_WARLOCK_SHADOW_EMBRACE))
                caster->CastSpell(GetTarget(), SPELL_WARLOCK_SHADOW_EMBRACE_BUFF, true);

		baseDamage = GetAura()->GetEffect(EFFECT_0)->GetDamage();
    }

    void HandleRemove(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /* mode */)
    {
        if (GetCaster() && GetTargetApplication()->GetRemoveMode() == AURA_REMOVE_BY_DEATH)
            GetCaster()->CastSpell(GetCaster(), SPELL_WARLOCK_DRAIN_SOUL_ENERGIZE, true);
    }

	void HandlePeriodic(AuraEffect const* /*aurEff*/)
	{
		Unit* owner = GetUnitOwner();
		Unit* caster = GetCaster();
		if (!caster || !owner)
			return;

		if (owner->HealthBelowPct(sSpellMgr->GetSpellInfo(SPELL_WARLOCK_DRAIN_SOUL)->GetEffect(EFFECT_2).BasePoints))
		{
			uint8 percent = sSpellMgr->GetSpellInfo(SPELL_WARLOCK_DRAIN_SOUL)->GetEffect(EFFECT_1).BasePoints;
			if (Aura* aura = owner->GetAura(SPELL_WARLOCK_DRAIN_SOUL, caster->GetGUID()))
				aura->GetEffect(EFFECT_0)->SetDamage(baseDamage + CalculatePct(baseDamage, percent));
		}
	}

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_warl_drain_soul::HandleApply, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE, AURA_EFFECT_HANDLE_REAL);
        OnEffectRemove += AuraEffectRemoveFn(spell_warl_drain_soul::HandleRemove, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE, AURA_EFFECT_HANDLE_REAL);
		OnEffectPeriodic += AuraEffectPeriodicFn(spell_warl_drain_soul::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE);
    }

private:
	int32 baseDamage = 0;
};

class spell_warl_glyph_of_soulwell : public SpellScriptLoader
{
public:
    spell_warl_glyph_of_soulwell() : SpellScriptLoader("spell_warl_glyph_of_soulwell") { }

    class spell_warl_glyph_of_soulwell_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_warl_glyph_of_soulwell_SpellScript);

        void HandleAfterCast()
        {
            if (!GetCaster())
                return;

            if (!GetExplTargetDest())
                return;

            if (!GetCaster()->HasAura(SPELL_WARLOCK_GLYPH_OF_SOULWELL))
                return;

            GetCaster()->CastSpell(*GetExplTargetDest(), SPELL_WARLOCK_GLYPH_OF_SOULWELL_VISUAL, true);
        }

        void Register() override
        {
            AfterCast += SpellCastFn(spell_warl_glyph_of_soulwell_SpellScript::HandleAfterCast);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_warl_glyph_of_soulwell_SpellScript();
    }
};

#define ENTRY_IMP               416
#define ENTRY_VOIDWALKER        1860
#define ENTRY_SUCCUBUS          1863
#define ENTRY_FELHUNTER         417
#define ENTRY_FELGUARD          17252
#define ENTRY_WATER_ELEMENTAL   510
#define ENTRY_TREANT            1964
#define ENTRY_FIRE_ELEMENTAL    15438
#define ENTRY_GHOUL             26125
#define ENTRY_BLOODWORM         28017

class spell_warl_metamorphosis_cost : public SpellScriptLoader
{
public:
    spell_warl_metamorphosis_cost() : SpellScriptLoader("spell_warl_metamorphosis_cost") { }

    class spell_warl_metamorphosis_cost_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_warl_metamorphosis_cost_AuraScript);

        void OnTick(const AuraEffect* /* aurEff */)
        {
            if (GetCaster())
            {
                GetCaster()->EnergizeBySpell(GetCaster(), sSpellMgr->GetSpellInfo(SPELL_WARLOCK_METAMORPHOSIS), -6, POWER_DEMONIC_FURY);
                if (GetCaster()->GetPower(POWER_DEMONIC_FURY) < 0)
                    GetCaster()->RemoveAura(GetAura());
            }

        }

        void Register() override
        {
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_warl_metamorphosis_cost_AuraScript::OnTick, EFFECT_2, SPELL_AURA_PERIODIC_DUMMY);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_warl_metamorphosis_cost_AuraScript();
    }
};

class spell_warl_molten_core_dot : public SpellScriptLoader
{
public:
    spell_warl_molten_core_dot() : SpellScriptLoader("spell_warl_molten_core_dot") { }

    class spell_warl_molten_core_dot_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_warl_molten_core_dot_AuraScript);

        void OnTick(const AuraEffect* aurEff)
        {
            if (GetCaster())
            {
                if (GetCaster()->HasAura(SPELL_WARLOCK_MOLTEN_CORE_AURA))
                    if (roll_chance_i(8))
                        GetCaster()->CastSpell(GetCaster(), SPELL_WARLOCK_MOLTEN_CORE, true);

                GetCaster()->EnergizeBySpell(GetCaster(), aurEff->GetSpellInfo(), 2, POWER_DEMONIC_FURY);
            }
        }

        void Register() override
        {
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_warl_molten_core_dot_AuraScript::OnTick, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_warl_molten_core_dot_AuraScript();
    }
};

class spell_warl_shadow_bulwark : public SpellScriptLoader
{
public:
    spell_warl_shadow_bulwark() : SpellScriptLoader("spell_warl_shadow_bulwark") { }

    class spell_warl_shadow_bulwark_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_warl_shadow_bulwark_AuraScript);

        void CalculateAmount(const AuraEffect*, int32& amount, bool &)
        {
            if (Unit* caster = GetCaster())
                amount = caster->CountPctFromMaxHealth(amount);
        }

        void Register() override
        {
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_warl_shadow_bulwark_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_MOD_INCREASE_HEALTH_2);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_warl_shadow_bulwark_AuraScript();
    }
};

class spell_warl_twilight_ward_s12 : public SpellScriptLoader
{
public:
    spell_warl_twilight_ward_s12() : SpellScriptLoader("spell_warl_twilight_ward_s12") { }

    class spell_warl_twilight_ward_s12_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_warl_twilight_ward_s12_SpellScript);

        void HandleOnHit()
        {
            if (Player* _player = GetCaster()->ToPlayer())
            {
                if (_player->HasAura(SPELL_WARLOCK_ITEM_S12_TIER_4))
                {
                    if (GetSpellInfo()->Id == 6229)
                    {
                        if (_player->HasAura(GetSpellInfo()->Id))
                            _player->RemoveAura(GetSpellInfo()->Id);

                        _player->CastSpell(_player, SPELL_WARLOCK_TWILIGHT_WARD_S12, true);
                    }
                    else if (GetSpellInfo()->Id == 104048)
                    {
                        if (_player->HasAura(GetSpellInfo()->Id))
                            _player->RemoveAura(GetSpellInfo()->Id);

                        _player->CastSpell(_player, SPELL_WARLOCK_TWILIGHT_WARD_METAMORPHOSIS_S12, true);
                    }
                }
            }
        }

        void Register() override
        {
            OnHit += SpellHitFn(spell_warl_twilight_ward_s12_SpellScript::HandleOnHit);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_warl_twilight_ward_s12_SpellScript();
    }
};

class spell_warl_void_ray : public SpellScriptLoader
{
public:
    spell_warl_void_ray() : SpellScriptLoader("spell_warl_void_ray") { }

    class spell_warl_void_ray_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_warl_void_ray_SpellScript);

        void HandleOnHit()
        {
            if (Player* _player = GetCaster()->ToPlayer())
            {
                if (Unit* target = GetHitUnit())
                {
                    if (Aura* corruption = target->GetAura(SPELL_WARLOCK_CORRUPTION, _player->GetGUID()))
                    {
                        corruption->SetDuration(corruption->GetDuration() + 4000);
                        corruption->SetNeedClientUpdateForTargets();
                    }
                }
            }
        }

        void Register() override
        {
            OnHit += SpellHitFn(spell_warl_void_ray_SpellScript::HandleOnHit);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_warl_void_ray_SpellScript();
    }
};

// Immolate - 348
class spell_warl_immolate : public SpellScriptLoader
{
public:
    spell_warl_immolate() : SpellScriptLoader("spell_warl_immolate") { }

    class spell_warl_immolate_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_warl_immolate_SpellScript);

        void HandleOnHit()
        {
            GetCaster()->CastSpell(GetHitUnit(), SPELL_WARLOCK_IMMOLATE_DOT, true);
            GetCaster()->CastSpell(GetCaster(), SPELL_WARLOCK_CHANNEL_DEMONFIRE_ACTIVATOR, true);
        }

        void Register() override
        {
            OnHit += SpellHitFn(spell_warl_immolate_SpellScript::HandleOnHit);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_warl_immolate_SpellScript();
    }
};

// Create Healthstone (Soulwell) - 34130
class spell_warl_create_healthstone_soulwell : public SpellScript
{
    PrepareSpellScript(spell_warl_create_healthstone_soulwell);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        if (!sSpellMgr->GetSpellInfo(SPELL_WARLOCK_SOULWELL_CREATE_HEALTHSTONE))
            return false;
        return true;
    }

    void HandleScriptEffect(SpellEffIndex /*effIndex*/)
    {
        GetCaster()->CastSpell(GetCaster(), 23517, true);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_warl_create_healthstone_soulwell::HandleScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
    }
};

// Call Dreadstalkers - 104316
class spell_warl_call_dreadstalkers : public SpellScript
{
    PrepareSpellScript(spell_warl_call_dreadstalkers);

    void HandleHit(SpellEffIndex /*effIndex*/)
    {
		Unit* caster = GetCaster();
		Unit* target = GetExplTargetUnit();
		if (!caster || !target)
			return;

        caster->Variables.Set("ExplicitTarget", target->GetGUID());

        caster->CastSpell(caster, SPELL_WARLOCK_CALL_DREADSTALKERS_SUMMON, true);
        caster->CastSpell(caster, SPELL_WARLOCK_CALL_DREADSTALKERS_SUMMON + 1, true);

		if (caster->HasAura(SPELL_WARLOCK_FROM_THE_SHADOWS))
			caster->CastSpell(target, SPELL_WARLOCK_FROM_THE_SHADOWS_AURA, true);

        if (Player* player = caster->ToPlayer())
            if (Pet* pet = player->GetPet())
                if (UnitAI* ai = pet->GetAI())
                    ai->AttackStart(target);

        caster->SetInCombatWith(target);
    }

    void HandleAfterCast()
    {
        if (Unit* caster = GetCaster())
        {

            if (caster->HasAura(SPELL_WARLOCK_DEMONIC_CALLING_TRIGGER))
                caster->RemoveAurasDueToSpell(SPELL_WARLOCK_DEMONIC_CALLING_TRIGGER);

            caster->RemoveAurasDueToSpell(342997); ///< Grim Inquisitor's Dread Calling
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_warl_call_dreadstalkers::HandleHit, EFFECT_0, SPELL_EFFECT_DUMMY);
        AfterCast += SpellCastFn(spell_warl_call_dreadstalkers::HandleAfterCast);
    }
};

//5782 - Fear
class spell_warl_fear : public SpellScriptLoader
{
public:
    spell_warl_fear() : SpellScriptLoader("spell_warl_fear") {}

    class spell_warl_fear_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_warl_fear_SpellScript);

        bool  Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_WARLOCK_FEAR))
                return false;
            if (!sSpellMgr->GetSpellInfo(SPELL_WARLOCK_FEAR_BUFF))
                return false;
            return true;
        }

        void HandleDummy(SpellEffIndex /*effIndex*/)
        {
            Unit* caster = GetCaster();
            if (!caster)
                return;

            Unit* target = GetExplTargetUnit();
            if (!target)
                return;

            caster->CastSpell(target, SPELL_WARLOCK_FEAR_BUFF, true);
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_warl_fear_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_warl_fear_SpellScript();
    }
};

//204730 - Fear (effect)
class spell_warl_fear_buff : public SpellScriptLoader
{
public:
    spell_warl_fear_buff() : SpellScriptLoader("spell_warl_fear_buff") {}

    class spell_warl_fear_buff_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_warl_fear_buff_SpellScript);

        bool  Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_WARLOCK_FEAR_BUFF))
                return false;
            return true;
        }

        void HandleAfterHit()
        {
            if (Aura* aura = GetHitAura())
            {
                aura->SetMaxDuration(20 * IN_MILLISECONDS);
                aura->SetDuration(20 * IN_MILLISECONDS);
                aura->RefreshDuration();
            }
        }

        void Register() override
        {
            AfterHit += SpellHitFn(spell_warl_fear_buff_SpellScript::HandleAfterHit);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_warl_fear_buff_SpellScript();
    }
};

class spell_warl_dark_pact : public AuraScript
{
    PrepareAuraScript(spell_warl_dark_pact);

    void CalculateAmount(AuraEffect const* aurEff, int32& amount, bool& /*canBeRecalculated*/)
    {
        if (Unit* caster = GetCaster())
        {
            int32 sacrifiedHealth = 0;

            if (Guardian* guardian = caster->GetGuardianPet())
            {
                sacrifiedHealth = guardian->CountPctFromCurHealth(GetSpellInfo()->GetEffect(EFFECT_1).CalcValue());
                guardian->ModifyHealth(-sacrifiedHealth);
            }
            else
            {
                sacrifiedHealth = caster->CountPctFromCurHealth(GetSpellInfo()->GetEffect(EFFECT_1).CalcValue());
                caster->ModifyHealth(-sacrifiedHealth);
            }

            amount = CalculatePct(sacrifiedHealth, aurEff->GetBaseAmount());
        }
    }

    void Register() override
    {
        DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_warl_dark_pact::CalculateAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
    }
};

//80240 - Havoc Aura / 200548 - Bane of Havoc
class spell_warl_havoc : public SpellScriptLoader
{
public:
    spell_warl_havoc() : SpellScriptLoader("spell_warl_havoc") { }

    class spell_warl_havoc_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_warl_havoc_AuraScript);

		void HandleApply(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /* mode */)
		{
			Unit* caster = GetCaster();
			Unit* target = GetTarget();
			if (!caster || !target)
				return;

			std::list<ObjectGuid> targets;
			if (caster->Variables.Exist("HAVOC_LIST"))
				targets = caster->Variables.GetValue<std::list<ObjectGuid>>("HAVOC_LIST");
			targets.push_back(target->GetGUID());
			caster->Variables.Set("HAVOC_LIST", targets);
		}

		void HandleRemove(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /* mode */)
		{
			Unit* caster = GetCaster();
			Unit* target = GetTarget();
			if (!caster || !target)
				return;

			std::list<ObjectGuid> targets;
			if (caster->Variables.Exist("HAVOC_LIST"))
			{
				targets = caster->Variables.GetValue<std::list<ObjectGuid>>("HAVOC_LIST");
				targets.remove(target->GetGUID());
                if (targets.size() == 0)
    				caster->Variables.Remove("HAVOC_LIST");
				else
					caster->Variables.Set("HAVOC_LIST", targets);
			}
		}

		void HandleProc(ProcEventInfo& eventInfo)
		{
            if (Unit* caster = GetCaster())
			    if (eventInfo.GetDamageInfo() && eventInfo.GetProcSpell() && eventInfo.GetProcSpell()->GetCaster() && eventInfo.GetDamageInfo()->GetDamage() > 0 &&
				    caster->GetGUID() == eventInfo.GetProcSpell()->GetCaster()->GetGUID())
			    {
				    uint8 reduction = 100 - sSpellMgr->GetSpellInfo(SPELL_WARLOCK_HAVOC)->GetEffect(EFFECT_0).BasePoints;
				    eventInfo.GetDamageInfo()->ModifyDamage(CalculatePct(eventInfo.GetDamageInfo()->GetDamage(), reduction) * -1);

                    if (AuraEffect* aurEff = caster->GetAuraEffect(SPELL_WARLOCK_ROLLING_HAVOC_POWER, EFFECT_0))
                        caster->CastCustomSpell(SPELL_WARLOCK_ROLLING_HAVOC_BUFF, SPELLVALUE_BASE_POINT0, aurEff->GetAmount(), caster, true);
			    }
		}

        void Register() override
        {
            OnEffectApply += AuraEffectApplyFn(spell_warl_havoc_AuraScript::HandleApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            OnEffectRemove += AuraEffectRemoveFn(spell_warl_havoc_AuraScript::HandleRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
			OnProc += AuraProcFn(spell_warl_havoc_AuraScript::HandleProc);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_warl_havoc_AuraScript();
    }
};

//146739 - Corruption
class spell_warl_corruption_effect : public AuraScript
{
    PrepareAuraScript(spell_warl_corruption_effect);

    bool  Validate(SpellInfo const* /*spellInfo*/) override
    {
        if(!sSpellMgr->GetSpellInfo(SPELL_WARLOCK_ABSOLUTE_CORRUPTION))
            return false;
        return true;
    }

    void HandleApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Unit* target = GetTarget();
        Unit* caster = GetCaster();
        if(!target || !caster)
            return;

        //If the target is a player, only cast for the time said in ABSOLUTE_CORRUPTION
        if(caster->HasAura(SPELL_WARLOCK_ABSOLUTE_CORRUPTION))
            GetAura()->SetDuration(target->GetTypeId() == TYPEID_PLAYER ? sSpellMgr->GetSpellInfo(SPELL_WARLOCK_ABSOLUTE_CORRUPTION)->GetEffect(EFFECT_0).CalcValue() * IN_MILLISECONDS : 60 * 60 * IN_MILLISECONDS); //If not player, 1 hour
    }

    /*
    Removes the aura if the caster is null, far away or dead.
    */
    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
        Unit* target = GetTarget();
        Unit* caster = GetCaster();
        if (!target)
            return;

        if(!caster)
        {
            target->RemoveAura(SPELL_WARLOCK_CORRUPTION_DAMAGE);
            return;
        }

        if(caster->isDead())
            target->RemoveAura(SPELL_WARLOCK_CORRUPTION_DAMAGE);

        if(!caster->IsInRange(target, 0, 80))
            target->RemoveAura(SPELL_WARLOCK_CORRUPTION_DAMAGE);
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_warl_corruption_effect::HandleApply, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE, AURA_EFFECT_HANDLE_REAL);
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_warl_corruption_effect::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE);
    }
};

// Rain of Fire - 5740
// AreaTriggerID - 5420
struct at_warl_rain_of_fire : AreaTriggerAI
{
    int32 timeInterval;

    at_warl_rain_of_fire(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger)
    {
        /// < CUSTOM
        timeInterval = 100;
    }

    void OnCreate() override
    {
        if (Unit* caster = at->GetCaster())
        {
            if (caster->Variables.Exist("GRIMOIRE_OF_SUPREMACY_STACK"))
            {
                caster->RemoveAura(SPELL_WARLOCK_GRIMOIRE_OF_SUPREMACY_BUFF);
                caster->CastCustomSpell(SPELL_WARLOCK_GRIMOIRE_OF_SUPREMACY_BUFF, SPELLVALUE_AURA_STACK, caster->Variables.GetValue<uint8>("GRIMOIRE_OF_SUPREMACY_STACK"), caster, true);
            }
        }
    }

    void OnUpdate(uint32 diff) override
    {
        Unit* caster = at->GetCaster();
        if (!caster || !caster->IsPlayer())
            return;

        // Check if we can handle actions
        timeInterval += diff;
        if (timeInterval < 1000)
            return;

        if(at->GetInsideUnits().size() >= 3)
            if(!caster->HasAura(SPELL_WARLOCK_ACCELERANT_BUFF))
                if(AuraEffect * aurEff = caster->GetAuraEffect(SPELL_WARLOCK_ACCELERANT_POWER, EFFECT_0))
                    caster->CastCustomSpell(SPELL_WARLOCK_ACCELERANT_BUFF, SPELLVALUE_BASE_POINT0, aurEff->GetAmount(), caster, true);

        for (auto obj : at->GetInsideUnits())
            if (Unit* unit = ObjectAccessor::GetUnit(*caster, obj))
                if (caster->IsValidAttackTarget(unit))
                    caster->CastSpell(unit, SPELL_WARLOCK_RAIN_OF_FIRE_DAMAGE, true);

        timeInterval -= 1000;
    }
};

// Bilescourge Bombers
// AreaTriggerID - 15141
struct at_warl_bilescourge_bombers : AreaTriggerAI
{
    at_warl_bilescourge_bombers(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger)
    {
        areatrigger->SetPeriodicProcTimer(500);
    }

    void OnPeriodicProc() override
    {
        if (Unit* caster = at->GetCaster())
        {
            AreaTrigger* zone = caster->GetAreaTrigger(SPELL_WARLOCK_BILESCOURGE_BOMBERS_FINISH);
            if (zone)
            {
                Position pos = caster->GetRandomPoint(zone->GetPosition(), 8);
                caster->SendPlayOrphanSpellVisual(pos, 75806, 0.5f, true);
                caster->CastSpell(pos, SPELL_WARLOCK_BILESCOURGE_MISSILE, true);
            }
        }
    }
};

// 212269 - Fel Fissure
// AreaTriggerID - 11457
struct at_warl_fel_fissure : AreaTriggerAI
{
	int32 timeInterval;

	at_warl_fel_fissure(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger)
	{}

	void OnUnitEnter(Unit* unit) override
	{
		if (Unit* caster = at->GetCaster())
			if (caster->IsValidAttackTarget(unit))
				caster->CastSpell(unit, SPELL_WARLOCK_FEL_FISSURE_EFFECT, true);
	}

	void OnUnitExit(Unit* unit) override
	{
		if (Unit* caster = at->GetCaster())
			if (unit && unit->HasAura(SPELL_WARLOCK_FEL_FISSURE_EFFECT, caster->GetGUID()))
				unit->RemoveAura(SPELL_WARLOCK_FEL_FISSURE_EFFECT, caster->GetGUID());
	}
};

// 200546 - Bane of Havoc
// AreaTriggerID - 5650
struct at_warl_bane_of_havoc: AreaTriggerAI
{
	int32 timeInterval;

	at_warl_bane_of_havoc(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger)
	{
		areatrigger->SetDuration(10 * IN_MILLISECONDS);
	}

	void OnUnitEnter(Unit* unit) override
	{
		if (Unit* caster = at->GetCaster())
			if (caster->IsValidAttackTarget(unit))
				caster->CastSpell(unit, SPELL_WARLOCK_BANE_OF_HAVOC, true);
	}

	void OnUnitExit(Unit* unit) override
	{
		if (Unit* caster = at->GetCaster())
			if (unit && unit->HasAura(SPELL_WARLOCK_BANE_OF_HAVOC, caster->GetGUID()))
				unit->RemoveAura(SPELL_WARLOCK_BANE_OF_HAVOC, caster->GetGUID());
	}
};

/// npc_demonic_gateway_purple - 59271
class spell_npc_warl_demonic_gateway_purple : public CreatureScript
{
public:
    spell_npc_warl_demonic_gateway_purple() : CreatureScript("spell_npc_warl_demonic_gateway_purple") { }

    struct spell_npc_warl_demonic_gateway_purpleAI : public CreatureAI
    {
        spell_npc_warl_demonic_gateway_purpleAI(Creature* p_Creature) : CreatureAI(p_Creature) { }

        TaskScheduler scheduler;
        uint32 ready_to_jump = 0;

        void IsSummonedBy(WorldObject* who) override
        {
            if (who)
                me->SetOrientation(who->GetOrientation());
        }

        void InitializeAI()
        {
            me->SetControlled(true, UNIT_STATE_ROOT);
            me->RemoveNpcFlag(UNIT_NPC_FLAG_SPELLCLICK);
            me->CastSpell(me, eGatewaySpells::PortalVisual, true);
            ready_to_jump = 0;

            scheduler.Schedule(500ms, [this](TaskContext context)
            {
                ready_to_jump = 1;
                me->SetInteractSpellID(eGatewaySpells::GatewayInteract);
                me->SetUnitFlag(UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_REMOVE_CLIENT_CONTROL);
                me->SetNpcFlag(UNIT_NPC_FLAG_SPELLCLICK);
                me->SetReactState(ReactStates::REACT_PASSIVE);
            });
        }

        void UpdateAI(uint32 diff) override
        {
            scheduler.Update(diff);
        }

        void OnSpellClick(Unit* p_Clicker, bool /*result*/) override
        {
            if (p_Clicker->GetTypeId() != TYPEID_PLAYER)
                return;

            // Demonic Gateway cooldown marker
            if (p_Clicker->HasAura(eGatewaySpells::CooldownMarker))
                return;

            /// Can't use gates in control
            if (p_Clicker->IsFeared())
                return;

            if (ready_to_jump == 0)
                return;

            Unit* l_Owner = me->GetOwner();
            if (!l_Owner || !l_Owner->ToPlayer())
                return;

            if (Group* l_Group = p_Clicker->ToPlayer()->GetGroup())
            {
                if (l_Owner->ToPlayer()->GetGroup() != l_Group)
                    return;
            }
            else if (l_Owner != p_Clicker)
                return;

            std::list<Creature*> l_GreenGates;
            me->GetCreatureListWithEntryInGrid(l_GreenGates, eGatewayNpc::GreenGate, 75.0f);

            if (l_GreenGates.empty())
                return;


            l_GreenGates.sort([this](const Unit* a, const Unit* b)
            {
                return a->GetDistance(me) < b->GetDistance(me);
            });
            for (auto itr : l_GreenGates)
            {
                p_Clicker->CastSpell(p_Clicker, eGatewaySpells::CooldownMarker, true);

                Unit* l_CurrentGateOwner = itr->GetOwner();

                /// Can't teleport to other players Gates
                if (l_CurrentGateOwner && l_Owner != l_CurrentGateOwner)
                    continue;

                // Init dest coordinates
                float x, y, z;
                itr->GetPosition(x, y, z);
                float speedXY;
                float speedZ = 5;

                speedXY = p_Clicker->GetExactDist2d(x, y) * 10.0f / speedZ;
                p_Clicker->CastSpell(p_Clicker, eGatewaySpells::TeleportVisualPurple, true);
                p_Clicker->GetMotionMaster()->MoveJump(x, y, z, p_Clicker->GetOrientation(), speedXY, speedZ);

                break;
            }
        }
    };

    CreatureAI* GetAI(Creature* p_Creature) const override
    {
        return new spell_npc_warl_demonic_gateway_purpleAI(p_Creature);
    }
};

/// npc_demonic_gateway_green - 59262
class spell_npc_warl_demonic_gateway_green : public CreatureScript
{
public:
    spell_npc_warl_demonic_gateway_green() : CreatureScript("spell_npc_warl_demonic_gateway_green") { }

    struct spell_npc_warl_demonic_gateway_greenAI : public CreatureAI
    {
        spell_npc_warl_demonic_gateway_greenAI(Creature* p_Creature) : CreatureAI(p_Creature) { }

        TaskScheduler scheduler;
        uint32 ready_to_jump = 0;

        void IsSummonedBy(WorldObject* who) override
        {
            if (who)
                me->SetOrientation(who->GetOrientation());
        }

        void InitializeAI()
        {
            me->SetControlled(true, UNIT_STATE_ROOT);
            me->RemoveNpcFlag(UNIT_NPC_FLAG_SPELLCLICK);
            me->CastSpell(me, eGatewaySpells::PortalVisual, true);
            ready_to_jump = 0;

            scheduler.Schedule(500ms, [this](TaskContext context)
                {
                    ready_to_jump = 1;
                    me->SetInteractSpellID(eGatewaySpells::GatewayInteract);
                    me->SetUnitFlag(UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_REMOVE_CLIENT_CONTROL);
                    me->SetNpcFlag(UNIT_NPC_FLAG_SPELLCLICK);
                    me->SetReactState(ReactStates::REACT_PASSIVE);
                });
        }

        void UpdateAI(uint32 diff) override
        {
            scheduler.Update(diff);
        }

        void OnSpellClick(Unit* p_Clicker, bool /*result*/) override
        {
            if (p_Clicker->GetTypeId() != TYPEID_PLAYER)
                return;

            if (p_Clicker->HasAura(eGatewaySpells::CooldownMarker))
                return;

            /// Can't use gates in control
            if (p_Clicker->IsFeared())
                return;

            if (ready_to_jump == 0)
                return;

            Unit* l_Owner = me->GetOwner();
            if (!l_Owner || !l_Owner->ToPlayer())
                return;

            if (Group* l_Group = p_Clicker->ToPlayer()->GetGroup())
            {
                if (l_Owner->ToPlayer()->GetGroup() != l_Group)
                    return;
            }
            else if (l_Owner != p_Clicker)
                return;

            std::list<Creature*> l_PurpleGates;
            me->GetCreatureListWithEntryInGrid(l_PurpleGates, eGatewayNpc::PurpleGate, 75.0f);

            if (l_PurpleGates.empty())
                return;

            l_PurpleGates.sort([this](const Unit* a, const Unit* b)
            {
                return a->GetDistance(me) < b->GetDistance(me);
            });

            for (auto itr : l_PurpleGates)
            {
                Unit* l_CurrentGateOwner = itr->GetOwner();

                /// Can't teleport to other players Gates
                if (l_CurrentGateOwner && l_Owner != l_CurrentGateOwner)
                    continue;

                p_Clicker->CastSpell(p_Clicker, eGatewaySpells::CooldownMarker, true);

                // Init dest coordinates
                float x, y, z;
                itr->GetPosition(x, y, z);
                float speedXY;
                float speedZ = 5;

                speedXY = p_Clicker->GetExactDist2d(x, y) * 10.0f / speedZ;
                p_Clicker->CastSpell(p_Clicker, eGatewaySpells::TeleportVisualGreen, true);
                p_Clicker->GetMotionMaster()->MoveJump(x, y, z, p_Clicker->GetOrientation(), speedXY, speedZ);

                break;
            }
        }
    };

    CreatureAI* GetAI(Creature* p_Creature) const override
    {
        return new spell_npc_warl_demonic_gateway_greenAI(p_Creature);
    }
};

// Cauterize Master - 119905
class spell_warl_cauterize_master : public SpellScriptLoader
{
public:
    spell_warl_cauterize_master() : SpellScriptLoader("spell_warl_cauterize_master") {}

    class spell_warl_cauterize_master_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_warl_cauterize_master_SpellScript);

        SpellCastResult CheckCast()
        {
            Unit* caster = GetCaster();
            if (!caster)
                return SPELL_FAILED_DONT_REPORT;
                        Guardian* pet = caster ? caster->GetGuardianPet() : nullptr;
            if (!pet)
                return SPELL_FAILED_DONT_REPORT;

            return SPELL_CAST_OK;
        }

        void HandleHit(SpellEffIndex /*effIndex*/)
        {
            Unit* caster = GetCaster();
            Guardian* pet = caster ? caster->GetGuardianPet() : nullptr;
            if (!caster || !pet)
                return;
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_warl_cauterize_master_SpellScript::HandleHit, EFFECT_0, SPELL_EFFECT_DUMMY);
            OnCheckCast += SpellCheckCastFn(spell_warl_cauterize_master_SpellScript::CheckCast);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_warl_cauterize_master_SpellScript();
    }
};

// Suffering - 119907
class spell_warl_suffering : public SpellScriptLoader
{
public:
    spell_warl_suffering() : SpellScriptLoader("spell_warl_suffering") {}

    class spell_warl_suffering_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_warl_suffering_SpellScript);

        SpellCastResult CheckCast()
        {
            Unit* caster = GetCaster();
                        Guardian* pet = caster ? caster->GetGuardianPet() : nullptr;
            if (!caster || !pet)
                return SPELL_FAILED_DONT_REPORT;

            return SPELL_CAST_OK;
        }

        void HandleHit(SpellEffIndex /*effIndex*/)
        {
            Unit* caster = GetCaster();
            Unit* target = GetHitUnit();
                        Guardian* pet = caster ? caster->GetGuardianPet() : nullptr;
            if (!caster || !pet || !target)
                return;
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_warl_suffering_SpellScript::HandleHit, EFFECT_0, SPELL_EFFECT_DUMMY);
            OnCheckCast += SpellCheckCastFn(spell_warl_suffering_SpellScript::CheckCast);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_warl_suffering_SpellScript();
    }
};

// Spell Lock - 119910
class spell_warl_spell_lock : public SpellScriptLoader
{
public:
    spell_warl_spell_lock() : SpellScriptLoader("spell_warl_spell_lock") {}

    class spell_warl_spell_lock_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_warl_spell_lock_SpellScript);

        SpellCastResult CheckCast()
        {
            Unit* caster = GetCaster();
                        Guardian* pet = caster ? caster->GetGuardianPet() : nullptr;
            if (!caster || !pet)
                return SPELL_FAILED_DONT_REPORT;

            return SPELL_CAST_OK;
        }

        void HandleHit(SpellEffIndex /*effIndex*/)
        {
            Unit* caster = GetCaster();
            Unit* target = GetHitUnit();
                        Guardian* pet = caster ? caster->GetGuardianPet() : nullptr;
            if (!caster || !pet || !target)
                return;
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_warl_spell_lock_SpellScript::HandleHit, EFFECT_0, SPELL_EFFECT_DUMMY);
            OnCheckCast += SpellCheckCastFn(spell_warl_spell_lock_SpellScript::CheckCast);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_warl_spell_lock_SpellScript();
    }
};

// Whiplash - 119909
class spell_warl_whiplash : public SpellScriptLoader
{
public:
    spell_warl_whiplash() : SpellScriptLoader("spell_warl_whiplash") {}

    class spell_warl_whiplash_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_warl_whiplash_SpellScript);

        void HandleHit()
        {
            Unit* caster = GetCaster();
            WorldLocation const* dest = GetExplTargetDest();
                        Guardian* pet = caster ? caster->GetGuardianPet() : nullptr;
            if (!caster || !pet || !dest)
                return;
        }

        SpellCastResult CheckCast()
        {
            Unit* caster = GetCaster();
                        Guardian* pet = caster ? caster->GetGuardianPet() : nullptr;
            if (!caster || !pet)
                return SPELL_FAILED_DONT_REPORT;

            return SPELL_CAST_OK;
        }

        void Register() override
        {
            OnCheckCast += SpellCheckCastFn(spell_warl_whiplash_SpellScript::CheckCast);
            OnCast += SpellCastFn(spell_warl_whiplash_SpellScript::HandleHit);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_warl_whiplash_SpellScript();
    }
};

// Felstorm - 119914
class spell_warl_felstorm : public SpellScriptLoader
{
public:
    spell_warl_felstorm() : SpellScriptLoader("spell_warl_felstorm") {}

    class spell_warl_felstorm_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_warl_felstorm_SpellScript);

        void HandleHit()
        {
            Unit* caster = GetCaster();
            if (!caster)
                return;

            caster->ToPlayer()->GetSpellHistory()->ModifyCooldown(GetSpellInfo()->Id, 45 * IN_MILLISECONDS);
        }

        SpellCastResult CheckCast()
        {
            Unit* caster = GetCaster();
                        Guardian* pet = caster ? caster->GetGuardianPet() : nullptr;
            if (!caster || !pet)
                return SPELL_FAILED_DONT_REPORT;

            return SPELL_CAST_OK;
        }

        void Register() override
        {
            OnCheckCast += SpellCheckCastFn(spell_warl_felstorm_SpellScript::CheckCast);
            OnCast += SpellCastFn(spell_warl_felstorm_SpellScript::HandleHit);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_warl_felstorm_SpellScript();
    }
};

// Meteor Strike - 171152
class spell_warl_meteor_strike : public SpellScriptLoader
{
public:
    spell_warl_meteor_strike() : SpellScriptLoader("spell_warl_meteor_strike") {}

    class spell_warl_meteor_strike_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_warl_meteor_strike_SpellScript);

        void HandleHit()
        {
            Unit* caster = GetCaster();
                        Guardian* pet = caster ? caster->GetGuardianPet() : nullptr;
            if (!caster || !pet)
                return;

        }

        SpellCastResult CheckCast()
        {
            Unit* caster = GetCaster();
                        Guardian* pet = caster ? caster->GetGuardianPet() : nullptr;
            if (!caster || !pet)
                return SPELL_FAILED_DONT_REPORT;

            return SPELL_CAST_OK;
        }

        void Register() override
        {
            OnCheckCast += SpellCheckCastFn(spell_warl_meteor_strike_SpellScript::CheckCast);
            OnCast += SpellCastFn(spell_warl_meteor_strike_SpellScript::HandleHit);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_warl_meteor_strike_SpellScript();
    }
};

// Shadow Lock - 171140
class spell_warl_shadow_lock : public SpellScriptLoader
{
public:
    spell_warl_shadow_lock() : SpellScriptLoader("spell_warl_shadow_lock") {}

    class spell_warl_shadow_lock_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_warl_shadow_lock_SpellScript);

        void HandleHit(SpellEffIndex /*effIndex*/)
        {
            Unit* caster = GetCaster();
            Unit* target = GetHitUnit();
                        Guardian* pet = caster ? caster->GetGuardianPet() : nullptr;
            if (!caster || !pet || !target)
                return;
        }

        SpellCastResult CheckCast()
        {
            Unit* caster = GetCaster();
                        Guardian* pet = caster ? caster->GetGuardianPet() : nullptr;
            if (!caster || !pet)
                return SPELL_FAILED_DONT_REPORT;

            return SPELL_CAST_OK;
        }

        void Register() override
        {
            OnCheckCast += SpellCheckCastFn(spell_warl_shadow_lock_SpellScript::CheckCast);
            OnEffectHitTarget += SpellEffectFn(spell_warl_shadow_lock_SpellScript::HandleHit, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_warl_shadow_lock_SpellScript();
    }
};

// Demonskin - 219272
class spell_warl_demonskin : public AuraScript
{
    PrepareAuraScript(spell_warl_demonskin);

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
        Unit* caster = GetCaster();
        if (!caster)
            return;

        int32 absorb = caster->CountPctFromMaxHealth(1);

        // Add remaining amount if already applied
        if (Aura* aur = caster->GetAura(SPELL_WARLOCK_SOUL_LEECH_ABSORB))
            if (AuraEffect* aurEff = aur->GetEffect(EFFECT_0))
                absorb += aurEff->GetAmount();

        int32 basePointDS = sSpellMgr->GetSpellInfo(SPELL_WARLOCK_DEMONSKIN)->GetEffect(EFFECT_1).CalcValue();
        int32 threshold = caster->CountPctFromMaxHealth(basePointDS);
        absorb = std::min(absorb, threshold);

        caster->CastCustomSpell(SPELL_WARLOCK_SOUL_LEECH_ABSORB, SPELLVALUE_BASE_POINT0, absorb, caster, TRIGGERED_FULL_MASK);
    }

	void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
	{
		if (Unit* caster = GetCaster())
			caster->RemoveAura(SPELL_WARLOCK_SOUL_LEECH_ABSORB);
	}

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_warl_demonskin::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
		OnEffectRemove += AuraEffectRemoveFn(spell_warl_demonskin::HandleRemove, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

// Cataclysm - 152108
class spell_warl_cataclysm : public SpellScriptLoader
{
public:
    spell_warl_cataclysm() : SpellScriptLoader("spell_warl_cataclysm") {}

    class spell_warl_cataclysm_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_warl_cataclysm_SpellScript);

        void HandleHit(SpellEffIndex /*effIndex*/)
        {
            Unit* caster = GetCaster();
            Unit* target = GetHitUnit();
            if (!caster || !target)
                return;
            if (!caster->ToPlayer())
                return;

            if (caster->ToPlayer()->GetSpecializationId() == TALENT_SPEC_WARLOCK_DESTRUCTION)
                caster->CastSpell(target, SPELL_WARLOCK_IMMOLATE_DOT, true);
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_warl_cataclysm_SpellScript::HandleHit, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_warl_cataclysm_SpellScript();
    }
};

// Channel Demonfire - 196447
class spell_warl_channel_demonfire : public SpellScriptLoader
{
public:
    spell_warl_channel_demonfire() : SpellScriptLoader("spell_warl_channel_demonfire") {}

    class spell_warl_channel_demonfire_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_warl_channel_demonfire_AuraScript);

        void HandlePeriodic(AuraEffect const* /*aurEff*/)
        {
            Unit* caster = GetCaster();
            if (!caster)
                return;

            std::list<Unit*> enemies;
            caster->GetAttackableUnitListInRange(enemies, 40.0f);
            enemies.remove_if(Trinity::UnitAuraCheck(false, SPELL_WARLOCK_IMMOLATE_DOT, caster->GetGUID()));
            if (enemies.empty())
                return;

            Unit* target = Trinity::Containers::SelectRandomContainerElement(enemies);
            caster->CastSpell(target, SPELL_WARLOCK_CHANNEL_DEMONFIRE, true);
        }

        void Register() override
        {
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_warl_channel_demonfire_AuraScript::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_warl_channel_demonfire_AuraScript();
    }
};

// Soul Conduit - 215941
class spell_warl_soul_conduit : public SpellScriptLoader
{
public:
    spell_warl_soul_conduit() : SpellScriptLoader("spell_warl_soul_conduit") {}

    class spell_warl_soul_conduit_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_warl_soul_conduit_AuraScript);

        int32 refund = 0;

        bool CheckProc(ProcEventInfo& eventInfo)
        {
            if (const Spell* spell = eventInfo.GetProcSpell())
                if (const SpellPowerCost* cost = spell->GetPowerCost(POWER_SOUL_SHARDS))
            {
					refund = cost->Amount / 10;
                return true;
            }

            return false;
        }

        void HandleProc(AuraEffect* /*aurEff*/, ProcEventInfo& /*eventInfo*/)
        {
            Unit* caster = GetCaster();
            if (!caster)
                return;

			for (uint8 i = 0; i < refund; i++)
				if (roll_chance_i(sSpellMgr->GetSpellInfo(SPELL_WARLOCK_SOUL_CONDUIT)->GetEffect(EFFECT_0).BasePoints))
					caster->GetScheduler().Schedule(100ms, [caster](TaskContext context)
				    {
					    caster->CastSpell(caster, SPELL_WARLOCK_SOUL_CONDUIT_ENERGIZE, true);
				    });
        }

        void Register() override
        {
            DoCheckProc += AuraCheckProcFn(spell_warl_soul_conduit_AuraScript::CheckProc);
            OnEffectProc += AuraEffectProcFn(spell_warl_soul_conduit_AuraScript::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_warl_soul_conduit_AuraScript();
    }
};

// Grimoire of Service summons - 111859, 111895, 111896, 111897, 111898
class spell_warl_grimoire_of_service : public SpellScriptLoader
{
public:
    spell_warl_grimoire_of_service() : SpellScriptLoader("spell_warl_grimoire_of_service") {}

    class spell_warl_grimoire_of_service_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_warl_grimoire_of_service_SpellScript);

        enum eServiceSpells
        {
            SPELL_IMP_SINGE_MAGIC               = 89808,
            SPELL_VOIDWALKER_SUFFERING          = 17735,
            SPELL_SUCCUBUS_SEDUCTION            = 6358,
            SPELL_FELHUNTER_SPELL_LOCK          = 19647,
            SPELL_FELGUARD_AXE_TOSS             = 89766
        };

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(eServiceSpells::SPELL_FELGUARD_AXE_TOSS) ||
                !sSpellMgr->GetSpellInfo(eServiceSpells::SPELL_FELHUNTER_SPELL_LOCK) ||
                !sSpellMgr->GetSpellInfo(eServiceSpells::SPELL_IMP_SINGE_MAGIC) ||
                !sSpellMgr->GetSpellInfo(eServiceSpells::SPELL_SUCCUBUS_SEDUCTION) ||
                !sSpellMgr->GetSpellInfo(eServiceSpells::SPELL_VOIDWALKER_SUFFERING))
                return false;
            return true;
        }

        void HandleSummon(Creature* creature)
        {
            Unit* caster = GetCaster();
            Unit* target = GetExplTargetUnit();
            if (!caster || !creature || !target)
                return;

            switch (GetSpellInfo()->Id)
            {
                case SPELL_WARLOCK_GRIMOIRE_IMP: // Imp
                    creature->CastSpell(caster, eServiceSpells::SPELL_IMP_SINGE_MAGIC, true);
                    break;
                case SPELL_WARLOCK_GRIMOIRE_VOIDWALKER: // Voidwalker
                    creature->CastSpell(target, eServiceSpells::SPELL_VOIDWALKER_SUFFERING, true);
                    break;
                case SPELL_WARLOCK_GRIMOIRE_SUCCUBUS: // Succubus
                    creature->CastSpell(target, eServiceSpells::SPELL_SUCCUBUS_SEDUCTION, true);
                    break;
                case SPELL_WARLOCK_GRIMOIRE_FELHUNTER: // Felhunter
                    creature->CastSpell(target, eServiceSpells::SPELL_FELHUNTER_SPELL_LOCK, true);
                    break;
                case SPELL_WARLOCK_GRIMOIRE_FELGUARD: // Felguard
                    creature->CastSpell(target, eServiceSpells::SPELL_FELGUARD_AXE_TOSS, true);
                    break;
            }
        }

        void Register() override
        {
            OnEffectSummon += SpellOnEffectSummonFn(spell_warl_grimoire_of_service_SpellScript::HandleSummon);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_warl_grimoire_of_service_SpellScript();
    }
};

// Grimoire of Synergy - 171975
class spell_warl_grimoire_of_synergy : public SpellScriptLoader
{
public:
    spell_warl_grimoire_of_synergy() : SpellScriptLoader("spell_warl_grimoire_of_synergy") {}

    class spell_warl_grimoire_of_synergy_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_warl_grimoire_of_synergy_SpellScript);

        void HandleCast()
        {
            Unit* caster = GetCaster();
            if (!caster)
                return;
            if (Player* player = caster->ToPlayer())
            {
                player->AddAura(GetSpellInfo()->Id, player);
                if (Guardian* pet = player->GetGuardianPet())
                    player->AddAura(GetSpellInfo()->Id, pet);
            }

        }

        void Register() override
        {
            OnCast += SpellCastFn(spell_warl_grimoire_of_synergy_SpellScript::HandleCast);
        }
    };

    class spell_warl_grimoire_of_synergy_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_warl_grimoire_of_synergy_AuraScript);

        bool CheckProc(ProcEventInfo& eventInfo)
        {
            Unit* actor = eventInfo.GetActor();
            if (!actor)
                return false;
            if (actor->IsPet() || actor->IsGuardian())
            {
                Unit* owner = actor->GetOwner();
                if (!owner)
                    return false;
                if (roll_chance_i(10))
                    owner->CastSpell(owner, SPELL_WARLOCK_GRIMOIRE_OF_SYNERGY_BUFF, true);
                return true;
            }
            if (Player* player = actor->ToPlayer())
            {
                Guardian* guardian = player->GetGuardianPet();
                if (!guardian)
                    return false;
                if (roll_chance_i(10))
                    player->CastSpell(guardian, SPELL_WARLOCK_GRIMOIRE_OF_SYNERGY_BUFF, true);
                return true;
            }
            return false;
        }

        void Register() override
        {
            DoCheckProc += AuraCheckProcFn(spell_warl_grimoire_of_synergy_AuraScript::CheckProc);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_warl_grimoire_of_synergy_AuraScript();
    }

    SpellScript* GetSpellScript() const override
    {
        return new spell_warl_grimoire_of_synergy_SpellScript();
    }
};

// 205231 - Eye Laser
class spell_warl_eye_laser : public SpellScript
{
    PrepareSpellScript(spell_warl_eye_laser);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo( { SPELL_WARLOCK_DARKGLARE_SUMMON });
    }

    void HandleHit()
    {
        if (Unit* caster = GetCaster())
            if (Unit* owner = caster->GetOwner())
            {
                // 10% of additional damage for every dot.
                auto corruptions = owner->GetTargetAuraApplications(SPELL_WARLOCK_CORRUPTION_DAMAGE);
                auto agonies = owner->GetTargetAuraApplications(SPELL_WARLOCK_AGONY);
                auto ua1 = owner->GetTargetAuraApplications(SPELL_WARLOCK_UNSTABLE_AFFLICTION_DAMAGE_1);
                auto ua2 = owner->GetTargetAuraApplications(SPELL_WARLOCK_UNSTABLE_AFFLICTION_DAMAGE_2);
                auto ua3 = owner->GetTargetAuraApplications(SPELL_WARLOCK_UNSTABLE_AFFLICTION_DAMAGE_3);
                auto ua4 = owner->GetTargetAuraApplications(SPELL_WARLOCK_UNSTABLE_AFFLICTION_DAMAGE_4);
                auto ua5 = owner->GetTargetAuraApplications(SPELL_WARLOCK_UNSTABLE_AFFLICTION_DAMAGE_5);
                auto ps = owner->GetTargetAuraApplications(SPELL_WARLOCK_PHANTOMATIC_SINGULARITY_DAMAGE);
                auto sl = owner->GetTargetAuraApplications(SPELL_WARLOCK_SIPHON_LIFE);

                uint32 baseValue = sSpellMgr->GetSpellInfo(SPELL_WARLOCK_DARKGLARE_SUMMON)->GetEffect(EFFECT_2).BasePoints;
                uint32 additionalDamage = baseValue * corruptions.size() + baseValue * agonies.size() + baseValue * ua1.size() + baseValue * ua2.size() +
                                          baseValue * ua3.size() + baseValue * ua4.size() + baseValue * ua5.size() + baseValue * ps.size() + baseValue * sl.size();

                uint32 finalDamage = GetHitDamage() + CalculatePct(GetHitDamage(), additionalDamage);
                SetHitDamage(finalDamage);
            }
    }

    void Register() override
    {
        OnHit += SpellHitFn(spell_warl_eye_laser::HandleHit);
    }
};

// Wild Imp - 143622
class npc_pet_warlock_wild_imp : public ScriptedAI
{
public:
    npc_pet_warlock_wild_imp(Creature* creature) : ScriptedAI(creature)
    {
        targetGUID = ObjectGuid::Empty;
    }

    void IsSummonedBy(WorldObject* owner) override
    {
        if (!owner)
        {
            me->DespawnOrUnsummon(0ms);
            return;
        }

        SetCombatMovement(false);

        // My slot
        if (owner->Variables.Exist("SLOT"))
            slot = owner->Variables.GetValue<uint8>("SLOT");
        else
            slot = 255;

        me->SetPowerType(Powers::POWER_ENERGY);
        me->SetMaxPower(Powers::POWER_ENERGY, 100);
        me->SetPower(Powers::POWER_ENERGY, 100);
    }

    void MovementInform(uint32 type, uint32 pointId) override
    {
        if (type != EFFECT_MOTION_TYPE)
            return;

        if (!imploding)
            return;

        Unit* owner = me->GetOwner();
        if (!owner)
            return;

        if (pointId == EVENT_JUMP)
        {
            owner->CastSpell(me->GetPosition(), SPELL_WARLOCK_IMPLOSION_DAMAGE, true);
            me->SetControlled(true, UNIT_STATE_ROOT);
            // Demonic core trigger chance.
            if (owner->HasAura(SPELL_WARLOCK_DEMONIC_CORE) && roll_chance_i(10))
            {
                // Create a dummy to cast the spell.
                // We need this because the spell doesn't work if it is casted on the Pet because the Pet is going to die before the missile arrives,
                // and if the "target" dies, the hooks don't work at all.
                TempSummon* summon = owner->SummonCreature(127816, me->GetPosition(), TEMPSUMMON_TIMED_DESPAWN, 60s);
                if (summon)
                    me->GetOwner()->CastSpell(summon, SPELL_WARLOCK_DEMONIC_CORE_PET, true);
            }
            // Current slot was freed, so make it invalid.
            slot = 255;
            me->DespawnOrUnsummon(500ms);
        }
    }

    void JustDied(Unit* /*killer*/) override
    {
        ExpiredOrDied(me->GetOwner());

        // Avoid a second call on JustUnsumoned.
        slot = 255;
    }

    void MakeSlotNotValid()
    {
        // Make slot invalid.
        slot = 255;
    }

	bool IsImploding()
	{
		return imploding;
	}

    void Implode(Unit* target, Unit* caster)
    {
        //We're on our way to implode, no need to implode again.
        if (imploding)
            return;

        if (!target)
            return;

        imploding = true;
        me->CastStop();
        // Free my slot, but only if it wasn't free before (Warlock changes position).
        if (slot != 255)
            GetVariables(caster)->WildImpSlots[slot] = false;

        // Jump to destination.
        me->CastSpell(target, SPELL_WARLOCK_IMPLOSION_JUMP, true);
    }

    void UpdateAI(uint32 diff) override
    {
        Unit* owner = me->GetOwner();
        if (!owner)
            return;

        // Out of energy.
		if (me->GetPower(POWER_ENERGY) == 0 && !expiring)
		{
			expiring = true;

			// Demonic core trigger chance.
			if (owner->HasAura(SPELL_WARLOCK_DEMONIC_CORE) && roll_chance_i(10))
			{
				// Create a dummy to cast the spell.
				// We need this because the spell doesn't work if it is casted on the Pet because the Pet is going to die before the missile arrives,
				// and if the "target" dies, the hooks don't work at all.
				TempSummon* summon = owner->SummonCreature(127816, me->GetPosition(), TEMPSUMMON_TIMED_DESPAWN, 60s);
				if (summon)
					me->GetOwner()->CastSpell(summon, SPELL_WARLOCK_DEMONIC_CORE_PET, true);
			}
			me->DespawnOrUnsummon(500ms);
		}

        // Don't update if we're are on our way to implode.
        if (imploding)
            return;

        if (me->IsInEvadeMode() && !owner->IsInCombat())
            return;

        Unit* target = GetTarget();
        ObjectGuid newtargetGUID = owner->GetTarget();
        if ((newtargetGUID.IsEmpty() || newtargetGUID == targetGUID) && (target && me->IsValidAttackTarget(target)))
        {
            CastSpellOnTarget(owner, target);
            return;
        }

        if (Unit* newTarget = ObjectAccessor::GetUnit(*me, newtargetGUID))
        {
            if (target != newTarget && me->IsValidAttackTarget(newTarget) && owner->IsInCombat())
                target = newTarget;
            CastSpellOnTarget(owner, target);
            return;
        }

        EnterEvadeMode(EVADE_REASON_NO_HOSTILES);
    }

    void JustUnsummoned() override
    {
        ExpiredOrDied(me->GetOwner());
    }

    void EnterEvadeMode(EvadeReason /*reason*/) override
    {
        if (me->IsInEvadeMode() || !me->IsAlive())
            return;

        Unit* owner = me->GetOwner();

        me->CombatStop(true);
        me->SetReactState(REACT_ASSIST);
        if (owner && !me->HasUnitState(UNIT_STATE_FOLLOW))
        {
            me->GetMotionMaster()->Clear();
            me->GetMotionMaster()->MoveFollow(owner, PET_FOLLOW_DIST, me->GetFollowAngle(), MovementSlot::MOTION_SLOT_ACTIVE);
        }
    }

private:

    Unit* GetTarget() const
    {
        return ObjectAccessor::GetUnit(*me, targetGUID);
    }

    void CastSpellOnTarget(Unit* owner, Unit* target)
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
            me->CastSpell(target, SPELL_WARLOCK_FEL_FIREBOLT, false);
        }
    }

    void ExpiredOrDied(Unit* caster)
    {
        // Owner has changed position, so now this slot is not valid anymore, don't try to release it.
        if (slot == 255)
            return;

        if (!caster)
            return;

        GetVariables(caster)->WildImpSlots[slot] = false;
    }

    ObjectGuid targetGUID;
    uint8 slot = 0;
    bool imploding = false;
	bool expiring = false;
};

// 98035 - Dreadstalker
class npc_pet_warlock_dreadstalker : public ScriptedAI
{
public:
    npc_pet_warlock_dreadstalker(Creature* creature) : ScriptedAI(creature) {}

    enum Spells
    {
        SPELL_SHARPENED_DREADFANGS              = 215111,
        SPELL_DREADSTALKER_BITE                 = 205196,
        SPELL_DREADSTALKER_BITE_MULTIPLE        = 271971,
    };

    void IsSummonedBy(WorldObject* o) override
    {
        if (!o)
            return;
        auto owner = o->ToUnit();
        if (!owner)
            return;

        targetGUID = owner->Variables.GetValue("ExplicitTarget", ObjectGuid::Empty);

        /// Grim Inquisitor's Dread Calling
        if (owner->HasAura(342997))
            owner->CastSpell(owner, 337142, true);

        me->CastSpell(me, SPELL_SHARPENED_DREADFANGS, true);
        me->GetScheduler().Schedule(100ms, [this, owner](TaskContext context)
        {
            float x, y, z;
            if (Unit* target = GetTarget())
            {
                GetTarget()->GetContactPoint(me, x, y, z, CONTACT_DISTANCE);

                JumpArrivalCastArgs arrivalCast;
                arrivalCast.SpellId = owner->HasAura(SPELL_WARLOCK_DREADLASH) ? SPELL_DREADSTALKER_BITE_MULTIPLE : SPELL_DREADSTALKER_BITE;
                arrivalCast.Target = targetGUID;
                //arrivalCast.Caster = me->GetGUID();

                me->GetMotionMaster()->MoveJump(x, y, z, 0.0f, 50, 9.5f, EVENT_JUMP, false, &arrivalCast);
            }
        });
    }

    void MovementInform(uint32 type, uint32 pointId) override
    {
        if (type != EFFECT_MOTION_TYPE)
            return;

        if (pointId == EVENT_JUMP)
        {     
            me->SetControlled(true, UNIT_STATE_ROOT);
            me->GetScheduler().Schedule(1s, 1200ms, [this](TaskContext context)
            {
                me->SetControlled(false, UNIT_STATE_ROOT);
                attack = true;
            });           
        }       
    }

    void UpdateAI(uint32 diff) override
    {
        Unit* owner = me->GetOwner();
        if (!owner || !attack)
        {
            me->CombatStop(false);
            return;
        }

        if (me->IsInEvadeMode() && !owner->IsInCombat())
            return;

        Unit* target = GetTarget();

        if (!target)
            return;

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

    void JustUnsummoned() override
    {
        Unit* owner = me->GetOwner();
        if (!owner)
            return;

        // Demonic core trigger chance.
        if (owner->HasAura(SPELL_WARLOCK_DEMONIC_CORE))
        {
            // Create a dummy to cast the spell.
            // We need this because the spell doesn't work if it is casted on the Pet because the Pet is going to die before the missile arrives,
            // and if the "target" dies, the hooks don't work at all.
            TempSummon* summon = owner->SummonCreature(127816, me->GetPosition(), TEMPSUMMON_TIMED_DESPAWN, 60s);
            if (summon)
                me->GetOwner()->CastSpell(summon, SPELL_WARLOCK_DEMONIC_CORE_PET, true);
        }

        if (Aura* aura = owner->GetAura(SPELL_WARLOCK_SHADOWS_BITE_POWER))
            owner->CastCustomSpell(SPELL_WARLOCK_SHADOWS_BITE_BUFF, SPELLVALUE_BASE_POINT0, aura->GetEffect(EFFECT_0)->GetAmount(), owner, true);
    }

    void EnterEvadeMode(EvadeReason /*reason*/) override
    {
        if (me->IsInEvadeMode() || !me->IsAlive())
            return;

        Unit* owner = me->GetOwner();

        me->CombatStop(true);
        me->SetReactState(REACT_ASSIST);
        if (owner && !me->HasUnitState(UNIT_STATE_FOLLOW))
        {
            me->GetMotionMaster()->Clear();
            me->GetMotionMaster()->MoveFollow(owner, PET_FOLLOW_DIST, me->GetFollowAngle(), MovementSlot::MOTION_SLOT_ACTIVE);
        }
    }

private:
    Unit* GetTarget() const
    {
        return ObjectAccessor::GetUnit(*me, targetGUID);
    }

    bool attack = false;
    ObjectGuid targetGUID;
};

// Demonic Tyrant - 135002
class npc_pet_warlock_demonic_tyrant : public PetAI
{
public:
	npc_pet_warlock_demonic_tyrant(Creature* creature) : PetAI(creature) {}

	void IsSummonedBy(WorldObject* o) override
	{
		if (!o)
			return;

        auto owner = o->ToUnit();
        if (!owner)
            return;

		// Demonic Consumption
		if (owner->HasAura(SPELL_WARLOCK_DEMONIC_CONSUMPTION))
		{
			int counter = 0;
			// Find every valid Wild Imp (Live and not imploding)
			std::list<TempSummon*> summons;
			owner->GetAllMinionsByEntry(summons, 143622);
            uint32 amount = 0;
			for (TempSummon* summon : summons)
			{
				if (!summon->IsAlive())
					continue;

				if (((npc_pet_warlock_wild_imp*)summon)->IsImploding())
					continue;

				if (me->GetDistance(summon) > 100)
					continue;

                amount += summon->GetPower(POWER_ENERGY) * 0.05f;
				summon->DespawnOrUnsummon();
				counter++;
			}
			if (counter > 0)
				me->CastCustomSpell(SPELL_WARLOCK_DEMONIC_CONSUMPTION_BUFF, SPELLVALUE_BASE_POINT0, amount, me, true);
		}

		// Power other demons.
		owner->CastSpell(owner, SPELL_WARLOCK_DEMONIC_POWER, true);
	}

	void UpdateAI(uint32 /*diff*/) override
	{
		Unit* owner = me->GetOwner();
		if (!owner)
			return;

        if (me->IsInEvadeMode() && !owner->IsInCombat())
			return;

		Unit* target = GetTarget();
		ObjectGuid newtargetGUID = owner->GetTarget();
		if ((newtargetGUID.IsEmpty() || newtargetGUID == _targetGUID) && (target && me->IsValidAttackTarget(target)))
		{
			CastSpellOnTarget(owner, target);
			return;
		}

		if (Unit* newTarget = ObjectAccessor::GetUnit(*me, newtargetGUID))
		{
			if (target != newTarget && me->IsValidAttackTarget(newTarget) && owner->IsInCombat())

				target = newTarget;
		CastSpellOnTarget(owner, target);
			return;
	}

        EnterEvadeMode(EVADE_REASON_NO_HOSTILES);
	}

    void JustUnsummoned() override
    {
        if (Unit* owner = me->GetOwner())
            if (Aura* aura = owner->GetAura(SPELL_WARLOCK_SUPREME_COMMANDER))
            {
                // Create a dummy to cast the spell.
                // We need this because the spell doesn't work if it is casted on the Pet because the Pet is going to die before the missile arrives,
                // and if the "target" dies, the hooks don't work at all.
                TempSummon* summon = owner->SummonCreature(127816, me->GetPosition(), TEMPSUMMON_TIMED_DESPAWN, 60s);
                if (summon)
                    me->GetOwner()->CastSpell(summon, SPELL_WARLOCK_DEMONIC_CORE_PET, true);
                owner->CastCustomSpell(SPELL_WARLOCK_SUPREME_COMMANDER_BUFF, SPELLVALUE_BASE_POINT0, aura->GetEffect(EFFECT_0)->GetAmount(), owner, true);
            }
    }

	void EnterEvadeMode(EvadeReason /*reason*/) override
	{
		if (me->IsInEvadeMode() || !me->IsAlive())
			return;

		Unit* owner = me->GetOwner();

		me->CombatStop(true);
        me->SetReactState(REACT_ASSIST);
		if (owner && !me->HasUnitState(UNIT_STATE_FOLLOW))
		{
			me->GetMotionMaster()->Clear();
			me->GetMotionMaster()->MoveFollow(owner, PET_FOLLOW_DIST, me->GetFollowAngle(), MovementSlot::MOTION_SLOT_ACTIVE);
		}
	}

private:
	Unit * GetTarget() const
	{
		return ObjectAccessor::GetUnit(*me, _targetGUID);
	}

	void CastSpellOnTarget(Unit* owner, Unit* target)
	{
		if (target && me->IsValidAttackTarget(target))
		{
			_targetGUID = target->GetGUID();
			me->SetTarget(_targetGUID);
			if (me->GetDistance(target->GetPosition()) > 40.f)
			{
				me->GetMotionMaster()->MoveChase(target);
				return;
			}
			me->CastSpell(target, SPELL_WARLOCK_DEMONFIRE, false);
		}
	}

	ObjectGuid _targetGUID;
};

// Vilefiend - 135816
class npc_pet_warlock_vilefiend : public ScriptedAI
{
    enum VilefiendSpells
    {
        SPELL_VILESPIT      = 267997,
        SPELL_HEADBUTT      = 267999,
    };

    enum VilefiendEvents
    {
        EVENT_SPIT          = 1,
        EVENT_JUMP          = 2,
        EVENT_ATTACK        = 3,
        EVENT_BUTT          = 4,
    };

public:
    npc_pet_warlock_vilefiend(Creature* creature) : ScriptedAI(creature) {}

    EventMap events;

    void IsSummonedBy(WorldObject* o) override
    {
        if (!o)
            return;

        auto owner = o->ToUnit();
        if (!owner)
            return;

                targetGUID = owner->Variables.GetValue("ExplicitTarget", ObjectGuid::Empty);
        if (targetGUID != ObjectGuid::Empty)
        {
            events.ScheduleEvent(EVENT_SPIT, 200ms, 1);
            events.ScheduleEvent(EVENT_JUMP, 1400ms, 1);
            events.ScheduleEvent(EVENT_ATTACK, 2500ms);
            events.ScheduleEvent(EVENT_BUTT, 3s);
        }
        else
            attack = true;
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

        Unit * target = GetTarget();
        while (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EVENT_SPIT:
                    if (target && me->IsValidAttackTarget(target))
                    {
                        me->SetTarget(targetGUID);
                        me->CastSpell(target, SPELL_VILESPIT, true);
                    }
                    else
					{
                        events.CancelEventGroup(1);
						attack = true;
					}
                    return;
                case EVENT_BUTT:
                    if (target && me->IsValidAttackTarget(target))
                    {
                        me->SetTarget(targetGUID);
                        me->CastSpell(target, SPELL_HEADBUTT, true);
                    }
                    events.ScheduleEvent(EVENT_BUTT, 3s);
                    return;
                case EVENT_ATTACK:
					if (target && me->IsValidAttackTarget(target))
                    attack = true;
					else
					{
						events.ScheduleEvent(EVENT_ATTACK, 1s);
						EnterEvadeMode(EVADE_REASON_NO_HOSTILES);
					}
                    break;
                case EVENT_JUMP:
                    if (target && me->IsValidAttackTarget(target))
                    {
                        float x, y, z;
                        GetTarget()->GetContactPoint(me, x, y, z, CONTACT_DISTANCE);

                        me->GetMotionMaster()->MoveJump(x, y, z, 0.0f, 50, 8, EVENT_JUMP, false);
                    }
                    else
					{
                        events.CancelEventGroup(1);
						attack = true;
					}
                    return;
            }
        }

        // Melee attack
        if (!attack)
		{
			me->CombatStop();
            return;
		}

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

    void EnterEvadeMode(EvadeReason /*reason*/) override
    {
        if (!attack)
            return;

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
    bool attack = false;
};

// -------------------
// Inner Demons Demons
// -------------------

// Eye of Guldan - 136401
class npc_pet_warlock_eye_of_guldan : public PetAI
{
public:
    npc_pet_warlock_eye_of_guldan(Creature* creature) : PetAI(creature) {}

    enum Spells
    {
        SPELL_EYE_OF_GULDAN     = 272131
    };

    void IsSummonedBy(WorldObject* o) override
    {
        if (!o)
            return;

        auto owner = o->ToUnit();
        if (!owner)
            return;

        // Save slot.
        if (owner->Variables.Exist("INNER_SLOT"))
            slot = owner->Variables.GetValue<uint8>("INNER_SLOT", 0);
    }

    void UpdateAI(uint32 /*diff*/) override
    {
        Unit* owner = me->GetOwner();
        if (!owner)
            return;

        if (me->IsInEvadeMode() && !owner->IsInCombat())
            return;

        Unit* target = GetTarget();
        ObjectGuid newtargetGUID = owner->GetTarget();
        if ((newtargetGUID.IsEmpty() || newtargetGUID == targetGUID) && (target && me->IsValidAttackTarget(target)))
        {
            CastSpellOnTarget(owner, target);
            return;
        }

        if (Unit* newTarget = ObjectAccessor::GetUnit(*me, newtargetGUID))
		{
			if (target != newTarget && me->IsValidAttackTarget(newTarget) && owner->IsInCombat())
                target = newTarget;
        CastSpellOnTarget(owner, target);
			return;
    }

        EnterEvadeMode(EVADE_REASON_NO_HOSTILES);
    }

    void JustDied(Unit* /*killer*/) override
    {
        ExpiredOrDied(me->GetOwner());

        // Avoid a second call on JustUnsumoned.
        slot = 255;
    }

    void JustUnsummoned() override
    {
        ExpiredOrDied(me->GetOwner());
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

    void CastSpellOnTarget(Unit* owner, Unit* target)
    {
        if (target && me->IsValidAttackTarget(target))
        {
            targetGUID = target->GetGUID();
            me->CastSpell(target, SPELL_EYE_OF_GULDAN, false);
        }
    }

    void ExpiredOrDied(Unit* caster)
    {
        // Owner has changed position, so now this slot is not valid anymore, don't try to release it.
        if (slot == 255)
            return;

        GetVariables(caster)->InnerDemonsSlots[slot] = false;
        // Incremement pool.
        GetVariables(caster)->InnerDemonsPool[7].Amount++;
    }

    ObjectGuid targetGUID;
    uint8 slot = 255;
};

// Bilescourge - 136404
class npc_pet_warlock_bilescourge : public PetAI
{
public:
    npc_pet_warlock_bilescourge(Creature* creature) : PetAI(creature) {}

    enum Spells
    {
        SPELL_TOXIC_VILE = 272167
    };

    void IsSummonedBy(WorldObject* o) override
    {
        if (!o)
            return;

        auto owner = o->ToUnit();
        if (!owner)
            return;

        // Save slot.
        if (owner->Variables.Exist("INNER_SLOT"))
            slot = owner->Variables.GetValue<uint8>("INNER_SLOT", 0);
    }

    void UpdateAI(uint32 /*diff*/) override
    {
        Unit* owner = me->GetOwner();
        if (!owner)
            return;

        if (me->IsInEvadeMode() && !owner->IsInCombat())
            return;

        Unit* target = GetTarget();
        ObjectGuid newtargetGUID = owner->GetTarget();
        if ((newtargetGUID.IsEmpty() || newtargetGUID == targetGUID) && (target && me->IsValidAttackTarget(target)))
        {
            CastSpellOnTarget(owner, target);
            return;
        }

        if (Unit* newTarget = ObjectAccessor::GetUnit(*me, newtargetGUID))
		{
			if (target != newTarget && me->IsValidAttackTarget(newTarget) && owner->IsInCombat())
                target = newTarget;
            CastSpellOnTarget(owner, target);
			return;
        }

        EnterEvadeMode(EVADE_REASON_NO_HOSTILES);
    }

    void JustDied(Unit* /*killer*/) override
    {
        ExpiredOrDied(me->GetOwner());

        // Avoid a second call on JustUnsumoned.
        slot = 255;
    }

    void JustUnsummoned() override
    {
        ExpiredOrDied(me->GetOwner());
    }

    void EnterEvadeMode(EvadeReason /*reason*/) override
    {
        if (me->IsInEvadeMode() || !me->IsAlive())
            return;

        Unit* owner = me->GetOwner();

        me->SetReactState(REACT_PASSIVE);
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

    void CastSpellOnTarget(Unit* owner, Unit* target)
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
            me->CastSpell(target, SPELL_TOXIC_VILE, false);
        }
    }

    void ExpiredOrDied(Unit* caster)
    {
        // Owner has changed position, so now this slot is not valid anymore, don't try to release it.
        if (slot == 255)
            return;

        GetVariables(caster)->InnerDemonsSlots[slot] = false;
        // Incremement pool.
        GetVariables(caster)->InnerDemonsPool[6].Amount++;
    }

    ObjectGuid targetGUID;
    uint8 slot = 255;
};

// Void Terror - 136403
class npc_pet_warlock_void_terror : public ScriptedAI
{
    enum Spell
    {
        SPELL_DOUBLE_BREATH = 272156,
    };

    enum Events
    {
        EVENT_DOUBLE_BREATH = 1,
    };

public:
    npc_pet_warlock_void_terror(Creature* creature) : ScriptedAI(creature) {}

    EventMap events;

    void IsSummonedBy(WorldObject* o) override
    {
        if (!o)
            return;

        auto owner = o->ToUnit();
        if (!owner)
            return;

                targetGUID = owner->Variables.GetValue("ExplicitTarget", ObjectGuid::Empty);
        if (targetGUID != ObjectGuid::Empty)
        {
            events.ScheduleEvent(EVENT_DOUBLE_BREATH, 3s);
        }
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

        Unit * target = GetTarget();
        while (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EVENT_DOUBLE_BREATH:
                    if (target && me->IsValidAttackTarget(target))
                    {
                        me->SetTarget(targetGUID);
                        me->CastSpell(target, SPELL_DOUBLE_BREATH, true);
                    }
                    events.ScheduleEvent(EVENT_DOUBLE_BREATH, 3s);
                    break;
            }
        }

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

// Illidari Satyr - 136398
class npc_pet_warlock_illidari_satyr : public ScriptedAI
{
    enum Spell
    {
        SPELL_SHADOW_SLASH = 272012,
    };

    enum Events
    {
        EVENT_SHADOW_SLASH = 1,
    };

public:
    npc_pet_warlock_illidari_satyr(Creature* creature) : ScriptedAI(creature) {}

    EventMap events;

    void IsSummonedBy(WorldObject* o) override
    {
        if (!o)
            return;

        auto owner = o->ToUnit();
        if (!owner)
            return;

                targetGUID = owner->Variables.GetValue("ExplicitTarget", ObjectGuid::Empty);
        if (targetGUID != ObjectGuid::Empty)
        {
            events.ScheduleEvent(EVENT_SHADOW_SLASH, 3s);
        }
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

        Unit * target = GetTarget();
        while (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
            case EVENT_SHADOW_SLASH:
                if (target && me->IsValidAttackTarget(target))
                {
                    me->SetTarget(targetGUID);
                    me->CastSpell(target, SPELL_SHADOW_SLASH, true);
                }
                events.ScheduleEvent(EVENT_SHADOW_SLASH, 3s);
                break;
            }
        }

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

// Darkhound - 136408
class npc_pet_warlock_darkhound : public ScriptedAI
{
    enum Spell
    {
        SPELL_FEL_BITE = 272435,
    };

    enum Events
    {
        EVENT_FEL_BITE = 1,
    };

public:
    npc_pet_warlock_darkhound(Creature* creature) : ScriptedAI(creature) {}

    EventMap events;

    void IsSummonedBy(WorldObject* o) override
    {
        if (!o)
            return;

        auto owner = o->ToUnit();
        if (!owner)
            return;

                targetGUID = owner->Variables.GetValue("ExplicitTarget", ObjectGuid::Empty);
        if (targetGUID != ObjectGuid::Empty)
        {
            events.ScheduleEvent(EVENT_FEL_BITE, 3s);
        }
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

        Unit * target = GetTarget();
        while (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
            case EVENT_FEL_BITE:
                if (target && me->IsValidAttackTarget(target))
                {
                    me->SetTarget(targetGUID);
                    me->CastSpell(target, SPELL_FEL_BITE, true);
                }
                events.ScheduleEvent(EVENT_FEL_BITE, 3s);
                break;
            }
        }

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

// Viciuos Hellhound - 136399
class npc_pet_warlock_viciuos_hellhound : public ScriptedAI
{
    enum Spell
    {
        SPELL_DEMON_FANGS = 272435,
    };

    enum Events
    {
        EVENT_DEMON_FANGS = 1,
    };

public:
    npc_pet_warlock_viciuos_hellhound(Creature* creature) : ScriptedAI(creature) {}

    EventMap events;

    void IsSummonedBy(WorldObject* o) override
    {
        if (!o)
            return;

        auto owner = o->ToUnit();
        if (!owner)
            return;

                targetGUID = owner->Variables.GetValue("ExplicitTarget", ObjectGuid::Empty);
        if (targetGUID != ObjectGuid::Empty)
        {
            events.ScheduleEvent(EVENT_DEMON_FANGS, 3s);
        }
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

        Unit * target = GetTarget();
        while (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
            case EVENT_DEMON_FANGS:
                if (target && me->IsValidAttackTarget(target))
                {
                    me->SetTarget(targetGUID);
                    me->CastSpell(target, SPELL_DEMON_FANGS, true);
                }
                events.ScheduleEvent(EVENT_DEMON_FANGS, 3s);
                break;
            }
        }

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

// Ursul - 136402
class npc_pet_warlock_ursul: public ScriptedAI
{
    enum Spell
    {
        SPELL_MANY_FACED_BITES = 272439,
    };

    enum Events
    {
        EVENT_MANY_FACED_BITES = 1,
    };

public:
    npc_pet_warlock_ursul(Creature* creature) : ScriptedAI(creature) {}

    EventMap events;
    void IsSummonedBy(WorldObject* o) override
    {
        if (!o)
            return;

        auto owner = o->ToUnit();
        if (!owner)
            return;

                targetGUID = owner->Variables.GetValue("ExplicitTarget", ObjectGuid::Empty);
        if (targetGUID != ObjectGuid::Empty)
        {
            events.ScheduleEvent(EVENT_MANY_FACED_BITES, 3s);
        }
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

        Unit * target = GetTarget();
        while (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
            case EVENT_MANY_FACED_BITES:
                if (target && me->IsValidAttackTarget(target))
                {
                    me->SetTarget(targetGUID);
                    me->CastSpell(target, SPELL_MANY_FACED_BITES, true);
                }
                events.ScheduleEvent(EVENT_MANY_FACED_BITES, 3s);
                break;
            }
        }

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

// Shivarra - 136406
class npc_pet_warlock_shivarra : public ScriptedAI
{
    enum Spell
    {
        SPELL_MULTISTRIKE = 272172,
    };

    enum Events
    {
        EVENT_MULTISTRIKE = 1,
    };

public:
    npc_pet_warlock_shivarra(Creature* creature) : ScriptedAI(creature) {}

    EventMap events;

    void IsSummonedBy(WorldObject* o) override
    {
        if (!o)
            return;

        auto owner = o->ToUnit();
        if (!owner)
            return;

                targetGUID = owner->Variables.GetValue("ExplicitTarget", ObjectGuid::Empty);
        if (targetGUID != ObjectGuid::Empty)
        {
            events.ScheduleEvent(EVENT_MULTISTRIKE, 3s);
        }
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

        Unit * target = GetTarget();
        while (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
            case EVENT_MULTISTRIKE:
                if (target && me->IsValidAttackTarget(target))
                {
                    me->SetTarget(targetGUID);
                    me->CastSpell(target, SPELL_MULTISTRIKE, true);
                }
                events.ScheduleEvent(EVENT_MULTISTRIKE, 3s);
                break;
            }
        }

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

// Wrathguard - 136407
class npc_pet_warlock_wrathguard : public ScriptedAI
{
    enum Spell
    {
        SPELL_OVERHEAD_ASSAULT = 272432,
    };

    enum Events
    {
        EVENT_OVERHEAD_ASSAULT = 1,
    };

public:
    npc_pet_warlock_wrathguard(Creature* creature) : ScriptedAI(creature) {}

    EventMap events;

    void IsSummonedBy(WorldObject* o) override
    {
        if (!o)
            return;

        auto owner = o->ToUnit();
        if (!owner)
            return;

                targetGUID = owner->Variables.GetValue("ExplicitTarget", ObjectGuid::Empty);
        if (targetGUID != ObjectGuid::Empty)
        {
            events.ScheduleEvent(EVENT_OVERHEAD_ASSAULT, 3s);
        }
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

        Unit * target = GetTarget();
        while (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
            case EVENT_OVERHEAD_ASSAULT:
                if (target && me->IsValidAttackTarget(target))
                {
                    me->SetTarget(targetGUID);
                    me->CastSpell(target, SPELL_OVERHEAD_ASSAULT, true);
                }
                events.ScheduleEvent(EVENT_OVERHEAD_ASSAULT, 3s);
                break;
            }
        }

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

// Prince Malchezzar - 136397
class npc_pet_warlock_prince_malchezzar : public ScriptedAI
{
public:
    npc_pet_warlock_prince_malchezzar(Creature* creature) : ScriptedAI(creature) {}

    void IsSummonedBy(WorldObject* o) override
    {
        if (!o)
            return;

        auto owner = o->ToUnit();
        if (!owner)
            return;

                targetGUID = owner->Variables.GetValue("ExplicitTarget", ObjectGuid::Empty);
        Talk(0);
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

// Fel Lord - 107024
class npc_pet_warlock_fel_lord : public ScriptedAI
{
	enum Spells
	{
		SPELL_CLEAVE = 213688
	};

public:
	npc_pet_warlock_fel_lord(Creature* creature) : ScriptedAI(creature) {}

    void IsSummonedBy(WorldObject* o) override
    {
        if (!o)
            return;

        auto owner = o->ToUnit();
        if (!owner)
            return;

		me->SetControlled(true, UNIT_STATE_ROOT);
	}

	void UpdateAI(uint32 /*diff*/) override
	{
		if (me->HasUnitState(UNIT_STATE_CASTING))
			return;

		me->CastSpell(me, SPELL_CLEAVE, false);
	}
};

// Infernal - 89
class npc_pet_warlock_infernal : public ScriptedAI
{
	enum Spells
	{
		SPELL_INMOLATION		= 19483,
		SPELL_EMBERS			= 264364
	};

public:
	npc_pet_warlock_infernal(Creature* creature) : ScriptedAI(creature)
    {
        m_Timer = 250;
    }

    void IsSummonedBy(WorldObject* o) override
    {
        if (!o)
            return;

        auto owner = o->ToUnit();
        if (!owner)
            return;

        if (Aura* aura = owner->GetAura(SPELL_WARLOCK_CRASHING_CHAOS))
            owner->CastCustomSpell(SPELL_WARLOCK_CRASHING_CHAOS_BUFF, SPELLVALUE_BASE_POINT0, aura->GetEffect(EFFECT_0)->GetAmount(), owner, true);

		        targetGUID = owner->Variables.GetValue("ExplicitTarget", ObjectGuid::Empty);
		owner->AddAura(SPELL_INMOLATION, me);
		owner->AddAura(SPELL_EMBERS, me);
		owner->CastSpell(owner, SPELL_EMBERS, true);
	}

	void UpdateAI(uint32 diff) override
	{
        if (m_Timer <= diff)
        {
            DoActions();
            m_Timer = 250;
        }
        else
        {
            m_Timer -= diff;
        }
	}

	void JustDied(Unit* /*killer*/) override
	{
		if (Unit* owner = me->GetOwner())
		{
			owner->RemoveAura(SPELL_EMBERS);
			owner->RemoveAura(SPELL_WARLOCK_GRIMOIRE_OF_SUPREMACY_BUFF);
            if (owner->Variables.Exist("GRIMOIRE_OF_SUPREMACY_STACK"))
                owner->Variables.Remove("GRIMOIRE_OF_SUPREMACY_STACK");
		}
	}

	void JustUnsummoned() override
	{
		if (Unit* owner = me->GetOwner())
		{
			owner->RemoveAura(SPELL_EMBERS);
			owner->RemoveAura(SPELL_WARLOCK_GRIMOIRE_OF_SUPREMACY_BUFF);
            if (owner->Variables.Exist("GRIMOIRE_OF_SUPREMACY_STACK"))
                owner->Variables.Remove("GRIMOIRE_OF_SUPREMACY_STACK");
		}
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

    void DoActions()
    {
        Unit* owner = me->GetOwner();
        if (!owner)
            return;

        if (me->IsInEvadeMode() && !owner->IsInCombat())
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

private:
	Unit * GetTarget() const
	{
		return ObjectAccessor::GetUnit(*me, targetGUID);
	}

	ObjectGuid targetGUID;
    uint32 m_Timer;
};

// Observer - 107100
class npc_pet_warlock_observer: public ScriptedAI
{
public:
    npc_pet_warlock_observer(Creature* creature) : ScriptedAI(creature) {}

    void IsSummonedBy(WorldObject* o) override
    {
        if (!o)
            return;

        auto owner = o->ToUnit();
        if (!owner)
            return;

        me->SetDisableGravity(true);
        me->SetHover(true);
        me->SetReactState(REACT_PASSIVE);
    }

    void UpdateAI(uint32 /*diff*/) override
    {
        EnterEvadeMode(EVADE_REASON_NO_HOSTILES);
    }

    void EnterEvadeMode(EvadeReason /*reason*/) override
    {
        if (me->IsInEvadeMode() || !me->IsAlive())
            return;

        me->CombatStop(false);
    }
};

// Doomguard - 11859
class npc_pet_warlock_doomguard : public ScriptedAI
{
public:
    npc_pet_warlock_doomguard(Creature* creature) : ScriptedAI(creature) {}

    void IsSummonedBy(WorldObject* o) override
    {
        if (!o)
            return;

        auto owner = o->ToUnit();
        if (!owner)
            return;

        me->SetObjectScale(2.f);
        me->Relocate(owner->GetPositionX() + 1, owner->GetPositionY() + 1, owner->GetPositionZ(), me->GetOrientation());
    }

    void UpdateAI(uint32 /*diff*/) override
    {
        Unit* owner = me->GetOwner();
        if (!owner)
            return;

        if (me->IsInEvadeMode() && !owner->IsInCombat())
            return;

        Unit* target = GetTarget();
        ObjectGuid newtargetGUID = owner->GetTarget();
        if ((newtargetGUID.IsEmpty() || newtargetGUID == _targetGUID) && (target && me->IsValidAttackTarget(target)))
        {
            CastSpellOnTarget(owner, target);
            return;
        }

        if (Unit* newTarget = ObjectAccessor::GetUnit(*me, newtargetGUID))
        {
            if (target != newTarget && me->IsValidAttackTarget(newTarget) && owner->IsInCombat())

                target = newTarget;
            CastSpellOnTarget(owner, target);
            return;
        }

        EnterEvadeMode(EVADE_REASON_NO_HOSTILES);
    }

    void EnterEvadeMode(EvadeReason /*reason*/) override
    {
        if (me->IsInEvadeMode() || !me->IsAlive())
            return;

        Unit* owner = me->GetOwner();

        me->CombatStop(true);
        me->SetReactState(REACT_ASSIST);
        if (owner && !me->HasUnitState(UNIT_STATE_FOLLOW))
        {
            me->GetMotionMaster()->Clear();
            me->GetMotionMaster()->MoveFollow(owner, PET_FOLLOW_DIST, me->GetFollowAngle(), MovementSlot::MOTION_SLOT_ACTIVE);
        }
    }

private:
    Unit * GetTarget() const
    {
        return ObjectAccessor::GetUnit(*me, _targetGUID);
    }

    void CastSpellOnTarget(Unit* owner, Unit* target)
    {
        if (target && me->IsValidAttackTarget(target))
        {
            _targetGUID = target->GetGUID();
            me->SetTarget(_targetGUID);
            if (me->GetDistance(target->GetPosition()) > 30.f)
            {
                me->GetMotionMaster()->MoveChase(target);
                return;
            }
            me->CastSpell(target, SPELL_WARLOCK_DOOM_BOLT, false);
        }
    }

    ObjectGuid _targetGUID;
};

// Demonic Calling - 205145
class spell_warl_demonic_calling : public SpellScriptLoader
{
public:
    spell_warl_demonic_calling() : SpellScriptLoader("spell_warl_demonic_calling") {}

    class spell_warl_demonic_calling_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_warl_demonic_calling_AuraScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_WARLOCK_DEMONIC_CALLING_TRIGGER))
                return false;
            return true;
        }

        bool CheckProc(ProcEventInfo& eventInfo)
        {
            Unit* caster = GetCaster();
            if (!caster)
                return false;
            if (eventInfo.GetSpellInfo() && (eventInfo.GetSpellInfo()->Id == SPELL_WARLOCK_DEMONBOLT || eventInfo.GetSpellInfo()->Id == SPELL_WARLOCK_SHADOW_BOLT) && roll_chance_i(20))
                caster->CastSpell(caster, SPELL_WARLOCK_DEMONIC_CALLING_TRIGGER, true);
            return false;
        }

        void Register() override
        {
            DoCheckProc += AuraCheckProcFn(spell_warl_demonic_calling_AuraScript::CheckProc);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_warl_demonic_calling_AuraScript();
    }
};

// Eradication - 196414
class spell_warl_eradication : public SpellScriptLoader
{
public:
    spell_warl_eradication() : SpellScriptLoader("spell_warl_eradication") {}

    class spell_warl_eradication_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_warl_eradication_AuraScript);

        bool CheckProc(ProcEventInfo& /*eventInfo*/)
        {
            return false;
        }

        void Register() override
        {
            DoCheckProc += AuraCheckProcFn(spell_warl_eradication_AuraScript::CheckProc);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_warl_eradication_AuraScript();
    }
};

// 205179 - Phantom Singularity
class aura_warl_phantomatic_singularity : public AuraScript
{
    PrepareAuraScript(aura_warl_phantomatic_singularity);

    void OnTick(const AuraEffect* /*aurEff*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetTarget();
        if (!caster || !target)
            return;

        caster->CastSpell(target, SPELL_WARLOCK_PHANTOMATIC_SINGULARITY_DAMAGE, true);
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(aura_warl_phantomatic_singularity::OnTick, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

// Incinerate - 29722
class spell_warl_incinerate : public SpellScript
{
    PrepareSpellScript(spell_warl_incinerate);

    void DoEffectHitTarget(SpellEffIndex /*effIndex*/)
    {
		Unit* caster = GetCaster();
        Unit* explTarget = GetExplTargetUnit();
        Unit* hitUnit = GetHitUnit();
        if (!caster || !explTarget || !hitUnit)
            return;

        if (explTarget != hitUnit)
			if (Aura* brimStoneAura = caster->GetAura(SPELL_WARLOCK_FIRE_AND_BRIMSTONE))
				if (AuraEffect const* eff0 = brimStoneAura->GetEffect(EFFECT_0))
				{
					int32 damage = CalculatePct(GetHitDamage(), eff0->GetAmount());
					SetHitDamage(damage);
					if (AuraEffect const* eff1 = brimStoneAura->GetEffect(EFFECT_1))
						caster->CastCustomSpell(SPELL_WARLOCK_INCINERATE_ENERGIZE, SPELLVALUE_BASE_POINT0, eff1->GetAmount(), caster, TRIGGERED_FULL_MASK);
					return;
				}

        caster->CastSpell(GetCaster(), SPELL_WARLOCK_INCINERATE_ENERGIZE, true);
        if (IsHitCrit())
            caster->CastCustomSpell(SPELL_WARLOCK_INCINERATE_ENERGIZE, SPELLVALUE_BASE_POINT0, 1, caster, TRIGGERED_FULL_MASK);

        if (caster->HasAura(Warlock::eLegendary::EmbersOfTheDiaboticRaiment))
            caster->CastSpell(GetCaster(), SPELL_WARLOCK_INCINERATE_ENERGIZE, true);
    }

    void FilterTargets(std::list<WorldObject*>& targets)
    {
		Unit* caster = GetCaster();
		Unit* explTarget = GetExplTargetUnit();
		if (!caster || !explTarget)
			return;

		if (!GetCaster()->HasAura(SPELL_WARLOCK_FIRE_AND_BRIMSTONE))
		{
			targets.clear();
			targets.push_back(explTarget);
            // Process pending Havoc targets.
			if (havocTargets.size() > 0)
				for (ObjectGuid guid : havocTargets)
					if (guid != explTarget->GetGUID())
						if (Unit* target = ObjectAccessor::GetUnit(*caster, guid))
                            if (caster->IsValidAttackTarget(target))
								targets.push_back(target);
		}
    }

	void HandleAfterCast()
	{
		if (Unit* caster = GetCaster())
		{
			if (Aura* aura = caster->GetAura(SPELL_WARLOCK_BACKDRAFT))
				aura->ModStackAmount(-1);

            caster->RemoveAurasDueToSpell(SPELL_WARLOCK_CHAOTIC_INFERNO_PROC);
		}
	}

	void HandlePrepare()
	{
        if (Unit* caster = GetCaster())
			if (caster->Variables.Exist("HAVOC_LIST"))
				havocTargets = caster->Variables.GetValue<std::list<ObjectGuid>>("HAVOC_LIST");
	}

    void Register() override
    {
		OnPrepare += SpellOnPrepareFn(spell_warl_incinerate::HandlePrepare);
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_warl_incinerate::FilterTargets, EFFECT_1, TARGET_UNIT_DEST_AREA_ENEMY);
        OnEffectHitTarget += SpellEffectFn(spell_warl_incinerate::DoEffectHitTarget, EFFECT_1, SPELL_EFFECT_SCHOOL_DAMAGE);
		AfterCast += SpellCastFn(spell_warl_incinerate::HandleAfterCast);
    }

private:
	std::list<ObjectGuid> havocTargets;
};

// Darkglare - 103673
class npc_pet_warlock_darkglare : public PetAI
{
public:
    npc_pet_warlock_darkglare(Creature* creature) : PetAI(creature) {}

    void UpdateAI(uint32 /*diff*/) override
    {
        Unit* owner = me->GetOwner();
        if (!owner)
            return;

        if (me->IsInEvadeMode() && !owner->IsInCombat())
            return;

        Unit* target = GetTarget();
        ObjectGuid newtargetGUID = owner->GetTarget();
        if ((newtargetGUID.IsEmpty() || newtargetGUID == _targetGUID) && (target && me->IsValidAttackTarget(target)))
        {
            CastSpellOnTarget(owner, target);
            return;
        }

        if (Unit* newTarget = ObjectAccessor::GetUnit(*me, newtargetGUID))
        {
            if (target != newTarget && me->IsValidAttackTarget(newTarget) && owner->IsInCombat())
                target = newTarget;
            CastSpellOnTarget(owner, target);
            return;
        }

        EnterEvadeMode(EVADE_REASON_NO_HOSTILES);
    }

    void DamageDealt(Unit* /*victim*/, uint32& damage, DamageEffectType /*damageType*/, SpellInfo const* /*spellInfo = nullptr*/) override
    {
        Unit* owner = me->GetOwner();
        if (!owner)
            return;

        uint32 baseDamageMultiplier = 10;

        auto ownedAuras = owner->GetOwnedAurasByTypes({ SPELL_AURA_PERIODIC_DAMAGE, SPELL_AURA_PERIODIC_DAMAGE_PERCENT });

        if (!ownedAuras.empty())
            AddPct(damage, ownedAuras.size() * baseDamageMultiplier);
    }

    void EnterEvadeMode(EvadeReason /*reason*/) override
    {
        if (me->IsInEvadeMode() || !me->IsAlive())
            return;

        Unit* owner = me->GetOwner();

        me->CombatStop(true);
        me->SetReactState(REACT_ASSIST);
        if (owner && !me->HasUnitState(UNIT_STATE_FOLLOW))
        {
            me->GetMotionMaster()->Clear();
            me->GetMotionMaster()->MoveFollow(owner, PET_FOLLOW_DIST, me->GetFollowAngle(), MovementSlot::MOTION_SLOT_ACTIVE);
        }
    }

private:
    Unit* GetTarget() const
    {
        return ObjectAccessor::GetUnit(*me, _targetGUID);
    }

    void CastSpellOnTarget(Unit* owner, Unit* target)
    {
        if (target && me->IsValidAttackTarget(target))
        {
            _targetGUID = target->GetGUID();
			me->SetTarget(_targetGUID);
            if (me->GetDistance(target->GetPosition()) > 40.f)
            {
                me->GetMotionMaster()->MoveChase(target);
                return;
            }
            if (!me->GetSpellHistory()->HasCooldown(SPELL_WARLOCK_DARKGLARE_EYE_BEAM))
            {
                me->CastSpell(target, SPELL_WARLOCK_DARKGLARE_EYE_BEAM);
                me->GetSpellHistory()->AddCooldown(SPELL_WARLOCK_DARKGLARE_EYE_BEAM, 0, 20ms);
            }
        }
    }

    ObjectGuid _targetGUID;
};

// Hand of Gul'Dan - 105174
class spell_warl_hand_of_guldan : public SpellScriptLoader
{
public:
    spell_warl_hand_of_guldan() : SpellScriptLoader("spell_warl_hand_of_guldan") { }

    class spell_warl_hand_of_guldan_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_warl_hand_of_guldan_SpellScript);

        void HandleTakePower(SpellPowerCost& powerCost)
        {
            if (Unit* caster = GetCaster())
                GetVariables(caster)->souldShards = (powerCost.Amount / 10) > 3 ? 3 : (powerCost.Amount / 10);

            // Demonic Meteor
            if (Unit* caster = GetCaster())
            {
                if (Aura* aura = caster->GetAura(SPELL_WARLOCK_DEMONIC_METEOR))
                {
                    if (AuraEffect* aurEff = aura->GetEffect(EFFECT_1))
                    {
                        uint8 chance = GetVariables(caster)->souldShards * aurEff->GetBaseAmount();
                        if (roll_chance_i(chance))
                            caster->EnergizeBySpell(caster, sSpellMgr->GetSpellInfo(SPELL_WARLOCK_DEMONIC_METEOR), 10, POWER_SOUL_SHARDS);
                    }
                }
            }
        }

        void HandleOnHit(SpellEffIndex /*effIndex*/)
        {
            if (Unit* caster = GetCaster())
            {
                if (Unit* target = GetHitUnit())
                {
                    if (roll_chance_i(15) && caster->HasAura(Warlock::eLegendary::ForcesOfTheHornedNightmare))
                        caster->CastSpell(target, Warlock::eDemonology::HandOfGuldan, true);

                    // Check if the Warlock has change position since last Hand of Guldan.
                    if ((std::abs(caster->GetPositionX() - GetVariables(caster)->LastPosition.GetPositionX()) >= 1 || std::abs(caster->GetPositionY() - GetVariables(caster)->LastPosition.GetPositionY()) >= 1) ||
                        abs(GetVariables(caster)->LastOrientation - caster->GetOrientation()) >= M_PI / 6)
                    {
                        // Free all slots
                        for (uint8 i = 0; i < 16; i++)
                            GetVariables(caster)->WildImpSlots[i] = false;

                        caster->GetScheduler().CancelGroup(1);

                        // Make current Wild Imp's slots invalid.
                        std::list<TempSummon*> imps;
                        caster->GetAllMinionsByEntry(imps, 143622);
                        for (TempSummon* summon : imps)
                            if (summon && summon->IsAlive() && summon->AI())
                                ((npc_pet_warlock_wild_imp*)summon->GetAI())->MakeSlotNotValid();

                        // Outer positions.
                        for (uint8 i = 0; i < 8; ++i)
                        {
                            float x, y;
                            if (i < 4)
                                GetPositionWithDistInOrientation(caster, 2.8f, (float)((M_PI / 4 + M_PI / 2 * i) + caster->GetOrientation()), x, y);
                            else
                                GetPositionWithDistInOrientation(caster, 3.1f, (float)(M_PI / 2 * (i - 4) + caster->GetOrientation()), x, y);
                            GetVariables(caster)->positions[i] = Position(x, y, caster->GetPosition().m_positionZ);
                        }
                        // Inner positions
                        for (uint8 i = 8; i < 16; ++i)
                        {
                            float x, y;
                            if (i < 12)
                                GetPositionWithDistInOrientation(caster, 1.5f, (float)((M_PI / 4 + M_PI / 2 * (i - 8)) + caster->GetOrientation()), x, y);
                            else
                                GetPositionWithDistInOrientation(caster, 1.8f, (float)(M_PI / 2 * (i - 12) + caster->GetOrientation()), x, y);
                            GetVariables(caster)->positions[i] = Position(x, y, caster->GetPosition().m_positionZ);
                        }

                        // Update last position and orientation.
                        GetVariables(caster)->LastPosition = caster->GetPosition();
                        GetVariables(caster)->LastOrientation = caster->GetOrientation();
                    }

                    // Find free slot and spawn Wild Imp.
                    summons = 0;
                    for (uint8 i = 0; i < 16; i++)
                    {
                        if (!GetVariables(caster)->WildImpSlots[i] && summons < GetVariables(caster)->souldShards)
                        {
                            GetVariables(caster)->WildImpSlots[i] = true;
                            Position pos = GetVariables(caster)->positions[i];
                            ObjectGuid targetGuid = target->GetGUID();
                            caster->GetScheduler().Schedule(200ms * summons, [targetGuid, pos, i, this](TaskContext context)
                            {
                                if (Unit* caster = GetContextUnit())
                                {
                                    if (Unit* target = ObjectAccessor::GetCreature(*caster, targetGuid))
                                        target->SendPlayOrphanSpellVisual(pos, 76813, 45);

                                    caster->GetScheduler().Schedule(250ms * summons, [pos, i](TaskContext context)
                                    {
                                        // Save slot.
                                        if (Unit* caster = GetContextUnit())
                                        {
                                            caster->Variables.Set<uint8>("SLOT", i);
                                            caster->CastSpell(pos, SPELL_WARLOCK_HAND_OF_GULDAN_SUMMON, true);
                                        }
                                    });
                                }
                            });
                            summons++;
                        }
                    }

                    // If we can't find a free slot, just spawn the Wild Imp at random point.
                    for (uint8 i = 0; i < GetVariables(caster)->souldShards - summons; i++)
                    {
                        float x, y, z;
                        caster->GetRandomContactPoint(caster, x, y, z, outerRadius + 4.5f, outerRadius + 5.5f);
                        // Don't need slot position for this one.
                        caster->Variables.Set<uint8>("SLOT", 255);
                        Position pos = Position(x, y, z, caster->GetOrientation());
                        ObjectGuid targetGUID = target->GetGUID();
                        ObjectGuid casterGUID = caster->GetGUID();
                        caster->GetScheduler().Schedule(200ms * summons, [targetGUID, pos, casterGUID, this](TaskContext context)
                        {
                            if (Unit* caster = ObjectAccessor::GetUnit(*context.GetUnit(), casterGUID))
                            {
                                if (Unit* target = ObjectAccessor::GetUnit(*context.GetUnit(), targetGUID))
                                {
                                    target->SendPlayOrphanSpellVisual(pos, 76813, 45);
                                    caster->GetScheduler().Schedule(250ms * summons, [pos, casterGUID](TaskContext context)
                                    {
                                        if (Unit* caster = ObjectAccessor::GetUnit(*context.GetUnit(), casterGUID))
                                            caster->CastSpell(pos, SPELL_WARLOCK_HAND_OF_GULDAN_SUMMON, true);
                                    });
                                }
                            }

                        });
                        summons++;
                    }

                    // Make AOE damage.
                    caster->CastSpell(target, SPELL_WARLOCK_HAND_OF_GULDAN_DAMAGE, true);
                }
            }
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_warl_hand_of_guldan_SpellScript::HandleOnHit, EFFECT_0, SPELL_EFFECT_DUMMY);
            OnTakePower += SpellOnTakePowerFn(spell_warl_hand_of_guldan_SpellScript::HandleTakePower);
        }

        uint8 summons = 0;
        const uint8 moveThreshold = 1;
        const float outerRadius = 3.0f;
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_warl_hand_of_guldan_SpellScript();
    }
};

// 196277 - Implosion
class spell_warl_implosion : public SpellScriptLoader
{
public:
    spell_warl_implosion() : SpellScriptLoader("spell_warl_implosion") {}

    class spell_warl_implosion_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_warl_implosion_SpellScript);

        SpellCastResult CheckWildImps()
        {
            Unit* caster = GetCaster();
            if (!caster)
                return SPELL_FAILED_DONT_REPORT;

            std::list<TempSummon*> imps;
            caster->GetAllMinionsByEntry(imps, 143622);
            if (imps.size() == 0)
                return SPELL_FAILED_DONT_REPORT;

                    return SPELL_CAST_OK;
            }

        void HandleHit(SpellEffIndex /*effIndex*/)
        {
            Unit* caster = GetCaster();
            Unit* target = GetHitUnit();
            if (!caster || !target)
                return;

            auto casterguid = caster->GetGUID();
            auto targetguid = target->GetGUID();

            // Select all the Wild Imps.
            std::list<TempSummon*> imps;
            caster->GetAllMinionsByEntry(imps, 143622);

            if (imps.size() > 0)
            {
                UnitList list;
                for (TempSummon* summon : imps)
                    list.push_back(summon->ToUnit());

                SortByDistanceTo(target, list);
                for (auto unit : list)
                {
                    if (unit && unit->GetAI())
                    {
                        auto unitGuid = unit->GetGUID();
                        unit->GetScheduler().Schedule(200ms * count, [targetguid, casterguid, unitGuid](TaskContext context)
                        {
                            auto unit = context.GetUnit();
                            if (auto caster = ObjectAccessor::GetUnit(*unit, casterguid))
                                if (auto target = ObjectAccessor::GetUnit(*unit, targetguid))
                                    ((npc_pet_warlock_wild_imp*)unit->GetAI())->Implode(target, caster);
                        });
                        count++;
                    }
                }
            }
        }

        void Register() override
        {
            OnCheckCast += SpellCheckCastFn(spell_warl_implosion_SpellScript::CheckWildImps);
            OnEffectHitTarget += SpellEffectFn(spell_warl_implosion_SpellScript::HandleHit, EFFECT_0, SPELL_EFFECT_DUMMY);
        }

    private:
        uint8 count = 0;
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_warl_implosion_SpellScript();
    }
};

// 205146 - Demonic Call Proc
class aura_war_demonic_call_proc : public AuraScript
{
    PrepareAuraScript(aura_war_demonic_call_proc);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_war_demonic_call_proc::CheckProc);
    }
};

// 264057 - Soul Strike
class spell_war_soul_strike : public SpellScript
{
    PrepareSpellScript(spell_war_soul_strike);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_WARLOCK_SOUL_STRIKE_ENERGIZE, SPELL_WARLOCK_SOUL_STRIKE_DAMAGE });
    }

    SpellCastResult CheckCast()
    {
        Pet* pet = GetCaster()->ToPlayer()->GetPet();
        if (!pet)
            return SPELL_FAILED_NO_PET;

        Unit* petTarget = pet->GetVictim();
        if (!petTarget)
            petTarget = GetExplTargetUnit();

        if (pet && pet->GetEntry() != 17252)
            return SPELL_FAILED_CANT_DO_THAT_RIGHT_NOW;
        if (pet && pet->HasAura(SPELL_WARLOCK_FELGUARD_FELSTORM))
            return SPELL_FAILED_CANT_DO_THAT_RIGHT_NOW;
        // pet has a target and target is within 8 yards and target is in line of sight
        if (!petTarget || !pet->IsWithinDist(petTarget, 8.f, true) || !petTarget->IsWithinLOSInMap(pet))
            return SPELL_FAILED_DONT_REPORT;

        if (pet->HasAuraType(SPELL_AURA_MOD_STUN) || pet->HasAuraType(SPELL_AURA_MOD_CONFUSE) || pet->HasAuraType(SPELL_AURA_MOD_SILENCE) ||
            pet->HasAuraType(SPELL_AURA_MOD_FEAR) || pet->HasAuraType(SPELL_AURA_MOD_FEAR_2))
            return SPELL_FAILED_CANT_DO_THAT_RIGHT_NOW;

        return SPELL_CAST_OK;
    };

    void HandleAfterCast()
    {
        if (Unit* caster = GetCaster())
            caster->CastSpell(caster, SPELL_WARLOCK_SOUL_STRIKE_ENERGIZE, true);
    }

    void HandleHit()
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();

        if (!target || !caster)
            return;

        if (caster->ToPlayer())
        {
            if (Pet* pet = caster->ToPlayer()->GetPet())
            {
                int32 damage = caster->GetTotalSpellPowerValue(SPELL_SCHOOL_MASK_SHADOW, false) * 0.35f;
                pet->CastCustomSpell(SPELL_WARLOCK_SOUL_STRIKE_DAMAGE, SPELLVALUE_BASE_POINT0, damage, target, true);

                // The Felguard should attack this unit.
                if (caster->IsValidAttackTarget(target))
                    if (UnitAI* ai = pet->GetAI())
                        ai->AttackStart(target);
            }

            caster->SetInCombatWith(target);
        }
    }

    void Register() override
    {
        AfterCast += SpellCastFn(spell_war_soul_strike::HandleAfterCast);
        OnHit += SpellHitFn(spell_war_soul_strike::HandleHit);
        OnCheckCast += SpellCheckCastFn(spell_war_soul_strike::CheckCast);
    }
};

// 264130 - Power Siphon
class spell_war_power_siphon : public SpellScript
{
    PrepareSpellScript(spell_war_power_siphon);

    SpellCastResult CheckCast()
    {
        if (Unit* caster = GetCaster())
        {
            std::list<TempSummon*> imps;
            caster->GetAllMinionsByEntry(imps, 143622);
            if (imps.size() < 2)
                return SPELL_FAILED_DONT_REPORT;

            return SPELL_CAST_OK;
        }
        return SPELL_FAILED_ERROR;
    }

    void HandleHit()
    {
        if (Unit* caster = GetCaster())
        {
            std::list<TempSummon*> imps;
            caster->GetAllMinionsByEntry(imps, 143622);
            if (imps.size() < 2)
                return;

            imps.remove_if([](TempSummon* summon)
            {
                return (!summon->IsAlive());
            });
            if (imps.size() > 2)
                Trinity::Containers::RandomResize(imps, 2);

            for (TempSummon* imp : imps)
            {
                // Create a dummy to cast the spell.
                // We need this because the spell doesn't work if it is casted on the Pet because the Pet is going to die before the missile arrives,
                // and if the "target" dies, the hooks don't work at all.
                TempSummon* summon = caster->SummonCreature(127816, imp->GetPosition(), TEMPSUMMON_TIMED_DESPAWN, 60s);
                if (summon)
                    caster->CastSpell(summon, SPELL_WARLOCK_DEMONIC_CORE_PET, true);
                imp->DespawnOrUnsummon(500ms);
        }
    }
    }

    void Register() override
    {
        OnCheckCast += SpellCheckCastFn(spell_war_power_siphon::CheckCast);
        OnHit += SpellHitFn(spell_war_power_siphon::HandleHit);
    }
};

// 108558 - Nightfall
class aura_war_nightfall : public AuraScript
{
	PrepareAuraScript(aura_war_nightfall);

	bool CheckProc(ProcEventInfo& eventInfo)
	{
		if (eventInfo.GetDamageInfo() && eventInfo.GetDamageInfo()->GetSpellInfo() && eventInfo.GetDamageInfo()->GetSpellInfo()->Id == SPELL_WARLOCK_CORRUPTION_DAMAGE)
			return true;

		return false;
	}

	void HandleProc(ProcEventInfo& eventInfo)
	{
		if (Unit* caster = GetCaster())
			caster->CastSpell(caster, SPELL_WARLOCK_NIGHTFALL_PROC, true);
	}

	void Register() override
	{
		DoCheckProc += AuraCheckProcFn(aura_war_nightfall::CheckProc);
		OnProc += AuraProcFn(aura_war_nightfall::HandleProc);
	}
};

// 264571 - Nightfall Proc
class aura_war_nightfall_proc : public AuraScript
{
	PrepareAuraScript(aura_war_nightfall_proc);

	bool CheckProc(ProcEventInfo& eventInfo)
	{
		return false;
	}

	void Register() override
	{
		DoCheckProc += AuraCheckProcFn(aura_war_nightfall_proc::CheckProc);
	}
};

// Cremation Aura Damage 212327
//Last Update 8.0.1 Build 28153
class spell_warl_cremation_damage : public SpellScript
{
    PrepareSpellScript(spell_warl_cremation_damage);

    void HandleOnHitTarget(SpellEffIndex /*effIndex*/)
    {
        if (Unit* caster = GetCaster())
        {
            if (Unit* target = GetHitUnit())
            {
                if (SpellInfo const* spellInfo = GetSpellInfo())
                {
                    //if (SpellEffectInfo const* effect1 = spellInfo->GetEffect(EFFECT_1))
                    {
                        int32 damage = CalculatePct(target->IsPlayer() ? target->GetMaxHealth() : caster->GetMaxHealth(), spellInfo->GetEffect(EFFECT_1).BasePoints);
                        SetHitDamage(damage);
                    }
                }
            }
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_warl_cremation_damage::HandleOnHitTarget, EFFECT_0, SPELL_EFFECT_DAMAGE_FROM_MAX_HEALTH_PCT);
    }
};

// Sacrificial Pact - 108416
class spell_warl_sacrificial_pact : public SpellScriptLoader
{
public:
    spell_warl_sacrificial_pact() : SpellScriptLoader("spell_warl_sacrificial_pact") { }

    class spell_warl_sacrificial_pact_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_warl_sacrificial_pact_AuraScript);

        void CalculateAmount(AuraEffect const* aurEff, int32& amount, bool& /*canBeRecalculated*/)
        {
            if (Unit* caster = GetCaster())
            {
                int32 sacrifiedHealth = 0;
               
                sacrifiedHealth = caster->CountPctFromCurHealth(GetSpellInfo()->GetEffect(EFFECT_1).BasePoints);
                caster->ModifyHealth(-sacrifiedHealth);

                amount = CalculatePct(sacrifiedHealth, GetSpellInfo()->GetEffect(EFFECT_2).BasePoints);
               
            }
        }

        void Register()
        {
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_warl_sacrificial_pact_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_warl_sacrificial_pact_AuraScript();
    }
};

// 17877 - Shadowburn
class spell_warl_shadowburn : public SpellScript
{
    PrepareSpellScript(spell_warl_shadowburn);

    void HandleOnHitTarget(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        if (!caster)
            return;

        caster->CastSpell(caster, SPELL_WARLOCK_SHADOWBURN_ENERGIZE, true);
    }
    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_warl_shadowburn::HandleOnHitTarget, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

// 17877 - Shadowburn Aura
class aura_warl_shadowburn : public AuraScript
{
    PrepareAuraScript(aura_warl_shadowburn);

    void HandleRemove(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /* mode */)
    {
        Unit* caster = GetCaster();
        Unit* target = GetTarget();
        if (!caster || !target)
            return;

        if (Player* player = caster->ToPlayer())
            if (GetTargetApplication()->GetRemoveMode() == AURA_REMOVE_BY_DEATH && player->isHonorOrXPTarget(target))
                player->GetSpellHistory()->RestoreCharge(sSpellMgr->GetSpellInfo(SPELL_WARLOCK_SHADOWBURN)->ChargeCategoryId);
       
    }

    void Register() override
    {       
        OnEffectRemove += AuraEffectApplyFn(aura_warl_shadowburn::HandleRemove, EFFECT_1, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

//Entrenched in Flame -  233581  V.8.0.1
class spell_warl_entrenched_in_flame_aura : public AuraScript
{
    PrepareAuraScript(spell_warl_entrenched_in_flame_aura);    

    bool OnCheckProc(ProcEventInfo& eventInfo)  {
        return eventInfo.GetProcSpell()->GetSpellInfo()->Id == SPELL_WARLOCK_CONFLAGRATE;        
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_warl_entrenched_in_flame_aura::OnCheckProc);       
    }
};

// 265273 - Demonic Power
class aura_war_demonic_power : public AuraScript
{
	PrepareAuraScript(aura_war_demonic_power);

	void HandleApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
	{
		Unit* caster = GetCaster();
		Unit* target = GetUnitOwner();
		if (!caster || !target)
			return;

		for (Unit::ControlList::iterator itr = caster->m_Controlled.begin(); itr != caster->m_Controlled.end(); ++itr)
		{
			Unit* unit = *itr;
			// 135002 - Tyrant shouldn't take the buff.
			if (unit->IsAlive() && unit->GetCreatureType() == CREATURE_TYPE_DEMON && unit->GetEntry() != 135002)
			{
				// Damage
				unit->AddAura(SPELL_WARLOCK_DEMONIC_POWER);

                // 8.0.1 - Demons from Inner Demons and Nether Portal don't benifit from extended duration.
				TempSummon* summon = unit->ToTempSummon();
				if (summon && !summon->IsPet() && IsValidExtendDemon(summon->GetEntry()))
					summon->ExtendLifetime(sSpellMgr->GetSpellInfo(SPELL_WARLOCK_DEMONIC_POWER)->GetEffect(EFFECT_2).BasePoints);
			}
		}
	}

	void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
	{
		Unit* caster = GetCaster();
		Unit* target = GetUnitOwner();
		if (!caster || !target)
			return;

		// If the Warlock removes the aura, every pet looses the aura too.
		for (Unit::ControlList::iterator itr = caster->m_Controlled.begin(); itr != caster->m_Controlled.end(); ++itr)
		{
			Unit* unit = *itr;
			if (unit->HasAura(SPELL_WARLOCK_DEMONIC_POWER))
				unit->RemoveAura(SPELL_WARLOCK_DEMONIC_POWER);
		}
	}

	void Register() override
	{
		OnEffectApply += AuraEffectApplyFn(aura_war_demonic_power::HandleApply, EFFECT_1, 429, AURA_EFFECT_HANDLE_REAL);
		OnEffectRemove += AuraEffectRemoveFn(aura_war_demonic_power::HandleRemove, EFFECT_1, 429, AURA_EFFECT_HANDLE_REAL);
	}

private:
    bool IsValidExtendDemon(uint32 entry)
    {
        if (entry == 136397 || entry == 136407 || entry == 136406 || entry == 136402 || entry == 136399 || entry == 136408 || entry == 136403 ||
            entry == 136398 || entry == 136404 || entry == 136401)
            return false;
        return true;
    }
};

// 270171 - Demonic Core
class spell_war_demonic_core : public SpellScript
{
	PrepareSpellScript(spell_war_demonic_core);

	void HandleHit()
	{
		Unit* caster = GetCaster();
		Unit* target = GetExplTargetUnit();
		if (!caster || !target)
			return;

		caster->CastSpell(caster, SPELL_WARLOCK_DEMONIC_CORE_BUFF, true);
		target->ToCreature()->DespawnOrUnsummon();
	}

	void Register() override
	{
		OnHit += SpellHitFn(spell_war_demonic_core::HandleHit);
	}
};

// 271971 - Dreadbite AOE
class spell_war_dreadbite_aoe : public SpellScript
{
    PrepareSpellScript(spell_war_dreadbite_aoe);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_WARLOCK_DREADLASH });
    }

    void HandleEffectHit(SpellEffIndex /*effIndex*/)
    {
		if (Unit* caster = GetCaster())
			if (Unit* owner = caster->GetOwner())
			{
				int32 damage = owner->GetTotalSpellPowerValue(SPELL_SCHOOL_MASK_SHADOW, false) * 0.375;
				SetHitDamage(damage + CalculatePct(damage, sSpellMgr->GetSpellInfo(SPELL_WARLOCK_DREADLASH)->GetEffect(EFFECT_0).BasePoints));
    }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_war_dreadbite_aoe::HandleEffectHit, EFFECT_0, SPELL_EFFECT_APPLY_AURA);
    }
};

// 267171 - Demonic Strength
class spell_war_demonic_strength : public SpellScript
{
    PrepareSpellScript(spell_war_demonic_strength);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_WARLOCK_FELGUARD_FELSTORM,  SPELL_WARLOCK_FELGUARD_CHARGE });
    }

    SpellCastResult CheckCast()
    {
        if (Unit* caster = GetCaster())
        {
            if (!caster->GetGuardianPet())
                return SPELL_FAILED_NO_PET;

            if (caster->GetGuardianPet()->GetEntry() != 17252)
                return SPELL_FAILED_CANT_DO_THAT_RIGHT_NOW;

            if (caster->GetGuardianPet()->HasAura(SPELL_WARLOCK_FELGUARD_FELSTORM))
                return SPELL_FAILED_CANT_DO_THAT_RIGHT_NOW;

            return SPELL_CAST_OK;
        }
        return SPELL_FAILED_ERROR;
    }

    void HandleHit()
    {
        Unit* caster = GetCaster();
        Unit* target = GetExplTargetUnit();
        if (!caster || !target)
            return;

        if (auto pet = caster->GetGuardianPet())
        {
            caster->SetInCombatWith(target);
            pet->SetInCombatWith(target);

            // Charge to target.
            if (pet->GetSpellHistory()->HasCooldown(SPELL_WARLOCK_FELGUARD_CHARGE))
                pet->GetSpellHistory()->ResetCooldown(SPELL_WARLOCK_FELGUARD_CHARGE, true);
            pet->CastSpell(target, SPELL_WARLOCK_FELGUARD_CHARGE, true);
            if (pet->AI())
                pet->GetAI()->AttackStart(target);
            // Then release a Felstorm.
            pet->GetScheduler().Schedule(500ms, [](TaskContext context)
            {
                if (context.GetUnit()->GetSpellHistory()->HasCooldown(SPELL_WARLOCK_FELGUARD_FELSTORM))
                    context.GetUnit()->GetSpellHistory()->ResetCooldown(SPELL_WARLOCK_FELGUARD_FELSTORM, true);
                context.GetUnit()->CastSpell(context.GetUnit(), SPELL_WARLOCK_FELGUARD_FELSTORM, true);
            });
        }
    }

    void Register() override
    {
        OnCheckCast += SpellCheckCastFn(spell_war_demonic_strength::CheckCast);
        OnHit += SpellHitFn(spell_war_demonic_strength::HandleHit);
    }
};

// 89751 - Felstorm
class aura_war_felstorm : public AuraScript
{
    PrepareAuraScript(aura_war_felstorm);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_WARLOCK_DEMONIC_STRENGTH });
    }

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* owner = GetUnitOwner())
            if (owner->HasAura(SPELL_WARLOCK_DEMONIC_STRENGTH))
                owner->RemoveAura(SPELL_WARLOCK_DEMONIC_STRENGTH);
    }

    void Register() override
    {
        OnEffectRemove += AuraEffectRemoveFn(aura_war_felstorm::HandleRemove, EFFECT_1, 264, AURA_EFFECT_HANDLE_REAL);
    }
};

// 89753 - Felstorm Damage
class spell_war_felstorm_damage : public SpellScript
{
    PrepareSpellScript(spell_war_felstorm_damage);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_WARLOCK_DEMONIC_STRENGTH });
    }

    void HandletHit(SpellEffIndex /*effIndex*/)
    {
        if (Unit* caster = GetCaster())
            if (caster->HasAura(SPELL_WARLOCK_DEMONIC_STRENGTH))
                SetHitDamage(GetHitDamage() + CalculatePct(GetHitDamage(), sSpellMgr->GetSpellInfo(SPELL_WARLOCK_DEMONIC_STRENGTH)->GetEffect(EFFECT_1).BasePoints));
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_war_felstorm_damage::HandletHit, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

// Demonic Circle Talent Learn
class spell_warl_demonic_circle_talent : public PlayerScript {
public:
    spell_warl_demonic_circle_talent() : PlayerScript("spell_warl_demonic_circle_talent") {}

    enum Used_Demonic_Circle_Spells {
        SPELL_WAR_DEMONIC_CIRCLE            = 48018,
        SPELL_WAR_DEMONIC_CIRCLE_TELEPORT   = 48020,
        TALENT_WAR_SPELL_DEMONIC_CIRCLE     = 268358

    };

    void OnSpellLearned (Player* p_Player, uint32 p_SpellID)
    {        
        if (p_SpellID == TALENT_WAR_SPELL_DEMONIC_CIRCLE && p_Player) {
            p_Player->LearnSpell(SPELL_WAR_DEMONIC_CIRCLE, false);
            p_Player->LearnSpell(SPELL_WAR_DEMONIC_CIRCLE_TELEPORT, false);
        }
    }

    void OnSpellRemoved(Player* p_Player, uint32 p_SpellID)
    {
        if (p_SpellID == TALENT_WAR_SPELL_DEMONIC_CIRCLE && p_Player) {
            p_Player->RemoveSpell(SPELL_WAR_DEMONIC_CIRCLE, false);
            p_Player->RemoveSpell(SPELL_WAR_DEMONIC_CIRCLE_TELEPORT, false);
        }
    }
};

// Casting Circle - 116011
// AreaTriggerID - 221703
struct at_war_casting_circle: AreaTriggerAI
{
    at_war_casting_circle(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger) { } 


    void OnUnitEnter(Unit* unit) override
    {
        if (Unit* caster = at->GetCaster())
            if (unit->GetGUID() == caster->GetGUID())
                caster->CastSpell(unit, SPELL_WARLOCK_CASTING_CIRCLE_AURA, true);
    }

    void OnUnitExit(Unit* unit) override
    {
        if (unit->HasAura(SPELL_WARLOCK_CASTING_CIRCLE_AURA))
            unit->RemoveAurasDueToSpell(SPELL_WARLOCK_CASTING_CIRCLE_AURA);
    }
};

//Unending Resolve - 104773   V.8.0.1
class spell_warl_unending_resolve_aura : public AuraScript
{
    PrepareAuraScript(spell_warl_unending_resolve_aura);

    void HandleApply(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /* mode */)
    {
        if (Unit* caster = GetCaster())
            if (caster && caster->HasAura(SPELL_WARLOCK_CASTING_CIRCLE_AURA))
                PreventDefaultAction();
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_warl_unending_resolve_aura::HandleApply, EFFECT_0, SPELL_AURA_MECHANIC_IMMUNITY, AURA_EFFECT_HANDLE_REAL);
    }
};

// 86040 - Hand of Guldan Damage
class spell_war_hand_of_guldan_damage : public SpellScript
{
    enum UmbralBlazeSpells
    {
        SPELL_UMBRAL_BLAZE_POWER = 273523,
        SPELL_UMBRAL_BLAZE_DAMAGE = 273526,
    };

	PrepareSpellScript(spell_war_hand_of_guldan_damage);

	void HandleEffectHit(SpellEffIndex /*effIndex*/)
	{
		SetHitDamage(GetHitDamage() * 3);

        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        if (Aura* aura = caster->GetAura(SPELL_UMBRAL_BLAZE_POWER))
            if (roll_chance_i(15))
                caster->CastCustomSpell(SPELL_UMBRAL_BLAZE_DAMAGE, SPELLVALUE_BASE_POINT0, aura->GetEffect(EFFECT_0)->GetAmount(), target, true);
	}

	void Register() override
	{
		OnEffectHitTarget += SpellEffectFn(spell_war_hand_of_guldan_damage::HandleEffectHit, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
	}
};

// 264119 - Summon Vilefiend
class spell_war_summon_vilefiend : public SpellScript
{
    PrepareSpellScript(spell_war_summon_vilefiend);

    void HandlePrepare()
    {
        if (Unit* caster = GetCaster())
		{
            caster->Variables.Remove("ExplicitTarget");
            if (caster->GetTarget() != ObjectGuid::Empty)
            {
                if (auto target = ObjectAccessor::GetUnit(*caster, caster->GetTarget()))
                    caster->SetInCombatWith(target);

                caster->Variables.Set("ExplicitTarget", caster->GetTarget());
            }
			Position pos = caster->GetPosition();
			caster->MovePositionToFirstCollision(pos, 5.0f, (float)-M_PI / 4);
			pos = Position(pos.GetPositionX(), pos.GetPositionY() - 1.5f, pos.GetPositionZ(), caster->GetOrientation());
			caster->SendPlayOrphanSpellVisual(pos, 81019, 100);
    }
    }

    void Register() override
    {
        OnPrepare += SpellOnPrepareFn(spell_war_summon_vilefiend::HandlePrepare);
    }
};

// 108370 - Soul Leech
class spell_war_soul_leech : public SpellScript
{
    PrepareSpellScript(spell_war_soul_leech);

    void HandleOnHit(SpellEffIndex /*effIndex*/)
    {
        if (Unit* caster = GetCaster())
            caster->AddAura(SPELL_WARLOCK_SOUL_LEECH);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_war_soul_leech::HandleOnHit, EFFECT_0, 202);
    }
};

// 267216 - Inner Demons / 267218 - Nether Portal
class aura_war_inner_demons : public AuraScript
{
    PrepareAuraScript(aura_war_inner_demons);

    enum InnerDemonSummons
	{
        SPELL_PRINCE_MALCHEZZAR     = 267986,
        SPELL_WRATHGUARD            = 267995,
        SPELL_SHIVARRA              = 267994,
        SPELL_URSUL                 = 268001,
        SPELL_VICIUS_HELLHOUND      = 267988,
        SPELL_DARKHOUND             = 267996,
        SPELL_DARKTERROR            = 267991,
        SPELL_ILLIDARI_SATYR        = 267987,
        SPELL_BILESCOURGE           = 267992,
        SPELL_EYE_OF_GULDAN         = 267989
    };

    void HandleApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        // Inner Demons instantly create a Wild Imp. After that, it begins to tick every 10 seconds.
        if (Unit* caster = GetCaster())
        {
            if (!caster->IsAlive() || caster->IsFlying() || caster->IsInFlight())
                return;

            // Calculate the positions.
            // This always spawn the first Wild Imp at the same position, because when the Aura is remove, the Inner Demons imps are also remove.
            float x, y;
            GetPositionWithDistInOrientation(caster, 2.2f, (float)((M_PI / 2) + caster->GetOrientation()), x, y);

            // Summon and alternate position.
            GetVariables(caster)->InnerLeft = true;
            caster->CastSpell(Position(x, y, caster->GetPosition().m_positionZ), SPELL_WARLOCK_HAND_OF_GULDAN_SUMMON, true);
            // Initialice pool
            InitialicePool(caster);
	    }

    }

    void OnTick(AuraEffect const* /*aurEff*/)
    {
        if (Unit* caster = GetCaster())
        {
            if (!caster->IsAlive())
                return;

            // We gonna use Hand of Guldan positions if we're in combat.
            // or alternate position if we're not in combat.
            if (!caster->IsInCombat())
            {
                // Calculate the positions.
                float x, y;
                GetPositionWithDistInOrientation(caster, 2.2f, (float)((!GetVariables(caster)->InnerLeft) ? (M_PI / 2) : (3 * M_PI / 2) + caster->GetOrientation()), x, y);
                caster->CastSpell(Position(x, y, caster->GetPosition().m_positionZ), SPELL_WARLOCK_HAND_OF_GULDAN_SUMMON, true);
            }
            else
            {
				// Check if the Warlock has change position.
				if ((std::abs(caster->GetPositionX() - GetVariables(caster)->LastPosition.GetPositionX()) >= 1 || std::abs(caster->GetPositionY() - GetVariables(caster)->LastPosition.GetPositionY()) >= 1) ||
					abs(GetVariables(caster)->LastOrientation - caster->GetOrientation()) >= M_PI / 6)
				{
					// Free all slots
					for (uint8 i = 0; i < 16; i++)
                        GetVariables(caster)->WildImpSlots[i] = false;

					caster->GetScheduler().CancelGroup(1);

					// Make current Wild Imp's slots invalid.
					std::list<TempSummon*> imps;
					caster->GetAllMinionsByEntry(imps, 143622);
					for (TempSummon* summon : imps)
						if (summon && summon->IsAlive() && summon->AI())
							((npc_pet_warlock_wild_imp*)summon->GetAI())->MakeSlotNotValid();

					// Outer positions.
					for (uint8 i = 0; i < 8; ++i)
					{
						float x, y;
						if (i < 4)
							GetPositionWithDistInOrientation(caster, 2.8f, (float)((M_PI / 4 + M_PI / 2 * i) + caster->GetOrientation()), x, y);
						else
							GetPositionWithDistInOrientation(caster, 3.1f, (float)(M_PI / 2 * (i - 4) + caster->GetOrientation()), x, y);
                        GetVariables(caster)->positions[i] = Position(x, y, caster->GetPosition().m_positionZ);
					}
					// Inner positions
					for (uint8 i = 8; i < 16; ++i)
					{
						float x, y;
						if (i < 12)
							GetPositionWithDistInOrientation(caster, 1.5f, (float)((M_PI / 4 + M_PI / 2 * (i - 8)) + caster->GetOrientation()), x, y);
						else
							GetPositionWithDistInOrientation(caster, 1.8f, (float)(M_PI / 2 * (i - 12) + caster->GetOrientation()), x, y);
                        GetVariables(caster)->positions[i] = Position(x, y, caster->GetPosition().m_positionZ);
					}

					// Update last position and orientation.
					GetVariables(caster)->LastPosition = caster->GetPosition();
					GetVariables(caster)->LastOrientation = caster->GetOrientation();
				}

                bool spawned = false;
                for (uint8 i = 0; i < 16; i++)
                {
                    if (!GetVariables(caster)->WildImpSlots[i])
                    {
                        GetVariables(caster)->WildImpSlots[i] = true;
                        Position pos = GetVariables(caster)->positions[i];
                        caster->Variables.Set<uint8>("SLOT", i);
                        caster->CastSpell(pos, SPELL_WARLOCK_HAND_OF_GULDAN_SUMMON, true);
                        spawned = true;
                        break;
                    }
                }
                // We couldn't find a valid position. Spawn the Imp outside.
                if (!spawned)
                {
                    float x, y, z;
                    caster->GetRandomContactPoint(caster, x, y, z, 4.5f, 5.5f);
                    // Don't need slot position for this one.
                    caster->Variables.Set<uint8>("SLOT", 255);
                    Position pos = Position(x, y, z, caster->GetOrientation());
                    caster->CastSpell(pos, SPELL_WARLOCK_HAND_OF_GULDAN_SUMMON, true);
                }
            }

                // Alternate anyway.
            GetVariables(caster)->InnerLeft = !GetVariables(caster)->InnerLeft;

            // We need target.
            Unit* target = ObjectAccessor::GetUnit(*caster, caster->GetTarget());
            if (!target)
                return;

            // Inner Demons only triggers big demons if we are in combat.
            if (caster->IsInCombat() && roll_chance_i(sSpellMgr->GetSpellInfo(SPELL_WARLOCK_INNER_DEMONS)->GetEffect(EFFECT_0).BasePoints))
                HandleSpawnDemon(caster, target);
        }
    }

    void HandleProc(ProcEventInfo& eventInfo)
            {
        if (!eventInfo.GetSpellInfo())
            return;

        if (Unit* caster = GetCaster())
        {
            // We need target.
            Unit* target = ObjectAccessor::GetUnit(*caster, caster->GetTarget());
            if (!target)
                return;

            for (auto powerCost : eventInfo.GetSpellInfo()->PowerCosts)
                if (powerCost->PowerType == POWER_SOUL_SHARDS)
                {
                    HandleSpawnDemon(caster, target);
                    break;
                }
        }
    }

    void Register() override
    {
        OnProc += AuraProcFn(aura_war_inner_demons::HandleProc);
        OnEffectApply += AuraEffectApplyFn(aura_war_inner_demons::HandleApply, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY, AURA_EFFECT_HANDLE_REAL);
        OnEffectPeriodic += AuraEffectPeriodicFn(aura_war_inner_demons::OnTick, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }

    // Initialice pool.
    void InitialicePool(Unit* caster)
    {
        GetVariables(caster)->InnerDemonsPool[0] = InnerDemonPoolEntry(267986, 1, 3);         // Prince Malchezzar
        GetVariables(caster)->InnerDemonsPool[2] = InnerDemonPoolEntry(267994, 1, 5);         // Shivarra
        GetVariables(caster)->InnerDemonsPool[1] = InnerDemonPoolEntry(267995, 1, 6.5f);      // Wrathguard
        GetVariables(caster)->InnerDemonsPool[3] = InnerDemonPoolEntry(268001, 1, 7.5);       // Ursul
        GetVariables(caster)->InnerDemonsPool[4] = InnerDemonPoolEntry(267988, 1, 9);         // Vicius Hellhound
        GetVariables(caster)->InnerDemonsPool[5] = InnerDemonPoolEntry(267996, 1, 11.5);      // Darkhound
        GetVariables(caster)->InnerDemonsPool[6] = InnerDemonPoolEntry(267991, 1, 12.5);      // Dark Terror
        GetVariables(caster)->InnerDemonsPool[7] = InnerDemonPoolEntry(267987, 2, 13);        // Illidari Satyr
        GetVariables(caster)->InnerDemonsPool[8] = InnerDemonPoolEntry(267992, 3, 15.5);      // Bilescourge
        GetVariables(caster)->InnerDemonsPool[9] = InnerDemonPoolEntry(267989, 5, 16.5f);     // Eye of Guldan
    }

    // Find random slot for Eye of Guldan and Bilescourge.
    uint8 FindPositions(bool eye, Unit* caster)
    {
        uint8* arr;
        uint8 currentSize = 0;

        if (eye)
            arr = new uint8[5];
        else
            arr = new uint8[3];

        if (eye)
        {
            for (uint8 i = 0; i < 3; i++)
                if (!GetVariables(caster)->InnerDemonsSlots[i])
                {
                    arr[i] = i;
                    currentSize++;
                }
            for (uint8 i = 6; i < 8; i++)
                if (!GetVariables(caster)->InnerDemonsSlots[i])
                {
                    arr[i - 3] = i;
                    currentSize++;
                }
        }
        else
            for (uint8 i = 3; i < 6; i++)
                if (!GetVariables(caster)->InnerDemonsSlots[i])
                {
                    arr[i - 3] = i;
                    currentSize++;
                }

        return arr[urand(0, currentSize - 1)];
    }

    void HandleSpawnDemon(Unit* caster, Unit* target)
    {
        if (!caster || !target)
            return;

                // Verify change of position only if we move or rotate.
                if ((std::abs(caster->GetPositionX() - GetVariables(caster)->LastPositionInner.GetPositionX()) >= 1 || std::abs(caster->GetPositionY() - GetVariables(caster)->LastPositionInner.GetPositionY()) >= 1) ||
                    abs(GetVariables(caster)->LastOrientationInner - caster->GetOrientation()) >= M_PI / 6)
                {
                    for (uint8 i = 0; i < 8; i++)
                    {
                        float x, y;
                        GetPositionWithDistInOrientation(caster, 3.2f, (float)((M_PI / 4 * i) + caster->GetOrientation()), x, y);
                        GetVariables(caster)->innerDemonPositions[i] = Position(x, y, caster->GetPosition().m_positionZ);
                    }
                    GetVariables(caster)->LastPositionInner = caster->GetPosition();
                    GetVariables(caster)->LastOrientationInner = caster->GetOrientation();
                }

                // Process the pool.
                float chance = frand(0, 100);
                float cacheChance = chance;             // Cache if we need to reset pool
                InnerDemonPoolEntry entry(0, 0, 0);

                // Take summon from pool
                while (entry.Entry == 0)
                {
                    for (uint8 i = 0; i < 10; i++)
                    {
                        if (chance <= GetVariables(caster)->InnerDemonsPool[i].Chance && GetVariables(caster)->InnerDemonsPool[i].Amount > 0)
                        {
                            // We found a valid entry.
                            entry = GetVariables(caster)->InnerDemonsPool[i];
                            GetVariables(caster)->InnerDemonsPool[i].Amount--;
                            break;
                        }
                        else
                            // Need to try another entry.
                            chance -= GetVariables(caster)->InnerDemonsPool[i].Chance;
                    }
                    // If we didn't find any thing valid, reset the pool and try again.
                    // Due the duration of the summons (15s), we SHOULD always find a valid one, so maybe this case never happens.
                    InitialicePool(caster);
                    chance = cacheChance;
                }

                    // Is Eye of Guldan or Bilescourge?
                    if (entry.Entry == SPELL_EYE_OF_GULDAN || entry.Entry == SPELL_BILESCOURGE)
                    {
                        // Eyes of Guldan will spawn in front of the caster. (Position Index: 0, 1, 2, 6, 7)
                        // and Bilescourge will spawn in back of the caster. (Position Index: 3, 4, 5)
                        // Due the duration of every summon we always find a valid position.
                        uint8 posIndex = (entry.Entry == SPELL_EYE_OF_GULDAN) ? FindPositions(true, caster) : FindPositions(false, caster);
                        GetVariables(caster)->InnerDemonsSlots[posIndex] = true;
                        caster->Variables.Set<uint8>("INNER_SLOT", posIndex);
                        caster->CastSpell(GetVariables(caster)->innerDemonPositions[posIndex], entry.Entry, true);
                        return;
                    }
                    else
                    {
                        // If the spawn doesn't need positioning then spawn just right next to the target.
			const double angles[] = { 0, M_PI / 4, M_PI / 2, M_PI, 5 * M_PI / 4, 3 * M_PI / 2, 3 * M_PI / 4, 2 * M_PI };
			Position pos = target->GetPosition();
			target->MovePositionToFirstCollision(pos, 1, (float)angles[irand(0, 7)]);
			caster->CastSpell(pos, entry.Entry, true);
                    }
                }
};

// 267211 - Bilescourge Bombers
class spell_war_bilescourge_bombers : public SpellScript
{
    PrepareSpellScript(spell_war_bilescourge_bombers);

    void HandleCast()
    {
        if (Unit* caster = GetCaster())
            caster->CastSpell(caster, SPELL_WARLOCK_BILESCOURGE_BOMBERS_START, true);
            }

    void Register() override
    {
        OnCast += SpellCastFn(spell_war_bilescourge_bombers::HandleCast);
        }
};

// 267217 - Nether Portal
class spell_war_nether_portal : public SpellScript
{
    PrepareSpellScript(spell_war_nether_portal);

    void HandleAfterCast()
    {
        if (Unit* caster = GetCaster())
            caster->CastSpell(caster, SPELL_WARLOCK_NETHER_PORTAL_AURA, true);
    }

	void Register() override
	{
        AfterCast += SpellCastFn(spell_war_nether_portal::HandleAfterCast);
	}
};

// 119898 - Command Demon (Every command demon spell)
class spell_warlock_command_demon : public SpellScript
    {
	PrepareSpellScript(spell_warlock_command_demon);

	uint32 GetSpellId()
	{
		// Get the REAL spell to cast.
		return GetSpellInfo()->GetEffect(EFFECT_0).BasePoints;
    }

	SpellCastResult CheckCast()
    {
        Unit* caster = GetCaster();
        if (!caster)
            return SPELL_FAILED_DONT_REPORT;

        Pet * pet = GetPet();
		if (!pet && !caster->HasAura(SPELL_WARLOCK_GRIMOIRE_OF_SACRIFICE))
			return SPELL_FAILED_CANT_DO_THAT_RIGHT_NOW;

		uint32 spellId = GetSpellId();
		if (!spellId)
			return SPELL_FAILED_CANT_DO_THAT_RIGHT_NOW;

        if (pet)
        {
            Player * player = GetCaster()->ToPlayer();
            Unit * victim = GetVictim(player, pet);
            WorldLocation const* dest = GetExplTargetDest();

            if (!sSpellMgr->GetSpellInfo(spellId) || (!victim && !dest))
                return SPELL_FAILED_CANT_DO_THAT_RIGHT_NOW;

            if (pet->HasAura(SPELL_WARLOCK_FELGUARD_FELSTORM))
                return SPELL_FAILED_CANT_DO_THAT_RIGHT_NOW;

            Spell * spell = new Spell(pet, sSpellMgr->GetSpellInfo(spellId), TRIGGERED_NONE);
            SpellCastTargets targets;
            targets.SetUnitTarget(victim);
            if (dest)
                targets.SetDst(*dest);
            spell->InitExplicitTargets(targets);
            SpellCastResult res = spell->CheckCast(true);
            delete spell;
            if (res != SPELL_CAST_OK)
                return res;
        }
        else if (!pet && caster->HasAura(SPELL_WARLOCK_GRIMOIRE_OF_SACRIFICE))
        {
            Player* player = caster->ToPlayer();
            if (player)
            {
                Unit* victim = player->GetSelectedUnit();
                WorldLocation const* dest = GetExplTargetDest();
                Spell * spell = new Spell(player, sSpellMgr->GetSpellInfo(spellId), TRIGGERED_NONE);
                SpellCastTargets targets;
                targets.SetUnitTarget(victim);
                if (dest)
                    targets.SetDst(*dest);
                spell->InitExplicitTargets(targets);
                SpellCastResult res = spell->CheckCast(true);
                delete spell;
                if (res != SPELL_CAST_OK)
                    return res;
            }
        }

		return SPELL_CAST_OK;
	}

	void HandleAfterCast()
        {
        Unit* caster = GetCaster();
        if (!caster)
            return;

		Pet* pet = GetPet();
		if (!pet && !caster->HasAura(SPELL_WARLOCK_GRIMOIRE_OF_SACRIFICE))
			return;

		Player* player = caster->ToPlayer();
        if (!player)
            return;

		uint32 spellId = GetSpellId();
		if (!spellId)
			return;

        if (pet)
        {
            // Make the pet actually cast.
            Unit * victim = GetVictim(player, pet);
            player->GetSession()->HandlePetActionHelper(pet, ObjectGuid::Empty, spellId, ACT_ENABLED, victim->GetGUID(), Position());
        }

		// Set Command Demon cooldown.
		player->GetSpellHistory()->StartCooldownROG(GetSpellInfo(), 0, GetSpell(), false, true);
	}

	void Register() override
                {
		OnCheckCast += SpellCheckCastFn(spell_warlock_command_demon::CheckCast);
		AfterCast += SpellCastFn(spell_warlock_command_demon::HandleAfterCast);
                }

private:
	Pet * GetPet()
                {
		if (Unit* caster = GetCaster())
			if (caster->ToPlayer())
			{
				Pet * pet = caster->ToPlayer()->GetPet();
				return pet;
                }
		return NULL;
        }

	Unit * GetVictim(Player* player, Pet* pet)
                {
		Unit * victim = pet->GetVictim();
		if (!victim)
			victim = GetExplTargetUnit();
		if (!victim)
			victim = player->GetVictim();
		if (!victim)
			victim = player->GetSelectedUnit();
		if (!victim)
			victim = pet;
		return victim;
                }
};

// Call by every pet summon. Creates the portal visual.
class spell_war_summon : public SpellScript
{
	PrepareSpellScript(spell_war_summon);

	void HandlePrepare()
	{
		if (Unit* caster = GetCaster())
		{
			uint32 visual = 0;
			float x, y;
			GetPositionWithDistInOrientation(caster, 3.f, (float)(M_PI / 2) + caster->GetOrientation(), x, y);
			Position pos = Position(x, y, caster->GetPositionZ());
			switch (GetSpellInfo()->Id)
			{
				// Felguard
				case 30146:
					visual = 81019;
					break;
				// Imp
				case 688:
					visual = 81024;
					break;
				// Voidwalker
				case 697:
					visual = 81022;
					break;
				// Succubus
				case 712:
					visual = 81023;
					break;
				// Felhunter
				case 691:
					visual = 81021;
					break;
			default:
				break;
    }
			caster->SendPlayOrphanSpellVisual(pos, visual, 100);
		}
	}

	void Register() override
	{
		OnPrepare += SpellOnPrepareFn(spell_war_summon::HandlePrepare);
	}
};

// Summon Observer
// MiscId - 90001
struct at_warl_summon_observer : AreaTriggerAI
{
    at_warl_summon_observer(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger) { }

    void OnUnitEnter(Unit* unit) override
    {
        if (Unit* caster = at->GetCaster())
            if (caster->IsValidAttackTarget(unit))
                caster->CastSpell(unit, SPELL_WARLOCK_OBSERVER_AURA, true);
    }

    void OnUnitExit(Unit* unit) override
    {
        Unit* caster = at->GetCaster();
        if (!caster || !unit)
            return;

        if (unit->HasAura(SPELL_WARLOCK_OBSERVER_AURA, caster->GetGUID()))
            unit->RemoveAura(SPELL_WARLOCK_OBSERVER_AURA, caster->GetGUID());
    }
};

// 117828 - Backdraft
class aura_warl_backdraft : public AuraScript
{
	PrepareAuraScript(aura_warl_backdraft);

	bool Validate(SpellInfo const* /*spellInfo*/) override
	{
		if (!sSpellMgr->GetSpellInfo(SPELL_WARLOCK_INCINERATE) && !sSpellMgr->GetSpellInfo(SPELL_WARLOCK_CHAOS_BOLT))
			return false;
		return true;
	}

	bool CheckProc(ProcEventInfo& /*eventInfo*/)
	{
		return false;
	}

	void Register() override
	{
		DoCheckProc += AuraCheckProcFn(aura_warl_backdraft::CheckProc);
	}
};

// 196412 - Erradication
class aura_warl_erradication : public AuraScript
{
	PrepareAuraScript(aura_warl_erradication);

	bool CheckProc(ProcEventInfo& eventInfo)
	{
		if (eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == SPELL_WARLOCK_CHAOS_BOLT)
			return true;

		return false;
	}

	void HandleProc(ProcEventInfo& eventInfo)
	{
		PreventDefaultAction();
		Unit* caster = GetCaster();
		Unit* target = eventInfo.GetActionTarget();
		if (!caster || !target)
			return;

		caster->CastSpell(target, SPELL_WARLOCK_ERADICATION_DEBUFF, true);
	}

	void Register() override
	{
		DoCheckProc += AuraCheckProcFn(aura_warl_erradication::CheckProc);
		OnProc += AuraProcFn(aura_warl_erradication::HandleProc);
	}
};

// 6353 - Soul Fire
class spell_warl_soul_fire : public SpellScript
{
	PrepareSpellScript(spell_warl_soul_fire);

	void HandleAfterCast()
	{
		if (Unit* caster = GetCaster())
			caster->CastSpell(caster, SPELL_WARLOCK_SOUL_FIRE_ENERGIZE, true);
	}

	void Register() override
	{
		AfterCast += SpellCastFn(spell_warl_soul_fire::HandleAfterCast);
	}
};

// 42223 - Rain of Fire Damage
class spell_warl_rain_of_fire_damage : public SpellScript
{
	PrepareSpellScript(spell_warl_rain_of_fire_damage);

	bool Validate(SpellInfo const* /*spellInfo*/) override
	{
		return ValidateSpellInfo({ SPELL_WARLOCK_INFERNO });
	}

	void HandleEffectHit(SpellEffIndex /*effIndex*/)
	{
		if (Unit* caster = GetCaster())
			if (caster->HasAura(SPELL_WARLOCK_INFERNO) && roll_chance_i(sSpellMgr->GetSpellInfo(SPELL_WARLOCK_INFERNO)->GetEffect(EFFECT_0).BasePoints))
				caster->ModifyPower(POWER_SOUL_SHARDS, 1);
	}

	void Register() override
	{
		OnEffectHitTarget += SpellEffectFn(spell_warl_rain_of_fire_damage::HandleEffectHit, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
	}
};

// 264106 - Deathbolt
class spell_warl_deathbolt : public SpellScript
{
	PrepareSpellScript(spell_warl_deathbolt);

	bool Validate(SpellInfo const* /*spellInfo*/) override
	{
		return ValidateSpellInfo({ SPELL_WARLOCK_DEATHBOLT });
	}

	void HandleHit(SpellEffIndex effIndex)
	{
		PreventHitDefaultEffect(effIndex);
		Unit* caster = GetCaster();
		Unit* target = GetHitUnit();
		if (!caster || !target)
			return;

		// Calculate remaining amount of damage.
		int32 damage = 0;
		Unit::AuraApplicationMap const& auras = target->GetAppliedAuras();
		for (auto i = auras.begin(); i != auras.end(); i++)
		{
            if (i->second->GetBase()->GetCasterGUID() != caster->GetGUID())
                continue;

            SpellInfo const* spellinfo = i->second->GetBase()->GetSpellInfo();
            // Every possible DOT spell.
            if (spellinfo->Id == SPELL_WARLOCK_CORRUPTION_DAMAGE || spellinfo->Id == SPELL_WARLOCK_UNSTABLE_AFFLICTION_DAMAGE_1 || spellinfo->Id == SPELL_WARLOCK_UNSTABLE_AFFLICTION_DAMAGE_2 ||
                spellinfo->Id == SPELL_WARLOCK_UNSTABLE_AFFLICTION_DAMAGE_3 || spellinfo->Id == SPELL_WARLOCK_UNSTABLE_AFFLICTION_DAMAGE_4 || spellinfo->Id == SPELL_WARLOCK_UNSTABLE_AFFLICTION_DAMAGE_5 ||
                spellinfo->Id == SPELL_WARLOCK_AGONY || spellinfo->Id == SPELL_WARLOCK_SIPHON_LIFE || spellinfo->Id == SPELL_WARLOCK_PHANTOMATIC_SINGULARITY_DAMAGE)
            {
                float currentRemainingTime = i->second->GetBase()->GetDuration();
                if (spellinfo->Id == SPELL_WARLOCK_CORRUPTION_DAMAGE && caster->HasAura(SPELL_WARLOCK_ABSOLUTE_CORRUPTION))
                	currentRemainingTime = sSpellMgr->GetSpellInfo(SPELL_WARLOCK_DEATHBOLT)->GetEffect(EFFECT_2).BasePoints * IN_MILLISECONDS;

                AuraEffectVector effects = i->second->GetBase()->GetAuraEffects();
                for (AuraEffectVector::const_iterator iter = effects.begin(); iter != effects.end(); ++iter)
                    if (*iter && ((*iter)->GetAuraType() == SPELL_AURA_PERIODIC_DAMAGE || (*iter)->GetAuraType() == SPELL_AURA_PERIODIC_LEECH))
                    {
                        int32 valDamage = CalculatePct((*iter)->GetDamage() * currentRemainingTime / (*iter)->GetPeriod(), sSpellMgr->GetSpellInfo(SPELL_WARLOCK_DEATHBOLT)->GetEffect(EFFECT_1).BasePoints);
                        damage += valDamage;
                        break;
                    }
            }
		}

		SetHitDamage(damage);
	}

	void Register() override
	{
		OnEffectHitTarget += SpellEffectFn(spell_warl_deathbolt::HandleHit, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
	}
};

// 200586 - Fel Fissure
class aura_warl_fel_fissure : public AuraScript
{
	PrepareAuraScript(aura_warl_fel_fissure);

	bool CheckProc(ProcEventInfo& eventInfo)
	{
		if (eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == SPELL_WARLOCK_CHAOS_BOLT)
			return true;

		return false;
	}

	void Register() override
	{
		DoCheckProc += AuraCheckProcFn(aura_warl_fel_fissure::CheckProc);
	}
};

// 221711 - Essence Drain
class aura_warl_essence_drain : public AuraScript
{
    PrepareAuraScript(aura_warl_essence_drain);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_WARLOCK_ESSENCE_DRAIN });
    }

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == SPELL_WARLOCK_DRAIN_LIFE_HEAL)
            return true;

        return false;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();
        Unit* target = eventInfo.GetActionTarget();
        if (!caster || !target)
            return;

        caster->CastSpell(target, SPELL_WARLOCK_ESSENCE_DRAIN, true);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_warl_essence_drain::CheckProc);
        OnProc += AuraProcFn(aura_warl_essence_drain::HandleProc);
    }
};

// 234877 - Curse of Shadows
class aura_warl_curse_of_shadows : public AuraScript
{
    PrepareAuraScript(aura_warl_curse_of_shadows);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_WARLOCK_CURSE_OF_THE_SHADOW, SPELL_WARLOCK_CURSE_OF_THE_SHADOW_DAMAGE });
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();
        Unit* target = eventInfo.GetActionTarget();
        if (!caster || !target || !eventInfo.GetDamageInfo())
            return;

        uint8 percent = sSpellMgr->GetSpellInfo(SPELL_WARLOCK_CURSE_OF_THE_SHADOW)->GetEffect(EFFECT_0).BasePoints;
        caster->CastCustomSpell(SPELL_WARLOCK_CURSE_OF_THE_SHADOW_DAMAGE, SPELLVALUE_BASE_POINT0, CalculatePct(eventInfo.GetDamageInfo()->GetDamage(), percent), target, true);
    }

    void Register() override
    {
        OnProc += AuraProcFn(aura_warl_curse_of_shadows::HandleProc);
    }
};

// 205196 - Dreadbite (Dreadstalkers)
class spell_warl_dreadbite : public SpellScript
{
	PrepareSpellScript(spell_warl_dreadbite);

	void HandleHitTarget(SpellEffIndex /*effIndex*/)
	{
		if (Unit* caster = GetCaster())
			if (Unit* owner = caster->GetOwner())
			{
				int32 damage = owner->GetTotalSpellPowerValue(SPELL_SCHOOL_MASK_SHADOW, false) * 0.375;
				SetHitDamage(damage);
			}
	}

	void Register() override
	{
		OnEffectHitTarget += SpellEffectFn(spell_warl_dreadbite::HandleHitTarget, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
	}
};

// 212580 - Eye of the Observer
class aura_warl_eye_of_the_observer: public AuraScript
{
    PrepareAuraScript(aura_warl_eye_of_the_observer);

	bool Validate(SpellInfo const* /*spellInfo*/) override
	{
		return ValidateSpellInfo({ SPELL_WARLOCK_LASERBEAM });
	}

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetDamageInfo() && (eventInfo.GetDamageInfo()->GetDamageType() != HEAL && eventInfo.GetDamageInfo()->GetDamageType() != NODAMAGE) && eventInfo.GetDamageInfo()->GetDamageType() != DOT)
            return true;

        return false;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();
        Unit* caster = GetCaster();
        Unit* actor = eventInfo.GetActor();
        if (!caster || !actor)
            return;

        if (Creature* creature = caster->GetSummonedCreatureByEntry(107100))
        {
            if (creature->GetSpellHistory()->HasCooldown(SPELL_WARLOCK_LASERBEAM))
                return;

            creature->SetTarget(actor->GetGUID());
            creature->CastCustomSpell(SPELL_WARLOCK_LASERBEAM, SPELLVALUE_BASE_POINT0, sSpellMgr->GetSpellInfo(SPELL_WARLOCK_LASERBEAM)->GetEffect(EFFECT_1).BasePoints, actor, true);
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_warl_eye_of_the_observer::CheckProc);
        OnProc += AuraProcFn(aura_warl_eye_of_the_observer::HandleProc);
    }
};

// 212282 - Cremation
class aura_warl_cremation : public AuraScript
{
	PrepareAuraScript(aura_warl_cremation);

	bool CheckProc(ProcEventInfo& eventInfo)
	{
		Unit* caster = GetCaster();
		Unit* target = eventInfo.GetActionTarget();
		if (!caster || !target)
			return false;

		if (eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == SPELL_WARLOCK_CONFLAGRATE && target->HasAura(SPELL_WARLOCK_IMMOLATE_DOT, caster->GetGUID()))
			return true;

		return false;
	}
	
	void Register() override
	{
		DoCheckProc += AuraCheckProcFn(aura_warl_cremation::CheckProc);
	}
};

// 234153 - Drain Life
class aura_warl_drain_life : public SpellScriptLoader
{
public:
    aura_warl_drain_life() : SpellScriptLoader("aura_warl_drain_life") { }

    class spell_warl_drain_life_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_warl_drain_life_SpellScript);


        enum SoulRot
        {
            SoulRotDrainLifeAura = 331623,
            SoulRotDebuff = 325640,
        };

        void HandleBeforeCast()
        {
            Unit* caster = GetCaster();
            if (!caster)
                return;
            if (caster->HasAura(SoulRotDrainLifeAura))
            {
                std::list<Unit*> extraTargets;
                caster->GetAttackableUnitListInRange(extraTargets, 40.0f);
                for (auto unit : extraTargets)
                {
                    if (unit->HasAura(SoulRotDebuff, caster->GetGUID()) && !unit->HasAura(GetSpellInfo()->Id, caster->GetGUID()))
                        caster->AddChannelObject(unit->GetGUID());
                }

                caster->Variables.Remove("DrainLifeDmg");
            }
        }

        void Register() override
        {
            BeforeCast += SpellCastFn(spell_warl_drain_life_SpellScript::HandleBeforeCast);
        }
    };
    /// ID: 234153 Drain Life
    class spell_drain_life_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_drain_life_AuraScript);

        void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            Unit* caster = GetCaster();
            if (!caster)
                return;

            // Handle Accrued Vitality conduit
            if (caster->Variables.Exist("DrainLifeDmg"))
            {
                uint32 dmg = caster->Variables.GetValue("DrainLifeDmg", 0u);
                caster->Variables.Remove("DrainLifeDmg");

                if (auto eff = caster->GetAuraEffect(339282, EFFECT_0))
                {
                    if (eff->ConduitRankEntry)
                    {
                        auto amount = CalculatePct(dmg, eff->ConduitRankEntry->AuraPointsOverride);
                        caster->CastSpell(caster, 339298, CastSpellExtraArgs(true).AddSpellBP0(amount));
                    }
                }
            }
        }

        void Register() override
        {
            OnEffectRemove += AuraEffectApplyFn(spell_drain_life_AuraScript::HandleRemove, EFFECT_0, SPELL_AURA_PERIODIC_LEECH, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_drain_life_AuraScript();
    }

    SpellScript* GetSpellScript() const override
    {
        return new spell_warl_drain_life_SpellScript();
    }
};

// 212356 - Soulshatter
class spell_warl_soulshatter : public SpellScript
{
	PrepareSpellScript(spell_warl_soulshatter);

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

				return false;
			});

			std::list<Unit*> finalList;
			for (WorldObject* object : targets)
			{
				Unit* target = object->ToUnit();
				if (target && (target->HasAura(SPELL_WARLOCK_UNSTABLE_AFFLICTION_DAMAGE_1, caster->GetGUID()) || target->HasAura(SPELL_WARLOCK_UNSTABLE_AFFLICTION_DAMAGE_2, caster->GetGUID()) ||
					target->HasAura(SPELL_WARLOCK_UNSTABLE_AFFLICTION_DAMAGE_3, caster->GetGUID()) || target->HasAura(SPELL_WARLOCK_UNSTABLE_AFFLICTION_DAMAGE_4, caster->GetGUID()) ||
					target->HasAura(SPELL_WARLOCK_UNSTABLE_AFFLICTION_DAMAGE_5, caster->GetGUID()) || target->HasAura(SPELL_WARLOCK_AGONY, caster->GetGUID()) ||
					target->HasAura(SPELL_WARLOCK_CORRUPTION_DAMAGE, caster->GetGUID()) || target->HasAura(SPELL_WARLOCK_SIPHON_LIFE_HEAL, caster->GetGUID()) ||
					target->HasAura(SPELL_WARLOCK_PHANTOMATIC_SINGULARITY, caster->GetGUID())))
					finalList.push_back(target);
			}

			finalList.sort(Trinity::DistanceCompareOrderPred(caster));
			if (finalList.size() > 5)
				finalList.resize(5);

			targets.clear();
			for (Unit* target : finalList)
				targets.push_back(target);
		}
		else
			targets.clear();
	}

	void HandleEffectHit(SpellEffIndex /*effIndex*/)
	{
		Unit* caster = GetCaster();
		Unit* target = GetHitUnit();
		if (!caster || !target)
			return;

		caster->SendPlaySpellVisual(target->GetGUID(), 56030, 0, 0, 40.f);
		target->RemoveAurasDueToSpell(SPELL_WARLOCK_UNSTABLE_AFFLICTION_DAMAGE_1, caster->GetGUID());
		target->RemoveAurasDueToSpell(SPELL_WARLOCK_UNSTABLE_AFFLICTION_DAMAGE_2, caster->GetGUID());
		target->RemoveAurasDueToSpell(SPELL_WARLOCK_UNSTABLE_AFFLICTION_DAMAGE_3, caster->GetGUID());
		target->RemoveAurasDueToSpell(SPELL_WARLOCK_UNSTABLE_AFFLICTION_DAMAGE_4, caster->GetGUID());
		target->RemoveAurasDueToSpell(SPELL_WARLOCK_UNSTABLE_AFFLICTION_DAMAGE_5, caster->GetGUID());
		target->RemoveAurasDueToSpell(SPELL_WARLOCK_AGONY, caster->GetGUID());
		target->RemoveAurasDueToSpell(SPELL_WARLOCK_CORRUPTION_DAMAGE, caster->GetGUID());
		target->RemoveAurasDueToSpell(SPELL_WARLOCK_SIPHON_LIFE_HEAL, caster->GetGUID());
		target->RemoveAurasDueToSpell(SPELL_WARLOCK_PHANTOMATIC_SINGULARITY, caster->GetGUID());

		SetHitDamage(CalculatePct(target->GetMaxHealth(), sSpellMgr->GetSpellInfo(SPELL_WARLOCK_SOULSHATTER)->GetEffect(EFFECT_1).BasePoints));
		caster->CastSpell(caster, SPELL_WARLOCK_SOULSHATTER_ENERGIZE, true);
		caster->CastSpell(caster, SPELL_WARLOCK_SOULSHATTER_HASTE, true);
	}

	void Register() override
	{
		OnEffectHitTarget += SpellEffectFn(spell_warl_soulshatter::HandleEffectHit, EFFECT_0, SPELL_EFFECT_DAMAGE_FROM_MAX_HEALTH_PCT);
		OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_warl_soulshatter::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
	}
};

// 118699 - Fear
class aura_warl_fear : public AuraScript
{
	PrepareAuraScript(aura_warl_fear);

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
		DoCheckProc += AuraCheckProcFn(aura_warl_fear::CheckProc);
		OnProc += AuraProcFn(aura_warl_fear::HandleProc);
	}
};

// 108503 - Grimoire of Sacrifice
class spell_warl_grimoire_of_sacrifice : public SpellScript
{
    PrepareSpellScript(spell_warl_grimoire_of_sacrifice);

    SpellCastResult CheckCast()
    {
        Unit* caster = GetCaster();
        if (!caster)
            return SPELL_FAILED_DONT_REPORT;
                    Guardian* pet = caster ? caster->GetGuardianPet() : nullptr;
        if (!pet)
            return SPELL_FAILED_NO_PET;

        return SPELL_CAST_OK;
    }

    void HandlePrepare()
    {
        if (Unit* caster = GetCaster())
            if (Guardian* pet = caster->GetGuardianPet())
                petEntry = pet->GetEntry();
    }

    void HandleAfterHit()
    {
        if (Unit* caster = GetCaster())
            caster->CastCustomSpell(SPELL_WARLOCK_GRIMOIRE_OF_SACRIFICE, SPELLVALUE_BASE_POINT0, petEntry, caster, true);
    }

    void Register() override
    {
        OnCheckCast += SpellCheckCastFn(spell_warl_grimoire_of_sacrifice::CheckCast);
        OnPrepare += SpellOnPrepareFn(spell_warl_grimoire_of_sacrifice::HandlePrepare);
        AfterHit += SpellHitFn(spell_warl_grimoire_of_sacrifice::HandleAfterHit);
    }

private:
    uint32 petEntry;
};

// 196099 - Grimoire of Sacrifice Aura
class aura_warl_grimoire_of_sacrifice : public AuraScript
{
    PrepareAuraScript(aura_warl_grimoire_of_sacrifice);

    void HandleApply(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /* mode */)
    {
        if (Unit* caster = GetCaster())
        {
            caster->RemoveAurasDueToSpell(119904);
            switch (GetEffect(EFFECT_0)->GetAmount())
            {
                // Imp
            case 416:
                caster->CastCustomSpell(119904, SPELLVALUE_BASE_POINT0, 119905, caster, true);
                break;
                // Felhunter
            case 417:
                caster->CastCustomSpell(119904, SPELLVALUE_BASE_POINT0, 119910, caster, true);
                break;
                // Voidwalker
            case 1860:
                caster->CastCustomSpell(119904, SPELLVALUE_BASE_POINT0, 119907, caster, true);
                break;
                // Succubus
            case 1863:
                caster->CastCustomSpell(119904, SPELLVALUE_BASE_POINT0, 119909, caster, true);
                break;
            default:
                break;
            }
        }
    }

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetDamageInfo() && eventInfo.GetDamageInfo()->GetDamage() > 0)
            return true;

        return false;
    }

    void HandleRemove(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /* mode */)
    {
        if (Unit* caster = GetCaster())
            caster->RemoveAura(119904);
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(aura_warl_grimoire_of_sacrifice::HandleApply, EFFECT_0, SPELL_AURA_PROC_TRIGGER_SPELL, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
        DoCheckProc += AuraCheckProcFn(aura_warl_grimoire_of_sacrifice::CheckProc);
        OnEffectRemove += AuraEffectRemoveFn(aura_warl_grimoire_of_sacrifice::HandleRemove, EFFECT_0, SPELL_AURA_PROC_TRIGGER_SPELL, AURA_EFFECT_HANDLE_REAL);
    }
};

// 20707 - Soulstone
class spell_warl_soulstone : public SpellScript
{
    PrepareSpellScript(spell_warl_soulstone);

    SpellCastResult CheckCast()
    {
        Unit* caster = GetCaster();
        Unit* target = GetExplTargetUnit();
        if (!caster || !target)
            return SPELL_FAILED_DONT_REPORT;

        if ((!caster->HasAura(SPELL_WARLOCK_SOULSTONE_RANK2) && !target->IsAlive()) || !target->ToPlayer())
            return SPELL_FAILED_BAD_TARGETS;

        return SPELL_CAST_OK;
    }

    void HandleCast()
    {
        Unit* caster = GetCaster();
        Unit* target = GetExplTargetUnit();
        if (!caster || !target)
            return;

        if (!target->IsAlive())
            caster->CastSpell(target, 160029, true);
    }

    void HandleHit()
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        // Target alive - not need for Resurrection Aura.
        if (target->IsAlive())
            target->RemoveAura(160029, caster->GetGUID());
        else
        {
            PreventHitAura();
            caster->CastSpell(target, SPELL_WARLOCK_SOULSTONE_RESURRECTION, true);
        }
    }

    void Register() override
    {
        OnCast += SpellCastFn(spell_warl_soulstone::HandleCast);
        OnHit += SpellHitFn(spell_warl_soulstone::HandleHit);
    }
};

// Called by 3026  - Soulstone
// Last Update 8.0.1 Build 28153 
class spell_warl_use_soulstone : public SpellScript
{
    PrepareSpellScript(spell_warl_use_soulstone);

    void HandleHit(SpellEffIndex effindex)
    {
        PreventHitEffect(effindex);

        Unit* caster = GetCaster();
        if (!caster)
            return;

        if (!caster || caster->IsAlive())
            return;
        if (caster->GetTypeId() != TYPEID_PLAYER)
            return;
        if (!caster->IsInWorld())
            return;

        uint32 health = 0;
        uint32 mana = 0;

        health = caster->CountPctFromMaxHealth(GetSpellInfo()->GetEffect(EFFECT_1).BasePoints);
        if (caster->GetMaxPower(POWER_MANA) > 0)
            mana = CalculatePct(caster->GetMaxPower(POWER_MANA), GetSpellInfo()->GetEffect(effindex).BasePoints);


        Player* player = caster->ToPlayer();
        player->ResurrectPlayer(0.0f);

        player->SetHealth(health);
        player->SetPower(POWER_MANA, mana);
        player->SetPower(POWER_RAGE, 0);
        player->SetFullPower(POWER_ENERGY);
        player->SetPower(POWER_FOCUS, 0);

        player->SpawnCorpseBones();
    }

    void Register() override
    {
        OnEffectHit += SpellEffectFn(spell_warl_use_soulstone::HandleHit, EFFECT_0, SPELL_EFFECT_SELF_RESURRECT);
    }
};

// 85692 - Doom Bolt
class spell_warl_doom_bolt : public SpellScript
{
    PrepareSpellScript(spell_warl_doom_bolt);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_WARLOCK_DOOM_BOLT });
    }

    void HandleHit()
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        uint8 percent = sSpellMgr->GetSpellInfo(SPELL_WARLOCK_DOOM_BOLT)->GetEffect(EFFECT_1).BasePoints;
        if (target->HealthBelowPct(percent))
            SetHitDamage(GetHitDamage() + CalculatePct(GetHitDamage(), percent));
    }

    void Register() override
    {
        OnHit += SpellHitFn(spell_warl_doom_bolt::HandleHit);
    }
};

// 212529 - Laser Beam
class spell_warl_laser_beam : public SpellScript
{
    PrepareSpellScript(spell_warl_laser_beam);

    void HandleAfterCast()
    {
        if (Unit* caster = GetCaster())
            caster->GetSpellHistory()->StartCooldownROG(GetSpellInfo(), 0, GetSpell(), false, true, 2 * IN_MILLISECONDS);
    }

    void Register() override
    {
        AfterCast += SpellCastFn(spell_warl_laser_beam::HandleAfterCast);
    }
};

// 89766 - Axe Toss
class spell_warl_axe_toss : public SpellScript
{
    PrepareSpellScript(spell_warl_axe_toss);

    SpellCastResult CheckCast()
    {
        Unit* caster = GetCaster();
        if (!caster)
            return SPELL_FAILED_NO_PET;
        if (caster && caster->GetEntry() != 17252)
            return SPELL_FAILED_CANT_DO_THAT_RIGHT_NOW;
        if (caster && caster->HasAura(SPELL_WARLOCK_FELGUARD_FELSTORM))
            return SPELL_FAILED_CANT_DO_THAT_RIGHT_NOW;
        return SPELL_CAST_OK;
    };

    void Register() override
    {
        OnCheckCast += SpellCheckCastFn(spell_warl_axe_toss::CheckCast);
    }
};

// 199954 - Curse of Fragility
//Last Update 8.0.1 Build 28153
class spell_curse_of_fragility : public SpellScript
{
    PrepareSpellScript(spell_curse_of_fragility);

    SpellCastResult CheckCast()
    {
        if (Unit* caster = GetCaster())
            if (Unit* target = GetExplTargetUnit())
                if (!target->IsPlayer() && !caster->GetMap()->IsBattlegroundOrArena()) //Can be used in Alterac Valley agains boss
                    return SPELL_FAILED_BAD_TARGETS;

        return SPELL_CAST_OK;
    }

    void Register() override
    {
        OnCheckCast += SpellCheckCastFn(spell_curse_of_fragility::CheckCast);
    }
};

// 325640 soul rot 
class spell_warl_soul_rot : public SpellScript
{
    PrepareSpellScript(spell_warl_soul_rot);

    enum SoulRot
    {
        SoulRotDrainLifeAura = 331623
    };

    void HandleAfterCast()
    {
        if (Unit* caster = GetCaster())
            caster->CastSpell(caster, SoulRotDrainLifeAura, true);
    }

    void Register() override
    {
        AfterCast += SpellCastFn(spell_warl_soul_rot::HandleAfterCast);
    }
};

const uint32 dotAuras[] = {325640, SPELL_WARLOCK_AGONY, SPELL_WARLOCK_UNSTABLE_AFFLICTION, SPELL_WARLOCK_CORRUPTION, 278350, 205179, 316099 };

// 324536 
class spell_warl_malefic_rapture : public SpellScript
{
    PrepareSpellScript(spell_warl_malefic_rapture);

    enum MaleficRapture
    {
        Dmg = 324540,
    };

    void HandleAfterCast()
    {
        if (Unit* caster = GetCaster())
        {
            caster->RemoveAurasDueToSpell(364322); ///< Calamitous Crescendo

            int32 baseDamage = caster->GetTotalSpellPowerValue(SPELL_SCHOOL_MASK_SHADOW, false) * 1.275f;

            std::list<Unit*> enemies;
            caster->GetAttackableUnitListInRange(enemies, 100.0f);
            for (auto enemy : enemies)
            {
                uint32 totalAuras = 0;
                for (auto dot : dotAuras)
                    if (enemy->HasAura(dot, caster->GetGUID()))
                        ++totalAuras;

                if (totalAuras > 0)
                {
                    caster->CastSpell(enemy, Dmg, CastSpellExtraArgs(true).AddSpellBP0(baseDamage * totalAuras));
                }
            }
        }
    }

    void Register() override
    {
        AfterCast += SpellCastFn(spell_warl_malefic_rapture::HandleAfterCast);
    }
};

void AddSC_warlock_spell_scripts()
{
    RegisterSpellScript(spell_warl_demonskin);
    RegisterSpellScript(spell_warl_doom);
    RegisterSpellScript(spell_warl_banish);
    RegisterSpellAndAuraScriptPair(spell_warl_burning_rush, aura_warl_burning_rush);
    RegisterSpellScript(spell_warl_call_dreadstalkers);
    RegisterSpellScript(spell_warl_chaos_bolt);
    RegisterSpellScript(spell_warl_conflagrate);
    RegisterSpellScript(spell_warl_conflagrate_aura);
    RegisterSpellScript(spell_warl_corruption_effect);
    RegisterSpellScript(spell_warl_create_healthstone);
    RegisterSpellScript(spell_warl_create_healthstone_soulwell);
    RegisterSpellScript(spell_warl_dark_pact);
    RegisterSpellScript(spell_warl_dark_regeneration);
    RegisterSpellScript(spell_warl_demonbolt);
    RegisterSpellScript(spell_warl_demonic_call);
    RegisterSpellScript(spell_warl_demonic_circle_summon);
    RegisterSpellScript(spell_warl_demonic_circle_teleport);
    RegisterSpellScript(spell_warl_demonic_gateway);
    RegisterSpellScript(spell_warl_devour_magic);
    RegisterSpellScript(spell_warl_drain_soul);
    new spell_warl_fear();
    new spell_warl_fear_buff();
    new spell_warl_glyph_of_soulwell();
    new spell_warl_hand_of_guldan();
    RegisterSpellScript(aura_warl_haunt);
    RegisterSpellScript(spell_warl_health_funnel);
    RegisterSpellScript(spell_warl_healthstone_heal);
    new spell_warl_immolate();
    RegisterSpellScript(spell_warl_immolate_aura);
    new spell_warl_life_tap();
    new spell_warl_metamorphosis_cost();
    new spell_warl_molten_core_dot();
    RegisterSpellAndAuraScriptPair(spell_warl_seed_of_corruption, aura_warl_seed_of_corruption);
    RegisterSpellScript(spell_warl_seed_of_corruption_damage);
    RegisterSpellScript(spell_warl_shadow_bolt);
    new spell_warl_shadow_bulwark();
    RegisterSpellScript(spell_warl_soul_leech_aura);
    new spell_warl_twilight_ward_s12();
    RegisterSpellScript(spell_warl_unstable_affliction);
    RegisterSpellScript(aura_warl_unstable_affliction);
    new spell_warl_void_ray();
    new spell_warlock_agony();
    new spell_warl_cauterize_master();
    new spell_warl_suffering();
    new spell_warl_whiplash();
    new spell_warl_spell_lock();
    new spell_warl_felstorm();
    new spell_warl_meteor_strike();
    new spell_warl_shadow_lock();
    new spell_warl_cataclysm();
    RegisterSpellScript(spell_warl_immolate_dot);
    new spell_warl_channel_demonfire();
    new spell_warl_soul_conduit();
    new spell_warl_grimoire_of_service();
    new spell_warl_implosion();
    new spell_warl_grimoire_of_synergy();
    RegisterSpellScript(spell_warl_eye_laser);
    new spell_warl_demonic_calling();
    new spell_warl_eradication();
    new spell_warl_havoc();
    RegisterSpellScript(aura_warl_phantomatic_singularity);
    RegisterSpellScript(spell_warl_incinerate);
    RegisterSpellScript(spell_warl_back_draft_aura);
    RegisterSpellScript(spell_warr_roaring_blaze);
    RegisterSpellScript(aura_war_demonic_call_proc);
    RegisterSpellScript(spell_war_soul_strike);
    RegisterSpellScript(spell_war_power_siphon);
	RegisterSpellScript(aura_war_nightfall);
	RegisterSpellScript(aura_war_nightfall_proc);
    new spell_warl_sacrificial_pact();
    RegisterSpellAndAuraScriptPair(spell_warl_shadowburn, aura_warl_shadowburn);
    RegisterSpellScript(spell_warl_cremation_damage);
    RegisterSpellScript(spell_warl_entrenched_in_flame_aura);
	RegisterSpellScript(aura_war_demonic_power);
	RegisterSpellScript(spell_war_demonic_core);
    RegisterSpellScript(spell_war_dreadbite_aoe);
    RegisterSpellScript(spell_war_demonic_strength);
    RegisterSpellScript(aura_war_felstorm);
    RegisterSpellScript(spell_war_felstorm_damage);
    RegisterSpellScript(spell_warl_unending_resolve_aura);
    RegisterSpellScript(spell_war_summon_vilefiend);
	RegisterSpellScript(spell_war_hand_of_guldan_damage);
    RegisterSpellScript(spell_war_soul_leech);
    RegisterSpellScript(aura_war_inner_demons);
    RegisterSpellScript(spell_war_bilescourge_bombers);
    RegisterSpellScript(spell_war_nether_portal);
	RegisterSpellScript(spell_warlock_command_demon);
	RegisterSpellScript(spell_war_summon);
	RegisterSpellScript(aura_warl_backdraft);
	RegisterSpellScript(aura_warl_erradication);
	RegisterSpellScript(spell_warl_soul_fire);
	RegisterSpellScript(spell_warl_rain_of_fire_damage);
	RegisterSpellScript(spell_warl_deathbolt);
	RegisterSpellScript(aura_warl_fel_fissure);
    RegisterSpellScript(aura_warl_essence_drain);
    RegisterSpellScript(aura_warl_curse_of_shadows);
	RegisterSpellScript(spell_warl_dreadbite);
    RegisterSpellScript(aura_warl_eye_of_the_observer);
	RegisterSpellScript(aura_warl_cremation);
    new aura_warl_drain_life();
	RegisterSpellScript(spell_warl_soulshatter);
	RegisterSpellScript(aura_warl_fear);
    RegisterSpellScript(spell_warl_grimoire_of_sacrifice);
    RegisterSpellScript(aura_warl_grimoire_of_sacrifice);
    RegisterSpellScript(spell_warl_soulstone);
    RegisterSpellScript(spell_warl_use_soulstone);    
    RegisterSpellScript(spell_warl_doom_damage);
    RegisterSpellScript(spell_warl_doom_bolt);
    RegisterSpellScript(spell_warl_laser_beam);
    RegisterSpellScript(spell_warl_axe_toss);
    RegisterSpellScript(spell_curse_of_fragility);
    RegisterSpellScript(spell_warl_soul_rot);
    RegisterSpellScript(spell_warl_malefic_rapture);

    new spell_warl_demonic_circle_talent();

    ///AreaTrigger scripts
    RegisterAreaTriggerAI(at_warl_rain_of_fire);
    RegisterAreaTriggerAI(at_warl_bilescourge_bombers);
	RegisterAreaTriggerAI(at_warl_fel_fissure);
	RegisterAreaTriggerAI(at_warl_bane_of_havoc);
    RegisterAreaTriggerAI(at_war_casting_circle);
    RegisterAreaTriggerAI(at_warl_summon_observer);

    ///NPC scripts
    new spell_npc_warl_demonic_gateway_green();
    new spell_npc_warl_demonic_gateway_purple();
    RegisterCreatureAI(npc_pet_warlock_wild_imp);
    RegisterCreatureAI(npc_pet_warlock_darkglare);
	RegisterCreatureAI(npc_pet_warlock_dreadstalker);
	RegisterCreatureAI(npc_pet_warlock_demonic_tyrant);
    RegisterCreatureAI(npc_pet_warlock_vilefiend);
    RegisterCreatureAI(npc_pet_warlock_eye_of_guldan);
    RegisterCreatureAI(npc_pet_warlock_bilescourge);
    RegisterCreatureAI(npc_pet_warlock_void_terror);
    RegisterCreatureAI(npc_pet_warlock_illidari_satyr);
    RegisterCreatureAI(npc_pet_warlock_darkhound);
    RegisterCreatureAI(npc_pet_warlock_viciuos_hellhound);
    RegisterCreatureAI(npc_pet_warlock_ursul);
    RegisterCreatureAI(npc_pet_warlock_shivarra);
    RegisterCreatureAI(npc_pet_warlock_wrathguard);
    RegisterCreatureAI(npc_pet_warlock_prince_malchezzar);
	RegisterCreatureAI(npc_pet_warlock_fel_lord);
	RegisterCreatureAI(npc_pet_warlock_infernal);
    RegisterCreatureAI(npc_pet_warlock_observer);
    RegisterCreatureAI(npc_pet_warlock_doomguard);

    // Playerscript
    new warlock_playerscript();
}
