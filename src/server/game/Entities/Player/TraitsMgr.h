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
        class ActiveGlyphs;
        class LearnTraits;
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

enum class TraitTrees
{
    Unk        = 0,
    HunterMain = 127,
    DHAllAlpha = 732,
};

inline TraitTrees GetTraitTreeForClass(uint8 classId);

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

    private:
        Player* _player;
        uint32 _specId;
        uint16 _pvpTalents[MAX_PVP_TALENT_SLOTS];
        std::vector<uint32> _glyphs;
};

struct TC_GAME_API TraitTalent
{
    TraitTalent(Player* player, Trait* trait, uint32 TraitNode, uint32 TraitNodeEntryID, uint32 Rank, uint32 Unk);

    uint32 TraitNode;
    uint32 TraitNodeEntryID;
    uint32 Rank;
    uint32 Unk;

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

enum class TraitType
{
    Talents      = 1,
    Unk          = 2,
    DragonRiding = 3,
};

class TC_GAME_API Trait
{
    public:
        Trait(Player* player, uint32 configId, uint32 specId, TraitType type, uint32 index);
        ~Trait();

        void SetConfigName(std::string_view configName);
        std::string const& GetConfigName() { return _configName; }

        uint32 GetIndex() const { return _index; }
        uint32 GetConfigID() const { return _configID; }
        uint32 GetSpecializationID() const { return _specializationID; }
        TraitType GetType() const { return _type; }

        void AddTraitTalent(TraitTalent* talent);
        bool RemoveTraitTalent(uint32 traitNode);

        void LearnTraitSpells();
        void LearnTraitSpell(TraitTalent* talent);
        void UnlearnTraitSpells();
        void RemoveTraitSpell(TraitTalent* talent);

        std::unordered_map<uint32, TraitTalent*>* GetTalents();

    private:
        Player* _player;
        uint32 _index;
        uint32 _configID;
        uint32 _specializationID;
        TraitType _type;
        std::string _configName;
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

        void LoadFromDB(CharacterDatabaseQueryHolder const& holder);

        void SendUpdateTalentData();

        /// Specialization
        int8 GetActiveTalentGroup() const { return _activeTalentGroup; }
        int8 GetActiveTalentGroupSafe() const { return _activeTalentGroup == -1 ? 0 : _activeTalentGroup; }
        void SetActiveTalentGroup(int8 orderIndex, bool force = false);
        Specialization* GetActiveSpecialization();
        Specialization* GetSpecialization(int8 orderIndex);

        /// Traits
        Trait* GetActiveTrait();
        Trait* GetTraitForSpec(uint32 specId);
        Trait* CreateDefaultTraitForSpec(ChrSpecializationEntry const* specEntry, bool activeSpec = false);
        void LearnTraits(WorldPackets::Talent::LearnTraits& learnTraits);

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
        uint32 _nextConfigId = 608843;
};
