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
* Scripts for spells with SPELLFAMILY_HUNTER, SPELLFAMILY_PET and SPELLFAMILY_GENERIC spells used by hunter players.
* Ordered alphabetically using scriptname.
* Scriptnames of files in this file should be prefixed with "spell_hun_".
*/

#include "AreaTrigger.h"
#include "AreaTriggerAI.h"
#include "Cell.h"
#include "CellImpl.h"
#include "Creature.h"
#include "GridNotifiers.h"
#include "GridNotifiersImpl.h"
#include "MotionMaster.h"
#include "ObjectAccessor.h"
#include "Pet.h"
#include "PetPackets.h"
#include "PhasingHandler.h"
#include "Player.h"
#include "ScriptMgr.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"
#include "SpellHistory.h"
#include "SpellMgr.h"
#include "TemporarySummon.h"
#include "ThreatManager.h"
#include "Unit.h"
#include "Log.h"

enum HunterSpells
{
    SPELL_HUNTER_A_MURDER_OF_CROWS_1                = 131894,
    SPELL_HUNTER_A_MURDER_OF_CROWS_2                = 206505,
    SPELL_HUNTER_A_MURDER_OF_CROWS_DAMAGE           = 131900,
    SPELL_HUNTER_AIMED_SHOT                         = 19434,
    SPELL_HUNTER_ANIMAL_INSTINCTS                   = 204315,
    SPELL_HUNTER_ANIMAL_INSTINCTS_CHEETAH           = 204324,
    SPELL_HUNTER_ANIMAL_INSTINCTS_MONGOOSE          = 204333,
    SPELL_HUNTER_ANIMAL_INSTINCTS_RAPTOR            = 204321,
    SPELL_HUNTER_ARCANE_SHOT                        = 185358,
    SPELL_HUNTER_ASPECT_OF_THE_CHEETAH_EFFECT_2     = 186258,
    SPELL_HUNTER_ASPECT_OF_THE_EAGLE                = 186289,
    SPELL_HUNTER_AURA_SHOOTING                      = 224729,
    SPELL_HUNTER_AUTO_SHOT                          = 75,
    SPELL_HUNTER_BARRAGE                            = 120360,
    SPELL_HUNTER_BASIC_ATTACK_COST_MODIFIER         = 62762,
    SPELL_HUNTER_BEAST_CLEAVE_AURA                  = 115939,
    SPELL_HUNTER_BEAST_CLEAVE_DAMAGE                = 118459,
    SPELL_HUNTER_BEAST_CLEAVE_PROC                  = 118455,
    SPELL_HUNTER_BESTIAL_WRATH                      = 19574,
    SPELL_HUNTER_BLACK_ARROW                        = 194599,
    SPELL_HUNTER_BLINK_STRIKES                      = 130392,
    SPELL_HUNTER_BLINK_STRIKES_TELEPORT             = 130393,
    SPELL_HUNTER_CAMOUFLAGE                         = 199483,
    SPELL_HUNTER_COBRA_SHOT                         = 193455,
    SPELL_HUNTER_DIRE_BEAST_GENERIC                 = 120679,
    SPELL_HUNTER_BARBED_SHOT                        = 217200,
    SPELL_HUNTER_BARBED_SHOT_REGENERATION           = 246152,
    SPELL_HUNTER_DIRE_FRENZY_DAMAGE                 = 217207,
    SPELL_HUNTER_DISENGAGE                          = 781,
    SPELL_HUNTER_EXHILARATION                       = 109304,
    SPELL_HUNTER_EXHILARATION_PET                   = 128594,
    SPELL_HUNTER_EXHILARATION_PET_AURA              = 231546,
    SPELL_HUNTER_EXPLOSIVE_SHOT                     = 212431,
    SPELL_HUNTER_EXPLOSIVE_SHOT_DAMAGE              = 212680,
    SPELL_HUNTER_EXPLOSIVE_SHOT_DETONATE            = 212679,
    SPELL_HUNTER_FLANKING_STRIKE                    = 202800,
    SPELL_HUNTER_FLANKING_STRIKE_PROC               = 204740,
    SPELL_HUNTER_FLANKING_STRIKE_PROC_UP            = 206933,
    SPELL_HUNTER_FRENZY_STACKS                      = 19615,
    SPELL_HUNTER_HARPOON                            = 190925,
    SPELL_HUNTER_HARPOON_ROOT                       = 190927,
    SPELL_HUNTER_HUNTERS_MARK                       = 185987,
    SPELL_HUNTER_HUNTERS_MARK_AURA                  = 185365, //This one is the graphics (The arrow effect)
    SPELL_HUNTER_HUNTERS_MARK_AURA_2                = 185743, //This one is enabling "Marked Shot"
    SPELL_HUNTER_IMPROVED_MEND_PET                  = 24406,
    SPELL_HUNTER_INTIMIDATION_STUN                  = 24394,
    SPELL_HUNTER_INVIGORATION_TRIGGERED             = 53398,
    SPELL_HUNTER_KILL_COMMAND                       = 34026,
    SPELL_HUNTER_KILL_COMMAND_CHARGE                = 118171,
    SPELL_HUNTER_KILL_COMMAND_TRIGGER               = 83381,
    SPELL_HUNTER_LACERATE                           = 185855,
    SPELL_HUNTER_LONE_WOLF                          = 155228,
    SPELL_HUNTER_MARKED_SHOT                        = 185901,
    SPELL_HUNTER_MARKED_SHOT_DAMAGE                 = 212621,
    SPELL_HUNTER_MARKING_TARGETS                    = 223138,
    SPELL_HUNTER_MASTERS_CALL_TRIGGERED             = 62305,
    SPELL_HUNTER_MISDIRECTION                       = 34477,
    SPELL_HUNTER_MISDIRECTION_PROC                  = 35079,
    SPELL_HUNTER_MONGOOSE_BITE                      = 259387,
    SPELL_HUNTER_MONGOOSE_FURY                      = 259388,
    SPELL_HUNTER_MULTISHOT                          = 2643,
    SPELL_HUNTER_PET_HEART_OF_THE_PHOENIX           = 55709,
    SPELL_HUNTER_PET_HEART_OF_THE_PHOENIX_DEBUFF    = 55711,
    SPELL_HUNTER_PET_HEART_OF_THE_PHOENIX_TRIGGERED = 54114,
    SPELL_HUNTER_POSTHAST                           = 109215,
    SPELL_HUNTER_POSTHAST_SPEED                     = 118922,
    SPELL_HUNTER_RANGERS_NET_INCREASE_SPEED         = 206755,
    SPELL_HUNTER_RAPTOR_STRIKE                      = 186270,
    SPELL_HUNTER_SENTINEL                           = 206817,
    SPELL_HUNTER_SERPENT_STING                      = 87935,
    SPELL_HUNTER_SERPENT_STING_DAMAGE               = 118253,
    SPELL_HUNTER_SPIKED_COLLAR                      = 53184,
    SPELL_HUNTER_STEADY_FOCUS                       = 193533,
    SPELL_HUNTER_STEADY_FOCUS_BUFF                  = 193534,
    SPELL_HUNTER_STICKY_BOMB_PROC                   = 191244,
    SPELL_HUNTER_THOWING_AXES_DAMAGE                = 200167,
    SPELL_HUNTER_TRAILBLAZER                        = 199921,
    SPELL_HUNTER_TRAILBLAZER_BUFF                   = 231390,
    SPELL_HUNTER_VULNERABLE                         = 187131,
    SPELL_HUNTER_WILD_CALL_AURA                     = 185791,
    SPELL_HUNTER_VIPER_VENOM_AURA                   = 268552,
    SPELL_HUNTER_SERPENT_STING_SURVIVAL             = 259491,
    SPELL_HUNTER_MANGOOSE_BITE                      = 259387,
    SPELL_HUNTER_KILLER_INSTINCT                    = 273887,
    SPELL_HUNTER_MASTER_MARKSMAN_TRIGGER            = 269576,
    SPELL_HUNTER_CAREFUL_AIM                        = 260228,
	SPELL_HUNTER_HIDRAS_BITE						= 260241,
    SPELL_HUNTER_EXPLOSIVE_TRAP                     = 236777,
	SPELL_HUNTER_TURTLE_PACIFY                      = 205769,
	SPELL_HUNTER_ASPECT_OF_THE_TURTLE				= 186265,
	SPELL_HUNTER_ROAR_OF_SACRIFICE_CHARGE			= 278454,
	SPELL_HUNTER_ROAR_OF_SACRIFICE					= 53480,
	SPELL_HUNTER_ROAR_OF_SACRIFICE_DAMAGE			= 67481,
	SPELL_HUNTER_FEIGN_DEATH						= 5384,
	SPELL_HUNTER_SURVIVAL_TATICS_TALENT				= 202746,
	SPELL_HUNTER_SURVIVAL_TATICS					= 202748,
    SPELL_HUNTER_AIMED_SHOT_BONUS                   = 236641,
    SPELL_HUNTER_PRECISE_SHOTS                      = 260242,
    SPELL_HUNTER_CALL_PET_1                         = 883,
    SPELL_HUNTER_CALL_PET_2                         = 83242,
    SPELL_HUNTER_CALL_PET_3                         = 83243,
    SPELL_HUNTER_CALL_PET_4                         = 83244,
    SPELL_HUNTER_CALL_PET_5                         = 83245,
    SPELL_HUNTER_LONE_WOLF_AURA                     = 164273,
    SPELL_HUNTER_STEADY_SHOT                        = 56641,
    SPELL_HUNTER_STEADY_SHOT_ENERGIZE               = 77443,
    SPELL_HUNTER_RAPID_FIRE_ENERGIZE                = 263585,
    SPELL_HUNTER_STAMPEDE_BEAR                      = 201591,
    SPELL_HUNTER_STAMPEDE_BIRD                      = 201610,
    SPELL_HUNTER_STAMPEDE_DAMAGE                    = 201594,
    SPELL_HUNTER_FEROCITY_PRIMAL_RAGE               = 264667,
    SPELL_HUNTER_TENACITY_SURVIVAL_OF_THE_FITTEST   = 264735,
    SPELL_HUNTER_CUNNING_MASTER_CALL                = 53271,
    SPELL_HUNTER_FRENZY                             = 272790,
    SPELL_HUNTER_PET_COMMAND                        = 272651,
    SPELL_HUNTER_OVERRIDE_COMMAND_DEMON             = 119904, //Aura necesary for cast Pet Command
    SPELL_HUNTER_SPIDER_STING_SILENCE               = 202933,
    SPELL_HUNTER_DOUBLE_TAP                         = 260402,
    SPELL_HUNTER_LOCK_AND_LOAD                      = 194594,
    SPELL_HUNTER_MASTER_MARKSMAN                    = 260309,
    SPELL_HUNTER_MARK_ENERGIZE                      = 259558,
    SPELL_HUNTER_STOMP_AURA                         = 199530,
    SPELL_HUNTER_STOMP_DAMAGE                       = 201754,
    SPELL_HUNTER_FLARE_DISPEL                       = 132951,
    SPELL_HUNTER_TIP_OF_THE_SPEAR                   = 260285,
    SPELL_HUNTER_BLOODSEEKER                        = 260248,
    SPELL_HUNTER_BLOODSEEKER_DOT                    = 259277,
    SPELL_HUNTER_PREDATOR                           = 260249,
    SPELL_HUNTER_THRILL_OF_THE_HUNT_TRIGGER         = 257946,
    SPELL_HUNTER_THRILL_OF_THE_HUNT                 = 257944,
    SPELL_HUNTER_TRICK_SHOT_AURA                    = 257621,
    SPELL_HUNTER_TRICK_SHOT_PROC                    = 257622,
    SPELL_HUNTER_DIAMOND_ICE                        = 203340,
    SPELL_HUNTER_DIAMOND_ICE_AURA                   = 203337,
    SPELL_HUNTER_COORDINATED_ASSAULT                = 266779,
    SPELL_HUNTER_WILDFIRE_BOMB_EXPLODE              = 265157,
    SPELL_HUNTER_WILDFIRE_BOMB_DOT                  = 269747,
    SPELL_HUNTER_WILDFIRE_INFUSION                  = 271014,
    SPELL_HUNTER_SHRAPNEL_BOMB                      = 270335,
    SPELL_HUNTER_SHRAPNEL_BOMB_MISSILE              = 270336,
    SPELL_HUNTER_SHRAPNEL_BOMB_EXPLODE              = 270338,
    SPELL_HUNTER_SHRAPNEL_BOMB_DOT                  = 270339,
    SPELL_HUNTER_PHEROMONE_BOMB                     = 270323,
    SPELL_HUNTER_PHEROMONE_BOMB_MISSILE             = 270327,
    SPELL_HUNTER_PHEROMONE_BOMB_EXPLODE             = 270329,
    SPELL_HUNTER_PHEROMONE_BOMB_DOT                 = 270332,
    SPELL_HUNTER_VOLATILE_BOMB                      = 271045,
    SPELL_HUNTER_VOLATILE_BOMB_MISSILE              = 271047,
    SPELL_HUNTER_VOLATILE_BOMB_EXPLODE              = 271048,
    SPELL_HUNTER_VOLATILE_BOMB_DOT                  = 271049,
    SPELL_HUNTER_VIOLENT_REACTION                   = 260231,
    SPELL_HUNTER_BUTCHERY                           = 212436,
    SPELL_HUNTER_INTERNAL_BLEEDING                  = 270343,
    SPELL_HUNTER_MASTERY_SPIRIT_BOND                = 263135,
    SPELL_HUNTER_WILDFIRE_BOMB                      = 259495,
    SPELL_HUNTER_VENOMOUS_BITE                      = 257891,
    SPELL_HUNTER_THE_BEAST_WITHIN                   = 212668,
    SPELL_HUNTER_THE_BEAST_WITHIN_BUFF              = 212704,
    SPELL_HUNTER_DIRE_BEAST_HAWK_FADE               = 208679,
    SPELL_HUNTER_DIRE_BEAST_HAWK_SUMMON             = 208819,
    SPELL_HUNTER_DIRE_BEAST_HAWK_ATTACK             = 208684,
    SPELL_HUNTER_WILD_PROTECTOR_AT                  = 204358,
    SPELL_HUNTER_WILD_PROTECTOR_BUFF                = 204205,
    SPELL_HUNTER_SERRATED_JAWS                      = 272717,
    SPELL_HUNTER_SERRATED_JAWS_ENERGIZE             = 272726,
    SPELL_HUNTER_RAPID_RELOAD                       = 278530,
    SPELL_HUNTER_RAPID_RELOAD_DAMAGE                = 278565,
    SPELL_HUNTER_ASPECT_OF_THE_WILD                 = 193530,
    SPELL_HUNTER_ASPECT_OF_THE_CHEETAH              = 186257,
    SPELL_HUNTER_WILDFIRE_INFUSION_PHEROMONE        = 271015,
    SPELL_HUNTER_WILDFIRE_INFUSION_SHRAPNEL         = 271020,
    SPELL_HUNTER_WILDFIRE_INFUSIN_VOLATILE          = 271050,
    SPELL_HUNTER_STEELTRAP_AT                       = 162496,
    SPELL_HUNTER_STEELTRAP_STUN                     = 162480,
    SPELL_HUNTER_STEELTRAP_BLEED                    = 162487,
    SPELL_HUNTER_CARVE                              = 187708,
    SPELL_HUNTER_BIRDS_OF_PREY                      = 260331,
    SPELL_HUNTER_UP_CLOSE_AND_PERSONAL_BUFF         = 279593,
    SPELL_HUNTER_HAZE_OF_RAGE_POWER                 = 273262,
    SPELL_HUNTER_HAZE_OF_RAGE_BUFF                  = 273264,
    SPELL_HUNTER_PRIMAL_INSTINCTS_POWER             = 279806,
    SPELL_HUNTER_PRIMAL_INSTINCTS_BUFF              = 279810,
    SPELL_HUNTER_BURSTING_SHOT                      = 186387,
    SPELL_HUNTER_COUNTER_SHOT                       = 147362,
    SPELL_HUNTER_CONCUSSIVE_SHOT                    = 5116,
    SPELL_HUNTER_RAPID_FIRE_DAMAGE                  = 257045,
    SPELL_HUNTER_MULTISHOT_RANK                     = 257620,
    SPELL_HUNTER_STEADY_AIM_BUFF                    = 277959,
    SPELL_HUNTER_LATENT_POISON_POWER                = 273283,
    SPELL_HUNTER_LATENT_POISON_DEBUFF               = 273286,
    SPELL_HUNTER_LATENT_POISON_DAMAGE               = 273289,
};

enum AncientHysteriaSpells
{
    SPELL_MAGE_TEMPORAL_DISPLACEMENT                = 80354,
    SPELL_SHAMAN_EXHAUSTION                         = 57723,
    SPELL_SHAMAN_SATED                              = 57724,
    SPELL_HUNTER_INSANITY                           = 95809
};

enum DireBeastSpells
{
    DIRE_BEAST_DREAD_WASTES                         = 126216,
    DIRE_BEAST_DUNGEONS                             = 132764,
    DIRE_BEAST_EASTERN_KINGDOMS                     = 122804,
    DIRE_BEAST_JADE_FOREST                          = 121118,
    DIRE_BEAST_KALIMDOR                             = 122802,
    DIRE_BEAST_KRASARANG_WILDS                      = 122809,
    DIRE_BEAST_KUN_LAI_SUMMIT                       = 126214,
    DIRE_BEAST_NORTHREND                            = 122807,
    DIRE_BEAST_OUTLAND                              = 122806,
    DIRE_BEAST_TOWNLONG_STEPPES                     = 126215,
    DIRE_BEAST_VALE_OF_THE_ETERNAL_BLOSSOM          = 126213,
    DIRE_BEAST_VALLEY_OF_THE_FOUR_WINDS             = 122811,
};

// Harpoon - 190925
class spell_hun_harpoon : public SpellScriptLoader
{
public:
    spell_hun_harpoon() : SpellScriptLoader("spell_hun_harpoon") { }

    class spell_hun_harpoon_SpellScript : public SpellScript
    {
        enum Used_Spell {
            TERMS_OF_ENGAGEMENT = 265895,
            TERMS_OF_ENGAGEMENT_POWER = 265898,
        };
        PrepareSpellScript(spell_hun_harpoon_SpellScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_HUNTER_HARPOON) ||
                !sSpellMgr->GetSpellInfo(SPELL_HUNTER_HARPOON_ROOT))
                return false;
            return true;
        }

        void CastHarpoon()
        {
            Player* player = GetCaster()->ToPlayer();
            Unit* target = GetExplTargetUnit();

            if (!player || !target)
                return;

            player->CastSpell(target, SPELL_HUNTER_HARPOON_ROOT, true);
        }

        void HandleDummy(SpellEffIndex /*effIndex*/)
        {
            Player* player = GetCaster()->ToPlayer();
            Unit* target = GetExplTargetUnit();

            if (!player || !target)
                return;

            WorldLocation pTarget = target->GetWorldLocation();

            float speedXY, speedZ;
            speedZ = 1.8f;
            speedXY = player->GetExactDist2d(&pTarget) * 10.0f / speedZ;
            player->GetMotionMaster()->MoveJump(pTarget, speedXY, speedZ, EVENT_JUMP);
            if (player && player->HasAura(TERMS_OF_ENGAGEMENT)) {
                player->CastSpell(player, TERMS_OF_ENGAGEMENT_POWER, true);
            }
        }

        void HandleAfterCast()
        {
            if (Player* player = GetCaster()->ToPlayer())
            {
                if (player->HasSpell(SPELL_HUNTER_POSTHAST))
                    player->CastSpell(player, SPELL_HUNTER_POSTHAST_SPEED, true);
            }
        }

        void Register() override
        {
            OnCast += SpellCastFn(spell_hun_harpoon_SpellScript::CastHarpoon);
            OnEffectHitTarget += SpellEffectFn(spell_hun_harpoon_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            AfterCast += SpellCastFn(spell_hun_harpoon_SpellScript::HandleAfterCast);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_hun_harpoon_SpellScript();
    }
};

// Snake Hunter - 201078
class spell_hun_snake_hunter : public SpellScriptLoader
{
public:
    spell_hun_snake_hunter() : SpellScriptLoader("spell_hun_snake_hunter") { }

    class spell_hun_snake_hunter_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_hun_snake_hunter_SpellScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_HUNTER_MONGOOSE_BITE))
                return false;
            return true;
        }

        void HandleDummy(SpellEffIndex /*effIndex*/)
        {
            Player* player = GetCaster()->ToPlayer();

            if (!player)
                return;

            player->GetSpellHistory()->ResetCharges(sSpellMgr->GetSpellInfo(SPELL_HUNTER_MONGOOSE_BITE)->ChargeCategoryId);
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_hun_snake_hunter_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_hun_snake_hunter_SpellScript();
    }
};

// Way of the Mok'nathal - 201082
class spell_hun_way_of_the_moknathal : public SpellScriptLoader
{
public:
    spell_hun_way_of_the_moknathal() : SpellScriptLoader("spell_hun_way_of_the_moknathal") {}

    class spell_hun_way_of_the_moknathal_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_hun_way_of_the_moknathal_AuraScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_HUNTER_RAPTOR_STRIKE))
                return false;
            return true;
        }

        bool CheckProc(ProcEventInfo& eventInfo)
        {
            if (eventInfo.GetSpellInfo()->Id == SPELL_HUNTER_RAPTOR_STRIKE)
                return true;
            return false;
        }

        void Register() override
        {
            DoCheckProc += AuraCheckProcFn(spell_hun_way_of_the_moknathal_AuraScript::CheckProc);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_hun_way_of_the_moknathal_AuraScript();
    }
};

//Master Marksman 260309 Last Update 8.0.1 28153
class spell_hun_master_marksman : public SpellScriptLoader
{
public:
    spell_hun_master_marksman() : SpellScriptLoader("spell_hun_master_marksman") {}

    class spell_hun_master_marksman_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_hun_master_marksman_AuraScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_HUNTER_MASTER_MARKSMAN))
                return false;
            return true;
        }

        bool CheckProc(ProcEventInfo& eventInfo)
        {
            if (eventInfo.GetSpellInfo()->Id == SPELL_HUNTER_AIMED_SHOT)
                return true;
            return false;
        }

        void Register() override
        {
            DoCheckProc += AuraCheckProcFn(spell_hun_master_marksman_AuraScript::CheckProc);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_hun_master_marksman_AuraScript();
    }
};

//259387  Mongoose Bite Last Update 8.0.1 Build 28153
class spell_hun_mongoose_bite : public SpellScriptLoader
{
public:
    spell_hun_mongoose_bite() : SpellScriptLoader("spell_hun_mongoose_bite") { }

    class spell_hun_mongoose_bite_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_hun_mongoose_bite_SpellScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_HUNTER_MONGOOSE_BITE))
                return false;
            return true;
        }

        void HandleHit()
        {
            if (Unit* caster = GetCaster())
            {
                caster->RemoveAura(SPELL_HUNTER_UP_CLOSE_AND_PERSONAL_BUFF);

                if (Unit* target = GetHitUnit())
                {
                    if (Aura* aura = target->GetAura(SPELL_HUNTER_LATENT_POISON_DEBUFF, caster->GetGUID()))
                    {
                        if (AuraEffect* aurEff = caster->GetAuraEffect(SPELL_HUNTER_LATENT_POISON_POWER, EFFECT_0))
                        {
                            caster->CastCustomSpell(SPELL_HUNTER_LATENT_POISON_DAMAGE, SPELLVALUE_BASE_POINT0, aurEff->GetAmount() * aura->GetStackAmount(), target, true);
                            target->RemoveAura(SPELL_HUNTER_LATENT_POISON_DEBUFF, caster->GetGUID());
                        }
                    }
                }
            }                
        }

        void ApplyBuff()
        {
            int32 dur = 0;
            if (Aura* aur = GetCaster()->GetAura(SPELL_HUNTER_MONGOOSE_FURY))
                dur = aur->GetDuration();

            GetCaster()->CastSpell(GetCaster(), SPELL_HUNTER_MONGOOSE_FURY, true);

            if (Aura* aur = GetCaster()->GetAura(SPELL_HUNTER_MONGOOSE_FURY))
                if (dur)
                    aur->SetDuration(dur);
        }

        void Register() override
        {
            OnHit += SpellHitFn(spell_hun_mongoose_bite_SpellScript::HandleHit);
            AfterHit += SpellHitFn(spell_hun_mongoose_bite_SpellScript::ApplyBuff);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_hun_mongoose_bite_SpellScript();
    }
};

