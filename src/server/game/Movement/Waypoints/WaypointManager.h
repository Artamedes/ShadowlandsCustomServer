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

#ifndef TRINITY_WAYPOINTMANAGER_H
#define TRINITY_WAYPOINTMANAGER_H

#include "Define.h"
#include "WaypointDefines.h"
#include <vector>
#include <unordered_map>

class TC_GAME_API WaypointMgr
{
public:
    static WaypointMgr* instance();

    // Attempts to reload a single path from database
    void ReloadPath(uint32 id);

    // Loads all base waypoint data from database. Should only be called on startup.
    void Load();

    // Loads additional path data for waypoints from database. Should only be called on startup.
    void LoadWaypointAddons();

    // Returns the path from a given id
    WaypointPath const* GetPath(uint32 id) const;

    WaypointPath* GetPathPig(uint32 id);
    std::unordered_map<uint32, WaypointPath> _waypointStore;

private:
    WaypointMgr() { }
};

#define sWaypointMgr WaypointMgr::instance()

#endif
