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

#ifndef TRINITY_INSTANCE_DATA_H
#define TRINITY_INSTANCE_DATA_H

#include "ZoneScript.h"
#include "Common.h"
#include "Duration.h"
#include <iosfwd>
#include <map>
#include <set>

#define OUT_SAVE_INST_DATA             TC_LOG_DEBUG("scripts", "Saving Instance Data for Instance %s (Map %d, Instance Id %d)", instance->GetMapName(), instance->GetId(), instance->GetInstanceId())
#define OUT_SAVE_INST_DATA_COMPLETE    TC_LOG_DEBUG("scripts", "Saving Instance Data for Instance %s (Map %d, Instance Id %d) completed.", instance->GetMapName(), instance->GetId(), instance->GetInstanceId())
#define OUT_LOAD_INST_DATA(a)          TC_LOG_DEBUG("scripts", "Loading Instance Data for Instance %s (Map %d, Instance Id %d). Input is '%s'", instance->GetMapName(), instance->GetId(), instance->GetInstanceId(), a)
#define OUT_LOAD_INST_DATA_COMPLETE    TC_LOG_DEBUG("scripts", "Instance Data Load for Instance %s (Map %d, Instance Id: %d) is complete.", instance->GetMapName(), instance->GetId(), instance->GetInstanceId())
#define OUT_LOAD_INST_DATA_FAIL        TC_LOG_ERROR("scripts", "Unable to load Instance Data for Instance %s (Map %d, Instance Id: %d).", instance->GetMapName(), instance->GetId(), instance->GetInstanceId())

class AreaBoundary;
class Creature;
class GameObject;
class InstanceMap;
class Item;
class ModuleReference;
class Player;
class Unit;
class TempSummon;
class Challenge;
struct InstanceSpawnGroupInfo;
struct CriteriaTree;
struct MythicKeystoneInfo;
enum class CriteriaType : uint8;
enum class CriteriaStartEvent : uint8;
enum EncounterCreditType : uint8;
namespace WorldPackets
{
    namespace Instance
    {
        class EncounterStart;
    }
}

enum EncounterFrameType
{
    ENCOUNTER_FRAME_SET_COMBAT_RES_LIMIT    = 0,
    ENCOUNTER_FRAME_RESET_COMBAT_RES_LIMIT  = 1,
    ENCOUNTER_FRAME_ENGAGE                  = 2,
    ENCOUNTER_FRAME_DISENGAGE               = 3,
    ENCOUNTER_FRAME_UPDATE_PRIORITY         = 4,
    ENCOUNTER_FRAME_ADD_TIMER               = 5,
    ENCOUNTER_FRAME_ENABLE_OBJECTIVE        = 6,
    ENCOUNTER_FRAME_UPDATE_OBJECTIVE        = 7,
    ENCOUNTER_FRAME_DISABLE_OBJECTIVE       = 8,
    ENCOUNTER_FRAME_UNK7                    = 9,    // Seems to have something to do with sorting the encounter units
    ENCOUNTER_FRAME_ADD_COMBAT_RES_LIMIT    = 10
};

// EnumUtils: DESCRIBE THIS
enum EncounterState
{
    NOT_STARTED   = 0,
    IN_PROGRESS   = 1,
    FAIL          = 2,
    DONE          = 3,
    SPECIAL       = 4,
    TO_BE_DECIDED = 5
};

enum DoorType
{
    DOOR_TYPE_ROOM          = 0,    // Door can open if encounter is not in progress
    DOOR_TYPE_PASSAGE       = 1,    // Door can open if encounter is done
    DOOR_TYPE_SPAWN_HOLE    = 2,    // Door can open if encounter is in progress, typically used for spawning places
    MAX_DOOR_TYPES
};

static uint32 const ChallengeModeOrb = 246779;
static uint32 const ChallengeModeDoor = 239323;

struct EntranceData
{
    uint32 BossId, WorldSafeLocId;
};

struct DoorData
{
    uint32 entry, bossId;
    DoorType type;
};

struct BossBoundaryEntry
{
    uint32 BossId;
    AreaBoundary const* Boundary;
};

struct TC_GAME_API BossBoundaryData
{
    typedef std::vector<BossBoundaryEntry> StorageType;
    typedef StorageType::const_iterator const_iterator;

    BossBoundaryData(std::initializer_list<BossBoundaryEntry> data) : _data(data) { }
    ~BossBoundaryData();
    const_iterator begin() const { return _data.begin(); }
    const_iterator end() const { return _data.end(); }

