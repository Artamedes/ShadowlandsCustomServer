#include "BattlePayPackets.h"
#include "BattlePay/BattlePayMgr.h"
#include "WorldSession.h"
#include "TokenPackets.h"
#include "GameTime.h"
#include "Chat.h"
#include "Player.h"
#include "CollectionMgr.h"
#include "Mail.h"
#include "Item.h"

using namespace WorldPackets::BattlePay;

const float g_CurrencyPrecision = 10000.0f;

// char __fastcall sub_25409A0(int a1)
// {
//     char result; // al
// 
//     switch (a1)
//     {
//         case 0:
//             result = 0;
//             break;
//         case 1:
//             result = 9;
//             break;
//         case 2:
//             result = 2;
//             break;
//         case 12:
//             result = 3;
//             break;
//         case 13:
//         case 14:
//             result = 4;
//             break;
//         case 25:
//             result = 1;
//             break;
//         case 28:
//         case 29:
//             result = 5;
//             break;
//         case 34:
//             result = 8;
//             break;
//         case 46:
//             result = 10;
//             break;
//         case 47:
//             result = 11;
//             break;
//         case 48:
//             result = 12;
//             break;
//         case 66:
//             result = 13;
//             break;
//         default:
//             result = 6;
//             break;
//     }
//     return result;
// }
/// Client error enum
/// See Blizzard_StoreUISecure.lua
/// Last update : 6.2.3 20779
enum Error
{
    InvalidPaymentMethod       = 25,
    PaymentFailed              = 2,
    WrongCurrency              = 12,
    BattlepayDisabled          = 13,    ///< Also 14
    InsufficientBalance        = 28,    ///< Also 29
    Other                      = 3,
    //AlreadyOwned               = ,
    ParentalControlsNoPurchase = 34,
    Denied                     = 1,
    ConsumableTokenOwned       = 46,
    TooManyTokens              = 47,
    Ok                         = 0
    /// ItemUnavailable
};

// TODO: Check accuracy
enum BattlepayDisplayFlag : uint32
{
    CardDoesNotShowModel = 1,
    CardAlwaysShowTexture = 2,
    HiddenPrice = 4,
    UseHorizontalLayoutForFullCard = 8,
    Deprecated1 = 16,
    Deprecated2 = 32,
    UseSquareIconBorder = 64,
    HideWhenOWned = 128,
    RafReward = 256,
    ShowFancyToast = 512,
};

enum PurchaseEligibilityFlag : uint32
{
    PartiallyOwned = 1,
    Owned = 2,
    ExpansionTooLow = 4,
    ExpansionTooHigh = 8,
    MissingRequiredDeliverable = 16,
};

/// Update status of SMSG_BATTLE_PAY_PURCHASE_UPDATE
/// see @Battlepay::PacketFactory::SendPurchaseUpdate
namespace UpdateStatus
{
    enum
    {
        Loading = 2,
        Ready = 3,
        Finish = 6
    };
}

void WorldSession::SendProductList()
{
    auto stmt = WebDatabase.GetPreparedStatement(WEB_SEL_DP);
    stmt->setUInt32(0, GetAccountId());
    _queryProcessor.AddCallback(WebDatabase.AsyncQuery(stmt)
        .WithPreparedCallback([this](PreparedQueryResult result)
    {
        uint32 bal = 0;
        if (result)
        {
            auto fields = result->Fetch();
            bal = fields[0].GetUInt32();
        }
        SendProductList(bal);
    }));
}

