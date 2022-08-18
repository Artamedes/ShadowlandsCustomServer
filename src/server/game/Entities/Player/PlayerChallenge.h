#pragma once

#include "Common.h"
#include "DatabaseEnvFwd.h"

class Player;
class Item;
struct MapChallengeModeEntry;

namespace Keystones
{
    /// <summary>
    /// ItemIds
    /// </summary>
    enum : uint32
    {
        Group       = 158923,
        Solo        = 180653,
        Timewalking = 700019,
    };
}

enum class KeystoneType
{
    Group,
    Solo,
    Timewalking,
    Unk,
};

static KeystoneType KeystoneTypeFromItem(Item* item);

struct MythicKeystoneInfo
{
    MythicKeystoneInfo(Item* keystone);
    bool IsActive() { return ID != 0; }

    MapChallengeModeEntry const* challengeEntry = nullptr;
    uint32 InstanceID = 0;
    uint32 timeReset = 0;
    uint32 ID = 0;
    uint8 Level = 0;
    uint8 Affix = 0;
    uint8 Affix1 = 0;
    uint8 Affix2 = 0;
    uint8 Affix3 = 0;
    uint8 KeyIsCharded = 0;
    bool needSave = false;
    bool needUpdate = false;
    KeystoneType Type;
    uint32 KeystoneItemID;
    ObjectGuid KeystoneGUID;

    void GenerateNewDungeon();
};

class TC_GAME_API PlayerChallenge
{
public:
    PlayerChallenge(Player* player);
    ~PlayerChallenge();

    /// <summary>
    /// Initializes the fields of a mythic keystone
    /// Called from the script item_challenge_key or when item is loaded from db
    /// Use CreateMythicKeystone to create a mythic keystone
    /// </summary>
    /// <param name="item">The item that was created</param>
    /// <returns>true if the keystone was succesfully generated</returns>
    bool InitMythicKeystone(Item* item);
    void CreateMythicKeystone(Item* item);
    void UpdateMythicKeystone(Item* item);
    void ResetMythicKeystone();
    void ResetMythicKeystoneTo(Item* item, uint32 challengeLevel, bool runRand = true);

    void _LoadMythicKeystones(PreparedQueryResult result);
    void _SaveMythicKeystones(CharacterDatabaseTransaction& trans);

    MythicKeystoneInfo* GetKeystoneInfo(Item* item, bool createIfNeed = false);
    MythicKeystoneInfo* GetKeystoneInfo(ObjectGuid const& itemGuid, bool createIfNeed = false);

private:
    Player* _player;
    std::unordered_map<uint32, MythicKeystoneInfo*> Keystones;
};
