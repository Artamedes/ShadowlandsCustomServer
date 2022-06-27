#pragma once

#include "Desmotaeron.h"

enum eInstanceDesmotaeron
{
    JainaConversation = 700313,
    NpcPortalToJaina = 707037,

    GoBonemawDoor = 233989,
};

struct instance_desmotaeron : public CustomInstanceScript
{
public:
    instance_desmotaeron(InstanceMap* map) : CustomInstanceScript(map)
    {
        SetBossNumber(Desmoteraon::MaxBosses);
        RequiredBossesKilled = 4;
    }

    void OnGameObjectCreate(GameObject* go) override
    {
        CustomInstanceScript::OnGameObjectCreate(go);

        switch (go->GetEntry())
        {
            case 353816:
            case 367939:
                go->SetFlag(GameObjectFlags::GO_FLAG_NOT_SELECTABLE);
                break;
            case GoBonemawDoor:
                BonemawDoorGuid = go->GetGUID();
                break;
        }
    }

    void OnCreatureCreate(Creature* creature) override
    {
        CustomInstanceScript::OnCreatureCreate(creature);

        switch (creature->GetEntry())
        {
            default:
                break;
        }
    }

    void OnPlayerEnter(Player* player) override
    {
        CustomInstanceScript::OnPlayerEnter(player);

        player->CastSpell(player, HeavyFogRain, true);
    }

    void OnPlayerLeave(Player* player) override
    {
        CustomInstanceScript::OnPlayerLeave(player);
        player->RemoveAurasDueToSpell(HeavyFogRain);
    }

    bool SetBossState(uint32 id, EncounterState state, bool forced) override
    {
        bool result = InstanceScript::SetBossState(id, state, forced);
        bool isUpperBoss = false;

        switch (id)
        {
            case BossGeneralNephmir:
            case BossShirgantai:
            case BossXarvius:
            case BossEcidus:
                isUpperBoss = true;
                break;

            default:
                break;
        }

        if (isUpperBoss && state == EncounterState::DONE)
        {
            if (RequiredBossesKilled > 0)
            {
                --RequiredBossesKilled;
                if (RequiredBossesKilled == 0)
                {
                    SetData(SetDataCheckpointId, 1);
                    instance->DoOnPlayers([](Player* player)
                    {
                        Conversation::CreateConversation(JainaConversation, player, *player, player->GetGUID());
                    });

                    if (auto portal = instance->SummonCreature(NpcPortalToJaina, { 4548.63f, 5843.36f, 4852.16f, 0.839205f }))
                    {
                        portal->SetTempSummonType(TempSummonType::TEMPSUMMON_MANUAL_DESPAWN);
                    }

                    if (auto door = instance->GetGameObject(BonemawDoorGuid))
                        door->Delete();
                }
            }
        }

        return result;
    }

    uint32 RequiredBossesKilled = 0;
    ObjectGuid BonemawDoorGuid;
};

void AddSC_instance_desmotareon()
{
    RegisterInstanceScript(instance_desmotaeron, 2456);
}
