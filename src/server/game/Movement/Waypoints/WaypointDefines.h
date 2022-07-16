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

#ifndef TRINITY_WAYPOINTDEFINES_H
#define TRINITY_WAYPOINTDEFINES_H

#include "Define.h"
#include "G3D/Vector3.h"
#include "Optional.h"
#include <vector>
#include <string>

class Player;

enum class WaypointMoveType : uint32
{
    Walk = 0,
    Run  = 1,
    Land = 2,
    TakeOff = 3,
    Max = 4,
};

struct TC_GAME_API WaypointNode
{
    WaypointNode() : PathId(0), Id(0), X(0.f), Y(0.f), Z(0.f), Velocity(0.f), Delay(0), EventId(0), MoveType(WaypointMoveType::Walk), EventChance(0), SmoothTransition(false) { }
    WaypointNode(uint32 pathId, uint32 id, float x, float y, float z, Optional<float> orientation = { }, float velocity = 0.f, uint32 delay = 0, bool smoothTransition = false) :
        PathId(pathId), Id(id), X(x), Y(y), Z(z), Orientation(orientation), Velocity(velocity), Delay(delay), SmoothTransition(smoothTransition)
    {
        EventId = 0;
        MoveType = WaypointMoveType::Walk;
        EventChance = 100;
    }

    uint32 PathId;
    uint32 Id;
    float X, Y, Z;
    Optional<float> Orientation;
    float Velocity;
    uint32 Delay;
    uint32 EventId;
    WaypointMoveType MoveType;
    uint8 EventChance;
    bool SmoothTransition;
    std::vector<G3D::Vector3> SplinePoints;
    uint64 wpguid = 0ULL;

    void ReplaceNodeInDB();

    void CreateMenuForPlayer(Player* player);
    void SendSplinePoints(Player* player);
    void CreateSplinePointMenu(Player* player, G3D::Vector3& position, int index);
};

struct TC_GAME_API WaypointPath
{
    WaypointPath() : Id(0) { }
    WaypointPath(uint32 _id, std::vector<WaypointNode>&& _nodes)
    {
        Id = _id;
        Nodes = _nodes;
    }

    std::vector<WaypointNode> Nodes;
    uint32 Id;

    void ReplacePathInDB();
    void CreateMenuForPlayer(Player* player);
    void DeleteWaypointNode(uint32 id);
};

#endif
