#include "AnimaPower.h"
#include "Containers.h"
#include "DB2Stores.h"
#include "GameObject.h"
#include "Player.h"
#include "QuestPackets.h"
#include "SpellInfo.h"
#include "SpellMgr.h"
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

        power->ResponseID = i;
        packet.Responses[i].ResponseIdentifier = i; ///< BLizz increments by 1 every time so this is wrong
        packet.Responses[i].ChoiceArtFileID = spellInfo->IconFileDataId;
        packet.Responses[i].Header = spellInfo->SpellName->Str[0]; ///< TODO:Implement locales
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

bool AnimaPowerChoice::GeneratePowers(Player* player)
{
    if (Rerolls == 0)
        return false;

    --Rerolls;

    uint32 totalPowers = urand(2, 3);

    ChrClassesEntry const* clsEntry = sChrClassesStore.LookupEntry(player->GetClass());
    auto family = clsEntry->SpellClassSet;

    for (int i = 0; i < totalPowers; ++i)
    {
        MawPowerEntry const* mawPower = nullptr;
        SpellInfo const* spellInfo = nullptr;
        while (true)
        {
            uint32 pig = urand(0, sMawPowerStore.GetNumRows());

            mawPower = sMawPowerStore.LookupEntry(pig);
            if (!mawPower)
                continue;

            if (mawPower->MawPowerRarityID == 0)
                continue;

            spellInfo = sSpellMgr->GetSpellInfo(mawPower->SpellID);
            if (!spellInfo)
                continue;

            if (spellInfo->RequiredAreasID != 6432)
                continue;

            if (spellInfo->SpellFamilyName == 0 || spellInfo->SpellFamilyName == family)
                break;
        }

        if (!mawPower)
            continue;

        auto rarityEntry = sMawPowerRarityStore.LookupEntry(mawPower->MawPowerRarityID);

        AnimaPower* power = new AnimaPower();

        power->MawPowerID = mawPower->ID;
        power->MaxStacks = spellInfo->StackAmount;
        power->Rarity = mawPower->MawPowerRarityID;
        power->RarityColor = rarityEntry ? rarityEntry->Color : -1;
        power->SpellID = spellInfo->Id;
        power->Unused901_2 = rarityEntry ? rarityEntry->Border : 0;
        // 3446881 - defense
        // 3446882 - offense
        // 3446883 - utility
        power->TypeArtFileID = 3446881;

        AddPower(power);
    }

    return true;
}
