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

Covenant::Covenant(CovenantID covId, Player* player) : _covenantId(covId), _player(player), _soulbindId(SoulbindID::None), _renownLevel(80), _anima(0), _souls(0)
{
}

void Covenant::SetSoulbind(SoulbindID soulbind)
{
    _soulbindId = soulbind;
    _player->SetSoulbind(static_cast<int32>(_soulbindId));

    // SMSG_GARRISON_ADD_SPEC_GROUPS send instead.
    WorldPackets::Garrison::AddSpecGroups packet;
    packet.GarrTypeID = 111;
    packet.SpecGroups.resize(1);
    packet.SpecGroups[0].ChrSpecializationID = _player->GetSpecializationId();
    packet.SpecGroups[0].SoulbindID = static_cast<int32>(GetSoulbindID());
    _player->SendDirectMessage(packet.Write());
}

void Covenant::SetRenown(int32 renown)
{
    _renownLevel = renown;
    _player->ModifyCurrency(1822, renown, true, false, true);
    _player->GetCovenantMgr()->LearnCovenantSpells(); // renown rewards

    // Check Renown
    auto covIdInt = static_cast<int32>(GetCovenantID());
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
    _player->ModifyCurrency(1813, anima, true, false, true);
}

void Covenant::SetSouls(uint32 souls)
{
    _souls = souls;
    _player->ModifyCurrency(1810, souls, true, false, true);
}

void Covenant::InitializeCovenant()
{
    SetRenown(_renownLevel);
    SetAnima(_anima);
    SetSouls(_souls);

    _player->CompletedAchievement(sAchievementStore.LookupEntry(15247));
    _player->CompletedAchievement(sAchievementStore.LookupEntry(15248));
    _player->CompletedAchievement(sAchievementStore.LookupEntry(15249));
    _player->CompletedAchievement(sAchievementStore.LookupEntry(15250));
    _player->CompletedAchievement(sAchievementStore.LookupEntry(14934));
    _player->CompletedAchievement(sAchievementStore.LookupEntry(14936));
    _player->CompletedAchievement(sAchievementStore.LookupEntry(14937));
    _player->CompletedAchievement(sAchievementStore.LookupEntry(14790));
}

void Covenant::LearnConduit(GarrTalentEntry const* talent, GarrTalentTreeEntry const* tree)
{
    Conduit conduit;
    conduit.TalentEntry = talent;
    conduit.TreeEntry = tree;

    if (std::find(_conduits.begin(), _conduits.end(), conduit) == _conduits.end())
        _conduits.emplace_back(conduit);

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
    if (auto talentRank = sDB2Manager.GetTalentRankEntryByGarrTalentID(talent->ID))
    {
        if (talentRank->PerkSpellID > 0)
        {
            if (!_player->HasSpell(talentRank->PerkSpellID))
                _player->LearnSpell(talentRank->PerkSpellID, false);
        }
    }
    // SMSG_CRITERIA_UPDATE Criteria ID, 30952, 3x Quantity
    // SMSG_GARRISON_TALENT_COMPLETED
    WorldPackets::Garrison::GarrisonTalentCompleted result2;
    result2.GarrTypeID = 111;
    result2.GarrTalentID = talent->ID;
    _player->SendDirectMessage(result2.Write());
}

void Conduit::BuildGarrisonTalent(WorldPackets::Garrison::GarrisonTalent& talent)
{
    // GarrTalentID: 864
    // Rank: 1
    // ResearchStartTime: 1649217259
    // Flags: 1
    // HasSocket: False
    talent.GarrTalentID = TalentEntry->ID; // GarrTalent.dbc - Contains GarrTalentTreeID, which is the soulbind. 997 - 304 Endurance Conduit
    talent.Rank = 1; // not sure
    talent.Flags = 1; // not 100% sure
    talent.ResearchStartTime = GameTime::GetGameTime(); // not 100% sure. other garrison packets used this.
    if (Socket.has_value())
        talent.Socket = Socket;
}

void Covenant::BuildGarrisonPacket(WorldPackets::Garrison::GarrisonInfo& result)
{
    for (auto& conduit : _conduits)
    {
        WorldPackets::Garrison::GarrisonTalent talent;
        conduit.BuildGarrisonTalent(talent);
        result.Talents.push_back(talent);
    }
}

void Covenant::SocketTalent(WorldPackets::Garrison::GarrisonSocketTalent& packet)
{
    // SMSG_GARRISON_APPLY_TALENT_SOCKET_DATA_CHANGES
    WorldPackets::Garrison::GarrisonApplyTalentSocketDataChanges response;
    response.GarrTypeID = 111;
    //response.Sockets.resize(packet.Sockets.size());
    for (int i = 0; i < packet.Sockets.size(); ++i)
    {
        if (packet.Sockets[i].SoulbindConduitID != 0)
        {
            WorldPackets::Garrison::GarrisonTalentSocketChange socketChange;
            socketChange.ConduitID = packet.Sockets[i].SoulbindConduitID;
            WorldPackets::Garrison::GarrisonTalentSocketData data;
            data.SoulbindConduitID = packet.Sockets[i].SoulbindConduitRank;
            data.SoulbindConduitRank = 0; // probably the rank
            socketChange.Socket = data;
            response.Sockets.push_back(socketChange);
        }
        else
            response.RemoveConduitIds.push_back(packet.Sockets[i].SoulbindConduitID);
    }
    _player->SendDirectMessage(response.Write());
}

