#pragma once

#include "Common.h"
#include "SharedDefines.h"
#include "DatabaseEnvFwd.h"
#include "DB2Structure.h"
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

enum GarrisonTalentFlags
{
    TalentFlagDisabled = 0x0,
    TalentFlagEnabled  = 0x1,
};

struct TC_GAME_API Conduit
{
    GarrTalentEntry const* TalentEntry;
    GarrTalentTreeEntry const* TreeEntry;

    Optional<WorldPackets::Garrison::GarrisonTalentSocketData> Socket;

    void BuildGarrisonTalent(WorldPackets::Garrison::GarrisonTalent& result);

    bool operator==(Conduit const& right) const
    {
        return TalentEntry == right.TalentEntry && TreeEntry == right.TreeEntry;
    }
    bool operator!=(Conduit const& right) const { return !(*this == right); }
};

class TC_GAME_API Covenant
{
    public:
        Covenant(CovenantID covId, Player* player);

        CovenantID GetCovenantID() const { return _covenantId; }
        SoulbindID GetSoulbindID() const { return _soulbindId; }
        int32 GetRenownLevel() const { return _renownLevel; }

        void SetSoulbind(SoulbindID soulbind);
        void SetRenown(int32 renown);
        void SetAnima(uint32 anima);
        void SetSouls(uint32 souls);

        void InitializeCovenant();
        void LearnConduit(GarrTalentEntry const* talent, GarrTalentTreeEntry const* tree);
        void BuildGarrisonPacket(WorldPackets::Garrison::GarrisonInfo& result);
        void SocketTalent(WorldPackets::Garrison::GarrisonSocketTalent& packet);
        void LearnTalent(WorldPackets::Garrison::GarrisonLearnTalent& researchResult);

    private:
        Player* _player;
        CovenantID _covenantId;
        SoulbindID _soulbindId;
        int32 _renownLevel;
        uint32 _anima;
        uint32 _souls;
        std::vector<Conduit> _conduits;
};

class TC_GAME_API CovenantMgr
{
    public:
        CovenantMgr(Player* player);

        void LoadFromDB();
        void SaveToDB(CharacterDatabaseTransaction trans);
        void InitializeFields();
        void SetCovenant(CovenantID covenant);
        void LearnCovenantSpells();
        void UnlearnCovenantSpells();
        std::list<uint32> GetCovenantSpells();

        Covenant* GetCovenant();
        Covenant* GetCovenant(CovenantID covenant)
        {
            return _playerCovenants.at(static_cast<size_t>(covenant)).get();
        }

        void AddGarrisonInfo(WorldPackets::Garrison::GetGarrisonInfoResult & garrisonInfo);
        void LearnSoulbindConduit(Item* item);
        
        SoulbindUIDisplayInfoIds GetSoulbindUIDisplayInfoIdFromSoulbindID(SoulbindID id) const
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

    private:
        Player* _player;
        size_t _currCovenantIndex;
        std::array<std::unique_ptr<Covenant>, 5> _playerCovenants = { };
        std::vector<WorldPackets::Garrison::GarrisonCollectionEntry> CollectionEntries;
};
