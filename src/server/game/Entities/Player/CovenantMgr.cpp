#include "CovenantMgr.h"
#include "Item.h"
#include "Player.h"
#include "DB2Stores.h"
#include "WorldSession.h"
#include "SpellInfo.h"
#include "SpellMgr.h"
#include "CovenantPackets.h"
#include "GarrisonPackets.h"
#include "ObjectMgr.h"
#include "GameTime.h"
#include "QueryHolder.h"
#include "SpellAuras.h"
#include "SpellAuraEffects.h"

Covenant::Covenant(CovenantID covId, Player* player) : _covenantId(covId), _player(player), _soulbindId(SoulbindID::None), _renownLevel(80), _anima(0), _souls(0)
{
}

bool Covenant::IsActiveCovenant() const
{
    return this == _player->GetCovenant();
}

void Covenant::SetSoulbind(SoulbindID soulbind, bool sendPacket /*= false*/)
{
    _soulbindId = soulbind;

    if (IsActiveCovenant())
    {
        _player->SetSoulbind(static_cast<int32>(_soulbindId));

        // SMSG_GARRISON_ADD_SPEC_GROUPS send instead.
        if (sendPacket)
        {
            WorldPackets::Garrison::AddSpecGroups packet;
            packet.GarrTypeID = 111;
            packet.SpecGroups.resize(1);
            packet.SpecGroups[0].ChrSpecializationID = _player->GetSpecializationId();
            packet.SpecGroups[0].SoulbindID = static_cast<int32>(GetSoulbindID());
            _player->SendDirectMessage(packet.Write());
        }

        _player->GetCovenantMgr()->UpdateConduits();
    }
}

void Covenant::SetRenown(int32 renown)
{
    _renownLevel = renown;

    if (!IsActiveCovenant())
        return;

    _player->ModifyCurrency(1822, renown, false, false, true);
    _player->GetCovenantMgr()->LearnCovenantSpells(); // renown rewards

    // Check Renown
    auto covIdInt = _player->m_playerData->CovenantID;
    for (auto reward : sRenownRewardsStore)
    {
        if (reward->CovenantID != covIdInt)
            continue;

        if (reward->Level > GetRenownLevel())
            continue;

        if (reward->QuestID > 0)
        {
            if (auto quest = sObjectMgr->GetQuestTemplate(reward->QuestID))
            {
                if (auto questStatus = _player->GetQuestStatus(reward->QuestID) == QUEST_STATUS_NONE)
                    _player->RewardQuest(quest, LootItemType::Item, 0, _player, false);
            }
        }
    }
}

void Covenant::SetAnima(uint32 anima)
{
    _anima = anima;
    if (IsActiveCovenant())
        _player->ModifyCurrency(1813, anima, true, false, true);
}

void Covenant::SetSouls(uint32 souls)
{
    _souls = souls;
    if (IsActiveCovenant())
        _player->ModifyCurrency(1810, souls, true, false, true);
}

void Covenant::InitializeCovenant()
{
    SetRenown(_renownLevel);
    SetAnima(_anima);
    SetSouls(_souls);

    // Don't think we need theese. Do need to complete the quests however.
    //_player->CompletedAchievement(sAchievementStore.LookupEntry(15247));
    //_player->CompletedAchievement(sAchievementStore.LookupEntry(15248));
    //_player->CompletedAchievement(sAchievementStore.LookupEntry(15249));
    //_player->CompletedAchievement(sAchievementStore.LookupEntry(15250));
    //_player->CompletedAchievement(sAchievementStore.LookupEntry(14934));
    //_player->CompletedAchievement(sAchievementStore.LookupEntry(14936));
    //_player->CompletedAchievement(sAchievementStore.LookupEntry(14937));
    //_player->CompletedAchievement(sAchievementStore.LookupEntry(14790));
    static uint32 questsToComplete[] = {61550, 59317, 61057, 61541, 61542, 62919, 62918, 61542, 61388, 61058, 60504, 60111, 60110, 59919, 59596, 59597, 59343, 59325, 58797, 59316, 57898};
    for (auto questId : questsToComplete)
    {
        if (_player->GetQuestStatus(questId) == QUEST_STATUS_NONE)
            _player->RewardQuest(sObjectMgr->GetQuestTemplate(questId), LootItemType::Item, 0, _player, false);
    }
}

