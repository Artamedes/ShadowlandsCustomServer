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

#ifndef TRINITY_SCRIPTEDCREATURE_H
#define TRINITY_SCRIPTEDCREATURE_H

#include "CreatureAI.h"
#include "Creature.h"  // convenience include for scripts, all uses of ScriptedCreature also need Creature (except ScriptedCreature itself doesn't need Creature)
#include "DBCEnums.h"
#include "EventMap.h"
#include "TaskScheduler.h"

enum SelectTargetType : uint8;
enum SelectEffect : uint8;

class TC_GAME_API EntryCheckPredicate
{
    public:
        EntryCheckPredicate(uint32 entry) : _entry(entry) { }
        bool operator()(ObjectGuid const& guid) const { return guid.GetEntry() == _entry; }

    private:
        uint32 _entry;
};

class TC_GAME_API DummyEntryCheckPredicate
{
    public:
        bool operator()(ObjectGuid const&) const { return true; }
};

struct TC_GAME_API ScriptedAI : public CreatureAI
{
    public:
        explicit ScriptedAI(Creature* creature);
        explicit ScriptedAI(Creature* creature, uint32 scriptId);
        virtual ~ScriptedAI() { }

        // *************
        // CreatureAI Functions
        // *************

        void AttackStartNoMove(Unit* target);

        // Called at World update tick
        virtual void UpdateAI(uint32 diff) override;

        // *************
        // Variables
        // *************

        // For fleeing
        bool IsFleeing;

        // *************
        // Pure virtual functions
        // *************

        // Called before JustEngagedWith even before the creature is in combat.
        void AttackStart(Unit* /*target*/) override;

        // *************
        // AI Helper Functions
        // *************

        // Start movement toward victim
        void DoStartMovement(Unit* target, float distance = 0.0f, float angle = 0.0f);

        // Start no movement on victim
        void DoStartNoMovement(Unit* target);

        // Stop attack of current victim
        void DoStopAttack();

        // Cast spell by spell info
        void DoCastSpell(Unit* target, SpellInfo const* spellInfo, bool triggered = false);

        // Plays a sound to all nearby players
        void DoPlaySoundToSet(WorldObject* source, uint32 soundId);

        // Add specified amount of threat directly to victim (ignores redirection effects) - also puts victim in combat and engages them if necessary
        void AddThreat(Unit* victim, float amount, Unit* who = nullptr);
        // Adds/removes the specified percentage from the specified victim's threat (to who, or me if not specified)
        void ModifyThreatByPercent(Unit* victim, int32 pct, Unit* who = nullptr);
        // Resets the victim's threat level to who (or me if not specified) to zero
        void ResetThreat(Unit* victim, Unit* who = nullptr);
        // Resets the specified unit's threat list (me if not specified) - does not delete entries, just sets their threat to zero
        void ResetThreatList(Unit* who = nullptr);
        // Returns the threat level of victim towards who (or me if not specified)
        float GetThreat(Unit const* victim, Unit const* who = nullptr);
        // Stops combat, ignoring restrictions, for the given creature
        void ForceCombatStop(Creature* who, bool reset = true);
        // Stops combat, ignoring restrictions, for the found creatures
        void ForceCombatStopForCreatureEntry(uint32 entry, float maxSearchRange = 250.0f, bool samePhase = true, bool reset = true);
        // Stops combat, ignoring restrictions, for the found creatures
        void ForceCombatStopForCreatureEntry(std::vector<uint32> creatureEntries, float maxSearchRange = 250.0f, bool samePhase = true, bool reset = true);

        void DoTeleportTo(float x, float y, float z, uint32 time = 0);
        void DoTeleportTo(float const pos[4]);

        // Teleports a player without dropping threat (only teleports to same map)
        void DoTeleportPlayer(Unit* unit, float x, float y, float z, float o);
        void DoTeleportAll(float x, float y, float z, float o);

        // Returns friendly unit with the most amount of hp missing from max hp
        Unit* DoSelectLowestHpFriendly(float range, uint32 minHPDiff = 1);

