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

#ifndef TRINITYCORE_GOSSIP_H
#define TRINITYCORE_GOSSIP_H

#include "Common.h"
#include "ObjectGuid.h"
#include <map>
#include <functional>

class Object;
class Quest;
class WorldSession;
enum class QuestGiverStatus : uint32;

#define GOSSIP_MAX_MENU_ITEMS               32
#define DEFAULT_GOSSIP_MESSAGE              0xffffff

enum class GossipOptionNpc : uint8
{
    None                       = 0,    // White chat bubble. Default
    Vendor                     = 1,    // Brown bag
    TaxiNode                   = 2,    // White wing
    Trainer                    = 3,    // Brown book
    SpiritHealer               = 4,    // Golden interaction wheel (with red center)
    Binder                     = 5,    // Golden interaction wheel
    Banker                     = 6,    // Brown bag (with gold coin in lower corner)
    PetitionVendor             = 7,    // White chat bubble (with "..." inside)
    TabardVendor               = 8,    // White tabard
    BattleMaster               = 9,    // Two crossed swords
    Auctioneer                 = 10,   // Stack of gold coins
    TalentMaster               = 11,   // White chat bubble
    StableMaster               = 12,   // White chat bubble
    PetSpecializationMaster    = 13,   /*DEPRECATED*/ // White chat bubble
    GuildBanker                = 14,   /*NYI*/ // White chat bubble
    SpellClick                 = 15,   /*NYI*/ // White chat bubble
    DisableXPGain              = 16,   // White chat bubble
    EnableXPGain               = 17,   // White chat bubble
    Mailbox                    = 18,   // White chat bubble
    WorldPVPQueue              = 19,   /*NYI*/ // White chat bubble
    LFGDungeon                 = 20,   /*NYI*/ // White chat bubble
    ArtifactRespec             = 21,   /*NYI*/ // White chat bubble
    CemeterySelect             = 22,   /*DEPRECATED*/ // White chat bubble
    SpecializationMaster       = 23,   /*DEPRECATED*/ // White chat bubble
    GlyphMaster                = 24,   /*DEPRECATED*/ // White chat bubble
    QueueScenario              = 25,   /*NYI*/ // White chat bubble
    GarrisonArchitect          = 26,   /*NYI*/ // White chat bubble
    GarrisonMission            = 27,   /*NYI*/ // White chat bubble
    ShipmentCrafter            = 28,   /*NYI*/ // Brown document
    GarrisonTradeskill         = 29,   /*NYI*/ // White chat bubble
    GarrisonRecruitment        = 30,   /*NYI*/ // White chat bubble
    AdventureMap               = 31,   /*NYI*/ // White chat bubble
    GarrisonTalent             = 32,   /*NYI*/ // White chat bubble
    ContributionCollector      = 33,   /*NYI*/ // White chat bubble
    Transmogrify               = 34,   // Purple helm
    AzeriteRespec              = 35,   /*NYI*/ // White chat bubble
    IslandsMission             = 36,   /*NYI*/ // White chat bubble
    UIItemInteraction          = 37,   /*NYI*/ // White chat bubble
    WorldMap                   = 38,   /*NYI*/ // White chat bubble
    Soulbind                   = 39,   /*NYI*/ // White chat bubble
    ChromieTime                = 40,   /*NYI*/ // White chat bubble
    CovenantPreview            = 41,   /*NYI*/ // White chat bubble
    RuneforgeLegendaryCrafting = 42,   /*NYI*/ // White chat bubble
    NewPlayerGuide             = 43,   /*NYI*/ // White chat bubble
    RuneforgeLegendaryUpgrade  = 44,   /*NYI*/ // White chat bubble
    CovenantRenown             = 45,   /*NYI*/ // White chat bubble
    Count
};

