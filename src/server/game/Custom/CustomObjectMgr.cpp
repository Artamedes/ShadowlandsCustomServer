#include "CustomObjectMgr.h"
#include "DatabaseEnv.h"
#include "DB2Stores.h"
#include "PlayerChallenge.h"
#include "Unit.h"
#include "SpellInfo.h"
#include "SpellFormulaOverride.h"
#include <boost/asio/thread_pool.hpp>
#include <boost/asio/post.hpp>

CustomObjectMgr::~CustomObjectMgr()
{
    for (auto& itr : _groupChallengeLevelInfo)
        delete itr.second;
    for (auto& itr : _soloChallengeLevelInfo)
        delete itr.second;
}

void CustomObjectMgr::LoadFromDB()
{
    LoadCustomSpellDmgs();
    LoadCustomScalingEntries();
    LoadCoinModels();
    LoadCustomTransmogVendorData();

    boost::asio::thread_pool pool;

    boost::asio::post(pool, [this]() {
        LoadFiledataData();
    });
    LoadCustomChallengeInfo();
    sSpellFormulaOverride->LoadFromDB();
}

void CustomObjectMgr::LoadCustomSpellDmgs()
{
    _customSpellDmgs.clear();
    auto result = WorldDatabase.Query("SELECT CreatureID, SpellID, Min, Max, PctModifier FROM z_custom_creature_spell_dmg");
    if (result)
    {
        do
        {
            Field* fields = result->Fetch();

            auto creatureId = fields[0].GetUInt32();
            auto spellId = fields[1].GetUInt32();
            auto min = fields[2].GetUInt32();
            auto max = fields[3].GetUInt32();
            auto pctModifier = fields[4].GetFloat();

            CustomDamage dmg;

            dmg.Min = min;
            dmg.Max = max;
            dmg.PctModifier = pctModifier;

            _customSpellDmgs[creatureId][spellId] = dmg;

        } while (result->NextRow());
    }
}

void CustomObjectMgr::LoadCustomScalingEntries()
{
    _customScalingEntries.clear();
    auto result = WorldDatabase.Query("SELECT Entry, HealthModifier, DamageModifier FROM z_custom_scaling_entries");
    if (result)
    {
        do
        {
            auto fields = result->Fetch();

            _customScalingEntries[fields[0].GetUInt32()] = { fields[1].GetFloat(), fields[2].GetFloat() };
        } while (result->NextRow());
    }
}

void CustomObjectMgr::LoadCoinModels()
{
    CoinModels.clear();
    auto result = WorldDatabase.Query("SELECT ID, ModelID, CreatureEntry FROM z_coin_models");
    if (result)
    {
        CoinModels.reserve(result->GetRowCount());
        do
        {
            Field* fields = result->Fetch();
            CoinModel model = { fields[0].GetUInt32(), fields[1].GetUInt32(), fields[2].GetUInt32() };
            CoinModels.emplace_back(model);
        } while (result->NextRow());
    }
}

void CustomObjectMgr::LoadCustomTransmogVendorData()
{
    _customTransmogVendorData.clear();
    auto result = WorldDatabase.Query("SELECT EntryID, TransmogSet, ClassMask, Flags, TransmogTokenCost, Icon FROM z_transmog_vendor_data");
    if (result)
    {
        do
        {
            Field* fields = result->Fetch();

            CustomTransmogVendor vendor;

            vendor.TransmogSet          = fields[1].GetUInt32();
            vendor.ClassMask            = fields[2].GetUInt32();
            vendor.Flags                = fields[3].GetUInt32();
            vendor.TransmogTokenCost    = fields[4].GetUInt32();
            vendor.Icon                 = fields[5].GetString();

            _customTransmogVendorData.insert({ fields[0].GetUInt32(), vendor});

        } while (result->NextRow());
    }
}

void CustomObjectMgr::LoadFiledataData()
{
    /// Pig or not?
    auto result = WorldDatabase.Query("SELECT FileDataID, FileName FROM z_filedata_data WHERE FileName like '%.blp%'");
    if (!result)
        return;

    do
    {
        auto fields = result->Fetch();

        _fileDataToPath[fields[0].GetUInt32()] = fields[1].GetString();
    } while (result->NextRow());
}

