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

/*
 * Scripts for spells with SPELLFAMILY_DEMON_HUNTER and SPELLFAMILY_GENERIC spells used by demon hunter players.
 * Ordered alphabetically using scriptname.
 * Scriptnames of files in this file should be prefixed with "spell_dh_".
 */

#include <chrono>
#include "AreaTrigger.h"
#include "AreaTriggerAI.h"
#include "CellImpl.h"
#include "GridNotifiers.h"
#include "GridNotifiersImpl.h"
#include "ObjectAccessor.h"
#include "PathGenerator.h"
#include "PhasingHandler.h"
#include "Player.h"
#include "ScriptedGossip.h"
#include "ScriptMgr.h"
#include "SpellScript.h"
#include "SpellMgr.h"
#include "SpellAuraEffects.h"
#include "SpellHistory.h"
#include "SpellPackets.h"
#include "TemporarySummon.h"
#include "Unit.h"
#include "World.h"
#include "IVMapManager.h"

enum DHSpells
{
    SPELL_DH_ANNIHILATION                          = 201427,
    SPELL_DH_ANNIHILATION_MAINHAIND                = 201428,
    SPELL_DH_ANNIHILATION_OFFHAND                  = 227518,
    SPELL_DH_BLADE_DANCE                           = 188499,
    SPELL_DH_SIGIL_OF_MISSERY                      = 207684,
    SPELL_DH_SIGIL_OF_SILENCE                      = 202137,
    SPELL_DH_SIGIL_OF_CHAINS                       = 202138,
    SPELL_DH_BLIND_FURY                            = 203550,
    SPELL_DH_BLOODLET                              = 206473,
    SPELL_DH_BLOODLET_DOT                          = 207690,
    SPELL_DH_BLUR                                  = 198589,
    SPELL_DH_BURNING_ALIVE                         = 207739,
    SPELL_DH_CHAOS_CLEAVE                          = 206475,
    SPELL_DH_CHAOS_CLEAVE_DAMAGE                   = 236237,
    SPELL_DH_CHAOS_NOVA                            = 179057,
    SPELL_DH_CHAOS_STRIKE                          = 162794,
    SPELL_DH_CHAOS_STRIKE_MAIN_HAND                = 199547,
    SPELL_DH_CHAOS_STRIKE_OFF_HAND                 = 222031,
    SPELL_DH_CHAOS_STRIKE_PROC                     = 193840,
    SPELL_DH_CONSUME_MAGIC                         = 278326,
    SPELL_DH_CONSUME_SOUL_10                       = 228532,
    SPELL_DH_CONSUME_SOUL_25                       = 178963,
    SPELL_DH_CONSUME_SOUL_25_VENG                  = 210042,
    SPELL_DH_CONSUME_SOUL_DEMON                    = 202644,
    SPELL_DH_CONSUME_SOUL_DEMON_VENG               = 208015,
    SPELL_DH_DARKNESS_BUFF                         = 209426,
    SPELL_DH_DEMON_BLADES                          = 203555,
    SPELL_DH_DEMON_BLADES_TRIGGER                  = 203796,
    SPELL_DH_DEMON_REBORN                          = 193897,
    SPELL_DH_DEMON_SPIKES                          = 203720,
    SPELL_DH_DEMON_SPIKES_BUFF                     = 203819,
    SPELL_DH_DEMONIC                               = 213410,
    SPELL_DH_DEMONIC_APPETITE                      = 206478,
    SPELL_DH_DEMONIC_APPETITE_FURY                 = 210041,
    SPELL_DH_DEMONS_BITE                           = 162243,
    SPELL_DH_EYE_BEAM                              = 198013,
    SPELL_DH_EYE_BEAM_DAMAGE                       = 198030,
    SPELL_DH_EYE_BEAM_VISUAL                       = 194326,
    SPELL_DH_FEAST_OF_SOULS                        = 207697,
    SPELL_DH_FEAST_OF_SOULS_HEAL                   = 207693,
    SPELL_DH_FEED_THE_DEMON                        = 218612,
    SPELL_DH_FEL_BARRAGE                           = 211053,
    SPELL_DH_FEL_BARRAGE_TRIGGER                   = 211052,
    SPELL_DH_FEL_DEVASTATION_DAMAGE                = 212105,
    SPELL_DH_FEL_DEVASTATION_HEAL                  = 212106,
    SPELL_DH_FEL_ERUPTION                          = 211881,
    SPELL_DH_FEL_ERUPTION_DAMAGE                   = 225102,
    SPELL_DH_FEL_MASTERY                           = 192939,
    SPELL_DH_FEL_RUSH                              = 195072,
    SPELL_DH_FEL_RUSH_AIR                          = 197923,
    SPELL_DH_FEL_RUSH_DAMAGE                       = 192611,
    SPELL_DH_FEL_RUSH_DASH                         = 197922,
    SPELL_DH_FEL_RUSH_DASH2                        = 208101,
    SPELL_DH_FELBLADE                              = 232893,
    SPELL_DH_FELBLADE_CHARGE                       = 213241,
    SPELL_DH_FELBLADE_DAMAGE                       = 213243,
    SPELL_DH_FIERY_BRAND_DOT                       = 207771,
    SPELL_DH_FIERY_BRAND_DMG_REDUCTION_DEBUFF      = 207744,
    SPELL_DH_FIRST_BLOOD                           = 206416,
    SPELL_DH_FLAME_CRASH                           = 227322,
    SPELL_DH_FRAILITY                              = 224509,
    SPELL_DH_GLIDE                                 = 131347,
    SPELL_DH_GLIDE_KNOCKBACK                       = 196353,
    SPELL_DH_GLUTTONY                              = 227327,
    SPELL_DH_GLUTTONY_BUFF                         = 227330,
    SPELL_DH_IMMOLATION_AURA                       = 258920,
    SPELL_DH_IMMOLATION_AURA_VISUAL                = 201122,
    SPELL_DH_INFERNAL_STRIKE                       = 189110,
    SPELL_DH_INFERNAL_STRIKE_DAMAGE                = 189112,
    SPELL_DH_INFERNAL_STRIKE_JUMP                  = 189111,
    SPELL_DH_INFERNAL_STRIKE_VISUAL                = 208461,
    SPELL_DH_LAST_RESORT_DEBUFF                    = 209261,
    SPELL_DH_METAMORPHOSIS_HAVOC                   = 162264,
    SPELL_DH_METAMORPHOSIS                         = 191427,
    SPELL_DH_METAMORPHOSIS_BUFFS                   = 162264,
    SPELL_DH_METAMORPHOSIS_IMMUNITY                = 201453,
    SPELL_DH_METAMORPHOSIS_LEAP                    = 191428,
    SPELL_DH_METAMORPHOSIS_STUN                    = 200166,
    SPELL_DH_METAMORPHOSIS_DAZZLE                  = 247121,
    SPELL_DH_METAMORPHOSIS_VENGEANCE               = 187827,
    SPELL_DH_MOMENTUM                              = 206476,
    SPELL_DH_MOMENTUM_BUFF                         = 208628,
    SPELL_DH_NEMESIS                               = 206491,
    SPELL_DH_NETHER_BOND                           = 207810,
    SPELL_DH_NETHER_BOND_DAMAGE                    = 207812,
    SPELL_DH_NETHER_BOND_PERIODIC                  = 207811,
    SPELL_DH_PREPARED                              = 203551,
    SPELL_DH_RAZOR_SPIKES_SLOW                     = 210003,
    SPELL_DH_SHATTERED_SOULS                       = 178940,
    SPELL_DH_SHATTER_SOUL                          = 209651,
    SPELL_DH_SHATTER_SOUL_1                        = 209980,
    SPELL_DH_SHATTER_SOUL_2                        = 209981,
    SPELL_DH_SHATTER_SOUL_3                        = 210038,
    SPELL_DH_SHATTERED_SOUL_LESSER_SOUL_FRAGMENT_1 = 228533,
    SPELL_DH_SHATTERED_SOUL_LESSER_SOUL_FRAGMENT_2 = 237867,
    SPELL_DH_SS_VENGEANCE_NORMAL_AT                = 203795,
    SPELL_DH_SS_HAVOC_NORMAL_AT                    = 209693,    
    SPELL_DH_SS_DEMON_AT                           = 204062,
    SPELL_DH_SS_LESSET_AT                          = 204255,
    SPELL_DH_SS_VENGEANCE_SOUL_NORMAL              = 226263,
    SPELL_DH_SS_HAVOC_SOUL_NORMAL                  = 209687,    
    SPELL_DH_SS_VENGEANCE_LESSER_SOUL              = 226258,
    SPELL_DH_SS_HAVOC_LESSER_SOUL                  = 228536,
    SPELL_DH_SS_VENG_LESSER_HEAL                   = 203794,
    SPELL_DH_SS_VENGEANCE_SOUL_DEMON               = 226264,
    SPELL_DH_SS_HAVOC_SOUL_DEMON                   = 226370,
    SPELL_DH_SS_DEMON_SOUL_BUFF                    = 210049,
    SPELL_DH_SHEAR                                 = 203782,
    SPELL_DH_SIGIL_OF_CHAINS_EXPLOSION             = 208673,
    SPELL_DH_SIGIL_OF_CHAINS_SLOW                  = 204843,
    SPELL_DH_SIGIL_OF_CHAINS_TRIGGER               = 208674,
    SPELL_DH_SIGIL_OF_FLAME_EXPLOSION              = 208710,
    SPELL_DH_SIGIL_OF_FLAME_NO_DEST                = 204513,
    SPELL_DH_SIGIL_OF_FLAME_TRIGGER                = 204598,
    SPELL_DH_SIGIL_OF_MISERY_EXPLOSION             = 208714,
    SPELL_DH_SIGIL_OF_MISERY_TRIGGER               = 207685,
    SPELL_DH_SIGIL_OF_SILENCE_EXPLOSION            = 208709,
    SPELL_DH_SIGIL_OF_SILENCE_TRIGGER              = 204490,
    SPELL_DH_SOUL_BARRIER                          = 263648,
    SPELL_DH_SOUL_CLEAVE_DAMAGE                    = 228478,
    SPELL_DH_SOUL_RENDING_HAVOC                    = 204909,
    SPELL_DH_SOUL_RENDING_VENGEANCE                = 217996,
    SPELL_DH_SPIRIT_BOMB                           = 247454,
    SPELL_DH_SPIRIT_BOMB_DAMAGE                    = 247455,
    SPELL_DH_SPIRIT_BOMB_HEAL                      = 227255,
    SPELL_DH_SPIRIT_BOMB_VISUAL                    = 218678,
    SPELL_DH_THROW_GLAIVE                          = 185123,
    SPELL_DH_VENGEFUL_RETREAT                      = 198793,
    SPELL_DH_VENGEFUL_RETREAT_FURY                 = 203650,
    SPELL_DH_VENGEFUL_RETREAT_TRIGGER              = 198813,
    SPELL_DH_CHAOS_BRAND                           = 1490,
    SPELL_DH_FELBLADE_AURA                         = 236167,
    SPELL_DH_FELBLADE_INDICATOR                    = 204497,
    SPELL_DH_CYCLE_OF_HATRED                       = 258887,
    SPELL_AURA_DH_INSATIABLE_HUNGER                = 258876,
	SPELL_DH_BLUR_AURA						       = 212800,
	SPELL_DH_SOLITUDE_BUFF					       = 211510,
	SPELL_DH_EYE_OF_LOTHERAS_DAMAGE			       = 206650,
    SPELL_DH_MANA_RIFT                             = 235903,
    SPELL_DH_MANA_RIFT_EFFECT                      = 235904,
    SPELL_DH_DEMONIC_ORIGINS                       = 235893,
    SPELL_DH_DEMONIC_ORIGINS_DAMAGE                = 235894,
    SPELL_DH_MANA_BREAK                            = 203704,
	SPELL_DH_JAGGED_SPIKES					       = 205627,
	SPELL_DH_JAGGED_SPIKES_DAMAGE			       = 208790,
	SPELL_DH_JAGGED_SPIKES_AURA				       = 208796,
	SPELL_DH_FALLOUT						       = 227174,
    SPELL_DH_IMPRISION                             = 217832,
    SPELL_DH_TRAIL_OF_RUIN                         = 258881,
    SPELL_DH_TRAIL_OF_RUIN_DAMAGE                  = 258883,
    SPELL_DH_BLADE_DANCE_LAST_HIT                  = 200685,
    SPELL_DH_PREPARED_ENERGIZE                     = 203650,
    SPELL_DH_SOUL_FRAGMENT_COUNTER                 = 203981,
    SPELL_DH_DISRUPT                               = 183752,
    SPELL_DH_DISRUPT_ENERGIZE                      = 218903,
    SPELL_DH_BURNING_SOUL_POWER                    = 280012,
    SPELL_DH_BURNING_SOUL_BUFF                     = 274289,
    SPELL_DH_SOUL_CLEAVE                           = 228477,
    SPELL_DH_VOID_REAVER                           = 268175,
    SPELL_DH_VOID_REAVER_DEBUFF                    = 268178,
    SPELL_DH_FRACTURE                              = 263642,
    SPELL_DH_CONSUME_SOUL_HAVOC                    = 228542,
    SPELL_DH_CONSUME_SOUL_HAVOC_DEMON              = 228556,
    SPELL_DH_CONSUME_SOUL_HAVOC_SHATTERED          = 228540,
    SPELL_DH_CONSUME_SOUL_VENGEANCE                = 208014,
    SPELL_DH_CONSUME_SOUL_VENGEANCE_DEMON          = 210050,
    SPELL_DH_CONSUME_SOUL_VENGEANCE_SHATTERED      = 210047,
    SPELL_DH_SHEAR_PROC                            = 203783,
    SPELL_DH_VENGEANCE_SHATTERED_SOUL              = 204254,
    SPELL_DH_RIGID_CARAPACE_POWER                  = 275350,
    SPELL_DH_RIGID_CARAPACE_BUFF                   = 275351,
    SPELL_DH_CYCLE_OF_BLINDING_POWER               = 278502,
    SPELL_DH_CYCLE_OF_BLINDING_BUFF                = 278769,
    SPELL_DH_SOULMONGER_POWER                      = 274344,
    SPELL_DH_SOULMONGER_SHIELD                     = 274346,
    SPELL_DH_REVEAL_IN_PAIN_POWER                  = 272983,
    SPELL_DH_REVEAL_IN_PAIN_PROC                   = 272986,
};

enum NemesisTargets
{
    NEMESIS_ABERRATION                          = 208607,
    NEMESIS_ELEMENTAL                           = 208611,
    NEMESIS_MECHANICAL                          = 208616,
    NEMESIS_DRAGONKIN                           = 208610,
    NEMESIS_HUMANOID                            = 208605,
    NEMESIS_CRITTERS                            = 208609,
    NEMESIS_DEMONS                              = 208579,
    NEMESIS_GIANTS                              = 208612,
    NEMESIS_UNDEAD                              = 208614,
    NEMESIS_BEASTS                              = 208608
};

enum DemnHunterAreatrigger
{
    AREATRIGGER_DH_SHATTERED_SOULS_HAVOC           = 8352,
    AREATRIGGER_DH_SHATTERED_SOULS_HAVOC_DEMON     = 11231,
    AREATRIGGER_DH_SHATTERED_SOULS_VENGEANCE       = 11266,
    AREATRIGGER_DH_SHATTERED_SOULS_VENGEANCE_DEMON = 10693,
    AREATRIGGER_DH_SOUL_FRAGMENT_HAVOC             = 12929,
    AREATRIGGER_DH_SOUL_FRAGMENT_VENGEANCE         = 10665,
};

void AbsorbSoul(AreaTrigger* at, Unit* caster)
{
    uint32 spellId = 0;

    switch (at->GetEntry())
    {
    case AREATRIGGER_DH_SHATTERED_SOULS_VENGEANCE_DEMON:
        spellId = SPELL_DH_CONSUME_SOUL_VENGEANCE_DEMON;
        break;
    case AREATRIGGER_DH_SHATTERED_SOULS_VENGEANCE:
        spellId = SPELL_DH_CONSUME_SOUL_VENGEANCE_SHATTERED;
        break;
    case AREATRIGGER_DH_SOUL_FRAGMENT_VENGEANCE:
        spellId = SPELL_DH_CONSUME_SOUL_VENGEANCE;
        break;
    case AREATRIGGER_DH_SHATTERED_SOULS_HAVOC_DEMON:
        spellId = SPELL_DH_CONSUME_SOUL_HAVOC_DEMON;
        break;
    case AREATRIGGER_DH_SHATTERED_SOULS_HAVOC:
        spellId = SPELL_DH_CONSUME_SOUL_HAVOC_SHATTERED;
        break;
    case AREATRIGGER_DH_SOUL_FRAGMENT_HAVOC:
        spellId = SPELL_DH_CONSUME_SOUL_HAVOC;
        break;
    }

    if (!spellId)
        return;

    caster->CastSpell(at->GetPosition(), spellId, true);
    at->Remove();

    //if (AuraEffect* auraEff = caster->GetAuraEffect(SPELL_DH_SOULMONGER_POWER, EFFECT_0))
    //    caster->CastSpell(SPELL_DH_SOULMONGER_SHIELD, SPELLVALUE_BASE_POINT0, auraEff->GetAmount(), caster);
}

class dh_playerscript : public PlayerScript
{
public:
    dh_playerscript() : PlayerScript("dh_playerscript") {}

    void OnSpellLearned(Player* player, uint32 spellID) override
    {
        if (!player)
            return;

        // Havoc DH
        if (player->GetSpecializationId() == TALENT_SPEC_DEMON_HUNTER_HAVOC)
        {
            if (spellID == SPELL_DH_DEMONIC_ORIGINS)
                if (!player->HasAura(SPELL_DH_METAMORPHOSIS_BUFFS))
                    player->CastSpell(player, SPELL_DH_DEMONIC_ORIGINS_DAMAGE, true);
        }
    }

    void OnSpellRemoved(Player* player, uint32 spellID) override
    {
        if (!player)
            return;

        // Havoc DH
        if (player->GetSpecializationId() == TALENT_SPEC_DEMON_HUNTER_HAVOC)
        {
            if (spellID == SPELL_DH_DEMONIC_ORIGINS)
                player->RemoveAura(SPELL_DH_DEMONIC_ORIGINS_DAMAGE);
        }
    }

    void OnLogin(Player* player, bool first) override
    {
        if (player->GetSpecializationId() == TALENT_SPEC_DEMON_HUNTER_HAVOC)
        {
            std::vector<int32> spellIds
            {
                SPELL_DH_CHAOS_NOVA, SPELL_DH_CONSUME_MAGIC, SPELL_DH_THROW_GLAIVE, SPELL_DH_METAMORPHOSIS,
                SPELL_DH_EYE_BEAM, SPELL_DH_BLUR, SPELL_DH_VENGEFUL_RETREAT, SPELL_DH_BLADE_DANCE,
                344866, // vengeful retreat
                183752, // disrupt
                200749, // dh talent spell
                195440, // chaos nova
            };

            for (auto spell : spellIds)
            {
                if (sSpellMgr->GetSpellInfo(spell) && !player->HasSpell(spell))
                    player->LearnSpell(spell, false);
            }
            if (!player->HasSpell(258920))
                player->CastSpell(player, 195447, true);
        }

        if (player->GetClass() == CLASS_DEMON_HUNTER)
        {
            std::vector<uint32> quests
            {
                40254,
            };

            for (auto questid : quests)
            {
                auto quest = sObjectMgr->GetQuestTemplate(questid);
                if (!quest)
                    continue;
                if (player->GetQuestStatus(questid) == QUEST_STATUS_NONE)
                {
                    player->AddQuestAndCheckCompletion(quest, player);
                    player->CompleteQuest(questid);
                    player->RewardQuest(quest, LootItemType::Item, 0, player);
                }
            }
        }
    }
};

