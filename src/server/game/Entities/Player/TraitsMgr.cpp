/// WRITTEN BY ARTAMEDES FOR SHADOWS-EMBRACE
/// 9-8-22

/// Game
#include "DB2Stores.h"
#include "ChallengeMode.h"
#include "InstanceScript.h"
#include "Player.h"
#include "TalentPackets.h"
#include "TraitsMgr.h"
#include "SpellHistory.h"
#include "SpellInfo.h"

////////////////////////////////////////////////////////////////////////

Specialization::Specialization(Player* player, ChrSpecializationEntry const* specEntry) : _player(player), _specId(specEntry->ID)
{
    for (int i = 0; i < MAX_PVP_TALENT_SLOTS; ++i)
        _pvpTalents[i] = 0;
}

void Specialization::BuildUpdateTalentDataPacket(WorldPackets::Talent::TalentGroupInfo& info)
{
    info.SpecID = _specId;
    info.PvPTalents.resize(MAX_PVP_TALENT_SLOTS);
    for (uint8 i = 0; i < MAX_PVP_TALENT_SLOTS; ++i)
    {
        info.PvPTalents[i].PvPTalentID = _pvpTalents[i];
        info.PvPTalents[i].Slot        = i;
    }
}

void Specialization::BuildActiveGlyphsPacket(WorldPackets::Talent::ActiveGlyphs& activeGlyphs)
{
    activeGlyphs.Glyphs.reserve(_glyphs.size());
    for (uint32 glyphId : _glyphs)
        if (std::vector<uint32> const* bindableSpells = sDB2Manager.GetGlyphBindableSpells(glyphId))
            for (uint32 bindableSpell : *bindableSpells)
                if (_player->HasSpell(bindableSpell) && _player->m_overrideSpells.find(bindableSpell) == _player->m_overrideSpells.end())
                    activeGlyphs.Glyphs.emplace_back(uint32(bindableSpell), uint16(glyphId));
}

void Specialization::TogglePVPTalents(bool on)
{
    for (uint16 pvpTalent : _pvpTalents)
    {
        if (PvpTalentEntry const* pvpTalentInfo = sPvpTalentStore.LookupEntry(pvpTalent))
        {
            if (on)
            {
                _player->LearnSpell(pvpTalentInfo->SpellID, false);
                if (pvpTalentInfo->OverridesSpellID)
                    _player->AddOverrideSpell(pvpTalentInfo->OverridesSpellID, pvpTalentInfo->SpellID);
            }
            else
            {
                if (pvpTalentInfo->OverridesSpellID)
                    _player->RemoveOverrideSpell(pvpTalentInfo->OverridesSpellID, pvpTalentInfo->SpellID);
                _player->RemoveSpell(pvpTalentInfo->SpellID, true);
            }
        }
    }
}

void Specialization::RemoveGlyphAuras()
{
}

void Specialization::LoadGlyphAuras()
{
    for (uint32 glyphId : _glyphs)
        _player->CastSpell(_player, sGlyphPropertiesStore.AssertEntry(glyphId)->SpellID, true);
}

void Specialization::SetPVPTalent(uint16 pvpTalentId, uint8 slot)
{
    for (uint16& oldTalent : _pvpTalents)
        if (oldTalent == pvpTalentId)
            oldTalent = 0;

    _pvpTalents[slot] = pvpTalentId;
}

////////////////////////////////////////////////////////////////////////

TraitsMgr::TraitsMgr(Player* player) : _player(player)
{
}

TraitsMgr::~TraitsMgr()
{
    for (Specialization* spec : _specializations)
        delete spec;
    for (auto it = _traits.begin(); it != _traits.end(); ++it)
        delete it->second;

    // activeTrait should have been deleted above
    _activeTrait = nullptr;
}

void TraitsMgr::Setup()
{
    _specializations.reserve(MAX_SPECIALIZATIONS);
    for (uint8 i = 0; i < MAX_SPECIALIZATIONS; ++i)
    {
        ChrSpecializationEntry const* spec = sDB2Manager.GetChrSpecializationByIndex(_player->GetClass(), i);
        if (!spec)
            continue;

        _specializations.emplace_back(new Specialization(_player, spec));
    }

    _player->SetCurrentConfigID(_nextConfigId++);
}

void TraitsMgr::LoadFromDB(CharacterDatabaseQueryHolder const& holder)
{
}

