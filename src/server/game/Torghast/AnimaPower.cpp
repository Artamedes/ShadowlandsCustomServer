#include "AnimaPower.h"
#include "Containers.h"
#include "DB2Stores.h"
#include "GameObject.h"
#include "Player.h"
#include "QuestPackets.h"
#include "SpellInfo.h"
#include "SpellMgr.h"
#include "Chat.h"
#include <sstream>

AnimaPowerChoice::AnimaPowerChoice(Player* player, GameObject* go) : _playerGuid(player->GetGUID()), _goGuid(go->GetGUID())
{
}

AnimaPowerChoice::~AnimaPowerChoice()
{
    for (AnimaPower* power : Powers)
        delete power;
}

void AnimaPowerChoice::BuildPacket(WorldPackets::Quest::DisplayPlayerChoice& packet)
{
    packet.ChoiceID = 573;
    packet.SenderGUID = _goGuid;
    packet.NumRerolls = Rerolls;
    packet.SoundKitID = 168437;
    packet.UiTextureKitID = 5275;
    packet.Question = "What shape should the Anima take?";
    packet.PendingChoiceText = "Pending Anima Power";

    packet.Responses.resize(Powers.size());

    std::ostringstream ss;

    for (size_t i = 0; i < Powers.size(); ++i)
    {
        auto power = Powers[i];

        auto spellInfo = sSpellMgr->GetSpellInfo(power->SpellID);
        if (!spellInfo)
            continue;

        ss << "$" << power->SpellID << "s";

        power->ResponseID = i + 1;
        packet.Responses[i].ResponseIdentifier = i + 1; ///< BLizz increments by 1 every time so this is wrong
        packet.Responses[i].ChoiceArtFileID = spellInfo->IconFileDataId;
        packet.Responses[i].Header = power->Name; ///< TODO:Implement locales
        packet.Responses[i].Description = ss.str();

        packet.Responses[i].MawPower = WorldPackets::Quest::PlayerChoiceResponseMawPower();

        packet.Responses[i].MawPower->Unused901_1   = power->Unused901_1;
        packet.Responses[i].MawPower->TypeArtFileID = power->TypeArtFileID;
        packet.Responses[i].MawPower->Unused901_2   = power->Unused901_2;
        packet.Responses[i].MawPower->SpellID       = power->SpellID;
        packet.Responses[i].MawPower->MaxStacks     = power->MaxStacks;
        packet.Responses[i].MawPower->Rarity        = power->Rarity;
        packet.Responses[i].MawPower->RarityColor   = power->RarityColor;

        ss.str("");
        ss.clear();
    }
}

bool AnimaPowerChoice::GeneratePowers(Player* player, uint32 mawPowerId /*= 0*/)
{
    if (Rerolls == 0 && !mawPowerId)
        return false;

    if (!mawPowerId)
        --Rerolls;

    /// Remove old powers
    for (AnimaPower* power : Powers)
        delete power;

    Powers.clear();

    // TODO: CLEANUP PIG
    uint32 totalPowers = urand(2, 3);

    ChrClassesEntry const* clsEntry = sChrClassesStore.LookupEntry(player->GetClass());
    auto family = clsEntry->SpellClassSet;

    static int index = 0;

    for (int i = 0; i < 8; ++i)
    {
        MawPowerEntry const* mawPower = nullptr;

        QueryResult result = WorldDatabase.PQuery("SELECT MawPowerID FROM maw_power_list WHERE MawPowerID = %u AND ClassID = 0", mawPowerId ? mawPowerId : index);
        if (result)
            ++index;

        while (!result)
        {
            result = WorldDatabase.PQuery("SELECT MawPowerID FROM maw_power_list WHERE MawPowerID = %u AND ClassID = 0", index);
            ++index;

            if (index > 2000)
                break;
        }
        if (result)
        {
            mawPower = sMawPowerStore.LookupEntry(result->Fetch()[0].GetUInt32());
        }

        if (!mawPower)
            continue;

        auto spellInfo = sSpellMgr->GetSpellInfo(mawPower->SpellID);
        if (!spellInfo)
            continue;

        auto rarityEntry = sMawPowerRarityStore.LookupEntry(mawPower->MawPowerRarityID);

        AnimaPower* power = new AnimaPower();

        power->MawPowerID = mawPower->ID;
        power->MaxStacks = spellInfo->StackAmount ? spellInfo->StackAmount : 1;
        power->Rarity = mawPower->MawPowerRarityID - 1;
        power->RarityColor = rarityEntry ? rarityEntry->Color : -1;
        power->SpellID = spellInfo->Id;
        power->Unused901_2 = rarityEntry ? rarityEntry->Border : 0;
        // 3446881 - defense
        // 3446882 - offense
        // 3446883 - utility
        power->TypeArtFileID = 3446881;

        AddPower(power);

        power->Name = spellInfo->SpellName->Str[player->GetSession()->GetSessionDbcLocale()];

        ChatHandler(player).PSendSysMessage("%s %u %u", spellInfo->SpellName->Str[0], power->SpellID, power->MawPowerID);
    }

    return true;
}
