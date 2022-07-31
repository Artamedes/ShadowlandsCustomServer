#include "TorghastDefines.h"
#include "CovenantMgr.h"

using namespace Torghast;

struct instance_torghast : public InstanceScript
{
public:
    instance_torghast(InstanceMap* map) : InstanceScript(map) { }

    void OnPlayerEnter(Player* player) override
    {
        player->SetJailerTowerLevel(5);
        player->SetJailerTowerLevelMax(5);

        DoUpdateWorldState(eWorldStates::TorghastLevel, 10);
        DoUpdateWorldState(eWorldStates::TorghastType, JailersTowerType::UpperReaches);

        player->CastSpell(player, eLightParams::UpperReaches, true);

        /// Set our box of many things up (stored in conduits)
        for (auto& it : player->GetCovenantMgr()->GetConduits())
        {
            // This will cast our box of many things spells, as some have a restriction per AreaID.
            if (it.second->CovenantID == 0 && it.second->GetSoulbindID() == 0)
                it.second->FlagsUpdated();
        }

        WorldPacket data(SMSG_MULTI_FLOOR_NEW_FLOOR, 150);
        data << uint64(2252081294093932760);
        data << uint32(82);
        data << uint32(1);
        data << uint32(61);
        data << uint32(1);

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
    }


};

// TODO: Reset phantasma on exit torghast map.

void AddSC_instance_torghast()
{
    RegisterInstanceScript(instance_torghast, 2162);
}