void Covenant::LearnTalent(WorldPackets::Garrison::GarrisonLearnTalent& researchResult)
{
    auto talent = sGarrTalentStore.LookupEntry(researchResult.GarrTalentID);
    if (!talent)
        return;

    TC_LOG_TRACE("network.opcode", "GarrisonLearnTalent: GarrTalentID %u UnkInt1 %u", researchResult.GarrTalentID, researchResult.UnkInt1);
    // Might be talentTier in researchResult. Have to verify.

    // SMSG_UNLEARNED_SPELLS
    // Need to track the OLD learned spells. possibly ordering by their Tier?
    // Also need to check Spells with pre-requestiteTalentIds
    //if (auto talentRank = sDB2Manager.GetTalentRankEntryByGarrTalentID(talent->ID))
    //{
    //    if (talentRank->PerkSpellID > 0)
    //    {
    //        if (!_player->HasSpell(talentRank->PerkSpellID))
    //            _player->LearnSpell(talentRank->PerkSpellID, false);
    //    }
    //}

    // SMSG_GARRISON_SWITCH_TALENT_TREE_BRANCH
    // ServerToClient: SMSG_GARRISON_SWITCH_TALENT_TREE_BRANCH(0x29AA) Length : 50 ConnIdx : 1 Time : 04 / 06 / 2022 15 : 55 : 14.871 Number : 3406
    // GarrTypeID : 111
    // Count : 2
    // GarrTalentID : 850
    // Rank : 1
    // ResearchStartTime : 1649223627
    // Flags : 0
    // HasSocket : False
    // GarrTalentID : 1009
    // Rank : 1
    // ResearchStartTime : 1649274916
    // Flags : 1
    // HasSocket : False
    WorldPackets::Garrison::GarrisonSwitchTalentTreeBranch packet;
    packet.GarrTypeID = 111;
    // possible resize to number of results in a row.
    for (auto garrTalent : sGarrTalentStore)
    {
        if (garrTalent->Tier == garrTalent->Tier && garrTalent->GarrTalentTreeID == talent->GarrTalentTreeID)
        {
            WorldPackets::Garrison::GarrisonTalent garrTalentPacket;

            garrTalentPacket.GarrTalentID = garrTalent->ID;
            garrTalentPacket.Flags = garrTalent->ID == researchResult.GarrTalentID ? GarrisonTalentFlags::TalentFlagEnabled : GarrisonTalentFlags::TalentFlagDisabled;
            garrTalentPacket.Rank = 1;
            garrTalentPacket.ResearchStartTime = GameTime::GetGameTimeMS();

            packet.Talents.push_back(garrTalentPacket);
        }
    }
    //packet.Talents.resize(2);
    _player->SendDirectMessage(packet.Write());
}

CovenantMgr::CovenantMgr(Player* player) : _player(player), _currCovenantIndex(0)
{
    _playerCovenants[0] = std::make_unique<Covenant>(CovenantID::None, _player);
    _playerCovenants[1] = std::make_unique<Covenant>(CovenantID::Kyrian, _player);
    _playerCovenants[2] = std::make_unique<Covenant>(CovenantID::Venthyr, _player);
    _playerCovenants[3] = std::make_unique<Covenant>(CovenantID::NightFae, _player);
    _playerCovenants[4] = std::make_unique<Covenant>(CovenantID::Necrolord, _player);
}

void CovenantMgr::LoadFromDB()
{
    // Test
    // SetCovenant(CovenantID::Kyrian);
}

void CovenantMgr::SaveToDB(CharacterDatabaseTransaction trans)
{

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
    uint32 rank = 1;

    // SMSG_GARRISON_COLLECTION_UPDATE_ENTRY
    WorldPackets::Garrison::GarrisonCollectionUpdateEntry packet;

    packet.GarrTypeID = 111;
    packet.UnkInt2 = 1; // Type.
    packet.Socket.SoulbindConduitID = conduitId;
    packet.Socket.SoulbindConduitRank = rank;
    _player->SendDirectMessage(packet.Write());

    auto itr = std::find(CollectionEntries.begin(), CollectionEntries.end(), conduitId);
    if (itr != CollectionEntries.end())
    {
        itr->Rank = rank;
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
    cov.Collections[0].Entries = CollectionEntries;

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
    GetCovenant()->BuildGarrisonPacket(cov);

    garrisonInfo.Garrisons.push_back(cov);
}

// Packets:
// CMSG_REQUEST_COVENANT_CALLINGS
// SMSG_COVENANT_CALLINGS_AVAILABILITY_RESPONSE
//      AreCallingsUnlocked: True
//      [0] BountyID: 239
//      [1] BountyID : 242
//      [2] BountyID : 255
// CMSG_COVENANT_RENOWN_REQUEST_CATCHUP_STATE
// SMSG_COVENANT_RENOWN_SEND_CATCHUP_STATE
//
// Spells
// 341427  - Spell (Learning)
// SPELL_EFFECT_LEARN_SOULBIND_CONDUIT

// Soulbind.db2
// SoulbindConduit.db2
// SoulbindConduitItem.db2
// SoulbindConduitRank.db2
// UICovenantAbility.db2

// CMSG_ACTIVATE_SOULBIND
// SMSG_ACTIVATE_SOULBIND_FAILED
// SMSG_DISPLAY_SOULBIND_UPDATE_MESSAGE
// CMSG_GARRISON_RESEARCH_TALENT
// CMSG_GARRISON_LEARN_TALENT
