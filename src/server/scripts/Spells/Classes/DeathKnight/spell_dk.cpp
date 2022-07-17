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
 * Scripts for spells with SPELLFAMILY_DEATHKNIGHT and SPELLFAMILY_GENERIC spells used by deathknight players.
 * Ordered alphabetically using scriptname.
 * Scriptnames of files in this file should be prefixed with "spell_dk_".
 */

#include "AreaTrigger.h"
#include "AreaTriggerAI.h"
#include "Player.h"
#include "DynamicObject.h"
#include "ScriptMgr.h"
#include "SpellMgr.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"
#include "SpellHistory.h"
#include "Containers.h"
#include "GridNotifiers.h"
#include "TemporarySummon.h"
#include "spell_dk.h"

enum DeathKnightSpells
{
    SPELL_DK_ARMY_FLESH_BEAST_TRANSFORM         = 127533,
    SPELL_DK_ARMY_GEIST_TRANSFORM               = 127534,
    SPELL_DK_ARMY_NORTHREND_SKELETON_TRANSFORM  = 127528,
    SPELL_DK_ARMY_SKELETON_TRANSFORM            = 127527,
    SPELL_DK_ARMY_SPIKED_GHOUL_TRANSFORM        = 127525,
    SPELL_DK_ARMY_SUPER_ZOMBIE_TRANSFORM        = 127526,
    SPELL_DK_BLOOD_PLAGUE                       = 55078,
    SPELL_DK_BLOOD_PRESENCE                     = 48263,
    SPELL_DK_BLOOD_SHIELD_MASTERY               = 77513,
    SPELL_DK_BLOOD_SHIELD_ABSORB                = 77535,
    SPELL_DK_CHAINS_OF_ICE                      = 45524,
    SPELL_DK_CORPSE_EXPLOSION_TRIGGERED         = 43999,
    SPELL_DK_DEATH_AND_DECAY_DAMAGE             = 52212,
    SPELL_DK_DEATH_AND_DECAY_SLOW               = 143375,
    SPELL_DK_DEATH_COIL_BARRIER                 = 115635,
    SPELL_DK_DEATH_COIL_DAMAGE                  = 47632,
    SPELL_DK_DEATH_COIL_HEAL                    = 47633,
    SPELL_DK_DEATH_GRIP                         = 49576,
    SPELL_DK_DEATH_GRIP_PULL                    = 49575,
    SPELL_DK_DEATH_GRIP_VISUAL                  = 55719,
    SPELL_DK_DEATH_GRIP_TAUNT                   = 57603,
    SPELL_DK_DEATH_STRIKE_HEAL                  = 45470,
    SPELL_DK_DECOMPOSING_AURA                   = 199720,
    SPELL_DK_DECOMPOSING_AURA_DAMAGE            = 199721,
    SPELL_DK_ENHANCED_DEATH_COIL                = 157343,
    SPELL_DK_FROST_FEVER                        = 55095,
    SPELL_DK_GHOUL_EXPLODE                      = 47496,
    SPELL_DK_GLYPH_OF_ABSORB_MAGIC              = 159415,
    SPELL_DK_GLYPH_OF_ANTI_MAGIC_SHELL          = 58623,
    SPELL_DK_GLYPH_OF_ARMY_OF_THE_DEAD          = 58669,
    SPELL_DK_GLYPH_OF_DEATH_COIL                = 63333,
    SPELL_DK_GLYPH_OF_DEATH_AND_DECAY           = 58629,
    SPELL_DK_GLYPH_OF_FOUL_MENAGERIE            = 58642,
    SPELL_DK_GLYPH_OF_REGENERATIVE_MAGIC        = 146648,
    SPELL_DK_GLYPH_OF_RUNIC_POWER_TRIGGERED     = 159430,
    SPELL_DK_GLYPH_OF_SWIFT_DEATH               = 146645,
    SPELL_DK_GLYPH_OF_THE_GEIST                 = 58640,
    SPELL_DK_GLYPH_OF_THE_SKELETON              = 146652,
    SPELL_DK_IMPROVED_BLOOD_PRESENCE            = 50371,
    SPELL_DK_IMPROVED_SOUL_REAPER               = 157342,
    SPELL_DK_RUNIC_POWER_ENERGIZE               = 49088,
    SPELL_DK_SCENT_OF_BLOOD                     = 49509,
    SPELL_DK_SCENT_OF_BLOOD_TRIGGERED           = 50421,
    SPELL_DK_SCOURGE_STRIKE_TRIGGERED           = 70890,
    SPELL_DK_SHADOW_OF_DEATH                    = 164047,
    SPELL_DK_SOUL_REAPER_DAMAGE                 = 114867,
    SPELL_DK_SOUL_REAPER_HASTE                  = 215711,
    SPELL_DK_T15_DPS_4P_BONUS                   = 138347,
    SPELL_DK_DEATHS_ADVANCE                     = 48265,
    SPELL_DK_WILL_OF_THE_NECROPOLIS             = 206967,
    SPELL_DK_BLOOD_BOIL_TRIGGERED               = 65658,
    SPELL_DK_BLOOD_GORGED_HEAL                  = 50454,
    SPELL_DK_DEATH_STRIKE_ENABLER               = 89832,
    SPELL_DK_FROST_PRESENCE                     = 48266,
    SPELL_DK_IMPROVED_FROST_PRESENCE            = 50385,
    SPELL_DK_IMPROVED_FROST_PRESENCE_TRIGGERED  = 50385,
    SPELL_DK_IMPROVED_UNHOLY_PRESENCE           = 50392,
    SPELL_DK_IMPROVED_UNHOLY_PRESENCE_TRIGGERED = 55222,
    SPELL_DK_RUNE_TAP                           = 48982,
    SPELL_DK_CORPSE_EXPLOSION_VISUAL            = 51270,
    SPELL_DK_MASTER_OF_GHOULS                   = 52143,
    SPELL_DK_GHOUL_AS_GUARDIAN                  = 46585,
    SPELL_DK_GHOUL_AS_PET                       = 52150,
    SPELL_DK_ROILING_BLOOD                      = 108170,
    SPELL_DK_PESTILENCE                         = 277234,
    SPELL_DK_CHILBLAINS                         = 50041,
    SPELL_DK_CHAINS_OF_ICE_ROOT                 = 53534,
    SPELL_DK_PLAGUE_LEECH                       = 123693,
    SPELL_DK_PERDITION                          = 123981,
    SPELL_DK_SHROUD_OF_PURGATORY                = 116888,
    SPELL_DK_PURGATORY_INSTAKILL                = 123982,
    SPELL_DK_BLOOD_RITES                        = 50034,
    SPELL_DK_DEATH_SIPHON_HEAL                  = 116783,
    SPELL_DK_BLOOD_CHARGE                       = 114851,
    SPELL_DK_BOOD_TAP                           = 45529,
    SPELL_DK_PILLAR_OF_FROST                    = 51271,
    SPELL_DK_CONVERSION                         = 119975,
    SPELL_DK_WEAKENED_BLOWS                     = 115798,
    SPELL_DK_SCARLET_FEVER                      = 81132,
    SPELL_DK_SCENT_OF_BLOOD_AURA                = 50421,
    SPELL_DK_DESECRATED_GROUND                  = 118009,
    SPELL_DK_DESECRATED_GROUND_IMMUNE           = 115018,
    SPELL_DK_ASPHYXIATE                         = 108194,
    SPELL_DK_DARK_INFUSION_STACKS               = 91342,
    SPELL_DK_DARK_INFUSION_AURA                 = 93426,
    SPELL_DK_RUNIC_CORRUPTION_REGEN             = 51460,
    SPELL_DK_RUNIC_EMPOWERMENT                  = 81229,
    SPELL_DK_GOREFIENDS_GRASP_GRIP_VISUAL       = 114869,
    SPELL_DK_SLUDGE_BELCHER_AURA                = 207313,
    SPELL_DK_SLUDGE_BELCHER_ABOMINATION         = 212027,
    SPELL_DK_RAISE_DEAD                         = 46584,
    SPELL_DK_RAISE_DEAD_GHOUL                   = 52150,
    SPELL_DK_GEIST_TRANSFORM                    = 121916,
    SPELL_DK_ANTI_MAGIC_BARRIER                 = 205725,
    SPELL_DK_RUNIC_CORRUPTION                   = 51462,
    SPELL_DK_NECROSIS                           = 207346,
    SPELL_DK_NECROSIS_EFFECT                    = 216974,
    SPELL_DK_ALL_WILL_SERVE                     = 194916,
    SPELL_DK_ALL_WILL_SERVE_SUMMON              = 196910,
    SPELL_DK_BREATH_OF_SINDRAGOSA               = 152279,
    SPELL_DK_DEATH_GRIP_ONLY_JUMP               = 146599,
    SPELL_DK_HEART_STRIKE                       = 206930,
    SPELL_DK_FESTERING_WOUND                    = 194310,
    SPELL_DK_FESTERING_WOUND_DAMAGE             = 194311,
    SPELL_DK_BONE_SHIELD                        = 195181,
    SPELL_DK_BLOOD_MIRROR_DAMAGE                = 221847,
    SPELL_DK_BLOOD_MIRROR                       = 206977,
    SPELL_DK_BONESTORM_HEAL                     = 196545,
    SPELL_DK_GLACIAL_ADVANCE                    = 194913,
    SPELL_DK_GLACIAL_ADVANCE_DAMAGE             = 195975,
    SPELL_DK_HOWLING_BLAST                      = 49184,
    SPELL_DK_HOWLING_BLAST_AOE                  = 237680,
    SPELL_DK_RIME_BUFF                          = 59052,
    SPELL_DK_NORTHREND_WINDS                    = 204088,
    SPELL_DK_KILLING_MACHINE                    = 51124,
    SPELL_DK_REMORSELESS_WINTER_SLOW_DOWN       = 211793,
    SPELL_DK_EPIDEMIC                           = 207317,
    SPELL_DK_EPIDEMIC_DAMAGE_SINGLE             = 212739,
    SPELL_DK_EPIDEMIC_DAMAGE_AOE                = 215969,
    SPELL_DK_VIRULENT_PLAGUE                    = 191587,
    SPELL_DK_VIRULENT_ERUPTION                  = 191685,
    SPELL_DK_OUTBREAK_PERIODIC                  = 196782,
    SPELL_DK_DEFILE                             = 152280,
    SPELL_DK_DEFILE_DAMAGE                      = 156000,
    SPELL_DK_DEFILE_DUMMY                       = 156004,
    SPELL_DK_DEFILE_MASTERY                     = 218100,
    SPELL_DK_UNHOLY_FRENZY                      = 207289,
    SPELL_DK_UNHOLY_FRENZY_BUFF                 = 207290,
    SPELL_DK_PESTILENT_PUSTULES                 = 194917,
    SPELL_DK_CASTIGATOR                         = 207305,
    SPELL_DK_UNHOLY_VIGOR                       = 196263,
    SPELL_DK_BLOD_HEARTBREAKER_ENERGIZE         = 210738,
    SPELL_AURA_DK_HEARTBREAKER                  = 221536,
    SPELL_DK_BLODD_DANCING_RUNE_WEAPON          = 49028,
    SPELL_DK_BLODD_DANCING_RUNE_WEAPON_ENERGIZE = 81256,
    SPELL_DK_PERMAFROST                         = 207200,
    SPELL_DK_RAPID_DECOMPOSITION_ENERGIZE       = 255203,
    SPELL_DK_OBLITERATE                         = 49020,
    SPELL_AURA_DK_RAPID_DECOMPOSITION           = 194662,
    SPELL_DK_GATHERING_STORM                    = 194912,
    SPELL_DK_GATHERING_STORM_DAMAGE             = 211805,
    SPELL_DK_REMORSELESS_WINTER                 = 196770,
    SPELL_DK_FROSTSCYTHE                        = 207230,
    SPELL_DK_PATH_OF_FROST                      = 3714,
    SPELL_DK_CONTROL_UNDEATH                    = 111673,
    SPELL_DK_VAMPIRIC_BLOOD                     = 55233,
	SPELL_DK_BLOODWORMS                         = 195679,
	SPELL_DK_BLOODWORM_HEAL                     = 197509,
	SPELL_DK_DEATH_AND_DECAY                    = 43265,
    SPELL_DK_ARMY_OF_DEATH                      = 42651,
    SPELL_DK_APOCALYPSE                         = 275699,
	SPELL_DK_DARK_SUCCOR                        = 101568,
	SPELL_DK_DEATH_STRIKE                       = 49998,
	SPELL_DK_BURSTING_SORES                     = 207264,
	SPELL_DK_BURSTING_SORES_EXPLOSION           = 207267,
    SPELL_DK_GRIP_OF_THE_DEAD                   = 273952,
    SPELL_DK_GRIP_OF_THE_DEAD_SLOW              = 273977,
    SPELL_DK_GRIP_OF_THE_DEAD_TICK              = 273980,
    SPELL_DK_GRIP_OF_THE_DEAD_REDUCTION         = 273984,
    SPELL_DK_DEATH_COIL                         = 47541,
	SPELL_DK_ARMY_OF_DEATH_TRIGGER              = 42650,
    SPELL_DK_ARMY_OF_THE_DAMNED                 = 276837,
    SPELL_DK_VORACIUS                           = 273953,
    SPELL_DK_VORACIUS_LEECH                     = 274009,
	SPELL_DK_INEXORABLE_ASSAULT					= 253595,
	SPELL_DK_INEXORABLE_ASSAULT_DAMAGE			= 253597,
	SPELL_DK_RIME								= 59057,
	SPELL_DK_COLD_HEART							= 281209,
	SPELL_DK_COLD_HEART_DAMAGE					= 281210,
	SPELL_DK_AVALANCHE_DAMAGE					= 207150,
	SPELL_DK_RUNE_STRIKE						= 210764,
	SPELL_DK_OSSUARY							= 219786,
	SPELL_DK_OSSUARY_BUFF						= 219788,
	SPELL_DK_TOMBSTONE							= 219809,
	SPELL_DK_MARK_OF_BLODD_HEAL					= 206945,
	SPELL_DK_BONESTORM							= 194844,
	SPELL_DK_NECROTIC_AURA_TALENT				= 199642,
	SPELL_DK_NECROTIC_AURA						= 214968,
	SPELL_DK_BLOOD_BOIL							= 50842,
	SPELL_DK_HEMOSTATIS_AURA					= 273947,
    SPELL_DK_HEARTSTOP_AURA_TALENT              = 199719,
	SPELL_DK_HEARTSTOP_AURA                     = 214975,
    SPELL_DK_FROST_SHIELD                       = 207203,
	SPELL_DK_ANTIMAGIC_ZONE_AURA				= 145629,
	SPELL_DK_NECROTIC_WOUND						= 223929,
	SPELL_DK_CRYPT_FEVER						= 199722,
	SPELL_DK_CRYPT_FEVER_DAMAGE					= 199723,
	SPELL_DK_UNHOLY_MUTATION					= 201934,
	SPELL_DK_UNHOLY_MUTATION_DAMAGE				= 200646,
	SPELL_DK_REANIMATION_DAMAGE					= 210141,
	SPELL_DK_DEATHCHILL							= 204080,
	SPELL_DK_DEATHCHILL_ROOT					= 204085,
	SPELL_DK_FROZEN_CENTER						= 204135,
	SPELL_DK_FROZEN_CENTER_ROOT					= 233395,
	SPELL_DK_WALKING_DEATH						= 202731,
	SPELL_DK_WALKING_DEATH_DEBUFF				= 212610,
	SPELL_DK_DEATH_CHAIN						= 203173,
	SPELL_DK_DEATH_CHAIN_VISUAL					= 203203,
	SPELL_DK_DEATH_CHAIN_DAMAGE					= 203174,
	SPELL_DK_FROST_STRIKE_MAIN_HAND				= 222026,
	SPELL_DK_THUNDRA_STALKER					= 279941,
	SPELL_DK_THUNDRA_STALKER_BUFF				= 279942,
	SPELL_DK_WANDERING_PLAGUE					= 199725,
	SPELL_DK_WANDERING_PLAGUE_DISEASE			= 199969,
	SPELL_DK_WANDERING_PLAGUE_SELECTOR			= 200093,
	SPELL_DK_UNHOLY_BLIGHT						= 115994,
	SPELL_DK_OUTBREAK							= 77575,
	SPELL_DK_OBLITERATE_MAIN_HAND				= 222024,
	SPELL_DK_OBLITERATE_OFF_HAND				= 66198,
	SPELL_DK_FROST_FEVER_ENERGIZE				= 195617,
	SPELL_DK_FROST_FEVER_PROC					= 195621,
	SPELL_DK_ICECAP								= 207126,
    SPELL_DK_OBLITERATION                       = 281238,
    SPELL_DK_OBLITERATION_PROC                  = 207256,
    SPELL_DK_MURDEROUS_EFFICIENCY               = 207061,
    SPELL_DK_CHILL_STREAK_MISSILE               = 204199,
    SPELL_DK_CHILL_STREAK_DAMAGE                = 204167,
    SPELL_DK_CHILL_STREAK_SELECTOR              = 204165,
    SPELL_DK_CHILL_STREAK_SLOW                  = 204206,
    SPELL_DK_RAZORICE                           = 51714,
    SPELL_DK_FROSTWYRM_FROZEN_FLOOR             = 279306,
    SPELL_DK_FROSTWYRM_BREATH                   = 279307,
    SPELL_DK_FROSTWYRM_DAMAGE                   = 279303,
    SPELL_DK_DEATH_STRIKE_RANK_2                = 278223,
    SPELL_DK_ANTIMAGIC_SHIELD                   = 48707,
    SPELL_DK_VOLATILE_SHIELD                    = 207188,
    SPELL_DK_ANTIMAGIC_BARRIER                  = 205727,
    SPELL_DK_KILLER_FROST_POWER                 = 278480,
    SPELL_DK_BONE_SPIKE_GRAVEYARD_POWER         = 273088,
    SPELL_DK_BONE_SPIKE_GRAVEYARD_DAMAGE        = 273089,
    SPELL_DK_HARROWING_DECAY_POWER              = 275929,
    SPELL_DK_HARROWING_DECAY_DEBUFF             = 275931,
    SPELL_DK_HORRID_EXPERIMENTATION_POWER       = 273095,
    SPELL_DK_HORRID_EXPERIMENTATION_DAMAGE      = 273096,
    SPELL_DK_MARROWREND                         = 195182,
    SPELL_DK_CRIMSON_SCOURGE                    = 81141,
    SPELL_DK_LAST_SURPRISE_POWER                = 278489,
    SPELL_DK_LAST_SURPRISE_DAMAGE               = 279606,
    SPELL_DK_DARK_TRANSFORMATION                = 63560,
    SPELL_DK_INFECTED_CLAWS                     = 207272,
    SPELL_DK_SUDDEN_DOOM                        = 81340,
    SPELL_DK_OBLITERATION_ENERGIZE              = 281327,
    SPELL_DK_RUNIC_EMPOWERMENT_ENERGIZE         = 193486,
    SPELL_DK_MURDEROUS_EFFICIENCY_ENERGIZE      = 207062,
    SPELL_DK_REANIMATION                        = 210128,
    SPELL_DK_DARK_SIMULACRUM_PROC               = 77606,
    SPELL_DK_DARK_SIMULACRUM_REPLACER           = 77616,
    SPELL_DK_DARK_SIMULACRUM_MODS               = 94984,
    SPELL_DK_FESTERMIGHT_AURA                   = 274081,
    SPELL_DK_FESTERMIGHT_EFFECT                 = 274373,
    SPELL_DK_CANKEROUS_WOUNDS                   = 278482,
    SPELL_DK_DEEP_CUTS_POWER                    = 272684,
    SPELL_DK_DEEP_CUTS_DEBUFF                   = 272685,
    SPELL_DK_MARROWBLOOD                        = 274057,
    SPELL_DK_ETERNAL_RUNE_WEAPON_BUFF           = 278543,
    SPELL_DK_ETERNAL_RUNE_WEAPON_AURA           = 278479,
    SPELL_DK_DEATHS_ADVANCE_SPEED               = 124285,
};

// 70656 - Advantage (T10 4P Melee Bonus)
class spell_dk_advantage_t10_4p : public SpellScriptLoader
{
public:
    spell_dk_advantage_t10_4p() : SpellScriptLoader("spell_dk_advantage_t10_4p") { }

    class spell_dk_advantage_t10_4p_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_dk_advantage_t10_4p_AuraScript);

        bool CheckProc(ProcEventInfo& eventInfo)
        {
            if (Unit* caster = eventInfo.GetActor())
            {
                Player* player = caster->ToPlayer();
                if (!player  || caster->GetClass() != CLASS_DEATH_KNIGHT)
                    return false;

                for (uint8 i = 0; i < player->GetMaxPower(POWER_RUNES); ++i)
                    if (player->GetRuneCooldown(i) == 0)
                        return false;

                return true;
            }

            return false;
        }

        void Register() override
        {
            DoCheckProc += AuraCheckProcFn(spell_dk_advantage_t10_4p_AuraScript::CheckProc);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_dk_advantage_t10_4p_AuraScript();
    }
};

// 43264 - Periodic Taunt
/// 6.x, does this belong here or in spell_generic? apply this in creature_template_addon? sniffs say this is always cast army of the dead ghouls.
class spell_dk_army_periodic_taunt : public SpellScriptLoader
{
    public:
        spell_dk_army_periodic_taunt() : SpellScriptLoader("spell_dk_army_periodic_taunt") { }

        class spell_dk_army_periodic_taunt_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dk_army_periodic_taunt_SpellScript);

            bool Load() override
            {
                return GetCaster()->IsGuardian();
            }

            SpellCastResult CheckCast()
            {
                if (Unit* owner = GetCaster()->GetOwner())
                    if (!owner->HasAura(SPELL_DK_GLYPH_OF_ARMY_OF_THE_DEAD))
                        return SPELL_CAST_OK;

                return SPELL_FAILED_SPELL_UNAVAILABLE;
            }

            void Register() override
            {
                OnCheckCast += SpellCheckCastFn(spell_dk_army_periodic_taunt_SpellScript::CheckCast);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_dk_army_periodic_taunt_SpellScript();
        }
};

