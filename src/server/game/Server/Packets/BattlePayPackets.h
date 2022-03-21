#pragma once

#include "Packet.h"
#include "ObjectGuid.h"
#include "Optional.h"
#include "PacketUtilities.h"

namespace WorldPackets
{
    namespace BattlePay
    {

        struct Visual
        {
            std::string Name;
            uint32 DisplayId;
            uint32 VisualId;
            uint32 Unk;
        };

        struct DisplayInfo
        {
            Optional<uint32> CreatureDisplayID;
            Optional<uint32> VisualID;
            std::string Name1;
            std::string Name2;
            std::string Name3;
            std::string Name4;
            std::string Name5;
            std::string Name6;
            std::string Name7;
            Optional<uint32> Flags;
            Optional<uint32> Unk1;
            Optional<uint32> Unk2;
            Optional<uint32> Unk3;
            uint32 UnkInt1;
            uint32 UnkInt2;
            uint32 UnkInt3;

            std::vector<Visual> Visuals;
        };

        struct ProductStruct
        {
            uint32 ProductId;
            uint64 NormalPriceFixedPoint;
            uint64 CurrentPriceFixedPoint;
            std::vector<uint32> ProductIds;
            uint32 Unk1;
            uint32 Unk2;
            std::vector<uint32> UnkInts;
            uint32 Unk3;
            uint32 ChoiceType;
            Optional<DisplayInfo> Display;
        };

        struct ProductItem
        {
            uint32 ID;
            uint8 UnkByte;
            uint32 ItemID;
            uint32 Quantity;
            uint32 UnkInt1;
            uint32 UnkInt2;
            bool IsPet;
            Optional<uint32> PetResult;
            Optional<DisplayInfo> Display;
        };

        struct Product
        {
            uint32 ProductId;
            uint8 Type;
            uint32 Flags;
            uint32 Unk1;
            uint32 DisplayId;
            uint32 ItemId;
            uint32 Unk4;
            uint32 Unk5;
            uint32 Unk6;
            uint32 Unk7;
            uint32 Unk8;
            uint32 Unk9;
            std::string UnkString;
            bool UnkBit;
            Optional<uint32> UnkBits;
            std::vector<ProductItem> Items;
            Optional<DisplayInfo> Display;
        };

        struct ShopGroup
        {
            uint32 GroupId;
            uint32 IconFileDataID;
            uint8 DisplayType;
            uint32 Ordering;
            uint32 Unk;
            std::string Name;
            std::string Description;
        };

        struct ShopEntry
        {
            uint32 EntryID;
            uint32 GroupID;
            uint32 ProductID;
            uint32 Ordering;
            uint32 VasServiceType;
            uint8 StoreDeliveryType;
            Optional<DisplayInfo> Display;
        };

        class BattlePayGetProductListResponse final : public ServerPacket
        {
            public:
                BattlePayGetProductListResponse() : ServerPacket(SMSG_BATTLE_PAY_GET_PRODUCT_LIST_RESPONSE, 4000) { }

                WorldPacket const* Write() override;

                uint32 Result = 0;
                uint32 CurrencyID = 1;
                std::vector<ProductStruct> ProductStructs;
                std::vector<Product> Products;
                std::vector<ShopGroup> Groups;
                std::vector<ShopEntry> Entries;
        };
        
        class BattlePayGetProductList final : public ClientPacket
        {
        public:
            BattlePayGetProductList(WorldPacket&& packet) : ClientPacket(CMSG_BATTLE_PAY_GET_PRODUCT_LIST, std::move(packet)) { }

            void Read() override { }
        };

        class BattlePayGetPurchaseList final : public ClientPacket
        {
        public:
            BattlePayGetPurchaseList(WorldPacket&& packet) : ClientPacket(CMSG_BATTLE_PAY_GET_PURCHASE_LIST, std::move(packet)) { }

            void Read() override { }
        };

        class BattlePayRequestPriceInfo final : public ClientPacket
        {
        public:
            BattlePayRequestPriceInfo(WorldPacket&& packet) : ClientPacket(CMSG_BATTLE_PAY_REQUEST_PRICE_INFO, std::move(packet)) { }

            void Read() override { }
        };
    }
}
