/*
 * Copyright (C) 2017-2018 AshamaneProject <https://github.com/AshamaneProject>
 * Copyright (C) 2008-2019 TrinityCore <http://www.trinitycore.org/>
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
#include "PhasingHandler.h"
#include "Player.h"
#include "ScriptMgr.h"
#include "Spell.h"
#include "SpellMgr.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"
#include "SpellHistory.h"
#include "Containers.h"
#include "SpellPackets.h"
#include "TemporarySummon.h"
#include "AreaTriggerPackets.h"
#include "spell_druid.h"

enum DruidSpells
{
    SPELL_DRUID_THRASH_BEAR_PERIODIC_DAMAGE         = 192090,
    SPELL_DRUID_BLESSING_OF_THE_ANCIENTS            = 202360,
    SPELL_DRUID_BLESSING_OF_ELUNE                   = 202737,
    SPELL_DRUID_BLESSING_OF_ANSHE                   = 202739,
    SPELL_DRUID_STARLORD_DUMMY                      = 202345,
    SPELL_DRUID_STARLORD_SOLAR                      = 202416,
    SPELL_DRUID_STARLORD_LUNAR                      = 202423,
    SPELL_DRUID_GLYPH_OF_STARS                      = 114301,
    SPELL_DRUID_CHOSEN_OF_ELUNE                     = 102560,
    SPELL_DRUID_BLUE_COLOR                          = 108268,
    SPELL_DRUID_SHADOWY_GHOST                       = 165114,
    SPELL_DRUID_GORE                                = 210706,
    SPELL_DRUID_YSERA_GIFT                          = 145108,
    SPELL_DRUID_YSERA_GIFT_CASTER_HEAL              = 145109,
    SPELL_DRUID_YSERA_GIFT_RAID_HEAL                = 145110,
    SPELL_DRUID_REJUVENATION                        = 774,
    SPELL_DRUID_HEALING_TOUCH                       = 5185,
    SPELL_DRUID_SWIFTMEND                           = 18562,
    SPELL_DRUID_TRAVEL_FORM                         = 783,
    SPELL_DRUID_FELINE_SWIFTNESS                    = 131768,
    SPELL_DRUID_SHRED                               = 5221,
    SPELL_DRUID_RAKE                                = 1822,
    SPELL_DRUID_RIP                                 = 1079,
    SPELL_DRUID_FEROCIOUS_BITE                      = 22568,
    SPELL_DRUID_MOONFIRE_CAT                        = 155625,
    SPELL_DRUID_SWIPE_CAT                           = 106785,
    SPELL_DRUID_SABERTOOTH                          = 202031,
    SPELL_DRUID_EMPOWERMENTS                        = 279708,
    SPELL_DRUID_SOLAR_EMPOWERMENT                   = 164545,
    SPELL_DRUID_LUNAR_EMPOWERMENT                   = 164547,
    SPELL_DRUID_STARSURGE_BALANCE                   = 78674,
    SPELL_DRUID_SOLAR_WRATH_BALANCE                 = 190984,
    SPELL_DRUID_LUNAR_STRIKE_BALANCE                = 194153,
    SPELL_DRUID_WILD_GROWTH                         = 48438,
    SPELL_DRUID_FERAL_AFFINITY_BALANCE              = 202157,
    SPELL_DRUID_FERAL_AFFINITY_GUARDIAN             = 202155,
    SPELL_DRUID_FERAL_AFFINITY_RESTO                = 197490,
    SPELL_DRUID_GUARDIAN_AFFINITY_BALANCE_RESTO     = 197491,
    SPELL_DRUID_GUARDIAN_AFFINITY_FERAL             = 217615,
    SPELL_DRUID_BALANCE_AFFINITY_FERAL_GUARDIAN     = 197488,
    SPELL_DRUID_BALANCE_AFFINITY_RESTO              = 197632,
    SPELL_DRUID_RESTO_ALL                           = 197492,
    SPELL_DRUID_MAIM                                = 22570,
    SPELL_DRUID_SAVAGE_ROAR                         = 52610,
    SPELL_DRUID_SAVAGE_ROAR_AURA                    = 62071,
    SPELL_DRUID_BRUTAL_SLASH                        = 202028,
    SPELL_DRUID_TRASH_CAT                           = 106830,
    SPELL_DRUID_CLEARCASTING_FERAL                  = 135700,
    SPELL_DRUID_GORE_AURA                           = 93622,
    SPELL_DRUID_GUARDIAN_OF_ELUNE_AURA              = 213680,
	SPELL_DRUID_ENTANGLING_ROOTS                    = 339,
	SPELL_DRUID_PREDATOR                            = 202021,
	SPELL_DRUID_TIGERS_FURY                         = 5217,
	SPELL_DRUID_SHOOTING_STARTS						= 202342,
	SPELL_DRUID_SHOOTING_START						= 202497,
    SPELL_DRUID_BRAMBLES                            = 203953,
    SPELL_DRUID_BRAMBLES_REFLECTION                 = 203958,
    SPELL_DRUID_BRAMBLES_REFLECTION_AOE             = 213709,
	SPELL_DRUID_SOLAR_RAY_SILENCE					= 97547,
    SPELL_DRUID_BLOOD_SCENT                         = 202022,
    SPELL_DRUID_SOUL_OF_THE_FOREST                  = 158476,
	SPELL_DRUID_ABUNDANCE                           = 207383,
	SPELL_DRUID_ABUNDANCE_BUFF                      = 207640,
	SPELL_DRUID_CENARION_WARD_HEAL                  = 102352,
    SPELL_DRUID_SOUL_OF_THE_FOREST_RESTO_BUFF       = 114108,
    SPELL_DRUID_REGROWTH                            = 8936,
    SPELL_DRUID_FERAL_FRENZY_DAMAGE                 = 274838,
	SPELL_DRUID_MOONKING_FORM_RANK2                 = 231042,
	SPELL_DRUID_OWLKIN_FRENZY                       = 157228,
    SPELL_DRUID_SPRING_BLOSSOMS                     = 207385,
    SPELL_DRUID_SPRING_BLOSSOMS_HEALS               = 207386,
    SPELL_DRUID_PHOTOSYNTHESIS                      = 274902,
	SPELL_DRUID_PHOTOSYNTHESIS_BUFF                 = 274906,
    SPELL_DRUID_LIFEBLOOM                           = 33763,
    SPELL_DRUID_CULTIVATION                         = 200390,
    SPELL_DRUID_CULTIVATION_HEAL                    = 200389,
    SPELL_DRUID_SOLAR_WRATH_AOE                     = 279729,
    SPELL_DRUID_STELLAR_DRIFT                       = 202354,
    SPELL_DRUID_STELLAR_DRIFT_CASTING               = 202461,
    SPELL_DRUID_CELESTIAL_GUARDIAN                  = 233754,
    SPELL_DRUID_CELESTIAL_GUARIDAN_BUFF             = 234081,
	SPELL_DRUID_DEN_MOTHER_TALENT					= 236180,
	SPELL_DRUID_DEN_MOTHER							= 236181,
	SPELL_DRUID_FRESH_WOUND							= 203224,
	SPELL_DRUID_RAKE_AURA							= 155722,
	SPELL_DRUID_FEROCIUS_BITE						= 236020,
	SPELL_DRUID_FEROCIUS_BITE_DEBUFF				= 236021,
	SPELL_DRUID_KING_OF_THE_JUNGLE					= 203052,
	SPELL_DRUID_KING_OF_THE_JUNGLE_BUFF				= 203059,
    SPELL_DRUID_TREE_OF_LIFE_DURATION               = 117679,
    SPELL_DRUID_DISENTAGLEMENT                      = 233673,
    SPELL_DRUID_DISENTAGLEMENT_EFFECT               = 233674,
    SPELL_DRUID_REVITALIZE                          = 203399,
    SPELL_DRUID_REVITALIZE_PROC                     = 203407,
    SPELL_DRUID_REVITALIZE_HEAL                     = 203406,
	SPELL_DRUID_NOURISH								= 203374,
	SPELL_DRUID_ENTANGLIN_BARK						= 247543,
	SPELL_DRUID_NATURE_GRASP						= 247563,
	SPELL_DRUID_ENTANGLING_ROOTS_2					= 170855,
	SPELL_DRUID_DEEP_ROOTS							= 233755,
	SPELL_DRUID_FOCUSED_GROWTH						= 203553,
	SPELL_DRUID_FOCUSED_GROWTH_EFFECT				= 203554,
	SPELL_DRUID_STARLORD_HASTE						= 279709,
	SPELL_DRUID_SAVAGE_MOMENTUM						= 205673,
	SPELL_DRUID_SKULL_BASH							= 106839,
	SPELL_DRUID_DYING_STARS							= 232546,
	SPELL_DRUID_DYING_STARS_ENERGIZE				= 232549,
	SPELL_DRUID_PRICKLING_TORNS						= 200549,
	SPELL_DRUID_PRICKLING_TORNS_DAMAGE				= 200550,
    SPELL_DRUID_PROTECTOR_OF_THE_GROVE              = 209730,
    SPELL_DRUID_PROTECTOR_OF_THE_GROVE_CAST         = 209731,
    SPELL_DRUID_FURY_OF_ELUNE_DAMAGE                = 211545,
	SPELL_DRUID_TRASH_GUARDIAN						= 77758,
	SPELL_DRUID_EARTHWARDEN_BUFF					= 203975,
	SPELL_DRUID_EARTHWARDEN							= 203974,
	SPELL_DRUID_GALATIC_GUARDIAN_ENERGIZE			= 213708,
	SPELL_DRUID_GALATIC_GUARIDAN_MOONFIRE			= 213708,
    SPELL_DRUID_LUNAR_BEAM_EFFECT                   = 204069,
    SPELL_DRUID_PULVERIZE                           = 80313,
    SPELL_DRUID_PULVERIZE_ACTIVATION                = 158790,
    SPELL_DRUID_PULVERIZE_BUFF                      = 158792,
    SPELL_DRUID_CLAN_DEFENDER                       = 213951,
    SPELL_DRUID_CLAN_DEFENDER_ALLIES                = 213947,
    SPELL_DRUID_CRESCENT_BURN                       = 200567,
    SPELL_DRUID_STARFALL                            = 191034,
    SPELL_DRUID_CELESTIAL_DOWNPOUR                  = 200726,
	SPELL_DRUID_WARRIOR_OF_ELUNE                    = 202425,
    SPELL_DRUID_NATURES_BALANCE_FREEZE              = 279649,
    SPELL_DRUID_NATURES_BALANCE_TICKER              = 279652,
    SPELL_DRUID_MASTER_SHAPESHIFTER                 = 236144,
    SPELL_DRUID_MASTER_SHAPESHIFTER_CAT             = 236188,
    SPELL_DRUID_MASTER_SHAPESHIFTER_HEAL            = 236185,
    SPELL_DRUID_MASTER_SHAPESHIFTER_MOONKIN         = 236187,
    SPELL_DRUID_GERMINATION                         = 155675,
    SPELL_DRUID_GERMINATION_REJUVENATION            = 155777,
    SPELL_DRUID_SHRED_RANK_2                        = 231063,
    SPELL_DRUID_SHRED_RANK_3                        = 231057,
    SPELL_DRUID_SOUL_OF_THE_FOREST_FERAL_ENERGIZE   = 114113,
    SPELL_DRUID_RAKE_RANK_2                         = 231052,
    SPELL_DRUID_FEROCIOUS_BITE_RANK_2               = 231056,
    SPELL_DRUID_MOONKING_FORM_AFFINITY              = 197625,
    SPELL_DRUID_SWIPE_RANK_2                        = 231283,
    SPELL_DRUID_REND_AND_TEAR                       = 204053,
    SPELL_DRUID_WALKING_DREAM                       = 278513,
    SPELL_DRUID_URSOC_ENDURANCE_POWER               = 280013,
    SPELL_DRUID_URSOC_ENDURANCE_BUFF                = 280165,
    SPELL_GUSHING_LACERATION                        = 278509,
    SPELL_DRUID_LIVELY_SPIRIT_POWER                 = 279642,
    SPELL_DRUID_LIVELY_SPIRIT_BUFF                  = 279648,
    SPELL_DRUID_LIVELY_SPIRIT_PROC                  = 279647,
    SPELL_DRUID_INNERVATE                           = 29166,
    SPELL_DRUID_BLOOD_FRENZY                        = 203962,
    SPELL_DRUID_BLODD_FRENZY_ENERGIZE               = 203961,
    SPELL_DRUID_WILD_FLESHRENDING                   = 279527,   
    SPELL_DRUID_IRON_JAWS                           = 276021,
    SPELL_DRUID_IRON_JAWS_BUFF                      = 276026,
};

enum ShapeshiftFormSpells
{
    SPELL_DRUID_BEAR_FORM                           = 5487,
    SPELL_DRUID_CAT_FORM                            = 768,
    SPELL_DRUID_MOONKIN_FORM                        = 24858,
    SPELL_DRUID_INCARNATION_TREE_OF_LIFE            = 33891,
    SPELL_DRUID_INCARNATION_KING_OF_JUNGLE          = 102543,
    SPELL_DRUID_INCARNATION_GUARDIAN_OF_URSOC       = 102558,
};

enum SoulOfTheForestSpells
{
    SPELL_DRUID_SOUL_OF_THE_FOREST_RESTO_TALENT  = 158478,
    SPELL_DRUID_SOUL_OF_THE_FOREST_RESTO         = 114108
};

enum EfflorescenceSpells
{
    SPELL_DRUID_EFFLORESCENCE_HEAL   = 81269,
    SPELL_DRUID_EFFLORESCENCE_DUMMY  = 81262
};

enum GoreSpells
{
    SPELL_DRUID_THRASH = 106832,
    SPELL_DRUID_MAUL = 6807,
    SPELL_DRUID_MOONFIRE = 8921,
    SPELL_DRUID_SWIPE = 213764
};

enum BalanceAffinitySpells
{
    SPELL_DRUID_ASTRAL_INFLUENCE        = 197524,
    SPELL_DRUID_MOONKIN_FORM_TALENT     = 197625,
    SPELL_DRUID_STARSURGE               = 197626,
    SPELL_DRUID_LUNAR_STRIKE            = 197628,
    SPELL_DRUID_SOLAR_WRATH             = 197629,
    SPELL_DRUID_SUNFIRE                 = 197630,
    SPELL_DRUID_ASTRAL_POWER            = 197911,
};

enum GuardianAffinitySpells
{
    SPELL_DRUID_THICK_HIDE              = 16931,
    SPELL_DRUID_MANGLE                  = 33917,
    SPELL_DRUID_THRASH_BEAR             = 77758,
    SPELL_DRUID_IRON_FUR                = 192081,
    SPELL_DRUID_FRENZIED_REGENERATION   = 22842
};

class druid_playerscript : public PlayerScript
{
public:
	druid_playerscript() : PlayerScript("druid_playerscript") {}

	void OnMapChanged(Player* player)
	{
		if (!player)
			return;

		if (player->GetSpecializationId() == TALENT_SPEC_DRUID_BEAR)
		{
			if (player->HasAura(SPELL_DRUID_DEN_MOTHER_TALENT))
				if (!player->GetAreaTrigger(SPELL_DRUID_DEN_MOTHER_TALENT))
					player->AddAura(SPELL_DRUID_DEN_MOTHER_TALENT);
            if (player->HasAura(SPELL_DRUID_CLAN_DEFENDER))
                if (!player->GetAreaTrigger(SPELL_DRUID_CLAN_DEFENDER))
                    player->AddAura(SPELL_DRUID_CLAN_DEFENDER);
		}
	}

    void OnSuccessfulSpellCast(Player* player, Spell* spell) override
    {
        if (!player || !spell)
            return;

        if (spell->IsTriggered() || spell->m_CastItem || spell->m_castFlagsEx & CAST_FLAG_EX_USE_TOY_SPELL)
            return;

        if (SpellInfo const* spellInfo = spell->GetSpellInfo())
        {
            if (!spellInfo->StartRecoveryTime || !spellInfo->StartRecoveryCategory)
                return;

            if (spellInfo->Id != SPELL_DRUID_INNERVATE && !spellInfo->HasAttribute(SPELL_ATTR2_RETAIN_ITEM_CAST) && !spellInfo->HasAura(SPELL_AURA_MOUNTED))
            {
                if (Aura* aura = player->GetAura(SPELL_DRUID_INNERVATE))
                {
                    if (Unit* caster = aura->GetCaster())
                    {
                        if (caster->HasAura(SPELL_DRUID_LIVELY_SPIRIT_PROC) || player->HasAura(SPELL_DRUID_LIVELY_SPIRIT_PROC, caster->GetGUID()))
                        {
                            if (caster->Variables.Exist("LIVELY_SPIRIT"))
                            {
                                if(spellInfo->StackAmount < caster->Variables.GetValue<uint32>("LIVELY_SPIRIT"))
                                    caster->Variables.Increment("LIVELY_SPIRIT");
                            }         
                            else
                                caster->Variables.Set<uint32>("LIVELY_SPIRIT", 1);
                        }
                    }
                }
            }
        }
    }

    void OnSetShapeshiftForm(Player* player, ShapeshiftForm form, ShapeshiftForm oldForm) override
    {
        if (player->HasAura(Druid::eLegendary::OathOfTheElderDruid) && !player->HasAura(Druid::eLegendary::OathOfTheElderDruidCD) && Druid::GetAffinityShapeshiftForm(player) == form)
        {
            uint32 duration = 10000;

            auto replacementHeartOfTheWildSpell = player->GetCastSpellInfo(sSpellMgr->GetSpellInfo(Druid::eDruid::HeartOfTheWild));

            if (auto aura = player->GetAura(replacementHeartOfTheWildSpell->Id))
                duration += aura->GetDuration();

            player->CastSpell(player, replacementHeartOfTheWildSpell->Id, CastSpellExtraArgs(TRIGGERED_FULL_MASK_NO_CD).AddSpellMod(SpellValueMod::SPELLVALUE_DURATION, duration));
            player->CastSpell(player, Druid::eLegendary::OathOfTheElderDruidCD, true);
        }

        if (oldForm == ShapeshiftForm::FORM_TRAVEL_FORM || oldForm == ShapeshiftForm::FORM_CAT_FORM)
        {
            if (auto tirelessPursuit = player->GetAuraEffect(340545, EFFECT_0))
            {
                player->CastSpell(player, 340546, CastSpellExtraArgs(true).AddSpellMod(SpellValueMod::SPELLVALUE_DURATION, tirelessPursuit->GetAmount()));
            }
        }
    }
};

// 210706 - Gore 7.3.5
 class aura_dru_gore : public AuraScript
 {
    PrepareAuraScript(aura_dru_gore);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetSpellInfo() && (eventInfo.GetSpellInfo()->Id == SPELL_DRUID_THRASH_BEAR || eventInfo.GetSpellInfo()->Id == SPELL_DRUID_MAUL ||
            eventInfo.GetSpellInfo()->Id == SPELL_DRUID_MOONFIRE || eventInfo.GetSpellInfo()->Id == SPELL_DRUID_SWIPE))
                return true;

        return false;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (Unit* caster = GetCaster())
            caster->CastSpell(caster, SPELL_DRUID_GORE_AURA, true);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_dru_gore::CheckProc);
        OnProc += AuraProcFn(aura_dru_gore::HandleProc);
    }
 };

// Thrash (Bear Form) - 77758, 106832
class spell_dru_thrash_bear : public SpellScript
{
    PrepareSpellScript(spell_dru_thrash_bear);

    void OnHit(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        caster->CastSpell(target, SPELL_DRUID_THRASH_BEAR_PERIODIC_DAMAGE, true);

		if (caster->HasAura(SPELL_DRUID_EARTHWARDEN))
			caster->CastSpell(caster, SPELL_DRUID_EARTHWARDEN_BUFF, true);

        if (caster->HasAura(SPELL_DRUID_BLOOD_FRENZY))
            caster->CastSpell(caster, SPELL_DRUID_BLODD_FRENZY_ENERGIZE, true);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_dru_thrash_bear::OnHit, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

// Thrash (Bear Form) periodic damage aura - 192090
class aura_dru_thrash_bear : public AuraScript
{
    PrepareAuraScript(aura_dru_thrash_bear);

    void HandleApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetTarget();
        if (!caster || !target)
            return;

        if (caster->HasSpell(SPELL_DRUID_PULVERIZE))
            if (Aura* aura = target->GetAura(SPELL_DRUID_THRASH_BEAR_PERIODIC_DAMAGE, caster->GetGUID()))
                if (aura->GetStackAmount() == 2)
                    caster->CastSpell(target, SPELL_DRUID_PULVERIZE_ACTIVATION, true);
    }

    void OnTick(AuraEffect const* auraEff)
    {
        if (Unit* caster = auraEff->GetCaster())
            if (Player* player = caster->ToPlayer())
                if (AuraEffect* aurEff = GetAura()->GetEffect(EFFECT_0))
                {
                    int32 dmg = player->m_unitData->AttackPower * GetSpellInfo()->GetEffect(EFFECT_0).BonusCoefficientFromAP;
                    dmg = (dmg * GetStackAmount()) / 5;
                    aurEff->SetDamage(dmg);

                    if (dmg > 0 && caster->HasAura(SPELL_DRUID_BLOOD_FRENZY))
                        caster->CastSpell(caster, SPELL_DRUID_BLODD_FRENZY_ENERGIZE, true);
                }
    }

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetTarget();
        if (!caster || !target)
            return;

        if (Aura* aura = target->GetAura(SPELL_DRUID_THRASH_BEAR_PERIODIC_DAMAGE, caster->GetGUID()))
        {
            if (aura->GetStackAmount() < 2)
                target->RemoveAura(SPELL_DRUID_PULVERIZE_ACTIVATION, caster->GetGUID());
        }
        else
            target->RemoveAura(SPELL_DRUID_PULVERIZE_ACTIVATION, caster->GetGUID());
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(aura_dru_thrash_bear::OnTick, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE);
        OnEffectApply += AuraEffectApplyFn(aura_dru_thrash_bear::HandleApply, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
        OnEffectRemove += AuraEffectRemoveFn(aura_dru_thrash_bear::HandleRemove, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE, AURA_EFFECT_HANDLE_REAL);
    }
};

// Blessing of the Ancients - 202360
class spell_dru_blessing_of_the_ancients : public SpellScript
{
    PrepareSpellScript(spell_dru_blessing_of_the_ancients);

    void HandleDummy(SpellEffIndex /*effIndex*/)
    {
        uint32 removeAura   = GetCaster()->HasAura(SPELL_DRUID_BLESSING_OF_ELUNE) ? SPELL_DRUID_BLESSING_OF_ELUNE : SPELL_DRUID_BLESSING_OF_ANSHE;
        uint32 addAura      = GetCaster()->HasAura(SPELL_DRUID_BLESSING_OF_ELUNE) ? SPELL_DRUID_BLESSING_OF_ANSHE : SPELL_DRUID_BLESSING_OF_ELUNE;

        GetCaster()->RemoveAurasDueToSpell(removeAura);
        GetCaster()->CastSpell(nullptr, addAura, true);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_dru_blessing_of_the_ancients::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

// Solar empowerment - 164545
class aura_dru_solar_empowerment : public AuraScript
{
    PrepareAuraScript(aura_dru_solar_empowerment);

    void OnApply(const AuraEffect* /* aurEff */, AuraEffectHandleModes /*mode*/)
    {
        if (GetTarget()->HasAura(SPELL_DRUID_STARLORD_DUMMY))
            GetTarget()->CastSpell(nullptr, SPELL_DRUID_STARLORD_SOLAR, true);
    }

    void OnRemove(const AuraEffect* /* aurEff */, AuraEffectHandleModes /*mode*/)
    {
        GetTarget()->RemoveAurasDueToSpell(SPELL_DRUID_STARLORD_SOLAR);
    }

	bool HandleCheckProc(ProcEventInfo& eventInfo)
	{
		return false;
	}

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(aura_dru_solar_empowerment::OnApply, EFFECT_0, SPELL_AURA_ADD_PCT_MODIFIER, AURA_EFFECT_HANDLE_REAL);
        OnEffectRemove += AuraEffectRemoveFn(aura_dru_solar_empowerment::OnRemove, EFFECT_0, SPELL_AURA_ADD_PCT_MODIFIER, AURA_EFFECT_HANDLE_REAL);
		DoCheckProc += AuraCheckProcFn(aura_dru_solar_empowerment::HandleCheckProc);
    }
};

// Lunar empowerment - 164547
class aura_dru_lunar_empowerment : public AuraScript
{
    PrepareAuraScript(aura_dru_lunar_empowerment);

    void OnApply(const AuraEffect* /* aurEff */, AuraEffectHandleModes /*mode*/)
    {
        if (GetTarget()->HasAura(SPELL_DRUID_STARLORD_DUMMY))
            GetTarget()->CastSpell(nullptr, SPELL_DRUID_STARLORD_LUNAR, true);
    }

    void OnRemove(const AuraEffect* /* aurEff */, AuraEffectHandleModes /*mode*/)
    {
        GetTarget()->RemoveAurasDueToSpell(SPELL_DRUID_STARLORD_LUNAR);
    }

	bool HandleCheckProc(ProcEventInfo& eventInfo)
	{
		return false;
	}

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(aura_dru_lunar_empowerment::OnApply, EFFECT_0, SPELL_AURA_ADD_PCT_MODIFIER, AURA_EFFECT_HANDLE_REAL);
        OnEffectRemove += AuraEffectRemoveFn(aura_dru_lunar_empowerment::OnRemove, EFFECT_0, SPELL_AURA_ADD_PCT_MODIFIER, AURA_EFFECT_HANDLE_REAL);
		DoCheckProc += AuraCheckProcFn(aura_dru_lunar_empowerment::HandleCheckProc);
    }
};
//7.3.2.25549 END

// Efflorescence - 145205
class spell_dru_efflorescence : public SpellScript
{
    PrepareSpellScript(spell_dru_efflorescence);

    enum eCreature
    {
        NPC_EFFLORESCENCE = 47649
    };

    void HandleSummon()
    {
        if (Unit* caster = GetCaster())
            if (Creature* efflorescence = caster->GetSummonedCreatureByEntry(NPC_EFFLORESCENCE))
                efflorescence->DespawnOrUnsummon();
    }

    void Register() override
    {
        OnCast += SpellCastFn(spell_dru_efflorescence::HandleSummon);
    }
};

// Efflorescence (Aura) - 81262
class spell_dru_efflorescence_aura : public AuraScript
{
    PrepareAuraScript(spell_dru_efflorescence_aura);

    void HandleHeal(AuraEffect const* /*aurEff*/)
    {
        if (Unit* caster = GetCaster())
            if (caster->GetOwner())
                caster->GetOwner()->CastSpell(caster->GetPosition(), SPELL_DRUID_EFFLORESCENCE_HEAL, true);
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_dru_efflorescence_aura::HandleHeal, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

// Efflorescence (Heal) - 81269
class spell_dru_efflorescence_heal : public SpellScript
{
    PrepareSpellScript(spell_dru_efflorescence_heal);

    void SortTargets(std::list<WorldObject*>& targets)
    {
        targets.sort(Trinity::HealthPctOrderPred());

        if (targets.size() > 3)
            targets.resize(3);
    }

	void HandleHit()
	{
		Unit* caster = GetCaster();
		Unit* target = GetHitUnit();
		if (!caster || !target)
			return;

		if (caster->HasAura(SPELL_DRUID_SPRING_BLOSSOMS))
			caster->CastSpell(target, SPELL_DRUID_SPRING_BLOSSOMS_HEALS, true);

        // Disentanglement
        if (caster->HasAura(SPELL_DRUID_DISENTAGLEMENT))
            caster->CastSpell(target, SPELL_DRUID_DISENTAGLEMENT_EFFECT, true);
	}

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_dru_efflorescence_heal::SortTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ALLY);
		OnHit += SpellHitFn(spell_dru_efflorescence_heal::HandleHit);
    }
};