void CustomObjectMgr::LoadCustomChallengeInfo()
{
    for (auto& itr : _groupChallengeLevelInfo)
        delete itr.second;
    for (auto& itr : _soloChallengeLevelInfo)
        delete itr.second;

    _groupChallengeLevelInfo.clear();
    _soloChallengeLevelInfo.clear();
    _customChallengeDungeonsByKeystone.clear();

    if (auto result = WorldDatabase.Query("SELECT ChallengeLevel, HPScalingPerPlayer, DMGScalingPerPlayer FROM z_group_challenge_level_info"))
    {
        do
        {
            auto fields = result->Fetch();

            ChallengeLevelInfo* levelInfo = new ChallengeLevelInfo();
        
            levelInfo->BaseHPScaling       = fields[1].GetFloat();
            levelInfo->BaseDmgScaling      = fields[2].GetFloat();
            levelInfo->HPScalingPerPlayer  = fields[3].GetFloat();
            levelInfo->DMGScalingPerPlayer = fields[4].GetFloat();

            _groupChallengeLevelInfo[fields[0].GetUInt32()] = levelInfo;
        } while (result->NextRow());
    }

    if (auto result = WorldDatabase.Query("SELECT ChallengeLevel, HPScalingPerPlayer, DMGScalingPerPlayer FROM z_solo_challenge_level_info"))
    {
        do
        {
            auto fields = result->Fetch();

            ChallengeLevelInfo* levelInfo = new ChallengeLevelInfo();
        
            levelInfo->BaseHPScaling       = fields[1].GetFloat();
            levelInfo->BaseDmgScaling      = fields[2].GetFloat();
            levelInfo->HPScalingPerPlayer  = fields[3].GetFloat();
            levelInfo->DMGScalingPerPlayer = fields[4].GetFloat();

            _groupChallengeLevelInfo[fields[0].GetUInt32()] = levelInfo;
        } while (result->NextRow());
    }

    if (auto result = WorldDatabase.Query("SELECT Keystone, ChallengeID FROM z_custom_challenge_dungeons"))
    {
        do
        {
            auto fields = result->Fetch();

            if (sMapChallengeModeStore.LookupEntry(fields[1].GetUInt32()))
                _customChallengeDungeonsByKeystone[fields[0].GetUInt32()].push_back(fields[1].GetUInt32());

        } while (result->NextRow());
    }
}

void CustomObjectMgr::ModifySpellDmg(Unit* unit, SpellInfo const* spellInfo, uint32& damage)
{
    if (!unit->IsCreature())
        return;

    if (!spellInfo)
        return;

    auto entry = unit->GetEntry();

    auto itr = _customSpellDmgs.find(entry);
    if (itr == _customSpellDmgs.end())
        return;

    auto spellId = spellInfo->Id;
    auto itr2 = itr->second.find(spellId);
    if (itr2 == itr->second.end())
        return;

    auto const& customDamage = itr2->second;

    if (customDamage.Max > 0 && customDamage.Max >= customDamage.Min)
        damage = urand(customDamage.Min, customDamage.Max);

    if (customDamage.PctModifier > 0.0f)
        damage *= customDamage.PctModifier;
}

void CustomObjectMgr::GenerateCustomDungeonForKeystone(MythicKeystoneInfo* keystoneInfo)
{
    auto it = _customChallengeDungeonsByKeystone.find(keystoneInfo->KeystoneItemID);
    if (it == _customChallengeDungeonsByKeystone.end() || it->second.empty())
        return;

    if (it->second.size() == 1)
    {
        keystoneInfo->ID = it->second.back();
        return;
    }

    uint32 oldID = keystoneInfo->ID;
    while (oldID == keystoneInfo->ID)
    {
        keystoneInfo->ID = Trinity::Containers::SelectRandomContainerElement(it->second);
    }
}

void CustomObjectMgr::SetChallengeLevelInfoIfNeed(MythicKeystoneInfo* keystoneInfo, ChallengeLevelInfo* levelInfo)
{
    switch (keystoneInfo->Type)
    {
        case KeystoneType::Timewalking:
        case KeystoneType::Group:
        {
            auto it = _groupChallengeLevelInfo.find(keystoneInfo->Level);
            if (it != _groupChallengeLevelInfo.end())
                levelInfo = it->second;
            break;
        }
        case KeystoneType::Solo:
        {
            auto it = _soloChallengeLevelInfo.find(keystoneInfo->Level);
            if (it != _soloChallengeLevelInfo.end())
                levelInfo = it->second;
            break;
        }
    }
}
