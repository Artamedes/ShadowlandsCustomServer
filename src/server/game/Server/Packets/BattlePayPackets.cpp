#include "BattlePayPackets.h"

ByteBuffer& operator<<(ByteBuffer& data, WorldPackets::BattlePay::DisplayInfo const& info)
{
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
        data << visual.Unk;
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
    data << p.Unk3;
    for (uint32 id : p.ProductIds)
        data << id;
    for (uint32 id : p.UnkInts)
        data << id;
    data.WriteBits(p.ChoiceType, 7);
    bool wrote = data.WriteBit(p.Display.has_value());
    data.FlushBits();
    if (wrote)
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
    data.FlushBits();
    if (p.Display.has_value())
        data << *p.Display;

    return data;
}

ByteBuffer& operator<<(ByteBuffer& data, WorldPackets::BattlePay::Product const& p)
{
    data << p.ProductId;
    data << p.Type;
    data << p.Flags;
    data << p.Unk1;
    data << p.DisplayId;
    data << p.ItemId;
    data << p.Unk4;
    data << p.Unk5;
    data << p.Unk6;
    data << p.Unk7;
    data << p.Unk8;
    data << p.Unk9;
    data.WriteBits(p.UnkString.size(), 8);
    data.WriteBit(p.UnkBit);
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
    data.WriteBits(group.Name.size(), 8);
    data.WriteBits(group.Description.size() + 1, 24);
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
    data.WriteBit(entry.Display.has_value());
    if (entry.Display.has_value())
    {
        data.FlushBits();
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
