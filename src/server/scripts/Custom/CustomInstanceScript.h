#pragma once

#include "ScriptMgr.h"
#include "Player.h"
#include "InstanceScript.h"
#include "Map.h"
#include "DatabaseEnv.h"

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

    void SetData(uint32 DataId, uint32 Value) override
    {
        if (DataId == SetDataCheckpointId)
            m_CheckpointId = Value;
    }

    uint32 m_CheckpointId = 0;
};
