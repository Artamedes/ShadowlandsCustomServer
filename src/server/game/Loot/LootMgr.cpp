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

#include "ChallengeMode.h"
#include "ChallengeModeMgr.h"
#include "LootMgr.h"
#include "Containers.h"
#include "DatabaseEnv.h"
#include "DB2Stores.h"
#include "ItemTemplate.h"
#include "Log.h"
#include "Loot.h"
#include "ObjectMgr.h"
#include "Player.h"
#include "Random.h"
#include "SpellInfo.h"
#include "SpellMgr.h"
#include "World.h"
#include "StringConvert.h"
#include "ObjectAccessor.h"

static Rates const qualityToRate[MAX_ITEM_QUALITY] =
{
    RATE_DROP_ITEM_POOR,                                    // ITEM_QUALITY_POOR
    RATE_DROP_ITEM_NORMAL,                                  // ITEM_QUALITY_NORMAL
    RATE_DROP_ITEM_UNCOMMON,                                // ITEM_QUALITY_UNCOMMON
    RATE_DROP_ITEM_RARE,                                    // ITEM_QUALITY_RARE
    RATE_DROP_ITEM_EPIC,                                    // ITEM_QUALITY_EPIC
    RATE_DROP_ITEM_LEGENDARY,                               // ITEM_QUALITY_LEGENDARY
    RATE_DROP_ITEM_ARTIFACT,                                // ITEM_QUALITY_ARTIFACT
};

LootStore LootTemplates_Creature("creature_loot_template",           "creature entry",                  true);
LootStore LootTemplates_Disenchant("disenchant_loot_template",       "item disenchant id",              true);
LootStore LootTemplates_Fishing("fishing_loot_template",             "area id",                         true);
LootStore LootTemplates_Gameobject("gameobject_loot_template",       "gameobject entry",                true);
LootStore LootTemplates_Item("item_loot_template",                   "item entry",                      true);
LootStore LootTemplates_Mail("mail_loot_template",                   "mail template id",                false);
LootStore LootTemplates_Milling("milling_loot_template",             "item entry (herb)",               true);
LootStore LootTemplates_Pickpocketing("pickpocketing_loot_template", "creature pickpocket lootid",      true);
LootStore LootTemplates_Prospecting("prospecting_loot_template",     "item entry (ore)",                true);
LootStore LootTemplates_Reference("reference_loot_template",         "reference id",                    false);
LootStore LootTemplates_Skinning("skinning_loot_template",           "creature skinning id",            true);
LootStore LootTemplates_Spell("spell_loot_template",                 "spell id (random item creating)", false);

// Selects invalid loot items to be removed from group possible entries (before rolling)
struct LootGroupInvalidSelector
{
    explicit LootGroupInvalidSelector(Loot const& loot, uint16 lootMode, Difficulty difficulty, Player const* playerLooter, bool checkSpec) : _loot(loot), _lootMode(lootMode), _difficulty(difficulty), _playerLooter(playerLooter), _checkSpec(checkSpec) { }

    bool operator()(LootStoreItem* item) const
    {
        if (!(item->lootmode & _lootMode))
            return true;

        if (item->difficulty && item->difficulty != _difficulty)
            return true;

        if (_playerLooter)
            if (ItemTemplate const* itemTemplate = item->GetItemTemplate())
                if (!_playerLooter->CheckItemCompatibility(itemTemplate, _checkSpec))
                    return true;

        uint8 foundDuplicates = 0;
        for (std::vector<LootItem>::const_iterator itr = _loot.items.begin(); itr != _loot.items.end(); ++itr)
            if (itr->itemid == item->itemid)
                if (++foundDuplicates == _loot.maxDuplicates)
                    return true;

        return false;
    }

private:
    Loot const& _loot;
    uint16 _lootMode;
    Difficulty _difficulty;
    Player const* _playerLooter;
    bool _checkSpec;
};

class LootTemplate::LootGroup                               // A set of loot definitions for items (refs are not allowed)
{
    public:
        LootGroup() { }
        ~LootGroup();

        void AddEntry(LootStoreItem* item);                 // Adds an entry to the group (at loading stage)
        bool HasQuestDrop() const;                          // True if group includes at least 1 quest drop entry
        bool HasQuestDropForPlayer(Player const* player) const;
                                                            // The same for active quests of the player
        void Process(Loot& loot, uint16 lootMode, Difficulty difficulty, Player const* player, bool specOnly = false, bool personaLoot = false) const;    // Rolls an item from the group (if any) and adds the item to the loot
        float RawTotalChance() const;                       // Overall chance for the group (without equal chanced items)
        float TotalChance() const;                          // Overall chance for the group

        void Verify(LootStore const& lootstore, uint32 id, uint8 group_id) const;
        void CheckLootRefs(LootTemplateMap const& store, LootIdSet* ref_set) const;
        LootStoreItemList* GetExplicitlyChancedItemList() { return &ExplicitlyChanced; }
        LootStoreItemList* GetEqualChancedItemList() { return &EqualChanced; }
        void CopyConditions(ConditionContainer conditions);
    private:
        LootStoreItemList ExplicitlyChanced;                // Entries with chances defined in DB
        LootStoreItemList EqualChanced;                     // Zero chances - every entry takes the same chance

        LootStoreItem const* Roll(Loot& loot, uint16 lootMode, Difficulty difficulty, Player const* player = nullptr, bool checkSpec = false) const;   // Rolls an item from the group, returns NULL if all miss their chances

        // This class must never be copied - storing pointers
        LootGroup(LootGroup const&) = delete;
        LootGroup& operator=(LootGroup const&) = delete;
};

//Remove all data and free all memory
void LootStore::Clear()
{
    for (LootTemplateMap::const_iterator itr = m_LootTemplates.begin(); itr != m_LootTemplates.end(); ++itr)
        delete itr->second;
    m_LootTemplates.clear();
}

// Checks validity of the loot store
// Actual checks are done within LootTemplate::Verify() which is called for every template
void LootStore::Verify() const
{
    for (LootTemplateMap::const_iterator i = m_LootTemplates.begin(); i != m_LootTemplates.end(); ++i)
        i->second->Verify(*this, i->first);
}