static const uint32 ArmyTransforms[6]
{
    SPELL_DK_ARMY_FLESH_BEAST_TRANSFORM,
    SPELL_DK_ARMY_GEIST_TRANSFORM,
    SPELL_DK_ARMY_NORTHREND_SKELETON_TRANSFORM,
    SPELL_DK_ARMY_SKELETON_TRANSFORM,
    SPELL_DK_ARMY_SPIKED_GHOUL_TRANSFORM,
    SPELL_DK_ARMY_SUPER_ZOMBIE_TRANSFORM
};

// 127517 - Army Transform
/// 6.x, does this belong here or in spell_generic? where do we cast this? sniffs say this is only cast when caster has glyph of foul menagerie.
class spell_dk_army_transform : public SpellScriptLoader
{
    public:
        spell_dk_army_transform() : SpellScriptLoader("spell_dk_army_transform") { }

        class spell_dk_army_transform_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dk_army_transform_SpellScript);

            bool Load() override
            {
                return GetCaster()->IsGuardian();
            }

            SpellCastResult CheckCast()
            {
                if (Unit* owner = GetCaster()->GetOwner())
                    if (owner->HasAura(SPELL_DK_GLYPH_OF_FOUL_MENAGERIE))
                        return SPELL_CAST_OK;

                return SPELL_FAILED_SPELL_UNAVAILABLE;
            }

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                GetCaster()->CastSpell(GetCaster(), ArmyTransforms[urand(0, 5)], true);
            }

            void Register() override
            {
                OnCheckCast += SpellCheckCastFn(spell_dk_army_transform_SpellScript::CheckCast);
                OnEffectHitTarget += SpellEffectFn(spell_dk_army_transform_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_dk_army_transform_SpellScript();
        }
};

// 50842 - Blood Boil
// Last Update 8.0.1 Build 28153
class spell_dk_blood_boil : public SpellScript
{
    PrepareSpellScript(spell_dk_blood_boil);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        if (!sSpellMgr->GetSpellInfo(SPELL_DK_BLOOD_PLAGUE))
            return false;
        return true;
    }

    void HandleOnHit(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();

        if (!caster || !target)
            return;

        caster->CastSpell(target, SPELL_DK_BLOOD_PLAGUE, true);
        DeathKnight::ApplySuperstrain(caster, target, SPELL_DK_BLOOD_PLAGUE);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_dk_blood_boil::HandleOnHit, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

// 55078 - Blood Plague
// Last Update 8.0.1 Build 28153
class spell_dk_blood_plague : public AuraScript
{
    PrepareAuraScript(spell_dk_blood_plague);

    void HandleApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Unit* caster = GetCaster();
        Unit* owner = GetUnitOwner();
        if (!caster || !owner)
            return;

        if (AuraEffect * aurEff = owner->GetAuraEffect(SPELL_DK_DEEP_CUTS_DEBUFF, EFFECT_0, caster->GetGUID()))
            GetAura()->GetEffect(EFFECT_0)->SetDamage(GetAura()->GetEffect(EFFECT_0)->GetDamage() + aurEff->GetAmount());
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_dk_blood_plague::HandleApply, EFFECT_0, SPELL_AURA_PERIODIC_LEECH, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
    }
};

// 43265 - Death and Decay
//Last Update 8.0.1 Build 28153
class spell_dk_death_and_decay : public SpellScriptLoader
{
    public:
        spell_dk_death_and_decay() : SpellScriptLoader("spell_dk_death_and_decay") { }

        class spell_dk_death_and_decay_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dk_death_and_decay_SpellScript);

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                Unit* caster = GetCaster();
                WorldLocation const* pos = GetExplTargetDest();
                if (!caster || !pos)
                    return;
                
                // Bone Spike Graveyard
                if (Aura* aura = caster->GetAura(SPELL_DK_BONE_SPIKE_GRAVEYARD_POWER))
                {
                    int32 damage = aura->GetEffect(0)->GetAmount();
                    caster->CastCustomSpell(pos->GetPositionX(), pos->GetPositionY(), pos->GetPositionZ(), SPELL_DK_BONE_SPIKE_GRAVEYARD_DAMAGE, &damage, NULL, NULL, true);
                }
            }

            void HandleAfterCast()
            {
                if (Unit* caster = GetCaster())
                    caster->RemoveAurasDueToSpell(SPELL_DK_CRIMSON_SCOURGE);
            }

            void Register() override
            {
                OnEffectHitTarget += SpellEffectFn(spell_dk_death_and_decay_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
                AfterCast += SpellCastFn(spell_dk_death_and_decay_SpellScript::HandleAfterCast);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_dk_death_and_decay_SpellScript();
        }
};

// 47541 - Death Coil
class spell_dk_death_coil : public SpellScript
{
    PrepareSpellScript(spell_dk_death_coil);

    bool Validate(SpellInfo const* /*spell*/) override
    {
		return ValidateSpellInfo({ SPELL_DK_DEATH_COIL_DAMAGE} );
    }

    void HandleDummy(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;
        
        caster->CastSpell(target, SPELL_DK_DEATH_COIL_DAMAGE, true);

        // Necrosis
        if (caster->HasAura(SPELL_DK_NECROSIS))
            caster->CastSpell(caster, SPELL_DK_NECROSIS_EFFECT, true);

        // Harrowing Decay
        if (Aura* aura = caster->GetAura(SPELL_DK_HARROWING_DECAY_POWER))
            caster->CastCustomSpell(SPELL_DK_HARROWING_DECAY_DEBUFF, SPELLVALUE_BASE_POINT0, aura->GetEffect(0)->GetAmount(), target, true);

        caster->GetSpellHistory()->ModifyCooldown(SPELL_DK_DARK_TRANSFORMATION, -1s);

        if (Aura* aura = caster->GetAura(SPELL_DK_SUDDEN_DOOM))
            aura->ModStackAmount(-1);

        if (caster->HasAura(SPELL_DK_ARMY_OF_THE_DAMNED))
        {
            caster->GetSpellHistory()->ModifyCooldown(SPELL_DK_ARMY_OF_DEATH_TRIGGER, -5s);
            caster->GetSpellHistory()->ModifyCooldown(SPELL_DK_APOCALYPSE, -1s);
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_dk_death_coil::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

// 52751 - Death Gate
class spell_dk_death_gate : public SpellScriptLoader
{
    public:
        spell_dk_death_gate() : SpellScriptLoader("spell_dk_death_gate") { }

        class spell_dk_death_gate_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dk_death_gate_SpellScript);

            SpellCastResult CheckClass()
            {
                if (GetCaster()->GetClass() != CLASS_DEATH_KNIGHT)
                {
                    SetCustomCastResultMessage(SPELL_CUSTOM_ERROR_MUST_BE_DEATH_KNIGHT);
                    return SPELL_FAILED_CUSTOM_ERROR;
                }

                return SPELL_CAST_OK;
            }

            void HandleScript(SpellEffIndex effIndex)
            {
                PreventHitDefaultEffect(effIndex);
                Unit* target = GetHitUnit();
                if (!target)
                    return;

                if (Player* player = target->ToPlayer())
                {
                    player->CastSpell(player, GetEffectValue(), true);
                }
            }

            void Register() override
            {
                OnCheckCast += SpellCheckCastFn(spell_dk_death_gate_SpellScript::CheckClass);
                OnEffectHitTarget += SpellEffectFn(spell_dk_death_gate_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_dk_death_gate_SpellScript();
        }
};

// 48743 - Death Pact Last Update 8.0.1 Build 28153
class spell_dk_death_pact : public SpellScriptLoader
{
    public:
        spell_dk_death_pact() : SpellScriptLoader("spell_dk_death_pact") { }

        class spell_dk_death_pact_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dk_death_pact_AuraScript);

            void HandleCalcAmount(AuraEffect const* /*aurEff*/, int32& amount, bool& canBeRecalculated)
            { 
                if(Unit* caster = GetCaster())
                    if (SpellInfo const* spellInfo = GetSpellInfo())
                        amount = int32(caster->CountPctFromMaxHealth(spellInfo->GetEffect(EFFECT_2).BasePoints));
            }

            void HandleAbsorb(AuraEffect* aurEff, HealInfo& healInfo, uint32& absorbAmount)
            {
                if (healInfo.GetSpellInfo() && healInfo.GetSpellInfo()->Id == GetId())
                    absorbAmount = 0;                
            }

            void Register() override
            {
                DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_dk_death_pact_AuraScript::HandleCalcAmount, EFFECT_1, SPELL_AURA_SCHOOL_HEAL_ABSORB);
                OnEffectHealAbsorb += AuraEffectHealAbsorbFn(spell_dk_death_pact_AuraScript::HandleAbsorb, EFFECT_1);
            }
        };

        AuraScript* GetAuraScript() const override
        {
            return new spell_dk_death_pact_AuraScript();
        }
};

// 49998 - Death Strike
// Last Update 8.0.1 Build 28153
class spell_dk_death_strike : public SpellScriptLoader
{
    public:
        spell_dk_death_strike() : SpellScriptLoader("spell_dk_death_strike") { }

        class spell_dk_death_strike_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dk_death_strike_SpellScript);

            bool Validate(SpellInfo const* /*spellInfo*/) override
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_DK_DEATH_STRIKE_HEAL) ||
                    !sSpellMgr->GetSpellInfo(SPELL_DK_BLOOD_SHIELD_MASTERY) ||
                    !sSpellMgr->GetSpellInfo(SPELL_DK_BLOOD_SHIELD_ABSORB))
                    return false;
                return true;
            }

            void HandleHeal(SpellEffIndex /*effIndex*/)
            {
                if (Unit* caster = GetCaster())
                {
                    const SpellInfo* spell = sSpellMgr->GetSpellInfo(SPELL_DK_DEATH_STRIKE);
                    int64 damage = caster->GetDamageOverLastSeconds(spell->GetEffect(EFFECT_3).BasePoints);
                    int64 healmin = CalculatePct(caster->GetMaxHealth(), spell->GetEffect(EFFECT_2).BasePoints + (caster->HasAura(SPELL_DK_DEATH_STRIKE_RANK_2) ? 3 : 0));
                    int64 healmax = CalculatePct(damage, spell->GetEffect(EFFECT_1).BasePoints + (caster->HasAura(SPELL_DK_DEATH_STRIKE_RANK_2) ? 10 : 0));
                    int64 heal = std::max(healmin, healmax);

                    if (caster->HasAura(SPELL_DK_DARK_SUCCOR))
                        heal += healmax;

                    if(Aura* aura = caster->GetAura(SPELL_DK_BONE_SHIELD))
                        if(AuraEffect* auraEff = caster->GetAuraEffect(SPELL_DK_MARROWBLOOD, EFFECT_0))
                            heal += (auraEff->GetAmount() * aura->GetStackAmount());

                    caster->CastCustomSpell(SPELL_DK_DEATH_STRIKE_HEAL, SPELLVALUE_BASE_POINT0, heal, caster, true);

                    // todo, if SPELL_AURA_MOD_ABSORB_PERCENTAGE will not apply to SPELL_DAMAGE_CLASS_NONE, resolve must be applied here.
                    if (AuraEffect const* aurEff = caster->GetAuraEffect(SPELL_DK_BLOOD_SHIELD_MASTERY, EFFECT_0))
                        caster->CastCustomSpell(SPELL_DK_BLOOD_SHIELD_ABSORB, SPELLVALUE_BASE_POINT0, CalculatePct(heal, aurEff->GetAmount()), caster);

                    if (caster->HasAura(SPELL_DK_VORACIUS))
                        caster->CastSpell(caster, SPELL_DK_VORACIUS_LEECH, true);

                    if (caster->HasAura(SPELL_DK_HEMOSTATIS_AURA))
                        caster->RemoveAura(SPELL_DK_HEMOSTATIS_AURA);

                    caster->RemoveAurasDueToSpell(SPELL_DK_DARK_SUCCOR);
                }
            }

            void Register() override
            {
                OnEffectHitTarget += SpellEffectFn(spell_dk_death_strike_SpellScript::HandleHeal, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_dk_death_strike_SpellScript();
        }
};

// 85948 - Festering Strike
class spell_dk_festering_strike : public SpellScript
{
    PrepareSpellScript(spell_dk_festering_strike);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_DK_FESTERING_WOUND });
    }

    void HandleFesteringWounds(SpellEffIndex effIndex)
    {
		Unit* caster = GetCaster();
		Unit* target = GetHitUnit();
		if (!caster || !target)
			return;

        uint32 amount = 2;
        uint32 chance = 50;

        if (caster->HasAura(SPELL_DK_CANKEROUS_WOUNDS))
            chance += sSpellMgr->GetSpellInfo(SPELL_DK_CANKEROUS_WOUNDS)->GetEffect(EFFECT_1).BasePoints;

        if (roll_chance_i(chance))
            amount++;

        for (uint8 i = 0; i < amount; ++i)
            caster->CastSpell(target, SPELL_DK_FESTERING_WOUND, true);
        }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_dk_festering_strike::HandleFesteringWounds, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

// 47496 - Explode, Ghoul spell for Corpse Explosion
class spell_dk_ghoul_explode : public SpellScript
{
    PrepareSpellScript(spell_dk_ghoul_explode);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_DK_CORPSE_EXPLOSION_TRIGGERED });
    }

    void HandleDamage(SpellEffIndex /*effIndex*/)
    {
        SetHitDamage(GetCaster()->CountPctFromMaxHealth(GetEffectInfo(EFFECT_2).CalcValue(GetCaster())));
    }

    void Suicide(SpellEffIndex /*effIndex*/)
    {
        // Corpse Explosion (Suicide)
        if (Unit* unitTarget = GetHitUnit())
            unitTarget->CastSpell(unitTarget, SPELL_DK_CORPSE_EXPLOSION_TRIGGERED, true);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_dk_ghoul_explode::HandleDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
        OnEffectHitTarget += SpellEffectFn(spell_dk_ghoul_explode::Suicide, EFFECT_1, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

// 58677 - Glyph of Death's Embrace
/// 6.x
class spell_dk_glyph_of_deaths_embrace : public SpellScriptLoader
{
    public:
        spell_dk_glyph_of_deaths_embrace() : SpellScriptLoader("spell_dk_glyph_of_deaths_embrace") { }

        class spell_dk_glyph_of_deaths_embrace_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dk_glyph_of_deaths_embrace_AuraScript);

            bool CheckProc(ProcEventInfo& eventInfo)
            {
                Unit* actionTarget = eventInfo.GetActionTarget();
                return actionTarget && actionTarget->GetCreatureType() == CREATURE_TYPE_UNDEAD && actionTarget->GetOwner();
            }

            void Register() override
            {
                DoCheckProc += AuraCheckProcFn(spell_dk_glyph_of_deaths_embrace_AuraScript::CheckProc);
            }
        };

        AuraScript* GetAuraScript() const override
        {
            return new spell_dk_glyph_of_deaths_embrace_AuraScript();
        }
};

// 159429 - Glyph of Runic Power
/// 6.x
class spell_dk_glyph_of_runic_power : public SpellScriptLoader
{
    public:
        spell_dk_glyph_of_runic_power() : SpellScriptLoader("spell_dk_glyph_of_runic_power") { }

        class spell_dk_glyph_of_runic_power_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dk_glyph_of_runic_power_AuraScript);

            bool Validate(SpellInfo const* /*spellInfo*/) override
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_DK_GLYPH_OF_RUNIC_POWER_TRIGGERED))
                    return false;
                return true;
            }

            bool Load() override
            {
                return GetUnitOwner()->GetClass() == CLASS_DEATH_KNIGHT;
            }

            bool CheckProc(ProcEventInfo& eventInfo)
            {
                return eventInfo.GetSpellInfo() && (eventInfo.GetSpellInfo()->GetAllEffectsMechanicMask() & (1 << MECHANIC_SNARE | 1 << MECHANIC_ROOT | 1 << MECHANIC_FREEZE));
            }

            void HandleProc(ProcEventInfo& eventInfo)
            {
                if (Unit* target = eventInfo.GetProcTarget())
                    target->CastSpell(target, SPELL_DK_GLYPH_OF_RUNIC_POWER_TRIGGERED, true);
            }

            void Register() override
            {
                DoCheckProc += AuraCheckProcFn(spell_dk_glyph_of_runic_power_AuraScript::CheckProc);
                OnProc += AuraProcFn(spell_dk_glyph_of_runic_power_AuraScript::HandleProc);
            }
        };

        AuraScript* GetAuraScript() const override
        {
            return new spell_dk_glyph_of_runic_power_AuraScript();
        }
};

// 48792 - Icebound Fortitude
/// 6.x
class spell_dk_icebound_fortitude : public SpellScriptLoader
{
    public:
        spell_dk_icebound_fortitude() : SpellScriptLoader("spell_dk_icebound_fortitude") { }

        class spell_dk_icebound_fortitude_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dk_icebound_fortitude_AuraScript);

            void CalculateAmount(AuraEffect const* /*aurEff*/, int32& amount, bool& /*canBeRecalculated*/)
            {
                if (GetUnitOwner()->HasAura(SPELL_DK_IMPROVED_BLOOD_PRESENCE))
                    amount += 30; /// todo, figure out how tooltip is updated
            }

            void Register() override
            {
                DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_dk_icebound_fortitude_AuraScript::CalculateAmount, EFFECT_2, SPELL_AURA_MOD_DAMAGE_PERCENT_TAKEN);
            }
        };

        AuraScript* GetAuraScript() const override
        {
            return new spell_dk_icebound_fortitude_AuraScript();
        }
};

// 121916 - Glyph of the Geist (Unholy)
/// 6.x, does this belong here or in spell_generic? apply this in creature_template_addon? sniffs say this is always cast on raise dead.
class spell_dk_pet_geist_transform : public SpellScriptLoader
{
    public:
        spell_dk_pet_geist_transform() : SpellScriptLoader("spell_dk_pet_geist_transform") { }

        class spell_dk_pet_geist_transform_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dk_pet_geist_transform_SpellScript);

            bool Load() override
            {
                return GetCaster()->IsPet();
            }

            SpellCastResult CheckCast()
            {
                if (Unit* owner = GetCaster()->GetOwner())
                    if (owner->HasAura(SPELL_DK_GLYPH_OF_THE_GEIST))
                        return SPELL_CAST_OK;

                return SPELL_FAILED_SPELL_UNAVAILABLE;
            }

            void Register() override
            {
                OnCheckCast += SpellCheckCastFn(spell_dk_pet_geist_transform_SpellScript::CheckCast);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_dk_pet_geist_transform_SpellScript();
        }
};

// 147157 Glyph of the Skeleton (Unholy)
/// 6.x, does this belong here or in spell_generic? apply this in creature_template_addon? sniffs say this is always cast on raise dead.
class spell_dk_pet_skeleton_transform : public SpellScriptLoader
{
    public:
        spell_dk_pet_skeleton_transform() : SpellScriptLoader("spell_dk_pet_skeleton_transform") { }

        class spell_dk_pet_skeleton_transform_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dk_pet_skeleton_transform_SpellScript);

            SpellCastResult CheckCast()
            {
                if (Unit* owner = GetCaster()->GetOwner())
                    if (owner->HasAura(SPELL_DK_GLYPH_OF_THE_SKELETON))
                        return SPELL_CAST_OK;

                return SPELL_FAILED_SPELL_UNAVAILABLE;
            }

            void Register() override
            {
                OnCheckCast += SpellCheckCastFn(spell_dk_pet_skeleton_transform_SpellScript::CheckCast);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_dk_pet_skeleton_transform_SpellScript();
        }
};

// 46584 - Raise Dead
class spell_dk_raise_dead : public SpellScriptLoader
{
    public:
        spell_dk_raise_dead() : SpellScriptLoader("spell_dk_raise_dead") { }

        class spell_dk_raise_dead_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dk_raise_dead_SpellScript);

        public:
            spell_dk_raise_dead_SpellScript() { }

        private:
            bool Validate(SpellInfo const* /*spellInfo*/) override
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_DK_RAISE_DEAD)||
                    !sSpellMgr->GetSpellInfo(SPELL_DK_SLUDGE_BELCHER_ABOMINATION)||
                    !sSpellMgr->GetSpellInfo(SPELL_DK_SLUDGE_BELCHER_AURA)||
                    !sSpellMgr->GetSpellInfo(SPELL_DK_RAISE_DEAD_GHOUL))
                    return false;
                return true;
            }

            bool Load() override
            {
                return GetCaster()->GetTypeId() == TYPEID_PLAYER;
            }

            void HandleDummy()
            {
                Unit* caster = GetCaster();

                if (caster->HasAura(SPELL_DK_SLUDGE_BELCHER_AURA))
                    caster->CastSpell((Unit*)nullptr, SPELL_DK_SLUDGE_BELCHER_ABOMINATION, true);
                else
                {
                    caster->CastSpell((Unit*)nullptr, SPELL_DK_RAISE_DEAD_GHOUL, true);
                    if (caster->HasAura(58640)) //Glyph of the Geist
                    {
                        if (Guardian* pet = caster->ToPlayer()->GetGuardianPet())
                            pet->CastSpell(pet, SPELL_DK_GEIST_TRANSFORM, true);
                    }
                }

                if (caster->HasAura(SPELL_DK_ALL_WILL_SERVE))
                {
                    caster->CastSpell(caster, SPELL_DK_ALL_WILL_SERVE_SUMMON, true);
                }
            }

            void Register() override
            {
                OnCast += SpellCastFn(spell_dk_raise_dead_SpellScript::HandleDummy);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_dk_raise_dead_SpellScript();
        }
};

// 130736 - Soul Reaper
// 8.x
class aura_dk_soul_reaper: public AuraScript
{
    PrepareAuraScript(aura_dk_soul_reaper);

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Unit * caster = GetCaster();
        Unit * target = GetUnitOwner();

        if (!caster || !target)
            return;

        if (GetTargetApplication()->GetRemoveMode() != AURA_REMOVE_BY_DEATH)
            return;

        if (!caster->ToPlayer()->isHonorOrXPTarget(target))
            return;