// 90355 - Ancient Hysteria
class spell_hun_ancient_hysteria : public SpellScriptLoader
{
public:
    spell_hun_ancient_hysteria() : SpellScriptLoader("spell_hun_ancient_hysteria") { }

    class spell_hun_ancient_hysteria_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_hun_ancient_hysteria_SpellScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_HUNTER_INSANITY)
                || !sSpellMgr->GetSpellInfo(SPELL_MAGE_TEMPORAL_DISPLACEMENT)
                || !sSpellMgr->GetSpellInfo(SPELL_SHAMAN_EXHAUSTION)
                || !sSpellMgr->GetSpellInfo(SPELL_SHAMAN_SATED))
                return false;
            return true;
        }

        void RemoveInvalidTargets(std::list<WorldObject*>& targets)
        {
            targets.remove_if(Trinity::UnitAuraCheck(true, SPELL_HUNTER_INSANITY));
            targets.remove_if(Trinity::UnitAuraCheck(true, SPELL_MAGE_TEMPORAL_DISPLACEMENT));
            targets.remove_if(Trinity::UnitAuraCheck(true, SPELL_SHAMAN_EXHAUSTION));
            targets.remove_if(Trinity::UnitAuraCheck(true, SPELL_SHAMAN_SATED));
        }

        void ApplyDebuff()
        {
            if (Unit* target = GetHitUnit())
                target->CastSpell(target, SPELL_HUNTER_INSANITY, true);
        }

        void Register() override
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_hun_ancient_hysteria_SpellScript::RemoveInvalidTargets, EFFECT_ALL, TARGET_UNIT_CASTER_AREA_RAID);
            AfterHit += SpellHitFn(spell_hun_ancient_hysteria_SpellScript::ApplyDebuff);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_hun_ancient_hysteria_SpellScript();
    }
};

// 53412 - Invigoration
class spell_hun_invigoration : public SpellScriptLoader
{
public:
    spell_hun_invigoration() : SpellScriptLoader("spell_hun_invigoration") { }

    class spell_hun_invigoration_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_hun_invigoration_SpellScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_HUNTER_INVIGORATION_TRIGGERED))
                return false;
            return true;
        }

        void HandleScriptEffect(SpellEffIndex /*effIndex*/)
        {
            if (Unit* unitTarget = GetHitUnit())
                if (AuraEffect* aurEff = unitTarget->GetDummyAuraEffect(SPELLFAMILY_HUNTER, 3487, 0))
                    if (roll_chance_i(aurEff->GetAmount()))
                        unitTarget->CastSpell(unitTarget, SPELL_HUNTER_INVIGORATION_TRIGGERED, true);
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_hun_invigoration_SpellScript::HandleScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_hun_invigoration_SpellScript();
    }
};

// 53271 - Masters Call
class spell_hun_masters_call : public SpellScriptLoader
{
public:
    spell_hun_masters_call() : SpellScriptLoader("spell_hun_masters_call") { }

    class spell_hun_masters_call_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_hun_masters_call_SpellScript);

        bool Validate(SpellInfo const* spellInfo) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_HUNTER_MASTERS_CALL_TRIGGERED) ||
                !sSpellMgr->GetSpellInfo(spellInfo->GetEffect(EFFECT_0).CalcValue()))
                return false;
            return true;
        }

        SpellCastResult CheckIfPetInLOS()
        {
            Unit* target = GetExplTargetUnit();

            if (target == nullptr)
                return SPELL_FAILED_DONT_REPORT;

            if (Unit* pet = GetCaster())
            {
                if (pet->GetOwner())
                {
                    if (Player* player = pet->GetOwner()->ToPlayer())
                    {
                        float x, y, z;
                        pet->GetPosition(x, y, z);

                        if (!pet->IsWithinDist(player, 40.0f, true))
                            return SPELL_FAILED_OUT_OF_RANGE;

                        if (pet->HasAuraType(SPELL_AURA_MOD_STUN) || pet->HasAuraType(SPELL_AURA_MOD_CONFUSE) || pet->HasAuraType(SPELL_AURA_MOD_SILENCE) ||
                            pet->HasAuraType(SPELL_AURA_MOD_FEAR) || pet->HasAuraType(SPELL_AURA_MOD_FEAR_2))
                            return SPELL_FAILED_CANT_DO_THAT_RIGHT_NOW;

                        if (player->IsWithinLOS(x, y, z))
                            return SPELL_CAST_OK;
                    }
                }
            }
            return SPELL_FAILED_LINE_OF_SIGHT;
        }

        void HandleDummy(SpellEffIndex /*effIndex*/)
        {
            if (Unit* ally = GetHitUnit())
            {
                if (Unit* caster = GetCaster())
                {
                    ally->RemoveMovementImpairingAuras(true);
                    TriggerCastFlags castMask = TriggerCastFlags(TRIGGERED_FULL_MASK & ~TRIGGERED_IGNORE_CASTER_AURASTATE);
                    caster->CastSpell(ally, GetEffectValue(), castMask);
                }
            }
        }

        void HandleScriptEffect(SpellEffIndex /*effIndex*/)
        {
            if (Unit* target = GetHitUnit())
            {
                target->RemoveMovementImpairingAuras(true);  
                TriggerCastFlags castMask = TriggerCastFlags(TRIGGERED_FULL_MASK & ~TRIGGERED_IGNORE_CASTER_AURASTATE);
                target->CastSpell(target, SPELL_HUNTER_MASTERS_CALL_TRIGGERED, castMask);
            }
        }

        void Register() override
        {
            OnCheckCast += SpellCheckCastFn(spell_hun_masters_call_SpellScript::CheckIfPetInLOS);
            OnEffectHitTarget += SpellEffectFn(spell_hun_masters_call_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            OnEffectHitTarget += SpellEffectFn(spell_hun_masters_call_SpellScript::HandleScriptEffect, EFFECT_1, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_hun_masters_call_SpellScript();
    }
};

// 34477 - Misdirection
class spell_hun_misdirection : public SpellScriptLoader
{
public:
    spell_hun_misdirection() : SpellScriptLoader("spell_hun_misdirection") { }

    class spell_hun_misdirection_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_hun_misdirection_SpellScript);

        void HandleDummy(SpellEffIndex /*effIndex*/)
        {
            GetCaster()->CastSpell(GetCaster(), SPELL_HUNTER_MISDIRECTION_PROC, true);
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_hun_misdirection_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_REDIRECT_THREAT);
        }
    };

    class spell_hun_misdirection_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_hun_misdirection_AuraScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            return ValidateSpellInfo({ SPELL_HUNTER_MISDIRECTION_PROC });
        }

        void OnRemove(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
        {
            if (Unit* caster = aurEff->GetCaster())
                if (caster->HasAura(SPELL_HUNTER_MISDIRECTION_PROC))
                    caster->RemoveAurasDueToSpell(SPELL_HUNTER_MISDIRECTION_PROC);
        }

        void Register() override
        {
            AfterEffectRemove += AuraEffectRemoveFn(spell_hun_misdirection_AuraScript::OnRemove, EFFECT_1, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_hun_misdirection_AuraScript();
    }
};

// 35079 - Misdirection (Proc)
class spell_hun_misdirection_proc : public SpellScriptLoader
{
public:
    spell_hun_misdirection_proc() : SpellScriptLoader("spell_hun_misdirection_proc") { }

    class spell_hun_misdirection_proc_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_hun_misdirection_proc_AuraScript);

        void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            GetTarget()->GetThreatManager().UnregisterRedirectThreat(GetId());
        }

        void Register() override
        {
            AfterEffectRemove += AuraEffectRemoveFn(spell_hun_misdirection_proc_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_hun_misdirection_proc_AuraScript();
    }
};

uint32 callPetSpellIdBySlot[5] =
{
    SPELL_HUNTER_CALL_PET_1,
    SPELL_HUNTER_CALL_PET_2,
    SPELL_HUNTER_CALL_PET_3,
    SPELL_HUNTER_CALL_PET_4,
    SPELL_HUNTER_CALL_PET_5
};

// 1515 - Tame Beast
class spell_hun_tame_beast : public SpellScriptLoader
{
    public:
        spell_hun_tame_beast() : SpellScriptLoader("spell_hun_tame_beast") { }

        class spell_hun_tame_beast_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_hun_tame_beast_SpellScript);

            enum eCreature
            {
                NPC_CHIMAERON = 43296
            };

           //SpellCastResult SendTameFailResult(PetTameFailureReason reason)
           //{
           //    Player * player = GetCaster()->ToPlayer();
           //    if (!player)
           //        return SPELL_FAILED_DONT_REPORT;
           //
           //    player->SendPetTameFailure(reason);
           //
           //    return SPELL_FAILED_DONT_REPORT;
           //}

            SpellCastResult CheckCast()
            {
               //Player* player = GetCaster()->ToPlayer();
               //
               //if(!player)
               //    return SPELL_FAILED_DONT_REPORT;
               //
               //if (player->GetClass() != CLASS_HUNTER)
               //    return SendTameFailResult(PET_TAME_FAILURE_CANNOT_TAME_CREATURES);
               //
               //if (!GetExplTargetUnit())
               //    return SPELL_FAILED_BAD_IMPLICIT_TARGETS;
               //
               //if (!player->GetFirstUnusedActivePetSlot())
               //    return SendTameFailResult(PET_TAME_FAILURE_TOO_MANY_PETS);
               //
               //if (Optional<uint8> slot = player->GetFirstUnusedActivePetSlot())
               //    if (!player->HasSpell(callPetSpellIdBySlot[*slot]))
               //        return SendTameFailResult(PET_TAME_FAILURE_SLOT_LOCKED);
               //
               //if (Creature* target = GetExplTargetUnit()->ToCreature())
               //{
               //    if (target->GetEffectiveLevel() > player->GetLevel())
               //        return SendTameFailResult(PET_TAME_FAILURE_TOO_HIGH_LEVEL);
               //
               //    if (!target->GetCreatureTemplate()->IsTameable(player))
               //        return SendTameFailResult(PET_TAME_FAILURE_CANNOT_TAME_EXOTIC);
               //
               //    if (!player->GetPetGUID().IsEmpty())
               //        return SendTameFailResult(PET_TAME_FAILURE_ACTIVE_SUMMON);
               //
               //    if (!player->GetCharmGUID().IsEmpty())
               //        return SendTameFailResult(PET_TAME_FAILURE_CREATURE_CONTROLLED);
               //
               //    // Chimaeron can be tamed but only at 20%
               //    if (target->GetEntry() == NPC_CHIMAERON && target->GetHealthPct() > 20.0f)
               //    {
               //        SetCustomCastResultMessage(SPELL_CUSTOM_ERROR_CHIMAERON_TOO_CALM_TO_TAME);
               //        return SPELL_FAILED_CUSTOM_ERROR;
               //    }
               //}
               //else
               //    return SendTameFailResult(PET_TAME_FAILURE_NOT_TAMEABLE);
               //
                return SPELL_CAST_OK;
            }

            void Register() override
            {
                OnCheckCast += SpellCheckCastFn(spell_hun_tame_beast_SpellScript::CheckCast);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_hun_tame_beast_SpellScript();
        }
};

// 53209 - chimera Shot
class spell_hun_chimera_shot : public SpellScriptLoader
{
public:
    spell_hun_chimera_shot() : SpellScriptLoader("spell_hun_chimera_shot") { }

    class spell_hun_chimera_shot_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_hun_chimera_shot_SpellScript);

        bool Load() override
        {
            return GetCaster()->GetTypeId() == TYPEID_PLAYER;
        }

        void HandleOnHit()
        {
            Unit* caster = GetCaster();
            Unit* target = GetHitUnit();
            if (urand(0, 1) == 1)
                caster->CastSpell(target, 171454, true);
            else
                caster->CastSpell(target, 171457, true);
        }

        void Register() override
        {
            OnHit += SpellHitFn(spell_hun_chimera_shot_SpellScript::HandleOnHit);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_hun_chimera_shot_SpellScript();
    }
};

// A Murder of Crows (Beast Mastery, Marksmanship) - 131894 and A Murder of Crows (Survival) - 206505
class spell_hun_a_murder_of_crows : public SpellScriptLoader
{
public:
    spell_hun_a_murder_of_crows() : SpellScriptLoader("spell_hun_a_murder_of_crows") { }

    class spell_hun_a_murder_of_crows_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_hun_a_murder_of_crows_AuraScript);

        void OnTick(const AuraEffect* aurEff)
        {
            if (Unit* target = GetTarget())
            {
                if (aurEff->GetTickNumber() > 15)
                    return;

                if (Unit* caster = GetCaster())
                {
                    if (Player* player = caster->ToPlayer())
                    {
                        player->CastSpell(target, SPELL_HUNTER_A_MURDER_OF_CROWS_DAMAGE, true);
                    }
                }
            }
        }

        void HandleAfterRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if (GetTargetApplication()->GetRemoveMode() != AURA_REMOVE_BY_DEATH)
                return;

            if (Unit* caster = GetCaster())
                if (SpellHistory* spellHistory = caster->GetSpellHistory())
                    spellHistory->ResetCooldown(SPELL_HUNTER_A_MURDER_OF_CROWS_1, true);           
        }

        void Register() override
        {
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_hun_a_murder_of_crows_AuraScript::OnTick, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
            AfterEffectRemove += AuraEffectRemoveFn(spell_hun_a_murder_of_crows_AuraScript::HandleAfterRemove, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_hun_a_murder_of_crows_AuraScript();
    }
};

// Barrage - 120361 Last Update 8.0.1 Build 28153
class spell_hun_barrage : public SpellScriptLoader
{
public:
    spell_hun_barrage() : SpellScriptLoader("spell_hun_barrage") { }

    class spell_hun_barrage_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_hun_barrage_SpellScript);

        void CheckLOS(std::list<WorldObject*>& targets)
        {
            if (targets.empty())
                return;

            Unit* caster = GetCaster();
            if (!caster)
                return;

            targets.remove_if([caster](WorldObject* objects) -> bool
            {
                if (!objects)
                    return true;

                if (!objects->IsWithinLOSInMap(caster))
                    return true;

                if (objects->ToUnit() && !caster->IsValidAttackTarget(objects->ToUnit()))
                    return true;

                return false;
            });
        }

        void Register() override
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_hun_barrage_SpellScript::CheckLOS, EFFECT_0, TARGET_UNIT_CONE_ENEMY_24);
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_hun_barrage_SpellScript::CheckLOS, EFFECT_1, TARGET_UNIT_CONE_ENEMY_24);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_hun_barrage_SpellScript();
    }
};

// Beast Cleave - 115939
// Called by Multi-Shot - 2643
class spell_hun_beast_cleave : public SpellScriptLoader
{
public:
    spell_hun_beast_cleave() : SpellScriptLoader("spell_hun_beast_cleave") { }

    class spell_hun_beast_cleave_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_hun_beast_cleave_SpellScript);

        void HandleAfterCast()
        {
            if (Player* player = GetCaster()->ToPlayer())
                if (player->HasAura(SPELL_HUNTER_BEAST_CLEAVE_AURA))
                    if (Pet* pet = player->GetPet())
                        player->CastSpell(pet, SPELL_HUNTER_BEAST_CLEAVE_PROC, true);
        }

        void Register() override
        {
            AfterCast += SpellCastFn(spell_hun_beast_cleave_SpellScript::HandleAfterCast);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_hun_beast_cleave_SpellScript();
    }
};

// Beast Cleave Proc - 118455
class spell_hun_beast_cleave_proc : public SpellScriptLoader
{
public:
    spell_hun_beast_cleave_proc() : SpellScriptLoader("spell_hun_beast_cleave_proc") { }

    class spell_hun_beast_cleave_proc_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_hun_beast_cleave_proc_AuraScript);

        void OnProc(AuraEffect* aurEff, ProcEventInfo& eventInfo)
        {
            PreventDefaultAction();

            if (!GetCaster())
                return;

            if (eventInfo.GetActor()->GetGUID() != GetTarget()->GetGUID())
                return;

            if (!eventInfo.GetDamageInfo())
                return;

            if (eventInfo.GetDamageInfo()->GetSpellInfo() && eventInfo.GetDamageInfo()->GetSpellInfo()->Id == SPELL_HUNTER_BEAST_CLEAVE_DAMAGE)
                return;

            if (Player* player = GetCaster()->ToPlayer())
            {
                if (GetTarget()->HasAura(aurEff->GetSpellInfo()->Id, player->GetGUID()))
                {
                    int32 bp = int32(eventInfo.GetDamageInfo()->GetDamage() * 0.75f);

                    GetTarget()->CastCustomSpell(GetTarget(), SPELL_HUNTER_BEAST_CLEAVE_DAMAGE, &bp, NULL, NULL, true);
                }
            }
        }

        void Register() override
        {
            OnEffectProc += AuraEffectProcFn(spell_hun_beast_cleave_proc_AuraScript::OnProc, EFFECT_0, SPELL_AURA_DUMMY);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_hun_beast_cleave_proc_AuraScript();
    }
};

// Dire Beast - 120679
class spell_hun_dire_beast : public SpellScriptLoader
{
public:
    spell_hun_dire_beast() : SpellScriptLoader("spell_hun_dire_beast") { }

    class spell_hun_dire_beast_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_hun_dire_beast_SpellScript);

        void HandleOnHit()
        {
            if (Player* player = GetCaster()->ToPlayer())
            {
                if (Unit* target = GetHitUnit())
                {
                    // Summon's skin is different function of Map or Zone ID
                    switch (player->GetZoneId())
                    {
                        case 5785: // The Jade Forest
                            player->CastSpell(target, DIRE_BEAST_JADE_FOREST, true);
                            break;
                        case 5805: // Valley of the Four Winds
                            player->CastSpell(target, DIRE_BEAST_VALLEY_OF_THE_FOUR_WINDS, true);
                            break;
                        case 5840: // Vale of Eternal Blossoms
                            player->CastSpell(target, DIRE_BEAST_VALE_OF_THE_ETERNAL_BLOSSOM, true);
                            break;
                        case 5841: // Kun-Lai Summit
                            player->CastSpell(target, DIRE_BEAST_KUN_LAI_SUMMIT, true);
                            break;
                        case 5842: // Townlong Steppes
                            player->CastSpell(target, DIRE_BEAST_TOWNLONG_STEPPES, true);
                            break;
                        case 6134: // Krasarang Wilds
                            player->CastSpell(target, DIRE_BEAST_KRASARANG_WILDS, true);
                            break;
                        case 6138: // Dread Wastes
                            player->CastSpell(target, DIRE_BEAST_DREAD_WASTES, true);
                            break;
                        default:
                        {
                            switch (player->GetMapId())
                            {
                            case 0: // Eastern Kingdoms
                                player->CastSpell(target, DIRE_BEAST_EASTERN_KINGDOMS, true);
                                break;
                            case 1: // Kalimdor
                                player->CastSpell(target, DIRE_BEAST_KALIMDOR, true);
                                break;
                            case 8: // Outland
                                player->CastSpell(target, DIRE_BEAST_OUTLAND, true);
                                break;
                            case 10: // Northrend
                                player->CastSpell(target, DIRE_BEAST_NORTHREND, true);
                                break;
                            default:
                                if (player->GetMap()->IsDungeon())
                                    player->CastSpell(target, DIRE_BEAST_DUNGEONS, true);
                                else // Default
                                    player->CastSpell(target, DIRE_BEAST_KALIMDOR, true);
                                break;
                            }
                            break;
                        }
                    }
                }
            }
        }

        void Register() override
        {
            OnHit += SpellHitFn(spell_hun_dire_beast_SpellScript::HandleOnHit);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_hun_dire_beast_SpellScript();
    }
};

// Kill Command - 34026
class spell_hun_kill_command : public SpellScriptLoader
{
public:
    spell_hun_kill_command() : SpellScriptLoader("spell_hun_kill_command") { }

    class spell_hun_kill_command_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_hun_kill_command_SpellScript);

        bool Validate(SpellInfo const* /*SpellEntry*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_HUNTER_KILL_COMMAND))
                return false;
            return true;
        }

        SpellCastResult CheckCastMeet()
        {
            if (!GetCaster()) return SPELL_CAST_OK;
            if (Player* player = GetCaster()->ToPlayer())
            {
                Pet* pet = player->GetPet();

                if (!pet || pet->isDead())
                    return SPELL_FAILED_NO_PET;

                Unit* petTarget = pet->GetVictim();
                if (!petTarget)
                    petTarget = GetExplTargetUnit();

                // pet has a target and target is within 50 yards and target is in line of sight
                if (!petTarget || !pet->IsWithinDist(petTarget, 50.f, true) || !petTarget->IsWithinLOSInMap(pet))
                    return SPELL_FAILED_DONT_REPORT;

                if (pet->HasAuraType(SPELL_AURA_MOD_STUN) || pet->HasAuraType(SPELL_AURA_MOD_CONFUSE) || pet->HasAuraType(SPELL_AURA_MOD_SILENCE) ||
                    pet->HasAuraType(SPELL_AURA_MOD_FEAR) || pet->HasAuraType(SPELL_AURA_MOD_FEAR_2))
                    return SPELL_FAILED_CANT_DO_THAT_RIGHT_NOW;
            }
            return SPELL_CAST_OK;
        }

        void HandleDummy(SpellEffIndex /*effIndex*/)
        {
            if (Unit* caster = GetCaster())
                if (Player* player = caster->ToPlayer())
                {
                    if (Pet* pet = player->GetPet())
                    {
                        Unit* petTarget = GetExplTargetUnit();
                        if (!petTarget)
                            petTarget = pet->GetVictim();

                        if (!petTarget)
                            return;

                        pet->CastSpell(petTarget, SPELL_HUNTER_KILL_COMMAND_TRIGGER, true);

                        if (pet->GetVictim())
                        {
                            pet->AttackStop();
                            pet->ToCreature()->AI()->AttackStart(petTarget);
                        }
                        else
                            pet->ToCreature()->AI()->AttackStart(petTarget);

                        pet->CastSpell(petTarget, SPELL_HUNTER_KILL_COMMAND_CHARGE, true);

                        ObjectGuid animalCompanionGuid = player->GetAnimalCompanion();
                        if (!animalCompanionGuid.IsEmpty() && animalCompanionGuid.IsPet())
                        {
                            if (Pet* animalCompanion = ObjectAccessor::GetPet(*player, animalCompanionGuid))
                            {
                                Unit* animalCompanionTarget = GetExplTargetUnit();
                                if (!animalCompanionTarget)
                                    animalCompanionTarget = pet->GetVictim();

                                if (!animalCompanionTarget)
                                    return;

                                animalCompanion->CastSpell(animalCompanionTarget, SPELL_HUNTER_KILL_COMMAND_TRIGGER, true);

                                if (animalCompanion->GetVictim())
                                {
                                    animalCompanion->AttackStop();
                                    animalCompanion->ToCreature()->AI()->AttackStart(animalCompanionTarget);
                                }
                                else
                                    animalCompanion->ToCreature()->AI()->AttackStart(animalCompanionTarget);

                                animalCompanion->CastSpell(animalCompanionTarget, SPELL_HUNTER_KILL_COMMAND_CHARGE, true);
                            }
                        }                        
                    }
                }
        }

        void Register() override
        {
            OnCheckCast += SpellCheckCastFn(spell_hun_kill_command_SpellScript::CheckCastMeet);
            OnEffectHit += SpellEffectFn(spell_hun_kill_command_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_hun_kill_command_SpellScript();
    }
};

// Kill Command - 259489
//Last Update 8.0.1 Build 28153
class spell_hun_sur_kill_command : public SpellScriptLoader
{
public:
    spell_hun_sur_kill_command() : SpellScriptLoader("spell_hun_sur_kill_command") { }

