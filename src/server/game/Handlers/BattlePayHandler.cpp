#include "BattlePayPackets.h"
#include "BattlePay/BattlePayMgr.h"
#include "WorldSession.h"
#include "TokenPackets.h"

void WorldSession::HandleBattlePayGetProductList(WorldPackets::BattlePay::BattlePayGetProductList& recvPacket)
{
    {
    }
    {
    }
    sBattlePayMgr->SendProductListResponseToSession(this);

    WorldPacket data(SMSG_BATTLE_PAY_VALIDATE_PURCHASE_RESPONSE, 4 + 4 + 8 + 8 + 1);
    data << uint32(4);
    data << uint32(699);
    data << uint64(200000);
    data << uint64(200000);
    data.WriteBits(0, 7);
    SendPacket(&data);
}

void WorldSession::HandleBattlePayGetPurchaseList(WorldPackets::BattlePay::BattlePayGetPurchaseList& recvPacket)
{
    WorldPacket data(SMSG_BATTLE_PAY_GET_PURCHASE_LIST_RESPONSE, 4 + 4 + 8 + 8 + 1);
    data << uint32(0);
    data.WriteBits(0, 11);
    SendPacket(&data);

    WorldPackets::Token::CommerceTokenGetMarketPriceResponse response;

    /// @todo: 6.x fix implementation
    response.CurrentMarketPrice = 300000000;
    response.UnkInt = 0;
    response.Result = TOKEN_RESULT_SUCCESS;
    //packet.ReadUInt32("UnkInt32");

    SendPacket(response.Write());
}

void WorldSession::HandleBattlePayRequestPriceInfo(WorldPackets::BattlePay::BattlePayRequestPriceInfo& recvPacket)
{
    WorldPackets::Token::CommerceTokenGetMarketPriceResponse response;

    /// @todo: 6.x fix implementation
    response.CurrentMarketPrice = 300000000;
    response.UnkInt = 0;
    response.Result = TOKEN_RESULT_SUCCESS;
    //packet.ReadUInt32("UnkInt32");

    SendPacket(response.Write());

    WorldPacket data(SMSG_CONSUMABLE_TOKEN_CAN_VETERAN_BUY_RESPONSE, 10);
    data << uint32(0);
    SendPacket(&data);
}
