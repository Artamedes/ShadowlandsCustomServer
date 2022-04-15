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

ByteBuffer& operator<<(ByteBuffer& data, WorldPackets::ChallengeMode::MapStatMember const& member)
{
    data << member.PlayerGuid;
    data << member.GuildGuid;
    data << member.VirtualRealmAddress;
    data << member.NativeRealmAddress;
    data << member.SpecializationID;
    data << member.Race;
    data << member.Ilevel;

    return data;
}

ByteBuffer& operator<<(ByteBuffer& data, WorldPackets::ChallengeMode::ChallengeMapStat const& mapStat)
{
    data << mapStat.ChallengeID;
    data << mapStat.CompletedChallengeLevel;
    data << mapStat.BestCompletionMilliseconds;

    data.AppendPackedTime(mapStat.StartTime);
    data.AppendPackedTime(mapStat.EndTime);

    for (auto const& v : mapStat.Affixes)
        data << v;

    data << static_cast<uint32>(mapStat.Members.size());

    for (auto const& member : mapStat.Members)
        data << member;

    return data;
}

ByteBuffer& operator<<(ByteBuffer& data, WorldPackets::ChallengeMode::ChallengeMapStatWeekAttempts const& weekAttempts)
{
    data << weekAttempts.ChallengeID;
    data << weekAttempts.ChallengeLevel;
    data.AppendPackedTime(weekAttempts.StartTime);
    data.AppendPackedTime(weekAttempts.EndTime);
    data.WriteBit(weekAttempts.InTime);
    data.FlushBits();

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

WorldPacket const* WorldPackets::ChallengeMode::AllMapStats::Write()
{
    _worldPacket << static_cast<uint32>(LegionChallengeModeMaps.size());
    _worldPacket << static_cast<uint32>(BFAChallengeModeMaps.size());
    _worldPacket << static_cast<uint32>(WeekAttempts.size());
    _worldPacket << CurrentSeason;

    for (auto const& legionChallengeModeMap : LegionChallengeModeMaps)
        _worldPacket << legionChallengeModeMap;

    for (auto const& BFAChallengeModeMap : BFAChallengeModeMaps)
    {
        _worldPacket << SeasonID;
        _worldPacket << BFAChallengeModeMap;
    }

    for (auto const& WeekAttempt : WeekAttempts)
        _worldPacket << WeekAttempt;

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

WorldPacket const* WorldPackets::ChallengeMode::Start::Write()
{
    _worldPacket << (uint32)MapID;
    _worldPacket << (uint32)ChallengeId;
    _worldPacket << (uint32)ChallengeLevel;

    for (uint32 v : Affixes)
        _worldPacket << v;

    _worldPacket << DeathCount;
    _worldPacket << uint32(PlayerDatas.size());

    for (auto playerData : PlayerDatas)
        _worldPacket << playerData;
    
    _worldPacket.WriteBit(IsKeyCharged);    
    _worldPacket.FlushBits();

    return &_worldPacket;
}

WorldPacket const* WorldPackets::ChallengeMode::Reset::Write()
{
    _worldPacket << (uint32)MapId;

    return &_worldPacket;
}

WorldPacket const* WorldPackets::ChallengeMode::UpdateDeathCount::Write()
{
    _worldPacket << (uint32)DeathCount;

    return &_worldPacket;
}

WorldPacket const* WorldPackets::ChallengeMode::Complete::Write()
{
    _worldPacket << (uint32)Duration;
    _worldPacket << (uint32)MapID;
    _worldPacket << (uint32)ChallengeId;
    _worldPacket << (uint32)ChallengeLevel;

    _worldPacket.WriteBit(IsCompletedInTimer);
    _worldPacket.FlushBits();

    return &_worldPacket;
}

WorldPacket const* WorldPackets::ChallengeMode::NewPlayerRecord::Write()
{
    _worldPacket << (uint32)ChallengeId;
    _worldPacket << (uint32)Duration;
    _worldPacket << (uint32)ChallengeLevel;

    return &_worldPacket;
}

WorldPacket const* WorldPackets::ChallengeMode::NewPlayerSeasonRecord::Write()
{
    _worldPacket << (uint32)ChallengeId;
    _worldPacket << (uint32)BestDuration;
    _worldPacket << (uint32)StartedChallengeLevel;

    return &_worldPacket;
}

WorldPacket const* WorldPackets::ChallengeMode::Affixes::Write()
{
    _worldPacket.reserve(affixesFileDatas.size() * 4);

    _worldPacket << uint32(affixesFileDatas.size());
    for (uint8 i = 0; i < affixesFileDatas.size(); i++)
        _worldPacket << affixesFileDatas[i];

    return &_worldPacket;
}
