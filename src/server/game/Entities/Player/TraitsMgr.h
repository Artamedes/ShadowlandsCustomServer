/// WRITTEN BY ARTAMEDES FOR SHADOWS-EMBRACE
/// 9-8-22
#pragma once

/// Common
#include "Common.h"

#include "DBCEnums.h"
#include "DatabaseEnvFwd.h"

#include <vector>

namespace WorldPackets
{
    namespace Talent
    {
        struct TalentGroupInfo;
        struct TraitConfigEntry;
        class ActiveGlyphs;
        class LearnTraits;
        class CreateNewLoadout;
    }
}

struct ChrSpecializationEntry;
struct TraitNodeEntry;
struct TraitTreeEntry;
struct TraitNodeEntryEntry;
struct TraitDefinitionEntry;

class Player;
class Trait;

// OK DF.45480
enum class TalentLearnResult
{
    Ok                            = 0,
    Unk                           = 1,
    NotEnoughTalentsInPrimaryTree = 2,
    NoPrimaryTreeSelected         = 3,
    CantDoThatRightNow            = 4,
    AffectingCombat               = 5,
    SpellOnCooldown               = 6,
    CantDoThatChallengeModeActive = 7,
    RestArea                      = 8,
};

// TraitConfigType
enum class TraitType : int32
{
    Invalid    = 0,
    Combat     = 1,
    Profession = 2,
    Generic    = 3,
};

enum class TraitTreeFlag : int32
{
    None                  = 0x0,
    CannotRefund          = 0x1,
    HideSingleRankNumbers = 0x2,
};

DEFINE_ENUM_FLAG(TraitTreeFlag);

enum class TraitCombatConfigFlags : int32
{
    None              = 0x0,
    ActiveForSpec     = 0x1,
    StarterBuild      = 0x2,
    SharedActionBVars = 0x4,
};

DEFINE_ENUM_FLAG(TraitCombatConfigFlags);

constexpr uint32 DragonridingSystemID = 1;

/// TraitConsts
constexpr uint32 MAX_COMBAT_TRAIT_CONFIGS = 10;
constexpr uint32 COMMIT_COMBAT_TRAIT_CONFIG_CHANGES_SPELL_ID = 384255;

class TC_GAME_API Specialization
{
    public:
        Specialization(Player* player, ChrSpecializationEntry const* specEntry);

        void BuildUpdateTalentDataPacket(WorldPackets::Talent::TalentGroupInfo& info);
        void BuildActiveGlyphsPacket(WorldPackets::Talent::ActiveGlyphs& activeGlyphs);

        uint16 GetSpecId() const { return _specId; }

        void TogglePVPTalents(bool on);
        void RemoveGlyphAuras();
        void LoadGlyphAuras();
        void SetPVPTalent(uint16 pvpTalentId, uint8 slot);
        uint16 GetPVPTalent(uint8 slot) const;
        void SetActiveLoadoutId(uint32 loadoutId) { _activeLoadoutId = loadoutId; }
        uint32 GetActiveLoadoutId() const { return _activeLoadoutId; };

        Trait* GetDefaultTrait() { return _trait; }

    private:
        Player* _player;
        uint32 _specId;
        uint16 _pvpTalents[MAX_PVP_TALENT_SLOTS];
        std::vector<uint32> _glyphs;
        std::vector<Trait*> _traits;
        Trait* _trait;
        uint32 _activeLoadoutId;
};

struct TC_GAME_API TraitTalent
{
    TraitTalent(Player* player, Trait* trait, uint32 TraitNode, uint32 TraitNodeEntryID, uint32 Rank, EnumFlag<TraitTreeFlag> treeFlags, bool isDefault = false);

    void Initialize();

    uint32 TraitNodeID;
    uint32 TraitNodeEntryID;
    uint32 Rank;
    EnumFlag<TraitTreeFlag> TreeFlags;

    bool IsDefault;
    bool IsChanged = true;

    /// Stored to prevent lookup at runtime
    TraitNodeEntry       const* TraitNodeEntry;
    TraitTreeEntry       const* TraitTreeEntry;
    TraitNodeEntryEntry  const* TraitNodeEntryEntry;
    TraitDefinitionEntry const* TraitDefinitionEntry;

    Player* _player;
    Trait* _trait;

    bool operator==(TraitTalent const& right) const;
    bool operator!=(TraitTalent const& right) const { return !(*this == right); }
};

class TC_GAME_API Trait
{
    public:
        Trait(Player* player, uint32 configId, TraitType type);
        ~Trait();

        uint32 GetConfigID() const { return _configID; }
        TraitType GetType() const { return _type; }

        void SetSkillLineID(uint32 skillLineID) { _skillLineID = skillLineID; }
        uint32 GetSkillLineID() const { return _skillLineID; }

