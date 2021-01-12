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

#include "ScenarioMgr.h"
#include "Containers.h"
#include "DatabaseEnv.h"
#include "DB2Stores.h"
#include "InstanceScenario.h"
#include "Log.h"
#include "Map.h"
#include "ScenarioPackets.h"

ScenarioMgr* ScenarioMgr::Instance()
{
    static ScenarioMgr instance;
    return &instance;
}

InstanceScenario* ScenarioMgr::CreateInstanceScenario(InstanceMap* map, TeamId team, LFGDungeonsEntry const* dungeonEntry) const
{
    ScenarioDBDataContainer::const_iterator dbDataItr = _scenarioDBData.find(std::make_pair(map->GetId(), map->GetDifficultyID()));
    ScenarioDBDataDungeonsContainer::const_iterator dbDungeonsDataItr;
    // Check for different dungeon ID
    if (dungeonEntry)
        dbDungeonsDataItr = _scenarioDBDungeonsData.find(std::make_pair(map->GetId(), dungeonEntry->ID));

    // No scenario registered for this map and difficulty in the database
    if (!dungeonEntry || dbDungeonsDataItr == _scenarioDBDungeonsData.end())
    {
        if (dbDataItr == _scenarioDBData.end())
        {
            // We then search for global scenario
            dbDataItr = _scenarioDBData.find(std::make_pair(map->GetId(), 0));

            // No more luck, return
            if (dbDataItr == _scenarioDBData.end())
                return nullptr;
        }
    }

    uint32 scenarioID = 0;
    switch (team)
    {
        case TEAM_ALLIANCE:
            if (!dungeonEntry || dbDungeonsDataItr == _scenarioDBDungeonsData.end())
                scenarioID = dbDataItr->second.Scenario_A;
            else
                scenarioID = dbDungeonsDataItr->second.Scenario_A;
            break;
        case TEAM_HORDE:
            if (!dungeonEntry || dbDungeonsDataItr == _scenarioDBDungeonsData.end())
                scenarioID = dbDataItr->second.Scenario_H;
            else
                scenarioID = dbDungeonsDataItr->second.Scenario_H;
            break;
        default:
            break;
    }

    ScenarioData const* scenarioData = GetScenarioData(scenarioID, team);
    if(!scenarioData)
    {
        TC_LOG_ERROR("scenario", "Table `scenarios` contained data linking scenario (Id: %u) to map (Id: %u), difficulty (Id: %u) but no scenario data was found related to that scenario Id.", scenarioID, map->GetId(), map->GetDifficultyID());
        return nullptr;
    }

    return new InstanceScenario(map, scenarioData);
}

