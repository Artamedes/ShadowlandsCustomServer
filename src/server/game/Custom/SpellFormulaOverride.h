#pragma once

#include "SpellIncludes.h"

class TC_GAME_API SpellFormulaOverride
{
public:
    static SpellFormulaOverride* instance()
    {
        static SpellFormulaOverride s_instance;
        return &s_instance;
    }

    void LoadFromDB();
    void AddEntryToDB(uint32 SpellId, SpellEffIndex EffectIndex, Player* player);
    void DeleteEntryFromDB(uint32 SpellId, SpellEffIndex EffectIndex);
    bool CanOverrideEffect(SpellEffectInfo const& eff);
    bool CanOverrideSpell(SpellInfo const* spellInfo);
    void DisplaySpellMap(Player* player, uint32 lowerBounds, uint32 upperBounds);
    void CreateMenu(Player* player, uint32 lowerBounds = 0, uint32 upperBounds = 20);
    void CreateMenuForSpell(Player* player, SpellInfo const* spellInfo);
    void CreateMenuForEffect(Player* player, SpellEffectInfo const* eff, SpellInfo const* spellInfo);
    void HandleInputSpellId(Player* player, std::string callback);
};

#define sSpellFormulaOverride SpellFormulaOverride::instance()
