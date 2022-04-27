#include "ChallengeMode.h"
#include "Containers.h"
#include "DatabaseEnv.h"
#include "PlayerChallenge.h"
#include "Player.h"
#include "Map.h"
#include "Item.h"
#include "World.h"

// TODO: move to db
constexpr uint32 CustomMiniDungeonsForChallenge[] = { 30002, };
constexpr uint32 CustomDungeonsForChallenge[] = { 251, 245, 169 };

void MythicKeystoneInfo::GenerateNewDungeon()
{
    uint16 oldID = ID;
    while (oldID == ID)
    {
        if (Type == KeystoneType::Normal)
            ID = Trinity::Containers::SelectRandomContainerElement(CustomDungeonsForChallenge);
        else if (Type == KeystoneType::Mini)
        {
            ID = Trinity::Containers::SelectRandomContainerElement(CustomMiniDungeonsForChallenge);
            break; // remove this break when more dungs are added.
        }
        else
            break;
    }
}

PlayerChallenge::PlayerChallenge(Player* player) : _player(player)
{
}

bool PlayerChallenge::InitMythicKeystone(Item* item)
{
    auto keystoneInfo = GetKeystoneInfo(item);
    if (!keystoneInfo)
        return true;

    if (!keystoneInfo->IsActive())
        return false;

    keystoneInfo->Affix = sWorld->getWorldState(WS_CHALLENGE_AFFIXE1_RESET_TIME);
    keystoneInfo->Affix1 = sWorld->getWorldState(WS_CHALLENGE_AFFIXE2_RESET_TIME);
    keystoneInfo->Affix2 = sWorld->getWorldState(WS_CHALLENGE_AFFIXE3_RESET_TIME);
    keystoneInfo->Affix3 = sWorld->getWorldState(WS_CHALLENGE_AFFIXE4_RESET_TIME);

    if (!item->GetModifier(ITEM_MODIFIER_CHALLENGE_MAP_CHALLENGE_MODE_ID))
        item->SetModifier(ITEM_MODIFIER_CHALLENGE_MAP_CHALLENGE_MODE_ID, keystoneInfo->ID);

    item->SetModifier(ITEM_MODIFIER_CHALLENGE_KEYSTONE_LEVEL, keystoneInfo->Level);

    if (keystoneInfo->Level > MYTHIC_LEVEL_1)
        item->SetModifier(ITEM_MODIFIER_CHALLENGE_KEYSTONE_AFFIX_ID_1, keystoneInfo->Affix);
    if (keystoneInfo->Level > MYTHIC_LEVEL_3)
        item->SetModifier(ITEM_MODIFIER_CHALLENGE_KEYSTONE_AFFIX_ID_2, keystoneInfo->Affix1);
    if (keystoneInfo->Level > MYTHIC_LEVEL_6)
        item->SetModifier(ITEM_MODIFIER_CHALLENGE_KEYSTONE_AFFIX_ID_3, keystoneInfo->Affix2);
    if (keystoneInfo->Level > MYTHIC_LEVEL_9)
        item->SetModifier(ITEM_MODIFIER_CHALLENGE_KEYSTONE_AFFIX_ID_4, keystoneInfo->Affix3);

    return true;
}

void PlayerChallenge::CreateMythicKeystone(Item* item)
{
    auto keystoneInfo = GetKeystoneInfo(item, true);
    if (!keystoneInfo)
        return;

    if (!keystoneInfo->IsActive())
        keystoneInfo->needSave = true;
    else
        keystoneInfo->needUpdate = true;

    if (!keystoneInfo->Level)
        keystoneInfo->Level = MYTHIC_LEVEL_2;

    item->SetModifier(ITEM_MODIFIER_CHALLENGE_KEYSTONE_LEVEL, keystoneInfo->Level);
    item->SetExpiration(sWorld->getNextChallengeKeyReset() - time(nullptr));

    if (!item->GetModifier(ITEM_MODIFIER_CHALLENGE_MAP_CHALLENGE_MODE_ID))
    {
        keystoneInfo->GenerateNewDungeon();
        item->SetModifier(ITEM_MODIFIER_CHALLENGE_MAP_CHALLENGE_MODE_ID, keystoneInfo->ID);
    }

    keystoneInfo->Affix = sWorld->getWorldState(WS_CHALLENGE_AFFIXE1_RESET_TIME);
    keystoneInfo->Affix1 = sWorld->getWorldState(WS_CHALLENGE_AFFIXE2_RESET_TIME);
    keystoneInfo->Affix2 = sWorld->getWorldState(WS_CHALLENGE_AFFIXE3_RESET_TIME);
    keystoneInfo->Affix3 = sWorld->getWorldState(WS_CHALLENGE_AFFIXE4_RESET_TIME);

    if (keystoneInfo->Level > MYTHIC_LEVEL_1)
        item->SetModifier(ITEM_MODIFIER_CHALLENGE_KEYSTONE_AFFIX_ID_1, keystoneInfo->Affix);
    if (keystoneInfo->Level > MYTHIC_LEVEL_3)
        item->SetModifier(ITEM_MODIFIER_CHALLENGE_KEYSTONE_AFFIX_ID_2, keystoneInfo->Affix1);
    if (keystoneInfo->Level > MYTHIC_LEVEL_6)
        item->SetModifier(ITEM_MODIFIER_CHALLENGE_KEYSTONE_AFFIX_ID_3, keystoneInfo->Affix2);
    if (keystoneInfo->Level > MYTHIC_LEVEL_9)
        item->SetModifier(ITEM_MODIFIER_CHALLENGE_KEYSTONE_AFFIX_ID_4, keystoneInfo->Affix3);

    keystoneInfo->ID = item->GetModifier(ITEM_MODIFIER_CHALLENGE_MAP_CHALLENGE_MODE_ID);
    keystoneInfo->timeReset = sWorld->getNextChallengeKeyReset();

    item->SetState(ITEM_CHANGED, _player);
}