// Nether Bond - 207810
class spell_dh_nether_bond : public SpellScriptLoader
{
public:
    spell_dh_nether_bond() : SpellScriptLoader("spell_dh_nether_bond") {}

    class spell_dh_nether_bond_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_dh_nether_bond_SpellScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_DH_NETHER_BOND_DAMAGE) ||
                !sSpellMgr->GetSpellInfo(SPELL_DH_NETHER_BOND_PERIODIC))
                return false;
            return true;
        }

        void HandleDummy()
        {
            Unit* caster = GetCaster();
            if (!caster)
                return;

            caster->CastSpell(caster, SPELL_DH_NETHER_BOND_PERIODIC, true);
        }

        void Register() override
        {
            OnCast += SpellCastFn(spell_dh_nether_bond_SpellScript::HandleDummy);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_dh_nether_bond_SpellScript();
    }
};

// Nether Bond periodic - 207811
class spell_dh_nether_bond_periodic : public SpellScriptLoader
{
public:
    spell_dh_nether_bond_periodic() : SpellScriptLoader("spell_dh_nether_bond_periodic") {}

    class spell_dh_nether_bond_periodic_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_dh_nether_bond_periodic_AuraScript);

        Unit* m_BondUnit;

        void HandlePeriodic(AuraEffect const* /*aurEff*/)
        {
            Unit* caster = GetCaster();
            if (!caster)
                return;

            if (!m_BondUnit)
                m_BondUnit = GetBondUnit();

            if (!m_BondUnit)
                return;

            int32 casterHealBp = 0;
            int32 casterDamageBp = 0;
            int32 targetHealBp = 0;
            int32 targetDamageBp = 0;

            float casterHp = caster->GetHealthPct();
            float targetHp = m_BondUnit->GetHealthPct();
            float healthPct = (casterHp + targetHp) / 2.0f;

            if (casterHp < targetHp)
            {
                casterHealBp = caster->CountPctFromMaxHealth(healthPct) - caster->GetHealth();
                targetDamageBp = m_BondUnit->GetHealth() - m_BondUnit->CountPctFromMaxHealth(healthPct);
            }
            else
            {
                casterDamageBp = caster->GetHealth() - caster->CountPctFromMaxHealth(healthPct);
                targetHealBp = m_BondUnit->CountPctFromMaxHealth(healthPct) - m_BondUnit->GetHealth();
            }

            //CustomSpellValues casterValues;
            //CustomSpellValues targetValues;
            //casterValues.AddSpellMod(SPELLVALUE_BASE_POINT0, casterDamageBp);
            //casterValues.AddSpellMod(SPELLVALUE_BASE_POINT1, casterHealBp);
            //targetValues.AddSpellMod(SPELLVALUE_BASE_POINT0, targetDamageBp);
            //targetValues.AddSpellMod(SPELLVALUE_BASE_POINT1, targetHealBp);
            //
            //caster->CastSpell(caster, SPELL_DH_NETHER_BOND_DAMAGE, casterValues, TRIGGERED_FULL_MASK);
            //caster->CastSpell(m_BondUnit, SPELL_DH_NETHER_BOND_DAMAGE, targetValues, TRIGGERED_FULL_MASK);
        }

        Unit* GetBondUnit()
        {
            Unit* caster = GetCaster();
            if (!caster)
                return nullptr;

            std::list<Unit*> units;
            Trinity::AnyUnitInObjectRangeCheck check(caster, 100.0f);
            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> search(caster, units, check);
            Cell::VisitAllObjects(caster, search, 100.0f);

            for (Unit* u : units)
                if (u->HasAura(SPELL_DH_NETHER_BOND, caster->GetGUID()))
                    return u;

            return nullptr;
        }

        void HandleApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            Unit* caster = GetCaster();
            if (!caster)
                return;

            m_BondUnit = GetBondUnit();
        }

        void Register() override
        {
            AfterEffectApply += AuraEffectApplyFn(spell_dh_nether_bond_periodic_AuraScript::HandleApply, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY, AURA_EFFECT_HANDLE_REAL);
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_dh_nether_bond_periodic_AuraScript::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_dh_nether_bond_periodic_AuraScript();
    }
};

// Soul Barrier - 263648 
//Last Update 8.0.1 Build 28153
class spell_dh_soul_barrier : public AuraScript
{
    PrepareAuraScript(spell_dh_soul_barrier);

    void CalcAmount(AuraEffect const* /*aurEff*/, int32& amount, bool& /*canBeRecalculated*/)
    {
        Unit* caster = GetCaster();
        if (!caster)
            return;

        uint32 soulShardsCount = 0;
        for (AreaTrigger* at : caster->GetAreaTriggersByEntry({ AREATRIGGER_DH_SOUL_FRAGMENT_VENGEANCE, AREATRIGGER_DH_SHATTERED_SOULS_VENGEANCE, AREATRIGGER_DH_SHATTERED_SOULS_VENGEANCE_DEMON }))
        {
            if (caster->GetDistance(at) <= 25.0f)
            {
                AbsorbSoul(at, caster);
                soulShardsCount++;
            }
        }

        if (Player* player = caster->ToPlayer())
        {
            soulShardsCount = soulShardsCount + 5;
            amount = soulShardsCount * player->GetTotalAttackPowerValue(BASE_ATTACK);
            AddPct(amount, player->m_activePlayerData->Versatility + player->m_activePlayerData->VersatilityBonus);
        }
    }

    void Register() override
    {
        DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_dh_soul_barrier::CalcAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
    }
};

// Fraility - 224509
//Last Update 8.0.1 Build 28153
class aura_dh_fraility : public AuraScript
{
    PrepareAuraScript(aura_dh_fraility);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_DH_SPIRIT_BOMB_HEAL });
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        Unit* caster = aurEff->GetCaster();
        if (!caster || !eventInfo.GetDamageInfo())
            return;

        int32 healAmount = CalculatePct(eventInfo.GetDamageInfo()->GetDamage(), GetEffectInfo(EFFECT_0).BasePoints);
        CastSpellExtraArgs args(true);
        caster->CastSpell(caster, SPELL_DH_SPIRIT_BOMB_HEAL, args.AddSpellBP0(healAmount));
    }

    void Register() override
    {
        //OnEffectProc += AuraEffectProcFn(aura_dh_fraility::HandleProc, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

// Spirit Bomb - 247454
//Last Update 8.0.1 Build 28153
class spell_dh_spirit_bomb : public SpellScript
{
    PrepareSpellScript(spell_dh_spirit_bomb);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_DH_SPIRIT_BOMB, SPELL_DH_SPIRIT_BOMB_DAMAGE, SPELL_DH_SPIRIT_BOMB_HEAL });
    }

    SpellCastResult CheckCast()
    {
        Unit* caster = GetCaster();
        if (!caster)
            return SPELL_FAILED_DONT_REPORT;

        float range = float(GetEffectInfo(EFFECT_0).BasePoints);
        bool _haveShatteredSouls = false;

        for (AreaTrigger* at : caster->GetAreaTriggersByEntry({ AREATRIGGER_DH_SOUL_FRAGMENT_VENGEANCE, AREATRIGGER_DH_SOUL_FRAGMENT_HAVOC, AREATRIGGER_DH_SHATTERED_SOULS_VENGEANCE, AREATRIGGER_DH_SHATTERED_SOULS_HAVOC, AREATRIGGER_DH_SHATTERED_SOULS_HAVOC_DEMON, AREATRIGGER_DH_SHATTERED_SOULS_VENGEANCE_DEMON }))
        {
            if (caster->GetDistance(at) <= range)
            {
                _haveShatteredSouls = true;
                break;
            }
        }

        if (!_haveShatteredSouls)
        {
            SetCustomCastResultMessage(SPELL_CUSTOM_ERROR_REQUIRES_NEARBY_SOUL_FRAGMENT);
            return SPELL_FAILED_CUSTOM_ERROR;
        }
        else
            return SPELL_CAST_OK;
    }

    void HandleDummy(SpellEffIndex /*effIndex*/)
    {
        if (Unit* caster = GetCaster())
            caster->CastSpell(caster, SPELL_DH_SPIRIT_BOMB_DAMAGE, true);
    }

    void Register() override
    {
        OnCheckCast += SpellCheckCastFn(spell_dh_spirit_bomb::CheckCast);
        OnEffectHitTarget += SpellEffectFn(spell_dh_spirit_bomb::HandleDummy, EFFECT_0, SPELL_EFFECT_APPLY_AURA);
    }
};

// Spirit Bomb damage - 247455
//Last Update 8.0.1 Build 28153
class spell_dh_spirit_bomb_damage : public SpellScript
{
    PrepareSpellScript(spell_dh_spirit_bomb_damage);

    SpellCastResult CheckCast()
    {
        mod = 0;

        Unit* caster = GetCaster();
        if (!caster)
            return SPELL_FAILED_DONT_REPORT;

        SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(SPELL_DH_SPIRIT_BOMB);
        if(!spellInfo)
            return SPELL_FAILED_DONT_REPORT;

        float range = float(spellInfo->GetEffect(EFFECT_0).BasePoints);
        bool _haveShatteredSouls = false;

        for (AreaTrigger* at : caster->GetAreaTriggersByEntry({ AREATRIGGER_DH_SOUL_FRAGMENT_VENGEANCE, AREATRIGGER_DH_SOUL_FRAGMENT_HAVOC, AREATRIGGER_DH_SHATTERED_SOULS_VENGEANCE, AREATRIGGER_DH_SHATTERED_SOULS_HAVOC, AREATRIGGER_DH_SHATTERED_SOULS_HAVOC_DEMON, AREATRIGGER_DH_SHATTERED_SOULS_VENGEANCE_DEMON }))
        {
            if (caster->GetDistance(at) <= range)
            {
                mod++;
                AbsorbSoul(at, caster);
                if (mod >= spellInfo->GetEffect(EFFECT_1).BasePoints)
                    break;
            }
        }

        if (!mod)
        {
            SetCustomCastResultMessage(SPELL_CUSTOM_ERROR_REQUIRES_NEARBY_SOUL_FRAGMENT);
            return SPELL_FAILED_CUSTOM_ERROR;
        }
        else
            return SPELL_CAST_OK;
    }

    void HandleCast()
    {
        if (mod)
            if (Unit* caster = GetCaster())
                caster->CastSpell(caster, SPELL_DH_FRAILITY, true);
    }

    void HandleDamage(SpellEffIndex /*effIndex*/)
    {
        if (mod)
            if (Unit* caster = GetCaster())
                if (Unit* target = GetHitUnit())
                    SetHitDamage(GetHitDamage() * mod);
    }

    void Register() override
    {
        OnCheckCast += SpellCheckCastFn(spell_dh_spirit_bomb_damage::CheckCast);
        OnCast += SpellCastFn(spell_dh_spirit_bomb_damage::HandleCast);
        OnEffectHitTarget += SpellEffectFn(spell_dh_spirit_bomb_damage::HandleDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }

private:
    uint32 mod;
};

// Blade Turning - 203753
class spell_dh_blade_turning : public SpellScriptLoader
{
public:
    spell_dh_blade_turning() : SpellScriptLoader("spell_dh_blade_turning") {}

    class spell_dh_blade_turning_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_dh_blade_turning_AuraScript);

        bool CheckProc(ProcEventInfo& eventInfo)
        {
            if (eventInfo.GetHitMask() & PROC_HIT_PARRY)
                return true;
            return false;
        }

        void Register() override
        {
            DoCheckProc += AuraCheckProcFn(spell_dh_blade_turning_AuraScript::CheckProc);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_dh_blade_turning_AuraScript();
    }
};

// Fel Devastation - 212084
class spell_dh_fel_devastation : public SpellScriptLoader
{
public:
    spell_dh_fel_devastation() : SpellScriptLoader("spell_dh_fel_devastation") {}

    class spell_dh_fel_devastation_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_dh_fel_devastation_AuraScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_DH_FEL_DEVASTATION_DAMAGE) ||
                !sSpellMgr->GetSpellInfo(SPELL_DH_FEL_DEVASTATION_HEAL))
                return false;
            return true;
        }

        void HandlePeriodic(AuraEffect const* /*aurEff*/)
        {
            Unit* caster = GetCaster();
            if (!caster)
                return;

            caster->CastSpell(caster, SPELL_DH_FEL_DEVASTATION_DAMAGE, true);
            caster->CastSpell(caster, SPELL_DH_FEL_DEVASTATION_HEAL, true);
        }

        void Demorph(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            Unit* caster = GetCaster();
            if (!caster)
                return;

            caster->SetDisplayId(caster->GetNativeDisplayId());
        }

        void Register() override
        {
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_dh_fel_devastation_AuraScript::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
            OnEffectRemove += AuraEffectRemoveFn(spell_dh_fel_devastation_AuraScript::Demorph, EFFECT_2, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        }
    };

    class spell_dh_fel_devastation_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_dh_fel_devastation_SpellScript);

        void Morph()
        {
            Unit* caster = GetCaster();
            if (!caster)
                return;

            caster->SetDisplayId(68671);
        }

        void Register() override
        {
            OnPrepare += SpellOnPrepareFn(spell_dh_fel_devastation_SpellScript::Morph);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_dh_fel_devastation_SpellScript();
    }

    AuraScript* GetAuraScript() const override
    {
        return new spell_dh_fel_devastation_AuraScript();
    }
};

// Fracture - 209795, 263642 
// Last Update 8.0.1 Build 28153
class spell_dh_fracture : public SpellScript
{
    PrepareSpellScript(spell_dh_fracture);

    void HandleDummy(SpellEffIndex /*effIndex*/)
    {
        if (Unit* caster = GetCaster())
        {
            for (int i = 0; i < 2; ++i)
            {
                auto randPos = caster->GetRandomNearPosition(10.0f);
                caster->CastSpell(randPos, SPELL_DH_SS_VENGEANCE_LESSER_SOUL, true);
            }
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_dh_fracture::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

// Consume Soul vengeance - 210042, 203794
// Last Update 8.0.1 Build 28153
class spell_dh_consume_soul_vengeance : public SpellScript
{
    PrepareSpellScript(spell_dh_consume_soul_vengeance);

    void HandleCast()
    {
        Unit* caster = GetCaster();
        if (!caster)
            return;

        if (caster->HasAura(SPELL_DH_GLUTTONY))
            caster->CastSpell(caster, SPELL_DH_GLUTTONY_BUFF, true);

        if (caster->HasAura(SPELL_DH_FEED_THE_DEMON))
            caster->GetSpellHistory()->ReduceChargeCooldown(sSpellMgr->GetSpellInfo(SPELL_DH_DEMON_SPIKES)->ChargeCategoryId, 2 * IN_MILLISECONDS);
    }

    void HandleHitTarget(SpellEffIndex /*effIndex*/)
    {
        if (GetSpellInfo()->Id != SPELL_DH_SS_VENG_LESSER_HEAL)
            return;

        if (Unit* caster = GetCaster())
        {
            if (SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(SPELL_DH_SHEAR_PROC))
            {
                uint32 damageTaken = caster->GetDamageOverLastSeconds(spellInfo->GetEffect(EFFECT_3).BasePoints);
                int32 healing = (damageTaken < CalculatePct(caster->GetMaxHealth(), spellInfo->GetEffect(EFFECT_2).BasePoints) ? CalculatePct(caster->GetMaxHealth(), spellInfo->GetEffect(EFFECT_2).BasePoints) : CalculatePct(damageTaken, spellInfo->GetEffect(EFFECT_1).BasePoints));
                SetHitHeal(healing);                
            }
        }
    }

    void Register() override
    {
        OnCast += SpellCastFn(spell_dh_consume_soul_vengeance::HandleCast);
        OnEffectHitTarget += SpellEffectFn(spell_dh_consume_soul_vengeance::HandleHitTarget, EFFECT_0, SPELL_EFFECT_HEAL);
    }
};

// 258921 - Immolation Aura initial damage
class spell_dh_immolation_aura_damage: public SpellScript
{
	PrepareSpellScript(spell_dh_immolation_aura_damage);

	void HandleHitTarget(SpellEffIndex /*effIndex*/)
	{
        if (Unit* caster = GetCaster())
        {
            if (roll_chance_i(60) && caster->HasAura(SPELL_DH_FALLOUT))// Missing proc chance, wowhead said that is near to 60-70
            {
                auto randPos = caster->GetRandomNearPosition(10.0f);
                caster->CastSpell(randPos, SPELL_DH_SS_VENGEANCE_LESSER_SOUL, true);
            }
        }
    }

	void Register() override
	{
		OnEffectHitTarget += SpellEffectFn(spell_dh_immolation_aura_damage::HandleHitTarget, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
	}
};

// Razor Spikes - 209400
class spell_dh_razor_spikes : public SpellScriptLoader
{
public:
    spell_dh_razor_spikes() : SpellScriptLoader("spell_dh_razor_spikes") {}

    class spell_dh_razor_spikes_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_dh_razor_spikes_AuraScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_DH_RAZOR_SPIKES_SLOW))
                return false;
            return true;
        }

        bool CheckProc(ProcEventInfo& eventInfo)
        {
            if (eventInfo.GetDamageInfo() &&
                (eventInfo.GetDamageInfo()->GetAttackType() == BASE_ATTACK ||
                 eventInfo.GetDamageInfo()->GetAttackType() == OFF_ATTACK))
            {
                Unit* caster = eventInfo.GetDamageInfo()->GetAttacker();
                Unit* target = eventInfo.GetDamageInfo()->GetVictim();
                if (!caster || !target)
                    return false;

                if (caster->HasAura(SPELL_DH_DEMON_SPIKES_BUFF))
                    caster->CastSpell(target, SPELL_DH_RAZOR_SPIKES_SLOW, true);
                return true;
            }
            return false;
        }

        void Register() override
        {
            DoCheckProc += AuraCheckProcFn(spell_dh_razor_spikes_AuraScript::CheckProc);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_dh_razor_spikes_AuraScript();
    }
};

// Soul Cleave - 228477
//Last Update 8.0.1 Build 28153
class spell_dh_soul_cleave : public SpellScriptLoader
{
public:
    spell_dh_soul_cleave() : SpellScriptLoader("spell_dh_soul_cleave") {}

    class spell_dh_soul_cleave_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_dh_soul_cleave_SpellScript);

        int32 m_ExtraSpellCost;

        bool Load() override
        {
            if (Unit* caster = GetCaster())
            {
                m_ExtraSpellCost = std::min(caster->GetPower(POWER_PAIN), 600);
                return true;
            }
            return false;
        }

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_DH_SOUL_CLEAVE_DAMAGE))
                return false;
            return true;
        }

        SpellCastResult CheckCast()
        {
            Unit* caster = GetCaster();
            if (!caster)
                return SPELL_FAILED_DONT_REPORT;

            float range = float(GetEffectInfo(EFFECT_0).BasePoints);

            for (AreaTrigger* at : caster->GetAreaTriggersByEntry({ AREATRIGGER_DH_SOUL_FRAGMENT_VENGEANCE, AREATRIGGER_DH_SHATTERED_SOULS_VENGEANCE, AREATRIGGER_DH_SHATTERED_SOULS_VENGEANCE_DEMON }))
            {
                if (caster->GetDistance(at) <= range)
                {
                    ats.push_back(at);
                    if (ats.size() >= GetSpellInfo()->GetEffect(EFFECT_2).BasePoints)
                        break;
                }
            }

            if (!ats.size())
            {
                SetCustomCastResultMessage(SPELL_CUSTOM_ERROR_REQUIRES_NEARBY_SOUL_FRAGMENT);
                return SPELL_FAILED_CUSTOM_ERROR;
            }
            else
                return SPELL_CAST_OK;
        }

        void HandleSouls(SpellEffIndex /*effindex*/)
        {
            Unit* caster = GetCaster();
            if (!caster)
                return;

            for (auto* at : ats)
                AbsorbSoul(at, caster);
        }

        void HandleHeal(SpellEffIndex /*effIndex*/)
        {
            Unit* caster = GetCaster();
            if (!caster)
                return;

            if (caster->GetTypeId() != TYPEID_PLAYER)
                return;

            if (caster->HasAura(SPELL_DH_FEAST_OF_SOULS))
                caster->CastSpell(caster, SPELL_DH_FEAST_OF_SOULS_HEAL, true);
        }

        void Register() override
        {
            OnCheckCast += SpellCheckCastFn(spell_dh_soul_cleave_SpellScript::CheckCast);
            OnEffectHitTarget += SpellEffectFn(spell_dh_soul_cleave_SpellScript::HandleSouls, EFFECT_0, SPELL_EFFECT_DUMMY);
            OnEffectHitTarget += SpellEffectFn(spell_dh_soul_cleave_SpellScript::HandleHeal, EFFECT_3, SPELL_EFFECT_HEAL);
        }

        private:
            std::list<AreaTrigger*> ats;
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_dh_soul_cleave_SpellScript();
    }
};