void Conduit::FlagsUpdated(bool forceRemove /*= false*/)
{
    bool disabled = Flags == 0 || forceRemove;

    if (auto talentRank = sDB2Manager.GetTalentRankEntryByGarrTalentID(TalentEntryId))
    {
        if (talentRank->PerkSpellID > 0)
        {
            if (disabled)
            {
                if (_player->HasSpell(talentRank->PerkSpellID))
                    _player->RemoveSpell(talentRank->PerkSpellID);
            }
            else
            {
                if (!_player->HasSpell(talentRank->PerkSpellID))
                    _player->LearnSpell(talentRank->PerkSpellID, false);
            }
        }
    }

    if (Socket.has_value())
    {
        auto entries = sDB2Manager.GetSoulbindConduitRankBySoulbindConduitID(Socket->SoulbindConduitID);
        if (entries)
        {
            if (!disabled)
            {
                for (auto entry : *entries)
                {
                    if (entry->RankIndex == Socket->SoulbindConduitRank)
                    {
                        // activate socket spell.
                        // todo: research this more
                        _player->RemoveAurasDueToSpell(entries->at(0)->SpellID);
                        if (auto aura = _player->AddAura(entry->SpellID))
                            ;// aura->GetEffect(0)->SetAmount()
                        break;
                    }
                }
            }
            else
                _player->RemoveAurasDueToSpell(entries->at(0)->SpellID);
        }
    }
}

void Conduit::BuildGarrisonTalent(WorldPackets::Garrison::GarrisonTalent& talent)
{
    // GarrTalentID: 864
    // Rank: 1
    // ResearchStartTime: 1649217259
    // Flags: 1
    // HasSocket: False
    talent.GarrTalentID = TalentEntryId; // GarrTalent.dbc - Contains GarrTalentTreeID, which is the soulbind. 997 - 304 Endurance Conduit
    talent.Rank = Rank; // not sure
    talent.Flags = Flags; // not 100% sure
    talent.ResearchStartTime = ResearchStartTime; // not 100% sure. other garrison packets used this.
    if (Socket.has_value())
        talent.Socket = Socket;
}

void Covenant::SocketTalent(WorldPackets::Garrison::GarrisonSocketTalent& packet)
{
    // SMSG_GARRISON_APPLY_TALENT_SOCKET_DATA_CHANGES
    WorldPackets::Garrison::GarrisonApplyTalentSocketDataChanges response;
    response.GarrTypeID = 111;
    //response.Sockets.resize(packet.Sockets.size());
    for (int i = 0; i < packet.Sockets.size(); ++i)
    {
        auto conduit = _player->GetCovenantMgr()->GetConduitByGarrTalentId(packet.Sockets[i].SoulbindConduitID);
        if (!conduit)
        {
            response.RemoveConduitIds.push_back(packet.Sockets[i].SoulbindConduitRank); // todo: find if this conduit is socketed
            continue;
        }

        // TODO: Name these fields correctly.
        WorldPackets::Garrison::GarrisonTalentSocketChange socketChange;
        socketChange.ConduitID = packet.Sockets[i].SoulbindConduitID;
        WorldPackets::Garrison::GarrisonTalentSocketData data;
        data.SoulbindConduitID = packet.Sockets[i].SoulbindConduitRank;
        data.SoulbindConduitRank = 0; // probably the rank
        socketChange.Socket = data;
        conduit->Socket = data;
        response.Sockets.push_back(socketChange);
        conduit->FlagsUpdated(true);
        conduit->FlagsUpdated();
    }
    _player->SendDirectMessage(response.Write());
}

