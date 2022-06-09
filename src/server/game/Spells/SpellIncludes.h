#pragma once

#include "AreaTrigger.h"
#include "AreaTriggerAI.h"
#include "Player.h"
#include "ScriptMgr.h"
#include "Spell.h"
#include "SpellScript.h"
#include "SpellInfo.h"
#include "SpellMgr.h"
#include "SpellAuraDefines.h"
#include "SpellAuraEffects.h"
#include "SpellAuras.h"
#include "SpellHistory.h"

/// Helper functions
inline Player* UnitToPlayer(Unit* who)
{
    if (who && who->IsPlayer())
        return who->ToPlayer();

    return nullptr;
}
