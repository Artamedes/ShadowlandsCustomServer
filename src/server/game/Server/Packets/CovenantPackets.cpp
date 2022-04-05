#include "CovenantPackets.h"

WorldPacket const* WorldPackets::Covenant::CovenantRenownOpenNpc::Write()
{
    _worldPacket << NpcGUID;
    _worldPacket.WriteBit(CatchupState);
    _worldPacket.FlushBits();
    return &_worldPacket;
}

WorldPacket const* WorldPackets::Covenant::CovenantRenownSendCatchupState::Write()
{
    _worldPacket.WriteBit(CatchupState);
    _worldPacket.FlushBits();
    return &_worldPacket;
}

WorldPacket const* WorldPackets::Covenant::OpenAnimaDiversionUI::Write()
{
    _worldPacket << GUID;
    _worldPacket << UiMapID;
    _worldPacket << GarrTalentTreeID;
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

WorldPacket const* WorldPackets::Covenant::OpenItemForge::Write()
{
    _worldPacket << UnkInt1;
    _worldPacket << GUID;
    _worldPacket << UnkInt2;
    return &_worldPacket;
}
