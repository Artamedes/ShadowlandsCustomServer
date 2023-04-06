/*
 * This file is part of the TrinityCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "WorldSession.h"
#include "CollectionMgr.h"
#include "CollectionPackets.h"
#include "Item.h"

void WorldSession::HandleCollectionItemSetFavorite(WorldPackets::Collections::CollectionItemSetFavorite& collectionItemSetFavorite)
{
    switch (collectionItemSetFavorite.Type)
    {
        case WorldPackets::Collections::TOYBOX:
            GetCollectionMgr()->ToySetFavorite(collectionItemSetFavorite.ID, collectionItemSetFavorite.IsFavorite);
            break;
        case WorldPackets::Collections::APPEARANCE:
        {
            auto [hasAppearance, isTemporary] = GetCollectionMgr()->HasItemAppearance(collectionItemSetFavorite.ID);
            if (!hasAppearance || isTemporary)
                return;

            GetCollectionMgr()->SetAppearanceIsFavorite(collectionItemSetFavorite.ID, collectionItemSetFavorite.IsFavorite);
            break;
        }
        case WorldPackets::Collections::TRANSMOG_SET:
            break;
        default:
            break;
    }
}

void WorldSession::HandleAddAccountCosmetic(WorldPackets::Collections::AddAccountCosmetic& addAccountCosmetic)
{
    if (auto item = _player->GetItemByGuid(addAccountCosmetic.Item))
    {
        if (item->GetTemplate()->GetSubClass() == 5 && item->GetItemModifiedAppearance() && !GetCollectionMgr()->HasItemAppearance(item->GetItemModifiedAppearance()->ID).second)
        {
            // ServerToClient: SMSG_PLAY_SPELL_VISUAL_KIT(0x2C49) Length : 22 ConnIdx : 1 Time : 08 / 26 / 2022 23:13 : 34.130 Number : 6293
            // Unit : Full : 0x0801340000000000000000000EC8BD77 Player / 0 R77 / S0 Map : 0 (Eastern Kingdoms) Low : 248036727
            // KitRecID : 362
            // KitType : 1
            // Duration : 0
            // MountedVisual : False

            _player->SendPlaySpellVisualKit(362, 1, 0);

            item->SetBinding(true);
            WorldPacket data(SMSG_ACCOUNT_COSMETIC_ADDED);
            data << uint32(113239);
            SendPacket(&data);
            GetCollectionMgr()->AddItemAppearance(item);
            _player->DestroyItem(item->GetBagSlot(), item->GetSlot(), true);

        }
    }
}
