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

#ifndef _MMAP_MANAGER_H
#define _MMAP_MANAGER_H

#include "Define.h"
#include "DetourNavMesh.h"
#include "DetourNavMeshQuery.h"
#include <string>
#include <unordered_map>
#include <vector>
#include "Util.h"

//  move map related classes
namespace MMAP
{
    typedef std::unordered_map<uint32, dtTileRef> MMapTileSet;
    typedef std::unordered_map<uint32, dtNavMeshQuery*> NavMeshQuerySet;

    // dummy struct to hold map's mmap data
    struct TC_COMMON_API MMapData
    {
        MMapData(dtNavMesh* mesh) : navMesh(mesh) { }
        ~MMapData()
        {
            for (NavMeshQuerySet::iterator i = navMeshQueries.begin(); i != navMeshQueries.end(); ++i)
                dtFreeNavMeshQuery(i->second);

            if (navMesh)
                dtFreeNavMesh(navMesh);
        }

        // we have to use single dtNavMeshQuery for every instance, since those are not thread safe
        NavMeshQuerySet navMeshQueries;     // instanceId to query

        dtNavMesh* navMesh;
        MMapTileSet loadedTileRefs;        // maps [map grid coords] to [dtTile]
    };

    typedef std::unordered_map<uint32, MMapData*> MMapDataSet;

    class TC_COMMON_API TransportMMapData
    {
    public:
        TransportMMapData(dtNavMesh* mesh, uint32 modelID);
        ~TransportMMapData();

        dtNavMeshQuery* GetNavMeshQuery() { return _navMeshQuery; }
        dtNavMesh* GetNavMesh() { return _navMesh; }

        void SetNavMeshQuery(dtNavMeshQuery* navMeshQuery) { _navMeshQuery = navMeshQuery; }

        dtTileRef GetTileRef() { return _tileRef; }
        void SetTileRef(dtTileRef tileRef) { _tileRef = tileRef; }

        void IncreaseLoadedTransports() { ++_loadedTransports; }
        void DecreaseLoadedTransports() { --_loadedTransports; }
        uint32 GetLoadedTransports() const { return _loadedTransports; }

    private:
        dtNavMeshQuery* _navMeshQuery;
        dtNavMesh* _navMesh;
        dtTileRef _tileRef;
        uint32 _modelID;
        uint32 _loadedTransports;
    };

    //typedef std::pair<uint32, uint32> TransportMMapKey;
    //typedef std::unordered_map<uint32, TransportMMapData*> TransportMMapDataSet;
    typedef std::unordered_map<uint32, TransportMMapData*> TransportMMapDataStore;

    // singleton class
    // holds all all access to mmap loading unloading and meshes
    class TC_COMMON_API MMapManager
    {
        public:
            MMapManager() : loadedTiles(0), thread_safe_environment(true) {}
            ~MMapManager();

            void InitializeThreadUnsafe(std::unordered_map<uint32, std::vector<uint32>> const& mapData);
            bool loadMap(std::string const& basePath, uint32 mapId, int32 x, int32 y);
            bool loadGameObject(uint32 displayId, std::string const& basePath);
            bool loadMapInstance(std::string const& basePath, uint32 mapId, uint32 instanceId);
            bool unloadMap(uint32 mapId, int32 x, int32 y);
            bool unloadMap(uint32 mapId);
            bool unloadMapInstance(uint32 mapId, uint32 instanceId);

            // the returned [dtNavMeshQuery const*] is NOT threadsafe
            dtNavMeshQuery const* GetNavMeshQuery(uint32 mapId, uint32 instanceId);
            dtNavMesh const* GetNavMesh(uint32 mapId);
            dtNavMeshQuery const* GetModelNavMeshQuery(uint32 displayId, uint32 instanceId);

            uint32 getLoadedTilesCount() const { return loadedTiles; }
            uint32 getLoadedMapsCount() const { return uint32(loadedMMaps.size()); }

            bool loadTransportMap(const std::string& basePath, uint32 modelID);
            bool unloadTransportMap(uint32 modelID);
            dtNavMesh const* GetTransportNavMesh(uint32 modelID);
            dtNavMeshQuery const* GetTransportNavMeshQuery(uint32 modelID);

        private:
            bool loadMapData(std::string const& basePath, uint32 mapId);
            uint32 packTileID(int32 x, int32 y);

            MMapDataSet::const_iterator GetMMapData(uint32 mapId) const;
            MMapDataSet::const_iterator GetModelData(uint32 modelId) const;
            MMapDataSet loadedMMaps;
            MMapDataSet loadedModels;
            uint32 loadedTiles;
            bool thread_safe_environment;

            std::unordered_map<uint32, uint32> parentMapData;

            TransportMMapData* loadTransportMapData(const std::string& basePath, uint32 modelID);

            TransportMMapData* GetTransportMMapData(uint32 modelID);
            TransportMMapDataStore loadedTransportMMaps;
    };
}

#endif
