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

#ifndef SpellHistory_h__
#define SpellHistory_h__

#include "SharedDefines.h"
#include "DatabaseEnvFwd.h"
#include "Duration.h"
#include "GameTime.h"
#include "Optional.h"
#include <deque>
#include <vector>
#include <unordered_map>

class Item;
class Player;
class Spell;
class SpellInfo;
class Unit;

/// Spell cooldown flags sent in SMSG_SPELL_COOLDOWN
enum SpellCooldownFlags
{
    SPELL_COOLDOWN_FLAG_NONE                    = 0x0,
    SPELL_COOLDOWN_FLAG_INCLUDE_GCD             = 0x1,  ///< Starts GCD in addition to normal cooldown specified in the packet
    SPELL_COOLDOWN_FLAG_INCLUDE_EVENT_COOLDOWNS = 0x2,  ///< Starts GCD for spells that should start their cooldown on events, requires SPELL_COOLDOWN_FLAG_INCLUDE_GCD set
    SPELL_COOLDOWN_FLAG_LOSS_OF_CONTROL_UI      = 0x4,  ///< Shows interrupt cooldown in loss of control ui
    SPELL_COOLDOWN_FLAG_ON_HOLD                 = 0x8   ///< Forces cooldown to behave as if SpellInfo::IsCooldownStartedOnEvent was true
};

class TC_GAME_API SpellHistory
{
public:
    using Clock = std::chrono::system_clock;
    using Duration = Milliseconds; // Cooldowns are stored only with millisecond precision, not whatever Clock's precision is

    struct CooldownEntry
    {
        uint32 SpellId = 0;
        Clock::time_point CooldownEnd = Clock::time_point::min();
        uint32 ItemId = 0;
        uint32 CategoryId = 0;
        Clock::time_point CategoryEnd = Clock::time_point::min();
        bool OnHold = false;
    };

    struct ChargeEntry
    {
        ChargeEntry() = default;
        ChargeEntry(Clock::time_point startTime, Duration rechargeTime) : RechargeStart(startTime), RechargeEnd(startTime + rechargeTime) { }
        ChargeEntry(Clock::time_point startTime, Clock::time_point endTime) : RechargeStart(startTime), RechargeEnd(endTime) { }

        Clock::time_point RechargeStart;
        Clock::time_point RechargeEnd;
    };

    using ChargeEntryCollection = std::deque<ChargeEntry>;
    using CooldownStorageType = std::unordered_map<uint32 /*spellId*/, CooldownEntry>;
    using CategoryCooldownStorageType = std::unordered_map<uint32 /*categoryId*/, CooldownEntry*>;
    using ChargeStorageType = std::unordered_map<uint32 /*categoryId*/, ChargeEntryCollection>;
    using GlobalCooldownStorageType = std::unordered_map<uint32 /*categoryId*/, Clock::time_point>;
    typedef std::unordered_map<uint32 /*spellCastedID*/, std::list<uint32> /*spellAffectedID*/> SpellRecoveryRatesStorageType;

    explicit SpellHistory(Unit* owner);
    ~SpellHistory();

    SpellHistory(SpellHistory const&) = delete;
    SpellHistory(SpellHistory&&) = delete;

    SpellHistory& operator=(SpellHistory const&) = delete;
    SpellHistory& operator=(SpellHistory&&) = delete;

    template<class OwnerType>
    void LoadFromDB(PreparedQueryResult cooldownsResult, PreparedQueryResult chargesResult);

    template<class OwnerType>
    void SaveToDB(CharacterDatabaseTransaction trans);

    void Update();

    void HandleCooldowns(SpellInfo const* spellInfo, Item const* item, Spell* spell = nullptr);
    void HandleCooldowns(SpellInfo const* spellInfo, uint32 itemId, Spell* spell = nullptr);
    bool IsReady(SpellInfo const* spellInfo, uint32 itemId = 0) const;
    template<class PacketType>
    void WritePacket(PacketType* packet) const;

    // Cooldowns
    static Duration const InfinityCooldownDelay;  // used for set "infinity cooldowns" for spells and check

