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

#include "MMapManager.h"
#include "Errors.h"
#include "Log.h"
#include "MMapDefines.h"

namespace MMAP
{
    static char const* const MAP_FILE_NAME_FORMAT = "%smmaps/%04i.mmap";
    static char const* const TILE_FILE_NAME_FORMAT = "%smmaps/%04i%02i%02i.mmtile";

    static char const* const TRANSPORT_MAP_FILE_NAME_FORMAT = "%smmaps/go%05i.mmap";
    static char const* const TRANSPORT_TILE_FILE_NAME_FORMAT = "%smmaps/go%05i.mmtile";
    // ######################## MMapManager ########################
    MMapManager::~MMapManager()
    {
        for (std::pair<uint32 const, MMapData*>& loadedMMap : loadedMMaps)
            delete loadedMMap.second;
 
        for (TransportMMapDataStore::iterator i = loadedTransportMMaps.begin(); i != loadedTransportMMaps.end(); ++i)
            delete i->second;

        // by now we should not have maps loaded
        // if we had, tiles in MMapData->mmapLoadedTiles, their actual data is lost!
    }

    void MMapManager::InitializeThreadUnsafe(std::unordered_map<uint32, std::vector<uint32>> const& mapData)
    {
        childMapData = mapData;
        // the caller must pass the list of all mapIds that will be used in the VMapManager2 lifetime
        for (std::pair<uint32 const, std::vector<uint32>> const& mapId : mapData)
        {
            loadedMMaps.insert(MMapDataSet::value_type(mapId.first, nullptr));
            for (uint32 childMapId : mapId.second)
                parentMapData[childMapId] = mapId.first;
        }

        thread_safe_environment = false;
    }

    MMapDataSet::const_iterator MMapManager::GetMMapData(uint32 mapId) const
    {
        // return the iterator if found or end() if not found/NULL
        MMapDataSet::const_iterator itr = loadedMMaps.find(mapId);
        if (itr != loadedMMaps.cend() && !itr->second)
            itr = loadedMMaps.cend();

        return itr;
    }

    MMapDataSet::const_iterator MMapManager::GetModelData(uint32 modelId) const
    {
        // return the iterator if found or end() if not found/NULL
        MMapDataSet::const_iterator itr = loadedModels.find(modelId);
        if (itr != loadedModels.cend() && !itr->second)
            itr = loadedModels.cend();

        return itr;
    }

    bool MMapManager::loadMapData(std::string const& basePath, uint32 mapId)
    {
        // we already have this map loaded?
        MMapDataSet::iterator itr = loadedMMaps.find(mapId);
        if (itr != loadedMMaps.end())
        {
            if (itr->second)
                return true;
        }
        else
        {
            if (thread_safe_environment)
                itr = loadedMMaps.insert(MMapDataSet::value_type(mapId, nullptr)).first;
            else
                ABORT_MSG("Invalid mapId %u passed to MMapManager after startup in thread unsafe environment", mapId);
        }

        // load and init dtNavMesh - read parameters from file
        std::string fileName = Trinity::StringFormat(MAP_FILE_NAME_FORMAT, basePath.c_str(), mapId);
        FILE* file = fopen(fileName.c_str(), "rb");
        if (!file)
        {
            TC_LOG_DEBUG("maps", "MMAP:loadMapData: Error: Could not open mmap file '%s'", fileName.c_str());
            return false;
        }

        dtNavMeshParams params;
        uint32 count = uint32(fread(&params, sizeof(dtNavMeshParams), 1, file));
        fclose(file);
        if (count != 1)
        {
            TC_LOG_DEBUG("maps", "MMAP:loadMapData: Error: Could not read params from file '%s'", fileName.c_str());
            return false;
        }

        dtNavMesh* mesh = dtAllocNavMesh();
        ASSERT(mesh);
        if (dtStatusFailed(mesh->init(&params)))
        {
            dtFreeNavMesh(mesh);
            TC_LOG_ERROR("maps", "MMAP:loadMapData: Failed to initialize dtNavMesh for mmap %04u from file %s", mapId, fileName.c_str());
            return false;
        }

        TC_LOG_DEBUG("maps", "MMAP:loadMapData: Loaded %04i.mmap", mapId);

        // store inside our map list
        MMapData* mmap_data = new MMapData(mesh);

        itr->second = mmap_data;
        return true;
    }

