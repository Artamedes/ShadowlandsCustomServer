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

#include "InstancePackets.h"

WorldPacket const* WorldPackets::Instance::UpdateLastInstance::Write()
{
    _worldPacket << uint32(MapID);

    return &_worldPacket;
}

WorldPacket const* WorldPackets::Instance::UpdateInstanceOwnership::Write()
{
    _worldPacket << int32(IOwnInstance);

    return &_worldPacket;
}

ByteBuffer& operator<<(ByteBuffer& data, WorldPackets::Instance::InstanceLock const& lockInfos)
{
    data << uint32(lockInfos.MapID);
    data << uint32(lockInfos.DifficultyID);
    data << uint64(lockInfos.InstanceID);
    data << uint32(lockInfos.TimeRemaining);
    data << uint32(lockInfos.CompletedMask);

    data.WriteBit(lockInfos.Locked);
    data.WriteBit(lockInfos.Extended);

    data.FlushBits();

    return data;
}

WorldPacket const* WorldPackets::Instance::InstanceInfo::Write()
{
    _worldPacket << int32(LockList.size());

    for (InstanceLock const& instanceLock : LockList)
        _worldPacket << instanceLock;

    return &_worldPacket;
}

WorldPacket const* WorldPackets::Instance::InstanceReset::Write()
{
    _worldPacket << uint32(MapID);

    return &_worldPacket;
}

WorldPacket const* WorldPackets::Instance::InstanceResetFailed::Write()
{
    _worldPacket << uint32(MapID);
    _worldPacket.WriteBits(ResetFailedReason, 2);
    _worldPacket.FlushBits();

    return &_worldPacket;
}

WorldPacket const* WorldPackets::Instance::InstanceSaveCreated::Write()
{
    _worldPacket.WriteBit(Gm);
    _worldPacket.FlushBits();

    return &_worldPacket;
}

void WorldPackets::Instance::InstanceLockResponse::Read()
{
    AcceptLock = _worldPacket.ReadBit();
}

WorldPacket const* WorldPackets::Instance::RaidGroupOnly::Write()
{
    _worldPacket << Delay;
    _worldPacket << Reason;

    return &_worldPacket;
}

WorldPacket const* WorldPackets::Instance::PendingRaidLock::Write()
{
    _worldPacket << int32(TimeUntilLock);
    _worldPacket << uint32(CompletedMask);
    _worldPacket.WriteBit(Extending);
    _worldPacket.WriteBit(WarningOnly);
    _worldPacket.FlushBits();

    return &_worldPacket;
}

WorldPacket const* WorldPackets::Instance::RaidInstanceMessage::Write()
{
    _worldPacket << uint8(Type);
    _worldPacket << uint32(MapID);
    _worldPacket << uint32(DifficultyID);
    _worldPacket.WriteBit(Locked);
    _worldPacket.WriteBit(Extended);
    _worldPacket.FlushBits();

    return &_worldPacket;
}

WorldPacket const* WorldPackets::Instance::InstanceEncounterEngageUnit::Write()
{
    _worldPacket << Unit;
    _worldPacket << uint8(TargetFramePriority);

    return &_worldPacket;
}

WorldPacket const* WorldPackets::Instance::InstanceEncounterDisengageUnit::Write()
{
    _worldPacket << Unit;

    return &_worldPacket;
}

WorldPacket const* WorldPackets::Instance::InstanceEncounterChangePriority::Write()
{
    _worldPacket << Unit;
    _worldPacket << uint8(TargetFramePriority);

    return &_worldPacket;
}

WorldPacket const* WorldPackets::Instance::InstanceEncounterStart::Write()
{
    _worldPacket << uint32(InCombatResCount);
    _worldPacket << uint32(MaxInCombatResCount);
    _worldPacket << uint32(CombatResChargeRecovery);
    _worldPacket << uint32(NextCombatResChargeTime);
    _worldPacket.WriteBit(InProgress);
    _worldPacket.FlushBits();

    return &_worldPacket;
}

WorldPacket const* WorldPackets::Instance::InstanceEncounterGainCombatResurrectionCharge::Write()
{
    _worldPacket << int32(InCombatResCount);
    _worldPacket << uint32(CombatResChargeRecovery);

    return &_worldPacket;
}

WorldPacket const* WorldPackets::Instance::BossKill::Write()
{
    _worldPacket << uint32(DungeonEncounterID);

    return &_worldPacket;
}

ByteBuffer& operator<<(ByteBuffer& data, WorldPackets::Instance::AuraInfo const& auraInfo)
{
    data << auraInfo.CasterGuid;
    data << uint32(auraInfo.SpellID);

    return data;
}