    class spell_hun_kill_command_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_hun_kill_command_SpellScript);

        SpellCastResult CheckCastMeet()
        {
            if (!GetCaster()) return SPELL_CAST_OK;
            if (Player* player = GetCaster()->ToPlayer())
            {
                Pet* pet = player->GetPet();

                if (!pet || pet->isDead())
                    return SPELL_FAILED_NO_PET;

                Unit* petTarget = pet->GetVictim();
                if (!petTarget)
                    petTarget = GetExplTargetUnit();

                // pet has a target and target is within 8 yards and target is in line of sight
                if (!petTarget || !pet->IsWithinDist(petTarget, 8.f, true) || !petTarget->IsWithinLOSInMap(pet))
                    return SPELL_FAILED_DONT_REPORT;

                if (pet->HasAuraType(SPELL_AURA_MOD_STUN) || pet->HasAuraType(SPELL_AURA_MOD_CONFUSE) || pet->HasAuraType(SPELL_AURA_MOD_SILENCE) ||
                    pet->HasAuraType(SPELL_AURA_MOD_FEAR) || pet->HasAuraType(SPELL_AURA_MOD_FEAR_2))
                    return SPELL_FAILED_CANT_DO_THAT_RIGHT_NOW;
            }
            return SPELL_CAST_OK;
        }

        void HandleDummy(SpellEffIndex /*effIndex*/)
        {
            if (!GetCaster()) return;
            if (Player* player = GetCaster()->ToPlayer())
            {
                if (Pet* pet = player->GetPet())
                {
                    Unit* petTarget = GetExplTargetUnit();
                    if (!petTarget)
                        petTarget = pet->GetVictim();

                    if (!petTarget)
                        return;

                    pet->CastSpell(petTarget, SPELL_HUNTER_KILL_COMMAND_TRIGGER, true);

                    if (pet->GetVictim())
                    {
                        pet->AttackStop();
                        pet->ToCreature()->AI()->AttackStart(petTarget);
                    }
                    else
                        pet->ToCreature()->AI()->AttackStart(petTarget);

                    pet->CastSpell(petTarget, SPELL_HUNTER_KILL_COMMAND_CHARGE, true);

                    if (player->HasAura(SPELL_HUNTER_BLOODSEEKER))
                    {                    
                        if (SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(SPELL_HUNTER_BLOODSEEKER_DOT))
                        {
                            int32 damage = 0;
                            //RAP * 0.1 * 4                    
                            damage = player->m_unitData->RangedAttackPower * 0.4 / (spellInfo->GetMaxDuration() / spellInfo->GetEffect(EFFECT_1).ApplyAuraPeriod);
                            
                            pet->CastCustomSpell(petTarget, SPELL_HUNTER_BLOODSEEKER_DOT, &damage, &damage, nullptr, true);                 
                        } 
                    }
                }
            }
        }

        void PreventSpear(SpellEffIndex effIndex)
        {
            if (!GetCaster()) return;
            if (!GetCaster()->HasAura(SPELL_HUNTER_TIP_OF_THE_SPEAR))
                PreventHitEffect(effIndex);
        }

        void HandleAfterHit()
        {
            if (GetCaster())
            {
                if (Player* player = GetCaster()->ToPlayer())
                {
                    if (Unit* target = GetHitUnit())
                    {
                        if (target->HasAura(SPELL_HUNTER_PHEROMONE_BOMB_DOT, player->GetGUID()))
                        {
                            if (SpellInfo const* pheromoneBomb = sSpellMgr->GetSpellInfo(SPELL_HUNTER_PHEROMONE_BOMB))
                                if (roll_chance_i(pheromoneBomb->GetEffect(EFFECT_1).BasePoints))
                                    player->GetSpellHistory()->RestoreCharge(GetSpellInfo()->ChargeCategoryId);
                            //Is 100% we don´t need calculate more
                            return;
                        }
                    }

                    uint8 coordinatedChance = 0;
                    if (player->HasAura(SPELL_HUNTER_COORDINATED_ASSAULT))
                        coordinatedChance = sSpellMgr->GetSpellInfo(SPELL_HUNTER_COORDINATED_ASSAULT)->GetEffect(EFFECT_3).BasePoints;

                    if (roll_chance_i(GetSpellInfo()->GetEffect(EFFECT_1).BasePoints + coordinatedChance))
                        player->GetSpellHistory()->RestoreCharge(GetSpellInfo()->ChargeCategoryId);
                }
            }
        }

        void Register() override
        {
            OnCheckCast += SpellCheckCastFn(spell_hun_kill_command_SpellScript::CheckCastMeet);
            OnEffectHit += SpellEffectFn(spell_hun_kill_command_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            AfterHit += SpellHitFn(spell_hun_kill_command_SpellScript::HandleAfterHit);
            OnEffectLaunch += SpellEffectFn(spell_hun_kill_command_SpellScript::PreventSpear, EFFECT_3, SPELL_EFFECT_TRIGGER_SPELL);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_hun_kill_command_SpellScript();
    }
};

// Kill Command (Damage) - 83381
class spell_hun_kill_command_proc : public SpellScriptLoader
{
public:
    spell_hun_kill_command_proc() : SpellScriptLoader("spell_hun_kill_command_proc") { }

    class spell_hun_kill_command_proc_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_hun_kill_command_proc_SpellScript);

		bool Validate(SpellInfo const* /*spellInfo*/) override
		{
			return ValidateSpellInfo({ SPELL_HUNTER_KILLER_INSTINCT, SPELL_HUNTER_SERRATED_JAWS });
		}

        void HandleDamage(SpellEffIndex /*effIndex*/)
        {
            Unit* caster = GetCaster();
			Unit* target = GetHitUnit();
            Unit* owner = nullptr;
            if (caster)
                owner = caster->GetOwner();
            if (!owner)
                owner = caster;
            if (!owner || !target || !caster)
                return;

            if (!owner->IsPlayer())
                return;

            //$bmMastery=$?s76657[${1+0.01*$76657m1}][${1}]
            //$lowNerf=${0.5+$min($pl,20)*0.025}
            //$damage=${$83381m1+($RAP*0.6)*$<bmMastery>*$<lowNerf>*(1+$@versadmg)}
            float rap = 0.6f * owner->m_unitData->RangedAttackPower;
            float lowNerf = 0.5f + std::min(int32(owner->GetLevel()), 20) * 0.025f;
            float damage = rap * lowNerf;
            AddPct(damage, owner->ToPlayer()->m_activePlayerData->Mastery);
            damage += GetHitDamage();

			if (owner->HasAura(SPELL_HUNTER_KILLER_INSTINCT) && target->HealthBelowPct(sSpellMgr->GetSpellInfo(SPELL_HUNTER_KILLER_INSTINCT)->GetEffect(EFFECT_1).BasePoints))
				damage += CalculatePct(damage, sSpellMgr->GetSpellInfo(SPELL_HUNTER_KILLER_INSTINCT)->GetEffect(EFFECT_0).BasePoints);

            // Serrated Jaws
            if (Aura* aura = owner->GetAura(SPELL_HUNTER_SERRATED_JAWS))
            {
                uint8 chance = sSpellMgr->GetSpellInfo(SPELL_HUNTER_SERRATED_JAWS)->GetEffect(EFFECT_2).BasePoints;
                if (roll_chance_i(chance))
                {
                    damage += aura->GetEffect(EFFECT_0)->GetAmount();
                    owner->CastCustomSpell(SPELL_HUNTER_SERRATED_JAWS_ENERGIZE, SPELLVALUE_BASE_POINT0, aura->GetEffect(EFFECT_1)->GetAmount(), caster, true);
                }
            }

            SetHitDamage(damage);
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_hun_kill_command_proc_SpellScript::HandleDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_hun_kill_command_proc_SpellScript();
    }
};

// Piercing Shot - 198670
//Last Update 8.0.1 Build 28153
class spell_hun_piercing_shot : public SpellScript
{
    PrepareSpellScript(spell_hun_piercing_shot);

    int32 m_ExtraSpellCost = 0;

    bool Load() override
    {
        m_ExtraSpellCost = std::min(GetCaster()->GetPower(POWER_FOCUS), 80);
        return true;
    }

    void HandleTakePower(SpellPowerCost& powerCost)
    {
        powerCost.Amount += m_ExtraSpellCost;
    }

    void CalcDamage(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        int32 damage = GetHitDamage();
        damage *= float(20 + m_ExtraSpellCost) / 100.f;

        SetHitDamage(damage);
    }

    void Register() override
    {
        OnTakePower += SpellOnTakePowerFn(spell_hun_piercing_shot::HandleTakePower);
        OnEffectHitTarget += SpellEffectFn(spell_hun_piercing_shot::CalcDamage, EFFECT_2, SPELL_EFFECT_NORMALIZED_WEAPON_DMG);
        OnEffectHitTarget += SpellEffectFn(spell_hun_piercing_shot::CalcDamage, EFFECT_4, SPELL_EFFECT_NORMALIZED_WEAPON_DMG);
    }
};

// Arcane Shot - 185358
class spell_hun_arcane_shot : public SpellScriptLoader
{
public:
    spell_hun_arcane_shot() : SpellScriptLoader("spell_hun_arcane_shot") { }

    class spell_hun_arcane_shot_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_hun_arcane_shot_SpellScript);

        void HandleOnHit()
        {
            Unit* caster = GetCaster();
            Unit* target = GetHitUnit();
            if (!caster || !target)
                return;

            if (caster->HasAura(SPELL_HUNTER_MARKING_TARGETS))
            {
                caster->CastSpell(target, SPELL_HUNTER_HUNTERS_MARK_AURA, true);
                caster->CastSpell(caster, SPELL_HUNTER_HUNTERS_MARK_AURA_2, true);
                caster->RemoveAurasDueToSpell(SPELL_HUNTER_MARKING_TARGETS);
            }

            if (caster->HasAura(SPELL_HUNTER_CAREFUL_AIM) && roll_chance_i(sSpellMgr->GetSpellInfo(SPELL_HUNTER_CAREFUL_AIM)->GetEffect(EFFECT_3).BasePoints))
            {
                int32 damage = GetHitDamage();
                if (target->HealthAbovePct(sSpellMgr->GetSpellInfo(SPELL_HUNTER_CAREFUL_AIM)->GetEffect(EFFECT_0).BasePoints) ||
                    target->HealthBelowPct(sSpellMgr->GetSpellInfo(SPELL_HUNTER_CAREFUL_AIM)->GetEffect(EFFECT_1).BasePoints))
                    damage += CalculatePct(damage, sSpellMgr->GetSpellInfo(SPELL_HUNTER_CAREFUL_AIM)->GetEffect(EFFECT_2).BasePoints);

                SetHitDamage(damage);
            }
        }

		void HandleAfterCast()
		{
			if (Unit* caster = GetCaster())
				if (caster->HasAura(SPELL_HUNTER_MASTER_MARKSMAN_TRIGGER))
					caster->RemoveAurasDueToSpell(SPELL_HUNTER_MASTER_MARKSMAN_TRIGGER);
		}

		void Register() override
        {
            OnHit += SpellHitFn(spell_hun_arcane_shot_SpellScript::HandleOnHit);
			AfterCast += SpellCastFn(spell_hun_arcane_shot_SpellScript::HandleAfterCast);
        }

    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_hun_arcane_shot_SpellScript();
    }
};

// Multi-Shot - 2643 Last Update 8.0.1 Build 28153
class spell_hun_multi_shot : public SpellScript
{
    PrepareSpellScript(spell_hun_multi_shot);

    void HandleOnHit()
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        if (caster->HasAura(SPELL_HUNTER_MARKING_TARGETS))
        {
            caster->CastSpell(caster, SPELL_HUNTER_HUNTERS_MARK_AURA_2, true);
            caster->RemoveAurasDueToSpell(SPELL_HUNTER_MARKING_TARGETS);

            caster->CastSpell(target, SPELL_HUNTER_HUNTERS_MARK_AURA, true);
        }

        caster->CastSpell(caster, SPELL_HUNTER_BEAST_CLEAVE_AURA, true);

        if (Aura* aura = caster->GetAura(SPELL_HUNTER_RAPID_RELOAD))
        {
            if (hitcounter == 4)
            {
                if (Unit* currentTarget = ObjectAccessor::GetUnit(*caster, caster->GetTarget()))
                    if (caster->IsValidAttackTarget(currentTarget))
                        caster->CastCustomSpell(SPELL_HUNTER_RAPID_RELOAD_DAMAGE, SPELLVALUE_BASE_POINT0, aura->GetEffect(EFFECT_0)->GetAmount(), currentTarget, true);

                caster->GetSpellHistory()->ModifyCooldown(SPELL_HUNTER_ASPECT_OF_THE_TURTLE, -1s);
                caster->GetSpellHistory()->ModifyCooldown(SPELL_HUNTER_ASPECT_OF_THE_WILD, -1s);
                caster->GetSpellHistory()->ModifyCooldown(SPELL_HUNTER_ASPECT_OF_THE_CHEETAH, -1s);
            }

            hitcounter++;
        }
    }

    void Register() override
    {
        OnHit += SpellHitFn(spell_hun_multi_shot::HandleOnHit);
    }

private:
    uint32 hitcounter = 0;
};

// Marked Shot - 185901
class spell_hun_marked_shot : public SpellScriptLoader
{
public:
    spell_hun_marked_shot() : SpellScriptLoader("spell_hun_marked_shot") { }

    class spell_hun_marked_shot_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_hun_marked_shot_SpellScript);

        void HandleOnCast()
        {
            if (Unit* caster = GetCaster())
            {
                std::list<Unit*> targetList;
                float radius = sSpellMgr->GetSpellInfo(SPELL_HUNTER_MARKED_SHOT)->GetEffect(EFFECT_0).CalcRadius(caster);

                caster->GetAttackableUnitListInRange(targetList, radius);

                if (!targetList.empty())
                {
                    for (auto itr : targetList)
                    {
                        if (itr->HasAura(SPELL_HUNTER_HUNTERS_MARK_AURA, caster->GetGUID()))
                        {
                            caster->CastSpell(itr, SPELL_HUNTER_MARKED_SHOT_DAMAGE, true);
                            caster->CastSpell(itr, SPELL_HUNTER_VULNERABLE, true);
                            caster->RemoveAura(SPELL_HUNTER_HUNTERS_MARK_AURA_2);
                        }
                    }
                }
            }
        }

        void Register() override
        {
            OnCast += SpellCastFn(spell_hun_marked_shot_SpellScript::HandleOnCast);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_hun_marked_shot_SpellScript();
    }
};

// Aspect of the Cheetah - 186257
class spell_hun_aspect_of_the_cheetah : public SpellScriptLoader
{
public:
    spell_hun_aspect_of_the_cheetah() : SpellScriptLoader("spell_hun_aspect_of_the_cheetah") { }

    class spell_hun_aspect_of_the_cheetah_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_hun_aspect_of_the_cheetah_AuraScript);

        void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            Unit* caster = GetCaster();
            if (!caster)
                return;

            if (GetTargetApplication()->GetRemoveMode() == AURA_REMOVE_BY_EXPIRE)
                caster->CastSpell(caster, SPELL_HUNTER_ASPECT_OF_THE_CHEETAH_EFFECT_2, true);
        }

        void Register() override
        {
            OnEffectRemove += AuraEffectRemoveFn(spell_hun_aspect_of_the_cheetah_AuraScript::HandleRemove, EFFECT_0, SPELL_AURA_MOD_INCREASE_SPEED, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_hun_aspect_of_the_cheetah_AuraScript();
    }
};

// Hunting Party - 212658
class spell_hun_hunting_party : public SpellScriptLoader
{
public:
    spell_hun_hunting_party() : SpellScriptLoader("spell_hun_hunting_party") { }

    class spell_hun_hunting_party_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_hun_hunting_party_AuraScript);

        void HandleProc(AuraEffect* aurEff, ProcEventInfo& /*procInfo*/)
        {
            Unit* caster = GetCaster();
            if (!caster)
                return;
            if (!caster->ToPlayer())
                return;

            caster->ToPlayer()->GetSpellHistory()->ModifyCooldown(SPELL_HUNTER_EXHILARATION, -aurEff->GetBaseAmount()*IN_MILLISECONDS);
        }

        void Register() override
        {
            OnEffectProc += AuraEffectProcFn(spell_hun_hunting_party_AuraScript::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_hun_hunting_party_AuraScript();
    }
};

// Hunter's Mark - 185987
class spell_hun_hunters_mark : public SpellScriptLoader
{
public:
    spell_hun_hunters_mark() : SpellScriptLoader("spell_hun_hunters_mark") { }

    class spell_hun_hunters_mark_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_hun_hunters_mark_AuraScript);

        bool CheckProc(ProcEventInfo& eventInfo)
        {
            if (eventInfo.GetSpellInfo()->Id == SPELL_HUNTER_AUTO_SHOT)
                return true;

            return false;
        }

        void Register() override
        {
            DoCheckProc += AuraCheckProcFn(spell_hun_hunters_mark_AuraScript::CheckProc);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_hun_hunters_mark_AuraScript();
    }
};

// Marking Targets - 223138
class spell_hun_marking_targets : public SpellScriptLoader
{
public:
    spell_hun_marking_targets() : SpellScriptLoader("spell_hun_marking_targets") { }

    class spell_hun_marking_targets_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_hun_marking_targets_AuraScript);

        bool CheckProc(ProcEventInfo& /*eventInfo*/)
        {
            // Called by Multi-shoot & Arcane Shot
            return false;
        }

        void Register() override
        {
            DoCheckProc += AuraCheckProcFn(spell_hun_marking_targets_AuraScript::CheckProc);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_hun_marking_targets_AuraScript();
    }
};

// Intimidation - 19577
class spell_hun_intimidation : public SpellScriptLoader
{
public:
    spell_hun_intimidation() : SpellScriptLoader("spell_hun_intimidation") {}

    class spell_hun_intimidation_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_hun_intimidation_AuraScript);

        void HandleProc(AuraEffect* /*aurEff*/, ProcEventInfo& eventInfo)
        {
            Unit* caster = eventInfo.GetDamageInfo()->GetAttacker();
            Unit* target = eventInfo.GetDamageInfo()->GetVictim();
            if (!caster || !target)
                return;

            caster->CastSpell(target, SPELL_HUNTER_INTIMIDATION_STUN, true);
        }

        void Register() override
        {
            OnEffectProc += AuraEffectProcFn(spell_hun_intimidation_AuraScript::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_hun_intimidation_AuraScript();
    }
};

// Killer Cobra - 199532
class spell_hun_killer_cobra : public SpellScriptLoader
{
public:
    spell_hun_killer_cobra() : SpellScriptLoader("spell_hun_killer_cobra") { }

    class spell_hun_killer_cobra_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_hun_killer_cobra_AuraScript);

        bool CheckProc(ProcEventInfo& eventInfo)
        {
            if (eventInfo.GetSpellInfo()->Id == SPELL_HUNTER_COBRA_SHOT)
                return true;

            return false;
        }

        void HandleProc(AuraEffect* /*aurEff*/, ProcEventInfo& /*eventInfo*/)
        {
            PreventDefaultAction();

            if (Unit* caster = GetCaster())
            {
                if (caster->HasAura(SPELL_HUNTER_BESTIAL_WRATH))
                {
                    if (caster->GetSpellHistory()->HasCooldown(SPELL_HUNTER_KILL_COMMAND))
                        caster->GetSpellHistory()->ResetCooldown(SPELL_HUNTER_KILL_COMMAND, true);
                }
            }
        }

        void Register() override
        {
            DoCheckProc += AuraCheckProcFn(spell_hun_killer_cobra_AuraScript::CheckProc);
            OnEffectProc += AuraEffectProcFn(spell_hun_killer_cobra_AuraScript::HandleProc, EFFECT_0, SPELL_AURA_PROC_TRIGGER_SPELL);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_hun_killer_cobra_AuraScript();
    }
};

// Disengage - 781
class spell_hun_disengage : public SpellScriptLoader
{
public:
    spell_hun_disengage() : SpellScriptLoader("spell_hun_disengage") { }

    class spell_hun_disengage_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_hun_disengage_SpellScript);

        void HandleAfterCast()
        {
            if (Player* player = GetCaster()->ToPlayer())
            {
                uint32 spec = player->GetSpecializationId();

                if (player->HasSpell(SPELL_HUNTER_POSTHAST))
                {
                    player->RemoveMovementImpairingAuras(true);
                    player->CastSpell(player, SPELL_HUNTER_POSTHAST_SPEED, true);
                }
            }
        }

        void Register() override
        {
            AfterCast += SpellCastFn(spell_hun_disengage_SpellScript::HandleAfterCast);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_hun_disengage_SpellScript();
    }
};

// Farstrider - 199523
class spell_hun_farstrider : public SpellScriptLoader
{
public:
    spell_hun_farstrider() : SpellScriptLoader("spell_hun_farstrider") { }

    class spell_hun_farstrider_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_hun_farstrider_AuraScript);

        bool CheckProc(ProcEventInfo& eventInfo)
        {
            if (eventInfo.GetHitMask() & PROC_HIT_CRITICAL)
                return true;

            return false;
        }

        void HandleProc(AuraEffect* /*aurEff*/, ProcEventInfo& /*eventInfo*/)
        {
            PreventDefaultAction();

            if (Player* player = GetCaster()->ToPlayer())
            {
                if (player->HasSpell(SPELL_HUNTER_DISENGAGE))
                    player->GetSpellHistory()->ResetCooldown(SPELL_HUNTER_DISENGAGE, true);

                if (player->HasSpell(SPELL_HUNTER_HARPOON))
                    player->GetSpellHistory()->ResetCooldown(SPELL_HUNTER_DISENGAGE, true);
            }
        }

        void Register() override
        {
            DoCheckProc += AuraCheckProcFn(spell_hun_farstrider_AuraScript::CheckProc);
            OnEffectProc += AuraEffectProcFn(spell_hun_farstrider_AuraScript::HandleProc, EFFECT_0, SPELL_AURA_PROC_TRIGGER_SPELL);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_hun_farstrider_AuraScript();
    }
};

// Throwing Axes - 200163
class spell_hun_throwing_axes : public SpellScript
{
    PrepareSpellScript(spell_hun_throwing_axes);

    void HandleOnCast()
    {
        Unit* caster = GetCaster();
        Unit* target = GetExplTargetUnit();
        if (!caster || !target)
            return;

        ObjectGuid targetGUID = target->GetGUID();
        uint8 throwCount = GetSpellInfo()->GetEffect(EFFECT_0).BasePoints;

        for (uint8 i = 0; i < throwCount; ++i)
        {
            caster->GetScheduler().Schedule(Milliseconds(500 * i), [targetGUID](TaskContext context)
            {
                if (Unit* caster = context.GetUnit())
                    if (Unit* target = ObjectAccessor::GetCreature(*caster, targetGUID))
                        caster->CastSpell(target, SPELL_HUNTER_THOWING_AXES_DAMAGE, false);
            });
        }
    }

    void Register() override
    {
        OnCast += SpellCastFn(spell_hun_throwing_axes::HandleOnCast);
    }
};

// Ranger's Net - 200108
class spell_hun_rangers_net : public SpellScriptLoader
{
public:
    spell_hun_rangers_net() : SpellScriptLoader("spell_hun_rangers_net") {}

    class spell_hun_rangers_net_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_hun_rangers_net_AuraScript);

        void HandleEffectRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            Unit* caster = GetCaster();

            caster->CastSpell(GetTarget(), SPELL_HUNTER_RANGERS_NET_INCREASE_SPEED, true);
        }

        void Register() override
        {
            AfterEffectRemove += AuraEffectRemoveFn(spell_hun_rangers_net_AuraScript::HandleEffectRemove, EFFECT_0, SPELL_AURA_MOD_ROOT, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_hun_rangers_net_AuraScript();
    }
};

// Sticky Bomb - 191241
class spell_hun_sticky_bomb : public SpellScriptLoader
{
public:
    spell_hun_sticky_bomb() : SpellScriptLoader("spell_hun_sticky_bomb") {}

