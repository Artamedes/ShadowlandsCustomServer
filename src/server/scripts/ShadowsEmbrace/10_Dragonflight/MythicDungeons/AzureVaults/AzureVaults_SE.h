/// Copyright 2022-2023 Shadows Embrace
/// All Rights Reserved.
/// You may not share or personally use this code without explicit written permission
/// @author: Artamedes

#pragma once

#include "CreatureAIImpl.h"


#define AzureVaultsScriptName "instance_azure_vaults"
#define DataHeader "AVDF"

uint32 const EncounterCount = 4;

enum AVDFDataTypes : uint32
{
    // Encounters
    DATA_LEYMOR          = 0,
    DATA_AZUREBLADE      = 1,
    DATA_TELASH_GREYWING = 2,
    DATA_UMBRELSKUL      = 3,
};

enum AVDFCreatureIds : uint32
{
    // Bosses
    BOSS_LEYMOR          = 186644,
    BOSS_AZUREBLADE      = 186739,
    BOSS_TELASH_GREYWING = 199614,
    BOSS_UMBRELSKUL      = 186738,

    // Telash Boss
    NPC_VAULT_RUNE       = 197204,
    NPC_BOOK_OF_TRANSLOCATION_LAST = 194715,
};

enum AVDFGameObjectIds : uint32
{
    // Doors
    GO_LEYMOR_DOOR_EXIT     = 377951,
    GO_LEYMOR_DOOR_ENTRANCE = 380536,
    GO_AZUREBLADE_EXIT      = 380537,
    GO_AZUREBLADE_ENTRANCE  = 377952,
};

enum AVDFGlobalActions : uint32
{
    ACTION_ARCANE_TENDERS_DEAD = 6000,
    ACTION_ACTIVATE_VAULT_RUNE,
    ACTION_DISABLE_VAULT_RUNE,
};

enum AVDFGlobalSpells : uint32
{
    SPELL_VAULT_RUNE_AT = 388065,
};

template <class AI, class T>
inline AI* GetAzureVaultsAI(T* obj)
{
    return GetInstanceAI<AI>(obj, AzureVaultsScriptName);
}

#define RegisterAzureVaultsCreatureAI(ai_name) RegisterCreatureAIWithFactory(ai_name, GetAzureVaultsAI)