    private:
        StorageType _data;
};

struct MinionData
{
    uint32 entry, bossId;
};

struct DamageManager
{
    uint32 entry;
    Creature* creature;
    ObjectGuid guid;
};

struct ObjectData
{
    uint32 entry;
    uint32 type;
};

typedef std::vector<AreaBoundary const*> CreatureBoundary;

struct BossInfo
{
    BossInfo() : state(TO_BE_DECIDED) { }
    EncounterState state;
    GuidSet door[MAX_DOOR_TYPES];
    GuidSet minion;
    CreatureBoundary boundary;
};

struct DoorInfo
{
    explicit DoorInfo(BossInfo* _bossInfo, DoorType _type)
        : bossInfo(_bossInfo), type(_type) { }
    BossInfo* bossInfo;
    DoorType type;
};

struct MinionInfo
{
    explicit MinionInfo(BossInfo* _bossInfo) : bossInfo(_bossInfo) { }
    BossInfo* bossInfo;
};

typedef std::multimap<uint32 /*entry*/, DoorInfo> DoorInfoMap;
typedef std::pair<DoorInfoMap::const_iterator, DoorInfoMap::const_iterator> DoorInfoMapBounds;

typedef std::map<uint8 /*bossId*/, uint32 /*entranceLocationId*/> EntranceLocationMap;
typedef std::map<uint32 /*entry*/, MinionInfo> MinionInfoMap;
typedef std::map<uint32 /*type*/, ObjectGuid /*guid*/> ObjectGuidMap;
typedef std::map<uint32 /*entry*/, uint32 /*type*/> ObjectInfoMap;
typedef std::map<int8, std::vector<DamageManager> > DamageManagerMap;
typedef std::map<ObjectGuid, int8> PullDamageManagerMap;

enum eInstanceSpells
{
    SpellDetermination = 139068,
    /// Heroism, Bloodlust...
    ShamanSated = 57724,
    HunterInsanity = 95809,
    MageTemporalDisplacement = 80354,
    ShamanExhaustion = 57723,
    Bloodlust = 2825,
    Heroism = 32182,
    TempralDisplacement = 80354,
    AncientHysteria = 90355,
};

class TC_GAME_API InstanceScript : public ZoneScript
{
    public:
        explicit InstanceScript(InstanceMap* map);

        virtual ~InstanceScript();

        InstanceMap* instance;

        // On instance load, exactly ONE of these methods will ALWAYS be called:
        // if we're starting without any saved instance data
        virtual void Create();
        // if we're loading existing instance save data
        virtual void Load(char const* data);

        // When save is needed, this function generates the data
        virtual std::string GetSaveData();

        virtual void SaveToDB();

        virtual void Update(uint32 /*diff*/) { }
        void UpdateOperations(uint32 const diff);
        void UpdateCombatResurrection(uint32 /*diff*/);

        // Used by the map's CannotEnter function.
        // This is to prevent players from entering during boss encounters.
        virtual bool IsEncounterInProgress() const;

        // Called when a creature/gameobject is added to map or removed from map.
        // Insert/Remove objectguid to dynamic guid store
        virtual void OnCreatureCreate(Creature* creature) override;
        virtual void OnCreatureRemove(Creature* creature) override;

        virtual void OnGameObjectCreate(GameObject* go) override;
        virtual void OnGameObjectRemove(GameObject* go) override;

        // For use in Challenge
        virtual void OnPlayerEnterForScript(Player* player);
        virtual void OnPlayerLeaveForScript(Player* player);
        virtual void OnPlayerDiesForScript(Player* player);
        virtual void OnCreatureCreateForScript(Creature* creature);
        virtual void OnCreatureRemoveForScript(Creature* creature);
        virtual void OnCreatureUpdateDifficulty(Creature* creature);
        virtual void EnterCombatForScript(Creature* creature, Unit* enemy);
        virtual void CreatureDiesForScript(Creature* creature, Unit* killer);
        virtual void OnGameObjectCreateForScript(GameObject* go);
        virtual void OnGameObjectRemoveForScript(GameObject* go);
        virtual void OnUnitCharmed(Unit* unit, Unit* charmer);
        virtual void OnUnitRemoveCharmed(Unit* unit, Unit* charmer);
        virtual void BroadcastPacket(WorldPacket const* data) const;
        virtual void SummonChallengeGameObject(bool /*door*/) { };