// Loads a *_loot_template DB table into loot store
// All checks of the loaded template are called from here, no error reports at loot generation required
uint32 LootStore::LoadLootTable()
{
    LootTemplateMap::const_iterator tab;

    // Clearing store (for reloading case)
    Clear();

    //                                                 0      1       2        3         4          5          6       7        8         9         10
    QueryResult result = WorldDatabase.PQuery("SELECT Entry, Type, Item, Reference, Chance, QuestRequired, LootMode, GroupId, MinCount, MaxCount, BonusList FROM %s", GetName());

    if (!result)
        return 0;

    uint32 count = 0;

    do
    {
        Field* fields = result->Fetch();

        uint32 entry               = fields[0].GetUInt32();
        auto   type                = static_cast<LootItemType>(fields[1].GetUInt8());
        uint32 item                = fields[2].GetUInt32();
        uint32 reference           = fields[3].GetUInt32();
        float  chance              = fields[4].GetFloat();
        bool   needsquest          = fields[5].GetBool();
        uint16 lootmode            = fields[6].GetUInt16();
        uint8  groupid             = fields[7].GetUInt8();
        uint8  mincount            = fields[8].GetUInt8();
        uint8  maxcount            = fields[9].GetUInt8();

        std::vector<int32> bonusIdList;

        for (std::string_view token : Trinity::Tokenize(fields[10].GetStringView(), ' ', false))
            if (Optional<int32> bonusListID = Trinity::StringTo<int32>(token))
                bonusIdList.push_back(*bonusListID);

        if (groupid >= 1 << 7)                                     // it stored in 7 bit field
        {
            TC_LOG_ERROR("sql.sql", "Table '%s' Entry %d Item %d: GroupId (%u) must be less %u - skipped", GetName(), entry, item, groupid, 1 << 7);
            return 0;
        }

        LootStoreItem* storeitem = new LootStoreItem(type, item, reference, chance, needsquest, lootmode, groupid, mincount, maxcount, bonusIdList);

        if (!storeitem->IsValid(*this, entry))            // Validity checks
        {
            delete storeitem;
            continue;
        }

        // Looking for the template of the entry
                                                         // often entries are put together
        if (m_LootTemplates.empty() || tab->first != entry)
        {
            // Searching the template (in case template Id changed)
            tab = m_LootTemplates.find(entry);
            if (tab == m_LootTemplates.end())
            {
                std::pair< LootTemplateMap::iterator, bool > pr = m_LootTemplates.insert(LootTemplateMap::value_type(entry, new LootTemplate()));
                tab = pr.first;
            }
        }
        // else is empty - template Id and iter are the same
        // finally iter refers to already existed or just created <entry, LootTemplate>

        // Adds current row to the template
        tab->second->AddEntry(storeitem);
        ++count;
    }
    while (result->NextRow());

    Verify();                                           // Checks validity of the loot store

    return count;
}

bool LootStore::HaveQuestLootFor(uint32 loot_id) const
{
    LootTemplateMap::const_iterator itr = m_LootTemplates.find(loot_id);
    if (itr == m_LootTemplates.end())
        return false;

    // scan loot for quest items
    return itr->second->HasQuestDrop(m_LootTemplates);
}

bool LootStore::HaveQuestLootForPlayer(uint32 loot_id, Player const* player) const
{
    LootTemplateMap::const_iterator tab = m_LootTemplates.find(loot_id);
    if (tab != m_LootTemplates.end())
        if (tab->second->HasQuestDropForPlayer(m_LootTemplates, player))
            return true;

    return false;
}

void LootStore::ResetConditions()
{
    for (LootTemplateMap::iterator itr = m_LootTemplates.begin(); itr != m_LootTemplates.end(); ++itr)
    {
        ConditionContainer empty;
        itr->second->CopyConditions(empty);
    }
}

LootTemplate const* LootStore::GetLootFor(uint32 loot_id) const
{
    LootTemplateMap::const_iterator tab = m_LootTemplates.find(loot_id);

    if (tab == m_LootTemplates.end())
        return nullptr;

    return tab->second;
}

LootTemplate* LootStore::GetLootForConditionFill(uint32 loot_id)
{
    LootTemplateMap::iterator tab = m_LootTemplates.find(loot_id);

    if (tab == m_LootTemplates.end())
        return nullptr;

    return tab->second;
}

uint32 LootStore::LoadAndCollectLootIds(LootIdSet& lootIdSet)
{
    uint32 count = LoadLootTable();

    for (LootTemplateMap::const_iterator tab = m_LootTemplates.begin(); tab != m_LootTemplates.end(); ++tab)
        lootIdSet.insert(tab->first);

    return count;
}

void LootStore::CheckLootRefs(LootIdSet* ref_set) const
{
    for (LootTemplateMap::const_iterator ltItr = m_LootTemplates.begin(); ltItr != m_LootTemplates.end(); ++ltItr)
        ltItr->second->CheckLootRefs(m_LootTemplates, ref_set);
}

void LootStore::ReportUnusedIds(LootIdSet const& lootIdSet) const
{
    // all still listed ids isn't referenced
    for (LootIdSet::const_iterator itr = lootIdSet.begin(); itr != lootIdSet.end(); ++itr)
        TC_LOG_ERROR("sql.sql", "Table '%s' Entry %d isn't %s and not referenced from loot, and thus useless.", GetName(), *itr, GetEntryName());
}

void LootStore::ReportNonExistingId(uint32 lootId) const
{
    TC_LOG_ERROR("sql.sql", "Table '%s' Entry %d does not exist", GetName(), lootId);
}

void LootStore::ReportNonExistingId(uint32 lootId, char const* ownerType, uint32 ownerId) const
{
    TC_LOG_ERROR("sql.sql", "Table '%s' Entry %d does not exist but it is used by %s %d", GetName(), lootId, ownerType, ownerId);
}

//
// --------- LootStoreItem ---------
//

// Checks if the entry (quest, non-quest, reference) takes it's chance (at loot generation)
// RATE_DROP_ITEMS is no longer used for all types of entries
bool LootStoreItem::Roll(bool rate, uint8 extraChance /* = 0 */, Player const* player /*= nullptr*/, bool checkSpec /*= false*/) const
{
    ItemTemplate const* pProto = sObjectMgr->GetItemTemplate(itemid);
    if (player && pProto)
        if (!player->CheckItemCompatibility(pProto, checkSpec))
            return false;

    if (chance >= 100.0f)
        return true;

    if (reference > 0)                                   // reference case
        return roll_chance_f(chance * (rate ? sWorld->getRate(RATE_DROP_ITEM_REFERENCED) : 1.0f));

    float qualityModifier = pProto && rate ? sWorld->getRate(qualityToRate[pProto->GetQuality()]) : 1.0f;

    return roll_chance_f((chance * qualityModifier) + extraChance);
}

// Checks correctness of values
bool LootStoreItem::IsValid(LootStore const& store, uint32 entry) const
{
    if (mincount == 0)
    {
        TC_LOG_ERROR("sql.sql", "Table '%s' Entry %d Item %d: wrong MinCount (%d) - skipped", store.GetName(), entry, itemid, mincount);
        return false;
    }

    if (reference == 0)                                      // item (quest or non-quest) entry, maybe grouped
    {
        ItemTemplate const* proto = sObjectMgr->GetItemTemplate(itemid);
        if (!proto)
        {
            TC_LOG_ERROR("sql.sql", "Table '%s' Entry %d Item %d: item does not exist - skipped", store.GetName(), entry, itemid);
            return false;
        }

        if (chance == 0 && groupid == 0)                     // Zero chance is allowed for grouped entries only
        {
            TC_LOG_ERROR("sql.sql", "Table '%s' Entry %d Item %d: equal-chanced grouped entry, but group not defined - skipped", store.GetName(), entry, itemid);
            return false;
        }

        if (chance != 0 && chance < 0.000001f)             // loot with low chance
        {
            TC_LOG_ERROR("sql.sql", "Table '%s' Entry %d Item %d: low chance (%f) - skipped",
                store.GetName(), entry, itemid, chance);
            return false;
        }

        if (maxcount < mincount)                       // wrong max count
        {
            TC_LOG_ERROR("sql.sql", "Table '%s' Entry %d Item %d: MaxCount (%u) less that MinCount (%i) - skipped", store.GetName(), entry, itemid, int32(maxcount), mincount);
            return false;
        }
    }
    else                                                    // if reference loot
    {
        if (needs_quest)
            TC_LOG_ERROR("sql.sql", "Table '%s' Entry %d Item %d: quest required will be ignored", store.GetName(), entry, itemid);
        else if (chance == 0)                              // no chance for the reference
        {
            TC_LOG_ERROR("sql.sql", "Table '%s' Entry %d Item %d: zero chance is specified for a reference, skipped", store.GetName(), entry, itemid);
            return false;
        }
    }
    return true;                                            // Referenced template existence is checked at whole store level
}