    uint32 MMapManager::packTileID(int32 x, int32 y)
    {
        return uint32(x << 16 | y);
    }

    bool MMapManager::loadMap(std::string const& basePath, uint32 mapId, int32 x, int32 y)
    {
        if (!loadMapImpl(basePath, mapId, x, y))
            return false;

        bool success = true;
        auto childMaps = childMapData.find(mapId);
        if (childMaps != childMapData.end())
            for (uint32 childMapId : childMaps->second)
                if (!loadMapImpl(basePath, childMapId, x, y))
                    success = false;

        return success;
    }


    bool MMapManager::loadGameObject(uint32 displayId, std::string const& basePath)
    {
        // we already have this map loaded?
        if (loadedModels.find(displayId) != loadedModels.end())
            return true;

        // load and init dtNavMesh - read parameters from file
        std::string fileName = Trinity::StringFormat(MAP_FILE_NAME_FORMAT, basePath.c_str(), displayId);
        FILE* file = fopen(fileName.c_str(), "rb");
        if (!file)
        {
            TC_LOG_DEBUG("mmap", "MMAP:loadGameObject: Error: Could not open mmap file %s", fileName.c_str());
            return false;
        }

        MmapTileHeader fileHeader;
        fread(&fileHeader, sizeof(MmapTileHeader), 1, file);

        if (fileHeader.mmapMagic != MMAP_MAGIC)
        {
            TC_LOG_ERROR("mmap", "MMAP:loadGameObject: Bad header in mmap %s", fileName.c_str());
            fclose(file);
            return false;
        }

        if (fileHeader.mmapVersion != MMAP_VERSION)
        {
            TC_LOG_ERROR("mmap", "MMAP:loadGameObject: %s was built with generator v%i, expected v%i",
                fileName.c_str(), fileHeader.mmapVersion, MMAP_VERSION);
            fclose(file);
            return false;
        }
        unsigned char* data = (unsigned char*)dtAlloc(fileHeader.size, DT_ALLOC_PERM);
        ASSERT(data);

        size_t result = fread(data, fileHeader.size, 1, file);
        if (!result)
        {
            TC_LOG_ERROR("mmap", "MMAP:loadGameObject: Bad header or data in mmap %s", fileName.c_str());
            fclose(file);
            return false;
        }

        fclose(file);

        dtNavMesh* mesh = dtAllocNavMesh();
        ASSERT(mesh);
        dtStatus r = mesh->init(data, fileHeader.size, DT_TILE_FREE_DATA);
        if (dtStatusFailed(r))
        {
            dtFreeNavMesh(mesh);
            TC_LOG_ERROR("mmap", "MMAP:loadGameObject: Failed to initialize dtNavMesh from file %s. Result 0x%x.", fileName.c_str(), r);
            return false;
        }
        TC_LOG_INFO("mmap", "MMAP:loadGameObject: Loaded file %s [size=%u]", fileName.c_str(), fileHeader.size);

        MMapData* mmap_data = new MMapData(mesh);
        loadedModels.insert(std::pair<uint32, MMapData*>(displayId, mmap_data));
        return true;

    }

