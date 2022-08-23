#pragma once

#include "Common.h"

class Player;

class GreatVault
{
public:
    GreatVault(Player* player);

    void SendWeeklyRewardsProgressResult();
    void SendWeeklyRewardsResult();
    void SendWeeklyRewardsClaimResult();
};