void WorldSession::SendProductList(uint32 balance)
{
    BattlePayGetProductListResponse packet;

    auto const& groups = sBattlePayMgr->GetGroups();
    packet.Groups.reserve(groups.size());
    for (auto const& group : groups)
    {
        packet.Groups.emplace_back(group.second);
    }

    auto const& products = sBattlePayMgr->GetProducts();
    packet.Products.reserve(products.size());
    for (auto const& product : products)
    {
        Product p;
        p.ProductId = product.second.ProductId;
        p.Type = product.second.Type;
        p.Item = product.second.Item;
        p.Unk1 = product.second.Unk1;
        p.SpellId = product.second.SpellId;
        p.CreatureEntry = product.second.CreatureEntry;
        p.Unk4 = product.second.Unk4;
        p.Flags = product.second.Flags;
        p.Unk6 = product.second.Unk6;
        p.TransmogSetId = product.second.TransmogSetId;
        p.Unk8 = product.second.Unk8;
        p.Unk9 = product.second.Unk9;
        p.UnkString = product.second.UnkString;
        p.AlreadyOwned = product.second.AlreadyOwned;
        p.UnkBits = product.second.UnkBits;
        p.Items = product.second.Items;
        p.Display = product.second.Display;

        bool alreadyOwns = false;
        if (p.Item > 0)
        {
            if (GetCollectionMgr()->HasToy(p.Item))
                alreadyOwns = true;
        }

        if (p.SpellId > 0)
        {
            if (GetCollectionMgr()->HasMount(p.SpellId))
                alreadyOwns = true;
        }

        if (p.TransmogSetId > 0)
        {
            if (GetCollectionMgr()->IsSetCompleted(p.TransmogSetId))
                alreadyOwns = true;
        }

        p.AlreadyOwned = alreadyOwns;
        packet.Products.emplace_back(p);
    }

    auto const& productStructs = sBattlePayMgr->GetProductStruct();
    packet.ProductStructs.reserve(productStructs.size());
    for (auto const& productStruct : productStructs)
    {
        ProductStruct pStruct;

        pStruct.ProductId = productStruct.second.ProductId;
        pStruct.NormalPriceFixedPoint = productStruct.second.NormalPriceFixedPoint;
        pStruct.CurrentPriceFixedPoint = productStruct.second.CurrentPriceFixedPoint;
        pStruct.Unk1 = productStruct.second.Unk1;
        pStruct.Unk2 = productStruct.second.Unk2;
        pStruct.PurchaseEligibility = productStruct.second.PurchaseEligibility & ~(PartiallyOwned | Owned);
        pStruct.ChoiceType = productStruct.second.ChoiceType;
        pStruct.ProductIds = productStruct.second.ProductIds;
        pStruct.UnkInts = productStruct.second.UnkInts;

        bool partiallyOwns = false;
        bool fullyOwns = false;

        for (auto productId : pStruct.ProductIds)
        {
            if (auto product = sBattlePayMgr->GetProductById(productId))
            {
                bool alreadyOwns = false;
                if (product->Item > 0)
                {
                    if (GetCollectionMgr()->HasToy(product->Item))
                        alreadyOwns = true;
                }

                if (product->SpellId > 0)
                {
                    if (GetCollectionMgr()->HasMount(product->SpellId))
                        alreadyOwns = true;
                }

                if (product->TransmogSetId > 0)
                {
                    if (GetCollectionMgr()->IsSetCompleted(product->TransmogSetId))
                        alreadyOwns = true;
                }

                if (!alreadyOwns)
                {
                    if (fullyOwns)
                    {
                        fullyOwns = false;
                        partiallyOwns = true;
                    }
                }
                else
                {
                    if (!fullyOwns)
                        fullyOwns = true;
                    else
                        partiallyOwns = true;
                }
            }
        }

        if (partiallyOwns)
            pStruct.PurchaseEligibility |= PartiallyOwned;
        if (fullyOwns)
            pStruct.PurchaseEligibility |= Owned;

        // Internal Balance
        if (pStruct.ProductId == 7 && productStruct.second.Display.has_value())
        {
            DisplayInfo display;
            display.CreatureDisplayID = productStruct.second.Display.value().CreatureDisplayID;
            display.VisualID = productStruct.second.Display.value().VisualID;
            display.Name1 = "Balance: $" + std::to_string(balance);
            display.Name2 = productStruct.second.Display.value().Name2;
            display.Name3 = productStruct.second.Display.value().Name3;
            display.Name4 = productStruct.second.Display.value().Name4;
            display.Name5 = productStruct.second.Display.value().Name5;
            display.Name6 = productStruct.second.Display.value().Name6;
            display.Name7 = productStruct.second.Display.value().Name7;
            display.Flags = productStruct.second.Display.value().Flags;
            display.Unk1 = productStruct.second.Display.value().Unk1;
            display.Unk2 = productStruct.second.Display.value().Unk2;
            display.Unk3 = productStruct.second.Display.value().Unk3;
            display.UnkInt1 = productStruct.second.Display.value().UnkInt1;
            display.UnkInt2 = productStruct.second.Display.value().UnkInt2;
            display.UnkInt3 = productStruct.second.Display.value().UnkInt3;
            display.Visuals = productStruct.second.Display.value().Visuals;

            pStruct.Display = display;
            pStruct.PurchaseEligibility |= (PartiallyOwned | Owned);
        }
        else
            pStruct.Display = productStruct.second.Display;

        packet.ProductStructs.emplace_back(pStruct);
    }

    auto const& entries = sBattlePayMgr->GetEntries();
    packet.Entries.reserve(entries.size());
    for (auto const& entry : entries)
    {
        ShopEntry sEntry;

        sEntry.EntryID           = entry.second.EntryID;
        sEntry.GroupID           = entry.second.GroupID;
        sEntry.ProductID         = entry.second.ProductID;
        sEntry.Ordering          = entry.second.Ordering;
        sEntry.VasServiceType    = entry.second.VasServiceType;
        sEntry.StoreDeliveryType = entry.second.StoreDeliveryType;
        sEntry.Display           = entry.second.Display;

        // Internal Balance
        if (sEntry.ProductID == 7 && sEntry.Display.has_value())
        {
            sEntry.Display.value().Name1 = "Balance: $" + std::to_string(balance);
        }

        packet.Entries.emplace_back(sEntry);
    }

    SendPacket(packet.Write());
}

