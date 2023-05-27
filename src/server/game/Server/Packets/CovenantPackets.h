#pragma once

#include "Packet.h"
#include "ObjectGuid.h"
#include "PacketUtilities.h"

namespace WorldPackets
{
    namespace Covenant
    {
        class RequestCovenantCallings final : public ClientPacket
        {
        public:
            RequestCovenantCallings(WorldPacket&& packet) : ClientPacket(CMSG_REQUEST_COVENANT_CALLINGS, std::move(packet)) { }

            void Read() override { }
        };

        class CovenantRenownRequestCatchupState final : public ClientPacket
        {
        public:
            CovenantRenownRequestCatchupState(WorldPacket&& packet) : ClientPacket(CMSG_COVENANT_RENOWN_REQUEST_CATCHUP_STATE, std::move(packet)) { }

            void Read() override { }
        };

        class ActivateSoulbind final : public ClientPacket
        {
        public:
            ActivateSoulbind(WorldPacket&& packet) : ClientPacket(CMSG_ACTIVATE_SOULBIND, std::move(packet)) { }

            void Read() override;

            uint32 SoulbindID;
        };

        class TC_GAME_API CovenantRenownSendCatchupState final : public ServerPacket
        {
        public:
            CovenantRenownSendCatchupState() : ServerPacket(SMSG_COVENANT_RENOWN_SEND_CATCHUP_STATE, 1) { }

            WorldPacket const* Write() override;

            bool CatchupState = false;
        };

        class TC_GAME_API CovenantPreviewOpenNpc final : public ServerPacket
        {
        public:
            CovenantPreviewOpenNpc() : ServerPacket(SMSG_COVENANT_PREVIEW_OPEN_NPC, 16 + 4) { }

            WorldPacket const* Write() override;

            ObjectGuid NpcGUID;
            int32 CovenantID = 0;
        };

        class TC_GAME_API CovenantCallingsAvailabilityResponse final : public ServerPacket
        {
        public:
            CovenantCallingsAvailabilityResponse() : ServerPacket(SMSG_COVENANT_CALLINGS_AVAILABILITY_RESPONSE, 16 + 4 + 4) { }

            WorldPacket const* Write() override;

            bool AreCallingsUnlocked = true;
            std::vector<int32> BountyIds;
        };
    }
}
