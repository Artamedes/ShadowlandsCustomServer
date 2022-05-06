#pragma once

#include "Common.h"
#include <vector>

namespace WorldPackets
{
    namespace BattlePay
    {
        struct ProductStruct;
        struct Product;
        struct ShopGroup;
        struct ShopEntry;
    }
}

class WorldSession;

class TC_GAME_API BattlePayMgr
{
    public:
        static BattlePayMgr* instance()
        {
            static BattlePayMgr instance;
            return &instance;
        }

        void LoadFromDB();
        void SendProductListResponseToSession(WorldSession* session);

    private:
        std::vector<WorldPackets::BattlePay::ProductStruct> ProductStructs;
        std::vector<WorldPackets::BattlePay::Product> Products;
        std::vector<WorldPackets::BattlePay::ShopGroup> Groups;
        std::vector<WorldPackets::BattlePay::ShopEntry> Entries;
};

#define sBattlePayMgr BattlePayMgr::instance()