ByteBuffer& operator<<(ByteBuffer& data, WorldPackets::Instance::ArtifactPowerInfo const& artifactPowerInfo)
{
    data << uint32(artifactPowerInfo.ArtifactPowerID);
    data << uint16(artifactPowerInfo.Rank);

    return data;
}

ByteBuffer& operator<<(ByteBuffer& data, WorldPackets::Instance::EncounterItemInfo const& encounterItemInfo)
{
    data << uint32(encounterItemInfo.ItemID);
    data << uint32(encounterItemInfo.ItemLevel);
    data << uint32(encounterItemInfo.EnchantmentIDs.size());
    data << uint32(encounterItemInfo.ItemBonusListIDs.size());
    data << uint32(encounterItemInfo.Gems.size());

    for (uint32 i = 0; i < encounterItemInfo.EnchantmentIDs.size(); ++i)
        data << uint32(encounterItemInfo.EnchantmentIDs[i]);

    for (uint32 i = 0; i < encounterItemInfo.ItemBonusListIDs.size(); ++i)
        data << uint32(encounterItemInfo.ItemBonusListIDs[i]);

    for (uint32 i = 0; i < encounterItemInfo.Gems.size(); ++i)
        data << uint32(encounterItemInfo.Gems[i]);

    return data;
}

ByteBuffer& operator<<(ByteBuffer& data, WorldPackets::Instance::InstancePlayerData const& instancePlayerData)
{
    data << instancePlayerData.PlayerGuid;
    data << uint32(instancePlayerData.Stats.size());
    data << uint32(instancePlayerData.CombatRatings.size());
    data << uint32(instancePlayerData.AuraInfos.size());
    data << uint32(instancePlayerData.SpecID);
    data << uint32(instancePlayerData.Talents.size());
    data << uint32(instancePlayerData.PvpTalents.size());

    for (uint32 i = 0; i < instancePlayerData.Talents.size(); ++i)
        data << uint32(instancePlayerData.Talents[i]);

    for (uint32 i = 0; i < instancePlayerData.PvpTalents.size(); ++i)
        data << uint32(instancePlayerData.PvpTalents[i]);

    data << uint32(instancePlayerData.ArtifactPowerInfos.size());
    data << uint32(instancePlayerData.EncounterItemInfos.size());

    for (uint32 i = 0; i < instancePlayerData.Stats.size(); ++i)
        data << uint32(instancePlayerData.Stats[i]);

    for (uint32 i = 0; i < instancePlayerData.CombatRatings.size(); ++i)
        data << uint32(instancePlayerData.CombatRatings[i]);

    for (auto auraInfo : instancePlayerData.AuraInfos)
        data << auraInfo;

    for (auto artifactPowerInfo : instancePlayerData.ArtifactPowerInfos)
        data << artifactPowerInfo;

    for (auto encounterItemInfos : instancePlayerData.EncounterItemInfos)
        data << encounterItemInfos;

    return data;
}

WorldPacket const* WorldPackets::Instance::EncounterStart::Write()
{
    _worldPacket << uint32(EncounterID);
    _worldPacket << uint32(DifficultyID);
    _worldPacket << uint32(GroupSize);
    _worldPacket << uint32(PlayerDatas.size());

    for (auto PlayerData : PlayerDatas)
        _worldPacket << PlayerData;

    return &_worldPacket;
}

WorldPacket const* WorldPackets::Instance::EncounterEnd::Write()
{
    _worldPacket << uint32(EncounterID);
    _worldPacket << uint32(DifficultyID);
    _worldPacket << uint32(GroupSize);
    _worldPacket.WriteBit(Success);
    _worldPacket.FlushBits();

    return &_worldPacket;
}

WorldPacket const* WorldPackets::Instance::ChangePlayerDifficultyResult::Write()
{
    _worldPacket.FlushBits();
    _worldPacket.WriteBits(Result, 4);
    switch (Result)
    {
        case (uint8)ChangeDifficultyResult::DIFFICULTY_CHANGE_SET_COOLDOWN_S:
        case (uint8)ChangeDifficultyResult::DIFFICULTY_CHANGE_OTHER_HEROIC_S:
            _worldPacket.WriteBit(Cooldown);
            _worldPacket.FlushBits();
            _worldPacket << CooldownReason;
            break;
        case (uint8)ChangeDifficultyResult::DIFFICULTY_CHANGE_BY_PARTY_LEADER:
            _worldPacket << InstanceMapID;
            _worldPacket << DifficultyRecID;
            break;
        case (uint8)ChangeDifficultyResult::DIFFICULTY_CHANGE_ENCOUNTER:
            _worldPacket << MapID;
            break;
        case (uint8)ChangeDifficultyResult::DIFFICULTY_CHANGE_PLAYER_BUSY:
            _worldPacket << Guid;
            break;
        default:
            break;
    }

    return &_worldPacket;
}