CovenantMgr::CovenantMgr(Player* player) : _player(player), _currCovenantIndex(0), _loaded(false)
{
    _playerCovenants[0] = std::make_unique<Covenant>(CovenantID::None, _player);
    _playerCovenants[1] = std::make_unique<Covenant>(CovenantID::Kyrian, _player);
    _playerCovenants[2] = std::make_unique<Covenant>(CovenantID::Venthyr, _player);
    _playerCovenants[3] = std::make_unique<Covenant>(CovenantID::NightFae, _player);
    _playerCovenants[4] = std::make_unique<Covenant>(CovenantID::Necrolord, _player);
}

void CovenantMgr::LoadFromDB(CharacterDatabaseQueryHolder const& holder)
{
    auto result = holder.GetPreparedResult(PLAYER_LOGIN_QUERY_LOAD_CHARACTER_COVENANT_COLLECTIONS);
    if (result)
    {
        CollectionEntries.rehash(result->GetRowCount());
        int i = 0;
        do
        {
            auto fields = result->Fetch();
            CollectionEntries[fields[0].GetInt32()] = fields[1].GetInt32();

            i++;

        } while (result->NextRow());
    }
    result = holder.GetPreparedResult(PLAYER_LOGIN_QUERY_LOAD_CHARACTER_COVENANT_CONDUITS);

    if (result)
    {
        do
        {
            auto fields = result->Fetch();

            uint32 CovenantID = fields[0].GetUInt32();
            uint32 GarrTalentID = fields[1].GetUInt32();
            uint32 GarrTalentTreeID = fields[2].GetUInt32();

            Conduit conduit(_player);

            conduit.TalentEntryId = GarrTalentID;
            conduit.TreeEntryId = GarrTalentTreeID;
            conduit.Rank = fields[3].GetUInt32();
            conduit.Flags = fields[4].GetUInt32();
            conduit.ResearchStartTime = fields[5].GetUInt64();

            uint32 SoulbindConduitID = fields[6].GetUInt32();
            if (SoulbindConduitID > 0)
            {
                WorldPackets::Garrison::GarrisonTalentSocketData data;
                data.SoulbindConduitID = SoulbindConduitID;
                data.SoulbindConduitRank = fields[7].GetUInt32();
                conduit.Socket = data;
            }

            _conduits.insert({ CovenantID, conduit });

        } while (result->NextRow());
    }

    result = holder.GetPreparedResult(PLAYER_LOGIN_QUERY_LOAD_CHARACTER_COVENANT);

    if (result)
    {
        do
        {
            auto fields = result->Fetch();

            auto covenant = fields[0].GetUInt32();

            // bad db data.
            if (covenant > 4)
                continue;

            auto Renown = fields[1].GetInt32();
            auto Anima = fields[2].GetUInt32();
            auto Souls = fields[2].GetUInt32();

            auto cov = _playerCovenants[covenant].get();

            cov->SetRenown(Renown);
            cov->SetAnima(Anima);
            cov->SetSouls(Souls);

        } while (result->NextRow());
    }


    result = holder.GetPreparedResult(PLAYER_LOGIN_QUERY_LOAD_CHARACTER_COVENANT_SOULBIND);

    if (result)
    {
        do
        {
            auto fields = result->Fetch();

            auto covenant = fields[0].GetUInt32();
            auto specId = fields[1].GetUInt32();
            auto soulbind = fields[2].GetUInt32();

            CovenantSoulbind covSoulbind;

            covSoulbind.SpecId = specId;
            covSoulbind.Soulbind = soulbind;

            _covenantSoulbinds.insert({ covenant, covSoulbind });
        } while (result->NextRow());
    }
    _loaded = true;
    OnSpecChange();
}