void ScenarioMgr::LoadDBData()
{
    _scenarioDBData.clear();
    _scenarioDBDungeonsData.clear();

    uint32 oldMSTime = getMSTime();

    QueryResult result = WorldDatabase.Query("SELECT map, difficulty, dungeonID, scenario_A, scenario_H FROM scenarios");

    if (!result)
    {
        TC_LOG_INFO("server.loading", ">> Loaded 0 scenarios. DB table `scenarios` is empty!");
        return;
    }

    do
    {
        Field* fields = result->Fetch();

        uint32 mapId = fields[0].GetUInt32();
        if (!sMapStore.LookupEntry(mapId))
        {
            TC_LOG_ERROR("sql.sql", "Map %u defined in `scenarios` does not exist, skipped.", mapId);
            continue;
        }

        uint8 difficulty = fields[1].GetUInt8();
        if (difficulty)
        {
            if (!sDB2Manager.GetMapDifficultyData(mapId, Difficulty(difficulty)))
            {
                TC_LOG_ERROR("sql.sql", "Map %u referenced in `scenarios` does not have difficulty %u, skipped", mapId, difficulty);
                continue;
            }
        }

        uint32 dungeonID = fields[2].GetUInt32();
        if (dungeonID)
        {
            if (!sLFGDungeonsStore.LookupEntry(dungeonID))
            {
                TC_LOG_ERROR("sql.sql", "dungeonID %u defined in `scenarios` does not exist, skipped.", dungeonID);
                continue;
            }
        }

        uint32 scenarioAllianceId = fields[3].GetUInt32();
        if (scenarioAllianceId > 0 && _scenarioData.find(scenarioAllianceId) == _scenarioData.end())
        {
            TC_LOG_ERROR("sql.sql", "ScenarioMgr::LoadDBData: DB Table `scenarios`, column scenario_A contained an invalid scenario (Id: %u)!", scenarioAllianceId);
            continue;
        }

        uint32 scenarioHordeId = fields[4].GetUInt32();
        if (scenarioHordeId > 0 && _scenarioData.find(scenarioHordeId) == _scenarioData.end())
        {
            TC_LOG_ERROR("sql.sql", "ScenarioMgr::LoadDBData: DB Table `scenarios`, column scenario_H contained an invalid scenario (Id: %u)!", scenarioHordeId);
            continue;
        }

        if (scenarioHordeId == 0)
            scenarioHordeId = scenarioAllianceId;


        if (!dungeonID)
        {
            ScenarioDBData& data = _scenarioDBData[std::make_pair(mapId, difficulty)];
            data.MapID = mapId;
            data.DifficultyID = difficulty;
            data.DungeonID = dungeonID;
            data.Scenario_A = scenarioAllianceId;
            data.Scenario_H = scenarioHordeId;
        }
        else
        {
            ScenarioDBData& data = _scenarioDBDungeonsData[std::make_pair(mapId, dungeonID)];
            data.MapID = mapId;
            data.DifficultyID = difficulty;
            data.DungeonID = dungeonID;
            data.Scenario_A = scenarioAllianceId;
            data.Scenario_H = scenarioHordeId;
        }
    }
    while (result->NextRow());

    TC_LOG_INFO("server.loading", ">> Loaded " SZFMTD " instance scenario entries in %u ms", _scenarioDBData.size(), GetMSTimeDiffToNow(oldMSTime));
}

void ScenarioMgr::LoadDB2Data()
{
    _scenarioData.clear();
    _hordeScenarioData.clear();
    _scenarioTeemingData.clear();
    _hordeScenarioTeemingData.clear();

    std::unordered_map<uint32, std::map<uint8, ScenarioStepEntry const*>> scenarioSteps;
    std::unordered_map<uint32, std::map<uint8, ScenarioStepEntry const*>> hordeScenarioSteps;
    std::unordered_map<uint32, std::map<uint8, ScenarioStepEntry const*>> scenarioTeemingSteps;
    std::unordered_map<uint32, std::map<uint8, ScenarioStepEntry const*>> hordeScenarioTeemingSteps;
    uint32 deepestCriteriaTreeSize = 0;

    for (ScenarioStepEntry const* step : sScenarioStepStore)
    {
        if (IsAffixesTeemingCriteriaTree(step->Criteriatreeid, true)) // Scenario for Mythic+ have 2 criteria one for Affix Teeming enable and other without the affix only for horde, ex Siege of Boralus
        {
            hordeScenarioTeemingSteps[step->ScenarioID][step->OrderIndex] = step;
            continue;
        }

        if (IsAffixesTeemingCriteriaTree(step->Criteriatreeid)) // Scenario for Mythic+ have 2 criteria one for Affix Teeming enable and other without the affix
        {
            scenarioTeemingSteps[step->ScenarioID][step->OrderIndex] = step;
            continue;
        }

        if (IsHordeCriteriaTree(step->Criteriatreeid)) // Exist some scenario like Siege of Boralus that use a special criteria with the same Scenario, stupid stuff weird of blizzard
        {
            hordeScenarioSteps[step->ScenarioID][step->OrderIndex] = step;
            continue;
        }

        scenarioSteps[step->ScenarioID][step->OrderIndex] = step;
        if (CriteriaTree const* tree = sCriteriaMgr->GetCriteriaTree(step->Criteriatreeid))
        {
            uint32 criteriaTreeSize = 0;
            CriteriaMgr::WalkCriteriaTree(tree, [&criteriaTreeSize](CriteriaTree const* /*tree*/)
            {
                ++criteriaTreeSize;
            });
            deepestCriteriaTreeSize = std::max(deepestCriteriaTreeSize, criteriaTreeSize);
        }
    }

    ASSERT(deepestCriteriaTreeSize < MAX_ALLOWED_SCENARIO_POI_QUERY_SIZE, "MAX_ALLOWED_SCENARIO_POI_QUERY_SIZE must be at least %u", deepestCriteriaTreeSize + 1);

    for (ScenarioEntry const* scenario : sScenarioStore)
    {
        if (!hordeScenarioTeemingSteps[scenario->ID].empty())
        {
            ScenarioData& data = _hordeScenarioTeemingData[scenario->ID];
            data.Entry = scenario;
            data.Steps = std::move(hordeScenarioTeemingSteps[scenario->ID]);
        }

        if (!scenarioTeemingSteps[scenario->ID].empty())
        {
            ScenarioData& data = _scenarioTeemingData[scenario->ID];
            data.Entry = scenario;
            data.Steps = std::move(scenarioTeemingSteps[scenario->ID]);
        }

        if (!hordeScenarioSteps[scenario->ID].empty())
        {
            ScenarioData& data = _hordeScenarioData[scenario->ID];
            data.Entry = scenario;
            data.Steps = std::move(hordeScenarioSteps[scenario->ID]);
        }

        ScenarioData& data = _scenarioData[scenario->ID];
        data.Entry = scenario;
        data.Steps = std::move(scenarioSteps[scenario->ID]);
    }
}

