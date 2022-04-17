/*
 * Copyright (C) 2008-2020 TrinityCore <http://www.trinitycore.org/>
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

#ifndef TRINITY_CHALLENGE_H
#define TRINITY_CHALLENGE_H

#include "Common.h"
#include "Scenario.h"
#include "InstanceScript.h"
#include "FunctionProcessor.h"

struct MapChallengeModeEntry;
class Scenario;

enum Affixes : uint32
{
    OVERFLOWING     = 1,
    SKITTISH        = 2,
    VOLCANIC        = 3,
    NECROTIC        = 4,
    TEEMING         = 5,
    RAGING          = 6,
    BOLSTERING      = 7,
    SANGUINE        = 8,
    TYRANNICAL      = 9,
    FORTIFIED       = 10,
    BURSTING        = 11,
    GRIEVOUS        = 12,
    EXPLOSIVES      = 13,
    QUAKING         = 14,
    RELENTLESS      = 15,
    INFESTED        = 16,

    MAX_AFFIXES
};

enum ChallengeSpells : uint32
{
    SPELL_CHALLENGER_MIGHT                     = 206150,
    SPELL_CHALLENGER_BURDEN                    = 206151,
    SPELL_CHALLENGER_BOLSTERING                = 209859,
    SPELL_CHALLENGER_NECROTIC                  = 209858,
    SPELL_CHALLENGER_OVERFLOWING               = 221772,
    SPELL_CHALLENGER_SANGUINE                  = 226489,
    SPELL_CHALLENGER_SANGUINE_HEAL             = 226510,
    SPELL_CHALLENGER_SANGUINE_DMG              = 226512,
    SPELL_CHALLENGER_RAGING                    = 228318,
    SPELL_CHALLENGER_SUMMON_VOLCANIC_PLUME     = 209861,
    SPELL_CHALLENGER_VOLCANIC_PLUME            = 209862,
    SPELL_CHALLENGER_BURSTING                  = 240443,
    SPELL_CHALLENGER_BURSTING_DAMAGE           = 243237,
    SPELL_CHALLENGER_QUAKE                     = 240447,
    SPELL_CHALLENGER_GRIEVOUS_WOUND            = 240559,
    SPELL_CHALLENGER_SIMBIOTE_OF_GHUUN         = 277242,
    SPELL_CHALLENGER_REGENERATIVE_BLOOD_AURA   = 277564,
    SPELL_CHALLENGER_INFEST                    = 277567,

    //Explosive
    SPELL_CHALLENGER_EXPLOSIVES_SUMMON         = 249439, //Short dist
    SPELL_CHALLENGER_EXPLOSIVES_VISUAL         = 240445,
    SPELL_CHALLENGER_EXPLOSIVES_DMG            = 240446,

    //Others
    SPELL_CHALLENGE_BONUS_LOOT                 = 259072
};

enum ChallengeNpcs : uint32
{
    NPC_VOLCANIC_PLUME      = 105877,
    NPC_EXPLOSIVES          = 125656,
    NPC_SPAWN_OF_GHUUN      = 141851,
};

enum MiscChallengeData : uint32
{
    ITEM_MYTHIC_KEYSTONE        = 158923,
    CHALLENGE_DELAY_TIMER       = 10,
    FIRST_WOD_CHALLENGE_ID      = 161,   //Skyreach is the first WoD Dungeon
    FIRST_LEGION_CHALLENGE_ID   = 197,   //Eye of Azshara is the first Legion Dungeon
    FIRST_BFA_CHALLENGE_ID      = 244,   //Atal'dazar is the first bfa Dungeon
    BASE_BONUSID_MYTHIC_LEVEL   = 4780,  //Base Bonus ID for replace Mythic Level in Item Description
    LEVEL3_BONUSID_MYTHIC_LEVEL = 5019,  //First Bonus ID for replace Mythic Level in Item Description
};

enum ChallengeAchievement : uint32
{
    ACHIEVEMENT_KEYMASTER_INITIATE                               = 11183,
    ACHIEVEMENT_KEYMASTER_CHALLENGER                             = 11184,
    ACHIEVEMENT_KEYMASTER_CONQUEROR                              = 11185,
    ACHIEVEMENT_KEYMASTER_MASTER                                 = 11162,
    ACHIEVEMENT_REALM_FIRST_BATTLE_FOR_AZEROTH_KEYSTONE_MASTER   = 13078,
    ACHIEVEMENT_BATTLE_FOR_AZEROTH_KEYSTONE_CONQUEROR_SEASON_ONE = 13079,
    ACHIEVEMENT_BATTLE_FOR_AZEROTH_KEYSTONE_MASTER_SEASON_ONE    = 13080,
};

enum MythicLevelChallenge : uint32
{
    MYTHIC_LEVEL_0 = 0,
    MYTHIC_LEVEL_1,
    MYTHIC_LEVEL_2,
    MYTHIC_LEVEL_3,
    MYTHIC_LEVEL_4,
    MYTHIC_LEVEL_5,
    MYTHIC_LEVEL_6,
    MYTHIC_LEVEL_7,
    MYTHIC_LEVEL_8,
    MYTHIC_LEVEL_9,
    MYTHIC_LEVEL_10,
    MYTHIC_LEVEL_11,
    MYTHIC_LEVEL_12,
    MYTHIC_LEVEL_13,
    MYTHIC_LEVEL_14,
    MYTHIC_LEVEL_15
};

enum MythicDoor : uint32
{
    MYTHIC_DOOR_0 = 211988,  //Challenge Mode - Start Door(Line 1.0)
    MYTHIC_DOOR_1 = 211989,  //Challenge Mode - Start Door(Line 2.0)
    MYTHIC_DOOR_2 = 211991,  //Challenge Mode - Start Door(Line 3.0)
    MYTHIC_DOOR_3 = 211992,  //Challenge Mode - Start Door(Line 1.5)
    MYTHIC_DOOR_4 = 212387,  //Challenge Mode - Start Door(Dome 2.0)
    MYTHIC_DOOR_5 = 212972,  //Challenge Mode - Start Door(Line 3.5)
    MYTHIC_DOOR_6 = 239408,  //Challenge Mode - Start Door(Line 2.5)
    MYTHIC_DOOR_7 = 282393,  //Challenge Mode - Start Door(Line 4.5)
    MYTHIC_DOOR_8 = 239323   //Challenge Mode - Start Door(Line 2.35)
};

enum MythicChest : uint32
{
    MYTHIC_CHEST_ATALDAZAR           = 282737, 
    MYTHIC_CHEST_FREE_HOLD           = 282735, 
    MYTHIC_CHEST_SIEGE_OF_BORALUS    = 288644, 
    MYTHIC_CHEST_TOL_DAGOR           = 282736, 
    MYTHIC_CHEST_MOTHERLODE          = 290544, 
    MYTHIC_CHEST_WAYCREST_MANOR      = 290621, 
    MYTHIC_CHEST_UNDERROT            = 290759, 
    MYTHIC_CHEST_SETHRALISS          = 290758, 
    MYTHIC_CHEST_SHRINE_OF_THE_STORM = 290761, 
    MYTHIC_CHEST_KING_REST           = 288642 
};

enum ChallengeMapID : uint32
{
    CHALLENGE_MAP_ID_THE_UNDERROT        = 1841,
    CHALLENGE_MAP_ID_WAYCREST_MANOR      = 1862,
    CHALLENGE_MAP_ID_TOL_DAGOR           = 1771,
    CHALLENGE_MAP_ID_THE_MOTHERLODE      = 1594,
    CHALLENGE_MAP_ID_SETHRALIS           = 1877,
    CHALLENGE_MAP_ID_SIEGE_OF_BORALUS    = 1822,
    CHALLENGE_MAP_ID_SHRINE_OF_THE_STORM = 1864,
    CHALLENGE_MAP_ID_KING_REST           = 1762,
    CHALLENGE_MAP_ID_FREE_HOLD           = 1754,
    CHALLENGE_MAP_ID_ATALDAZAR           = 1763
};

enum ChallengeNode : uint32
{
    CHALLENGE_ATALDAZAR = 0,
    CHALLENGE_FREE_HOLD,
    CHALLENGE_KING_REST,
    CHALLENGE_TOL_DAGOR,
    CHALLENGE_UNDERROT,
    CHALLENGE_MOTHERLODE,
    CHALLENGE_TEMPLE_OF_SETHRALIS,
    CHALLENGE_SIEGE_OF_BORALUS,
    CHALLENGE_WAYCREST_MANOR,
    CHALLENGE_SHRINE_OF_THE_STORM,
    CHALLENGE_SIEGE_OF_BORALUS_HORDE,
    CHALLENGE_MAX
};

enum ChallengeBonusID : uint32
{
    CHALLENGE_BONUS_ID_THE_UNDERROT        = 157,
    CHALLENGE_BONUS_ID_WAYCREST_MANOR      = 158,
    CHALLENGE_BONUS_ID_TOL_DAGOR           = 159,
    CHALLENGE_BONUS_ID_THE_MOTHERLODE      = 160,
    CHALLENGE_BONUS_ID_SETHRALIS           = 161,
    CHALLENGE_BONUS_ID_SIEGE_OF_BORALUS    = 162,
    CHALLENGE_BONUS_ID_SHRINE_OF_THE_STORM = 163,
    CHALLENGE_BONUS_ID_KING_REST           = 164,
    CHALLENGE_BONUS_ID_FREE_HOLD           = 165,
    CHALLENGE_BONUS_ID_ATALDAZAR           = 166
};

// x, y, z, o, rot0, rot1, rot2, rot3
const float DoorPositions[CHALLENGE_MAX][8] =
{
    {-848.191f,	2095.480f,	726.819f,	1.57080f, 0.0f, 0.0f, 0.7018130f, -0.712361f},	//Ataldazar
    {-1590.96f,	-998.204f,	73.3076f,	2.35733f, 0.0f, 0.0f, 0.0f      , 0.0f      },  //Free Hold
    {-945.387f,	2578.390f,	833.052f,	1.55544f, 0.0f, 0.0f, -0.716606f, -0.697478f},  //King Rest
    { 87.3755f,	-2920.97f,	1.35102f,	1.55509f, 0.0f, 0.0f, 0.0f      , 0.0f      },  //Tol Dagor
    { 636.715f,	1253.030f,	98.5464f,	0.0f	, 0.0f, 0.0f, 0.0f      , 0.0f      },  //Underrot
    { 692.795f,	-3659.28f,	7.69999f,	6.06680f, 0.0f, 0.0f, 0.0f      , 0.0f      },	//Motherlode
    { 3216.71f,	3151.360f,	121.605f,	0.0f    , 0.0f, 0.0f, 0.0f      , 0.0f      },  //Temple of Sethralis
    { 1085.82f, -619.929f,	17.6889f,	0.92056f, 0.0f, 0.0f, 0.0f      , 0.0f      },  //Siege of Boralus
    { -601.52f, -259.619f,	236.029f,	0.00416f, 0.0f, 0.0f, 0.0f      , 0.0f      },  //Waycrest Manor
    { 4167.48f, -1261.76f,	181.326f,	4.73342f, 0.0f, 0.0f, -0.722584f, 0.691284f },  //Shrine of the Storm
    { 1099.45f, -615.732f,	1.54370f,	0.18752f, 0.0f, 0.0f, -0.093627f, -0.995607f},  //Siege of Boralus Horde
};

const float ChestPositions[CHALLENGE_MAX][8] =
{
    {-847.798f,	2545.490f,	732.132f,	4.69589f, 0.0f, 0.0f, -0.705056f, -0.709151f},	//Ataldazar
    {-1550.03f, -573.654f,	68.9249f,	3.81472f, 0.0f, 0.0f, -0.861598f, 0.5075920f},  //Free Hold
    {-945.159f,	3217.770f,	779.108f,	4.77271f, 0.0f, 0.0f, -0.700267f, -0.713881f},  //King Rest
    { 122.795f,	-2660.86f,	74.4368f,	5.64580f, 0.0f, 0.0f, -0.304219f, 0.9526020f},  //Tol Dagor
    { 1207.40f,	1433.150f,	-181.70f,	1.78050f, 0.0f, 0.0f, -0.606807f, 0.7948490f},  //Underrot
    { 1077.23f,	-3906.49f,	79.6890f,	5.86409f, 0.0f, 0.0f, -0.975267f, -0.221029f},	//Motherlode
    { 4185.89f,	3688.640f,	-43.230f,	3.63425f, 0.0f, 0.0f, -0.966178f, 0.2578780f},  //Temple of Sethralis
    { 234.498f, -177.783f,	0.83633f,	3.34207f, 0.0f, 0.0f, -0.999715f, 0.0238778f},  //Siege of Boralus
    { -430.90f,	-343.831f,	152.478f,	3.14726f, 0.0f, 0.0f, -0.064774f, -0.997900f},  //Waycrest Manor
    { 3640.62f, -1733.39f,	85.6534f,	2.61714f, 0.0f, 0.0f, -0.700267f, -0.713881f},  //Shrine of the Storm
    { 234.498f, -177.783f,	0.83633f,	3.34207f, 0.0f, 0.0f, -0.999715f, 0.0238778f},  //Siege of Boralus Horde
};

class TC_GAME_API Challenge : public InstanceScript
{
public:
    Challenge(InstanceMap* map, Player* player, uint32 instanceID, Scenario* scenario);
    ~Challenge();

    void OnPlayerEnterForScript(Player* player) override;
    void OnPlayerLeaveForScript(Player* player) override;
    void OnPlayerDiesForScript(Player* player) override;
    void OnCreatureCreateForScript(Creature* creature) override;
    void OnCreatureRemoveForScript(Creature* creature) override;
    void OnCreatureUpdateDifficulty(Creature* creature) override;
    void EnterCombatForScript(Creature* creature, Unit* enemy) override;
    void CreatureDiesForScript(Creature* creature, Unit* killer) override;
    void OnGameObjectCreateForScript(GameObject* /*go*/) override {}
    void OnGameObjectRemoveForScript(GameObject* /*go*/) override {}
    void OnUnitCharmed(Unit* unit, Unit* charmer) override;
    void OnUnitRemoveCharmed(Unit* unit, Unit* charmer) override;

    void Update(uint32 diff) override;

    bool CanStart();
    void Start();
    void Complete();

    void BroadcastPacket(WorldPacket const* data) const override;

    void HitTimer();

    uint32 GetChallengeLevel() const;
    std::array<int32, 4> GetAffixes() const;
    bool HasAffix(Affixes affix);

    uint32 GetChallengeTimerToNow() const;
    void ModChallengeTimer();
    uint32 GetChallengeTimer();

    void ResetGo();
    void SendStartTimer(Player* player = nullptr);
    void SendStartElapsedTimer(Player* player = nullptr);
    void SendChallengeModeStart(Player* player = nullptr);
    void SendChallengeInstanceEncounterStart();
    void SendChallengeModeNewPlayerRecord(Player* player);
    void SummonGobject(bool door);
    uint8 GetItemCount(ObjectGuid guid) const;
    uint8 GetLevelBonus() const;
    void SendChallengeBonusLootPrompt(Player* player);

    float GetDamageMultiplier(uint8 challengeLevel);
    float GetHealthMultiplier(uint8 challengeLevel);

    void SetInstanceScript(InstanceScript* instanceScript);
    InstanceScript* GetInstanceScript() const;

    bool CanRun() { return _canRun; }
    bool CanCheckStart() { return _checkStart; }
    bool IsRunning() { return _run; }
    bool IsComplete() { return _complete; }
    bool IsHordeChallenge() { return _hordeSpawn; }

    GuidUnorderedSet _challengers;

    ObjectGuid m_gguid;
    ObjectGuid m_ownerGuid;
    ObjectGuid m_itemGuid;

    uint32 _challengeTimer;
    uint32 _affixQuakingTimer;

    FunctionProcessor m_Functions;
    uint32 _mapID;

private:
    std::map<ObjectGuid, uint8> _countItems;

    ObjectGuid _creator;
    std::array<int32, 4> _affixes;  // key modifiers
    std::bitset<size_t(MAX_AFFIXES)> _affixesTest;
    uint16 _chestTimers[3];
    Item* _item;
    Map* _map;
    InstanceScript* _instanceScript;
    MapChallengeModeEntry const* _challengeEntry;
    uint32 _challengeLevel;
    uint32 _instanceID;
    uint8 _rewardLevel;
    bool _isKeyDepleted;
    Scenario* _scenario;
    uint32 _deathCount = 0;
    bool _checkStart;
    bool _canRun;
    bool _run;
    bool _complete;
    bool _hordeSpawn;
};

#endif
