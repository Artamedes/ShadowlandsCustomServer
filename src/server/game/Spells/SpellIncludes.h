#pragma once

#include "AreaTrigger.h"
#include "AreaTriggerAI.h"
#include "Containers.h"
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

///< Last Update 9.2.5.44061
enum class SimpleTalentSpecs : uint32
{
    None                = 1,
    Arcane              = 62,
    Fire                = 63,
    MageFrost           = 64,
    HPally              = 65,
    ProtPally           = 66,
    Retribution         = 70,
    Arms                = 71,
    Fury                = 72,
    ProtWarrior         = 73,
    Balance             = 102,
    Feral               = 103,
    Guardian            = 104,
    RDruid              = 105,
    Blood               = 250,
    DKFrost             = 251,
    DKUnholy            = 252,
    BeastMaster         = 253,
    Marksman            = 254,
    Survival            = 255,
    Discipline          = 256,
    HPriest             = 257,
    Shadow              = 258,
    Assassination       = 259,
    Outlaw              = 260,
    Subtlety            = 261,
    Elemental           = 262,
    Enhancement         = 263,
    RShaman             = 264,
    Affiliction         = 265,
    Demonology          = 266,
    Destruction         = 267,
    Brewmaster          = 268,
    Windwalker          = 269,
    Mistweaver          = 270,
    Havoc               = 577,
    Vengeance           = 581,
};

/// Helper functions
inline Player* UnitToPlayer(Unit* who)
{
    if (who && who->IsPlayer())
        return who->ToPlayer();

    return nullptr;
}

inline SimpleTalentSpecs GetSpecializationId(Unit* caster)
{
    if (caster && caster->IsPlayer())
        return static_cast<SimpleTalentSpecs>(caster->ToPlayer()->GetSpecializationId());

    return SimpleTalentSpecs::None;
}

inline bool IsSpec(Unit* who, SimpleTalentSpecs spec)
{
    return GetSpecializationId(who) == spec;
}