        virtual bool HandleRelocatePlayer(Player* player) { return false; }

        // Called when falling damage are calculated for player
        virtual bool IsPlayerImmuneToFallDamage(Player* /*player*/) const { return false; }

        ObjectGuid GetObjectGuid(uint32 type) const;
        virtual ObjectGuid GetGuidData(uint32 type) const override;

        // Triggers a GameEvent
        // * If source is nullptr then event is triggered for each player in the instance as "source"
        void TriggerGameEvent(uint32 gameEventId, WorldObject* source = nullptr, WorldObject* target = nullptr) override;

        Creature* GetCreature(uint32 type);
        GameObject* GetGameObject(uint32 type);

        // Called when a player successfully enters the instance.
        virtual void OnPlayerEnter(Player* /*player*/) { }
        // Called when a player successfully leaves the instance.
        virtual void OnPlayerLeave(Player* /*player*/) { }

        virtual void OnCompletedCriteriaTree(CriteriaTree const* /*tree*/) { }

        // Handle open / close objects
        // * use HandleGameObject(0, boolen, GO); in OnObjectCreate in instance scripts
        // * use HandleGameObject(GUID, boolen, nullptr); in any other script
        void HandleGameObject(ObjectGuid guid, bool open, GameObject* go = nullptr);

        // Change active state of doors or buttons
        void DoUseDoorOrButton(ObjectGuid guid, uint32 withRestoreTime = 0, bool useAlternativeState = false);
        void DoCloseDoorOrButton(ObjectGuid guid);

        // Respawns a GO having negative spawntimesecs in gameobject-table
        void DoRespawnGameObject(ObjectGuid guid, Seconds timeToDespawn = 1min);

        // Sends world state update to all players in instance
        void DoUpdateWorldState(int32 worldStateId, int32 value);

        // Send Notify to all players in instance
        void DoSendNotifyToInstance(char const* format, ...);

        // Update Achievement Criteria for all players in instance
        void DoUpdateCriteria(CriteriaType type, uint32 miscValue1 = 0, uint32 miscValue2 = 0, Unit* unit = nullptr);

        // Remove Auras due to Spell on all players in instance
        void DoRemoveAurasDueToSpellOnPlayers(uint32 spell, bool includePets = false, bool includeControlled = false);
        void DoRemoveAurasDueToSpellOnPlayer(Player* player, uint32 spell, bool includePets = false, bool includeControlled = false);

        // Cast spell on all players in instance
        void DoCastSpellOnPlayers(uint32 spell, bool includePets = false, bool includeControlled = false);
        void DoCastSpellOnPlayer(Player* player, uint32 spell, bool includePets = false, bool includeControlled = false);

        // Play scene by packageId on all players in instance
        void DoPlayScenePackageIdOnPlayers(uint32 scenePackageId);

        // Play scene by Id on all players in instance
        void DoPlaySceneOnPlayers(uint32 sceneId);

        // Return wether server allow two side groups or not
        static bool ServerAllowsTwoSideGroups();

        CreatureGroup* SummonCreatureGroup(uint32 creatureGroupID, std::list<TempSummon*>* list = nullptr);
        CreatureGroup* GetCreatureGroup(uint32 creatureGroupID);
        void DespawnCreatureGroup(uint32 creatureGroupID);

        virtual bool SetBossState(uint32 id, EncounterState state, bool forced = false);
        EncounterState GetBossState(uint32 id) const { return id < bosses.size() ? bosses[id].state : TO_BE_DECIDED; }
        static char const* GetBossStateName(uint8 state);
        CreatureBoundary const* GetBossBoundary(uint32 id) const { return id < bosses.size() ? &bosses[id].boundary : nullptr; }

        // Add aura on all players in instance
        void DoAddAuraOnPlayers(uint32 spell);

        // Remove cooldown for spell on all players in instance
        void DoRemoveSpellCooldownOnPlayers(uint32 spellID);

        // Remove cooldowns equal or less than specified time to all players in instance
        void DoRemoveSpellCooldownWithTimeOnPlayers(uint32 minRecoveryTime);

        // Do combat stop on all players in instance
        void DoCombatStopOnPlayers();

        void DoPlayConversation(uint32 conversationId);

        // Complete Achievement for all players in instance
        void DoCompleteAchievement(uint32 achievement);

