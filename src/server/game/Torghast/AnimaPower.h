#pragma once

#include "Common.h"
#include "Optional.h"

#include <vector>

namespace WorldPackets
{
    namespace Quest
    {
        class DisplayPlayerChoice;
    }
}

class GameObject;
class Player;

class TC_GAME_API AnimaPower
{
public:
    uint32 ResponseID = 0;
    uint32 MawPowerID = 0;
    int32 Unused901_1 = 0;
    int32 TypeArtFileID = 0;
    Optional<int32> Rarity;
    Optional<uint32> RarityColor;
    int32 Unused901_2 = 0; // seen values 11553, 11554, 11545
    int32 SpellID = 0;
    int32 MaxStacks = 0;
    std::string Name;
};

class TC_GAME_API AnimaPowerChoice
{
public:
    AnimaPowerChoice(Player* player, GameObject* go);
    ~AnimaPowerChoice();

    void BuildPacket(WorldPackets::Quest::DisplayPlayerChoice& packet);

    bool GeneratePowers(Player* player, uint32 mawPowerId = 0);

    void AddPower(AnimaPower* power)
    {
        Powers.push_back(power);
    }

    std::vector<AnimaPower*>& GetPowers()
    {
        return Powers;
    }

    ObjectGuid const& GetGameObjectGUID()
    {
        return _goGuid;
    }

private:
    ObjectGuid _playerGuid;
    ObjectGuid _goGuid;
    uint32 Rerolls = 1;
    std::vector<AnimaPower*> Powers;
};
