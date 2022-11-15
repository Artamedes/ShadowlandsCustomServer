#include "SpellFormulaOverride.h"
#include "DatabaseEnv.h"
#include "WorldDatabase.h"
#include "GossipDef.h"
#include "ScriptedGossip.h"
#include "Chat.h"
#include "CustomObjectMgr.h"
#include "SmartEnum.h"
#include <sstream>

void SpellFormulaOverride::LoadFromDB()
{
    QueryResult result = WorldDatabase.Query("SELECT SpellID, EffectIndex, BonusCoefficient, BonusCoefficientFromAP, PvpMultiplierMod FROM z_spell_fixes");

    if (!result)
        return;

    do
    {
        Field* fields = result->Fetch();

        uint32 spellId              = fields[0].GetUInt32();
        uint32 effectIndex          = fields[1].GetUInt32();
        float bonusCoeff            = fields[2].GetFloat();
        float bonusCoeffFromAP      = fields[3].GetFloat();
        float bonusPvpMultiplierMod = fields[4].GetFloat();

        SpellMgr::ApplySpellFix({ spellId }, [&](SpellInfo* info)
        {
            SpellMgr::ApplySpellEffectFix(info, static_cast<SpellEffIndex>(effectIndex), [&](SpellEffectInfo* info)
            {
                if (bonusCoeff > 0.0f)
                    info->BonusCoefficient = bonusCoeff;
                if (bonusCoeffFromAP > 0.0f)
                    info->BonusCoefficientFromAP = bonusCoeffFromAP;
                if (bonusPvpMultiplierMod > 0.0f)
                    info->PvpMultiplierMod = bonusPvpMultiplierMod;
            });
        });

    } while (result->NextRow());
}

void SpellFormulaOverride::AddEntryToDB(uint32 SpellId, SpellEffIndex EffectIndex, Player* player)
{
    auto spellInfo = sSpellMgr->GetSpellInfo(SpellId);
    if (!spellInfo)
        return;

    auto effInfo = spellInfo->GetEffectPtr(EffectIndex);
    if (!effInfo)
        return;

    std::ostringstream ss;

    ss << player->GetName() << " (" << player->GetSession()->GetAccountName() << ")";

    auto stmt = WorldDatabase.GetPreparedStatement(WORLD_REP_Z_SPELL_FIX);

    stmt->setUInt32(0, spellInfo->Id);
    stmt->setUInt32(1, EffectIndex);
    stmt->setFloat(2, effInfo->BonusCoefficient);
    stmt->setFloat(3, effInfo->BonusCoefficientFromAP);
    stmt->setFloat(4, effInfo->PvpMultiplierMod);
    stmt->setString(5, ss.str());

    WorldDatabase.Execute(stmt);
}

void SpellFormulaOverride::DeleteEntryFromDB(uint32 SpellId, SpellEffIndex EffectIndex)
{
    WorldDatabase.PExecute("DELETE FROM z_spell_fixes WHERE SpellId = %u AND EffectIndex = %u",
        SpellId,
        static_cast<uint32>(EffectIndex));
}

bool SpellFormulaOverride::CanOverrideEffect(SpellEffectInfo const& eff)
{
    switch (eff.Effect)
    {
        case SpellEffectName::SPELL_EFFECT_WEAPON_DAMAGE:
        case SpellEffectName::SPELL_EFFECT_SCHOOL_DAMAGE:
        case SpellEffectName::SPELL_EFFECT_WEAPON_DAMAGE_NOSCHOOL:
        case SpellEffectName::SPELL_EFFECT_NORMALIZED_WEAPON_DMG:
        case SpellEffectName::SPELL_EFFECT_WEAPON_PERCENT_DAMAGE:
        case SpellEffectName::SPELL_EFFECT_POWER_DRAIN:
        case SpellEffectName::SPELL_EFFECT_HEALTH_LEECH:
        case SpellEffectName::SPELL_EFFECT_HEAL:
        case SpellEffectName::SPELL_EFFECT_HEAL_PCT:
        case SpellEffectName::SPELL_EFFECT_HEAL_MECHANICAL:
            return true;
        default:
            break;
    }

    switch (eff.ApplyAuraName)
    {
        case AuraType::SPELL_AURA_PERIODIC_DAMAGE:
        case AuraType::SPELL_AURA_PERIODIC_DAMAGE_PERCENT:
        case AuraType::SPELL_AURA_PERIODIC_LEECH:
        case AuraType::SPELL_AURA_PERIODIC_HEAL:
        case AuraType::SPELL_AURA_OBS_MOD_HEALTH:
        case AuraType::SPELL_AURA_PROC_TRIGGER_DAMAGE:
            return true;
        default:
            break;
    }

    return false;
}