    class spell_hun_sticky_bomb_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_hun_sticky_bomb_AuraScript);

        void HandleEffectRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            Unit* caster = GetCaster();

            caster->CastSpell(GetTarget(), SPELL_HUNTER_STICKY_BOMB_PROC, true);
        }

        void Register() override
        {
            AfterEffectRemove += AuraEffectRemoveFn(spell_hun_sticky_bomb_AuraScript::HandleEffectRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_hun_sticky_bomb_AuraScript();
    }
};

// Camouflage - 199483
class spell_hun_camouflage : public SpellScriptLoader
{
public:
    spell_hun_camouflage() : SpellScriptLoader("spell_hun_camouflage") { }

    class spell_hun_camouflage_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_hun_camouflage_AuraScript);

        void OnApply(AuraEffect const*, AuraEffectHandleModes)
        {
            if (GetCaster() && GetCaster()->IsPlayer())
                if (Unit* pet = GetCaster()->GetGuardianPet())
                    pet->CastSpell(pet, SPELL_HUNTER_CAMOUFLAGE, true);
        }

        void OnRemove(AuraEffect const*, AuraEffectHandleModes)
        {
            if (GetCaster() && GetCaster()->IsPlayer())
                if (Unit* pet = GetCaster()->GetGuardianPet())
                    pet->RemoveAurasDueToSpell(SPELL_HUNTER_CAMOUFLAGE);
        }

        void Register() override
        {
            AfterEffectApply += AuraEffectApplyFn(spell_hun_camouflage_AuraScript::OnApply, EFFECT_0, SPELL_AURA_MOD_STEALTH, AURA_EFFECT_HANDLE_REAL);
            OnEffectRemove += AuraEffectRemoveFn(spell_hun_camouflage_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_MOD_STEALTH, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_hun_camouflage_AuraScript();
    }
};

// Lock and Load - 194595
class spell_hun_lock_and_load : public SpellScriptLoader
{
public:
    spell_hun_lock_and_load() : SpellScriptLoader("spell_hun_lock_and_load") { }

    class spell_hun_lock_and_load_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_hun_lock_and_load_AuraScript);

        bool CheckProc(ProcEventInfo& eventInfo)
        {
            if (eventInfo.GetSpellInfo()->Id == SPELL_HUNTER_AUTO_SHOT)
                return true;

            return false;
        }

        void HandleProc(AuraEffect* /*aurEff*/, ProcEventInfo& /*eventInfo*/)
        {
            if (Player* player = GetCaster()->ToPlayer())
            {
                if (SpellCategoryEntry const* mongooseBite = sSpellCategoryStore.LookupEntry(1715))
                {
                    player->GetSpellHistory()->RestoreCharge(1715);
                    player->GetSpellHistory()->ForceSendSetSpellCharges(mongooseBite);
                }
            }
        }

        void Register() override
        {
            DoCheckProc += AuraCheckProcFn(spell_hun_lock_and_load_AuraScript::CheckProc);
            OnEffectProc += AuraEffectProcFn(spell_hun_lock_and_load_AuraScript::HandleProc, EFFECT_0, SPELL_AURA_PROC_TRIGGER_SPELL);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_hun_lock_and_load_AuraScript();
    }
};

// Sentinel - 206817
class spell_hun_sentinel : public SpellScriptLoader
{
public:
    spell_hun_sentinel() : SpellScriptLoader("spell_hun_sentinel") { }

    class spell_hun_sentinel_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_hun_sentinel_SpellScript);

        void HandleOnCast()
        {
            if (Unit* caster = GetCaster())
            {
                if (GetExplTargetUnit())
                {
                    std::list<Unit*> targetList;
                    float radius = sSpellMgr->GetSpellInfo(SPELL_HUNTER_SENTINEL)->GetEffect(EFFECT_0).CalcRadius(caster);
                    caster->GetAttackableUnitListInRange(targetList, radius);

                    if (!targetList.empty())
                    {
                        for (auto itr : targetList)
                        {
                            caster->CastSpell(itr, SPELL_HUNTER_HUNTERS_MARK_AURA, true);
                        }
                    }
                }
                caster->CastSpell(caster, SPELL_HUNTER_HUNTERS_MARK_AURA_2, true);
            }
        }

        void Register() override
        {
            OnCast += SpellCastFn(spell_hun_sentinel_SpellScript::HandleOnCast);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_hun_sentinel_SpellScript();
    }
};

// Barbed Shot - 217200
class spell_hun_barber_shot : public SpellScriptLoader
{
public:
    spell_hun_barber_shot() : SpellScriptLoader("spell_hun_barber_shot") { }

    class spell_hun_barber_shot_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_hun_barber_shot_SpellScript);

        void HandleOnCast()
        {
            if (Player* player = GetCaster()->ToPlayer())
            {
                if (Pet* pet = player->GetPet())
                {
                    player->CastSpell(pet, SPELL_HUNTER_FRENZY, true);

                    if(player->HasAura(SPELL_HUNTER_STOMP_AURA))
                        pet->CastSpell(pet, SPELL_HUNTER_STOMP_DAMAGE, true);
                }   

                if(SpellInfo const* spellinfo = sSpellMgr->GetSpellInfo(SPELL_HUNTER_BESTIAL_WRATH))
                    if (player->GetSpellHistory()->HasCooldown(spellinfo->Id))
                        player->GetSpellHistory()->ModifyCooldown(spellinfo->Id, -spellinfo->GetEffect(EFFECT_2).BasePoints * IN_MILLISECONDS);

                if (player->HasAura(SPELL_HUNTER_THRILL_OF_THE_HUNT))
                    player->CastSpell(player, SPELL_HUNTER_THRILL_OF_THE_HUNT_TRIGGER, true);

                player->CastSpell(player, SPELL_HUNTER_BARBED_SHOT_REGENERATION, true);
            }
        }

        void HandleAfterCast()
        {
            if (Player* player = GetCaster()->ToPlayer())
            {
                if (player->HasAura(SPELL_HUNTER_WILD_CALL_AURA))
                    player->RemoveAurasDueToSpell(SPELL_HUNTER_WILD_CALL_AURA);
            }
        }

        void Register() override
        {
            OnCast += SpellCastFn(spell_hun_barber_shot_SpellScript::HandleOnCast);
            AfterCast += SpellCastFn(spell_hun_barber_shot_SpellScript::HandleAfterCast);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_hun_barber_shot_SpellScript();
    }
};

// Flanking Strike - 202800
// Trigger for Animal Instincts - 204315
class spell_hun_flanking_strike : public SpellScriptLoader
{
public:
    spell_hun_flanking_strike() : SpellScriptLoader("spell_hun_flanking_strike") { }

    class spell_hun_flanking_strike_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_hun_flanking_strike_SpellScript);

        void HandleDummy(SpellEffIndex /*effIndex*/)
        {
            if (Player* player = GetCaster()->ToPlayer())
            {
                if (Unit* pet = GetCaster()->GetGuardianPet())
                {
                    if (!pet)
                        return;

                    Unit* target = GetExplTargetUnit();
                    if (!target)
                        return;

                    int32 dmg = GetHitDamage();

                    if (player->getAttackers().empty())
                    {
                        pet->ToCreature()->AI()->AttackStart(target);
                        pet->CastSpell(target, SPELL_HUNTER_FLANKING_STRIKE_PROC, true);
                        dmg *= 1.5f;
                    }
                    else
                    {
                        pet->ToCreature()->AI()->AttackStart(target);
                        pet->CastSpell(target, SPELL_HUNTER_FLANKING_STRIKE_PROC_UP, true);
                     //   pet->AddThreat(target, 400.0f);
                    }

                    dmg = player->SpellDamageBonusDone(target, GetSpellInfo(), dmg, SPELL_DIRECT_DAMAGE, GetEffectInfo(EFFECT_0));
                    dmg = target->SpellDamageBonusTaken(player, GetSpellInfo(), dmg, SPELL_DIRECT_DAMAGE);

                    SetHitDamage(dmg);
                }
            }
        }

        void HandleAfterCast()
        {
            Unit* caster = GetCaster();
            Unit* target = GetHitUnit();
            if (!caster || !target)
                return;

            if (caster->HasSpell(SPELL_HUNTER_ANIMAL_INSTINCTS))
            {
                uint32 roll = rand() % 4;

                if (roll == 3)
                    caster->GetSpellHistory()->ModifyCooldown(SPELL_HUNTER_FLANKING_STRIKE, -3000);
                if (roll == 2)
                    caster->GetSpellHistory()->ModifyCooldown(SPELL_HUNTER_MONGOOSE_BITE, -3000);
                else if (roll == 1)
                    caster->GetSpellHistory()->ModifyCooldown(SPELL_HUNTER_ASPECT_OF_THE_EAGLE, -3000);
                else if (roll == 0)
                    caster->GetSpellHistory()->ModifyCooldown(SPELL_HUNTER_HARPOON, -3000);
            }
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_hun_flanking_strike_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_WEAPON_PERCENT_DAMAGE);
            AfterCast += SpellCastFn(spell_hun_flanking_strike_SpellScript::HandleAfterCast);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_hun_flanking_strike_SpellScript();
    }
};

// Flanking Strike (Pet - Damage) - 204740
class spell_hun_flanking_strike_proc : public SpellScriptLoader
{
public:
    spell_hun_flanking_strike_proc() : SpellScriptLoader("spell_hun_flanking_strike_proc") { }

    class spell_hun_flanking_strike_proc_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_hun_flanking_strike_proc_SpellScript);

        void HandleDamage(SpellEffIndex /*effIndex*/)
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

            // (3.652 * (rap) * lowNerf * (1 + versability))
            int32 dmg = 3.652f * owner->m_unitData->RangedAttackPower;
            int32 lowNerf = std::min(int32(owner->GetLevel()), 20) * 0.05f;
            dmg *= lowNerf;

            dmg = caster->SpellDamageBonusDone(target, GetSpellInfo(), dmg, SPELL_DIRECT_DAMAGE, GetEffectInfo(EFFECT_0));
            dmg = target->SpellDamageBonusTaken(caster, GetSpellInfo(), dmg, SPELL_DIRECT_DAMAGE);

            SetHitDamage(dmg);
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_hun_flanking_strike_proc_SpellScript::HandleDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_hun_flanking_strike_proc_SpellScript();
    }
};

// Flanking Strike (Pet - Damage 50%) - 206933
class spell_hun_flanking_strike_proc_up : public SpellScriptLoader
{
public:
    spell_hun_flanking_strike_proc_up() : SpellScriptLoader("spell_hun_flanking_strike_proc_up") { }

    class spell_hun_flanking_strike_proc_up_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_hun_flanking_strike_proc_up_SpellScript);

        void HandleDamage(SpellEffIndex /*effIndex*/)
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

            // (3.652 * (rap) * lowNerf * (1 + versability))
            int32 dmg = 3.652f * owner->m_unitData->RangedAttackPower;
            int32 lowNerf = std::min(int32(owner->GetLevel()), 20) * 0.05f;
            dmg *= lowNerf;
            dmg *= 1.5f;

            dmg = caster->SpellDamageBonusDone(target, GetSpellInfo(), dmg, SPELL_DIRECT_DAMAGE, GetEffectInfo(EFFECT_0));
            dmg = target->SpellDamageBonusTaken(caster, GetSpellInfo(), dmg, SPELL_DIRECT_DAMAGE);

            SetHitDamage(dmg);
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_hun_flanking_strike_proc_up_SpellScript::HandleDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_hun_flanking_strike_proc_up_SpellScript();
    }
};

// Mortal Wounds - 201075
class spell_hun_mortal_wounds : public SpellScriptLoader
{
public:
    spell_hun_mortal_wounds() : SpellScriptLoader("spell_hun_mortal_wounds") { }

    class spell_hun_mortal_wounds_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_hun_mortal_wounds_AuraScript);

        bool CheckProc(ProcEventInfo& eventInfo)
        {
            if ((eventInfo.GetHitMask() & PROC_HIT_NONE) && eventInfo.GetSpellInfo()->Id == SPELL_HUNTER_LACERATE)
                return true;

            return false;
        }

        void HandleProc(AuraEffect* /*aurEff*/, ProcEventInfo& /*eventInfo*/)
        {
            PreventDefaultAction();

            if (Player* player = GetCaster()->ToPlayer())
            {
                int32 chargeCatId = sSpellMgr->GetSpellInfo(SPELL_HUNTER_MONGOOSE_BITE)->ChargeCategoryId;

                if (SpellCategoryEntry const* mongooseBite = sSpellCategoryStore.LookupEntry(chargeCatId))
                {
                    player->GetSpellHistory()->RestoreCharge(chargeCatId);
                    player->GetSpellHistory()->ForceSendSetSpellCharges(mongooseBite);
                }
            }
        }

        void Register() override
        {
            DoCheckProc += AuraCheckProcFn(spell_hun_mortal_wounds_AuraScript::CheckProc);
            OnEffectProc += AuraEffectProcFn(spell_hun_mortal_wounds_AuraScript::HandleProc, EFFECT_0, SPELL_AURA_PROC_TRIGGER_SPELL);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_hun_mortal_wounds_AuraScript();
    }
};

// Raptor Strike - 186270
class spell_hun_raptor_strike : public SpellScriptLoader
{
public:
    spell_hun_raptor_strike() : SpellScriptLoader("spell_hun_raptor_strike") { }

    class spell_hun_raptor_strike_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_hun_raptor_strike_SpellScript);

        void HandleOnHit()
        {
            Unit* caster = GetCaster();
            Unit* target = GetHitUnit();
            if (!caster || !target)
                return;

            if (Aura* aur = caster->GetAura(260286))
                aur->ModStackAmount(-1);

            if (caster->HasSpell(SPELL_HUNTER_SERPENT_STING))
                caster->CastSpell(target, SPELL_HUNTER_SERPENT_STING_DAMAGE, true);

            caster->RemoveAura(SPELL_HUNTER_UP_CLOSE_AND_PERSONAL_BUFF);

            if (Aura* aura = target->GetAura(SPELL_HUNTER_LATENT_POISON_DEBUFF, caster->GetGUID()))
            {                
                if (AuraEffect* aurEff = caster->GetAuraEffect(SPELL_HUNTER_LATENT_POISON_POWER, EFFECT_0))
                {
                    caster->CastCustomSpell(SPELL_HUNTER_LATENT_POISON_DAMAGE, SPELLVALUE_BASE_POINT0, aurEff->GetAmount() * aura->GetStackAmount(), target, true);
                    target->RemoveAura(SPELL_HUNTER_LATENT_POISON_DEBUFF, caster->GetGUID());
                }
            }
        }

        void Register() override
        {
            OnHit += SpellHitFn(spell_hun_raptor_strike_SpellScript::HandleOnHit);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_hun_raptor_strike_SpellScript();
    }
};

// 187708 - Carve
class spell_hun_carve : public SpellScript
{
    PrepareSpellScript(spell_hun_carve);

    void HandleOnHit()
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        if (caster->HasSpell(SPELL_HUNTER_SERPENT_STING))
            caster->CastSpell(target, SPELL_HUNTER_SERPENT_STING_DAMAGE, true);

        if (hitCount < 5)
        {
            caster->GetSpellHistory()->ReduceChargeCooldown(sSpellMgr->GetSpellInfo(SPELL_HUNTER_WILDFIRE_BOMB)->ChargeCategoryId, 1 * IN_MILLISECONDS);
            hitCount++;
        }
    }

    void Register() override
    {
        OnHit += SpellHitFn(spell_hun_carve::HandleOnHit);
    }

private:
    uint8 hitCount = 0;
};

// True Aim - 199527
class spell_hun_true_aim : public SpellScriptLoader
{
public:
    spell_hun_true_aim() : SpellScriptLoader("spell_hun_true_aim") { }

    class spell_hun_true_aim_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_hun_true_aim_AuraScript);

        bool CheckProc(ProcEventInfo& eventInfo)
        {
            if (eventInfo.GetSpellInfo()->Id == SPELL_HUNTER_AIMED_SHOT || eventInfo.GetSpellInfo()->Id == SPELL_HUNTER_ARCANE_SHOT)
                return true;

            return false;
        }

        void Register() override
        {
            DoCheckProc += AuraCheckProcFn(spell_hun_true_aim_AuraScript::CheckProc);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_hun_true_aim_AuraScript();
    }
};

// Explosive Shot - 212679
class spell_hun_explosive_shot_detonate : public SpellScript
{
    PrepareSpellScript(spell_hun_explosive_shot_detonate);

    void HandleDummy(SpellEffIndex /*effIndex*/)
    {
        if (AreaTrigger* at = GetCaster()->GetAreaTrigger(SPELL_HUNTER_EXPLOSIVE_SHOT))
        {
            GetCaster()->RemoveAurasDueToSpell(SPELL_HUNTER_EXPLOSIVE_SHOT);
            GetCaster()->CastSpell(at->GetPosition(), SPELL_HUNTER_EXPLOSIVE_SHOT_DAMAGE, true);
            at->Remove();
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_hun_explosive_shot_detonate::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

// Exhilaration - 109304
class spell_hun_exhilaration : public SpellScript
{
    PrepareSpellScript(spell_hun_exhilaration);

    void HandeHeal(SpellEffIndex /*effIndex*/)
    {
        if (Player* player = GetCaster()->ToPlayer())
            if (player->HasAura(SPELL_HUNTER_EXHILARATION_PET_AURA))
                if (Pet* pet = player->GetPet())
                    player->CastSpell(pet, SPELL_HUNTER_EXHILARATION_PET, true);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_hun_exhilaration::HandeHeal, EFFECT_0, SPELL_EFFECT_HEAL_PCT);
    }
};

// 194386
class aura_hun_volley : public AuraScript
{
    PrepareAuraScript(aura_hun_volley);

    bool CheckProc(ProcEventInfo& /*eventInfo*/)
    {
        return GetTarget()->GetPower(POWER_FOCUS) >= GetSpellInfo()->GetEffect(EFFECT_0).BasePoints;
    }

    void HandleProc(AuraEffect* /*aurEff*/, ProcEventInfo& /*eventInfo*/)
    {
        GetTarget()->ModifyPower(POWER_FOCUS, -GetSpellInfo()->GetEffect(EFFECT_0).BasePoints);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_hun_volley::CheckProc);
        OnEffectProc += AuraEffectProcFn(aura_hun_volley::HandleProc, EFFECT_0, SPELL_AURA_PROC_TRIGGER_SPELL);
    }
};

// 199921
class aura_trailblazer : public AuraScript
{
    PrepareAuraScript(aura_trailblazer);

    void EffectApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        RescheduleBuff();
    }

    void HandleProc(AuraEffect* /*aurEff*/, ProcEventInfo& /*eventInfo*/)
    {
        RescheduleBuff();
    }

	void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
	{
		if (Unit* caster = GetCaster())
			if (Aura* aura = caster->GetAura(SPELL_HUNTER_TRAILBLAZER_BUFF))
				caster->RemoveAura(SPELL_HUNTER_TRAILBLAZER_BUFF);
	}

    void RescheduleBuff()
    {
        Unit* target = GetTarget();
        target->RemoveAurasDueToSpell(SPELL_HUNTER_TRAILBLAZER_BUFF);
        target->GetScheduler().CancelGroup(SPELL_HUNTER_TRAILBLAZER);
        target->GetScheduler().Schedule(Milliseconds((int32)GetSpellInfo()->GetEffect(EFFECT_0).BasePoints), SPELL_HUNTER_TRAILBLAZER, [](TaskContext context)
        {
            GetContextUnit()->CastSpell(GetContextUnit(), SPELL_HUNTER_TRAILBLAZER_BUFF, true);
        });
    }


    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(aura_trailblazer::EffectApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        OnEffectProc += AuraEffectProcFn(aura_trailblazer::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
        OnEffectRemove += AuraEffectRemoveFn(aura_trailblazer::HandleRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

// Heart of the Phoenix (Pet) - 55709
class spell_hun_pet_heart_of_the_phoenix : public SpellScriptLoader
{
public:
    spell_hun_pet_heart_of_the_phoenix() : SpellScriptLoader("spell_hun_pet_heart_of_the_phoenix") { }

    class spell_hun_pet_heart_of_the_phoenix_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_hun_pet_heart_of_the_phoenix_SpellScript);

        bool Load() override
        {
            if (!GetCaster()->IsPet())
                return false;
            return true;
        }

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_HUNTER_PET_HEART_OF_THE_PHOENIX_TRIGGERED) || !sSpellMgr->GetSpellInfo(SPELL_HUNTER_PET_HEART_OF_THE_PHOENIX_DEBUFF))
                return false;
            return true;
        }

        void HandleScript(SpellEffIndex /*effIndex*/)
        {
            Unit* caster = GetCaster();
            if (Unit* owner = caster->GetOwner())
                if (!caster->HasAura(SPELL_HUNTER_PET_HEART_OF_THE_PHOENIX_DEBUFF))
                {
                    owner->CastCustomSpell(SPELL_HUNTER_PET_HEART_OF_THE_PHOENIX_TRIGGERED, SPELLVALUE_BASE_POINT0, 100, caster, true);
                    caster->CastSpell(caster, SPELL_HUNTER_PET_HEART_OF_THE_PHOENIX_DEBUFF, true);
                }
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_hun_pet_heart_of_the_phoenix_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_hun_pet_heart_of_the_phoenix_SpellScript();
    }
};

// Thunderstomp (Pet) - 63900
class spell_hun_pet_thunderstomp : public SpellScriptLoader
{
public:
    spell_hun_pet_thunderstomp() : SpellScriptLoader("spell_hun_pet_thunderstomp") { }

    class spell_hun_pet_thunderstomp_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_hun_pet_thunderstomp_SpellScript);

        void HandleDamage(SpellEffIndex /*effIndex*/)
        {
            Unit* caster = GetCaster();
            Unit* owner = GetCaster()->GetOwner();
            Unit* target = GetHitUnit();

            if (!owner || !target)
                return;

            int32 dmg = int32(1.5f * (owner->m_unitData->RangedAttackPower * 0.250f));

            dmg = caster->SpellDamageBonusDone(target, GetSpellInfo(), dmg, SPELL_DIRECT_DAMAGE, GetEffectInfo(EFFECT_0));
            dmg = target->SpellDamageBonusTaken(caster, GetSpellInfo(), dmg, SPELL_DIRECT_DAMAGE);

            SetHitDamage(dmg);
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_hun_pet_thunderstomp_SpellScript::HandleDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_hun_pet_thunderstomp_SpellScript();
    }
};

// Basic Attack + Blink Strikes
// Called by Smack - 49966, Bite - 17253, Claw - 16827
class spell_hun_pet_basic_attack : public SpellScriptLoader
{
public:
    spell_hun_pet_basic_attack() : SpellScriptLoader("spell_hun_pet_basic_attack") { }