    void StartCooldownROG(SpellInfo const* spellInfo, uint32 itemId, Spell* spell = nullptr, bool onHold = false, bool forceSendPacket = false, uint32 ModCooldown = 0);
    void StartCooldown(SpellInfo const* spellInfo, uint32 itemId, Spell* spell = nullptr, bool onHold = false, Optional<Duration> forcedCooldown = {});
    void SendCooldownEvent(SpellInfo const* spellInfo, uint32 itemId = 0, Spell* spell = nullptr, bool startCooldown = true);

    void AddCooldown(uint32 spellId, uint32 itemId, Duration cooldownDuration)
    {
        Clock::time_point now = GameTime::GetTime<Clock>();
        AddCooldown(spellId, itemId, now + cooldownDuration, 0, now);
    }

    void AddCooldown(uint32 spellId, uint32 itemId, Clock::time_point cooldownEnd, uint32 categoryId, Clock::time_point categoryEnd, bool onHold = false);
    void AddSpellCooldown(uint32 spellid, uint32 itemid, uint32 cooldownEnd);
    void ModifyCooldown(uint32 spellId, int32 cooldownModMs);
    void ModifyCooldown(uint32 spellId, Duration cooldownMod, bool withoutCategoryCooldown = false);
    void ModifyCooldown(SpellInfo const* spellInfo, Duration cooldownMod, bool withoutCategoryCooldown = false);
    void ResetCooldown(uint32 spellId, bool update = false);
    void ResetCategoryCooldown(uint32 category, bool update = false);
    void ResetCooldown(CooldownStorageType::iterator& itr, bool update = false);
    template<typename Predicate>
    void ResetCooldowns(Predicate predicate, bool update = false)
    {
        std::vector<int32> resetCooldowns;
        resetCooldowns.reserve(_spellCooldowns.size());
        for (auto itr = _spellCooldowns.begin(); itr != _spellCooldowns.end();)
        {
            if (predicate(itr))
            {
                resetCooldowns.push_back(int32(itr->first));
                ResetCooldown(itr, false);
            }
            else
                ++itr;
        }

        if (update && !resetCooldowns.empty())
            SendClearCooldowns(resetCooldowns);
    }

    template<typename Predicate>
    void ReduceCooldowns(Predicate predicate, int32 time = 0)
    {
        std::vector<uint32> resetCooldowns;
        resetCooldowns.reserve(_spellCooldowns.size());

        for (auto itr = _spellCooldowns.begin(); itr != _spellCooldowns.end();)
        {
            if (predicate(itr))
            {
                resetCooldowns.push_back(itr->first);
            }
            ++itr;
        }

        for (uint32 itr : resetCooldowns)
            ModifyCooldown(itr, -time);
    }

    template<typename Predicate>
    void ReduceCategories(Predicate predicate, Duration time)
    {
        std::vector<uint32> resetCategories;
        resetCategories.reserve(_categoryCharges.size());

        for (auto itr = _categoryCharges.begin(); itr != _categoryCharges.end();)
        {
            if (predicate(itr))
            {
                resetCategories.push_back(itr->first);
            }
            ++itr;
        }

        for (uint32 itr : resetCategories)
            ModifyChargeRecoveryTime(itr, -time);
    }

    void ResetAllCooldowns();
    bool HasCooldown(SpellInfo const* spellInfo, uint32 itemId = 0) const;
    bool HasCooldown(uint32 spellId, uint32 itemId = 0) const;
    Duration GetRemainingCooldown(SpellInfo const* spellInfo) const;
    Duration GetRemainingCategoryCooldown(uint32 categoryId) const;
    Duration GetRemainingCategoryCooldown(SpellInfo const* spellInfo) const;

    // School lockouts
    void LockSpellSchool(SpellSchoolMask schoolMask, Duration lockoutTime);
    bool IsSchoolLocked(SpellSchoolMask schoolMask) const;

