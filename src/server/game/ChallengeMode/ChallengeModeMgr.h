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

#include "GameEventMgr.h"
#include "ChallengeMode.h"

#ifndef _CHALLENGEMODEMGR_H
#define _CHALLENGEMODEMGR_H

struct ChallengeMember
{
    ObjectGuid playerGuid;
    ObjectGuid guildGuid;
    uint16 specId;
    uint32 CompleteDate;            // time when recorde done
    uint32 Ilevel;
    uint32 ChallengeLevel;          // 2-15 but blizzard store it as uint32? rly?
    uint32 ChestID;
    uint16 Race;
    // TODO: add bnetaccountid,covenantid,soulbinid

    bool operator <(const ChallengeMember& i) const;
    bool operator ==(const ChallengeMember& i) const;
};

typedef std::set<ChallengeMember> ChallengeMemberList;

struct ChallengeData
{
    std::array<int32, 4> Affixes;  // key modifiers
    ObjectGuid::LowType GuildID;    // is it guild group
    ObjectGuid::LowType ID;         // challenge id
    uint32 RecordTime;              // time taken for complete challenge
    uint32 CompleteDate;            // time when recorde done
    uint32 StartDate;               // time when recorde start
    uint32 ChallengeLevel;          // 2-15 but blizzard store it as uint32? rly?
    uint32 ChestID;
    uint16 MapID;
    uint16 ChallengeID;
    uint8  TimerLevel;              // like 0 - not in time; 1-2-3 'timer deal' by db2 data 1-2-3 chests
    uint8 Expansion;

    ChallengeMemberList members;
};

struct OploteLoot
{
    ObjectGuid guid;
    uint32 Date;
    uint32 ChallengeLevel;
    uint32 ChallengeID;
    std::set<uint32> chestListID;
    bool needSave = true;
};

typedef std::unordered_map<uint16 /*ChallengeID*/, ChallengeData*> ChallengeByMap;
typedef std::unordered_map<ObjectGuid::LowType /*ID*/, ChallengeData*> ChallengeMap;
typedef std::unordered_map<ObjectGuid /*MemberGUID*/, ChallengeByMap> ChallengesOfMember;
typedef std::unordered_map<ObjectGuid::LowType /*guild*/, ChallengeByMap> GuildBestRecord;
typedef std::unordered_map<ObjectGuid /*MemberGUID*/, std::set<ChallengeData*>> ChallengeWeekListMap;
typedef std::unordered_map<ObjectGuid /*MemberGUID*/, OploteLoot> OploteLootMap;

static const std::list<uint32> ChallengeChestList =
{
    MYTHIC_CHEST_ATALDAZAR,
    MYTHIC_CHEST_FREE_HOLD,
    MYTHIC_CHEST_SIEGE_OF_BORALUS,
    MYTHIC_CHEST_TOL_DAGOR,
    MYTHIC_CHEST_MOTHERLODE,
    MYTHIC_CHEST_WAYCREST_MANOR,
    MYTHIC_CHEST_UNDERROT,
    MYTHIC_CHEST_SETHRALISS,
    MYTHIC_CHEST_SHRINE_OF_THE_STORM,
    MYTHIC_CHEST_KING_REST
};

class Challenge;
class InstanceScript;

struct MapChallengeModeEntry;

class TC_GAME_API ChallengeModeMgr
{
public:
    static ChallengeModeMgr* instance();

    void LoadFromDB();
    void SaveChallengeToDB(ChallengeData const* challengeData);

    void CheckBestMapId(ChallengeData* challengeData);
    void CheckBestGuildMapId(ChallengeData* challengeData);
    bool CheckBestMemberMapId(ObjectGuid const& guid, ChallengeData* challengeData);

    ChallengeData* BestServerChallenge(uint16 ChallengeID);
    ChallengeData* BestGuildChallenge(ObjectGuid::LowType const& guildId, uint16 ChallengeID);
    void SetChallengeMapData(ObjectGuid::LowType const& ID, ChallengeData* data);
    ChallengeByMap* BestForMember(ObjectGuid const& guid);
    ChallengeByMap* LastForMember(ObjectGuid const& guid);
    ChallengeData* LastForMemberMap(ObjectGuid const& guid, uint32 ChallengeID);
    ChallengeData* BestForMemberMap(ObjectGuid const& guid, uint32 ChallengeID);
    bool HasOploteLoot(ObjectGuid const& guid);
    OploteLoot* GetOploteLoot(ObjectGuid const& guid);
    uint32 GetBestActualWeekChallengeLevel();
    void SaveOploteLootToDB();
    void DeleteOploteLoot(ObjectGuid const& guid, CharacterDatabaseTransaction& trans);
    void GenerateOploteLoot(bool manual = false);
    static bool GetStartPosition(InstanceScript* instance, float& x, float& y, float& z, float& o, ObjectGuid OwnerGuid);
    bool GetChallengeDoorOrChestPosition(uint32 mapID, float& x, float& y, float& z, float& o, float& rot0, float& rot1, float& rot2, float& rot3, bool door, bool horde);
    uint32 GetDoorOrChestByMap(uint32 mapID, bool door, bool horde);
    uint32 GetChallengeChestByBonusLootID(uint32 bonusLootID);
    void GenerateAchievementByMythicLevel(Player* member, uint32 challengeLevel);

    void GenerateCurrentWeekAffixes();
    void GenerateManualAffixes();
    uint8 GetActiveAffixe();

    static uint8  GetLootTreeMod(int32& levelBonus, uint32& challengeLevel, Challenge* challenge = nullptr);
    static float GetChanceItem(uint8 mode, uint32 challengeLevel);    
    static bool IsChest(uint32 goEntry);
    static bool IsDoor(uint32 goEntry);
    static bool IsAuraAffix(uint32 auraId);
    static bool IsTeemingAffixInRotation();
    std::vector<uint32> CalculateChallengeItemBonus(int32 levelBonus);
    void ReplaceChallengeLevel(std::set<uint32>& bonusListIDs, int32 challengeLevel);

protected:
    ChallengeMap _challengeMap;
    ChallengesOfMember _lastForMember;
    ChallengesOfMember _challengesOfMember;
    ChallengeByMap _bestForMap;
    GuildBestRecord m_GuildBest;
    ChallengeWeekListMap _challengeWeekList;
    OploteLootMap _oploteWeekLoot;
};

#define sChallengeModeMgr ChallengeModeMgr::instance()

#endif
