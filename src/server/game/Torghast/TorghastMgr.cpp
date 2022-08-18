#include "Containers.h"
#include "TorghastMgr.h"
#include "DatabaseEnv.h"
#include "Player.h"

using namespace Torghast;

TorghastMgr::~TorghastMgr()
{
    for (auto power : _mawPowersDB)
        delete power;

    _mawPowersDB.clear();
    _mawPowersByNpcEntry.clear();
    _mawPowersByCovenant.clear();
    _mawPowersByClass.clear();
    _mawPowersByRarity.clear();
}

void TorghastMgr::LoadFromDB()
{
    auto result = WorldDatabase.Query("SELECT MawPowerId, ClassId, RarityID, CovenantID, RequiredFloor, RequiredNpc, RequiredAura, RequiredQuest FROM maw_power_list");
    if (!result)
        return;
    _mawPowersDB.reserve(result->GetRowCount());
    do
    {
        auto fields = result->Fetch();

        MawPowerDB* mawPower = new MawPowerDB();

        mawPower->MawPowerID     = fields[0].GetUInt32();
        mawPower->ClassID        = fields[1].GetUInt32();
        mawPower->RarityID       = static_cast<eMawPowerRarity>(fields[2].GetUInt32());
        mawPower->CovenantID     = fields[3].GetUInt32();
        mawPower->RequiredFloor  = fields[4].GetUInt32();
        mawPower->RequiredNpc    = fields[5].GetUInt32();
        mawPower->RequiredAura   = fields[6].GetUInt32();
        mawPower->RequiredQuest  = fields[7].GetUInt32();

        _mawPowersDB.emplace_back(mawPower);
        _mawPowersByNpcEntry.insert(std::make_pair(mawPower->RequiredNpc, mawPower));
        _mawPowersByCovenant.insert(std::make_pair(mawPower->CovenantID, mawPower));
        _mawPowersByClass.insert(std::make_pair(mawPower->ClassID, mawPower));
        _mawPowersByRarity.insert(std::make_pair(mawPower->RarityID, mawPower));
    } while (result->NextRow());
}

void TorghastMgr::ChooseMawPower(Player* player, std::vector<MawPowerDB*>& powers, uint32 amount, EnumFlag<MawPowerFlags> rarity /*= MawPowerFlags::None*/, uint32 RequiredNpc, bool classOnly /*= false*/)
{
    auto classId = player->GetClass();

    float RareChance = irand(0, 100);
    float EpicChance = irand(0, 100);

    float RequiredRareChance = 75.0f;
    float RequiredEpicChance = 90.0f;

    if (player->IsQuestRewarded(VenariUpgradesQuests::RitualPrismofFortune))
        RequiredEpicChance -= 10.0f;

    auto IsValidMawPower([&](MawPowerDB const* power) -> bool
    {
        if (power->ClassID && power->ClassID != classId)
            return false;

        if (classOnly && !power->ClassID)
            return false;

        if (power->CovenantID && player->m_playerData->CovenantID != power->CovenantID)
            return false;

        if (power->RequiredAura && !player->HasAura(power->RequiredAura))
            return false;

        if (power->RequiredQuest && !player->IsQuestRewarded(power->RequiredQuest))
            return false;

        if (rarity == MawPowerFlags::None)
        {
            switch (power->RarityID)
            {
                case eMawPowerRarity::Common:
                    break;
                case eMawPowerRarity::Uncommon:
                    break;
                case eMawPowerRarity::Rare:
                    if (RareChance < RequiredRareChance)
                        return false;
                    break;
                case eMawPowerRarity::Epic:
                    if (RareChance < RequiredEpicChance)
                        return false;
                    break;
                default:
                    break;
            }

            return true;
        }

        switch (power->RarityID)
        {
            case eMawPowerRarity::Common:
                return rarity.HasFlag(MawPowerFlags::Common);
            case eMawPowerRarity::Uncommon:
                return rarity.HasFlag(MawPowerFlags::Uncommon);
            case eMawPowerRarity::Rare:
                return rarity.HasFlag(MawPowerFlags::Rare);
            case eMawPowerRarity::Epic:
                return rarity.HasFlag(MawPowerFlags::Epic);
            default:
                return false;
        }
    });

    if (RequiredNpc != 0)
    {
        auto range = _mawPowersByNpcEntry.equal_range(RequiredNpc);
        for (auto it = range.first; it != range.second; ++it)
        {
            if (IsValidMawPower(it->second))
            {
                powers.push_back(it->second);
                amount--;
                if (!amount)
                    return;
            }
        }
    }

    while (amount)
    {
        auto power = Trinity::Containers::SelectRandomContainerElement(_mawPowersDB);

        if (std::find(powers.begin(), powers.end(), power) != powers.end())
            continue;

        if (IsValidMawPower(power))
        {
            powers.push_back(power);
            amount--;
            if (!amount)
                return;
        }
    }
}