// Soul cleave damage - 228478
// Last Update 8.0.1 Build 28153
class spell_dh_soul_cleave_damage : public SpellScriptLoader
{
public:
    spell_dh_soul_cleave_damage() : SpellScriptLoader("spell_dh_soul_cleave_damage") {}

    class spell_dh_soul_cleave_damage_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_dh_soul_cleave_damage_SpellScript);

        void HandleDamage(SpellEffIndex /*effIndex*/)
        {
            Unit* caster = GetCaster();
            Unit* target = GetHitUnit();
            if (!caster || !target)
                return;

            if (caster->HasAura(SPELL_DH_VOID_REAVER))
                caster->CastSpell(target, SPELL_DH_VOID_REAVER_DEBUFF, true);

            if (caster->HasAura(SPELL_DH_GLUTTONY_BUFF))
                caster->RemoveAurasDueToSpell(SPELL_DH_GLUTTONY_BUFF);
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_dh_soul_cleave_damage_SpellScript::HandleDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_dh_soul_cleave_damage_SpellScript();
    }
};

// 203783 - Shear Proc
//Last Update 8.0.1 Build 28153
class spell_dh_shear_proc : public AuraScript
{
    PrepareAuraScript(spell_dh_shear_proc);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        Unit* caster = eventInfo.GetActor();
        Unit* target = eventInfo.GetProcTarget();
        SpellInfo const* procSpell = eventInfo.GetSpellInfo();

        if (!caster || !target)
            return false;

        if (!procSpell || procSpell->Id != SPELL_DH_SHEAR)
            return false;

        return true;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();

        Unit* caster = eventInfo.GetActor();
        if (!caster)
            return;
        auto randPos = caster->GetRandomNearPosition(10.0f);
        caster->CastSpell(randPos, SPELL_DH_SS_VENGEANCE_LESSER_SOUL, true);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_dh_shear_proc::CheckProc);
        OnProc += AuraProcFn(spell_dh_shear_proc::HandleProc);
    }

private:
    uint8 shearCounter = 0;
};

// Fiery Brand - 204021
//Last Update 8.0.1 Build 28153
class spell_dh_fiery_brand : public SpellScript
{
    PrepareSpellScript(spell_dh_fiery_brand);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        if (!sSpellMgr->GetSpellInfo(SPELL_DH_FIERY_BRAND_DOT))
            return false;
        return true;
    }

    void HandleDamage(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        uint32 spellID = SPELL_DH_FIERY_BRAND_DMG_REDUCTION_DEBUFF;
        if (caster->HasAura(SPELL_DH_BURNING_ALIVE))
        {
            spellID = SPELL_DH_FIERY_BRAND_DOT;
            caster->Variables.Set<ObjectGuid>("BURNING_ALIVE_TARGET", target->GetGUID());
        }

        caster->CastSpell(target, spellID, true);
    }

    void HandleAfterHit()
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        if (caster->HasAura(SPELL_DH_REVEAL_IN_PAIN_POWER))
            caster->CastSpell(target, SPELL_DH_REVEAL_IN_PAIN_PROC, true);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_dh_fiery_brand::HandleDamage, EFFECT_1, SPELL_EFFECT_SCHOOL_DAMAGE);
        AfterHit += SpellHitFn(spell_dh_fiery_brand::HandleAfterHit);
    }
};

// Fiery Brand dot - 207771
//Last Update 8.0.1 Build 28153
class spell_dh_fiery_brand_dot : public AuraScript
{
    PrepareAuraScript(spell_dh_fiery_brand_dot);

    void HandlePeriodic(AuraEffect const* aurEff)
    {
        Unit* caster = aurEff->GetCaster();
        if (!caster || !caster->HasAura(SPELL_DH_BURNING_ALIVE))
            return;

        if (!caster->Variables.Exist("BURNING_ALIVE_TARGET"))
            return;

        Unit* owner = GetUnitOwner();
        if (!owner)
            return;

        if (owner->GetGUID() != caster->Variables.GetValue<ObjectGuid>("BURNING_ALIVE_TARGET"))
            return;

        std::list<Unit*> nearbyUnits;
        Trinity::AnyUnitInObjectRangeCheck checker(owner, 8.0f);
        Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(owner, nearbyUnits, checker);
        Cell::VisitAllObjects(owner, searcher, 8.0f);

        for (Unit* unit : nearbyUnits)
        {
            if (unit->HasAura(SPELL_DH_FIERY_BRAND_DOT, caster->GetGUID()))
                continue;

            if (unit == owner)
                continue;

            if (caster->IsValidAttackTarget(unit))
            {
                caster->CastSpell(unit, SPELL_DH_FIERY_BRAND_DOT, true);
                break;
            }
        }
    }

    void HandleRemove(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /* mode */)
    {
        if (Unit* caster = GetCaster())
        {
            if (!caster->Variables.Exist("BURNING_ALIVE_TARGET"))
                return;

            Unit* owner = GetUnitOwner();
            if (!owner)
                return;

            if (owner->GetGUID() != caster->Variables.GetValue<ObjectGuid>("BURNING_ALIVE_TARGET"))
                return;

            caster->Variables.Remove("BURNING_ALIVE_TARGET");
        }            
    }

    void Register() override
    {       
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_dh_fiery_brand_dot::HandlePeriodic, EFFECT_2, SPELL_AURA_PERIODIC_DAMAGE);
        OnEffectRemove += AuraEffectRemoveFn(spell_dh_fiery_brand_dot::HandleRemove, EFFECT_2, SPELL_AURA_MOD_PARRY_PERCENT, AURA_EFFECT_HANDLE_REAL);
    }
};

// Last resort - 209258
//Last Update 8.0.1 Build 28153
class spell_dh_last_resort : public AuraScript
{
    PrepareAuraScript(spell_dh_last_resort);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        if (!sSpellMgr->GetSpellInfo(SPELL_DH_LAST_RESORT_DEBUFF))
            return false;
        return true;
    }

    void CalcAmount(AuraEffect const* /*aurEff*/, int32& amount, bool& /*canBeRecalculated*/)
    {
        amount = -1;
    }

    void HandleAbsorb(AuraEffect* /*aurEff*/, DamageInfo& dmgInfo, uint32& absorbAmount)
    {
        Unit* caster = GetCaster();

        if (dmgInfo.GetDamage() < caster->GetHealth())
            return;

        if (caster->HasAura(SPELL_DH_LAST_RESORT_DEBUFF))
            return;

        absorbAmount = dmgInfo.GetDamage();
        caster->CastSpell(caster, SPELL_DH_LAST_RESORT_DEBUFF, true);
        caster->CastSpell(caster, SPELL_DH_METAMORPHOSIS_VENGEANCE, true);
        caster->SetHealth(caster->CountPctFromMaxHealth(GetSpellInfo()->GetEffect(EFFECT_1).BasePoints));
    }

    void Register() override
    {
        DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_dh_last_resort::CalcAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
        OnEffectAbsorb += AuraEffectAbsorbFn(spell_dh_last_resort::HandleAbsorb, EFFECT_0);
    }
};

// 178940 (Havoc) / 204254 (Vengeance) - Shattered Souls
//Last Update 8.0.1 Build 28153
class spell_dh_shattered_souls : public AuraScript
{
    PrepareAuraScript(spell_dh_shattered_souls);

    void HandleProc(AuraEffect const* /*aurEff*/, ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();
        Unit* target = eventInfo.GetActionTarget();
        if (!caster || !target)
            return;

        if (roll_chance_i(GetSpellInfo()->GetEffect(EFFECT_0).BasePoints))
        {
            uint32 triggerSpellId = GetSpellInfo()->Id == SPELL_DH_VENGEANCE_SHATTERED_SOUL ? SPELL_DH_SS_VENGEANCE_SOUL_NORMAL : SPELL_DH_SS_HAVOC_SOUL_NORMAL;
            if (Creature* creature = target->ToCreature())
                if (CreatureTemplate const* creTemplate = creature->GetCreatureTemplate())
                    if (creTemplate->type == CREATURE_TYPE_DEMON)
                        triggerSpellId = GetSpellInfo()->Id == SPELL_DH_VENGEANCE_SHATTERED_SOUL ? SPELL_DH_SS_VENGEANCE_SOUL_DEMON : SPELL_DH_SS_HAVOC_SOUL_DEMON;

           // caster->CastSpell(RAND(SPELL_DH_SHATTER_SOUL, SPELL_DH_SHATTER_SOUL_1, SPELL_DH_SHATTER_SOUL_2, SPELL_DH_SHATTER_SOUL_3), SpellValueMod(SPELLVALUE_TRIGGER_SPELL + EFFECT_1), triggerSpellId, caster);
        }
    }

    void Register() override
    {
       // OnEffectProc += AuraEffectProcFn(spell_dh_shattered_souls::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

// Blade Dance abilities - 188499
//Last Update 8.0.1 Build 28153
class spell_dh_blade_dance_first_target : public SpellScript
{
    PrepareSpellScript(spell_dh_blade_dance_first_target);

    void HandleDummy(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        if (caster->HasAura(SPELL_DH_FIRST_BLOOD))
            caster->Variables.Set<ObjectGuid>("FIRST_BLOOD_TARGET", target->GetGUID());
    }

    void Register() override
    {
        OnEffectLaunchTarget += SpellEffectFn(spell_dh_blade_dance_first_target::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

// Blade Dance damaging abilities - 199552, 200685, 210153, 210155
//Last Update 8.0.1 Build 28153
class spell_dh_blade_dance : public SpellScript
{
    PrepareSpellScript(spell_dh_blade_dance);

    enum BladeDance
    {
        DancingWithFate = 339228, // Conduit
    };

    void HandleOnHit(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        int32 dmg = GetHitDamage();
        if (caster->Variables.Exist("FIRST_BLOOD_TARGET"))
            if (AuraEffect* aurEff = caster->GetAuraEffect(SPELL_DH_FIRST_BLOOD, EFFECT_0))
                if (target->GetGUID() == caster->Variables.GetValue<ObjectGuid>("FIRST_BLOOD_TARGET"))
                    AddPct(dmg, aurEff->GetAmount());

        if (GetSpellInfo()->Id == SPELL_DH_BLADE_DANCE_LAST_HIT)
            if (auto aurEff = caster->GetAuraEffect(DancingWithFate, EFFECT_0))
                AddPct(dmg, aurEff->GetAmount());

        SetHitDamage(dmg);

        // Trail of ruin
        if (caster->HasAura(SPELL_DH_TRAIL_OF_RUIN) && GetSpellInfo()->Id == SPELL_DH_BLADE_DANCE_LAST_HIT)
            caster->CastSpell(target, SPELL_DH_TRAIL_OF_RUIN_DAMAGE, true);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_dh_blade_dance::HandleOnHit, EFFECT_1, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

// Nemesis - 206491
//class spell_dh_nemesis : public SpellScriptLoader
//{
//public:
//    spell_dh_nemesis() : SpellScriptLoader("spell_dh_nemesis") {}
//
//    class spell_dh_nemesis_AuraScript : public AuraScript
//    {
//        PrepareAuraScript(spell_dh_nemesis_AuraScript);
//
//        void HandleAfterRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
//        {
//            if (GetTargetApplication()->GetRemoveMode() != AURA_REMOVE_BY_DEATH)
//                return;
//
//            Unit* target = GetTargetApplication()->GetTarget();
//
//			if (!target)
//				return;
//
//            uint32 type = target->GetCreatureType();
//            int32 dur = GetTargetApplication()->GetBase()->GetDuration();
//            Unit* caster = GetAura()->GetCaster();
//
//			if (!caster)
//				return;
//
//            switch (type)
//            {
//                case CREATURE_TYPE_ABERRATION:
//                    caster->CastSpell(caster, NEMESIS_ABERRATION, NULL, NULL, NULL, true);
//                    if (Aura* nemesis = caster->GetAura(NEMESIS_ABERRATION))
//                        nemesis->SetDuration(dur);
//                    break;
//                case CREATURE_TYPE_BEAST:
//                    caster->CastSpell(caster, NEMESIS_BEASTS, NULL, NULL, NULL, true);
//                    if (Aura* nemesis = caster->GetAura(NEMESIS_BEASTS))
//                        nemesis->SetDuration(dur);
//                    break;
//                case CREATURE_TYPE_CRITTER:
//                    caster->CastSpell(caster, NEMESIS_CRITTERS, NULL, NULL, NULL, true);
//                    if (Aura* nemesis = caster->GetAura(NEMESIS_CRITTERS))
//                        nemesis->SetDuration(dur);
//                    break;
//                case CREATURE_TYPE_DEMON:
//                    caster->CastSpell(caster, NEMESIS_DEMONS, NULL, NULL, NULL, true);
//                    if (Aura* nemesis = caster->GetAura(NEMESIS_DEMONS))
//                        nemesis->SetDuration(dur);
//                    break;
//                case CREATURE_TYPE_DRAGONKIN:
//                    caster->CastSpell(caster, NEMESIS_DRAGONKIN, NULL, NULL, NULL, true);
//                    if (Aura* nemesis = caster->GetAura(NEMESIS_DRAGONKIN))
//                        nemesis->SetDuration(dur);
//                    break;
//                case CREATURE_TYPE_ELEMENTAL:
//                    caster->CastSpell(caster, NEMESIS_ELEMENTAL, NULL, NULL, NULL, true);
//                    if (Aura* nemesis = caster->GetAura(NEMESIS_ELEMENTAL))
//                        nemesis->SetDuration(dur);
//                    break;
//                case CREATURE_TYPE_GIANT:
//                    caster->CastSpell(caster, NEMESIS_GIANTS, NULL, NULL, NULL, true);
//                    if (Aura* nemesis = caster->GetAura(NEMESIS_GIANTS))
//                        nemesis->SetDuration(dur);
//                    break;
//                case CREATURE_TYPE_HUMANOID:
//                    caster->CastSpell(caster, NEMESIS_HUMANOID, NULL, NULL, NULL, true);
//                    if (Aura* nemesis = caster->GetAura(NEMESIS_HUMANOID))
//                        nemesis->SetDuration(dur);
//                    break;
//                case CREATURE_TYPE_MECHANICAL:
//                    caster->CastSpell(caster, NEMESIS_MECHANICAL, NULL, NULL, NULL, true);
//                    if (Aura* nemesis = caster->GetAura(NEMESIS_MECHANICAL))
//                        nemesis->SetDuration(dur);
//                    break;
//                case CREATURE_TYPE_UNDEAD:
//                    caster->CastSpell(caster, NEMESIS_UNDEAD, NULL, NULL, NULL, true);
//                    if (Aura* nemesis = caster->GetAura(NEMESIS_UNDEAD))
//                        nemesis->SetDuration(dur);
//                    break;
//                default:
//                    break;
//            }
//        }
//
//        void Register() override
//        {
//            AfterEffectRemove += AuraEffectRemoveFn(spell_dh_nemesis_AuraScript::HandleAfterRemove, EFFECT_0, 270, AURA_EFFECT_HANDLE_REAL);
//        }
//    };
//
//    AuraScript* GetAuraScript() const override
//    {
//        return new spell_dh_nemesis_AuraScript();
//    }
//};

// // Bloodlet - 206473
// class spell_dh_bloodlet : public SpellScriptLoader
// {
// public:
//     spell_dh_bloodlet() : SpellScriptLoader("spell_dh_bloodlet") {}
// 
//     class spell_dh_bloodlet_AuraScript : public AuraScript
//     {
//         PrepareAuraScript(spell_dh_bloodlet_AuraScript);
// 
//         bool CheckProc(ProcEventInfo& eventInfo)
//         {
//             if (eventInfo.GetSpellInfo()->Id == SPELL_DH_THROW_GLAIVE)
//                 return true;
//             return false;
//         }
// 
//         void HandleProc(AuraEffect const* /*aurEff*/, ProcEventInfo& eventInfo)
//         {
//             Unit* caster = GetCaster();
//             Unit* target = eventInfo.GetActionTarget();
//             int32 dmg = int32((eventInfo.GetDamageInfo()->GetDamage()*2)/5);
//             if (AuraEffect* dot = target->GetAuraEffect(SPELL_DH_BLOODLET_DOT, EFFECT_0, caster->GetGUID()))
//             {
//                 dmg += (dot->GetAmount() * (dot->GetTotalTicks() - dot->GetTickNumber())) / 5;
//             }
// 
//             caster->CastSpell(target, SPELL_DH_BLOODLET_DOT, &dmg, NULL, NULL, true);
//         }
// 
//         void Register() override
//         {
//             DoCheckProc += AuraCheckProcFn(spell_dh_bloodlet_AuraScript::CheckProc);
//             OnEffectProc += AuraEffectProcFn(spell_dh_bloodlet_AuraScript::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
//         }
//     };
// 
//     AuraScript* GetAuraScript() const override
//     {
//         return new spell_dh_bloodlet_AuraScript();
//     }
// };

// Demon Blades - 203555
class spell_dh_demon_blades : public SpellScriptLoader
{
public:
    spell_dh_demon_blades() : SpellScriptLoader("spell_dh_demon_blades") {}

    class spell_dh_demon_blades_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_dh_demon_blades_AuraScript);

        void HandleProc(AuraEffect const* /*aurEff*/, ProcEventInfo& eventInfo)
        {
            Unit* caster = GetCaster();
            Unit* target = eventInfo.GetActionTarget();

            if(roll_chance_i(sSpellMgr->GetSpellInfo(SPELL_DH_DEMON_BLADES)->GetEffect(EFFECT_0).BasePoints))
                caster->CastSpell(target, SPELL_DH_DEMON_BLADES_TRIGGER, true);
        }

        void Register() override
        {
           // OnEffectProc += AuraEffectProcFn(spell_dh_demon_blades_AuraScript::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_dh_demon_blades_AuraScript();
    }
};

// Fel Barrage - 211053
class spell_dh_fel_barrage : public SpellScriptLoader
{
public:
    spell_dh_fel_barrage() : SpellScriptLoader("spell_dh_fel_barrage") {}

    class spell_dh_fel_barrage_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_dh_fel_barrage_AuraScript);

    public:

        spell_dh_fel_barrage_AuraScript()
        {
            _charges = 1;
        }

    private:

        int32 _charges;

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_DH_FEL_BARRAGE) ||
                !sSpellMgr->GetSpellInfo(SPELL_DH_FEL_BARRAGE_TRIGGER))
                return false;
            return true;
        }

        bool Load() override
        {
            _charges = GetCaster()->GetSpellHistory()->GetChargeCount(sSpellMgr->GetSpellInfo(SPELL_DH_FEL_BARRAGE)->ChargeCategoryId);
            return true;
        }

        void HandleTrigger(AuraEffect const* /*aurEff*/)
        {
            GetCaster()->CastSpell(GetTarget(), SPELL_DH_FEL_BARRAGE_TRIGGER, true);
        }

        void Register() override
        {
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_dh_fel_barrage_AuraScript::HandleTrigger, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_dh_fel_barrage_AuraScript();
    }
};

// Fel Barrage Damage - 211052
class spell_dh_fel_barrage_damage : public SpellScriptLoader
{
public:
    spell_dh_fel_barrage_damage() : SpellScriptLoader("spell_dh_fel_barrage_damage") {}

    class spell_dh_fel_barrage_damage_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_dh_fel_barrage_damage_SpellScript);

        void HandleHit(SpellEffIndex /*effIndex*/)
        {
            int32 chargesUsed = GetSpellValue()->EffectBasePoints[0];
            int32 dmg = GetHitDamage();
            SetHitDamage((dmg*chargesUsed)/5);
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_dh_fel_barrage_damage_SpellScript::HandleHit, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_dh_fel_barrage_damage_SpellScript();
    }
};

// Fel Barrage aura - 222703
class spell_dh_fel_barrage_aura : public SpellScriptLoader
{
public:
    spell_dh_fel_barrage_aura() : SpellScriptLoader("spell_dh_fel_barrage_aura") {}

