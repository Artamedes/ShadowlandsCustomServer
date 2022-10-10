/// WRITTEN BY ARTAMEDES FOR SHADOWS-EMBRACE
/// 9-8-22

/// Game
#include "DB2Stores.h"
#include "ChallengeMode.h"
#include "InstanceScript.h"
#include "Player.h"
#include "TalentPackets.h"
#include "TraitsMgr.h"
#include "SpellAuras.h"
#include "SpellAuraEffects.h"
#include "SpellHistory.h"
#include "SpellInfo.h"

// debug
#include "Chat.h"

////////////////////////////////////////////////////////////////////////

Specialization::Specialization(Player* player, ChrSpecializationEntry const* specEntry) : _player(player), _specId(specEntry->ID)
{
    for (int i = 0; i < MAX_PVP_TALENT_SLOTS; ++i)
        _pvpTalents[i] = 0;

    // Create default trait for this spec
    auto traitMgr = _player->GetTraitsMgr();
    _trait = traitMgr->CreateDefaultTraitForSpec(specEntry);
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

TraitsMgr::TraitsMgr(Player* player) : _player(player), _hasDragonriding(false)
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
    SetupDragonRiding();
    _specializations.reserve(MAX_SPECIALIZATIONS);

    int8 activeTalentGroup = -1;

    for (uint8 i = 0; i < MAX_SPECIALIZATIONS; ++i)
    {
        ChrSpecializationEntry const* spec = sDB2Manager.GetChrSpecializationByIndex(_player->GetClass(), i);
        if (!spec)
            continue;

        /// Don't send Initial in packet
        if (spec->ID >= 1444 && spec->ID <= 1465)
            continue;

        _specializations.emplace_back(new Specialization(_player, spec));

        if (spec->ID == _player->GetSpecializationId())
            activeTalentGroup = spec->OrderIndex;
    }

    if (activeTalentGroup != -1)
        SetActiveTalentGroup(activeTalentGroup, true);

    //std::sort(_specializations.begin(), _specializations.end(), [](Specialization* a, Specialization* b)
    //{
    //    return a->GetSpecId() > b->GetSpecId();
    //});
}

void TraitsMgr::SetupDragonRiding()
{
    if (_hasDragonriding)
        return;
    _hasDragonriding = true;
    uint32 configId = _nextConfigId;

    // Learn default traits for spec
    Trait* trait = new Trait(_player, configId, TraitType::Generic);
    trait->SetSystemID(DragonridingSystemID);
    _traits[configId] = trait;

    static const std::unordered_map<uint32, uint32> DragonRidingTraits =
    {
        { 64057, 82376 },
        { 64055, 82374 },
        { 64053, 82372 },
        { 64056, 82375 },
        { 64052, 82371 },
        { 64054, 82373 },
    };

    for (auto [node, entry] : DragonRidingTraits)
    {
        TraitTalent* newTalent = new TraitTalent(_player, trait, node, entry, 0, TraitTreeFlag::CannotRefund);
        trait->AddTraitTalent(newTalent);
    }

    trait->LearnTraitSpells();
    _player->AddOrSetTrait(trait);
    _nextConfigId++;
}

/// ConfigID to delete/reset before.
constexpr uint32 DeleteConfigIDBefore = 700100;