        // Achievement criteria additional requirements check
        // NOTE: not use this if same can be checked existed requirement types from AchievementCriteriaRequirementType
        virtual bool CheckAchievementCriteriaMeet(uint32 /*criteria_id*/, Player const* /*source*/, Unit const* /*target*/ = nullptr, uint32 /*miscvalue1*/ = 0);

        // Checks boss requirements (one boss required to kill other)
        virtual bool CheckRequiredBosses(uint32 /*bossId*/, Player const* /*player*/ = nullptr) const { return true; }

        // Checks encounter state at kill/spellcast
        void UpdateEncounterStateForKilledCreature(uint32 creatureId, Unit* source, Unit* player = nullptr);
        void UpdateEncounterStateForSpellCast(uint32 spellId, Unit* source, Unit* player = nullptr);

        // Used only during loading
        void SetCompletedEncountersMask(uint32 newMask);

        // Returns completed encounters mask for packets
        uint32 GetCompletedEncounterMask() const { return completedEncounters; }

        /// Add timed delayed operation
        /// @p_Timeout  : Delay time
        /// @p_Function : Callback function
        void AddTimedDelayedOperation(uint32 timeout, std::function<void()>&& function)
        {
            emptyWarned = false;
            timedDelayedOperations.push_back(std::pair<uint32, std::function<void()>>(timeout, function));
        }

        /// Called after last delayed operation was deleted
        /// Do whatever you want
        virtual void LastOperationCalled() { }

        std::vector<std::pair<int32, std::function<void()>>>    timedDelayedOperations;   ///< Delayed operations
        bool                                                    emptyWarned;              ///< Warning when there are no more delayed operations

        uint32 GetEncounterCount() const { return uint32(bosses.size()); }

        // Sets the entrance location (WorldSafeLoc) id
        void SetEntranceLocation(uint32 worldSafeLocationId);

        // Sets a temporary entrance that does not get saved to db
        void SetTemporaryEntranceLocation(uint32 worldSafeLocationId) { _temporaryEntranceId = worldSafeLocationId; }

        // Get's the current entrance id
        uint32 GetEntranceLocation() const { return _temporaryEntranceId ? _temporaryEntranceId : _entranceId; }

        // Only used by areatriggers that inherit from OnlyOnceAreaTriggerScript
        void MarkAreaTriggerDone(uint32 id) { _activatedAreaTriggers.insert(id); }
        void ResetAreaTriggerDone(uint32 id) { _activatedAreaTriggers.erase(id); }
        bool IsAreaTriggerDone(uint32 id) const { return _activatedAreaTriggers.find(id) != _activatedAreaTriggers.end(); }

        void SendEncounterUnit(uint32 type, Unit* unit = nullptr, uint8 priority = 0);
        void SendEncounterStart(uint32 inCombatResCount = 0, uint32 maxInCombatResCount = 0, uint32 inCombatResChargeRecovery = 0, uint32 nextCombatResChargeTime = 0, bool inProgress = true);
        void SendEncounterEnd();
        void BuildPlayerDatas(WorldPackets::Instance::EncounterStart& packet);
        void SendEncounterStart(uint32 encounterID);
        void SendEncounterEnd(uint32 encounterID, bool success);
        uint32 GetEncounterIDForBoss(Creature* boss) const;

        //Damage Manager
        void UpdateDamageManager(ObjectGuid caller, int32 damage, bool heal = false);
        void AddToDamageManager(Creature* creature, uint8 pullNum = 0);
        bool CheckDamageManager();
        void SetPullDamageManager(ObjectGuid guid, uint8 pullId);
        int8 GetPullDamageManager(ObjectGuid guid) const;

        DamageManagerMap damageManager;
        PullDamageManagerMap pullDamageManager;
        bool initDamageManager;

        void SendBossKillCredit(uint32 encounterId);

        // ReCheck PhaseTemplate related conditions
        void UpdatePhasing();

        void InitializeCombatResurrections(uint8 charges = 1, uint32 interval = 0);
        void AddCombatResurrectionCharge();
        void UseCombatResurrection();
        void ResetCombatResurrections();
        uint8 GetCombatResurrectionCharges() const { return _combatResurrectionCharges; }
        uint32 GetCombatResurrectionChargeInterval() const;

        virtual bool HandlePlayerRepopRequest(Player* ) const { return false; }
        virtual void OnPlayerPositionChange(Player* ) { }
        virtual bool HandleGetStartPosition(float&, float&, float&, float &) const { return false; }
        virtual uint32 GetLootIdForDungeon() { return 0; };
        virtual void OnChallengeStart() { }
        virtual void OnChallengeComplete() { }

