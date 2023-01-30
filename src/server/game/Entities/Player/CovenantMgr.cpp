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
#include "StringConvert.h"
#include "ConditionMgr.h"
#include <sstream>
#include "CollectionMgr.h"

Covenant::Covenant(CovenantID covId, Player* player) : _covenantId(covId), _player(player), _soulbindId(SoulbindID::None), _anima(0), _souls(0)
{
    switch (covId)
    {
        case CovenantID::Kyrian:
        case CovenantID::Venthyr:
        case CovenantID::NightFae:
        case CovenantID::Necrolord:
            _renownLevel = 80;
            break;
        default:
            _renownLevel = 1;
            break;
    }
}

bool Covenant::IsActiveCovenant() const
{
    return this == _player->GetCovenant();
}

void Covenant::SetSoulbind(SoulbindID soulbind, bool sendPacket /*= false*/)
{
    m_SaveFlags.AddFlag(eCovenantSaveFlags::SaveSoulbind);
    _player->GetCovenantMgr()->DisableAllConduitsForSoulbind();
    _soulbindId = soulbind;

    if (IsActiveCovenant())
    {
        _player->SetSoulbind(static_cast<int32>(_soulbindId));

        // SMSG_GARRISON_ADD_SPEC_GROUPS send instead.
        if (sendPacket)
        {
            WorldPackets::Garrison::AddSpecGroups packet;
            packet.GarrTypeID = CovenantMgr::TheShadowlands;
            packet.SpecGroups.resize(1);
            packet.SpecGroups[0].ChrSpecializationID = _player->GetSpecializationId();
            packet.SpecGroups[0].SoulbindID = static_cast<int32>(GetSoulbindID());
            _player->SendDirectMessage(packet.Write());
        }
        _player->GetCovenantMgr()->UpdateAllConduitsForSoulbind();
    }
}

void Covenant::SetRenown(int32 renown, bool /*modCurr = true*/)
{
    m_SaveFlags.AddFlag(eCovenantSaveFlags::SaveCovenant);
    _renownLevel = renown;

    if (!IsActiveCovenant())
        return;

    _player->SetCreateCurrency(1822, renown);
    _player->SendCurrencies();
    UpdateRenownRewards();
}

void Covenant::SetAnima(uint32 anima, bool modCurr /*= true*/, bool inital)
{
    uint32 beforeAnima = _anima;
    m_SaveFlags.AddFlag(eCovenantSaveFlags::SaveCovenant);
    _anima = anima;
    if (IsActiveCovenant())
    {
        if (modCurr)
        {
            _player->SetCreateCurrency(1813, anima);
            _player->SendCurrencies();

            if (!inital)
            {
                _player->GetScheduler().Schedule(3s, 1000, [this, beforeAnima](TaskContext /*context*/)
                {
                    /// Only sends a yellow message...pretty boring.
                    if (beforeAnima < _anima)
                    {
                        WorldPacket data(SMSG_CONVERT_ITEMS_TO_CURRENCY_VALUE, 4 + 4);
                        data << uint32(1813);
                        data << _anima - beforeAnima;
                        _player->SendDirectMessage(&data);
                    }
                });
            }
        }
    }
}

void Covenant::SetSouls(uint32 souls, bool modCurr /*= true*/, bool inital)
{
    m_SaveFlags.AddFlag(eCovenantSaveFlags::SaveCovenant);
    _souls = souls;
    if (IsActiveCovenant() && modCurr)
    {
        _player->SetCreateCurrency(1810, souls);
        _player->SendCurrencies();
    }
}

void Covenant::AddAnima(uint32 anima)
{
    m_SaveFlags.AddFlag(eCovenantSaveFlags::SaveCovenant);
    SetAnima(_anima + anima);
}

