#pragma once

#include "Common.h"

class Unit;
class SpellInfo;
struct MythicKeystoneInfo;

struct CustomDamage
{
    uint32 Min;
    uint32 Max;
    float PctModifier;
};

struct CustomScalingEntry
{
    float HealthModifier;
    float DamageModifier;
};

struct CoinModel
{
    uint32 ID;
    uint32 ModelID;
    uint32 CreatureEntry;
};

struct CustomTransmogVendor
{
    uint32 TransmogSet;
    uint32 ClassMask;
    uint32 Flags;
    uint32 TransmogTokenCost;
    std::string Icon;
};

struct ChallengeLevelInfo
{
    float BaseHPScaling;
    float BaseDmgScaling;
    float HPScalingPerPlayer;
    float DMGScalingPerPlayer;
};

class TC_GAME_API CustomObjectMgr
{
    public:
        static CustomObjectMgr* instance()
        {
            static CustomObjectMgr instance;
            return &instance;
        }

        ~CustomObjectMgr();

        void LoadFromDB();

        void LoadCustomSpellDmgs();
        void LoadCustomScalingEntries();
        void LoadCoinModels();
        void LoadCustomTransmogVendorData();
        void LoadFiledataData();
        void LoadCustomChallengeInfo();

        void ModifySpellDmg(Unit* unit, SpellInfo const* spellInfo, uint32& damage);
        void GenerateCustomDungeonForKeystone(MythicKeystoneInfo* keystoneInfo);
        void SetChallengeLevelInfoIfNeed(MythicKeystoneInfo* keystoneInfo, ChallengeLevelInfo* levelInfo);

        std::unordered_map<uint32, std::unordered_map<uint32, CustomDamage>> _customSpellDmgs;
        std::unordered_map<uint32, CustomScalingEntry> _customScalingEntries;
        std::multimap<uint32, CustomTransmogVendor> _customTransmogVendorData;
        std::vector<CoinModel> CoinModels;
        std::unordered_map<uint32, std::string> _fileDataToPath;
        std::unordered_map<uint32, ChallengeLevelInfo*> _groupChallengeLevelInfo;
        std::unordered_map<uint32, ChallengeLevelInfo*> _soloChallengeLevelInfo;
        std::unordered_map<uint32, std::vector<uint32>> _customChallengeDungeonsByKeystone;
};

#define sCustomObjectMgr CustomObjectMgr::instance()