void ScenarioMgr::LoadScenarioPOI()
{
    uint32 oldMSTime = getMSTime();

    _scenarioPOIStore.clear(); // need for reload case

    uint32 count = 0;

    //                                                      0            1        2     3       4         5       6          7               8                        9
    QueryResult result = WorldDatabase.Query("SELECT CriteriaTreeID, BlobIndex, Idx1, MapID, UiMapID, Priority, Flags, WorldEffectID, PlayerConditionID, NavigationPlayerConditionID FROM scenario_poi ORDER BY CriteriaTreeID, Idx1");
    if (!result)
    {
        TC_LOG_ERROR("server.loading", ">> Loaded 0 scenario POI definitions. DB table `scenario_poi` is empty.");
        return;
    }

    //                                                       0        1    2  3  4
    QueryResult pointsResult = WorldDatabase.Query("SELECT CriteriaTreeID, Idx1, X, Y, Z FROM scenario_poi_points ORDER BY CriteriaTreeID DESC, Idx1, Idx2");

    std::unordered_map<int32, std::map<int32, std::vector<ScenarioPOIPoint>>> allPoints;

    if (pointsResult)
    {
        Field* fields = pointsResult->Fetch();

        do
        {
            fields = pointsResult->Fetch();

            int32 CriteriaTreeID = fields[0].GetInt32();
            int32 Idx1 = fields[1].GetInt32();
            int32 X = fields[2].GetInt32();
            int32 Y = fields[3].GetInt32();
            int32 Z = fields[4].GetInt32();

            allPoints[CriteriaTreeID][Idx1].emplace_back(X, Y, Z);
        } while (pointsResult->NextRow());
    }

    do
    {
        Field* fields = result->Fetch();

        int32 criteriaTreeID = fields[0].GetInt32();
        int32 blobIndex = fields[1].GetInt32();
        int32 idx1 = fields[2].GetInt32();
        int32 mapID = fields[3].GetInt32();
        int32 uiMapID = fields[4].GetInt32();
        int32 priority = fields[5].GetInt32();
        int32 flags = fields[6].GetInt32();
        int32 worldEffectID = fields[7].GetInt32();
        int32 playerConditionID = fields[8].GetInt32();
        int32 navigationPlayerConditionID = fields[9].GetInt32();

        if (!sCriteriaMgr->GetCriteriaTree(criteriaTreeID))
            TC_LOG_ERROR("sql.sql", "`scenario_poi` CriteriaTreeID (%u) Idx1 (%u) does not correspond to a valid criteria tree", criteriaTreeID, idx1);

        if (std::map<int32, std::vector<ScenarioPOIPoint>>* blobs = Trinity::Containers::MapGetValuePtr(allPoints, criteriaTreeID))
        {
            if (std::vector<ScenarioPOIPoint>* points = Trinity::Containers::MapGetValuePtr(*blobs, idx1))
            {
                _scenarioPOIStore[criteriaTreeID].emplace_back(blobIndex, mapID, uiMapID, priority, flags, worldEffectID, playerConditionID, navigationPlayerConditionID, std::move(*points));
                ++count;
                continue;
            }
        }

        TC_LOG_ERROR("server.loading", "Table scenario_poi references unknown scenario poi points for criteria tree id %i POI id %i", criteriaTreeID, blobIndex);

    } while (result->NextRow());

    TC_LOG_INFO("server.loading", ">> Loaded %u scenario POI definitions in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

ScenarioPOIVector const* ScenarioMgr::GetScenarioPOIs(int32 criteriaTreeID) const
{
    auto itr = _scenarioPOIStore.find(criteriaTreeID);
    if (itr != _scenarioPOIStore.end())
        return &itr->second;

    return nullptr;
}


ScenarioDBData const* ScenarioMgr::GetScenarioOnMap(uint32 mapId, uint8 difficultyID /*= 0*/) const
{
    ScenarioDBDataContainer::const_iterator dbDataItr = _scenarioDBData.find(std::make_pair(mapId, difficultyID));
    if (dbDataItr == _scenarioDBData.end())
        return nullptr; 

    return &dbDataItr->second;
}

ScenarioData const* ScenarioMgr::GetScenarioData(uint32 scenarioID, TeamId team, bool teeming /*= false*/) const
{
    if (teeming)
    {
        if (team == TEAM_HORDE)
        {
            auto teemingHordeItr = _hordeScenarioTeemingData.find(scenarioID);
            if (teemingHordeItr != _hordeScenarioTeemingData.end())
                return &teemingHordeItr->second;            
        }

        auto teemingItr = _scenarioTeemingData.find(scenarioID);
        if (teemingItr != _scenarioTeemingData.end())
            return &teemingItr->second;
    }

    if (team == TEAM_HORDE)
    {
        auto hordeItr = _hordeScenarioData.find(scenarioID);
        if (hordeItr != _hordeScenarioData.end())
            return &hordeItr->second;
    }

    auto itr = _scenarioData.find(scenarioID);
    if (itr != _scenarioData.end())
        return &itr->second;

    return nullptr;
}

bool ScenarioMgr::IsAffixesTeemingCriteriaTree(uint32 CriteriaTreeID, bool horde /*= false*/) const
{
    //ToDo port to a new table in DB
    switch (CriteriaTreeID)
    {
    case 47415: //Halls of Valor
    case 50599: //Black Rook Hold
    case 51246: //Eye of Azshara
    case 51710: //Darkheart Thicket
    case 51880: //Vault of the Wardens
    case 52278: //Neltharion's Lair
    case 52327: //Maw of Souls
    case 52427: //The Arcway
    case 52471: //Court of Stars
    case 57810: //Upper Return to Karazhan
    case 57866: //Lower Return to Karazhan
    case 58715: //Cathedral of Eternal Night
    case 60933: //Seat of the Triumvirate
    case 66648: //Shrine fo the Storm
    case 66605: //Underrot
    case 66567: //Temple of Sethraliss
    case 66485: //King Rest
    case 66408: //Waycrest Manor
    case 66317: //The Motherlode!!
    case 65674: //Free Hold
    case 65745: //Tol Dagor
    case 65621: //Ataldazar
        return true;
    case 67255: //Siege of Boralus
        if (!horde)
            return true;
    case 67311: //Siege of Boralus
        if (horde)
            return true;
    }

    return false;
}

bool ScenarioMgr::IsHordeCriteriaTree(uint32 CriteriaTreeID) const
{
    return CriteriaTreeID == 67283; //Siege of Boralus Horde Criteria
}
