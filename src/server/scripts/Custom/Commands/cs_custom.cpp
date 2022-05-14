#include "ScriptMgr.h"
#include "Chat.h"
#include "WorldSession.h"
#include "Player.h"
#include "ChatCommand.h"
#include "GossipDef.h"
#include "ScriptedGossip.h"
#include "HotfixDatabase.h"
#include "DB2Stores.h"
#include "CovenantPackets.h"
#include "QuestPackets.h"
#include "../MagicStone.h"
#include "../CustomInstanceScript.h"
#include "Item.h"

#ifdef WIN32
#include "windows.h"
#endif

using namespace Trinity::ChatCommands;

struct CreateItemPlayerData
{
    bool Reset = true;
    uint32 LastMenuId = 0;

    uint32 EntryID = 0;
    uint32 Class = 0;
    uint32 SubClass = 0;
    uint32 Material = 0;
    std::string Name = "Name";
    std::string Description = "Desc";

    std::string CurrentItem = "";

    uint32 Quality = 0;
    uint32 IconFileDataID = 0;
    uint32 Sheathe = 0;
    uint32 InventoryType = 0;
    int32 StatPercentEditor[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    int8 StatModifierBonusStat[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    uint32 CurrentStatType = 0;
    int32 AllowableRace = -1;
    uint32 ItemLevel = 400;
    uint32 Bonding = 1;

    uint32 ItemAppearanceID = 0;
    uint32 DisplayItemID = 0;
};

static std::unordered_map<ObjectGuid::LowType, CreateItemPlayerData> _createItemPlayerData;

class create_item_player_script : public PlayerScript
{
public:
    create_item_player_script() : PlayerScript("create_item_player_script") { }

    template <class T>
    static std::string GetText(std::string text, T var)
    {
        std::ostringstream ss;
        ss << text << var;
        return ss.str();
    }

    enum Senders
    {
        SenderMenu,
        SenderEditField,
        SenderCreateItem,
    };

    enum Actions
    {
        RawClass = 1,
        RawSubClass,
        RawName,
        RawDescription,
        RawQuality,
        RawEntry,
        NotImplemented,
        RawInventoryType,
        RawIconFileDataID,
        RawSheathe,
        RawStatPercentEditor1,
        RawStatPercentEditor2,
        RawStatPercentEditor3,
        RawStatPercentEditor4,
        RawStatPercentEditor5,
        RawStatPercentEditor6,
        RawStatPercentEditor7,
        RawStatPercentEditor8,
        RawStatPercentEditor9,
        RawStatPercentEditor10,
        RawItemLevel,
        RawItemAppearanceID,
        RawItemID,

        // Class,Subclass
        Consumable,
        Potion,
        Elixir,
        Flask,
        Scroll,
        FoodDrink,
        ItemEnhancement,
        Bandage,
        Other,
        Bag,
        SoulBag,
        HerbBag,
        EnchantingBag,
        EngineeringBag,
        GemBag,
        MiningBag,
        LeatherworkingBag,
        InscriptionBag,
        AxeOnehanded,
        AxeTwohanded,
        Bow,
        Gun,
        MaceOnehanded,
        MaceTwohanded,
        Polearm,
        SwordOnehanded,
        SwordTwohanded,
        Obsolete,
        Staff,
        Exotic,
        Exotic2,
        FistWeapon,
        Miscellaneous,
        Dagger,
        Thrown,
        Spear,
        Crossbow,
        Wand,
        FishingPole,
        Red,
        Blue,
        Yellow,
        Purple,
        Green,
        Orange,
        Meta,
        Simple,
        Prismatic,
        Miscellaneous2,
        Cloth,
        Leather,
        Mail,
        Plate,
        BucklerOBSOLETE,
        Shield,
        Libram,
        Idol,
        Totem,
        Sigil,
        Reagent,
        WandOBSOLETE,
        BoltOBSOLETE,
        Arrow,
        Bullet,
        ThrownOBSOLETE,
        QuiverCanholdarrows,
        AmmoPouchCanholdbullets,
        Quest,
        Key,
        Lockpick,
        Permanent,
        Junk,
        Reagent2,
        Pet,
        Holiday2,
        Other2,
        Mount,
        Warrior,
        Paladin,
        Hunter,
        Rogue,
        Priest,
        DeathKnight,
        Shaman,
        Mage,
        Warlock,
        Druid,

        Poor,
        Common,
        Uncommon,
        Rare,
        Epic,
        Legendary,
        Artifact,
        Heirloom,
        WowToken,

        SheatheOne,
        SheatheTwo,
        SheatheThree,
        SheatheFour,
        SheatheFive,
        SheatheSix,

        InvNonEquipable,
        InvHead,
        InvNeck,
        InvShoulder,
        InvShirt,
        InvChest,
        InvWaist,
        InvLegs,
        InvFeet,
        InvWrists,
        InvHands,
        InvFinger,
        InvTrinket,
        InvWeapon,
        InvShield,
        InvRangedBows,
        InvBack,
        InvTwoHand,
        InvBag,
        InvTabard,
        InvRobe,
        InvMainHand,
        InvOffHand,
        InvHoldableTome,
        InvAmmo,
        InvThrown,
        InvRangedRight,
        InvQuiver,
        InvRelic,

            EditStatType1,
            EditStatType2,
            EditStatType3,
            EditStatType4,
            EditStatType5,
            EditStatType6,
            EditStatType7,
            EditStatType8,
            EditStatType9,
            EditStatType10,

            TYPEMANA,
            TYPEHEALTH,
            TYPEAGILITY,
            TYPESTRENGTH,
            TYPEINTELLECT,
            TYPESPIRIT,
            TYPESTAMINA,
            TYPEDEFENSE_SKILL_RATING,
            TYPEDODGE_RATING,
            TYPEPARRY_RATING,
            TYPEBLOCK_RATING,
            TYPEHIT_MELEE_RATING,
            TYPEHIT_RANGED_RATING,
            TYPEHIT_SPELL_RATING,
            TYPECRIT_MELEE_RATING,
            TYPECRIT_RANGED_RATING,
            TYPECRIT_SPELL_RATING,
            TYPECORRUPTION,
            TYPECORRUPTION_RESISTANCE,
            TYPEMODIFIED_CRAFTING_STAT_1,
            TYPEMODIFIED_CRAFTING_STAT_2,
            TYPECRIT_TAKEN_RANGED_RATING,
            TYPECRIT_TAKEN_SPELL_RATING,
            TYPEHASTE_MELEE_RATING,
            TYPEHASTE_RANGED_RATING,
            TYPEHASTE_SPELL_RATING,
            TYPEHIT_RATING,
            TYPECRIT_RATING,
            TYPEHIT_TAKEN_RATING,
            TYPECRIT_TAKEN_RATING,
            TYPERESILIENCE_RATING,
            TYPEHASTE_RATING,
            TYPEEXPERTISE_RATING,
            TYPEATTACK_POWER,
            TYPERANGED_ATTACK_POWER,
            TYPEVERSATILITY,
            TYPESPELL_HEALING_DONE,
            TYPESPELL_DAMAGE_DONE,
            TYPEMANA_REGENERATION,
            TYPEARMOR_PENETRATION_RATING,
            TYPESPELL_POWER,
            TYPEHEALTH_REGEN,
            TYPESPELL_PENETRATION,
            TYPEBLOCK_VALUE,
            TYPEMASTERY_RATING,
            TYPEEXTRA_ARMOR,
            TYPEFIRE_RESISTANCE,
            TYPEFROST_RESISTANCE,
            TYPEHOLY_RESISTANCE,
            TYPESHADOW_RESISTANCE,
            TYPENATURE_RESISTANCE,
            TYPEARCANE_RESISTANCE,
            TYPEPVP_POWER,
            TYPECR_UNUSED_0,
            TYPECR_UNUSED_1,
            TYPECR_UNUSED_3,
            TYPECR_SPEED,
            TYPECR_LIFESTEAL,
            TYPECR_AVOIDANCE,
            TYPECR_STURDINESS,
            TYPECR_UNUSED_7,
            TYPECR_UNUSED_27,
            TYPECR_UNUSED_9,
            TYPECR_UNUSED_10,
            TYPECR_UNUSED_11,
            TYPECR_UNUSED_12,
            TYPEAGI_STR_INT,
            TYPEAGI_STR,
            TYPEAGI_INT,
            TYPESTR_INT,

            NoBounds,
            BOP,
            BOE,
            BOU,
            BOQ,
            BOQ2,

            Reset,


        // Menus
        EditType = 1,
        MainMenu,
        TypeMenu2,
        TypeMenu3,
        TypeMenu4,
        EditQuality,
        EditSheathe,
        EditInventoryType,
        EditStats,
            EditStatsValues,
            CreateWeapon,
            CreateArmor,
            CreateMisc,

            CreateInventoryTypeWeapon,
            CreateInventoryTypeArmor,
            CreateQuality,
                CreateSheathe,
                CreateBonding,
                EditApperance,
    };

    static bool IsWeaponOrArmor(Player* player)
    {
        auto& data = _createItemPlayerData[player->GetGUID().GetCounter()];
        return data.InventoryType > 0 && data.InventoryType != INVTYPE_BAG;
    }
    static bool IsJunk(Player* player)
    {
        auto& data = _createItemPlayerData[player->GetGUID().GetCounter()];
        return data.Class == 0;
    }
    static bool IsWeapon(Player* player)
    {
        auto& data = _createItemPlayerData[player->GetGUID().GetCounter()];
        switch (data.InventoryType)
        {
            case INVTYPE_WEAPON:
            case INVTYPE_2HWEAPON:
            case INVTYPE_RANGED:
            case INVTYPE_THROWN:
            case INVTYPE_HOLDABLE:
            case INVTYPE_WEAPONMAINHAND:
            case INVTYPE_WEAPONOFFHAND:
            case INVTYPE_RANGEDRIGHT:
                return true;
            default:
                return false;
        }
    }

    void CreateItem(Player* player)
    {
        auto& data = _createItemPlayerData[player->GetGUID().GetCounter()];
        if (data.EntryID > 0)
        {
            // (ID, ClassID, SubclassID, Material, InventoryType, SheatheType, SoundOverrideSubclassID, IconFileDataID, ItemGroupSoundsID, ContentTuningID, ModifiedCraftingReagentItemID)
            auto stmt = HotfixDatabase.GetPreparedStatement(HOTFIX_REP_ITEM);
            stmt->setUInt32(0, data.EntryID); // ID
            stmt->setUInt32(1, data.Class); // ClassID
            stmt->setUInt32(2, data.SubClass); // SubClassID
            stmt->setUInt32(3, data.Material); // Material
            stmt->setUInt32(4, data.InventoryType); // InventoryType
            stmt->setUInt32(5, data.Sheathe); // SheatheType
            stmt->setInt8(6, -1); // SoundOverrideSubclassID
            stmt->setUInt32(7, data.IconFileDataID); // IconFIleDataID
            stmt->setUInt32(8, 0); // ItemGroupSoundsID
            stmt->setUInt32(9, 0); // ContentTuningID
            stmt->setUInt32(10, 0); // ModifiedCraftingReagentItemID
            HotfixDatabase.Query(stmt);

            // (ID, AllowableRace, Description, Display3, Display2, Display1, Display, ExpansionID, DmgVariance, "
            // "LimitCategory, DurationInInventory, QualityModifier, BagFamily, StartQuestID, LanguageID, ItemRange, StatPercentageOfSocket1, "
            // "StatPercentageOfSocket2, StatPercentageOfSocket3, StatPercentageOfSocket4, StatPercentageOfSocket5, StatPercentageOfSocket6, "
            // "StatPercentageOfSocket7, StatPercentageOfSocket8, StatPercentageOfSocket9, StatPercentageOfSocket10, StatPercentEditor1, StatPercentEditor2, "
            // "StatPercentEditor3, StatPercentEditor4, StatPercentEditor5, StatPercentEditor6, StatPercentEditor7, StatPercentEditor8, StatPercentEditor9, "
            // "StatPercentEditor10, Stackable, MaxCount, RequiredAbility, SellPrice, BuyPrice, VendorStackCount, PriceVariance, PriceRandomValue, Flags1, "
            // "Flags2, Flags3, Flags4, FactionRelated, ModifiedCraftingReagentItemID, ContentTuningID, PlayerLevelToItemLevelCurveID, "
            // "ItemNameDescriptionID, RequiredTransmogHoliday, RequiredHoliday, GemProperties, SocketMatchEnchantmentId, TotemCategoryID, InstanceBound, "
            // "ZoneBound1, ZoneBound2, ItemSet, LockID, PageID, ItemDelay, MinFactionID, RequiredSkillRank, RequiredSkill, ItemLevel, AllowableClass, "
            // "ArtifactID, SpellWeight, SpellWeightCategory, SocketType1, SocketType2, SocketType3, SheatheType, Material, PageMaterialID, Bonding, "
            // "DamageDamageType, StatModifierBonusStat1, StatModifierBonusStat2, StatModifierBonusStat3, StatModifierBonusStat4, StatModifierBonusStat5, "
            // "StatModifierBonusStat6, StatModifierBonusStat7, StatModifierBonusStat8, StatModifierBonusStat9, StatModifierBonusStat10, ContainerSlots, "
            // "MinReputation, RequiredPVPMedal, RequiredPVPRank, RequiredLevel, InventoryType, OverallQualityID)
            stmt = HotfixDatabase.GetPreparedStatement(HOTFIX_REP_ITEM_SPARSE);

            // (ID, AllowableRace, Description, Display3, Display2, Display1, Display, ExpansionID, DmgVariance, "
            uint32 index = 0;
            stmt->setUInt32(index++, data.EntryID);      // ID
            stmt->setInt32(index++, data.AllowableRace);// AllowableRace
            stmt->setString(index++, data.Description);  // Description
            stmt->setString(index++, "");                // Display3
            stmt->setString(index++, "");                // Display2
            stmt->setString(index++, "");                // Display1
            stmt->setString(index++, data.Name);         // Display
            stmt->setUInt32(index++, 0);                 // ExpansionID
            stmt->setFloat(index++, 0.0f);               // DmgVariance
            stmt->setUInt32(index++, 0);                 // LimitCategory
            stmt->setUInt32(index++, 0);                 // DurationInInventory
            stmt->setFloat(index++, 0.0f);               // QualityModifier
            stmt->setUInt32(index++, 0);                 // BagFamily
            stmt->setUInt32(index++, 0);                 // StartQuestID
            stmt->setUInt32(index++, 0);                 // LanguageID
            stmt->setFloat(index++, 0);                  // ItemRange
            stmt->setFloat(index++, 0);                  // StatPercentageOfSocket1
            stmt->setFloat(index++, 0.0f);               // StatPercentageOfSocket2
            stmt->setFloat(index++, 0.0f);               // StatPercentageOfSocket3
            stmt->setFloat(index++, 0.0f);               // StatPercentageOfSocket4
            stmt->setFloat(index++, 0.0f);               // StatPercentageOfSocket5
            stmt->setFloat(index++, 0.0f);               // StatPercentageOfSocket6
            stmt->setFloat(index++, 0.0f);               // StatPercentageOfSocket7
            stmt->setFloat(index++, 0.0f);               // StatPercentageOfSocket8
            stmt->setFloat(index++, 0.0f);               // StatPercentageOfSocket9,
            stmt->setFloat(index++, 0.0f);               // StatPercentageOfSocket10,
            stmt->setInt32(index++, data.StatPercentEditor[0]);                  // StatPercentEditor1,
            stmt->setInt32(index++, data.StatPercentEditor[1]);                  // StatPercentEditor2, "
            stmt->setInt32(index++, data.StatPercentEditor[2]);                  // StatPercentEditor3,
            stmt->setInt32(index++, data.StatPercentEditor[3]);                  // StatPercentEditor4,
            stmt->setInt32(index++, data.StatPercentEditor[4]);                  // StatPercentEditor5,
            stmt->setInt32(index++, data.StatPercentEditor[5]);                  // StatPercentEditor6,
            stmt->setInt32(index++, data.StatPercentEditor[6]);                  // StatPercentEditor7,
            stmt->setInt32(index++, data.StatPercentEditor[7]);                  // StatPercentEditor8,
            stmt->setInt32(index++, data.StatPercentEditor[8]);                  // StatPercentEditor9, "
            stmt->setInt32(index++, data.StatPercentEditor[9]);                  // "StatPercentEditor10,
            stmt->setInt32(index++, 0);                  // Stackable,
            stmt->setInt32(index++, 0);                  // MaxCount,
            stmt->setInt32(index++, 0);                  // RequiredAbility,
            stmt->setInt32(index++, 0);                  //  SellPrice,
            stmt->setInt32(index++, 0);                  //  BuyPrice,
            stmt->setInt32(index++, 0);                  //  VendorStackCount,
            stmt->setFloat(index++, 0.0f);                  // PriceVariance,
            stmt->setFloat(index++, 0.0f);                  // PriceRandomValue,
            stmt->setInt32(index++, 0);                  // Flags1, "
            stmt->setInt32(index++, 0);                  // "Flags2,
            stmt->setInt32(index++, 0);                  // Flags3,
            stmt->setInt32(index++, 0);                  // Flags4,
            stmt->setInt32(index++, 0);                  // FactionRelated,
            stmt->setInt32(index++, 0);                  // ModifiedCraftingReagentItemID,
            stmt->setInt32(index++, 0);                  // ContentTuningID,
            stmt->setInt32(index++, 0);                  // PlayerLevelToItemLevelCurveID,
            stmt->setInt32(index++, 0);                  // "ItemNameDescriptionID,
            stmt->setInt32(index++, 0);                  // RequiredTransmogHoliday,
            stmt->setInt32(index++, 0);                  // RequiredHoliday,
            stmt->setInt32(index++, 0);                  // GemProperties,
            stmt->setInt32(index++, 0);                  //  SocketMatchEnchantmentId,
            stmt->setInt32(index++, 0);                  // TotemCategoryID,
            stmt->setInt32(index++, 0);                  // InstanceBound, "
            stmt->setInt32(index++, 0);                  // "ZoneBound1,
            stmt->setInt32(index++, 0);                  // ZoneBound2,
            stmt->setInt32(index++, 0);                  //  ItemSet,
            stmt->setInt32(index++, 0);                  // LockID,
            stmt->setInt32(index++, 0);                  // PageID,
            stmt->setInt32(index++, 0);                  // ItemDelay,
            stmt->setInt32(index++, 0);                  // MinFactionID,
            stmt->setInt32(index++, 0);                  // RequiredSkillRank,
            stmt->setInt32(index++, 0);                  //  RequiredSkill,
            stmt->setInt32(index++, data.ItemLevel);     // ItemLevel,
            stmt->setInt32(index++, -1);                  // AllowableClass, "
            stmt->setInt32(index++, 0);                  // "ArtifactID,
            stmt->setInt32(index++, 0);                  // SpellWeight,
            stmt->setInt32(index++, 0);                  //  SpellWeightCategory,
            stmt->setInt32(index++, 0);                  //  SocketType1,
            stmt->setInt32(index++, 0);                  // SocketType2,
            stmt->setInt32(index++, 0);                  // SocketType3,
            stmt->setInt32(index++, data.Sheathe);                  // SheatheType,
            stmt->setInt32(index++, data.Material);                  // Material,
            stmt->setInt32(index++, 0);                  // PageMaterialID,
            stmt->setInt32(index++, data.Bonding);                  // Bonding, "
            stmt->setInt32(index++, 0);                  // "DamageDamageType,
            stmt->setInt8(index++, data.StatModifierBonusStat[0]);                  //  StatModifierBonusStat1,
            stmt->setInt8(index++, data.StatModifierBonusStat[1]);                  //  StatModifierBonusStat2,
            stmt->setInt8(index++, data.StatModifierBonusStat[2]);                  //  StatModifierBonusStat3,
            stmt->setInt8(index++, data.StatModifierBonusStat[3]);                  //  StatModifierBonusStat4,
            stmt->setInt8(index++, data.StatModifierBonusStat[4]);                  //  StatModifierBonusStat5, "
            stmt->setInt8(index++, data.StatModifierBonusStat[5]);                  // "StatModifierBonusStat6,
            stmt->setInt8(index++, data.StatModifierBonusStat[6]);                  // StatModifierBonusStat7,
            stmt->setInt8(index++, data.StatModifierBonusStat[7]);                  // StatModifierBonusStat8,
            stmt->setInt8(index++, data.StatModifierBonusStat[8]);                  //  StatModifierBonusStat9,
            stmt->setInt8(index++, data.StatModifierBonusStat[9]);                  //  StatModifierBonusStat10,
            stmt->setInt32(index++, 0);                  // ContainerSlots, "
            stmt->setInt32(index++, 0);                  // "MinReputation,
            stmt->setInt32(index++, 0);                  // RequiredPVPMedal,
            stmt->setInt32(index++, 0);                  //  RequiredPVPRank,
            stmt->setInt32(index++, 0);                  // RequiredLevel,
            stmt->setInt32(index++, data.InventoryType);                  //  InventoryType,
            stmt->setInt32(index++, data.Quality);                  //  OverallQualityID)

            HotfixDatabase.Query(stmt);

            bool HasModifiedAppearance = false;

            if (data.DisplayItemID > 0 || data.ItemAppearanceID > 0)
            {
                HasModifiedAppearance = true;

                stmt = HotfixDatabase.GetPreparedStatement(HOTFIX_REP_ITEM_MODIFIED_APPERANCE);

                ItemModifiedAppearanceEntry const* modApp = sDB2Manager.GetItemModifiedAppearance(data.DisplayItemID, 0);

                if (data.DisplayItemID == 0 || modApp == nullptr)
                {
                    stmt->setUInt32(0, data.EntryID);          // ID
                    stmt->setInt32(1, data.EntryID);           // ItemID
                    stmt->setInt32(2, 0);                      // ItemApperanceModifierID
                    stmt->setInt32(3, data.ItemAppearanceID);  // ItemAppearanceID
                    stmt->setInt32(4, 0);                      // OrderIndex
                    stmt->setUInt8(5, 0);                      // TransmogSourceTypeEnum
                }
                else
                {
                    stmt->setUInt32(0, data.EntryID);                    // ID
                    stmt->setInt32(1, data.EntryID);                     // ItemID
                    stmt->setInt32(2, modApp->ItemAppearanceModifierID); // ItemApperanceModifierID
                    stmt->setInt32(3, modApp->ItemAppearanceID);         // ItemAppearanceID
                    stmt->setInt32(4, modApp->OrderIndex);               // OrderIndex
                    stmt->setUInt8(5, modApp->TransmogSourceTypeEnum);   // TransmogSourceTypeEnum
                }

                HotfixDatabase.Query(stmt);
            }

            std::vector<uint32> Hashes;
            Hashes.reserve(HasModifiedAppearance ? 3 : 2);

            Hashes.emplace_back(1344507586);
            Hashes.emplace_back(2442913102);
            if (HasModifiedAppearance)
                Hashes.emplace_back(0xE491AC55);


            // (Id, UniqueId, TableHash, RecordId, Status)
            for (auto itr : Hashes)
            {
                stmt = HotfixDatabase.GetPreparedStatement(HOTFIX_REP_HOTFIX_DATA);
                stmt->setUInt32(0, data.EntryID);
                stmt->setUInt32(1, data.EntryID);
                stmt->setUInt32(2, itr);
                stmt->setUInt32(3, data.EntryID);
                stmt->setUInt8(4, 1);
                HotfixDatabase.Query(stmt);
                sDB2Manager.InsertNewHotfix(itr, data.EntryID);
            }

            player->GetSession()->SendAvailableHotfixes();


            sItemSparseStore.LoadFromDB();
            sItemStore.LoadFromDB();
            sObjectMgr->LoadItemTemplates();

            ShowMenu(player);
            player->AddItem(data.EntryID, 1);
        }

    }

    static void ShowMenu(Player* player)
    {
        ClearGossipMenuFor(player);
        auto& data = _createItemPlayerData[player->GetGUID().GetCounter()];
        data.LastMenuId = Actions::MainMenu;

        auto itemColor = "|cff9d9d9d";

        switch (data.Quality)
        {
            case 1: itemColor = "|cffffffff"; break;
            case 2: itemColor = "|cff1eff00"; break;
            case 3: itemColor = "|cff0070dd"; break;
            case 4: itemColor = "|cffa335ee"; break;
            case 5: itemColor = "|cffff8000"; break;
            case 6: itemColor = "|cffe6cc80"; break;
            case 7: case 8: itemColor = "|cff00ccff"; break;
        }

        AddGossipItemFor(player, GossipOptionIcon::None, GetText("|TInterface/Icons/inv_misc_punchcards_prismatic.blp:30:30:-30:0|tEntry: ", data.EntryID), SenderEditField, RawEntry, "", 0, true);

        AddGossipItemFor(player, GossipOptionIcon::None, GetText(itemColor, data.Name), SenderEditField, RawName, "", 0, true);
        AddGossipItemFor(player, GossipOptionIcon::None, GetText("", data.Description), SenderEditField, RawDescription, "", 0, true);

        if (data.Reset)
        {
            AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/Icons/inv_weapon_glave_01.blp:30:30:-30:0|tCreate Weapon", SenderMenu, CreateWeapon);
            AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/Icons/inv_helmet_22.blp:30:30:-30:0|tCreate Armor", SenderMenu, CreateArmor);
            AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/Icons/inv_misc_gear_08.blp:30:30:-30:0|tCreate Misc", SenderMenu, CreateMisc);
            AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/PaperDoll/UI-Backpack-EmptySlot.blp:30:30:-30:0|tEdit Type", SenderMenu, EditType);
        }
        else
        {
            AddGossipItemFor(player, GossipOptionIcon::None, GetText("|TInterface/Icons/misc_arrowleft.blp:30:30:-30:0|tReset, Current: ", data.CurrentItem), SenderEditField, Reset, "Are you sure you want to reset?", 0, false);


            if (IsWeaponOrArmor(player))
            {
                AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/PaperDoll/inv_misc_desecrated_leatherglove.blp:30:30:-30:0|tEdit Appearance", SenderMenu, EditApperance);
                AddGossipItemFor(player, GossipOptionIcon::None, GetText("|TInterface/Icons/achievement_garrisonfollower_itemlevel650.blp:30:30:-30:0|tItemLevel ", data.ItemLevel), SenderEditField, RawItemLevel, "", 0, true);
                AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/Icons/inv_misc_enchantedscroll.blp:30:30:-30:0|tEdit Stats Types ", SenderMenu, EditStats);
                AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/Icons/spell_holy_devotion.blp:30:30:-30:0|tEdit Stats Values ", SenderMenu, EditStatsValues);
            }
            if (IsWeapon(player))
                AddGossipItemFor(player, GossipOptionIcon::None, GetText("|TInterface/PaperDoll/UI-PaperDoll-Slot-MainHand.blp:30:30:-30:0|tEdit Sheathe ", data.Sheathe), SenderMenu, EditSheathe);
            if (!IsJunk(player))
                AddGossipItemFor(player, GossipOptionIcon::None, GetText("|TInterface/PaperDoll/UI-Backpack-EmptySlot.blp:30:30:-30:0|tEdit InventoryType ", data.InventoryType), SenderMenu, EditInventoryType);


            AddGossipItemFor(player, GossipOptionIcon::None, GetText("|TInterface/Icons/inv_farm_enchantedseed.blp:30:30:-30:0|tEdit Quality ", data.Quality), SenderMenu, EditQuality);
            AddGossipItemFor(player, GossipOptionIcon::None, GetText("|TInterface/Icons/trade_engineering.blp:30:30:-30:0|tIconFileDataID ", data.IconFileDataID), SenderEditField, RawIconFileDataID, "", 0, true);

            AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/Icons/inv_alchemy_endlessflask_04.blp:30:30:-30:0|tCreateItem ", SenderCreateItem, 0, GetText("Are you sure you want to create&replace with entry: ", data.EntryID), 0, false);
        }
        player->PlayerTalkClass->GetGossipMenu().SetMenuId(5050);
        SendGossipMenuFor(player, 1, player->GetGUID());
    }

    void OnGossipSelect(Player* player, uint32 menuId, uint32 sender, uint32 actionId) override
    {
        if (menuId != 5050)
            return;

        ClearGossipMenuFor(player);

        ChatHandler(player).PSendSysMessage("%u sender %u action", sender, actionId);
        auto& data = _createItemPlayerData[player->GetGUID().GetCounter()];

        auto nextActionId = actionId;

        switch (sender)
        {
            case Senders::SenderCreateItem:
            {
                CreateItem(player);
                break;
            }
            case Senders::SenderMenu:
            {
                switch (actionId)
                {
                case Actions::EditApperance:
                    AddGossipItemFor(player, GossipOptionIcon::None, GetText("|TInterface/Icons/inv_axe_01.blp:30:30:-30:0|tRawItemAppearanceID ", data.ItemAppearanceID), SenderEditField, RawItemAppearanceID, "", 0, true);
                    AddGossipItemFor(player, GossipOptionIcon::None, GetText("|TInterface/Icons/inv_axe_02.blp:30:30:-30:0|tCopy another ItemID ", data.DisplayItemID), SenderEditField, RawItemID, "", 0, true);
                    AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/Icons/achievement_bg_returnxflags_def_wsg:15:15:-30:0|tBack", SenderMenu, MainMenu);
                    SendGossipMenuFor(player, 1, player->GetGUID());
                    break;
                case Actions::CreateWeapon:
                    AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/Icons/inv_axe_01.blp:30:30:-30:0|tAxe One handed  ", SenderEditField, AxeOnehanded);
                    AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/Icons/inv_axe_02.blp:30:30:-30:0|tAxe Two handed  ", SenderEditField, AxeTwohanded);
                    AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/Icons/inv_weapon_bow_08.blp:30:30:-30:0|tBow ", SenderEditField, Bow);
                    AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/Icons/inv_weapon_rifle_33.blp:30:30:-30:0|tGun ", SenderEditField, Gun);
                    AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/Icons/inv_mace_01.blp:30:30:-30:0|tMace One handed ", SenderEditField, MaceOnehanded);
                    AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/Icons/inv_mace_02.blp:30:30:-30:0|tMace Two handed ", SenderEditField, MaceTwohanded);
                    AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/Icons/inv_polearm_2h_oribosdungeon_c_01.blp:30:30:-30:0|tPolearm", SenderEditField, Polearm);
                    AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/Icons/inv_sword_01.blp:30:30:-30:0|tSword One handed", SenderEditField, SwordOnehanded);
                    AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/Icons/inv_sword_02.blp:30:30:-30:0|tSword Two handed", SenderEditField, SwordTwohanded);
                    AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/Icons/inv_staff_01.blp:30:30:-30:0|tStaff  ", SenderEditField, Staff);
                    AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/Icons/inv_hand_1h_bwdraid_d_01.blp:30:30:-30:0|tFist Weapon  ", SenderEditField, FistWeapon);
                    AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/Icons/inv_hammer_20.blp:30:30:-30:0|tMiscellaneous", SenderEditField, Miscellaneous);
                    AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/Icons/inv_knife_1h_progenitorraid_d_02.blp:30:30:-30:0|tDagger ", SenderEditField, Dagger);
                    AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/Icons/achievement_bg_returnxflags_def_wsg:15:15:-30:0|tBack", SenderMenu, MainMenu);
                    SendGossipMenuFor(player, 1, player->GetGUID());
                    data.CurrentItem = "Weapon";
                    data.Reset = false;
                    nextActionId = Actions::CreateInventoryTypeWeapon;
                    break;
                case Actions::CreateInventoryTypeWeapon:
                    AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/PaperDoll/UI-PaperDoll-Slot-MainHand.blp:30:30:-30:0|tWeapon", SenderEditField, InvWeapon);
                    AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/PaperDoll/UI-PaperDoll-Slot-SecondaryHand.blp:30:30:-30:0|tShield", SenderEditField, InvShield);
                    AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/PaperDoll/UI-PaperDoll-Slot-MainHand.blp:30:30:-30:0|tTwoHand", SenderEditField, InvTwoHand);
                    AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/PaperDoll/UI-PaperDoll-Slot-MainHand.blp:30:30:-30:0|tMainHand", SenderEditField, InvMainHand);
                    AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/PaperDoll/UI-PaperDoll-Slot-SecondaryHand.blp:30:30:-30:0|tOffHand", SenderEditField, InvOffHand);
                    AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/PaperDoll/UI-PaperDoll-Slot-SecondaryHand.blp:30:30:-30:0|tHoldableTome", SenderEditField, InvHoldableTome);
                    AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/PaperDoll/UI-PaperDoll-Slot-MainHand.blp:30:30:-30:0|tThrown", SenderEditField, InvThrown);
                    AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/PaperDoll/UI-PaperDoll-Slot-Ranged.blp:30:30:-30:0|t Ranged Bows", SenderEditField, InvRangedBows);
                    AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/PaperDoll/UI-PaperDoll-Slot-Ranged.blp:30:30:-30:0|t Ranged Gun", SenderEditField, InvRangedRight);
                    AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/Icons/achievement_bg_returnxflags_def_wsg:15:15:-30:0|tBack", SenderMenu, CreateWeapon);
                    SendGossipMenuFor(player, 1, player->GetGUID());
                    nextActionId = Actions::CreateSheathe;
                    break;
                case Actions::CreateSheathe:
                    AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/Icons/inv_axe_113.blp:30:30:-30:0|tTwo Handed Weapon", SenderEditField, SheatheOne);
                    AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/Icons/inv_staff_2h_oribosdungeon_c_01.blp:30:30:-30:0|tStaff", SenderEditField, SheatheTwo);
                    AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/Icons/inv_sword_122.blp:30:30:-30:0|tOne Handed", SenderEditField, SheatheThree);
                    AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/Icons/inv_shield_04.blp:30:30:-30:0|tShield", SenderEditField, SheatheFour);
                    AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/Icons/inv_offhand_1h_ardenwealdquest_b_01.blp:30:30:-30:0|tEnchanter's Rod", SenderEditField, SheatheFive);
                    AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/Icons/inv_misc_book_07.blp:30:30:-30:0|tOff hand", SenderEditField, SheatheSix);
                    AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/Icons/achievement_bg_returnxflags_def_wsg:15:15:-30:0|tBack", SenderMenu, CreateInventoryTypeWeapon);
                    SendGossipMenuFor(player, 1, player->GetGUID());
                    nextActionId = Actions::CreateQuality;
                    break;
                case Actions::CreateQuality:
                    AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/Icons/inv_misc_note_05.blp:30:30:-30:0|t|cff9d9d9dPoor 0", SenderEditField, Poor);
                    AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/Icons/inv_shirt_white_01.blp:30:30:-30:0|t|cffffffffCommon 1", SenderEditField, Common);
                    AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/Icons/ivn_toadloamount.blp:30:30:-30:0|t|cff1eff00Uncommon 2", SenderEditField, Uncommon);
                    AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/Icons/inv_misc_qirajicrystal_04.blp:30:30:-30:0|t|cff0070ddRare 3", SenderEditField, Rare);
                    AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/Icons/inv_enchant_voidcrystal.blp:30:30:-30:0|t|cffa335eeEpic 4", SenderEditField, Epic);
                    AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/Icons/trade_archaeology_draenei_tome.blp:30:30:-30:0|t|cffff8000Legendary 5", SenderEditField, Legendary);
                    AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/Icons/inv_scroll_11.blp:30:30:-30:0|t|cffe6cc80Artifact 6", SenderEditField, Artifact);
                    AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/Icons/inv_leather_warfrontsalliance_c_01_shoulder.blp:30:30:-30:0|t|cff00ccffHeirloom 7", SenderEditField, Heirloom);
                    AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/Icons/wow_token01.blp:30:30:-30:0|t|cff00ccffWowToken 8", SenderEditField, WowToken);
                    AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/Icons/achievement_bg_returnxflags_def_wsg:15:15:-30:0|tBack", SenderMenu, data.LastMenuId);
                    SendGossipMenuFor(player, 1, player->GetGUID());
                    nextActionId = Actions::CreateBonding;
                    break;
                case Actions::CreateBonding:
                    AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/Icons/inv_misc_note_01.blp:30:30:-30:0|tNo bounds", SenderEditField, NoBounds);
                    AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/Icons/inv_misc_note_02.blp:30:30:-30:0|tBinds when picked up", SenderEditField, BOP);
                    AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/Icons/inv_misc_note_03.blp:30:30:-30:0|tBinds when equipped", SenderEditField, BOE);
                    AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/Icons/inv_misc_note_04.blp:30:30:-30:0|tBinds when used", SenderEditField, BOU);
                    AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/Icons/inv_misc_note_05.blp:30:30:-30:0|tQuest item", SenderEditField, BOQ);
                    AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/Icons/inv_misc_note_06.blp:30:30:-30:0|tQuest Item1", SenderEditField, BOQ2);
                    AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/Icons/achievement_bg_returnxflags_def_wsg:15:15:-30:0|tBack", SenderMenu, data.LastMenuId);
                    SendGossipMenuFor(player, 1, player->GetGUID());
                    nextActionId = Actions::MainMenu;
                    break;
                case Actions::CreateArmor:
                    AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/Icons/inv_chest_cloth_14.blp:30:30:-30:0|tCloth", SenderEditField, Cloth);
                    AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/Icons/inv_chest_leather_14.blp:30:30:-30:0|tLeather", SenderEditField, Leather);
                    AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/Icons/inv_chest_chain_05.blp:30:30:-30:0|tMail", SenderEditField, Mail);
                    AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/Icons/inv_chest_plate03.blp:30:30:-30:0|tPlate", SenderEditField, Plate);
                    AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/Icons/achievement_bg_returnxflags_def_wsg:15:15:-30:0|tBack", SenderMenu, MainMenu);
                    SendGossipMenuFor(player, 1, player->GetGUID());
                    data.CurrentItem = "Armor";
                    data.Reset = false;
                    nextActionId = Actions::CreateInventoryTypeArmor;
                    break;
                case Actions::CreateInventoryTypeArmor:
                    AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/PaperDoll/UI-PaperDoll-Slot-Head.blp:30:30:-30:0|tHead", SenderEditField, InvHead);
                    AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/PaperDoll/UI-PaperDoll-Slot-Neck.blp:30:30:-30:0|tNeck", SenderEditField, InvNeck);
                    AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/PaperDoll/UI-PaperDoll-Slot-Shoulder.blp:30:30:-30:0|tShoulder", SenderEditField, InvShoulder);
                    AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/PaperDoll/UI-PaperDoll-Slot-Shirt.blp:30:30:-30:0|tShirt", SenderEditField, InvShirt);
                    AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/PaperDoll/UI-PaperDoll-Slot-Chest.blp:30:30:-30:0|tChest", SenderEditField, InvChest);
                    AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/PaperDoll/UI-PaperDoll-Slot-Waist.blp:30:30:-30:0|tWaist", SenderEditField, InvWaist);
                    AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/PaperDoll/UI-PaperDoll-Slot-Legs.blp:30:30:-30:0|tLegs", SenderEditField, InvLegs);
                    AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/PaperDoll/UI-PaperDoll-Slot-Feet.blp:30:30:-30:0|tFeet", SenderEditField, InvFeet);
                    AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/PaperDoll/UI-PaperDoll-Slot-Wrists.blp:30:30:-30:0|tWrists", SenderEditField, InvWrists);
                    AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/PaperDoll/UI-PaperDoll-Slot-Hands.blp:30:30:-30:0|tHands", SenderEditField, InvHands);
                    AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/PaperDoll/UI-PaperDoll-Slot-Finger.blp:30:30:-30:0|tFinger", SenderEditField, InvFinger);
                    AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/PaperDoll/UI-PaperDoll-Slot-Trinket.blp:30:30:-30:0|tTrinket", SenderEditField, InvTrinket);
                    AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/PaperDoll/UI-PaperDoll-Slot-Chest.blp:30:30:-30:0|tBack", SenderEditField, InvBack);
                    AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/PaperDoll/UI-PaperDoll-Slot-Bag.blp:30:30:-30:0|tBag", SenderEditField, InvBag);
                    AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/PaperDoll/UI-PaperDoll-Slot-Tabard.blp:30:30:-30:0|tTabard", SenderEditField, InvTabard);
                    AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/Icons/achievement_bg_returnxflags_def_wsg:15:15:-30:0|tBack", SenderMenu, CreateArmor);
                    SendGossipMenuFor(player, 1, player->GetGUID());
                    nextActionId = Actions::CreateQuality;
                    break;
                case Actions::CreateMisc:
                    data.InventoryType = 0;

                    AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/Icons/inv_stone_04.blp:30:30:-30:0|tConsumable", SenderEditField, Consumable);
                    AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/Icons/inv_potion_132.blp:30:30:-30:0|tPotion ", SenderEditField, Potion);
                    AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/Icons/inv_potion_83.blp:30:30:-30:0|tElixir ", SenderEditField, Elixir);
                    AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/Icons/inv_alchemy_90_flask_green.blp:30:30:-30:0|tFlask  ", SenderEditField, Flask);
                    AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/Icons/70_professions_scroll_02.blp:30:30:-30:0|tScroll ", SenderEditField, Scroll);
                    AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/Icons/inv_misc_food_73cinnamonroll.blp:30:30:-30:0|tFood & Drink ", SenderEditField, FoodDrink);
                    AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/Icons/inv_scroll_06.blp:30:30:-30:0|tItem Enhancement", SenderEditField, ItemEnhancement);
                    AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/Icons/inv_misc_bandage_frostweave_heavy.blp:30:30:-30:0|tBandage", SenderEditField, Bandage);
                    AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/Icons/inv_misc_wrench_01.blp:30:30:-30:0|tOther  ", SenderEditField, Other);
                    AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/Icons/achievement_bg_returnxflags_def_wsg:15:15:-30:0|tBack", SenderMenu, MainMenu);
                    nextActionId = Actions::CreateQuality;
                    data.CurrentItem = "Misc";
                    data.Reset = false;
                    SendGossipMenuFor(player, 1, player->GetGUID());
                    break;

                case Actions::EditStatType1:
                case Actions::EditStatType2:
                case Actions::EditStatType3:
                case Actions::EditStatType4:
                case Actions::EditStatType5:
                case Actions::EditStatType6:
                case Actions::EditStatType7:
                case Actions::EditStatType8:
                case Actions::EditStatType9:
                case Actions::EditStatType10:
                {

                    auto i = actionId - EditStatType1;
                    data.CurrentStatType = i;
                    if (data.CurrentStatType > 9)
                        data.CurrentStatType = 9;
                    std::string statType = "none";

                    switch (data.StatModifierBonusStat[i])
                    {
                    case ITEM_MOD_MANA: statType = "None"; break;
                    case ITEM_MOD_HEALTH: statType = "HEALTH"; break;
                    case ITEM_MOD_AGILITY: statType = "AGILITY"; break;
                    case ITEM_MOD_STRENGTH: statType = "STRENGTH"; break;
                    case ITEM_MOD_INTELLECT: statType = "INTELLECT"; break;
                    case ITEM_MOD_SPIRIT: statType = "SPIRIT"; break;
                    case ITEM_MOD_STAMINA: statType = "STAMINA"; break;
                    case ITEM_MOD_DEFENSE_SKILL_RATING: statType = "DEFENSE_SKILL_RATING"; break;
                    case ITEM_MOD_DODGE_RATING: statType = "DODGE_RATING"; break;
                    case ITEM_MOD_PARRY_RATING: statType = "PARRY_RATING"; break;
                    case ITEM_MOD_BLOCK_RATING: statType = "BLOCK_RATING"; break;
                    case ITEM_MOD_HIT_MELEE_RATING: statType = "HIT_MELEE_RATING"; break;
                    case ITEM_MOD_HIT_RANGED_RATING: statType = "HIT_RANGED_RATING"; break;
                    case ITEM_MOD_HIT_SPELL_RATING: statType = "HIT_SPELL_RATING"; break;
                    case ITEM_MOD_CRIT_MELEE_RATING: statType = "CRIT_MELEE_RATING"; break;
                    case ITEM_MOD_CRIT_RANGED_RATING: statType = "CRIT_RANGED_RATING"; break;
                    case ITEM_MOD_CRIT_SPELL_RATING: statType = "CRIT_SPELL_RATING"; break;
                    case ITEM_MOD_CORRUPTION: statType = "CORRUPTION"; break;
                    case ITEM_MOD_CORRUPTION_RESISTANCE: statType = "CORRUPTION_RESISTANCE"; break;
                    case ITEM_MOD_MODIFIED_CRAFTING_STAT_1: statType = "MODIFIED_CRAFTING_STAT_1"; break;
                    case ITEM_MOD_MODIFIED_CRAFTING_STAT_2: statType = "MODIFIED_CRAFTING_STAT_2"; break;
                    case ITEM_MOD_CRIT_TAKEN_RANGED_RATING: statType = "CRIT_TAKEN_RANGED_RATING"; break;
                    case ITEM_MOD_CRIT_TAKEN_SPELL_RATING: statType = "CRIT_TAKEN_SPELL_RATING"; break;
                    case ITEM_MOD_HASTE_MELEE_RATING: statType = "HASTE_MELEE_RATING"; break;
                    case ITEM_MOD_HASTE_RANGED_RATING: statType = "HASTE_RANGED_RATING"; break;
                    case ITEM_MOD_HASTE_SPELL_RATING: statType = "HASTE_SPELL_RATING"; break;
                    case ITEM_MOD_HIT_RATING: statType = "HIT_RATING"; break;
                    case ITEM_MOD_CRIT_RATING: statType = "CRIT_RATING"; break;
                    case ITEM_MOD_HIT_TAKEN_RATING: statType = "HIT_TAKEN_RATING"; break;
                    case ITEM_MOD_CRIT_TAKEN_RATING: statType = "CRIT_TAKEN_RATING"; break;
                    case ITEM_MOD_RESILIENCE_RATING: statType = "RESILIENCE_RATING"; break;
                    case ITEM_MOD_HASTE_RATING: statType = "HASTE_RATING"; break;
                    case ITEM_MOD_EXPERTISE_RATING: statType = "EXPERTISE_RATING"; break;
                    case ITEM_MOD_ATTACK_POWER: statType = "ATTACK_POWER"; break;
                    case ITEM_MOD_RANGED_ATTACK_POWER: statType = "RANGED_ATTACK_POWER"; break;
                    case ITEM_MOD_VERSATILITY: statType = "VERSATILITY"; break;
                    case ITEM_MOD_SPELL_HEALING_DONE: statType = "SPELL_HEALING_DONE"; break;
                    case ITEM_MOD_SPELL_DAMAGE_DONE: statType = "SPELL_DAMAGE_DONE"; break;
                    case ITEM_MOD_MANA_REGENERATION: statType = "MANA_REGENERATION"; break;
                    case ITEM_MOD_ARMOR_PENETRATION_RATING: statType = "ARMOR_PENETRATION_RATING"; break;
                    case ITEM_MOD_SPELL_POWER: statType = "SPELL_POWER"; break;
                    case ITEM_MOD_HEALTH_REGEN: statType = "HEALTH_REGEN"; break;
                    case ITEM_MOD_SPELL_PENETRATION: statType = "SPELL_PENETRATION"; break;
                    case ITEM_MOD_BLOCK_VALUE: statType = "BLOCK_VALUE"; break;
                    case ITEM_MOD_MASTERY_RATING: statType = "MASTERY_RATING"; break;
                    case ITEM_MOD_EXTRA_ARMOR: statType = "EXTRA_ARMOR"; break;
                    case ITEM_MOD_FIRE_RESISTANCE: statType = "FIRE_RESISTANCE"; break;
                    case ITEM_MOD_FROST_RESISTANCE: statType = "FROST_RESISTANCE"; break;
                    case ITEM_MOD_HOLY_RESISTANCE: statType = "HOLY_RESISTANCE"; break;
                    case ITEM_MOD_SHADOW_RESISTANCE: statType = "SHADOW_RESISTANCE"; break;
                    case ITEM_MOD_NATURE_RESISTANCE: statType = "NATURE_RESISTANCE"; break;
                    case ITEM_MOD_ARCANE_RESISTANCE: statType = "ARCANE_RESISTANCE"; break;
                    case ITEM_MOD_PVP_POWER: statType = "PVP_POWER"; break;
                    case ITEM_MOD_CR_UNUSED_0: statType = "CR_UNUSED_0"; break;
                    case ITEM_MOD_CR_UNUSED_1: statType = "CR_UNUSED_1"; break;
                    case ITEM_MOD_CR_UNUSED_3: statType = "CR_UNUSED_3"; break;
                    case ITEM_MOD_CR_SPEED: statType = "CR_SPEED"; break;
                    case ITEM_MOD_CR_LIFESTEAL: statType = "CR_LIFESTEAL"; break;
                    case ITEM_MOD_CR_AVOIDANCE: statType = "CR_AVOIDANCE"; break;
                    case ITEM_MOD_CR_STURDINESS: statType = "CR_STURDINESS"; break;
                    case ITEM_MOD_CR_UNUSED_7: statType = "CR_UNUSED_7"; break;
                    case ITEM_MOD_CR_UNUSED_27: statType = "CR_UNUSED_27"; break;
                    case ITEM_MOD_CR_UNUSED_9: statType = "CR_UNUSED_9"; break;
                    case ITEM_MOD_CR_UNUSED_10: statType = "CR_UNUSED_10"; break;
                    case ITEM_MOD_CR_UNUSED_11: statType = "CR_UNUSED_11"; break;
                    case ITEM_MOD_CR_UNUSED_12: statType = "CR_UNUSED_12"; break;
                    case ITEM_MOD_AGI_STR_INT: statType = "AGI_STR_INT"; break;
                    case ITEM_MOD_AGI_STR: statType = "AGI_STR"; break;
                    case ITEM_MOD_AGI_INT: statType = "AGI_INT"; break;
                    case ITEM_MOD_STR_INT: statType = "STR_INT"; break;

                    }


                    AddGossipItemFor(player, GossipOptionIcon::None, GetText("Current I: ", i), SenderMenu, EditStatType1 + i);
                    AddGossipItemFor(player, GossipOptionIcon::None, GetText("Current: ", statType), SenderMenu, EditStatType1 + i);
                    AddGossipItemFor(player, GossipOptionIcon::None, GetText("StatPercentEditor: ", data.StatPercentEditor[i]), SenderEditField, RawStatPercentEditor1 + i, "", 0, true);
                    AddGossipItemFor(player, GossipOptionIcon::None, " None = 0,                                    ", SenderEditField, TYPEMANA);
                    AddGossipItemFor(player, GossipOptionIcon::None, " HEALTH = 1,                         ", SenderEditField, TYPEHEALTH);
                    AddGossipItemFor(player, GossipOptionIcon::None, " AGILITY = 3,                        ", SenderEditField, TYPEAGILITY);
                    AddGossipItemFor(player, GossipOptionIcon::None, " STRENGTH = 4,                       ", SenderEditField, TYPESTRENGTH);
                    AddGossipItemFor(player, GossipOptionIcon::None, " INTELLECT = 5,                      ", SenderEditField, TYPEINTELLECT);
                    AddGossipItemFor(player, GossipOptionIcon::None, " SPIRIT = 6,                         ", SenderEditField, TYPESPIRIT);
                    AddGossipItemFor(player, GossipOptionIcon::None, " STAMINA = 7,                        ", SenderEditField, TYPESTAMINA);
                    AddGossipItemFor(player, GossipOptionIcon::None, " DEFENSE_SKILL_RATING = 12,          ", SenderEditField, TYPEDEFENSE_SKILL_RATING);
                    AddGossipItemFor(player, GossipOptionIcon::None, " DODGE_RATING = 13,                  ", SenderEditField, TYPEDODGE_RATING);
                    AddGossipItemFor(player, GossipOptionIcon::None, " PARRY_RATING = 14,                  ", SenderEditField, TYPEPARRY_RATING);
                    AddGossipItemFor(player, GossipOptionIcon::None, " BLOCK_RATING = 15,                  ", SenderEditField, TYPEBLOCK_RATING);
                    AddGossipItemFor(player, GossipOptionIcon::None, " HIT_MELEE_RATING = 16,              ", SenderEditField, TYPEHIT_MELEE_RATING);
                    AddGossipItemFor(player, GossipOptionIcon::None, " HIT_RANGED_RATING = 17,             ", SenderEditField, TYPEHIT_RANGED_RATING);
                    AddGossipItemFor(player, GossipOptionIcon::None, " HIT_SPELL_RATING = 18,              ", SenderEditField, TYPEHIT_SPELL_RATING);
                    AddGossipItemFor(player, GossipOptionIcon::None, " CRIT_MELEE_RATING = 19,             ", SenderEditField, TYPECRIT_MELEE_RATING);
                    AddGossipItemFor(player, GossipOptionIcon::None, " CRIT_RANGED_RATING = 20,            ", SenderEditField, TYPECRIT_RANGED_RATING);
                    AddGossipItemFor(player, GossipOptionIcon::None, " CRIT_SPELL_RATING = 21,             ", SenderEditField, TYPECRIT_SPELL_RATING);
                    AddGossipItemFor(player, GossipOptionIcon::None, " CORRUPTION = 22,                    ", SenderEditField, TYPECORRUPTION);
                    AddGossipItemFor(player, GossipOptionIcon::None, " CORRUPTION_RESISTANCE = 23,         ", SenderEditField, TYPECORRUPTION_RESISTANCE);
                    AddGossipItemFor(player, GossipOptionIcon::None, " MODIFIED_CRAFTING_STAT_1 = 24,      ", SenderEditField, TYPEMODIFIED_CRAFTING_STAT_1);
                    AddGossipItemFor(player, GossipOptionIcon::None, " MODIFIED_CRAFTING_STAT_2 = 25,      ", SenderEditField, TYPEMODIFIED_CRAFTING_STAT_2);
                    AddGossipItemFor(player, GossipOptionIcon::None, " CRIT_TAKEN_RANGED_RATING = 26,      ", SenderEditField, TYPECRIT_TAKEN_RANGED_RATING);
                    AddGossipItemFor(player, GossipOptionIcon::None, " CRIT_TAKEN_SPELL_RATING = 27,       ", SenderEditField, TYPECRIT_TAKEN_SPELL_RATING);
                    AddGossipItemFor(player, GossipOptionIcon::None, " HASTE_MELEE_RATING = 28,            ", SenderEditField, TYPEHASTE_MELEE_RATING);
                    AddGossipItemFor(player, GossipOptionIcon::None, " HASTE_RANGED_RATING = 29,           ", SenderEditField, TYPEHASTE_RANGED_RATING);
                    AddGossipItemFor(player, GossipOptionIcon::None, " HASTE_SPELL_RATING = 30,            ", SenderEditField, TYPEHASTE_SPELL_RATING);
                    AddGossipItemFor(player, GossipOptionIcon::None, " HIT_RATING = 31,                    ", SenderEditField, TYPEHIT_RATING);
                    AddGossipItemFor(player, GossipOptionIcon::None, " CRIT_RATING = 32,                   ", SenderEditField, TYPECRIT_RATING);
                    AddGossipItemFor(player, GossipOptionIcon::None, " HIT_TAKEN_RATING = 33,              ", SenderEditField, TYPEHIT_TAKEN_RATING);
                    AddGossipItemFor(player, GossipOptionIcon::None, " CRIT_TAKEN_RATING = 34,             ", SenderEditField, TYPECRIT_TAKEN_RATING);
                    AddGossipItemFor(player, GossipOptionIcon::None, " RESILIENCE_RATING = 35,             ", SenderEditField, TYPERESILIENCE_RATING);
                    AddGossipItemFor(player, GossipOptionIcon::None, " HASTE_RATING = 36,                  ", SenderEditField, TYPEHASTE_RATING);
                    AddGossipItemFor(player, GossipOptionIcon::None, " EXPERTISE_RATING = 37,              ", SenderEditField, TYPEEXPERTISE_RATING);
                    AddGossipItemFor(player, GossipOptionIcon::None, " ATTACK_POWER = 38,                  ", SenderEditField, TYPEATTACK_POWER);
                    AddGossipItemFor(player, GossipOptionIcon::None, " RANGED_ATTACK_POWER = 39,           ", SenderEditField, TYPERANGED_ATTACK_POWER);
                    AddGossipItemFor(player, GossipOptionIcon::None, " VERSATILITY = 40,                   ", SenderEditField, TYPEVERSATILITY);
                    AddGossipItemFor(player, GossipOptionIcon::None, " SPELL_HEALING_DONE = 41,            ", SenderEditField, TYPESPELL_HEALING_DONE);
                    AddGossipItemFor(player, GossipOptionIcon::None, " SPELL_DAMAGE_DONE = 42,             ", SenderEditField, TYPESPELL_DAMAGE_DONE);
                    AddGossipItemFor(player, GossipOptionIcon::None, " MANA_REGENERATION = 43,             ", SenderEditField, TYPEMANA_REGENERATION);
                    AddGossipItemFor(player, GossipOptionIcon::None, " ARMOR_PENETRATION_RATING = 44,      ", SenderEditField, TYPEARMOR_PENETRATION_RATING);
                    AddGossipItemFor(player, GossipOptionIcon::None, " SPELL_POWER = 45,                   ", SenderEditField, TYPESPELL_POWER);
                    AddGossipItemFor(player, GossipOptionIcon::None, " HEALTH_REGEN = 46,                  ", SenderEditField, TYPEHEALTH_REGEN);
                    AddGossipItemFor(player, GossipOptionIcon::None, " SPELL_PENETRATION = 47,             ", SenderEditField, TYPESPELL_PENETRATION);
                    AddGossipItemFor(player, GossipOptionIcon::None, " BLOCK_VALUE = 48,                   ", SenderEditField, TYPEBLOCK_VALUE);
                    AddGossipItemFor(player, GossipOptionIcon::None, " MASTERY_RATING = 49,                ", SenderEditField, TYPEMASTERY_RATING);
                    AddGossipItemFor(player, GossipOptionIcon::None, " EXTRA_ARMOR = 50,                   ", SenderEditField, TYPEEXTRA_ARMOR);
                    AddGossipItemFor(player, GossipOptionIcon::None, " FIRE_RESISTANCE = 51,               ", SenderEditField, TYPEFIRE_RESISTANCE);
                    AddGossipItemFor(player, GossipOptionIcon::None, " FROST_RESISTANCE = 52,              ", SenderEditField, TYPEFROST_RESISTANCE);
                    AddGossipItemFor(player, GossipOptionIcon::None, " HOLY_RESISTANCE = 53,               ", SenderEditField, TYPEHOLY_RESISTANCE);
                    AddGossipItemFor(player, GossipOptionIcon::None, " SHADOW_RESISTANCE = 54,             ", SenderEditField, TYPESHADOW_RESISTANCE);
                    AddGossipItemFor(player, GossipOptionIcon::None, " NATURE_RESISTANCE = 55,             ", SenderEditField, TYPENATURE_RESISTANCE);
                    AddGossipItemFor(player, GossipOptionIcon::None, " ARCANE_RESISTANCE = 56,             ", SenderEditField, TYPEARCANE_RESISTANCE);
                    AddGossipItemFor(player, GossipOptionIcon::None, " PVP_POWER = 57,                     ", SenderEditField, TYPEPVP_POWER);
                    AddGossipItemFor(player, GossipOptionIcon::None, " CR_UNUSED_0 = 58,                   ", SenderEditField, TYPECR_UNUSED_0);
                    AddGossipItemFor(player, GossipOptionIcon::None, " CR_UNUSED_1 = 59,                   ", SenderEditField, TYPECR_UNUSED_1);
                    AddGossipItemFor(player, GossipOptionIcon::None, " CR_UNUSED_3 = 60,                   ", SenderEditField, TYPECR_UNUSED_3);
                    AddGossipItemFor(player, GossipOptionIcon::None, " CR_SPEED = 61,                      ", SenderEditField, TYPECR_SPEED);
                    AddGossipItemFor(player, GossipOptionIcon::None, " CR_LIFESTEAL = 62,                  ", SenderEditField, TYPECR_LIFESTEAL);
                    AddGossipItemFor(player, GossipOptionIcon::None, " CR_AVOIDANCE = 63,                  ", SenderEditField, TYPECR_AVOIDANCE);
                    AddGossipItemFor(player, GossipOptionIcon::None, " CR_STURDINESS = 64,                 ", SenderEditField, TYPECR_STURDINESS);
                    AddGossipItemFor(player, GossipOptionIcon::None, " CR_UNUSED_7 = 65,                   ", SenderEditField, TYPECR_UNUSED_7);
                    AddGossipItemFor(player, GossipOptionIcon::None, " CR_UNUSED_27 = 66,                  ", SenderEditField, TYPECR_UNUSED_27);
                    AddGossipItemFor(player, GossipOptionIcon::None, " CR_UNUSED_9 = 67,                   ", SenderEditField, TYPECR_UNUSED_9);
                    AddGossipItemFor(player, GossipOptionIcon::None, " CR_UNUSED_10 = 68,                  ", SenderEditField, TYPECR_UNUSED_10);
                    AddGossipItemFor(player, GossipOptionIcon::None, " CR_UNUSED_11 = 69,                  ", SenderEditField, TYPECR_UNUSED_11);
                    AddGossipItemFor(player, GossipOptionIcon::None, " CR_UNUSED_12 = 70,                  ", SenderEditField, TYPECR_UNUSED_12);
                    AddGossipItemFor(player, GossipOptionIcon::None, " AGI_STR_INT = 71,                   ", SenderEditField, TYPEAGI_STR_INT);
                    AddGossipItemFor(player, GossipOptionIcon::None, " AGI_STR = 72,                       ", SenderEditField, TYPEAGI_STR);
                    AddGossipItemFor(player, GossipOptionIcon::None, " AGI_INT = 73,                       ", SenderEditField, TYPEAGI_INT);
                    AddGossipItemFor(player, GossipOptionIcon::None, " STR_INT = 74                        ", SenderEditField, TYPESTR_INT);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Back", SenderMenu, MainMenu);
                    SendGossipMenuFor(player, 1, player->GetGUID());

                    break;
                }
                case Actions::EditStatsValues:
                case Actions::EditStats:
                {
                    std::ostringstream ss;
                    for (int i = 0; i < 10; ++i)
                    {
                        std::string statType = "none";

                        switch (data.StatModifierBonusStat[i])
                        {
                        case ITEM_MOD_MANA: statType = "None"; break;
                        case ITEM_MOD_HEALTH: statType = "HEALTH"; break;
                        case ITEM_MOD_AGILITY: statType = "AGILITY"; break;
                        case ITEM_MOD_STRENGTH: statType = "STRENGTH"; break;
                        case ITEM_MOD_INTELLECT: statType = "INTELLECT"; break;
                        case ITEM_MOD_SPIRIT: statType = "SPIRIT"; break;
                        case ITEM_MOD_STAMINA: statType = "STAMINA"; break;
                        case ITEM_MOD_DEFENSE_SKILL_RATING: statType = "DEFENSE_SKILL_RATING"; break;
                        case ITEM_MOD_DODGE_RATING: statType = "DODGE_RATING"; break;
                        case ITEM_MOD_PARRY_RATING: statType = "PARRY_RATING"; break;
                        case ITEM_MOD_BLOCK_RATING: statType = "BLOCK_RATING"; break;
                        case ITEM_MOD_HIT_MELEE_RATING: statType = "HIT_MELEE_RATING"; break;
                        case ITEM_MOD_HIT_RANGED_RATING: statType = "HIT_RANGED_RATING"; break;
                        case ITEM_MOD_HIT_SPELL_RATING: statType = "HIT_SPELL_RATING"; break;
                        case ITEM_MOD_CRIT_MELEE_RATING: statType = "CRIT_MELEE_RATING"; break;
                        case ITEM_MOD_CRIT_RANGED_RATING: statType = "CRIT_RANGED_RATING"; break;
                        case ITEM_MOD_CRIT_SPELL_RATING: statType = "CRIT_SPELL_RATING"; break;
                        case ITEM_MOD_CORRUPTION: statType = "CORRUPTION"; break;
                        case ITEM_MOD_CORRUPTION_RESISTANCE: statType = "CORRUPTION_RESISTANCE"; break;
                        case ITEM_MOD_MODIFIED_CRAFTING_STAT_1: statType = "MODIFIED_CRAFTING_STAT_1"; break;
                        case ITEM_MOD_MODIFIED_CRAFTING_STAT_2: statType = "MODIFIED_CRAFTING_STAT_2"; break;
                        case ITEM_MOD_CRIT_TAKEN_RANGED_RATING: statType = "CRIT_TAKEN_RANGED_RATING"; break;
                        case ITEM_MOD_CRIT_TAKEN_SPELL_RATING: statType = "CRIT_TAKEN_SPELL_RATING"; break;
                        case ITEM_MOD_HASTE_MELEE_RATING: statType = "HASTE_MELEE_RATING"; break;
                        case ITEM_MOD_HASTE_RANGED_RATING: statType = "HASTE_RANGED_RATING"; break;
                        case ITEM_MOD_HASTE_SPELL_RATING: statType = "HASTE_SPELL_RATING"; break;
                        case ITEM_MOD_HIT_RATING: statType = "HIT_RATING"; break;
                        case ITEM_MOD_CRIT_RATING: statType = "CRIT_RATING"; break;
                        case ITEM_MOD_HIT_TAKEN_RATING: statType = "HIT_TAKEN_RATING"; break;
                        case ITEM_MOD_CRIT_TAKEN_RATING: statType = "CRIT_TAKEN_RATING"; break;
                        case ITEM_MOD_RESILIENCE_RATING: statType = "RESILIENCE_RATING"; break;
                        case ITEM_MOD_HASTE_RATING: statType = "HASTE_RATING"; break;
                        case ITEM_MOD_EXPERTISE_RATING: statType = "EXPERTISE_RATING"; break;
                        case ITEM_MOD_ATTACK_POWER: statType = "ATTACK_POWER"; break;
                        case ITEM_MOD_RANGED_ATTACK_POWER: statType = "RANGED_ATTACK_POWER"; break;
                        case ITEM_MOD_VERSATILITY: statType = "VERSATILITY"; break;
                        case ITEM_MOD_SPELL_HEALING_DONE: statType = "SPELL_HEALING_DONE"; break;
                        case ITEM_MOD_SPELL_DAMAGE_DONE: statType = "SPELL_DAMAGE_DONE"; break;
                        case ITEM_MOD_MANA_REGENERATION: statType = "MANA_REGENERATION"; break;
                        case ITEM_MOD_ARMOR_PENETRATION_RATING: statType = "ARMOR_PENETRATION_RATING"; break;
                        case ITEM_MOD_SPELL_POWER: statType = "SPELL_POWER"; break;
                        case ITEM_MOD_HEALTH_REGEN: statType = "HEALTH_REGEN"; break;
                        case ITEM_MOD_SPELL_PENETRATION: statType = "SPELL_PENETRATION"; break;
                        case ITEM_MOD_BLOCK_VALUE: statType = "BLOCK_VALUE"; break;
                        case ITEM_MOD_MASTERY_RATING: statType = "MASTERY_RATING"; break;
                        case ITEM_MOD_EXTRA_ARMOR: statType = "EXTRA_ARMOR"; break;
                        case ITEM_MOD_FIRE_RESISTANCE: statType = "FIRE_RESISTANCE"; break;
                        case ITEM_MOD_FROST_RESISTANCE: statType = "FROST_RESISTANCE"; break;
                        case ITEM_MOD_HOLY_RESISTANCE: statType = "HOLY_RESISTANCE"; break;
                        case ITEM_MOD_SHADOW_RESISTANCE: statType = "SHADOW_RESISTANCE"; break;
                        case ITEM_MOD_NATURE_RESISTANCE: statType = "NATURE_RESISTANCE"; break;
                        case ITEM_MOD_ARCANE_RESISTANCE: statType = "ARCANE_RESISTANCE"; break;
                        case ITEM_MOD_PVP_POWER: statType = "PVP_POWER"; break;
                        case ITEM_MOD_CR_UNUSED_0: statType = "CR_UNUSED_0"; break;
                        case ITEM_MOD_CR_UNUSED_1: statType = "CR_UNUSED_1"; break;
                        case ITEM_MOD_CR_UNUSED_3: statType = "CR_UNUSED_3"; break;
                        case ITEM_MOD_CR_SPEED: statType = "CR_SPEED"; break;
                        case ITEM_MOD_CR_LIFESTEAL: statType = "CR_LIFESTEAL"; break;
                        case ITEM_MOD_CR_AVOIDANCE: statType = "CR_AVOIDANCE"; break;
                        case ITEM_MOD_CR_STURDINESS: statType = "CR_STURDINESS"; break;
                        case ITEM_MOD_CR_UNUSED_7: statType = "CR_UNUSED_7"; break;
                        case ITEM_MOD_CR_UNUSED_27: statType = "CR_UNUSED_27"; break;
                        case ITEM_MOD_CR_UNUSED_9: statType = "CR_UNUSED_9"; break;
                        case ITEM_MOD_CR_UNUSED_10: statType = "CR_UNUSED_10"; break;
                        case ITEM_MOD_CR_UNUSED_11: statType = "CR_UNUSED_11"; break;
                        case ITEM_MOD_CR_UNUSED_12: statType = "CR_UNUSED_12"; break;
                        case ITEM_MOD_AGI_STR_INT: statType = "AGI_STR_INT"; break;
                        case ITEM_MOD_AGI_STR: statType = "AGI_STR"; break;
                        case ITEM_MOD_AGI_INT: statType = "AGI_INT"; break;
                        case ITEM_MOD_STR_INT: statType = "STR_INT"; break;

                        }

                        if (actionId != EditStatsValues)
                            ss << "Edit ";
                        ss << "Stat [" << i << "]: " << statType << " : StatPercentEditor: " << data.StatPercentEditor[i];
                        if (actionId == EditStatsValues)
                            AddGossipItemFor(player, GossipOptionIcon::None, ss.str(), SenderEditField, RawStatPercentEditor1 + i, "", 0, true);
                        else
                            AddGossipItemFor(player, GossipOptionIcon::None, ss.str(), SenderMenu, EditStatType1 + i);
                        ss.str("");
                        ss.clear();
                    }
                    AddGossipItemFor(player, GossipOptionIcon::None, "Back", SenderMenu, MainMenu);
                    SendGossipMenuFor(player, 1, player->GetGUID());
                    break;
                }
                case Actions::EditInventoryType:

                    AddGossipItemFor(player, GossipOptionIcon::None, GetText("InventoryType: ", data.InventoryType), SenderEditField, RawInventoryType, "", 0, true);

                    if (IsWeapon(player))
                    {
                        AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/PaperDoll/UI-PaperDoll-Slot-MainHand.blp:30:30:-30:0|tWeapon", SenderEditField, InvWeapon);
                        AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/PaperDoll/UI-PaperDoll-Slot-SecondaryHand.blp:30:30:-30:0|tShield", SenderEditField, InvShield);
                        AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/PaperDoll/UI-PaperDoll-Slot-MainHand.blp:30:30:-30:0|tTwoHand", SenderEditField, InvTwoHand);
                        AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/PaperDoll/UI-PaperDoll-Slot-MainHand.blp:30:30:-30:0|tMainHand", SenderEditField, InvMainHand);
                        AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/PaperDoll/UI-PaperDoll-Slot-SecondaryHand.blp:30:30:-30:0|tOffHand", SenderEditField, InvOffHand);
                        AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/PaperDoll/UI-PaperDoll-Slot-SecondaryHand.blp:30:30:-30:0|tHoldableTome", SenderEditField, InvHoldableTome);
                        AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/PaperDoll/UI-PaperDoll-Slot-MainHand.blp:30:30:-30:0|tThrown", SenderEditField, InvThrown);
                        AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/PaperDoll/UI-PaperDoll-Slot-Ranged.blp:30:30:-30:0|t Ranged Bows", SenderEditField, InvRangedBows);
                        AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/PaperDoll/UI-PaperDoll-Slot-Ranged.blp:30:30:-30:0|t Ranged Gun", SenderEditField, InvRangedRight);
                        AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/Icons/achievement_bg_returnxflags_def_wsg:15:15:-30:0|tBack", SenderMenu, CreateWeapon);
                    }
                    else
                    {
                        AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/PaperDoll/UI-PaperDoll-Slot-Head.blp:30:30:-30:0|tHead", SenderEditField, InvHead);
                        AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/PaperDoll/UI-PaperDoll-Slot-Neck.blp:30:30:-30:0|tNeck", SenderEditField, InvNeck);
                        AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/PaperDoll/UI-PaperDoll-Slot-Shoulder.blp:30:30:-30:0|tShoulder", SenderEditField, InvShoulder);
                        AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/PaperDoll/UI-PaperDoll-Slot-Shirt.blp:30:30:-30:0|tShirt", SenderEditField, InvShirt);
                        AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/PaperDoll/UI-PaperDoll-Slot-Chest.blp:30:30:-30:0|tChest", SenderEditField, InvChest);
                        AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/PaperDoll/UI-PaperDoll-Slot-Waist.blp:30:30:-30:0|tWaist", SenderEditField, InvWaist);
                        AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/PaperDoll/UI-PaperDoll-Slot-Legs.blp:30:30:-30:0|tLegs", SenderEditField, InvLegs);
                        AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/PaperDoll/UI-PaperDoll-Slot-Feet.blp:30:30:-30:0|tFeet", SenderEditField, InvFeet);
                        AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/PaperDoll/UI-PaperDoll-Slot-Wrists.blp:30:30:-30:0|tWrists", SenderEditField, InvWrists);
                        AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/PaperDoll/UI-PaperDoll-Slot-Hands.blp:30:30:-30:0|tHands", SenderEditField, InvHands);
                        AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/PaperDoll/UI-PaperDoll-Slot-Finger.blp:30:30:-30:0|tFinger", SenderEditField, InvFinger);
                        AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/PaperDoll/UI-PaperDoll-Slot-Trinket.blp:30:30:-30:0|tTrinket", SenderEditField, InvTrinket);
                        AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/PaperDoll/UI-PaperDoll-Slot-Chest.blp:30:30:-30:0|tBack", SenderEditField, InvBack);
                        AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/PaperDoll/UI-PaperDoll-Slot-Bag.blp:30:30:-30:0|tBag", SenderEditField, InvBag);
                        AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/PaperDoll/UI-PaperDoll-Slot-Tabard.blp:30:30:-30:0|tTabard", SenderEditField, InvTabard);
                        AddGossipItemFor(player, GossipOptionIcon::None, "|TInterface/Icons/achievement_bg_returnxflags_def_wsg:15:15:-30:0|tBack", SenderMenu, CreateArmor);
                    }

                    // AddGossipItemFor(player, GossipOptionIcon::None, "0 NonEquipable,  ", SenderEditField, InvNonEquipable);
                    // AddGossipItemFor(player, GossipOptionIcon::None, "1 Head,          ", SenderEditField, InvHead);
                    // AddGossipItemFor(player, GossipOptionIcon::None, "2 Neck,          ", SenderEditField, InvNeck);
                    // AddGossipItemFor(player, GossipOptionIcon::None, "3 Shoulder,      ", SenderEditField, InvShoulder);
                    // AddGossipItemFor(player, GossipOptionIcon::None, "4 Shirt,         ", SenderEditField, InvShirt);
                    // AddGossipItemFor(player, GossipOptionIcon::None, "5 Chest,         ", SenderEditField, InvChest);
                    // AddGossipItemFor(player, GossipOptionIcon::None, "6 Waist,         ", SenderEditField, InvWaist);
                    // AddGossipItemFor(player, GossipOptionIcon::None, "7 Legs,          ", SenderEditField, InvLegs);
                    // AddGossipItemFor(player, GossipOptionIcon::None, "8 Feet,          ", SenderEditField, InvFeet);
                    // AddGossipItemFor(player, GossipOptionIcon::None, "9 Wrists,        ", SenderEditField, InvWrists);
                    // AddGossipItemFor(player, GossipOptionIcon::None, "10 Hands,         ", SenderEditField, InvHands);
                    // AddGossipItemFor(player, GossipOptionIcon::None, "11 Finger,        ", SenderEditField, InvFinger);
                    // AddGossipItemFor(player, GossipOptionIcon::None, "12 Trinket,       ", SenderEditField, InvTrinket);
                    // AddGossipItemFor(player, GossipOptionIcon::None, "13 Weapon,        ", SenderEditField, InvWeapon);
                    // AddGossipItemFor(player, GossipOptionIcon::None, "14 Shield,        ", SenderEditField, InvShield);
                    // AddGossipItemFor(player, GossipOptionIcon::None, "15 RangedBows,    ", SenderEditField, InvRangedBows);
                    // AddGossipItemFor(player, GossipOptionIcon::None, "16 Back,          ", SenderEditField, InvBack);
                    // AddGossipItemFor(player, GossipOptionIcon::None, "17 TwoHand,       ", SenderEditField, InvTwoHand);
                    // AddGossipItemFor(player, GossipOptionIcon::None, "18 Bag,           ", SenderEditField, InvBag);
                    // AddGossipItemFor(player, GossipOptionIcon::None, "19 Tabard,        ", SenderEditField, InvTabard);
                    // AddGossipItemFor(player, GossipOptionIcon::None, "20 Robe,          ", SenderEditField, InvRobe);
                    // AddGossipItemFor(player, GossipOptionIcon::None, "21 MainHand,      ", SenderEditField, InvMainHand);
                    // AddGossipItemFor(player, GossipOptionIcon::None, "22 OffHand,       ", SenderEditField, InvOffHand);
                    // AddGossipItemFor(player, GossipOptionIcon::None, "23 HoldableTome,  ", SenderEditField, InvHoldableTome);
                    // AddGossipItemFor(player, GossipOptionIcon::None, "24 Ammo,          ", SenderEditField, InvAmmo);
                    // AddGossipItemFor(player, GossipOptionIcon::None, "25 Thrown,        ", SenderEditField, InvThrown);
                    // AddGossipItemFor(player, GossipOptionIcon::None, "26 RangedRight,   ", SenderEditField, InvRangedRight);
                    // AddGossipItemFor(player, GossipOptionIcon::None, "27 Quiver,        ", SenderEditField, InvQuiver);
                    // AddGossipItemFor(player, GossipOptionIcon::None, "28 Relic,         ", SenderEditField, InvRelic);

                    AddGossipItemFor(player, GossipOptionIcon::None, "Back", SenderMenu, MainMenu);
                    SendGossipMenuFor(player, 1, player->GetGUID());
                    break;
                case Actions::EditSheathe:
                    AddGossipItemFor(player, GossipOptionIcon::None, GetText("Sheathe: ", data.Sheathe), SenderEditField, RawSheathe, "", 0, true);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Two Handed Weapon", SenderEditField, SheatheOne);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Staff", SenderEditField, SheatheTwo);
                    AddGossipItemFor(player, GossipOptionIcon::None, "One Handed", SenderEditField, SheatheThree);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Shield", SenderEditField, SheatheFour);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Enchanter's Rod", SenderEditField, SheatheFive);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Off hand", SenderEditField, SheatheSix);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Back", SenderMenu, MainMenu);
                    SendGossipMenuFor(player, 1, player->GetGUID());
                    break;
                case Actions::MainMenu:
                    ShowMenu(player);
                    break;
                case Actions::EditType:
                    data.Reset = false;
                    AddGossipItemFor(player, GossipOptionIcon::None, GetText("Class: ", data.Class), SenderEditField, RawClass, "", 0, true);
                    AddGossipItemFor(player, GossipOptionIcon::None, GetText("SubClass: ", data.SubClass), SenderEditField, RawSubClass, "", 0, true);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Consumable [Usability in combat is decided by the spell assigned]", SenderEditField, Consumable);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Potion ", SenderEditField, Potion);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Elixir ", SenderEditField, Elixir);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Flask  ", SenderEditField, Flask);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Scroll ", SenderEditField, Scroll);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Food & Drink ", SenderEditField, FoodDrink);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Item Enhancement", SenderEditField, ItemEnhancement);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Bandage", SenderEditField, Bandage);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Other  ", SenderEditField, Other);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Bag ", SenderEditField, Bag);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Soul Bag  ", SenderEditField, SoulBag);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Herb Bag  ", SenderEditField, HerbBag);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Enchanting Bag  ", SenderEditField, EnchantingBag);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Engineering Bag ", SenderEditField, EngineeringBag);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Gem Bag", SenderEditField, GemBag);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Mining Bag", SenderEditField, MiningBag);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Leatherworking Bag ", SenderEditField, LeatherworkingBag);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Inscription Bag ", SenderEditField, InscriptionBag);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Axe One handed  ", SenderEditField, AxeOnehanded);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Axe Two handed  ", SenderEditField, AxeTwohanded);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Bow ", SenderEditField, Bow);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Gun ", SenderEditField, Gun);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Mace One handed ", SenderEditField, MaceOnehanded);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Mace Two handed ", SenderEditField, MaceTwohanded);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Polearm", SenderEditField, Polearm);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Sword One handed", SenderEditField, SwordOnehanded);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Sword Two handed", SenderEditField, SwordTwohanded);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Obsolete  ", SenderEditField, Obsolete);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Back", SenderMenu, MainMenu);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Next", SenderMenu, TypeMenu2);
                    SendGossipMenuFor(player, 1, player->GetGUID());
                    break;
                case Actions::TypeMenu2:

                    AddGossipItemFor(player, GossipOptionIcon::None, "Staff  ", SenderEditField, Staff);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Exotic ", SenderEditField, Exotic);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Exotic ", SenderEditField, Exotic2);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Fist Weapon  ", SenderEditField, FistWeapon);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Miscellaneous (Blacksmith Hammer, Mining Pick, etc.)", SenderEditField, Miscellaneous);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Dagger ", SenderEditField, Dagger);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Thrown ", SenderEditField, Thrown);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Spear  ", SenderEditField, Spear);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Crossbow  ", SenderEditField, Crossbow);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Wand", SenderEditField, Wand);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Fishing Pole ", SenderEditField, FishingPole);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Back", SenderMenu, EditType);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Next", SenderMenu, TypeMenu3);
                    SendGossipMenuFor(player, 1, player->GetGUID());
                    break;
                case Actions::TypeMenu3:

                    AddGossipItemFor(player, GossipOptionIcon::None, "Red ", SenderEditField, Red);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Blue", SenderEditField, Blue);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Yellow ", SenderEditField, Yellow);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Purple ", SenderEditField, Purple);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Green  ", SenderEditField, Green);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Orange ", SenderEditField, Orange);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Meta", SenderEditField, Meta);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Simple ", SenderEditField, Simple);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Prismatic ", SenderEditField, Prismatic);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Miscellaneous", SenderEditField, Miscellaneous2);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Cloth  ", SenderEditField, Cloth);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Leather", SenderEditField, Leather);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Mail", SenderEditField, Mail);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Plate  ", SenderEditField, Plate);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Buckler(OBSOLETE)  ", SenderEditField, BucklerOBSOLETE);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Shield ", SenderEditField, Shield);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Libram ", SenderEditField, Libram);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Idol", SenderEditField, Idol);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Totem  ", SenderEditField, Totem);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Sigil  ", SenderEditField, Sigil);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Reagent", SenderEditField, Reagent);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Wand(OBSOLETE)  ", SenderEditField, WandOBSOLETE);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Bolt(OBSOLETE)  ", SenderEditField, BoltOBSOLETE);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Arrow  ", SenderEditField, Arrow);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Bullet ", SenderEditField, Bullet);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Thrown(OBSOLETE)", SenderEditField, ThrownOBSOLETE);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Quiver Can hold arrows", SenderEditField, QuiverCanholdarrows);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Ammo Pouch Can hold bullets ", SenderEditField, AmmoPouchCanholdbullets);

                    AddGossipItemFor(player, GossipOptionIcon::None, "Back", SenderMenu, TypeMenu2);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Next", SenderMenu, TypeMenu4);
                    SendGossipMenuFor(player, 1, player->GetGUID());
                    break;
                case Actions::TypeMenu4:

                    AddGossipItemFor(player, GossipOptionIcon::None, "Quest  ", SenderEditField, Quest);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Key ", SenderEditField, Key);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Lockpick  ", SenderEditField, Lockpick);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Permanent ", SenderEditField, Permanent);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Junk", SenderEditField, Junk);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Reagent", SenderEditField, Reagent2);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Pet ", SenderEditField, Pet);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Holiday", SenderEditField, Holiday2);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Other  ", SenderEditField, Other2);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Mount  ", SenderEditField, Mount);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Warrior", SenderEditField, Warrior);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Paladin", SenderEditField, Paladin);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Hunter ", SenderEditField, Hunter);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Rogue  ", SenderEditField, Rogue);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Priest ", SenderEditField, Priest);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Death Knight ", SenderEditField, DeathKnight);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Shaman ", SenderEditField, Shaman);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Mage", SenderEditField, Mage);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Warlock", SenderEditField, Warlock);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Druid  ", SenderEditField, Druid);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Back", SenderMenu, TypeMenu3);
                    SendGossipMenuFor(player, 1, player->GetGUID());
                    break;
                case Actions::EditQuality:
                    AddGossipItemFor(player, GossipOptionIcon::None, GetText("Current: ", data.Quality), SenderEditField, RawQuality);
                    AddGossipItemFor(player, GossipOptionIcon::None, "|cff9d9d9dPoor 0", SenderEditField, Poor);
                    AddGossipItemFor(player, GossipOptionIcon::None, "|cffffffffCommon 1", SenderEditField, Common);
                    AddGossipItemFor(player, GossipOptionIcon::None, "|cff1eff00Uncommon 2", SenderEditField, Uncommon);
                    AddGossipItemFor(player, GossipOptionIcon::None, "|cff0070ddRare  3", SenderEditField, Rare);
                    AddGossipItemFor(player, GossipOptionIcon::None, "|cffa335eeEpic 4", SenderEditField, Epic);
                    AddGossipItemFor(player, GossipOptionIcon::None, "|cffff8000Legendary 5", SenderEditField, Legendary);
                    AddGossipItemFor(player, GossipOptionIcon::None, "|cffe6cc80Artifact 6", SenderEditField, Artifact);
                    AddGossipItemFor(player, GossipOptionIcon::None, "|cff00ccffHeirloom 7", SenderEditField, Heirloom);
                    AddGossipItemFor(player, GossipOptionIcon::None, "|cff00ccffWowToken 8", SenderEditField, WowToken);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Back", SenderMenu, MainMenu);
                    SendGossipMenuFor(player, 1, player->GetGUID());
                    break;
                }

                data.LastMenuId = nextActionId;
                break;
            }
            case Senders::SenderEditField:
                switch (actionId)
                {
                    case Reset: data = CreateItemPlayerData(); ShowMenu(player);  break;

                        // Bonding
                    case NoBounds:    data.Bonding = 0;      break;
                    case     BOP:     data.Bonding = 1;      break;
                    case     BOE:     data.Bonding = 2;      break;
                    case     BOU:     data.Bonding = 3;      break;
                    case     BOQ:     data.Bonding = 4;      break;
                    case     BOQ2:    data.Bonding = 5;      break;

                    case TYPEMANA                               : data.StatModifierBonusStat[data.CurrentStatType] = ITEM_MOD_MANA                          ; break;
                    case TYPEHEALTH                             : data.StatModifierBonusStat[data.CurrentStatType] = ITEM_MOD_HEALTH                        ; break;
                    case TYPEAGILITY                            : data.StatModifierBonusStat[data.CurrentStatType] = ITEM_MOD_AGILITY                       ; break;
                    case TYPESTRENGTH                           : data.StatModifierBonusStat[data.CurrentStatType] = ITEM_MOD_STRENGTH                      ; break;
                    case TYPEINTELLECT                          : data.StatModifierBonusStat[data.CurrentStatType] = ITEM_MOD_INTELLECT                     ; break;
                    case TYPESPIRIT                             : data.StatModifierBonusStat[data.CurrentStatType] = ITEM_MOD_SPIRIT                        ; break;
                    case TYPESTAMINA                            : data.StatModifierBonusStat[data.CurrentStatType] = ITEM_MOD_STAMINA                       ; break;
                    case TYPEDEFENSE_SKILL_RATING               : data.StatModifierBonusStat[data.CurrentStatType] = ITEM_MOD_DEFENSE_SKILL_RATING          ; break;
                    case TYPEDODGE_RATING                       : data.StatModifierBonusStat[data.CurrentStatType] = ITEM_MOD_DODGE_RATING                  ; break;
                    case TYPEPARRY_RATING                       : data.StatModifierBonusStat[data.CurrentStatType] = ITEM_MOD_PARRY_RATING                  ; break;
                    case TYPEBLOCK_RATING                       : data.StatModifierBonusStat[data.CurrentStatType] = ITEM_MOD_BLOCK_RATING                  ; break;
                    case TYPEHIT_MELEE_RATING                   : data.StatModifierBonusStat[data.CurrentStatType] = ITEM_MOD_HIT_MELEE_RATING              ; break;
                    case TYPEHIT_RANGED_RATING                  : data.StatModifierBonusStat[data.CurrentStatType] = ITEM_MOD_HIT_RANGED_RATING             ; break;
                    case TYPEHIT_SPELL_RATING                   : data.StatModifierBonusStat[data.CurrentStatType] = ITEM_MOD_HIT_SPELL_RATING              ; break;
                    case TYPECRIT_MELEE_RATING                  : data.StatModifierBonusStat[data.CurrentStatType] = ITEM_MOD_CRIT_MELEE_RATING             ; break;
                    case TYPECRIT_RANGED_RATING                 : data.StatModifierBonusStat[data.CurrentStatType] = ITEM_MOD_CRIT_RANGED_RATING            ; break;
                    case TYPECRIT_SPELL_RATING                  : data.StatModifierBonusStat[data.CurrentStatType] = ITEM_MOD_CRIT_SPELL_RATING             ; break;
                    case TYPECORRUPTION                         : data.StatModifierBonusStat[data.CurrentStatType] = ITEM_MOD_CORRUPTION                    ; break;
                    case TYPECORRUPTION_RESISTANCE              : data.StatModifierBonusStat[data.CurrentStatType] = ITEM_MOD_CORRUPTION_RESISTANCE         ; break;
                    case TYPEMODIFIED_CRAFTING_STAT_1           : data.StatModifierBonusStat[data.CurrentStatType] = ITEM_MOD_MODIFIED_CRAFTING_STAT_1      ; break;
                    case TYPEMODIFIED_CRAFTING_STAT_2           : data.StatModifierBonusStat[data.CurrentStatType] = ITEM_MOD_MODIFIED_CRAFTING_STAT_2      ; break;
                    case TYPECRIT_TAKEN_RANGED_RATING           : data.StatModifierBonusStat[data.CurrentStatType] = ITEM_MOD_CRIT_TAKEN_RANGED_RATING      ; break;
                    case TYPECRIT_TAKEN_SPELL_RATING            : data.StatModifierBonusStat[data.CurrentStatType] = ITEM_MOD_CRIT_TAKEN_SPELL_RATING       ; break;
                    case TYPEHASTE_MELEE_RATING                 : data.StatModifierBonusStat[data.CurrentStatType] = ITEM_MOD_HASTE_MELEE_RATING            ; break;
                    case TYPEHASTE_RANGED_RATING                : data.StatModifierBonusStat[data.CurrentStatType] = ITEM_MOD_HASTE_RANGED_RATING           ; break;
                    case TYPEHASTE_SPELL_RATING                 : data.StatModifierBonusStat[data.CurrentStatType] = ITEM_MOD_HASTE_SPELL_RATING            ; break;
                    case TYPEHIT_RATING                         : data.StatModifierBonusStat[data.CurrentStatType] = ITEM_MOD_HIT_RATING                    ; break;
                    case TYPECRIT_RATING                        : data.StatModifierBonusStat[data.CurrentStatType] = ITEM_MOD_CRIT_RATING                   ; break;
                    case TYPEHIT_TAKEN_RATING                   : data.StatModifierBonusStat[data.CurrentStatType] = ITEM_MOD_HIT_TAKEN_RATING              ; break;
                    case TYPECRIT_TAKEN_RATING                  : data.StatModifierBonusStat[data.CurrentStatType] = ITEM_MOD_CRIT_TAKEN_RATING             ; break;
                    case TYPERESILIENCE_RATING                  : data.StatModifierBonusStat[data.CurrentStatType] = ITEM_MOD_RESILIENCE_RATING             ; break;
                    case TYPEHASTE_RATING                       : data.StatModifierBonusStat[data.CurrentStatType] = ITEM_MOD_HASTE_RATING                  ; break;
                    case TYPEEXPERTISE_RATING                   : data.StatModifierBonusStat[data.CurrentStatType] = ITEM_MOD_EXPERTISE_RATING              ; break;
                    case TYPEATTACK_POWER                       : data.StatModifierBonusStat[data.CurrentStatType] = ITEM_MOD_ATTACK_POWER                  ; break;
                    case TYPERANGED_ATTACK_POWER                : data.StatModifierBonusStat[data.CurrentStatType] = ITEM_MOD_RANGED_ATTACK_POWER           ; break;
                    case TYPEVERSATILITY                        : data.StatModifierBonusStat[data.CurrentStatType] = ITEM_MOD_VERSATILITY                   ; break;
                    case TYPESPELL_HEALING_DONE                 : data.StatModifierBonusStat[data.CurrentStatType] = ITEM_MOD_SPELL_HEALING_DONE            ; break;
                    case TYPESPELL_DAMAGE_DONE                  : data.StatModifierBonusStat[data.CurrentStatType] = ITEM_MOD_SPELL_DAMAGE_DONE             ; break;
                    case TYPEMANA_REGENERATION                  : data.StatModifierBonusStat[data.CurrentStatType] = ITEM_MOD_MANA_REGENERATION             ; break;
                    case TYPEARMOR_PENETRATION_RATING           : data.StatModifierBonusStat[data.CurrentStatType] = ITEM_MOD_ARMOR_PENETRATION_RATING      ; break;
                    case TYPESPELL_POWER                        : data.StatModifierBonusStat[data.CurrentStatType] = ITEM_MOD_SPELL_POWER                   ; break;
                    case TYPEHEALTH_REGEN                       : data.StatModifierBonusStat[data.CurrentStatType] = ITEM_MOD_HEALTH_REGEN                  ; break;
                    case TYPESPELL_PENETRATION                  : data.StatModifierBonusStat[data.CurrentStatType] = ITEM_MOD_SPELL_PENETRATION             ; break;
                    case TYPEBLOCK_VALUE                        : data.StatModifierBonusStat[data.CurrentStatType] = ITEM_MOD_BLOCK_VALUE                   ; break;
                    case TYPEMASTERY_RATING                     : data.StatModifierBonusStat[data.CurrentStatType] = ITEM_MOD_MASTERY_RATING                ; break;
                    case TYPEEXTRA_ARMOR                        : data.StatModifierBonusStat[data.CurrentStatType] = ITEM_MOD_EXTRA_ARMOR                   ; break;
                    case TYPEFIRE_RESISTANCE                    : data.StatModifierBonusStat[data.CurrentStatType] = ITEM_MOD_FIRE_RESISTANCE               ; break;
                    case TYPEFROST_RESISTANCE                   : data.StatModifierBonusStat[data.CurrentStatType] = ITEM_MOD_FROST_RESISTANCE              ; break;
                    case TYPEHOLY_RESISTANCE                    : data.StatModifierBonusStat[data.CurrentStatType] = ITEM_MOD_HOLY_RESISTANCE               ; break;
                    case TYPESHADOW_RESISTANCE                  : data.StatModifierBonusStat[data.CurrentStatType] = ITEM_MOD_SHADOW_RESISTANCE             ; break;
                    case TYPENATURE_RESISTANCE                  : data.StatModifierBonusStat[data.CurrentStatType] = ITEM_MOD_NATURE_RESISTANCE             ; break;
                    case TYPEARCANE_RESISTANCE                  : data.StatModifierBonusStat[data.CurrentStatType] = ITEM_MOD_ARCANE_RESISTANCE             ; break;
                    case TYPEPVP_POWER                          : data.StatModifierBonusStat[data.CurrentStatType] = ITEM_MOD_PVP_POWER                     ; break;
                    case TYPECR_UNUSED_0                        : data.StatModifierBonusStat[data.CurrentStatType] = ITEM_MOD_CR_UNUSED_0                   ; break;
                    case TYPECR_UNUSED_1                        : data.StatModifierBonusStat[data.CurrentStatType] = ITEM_MOD_CR_UNUSED_1                   ; break;
                    case TYPECR_UNUSED_3                        : data.StatModifierBonusStat[data.CurrentStatType] = ITEM_MOD_CR_UNUSED_3                   ; break;
                    case TYPECR_SPEED                           : data.StatModifierBonusStat[data.CurrentStatType] = ITEM_MOD_CR_SPEED                      ; break;
                    case TYPECR_LIFESTEAL                       : data.StatModifierBonusStat[data.CurrentStatType] = ITEM_MOD_CR_LIFESTEAL                  ; break;
                    case TYPECR_AVOIDANCE                       : data.StatModifierBonusStat[data.CurrentStatType] = ITEM_MOD_CR_AVOIDANCE                  ; break;
                    case TYPECR_STURDINESS                      : data.StatModifierBonusStat[data.CurrentStatType] = ITEM_MOD_CR_STURDINESS                 ; break;
                    case TYPECR_UNUSED_7                        : data.StatModifierBonusStat[data.CurrentStatType] = ITEM_MOD_CR_UNUSED_7                   ; break;
                    case TYPECR_UNUSED_27                       : data.StatModifierBonusStat[data.CurrentStatType] = ITEM_MOD_CR_UNUSED_27                  ; break;
                    case TYPECR_UNUSED_9                        : data.StatModifierBonusStat[data.CurrentStatType] = ITEM_MOD_CR_UNUSED_9                   ; break;
                    case TYPECR_UNUSED_10                       : data.StatModifierBonusStat[data.CurrentStatType] = ITEM_MOD_CR_UNUSED_10                  ; break;
                    case TYPECR_UNUSED_11                       : data.StatModifierBonusStat[data.CurrentStatType] = ITEM_MOD_CR_UNUSED_11                  ; break;
                    case TYPECR_UNUSED_12                       : data.StatModifierBonusStat[data.CurrentStatType] = ITEM_MOD_CR_UNUSED_12                  ; break;
                    case TYPEAGI_STR_INT                        : data.StatModifierBonusStat[data.CurrentStatType] = ITEM_MOD_AGI_STR_INT                   ; break;
                    case TYPEAGI_STR                            : data.StatModifierBonusStat[data.CurrentStatType] = ITEM_MOD_AGI_STR                       ; break;
                    case TYPEAGI_INT                            : data.StatModifierBonusStat[data.CurrentStatType] = ITEM_MOD_AGI_INT                       ; break;
                    case TYPESTR_INT                            : data.StatModifierBonusStat[data.CurrentStatType] = ITEM_MOD_STR_INT                       ; break;


                    case InvNonEquipable        : data.InventoryType = 0; break;
                    case InvHead                : data.InventoryType = 1; break;
                    case InvNeck                : data.InventoryType = 2; break;
                    case InvShoulder            : data.InventoryType = 3; break;
                    case InvShirt               : data.InventoryType = 4; break;
                    case InvChest               : data.InventoryType = 5; break;
                    case InvWaist               : data.InventoryType = 6; break;
                    case InvLegs                : data.InventoryType = 7; break;
                    case InvFeet                : data.InventoryType = 8; break;
                    case InvWrists              : data.InventoryType = 9; break;
                    case InvHands               : data.InventoryType = 10; break;
                    case InvFinger              : data.InventoryType = 11; break;
                    case InvTrinket             : data.InventoryType = 12; break;
                    case InvWeapon              : data.InventoryType = 13; break;
                    case InvShield              : data.InventoryType = 14; break;
                    case InvRangedBows          : data.InventoryType = 15; break;
                    case InvBack                : data.InventoryType = 16; break;
                    case InvTwoHand             : data.InventoryType = 17; break;
                    case InvBag                 : data.InventoryType = 18; break;
                    case InvTabard              : data.InventoryType = 19; break;
                    case InvRobe                : data.InventoryType = 20; break;
                    case InvMainHand            : data.InventoryType = 21; break;
                    case InvOffHand             : data.InventoryType = 22; break;
                    case InvHoldableTome        : data.InventoryType = 23; break;
                    case InvAmmo                : data.InventoryType = 24; break;
                    case InvThrown              : data.InventoryType = 25; break;
                    case InvRangedRight         : data.InventoryType = 26; break;
                    case InvQuiver              : data.InventoryType = 27; break;
                    case InvRelic               : data.InventoryType = 28; break;

                    case SheatheOne:
                        data.Sheathe = 1;
                        break;
                    case SheatheTwo:
                        data.Sheathe = 2;
                        break;
                    case SheatheThree:
                        data.Sheathe = 3;
                        break;
                    case SheatheFour:
                        data.Sheathe = 4;
                        break;
                    case SheatheFive:
                        data.Sheathe = 5;
                        break;
                    case SheatheSix:
                        data.Sheathe = 6;
                        break;
                    case Poor:
                        data.Quality = 0;
                        break;
                    case Common:
                        data.Quality = 1;
                        break;
                    case Uncommon:
                        data.Quality = 2;
                        break;
                    case Rare:
                        data.Quality = 3;
                        break;
                    case Epic:
                        data.Quality = 4;
                        break;
                    case Legendary:
                        data.Quality = 5;
                        break;
                    case Artifact:
                        data.Quality = 6;
                        break;
                    case Heirloom:
                        data.Quality = 7;
                        break;
                    case WowToken:
                        data.Quality = 8;
                        break;
                    case Consumable:
                        data.Class = 0;
                        data.SubClass = 0;
                        break;
                    case Potion:
                        data.Class = 0;
                        data.SubClass = 1;
                        break;
                    case Elixir:
                        data.Class = 0;
                        data.SubClass = 2;
                        break;
                    case Flask:
                        data.Class = 0;
                        data.SubClass = 3;
                        break;
                    case Scroll:
                        data.Class = 0;
                        data.SubClass = 4;
                        break;
                    case FoodDrink:
                        data.Class = 0;
                        data.SubClass = 5;
                        break;
                    case ItemEnhancement:
                        data.Class = 0;
                        data.SubClass = 6;
                        break;
                    case Bandage:
                        data.Class = 0;
                        data.SubClass = 7;
                        break;
                    case Other:
                        data.Class = 0;
                        data.SubClass = 8;
                        break;
                    case Bag:
                        data.Class = 1;
                        data.SubClass = 0;
                        break;
                    case SoulBag:
                        data.Class = 1;
                        data.SubClass = 1;
                        break;
                    case HerbBag:
                        data.Class = 1;
                        data.SubClass = 2;
                        break;
                    case EnchantingBag:
                        data.Class = 1;
                        data.SubClass = 3;
                        break;
                    case EngineeringBag:
                        data.Class = 1;
                        data.SubClass = 4;
                        break;
                    case GemBag:
                        data.Class = 1;
                        data.SubClass = 5;
                        break;
                    case MiningBag:
                        data.Class = 1;
                        data.SubClass = 6;
                        break;
                    case LeatherworkingBag:
                        data.Class = 1;
                        data.SubClass = 7;
                        break;
                    case InscriptionBag:
                        data.Class = 1;
                        data.SubClass = 8;
                        break;
                    case AxeOnehanded:
                        data.Class = 2;
                        data.SubClass = 0;
                        break;
                    case AxeTwohanded:
                        data.Class = 2;
                        data.SubClass = 1;
                        break;
                    case Bow:
                        data.Class = 2;
                        data.SubClass = 2;
                        break;
                    case Gun:
                        data.Class = 2;
                        data.SubClass = 3;
                        break;
                    case MaceOnehanded:
                        data.Class = 2;
                        data.SubClass = 4;
                        break;
                    case MaceTwohanded:
                        data.Class = 2;
                        data.SubClass = 5;
                        break;
                    case Polearm:
                        data.Class = 2;
                        data.SubClass = 6;
                        break;
                    case SwordOnehanded:
                        data.Class = 2;
                        data.SubClass = 7;
                        break;
                    case SwordTwohanded:
                        data.Class = 2;
                        data.SubClass = 8;
                        break;
                    case Obsolete:
                        data.Class = 2;
                        data.SubClass = 9;
                        break;
                    case Staff:
                        data.Class = 2;
                        data.SubClass = 10;
                        break;
                    case Exotic:
                        data.Class = 2;
                        data.SubClass = 11;
                        break;
                    case Exotic2:
                        data.Class = 2;
                        data.SubClass = 12;
                        break;
                    case FistWeapon:
                        data.Class = 2;
                        data.SubClass = 13;
                        break;
                    case Miscellaneous:
                        data.Class = 2;
                        data.SubClass = 14;
                        break;
                    case Dagger:
                        data.Class = 2;
                        data.SubClass = 15;
                        break;
                    case Thrown:
                        data.Class = 2;
                        data.SubClass = 16;
                        break;
                    case Spear:
                        data.Class = 2;
                        data.SubClass = 17;
                        break;
                    case Crossbow:
                        data.Class = 2;
                        data.SubClass = 18;
                        break;
                    case Wand:
                        data.Class = 2;
                        data.SubClass = 19;
                        break;
                    case FishingPole:
                        data.Class = 2;
                        data.SubClass = 20;
                        break;
                    case Red:
                        data.Class = 3;
                        data.SubClass = 0;
                        break;
                    case Blue:
                        data.Class = 3;
                        data.SubClass = 1;
                        break;
                    case Yellow:
                        data.Class = 3;
                        data.SubClass = 2;
                        break;
                    case Purple:
                        data.Class = 3;
                        data.SubClass = 3;
                        break;
                    case Green:
                        data.Class = 3;
                        data.SubClass = 4;
                        break;
                    case Orange:
                        data.Class = 3;
                        data.SubClass = 5;
                        break;
                    case Meta:
                        data.Class = 3;
                        data.SubClass = 6;
                        break;
                    case Simple:
                        data.Class = 3;
                        data.SubClass = 7;
                        break;
                    case Prismatic:
                        data.Class = 3;
                        data.SubClass = 8;
                        break;
                    case Miscellaneous2:
                        data.Class = 4;
                        data.SubClass = 0;
                        break;
                    case Cloth:
                        data.Class = 4;
                        data.SubClass = 1;
                        break;
                    case Leather:
                        data.Class = 4;
                        data.SubClass = 2;
                        break;
                    case Mail:
                        data.Class = 4;
                        data.SubClass = 3;
                        break;
                    case Plate:
                        data.Class = 4;
                        data.SubClass = 4;
                        break;
                    case BucklerOBSOLETE:
                        data.Class = 4;
                        data.SubClass = 5;
                        break;
                    case Shield:
                        data.Class = 4;
                        data.SubClass = 6;
                        break;
                    case Libram:
                        data.Class = 4;
                        data.SubClass = 7;
                        break;
                    case Idol:
                        data.Class = 4;
                        data.SubClass = 8;
                        break;
                    case Totem:
                        data.Class = 4;
                        data.SubClass = 9;
                        break;
                    case Sigil:
                        data.Class = 4;
                        data.SubClass = 10;
                        break;
                    case Reagent:
                        data.Class = 5;
                        data.SubClass = 0;
                        break;
                    case WandOBSOLETE:
                        data.Class = 6;
                        data.SubClass = 0;
                        break;
                    case BoltOBSOLETE:
                        data.Class = 6;
                        data.SubClass = 1;
                        break;
                    case Arrow:
                        data.Class = 6;
                        data.SubClass = 2;
                        break;
                    case Bullet:
                        data.Class = 6;
                        data.SubClass = 3;
                        break;
                    case ThrownOBSOLETE:
                        data.Class = 6;
                        data.SubClass = 4;
                        break;
                    case QuiverCanholdarrows:
                        data.Class = 11;
                        data.SubClass = 2;
                        break;
                    case AmmoPouchCanholdbullets:
                        data.Class = 11;
                        data.SubClass = 3;
                        break;
                    case Quest:
                        data.Class = 12;
                        data.SubClass = 0;
                        break;
                    case Key:
                        data.Class = 13;
                        data.SubClass = 0;
                        break;
                    case Lockpick:
                        data.Class = 13;
                        data.SubClass = 1;
                        break;
                    case Permanent:
                        data.Class = 14;
                        data.SubClass = 0;
                        break;
                    case Junk:
                        data.Class = 15;
                        data.SubClass = 0;
                        break;
                    case Reagent2:
                        data.Class = 15;
                        data.SubClass = 1;
                        break;
                    case Pet:
                        data.Class = 15;
                        data.SubClass = 2;
                        break;
                    case Holiday2:
                        data.Class = 15;
                        data.SubClass = 3;
                        break;
                    case Other2:
                        data.Class = 15;
                        data.SubClass = 4;
                        break;
                    case Mount:
                        data.Class = 15;
                        data.SubClass = 5;
                        break;
                    case Warrior:
                        data.Class = 16;
                        data.SubClass = 1;
                        break;
                    case Paladin:
                        data.Class = 16;
                        data.SubClass = 2;
                        break;
                    case Hunter:
                        data.Class = 16;
                        data.SubClass = 3;
                        break;
                    case Rogue:
                        data.Class = 16;
                        data.SubClass = 4;
                        break;
                    case Priest:
                        data.Class = 16;
                        data.SubClass = 5;
                        break;
                    case DeathKnight:
                        data.Class = 16;
                        data.SubClass = 6;
                        break;
                    case Shaman:
                        data.Class = 16;
                        data.SubClass = 7;
                        break;
                    case Mage:
                        data.Class = 16;
                        data.SubClass = 8;
                        break;
                    case Warlock:
                        data.Class = 16;
                        data.SubClass = 9;
                        break;
                    case Druid:
                        data.Class = 16;
                        data.SubClass = 11;
                        break;
                    default:
                        ChatHandler(player).PSendSysMessage("SenderEditField %u actionId not implemented", actionId);
                        break;
                }
                GoToLastMenuForPlayer(player);
                break;
        }
    }

    void OnGossipSelectCode(Player* player, uint32 menuId, uint32 sender, uint32 actionId, char const* code) override
    {
        if (menuId != 5050)
            return;

        ClearGossipMenuFor(player);

        if (!code)
            return;

        auto& data = _createItemPlayerData[player->GetGUID().GetCounter()];

        if (sender == SenderEditField)
        {
            switch (actionId)
            {
                case Actions::RawEntry:
                    data.EntryID = atol(code);
                    break;
                case Actions::RawClass:
                    data.Class = atol(code);
                    break;
                case Actions::RawSubClass:
                    data.SubClass = atol(code);
                    break;
                case Actions::RawName:
                    data.Name = code;
                    break;
                case Actions::RawDescription:
                    data.Description = code;
                    break;
                case Actions::RawQuality:
                    data.Quality = atol(code);
                    break;
                case Actions::RawIconFileDataID:
                    data.IconFileDataID = atol(code);
                    break;
                case Actions::RawInventoryType:
                    data.InventoryType = atol(code);
                    break;
                case Actions::RawSheathe:
                    data.Sheathe = atol(code);
                    break;
                case Actions::RawItemLevel:
                    data.ItemLevel = atol(code);
                    break;
                case Actions::RawItemAppearanceID:
                    data.ItemAppearanceID = atol(code);
                    break;
                case Actions::RawItemID:
                    data.DisplayItemID = atol(code);
                    break;
                case Actions::RawStatPercentEditor1 : data.StatPercentEditor[0] = atol(code);  break;
                case Actions::RawStatPercentEditor2 : data.StatPercentEditor[1] = atol(code);  break;
                case Actions::RawStatPercentEditor3 : data.StatPercentEditor[2] = atol(code);  break;
                case Actions::RawStatPercentEditor4 : data.StatPercentEditor[3] = atol(code);  break;
                case Actions::RawStatPercentEditor5 : data.StatPercentEditor[4] = atol(code);  break;
                case Actions::RawStatPercentEditor6 : data.StatPercentEditor[5] = atol(code);  break;
                case Actions::RawStatPercentEditor7 : data.StatPercentEditor[6] = atol(code);  break;
                case Actions::RawStatPercentEditor8 : data.StatPercentEditor[7] = atol(code);  break;
                case Actions::RawStatPercentEditor9 : data.StatPercentEditor[8] = atol(code);  break;
                case Actions::RawStatPercentEditor10: data.StatPercentEditor[9] = atol(code);  break;

            }
            GoToLastMenuForPlayer(player);
        }

        // switch (actionId)
        // {
        // 
        // }
    }

    void GoToLastMenuForPlayer(Player* player)
    {
        auto lastAction = _createItemPlayerData[player->GetGUID().GetCounter()].LastMenuId;
        OnGossipSelect(player, 5050, Senders::SenderMenu, lastAction);
    }
};