enum class PlayerInteractionType : uint32
{
    None                   = 0,
    TradePartner           = 1,
    Item                   = 2,
    Gossip                 = 3,
    QuestGiver             = 4,
    Merchant               = 5,
    TaxiNode               = 6,
    Trainer                = 7,
    Banker                 = 8,
    AlliedRaceDetailsGiver = 9,
    GuildBanker             = 10,
    Registrar               = 11,
    Vendor                  = 12,
    PetitionVendor          = 13,
    TabardVendor            = 14,
    TalentMaster            = 15,
    SpecializationMaster    = 16,
    MailInfo                = 17,
    SpiritHealer            = 18,
    AreaSpiritHealer        = 19,
    Binder                  = 20,
    Auctioneer              = 21,
    StableMaster            = 22,
    BattleMaster            = 23,
    Transmogrifier          = 24,
    LFGDungeon              = 25,
    VoidStorageBanker       = 26,
    BlackMarketAuctioneer   = 27,
    AdventureMap            = 28,
    WorldMap                = 29,
    GarrArchitect           = 30,
    GarrTradeskill          = 31,
    GarrMission             = 32,
    ShipmentCrafter         = 33,
    GarrRecruitment         = 34,
    GarrTalent              = 35,
    Trophy                  = 36,
    PlayerChoice            = 37,
    ArtifactForge           = 38,
    ObliterumForge          = 39,
    ScrappingMachine        = 40,
    ContributionCollector   = 41,
    AzeriteRespec           = 42,
    IslandQueue             = 43,
    ItemInteraction         = 44,
    ChromieTime             = 45,
    CovenantPreview         = 46,
    AnimaDiversion          = 47,
    LegendaryCrafting       = 48,
    WeeklyRewards           = 49,
    Soulbind                = 50,
    CovenantSanctum         = 51,
    NewPlayerGuide          = 52,
    ItemUpgrade             = 53,
    AdventureJournal        = 54,
    Renown                  = 55,
    AzeriteForge            = 56,
    PerksProgramVendor      = 57,
    ProfessionsCraftingOrder= 58,
    Professions             = 59,
    ProfessionsCustomerOrder= 60,
    TraitSystem             = 61,
    BarbersChoice           = 62,
    JailersTowerBuffs       = 63,
    MajorFactionRenown      = 64,
};

enum class GossipOptionStatus : uint8
{
    Available       = 0,
    Unavailable     = 1,
    Locked          = 2,
    AlreadyComplete = 3
};

enum class GossipOptionRewardType : uint8
{
    Item        = 0,
    Currency    = 1
};

struct GossipMenuItem
{
    GossipOptionNpc  OptionNpc;
    uint32           ClientOption;
    bool             IsCoded;
    std::string      Message;
    uint32           Sender;
    uint32           Action;
    std::string      BoxMessage;
    uint32           BoxMoney;
    uint32           Language;
    std::function<void(std::string)> _callback = nullptr;
};

// need an ordered container
typedef std::map<uint32, GossipMenuItem*> GossipMenuItemContainer;

struct GossipMenuItemData
{
    uint32 GossipActionMenuId;  // MenuId of the gossip triggered by this action
    uint32 GossipActionPoi;
};

// need an ordered container
typedef std::map<uint32, GossipMenuItemData> GossipMenuItemDataContainer;

struct QuestMenuItem
{
    uint32  QuestId;
    uint8   QuestIcon;
};

typedef std::vector<QuestMenuItem> QuestMenuItemList;

class TC_GAME_API GossipMenu
{
    public:
        GossipMenu();
        ~GossipMenu();

        uint32 AddMenuItem(int32 menuItemId, GossipOptionNpc optionNpc, std::string const& message, uint32 sender, uint32 action, std::string const& boxMessage, uint32 boxMoney, bool coded = false, std::function<void(std::string)> callback = nullptr);
        void AddMenuItem(uint32 menuId, uint32 menuItemId, uint32 sender, uint32 action);

        void SetMenuId(uint32 menu_id) { _menuId = menu_id; }
        uint32 GetMenuId() const { return _menuId; }
        void SetLocale(LocaleConstant locale) { _locale = locale; }
        LocaleConstant GetLocale() const { return _locale; }

        void AddGossipMenuItemData(uint32 menuItemId, uint32 gossipActionMenuId, uint32 gossipActionPoi);