    bool MMapManager::loadMapImpl(std::string const& basePath, uint32 mapId, int32 x, int32 y)
    {
        // make sure the mmap is loaded and ready to load tiles
        if (!loadMapData(basePath, mapId))
            return false;

        // get this mmap data
        MMapData* mmap = loadedMMaps[mapId];
        ASSERT(mmap->navMesh);

        // check if we already have this tile loaded
        uint32 packedGridPos = packTileID(x, y);
        if (mmap->loadedTileRefs.find(packedGridPos) != mmap->loadedTileRefs.end())
            return false;

        // load this tile :: mmaps/MMMMXXYY.mmtile
        std::string fileName = Trinity::StringFormat(TILE_FILE_NAME_FORMAT, basePath.c_str(), mapId, x, y);
        FILE* file = fopen(fileName.c_str(), "rb");
        if (!file)
        {
            auto parentMapItr = parentMapData.find(mapId);
            if (parentMapItr != parentMapData.end())
            {
                fileName = Trinity::StringFormat(TILE_FILE_NAME_FORMAT, basePath.c_str(), parentMapItr->second, x, y);
                file = fopen(fileName.c_str(), "rb");
            }
        }

        if (!file)
        {
            TC_LOG_DEBUG("maps", "MMAP:loadMap: Could not open mmtile file '%s'", fileName.c_str());
            return false;
        }

        // read header
        MmapTileHeader fileHeader;
        if (fread(&fileHeader, sizeof(MmapTileHeader), 1, file) != 1 || fileHeader.mmapMagic != MMAP_MAGIC)
        {
            TC_LOG_ERROR("maps", "MMAP:loadMap: Bad header in mmap %04u%02i%02i.mmtile", mapId, x, y);
            fclose(file);
            return false;
        }

        if (fileHeader.mmapVersion != MMAP_VERSION)
        {
            TC_LOG_ERROR("maps", "MMAP:loadMap: %04u%02i%02i.mmtile was built with generator v%i, expected v%i",
                mapId, x, y, fileHeader.mmapVersion, MMAP_VERSION);
            fclose(file);
            return false;
        }

        long pos = ftell(file);
        fseek(file, 0, SEEK_END);
        if (pos < 0 || static_cast<int32>(fileHeader.size) > ftell(file) - pos)
        {
            TC_LOG_ERROR("maps", "MMAP:loadMap: %04u%02i%02i.mmtile has corrupted data size", mapId, x, y);
            fclose(file);
            return false;
        }

        fseek(file, pos, SEEK_SET);

        unsigned char* data = (unsigned char*)dtAlloc(fileHeader.size, DT_ALLOC_PERM);
        ASSERT(data);

        size_t result = fread(data, fileHeader.size, 1, file);
        if (!result)
        {
            TC_LOG_ERROR("maps", "MMAP:loadMap: Bad header or data in mmap %04u%02i%02i.mmtile", mapId, x, y);
            fclose(file);
            return false;
        }

        fclose(file);

        dtMeshHeader* header = (dtMeshHeader*)data;
        dtTileRef tileRef = 0;

        // memory allocated for data is now managed by detour, and will be deallocated when the tile is removed
        if (dtStatusSucceed(mmap->navMesh->addTile(data, fileHeader.size, DT_TILE_FREE_DATA, 0, &tileRef)))
        {
            mmap->loadedTileRefs.insert(std::pair<uint32, dtTileRef>(packedGridPos, tileRef));
            ++loadedTiles;
            TC_LOG_DEBUG("maps", "MMAP:loadMap: Loaded mmtile %04i[%02i, %02i] into %04i[%02i, %02i]", mapId, x, y, mapId, header->x, header->y);
            return true;
        }
        else
        {
            TC_LOG_ERROR("maps", "MMAP:loadMap: Could not load %04u%02i%02i.mmtile into navmesh", mapId, x, y);
            dtFree(data);
            return false;
        }
    }

    bool MMapManager::loadMapInstance(std::string const& basePath, uint32 mapId, uint32 instanceId)
    {
        if (!loadMapInstanceImpl(basePath, mapId, instanceId))
            return false;

        bool success = true;
        auto childMaps = childMapData.find(mapId);
        if (childMaps != childMapData.end())
            for (uint32 childMapId : childMaps->second)
                if (!loadMapInstanceImpl(basePath, childMapId, instanceId))
                    success = false;

        return success;
    }