    class spell_dh_fel_barrage_aura_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_dh_fel_barrage_aura_AuraScript);

        bool CheckProc(ProcEventInfo& eventInfo)
        {
            // Blade Dance, Chaos Strike and Annihilation have many damagers,
            // so we accept only 1 of those, and we remove the others
            // Also we remove fel barrage itself too.
            std::vector<uint32> removeSpellIds{ 199552, 210153, 222031, 227518, 211052, 198030 };
            return std::find(removeSpellIds.begin(), removeSpellIds.end(), eventInfo.GetSpellInfo()->Id) == removeSpellIds.end();
        }

        void HandleProc(AuraEffect const* /*aurEff*/, ProcEventInfo& /*eventInfo*/)
        {
            PreventDefaultAction();

            Unit* caster = GetCaster();
            if (!caster)
                return;

            int32 chargeCatId = sSpellMgr->GetSpellInfo(SPELL_DH_FEL_BARRAGE)->ChargeCategoryId;
            if (SpellCategoryEntry const* barrage = sSpellCategoryStore.LookupEntry(chargeCatId))
            {
                caster->GetSpellHistory()->RestoreCharge(chargeCatId);
                caster->GetSpellHistory()->ForceSendSetSpellCharges(barrage);
            }
        }

        void Register() override
        {
            DoCheckProc += AuraCheckProcFn(spell_dh_fel_barrage_aura_AuraScript::CheckProc);
            //OnEffectProc += AuraEffectProcFn(spell_dh_fel_barrage_aura_AuraScript::HandleProc, EFFECT_0, SPELL_AURA_PROC_TRIGGER_SPELL);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_dh_fel_barrage_aura_AuraScript();
    }
};

// Annihilation - 201427
//Last Update 8.0.1 Build 28153
class spell_dh_annihilation : public SpellScriptLoader
{
public:
    spell_dh_annihilation() : SpellScriptLoader("spell_dh_annihilation") {}

    class spell_dh_annihilation_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_dh_annihilation_SpellScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_DH_ANNIHILATION) ||
                !sSpellMgr->GetSpellInfo(SPELL_DH_ANNIHILATION_MAINHAIND) ||
                !sSpellMgr->GetSpellInfo(SPELL_DH_ANNIHILATION_OFFHAND))
                return false;
            return true;
        }

        void PreventMainhandEffect(SpellEffIndex /*effIndex*/)
        {
            Unit* caster = GetCaster();
            Unit* target = GetExplTargetUnit();
            if (!caster || !target)
                return;

            caster->CastSpell(target, SPELL_DH_ANNIHILATION_MAINHAIND, true);

            // Trail of ruin
            if (caster->HasAura(SPELL_DH_TRAIL_OF_RUIN))
                caster->CastSpell(target, SPELL_DH_TRAIL_OF_RUIN_DAMAGE, true);
        }

        void PreventOffhandEffect(SpellEffIndex /*effIndex*/)
        {
            Unit* caster = GetCaster();
            Unit* target = GetExplTargetUnit();
            if (!caster || !target)
                return;

            caster->CastSpell(target, SPELL_DH_ANNIHILATION_OFFHAND, true);
        }

        void Register() override
        {
            OnEffectHit += SpellEffectFn(spell_dh_annihilation_SpellScript::PreventMainhandEffect, EFFECT_1, SPELL_EFFECT_TRIGGER_SPELL);
            OnEffectHit += SpellEffectFn(spell_dh_annihilation_SpellScript::PreventOffhandEffect, EFFECT_2, SPELL_EFFECT_TRIGGER_SPELL);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_dh_annihilation_SpellScript();
    }
};

// Annihilation mainhand damge and offhand damage - 201428, 227518
class spell_dh_annihilation_damage : public SpellScriptLoader
{
public:
    spell_dh_annihilation_damage() : SpellScriptLoader("spell_dh_annihilation_damage") {}

    class spell_dh_annihilation_damage_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_dh_annihilation_damage_SpellScript);

        void HandleHit(SpellEffIndex /*effIndex*/)
        {
            Unit* caster = GetCaster();
            Unit* target = GetHitUnit();

            if (caster == target)
                PreventHitDamage();
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_dh_annihilation_damage_SpellScript::HandleHit, EFFECT_0, SPELL_EFFECT_NORMALIZED_WEAPON_DMG);
            OnEffectHitTarget += SpellEffectFn(spell_dh_annihilation_damage_SpellScript::HandleHit, EFFECT_1, SPELL_EFFECT_WEAPON_DAMAGE);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_dh_annihilation_damage_SpellScript();
    }
};

// Fel Eruption - 211881
class spell_dh_fel_eruption : public SpellScriptLoader
{
public:
    spell_dh_fel_eruption() : SpellScriptLoader("spell_dh_fel_eruption") {}

    class spell_dh_fel_eruption_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_dh_fel_eruption_SpellScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            return ValidateSpellInfo({ SPELL_DH_FEL_ERUPTION, SPELL_DH_FEL_ERUPTION_DAMAGE });
        }

        void HandleOnHit(SpellEffIndex /*effIndex*/)
        {
            Unit* caster = GetCaster();
            Unit* target = GetExplTargetUnit();

            caster->CastSpell(target, SPELL_DH_FEL_ERUPTION_DAMAGE, true);
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_dh_fel_eruption_SpellScript::HandleOnHit, EFFECT_0, SPELL_EFFECT_APPLY_AURA);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_dh_fel_eruption_SpellScript();
    }
};

// Immolation aura - 258920 
class spell_dh_immolation_aura : public SpellScriptLoader
{
public:
    spell_dh_immolation_aura() : SpellScriptLoader("spell_dh_immolation_aura") {}

    class spell_dh_immolation_aura_AuraScript : public AuraScript
    {
        enum ImmoAura
        {
            UnboundChaos = 347461,
            UnboundChaosProc = 347462,
        };

        PrepareAuraScript(spell_dh_immolation_aura_AuraScript);

        void HandlePeriodic(AuraEffect const* /*aurEff*/)
        {
            if (Unit* caster = GetCaster())
            {
                caster->Variables.Set("ImmolationAuraTicks", caster->Variables.GetValue("ImmolationAuraTicks", 0) + 1);
            }
        }
        void HandleApply(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /* mode */)
        {
            Unit* caster = GetCaster();
            if (!caster)
                return;

            if (caster->HasAura(UnboundChaos))
                caster->CastSpell(caster, UnboundChaosProc, true);

            caster->CastSpell(caster, 258921, true); ///< DH Immo aura inital DMG
            caster->CastSpell(caster, SPELL_DH_IMMOLATION_AURA_VISUAL, true);

            if (Aura* imm = caster->GetAura(SPELL_DH_IMMOLATION_AURA_VISUAL))
            {
                imm->SetDuration(6000); //it's 10 seconds otherwise.
                caster->RemoveVisibleAura(imm->GetApplicationOfTarget(caster->GetGUID()));
            }
        }

        void HandleRemove(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /* mode */)
        {
            if (Unit* caster = GetCaster())
                caster->Variables.Remove("ImmolationAuraTicks");
        }
        void Register() override
        {
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_dh_immolation_aura_AuraScript::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
            OnEffectApply += AuraEffectApplyFn(spell_dh_immolation_aura_AuraScript::HandleApply, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
            OnEffectRemove += AuraEffectRemoveFn(spell_dh_immolation_aura_AuraScript::HandleRemove, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_dh_immolation_aura_AuraScript();
    }
};

// 258922
class spell_dh_immolation_aura_dmg : public SpellScript
{
    PrepareSpellScript(spell_dh_immolation_aura_dmg);

    enum ImmoAura
    {
        GrowingInferno = 339231,
    };

    void OnHit(SpellEffIndex /*effIndex*/)
    {
        auto hitDmg = GetHitDamage();

        if (auto growingInferno = GetCaster()->GetAuraEffect(GrowingInferno, EFFECT_0))
            AddPct(hitDmg, growingInferno->GetAmount() * GetCaster()->Variables.GetValue("ImmolationAuraTicks", 1));

        SetHitDamage(hitDmg);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_dh_immolation_aura_dmg::OnHit, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

// 198813 - Vengeful retreat trigger
class spell_dh_vengeful_retreat_trigger : public SpellScript
{
    PrepareSpellScript(spell_dh_vengeful_retreat_trigger);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        if (!sSpellMgr->GetSpellInfo(SPELL_DH_VENGEFUL_RETREAT) ||
            !sSpellMgr->GetSpellInfo(SPELL_DH_VENGEFUL_RETREAT_FURY))
            return false;
        return true;
    }

    void HandleOnHit(SpellEffIndex /*effIndex*/)
    {
        if (Unit* caster = GetCaster())
            if (caster->HasAura(SPELL_DH_MOMENTUM) && !momentum)
            {
                caster->CastSpell(caster, SPELL_DH_PREPARED_ENERGIZE, true);
                momentum = true;
                caster->Variables.Set<bool>("MOMENTUM", true);
            }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_dh_vengeful_retreat_trigger::HandleOnHit, EFFECT_1, SPELL_EFFECT_SCHOOL_DAMAGE);
    }

private:
    bool momentum = false;
};

// Prepare refiller - 203650
class spell_dh_vengeful_retreat_fury_refiller : public SpellScriptLoader
{
public:
    spell_dh_vengeful_retreat_fury_refiller() : SpellScriptLoader("spell_dh_vengeful_retreat_fury_refiller") {}

    class spell_dh_vengeful_retreat_fury_refiller_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_dh_vengeful_retreat_fury_refiller_AuraScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_DH_VENGEFUL_RETREAT_FURY))
                return false;
            return true;
        }

        void Energize(AuraEffect const* /*aurEff*/)
        {
            PreventDefaultAction();

            Unit* caster = GetCaster();
            int32 fury = caster->GetPower(POWER_FURY);

            if (fury + 4 < caster->GetMaxPower(POWER_FURY))
            {
                caster->SetPower(POWER_FURY, fury + 4);
            }
            else
            {
                caster->SetPower(POWER_FURY, caster->GetMaxPower(POWER_FURY));
            }
        }

        void Register() override
        {
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_dh_vengeful_retreat_fury_refiller_AuraScript::Energize, EFFECT_0, SPELL_AURA_PERIODIC_ENERGIZE);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_dh_vengeful_retreat_fury_refiller_AuraScript();
    }
};

// 203720 - Demon Spikes
class spell_dh_demon_spikes : public SpellScript
{
	PrepareSpellScript(spell_dh_demon_spikes);

	bool Validate(SpellInfo const* /*spellInfo*/) override
	{
		if (!sSpellMgr->GetSpellInfo(SPELL_DH_DEMON_SPIKES) ||
			!sSpellMgr->GetSpellInfo(SPELL_DH_DEMON_SPIKES_BUFF))
			return false;
		return true;
	}

	void HandleOnHit(SpellEffIndex /*effIndex*/)
	{
		Unit* caster = GetCaster();
		if (!caster)
			return;

		if (!caster->ToPlayer())
			return;
		caster->CastSpell(caster, SPELL_DH_DEMON_SPIKES_BUFF, true);

       //if (AuraEffect* auraEff = caster->GetAuraEffect(SPELL_DH_RIGID_CARAPACE_POWER, EFFECT_0))
       //    caster->CastSpell(SPELL_DH_RIGID_CARAPACE_BUFF, SPELLVALUE_BASE_POINT0, auraEff->GetAmount(), caster);
	}

	void Register() override
	{
		OnEffectHitTarget += SpellEffectFn(spell_dh_demon_spikes::HandleOnHit, EFFECT_0, SPELL_EFFECT_DUMMY);
	}
};

// 203819 - Demon Spikes buff
class spell_dh_demon_spikes_buff : public AuraScript
{
	PrepareAuraScript(spell_dh_demon_spikes_buff);

	void HandleApply(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /* mode */)
	{
		if (Unit* caster = GetCaster())
			if (caster->HasAura(SPELL_DH_JAGGED_SPIKES))
				caster->CastSpell(caster, SPELL_DH_JAGGED_SPIKES_AURA, true);
	}

	void HandleRemove(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /* mode */)
	{
		if (Unit* caster = GetCaster())
			caster->RemoveAura(SPELL_DH_JAGGED_SPIKES_AURA);
	}

	void Register() override
	{
		OnEffectApply += AuraEffectApplyFn(spell_dh_demon_spikes_buff::HandleApply, EFFECT_0, SPELL_AURA_MOD_PARRY_PERCENT, AURA_EFFECT_HANDLE_REAL);
		OnEffectRemove += AuraEffectRemoveFn(spell_dh_demon_spikes_buff::HandleRemove, EFFECT_0, SPELL_AURA_MOD_PARRY_PERCENT, AURA_EFFECT_HANDLE_REAL);
	}
};

// Fel Mastery - 192939
class spell_dh_fel_mastery : public SpellScriptLoader
{
public:
    spell_dh_fel_mastery() : SpellScriptLoader("spell_dh_fel_mastery") {}

    class spell_dh_fel_mastery_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_dh_fel_mastery_AuraScript);

        bool CheckProc(ProcEventInfo& eventInfo)
        {
            return (eventInfo.GetSpellInfo()->Id == SPELL_DH_FEL_RUSH_DAMAGE);
        }

        void HandleProc(AuraEffect const* /*aurEff*/, ProcEventInfo& /*eventInfo*/)
        {
            Unit* caster = GetCaster();
            if (!caster)
                return;

            if (Player* player = caster->ToPlayer())
            {
                int32 fury = caster->GetPower(POWER_FURY);
                int32 amountToAdd = GetSpellInfo()->GetEffect(EFFECT_0).BasePoints;
                if (fury + amountToAdd < caster->GetMaxPower(POWER_FURY))
                    caster->SetPower(POWER_FURY, fury + amountToAdd);
                else
                    caster->SetPower(POWER_FURY, caster->GetMaxPower(POWER_FURY));

                player->SetPower(POWER_FURY, caster->GetPower(POWER_FURY));
            }

        }

        void Register() override
        {
            DoCheckProc += AuraCheckProcFn(spell_dh_fel_mastery_AuraScript::CheckProc);
          //  OnEffectProc += AuraEffectProcFn(spell_dh_fel_mastery_AuraScript::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_dh_fel_mastery_AuraScript();
    }
};

// Fel Rush air - 197923
//Last Update 8.0.1 Build 28153
class spell_dh_fel_rush_dash : public SpellScriptLoader
{
public:
    spell_dh_fel_rush_dash() : SpellScriptLoader("spell_dh_fel_rush_dash") {}

    class spell_dh_fel_rush_dash_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_dh_fel_rush_dash_AuraScript);

        void AfterRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if (Unit* caster = GetCaster())
                caster->GetScheduler().Schedule(100ms, [](TaskContext context)
                {
                    if (!context.GetUnit()->HasAura(SPELL_DH_FEL_RUSH_AIR))
                        context.GetUnit()->SetDisableGravity(false);
                });
        }

        void CalcSpeed(AuraEffect const* /*aurEff*/, int32& amount, bool& /*canBeRecalculated*/)
        {
            amount = 1250;
            RefreshDuration();
        }

        void Register() override
        {
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_dh_fel_rush_dash_AuraScript::CalcSpeed, EFFECT_1, SPELL_AURA_MOD_SPEED_NO_CONTROL);
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_dh_fel_rush_dash_AuraScript::CalcSpeed, EFFECT_3, SPELL_AURA_MOD_MINIMUM_SPEED);
            AfterEffectRemove += AuraEffectRemoveFn(spell_dh_fel_rush_dash_AuraScript::AfterRemove, EFFECT_9, SPELL_AURA_MOD_MINIMUM_SPEED_RATE, AURA_EFFECT_HANDLE_SEND_FOR_CLIENT_MASK);
        }
    };

    class spell_dh_fel_rush_dash_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_dh_fel_rush_dash_SpellScript);

        void PreventTrigger(SpellEffIndex effIndex)
        {
            PreventHitEffect(effIndex);
        }

        void Register() override
        {
            OnEffectLaunch += SpellEffectFn(spell_dh_fel_rush_dash_SpellScript::PreventTrigger, EFFECT_6, SPELL_EFFECT_TRIGGER_SPELL);
            OnEffectHit += SpellEffectFn(spell_dh_fel_rush_dash_SpellScript::PreventTrigger, EFFECT_6, SPELL_EFFECT_TRIGGER_SPELL);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_dh_fel_rush_dash_AuraScript();
    }

    SpellScript* GetSpellScript() const override
    {
        return new spell_dh_fel_rush_dash_SpellScript();
    }
};

void CastFelRushDmg(Unit* unitCaster)
{
    float x, y, z, o;
    float srcX, srcY, srcZ;
    float zSearchDist = 20.0f; // Falling case
    float ground = 0.0f;
    unitCaster->GetSafePosition(x, y, z);
    unitCaster->GetSafePosition(srcX, srcY, srcZ);
    o = unitCaster->GetOrientation();

    float dis = 20.0f;

    float waterLevel = unitCaster->GetTransport() ? VMAP_INVALID_HEIGHT_VALUE : unitCaster->GetMap()->GetWaterOrGroundLevel(unitCaster->GetPhaseShift(), x, y, z, &ground);
    x += dis * std::cos(o);
    y += dis * std::sin(o);
    // Underwater blink case
    if (waterLevel != VMAP_INVALID_HEIGHT_VALUE && waterLevel > ground)
    {
        if (z < ground)
            z = ground;
        // If blinking up to the surface, limit z position (do not teleport out of water)
        if (z > waterLevel && (z - srcZ) > 1.0f)
        {
            float t = (waterLevel - srcZ) / (z - srcZ);
            x = (x - srcX) * t + srcX;
            y = (y - srcY) * t + srcY;
            z = waterLevel;
        }
        unitCaster->GetMap()->GetLosHitPosition(unitCaster->GetPhaseShift(), srcX, srcY, srcZ, x, y, z, -0.5f);
        ground = unitCaster->GetMap()->GetHeight(unitCaster->GetPhaseShift(), x, y, z);
        waterLevel = unitCaster->GetMap()->GetWaterOrGroundLevel(unitCaster->GetPhaseShift(), x, y, z, &ground);

        if (ground != VMAP_INVALID_HEIGHT_VALUE && waterLevel != VMAP_INVALID_HEIGHT_VALUE && ground < z)
        {
            unitCaster->CastSpell(Position(x, y, z, o), SPELL_DH_FEL_RUSH_DAMAGE, true);
            return;
        }
        // If we are leaving water, rather use pathfinding, but increase z-range position research.
        zSearchDist = 20.0f;
    }

    if (!unitCaster->GetMap()->GetWalkHitPosition(unitCaster->GetPhaseShift(), unitCaster->GetTransport(), srcX, srcY, srcZ, x, y, z, NAV_GROUND | NAV_WATER, zSearchDist, false))
    {
        x = srcX;
        y = srcY;
        z = srcZ;
    }

    unitCaster->CastSpell(Position(x, y, z, o), SPELL_DH_FEL_RUSH_DAMAGE, true);
}

