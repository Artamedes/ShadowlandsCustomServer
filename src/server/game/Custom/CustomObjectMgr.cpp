#include "CustomObjectMgr.h"
#include "DatabaseEnv.h"
#include "Unit.h"
#include "SpellInfo.h"

void CustomObjectMgr::LoadFromDB()
{
    LoadCustomSpellDmgs();
    LoadCustomScalingEntries();
    LoadCoinModels();
    LoadCustomTransmogVendorData();
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