bool SpellFormulaOverride::CanOverrideSpell(SpellInfo const* spellInfo)
{
    for (auto const& eff : spellInfo->GetEffects())
        if (CanOverrideEffect(eff))
            return true;

    return false;
}

void SpellFormulaOverride::DisplaySpellMap(Player* player, uint32 lowerBounds, uint32 upperBounds)
{
    std::ostringstream ss;

    ChrClassesEntry const* clsEntry = sChrClassesStore.LookupEntry(player->GetClass());
    auto family = clsEntry->SpellClassSet;

    uint32 count = 0;

    std::set<uint32> spellIds;

    for (auto& spell : player->GetSpellMap())
    {
        if (spell.second.active && !spell.second.disabled && spell.second.state != PLAYERSPELL_REMOVED)
        {
            if (auto spellInfo = sSpellMgr->GetSpellInfo(spell.first))
            {
                if (CanOverrideSpell(spellInfo))
                {
                    if (spellInfo->SpellFamilyName == family)
                    {
                        if (spellIds.count(spellInfo->Id))
                            continue;

                        spellIds.insert(spellInfo->Id);
                        ++count;


                        if (count < lowerBounds || count > upperBounds)
                            continue;

                        auto it = sCustomObjectMgr->_fileDataToPath.find(spellInfo->IconFileDataId);
                        if (it != sCustomObjectMgr->_fileDataToPath.end())
                            ss << "|T" << it->second << ":15:15:-23:0|t ";

                        ss << spellInfo->SpellName->Str[0] << " " << spellInfo->Id;

                        AddGossipItemFor(player, GossipOptionIcon::None, ss.str(), 0, 0, [player, spellInfo](std::string /*callback*/)
                        {
                            sSpellFormulaOverride->CreateMenuForSpell(player, spellInfo);
                        });

                        ss.clear();
                        ss.str("");
                    }
                }

                // Check SPELL_AURA_PERIODIC_TRIGGER_SPELL and SPELL_EFFECT_TRIGGER_SPELL
                // can check w/ TriggerSpell
                for (auto const& eff : spellInfo->GetEffects())
                {
                    if (eff.TriggerSpell)
                    {
                        auto spellInfo2 = sSpellMgr->GetSpellInfo(eff.TriggerSpell);
                        if (spellInfo2 && CanOverrideSpell(spellInfo2))
                        {
                            if (spellInfo2->SpellFamilyName == family)
                            {
                                if (spellIds.count(spellInfo2->Id))
                                    continue;

                                spellIds.insert(spellInfo2->Id);

                                ++count;

                                if (count < lowerBounds || count > upperBounds)
                                    continue;

                                auto it = sCustomObjectMgr->_fileDataToPath.find(spellInfo2->IconFileDataId);
                                if (it != sCustomObjectMgr->_fileDataToPath.end())
                                    ss << "|T" << it->second << ":15:15:-23:0|t ";

                                ss << spellInfo2->SpellName->Str[0] << " " << spellInfo2->Id << " (Trigger)";

                                AddGossipItemFor(player, GossipOptionIcon::None, ss.str(), 0, 0, [player, spellInfo2](std::string /*callback*/)
                                {
                                    sSpellFormulaOverride->CreateMenuForSpell(player, spellInfo2);
                                });

                                ss.clear();
                                ss.str("");
                            }
                        }
                    }
                }
            }
        }
    }

    if (lowerBounds > 0)
    {
        AddGossipItemFor(player, GossipOptionIcon::None, "<-----", 0, 0, [player, lowerBounds, upperBounds](std::string /*callback*/)
        {
            sSpellFormulaOverride->CreateMenu(player, lowerBounds - 20, upperBounds - 20);
        });
    }

    if (count > upperBounds)
    {
        AddGossipItemFor(player, GossipOptionIcon::None, "----->", 0, 0, [player, lowerBounds, upperBounds](std::string /*callback*/)
        {
            sSpellFormulaOverride->CreateMenu(player, lowerBounds + 20, upperBounds + 20);
        });
    }
}