        //Pop all player to the graveyard more near in the instance
        void RepopPlayersAtGraveyard();

        // Challenge
        void SetChallenge(Challenge* challenge);
        Challenge* GetChallenge() const;
        bool IsChallenge() const;
        void ResetChallengeMode(Player* player);

        ObjectGuid GetChallengeModeChest() { return _challengeChest; }
        ObjectGuid GetChallengeModeOrb() { return _challengeOrbGuid; }
        ObjectGuid GetChallengeModeDoor() { return _challengeDoorGuid; }
        void AddChallengeModeChest(ObjectGuid chestGuid);
        void AddChallengeModeDoor(ObjectGuid doorGuid);
        void AddChallengeModeOrb(ObjectGuid orbGuid);
        void CreateChallenge(Player* player, MythicKeystoneInfo* keystoneInfo);

        ObjectGuid _challengeDoorGuid;
        ObjectGuid _challengeOrbGuid;
        ObjectGuid _challengeChest;

        void SendCompleteGuildChallenge(uint32 id);

        virtual void NerfLeechIfNeed(Unit* /*attacker*/, int32& /*heal*/) { }

    protected:
        void SetHeaders(std::string const& dataHeaders);
        void SetBossNumber(uint32 number) { bosses.resize(number); }
        void LoadBossBoundaries(BossBoundaryData const& data);
        void LoadEntranceData(EntranceData const* data);
        void LoadDoorData(DoorData const* data);
        void LoadMinionData(MinionData const* data);
        void LoadObjectData(ObjectData const* creatureData, ObjectData const* gameObjectData);

        void AddObject(Creature* obj, bool add);
        void AddObject(GameObject* obj, bool add);
        void AddObject(WorldObject* obj, uint32 type, bool add);

        virtual void AddDoor(GameObject* door, bool add);
        void AddMinion(Creature* minion, bool add);

        virtual void UpdateDoorState(GameObject* door);
        void UpdateMinionState(Creature* minion, EncounterState state);

        void UpdateSpawnGroups();

        // Exposes private data that should never be modified unless exceptional cases.
        // Pay very much attention at how the returned BossInfo data is modified to avoid issues.
        BossInfo* GetBossInfo(uint32 id);

        // Instance Load and Save
        bool ReadSaveDataHeaders(std::istringstream& data);
        void ReadSaveDataBossStates(std::istringstream& data);
        virtual void ReadSaveDataMore(std::istringstream& /*data*/) { }
        void WriteSaveDataHeaders(std::ostringstream& data);
        void WriteSaveDataBossStates(std::ostringstream& data);
        virtual void WriteSaveDataMore(std::ostringstream& /*data*/) { }

        bool _SkipCheckRequiredBosses(Player const* player = nullptr) const;

    private:
        static void LoadObjectData(ObjectData const* creatureData, ObjectInfoMap& objectInfo);
        void UpdateEncounterState(EncounterCreditType type, uint32 creditEntry, Unit* source, Unit* unit = nullptr);

        std::vector<char> headers;
        std::vector<BossInfo> bosses;
        EntranceLocationMap entrances;
        DoorInfoMap doors;
        MinionInfoMap minions;
        ObjectInfoMap _creatureInfo;
        ObjectInfoMap _gameObjectInfo;
        ObjectGuidMap _objectGuids;
        uint32 completedEncounters; // completed encounter mask, bit indexes are DungeonEncounter.dbc boss numbers, used for packets
        std::vector<InstanceSpawnGroupInfo> const* const _instanceSpawnGroups;
        std::unordered_set<uint32> _activatedAreaTriggers;
        uint32 _entranceId;
        uint32 _temporaryEntranceId;
        uint32 _combatResurrectionTimer;
        uint8 _combatResurrectionCharges; // the counter for available battle resurrections
        bool _combatResurrectionTimerStarted;

        std::map<uint32, std::list<ObjectGuid>> summonBySummonGroupIDs;

        uint32 _disabledMask;
        uint32 _encounterTime;

        Challenge* _challenge;

    #ifdef TRINITY_API_USE_DYNAMIC_LINKING
        // Strong reference to the associated script module
        std::shared_ptr<ModuleReference> module_reference;
    #endif // #ifndef TRINITY_API_USE_DYNAMIC_LINKING

        friend class debug_commandscript;
};

#endif // TRINITY_INSTANCE_DATA_H