// Fel Rush - 195072
//Last Update 8.0.1 Build 28153
class spell_dh_fel_rush : public SpellScriptLoader
{
public:
    spell_dh_fel_rush() : SpellScriptLoader("spell_dh_fel_rush") {}

    class spell_dh_fel_rush_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_dh_fel_rush_SpellScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            return ValidateSpellInfo({ SPELL_DH_FEL_RUSH_DASH, SPELL_DH_FEL_RUSH_AIR });
        }

        enum Extra
        {
            AuraFelfireHaste = 338799,
            FelfireHasteProc = 338804,
        };

        void HandleDashGround(SpellEffIndex /*effIndex*/)
        {
            if (Unit* caster = GetCaster())
            {
                if (!caster->IsFalling() || caster->IsInWater())
                {
                  //  caster->CastSpell(caster, SPELL_DH_FEL_RUSH_DASH, true);
                    CastFelRushDmg(caster);
                }
                if (caster->HasAura(SPELL_DH_MOMENTUM))
                    caster->CastSpell(caster, SPELL_DH_MOMENTUM_BUFF, true);
                if (auto aura1 = caster->GetAura(AuraFelfireHaste))
                    if (auto aura = caster->AddAura(FelfireHasteProc))
                        aura->GetEffect(0)->SetAmount(aura1->GetEffect(0)->GetAmount());
            }
        }

        void HandleDashAir(SpellEffIndex /*effIndex*/)
        {
            if (Unit* caster = GetCaster())
                if (caster->IsFalling())
                {
                   // caster->SetDisableGravity(true);
                  //  caster->CastSpell(caster, SPELL_DH_FEL_RUSH_AIR, true);
                    CastFelRushDmg(caster);
                }
        }

        void HandleBeforeStartCast()
        {
            if (Unit* caster = GetCaster())
            {
                if (caster->HasUnitMovementFlag(MOVEMENTFLAG_FALLING))
                {
                    caster->CastSpell(caster, SPELL_DH_FEL_RUSH_AIR, true);
                }
                else
                {
                    caster->CastSpell(caster, SPELL_DH_FEL_RUSH_DASH, true);
                }
            }
        }


        void Register() override
        {
            BeforeCast += SpellCastFn(spell_dh_fel_rush_SpellScript::HandleBeforeStartCast);
            OnEffectHitTarget += SpellEffectFn(spell_dh_fel_rush_SpellScript::HandleDashGround, EFFECT_0, SPELL_EFFECT_DUMMY);
            OnEffectHitTarget += SpellEffectFn(spell_dh_fel_rush_SpellScript::HandleDashAir, EFFECT_1, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_dh_fel_rush_SpellScript();
    }
};

// Metamorphosis (vengeance) buffs - 187827
class spell_dh_metamorphosis_buffs_veng : public SpellScriptLoader
{
public:
    spell_dh_metamorphosis_buffs_veng() : SpellScriptLoader("spell_dh_metamorphosis_buffs_veng") {}

    class spell_dh_metamorphosis_buffs_veng_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_dh_metamorphosis_buffs_veng_AuraScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_DH_METAMORPHOSIS))
                return false;
            return true;
        }

        void CalcLeech(AuraEffect const* /*aurEff*/, int32& amount, bool& /*canBeRecalculated*/)
        {
            Unit* caster = GetCaster();
            if (!caster)
                return;

            if (caster->HasAura(SPELL_DH_SOUL_RENDING_VENGEANCE))
                amount += 50;
        }

        void Register() override
        {
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_dh_metamorphosis_buffs_veng_AuraScript::CalcLeech, EFFECT_2, SPELL_AURA_MOD_LEECH);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_dh_metamorphosis_buffs_veng_AuraScript();
    }
};

// Metamorphosis - 191427
class spell_dh_metamorphosis : public SpellScriptLoader
{
public:
    spell_dh_metamorphosis() : SpellScriptLoader("spell_dh_metamorphosis") {}

    class spell_dh_metamorphosis_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_dh_metamorphosis_SpellScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_DH_METAMORPHOSIS) ||
                !sSpellMgr->GetSpellInfo(SPELL_DH_METAMORPHOSIS_BUFFS) ||
                !sSpellMgr->GetSpellInfo(SPELL_DH_METAMORPHOSIS_LEAP) ||
                !sSpellMgr->GetSpellInfo(SPELL_DH_METAMORPHOSIS_STUN))
                return false;
            return true;
        }

        void HandleDummy()
        {
            Unit* caster = GetCaster();
            if (!caster)
                return;

            Player* player = caster->ToPlayer();
            if (!player)
                return;

            if (const WorldLocation* dest = GetExplTargetDest())
            {
                player->CastSpell(*dest, SPELL_DH_METAMORPHOSIS_LEAP, false);
            }

            player->GetSpellHistory()->ResetCooldown(SPELL_DH_EYE_BEAM, true);
            player->GetSpellHistory()->ResetCooldown(SPELL_DH_BLADE_DANCE, true);
        }

        void Register() override
        {
            BeforeCast += SpellCastFn(spell_dh_metamorphosis_SpellScript::HandleDummy);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_dh_metamorphosis_SpellScript();
    }
};

// Metamorphosis temporary immunity - 201453
class spell_dh_metamorphosis_immunity : public SpellScript
{
    PrepareSpellScript(spell_dh_metamorphosis_immunity);

    void PreventImmunity(SpellEffIndex effIndex)
    {
        if (Unit* caster = GetCaster())
            if (Player* player = GetCaster()->ToPlayer())
                if (player->GetSpecializationId() == TALENT_SPEC_DEMON_HUNTER_VENGEANCE)
                    PreventHitEffect(effIndex);
    }

    void Register() override
    {
        OnEffectLaunch += SpellEffectFn(spell_dh_metamorphosis_immunity::PreventImmunity, EFFECT_1, SPELL_AURA_SCHOOL_IMMUNITY);
        OnEffectHit    += SpellEffectFn(spell_dh_metamorphosis_immunity::PreventImmunity, EFFECT_1, SPELL_AURA_SCHOOL_IMMUNITY);
    }
};

// Metamorphosis temporary immunity - 201453
class aura_dh_metamorphosis_immunity : public AuraScript
{
    PrepareAuraScript(aura_dh_metamorphosis_immunity);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_DH_METAMORPHOSIS });
    }

    void HandleApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* caster = GetCaster())
            if (Player* player = GetCaster()->ToPlayer())
                if (player->GetSpecializationId() == TALENT_SPEC_DEMON_HUNTER_VENGEANCE)
                GetAura()->SetDuration(750);
    }

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Unit* caster = GetCaster();
        if (!caster)
            return;

        if (Unit* caster = GetCaster())
        {
            if (Player* player = GetCaster()->ToPlayer())
            {
                if (player->GetSpecializationId() == TALENT_SPEC_DEMON_HUNTER_HAVOC)
                {
                    caster->CastSpell(caster, SPELL_DH_METAMORPHOSIS_STUN, true);
                }
            }
        }
    }

    void Register() override
    {
        AfterEffectApply += AuraEffectApplyFn(aura_dh_metamorphosis_immunity::HandleApply, EFFECT_1, SPELL_AURA_DISABLE_CASTING_EXCEPT_ABILITIES, AURA_EFFECT_HANDLE_REAL);
        OnEffectRemove += AuraEffectRemoveFn(aura_dh_metamorphosis_immunity::HandleRemove, EFFECT_1, SPELL_AURA_DISABLE_CASTING_EXCEPT_ABILITIES, AURA_EFFECT_HANDLE_REAL);
    }
};

// Eye Beam - 198013
class spell_dh_eye_beam : public SpellScriptLoader
{
public:
    spell_dh_eye_beam() : SpellScriptLoader("spell_dh_eye_beam") {}

    class spell_dh_eye_beam_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_dh_eye_beam_AuraScript);

        bool firstTick = true;

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_DH_EYE_BEAM) ||
                !sSpellMgr->GetSpellInfo(SPELL_DH_EYE_BEAM_DAMAGE))
                return false;
            return true;
        }

        void HandlePeriodic(AuraEffect const* /*aurEff*/)
        {
            if (Unit* caster = GetCaster())
            {
                if (!firstTick)
                {
                    caster->CastSpell(caster, SPELL_DH_EYE_BEAM_DAMAGE, true);
                    if (int32 energize = caster->GetAuraEffectAmount(SPELL_DH_BLIND_FURY, EFFECT_2))
                        caster->ModifyPower(POWER_FURY, energize * 2.f / 50.f);
                }
            }

            firstTick = false;
        }

        void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if (Unit* caster = GetCaster())
            {
                caster->RemoveAurasDueToSpell(SPELL_DH_EYE_BEAM_VISUAL);
            }
        }

        enum EyeB
        {
            DarkglareMedallion = 322832, // torghast power i guess
            DarkglareBoon = 337534,
            DarkglareBoonEnergize = 350726,
        };

        void HandleApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if (Unit* caster = GetCaster())
            {
                //if (!caster->HasAura(SPELL_DH_DEMONIC))
                 //   caster->CastSpell(caster, SPELL_DH_EYE_BEAM_VISUAL, true);
                if (caster->HasAura(DarkglareMedallion) && roll_chance_i(20))
                    caster->GetSpellHistory()->ResetCooldown(SPELL_DH_EYE_BEAM, true);

                if (caster->HasAura(DarkglareBoon) && roll_chance_i(40))
                {
                    caster->GetSpellHistory()->ResetCooldown(SPELL_DH_EYE_BEAM, true);
                    caster->CastSpell(caster, DarkglareBoonEnergize, true);
                }
            }
        }

        void ModDuration(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
        {
            const_cast<AuraEffect*>(aurEff)->SetAmount(-95);
        }

        void Register() override
        {
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_dh_eye_beam_AuraScript::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
            OnEffectRemove += AuraEffectRemoveFn(spell_dh_eye_beam_AuraScript::HandleRemove, EFFECT_2, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            OnEffectApply += AuraEffectApplyFn(spell_dh_eye_beam_AuraScript::HandleApply, EFFECT_2, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            OnEffectApply += AuraEffectApplyFn(spell_dh_eye_beam_AuraScript::ModDuration, EFFECT_1, SPELL_AURA_MOD_DECREASE_SPEED, AURA_EFFECT_HANDLE_REAL);
        }
    };

    class spell_dh_eye_beam_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_dh_eye_beam_SpellScript);

        void HandleBeforeCast()
        {
            if (Unit* caster = GetCaster())
            {
                /// so for the animation, seems i can't fix it... - retail has packets as CMSG_CAST_SPELL - SMSG_AURA_UPDATE, SMSG_SPELL_START, SMSG_SPELL_GO
                // we don't sent the packets like that.. SMSG_AURA_UPDATE is sent after spel go so maybe that fixes it. but would require system updates.
                if (caster->HasAura(SPELL_DH_DEMONIC))
                {
                    caster->CastSpell(caster, SPELL_DH_METAMORPHOSIS_HAVOC, CastSpellExtraArgs(true).AddSpellMod(SpellValueMod::SPELLVALUE_DURATION, 6000));
                }
            }
        }

        void Register() override
        {
            BeforeCast += SpellCastFn(spell_dh_eye_beam_SpellScript::HandleBeforeCast);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_dh_eye_beam_AuraScript();
    }

    SpellScript* GetSpellScript() const override
    {
        return new spell_dh_eye_beam_SpellScript();
    }
};

// Eye Beam Trigger - 197640
class spell_dh_eye_beam_trigger : public SpellScriptLoader
{
public:
    spell_dh_eye_beam_trigger() : SpellScriptLoader("spell_dh_eye_beam_trigger") {}

    class spell_dh_eye_beam_trigger_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_dh_eye_beam_trigger_SpellScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_DH_EYE_BEAM) ||
                !sSpellMgr->GetSpellInfo(SPELL_DH_EYE_BEAM_DAMAGE))
                return false;
            return true;
        }

        void PreventHit(SpellEffIndex /*effIndex*/)
        {
            PreventHitDamage();
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_dh_eye_beam_trigger_SpellScript::PreventHit, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_dh_eye_beam_trigger_SpellScript();
    }
};

// Master of the Glaive - 203556
class spell_dh_master_of_the_glaive : public SpellScriptLoader
{
public:
    spell_dh_master_of_the_glaive() : SpellScriptLoader("spell_dh_master_of_the_glaive") {}

    class spell_dh_master_of_the_glaive_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_dh_master_of_the_glaive_AuraScript);

        bool CheckProc(ProcEventInfo& eventInfo)
        {
            if (eventInfo.GetSpellInfo()->Id == SPELL_DH_THROW_GLAIVE)
                return true;
            return false;
        }

        void Register() override
        {
            DoCheckProc += AuraCheckProcFn(spell_dh_master_of_the_glaive_AuraScript::CheckProc);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_dh_master_of_the_glaive_AuraScript();
    }
};

// npc 999999
/// TODO: move this to scripts/World when they will be compiled
// class npc_dh_spell_trainer : public CreatureScript
// {
// public:
//     npc_dh_spell_trainer() : CreatureScript("npc_dh_spell_trainer") {}
// 
//     bool OnGossipHello(Player* player, Creature* creature) override
//     {
//         if (player->GetUInt32Value(PLAYER_FIELD_CURRENT_SPEC_ID) != TALENT_SPEC_DEMON_HUNTER_HAVOC)
//             return false;
//         if (player->getLevel() < 99)
//             return false;
//         AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Teach me!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
//         AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Close", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
//         SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
//         return true;
//     }
// 
//     bool OnGossipSelect(Player* player, Creature* /*creature*/, uint32 /*sender*/, uint32 action) override
//     {
//         player->PlayerTalkClass->ClearMenus();
// 
//         std::vector<int32> spellIds
//         {
//             SPELL_DH_CHAOS_NOVA, SPELL_DH_CONSUME_MAGIC, SPELL_DH_THROW_GLAIVE, SPELL_DH_METAMORPHOSIS,
//             SPELL_DH_EYE_BEAM, SPELL_DH_BLUR, SPELL_DH_VENGEFUL_RETREAT, SPELL_DH_SIGIL_OF_FLAME
//         };
// 
//         switch (action)
//         {
//             case GOSSIP_ACTION_INFO_DEF + 1:
//                 for (auto spell : spellIds)
//                 {
//                     if (sSpellMgr->GetSpellInfo(spell) && !player->HasSpell(spell))
//                         player->LearnSpell(spell, false);
//                 }
//                 CloseGossipMenuFor(player);
//                 break;
//             case GOSSIP_ACTION_INFO_DEF + 2:
//                 CloseGossipMenuFor(player);
//                 break;
//         }
//         return true;
//     }
// };

// 197125 - Chaos Strike
//class spell_dh_chaos_strike : public SpellScriptLoader
//{
//public:
//    spell_dh_chaos_strike() : SpellScriptLoader("spell_dh_chaos_strike") { }
//
//    class spell_dh_chaos_strike_AuraScript : public AuraScript
//    {
//        PrepareAuraScript(spell_dh_chaos_strike_AuraScript);
//
//        bool Validate(SpellInfo const* /*spellInfo*/) override
//        {
//            return ValidateSpellInfo({ SPELL_DH_CHAOS_STRIKE_PROC });
//        }
//
//		bool CheckProc(ProcEventInfo& eventInfo)
//        {
//			if (eventInfo.GetSpellInfo() && (eventInfo.GetSpellInfo()->Id == SPELL_DH_CHAOS_STRIKE || eventInfo.GetSpellInfo()->Id == SPELL_DH_ANNIHILATION))
//				return true;
//
//			return false;
//		}
//
//        void HandleProc(ProcEventInfo& /*eventInfo*/)
//        {
//            PreventDefaultAction();
//
//            if (Unit* caster = GetCaster())
//			{
//				caster->CastSpell(caster, SPELL_DH_CHAOS_STRIKE_PROC, true);
//				if (caster->HasAura(SPELL_DH_CYCLE_OF_HATRED))
//					caster->GetSpellHistory()->ModifyCooldown(SPELL_DH_METAMORPHOSIS, -1s * (int32)sSpellMgr->GetSpellInfo(SPELL_DH_CYCLE_OF_HATRED)->GetEffect(EFFECT_0).BasePoints);
//        }
//        }
//
//        void Register() override
//        {
//			DoCheckProc += AuraCheckProcFn(spell_dh_chaos_strike_AuraScript::CheckProc);
//            OnProc += AuraProcFn(spell_dh_chaos_strike_AuraScript::HandleProc);
//        }
//    };
//
//    AuraScript* GetAuraScript() const override
//    {
//        return new spell_dh_chaos_strike_AuraScript();
//    }
//};

// Consume Soul - 178963 and 228532
//Last Update 8.0.1 Build 28153
class spell_dh_consume_soul : public SpellScriptLoader
{
public:
    spell_dh_consume_soul() : SpellScriptLoader("spell_dh_consume_soul") {}

    class spell_dh_consume_soul_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_dh_consume_soul_SpellScript);

        void PreventPower(SpellEffIndex effIndex)
        {
            Unit* caster = GetCaster();
            if (!caster)
                return;
            
            if (!caster->HasAura(SPELL_DH_DEMONIC_APPETITE))                 
                PreventHitEffect(effIndex);                     
        }

        void Register() override
        {
            OnEffectHit += SpellEffectFn(spell_dh_consume_soul_SpellScript::PreventPower, EFFECT_1, SPELL_EFFECT_TRIGGER_SPELL);
            OnEffectHitTarget += SpellEffectFn(spell_dh_consume_soul_SpellScript::PreventPower, EFFECT_1, SPELL_EFFECT_TRIGGER_SPELL);
            OnEffectLaunch += SpellEffectFn(spell_dh_consume_soul_SpellScript::PreventPower, EFFECT_1, SPELL_EFFECT_TRIGGER_SPELL);
            OnEffectLaunchTarget += SpellEffectFn(spell_dh_consume_soul_SpellScript::PreventPower, EFFECT_1, SPELL_EFFECT_TRIGGER_SPELL);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_dh_consume_soul_SpellScript();
    }
};

// 206478 - Demonic Appetite
class spell_dh_demonic_appetite : public AuraScript
{
    PrepareAuraScript(spell_dh_demonic_appetite);

    bool CheckProc(ProcEventInfo& eventInfo)
    {           
        if (eventInfo.GetSpellInfo() && (eventInfo.GetSpellInfo()->Id == SPELL_DH_CHAOS_STRIKE_MAIN_HAND || eventInfo.GetSpellInfo()->Id == SPELL_DH_ANNIHILATION_MAINHAIND))
            return true;

        return false;
    }

    void HandleProc(AuraEffect const* /*aurEff*/, ProcEventInfo& /*eventInfo*/)
    {
        PreventDefaultAction();           
       ///if (Unit* caster = GetCaster())
       ///    caster->CastSpell(RAND(SPELL_DH_SHATTERED_SOUL_LESSER_SOUL_FRAGMENT_1, SPELL_DH_SHATTERED_SOUL_LESSER_SOUL_FRAGMENT_2), SpellValueMod(SPELLVALUE_TRIGGER_SPELL + EFFECT_1), SPELL_DH_SS_HAVOC_LESSER_SOUL, caster, TRIGGERED_FULL_MASK);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_dh_demonic_appetite::CheckProc);
     //   OnEffectProc += AuraEffectProcFn(spell_dh_demonic_appetite::HandleProc, EFFECT_0, SPELL_AURA_PROC_TRIGGER_SPELL);
    }
};

// 131347 - Glide
//Last Update 8.0.1 Build 28153
class spell_dh_glide : public SpellScriptLoader
{
public:
    spell_dh_glide() : SpellScriptLoader("spell_dh_glide") { }

