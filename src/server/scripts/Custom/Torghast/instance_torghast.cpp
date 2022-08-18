#include "TorghastDefines.h"
#include "CovenantMgr.h"
#include "TorghastFloorData.h"
#include <sstream>

using namespace Torghast;

struct instance_torghast : public InstanceScript
{
public:
    instance_torghast(InstanceMap* map) : InstanceScript(map)
    {
        SetupFloors();
    }

    void OnPlayerEnter(Player* player) override
    {
        player->SetJailerTowerLevel(1);
        player->SetJailerTowerLevelMax(5);

        DoUpdateWorldState(eWorldStates::TorghastLevel, 1);
        DoUpdateWorldState(eWorldStates::TorghastType, JailersTowerType::UpperReaches);
        DoUpdateWorldState(eWorldStates::CurrentFloor, CurrFloorLevel);
        DoUpdateWorldState(eWorldStates::NextFloor, CurrFloorLevel + 1);

        switch (Type)
        {
            case JailersTowerType::SkoldusHalls:
                player->CastSpell(player, eLightParams::SkoldusHall, true);
                break;
            case JailersTowerType::FractureChambers:
                player->CastSpell(player, eLightParams::FractureChambers, true);
                break;
            case JailersTowerType::Soulforges:
                player->CastSpell(player, eLightParams::Soulforges, true);
                break;
            case JailersTowerType::Coldheart:
                player->CastSpell(player, eLightParams::ColdheartInterstia, true);
                break;
            case JailersTowerType::Mortregar:
                player->CastSpell(player, eLightParams::Mortregar, true);
                break;
            case JailersTowerType::UpperReaches:
                player->CastSpell(player, eLightParams::UpperReaches, true);
                break;
            case JailersTowerType::AdamantVaults:
                player->CastSpell(player, eLightParams::AdamantVaults, true);
                break;
            default:
                break;
        }

        /// Set our box of many things up (stored in conduits)
        for (auto& it : player->GetCovenantMgr()->GetConduits())
        {
            // This will cast our box of many things spells, as some have a restriction per AreaID.
            if (it.second->CovenantID == 0 && it.second->GetSoulbindID() == 0)
                it.second->FlagsUpdated();
        }

        /// Not sure if this packet does anything, or what it represents.
        WorldPacket data(SMSG_MULTI_FLOOR_NEW_FLOOR, 150);
        data << uint64(2252081294093932760);
        data << uint32(82);
        data << uint32(1);
        data << uint32(61);
        data << uint32(1);

        /// Could be related to Venari?
        std::vector<uint32> unkVector = { 941, 978, 999, 1036, 1176, 1151, 984, 969, 952, 953, 1025, 1027, 1030, 1016, 1068, 1083, 1276, 1262 };
        data << uint32(unkVector.size());
        for (uint32 dumb : unkVector)
            data << dumb;

        std::string dumbstring = "06 Upper - Normal - 2 Levels (82)";
        data.WriteBits(dumbstring.size(), 8);
        data.FlushBits();
        data.WriteString(dumbstring);
        player->SendDirectMessage(&data);
    }

    void OnPlayerLeave(Player* player) override
    {
        player->SetJailerTowerLevel(0);
        player->SetJailerTowerLevelMax(0);
        /// Need to check if this is called on logout, we can reset phantasma here.
        player->ModifyCurrency(eCurrencies::Phantasma, 0, true, true, true);
    }

    void WriteSaveDataMore(std::ostringstream& data) override
    {
        data << CurrFloorLevel;
    }

    void ReadSaveDataMore(std::istringstream& data) override
    {
        data >> CurrFloorLevel;

        DoUpdateWorldState(eWorldStates::CurrentFloor, CurrFloorLevel);
        DoUpdateWorldState(eWorldStates::NextFloor, CurrFloorLevel + 1);
    }

