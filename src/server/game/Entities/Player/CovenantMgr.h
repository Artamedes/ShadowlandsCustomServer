#pragma once

#include "Common.h"
#include "SharedDefines.h"
#include "DatabaseEnvFwd.h"
#include "DB2Structure.h"
#include "EnumFlag.h"
#include "GarrisonPackets.h"

class Player;
class Unit;
class Item;

enum class CovenantID : int32
{
    None        = 0,
    Kyrian      = 1,
    Venthyr     = 2,
    NightFae    = 3,
    Necrolord   = 4,
};

enum class SoulbindID : int32
{
    None                  = 0,
    Niya                  = 1,
    Dreamweaver           = 2,
    GeneralDraven         = 3,
    PlagueDeviserMarileth = 4,
    Emeni                 = 5,
    Korayn                = 6,
    Pelagos               = 7,
    NadjiaTheMistblade    = 8,
    TheotarTheMadDuke     = 9,
    BonesmithHeimer       = 10,
    Kleia                 = 13,
    ForgePrimeMikanikos   = 18,
};

enum class SoulbindUIDisplayInfoIds : uint32
{
    None          = 0,
    Niya          = 1,
    Dreamweaver   = 2,
    GeneralDraven = 3,
    Marileth      = 4,
    Emeni         = 5,
    Korayn        = 7,
    Pelagos       = 9,
    Heimer        = 10,
    Kleia         = 11,
    Mikanikos     = 12,
    Nadjia        = 14,
    Theotar       = 15,
};

enum GarrTalentTreeIds : uint32
{
    Niya          = 276,
    Dreamweaver   = 275,
    GeneralDraven = 304,
    Marileth      = 325,
    Emeni         = 330,
    Korayn        = 334,
    Pelagos       = 357,
    Heimer        = 349,
    Kleia         = 360,
    Mikanikos     = 365,
    Nadjia        = 272,
    Nadjia2       = 368, // hmm
    Theotar       = 392,
};

enum class eCovenantSaveFlags : uint32
{
    None              = 0x0,
    SaveConduits      = 0x1,
    SaveSoulbind      = 0x2,
    SaveCovenant      = 0x4,
    SaveRenownRewards = 0x8,
};

DEFINE_ENUM_FLAG(eCovenantSaveFlags);

enum class eCovenantMgrSaveFlags : uint32
{
    None              = 0x0,
    SaveCollections   = 0x1,
    SaveSoulbindSpecs = 0x2,
};

DEFINE_ENUM_FLAG(eCovenantMgrSaveFlags);

enum GarrisonTalentFlags
{
    TalentFlagDisabled = 0x0,
    TalentFlagEnabled  = 0x1,
};

static SoulbindID GetSoulbindIDFromTalentTreeId(uint32 talentTreeId)
{
    switch (talentTreeId)
    {
        case GarrTalentTreeIds::Niya: return SoulbindID::Niya;
        case GarrTalentTreeIds::Dreamweaver: return SoulbindID::Dreamweaver;
        case GarrTalentTreeIds::GeneralDraven: return SoulbindID::GeneralDraven;
        case GarrTalentTreeIds::Marileth: return SoulbindID::PlagueDeviserMarileth;
        case GarrTalentTreeIds::Emeni: return SoulbindID::Emeni;
        case GarrTalentTreeIds::Korayn: return SoulbindID::Korayn;
        case GarrTalentTreeIds::Pelagos: return SoulbindID::Pelagos;
        case GarrTalentTreeIds::Heimer: return SoulbindID::BonesmithHeimer;
        case GarrTalentTreeIds::Kleia: return SoulbindID::Kleia;
        case GarrTalentTreeIds::Mikanikos: return SoulbindID::ForgePrimeMikanikos;
        case GarrTalentTreeIds::Nadjia: return SoulbindID::NadjiaTheMistblade;
        case GarrTalentTreeIds::Nadjia2: return SoulbindID::NadjiaTheMistblade;
        case GarrTalentTreeIds::Theotar: return SoulbindID::TheotarTheMadDuke;
        default:
            return SoulbindID::None;
    }
}

struct TC_GAME_API Conduit
{
    Conduit(Player* player) : _player(player) { }

    uint32 TalentEntryId = 0;//GarrTalentEntry const* TalentEntry;
    uint32 TreeEntryId = 0;//GarrTalentTreeEntry const* TreeEntry;
    uint32 Rank = 1;
    uint32 Flags = 1;
    uint64 ResearchStartTime = 0;

    Optional<WorldPackets::Garrison::GarrisonTalentSocketData> Socket;

    void FlagsUpdated(bool forceRemove = false);
    void BuildGarrisonTalent(WorldPackets::Garrison::GarrisonTalent& result) const;

    bool operator==(Conduit const& right) const
    {
        return TalentEntryId == right.TalentEntryId && TreeEntryId == right.TreeEntryId;
    }
    bool operator!=(Conduit const& right) const { return !(*this == right); }

    bool IsEnhancedConduit();
    int32 GetSoulbindID() const;

    Player* _player;
};

class TC_GAME_API Covenant
{
    public:
        Covenant(CovenantID covId, Player* player);

        CovenantID GetCovenantID() const { return _covenantId; }
        SoulbindID GetSoulbindID() const { return _soulbindId; }
        int32 GetRenownLevel() const { return _renownLevel; }
        uint32 GetAnima() const { return _anima; }
        uint32 GetSouls() const { return _souls; }
        bool IsActiveCovenant() const;

        void SetSoulbind(SoulbindID soulbind, bool sendPacket = false);
        void SetRenown(int32 renown, bool modCurr = true);
        void SetAnima(uint32 anima, bool modCurr = true, bool inital = false);
        void SetSouls(uint32 souls, bool modCurr = true, bool inital = false);

