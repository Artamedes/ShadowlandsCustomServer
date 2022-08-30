/*
 * Copyright (C) 2017-2018 AshamaneProject <https://github.com/AshamaneProject>
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

#include "ChallengeModePackets.h"

ByteBuffer& operator<<(ByteBuffer& data, WorldPackets::ChallengeMode::ModeAttempt const& modeAttempt)
{
    time_t currTime = time(NULL);
    data << modeAttempt.InstanceRealmAddress;
    data << modeAttempt.AttemptID;
    data << modeAttempt.CompletionTime;
    data.AppendPackedTime(modeAttempt.CompletionDate);
    data << modeAttempt.MedalEarned;
    data << static_cast<uint32>(modeAttempt.Members.size());
    for (auto const& map : modeAttempt.Members)
    {
        data << map.VirtualRealmAddress;
        data << map.NativeRealmAddress;
        data << map.Guid;
        data << map.SpecializationID;
    }

    return data;
}

void WorldPackets::ChallengeMode::StartRequest::Read()
{
    _worldPacket >> Bag;
    _worldPacket >> Slot;
    _worldPacket >> GobGUID;
}

void WorldPackets::ChallengeMode::RequestLeaders::Read()
{
    _worldPacket >> MapId;
    _worldPacket >> ChallengeID;
    LastGuildUpdate = _worldPacket.read<uint32>();
    LastRealmUpdate = _worldPacket.read<uint32>();
}

// good 9.2
WorldPacket const* WorldPackets::ChallengeMode::RequestLeadersResult::Write()
{
    _worldPacket << MapID;
    _worldPacket << ChallengeID;
    _worldPacket.AppendPackedTime(LastGuildUpdate);
    _worldPacket.AppendPackedTime(LastRealmUpdate);

    _worldPacket << static_cast<uint32>(GuildLeaders.size());
    _worldPacket << static_cast<uint32>(RealmLeaders.size());

    for (auto const& guildLeaders : GuildLeaders)
        _worldPacket << guildLeaders;

    for (auto const& realmLeaders : RealmLeaders)
        _worldPacket << realmLeaders;

    return &_worldPacket;
}

// updated 9.2
WorldPacket const* WorldPackets::ChallengeMode::AllMapStats::Write()
{
    _worldPacket << uint32(Runs.size());
    _worldPacket << uint32(Rewards.size());
    _worldPacket << Season;
    _worldPacket << SubSeason;

    for (auto const& run : Runs)
        _worldPacket << run;

    for (auto const& reward : Rewards)
        _worldPacket << reward;

    return &_worldPacket;
}

WorldPacket const* WorldPackets::ChallengeMode::Rewards::Write()
{
    _worldPacket.WriteBit(IsWeeklyRewardAvailable);
    _worldPacket.FlushBits();

    _worldPacket << (uint32)LastWeekHighestKeyCompleted;
    _worldPacket << (uint32)LastWeekMapChallengeKeyEntry;
    _worldPacket << (uint32)CurrentWeekHighestKeyCompleted;

    return &_worldPacket;
}

// 9.2 checked
WorldPacket const* WorldPackets::ChallengeMode::Start::Write()
{
    _worldPacket << (uint32)MapID;
    _worldPacket << (uint32)ChallengeId;
    _worldPacket << (uint32)ChallengeLevel;

    for (uint32 v : Affixes)
        _worldPacket << v;

    _worldPacket << DeathCount;
    _worldPacket << uint32(PlayerDatas.size());

    _worldPacket.WriteBit(IsKeyCharged);
    _worldPacket.FlushBits();

    for (auto const& playerData : PlayerDatas)
        _worldPacket << playerData;

    return &_worldPacket;
}

// 9.2 read 4 ints, sniff only reads int
WorldPacket const* WorldPackets::ChallengeMode::Reset::Write()
{
    _worldPacket << uint32(MapId);

    return &_worldPacket;
}

// 9.2 read 4 ints
WorldPacket const* WorldPackets::ChallengeMode::UpdateDeathCount::Write()
{
    _worldPacket << (uint32)DeathCount;
    _worldPacket << (uint32)0;
    _worldPacket << (uint32)0;
    _worldPacket << (uint32)0;

    return &_worldPacket;
}

// checked 9.2
WorldPacket const* WorldPackets::ChallengeMode::Complete::Write()
{
    _worldPacket << Run;
    _worldPacket << int32(UnkInt);
    _worldPacket << uint32(Members.size());
    _worldPacket.WriteBit(IsCompletedInTimer);
    _worldPacket.FlushBits();
    for (auto const& mem : Members)
    {
        _worldPacket << mem.Member;
        _worldPacket.WriteBits(mem.Name.size(), 6);
        _worldPacket.FlushBits();
        _worldPacket.WriteString(mem.Name);
    }

    return &_worldPacket;
}

// read 4 ints 9.2
WorldPacket const* WorldPackets::ChallengeMode::NewPlayerRecord::Write()
{
    _worldPacket << (uint32)ChallengeId;
    _worldPacket << (uint32)Duration;
    _worldPacket << (uint32)ChallengeLevel;
    _worldPacket << (uint32)0; // unk

    return &_worldPacket;
}

// bad 9.2
WorldPacket const* WorldPackets::ChallengeMode::NewPlayerSeasonRecord::Write()
{
    _worldPacket << (uint32)ChallengeId;
    _worldPacket << (uint32)BestDuration;
    _worldPacket << (uint32)StartedChallengeLevel;

    return &_worldPacket;
}

// updated 9.2
WorldPacket const* WorldPackets::ChallengeMode::MythicPlusCurrentAffixes::Write()
{
    _worldPacket.reserve(Affixes.size() * 8);

    _worldPacket << uint32(Affixes.size());
    for (auto const& affix : Affixes)
    {
        _worldPacket << affix.KeystoneAffixID;
        _worldPacket << affix.RequiredSeason;
    }

    return &_worldPacket;
}
