/// Copyright 2022-2023 Shadows Embrace
/// All Rights Reserved.
/// You may not share or personally use this code without explicit written permission
/// @author: Artamedes

#include "InstanceScript.h"
#include "ScriptMgr.h"
#include "AzureVaults_SE.h"

ObjectData const creatureData[] =
{
    { BOSS_LEYMOR,          DATA_LEYMOR          },
    { BOSS_AZUREBLADE,      DATA_AZUREBLADE      },
    { BOSS_TELASH_GREYWING, DATA_TELASH_GREYWING },
    { BOSS_UMBRELSKUL,      DATA_UMBRELSKUL      },
    { 0,                    0                    }  // END
};

DoorData const doorData[] =
{
    { GO_LEYMOR_DOOR_EXIT,        DATA_LEYMOR,      DOOR_TYPE_PASSAGE },
    { GO_LEYMOR_DOOR_ENTRANCE,    DATA_LEYMOR,      DOOR_TYPE_ROOM },
    { GO_AZUREBLADE_EXIT,         DATA_AZUREBLADE,  DOOR_TYPE_PASSAGE },
    { GO_AZUREBLADE_ENTRANCE,     DATA_AZUREBLADE,  DOOR_TYPE_ROOM },
    { 0,                          0,                     DOOR_TYPE_ROOM    }  // END
};

DungeonEncounterData const encounters[] =
{
    { DATA_LEYMOR,          {{ 2582 }} },
    { DATA_AZUREBLADE,      {{ 2585 }} },
    { DATA_TELASH_GREYWING, {{ 2583 }} },
    { DATA_UMBRELSKUL,      {{ 2584 }} },
};

struct instance_azure_vaults : public InstanceScript
{
    public:
        instance_azure_vaults(InstanceMap* map) : InstanceScript(map)
        {
            SetHeaders(DataHeader);
            SetBossNumber(EncounterCount);
            LoadObjectData(creatureData, nullptr);
            LoadDoorData(doorData);
            LoadDungeonEncounterData(encounters);
        }

        void OnCreatureCreate(Creature* creature) override
        {
            InstanceScript::OnCreatureCreate(creature);

            switch (creature->GetSpawnId())
            {
                // SpawnIds for Arcane Tenders
                case 9001823:
                case 9001856:
                case 9001816:
                    ++_remainingArcaneTenders;
                    _arcaneTenders.insert(creature->GetGUID());
                    break;
                default:
                    break;
            }

            switch (creature->GetEntry())
            {
                case NPC_VAULT_RUNE:
                    creature->SetReactState(REACT_PASSIVE);
                    creature->SetUnitFlag(UnitFlags::UNIT_FLAG_IMMUNE_TO_PC);
                    creature->SetUnitFlag(UnitFlags::UNIT_FLAG_NON_ATTACKABLE);

                    creature->RemoveAllAuras();

                    switch (creature->GetSpawnId())
                    {
                        case 9001911: // first rune.
                            _vaultRunes[0] = creature->GetGUID();
                            break;
                        case 9001901: // second rune.
                            _vaultRunes[1] = creature->GetGUID();
                            break;
                        case 9001917: // third rune.
                            _vaultRunes[2] = creature->GetGUID();
                            break;
                        default:
                            break;
                    }

                    break;

                case NPC_BOOK_OF_TRANSLOCATION_TELASH_BACK:
                    _3rdBossBackBook = creature->GetGUID();

                    if (GetBossState(DATA_TELASH_GREYWING) != DONE)
                        creature->SetVisible(false);
                    break;

                case NPC_BOOK_OF_TRANSLOCATION_LAST:
                    if (GetBossState(DATA_TELASH_GREYWING) != DONE)
                        creature->SetVisible(false);
                    _3rdBossBooks.insert(creature->GetGUID());
                    break;

                case NPC_SINDRAGOSA_TELE:
                    if (GetBossState(DATA_LEYMOR) != DONE)
                        creature->SetVisible(false);
                    _sindragosaTeleGUID = creature->GetGUID();
                    break;
            }
        }

        void OnUnitDeath(Unit* unit) override
        {
            if (unit->IsCreature())
            {
                if (auto creature = unit->ToCreature())
                {
                    if (_arcaneTenders.count(creature->GetGUID()))
                    {
                        if (_remainingArcaneTenders > 0)
                        {
                            --_remainingArcaneTenders;

                            if (_remainingArcaneTenders == 0)
                            {
                                if (auto leymor = GetCreature(DATA_LEYMOR))
                                {
                                    leymor->AI()->DoAction(ACTION_ARCANE_TENDERS_DEAD);
                                }
                            }
                        }
                    }
                }
            }
        }

        void SetData(uint32 data, uint32 value) override
        {
            if (data == ACTION_ACTIVATE_VAULT_RUNE)
            {
                _nextValueIndex++;

                if (_nextValueIndex > 2)
                    _nextValueIndex = 0;

                bool mythic = instance->IsMythic();

                for (uint8 i = 0; i < 3; ++i)
                {
                    if (auto vaultRune = instance->GetCreature(_vaultRunes[i]))
                    {
                        vaultRune->RemoveAurasDueToSpell(SPELL_VAULT_RUNE_AT);

                        if (i == _nextValueIndex || !mythic)
                        {
                            vaultRune->CastSpell(vaultRune, SPELL_VAULT_RUNE_AT, true);
                        }
                    }
                }
            }
            else if (data == ACTION_DISABLE_VAULT_RUNE)
            {
                for (uint8 i = 0; i < 3; ++i)
                {
                    if (auto vaultRune = instance->GetCreature(_vaultRunes[i]))
                    {
                        vaultRune->RemoveAurasDueToSpell(SPELL_VAULT_RUNE_AT);
                    }
                }
            }
        }

        bool SetBossState(uint32 id, EncounterState state, bool set) override
        {
            if (id == DATA_TELASH_GREYWING)
            {
                if (state == IN_PROGRESS)
                {
                    _nextValueIndex = 0;
                    SetData(ACTION_DISABLE_VAULT_RUNE, 1);
                }
                else if (state == DONE)
                {
                    // set visible for the books.
                    for (auto const& guid : _3rdBossBooks)
                        if (auto creature = instance->GetCreature(guid))
                            creature->SetVisible(true);

                    // activate the book to get back
                    if (auto creature = instance->GetCreature(_3rdBossBackBook))
                        creature->SetVisible(true);
                }
            }
            else if (id == DATA_LEYMOR)
            {
                if (auto creature = instance->GetCreature(_sindragosaTeleGUID))
                    creature->SetVisible(true);
            }

            return InstanceScript::SetBossState(id, state, set);
        }

    private:
        GuidUnorderedSet _arcaneTenders;
        GuidUnorderedSet _3rdBossBooks;
        ObjectGuid _3rdBossBackBook;
        uint32 _remainingArcaneTenders = 0;
        ObjectGuid _vaultRunes[3];
        uint8 _nextValueIndex = 0;

        ObjectGuid _sindragosaTeleGUID;
};

void AddSC_instance_azure_vaults_SE()
{
    RegisterInstanceScript(instance_azure_vaults, 2515);
}