        caster->CastSpell(caster, SPELL_DK_SOUL_REAPER_HASTE, true);
    }

    void Register() override
    {
        AfterEffectRemove += AuraEffectApplyFn(aura_dk_soul_reaper::HandleRemove, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE, AURA_EFFECT_HANDLE_REAL);
    }
};

// 206967 - Will of the Necropolis
class spell_dk_will_of_the_necropolis : public AuraScript
{
    PrepareAuraScript(spell_dk_will_of_the_necropolis);

    void CalculateAmount(AuraEffect const* /*p_AuraEffect*/, int32& p_Amount, bool& /*p_CanBeRecalculated*/)
    {
        p_Amount = -1;
    }

    void Absorb(AuraEffect* /*auraEffect*/, DamageInfo& dmgInfo, uint32& absorbAmount)
    {
        absorbAmount = 0;

        if (GetTarget()->GetHealthPct() < GetEffect(EFFECT_2)->GetBaseAmount())
            absorbAmount = CalculatePct(dmgInfo.GetDamage(), GetEffect(EFFECT_1)->GetBaseAmount());
    }

    void Register() override
    {
        DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_dk_will_of_the_necropolis::CalculateAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
        OnEffectAbsorb += AuraEffectAbsorbFn(spell_dk_will_of_the_necropolis::Absorb, EFFECT_0);
    }
};

// Called by 49576 - Death Grip
//Last Update 8.0.1 Build 28153
class spell_dk_death_grip_initial : public SpellScript
{
    PrepareSpellScript(spell_dk_death_grip_initial);

    bool Validate(SpellInfo const* /*spellinfo*/) override
    {
        return ValidateSpellInfo({  SPELL_DK_DEATH_GRIP,
                                    SPELL_DK_DEATH_GRIP_PULL,
                                    SPELL_DK_DEATH_GRIP_VISUAL,
                                    SPELL_DK_DEATH_GRIP_TAUNT });
    }

    SpellCastResult CheckCast()
    {
        Unit* caster = GetCaster();

        // Death Grip should not be castable while jumping/falling
        if (caster->HasUnitState(UNIT_STATE_JUMPING) || caster->HasUnitMovementFlag(MOVEMENTFLAG_FALLING))
            return SPELL_FAILED_MOVING;

        // Patch 3.3.3 (2010-03-23): Minimum range has been changed to 8 yards in PvP.
        Unit* target = GetExplTargetUnit();
        if (target && target->IsPlayer())
            if (caster->GetDistance(target) < 8.f)
                return SPELL_FAILED_TOO_CLOSE;

        return SPELL_CAST_OK;
    }

    void HandleOnCast()
    {
        Unit* caster = GetCaster();
        Unit* target = GetExplTargetUnit();

        if (!caster || !target)
            return;

        if (!target->HasAuraType(SPELL_AURA_DEFLECT_SPELLS))
            caster->CastSpell(target, SPELL_DK_DEATH_GRIP_VISUAL, true);
    }

    void HandleScriptEffect(SpellEffIndex /*effIndex*/)
	{
		Unit* caster = GetCaster();
		Unit* target = GetHitUnit();
		if (!caster || !target)
			return;

        if (!target->HasAuraType(SPELL_AURA_DEFLECT_SPELLS))
        {
            target->CastSpell(caster, SPELL_DK_DEATH_GRIP_PULL, true);

            if (caster->IsPlayer() && caster->ToPlayer()->GetSpecializationId() == TALENT_SPEC_DEATHKNIGHT_BLOOD)
                caster->CastSpell(target, SPELL_DK_DEATH_GRIP_TAUNT, true);
        }

        if (caster->HasAura(SPELL_DK_DEATHCHILL))
        {
            if (!target->HasAura(SPELL_DK_CHAINS_OF_ICE, caster->GetGUID()))
                caster->CastSpell(target, SPELL_DK_CHAINS_OF_ICE, true);
            else
            {
                caster->CastSpell(target, SPELL_DK_DEATHCHILL_ROOT, true);
                target->RemoveAurasDueToSpell(SPELL_DK_CHAINS_OF_ICE, caster->GetGUID());
            }
        }

		if (caster->HasAura(SPELL_DK_WALKING_DEATH))
			caster->CastSpell(target, SPELL_DK_WALKING_DEATH_DEBUFF, true);

        /// Unending Grip
        if (auto eff = caster->GetAuraEffect(338311, EFFECT_0))
            if (eff->ConduitRankEntry)
                caster->CastSpell(target, 338312, CastSpellExtraArgs(true).AddSpellBP0(eff->ConduitRankEntry->AuraPointsOverride));

        if (caster->HasAura(DeathKnight::eLegendary::GripOfTheEverlasting))
        {
            caster->CastSpell(caster, DeathKnight::eLegendary::GripOfTheEverlastingBuff, true);
            caster->GetSpellHistory()->ModifyCooldown(SPELL_DK_DEATH_GRIP, -15000);
        }
	}

    void Register() override
    {
        OnCheckCast += SpellCheckCastFn(spell_dk_death_grip_initial::CheckCast);
        OnCast += SpellCastFn(spell_dk_death_grip_initial::HandleOnCast);
        OnEffectHitTarget += SpellEffectFn(spell_dk_death_grip_initial::HandleScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
    }
};

// 63560 - Dark transformation
class spell_dk_dark_transformation_form : public SpellScript
{
    PrepareSpellScript(spell_dk_dark_transformation_form);

    enum DarkTransformation
    {
        UnholyPactTalent = 319230,
        UnholyPactTrigger = 319232,
        UnholyPactDmg = 319236,
    };

    void HandleOnHit()
    {
        if (Player* _player = GetCaster()->ToPlayer())
        {
            if (Unit* pet = GetHitUnit())
            {
                if (_player->HasAura(UnholyPactTalent))
                {
                    _player->CastSpell(pet, UnholyPactTrigger, true);
                }

                if (pet->HasAura(SPELL_DK_DARK_INFUSION_STACKS))
                {
                    _player->RemoveAura(SPELL_DK_DARK_INFUSION_STACKS);
                    pet->RemoveAura(SPELL_DK_DARK_INFUSION_STACKS);
                }
            }
        }
    }

    void Register() override
    {
        OnHit += SpellHitFn(spell_dk_dark_transformation_form::HandleOnHit);
    }
};

// 63560 - Dark transformation
class aura_spell_dk_dark_transformation : public AuraScript
{
    PrepareAuraScript(aura_spell_dk_dark_transformation);

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetUnitOwner();
        if (!caster || !target)
            return;

        if (!target->IsAlive())
            return;

        // Horrid Experimentation
        if (Aura* aura = caster->GetAura(SPELL_DK_HORRID_EXPERIMENTATION_POWER))
        {
            Position pos = target->GetPosition();
            int32 damage = aura->GetEffect(0)->GetAmount();
            caster->CastCustomSpell(pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ(), SPELL_DK_HORRID_EXPERIMENTATION_DAMAGE, &damage, NULL, NULL, true);
        }
    }

    void Register() override
    {
        OnEffectRemove += AuraEffectRemoveFn(aura_spell_dk_dark_transformation::HandleRemove, EFFECT_0, SPELL_AURA_MOD_DAMAGE_PERCENT_DONE, AURA_EFFECT_HANDLE_REAL);
    }
};

// Desecrated ground - 118009
class spell_dk_desecrated_ground : public SpellScriptLoader
{
public:
    spell_dk_desecrated_ground() : SpellScriptLoader("spell_dk_desecrated_ground") { }

    class spell_dk_desecrated_ground_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_dk_desecrated_ground_AuraScript);

        void OnTick(AuraEffect const* /* aurEff */)
        {
            if (GetCaster())
                if (DynamicObject* dynObj = GetCaster()->GetDynObject(SPELL_DK_DESECRATED_GROUND))
                    if (GetCaster()->GetDistance(dynObj) <= 8.0f)
                        GetCaster()->CastSpell(GetCaster(), SPELL_DK_DESECRATED_GROUND_IMMUNE, true);
        }

        void Register() override
        {
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_dk_desecrated_ground_AuraScript::OnTick, EFFECT_1, SPELL_AURA_PERIODIC_DUMMY);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_dk_desecrated_ground_AuraScript();
    }
};

// 49184 - Howling Blast
class spell_dk_howling_blast : public SpellScript
{
    PrepareSpellScript(spell_dk_howling_blast);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_DK_OBLITERATION });
    }

    ObjectGuid tar;

    void HandleBeforeCast()
    {
        if (Unit* target = GetExplTargetUnit())
            tar = target->GetGUID();
    }

    void HandleOnHit()
    {
        Unit* target = GetHitUnit();
        Unit* caster = GetCaster();

        if (!caster || !target || !tar)
            return;

        if (target->GetGUID() != tar)
            if (const SpellInfo* info = GetSpellInfo())
                SetHitDamage(int32(GetHitDamage()*info->GetEffect(EFFECT_0).BasePoints / 100));

        caster->CastSpell(target, SPELL_DK_FROST_FEVER, true);
		caster->CastSpell(caster, SPELL_DK_FROST_FEVER_PROC, true);
        DeathKnight::ApplySuperstrain(caster, target, SPELL_DK_FROST_FEVER);

        if (!caster->HasAura(SPELL_DK_NORTHREND_WINDS))
            caster->CastSpell(target, SPELL_DK_HOWLING_BLAST_AOE, true);

        // Obliteration
        if (caster->HasAura(SPELL_DK_OBLITERATION_PROC))
        {
            caster->CastSpell(caster, SPELL_DK_KILLING_MACHINE, true);
            if (roll_chance_i(sSpellMgr->GetSpellInfo(SPELL_DK_OBLITERATION)->GetEffect(EFFECT_1).BasePoints))
                caster->CastSpell(caster, SPELL_DK_OBLITERATION_ENERGIZE, true);
        }
    }

	void HandleAfterCast()
	{
		if (Unit* caster = GetCaster())
        if (caster->HasAura(SPELL_DK_RIME_BUFF))
            caster->RemoveAura(SPELL_DK_RIME_BUFF);
    }

    void Register() override
    {
        BeforeCast += SpellCastFn(spell_dk_howling_blast::HandleBeforeCast);
        OnHit += SpellHitFn(spell_dk_howling_blast::HandleOnHit);
		AfterCast += SpellCastFn(spell_dk_howling_blast::HandleAfterCast);
    }
};

// Howling Blast AOE - 237680
class spell_dk_howling_blast_aoe : public SpellScript
{
    PrepareSpellScript(spell_dk_howling_blast_aoe);

    ObjectGuid tar;

    void HandleBeforeCast()
    {
        tar = GetOrigUnitTargetGUID();
    }

    void HandleOnHit(SpellEffIndex /*effIndex*/)
    {
		Unit* caster = GetCaster();
		Unit* target = GetHitUnit();
		if (!caster || !target)
			return;

		if (target->GetGUID() == tar)
			PreventHitDamage();
        else
        {
			caster->CastSpell(target, SPELL_DK_FROST_FEVER, true);
            DeathKnight::ApplySuperstrain(caster, target, SPELL_DK_FROST_FEVER);
        }

    }

    void Register() override
    {
        BeforeCast += SpellCastFn(spell_dk_howling_blast_aoe::HandleBeforeCast);
        OnEffectHitTarget += SpellEffectFn(spell_dk_howling_blast_aoe::HandleOnHit, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

// 196770 - Remorseless Winter
class spell_dk_remorseless_winter : public SpellScript
{
	PrepareSpellScript(spell_dk_remorseless_winter);

	void HandleAfterCast()
	{
		if (Unit* caster = GetCaster())
			if (caster->HasAura(SPELL_DK_FROZEN_CENTER))
				caster->CastSpell(caster->GetPosition(), SPELL_DK_FROZEN_CENTER_ROOT, true);
	}

	void Register() override
	{
		AfterCast += SpellCastFn(spell_dk_remorseless_winter::HandleAfterCast);
	}
};

// 196771 - Remorseless Winter
class spell_dk_remorseless_winter_damage : public SpellScript
{
    PrepareSpellScript(spell_dk_remorseless_winter_damage);

    void HandleOnHit(SpellEffIndex /*effIndex*/)
    {
        if (Unit* unit = GetHitUnit())
            GetCaster()->CastSpell(unit, SPELL_DK_REMORSELESS_WINTER_SLOW_DOWN, true);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_dk_remorseless_winter_damage::HandleOnHit, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

// 51271 - Pillar of Frost
class spell_dk_pillar_of_frost : public SpellScript
{
    PrepareSpellScript(spell_dk_pillar_of_frost);

    void HandleHit()
    {
        if (Unit* caster = GetCaster())
            if (caster->HasAura(SPELL_DK_OBLITERATION))
                caster->CastSpell(caster, SPELL_DK_OBLITERATION_PROC, true);
    }

    void Register() override
    {
        OnHit += SpellHitFn(spell_dk_pillar_of_frost::HandleHit);
    }
};

class aura_dk_pillar_of_frost : public AuraScript
{
	PrepareAuraScript(aura_dk_pillar_of_frost);

	bool CheckProc(ProcEventInfo& eventInfo)
	{
		if (Spell const* procSpell = eventInfo.GetProcSpell())
			if (SpellPowerCost const* powerCost = procSpell->GetPowerCost(POWER_RUNES))
				if (powerCost->Amount > 0)
				{
					powerSpent = powerCost->Amount;
					return true;
				}

		return false;
	}

	void CalcAmount(AuraEffect const* /*aurEff*/, int32& amount, bool& canBeRecalculated)
	{
		canBeRecalculated = true;
		amount = currentAmount;
	}

	void HandleProc(ProcEventInfo& eventInfo)
	{
		currentAmount += powerSpent;
		GetAura()->RecalculateAmountOfEffects();
	}

    void HandleRemove(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /* mode */)
    {
        if (Unit* caster = GetCaster())
            caster->RemoveAura(SPELL_DK_OBLITERATION_PROC);
    }

	void Register() override
	{
		DoCheckProc += AuraCheckProcFn(aura_dk_pillar_of_frost::CheckProc);
		OnProc += AuraProcFn(aura_dk_pillar_of_frost::HandleProc);
		DoEffectCalcAmount += AuraEffectCalcAmountFn(aura_dk_pillar_of_frost::CalcAmount, EFFECT_0, SPELL_AURA_MOD_TOTAL_STAT_PERCENTAGE);
        OnEffectRemove += AuraEffectRemoveFn(aura_dk_pillar_of_frost::HandleRemove, EFFECT_0, SPELL_AURA_MOD_TOTAL_STAT_PERCENTAGE, AURA_EFFECT_HANDLE_REAL);
	}

private:
	uint8 powerSpent = 0;
	int32 currentAmount = 15;
};


// Called by Death Coil - 47541, Rune Strike - 56815 and Frost Strike - 49143
// Blood Charges - 114851 for Blood Tap - 45529
class spell_dk_blood_charges : public SpellScriptLoader
{
public:
    spell_dk_blood_charges() : SpellScriptLoader("spell_dk_blood_charges") { }

    class spell_dk_blood_charges_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_dk_blood_charges_SpellScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            return sSpellMgr->GetSpellInfo(SPELL_DK_BOOD_TAP) && sSpellMgr->GetSpellInfo(SPELL_DK_BLOOD_CHARGE);
        }

        void HandleOnHit()
        {
            if (Player* _player = GetCaster()->ToPlayer())
            {
                if (GetHitUnit())
                {
                    if (_player->HasSpell(SPELL_DK_BOOD_TAP))
                    {
                        _player->CastSpell(_player, SPELL_DK_BLOOD_CHARGE, true);
                        _player->CastSpell(_player, SPELL_DK_BLOOD_CHARGE, true);
                    }
                }
            }
        }

        void Register() override
        {
            OnHit += SpellHitFn(spell_dk_blood_charges_SpellScript::HandleOnHit);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_dk_blood_charges_SpellScript();
    }
};

// Death Siphon - 108196
class spell_dk_death_siphon : public SpellScriptLoader
{
public:
    spell_dk_death_siphon() : SpellScriptLoader("spell_dk_death_siphon") { }

    class spell_dk_death_siphon_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_dk_death_siphon_SpellScript);

        void HandleScriptEffect(SpellEffIndex /*effIndex*/)
        {
            if (Player* _player = GetCaster()->ToPlayer())
            {
                if (GetHitUnit())
                {
                    int32 bp = GetHitDamage();
                    _player->CastCustomSpell(_player, SPELL_DK_DEATH_SIPHON_HEAL, &bp, NULL, NULL, true);
                }
            }
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_dk_death_siphon_SpellScript::HandleScriptEffect, EFFECT_1, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_dk_death_siphon_SpellScript();
    }
};

// Purgatory - 116888
class spell_dk_purgatory : public SpellScriptLoader
{
public:
    spell_dk_purgatory() : SpellScriptLoader("spell_dk_purgatory") { }

    class spell_dk_purgatory_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_dk_purgatory_AuraScript);

        void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if (Player* _player = GetTarget()->ToPlayer())
            {
                AuraRemoveMode removeMode = GetTargetApplication()->GetRemoveMode();
                if (removeMode == AURA_REMOVE_BY_EXPIRE)
                    _player->CastSpell(_player, SPELL_DK_PURGATORY_INSTAKILL, true);
            }
        }

        void Register() override
        {
            OnEffectRemove += AuraEffectRemoveFn(spell_dk_purgatory_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_SCHOOL_HEAL_ABSORB, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_dk_purgatory_AuraScript();
    }
};


// Purgatory - 114556
class spell_dk_purgatory_absorb : public SpellScriptLoader
{
public:
    spell_dk_purgatory_absorb() : SpellScriptLoader("spell_dk_purgatory_absorb") { }

    class spell_dk_purgatory_absorb_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_dk_purgatory_absorb_AuraScript);

        void CalculateAmount(AuraEffect const* /*auraEffect*/, int32& amount, bool& /*canBeRecalculated*/)
        {
            amount = -1;
        }

        void Absorb(AuraEffect* /*auraEffect*/, DamageInfo& dmgInfo, uint32& absorbAmount)
        {
            Unit* target = GetTarget();

            if (dmgInfo.GetDamage() < target->GetHealth())
                return;

            // No damage received under Shroud of Purgatory
            if (target->ToPlayer()->HasAura(SPELL_DK_SHROUD_OF_PURGATORY))
            {
                absorbAmount = dmgInfo.GetDamage();
                return;
            }

            if (target->ToPlayer()->HasAura(SPELL_DK_PERDITION))
                return;

            int32 bp = dmgInfo.GetDamage();

            target->CastCustomSpell(target, SPELL_DK_SHROUD_OF_PURGATORY, &bp, NULL, NULL, true);
            target->CastSpell(target, SPELL_DK_PERDITION, true);
            target->SetHealth(1);
            absorbAmount = dmgInfo.GetDamage();
        }

        void Register() override
        {
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_dk_purgatory_absorb_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
            OnEffectAbsorb += AuraEffectAbsorbFn(spell_dk_purgatory_absorb_AuraScript::Absorb, EFFECT_0);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_dk_purgatory_absorb_AuraScript();
    }
};

// Outbreak - 77575 Last Update 8.0.1 Build 28153
class spell_dk_outbreak : public SpellScript
{
    PrepareSpellScript(spell_dk_outbreak);