    class spell_hun_pet_basic_attack_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_hun_pet_basic_attack_SpellScript);

        SpellCastResult CheckCastRange()
        {
            Unit* caster = GetCaster();

            if (caster == nullptr)
                return SPELL_FAILED_DONT_REPORT;

            Unit* owner = caster->GetOwner();

            if (owner == nullptr)
                return SPELL_FAILED_DONT_REPORT;

            Unit* target = GetExplTargetUnit();

            if (target == nullptr)
                return SPELL_FAILED_DONT_REPORT;

            if (owner->HasSpell(SPELL_HUNTER_BLINK_STRIKES))
            {
                if (owner->ToPlayer()->GetSpellHistory()->HasCooldown(SPELL_HUNTER_BLINK_STRIKES) && caster->GetDistance(target) > 10.0f)
                    return SPELL_FAILED_OUT_OF_RANGE;

                if ((caster->HasAuraType(SPELL_AURA_MOD_ROOT) || caster->HasAuraType(SPELL_AURA_MOD_STUN)) && caster->GetDistance(target) > 5.0f)
                    return SPELL_FAILED_ROOTED;

                if (!owner->ToPlayer()->GetSpellHistory()->HasCooldown(SPELL_HUNTER_BLINK_STRIKES) && target->IsWithinLOSInMap(caster) &&
                    caster->GetDistance(target) > 10.0f && caster->GetDistance(target) < 30.0f && /*!caster->IsInRoots() && */!caster->HasAuraType(SPELL_AURA_MOD_STUN))
                {
                    caster->CastSpell(target, SPELL_HUNTER_BLINK_STRIKES_TELEPORT, true);

                    if (caster->ToCreature()->AI() && caster->ToPet())
                    {
                        caster->ToPet()->ClearUnitState(UNIT_STATE_FOLLOW);
                        if (caster->ToPet()->GetVictim())
                            caster->ToPet()->AttackStop();
                        caster->GetMotionMaster()->Clear();
                        caster->ToPet()->GetCharmInfo()->SetIsCommandAttack(true);
                        caster->ToPet()->GetCharmInfo()->SetIsAtStay(false);
                        caster->ToPet()->GetCharmInfo()->SetIsReturning(false);
                        caster->ToPet()->GetCharmInfo()->SetIsFollowing(false);

                        caster->ToCreature()->AI()->AttackStart(target);
                    }

                    owner->ToPlayer()->GetSpellHistory()->AddCooldown(SPELL_HUNTER_BLINK_STRIKES, 0, std::chrono::seconds(20));
                }
            }
            return SPELL_CAST_OK;
        }

        void HandleDamage(SpellEffIndex /*effIndex*/)
        {
            if (Pet* pet = GetCaster()->ToPet())
            {
                if (Unit* owner = GetCaster()->GetOwner())
                {
                    Unit* target = GetHitUnit();
                    if (!target)
                        return;

                    // (1.5 * 1 * 1 * (Ranged attack power * 0.333) * (1 + $versadmg))
                    int32 dmg = (owner->m_unitData->RangedAttackPower * 0.333f);

                    SpellInfo const* CostModifier = sSpellMgr->GetSpellInfo(SPELL_HUNTER_BASIC_ATTACK_COST_MODIFIER);
                    SpellInfo const* SpikedCollar = sSpellMgr->GetSpellInfo(SPELL_HUNTER_SPIKED_COLLAR);

                    // Increases the damage done by your pet's Basic Attacks by 10%
                    if (pet->HasAura(SPELL_HUNTER_SPIKED_COLLAR) && SpikedCollar != nullptr)
                        AddPct(dmg, SpikedCollar->GetEffect(EFFECT_0).BasePoints);

                    // Deals 100% more damage and costs 100% more Focus when your pet has 50 or more Focus.
                    if (pet->GetPower(POWER_FOCUS) + 25 >= 50)
                    {
                        if (CostModifier != nullptr)
                            dmg += CalculatePct(dmg, CostModifier->GetEffect(EFFECT_1).BasePoints);
                        pet->EnergizeBySpell(pet, GetSpellInfo(), -25, POWER_FOCUS);
                    }

                  //  dmg *= pet->GetModifierValue(UNIT_MOD_DAMAGE_MAINHAND, TOTAL_PCT);

                    dmg = pet->SpellDamageBonusDone(target, GetSpellInfo(), dmg, SPELL_DIRECT_DAMAGE, GetEffectInfo(EFFECT_0));
                    dmg = target->SpellDamageBonusTaken(pet, GetSpellInfo(), dmg, SPELL_DIRECT_DAMAGE);

                    SetHitDamage(dmg);
                }
            }
        }

        void Register() override
        {
            OnCheckCast += SpellCheckCastFn(spell_hun_pet_basic_attack_SpellScript::CheckCastRange);
            OnEffectHitTarget += SpellEffectFn(spell_hun_pet_basic_attack_SpellScript::HandleDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_hun_pet_basic_attack_SpellScript();
    }
};

// Cobra Spit (Pet) - 206685
class spell_hun_pet_cobra_spit : public SpellScriptLoader
{
public:
    spell_hun_pet_cobra_spit() : SpellScriptLoader("spell_hun_pet_cobra_spit") { }

    class spell_hun_pet_cobra_spit_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_hun_pet_cobra_spit_SpellScript);

        void HandleDamage(SpellEffIndex /*effIndex*/)
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

            // (1 + AP * 0,2)
            int32 dmg = 1 + owner->m_unitData->RangedAttackPower * 0.2f;

            dmg = caster->SpellDamageBonusDone(target, GetSpellInfo(), dmg, SPELL_DIRECT_DAMAGE, GetEffectInfo(EFFECT_0));
            dmg = target->SpellDamageBonusTaken(caster, GetSpellInfo(), dmg, SPELL_DIRECT_DAMAGE);

            SetHitDamage(dmg);
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_hun_pet_cobra_spit_SpellScript::HandleDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_hun_pet_cobra_spit_SpellScript();
    }
};

// Dire Basilisk  - 105419
class npc_pet_hunter_dire_basilisk : public ScriptedAI
{
public:
    npc_pet_hunter_dire_basilisk(Creature* creature) : ScriptedAI(creature) {}

    void IsSummonedBy(WorldObject* owner) override
    {
        if (!owner)
            return;

        me->SetWalk(true);
        targetGUID = (owner->Variables.Exist("EXPLICIT_TARGET")) ? owner->Variables.GetValue<ObjectGuid>("EXPLICIT_TARGET") : ObjectGuid::Empty;
    }

    void UpdateAI(uint32 diff) override
    {
        for (uint8 i = MOVE_WALK; i < MAX_MOVE_TYPE; i++)
            me->SetSpeedRate((UnitMoveType)i, 0.2f);

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

// Flare - 1543
// AreaTriggerID - 510
class at_hun_flare : public AreaTriggerEntityScript
{
public:
    at_hun_flare() : AreaTriggerEntityScript("at_hun_flare") {}

    struct at_hun_flareAI : AreaTriggerAI
    {
        at_hun_flareAI(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger) { }

        enum eSpells
        {
            SPELL_ROGUE_STEALTH    = 1784,
            SPELL_ROGUE_SUBTERFUGE = 115191,
        };

        void OnUnitEnter(Unit* unit) override
        {
            if (!unit)
                return;

            if (Unit* caster = at->GetCaster())
            {
                if (caster->IsValidAttackTarget(unit))
                {
                    unit->AddAura(SPELL_HUNTER_FLARE_DISPEL, unit);
                    unit->RemoveAurasByType(SPELL_AURA_MOD_STEALTH);
                    unit->RemoveAurasByType(SPELL_AURA_MOD_INVISIBILITY);
                    if (unit->GetClass() == CLASS_ROGUE)
                    {
                        unit->RemoveAura(SPELL_ROGUE_SUBTERFUGE);
                        unit->RemoveAura(SPELL_ROGUE_STEALTH);
                    }
                }
            }
        }

        void OnUnitExit(Unit* unit) override
        {
            if (!unit)
                return;

            unit->RemoveAura(SPELL_HUNTER_FLARE_DISPEL);
        }
    };

    AreaTriggerAI* GetAI(AreaTrigger* areatrigger) const override
    {
        return new at_hun_flareAI(areatrigger);
    }
};

// Exposive Trap - 191433
// AreaTriggerID - 1613
class at_hun_explosive_trap : public AreaTriggerEntityScript
{
public:

    at_hun_explosive_trap() : AreaTriggerEntityScript("at_hun_explosive_trap") { }

    struct at_hun_explosive_trapAI : AreaTriggerAI
    {
        int32 timeInterval;

        enum UsedSpells
        {
            SPELL_HUNTER_EXPLOSIVE_TRAP_DAMAGE = 13812
        };

        at_hun_explosive_trapAI(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger)
        {
            timeInterval = 200;
        }

        void OnCreate() override
        {
            Unit* caster = at->GetCaster();

            if (!caster)
                return;

            if (!caster->ToPlayer())
                return;

            for (auto itr : at->GetInsideUnits())
            {
                Unit* target = ObjectAccessor::GetUnit(*caster, itr);
                if (!caster->IsFriendlyTo(target))
                {
                    if (Creature* tempSumm = caster->SummonCreature(WORLD_TRIGGER, at->GetPosition(), TEMPSUMMON_TIMED_DESPAWN, 200ms))
                    {
                        tempSumm->SetFaction(caster->GetFaction());
                        tempSumm->SetOwnerGUID(caster->GetGUID());
                        PhasingHandler::InheritPhaseShift(tempSumm, caster);
                        caster->CastSpell(tempSumm, SPELL_HUNTER_EXPLOSIVE_TRAP_DAMAGE, true);
                        at->Remove();
                    }
                }
            }
        }

        void OnUnitEnter(Unit* unit) override
        {
            Unit* caster = at->GetCaster();

            if (!caster || !unit)
                return;

            if (!caster->ToPlayer())
                return;

            if (!caster->IsFriendlyTo(unit))
            {
                if (Creature* tempSumm = caster->SummonCreature(WORLD_TRIGGER, at->GetPosition(), TEMPSUMMON_TIMED_DESPAWN, 200ms))
                {
                    tempSumm->SetFaction(caster->GetFaction());
                    tempSumm->SetOwnerGUID(caster->GetGUID());
                    PhasingHandler::InheritPhaseShift(tempSumm, caster);
                    caster->CastSpell(tempSumm, SPELL_HUNTER_EXPLOSIVE_TRAP_DAMAGE, true);
                    at->Remove();
                }
            }
        }
    };

    AreaTriggerAI* GetAI(AreaTrigger* areatrigger) const override
    {
        return new at_hun_explosive_trapAI(areatrigger);
    }
};

// Freezing Trap - 187650
// AreaTriggerID - 4424
class at_hun_freezing_trap : public AreaTriggerEntityScript
{
public:

    at_hun_freezing_trap() : AreaTriggerEntityScript("at_hun_freezing_trap") { }

    struct at_hun_freezing_trapAI : AreaTriggerAI
    {
        int32 timeInterval;

        enum UsedSpells
        {
            SPELL_HUNTER_FREEZING_TRAP_STUN = 3355
        };

        at_hun_freezing_trapAI(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger)
        {
            timeInterval = 200;
        }

        void OnCreate() override
        {
            Unit* caster = at->GetCaster();

            if (!caster)
                return;

            if (!caster->ToPlayer())
                return;

            for (auto itr : at->GetInsideUnits())
            {
                Unit* target = ObjectAccessor::GetUnit(*caster, itr);
                if (!caster->IsFriendlyTo(target))
                {
                    if (caster->HasAura(SPELL_HUNTER_DIAMOND_ICE))
                        caster->CastSpell(target, SPELL_HUNTER_DIAMOND_ICE_AURA, true);
                    else
                        caster->CastSpell(target, SPELL_HUNTER_FREEZING_TRAP_STUN, true);

                    at->Remove();
                    return;
                }
            }
        }

        void OnUnitEnter(Unit* unit) override
        {
            Unit* caster = at->GetCaster();

            if (!caster || !unit)
                return;

            if (!caster->ToPlayer())
                return;

            if (!caster->IsFriendlyTo(unit))
            {
                if (caster->HasAura(SPELL_HUNTER_DIAMOND_ICE))
                    caster->CastSpell(unit, SPELL_HUNTER_DIAMOND_ICE_AURA, true);
                else
                    caster->CastSpell(unit, SPELL_HUNTER_FREEZING_TRAP_STUN, true);

                at->Remove();
                return;
            }
        }
    };

    AreaTriggerAI* GetAI(AreaTrigger* areatrigger) const override
    {
        return new at_hun_freezing_trapAI(areatrigger);
    }
};

//Freezing Trap - 3355   v8.0.1
class spell_hun_freezing_trap_take_damage_spellScript : public AuraScript
{
    PrepareAuraScript(spell_hun_freezing_trap_take_damage_spellScript);

    enum UsedSpells
    {
        SPELL_HUNTER_FREEZING_TRAP_STUN = 3355
    };

    void OnProc(AuraEffect* aurEff, ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();

        if (!GetTarget())
            return;

        if (Unit* target = GetTarget())
        {
            target->RemoveAura(SPELL_HUNTER_FREEZING_TRAP_STUN);
            
        }
    }

    void Register() override
    {
        OnEffectProc += AuraEffectProcFn(spell_hun_freezing_trap_take_damage_spellScript::OnProc, EFFECT_0, SPELL_AURA_MOD_STUN);
    }
};

// Tar Trap (not activated) - 187698
// AreaTriggerID - 4435
class at_hun_tar_trap_not_activated : public AreaTriggerEntityScript
{
public:

    at_hun_tar_trap_not_activated() : AreaTriggerEntityScript("at_hun_tar_trap_not_activated") { }

    struct at_hun_tar_trap_not_activatedAI : AreaTriggerAI
    {
        int32 timeInterval;

        enum UsedSpells
        {
            SPELL_HUNTER_ACTIVATE_TAR_TRAP = 187700
        };

        at_hun_tar_trap_not_activatedAI(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger)
        {
            timeInterval = 200;
        }

        void OnCreate() override
        {
            Unit* caster = at->GetCaster();

            if (!caster)
                return;

            if (!caster->ToPlayer())
                return;

            for (auto itr : at->GetInsideUnits())
            {
                Unit* target = ObjectAccessor::GetUnit(*caster, itr);
                if (!caster->IsFriendlyTo(target))
                    if (Creature* tempSumm = caster->SummonCreature(WORLD_TRIGGER, at->GetPosition(), TEMPSUMMON_TIMED_DESPAWN, 200ms))
                    {
                        tempSumm->SetFaction(caster->GetFaction());
                        tempSumm->SetOwnerGUID(caster->GetGUID());
                        PhasingHandler::InheritPhaseShift(tempSumm, caster);
                        caster->CastSpell(tempSumm, SPELL_HUNTER_ACTIVATE_TAR_TRAP, true);
                        at->Remove();
                    }
            }
        }

        void OnUnitEnter(Unit* unit) override
        {
            Unit* caster = at->GetCaster();

            if (!caster || !unit)
                return;

            if (!caster->ToPlayer())
                return;

            if (!caster->IsFriendlyTo(unit))
            {
                if (Creature* tempSumm = caster->SummonCreature(WORLD_TRIGGER, at->GetPosition(), TEMPSUMMON_TIMED_DESPAWN, 200ms))
                {
                    tempSumm->SetFaction(caster->GetFaction());
                    tempSumm->SetOwnerGUID(caster->GetGUID());
                    PhasingHandler::InheritPhaseShift(tempSumm, caster);
                    caster->CastSpell(tempSumm, SPELL_HUNTER_ACTIVATE_TAR_TRAP, true);
                    at->Remove();
                }
            }
        }
    };

    AreaTriggerAI* GetAI(AreaTrigger* areatrigger) const override
    {
        return new at_hun_tar_trap_not_activatedAI(areatrigger);
    }
};

// Tar Trap (activated) - 187700
// AreaTriggerID - 4436
class at_hun_tar_trap_activated : public AreaTriggerEntityScript
{
public:
    at_hun_tar_trap_activated() : AreaTriggerEntityScript("at_hun_tar_trap_activated") { }

    struct at_hun_tar_trap_activatedAI : AreaTriggerAI
    {
        int32 timeInterval;

        enum UsedSpells
        {
            SPELL_HUNTER_TAR_TRAP_SLOW = 135299
        };

        at_hun_tar_trap_activatedAI(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger)
        {
            timeInterval = 200;
        }

        void OnCreate() override
        {
            Unit* caster = at->GetCaster();

            if (!caster)
                return;

            if (!caster->ToPlayer())
                return;

            for (auto itr : at->GetInsideUnits())
            {
                Unit* target = ObjectAccessor::GetUnit(*caster, itr);
                if (!caster->IsFriendlyTo(target))
                {
                    caster->CastSpell(target, SPELL_HUNTER_TAR_TRAP_SLOW, true);
                }
            }
        }

        void OnUnitEnter(Unit* unit) override
        {
            Unit* caster = at->GetCaster();

            if (!caster || !unit)
                return;

            if (!caster->ToPlayer())
                return;

            if (!caster->IsFriendlyTo(unit))
            {
                caster->CastSpell(unit, SPELL_HUNTER_TAR_TRAP_SLOW, true);
            }
        }

        void OnUnitExit(Unit* unit) override
        {
            Unit* caster = at->GetCaster();

            if (!caster || !unit)
                return;

            if (!caster->ToPlayer())
                return;

            if (unit->HasAura(SPELL_HUNTER_TAR_TRAP_SLOW) && unit->GetAura(SPELL_HUNTER_TAR_TRAP_SLOW)->GetCaster() == caster)
                unit->RemoveAura(SPELL_HUNTER_TAR_TRAP_SLOW);
        }

        void OnRemove() override
        {
            Unit* caster = at->GetCaster();

            if (!caster)
                return;

            if (!caster->ToPlayer())
                return;

            for (auto itr : at->GetInsideUnits())
            {
                if (Unit* target = ObjectAccessor::GetUnit(*caster, itr))
                {
                    if (target->HasAura(SPELL_HUNTER_TAR_TRAP_SLOW) && target->GetAura(SPELL_HUNTER_TAR_TRAP_SLOW)->GetCaster() == caster)
                        target->RemoveAura(SPELL_HUNTER_TAR_TRAP_SLOW);
                }
            }
        }
    };

    AreaTriggerAI* GetAI(AreaTrigger* areatrigger) const override
    {
        return new at_hun_tar_trap_activatedAI(areatrigger);
    }
};

// Binding Shot - 109248
// AreaTriggerID - 1524
class at_hun_binding_shot : public AreaTriggerEntityScript
{
public:

    at_hun_binding_shot() : AreaTriggerEntityScript("at_hun_binding_shot") { }

    struct at_hun_binding_shotAI : AreaTriggerAI
    {
        enum UsedSpells
        {
            SPELL_HUNTER_BINDING_SHOT_AURA = 117405,
            SPELL_HUNTER_BINDING_SHOT_STUN = 117526,
            SPELL_HUNTER_BINDING_SHOT_IMMUNE = 117553,
            SPELL_HUNTER_BINDING_SHOT_VISUAL_1 = 118306,
            SPELL_HUNDER_BINDING_SHOT_VISUAL_2 = 117614
        };

        at_hun_binding_shotAI(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger) { }

        void OnUnitEnter(Unit* unit) override
        {
            Unit* caster = at->GetCaster();

            if (!caster)
                return;

            if (!unit)
                return;

            if (!caster->IsFriendlyTo(unit))
            {
                unit->CastSpell(unit, SPELL_HUNTER_BINDING_SHOT_AURA, true);
            }
        }

        void OnUnitExit(Unit* unit) override
        {
            if (!unit || !at->GetCaster())
                return;

            Position pos = at->GetPosition();

            // Need to check range also, since when the trigger is removed, this get called as well.
            if (unit->HasAura(SPELL_HUNTER_BINDING_SHOT_AURA) && unit->GetExactDist(&pos) >= 5.0f)
            {
                unit->RemoveAura(SPELL_HUNTER_BINDING_SHOT_AURA);
                at->GetCaster()->CastSpell(unit, SPELL_HUNTER_BINDING_SHOT_STUN, true);
            }
        }
    };

    AreaTriggerAI* GetAI(AreaTrigger* areatrigger) const override
    {
        return new at_hun_binding_shotAI(areatrigger);
    }
};

// Caltrops - 194277 (194278)
// AreaTriggerID - 5084
class at_hun_caltrops : public AreaTriggerEntityScript
{
public:
    at_hun_caltrops() : AreaTriggerEntityScript("at_hun_caltrops") { }

    struct at_hun_caltropsAI : AreaTriggerAI
    {
        int32 timeInterval;

        enum UsedSpells
        {
            SPELL_HUNTER_CALTROPS_AURA = 194279
        };

        at_hun_caltropsAI(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger)
        {
            // How often should the action be executed
            timeInterval = 1000;
        }

        void OnUpdate(uint32 p_Time) override
        {
            Unit* caster = at->GetCaster();
            if (!caster)
                return;

            if (caster->GetTypeId() != TYPEID_PLAYER)
                return;

            // Check if we can handle actions
            timeInterval += p_Time;
            if (timeInterval < 1000)
                return;

            for (auto guid : at->GetInsideUnits())
            {
                if (Unit* unit = ObjectAccessor::GetUnit(*caster, guid))
                {
                    if (!caster->IsFriendlyTo(unit))
                    {
                        caster->CastSpell(unit, SPELL_HUNTER_CALTROPS_AURA, true);
                    }
                }
            }

            timeInterval -= 1000;
        }
    };

    AreaTriggerAI* GetAI(AreaTrigger* areatrigger) const override
    {
        return new at_hun_caltropsAI(areatrigger);
    }
};

// Black Arrow - 194599
// Reset Cooldown on creature kill
class PlayerScript_black_arrow : public PlayerScript
{
public:
    PlayerScript_black_arrow() :PlayerScript("PlayerScript_black_arrow") {}

    void OnCreatureKill(Player* Player, Creature* /*Creature*/)
    {
        if (Player->HasSpell(SPELL_HUNTER_BLACK_ARROW))
        {
            if (Player->GetSpellHistory()->HasCooldown(SPELL_HUNTER_BLACK_ARROW))
                Player->GetSpellHistory()->ResetCooldown(SPELL_HUNTER_BLACK_ARROW, true);
        }
    }

    void OnPVPKill(Player* killer, Player* /*killed*/)
    {
        if (killer->HasSpell(SPELL_HUNTER_BLACK_ARROW))
        {
            if (killer->GetSpellHistory()->HasCooldown(SPELL_HUNTER_BLACK_ARROW))
                killer->GetSpellHistory()->ResetCooldown(SPELL_HUNTER_BLACK_ARROW, true);
        }
    }
};


// Natural mending (talent) - 270581 v8.0.1
class PlayerScript_hunter_natural_mending : public PlayerScript
{
public:
    PlayerScript_hunter_natural_mending() : PlayerScript("PlayerScript_hunter_natural_mending") {}

    enum eSpells
    {
        NATURAL_MENDING = 270581
    };

    void OnModifyPower(Player * player, Powers power, int32 oldValue, int32& newValue, bool regen, bool after)
    {
        if (after || regen)
            return;

        if (!player || player->GetClass() != CLASS_HUNTER)
            return;

        int basePoint = player->GetSpecializationId() == TALENT_SPEC_HUNTER_BEASTMASTER ? sSpellMgr->GetSpellInfo(NATURAL_MENDING)->GetEffect(EFFECT_0).BasePoints : sSpellMgr->GetSpellInfo(NATURAL_MENDING)->GetEffect(EFFECT_1).BasePoints;
       
        if (player->HasSpell(NATURAL_MENDING) && player->GetSpellHistory()->HasCooldown(SPELL_HUNTER_EXHILARATION) && power == POWER_FOCUS && newValue >= basePoint)
        {   
            player->GetSpellHistory()->ModifyCooldown(SPELL_HUNTER_EXHILARATION, -1000);
        }
    }
};

class Playerscript_hunter_lone_wolf : public PlayerScript
{
public:
    Playerscript_hunter_lone_wolf() : PlayerScript("Playerscript_hunter_lone_wolf") {}

    void OnUpdate(Player* player, uint32 diff)
    {
        if (timer <= diff)
        {       
            timer = 500;

            if (!player || !player->IsAlive())
                return;

            if (player->GetClass() != CLASS_HUNTER)
                return;

            if (!player->HasAura(SPELL_HUNTER_LONE_WOLF))
                return;

            if (Aura* aura = player->GetAura(SPELL_HUNTER_LONE_WOLF))
            {
                Pet* pet = player->GetPet();
                if (!pet && !player->HasAura(SPELL_HUNTER_LONE_WOLF_AURA))
                {
                    uint8 damage = sSpellMgr->GetSpellInfo(SPELL_HUNTER_LONE_WOLF)->GetEffect(EFFECT_2).BasePoints;
                    aura->GetEffect(EFFECT_0)->ChangeAmount(damage);
                    aura->GetEffect(EFFECT_1)->ChangeAmount(damage);
                    player->CastCustomSpell(SPELL_HUNTER_LONE_WOLF_AURA, SPELLVALUE_BASE_POINT0, damage, player, true);
                }
                else if (pet && player->HasAura(SPELL_HUNTER_LONE_WOLF_AURA))
                {
                    aura->GetEffect(EFFECT_0)->ChangeAmount(0);
                    aura->GetEffect(EFFECT_1)->ChangeAmount(0);
                    player->RemoveAura(SPELL_HUNTER_LONE_WOLF_AURA);
                }
            }
        }
        else
            timer -= diff;        
    }

private:
    uint32 timer = 500;

};

/// Bursting Shot --  186387
class spell_bursting_shot : public SpellScript
{
    PrepareSpellScript(spell_bursting_shot);

    void HandleAfterHit()
    {
        if (Unit* caster = GetCaster())
            caster->CastSpell(GetHitUnit(), SPELL_HUNTER_AURA_SHOOTING, true);
    }

    void Register()
    {
        AfterHit += SpellHitFn(spell_bursting_shot::HandleAfterHit);
    }
};

//90361 Spirit Mend
//Last Update 8.0.1 Build 28153
class spell_hun_spirit_mend : public SpellScriptLoader
{
public:
    spell_hun_spirit_mend() : SpellScriptLoader("spell_hun_spirit_mend") { }

    class spell_hun_spirit_mend_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_hun_spirit_mend_AuraScript);

        void CalculateAmount(AuraEffect const* auraEffect, int32& amount, bool& /*canBeRecalculated*/)
        {
            if (Unit* caster = GetCaster())            
                if (Unit* owner = caster->GetOwner())                
                    if (auraEffect->GetPeriod() && GetMaxDuration())
                        amount = int32(owner->GetTotalAttackPowerValue(WeaponAttackType::RANGED_ATTACK) * 0.6f * 2.0f * 1.0504f) / (GetMaxDuration() / auraEffect->GetPeriod());
        }

        void Register()
        {
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_hun_spirit_mend_AuraScript::CalculateAmount, EFFECT_1, SPELL_AURA_PERIODIC_HEAL);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_hun_spirit_mend_AuraScript();
    }

