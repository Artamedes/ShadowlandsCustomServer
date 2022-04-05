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

        class TC_GAME_API CovenantRenownOpenNpc final : public ServerPacket
        {
        public:
            CovenantRenownOpenNpc() : ServerPacket(SMSG_COVENANT_RENOWN_OPEN_NPC, 16 + 1) { }

            WorldPacket const* Write() override;

            ObjectGuid NpcGUID;
            bool CatchupState = false;
        };

        class TC_GAME_API CovenantRenownSendCatchupState final : public ServerPacket
        {
        public:
            CovenantRenownSendCatchupState() : ServerPacket(SMSG_COVENANT_RENOWN_SEND_CATCHUP_STATE, 1) { }

            WorldPacket const* Write() override;

            bool CatchupState = false;
        };

        class TC_GAME_API OpenAnimaDiversionUI final : public ServerPacket
        {
        public:
            OpenAnimaDiversionUI() : ServerPacket(SMSG_OPEN_ANIMA_DIVERSION_UI, 16 + 4 + 4) { }

            WorldPacket const* Write() override;

            ObjectGuid GUID;
            int32 UiMapID = 0;
            int32 GarrTalentTreeID = 0;
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

        class TC_GAME_API OpenItemForge final : public ServerPacket
        {
        public:
            OpenItemForge(ObjectGuid guid) : ServerPacket(SMSG_OPEN_ITEM_FORGE, 16), GUID(guid) { }

            WorldPacket const* Write() override;

            int32 UnkInt1 = 3;
            ObjectGuid GUID;
            int32 UnkInt2 = 0;
        };
    }
}