void WorldSession::HandleBattlePayGetProductList(WorldPackets::BattlePay::BattlePayGetProductList& /*recvPacket*/)
{
    SendProductList();
}

void WorldSession::HandleBattlePayGetPurchaseList(WorldPackets::BattlePay::BattlePayGetPurchaseList& recvPacket)
{
    /// @TODO!
    BattlePayPurchaseListResponse packet;
    //auto purchaseId = urand(0, 0xFFFF);
    //packet.Purchases.resize(1);
    //packet.Purchases[0].PurchaseID = purchaseId;
    //packet.Purchases[0].Status     = UpdateStatus::Ready;
    //packet.Purchases[0].ResultCode = Error::Ok;
    //packet.Purchases[0].ProductID  = 717;
    //packet.Purchases[0].CurrentDollars  = 50000000;
    //packet.Purchases[0].CurrentCents    = 50000000;
    //packet.Purchases[0].UnkInt32   = (uint32)GameTime::GetGameTime();
    //packet.Purchases[0].WalletName = "Account Balance";
    SendPacket(packet.Write());
}

void WorldSession::HandleBattlePayRequestPriceInfo(WorldPackets::BattlePay::BattlePayRequestPriceInfo& recvPacket)
{
    /// @TODO!
    WorldPackets::Token::CommerceTokenGetMarketPriceResponse response;

    response.CurrentMarketPrice = 1572130000;
    response.UnkInt = 0;
    response.Result = TOKEN_RESULT_SUCCESS;
    response.AuctionDuration = 14400;

    SendPacket(response.Write());
}