// Primal Fury - 159286
// @Version : 7.1.0.22908
class spell_dru_primal_fury : public SpellScriptLoader
{
public:
    spell_dru_primal_fury() : SpellScriptLoader("spell_dru_primal_fury") { }

    class spell_dru_primal_fury_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_dru_primal_fury_AuraScript);

        bool CheckProc(ProcEventInfo& eventInfo)
        {
            if (!eventInfo.GetProcSpell())
                return false;

            if ((eventInfo.GetHitMask() & PROC_HIT_CRITICAL) && eventInfo.GetProcSpell()->m_comboPointsEnergized)
                return true;

            return false;
        }

        void Register() override
        {
            DoCheckProc += AuraCheckProcFn(spell_dru_primal_fury_AuraScript::CheckProc);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_dru_primal_fury_AuraScript();
    }
};

enum PredatorySwiftnessSpells
{
    SPELL_DRUID_PREDATORY_SWIFTNESS       = 16974,
    SPELL_DRUID_PREDATORY_SWIFTNESS_AURA  = 69369
};

enum LifebloomSpells
{
    SPELL_DRUID_LIFEBLOOM_FINAL_HEAL = 33778
};

// Lifebloom - 33763
class spell_dru_lifebloom : public SpellScript
{
	PrepareSpellScript(spell_dru_lifebloom);

	void HandleHit()
	{
		Unit* caster = GetCaster();
		Unit* target = GetHitUnit();
		if (!caster || !target)
			return;

		if (caster->HasAura(SPELL_DRUID_FOCUSED_GROWTH))
			caster->CastSpell(target, SPELL_DRUID_FOCUSED_GROWTH_EFFECT, true);

		if (caster->HasAura(SPELL_DRUID_PHOTOSYNTHESIS) && caster->GetGUID() == target->GetGUID())
			caster->CastSpell(caster, SPELL_DRUID_PHOTOSYNTHESIS_BUFF, true);
	}

	void Register() override
	{
		OnHit += SpellHitFn(spell_dru_lifebloom::HandleHit);
	}
};

class aura_dru_lifebloom : public AuraScript
{
	PrepareAuraScript(aura_dru_lifebloom);

	void AfterRemove(AuraEffect const* /* aurEff */, AuraEffectHandleModes /*mode*/)
	{
		Unit* caster = GetCaster();
		Unit* target = GetTarget();
		if (!caster || !target)
			return;

		// Final heal only on duration end
		AuraRemoveMode removeMode = GetTargetApplication()->GetRemoveMode();
		if (removeMode != AURA_REMOVE_BY_EXPIRE && removeMode != AURA_REMOVE_BY_ENEMY_SPELL)
			return;

		caster->CastSpell(target, SPELL_DRUID_LIFEBLOOM_FINAL_HEAL, true);

        target->RemoveAura(SPELL_DRUID_FOCUSED_GROWTH_EFFECT, caster->GetGUID());
        caster->RemoveAura(SPELL_DRUID_PHOTOSYNTHESIS_BUFF);
	}

	void Register() override
	{
		AfterEffectRemove += AuraEffectRemoveFn(aura_dru_lifebloom::AfterRemove, EFFECT_0, SPELL_AURA_PERIODIC_HEAL, AURA_EFFECT_HANDLE_REAL);
	}
};

// Berserk - 106951
// @Version : 7.1.0.22908
class spell_dru_berserk : public SpellScriptLoader
{
public:
    spell_dru_berserk() : SpellScriptLoader("spell_dru_berserk") { }

    class spell_dru_berserk_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_dru_berserk_SpellScript);

        SpellCastResult CheckCast()
        {
            Unit* caster = GetCaster();
            if (caster->GetShapeshiftForm() != FORM_CAT_FORM)
                return SPELL_FAILED_ONLY_SHAPESHIFT;

            return SPELL_CAST_OK;
        }

        void Register() override
        {
            OnCheckCast += SpellCheckCastFn(spell_dru_berserk_SpellScript::CheckCast);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_dru_berserk_SpellScript();
    }
};

enum SunfireSpells
{
    SPELL_DRUID_SUNFIRE_DAMAGE = 164815
};

// Sunfire - 93402
// @Version : 7.1.0.22908
class spell_dru_sunfire : public SpellScriptLoader
{
public:
    spell_dru_sunfire() : SpellScriptLoader("spell_dru_sunfire") {}

    class spell_dru_sunfire_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_dru_sunfire_SpellScript);

        void HandleDamage(SpellEffIndex /*effIndex*/)
        {
            Unit* caster = GetCaster();
            Unit* target = GetHitUnit();
            if (!target || !caster)
                return;

            caster->CastSpell(target, SPELL_DRUID_SUNFIRE_DAMAGE, true);
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_dru_sunfire_SpellScript::HandleDamage, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_dru_sunfire_SpellScript();
    }
};

// Ferocious Bite - 22568
class spell_dru_ferocious_bite : public SpellScript
{
    PrepareSpellScript(spell_dru_ferocious_bite);

    void HandlePrepare()
    {
        if (Unit* caster = GetCaster())
            currentEnergy = caster->GetPower(POWER_ENERGY);
    }

    void HandleOnTakePower(SpellPowerCost& powerCost)
    {
        if (powerCost.Power == POWER_COMBO_POINTS)
        {
            comboPoints = powerCost.Amount;
        }
        if (powerCost.Power == POWER_ENERGY)
            energy = std::min((uint32)currentEnergy - powerCost.Amount, (uint32)25);
    }

    void CalcCrit(Unit const* victim, float& chance)
    {
        if (Unit* caster = GetCaster())
            if (caster->HasAura(SPELL_DRUID_CAT_FORM) && caster->HasAura(SPELL_DRUID_BLOOD_SCENT) && victim->HasAuraState(AURA_STATE_BLEED))
                chance += sSpellMgr->GetSpellInfo(SPELL_DRUID_BLOOD_SCENT)->GetEffect(EFFECT_0).BasePoints;
    }

    void CalcDmg(SpellEffIndex /*effIndex*/)
    {
		Unit* caster = GetCaster();
		Unit* target = GetHitUnit();
		if (!caster || !target)
			return;

        int32 damage = GetHitDamage();

        // Calculate damage per Combo Points
        AddPct(damage, 20 * comboPoints);

        //damage += caster->m_unitData->AttackPower * 6.8f;

        // Calculate additional consumed Energy. The spell cost is 25 Energy, so the damage is incremented by additional 25.
        float proportion = float(energy / sSpellMgr->GetSpellInfo(SPELL_DRUID_FEROCIOUS_BITE)->GetEffect(EFFECT_1).BasePoints);
        damage += CalculatePct(damage, proportion * 100);

        if (auto tasteForBlood = caster->GetAuraEffect(340682, EFFECT_0))
        {
            if (tasteForBlood->ConduitRankEntry)
            {
                auto AddPctIfHasDot([&](uint32 bleed) -> void
                {
                    if (target->HasAura(bleed, caster->GetGUID()))
                    {
                        AddPct(damage, tasteForBlood->ConduitRankEntry->AuraPointsOverride);
                    }
                });

                AddPctIfHasDot(SPELL_DRUID_RIP);
                AddPctIfHasDot(SPELL_DRUID_TRASH_CAT);
                AddPctIfHasDot(SPELL_DRUID_RAKE_AURA);
            }
        }

        SetHitDamage(damage);

        /// Updated 9.2.5.44061
        /// Increase rip duration per combo spent
        if (caster->HasAura(SPELL_DRUID_SABERTOOTH))
            if (Aura* rip = target->GetAura(SPELL_DRUID_RIP, caster->GetGUID()))
                rip->ModDuration(comboPoints * 1000);

		// Ferocius Bite
		if (caster->HasAura(SPELL_DRUID_FEROCIUS_BITE) && comboPoints == 5 && (target->IsPlayer() || caster->GetMap()->IsBattlegroundOrArena())) //Can be used in Alterac Valley agains boss
			caster->CastSpell(target, SPELL_DRUID_FEROCIUS_BITE_DEBUFF, true);

        // Soul of the Forest.
        if (caster->HasAura(SPELL_DRUID_SOUL_OF_THE_FOREST))
            caster->CastCustomSpell(SPELL_DRUID_SOUL_OF_THE_FOREST_FERAL_ENERGIZE, SPELLVALUE_BASE_POINT0, comboPoints * sSpellMgr->GetSpellInfo(SPELL_DRUID_SOUL_OF_THE_FOREST)->GetEffect(EFFECT_0).BasePoints, caster, true);

        // Iron Jaws.
        if (Aura* aura = caster->GetAura(SPELL_DRUID_IRON_JAWS))
            if (roll_chance_i(sSpellMgr->GetSpellInfo(SPELL_DRUID_IRON_JAWS)->GetEffect(EFFECT_1).BasePoints * comboPoints))
                caster->CastCustomSpell(SPELL_DRUID_IRON_JAWS_BUFF, SPELLVALUE_BASE_POINT0, aura->GetEffect(EFFECT_0)->GetAmount(), caster, true);
    }

    void Register() override
    {
        OnPrepare += SpellOnPrepareFn(spell_dru_ferocious_bite::HandlePrepare);
        OnCalcCritChance += SpellOnCalcCritChanceFn(spell_dru_ferocious_bite::CalcCrit);
        OnTakePower += SpellOnTakePowerFn(spell_dru_ferocious_bite::HandleOnTakePower);
        OnEffectHitTarget += SpellEffectFn(spell_dru_ferocious_bite::CalcDmg, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }

private:
    int32 comboPoints = 0;
    uint32 energy = 0;
    uint32 currentEnergy = 0;
};

// Dash - 1850
// @Version : 7.1.0.22908
class spell_dru_dash : public SpellScriptLoader
{
public:
    spell_dru_dash() : SpellScriptLoader("spell_dru_dash") { }

    class spell_dru_dash_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_dru_dash_AuraScript);

        void CalculateAmount(AuraEffect const* /*aurEff*/, int32& amount, bool& /*canBeRecalculated*/)
        {
            // do not set speed if not in cat form
            if (GetUnitOwner()->GetShapeshiftForm() != FORM_CAT_FORM)
                amount = 0;
        }

        void Register() override
        {
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_dru_dash_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_MOD_INCREASE_SPEED);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_dru_dash_AuraScript();
    }
};

// 52610 - Savage Roar
class spell_dru_savage_roar : public SpellScript
{
    PrepareSpellScript(spell_dru_savage_roar);

    void HandleTakePower(SpellPowerCost& powerCost)
    {
        if (powerCost.Power == POWER_COMBO_POINTS)
        {
            comboPoints = powerCost.Amount;
        }
    }

    void HandleEffectHitTarget(SpellEffIndex /*effIndex*/)
    {
        if (Unit* caster = GetCaster())
            // Soul of the Forest.
            if (caster->HasAura(SPELL_DRUID_SOUL_OF_THE_FOREST))
                caster->CastCustomSpell(SPELL_DRUID_SOUL_OF_THE_FOREST_FERAL_ENERGIZE, SPELLVALUE_BASE_POINT0, comboPoints * sSpellMgr->GetSpellInfo(SPELL_DRUID_SOUL_OF_THE_FOREST)->GetEffect(EFFECT_0).BasePoints, caster, true);
    }

    void Register() override
    {
        OnTakePower += SpellOnTakePowerFn(spell_dru_savage_roar::HandleTakePower);
        OnEffectHitTarget += SpellEffectFn(spell_dru_savage_roar::HandleEffectHitTarget, EFFECT_0, SPELL_EFFECT_DUMMY);
    }

private:
    uint8 comboPoints = 0;
};

// 52610 - Aura Savage Roar
class aura_dru_savage_roar : public AuraScript
{
    PrepareAuraScript(aura_dru_savage_roar);

    void HandleApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* caster = GetCaster())
        {
            if (caster->Variables.Exist("LastComboPointsUsed"))
            {
                int32 ComboPoints = caster->Variables.GetValue("LastComboPointsUsed", 0);

                GetAura()->SetMaxDuration(6 * (ComboPoints + 1) * IN_MILLISECONDS);
                GetAura()->SetDuration(6 * (ComboPoints + 1) * IN_MILLISECONDS);
                caster->CastSpell(caster, SPELL_DRUID_SAVAGE_ROAR_AURA, true);
            }
        }
    }

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* caster = GetCaster())
            caster->RemoveAura(SPELL_DRUID_SAVAGE_ROAR_AURA);
    }

    void Register() override
    {
        AfterEffectApply += AuraEffectApplyFn(aura_dru_savage_roar::HandleApply, EFFECT_1, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
        AfterEffectRemove += AuraEffectRemoveFn(aura_dru_savage_roar::HandleRemove, EFFECT_1, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

enum SurvivalInstinctsSpells
{
    SPELL_DRUID_SURVIVAL_INSTINCTS = 50322
};

// Survival Instincts - 61336
// Last Update 8.0.1 Build 28153
class spell_dru_survival_instincts : public SpellScriptLoader
{
public:
    spell_dru_survival_instincts() : SpellScriptLoader("spell_dru_survival_instincts") { }

    class spell_dru_survival_instincts_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_dru_survival_instincts_AuraScript);

        void AfterApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if (Unit* caster = GetCaster())
            {
                if(AuraEffect* aurEff = caster->GetAuraEffect(SPELL_DRUID_URSOC_ENDURANCE_POWER, EFFECT_0))
                    caster->CastCustomSpell(SPELL_DRUID_URSOC_ENDURANCE_BUFF, SPELLVALUE_BASE_POINT0, aurEff->GetAmount(), caster, true);

                caster->CastSpell(caster, SPELL_DRUID_SURVIVAL_INSTINCTS, true);
            }
        }

        void AfterRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if (Unit* target = GetTarget())
                target->RemoveAurasDueToSpell(SPELL_DRUID_SURVIVAL_INSTINCTS);
        }

        void Register() override
        {
            AfterEffectApply += AuraEffectApplyFn(spell_dru_survival_instincts_AuraScript::AfterApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_CHANGE_AMOUNT_MASK);
            AfterEffectRemove += AuraEffectRemoveFn(spell_dru_survival_instincts_AuraScript::AfterRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_CHANGE_AMOUNT_MASK);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_dru_survival_instincts_AuraScript();
    }
};

// Swift Flight Form (Passive) - 40121
// @Version : 7.1.0.22908
class spell_dru_swift_flight_passive : public SpellScriptLoader
{
public:
    spell_dru_swift_flight_passive() : SpellScriptLoader("spell_dru_swift_flight_passive") { }

    class spell_dru_swift_flight_passive_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_dru_swift_flight_passive_AuraScript);

        bool Load() override
        {
            return GetCaster()->GetTypeId() == TYPEID_PLAYER;
        }

        void CalculateAmount(AuraEffect const* /*aurEff*/, int32& amount, bool & /*canBeRecalculated*/)
        {
            if (Player* caster = GetCaster()->ToPlayer())
                if (caster->GetSkillValue(SKILL_RIDING) >= 375)
                    amount = 310;
        }

        void Register() override
        {
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_dru_swift_flight_passive_AuraScript::CalculateAmount, EFFECT_1, SPELL_AURA_MOD_INCREASE_VEHICLE_FLIGHT_SPEED);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_dru_swift_flight_passive_AuraScript();
    }
};

// Wild growth - 48438
// @Edit : Soul of the Forest - 114108, Tree of Life - 33891
// @Version : 7.1.0.22908
class spell_dru_wild_growth : public SpellScript
{
    PrepareSpellScript(spell_dru_wild_growth);

    bool m_HasSoulOfTheForest = false;

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        Unit* caster = GetCaster();
        if (!caster)
            return;

        uint8 maxTargets = 5;
        if (!maxTargets)
            return;

        // If Tree of Life is activated we increase 2 targets
        if (caster->HasAura(SPELL_DRUID_INCARNATION_TREE_OF_LIFE))
            maxTargets += 2;

        if (targets.size() > maxTargets)
        {
            targets.sort(Trinity::HealthPctOrderPred());
            targets.resize(maxTargets);
        }
    }

    void HandleAfterHit()
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!target)
            return;

        // If soul of the forest is activated we increase the heal by 50%
        if (AuraEffect* wildGrowth = target->GetAuraEffect(GetSpellInfo()->Id, EFFECT_0, caster->GetGUID()))
        {
            if (caster->HasAura(SPELL_DRUID_SOUL_OF_THE_FOREST_RESTO) || m_HasSoulOfTheForest)
            {
                uint8 SoulofTheForestBonus = GetSpellInfo()->GetEffect(EFFECT_2).BasePoints;
                if (!SoulofTheForestBonus)
                    return;

                wildGrowth->SetDamage(wildGrowth->GetDamage() + CalculatePct(wildGrowth->GetDamage(), SoulofTheForestBonus));
                m_HasSoulOfTheForest = true;
                caster->RemoveAura(SPELL_DRUID_SOUL_OF_THE_FOREST_RESTO);
            }
        }
    }

    void Register() override
    {
        AfterHit += SpellHitFn(spell_dru_wild_growth::HandleAfterHit);
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_dru_wild_growth::FilterTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ALLY);
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_dru_wild_growth::FilterTargets, EFFECT_1, TARGET_UNIT_DEST_AREA_ALLY);
    }
};

// 48438 - Wild growth
class aura_dru_wild_growth : public AuraScript
{
    PrepareAuraScript(aura_dru_wild_growth);

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
        Unit* caster = GetCaster();
        Unit* owner = GetUnitOwner();
        if (!caster || !owner)
            return;

        if (caster->HasAura(SPELL_DRUID_PHOTOSYNTHESIS) && caster->GetGUID() != owner->GetGUID() && owner->HasAura(SPELL_DRUID_LIFEBLOOM, caster->GetGUID()) &&
            roll_chance_i(sSpellMgr->GetSpellInfo(SPELL_DRUID_PHOTOSYNTHESIS)->GetEffect(EFFECT_1).BasePoints))
            owner->RemoveAurasDueToSpell(SPELL_DRUID_LIFEBLOOM, caster->GetGUID(), 0, AURA_REMOVE_BY_EXPIRE);
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(aura_dru_wild_growth::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_HEAL);
    }
};

enum MoonfireSpells
{
    SPELL_DRUID_MOONFIRE_DAMAGE = 164812
};

// 8921 - Moonfire Aura
class spell_dru_moonfire : public SpellScript
{
	PrepareSpellScript(spell_dru_moonfire);

	void HandleOnHit(SpellEffIndex /*effIndex*/)
	{
		Unit* caster = GetCaster();
		Unit* target = GetHitUnit();
		if (caster != target)
			caster->CastSpell(target, SPELL_DRUID_MOONFIRE_DAMAGE, true);
	}

	void Register() override
	{
		OnEffectHitTarget += SpellEffectFn(spell_dru_moonfire::HandleOnHit, EFFECT_0, SPELL_EFFECT_DUMMY);
	}
};

enum OmenOfClaritySpells
{
    SPELL_DRUID_CLEARCASTING       = 16870,
    SPELL_DRUID_MOMENT_OF_CLARITY  = 155577,
    SPELL_DRUID_OMEN_OF_CLARITY    = 113043
};

// Omen of Clarity - 113043
// @Called : Lifebloom - 33763, Moment of Clarity - 155577
// @Version : 7.1.0.22908
class spell_dru_omen_of_clarity : public SpellScriptLoader
{
public:
    spell_dru_omen_of_clarity() : SpellScriptLoader("spell_dru_omen_of_clarity") { }

    class spell_dru_omen_of_clarity_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_dru_omen_of_clarity_AuraScript);

        void HandleEffectPeriodic(const AuraEffect* /*aurEff*/)
        {
            Unit* caster = GetCaster();
            if (!caster)
                return;

            if (caster->HasAura(SPELL_DRUID_OMEN_OF_CLARITY))
            {
                if (roll_chance_i(4) && !caster->HasAura(SPELL_DRUID_CLEARCASTING))
                {
                    caster->CastSpell(caster, SPELL_DRUID_CLEARCASTING, true);

                    if (caster->HasAura(SPELL_DRUID_MOMENT_OF_CLARITY))
                    {
                        if (Aura* clearcasting = caster->GetAura(SPELL_DRUID_CLEARCASTING))
                            clearcasting->ModStackAmount(3);
                    }
                }
            }
        }

        void Register() override
        {
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_dru_omen_of_clarity_AuraScript::HandleEffectPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_HEAL);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_dru_omen_of_clarity_AuraScript();
    }
};

enum CatFormSpells
{
    SPELL_DRUID_DASH                     = 1850,
    SPELL_DRUID_PROWL                    = 5215,
    SPELL_DRUID_FORM_CAT_INCREASE_SPEED  = 113636,
    SPELL_DRUID_CATFORM_OVERRIDE         = 48629,
    SPELL_DRUID_LUNAR_INSPIRATION        = 155580,
    SPELL_DRUID_MOONFIRE_CAT_OVERRIDE    = 155627
};

enum DruidFlamesSpells
{
    SPELL_DRUID_DRUID_OF_THE_FLAMES      = 99245,
    SPELL_DRUID_BURNING_ESSENCE          = 138927,
    MODEL_DRUID_OF_THE_FLAMES            = 38150
};

// Cat Form - 768
// @Called : Cat Form (Speed) - 113636, Cat Form (Thrash/Swipe) - 48629, Dash - 1850, Lunar Inspiration - 155580
// @Version : 7.1.0.22908
class spell_dru_cat_form : public SpellScriptLoader
{
public:
    spell_dru_cat_form() : SpellScriptLoader("spell_dru_cat_form") { }

    class spell_dru_cat_form_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_dru_cat_form_SpellScript);

        void OnActivate()
        {
            if (Player* player = GetCaster()->ToPlayer())
            {
                if (!player->HasAura(SPELL_DRUID_FORM_CAT_INCREASE_SPEED))
                {
                    player->CastSpell(player, SPELL_DRUID_FORM_CAT_INCREASE_SPEED, true);
                    player->RemoveMovementImpairingAuras(true);
                }

                if (player->HasAura(SPELL_DRUID_MASTER_SHAPESHIFTER) && player->HasAura(SPELL_DRUID_FERAL_AFFINITY_GUARDIAN))
                    player->CastSpell(player, SPELL_DRUID_MASTER_SHAPESHIFTER_CAT, true);
            }
        }

        void Register() override
        {
            OnCast += SpellCastFn(spell_dru_cat_form_SpellScript::OnActivate);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_dru_cat_form_SpellScript();
    }

    class spell_dru_cat_form_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_dru_cat_form_AuraScript);

        void OnApply(const AuraEffect* /* aurEff */, AuraEffectHandleModes /*mode*/)
        {
            if (Unit* caster = GetCaster())
            {
                if (Aura* dash = caster->GetAura(SPELL_DRUID_DASH))
                    if (dash->GetEffect(0))
                        if (dash->GetEffect(EFFECT_0)->GetAmount() == 0)
                            dash->GetEffect(EFFECT_0)->SetAmount(70);

                if (caster->HasAura(SPELL_DRUID_LUNAR_INSPIRATION))
                    caster->CastSpell(caster, SPELL_DRUID_MOONFIRE_CAT_OVERRIDE, true);

                caster->CastSpell(caster, SPELL_DRUID_CATFORM_OVERRIDE, true);
            }
        }

        void AfterApply(const AuraEffect* /*p_AurEff*/, AuraEffectHandleModes /*p_Mode*/)
        {
            if (Unit* caster = GetCaster())
                // Check if the caster have Burning Essence or Druid of the Flames aura
                if (caster->HasAura(SPELL_DRUID_BURNING_ESSENCE) || caster->HasAura(SPELL_DRUID_DRUID_OF_THE_FLAMES))
                    // Change the caster model to Druid of the Flames (Fire Cat Form)
                    caster->SetDisplayId(MODEL_DRUID_OF_THE_FLAMES);
        }

        void OnRemove(const AuraEffect* /* aurEff */, AuraEffectHandleModes /*mode*/)
        {
            if (Unit* caster = GetCaster())
            {
                if (Aura* dash = caster->GetAura(SPELL_DRUID_DASH))
                    dash->GetEffect(EFFECT_0)->SetAmount(0);

                if (caster->HasAura(SPELL_DRUID_PROWL))
                    caster->RemoveAura(SPELL_DRUID_PROWL);

                if (caster->HasAura(SPELL_DRUID_LUNAR_INSPIRATION))
                    caster->RemoveAura(SPELL_DRUID_MOONFIRE_CAT_OVERRIDE);

                caster->RemoveAura(SPELL_DRUID_CATFORM_OVERRIDE);
            }
        }

        void Register() override
        {
            OnEffectApply += AuraEffectApplyFn(spell_dru_cat_form_AuraScript::OnApply, EFFECT_0, SPELL_AURA_MOD_SHAPESHIFT, AURA_EFFECT_HANDLE_REAL);
            AfterEffectApply += AuraEffectApplyFn(spell_dru_cat_form_AuraScript::AfterApply, EFFECT_0, SPELL_AURA_MOD_SHAPESHIFT, AURA_EFFECT_HANDLE_REAL);
            OnEffectRemove += AuraEffectRemoveFn(spell_dru_cat_form_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_MOD_SHAPESHIFT, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_dru_cat_form_AuraScript();
    }
};

enum BearFormSpells
{
    SPELL_DRUID_BEARFORM_OVERRIDE              = 106829,
    SPELL_DRUID_STAMPEDING_ROAR                = 106898,
    SPELL_DRUID_STAMPEDING_ROAR_BEAR_OVERRIDE  = 106899
};

// Bear form - 5487
// @Called : Bear Form (Thrash/Swipe) - 106829, Bear Form (Stampeding Roar) - 106899
// @Version : 7.1.0.22908
class spell_dru_bear_form : public SpellScriptLoader
{
public:
    spell_dru_bear_form() : SpellScriptLoader("spell_dru_bear_form") {}

    class spell_dru_bear_form_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_dru_bear_form_AuraScript);

        void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            Unit* caster = GetCaster();
            if (!caster)
                return;

            caster->CastSpell(caster, SPELL_DRUID_BEARFORM_OVERRIDE, true);

            if (caster->HasSpell(SPELL_DRUID_STAMPEDING_ROAR))
                caster->CastSpell(caster, SPELL_DRUID_STAMPEDING_ROAR_BEAR_OVERRIDE, true);

            if (caster->HasAura(SPELL_DRUID_CELESTIAL_GUARDIAN))
                caster->CastSpell(caster, SPELL_DRUID_CELESTIAL_GUARIDAN_BUFF, true);
        }

        void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            Unit* caster = GetCaster();
            if (!caster)
                return;

            caster->RemoveAurasDueToSpell(SPELL_DRUID_BEARFORM_OVERRIDE);

            if (caster->HasSpell(SPELL_DRUID_STAMPEDING_ROAR))
                caster->RemoveAurasDueToSpell(SPELL_DRUID_STAMPEDING_ROAR_BEAR_OVERRIDE);

            caster->RemoveAura(SPELL_DRUID_CELESTIAL_GUARIDAN_BUFF);
        }

        void Register() override
        {
            OnEffectApply += AuraEffectApplyFn(spell_dru_bear_form_AuraScript::OnApply, EFFECT_0, SPELL_AURA_MOD_SHAPESHIFT, AURA_EFFECT_HANDLE_REAL);
            OnEffectRemove += AuraEffectRemoveFn(spell_dru_bear_form_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_MOD_SHAPESHIFT, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_dru_bear_form_AuraScript();
    }
};