void CovenantMgr::SaveToDB(CharacterDatabaseTransaction trans)
{
    for (auto const& itr : _playerCovenants)
    {
        if (itr->GetCovenantID() == CovenantID::None)
            continue;

        auto stmt = CharacterDatabase.GetPreparedStatement(CHAR_REP_COVENANT);
        stmt->setUInt64(0, _player->GetGUID().GetCounter());
        stmt->setUInt32(1, static_cast<uint32>(itr->GetCovenantID()));
        stmt->setUInt32(2, itr->GetRenownLevel());
        stmt->setUInt32(3, itr->GetAnima());
        stmt->setUInt32(4, itr->GetSouls());
        trans->Append(stmt);
    }

    for (auto const& itr : _covenantSoulbinds)
    {
        auto stmt = CharacterDatabase.GetPreparedStatement(CHAR_REP_COVENANT_SOULBIND);
        stmt->setUInt64(0, _player->GetGUID().GetCounter());
        stmt->setUInt32(1, itr.first);
        stmt->setUInt32(2, itr.second.SpecId);
        stmt->setUInt32(3, itr.second.Soulbind);
        trans->Append(stmt);
    }

    for (auto const& itr : CollectionEntries)
    {
        auto stmt = CharacterDatabase.GetPreparedStatement(CHAR_REP_COVENANT_COLLECTIONS);
        stmt->setUInt64(0, _player->GetGUID().GetCounter());
        stmt->setInt32(1, itr.first);
        stmt->setInt32(2, itr.second);
        trans->Append(stmt);
    }

    for (auto const& itr : _conduits)
    {
        auto covenantid = itr.first;
        auto const& conduit = itr.second;

        auto index = 0;

        auto stmt = CharacterDatabase.GetPreparedStatement(CHAR_REP_COVENANT_CONDUITS);
        stmt->setUInt64(index++, _player->GetGUID().GetCounter());
        stmt->setUInt32(index++, covenantid);
        stmt->setUInt32(index++, conduit.TalentEntryId);
        stmt->setUInt32(index++, conduit.TreeEntryId);
        stmt->setUInt32(index++, conduit.Rank);
        stmt->setUInt32(index++, conduit.Flags);
        stmt->setUInt64(index++, conduit.ResearchStartTime);

        uint32 SoulbindConduitID = 0;
        uint32 SoulbindConduitRank = 0;

        if (conduit.Socket.has_value())
        {
            SoulbindConduitID = conduit.Socket->SoulbindConduitID;
            SoulbindConduitRank = conduit.Socket->SoulbindConduitRank;
        }

        stmt->setUInt32(index++, SoulbindConduitID);
        stmt->setUInt32(index++, SoulbindConduitRank);
        trans->Append(stmt);
    }
}

void CovenantMgr::InitializeFields()
{
    auto covenant = GetCovenant();
    LearnCovenantSpells();

    // Learn [0] SpellID: 340010 (Opening)
    // [0] SpellID: 321076 (Kyrian)
    // [0] SpellID: 324739 (Summon Steward)
    // [1] SpellID: 323547 (Echoing Reprimand)
    // [2] SpellID: 361948 (Language Verbal I)
    // [3] SpellID: 362067 (Language Glyphic 1)
    // [4] SpellID: 362791 (Language Interface 1)
    // [5] SpellID: 362790 (Language Glyphic 2)
    // SMSG_GET_GARRISON_INFO_RESULT
    //
    _player->SendGarrisonInfoResult();
    // SMSG_SET_CURRENCY 1822 - Quantity 79 - Renown
    // SMSG_SET_CURRENCY 1813 - Quantity: 79775 - Reservoir Anima
    // SMSG_SET_CURRENCY 1810 - Quantity: 3 - Redeemed Soul
    covenant->InitializeCovenant();
    // SMSG_SPELL_START (Cast) SpellID: 346760 (Gain Conduit Energy [DNT])
    _player->CastSpell(_player, 346760, true);
    //[0] (CtrOptions) ContentTuningConditionMask: 2
    // [0] (CtrOptions) Field_4: 3
    // [0] (CtrOptions) ExpansionLevelMask: 0
    // [0] CovenantID: 1
    // [0] SoulbindID: 0
    _player->SetCovenant(static_cast<int32>(covenant->GetCovenantID()));
    _player->SetSoulbind(static_cast<int32>(covenant->GetSoulbindID()));
    // [0] SpellID: 344087 (Deepening Bond)
    // (Cast) SpellID: 344088 (Deepening Bond)
    // SMSG_SUPERCEDED_SPELLS
    // [0] SpellID: 344089 // ID - 344089 Deepening Bond
    // [0] Superceded: 344087 // ID - 344087 Deepening Bond
    // (Cast) SpellID: 344090 (Deepening Bond)

    // Looks like it's just from RenownRewards.db2
    UpdateConduits();
}

