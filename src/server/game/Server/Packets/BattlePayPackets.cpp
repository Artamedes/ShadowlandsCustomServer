#include "BattlePayPackets.h"

ByteBuffer& operator<<(ByteBuffer& data, WorldPackets::BattlePay::DisplayInfo const& info)
{
    data.FlushBits();

    data.WriteBit(info.CreatureDisplayID.has_value());
    data.WriteBit(info.VisualID.has_value());
    data.WriteBits(info.Name1.size(), 10);
    data.WriteBits(info.Name2.size(), 10);
    data.WriteBits(info.Name3.size(), 13);
    data.WriteBits(info.Name4.size(), 13);
    data.WriteBits(info.Name5.size(), 13);
    data.WriteBit(info.Flags.has_value());
    data.WriteBit(info.Unk1.has_value());
    data.WriteBit(info.Unk2.has_value());
    data.WriteBit(info.Unk3.has_value());
    data.WriteBits(info.Name6.size(), 13);
    data.WriteBits(info.Name7.size(), 13);

    data.FlushBits();

    data << (uint32)info.Visuals.size();
    data << info.UnkInt1;
    data << info.UnkInt2;
    data << info.UnkInt3;
    if (info.CreatureDisplayID.has_value())
        data << *info.CreatureDisplayID;
    if (info.VisualID.has_value())
        data << *info.VisualID;
    data.WriteString(info.Name1);
    data.WriteString(info.Name2);
    data.WriteString(info.Name3);
    data.WriteString(info.Name4);
    data.WriteString(info.Name5);
    if (info.Flags.has_value())
        data << *info.Flags;
    if (info.Unk1.has_value())
        data << *info.Unk1;
    if (info.Unk2.has_value())
        data << *info.Unk2;
    if (info.Unk3.has_value())
        data << *info.Unk3;
    data.WriteString(info.Name6);
    data.WriteString(info.Name7);

    for (auto const& visual : info.Visuals)
    {
        data.WriteBits(visual.Name.size(), 10);
        data.FlushBits();
        data << visual.DisplayId;
        data << visual.VisualId;
        data << visual.TransmogSetID;
        data.WriteString(visual.Name);
    }

    return data;
}


ByteBuffer& operator<<(ByteBuffer& data, WorldPackets::BattlePay::ProductStruct const& p)
{
    data << p.ProductId;
    data << p.NormalPriceFixedPoint;
    data << p.CurrentPriceFixedPoint;
    data << (uint32)p.ProductIds.size();
    data << p.Unk1;
    data << p.Unk2;
    data << (uint32)p.UnkInts.size();
    data << uint32(p.PurchaseEligibility);
    for (uint32 id : p.ProductIds)
        data << id;
    for (uint32 id : p.UnkInts)
        data << id;
    data.WriteBits(p.ChoiceType, 7);
    if (data.WriteBit(p.Display.has_value()))
        data << *p.Display;

    return data;
}

ByteBuffer& operator<<(ByteBuffer& data, WorldPackets::BattlePay::ProductItem const& p)
{
    data << p.ID;
    data << p.UnkByte;
    data << p.ItemID;
    data << p.Quantity;
    data << p.UnkInt1;
    data << p.UnkInt2;
    data.WriteBit(p.IsPet);
    data.WriteBit(p.PetResult.has_value());
    data.WriteBit(p.Display.has_value());
    if (p.PetResult.has_value())
        data.WriteBits(*p.PetResult, 4);
    if (p.Display.has_value())
        data << *p.Display;

    return data;
}

ByteBuffer& operator<<(ByteBuffer& data, WorldPackets::BattlePay::Product const& p)
{
    data << p.ProductId;
    data << p.Type;
    data << p.Item;
    data << p.Unk1;
    data << p.SpellId;
    data << p.CreatureEntry;
    data << p.Unk4;
    data << p.Flags;
    data << p.Unk6;
    data << p.TransmogSetId;
    data << p.Unk8; 
    data << p.Unk9;

    data.WriteBits(p.UnkString.length(), 8);
    data.WriteBit(p.AlreadyOwned);
    data.WriteBit(p.UnkBits.has_value());
    data.WriteBits(p.Items.size(), 7);
    data.WriteBit(p.Display.has_value());
    if (p.UnkBits.has_value())
        data.WriteBits(*p.UnkBits, 4);

    data.FlushBits();

    for (auto const& item : p.Items)
        data << item;

    data.WriteString(p.UnkString);

    if (p.Display.has_value())
        data << *p.Display;

    return data;
}

ByteBuffer& operator<<(ByteBuffer& data, WorldPackets::BattlePay::ShopGroup const& group)
{
    data << group.GroupId;
    data << group.IconFileDataID;
    data << group.DisplayType;
    data << group.Ordering;
    data << group.Unk;
    data.WriteBits(group.Name.length(), 8);
    data.WriteBits(!group.Description.empty() ? group.Description.length() + 1 : 0, 24); // for some reason + 1 is required here.
    data.FlushBits();
    data.WriteString(group.Name);
    if (!group.Description.empty())
        data << group.Description;

    return data;
}