    bool MMapManager::loadMapInstanceImpl(std::string const& basePath, uint32 mapId, uint32 instanceId)
    {
        if (!loadMapData(basePath, mapId))
            return false;

        MMapData* mmap = loadedMMaps[mapId];
        if (mmap->navMeshQueries.find(instanceId) != mmap->navMeshQueries.end())
            return true;

        // allocate mesh query
        dtNavMeshQuery* query = dtAllocNavMeshQuery();
        ASSERT(query);
        if (dtStatusFailed(query->init(mmap->navMesh, 1024)))
        {
            dtFreeNavMeshQuery(query);
            TC_LOG_ERROR("maps", "MMAP:GetNavMeshQuery: Failed to initialize dtNavMeshQuery for mapId %04u instanceId %u", mapId, instanceId);
            return false;
        }

        TC_LOG_DEBUG("maps", "MMAP:GetNavMeshQuery: created dtNavMeshQuery for mapId %04u instanceId %u", mapId, instanceId);
        mmap->navMeshQueries.insert(std::pair<uint32, dtNavMeshQuery*>(instanceId, query));
        return true;
    }

    bool MMapManager::unloadMap(uint32 mapId, int32 x, int32 y)
    {
        auto childMaps = childMapData.find(mapId);
        if (childMaps != childMapData.end())
            for (uint32 childMapId : childMaps->second)
                unloadMapImpl(childMapId, x, y);

        return unloadMapImpl(mapId, x, y);
    }

    bool MMapManager::unloadMapImpl(uint32 mapId, int32 x, int32 y)
    {
        // check if we have this map loaded
        MMapDataSet::const_iterator itr = GetMMapData(mapId);
        if (itr == loadedMMaps.end())
        {
            // file may not exist, therefore not loaded
            TC_LOG_DEBUG("maps", "MMAP:unloadMap: Asked to unload not loaded navmesh map. %04u%02i%02i.mmtile", mapId, x, y);
            return false;
        }

        MMapData* mmap = itr->second;

        // check if we have this tile loaded
        uint32 packedGridPos = packTileID(x, y);
        auto tileRefItr = mmap->loadedTileRefs.find(packedGridPos);
        if (tileRefItr == mmap->loadedTileRefs.end())
        {
            // file may not exist, therefore not loaded
            TC_LOG_DEBUG("maps", "MMAP:unloadMap: Asked to unload not loaded navmesh tile. %04u%02i%02i.mmtile", mapId, x, y);
            return false;
        }

        // unload, and mark as non loaded
        if (dtStatusFailed(mmap->navMesh->removeTile(tileRefItr->second, nullptr, nullptr)))
        {
            // this is technically a memory leak
            // if the grid is later reloaded, dtNavMesh::addTile will return error but no extra memory is used
            // we cannot recover from this error - assert out
            TC_LOG_ERROR("maps", "MMAP:unloadMap: Could not unload %04u%02i%02i.mmtile from navmesh", mapId, x, y);
            ABORT();
        }
        else
        {
            mmap->loadedTileRefs.erase(tileRefItr);
            --loadedTiles;
            TC_LOG_DEBUG("maps", "MMAP:unloadMap: Unloaded mmtile %04i[%02i, %02i] from %03i", mapId, x, y, mapId);
            return true;
        }

        return false;
    }

    bool MMapManager::unloadMap(uint32 mapId)
    {
        auto childMaps = childMapData.find(mapId);
        if (childMaps != childMapData.end())
            for (uint32 childMapId : childMaps->second)
                unloadMapImpl(childMapId);

        return unloadMapImpl(mapId);
    }

    bool MMapManager::unloadMapImpl(uint32 mapId)
    {
        MMapDataSet::iterator itr = loadedMMaps.find(mapId);
        if (itr == loadedMMaps.end() || !itr->second)
        {
            // file may not exist, therefore not loaded
            TC_LOG_DEBUG("maps", "MMAP:unloadMap: Asked to unload not loaded navmesh map %04u", mapId);
            return false;
        }

        // unload all tiles from given map
        MMapData* mmap = itr->second;
        for (MMapTileSet::iterator i = mmap->loadedTileRefs.begin(); i != mmap->loadedTileRefs.end(); ++i)
        {
            uint32 x = (i->first >> 16);
            uint32 y = (i->first & 0x0000FFFF);
            if (dtStatusFailed(mmap->navMesh->removeTile(i->second, nullptr, nullptr)))
                TC_LOG_ERROR("maps", "MMAP:unloadMap: Could not unload %04u%02i%02i.mmtile from navmesh", mapId, x, y);
            else
            {
                --loadedTiles;
                TC_LOG_DEBUG("maps", "MMAP:unloadMap: Unloaded mmtile %04i[%02i, %02i] from %04i", mapId, x, y, mapId);
            }
        }

        delete mmap;
        itr->second = nullptr;
        TC_LOG_DEBUG("maps", "MMAP:unloadMap: Unloaded %04i.mmap", mapId);

        return true;
    }