        // Returns friendly unit with hp pct below specified and with specified entry
        Unit* DoSelectBelowHpPctFriendlyWithEntry(uint32 entry, float range, uint8 hpPct = 1, bool excludeSelf = true);

        // Returns a list of friendly CC'd units within range
        std::list<Creature*> DoFindFriendlyCC(float range);

        // Returns a list of all friendly units missing a specific buff within range
        std::list<Creature*> DoFindFriendlyMissingBuff(float range, uint32 spellId);

        // Return a player with at least minimumRange from me
        Player* GetPlayerAtMinimumRange(float minRange);

        // Spawns a creature relative to me
        Creature* DoSpawnCreature(uint32 entry, float offsetX, float offsetY, float offsetZ, float angle, uint32 type, Milliseconds despawntime);

        bool HealthBelowPct(uint32 pct) const;
        bool HealthAbovePct(uint32 pct) const;

        // Returns spells that meet the specified criteria from the creatures spell list
        SpellInfo const* SelectSpell(Unit* target, uint32 school, uint32 mechanic, SelectTargetType targets, float rangeMin, float rangeMax, SelectEffect effect);

        void SetEquipmentSlots(bool loadDefault, int32 mainHand = EQUIP_NO_CHANGE, int32 offHand = EQUIP_NO_CHANGE, int32 ranged = EQUIP_NO_CHANGE);

        // Used to control if MoveChase() is to be used or not in AttackStart(). Some creatures does not chase victims
        // NOTE: If you use SetCombatMovement while the creature is in combat, it will do NOTHING - This only affects AttackStart
        //       You should make the necessary to make it happen so.
        //       Remember that if you modified _isCombatMovementAllowed (e.g: using SetCombatMovement) it will not be reset at Reset().
        //       It will keep the last value you set.
        void SetCombatMovement(bool allowMovement);
        bool IsCombatMovementAllowed() const { return _isCombatMovementAllowed; }

        void ApplyAllImmunities(bool apply);

        virtual void DamageDealt(Unit* /*victim*/, uint32& /*damage*/, DamageEffectType /*damageType*/, SpellInfo const* /*spellInfo = nullptr*/);

        // return true for heroic mode. i.e.
        //   - for dungeon in mode 10-heroic,
        //   - for raid in mode 10-Heroic
        //   - for raid in mode 25-heroic
        // DO NOT USE to check raid in mode 25-normal.
        bool IsHeroic() const { return _isHeroic; }

        // return the dungeon or raid difficulty
        Difficulty GetDifficulty() const { return _difficulty; }

        // return true for 25 man or 25 man heroic mode
        bool Is25ManRaid() const { return _difficulty == DIFFICULTY_25_N || _difficulty == DIFFICULTY_25_HC; }
        bool IsChallengeMode() const { return _difficulty == DIFFICULTY_MYTHIC_KEYSTONE; }
        bool IsMythic() const { return _difficulty == DIFFICULTY_MYTHIC_KEYSTONE || _difficulty == DIFFICULTY_MYTHIC; }

        template <class T>
        inline T const& DUNGEON_MODE(T const& normal5, T const& heroic10) const
        {
            switch (_difficulty)
            {
                case DIFFICULTY_NORMAL:
                    return normal5;
                case DIFFICULTY_HEROIC:
                    return heroic10;
                default:
                    break;
            }

            return heroic10;
        }

        template <class T>
        inline T const& RAID_MODE(T const& normal10, T const& normal25) const
        {
            switch (_difficulty)
            {
                case DIFFICULTY_10_N:
                    return normal10;
                case DIFFICULTY_25_N:
                    return normal25;
                default:
                    break;
            }

            return normal25;
        }

        template <class T>
        inline T const& RAID_MODE(T const& normal10, T const& normal25, T const& heroic10, T const& heroic25) const
        {
            switch (_difficulty)
            {
                case DIFFICULTY_10_N:
                    return normal10;
                case DIFFICULTY_25_N:
                    return normal25;
                case DIFFICULTY_10_HC:
                    return heroic10;
                case DIFFICULTY_25_HC:
                    return heroic25;
                default:
                    break;
            }

            return heroic25;
        }

    private:
        Difficulty _difficulty;
        bool _isCombatMovementAllowed;
        bool _isHeroic;
};