void SpellFormulaOverride::CreateMenu(Player* player, uint32 lowerBounds /*= 0*/, uint32 upperBounds /*= 20*/)
{
    ClearGossipMenuFor(player);
    AddGossipItemFor(player, GossipOptionIcon::None, "Input SpellId", 0, 0, "", 0, true, [player](std::string callback)
    {
        sSpellFormulaOverride->HandleInputSpellId(player, callback);
    });
    DisplaySpellMap(player, lowerBounds, upperBounds);
    SendGossipMenuFor(player, 1, player);
}

void SpellFormulaOverride::CreateMenuForSpell(Player* player, SpellInfo const* spellInfo)
{
    ClearGossipMenuFor(player);

    AddGossipItemFor(player, GossipOptionIcon::None, "Input SpellId", 0, 0, "", 0, true, [player](std::string callback)
    {
        sSpellFormulaOverride->HandleInputSpellId(player, callback);
    });

    std::ostringstream ss;

    auto it = sCustomObjectMgr->_fileDataToPath.find(spellInfo->IconFileDataId);
    if (it != sCustomObjectMgr->_fileDataToPath.end())
        ss << "|T" << it->second << ":15:15:-23:0|t ";

    ss << spellInfo->SpellName->Str[0] << " |cffFF0000" << spellInfo->Id;

    AddGossipItemFor(player, GossipOptionIcon::None, ss.str(), 0, 0, [player, spellInfo](std::string /*callback*/)
    {
        sSpellFormulaOverride->CreateMenuForSpell(player, spellInfo);
    });

    ss.clear();
    ss.str("");

    bool hasScripts = false;

    SpellScriptsBounds bounds = sObjectMgr->GetSpellScriptsBounds(spellInfo->Id);
    for (auto itr = bounds.first; itr != bounds.second; ++itr)
    {
        // When the script is disabled continue with the next one
        if (!itr->second.second)
            continue;

        SpellScriptLoader* tmpscript = sScriptMgr->GetSpellScriptLoader(itr->second.first);
        if (!tmpscript)
            continue;

        if (hasScripts)
            ss << "\n";

        ss << tmpscript->GetName();
        hasScripts = true;
    }

    if (hasScripts)
    {
        AddGossipItemFor(player, GossipOptionIcon::None, ss.str(), 0, 0, [player, spellInfo](std::string /*callback*/)
        {
            sSpellFormulaOverride->CreateMenuForSpell(player, spellInfo);
        });

        ss.clear();
        ss.str("");
    }

    for (auto const& eff : spellInfo->GetEffects())
    {
        if (CanOverrideEffect(eff))
        {
            ss << "[" << EnumUtils::ToString(eff.EffectIndex).Title << "] ";

            if (eff.ApplyAuraName != AuraType::SPELL_AURA_NONE)
                ss << "[" << EnumUtils::ToString(eff.ApplyAuraName).Title << "] ";
            else
                ss << "[" << EnumUtils::ToString(eff.Effect).Title << "] ";

            AddGossipItemFor(player, GossipOptionIcon::None, ss.str(), 0, 0, [player, spellInfo, eff](std::string /*callback*/)
            {
                sSpellFormulaOverride->CreateMenuForEffect(player, spellInfo->GetEffectPtr(eff.EffectIndex), spellInfo);
            });

            ss.clear();
            ss.str("");
        }
    }

    AddGossipItemFor(player, GossipOptionIcon::None, "Back", 0, 0, [player](std::string /*callback*/)
    {
        sSpellFormulaOverride->CreateMenu(player);
    });

    SendGossipMenuFor(player, 1, player);
}