void PlayerChallenge::UpdateMythicKeystone(Item* item)
{
    auto keystoneInfo = GetKeystoneInfo(item);
    if (!keystoneInfo)
        return;

    keystoneInfo->ID = item->GetModifier(ITEM_MODIFIER_CHALLENGE_MAP_CHALLENGE_MODE_ID);
    keystoneInfo->Level = item->GetModifier(ITEM_MODIFIER_CHALLENGE_KEYSTONE_LEVEL);

    keystoneInfo->Affix = sWorld->getWorldState(WS_CHALLENGE_AFFIXE1_RESET_TIME);
    keystoneInfo->Affix1 = sWorld->getWorldState(WS_CHALLENGE_AFFIXE2_RESET_TIME);
    keystoneInfo->Affix2 = sWorld->getWorldState(WS_CHALLENGE_AFFIXE3_RESET_TIME);
    keystoneInfo->Affix3 = sWorld->getWorldState(WS_CHALLENGE_AFFIXE4_RESET_TIME);

    if (keystoneInfo->Level > MYTHIC_LEVEL_1)
        item->SetModifier(ITEM_MODIFIER_CHALLENGE_KEYSTONE_AFFIX_ID_1, keystoneInfo->Affix);
    if (keystoneInfo->Level > MYTHIC_LEVEL_3)
        item->SetModifier(ITEM_MODIFIER_CHALLENGE_KEYSTONE_AFFIX_ID_2, keystoneInfo->Affix1);
    if (keystoneInfo->Level > MYTHIC_LEVEL_6)
        item->SetModifier(ITEM_MODIFIER_CHALLENGE_KEYSTONE_AFFIX_ID_3, keystoneInfo->Affix2);
    if (keystoneInfo->Level > MYTHIC_LEVEL_9)
        item->SetModifier(ITEM_MODIFIER_CHALLENGE_KEYSTONE_AFFIX_ID_4, keystoneInfo->Affix3);

    keystoneInfo->InstanceID = 0;
    keystoneInfo->needUpdate = true;
}

void PlayerChallenge::ResetMythicKeystone()
{
    _player->DestroyItemCount(MythicKeystone, 100, true, false);
    _player->DestroyItemCount(MiniMythicKeystone, 100, true, false);
    if (MainKeystone)
        MainKeystone.reset();
    if (MiniKeystone)
        MiniKeystone.reset();
}

void PlayerChallenge::ResetMythicKeystoneTo(Item* item, uint32 challengeLevel, bool runRand)
{
    auto keystoneInfo = GetKeystoneInfo(item);
    if (!keystoneInfo)
        return;

    if (challengeLevel > MYTHIC_LEVEL_2)
        challengeLevel -= 1;

    keystoneInfo->challengeEntry = nullptr;
    if (challengeLevel >= MYTHIC_LEVEL_2)
    {
        keystoneInfo->Level = challengeLevel;
        if (runRand)
        {
            keystoneInfo->GenerateNewDungeon();
        }
        keystoneInfo->needUpdate = true;

        if (item)
        {
            item->SetModifier(ITEM_MODIFIER_CHALLENGE_KEYSTONE_LEVEL, challengeLevel);
            item->SetModifier(ITEM_MODIFIER_CHALLENGE_MAP_CHALLENGE_MODE_ID, keystoneInfo->ID);
            UpdateMythicKeystone(item);
            item->SetState(ITEM_CHANGED, _player);
        }
        return;
    }

    if (!keystoneInfo->IsActive())
        return;

    keystoneInfo->ID = 0;
    keystoneInfo->Level = MYTHIC_LEVEL_2;
    keystoneInfo->Affix = 0;
    keystoneInfo->Affix1 = 0;
    keystoneInfo->Affix2 = 0;
    keystoneInfo->Affix3 = 0;
    keystoneInfo->KeyIsCharded = 1;
    keystoneInfo->InstanceID = 0;
    _player->DestroyItemCount(ITEM_MYTHIC_KEYSTONE, 100, true, false);
}