        void SetSpecializationID(uint32 specializationID) { _specializationID = specializationID; }
        uint32 GetSpecializationID() const { return _specializationID; }

        void SetCombatConfigFlags(TraitCombatConfigFlags flags) { _combatConfigFlags = flags; }
        void AddCombatConfigFlags(TraitCombatConfigFlags flags) { _combatConfigFlags.AddFlag(flags); }
        void RemoveCombatConfigFlags(TraitCombatConfigFlags flags) { _combatConfigFlags.RemoveFlag(flags); }
        EnumFlag<TraitCombatConfigFlags> GetCombatConfigFlags() const { return _combatConfigFlags; }

        void SetLoadoutIndex(uint32 index) { _loadoutIndex = index; }
        uint32 GetLoadoutIndex() const { return _loadoutIndex; }

        void SetSystemID(uint32 systemID) { _systemID = systemID; }
        uint32 GetSystemID() const { return _systemID; }

        void SetConfigName(std::string const& loadoutName);
        std::string const& GetConfigName() { return _loadoutName; }

        void AddTraitTalent(TraitTalent* talent);
        bool RemoveTraitTalent(uint32 traitNode);
        bool RemoveTraitTalentOnlyUnlearn(uint32 traitNode);

        void LearnTraitSpells();
        void LearnTraitSpell(TraitTalent* talent);
        void UnlearnTraitSpells();
        void RemoveTraitSpell(TraitTalent* talent);

        std::unordered_map<uint32, TraitTalent*>* GetTalents();

        void SaveToDB(CharacterDatabaseTransaction trans);

        void SetIndex(uint32 index) { _index = index; }
        uint32 GetIndex() const { return _index; }

    private:
        Player* _player;

        uint32 _configID;
        TraitType _type;

        /// This works a certain way - values are only used by certain types.
        /// TraitType::Profession
        uint32 _skillLineID;
        /// TraitType::Combat
        uint32 _specializationID;
        EnumFlag<TraitCombatConfigFlags> _combatConfigFlags;
        uint32 _loadoutIndex;
        /// TraitType::Generic
        uint32 _systemID;

        uint32 _index; ///< The index stored in the update field

        std::string _loadoutName;
        std::unordered_map<uint32, TraitTalent*> _talents;
};

class TC_GAME_API TraitsMgr
{
    public:
        TraitsMgr(Player* player);
        ~TraitsMgr();

        /// <summary>
        /// Setups the player's specialization info. Called when player is first loading
        /// </summary>
        void Setup();
        void SetupDragonRiding();

        void LoadFromDB(CharacterDatabaseQueryHolder const& holder);
        void SaveToDB(CharacterDatabaseTransaction trans);

        void SendUpdateTalentData();

        /// Specialization
        Specialization* GetActiveSpecialization();
        Specialization* GetSpecialization(int8 orderIndex);

        void SetActiveTalentGroup(int8 orderIndex, bool force = false);

        int8 GetActiveTalentGroup() const { return _activeTalentGroup; }
        int8 GetActiveTalentGroupSafe() const { return _activeTalentGroup == -1 ? 0 : _activeTalentGroup; }

        /// Traits
        Trait* GetActiveTrait();
        Trait* GetTraitForSpec(uint32 specId);
        Trait* GetTraitByConfigID(uint32 configID);
        Trait* CreateDefaultTraitForSpec(ChrSpecializationEntry const* specEntry, bool activeSpec = false);
        Trait* GetTraitByLoadoutID(uint32 loadoutId);

        void LearnTraits(WorldPackets::Talent::LearnTraits& learnTraits);
        void CreateNewLoadout(WorldPackets::Talent::CreateNewLoadout& createNewLoadout);
        void SwapLoadout(uint32 loadoutId, std::vector<WorldPackets::Talent::TraitConfigEntry> traits);
        void SwapLoadout(uint32 loadout);
        void RenameLoadout(uint32 configId, std::string const& newName);
        void RemoveLoadout(uint32 configId);

        uint32 GetNextTraitLoadoutIndex() const;

        /// Glyphs
        void SendActiveGlyphs(bool fullUpdate = false);
        void LoadGlyphAuras();

        /// PvPTalents
        void TogglePVPTalents(bool on);
        TalentLearnResult LearnPVPTalent(uint16 pvpTalentId, uint8 slot, int32* spellOnCooldown = nullptr);

    private:
        Player* _player;
        int8 _activeTalentGroup = 0;
        Trait* _activeTrait = nullptr;
        std::vector<Specialization*> _specializations;
        std::unordered_map<uint32, Trait*> _traits; ///< Key: ConfigID, Value: Trait*
        uint32 _nextConfigId = 700100;
        bool _hasDragonriding = false;
};
