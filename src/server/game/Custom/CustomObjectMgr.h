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
        void ModifySpellDmg(Unit* unit, SpellInfo const* spellInfo, uint32& damage);

        std::unordered_map<uint32, std::unordered_map<uint32, CustomDamage>> _customSpellDmgs;
};

#define sCustomObjectMgr CustomObjectMgr::instance()