        void AddAnima(uint32 anima);

        void InitializeCovenant();
        void UpdateRenownRewards();
        void SocketTalent(WorldPackets::Garrison::GarrisonSocketTalent& packet);

        void SaveToDB(CharacterDatabaseTransaction trans);

        std::set<uint32> _claimedRenownRewards;

        /// <summary>
        /// Use for swapping covenants
        /// </summary>
        void DisableAllConduits();
        /// <summary>
        /// Use for swapping soulbinds
        /// </summary>
        void DisableAllConduitsForSoulbind();
        /// <summary>
        /// updates all conduits use after swap covenant only
        /// </summary>
        void UpdateAllConduits();
        /// <summary>
        /// updates all conduits use after swap conduits on soulbind
        /// </summary>
        void UpdateAllConduitsForSoulbind();

        std::multimap<int32, Conduit>& GetConduits()
        {
            return _conduits;
        }

        /// <summary>
        /// Adds a conduit to the conduit map
        /// </summary>
        /// <param name="SoulbindID">what soulbind to add it to</param>
        /// <param name="conduit">reference to the conduit passed</param>
        void AddConduit(Conduit& conduit);

        /// <summary>
        /// Sets m_SaveFlags to include eCovenantSaveFlags::SaveConduits
        /// </summary>
        void SetSaveConduits();

    private:
        Player* _player;
        CovenantID _covenantId;
        SoulbindID _soulbindId;
        int32 _renownLevel;
        uint32 _anima;
        uint32 _souls;
        std::multimap<int32, Conduit> _conduits; ///< SoulbindID, Conduit
        EnumFlag<eCovenantSaveFlags> m_SaveFlags = eCovenantSaveFlags::None;
};

struct TC_GAME_API CovenantSoulbind
{
    uint32 SpecId;
    uint32 Soulbind;
};

class TC_GAME_API CovenantMgr
{
    public:
        CovenantMgr(Player* player);

        void LoadFromDB(CharacterDatabaseQueryHolder const& holder);
        void SaveToDB(CharacterDatabaseTransaction trans);
        void InitializeFields();
        void SetCovenant(CovenantID covenant);
        void LearnCovenantSpells();
        void UnlearnCovenantSpells();
        std::list<uint32> GetCovenantSpells(CovenantID covenantId = CovenantID::None);

        Covenant* GetCovenant();
        Covenant* GetCovenant(CovenantID covenant)
        {
            return _playerCovenants.at(static_cast<size_t>(covenant)).get();
        }

        void AddGarrisonInfo(WorldPackets::Garrison::GetGarrisonInfoResult & garrisonInfo);
        void LearnSoulbindConduit(Item* item);
        void LearnConduit(GarrTalentEntry const* talent, GarrTalentTreeEntry const* tree, uint32 Rank = 1);
        void BuildGarrisonPacket(WorldPackets::Garrison::GarrisonInfo& result);
        void LearnTalent(WorldPackets::Garrison::GarrisonLearnTalent& researchResult);
        Conduit* GetConduitByGarrTalentId(uint32 garrTalentId);
        void SetSoulbind(SoulbindID soulbind, bool sendPacket = false);

        // Events
        void OnSpecChange();
        void UpdateConduits(); // called when a soulbind is chosen at active covenant, or when covenant is swapped.

        static SoulbindUIDisplayInfoIds GetSoulbindUIDisplayInfoIdFromSoulbindID(SoulbindID id)
        {
            switch (id)
            {
                default:
                case SoulbindID::None                     : return SoulbindUIDisplayInfoIds::None;
                case SoulbindID::Niya                     : return SoulbindUIDisplayInfoIds::Niya;
                case SoulbindID::Dreamweaver              : return SoulbindUIDisplayInfoIds::Dreamweaver;
                case SoulbindID::GeneralDraven            : return SoulbindUIDisplayInfoIds::GeneralDraven;
                case SoulbindID::PlagueDeviserMarileth    : return SoulbindUIDisplayInfoIds::Marileth;
                case SoulbindID::Emeni                    : return SoulbindUIDisplayInfoIds::Emeni;
                case SoulbindID::Korayn                   : return SoulbindUIDisplayInfoIds::Korayn;
                case SoulbindID::Pelagos                  : return SoulbindUIDisplayInfoIds::Pelagos;
                case SoulbindID::NadjiaTheMistblade       : return SoulbindUIDisplayInfoIds::Nadjia;
                case SoulbindID::TheotarTheMadDuke        : return SoulbindUIDisplayInfoIds::Theotar;
                case SoulbindID::BonesmithHeimer          : return SoulbindUIDisplayInfoIds::Heimer;
                case SoulbindID::Kleia                    : return SoulbindUIDisplayInfoIds::Kleia;
                case SoulbindID::ForgePrimeMikanikos      : return SoulbindUIDisplayInfoIds::Mikanikos;

            }
        }

        bool _loaded = false;

        int32 GetConduitRank(int32 id) const
        {
            auto it = CollectionEntries.find(id);
            if (it != CollectionEntries.end())
                return it->second;
            return 0;
        }

    private:
        Player* _player;
        size_t _currCovenantIndex;
        std::array<std::unique_ptr<Covenant>, 5> _playerCovenants = { };
        std::unordered_map<int32, int32> CollectionEntries;
        std::unordered_multimap <int32, CovenantSoulbind> _covenantSoulbinds;
        EnumFlag<eCovenantMgrSaveFlags> m_SaveFlags = eCovenantMgrSaveFlags::None;
};
