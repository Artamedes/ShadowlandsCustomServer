#include "BattlePayMgr.h"
#include "DatabaseEnv.h"
#include "BattlePayPackets.h"
#include "Util.h"
#include "WorldSession.h"
#include "StringConvert.h"

void BattlePayMgr::LoadFromDB()
{
    ProductStructs.clear();
    Products.clear();
    Groups.clear();
    Entries.clear();

    std::unordered_map<uint32, WorldPackets::BattlePay::DisplayInfo> displayInfos;

    auto result = LoginDatabase.Query("SELECT ID, CreatureDisplayID, VisualID, Name1, Name2, Name3, Name4, Name5, Name6, Name7, Flags, Unk1, Unk2, Unk3, VisualsID, UnkInt1, UnkInt2, UnkInt3 FROM battlepay_displayinfo");
    if (result)
    {
        do
        {
            auto fields = result->Fetch();

            WorldPackets::BattlePay::DisplayInfo info;

            if (auto x = fields[1].GetUInt32())
                info.CreatureDisplayID = x;
            if (auto x = fields[2].GetUInt32())
                info.VisualID = x;
            info.Name1 = fields[3].GetString();
            info.Name2 = fields[4].GetString();
            info.Name3 = fields[5].GetString();
            info.Name4 = fields[6].GetString();
            info.Name5 = fields[7].GetString();
            info.Name6 = fields[8].GetString();
            info.Name7 = fields[9].GetString();
            if (auto x = fields[10].GetUInt32())
                info.Flags = x;
            if (auto x = fields[11].GetUInt32())
                info.Unk1 = x;
            if (auto x = fields[12].GetUInt32())
                info.Unk2 = x;
            if (auto x = fields[13].GetUInt32())
                info.Unk3 = x;

            if (uint32 visualId = fields[14].GetUInt32())
            {
                auto result2 = LoginDatabase.PQuery("SELECT DisplayID, VisualId, UnkVisualInt, Name FROM battlepay_visuals WHERE ID = %u", visualId);
                if (result2)
                {
                    do
                    {
                        auto fields2 = result2->Fetch();

                        WorldPackets::BattlePay::Visual visual;

                        visual.DisplayId = fields2[0].GetUInt32();
                        visual.VisualId = fields2[1].GetUInt32();
                        visual.Unk = fields2[2].GetUInt32();
                        visual.Name = fields2[3].GetString();

                        info.Visuals.push_back(visual);
                    } while (result2->NextRow());
                }
            }

            info.UnkInt1 = fields[15].GetUInt32();
            info.UnkInt2 = fields[16].GetUInt32();
            info.UnkInt3 = fields[17].GetUInt32();

            displayInfos[fields[0].GetUInt32()] = info;
        } while (result->NextRow());
    }

    result = LoginDatabase.Query("SELECT ProductId, NormalPriceFixedPoint, CurrentPriceFixedPoint, ProductsGroup, UnkIntsGroup, Unk1, Unk2, Unk3, ChoiceType, DisplayInfoID FROM battlepay_productinfo");
    if (result)
    {
        do
        {
            auto fields = result->Fetch();

            WorldPackets::BattlePay::ProductStruct product;

            product.ProductId = fields[0].GetUInt32();
            product.NormalPriceFixedPoint = fields[1].GetUInt64();
            product.CurrentPriceFixedPoint = fields[2].GetUInt64();

            for (std::string_view parse : Trinity::Tokenize(fields[3].GetStringView(), ' ', false))
                if (Optional<uint32> dumb = Trinity::StringTo<uint32>(parse))
                    product.ProductIds.push_back(*dumb);
            for (std::string_view parse : Trinity::Tokenize(fields[4].GetStringView(), ' ', false))
                if (Optional<uint32> dumb = Trinity::StringTo<uint32>(parse))
                    product.UnkInts.push_back(*dumb);

            product.Unk1 = fields[5].GetUInt32();
            product.Unk2 = fields[6].GetUInt32();
            product.Unk3 = fields[7].GetUInt32();
            product.ChoiceType = fields[8].GetUInt32();

            if (uint32 displayInfoId = fields[9].GetUInt32())
            {
                auto itr = displayInfos.find(displayInfoId);
                if (itr != displayInfos.end())
                    product.Display = itr->second;
            }

            ProductStructs.push_back(product);

        } while (result->NextRow());
    }
    result = LoginDatabase.Query("SELECT ProductId, Type, Flags, Unk1, DisplayId, ItemId, Unk4, Unk5, Unk6, Unk7, Unk8, Unk9, UnkString, UnkBit, UnkBits, ItemGroup, DisplayInfoID FROM battlepay_product");
    if (result)
    {
        do
        {
            auto fields = result->Fetch();

            WorldPackets::BattlePay::Product product;

            product.ProductId = fields[0].GetUInt32();
            product.Type = fields[1].GetUInt8();
            product.Flags = fields[2].GetUInt32();
            product.Unk1 = fields[3].GetUInt32();
            product.DisplayId = fields[4].GetUInt32();
            product.ItemId = fields[5].GetUInt32();
            product.Unk4 = fields[6].GetUInt32();
            product.Unk5 = fields[7].GetUInt32();
            product.Unk6 = fields[8].GetUInt32();
            product.Unk7 = fields[9].GetUInt32();
            product.Unk8 = fields[10].GetUInt32();
            product.Unk9 = fields[11].GetUInt32();
            product.UnkString = fields[12].GetString();
            product.UnkBit = fields[13].GetBool();
            if (uint32 unkBits = fields[14].GetUInt32())
                product.UnkBits = unkBits;
            if (uint32 itemGroup = fields[15].GetUInt32())
            {
                auto result2 = LoginDatabase.PQuery("SELECT ItemGroupID, UnkByte, ItemID, Quantity, UnkInt1, UnkInt2, IsPet, PetResult, DisplayInfoID FROM battlepay_item_group WHERE ID = %u", itemGroup);
                if (result2)
                {
                    do
                    {
                        auto fields2 = result2->Fetch();

                        WorldPackets::BattlePay::ProductItem item;

                        item.ID = fields2[0].GetUInt32();
                        item.UnkByte = fields2[1].GetUInt8();
                        item.ItemID = fields2[2].GetUInt32();
                        item.Quantity = fields2[3].GetUInt32();
                        item.UnkInt1 = fields2[4].GetUInt32();
                        item.UnkInt1 = fields2[5].GetUInt32();
                        item.IsPet = fields2[6].GetBool();
                        if (uint32 petResult = fields[7].GetUInt32())
                            item.PetResult = petResult;

                        if (uint32 displayInfoId = fields2[8].GetUInt32())
                        {
                            auto itr = displayInfos.find(displayInfoId);
                            if (itr != displayInfos.end())
                                item.Display = itr->second;
                        }

                        product.Items.push_back(item);
                    } while (result2->NextRow());
                }
            }

            if (uint32 displayInfoId = fields[16].GetUInt32())
            {
                auto itr = displayInfos.find(displayInfoId);
                if (itr != displayInfos.end())
                    product.Display = itr->second;
            }

            Products.push_back(product);

        } while (result->NextRow());
    }

    result = LoginDatabase.Query("SELECT GroupID, IconFileDataID, DisplayType, Ordering, Unk, Name, Description FROM battlepay_groups");
    if (result)
    {
        do
        {
            auto fields = result->Fetch();

            WorldPackets::BattlePay::ShopGroup group;

            group.GroupId = fields[0].GetUInt32();
            group.IconFileDataID = fields[1].GetUInt32();
            group.DisplayType = fields[2].GetUInt8();
            group.Ordering = fields[3].GetUInt32();
            group.Unk = fields[4].GetUInt32();
            group.Name = fields[5].GetString();
            group.Description = fields[6].GetString();

            Groups.push_back(group);

        } while (result->NextRow());
    }

    result = LoginDatabase.Query("SELECT EntryID, GroupID, ProductID, Ordering, VasServiceType, StoreDeliveryType, DisplayInfoID FROM battlepay_entries");
    if (result)
    {
        do
        {
            auto fields = result->Fetch();

            WorldPackets::BattlePay::ShopEntry entry;

            entry.EntryID = fields[0].GetUInt32();
            entry.GroupID = fields[1].GetUInt32();
            entry.ProductID = fields[2].GetUInt32();
            entry.Ordering = fields[3].GetUInt32();
            entry.VasServiceType = fields[4].GetUInt32();
            entry.StoreDeliveryType = fields[5].GetUInt8();

            if (uint32 displayInfoId = fields[6].GetUInt32())
            {
                auto itr = displayInfos.find(displayInfoId);
                if (itr != displayInfos.end())
                    entry.Display = itr->second;
            }

            Entries.push_back(entry);

        } while (result->NextRow());
    }
}

// TODO: Implement this properly. this is just for a test
void BattlePayMgr::SendProductListResponseToSession(WorldSession* session)
{
    WorldPackets::BattlePay::BattlePayGetProductListResponse packet;
    packet.CurrencyID = 1;
    packet.Result = 0;
    packet.Entries = Entries;
    packet.Groups = Groups;
    packet.Products = Products;
    packet.ProductStructs = ProductStructs;
    session->SendPacket(packet.Write());
}
