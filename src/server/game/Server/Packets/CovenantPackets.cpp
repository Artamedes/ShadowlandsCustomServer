#include "CovenantPackets.h"

WorldPacket const* WorldPackets::Covenant::CovenantRenownSendCatchupState::Write()
{
    _worldPacket.WriteBit(CatchupState);
    _worldPacket.FlushBits();
    return &_worldPacket;
}

WorldPacket const* WorldPackets::Covenant::CovenantCallingsAvailabilityResponse::Write()
{
    _worldPacket.WriteBit(AreCallingsUnlocked);
    _worldPacket.FlushBits();
    for (int32 bounty : BountyIds)
        _worldPacket << bounty;
    return &_worldPacket;
}

WorldPacket const* WorldPackets::Covenant::CovenantPreviewOpenNpc::Write()
{
    _worldPacket << NpcGUID;
    _worldPacket << CovenantID;
    return &_worldPacket;
}

void WorldPackets::Covenant::ActivateSoulbind::Read()
{
    _worldPacket >> SoulbindID;
}