class cs_custom : public CommandScript
{
public:
    cs_custom() : CommandScript("cs_custom") { }

    ChatCommandTable GetCommands() const override
    {
        static ChatCommandTable commandTable =
        {
            { "start",            HandleStartCommand,      rbac::RBAC_PERM_INSTANT_LOGOUT,          Console::No },
            { "createitem",       HandleCreateItemCommand, rbac::RBAC_PERM_COMMAND_RELOAD_ALL_ITEM, Console::No },
            { "magicstone",       HandleReloadMagicStone,  rbac::RBAC_PERM_COMMAND_RELOAD_ALL_ITEM, Console::No },
            { "instance_respawn", HandleReloadInstanceRespawn,  rbac::RBAC_PERM_COMMAND_RELOAD_ALL_ITEM, Console::No },
            { "testpacket",       HandleTestCommand,  rbac::RBAC_PERM_COMMAND_RELOAD_ALL_ITEM, Console::No },
            { "testpacket2",       HandleTest2Command,  rbac::RBAC_PERM_COMMAND_RELOAD_ALL_ITEM, Console::No },
            { "testpacket3",       HandleTest3Command,  rbac::RBAC_PERM_COMMAND_RELOAD_ALL_ITEM, Console::No },
            { "testpacket4",       HandleTest4Command,  rbac::RBAC_PERM_COMMAND_RELOAD_ALL_ITEM, Console::No },
            { "testpacket5",       HandleTest5Command,  rbac::RBAC_PERM_COMMAND_RELOAD_ALL_ITEM, Console::No },

#ifdef WIN32
            { "gpscopy", HandleGPSCopyCommand,  rbac::RBAC_PERM_COMMAND_RELOAD_ALL_ITEM, Console::No },
#endif

        };
        return commandTable;
    }