ItemTemplate const* LootStoreItem::GetItemTemplate()
{
    if (type == LootItemType::Item)
        if (ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(itemid))
            return itemTemplate;

    return nullptr;
}


//
// --------- LootTemplate::LootGroup ---------
//

LootTemplate::LootGroup::~LootGroup()
{
    while (!ExplicitlyChanced.empty())
    {
        delete ExplicitlyChanced.back();
        ExplicitlyChanced.pop_back();
    }

    while (!EqualChanced.empty())
    {
        delete EqualChanced.back();
        EqualChanced.pop_back();
    }
}

// Adds an entry to the group (at loading stage)
void LootTemplate::LootGroup::AddEntry(LootStoreItem* item)
{
    if (item->chance != 0)
        ExplicitlyChanced.push_back(item);
    else
        EqualChanced.push_back(item);
}

// Rolls an item from the group, returns NULL if all miss their chances
LootStoreItem const* LootTemplate::LootGroup::Roll(Loot& loot, uint16 lootMode, Difficulty difficulty, Player const* player /*= nullptr*/, bool checkSpec /*= false*/) const
{
    LootStoreItemList possibleLoot = ExplicitlyChanced;
    possibleLoot.remove_if(LootGroupInvalidSelector(loot, lootMode, difficulty, player, checkSpec));

    if (!possibleLoot.empty())                             // First explicitly chanced entries are checked
    {
        float roll = (float)rand_chance();

        for (LootStoreItemList::const_iterator itr = possibleLoot.begin(); itr != possibleLoot.end(); ++itr)   // check each explicitly chanced entry in the template and modify its chance based on quality.
        {
            LootStoreItem* item = *itr;
            if (item->chance >= 100.0f)
                return item;

            roll -= item->chance;
            if (roll < 0)
                return item;
        }
    }

    possibleLoot = EqualChanced;
    possibleLoot.remove_if(LootGroupInvalidSelector(loot, lootMode, difficulty, player, checkSpec));
    if (!possibleLoot.empty())                              // If nothing selected yet - an item is taken from equal-chanced part
        return Trinity::Containers::SelectRandomContainerElement(possibleLoot);

    return NULL;                                            // Empty drop from the group
}

// True if group includes at least 1 quest drop entry
bool LootTemplate::LootGroup::HasQuestDrop() const
{
    for (LootStoreItemList::const_iterator i = ExplicitlyChanced.begin(); i != ExplicitlyChanced.end(); ++i)
        if ((*i)->needs_quest)
            return true;

    for (LootStoreItemList::const_iterator i = EqualChanced.begin(); i != EqualChanced.end(); ++i)
        if ((*i)->needs_quest)
            return true;

    return false;
}

// True if group includes at least 1 quest drop entry for active quests of the player
bool LootTemplate::LootGroup::HasQuestDropForPlayer(Player const* player) const
{
    for (LootStoreItemList::const_iterator i = ExplicitlyChanced.begin(); i != ExplicitlyChanced.end(); ++i)
        if (player->HasQuestForItem((*i)->itemid))
            return true;

    for (LootStoreItemList::const_iterator i = EqualChanced.begin(); i != EqualChanced.end(); ++i)
        if (player->HasQuestForItem((*i)->itemid))
            return true;

    return false;
}

void LootTemplate::LootGroup::CopyConditions(ConditionContainer /*conditions*/)
{
    for (LootStoreItemList::iterator i = ExplicitlyChanced.begin(); i != ExplicitlyChanced.end(); ++i)
        (*i)->conditions.clear();

    for (LootStoreItemList::iterator i = EqualChanced.begin(); i != EqualChanced.end(); ++i)
        (*i)->conditions.clear();
}

// Rolls an item from the group (if any takes its chance) and adds the item to the loot
void LootTemplate::LootGroup::Process(Loot& loot, uint16 lootMode, Difficulty difficulty, Player const* player, bool specOnly /*= false*/, bool personalLoot /*= false*/) const
{
    if (LootStoreItem const* item = Roll(loot, lootMode, difficulty, player, specOnly))
        loot.AddItem(*item, player, personalLoot);
}