enum SkullBashSpells
{
    SPELL_DRUID_SKULL_BASH_CHARGE    = 221514,
    SPELL_DRUID_SKULL_BASH_INTERUPT  = 93985
};

// Skull Bash - 106839
// @Version : 7.1.0.22908
class spell_dru_skull_bash : public SpellScriptLoader
{
public:
    spell_dru_skull_bash() : SpellScriptLoader("spell_dru_skull_bash") { }

    class spell_dru_skull_bash_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_dru_skull_bash_SpellScript);

        void HandleOnHit()
        {
			Unit* caster = GetCaster();
			Unit* target = GetHitUnit();
			if (!caster || !target)
				return;

			if (target->IsNonMeleeSpellCast(false) && !target->IsImmunedToSpellEffect(sSpellMgr->GetSpellInfo(SPELL_DRUID_SKULL_BASH_INTERUPT), sSpellMgr->GetSpellInfo(SPELL_DRUID_SKULL_BASH_INTERUPT)->GetEffect(EFFECT_0), caster))
				caster->Variables.Set<bool>("INTERRUPT", true);
			else
				caster->Variables.Set<bool>("INTERRUPT", false);
            caster->CastSpell(target, SPELL_DRUID_SKULL_BASH_CHARGE, true);
            caster->CastSpell(target, SPELL_DRUID_SKULL_BASH_INTERUPT, true);
        }

        void Register() override
        {
            OnHit += SpellHitFn(spell_dru_skull_bash_SpellScript::HandleOnHit);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_dru_skull_bash_SpellScript();
    }
};

// Stampeding Roar - 106898
// @Version : 7.1.0.22908
class spell_dru_stampeding_roar : public SpellScriptLoader
{
public:
    spell_dru_stampeding_roar() : SpellScriptLoader("spell_dru_stampeding_roar") { }

    class spell_dru_stampeding_roar_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_dru_stampeding_roar_SpellScript);

        void HandleOnHit()
        {
            Unit* caster = GetCaster();
            if (!caster)
                return;

            if (!caster->HasAura(SPELL_DRUID_BEAR_FORM) && !caster->HasAura(SPELL_DRUID_CAT_FORM))
                caster->CastSpell(caster, SPELL_DRUID_BEAR_FORM, true);

            if (Unit* target = GetHitUnit())
                target->RemoveMovementImpairingAuras(true);
        }

        void Register() override
        {
            OnHit += SpellHitFn(spell_dru_stampeding_roar_SpellScript::HandleOnHit);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_dru_stampeding_roar_SpellScript();
    }
};

// Activate Cat Form
// @Called : Dash - 1850, Prowl - 5215, Displacer Beast - 102280
// @Version : 7.1.0.22908
class spell_dru_activate_cat_form : public SpellScriptLoader
{
public:
    spell_dru_activate_cat_form() : SpellScriptLoader("spell_dru_activate_cat_form") { }

    class spell_dru_activate_cat_form_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_dru_activate_cat_form_SpellScript);

        void HandleOnHit()
        {
            Unit* caster = GetCaster();
            if (!caster)
                return;

            if (!caster->HasAura(SPELL_DRUID_CAT_FORM))
                caster->CastSpell(caster, SPELL_DRUID_CAT_FORM, true);
        }

        void Register() override
        {
            OnHit += SpellHitFn(spell_dru_activate_cat_form_SpellScript::HandleOnHit);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_dru_activate_cat_form_SpellScript();
    }
};

enum KillerInstinctSpells
{
    SPELL_DRUID_KILLER_INSTINCT          = 108299,
    SPELL_DRUID_KILLER_INSTINCT_MOD_STAT = 108300
};

//Killer Instinct - 108299
// @Called : Called by Cat Form - 768 and Bear Form - 5487
// @Version : 7.1.0.22908
class spell_dru_killer_instinct : public SpellScriptLoader
{
public:
    spell_dru_killer_instinct() : SpellScriptLoader("spell_dru_killer_instinct") { }

    class spell_dru_killer_instinct_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_dru_killer_instinct_AuraScript);

        void AfterApply(AuraEffect const* /*p_AurEff*/, AuraEffectHandleModes /*m_Mode*/)
        {
            if (Player* player = GetTarget()->ToPlayer())
            {
                if (player->HasAura(SPELL_DRUID_KILLER_INSTINCT))
                {
                    int32 bp = player->GetStat(STAT_INTELLECT);

                    player->CastCustomSpell(player, SPELL_DRUID_KILLER_INSTINCT_MOD_STAT, &bp, NULL, NULL, true);
                }
            }
        }

        void AfterRemove(AuraEffect const* /*p_AurEff*/, AuraEffectHandleModes /*m_Mode*/)
        {
            if (Player* player = GetTarget()->ToPlayer())
            {
                if (player->HasAura(SPELL_DRUID_KILLER_INSTINCT))
                    player->RemoveAura(SPELL_DRUID_KILLER_INSTINCT_MOD_STAT);
            }
        }

        void Register() override
        {
            AfterEffectApply += AuraEffectApplyFn(spell_dru_killer_instinct_AuraScript::AfterApply, EFFECT_0, SPELL_AURA_MOD_SHAPESHIFT, AURA_EFFECT_HANDLE_REAL);
            AfterEffectRemove += AuraEffectRemoveFn(spell_dru_killer_instinct_AuraScript::AfterRemove, EFFECT_0, SPELL_AURA_MOD_SHAPESHIFT, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_dru_killer_instinct_AuraScript();
    }
};

enum LivingSeedSpells
{
    SPELL_DRUID_LIVING_SEED_PROC = 48504
};

// Living Seed - 48500
// @Version : 7.1.0.22908
class spell_dru_living_seed : public SpellScriptLoader
{
public:
    spell_dru_living_seed() : SpellScriptLoader("spell_dru_living_seed") { }

    class spell_dru_living_seed_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_dru_living_seed_AuraScript);

        bool CheckProc(ProcEventInfo& eventInfo)
        {
            if (eventInfo.GetTypeMask() & PROC_FLAG_TAKE_HARMFUL_PERIODIC && eventInfo.GetSpellTypeMask() & PROC_SPELL_TYPE_HEAL)
                return false;

            return true;
        }

        void HandleProc(AuraEffect* aurEff, ProcEventInfo& eventInfo)
        {
            PreventDefaultAction();

            if (HealInfo* healInfo = eventInfo.GetHealInfo())
            {
                int32 amount = CalculatePct(healInfo->GetHeal(), aurEff->GetAmount());
                GetTarget()->CastCustomSpell(SPELL_DRUID_LIVING_SEED_PROC, SPELLVALUE_BASE_POINT0, amount, eventInfo.GetProcTarget(), true, NULL, aurEff);
            }
        }

        void Register() override
        {
            DoCheckProc += AuraCheckProcFn(spell_dru_living_seed_AuraScript::CheckProc);
            OnEffectProc += AuraEffectProcFn(spell_dru_living_seed_AuraScript::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_dru_living_seed_AuraScript();
    }
};

// Infected wound - 48484
// @Version : 7.1.0.22908
class spell_dru_infected_wound : public SpellScriptLoader
{
public:
    spell_dru_infected_wound() : SpellScriptLoader("spell_dru_infected_wound") { }

    class spell_dru_infected_wound_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_dru_infected_wound_AuraScript);

        bool CheckProc(ProcEventInfo& eventInfo)
        {
            if (eventInfo.GetSpellInfo()->Id == SPELL_DRUID_RAKE)
                return true;

            return false;
        }

        void Register() override
        {
            DoCheckProc += AuraCheckProcFn(spell_dru_infected_wound_AuraScript::CheckProc);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_dru_infected_wound_AuraScript();
    }
};

// Ysera's Gift - 145108
class aura_dru_ysera_gift : public AuraScript
{
    PrepareAuraScript(aura_dru_ysera_gift);

    void HandleEffectPeriodic(AuraEffect const* aurEff)
    {
        Unit* caster = GetCaster();
        if (!caster || !caster->IsAlive())
            return;

        int64 amount = CalculatePct(caster->GetMaxHealth(), aurEff->GetBaseAmount());

        if (AuraEffect* aurEff = caster->GetAuraEffect(SPELL_DRUID_WALKING_DREAM, EFFECT_0))
            if (caster->GetTargetAuraApplications(SPELL_DRUID_REJUVENATION).size())
                amount += aurEff->GetAmount() * caster->GetTargetAuraApplications(SPELL_DRUID_REJUVENATION).size();
        
        CastSpellExtraArgs values(true);
       // values.AddSpellMod(SPELLVALUE_MAX_TARGETS, 1);
        values.AddSpellBP0(amount);

        if (caster->IsFullHealth())
            caster->CastSpell(caster, SPELL_DRUID_YSERA_GIFT_RAID_HEAL, values);
        else
            caster->CastSpell(caster, SPELL_DRUID_YSERA_GIFT_CASTER_HEAL, values);
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(aura_dru_ysera_gift::HandleEffectPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

enum RakeSpells
{
    SPELL_DRUID_RAKE_STUN             = 163505
};

// 1822 - Rake
class spell_dru_rake : public SpellScript
{
    PrepareSpellScript(spell_dru_rake);

    bool Load() override
    {
        Unit* caster = GetCaster();
        if (caster->HasAuraType(SPELL_AURA_MOD_STEALTH) || caster->HasAura(340698)) ///< Sudden Ambush
            stealthed = true;

        return true;
    }

    void CalcCrit(Unit const* victim, float& chance)
    {
		if (Unit* caster = GetCaster())
		{
			if (caster->HasAura(SPELL_DRUID_CAT_FORM) && caster->HasAura(SPELL_DRUID_BLOOD_SCENT) && victim->HasAuraState(AURA_STATE_BLEED))
				chance += sSpellMgr->GetSpellInfo(SPELL_DRUID_BLOOD_SCENT)->GetEffect(EFFECT_0).BasePoints;

			// Fresh Wound
			if (caster->HasAura(SPELL_DRUID_FRESH_WOUND) && !victim->HasAura(SPELL_DRUID_RAKE_AURA, caster->GetGUID()))
				chance += sSpellMgr->GetSpellInfo(SPELL_DRUID_FRESH_WOUND)->GetEffect(EFFECT_0).BasePoints;
		}
    }

    void HandleOnHit(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetExplTargetUnit();
        if (!caster || !target)
            return;

		int32 damage = GetHitDamage();
        bool increased = caster->HasAura(SPELL_DRUID_RAKE_RANK_2) && (stealthed || caster->HasAura(SPELL_DRUID_INCARNATION_KING_OF_JUNGLE));

        // While stealthed or have Incarnation: King of the Jungle aura, deal 100% increased damage
        if (increased)
            damage += CalculatePct(damage, sSpellMgr->GetSpellInfo(SPELL_DRUID_RAKE)->GetEffect(EFFECT_3).BasePoints);

        // Only stun if the caster was in stealth
        if (stealthed && caster->HasAura(SPELL_DRUID_RAKE_RANK_2))
        {
            caster->CastSpell(target, SPELL_DRUID_RAKE_STUN, true);
            caster->Variables.Set("IncreassedRakeDmg", true);
        }

		SetHitDamage(damage);
    }

    void Register() override
    {
        OnCalcCritChance += SpellOnCalcCritChanceFn(spell_dru_rake::CalcCrit);
        OnEffectHitTarget += SpellEffectFn(spell_dru_rake::HandleOnHit, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }

private:
    bool stealthed = false;
};



enum MaimSpells
{
    SPELL_DRUID_MAIM_STUN  = 203123
};

// 22570 - Maim
class spell_dru_maim : public SpellScript
{
    PrepareSpellScript(spell_dru_maim);

    void HandleTakePower(SpellPowerCost& powerCost)
    {
        if (powerCost.Power == POWER_COMBO_POINTS)
        {
            comboPoints = powerCost.Amount;
        }
    }

    void CalcCrit(Unit const* victim, float& chance)
    {
        if (Unit* caster = GetCaster())
            if (caster->HasAura(SPELL_DRUID_CAT_FORM) && caster->HasAura(SPELL_DRUID_BLOOD_SCENT) && victim->HasAuraState(AURA_STATE_BLEED))
                chance += sSpellMgr->GetSpellInfo(SPELL_DRUID_BLOOD_SCENT)->GetEffect(EFFECT_0).BasePoints;
    }

    void HandleEffectHitStun(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        // Stun.
        caster->CastCustomSpell(SPELL_DRUID_MAIM_STUN, SPELLVALUE_DURATION, comboPoints * IN_MILLISECONDS, target, true);
    }

    void HandleEffectHitTarget(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        int32 damage = GetHitDamage();
        SetHitDamage(damage * comboPoints);

        // Soul of the Forest.
        if (caster->HasAura(SPELL_DRUID_SOUL_OF_THE_FOREST))
            caster->CastCustomSpell(SPELL_DRUID_SOUL_OF_THE_FOREST_FERAL_ENERGIZE, SPELLVALUE_BASE_POINT0, comboPoints * sSpellMgr->GetSpellInfo(SPELL_DRUID_SOUL_OF_THE_FOREST)->GetEffect(EFFECT_0).BasePoints, caster, true);
    }

    void Register() override
    {
        OnCalcCritChance += SpellOnCalcCritChanceFn(spell_dru_maim::CalcCrit);
        OnTakePower += SpellOnTakePowerFn(spell_dru_maim::HandleTakePower);
        OnEffectHitTarget += SpellEffectFn(spell_dru_maim::HandleEffectHitStun, EFFECT_0, SPELL_EFFECT_DUMMY);
        OnEffectHitTarget += SpellEffectFn(spell_dru_maim::HandleEffectHitTarget, EFFECT_1, SPELL_EFFECT_SCHOOL_DAMAGE);
    }

private:
    uint8 comboPoints = 0;
};

// 1079 - Rip
class spell_dru_rip : public SpellScript
{
    PrepareSpellScript(spell_dru_rip);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_DRUID_SOUL_OF_THE_FOREST });
    }

    void HandleTakePower(SpellPowerCost& powerCost)
    {
        if (powerCost.Power == POWER_COMBO_POINTS)
        {
            comboPoints = powerCost.Amount;
        }
    }

    void CalcCrit(Unit const* victim, float& chance)
    {
        if (Unit* caster = GetCaster())
            if (caster->HasAura(SPELL_DRUID_CAT_FORM) && caster->HasAura(SPELL_DRUID_BLOOD_SCENT) && victim->HasAuraState(AURA_STATE_BLEED))
                chance += sSpellMgr->GetSpellInfo(SPELL_DRUID_BLOOD_SCENT)->GetEffect(EFFECT_0).BasePoints;
    }

	void HandleEffectHit(SpellEffIndex /*effIndex*/)
	{
        if (Unit* caster = GetCaster())
        {
            if (caster->HasAura(SPELL_DRUID_SOUL_OF_THE_FOREST))
                caster->CastCustomSpell(SPELL_DRUID_SOUL_OF_THE_FOREST_FERAL_ENERGIZE, SPELLVALUE_BASE_POINT0, comboPoints * sSpellMgr->GetSpellInfo(SPELL_DRUID_SOUL_OF_THE_FOREST)->GetEffect(EFFECT_0).BasePoints, caster, true);
        }
	}

    SpellCastResult CheckCast()
    {
        if (Unit* caster = GetCaster())
            if (Unit* target = GetExplTargetUnit())
                if (auto rip = target->GetAura(SPELL_DRUID_RIP, caster->GetGUID()))
                {
                    auto comboPoints = caster->GetComboPoints();

                    int32 duration = 0;

                    switch (comboPoints)
                    {
                        case 1:
                            duration += 8000;
                            break;
                        case 2:
                            duration += 12000;
                            break;
                        case 3:
                            duration += 16000;
                            break;
                        case 4:
                            duration += 20000;
                            break;
                        case 5:
                            duration += 24000;
                            break;
                        default:
                            break;
                    }

                    if (duration < rip->GetDuration())
                        return SPELL_FAILED_AURA_BOUNCED;
                }

        return SPELL_CAST_OK;
    }

    void Register() override
    {
        OnCalcCritChance += SpellOnCalcCritChanceFn(spell_dru_rip::CalcCrit);
        OnTakePower += SpellOnTakePowerFn(spell_dru_rip::HandleTakePower);
		OnEffectHitTarget += SpellEffectFn(spell_dru_rip::HandleEffectHit, EFFECT_0, SPELL_EFFECT_APPLY_AURA);
        OnCheckCast += SpellCheckCastFn(spell_dru_rip::CheckCast);
    }

private:
    uint8 comboPoints = 0;
};

// 1079 - Rip Aura
// Last Update 8.0.1 Build 28153
 class aura_dru_rip : public AuraScript
 {
    PrepareAuraScript(aura_dru_rip);

    void HandleApply(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* caster = GetCaster())
        {
            if (Unit* target = GetTarget())
            {
                if (caster->HasAura(SPELL_DRUID_KING_OF_THE_JUNGLE))
                    caster->CastSpell(caster, SPELL_DRUID_KING_OF_THE_JUNGLE_BUFF, true);
            }
        }
    }

	void HandleRemove(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
	{
        if (Unit* caster = GetCaster())
        {
            if (caster->HasAura(SPELL_DRUID_PREDATOR))
            {
                if (GetTargetApplication() && GetTargetApplication()->GetRemoveMode() != AURA_REMOVE_BY_DEATH)
                    return;

                caster->GetSpellHistory()->ResetCooldown(SPELL_DRUID_TIGERS_FURY, true);
            }

            if (Aura* aura = caster->GetAura(SPELL_DRUID_KING_OF_THE_JUNGLE_BUFF))
                aura->ModStackAmount(-1);
        }
	}

    void HandlePeriodic(AuraEffect const* aurEff)
    {
        auto caster = GetCaster();
        if (!caster)
            return;
        auto target = GetTarget();
        if (!target)
            return;

        if (_originalDamage > 0)
        {
            if (!Druid::CanDraughtOfDeepFocus(caster, target, GetId()))
            {
                const_cast<AuraEffect*>(aurEff)->ChangeAmount(_originalDamage);
                const_cast<AuraEffect*>(aurEff)->SetDamage(_originalDamage);
                _originalDamage = 0;
            }
        }
        else
        {
            if (Druid::CanDraughtOfDeepFocus(caster, target, GetId()))
            {
                _originalDamage = aurEff->GetDamage();
                uint32 newDmg = CalculatePct(aurEff->GetDamage(), 140);;
                const_cast<AuraEffect*>(aurEff)->SetDamage(newDmg);
                const_cast<AuraEffect*>(aurEff)->ChangeAmount(newDmg);
            }
        }
    }

    uint32 _originalDamage = 0;

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(aura_dru_rip::HandleApply, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE, AURA_EFFECT_HANDLE_REAL);
		OnEffectRemove += AuraEffectRemoveFn(aura_dru_rip::HandleRemove, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE, AURA_EFFECT_HANDLE_REAL);
        OnEffectPeriodic += AuraEffectPeriodicFn(aura_dru_rip::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE);
    }
};

enum DruidForms
{
    DRUID_AQUATIC_FORM                      = 1066,
    DRUID_FLIGHT_FORM                       = 33943,
    DRUID_STAG_FORM                         = 165961,
    DRUID_SWIFT_FLIGHT_FORM                 = 40120
};

// 783 - Travel Form (dummy)
class spell_dru_travel_form_dummy : public SpellScriptLoader
{
public:
    spell_dru_travel_form_dummy() : SpellScriptLoader("spell_dru_travel_form_dummy") { }

    class spell_dru_travel_form_dummy_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_dru_travel_form_dummy_SpellScript);

        SpellCastResult CheckCast()
        {
            Player* player = GetCaster()->ToPlayer();
            if (!player)
                return SPELL_FAILED_CUSTOM_ERROR;

            SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(player->IsInWater() ? DRUID_AQUATIC_FORM : DRUID_STAG_FORM);
            return spellInfo->CheckLocation(player->GetMapId(), player->GetZoneId(), player->GetAreaId(), player);
        }

        void Register() override
        {
            OnCheckCast += SpellCheckCastFn(spell_dru_travel_form_dummy_SpellScript::CheckCast);
        }
    };

    class spell_dru_travel_form_dummy_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_dru_travel_form_dummy_AuraScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            return ValidateSpellInfo({ DRUID_STAG_FORM, DRUID_AQUATIC_FORM, DRUID_FLIGHT_FORM, DRUID_SWIFT_FLIGHT_FORM });
        }

        bool Load() override
        {
            if (auto caster = GetCaster())
                return caster->IsPlayer();
            return false;
        }

        void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            uint32 triggeredSpellId;

            Player* player = GetTarget()->ToPlayer();
            if (player->IsInWater()) // Aquatic form
                triggeredSpellId = DRUID_AQUATIC_FORM;
            // added isJumping because IsInAir is delayed and people wouldn't be able to get into fly form often otherwise
            else if (player->GetSkillValue(SKILL_RIDING) >= 225 && (player->IsInAir() || player->IsJumping()) && CheckLocationForForm(DRUID_FLIGHT_FORM) == SPELL_CAST_OK) // Flight form
                triggeredSpellId = player->GetLevel() >= 71 ? DRUID_SWIFT_FLIGHT_FORM : DRUID_FLIGHT_FORM;
            else // Stag form (riding skill already checked in CheckCast)
                triggeredSpellId = DRUID_STAG_FORM;

            player->AddAura(triggeredSpellId, player);
        }

        void AfterRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            // No need to check remove mode, it's safe for auras to remove each other in AfterRemove hook.
            GetTarget()->RemoveAura(DRUID_STAG_FORM);
            GetTarget()->RemoveAura(DRUID_AQUATIC_FORM);
            GetTarget()->RemoveAura(DRUID_FLIGHT_FORM);
            GetTarget()->RemoveAura(DRUID_SWIFT_FLIGHT_FORM);
        }

        void Register() override
        {
            OnEffectApply += AuraEffectApplyFn(spell_dru_travel_form_dummy_AuraScript::OnApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            OnEffectRemove += AuraEffectRemoveFn(spell_dru_travel_form_dummy_AuraScript::AfterRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        }

    private:
        // Outdoor check already passed - Travel Form (dummy) has SPELL_ATTR0_OUTDOORS_ONLY attribute.
        SpellCastResult CheckLocationForForm(uint32 spell)
        {
            Player* player = GetTarget()->ToPlayer();
            SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(spell);
            return spellInfo->CheckLocation(player->GetMapId(), player->GetZoneId(), player->GetAreaId(), player);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_dru_travel_form_dummy_SpellScript();
    }

    AuraScript* GetAuraScript() const override
    {
        return new spell_dru_travel_form_dummy_AuraScript();
    }
};

// 1066 - Aquatic Form
// 33943 - Flight Form
// 40120 - Swift Flight Form
// 165961 - Stag Form
class spell_dru_travel_form : public SpellScriptLoader
{
public:
    spell_dru_travel_form() : SpellScriptLoader("spell_dru_travel_form") { }

    class spell_dru_travel_form_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_dru_travel_form_AuraScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            return ValidateSpellInfo({ DRUID_STAG_FORM, DRUID_AQUATIC_FORM, DRUID_FLIGHT_FORM, DRUID_SWIFT_FLIGHT_FORM });
        }

        bool Load() override
        {
            if (auto caster = GetCaster())
                return caster->IsPlayer();
            return false;
        } 

        void AfterRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            Player* player = GetTarget()->ToPlayer();
            player->RemoveAura(SPELL_DRUID_TRAVEL_FORM);
        }

        void Register() override
        {
            AfterEffectRemove += AuraEffectRemoveFn(spell_dru_travel_form_AuraScript::AfterRemove, EFFECT_0, SPELL_AURA_MOD_SHAPESHIFT, AURA_EFFECT_HANDLE_REAL);
        }

    private:
        SpellCastResult CheckLocationForForm(uint32 spell_id)
        {
            Player* player = GetTarget()->ToPlayer();
            SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(spell_id);

            if (!player->IsOutdoors())
                return SPELL_FAILED_ONLY_OUTDOORS;

            return spellInfo->CheckLocation(player->GetMapId(), player->GetZoneId(), player->GetAreaId(), player);
        }

        uint32 triggeredSpellId;
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_dru_travel_form_AuraScript();
    }
};

// Moonkin Form - 24858
// Chosen of Elune - 102560
// Moonkin Form (Balance Affinity talent) - 197625
class aura_dru_astral_form : public AuraScript
{
    PrepareAuraScript(aura_dru_astral_form);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_DRUID_GLYPH_OF_STARS, SPELL_DRUID_MOONKING_FORM_RANK2, SPELL_DRUID_OWLKIN_FRENZY });
    }

    void AfterApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Unit* target = GetTarget();

        if (target->HasAura(SPELL_DRUID_MOONKIN_FORM) || target->HasAura(SPELL_DRUID_MOONKIN_FORM_TALENT))
            target->SetDisplayId(target->GetModelForForm(FORM_MOONKIN_FORM, 0));

        if (target->HasAura(SPELL_DRUID_GLYPH_OF_STARS))
        {
            target->SetDisplayId(target->GetNativeDisplayId());
            target->AddAura(SPELL_DRUID_BLUE_COLOR, target);
            target->AddAura(SPELL_DRUID_SHADOWY_GHOST, target);
            target->CastSpell(target, sSpellMgr->GetSpellInfo(SPELL_DRUID_GLYPH_OF_STARS)->GetEffect(EFFECT_0).BasePoints, true);
        }

        if (target->HasAura(SPELL_DRUID_MASTER_SHAPESHIFTER) && target->HasAura(SPELL_DRUID_BALANCE_AFFINITY_FERAL_GUARDIAN))
            target->CastSpell(target, SPELL_DRUID_MASTER_SHAPESHIFTER_MOONKIN, true);
    }

    void AfterRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Unit* target = GetTarget();
        if (target->HasAura(SPELL_DRUID_MOONKIN_FORM) || target->HasAura(SPELL_DRUID_CHOSEN_OF_ELUNE))
            return;

        target->SetDisplayId(target->GetNativeDisplayId());
        target->RemoveAura(sSpellMgr->GetSpellInfo(SPELL_DRUID_GLYPH_OF_STARS)->GetEffect(EFFECT_0).BasePoints);
        target->RemoveAura(SPELL_DRUID_BLUE_COLOR);
        target->RemoveAura(SPELL_DRUID_SHADOWY_GHOST);
    }

	bool CheckProc(ProcEventInfo& eventInfo)
	{
		if (Unit* caster = GetCaster())
			if (!caster->HasAura(SPELL_DRUID_MOONKING_FORM_RANK2))
				return false;

		if (eventInfo.GetDamageInfo() && (eventInfo.GetDamageInfo()->GetAttackType() == BASE_ATTACK || eventInfo.GetDamageInfo()->GetAttackType() == OFF_ATTACK))
			return true;

		if (eventInfo.GetSpellInfo() && !eventInfo.GetSpellInfo()->IsAffectingArea() && !eventInfo.GetSpellInfo()->IsTargetingArea() && (eventInfo.GetDamageInfo() &&
			(eventInfo.GetDamageInfo()->GetDamageType() != HEAL && eventInfo.GetDamageInfo()->GetDamageType() != NODAMAGE)))
			return true;

		return false;
	}

	void HandleProc(ProcEventInfo& eventInfo)
	{
		if (Unit* caster = GetCaster())
			caster->CastSpell(caster, SPELL_DRUID_OWLKIN_FRENZY, true);
	}

    void Register() override
    {
        switch (m_scriptSpellId)
        {
            case SPELL_DRUID_MOONKIN_FORM:
            case SPELL_DRUID_MOONKIN_FORM_TALENT:
                AfterEffectApply += AuraEffectApplyFn(aura_dru_astral_form::AfterApply, EFFECT_1, SPELL_AURA_MOD_SHAPESHIFT, AURA_EFFECT_HANDLE_REAL);
                AfterEffectRemove += AuraEffectRemoveFn(aura_dru_astral_form::AfterRemove, EFFECT_1, SPELL_AURA_MOD_SHAPESHIFT, AURA_EFFECT_HANDLE_REAL);
                break;
            case SPELL_DRUID_CHOSEN_OF_ELUNE:
                AfterEffectApply += AuraEffectApplyFn(aura_dru_astral_form::AfterApply, EFFECT_0, SPELL_AURA_MOD_DAMAGE_PERCENT_DONE, AURA_EFFECT_HANDLE_REAL);
                AfterEffectRemove += AuraEffectRemoveFn(aura_dru_astral_form::AfterRemove, EFFECT_0, SPELL_AURA_MOD_DAMAGE_PERCENT_DONE, AURA_EFFECT_HANDLE_REAL);
                break;
            default:
                break;
        }
		DoCheckProc += AuraCheckProcFn(aura_dru_astral_form::CheckProc);
		OnProc += AuraProcFn(aura_dru_astral_form::HandleProc);
    }
};