Covenant* CovenantMgr::GetCovenant()
{
    return _playerCovenants[_currCovenantIndex].get();
}

void CovenantMgr::SetCovenant(CovenantID covenant)
{
    size_t newCovenantId = -1;

    switch (covenant)
    {
    case CovenantID::Kyrian: newCovenantId = 1; break;
    case CovenantID::Venthyr: newCovenantId = 2; break;
    case CovenantID::NightFae: newCovenantId = 3; break;
    case CovenantID::Necrolord: newCovenantId = 4; break;
    }

    if (newCovenantId == -1)
        return;

    // nothing to do.
    if (_currCovenantIndex == newCovenantId)
        return;

    // cleanups when swapping
    if (_currCovenantIndex != 0)
    {
        // Probably don't need
        //OnCovenantChange();
        // When changing blizz sends:
        // Reset Tracking Quests - 341736
        // (Cast) SpellID: 360991 (Become a Kyrian Again)
        // SMSG_UNLEARNED_SPELLS For all the conduits
        UnlearnCovenantSpells();
    }

    _currCovenantIndex = newCovenantId;
    InitializeFields();
}

void CovenantMgr::LearnCovenantSpells()
{
    auto spells = GetCovenantSpells();
    for (auto spell : spells)
        if (!_player->HasSpell(spell))
            _player->LearnSpell(spell, false);
}

void CovenantMgr::UnlearnCovenantSpells()
{
    auto spells = GetCovenantSpells();
    for (auto spell : spells)
        _player->RemoveSpell(spell);
}

std::list<uint32> CovenantMgr::GetCovenantSpells()
{
    std::list<uint32> SpellsToLearn;
    auto covenant = GetCovenant();

    uint32 RequiredCovenantPreviewID = 0;

    switch (covenant->GetCovenantID())
    {
    case CovenantID::Kyrian: RequiredCovenantPreviewID = 2; break;
    case CovenantID::Venthyr: RequiredCovenantPreviewID = 7; break;
    case CovenantID::Necrolord: RequiredCovenantPreviewID = 6; break;
    case CovenantID::NightFae: RequiredCovenantPreviewID = 5;break;
    }

    auto soulbind = static_cast<uint32>(GetSoulbindUIDisplayInfoIdFromSoulbindID(covenant->GetSoulbindID()));

    ChrClassesEntry const* clsEntry = sChrClassesStore.LookupEntry(_player->GetClass());
    auto family = clsEntry->SpellClassSet;

    for (auto entry : sUiCovenantAbilityEntry)
    {
        if (entry->CovenantPreviewID != RequiredCovenantPreviewID)
            continue;

        if (entry->AbilityType == 1)
            SpellsToLearn.push_back(entry->SpellID);
        else if (entry->AbilityType == 0)
        {
            // Class
            auto spellInfo = sSpellMgr->GetSpellInfo(entry->SpellID);
            if (spellInfo == nullptr)
                continue;
            if (spellInfo->SpellFamilyName == family)
                SpellsToLearn.push_back(entry->SpellID);
        }
        else if (entry->AbilityType == 2)
        {
            // Soulbind
            if (entry->SoulbindDisplayInfoID == soulbind)
                SpellsToLearn.push_back(entry->SpellID);
        }
    }

    // We can use UICovenantAbility.db2 here.
    switch (covenant->GetCovenantID())
    {
        case CovenantID::Kyrian:
            // [0] SpellID: 321076 (Kyrian)
            // [0] SpellID: 324739 (Summon Steward)
            SpellsToLearn.push_back(321076);
            //SpellsToLearn.push_back(324739);
            // [1] SpellID: 323547 (Echoing Reprimand)
            //SpellsToLearn.push_back(323547);
            break;
        case CovenantID::Venthyr:
            // 321079 - venthyr
            SpellsToLearn.push_back(321079);
            break;
        case CovenantID::Necrolord:
            // 321078 - necro
            SpellsToLearn.push_back(321078);
            break;
        case CovenantID::NightFae:
            // 321077  - night fae
            SpellsToLearn.push_back(321077);
            break;
    }

    // Check Renown
    auto covIdInt = static_cast<int32>(covenant->GetCovenantID());
    for (auto reward : sRenownRewardsStore)
    {
        if (reward->CovenantID != covIdInt)
            continue;

        if (reward->Level > covenant->GetRenownLevel())
            continue;

        if (reward->SpellID > 0)
            SpellsToLearn.push_back(reward->SpellID);
    }

    return SpellsToLearn;
}