    class spell_hun_spirit_mend_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_hun_spirit_mend_SpellScript);

        void HandleHeal(SpellEffIndex effect)
        {
            Unit* caster = GetCaster();
            Unit* owner = caster->GetOwner();
            Unit* target = GetHitUnit();

            if (target == nullptr || owner == nullptr)
                return;

            int32 heal = int32(owner->GetTotalAttackPowerValue(WeaponAttackType::RANGED_ATTACK) * 0.6f * 3.0f);
            heal = owner->SpellHealingBonusDone(target, GetSpellInfo(), heal, HEAL, GetEffectInfo(EFFECT_0));
            heal = target->SpellHealingBonusTaken(caster, GetSpellInfo(), heal, HEAL);
            SetHitHeal(heal);
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_hun_spirit_mend_SpellScript::HandleHeal, EFFECT_0, SPELL_EFFECT_HEAL);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_hun_spirit_mend_SpellScript();
    }
};

class spell_hun_steady_shot : public SpellScriptLoader
{
public:
    spell_hun_steady_shot() : SpellScriptLoader("spell_hun_steady_shot") { }

    class spell_hun_steady_shot_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_hun_steady_shot_SpellScript);

        void HandleAfterCast()
        {
            if (Unit* caster = GetCaster())
                caster->ModifyPower(POWER_FOCUS, 10);
        }

        void Register()
        {
            AfterCast += SpellCastFn(spell_hun_steady_shot_SpellScript::HandleAfterCast);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_hun_steady_shot_SpellScript();
    }
};

// 193455 - Cobra Shot
class spell_hun_cobra_shot : public SpellScriptLoader
{
public:
    spell_hun_cobra_shot() : SpellScriptLoader("spell_hun_cobra_shot") { }

    class spell_hun_cobra_shot_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_hun_cobra_shot_SpellScript);

        void HandleDamage(SpellEffIndex /*effIndex*/)
        {
            Unit* caster = GetCaster();
			Unit* target = GetExplTargetUnit();
			if (!caster || !target)
                return;
            Unit* owner = caster->GetOwner();
            if (!owner)
                return;

            // (26% * (rap) * lowNerf * (1 + versability))
            int32 dmg = (owner->m_unitData->RangedAttackPower / 100) * 27.5808f;
            int32 lowNerf = std::min(int32(owner->GetLevel()), 20) * 0.12f + 0.112f;
            int32 final = lowNerf / 0.34f;
            dmg *= final;

            dmg = caster->SpellDamageBonusDone(target, GetSpellInfo(), dmg, SPELL_DIRECT_DAMAGE, GetEffectInfo(EFFECT_1));
            dmg = target->SpellDamageBonusTaken(caster, GetSpellInfo(), dmg, SPELL_DIRECT_DAMAGE);

            SetHitDamage(dmg);
        }

		void HandleAfterCast()
		{
            if (Unit* caster = GetCaster())
            {
                if (caster->GetSpellHistory()->HasCooldown(SPELL_HUNTER_KILL_COMMAND))
                    caster->GetSpellHistory()->ModifyCooldown(SPELL_HUNTER_KILL_COMMAND, -IN_MILLISECONDS);

                if (caster->HasAura(SPELL_HUNTER_VENOMOUS_BITE))
                    caster->GetSpellHistory()->ModifyCooldown(SPELL_HUNTER_BESTIAL_WRATH, -IN_MILLISECONDS);
            }
		}

        void Register() override
        {
			AfterCast += SpellCastFn(spell_hun_cobra_shot_SpellScript::HandleAfterCast);
            OnEffectHitTarget += SpellEffectFn(spell_hun_cobra_shot_SpellScript::HandleDamage, EFFECT_1, SPELL_EFFECT_SCHOOL_DAMAGE);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_hun_cobra_shot_SpellScript();
    }
};

// Sentinel - 206817
// AreaTriggerID - 9769
struct at_hun_sentinel : AreaTriggerAI
{
    at_hun_sentinel(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger) { }

    int32 baseTimeInterval;
    int32 timeInterval;

    void OnCreate() override
    {
        baseTimeInterval = sSpellMgr->GetSpellInfo(SPELL_HUNTER_SENTINEL)->GetEffect(EFFECT_1).BasePoints * IN_MILLISECONDS;
        timeInterval = baseTimeInterval;
    }

    void OnUpdate(uint32 diff) override
    {
        timeInterval += diff;
        if (timeInterval < baseTimeInterval)
            return;

        if (Unit* caster = at->GetCaster())
            for (ObjectGuid guid : at->GetInsideUnits())
                if (Unit* target = ObjectAccessor::GetUnit(*caster, guid))
                    if (caster->IsValidAttackTarget(target))
                    {
                        caster->CastSpell(target, SPELL_HUNTER_HUNTERS_MARK_AURA, true);
                        caster->CastSpell(caster, SPELL_HUNTER_HUNTERS_MARK_AURA_2, true);
                    }

        timeInterval -= baseTimeInterval;
    }
};

struct at_hunter_explosive_trap : AreaTriggerAI
{
	at_hunter_explosive_trap(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger) { }

	void OnUnitEnter(Unit* unit)
	{
		if (Unit* caster = at->GetCaster())
			if (unit && caster->IsValidAttackTarget(unit))
			{
				caster->CastSpell(at->GetPosition(), SPELL_HUNTER_EXPLOSIVE_TRAP, true);
				at->SetDuration(0);
			}
	}
};

class aura_hun_lethal_shots : public AuraScript
{
    PrepareAuraScript(aura_hun_lethal_shots);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == SPELL_HUNTER_STEADY_SHOT)
            return true;
        return false;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_hun_lethal_shots::CheckProc);
    }
};

// 268501 - Viper's Venom
//Last Update 8.0.1 Build 28153
class aura_hun_viper_venom : public AuraScript
{
	PrepareAuraScript(aura_hun_viper_venom);

	bool CheckProc(ProcEventInfo& eventInfo)
	{
		if (eventInfo.GetSpellInfo() && (eventInfo.GetSpellInfo()->Id == SPELL_HUNTER_RAPTOR_STRIKE || eventInfo.GetSpellInfo()->Id == SPELL_HUNTER_MANGOOSE_BITE))
			return true;

		return false;
	}

	void Register() override
	{
		DoCheckProc += AuraCheckProcFn(aura_hun_viper_venom::CheckProc);
	}
};

// 259491 - Serpent Sting
class spell_hun_serpent_sting : public SpellScript
{
	PrepareSpellScript(spell_hun_serpent_sting);

    ObjectGuid mainTarget;

	void CacheMainTarget(WorldObject*& target)
	{
        if (target)
		    mainTarget = target->GetGUID();
	}

	void FilterTargets(std::list<WorldObject*>& targets)
	{
		if (Unit* caster = GetCaster())
		{
			if (mainTarget.IsEmpty())
				return;

            auto mainTargetUnit = ObjectAccessor::GetUnit(*caster, mainTarget);

			if (!caster->HasAura(SPELL_HUNTER_HIDRAS_BITE))
			{
				targets.clear();
				targets.push_back(mainTargetUnit);
				return;
			}

			CreatureList list = mainTargetUnit->FindAllCreaturesInRange(8.0f);
			list.sort(Trinity::ObjectDistanceOrderPred(mainTargetUnit));
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
			
			if (targets.size() > 3)
				targets.resize(3);
		}
	}

	void HandleAfterCast()
	{
		if (Unit* caster = GetCaster())
			if (caster->HasAura(SPELL_HUNTER_VIPER_VENOM_AURA))
				caster->RemoveAurasDueToSpell(SPELL_HUNTER_VIPER_VENOM_AURA);
	}

	void Register() override
	{
		OnObjectTargetSelect += SpellObjectTargetSelectFn(spell_hun_serpent_sting::CacheMainTarget, EFFECT_0, TARGET_UNIT_TARGET_ENEMY);
		OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_hun_serpent_sting::FilterTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ENEMY);
		OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_hun_serpent_sting::FilterTargets, EFFECT_1, TARGET_UNIT_DEST_AREA_ENEMY);
		AfterCast += SpellCastFn(spell_hun_serpent_sting::HandleAfterCast);
	}
};

//259387 - Mongoose Bite
class spell_hun_mangoose_bite : public SpellScript
{
	PrepareSpellScript(spell_hun_mangoose_bite);

	void HandleAfterCast()
	{
		if (Unit* caster = GetCaster())
			if (caster->HasAura(SPELL_HUNTER_VIPER_VENOM_AURA))
				caster->RemoveAurasDueToSpell(SPELL_HUNTER_VIPER_VENOM_AURA);
	}

	void Register() override
	{
		AfterCast += SpellCastFn(spell_hun_mangoose_bite::HandleAfterCast);
	}
};

// 257620 - Multishot
class spell_hun_multishot_aim : public SpellScript
{
	PrepareSpellScript(spell_hun_multishot_aim);

    uint32 hitCounted = 0;

	void HandleHit()
	{
        if (Unit* caster = GetCaster())
        {
            if (Aura* aura = caster->GetAura(SPELL_HUNTER_RAPID_RELOAD))
            {
                if (hitCounted == 4)
                {
                    if (Unit* currentTarget = ObjectAccessor::GetUnit(*caster, caster->GetTarget()))
                        if (caster->IsValidAttackTarget(currentTarget))
                            caster->CastCustomSpell(SPELL_HUNTER_RAPID_RELOAD_DAMAGE, SPELLVALUE_BASE_POINT0, aura->GetEffect(EFFECT_0)->GetAmount(), currentTarget, true);

                    caster->GetSpellHistory()->ModifyCooldown(SPELL_HUNTER_ASPECT_OF_THE_TURTLE, -1s);
                    caster->GetSpellHistory()->ModifyCooldown(SPELL_HUNTER_ASPECT_OF_THE_WILD, -1s);
                    caster->GetSpellHistory()->ModifyCooldown(SPELL_HUNTER_ASPECT_OF_THE_CHEETAH, -1s);
                }
            }

            hitCounted++;
        }
	}

	void HandleAfterCast()
	{
		if (Unit* caster = GetCaster())
			if (caster->HasAura(SPELL_HUNTER_MASTER_MARKSMAN_TRIGGER))
				caster->RemoveAurasDueToSpell(SPELL_HUNTER_MASTER_MARKSMAN_TRIGGER);
	}

    void HandleAfterHit()
    {
        if (Unit* caster = GetCaster())
            if (SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(SPELL_HUNTER_TRICK_SHOT_AURA))
                if (hitCounted >= (uint32)spellInfo->GetEffect(EFFECT_1).BasePoints)
                    caster->CastSpell(caster, SPELL_HUNTER_TRICK_SHOT_PROC, true);
    }

	void Register() override
	{
		AfterCast += SpellCastFn(spell_hun_multishot_aim::HandleAfterCast);
		OnHit += SpellHitFn(spell_hun_multishot_aim::HandleHit);
        AfterHit += SpellHitFn(spell_hun_multishot_aim::HandleAfterHit);
	}
};

//Steady Shot - 56641  v8.0.1
class spell_hun_steady_shot_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_hun_steady_shot_SpellScript);

    void HandleAfterCast()
    {
        if (Unit* caster = GetCaster())
            caster->CastCustomSpell(SPELL_HUNTER_STEADY_SHOT_ENERGIZE, SPELLVALUE_BASE_POINT0, sSpellMgr->GetSpellInfo(SPELL_HUNTER_STEADY_SHOT)->GetEffect(EFFECT_1).BasePoints);
    }

    void Register() override
    {
        AfterCast += SpellCastFn(spell_hun_steady_shot_SpellScript::HandleAfterCast);
    }
};

// 212640 - Mending Bandage
class spell_hun_mending_bandage : public SpellScript
{
	PrepareSpellScript(spell_hun_mending_bandage);

	void HandleAfterCast()
	{
		if (Unit* caster = GetCaster())
			caster->GetSpellHistory()->StartCooldownROG(GetSpellInfo(), 0, GetSpell(), false, true, 25 * IN_MILLISECONDS);
	}

	void Register() override
	{
		AfterCast += SpellCastFn(spell_hun_mending_bandage::HandleAfterCast);
	}
};

// 186265 - Aspect of the Turtle
class spell_hun_aspect_of_the_turtle : public SpellScript
{
	PrepareSpellScript(spell_hun_aspect_of_the_turtle);

	void HandleCast()
	{
		if (Unit* caster = GetCaster())
			caster->CastSpell(caster, SPELL_HUNTER_TURTLE_PACIFY, true);
	}

	void Register() override
	{
		OnCast += SpellCastFn(spell_hun_aspect_of_the_turtle::HandleCast);
	}
};

// 186265 - Aspect of the Turtle
class aura_hun_aspect_of_the_turtle_aura : public AuraScript
{
	PrepareAuraScript(aura_hun_aspect_of_the_turtle_aura);

	void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
	{
		if (Unit* caster = GetCaster())
			caster->RemoveAura(SPELL_HUNTER_TURTLE_PACIFY);
	}

	void Register() override
	{
		OnEffectRemove += AuraEffectRemoveFn(aura_hun_aspect_of_the_turtle_aura::HandleRemove, EFFECT_0, SPELL_AURA_MOD_ATTACKER_MELEE_HIT_CHANCE, AURA_EFFECT_HANDLE_REAL);
	}
};

// 248443 - Ranger's Finesse
class aura_hun_ranger_finesse : public AuraScript
{
	PrepareAuraScript(aura_hun_ranger_finesse);

	bool CheckProc(ProcEventInfo& eventInfo)
	{
		if (eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == SPELL_HUNTER_AIMED_SHOT)
			return true;
		
		return false;
	}

	void HandleProc(ProcEventInfo& eventInfo)
	{
		if (Unit* caster = GetCaster())
		{
			caster->GetSpellHistory()->ModifyCooldown(SPELL_HUNTER_EXHILARATION, -5s);
			caster->GetSpellHistory()->ModifyCooldown(SPELL_HUNTER_ASPECT_OF_THE_TURTLE, -5s);
		}
	}

	void Register() override
	{
		DoCheckProc += AuraCheckProcFn(aura_hun_ranger_finesse::CheckProc);
		OnProc += AuraProcFn(aura_hun_ranger_finesse::HandleProc);
	}
};

// 53480 - Roar of Sacrifice
class spell_hun_roar_of_sacrifice : public SpellScript
{
	PrepareSpellScript(spell_hun_roar_of_sacrifice);

	SpellCastResult CheckCast()
	{
		if (Unit* caster = GetCaster())
		{
			if (!caster->GetGuardianPet())
				return SPELL_FAILED_NO_PET;

			return SPELL_CAST_OK;
		}
		return SPELL_FAILED_ERROR;
	}

	void HandleBeforeHit(SpellMissInfo /*missInfo*/)
	{
		Unit* caster = GetCaster();
		Unit* target = GetExplTargetUnit();
		if (!caster || !target)
			return;

		if (Guardian* pet = caster->GetGuardianPet())
		{
			pet->SetTarget(target->GetGUID());
			pet->CastSpell(target, SPELL_HUNTER_ROAR_OF_SACRIFICE_CHARGE, true);
		}
	}

	void Register() override
	{
		OnCheckCast += SpellCheckCastFn(spell_hun_roar_of_sacrifice::CheckCast);
		BeforeHit += BeforeSpellHitFn(spell_hun_roar_of_sacrifice::HandleBeforeHit);
	}
};

// 53480 - Roar of Sacrifice
class aura_hun_roar_of_sacrifice : public AuraScript
{
	PrepareAuraScript(aura_hun_roar_of_sacrifice);

	bool CheckProc(ProcEventInfo& eventInfo)
	{
		if (eventInfo.GetDamageInfo() && (eventInfo.GetDamageInfo()->GetDamageType() != HEAL && eventInfo.GetDamageInfo()->GetDamageType() != NODAMAGE))
			return true;

		return false;
	}

	void HandleProc(ProcEventInfo& eventInfo)
	{
		Unit* caster = GetCaster();
		Unit* owner = GetUnitOwner();
		if (!caster || !owner)
			return;

		if (eventInfo.GetDamageInfo())
		{
			int32 damage = eventInfo.GetDamageInfo()->GetDamage();
			if (Guardian* pet = caster->GetGuardianPet())
			{
				int32 petDamage = CalculatePct(damage, sSpellMgr->GetSpellInfo(SPELL_HUNTER_ROAR_OF_SACRIFICE)->GetEffect(EFFECT_1).BasePoints);
				caster->CastCustomSpell(SPELL_HUNTER_ROAR_OF_SACRIFICE_DAMAGE, SPELLVALUE_BASE_POINT0, petDamage, pet, true);
			}
		}
	}

	void Register() override
	{
		DoCheckProc += AuraCheckProcFn(aura_hun_roar_of_sacrifice::CheckProc);
		OnProc += AuraProcFn(aura_hun_roar_of_sacrifice::HandleProc);
	}
};

// 202746 - Survival Tactics
class aura_hun_survival_tactics : public AuraScript
{
	PrepareAuraScript(aura_hun_survival_tactics);

	bool CheckProc(ProcEventInfo& eventInfo)
	{
		return false;
	}

	void Register() override
	{
		DoCheckProc += AuraCheckProcFn(aura_hun_survival_tactics::CheckProc);
	}
};

// 19434 - Aimed Shot
class spell_hun_aimed_shot : public SpellScript
{
	PrepareSpellScript(spell_hun_aimed_shot);

    bool removeLockAndLoad;

    void HandlePrepare()
    {
        Unit* caster = GetCaster();
        if (!caster)
            return;

        //Is better use this way to avoid innecesary remove when the caster have UNIT_STATE_CASTING and the aura is added in that process
        //then with this we only could remove lock and load if the caster have the aura before cast
        if (caster->HasAura(SPELL_HUNTER_LOCK_AND_LOAD))
            removeLockAndLoad = true;
    }

    void HandleCalcCastTime(int32& castTime)
    {
        if (Unit* caster = GetCaster())
            if (caster->HasAura(SPELL_HUNTER_LOCK_AND_LOAD))
                castTime = 0;
    }

    void HandleAfterCast()
    {
        Unit* caster = GetCaster();
        Unit* target = GetExplTargetUnit();
        if (!caster || !target)
            return;

        // Lock and Load
        if (caster->HasAura(SPELL_HUNTER_LOCK_AND_LOAD) && removeLockAndLoad)
            caster->RemoveAura(SPELL_HUNTER_LOCK_AND_LOAD);

        // Steady Aim
        if (caster->HasAura(SPELL_HUNTER_STEADY_AIM_BUFF))
            caster->RemoveAura(SPELL_HUNTER_STEADY_AIM_BUFF);
    }

	void HandleHit()
	{
		Unit* caster = GetCaster();
		Unit* target = GetHitUnit();
		if (!caster || !target)
			return;

        damage = GetHitDamage();
        if (!target->HasAura(SPELL_HUNTER_AIMED_SHOT_BONUS, caster->GetGUID()))
            damage = damage + CalculatePct(damage, sSpellMgr->GetSpellInfo(SPELL_HUNTER_AIMED_SHOT)->GetEffect(EFFECT_1).CalcValue(caster));
		

        if(caster->HasAura(SPELL_HUNTER_TRICK_SHOT_PROC))
            damage = CalculatePct(damage, sSpellMgr->GetSpellInfo(SPELL_HUNTER_TRICK_SHOT_AURA)->GetEffect(EFFECT_3).BasePoints);

        SetHitDamage(damage);
	}

    void HandleAfterHit()
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        if (caster->HasAura(SPELL_HUNTER_DOUBLE_TAP))
        {
            caster->RemoveAura(SPELL_HUNTER_DOUBLE_TAP);

            SpellNonMeleeDamage damageLog = SpellNonMeleeDamage(caster, target, GetSpellInfo(), { GetSpellInfo()->GetSpellXSpellVisualId(), 0 }, GetSpellInfo()->GetSchoolMask());
            damageLog.damage = damage;
            caster->CalculateSpellDamageTaken(&damageLog, damageLog.damage, GetSpellInfo());
            caster->DealDamageMods(caster, target, damageLog.damage, &damageLog.absorb);
            caster->SendSpellNonMeleeDamageLog(&damageLog);
            caster->DealDamage(caster, target, damage);
        }     
    }

	void Register() override
	{
        OnPrepare += SpellOnPrepareFn(spell_hun_aimed_shot::HandlePrepare);
        OnCalcCastTime += SpellOnCalcCastTimeFn(spell_hun_aimed_shot::HandleCalcCastTime);
        AfterCast += SpellCastFn(spell_hun_aimed_shot::HandleAfterCast);
		 OnHit += SpellHitFn(spell_hun_aimed_shot::HandleHit);
        AfterHit += SpellHitFn(spell_hun_aimed_shot::HandleAfterHit);
	}

private:
    int32 damage;
};

// 260240 - Precise Shots
class aura_hun_precise_shots : public AuraScript
{
	PrepareAuraScript(aura_hun_precise_shots);

	bool CheckProc(ProcEventInfo& eventInfo)
	{
		if (eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == SPELL_HUNTER_AIMED_SHOT)
			return true;

		return false;
	}

	void HandleProc(ProcEventInfo& eventInfo)
	{
		if (Unit* caster = GetCaster())
    		caster->CastSpell(caster, SPELL_HUNTER_PRECISE_SHOTS, true);
	}

	void Register() override
	{
		DoCheckProc += AuraCheckProcFn(aura_hun_precise_shots::CheckProc);
		OnProc += AuraProcFn(aura_hun_precise_shots::HandleProc);
	}
};

// 270581 - Natural Mending
class aura_hun_natural_mending : public AuraScript
{
	PrepareAuraScript(aura_hun_natural_mending);

	bool CheckProc(ProcEventInfo& eventInfo)
	{
		if (Spell const* procSpell = eventInfo.GetProcSpell())
			if (SpellPowerCost const* powerCost = procSpell->GetPowerCost(POWER_FOCUS))
				if (powerCost->Amount > 0)
				{
					powerSpent = powerCost->Amount;
					return true;
				}

		return false;
	}

	void HandleProc(ProcEventInfo& eventInfo)
	{
		if (Unit* caster = GetCaster())
		{
			uint8 extra = (caster->Variables.Exist("NM_EXTRA")) ? caster->Variables.GetValue<uint8>("NM_EXTRA") : 0;
			if (caster->GetSpellHistory()->HasCooldown(SPELL_HUNTER_EXHILARATION))
			{
				extra += powerSpent;
				if (extra >= 20)
				{
					uint8 rest = extra % 20;
					uint8 value = std::floor(extra / 20);
					extra = rest;
					caster->GetSpellHistory()->ModifyCooldown(SPELL_HUNTER_EXHILARATION, -1s * value);
				}
			}
			else
				extra = 0;

            // Set extra.
			caster->Variables.Set<uint8>("NM_EXTRA", extra);
		}
	}