    // Charges
    void ForceSendSpellCharges();
    void ForceSendSpellCharge(SpellCategoryEntry const* chargeCategoryEntry);
    void ForceSendSetSpellCharges(SpellCategoryEntry const* chargeCategoryEntry);
    void UpdateCharges();
    void UpdateCharge(SpellCategoryEntry const* chargeCategoryEntry);
    void ReduceChargeCooldown(uint32 chargeCategoryId, uint32 reductionTime);
    void ReduceChargeCooldown(SpellCategoryEntry const* chargeCategoryEntry, uint32 reductionTime);
    bool ConsumeCharge(uint32 chargeCategoryId, bool withPacket = false, SpellInfo const* spellinfo = nullptr);
    int32 ConsumeAllCharges(uint32 chargeCategoryId);
    bool ResetCharges(uint32 chargeCategoryId, bool eraseCategory = true);
    void ModifyChargeRecoveryTime(uint32 chargeCategoryId, Duration cooldownMod);
    void RestoreCharge(uint32 chargeCategoryId);
    void ResetAllCharges();
    void ReduceChargeTime(uint32 chargeCategoryId, uint32 msToReduce);
    bool HasCharge(uint32 chargeCategoryId) const;
    bool HasChargeInCooldown(uint32 spellID) const;
    int32 GetChargeCount(uint32 chargeCategoryId) const;
    int32 GetMaxCharges(uint32 chargeCategoryId) const;
    int32 GetChargeRecoveryTime(uint32 chargeCategoryId, SpellInfo const* spellinfo = nullptr);
    void RecalculateSpellCategoryCharges(uint32 category);

    //Recovery Rates
    void AddSpellAffectedByRecoveryRate(uint32 spellCastedID, uint32 spellAffectedID) { SpellAffectedByRecoveryRates[spellCastedID].push_back(spellAffectedID); }
    void RemoveSpellAffectedByRecoveryRate(uint32 spellCastedID);
    bool HasSpellAffectedByRecoveryRate(uint32 spellCastedID, uint32 spellAffectedID);

    void SpellRecoveryRate(uint32 spellId, float rate);
    void ChangeRecoveryRate(uint32 chargeId, float rate);

    // Global cooldown
    bool HasGlobalCooldown(SpellInfo const* spellInfo) const;
    void AddGlobalCooldown(SpellInfo const* spellInfo, Duration duration);
    void CancelGlobalCooldown(SpellInfo const* spellInfo);

    void SaveCooldownStateBeforeDuel();
    void RestoreCooldownStateAfterDuel();

    void RemoveSpellCooldownsWithTime(uint32 minRecoveryTime);

    // COPY ON PURPOSE
    CooldownStorageType GetCooldowns()
    {
        return _spellCooldowns;
    }

    CategoryCooldownStorageType GetCategories()
    {
        return _categoryCooldowns;
    }

    ChargeStorageType GetCharges()
    {
        return _categoryCharges;
    }

private:
    Player* GetPlayerOwner() const;
    void ModifySpellCooldown(uint32 spellId, Duration cooldownMod, bool withoutCategoryCooldown = false);
    void SendClearCooldowns(std::vector<int32> const& cooldowns) const;
    CooldownStorageType::iterator EraseCooldown(CooldownStorageType::iterator itr)
    {
        _categoryCooldowns.erase(itr->second.CategoryId);
        return _spellCooldowns.erase(itr);
    }

    void SendSetSpellCharges(uint32 chargeCategoryId, ChargeEntryCollection const& chargeCollection);

    static void GetCooldownDurations(SpellInfo const* spellInfo, uint32 itemId, Duration* cooldown, uint32* categoryId, Duration* categoryCooldown);

    Unit* _owner;
    CooldownStorageType _spellCooldowns;
    CooldownStorageType _spellCooldownsBeforeDuel;
    CategoryCooldownStorageType _categoryCooldowns;
    Clock::time_point _schoolLockouts[MAX_SPELL_SCHOOL];
    ChargeStorageType _categoryCharges;
    GlobalCooldownStorageType _globalCooldowns;
    SpellRecoveryRatesStorageType SpellAffectedByRecoveryRates;

    template<class T>
    struct PersistenceHelper { };
};

#endif // SpellHistory_h__