    bool MMapManager::unloadMapInstance(uint32 mapId, uint32 instanceId)
    {
        // check if we have this map loaded
        MMapDataSet::const_iterator itr = GetMMapData(mapId);
        if (itr == loadedMMaps.end())
        {
            // file may not exist, therefore not loaded
            TC_LOG_DEBUG("maps", "MMAP:unloadMapInstance: Asked to unload not loaded navmesh map %04u", mapId);
            return false;
        }

        MMapData* mmap = itr->second;
        if (mmap->navMeshQueries.find(instanceId) == mmap->navMeshQueries.end())
        {
            TC_LOG_DEBUG("maps", "MMAP:unloadMapInstance: Asked to unload not loaded dtNavMeshQuery mapId %04u instanceId %u", mapId, instanceId);
            return false;
        }

        dtNavMeshQuery* query = mmap->navMeshQueries[instanceId];

        dtFreeNavMeshQuery(query);
        mmap->navMeshQueries.erase(instanceId);
        TC_LOG_DEBUG("maps", "MMAP:unloadMapInstance: Unloaded mapId %04u instanceId %u", mapId, instanceId);

        return true;
    }

    dtNavMesh const* MMapManager::GetNavMesh(uint32 mapId)
    {
        MMapDataSet::const_iterator itr = GetMMapData(mapId);
        if (itr == loadedMMaps.end())
            return nullptr;

        return itr->second->navMesh;
    }

    dtNavMeshQuery const* MMapManager::GetNavMeshQuery(uint32 mapId, uint32 instanceId)
    {
        auto itr = GetMMapData(mapId);
        if (itr == loadedMMaps.end())
            return nullptr;

        auto queryItr = itr->second->navMeshQueries.find(instanceId);
        if (queryItr == itr->second->navMeshQueries.end())
            return nullptr;

        return queryItr->second;
    }

    dtNavMeshQuery const* MMapManager::GetModelNavMeshQuery(uint32 displayId, uint32 instanceId)
    {
        MMapDataSet::const_iterator itr = GetModelData(displayId);
        if (itr == loadedModels.end())
            return nullptr;

        MMapData* mmap = itr->second;

        if (mmap->navMeshQueries.find(instanceId) == mmap->navMeshQueries.end())
        {
            // allocate mesh query
            dtNavMeshQuery* query = dtAllocNavMeshQuery();
            ASSERT(query);
            if (dtStatusFailed(query->init(mmap->navMesh, 1024)))
            {
                dtFreeNavMeshQuery(query);
                TC_LOG_ERROR("mmap", "MMAP:GetNavMeshQuery: Failed to initialize dtNavMeshQuery for displayid %03u tid %u", displayId, instanceId);
                return nullptr;
            }

            TC_LOG_INFO("mmap", "MMAP:GetNavMeshQuery: created dtNavMeshQuery for displayid %03u tid %u", displayId, instanceId);
            mmap->navMeshQueries.insert(std::pair<uint32, dtNavMeshQuery*>(instanceId, query));
        }

        return mmap->navMeshQueries[instanceId];
    }

    TransportMMapData::TransportMMapData(dtNavMesh* mesh, uint32 modelID) : _navMeshQuery(nullptr), _loadedTransports(1), _tileRef(0)
    {
        _navMesh = mesh;
        _modelID = modelID;
    }

    TransportMMapData::~TransportMMapData()
    {
        dtFreeNavMeshQuery(_navMeshQuery);
        dtFreeNavMesh(_navMesh);
    }