// Restoration Affinity - 197492
class aura_dru_restoration_affinity : public AuraScript
{
    PrepareAuraScript(aura_dru_restoration_affinity);

    const std::vector<uint32> LearnedSpells =
    {
        SPELL_DRUID_YSERA_GIFT,
        SPELL_DRUID_REJUVENATION,
        SPELL_DRUID_HEALING_TOUCH,
        SPELL_DRUID_SWIFTMEND
    };

    void AfterApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Player* target = GetTarget()->ToPlayer();
        if(!target)
            return;

        for (uint32 spellId : LearnedSpells)
            target->LearnSpell(spellId, false);
    }

    void AfterRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Player* target = GetTarget()->ToPlayer();
        if(!target)
            return;

        for (uint32 spellId : LearnedSpells)
        {
            // This prevent Rejuvenation gones missing if the target was a low level character and in Restoration specialization
            if(target->GetSpecializationId() == TALENT_SPEC_DRUID_RESTORATION)
                if(spellId == SPELL_DRUID_REJUVENATION)
                    continue;

            target->RemoveSpell(spellId);
        }
    }

    void Register() override
    {
        AfterEffectApply += AuraEffectApplyFn(aura_dru_restoration_affinity::AfterApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        AfterEffectRemove += AuraEffectRemoveFn(aura_dru_restoration_affinity::AfterRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

// 22842 - Frenzied Regeneration
class aura_dru_frenzied_regeneration : public AuraScript
{
    PrepareAuraScript(aura_dru_frenzied_regeneration);

    void CalcAmount(AuraEffect const* aurEff, int32& amount, bool& canBeRecalculated)
    {
		canBeRecalculated = true;
		if (Unit* caster = GetCaster())
		{
			// Check Guardian of Elune aura
			if (caster->HasAura(SPELL_DRUID_GUARDIAN_OF_ELUNE_AURA))
			{
				uint32 total = sSpellMgr->GetSpellInfo(SPELL_DRUID_FRENZIED_REGENERATION)->GetEffect(EFFECT_0).BasePoints * (sSpellMgr->GetSpellInfo(SPELL_DRUID_FRENZIED_REGENERATION)->GetMaxDuration() / 1000 + 1);
				total += sSpellMgr->GetSpellInfo(SPELL_DRUID_GUARDIAN_OF_ELUNE_AURA)->GetEffect(EFFECT_1).BasePoints;
				amount = total / (sSpellMgr->GetSpellInfo(SPELL_DRUID_FRENZIED_REGENERATION)->GetMaxDuration() / 1000 + 1);
			}
		}
    }

    void Register() override
    {
        DoEffectCalcAmount += AuraEffectCalcAmountFn(aura_dru_frenzied_regeneration::CalcAmount, EFFECT_0, SPELL_AURA_OBS_MOD_HEALTH);
    }
};

enum StarfallSpells
{
    SPELL_DRUID_STARFALL_DAMAGE      = 191037,
    SPELL_DRUID_STELLAR_EMPOWERMENT  = 197637
};

// Starfall - 191034
// AreaTriggerID - 9482
struct at_dru_starfall : AreaTriggerAI
{
    int32 timeInterval;

    at_dru_starfall(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger)
    {
        // How often should the action be executed
        areatrigger->SetPeriodicProcTimer(100); // 850 retail
    }

    void OnPeriodicProc() override
    {
        if (Unit* caster = at->GetCaster())
            for (ObjectGuid objguid : at->GetInsideUnits())
                if (Unit* unit = ObjectAccessor::GetUnit(*caster, objguid))
                    if (caster->IsValidAttackTarget(unit))
                    {
                        caster->CastSpell(unit, SPELL_DRUID_STARFALL_DAMAGE, true);
                        caster->CastSpell(unit, SPELL_DRUID_STELLAR_EMPOWERMENT, true);
                    }
    }

    void OnUnitEnter(Unit* unit) override
    {
        if (Unit* caster = at->GetCaster())
            if (unit && unit->GetGUID() == caster->GetGUID() && caster->HasAura(SPELL_DRUID_STELLAR_DRIFT))
                caster->CastSpell(caster, SPELL_DRUID_STELLAR_DRIFT_CASTING, true);
    }

    void OnUnitExit(Unit* unit) override
    {
        if (Unit* caster = at->GetCaster())
            if (unit && unit->GetGUID() == caster->GetGUID())
                caster->RemoveAura(SPELL_DRUID_STELLAR_DRIFT_CASTING);
    }
};

enum SolarBeamSpells
{
    SPELL_DRUID_SOLAR_BEAM_SILENCE = 81261
};

// Solar Beam - 78675
// AreaTriggerID - 983
// @Version : 7.1.0.22908
struct at_dru_solar_beam : AreaTriggerAI
{
	at_dru_solar_beam(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger) { }

	void OnUnitEnter(Unit* unit) override
	{
		Unit* caster = at->GetCaster();
		if (!caster || !unit)
			return;

		if (caster->GetTypeId() != TYPEID_PLAYER)
			return;

		if (caster->IsValidAttackTarget(unit))
			caster->CastSpell(unit, SPELL_DRUID_SOLAR_BEAM_SILENCE, true);
	}

	void OnUnitExit(Unit* unit) override
	{
		Unit* caster = at->GetCaster();
		if (!caster || !unit)
			return;

		if (caster->GetTypeId() != TYPEID_PLAYER)
			return;

        if (Aura* solarBeam = unit->GetAura(SPELL_DRUID_SOLAR_BEAM_SILENCE, caster->GetGUID()))
        {
            if (AuraApplication* aurApp = unit->GetAuraApplication(SPELL_DRUID_SOLAR_BEAM_SILENCE, caster->GetGUID()))
                unit->SendRemoveLossOfControl(aurApp, LossOfControlType::TypeSilenced);
            unit->RemoveAura(solarBeam);
        }
	}
};

struct at_druid_den_mother : AreaTriggerAI
{
	at_druid_den_mother(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger) { }

	void OnUnitEnter(Unit* unit) override
	{
		if (Unit* caster = at->GetCaster())
			if (Player* player = caster->ToPlayer())
				if (unit && unit->ToPlayer() && player->IsValidAssistTarget(unit) && (player->IsInSameGroupWith(unit->ToPlayer()) || player->IsInSameRaidWith(unit->ToPlayer())))
					player->CastSpell(unit, SPELL_DRUID_DEN_MOTHER, true);
	}

	void OnUnitExit(Unit* unit) override
	{
		if (Unit* caster = at->GetCaster())
			if (unit->HasAura(SPELL_DRUID_DEN_MOTHER, caster->GetGUID()))
				unit->RemoveAura(SPELL_DRUID_DEN_MOTHER, caster->GetGUID());
	}
};

struct at_dru_lunar_beam : AreaTriggerAI
{
    at_dru_lunar_beam(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger)
    {
        areatrigger->SetPeriodicProcTimer(1 * IN_MILLISECONDS);
    }

    void OnUnitEnter(Unit* unit) override
    {
        if (Unit* caster = at->GetCaster())
        {
            if (unit && unit->GetGUID() == caster->GetGUID())
                caster->Variables.Set<bool>("INSIDE_BEAM", true);
        }
    }

    void OnPeriodicProc() override
    {
        if (Unit* caster = at->GetCaster())
            caster->CastSpell(at->GetPosition(), SPELL_DRUID_LUNAR_BEAM_EFFECT, true);
    }

    void OnUnitExit(Unit* unit) override
    {
        if (Unit* caster = at->GetCaster())
           if (unit && unit->GetGUID() == caster->GetGUID())
               caster->Variables.Set<bool>("INSIDE_BEAM", false);
    }
};

struct at_dru_clan_defender : AreaTriggerAI
{
    at_dru_clan_defender(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger) { }

    void OnUnitEnter(Unit* unit) override
    {
        if (Unit* caster = at->GetCaster())
        {
            if (unit && caster->IsValidAssistTarget(unit))
                caster->CastSpell(unit, SPELL_DRUID_CLAN_DEFENDER_ALLIES, true);
        }
    }

    void OnUnitExit(Unit* unit) override
    {
        if (Unit* caster = at->GetCaster())
            if (unit && unit->HasAura(SPELL_DRUID_CLAN_DEFENDER_ALLIES, caster->GetGUID()))
                unit->RemoveAura(SPELL_DRUID_CLAN_DEFENDER_ALLIES, caster->GetGUID());
    }
};

// 202770 - Fury of Elune
// AreatriggerAI - 6887
struct at_dru_fury_of_elune : AreaTriggerAI
{
	at_dru_fury_of_elune(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger)
	{
		areatrigger->SetPeriodicProcTimer(750);
	}

	void OnPeriodicProc() override
	{
        //if (at->_reachedDestination && sendStopPacket)
        //{
        //    WorldPackets::AreaTrigger::AreaTriggerRePath reshape;
        //    reshape.TriggerGUID = at->GetGUID();
        //    at->SendMessageToSet(reshape.Write(), true);
        //    sendStopPacket = false;
        //}

        if (Unit* caster = at->GetCaster())
        {
            if (auto target = ObjectAccessor::GetUnit(*caster, at->m_areaTriggerData->TargetGUID))
                if (lastTargetPosition != target->GetPosition())
                {
                    lastTargetPosition = target->GetPosition();
                    at->SetDestination(*target, 200, true);
                }

            caster->CastSpell(at->GetPosition(), SPELL_DRUID_FURY_OF_ELUNE_DAMAGE, true);
        }
	}

private:
	Position lastTargetPosition;
};

enum UrsolsVortexSpells
{
    SPELL_DRUID_URSOLS_VORTEX_SLOW   = 127797,
    SPELL_DRUID_URSOLS_VORTEX_PULL   = 118283
};

// Ursol's Vortex - 102793
// AreaTriggerID - 314
// @Version : 7.1.0.22908
struct at_dru_ursols_vortex : AreaTriggerAI
{
    at_dru_ursols_vortex(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger) { }

    void OnUnitEnter(Unit* unit) override
    {
        Unit* caster = at->GetCaster();

        if (!caster || !unit)
            return;

        if (!caster->ToPlayer())
            return;

        if (caster->IsValidAttackTarget(unit))
            caster->CastSpell(unit, SPELL_DRUID_URSOLS_VORTEX_SLOW, true);
    }

    void OnUnitExit(Unit* unit) override
    {
        Unit* caster = at->GetCaster();

        if (!caster || !unit)
            return;

        if (!caster->ToPlayer())
            return;

        if (auto tempSumm = caster->SummonCreature(WORLD_TRIGGER, { at->GetPositionX(), at->GetPositionY(), at->GetPositionZ() }, TEMPSUMMON_TIMED_DESPAWN, 200ms))
        {
            tempSumm->SetFaction(caster->GetFaction());
            tempSumm->SetOwnerGUID(caster->GetGUID());
            PhasingHandler::InheritPhaseShift(tempSumm, caster);

            if (caster->IsValidAttackTarget(unit))
            {
                // Was already pulled, we can let him leave, remove slow and pull aura.
                if (unit->HasAura(SPELL_DRUID_URSOLS_VORTEX_PULL))
                {
                    unit->RemoveAurasDueToSpell(SPELL_DRUID_URSOLS_VORTEX_PULL);
                    unit->RemoveAurasDueToSpell(SPELL_DRUID_URSOLS_VORTEX_SLOW);
                }
                else // Was not yet pulled, we pull him back
                    unit->CastSpell(tempSumm, SPELL_DRUID_URSOLS_VORTEX_PULL, true);
            }
        }
    }
};

// Efflorescence
// NPC Id - 47649
class npc_dru_efflorescence : public ScriptedAI
{
public:
    npc_dru_efflorescence(Creature* creature) : ScriptedAI(creature) {}

    void Reset() override
    {
        me->CastSpell(me, SPELL_DRUID_EFFLORESCENCE_DUMMY, true);
        me->SetReactState(REACT_PASSIVE);
    }
};

// Charm Woodland Creature - 127757
class aura_dru_charm_woodland_creature : public AuraScript
{
    PrepareAuraScript(aura_dru_charm_woodland_creature);

    void OnApply(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        // Make targeted creature follow the player - Using pet's default dist and angle
        if (Unit* caster = GetCaster())
            if (Unit* target = GetTarget())
                target->FollowTarget(caster);
    }

    void OnRemove(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* target = GetTarget())
            if (target->GetMotionMaster()->GetCurrentMovementGeneratorType() == FOLLOW_MOTION_TYPE)
                target->GetMotionMaster()->MoveIdle();
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(aura_dru_charm_woodland_creature::OnApply, EFFECT_0, SPELL_AURA_AOE_CHARM, AURA_EFFECT_HANDLE_REAL);
        OnEffectRemove += AuraEffectRemoveFn(aura_dru_charm_woodland_creature::OnRemove, EFFECT_0, SPELL_AURA_AOE_CHARM, AURA_EFFECT_HANDLE_REAL);
    }
};

// Swipe - 106785
class spell_dru_swipe : public SpellScript
{
    PrepareSpellScript(spell_dru_swipe);

    void HandleOnHit(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        int32 damage = GetHitDamage();
        int32 casterLevel = caster->GetLevelForTarget(caster);

        // This prevent awarding multiple Combo Points when multiple targets hit with Swipe AoE
        if (awardComboPoint)
            // Awards the caster 1 Combo Point (get value from the spell data)
            caster->EnergizeBySpell(caster, sSpellMgr->GetSpellInfo(SPELL_DRUID_SWIPE_CAT), sSpellMgr->GetSpellInfo(SPELL_DRUID_SWIPE_CAT)->GetEffect(EFFECT_0).BasePoints, POWER_COMBO_POINTS);

        // If caster has Swipe Rank 2 and the target is bleeding, deals 20% increased damage (get value from the spell data)
        if (caster->HasAura(SPELL_DRUID_SWIPE_RANK_2) && target->HasAuraState(AURA_STATE_BLEED))
            AddPct(damage, sSpellMgr->GetSpellInfo(SPELL_DRUID_SWIPE_CAT)->GetEffect(EFFECT_1).BasePoints);

        // Wild Fleshrending
        if (target->HasAura(SPELL_DRUID_TRASH_CAT, caster->GetGUID()))
            if (Aura* aura = caster->GetAura(SPELL_DRUID_WILD_FLESHRENDING))
                damage += aura->GetEffect(EFFECT_1)->GetAmount();

        SetHitDamage(damage);

        awardComboPoint = false;
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_dru_swipe::HandleOnHit, EFFECT_1, SPELL_EFFECT_DUMMY);
    }

private:
    bool awardComboPoint = true;
};

// Brutal Slash - 202028
class spell_dru_brutal_slash : public SpellScript
{
    PrepareSpellScript(spell_dru_brutal_slash);

    void HandleOnHit(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        // This prevent awarding multiple Combo Points when multiple targets hit with Brutal Slash AoE
        if(m_awardComboPoint)
            // Awards the caster 1 Combo Point (get value from the spell data)
            caster->ModifyPower(POWER_COMBO_POINTS, sSpellMgr->GetSpellInfo(SPELL_DRUID_SWIPE_CAT)->GetEffect(EFFECT_0).BasePoints);

        m_awardComboPoint = false;

        // Wild Fleshrending
        if (target->HasAura(SPELL_DRUID_TRASH_CAT, caster->GetGUID()))
            if (Aura* aura = caster->GetAura(SPELL_DRUID_WILD_FLESHRENDING))
                SetHitDamage(GetHitDamage() + aura->GetEffect(EFFECT_1)->GetAmount());
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_dru_brutal_slash::HandleOnHit, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }

private:
    bool m_awardComboPoint = true;
};

// Thrash (Cat Form) - 106830
class spell_dru_thrash_cat : public SpellScript
{
    PrepareSpellScript(spell_dru_thrash_cat);

    void HandleOnEffectHitTarget(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        // This prevent awarding multiple Combo Points when multiple targets hit with Thrash AoE
        if(m_awardComboPoint)
            // Awards the caster 1 Combo Point
            caster->ModifyPower(POWER_COMBO_POINTS, 1);

        m_awardComboPoint = false;
    }

    void HandleAfterCast()
    {
        // Fix Clearcasting proc only removes Trash when Trash does damage.
        // TODO: Find why? [PROC SYSTEM]
        if (Unit* caster = GetCaster())
            if (caster->HasAura(SPELL_DRUID_CLEARCASTING_FERAL))
                caster->RemoveAurasDueToSpell(SPELL_DRUID_CLEARCASTING_FERAL);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_dru_thrash_cat::HandleOnEffectHitTarget, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
        AfterCast += SpellCastFn(spell_dru_thrash_cat::HandleAfterCast);
    }

private:
    bool m_awardComboPoint = true;
};

// 5221 - Shred
class spell_dru_shred : public SpellScript
{
    PrepareSpellScript(spell_dru_shred);

    bool Load() override
    {
        Unit* caster = GetCaster();

        if (caster->HasAuraType(SPELL_AURA_MOD_STEALTH) || caster->HasAura(340698)) ///< Sudden Ambush
            stealthed = true;

        if (caster->HasAura(SPELL_DRUID_INCARNATION_KING_OF_JUNGLE) || caster->HasAura(106951)) ///< Berserk
            incarnation = true;

        return true;
    }

    void HandleCritChance(Unit const* victim, float& chance)
    {
        if (Unit* caster = GetCaster())
        {
            // Shred Rank 3
            // While stealthed, Shred deals increased damage, and has double the chance to critically strike.
            if (caster->HasAura(SPELL_DRUID_SHRED_RANK_3) && (stealthed || incarnation))
                chance *= 2.0f;

            if (caster->HasAura(SPELL_DRUID_CAT_FORM) && caster->HasAura(SPELL_DRUID_BLOOD_SCENT) && victim->HasAuraState(AURA_STATE_BLEED))
                chance += sSpellMgr->GetSpellInfo(SPELL_DRUID_BLOOD_SCENT)->GetEffect(EFFECT_0).BasePoints;
        }
    }

    void HandleOnEffectHitTarget(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        int32 damage = GetHitDamage();

        // Shred Rank 2
        // Shred deals increased damage against bleeding targets.
        if (caster->HasAura(SPELL_DRUID_SHRED_RANK_2) && target->HasAuraState(AURA_STATE_BLEED))
            AddPct(damage, sSpellMgr->GetSpellInfo(SPELL_DRUID_SHRED)->GetEffect(EFFECT_2).BasePoints);

        // Shred Rank 3
        // While stealthed, Shred deals increased damage, and has double the chance to critically strike.
        if (caster->HasAura(SPELL_DRUID_SHRED_RANK_3) && (stealthed || incarnation))
            AddPct(damage, sSpellMgr->GetSpellInfo(SPELL_DRUID_SHRED)->GetEffect(EFFECT_2).BasePoints);

        SetHitDamage(damage);
    }

    void HandleEnergize(SpellEffIndex effIndex)
    {
        if (Unit* caster = GetCaster())
            if (caster->GetLevel() < 10)
            {
                PreventHitDamage();
                PreventHitDefaultEffect(effIndex);
                PreventHitEffect(effIndex);
            }
    }

    void Register() override
    {
        OnCalcCritChance += SpellOnCalcCritChanceFn(spell_dru_shred::HandleCritChance);
        OnEffectHitTarget += SpellEffectFn(spell_dru_shred::HandleOnEffectHitTarget, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
        OnEffectHitTarget += SpellEffectFn(spell_dru_shred::HandleEnergize, EFFECT_1, SPELL_EFFECT_ENERGIZE);
    }

private:
    bool stealthed = false;
    bool incarnation = false;
};

// 279708 - Empowerments
class aura_dru_empowerments : public AuraScript
{
    PrepareAuraScript(aura_dru_empowerments);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == SPELL_DRUID_STARSURGE_BALANCE)
            return true;

        return false;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();
        if (Unit* caster = GetCaster())
        {
			if (Aura* aura = caster->GetAura(SPELL_DRUID_SOLAR_EMPOWERMENT))
				aura->ModStackAmount(1);
			else
                caster->CastSpell(caster, SPELL_DRUID_SOLAR_EMPOWERMENT, true);
			if (Aura* aura = caster->GetAura(SPELL_DRUID_LUNAR_EMPOWERMENT))
				aura->ModStackAmount(1);
			else
				caster->CastSpell(caster, SPELL_DRUID_LUNAR_EMPOWERMENT, true);
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_dru_empowerments::CheckProc);
        OnProc += AuraProcFn(aura_dru_empowerments::HandleProc);
    }
};

// 194153 / 197628 - Lunar Strike Balance
class spell_dru_lunar_strike_balance : public SpellScript
{
    PrepareSpellScript(spell_dru_lunar_strike_balance);

    void HandleHitTarget(SpellEffIndex effIndex)
    {
        Unit* caster = GetCaster();
        Unit* target = GetExplTargetUnit();

        if (!caster || !target)
            return;

        caster->Variables.Set("LunarStrikeMain", target->GetGUID());
		caster->SendPlaySpellVisual(target->GetGUID(), 78356);
    }

    void HandleAfterCast()
    {
        if (Unit* caster = GetCaster())
        {
            if (caster->HasAura(SPELL_DRUID_OWLKIN_FRENZY) && caster->GetCurrentSpellCastTime(SPELL_DRUID_LUNAR_STRIKE_BALANCE) > 0)
                caster->GetSpellHistory()->RestoreCharge(sSpellMgr->GetSpellInfo(SPELL_DRUID_LUNAR_STRIKE_BALANCE)->ChargeCategoryId);
            else if (caster->HasAura(SPELL_DRUID_OWLKIN_FRENZY) && caster->GetCurrentSpellCastTime(SPELL_DRUID_LUNAR_STRIKE_BALANCE) == 0)
                caster->RemoveAurasDueToSpell(SPELL_DRUID_OWLKIN_FRENZY);
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_dru_lunar_strike_balance::HandleHitTarget, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
        AfterCast += SpellCastFn(spell_dru_lunar_strike_balance::HandleAfterCast);
    }
};

// 197491 - Guardian Affinity for Resto and Balance
class aura_dru_guaridan_affinity_balance_resto : public AuraScript
{
    PrepareAuraScript(aura_dru_guaridan_affinity_balance_resto);

    const std::vector<uint32> LearnedSpells =
    {
        SPELL_DRUID_THICK_HIDE,
        SPELL_DRUID_THRASH,
        SPELL_DRUID_IRON_FUR,
        SPELL_DRUID_FRENZIED_REGENERATION,
    };

    void HandleAppy(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        // Remove wrong auras.
        if (Unit* caster = GetCaster())
        {
            if (caster->ToPlayer()->GetSpecializationId() != TALENT_SPEC_DRUID_BALANCE && caster->ToPlayer()->GetSpecializationId() != TALENT_SPEC_DRUID_RESTORATION)
                caster->RemoveAura(SPELL_DRUID_GUARDIAN_AFFINITY_BALANCE_RESTO);
            else
            {
                if (Player* target = GetTarget()->ToPlayer())
                    for (uint32 spellId : LearnedSpells)
                        target->LearnSpell(spellId, false);
            }
        }
    }