void TraitsMgr::SendUpdateTalentData()
{
    WorldPackets::Talent::UpdateTalentData packet;

    packet.Info.ActiveGroup = GetActiveTalentGroupSafe();
    packet.Info.PrimarySpecialization = _player->GetSpecializationId();
    packet.Info.TalentGroups.resize(_specializations.size());

    for (uint32 i = 0; i < _specializations.size(); ++i)
        _specializations[i]->BuildUpdateTalentDataPacket(packet.Info.TalentGroups[i]);

    _player->SendDirectMessage(packet.Write());
}

void TraitsMgr::SetActiveTalentGroup(int8 orderIndex)
{
    if (_activeTalentGroup == orderIndex)
    {
        TC_LOG_ERROR("player.talents", "Same talent group was tried to set!");
        return;
    }

    auto newSpecialization = GetSpecialization(orderIndex);

    if (!newSpecialization)
    {
        TC_LOG_ERROR("player.talents", "Attempted to swap spec on invalid spec");
        return;
    }

    auto currSpecialization = GetActiveSpecialization();

    // specialization spells is already unlearned in Player::ActivateSpecialization

    currSpecialization->RemoveGlyphAuras();
    currSpecialization->TogglePVPTalents(false);

    _activeTalentGroup = orderIndex;

    newSpecialization->LoadGlyphAuras();
    newSpecialization->TogglePVPTalents(true);

    // specialization spells is are learned in Player::ActivateSpecialization
    // maybe should move to maintain clean
}

Specialization* TraitsMgr::GetActiveSpecialization()
{
    if (_activeTalentGroup == -1)
        return nullptr;

    return _specializations[_activeTalentGroup];
}

Specialization* TraitsMgr::GetSpecialization(int8 orderIndex)
{
    if (orderIndex == -1 || orderIndex >= _specializations.size())
        return nullptr;

    return _specializations[orderIndex];
}

Trait* TraitsMgr::GetActiveTrait()
{
    return _activeTrait;
}

void TraitsMgr::SendActiveGlyphs(bool fullUpdate /*= false*/)
{
    WorldPackets::Talent::ActiveGlyphs activeGlyphs;

    if (auto spec = GetActiveSpecialization())
        spec->BuildActiveGlyphsPacket(activeGlyphs);

    activeGlyphs.IsFullUpdate = fullUpdate;
    _player->SendDirectMessage(activeGlyphs.Write());
}

void TraitsMgr::LoadGlyphAuras()
{
    if (_activeTalentGroup == -1)
        return;

    _specializations[_activeTalentGroup]->LoadGlyphAuras();
}

void TraitsMgr::TogglePVPTalents(bool on)
{
    if (auto specialization = GetActiveSpecialization())
        specialization->TogglePVPTalents(on);
}

TalentLearnResult TraitsMgr::LearnPVPTalent(uint16 pvpTalentId, uint8 slot, int32* spellOnCooldown)
{
    auto currSpec = GetActiveSpecialization();
    if (!currSpec)
        return TalentLearnResult::NoPrimaryTreeSelected;

    auto pvpTalentEntry = sPvpTalentStore.LookupEntry(pvpTalentId);
    if (!pvpTalentEntry)
        return TalentLearnResult::Unk;

    if (pvpTalentEntry->SpecID != currSpec->GetSpecId())
        return TalentLearnResult::NoPrimaryTreeSelected;

    if (auto instance = _player->GetInstanceScript())
        if (auto challenge = instance->GetChallenge())
            return TalentLearnResult::CantDoThatChallengeModeActive;

    if (_player->IsInCombat())
        return TalentLearnResult::AffectingCombat;

    if (!_player->HasPlayerFlag(PLAYER_FLAGS_RESTING) && !_player->HasUnitFlag2(UNIT_FLAG2_ALLOW_CHANGING_TALENTS))
        return TalentLearnResult::RestArea;

    if (slot > 3)
        return TalentLearnResult::NoPrimaryTreeSelected;

    if (auto spellInfo = sSpellMgr->GetSpellInfo(pvpTalentEntry->SpellID))
    {
        if (_player->GetSpellHistory()->HasCooldown(spellInfo))
        {
            *spellOnCooldown = pvpTalentEntry->SpellID;
            return TalentLearnResult::SpellOnCooldown;
        }
    }

    currSpec->SetPVPTalent(pvpTalentId, slot);

    return TalentLearnResult::Ok;
}

Trait::Trait(Player* player, uint32 configId, uint32 specId) : _player(player), _configID(configId), _specializationID(specId)
{
}

void Trait::SetConfigName(std::string_view configName)
{
    _configName = configName;
}

TraitTalent::TraitTalent(Player* player, Trait* trait) : _player(player), _trait(trait)
{
}
