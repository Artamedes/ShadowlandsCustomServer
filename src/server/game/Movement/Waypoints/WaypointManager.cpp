/*
 * This file is part of the TrinityCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "WaypointManager.h"
#include "DatabaseEnv.h"
#include "GridDefines.h"
#include "MapManager.h"
#include "Log.h"
#include "Player.h"
#include "ScriptedGossip.h"
#include "Chat.h"
#include "Creature.h"
#include "TemporarySummon.h"
#include <sstream>
#include "MotionMaster.h"

void WaypointMgr::Load()
{
    uint32 oldMSTime = getMSTime();

    //                                               0   1      2           3           4           5            6         7          8      9                 10      11
    QueryResult result = WorldDatabase.Query("SELECT id, point, position_x, position_y, position_z, orientation, velocity, move_type, delay, smoothTransition, action, action_chance FROM waypoint_data ORDER BY id, point");

    if (!result)
    {
        TC_LOG_INFO("server.loading", ">> Loaded 0 waypoints. DB table `waypoint_data` is empty!");
        return;
    }

    uint32 count = 0;

    do
    {
        Field* fields = result->Fetch();
        uint32 pathId = fields[0].GetUInt32();
        float x = fields[2].GetFloat();
        float y = fields[3].GetFloat();
        float z = fields[4].GetFloat();
        Optional<float> o;
        if (!fields[5].IsNull())
            o = fields[5].GetFloat();

        float velocity = fields[6].GetFloat();

        Trinity::NormalizeMapCoord(x);
        Trinity::NormalizeMapCoord(y);

        WaypointNode waypoint;
        waypoint.PathId = pathId;
        waypoint.Id = fields[1].GetUInt32();
        waypoint.X = x;
        waypoint.Y = y;
        waypoint.Z = z;
        if (o.has_value())
            waypoint.Orientation = o;
        waypoint.Velocity = velocity;
        waypoint.MoveType = static_cast<WaypointMoveType>(fields[7].GetUInt32());

        if (waypoint.MoveType >= WaypointMoveType::Max)
        {
            TC_LOG_ERROR("sql.sql", "Waypoint %u in waypoint_data has invalid move_type, ignoring", waypoint.Id);
            continue;
        }

        waypoint.Delay = fields[8].GetUInt32();
        waypoint.SmoothTransition = fields[9].GetBool();
        waypoint.EventId = fields[10].GetUInt32();
        waypoint.EventChance = fields[11].GetInt16();

        WaypointPath& path = _waypointStore[pathId];
        path.Id = pathId;
        path.Nodes.push_back(std::move(waypoint));
        ++count;
    } while (result->NextRow());

    TC_LOG_INFO("server.loading", ">> Loaded %u waypoints in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

void WaypointMgr::LoadWaypointAddons()
{
    uint32 oldMSTime = getMSTime();

    //                                               0       1        2                 3          4          5
    QueryResult result = WorldDatabase.Query("SELECT PathID, PointID, SplinePointIndex, PositionX, PositionY, PositionZ FROM waypoint_data_addon ORDER BY PathID, PointID, SplinePointIndex");

    if (!result)
    {
        TC_LOG_INFO("server.loading", ">> Loaded 0 waypoints. DB table `waypoint_data_addon` is empty!");
        return;
    }

    uint32 count = 0;

    do
    {
        Field* fields = result->Fetch();
        uint32 pathId = fields[0].GetUInt32();

        std::unordered_map<uint32, WaypointPath>::iterator it = _waypointStore.find(pathId);
        if (it == _waypointStore.end())
        {
            TC_LOG_ERROR("sql.sql", "Tried to load waypoint_data_addon data for PathID %u but there is no such path in waypoint_data. Ignoring.", pathId);
            continue;
        }

        WaypointPath& path = it->second;
        uint32 pointId          = fields[1].GetUInt32();
        uint32 SplinePointIndex = fields[2].GetUInt32();

        std::vector<WaypointNode>::iterator itr = std::find_if(path.Nodes.begin(), path.Nodes.end(), [pointId](WaypointNode const& node)
        {
            return node.Id == pointId;
        });

        if (itr == path.Nodes.end())
        {
            TC_LOG_ERROR("sql.sql", "Tried to load waypoint_data_addon data for PointID %u of PathID %u but there is no such point in waypoint_data. Ignoring.", pointId, pathId);
            continue;
        }

        float x = fields[3].GetFloat();
        float y = fields[4].GetFloat();
        float z = fields[5].GetFloat();

        Trinity::NormalizeMapCoord(x);
        Trinity::NormalizeMapCoord(y);

        if (itr->SplinePoints.size() >= SplinePointIndex)
            itr->SplinePoints.push_back(G3D::Vector3(x, y, z));
        else
            itr->SplinePoints[SplinePointIndex] = G3D::Vector3(x, y, z);

        ++count;
    } while (result->NextRow());

    TC_LOG_INFO("server.loading", ">> Loaded %u waypoint addon data in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

WaypointMgr* WaypointMgr::instance()
{
    static WaypointMgr instance;
    return &instance;
}

void WaypointMgr::ReloadPath(uint32 id)
{
    auto itr = _waypointStore.find(id);
    if (itr != _waypointStore.end())
        _waypointStore.erase(itr);

    WorldDatabasePreparedStatement* stmt = WorldDatabase.GetPreparedStatement(WORLD_SEL_WAYPOINT_DATA_BY_ID);

    stmt->setUInt32(0, id);

    PreparedQueryResult result = WorldDatabase.Query(stmt);

    if (!result)
        return;

    std::vector<WaypointNode> values;
    do
    {
        Field* fields = result->Fetch();
        float x = fields[1].GetFloat();
        float y = fields[2].GetFloat();
        float z = fields[3].GetFloat();
        Optional<float> o;
        if (!fields[4].IsNull())
            o = fields[4].GetFloat();

        float velocity = fields[5].GetFloat();

        Trinity::NormalizeMapCoord(x);
        Trinity::NormalizeMapCoord(y);

        WaypointNode waypoint;
        waypoint.PathId = id;
        waypoint.Id = fields[0].GetUInt32();
        waypoint.X = x;
        waypoint.Y = y;
        waypoint.Z = z;
        if (o.has_value())
            waypoint.Orientation = o;
        waypoint.Velocity = velocity;
        waypoint.MoveType = static_cast<WaypointMoveType>(fields[6].GetUInt32());

        if (waypoint.MoveType >= WaypointMoveType::Max)
        {
            TC_LOG_ERROR("sql.sql", "Waypoint %u in waypoint_data has invalid move_type, ignoring", waypoint.Id);
            continue;
        }

        waypoint.Delay = fields[7].GetUInt32();
        waypoint.EventId = fields[8].GetUInt32();
        waypoint.EventChance = fields[9].GetUInt8();

        values.push_back(std::move(waypoint));
    } while (result->NextRow());

    _waypointStore[id] = WaypointPath(id, std::move(values));
}

WaypointPath const* WaypointMgr::GetPath(uint32 id) const
{
    auto itr = _waypointStore.find(id);
    if (itr != _waypointStore.end())
        return &itr->second;

    return nullptr;
}

WaypointPath* WaypointMgr::GetPathPig(uint32 id)
{
    auto itr = _waypointStore.find(id);
    if (itr != _waypointStore.end())
        return &itr->second;

    // create a default
    WaypointPath path;
    path.Id = id;
    _waypointStore[id] = path;
    return GetPathPig(id);
}

void WaypointNode::ReplaceNodeInDB()
{
    auto stmt = WorldDatabase.GetPreparedStatement(WORLD_REP_WAYPOINT_NODE);
    stmt->setUInt32(0, PathId);
    stmt->setUInt32(1, Id);
    stmt->setFloat(2, X);
    stmt->setFloat(3, Y);
    stmt->setFloat(4, Z);
    stmt->setFloat(5, Orientation.has_value() ? *Orientation : 0.0f);
    stmt->setFloat(6, Velocity);
    stmt->setUInt32(7, Delay);
    stmt->setUInt8(8, SmoothTransition);
    stmt->setUInt32(9, static_cast<uint32>(MoveType));
    stmt->setUInt32(10, EventId);
    stmt->setUInt8(11, EventChance);
    stmt->setUInt64(12, wpguid);
    WorldDatabase.Query(stmt);

    uint32 SplinePointIndex = 0;
    for (auto const& splinePoint : SplinePoints)
    {
        stmt = WorldDatabase.GetPreparedStatement(WORLD_REP_WAYPOINT_ADDON_NODE);
        stmt->setUInt32(0, PathId);
        stmt->setUInt32(1, Id);
        stmt->setUInt32(2, SplinePointIndex++);
        stmt->setFloat(3, splinePoint.x);
        stmt->setFloat(4, splinePoint.y);
        stmt->setFloat(5, splinePoint.z);
        WorldDatabase.Query(stmt);
    }
}

std::string MoveTypeToString(WaypointMoveType MoveType)
{
    switch (MoveType)
    {
        case WaypointMoveType::Walk:
            return "Walk";
        case WaypointMoveType::Run:
            return "Run";
        case WaypointMoveType::Land:
            return "Land";
        case WaypointMoveType::TakeOff:
            return "TakeOff";
        default:
            return "Unk";
    }
}

void WaypointNode::CreateMenuForPlayer(Player* player)
{
    ClearGossipMenuFor(player);

    AddGossipItemFor(player, GossipOptionIcon::None, "PathID: " + std::to_string(PathId), 0, 0, [player, this](std::string /*callback*/)
    {
        CreateMenuForPlayer(player);
    });

    AddGossipItemFor(player, GossipOptionIcon::None, "PointID: " + std::to_string(Id), 0, 0, [player, this](std::string /*callback*/)
    {
        CreateMenuForPlayer(player);
    });

    std::ostringstream ss;
    ss << "|cffFF0000[X: " << X << " Y: " << Y << " Z: " << Z << "]|R Set New Endpoint";
    AddGossipItemFor(player, GossipOptionIcon::None, ss.str().c_str(), 0, 0, [player, this](std::string /*callback*/)
    {
        player->GetPosition(X, Y, Z);

        Trinity::NormalizeMapCoord(X);
        Trinity::NormalizeMapCoord(Y);

        ChatHandler(player).PSendSysMessage("Pos updated to %s", player->GetPosition().ToString().c_str());

        CreateMenuForPlayer(player);
    });

    AddGossipItemFor(player, GossipOptionIcon::None, "Teleport To Position", 0, 0, [this, player](std::string /*callback*/)
    {
        player->NearTeleportTo({ X, Y, Z }, false, true);
        CreateMenuForPlayer(player);
    });

    AddGossipItemFor(player, GossipOptionIcon::None, "Orientation: " + std::to_string((Orientation.has_value() ? *Orientation : 0.0f)), 0, 0, [player, this](std::string /*callback*/)
    {
        Orientation = player->GetOrientation();
        ChatHandler(player).PSendSysMessage("Orientation updated to %f", player->GetOrientation());
        CreateMenuForPlayer(player);
    });

    ss.clear();
    ss.str("");

    AddGossipItemFor(player, GossipOptionIcon::None, "Velocity: " + std::to_string(Velocity), 0, 0, "", 0, true, [player, this](std::string callback)
    {
        Velocity = atof(callback.c_str());
        ChatHandler(player).PSendSysMessage("Velocity updated to %f", Velocity);
        CreateMenuForPlayer(player);
    });

    AddGossipItemFor(player, GossipOptionIcon::None, "Delay: " + std::to_string(Delay), 0, 0, "", 0, true, [player, this](std::string callback)
    {
        Delay = atol(callback.c_str());
        ChatHandler(player).PSendSysMessage("Delay updated to %u", Delay);
        CreateMenuForPlayer(player);
    });

    AddGossipItemFor(player, GossipOptionIcon::None, "MoveType: " + MoveTypeToString(MoveType), 0, 0, "", 0, true, [player, this](std::string callback)
    {
        MoveType = static_cast<WaypointMoveType>(atol(callback.c_str()));
        ChatHandler(player).PSendSysMessage("MoveType updated to %u", MoveType);
        CreateMenuForPlayer(player);
    });

    AddGossipItemFor(player, GossipOptionIcon::None, "SplinePoints " + std::to_string(SplinePoints.size()), 0, 0, [player, this](std::string /*callback*/)
    {
        SendSplinePoints(player);
    });


    AddGossipItemFor(player, GossipOptionIcon::None, "Delete Node", 0, 0, [player, this](std::string /*callback*/)
    {
        auto Parent = sWaypointMgr->GetPathPig(PathId);
        Parent->DeleteWaypointNode(Id);
        Parent->CreateMenuForPlayer(player);
    });

    AddGossipItemFor(player, GossipOptionIcon::None, "Back: ", 0, 0, [player, this](std::string /*callback*/)
    {
        auto Parent = sWaypointMgr->GetPathPig(PathId);
        Parent->CreateMenuForPlayer(player);
    });

    SendGossipMenuFor(player, 1, player);
}