void Covenant::InitializeCovenant()
{
    SetRenown(_renownLevel);
    SetAnima(_anima, true, true);
    SetSouls(_souls, true, true);

    _player->CompletedAchievement(sAchievementStore.LookupEntry(15247));
    _player->CompletedAchievement(sAchievementStore.LookupEntry(15248));
    _player->CompletedAchievement(sAchievementStore.LookupEntry(15249));
    _player->CompletedAchievement(sAchievementStore.LookupEntry(15250));
    _player->CompletedAchievement(sAchievementStore.LookupEntry(14934));
    _player->CompletedAchievement(sAchievementStore.LookupEntry(14936));
    _player->CompletedAchievement(sAchievementStore.LookupEntry(14937));
    _player->CompletedAchievement(sAchievementStore.LookupEntry(14790));
    static uint32 questsToComplete[] = {61550, 59317, 61057, 61541, 61542, 62919, 62918, 61542, 61388, 61058, 60504, 60111, 60110, 59919, 59596, 59597, 59343, 59325, 58797, 59316, 57898};
    for (auto questId : questsToComplete)
    {
        if (_player->GetQuestStatus(questId) == QUEST_STATUS_NONE)
            _player->RewardQuest(sObjectMgr->GetQuestTemplate(questId), LootItemType::Item, 0, _player, false);
    }
}

void Covenant::UpdateRenownRewards()
{
    if (!_player->GetCovenantMgr()->_loaded)
        return;

    _player->GetCovenantMgr()->LearnCovenantSpells(); // renown rewards

    // Check Renown
    auto covIdInt = _player->m_playerData->CovenantID;
    for (auto reward : sRenownRewardsStore)
    {
        if (reward->CovenantID != covIdInt)
            continue;

        if (reward->Level > GetRenownLevel())
            continue;

        if (_claimedRenownRewards.count(reward->ID))
            continue;

        if (reward->PlayerConditionID > 0)
            if (PlayerConditionEntry const* playerCondition = sPlayerConditionStore.LookupEntry(reward->PlayerConditionID))
                if (!ConditionMgr::IsPlayerMeetingCondition(_player, playerCondition))
                    continue;

        if (reward->QuestID > 0)
        {
            if (auto quest = sObjectMgr->GetQuestTemplate(reward->QuestID))
            {
                if (auto questStatus = _player->GetQuestStatus(reward->QuestID) == QUEST_STATUS_NONE)
                    _player->RewardQuest(quest, LootItemType::Item, 0, _player, false);
            }
        }

        if (reward->ItemID > 0 && !_player->GetSession()->GetCollectionMgr()->HasToy(reward->ItemID))
        {
            /// Check if they already have runeforge memory
            if (auto runeforgeLegendary = sDB2Manager.GetRuneforgeLegendaryAbilityEntryByItemID(reward->ItemID))
                if (_player->GetSession()->GetCollectionMgr()->HasRuneforgeMemory(runeforgeLegendary->ID))
                {
                    m_SaveFlags.AddFlag(eCovenantSaveFlags::SaveRenownRewards);
                    _claimedRenownRewards.insert(reward->ID);
                    continue;
                }

            switch (reward->ItemID)
            {
                case 186472: ///< Wisp of Memory
                    continue;
                default:
                    break;
            }

            if (_player->GetSession()->GetCollectionMgr()->HasToy(reward->ItemID))
                continue;

            if (!_player->AddItem(reward->ItemID, 1))
                _player->SendItemRetrievalMail(reward->ItemID, 1, ItemContext::NONE);
        }

        if (reward->CharTitlesID > 0)
        {
            if (auto titleEntry = sCharTitlesStore.LookupEntry(reward->CharTitlesID))
                _player->SetTitle(titleEntry);
        }

        // what other rewards to add?
        m_SaveFlags.AddFlag(eCovenantSaveFlags::SaveRenownRewards);
        _claimedRenownRewards.insert(reward->ID);
    }
}

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

