#include "ChallengeMode.h"
#include "Chat.h"
#include "Containers.h"
#include "CustomObjectMgr.h"
#include "DatabaseEnv.h"
#include "PlayerChallenge.h"
#include "Player.h"
#include "Map.h"
#include "Item.h"
#include "World.h"
#include "GameTime.h"
#include "WorldStateMgr.h"

static KeystoneType KeystoneTypeFromItem(Item* item)
{
    switch (item->GetEntry())
    {
        case Keystones::Group:
            return KeystoneType::Group;
        case Keystones::Solo:
            return KeystoneType::Solo;
        case Keystones::Timewalking:
            return KeystoneType::Timewalking;
        default:
            return KeystoneType::Unk;
    }
}

MythicKeystoneInfo::MythicKeystoneInfo(Item* keystone)
    : Type(KeystoneTypeFromItem(keystone)), KeystoneGUID(keystone->GetGUID()), KeystoneItemID(keystone->GetEntry())
{
}

void MythicKeystoneInfo::GenerateNewDungeon()
{
    sCustomObjectMgr->GenerateCustomDungeonForKeystone(this);
}

PlayerChallenge::PlayerChallenge(Player* player) : _player(player)
{
}

PlayerChallenge::~PlayerChallenge()
{
    for (auto itr = Keystones.begin(); itr != Keystones.end(); itr++)
        delete itr->second;
}

bool PlayerChallenge::InitMythicKeystone(Item* item)
{
    switch (item->GetEntry())
    {
        case Keystones::Group:
        case Keystones::Solo:
        case Keystones::Timewalking:
            break;
        default:
            /// We want to return true here because this can be called from player and its'not key item
            return true;
    }

    auto keystoneInfo = GetKeystoneInfo(item);

    /// Keys can be loaded before we load below.. Return true
    if (!keystoneInfo)
        return true;

    if (!keystoneInfo->IsActive())
        return false;

    if (keystoneInfo->Type != KeystoneType::Timewalking)
    {
        keystoneInfo->Affix  = sWorldStateMgr->GetValue(WS_CHALLENGE_AFFIXE1_RESET_TIME);
        keystoneInfo->Affix1 = sWorldStateMgr->GetValue(WS_CHALLENGE_AFFIXE2_RESET_TIME);
        keystoneInfo->Affix2 = sWorldStateMgr->GetValue(WS_CHALLENGE_AFFIXE3_RESET_TIME);
        keystoneInfo->Affix3 = sWorldStateMgr->GetValue(WS_CHALLENGE_AFFIXE4_RESET_TIME);
    }
    else
    {
        keystoneInfo->Affix  = sWorldStateMgr->GetValue(WS_CHALLENGE_MINI_AFFIXE1_RESET_TIME);
        keystoneInfo->Affix1 = sWorldStateMgr->GetValue(WS_CHALLENGE_MINI_AFFIXE2_RESET_TIME);
        keystoneInfo->Affix2 = sWorldStateMgr->GetValue(WS_CHALLENGE_MINI_AFFIXE3_RESET_TIME);
        keystoneInfo->Affix3 = sWorldStateMgr->GetValue(WS_CHALLENGE_MINI_AFFIXE4_RESET_TIME);
    }

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

    bool sendMsg = false;

    if (!item->GetModifier(ITEM_MODIFIER_CHALLENGE_MAP_CHALLENGE_MODE_ID))
    {
        keystoneInfo->GenerateNewDungeon();
        item->SetModifier(ITEM_MODIFIER_CHALLENGE_MAP_CHALLENGE_MODE_ID, keystoneInfo->ID);
        sendMsg = true;
    }

    if (keystoneInfo->Type != KeystoneType::Timewalking)
    {
        keystoneInfo->Affix  = sWorldStateMgr->GetValue(WS_CHALLENGE_AFFIXE1_RESET_TIME);
        keystoneInfo->Affix1 = sWorldStateMgr->GetValue(WS_CHALLENGE_AFFIXE2_RESET_TIME);
        keystoneInfo->Affix2 = sWorldStateMgr->GetValue(WS_CHALLENGE_AFFIXE3_RESET_TIME);
        keystoneInfo->Affix3 = sWorldStateMgr->GetValue(WS_CHALLENGE_AFFIXE4_RESET_TIME);
    }
    else
    {
        keystoneInfo->Affix  = sWorldStateMgr->GetValue(WS_CHALLENGE_MINI_AFFIXE1_RESET_TIME);
        keystoneInfo->Affix1 = sWorldStateMgr->GetValue(WS_CHALLENGE_MINI_AFFIXE2_RESET_TIME);
        keystoneInfo->Affix2 = sWorldStateMgr->GetValue(WS_CHALLENGE_MINI_AFFIXE3_RESET_TIME);
        keystoneInfo->Affix3 = sWorldStateMgr->GetValue(WS_CHALLENGE_MINI_AFFIXE4_RESET_TIME);
    }

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

    if (sendMsg && _player->IsInWorld())
        ChatHandler(_player).PSendSysMessage("|cff35B3EENew Keystone: %s", Item::GetItemLink(item, _player).c_str());

    item->SetState(ITEM_CHANGED, _player);
}