void WaypointNode::CreateSplinePointMenu(Player* player, G3D::Vector3& splinePoint, int i)
{
    ClearGossipMenuFor(player);
    std::ostringstream ss;
    ss << "[" << i << "]: " << " |cffFF0000[X:" << splinePoint.x << " Y : " << splinePoint.y << " Z : " << splinePoint.z << "]";

    AddGossipItemFor(player, GossipOptionIcon::None, ss.str(), 0, 0, [this, player, &splinePoint, i](std::string /*callback*/)
    {
        CreateSplinePointMenu(player, splinePoint, i);
    });

    AddGossipItemFor(player, GossipOptionIcon::None, "Set new Position", 0, 0, [this, player, &splinePoint, i](std::string /*callback*/)
    {
        float x, y, z;
        player->GetPosition(x, y, z);

        Trinity::NormalizeMapCoord(x);
        Trinity::NormalizeMapCoord(y);

        splinePoint = G3D::Vector3(x, y, z);
        CreateSplinePointMenu(player, splinePoint, i);
    });
    AddGossipItemFor(player, GossipOptionIcon::None, "Teleport To Position", 0, 0, [this, player, &splinePoint, i](std::string /*callback*/)
    {
        player->NearTeleportTo({ splinePoint.x, splinePoint.y, splinePoint.z }, false, true);
        CreateSplinePointMenu(player, splinePoint, i);
    });
    AddGossipItemFor(player, GossipOptionIcon::None, "Remove", 0, 0, [this, player, &splinePoint, i](std::string /*callback*/)
    {
        SplinePoints.erase(SplinePoints.begin() + i);
        SendSplinePoints(player);
    });
    AddGossipItemFor(player, GossipOptionIcon::None, "Back", 0, 0, [this, player, &splinePoint, i](std::string /*callback*/)
    {
        SendSplinePoints(player);
    });
    SendGossipMenuFor(player, 1, player);
}