    class spell_dh_glide_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_dh_glide_SpellScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_DH_GLIDE))
                return false;
            return true;
        }

        SpellCastResult CheckCast()
        {
            if (!GetCaster())
                return SPELL_FAILED_DONT_REPORT;

            if (!GetCaster()->IsFalling())
                return SPELL_FAILED_NOT_ON_GROUND;

            if (GetCaster()->IsMounted())
                return SPELL_FAILED_NOT_MOUNTED;

            if (GetCaster()->GetCurrentSpell(CurrentSpellTypes::CURRENT_CHANNELED_SPELL))
                return SPELL_FAILED_DONT_REPORT;

            return SPELL_CAST_OK;
        }

        void HandleOnHit(SpellEffIndex /*effIndex*/)
        {
            if(Unit* caster = GetCaster())
                caster->CastSpell(caster, SPELL_DH_GLIDE_KNOCKBACK, true);
        }

        void Register() override
        {
            OnCheckCast += SpellCheckCastFn(spell_dh_glide_SpellScript::CheckCast);
            OnEffectHitTarget += SpellEffectFn(spell_dh_glide_SpellScript::HandleOnHit, EFFECT_0, SPELL_EFFECT_APPLY_AURA);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_dh_glide_SpellScript();
    }
};

// Darkness absorb - 209426
//Last Update 8.0.1 Build 28153
class spell_dh_darkness_absorb : public SpellScriptLoader
{
public:
    spell_dh_darkness_absorb() : SpellScriptLoader("spell_dh_darkness_absorb") {}

    class spell_dh_darkness_absorb_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_dh_darkness_absorb_AuraScript);

        void CalculateAmount(AuraEffect const* /*aurEff*/, int32& amount, bool& /*canBeRecalculated*/)
        {
            amount = -1;
        }

        void HandleAbsorb(AuraEffect* /*aurEff*/, DamageInfo& dmgInfo, uint32& absorbAmount)
        {
            if (Aura* aura = GetAura())
            {
                int32 absorbChance = aura->GetEffect(EFFECT_1)->GetAmount();
                if (roll_chance_i(absorbChance))
                    absorbAmount = dmgInfo.GetDamage();
                else
                    absorbAmount = 0;
            }
        }

        void Register() override
        {
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_dh_darkness_absorb_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
            OnEffectAbsorb += AuraEffectAbsorbFn(spell_dh_darkness_absorb_AuraScript::HandleAbsorb, EFFECT_0);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_dh_darkness_absorb_AuraScript();
    }
};

// Infernal Strike - 189110
class spell_dh_infernal_strike : public SpellScript
{
    PrepareSpellScript(spell_dh_infernal_strike);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_DH_INFERNAL_STRIKE_JUMP, SPELL_DH_INFERNAL_STRIKE_DAMAGE });
    }

    SpellCastResult CheckDestination()
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
        Unit* caster = GetCaster();
        WorldLocation const* dest = GetHitDest();
        if (!caster || !dest)
            return;

        caster->CastSpell(*dest, SPELL_DH_INFERNAL_STRIKE_JUMP, true);
        caster->CastSpell(caster, SPELL_DH_INFERNAL_STRIKE_VISUAL, true);
    }

    void Register() override
    {
        OnCheckCast += SpellCheckCastFn(spell_dh_infernal_strike::CheckDestination);
        OnEffectHit += SpellEffectFn(spell_dh_infernal_strike::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

/// ID: 189111 Infernal Strike
class spell_infernal_strike_jump : public SpellScript
{
    PrepareSpellScript(spell_infernal_strike_jump);

    void HandleJumpCharge(Optional<JumpArrivalCastArgs>& arrivalCast)
    {
        auto caster = GetCaster();
        if (!caster)
            return;
        if (!arrivalCast.has_value())
        {
            arrivalCast.emplace();
            arrivalCast->Callback = [caster]
            {
                caster->CastSpell(caster, SPELL_DH_INFERNAL_STRIKE_DAMAGE, true);
                if (caster->HasAura(207550)) ///< Abyssal Strike
                    caster->CastSpell(caster, SPELL_DH_SIGIL_OF_FLAME_NO_DEST, true);
            };
        }
    }

    void Register() override
    {
        OnJumpCharge += SpellJumpChargeFn(spell_infernal_strike_jump::HandleJumpCharge);
    }
};

// Felblade - 232893
class spell_dh_felblade : public SpellScript
{
    PrepareSpellScript(spell_dh_felblade);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_DH_FELBLADE_CHARGE });
    }

    void HandleDummy(SpellEffIndex /*effIndex*/)
    {
		Unit* target = GetHitUnit();
		Unit* caster = GetCaster();
		if (!caster || !target)
			return;

		caster->CastSpell(target, SPELL_DH_FELBLADE_CHARGE, true);
		caster->RemoveAurasDueToSpell(SPELL_DH_FELBLADE_INDICATOR);
    }

	void HandleAfterCast()
	{
		if (Unit* caster = GetCaster())
			caster->CastSpell(caster, SPELL_DH_FELBLADE_AURA, true);;
	}

    void Register() override
    {
		AfterCast += SpellCastFn(spell_dh_felblade::HandleAfterCast);
        OnEffectHitTarget += SpellEffectFn(spell_dh_felblade::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

class spell_dh_sigil_of_misery_fear : public AuraScript
{
    PrepareAuraScript(spell_dh_sigil_of_misery_fear);

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
                owner->ToUnit()->RemoveAura(GetAura());
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_dh_sigil_of_misery_fear::CheckProc);
        OnProc += AuraProcFn(spell_dh_sigil_of_misery_fear::HandleProc);
    }
};

// 206475
class aura_dh_chaos_cleave : public AuraScript
{
    PrepareAuraScript(aura_dh_chaos_cleave);

    void HandleProc(AuraEffect const* /*aurEff*/, ProcEventInfo& eventInfo)
    {
        int32 bp = CalculatePct(eventInfo.GetDamageInfo()->GetDamage(), 10);
     //   GetTarget()->CastSpell(nullptr, SPELL_DH_CHAOS_CLEAVE_DAMAGE, &bp, nullptr, nullptr, true);
    }

    void Register() override
    {
       // OnEffectProc += AuraEffectProcFn(aura_dh_chaos_cleave::HandleProc, EFFECT_0, SPELL_AURA_PROC_TRIGGER_SPELL);
    }
};

// Sigil of Misery - 207684
// AreaTriggerID - 6351
struct at_dh_sigil_of_misery : AreaTriggerAI
{
    at_dh_sigil_of_misery(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger) { }

    void OnRemove() override
    {
        if (Unit* caster = at->GetCaster())
        {
            caster->CastSpell(at->GetPosition(), SPELL_DH_SIGIL_OF_MISERY_TRIGGER, true);
            caster->CastSpell(at->GetPosition(), SPELL_DH_SIGIL_OF_MISERY_EXPLOSION, true);

            if (AuraEffect* auraEff = caster->GetAuraEffect(SPELL_DH_CYCLE_OF_BLINDING_POWER, EFFECT_0))
            {
              //  caster->CastSpell(SPELL_DH_CYCLE_OF_BLINDING_BUFF, SPELLVALUE_BASE_POINT0, auraEff->GetAmount(), caster);

              //  caster->GetSpellHistory()->ModifyCooldown(SPELL_DH_SIGIL_OF_FLAME, -1s * (int32)sSpellMgr->GetSpellInfo(SPELL_DH_CYCLE_OF_BLINDING_POWER)->GetEffect(EFFECT_1).BasePoints);
                caster->GetSpellHistory()->ModifyCooldown(SPELL_DH_SIGIL_OF_MISSERY, -1s * (int32)sSpellMgr->GetSpellInfo(SPELL_DH_CYCLE_OF_BLINDING_POWER)->GetEffect(EFFECT_1).BasePoints);
                caster->GetSpellHistory()->ModifyCooldown(SPELL_DH_SIGIL_OF_SILENCE, -1s * (int32)sSpellMgr->GetSpellInfo(SPELL_DH_CYCLE_OF_BLINDING_POWER)->GetEffect(EFFECT_1).BasePoints);
                caster->GetSpellHistory()->ModifyCooldown(SPELL_DH_SIGIL_OF_CHAINS, -1s * (int32)sSpellMgr->GetSpellInfo(SPELL_DH_CYCLE_OF_BLINDING_POWER)->GetEffect(EFFECT_1).BasePoints);
            }
        }
    }
};

// Sigil of Flame - 204596
// AreaTriggerID - 10727
struct at_dh_sigil_of_flame : AreaTriggerAI
{
    at_dh_sigil_of_flame(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger) { }

    void OnRemove() override
    {
        if (Unit* caster = at->GetCaster())
        {
            caster->CastSpell(at->GetPosition(), SPELL_DH_SIGIL_OF_FLAME_TRIGGER, true);
            caster->CastSpell(at->GetPosition(), SPELL_DH_SIGIL_OF_FLAME_EXPLOSION, true);

            if (AuraEffect* auraEff = caster->GetAuraEffect(SPELL_DH_CYCLE_OF_BLINDING_POWER, EFFECT_0))
            {
               // caster->CastSpell(SPELL_DH_CYCLE_OF_BLINDING_BUFF, SPELLVALUE_BASE_POINT0, auraEff->GetAmount(), caster);

          //      caster->GetSpellHistory()->ModifyCooldown(SPELL_DH_SIGIL_OF_FLAME, -1s * (int32)sSpellMgr->GetSpellInfo(SPELL_DH_CYCLE_OF_BLINDING_POWER)->GetEffect(EFFECT_1).BasePoints);
                caster->GetSpellHistory()->ModifyCooldown(SPELL_DH_SIGIL_OF_MISSERY, -1s * (int32)sSpellMgr->GetSpellInfo(SPELL_DH_CYCLE_OF_BLINDING_POWER)->GetEffect(EFFECT_1).BasePoints);
                caster->GetSpellHistory()->ModifyCooldown(SPELL_DH_SIGIL_OF_SILENCE, -1s * (int32)sSpellMgr->GetSpellInfo(SPELL_DH_CYCLE_OF_BLINDING_POWER)->GetEffect(EFFECT_1).BasePoints);
                caster->GetSpellHistory()->ModifyCooldown(SPELL_DH_SIGIL_OF_CHAINS, -1s * (int32)sSpellMgr->GetSpellInfo(SPELL_DH_CYCLE_OF_BLINDING_POWER)->GetEffect(EFFECT_1).BasePoints);
            }
        }
    }
};

//204598 Sigil of Flame
//Last Update 8.0.1 Build 28153
class aura_dh_vengeance_sigil_of_flame : public AuraScript
{
    PrepareAuraScript(aura_dh_vengeance_sigil_of_flame);

    void HandleApply(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
    {
        Unit* caster = GetCaster();
        if (!caster)
            return;

        const_cast<AuraEffect*>(aurEff)->SetDonePct(caster->SpellDamagePctDone(GetTarget(), GetSpellInfo(), DOT, GetSpellInfo()->GetEffect(EFFECT_2)));
        const_cast<AuraEffect*>(aurEff)->SetDamage(int32(caster->SpellDamageBonusDone(GetTarget(), GetSpellInfo(), 0, DOT, GetSpellInfo()->GetEffect(EFFECT_2), GetStackAmount()) * aurEff->GetDonePct()));
        const_cast<AuraEffect*>(aurEff)->SetCritChance(caster->GetUnitSpellCriticalChance(GetTarget(), nullptr, aurEff, GetSpellInfo()->GetSchoolMask()));
        const_cast<AuraEffect*>(aurEff)->SetAmount(aurEff->GetDamage());
        GetAura()->SetNeedClientUpdateForTargets();
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(aura_dh_vengeance_sigil_of_flame::HandleApply, EFFECT_1, SPELL_AURA_PERIODIC_DAMAGE, AURA_EFFECT_HANDLE_REAL);
    }
};

// Sigil of Chains - 202138
// AreaTriggerID - 6031
struct at_dh_sigil_of_chains : AreaTriggerAI
{
    at_dh_sigil_of_chains(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger) { }

    void OnRemove() override
    {
        Unit* caster = at->GetCaster();
        if (!caster || !caster->IsPlayer())
            return;

        caster->CastSpell(at->GetPosition(), SPELL_DH_SIGIL_OF_CHAINS_EXPLOSION, true);
    }

    void OnUnitExit(Unit* unit) override
    {
        if (!at->IsRemoved())
            return;

        Unit* caster = at->GetCaster();
        if (!caster || !caster->IsPlayer())
            return;

        if (caster->IsValidAttackTarget(unit))
        {
            caster->CastSpell(unit, SPELL_DH_SIGIL_OF_CHAINS_SLOW, true);
            unit->CastSpell(at->GetPosition(), SPELL_DH_SIGIL_OF_CHAINS_TRIGGER, true);

            if (AuraEffect* auraEff = caster->GetAuraEffect(SPELL_DH_CYCLE_OF_BLINDING_POWER, EFFECT_0))
            {
                //  caster->CastSpell(SPELL_DH_CYCLE_OF_BLINDING_BUFF, SPELLVALUE_BASE_POINT0, auraEff->GetAmount(), caster);

       //           caster->GetSpellHistory()->ModifyCooldown(SPELL_DH_SIGIL_OF_FLAME, -1s * (int32)sSpellMgr->GetSpellInfo(SPELL_DH_CYCLE_OF_BLINDING_POWER)->GetEffect(EFFECT_1).BasePoints);
                caster->GetSpellHistory()->ModifyCooldown(SPELL_DH_SIGIL_OF_MISSERY, -1s * (int32)sSpellMgr->GetSpellInfo(SPELL_DH_CYCLE_OF_BLINDING_POWER)->GetEffect(EFFECT_1).BasePoints);
                caster->GetSpellHistory()->ModifyCooldown(SPELL_DH_SIGIL_OF_SILENCE, -1s * (int32)sSpellMgr->GetSpellInfo(SPELL_DH_CYCLE_OF_BLINDING_POWER)->GetEffect(EFFECT_1).BasePoints);
                caster->GetSpellHistory()->ModifyCooldown(SPELL_DH_SIGIL_OF_CHAINS, -1s * (int32)sSpellMgr->GetSpellInfo(SPELL_DH_CYCLE_OF_BLINDING_POWER)->GetEffect(EFFECT_1).BasePoints);
            }
        }
    }
};

// Darkness - 196718
// AreaTriggerID - 6615
//Last Update 8.0.1 Build 28153
struct at_dh_darkness : AreaTriggerAI
{
    at_dh_darkness(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger) { }

    void OnUnitEnter(Unit* unit) override
    {
        Unit* caster = at->GetCaster();
        if (!caster || !unit || !caster->IsPlayer())
            return;

        if (caster->IsFriendlyTo(unit))
            caster->CastSpell(unit, SPELL_DH_DARKNESS_BUFF, true);
    }

    void OnUnitExit(Unit* unit) override
    {
        Unit* caster = at->GetCaster();
        if (!caster || !unit || !caster->IsPlayer())
            return;

        if (Aura* darkness = unit->GetAura(SPELL_DH_DARKNESS_BUFF, caster->GetGUID()))
            darkness->SetDuration(0);
    }
};

// Shattered Souls
// Normal / Demon
//Last Update 8.0.1 Build 28153
struct at_dh_shattered_souls : AreaTriggerAI
{
    at_dh_shattered_souls(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger) { }

    void OnCreate() override
    {
        Unit* caster = at->GetCaster();
        if (!caster)
            return;

        caster->CastSpell(caster, SPELL_DH_SOUL_FRAGMENT_COUNTER, true);
    }

    void OnRemove() override
    {
        Unit* caster = at->GetCaster();
        if (!caster)
            return;

        caster->RemoveAuraFromStack(SPELL_DH_SOUL_FRAGMENT_COUNTER);
    }

    void OnUnitEnter(Unit* unit) override
    {
        Unit* caster = at->GetCaster();
        if (!caster)
            return;

        if (unit->GetGUID() != caster->GetGUID())
            return;

        uint32 spellId = at->GetSpellId();
        if (Player* player = caster->ToPlayer())
        {
            if (spellId == SPELL_DH_SS_HAVOC_NORMAL_AT || spellId == SPELL_DH_SS_VENGEANCE_NORMAL_AT)
                player->CastSpell(at->GetPosition(), (player->GetSpecializationId() == TALENT_SPEC_DEMON_HUNTER_HAVOC) ? SPELL_DH_CONSUME_SOUL_HAVOC_SHATTERED : SPELL_DH_CONSUME_SOUL_VENGEANCE_SHATTERED, true);
            else
            {
                player->CastSpell(at->GetPosition(), SPELL_DH_SS_DEMON_SOUL_BUFF);
                if (player->HasAura(SPELL_DH_DEMONIC_APPETITE))
                    player->CastSpell(player, SPELL_DH_DEMONIC_APPETITE_FURY, true);
            }

            //if (AuraEffect* auraEff = player->GetAuraEffect(SPELL_DH_SOULMONGER_POWER, EFFECT_0))
            //    player->CastSpell(SPELL_DH_SOULMONGER_SHIELD, SPELLVALUE_BASE_POINT0, auraEff->GetAmount(), player);

            at->SetDuration(0);
        }
    }
};

// Shattered Souls
// Lesser
//Last Update 8.0.1 Build 28153
struct at_dh_shattered_souls_lesser : AreaTriggerAI
{
    at_dh_shattered_souls_lesser(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger) { }

    void OnCreate() override
    {
        Unit* caster = at->GetCaster();
        if (!caster)
            return;

        caster->CastSpell(caster, SPELL_DH_SOUL_FRAGMENT_COUNTER, true);
    }

    void OnRemove() override
    {
        Unit* caster = at->GetCaster();
        if (!caster)
            return;

        caster->RemoveAuraFromStack(SPELL_DH_SOUL_FRAGMENT_COUNTER);
    }

    void OnUnitEnter(Unit* unit) override
    {
        Unit* caster = at->GetCaster();
        if (!caster)
            return;

        if (unit->GetGUID() != caster->GetGUID())
            return;

        if (Player* player = caster->ToPlayer())
        {
            if (player->GetSpecializationId() == TALENT_SPEC_DEMON_HUNTER_HAVOC)
                player->CastSpell(at->GetPosition(), SPELL_DH_CONSUME_SOUL_HAVOC, true);
            else            
                player->CastSpell(at->GetPosition(), SPELL_DH_SS_VENG_LESSER_HEAL, true);

           // if (AuraEffect* auraEff = player->GetAuraEffect(SPELL_DH_SOULMONGER_POWER, EFFECT_0))
           //     player->CastSpell(SPELL_DH_SOULMONGER_SHIELD, SPELLVALUE_BASE_POINT0, auraEff->GetAmount(), player);

            at->SetDuration(0);
        }
    }
};

// Sigil of Silence - 202137
// AreaTriggerID -  10714
struct at_dh_sigil_of_silence : AreaTriggerAI
{
    at_dh_sigil_of_silence(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger) { }

