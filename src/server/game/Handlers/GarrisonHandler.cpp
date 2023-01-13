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

#include "Chat.h"
#include "WorldSession.h"
#include "Garrison.h"
#include "GarrisonPackets.h"
#include "Player.h"
#include "CovenantMgr.h"

void WorldSession::HandleGetGarrisonInfo(WorldPackets::Garrison::GetGarrisonInfo& /*getGarrisonInfo*/)
{
    _player->SendGarrisonInfoResult();
    //if (Garrison* garrison = _player->GetGarrison())
    //    garrison->SendInfo();
}

void WorldSession::HandleGarrisonPurchaseBuilding(WorldPackets::Garrison::GarrisonPurchaseBuilding& garrisonPurchaseBuilding)
{
    if (!_player->GetNPCIfCanInteractWith(garrisonPurchaseBuilding.NpcGUID, UNIT_NPC_FLAG_NONE, UNIT_NPC_FLAG_2_GARRISON_ARCHITECT))
        return;

    if (Garrison* garrison = _player->GetGarrison())
        garrison->PlaceBuilding(garrisonPurchaseBuilding.PlotInstanceID, garrisonPurchaseBuilding.BuildingID);
}

void WorldSession::HandleGarrisonCancelConstruction(WorldPackets::Garrison::GarrisonCancelConstruction& garrisonCancelConstruction)
{
    if (!_player->GetNPCIfCanInteractWith(garrisonCancelConstruction.NpcGUID, UNIT_NPC_FLAG_NONE, UNIT_NPC_FLAG_2_GARRISON_ARCHITECT))
        return;

    if (Garrison* garrison = _player->GetGarrison())
        garrison->CancelBuildingConstruction(garrisonCancelConstruction.PlotInstanceID);
}

void WorldSession::HandleGarrisonRequestBlueprintAndSpecializationData(WorldPackets::Garrison::GarrisonRequestBlueprintAndSpecializationData& /*garrisonRequestBlueprintAndSpecializationData*/)
{
    if (Garrison* garrison = _player->GetGarrison())
        garrison->SendBlueprintAndSpecializationData();
}

void WorldSession::HandleGarrisonGetMapData(WorldPackets::Garrison::GarrisonGetMapData& /*garrisonGetMapData*/)
{
    if (Garrison* garrison = _player->GetGarrison())
        garrison->SendMapData(_player);
}

void WorldSession::HandleGarrisonResearchTalent(WorldPackets::Garrison::GarrisonResearchTalent& researchResult)
{
    TC_LOG_TRACE("network.opcode", "HandleGarrisonResearchTalent GarrTalentID: {} {} {}",
        researchResult.GarrTalentID, researchResult.Rank, researchResult.UnkGuid.ToString());
    if (auto talent = sGarrTalentStore.LookupEntry(researchResult.GarrTalentID))
    {
        if (auto tree = sGarrTalentTreeStore.LookupEntry(talent->GarrTalentTreeID))
        {
            if (tree->GarrTypeID == CovenantMgr::TheShadowlands)
            {
                uint32 Rank = 1;

                if (auto conduit = _player->GetCovenantMgr()->GetConduitByGarrTalentId(talent->ID))
                    Rank = conduit->Rank + 1;

                if (Rank != researchResult.Rank)
                    TC_LOG_ERROR("network.opcode", "{} sent invalid rank {} in HandleGarrisonResearchTalent", GetPlayerInfo(), researchResult.Rank);

                /// Handle cost for currency types
                if (auto costEntries = sDB2Manager.GetGarrTalentCostEntriesByGarrTalentId(talent->ID))
                {
                    for (auto costEntry : *costEntries)
                    {
                        if (costEntry->CostType == GarrTalentCostType::GARR_TALENT_COST_TYPE_INITAL)
                        {
                            if (costEntry->CurrencyTypesID > 0)
                            {
                                if (auto rankEntry = sGarrTalentRankStore.LookupEntry(costEntry->GarrTalentRankID))
                                {
                                    if (rankEntry->Rank == Rank - 1)
                                    {
                                        if (_player->GetCurrency(costEntry->CurrencyTypesID) < costEntry->CurrencyQuantity)
                                        {
                                            ChatHandler(this).SendSysMessage("Not enough tower knowledge to research this!");
                                            return;
                                        }

                                        _player->ModifyCurrency(costEntry->CurrencyTypesID, -int32(costEntry->CurrencyQuantity));
                                    }
                                }
                            }
                        }
                    }
                }

                _player->GetCovenantMgr()->LearnConduit(talent, tree, Rank);
                _player->KilledMonsterCredit(7000002);
            }
        }
    }
}

void WorldSession::HandleGarrisonLearnTalent(WorldPackets::Garrison::GarrisonLearnTalent& packet)
{
    _player->GetCovenantMgr()->LearnTalent(packet);
    _player->KilledMonsterCredit(7000002);
}

void WorldSession::HandleGarrisonSocketTalent(WorldPackets::Garrison::GarrisonSocketTalent& packet)
{
    // TODO: check if they own the SoulbindConduitItemID.
    _player->GetCovenant()->SocketTalent(packet);
    _player->KilledMonsterCredit(7000002);
}