void WaypointNode::SendSplinePoints(Player* player)
{
    ClearGossipMenuFor(player);

    AddGossipItemFor(player, GossipOptionIcon::None, "Clear Spline Points " + std::to_string(SplinePoints.size()), 0, 0, [player, this](std::string /*callback*/)
    {
        SplinePoints.clear();
        SendSplinePoints(player);
    });

    AddGossipItemFor(player, GossipOptionIcon::None, "Add spline point", 0, 0, [player, this](std::string /*callback*/)
    {
        float x, y, z;
        player->GetPosition(x, y, z);

        Trinity::NormalizeMapCoord(x);
        Trinity::NormalizeMapCoord(y);

        SplinePoints.push_back(G3D::Vector3(x, y, z));
        SendSplinePoints(player);
    });

    std::ostringstream ss;
    for (int i = 0; i < SplinePoints.size(); ++i)
    {
        auto splinePoint = SplinePoints[i];
        ss << "[" << i << "]: " << " |cffFF0000[X:" << splinePoint.x << " Y : " << splinePoint.y << " Z : " << splinePoint.z << "]";

        AddGossipItemFor(player, GossipOptionIcon::None, ss.str(), 0, 0, [player, this, i](std::string /*callback*/)
        {
            CreateSplinePointMenu(player, SplinePoints[i], i);
        });

        ss.clear();
        ss.str("");
    }

    AddGossipItemFor(player, GossipOptionIcon::None, "Visualize Spline Points", 0, 0, [this, player](std::string /*callback*/)
    {
        for (int i = 0; i < SplinePoints.size(); ++i)
        {
            auto splinePoint = SplinePoints[i];

            if (auto creature = player->SummonCreature(1, { splinePoint.x, splinePoint.y, splinePoint.z }, TEMPSUMMON_TIMED_DESPAWN, 30s, 0, 0, player->GetGUID()))
                creature->SetLevel(i);
        }

        SendSplinePoints(player);
    });

    AddGossipItemFor(player, GossipOptionIcon::None, "Back", 0, 0, [this, player](std::string /*callback*/)
    {
        CreateMenuForPlayer(player);
    });

    SendGossipMenuFor(player, 1, player);
}