    void HandleOnHit(SpellEffIndex /*effIndex*/)
    {
		Unit* caster = GetCaster();
		Unit* target = GetHitUnit();
		if (!caster || !target)
			return;

        if (!target->HasAura(SPELL_DK_OUTBREAK_PERIODIC, GetCaster()->GetGUID()))
            caster->CastSpell(target, SPELL_DK_OUTBREAK_PERIODIC, true);

		// Wandering Plague
		if (caster->HasAura(SPELL_DK_WANDERING_PLAGUE))
		{
			caster->CastSpell(target, SPELL_DK_WANDERING_PLAGUE_DISEASE, true);
			caster->Variables.Set<uint8>("WP_JUMPS", 0);
		}
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_dk_outbreak::HandleOnHit, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

// Outbreak - 196782 Last Update 8.0.1 Build 28153
class aura_dk_outbreak_periodic : public AuraScript
{
    PrepareAuraScript(aura_dk_outbreak_periodic);

	void HandleApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
	{
		Unit* caster = GetCaster();
		Unit* owner = GetUnitOwner();
		if (!caster || !owner)
			return;

		caster->CastSpell(owner, SPELL_DK_VIRULENT_PLAGUE, true);
        DeathKnight::ApplySuperstrain(caster, owner, SPELL_DK_VIRULENT_PLAGUE);
	}

    void HandleDummyTick(AuraEffect const* /*aurEff*/)
    {
        if (Unit* caster = GetCaster())
        {
            if (Unit* target = GetTarget())
            {
                std::list<Unit*> friendlyUnits;
                target->GetFriendlyUnitListInRange(friendlyUnits, 10.f, true);

                friendlyUnits.push_back(target);

                for (Unit* unit : friendlyUnits)
                    if (caster->IsValidAttackTarget(unit))
                    {
                        caster->CastSpell(unit, SPELL_DK_VIRULENT_PLAGUE, true);
                        DeathKnight::ApplySuperstrain(caster, unit, SPELL_DK_VIRULENT_PLAGUE);
                    }
            }
        }
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(aura_dk_outbreak_periodic::HandleDummyTick, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
		OnEffectApply += AuraEffectApplyFn(aura_dk_outbreak_periodic::HandleApply, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
    }
};

// 48707 - Anti-Magic Shell (on self)
class spell_dk_anti_magic_shell_self : public AuraScript
{
    PrepareAuraScript(spell_dk_anti_magic_shell_self);

    void CalculateAmount(AuraEffect const* /*aurEff*/, int32& amount, bool & /*canBeRecalculated*/)
    {
        // $amb = $?s205727 [${1.3}] [${1.0}]
        // $shield = ${ $MHP * $m2 / 100 * (1 + $@versadmg) * $<amb> }
        if (Unit* caster = GetCaster())
        {
            float factor = (caster->HasAura(SPELL_DK_ANTIMAGIC_BARRIER) ? 1.3f : 1.0f);
            amount = CalculatePct(caster->GetMaxHealth(), (caster->HasAura(SPELL_DK_VOLATILE_SHIELD)) ? 65 : 30) * factor;
        }
    }

    void Absorb(AuraEffect* /*aurEff*/, DamageInfo& dmgInfo, uint32& absorbAmount)
    {
        if (dmgInfo.GetSchoolMask() == SpellSchoolMask::SPELL_SCHOOL_MASK_NORMAL)
            absorbAmount = 0;
    }

    void Trigger(AuraEffect* aurEff, DamageInfo& /*dmgInfo*/, uint32& absorbAmount)
    {
        if (Unit* caster = GetCaster())
        {
            float damagePerRp = caster->CountPctFromMaxHealth(1) / 2.0f;
            int32 energizeAmount = (absorbAmount / damagePerRp) * 10.0f;
            caster->CastCustomSpell(caster, SPELL_DK_RUNIC_POWER_ENERGIZE, &energizeAmount, NULL, NULL, true, NULL, aurEff);

            if (caster->HasAura(DeathKnight::eLegendary::DeathsEmbrace))
                caster->CastSpell(caster, DeathKnight::eLegendary::DeathsEmbraceHeal, CastSpellExtraArgs(true).AddSpellBP0(absorbAmount));
        }
    }

    void Register() override
    {
        OnEffectAbsorb += AuraEffectAbsorbFn(spell_dk_anti_magic_shell_self::Absorb, EFFECT_0);
        AfterEffectAbsorb += AuraEffectAbsorbFn(spell_dk_anti_magic_shell_self::Trigger, EFFECT_0);
        DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_dk_anti_magic_shell_self::CalculateAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
    }
};

// Plague Leech
class spell_dk_plague_leech : public SpellScriptLoader
{
public:
    spell_dk_plague_leech() : SpellScriptLoader("spell_dk_plague_leech") {}

    class spell_dk_plague_leech_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_dk_plague_leech_SpellScript);

        SpellCastResult CheckClass()
        {
            if (Unit* target = GetExplTargetUnit())
            {
                uint8 diseases = target->GetDiseasesByCaster(GetCaster()->GetGUID());
                uint8 requiredDiseases = GetCaster()->HasAura(152281) ? 1 : 2;
                if (diseases < requiredDiseases)
                {
                    //SetCustomCastResultMessage(159);
                    return SPELL_FAILED_CUSTOM_ERROR;
                }
            }

            return SPELL_CAST_OK;
        }

        void HandleOnHit()
        {
            Player* player = GetCaster()->ToPlayer();
            if (!player)
                return;

            std::vector<uint8> runes;
            for (uint8 i = 0; i < MAX_RUNES; ++i)
                if (player->GetRuneCooldown(i) == player->GetRuneBaseCooldown())
                    runes.push_back(i);

            if (!runes.empty())
            {
                for (uint8 i = 0; i < 2 && !runes.empty(); i++)
                {
                    std::vector<uint8>::iterator itr = runes.begin();
                    std::advance(itr, urand(0, runes.size() - 1));
                    uint32 runesState = player->GetRunesState();
                    player->SetRuneCooldown((*itr), 0);
                    if ((player->GetRunesState() & ~runesState) != 0)
                        player->AddRunePower((player->GetRunesState() & ~runesState));

                    runes.erase(itr);
                }

                GetHitUnit()->GetDiseasesByCaster(GetCaster()->GetGUID(), true);
            }
        }

        void Register() override
        {
            OnCheckCast += SpellCheckCastFn(spell_dk_plague_leech_SpellScript::CheckClass);
            OnHit += SpellHitFn(spell_dk_plague_leech_SpellScript::HandleOnHit);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_dk_plague_leech_SpellScript();
    }
};

// 50453 - Bloodworms Health Leech
class spell_dk_blood_gorged : public SpellScriptLoader
{
public:
    spell_dk_blood_gorged() : SpellScriptLoader("spell_dk_blood_gorged") { }

    class spell_dk_blood_gorged_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_dk_blood_gorged_AuraScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_DK_BLOOD_GORGED_HEAL))
                return false;
            return true;
        }

        bool Load() override
        {
            _procTarget = NULL;
            return true;
        }

        bool CheckProc(ProcEventInfo& /*eventInfo*/)
        {
            _procTarget = GetTarget()->GetOwner();
            return _procTarget != nullptr;
        }

        void HandleProc(AuraEffect* aurEff, ProcEventInfo& eventInfo)
        {
            int32 heal = int32(CalculatePct(eventInfo.GetDamageInfo()->GetDamage(), 150));
            GetTarget()->CastCustomSpell(SPELL_DK_BLOOD_GORGED_HEAL, SPELLVALUE_BASE_POINT0, heal, _procTarget, true, NULL, aurEff);
        }

        void Register() override
        {
            DoCheckProc += AuraCheckProcFn(spell_dk_blood_gorged_AuraScript::CheckProc);
            OnEffectProc += AuraEffectProcFn(spell_dk_blood_gorged_AuraScript::HandleProc, EFFECT_0, SPELL_AURA_PROC_TRIGGER_SPELL);
        }

    private:
        Unit* _procTarget;
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_dk_blood_gorged_AuraScript();
    }
};

// Anti-Magic Barrier - 205725
class spell_dk_anti_magic_barrier : public SpellScriptLoader
{
public:
    spell_dk_anti_magic_barrier() : SpellScriptLoader("spell_dk_anti_magic_barrier") { }

    class spell_dk_anti_magic_barrier_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_dk_anti_magic_barrier_AuraScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_DK_ANTI_MAGIC_BARRIER))
                return false;
            return true;
        }

        void CalcAmount(AuraEffect const* aurEff, int32& amount, bool& /*canBeRecalculated*/)
        {
            if (Unit* caster = GetCaster())
                amount = int32((caster->GetMaxHealth()*25.0f) / 100.0f);

          //  aurEff->GetCaster()->DealDamage(aurEff->GetCaster(), 6969); //debug
        }

        void Register() override
        {
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_dk_anti_magic_barrier_AuraScript::CalcAmount, EFFECT_0, SPELL_AURA_MOD_INCREASE_HEALTH_2);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_dk_anti_magic_barrier_AuraScript();
    }
};

// Breath of Sindragosa - 152279
class spell_dk_breath_of_sindragosa : public SpellScriptLoader
{
public:
    spell_dk_breath_of_sindragosa() : SpellScriptLoader("spell_dk_breath_of_sindragosa") { }

    class spell_dk_breath_of_sindragosa_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_dk_breath_of_sindragosa_AuraScript);

        void OnTick(AuraEffect const* /*p_AurEff*/)
        {
            Unit* caster = GetCaster();
            if (caster == nullptr)
                return;

            Player* l_Player = caster->ToPlayer();
            if (l_Player == nullptr)
                return;

            caster->ModifyPower(POWER_RUNIC_POWER, -130);
            if (caster->ToPlayer())
                caster->ToPlayer()->SendPowerUpdate(POWER_RUNIC_POWER, caster->GetPower(POWER_RUNIC_POWER));

            if (caster->GetPower(POWER_RUNIC_POWER) <= 130)
                caster->RemoveAura(SPELL_DK_BREATH_OF_SINDRAGOSA);

        }

        void Register() override
        {
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_dk_breath_of_sindragosa_AuraScript::OnTick, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_dk_breath_of_sindragosa_AuraScript();
    }
};

// Runic Empowerment - 81229
class dk_playerscript : public PlayerScript
{
public:
    dk_playerscript() : PlayerScript("dk_playerscript") {}

    void OnModifyPower(Player * player, Powers power, int32 oldValue, int32& newValue, bool regen, bool after) override
    {
		if (after || regen)
            return;

        if (player->GetClass() != CLASS_DEATH_KNIGHT)
            return;

		// Blood DK
		if (player->GetSpecializationId() == TALENT_SPEC_DEATHKNIGHT_BLOOD)
		{
            if (newValue < oldValue && power == POWER_RUNES)
            {
                if (player->HasSpell(SPELL_DK_RUNE_STRIKE))
                {
                    uint8 runes = oldValue - newValue;
                    player->GetSpellHistory()->ReduceChargeCooldown(sSpellMgr->GetSpellInfo(SPELL_DK_RUNE_STRIKE)->ChargeCategoryId, runes * IN_MILLISECONDS);
                }

                if (Aura* aura = player->GetAura(SPELL_DK_ETERNAL_RUNE_WEAPON_BUFF))
                {
                    if (SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(SPELL_DK_ETERNAL_RUNE_WEAPON_AURA))
                    {
                        bool addDuration = false;
                        int32 duration = 0;

                        if (player->Variables.Exist("ETERNAL_RUNE_DURATION"))
                        {
                            duration = player->Variables.GetValue<int32>("ETERNAL_RUNE_DURATION");
                            if ((spellInfo->GetEffect(EFFECT_2).BasePoints * IN_MILLISECONDS) > duration)
                                addDuration = true;
                        }
                        else
                            addDuration = true;

                        if (addDuration)
                        {
                            addDuration = false;
                            int32 plus = float(spellInfo->GetEffect(EFFECT_1).BasePoints / 10) * IN_MILLISECONDS;
                            player->Variables.Set<int32>("ETERNAL_RUNE_DURATION", duration + plus);
                            //w tf
                          //  player->Yell(std::to_string(duration));
                            aura->SetDuration(aura->GetDuration() + plus);
                            aura->SetMaxDuration(aura->GetMaxDuration() + plus);
                        }
                    }
                }
            }
		}

        // Unholy DK
        if (player->GetSpecializationId() == TALENT_SPEC_DEATHKNIGHT_UNHOLY)
        {
            if (power == POWER_RUNES && newValue < oldValue)
            {
                // Gargoyle Empowerment
                if (Creature* gargoyle = player->GetSummonedCreatureByEntry(27829))
                {
                    if (player->Variables.Exist("RUNE_REST"))
                    {
                        uint8 rest = player->Variables.GetValue<uint8>("RUNE_REST");
                        if (oldValue - newValue + rest >= 2)
                        {
                            uint8 stack = 0;
                            uint8 newRest = (oldValue - newValue + rest) % 2;
                            uint8 value = std::floor((oldValue - newValue + rest) / 2);
                            if (Aura* aura = gargoyle->GetAura(211947))
                                stack = aura->GetEffect(0)->GetAmount();

                            gargoyle->RemoveAura(211947);
                            gargoyle->CastCustomSpell(211947, SPELLVALUE_BASE_POINT0, value + stack, gargoyle, true);
                            player->Variables.Set<uint8>("RUNE_REST", newRest);
                        }
                        else
                        {
                            uint8 rest = player->Variables.GetValue<uint8>("RUNE_REST");
                            uint8 newRest = rest + oldValue - newValue;
                            player->Variables.Set<uint8>("RUNE_REST", newRest);
                        }
                    }
                }
            }

            if (player->HasAura(SPELL_DK_RUNIC_CORRUPTION) && newValue < oldValue && power == POWER_RUNIC_POWER)
            {
                float prob = sSpellMgr->GetSpellInfo(SPELL_DK_RUNIC_CORRUPTION)->GetEffect(EFFECT_0).BasePoints / 100 * ((oldValue - newValue) / 10);
                if (roll_chance_f(prob))
                {
                    player->CastSpell(player, SPELL_DK_RUNIC_CORRUPTION_REGEN, true);
                    return;
                }
            }
        }

        // Frost DK
        if (player->GetSpecializationId() == TALENT_SPEC_DEATHKNIGHT_FROST)
        {
            if (player->HasAura(SPELL_DK_RUNIC_EMPOWERMENT) && newValue < oldValue && power == POWER_RUNIC_POWER)
            {
                float prob = 2.0f * ((oldValue - newValue) / 10);
                if (roll_chance_f(prob))
                    player->CastSpell(player, SPELL_DK_RUNIC_EMPOWERMENT_ENERGIZE, true);
            }
        }
    }

	void OnMapChanged(Player* player) override
	{
		if (!player)
			return;

		if (player->GetSpecializationId() == TALENT_SPEC_DEATHKNIGHT_BLOOD || player->GetSpecializationId() == TALENT_SPEC_DEATHKNIGHT_UNHOLY || player->GetSpecializationId() == TALENT_SPEC_DEATHKNIGHT_FROST)
		{
			if (player->HasAura(SPELL_DK_NECROTIC_AURA_TALENT))
                if (!player->GetAreaTrigger(SPELL_DK_NECROTIC_AURA_TALENT))
				player->AddAura(SPELL_DK_NECROTIC_AURA_TALENT);
			if (player->HasAura(SPELL_DK_HEARTSTOP_AURA_TALENT))
				if (!player->GetAreaTrigger(SPELL_DK_HEARTSTOP_AURA_TALENT))
    				player->AddAura(SPELL_DK_HEARTSTOP_AURA_TALENT);
		}
	}

    void OnSuccessfulSpellCast(Player* player, Spell* spell) override
    {
        if (!player || !spell)
            return;

        if (player->GetClass() != CLASS_DEATH_KNIGHT)
            return;

        if(player->HasAura(SPELL_DK_DARK_SIMULACRUM_PROC))
            if (spell->IsDarkSimulacrum())
                player->RemoveAurasDueToSpell(SPELL_DK_DARK_SIMULACRUM_REPLACER);
    }

    void OnSpellLearned(Player* player, uint32 spellID) override
    {
        if (!player || !spellID)
            return;

        if (spellID == SPELL_DK_DEATHS_ADVANCE)
            player->CastSpell(player, SPELL_DK_DEATHS_ADVANCE_SPEED, true);
    }

    void OnLogin(Player* player, bool firstLogin) override
    {
        if (!player || firstLogin)
            return;

        if (player->HasSpell(SPELL_DK_DEATHS_ADVANCE) && !player->HasAura(SPELL_DK_DEATHS_ADVANCE_SPEED))
            player->CastSpell(player, SPELL_DK_DEATHS_ADVANCE_SPEED, true);
    }
};

// Gorefiend's Grasp - 108199
class spell_dk_gorefiends_grasp : public SpellScriptLoader
{
public:
    spell_dk_gorefiends_grasp() : SpellScriptLoader("spell_dk_gorefiends_grasp") { }

    class spell_dk_gorefiends_grasp_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_dk_gorefiends_grasp_SpellScript);

        void HandleScript(SpellEffIndex /*effIndex*/)
        {
            if (Player* _player = GetCaster()->ToPlayer())
            {
                if (Unit* target = GetHitUnit())
                {
                    std::list<Unit*> tempList;
                    std::list<Unit*> gripList;

                    _player->GetAttackableUnitListInRange(tempList, 20.0f);

                    for (auto itr : tempList)
                    {
                        if (itr->GetGUID() == _player->GetGUID())
                            continue;

                        if (!_player->IsValidAttackTarget(itr))
                            continue;

                        if (itr->IsImmunedToSpell(GetSpellInfo(), GetCaster()))
                            continue;

                        if (!itr->IsWithinLOSInMap(_player))
                            continue;

                        gripList.push_back(itr);
                    }

                    for (auto itr : gripList)
                    {
                        itr->CastSpell(target, SPELL_DK_DEATH_GRIP_ONLY_JUMP, true);
                        itr->CastSpell(target, SPELL_DK_GOREFIENDS_GRASP_GRIP_VISUAL, true);
                    }
                }
            }
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_dk_gorefiends_grasp_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_dk_gorefiends_grasp_SpellScript();
    }
};

//55233 Vampiric Blood
class spell_dk_vampiric_blood : public SpellScriptLoader
{
public:
    spell_dk_vampiric_blood() : SpellScriptLoader("spell_dk_vampiric_blood") { }

    class spell_dk_vampiric_blood_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_dk_vampiric_blood_AuraScript);

        void CalcAmount(AuraEffect const* /*aurEff*/, int32& amount, bool& /*canBeRecalculated*/)
        {
            Unit* caster = GetCaster();
            if (!caster)
                return;
            
            amount = caster->CountPctFromMaxHealth(sSpellMgr->GetSpellInfo(SPELL_DK_VAMPIRIC_BLOOD)->GetEffect(EFFECT_3).BasePoints);
        }

        void Register() override
        {
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_dk_vampiric_blood_AuraScript::CalcAmount, EFFECT_1, SPELL_AURA_MOD_INCREASE_HEALTH);           
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_dk_vampiric_blood_AuraScript();
    }
};

// 195181 - Bone Shield (Triggered by artifact)
//Last Update 8.0.1 Build 28153
class spell_dk_bone_shield : public AuraScript
{
    PrepareAuraScript(spell_dk_bone_shield);

	void HandleAfterApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        SetCharges(GetStackAmount());

		if (Unit* caster = GetCaster())            
            if (caster->HasAura(SPELL_DK_OSSUARY))
            {
                if (GetAura()->GetStackAmount() >= 5)
                    caster->CastSpell(caster, SPELL_DK_OSSUARY_BUFF, true);
            }
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();        
        Unit* caster = GetCaster();
        if (eventInfo.GetDamageInfo() && caster)
        {
            ModStackAmount(-1);
            if (GetAura()->GetStackAmount() < 5)
                caster->RemoveAura(SPELL_DK_OSSUARY_BUFF);
        }
    }

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* caster = GetCaster())
            caster->RemoveAura(SPELL_DK_OSSUARY_BUFF);
    }

    void Register() override
    {
        AfterEffectApply += AuraEffectApplyFn(spell_dk_bone_shield::HandleAfterApply, EFFECT_0, SPELL_AURA_MOD_ARMOR_PCT_FROM_STAT, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
		AfterEffectRemove += AuraEffectRemoveFn(spell_dk_bone_shield::HandleRemove, EFFECT_0, SPELL_AURA_MOD_ARMOR_PCT_FROM_STAT, AURA_EFFECT_HANDLE_REAL);
        OnProc += AuraProcFn(spell_dk_bone_shield::HandleProc);
    }
};

// 195182 - Marrowrend
class spell_dk_marrowrend : public SpellScript
{
    PrepareSpellScript(spell_dk_marrowrend);

    void HandleHit()
    {
        if (Unit* caster = GetCaster())
        {
            uint8 charges = (caster->HasAura(SPELL_DK_BONE_SHIELD)) ? sSpellMgr->GetSpellInfo(SPELL_DK_MARROWREND)->GetEffect(EFFECT_2).BasePoints :
                                                                      sSpellMgr->GetSpellInfo(SPELL_DK_MARROWREND)->GetEffect(EFFECT_2).BasePoints + 1;
            caster->CastCustomSpell(SPELL_DK_BONE_SHIELD, SPELLVALUE_AURA_STACK, charges, caster, true);
        }
    }

    void Register() override
    {
        OnHit += SpellHitFn(spell_dk_marrowrend::HandleHit);
    }
};

//206977
class spell_dk_blood_mirror : public SpellScriptLoader
{
public:
    spell_dk_blood_mirror() : SpellScriptLoader("spell_dk_blood_mirror") { }

    class spell_dk_blood_mirror_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_dk_blood_mirror_AuraScript);

        void CalcAmount(AuraEffect const* /*aurEff*/, int32& amount, bool& /*canBeRecalculated*/)
        {
            amount = -1;
        }

        void HandleApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            Unit* target = GetTarget();
            Unit* caster = GetCaster();
            if (!target || !caster)
                return;
            if(caster->HasAura(SPELL_DK_BLOOD_MIRROR))
                caster->GetAura(SPELL_DK_BLOOD_MIRROR)->Variables.Set("targetGUID", target->GetGUID());
        }

        void HandleAbsorb(AuraEffect* aurEff, DamageInfo& dmgInfo, uint32& absorbAmount)
        {
            absorbAmount = dmgInfo.GetDamage() * (aurEff->GetBaseAmount() / 100);

            Unit* caster = GetCaster();
            ObjectGuid const procTargetGUID = GetAura()->Variables.GetValue<ObjectGuid>("targetGUID");
            if (!caster || procTargetGUID.IsEmpty())
                return;

            Unit* target = ObjectAccessor::GetUnit(*caster, procTargetGUID);
            if (!target)
                return;

            caster->CastCustomSpell(SPELL_DK_BLOOD_MIRROR_DAMAGE, SPELLVALUE_BASE_POINT0, absorbAmount, target, true);
        }

        void Register() override
        {
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_dk_blood_mirror_AuraScript::CalcAmount, EFFECT_1, SPELL_AURA_SCHOOL_ABSORB);
            AfterEffectApply += AuraEffectApplyFn(spell_dk_blood_mirror_AuraScript::HandleApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            OnEffectAbsorb += AuraEffectAbsorbFn(spell_dk_blood_mirror_AuraScript::HandleAbsorb, EFFECT_1);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_dk_blood_mirror_AuraScript();
    }
};

//194909 - Frozen Pulse
//Updated to 7.1
class spell_dk_frozen_pulse : public SpellScriptLoader
{
public:
    spell_dk_frozen_pulse() : SpellScriptLoader("spell_dk_frozen_pulse") { }

    class spell_dk_frozen_pulse_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_dk_frozen_pulse_AuraScript);

        bool HandleProc(ProcEventInfo& /*procInfo*/)
        {
            Unit* caster = GetCaster();

            if (!caster)
                return false;

            if (caster->GetPower(POWER_RUNES) > GetSpellInfo()->GetEffect(EFFECT_1).BasePoints)
                return false;

            return true;
        }

        void Register() override
        {
            DoCheckProc += AuraCheckProcFn(spell_dk_frozen_pulse_AuraScript::HandleProc);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_dk_frozen_pulse_AuraScript();
    }
};

