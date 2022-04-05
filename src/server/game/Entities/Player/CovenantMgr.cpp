#include "CovenantMgr.h"
#include "Item.h"
#include "Player.h"
#include "DB2Stores.h"
#include "WorldSession.h"
#include "SpellInfo.h"
#include "SpellMgr.h"
#include "CovenantPackets.h"
#include "GarrisonPackets.h"

Covenant::Covenant(CovenantID covId, Player* player) : _covenantId(covId), _player(player), _soulbindId(SoulbindID::None), _renownLevel(1), _anima(0), _souls(0)
{
}

void Covenant::SetSoulbind(SoulbindID soulbind)
{
    _soulbindId = soulbind;
    _player->SetSoulbind(static_cast<int32>(_soulbindId));
}

void Covenant::SetRenown(int32 renown)
{
    _renownLevel = renown;
    _player->ModifyCurrency(1822, renown, true, false, true);
    _player->GetCovenantMgr()->LearnCovenantSpells(); // renown rewards
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
}

void CovenantMgr::AddGarrisonInfo(WorldPackets::Garrison::GetGarrisonInfoResult& garrisonInfo)
{
    WorldPackets::Garrison::GarrisonInfo cov;

    cov.GarrTypeID = 111; // GarrType.db2
    cov.GarrSiteID = 299; // don't know
    cov.GarrSiteLevelID = 864; // GarrSiteLevel.db2

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
