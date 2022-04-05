#include "CovenantPackets.h"
#include "WorldSession.h"


void WorldSession::HandleRequestCovenantCallingsOpcode(WorldPackets::Covenant::RequestCovenantCallings& /*packet*/)
{
    WorldPackets::Covenant::CovenantCallingsAvailabilityResponse packet;
    packet.BountyIds.reserve(3);
    packet.BountyIds.emplace_back(173);
    packet.BountyIds.emplace_back(176);
    packet.BountyIds.emplace_back(189);
    SendPacket(packet.Write());
}

void WorldSession::HandleCovenantRenownRequestCatchupStateOpcode(WorldPackets::Covenant::CovenantRenownRequestCatchupState& /*packet*/)
{
    WorldPackets::Covenant::CovenantRenownSendCatchupState packet;
    SendPacket(packet.Write());
}