class TC_GAME_API BossAI : public ScriptedAI
{
    public:
        BossAI(Creature* creature, uint32 bossId);
        virtual ~BossAI() { }

        void JustSummoned(Creature* summon) override;
        void SummonedCreatureDespawn(Creature* summon) override;

        virtual void UpdateAI(uint32 diff) override;

        // Hook used to execute events scheduled into EventMap without the need
        // to override UpdateAI
        // note: You must re-schedule the event within this method if the event
        // is supposed to run more than once
        virtual void ExecuteEvent(uint32 /*eventId*/) { }

        virtual void ScheduleTasks() { }

        void InitializeAI() override { _InitializeAI(); }
        void Reset() override { _Reset(); }
        void JustEngagedWith(Unit* who) override { _JustEngagedWith(who); }
        void JustDied(Unit* /*killer*/) override { _JustDied(); }
        void JustReachedHome() override { _JustReachedHome(); }

        bool CanAIAttack(Unit const* target) const override;

    protected:
        void _InitializeAI();
        void _Reset();
        void _JustEngagedWith(Unit* who);
        void _JustDied();
        void _JustReachedHome();
        void _DespawnAtEvade(Seconds delayToRespawn = 30s, Creature* who = nullptr);

        void TeleportCheaters();

    private:
        uint32 const _bossId;
};

class TC_GAME_API WorldBossAI : public ScriptedAI
{
    public:
        WorldBossAI(Creature* creature);
        virtual ~WorldBossAI() { }

        void JustSummoned(Creature* summon) override;
        void SummonedCreatureDespawn(Creature* summon) override;

        virtual void UpdateAI(uint32 diff) override;

        // Hook used to execute events scheduled into EventMap without the need
        // to override UpdateAI
        // note: You must re-schedule the event within this method if the event
        // is supposed to run more than once
        virtual void ExecuteEvent(uint32 /*eventId*/) { }

        void Reset() override { _Reset(); }
        void JustEngagedWith(Unit* /*who*/) override { _JustEngagedWith(); }
        void JustDied(Unit* /*killer*/) override { _JustDied(); }

    protected:
        void _Reset();
        void _JustEngagedWith();
        void _JustDied();

        EventMap events;
        SummonList summons;
};

// SD2 grid searchers.
inline Creature* GetClosestCreatureWithEntry(WorldObject* source, uint32 entry, float maxSearchRange, bool alive = true)
{
    return source->FindNearestCreature(entry, maxSearchRange, alive);
}

inline GameObject* GetClosestGameObjectWithEntry(WorldObject* source, uint32 entry, float maxSearchRange, bool spawnedOnly = true)
{
    return source->FindNearestGameObject(entry, maxSearchRange, spawnedOnly);
}

template <typename Container>
inline void GetCreatureListWithEntryInGrid(Container& container, WorldObject* source, uint32 entry, float maxSearchRange)
{
    source->GetCreatureListWithEntryInGrid(container, entry, maxSearchRange);
}

template <typename Container>
inline void GetGameObjectListWithEntryInGrid(Container& container, WorldObject* source, uint32 entry, float maxSearchRange)
{
    source->GetGameObjectListWithEntryInGrid(container, entry, maxSearchRange);
}

template <typename Container>
inline void GetPlayerListInGrid(Container& container, WorldObject* source, float maxSearchRange, bool alive = true)
{
    source->GetPlayerListInGrid(container, maxSearchRange, alive);
}

TC_GAME_API void GetPositionWithDistInOrientation(Position* pUnit, float dist, float orientation, float& x, float& y);
TC_GAME_API void GetPositionWithDistInOrientation(Position* fromPos, float dist, float orientation, Position& movePosition);

TC_GAME_API void GetRandPosFromCenterInDist(float centerX, float centerY, float dist, float& x, float& y);
TC_GAME_API void GetRandPosFromCenterInDist(Position* centerPos, float dist, Position& movePosition);

TC_GAME_API void GetPositionWithDistInFront(Position* centerPos, float dist, Position& movePosition);

#endif // TRINITY_SCRIPTEDCREATURE_H