	void HandleRemove(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /* mode */)
	{
		if (Unit* caster = GetCaster())
			caster->Variables.Remove("NM_EXTRA");
	}

	void Register() override
	{
		DoCheckProc += AuraCheckProcFn(aura_hun_natural_mending::CheckProc);
		OnProc += AuraProcFn(aura_hun_natural_mending::HandleProc);
		OnEffectRemove += AuraEffectRemoveFn(aura_hun_natural_mending::HandleRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
	}

private:
	uint8 powerSpent = 0;
};

// 257044 - Rapid Fire Update 8.0.1 build 28153
class aura_hun_rapid_fire : public AuraScript
{
    PrepareAuraScript(aura_hun_rapid_fire);

    void AfterApply(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* caster = GetCaster())
            if (caster->HasAura(SPELL_HUNTER_DOUBLE_TAP))
                caster->RemoveAura(SPELL_HUNTER_DOUBLE_TAP);
    }

    void OnPeriodic(AuraEffect const* /*aurEff*/)
    {
        if (Unit* caster = GetCaster())
            caster->CastSpell(caster, SPELL_HUNTER_RAPID_FIRE_ENERGIZE, true);            
    }

    void HandleRemove(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /* mode */)
    {
        Unit* caster = GetCaster();
        if (!caster)
            return;

        if (caster->HasAura(SPELL_HUNTER_TRICK_SHOT_PROC))
            caster->RemoveAura(SPELL_HUNTER_TRICK_SHOT_PROC);
    }

    void Register() override
    {
        AfterEffectApply += AuraEffectApplyFn(aura_hun_rapid_fire::AfterApply, EFFECT_1, SPELL_AURA_PERIODIC_TRIGGER_SPELL, AURA_EFFECT_HANDLE_REAL);
        OnEffectPeriodic += AuraEffectPeriodicFn(aura_hun_rapid_fire::OnPeriodic, EFFECT_1, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
        OnEffectRemove += AuraEffectApplyFn(aura_hun_rapid_fire::HandleRemove, EFFECT_1, SPELL_AURA_PERIODIC_TRIGGER_SPELL, AURA_EFFECT_HANDLE_REAL);
    }
};

// 257045 - Rapid Fire Damage
class spell_hun_rapid_fire_damage : public SpellScript
{
    PrepareSpellScript(spell_hun_rapid_fire_damage);

    void CheckTarget(WorldObject*& target)
    {
        if (target == GetCaster())
            target = nullptr;
    }

    void Register() override
    {
        OnObjectTargetSelect += SpellObjectTargetSelectFn(spell_hun_rapid_fire_damage::CheckTarget, EFFECT_0, TARGET_UNIT_CHANNEL_TARGET);
    }
};

// Last Update 8.0.1 Build 23420
// Called By Stampede - 201631
class aura_hun_stampede : public AuraScript
{
    PrepareAuraScript(aura_hun_stampede);

    std::vector<uint32> StampedeSpells =
    {
        SPELL_HUNTER_STAMPEDE_BEAR,
        SPELL_HUNTER_STAMPEDE_BIRD
    };

    void OnPeriodic(AuraEffect const* /*aurEff*/)
    {
        Unit* caster = GetCaster();
        if (!caster)
            return;

        for (int8 i = 0; i < 3; ++i)
            caster->CastSpell(caster, StampedeSpells[urand(0, StampedeSpells.size() - 1)], true);
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(aura_hun_stampede::OnPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

//10466 Stampede Areatrigger Misc ID 5754 Update 8.0.1 Build 28153
struct at_hunter_stampede : AreaTriggerAI
{
    at_hunter_stampede(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger) { }

    void OnInitialize() override
    {
        Unit* caster = at->GetCaster();
        if (!caster)
            return;

        Position pos = caster->GetPositionWithDistInFront(44.9984f); //Snifed Value
        at->SetDestination(pos, 2279); //Snifed Value        
    }

    void OnUnitEnter(Unit* unit) override
    {
        if (Unit* caster = at->GetCaster())
        {
            if (Unit* owner = caster->GetOwner())
            {
                if (unit && owner->IsValidAttackTarget(unit))
                {
                    owner->CastSpell(unit, SPELL_HUNTER_STAMPEDE_DAMAGE, true);
                }
            }
        }
    }
};

// 202914 Spider Sting Last Update 8.0.1 Build 28153
class aura_hun_spider_sting : public AuraScript
{
    PrepareAuraScript(aura_hun_spider_sting);

    void HandleProc(AuraEffect* /*aurEff*/, ProcEventInfo& /*eventInfo*/)
    {
        if (Unit* caster = GetCaster())
            if (Unit* target = GetTarget())
                caster->CastSpell(target, SPELL_HUNTER_SPIDER_STING_SILENCE, true);
    }

    void Register() override
    {
        OnEffectProc += AuraEffectProcFn(aura_hun_spider_sting::HandleProc, EFFECT_0, SPELL_AURA_PROC_TRIGGER_SPELL);
    }
};

// 257284 Hunter's Mark Last Update 8.0.1 build 28153 
class aura_hun_mark_energize : public AuraScript
{
    PrepareAuraScript(aura_hun_mark_energize);

    void HandleRemove(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /* mode */)
    {
        Unit* caster = GetCaster();
        if (!caster)
            return;

        if (Player* player = caster->ToPlayer())
            if (GetTargetApplication()->GetRemoveMode() == AURA_REMOVE_BY_DEATH)
                player->CastSpell(player, SPELL_HUNTER_MARK_ENERGIZE, true);
    }

    void Register() override
    {
        OnEffectRemove += AuraEffectApplyFn(aura_hun_mark_energize::HandleRemove, EFFECT_1, SPELL_AURA_MOD_STALKED, AURA_EFFECT_HANDLE_REAL);
    }
};

//260248 Bloodseeker Misc ID 12314  Update 8.0.1 Build 28153
struct at_hun_bloodseeker : AreaTriggerAI
{
    at_hun_bloodseeker(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger) { }

    uint32 bleedingCheck = 500;

    void OnUnitEnter(Unit* unit) override
    {
        if (unit && unit->HasAuraState(AURA_STATE_BLEED))
        {
            if (Unit* caster = at->GetCaster())
            {
                if (caster->IsValidAttackTarget(unit))
                {
                    if (Player* player = caster->ToPlayer())
                    {
                        player->CastSpell(player, SPELL_HUNTER_PREDATOR, true);

                        if (Pet* pet = player->GetPet())
                            pet->CastSpell(pet, SPELL_HUNTER_PREDATOR, true);
                    }
                }
            }
        }
    }

    void OnUnitExit(Unit* unit) override
    {
        if (unit)
        {
            if (Unit* caster = at->GetCaster())
            {
                if (Player* player = caster->ToPlayer())
                {
                    if (Aura* predator = player->GetAura(SPELL_HUNTER_PREDATOR))
                        predator->DropStack();

                    if (Pet* pet = player->GetPet())
                        if (Aura* predator = pet->GetAura(SPELL_HUNTER_PREDATOR))
                            predator->DropStack();
                }
            }
        }
    }

    void OnUpdate(uint32 diff) override
    {
        if (bleedingCheck <= diff)
        {
            if (Unit* caster = at->GetCaster())
            {
                if (Player* player = caster->ToPlayer())
                {
                    std::list<Unit*> unitsBleeding;

                    for (auto obj : at->GetInsideUnits())
                        if (Unit* unit = ObjectAccessor::GetUnit(*player, obj))
                            if (player->IsValidAttackTarget(unit))
                                if (unit->HasAuraState(AURA_STATE_BLEED))
                                    unitsBleeding.push_back(unit);

                    if (Aura* predator = player->GetAura(SPELL_HUNTER_PREDATOR))
                    {
                        if (unitsBleeding.size() != predator->GetStackAmount())
                            predator->SetStackAmount(unitsBleeding.size());
                        else if (unitsBleeding.empty())
                            player->RemoveAura(SPELL_HUNTER_PREDATOR);
                    }                    
                    else if (!unitsBleeding.empty())
                        player->CastSpell(player, SPELL_HUNTER_PREDATOR, true);

                    if (Pet* pet = player->GetPet())
                    {
                        if (Aura* predator = pet->GetAura(SPELL_HUNTER_PREDATOR))
                        {
                            if (unitsBleeding.size() != predator->GetStackAmount())
                                predator->SetStackAmount(unitsBleeding.size());
                            else if (unitsBleeding.empty())
                                pet->RemoveAura(SPELL_HUNTER_PREDATOR);
                        }
                        else if (!unitsBleeding.empty())
                            pet->CastSpell(pet, SPELL_HUNTER_PREDATOR, true);
                    }

                    bleedingCheck = 500;
                }
            }
        }
        else
            bleedingCheck -= diff;
    }
};

// AT: Dire Beast: Hawk
struct at_hunter_hawk : AreaTriggerAI
{
    at_hunter_hawk(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger) { }

    void OnCreate() override
    {
        if (Unit* caster = at->GetCaster())
        {
            Position position = Position(at->GetPositionX(), at->GetPositionY(), at->GetPositionZ());
            TempSummon* hawk = caster->SummonCreature(105374, position, TEMPSUMMON_TIMED_DESPAWN, 11s);
            if (hawk)
            {
                hawk->SetFlying(true);
                hawk->SetDisableGravity(true);
                hawk->CastSpell(hawk, SPELL_HUNTER_DIRE_BEAST_HAWK_FADE, true);
                for (uint8 i = MOVE_WALK; i < MAX_MOVE_TYPE; i++)
                    hawk->SetSpeedRate((UnitMoveType)i, 2.5f);
                hawk->GetMotionMaster()->MoveCirclePath(position.GetPositionX(), position.GetPositionY(), position.GetPositionZ() + 6, 8.f, true, 10);
                hawk->ReplaceAllUnitFlags(UNIT_FLAG_UNINTERACTIBLE | UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC);
            }
        }
    }

    void OnUnitEnter(Unit* unit)
    {
        if (!unit)
            return;

        if (Unit* caster = at->GetCaster())
            if (caster->IsValidAttackTarget(unit))
                caster->CastSpell(unit, SPELL_HUNTER_DIRE_BEAST_HAWK_ATTACK, true);
    }

    void OnUnitExit(Unit* unit)
    {
        if (!unit)
            return;

        if (Unit* caster = at->GetCaster())
            if (unit->HasAura(SPELL_HUNTER_DIRE_BEAST_HAWK_ATTACK, caster->GetGUID()))
                unit->RemoveAura(SPELL_HUNTER_DIRE_BEAST_HAWK_ATTACK, caster->GetGUID());
    }
};

// AT: Wild Protector
struct at_hunter_wild_protector : AreaTriggerAI
{
    at_hunter_wild_protector(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger) { }

    void OnUnitEnter(Unit* unit) override
    {
        if (!unit)
            return;

        if (Unit* caster = at->GetCaster())
            if (caster->IsValidAssistTarget(unit))
                caster->CastSpell(unit, SPELL_HUNTER_WILD_PROTECTOR_BUFF, true);
    }

    void OnUnitExit(Unit* unit)
    {
        if (!unit)
            return;
        if (Unit* caster = at->GetCaster())
            if (unit->HasAura(SPELL_HUNTER_WILD_PROTECTOR_BUFF, caster->GetGUID()))
                unit->RemoveAura(SPELL_HUNTER_WILD_PROTECTOR_BUFF, caster->GetGUID());
    }
};

// 2392 - AT: Steeltrap
struct at_hunter_steeltrap : AreaTriggerAI
{
    at_hunter_steeltrap(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger) { }

    void OnUnitEnter(Unit* unit)
    {
        if (Unit* caster = at->GetCaster())
            if (caster->IsValidAttackTarget(unit))
            {
                caster->CastSpell(unit, SPELL_HUNTER_STEELTRAP_STUN, true);
                caster->CastSpell(unit, SPELL_HUNTER_STEELTRAP_BLEED, true);
                at->SetDuration(0);
            }
    }
};

// 19574 Bestial Wrath Last Update 8.0.1 build 28153 
class aura_hun_bestial_wrath : public AuraScript
{
    PrepareAuraScript(aura_hun_bestial_wrath);

    void HandleApply(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /* mode */)
    {
        if (Unit* caster = GetCaster())
        {
            if (Player* player = GetCaster()->ToPlayer())
                if (Pet* pet = player->GetPet())
                    pet->AddAura(SPELL_HUNTER_BESTIAL_WRATH, pet);

            if (caster->HasAura(SPELL_HUNTER_THE_BEAST_WITHIN))
                caster->CastSpell(caster, SPELL_HUNTER_THE_BEAST_WITHIN_BUFF, true);

            if (Aura* aura = caster->GetAura(SPELL_HUNTER_HAZE_OF_RAGE_POWER))
                caster->CastCustomSpell(SPELL_HUNTER_HAZE_OF_RAGE_BUFF, SPELLVALUE_BASE_POINT0, aura->GetEffect(EFFECT_0)->GetAmount(), caster, true);
        }
    }

    void HandleRemove(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /* mode */)
    {
        if (Unit* caster = GetCaster())
        {
            if (caster->HasAura(SPELL_HUNTER_THE_BEAST_WITHIN_BUFF))
                caster->RemoveAura(SPELL_HUNTER_THE_BEAST_WITHIN_BUFF);

            if (Player* player = GetCaster()->ToPlayer())
                if (Pet* pet = player->GetPet())
                    pet->RemoveAura(SPELL_HUNTER_THE_BEAST_WITHIN_BUFF);
        }
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(aura_hun_bestial_wrath::HandleApply, EFFECT_0, SPELL_AURA_ADD_PCT_MODIFIER, AURA_EFFECT_HANDLE_REAL);
        OnEffectRemove += AuraEffectRemoveFn(aura_hun_bestial_wrath::HandleRemove, EFFECT_0, SPELL_AURA_ADD_PCT_MODIFIER, AURA_EFFECT_HANDLE_REAL);
    }

};

// 185791 Wild Call Last Update 8.0.1 build 28153 
class aura_hun_wild_call_trigger : public AuraScript
{
    PrepareAuraScript(aura_hun_wild_call_trigger);

    void HandleApply(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /* mode */)
    {
        if (!GetCaster())
            return;

        if (Player* player = GetCaster()->ToPlayer())
        {
            int32 chargeCatId = sSpellMgr->GetSpellInfo(SPELL_HUNTER_BARBED_SHOT)->ChargeCategoryId;
            if (SpellCategoryEntry const* barbedShot = sSpellCategoryStore.LookupEntry(chargeCatId))
            {
                player->GetSpellHistory()->RestoreCharge(chargeCatId);
                player->GetSpellHistory()->ForceSendSetSpellCharges(barbedShot);
            }
        }
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(aura_hun_wild_call_trigger::HandleApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

// 191384 Aspect of the Beast Last Update 8.0.1 build 28153 
class aura_hun_aspect_of_the_beast : public AuraScript
{
    PrepareAuraScript(aura_hun_aspect_of_the_beast);

    void AfterApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* caster = GetCaster())
        {
            Unit::AuraApplicationMap const& appliedAuras = caster->GetAppliedAuras();
            for (Unit::AuraApplicationMap::const_iterator i = appliedAuras.begin(); i != appliedAuras.end(); ++i)
                if (i->second->GetBase()->GetId() != GetId())
                    i->second->GetBase()->RecalculateAmountOfEffects(true, true);
        }
    }

    void AfterRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* caster = GetCaster())
        {
            caster->AddDelayedEvent(200, [caster]()->void
            {
                if (caster->IsInWorld() && caster->IsAlive())
                {
                    Unit::AuraApplicationMap const& appliedAuras = caster->GetAppliedAuras();
                    for (Unit::AuraApplicationMap::const_iterator i = appliedAuras.begin(); i != appliedAuras.end(); ++i)
                        i->second->GetBase()->RecalculateAmountOfEffects(true, true);
                }
            });
        }
    }

    void Register() override
    {
        AfterEffectApply += AuraEffectApplyFn(aura_hun_aspect_of_the_beast::AfterApply, EFFECT_1, SPELL_AURA_ADD_PCT_MODIFIER, AURA_EFFECT_HANDLE_REAL);
        AfterEffectRemove += AuraEffectRemoveFn(aura_hun_aspect_of_the_beast::AfterRemove, EFFECT_1, SPELL_AURA_ADD_PCT_MODIFIER, AURA_EFFECT_HANDLE_REAL);
    }
};

// 265163 Wildfire Bomb Missile, 270336 Shrapnel Bomb Missile,
// 270327 Pheromone Bomb Missile, 271047 Volatile Bomb Missile
//Last Update 8.0.1 Build 28153
class spell_hun_wildfire_bomb_missile : public SpellScript
{
    PrepareSpellScript(spell_hun_wildfire_bomb_missile);

    void HandleDummy(SpellEffIndex /*effIndex*/)
    {
        if (Unit* caster = GetCaster())
        {

            if (Unit* target = GetHitUnit())
            {
                std::list<Unit*> targets;
                Trinity::AnyUnitInObjectRangeCheck check(target, 5.0f);
                Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> search(target, targets, check);
                Cell::VisitAllObjects(target, search, 5.0f);


                targets.remove_if([caster](WorldObject* objects) -> bool
                {
                    if (!objects)
                        return true;

                    if (!objects->ToUnit())
                        return true;

                    if (!caster->IsValidAttackTarget(objects->ToUnit()))
                        return true;

                    if (caster->HasInArc(float(M_PI / 3), objects->ToUnit()))
                        return false;

                    return true;
                });


                if (!targets.empty())
                {
                    for (auto castTarget : targets)
                    {
                        switch (GetSpellInfo()->Id)
                        {
                        case SPELL_HUNTER_SHRAPNEL_BOMB_MISSILE:
                            caster->CastSpell(castTarget, SPELL_HUNTER_SHRAPNEL_BOMB_EXPLODE, true);
                            caster->CastSpell(castTarget, SPELL_HUNTER_SHRAPNEL_BOMB_DOT, true);
                            break;
                        case SPELL_HUNTER_PHEROMONE_BOMB_MISSILE:
                            caster->CastSpell(castTarget, SPELL_HUNTER_PHEROMONE_BOMB_EXPLODE, true);
                            caster->CastSpell(castTarget, SPELL_HUNTER_PHEROMONE_BOMB_DOT, true);
                            break;
                        case SPELL_HUNTER_VOLATILE_BOMB_MISSILE:
                            caster->CastSpell(castTarget, SPELL_HUNTER_VOLATILE_BOMB_EXPLODE, true);
                            caster->CastSpell(castTarget, SPELL_HUNTER_VOLATILE_BOMB_DOT, true); 
                            break;
                        default:
                            caster->CastSpell(castTarget, SPELL_HUNTER_WILDFIRE_BOMB_EXPLODE, true);
                            caster->CastSpell(castTarget, SPELL_HUNTER_WILDFIRE_BOMB_DOT, true);
                            break;
                        }
                    }
                }
            }
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_hun_wildfire_bomb_missile::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

// 270339 Shrapnel Bomb Dot Last Update 8.0.1 Build 28153
class aura_hun_shrapnel_bomb_proc : public AuraScript
{
    PrepareAuraScript(aura_hun_shrapnel_bomb_proc);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetSpellInfo() && (eventInfo.GetSpellInfo()->Id == SPELL_HUNTER_MONGOOSE_BITE ||
            eventInfo.GetSpellInfo()->Id == SPELL_HUNTER_BUTCHERY || eventInfo.GetSpellInfo()->Id == SPELL_HUNTER_RAPTOR_STRIKE))
            return true;

        return false;
    }

    void HandleProc(AuraEffect* aurEff, ProcEventInfo& /*eventInfo*/)
    {
        PreventDefaultAction();

        if(Unit* caster = GetCaster())
            if(Unit* target = GetTarget())
                caster->CastSpell(target, SPELL_HUNTER_INTERNAL_BLEEDING, true);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_hun_shrapnel_bomb_proc::CheckProc);
        OnEffectProc += AuraEffectProcFn(aura_hun_shrapnel_bomb_proc::HandleProc, EFFECT_1, SPELL_AURA_DUMMY);
    }
};

// 271048 Volatile Bomb Explosion
//Last Update 8.0.1 Build 28153
class spell_hun_volatile_bomb_explode : public SpellScript
{
    PrepareSpellScript(spell_hun_volatile_bomb_explode);

    void HandleEffect(SpellEffIndex /*effIndex*/)
    {
        if (Unit* caster = GetCaster())
        {
            if (Unit* target = GetHitUnit())
            {
                if (Aura* aura = target->GetAura(SPELL_HUNTER_SERPENT_STING_SURVIVAL, caster->GetGUID()))
                {
                    caster->CastSpell(target, SPELL_HUNTER_VIOLENT_REACTION, true);
                    aura->RefreshDuration();
                }
            }
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_hun_volatile_bomb_explode::HandleEffect, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

// 264667 Primal Rage
//Last Update 8.0.1 Build 28153
class spell_hun_primal_rage : public SpellScript
{
    PrepareSpellScript(spell_hun_primal_rage);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        if (!sSpellMgr->GetSpellInfo(SPELL_HUNTER_INSANITY)
            || !sSpellMgr->GetSpellInfo(SPELL_MAGE_TEMPORAL_DISPLACEMENT)
            || !sSpellMgr->GetSpellInfo(SPELL_SHAMAN_EXHAUSTION)
            || !sSpellMgr->GetSpellInfo(SPELL_SHAMAN_SATED))
            return false;
        return true;
    }

    void RemoveInvalidTargets(std::list<WorldObject*>& targets)
    {
        targets.remove_if(Trinity::UnitAuraCheck(true, SPELL_HUNTER_INSANITY));
        targets.remove_if(Trinity::UnitAuraCheck(true, SPELL_MAGE_TEMPORAL_DISPLACEMENT));
        targets.remove_if(Trinity::UnitAuraCheck(true, SPELL_SHAMAN_EXHAUSTION));
        targets.remove_if(Trinity::UnitAuraCheck(true, SPELL_SHAMAN_SATED));
    }

    void ApplyDebuff()
    {
        if (Unit* target = GetHitUnit())
            target->CastSpell(target, SPELL_SHAMAN_SATED, true);
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_hun_primal_rage::RemoveInvalidTargets, EFFECT_ALL, TARGET_UNIT_CASTER_AREA_RAID);
        AfterHit += SpellHitFn(spell_hun_primal_rage::ApplyDebuff);
    }
};
// 263140 - Spirit Bond
class spell_hun_spirit_bond : public SpellScript
{
    PrepareSpellScript(spell_hun_spirit_bond);

    void HandleHit()
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();

        if (!caster || !target)
            return;

        Aura* aura = caster->GetAura(SPELL_HUNTER_MASTERY_SPIRIT_BOND);
        if (!aura)
            return;

        Player* player = caster->ToPlayer();
        if (!player)
            return;

        uint32 regen = CalculatePct(target->GetMaxHealth(), player->m_activePlayerData->Mastery * 0.1f);
        SetHitHeal(regen);
    }

    void Register() override
    {
        OnHit += SpellHitFn(spell_hun_spirit_bond::HandleHit);
    }
};

// 272651 - Command Pet (Every command spell)
class spell_hun_command_pet : public SpellScript
{
    PrepareSpellScript(spell_hun_command_pet);

    void HandleAfterCast()
    {
        if (Unit* caster = GetCaster())
            if (Player* player = caster->ToPlayer())
                if (Pet* pet = player->GetPet())
                    {
                        // Make the pet actually cast.
                        player->GetSession()->HandlePetActionHelper(pet, ObjectGuid::Empty, GetSpellInfo()->Id, ACT_ENABLED, pet->GetGUID(), Position());

                        // Set Command Pet cooldown.
                        player->GetSpellHistory()->StartCooldown(GetSpellInfo(), 0, GetSpell(), false);
                    }
    }

    void Register() override
    {
        AfterCast += SpellCastFn(spell_hun_command_pet::HandleAfterCast);
    }
};

// 204190 - Wild Protector
class aura_hun_wild_protector : public AuraScript
{
    PrepareAuraScript(aura_hun_wild_protector);

    void HandleApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* caster = GetCaster())
            if (Player* player = caster->ToPlayer())
                if (Pet* pet = player->GetPet())
                    pet->CastSpell(pet, SPELL_HUNTER_WILD_PROTECTOR_AT, true);
    }

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* caster = GetCaster())
            if (Player* player = caster->ToPlayer())
                if (Pet* pet = player->GetPet())
                    pet->RemoveAura(SPELL_HUNTER_WILD_PROTECTOR_AT);
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(aura_hun_wild_protector::HandleApply, EFFECT_0, SPELL_AURA_AREA_TRIGGER, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
        OnEffectRemove += AuraEffectRemoveFn(aura_hun_wild_protector::HandleRemove, EFFECT_0, SPELL_AURA_AREA_TRIGGER, AURA_EFFECT_HANDLE_REAL);
    }
};