void WorldSession::HandleBattlePayStartPurchase(WorldPackets::BattlePay::BattlePayStartPurchase& startPurchase)
{
    TC_LOG_TRACE("network.opcode", "HandleBattlePayStartPurchase ClientToken: {} ProductId: {} {}", startPurchase.ClientToken, startPurchase.ProductID, startPurchase.TargetCharacter.ToString());

    auto productId = startPurchase.ProductID;
    auto clientToken = startPurchase.ClientToken;
    auto targetCharacter = startPurchase.TargetCharacter;
    auto system = startPurchase.WowSytem;
    auto publicKey = startPurchase.PublicKey;
    auto productInfo = sBattlePayMgr->GetProductInfoById(productId);

    // Remove purchase
    if (_battlePayPurchase)
    {
        sBattlePayMgr->RemovePurchase(_battlePayPurchase);
        _battlePayPurchase = nullptr;
    }

    auto purchase = sBattlePayMgr->CreatePurchase();
    purchase->ProductID = productId;
    purchase->AccountID = GetAccountId();
    purchase->CharacterGuid = targetCharacter;
    purchase->ClientToken = clientToken;
    purchase->System = system;
    purchase->PublicKey = publicKey;

    // set current purchase for next packet client will send.
    _battlePayPurchase = purchase;

    BattlePayStartPurchaseResponse packet;
    packet.PurchaseID = purchase->PurchaseID;
    packet.PurchaseResult = Error::Ok;
    packet.ClientToken = clientToken;
    SendPacket(packet.Write());

    if (!productInfo)
    {
        BattlePayAckFailed ackFailed;
        ackFailed.PurchaseID = purchase->PurchaseID;
        ackFailed.ServerToken = purchase->ServerToken;
        ackFailed.Status = 12;
        ackFailed.Result = Error::Denied;
        SendPacket(ackFailed.Write());
        return;
    }

    // Check if we already own this product.

    for (auto productId : productInfo->ProductIds)
    {
        if (auto product = sBattlePayMgr->GetProductById(productId))
        {
            bool alreadyOwns = false;
            if (product->Item > 0)
            {
                if (GetCollectionMgr()->HasToy(product->Item))
                    alreadyOwns = true;
            }

            if (product->SpellId > 0)
            {
                if (GetCollectionMgr()->HasMount(product->SpellId))
                    alreadyOwns = true;
            }

            if (product->TransmogSetId > 0)
            {
                if (GetCollectionMgr()->IsSetCompleted(product->TransmogSetId))
                    alreadyOwns = true;
            }

            if (alreadyOwns)
            {
                BattlePayAckFailed ackFailed;
                ackFailed.PurchaseID = purchase->PurchaseID;
                ackFailed.ServerToken = purchase->ServerToken;
                ackFailed.Status = 12;
                ackFailed.Result = Error::Denied;
                SendPacket(ackFailed.Write());
                return;
            }
        }
    }

    // Check balance for product
    auto stmt = WebDatabase.GetPreparedStatement(WEB_SEL_DP);
    stmt->setUInt32(0, GetAccountId());
    _queryProcessor.AddCallback(WebDatabase.AsyncQuery(stmt)
        .WithPreparedCallback([this, productInfo, productId, clientToken, targetCharacter, system, publicKey, purchase](PreparedQueryResult result)
    {
        // No balance!
        if (!result)
        {
            BattlePayAckFailed ackFailed;
            ackFailed.PurchaseID = purchase->PurchaseID;
            ackFailed.ServerToken = purchase->ServerToken;
            ackFailed.Status = 12;
            ackFailed.Result = Error::InvalidPaymentMethod;
            SendPacket(ackFailed.Write());
            return;
        }

        Field* fields = result->Fetch();
        uint32 currDP = fields[0].GetUInt32();

        // Not enough points!
        if (currDP < (productInfo->CurrentPriceFixedPoint / 10000))
        {
            BattlePayAckFailed ackFailed;
            ackFailed.PurchaseID = purchase->PurchaseID;
            ackFailed.ServerToken = purchase->ServerToken;
            ackFailed.Status = 12;
            ackFailed.Result = Error::InsufficientBalance;
            SendPacket(ackFailed.Write());
            return;
        }


        // BattlePayStartPurchaseResponse packet;
        // packet.PurchaseID = purchase->PurchaseID;
        // packet.PurchaseResult = Error::Ok;
        // packet.ClientToken = clientToken;
        // SendPacket(packet.Write());

        BattlePayStartPurchaseResponse packet;
        packet.PurchaseID = purchase->PurchaseID;
        packet.PurchaseResult = Error::Ok;
        packet.ClientToken = clientToken;
        SendPacket(packet.Write());

        // All good send packets to let client buy
        BattlePayPurchaseUpdate packet2;
        packet2.Purchases.resize(1);
        packet2.Purchases[0].PurchaseID = purchase->PurchaseID;
        packet2.Purchases[0].Status = 9; // TODO: Find what 9 is without client dont send packet back
        packet2.Purchases[0].ResultCode = Error::Ok;
        packet2.Purchases[0].ProductID = productId;
        packet2.Purchases[0].CurrentDollars = 0;
        packet2.Purchases[0].CurrentCents = 0;
        packet2.Purchases[0].UnkInt32 = (uint32)GameTime::GetGameTime();
        packet2.Purchases[0].WalletName = "";
        SendPacket(packet2.Write());

        BattlePayConfirmPurchase packet3;
        packet3.CurrentPriceFixedPoint = 0;
        packet3.PurchaseID = purchase->PurchaseID;
        packet3.ServerToken = purchase->ServerToken;
        SendPacket(packet3.Write());

        ChatHandler(this).SendSysMessage("|cff1DCDE5[BattlePay]: If you get an error please try again!");
    }));

    // SMSG_BATTLE_PAY_START_CHECKOUT


    // WorldPacket data(SMSG_BATTLE_PAY_START_CHECKOUT);
    // data << int32(301384);
    // data << int32(1);
    // data << uint64(103761917);
    // std::string str1 = "iC4e08ya-gVDIotqheflOleDQTb9OBqxaPNy4vKj_Hs=";
    // std::string str2 = "AwEAAQATmeIAAAByHg==";
    // data.WriteBits(44, 6);
    // data.WriteBits(20, 7);
    // data.WriteString(str1);
    // data.WriteString(str2);
    // SendPacket(&data);
}