void SpellFormulaOverride::CreateMenuForEffect(Player* player, SpellEffectInfo const* eff, SpellInfo const* spellInfo)
{
    ClearGossipMenuFor(player);

    std::ostringstream ss;

    auto it = sCustomObjectMgr->_fileDataToPath.find(spellInfo->IconFileDataId);
    if (it != sCustomObjectMgr->_fileDataToPath.end())
        ss << "|T" << it->second << ":15:15:-23:0|t ";

    ss << spellInfo->SpellName->Str[0] << " |cffFF0000" << spellInfo->Id;

    auto spellId = spellInfo->Id;

    AddGossipItemFor(player, GossipOptionIcon::None, ss.str(), 0, 0, [player, eff, spellInfo](std::string /*callback*/)
    {
        sSpellFormulaOverride->CreateMenuForEffect(player, eff, spellInfo);
    });

    ss.clear();
    ss.str("");

    ss << "[" << EnumUtils::ToString(eff->EffectIndex).Title << "] ";

    if (eff->ApplyAuraName != AuraType::SPELL_AURA_NONE)
        ss << "[" << EnumUtils::ToString(eff->ApplyAuraName).Title << "] ";
    else
        ss << "[" << EnumUtils::ToString(eff->Effect).Title << "] ";

    AddGossipItemFor(player, GossipOptionIcon::None, ss.str(), 0, 0, [player, eff, spellInfo](std::string /*callback*/)
    {
        sSpellFormulaOverride->CreateMenuForEffect(player, eff, spellInfo);
    });

    ss.clear();
    ss.str("");
    ss << "BonusCoefficient: " << eff->BonusCoefficient;

    AddGossipItemFor(player, GossipOptionIcon::None, ss.str(), 0, 0, "", 0, true, [player, eff, spellInfo](std::string callback)
    {
        const_cast<SpellEffectInfo*>(eff)->BonusCoefficient = std::atof(callback.c_str());
        sSpellFormulaOverride->AddEntryToDB(spellInfo->Id, eff->EffectIndex, player);
        sSpellFormulaOverride->CreateMenuForEffect(player, eff, spellInfo);
    });

    ss.clear();
    ss.str("");
    ss << "BonusCoefficientFromAP: " << eff->BonusCoefficientFromAP;

    AddGossipItemFor(player, GossipOptionIcon::None, ss.str(), 0, 0, "", 0, true, [player, eff, spellInfo](std::string callback)
    {
        const_cast<SpellEffectInfo*>(eff)->BonusCoefficientFromAP = std::atof(callback.c_str());
        sSpellFormulaOverride->AddEntryToDB(spellInfo->Id, eff->EffectIndex, player);
        sSpellFormulaOverride->CreateMenuForEffect(player, eff, spellInfo);
    });

    ss.clear();
    ss.str("");
    ss << "PvpMultiplierMod: " << eff->PvpMultiplierMod;

    AddGossipItemFor(player, GossipOptionIcon::None, ss.str(), 0, 0, "", 0, true, [player, eff, spellInfo](std::string callback)
    {
        const_cast<SpellEffectInfo*>(eff)->PvpMultiplierMod = std::atof(callback.c_str());
        sSpellFormulaOverride->AddEntryToDB(spellInfo->Id, eff->EffectIndex, player);
        sSpellFormulaOverride->CreateMenuForEffect(player, eff, spellInfo);
    });

    AddGossipItemFor(player, GossipOptionIcon::None, "Back", 0, 0, [player, spellInfo](std::string /*callback*/)
    {
        sSpellFormulaOverride->CreateMenuForSpell(player, spellInfo);
    });
    SendGossipMenuFor(player, 1, player);
}

void SpellFormulaOverride::HandleInputSpellId(Player* player, std::string callback)
{
    uint32 spellId = std::atoi(callback.c_str());
    auto spellInfo = sSpellMgr->GetSpellInfo(spellId);
    if (!spellInfo)
    {
        ChatHandler(player).PSendSysMessage("%u not found!", spellId);
        CreateMenu(player);
        return;
    }

    CreateMenuForSpell(player, spellInfo);
}