        uint32 GetMenuItemCount() const
        {
            return _menuItems.size();
        }

        bool Empty() const
        {
            return _menuItems.empty();
        }

        GossipMenuItem const* GetItem(uint32 id) const
        {
            GossipMenuItemContainer::const_iterator itr = _menuItems.find(id);
            if (itr != _menuItems.end())
                return itr->second;

            return nullptr;
        }

        GossipMenuItemData const* GetItemData(uint32 indexId) const
        {
            GossipMenuItemDataContainer::const_iterator itr = _menuItemData.find(indexId);
            if (itr != _menuItemData.end())
                return &itr->second;

            return nullptr;
        }

        uint32 GetMenuItemSender(uint32 menuItemId) const;
        uint32 GetMenuItemAction(uint32 menuItemId) const;
        bool IsMenuItemCoded(uint32 menuItemId) const;

        void ClearMenu();

        GossipMenuItemContainer const& GetMenuItems() const
        {
            return _menuItems;
        }

    private:
        GossipMenuItemContainer _menuItems;
        GossipMenuItemDataContainer _menuItemData;
        uint32 _menuId;
        LocaleConstant _locale;
};

class TC_GAME_API QuestMenu
{
    public:
        QuestMenu();
        ~QuestMenu();

        void AddMenuItem(uint32 QuestId, uint8 Icon);
        void ClearMenu();
        uint8 GetMenuItemCount() const{ return uint8(_questMenuItems.size()); }
        bool Empty() const { return _questMenuItems.empty(); }
        bool HasItem(uint32 questId) const;
        QuestMenuItem const& GetItem(uint16 index) const { return _questMenuItems[index]; }

    private:
        QuestMenuItemList _questMenuItems;
};

class InteractionData
{
    public:
        InteractionData() { Reset(); }

        void Reset()
        {
            SourceGuid.Clear();
            TrainerId = 0;
            VendorId = 0;
            PlayerChoiceId = 0;
        }

        ObjectGuid SourceGuid;
        uint32 TrainerId;
        uint32 VendorId;
        uint32 PlayerChoiceId;
};

class TC_GAME_API PlayerMenu
{
    public:
        explicit PlayerMenu(WorldSession* session);
        ~PlayerMenu();

        GossipMenu& GetGossipMenu() { return _gossipMenu; }
        QuestMenu& GetQuestMenu() { return _questMenu; }
        InteractionData& GetInteractionData() { return _interactionData; }

        bool Empty() const { return _gossipMenu.Empty() && _questMenu.Empty(); }

        void ClearMenus();
        uint32 GetGossipOptionSender(uint32 selection) const { return _gossipMenu.GetMenuItemSender(selection); }
        uint32 GetGossipOptionAction(uint32 selection) const { return _gossipMenu.GetMenuItemAction(selection); }
        bool IsGossipOptionCoded(uint32 selection) const { return _gossipMenu.IsMenuItemCoded(selection); }

        void SendGossipMenu(uint32 titleTextId, ObjectGuid objectGUID);
        void SendCloseGossip();
        void SendPointOfInterest(uint32 poiId) const;

        /*********************************************************/
        /***                    QUEST SYSTEM                   ***/
        /*********************************************************/
        void SendQuestGiverStatus(QuestGiverStatus questStatus, ObjectGuid npcGUID) const;

        void SendQuestGiverQuestListMessage(Object* questgiver);

        void SendQuestQueryResponse(Quest const* quest) const;
        void SendQuestGiverQuestDetails(Quest const* quest, ObjectGuid npcGUID, bool autoLaunched, bool displayPopup) const;

        void SendQuestGiverOfferReward(Quest const* quest, ObjectGuid npcGUID, bool autoLaunched) const;
        void SendQuestGiverRequestItems(Quest const* quest, ObjectGuid npcGUID, bool canComplete, bool autoLaunched) const;

    private:
        GossipMenu _gossipMenu;
        QuestMenu  _questMenu;
        WorldSession* _session;
        InteractionData _interactionData;
};
#endif