void CovenantMgr::LearnSoulbindConduit(Item* item)
{
    auto conduitId = sDB2Manager.GetConduitIDFromItemID(item->GetEntry());
    if (!conduitId)
        return;

    // SoulbindConduitRankProperties.db2, And check the itemlevel
    int32 rank = 0;
    for (auto prop : sSoulbindConduitRankPropertiesStore)
    {
        if (item->GetItemLevel(_player) > prop->ItemLevel)
            break;

        rank++;
    }

    // SMSG_GARRISON_COLLECTION_UPDATE_ENTRY
    WorldPackets::Garrison::GarrisonCollectionUpdateEntry packet;

    packet.GarrTypeID = 111;
    packet.UnkInt2 = 1; // Type.
    packet.Socket.SoulbindConduitID = conduitId;
    packet.Socket.SoulbindConduitRank = rank;
    _player->SendDirectMessage(packet.Write());

    auto itr = CollectionEntries.find(conduitId);
    if (itr != CollectionEntries.end())
    {
        if (itr->second < rank)
            itr->second = rank;
    }
    else
    {
        CollectionEntries[conduitId] = rank;
    }
}

void CovenantMgr::AddGarrisonInfo(WorldPackets::Garrison::GetGarrisonInfoResult& garrisonInfo)
{
    WorldPackets::Garrison::GarrisonInfo cov;

    cov.GarrTypeID = 111; // GarrType.db2
    cov.GarrSiteID = 299; // don't know
    cov.GarrSiteLevelID = 864; // GarrSiteLevel.db2

    cov.Collections.resize(1);
    cov.Collections[0].Type = 1;

    cov.Collections[0].Entries.reserve(CollectionEntries.size());
    for (auto const& itr : CollectionEntries)
    {
        WorldPackets::Garrison::GarrisonCollectionEntry entry;
        entry.EntryID = itr.first;
        entry.Rank = itr.second;
        cov.Collections[0].Entries.emplace_back(entry);
    }

   //for (auto entry : sSoulbindConduitStore)
   //{
   //    // [7] (Talents) [0] GarrTalentID: 997
   //    // [7] (Talents) [0] Rank: 1
   //    // [7] (Talents) [0] ResearchStartTime: 1625953643
   //    // [7] (Talents) [0] Flags: 1
   //    // [7] (Talents) [0] (Socket) SoulbindConduitID: 283
   //    // [7] (Talents) [0] (Socket) SoulbindConduitRank: 0
   //    WorldPackets::Garrison::GarrisonTalent talent;
   //    WorldPackets::Garrison::GarrisonTalentSocketData socket;
   //    socket.SoulbindConduitID = entry->ID;
   //    socket.SoulbindConduitRank = 0;
   //    talent.Socket = socket;
   //    talent.Flags = entry->Flags;
   //    talent.GarrTalentID = 997; // GarrTalent.dbc - Contains GarrTalentTreeID, which is the soulbind. 997 - 304 Endurance Conduit
   //    talent.Rank = 1;
   //    talent.ResearchStartTime = getMSTime();
   //    cov.Talents.push_back(talent);
   //}
    BuildGarrisonPacket(cov);

    garrisonInfo.Garrisons.push_back(cov);
}