// 194913 - Glacial Advance
class spell_dk_glacial_advance : public SpellScript
{
    PrepareSpellScript(spell_dk_glacial_advance);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_DK_OBLITERATION });
    }

    void HandleHit(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();

        Position castPosition = *caster;
        Position collisonPos = caster->GetFirstCollisionPosition(GetEffectInfo().MaxRadiusEntry->RadiusMax);
        float maxDistance = caster->GetDistance(collisonPos);

        if (caster->Variables.Exist("GLACIAL_ADVANCE"))
            caster->Variables.Remove("GLACIAL_ADVANCE");

        for (float dist = 1.0f; dist <= maxDistance; dist += 2.5f)
        {
            caster->GetScheduler().Schedule(Milliseconds(uint32(dist / 2.5f * 50.0f)), [castPosition, dist](TaskContext context)
            {
                Unit* caster = context.GetUnit();
                Position targetPosition = castPosition;
                caster->MovePosition(targetPosition, dist, 0.0f);
                caster->CastSpell(targetPosition, SPELL_DK_GLACIAL_ADVANCE_DAMAGE, true);
            });
        }

        // Obliteration
        if (caster->HasAura(SPELL_DK_OBLITERATION_PROC))
        {
            caster->CastSpell(caster, SPELL_DK_KILLING_MACHINE, true);
            if (roll_chance_i(sSpellMgr->GetSpellInfo(SPELL_DK_OBLITERATION)->GetEffect(EFFECT_1).BasePoints))
                caster->CastSpell(caster, SPELL_DK_OBLITERATION_ENERGIZE, true);
        }
    }

    void Register() override
    {
        OnEffectHit += SpellEffectFn(spell_dk_glacial_advance::HandleHit, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

// 222024 - Obliterate Main Hand
class spell_dk_obliterate_main_hand : public SpellScript
{
	PrepareSpellScript(spell_dk_obliterate_main_hand);

	void HandleCritChance(Unit const* /*victim*/, float& chance)
	{
		if (Unit* caster = GetCaster())
			if (caster->HasAura(SPELL_DK_KILLING_MACHINE))
				chance = 100.f;
	}

	void HandleHit()
	{
		if (Unit* caster = GetCaster())
		{
			if (Player* player = caster->ToPlayer())
				if (!player->GetEquippedItem(EQUIPMENT_SLOT_OFFHAND))
					player->RemoveAurasDueToSpell(SPELL_DK_KILLING_MACHINE);

			if (caster->HasAura(SPELL_DK_RIME) && roll_chance_f(sSpellMgr->GetSpellInfo(SPELL_DK_RIME)->GetEffect(EFFECT_1).BasePoints))
				caster->CastSpell(caster, SPELL_DK_RIME_BUFF, true);

			// Icecap
			if (caster->HasAura(SPELL_DK_ICECAP) && IsHitCrit())
			{
				caster->Variables.Set<bool>("IC_HANDLE_CRIT", true);
				caster->GetSpellHistory()->ModifyCooldown(SPELL_DK_PILLAR_OF_FROST, -1s);
			}
		}
	}

	void Register() override
	{
		OnCalcCritChance += SpellOnCalcCritChanceFn(spell_dk_obliterate_main_hand::HandleCritChance);
		OnHit += SpellHitFn(spell_dk_obliterate_main_hand::HandleHit);
	}
};

// 66198 - Obliterate Off Hand
class spell_dk_obliterate_off_hand : public SpellScript
{
	PrepareSpellScript(spell_dk_obliterate_off_hand);

	void HandleCritChance(Unit const* /*victim*/, float& chance)
	{
		if (Unit* caster = GetCaster())
			if (caster->HasAura(SPELL_DK_KILLING_MACHINE))
				chance = 100.f;
	}

	void HandleHit()
	{
		if (Unit* caster = GetCaster())
		{
			// Icecap
			if (caster->HasAura(SPELL_DK_ICECAP) && IsHitCrit()  && !caster->Variables.Exist("IC_HANDLE_CRIT"))
				caster->GetSpellHistory()->ModifyCooldown(SPELL_DK_PILLAR_OF_FROST, -1s);

			caster->Variables.Remove("IC_HANDLE_CRIT");
			caster->RemoveAurasDueToSpell(SPELL_DK_KILLING_MACHINE);
		}
	}

	void Register() override
	{
		OnCalcCritChance += SpellOnCalcCritChanceFn(spell_dk_obliterate_off_hand::HandleCritChance);
		OnHit += SpellHitFn(spell_dk_obliterate_off_hand::HandleHit);
	}
};

// 207317 - Epidemic
class spell_dk_epidemic : public SpellScript
{
    PrepareSpellScript(spell_dk_epidemic);

    void HandleHit(SpellEffIndex /*effIndex*/)
    {
        if (Unit* target = GetHitUnit())
        {
            if (target->HasAura(SPELL_DK_VIRULENT_PLAGUE, GetCaster()->GetGUID()))
            {
                GetCaster()->CastSpell(target, SPELL_DK_EPIDEMIC_DAMAGE_SINGLE, true);
                GetCaster()->CastSpell(target, SPELL_DK_EPIDEMIC_DAMAGE_AOE, true);
            }
        }

        PreventHitDamage();
    }

	void HandleAfterCast()
	{
        if (Unit* caster = GetCaster())
        {
            if (Aura* aura = caster->GetAura(SPELL_DK_SUDDEN_DOOM))
                aura->ModStackAmount(-1);

			if (caster->HasAura(SPELL_DK_ARMY_OF_THE_DAMNED))
			{
				caster->GetSpellHistory()->ModifyCooldown(SPELL_DK_ARMY_OF_DEATH_TRIGGER, -5s);
				caster->GetSpellHistory()->ModifyCooldown(SPELL_DK_APOCALYPSE, -1s);
			}
        }
	}

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_dk_epidemic::HandleHit, EFFECT_0, SPELL_EFFECT_DUMMY);
		AfterCast += SpellCastFn(spell_dk_epidemic::HandleAfterCast);
    }
};

// 215969 - Epidemic AOE
class spell_dk_epidemic_aoe : public SpellScript
{
    PrepareSpellScript(spell_dk_epidemic_aoe);

    void HandleOnHitMain(SpellEffIndex /*effIndex*/)
    {
        if (Unit* target = GetHitUnit())
            explicitTarget = target->GetGUID();
    }

    void HandleOnHitAOE(SpellEffIndex /*effIndex*/)
    {
        if (Unit* target = GetHitUnit())
            if (target->GetGUID() == explicitTarget)
                PreventHitDamage();
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_dk_epidemic_aoe::HandleOnHitMain, EFFECT_0, SPELL_EFFECT_DUMMY);
        OnEffectHitTarget += SpellEffectFn(spell_dk_epidemic_aoe::HandleOnHitAOE, EFFECT_1, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
private:
    ObjectGuid explicitTarget;
};

// 191587 - Virulent Plague Last Update 8.0.1 Build 28153
class aura_dk_virulent_plague : public AuraScript
{
    PrepareAuraScript(aura_dk_virulent_plague);

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
        if (Unit* caster = GetCaster())
        {
            if (Unit* target = GetUnitOwner())
            {
                uint32 eruptionChances = GetEffectInfo(EFFECT_1).BasePoints;
                if (roll_chance_i(eruptionChances))
                    caster->CastSpell(target, SPELL_DK_VIRULENT_ERUPTION, true);
            }
        }
    }

    void HandleEffectRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
		Unit* caster = GetCaster();
		Unit* target = GetUnitOwner();
		if (!caster || !target)
			return;

		AuraRemoveMode removeMode = GetTargetApplication()->GetRemoveMode();
		if (removeMode == AURA_REMOVE_BY_DEATH)
		{
			if (Unit* caster = GetCaster())
				caster->CastSpell(target, SPELL_DK_VIRULENT_ERUPTION, true);
		}
		else if (caster->HasAura(SPELL_DK_UNHOLY_MUTATION) && (removeMode == AURA_REMOVE_BY_EXPIRE || removeMode == AURA_REMOVE_BY_ENEMY_SPELL))
		{
            caster->Variables.Set<bool>("MutationDamage", true);
			caster->CastSpell(target, SPELL_DK_VIRULENT_ERUPTION, true);
			caster->CastSpell(target->GetPosition(), SPELL_DK_UNHOLY_MUTATION_DAMAGE, true);
		}

		target->RemoveAurasDueToSpell(SPELL_DK_OUTBREAK_PERIODIC, caster->GetGUID());
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(aura_dk_virulent_plague::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE);
        AfterEffectRemove += AuraEffectRemoveFn(aura_dk_virulent_plague::HandleEffectRemove, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE, AURA_EFFECT_HANDLE_REAL);
    }
};

// 152280 - Defile
class aura_dk_defile : public AuraScript
{
    PrepareAuraScript(aura_dk_defile);

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
        if (Unit* caster = GetCaster())
        {
            for (AreaTrigger* at : caster->GetAreaTriggers(GetId()))
            {
                caster->CastSpell(at->GetPosition(), SPELL_DK_DEFILE_DAMAGE, true);

                if (at->GetInsideUnits().size())
                    caster->CastSpell(caster, SPELL_DK_DEFILE_MASTERY, true);
            }
        }
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(aura_dk_defile::HandlePeriodic, EFFECT_2, SPELL_AURA_PERIODIC_DUMMY);
    }
};

// 55090 - Scourge Strike
class spell_dk_scourge_strike : public SpellScript
{
    PrepareSpellScript(spell_dk_scourge_strike);

	void CacheMainTarget(WorldObject*& target)
    {
		mainTarget = target;
	}

	void FilterTargets(std::list<WorldObject*>& targets)
	{
        Unit* caster = GetCaster();
		if (!caster)
			return;

		if (!caster->HasAura(SPELL_DK_DEATH_AND_DECAY))
        {
			targets.clear();
			targets.push_back(mainTarget);
		}
	}

    void HandleOnHit(SpellEffIndex effIndex)
    {
        Unit* caster = GetCaster();
		Unit* target = GetHitUnit();
		if (!caster || !target)
			return;

            if (Aura* festeringWoundAura = target->GetAura(SPELL_DK_FESTERING_WOUND, GetCaster()->GetGUID()))
            {
                if (caster->HasAura(SPELL_DK_UNHOLY_FRENZY))
                    caster->CastSpell(caster, SPELL_DK_UNHOLY_FRENZY_BUFF, true);

                if (Aura* pestilentPustulesAura = caster->GetAura(SPELL_DK_PESTILENT_PUSTULES))
                    if (festeringWoundAura->GetStackAmount() >= pestilentPustulesAura->GetEffect(EFFECT_0)->GetSpellEffectInfo().BasePoints)
                        caster->ModifyPower(POWER_RUNES, 1);

                uint8 festeringWoundBurst = 1;
                if (Aura* castiragorAura = caster->GetAura(SPELL_DK_CASTIGATOR))
                    festeringWoundBurst += castiragorAura->GetEffect(EFFECT_1)->GetSpellEffectInfo().BasePoints;

                festeringWoundBurst = std::min(festeringWoundBurst, festeringWoundAura->GetStackAmount());

                for (uint8 i = 0; i < festeringWoundBurst; ++i)
                {
                    caster->CastSpell(target, SPELL_DK_FESTERING_WOUND_DAMAGE, true);
                    if (caster->HasAura(SPELL_DK_BURSTING_SORES))
                        caster->CastSpell(target, SPELL_DK_BURSTING_SORES_EXPLOSION, true);

                    if (AuraEffect* auraEff = caster->GetAuraEffect(SPELL_DK_FESTERMIGHT_AURA, EFFECT_0))
                        caster->CastCustomSpell(SPELL_DK_FESTERMIGHT_EFFECT, SPELLVALUE_BASE_POINT0, auraEff->GetAmount(), caster);

                    festeringWoundAura->ModStackAmount(-1);
                }
            }
        }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_dk_scourge_strike::HandleOnHit, EFFECT_1, SPELL_EFFECT_SCHOOL_DAMAGE);
		OnObjectTargetSelect += SpellObjectTargetSelectFn(spell_dk_scourge_strike::CacheMainTarget, EFFECT_0, TARGET_UNIT_TARGET_ENEMY);
		OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_dk_scourge_strike::FilterTargets, EFFECT_1, TARGET_UNIT_DEST_AREA_ENEMY);
    }

    private:
	    WorldObject * mainTarget;
};

// Spell 152280
// At 6212
struct at_dk_defile : AreaTriggerAI
{
    at_dk_defile(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger) { }

    void OnUnitEnter(Unit* unit) override
    {
        if (Unit* caster = at->GetCaster())
            caster->CastSpell(unit, SPELL_DK_DEFILE_DUMMY, true);
    }

    void OnUnitExit(Unit* unit) override
    {
        unit->RemoveAurasDueToSpell(SPELL_DK_DEFILE_DUMMY);
    }
};