void PlayerChallenge::UpdateMythicKeystone(Item* item)
{
    auto keystoneInfo = GetKeystoneInfo(item);
    if (!keystoneInfo)
        return;

    keystoneInfo->ID = item->GetModifier(ITEM_MODIFIER_CHALLENGE_MAP_CHALLENGE_MODE_ID);
    keystoneInfo->Level = item->GetModifier(ITEM_MODIFIER_CHALLENGE_KEYSTONE_LEVEL);

    if (keystoneInfo->Type != KeystoneType::Timewalking)
    {
        keystoneInfo->Affix = sWorldStateMgr->GetValue(WS_CHALLENGE_AFFIXE1_RESET_TIME);
        keystoneInfo->Affix1 = sWorldStateMgr->GetValue(WS_CHALLENGE_AFFIXE2_RESET_TIME);
        keystoneInfo->Affix2 = sWorldStateMgr->GetValue(WS_CHALLENGE_AFFIXE3_RESET_TIME);
        keystoneInfo->Affix3 = sWorldStateMgr->GetValue(WS_CHALLENGE_AFFIXE4_RESET_TIME);
    }
    else
    {
        keystoneInfo->Affix = sWorldStateMgr->GetValue(WS_CHALLENGE_MINI_AFFIXE1_RESET_TIME);
        keystoneInfo->Affix1 = sWorldStateMgr->GetValue(WS_CHALLENGE_MINI_AFFIXE2_RESET_TIME);
        keystoneInfo->Affix2 = sWorldStateMgr->GetValue(WS_CHALLENGE_MINI_AFFIXE3_RESET_TIME);
        keystoneInfo->Affix3 = sWorldStateMgr->GetValue(WS_CHALLENGE_MINI_AFFIXE4_RESET_TIME);
    }

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
    /// Delete the old keystones
    for (auto& itr : Keystones)
    {
        if (auto item = _player->GetItemByGuid(itr.second->KeystoneGUID))
            _player->DestroyItem(item->GetBagSlot(), item->GetSlot(), true);
        delete itr.second;
    }

    Keystones.clear();
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

            if (runRand && _player->IsInWorld())
                ChatHandler(_player).PSendSysMessage("|cff35B3EENew Keystone: %s", Item::GetItemLink(item, _player).c_str());
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
    _player->DestroyItemCount(keystoneInfo->KeystoneItemID, 100, true, false);
}

void PlayerChallenge::_LoadMythicKeystones(PreparedQueryResult result)
{
    if (!result)
    {
        /// No result? Delete all keystone items.
        _player->DestroyItemCount(Keystones::Group, 1, true);
        _player->DestroyItemCount(Keystones::Solo, 1, true);
        _player->DestroyItemCount(Keystones::Timewalking, 1, true);
        return;
    }

    do
    {
        Field* fields = result->Fetch();
        uint8 index = 0;
        auto itemId = fields[index++].GetUInt32();
        /// Get object pointer from bag
        auto item = _player->GetItemByEntry(itemId);
        if (!item)
            continue;
        auto keystoneInfo = GetKeystoneInfo(item, true);

        // can happen if bad db (invalid entry)
        if (keystoneInfo == nullptr)
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
                ResetMythicKeystoneTo(item, keystoneInfo->Level, false);
            keystoneInfo->KeyIsCharded = 1;
        }

        // reset key
        if (sWorld->getNextChallengeKeyReset() > keystoneInfo->timeReset)
        {
            ResetMythicKeystoneTo(item, keystoneInfo->Level, true);
        }
        else
        {
            // initialize key
            InitMythicKeystone(item);
        }

    } while (result->NextRow());
}

void PlayerChallenge::_SaveMythicKeystones(CharacterDatabaseTransaction& trans)
{
    for (auto& itr : Keystones)
    {
        auto keystone = itr.second;
        
        if (keystone->needSave || keystone->needUpdate)
        {
            if (keystone->Level < 2)
                keystone->Level = 2;

            uint8 index = 0;
            CharacterDatabasePreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_REP_CHALLENGE_KEY);

            stmt->setUInt32(index++, keystone->KeystoneItemID);
            stmt->setUInt16(index++, keystone->ID);
            stmt->setUInt8(index++,  keystone->Level);
            stmt->setUInt8(index++,  keystone->Affix);
            stmt->setUInt8(index++,  keystone->Affix1);
            stmt->setUInt8(index++,  keystone->Affix2);
            stmt->setUInt8(index++,  keystone->Affix3);
            stmt->setUInt8(index++,  keystone->KeyIsCharded);
            stmt->setUInt32(index++, keystone->timeReset);
            stmt->setUInt32(index++, keystone->InstanceID);
            stmt->setUInt64(index++, _player->GetGUID().GetCounter());
            trans->Append(stmt);
        }
    }
}

MythicKeystoneInfo* PlayerChallenge::GetKeystoneInfo(Item* item, bool createIfNeed /*= false*/)
{
    if (!item)
        return nullptr;

    MythicKeystoneInfo* currentKeyInfo = nullptr;

    auto it = Keystones.find(item->GetEntry());
    if (it != Keystones.end())
        return it->second;

    if (createIfNeed)
    {
        MythicKeystoneInfo* keystoneInfo = new MythicKeystoneInfo(item);
        Keystones[item->GetEntry()] = keystoneInfo;
        return keystoneInfo;
    }

    return nullptr;
}

MythicKeystoneInfo* PlayerChallenge::GetKeystoneInfo(ObjectGuid const& guid, bool createIfNeed)
{
    return GetKeystoneInfo(_player->GetItemByGuid(guid), createIfNeed);
}