    static bool HandleTestCommand(ChatHandler* handler, Optional<uint32> CovenantID)
    {
        WorldPackets::Covenant::CovenantPreviewOpenNpc packet;
        packet.NpcGUID = handler->GetPlayer()->GetGUID();
        packet.CovenantID = CovenantID.value_or(0);
        handler->GetSession()->SendPacket(packet.Write());
        return true;
    }
    static bool HandleTest2Command(ChatHandler* handler, Optional<uint32> CovenantID)
    {
        WorldPacket data(SMSG_WORLD_MAP_OPEN_NPC, 20);
        data << handler->GetPlayer()->GetGUID();
        data << uint32(CovenantID.value_or(0));
        handler->GetSession()->SendPacket(&data);
        return true;
    }
    static bool HandleTest3Command(ChatHandler* handler, Optional<uint32> CovenantID)
    {
        WorldPacket data(SMSG_ADVENTURE_MAP_OPEN_NPC, 20);
        data << handler->GetPlayer()->GetGUID();
        data << uint32(CovenantID.value_or(0));
        handler->GetSession()->SendPacket(&data);
        return true;
    }
    static bool HandleTest4Command(ChatHandler* handler, Optional<uint32> flag)
    {
        auto player = handler->GetPlayer();
        WorldPackets::Quest::DisplayPlayerChoice displayPlayerChoice;

        displayPlayerChoice.SenderGUID = player->GetGUID();
        displayPlayerChoice.ChoiceID = 682925852;
        displayPlayerChoice.Question = "Are you sure you want to upgrade?";
        displayPlayerChoice.CloseChoiceFrame = false;
        displayPlayerChoice.HideWarboardHeader = false;
        displayPlayerChoice.KeepOpenAfterChoice = false;

        displayPlayerChoice.UiTextureKitID = 5260;
        displayPlayerChoice.SoundKitID = 80244; // 80244 brwaler upgrade

        for (int i = 0; i < 1; ++i)
        {
            WorldPackets::Quest::PlayerChoiceResponse playerChoiceResponse;

            playerChoiceResponse.ResponseID = 4412414;
            playerChoiceResponse.ResponseIdentifier = 335;
            playerChoiceResponse.Flags = 2;
            playerChoiceResponse.ChoiceArtFileID = flag.value_or(1274664);
            playerChoiceResponse.UiTextureKitID = 5487;
            playerChoiceResponse.Reward.emplace();
            playerChoiceResponse.RewardQuestID = 591918;
            if (i == 0)
            {
                playerChoiceResponse.Header = "Requirements";
                //playerChoiceResponse.SubHeader = "Requirements";
                playerChoiceResponse.ButtonTooltip = "Clicking this will consume the requirements!";
                playerChoiceResponse.Confirmation = "Confirmation";
                playerChoiceResponse.Flags = 0;
                playerChoiceResponse.Answer = "Requirements";
                playerChoiceResponse.ButtonTooltip = "|cffFF0000Not enough x...";
                playerChoiceResponse.SubHeader = "Consumes";
            }
            else
            {
                playerChoiceResponse.Header = "Rewards";
                //playerChoiceResponse.SubHeader = "Rewards";
                playerChoiceResponse.SubHeader = "Awards";
                playerChoiceResponse.Answer = "Upgrade";
                playerChoiceResponse.ButtonTooltip = "Are you sure you want to upgrade?";
                playerChoiceResponse.Confirmation = "Confirmation";
            }

            playerChoiceResponse.Reward.emplace();
            playerChoiceResponse.Reward->Money = 400000;
            for (int i = 0; i < 2; ++i)
            {
                if (auto item = player->GetItemByEntry(i == 0 ? 183021 : 175921))
                {

                    {
                        playerChoiceResponse.Reward->Items.emplace_back();
                        WorldPackets::Quest::PlayerChoiceResponseRewardEntry& rewardEntry = playerChoiceResponse.Reward->Items.back();
                        rewardEntry.Item.ItemID = item->GetEntry();
                        rewardEntry.Item.Initialize(item);
                    }
                }
            }

            playerChoiceResponse.Reward->Currencies.emplace_back();
            WorldPackets::Quest::PlayerChoiceResponseRewardEntry& rewardEntry = playerChoiceResponse.Reward->Currencies.back();
            rewardEntry.Item.ItemID = 1813;
            rewardEntry.Quantity = 500;

            displayPlayerChoice.Responses.push_back(playerChoiceResponse);
        }


        handler->GetSession()->SendPacket(displayPlayerChoice.Write());
        return true;
    }
    static bool HandleTest5Command(ChatHandler* handler, Optional<uint32> flag)
    {
        auto player = handler->GetPlayer();
        WorldPackets::Quest::DisplayPlayerChoice displayPlayerChoice;

        displayPlayerChoice.SenderGUID = player->GetGUID();
        displayPlayerChoice.ChoiceID = 682925853;
        displayPlayerChoice.Question = "Rewards Chest";
        displayPlayerChoice.CloseChoiceFrame = false;
        displayPlayerChoice.HideWarboardHeader = false;
        displayPlayerChoice.KeepOpenAfterChoice = false;

        displayPlayerChoice.UiTextureKitID = 5240;
        displayPlayerChoice.SoundKitID = 40319; // 80244 brwaler upgrade

        for (int i = 0; i < 2; ++i)
        {
            WorldPackets::Quest::PlayerChoiceResponse playerChoiceResponse;

            playerChoiceResponse.ResponseID = 4412414;
            playerChoiceResponse.ResponseIdentifier = 335;
            playerChoiceResponse.Flags = 2;
            playerChoiceResponse.ChoiceArtFileID = flag.value_or(986496);
            playerChoiceResponse.UiTextureKitID = 0;
            playerChoiceResponse.Reward.emplace();
            //playerChoiceResponse.RewardQuestID = 591918;
            if (i == 0)
            {
                playerChoiceResponse.Header = "Today";
                //playerChoiceResponse.SubHeader = "Requirements";
                playerChoiceResponse.ButtonTooltip = "Clicking this will consume the requirements!";
                playerChoiceResponse.Confirmation = "Confirmation";
                playerChoiceResponse.Flags = 5;
                playerChoiceResponse.Answer = "Requirements";
                playerChoiceResponse.ButtonTooltip = "|cffFF0000Not enough x...";
                playerChoiceResponse.SubHeader = "";
            }
            else
            {
                playerChoiceResponse.Header = "Tommorow";
                //playerChoiceResponse.SubHeader = "Rewards";
                playerChoiceResponse.Flags = 5;
                playerChoiceResponse.SubHeader = "";
                playerChoiceResponse.Answer = "Upgrade";
                playerChoiceResponse.ButtonTooltip = "Login tommorow to claim!";
                playerChoiceResponse.Confirmation = "Confirmation";
            }

            playerChoiceResponse.Reward.emplace();
            playerChoiceResponse.Reward->Money = 400000;
            for (int i = 0; i < 2; ++i)
            {
                if (auto item = player->GetItemByEntry(i == 0 ? 183021 : 175921))
                {

                    {
                        playerChoiceResponse.Reward->Items.emplace_back();
                        WorldPackets::Quest::PlayerChoiceResponseRewardEntry& rewardEntry = playerChoiceResponse.Reward->Items.back();
                        rewardEntry.Item.ItemID = item->GetEntry();
                        rewardEntry.Item.Initialize(item);
                    }
                }
            }

            playerChoiceResponse.Reward->Currencies.emplace_back();
            WorldPackets::Quest::PlayerChoiceResponseRewardEntry& rewardEntry = playerChoiceResponse.Reward->Currencies.back();
            rewardEntry.Item.ItemID = 1813;
            rewardEntry.Quantity = 500;

            displayPlayerChoice.Responses.push_back(playerChoiceResponse);
        }


        handler->GetSession()->SendPacket(displayPlayerChoice.Write());
        return true;
    }