// 264667 - Primal Rage
class aura_hun_primal_rage : public AuraScript
{
    PrepareAuraScript(aura_hun_primal_rage);

    void HandleApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetTarget();
        if (!caster || !target)
            return;

        if (target->HasAura(SPELL_SHAMAN_SATED) || target->HasAura(SPELL_SHAMAN_EXHAUSTION) || target->HasAura(SPELL_MAGE_TEMPORAL_DISPLACEMENT) ||
            target->HasAura(SPELL_HUNTER_INSANITY))
            target->RemoveAura(GetAura());
        else
        {
            if (Pet* pet = caster->ToPet())
                if (Unit* owner = pet->GetOwner())
                    if (Player* player = owner->ToPlayer())
                        if (player->GetTeamId() == TEAM_HORDE)
                            target->AddAura(SPELL_SHAMAN_SATED);
                        else
                            target->AddAura(SPELL_SHAMAN_EXHAUSTION);
        }
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(aura_hun_primal_rage::HandleApply, EFFECT_0, SPELL_AURA_MELEE_SLOW, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
    }
};

// 271014 - Wilfire Infusion
class aura_hun_wildfire_infusion : public AuraScript
{
    PrepareAuraScript(aura_hun_wildfire_infusion);

    void HandleApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* caster = GetCaster())
        {
            // Remove the old one.
            caster->RemoveAura(SPELL_HUNTER_WILDFIRE_INFUSION_SHRAPNEL);
            caster->RemoveAura(SPELL_HUNTER_WILDFIRE_INFUSION_PHEROMONE);
            caster->RemoveAura(SPELL_HUNTER_WILDFIRE_INFUSIN_VOLATILE);

            // Give one random bomb.
            int32 rand = irand(0, 2);
            switch (rand)
            {
                case 0:
                    caster->CastSpell(caster, SPELL_HUNTER_WILDFIRE_INFUSION_SHRAPNEL, true);
                    break;
                case 1:
                    caster->CastSpell(caster, SPELL_HUNTER_WILDFIRE_INFUSION_PHEROMONE, true);
                    break;
                case 2:
                    caster->CastSpell(caster, SPELL_HUNTER_WILDFIRE_INFUSIN_VOLATILE, true);
                    break;
                default:
                    caster->CastSpell(caster, SPELL_HUNTER_WILDFIRE_INFUSION_SHRAPNEL, true);
                    break;
            }
        }
    }

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* caster = GetCaster())
        {
            caster->RemoveAura(SPELL_HUNTER_WILDFIRE_INFUSION_SHRAPNEL);
            caster->RemoveAura(SPELL_HUNTER_WILDFIRE_INFUSION_PHEROMONE);
            caster->RemoveAura(SPELL_HUNTER_WILDFIRE_INFUSIN_VOLATILE);
        }
    }

    void Register() override
    {
        AfterEffectApply += AuraEffectApplyFn(aura_hun_wildfire_infusion::HandleApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        OnEffectRemove += AuraEffectRemoveFn(aura_hun_wildfire_infusion::HandleRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

// 270323, 270335, 271045 - Wildfire Infusion General
class spell_hun_wildfire_infusion_general : public SpellScript
{
    PrepareSpellScript(spell_hun_wildfire_infusion_general);

    void HandleAfterCast()
    {
        if (Unit* caster = GetCaster())
        {
            // Remove the old one.
            caster->RemoveAura(SPELL_HUNTER_WILDFIRE_INFUSION_SHRAPNEL);
            caster->RemoveAura(SPELL_HUNTER_WILDFIRE_INFUSION_PHEROMONE);
            caster->RemoveAura(SPELL_HUNTER_WILDFIRE_INFUSIN_VOLATILE);

            // Give one random bomb.
            int32 rand = irand(0, 2);
            switch (rand)
            {
                case 0:
                    caster->CastSpell(caster, SPELL_HUNTER_WILDFIRE_INFUSION_SHRAPNEL, true);
                    break;
                case 1:
                    caster->CastSpell(caster, SPELL_HUNTER_WILDFIRE_INFUSION_PHEROMONE, true);
                    break;
                case 2:
                    caster->CastSpell(caster, SPELL_HUNTER_WILDFIRE_INFUSIN_VOLATILE, true);
                    break;
                default:
                    caster->CastSpell(caster, SPELL_HUNTER_WILDFIRE_INFUSION_SHRAPNEL, true);
                    break;
            }
        }
    }

    void Register() override
    {
        AfterCast += SpellCastFn(spell_hun_wildfire_infusion_general::HandleAfterCast);
    }
};

// 162488 - Steel trap
class spell_hun_steeltrap : public SpellScript
{
    PrepareSpellScript(spell_hun_steeltrap);

    void HandlePrepare()
    {
        if (Unit* caster = GetCaster())
            if (AreaTrigger* at = caster->GetAreaTrigger(SPELL_HUNTER_STEELTRAP_AT))
                if (at)
                    at->Remove();
    }

    void Register() override
    {
        OnPrepare += SpellOnPrepareFn(spell_hun_steeltrap::HandlePrepare);
    }
};

// 162480 - Steel Trap Inmobilization
class aura_hun_steeltrap_inmobilization : public AuraScript
{
    PrepareAuraScript(aura_hun_steeltrap_inmobilization);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == SPELL_HUNTER_STEELTRAP_BLEED)
            return false;

        if (eventInfo.GetDamageInfo() && (eventInfo.GetDamageInfo()->GetDamageType() != HEAL && eventInfo.GetDamageInfo()->GetDamageType() != NODAMAGE))
        {
            Unit* caster = GetCaster();
            Unit* target = GetTarget();
            if (!caster || !target)
                return false;

            Aura* aura = GetAura();

            // Aura will be removed if the damage if greater or equal to 10% of the target maximun health.
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
        DoCheckProc += AuraCheckProcFn(aura_hun_steeltrap_inmobilization::CheckProc);
        OnProc += AuraProcFn(aura_hun_steeltrap_inmobilization::HandleProc);
    }
};

// 260331 - Birds of Prey
class aura_hun_birds_of_prey : public AuraScript
{
    PrepareAuraScript(aura_hun_birds_of_prey);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();
        Unit* target = eventInfo.GetActionTarget();
        if (!caster || !target)
            return false;

        if (Player* player = caster->ToPlayer())
            if (Pet* pet = player->GetPet())
                if (pet->GetTarget() == player->GetTarget())
                    if (eventInfo.GetSpellInfo() && (eventInfo.GetSpellInfo()->Id == SPELL_HUNTER_RAPTOR_STRIKE || eventInfo.GetSpellInfo()->Id == SPELL_HUNTER_MANGOOSE_BITE ||
                        eventInfo.GetSpellInfo()->Id == SPELL_HUNTER_BUTCHERY || eventInfo.GetSpellInfo()->Id == SPELL_HUNTER_CARVE))
                        return true;

        return false;
    }

    void HandleProc(ProcEventInfo& /*eventInfo*/)
    {
        if (Unit* caster = GetCaster())
        {
            if (Aura* aura = caster->GetAura(SPELL_HUNTER_COORDINATED_ASSAULT))
                aura->ModDuration(sSpellMgr->GetSpellInfo(SPELL_HUNTER_BIRDS_OF_PREY)->GetEffect(EFFECT_0).BasePoints);
            if (Player* player = caster->ToPlayer())
                if (Pet* pet = player->GetPet())
                    if (Aura* aura = pet->GetAura(SPELL_HUNTER_COORDINATED_ASSAULT))
                        aura->ModDuration(sSpellMgr->GetSpellInfo(SPELL_HUNTER_BIRDS_OF_PREY)->GetEffect(EFFECT_0).BasePoints);
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_hun_birds_of_prey::CheckProc);
        OnProc += AuraProcFn(aura_hun_birds_of_prey::HandleProc);
    }
};

// 193530 - Aspect of the Wild
class aura_hun_aspect_of_the_wild : public AuraScript
{
    PrepareAuraScript(aura_hun_aspect_of_the_wild);

    void HandleApply(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /* mode */)
    {
        if (Unit* caster = GetCaster())
            if (Aura* aura = caster->GetAura(SPELL_HUNTER_PRIMAL_INSTINCTS_POWER))
            {
                caster->CastCustomSpell(SPELL_HUNTER_PRIMAL_INSTINCTS_BUFF, SPELLVALUE_BASE_POINT0, aura->GetEffect(EFFECT_0)->GetAmount(), caster, true);
                caster->CastSpell(caster, SPELL_HUNTER_WILD_CALL_AURA, true);
            }
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(aura_hun_aspect_of_the_wild::HandleApply, EFFECT_0, SPELL_AURA_ADD_FLAT_MODIFIER, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
    }
};

// 205691 - Dire Beast: Basilisk
class spell_hun_dire_beast_basilisk : public SpellScript
{
    PrepareSpellScript(spell_hun_dire_beast_basilisk);

    void HandleHit()
    {
        Unit* caster = GetCaster();
        Unit* target = GetExplTargetUnit();
        if (!caster || !target)
            return;

        caster->Variables.Set<ObjectGuid>("EXPLICIT_TARGET", target->GetGUID());
        caster->SetInCombatWith(target);
    }

    void Register() override
    {
        OnHit += SpellHitFn(spell_hun_dire_beast_basilisk::HandleHit);
    }
};

// Last Update 8.0.1 Build 28153
// Called by Steady Focus - 193533
class spell_hun_steady_focus : public AuraScript
{
    PrepareAuraScript(spell_hun_steady_focus);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();      
        if (!caster)
            return false;

        switch (eventInfo.GetSpellInfo()->Id)
        {
        case SPELL_HUNTER_AIMED_SHOT:
        case SPELL_HUNTER_STEADY_SHOT:
        case SPELL_HUNTER_ARCANE_SHOT:
        case SPELL_HUNTER_BURSTING_SHOT:
        case SPELL_HUNTER_COUNTER_SHOT:
        case SPELL_HUNTER_CONCUSSIVE_SHOT:
        case SPELL_HUNTER_MULTISHOT:
        case SPELL_HUNTER_RAPID_FIRE_DAMAGE:
        case SPELL_HUNTER_MULTISHOT_RANK:
            return true;
        }
        
        return false;
    }

    void HandleOnProc(AuraEffect* auraEff, ProcEventInfo& procEventInfo)
    {
        Unit* owner = GetUnitOwner();
        if (!owner)
            return;

        if (!procEventInfo.GetDamageInfo())
            return;

        SpellInfo const* spellInfo = procEventInfo.GetDamageInfo()->GetSpellInfo();
        if (!spellInfo)
            return;

        if (spellInfo->Id == SPELL_HUNTER_STEADY_SHOT)
            owner->CastSpell(owner, SPELL_HUNTER_STEADY_FOCUS_BUFF, true);
        else
            owner->RemoveAura(SPELL_HUNTER_STEADY_FOCUS_BUFF);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_hun_steady_focus::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_hun_steady_focus::HandleOnProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

// Last Update 8.0.1 Build 28153
// Called by Lethal Shots - 260395
class spell_hun_lethal_shots : public AuraScript
{
    PrepareAuraScript(spell_hun_lethal_shots);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();
        if (!caster)
            return false;

        if (eventInfo.GetSpellInfo()->Id == SPELL_HUNTER_AIMED_SHOT || eventInfo.GetSpellInfo()->Id == SPELL_HUNTER_RAPID_FIRE_DAMAGE)
            return true;

        return false;
    }    

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_hun_lethal_shots::CheckProc);
    }
};

// Dragonscale Armor (PvP talent) 202589
// Last Update 8.0.1 Build 28153
class spell_hun_dragonscale_armor : public AuraScript
{
    PrepareAuraScript(spell_hun_dragonscale_armor);

    void CalculateAmount(AuraEffect const* aurEff, int32 & amount, bool & canBeRecalculated)
    {
        // Set absorbtion amount to unlimited
        amount = -1;
    }

    void Absorb(AuraEffect* aurEff, DamageInfo& dmgInfo, uint32& absorbAmount)
    {
        absorbAmount = 0;
        if (dmgInfo.GetDamageType() == DOT)
            absorbAmount = CalculatePct(dmgInfo.GetDamage(), GetSpellInfo()->GetEffect(EFFECT_1).BasePoints);
    }

    void Register() override
    {
        DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_hun_dragonscale_armor::CalculateAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
        OnEffectAbsorb += AuraEffectAbsorbFn(spell_hun_dragonscale_armor::Absorb, EFFECT_0);
    }
};

// 193526 - Trueshot
class spell_hun_trueshot : public SpellScript
{
    PrepareSpellScript(spell_hun_trueshot);

    void HandleHit()
    {
        Unit* caster = GetCaster();
        if (!caster || !caster->IsPlayer())
            return;

        if (SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(SPELL_HUNTER_AIMED_SHOT))
            caster->ToPlayer()->GetSpellHistory()->RestoreCharge(spellInfo->ChargeCategoryId);
    }

    void Register() override
    {
        OnHit += SpellHitFn(spell_hun_trueshot::HandleHit);
    }
};

// Last Update 8.0.1 Build 28153
// Called by Trick Shots - 257622 
class spell_hun_trick_shots_proc : public AuraScript
{
    PrepareAuraScript(spell_hun_trick_shots_proc);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();
        if (!caster)
            return false;

        if (eventInfo.GetSpellInfo()->Id == SPELL_HUNTER_AIMED_SHOT || eventInfo.GetSpellInfo()->Id == SPELL_HUNTER_RAPID_FIRE_DAMAGE)
            return true;

        return false;
    }

    void HandleOnProc(AuraEffect* auraEff, ProcEventInfo& eventInfo)
    {
        Unit* owner = GetUnitOwner();

        if (!owner)
            return;

        if (!eventInfo.GetDamageInfo())
            return;

        Unit* mainTarget = eventInfo.GetActionTarget();
        if (!mainTarget)
            return;

        SpellInfo const* spellInfo = eventInfo.GetDamageInfo()->GetSpellInfo();
        if (!spellInfo)
            return;

        SpellInfo const* trickShotInfo = sSpellMgr->GetSpellInfo(SPELL_HUNTER_TRICK_SHOT_AURA);
        if (!trickShotInfo)
            return;

        std::list<Unit*> targetList;
        Trinity::AnyUnitInObjectRangeCheck check(mainTarget, 10.0f);
        Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(mainTarget, targetList, check);
        Cell::VisitAllObjects(mainTarget, searcher, 10.0f);
        targetList.remove(mainTarget);

        targetList.remove_if([owner](WorldObject* objects) -> bool
        {
            if (!objects)
                return true;

            if (objects->ToUnit() && !owner->IsValidAttackTarget(objects->ToUnit()))
                return true;

            return false;
        });

        if (eventInfo.GetSpellInfo()->Id == SPELL_HUNTER_AIMED_SHOT)
        {
            if (targetList.size() > trickShotInfo->GetEffect(EFFECT_0).BasePoints)
                targetList.resize(trickShotInfo->GetEffect(EFFECT_0).BasePoints);
        }
        else if (eventInfo.GetSpellInfo()->Id == SPELL_HUNTER_RAPID_FIRE_DAMAGE)
            if (targetList.size() > trickShotInfo->GetEffect(EFFECT_2).BasePoints)
                targetList.resize(trickShotInfo->GetEffect(EFFECT_2).BasePoints);

        for (auto target : targetList)
        {
            SpellNonMeleeDamage damageLog = SpellNonMeleeDamage(owner, target, eventInfo.GetSpellInfo(), { eventInfo.GetSpellInfo()->GetSpellXSpellVisualId(), 0 }, eventInfo.GetSchoolMask());
            damageLog.damage = eventInfo.GetDamageInfo()->GetOriginalDamage();
            owner->CalculateSpellDamageTaken(&damageLog, damageLog.damage, eventInfo.GetSpellInfo());
            owner->DealDamageMods(owner, target, damageLog.damage, &damageLog.absorb);
            owner->SendSpellNonMeleeDamageLog(&damageLog);
            owner->DealDamage(owner, target, eventInfo.GetDamageInfo()->GetOriginalDamage());
        }

        if(eventInfo.GetSpellInfo()->Id == SPELL_HUNTER_AIMED_SHOT)
            Remove();
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_hun_trick_shots_proc::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_hun_trick_shots_proc::HandleOnProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

// 18036
struct at_hunter_resonating_arrow : AreaTriggerAI
{
    at_hunter_resonating_arrow(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger)
    {
    }

    enum ResonatingArrow
    {
        Debuff = 308498,
    };

    void OnUnitEnter(Unit* unit) override
    {
        Unit* caster = at->GetCaster();

        if (!caster || !unit)
            return;

        if (caster->IsValidAttackTarget(unit))
            caster->CastSpell(unit, Debuff, true);
    }

    void OnUnitExit(Unit* unit) override
    {
        Unit* caster = at->GetCaster();

        if (!caster || !unit)
            return;

        if (auto debuff = unit->GetAura(Debuff, caster->GetGUID()))
        {
            if (debuff->GetDuration() >= 4000)
                debuff->SetDuration(4000);
        }
    }
};


void AddSC_hunter_spell_scripts()
{
    new spell_hun_harpoon();
    new spell_hun_snake_hunter();
    new spell_hun_way_of_the_moknathal();
    new spell_hun_mongoose_bite();
    new spell_hun_ancient_hysteria();
    new spell_hun_invigoration();
    new spell_hun_masters_call();
    new spell_hun_misdirection();
    new spell_hun_misdirection_proc();
    new spell_hun_tame_beast();
    new spell_hun_chimera_shot();
    new spell_hun_a_murder_of_crows();
    new spell_hun_barrage();
    new spell_hun_beast_cleave();
    new spell_hun_beast_cleave_proc();
    new spell_hun_dire_beast();
    new spell_hun_kill_command();
    new spell_hun_kill_command_proc();
    RegisterSpellScript(spell_hun_piercing_shot);
    new spell_hun_arcane_shot();
    RegisterSpellScript(spell_hun_multi_shot);
    new spell_hun_marked_shot();
    new spell_hun_aspect_of_the_cheetah();
    new spell_hun_hunting_party();
    new spell_hun_hunters_mark();
    new spell_hun_marking_targets();
    new spell_hun_intimidation();
    new spell_hun_killer_cobra();
    new spell_hun_disengage();
    new spell_hun_farstrider();
    RegisterSpellScript(spell_hun_throwing_axes);
    new spell_hun_rangers_net();
    new spell_hun_sticky_bomb();
    new spell_hun_camouflage();
    new spell_hun_steady_shot();
    new spell_hun_spirit_mend();
    new spell_hun_master_marksman();
    new spell_hun_cobra_shot();
    new spell_hun_lock_and_load();
    new spell_hun_sentinel();
    new spell_hun_barber_shot();
    new spell_hun_flanking_strike();
    new spell_hun_flanking_strike_proc();
    new spell_hun_flanking_strike_proc_up();
    new spell_hun_mortal_wounds();
    new spell_hun_raptor_strike();
    RegisterSpellScript(spell_hun_carve);
    new spell_hun_true_aim();
	RegisterSpellScript(spell_bursting_shot);
    RegisterSpellScript(spell_hun_explosive_shot_detonate);
    RegisterSpellScript(spell_hun_exhilaration);
    RegisterSpellScript(aura_hun_volley);
    RegisterSpellScript(aura_trailblazer);
	RegisterSpellScript(aura_hun_viper_venom);
    RegisterSpellScript(spell_hun_steady_shot_SpellScript);
    RegisterSpellScript(aura_hun_lethal_shots);
    RegisterSpellScript(spell_hun_freezing_trap_take_damage_spellScript);
    new spell_hun_sur_kill_command();
	RegisterSpellScript(spell_hun_serpent_sting);
	RegisterSpellScript(spell_hun_mangoose_bite);
	RegisterSpellScript(spell_hun_multishot_aim);
	RegisterSpellScript(spell_hun_mending_bandage);
	RegisterSpellAndAuraScriptPair(spell_hun_aspect_of_the_turtle, aura_hun_aspect_of_the_turtle_aura);
	RegisterSpellScript(aura_hun_ranger_finesse);
	RegisterSpellAndAuraScriptPair(spell_hun_roar_of_sacrifice, aura_hun_roar_of_sacrifice);
	RegisterSpellScript(aura_hun_survival_tactics);
	RegisterSpellScript(spell_hun_aimed_shot);
	RegisterSpellScript(aura_hun_precise_shots);
	RegisterSpellScript(aura_hun_natural_mending);
    RegisterSpellScript(aura_hun_rapid_fire);
    RegisterSpellScript(spell_hun_rapid_fire_damage);
    RegisterSpellScript(aura_hun_stampede);
    RegisterSpellScript(aura_hun_spider_sting);
    RegisterSpellScript(aura_hun_mark_energize);
    RegisterSpellScript(aura_hun_bestial_wrath);
    RegisterSpellScript(aura_hun_wild_call_trigger);
    RegisterSpellScript(aura_hun_aspect_of_the_beast);
    RegisterSpellScript(spell_hun_wildfire_bomb_missile);
    RegisterSpellScript(aura_hun_shrapnel_bomb_proc);
    RegisterSpellScript(spell_hun_volatile_bomb_explode);
    RegisterSpellScript(spell_hun_spirit_bond);
    RegisterSpellAndAuraScriptPair(spell_hun_command_pet, aura_hun_primal_rage);
    RegisterSpellScript(aura_hun_wild_protector);
    RegisterSpellScript(aura_hun_primal_rage);
    RegisterSpellScript(aura_hun_wildfire_infusion);
    RegisterSpellScript(spell_hun_wildfire_infusion_general);
    RegisterSpellScript(spell_hun_steeltrap);
    RegisterSpellScript(aura_hun_steeltrap_inmobilization);
    RegisterSpellScript(aura_hun_birds_of_prey);
    RegisterSpellScript(aura_hun_aspect_of_the_wild);
    RegisterSpellScript(spell_hun_dire_beast_basilisk);
    RegisterSpellScript(spell_hun_steady_focus);
    RegisterSpellScript(spell_hun_lethal_shots);
    RegisterSpellScript(spell_hun_dragonscale_armor);
    RegisterSpellScript(spell_hun_trueshot);    
    RegisterSpellScript(spell_hun_trick_shots_proc); 

    // Spell Pet scripts
    new spell_hun_pet_heart_of_the_phoenix();
    new spell_hun_pet_thunderstomp();
    new spell_hun_pet_basic_attack();
    new spell_hun_pet_cobra_spit();
    RegisterCreatureAI(npc_pet_hunter_dire_basilisk);

    // Area Trigger scripts
    new at_hun_flare();
    new at_hun_explosive_trap();
    new at_hun_freezing_trap();
    new at_hun_tar_trap_activated();
    new at_hun_tar_trap_not_activated();
    new at_hun_binding_shot();
    new at_hun_caltrops();
    RegisterAreaTriggerAI(at_hun_sentinel);
	RegisterAreaTriggerAI(at_hunter_explosive_trap);
    RegisterAreaTriggerAI(at_hunter_stampede);
    RegisterAreaTriggerAI(at_hun_bloodseeker);
    RegisterAreaTriggerAI(at_hunter_hawk);
    RegisterAreaTriggerAI(at_hunter_wild_protector);
    RegisterAreaTriggerAI(at_hunter_steeltrap);
    RegisterAreaTriggerAI(at_hunter_resonating_arrow);

    // Playerscripts
    new PlayerScript_black_arrow();
    new PlayerScript_hunter_natural_mending();
    new Playerscript_hunter_lone_wolf();
}
