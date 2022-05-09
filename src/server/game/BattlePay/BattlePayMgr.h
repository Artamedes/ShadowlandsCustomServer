#pragma once

#include "BattlePayPackets.h"
#include "Common.h"
#include <vector>

class WorldSession;

struct Purchase
{
    uint64 PurchaseID = 0;
    uint32 ServerToken = 0;
    uint32 AccountID = 0;
    uint32 ClientToken = 0;
    uint32 ProductID = 0;
    ObjectGuid CharacterGuid;
    std::string System;
    std::string PublicKey;
};

class TC_GAME_API BattlePayMgr
{
    public:
        ~BattlePayMgr();

        static BattlePayMgr* instance()
        {
            static BattlePayMgr instance;
            return &instance;
        }

        void LoadFromDB();

        std::map<uint32, WorldPackets::BattlePay::ProductStruct> const& GetProductStruct() { return ProductStructs; }
        std::map<uint32, WorldPackets::BattlePay::Product> const& GetProducts() { return Products; }
        std::map<uint32, WorldPackets::BattlePay::ShopGroup> const& GetGroups() { return Groups; }
        std::map<uint32, WorldPackets::BattlePay::ShopEntry> const& GetEntries() { return Entries; }

        WorldPackets::BattlePay::Product const* GetProductById(uint32 productId) const
        {
            auto itr = Products.find(productId);
            if (itr != Products.end())
                return &itr->second;
            return nullptr;
        }

        WorldPackets::BattlePay::ProductStruct const* GetProductInfoById(uint32 productId) const
        {
            auto itr = ProductStructs.find(productId);
            if (itr != ProductStructs.end())
                return &itr->second;
            return nullptr;
        }

        Purchase* GetPurchase(uint64 purchaseId)
        {
            auto itr = Purchases.find(purchaseId);
            if (itr != Purchases.end())
                return itr->second;
            return nullptr;
        }

        bool RemovePurchase(uint64 purchaseId)
        {
            auto itr = Purchases.find(purchaseId);
            if (itr != Purchases.end())
            {
                delete itr->second;
                Purchases.erase(itr);
            }
            return false;
        }

        bool RemovePurchase(Purchase* purchase)
        {
            return RemovePurchase(purchase->PurchaseID);
        }

        uint64 CurrPurchaseID = 0;
        Purchase* CreatePurchase();

    private:
        std::map<uint32, WorldPackets::BattlePay::ProductStruct> ProductStructs;
        std::map<uint32, WorldPackets::BattlePay::Product> Products;
        std::map<uint32, WorldPackets::BattlePay::ShopGroup> Groups;
        std::map<uint32, WorldPackets::BattlePay::ShopEntry> Entries;
        std::map<uint64, Purchase*> Purchases;
};

#define sBattlePayMgr BattlePayMgr::instance()
