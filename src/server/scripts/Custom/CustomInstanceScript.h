#pragma once

#include "ChallengeMode.h"
#include "ChallengeModeMgr.h"
#include "ScriptMgr.h"
#include "Player.h"
#include "InstanceScript.h"
#include "Map.h"
#include "DatabaseEnv.h"
#include "LootMgr.h"

struct CustomInstanceRespawnData
{
    uint32 CheckPoint;
    Position Pos;
};

class CustomInstanceRespawn
{
public:
    static CustomInstanceRespawn* instance()
    {
        static CustomInstanceRespawn instance;
        return &instance;
    }

    void LoadFromDB()
    {
        m_CustomInstanceRespawnData.clear();
        QueryResult result = WorldDatabase.Query("SELECT MapID, Checkpoint, X, Y, Z, O FROM z_custom_dungeon_respawn_checkpoints");
        if (!result)
            return;

        do
        {
            Field* fields = result->Fetch();

            CustomInstanceRespawnData data;

            data.CheckPoint = fields[1].GetUInt32();
            data.Pos = Position(fields[2].GetFloat(), fields[3].GetFloat(), fields[4].GetFloat(), fields[5].GetFloat());

            m_CustomInstanceRespawnData.insert({ fields[0].GetUInt32(), data });
        } while (result->NextRow());
    }

    CustomInstanceRespawnData const* GetRespawnData(uint32 MapId, uint32 CheckPoint)
    {
        auto itr = m_CustomInstanceRespawnData.equal_range(MapId);
        for (auto i = itr.first; i != itr.second; ++i)
        {
            if (i->second.CheckPoint == CheckPoint)
                return &i->second;
        }

        return nullptr;
    }

    std::multimap<uint32, CustomInstanceRespawnData> m_CustomInstanceRespawnData;
};

#define sCustomInstanceRespawn CustomInstanceRespawn::instance()

constexpr uint32 SetDataCheckpointId = 4000;

static void SetCheckpointId(WorldObject* obj, uint32 checkpoint)
{
    if (auto instance = obj->GetInstanceScript())
        instance->SetData(SetDataCheckpointId, checkpoint);
}

struct CustomInstanceScript : public InstanceScript
{
public:
    CustomInstanceScript(InstanceMap* map) : InstanceScript(map)
    {
    }

    bool HandlePlayerRepopRequest(Player* player) const
    {
        if (auto respawnData = sCustomInstanceRespawn->GetRespawnData(instance->GetId(), m_CheckpointId))
        {
            player->TeleportTo(WorldLocation(instance->GetId(), respawnData->Pos), TELE_REVIVE_AT_TELEPORT);
            //player->ResurrectPlayer(0.85f);
            return true;
        }

        return false;
    }

    bool HandleGetStartPosition(float& x, float& y, float& z, float& o) const
    {
        if (auto respawnData = sCustomInstanceRespawn->GetRespawnData(instance->GetId(), m_CheckpointId))
        {
            x = respawnData->Pos.GetPositionX();
            y = respawnData->Pos.GetPositionY();
            z = respawnData->Pos.GetPositionZ();
            o = respawnData->Pos.GetOrientation();
            return true;
        }

        return false;
    }

    void SetData(uint32 DataId, uint32 Value) override
    {
        if (DataId == SetDataCheckpointId)
            m_CheckpointId = Value;
    }

    void OnChallengeComplete() override
    {
        if (auto chest = instance->SummonGameObject(1200005, ChestSpawn, Quad, 0))
        {
            instance->DoOnPlayers([this, chest](Player* player)
            {
                auto loot = chest->GetLootFor(player, true);
                loot->FillLoot(GetLootIdForDungeon(), LootTemplates_Gameobject, player, true, false, chest->GetLootMode(), true, true, false, chest->GetGOInfo()->IsOploteChest());
            });

            chest->SetLootState(LootState::GO_ACTIVATED); // set activated
            chest->ForceUpdateFieldChange(chest->m_values.ModifyValue(&Object::m_objectData).ModifyValue(&UF::ObjectData::DynamicFlags)); // force update dynflags
        }
    }

    uint32 m_CheckpointId = 0;
    Position ChestSpawn;
    QuaternionData Quad;
};