    void HandleRemove(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        // Remove wrong auras.
        if (Unit* caster = GetTarget())
        {
            if (caster->ToPlayer()->GetSpecializationId() == TALENT_SPEC_DRUID_BALANCE || caster->ToPlayer()->GetSpecializationId() == TALENT_SPEC_DRUID_RESTORATION)
                for (uint32 spellId : LearnedSpells)
                    caster->ToPlayer()->RemoveSpell(spellId);
        }
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(aura_dru_guaridan_affinity_balance_resto::HandleAppy, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        OnEffectRemove += AuraEffectRemoveFn(aura_dru_guaridan_affinity_balance_resto::HandleRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

// 217615 - Guardian Affinity for Feral
class aura_dru_guaridan_affinity_feral : public AuraScript
{
    PrepareAuraScript(aura_dru_guaridan_affinity_feral);

    const std::vector<uint32> LearnedSpells =
    {
        SPELL_DRUID_THICK_HIDE,
        SPELL_DRUID_THRASH_BEAR,
        SPELL_DRUID_IRON_FUR,
        SPELL_DRUID_FRENZIED_REGENERATION,
    };

    void HandleAppy(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        // Remove wrong auras.
        if (Unit* caster = GetCaster())
        {
            if (caster->ToPlayer()->GetSpecializationId() != TALENT_SPEC_DRUID_CAT)
                caster->RemoveAura(SPELL_DRUID_GUARDIAN_AFFINITY_FERAL);
            else
            {
                if (Player* target = GetTarget()->ToPlayer())
                    for (uint32 spellId : LearnedSpells)
                        target->LearnSpell(spellId, false);
            }
        }
    }

    void HandleRemove(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        // Remove wrong auras.
        if (Unit* caster = GetTarget())
        {
            if (caster->ToPlayer()->GetSpecializationId() == TALENT_SPEC_DRUID_CAT)
                for (uint32 spellId : LearnedSpells)
                    caster->ToPlayer()->RemoveSpell(spellId);
        }
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(aura_dru_guaridan_affinity_feral::HandleAppy, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        OnEffectRemove += AuraEffectRemoveFn(aura_dru_guaridan_affinity_feral::HandleRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

// 197492 - Resto Affinity for All
class aura_dru_resto_affinity_all : public AuraScript
{
    PrepareAuraScript(aura_dru_resto_affinity_all);

    const std::vector<uint32> LearnedSpells =
    {
        SPELL_DRUID_YSERA_GIFT,
        SPELL_DRUID_REJUVENATION,
        SPELL_DRUID_WILD_GROWTH,
        SPELL_DRUID_SWIFTMEND
    };

    void HandleAppy(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        // Remove wrong auras.
        if (Unit* caster = GetCaster())
        {
            if (caster->ToPlayer()->GetSpecializationId() != TALENT_SPEC_DRUID_BALANCE && caster->ToPlayer()->GetSpecializationId() != TALENT_SPEC_DRUID_CAT &&
                caster->ToPlayer()->GetSpecializationId() != TALENT_SPEC_DRUID_BEAR)
                caster->RemoveAura(SPELL_DRUID_RESTO_ALL);
            else
            {
                if (Player* target = GetTarget()->ToPlayer())
                    for (uint32 spellId : LearnedSpells)
                        target->LearnSpell(spellId, false);
            }
        }
    }

    void HandleRemove(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        // Remove wrong auras.
        if (Unit* caster = GetTarget())
        {
            if (caster->ToPlayer()->GetSpecializationId() == TALENT_SPEC_DRUID_BALANCE || caster->ToPlayer()->GetSpecializationId() == TALENT_SPEC_DRUID_CAT ||
                caster->ToPlayer()->GetSpecializationId() == TALENT_SPEC_DRUID_BEAR)
                for (uint32 spellId : LearnedSpells)
                    caster->ToPlayer()->RemoveSpell(spellId);
        }
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(aura_dru_resto_affinity_all::HandleAppy, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
        OnEffectRemove += AuraEffectRemoveFn(aura_dru_resto_affinity_all::HandleRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

// 197632 - Balance Affinity for Resto
class aura_dru_balance_affinity_resto : public AuraScript
{
    PrepareAuraScript(aura_dru_balance_affinity_resto);

    const std::vector<uint32> LearnedSpells =
    {
        SPELL_DRUID_ASTRAL_INFLUENCE,
        SPELL_DRUID_MOONKING_FORM_AFFINITY,
        SPELL_DRUID_STARSURGE,
        SPELL_DRUID_LUNAR_STRIKE,
    };

    void HandleAppy(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        // Remove wrong auras.
        if (Unit* caster = GetCaster())
        {
            if (caster->ToPlayer()->GetSpecializationId() != TALENT_SPEC_DRUID_RESTORATION)
                caster->RemoveAura(SPELL_DRUID_BALANCE_AFFINITY_RESTO);
            else
            {
                if (Player* target = GetTarget()->ToPlayer())
                {
                    // Remove the old aura if preset. (Just safe check).
                    target->RemoveSpell(SPELL_DRUID_MOONKIN_FORM);
                    for (uint32 spellId : LearnedSpells)
                        target->LearnSpell(spellId, false);
                }
            }
        }
    }

    void HandleRemove(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        // Remove wrong auras.
        if (Unit* caster = GetTarget())
        {
            if (caster->ToPlayer()->GetSpecializationId() == TALENT_SPEC_DRUID_RESTORATION)
                for (uint32 spellId : LearnedSpells)
                    caster->ToPlayer()->RemoveSpell(spellId);
        }
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(aura_dru_balance_affinity_resto::HandleAppy, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        OnEffectRemove += AuraEffectRemoveFn(aura_dru_balance_affinity_resto::HandleRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

// 197488 - Balance Affinity for Feral and Guardian
class aura_dru_balance_affinity_feral_guardian : public AuraScript
{
    PrepareAuraScript(aura_dru_balance_affinity_feral_guardian);

    const std::vector<uint32> LearnedSpells =
    {
        SPELL_DRUID_ASTRAL_INFLUENCE,
        SPELL_DRUID_MOONKING_FORM_AFFINITY,
        SPELL_DRUID_STARSURGE,
        SPELL_DRUID_LUNAR_STRIKE,
        SPELL_DRUID_SOLAR_WRATH,
        SPELL_DRUID_SUNFIRE,
    };

    void HandleAppy(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        // Remove wrong auras.
        if (Unit* caster = GetCaster())
        {
            if (caster->ToPlayer()->GetSpecializationId() != TALENT_SPEC_DRUID_CAT && caster->ToPlayer()->GetSpecializationId() != TALENT_SPEC_DRUID_BEAR)
                caster->RemoveAura(SPELL_DRUID_BALANCE_AFFINITY_FERAL_GUARDIAN);
            else
            {
                if (Player* target = GetTarget()->ToPlayer())
                {
                    // Remove the old aura if preset. (Just safe check).
                    target->RemoveSpell(SPELL_DRUID_MOONKIN_FORM);
                    for (uint32 spellId : LearnedSpells)
                        target->LearnSpell(spellId, false);
                }
            }
        }
    }

    void HandleRemove(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        // Remove wrong auras.
        if (Unit* caster = GetTarget())
        {
            if (caster->ToPlayer()->GetSpecializationId() == TALENT_SPEC_DRUID_CAT || caster->ToPlayer()->GetSpecializationId() == TALENT_SPEC_DRUID_BEAR)
                for (uint32 spellId : LearnedSpells)
                    caster->ToPlayer()->RemoveSpell(spellId);
        }
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(aura_dru_balance_affinity_feral_guardian::HandleAppy, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        OnEffectRemove += AuraEffectRemoveFn(aura_dru_balance_affinity_feral_guardian::HandleRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

// 202155 - Feral Affinity for Guardian
class aura_dru_feral_affinity_guardian : public AuraScript
{
    PrepareAuraScript(aura_dru_feral_affinity_guardian);

    const std::vector<uint32> LearnedSpells =
    {
        SPELL_DRUID_FELINE_SWIFTNESS,
        SPELL_DRUID_RAKE,
        SPELL_DRUID_RIP,
        SPELL_DRUID_FEROCIOUS_BITE
    };

    void HandleAppy(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        // Remove wrong auras.
        if (Unit* caster = GetCaster())
        {
            if (caster->ToPlayer()->GetSpecializationId() != TALENT_SPEC_DRUID_BEAR)
                caster->RemoveAura(SPELL_DRUID_FERAL_AFFINITY_GUARDIAN);
            else
            {
                if (Player* target = GetTarget()->ToPlayer())
                    for (uint32 spellId : LearnedSpells)
                        target->LearnSpell(spellId, false);
            }
        }
    }

    void HandleRemove(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        // Remove wrong auras.
        if (Unit* caster = GetTarget())
        {
            if (caster->ToPlayer()->GetSpecializationId() == TALENT_SPEC_DRUID_BEAR)
                for (uint32 spellId : LearnedSpells)
                    caster->ToPlayer()->RemoveSpell(spellId);
        }
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(aura_dru_feral_affinity_guardian::HandleAppy, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        OnEffectRemove += AuraEffectRemoveFn(aura_dru_feral_affinity_guardian::HandleRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

// 202157 - Feral Affinity for Balance
class aura_dru_feral_affinity_balance : public AuraScript
{
    PrepareAuraScript(aura_dru_feral_affinity_balance);

    const std::vector<uint32> LearnedSpells =
    {
        SPELL_DRUID_FELINE_SWIFTNESS,
        SPELL_DRUID_RAKE,
        SPELL_DRUID_RIP,
        SPELL_DRUID_FEROCIOUS_BITE,
        SPELL_DRUID_SWIPE
    };

    void HandleAppy(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        // Remove wrong auras.
        if (Unit* caster = GetCaster())
        {
            if (caster->ToPlayer()->GetSpecializationId() != TALENT_SPEC_DRUID_BALANCE)
                caster->RemoveAura(SPELL_DRUID_FERAL_AFFINITY_BALANCE);
            else
            {
                if (Player* target = GetTarget()->ToPlayer())
                    for (uint32 spellId : LearnedSpells)
                        target->LearnSpell(spellId, false);

            }
        }
    }

    void HandleRemove(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        // Remove wrong auras.
        if (Unit* caster = GetTarget())
        {
            if (caster->ToPlayer()->GetSpecializationId() == TALENT_SPEC_DRUID_BALANCE)
                for (uint32 spellId : LearnedSpells)
                    caster->ToPlayer()->RemoveSpell(spellId);
        }
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(aura_dru_feral_affinity_balance::HandleAppy, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        OnEffectRemove += AuraEffectRemoveFn(aura_dru_feral_affinity_balance::HandleRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

// 197490 - Feral Affinity for Resto
class aura_dru_feral_affinity_resto : public AuraScript
{
    PrepareAuraScript(aura_dru_feral_affinity_resto);

    const std::vector<uint32> LearnedSpells =
    {
        SPELL_DRUID_FELINE_SWIFTNESS,
        SPELL_DRUID_RAKE,
        SPELL_DRUID_RIP,
        SPELL_DRUID_FEROCIOUS_BITE,
        SPELL_DRUID_SWIPE
    };

    void HandleAppy(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        // Remove wrong auras.
        if (Unit* caster = GetCaster())
        {
            if (caster->ToPlayer()->GetSpecializationId() != TALENT_SPEC_DRUID_RESTORATION)
                caster->RemoveAura(SPELL_DRUID_FERAL_AFFINITY_RESTO);
            else
            {
                if (Player* target = GetTarget()->ToPlayer())
                    for (uint32 spellId : LearnedSpells)
                        target->LearnSpell(spellId, false);
            }
        }
    }

    void HandleRemove(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        // Remove wrong auras.
        if (Unit* caster = GetTarget())
        {
            if (caster->ToPlayer()->GetSpecializationId() == TALENT_SPEC_DRUID_RESTORATION)
                for (uint32 spellId : LearnedSpells)
                    caster->ToPlayer()->RemoveSpell(spellId);
        }
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(aura_dru_feral_affinity_resto::HandleAppy, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        OnEffectRemove += AuraEffectRemoveFn(aura_dru_feral_affinity_resto::HandleRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

// 16974 - Predatory Swiftness
/// Updated 9.2.0
class aura_dru_predatory_swiftness : public AuraScript
{
    PrepareAuraScript(aura_dru_predatory_swiftness);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetProcSpell())
            return false;

        if (!eventInfo.GetProcSpell()->GetUsedComboPoints())
            return false;

        return roll_chance_i(eventInfo.GetProcSpell()->GetUsedComboPoints() * 20);
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();

        if (Unit* caster = GetCaster())
            caster->AddAura(SPELL_DRUID_PREDATORY_SWIFTNESS_AURA, caster);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_dru_predatory_swiftness::CheckProc);
        OnProc += AuraProcFn(aura_dru_predatory_swiftness::HandleProc);
    }
};

// 69369 - Predatory Swiftness
// @Called : Entangling Roots - 339, Regrowth - 8936
class spell_dru_predatory_swiftness_aura : public SpellScript
{
    PrepareSpellScript(spell_dru_predatory_swiftness_aura);

    void HandleAfterCast()
    {
        if (Unit* caster = GetCaster())
        {
            if (caster->HasAura(SPELL_DRUID_PREDATORY_SWIFTNESS_AURA))
                caster->RemoveAurasDueToSpell(SPELL_DRUID_PREDATORY_SWIFTNESS_AURA);
        }
    }

    void Register() override
    {
        AfterCast += SpellCastFn(spell_dru_predatory_swiftness_aura::HandleAfterCast);
    }
};

// 8936 - Regrowth
class spell_dru_regrowth : public SpellScript
{
    PrepareSpellScript(spell_dru_regrowth);

    bool m_HasSoulOfTheForest = false;

	void HandleCritChance(Unit const* victim, float& chance)
	{
        if (Unit* caster = GetCaster())
        {
            if (caster->HasAura(SPELL_DRUID_NOURISH))
            {
                if ((victim->HasAura(SPELL_DRUID_REJUVENATION, caster->GetGUID()) || victim->HasAura(SPELL_DRUID_GERMINATION_REJUVENATION, caster->GetGUID()))
                    && victim->HasAura(SPELL_DRUID_WILD_GROWTH, caster->GetGUID()) && victim->HasAura(SPELL_DRUID_LIFEBLOOM, caster->GetGUID()))
                    chance = 100;
            }

            if (caster->HasAura(SPELL_DRUID_PROTECTOR_OF_THE_GROVE) && caster->GetGUID() != victim->GetGUID())
                if(!victim->HasAura(SPELL_DRUID_REGROWTH))
                    chance = 100;
        }
	}

    void HandleAfterCast()
    {
        Unit* caster = GetCaster();
        Unit* target = GetExplTargetUnit();
        if (!caster || !target)
            return;

        if (caster->HasAura(SPELL_DRUID_PREDATORY_SWIFTNESS_AURA))
            caster->RemoveAurasDueToSpell(SPELL_DRUID_PREDATORY_SWIFTNESS_AURA);

        if (caster->HasAura(SPELL_DRUID_PROTECTOR_OF_THE_GROVE) && caster->GetGUID() != target->GetGUID())
            caster->CastSpell(caster, SPELL_DRUID_PROTECTOR_OF_THE_GROVE_CAST, true);

        caster->RemoveAurasDueToSpell(SPELL_DRUID_CLEARCASTING);
        caster->RemoveAurasDueToSpell(SPELL_DRUID_MASTER_SHAPESHIFTER_HEAL);
    }

    void HandleHit()
    {
		Unit* caster = GetCaster();
		Unit* target = GetHitUnit();
		if (!caster || !target)
			return;

		if (caster->HasAura(SPELL_DRUID_SOUL_OF_THE_FOREST_RESTO))
		{
			int32 baseHealing = GetHitHeal();
			SetHitHeal(baseHealing + CalculatePct(baseHealing, sSpellMgr->GetSpellInfo(SPELL_DRUID_SOUL_OF_THE_FOREST_RESTO)->GetEffect(EFFECT_1).BasePoints));
		}

		if (caster->HasAura(SPELL_DRUID_NOURISH))
		{
			if (target->HasAura(SPELL_DRUID_REJUVENATION, caster->GetGUID()) && target->HasAura(SPELL_DRUID_WILD_GROWTH, caster->GetGUID()) &&
				target->HasAura(SPELL_DRUID_LIFEBLOOM, caster->GetGUID()))
				return;

			std::list<uint32> randomHOTs;
			if (!target->HasAura(SPELL_DRUID_REJUVENATION, caster->GetGUID()))
				randomHOTs.push_back(SPELL_DRUID_REJUVENATION);
			if (!target->HasAura(SPELL_DRUID_WILD_GROWTH, caster->GetGUID()))
				randomHOTs.push_back(SPELL_DRUID_WILD_GROWTH);
			if (!target->HasAura(SPELL_DRUID_LIFEBLOOM, caster->GetGUID()))
				randomHOTs.push_back(SPELL_DRUID_LIFEBLOOM);

			// Pick a random one
			if (randomHOTs.size() > 1)
				Trinity::Containers::RandomResize(randomHOTs, 1);
			for (uint32 spell : randomHOTs)
			{
				if (spell == SPELL_DRUID_WILD_GROWTH)
					caster->AddAura(spell, target);
				else
					caster->CastSpell(target, spell, true);
			}
		}
    }

    void HandleAfterHit()
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        // If soul of the forest is activated we increase the heal by 200%
        if (AuraEffect* regrowth = target->GetAuraEffect(GetSpellInfo()->Id, EFFECT_1, caster->GetGUID()))
        {
            if (caster->HasAura(SPELL_DRUID_SOUL_OF_THE_FOREST_RESTO) || m_HasSoulOfTheForest)
            {
                uint8 SoulofTheForestBonus = sSpellMgr->GetSpellInfo(SPELL_DRUID_SOUL_OF_THE_FOREST_RESTO)->GetEffect(EFFECT_1).BasePoints;
                if (!SoulofTheForestBonus)
                    return;

                regrowth->SetDamage(regrowth->GetDamage() + CalculatePct(regrowth->GetDamage(), SoulofTheForestBonus));
                m_HasSoulOfTheForest = true;
                caster->RemoveAurasDueToSpell(SPELL_DRUID_SOUL_OF_THE_FOREST_RESTO);
            }
        }       
    }

    void HandleEffectHit(SpellEffIndex /*effIndex*/)
    {
        if (Unit* caster = GetCaster())
        {
            if (caster->Variables.Exist("OVERGROWTH") && caster->Variables.GetValue<bool>("OVERGROWTH"))
                PreventHitHeal();

            auto heal = GetHitHeal();

            if (auto innateResolve = caster->GetAuraEffect(340543, EFFECT_0))
                if (innateResolve)
                    if (innateResolve->ConduitRankEntry)
                        AddPct(heal, innateResolve->ConduitRankEntry->AuraPointsOverride);

            SetHitHeal(heal);
        }
    }

    void Register() override
    {
		OnCalcCritChance += SpellOnCalcCritChanceFn(spell_dru_regrowth::HandleCritChance);
        OnHit += SpellHitFn(spell_dru_regrowth::HandleHit);
        AfterHit += SpellHitFn(spell_dru_regrowth::HandleAfterHit);
        AfterCast += SpellCastFn(spell_dru_regrowth::HandleAfterCast);
        OnEffectHitTarget += SpellEffectFn(spell_dru_regrowth::HandleEffectHit, EFFECT_0, SPELL_EFFECT_HEAL);
    }
};

// 8936 - Regrowth aura
class aura_dru_regrowth : public AuraScript
{
    PrepareAuraScript(aura_dru_regrowth);

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
        Unit* caster = GetCaster();
        Unit* owner = GetUnitOwner();
        if (!caster || !owner)
            return;

        if (caster->HasAura(SPELL_DRUID_PHOTOSYNTHESIS) && caster->GetGUID() != owner->GetGUID() && owner->HasAura(SPELL_DRUID_LIFEBLOOM, caster->GetGUID()) &&
            roll_chance_i(sSpellMgr->GetSpellInfo(SPELL_DRUID_PHOTOSYNTHESIS)->GetEffect(EFFECT_1).BasePoints))
            owner->RemoveAurasDueToSpell(SPELL_DRUID_LIFEBLOOM, caster->GetGUID(), 0, AURA_REMOVE_BY_EXPIRE);
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(aura_dru_regrowth::HandlePeriodic, EFFECT_1, SPELL_AURA_PERIODIC_HEAL);
    }
};

// 135700 - Clearcasting
class aura_dru_clearcasting : public AuraScript
{
    PrepareAuraScript(aura_dru_clearcasting);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetSpellInfo())
            return false;

        switch (eventInfo.GetSpellInfo()->Id)
        {
            case SPELL_DRUID_SHRED:
            case SPELL_DRUID_TRASH_CAT:
            case SPELL_DRUID_SWIPE_CAT:
            case SPELL_DRUID_BRUTAL_SLASH:
                return true;
            default:
                return false;
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_dru_clearcasting::CheckProc);
    }
};

// 155578 - Guardian of Elune
class aura_dru_guardian_of_elune : public AuraScript
{
	PrepareAuraScript(aura_dru_guardian_of_elune);

	bool CheckProc(ProcEventInfo& eventInfo)
	{
		if (eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == SPELL_DRUID_MANGLE)
			return true;

		return false;
	}

	void HandleProc(ProcEventInfo& eventInfo)
	{
		PreventDefaultAction();

		if (Unit* caster = GetCaster())
			caster->CastSpell(caster, SPELL_DRUID_GUARDIAN_OF_ELUNE_AURA, true);
	}

	void Register() override
	{
		DoCheckProc += AuraCheckProcFn(aura_dru_guardian_of_elune::CheckProc);
		OnProc += AuraProcFn(aura_dru_guardian_of_elune::HandleProc);
	}
};

// 213680 - Guardian of Elune Aura
class aura_dru_guardian_of_elune_aura : public AuraScript
{
	PrepareAuraScript(aura_dru_guardian_of_elune_aura);

	bool CheckProc(ProcEventInfo& eventInfo)
	{
		if (eventInfo.GetSpellInfo() && (eventInfo.GetSpellInfo()->Id == SPELL_DRUID_IRON_FUR || eventInfo.GetSpellInfo()->Id == SPELL_DRUID_FRENZIED_REGENERATION))
			return true;

		return false;
	}

	void Register() override
	{
		DoCheckProc += AuraCheckProcFn(aura_dru_guardian_of_elune_aura::CheckProc);
	}
};

// 339 - Entangling Roots
class aura_dru_entangling_roots : public AuraScript
{
	PrepareAuraScript(aura_dru_entangling_roots);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetDamageInfo() && (eventInfo.GetDamageInfo()->GetDamageType() != HEAL && eventInfo.GetDamageInfo()->GetDamageType() != NODAMAGE))
        {
            Unit* caster = GetCaster();
            Unit* target = GetTarget();
            if (!caster || !target)
                return false;

            Aura* aura = GetAura();
            if (aura->GetId() != SPELL_DRUID_ENTANGLING_ROOTS && aura->GetId() != SPELL_DRUID_ENTANGLING_ROOTS_2)
                return false;

            // Fear will be removed if the damage if greater or equal to 10% of the target maximun health.
            uint32 ten = CalculatePct(target->GetMaxHealth(), !caster->HasAura(SPELL_DRUID_DEEP_ROOTS) ? 10 : 30);
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

	void HandleRemove(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /* mode */)
	{
		Unit* caster = GetCaster();
		Unit* owner = GetUnitOwner();
		if (!caster || !owner)
			return;

		if (GetTargetApplication()->GetRemoveMode() != AURA_REMOVE_BY_DEATH && caster->HasAura(SPELL_DRUID_PRICKLING_TORNS))
			caster->CastSpell(owner, SPELL_DRUID_PRICKLING_TORNS_DAMAGE, true);
	}

	void Register() override
	{
		DoCheckProc += AuraCheckProcFn(aura_dru_entangling_roots::CheckProc);
		OnProc += AuraProcFn(aura_dru_entangling_roots::HandleProc);
		OnEffectRemove += AuraEffectRemoveFn(aura_dru_entangling_roots::HandleRemove, EFFECT_0, SPELL_AURA_MOD_ROOT_2, AURA_EFFECT_HANDLE_REAL);
	}
};

// 155722 - Rake Aura
class aura_dru_rake : public AuraScript
{
	PrepareAuraScript(aura_dru_rake);

    void HandleApply(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
    {
        Unit* caster = GetCaster();
        if (!caster)
            return;

        if (caster->Variables.Exist("IncreassedRakeDmg"))
        {
            caster->Variables.Remove("IncreassedRakeDmg");
            const_cast<AuraEffect*>(aurEff)->SetDamage(aurEff->GetDamage() + CalculatePct(aurEff->GetDamage(), 60));
            const_cast<AuraEffect*>(aurEff)->ChangeAmount(aurEff->GetDamage());
        }
        _originalDamage = 0;
    }

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
	{
		Unit* caster = GetCaster();
		if (!caster)
			return;

		if (caster->HasAura(SPELL_DRUID_PREDATOR))
		{
			if (GetTargetApplication() && GetTargetApplication()->GetRemoveMode() != AURA_REMOVE_BY_DEATH)
				return;

			caster->GetSpellHistory()->ResetCooldown(SPELL_DRUID_TIGERS_FURY, true);
		}
	}

    void HandlePeriodic(AuraEffect const* aurEff)
    {
        auto caster = GetCaster();
        if (!caster)
            return;
        auto target = GetTarget();
        if (!target)
            return;

        if (_originalDamage > 0)
        {
            if (!Druid::CanDraughtOfDeepFocus(caster, target, GetId()))
            {
                const_cast<AuraEffect*>(aurEff)->ChangeAmount(_originalDamage);
                const_cast<AuraEffect*>(aurEff)->SetDamage(_originalDamage);
                _originalDamage = 0;
            }
        }
        else
        {
            if (Druid::CanDraughtOfDeepFocus(caster, target, GetId()))
            {
                _originalDamage = aurEff->GetDamage();
                uint32 newDmg = CalculatePct(aurEff->GetDamage(), 140);;
                const_cast<AuraEffect*>(aurEff)->SetDamage(newDmg);
                const_cast<AuraEffect*>(aurEff)->ChangeAmount(newDmg);
            }
        }
    }

    uint32 _originalDamage = 0;

	void Register() override
	{
        OnEffectApply += AuraEffectApplyFn(aura_dru_rake::HandleApply, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE, AURA_EFFECT_HANDLE_REAL);
        OnEffectRemove += AuraEffectRemoveFn(aura_dru_rake::HandleRemove, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE, AURA_EFFECT_HANDLE_REAL);
        OnEffectPeriodic += AuraEffectPeriodicFn(aura_dru_rake::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE);
	}

private:
    bool stealthed = false;
};

// 106830 - Thrash Aura
class aura_dru_thrash : public AuraScript
{
	PrepareAuraScript(aura_dru_thrash);

	void HandleRemove(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
	{
		Unit* caster = GetCaster();
		if (!caster)
			return;

		if (caster->HasAura(SPELL_DRUID_PREDATOR))
		{
			if (GetTargetApplication()->GetRemoveMode() != AURA_REMOVE_BY_DEATH)
				return;

			caster->GetSpellHistory()->ResetCooldown(SPELL_DRUID_TIGERS_FURY, true);
		}
	}

	void Register() override
	{
		OnEffectRemove += AuraEffectRemoveFn(aura_dru_thrash::HandleRemove, EFFECT_1, SPELL_AURA_PERIODIC_DAMAGE, AURA_EFFECT_HANDLE_REAL);
	}
};

// 279620 - Twin Moons
class aura_dru_twin_moons : public AuraScript
{
	PrepareAuraScript(aura_dru_twin_moons);

	bool CheckProc(ProcEventInfo& eventInfo)
	{
		if (eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == SPELL_DRUID_MOONFIRE)
			return true;

		return false;
	}

	void Register() override
	{
		DoCheckProc += AuraCheckProcFn(aura_dru_twin_moons::CheckProc);
	}
};

// 164815 - Sunfire Damage
class aura_dru_sunfire_damage : public AuraScript
{
	PrepareAuraScript(aura_dru_sunfire_damage);

	void HandlePeriodic(AuraEffect const* /*aurEff*/)
	{
		Unit* caster = GetCaster();
		Unit* target = GetUnitOwner();
		if (!caster || !target)
			return;

		if (Aura* aura = caster->GetAura(SPELL_DRUID_SHOOTING_STARTS))
			if (roll_chance_i(aura->GetEffect(EFFECT_0)->GetAmount()))			
				caster->CastSpell(target, SPELL_DRUID_SHOOTING_START, true);			
	}

	void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes mode)
	{
		if (Unit* caster = GetCaster())
			if (GetTargetApplication()->GetRemoveMode() == AURA_REMOVE_BY_ENEMY_SPELL && caster->HasAura(SPELL_DRUID_DYING_STARS))
				caster->CastSpell(caster, SPELL_DRUID_DYING_STARS_ENERGIZE, true);
	}

	void Register() override
	{
		OnEffectPeriodic += AuraEffectPeriodicFn(aura_dru_sunfire_damage::HandlePeriodic, EFFECT_1, SPELL_AURA_PERIODIC_DAMAGE);
		OnEffectRemove += AuraEffectRemoveFn(aura_dru_sunfire_damage::HandleRemove, EFFECT_1, SPELL_AURA_PERIODIC_DAMAGE, AURA_EFFECT_HANDLE_REAL);
	}
};

// 164812 - Moonfire Damage
class aura_dru_moonfire_damage : public AuraScript
{
	PrepareAuraScript(aura_dru_moonfire_damage);

	void HandlePeriodic(AuraEffect const* aurEff)
	{
		Unit* caster = GetCaster();
		Unit* target = GetUnitOwner();
		if (!caster || !target)
			return;

		if (Aura* aura = caster->GetAura(SPELL_DRUID_SHOOTING_STARTS))
			if (roll_chance_i(aura->GetEffect(EFFECT_0)->GetAmount()))			
				caster->CastSpell(target, SPELL_DRUID_SHOOTING_START, true);

        if (_originalDamage > 0)
        {
            if (!Druid::CanDraughtOfDeepFocus(caster, target, GetId()))
            {
                const_cast<AuraEffect*>(aurEff)->ChangeAmount(_originalDamage);
                const_cast<AuraEffect*>(aurEff)->SetDamage(_originalDamage);
                _originalDamage = 0;
            }
        }
        else
        {
            if (Druid::CanDraughtOfDeepFocus(caster, target, GetId()))
            {
                _originalDamage = aurEff->GetDamage();
                uint32 newDmg = CalculatePct(aurEff->GetDamage(), 140);;
                const_cast<AuraEffect*>(aurEff)->SetDamage(newDmg);
                const_cast<AuraEffect*>(aurEff)->ChangeAmount(newDmg);
            }
        }
	}

	void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes mode)
	{
		if (Unit* caster = GetCaster())
			if (GetTargetApplication()->GetRemoveMode() == AURA_REMOVE_BY_ENEMY_SPELL && caster->HasAura(SPELL_DRUID_DYING_STARS))
				caster->CastSpell(caster, SPELL_DRUID_DYING_STARS_ENERGIZE, true);
	}

    void HandleApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes mode)
    {
        _originalDamage = 0;
    }

    uint32 _originalDamage = 0;

	void Register() override
	{
		OnEffectPeriodic += AuraEffectPeriodicFn(aura_dru_moonfire_damage::HandlePeriodic, EFFECT_1, SPELL_AURA_PERIODIC_DAMAGE);
        OnEffectApply += AuraEffectApplyFn(aura_dru_moonfire_damage::HandleApply, EFFECT_1, SPELL_AURA_PERIODIC_DAMAGE, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
        OnEffectRemove += AuraEffectRemoveFn(aura_dru_moonfire_damage::HandleRemove, EFFECT_1, SPELL_AURA_PERIODIC_DAMAGE, AURA_EFFECT_HANDLE_REAL);
	}
};

// 203953 - Brambles
class aura_dru_brambles : public AuraScript
{
	PrepareAuraScript(aura_dru_brambles);

	void CalcAmount(AuraEffect const* /*aurEff*/, int32& amount, bool& /*canBeRecalculated*/)
	{
		amount = -1;
	}

	void OnAbsorb(AuraEffect* aurEff, DamageInfo& dmgInfo, uint32& absorbAmount)
	{
		if (Unit* caster = GetCaster())
		{
			if (dmgInfo.GetDamage() == 0)
				return;

            uint32 amount = caster->m_unitData->AttackPower * 0.06f;
			absorbAmount = amount;

            // The spell should not be triggered by it self or my create a infinite loop
            // Should absob but thats it
            if (auto baseSpellInfo = GetSpellInfo())
                if (auto spellInfo = dmgInfo.GetSpellInfo())
                    if (baseSpellInfo->Id == spellInfo->Id || spellInfo->Id == SPELL_DRUID_BRAMBLES_REFLECTION)
                        return;

			if (dmgInfo.GetAttacker() && caster->IsValidAttackTarget(dmgInfo.GetAttacker()))
				caster->CastCustomSpell(SPELL_DRUID_BRAMBLES_REFLECTION, SPELLVALUE_BASE_POINT0, amount, dmgInfo.GetAttacker(), true, nullptr, aurEff);
		}
	}

	void Register() override
	{
		DoEffectCalcAmount += AuraEffectCalcAmountFn(aura_dru_brambles::CalcAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
		OnEffectAbsorb += AuraEffectAbsorbFn(aura_dru_brambles::OnAbsorb, EFFECT_0);
	}
};

// 22812 - Barkskin
// Last Update 8.0.1 Build 28153
class aura_dru_barkskin : public AuraScript
{
	PrepareAuraScript(aura_dru_barkskin);

    void HandleApply(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /* mode */)
    {
        if (Unit* caster = GetCaster())
        {
            if (AuraEffect* aurEff = caster->GetAuraEffect(SPELL_DRUID_URSOC_ENDURANCE_POWER, EFFECT_0))
                caster->CastCustomSpell(SPELL_DRUID_URSOC_ENDURANCE_BUFF, SPELLVALUE_BASE_POINT0, aurEff->GetAmount(), caster, true);

            if (caster->HasAura(Druid::eLegendary::TheNaturalOrdersWill))
                if (caster->HasAura(Druid::eDruid::BearForm))
                {
                    caster->CastSpell(caster, Druid::eGuardian::FrenziedRegeneration, CastSpellExtraArgs(TRIGGERED_FULL_MASK_NO_CD));
                    caster->CastSpell(caster, Druid::eGuardian::Ironfur, CastSpellExtraArgs(TRIGGERED_FULL_MASK_NO_CD));
                }
        }
    }

    void HandleRemove(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /* mode */)
    {
        if (Unit* caster = GetCaster())
        {
            if (caster->HasAura(Druid::eLegendary::TheNaturalOrdersWill))
                if (caster->HasAura(Druid::eDruid::BearForm))
                {
                    caster->CastSpell(caster, Druid::eGuardian::FrenziedRegeneration, CastSpellExtraArgs(TRIGGERED_FULL_MASK_NO_CD));
                    caster->CastSpell(caster, Druid::eGuardian::Ironfur, CastSpellExtraArgs(TRIGGERED_FULL_MASK_NO_CD));
                }
        }
    }

	void OnTick(AuraEffect const* /*aurEff*/)
	{
        if (Unit* caster = GetCaster())
            if (caster->HasAura(SPELL_DRUID_BRAMBLES))
                caster->CastSpell(caster, SPELL_DRUID_BRAMBLES_REFLECTION_AOE, true);       
	}

	void Register() override
	{
        OnEffectApply += AuraEffectApplyFn(aura_dru_barkskin::HandleApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
        OnEffectRemove += AuraEffectRemoveFn(aura_dru_barkskin::HandleRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
		OnEffectPeriodic += AuraEffectPeriodicFn(aura_dru_barkskin::OnTick, EFFECT_4, SPELL_AURA_PERIODIC_DUMMY);
	}
};

// 274281 - New Moon / 274282 - Half Moon / 274283 - Full Moon
class spell_dru_moons : public SpellScript
{
	PrepareSpellScript(spell_dru_moons);

	enum  MoonOverriders
	{
		SPELL_NEW_MOON_OVERRIDE		= 274295,
		SPELL_HALF_MOON_OVERRIDE	= 274297,
		SPELL_FULL_MOON_OVERRIDE	= 202789,
	};

	enum MoonSpells
	{
		SPELL_NEW_MOON				= 274281,
		SPELL_HALF_MOON				= 274282,
		SPELL_FULL_MOON				= 274283,
	};

    void HandleOnObjectAreaTargetSelect(std::list<WorldObject*>& targets)
    {
        counter = targets.size();
    }

    void HandleOnEffectHitTarget(SpellEffIndex /*effIndex*/)
    {
        if (GetSpellInfo()->Id == SPELL_FULL_MOON)
        {
            Unit* target = GetHitUnit();
            Unit* expTarget = GetExplTargetUnit();
            if (!target || !expTarget)
                return;

            if (target->GetGUID() != expTarget->GetGUID())
                SetHitDamage(GetHitDamage() / counter);
        }
    }

	void HandleAfterCast()
	{
		if (Unit* caster = GetCaster())
			switch (GetSpellInfo()->Id)
			{
				case SPELL_NEW_MOON:
					caster->CastSpell(caster, SPELL_NEW_MOON_OVERRIDE, true);
					break;
				case SPELL_HALF_MOON:
					caster->RemoveAura(SPELL_NEW_MOON_OVERRIDE);
					caster->CastSpell(caster, SPELL_HALF_MOON_OVERRIDE, true);
					break;
				case SPELL_FULL_MOON:
					caster->RemoveAura(SPELL_HALF_MOON_OVERRIDE);
					return;
				default:
					break;
			}
	}

	void Register() override
	{
		AfterCast += SpellCastFn(spell_dru_moons::HandleAfterCast);
        OnEffectHitTarget += SpellEffectFn(spell_dru_moons::HandleOnEffectHitTarget, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_dru_moons::HandleOnObjectAreaTargetSelect, EFFECT_0, TARGET_UNIT_DEST_AREA_ENEMY);
	}

private:
    uint8 counter = 0;
};

// 202430 - Nature's Balance
class aura_dru_nature_balance : public AuraScript
{
    PrepareAuraScript(aura_dru_nature_balance);

    void HandleApply(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /* mode */)
    {
        if (Unit* caster = GetCaster())
        {
            if (!caster->HasAura(SPELL_DRUID_CAT_FORM) && !caster->HasAura(SPELL_DRUID_BEAR_FORM))
            {
                if (caster->GetPower(POWER_LUNAR_POWER) > caster->GetMaxPower(POWER_LUNAR_POWER) * 0.5f + 5)
                {
                    caster->RemoveAura(SPELL_DRUID_NATURES_BALANCE_FREEZE);
                    caster->SetUnitFlag2(UNIT_FLAG2_REGENERATE_POWER);
                }
                else if (caster->GetPower(POWER_LUNAR_POWER) < caster->GetMaxPower(POWER_LUNAR_POWER) * 0.5f - 5)
                {
                    caster->CastSpell(caster, SPELL_DRUID_NATURES_BALANCE_FREEZE, true);
                    caster->RemoveUnitFlag2(UNIT_FLAG2_REGENERATE_POWER);
                }
                else
                {
                    caster->CastSpell(caster, SPELL_DRUID_NATURES_BALANCE_FREEZE, true);
                    caster->RemoveUnitFlag2(UNIT_FLAG2_REGENERATE_POWER);
                    caster->SetPower(POWER_LUNAR_POWER, caster->GetMaxPower(POWER_LUNAR_POWER) * 0.5f);
                }
            }

            // Set the ticker.
            caster->CastSpell(caster, SPELL_DRUID_NATURES_BALANCE_TICKER, true);
        }
    }

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
        if (Unit* caster = GetCaster())
        {
            if (caster->IsAlive())
            {
                if (!caster->HasAura(SPELL_DRUID_NATURES_BALANCE_TICKER))
                {
                    if (!caster->HasAura(SPELL_DRUID_CAT_FORM) && !caster->HasAura(SPELL_DRUID_BEAR_FORM))
                    {
                        if (caster->GetPower(POWER_LUNAR_POWER) > caster->GetMaxPower(POWER_LUNAR_POWER) * 0.5f + 5)
                        {
                            caster->RemoveAura(SPELL_DRUID_NATURES_BALANCE_FREEZE);
                            caster->SetUnitFlag2(UNIT_FLAG2_REGENERATE_POWER);
                        }
                        else if (caster->GetPower(POWER_LUNAR_POWER) < caster->GetMaxPower(POWER_LUNAR_POWER) * 0.5f - 5)
                        {
                            caster->CastSpell(caster, SPELL_DRUID_NATURES_BALANCE_FREEZE, true);
                            caster->RemoveUnitFlag2(UNIT_FLAG2_REGENERATE_POWER);
                        }
                        else
                        {
                            caster->CastSpell(caster, SPELL_DRUID_NATURES_BALANCE_FREEZE, true);
                            caster->RemoveUnitFlag2(UNIT_FLAG2_REGENERATE_POWER);
                            caster->SetPower(POWER_LUNAR_POWER, caster->GetMaxPower(POWER_LUNAR_POWER) * 0.5f);
                        }
                    }

                    caster->CastSpell(caster, SPELL_DRUID_NATURES_BALANCE_TICKER, true);
                }

                if (!caster->IsInCombat())
                    GetAura()->GetEffect(EFFECT_0)->SetAmount(0);
                else
                {
                    if (!caster->HasAura(SPELL_DRUID_CAT_FORM) && !caster->HasAura(SPELL_DRUID_BEAR_FORM))
                        GetAura()->GetEffect(EFFECT_0)->SetAmount(20);
                }
            }            
        }
    }

    void HandleRemove(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /* mode */)
    {
        if (Unit* caster = GetCaster())
        {
            caster->RemoveAura(SPELL_DRUID_NATURES_BALANCE_FREEZE);
            caster->RemoveAura(SPELL_DRUID_NATURES_BALANCE_TICKER);
            caster->SetUnitFlag2(UNIT_FLAG2_REGENERATE_POWER);
        }
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(aura_dru_nature_balance::HandleApply, EFFECT_0, SPELL_AURA_PERIODIC_ENERGIZE, AURA_EFFECT_HANDLE_REAL);
        OnEffectPeriodic += AuraEffectPeriodicFn(aura_dru_nature_balance::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_ENERGIZE);
        OnEffectRemove += AuraEffectRemoveFn(aura_dru_nature_balance::HandleRemove, EFFECT_0, SPELL_AURA_PERIODIC_ENERGIZE, AURA_EFFECT_HANDLE_REAL);
    }
};

// 279652 - Nature's Balance Ticker
class aura_dru_natures_balance_ticker : public AuraScript
{
    PrepareAuraScript(aura_dru_natures_balance_ticker);

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
        if (Unit* caster = GetCaster())
        {
            if (!caster->IsInCombat() && !caster->HasAura(SPELL_DRUID_CAT_FORM) && !caster->HasAura(SPELL_DRUID_BEAR_FORM))
            {
                if (caster->GetPower(POWER_LUNAR_POWER) > caster->GetMaxPower(POWER_LUNAR_POWER) * 0.5f + 5)
                {
                    caster->RemoveAura(SPELL_DRUID_NATURES_BALANCE_FREEZE);
                    caster->SetUnitFlag2(UNIT_FLAG2_REGENERATE_POWER);
                }
                else if (caster->GetPower(POWER_LUNAR_POWER) < caster->GetMaxPower(POWER_LUNAR_POWER) * 0.5f - 5)
                {
                    caster->CastSpell(caster, SPELL_DRUID_NATURES_BALANCE_FREEZE, true);
                    caster->RemoveUnitFlag2(UNIT_FLAG2_REGENERATE_POWER);
                    uint32 amount = (caster->GetMaxPower(POWER_LUNAR_POWER) * 0.5f - caster->GetPower(POWER_LUNAR_POWER) > 20) ? 20 : caster->GetMaxPower(POWER_LUNAR_POWER) * 0.5f - caster->GetPower(POWER_LUNAR_POWER);
                    caster->ModifyPower(POWER_LUNAR_POWER, amount);
                }
                else
                {
                    caster->CastSpell(caster, SPELL_DRUID_NATURES_BALANCE_FREEZE, true);
                    caster->RemoveUnitFlag2(UNIT_FLAG2_REGENERATE_POWER);
                    caster->SetPower(POWER_LUNAR_POWER, caster->GetMaxPower(POWER_LUNAR_POWER) * 0.5f);
                }
            }
            else
            {
                caster->RemoveAura(SPELL_DRUID_NATURES_BALANCE_FREEZE);
                caster->SetUnitFlag2(UNIT_FLAG2_REGENERATE_POWER);
            }
        }
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(aura_dru_natures_balance_ticker::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

// 274838 - Feral Frenzy
//Last Update 8.0.1 Build 28153
class spell_dru_feral_frenzy : public SpellScript
{
    PrepareSpellScript(spell_dru_feral_frenzy);

    void CalcCrit(Unit const* victim, float& chance)
    {
        if (Unit* caster = GetCaster())
            if (caster->HasAura(SPELL_DRUID_CAT_FORM) && caster->HasAura(SPELL_DRUID_BLOOD_SCENT) && victim->HasAuraState(AURA_STATE_BLEED))
                chance += sSpellMgr->GetSpellInfo(SPELL_DRUID_BLOOD_SCENT)->GetEffect(EFFECT_0).BasePoints;
    }

    void Register() override
    {
        OnCalcCritChance += SpellOnCalcCritChanceFn(spell_dru_feral_frenzy::CalcCrit);
    }
};

// 274838 - Feral Frenzy
//Last Update 8.0.1 Build 28153
class aura_dru_feral_frenzy_damage : public AuraScript
{
	PrepareAuraScript(aura_dru_feral_frenzy_damage);

    void HandleApply(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* caster = GetCaster())
        {            
            auto effect1 = GetAura()->GetEffect(EFFECT_1);
            auto effect2 = GetAura()->GetEffect(EFFECT_2);

            if (effect1 && effect2)
                effect1->ChangeAmount(effect2->GetDamage());
        } 
    }

	void Register() override
	{		
        AfterEffectApply += AuraEffectApplyFn(aura_dru_feral_frenzy_damage::HandleApply, EFFECT_1, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
	}
};

// 236026 - Enraged Maim
class spell_dru_enraged_maim : public SpellScript
{
    PrepareSpellScript(spell_dru_enraged_maim);

    void HandleOnTakePower(SpellPowerCost& powerCost)
    {
        if (powerCost.Power == POWER_COMBO_POINTS)
        {
            comboPoints = powerCost.Amount;
        }
    }

    void CalcCrit(Unit const* victim, float& chance)
    {
        if (Unit* caster = GetCaster())
            if (caster->HasAura(SPELL_DRUID_CAT_FORM) && caster->HasAura(SPELL_DRUID_BLOOD_SCENT) && victim->HasAuraState(AURA_STATE_BLEED))
                chance += sSpellMgr->GetSpellInfo(SPELL_DRUID_BLOOD_SCENT)->GetEffect(EFFECT_0).BasePoints;
    }

    void HandleEffectHitTarget(SpellEffIndex /*effIndex*/)
    {
        if (Unit* caster = GetCaster())
            if (caster->HasAura(SPELL_DRUID_SOUL_OF_THE_FOREST))
                caster->CastCustomSpell(SPELL_DRUID_SOUL_OF_THE_FOREST_FERAL_ENERGIZE, SPELLVALUE_BASE_POINT0, comboPoints * sSpellMgr->GetSpellInfo(SPELL_DRUID_SOUL_OF_THE_FOREST)->GetEffect(EFFECT_0).BasePoints, caster, true);
    }

    void Register() override
    {
        OnTakePower += SpellOnTakePowerFn(spell_dru_enraged_maim::HandleOnTakePower);
        OnEffectHitTarget += SpellEffectFn(spell_dru_enraged_maim::HandleEffectHitTarget, EFFECT_2, SPELL_EFFECT_SCHOOL_DAMAGE);
        OnCalcCritChance += SpellOnCalcCritChanceFn(spell_dru_enraged_maim::CalcCrit);
    }

private:
    uint8 comboPoints = 0;
};

// 203242 - Rip and Tear
class spell_dru_rip_and_tear : public SpellScript
{
    PrepareSpellScript(spell_dru_rip_and_tear);

    void HandleHit()
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        caster->CastSpell(target, SPELL_DRUID_RIP, true);
        caster->CastSpell(target, SPELL_DRUID_RAKE, true);
    }

    void Register() override
    {
        OnHit += SpellHitFn(spell_dru_rip_and_tear::HandleHit);
    }
};

// 774 - Rejuvenation
class aura_dru_rejuvenation : public AuraScript
{
	PrepareAuraScript(aura_dru_rejuvenation);

	bool Validate(SpellInfo const* /*spellInfo*/) override
	{
		return ValidateSpellInfo({ SPELL_DRUID_ABUNDANCE, SPELL_DRUID_ABUNDANCE_BUFF, SPELL_DRUID_PHOTOSYNTHESIS, SPELL_DRUID_LIFEBLOOM, SPELL_DRUID_CULTIVATION });
	}

	void AfterRemove(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
	{
		if (Unit* caster = GetCaster())
			if (caster->HasAura(SPELL_DRUID_ABUNDANCE))
				if (Aura* abundanceBuff = caster->GetAura(SPELL_DRUID_ABUNDANCE_BUFF))
					abundanceBuff->ModStackAmount(-1);
	}

    void HandlePeriodic(AuraEffect const* aurEff)
    {
        Unit* caster = GetCaster();
        Unit* owner = GetUnitOwner();
        if (!caster || !owner)
            return;

        if (caster->HasAura(SPELL_DRUID_PHOTOSYNTHESIS) && caster->GetGUID() != owner->GetGUID() && owner->HasAura(SPELL_DRUID_LIFEBLOOM, caster->GetGUID()) &&
            roll_chance_i(sSpellMgr->GetSpellInfo(SPELL_DRUID_PHOTOSYNTHESIS)->GetEffect(EFFECT_1).BasePoints))
            owner->RemoveAurasDueToSpell(SPELL_DRUID_LIFEBLOOM, caster->GetGUID(), 0, AURA_REMOVE_BY_EXPIRE);

        if (caster->HasAura(SPELL_DRUID_CULTIVATION) && owner->GetHealthPct() <= sSpellMgr->GetSpellInfo(SPELL_DRUID_CULTIVATION)->GetEffect(EFFECT_0).BasePoints)
            caster->CastSpell(owner, SPELL_DRUID_CULTIVATION_HEAL, true);

        if (_originalDamage > 0)
        {
            if (!Druid::CanDraughtOfDeepFocus(caster, owner, GetId()))
            {
                const_cast<AuraEffect*>(aurEff)->ChangeAmount(_originalDamage);
                const_cast<AuraEffect*>(aurEff)->SetDamage(_originalDamage);
                _originalDamage = 0;
            }
        }
        else
        {
            if (Druid::CanDraughtOfDeepFocus(caster, owner, GetId()))
            {
                _originalDamage = aurEff->GetDamage();
                uint32 newDmg = CalculatePct(aurEff->GetDamage(), 140);;
                const_cast<AuraEffect*>(aurEff)->SetDamage(newDmg);
                const_cast<AuraEffect*>(aurEff)->ChangeAmount(newDmg);
            }
        }
    }

    void HandleApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        _originalDamage = 0;
    }

    uint32 _originalDamage = 0;

	void Register() override
	{
        OnEffectApply += AuraEffectApplyFn(aura_dru_rejuvenation::HandleApply, EFFECT_0, SPELL_AURA_PERIODIC_HEAL, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
        AfterEffectRemove += AuraEffectRemoveFn(aura_dru_rejuvenation::AfterRemove, EFFECT_0, SPELL_AURA_PERIODIC_HEAL, AURA_EFFECT_HANDLE_REAL);
        OnEffectPeriodic += AuraEffectPeriodicFn(aura_dru_rejuvenation::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_HEAL);
	}
};

// 774 - Rejuvenation
class spell_dru_rejuvenation : public SpellScript
{
	PrepareSpellScript(spell_dru_rejuvenation);

	bool Validate(SpellInfo const* /*spellInfo*/) override
	{
		return ValidateSpellInfo( { SPELL_DRUID_ABUNDANCE, SPELL_DRUID_ABUNDANCE_BUFF });
	}

	void HandleBeforeHit(SpellMissInfo /*missInfo*/)
	{
		Unit* caster = GetCaster();
		Unit* target = GetHitUnit();

		if (!caster || !target)
			return;

		if (caster->HasAura(SPELL_DRUID_ABUNDANCE))
			if (!target->HasAura(SPELL_DRUID_REJUVENATION, caster->GetGUID()))
				if (Aura* abundanceBuff = caster->GetAura(SPELL_DRUID_ABUNDANCE_BUFF))
					abundanceBuff->ModStackAmount(1);
				else
					caster->AddAura(SPELL_DRUID_ABUNDANCE_BUFF, caster);

        if (caster->HasAura(SPELL_DRUID_GERMINATION))
            if (target->HasAura(SPELL_DRUID_REJUVENATION, caster->GetGUID()) && target->HasAura(SPELL_DRUID_GERMINATION_REJUVENATION, caster->GetGUID()))
            {
                rejuvenationControl = 3;        // Both auras applied.
                if (Aura* aurRejuvenation = target->GetAura(SPELL_DRUID_REJUVENATION, caster->GetGUID()))
                    durationRejuvenation = aurRejuvenation->GetDuration();
                if (Aura* aurRejuvenationGermination = target->GetAura(SPELL_DRUID_GERMINATION_REJUVENATION, caster->GetGUID()))
                    durationRejuventationGermination = aurRejuvenationGermination->GetDuration();
            }
            else if (target->HasAura(SPELL_DRUID_GERMINATION_REJUVENATION, caster->GetGUID()))
                rejuvenationControl = 2;        // Only Germination aura applied.
            else if (target->HasAura(SPELL_DRUID_REJUVENATION, caster->GetGUID()))
            {
                rejuvenationControl = 1;        // Only Rejuvenation aura applied.
                if (Aura* aurRejuvenation = target->GetAura(SPELL_DRUID_REJUVENATION, caster->GetGUID()))
                    durationRejuvenation = aurRejuvenation->GetDuration();
            }
            else
                rejuvenationControl = 0;        // None.
	}

    void HandleAfterHit()
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        // Germination
        if (caster->HasAura(SPELL_DRUID_GERMINATION))
        {
            switch (rejuvenationControl)
            {
                case 1:
                    caster->CastSpell(target, SPELL_DRUID_GERMINATION_REJUVENATION, true);
                    if (Aura* aurRejuvenation = target->GetAura(SPELL_DRUID_REJUVENATION, caster->GetGUID()))
                        aurRejuvenation->SetDuration(durationRejuvenation);
                    break;
                case 3:
                    // Compares duration.
                    if (durationRejuventationGermination < durationRejuvenation)
                    {
                        caster->CastSpell(target, SPELL_DRUID_GERMINATION_REJUVENATION, true);
                        if (Aura* aurRejuvenation = target->GetAura(SPELL_DRUID_REJUVENATION, caster->GetGUID()))
                            aurRejuvenation->SetDuration(durationRejuvenation);
                    }
                    break;
            }
        }

        if (rejuvenationControl == 1 || rejuvenationControl == 3)
            return;

        // If soul of the forest is activated we increase the heal by 200%
        if (AuraEffect* rejuvenation = target->GetAuraEffect(GetSpellInfo()->Id, EFFECT_0, caster->GetGUID()))
        {
            if (caster->HasAura(SPELL_DRUID_SOUL_OF_THE_FOREST_RESTO) || m_HasSoulOfTheForest)
            {
                uint8 SoulofTheForestBonus = sSpellMgr->GetSpellInfo(SPELL_DRUID_SOUL_OF_THE_FOREST_RESTO)->GetEffect(EFFECT_1).BasePoints;
                if (!SoulofTheForestBonus)
                    return;

                rejuvenation->SetDamage(rejuvenation->GetDamage() + CalculatePct(rejuvenation->GetDamage(), SoulofTheForestBonus));
                m_HasSoulOfTheForest = true;
                caster->RemoveAurasDueToSpell(SPELL_DRUID_SOUL_OF_THE_FOREST_RESTO);
            }
        }

        // Revitalize
        if (caster->HasAura(SPELL_DRUID_REVITALIZE))
        {
            caster->CastSpell(target, SPELL_DRUID_REVITALIZE_PROC, true);
            if (Aura* aura = target->GetAura(SPELL_DRUID_REVITALIZE_PROC, caster->GetGUID()))
            {
                aura->SetStackAmount(2);
                aura->SetCharges(2);
            }
        }
    }

    void Register() override
	{
		BeforeHit += BeforeSpellHitFn(spell_dru_rejuvenation::HandleBeforeHit);
        AfterHit += SpellHitFn(spell_dru_rejuvenation::HandleAfterHit);
	}

private:
    bool m_HasSoulOfTheForest = false;
    uint8 rejuvenationControl = 0;
    uint32 durationRejuvenation = 0;
    uint32 durationRejuventationGermination = 0;
};

// 102351 - Cenarion Ward
class aura_dru_cenarion_ward : public AuraScript
{
	PrepareAuraScript(aura_dru_cenarion_ward);

	bool CheckProc(ProcEventInfo& eventInfo)
	{
		if (eventInfo.GetDamageInfo() && (eventInfo.GetDamageInfo()->GetDamageType() != HEAL && eventInfo.GetDamageInfo()->GetDamageType() != NODAMAGE))
			return true;

		return false;
	}

	void HandleProc(ProcEventInfo& eventInfo)
	{
		if (Unit* owner = GetUnitOwner())
			owner->CastSpell(owner, SPELL_DRUID_CENARION_WARD_HEAL, true);
	}

	void Register() override
	{
		DoCheckProc += AuraCheckProcFn(aura_dru_cenarion_ward::CheckProc);
		OnProc += AuraProcFn(aura_dru_cenarion_ward::HandleProc);
	}
};

// 18562 - Swiftmend
class spell_dru_swiftmend : public SpellScript
{
	PrepareSpellScript(spell_dru_swiftmend);

	void HandleAfterCast()
	{
        if (Unit* caster = GetCaster())
        {
            if (caster->HasAura(SPELL_DRUID_SOUL_OF_THE_FOREST_RESTO_TALENT))
                caster->CastSpell(caster, SPELL_DRUID_SOUL_OF_THE_FOREST_RESTO_BUFF);

            if (caster->HasAura(SPELL_DRUID_MASTER_SHAPESHIFTER))
                caster->CastSpell(caster, SPELL_DRUID_MASTER_SHAPESHIFTER_HEAL, true);
        }
	}

    void HandleHeal(SpellEffIndex /*eff*/)
    {
        if (Unit* caster = GetCaster())
        {
            if (auto target = GetHitUnit())
            {
                bool hasVerdantInfusion = caster->HasAura(Druid::eLegendary::VerdantInfusion);

                auto RemoveAuraAndApplyFloralRecycling([&](Aura* aura) -> void
                {
                    auto heal = GetHitHeal();

                    // Floral Recycling
                    if (auto eff = caster->GetAuraEffect(340621, EFFECT_0))
                    {
                        if (eff->ConduitRankEntry)
                        {
                            for (auto eff : aura->GetAuraEffects())
                            {
                                if (eff->GetAuraType() == AuraType::SPELL_AURA_PERIODIC_HEAL)
                                {
                                    auto aurHeal = eff->GetAmount();
                                    aurHeal = CalculatePct(aurHeal, eff->ConduitRankEntry->AuraPointsOverride);
                                    heal += aurHeal;
                                }
                            }
                        }
                    }

                    SetHitHeal(heal);

                    if (!hasVerdantInfusion)
                        aura->Remove();
                });

                /// Wowhead Coments
                /// Also, it preffer to consume in ORDER: Regrowth > Wild Growth > Rejuvenation. as in if it can,
                /// it will ALWAYS pick regrowth, else, it picks wild growth, if nothing else, pick rejuv
                if (auto aur = target->GetAura(Druid::eDruid::Regrowth, caster->GetGUID()))
                    RemoveAuraAndApplyFloralRecycling(aur);
                else if (auto aur = target->GetAura(Druid::eRestoration::WildGrowth, caster->GetGUID()))
                    RemoveAuraAndApplyFloralRecycling(aur);
                else if (auto aur = target->GetAura(Druid::eRestoration::Rejuvenation, caster->GetGUID()))
                    RemoveAuraAndApplyFloralRecycling(aur);
            }
        }
    }

	void Register() override
	{
        OnEffectHitTarget += SpellEffectFn(spell_dru_swiftmend::HandleHeal, EFFECT_0, SPELL_EFFECT_HEAL);
		AfterCast += SpellCastFn(spell_dru_swiftmend::HandleAfterCast);
	}
};

// 114108 - Soul of the Forest
class aura_dru_soul_of_the_forest_resto : public AuraScript
{
	PrepareAuraScript(aura_dru_soul_of_the_forest_resto);

	bool CheckProc(ProcEventInfo& eventInfo)
	{
		return false;
	}

	void Register() override
	{
		DoCheckProc += AuraCheckProcFn(aura_dru_soul_of_the_forest_resto::CheckProc);
	}
};

// 274837 - Feral Frenzy Periodic
//Last Update 8.0.1 Build 28153
class spell_dru_feral_frenzy_periodic : public SpellScript
{
	PrepareSpellScript(spell_dru_feral_frenzy_periodic);

	void HandleTargetHit(SpellEffIndex /*effIndex*/)
	{
        if (Unit* target = GetExplTargetUnit())
            if (auto caster = GetCaster())
                caster->Variables.Set("FeralFrenzyTarget", target->GetGUID());
	}

	void Register() override
	{
		OnEffectHitTarget += SpellEffectFn(spell_dru_feral_frenzy_periodic::HandleTargetHit, EFFECT_0, SPELL_EFFECT_DUMMY);
	}
};

// 274837 - Feral Frenzy
//Last Update 8.0.1 Build 28153
class aura_dru_feral_frenzy : public AuraScript
{
	PrepareAuraScript(aura_dru_feral_frenzy);

	void HandlePeriodic(AuraEffect const* /*auraEff*/)
	{
		Unit* caster = GetCaster();
		if (caster && caster->Variables.Exist("FeralFrenzyTarget"))
		{
			Unit* target = ObjectAccessor::GetUnit(*caster, caster->Variables.GetValue("FeralFrenzyTarget", ObjectGuid::Empty));
            if (target && caster->IsValidAttackTarget(target))            
                caster->CastSpell(target, SPELL_DRUID_FERAL_FRENZY_DAMAGE, true);            
		}
	}

    void OnRemove(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        Unit* caster = GetCaster();
        if (caster && caster->Variables.Exist("FeralFrenzyTarget"))
        {
            Unit* target = ObjectAccessor::GetUnit(*caster, caster->Variables.GetValue("FeralFrenzyTarget", ObjectGuid::Empty));
            if (target && caster->IsValidAttackTarget(target))
            {
                //Right now the feral frenzy are doing another hit because the spell cast 4 time the aura
                //The core don`t have any form to avoid the 4 tick, that is the reason for remove the aura and add again
                //To refresh the duration and the periodic
                target->RemoveAura(SPELL_DRUID_FERAL_FRENZY_DAMAGE);
                caster->AddAura(SPELL_DRUID_FERAL_FRENZY_DAMAGE, target);

                if (AuraEffect* effect = target->GetAuraEffect(SPELL_DRUID_FERAL_FRENZY_DAMAGE, EFFECT_2))
                {
                    effect->SetDonePct(caster->SpellDamagePctDone(target, sSpellMgr->GetSpellInfo(SPELL_DRUID_FERAL_FRENZY_DAMAGE), DOT, effect->GetSpellEffectInfo())); // Calculate done percentage first!
                    effect->SetDamage(caster->SpellDamageBonusDone(target, sSpellMgr->GetSpellInfo(SPELL_DRUID_FERAL_FRENZY_DAMAGE), 0, DOT, effect->GetSpellEffectInfo(), GetStackAmount()) * effect->GetDonePct() * GetSpellInfo()->GetEffect(EFFECT_1).BasePoints);
                }
            }
        }
    }

	void Register() override
	{
		OnEffectPeriodic += AuraEffectPeriodicFn(aura_dru_feral_frenzy::HandlePeriodic, EFFECT_1, SPELL_AURA_PERIODIC_DUMMY);
        OnEffectRemove += AuraEffectRemoveFn(aura_dru_feral_frenzy::OnRemove, EFFECT_1, SPELL_AURA_PERIODIC_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

// 200389 - Cultivation Heal
class aura_dru_cultivation_heal : public AuraScript
{
    PrepareAuraScript(aura_dru_cultivation_heal);

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
        Unit* caster = GetCaster();
        Unit* owner = GetUnitOwner();
        if (!caster || !owner)
            return;

        if (caster->HasAura(SPELL_DRUID_PHOTOSYNTHESIS) && caster->GetGUID() != owner->GetGUID() && owner->HasAura(SPELL_DRUID_LIFEBLOOM, caster->GetGUID()) &&
            roll_chance_i(sSpellMgr->GetSpellInfo(SPELL_DRUID_PHOTOSYNTHESIS)->GetEffect(EFFECT_1).BasePoints))
            owner->RemoveAurasDueToSpell(SPELL_DRUID_LIFEBLOOM, caster->GetGUID(), 0, AURA_REMOVE_BY_EXPIRE);
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(aura_dru_cultivation_heal::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_HEAL);
    }
};

// 207386 - Spring Blossoms Heal
class aura_dru_spring_blossoms_heal : public AuraScript
{
    PrepareAuraScript(aura_dru_spring_blossoms_heal);

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
        Unit* caster = GetCaster();
        Unit* owner = GetUnitOwner();
        if (!caster || !owner)
            return;

        if (caster->HasAura(SPELL_DRUID_PHOTOSYNTHESIS) && caster->GetGUID() != owner->GetGUID() && owner->HasAura(SPELL_DRUID_LIFEBLOOM, caster->GetGUID()) &&
            roll_chance_i(sSpellMgr->GetSpellInfo(SPELL_DRUID_PHOTOSYNTHESIS)->GetEffect(EFFECT_1).BasePoints))
            owner->RemoveAurasDueToSpell(SPELL_DRUID_LIFEBLOOM, caster->GetGUID(), 0, AURA_REMOVE_BY_EXPIRE);
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(aura_dru_spring_blossoms_heal::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_HEAL);
    }
};

// 190984 - Solar Wrath
class spell_dru_solar_wrath : public SpellScript
{
	PrepareSpellScript(spell_dru_solar_wrath);

	void HandlePrepare()
	{
        if (Unit* caster = GetCaster())
            if (caster->HasAura(SPELL_DRUID_SOLAR_EMPOWERMENT))
				caster->Variables.Set<bool>("EMPOWERMENT", true);
			else
				caster->Variables.Remove("EMPOWERMENT");
	}

	void HandleEffectHit(SpellEffIndex /*effIndex*/)
	{
		Unit* caster = GetCaster();
		Unit* target = GetHitUnit();
		if (!caster || !target)
			return;

		if (caster->Variables.Exist("EMPOWERMENT"))
		{
			int32 damage = CalculatePct(GetHitDamage(), sSpellMgr->GetSpellInfo(SPELL_DRUID_SOLAR_EMPOWERMENT)->GetEffect(EFFECT_0).BasePoints);
			caster->CastCustomSpell(SPELL_DRUID_SOLAR_WRATH_AOE, SPELLVALUE_BASE_POINT0, damage, target, true);
		}
	}

	void Register() override
	{
		OnPrepare += SpellOnPrepareFn(spell_dru_solar_wrath::HandlePrepare);
		OnEffectHitTarget += SpellEffectFn(spell_dru_solar_wrath::HandleEffectHit, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
	}
};

// 233754 - Celestial Guardian
class aura_dru_celestial_guardian : public AuraScript
{
    PrepareAuraScript(aura_dru_celestial_guardian);

    void HandleApply(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* caster = GetCaster())
            if (caster->HasAura(SPELL_DRUID_BEAR_FORM))
                caster->CastSpell(caster, SPELL_DRUID_CELESTIAL_GUARIDAN_BUFF, true);
    }

    void HandleRemove(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* caster = GetCaster())
            caster->RemoveAura(SPELL_DRUID_CELESTIAL_GUARIDAN_BUFF);
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(aura_dru_celestial_guardian::HandleApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        OnEffectRemove += AuraEffectRemoveFn(aura_dru_celestial_guardian::HandleRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

//Called by:
// Incarnation: Tree of Life (Shapeshift) - 33891
// Incarnation: King of the Jungle - 102543
// Incarnation: Son of Ursoc - 102558
// Incarnation: Chosen of Elune (Shapeshift) - 102560
// Last Update 8.0.1 Build 28153
class aura_dru_incarnation : public AuraScript
{
    PrepareAuraScript(aura_dru_incarnation);

    void UpdateModel(uint32 spellId)
    {
        Unit* target = GetTarget();
        if (!target)
            return;

        ShapeshiftForm form = target->GetShapeshiftForm();
        if (form == FORM_CAT_FORM || form == FORM_BEAR_FORM || form == FORM_MOONKIN_FORM)
            if (uint32 model = target->GetModelForForm(form, spellId))
                target->SetDisplayId(model);
    }

    void OnApply(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        UpdateModel(GetId());

        Unit* target = GetTarget();
        if (!target)
            return;

        switch (GetId())
        {
        case SPELL_DRUID_INCARNATION_TREE_OF_LIFE:  
            if (!target->HasAura(SPELL_DRUID_TREE_OF_LIFE_DURATION))
                target->CastSpell(target, SPELL_DRUID_TREE_OF_LIFE_DURATION, true);
            break;
        case SPELL_DRUID_INCARNATION_KING_OF_JUNGLE:    // Incarnation: King of the Jungle
            if (!target->HasAura(SPELL_DRUID_CAT_FORM))
                target->CastSpell(target, SPELL_DRUID_CAT_FORM, true);       // activate Cat Form
            break;
        case SPELL_DRUID_INCARNATION_GUARDIAN_OF_URSOC:    // Incarnation: Son of Ursoc
            if (!target->HasAura(SPELL_DRUID_BEAR_FORM))
                target->CastSpell(target, SPELL_DRUID_BEAR_FORM, true);      // activate Bear Form
            break;
        case SPELL_DRUID_CHOSEN_OF_ELUNE:    // Incarnation: Chosen of Elune (Shapeshift)
            if (!target->HasAura(SPELL_DRUID_MOONKIN_FORM))
                target->CastSpell(target, SPELL_DRUID_MOONKIN_FORM, true);     // activate Moonkin Form
            break;
        }
    }

    void OnRemove(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        UpdateModel(GetId());
    }

    void Register() override
    {
        switch (m_scriptSpellId)
        {
        case SPELL_DRUID_INCARNATION_TREE_OF_LIFE:        
            AfterEffectApply += AuraEffectApplyFn(aura_dru_incarnation::OnApply, EFFECT_0, SPELL_AURA_MOD_SHAPESHIFT, AURA_EFFECT_HANDLE_REAL);
            AfterEffectRemove += AuraEffectRemoveFn(aura_dru_incarnation::OnRemove, EFFECT_0, SPELL_AURA_MOD_SHAPESHIFT, AURA_EFFECT_HANDLE_REAL);
            break;
        case SPELL_DRUID_INCARNATION_KING_OF_JUNGLE:
        case SPELL_DRUID_CHOSEN_OF_ELUNE:
        case SPELL_DRUID_INCARNATION_GUARDIAN_OF_URSOC:
            AfterEffectApply += AuraEffectApplyFn(aura_dru_incarnation::OnApply, EFFECT_0, SPELL_AURA_ADD_PCT_MODIFIER, AURA_EFFECT_HANDLE_REAL);
            AfterEffectRemove += AuraEffectRemoveFn(aura_dru_incarnation::OnRemove, EFFECT_0, SPELL_AURA_ADD_PCT_MODIFIER, AURA_EFFECT_HANDLE_REAL);
            break;
        default:
            break;
        }
    }
};

// 117679 - Tree of Life duration
class aura_dru_tree_of_life : public AuraScript
{
    PrepareAuraScript(aura_dru_tree_of_life);

    void HandleRemove(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* caster = GetCaster())
            caster->RemoveAura(SPELL_DRUID_INCARNATION_TREE_OF_LIFE);
    }

    void Register() override
    {
        OnEffectRemove += AuraEffectRemoveFn(aura_dru_tree_of_life::HandleRemove, EFFECT_0, SPELL_AURA_IGNORE_SPELL_COOLDOWN, AURA_EFFECT_HANDLE_REAL);
    }
};

// 233673 - Disentanglement
class aura_dru_distanglement : public AuraScript
{
    PrepareAuraScript(aura_dru_distanglement);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_dru_distanglement::CheckProc);
    }
};

// 203407 - Revitalize Proc
class aura_druid_revitalize_proc : public AuraScript
{
    PrepareAuraScript(aura_druid_revitalize_proc);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();
        Unit* target = GetUnitOwner();
        if (!caster || !target)
            return false;

        if (!caster->HasAura(SPELL_DRUID_REVITALIZE))
        {
            if (Aura* aura = target->GetAura(SPELL_DRUID_REVITALIZE_PROC, caster->GetGUID()))
                target->RemoveAura(SPELL_DRUID_REVITALIZE_PROC, caster->GetGUID());
            return false;
        }

        if (eventInfo.GetDamageInfo() && (eventInfo.GetDamageInfo()->GetDamageType() != HEAL && eventInfo.GetDamageInfo()->GetDamageType() != NODAMAGE) && eventInfo.GetDamageInfo()->GetDamage() > 0
            && (eventInfo.GetHitMask() & PROC_HIT_CRITICAL))
            return true;

        return false;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();
        Unit* target = GetUnitOwner();
        if (!caster || !target)
            return;

        caster->CastSpell(target, SPELL_DRUID_REVITALIZE_HEAL, true);
        if (Aura* aura = target->GetAura(SPELL_DRUID_REVITALIZE_PROC, caster->GetGUID()))
            aura->ModStackAmount(-1);
        if (Aura* aura = target->GetAura(SPELL_DRUID_REJUVENATION, caster->GetGUID()))
            aura->ModDuration(3 * IN_MILLISECONDS);
        if (Aura* aura = target->GetAura(SPELL_DRUID_GERMINATION_REJUVENATION, caster->GetGUID()))
            aura->ModDuration(3 * IN_MILLISECONDS);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_druid_revitalize_proc::CheckProc);
        OnProc += AuraProcFn(aura_druid_revitalize_proc::HandleProc);
    }
};

// 102342 - Ironbark
class spell_dru_ironbark : public SpellScript
{
	PrepareSpellScript(spell_dru_ironbark);

	void HandleHit()
	{
		Unit* caster = GetCaster();
		Unit* target = GetHitUnit();
		if (!caster || !target)
			return;

		if (caster->HasAura(SPELL_DRUID_ENTANGLIN_BARK))
			caster->CastSpell(target, SPELL_DRUID_NATURE_GRASP, true);
	}

	void Register() override
	{
		OnHit += SpellHitFn(spell_dru_ironbark::HandleHit);
	}
};

// 203728 - Thorns
//Last Update 8.0.1 Build 28153
class spell_dru_thorn : public SpellScript
{
	PrepareSpellScript(spell_dru_thorn);

	void HandleHitTarget(SpellEffIndex /*effIndex*/)
	{
		Unit* caster = GetCaster();
		Unit* target = GetHitUnit();
		if (!caster || !target)
			return;

        uint8 pct = GetSpellInfo()->GetEffect(EFFECT_1).BasePoints;
		SetHitDamage(CalculatePct(target->IsPlayer() ? target->GetMaxHealth() : caster->GetMaxHealth(), pct));
	}

	void Register() override
	{
		OnEffectHitTarget += SpellEffectFn(spell_dru_thorn::HandleHitTarget, EFFECT_0, SPELL_EFFECT_DAMAGE_FROM_MAX_HEALTH_PCT);
	}
};

// 202345 - Starlord
class aura_dru_starlord : public AuraScript
{
	PrepareAuraScript(aura_dru_starlord);

	bool CheckProc(ProcEventInfo& eventInfo)
	{
		if (eventInfo.GetSpellInfo() && (eventInfo.GetSpellInfo()->Id == SPELL_DRUID_STARFALL_DAMAGE || eventInfo.GetSpellInfo()->Id == SPELL_DRUID_STARSURGE_BALANCE))
			return true;

		return false;
	}

	void HandleProc(ProcEventInfo& eventInfo)
	{
		if (Unit* caster = GetCaster())
		{
			uint32 duration = 20 * IN_MILLISECONDS;
			if (Aura* aura = caster->GetAura(SPELL_DRUID_STARLORD_HASTE))
				duration = aura->GetDuration();
			caster->CastSpell(caster, SPELL_DRUID_STARLORD_HASTE, true);
			if (Aura* aura = caster->GetAura(SPELL_DRUID_STARLORD_HASTE))
				aura->SetDuration(duration);
		}
	}

	void Register() override
	{
		DoCheckProc += AuraCheckProcFn(aura_dru_starlord::CheckProc);
		OnProc += AuraProcFn(aura_dru_starlord::HandleProc);
	}
};

// 205673 - Savage Momentum
class aura_dru_savage_momentum : public AuraScript
{
	PrepareAuraScript(aura_dru_savage_momentum);

	bool CheckProc(ProcEventInfo& eventInfo)
	{
		if (Unit* caster = GetCaster())
			if (eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == SPELL_DRUID_SKULL_BASH && caster->Variables.Exist("INTERRUPT") && caster->Variables.GetValue<bool>("INTERRUPT"))
				return true;

		return false;
	}

	void HandleProc(ProcEventInfo& eventInfo)
	{
		Unit* caster = GetCaster();
		Unit* target = eventInfo.GetActionTarget();
		if (!caster || !target)
			return;

		caster->GetSpellHistory()->ResetCooldown(SPELL_DRUID_TIGERS_FURY, true);
	}

	void Register() override
	{
		DoCheckProc += AuraCheckProcFn(aura_dru_savage_momentum::CheckProc);
		OnProc += AuraProcFn(aura_dru_savage_momentum::HandleProc);
	}
};

// 209740 - Moonkin Aura
class aura_dru_moonkin_aura : public AuraScript
{
	PrepareAuraScript(aura_dru_moonkin_aura);

	bool CheckProc(ProcEventInfo& eventInfo)
	{
		if (eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == SPELL_DRUID_STARSURGE_BALANCE)
			return true;

		return false;
	}

	void Register() override
	{
		DoCheckProc += AuraCheckProcFn(aura_dru_moonkin_aura::CheckProc);
	}
};

// 209746 - Moonkin Aura Buff
class spell_dru_moonkin_aura_buff : public SpellScript
{
	PrepareSpellScript(spell_dru_moonkin_aura_buff);

	void FilterTargets(std::list<WorldObject*>& targets)
	{
		if (Unit* caster = GetCaster())
			targets.remove_if([caster](WorldObject* object)
			{
				if (!object->ToPlayer())
					return true;

				if (!caster->ToPlayer()->IsInSameGroupWith(object->ToPlayer()) && !caster->ToPlayer()->IsInSameRaidWith(object->ToPlayer()))
					return true;

				return false;
			});
	}

	void Register() override
	{
		OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_dru_moonkin_aura_buff::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ALLY);
	}
};

// 102359 - Mass Entanglement
class aura_dru_mass_entanglement : public AuraScript
{
	PrepareAuraScript(aura_dru_mass_entanglement);

	bool CheckProc(ProcEventInfo& eventInfo)
	{
		if (!eventInfo.GetDamageInfo())
			return false;

		Aura* aura = GetAura();
		if (Unit* caster = GetCaster())
		{
			float chance = caster->HasAura(SPELL_DRUID_DEEP_ROOTS) ? 12.5f : 50;
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
		Unit* owner = GetUnitOwner();
		if (!caster || !owner)
			return;

		if (GetTargetApplication()->GetRemoveMode() != AURA_REMOVE_BY_DEATH && caster->HasAura(SPELL_DRUID_PRICKLING_TORNS))
			caster->CastSpell(owner, SPELL_DRUID_PRICKLING_TORNS_DAMAGE, true);
	}

	void Register() override
	{
		DoCheckProc += AuraCheckProcFn(aura_dru_mass_entanglement::CheckProc);
		OnProc += AuraProcFn(aura_dru_mass_entanglement::HandleProc);
		OnEffectRemove += AuraEffectRemoveFn(aura_dru_mass_entanglement::HandleRemove, EFFECT_0, SPELL_AURA_MOD_ROOT_2, AURA_EFFECT_HANDLE_REAL);
	}
};

// 202770 - Fury of Elune
class spell_dru_fury_of_elune : public SpellScript
{
	PrepareSpellScript(spell_dru_fury_of_elune);

	void HandleEffectHit(SpellEffIndex /*effIndex*/)
	{
		Unit* caster = GetCaster();
		Unit* target = GetHitUnit();
		if (!caster || !target)
			return;
	}

	void Register() override
	{
		OnEffectHitTarget += SpellEffectFn(spell_dru_fury_of_elune::HandleEffectHit, EFFECT_0, SPELL_EFFECT_DUMMY);
	}
};

// 203974 - Earthwarden
class aura_dru_earthwarden : public AuraScript
{
	PrepareAuraScript(aura_dru_earthwarden);

	bool CheckProc(ProcEventInfo& eventInfo)
	{
		return false;
	}

	void Register() override
	{
		DoCheckProc += AuraCheckProcFn(aura_dru_earthwarden::CheckProc);
	}
};

// 203975 - Earthwarden Absorb
class aura_dru_earthwarden_absorb : public AuraScript
{
	PrepareAuraScript(aura_dru_earthwarden_absorb);

	void CalculateAmount(AuraEffect const* /*auraEffect*/, int32& amount, bool& /*canBeRecalculated*/)
	{
		amount = -1;
	}

	void HandleAbsorb(AuraEffect* /*aurEff*/, DamageInfo& dmgInfo, uint32& absorbAmount)
	{
		if (dmgInfo.GetDamage() <= 0 || (dmgInfo.GetAttackType() != BASE_ATTACK && dmgInfo.GetAttackType() != OFF_ATTACK))
			absorbAmount = 0;
		else
			absorbAmount = CalculatePct(dmgInfo.GetDamage(), sSpellMgr->GetSpellInfo(SPELL_DRUID_EARTHWARDEN)->GetEffect(EFFECT_0).BasePoints);
	}

	void Register() override
	{
		DoEffectCalcAmount += AuraEffectCalcAmountFn(aura_dru_earthwarden_absorb::CalculateAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
		OnEffectAbsorb += AuraEffectAbsorbFn(aura_dru_earthwarden_absorb::HandleAbsorb, EFFECT_0);
	}
};

// 203964 - Galactic Guardian
class aura_dru_galatic_guardian : public AuraScript
{
	PrepareAuraScript(aura_dru_galatic_guardian);

	void HandleProc(ProcEventInfo& eventInfo)
	{
		Unit* caster = GetCaster();
		Unit* target = eventInfo.GetActionTarget();
		if (!caster || !target)
			return;

		caster->CastSpell(target, SPELL_DRUID_MOONFIRE, true);
		caster->CastSpell(target, SPELL_DRUID_GALATIC_GUARIDAN_MOONFIRE, true);
	}

	void Register() override
	{
		OnProc += AuraProcFn(aura_dru_galatic_guardian::HandleProc);
	}
};

// 213708 - Galactic Guardian Moonfire
class aura_dru_galatic_guardian_moonfire : public AuraScript
{
	PrepareAuraScript(aura_dru_galatic_guardian_moonfire);

	bool CheckProc(ProcEventInfo& eventInfo)
	{
		if (eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == SPELL_DRUID_MOONFIRE)
			return true;

		return false;
	}

	void HandleProc(ProcEventInfo& eventInfo)
	{
		if (Unit* caster = GetCaster())
			caster->CastSpell(caster, SPELL_DRUID_GALATIC_GUARDIAN_ENERGIZE, true);
	}

	void Register() override
	{
		DoCheckProc += AuraCheckProcFn(aura_dru_galatic_guardian_moonfire::CheckProc);
		OnProc += AuraProcFn(aura_dru_galatic_guardian_moonfire::HandleProc);
	}
};

// 204069 - Lunar Beam Effect
class spell_dru_lunar_beam_effect : public SpellScript
{
    PrepareSpellScript(spell_dru_lunar_beam_effect);

    void HandleEffectHit(SpellEffIndex /*effIndex*/)
    {
        if (Unit* caster = GetCaster())
            if (!caster->Variables.Exist("INSIDE_BEAM") || !caster->Variables.GetValue<bool>("INSIDE_BEAM"))
                SetHitHeal(0);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_dru_lunar_beam_effect::HandleEffectHit, EFFECT_0, SPELL_EFFECT_HEAL);
    }
};

// 80313 - Pulverize
class spell_dru_pulverize : public SpellScript
{
    PrepareSpellScript(spell_dru_pulverize);

    void HandleHit()
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        if (Aura* aura = target->GetAura(SPELL_DRUID_THRASH_BEAR_PERIODIC_DAMAGE, caster->GetGUID()))
            aura->ModStackAmount(-2);

        caster->CastSpell(caster, SPELL_DRUID_PULVERIZE_BUFF, true);
    }

    void Register() override
    {
        OnHit += SpellHitFn(spell_dru_pulverize::HandleHit);
    }
};

// 202110 - Sharpened Claws
class aura_dru_sharpened_claws : public AuraScript
{
    PrepareAuraScript(aura_dru_sharpened_claws);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == SPELL_DRUID_MAUL)
            return true;

        return false;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_dru_sharpened_claws::CheckProc);
    }
};

// 213947 - Clan Defender Proc
class aura_dru_clan_defender_proc : public AuraScript
{
    PrepareAuraScript(aura_dru_clan_defender_proc);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetDamageInfo() && eventInfo.GetDamageInfo()->GetDamage() > 0 &&
            (eventInfo.GetDamageInfo()->GetDamageType() != HEAL && eventInfo.GetDamageInfo()->GetDamageType() != NODAMAGE) && (eventInfo.GetHitMask() & PROC_HIT_CRITICAL))
            return true;

        return false;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (Unit* caster = GetCaster())
            caster->AddAura(SPELL_DRUID_GORE_AURA);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_dru_clan_defender_proc::CheckProc);
        OnProc += AuraProcFn(aura_dru_clan_defender_proc::HandleProc);
    }
};

// 164812 - Moonfire Damage
class spell_dru_moonfire_damage : public SpellScript
{
	PrepareSpellScript(spell_dru_moonfire_damage);

	void HandleEffectHit(SpellMissInfo missInfo)
	{
		Unit* caster = GetCaster();
		Unit* target = GetHitUnit();
		if (!caster || !target)
			return;

		if (caster->HasAura(SPELL_DRUID_CRESCENT_BURN) && target->HasAura(SPELL_DRUID_MOONFIRE_DAMAGE, caster->GetGUID()))
			incrementDamage = true;
	}

	void HandleEffectHitTarget(SpellEffIndex /*effIndex*/)
	{
        if (incrementDamage)
			SetHitDamage(GetHitDamage() + CalculatePct(GetHitDamage(), sSpellMgr->GetSpellInfo(SPELL_DRUID_CRESCENT_BURN)->GetEffect(EFFECT_0).BasePoints));
	}

	void Register() override
	{
		BeforeHit += BeforeSpellHitFn(spell_dru_moonfire_damage::HandleEffectHit);
		OnEffectHitTarget += SpellEffectFn(spell_dru_moonfire_damage::HandleEffectHitTarget, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
	}

private:
	bool incrementDamage = false;
};

// 191034 - Starfall
class spell_dru_starfall : public SpellScript
{
	PrepareSpellScript(spell_dru_starfall);

	void HandlePrepare()
	{
		if (Unit* caster = GetCaster())
            if (caster->HasAura(SPELL_DRUID_CELESTIAL_DOWNPOUR))
			    if (AreaTrigger* at = caster->GetAreaTrigger(SPELL_DRUID_STARFALL))
				    at->SetDuration(0);
	}

	void Register() override
	{
		OnPrepare += SpellOnPrepareFn(spell_dru_starfall::HandlePrepare);
	}
};

// 202425 - Warrior of Elune
class spell_dru_warrior_of_elune : public SpellScript
{
	PrepareSpellScript(spell_dru_warrior_of_elune);

	void HandleHit()
	{
		if (Unit* caster = GetCaster())
			if (Aura* aura = caster->GetAura(SPELL_DRUID_WARRIOR_OF_ELUNE))
				aura->SetStackAmount(3);
	}

	void Register() override
	{
		OnHit += SpellHitFn(spell_dru_warrior_of_elune::HandleHit);
	}
};

// 202425 - Warrior of Elune
class aura_dru_warrior_of_elune : public AuraScript
{
	PrepareAuraScript(aura_dru_warrior_of_elune);

	bool CheckProc(ProcEventInfo& eventInfo)
	{
		if (Unit* caster = GetCaster())
			if (eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == SPELL_DRUID_LUNAR_STRIKE_BALANCE && caster->Variables.Exist("LunarStrikeMain") && eventInfo.GetActionTarget() && eventInfo.GetActionTarget()->GetGUID() == caster->Variables.GetValue("LunarStrikeMain", ObjectGuid::Empty))
				return true;

		return false;
	}

	void HandleProc(ProcEventInfo& eventInfo)
	{
		PreventDefaultAction();
		GetAura()->ModStackAmount(-1);
	}

	void Register() override
	{
		DoCheckProc += AuraCheckProcFn(aura_dru_warrior_of_elune::CheckProc);
		OnProc += AuraProcFn(aura_dru_warrior_of_elune::HandleProc);
	}
};

// 252216 - Tiger Dash
class spell_dru_tiger_dash : public SpellScript
{
	PrepareSpellScript(spell_dru_tiger_dash);

	void HandleHit()
	{
		if (Unit* caster = GetCaster())
			caster->CastSpell(caster, SPELL_DRUID_CAT_FORM, true);
	}

	void Register() override
	{
		OnHit += SpellHitFn(spell_dru_tiger_dash::HandleHit);
	}
};

// 252216 - Tiger Dash
class aura_dru_tiger_dash : public AuraScript
{
    PrepareAuraScript(aura_dru_tiger_dash);

    void CalculateAmount(AuraEffect const* /*aurEff*/, int32& amount, bool& canBeRecalculated)
    {
        canBeRecalculated = true;
        if (tick > 0)
            amount -= tick * GetAura()->GetEffect(EFFECT_1)->GetAmount();
    }

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
        tick++;
        GetAura()->GetEffect(EFFECT_0)->RecalculateAmount();
    }

    void Register() override
    {
        DoEffectCalcAmount += AuraEffectCalcAmountFn(aura_dru_tiger_dash::CalculateAmount, EFFECT_0, SPELL_AURA_MOD_INCREASE_SPEED);
        OnEffectPeriodic += AuraEffectPeriodicFn(aura_dru_tiger_dash::HandlePeriodic, EFFECT_1, SPELL_AURA_PERIODIC_DUMMY);
    }

private:
    uint8 tick = 0;
};

// 137013 - Balance Druid
class aura_dru_balance_druid : public AuraScript
{
    PrepareAuraScript(aura_dru_balance_druid);

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* caster = GetCaster())
        {
            caster->RemoveAura(SPELL_DRUID_LUNAR_EMPOWERMENT);
            caster->RemoveAura(SPELL_DRUID_SOLAR_EMPOWERMENT);
        }
    }

    void Register() override
    {
        OnEffectRemove += AuraEffectRemoveFn(aura_dru_balance_druid::HandleRemove, EFFECT_0, SPELL_AURA_ADD_PCT_MODIFIER, AURA_EFFECT_HANDLE_REAL);
    }
};

// 155777 - Rejuvenation (Germination)
class spell_dru_rejuvenation_germination : public SpellScript
{
    PrepareSpellScript(spell_dru_rejuvenation_germination);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_DRUID_ABUNDANCE, SPELL_DRUID_ABUNDANCE_BUFF });
    }

    void HandleBeforeHit(SpellMissInfo /*missInfo*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();

        if (!caster || !target)
            return;

        if (caster->HasAura(SPELL_DRUID_ABUNDANCE))
            if (!target->HasAura(SPELL_DRUID_GERMINATION_REJUVENATION, caster->GetGUID()))
                if (Aura* abundanceBuff = caster->GetAura(SPELL_DRUID_ABUNDANCE_BUFF))
                    abundanceBuff->ModStackAmount(1);
                else
                    caster->AddAura(SPELL_DRUID_ABUNDANCE_BUFF, caster);
    }

    void HandleAfterHit()
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        // If soul of the forest is activated we increase the heal by 200%
        if (AuraEffect* rejuvenation = target->GetAuraEffect(GetSpellInfo()->Id, EFFECT_0, caster->GetGUID()))
        {
            if (caster->HasAura(SPELL_DRUID_SOUL_OF_THE_FOREST_RESTO) || m_HasSoulOfTheForest)
            {
                uint8 SoulofTheForestBonus = sSpellMgr->GetSpellInfo(SPELL_DRUID_SOUL_OF_THE_FOREST_RESTO)->GetEffect(EFFECT_1).BasePoints;
                if (!SoulofTheForestBonus)
                    return;

                rejuvenation->SetDamage(rejuvenation->GetDamage() + CalculatePct(rejuvenation->GetDamage(), SoulofTheForestBonus));
                m_HasSoulOfTheForest = true;
                caster->RemoveAurasDueToSpell(SPELL_DRUID_SOUL_OF_THE_FOREST_RESTO);
            }
        }

        // Revitalize
        if (caster->HasAura(SPELL_DRUID_REVITALIZE))
        {
            caster->CastSpell(target, SPELL_DRUID_REVITALIZE_PROC, true);
            if (Aura* aura = target->GetAura(SPELL_DRUID_REVITALIZE_PROC, caster->GetGUID()))
                aura->SetStackAmount(2);
        }
    }

    void Register() override
    {
        BeforeHit += BeforeSpellHitFn(spell_dru_rejuvenation_germination::HandleBeforeHit);
        AfterHit += SpellHitFn(spell_dru_rejuvenation_germination::HandleAfterHit);
    }

private:
    bool m_HasSoulOfTheForest = false;
};

// 155777 - Rejuvenation (Germination)
class aura_dru_rejuvenation_germination : public AuraScript
{
    PrepareAuraScript(aura_dru_rejuvenation_germination);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_DRUID_ABUNDANCE, SPELL_DRUID_ABUNDANCE_BUFF, SPELL_DRUID_PHOTOSYNTHESIS, SPELL_DRUID_LIFEBLOOM, SPELL_DRUID_CULTIVATION });
    }

    void AfterRemove(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* caster = GetCaster())
            if (caster->HasAura(SPELL_DRUID_ABUNDANCE))
                if (Aura* abundanceBuff = caster->GetAura(SPELL_DRUID_ABUNDANCE_BUFF))
                    abundanceBuff->ModStackAmount(-1);
    }

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
        Unit* caster = GetCaster();
        Unit* owner = GetUnitOwner();
        if (!caster || !owner)
            return;

        if (caster->HasAura(SPELL_DRUID_PHOTOSYNTHESIS) && caster->GetGUID() != owner->GetGUID() && owner->HasAura(SPELL_DRUID_LIFEBLOOM, caster->GetGUID()) &&
            roll_chance_i(sSpellMgr->GetSpellInfo(SPELL_DRUID_PHOTOSYNTHESIS)->GetEffect(EFFECT_1).BasePoints))
            owner->RemoveAurasDueToSpell(SPELL_DRUID_LIFEBLOOM, caster->GetGUID(), 0, AURA_REMOVE_BY_EXPIRE);

        if (caster->HasAura(SPELL_DRUID_CULTIVATION) && owner->GetHealthPct() <= sSpellMgr->GetSpellInfo(SPELL_DRUID_CULTIVATION)->GetEffect(EFFECT_0).BasePoints)
            caster->CastSpell(owner, SPELL_DRUID_CULTIVATION_HEAL, true);
    }

    void Register() override
    {
        AfterEffectRemove += AuraEffectRemoveFn(aura_dru_rejuvenation_germination::AfterRemove, EFFECT_0, SPELL_AURA_PERIODIC_HEAL, AURA_EFFECT_HANDLE_REAL);
        OnEffectPeriodic += AuraEffectPeriodicFn(aura_dru_rejuvenation_germination::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_HEAL);
    }
};

// 203651 - Overgrowth
//Last Update 8.0.1 Build 28153 
class spell_dru_overgrowth : public SpellScript
{
    PrepareSpellScript(spell_dru_overgrowth);

    void HandleHit()
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        // Applies all heals.
        caster->CastSpell(target, SPELL_DRUID_LIFEBLOOM, true);
        caster->CastSpell(target, SPELL_DRUID_REJUVENATION, true);
        caster->CastSpell(target, SPELL_DRUID_WILD_GROWTH, true);
        caster->Variables.Set<bool>("OVERGROWTH", true);
        caster->CastSpell(target, SPELL_DRUID_REGROWTH, true);
        caster->Variables.Remove("OVERGROWTH");
    }

    void Register() override
    {
        OnHit += SpellHitFn(spell_dru_overgrowth::HandleHit);
    }
};

// 93622 - Gore Aura
class aura_dru_gore_aura : public AuraScript
{
    PrepareAuraScript(aura_dru_gore_aura);

    bool HandleCheckProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == SPELL_DRUID_MANGLE)
            return true;

        return false;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_dru_gore_aura::HandleCheckProc);
    }
};

//Rend and Tear - 204053
//Last Update 8.0.1 Build 28153
class aura_dru_rend_and_tear : public AuraScript
{
    PrepareAuraScript(aura_dru_rend_and_tear);

    void CalculateAmount(AuraEffect const* aurEff, int32& amount, bool & /*canBeRecalculated*/)
    {
        amount = -1;
    }

    void Absorb(AuraEffect* /*AuraEffect**/, DamageInfo& dmgInfo, uint32& absorbAmount)
    {
        absorbAmount = 0;
        Unit* caster = GetCaster();
        if (!caster || caster->GetShapeshiftForm() != FORM_BEAR_FORM)
            return;

        if (Unit* target = dmgInfo.GetAttacker())
        {
            if (Aura* aura = target->GetAura(SPELL_DRUID_THRASH_BEAR_PERIODIC_DAMAGE))
                absorbAmount = CalculatePct(dmgInfo.GetDamage(), GetEffectInfo(EFFECT_1).BasePoints * aura->GetStackAmount());
        }
    }

    void Register() override
    {
        OnEffectAbsorb += AuraEffectAbsorbFn(aura_dru_rend_and_tear::Absorb, EFFECT_0);
        DoEffectCalcAmount += AuraEffectCalcAmountFn(aura_dru_rend_and_tear::CalculateAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
    }
};

//29166 Innervate
//Last Update 8.0.1 Build 28153
class aura_dru_innervate : public AuraScript
{
    PrepareAuraScript(aura_dru_innervate);

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Unit* caster = GetCaster();
        if (!caster)
            return;

        if (AuraEffect* aurEff = caster->GetAuraEffect(SPELL_DRUID_LIVELY_SPIRIT_POWER, EFFECT_0))
        {
            if (caster->Variables.Exist("LIVELY_SPIRIT"))
            {
                uint32 stack = caster->Variables.GetValue<uint32>("LIVELY_SPIRIT");
                CastSpellExtraArgs values(true);
                values.SetTriggeringAura(aurEff);
                values.AddSpellBP0(aurEff->GetAmount());
                caster->CastSpell(caster, SPELL_DRUID_LIVELY_SPIRIT_BUFF, values);
                caster->Variables.Remove("LIVELY_SPIRIT");
            }             
        }
    }

    void Register() override
    {
        OnEffectRemove += AuraEffectRemoveFn(aura_dru_innervate::HandleRemove, EFFECT_0, SPELL_AURA_MOD_POWER_COST_SCHOOL_PCT, AURA_EFFECT_HANDLE_REAL);
    }
};

// 157982 - Tranquility Heal
// Last Update 8.0.1 Build 28153
class spell_dru_tranquility_heal : public SpellScript
{
    PrepareSpellScript(spell_dru_tranquility_heal);

    void HandleHitTarget(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        if (!target->IsInRaidWith(caster))
            SetHitHeal(GetHitHeal() * 2);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_dru_tranquility_heal::HandleHitTarget, EFFECT_1, SPELL_EFFECT_HEAL);
    }
};

class aura_dru_tranquility_heal : public AuraScript
{
    PrepareAuraScript(aura_dru_tranquility_heal);

    void CalculateAmount(AuraEffect const* /*aurEff*/, int32& amount, bool& canBeRecalculated)
    {
        canBeRecalculated = false;
        Unit* caster = GetCaster();
        Unit* target = GetTarget();
        if (!caster || !target)
            return;

        if (!target->IsInRaidWith(caster))
            amount *= 2;
    }

    void Register() override
    {
        DoEffectCalcAmount += AuraEffectCalcAmountFn(aura_dru_tranquility_heal::CalculateAmount, EFFECT_0, SPELL_AURA_PERIODIC_HEAL);
    }
};

// 323764
class spell_dru_convoke : public AuraScript
{
    PrepareAuraScript(spell_dru_convoke);

    void HandleConvoke(AuraEffect const* /*aurEff*/)
    {
        if (Unit* caster = GetCaster())
        {
            std::vector<uint32> SpellsToCast;

            SpellsToCast.push_back(774);
            SpellsToCast.push_back(8936);
            SpellsToCast.push_back(8921);
            SpellsToCast.push_back(5176);

            switch (caster->GetShapeshiftForm())
            {
                case ShapeshiftForm::FORM_BEAR_FORM:
                    SpellsToCast.push_back(33917);
                    SpellsToCast.push_back(192081);
                    SpellsToCast.push_back(106832);
                    SpellsToCast.push_back(80313);
                    break;
                case ShapeshiftForm::FORM_CAT_FORM:
                    SpellsToCast.push_back(22568);
                    SpellsToCast.push_back(1822);
                    SpellsToCast.push_back(5221);
                    SpellsToCast.push_back(5217);
                    break;
                case ShapeshiftForm::FORM_MOONKIN_FORM:
                    SpellsToCast.push_back(78674);
                    SpellsToCast.push_back(191034);
                    break;
                default: // heal
                    if (caster->ToPlayer() && caster->ToPlayer()->GetSpecializationId() == TALENT_SPEC_DRUID_RESTORATION)
                    {
                        SpellsToCast.push_back(18562);
                        SpellsToCast.push_back(48438);
                        SpellsToCast.push_back(1917721);
                    }
                    break;
            }

            auto target = ObjectAccessor::GetUnit(*caster, caster->GetTarget());
            if (!target)
                target = caster;
            if (auto spell = Trinity::Containers::SelectRandomContainerElement(SpellsToCast))
                caster->CastSpell(target, spell, true);
        }
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_dru_convoke::HandleConvoke, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

/// ID: 363498 Sickle of the Lion
class spell_sickle_of_the_lion : public AuraScript
{
    PrepareAuraScript(spell_sickle_of_the_lion);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && (eventInfo.GetSpellInfo()->Id == 106951 || eventInfo.GetSpellInfo()->Id == 102543);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_sickle_of_the_lion::CheckProc);
    }
};

/// ID: 363496 Architect's Aligner
class spell_architects_aligner : public AuraScript
{
    PrepareAuraScript(spell_architects_aligner);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && (eventInfo.GetSpellInfo()->Id == 50334 || eventInfo.GetSpellInfo()->Id == 102558);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_architects_aligner::CheckProc);
    }
};

void AddSC_druid_spell_scripts()
{
    // Spells Scripts
    RegisterSpellScript(spell_dru_efflorescence);
    RegisterSpellScript(spell_dru_efflorescence_aura);
    RegisterSpellScript(spell_dru_efflorescence_heal);
    new spell_dru_primal_fury();
	RegisterSpellAndAuraScriptPair(spell_dru_lifebloom, aura_dru_lifebloom);
    new spell_dru_berserk();
    new spell_dru_sunfire();
    RegisterSpellScript(spell_dru_ferocious_bite);
    new spell_dru_dash();
    RegisterSpellAndAuraScriptPair(spell_dru_savage_roar, aura_dru_savage_roar);
    new spell_dru_survival_instincts();
    new spell_dru_swift_flight_passive();
    RegisterSpellAndAuraScriptPair(spell_dru_wild_growth, aura_dru_wild_growth);
	RegisterSpellScript(spell_dru_moonfire);
    new spell_dru_omen_of_clarity();
    new spell_dru_cat_form();
    new spell_dru_bear_form();
    new spell_dru_skull_bash();
    new spell_dru_stampeding_roar();
    new spell_dru_activate_cat_form();
    new spell_dru_killer_instinct();
    new spell_dru_infected_wound();
    RegisterSpellScript(aura_dru_ysera_gift);
    RegisterSpellScript(spell_dru_rake);
    RegisterSpellScript(spell_dru_maim);
    RegisterSpellAndAuraScriptPair(spell_dru_rip, aura_dru_rip);
    new spell_dru_travel_form_dummy();
    new spell_dru_travel_form();
    RegisterSpellScript(aura_dru_charm_woodland_creature);
    RegisterSpellScript(spell_dru_swipe);
    RegisterSpellScript(spell_dru_brutal_slash);
    RegisterSpellAndAuraScriptPair(spell_dru_thrash_cat,aura_dru_thrash);
    RegisterSpellScript(spell_dru_shred);
    RegisterSpellScript(spell_dru_thrash_bear);
    RegisterSpellScript(aura_dru_thrash_bear);
    RegisterSpellScript(spell_dru_blessing_of_the_ancients);
    RegisterSpellScript(aura_dru_gore);
    RegisterSpellScript(aura_dru_solar_empowerment);
    RegisterSpellScript(aura_dru_lunar_empowerment);
    RegisterSpellScript(aura_dru_astral_form);
    RegisterSpellScript(aura_dru_frenzied_regeneration);
    RegisterSpellScript(aura_dru_empowerments);
    RegisterSpellScript(spell_dru_lunar_strike_balance);
    RegisterSpellScript(aura_dru_predatory_swiftness);
    RegisterSpellAndAuraScriptPair(spell_dru_predatory_swiftness_aura, aura_dru_entangling_roots);
    RegisterSpellScript(aura_dru_clearcasting);
	RegisterSpellScript(aura_dru_rake);
	RegisterSpellScript(aura_dru_twin_moons);
	RegisterSpellScript(aura_dru_guardian_of_elune);
	RegisterSpellScript(aura_dru_guardian_of_elune_aura);
	RegisterSpellScript(aura_dru_sunfire_damage);
	RegisterSpellAndAuraScriptPair(spell_dru_moonfire_damage, aura_dru_moonfire_damage);
	RegisterSpellScript(aura_dru_brambles);
	RegisterSpellScript(aura_dru_barkskin);
	RegisterSpellScript(spell_dru_moons);
	RegisterSpellScript(aura_dru_nature_balance);
	RegisterSpellAndAuraScriptPair(spell_dru_feral_frenzy, aura_dru_feral_frenzy_damage);
	RegisterSpellScript(spell_dru_enraged_maim);
	RegisterSpellScript(spell_dru_rip_and_tear);
	RegisterSpellAndAuraScriptPair(spell_dru_rejuvenation, aura_dru_rejuvenation);
	RegisterSpellScript(aura_dru_cenarion_ward);
	RegisterSpellScript(spell_dru_swiftmend);
	RegisterSpellScript(aura_dru_soul_of_the_forest_resto);
	RegisterSpellAndAuraScriptPair(spell_dru_feral_frenzy_periodic, aura_dru_feral_frenzy);
    RegisterSpellAndAuraScriptPair(spell_dru_regrowth, aura_dru_regrowth);
    RegisterSpellScript(aura_dru_cultivation_heal);
    RegisterSpellScript(aura_dru_spring_blossoms_heal);
	RegisterSpellScript(spell_dru_solar_wrath);
    RegisterSpellScript(aura_dru_celestial_guardian);
    RegisterSpellScript(aura_dru_tree_of_life);
    RegisterSpellScript(aura_dru_distanglement);
    RegisterSpellScript(aura_druid_revitalize_proc);
	RegisterSpellScript(spell_dru_ironbark);
	RegisterSpellScript(spell_dru_thorn);
	RegisterSpellScript(aura_dru_starlord);
	RegisterSpellScript(aura_dru_savage_momentum);
	RegisterSpellScript(aura_dru_moonkin_aura);
	RegisterSpellScript(spell_dru_moonkin_aura_buff);
	RegisterSpellScript(aura_dru_mass_entanglement);
	RegisterSpellScript(spell_dru_fury_of_elune);
	RegisterSpellScript(aura_dru_earthwarden);
	RegisterSpellScript(aura_dru_earthwarden_absorb);
	RegisterSpellScript(aura_dru_galatic_guardian);
	RegisterSpellScript(aura_dru_galatic_guardian_moonfire);
    RegisterSpellScript(spell_dru_lunar_beam_effect);
    RegisterSpellScript(spell_dru_pulverize);
    RegisterSpellScript(aura_dru_sharpened_claws);
    RegisterSpellScript(aura_dru_clan_defender_proc);
	RegisterSpellScript(spell_dru_starfall);
	RegisterSpellAndAuraScriptPair(spell_dru_warrior_of_elune, aura_dru_warrior_of_elune);
    RegisterSpellAndAuraScriptPair(spell_dru_tiger_dash, aura_dru_tiger_dash);
    RegisterSpellScript(aura_dru_natures_balance_ticker);
    RegisterSpellScript(aura_dru_balance_druid);
    RegisterSpellAndAuraScriptPair(spell_dru_rejuvenation_germination, aura_dru_rejuvenation_germination);
    RegisterSpellScript(spell_dru_overgrowth);
    RegisterSpellScript(aura_dru_gore_aura);
    RegisterSpellScript(aura_dru_incarnation);
    RegisterSpellScript(aura_dru_rend_and_tear);
    RegisterSpellScript(aura_dru_innervate);
    RegisterSpellAndAuraScriptPair(spell_dru_tranquility_heal, aura_dru_tranquility_heal);
    RegisterSpellScript(spell_dru_convoke);
    RegisterSpellScript(spell_sickle_of_the_lion);
    RegisterSpellScript(spell_architects_aligner);

	// Affinity
    RegisterSpellScript(aura_dru_guaridan_affinity_balance_resto);
    RegisterSpellScript(aura_dru_guaridan_affinity_feral);
    RegisterSpellScript(aura_dru_resto_affinity_all);
    RegisterSpellScript(aura_dru_balance_affinity_resto);
    RegisterSpellScript(aura_dru_balance_affinity_feral_guardian);
    RegisterSpellScript(aura_dru_feral_affinity_guardian);
    RegisterSpellScript(aura_dru_feral_affinity_balance);
    RegisterSpellScript(aura_dru_feral_affinity_resto);

    // AreaTrigger Scripts
	RegisterAreaTriggerAI(at_dru_solar_beam);
    RegisterAreaTriggerAI(at_dru_starfall);
    RegisterAreaTriggerAI(at_dru_ursols_vortex);
	RegisterAreaTriggerAI(at_druid_den_mother);
	RegisterAreaTriggerAI(at_dru_fury_of_elune);
    RegisterAreaTriggerAI(at_dru_lunar_beam);
    RegisterAreaTriggerAI(at_dru_clan_defender);

    // NPC Scripts
    RegisterCreatureAI(npc_dru_efflorescence);

	// Playerscript
	new druid_playerscript();

    // Deprecated
   //new spell_dru_living_seed(); Deprecated Spell
}
