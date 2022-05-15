#pragma once
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "WorldSession.h"
#include "QuestPackets.h"
#include "GossipDef.h"
#include "ScriptedGossip.h"
#include "TemporarySummon.h"
#include "Player.h"
#include "MotionMaster.h"
#include "Item.h"
#include "CellImpl.h"
#include "Cell.h"
#include "GridNotifiers.h"
#include "MoveSpline.h"
#include "ObjectMgr.h"
#include "Chat.h"
#include <map>
#include <sstream>

#include "../CustomInstanceScript.h"

enum DarkmaulCitadel
{
    BossCrystal = 0,

    // Enemies
    Goblin          = 860000,
    Kobold          = 860001,
    Orc             = 860002,
    OrcBruiser      = 860003,
    Beholder        = 860004,
    Ogre            = 860005,
    GoblinChef      = 860007,

    // Friendlies
    RiftCrystal     = 851000,
    // Summons
    Archer          = 851001,
    FireWizard      = 851002,
    Cannon          = 851003,
    FriendlyOgre    = 851007,
    TauntTotem      = 851004,
    SlowTotem       = 851006, // don't attack
    BombTotem       = 851005, // don't attack

    // Actions
    StartEvent   = 1,
    Cleanup,
    StartStageOffset = 1000,
    LeftWaypoints    = 2000,
    RightWaypoints   = 2001,
    // Creature set data
    SetRiftEnergy    = 3000,

    // Instance Set Data
    SetDataNextStage = 1337,
    SetMaxRiftEnergy,
    SetDifficulty,
    SetStartRiftEnergy,
    SetAwardRiftEssence,
    SetDefensePoints,
    SetMaxDefensePoints,
    SetAddDefensePoints,
    SetRemoveDefensePoints,
    // Instance Get Data
    DataGetMaxEnergy = 5000,
    DataGetCurrentDifficulty,
    DataGetDefensePoints,
    DataGetMaxDefensePoints,

    // PlayerChoice
    PlayerChoiceID   = 682925854,

    // MapId
    DarkmaulMapId    = 2236,

    // Spells
    Fireball         = 329420,
    Pyroblast        = 147600,

    // Currencies
    RiftEssence      = 10177,
    AllotedRiftEnergy = 10178, // useless
    RiftEnergy = 10179, // per instance currency
    DefensePoints = 10180,

    // Broadcasts
    DefenderNpcTextId = 851001,
    DungeonDefenseItemNpcTextId = 699999,

    // Difficulties
    DifficultyNormal = 0,
    DifficultyEasy   = 1,
    DifficultyHeroic = 2,
    DifficultyMythic = 3,
};

const Position CrystalSpawnPos = { 872.208f, -1877.28f, 207.632f, 2.08771f };
const Position EnemySpawnPos = { 913.561f, -1762.8f, 181.191f, 3.69085f };

const Position EnemyPointOne = { 886.193f, -1779.7f, 181.419f, 3.74321f };
const Position EnemyPointTwo = { 849.567f, -1808.24f, 181.49f, 4.28971f };
const Position EnemyPointThree = { 857.928f, -1850.06f, 184.705f, 5.22565f };

const Position EnemyPointRightOne = { 832.571f, -1901.04f, 196.241f, 5.03912f }; // right one
const Position EnemyPointRightTwo = { 865.323f, -1881.52f, 207.745f, 0.562353f }; // right two

const Position EnemyPointLeftOne = { 916.215f, -1854.46f, 196.256f, 2.75493f }; // left one
const Position EnemyPointLeftTwo = { 877.948f, -1873.99f, 207.624f, 3.69086f }; // left two

struct DungeonDefenseCreature
{
    uint64 MinHealth;
    uint64 MaxHealth;
    float  MinDmg;
    float  MaxDmg;
    float  Range;
    uint32 RiftEnergyCost;
    uint32 RiftEnergyReward;
    uint32 DefensePoints;
    std::vector<uint32> UpgradeEntries;
};

using DungeonDefenseCreatureStorage = std::unordered_map<std::pair<uint32, uint32>, DungeonDefenseCreature>;

struct DungeonDefenseTemplate
{
    uint32 StartRiftEnergy;
    uint32 MaxRiftEnergy;
    uint32 RewardRiftEssence;
    uint32 MaxDefensePoints;
};

using DungeonDefenseTemplateStorage = std::unordered_map<uint32, DungeonDefenseTemplate>;

struct DungeonDefenseStageMobs
{
    uint32 NpcEntry;
    uint32 Amount;
};

using DungeonDefenseStageStorage = std::multimap<std::pair<uint32, uint32>, DungeonDefenseStageMobs>;

class DungeonDefenseMgr
{
public:
    static DungeonDefenseMgr* instance()
    {
        static DungeonDefenseMgr instance;
        return &instance;
    }

    DungeonDefenseCreatureStorage m_CreatureStorage;
    DungeonDefenseTemplateStorage m_DefenseTemplates;
    DungeonDefenseStageStorage    m_StageStorage;