void CovenantMgr::LearnConduit(GarrTalentEntry const* talent, GarrTalentTreeEntry const* tree)
{
    Conduit conduit(_player);
    conduit.TalentEntryId = talent->ID;
    conduit.TreeEntryId = tree->ID;
    conduit.Flags = GarrisonTalentFlags::TalentFlagEnabled;

    uint32 covId = (uint32)_currCovenantIndex;
    auto range = _conduits.equal_range(covId);
    bool found = false;
    for (auto i = range.first; i != range.second; ++i)
    {
        if (i->second.TalentEntryId == talent->ID)
        {
            found = true;
            break;
        }
    }
    if (!found)
        _conduits.insert({ covId, conduit });

    // SMSG_GARRISON_RESEARCH_TALENT_RESULT send instead
    //_player->SendGarrisonInfoResult();
    // ServerToClient: SMSG_GARRISON_RESEARCH_TALENT_RESULT (0x296C) Length: 30 ConnIdx: 1 Time: 04/05/2022 23:54:19.075 Number: 15355
    // UnkInt1: 0
    // GarrTypeID: 111
    // unkbit: True

    WorldPackets::Garrison::GarrisonResearchTalentResult result;
    result.GarrTypeID = 111;
    conduit.BuildGarrisonTalent(result.talent);
    _player->SendDirectMessage(result.Write());

    // SMSG_LEARNED_SPELLS - need implement GarrTalentRank.db2
    auto covenant = GetCovenant();
    auto soulbindId = GetSoulbindIDFromTalentTreeId(tree->ID);
    if (soulbindId == SoulbindID::None || soulbindId == covenant->GetSoulbindID())
        conduit.FlagsUpdated();
    // SMSG_CRITERIA_UPDATE Criteria ID, 30952, 3x Quantity
    // SMSG_GARRISON_TALENT_COMPLETED
    WorldPackets::Garrison::GarrisonTalentCompleted result2;
    result2.GarrTypeID = 111;
    result2.GarrTalentID = talent->ID;
    _player->SendDirectMessage(result2.Write());
}

void CovenantMgr::BuildGarrisonPacket(WorldPackets::Garrison::GarrisonInfo& result)
{
    uint32 covId = (uint32)_currCovenantIndex;
    auto range = _conduits.equal_range(covId);

    for (auto i = range.first; i != range.second; ++i)
    {
        auto& conduit = i->second;

        WorldPackets::Garrison::GarrisonTalent talent;
        conduit.BuildGarrisonTalent(talent); // maybe make const
        result.Talents.push_back(talent);
    }
}