    TransportMMapData* MMapManager::loadTransportMapData(const std::string& basePath, uint32 modelID)
    {
        // load and init dtNavMesh - read parameters from file
        std::string fileName = Trinity::StringFormat(TRANSPORT_MAP_FILE_NAME_FORMAT, basePath.c_str(), modelID);
        FILE* file = fopen(fileName.c_str(), "rb");
        if (!file)
        {
            TC_LOG_DEBUG("maps", "MMAP:loadMapData model: Error: Could not open model file '%s'", fileName.c_str());
            return nullptr;
        }

        dtNavMeshParams params;
        int count = fread(&params, sizeof(dtNavMeshParams), 1, file);
        fclose(file);
        if (count != 1)
        {
            TC_LOG_DEBUG("maps", "MMAP:loadMapData model: Error: Could not read params from file '%s'", fileName.c_str());
            return nullptr;
        }

        dtNavMesh* mesh = dtAllocNavMesh();
        ASSERT(mesh);
        if (dtStatusFailed(mesh->init(&params)))
        {
            dtFreeNavMesh(mesh);
            TC_LOG_ERROR("maps", "MMAP:loadMapData model: Failed to initialize dtNavMesh for model %05u from file %s", modelID, fileName.c_str());
            return nullptr;
        }

        TC_LOG_DEBUG("maps", "MMAP:loadMapData model: Loaded %05i.mmap", modelID);

        // store inside our map list
        TransportMMapData* mmap_data = new TransportMMapData(mesh, modelID);

        loadedTransportMMaps[modelID] = mmap_data;

        return mmap_data;
    }

    bool MMapManager::loadTransportMap(const std::string& basePath, uint32 modelID)
    {
        // we already have this model loaded?
        TransportMMapDataStore::iterator itr = loadedTransportMMaps.find(modelID);
        if (itr != loadedTransportMMaps.end())
        {
            if (TransportMMapData* mmap = itr->second)
            {
                mmap->IncreaseLoadedTransports();
                return true;
            }
        }

        // make sure the mmap is loaded and ready to load tiles
        TransportMMapData* mmap = loadTransportMapData(basePath, modelID);
        if (!mmap)
            return false;

        ASSERT(mmap->GetNavMesh());

        // load this tile :: mmaps/MMMMM.mmtile
        std::string fileName = Trinity::StringFormat(TRANSPORT_TILE_FILE_NAME_FORMAT, basePath.c_str(), modelID);
        FILE* file = fopen(fileName.c_str(), "rb");
        if (!file)
        {
            TC_LOG_DEBUG("maps", "MMAP:loadMap model: Could not open mmtile file '%s'", fileName.c_str());
            return false;
        }

        // read header
        MmapTileHeader fileHeader;
        if (fread(&fileHeader, sizeof(MmapTileHeader), 1, file) != 1 || fileHeader.mmapMagic != MMAP_MAGIC)
        {
            TC_LOG_ERROR("maps", "MMAP:loadMap model: Bad header in model %05u.mmtile", modelID);
            fclose(file);
            return false;
        }

        if (fileHeader.mmapVersion != MMAP_VERSION)
        {
            TC_LOG_ERROR("maps", "MMAP:loadMap model: %05u.mmtile was built with generator v%i, expected v%i", modelID, fileHeader.mmapVersion, MMAP_VERSION);
            fclose(file);
            return false;
        }

        long pos = ftell(file);
        fseek(file, 0, SEEK_END);
        if (int64(fileHeader.size) > ftell(file) - pos)
        {
            TC_LOG_ERROR("maps", "MMAP:loadMap model: %05.mmtile has corrupted data size", modelID);
            fclose(file);
            return false;
        }

        fseek(file, pos, SEEK_SET);

        unsigned char* data = (unsigned char*)dtAlloc(fileHeader.size, DT_ALLOC_PERM);
        ASSERT(data);

        size_t result = fread(data, fileHeader.size, 1, file);
        if (!result)
        {
            TC_LOG_ERROR("maps", "MMAP:loadMap model: Bad header or data in mmap %05.mmtile", modelID);
            fclose(file);
            return false;
        }

        fclose(file);

        dtMeshHeader* header = (dtMeshHeader*)data;
        dtTileRef tileRef = 0;

        // memory allocated for data is now managed by detour, and will be deallocated when the tile is removed
        if (dtStatusSucceed(mmap->GetNavMesh()->addTile(data, fileHeader.size, 0, 0, &tileRef)))
        {
            mmap->SetTileRef(tileRef);

            TC_LOG_DEBUG("maps", "MMAP:loadMap model: Loaded mmtile %05i", modelID);

            return true;
        }

        TC_LOG_ERROR("maps", "MMAP:loadMap model: Could not load %05.mmtile into navmesh", modelID);
        dtFree(data);

        return false;
    }