ByteBuffer& operator<<(ByteBuffer& data, WorldPackets::BattlePay::ShopEntry const& entry)
{
    data << entry.EntryID;
    data << entry.GroupID;
    data << entry.ProductID;
    data << entry.Ordering;
    data << entry.VasServiceType;
    data << entry.StoreDeliveryType;
    data.FlushBits();
    if (data.WriteBit(entry.Display.has_value()))
    {
        data << *entry.Display;
    }
    return data;
}

WorldPacket const* WorldPackets::BattlePay::BattlePayGetProductListResponse::Write()
{
    _worldPacket << Result;
    _worldPacket << CurrencyID;
    _worldPacket << (uint32)ProductStructs.size();
    _worldPacket << (uint32)Products.size();
    _worldPacket << (uint32)Groups.size();
    _worldPacket << (uint32)Entries.size();

    for (auto const& p : ProductStructs)
        _worldPacket << p;
    for (auto const& p : Products)
        _worldPacket << p;
    for (auto const& p : Groups)
        _worldPacket << p;
    for (auto const& p : Entries)
        _worldPacket << p;

    return &_worldPacket;
}

void WorldPackets::BattlePay::BattlePayStartPurchase::Read()
{
    _worldPacket >> ClientToken;
    _worldPacket >> ProductID;
    _worldPacket >> TargetCharacter;

    uint32 strlen1 = _worldPacket.ReadBits(6);
    uint32 strlen2 = _worldPacket.ReadBits(12);
    WowSytem = _worldPacket.ReadString(strlen1);
    PublicKey = _worldPacket.ReadString(strlen2);
}

WorldPacket const* WorldPackets::BattlePay::BattlePayPurchaseUpdate::Write()
{
    _worldPacket << uint32(Purchases.size());

    for (auto const& purchase : Purchases)
    {
        _worldPacket << uint64(purchase.PurchaseID);
        _worldPacket << uint32(purchase.Status);
        _worldPacket << uint32(purchase.ResultCode);
        _worldPacket << uint32(purchase.ProductID);
        _worldPacket << uint64(purchase.CurrentDollars);
        _worldPacket << uint64(purchase.CurrentCents);
        _worldPacket << uint32(purchase.UnkInt32);
        _worldPacket.WriteBits(purchase.WalletName.size(), 8);
        _worldPacket.WriteString(purchase.WalletName);
    }

    return &_worldPacket;
}

WorldPacket const* WorldPackets::BattlePay::BattlePayConfirmPurchase::Write()
{
    _worldPacket << uint64(PurchaseID);
 //   _worldPacket << uint64(CurrentPriceFixedPoint);
    _worldPacket << uint32(ServerToken);

    return &_worldPacket;
}

void WorldPackets::BattlePay::BattlePayConfirmPurchaseResponse::Read()
{
    ConfirmPurchase = _worldPacket.ReadBit();
    _worldPacket.ResetBitPos();
    _worldPacket >> ServerToken;
    _worldPacket >> ClientCurrentPriceFixedPoint;
}

WorldPacket const* WorldPackets::BattlePay::BattlePayStartPurchaseResponse::Write()
{
    _worldPacket << uint64(PurchaseID);                         ///< Purchase ID
    _worldPacket << uint32(PurchaseResult);                     ///< Result
    _worldPacket << uint32(ClientToken);                        ///< Client Token
    return &_worldPacket;
}

void WorldPackets::BattlePay::BattlePayOpenCheckout::Read()
{
    _worldPacket >> UnkInt32;
}

void WorldPackets::BattlePay::ConsumableTokenCanVeteranBuy::Read()
{
    _worldPacket >> UnkInt32;
}

void WorldPackets::BattlePay::BattlePayRequestPriceInfo::Read()
{
    _worldPacket >> UnkInt1;
    _worldPacket >> UnkInt2;
}

WorldPacket const* WorldPackets::BattlePay::BattlePayPurchaseListResponse::Write()
{
    _worldPacket << uint32(Result);
    _worldPacket << uint32(Purchases.size());

    for (auto const& purchase : Purchases)
    {
        _worldPacket << uint64(purchase.PurchaseID);
        _worldPacket << uint32(purchase.Status);
        _worldPacket << uint32(purchase.ResultCode);
        _worldPacket << uint32(purchase.ProductID);
        _worldPacket << uint64(purchase.CurrentDollars);
        _worldPacket << uint64(purchase.CurrentCents);
        _worldPacket << uint32(purchase.UnkInt32);
        _worldPacket.WriteBits(purchase.WalletName.size(), 8);
        _worldPacket.WriteString(purchase.WalletName);
    }

    return &_worldPacket;
}

WorldPacket const* WorldPackets::BattlePay::BattlePayAckFailed::Write()
{
    _worldPacket << PurchaseID;
    _worldPacket << ServerToken;
    _worldPacket << Status;
    _worldPacket << Result;
    return &_worldPacket;
}

void WorldPackets::BattlePay::BattlePayAckFailedResponse::Read()
{
    _worldPacket >> ServerToken;
}