void CovenantMgr::LearnTalent(WorldPackets::Garrison::GarrisonLearnTalent& researchResult)
{
    auto talent = sGarrTalentStore.LookupEntry(researchResult.GarrTalentID);
    if (!talent)
        return;

    // SMSG_UNLEARNED_SPELLS
    // Sent down below.

    WorldPackets::Garrison::GarrisonSwitchTalentTreeBranch packet;
    packet.GarrTypeID = 111;
    uint32 covId = (uint32)_currCovenantIndex;
    auto range = _conduits.equal_range(covId);

    auto AddConduitToListIfNeed([range, covId, this](GarrTalentEntry const* pTalent)
    {
        bool found = false;
        for (auto i = range.first; i != range.second; ++i)
        {
            if (i->second.TalentEntryId == pTalent->ID)
            {
                found = true;
                break;
            }
        }
        if (!found)
        {
            Conduit conduit(_player);
            conduit.TalentEntryId = pTalent->ID;
            conduit.TreeEntryId = pTalent->GarrTalentTreeID;
            conduit.Flags = GarrisonTalentFlags::TalentFlagEnabled;

            _conduits.insert({ covId, conduit });
        }
    });

    AddConduitToListIfNeed(talent);

    std::set<uint32> TalentTiersToCheck;
    TalentTiersToCheck.insert(talent->Tier);
    auto extraConduits = sDB2Manager.GetTalentEntriesByGarrTalentId(talent->ID);
    if (extraConduits != nullptr)
    {
        for (auto t : *extraConduits)
        {
            AddConduitToListIfNeed(t);
            TalentTiersToCheck.insert(t->Tier);
        }
    }

    auto garrTalentResult = sGarrTalentStore.LookupEntry(talent->PrerequesiteTalentID);

    while (garrTalentResult != nullptr)
    {
        AddConduitToListIfNeed(garrTalentResult);
        TalentTiersToCheck.insert(garrTalentResult->Tier);
        talent = garrTalentResult;
        auto newResult = sGarrTalentStore.LookupEntry(garrTalentResult->PrerequesiteTalentID);
        if (newResult == garrTalentResult)
            break;
        garrTalentResult = newResult;
    }

    for (auto i = range.first; i != range.second; ++i)
    {
        auto entry = sGarrTalentStore.LookupEntry(i->second.TalentEntryId);

        if (TalentTiersToCheck.count(entry->Tier))
        {
            if (entry->GarrTalentTreeID != talent->GarrTalentTreeID)
                continue;

            if (i->second.TalentEntryId == talent->ID || entry->PrerequesiteTalentID == talent->ID)
                i->second.Flags = GarrisonTalentFlags::TalentFlagEnabled;
            else
                i->second.Flags = GarrisonTalentFlags::TalentFlagDisabled;

            if (researchResult.SoulbindID == _player->m_playerData->SoulbindID)
                i->second.FlagsUpdated();
            WorldPackets::Garrison::GarrisonTalent garrTalentPacket;
            i->second.BuildGarrisonTalent(garrTalentPacket);
            packet.Talents.push_back(garrTalentPacket);
        }
    }

    _player->SendDirectMessage(packet.Write());
}

Conduit* CovenantMgr::GetConduitByGarrTalentId(uint32 garrTalentId)
{
    uint32 covId = (uint32)_currCovenantIndex;
    auto range = _conduits.equal_range(covId);

    for (auto i = range.first; i != range.second; ++i)
    {
        auto& conduit = i->second;
        if (conduit.TalentEntryId == garrTalentId)
            return &conduit;
    }

    return nullptr;
}

void CovenantMgr::SetSoulbind(SoulbindID soulbind, bool sendPacket /*= false*/)
{
    auto covenant = GetCovenant();
    if (covenant->GetCovenantID() == CovenantID::None)
        return;

    covenant->SetSoulbind(soulbind, sendPacket);

    auto range = _covenantSoulbinds.equal_range(_player->m_playerData->CovenantID);
    for (auto i = range.first; i != range.second; ++i)
    {
        if (i->second.SpecId == _player->GetSpecializationId())
        {
            i->second.Soulbind = static_cast<uint32>(soulbind);
            return;
        }
    }

    CovenantSoulbind covSoulbind;

    covSoulbind.Soulbind = static_cast<uint32>(soulbind);
    covSoulbind.SpecId = _player->GetSpecializationId();

    _covenantSoulbinds.insert({ _player->m_playerData->CovenantID, covSoulbind });
}

void CovenantMgr::OnSpecChange()
{
    if (!_loaded)
        return;
    auto covenant = GetCovenant();
    if (covenant->GetCovenantID() == CovenantID::None)
        return;

    auto range = _covenantSoulbinds.equal_range(_player->m_playerData->CovenantID);
    for (auto i = range.first; i != range.second; ++i)
    {
        if (i->second.SpecId == _player->GetSpecializationId())
        {
            covenant->SetSoulbind(static_cast<SoulbindID>(i->second.Soulbind));
            break;
        }
    }
}

void CovenantMgr::UpdateConduits()
{
    for (auto& itr : _conduits)
    {
        bool remove = false;

        if (itr.first != _player->m_playerData->CovenantID)
            remove = true;

        if (!remove)
        {
            auto requiredSoulbindId = static_cast<int32>(GetSoulbindIDFromTalentTreeId(itr.second.TreeEntryId));
            if (requiredSoulbindId != 0 && requiredSoulbindId != _player->m_playerData->SoulbindID)
                remove = true;
        }

        itr.second.FlagsUpdated(remove);
    }
}