void TraitsMgr::LoadFromDB(CharacterDatabaseQueryHolder const& holder)
{
    bool sendPacketTalentsReset = false;

    auto traitResult = holder.GetPreparedResult(PLAYER_LOGIN_QUERY_LOAD_SEL_TRAITS);
    if (traitResult)
    {
        do
        {
            Field* fields = traitResult->Fetch();

            uint32 configId                  = fields[0].GetUInt32();
            auto type = static_cast<TraitType>(fields[1].GetUInt32());
            uint32 skillLineID               = fields[2].GetUInt32();;
            uint32 specId                    = fields[3].GetUInt32();
            uint32 combatConfigFlags         = fields[4].GetUInt32();
            uint32 loadoutIndex              = fields[5].GetUInt32();
            uint32 systemID                  = fields[6].GetUInt32();
            std::string_view loadoutName     = fields[7].GetStringView();

            if (configId < DeleteConfigIDBefore)
            {
                auto stmt = CharacterDatabase.GetPreparedStatement(CHAR_DEL_TRAIT);
                stmt->setUInt64(0, _player->GetGUID().GetCounter());
                stmt->setUInt32(1, configId);
                CharacterDatabase.Execute(stmt);
                stmt = CharacterDatabase.GetPreparedStatement(CHAR_DEL_ALL_TRAIT_TALENTS);
                stmt->setUInt64(0, _player->GetGUID().GetCounter());
                stmt->setUInt32(1, configId);
                CharacterDatabase.Execute(stmt);
                sendPacketTalentsReset = true;
                continue;
            }

            if (type == TraitType::Generic && systemID == DragonridingSystemID)
                _hasDragonriding = true;

            /// Traits can be setup from spec initalize
            auto it = _traits.find(configId);
            if (it != _traits.end())
            {
                auto trait = it->second;
                trait->SetConfigName(loadoutName);
            }
            else
            {
                /// Custom loadout trait support
                Trait* trait = new Trait(_player, configId, type);
                trait->SetSkillLineID(skillLineID);
                trait->SetSpecializationID(specId);
                trait->SetLoadoutIndex(loadoutIndex);
                trait->SetCombatConfigFlags(static_cast<TraitCombatConfigFlags>(combatConfigFlags));
                trait->SetSystemID(systemID);
                trait->SetIndex(_traits.size());
                trait->SetConfigName(loadoutName);
                _traits[configId] = trait;
            }

        } while (traitResult->NextRow());
    }

    auto talentResult = holder.GetPreparedResult(PLAYER_LOGIN_QUERY_LOAD_SEL_TRAIT_TALENTS);
    if (talentResult)
    {
        do
        {
            Field* fields = talentResult->Fetch();

            uint32 configId          = fields[0].GetUInt32();
            uint32 traitNode         = fields[1].GetUInt32();
            uint32 traitNodeEntryID  = fields[2].GetUInt32();
            uint32 rank              = fields[3].GetUInt32();
            TraitTreeFlag treeFlags  = static_cast<TraitTreeFlag>(fields[4].GetUInt32());

            if (configId < DeleteConfigIDBefore)
            {
                auto stmt = CharacterDatabase.GetPreparedStatement(CHAR_DEL_TRAIT_TALENT);
                stmt->setUInt64(0, _player->GetGUID().GetCounter());
                stmt->setUInt32(1, configId);
                stmt->setUInt32(2, traitNode);
                CharacterDatabase.Execute(stmt);
                sendPacketTalentsReset = true;
                continue;
            }

            auto it = _traits.find(configId);
            if (it != _traits.end())
            {
                auto trait = it->second;
                auto talentsMap = trait->GetTalents();
                bool hasTalentAlready = talentsMap->find(traitNode) != talentsMap->end();

                if (!hasTalentAlready)
                {
                    /// Not a default talent here, so we going to create new TraitTalent object
                    trait->AddTraitTalent(new TraitTalent(_player, trait, traitNode, traitNodeEntryID, rank, treeFlags));
                }
            }

        } while (talentResult->NextRow());
    }

    if (auto specResult = holder.GetPreparedResult(PLAYER_LOGIN_QUERY_LOAD_SEL_SPEC_INFO))
    {
        do
        {
            Field* fields = talentResult->Fetch();
            
            uint32 SpecId         = fields[0].GetUInt32();
            uint32 LoadoutID      = fields[1].GetUInt32();

            for (auto specalization : _specializations)
            {
                if (specalization->GetSpecId() == SpecId)
                {
                    specalization->SetActiveLoadoutId(LoadoutID);
                    break;
                }
            }

        } while (specResult->NextRow());
    }

    if (_player->m_activePlayerData->ActiveTraitConfigID < DeleteConfigIDBefore)
        _player->SetCurrentConfigID(0);

    /// Initialize updatefields
    for (auto itr = _traits.begin(); itr != _traits.end(); ++itr)
    {
        auto trait = itr->second;

        if (trait->GetConfigID() == _player->m_activePlayerData->ActiveTraitConfigID)
        {
            _player->SetCurrentConfigID(trait->GetConfigID());
            trait->LearnTraitSpells();
            _activeTrait = trait;
        }

        _player->AddOrSetTrait(trait);

        if (_nextConfigId <= trait->GetConfigID())
            _nextConfigId = trait->GetConfigID() + 1;
    }

    /// If we still have 0 configid at this point, player spec change should set it.
    if (sendPacketTalentsReset)
    {
        WorldPacket data(SMSG_TALENTS_INVOLUNTARILY_RESET, 1);
        data.WriteBit(0); ///< IsPet
        data.FlushBits();
        _player->SendDirectMessage(&data);
    }

    // if we still don't have a trait, we going to set one here.
    if (_activeTrait == nullptr && GetActiveSpecialization())
    {
        _activeTrait = GetActiveSpecialization()->GetDefaultTrait();
        _activeTrait->LearnTraitSpells();
        _player->SetCurrentConfigID(_activeTrait->GetConfigID());
    }
}

