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
            uint32 TransmogSetID;
        };

        struct DisplayInfo
        {
            Optional<uint32>    CreatureDisplayID;
            Optional<uint32>    VisualID;
            std::string         Name1;
            std::string         Name2;
            std::string         Name3;
            std::string         Name4;
            std::string         Name5;
            std::string         Name6;
            std::string         Name7;
            Optional<uint32>    Flags;
            Optional<uint32>    Unk1;
            Optional<uint32>    Unk2;
            Optional<uint32>    Unk3;
            uint32              UnkInt1;
            uint32              UnkInt2;
            uint32              UnkInt3;
            std::vector<Visual> Visuals;
        };

        struct ProductStruct
        {
            uint32                ProductId                 = 0;
            uint64                NormalPriceFixedPoint     = 0;
            uint64                CurrentPriceFixedPoint    = 0;
            uint32                Unk1                      = 0;
            uint32                Unk2                      = 0;
            uint32                PurchaseEligibility       = 0;
            uint32                ChoiceType                = 0;
            std::vector<uint32>   ProductIds;
            std::vector<uint32>   UnkInts;
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
            uint32                   ProductId          = 0;
            uint8                    Type               = 0;
            uint32                   Item               = 0;
            uint32                   Unk1               = 0;
            uint32                   SpellId            = 0;
            uint32                   CreatureEntry      = 0;
            uint32                   Unk4               = 0;
            uint32                   Flags              = 0;
            uint32                   Unk6               = 0;
            uint32                   TransmogSetId      = 0;
            uint32                   Unk8               = 0;
            uint32                   Unk9               = 0;
            std::string              UnkString;
            bool                     AlreadyOwned       = false;
            Optional<uint32>         UnkBits               ;
            std::vector<ProductItem> Items                 ;
            Optional<DisplayInfo>    Display               ;
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
            uint32                EntryID;
            uint32                GroupID;
            uint32                ProductID;
            uint32                Ordering;
            uint32                VasServiceType;
            uint8                 StoreDeliveryType;
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

            void Read() override;

            uint32 UnkInt1 = 0;
            uint32 UnkInt2 = 0;
        };

        class BattlePayStartPurchase final : public ClientPacket
        {
        public:
            BattlePayStartPurchase(WorldPacket&& packet) : ClientPacket(CMSG_BATTLE_PAY_START_PURCHASE, std::move(packet)) { }

            void Read() override;

            uint32 ClientToken = 0;
            uint32 ProductID = 0;
            ObjectGuid TargetCharacter;
            std::string WowSytem;
            std::string PublicKey;
        };

        /// function StoreConfirmationFrame_Update(self)
        struct JamBattlePayPurchase
        {
            uint64      PurchaseID       = 0;         ///< Offset 0x0000 Type _MJVTBL_UINT64
            uint32      Status           = 0;             ///< Offset 0x0008 Type _MJVTBL_UINT32
            uint32      ResultCode       = 0;         ///< Offset 0x000C Type _MJVTBL_UINT32
            uint32      ProductID        = 0;          ///< Offset 0x0010 Type _MJVTBL_UINT32
            uint32      CurrentDollars   = 0;
            uint32      CurrentCents     = 0;
            uint32      UnkInt32         = 0;
            std::string WalletName;         ///< Offset 0x0014 Type _MJVTBL_STRING
        };

        class BattlePayPurchaseUpdate final : public ServerPacket
        {
        public:
            BattlePayPurchaseUpdate() : ServerPacket(SMSG_BATTLE_PAY_PURCHASE_UPDATE, 4000) { }

            WorldPacket const* Write() override;

            std::vector<JamBattlePayPurchase> Purchases;                                ///< Offset 0x0000 Type MakeMJVTblForArrayOfStruct<JamBattlePayPurchase>::MJVTBL
        };


        class BattlePayPurchaseListResponse final : public ServerPacket
        {
        public:
            BattlePayPurchaseListResponse() : ServerPacket(SMSG_BATTLE_PAY_GET_PURCHASE_LIST_RESPONSE, 4000) { }

            WorldPacket const* Write() override;

            uint32 Result = 0;
            std::vector<JamBattlePayPurchase> Purchases;                                ///< Offset 0x0000 Type MakeMJVTblForArrayOfStruct<JamBattlePayPurchase>::MJVTBL
        };


        class BattlePayConfirmPurchase final : public ServerPacket
        {
        public:
            BattlePayConfirmPurchase() : ServerPacket(SMSG_BATTLE_PAY_CONFIRM_PURCHASE, 4000) { }

            WorldPacket const* Write() override;

            uint64 CurrentPriceFixedPoint = 0;        ///< Offset 0x0000 Type _MJVTBL_UINT64
            uint64 PurchaseID = 0;                    ///< Offset 0x0008 Type _MJVTBL_UINT64
            uint32 ServerToken = 0;                   ///< Offset 0x0010 Type _MJVTBL_UINT32
        };

        class BattlePayStartPurchaseResponse final : public ServerPacket
        {
        public:
            BattlePayStartPurchaseResponse() : ServerPacket(SMSG_BATTLE_PAY_START_PURCHASE_RESPONSE, 8+4+4) { }

            WorldPacket const* Write() override;

            uint64 PurchaseID = 0;            ///< Offset 0x0000 Type _MJVTBL_UINT64
            uint32 PurchaseResult = 0;        ///< Offset 0x0008 Type _MJVTBL_UINT32
            uint32 ClientToken = 0;           ///< Offset 0x000C Type _MJVTBL_UINT32
        };

        class BattlePayConfirmPurchaseResponse final : public ClientPacket
        {
        public:
            BattlePayConfirmPurchaseResponse(WorldPacket&& packet) : ClientPacket(CMSG_BATTLE_PAY_CONFIRM_PURCHASE_RESPONSE, std::move(packet)) { }

            void Read() override;

            uint64 ClientCurrentPriceFixedPoint = 0; ///< Offset 0x0000 Type _MJVTBL_UINT64
            bool   ConfirmPurchase = false;          ///< Offset 0x0008 Type _MJVTBL_BOOL
            uint32 ServerToken = 0;                  ///< Offset 0x000C Type _MJVTBL_UINT32
        };

        class BattlePayOpenCheckout final : public ClientPacket
        {
        public:
            BattlePayOpenCheckout(WorldPacket&& packet) : ClientPacket(CMSG_BATTLE_PAY_OPEN_CHECKOUT, std::move(packet)) { }

            void Read() override;

            uint32 UnkInt32 = 0;
        };

        class ConsumableTokenCanVeteranBuy final : public ClientPacket
        {
        public:
            ConsumableTokenCanVeteranBuy(WorldPacket&& packet) : ClientPacket(CMSG_CONSUMABLE_TOKEN_CAN_VETERAN_BUY, std::move(packet)) { }

            void Read() override;

            uint32 UnkInt32 = 0;
        };

        class BattlePayAckFailed final : public ServerPacket
        {
        public:
            BattlePayAckFailed() : ServerPacket(SMSG_BATTLE_PAY_ACK_FAILED, 8 + 4 + 4) { }

            WorldPacket const* Write() override;

            uint64 PurchaseID = 0;         ///< Offset 0x0000 Type _MJVTBL_UINT64
            uint32 ServerToken = 0;
            uint32 Status = 0;             ///< Offset 0x000C Type _MJVTBL_UINT32
            uint32 Result = 0;              ///< Offset 0x0010 Type _MJVTBL_UINT32
        };

        class BattlePayAckFailedResponse final : public ClientPacket
        {
        public:
            BattlePayAckFailedResponse(WorldPacket&& packet) : ClientPacket(CMSG_BATTLE_PAY_ACK_FAILED_RESPONSE, std::move(packet)) { }

            void Read() override;

            uint32 ServerToken = 0;
        };

    }
}