void WaypointPath::ReplacePathInDB()
{
    auto stmt = WorldDatabase.GetPreparedStatement(WORLD_DEL_WP_PATH_NODE);
    stmt->setUInt32(0, this->Id);
    WorldDatabase.Query(stmt);

    stmt = WorldDatabase.GetPreparedStatement(WORLD_DEL_WP_ADDON_PATH_NODE);
    stmt->setUInt32(0, this->Id);
    WorldDatabase.Query(stmt);

    for (auto& node : Nodes)
        node.ReplaceNodeInDB();
}

void WaypointPath::CreateMenuForPlayer(Player* player)
{
    ClearGossipMenuFor(player);

    AddGossipItemFor(player, GossipOptionIcon::None, "PathID: " + std::to_string(Id), 0, 0, [this, player](std::string /*callback*/)
    {
        CreateMenuForPlayer(player);
    });

    std::ostringstream ss;
    
    for (int i = 0; i < Nodes.size(); ++i)
    {
        auto& node = Nodes[i];

        ss << "Edit Node: [" << i << "]" << " |cffFF0000[X: " << node.X << " Y: " << node.Y << " Z: " << node.Z << "]";

        AddGossipItemFor(player, GossipOptionIcon::None, ss.str(), 0, 0, [this, player, i](std::string /*callback*/)
        {
            Nodes[i].CreateMenuForPlayer(player);
        });

        ss.clear();
        ss.str("");
    }

    AddGossipItemFor(player, GossipOptionIcon::None, "Create Node", 0, 0, [this, player](std::string /*callback*/)
    {
        ChatHandler(player).SendSysMessage("Created a node.");
        ReplacePathInDB();

        auto wpNode = WaypointNode();
        wpNode.PathId = Id;

        if (!Nodes.empty())
        {
            wpNode.Id = Nodes.size();
        }

        player->GetPosition(wpNode.X, wpNode.Y, wpNode.Z);

        Trinity::NormalizeMapCoord(wpNode.X);
        Trinity::NormalizeMapCoord(wpNode.Y);

        Nodes.push_back(wpNode);
        CreateMenuForPlayer(player);
    });

    AddGossipItemFor(player, GossipOptionIcon::None, "Save to DB", 0, 0, [player, this](std::string /*callback*/)
    {
        ReplacePathInDB();
        ChatHandler(player).SendSysMessage("Saved");
        CreateMenuForPlayer(player);
    });

    AddGossipItemFor(player, GossipOptionIcon::None, "Rel WP", 0, 0, [player, this](std::string /*callback*/)
    {
        if (player->GetSelectedUnit())
        {
            if (auto target = player->GetSelectedUnit()->ToCreature())
            {
                auto guidLow = target->GetSpawnId();
                WorldDatabasePreparedStatement* stmt = WorldDatabase.GetPreparedStatement(WORLD_SEL_CREATURE_ADDON_BY_GUID);

                stmt->setUInt64(0, guidLow);

                PreparedQueryResult result = WorldDatabase.Query(stmt);

                if (result)
                {
                    auto fields = result->Fetch();
                    stmt = WorldDatabase.GetPreparedStatement(WORLD_UPD_CREATURE_ADDON_PATH);

                    stmt->setUInt32(0, Id);
                    stmt->setStringView(1, fields[1].GetStringView());
                    stmt->setUInt64(2, guidLow);
                }
                else
                {
                    stmt = WorldDatabase.GetPreparedStatement(WORLD_INS_CREATURE_ADDON);

                    stmt->setUInt64(0, guidLow);
                    stmt->setUInt32(1, Id);
                    stmt->setStringView(2, "");
                }

                WorldDatabase.Query(stmt);

                stmt = WorldDatabase.GetPreparedStatement(WORLD_UPD_CREATURE_MOVEMENT_TYPE);

                stmt->setUInt8(0, uint8(WAYPOINT_MOTION_TYPE));
                stmt->setUInt64(1, guidLow);

                WorldDatabase.Query(stmt);

                target->LoadPath(Id);
                target->SetDefaultMovementType(WAYPOINT_MOTION_TYPE);
                target->GetMotionMaster()->Initialize();
                target->Say("Path loaded.", LANG_UNIVERSAL);
            }
        }

        CreateMenuForPlayer(player);
    });

    SendGossipMenuFor(player, 1, player);
}

void WaypointPath::DeleteWaypointNode(uint32 id)
{
    Nodes.erase(Nodes.begin() + id);

    if (!Nodes.empty())
    {
        // ReIdx
        uint32 Idx = 0;

        for (auto& node : Nodes)
        {
            node.Id = Idx++;
        }
    }
}