// 195758 - Blighted Rune Weapon
class spell_dk_blighted_rune_weapon : public SpellScript
{
    PrepareSpellScript(spell_dk_blighted_rune_weapon);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_DK_FESTERING_WOUND });
    }

    void HandleHit(SpellEffIndex /*effIndex*/)
    {
        if (Unit* target = GetHitUnit())
            GetCaster()->CastSpell(target, SPELL_DK_FESTERING_WOUND, true);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_dk_blighted_rune_weapon::HandleHit, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

// Spell 199720
// At 199720
struct at_dk_decomposing_aura : AreaTriggerAI
{
    at_dk_decomposing_aura(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger) { }

    void OnUnitExit(Unit* unit) override
    {
        unit->RemoveAurasDueToSpell(SPELL_DK_DECOMPOSING_AURA_DAMAGE, at->GetCasterGuid());
    }
};

//spell heart strike 206930
//Last Update 8.0.1 Build 28153
class spell_dk_heart_strike : public SpellScript
{
    PrepareSpellScript(spell_dk_heart_strike);
    
    void OnHandleEffectHit(SpellEffIndex /*effIndex*/)
    {
        Player* caster = GetCaster()->ToPlayer();
        Unit* target = GetHitUnit();
        Unit* mainTarget = GetExplTargetUnit();
        if (!caster || !target)
            return;

        if (caster->HasAura(SPELL_AURA_DK_HEARTBREAKER))
            if (mainTarget != target)
                caster->CastCustomSpell(SPELL_DK_BLOD_HEARTBREAKER_ENERGIZE, SPELLVALUE_BASE_POINT0, sSpellMgr->GetSpellInfo(SPELL_DK_BLOD_HEARTBREAKER_ENERGIZE)->GetEffect(EFFECT_0).BasePoints, caster);

        if(AuraEffect * aurEff = caster->GetAuraEffect(SPELL_DK_DEEP_CUTS_POWER, EFFECT_0))
            caster->CastCustomSpell(SPELL_DK_DEEP_CUTS_DEBUFF, SPELLVALUE_BASE_POINT0, aurEff->GetAmount(), target);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_dk_heart_strike::OnHandleEffectHit, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

//spell dancing rune weapon  49028 
class spell_dk_blodd_dancing_rune_weapon : public SpellScript
{
    PrepareSpellScript(spell_dk_blodd_dancing_rune_weapon);

    void OnHandleEffectHit(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        if (!caster)
            return;

        caster->CastSpell(caster, SPELL_DK_BLODD_DANCING_RUNE_WEAPON_ENERGIZE, true);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_dk_blodd_dancing_rune_weapon::OnHandleEffectHit, EFFECT_1, SPELL_EFFECT_APPLY_AURA);
    }
};

// 207200 - Permafrost
class aura_dk_permafrost : public AuraScript
{
	PrepareAuraScript(aura_dk_permafrost);

	bool CheckProc(ProcEventInfo& eventInfo)
	{
		if (eventInfo.GetDamageInfo() && (eventInfo.GetDamageInfo()->GetAttackType() == BASE_ATTACK || eventInfo.GetDamageInfo()->GetAttackType() == OFF_ATTACK))
			return true;

		return false;
	}

	void HandleProc(ProcEventInfo& eventInfo)
	{
		PreventDefaultAction();

		Unit* caster = GetCaster();
		if (eventInfo.GetDamageInfo() && caster)
		{
			uint32 shield = CalculatePct(eventInfo.GetDamageInfo()->GetDamage(), sSpellMgr->GetSpellInfo(SPELL_DK_PERMAFROST)->GetEffect(EFFECT_0).BasePoints);
			caster->CastCustomSpell(SPELL_DK_FROST_SHIELD, SPELLVALUE_BASE_POINT0, shield, caster, true);
		}
	}

	void Register() override
	{
		DoCheckProc += AuraCheckProcFn(aura_dk_permafrost::CheckProc);
		OnProc += AuraProcFn(aura_dk_permafrost::HandleProc);
	}
};

// 194912 - Gathering Storm
class aura_gathering_storm : public AuraScript
{
    PrepareAuraScript(aura_gathering_storm);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();
        if (!caster)
            return false;

        if (eventInfo.GetSpellInfo())
        {
            bool spells = (eventInfo.GetSpellInfo()->Id == SPELL_DK_OBLITERATE || eventInfo.GetSpellInfo()->Id == SPELL_DK_CHAINS_OF_ICE || eventInfo.GetSpellInfo()->Id == SPELL_DK_PATH_OF_FROST ||
                           eventInfo.GetSpellInfo()->Id == SPELL_DK_CONTROL_UNDEATH || eventInfo.GetSpellInfo()->Id == SPELL_DK_HOWLING_BLAST);
            if (spells && caster->HasAura(SPELL_DK_REMORSELESS_WINTER))
                return true;
        }
        return false;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (Unit* caster = GetCaster())
        {
            uint8 runes = 1;

            if (eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == SPELL_DK_OBLITERATE)
                runes = 2;

            if (Aura* aura = caster->GetAura(SPELL_DK_REMORSELESS_WINTER))
                aura->ModDuration(runes * IN_MILLISECONDS, true);

            for (uint8 i = 0; i < runes; i++)
                caster->CastSpell(caster, SPELL_DK_GATHERING_STORM_DAMAGE, true);
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_gathering_storm::CheckProc);
        OnProc += AuraProcFn(aura_gathering_storm::HandleProc);
    }
};

// 207230 - Frostscythe
class spell_dk_frostscythe : public SpellScript
{
    PrepareSpellScript(spell_dk_frostscythe);

	void HandleCritChance(Unit const* /*victim*/, float& chance)
	{
		if (Unit* caster = GetCaster())
			if (caster->HasAura(SPELL_DK_KILLING_MACHINE))
				chance = 100.f;
	}

	void HandleHit(SpellEffIndex /*effIndex*/)
	{
		Unit* caster = GetCaster();
		Unit* target = GetHitUnit();
		if (!caster || !target)
			return;

		if (Aura* aura = caster->GetAura(SPELL_DK_INEXORABLE_ASSAULT))
			caster->CastSpell(target, SPELL_DK_INEXORABLE_ASSAULT_DAMAGE, true);

		// Frostscythe crit damage is multiply by 4.
		if (IsHitCrit())
		{
			SetHitDamage(GetHitDamage() * 2);
			crit = true;
		}

		hit = true;

		caster->RemoveAurasDueToSpell(SPELL_DK_KILLING_MACHINE);
	}

    void HandleAfterCast()
    {
        if (Unit* caster = GetCaster())
            {
			if (caster->HasAura(SPELL_DK_GATHERING_STORM) && caster->HasAura(SPELL_DK_REMORSELESS_WINTER))
			{
                caster->CastSpell(caster, SPELL_DK_GATHERING_STORM_DAMAGE, true);
                if (Aura* aura = caster->GetAura(SPELL_DK_REMORSELESS_WINTER))
                    aura->ModDuration(IN_MILLISECONDS, true);
            }

			if (Aura* aura = caster->GetAura(SPELL_DK_INEXORABLE_ASSAULT))
				if (hit)
					aura->ModStackAmount(-1);

			if (caster->HasAura(SPELL_DK_RIME) && roll_chance_f(sSpellMgr->GetSpellInfo(SPELL_DK_RIME)->GetEffect(EFFECT_1).BasePoints * 0.5f) && hit)
				caster->CastSpell(caster, SPELL_DK_RIME_BUFF, true);

			// Icecap
			if (caster->HasAura(SPELL_DK_ICECAP) && hit && crit)
				caster->GetSpellHistory()->ModifyCooldown(SPELL_DK_PILLAR_OF_FROST, -1s);
    }
    }

    void Register() override
    {
		OnCalcCritChance += SpellOnCalcCritChanceFn(spell_dk_frostscythe::HandleCritChance);
		OnEffectHitTarget += SpellEffectFn(spell_dk_frostscythe::HandleHit, EFFECT_1, SPELL_EFFECT_SCHOOL_DAMAGE);
        AfterCast += SpellCastFn(spell_dk_frostscythe::HandleAfterCast);
    }

private:
	bool hit = false;
	bool crit = false;
};

// NPC Bloodworm - 99739
struct npc_dk_bloodworm : public CreatureAI
{
	npc_dk_bloodworm(Creature* creature) : CreatureAI(creature) {}

	void IsSummonedBy(WorldObject* o) override
	{
        if (!o)
            return;
        auto owner = o->ToUnit();
		if (!owner)
			return;

		owner->AddAura(198494, me);
		me->DespawnOrUnsummon(16000ms);
		me->GetScheduler().Schedule(15s, [this, owner](TaskContext context)
		{
			Burst(owner);
		});

		if (owner->GetVictim() && me->IsValidAttackTarget(owner->GetVictim()))
			me->GetAI()->AttackStart(owner->GetVictim());
	}

	void UpdateAI(uint32 /*diff*/) override
	{
		Unit* owner = me->GetOwner();
		if (!owner)
			return;

		if (owner->GetHealthPct() <= 50)
			Burst(owner);

		if (owner->GetVictim() && me->IsValidAttackTarget(owner->GetVictim()))
			me->GetAI()->AttackStart(owner->GetVictim());
		else
			EnterEvadeMode(EVADE_REASON_NO_HOSTILES);

		DoMeleeAttackIfReady();
	}

	void Burst(Unit* owner)
	{
		if (owner && me->IsValidAssistTarget(owner))
		{
			int32 missing = owner->GetMaxHealth() - owner->GetHealth();
			int32 percent = CalculatePct(missing, sSpellMgr->GetSpellInfo(SPELL_DK_BLOODWORMS)->GetEffect(EFFECT_2).BasePoints);
            int32 heal = percent * 100 / owner->GetMaxHealth();
			me->CastCustomSpell(SPELL_DK_BLOODWORM_HEAL, SPELLVALUE_BASE_POINT1, heal, owner, true, NULL, NULL, owner->GetGUID());
			me->DespawnOrUnsummon(1000ms);
		}
	}

	void EnterEvadeMode(EvadeReason /*reason*/) override
	{
		if (me->IsInEvadeMode() || !me->IsAlive())
			return;
		me->CombatStop(true);
	}
};

// 194310 - Festering Wound
class aura_festering_wound : public AuraScript
{
	PrepareAuraScript(aura_festering_wound);

	bool CheckProc(ProcEventInfo& eventInfo)
	{
		Unit* caster = GetCaster();
		Unit* owner = GetUnitOwner();
		if (!caster || !owner)
			return false;

		if (eventInfo.GetHealInfo() && eventInfo.GetHealInfo()->GetHeal() > 0 && caster->HasAura(SPELL_DK_CRYPT_FEVER))
			return true;

		return false;
	}

	void HandleProc(ProcEventInfo& eventInfo)
	{
		Unit* caster = GetCaster();
		Unit* owner = GetUnitOwner();
		if (!caster || !owner)
			return;

		caster->CastSpell(owner, SPELL_DK_CRYPT_FEVER_DAMAGE, true);
	}

	void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
	{
		Unit * caster = GetCaster();
		Unit * target = GetUnitOwner();

		if (!caster || !target)
			return;

		if (GetTargetApplication()->GetRemoveMode() == AURA_REMOVE_BY_DEATH)
		{
    		caster->CastSpell(target, SPELL_DK_FESTERING_WOUND_DAMAGE, true);
			if (caster->HasAura(SPELL_DK_BURSTING_SORES))
				caster->CastSpell(target, SPELL_DK_BURSTING_SORES_EXPLOSION, true);
	}
	}

	void Register() override
	{
		DoCheckProc += AuraCheckProcFn(aura_festering_wound::CheckProc);
		OnProc += AuraProcFn(aura_festering_wound::HandleProc);
		OnEffectRemove += AuraEffectRemoveFn(aura_festering_wound::HandleRemove, EFFECT_0, SPELL_EFFECT_APPLY_AURA, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
	}
};

// 275699 - Apocalypse
class spell_dk_apocalypse : public SpellScript
{
	PrepareSpellScript(spell_dk_apocalypse);

	bool Validate(SpellInfo const* /*spellInfo*/) override
	{
		return ValidateSpellInfo({ SPELL_DK_FESTERING_WOUND, SPELL_DK_ARMY_OF_DEATH });
	}

	void HandleEffectHit(SpellEffIndex /*effIndex*/)
	{
		Unit* caster = GetCaster();
		Unit* target = GetHitUnit();
		if (!caster || !target)
			return;

		if (Aura* aura = target->GetAura(SPELL_DK_FESTERING_WOUND))
		{
			uint8 stacks = (aura->GetStackAmount() > 4) ? sSpellMgr->GetSpellInfo(SPELL_DK_APOCALYPSE)->GetEffect(EFFECT_1).BasePoints : aura->GetStackAmount();
			for (uint8 i = 0; i < stacks; i++)
			{
				caster->CastSpell(target, SPELL_DK_FESTERING_WOUND_DAMAGE, true);
				caster->CastSpell(caster, SPELL_DK_ARMY_OF_DEATH, true);
			}
			aura->ModStackAmount(-stacks);
		}
	}

	void Register() override
	{
		OnEffectHitTarget += SpellEffectFn(spell_dk_apocalypse::HandleEffectHit, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
	}
};

// 24207 - Ghoul NPC
class npc_pet_dk_ghoul : public ScriptedAI
{
public:
	npc_pet_dk_ghoul(Creature* creature) : ScriptedAI(creature) {}

	enum Events
	{
		EVENT_ATTACK = 1,
	};

    EventMap events;

	void IsSummonedBy(WorldObject* owner) override
	{
		if (!owner)
			return;

		events.ScheduleEvent(EVENT_ATTACK, 4500ms);
	}

	void UpdateAI(uint32 diff) override
	{
		Unit* owner = me->GetOwner();
		if (!owner)
			return;

		if (attack && !owner->IsInCombat())
		{
            EnterEvadeMode(EVADE_REASON_NO_HOSTILES);
			return;
		}

		events.Update(diff);

		Unit* target = GetTarget();
		while (uint32 eventId = events.ExecuteEvent())
		{
			switch (eventId)
			{
				case EVENT_ATTACK:
					attack = true;
					break;
			}
		}

		if (!attack)
			return;

		ObjectGuid newtargetGUID = owner->GetTarget();
		if (newtargetGUID.IsEmpty() || newtargetGUID == targetGUID)
		{
			me->GetAI()->AttackStart(target);
			DoMeleeAttackIfReady();
			return;
		}

		if (Unit* newTarget = ObjectAccessor::GetUnit(*me, newtargetGUID))
			if (target != newTarget && me->IsValidAttackTarget(newTarget))
				target = newTarget;

		me->GetAI()->AttackStart(target);
		DoMeleeAttackIfReady();
	}

	void EnterEvadeMode(EvadeReason /*reason*/) override
	{
		if (!attack)
			return;

		if (me->IsInEvadeMode() || !me->IsAlive())
			return;

		Unit* owner = me->GetOwner();

		me->CombatStop(true);
		if (owner && !me->HasUnitState(UNIT_STATE_FOLLOW))
		{
			me->GetMotionMaster()->Clear();
            me->FollowTarget(owner);
		}
	}

    void JustUnsummoned() override
    {
        if (Unit* owner = me->GetOwner())
            if (Aura* aura = owner->GetAura(SPELL_DK_LAST_SURPRISE_POWER))
                me->CastCustomSpell(SPELL_DK_LAST_SURPRISE_DAMAGE, SPELLVALUE_BASE_POINT0, aura->GetEffect(0)->GetAmount(), me, true);
    }

private:
	Unit * GetTarget() const
	{
		return ObjectAccessor::GetUnit(*me, targetGUID);
	}

	ObjectGuid targetGUID;
	bool attack = false;
};

// 106041 - Zombie NPC
//Last Update 8.0.1 Build 28153
class npc_pet_dk_zombie : public ScriptedAI
{
public:
	npc_pet_dk_zombie(Creature* creature) : ScriptedAI(creature) {}

	void IsSummonedBy(WorldObject* owner) override
	{
		if (!owner)
			return;

        SpellInfo const* reanimation = sSpellMgr->GetSpellInfo(SPELL_DK_REANIMATION);
        if (!reanimation)
            return;

		targetGUID = owner->Variables.GetValue<ObjectGuid>("ZOMBIE_TARGET", ObjectGuid::Empty);
		me->SetMaxHealth(reanimation->GetEffect(EFFECT_2).BasePoints);
		me->SetReactState(REACT_PASSIVE);
        me->SetControlled(true, UNIT_STATE_ROOT);   
        
        Unit* target = GetTarget();
        if (target && owner->IsValidAttackTarget(target))
        {
            me->GetScheduler().Schedule(1s, [this](TaskContext context)
            {
                if (Creature* creature = GetContextCreature())
                {
                    if (auto t = GetTarget())
                    {
                        me->SetControlled(false, UNIT_STATE_ROOT);                        
                        creature->EngageWithTarget(t);
                        creature->SetWalk(true);
                        for (uint8 move = MOVE_WALK; move < MAX_MOVE_TYPE; move++)
                            me->SetSpeedRate((UnitMoveType)move, 0.5f);
                        creature->GetMotionMaster()->Clear();
                        chase = true;
                    }
                }
            });
        }
	}

	void UpdateAI(uint32 diff) override
	{
		Unit* owner = me->GetOwner();
		if (!owner || !chase)
			return;

		Unit* target = GetTarget();
		if (!target || (target && !me->IsValidAttackTarget(target)))
		{
			chase = false;
			me->DespawnOrUnsummon(1s);
			return;
		}
		else
		{
            me->EngageWithTarget(target);
            me->GetMotionMaster()->MoveChase(target);
			// Explode when reach target.
			if (me->GetDistance(target) <= 2.0f)
			{
				me->CastSpell(target, SPELL_DK_REANIMATION_DAMAGE, true);
				me->KillSelf(false);
				me->DespawnOrUnsummon(2s);
			}
		}
	}

private:
	Unit * GetTarget() const
	{
		return ObjectAccessor::GetUnit(*me, targetGUID);
	}

	ObjectGuid targetGUID;
	bool chase = false;
};

// 52212 - Death and decay damage
// AreaTriggerID - 4485
struct at_dk_death_and_decay : AreaTriggerAI
{
	at_dk_death_and_decay(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger)
	{
		at->SetPeriodicProcTimer(1000);
	}

	void OnUnitEnter(Unit* unit) override
	{
		if (Unit* caster = at->GetCaster())
		{
            if (unit && caster->IsValidAttackTarget(unit) && caster->HasAura(SPELL_DK_GRIP_OF_THE_DEAD))
            {
                caster->CastSpell(unit, SPELL_DK_GRIP_OF_THE_DEAD_SLOW, true);
                caster->CastSpell(caster, SPELL_DK_GRIP_OF_THE_DEAD_TICK, true);
            }

            if (unit->GetOwner() == caster && caster->HasAura(DeathKnight::eLegendary::Phearomones))
                unit->CastSpell(unit, DeathKnight::eLegendary::DeathTurf, true);
		}
	}

    void OnUnitExit(Unit* unit) override
    {
        if (Unit* caster = at->GetCaster())
        {
            if (unit && unit->HasAura(SPELL_DK_GRIP_OF_THE_DEAD_SLOW, caster->GetGUID()))
                unit->RemoveAura(SPELL_DK_GRIP_OF_THE_DEAD_SLOW);

            if (unit->GetOwner() == caster)
                unit->RemoveAurasDueToSpell(DeathKnight::eLegendary::DeathTurf);
        }
    }

    void OnRemove() override
    {
        if (Unit* caster = at->GetCaster())
        {
            caster->RemoveAura(SPELL_DK_GRIP_OF_THE_DEAD_TICK);
            caster->RemoveAura(SPELL_DK_GRIP_OF_THE_DEAD_REDUCTION);
        }
    }

	void OnPeriodicProc() override
	{
        if (Unit* caster = at->GetCaster())
        {
    	    caster->CastSpell(at->GetPosition(), SPELL_DK_DEATH_AND_DECAY_DAMAGE, true);
        }
	}
};

// 199642 Necrotic Aura
// AreaTriggerID - 7325
struct at_dk_necrotic_aura : AreaTriggerAI
{
	at_dk_necrotic_aura(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger) { }

	void OnUnitEnter(Unit* unit) override
	{
		if (Unit* caster = at->GetCaster())
		{
			if (unit && caster->IsValidAttackTarget(unit))
				caster->CastSpell(unit, SPELL_DK_NECROTIC_AURA, true);
		}
	}

	void OnUnitExit(Unit* unit) override
	{
		if (Unit* caster = at->GetCaster())
		{
			if (unit && unit->HasAura(SPELL_DK_NECROTIC_AURA, caster->GetGUID()))
				unit->RemoveAura(SPELL_DK_NECROTIC_AURA);
		}
	}
};

// 199719 Heartstop Aura
// AreaTriggerID - 7326
struct at_dk_heartstop_aura : AreaTriggerAI
{
	at_dk_heartstop_aura(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger) { }

	void OnUnitEnter(Unit* unit) override
	{
		if (Unit* caster = at->GetCaster())
		{
			if (unit && caster->IsValidAttackTarget(unit))
				caster->CastSpell(unit, SPELL_DK_HEARTSTOP_AURA, true);
		}
	}

	void OnUnitExit(Unit* unit) override
	{
		if (Unit* caster = at->GetCaster())
		{
			if (unit && unit->HasAura(SPELL_DK_HEARTSTOP_AURA, caster->GetGUID()))
				unit->RemoveAura(SPELL_DK_HEARTSTOP_AURA);
		}
	}
};

// 51052 Anti-Magic Zone
// AreaTriggerID - 1193
struct at_dk_antimagic_zone : AreaTriggerAI
{
	at_dk_antimagic_zone(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger) { }

	void OnUnitEnter(Unit* unit) override
	{
		if (Unit* caster = at->GetCaster())
		{
			if (unit && caster->IsValidAssistTarget(unit) && (caster->IsInPartyWith(unit) || caster->IsInRaidWith(unit)))
				caster->CastSpell(unit, SPELL_DK_ANTIMAGIC_ZONE_AURA, true);
		}
	}

	void OnUnitExit(Unit* unit) override
	{
		if (Unit* caster = at->GetCaster())
		{
			if (unit && unit->HasAura(SPELL_DK_ANTIMAGIC_ZONE_AURA, caster->GetGUID()))
				unit->RemoveAura(SPELL_DK_ANTIMAGIC_ZONE_AURA);
		}
	}
};

struct at_dk_frostwyrm : AreaTriggerAI
{
    at_dk_frostwyrm(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger) 
    {
        areatrigger->SetPeriodicProcTimer(120);
        areatrigger->SetDuration(3.f * IN_MILLISECONDS);
    }

    void OnPeriodicProc() override
    {
        if (Unit* caster = at->GetCaster())
        {
            Position pos = at->GetPosition();
            caster->CastSpell(pos, SPELL_DK_FROSTWYRM_FROZEN_FLOOR, true);
        }
    }

    void OnUnitEnter(Unit* unit)
    {
        if (Unit* caster = at->GetCaster())
            if (caster->IsValidAttackTarget(unit))
                caster->CastSpell(unit, SPELL_DK_FROSTWYRM_DAMAGE, true);
    }
};

// 52212 - Death and Decay damage
//Last Update 8.0.1 Build 28153
class spell_dk_death_and_decay_damage : public SpellScript
{
    PrepareSpellScript(spell_dk_death_and_decay_damage);

    void HandleEffectHit(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        if (AuraEffect* aurEff = target->GetAuraEffect(SPELL_DK_GRIP_OF_THE_DEAD_SLOW, EFFECT_0))
            aurEff->RecalculateAmount();

        if (Aura* aura = caster->GetAura(SPELL_DK_PESTILENCE))
            if (roll_chance_i(aura->GetEffect(0)->GetAmount()))
                caster->CastSpell(target, SPELL_DK_FESTERING_WOUND, true);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_dk_death_and_decay_damage::HandleEffectHit, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

// 276837 - Army of the Damned
// broken for some reason, not sure why
class aura_dk_army_of_the_damned : public AuraScript
{
	PrepareAuraScript(aura_dk_army_of_the_damned);

	bool CheckProc(ProcEventInfo& eventInfo)
	{
		if (eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == SPELL_DK_DEATH_COIL)
			return true;

		return false;
			}

	void HandleProc(ProcEventInfo& eventInfo)
	{
		if (Unit* caster = GetCaster())
		{
			caster->GetSpellHistory()->ModifyCooldown(SPELL_DK_ARMY_OF_DEATH_TRIGGER, -5s);
			caster->GetSpellHistory()->ModifyCooldown(SPELL_DK_APOCALYPSE, -1s);
		}
	}

	void Register() override
	{
		DoCheckProc += AuraCheckProcFn(aura_dk_army_of_the_damned::CheckProc);
		OnProc += AuraProcFn(aura_dk_army_of_the_damned::HandleProc);
	}
};

// 207289 - Unholy Freenzy
class aura_dk_unholy_freenzy : public AuraScript
{
	PrepareAuraScript(aura_dk_unholy_freenzy);

	void HandleProc(ProcEventInfo& eventInfo)
	{
		Unit* caster = GetCaster();
		Unit* target = eventInfo.GetActionTarget();
		if (!caster || !target)
			return;

		caster->CastSpell(target, SPELL_DK_FESTERING_WOUND, true);
	}

	void Register() override
	{
		OnProc += AuraProcFn(aura_dk_unholy_freenzy::HandleProc);
	}
};

// 253593 - Inexorable Assault
class aura_dk_inexorable_assault : public AuraScript
{
	PrepareAuraScript(aura_dk_inexorable_assault);

	void OnTick(AuraEffect const* /*aurEff*/)
	{
		if (Unit* caster = GetCaster())
			caster->CastSpell(caster, SPELL_DK_INEXORABLE_ASSAULT, true);
	}

	void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
	{
		if (Unit* caster = GetCaster())
			caster->RemoveAura(SPELL_DK_INEXORABLE_ASSAULT);
	}

	void Register() override
	{
		OnEffectPeriodic += AuraEffectPeriodicFn(aura_dk_inexorable_assault::OnTick, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
		OnEffectRemove += AuraEffectRemoveFn(aura_dk_inexorable_assault::HandleRemove, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY, AURA_EFFECT_HANDLE_REAL);
	}
};

// 253595 - Inexorable Assault Aura
class aura_dk_inexorable_assault_aura : public AuraScript
{
	PrepareAuraScript(aura_dk_inexorable_assault_aura);

	bool CheckProc(ProcEventInfo& eventInfo)
	{
		Unit* caster = GetCaster();
		Unit* target = eventInfo.GetActionTarget();
		if (!caster || !target)
			return true;

		if (eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == SPELL_DK_OBLITERATE)
		{
			if (Aura* aura = caster->GetAura(SPELL_DK_INEXORABLE_ASSAULT))
			{
				aura->ModStackAmount(-1);
				caster->CastSpell(target, SPELL_DK_INEXORABLE_ASSAULT_DAMAGE, true);
			}
		}

		return false;
	}

	void Register() override
	{
		DoCheckProc += AuraCheckProcFn(aura_dk_inexorable_assault_aura::CheckProc);
	}
};

// 59057 - Rime
class aura_dk_rime : public AuraScript
{
	PrepareAuraScript(aura_dk_rime);

	bool CheckProc(ProcEventInfo& eventInfo)
	{
		return false;
	}

	void Register() override
	{
		DoCheckProc += AuraCheckProcFn(aura_dk_rime::CheckProc);
	}
};

// 281208 - Cold Heart
class aura_dk_cold_heart : public AuraScript
{
	PrepareAuraScript(aura_dk_cold_heart);

	void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
	{
		if (Unit* caster = GetCaster())
			caster->RemoveAura(SPELL_DK_COLD_HEART);
	}

	void Register() override
	{
		OnEffectRemove += AuraEffectRemoveFn(aura_dk_cold_heart::HandleRemove, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL, AURA_EFFECT_HANDLE_REAL);
	}
};

// 45524 - Chains of Ice
class spell_dk_chains_of_ice : public SpellScript
{
	PrepareSpellScript(spell_dk_chains_of_ice);

	void HandleHit()
	{
		Unit* caster = GetCaster();
		Unit* target = GetHitUnit();
		if (!caster || !target)
			return;

		if (Aura* aura = caster->GetAura(SPELL_DK_COLD_HEART))
		{
			uint8 stacks = aura->GetStackAmount();
            int32 damage = caster->GetTotalAttackPowerValue(BASE_ATTACK) * 0.1f;
			caster->CastCustomSpell(SPELL_DK_COLD_HEART_DAMAGE, SPELLVALUE_BASE_POINT0, damage * stacks, target, true);
			aura->ModStackAmount(-1 * stacks);
		}
	}

	void Register() override
	{
		OnHit += SpellHitFn(spell_dk_chains_of_ice::HandleHit);
	}
};

// 207142 - Avalanche
class aura_dk_avalance : public AuraScript
{
	PrepareAuraScript(aura_dk_avalance);

	bool CheckProc(ProcEventInfo& eventInfo)
	{
		if (Unit* caster = GetCaster())
			if (eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == SPELL_DK_HOWLING_BLAST && caster->HasAura(SPELL_DK_RIME_BUFF))
				return true;

		return false;
	}

	void HandleProc(ProcEventInfo& eventInfo)
	{
		Unit* caster = GetCaster();
		Unit* target = eventInfo.GetActionTarget();
		if (!caster || !target)
			return;

		caster->CastSpell(target, SPELL_DK_AVALANCHE_DAMAGE, true);
	}

	void Register() override
	{
		DoCheckProc += AuraCheckProcFn(aura_dk_avalance::CheckProc);
		OnProc += AuraProcFn(aura_dk_avalance::HandleProc);
	}
};

// 219809 - Tombstone
class spell_dk_tombstone : public SpellScript
{
	PrepareSpellScript(spell_dk_tombstone);

	void HandleAfterHit()
	{
		if (Unit* caster = GetCaster())
			if (Aura* aura = caster->GetAura(SPELL_DK_BONE_SHIELD))
			{
				uint8 maxStacks = sSpellMgr->GetSpellInfo(SPELL_DK_TOMBSTONE)->GetEffect(EFFECT_4).BasePoints;
				uint8 stacks = (aura->GetStackAmount() > maxStacks) ? maxStacks : aura->GetStackAmount();
				caster->ModifyPower(POWER_RUNIC_POWER, sSpellMgr->GetSpellInfo(SPELL_DK_TOMBSTONE)->GetEffect(EFFECT_2).BasePoints * stacks * 10);
				aura->ModStackAmount(-stacks);
			}
	}

	void Register() override
	{
		AfterHit += SpellHitFn(spell_dk_tombstone::HandleAfterHit);
	}
};

// 219809 - Tombstone Aura
class aura_dk_tombstone_aura : public AuraScript
{
	PrepareAuraScript(aura_dk_tombstone_aura);

	void CalculateAmountAbsorb(AuraEffect const* /*aurEff*/, int32& amount, bool& /*canBeRecalculated*/)
	{
		if (Unit* caster = GetCaster())
			if (Aura* aura = caster->GetAura(SPELL_DK_BONE_SHIELD))
			{
				uint8 maxStacks = sSpellMgr->GetSpellInfo(SPELL_DK_TOMBSTONE)->GetEffect(EFFECT_4).BasePoints;
				uint8 stacks = (aura->GetStackAmount() > maxStacks) ? maxStacks : aura->GetStackAmount();
				amount = CalculatePct(caster->GetMaxHealth(), sSpellMgr->GetSpellInfo(SPELL_DK_TOMBSTONE)->GetEffect(EFFECT_3).BasePoints * stacks);
			}
	}

	void Register() override
	{
		DoEffectCalcAmount += AuraEffectCalcAmountFn(aura_dk_tombstone_aura::CalculateAmountAbsorb, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
	}
};

// 206940 - Mark of Blood
class aura_dk_mark_of_blood : public AuraScript
{
	PrepareAuraScript(aura_dk_mark_of_blood);

	void HandleProc(ProcEventInfo& eventInfo)
	{
		Unit* target = eventInfo.GetProcTarget();
		Unit* owner = GetUnitOwner();
		if (!owner || !target)
			return;

		if (target->IsAlive())
			target->CastSpell(target, SPELL_DK_MARK_OF_BLODD_HEAL, true);
	}

	void Register() override
	{
		OnProc += AuraProcFn(aura_dk_mark_of_blood::HandleProc);
	}
};

// 194844 - Bonestorm
class spell_dk_bonestorm : public SpellScript
{
	PrepareSpellScript(spell_dk_bonestorm);

	void HandleTakePower(SpellPowerCost& powerCost)
	{
		if (powerCost.Power == POWER_RUNIC_POWER)
			runicPower = powerCost.Amount;
	}

	void HandleAfterHit()
	{
		if (Unit* caster = GetCaster())
			if (Aura* aura = caster->GetAura(SPELL_DK_BONESTORM))
				aura->SetDuration(runicPower / 100 * IN_MILLISECONDS);
	}

	void Register() override
	{
		OnTakePower += SpellOnTakePowerFn(spell_dk_bonestorm::HandleTakePower);
		AfterHit += SpellHitFn(spell_dk_bonestorm::HandleAfterHit);
	}

private:
	uint32 runicPower = 10;
};

// 196528 - Bonestorm Damage
class spell_dk_bonestorm_damage : public SpellScript
{
	PrepareSpellScript(spell_dk_bonestorm_damage);

	void HandleOnHit()
	{
		if (Unit* caster = GetCaster())
			caster->CastSpell(caster, SPELL_DK_BONESTORM_HEAL, true);
	}

	void Register() override
	{
		OnHit += SpellHitFn(spell_dk_bonestorm_damage::HandleOnHit);
	}
};

// 273946 - Hemostasis
class aura_dk_hemostatis : public AuraScript
{
	PrepareAuraScript(aura_dk_hemostatis);

	bool CheckProc(ProcEventInfo& eventInfo)
	{
		if (eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == SPELL_DK_BLOOD_BOIL)
			return true;

		return false;
	}

	void Register() override
	{
		DoCheckProc += AuraCheckProcFn(aura_dk_hemostatis::CheckProc);
	}
};

// 273947 - Hemostasis Aura
class aura_dk_hemostatis_aura : public AuraScript
{
	PrepareAuraScript(aura_dk_hemostatis_aura);

	bool CheckProc(ProcEventInfo& eventInfo)
	{
		return false;
	}

	void HandleProc(ProcEventInfo& eventInfo)
	{
		if (Unit* caster = GetCaster())
			caster->RemoveAura(SPELL_DK_HEMOSTATIS_AURA);
	}

	void Register() override
	{
		DoCheckProc += AuraCheckProcFn(aura_dk_hemostatis_aura::CheckProc);
	}
};

// 223829 - Necrotic Strike
class spell_dk_necrotic_strike : public SpellScript
{
	PrepareSpellScript(spell_dk_necrotic_strike);

	void HandleEffectHit(SpellEffIndex /*effIndex*/)
	{
		Unit* caster = GetCaster();
		Unit* target = GetHitUnit();
		if (!caster || !target)
			return;

		if (Aura* aura = target->GetAura(SPELL_DK_FESTERING_WOUND, caster->GetGUID()))
		{
			int32 amount = CalculatePct(caster->GetTotalAttackPowerValue(BASE_ATTACK), sSpellMgr->GetSpellInfo(SPELL_DK_NECROTIC_WOUND)->GetEffect(EFFECT_1).BasePoints);
			caster->CastCustomSpell(SPELL_DK_NECROTIC_WOUND, SPELLVALUE_BASE_POINT0, amount, target, true);
			aura->ModStackAmount(-1);
		}
	}

	void Register() override
	{
		OnEffectHitTarget += SpellEffectFn(spell_dk_necrotic_strike::HandleEffectHit, EFFECT_2, SPELL_EFFECT_SCHOOL_DAMAGE);
	}
};

// 191685 - Virulent Plage Damage Last Update 8.0.1 Build 28153
class spell_dk_virulent_plage_damage : public SpellScript
{
	PrepareSpellScript(spell_dk_virulent_plage_damage);

	void HandleEffectHit(SpellEffIndex /*effIndex*/)
	{
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        // Divide damage by nearby enemy count.
        UnitList list;
        target->GetFriendlyUnitListInRange(list, 8.0f);
        int32 damage = GetHitDamage() / ((list.size() > 0) ? list.size() : 1);
        if (caster->HasAura(SPELL_DK_UNHOLY_MUTATION) && caster->Variables.Exist("MutationDamage"))
        {
            caster->Variables.Remove("MutationDamage");
            damage += CalculatePct(damage, sSpellMgr->GetSpellInfo(SPELL_DK_UNHOLY_MUTATION)->GetEffect(EFFECT_0).BasePoints);
        }
        
        SetHitDamage(damage);
	}

	void Register() override
	{
		OnEffectHitTarget += SpellEffectFn(spell_dk_virulent_plage_damage::HandleEffectHit, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
	}
};

// 210128 - Reanimation
class spell_dk_reanimation : public SpellScript
{
	PrepareSpellScript(spell_dk_reanimation);

	void HandlePrepare()
	{
		if (Unit* caster = GetCaster())
		{
			if (caster->GetTarget() != ObjectGuid::Empty)
			{
                if(Unit* target = ObjectAccessor::GetUnit(*caster, caster->GetTarget()))
                    caster->SetInCombatWith(target);
                if (auto zombieTarget = GetExplTargetUnit())
                    caster->Variables.Set<ObjectGuid>("ZOMBIE_TARGET", zombieTarget->GetGUID());
			}
		}
	}

	void Register() override
	{
		OnPrepare += SpellOnPrepareFn(spell_dk_reanimation::HandlePrepare);
	}
};

// 233395 - Frozen Center
class aura_dk_frozen_center : public AuraScript
{
	PrepareAuraScript(aura_dk_frozen_center);

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
				owner->ToUnit()->RemoveAura(SPELL_DK_FROZEN_CENTER_ROOT);
	}

	void Register() override
	{
		DoCheckProc += AuraCheckProcFn(aura_dk_frozen_center::CheckProc);
		OnProc += AuraProcFn(aura_dk_frozen_center::HandleProc);
	}
};

// 203173 - Death Chain
class spell_dk_death_chain : public SpellScript
{
	PrepareSpellScript(spell_dk_death_chain);

	void HandleHitTarget(SpellEffIndex /*effIndex*/)
	{
		Unit* caster = GetCaster();
		Unit* target = GetHitUnit();
		Unit* expTarget = GetExplTargetUnit();
		if (!caster || !target || !expTarget)
			return;

		if (target->GetGUID() != expTarget->GetGUID())
			expTarget->CastSpell(target, SPELL_DK_DEATH_CHAIN_VISUAL, true);
	}

	void Register() override
	{
		OnEffectHitTarget += SpellEffectFn(spell_dk_death_chain::HandleHitTarget, EFFECT_0, SPELL_EFFECT_APPLY_AURA);
	}
};

class aura_dk_death_chain : public AuraScript 
{
	PrepareAuraScript(aura_dk_death_chain);

	bool Validate(SpellInfo const* /*spellInfo*/) override
	{
		return ValidateSpellInfo({ SPELL_DK_DEATH_CHAIN });
	}

	bool CheckProc(ProcEventInfo& eventInfo)
	{
		if (eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == SPELL_DK_DEATH_CHAIN_DAMAGE)
			return false;

		return true;
	}

	void HandleProc(ProcEventInfo& eventInfo)
	{
		Unit* caster = GetCaster();
		Unit* target = eventInfo.GetActionTarget();
		if (!caster || !target)
			return;

		if (eventInfo.GetDamageInfo() && eventInfo.GetDamageInfo()->GetDamage() > 0)
		{
			std::list<Unit*> targets;
			target->GetFriendlyUnitListInRange(targets, 100.f, true);
			targets.remove_if(Trinity::UnitAuraCheck(false, SPELL_DK_DEATH_CHAIN, caster->GetGUID()));
			for (Unit* tg : targets)
				caster->CastCustomSpell(SPELL_DK_DEATH_CHAIN_DAMAGE, SPELLVALUE_BASE_POINT0, CalculatePct(eventInfo.GetDamageInfo()->GetDamage(), sSpellMgr->GetSpellInfo(SPELL_DK_DEATH_CHAIN)->GetEffect(EFFECT_0).BasePoints), tg, true);
		}
	}

	void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes mode)
	{
		Unit* caster = GetCaster();
		Unit* target = GetUnitOwner();
		if (!caster || !target)
			return;

		target->RemoveAura(SPELL_DK_DEATH_CHAIN_VISUAL, caster->GetGUID());
	}

	void Register() override
	{
		DoCheckProc += AuraCheckProcFn(aura_dk_death_chain::CheckProc);
		OnProc += AuraProcFn(aura_dk_death_chain::HandleProc);
		OnEffectRemove += AuraEffectRemoveFn(aura_dk_death_chain::HandleRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
	}
};

// 233396 - Delirium
class aura_dk_delirium : public AuraScript
{
	PrepareAuraScript(aura_dk_delirium);

	bool CheckProc(ProcEventInfo& eventInfo)
	{
		if (eventInfo.GetSpellInfo() && (eventInfo.GetSpellInfo()->Id == SPELL_DK_HOWLING_BLAST || eventInfo.GetSpellInfo()->Id == SPELL_DK_HOWLING_BLAST_AOE ||
            eventInfo.GetSpellInfo()->Id == SPELL_DK_FROST_STRIKE_MAIN_HAND))
			return true;

		return false;
	}

	void Register() override
	{
		DoCheckProc += AuraCheckProcFn(aura_dk_delirium::CheckProc);
	}
};

// 199969 - Wandering Plague
class aura_dk_wandering_plague : public AuraScript
{
	PrepareAuraScript(aura_dk_wandering_plague);

	void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
	{
		if (GetTargetApplication()->GetRemoveMode() != AURA_REMOVE_BY_ENEMY_SPELL && GetTargetApplication()->GetRemoveMode() != AURA_REMOVE_BY_EXPIRE)
			return;

		// Find nearby enemy to infect.
		Unit* caster = GetCaster();
		Unit* target = GetTarget();
		if (!caster || !target)
			return;

		if (caster->Variables.Exist("WP_JUMPS") && caster->Variables.GetValue<uint8>("WP_JUMPS") < 3)
		{
			caster->Variables.Set<ObjectGuid>("WP_MAIN", target->GetGUID());
			caster->CastSpell(target, SPELL_DK_WANDERING_PLAGUE_SELECTOR, true);
			uint8 jump = caster->Variables.GetValue<uint8>("WP_JUMPS") + 1;
			caster->Variables.Set("WP_JUMPS", jump);
		}
	}

	void Register() override
	{
		AfterEffectRemove += AuraEffectApplyFn(aura_dk_wandering_plague::HandleRemove, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE, AURA_EFFECT_HANDLE_REAL);
	}
};

// 200093 - Wandering Plague Selector
class spell_dk_wandering_plague_selector : public SpellScript
{
	PrepareSpellScript(spell_dk_wandering_plague_selector);

	void FilterTargets(std::list<WorldObject*>& targets)
	{
		if (Unit* caster = GetCaster())
		{
			targets.remove_if([caster](WorldObject* obj)
			{
				if (caster->Variables.Exist("WP_MAIN") && obj->GetGUID() == caster->Variables.GetValue<ObjectGuid>("WP_MAIN"))
					return true;

				if (!obj->ToUnit())
					return true;

				if (!caster->IsValidAttackTarget(obj->ToUnit()))
					return true;

				if (!obj->ToUnit()->HasAura(SPELL_DK_VIRULENT_PLAGUE, caster->GetGUID()) &&
					!obj->ToUnit()->HasAura(SPELL_DK_OUTBREAK_PERIODIC, caster->GetGUID()) &&
					!obj->ToUnit()->HasAura(SPELL_DK_UNHOLY_BLIGHT, caster->GetGUID()))
					return true;

				return false;
			});

			if (targets.size() > 0)
				Trinity::Containers::RandomResize(targets, 1);
		}
	}

	void HandleHit()
	{
		Unit* caster = GetCaster();
		Unit* target = GetHitUnit();
		if (!caster || !target)
			return;

		caster->CastSpell(target, SPELL_DK_WANDERING_PLAGUE_DISEASE, true);
	}

	void Register() override
	{
		OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_dk_wandering_plague_selector::FilterTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ENEMY);
		OnHit += SpellHitFn(spell_dk_wandering_plague_selector::HandleHit);
	}
};

// 199724 - Pandemic
class aura_dk_pandemic : public AuraScript
{
	PrepareAuraScript(aura_dk_pandemic);

	bool CheckProc(ProcEventInfo& eventInfo)
	{
		if (eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == SPELL_DK_OUTBREAK)
			return true;

		return false;
	}

	void Register() override
	{
		DoCheckProc += AuraCheckProcFn(aura_dk_pandemic::CheckProc);
	}
};

// 199799 - Pandemic Damage
class spell_dk_pandemic_damage : public SpellScript
{
	PrepareSpellScript(spell_dk_pandemic_damage);

	void FilterTargets(std::list<WorldObject*>& targets)
	{
		if (Unit* caster = GetCaster())
		{
			targets.remove_if([caster](WorldObject* obj)
			{
				if (!obj->ToUnit())
					return true;

				if (!caster->IsValidAttackTarget(obj->ToUnit()))
					return true;

				if (!obj->ToUnit()->HasAura(SPELL_DK_VIRULENT_PLAGUE, caster->GetGUID()) &&
					!obj->ToUnit()->HasAura(SPELL_DK_OUTBREAK_PERIODIC, caster->GetGUID()) &&
					!obj->ToUnit()->HasAura(SPELL_DK_UNHOLY_BLIGHT, caster->GetGUID()) &&
					!obj->ToUnit()->HasAura(SPELL_DK_WANDERING_PLAGUE_DISEASE, caster->GetGUID()))
					return true;

				return false;
			});
		}
	}

	void HandleHit()
	{
		Unit* caster = GetCaster();
		Unit* target = GetHitUnit();
		if (!caster || !target)
			return;

		if (Aura* aura = target->GetAura(SPELL_DK_VIRULENT_PLAGUE, caster->GetGUID()))
			aura->SetDuration(aura->GetMaxDuration());
		if (Aura* aura = target->GetAura(SPELL_DK_OUTBREAK_PERIODIC, caster->GetGUID()))
			aura->SetDuration(aura->GetMaxDuration());
		if (Aura* aura = target->GetAura(SPELL_DK_UNHOLY_BLIGHT, caster->GetGUID()))
			aura->SetDuration(aura->GetMaxDuration());
	}

	void Register() override
	{
		OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_dk_pandemic_damage::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
		OnHit += SpellHitFn(spell_dk_pandemic_damage::HandleHit);
	}

private:
	WorldObject * mainTarget = NULL;
};

// 195621 - Frost Fever Proc
class aura_dk_frost_fever_proc : public AuraScript
{
	PrepareAuraScript(aura_dk_frost_fever_proc);

	bool CheckProc(ProcEventInfo& eventInfo)
	{
		if (eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == SPELL_DK_FROST_FEVER)
			return true;

		return false;
	}

	void Register() override
	{
		DoCheckProc += AuraCheckProcFn(aura_dk_frost_fever_proc::CheckProc);
	}
};

// 207126 - Icecap
class aura_dk_icecap : public AuraScript
{
	PrepareAuraScript(aura_dk_icecap);

	bool CheckProc(ProcEventInfo& eventInfo)
	{
		return false;
	}

	void Register() override
	{
		DoCheckProc += AuraCheckProcFn(aura_dk_icecap::CheckProc);
	}
};

// 222026 - Frost Strike Main Hand
class spell_frost_strike_main_hand : public SpellScript
{
	PrepareSpellScript(spell_frost_strike_main_hand);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_DK_OBLITERATION });
    }

	void HandleHit()
	{
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        // Icecap
        if (caster->HasAura(SPELL_DK_ICECAP) && IsHitCrit())
        {
            caster->Variables.Set<bool>("IC_HANDLE_CRIT", true);
            caster->GetSpellHistory()->ModifyCooldown(SPELL_DK_PILLAR_OF_FROST, -1s);
        }

        // Killer Frost
        if (Aura* aura = caster->GetAura(SPELL_DK_KILLER_FROST_POWER))
        {
            int32 damage = GetHitDamage();
            SetHitDamage(damage + aura->GetEffect(0)->GetAmount());
        }

        /// EradicatingBlowBuff (Conduit)
        if (Aura* aura = caster->GetAura(337936))
        {
            int32 damage = GetHitDamage();
            SetHitDamage(damage + CalculatePct(damage, aura->GetEffect(EFFECT_0)->GetAmount()));
            aura->Remove();
        }

        // Thundra Stalker
        uint32 const MechanicList =
            (1 << MECHANIC_ROOT)
            | (1 << MECHANIC_STUN)
            | (1 << MECHANIC_SLEEP)
            | (1 << MECHANIC_SAPPED)
            | (1 << MECHANIC_FREEZE);

        if (caster->HasAura(SPELL_DK_THUNDRA_STALKER) && target->HasAuraWithMechanic(MechanicList))
            caster->CastSpell(caster, SPELL_DK_THUNDRA_STALKER_BUFF, true);

        // Obliteration
        if (caster->HasAura(SPELL_DK_OBLITERATION_PROC))
        {
            caster->CastSpell(caster, SPELL_DK_KILLING_MACHINE, true);
            if (roll_chance_i(sSpellMgr->GetSpellInfo(SPELL_DK_OBLITERATION)->GetEffect(EFFECT_1).BasePoints))
                caster->CastSpell(caster, SPELL_DK_OBLITERATION_ENERGIZE, true);
        }
	}

	void Register() override
	{
		OnHit += SpellHitFn(spell_frost_strike_main_hand::HandleHit);
	}
};

// 66196 - Frost Strike Off Hand
class spell_dk_frost_strike_off_hand : public SpellScript
{
	PrepareSpellScript(spell_dk_frost_strike_off_hand);

	void HandleHit()
	{
		if (Unit* caster = GetCaster())
		{
			// Icecap
			if (caster->HasAura(SPELL_DK_ICECAP) && IsHitCrit() && !caster->Variables.Exist("IC_HANDLE_CRIT"))
				caster->GetSpellHistory()->ModifyCooldown(SPELL_DK_PILLAR_OF_FROST, -1s);

			caster->Variables.Remove("IC_HANDLE_CRIT");

            // Killer Frost
            if (Aura* aura = caster->GetAura(SPELL_DK_KILLER_FROST_POWER))
            {
                int32 damage = GetHitDamage();
                SetHitDamage(damage + aura->GetEffect(0)->GetAmount());
            }
		}
	}

	void Register() override
	{
		OnHit += SpellHitFn(spell_dk_frost_strike_off_hand::HandleHit);
	}
};

// 281238 - Obliteration
class aura_dk_obliteration : public AuraScript
{
    PrepareAuraScript(aura_dk_obliteration);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }

    void HandleRemove(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /* mode */)
    {
        if (Unit* caster = GetCaster())
            caster->RemoveAura(SPELL_DK_OBLITERATION_PROC);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_dk_obliteration::CheckProc);
        OnEffectRemove += AuraEffectRemoveFn(aura_dk_obliteration::HandleRemove, EFFECT_1, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

// 207256 - Obliteration Proc
class aura_dk_obliteration_proc : public AuraScript
{
    PrepareAuraScript(aura_dk_obliteration_proc);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_dk_obliteration_proc::CheckProc);
    }
};

// 51124 - Killing Machine
class aura_dk_killing_machine : public AuraScript
{
    PrepareAuraScript(aura_dk_killing_machine);

    void HandleRemove(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /* mode */)
    {
        if (GetTargetApplication()->GetRemoveMode() != AURA_REMOVE_BY_DEFAULT)
            return;

        if (Unit* caster = GetCaster())
            if (caster->HasAura(SPELL_DK_MURDEROUS_EFFICIENCY) && roll_chance_i(sSpellMgr->GetSpellInfo(SPELL_DK_MURDEROUS_EFFICIENCY)->GetEffect(EFFECT_0).BasePoints))
                caster->CastSpell(caster, SPELL_DK_MURDEROUS_EFFICIENCY_ENERGIZE, true);
    }

    void Register() override
    {
        OnEffectRemove += AuraEffectRemoveFn(aura_dk_killing_machine::HandleRemove, EFFECT_0, SPELL_AURA_ADD_FLAT_MODIFIER, AURA_EFFECT_HANDLE_REAL);
    }
};

// 204160 - Chill Streak
//Last Update 8.0.1 Build 28153
class spell_dk_chill_streak : public SpellScript
{
    PrepareSpellScript(spell_dk_chill_streak);

    void HandleHit()
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        caster->CastSpell(target, SPELL_DK_CHILL_STREAK_MISSILE, true);
        caster->CastSpell(target, SPELL_DK_CHILL_STREAK_DAMAGE, true);
        caster->Variables.Set<uint8>("CS_JUMPS", 0);
    }

    void Register() override
    {
        OnHit += SpellHitFn(spell_dk_chill_streak::HandleHit);
    }
};

// 204199 - Chill Streak Missile
class spell_dk_chill_streak_missiles : public SpellScript
{
    PrepareSpellScript(spell_dk_chill_streak_missiles);

    void HandleHit()
    {
        Unit* caster = GetOriginalCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        caster->CastSpell(target, SPELL_DK_CHILL_STREAK_SLOW, true);
        if (caster->Variables.Exist("CS_JUMPS") && caster->Variables.GetValue<uint8>("CS_JUMPS") < 9)
        {
            caster->Variables.Set<ObjectGuid>("CS_MAIN", target->GetGUID());
            caster->CastSpell(target, SPELL_DK_CHILL_STREAK_SELECTOR, true);
            uint8 jump = caster->Variables.GetValue<uint8>("CS_JUMPS") + 1;
            caster->Variables.Set("CS_JUMPS", jump);
        }
    }

    void Register() override
    {
        OnHit += SpellHitFn(spell_dk_chill_streak_missiles::HandleHit);
    }
};

// 204165 - Chill Streak Selector
class spell_dk_chill_streak_selector : public SpellScript
{
    PrepareSpellScript(spell_dk_chill_streak_selector);

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        if (Unit* caster = GetOriginalCaster())
        {
            targets.remove_if([caster](WorldObject* obj)
            {
                if (caster->Variables.Exist("CS_MAIN") && obj->GetGUID() == caster->Variables.GetValue<ObjectGuid>("CS_MAIN"))
                    return true;

                if (!obj->ToUnit())
                    return true;

                if (!caster->IsValidAttackTarget(obj->ToUnit()))
                    return true;

                return false;
            });

            if (targets.size() > 0)
                Trinity::Containers::RandomResize(targets, 1);
        }
    }

    void HandleHit()
    {
        Unit* caster = GetOriginalCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        if (caster->Variables.Exist("CS_MAIN"))
        {
            Unit* lastTarget = ObjectAccessor::GetUnit(*caster, caster->Variables.GetValue<ObjectGuid>("CS_MAIN"));
            if (lastTarget)
            {
                lastTarget->CastSpell(target, SPELL_DK_CHILL_STREAK_MISSILE, true);
                lastTarget->CastSpell(target, SPELL_DK_CHILL_STREAK_DAMAGE, true);
            }
        }
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_dk_chill_streak_selector::FilterTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ENEMY);
        OnHit += SpellHitFn(spell_dk_chill_streak_selector::HandleHit);
    }
};