void PlayerChallenge::_LoadMythicKeystones(PreparedQueryResult result)
{
    if (!result)
        return;

    do
    {
        Field* fields = result->Fetch();
        uint8 index = 0;
        auto itemId = fields[index++].GetUInt32();
        auto keystoneInfo = GetKeystoneInfo(itemId, true);
        if (!keystoneInfo)
            continue;
        keystoneInfo->ID = fields[index++].GetUInt16();
        keystoneInfo->Level = fields[index++].GetUInt8();
        keystoneInfo->Affix = fields[index++].GetUInt8();
        keystoneInfo->Affix1 = fields[index++].GetUInt8();
        keystoneInfo->Affix2 = fields[index++].GetUInt8();
        keystoneInfo->Affix3 = fields[index++].GetUInt8();
        keystoneInfo->KeyIsCharded = fields[index++].GetUInt8();
        keystoneInfo->timeReset = fields[index++].GetUInt32();
        keystoneInfo->InstanceID = fields[index++].GetUInt32();

        if (keystoneInfo->Level < 2)
            keystoneInfo->Level = 2;

        if (!keystoneInfo->KeyIsCharded)
        {
            if (keystoneInfo->Level > MYTHIC_LEVEL_2)
                ResetMythicKeystoneTo(nullptr, keystoneInfo->Level, false);
            keystoneInfo->KeyIsCharded = 1;
        }
    } while (result->NextRow());
}

void PlayerChallenge::_SaveMythicKeystones(CharacterDatabaseTransaction& trans)
{
    static uint32 keys[] = { MythicKeystone, MiniMythicKeystone };
    for (auto key : keys)
    {
        auto keystoneInfo = GetKeystoneInfo(key);
        if (!keystoneInfo)
            continue;

        if (!keystoneInfo->needSave && !keystoneInfo->needUpdate)
            continue;

        if (keystoneInfo->Level < 2)
            keystoneInfo->Level = 2;

        uint8 index = 0;
        CharacterDatabasePreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_REP_CHALLENGE_KEY);

        stmt->setUInt32(index++, keystoneInfo->KeystoneEntry);
        stmt->setUInt16(index++, keystoneInfo->ID);
        stmt->setUInt8(index++, keystoneInfo->Level);
        stmt->setUInt8(index++, keystoneInfo->Affix);
        stmt->setUInt8(index++, keystoneInfo->Affix1);
        stmt->setUInt8(index++, keystoneInfo->Affix2);
        stmt->setUInt8(index++, keystoneInfo->Affix3);
        stmt->setUInt8(index++, keystoneInfo->KeyIsCharded);
        stmt->setUInt32(index++, keystoneInfo->timeReset);
        stmt->setUInt32(index++, keystoneInfo->InstanceID);
        stmt->setUInt64(index++, _player->GetGUID().GetCounter());
        trans->Append(stmt);
    }
}

MythicKeystoneInfo* PlayerChallenge::GetKeystoneInfo(Item* item, bool createIfNeed /*= false*/)
{
    return GetKeystoneInfo(item->GetEntry(), createIfNeed);
}

MythicKeystoneInfo* PlayerChallenge::GetKeystoneInfo(uint32 itemEntry, bool createIfNeed)
{
    switch (itemEntry)
    {
        case MythicKeystone:
        {
            if (!MainKeystone)
            {
                if (createIfNeed)
                    return (MainKeystone = std::make_unique<MythicKeystoneInfo>(KeystoneType::Normal, itemEntry)).get();
            }
            return MainKeystone ? MainKeystone.get() : nullptr;
        }
        case MiniMythicKeystone:
        {
            if (!MiniKeystone)
            {
                if (createIfNeed)
                    return (MiniKeystone = std::make_unique<MythicKeystoneInfo>(KeystoneType::Mini, itemEntry)).get();
            }

            return MiniKeystone ? MiniKeystone.get() : nullptr;
        }
        default:
            return nullptr;
    }
}

uint32 PlayerChallenge::GetKeystoneEntryFromMap(InstanceMap* map) const
{
    // TODO: Convert to DB
    switch (map->GetId())
    {
        case 1469:
            return MiniMythicKeystone;
    }


    return MythicKeystone;
}