    bool MMapManager::unloadTransportMap(uint32 modelID)
    {
        TransportMMapDataStore::iterator iter = loadedTransportMMaps.find(modelID);
        if (iter == loadedTransportMMaps.end())
        {
            // file may not exist, therefore not loaded
            TC_LOG_DEBUG("maps", "MMAP:unloadMap model: Asked to unload not loaded navmesh model %05u", modelID);
            return false;
        }

        TransportMMapData* mmap = iter->second;
        if (!mmap)
        {
            // file may not exist, therefore not loaded
            TC_LOG_DEBUG("maps", "MMAP:unloadMap model: Asked to unload not loaded navmesh model %05u", modelID);
            return false;
        }

        // remove model movemap if all references are gone
        mmap->DecreaseLoadedTransports();
        if (mmap->GetLoadedTransports() > 0)
            return false;

        // unload all tiles from given map
        unsigned char* data = NULL;
        if (dtStatusFailed(mmap->GetNavMesh()->removeTile(mmap->GetTileRef(), &data, nullptr)))
            TC_LOG_ERROR("maps", "MMAP:unloadMap model: Could not unload %05u.mmtile from navmesh", modelID);
        else
        {
            dtFree(data);
            TC_LOG_DEBUG("maps", "MMAP:unloadMap model: Unloaded mmtile %05i", modelID);
        }

        delete mmap;
        iter->second = nullptr;

        loadedTransportMMaps.erase(modelID);

        TC_LOG_DEBUG("maps", "MMAP:unloadMap model: Unloaded %05i.mmap", modelID);

        return true;
    }

    TransportMMapData* MMapManager::GetTransportMMapData(uint32 modelID)
    {
        TransportMMapDataStore::iterator itr = loadedTransportMMaps.find(modelID);
        if (itr == loadedTransportMMaps.end())
            return nullptr;

        return itr->second;
    }

    dtNavMesh const* MMapManager::GetTransportNavMesh(uint32 modelID)
    {
        TransportMMapData* mmapData = GetTransportMMapData(modelID);
        if (!mmapData)
            return nullptr;

        return mmapData->GetNavMesh();
    }

    // todo: merge wthis with the model instance
    dtNavMeshQuery const* MMapManager::GetTransportNavMeshQuery(uint32 modelID)
    {
        TransportMMapData* mmapData = GetTransportMMapData(modelID);
        if (!mmapData)
            return nullptr;

        dtNavMeshQuery* navMeshQuery = mmapData->GetNavMeshQuery();
        if (!navMeshQuery)
        {
            // allocate mesh query
            dtNavMeshQuery* query = dtAllocNavMeshQuery();
            ASSERT(query);

            if (dtStatusFailed(query->init(mmapData->GetNavMesh(), 1024)))
            {
                dtFreeNavMeshQuery(query);
                TC_LOG_ERROR("maps", "MMAP:GetNavMeshQuery: Failed to initialize dtNavMeshQuery for modelID %05u", modelID);
                return nullptr;
            }

            TC_LOG_DEBUG("maps", "MMAP:GetNavMeshQuery: created dtNavMeshQuery for modelID %05u", modelID);

            mmapData->SetNavMeshQuery(query);

            return query;
        }

        return navMeshQuery;
    }
}