// 195975 - Glacial Advance Damage
class spell_dk_glacial_advance_damage : public SpellScript
{
    PrepareSpellScript(spell_dk_glacial_advance_damage);

    void HandleHit()
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        std::list<ObjectGuid> targets;
        if (caster->Variables.Exist("GLACIAL_ADVANCE"))
            targets = caster->Variables.GetValue<std::list<ObjectGuid>>("GLACIAL_ADVANCE");

        for (ObjectGuid guid : targets)
        {
            if (guid == target->GetGUID())
            {
                PreventHitDamage();
                return;
            }
        }        

        caster->CastSpell(target, SPELL_DK_RAZORICE, true);
        targets.push_back(target->GetGUID());
        caster->Variables.Set<std::list<ObjectGuid>>("GLACIAL_ADVANCE", targets);
    }

    void Register() override
    {
        OnHit += SpellHitFn(spell_dk_glacial_advance_damage::HandleHit);
    }

private:

};

// 279302 - Frostwyrm's Fury
class spell_dk_frostwyrm_fury : public SpellScript
{
    PrepareSpellScript(spell_dk_frostwyrm_fury);

    void HandleCast()
    {
        if (Unit* caster = GetCaster())
        {
            float angle = 3.14 + caster->GetOrientation();
            float destx, desty;
            destx = caster->GetPositionX() + 10 * std::cos(angle);
            desty = caster->GetPositionY() + 10 * std::sin(angle);
            Position summonPos = Position(destx, desty, caster->GetPositionZ() + 8, caster->GetOrientation());
            TempSummon* summon = caster->SummonCreature(117591, summonPos, TEMPSUMMON_TIMED_DESPAWN, 5s);
            if (summon)
            {
                // Avoid any interaction with the Wyrm.
                summon->SetUnitFlag(UNIT_FLAG_UNINTERACTIBLE);
                summon->SetUnitFlag(UNIT_FLAG_NON_ATTACKABLE);
                summon->SetUnitFlag(UNIT_FLAG_IMMUNE_TO_PC);
                summon->SetUnitFlag(UNIT_FLAG_IMMUNE_TO_NPC);

                // Calculate the new destination.
                angle = summon->GetOrientation();
                destx = summon->GetPositionX() + 50 * std::cos(angle);
                desty = summon->GetPositionY() + 50 * std::sin(angle);
                Position destPos[2] =
                {
                    { summon->GetPositionX(), summon->GetPositionY(), summon->GetPositionZ() + 6},
                    { destx, desty, summon->GetPositionZ() + 6},
                };
                for (uint8 i = MOVE_WALK; i < MAX_MOVE_TYPE; i++)
                    summon->SetSpeedRate((UnitMoveType)i, 5.0f);
                summon->SetFlying(true);
                summon->GetMotionMaster()->MoveSmoothPath(0, destPos, 2, false, true, 25.0f);
                caster->CastSpell(summon, SPELL_DK_FROSTWYRM_BREATH, true);
            }
        }
    }