    void OnRemove() override
    {
        if (Unit* caster = at->GetCaster())
        {
            caster->CastSpell(at->GetPosition(), SPELL_DH_SIGIL_OF_SILENCE_TRIGGER, true);
            caster->CastSpell(at->GetPosition(), SPELL_DH_SIGIL_OF_SILENCE_EXPLOSION, true);

            if (AuraEffect* auraEff = caster->GetAuraEffect(SPELL_DH_CYCLE_OF_BLINDING_POWER, EFFECT_0))
            {
              //  caster->CastSpell(SPELL_DH_CYCLE_OF_BLINDING_BUFF, SPELLVALUE_BASE_POINT0, auraEff->GetAmount(), caster);

             //   caster->GetSpellHistory()->ModifyCooldown(SPELL_DH_SIGIL_OF_FLAME, -1s * (int32)sSpellMgr->GetSpellInfo(SPELL_DH_CYCLE_OF_BLINDING_POWER)->GetEffect(EFFECT_1).BasePoints);
                caster->GetSpellHistory()->ModifyCooldown(SPELL_DH_SIGIL_OF_MISSERY, -1s * (int32)sSpellMgr->GetSpellInfo(SPELL_DH_CYCLE_OF_BLINDING_POWER)->GetEffect(EFFECT_1).BasePoints);
                caster->GetSpellHistory()->ModifyCooldown(SPELL_DH_SIGIL_OF_SILENCE, -1s * (int32)sSpellMgr->GetSpellInfo(SPELL_DH_CYCLE_OF_BLINDING_POWER)->GetEffect(EFFECT_1).BasePoints);
                caster->GetSpellHistory()->ModifyCooldown(SPELL_DH_SIGIL_OF_CHAINS, -1s * (int32)sSpellMgr->GetSpellInfo(SPELL_DH_CYCLE_OF_BLINDING_POWER)->GetEffect(EFFECT_1).BasePoints);
            }
        }
    }
};

// 258881 - Trail of Ruin (v8.0.1)
class spell_talent_dh_trail_of_ruin_aura : public AuraScript
{
    PrepareAuraScript(spell_talent_dh_trail_of_ruin_aura);

    bool OnCheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_talent_dh_trail_of_ruin_aura::OnCheckProc);
    }
};

// Demon's Bite(162243) - Insatiable Hunger(258876) v8.0.1
class spell_dh_demon_bite_insatiable_hunger : public SpellScript
{
    PrepareSpellScript(spell_dh_demon_bite_insatiable_hunger);


    void HandleHit(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();

        if (!caster)
            return;

        if (caster->HasAura(SPELL_AURA_DH_INSATIABLE_HUNGER))
        {            
            SetEffectValue(GetEffectValue() + caster->GetAura(SPELL_AURA_DH_INSATIABLE_HUNGER)->GetEffect(EFFECT_0)->GetBaseAmount());
        }
        
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_dh_demon_bite_insatiable_hunger::HandleHit, EFFECT_2, SPELL_EFFECT_ENERGIZE);
    }
};

// Mana Rift - 235903
// AreaTriggerID -  9695
//Last Update 8.0.1 Build 28153
struct at_dh_mana_rift : AreaTriggerAI
{
    at_dh_mana_rift(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger) { }

    void OnRemove() override
    {
        if (Unit* caster = at->GetCaster())
        {
            for (ObjectGuid guid : at->GetInsideUnits())
            {
                Unit* unit = ObjectAccessor::GetUnit(*caster, guid);
                if (unit && unit->IsPlayer() && caster->IsValidAttackTarget(unit))
                {
                    int32 bp0 = CalculatePct(unit->GetMaxHealth(), sSpellMgr->GetSpellInfo(SPELL_DH_MANA_RIFT)->GetEffect(EFFECT_1).BasePoints);

                    if (unit->GetPower(POWER_MANA) > 0)
                    {
                        int32 mana = unit->GetPower(POWER_MANA) - CalculatePct(unit->GetMaxPower(POWER_MANA), sSpellMgr->GetSpellInfo(SPELL_DH_MANA_RIFT)->GetEffect(EFFECT_2).BasePoints);
                        unit->SetPower(POWER_MANA, mana > 0 ? mana : 0);
                    }

                  //  caster->CastSpell(unit, SPELL_DH_MANA_RIFT_EFFECT, &bp0, nullptr, nullptr, true);
                }
            }
        }
    }
};

// 255260, 281242 - Chaos Brand
class aura_dh_chaos_brand : public AuraScript
{
	PrepareAuraScript(aura_dh_chaos_brand);

	bool CheckProc(ProcEventInfo& eventInfo)
	{
        if (eventInfo.GetSpellInfo())
        {
            if (Unit* caster = GetCaster())
            {
                if (Player* player = caster->ToPlayer())
                {
                    if (player->GetSpecializationId() == TALENT_SPEC_DEMON_HUNTER_VENGEANCE)
                    {
                        if ((eventInfo.GetSpellInfo()->GetSchoolMask() == SPELL_SCHOOL_MASK_FIRE))
                            return true;
                    }
                    else if ((eventInfo.GetSpellInfo()->GetSchoolMask() == SPELL_SCHOOL_MASK_ALL))
                        return true;
                }
            }
        }

		return false;
	}

	void HandleProc(ProcEventInfo& eventInfo)
	{
		Unit* caster = GetCaster();
		Unit* target = eventInfo.GetActionTarget();
		if (!caster || !target)
			return;

		caster->CastSpell(target, SPELL_DH_CHAOS_BRAND, true);
		if (Aura* aura = target->GetAura(SPELL_DH_CHAOS_BRAND))
			aura->SetDuration(15 * IN_MILLISECONDS);
	}

	void Register() override
	{
		DoCheckProc += AuraCheckProcFn(aura_dh_chaos_brand::CheckProc);
		OnProc += AuraProcFn(aura_dh_chaos_brand::HandleProc);
	}
};

// 236167 - Felblade
//Last Update 8.0.1 Build 28153
class aura_dh_felblade : public AuraScript
{
	PrepareAuraScript(aura_dh_felblade);

	bool CheckProc(ProcEventInfo& eventInfo)
	{
        if(eventInfo.GetActor() && eventInfo.GetActor()->ToPlayer() && eventInfo.GetActor()->ToPlayer()->GetSpellHistory()->HasCooldown(SPELL_DH_FELBLADE))
            if (eventInfo.GetSpellInfo() && (eventInfo.GetSpellInfo()->Id == SPELL_DH_DEMONS_BITE || eventInfo.GetSpellInfo()->Id == SPELL_DH_DEMON_BLADES_TRIGGER) && roll_chance_i(10))
                return true;

		return false;
	}

	void HandleProc(ProcEventInfo& eventInfo)
	{
		if (Unit* caster = GetCaster())
		{
			caster->GetSpellHistory()->ResetCooldown(SPELL_DH_FELBLADE, true);
			caster->CastSpell(caster, SPELL_DH_FELBLADE_INDICATOR, true);
			caster->RemoveAurasDueToSpell(SPELL_DH_FELBLADE_AURA);
		}
	}

	void Register() override
	{
		DoCheckProc += AuraCheckProcFn(aura_dh_felblade::CheckProc);
		OnProc += AuraProcFn(aura_dh_felblade::HandleProc);
	}
};

// 203468 - Glimpse
class aura_dh_glimpse : public AuraScript
{
	PrepareAuraScript(aura_dh_glimpse);

	bool CheckProc(ProcEventInfo& eventInfo)
	{
		if (eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == SPELL_DH_VENGEFUL_RETREAT)
			return true;

		return false;
	}

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& /*eventInfo*/)
	{
        if (Unit* owner = GetUnitOwner())
        {
            // "You automatically gain Blur for 3 sec after you use Vengeful Retreat."
            if (Aura* blur = owner->GetAura(SPELL_DH_BLUR_AURA))
            {
                blur->SetDuration(blur->GetDuration() + aurEff->GetAmount());

                if (blur->GetDuration() > blur->GetMaxDuration())
                    blur->SetMaxDuration(blur->GetDuration());
            }
            else
            {
                if (Aura* aura = owner->AddAura(SPELL_DH_BLUR_AURA, owner))
                {                    
                    aura->SetDuration(GetSpellInfo()->GetEffect(EFFECT_0).BasePoints);
                    aura->SetMaxDuration(GetSpellInfo()->GetEffect(EFFECT_0).BasePoints);
                }
            }          
        }
	}

	void Register() override
	{
		DoCheckProc += AuraCheckProcFn(aura_dh_glimpse::CheckProc);
    //    OnEffectProc += AuraEffectProcFn(aura_dh_glimpse::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
	}
};

// 211509 - Solitude
class aura_dh_solitude : public AuraScript
{
	PrepareAuraScript(aura_dh_solitude);

	void HandlePeriodic(AuraEffect const* /*aurEff*/)
	{
		if (Unit* caster = GetCaster())

			if (Player* player = caster->ToPlayer())
			{
				UnitList friends;
				player->GetFriendlyUnitListInRange(friends, 15, true);
				friends.remove_if([player](Unit* target)
				{
					if (!target)
						return true;

					if (!target->ToPlayer())
						return true;

					if (!player->IsInSameGroupWith(target->ToPlayer()) && !player->IsInSameRaidWith(target->ToPlayer()))
						return true;

					return false;
				});

				if (!player->HasAura(SPELL_DH_SOLITUDE_BUFF) && friends.size() == 0)
					player->CastSpell(player, SPELL_DH_SOLITUDE_BUFF, true);
				else if (player->HasAura(SPELL_DH_SOLITUDE_BUFF) && friends.size() > 0)
					player->RemoveAura(SPELL_DH_SOLITUDE_BUFF);
			}
	}

	void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
	{
		if (Unit* caster = GetCaster())
			caster->RemoveAura(SPELL_DH_SOLITUDE_BUFF);
	}

	void Register() override
	{
		OnEffectPeriodic += AuraEffectPeriodicFn(aura_dh_solitude::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
		OnEffectRemove += AuraEffectRemoveFn(aura_dh_solitude::HandleRemove, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL, AURA_EFFECT_HANDLE_REAL);
	}
};

// 206649 - Eye of Leotheras
class aura_dh_eye_of_leotheras : public AuraScript
{
	PrepareAuraScript(aura_dh_eye_of_leotheras);

	bool Validate(SpellInfo const* /*spellInfo*/) override
	{
		return ValidateSpellInfo({ SPELL_DH_EYE_OF_LOTHERAS_DAMAGE });
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

		//caster->CastSpell(SPELL_DH_EYE_OF_LOTHERAS_DAMAGE, SPELLVALUE_BASE_POINT0, sSpellMgr->GetSpellInfo(SPELL_DH_EYE_OF_LOTHERAS_DAMAGE)->GetEffect(1)->BasePoints, actor, true);
		if (Aura* aura = GetAura())
			aura->RefreshDuration();
	}

	void Register() override
	{
		DoCheckProc += AuraCheckProcFn(aura_dh_eye_of_leotheras::CheckProc);
		OnProc += AuraProcFn(aura_dh_eye_of_leotheras::HandleProc);
	}
};

// 235893 - Demonic Origins
//Last Update 8.0.1 Build 28153
class aura_dh_demonic_origins : public AuraScript
{
    PrepareAuraScript(aura_dh_demonic_origins);

    void HandleApply(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /* mode */)
    {
        if (Unit* caster = GetCaster())
            if (!caster->HasAura(SPELL_DH_METAMORPHOSIS_BUFFS))
                caster->CastSpell(caster, SPELL_DH_DEMONIC_ORIGINS_DAMAGE, true);
    }

    void HandleRemove(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /* mode */)
    {
        if (Unit* caster = GetCaster())
            caster->RemoveAura(SPELL_DH_DEMONIC_ORIGINS_DAMAGE);
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(aura_dh_demonic_origins::HandleApply, EFFECT_1, SPELL_AURA_ADD_FLAT_MODIFIER, AURA_EFFECT_HANDLE_REAL);
        OnEffectRemove += AuraEffectRemoveFn(aura_dh_demonic_origins::HandleRemove, EFFECT_1, SPELL_AURA_ADD_FLAT_MODIFIER, AURA_EFFECT_HANDLE_REAL);
    }

private:
    uint32 tick = 1 * IN_MILLISECONDS;
};

// 162264 - Metamorphosis buff
class aura_dh_metamorphosis_buff : public AuraScript
{
    PrepareAuraScript(aura_dh_metamorphosis_buff);

    void HandleApply(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /* mode */)
    {
        if (Unit* caster = GetCaster())
            caster->RemoveAura(SPELL_DH_DEMONIC_ORIGINS_DAMAGE);
    }

    void HandleRemove(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /* mode */)
    {
        if (Unit* caster = GetCaster())
            if (caster->HasSpell(SPELL_DH_DEMONIC_ORIGINS))
                caster->CastSpell(caster, SPELL_DH_DEMONIC_ORIGINS_DAMAGE, true);
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(aura_dh_metamorphosis_buff::HandleApply, EFFECT_0, SPELL_AURA_TRANSFORM, AURA_EFFECT_HANDLE_REAL);
        OnEffectRemove += AuraEffectRemoveFn(aura_dh_metamorphosis_buff::HandleRemove, EFFECT_0, SPELL_AURA_TRANSFORM, AURA_EFFECT_HANDLE_REAL);
    }
};

// 203704 - Mana Break
//Last Update 8.0.1 Build 28153
class spell_dh_mana_break : public SpellScript
{
    PrepareSpellScript(spell_dh_mana_break);

    void HandleHitTarget(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        float pct = GetSpellInfo()->GetEffect(EFFECT_1).BasePoints;
        // Only affects mana targets.
        if (target->GetPower(POWER_MANA) > 0)
        {
            pct += (100.0f - target->GetPowerPct(POWER_MANA)) / GetSpellInfo()->GetEffect(EFFECT_2).BasePoints;

            if (pct > GetSpellInfo()->GetEffect(EFFECT_3).BasePoints)
                pct = GetSpellInfo()->GetEffect(EFFECT_3).BasePoints;
        }
        
        SetHitDamage(CalculatePct(target->IsPlayer() ? target->GetMaxHealth() : caster->GetMaxHealth(), pct));
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_dh_mana_break::HandleHitTarget, EFFECT_0, SPELL_EFFECT_DAMAGE_FROM_MAX_HEALTH_PCT);
    }
};

// 208796 - Jagged Spikes Aura
class aura_jagged_spikes_aura : public AuraScript
{
	PrepareAuraScript(aura_jagged_spikes_aura);

	void HandleProc(ProcEventInfo& eventInfo)
	{
		if (eventInfo.GetDamageInfo())
		{
			Unit* caster = GetCaster();
			Unit* target = eventInfo.GetDamageInfo()->GetAttacker();
			if (!caster || !target)
				return;

			int32 damage = eventInfo.GetDamageInfo()->GetDamage();
			int32 finalDamage = CalculatePct(damage, sSpellMgr->GetSpellInfo(SPELL_DH_JAGGED_SPIKES)->GetEffect(EFFECT_0).BasePoints);
		//	caster->CastSpell(SPELL_DH_JAGGED_SPIKES_DAMAGE, SPELLVALUE_BASE_POINT0, finalDamage, target, true);
		}
	}

	void Register() override
	{
		OnProc += AuraProcFn(aura_jagged_spikes_aura::HandleProc);
	}
};

// 205625 - Cleansed by Flame
class aura_dh_cleansed_by_flame : public AuraScript
{
	PrepareAuraScript(aura_dh_cleansed_by_flame);

	bool CheckProc(ProcEventInfo& eventInfo)
	{
		if (eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == SPELL_DH_IMMOLATION_AURA)
			return true;

		return false;
	}

	void Register() override
	{
		DoCheckProc += AuraCheckProcFn(aura_dh_cleansed_by_flame::CheckProc);
	}
};

// 217832 - Imprison
class aura_dh_imprision : public AuraScript
{
    PrepareAuraScript(aura_dh_imprision);

    void HandleProc(ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();
        Unit* target = GetTarget();
        if (!caster || !target)
            return;

        target->RemoveAura(SPELL_DH_IMPRISION, caster->GetGUID());
    }

    void Register() override
    {
        OnProc += AuraProcFn(aura_dh_imprision::HandleProc);
    }
};

// 218903 - Disrupt Energize
class spell_dh_disrupt_energize : public SpellScript
{
    PrepareSpellScript(spell_dh_disrupt_energize);

    void HandleEffectHitHVengeance(SpellEffIndex effIndex)
    {
        if (Unit* caster = GetCaster())
        {
            if (Player* player = caster->ToPlayer())
            {
                if (player->GetSpecializationId() != TALENT_SPEC_DEMON_HUNTER_HAVOC)
                {
                    PreventHitEffect(effIndex);
                    return;
                }
            }
        }
    }

    void HandleEffectHitHavoc(SpellEffIndex effIndex)
    {
        if (Unit* caster = GetCaster())
        {
            if (Player* player = caster->ToPlayer())
            {
                if (player->GetSpecializationId() != TALENT_SPEC_DEMON_HUNTER_VENGEANCE)
                {
                    PreventHitEffect(effIndex);
                    return;
                }
            }
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_dh_disrupt_energize::HandleEffectHitHVengeance, EFFECT_0, SPELL_EFFECT_ENERGIZE);
        OnEffectHitTarget += SpellEffectFn(spell_dh_disrupt_energize::HandleEffectHitHavoc, EFFECT_1, SPELL_EFFECT_ENERGIZE);
    }
};

// 278326 - Consume Magic
class spell_dh_consume_magic : public SpellScript
{
    PrepareSpellScript(spell_dh_consume_magic);

    void OnSuccessfulDispel(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        Player* player = GetCaster()->ToPlayer();
        if (!player)
            return;

        if (AuraEffect* aurEff = caster->GetAuraEffect(SPELL_DH_BURNING_SOUL_POWER, EFFECT_0))
        {
         //   caster->CastSpell(SPELL_DH_BURNING_SOUL_BUFF, SPELLVALUE_BASE_POINT0, aurEff->GetAmount(), caster, true);

            uint32 triggerSpellId = player->GetSpecializationId() == TALENT_SPEC_DEMON_HUNTER_VENGEANCE ? SPELL_DH_SS_VENGEANCE_SOUL_NORMAL : SPELL_DH_SS_HAVOC_SOUL_NORMAL;
            if (Creature* creature = target->ToCreature())
                if (CreatureTemplate const* creTemplate = creature->GetCreatureTemplate())
                    if (creTemplate->type == CREATURE_TYPE_DEMON)
                        triggerSpellId = player->GetSpecializationId() == TALENT_SPEC_DEMON_HUNTER_VENGEANCE ? SPELL_DH_SS_VENGEANCE_SOUL_DEMON : SPELL_DH_SS_HAVOC_SOUL_DEMON;

        //    caster->CastSpell(RAND(SPELL_DH_SHATTER_SOUL, SPELL_DH_SHATTER_SOUL_1, SPELL_DH_SHATTER_SOUL_2, SPELL_DH_SHATTER_SOUL_3), SpellValueMod(SPELLVALUE_TRIGGER_SPELL + EFFECT_1), triggerSpellId, caster);
        }

        consume = true;
    }

    void HandleEffectHitHVengeance(SpellEffIndex effIndex)
    {
        if (Unit* caster = GetCaster())
        {
            if (Player* player = caster->ToPlayer())
                if (player->GetSpecializationId() != TALENT_SPEC_DEMON_HUNTER_HAVOC)
                {
                    PreventHitEffect(effIndex);
                    return;
                }

            if (consume)
                return;

            PreventHitEffect(effIndex);
        }
    }

    void HandleEffectHitHavoc(SpellEffIndex effIndex)
    {
        if (Unit* caster = GetCaster())
        {
            if (Player* player = caster->ToPlayer())
                if (player->GetPrimarySpecialization() != TALENT_SPEC_DEMON_HUNTER_VENGEANCE)
                {
                    PreventHitEffect(effIndex);
                    return;
                }

            if (consume)
                return;

            PreventHitEffect(effIndex);
        }
    }

    void Register() override
    {
        OnEffectSuccessfulDispel += SpellEffectFn(spell_dh_consume_magic::OnSuccessfulDispel, EFFECT_0, SPELL_EFFECT_DISPEL);
        OnEffectHitTarget += SpellEffectFn(spell_dh_consume_magic::HandleEffectHitHVengeance, EFFECT_1, SPELL_EFFECT_ENERGIZE);
        OnEffectHitTarget += SpellEffectFn(spell_dh_consume_magic::HandleEffectHitHavoc, EFFECT_2, SPELL_EFFECT_ENERGIZE);
    }

private:
    bool consume = false;
};

// 200166 - Metamorphosis Stun
class spell_dh_metamorphosis_stun : public SpellScript
{
    PrepareSpellScript(spell_dh_metamorphosis_stun);

