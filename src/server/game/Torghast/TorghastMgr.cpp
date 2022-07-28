#include "TorghastMgr.h"
#include "DatabaseEnv.h"
#include "Player.h"

void TorghastMgr::LoadFromDB()
{
    auto result = WorldDatabase.Query("SELECT MawPowerId, ClassId, RarityID, CovenantID, RequiredFloor, RequiredNpc FROM maw_power_list");
    if (!result)
        return;

    do
    {
        auto fields = result->Fetch();

        MawPowerDB mawPower;

        mawPower.MawPowerID    = fields[0].GetUInt32();
        mawPower.ClassID       = fields[1].GetUInt32();
        mawPower.RarityID      = static_cast<eMawPowerRarity>(fields[2].GetUInt32());
        mawPower.CovenantID    = fields[3].GetUInt32();
        mawPower.RequiredFloor = fields[4].GetUInt32();
        mawPower.RequiredNpc   = fields[5].GetUInt32();

        _mawPowersDB[mawPower.MawPowerID] = mawPower;
        _mawPowersByNpcEntry.insert(std::make_pair(mawPower.RequiredNpc, mawPower));
        _mawPowersByCovenant.insert(std::make_pair(mawPower.CovenantID, mawPower));
        _mawPowersByClass.insert(std::make_pair(mawPower.ClassID, mawPower));
        _mawPowersByRarity.insert(std::make_pair(mawPower.RarityID, mawPower));
    } while (result->NextRow());
}

void TorghastMgr::ChooseMawPower(Player* player, std::vector<MawPowerDB>& powers, uint32 amount, eMawPowerRarity rarity, uint32 RequiredNpc, bool classOnly /*= false*/)
{
    auto classId = player->GetClass();

    auto IsValidMawPower([&](MawPowerDB& power) -> bool
    {
        if (power.ClassID && power.ClassID != classId)

        return true;
    });

    if (rarity != eMawPowerRarity::Any)
    {

    }

    for (auto it = _mawPowersDB.begin(); it != _mawPowersDB.end(); ++it)
    {

    }
}