void LootTemplate::FillAutoAssignationLoot(std::list<const ItemTemplate*>& itemList, Player* player, bool checkSpec /*= true*/, bool checkChance /*= true*/, bool challengeCheck /*= false*/) const
{
    InstanceScript* instance = player->GetInstanceScript();
    Difficulty difficulty = DIFFICULTY_NONE;
    if (instance && instance->instance)
        difficulty = instance->instance->GetDifficultyID();

    // Handle Items.
    if (!Entries.empty())
    {
        for (LootStoreItemList::const_iterator ItrA = Entries.begin(); ItrA != Entries.end(); ++ItrA)
        {
            if ((*ItrA)->type == LootItemType::Item)
            {
                if ((*ItrA)->difficulty && (*ItrA)->difficulty != difficulty)
                    continue;

                if ((*ItrA)->reference == 0)
                {
                    if (ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate((*ItrA)->itemid))
                    {
                        if (!player->CheckItemCompatibility(itemTemplate, checkSpec))
                            continue;

                        if (challengeCheck)
                        {
                           // if (sDB2Manager.IsAzeriteEmpoweredItem((*ItrA)->itemid))
                           //     continue;

                            if (itemTemplate->GetId() == ITEM_MYTHIC_KEYSTONE)
                                continue;

                            if (itemTemplate->IsOtherDrops() || itemTemplate->IsRecipe())
                                continue;
                        }

                        if (!(*ItrA)->chance || (*ItrA)->chance >= 100.0f || !checkChance)
                        {
                            itemList.push_back(itemTemplate);
                            continue;
                        }
                       
                        if (roll_chance_i((*ItrA)->chance))
                            itemList.push_back(itemTemplate);
                    }
                }
                else
                {
                    LootTemplate const * lootTemplate = LootTemplates_Reference.GetLootFor((*ItrA)->reference);
                    if (lootTemplate == nullptr)
                        continue;

                    if (!lootTemplate->Entries.empty())
                    {
                        for (LootStoreItemList::const_iterator ItrB = lootTemplate->Entries.begin(); ItrB != lootTemplate->Entries.end(); ++ItrB)
                        {
                            if ((*ItrB)->difficulty && (*ItrB)->difficulty != difficulty)
                                continue;

                            if (ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate((*ItrB)->itemid))
                            {
                                if (!player->CheckItemCompatibility(itemTemplate, checkSpec))
                                    continue;

                                if (challengeCheck)
                                {
                                    //if (sDB2Manager.IsAzeriteEmpoweredItem((*ItrB)->itemid))
                                    //    continue;

                                    if (itemTemplate->GetId() == ITEM_MYTHIC_KEYSTONE)
                                        continue;

                                    if (itemTemplate->IsOtherDrops() || itemTemplate->IsRecipe())
                                        continue;
                                }

                                if (!(*ItrB)->chance || (*ItrB)->chance >= 100.0f || !checkChance)
                                {
                                    itemList.push_back(itemTemplate);
                                    continue;
                                }

                                if (roll_chance_i((*ItrB)->chance))
                                    itemList.push_back(itemTemplate);
                            }
                        }
                    }
                    else if (!lootTemplate->Groups.empty())
                    {
                        for (LootGroup* groupLoot : lootTemplate->Groups)
                        {
                            LootStoreItemList* groupList = groupLoot->GetEqualChancedItemList();
                            if (groupList && !groupList->empty())
                            {
                                for (LootStoreItemList::const_iterator Itrc = groupList->begin(); Itrc != groupList->end(); ++Itrc)
                                {
                                    if ((*Itrc)->difficulty && (*Itrc)->difficulty != difficulty)
                                        continue;

                                    if (ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate((*Itrc)->itemid))
                                    {
                                        if (!player->CheckItemCompatibility(itemTemplate, checkSpec))
                                            continue;

                                        if (challengeCheck)
                                        {
                                            //if (sDB2Manager.IsAzeriteEmpoweredItem((*Itrc)->itemid))
                                            //    continue;

                                            if (itemTemplate->GetId() == ITEM_MYTHIC_KEYSTONE)
                                                continue;

                                            if (itemTemplate->IsOtherDrops() || itemTemplate->IsRecipe())
                                                continue;
                                        }

                                        if (!(*Itrc)->chance || (*Itrc)->chance >= 100.0f || !checkChance)
                                        {
                                            itemList.push_back(itemTemplate);
                                            continue;
                                        }

                                        if (roll_chance_i((*Itrc)->chance))
                                            itemList.push_back(itemTemplate);
                                    }
                                }
                            }

                            groupList = groupLoot->GetExplicitlyChancedItemList();
                            if (groupList && !groupList->empty())
                            {
                                for (LootStoreItemList::const_iterator Itrc = groupList->begin(); Itrc != groupList->end(); ++Itrc)
                                {
                                    if ((*Itrc)->difficulty && (*Itrc)->difficulty != difficulty)
                                        continue;

                                    if (ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate((*Itrc)->itemid))
                                    {
                                        if (!player->CheckItemCompatibility(itemTemplate, checkSpec))
                                            continue;

                                        if (challengeCheck)
                                        {
                                            //if (sDB2Manager.IsAzeriteEmpoweredItem((*Itrc)->itemid))
                                            //    continue;

                                            if (itemTemplate->GetId() == ITEM_MYTHIC_KEYSTONE)
                                                continue;

                                            if (itemTemplate->IsOtherDrops() || itemTemplate->IsRecipe())
                                                continue;
                                        }

                                        if (!(*Itrc)->chance || (*Itrc)->chance >= 100.0f || !checkChance)
                                        {
                                            itemList.push_back(itemTemplate);
                                            continue;
                                        }

                                        if (roll_chance_i((*Itrc)->chance))
                                            itemList.push_back(itemTemplate);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        // Handle Groups.
        if (!Groups.empty())
        {
            for (auto iterA : Groups)
            {
                LootStoreItemList* list = iterA->GetExplicitlyChancedItemList();
                if (list && !list->empty())
                {
                    for (LootStoreItemList::const_iterator Itrc = list->begin(); Itrc != list->end(); ++Itrc)
                    {
                        if ((*Itrc)->difficulty && (*Itrc)->difficulty != difficulty)
                            continue;

                        if (ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate((*Itrc)->itemid))
                        {
                            if (!player->CheckItemCompatibility(itemTemplate, checkSpec))
                                continue;

                            if (challengeCheck)
                            {
                                //if (sDB2Manager.IsAzeriteEmpoweredItem((*Itrc)->itemid))
                                //    continue;

                                if (itemTemplate->GetId() == ITEM_MYTHIC_KEYSTONE)
                                    continue;

                                if (itemTemplate->IsOtherDrops() || itemTemplate->IsRecipe())
                                    continue;
                            }

                            if (!(*Itrc)->chance || (*Itrc)->chance >= 100.0f || !checkChance)
                            {
                                itemList.push_back(itemTemplate);
                                continue;
                            }

                            if (roll_chance_i((*Itrc)->chance))
                                itemList.push_back(itemTemplate);
                        }
                    }
                }
            }
        }
    }        
}

// Overall chance for the group without equal chanced items
float LootTemplate::LootGroup::RawTotalChance() const
{
    float result = 0;

    for (LootStoreItemList::const_iterator i=ExplicitlyChanced.begin(); i != ExplicitlyChanced.end(); ++i)
        if (!(*i)->needs_quest)
            result += (*i)->chance;

    return result;
}

// Overall chance for the group
float LootTemplate::LootGroup::TotalChance() const
{
    float result = RawTotalChance();

    if (!EqualChanced.empty() && result < 100.0f)
        return 100.0f;

    return result;
}

void LootTemplate::LootGroup::Verify(LootStore const& lootstore, uint32 id, uint8 group_id) const
{
    float chance = RawTotalChance();
    if (chance > 101.0f)                                    /// @todo replace with 100% when DBs will be ready
        TC_LOG_ERROR("sql.sql", "Table '%s' entry %u group %d has total chance > 100%% (%f)", lootstore.GetName(), id, group_id, chance);

    if (chance >= 100.0f && !EqualChanced.empty())
        TC_LOG_ERROR("sql.sql", "Table '%s' entry %u group %d has items with chance=0%% but group total chance >= 100%% (%f)", lootstore.GetName(), id, group_id, chance);
}

void LootTemplate::LootGroup::CheckLootRefs(LootTemplateMap const& /*store*/, LootIdSet* ref_set) const
{
    for (LootStoreItemList::const_iterator ieItr = ExplicitlyChanced.begin(); ieItr != ExplicitlyChanced.end(); ++ieItr)
    {
        LootStoreItem* item = *ieItr;
        if (item->reference > 0)
        {
            if (!LootTemplates_Reference.GetLootFor(item->reference))
                LootTemplates_Reference.ReportNonExistingId(item->reference, "Reference", item->itemid);
            else if (ref_set)
                ref_set->erase(item->reference);
        }
    }

    for (LootStoreItemList::const_iterator ieItr = EqualChanced.begin(); ieItr != EqualChanced.end(); ++ieItr)
    {
        LootStoreItem* item = *ieItr;
        if (item->reference > 0)
        {
            if (!LootTemplates_Reference.GetLootFor(item->reference))
                LootTemplates_Reference.ReportNonExistingId(item->reference, "Reference", item->itemid);
            else if (ref_set)
                ref_set->erase(item->reference);
        }
    }
}

//
// --------- LootTemplate ---------
//

LootTemplate::~LootTemplate()
{
    for (LootStoreItemList::iterator i = Entries.begin(); i != Entries.end(); ++i)
        delete *i;

    for (size_t i = 0; i < Groups.size(); ++i)
        delete Groups[i];
}

// Adds an entry to the group (at loading stage)
void LootTemplate::AddEntry(LootStoreItem* item)
{
    if (item->groupid > 0 && item->reference == 0)            // Group
    {
        if (item->groupid >= Groups.size())
            Groups.resize(item->groupid, nullptr);            // Adds new group the the loot template if needed
        if (!Groups[item->groupid - 1])
            Groups[item->groupid - 1] = new LootGroup();

        Groups[item->groupid - 1]->AddEntry(item);            // Adds new entry to the group
    }
    else                                                      // Non-grouped entries and references are stored together
        Entries.push_back(item);
}

void LootTemplate::CopyConditions(ConditionContainer const& conditions)
{
    for (LootStoreItemList::iterator i = Entries.begin(); i != Entries.end(); ++i)
        (*i)->conditions.clear();

    for (LootGroups::iterator i = Groups.begin(); i != Groups.end(); ++i)
        if (LootGroup* group = *i)
            group->CopyConditions(conditions);
}

void LootTemplate::CopyConditions(LootItem* li) const
{
    // Copies the conditions list from a template item to a LootItemData
    for (LootStoreItemList::const_iterator _iter = Entries.begin(); _iter != Entries.end(); ++_iter)
    {
        LootStoreItem* item = *_iter;
        if (item->itemid != li->itemid)
            continue;

        li->conditions = item->conditions;
        break;
    }
}

// Rolls for every item in the template and adds the rolled items the the loot
void LootTemplate::Process(Loot& loot, bool rate, uint16 lootMode, Difficulty difficulty, uint8 groupId, Player const* player, bool specOnly /*= false*/, bool personaLoot /*= false*/, bool fishing /*= false*/) const
{
    if (groupId)                                            // Group reference uses own processing of the group
    {
        if (groupId > Groups.size())
            return;                                         // Error message already printed at loading stage

        if (!Groups[groupId - 1])
            return;

        Groups[groupId - 1]->Process(loot, lootMode, difficulty, player, specOnly, personaLoot);
        return;
    }

    // Rolling non-grouped items
    for (LootStoreItemList::const_iterator i = Entries.begin(); i != Entries.end(); ++i)
    {
        LootStoreItem* item = *i;

        if (!(item->lootmode & lootMode) || (item->difficulty && item->difficulty != difficulty)) // Do not add if mode or difficulty mismatch
            continue;

        // Process bait chance here.
        uint8 extraChance = 0;
        //if (fishing)
        //    extraChance = sLootExtra->GetItemExtra(player, item->itemid);

        if (!item->Roll(rate, extraChance, player, specOnly))
            continue;                                       // Bad luck for the entry

        if (item->reference > 0)                            // References processing
        {
            LootTemplate const* Referenced = LootTemplates_Reference.GetLootFor(item->reference);
            if (!Referenced)
                continue;                                       // Error message already printed at loading stage

            uint32 maxcount = uint32(float(item->maxcount) * sWorld->getRate(RATE_DROP_ITEM_REFERENCED_AMOUNT));
            for (uint32 loop = 0; loop < maxcount; ++loop)      // Ref multiplicator
                Referenced->Process(loot, rate, lootMode, difficulty, item->groupid, player, specOnly, personaLoot);
        }
        else                                                    // Plain entries (not a reference, not grouped)
            loot.AddItem(*item, player, personaLoot);       // Chance is already checked, just add
    }

    // Now processing groups
    for (LootGroups::const_iterator i = Groups.begin(); i != Groups.end(); ++i)
        if (LootGroup* group = *i)
            group->Process(loot, lootMode, difficulty, player, specOnly, personaLoot);
}

void LootTemplate::ProcessOploteChest(Loot& loot) const
{
    Player const* lootOwner = ObjectAccessor::FindPlayer(loot.GetLootOwnerGuid());
    if (!lootOwner)
        return;

    LootStoreItemList ItemPossibleDrops;
    LootStoreItemList OtherPossibleDrops;

    // Rolling non-grouped items
    for (LootStoreItemList::const_iterator i = Entries.begin(); i != Entries.end(); ++i)
    {
        LootStoreItem* item = *i;

        if (item->needs_quest) //Don`t add quest item
        {
            OtherPossibleDrops.push_back(*i);
            continue;
        }

        if (item->type == LootItemType::Currency) //In BFA always gonna give Azerite, then we don't check the chance
            continue;

        if (item->reference && item->type == LootItemType::Item)              // References processing
            continue;

        if (item->type == LootItemType::Item)
        {
            if (ItemTemplate const* _proto = sObjectMgr->GetItemTemplate(item->itemid))
            {
                if (!lootOwner->CheckItemCompatibility(_proto, true))
                    continue;

                if (_proto->GetId() == ITEM_MYTHIC_KEYSTONE)
                    continue;

                if (_proto->IsOtherDrops() || _proto->IsRecipe() || _proto->IsCraftingReagent())
                    continue;
            }
            else
                continue;
        }

        ItemPossibleDrops.push_back(*i);
    }

    if (!ItemPossibleDrops.empty()) // If nothing selected yet - an item is taken from equal-chanced part
    {
        LootStoreItemList::iterator itr = ItemPossibleDrops.begin();
        std::advance(itr, irand(0, ItemPossibleDrops.size() - 1));
        LootStoreItem* item = *itr;
        loot.AddItem(*item, lootOwner, true, true);
    }

    //1200 of currency for the weekly chest in 8.0.1
   // loot.AddItem(LootStoreItem(CURRENCY_TYPE_AZERITE, LootItemType::Currency, 0, 100, 0, LOOT_MODE_DEFAULT, 1, 1200, 1200), lootOwner, true);

    for (LootStoreItemList::const_iterator i = OtherPossibleDrops.begin(); i != OtherPossibleDrops.end(); ++i)
    {
        LootStoreItem* item = *i;

        if (!item->Roll(false))
            continue;

        loot.AddItem(*item, lootOwner, true);
    }

    //if (loot.GetChallengeLevel() > MYTHIC_LEVEL_2) // Prevent bug with 1 level key Oo
    //{
    //    loot.SetChallengeMap(const_cast<Player*>(lootOwner)->m_challengeKeyInfo.ID);
    //    const_cast<Player*>(lootOwner)->m_challengeKeyInfo.Level = loot.GetRealChallengeLevel() - MYTHIC_LEVEL_1;
    //    loot.AddItem(LootStoreItem(ITEM_MYTHIC_KEYSTONE, LOOT_ITEM_TYPE_ITEM, 0, 100.0f, 0, LOOT_MODE_DEFAULT, 1, 1, 1), lootOwner, true);       
    //}
}

void LootTemplate::ProcessChallengeChest(Loot& loot, uint32 lootId, Challenge* _challenge, bool rate, uint16 lootMode, Difficulty difficulty) const
{
    Player const* lootOwner = ObjectAccessor::FindPlayer(loot.GetLootOwnerGuid());
    if (!lootOwner)
        return;

    LootStoreItemList ItemPossibleDrops;
    LootStoreItemList OtherPossibleDrops;

    // Rolling non-grouped items
    for (LootStoreItemList::const_iterator i = Entries.begin(); i != Entries.end(); ++i)
    {
        LootStoreItem* item = *i;
        if (item->needs_quest) //Don`t add quest item
        {
            OtherPossibleDrops.push_back(*i);
            continue;
        }

        if (item->type == LootItemType::Currency)
        {
            OtherPossibleDrops.push_back(*i);
            continue;
        }

        if (!item->Roll(true, 0.0f, lootOwner, true))
            continue;                                       // Bad luck for the entry

        if (item->reference > 0)                            // References processing
        {
            LootTemplate const* Referenced = LootTemplates_Reference.GetLootFor(item->reference);
            if (!Referenced)
                continue;                                       // Error message already printed at loading stage

            uint32 maxcount = uint32(float(item->maxcount) * sWorld->getRate(RATE_DROP_ITEM_REFERENCED_AMOUNT));
            for (uint32 loop = 0; loop < maxcount; ++loop)      // Ref multiplicator
                Referenced->Process(loot, rate, lootMode, difficulty, item->groupid, lootOwner, true, true);

            continue;
        }

        if (item->type == LootItemType::Item)
        {
            if (ItemTemplate const* _proto = sObjectMgr->GetItemTemplate(item->itemid))
            {
                //if (sDB2Manager.IsAzeriteEmpoweredItem(item->itemid))
                //    continue;

                if (!lootOwner->CheckItemCompatibility(_proto, true))
                    continue;

                if (_proto->GetId() == ITEM_MYTHIC_KEYSTONE)
                    continue;

                if (_proto->IsOtherDrops() || _proto->IsRecipe())                
                    continue;
            }
            else
                continue;
        }

        ItemPossibleDrops.push_back(*i);
    }

    if (!ItemPossibleDrops.empty()) // If nothing selected yet - an item is taken from equal-chanced part
    {
        Trinity::Containers::RandomResize(ItemPossibleDrops, _challenge->GetItemCount(lootOwner->GetGUID()));
        for (auto const& item : ItemPossibleDrops)        
            loot.AddItem(*item, lootOwner, true);
    }

    for (LootStoreItemList::const_iterator i = OtherPossibleDrops.begin(); i != OtherPossibleDrops.end(); ++i)
    {
        LootStoreItem* item = *i;
        if (!item->Roll(false))
            continue;                                         // Bad luck for the entry

        loot.AddItem(*item, lootOwner, true);                                 // Chance is already checked, just add                                                          
    }

    //if (!const_cast<Player*>(lootOwner)->m_challengeKeyInfo.IsActive() && !sChallengeModeMgr->HasOploteLoot(lootOwner->GetGUID()))
    //{
    //    const_cast<Player*>(lootOwner)->m_challengeKeyInfo.Level = _challenge->GetChallengeLevel() - MYTHIC_LEVEL_1;
    //    loot.AddItem(LootStoreItem(ITEM_MYTHIC_KEYSTONE, LOOT_ITEM_TYPE_ITEM, 0, 100.0f, 0, LOOT_MODE_DEFAULT, 1, 1, 1), lootOwner, true);
    //}
}

// True if template includes at least 1 quest drop entry
bool LootTemplate::HasQuestDrop(LootTemplateMap const& store, uint8 groupId) const
{
    if (groupId)                                            // Group reference
    {
        if (groupId > Groups.size())
            return false;                                   // Error message [should be] already printed at loading stage

        if (!Groups[groupId - 1])
            return false;

        return Groups[groupId-1]->HasQuestDrop();
    }

    for (LootStoreItemList::const_iterator i = Entries.begin(); i != Entries.end(); ++i)
    {
        LootStoreItem* item = *i;
        if (item->reference > 0)                        // References
        {
            LootTemplateMap::const_iterator Referenced = store.find(item->reference);
            if (Referenced == store.end())
                continue;                                   // Error message [should be] already printed at loading stage
            if (Referenced->second->HasQuestDrop(store, item->groupid))
                return true;
        }
        else if (item->needs_quest)
            return true;                                    // quest drop found
    }

    // Now processing groups
    for (LootGroups::const_iterator i = Groups.begin(); i != Groups.end(); ++i)
        if (LootGroup* group = *i)
            if (group->HasQuestDrop())
                return true;

    return false;
}

// True if template includes at least 1 quest drop for an active quest of the player
bool LootTemplate::HasQuestDropForPlayer(LootTemplateMap const& store, Player const* player, uint8 groupId) const
{
    if (groupId)                                            // Group reference
    {
        if (groupId > Groups.size())
            return false;                                   // Error message already printed at loading stage

        if (!Groups[groupId - 1])
            return false;

        return Groups[groupId - 1]->HasQuestDropForPlayer(player);
    }

    // Checking non-grouped entries
    for (LootStoreItemList::const_iterator i = Entries.begin(); i != Entries.end(); ++i)
    {
        LootStoreItem* item = *i;
        if (item->reference > 0)                        // References processing
        {
            LootTemplateMap::const_iterator Referenced = store.find(item->reference);
            if (Referenced == store.end())
                continue;                                   // Error message already printed at loading stage
            if (Referenced->second->HasQuestDropForPlayer(store, player, item->groupid))
                return true;
        }
        else if (player->HasQuestForItem(item->itemid))
            return true;                                    // active quest drop found
    }

    // Now checking groups
    for (LootGroups::const_iterator i = Groups.begin(); i != Groups.end(); ++i)
        if (LootGroup* group = *i)
            if (group->HasQuestDropForPlayer(player))
                return true;

    return false;
}

// Checks integrity of the template
void LootTemplate::Verify(LootStore const& lootstore, uint32 id) const
{
    // Checking group chances
    for (uint32 i = 0; i < Groups.size(); ++i)
        if (Groups[i])
            Groups[i]->Verify(lootstore, id, i + 1);

    /// @todo References validity checks
}

void LootTemplate::CheckLootRefs(LootTemplateMap const& store, LootIdSet* ref_set) const
{
    for (LootStoreItemList::const_iterator ieItr = Entries.begin(); ieItr != Entries.end(); ++ieItr)
    {
        LootStoreItem* item = *ieItr;
        if (item->reference > 0)
        {
            if (!LootTemplates_Reference.GetLootFor(item->reference))
                LootTemplates_Reference.ReportNonExistingId(item->reference, "Reference", item->itemid);
            else if (ref_set)
                ref_set->erase(item->reference);
        }
    }

    for (LootGroups::const_iterator grItr = Groups.begin(); grItr != Groups.end(); ++grItr)
        if (LootGroup* group = *grItr)
            group->CheckLootRefs(store, ref_set);
}

bool LootTemplate::addConditionItem(Condition* cond)
{
    if (!cond || !cond->isLoaded())//should never happen, checked at loading
    {
        TC_LOG_ERROR("loot", "LootTemplate::addConditionItem: condition is null");
        return false;
    }

    if (!Entries.empty())
    {
        for (LootStoreItemList::iterator i = Entries.begin(); i != Entries.end(); ++i)
        {
            if ((*i)->itemid == uint32(cond->SourceEntry))
            {
                (*i)->conditions.push_back(cond);
                return true;
            }
        }
    }

    if (!Groups.empty())
    {
        for (LootGroups::iterator groupItr = Groups.begin(); groupItr != Groups.end(); ++groupItr)
        {
            LootGroup* group = *groupItr;
            if (!group)
                continue;

            LootStoreItemList* itemList = group->GetExplicitlyChancedItemList();
            if (!itemList->empty())
            {
                for (LootStoreItemList::iterator i = itemList->begin(); i != itemList->end(); ++i)
                {
                    if ((*i)->itemid == uint32(cond->SourceEntry))
                    {
                        (*i)->conditions.push_back(cond);
                        return true;
                    }
                }
            }

            itemList = group->GetEqualChancedItemList();
            if (!itemList->empty())
            {
                for (LootStoreItemList::iterator i = itemList->begin(); i != itemList->end(); ++i)
                {
                    if ((*i)->itemid == uint32(cond->SourceEntry))
                    {
                        (*i)->conditions.push_back(cond);
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool LootTemplate::isReference(uint32 id)
{
    for (LootStoreItemList::const_iterator ieItr = Entries.begin(); ieItr != Entries.end(); ++ieItr)
        if ((*ieItr)->itemid == id && (*ieItr)->reference > 0)
            return true;

    return false;//not found or not reference
}

void LoadLootTemplates_Creature()
{
    TC_LOG_INFO("server.loading", "Loading creature loot templates...");

    uint32 oldMSTime = getMSTime();

    LootIdSet lootIdSet, lootIdSetUsed;
    uint32 count = LootTemplates_Creature.LoadAndCollectLootIds(lootIdSet);

    // Remove real entries and check loot existence
    CreatureTemplateContainer const& ctc = sObjectMgr->GetCreatureTemplates();
    for (auto const& creatureTemplatePair : ctc)
    {
        if (uint32 lootid = creatureTemplatePair.second.lootid)
        {
            if (!lootIdSet.count(lootid))
                LootTemplates_Creature.ReportNonExistingId(lootid, "Creature", creatureTemplatePair.first);
            else
                lootIdSetUsed.insert(lootid);
        }
    }

    for (LootIdSet::const_iterator itr = lootIdSetUsed.begin(); itr != lootIdSetUsed.end(); ++itr)
        lootIdSet.erase(*itr);

    // 1 means loot for player corpse
    lootIdSet.erase(PLAYER_CORPSE_LOOT_ENTRY);

    // output error for any still listed (not referenced from appropriate table) ids
    LootTemplates_Creature.ReportUnusedIds(lootIdSet);

    if (count)
        TC_LOG_INFO("server.loading", ">> Loaded %u creature loot templates in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
    else
        TC_LOG_INFO("server.loading", ">> Loaded 0 creature loot templates. DB table `creature_loot_template` is empty");
}

void LoadLootTemplates_Disenchant()
{
    TC_LOG_INFO("server.loading", "Loading disenchanting loot templates...");

    uint32 oldMSTime = getMSTime();

    LootIdSet lootIdSet, lootIdSetUsed;
    uint32 count = LootTemplates_Disenchant.LoadAndCollectLootIds(lootIdSet);

    for (ItemDisenchantLootEntry const* disenchant : sItemDisenchantLootStore)
    {
        uint32 lootid = disenchant->ID;
        if (lootIdSet.find(lootid) == lootIdSet.end())
            LootTemplates_Disenchant.ReportNonExistingId(lootid);
        else
            lootIdSetUsed.insert(lootid);
    }

    for (LootIdSet::const_iterator itr = lootIdSetUsed.begin(); itr != lootIdSetUsed.end(); ++itr)
        lootIdSet.erase(*itr);

    // output error for any still listed (not referenced from appropriate table) ids
    LootTemplates_Disenchant.ReportUnusedIds(lootIdSet);

    if (count)
        TC_LOG_INFO("server.loading", ">> Loaded %u disenchanting loot templates in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
    else
        TC_LOG_INFO("server.loading", ">> Loaded 0 disenchanting loot templates. DB table `disenchant_loot_template` is empty");
}

void LoadLootTemplates_Fishing()
{
    TC_LOG_INFO("server.loading", "Loading fishing loot templates...");

    uint32 oldMSTime = getMSTime();

    LootIdSet lootIdSet;
    uint32 count = LootTemplates_Fishing.LoadAndCollectLootIds(lootIdSet);

    // remove real entries and check existence loot
    for (AreaTableEntry const* areaTable : sAreaTableStore)
        if (lootIdSet.find(areaTable->ID) != lootIdSet.end())
            lootIdSet.erase(areaTable->ID);

    // output error for any still listed (not referenced from appropriate table) ids
    LootTemplates_Fishing.ReportUnusedIds(lootIdSet);

    if (count)
        TC_LOG_INFO("server.loading", ">> Loaded %u fishing loot templates in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
    else
        TC_LOG_INFO("server.loading", ">> Loaded 0 fishing loot templates. DB table `fishing_loot_template` is empty");
}

void LoadLootTemplates_Gameobject()
{
    TC_LOG_INFO("server.loading", "Loading gameobject loot templates...");

    uint32 oldMSTime = getMSTime();

    LootIdSet lootIdSet, lootIdSetUsed;
    uint32 count = LootTemplates_Gameobject.LoadAndCollectLootIds(lootIdSet);

    // remove real entries and check existence loot
    GameObjectTemplateContainer const& gotc = sObjectMgr->GetGameObjectTemplates();
    for (auto const& gameObjectTemplatePair : gotc)
    {
        if (uint32 lootid = gameObjectTemplatePair.second.GetLootId())
        {
            if (!lootIdSet.count(lootid))
                LootTemplates_Gameobject.ReportNonExistingId(lootid, "Gameobject", gameObjectTemplatePair.first);
            else
                lootIdSetUsed.insert(lootid);
        }
    }

    for (LootIdSet::const_iterator itr = lootIdSetUsed.begin(); itr != lootIdSetUsed.end(); ++itr)
        lootIdSet.erase(*itr);

    // output error for any still listed (not referenced from appropriate table) ids
    LootTemplates_Gameobject.ReportUnusedIds(lootIdSet);

    if (count)
        TC_LOG_INFO("server.loading", ">> Loaded %u gameobject loot templates in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
    else
        TC_LOG_INFO("server.loading", ">> Loaded 0 gameobject loot templates. DB table `gameobject_loot_template` is empty");
}

void LoadLootTemplates_Item()
{
    TC_LOG_INFO("server.loading", "Loading item loot templates...");

    uint32 oldMSTime = getMSTime();

    LootIdSet lootIdSet;
    uint32 count = LootTemplates_Item.LoadAndCollectLootIds(lootIdSet);

    // remove real entries and check existence loot
    ItemTemplateContainer const& its = sObjectMgr->GetItemTemplateStore();
    for (auto const& itemTemplatePair : its)
        if (lootIdSet.count(itemTemplatePair.first) > 0 && itemTemplatePair.second.HasFlag(ITEM_FLAG_HAS_LOOT))
            lootIdSet.erase(itemTemplatePair.first);

    // output error for any still listed (not referenced from appropriate table) ids
    LootTemplates_Item.ReportUnusedIds(lootIdSet);

    if (count)
        TC_LOG_INFO("server.loading", ">> Loaded %u item loot templates in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
    else
        TC_LOG_INFO("server.loading", ">> Loaded 0 item loot templates. DB table `item_loot_template` is empty");
}

void LoadLootTemplates_Milling()
{
    TC_LOG_INFO("server.loading", "Loading milling loot templates...");

    uint32 oldMSTime = getMSTime();

    LootIdSet lootIdSet;
    uint32 count = LootTemplates_Milling.LoadAndCollectLootIds(lootIdSet);

    // remove real entries and check existence loot
    ItemTemplateContainer const& its = sObjectMgr->GetItemTemplateStore();
    for (auto const& itemTemplatePair : its)
    {
        if (!itemTemplatePair.second.HasFlag(ITEM_FLAG_IS_MILLABLE))
            continue;

        if (lootIdSet.count(itemTemplatePair.first) > 0)
            lootIdSet.erase(itemTemplatePair.first);
    }

    // output error for any still listed (not referenced from appropriate table) ids
    LootTemplates_Milling.ReportUnusedIds(lootIdSet);

    if (count)
        TC_LOG_INFO("server.loading", ">> Loaded %u milling loot templates in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
    else
        TC_LOG_INFO("server.loading", ">> Loaded 0 milling loot templates. DB table `milling_loot_template` is empty");
}

void LoadLootTemplates_Pickpocketing()
{
    TC_LOG_INFO("server.loading", "Loading pickpocketing loot templates...");

    uint32 oldMSTime = getMSTime();

    LootIdSet lootIdSet, lootIdSetUsed;
    uint32 count = LootTemplates_Pickpocketing.LoadAndCollectLootIds(lootIdSet);

    // Remove real entries and check loot existence
    CreatureTemplateContainer const& ctc = sObjectMgr->GetCreatureTemplates();
    for (auto const& creatureTemplatePair : ctc)
    {
        if (uint32 lootid = creatureTemplatePair.second.pickpocketLootId)
        {
            if (!lootIdSet.count(lootid))
                LootTemplates_Pickpocketing.ReportNonExistingId(lootid, "Creature", creatureTemplatePair.first);
            else
                lootIdSetUsed.insert(lootid);
        }
    }

    for (LootIdSet::const_iterator itr = lootIdSetUsed.begin(); itr != lootIdSetUsed.end(); ++itr)
        lootIdSet.erase(*itr);

    // output error for any still listed (not referenced from appropriate table) ids
    LootTemplates_Pickpocketing.ReportUnusedIds(lootIdSet);

    if (count)
        TC_LOG_INFO("server.loading", ">> Loaded %u pickpocketing loot templates in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
    else
        TC_LOG_INFO("server.loading", ">> Loaded 0 pickpocketing loot templates. DB table `pickpocketing_loot_template` is empty");
}

void LoadLootTemplates_Prospecting()
{
    TC_LOG_INFO("server.loading", "Loading prospecting loot templates...");

    uint32 oldMSTime = getMSTime();

    LootIdSet lootIdSet;
    uint32 count = LootTemplates_Prospecting.LoadAndCollectLootIds(lootIdSet);

    // remove real entries and check existence loot
    ItemTemplateContainer const& its = sObjectMgr->GetItemTemplateStore();
    for (auto const& itemTemplatePair : its)
    {
        if (!itemTemplatePair.second.HasFlag(ITEM_FLAG_IS_PROSPECTABLE))
            continue;

        if (lootIdSet.count(itemTemplatePair.first) > 0)
            lootIdSet.erase(itemTemplatePair.first);
    }

    // output error for any still listed (not referenced from appropriate table) ids
    LootTemplates_Prospecting.ReportUnusedIds(lootIdSet);

    if (count)
        TC_LOG_INFO("server.loading", ">> Loaded %u prospecting loot templates in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
    else
        TC_LOG_INFO("server.loading", ">> Loaded 0 prospecting loot templates. DB table `prospecting_loot_template` is empty");
}

void LoadLootTemplates_Mail()
{
    TC_LOG_INFO("server.loading", "Loading mail loot templates...");

    uint32 oldMSTime = getMSTime();

    LootIdSet lootIdSet;
    uint32 count = LootTemplates_Mail.LoadAndCollectLootIds(lootIdSet);

    // remove real entries and check existence loot
    for (uint32 i = 1; i < sMailTemplateStore.GetNumRows(); ++i)
        if (sMailTemplateStore.LookupEntry(i))
            if (lootIdSet.find(i) != lootIdSet.end())
                lootIdSet.erase(i);

    // output error for any still listed (not referenced from appropriate table) ids
    LootTemplates_Mail.ReportUnusedIds(lootIdSet);

    if (count)
        TC_LOG_INFO("server.loading", ">> Loaded %u mail loot templates in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
    else
        TC_LOG_INFO("server.loading", ">> Loaded 0 mail loot templates. DB table `mail_loot_template` is empty");
}

void LoadLootTemplates_Skinning()
{
    TC_LOG_INFO("server.loading", "Loading skinning loot templates...");

    uint32 oldMSTime = getMSTime();

    LootIdSet lootIdSet, lootIdSetUsed;
    uint32 count = LootTemplates_Skinning.LoadAndCollectLootIds(lootIdSet);

    // remove real entries and check existence loot
    CreatureTemplateContainer const& ctc = sObjectMgr->GetCreatureTemplates();
    for (auto const& creatureTemplatePair : ctc)
    {
        if (uint32 lootid = creatureTemplatePair.second.SkinLootId)
        {
            if (!lootIdSet.count(lootid))
                LootTemplates_Skinning.ReportNonExistingId(lootid, "Creature", creatureTemplatePair.first);
            else
                lootIdSetUsed.insert(lootid);
        }
    }

    for (LootIdSet::const_iterator itr = lootIdSetUsed.begin(); itr != lootIdSetUsed.end(); ++itr)
        lootIdSet.erase(*itr);

    // output error for any still listed (not referenced from appropriate table) ids
    LootTemplates_Skinning.ReportUnusedIds(lootIdSet);

    if (count)
        TC_LOG_INFO("server.loading", ">> Loaded %u skinning loot templates in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
    else
        TC_LOG_INFO("server.loading", ">> Loaded 0 skinning loot templates. DB table `skinning_loot_template` is empty");
}

void LoadLootTemplates_Spell()
{
    // TODO: change this to use MiscValue from spell effect as id instead of spell id
    TC_LOG_INFO("server.loading", "Loading spell loot templates...");

    uint32 oldMSTime = getMSTime();

    LootIdSet lootIdSet;
    uint32 count = LootTemplates_Spell.LoadAndCollectLootIds(lootIdSet);

    // remove real entries and check existence loot
    for (SpellNameEntry const* spellNameEntry : sSpellNameStore)
    {
        SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(spellNameEntry->ID, DIFFICULTY_NONE);
        if (!spellInfo)
            continue;

        // possible cases
        if (!spellInfo->IsLootCrafting())
            continue;

        if (lootIdSet.find(spellInfo->Id) == lootIdSet.end())
        {
            // not report about not trainable spells (optionally supported by DB)
            // ignore 61756 (Northrend Inscription Research (FAST QA VERSION) for example
            if (!spellInfo->HasAttribute(SPELL_ATTR0_NOT_SHAPESHIFTED) || spellInfo->HasAttribute(SPELL_ATTR0_IS_TRADESKILL))
                LootTemplates_Spell.ReportNonExistingId(spellInfo->Id, "Spell", spellInfo->Id);
        }
        else
            lootIdSet.erase(spellInfo->Id);
    }

    // output error for any still listed (not referenced from appropriate table) ids
    LootTemplates_Spell.ReportUnusedIds(lootIdSet);

    if (count)
        TC_LOG_INFO("server.loading", ">> Loaded %u spell loot templates in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
    else
        TC_LOG_INFO("server.loading", ">> Loaded 0 spell loot templates. DB table `spell_loot_template` is empty");
}

void LoadLootTemplates_Reference()
{
    TC_LOG_INFO("server.loading", "Loading reference loot templates...");

    uint32 oldMSTime = getMSTime();

    LootIdSet lootIdSet;
    LootTemplates_Reference.LoadAndCollectLootIds(lootIdSet);

    // check references and remove used
    LootTemplates_Creature.CheckLootRefs(&lootIdSet);
    LootTemplates_Fishing.CheckLootRefs(&lootIdSet);
    LootTemplates_Gameobject.CheckLootRefs(&lootIdSet);
    LootTemplates_Item.CheckLootRefs(&lootIdSet);
    LootTemplates_Milling.CheckLootRefs(&lootIdSet);
    LootTemplates_Pickpocketing.CheckLootRefs(&lootIdSet);
    LootTemplates_Skinning.CheckLootRefs(&lootIdSet);
    LootTemplates_Disenchant.CheckLootRefs(&lootIdSet);
    LootTemplates_Prospecting.CheckLootRefs(&lootIdSet);
    LootTemplates_Mail.CheckLootRefs(&lootIdSet);
    LootTemplates_Reference.CheckLootRefs(&lootIdSet);

    // output error for any still listed ids (not referenced from any loot table)
    LootTemplates_Reference.ReportUnusedIds(lootIdSet);

    TC_LOG_INFO("server.loading", ">> Loaded reference loot templates in %u ms", GetMSTimeDiffToNow(oldMSTime));
}

void LoadLootTables()
{
    LoadLootTemplates_Creature();
    LoadLootTemplates_Fishing();
    LoadLootTemplates_Gameobject();
    LoadLootTemplates_Item();
    LoadLootTemplates_Mail();
    LoadLootTemplates_Milling();
    LoadLootTemplates_Pickpocketing();
    LoadLootTemplates_Skinning();
    LoadLootTemplates_Disenchant();
    LoadLootTemplates_Prospecting();
    LoadLootTemplates_Spell();

    LoadLootTemplates_Reference();
}