void WorldSession::HandleBattlePayConfirmPurchaseResponse(WorldPackets::BattlePay::BattlePayConfirmPurchaseResponse& confirmPurchase)
{
    if (!_battlePayPurchase)
        return;

    TC_LOG_TRACE("network.opcode", "HandleBattlePayConfirmPurchaseResponse ClientCurrentPriceFixedPoint: {} ConfirmPurchase: {} ServerToken: {}", confirmPurchase.ClientCurrentPriceFixedPoint, confirmPurchase.ConfirmPurchase ? 1 : 0, confirmPurchase.ServerToken);

    if (!confirmPurchase.ConfirmPurchase)
    {
        sBattlePayMgr->RemovePurchase(_battlePayPurchase);
        _battlePayPurchase = nullptr;
        return;
    }
    auto productInfo = sBattlePayMgr->GetProductInfoById(_battlePayPurchase->ProductID);
    if (!productInfo)
    {
        BattlePayAckFailed ackFailed;
        ackFailed.PurchaseID = _battlePayPurchase->PurchaseID;
        ackFailed.ServerToken = _battlePayPurchase->ServerToken;
        ackFailed.Status = 12;
        ackFailed.Result = Error::Denied;
        SendPacket(ackFailed.Write());
        sBattlePayMgr->RemovePurchase(_battlePayPurchase);
        _battlePayPurchase = nullptr;
        return;
    }

    // Check balance for product
    auto stmt = WebDatabase.GetPreparedStatement(WEB_SEL_DP);
    stmt->setUInt32(0, GetAccountId());
    _queryProcessor.AddCallback(WebDatabase.AsyncQuery(stmt)
        .WithPreparedCallback([this, productInfo](PreparedQueryResult result)
    {
        // No balance!
        if (!result)
        {
            BattlePayAckFailed ackFailed;
            ackFailed.PurchaseID = _battlePayPurchase->PurchaseID;
            ackFailed.ServerToken = _battlePayPurchase->ServerToken;
            ackFailed.Status = 12;
            ackFailed.Result = Error::InvalidPaymentMethod;
            SendPacket(ackFailed.Write());
            return;
        }

        Field* fields = result->Fetch();
        uint32 currDP = fields[0].GetUInt32();

        // Not enough points!
        uint32 cost = productInfo->CurrentPriceFixedPoint / 10000;
        if (currDP < cost)
        {
            BattlePayAckFailed ackFailed;
            ackFailed.PurchaseID = _battlePayPurchase->PurchaseID;
            ackFailed.ServerToken = _battlePayPurchase->ServerToken;
            ackFailed.Status = 12;
            ackFailed.Result = Error::InsufficientBalance;
            SendPacket(ackFailed.Write());
            return;
        }

        // Remove the DP
        auto stmt = WebDatabase.GetPreparedStatement(WEB_UPD_DP);
        stmt->setUInt32(0, currDP - cost);
        stmt->setUInt32(1, GetAccountId());
        WebDatabase.Execute(stmt);

        for (auto productId : productInfo->ProductIds)
        {
            if (auto product = sBattlePayMgr->GetProductById(productId))
            {
                if (product->Item)
                {
                    if (product->Type == 14)
                        GetCollectionMgr()->AddToy(product->Item, false, false);
                    else
                    {
                        // Add Item
                        if (_player)
                        {
                            if (!_player->AddItem(product->Item, 1))
                                _player->SendItemRetrievalMail(product->Item, 1, ItemContext::NONE);
                        }
                        else
                        {
                            MailSender sender(MAIL_CREATURE, UI64LIT(34337) /* The Postmaster */);
                            MailDraft draft("BattlePay", "Your shop purchase.");
                            CharacterDatabaseTransaction trans = CharacterDatabase.BeginTransaction();

                            if (Item* item = Item::CreateItem(product->Item, 1, ItemContext::NONE, nullptr))
                            {
                                item->SaveToDB(trans);
                                draft.AddItem(item);
                            }

                            draft.SendMailTo(trans, MailReceiver(nullptr, _battlePayPurchase->CharacterGuid), sender);
                            CharacterDatabase.CommitTransaction(trans);
                        }
                    }
                }

                if (product->SpellId)
                {
                    GetCollectionMgr()->AddMount(product->SpellId, MountStatusFlags::MOUNT_STATUS_NONE, false, false);
                }

                if (product->TransmogSetId)
                {
                    GetCollectionMgr()->AddTransmogSet(product->TransmogSetId);
                }
            }
        }

        BattlePayPurchaseUpdate packet2;
        packet2.Purchases.resize(1);
        packet2.Purchases[0].PurchaseID = _battlePayPurchase->PurchaseID;
        packet2.Purchases[0].Status = 5;
        packet2.Purchases[0].ResultCode = Error::Ok;
        packet2.Purchases[0].ProductID = _battlePayPurchase->ProductID;
        packet2.Purchases[0].CurrentDollars = 0;
        packet2.Purchases[0].CurrentCents = 0;
        packet2.Purchases[0].UnkInt32 = (uint32)GameTime::GetGameTime();
        packet2.Purchases[0].WalletName = "";
        SendPacket(packet2.Write());

        /// @TODO: Send Delivery Frame

        // Send List
        SendProductList(currDP - cost);
    }));
}

