/*
 * Copyright (C) 2017-2020 AshamaneProject <https://github.com/AshamaneProject>
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

#include "ChallengeModeMgr.h"
#include "Containers.h"
#include "DB2Stores.h"
#include "DBCEnums.h"
#include "GameTables.h"
#include "Item.h"
#include "LootPackets.h"
#include "StringConvert.h"
#include <sstream>
#include "ObjectAccessor.h"

ChallengeModeMgr* ChallengeModeMgr::instance()
{
    static ChallengeModeMgr instance;
    return &instance;
}

bool ChallengeMember::operator<(const ChallengeMember& i) const
{
    return playerGuid.GetCounter() > i.playerGuid.GetCounter();
}

bool ChallengeMember::operator==(const ChallengeMember& i) const
{
    return playerGuid.GetCounter() == i.playerGuid.GetCounter();
}


void ChallengeModeMgr::CheckBestMapId(ChallengeData* challengeData)
{
    if (!challengeData)
        return;

    if (!_bestForMap[challengeData->ChallengeID] || _bestForMap[challengeData->ChallengeID]->RecordTime > challengeData->RecordTime)
        _bestForMap[challengeData->ChallengeID] = challengeData;
}

void ChallengeModeMgr::CheckBestGuildMapId(ChallengeData* challengeData)
{
    if (!challengeData || !challengeData->GuildID)
        return;

    if (!m_GuildBest[challengeData->GuildID][challengeData->ChallengeID] || m_GuildBest[challengeData->GuildID][challengeData->ChallengeID]->RecordTime > challengeData->RecordTime)
        m_GuildBest[challengeData->GuildID][challengeData->ChallengeID] = challengeData;
}

bool ChallengeModeMgr::CheckBestMemberMapId(ObjectGuid const& guid, ChallengeData* challengeData)
{
    bool isBest = false;
    if (!_challengesOfMember[guid][challengeData->ChallengeID] || _challengesOfMember[guid][challengeData->ChallengeID]->RecordTime > challengeData->RecordTime)
    {
        _challengesOfMember[guid][challengeData->ChallengeID] = challengeData;
        isBest = true;
    }

    if (!_lastForMember[guid][challengeData->ChallengeID] || _lastForMember[guid][challengeData->ChallengeID]->CompleteDate < challengeData->CompleteDate)
        _lastForMember[guid][challengeData->ChallengeID] = challengeData;

    _challengeWeekList[guid].insert(challengeData);

    return isBest;
}

void ChallengeModeMgr::SaveChallengeToDB(ChallengeData const* challengeData)
{
    CharacterDatabaseTransaction trans = CharacterDatabase.BeginTransaction();

    CharacterDatabasePreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_INS_CHALLENGE);
    stmt->setUInt32(0, challengeData->ID);
    stmt->setUInt64(1, challengeData->GuildID);
    stmt->setUInt16(2, challengeData->MapID);
    stmt->setUInt32(3, challengeData->RecordTime);
    stmt->setUInt32(4, challengeData->StartDate);
    stmt->setUInt32(5, challengeData->CompleteDate);
    stmt->setUInt8(6, challengeData->ChallengeLevel);
    stmt->setUInt8(7, challengeData->TimerLevel);
    std::ostringstream affixesListIDs;
    for (uint16 affixe : challengeData->Affixes)
        if (affixe)
            affixesListIDs << affixe << ' ';
    stmt->setString(8, affixesListIDs.str());
    stmt->setUInt32(9, challengeData->ChestID);
    stmt->setUInt32(10, challengeData->ChallengeID);
    stmt->setUInt8(11, challengeData->Expansion);
    trans->Append(stmt);

    for (auto const& v : challengeData->members)
    {
        stmt = CharacterDatabase.GetPreparedStatement(CHAR_INS_CHALLENGE_MEMBER);
        stmt->setUInt32(0, challengeData->ID);
        stmt->setUInt64(1, v.playerGuid.GetCounter());
        stmt->setUInt64(2, v.guildGuid.GetCounter());
        stmt->setUInt16(3, v.specId);
        stmt->setUInt32(4, v.ChallengeLevel);
        stmt->setUInt32(5, v.CompleteDate);
        stmt->setUInt32(6, v.ChestID);
        stmt->setUInt32(7, v.Ilevel);
        stmt->setUInt32(8, v.Race);
        trans->Append(stmt);
    }

    CharacterDatabase.CommitTransaction(trans);
}

void ChallengeModeMgr::LoadFromDB()
{
    if (QueryResult result = CharacterDatabase.Query("SELECT `ID`, `GuildID`, `MapID`, `RecordTime`, `StartDate`, `CompleteDate`, `ChallengeLevel`, `TimerLevel`, `Affixes`, `ChestID`, `ChallengeID`, Expansion FROM `challenge`"))
    {
        do
        {
            Field* fields = result->Fetch();

            auto challengeData = new ChallengeData;
            challengeData->ID = fields[0].GetUInt64();
            challengeData->GuildID = fields[1].GetUInt64();
            challengeData->MapID = fields[2].GetUInt16();
            challengeData->RecordTime = fields[3].GetUInt32();
            if (challengeData->RecordTime < 10000)
                challengeData->RecordTime *= IN_MILLISECONDS;
            challengeData->StartDate = fields[4].GetUInt32();
            challengeData->CompleteDate = fields[5].GetUInt32();
            challengeData->ChallengeLevel = fields[6].GetUInt8();
            challengeData->TimerLevel = fields[7].GetUInt8();
            challengeData->ChestID = fields[9].GetUInt32();
            challengeData->ChallengeID = fields[10].GetUInt16();
            challengeData->Expansion = fields[11].GetUInt8();
            if (!challengeData->ChallengeID)
                if (MapChallengeModeEntry const* challengeEntry = sDB2Manager.GetChallengeModeByMapID(challengeData->MapID))
                    challengeData->ChallengeID = challengeEntry->ID;

            challengeData->Affixes.fill(0);

            uint8 i = 0;
            for (auto str : Trinity::Tokenize(fields[8].GetStringView(), ' ', false))
                if (Optional<uint32> affix = Trinity::StringTo<uint32>(str))
                    challengeData->Affixes[i] = affix.value();

            _challengeMap[challengeData->ID] = challengeData;
            CheckBestMapId(challengeData);
            CheckBestGuildMapId(challengeData);

        } while (result->NextRow());
    }

    if (QueryResult result = CharacterDatabase.Query("SELECT `ID`, `Member`, `GuildID`, `SpecID`, `ChallengeLevel`, `CompleteDate`, `ChestID`, `Ilevel`, `Race` FROM `challenge_member`"))
    {
        do
        {
            Field* fields = result->Fetch();
            ChallengeMember member;
            member.playerGuid = ObjectGuid::Create<HighGuid::Player>(fields[1].GetUInt64());
            member.guildGuid = ObjectGuid::Create<HighGuid::Guild>(fields[2].GetUInt64());
            member.specId = fields[3].GetUInt16();
            member.ChallengeLevel = fields[4].GetUInt32();
            member.CompleteDate = fields[5].GetUInt32();
            member.ChestID = fields[6].GetUInt32();   
            member.Ilevel = fields[7].GetUInt32();
            member.Race = fields[8].GetUInt32();

            auto itr = _challengeMap.find(fields[0].GetUInt64());
            if (itr == _challengeMap.end())
                continue;

            itr->second->members.insert(member);
            CheckBestMemberMapId(member.playerGuid, itr->second);
        } while (result->NextRow());
    }

    for (auto v : _challengeMap)
        if (v.second->members.empty())
            CharacterDatabase.PQuery("DELETE FROM `challenge` WHERE `ID` = '%u';", v.first);

    if (QueryResult result = CharacterDatabase.Query("SELECT `guid`, `chestListID`, `date`, `ChallengeLevel`, `ChallengeID` FROM `challenge_oplote_loot`"))
    {
        do
        {
            Field* fields = result->Fetch();
            ObjectGuid guid = ObjectGuid::Create<HighGuid::Player>(fields[0].GetUInt64());
            OploteLoot& lootOplote = _oploteWeekLoot[guid];
            lootOplote.Date = fields[2].GetUInt32();
            lootOplote.ChallengeLevel = fields[3].GetUInt32();
            lootOplote.ChallengeID = fields[4].GetUInt32();
            lootOplote.needSave = false;
            lootOplote.guid = guid;

            for (auto str : Trinity::Tokenize(fields[1].GetStringView(), ' ', false))
                if (Optional<uint32> chestList = Trinity::StringTo<uint32>(str))
                    lootOplote.chestListID.insert(chestList.value());

        } while (result->NextRow());
    }

    GenerateCurrentWeekAffixes();

    //if ((sWorld->getIntConfig(CONFIG_CHALLENGE_MANUAL_AFFIX1) > 0 && sWorld->getIntConfig(CONFIG_CHALLENGE_MANUAL_AFFIX1) < MAX_AFFIXES)  &&
    //    (sWorld->getIntConfig(CONFIG_CHALLENGE_MANUAL_AFFIX2) > 0 && sWorld->getIntConfig(CONFIG_CHALLENGE_MANUAL_AFFIX2) < MAX_AFFIXES)  &&
    //    (sWorld->getIntConfig(CONFIG_CHALLENGE_MANUAL_AFFIX3) > 0 && sWorld->getIntConfig(CONFIG_CHALLENGE_MANUAL_AFFIX3) < MAX_AFFIXES)  &&
    //    (sWorld->getIntConfig(CONFIG_CHALLENGE_MANUAL_AFFIX4) > 0 && sWorld->getIntConfig(CONFIG_CHALLENGE_MANUAL_AFFIX4) < MAX_AFFIXES))
    //    GenerateManualAffixes();
}

ChallengeData* ChallengeModeMgr::BestServerChallenge(uint16 ChallengeID)
{
    return Trinity::Containers::MapGetValuePtr(_bestForMap, ChallengeID);
}

ChallengeData* ChallengeModeMgr::BestGuildChallenge(ObjectGuid::LowType const& GuildID, uint16 ChallengeID)
{
    if (!GuildID)
        return nullptr;

    auto itr = m_GuildBest.find(GuildID);
    if (itr == m_GuildBest.end())
        return nullptr;

    auto itr2 = itr->second.find(ChallengeID);
    if (itr2 == itr->second.end())
        return nullptr;

    return itr2->second;
}

void ChallengeModeMgr::SetChallengeMapData(ObjectGuid::LowType const& ID, ChallengeData* data)
{
    _challengeMap[ID] = data;
}

ChallengeByMap* ChallengeModeMgr::BestForMember(ObjectGuid const& guid)
{
    return Trinity::Containers::MapGetValuePtr(_challengesOfMember, guid);
}

ChallengeByMap* ChallengeModeMgr::LastForMember(ObjectGuid const& guid)
{
    return Trinity::Containers::MapGetValuePtr(_lastForMember, guid);
}

ChallengeData* ChallengeModeMgr::LastForMemberMap(ObjectGuid const& guid, uint32 ChallengeID)
{
    if (ChallengeByMap* _lastResalt = LastForMember(guid))
    {
        auto itr = _lastResalt->find(ChallengeID);
        if (itr != _lastResalt->end())
            return itr->second;
    }

    return nullptr;
}

ChallengeData* ChallengeModeMgr::BestForMemberMap(ObjectGuid const& guid, uint32 ChallengeID)
{
    if (ChallengeByMap* _lastResalt = BestForMember(guid))
    {
        auto itr = _lastResalt->find(ChallengeID);
        if (itr != _lastResalt->end())
            return itr->second;
    }

    return nullptr;
}

void ChallengeModeMgr::GenerateCurrentWeekAffixes()
{
    static uint32 affixes[12][4] =
    {
        { Fortified,  Sanguine,   Necrotic,  Prideful },
        { Tyrannical, Bolstering, Bursting,  Prideful },
        { Fortified,  Volcanic,   Explosive, Prideful },
        { Tyrannical, Inspiring,  Quaking,   Prideful },
        { Fortified,  Raging,     Sanguine,  Prideful },
        { Tyrannical, Inspiring,  Spiteful,  Prideful },
        { Fortified,  Volcanic,   Bursting,  Prideful },
        { Tyrannical, Bolstering, Quaking,   Prideful },
        { Fortified,  Sanguine,   Bursting,  Prideful },
        { Tyrannical, Spiteful,   Necrotic,  Prideful },
        { Fortified,  Raging,     Explosive, Prideful },
        { Tyrannical, Grievous,   Inspiring, Prideful },
    };

    auto weekContainer = affixes[GetActiveAffixe()];

    sWorld->setWorldState(WS_CHALLENGE_AFFIXE1_RESET_TIME, weekContainer[0]);
    sWorld->setWorldState(WS_CHALLENGE_AFFIXE2_RESET_TIME, weekContainer[1]);
    sWorld->setWorldState(WS_CHALLENGE_AFFIXE3_RESET_TIME, weekContainer[2]);
    sWorld->setWorldState(WS_CHALLENGE_AFFIXE4_RESET_TIME, weekContainer[3]);

    static uint32 miniAffixes[12][4] =
    {
        { Fortified,  Volcanic,   Bursting,  Beguiling },
        { Tyrannical, Bolstering, Quaking,   Beguiling },
        { Fortified,  Sanguine,   Bursting,  Beguiling },
        { Tyrannical, Spiteful,   Necrotic,  Beguiling },
        { Fortified,  Raging,     Explosive, Beguiling },
        { Tyrannical, Grievous,   Inspiring, Beguiling },
        { Fortified,  Sanguine,   Necrotic,  Beguiling },
        { Tyrannical, Bolstering, Bursting,  Beguiling },
        { Fortified,  Volcanic,   Explosive, Beguiling },
        { Tyrannical, Inspiring,  Quaking,   Beguiling },
        { Fortified,  Raging,     Sanguine,  Beguiling },
        { Tyrannical, Inspiring,  Spiteful,  Beguiling },
    };

    weekContainer = miniAffixes[GetActiveAffixe()];
    sWorld->setWorldState(WS_CHALLENGE_MINI_AFFIXE1_RESET_TIME, weekContainer[0]);
    sWorld->setWorldState(WS_CHALLENGE_MINI_AFFIXE2_RESET_TIME, weekContainer[1]);
    sWorld->setWorldState(WS_CHALLENGE_MINI_AFFIXE3_RESET_TIME, weekContainer[2]);
    sWorld->setWorldState(WS_CHALLENGE_MINI_AFFIXE4_RESET_TIME, weekContainer[3]);
}

void ChallengeModeMgr::GenerateManualAffixes()
{
    sWorld->setWorldState(WS_CHALLENGE_AFFIXE1_RESET_TIME, sWorld->getIntConfig(CONFIG_CHALLENGE_MANUAL_AFFIX1));
    sWorld->setWorldState(WS_CHALLENGE_AFFIXE2_RESET_TIME, sWorld->getIntConfig(CONFIG_CHALLENGE_MANUAL_AFFIX2));
    sWorld->setWorldState(WS_CHALLENGE_AFFIXE3_RESET_TIME, sWorld->getIntConfig(CONFIG_CHALLENGE_MANUAL_AFFIX3));
    sWorld->setWorldState(WS_CHALLENGE_AFFIXE4_RESET_TIME, sWorld->getIntConfig(CONFIG_CHALLENGE_MANUAL_AFFIX4));
}

uint8 ChallengeModeMgr::GetActiveAffixe()
{
    if (sGameEventMgr->IsActiveEvent(109))
        return 0;
    if (sGameEventMgr->IsActiveEvent(110))
        return 1;
    if (sGameEventMgr->IsActiveEvent(111))
        return 2;
    if (sGameEventMgr->IsActiveEvent(112))
        return 3;
    if (sGameEventMgr->IsActiveEvent(113))
        return 4;
    if (sGameEventMgr->IsActiveEvent(114))
        return 5;
    if (sGameEventMgr->IsActiveEvent(115))
        return 6;
    if (sGameEventMgr->IsActiveEvent(116))
        return 7;
    if (sGameEventMgr->IsActiveEvent(117))
        return 8;
    if (sGameEventMgr->IsActiveEvent(118))
        return 9;
    if (sGameEventMgr->IsActiveEvent(119))
        return 10;
    if (sGameEventMgr->IsActiveEvent(120))
        return 11;

    return 0;
}

bool ChallengeModeMgr::HasOploteLoot(ObjectGuid const& guid)
{
    return Trinity::Containers::MapGetValuePtr(_oploteWeekLoot, guid);
}

OploteLoot* ChallengeModeMgr::GetOploteLoot(ObjectGuid const& guid)
{
    return Trinity::Containers::MapGetValuePtr(_oploteWeekLoot, guid);
}

uint32 ChallengeModeMgr::GetBestActualWeekChallengeLevel()
{
    uint32 bestChallengeLevel = 0;
    for (auto const& c : _challengeWeekList)
    {
        for (auto const& v : c.second)
        {
            if ((v->CompleteDate > sWorld->getWorldState(WS_CHALLENGE_KEY_RESET_TIME) || v->CompleteDate < sWorld->getWorldState(WS_CHALLENGE_LAST_RESET_TIME)))
                continue;

            if (bestChallengeLevel < v->ChallengeLevel)            
                bestChallengeLevel = v->ChallengeLevel;            
        }
    }

    return bestChallengeLevel;
}

void ChallengeModeMgr::SaveOploteLootToDB()
{
    CharacterDatabaseTransaction trans = CharacterDatabase.BeginTransaction();

    for (auto const& v : _oploteWeekLoot)
    {
        if (v.second.needSave)
        {
            auto stmt = CharacterDatabase.GetPreparedStatement(CHAR_INS_CHALLENGE_OPLOTE_LOOT);
            stmt->setUInt32(0, v.second.guid.GetCounter());
            std::ostringstream chestLists;
            for (uint32 chestList : v.second.chestListID)
                if (chestList)
                    chestLists << chestList << ' ';
            stmt->setString(1, chestLists.str());
            stmt->setUInt32(2, v.second.Date);
            stmt->setUInt32(3, v.second.ChallengeLevel);
            stmt->setUInt32(4, v.second.ChallengeID);
            trans->Append(stmt);
        }
    }
    CharacterDatabase.CommitTransaction(trans);
}

void ChallengeModeMgr::DeleteOploteLoot(ObjectGuid const& guid, CharacterDatabaseTransaction& trans)
{
    CharacterDatabasePreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_DEL_CHALLENGE_OPLOTE_LOOT_BY_GUID);
    stmt->setUInt32(0, guid.GetCounter());
    trans->Append(stmt);

    _oploteWeekLoot.erase(guid);
}

void ChallengeModeMgr::GenerateOploteLoot(bool manual)
{
    TC_LOG_DEBUG("misc", "GenerateOploteLoot manual %u _challengeWeekList %u", manual, _challengeWeekList.size());

    CharacterDatabase.Query("DELETE FROM challenge_oplote_loot WHERE date <= UNIX_TIMESTAMP()");
    _oploteWeekLoot.clear();

    for (auto const& c : _challengeWeekList)
    {
        for (auto const& v : c.second)
        {
            if (manual && (v->CompleteDate > sWorld->getWorldState(WS_CHALLENGE_LAST_RESET_TIME) + (7 * DAY) || v->CompleteDate < (sWorld->getWorldState(WS_CHALLENGE_LAST_RESET_TIME) - (7 * DAY))))
                continue;

            if (!manual && (v->CompleteDate > sWorld->getWorldState(WS_CHALLENGE_KEY_RESET_TIME) || v->CompleteDate < sWorld->getWorldState(WS_CHALLENGE_LAST_RESET_TIME)))
                continue;

            if (!v->ChestID)
                continue;

            auto itr = _oploteWeekLoot.find(c.first);
            if (itr != _oploteWeekLoot.end())
            {
                if (itr->second.ChallengeLevel < v->ChallengeLevel)
                {
                    itr->second.ChallengeLevel = v->ChallengeLevel;
                    itr->second.ChallengeID = v->ChallengeID;
                }                    

                itr->second.chestListID.insert(v->ChestID);
            }
            else
            {
                OploteLoot& lootOplote = _oploteWeekLoot[c.first];
                lootOplote.Date = sWorld->getNextChallengeKeyReset();
                lootOplote.ChallengeLevel = v->ChallengeLevel;
                lootOplote.ChallengeID = v->ChallengeID;
                lootOplote.needSave = true;
                lootOplote.guid = c.first;
                lootOplote.chestListID.insert(v->ChestID);
            }
        }
    }

    if (!manual)
    {
        _challengeWeekList.clear();
        SaveOploteLootToDB();
    }
}

bool ChallengeModeMgr::GetStartPosition(InstanceScript* instance, float& x, float& y, float& z, float& o, ObjectGuid OwnerGuid)
{
    if (!instance)
        return false;

    //ToDo Implement in DB
    uint32 WorldSafeLocID = 0;
    switch (instance->instance->GetId())
    {
        case CHALLENGE_MAP_ID_SHRINE_OF_THE_STORM:
            WorldSafeLocID = 6524; 
            break; 
        case CHALLENGE_MAP_ID_TOL_DAGOR: 
            WorldSafeLocID = 6383;
            break;
        case CHALLENGE_MAP_ID_FREE_HOLD: 
            WorldSafeLocID = 6335;
            break;
        case CHALLENGE_MAP_ID_WAYCREST_MANOR: 
            WorldSafeLocID = 6523;
            break;
        case CHALLENGE_MAP_ID_THE_MOTHERLODE: 
            WorldSafeLocID = 6359;
            break;
        case CHALLENGE_MAP_ID_SETHRALIS: 
            WorldSafeLocID = 6419;
            break;
        case CHALLENGE_MAP_ID_THE_UNDERROT: 
            WorldSafeLocID = 6378;
            break;
        case CHALLENGE_MAP_ID_ATALDAZAR: 
            WorldSafeLocID = 6123;
            break;
        case CHALLENGE_MAP_ID_SIEGE_OF_BORALUS: 
            if (Player* keyOwner = ObjectAccessor::FindPlayer(OwnerGuid))
            {
                if (keyOwner->GetTeamId() == TEAM_ALLIANCE)
                    WorldSafeLocID = 6397; 
                else
                    WorldSafeLocID = 6441; 
            }
            break;
        case CHALLENGE_MAP_ID_KING_REST: 
            WorldSafeLocID = 6560;
            break;
        default:
            break;
    }

    if (WorldSafeLocID == 0)
    {
        if (instance->HandleGetStartPosition(x, y, z, o))
            return true;
        return false;
    }

    if (auto entry = sObjectMgr->GetWorldSafeLoc(WorldSafeLocID))
    {
        x = entry->Loc.GetPositionX();
        y = entry->Loc.GetPositionY();
        z = entry->Loc.GetPositionZ();
        o = entry->Loc.GetOrientation(); // already converted in load
        return true;
    }

   // if (WorldSafeLocsEntry const* entry = sWorldSafeLocsStore.LookupEntry(WorldSafeLocID))
   // {
   //     x = entry->Loc.X;
   //     y = entry->Loc.Y;
   //     z = entry->Loc.Z;
   //     o = entry->Facing * M_PI / 180.0f;
   //     return true;
   // }
    return false;
}

bool ChallengeModeMgr::GetChallengeDoorOrChestPosition(uint32 mapID, float& x, float& y, float& z, float& o, float& rot0, float& rot1, float& rot2, float& rot3, bool door, bool horde)
{
    // PIGPIGPIG!!!
    switch (mapID)
    {
        case CHALLENGE_MAP_ID_SHRINE_OF_THE_STORM:
            x = door ? DoorPositions[CHALLENGE_SHRINE_OF_THE_STORM][0] : ChestPositions[CHALLENGE_SHRINE_OF_THE_STORM][0];
            y = door ? DoorPositions[CHALLENGE_SHRINE_OF_THE_STORM][1] : ChestPositions[CHALLENGE_SHRINE_OF_THE_STORM][1];
            z = door ? DoorPositions[CHALLENGE_SHRINE_OF_THE_STORM][2] : ChestPositions[CHALLENGE_SHRINE_OF_THE_STORM][2];
            o = door ? DoorPositions[CHALLENGE_SHRINE_OF_THE_STORM][3] : ChestPositions[CHALLENGE_SHRINE_OF_THE_STORM][3];
            rot0 = door ? DoorPositions[CHALLENGE_SHRINE_OF_THE_STORM][4] : ChestPositions[CHALLENGE_SHRINE_OF_THE_STORM][4];
            rot1 = door ? DoorPositions[CHALLENGE_SHRINE_OF_THE_STORM][5] : ChestPositions[CHALLENGE_SHRINE_OF_THE_STORM][5];
            rot2 = door ? DoorPositions[CHALLENGE_SHRINE_OF_THE_STORM][6] : ChestPositions[CHALLENGE_SHRINE_OF_THE_STORM][6];
            rot3 = door ? DoorPositions[CHALLENGE_SHRINE_OF_THE_STORM][7] : ChestPositions[CHALLENGE_SHRINE_OF_THE_STORM][7];
            return true;
        case CHALLENGE_MAP_ID_TOL_DAGOR:
            x = door ? DoorPositions[CHALLENGE_TOL_DAGOR][0] : ChestPositions[CHALLENGE_TOL_DAGOR][0];
            y = door ? DoorPositions[CHALLENGE_TOL_DAGOR][1] : ChestPositions[CHALLENGE_TOL_DAGOR][1];
            z = door ? DoorPositions[CHALLENGE_TOL_DAGOR][2] : ChestPositions[CHALLENGE_TOL_DAGOR][2];
            o = door ? DoorPositions[CHALLENGE_TOL_DAGOR][3] : ChestPositions[CHALLENGE_TOL_DAGOR][3];
            rot0 = door ? DoorPositions[CHALLENGE_TOL_DAGOR][4] : ChestPositions[CHALLENGE_TOL_DAGOR][4];
            rot1 = door ? DoorPositions[CHALLENGE_TOL_DAGOR][5] : ChestPositions[CHALLENGE_TOL_DAGOR][5];
            rot2 = door ? DoorPositions[CHALLENGE_TOL_DAGOR][6] : ChestPositions[CHALLENGE_TOL_DAGOR][6];
            rot3 = door ? DoorPositions[CHALLENGE_TOL_DAGOR][7] : ChestPositions[CHALLENGE_TOL_DAGOR][7];
            return true;
        case CHALLENGE_MAP_ID_FREE_HOLD:
            x = door ? DoorPositions[CHALLENGE_FREE_HOLD][0] : ChestPositions[CHALLENGE_FREE_HOLD][0];
            y = door ? DoorPositions[CHALLENGE_FREE_HOLD][1] : ChestPositions[CHALLENGE_FREE_HOLD][1];
            z = door ? DoorPositions[CHALLENGE_FREE_HOLD][2] : ChestPositions[CHALLENGE_FREE_HOLD][2];
            o = door ? DoorPositions[CHALLENGE_FREE_HOLD][3] : ChestPositions[CHALLENGE_FREE_HOLD][3];
            rot0 = door ? DoorPositions[CHALLENGE_FREE_HOLD][4] : ChestPositions[CHALLENGE_FREE_HOLD][4];
            rot1 = door ? DoorPositions[CHALLENGE_FREE_HOLD][5] : ChestPositions[CHALLENGE_FREE_HOLD][5];
            rot2 = door ? DoorPositions[CHALLENGE_FREE_HOLD][6] : ChestPositions[CHALLENGE_FREE_HOLD][6];
            rot3 = door ? DoorPositions[CHALLENGE_FREE_HOLD][7] : ChestPositions[CHALLENGE_FREE_HOLD][7];
            return true;
        case CHALLENGE_MAP_ID_WAYCREST_MANOR:
            x = door ? DoorPositions[CHALLENGE_WAYCREST_MANOR][0] : ChestPositions[CHALLENGE_WAYCREST_MANOR][0];
            y = door ? DoorPositions[CHALLENGE_WAYCREST_MANOR][1] : ChestPositions[CHALLENGE_WAYCREST_MANOR][1];
            z = door ? DoorPositions[CHALLENGE_WAYCREST_MANOR][2] : ChestPositions[CHALLENGE_WAYCREST_MANOR][2];
            o = door ? DoorPositions[CHALLENGE_WAYCREST_MANOR][3] : ChestPositions[CHALLENGE_WAYCREST_MANOR][3];
            rot0 = door ? DoorPositions[CHALLENGE_WAYCREST_MANOR][4] : ChestPositions[CHALLENGE_WAYCREST_MANOR][4];
            rot1 = door ? DoorPositions[CHALLENGE_WAYCREST_MANOR][5] : ChestPositions[CHALLENGE_WAYCREST_MANOR][5];
            rot2 = door ? DoorPositions[CHALLENGE_WAYCREST_MANOR][6] : ChestPositions[CHALLENGE_WAYCREST_MANOR][6];
            rot3 = door ? DoorPositions[CHALLENGE_WAYCREST_MANOR][7] : ChestPositions[CHALLENGE_WAYCREST_MANOR][7];
            return true;
        case CHALLENGE_MAP_ID_THE_MOTHERLODE:
            x = door ? DoorPositions[CHALLENGE_MOTHERLODE][0] : ChestPositions[CHALLENGE_MOTHERLODE][0];
            y = door ? DoorPositions[CHALLENGE_MOTHERLODE][1] : ChestPositions[CHALLENGE_MOTHERLODE][1];
            z = door ? DoorPositions[CHALLENGE_MOTHERLODE][2] : ChestPositions[CHALLENGE_MOTHERLODE][2];
            o = door ? DoorPositions[CHALLENGE_MOTHERLODE][3] : ChestPositions[CHALLENGE_MOTHERLODE][3];
            rot0 = door ? DoorPositions[CHALLENGE_MOTHERLODE][4] : ChestPositions[CHALLENGE_MOTHERLODE][4];
            rot1 = door ? DoorPositions[CHALLENGE_MOTHERLODE][5] : ChestPositions[CHALLENGE_MOTHERLODE][5];
            rot2 = door ? DoorPositions[CHALLENGE_MOTHERLODE][6] : ChestPositions[CHALLENGE_MOTHERLODE][6];
            rot3 = door ? DoorPositions[CHALLENGE_MOTHERLODE][7] : ChestPositions[CHALLENGE_MOTHERLODE][7];
            return true;
        case CHALLENGE_MAP_ID_SETHRALIS:
            x = door ? DoorPositions[CHALLENGE_TEMPLE_OF_SETHRALIS][0] : ChestPositions[CHALLENGE_TEMPLE_OF_SETHRALIS][0];
            y = door ? DoorPositions[CHALLENGE_TEMPLE_OF_SETHRALIS][1] : ChestPositions[CHALLENGE_TEMPLE_OF_SETHRALIS][1];
            z = door ? DoorPositions[CHALLENGE_TEMPLE_OF_SETHRALIS][2] : ChestPositions[CHALLENGE_TEMPLE_OF_SETHRALIS][2];
            o = door ? DoorPositions[CHALLENGE_TEMPLE_OF_SETHRALIS][3] : ChestPositions[CHALLENGE_TEMPLE_OF_SETHRALIS][3];
            rot0 = door ? DoorPositions[CHALLENGE_TEMPLE_OF_SETHRALIS][4] : ChestPositions[CHALLENGE_TEMPLE_OF_SETHRALIS][4];
            rot1 = door ? DoorPositions[CHALLENGE_TEMPLE_OF_SETHRALIS][5] : ChestPositions[CHALLENGE_TEMPLE_OF_SETHRALIS][5];
            rot2 = door ? DoorPositions[CHALLENGE_TEMPLE_OF_SETHRALIS][6] : ChestPositions[CHALLENGE_TEMPLE_OF_SETHRALIS][6];
            rot3 = door ? DoorPositions[CHALLENGE_TEMPLE_OF_SETHRALIS][7] : ChestPositions[CHALLENGE_TEMPLE_OF_SETHRALIS][7];
            return true;
        case CHALLENGE_MAP_ID_THE_UNDERROT:
            x = door ? DoorPositions[CHALLENGE_UNDERROT][0] : ChestPositions[CHALLENGE_UNDERROT][0];
            y = door ? DoorPositions[CHALLENGE_UNDERROT][1] : ChestPositions[CHALLENGE_UNDERROT][1];
            z = door ? DoorPositions[CHALLENGE_UNDERROT][2] : ChestPositions[CHALLENGE_UNDERROT][2];
            o = door ? DoorPositions[CHALLENGE_UNDERROT][3] : ChestPositions[CHALLENGE_UNDERROT][3];
            rot0 = door ? DoorPositions[CHALLENGE_UNDERROT][4] : ChestPositions[CHALLENGE_UNDERROT][4];
            rot1 = door ? DoorPositions[CHALLENGE_UNDERROT][5] : ChestPositions[CHALLENGE_UNDERROT][5];
            rot2 = door ? DoorPositions[CHALLENGE_UNDERROT][6] : ChestPositions[CHALLENGE_UNDERROT][6];
            rot3 = door ? DoorPositions[CHALLENGE_UNDERROT][7] : ChestPositions[CHALLENGE_UNDERROT][7];
            return true;
        case CHALLENGE_MAP_ID_ATALDAZAR:
            x = door ? DoorPositions[CHALLENGE_ATALDAZAR][0] : ChestPositions[CHALLENGE_ATALDAZAR][0];
            y = door ? DoorPositions[CHALLENGE_ATALDAZAR][1] : ChestPositions[CHALLENGE_ATALDAZAR][1];
            z = door ? DoorPositions[CHALLENGE_ATALDAZAR][2] : ChestPositions[CHALLENGE_ATALDAZAR][2];
            o = door ? DoorPositions[CHALLENGE_ATALDAZAR][3] : ChestPositions[CHALLENGE_ATALDAZAR][3];
            rot0 = door ? DoorPositions[CHALLENGE_ATALDAZAR][4] : ChestPositions[CHALLENGE_ATALDAZAR][4];
            rot1 = door ? DoorPositions[CHALLENGE_ATALDAZAR][5] : ChestPositions[CHALLENGE_ATALDAZAR][5];
            rot2 = door ? DoorPositions[CHALLENGE_ATALDAZAR][6] : ChestPositions[CHALLENGE_ATALDAZAR][6];
            rot3 = door ? DoorPositions[CHALLENGE_ATALDAZAR][7] : ChestPositions[CHALLENGE_ATALDAZAR][7];
            return true;
        case CHALLENGE_MAP_ID_SIEGE_OF_BORALUS:
            x = door ? DoorPositions[horde ? CHALLENGE_SIEGE_OF_BORALUS_HORDE : CHALLENGE_SIEGE_OF_BORALUS][0] : ChestPositions[horde ? CHALLENGE_SIEGE_OF_BORALUS_HORDE : CHALLENGE_SIEGE_OF_BORALUS][0];
            y = door ? DoorPositions[horde ? CHALLENGE_SIEGE_OF_BORALUS_HORDE : CHALLENGE_SIEGE_OF_BORALUS][1] : ChestPositions[horde ? CHALLENGE_SIEGE_OF_BORALUS_HORDE : CHALLENGE_SIEGE_OF_BORALUS][1];
            z = door ? DoorPositions[horde ? CHALLENGE_SIEGE_OF_BORALUS_HORDE : CHALLENGE_SIEGE_OF_BORALUS][2] : ChestPositions[horde ? CHALLENGE_SIEGE_OF_BORALUS_HORDE : CHALLENGE_SIEGE_OF_BORALUS][2];
            o = door ? DoorPositions[horde ? CHALLENGE_SIEGE_OF_BORALUS_HORDE : CHALLENGE_SIEGE_OF_BORALUS][3] : ChestPositions[horde ? CHALLENGE_SIEGE_OF_BORALUS_HORDE : CHALLENGE_SIEGE_OF_BORALUS][3];
            rot0 = door ? DoorPositions[horde ? CHALLENGE_SIEGE_OF_BORALUS_HORDE : CHALLENGE_SIEGE_OF_BORALUS][4] : ChestPositions[horde ? CHALLENGE_SIEGE_OF_BORALUS_HORDE : CHALLENGE_SIEGE_OF_BORALUS][4];
            rot1 = door ? DoorPositions[horde ? CHALLENGE_SIEGE_OF_BORALUS_HORDE : CHALLENGE_SIEGE_OF_BORALUS][5] : ChestPositions[horde ? CHALLENGE_SIEGE_OF_BORALUS_HORDE : CHALLENGE_SIEGE_OF_BORALUS][5];
            rot2 = door ? DoorPositions[horde ? CHALLENGE_SIEGE_OF_BORALUS_HORDE : CHALLENGE_SIEGE_OF_BORALUS][6] : ChestPositions[horde ? CHALLENGE_SIEGE_OF_BORALUS_HORDE : CHALLENGE_SIEGE_OF_BORALUS][6];
            rot3 = door ? DoorPositions[horde ? CHALLENGE_SIEGE_OF_BORALUS_HORDE : CHALLENGE_SIEGE_OF_BORALUS][7] : ChestPositions[horde ? CHALLENGE_SIEGE_OF_BORALUS_HORDE : CHALLENGE_SIEGE_OF_BORALUS][7];
            return true;
        case CHALLENGE_MAP_ID_KING_REST:
            x = door ? DoorPositions[CHALLENGE_KING_REST][0] : ChestPositions[CHALLENGE_KING_REST][0];
            y = door ? DoorPositions[CHALLENGE_KING_REST][1] : ChestPositions[CHALLENGE_KING_REST][1];
            z = door ? DoorPositions[CHALLENGE_KING_REST][2] : ChestPositions[CHALLENGE_KING_REST][2];
            o = door ? DoorPositions[CHALLENGE_KING_REST][3] : ChestPositions[CHALLENGE_KING_REST][3];
            rot0 = door ? DoorPositions[CHALLENGE_KING_REST][4] : ChestPositions[CHALLENGE_KING_REST][4];
            rot1 = door ? DoorPositions[CHALLENGE_KING_REST][5] : ChestPositions[CHALLENGE_KING_REST][5];
            rot2 = door ? DoorPositions[CHALLENGE_KING_REST][6] : ChestPositions[CHALLENGE_KING_REST][6];
            rot3 = door ? DoorPositions[CHALLENGE_KING_REST][7] : ChestPositions[CHALLENGE_KING_REST][7];
            return true;
        default:
            break;
    }

    return false;
}

uint32 ChallengeModeMgr::GetDoorOrChestByMap(uint32 mapID, bool door, bool horde)
{
    switch (mapID)
    {
        case CHALLENGE_MAP_ID_WAYCREST_MANOR:
            return door ? MYTHIC_DOOR_2 : MYTHIC_CHEST_WAYCREST_MANOR;
        case CHALLENGE_MAP_ID_SIEGE_OF_BORALUS:
            return door ? (horde ? MYTHIC_DOOR_3 : MYTHIC_DOOR_4) : MYTHIC_CHEST_SIEGE_OF_BORALUS;
        case CHALLENGE_MAP_ID_TOL_DAGOR:
            return door ? MYTHIC_DOOR_4 : MYTHIC_CHEST_TOL_DAGOR;
        case CHALLENGE_MAP_ID_FREE_HOLD:
            return door ? MYTHIC_DOOR_4 : MYTHIC_CHEST_FREE_HOLD;
        case CHALLENGE_MAP_ID_THE_UNDERROT:
            return door ? MYTHIC_DOOR_4 : MYTHIC_CHEST_UNDERROT;
        case CHALLENGE_MAP_ID_THE_MOTHERLODE:
            return door ? MYTHIC_DOOR_5 : MYTHIC_CHEST_MOTHERLODE;
        case CHALLENGE_MAP_ID_SETHRALIS:
            return door ? MYTHIC_DOOR_1 : MYTHIC_CHEST_SETHRALISS;
        case CHALLENGE_MAP_ID_ATALDAZAR:
            return door ? MYTHIC_DOOR_7 : MYTHIC_CHEST_ATALDAZAR;
        case CHALLENGE_MAP_ID_KING_REST:
            return door ? MYTHIC_DOOR_6 : MYTHIC_CHEST_KING_REST;
        case CHALLENGE_MAP_ID_SHRINE_OF_THE_STORM:
            return door ? MYTHIC_DOOR_3 : MYTHIC_CHEST_SHRINE_OF_THE_STORM;
        default:
            break;
    }

    return 0;
}

uint32 ChallengeModeMgr::GetChallengeChestByBonusLootID(uint32 bonusLootID)
{
    switch (bonusLootID)
    {
        case CHALLENGE_BONUS_ID_WAYCREST_MANOR:
            return MYTHIC_CHEST_WAYCREST_MANOR;
        case CHALLENGE_BONUS_ID_SIEGE_OF_BORALUS:
            return MYTHIC_CHEST_SIEGE_OF_BORALUS;
        case CHALLENGE_BONUS_ID_TOL_DAGOR:
            return MYTHIC_CHEST_TOL_DAGOR;
        case CHALLENGE_BONUS_ID_FREE_HOLD:
            return MYTHIC_CHEST_FREE_HOLD;
        case CHALLENGE_BONUS_ID_THE_UNDERROT:
            return MYTHIC_CHEST_UNDERROT;
        case CHALLENGE_BONUS_ID_THE_MOTHERLODE:
            return MYTHIC_CHEST_MOTHERLODE;
        case CHALLENGE_BONUS_ID_SETHRALIS:
            return MYTHIC_CHEST_SETHRALISS;
        case CHALLENGE_BONUS_ID_ATALDAZAR:
            return MYTHIC_CHEST_ATALDAZAR;
        case CHALLENGE_BONUS_ID_KING_REST:
            return MYTHIC_CHEST_KING_REST;
        case CHALLENGE_BONUS_ID_SHRINE_OF_THE_STORM:
            return MYTHIC_CHEST_SHRINE_OF_THE_STORM;
        default:
            break;
    }

    return 0;
}

uint8 ChallengeModeMgr::GetLootTreeMod(int32& levelBonus, uint32& challengeRewardLevel, Challenge* challenge)
{
    int8 seasonID = sWorld->getIntConfig(CONFIG_CHALLENGE_SEASON_ID);
    if (seasonID < 0)
        return uint8(ItemContext::MythicPlus_End_of_Run);

    if (challenge)
        challengeRewardLevel = std::min(challenge->GetChallengeLevel(), sWorld->getIntConfig(CONFIG_CHALLENGE_LEVEL_MAX));
    else
        challengeRewardLevel = std::min(challengeRewardLevel, sWorld->getIntConfig(CONFIG_CHALLENGE_LEVEL_MAX));

    levelBonus = sDB2Manager.GetChallengeLevelReward(challengeRewardLevel, seasonID, challenge == nullptr);

    return uint8(ItemContext::MythicPlus_End_of_Run);
}

float ChallengeModeMgr::GetChanceItem(uint8 mode, uint32 challengeLevel)
{
    float base_chance = 200.0f;
    float add_chance = 0.0f;

    if (challengeLevel > MYTHIC_LEVEL_10)
        add_chance += (challengeLevel - 10) * 40.0f; 

    switch (mode)
    {
        case CHALLENGE_TIMER_LEVEL_3: // 3 chests + 3 levels
        case CHALLENGE_TIMER_LEVEL_2: // 2 chests + 2 levels
        case CHALLENGE_TIMER_LEVEL_1: // 1 chest + 1 level
            base_chance += 100.0f; // 300% is 3 items
            break;
        case CHALLENGE_NOT_IN_TIMER:  // 0 chest
            base_chance += 0.0f; // 200% is 2 items
            break;
        default:
            break;
    }

    base_chance += add_chance;

    return base_chance;
}

std::vector<uint32> ChallengeModeMgr::CalculateChallengeItemBonus(int32 levelBonus)
{
    std::vector<uint32> bonusListIDs;

    int8 seasonID = sWorld->getIntConfig(CONFIG_CHALLENGE_SEASON_ID);
    if (seasonID < 0)
        return bonusListIDs;

    int32 levelBase = sDB2Manager.GetChallengeLevelReward(MYTHIC_LEVEL_2, seasonID, false);// The level base of the season is level 2 in EndRunChest
    if (levelBonus > levelBase)
        if (uint32 bonusListID = sDB2Manager.GetItemBonusListForItemLevelDelta(levelBonus - levelBase))
            bonusListIDs.push_back(bonusListID);

    return bonusListIDs;
}

void ChallengeModeMgr::ReplaceChallengeLevel(std::set<uint32>& bonusListIDs, int32 challengeLevel)
{
    if (challengeLevel <= MYTHIC_LEVEL_2)// Don't replace for level 2 or less
        return;

    auto bonusItr = bonusListIDs.find(BASE_BONUSID_MYTHIC_LEVEL);
    if (bonusItr == bonusListIDs.end())
        return;

    uint32 replaceTo = LEVEL3_BONUSID_MYTHIC_LEVEL + (challengeLevel - MYTHIC_LEVEL_3);

    bonusListIDs.erase(BASE_BONUSID_MYTHIC_LEVEL);
    bonusListIDs.insert(replaceTo);
}

void ChallengeModeMgr::GenerateAchievementByMythicLevel(Player* member, uint32 challengeLevel)
{
    if (!member)
        return;

    if(challengeLevel >= MYTHIC_LEVEL_2 && !member->HasAchieved(ACHIEVEMENT_KEYMASTER_INITIATE))
        member->CompletedAchievement(ACHIEVEMENT_KEYMASTER_INITIATE);

    if (challengeLevel >= MYTHIC_LEVEL_5 && !member->HasAchieved(ACHIEVEMENT_KEYMASTER_CHALLENGER))
        member->CompletedAchievement(ACHIEVEMENT_KEYMASTER_CHALLENGER);

    if (challengeLevel >= MYTHIC_LEVEL_10)
    {
        if (!member->HasAchieved(ACHIEVEMENT_KEYMASTER_CONQUEROR))
            member->CompletedAchievement(ACHIEVEMENT_KEYMASTER_CONQUEROR);

        if (!member->HasAchieved(ACHIEVEMENT_BATTLE_FOR_AZEROTH_KEYSTONE_CONQUEROR_SEASON_ONE))
        {
            bool addAchievement = true;
            for (auto challengeID : sDB2Manager.GetChallengeMaps())
            {
                if (ChallengeData* _bestData = BestForMemberMap(member->GetGUID(), challengeID))
                {
                    if (_bestData->ChallengeLevel < MYTHIC_LEVEL_10)
                    {
                        addAchievement = false;
                        break;
                    }
                }
                else
                {
                    addAchievement = false;
                    break;
                }
            }

            if(addAchievement)
                member->CompletedAchievement(ACHIEVEMENT_BATTLE_FOR_AZEROTH_KEYSTONE_CONQUEROR_SEASON_ONE);
        }
    }

    if (challengeLevel >= MYTHIC_LEVEL_15)
    {
        if(!member->HasAchieved(ACHIEVEMENT_KEYMASTER_MASTER))
            member->CompletedAchievement(ACHIEVEMENT_KEYMASTER_MASTER);

        if(!member->HasAchieved(ACHIEVEMENT_REALM_FIRST_BATTLE_FOR_AZEROTH_KEYSTONE_MASTER))
            member->CompletedAchievement(ACHIEVEMENT_REALM_FIRST_BATTLE_FOR_AZEROTH_KEYSTONE_MASTER); //This gonna be checked realm size

        if (!member->HasAchieved(ACHIEVEMENT_BATTLE_FOR_AZEROTH_KEYSTONE_MASTER_SEASON_ONE))
        {
            bool addAchievement = true;
            for (auto challengeID : sDB2Manager.GetChallengeMaps())
            {
                if (ChallengeData* _bestData = BestForMemberMap(member->GetGUID(), challengeID))
                {
                    if (_bestData->ChallengeLevel < MYTHIC_LEVEL_15)
                    {
                        addAchievement = false;
                        break;
                    }
                }
                else
                {
                    addAchievement = false;
                    break;
                }
            }

            if (addAchievement)
                member->CompletedAchievement(ACHIEVEMENT_BATTLE_FOR_AZEROTH_KEYSTONE_MASTER_SEASON_ONE);
        }
    }
}

bool ChallengeModeMgr::IsChest(uint32 goEntry)
{
    switch (goEntry)
    {        
        case MYTHIC_CHEST_ATALDAZAR:
        case MYTHIC_CHEST_FREE_HOLD:
        case MYTHIC_CHEST_SIEGE_OF_BORALUS: 
        case MYTHIC_CHEST_TOL_DAGOR: 
        case MYTHIC_CHEST_MOTHERLODE: 
        case MYTHIC_CHEST_WAYCREST_MANOR: 
        case MYTHIC_CHEST_UNDERROT: 
        case MYTHIC_CHEST_SETHRALISS: 
        case MYTHIC_CHEST_SHRINE_OF_THE_STORM: 
        case MYTHIC_CHEST_KING_REST:
        case MYTHIC_CHEST_CUSTOM:
            return true;
        default:
            break;
    }

    return false;
}

bool ChallengeModeMgr::IsDoor(uint32 goEntry)
{
    switch (goEntry)
    {          
        case MYTHIC_DOOR_0:    
        case MYTHIC_DOOR_1:  
        case MYTHIC_DOOR_2:  
        case MYTHIC_DOOR_3:  
        case MYTHIC_DOOR_4:  
        case MYTHIC_DOOR_5:  
        case MYTHIC_DOOR_6:  
        case MYTHIC_DOOR_7:  
        case MYTHIC_DOOR_8:
        case MYTHIC_DOOR_9:
            return true;
        default:
            break;
    }

    return false;
}

bool ChallengeModeMgr::IsAuraAffix(uint32 auraId)
{
    switch (auraId)
    {
        case SPELL_CHALLENGER_SIMBIOTE_OF_GHUUN:
        case SPELL_CHALLENGER_REGENERATIVE_BLOOD_AURA:
        case SPELL_CHALLENGER_MIGHT:
            return true;
        default:
            break;
    }

    return false;
}

bool ChallengeModeMgr::IsTeemingAffixInRotation()
{
    if (sWorld->getWorldState(WS_CHALLENGE_AFFIXE1_RESET_TIME) == Affixes::Teeming
        || sWorld->getWorldState(WS_CHALLENGE_AFFIXE2_RESET_TIME) == Affixes::Teeming
        || sWorld->getWorldState(WS_CHALLENGE_AFFIXE3_RESET_TIME) == Affixes::Teeming
        || sWorld->getWorldState(WS_CHALLENGE_AFFIXE4_RESET_TIME) == Affixes::Teeming)
        return true;

    return false;
}