    void LoadFromDB()
    {
        m_CreatureStorage.clear();
        m_DefenseTemplates.clear();
        m_StageStorage.clear();

        if (auto result = WorldDatabase.Query("SELECT Entry, Difficulty, MinHealth, MaxHealth, MinDmg, MaxDmg, `Range`, RiftEnergyCost, RiftEnergyReward, DefensePoints, UpgradeEntries FROM z_dungeon_defense_creatures"))
        {
            do
            {
                auto fields = result->Fetch();

                DungeonDefenseCreature defenseCreature;

                defenseCreature.MinHealth        = fields[2].GetUInt64();
                defenseCreature.MaxHealth        = fields[3].GetUInt64();
                defenseCreature.MinDmg           = fields[4].GetFloat();
                defenseCreature.MaxDmg           = fields[5].GetFloat();
                defenseCreature.Range            = fields[6].GetUInt64();
                defenseCreature.RiftEnergyCost   = fields[7].GetUInt32();
                defenseCreature.RiftEnergyReward = fields[8].GetUInt32();
                defenseCreature.DefensePoints    = fields[9].GetUInt32();

                // UpgradeEntries
                for (std::string_view token : Trinity::Tokenize(fields[10].GetStringView(), ',', false))
                    if (Optional<uint32> entryId = Trinity::StringTo<uint32>(token))
                        defenseCreature.UpgradeEntries.push_back(*entryId);

                m_CreatureStorage[std::make_pair(fields[0].GetUInt32(), fields[1].GetUInt32())] = defenseCreature;

            } while (result->NextRow());
        }

        if (auto result = WorldDatabase.Query("SELECT DifficultyID, StartRiftEnergy, MaxRiftEnergy, RewardRiftEssence, MaxDefensePoints FROM z_dungeon_defense_template"))
        {
            do
            {
                auto fields = result->Fetch();

                DungeonDefenseTemplate defenseTemplate;

                defenseTemplate.StartRiftEnergy   = fields[1].GetUInt32();
                defenseTemplate.MaxRiftEnergy     = fields[2].GetUInt32();
                defenseTemplate.RewardRiftEssence = fields[3].GetUInt32();
                defenseTemplate.MaxDefensePoints  = fields[4].GetUInt32();

                m_DefenseTemplates[fields[0].GetUInt32()] = defenseTemplate;

            } while (result->NextRow());
        }

        if (auto result = WorldDatabase.Query("SELECT DifficultyID, Stage, NpcEntry, Amount FROM z_dungeon_defense_stages ORDER by `Ordering`"))
        {
            do
            {
                auto fields = result->Fetch();

                DungeonDefenseStageMobs stageMobs;

                uint32 DifficultyID = fields[0].GetUInt32();
                uint32 Stage        = fields[1].GetUInt32();
                stageMobs.NpcEntry  = fields[2].GetUInt32();
                stageMobs.Amount    = fields[3].GetUInt32();

                m_StageStorage.insert(std::make_pair(std::make_pair(DifficultyID, Stage), stageMobs));

            } while (result->NextRow());
        }
    }

    void GiveRiftEnergyToPlayer(Player* player, uint32 reward)
    {
        auto instance = player->GetInstanceScript();
        uint32 currCurrency = player->GetCurrency(RiftEnergy);
        uint32 maxCurrency = instance->GetData(DataGetMaxEnergy);
        if (currCurrency <= maxCurrency)
        {
            if (currCurrency + reward > maxCurrency)
            {
                uint32 prevReward = reward;
                reward = maxCurrency - currCurrency;
                uint32 diff = prevReward - reward;
                player->ModifyCurrency(RiftEssence, diff);
            }

            player->ModifyCurrency(RiftEnergy, reward);
        }
    }

    void SendRemovedRiftEnergyTo(Player* player, uint32 cost)
    {
        ChatHandler(player).PSendSysMessage("|cffFFA600-%u Rift Energy", cost);
    }

    DungeonDefenseCreature const* GetDefenseDataForCreature(Creature* me)
    {
        uint32 difficulty = DifficultyNormal;
        if (auto instance = me->GetInstanceScript())
            difficulty = instance->GetData(DataGetCurrentDifficulty);

        auto it = m_CreatureStorage.find(std::make_pair(me->GetEntry(), difficulty));
        if (it == m_CreatureStorage.end())
        {
            it = m_CreatureStorage.find(std::make_pair(me->GetEntry(), DifficultyNormal));
            if (it == m_CreatureStorage.end())
                return nullptr;
        }

        return &it->second;
    }

    void InitializeCreature(Creature* me, float & range)
    {
        if (auto data = GetDefenseDataForCreature(me))
        {
            uint64 health = urand(data->MinHealth, data->MaxHealth);

            me->SetMaxHealth(health);
            me->SetHealth(health);
            range = data->Range;
        }
    }

    void InitializeCreatureDamage(Creature* me, float& minDmg, float& maxDmg)
    {
        if (auto data = GetDefenseDataForCreature(me))
        {
            minDmg = data->MinDmg;
            maxDmg = data->MaxDmg;
        }
    }

    void HandleCreatureDeath(Creature* me)
    {
        if (auto instance = me->GetInstanceScript())
        {
            if (auto data = GetDefenseDataForCreature(me))
            {
                uint32 reward = data->RiftEnergyReward;

                std::list<Player*> players;
                for (MapReference const& ref : instance->instance->GetPlayers())
                    if (Player* player = ref.GetSource())
                        players.push_back(player);

                Player* randPlayer = nullptr;

                int i = 5;
                while (i > 0)
                {
                    randPlayer = Trinity::Containers::SelectRandomContainerElement(players);
                    if (!randPlayer->IsGameMaster())
                        break;

                    i--;
                }

                if (randPlayer)
                {
                    GiveRiftEnergyToPlayer(randPlayer, reward);
                }
            }
        }
    }

    std::string GetDifficultyText(uint32 difficultyId) const
    {
        switch (difficultyId)
        {
            case DifficultyNormal:
            case DifficultyEasy  :
                return "Easy";
            case DifficultyHeroic:
                return "Heroic";
            case DifficultyMythic:
                return "Mythic";

            default:
                return "";
        }
    }
};

#define sDungeonDefenseMgr DungeonDefenseMgr::instance()
