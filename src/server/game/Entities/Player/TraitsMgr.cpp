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

uint16 Specialization::GetPVPTalent(uint8 slot) const
{
    if (slot >= MAX_PVP_TALENT_SLOTS)
        return 0;

    return _pvpTalents[slot];
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

    //std::sort(_specializations.begin(), _specializations.end(), [](Specialization* a, Specialization* b)
    //{
    //    return a->GetSpecId() > b->GetSpecId();
    //});

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

void TraitsMgr::SetActiveTalentGroup(int8 orderIndex, bool force /*= false*/)
{
    if (_activeTalentGroup == orderIndex && !force)
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

    /// unlearn old specialization spells
    for (auto spec : _specializations)
    {
        if (ChrSpecializationEntry const* specialization = sChrSpecializationStore.LookupEntry(spec->GetSpecId()))
        {
            if (std::vector<SpecializationSpellsEntry const*> const* specSpells = sDB2Manager.GetSpecializationSpells(specialization->ID))
            {
                for (size_t j = 0; j < specSpells->size(); ++j)
                {
                    SpecializationSpellsEntry const* specSpell = (*specSpells)[j];
                    _player->RemoveSpell(specSpell->SpellID, true);
                    if (specSpell->OverridesSpellID)
                        _player->RemoveOverrideSpell(specSpell->OverridesSpellID, specSpell->SpellID);
                }
            }

            for (uint32 j = 0; j < MAX_MASTERY_SPELLS; ++j)
                if (uint32 mastery = specialization->MasterySpellID[j])
                    _player->RemoveAurasDueToSpell(mastery);
        }
    }

    currSpecialization->RemoveGlyphAuras();
    currSpecialization->TogglePVPTalents(false);

    _activeTalentGroup = orderIndex;

    newSpecialization->LoadGlyphAuras();
    newSpecialization->TogglePVPTalents(true);

    /// learn new specialization spells
    if (std::vector<SpecializationSpellsEntry const*> const* specSpells = sDB2Manager.GetSpecializationSpells(newSpecialization->GetSpecId()))
    {
        for (size_t j = 0; j < specSpells->size(); ++j)
        {
            SpecializationSpellsEntry const* specSpell = (*specSpells)[j];
            SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(specSpell->SpellID, DIFFICULTY_NONE);
            if (!spellInfo || spellInfo->SpellLevel > _player->GetLevel())
                continue;

            _player->LearnSpell(specSpell->SpellID, false);
            if (specSpell->OverridesSpellID)
                _player->AddOverrideSpell(specSpell->OverridesSpellID, specSpell->SpellID);
        }
    }
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

void TraitsMgr::LearnTraits(WorldPackets::Talent::LearnTraits& learnTraits)
{
    auto UpdateTrait([&](Trait* trait)
    {
        trait->SetConfigName(learnTraits.Trait.ConfigName);

        _player->SetCurrentConfigID(learnTraits.Trait.ConfigID);

        for (auto const& talent : learnTraits.Trait.Talents)
        {
            TraitTalent* newTalent = new TraitTalent(_player, trait, talent.TraitNode, talent.TraitNodeEntryID, talent.Rank, talent.Unk);
            trait->AddTrait(newTalent);
        }

        trait->LearnTraitSpells();
    });

    auto it = _traits.find(learnTraits.Trait.ConfigID);

    Trait* trait = nullptr;

    if (it == _traits.end())
    {
        trait = new Trait(_player, learnTraits.Trait.ConfigID, _player->GetSpecializationId(), uint32(_traits.size()));
        _traits[learnTraits.Trait.ConfigID] = trait;
    }
    else
    {
        trait = it->second;
    }

    UpdateTrait(trait);
    _player->AddOrSetTrait(trait);
    _activeTrait = trait;
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
            if (!challenge->IsComplete())
                return TalentLearnResult::CantDoThatChallengeModeActive;

    if (_player->IsInCombat())
        return TalentLearnResult::AffectingCombat;

    if (slot >= MAX_PVP_TALENT_SLOTS)
        return TalentLearnResult::NoPrimaryTreeSelected;

    uint16 oldPvpTalent = currSpec->GetPVPTalent(slot);

    if (oldPvpTalent && !_player->HasPlayerFlag(PLAYER_FLAGS_RESTING) && !_player->HasUnitFlag2(UNIT_FLAG2_ALLOW_CHANGING_TALENTS))
        return TalentLearnResult::RestArea;

    if (auto oldEntry = sPvpTalentStore.LookupEntry(oldPvpTalent))
    {
        if (auto spellInfo = sSpellMgr->GetSpellInfo(oldEntry->SpellID))
        {
            if (_player->GetSpellHistory()->HasCooldown(spellInfo))
            {
                *spellOnCooldown = oldEntry->SpellID;
                return TalentLearnResult::SpellOnCooldown;
            }
        }
    }

    currSpec->SetPVPTalent(pvpTalentId, slot);

    return TalentLearnResult::Ok;
}

Trait::Trait(Player* player, uint32 configId, uint32 specId, uint32 index) :
    _player(player), _configID(configId), _specializationID(specId), _index(index)
{
}

Trait::~Trait()
{
    for (auto talent : _talents)
        delete talent;
}

void Trait::SetConfigName(std::string_view configName)
{
    _configName = configName;
}

void Trait::AddTrait(TraitTalent* talent)
{
    _talents.push_back(talent);
}

void Trait::LearnTraitSpells()
{
    for (TraitTalent* talent : _talents)
    {
        LearnTraitSpell(talent);
    }
}

void Trait::LearnTraitSpell(TraitTalent* talent)
{
    if (talent->TraitDefinitionEntry)
    {
        _player->LearnSpell(talent->TraitDefinitionEntry->SpellID, true, 0, false, talent->TraitDefinitionEntry->ID);
        if (talent->TraitDefinitionEntry->OverridesSpellID)
            _player->AddOverrideSpell(talent->TraitDefinitionEntry->OverridesSpellID, talent->TraitDefinitionEntry->SpellID);
    }
}

void Trait::UnlearnTraitSpells()
{
    for (TraitTalent* talent : _talents)
    {
        RemoveTraitSpell(talent);
    }
}

void Trait::RemoveTraitSpell(TraitTalent* talent)
{
    if (talent->TraitDefinitionEntry)
    {
        _player->RemoveSpell(talent->TraitDefinitionEntry->SpellID);

        // search for spells that the talent teaches and unlearn them

        auto spellInfo = sSpellMgr->GetSpellInfo(talent->TraitDefinitionEntry->SpellID);
        if (spellInfo)
        {
            for (SpellEffectInfo const& spellEffectInfo : spellInfo->GetEffects())
                if (spellEffectInfo.IsEffect(SPELL_EFFECT_LEARN_SPELL) && spellEffectInfo.TriggerSpell > 0)
                    _player->RemoveSpell(spellEffectInfo.TriggerSpell, true);
        }

        if (talent->TraitDefinitionEntry->OverridesSpellID)
            _player->RemoveOverrideSpell(talent->TraitDefinitionEntry->OverridesSpellID, talent->TraitDefinitionEntry->SpellID);
    }
}

std::vector<TraitTalent*>* Trait::GetTalents()
{
    return &_talents;
}

TraitTalent::TraitTalent(Player* player, Trait* trait, uint32 traitNode, uint32 traitNodeEntryID, uint32 rank, uint32 unk)
    : _player(player), _trait(trait),
    TraitNode(traitNode), TraitNodeEntryID(traitNodeEntryID), Rank(rank), Unk(unk)
{
    TraitNodeEntry       = sTraitNodeStore.LookupEntry(traitNode);
    TraitTreeEntry       = sTraitTreeStore.LookupEntry(TraitNodeEntry ? TraitNodeEntry->TraitTreeID : 0);
    TraitNodeEntryEntry  = sTraitNodeEntryStore.LookupEntry(traitNodeEntryID);
    TraitDefinitionEntry = sTraitDefinitionStore.LookupEntry(TraitNodeEntryEntry ? TraitNodeEntryEntry->TraitDefinitionID : 0);
}

bool TraitTalent::operator==(TraitTalent const& right) const
{
    return TraitNode == right.TraitNode && TraitNodeEntryID == right.TraitNodeEntryID;
}
