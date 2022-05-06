#pragma once

#include "Common.h"

class Unit;
class SpellInfo;

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

class TC_GAME_API CustomObjectMgr
{
    public:
        static CustomObjectMgr* instance()
        {
            static CustomObjectMgr instance;
            return &instance;
        }

        void LoadFromDB();

        void LoadCustomSpellDmgs();
        void LoadCustomScalingEntries();
        void LoadCoinModels();

        void ModifySpellDmg(Unit* unit, SpellInfo const* spellInfo, uint32& damage);

        std::unordered_map<uint32, std::unordered_map<uint32, CustomDamage>> _customSpellDmgs;
        std::unordered_map<uint32, CustomScalingEntry> _customScalingEntries;
        std::vector<CoinModel> CoinModels;
};

#define sCustomObjectMgr CustomObjectMgr::instance()