    void OnUnitDeath(Unit* unit) override
    {
        auto creature = unit->ToCreature();
        if (!creature)
            return;

        if (!creature->GetSpawnId())
            return;

        /// We need to iterate the floors to see what boss we killed
        for (auto const& floor : Floors)
        {
            /// Check if the boss killed was one on our list
            if (floor.Floor.BossSpawnId == creature->GetSpawnId())
            {
                /// Get the door guid, this is filled in OnCreatureCreate
                auto it = NextFloorDoorGuids.find(floor.Floor.DoorSpawnId);
                if (it != NextFloorDoorGuids.end())
                {
                    /// Activate the door. and up the next level
                    /// Door shouldn't be null at this point, unless something went wrong.
                    if (auto door = instance->GetCreature(it->second))
                    {
                        if (CurrFloorLevel >= MaxFloors)
                            return;

                        CurrFloorLevel++;

                        DoUpdateWorldState(eWorldStates::CurrentFloor, CurrFloorLevel);
                        DoUpdateWorldState(eWorldStates::NextFloor, CurrFloorLevel + 1);

                        if (door->AI())
                            door->AI()->DoAction(1);
                        break;
                    }
                }
            }
        }
    }

    void OnCreatureCreate(Creature* creature) override
    {
        if (!creature->GetSpawnId())
            return;

        switch (creature->GetEntry())
        {
            /// Fill each floor in the NextFloorDoorGuids map by spawnid for access on boss death
            case NpcEntries::NextFloor:
                NextFloorDoorGuids[creature->GetSpawnId()] = creature->GetGUID();
                break;
        }

        /// Auto activate doors that have no bosses (Break rooms)
        for (auto const& floor : Floors)
        {
            if (floor.Floor.DoorSpawnId == creature->GetSpawnId())
            {
                switch (floor.Floor.Type)
                {
                    case FloorType::Break:
                        if (creature->AI())
                            creature->AI()->DoAction(1);
                        break;
                    default:
                        break;
                }
            }
        }
    }

    /// Sets up the floors for torghast type.
    void SetupFloors()
    {
        if (!didSetup)
        {
            didSetup = true;

            /// We want to get random floors for each run.
            uint32 randFloors[] = { 0, 1, 2 };
            Trinity::Containers::RandomShuffle(randFloors);

            switch (Type)
            {
                case JailersTowerType::UpperReaches:
                    Floors.push_back( { UpperReaches::TrashFloor[randFloors[0]], false });
                    Floors.push_back( { UpperReaches::TrashFloor[randFloors[1]], false });
                    Floors.push_back( { UpperReaches::BreakFloor[0], false });
                    Floors.push_back( { UpperReaches::TrashFloor[randFloors[2]], false });
                    Floors.push_back( { UpperReaches::BossFloor[0], false });
                    MaxFloors = static_cast<uint32>(Floors.size());
                    break;
                default:
                    break;
            }

            DoUpdateWorldState(eWorldStates::CurrentFloor, CurrFloorLevel);
            DoUpdateWorldState(eWorldStates::NextFloor, CurrFloorLevel + 1);
        }
    }

    void SetGuidData(uint32 dataId, ObjectGuid guid) override
    {
        /// Called from the SpellScript after fade to black aura is removed.
        /// Handles teleporting the player to the next floor and updating the current floor worldstate.
        if (dataId == GotoNextFloor)
        {
            auto player = instance->GetPlayer(guid);
            if (player)
            {
                auto& floorData = Floors[CurrFloorLevel - 1];

                player->NearTeleportTo(floorData.Floor.TeleportPos, true, true);
                player->SetJailerTowerLevel(CurrFloorLevel);
                player->SendUpdateWorldState(eWorldStates::CurrentFloor, CurrFloorLevel);

                if (!floorData.CheckedFloor)
                {
                    floorData.CheckedFloor = true;
                    if (floorData.Floor.Type == FloorType::Break)
                    {
                        CurrFloorLevel++;
                    }
                }
            }
        }
    }

    bool HandleRelocatePlayer(Player* player)
    {
        player->Relocate(Floors[CurrFloorLevel - 1].Floor.TeleportPos);
        player->SetJailerTowerLevel(CurrFloorLevel);
        player->SendUpdateWorldState(eWorldStates::CurrentFloor, CurrFloorLevel);
        return true;
    }

    private:
        JailersTowerType::JailerTower Type = JailersTowerType::UpperReaches;
        bool didSetup = false;
        uint32 CurrFloorLevel = 1;
        uint32 MaxFloors = 5;
        std::vector<TorghastFloorData> Floors;
        std::unordered_map<uint32, ObjectGuid> NextFloorDoorGuids;
};

void AddSC_instance_torghast()
{
    RegisterInstanceScript(instance_torghast, 2162);
}