    void FilterTarget(std::list<WorldObject*>& targets)
    {
        Unit* caster = GetCaster();
        if (!caster)
            return;

        for (auto target : targets)
            if (target->ToPlayer())
                caster->CastSpell(target->ToPlayer(), SPELL_DH_METAMORPHOSIS_DAZZLE, true);

        targets.remove_if([](WorldObject* unit)
        {
            if (!unit->ToUnit())
                return true;

            if (unit->ToPlayer())
                return true;

            return false;
        });
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_dh_metamorphosis_stun::FilterTarget, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
    }
};

// 198030 - Eye Beam Damage
class spell_dh_eye_beam_damage : public SpellScript
{
    PrepareSpellScript(spell_dh_eye_beam_damage);

    void HandlePrepare()
    {
        if (Unit* caster = GetCaster())
            if (Player* player = caster->ToPlayer())
                mainTarget = player->GetSelectedUnit();
    }

    void HandleHit()
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        if (mainTarget && mainTarget->GetGUID() == target->GetGUID())
        {
            int32 damage = GetHitDamage();
            SetHitDamage(damage + CalculatePct(damage, 50));
        }
    }

    void FilterTargets(std::list<WorldObject*>& unitList)
    {
        Unit* caster = GetCaster();
        if (!caster)
            return;

        unitList.clear();
        std::list<Unit*>  units;
        caster->GetAttackableUnitListInRange(units, 25.f);
        units.remove_if([caster](Unit* unit)
            {
                return !caster->HasInLine(unit, 5.f, caster->GetObjectScale());
            });

        for (Unit* unit : units)
            unitList.push_back(unit);
    }


    void Register() override
    {
        OnPrepare += SpellOnPrepareFn(spell_dh_eye_beam_damage::HandlePrepare);
        OnHit += SpellHitFn(spell_dh_eye_beam_damage::HandleHit);
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_dh_eye_beam_damage::FilterTargets, EFFECT_0, TARGET_UNIT_RECT_CASTER_ENEMY);
    }

private:
    Unit* mainTarget;
};

// 198793 - Vengeful Retreat
class spell_dh_vengegul_retreat : public SpellScript
{
    PrepareSpellScript(spell_dh_vengegul_retreat);

    void HandleOnPrepare()
    {
        Unit* caster = GetCaster();
        if (caster)
            caster->RemoveMovementImpairingAuras(true);
    }

    void HandleAfterCast()
    {
        if (Unit* caster = GetCaster())
            if (caster->Variables.Exist("MOMENTUM"))
            {
                caster->GetSpellHistory()->ModifyCooldown(SPELL_DH_VENGEFUL_RETREAT, -5s);
                caster->Variables.Remove("MOMENTUM");
            }
    }

    void Register() override
    {
        OnPrepare += SpellOnPrepareFn(spell_dh_vengegul_retreat::HandleOnPrepare);
        AfterCast += SpellCastFn(spell_dh_vengegul_retreat::HandleAfterCast);
    }
};

// Reverse Magic - 205604
// Last Update 8.0.1 Build 28153
class spell_dh_reverse_magic : public SpellScript
{
    PrepareSpellScript(spell_dh_reverse_magic);

    void HandleOnHit()
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        uint32 dispelMask = (1 << DISPEL_MAGIC) | (1 << DISPEL_POISON);
        DispelChargesList dispel_list;
        target->GetDispellableAuraList(caster, dispelMask, dispel_list);
        if (dispel_list.empty())
            return;

        for (DispelChargesList::iterator itr = dispel_list.begin(); itr != dispel_list.end(); ++itr)
        {
            Aura* aura = itr->GetAura();
            if (!aura)
                continue;
            Unit* casterBuff = aura->GetCaster();
            if (casterBuff && caster->GetDistance(casterBuff) <= GetSpellInfo()->GetEffect(EFFECT_0).BasePoints)
            {
                if (Aura* targetAura = casterBuff->AddAura(aura->GetSpellInfo()->Id, casterBuff))
                {
                    targetAura->SetStackAmount(aura->GetStackAmount());
                    targetAura->SetDuration(aura->GetDuration());
                    targetAura->SetMaxDuration(aura->GetDuration());
                    for (int i = 0; i < MAX_SPELL_EFFECTS; ++i)
                    {
                        if (AuraEffect* targetEff = targetAura->GetEffect(i))
                        {
                            if (AuraEffect* Eff = aura->GetEffect(i))
                            {
                                targetEff->SetAmount(Eff->GetAmount());
                                targetEff->SetPeriodicTimer(Eff->GetPeriodicTimer());
                            }
                        }
                    }
                }
            }
            target->RemoveAurasDueToSpellByDispel(aura->GetId(), GetSpellInfo()->Id, aura->GetCasterGUID(), caster);
        }
    }    

    void Register() override
    {
        OnHit += SpellHitFn(spell_dh_reverse_magic::HandleOnHit);
    }
};

// 268175 - Void Reaver
//Last Update 8.0.1 Build 28153
class spell_dh_void_reaver : public AuraScript
{
    PrepareAuraScript(spell_dh_void_reaver);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return false;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_dh_void_reaver::CheckProc);
    }
};

// 206966 Fel Lance
//Last Update 8.0.1 Build 28153
class spell_dh_fel_lance : public SpellScript
{
    PrepareSpellScript(spell_dh_fel_lance);

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
        OnEffectHitTarget += SpellEffectFn(spell_dh_fel_lance::HandleHitTarget, EFFECT_0, SPELL_EFFECT_DAMAGE_FROM_MAX_HEALTH_PCT);
    }
};

// Chaos Nova - 179057 
//Last Update 8.0.1 Build 28153
class spell_dh_chaos_nova : public SpellScript
{
    PrepareSpellScript(spell_dh_chaos_nova);
    
    void HandleDummy(SpellEffIndex /*effIndex*/)
    {
        //if (Unit* caster = GetCaster())
        //    if(roll_chance_i(GetSpellInfo()->GetEffect(EFFECT_2).BasePoints))
        //        caster->CastSpell(RAND(SPELL_DH_SHATTERED_SOUL_LESSER_SOUL_FRAGMENT_1, SPELL_DH_SHATTERED_SOUL_LESSER_SOUL_FRAGMENT_2), SpellValueMod(SPELLVALUE_TRIGGER_SPELL + EFFECT_1), SPELL_DH_SS_HAVOC_LESSER_SOUL, caster, TRIGGERED_FULL_MASK);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_dh_chaos_nova::HandleDummy, EFFECT_1, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

// 228533 - Shatter Soul
// 237867 - Shatter Soul
// Last Update 8.0.1 Build 28153
class spell_dh_vengeance_shatter_soul : public SpellScript
{
    PrepareSpellScript(spell_dh_vengeance_shatter_soul);

#define MAX_SOUL_FRAGMENT_COUNT 4

    void HandleSoulFragment(SpellEffIndex /*effIndex*/)
    {
        if (Unit* caster = GetCaster())
        {
            std::vector<AreaTrigger*> areaTriggers = caster->GetAreaTriggersByEntry({ AREATRIGGER_DH_SOUL_FRAGMENT_VENGEANCE });
            while (areaTriggers.size() > MAX_SOUL_FRAGMENT_COUNT)
            {
                Trinity::Containers::RandomShuffle(areaTriggers);
                AbsorbSoul(areaTriggers.front(), caster);
                areaTriggers.erase(areaTriggers.begin());
            }
        }
    }

    void Register() override
    {
        OnEffectLaunchTarget += SpellEffectFn(spell_dh_vengeance_shatter_soul::HandleSoulFragment, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

// 323639 
class spell_dh_the_hunt : public SpellScript
{
    PrepareSpellScript(spell_dh_the_hunt);

    void HandleScript(SpellEffIndex /*effIndex*/)
    {
        if (Unit* target = GetHitUnit())
        {
            Unit* caster = GetCaster();
            if (!caster)
                return;

            std::list<Unit*> units;

            CellCoord p(Trinity::ComputeCellCoord(target->GetPositionX(), target->GetPositionY()));
            Cell cell(p);
            cell.SetNoCreate();

            Trinity::AttackableUnitInObjectRangeCheck u_check(caster, MELEE_RANGE);
            Trinity::UnitListSearcher<Trinity::AttackableUnitInObjectRangeCheck> searcher(caster, units, u_check);

            TypeContainerVisitor<Trinity::UnitListSearcher<Trinity::AttackableUnitInObjectRangeCheck>, WorldTypeMapContainer > world_unit_searcher(searcher);
            TypeContainerVisitor<Trinity::UnitListSearcher<Trinity::AttackableUnitInObjectRangeCheck>, GridTypeMapContainer >  grid_unit_searcher(searcher);

            cell.Visit(p, world_unit_searcher, *target->GetMap(), *target, MELEE_RANGE);
            cell.Visit(p, grid_unit_searcher, *target->GetMap(), *target, MELEE_RANGE);

            for (auto unit : units)
                caster->CastSpell(unit, 345335, true); // Hunt Dot
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_dh_the_hunt::HandleScript, EFFECT_0, SPELL_EFFECT_CHARGE);
    }
};

// 162794 201427
class spell_dh_chaos_strike : public SpellScript
{
    PrepareSpellScript(spell_dh_chaos_strike);

    enum ChaosStrike
    {
        RelentlessOnslought = 339151,
    };

    void HandleDummy(SpellEffIndex /*effIndex*/)
    {
        if (Unit* target = GetHitUnit())
        {
            uint32 chance = 0;

            if (auto aurEff = GetCaster()->GetAuraEffect(RelentlessOnslought, EFFECT_0))
                chance += aurEff->GetAmount();

            if (chance > 100)
                chance = 100;

            if (roll_chance_i(chance))
                GetCaster()->CastSpell(target, GetSpellInfo()->Id, true);

            if (roll_chance_i(40))
            {
                auto caster = GetCaster();
                if (!caster)
                    return;
                caster->CastSpell(caster, SPELL_DH_CHAOS_STRIKE_PROC, true);
                if (caster->HasAura(SPELL_DH_CYCLE_OF_HATRED))
                    caster->GetSpellHistory()->ModifyCooldown(SPELL_DH_EYE_BEAM, -1s);
            }
        }
    }

    void Register() override
    {
        OnEffectLaunchTarget += SpellEffectFn(spell_dh_chaos_strike::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

// ID - 339230 Serrated Glaive
class spell_dh_serrated_glaive : public AuraScript
{
    PrepareAuraScript(spell_dh_serrated_glaive);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == SPELL_DH_THROW_GLAIVE)
            return true;
        return false;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_dh_serrated_glaive::CheckProc);
    }
};

// ID - 258860 Essence Break
class spell_dh_essence_break : public SpellScript
{
    PrepareSpellScript(spell_dh_essence_break);

    enum EssenceBreak
    {
        EssenceBreakDebuff = 320338,
    };

    void HandleDamage(SpellEffIndex /*effIndex*/)
    {
        if (auto hitUnit = GetHitUnit())
        {
            GetCaster()->CastSpell(hitUnit, EssenceBreakDebuff, true);
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_dh_essence_break::HandleDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

// 183782
class spell_dh_disrupt : public AuraScript
{
    PrepareAuraScript(spell_dh_disrupt);

    void HandleProc(AuraEffect* /*aurEff*/, ProcEventInfo& procInfo)
    {
        PreventDefaultAction();

        Unit* caster = GetCaster();
        if (!caster)
            return;

        Unit* target = procInfo.GetActionTarget();
        if (!target)
            return;

        auto spell = procInfo.GetSpellInfo();
        if (!spell)
            return;
        if (!(procInfo.GetHitMask() & PROC_HIT_INTERRUPT))
            return;

        if (spell->Id == SPELL_DH_DISRUPT)
            caster->CastSpell(caster, SPELL_DH_DISRUPT_ENERGIZE, true);
    }

    void Register() override
    {
        OnEffectProc += AuraEffectProcFn(spell_dh_disrupt::HandleProc, EFFECT_0, SPELL_AURA_PROC_TRIGGER_SPELL);
    }
};


// ID - 192611 Fel Rush
class spell_dh_fel_rush_dmg : public SpellScript
{
    PrepareSpellScript(spell_dh_fel_rush_dmg);

    enum EssenceBreak
    {
        UnboundChaos = 347462,
    };

    uint32 AddPctAmount = 0;
    void BeforeSCast()
    {
        if (auto unbounChaos = GetCaster()->GetAuraEffect(UnboundChaos, EFFECT_0))
        {
            AddPctAmount = unbounChaos->GetAmount();
            GetCaster()->RemoveAurasDueToSpell(UnboundChaos);
        }
    }

    void HandleDamage(SpellEffIndex /*effIndex*/)
    {
        if (auto hitUnit = GetHitUnit())
        {
            auto hitDmg = GetHitDamage();

            if (AddPctAmount)
                AddPct(hitDmg, AddPctAmount);

            SetHitDamage(hitDmg);
        }
    }

    void CountTargets(std::list<WorldObject*>& targets)
    {
        Unit* caster = GetCaster();
        if (!caster)
            return;

        targets.clear();
        std::list<Unit*> units;
        caster->GetAttackableUnitListInRange(units, 25.f);
        units.remove_if([caster](Unit* unit)
        {
            return !caster->HasInLine(unit, 6.f, caster->GetObjectScale());
        });

        for (Unit* unit : units)
            targets.push_back(unit);
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_dh_fel_rush_dmg::CountTargets, EFFECT_0, TARGET_UNIT_RECT_CASTER_ENEMY);
        BeforeCast += SpellCastFn(spell_dh_fel_rush_dmg::BeforeSCast);
        OnEffectHitTarget += SpellEffectFn(spell_dh_fel_rush_dmg::HandleDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};
/// ID: 328725 Mortal Dance
class spell_mortal_dance : public AuraScript
{
    PrepareAuraScript(spell_mortal_dance);

    enum MortalDance
    {
        DeathSweep = 210152,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetActor())
            return false;
        if (!eventInfo.GetActionTarget())
            return false;

        if (!eventInfo.GetSpellInfo())
            return false;

        return eventInfo.GetSpellInfo()->Id == SPELL_DH_BLADE_DANCE || eventInfo.GetSpellInfo()->Id == DeathSweep;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_mortal_dance::CheckProc);
    }
};

void AddSC_demon_hunter_spell_scripts()
{
    new spell_dh_annihilation();
    new spell_dh_annihilation_damage();
    RegisterSpellScript(spell_dh_blade_dance_first_target);
    RegisterSpellScript(spell_dh_blade_dance);    
    new spell_dh_blade_turning();
    //new spell_dh_bloodlet();
    //new spell_dh_chaos_strike();
    new spell_dh_consume_soul();
    RegisterSpellScript(spell_dh_consume_soul_vengeance);
    new spell_dh_darkness_absorb();
    new spell_dh_demon_blades();
	RegisterSpellScript(spell_dh_demon_spikes);
	RegisterSpellScript(spell_dh_demon_spikes_buff);
    RegisterSpellScript(spell_dh_demonic_appetite);
    new spell_dh_eye_beam();
    new spell_dh_eye_beam_trigger();
    new spell_dh_fel_barrage();
    new spell_dh_fel_barrage_aura();
    new spell_dh_fel_barrage_damage();
    new spell_dh_fel_devastation();
    new spell_dh_fel_eruption();
    new spell_dh_fel_mastery();
    new spell_dh_fel_rush();
    new spell_dh_fel_rush_dash();
    RegisterSpellScript(spell_dh_fiery_brand);
    RegisterSpellScript(spell_dh_fiery_brand_dot);
    RegisterSpellScript(spell_dh_fracture);
    RegisterSpellScript(aura_dh_fraility);
    new spell_dh_glide();
    new spell_dh_immolation_aura();
    RegisterSpellScript(spell_dh_immolation_aura_damage);
    RegisterSpellScript(spell_dh_immolation_aura_dmg);
    RegisterSpellScript(spell_dh_infernal_strike);
    RegisterSpellScript(spell_dh_last_resort);    
    new spell_dh_master_of_the_glaive();
    new spell_dh_metamorphosis();
    new spell_dh_metamorphosis_buffs_veng();
    RegisterSpellAndAuraScriptPair(spell_dh_metamorphosis_immunity, aura_dh_metamorphosis_immunity);
    //new spell_dh_nemesis();
    new spell_dh_nether_bond();
    new spell_dh_nether_bond_periodic();
    new spell_dh_razor_spikes();
    RegisterSpellScript(spell_dh_shattered_souls);
    RegisterSpellScript(spell_dh_shear_proc);
    RegisterSpellScript(spell_dh_sigil_of_misery_fear);
    RegisterSpellScript(spell_dh_soul_barrier);
    new spell_dh_soul_cleave();
    new spell_dh_soul_cleave_damage();
    RegisterSpellScript(spell_dh_spirit_bomb);
    RegisterSpellScript(spell_dh_spirit_bomb_damage);
    RegisterSpellScript(spell_dh_demon_bite_insatiable_hunger);
    new spell_dh_vengeful_retreat_fury_refiller();
    RegisterSpellScript(spell_dh_vengeful_retreat_trigger);
    RegisterSpellScript(spell_dh_felblade);
    RegisterSpellScript(aura_dh_chaos_cleave);
    RegisterSpellScript(spell_talent_dh_trail_of_ruin_aura);
	RegisterSpellScript(aura_dh_chaos_brand);
	RegisterSpellScript(aura_dh_felblade);
	RegisterSpellScript(aura_dh_glimpse);
	RegisterSpellScript(aura_dh_solitude);
	RegisterSpellScript(aura_dh_eye_of_leotheras);
    RegisterSpellScript(aura_dh_demonic_origins);
    RegisterSpellScript(aura_dh_metamorphosis_buff);
    RegisterSpellScript(spell_dh_mana_break);
	RegisterSpellScript(aura_jagged_spikes_aura);
	RegisterSpellScript(aura_dh_cleansed_by_flame);
    RegisterSpellScript(aura_dh_imprision);
    RegisterSpellScript(spell_dh_disrupt_energize);
    RegisterSpellScript(spell_dh_consume_magic);
    RegisterSpellScript(spell_dh_metamorphosis_stun);
    RegisterSpellScript(spell_dh_eye_beam_damage);
    RegisterSpellScript(spell_dh_vengegul_retreat);
    RegisterSpellScript(spell_dh_reverse_magic);
    RegisterSpellScript(spell_dh_void_reaver);
    RegisterSpellScript(spell_dh_fel_lance);
    RegisterSpellScript(spell_dh_chaos_nova);
    RegisterSpellScript(spell_dh_vengeance_shatter_soul);
    RegisterSpellScript(aura_dh_vengeance_sigil_of_flame);
    RegisterSpellScript(spell_dh_the_hunt);
    RegisterSpellScript(spell_dh_chaos_strike);
    RegisterSpellScript(spell_dh_serrated_glaive);
    RegisterSpellScript(spell_dh_essence_break);
    RegisterSpellScript(spell_dh_fel_rush_dmg);
    RegisterSpellScript(spell_dh_disrupt);
    RegisterSpellScript(spell_mortal_dance);
    RegisterSpellScript(spell_infernal_strike_jump);

    /// AreaTrigger Scripts
    RegisterAreaTriggerAI(at_dh_darkness);
    RegisterAreaTriggerAI(at_dh_shattered_souls);
    RegisterAreaTriggerAI(at_dh_shattered_souls_lesser);
    RegisterAreaTriggerAI(at_dh_sigil_of_chains);
    RegisterAreaTriggerAI(at_dh_sigil_of_flame);
    RegisterAreaTriggerAI(at_dh_sigil_of_silence);
    RegisterAreaTriggerAI(at_dh_sigil_of_misery);
    RegisterAreaTriggerAI(at_dh_mana_rift);


    /// Custom NPC scripts
   // new npc_dh_spell_trainer();

    // Playerscript
    new dh_playerscript();
}