    void Register() override
    {
        OnCast += SpellCastFn(spell_dk_frostwyrm_fury::HandleCast);
    }
};

// 81136 - Crimson Scourge
class aura_dk_crimson_scourge : public AuraScript
{
    PrepareAuraScript(aura_dk_crimson_scourge);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();
        Unit* target = eventInfo.GetActionTarget();
        if (!caster || !target)
            return false;

        if (target->HasAura(SPELL_DK_BLOOD_PLAGUE, caster->GetGUID()))
            return true;

        return false;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (Unit* caster = GetCaster())
        {
                caster->GetSpellHistory()->ResetCooldown(SPELL_DK_DEFILE, true);
                caster->GetSpellHistory()->ResetCooldown(SPELL_DK_DEATH_AND_DECAY, true);
                caster->CastSpell(caster, SPELL_DK_CRIMSON_SCOURGE, true);
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_dk_crimson_scourge::CheckProc);
        OnProc += AuraProcFn(aura_dk_crimson_scourge::HandleProc);
    }
};

// 91776 - Claw / 91778 - Sweeping Claws
class spell_dk_claw : public SpellScript
{
    PrepareSpellScript(spell_dk_claw);

    void HandleHit()
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        Unit* owner = caster->GetOwner();
        if (!owner)
            return;

        if (owner->HasAura(SPELL_DK_INFECTED_CLAWS))
            if (roll_chance_i(sSpellMgr->GetSpellInfo(SPELL_DK_INFECTED_CLAWS)->GetEffect(EFFECT_0).BasePoints))
                owner->CastSpell(target, SPELL_DK_FESTERING_WOUND, true);
    }

    void Register() override
    {
        OnHit += SpellHitFn(spell_dk_claw::HandleHit);
    }
};

// 81340 - Sudden Doom
class aura_dk_sudden_doom : public AuraScript
{
    PrepareAuraScript(aura_dk_sudden_doom);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_dk_sudden_doom::CheckProc);
    }
};

// 273980 - Grip of the Dead Tick
class aura_dk_grip_of_the_dead_tick : public AuraScript
{
    PrepareAuraScript(aura_dk_grip_of_the_dead_tick);

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
        if (Unit* caster = GetCaster())
            caster->CastSpell(caster, SPELL_DK_GRIP_OF_THE_DEAD_REDUCTION, true);
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(aura_dk_grip_of_the_dead_tick::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

// 49028 - Dancing Rune Weapon
class spell_dk_dancing_rune_weapon : public SpellScript
{
    PrepareSpellScript(spell_dk_dancing_rune_weapon);

    void HandleAfterCast()
    {
        if (Unit* caster = GetCaster())
        {
            caster->CastSpell(caster, SPELL_DK_BLODD_DANCING_RUNE_WEAPON_ENERGIZE, true);
            if (Aura* aura = caster->GetAura(SPELL_DK_BLODD_DANCING_RUNE_WEAPON_ENERGIZE))
                aura->SetDuration(8 * IN_MILLISECONDS);
        }
    }

    void Register() override
    {
        AfterCast += SpellCastFn(spell_dk_dancing_rune_weapon::HandleAfterCast);
    }
};

// 49028 - Dancing Rune Weapon
class aura_dk_dancing_rune_weapon : public AuraScript
{
    PrepareAuraScript(aura_dk_dancing_rune_weapon);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetDamageInfo() && eventInfo.GetDamageInfo()->GetDamageType() == DOT)
            return false;

        return true;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetDamageInfo() || !eventInfo.GetDamageInfo()->GetSpellInfo())
            return;
    
        Unit* caster = GetCaster();
        Unit* target = eventInfo.GetActionTarget();
        if (!caster || !target)
            return;

        Unit* weapon = NULL;
        for (auto itr = caster->m_Controlled.begin(); itr != caster->m_Controlled.end(); ++itr) // Find Rune Weapon
            if ((*itr)->GetEntry() == 27893)
            {
                weapon = *itr;
                break;
            }

        if (!weapon)
            return;

        SpellNonMeleeDamage damageLog = SpellNonMeleeDamage(weapon,
            target,
            eventInfo.GetSpellInfo(),
            SpellCastVisual(eventInfo.GetSpellInfo()->GetSpellXSpellVisualId(), 0 ),
            eventInfo.GetSchoolMask());
        damageLog.damage = eventInfo.GetDamageInfo()->GetDamage();
        caster->SendSpellNonMeleeDamageLog(&damageLog);
        uint32 dam = eventInfo.GetDamageInfo()->GetDamage();
        Unit::DealDamage(weapon, target, dam);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_dk_dancing_rune_weapon::CheckProc);
        OnProc += AuraProcFn(aura_dk_dancing_rune_weapon::HandleProc);
    }
};

// 127344 - Corpse Exploder
class spell_dk_corpse_exploder : public SpellScript
{
    PrepareSpellScript(spell_dk_corpse_exploder);

    SpellCastResult CheckCast()
    {
        if (Unit* target = GetExplTargetUnit())
            if (target->IsAlive())
                return SPELL_FAILED_BAD_TARGETS;

        return SPELL_CAST_OK;
    }

    void Register() override
    {
        OnCheckCast += SpellCheckCastFn(spell_dk_corpse_exploder::CheckCast);
    }
};

// Called by All Will Serve - 194916
// Last Update 8.0.1 Build 28153
class aura_dk_all_will_serve : public AuraScript
{
    PrepareAuraScript(aura_dk_all_will_serve);

    void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Unit* caster = GetCaster();
        if (!caster)
            return;

        for (auto pet : caster->m_Controlled)
        {
            if (pet && pet->GetEntry() == ENTRY_RISEN_SKULKER)
            {
                pet->ToCreature()->DespawnOrUnsummon();
                break;
            }
        }
    }

    void Register() override
    {
        AfterEffectRemove += AuraEffectRemoveFn(aura_dk_all_will_serve::OnRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

// Called by Dark Simulacrum - 77606
// Last Update 8.0.1 Build 28153
class aura_dk_dark_simulacrum : public AuraScript
{
    PrepareAuraScript(aura_dk_dark_simulacrum);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetSpellInfo())
            return false;

        return true;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();
        Unit* target = GetTarget();
        if (!caster || !target)
            return;

        if (caster->HasAura(SPELL_DK_DARK_SIMULACRUM_REPLACER))
            return;

        if (!eventInfo.GetSpellInfo()->IsCanBeStolen())
            return;

        // Replacer
        int32  basepoints0 = eventInfo.GetSpellInfo()->Id;
        caster->CastCustomSpell(caster, SPELL_DK_DARK_SIMULACRUM_REPLACER, &basepoints0, NULL, NULL, true);

        // SpellPower
        int32 spellPower = target->SpellBaseDamageBonusDone(SpellSchoolMask(eventInfo.GetSpellInfo()->SchoolMask));
        int32 healPower = target->SpellBaseHealingBonusDone(SpellSchoolMask(eventInfo.GetSpellInfo()->SchoolMask));
        caster->CastCustomSpell(caster, SPELL_DK_DARK_SIMULACRUM_MODS, &spellPower, &healPower, NULL, true);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_dk_dark_simulacrum::CheckProc);
        OnProc += AuraProcFn(aura_dk_dark_simulacrum::HandleProc);
    }
};

// 210141 Zombie Explosion
//Last Update 8.0.1 Build 28153
class spell_dk_zombie_explosion : public SpellScript
{
    PrepareSpellScript(spell_dk_zombie_explosion);

    void HandleHitTarget(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetOriginalCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        uint8 pct = sSpellMgr->GetSpellInfo(SPELL_DK_REANIMATION_DAMAGE)->GetEffect(EFFECT_1).BasePoints;
        SetHitDamage(CalculatePct(target->IsPlayer() ? target->GetMaxHealth() : caster->GetMaxHealth(), pct));
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_dk_zombie_explosion::HandleHitTarget, EFFECT_0, SPELL_EFFECT_DAMAGE_FROM_MAX_HEALTH_PCT);
    }
};

// 199721 Decomposing Aura
//Last Update 8.0.1 Build 28153
class spell_dk_decomposing_aura_selector : public SpellScript
{
    PrepareSpellScript(spell_dk_decomposing_aura_selector);

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        if (Unit* caster = GetCaster())
        {
            targets.remove_if([caster](WorldObject* obj)
            {
                if (!obj->ToUnit())
                    return true;

                if(!obj->IsPlayer() && !caster->GetMap()->IsBattlegroundOrArena()) //Can be used in Alterac Valley agains boss
                    return true;

                return false;
            });
        }
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_dk_decomposing_aura_selector::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
    }
};

// 204167 Chill Streak
//Last Update 8.0.1 Build 28153
class spell_dk_chill_streak_damage : public SpellScript
{
    PrepareSpellScript(spell_dk_chill_streak_damage);

    void HandleHitTarget(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetOriginalCaster() ? GetOriginalCaster() : GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        uint8 pct = sSpellMgr->GetSpellInfo(SPELL_DK_CHILL_STREAK_DAMAGE)->GetEffect(EFFECT_1).BasePoints;
        SetHitDamage(CalculatePct(target->IsPlayer() ? target->GetMaxHealth() : caster->GetMaxHealth(), pct));
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_dk_chill_streak_damage::HandleHitTarget, EFFECT_0, SPELL_EFFECT_DAMAGE_FROM_MAX_HEALTH_PCT);
    }
};

// 194878 - Icy Talons
// Last Update 8.0.1 Build 28153
class aura_dk_icy_talons : public AuraScript
{
    PrepareAuraScript(aura_dk_icy_talons);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetSpellInfo())
            if (Spell const* procSpell = eventInfo.GetProcSpell())
                if (SpellPowerCost const* powerCost = procSpell->GetPowerCost(POWER_RUNES))
                    if (powerCost->Amount > 0)
                        return true;

        return false;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_dk_icy_talons::CheckProc);
    }
};

// ID - 326801 Rune of Sanguination
class spell_dk_rune_of_sanguination : public AuraScript
{
    PrepareAuraScript(spell_dk_rune_of_sanguination);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetActionTarget())
            return false;

        return !eventInfo.GetActionTarget()->GetSpellHistory()->HasCooldown(326808) && !eventInfo.GetActionTarget()->HasAura(326809) && eventInfo.GetActionTarget()->HealthBelowPct(35); // ID - 326809 Satiated
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();
        if (Unit* target = eventInfo.GetActionTarget())
            if (!target->GetSpellHistory()->HasCooldown(326808) && !target->HasAura(326809))
            {
                target->CastSpell(target, 326808, true); // Trigger spell(326808) Rune of Sanguination.Chance = 101
                target->GetSpellHistory()->AddCooldown(326808, 0, 60s);
            }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_dk_rune_of_sanguination::CheckProc);
        OnProc += AuraProcFn(spell_dk_rune_of_sanguination::HandleProc);
    }
};

void AddSC_deathknight_spell_scripts()
{
    new spell_dk_advantage_t10_4p();
    new spell_dk_anti_magic_barrier();
    RegisterSpellScript(spell_dk_anti_magic_shell_self);
    new spell_dk_army_periodic_taunt();
    new spell_dk_army_transform();
    RegisterSpellScript(spell_dk_blood_boil);
    RegisterSpellScript(spell_dk_blood_plague);    
    new spell_dk_blood_charges();
    new spell_dk_blood_gorged();
    new spell_dk_blood_mirror();
    new spell_dk_breath_of_sindragosa();
    RegisterSpellScript(spell_dk_bone_shield);
    RegisterSpellAndAuraScriptPair(spell_dk_dark_transformation_form, aura_spell_dk_dark_transformation);
    new spell_dk_death_and_decay();
    RegisterSpellScript(spell_dk_death_coil);
    new spell_dk_death_gate();
    RegisterSpellScript(spell_dk_death_grip_initial);
    new spell_dk_death_pact();
    new spell_dk_death_siphon();
    new spell_dk_death_strike();
    new spell_dk_desecrated_ground();
    RegisterSpellScript(spell_dk_festering_strike);
    new spell_dk_frozen_pulse();
    RegisterSpellScript(spell_dk_ghoul_explode);
    new spell_dk_glyph_of_deaths_embrace();
    new spell_dk_glyph_of_runic_power();
    new spell_dk_gorefiends_grasp();
    RegisterSpellScript(spell_dk_howling_blast);
    RegisterSpellScript(spell_dk_howling_blast_aoe);
    new spell_dk_icebound_fortitude();
    RegisterSpellScript(spell_dk_marrowrend);
    RegisterSpellScript(spell_dk_outbreak);
    RegisterSpellScript(aura_dk_outbreak_periodic);
    new spell_dk_pet_geist_transform();
    new spell_dk_pet_skeleton_transform();
	RegisterSpellAndAuraScriptPair(spell_dk_pillar_of_frost, aura_dk_pillar_of_frost);
    new spell_dk_plague_leech();
    new spell_dk_purgatory();
    new spell_dk_purgatory_absorb();
    new spell_dk_raise_dead();
    RegisterSpellScript(spell_dk_remorseless_winter_damage);
    RegisterSpellScript(aura_dk_soul_reaper);
    new spell_dk_vampiric_blood();
    RegisterSpellScript(spell_dk_will_of_the_necropolis);
    RegisterSpellScript(spell_dk_glacial_advance);
    RegisterSpellScript(spell_dk_epidemic);
    RegisterSpellScript(spell_dk_epidemic_aoe);
    RegisterSpellScript(aura_dk_virulent_plague);
    RegisterSpellScript(spell_dk_scourge_strike);
    RegisterSpellScript(aura_dk_defile);
    RegisterAreaTriggerAI(at_dk_defile);
    RegisterSpellScript(spell_dk_blighted_rune_weapon);
    RegisterAreaTriggerAI(at_dk_decomposing_aura);
    RegisterSpellScript(spell_dk_heart_strike);
    RegisterSpellScript(spell_dk_blodd_dancing_rune_weapon);
	RegisterSpellScript(aura_dk_permafrost);
    RegisterSpellScript(aura_gathering_storm);
    RegisterSpellScript(spell_dk_frostscythe);
	RegisterSpellScript(aura_festering_wound);
	RegisterCreatureAI(npc_dk_bloodworm);
	RegisterSpellScript(spell_dk_apocalypse);
	RegisterSpellScript(spell_dk_death_and_decay_damage);
	RegisterSpellScript(aura_dk_army_of_the_damned);
	RegisterSpellScript(aura_dk_unholy_freenzy);
	RegisterSpellScript(aura_dk_inexorable_assault);
	RegisterSpellScript(aura_dk_inexorable_assault_aura);
	RegisterSpellScript(aura_dk_rime);
	RegisterSpellScript(aura_dk_cold_heart);
	RegisterSpellScript(spell_dk_chains_of_ice);
	RegisterSpellScript(aura_dk_avalance);
	RegisterSpellAndAuraScriptPair(spell_dk_tombstone, aura_dk_tombstone_aura);
	RegisterSpellScript(aura_dk_mark_of_blood);
	RegisterSpellScript(spell_dk_bonestorm);
	RegisterSpellScript(spell_dk_bonestorm_damage);
	RegisterSpellScript(aura_dk_hemostatis);
	RegisterSpellScript(aura_dk_hemostatis_aura);
	RegisterSpellScript(spell_dk_necrotic_strike);
	RegisterSpellScript(spell_dk_virulent_plage_damage);
	RegisterSpellScript(spell_dk_reanimation);
	RegisterSpellScript(spell_dk_remorseless_winter);
	RegisterSpellScript(aura_dk_frozen_center);
	RegisterSpellAndAuraScriptPair(spell_dk_death_chain, aura_dk_death_chain);
	RegisterSpellScript(aura_dk_delirium);
	RegisterSpellScript(aura_dk_wandering_plague);
	RegisterSpellScript(spell_dk_wandering_plague_selector);
	RegisterSpellScript(aura_dk_pandemic);
	RegisterSpellScript(spell_dk_pandemic_damage);
	RegisterSpellScript(spell_dk_obliterate_main_hand);
	RegisterSpellScript(spell_dk_obliterate_off_hand);
	RegisterSpellScript(aura_dk_frost_fever_proc);
	RegisterSpellScript(aura_dk_icecap);
	RegisterSpellScript(spell_frost_strike_main_hand);
	RegisterSpellScript(spell_dk_frost_strike_off_hand);
    RegisterSpellScript(aura_dk_obliteration);
    RegisterSpellScript(aura_dk_obliteration_proc);
    RegisterSpellScript(aura_dk_killing_machine);
    RegisterSpellScript(spell_dk_chill_streak);
    RegisterSpellScript(spell_dk_chill_streak_missiles);
    RegisterSpellScript(spell_dk_chill_streak_selector);
    RegisterSpellScript(spell_dk_glacial_advance_damage);
    RegisterSpellScript(spell_dk_frostwyrm_fury);
    RegisterSpellScript(aura_dk_crimson_scourge);
    RegisterSpellScript(spell_dk_claw);
    RegisterSpellScript(aura_dk_sudden_doom);
    RegisterSpellScript(aura_dk_grip_of_the_dead_tick);
    RegisterSpellAndAuraScriptPair(spell_dk_dancing_rune_weapon, aura_dk_dancing_rune_weapon);
    RegisterSpellScript(spell_dk_corpse_exploder);
    RegisterSpellScript(aura_dk_all_will_serve);
    RegisterSpellScript(aura_dk_dark_simulacrum);
    RegisterSpellScript(aura_dk_icy_talons);
    RegisterSpellScript(spell_dk_zombie_explosion);    
    RegisterSpellScript(spell_dk_decomposing_aura_selector);    
    RegisterSpellScript(spell_dk_chill_streak_damage);
    RegisterSpellScript(spell_dk_rune_of_sanguination);

    // NPCs
	RegisterCreatureAI(npc_pet_dk_ghoul);
	RegisterCreatureAI(npc_pet_dk_zombie);

    // AreaTrigger
	RegisterAreaTriggerAI(at_dk_death_and_decay);
	RegisterAreaTriggerAI(at_dk_necrotic_aura);
	RegisterAreaTriggerAI(at_dk_heartstop_aura);
	RegisterAreaTriggerAI(at_dk_antimagic_zone);
    RegisterAreaTriggerAI(at_dk_frostwyrm);

    // Playerscript
    new dk_playerscript();
}