void WorldSession::HandleBattlePayOpenCheckout(WorldPackets::BattlePay::BattlePayOpenCheckout& openCheckout)
{
    //WorldPacket data(SMSG_GENERATE_SSO_TOKEN_RESPONSE);
    //data << int32(1);
    //data << int32(0);
    //data << uint64(1651954049);
    //data << uint64(1651968449);
    //std::string str3 = "US-9de2b56eff4572d1a0c3985d1f7eedc3-75539450";
    //data.WriteBits(str3.size(), 8);
    //data.WriteString(str3);
    //SendPacket(&data);
}

void WorldSession::HandleConsumableTokenCanVeteranBuy(WorldPackets::BattlePay::ConsumableTokenCanVeteranBuy& consumable)
{
    WorldPacket data(SMSG_CONSUMABLE_TOKEN_CAN_VETERAN_BUY_RESPONSE, 10);
    data << uint32(0);
    data << uint32(0);
    data << uint32(0);
    data << uint32(1);
    SendPacket(&data);

}

void WorldSession::HandleBattlePayAckFailedResponse(WorldPackets::BattlePay::BattlePayAckFailedResponse& response)
{
    if (!_battlePayPurchase)
        return;

    // BattlePayPurchaseUpdate packet2;
    // packet2.Purchases.resize(1);
    // packet2.Purchases[0].PurchaseID = _battlePayPurchase->PurchaseID;
    // packet2.Purchases[0].Status = 12;
    // packet2.Purchases[0].ResultCode = 63;
    // packet2.Purchases[0].ProductID = _battlePayPurchase->ProductID;
    // packet2.Purchases[0].CurrentDollars = 0;
    // packet2.Purchases[0].CurrentCents = 0;
    // packet2.Purchases[0].UnkInt32 = (uint32)GameTime::GetGameTime();
    // packet2.Purchases[0].WalletName = "";
    // SendPacket(packet2.Write());

    BattlePayConfirmPurchase packet3;
    packet3.CurrentPriceFixedPoint = 0;
    packet3.PurchaseID = _battlePayPurchase->PurchaseID;
    packet3.ServerToken = _battlePayPurchase->ServerToken;
    SendPacket(packet3.Write());

    sBattlePayMgr->RemovePurchase(_battlePayPurchase);
    _battlePayPurchase = nullptr;
}