    // Teleports and revives the player at their homebind.
    // Useful if the player somehow gets stuck.
    static bool HandleStartCommand(ChatHandler* handler)
    {
        auto player = handler->GetPlayer();
        player->TeleportTo(player->m_homebind, TELE_REVIVE_AT_TELEPORT);
        return true;
    }

#ifdef WIN32
    static bool HandleGPSCopyCommand(ChatHandler* handler, Optional<uint32> keep)
    {
        std::ostringstream ss;

        auto player = handler->GetPlayer();

        ss << "{ " << player->GetPositionX() << "f, " << player->GetPositionY() << "f, " << player->GetPositionZ() << "f, " << player->GetOrientation() << "f }, ";
        const char* output = ss.str().c_str();
        const size_t len = strlen(output) + 1;
        HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, len);
        memcpy(GlobalLock(hMem), output, len);
        GlobalUnlock(hMem);
        OpenClipboard(0);
        if (!keep.has_value())
            EmptyClipboard();
        SetClipboardData(CF_TEXT, hMem);
        CloseClipboard();
        handler->SendSysMessage(ss.str().c_str());
        return true;
    }
#endif

    static bool HandleReloadInstanceRespawn(ChatHandler* handler, char const* /*args*/)
    {
        TC_LOG_INFO("misc", "Reloading HandleReloadBroadcastText table...");
        handler->SendSysMessage("Loading broadcast_text");
        sCustomInstanceRespawn->LoadFromDB();
        return true;
    }

    static bool HandleReloadMagicStone(ChatHandler* handler, char const* /*args*/)
    {
        handler->SendSysMessage("Loading magic stone!");
        TC_LOG_INFO("misc", "Reloading HandleReloadMagicStone table...");
        sMagicStoneMgr->LoadFromDB();
        return true;
    }

    static bool HandleCreateItemCommand(ChatHandler* handler, Optional<std::string_view> a)
    {
        auto player = handler->GetPlayer();


        uint32 itemId = 0;

        if (a.has_value())
        {
            auto args = a.value().data();
            if (args[0] == '[')                                        // [name] manual form
            {
                char const* itemNameStr = strtok((char*)args, "]");

                if (itemNameStr && itemNameStr[0])
                {
                    std::string itemName = itemNameStr + 1;
                    auto itr = std::find_if(sItemSparseStore.begin(), sItemSparseStore.end(), [&itemName](ItemSparseEntry const* sparse)
                        {
                            for (LocaleConstant i = LOCALE_enUS; i < TOTAL_LOCALES; i = LocaleConstant(i + 1))
                                if (itemName == sparse->Display[i])
                                    return true;
                            return false;
                        });

                    if (itr == sItemSparseStore.end())
                    {
                        handler->PSendSysMessage(LANG_COMMAND_COULDNOTFIND, itemNameStr + 1);
                        handler->SetSentErrorMessage(true);
                        return false;
                    }

                    itemId = itr->ID;
                }
                else
                    return false;
            }
            else                                                    // item_id or [name] Shift-click form |color|Hitem:item_id:0:0:0|h[name]|h|r
            {
                char const* id = handler->extractKeyFromLink((char*)args, "Hitem");
                if (!id)
                    return false;
                itemId = atoul(id);
            }
        }

        if (itemId > 0)
        {
            auto& data = _createItemPlayerData[player->GetGUID().GetCounter()];
            data.DisplayItemID = itemId;

            handler->PSendSysMessage("Set AppearanceID to %u", data.DisplayItemID);
        }

        create_item_player_script::ShowMenu(player);
        return true;
    }
};

void AddSC_cs_custom()
{
    new cs_custom();
    new create_item_player_script();
}