void Conduit::FlagsUpdated(bool forceRemove /*= false*/)
{
    bool disabled = Flags == 0 || forceRemove;

    if (auto talentRank = sDB2Manager.GetTalentRankEntryByGarrTalentID(TalentEntryId, Rank > 1 ? Rank - 1 : 0))
    {
        if (talentRank->PerkSpellID > 0)
        {
            if (disabled)
            {
                //if (_player->HasSpell(talentRank->PerkSpellID))
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
        /// pig or not?
        Socket->SoulbindConduitRank = _player->GetCovenantMgr()->GetConduitRank(Socket->SoulbindConduitID);

        auto entries = sDB2Manager.GetSoulbindConduitRankBySoulbindConduitID(Socket->SoulbindConduitID);
        if (entries)
        {
            if (!disabled)
            {
                SoulbindConduitRankEntry const* currRank = nullptr;
                bool IsEnhanced = IsEnhancedConduit();
                for (auto entry : *entries)
                {
                    currRank = entry;
                    if (entry->RankIndex == Socket->SoulbindConduitRank + (IsEnhanced ? 2 : 0))
                    {
                        break;
                    }
                }

                if (currRank != nullptr)
                {
                    // activate socket spell.
                    // todo: research this more
                    _player->RemoveAurasDueToSpell(entries->at(0)->SpellID);
                    if (auto aura = _player->AddAura(currRank->SpellID))
                    {
                        if (auto eff = aura->GetEffect(EFFECT_0))
                        {
                            eff->ConduitRankEntry = currRank;
                            eff->ApplySpellMod(_player, false);
                            eff->SetAmount((int32)currRank->AuraPointsOverride); ///< Some are floats. How to handle this? - we can handle this by storing the SoulbindConduitRankEntry and scripting the effect in the SpellScript :)
                            eff->ApplySpellMod(_player, true);
                            eff->CalculateSpellMod();
                        }
                    }
                }
            }
            else
                _player->RemoveAurasDueToSpell(entries->at(0)->SpellID);
        }
    }
}

void Conduit::BuildGarrisonTalent(WorldPackets::Garrison::GarrisonTalent& talent) const
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

bool Conduit::IsEnhancedConduit()
{
    // TODO: Convert to lookup by map
    for (auto entry : sSoulbindConduitEnhancedSocketStore)
    {
        if (entry->GarrTalentID == TalentEntryId)
        {
            if (_player->MeetPlayerCondition(entry->PlayerConditionEntry))
                return true;
        }
    }

    return false;
}

int32 Conduit::GetSoulbindID() const
{
    auto requiredSoulbindId = static_cast<int32>(GetSoulbindIDFromTalentTreeId(TreeEntryId));
    return requiredSoulbindId;
}

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

void Covenant::SocketTalent(WorldPackets::Garrison::GarrisonSocketTalent& packet)
{
    // SMSG_GARRISON_APPLY_TALENT_SOCKET_DATA_CHANGES
    WorldPackets::Garrison::GarrisonApplyTalentSocketDataChanges response;
    response.GarrTypeID = CovenantMgr::TheShadowlands;
    //response.Sockets.resize(packet.Sockets.size());
    for (int i = 0; i < packet.Sockets.size(); ++i)
    {
        auto conduit = _player->GetCovenantMgr()->GetConduitByGarrTalentId(packet.Sockets[i].SoulbindConduitID);
        if (!conduit)
        {
            response.RemoveConduitIds.push_back(packet.Sockets[i].SoulbindConduitRank); // todo: find if this conduit is socketed
            continue;
        }

        // unapply before modifying
        // this has to be ran because Socket can reset
        conduit->FlagsUpdated(true);
        // TODO: Name these fields correctly.
        WorldPackets::Garrison::GarrisonTalentSocketChange socketChange;
        socketChange.ConduitID = packet.Sockets[i].SoulbindConduitID;

        if (packet.Sockets[i].SoulbindConduitRank != 0)
        {
            WorldPackets::Garrison::GarrisonTalentSocketData data;
            data.SoulbindConduitID = packet.Sockets[i].SoulbindConduitRank;
            data.SoulbindConduitRank = _player->GetCovenantMgr()->GetConduitRank(data.SoulbindConduitID); // probably the rank
            socketChange.Socket = data;
            conduit->Socket = data;
            // we apply here
            conduit->FlagsUpdated();
        }
        else
            conduit->Socket.reset();

        response.Sockets.push_back(socketChange);
    }
    _player->SendDirectMessage(response.Write());

    // just incase to remove auras for whatever reason, maybe it bug, but it's ok it will remove/apply
    _player->GetCovenantMgr()->UpdateAllConduitsForSoulbind();
    _player->GetCovenantMgr()->SetSaveConduits();
}

void Covenant::SaveToDB(CharacterDatabaseTransaction trans)
{
    if (m_SaveFlags.HasFlag(eCovenantSaveFlags::SaveCovenant))
    {
        auto stmt = CharacterDatabase.GetPreparedStatement(CHAR_REP_COVENANT);
        stmt->setUInt64(0, _player->GetGUID().GetCounter());
        stmt->setUInt32(1, static_cast<uint32>(GetCovenantID()));
        stmt->setUInt32(2, GetRenownLevel());
        stmt->setUInt32(3, GetAnima());
        stmt->setUInt32(4, GetSouls());
        trans->Append(stmt);

        m_SaveFlags.RemoveFlag(eCovenantSaveFlags::SaveCovenant);
    }

    if (m_SaveFlags.HasFlag(eCovenantSaveFlags::SaveRenownRewards))
    {
        if (!_claimedRenownRewards.empty())
        {
            auto stmt = CharacterDatabase.GetPreparedStatement(CHAR_REP_COVENANT_CLAIMED_RENOWN_REWARDS);
            stmt->setUInt64(0, _player->GetGUID().GetCounter());
            stmt->setUInt32(1, static_cast<uint32>(GetCovenantID()));

            std::stringstream ss;
            for (auto rewardId : _claimedRenownRewards)
                ss << rewardId << ",";
            stmt->setString(2, ss.str());
            trans->Append(stmt);
        }
        m_SaveFlags.RemoveFlag(eCovenantSaveFlags::SaveRenownRewards);
    }
}

void CovenantMgr::DisableAllConduits()
{
    auto covenantId = static_cast<uint32>(GetCovenant()->GetCovenantID());

    for (auto& itr : _conduits)
    {
        if (itr.second->CovenantID != covenantId)
            continue;

        itr.second->FlagsUpdated(true);
    }
    m_SaveFlags.AddFlag(eCovenantMgrSaveFlags::SaveConduits);
}

void CovenantMgr::DisableAllConduitsForSoulbind()
{
    // no soulbind - nothing to do. same for covenantid
    if (_player->m_playerData->SoulbindID == 0)
        return;

    auto covenantId = static_cast<uint32>(GetCovenant()->GetCovenantID());

    for (auto& itr : _conduits)
    {
        if (itr.second->CovenantID != covenantId)
            continue;

        if (itr.second->GetSoulbindID() == _player->m_playerData->SoulbindID)
            itr.second->FlagsUpdated(true);
    }
    m_SaveFlags.AddFlag(eCovenantMgrSaveFlags::SaveConduits);
}

void CovenantMgr::UpdateAllConduits()
{
    for (auto& itr : _conduits)
    {
        auto soulbind = itr.second->GetSoulbindID();
        // only track covenant
        if (soulbind == 0)
            continue;

        bool add = soulbind == _player->m_playerData->SoulbindID;
        itr.second->FlagsUpdated(!add);
    }
    m_SaveFlags.AddFlag(eCovenantMgrSaveFlags::SaveConduits);
}

void CovenantMgr::UpdateAllConduitsForSoulbind()
{
    if (_player->m_playerData->SoulbindID == 0)
        return;

    for (auto& itr : _conduits)
    {
        auto soulbind = itr.second->GetSoulbindID();
        if (soulbind == 0)
            continue;

        if (soulbind  == _player->m_playerData->SoulbindID)
            itr.second->FlagsUpdated();
    }
    m_SaveFlags.AddFlag(eCovenantMgrSaveFlags::SaveConduits);
}

void CovenantMgr::AddConduit(Conduit* conduit)
{
    _conduits[conduit->TalentEntryId] = conduit;
    m_SaveFlags.AddFlag(eCovenantMgrSaveFlags::SaveConduits);
}

void CovenantMgr::SetSaveConduits()
{
    m_SaveFlags.AddFlag(eCovenantMgrSaveFlags::SaveConduits);
}

CovenantMgr::CovenantMgr(Player* player) : _player(player), _currCovenantIndex(0), _loaded(false)
{
    _playerCovenants[0] = std::make_unique<Covenant>(CovenantID::None, _player);
    _playerCovenants[1] = std::make_unique<Covenant>(CovenantID::Kyrian, _player);
    _playerCovenants[2] = std::make_unique<Covenant>(CovenantID::Venthyr, _player);
    _playerCovenants[3] = std::make_unique<Covenant>(CovenantID::NightFae, _player);
    _playerCovenants[4] = std::make_unique<Covenant>(CovenantID::Necrolord, _player);
}

CovenantMgr::~CovenantMgr()
{
    for (auto it = _conduits.begin(); it != _conduits.end(); ++it)
        delete it->second;
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

            uint32 covenantId = fields[0].GetUInt32();
            uint32 GarrTalentID = fields[1].GetUInt32();
            uint32 GarrTalentTreeID = fields[2].GetUInt32();

            Conduit* conduit = new Conduit(_player);

            conduit->TalentEntryId = GarrTalentID;
            conduit->TreeEntryId = GarrTalentTreeID;
            conduit->CovenantID = covenantId;
            conduit->Rank = fields[3].GetUInt32();
            conduit->Flags = fields[4].GetUInt32();
            conduit->ResearchStartTime = fields[5].GetUInt64();

            uint32 SoulbindConduitID = fields[6].GetUInt32();
            if (SoulbindConduitID > 0)
            {
                WorldPackets::Garrison::GarrisonTalentSocketData data;
                data.SoulbindConduitID = SoulbindConduitID;
                data.SoulbindConduitRank = fields[7].GetUInt32();
                conduit->Socket = data;
            }

            AddConduit(conduit);

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
            cov->SetAnima(Anima, false);
            cov->SetSouls(Souls, false);

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

    result = holder.GetPreparedResult(PLAYER_LOGIN_QUERY_LOAD_CHARACTER_COVENANT_CLAIMED_RENOWN_REWARDS);

    if (result)
    {
        do
        {
            auto fields = result->Fetch();
            auto covenant = fields[0].GetUInt32();

            // bad db data.
            if (covenant > 4)
                continue;

            auto cov = _playerCovenants[covenant].get();

            for (std::string_view rewardId : Trinity::Tokenize(fields[1].GetStringView(), ',', false))
                if (Optional<uint32> reward = Trinity::StringTo<uint32>(rewardId))
                    cov->_claimedRenownRewards.insert(reward.value());

        } while (result->NextRow());
    }
    _loaded = true;
}

void CovenantMgr::SaveToDB(CharacterDatabaseTransaction trans)
{
    std::ostringstream ss;
    for (auto const& itr : _playerCovenants)
    {
        if (itr->GetCovenantID() == CovenantID::None)
            continue;

        itr->SaveToDB(trans);
    }

    if (m_SaveFlags.HasFlag(eCovenantMgrSaveFlags::SaveConduits))
    {
        for (auto const& itr : _conduits)
        {
            auto const& conduit = itr.second;

            auto index = 0;

            auto stmt = CharacterDatabase.GetPreparedStatement(CHAR_REP_COVENANT_CONDUITS);
            stmt->setUInt64(index++, _player->GetGUID().GetCounter());
            stmt->setUInt32(index++, conduit->CovenantID);
            stmt->setUInt32(index++, conduit->TalentEntryId);
            stmt->setUInt32(index++, conduit->TreeEntryId);
            stmt->setUInt32(index++, conduit->Rank);
            stmt->setUInt32(index++, conduit->Flags);
            stmt->setUInt64(index++, conduit->ResearchStartTime);

            uint32 SoulbindConduitID = 0;
            uint32 SoulbindConduitRank = 0;

            if (conduit->Socket.has_value())
            {
                SoulbindConduitID = conduit->Socket->SoulbindConduitID;
                SoulbindConduitRank = conduit->Socket->SoulbindConduitRank;
            }

            stmt->setUInt32(index++, SoulbindConduitID);
            stmt->setUInt32(index++, SoulbindConduitRank);
            trans->Append(stmt);
        }
        m_SaveFlags.RemoveFlag(eCovenantMgrSaveFlags::SaveConduits);
    }

    if (m_SaveFlags.HasFlag(eCovenantMgrSaveFlags::SaveSoulbindSpecs))
    {
        for (auto const& itr : _covenantSoulbinds)
        {
            auto stmt = CharacterDatabase.GetPreparedStatement(CHAR_REP_COVENANT_SOULBIND);
            stmt->setUInt64(0, _player->GetGUID().GetCounter());
            stmt->setUInt32(1, itr.first);
            stmt->setUInt32(2, itr.second.SpecId);
            stmt->setUInt32(3, itr.second.Soulbind);
            trans->Append(stmt);
        }
        m_SaveFlags.RemoveFlag(eCovenantMgrSaveFlags::SaveSoulbindSpecs);
    }

    if (m_SaveFlags.HasFlag(eCovenantMgrSaveFlags::SaveCollections))
    {
        for (auto const& itr : CollectionEntries)
        {
            auto stmt = CharacterDatabase.GetPreparedStatement(CHAR_REP_COVENANT_COLLECTIONS);
            stmt->setUInt64(0, _player->GetGUID().GetCounter());
            stmt->setInt32(1, itr.first);
            stmt->setInt32(2, itr.second);
            trans->Append(stmt);
        }

        m_SaveFlags.RemoveFlag(eCovenantMgrSaveFlags::SaveCollections);
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
    DisableAllConduits();

    size_t newCovenantId = -1;

    switch (covenant)
    {
        case CovenantID::Kyrian: newCovenantId = 1; break;
        case CovenantID::Venthyr: newCovenantId = 2; break;
        case CovenantID::NightFae: newCovenantId = 3; break;
        case CovenantID::Necrolord: newCovenantId = 4; break;
        default:
            break;
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
    if (_loaded)
        GetCovenant()->UpdateRenownRewards();
}

void CovenantMgr::LearnCovenantSpells()
{
    auto spells = GetCovenantSpells(GetCovenant()->GetCovenantID());
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

std::list<uint32> CovenantMgr::GetCovenantSpells(CovenantID covenantId)
{
    std::list<uint32> SpellsToLearn;

    uint32 RequiredCovenantPreviewID = 0;

    switch (covenantId)
    {
        case CovenantID::Kyrian: RequiredCovenantPreviewID = 2; break;
        case CovenantID::Venthyr: RequiredCovenantPreviewID = 7; break;
        case CovenantID::Necrolord: RequiredCovenantPreviewID = 6; break;
        case CovenantID::NightFae: RequiredCovenantPreviewID = 5; break;
        default:
            RequiredCovenantPreviewID = 99999; /// Unlearning case, currently only affects shadowlands covenants
            break;
    }

    //auto soulbind = static_cast<uint32>(GetSoulbindUIDisplayInfoIdFromSoulbindID(GetCovenant()->GetSoulbindID()));

    ChrClassesEntry const* clsEntry = sChrClassesStore.LookupEntry(_player->GetClass());
    auto family = clsEntry->SpellClassSet;

    /// Shadowlands only
    for (auto entry : sUiCovenantAbilityEntry)
    {
        if (RequiredCovenantPreviewID != 99999 && entry->CovenantPreviewID != RequiredCovenantPreviewID)
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
        // Should be handled by conduit system
        // else if (entry->AbilityType == 2)
        // {
        //     // Soulbind
        //     if (entry->SoulbindDisplayInfoID == soulbind)
        //         SpellsToLearn.push_back(entry->SpellID);
        // }
    }

    // We can use UICovenantAbility.db2 here.
    switch (covenantId)
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
        default: /// Unlearning case, currently only effects Shadowlands covenants
            SpellsToLearn.push_back(321076);
            SpellsToLearn.push_back(321079);
            SpellsToLearn.push_back(321078);
            SpellsToLearn.push_back(321077);
            break;
    }

    /// @TODO: Check in dragonflight if we are suppoed to remove renown reward spells on swap covenant

    // Check Renown
    auto covIdInt = static_cast<int32>(covenantId);
    for (auto reward : sRenownRewardsStore)
    {
        if (RequiredCovenantPreviewID != 99999 && reward->CovenantID != covIdInt)
            continue;

        if (RequiredCovenantPreviewID != 99999 && reward->Level > GetCovenant()->GetRenownLevel())
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
        if (prop->ItemLevel > item->GetItemLevel(_player))
            break;

        rank++;
    }

    // SMSG_GARRISON_COLLECTION_UPDATE_ENTRY
    WorldPackets::Garrison::GarrisonCollectionUpdateEntry packet;

    packet.GarrTypeID = CovenantMgr::TheShadowlands;
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

    UpdateAllConduitsForSoulbind();
    m_SaveFlags.AddFlag(eCovenantMgrSaveFlags::SaveCollections);
}

void CovenantMgr::AddGarrisonInfo(WorldPackets::Garrison::GetGarrisonInfoResult& garrisonInfo)
{
    WorldPackets::Garrison::GarrisonInfo cov;

    cov.GarrTypeID = CovenantMgr::TheShadowlands; // GarrType.db2
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


void CovenantMgr::LearnConduit(GarrTalentEntry const* talent, GarrTalentTreeEntry const* tree, uint32 Rank /*= 1*/)
{
    Conduit* conduit = GetConduitByGarrTalentId(talent->ID);

    auto soulbindId = GetSoulbindIDFromTalentTreeId(tree->ID);

    if (!conduit)
    {
        conduit = new Conduit(_player);
        conduit->TalentEntryId = talent->ID;
        conduit->TreeEntryId = tree->ID;
        conduit->Flags = GarrisonTalentFlags::TalentFlagEnabled;
        conduit->CovenantID = static_cast<int32>(GetCovenantIDFromSoulbindID(soulbindId));
        AddConduit(conduit);
    }

    // unapply
    conduit->FlagsUpdated(true);

    // apply rank after unapplying
    conduit->Rank = Rank;

    // SMSG_GARRISON_RESEARCH_TALENT_RESULT send instead
    //_player->SendGarrisonInfoResult();
    // ServerToClient: SMSG_GARRISON_RESEARCH_TALENT_RESULT (0x296C) Length: 30 ConnIdx: 1 Time: 04/05/2022 23:54:19.075 Number: 15355
    // UnkInt1: 0
    // GarrTypeID: 111
    // unkbit: True

    WorldPackets::Garrison::GarrisonResearchTalentResult result;
    result.GarrTypeID = CovenantMgr::TheShadowlands;
    conduit->BuildGarrisonTalent(result.talent);
    _player->SendDirectMessage(result.Write());

    // SMSG_LEARNED_SPELLS - need implement GarrTalentRank.db2
    if (soulbindId == SoulbindID::None || static_cast<int32>(soulbindId) == _player->m_playerData->SoulbindID)
        conduit->FlagsUpdated();
    // SMSG_CRITERIA_UPDATE Criteria ID, 30952, 3x Quantity
    // SMSG_GARRISON_TALENT_COMPLETED
    WorldPackets::Garrison::GarrisonTalentCompleted result2;
    result2.GarrTypeID = CovenantMgr::TheShadowlands;
    result2.GarrTalentID = talent->ID;
    result2.UnkInt1 = Rank;
    _player->SendDirectMessage(result2.Write());
    SetSaveConduits();
}

void CovenantMgr::BuildGarrisonPacket(WorldPackets::Garrison::GarrisonInfo& result)
{
    auto covenant = GetCovenant();

    for (auto& itr : _conduits)
    {
        WorldPackets::Garrison::GarrisonTalent talent;
        itr.second->BuildGarrisonTalent(talent); // maybe make const
        result.Talents.push_back(talent);
    }

    // DF
    for (int i = 0; i < 6; ++i)
    {
        WorldPackets::Garrison::GarrisonTalent talent;
        talent.Flags = 1;
        talent.GarrTalentID = 2078 + i;
        talent.Rank = 1;
        talent.ResearchStartTime = 1662496826;
        result.Talents.push_back(talent);
    }
}

void CovenantMgr::LearnTalent(WorldPackets::Garrison::GarrisonLearnTalent& researchResult)
{
    auto talent = sGarrTalentStore.LookupEntry(researchResult.GarrTalentID);
    if (!talent)
        return;

    // don't trust client
    uint32 SoulbindID = static_cast<uint32>(GetSoulbindIDFromTalentTreeId(talent->GarrTalentTreeID));//researchResult.SoulbindID;

    // SMSG_UNLEARNED_SPELLS
    // Sent down below.

    uint32 covId = (uint32)_currCovenantIndex;
    auto covenant = GetCovenant();

    auto AddConduitToListIfNeed([covenant, covId, SoulbindID, this](GarrTalentEntry const* pTalent)
    {
        auto it = _conduits.find(pTalent->ID);
        if (it == _conduits.end())
        {
            Conduit* conduit = new Conduit(_player);
            conduit->TalentEntryId = pTalent->ID;
            conduit->TreeEntryId = pTalent->GarrTalentTreeID;
            conduit->Flags = GarrisonTalentFlags::TalentFlagEnabled;

            AddConduit(conduit);

            //// TODO: Verify this. - seems fine
            WorldPackets::Garrison::GarrisonResearchTalentResult result;
            result.GarrTypeID = CovenantMgr::TheShadowlands;
            conduit->BuildGarrisonTalent(result.talent);
            _player->SendDirectMessage(result.Write());

            WorldPackets::Garrison::GarrisonTalentCompleted result2;
            result2.GarrTypeID = CovenantMgr::TheShadowlands;
            result2.GarrTalentID = pTalent->ID;
            _player->SendDirectMessage(result2.Write());
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

    WorldPackets::Garrison::GarrisonSwitchTalentTreeBranch packet;
    packet.GarrTypeID = CovenantMgr::TheShadowlands;

    for (auto itr : _conduits)
    {
        auto entry = sGarrTalentStore.LookupEntry(itr.second->TalentEntryId);

        if (TalentTiersToCheck.count(entry->Tier))
        {
            if (entry->GarrTalentTreeID != talent->GarrTalentTreeID)
                continue;

            if (itr.second->TalentEntryId == talent->ID || entry->PrerequesiteTalentID == talent->ID)
            {
                itr.second->Flags = GarrisonTalentFlags::TalentFlagEnabled;
            }
            else
            {
                itr.second->Flags = GarrisonTalentFlags::TalentFlagDisabled;
            }

            if (researchResult.SoulbindID == _player->m_playerData->SoulbindID)
            {
                itr.second->FlagsUpdated(true);
                itr.second->FlagsUpdated();
            }
            WorldPackets::Garrison::GarrisonTalent garrTalentPacket;
            itr.second->BuildGarrisonTalent(garrTalentPacket);
            packet.Talents.push_back(garrTalentPacket);
        }
    }

    SetSaveConduits();
    _player->SendDirectMessage(packet.Write());
}

Conduit* CovenantMgr::GetConduitByGarrTalentId(uint32 garrTalentId)
{
    auto it = _conduits.find(garrTalentId);
    if (it == _conduits.end())
        return nullptr;

    return it->second;
}

void CovenantMgr::SetSoulbind(SoulbindID soulbind, bool sendPacket /*= false*/)
{
    auto covenant = GetCovenant();
    if (covenant->GetCovenantID() == CovenantID::None)
        return;

    // Cheating check
    auto soulbindEntry = sSoulbindStore.LookupEntry(static_cast<uint32>(soulbind));
    if (!soulbindEntry || soulbindEntry->CovenantID != _player->m_playerData->CovenantID)
        return;

    covenant->SetSoulbind(soulbind, sendPacket);
    m_SaveFlags.AddFlag(eCovenantMgrSaveFlags::SaveSoulbindSpecs);

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

    m_SaveFlags.AddFlag(eCovenantMgrSaveFlags::SaveSoulbindSpecs);

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
    auto covenant = GetCovenant();
    if (!covenant)
        return;

    UpdateAllConduits();
}