void TraitsMgr::SaveToDB(CharacterDatabaseTransaction trans)
{
    for (auto it = _traits.begin(); it != _traits.end(); ++it)
    {
        auto trait = it->second;

        trait->SaveToDB(trans);
    }
}

void TraitsMgr::SendUpdateTalentData()
{
    WorldPackets::Talent::UpdateTalentData packet;

    packet.Info.ActiveGroup = GetActiveTalentGroupSafe();
    packet.Info.PrimarySpecialization = !_specializations.empty() ? _specializations[0]->GetSpecId() : 0; ///< Unsure why blizz always sneding same here
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

    if (currSpecialization)
    {
        currSpecialization->RemoveGlyphAuras();
        currSpecialization->TogglePVPTalents(false);

        if (GetActiveTrait())
            GetActiveTrait()->UnlearnTraitSpells();
    }

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

    /// Update primary specialization UF
    _player->SetPrimarySpecialization(newSpecialization->GetSpecId());
    /// Send SMSG_UPDATE_TALENT_DATA to update the UI
    SendUpdateTalentData();
    uint32 configId = 0;

    if (!force || _player->m_activePlayerData->ActiveTraitConfigID == 0)
    {
        if (Trait* swappedTrait = GetTraitForSpec(newSpecialization->GetSpecId()))
        {
            swappedTrait->LearnTraitSpells();
            configId = swappedTrait->GetConfigID();
            _player->SetCurrentConfigID(configId);
            _activeTrait = swappedTrait;
        }
        else
        {
            /// First time setting the spec
            TC_LOG_ERROR("network.opcode", "Somehow player not have traits!");
            if (auto specEntry = sChrSpecializationStore.LookupEntry(newSpecialization->GetSpecId()))
                if (auto trait = CreateDefaultTraitForSpec(specEntry, true))
                    configId = trait->GetConfigID();
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

Trait* TraitsMgr::GetTraitForSpec(uint32 specId)
{
    auto defaultTrait = GetActiveSpecialization()->GetDefaultTrait();
    uint32 activeLoadoutId = GetActiveSpecialization()->GetActiveLoadoutId();

    for (auto itr = _traits.begin(); itr != _traits.end(); ++itr)
    {
        Trait* trait = itr->second;
        if (trait->GetType() == TraitType::Combat
            && trait->GetSpecializationID() == specId
            && trait->GetLoadoutIndex() == activeLoadoutId)
            return trait;
    }

    return defaultTrait;
}

Trait* TraitsMgr::CreateDefaultTraitForSpec(ChrSpecializationEntry const* specEntry, bool activeSpec /*= false*/)
{
    uint32 talentConfigId = _nextConfigId;

    // Learn default traits for spec
    Trait* trait = new Trait(_player, talentConfigId, TraitType::Combat);
    trait->SetSpecializationID(specEntry->ID);
    trait->SetLoadoutIndex(0);
    trait->SetIndex(_traits.size());
    trait->SetConfigName(specEntry->Name.Str[_player->GetSession()->GetSessionDbcLocale()]);
    _traits[talentConfigId] = trait;

    std::set<int32> traitTreeIds;

    for (auto traitTreeLoadoutEntry : sTraitTreeLoadoutEntryStore)
    {
        if (auto traitTreeLoadout = sTraitTreeLoadoutStore.LookupEntry(traitTreeLoadoutEntry->ID))
        {
            if (traitTreeLoadout->Field_10_0_0_45232_002 == specEntry->ID)
            {
                traitTreeIds.insert(traitTreeLoadout->TraitTreeID);
            }
        }
    }

    std::vector<int32> traitNodeIds;
    for (auto id : traitTreeIds)
    {
        for (auto traitCond : sTraitCondStore)
        {
            if (traitCond->CondType == 2 && traitCond->TraitTreeID == id)
            {
                bool shouldContinue = true;

                for (auto specSet : sSpecSetMemberStore)
                {
                    if (specSet->ChrSpecializationID == specEntry->ID && traitCond->SpecSetID == specSet->SpecSetID)
                    {
                        shouldContinue = false;
                        break;
                    }
                }

                if (shouldContinue)
                    continue;

                for (auto traitNodeXTraitCond : sTraitNodeXTraitCondStore)
                {
                    if (traitNodeXTraitCond->TraitCondID == traitCond->ID)
                    {
                        traitNodeIds.emplace_back(traitNodeXTraitCond->TraitNodeID);
                        TC_LOG_INFO("network.opcode", "traitNodeXTraitCond Default TraitNodeID %u for spec %u", traitNodeXTraitCond->TraitNodeID, specEntry->ID);
                    }
                }

                for (auto traitNodeGroupXTraitCond : sTraitNodeGroupXTraitCondStore)
                {
                    if (traitNodeGroupXTraitCond->TraitCondID == traitCond->ID)
                    {
                        for (auto traitNodeGroup : sTraitNodeGroupXTraitNodeStore)
                        {
                            if (traitNodeGroup->TraitNodeGroupID == traitNodeGroupXTraitCond->TraitNodeGroupID)
                            {
                                traitNodeIds.emplace_back(traitNodeGroup->TraitNodeID);
                                TC_LOG_INFO("network.opcode", "traitNodeGroup Default TraitNodeID %u for spec %u", traitNodeGroup->TraitNodeID, specEntry->ID);
                            }
                        }
                    }
                }
            }
        }
    }

    std::set<uint32> learnedSpells;

    std::sort(traitNodeIds.begin(), traitNodeIds.end(), std::greater<>());

    for (auto id : traitNodeIds)
    {
        for (auto traitNodeXTraitNode : sTraitNodeXTraitNodeEntryStore)
        {
            if (traitNodeXTraitNode->TraitNodeID == id)
            {
                if (auto traitNodeEntry = sTraitNodeEntryStore.LookupEntry(traitNodeXTraitNode->TraitNodeEntryID))
                {
                    if (auto traitDef = sTraitDefinitionStore.LookupEntry(traitNodeEntry->TraitDefinitionID))
                    {
                        if (learnedSpells.find(traitDef->SpellID) == learnedSpells.end())
                        {
                            learnedSpells.insert(traitDef->SpellID);
                            trait->AddTraitTalent(new TraitTalent(_player, trait,
                                traitNodeXTraitNode->TraitNodeID,
                                traitNodeXTraitNode->TraitNodeEntryID,
                                traitNodeEntry->MaxRanks - 1,
                                TraitTreeFlag::CannotRefund,
                                true));
                        }
                    }
                }
                break;
            }
        }
    }

   //for (auto id : traitTreeIds)
   //{
   //    if (auto traitTree = sTraitTreeStore.LookupEntry(id))
   //    {
   //        for (auto traitNode : sTraitNodeStore)
   //        {
   //            if (traitNode->TraitTreeID == id)
   //            {
   //                if (selectedTraitNodeIDs.find(traitNode->ID) == selectedTraitNodeIDs.end())
   //                     TC_LOG_INFO("network.opcode", "Trait %u for spec %u TraitTreeId: %u", traitNode->ID, specEntry->ID, id);
   //            }
   //        }
   //    }
   //}

    if (activeSpec)
    {
        trait->LearnTraitSpells();
        _player->SetCurrentConfigID(talentConfigId);
        _activeTrait = trait;
    }

    _player->AddOrSetTrait(trait);
    _nextConfigId++;

    return trait;
}

Trait* TraitsMgr::GetTraitByLoadoutID(uint32 loadoutId)
{
    for (auto itr = _traits.begin(); itr != _traits.end(); ++itr)
    {
        Trait* trait = itr->second;
        if (trait->GetType() == TraitType::Combat
            && trait->GetSpecializationID() == _player->GetSpecializationId()
            && trait->GetLoadoutIndex() == loadoutId)
            return trait;
    }

    return nullptr;
}

void TraitsMgr::LearnTraits(WorldPackets::Talent::LearnTraits& learnTraits)
{
    auto UpdateTrait([&](Trait* trait)
    {
        trait->SetConfigName(learnTraits.Trait.LoadoutName);

        _player->SetCurrentConfigID(learnTraits.Trait.ConfigID);

        std::vector<uint32> unlearnedTraits;
        unlearnedTraits.reserve(learnTraits.Trait.Talents.size());

        auto traitMap = trait->GetTalents();

        for (auto const& talent : learnTraits.Trait.Talents)
        {
            // learn case
            if (talent.Rank > 0)
            {
                auto it = traitMap->find(talent.TraitNode);

                if (it == traitMap->end())
                    trait->AddTraitTalent(new TraitTalent(_player, trait, talent.TraitNode, talent.TraitNodeEntryID, talent.Rank, talent.TreeFlags));
                else
                {
                    // update new rank
                    it->second->Rank = talent.Rank;
                    it->second->TreeFlags = talent.TreeFlags;
                    it->second->IsChanged = true;
                }
            }
            else
            {
                // unlearn case
                unlearnedTraits.emplace_back(talent.TraitNode);
            }
        }

        // Now we need to check old traits in relearn unlearn case
        for (uint32 removedTrait : unlearnedTraits)
        {
            if (!trait->RemoveTraitTalent(removedTrait))
                TC_LOG_ERROR("network.opcode", "Client tried to unlearn not-learned or default trait! %u", removedTrait);
        }

        trait->LearnTraitSpells();
    });

    auto it = _traits.find(learnTraits.Trait.ConfigID);

    Trait* trait = nullptr;

    if (it == _traits.end())
    {
        trait = new Trait(_player, learnTraits.Trait.ConfigID, TraitType::Combat);
        trait->SetSpecializationID(_player->GetSpecializationId());
        trait->SetLoadoutIndex(GetNextTraitLoadoutIndex());
        trait->SetIndex(_traits.size());
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

Trait* TraitsMgr::GetTraitByConfigID(uint32 configID)
{
    auto it = _traits.find(configID);
    if (it == _traits.end())
        return nullptr;

    return it->second;
}

void TraitsMgr::CreateNewLoadout(WorldPackets::Talent::CreateNewLoadout& createNewLoadout)
{
    auto UpdateTrait([&](Trait* trait)
    {
        trait->SetConfigName(createNewLoadout.Trait.LoadoutName);

        //_player->SetCurrentConfigID(createNewLoadout.Trait.ConfigID);

        std::vector<uint32> unlearnedTraits;
        unlearnedTraits.reserve(createNewLoadout.Trait.Talents.size());

        for (auto const& talent : createNewLoadout.Trait.Talents)
        {
            // learn case
            if (talent.Rank > 0)
            {
                TraitTalent* newTalent = new TraitTalent(_player, trait, talent.TraitNode, talent.TraitNodeEntryID, talent.Rank, talent.TreeFlags);
                trait->AddTraitTalent(newTalent);
            }
            else
            {
                // unlearn case
                unlearnedTraits.emplace_back(talent.TraitNode);
            }
        }

        // Now we need to check old traits in relearn unlearn case
        for (uint32 removedTrait : unlearnedTraits)
        {
            if (!trait->RemoveTraitTalent(removedTrait))
                TC_LOG_ERROR("network.opcode", "Client tried to unlearn not learned trait! %u", removedTrait);
        }

        trait->LearnTraitSpells();
    });

    // Since we are swapping, remove active trait data
    if (GetActiveTrait())
        GetActiveTrait()->UnlearnTraitSpells();

    // seems like this packet supplies old configid of copy
    uint32 newConfigId = _nextConfigId++;

    auto it = _traits.find(newConfigId);

    Trait* trait = nullptr;

    if (it == _traits.end())
    {
        trait = new Trait(_player, newConfigId, TraitType::Combat);
        trait->SetSpecializationID(_player->GetSpecializationId());
        trait->SetLoadoutIndex(GetNextTraitLoadoutIndex());
        trait->SetIndex(_traits.size());
        _traits[newConfigId] = trait;
    }
    else
    {
        trait = it->second;
    }

    UpdateTrait(trait);
    _player->AddOrSetTrait(trait);
    _activeTrait = trait;
   // _player->SetCurrentConfigID(trait->GetConfigID());
}

void TraitsMgr::SwapLoadout(uint32 loadoutId, std::vector<WorldPackets::Talent::TraitConfigEntry> traits)
{
    auto trait = GetTraitByLoadoutID(loadoutId);
    if (!trait)
        return;

    // edit default layout for some reason - wtf blizz
    auto defaultTrait = GetActiveSpecialization()->GetDefaultTrait();

    for (auto const& talent : traits)
    {
        auto itTalent = defaultTrait->GetTalents()->find(talent.TraitNode);
        if (itTalent != defaultTrait->GetTalents()->end())
        {
            TraitTalent* oldTalent = itTalent->second;

            if (talent.Rank > 0)
            {
                oldTalent->Rank = talent.Rank;
                oldTalent->TraitNodeEntryID = talent.TraitNodeEntryID;
                oldTalent->TreeFlags = talent.Rank == 0 ? TraitTreeFlag::CannotRefund : talent.TreeFlags;
                oldTalent->IsChanged = true;
                oldTalent->Initialize();

                //if (oldTalent->Rank == 0)
                //    if (!defaultTrait->RemoveTraitTalent(talent.TraitNode))
                //        TC_LOG_ERROR("network.opcode", "Client tried to unlearn not learned trait! %u", talent.TraitNode);
            }
            else
            {
                if (!defaultTrait->RemoveTraitTalent(talent.TraitNode))
                    TC_LOG_ERROR("network.opcode", "Client tried to unlearn not learned trait! %u", talent.TraitNode);
            }
        }
        else
        {
            // learn case
            if (talent.Rank > 0)
            {
                TraitTalent* newTalent = new TraitTalent(_player, defaultTrait, talent.TraitNode, talent.TraitNodeEntryID, talent.Rank, talent.TreeFlags);
                defaultTrait->AddTraitTalent(newTalent);
            }
            else
            {
                // unlearn case
                if (!defaultTrait->RemoveTraitTalentOnlyUnlearn(talent.TraitNode))
                    TC_LOG_ERROR("network.opcode", "RemoveTraitTalentOnlyUnlearn Client tried to unlearn not learned trait! %u ignoring.", talent.TraitNode);
            }
        }
    }

    _player->AddOrSetTrait(defaultTrait);

    _activeTrait = trait;

    // learn new spells
    defaultTrait->LearnTraitSpells();
    _player->SetCurrentConfigID(_activeTrait->GetConfigID());
}

void TraitsMgr::SwapLoadout(uint32 loadout)
{
    for (auto it = _traits.begin(); it != _traits.end(); ++it)
    {
        if (it->second->GetSpecializationID() == _player->GetSpecializationId() && it->second->GetLoadoutIndex() == loadout)
        {
            auto trait = it->second;

            if (trait == GetActiveTrait())
                break;

            // Since we are swapping, remove active trait data
            // @todo: diff 2 traits and only unlearn/learn what need - blizzlike
            if (GetActiveTrait())
                GetActiveTrait()->UnlearnTraitSpells();

            trait->LearnTraitSpells();
            _activeTrait = trait;
            GetActiveSpecialization()->SetActiveLoadoutId(trait->GetLoadoutIndex());
            _player->SetCurrentConfigID(trait->GetConfigID());
            break;
        }
    }
}

void TraitsMgr::RenameLoadout(uint32 configId, std::string const& newName)
{
    if (auto trait = GetTraitByConfigID(configId))
    {
        trait->SetConfigName(newName);
        _player->AddOrSetTrait(trait);
    }
}

void TraitsMgr::RemoveLoadout(uint32 configId)
{
    auto it = _traits.find(configId);
    if (it == _traits.end())
        return;

    auto trait = it->second;

    auto DeleteTrait([&]() -> void
    {
        auto stmt = CharacterDatabase.GetPreparedStatement(CHAR_DEL_TRAIT);
        stmt->setUInt64(0, _player->GetGUID().GetCounter());
        stmt->setUInt32(1, configId);
        CharacterDatabase.Execute(stmt);
        stmt = CharacterDatabase.GetPreparedStatement(CHAR_DEL_ALL_TRAIT_TALENTS);
        stmt->setUInt64(0, _player->GetGUID().GetCounter());
        stmt->setUInt32(1, configId);
        CharacterDatabase.Execute(stmt);

        _player->RemoveTrait(trait);
        delete trait;
        _traits.erase(configId);
    });

    if (trait == GetActiveTrait())
    {
        for (auto itr = _traits.begin(); itr != _traits.end(); ++itr)
        {
            if (itr->second == trait)
                continue;

            if (itr->second->GetSpecializationID() == _player->GetSpecializationId())
            {
                trait->UnlearnTraitSpells();
                DeleteTrait();

                auto swappedTrait = itr->second;
                _activeTrait = swappedTrait;
                swappedTrait->LearnTraitSpells();
                configId = swappedTrait->GetConfigID();
                _player->SetCurrentConfigID(configId);
                GetActiveSpecialization()->SetActiveLoadoutId(swappedTrait->GetLoadoutIndex());
                return;
            }
        }
    }
    else
    {
        DeleteTrait();
    }
}

uint32 TraitsMgr::GetNextTraitLoadoutIndex() const
{
    uint32 nextLoadoutIndex = 0;

    for (auto const& [configId, trait] : _traits)
    {
        if (trait->GetSpecializationID() == _player->GetSpecializationId())
            if (nextLoadoutIndex < trait->GetLoadoutIndex())
                nextLoadoutIndex = trait->GetLoadoutIndex();
    }

    return nextLoadoutIndex;
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

Trait::Trait(Player* player, uint32 configId, TraitType type) :
    _player(player), _configID(configId), _type(type),
    _skillLineID(0),
    _specializationID(0), _combatConfigFlags(TraitCombatConfigFlags::None), _loadoutIndex(0),
    _systemID(0),
    _index(0)
{
}

Trait::~Trait()
{
    for (auto itr = _talents.begin(); itr != _talents.end(); itr++)
        delete itr->second;
}

void Trait::SetConfigName(std::string_view configName)
{
    _loadoutName = configName;
}

void Trait::AddTraitTalent(TraitTalent* talent)
{
    _talents[talent->TraitNodeID] = talent;
}

bool Trait::RemoveTraitTalent(uint32 traitNode)
{
    auto it = _talents.find(traitNode);
    if (it == _talents.end())
        return false;

    /// Can't remove default talents
    if (it->second->IsDefault)
        return false;

    /// Remove trait auras/learned spells
    RemoveTraitSpell(it->second);
    it->second->IsChanged = true;

    /// Remove from DB
    auto stmt = CharacterDatabase.GetPreparedStatement(CHAR_DEL_TRAIT_TALENT);
    stmt->setUInt64(0, _player->GetGUID().GetCounter());
    stmt->setUInt32(1, GetConfigID());
    stmt->setUInt32(2, traitNode);
    CharacterDatabase.Execute(stmt);

    _player->RemoveTraitTalent(this, it->second);

    /// Free memory
    delete it->second;
    _talents.erase(it);
    return true;
}

bool Trait::RemoveTraitTalentOnlyUnlearn(uint32 traitNode)
{
    auto it = _talents.find(traitNode);
    if (it == _talents.end())
        return false;

    /// Can't remove default talents
    if (it->second->IsDefault)
        return false;

    /// Remove trait auras/learned spells
    RemoveTraitSpell(it->second);
    it->second->IsChanged = true;
    return true;
}

void Trait::LearnTraitSpells()
{
    for (auto itr = _talents.begin(); itr != _talents.end(); itr++)
    {
        LearnTraitSpell(itr->second);
    }
}

void Trait::LearnTraitSpell(TraitTalent* talent)
{
    if (!talent->TreeFlags.HasFlag(TraitTreeFlag::CannotRefund) && talent->TraitDefinitionEntry)
    {
        auto spellInfo = sSpellMgr->GetSpellInfo(talent->TraitDefinitionEntry->SpellID);

        if (spellInfo && spellInfo->IsPassive())
            if (auto aura = _player->GetAura(spellInfo->Id))
            {
                // we going to remove this aura, then reapply it in Player::AddSpell below
                aura->Remove();
            }

        _player->LearnSpell(talent->TraitDefinitionEntry->SpellID, true, 0, false, talent->TraitDefinitionEntry->ID, [&]()
        {
            if (auto aura = _player->GetAura(talent->TraitDefinitionEntry->SpellID))
            {
                aura->SetTraitTalent(talent);

                if (talent->Rank > 1)
                {
                    for (auto aurEff : aura->GetAuraEffects())
                    {
                        if (aurEff)
                        {
                            aurEff->RecalculateAmount();
                        }
                    }
                }
            }
        });

        if (talent->TraitDefinitionEntry->OverridesSpellID)
            _player->AddOverrideSpell(talent->TraitDefinitionEntry->OverridesSpellID, talent->TraitDefinitionEntry->SpellID);
    }
}

void Trait::SaveToDB(CharacterDatabaseTransaction trans)
{
    auto stmt = CharacterDatabase.GetPreparedStatement(CHAR_REP_TRAIT);

    stmt->setUInt64(0, _player->GetGUID().GetCounter());
    stmt->setUInt32(1, GetConfigID());
    stmt->setUInt32(2, static_cast<uint32>(GetType()));
    stmt->setUInt32(3, GetSkillLineID());
    stmt->setUInt32(4, GetSpecializationID());
    stmt->setUInt32(5, GetCombatConfigFlags().AsUnderlyingType());
    stmt->setUInt32(6, GetLoadoutIndex());
    stmt->setUInt32(7, GetSystemID());
    stmt->setStringView(8, GetConfigName());

    trans->Append(stmt);

    for (auto itr = _talents.begin(); itr != _talents.end(); ++itr)
    {
        auto talent = itr->second;

        auto stmt = CharacterDatabase.GetPreparedStatement(CHAR_REP_TRAIT_TALENT);

        stmt->setUInt64(0, _player->GetGUID().GetCounter());
        stmt->setUInt32(1, GetConfigID());
        stmt->setUInt32(2, talent->TraitNodeID);
        stmt->setUInt32(3, talent->TraitNodeEntryID);
        stmt->setUInt32(4, talent->Rank);
        stmt->setUInt32(5, talent->TreeFlags.AsUnderlyingType());

        trans->Append(stmt);
    }
}

void Trait::UnlearnTraitSpells()
{
    _player->InterruptNonMeleeSpells(false);

    for (auto itr = _talents.begin(); itr != _talents.end(); itr++)
    {
        RemoveTraitSpell(itr->second);
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

std::unordered_map<uint32, TraitTalent*>* Trait::GetTalents()
{
    return &_talents;
}

TraitTalent::TraitTalent(Player* player, Trait* trait, uint32 traitNode, uint32 traitNodeEntryID, uint32 rank, EnumFlag<TraitTreeFlag> treeFlags, bool isDefault)
    : _player(player), _trait(trait),
    TraitNodeID(traitNode), TraitNodeEntryID(traitNodeEntryID), Rank(rank), TreeFlags(treeFlags), IsDefault(isDefault)
{
    Initialize();
}

void TraitTalent::Initialize()
{
    TraitNodeEntry       = sTraitNodeStore.LookupEntry(TraitNodeID);
    TraitTreeEntry       = sTraitTreeStore.LookupEntry(TraitNodeEntry ? TraitNodeEntry->TraitTreeID : 0);
    TraitNodeEntryEntry  = sTraitNodeEntryStore.LookupEntry(TraitNodeEntryID);
    TraitDefinitionEntry = sTraitDefinitionStore.LookupEntry(TraitNodeEntryEntry ? TraitNodeEntryEntry->TraitDefinitionID : 0);
}

bool TraitTalent::operator==(TraitTalent const& right) const
{
    return TraitNodeID == right.TraitNodeID
        && TraitNodeEntryID == right.TraitNodeEntryID;
}
