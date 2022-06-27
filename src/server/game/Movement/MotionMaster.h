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

#ifndef MOTIONMASTER_H
#define MOTIONMASTER_H

#include "Common.h"
#include "ObjectGuid.h"
#include "Optional.h"
#include "MovementDefines.h"
#include "MovementGenerator.h"
#include "SharedDefines.h"
#include <deque>
#include <functional>
#include <set>
#include <unordered_map>
#include <vector>

class PathGenerator;
class Unit;
class GenericMovementGenerator;
struct Position;
struct SplineChainLink;
struct SplineChainResumeInfo;
struct WaypointPath;

namespace Movement
{
    class MoveSplineInit;
    struct SpellEffectExtraData;
}

enum MotionMasterFlags : uint8
{
    MOTIONMASTER_FLAG_NONE                          = 0x0,
    MOTIONMASTER_FLAG_UPDATE                        = 0x1, // Update in progress
    MOTIONMASTER_FLAG_STATIC_INITIALIZATION_PENDING = 0x2, // Static movement (MOTION_SLOT_DEFAULT) hasn't been initialized
    MOTIONMASTER_FLAG_INITIALIZATION_PENDING        = 0x4, // MotionMaster is stalled until signaled
    MOTIONMASTER_FLAG_INITIALIZING                  = 0x8, // MotionMaster is initializing

    MOTIONMASTER_FLAG_DELAYED = MOTIONMASTER_FLAG_UPDATE | MOTIONMASTER_FLAG_INITIALIZATION_PENDING
};

enum MotionMasterDelayedActionType : uint8
{
    MOTIONMASTER_DELAYED_CLEAR = 0,
    MOTIONMASTER_DELAYED_CLEAR_SLOT,
    MOTIONMASTER_DELAYED_CLEAR_MODE,
    MOTIONMASTER_DELAYED_CLEAR_PRIORITY,
    MOTIONMASTER_DELAYED_ADD,
    MOTIONMASTER_DELAYED_REMOVE,
    MOTIONMASTER_DELAYED_REMOVE_TYPE,
    MOTIONMASTER_DELAYED_INITIALIZE
};

enum MoveOptions : uint32
{
    MOVE_NONE                 = 0x000,
    MOVE_PATHFINDING          = 0x001,
    MOVE_WALK_MODE            = 0x002,
    MOVE_RUN_MODE             = 0x004,
    MOVE_FLY_MODE             = 0x008,
    MOVE_CYCLIC               = 0x010,
    MOVE_FALLING              = 0x020,
    MOVE_FORCE_DESTINATION    = 0x040,
    MOVE_EXCLUDE_STEEP_SLOPES = 0x080,
    MOVE_STRAIGHT_PATH        = 0x100,
    MOVE_SMOOTH_PATH          = 0x200,
    MOVE_CAN_SWIM             = 0x400, ///< Add spline flag: CanSwim
    MOVE_ANIMATION            = 0x800, ///< Add spline flag: Animation
};

struct MovementGeneratorDeleter
{
    void operator()(MovementGenerator* a);
};

struct MovementGeneratorComparator
{
    public:
        bool operator()(MovementGenerator const* a, MovementGenerator const* b) const;
};

struct MovementGeneratorInformation
{
    MovementGeneratorInformation(MovementGeneratorType type, ObjectGuid targetGUID, std::string const& targetName);

    MovementGeneratorType Type;
    ObjectGuid TargetGUID;
    std::string TargetName;
};

static bool EmptyValidator()
{
    return true;
}

enum class MoveTypes
{
    Forward,
    Backwards,
    Up,
    Down,
    Home,
    Ground
};

class TC_GAME_API MotionMaster
{
    public:
        typedef std::function<void()> DelayedActionDefine;
        typedef std::function<bool()> DelayedActionValidator;

        class DelayedAction
        {
            public:
                explicit DelayedAction(DelayedActionDefine&& action, DelayedActionValidator&& validator, MotionMasterDelayedActionType type) : Action(std::move(action)), Validator(std::move(validator)), Type(type) { }
                explicit DelayedAction(DelayedActionDefine&& action, MotionMasterDelayedActionType type) : Action(std::move(action)), Validator(EmptyValidator), Type(type) { }
                ~DelayedAction() { }

                void Resolve() { if (Validator()) Action(); }

                DelayedActionDefine Action;
                DelayedActionValidator Validator;
                uint8 Type;
        };

        explicit MotionMaster(Unit* unit);
        ~MotionMaster();

        void Initialize();
        void InitializeDefault();
        void AddToWorld();

        bool Empty() const;
        uint32 Size() const;
        std::vector<MovementGeneratorInformation> GetMovementGeneratorsInformation() const;
        MovementSlot GetCurrentSlot() const;
        MovementGenerator* GetCurrentMovementGenerator() const;
        MovementGeneratorType GetCurrentMovementGeneratorType() const;
        MovementGeneratorType GetCurrentMovementGeneratorType(MovementSlot slot) const;
        MovementGenerator* GetCurrentMovementGenerator(MovementSlot slot) const;
        // Returns first found MovementGenerator that matches the given criteria
        MovementGenerator* GetMovementGenerator(std::function<bool(MovementGenerator const*)> const& filter, MovementSlot slot = MOTION_SLOT_ACTIVE) const;
        bool HasMovementGenerator(std::function<bool(MovementGenerator const*)> const& filter, MovementSlot slot = MOTION_SLOT_ACTIVE) const;

        void Update(uint32 diff);
        template <class T>
        T* Add(T* movement, MovementSlot slot = MOTION_SLOT_ACTIVE);
        // NOTE: MOTION_SLOT_DEFAULT will be autofilled with IDLE_MOTION_TYPE
        void Remove(MovementGenerator* movement, MovementSlot slot = MOTION_SLOT_ACTIVE);
        // Removes first found movement
        // NOTE: MOTION_SLOT_DEFAULT will be autofilled with IDLE_MOTION_TYPE
        void Remove(MovementGeneratorType type, MovementSlot slot = MOTION_SLOT_ACTIVE);
        // NOTE: MOTION_SLOT_DEFAULT wont be affected
        void Clear();
        // Removes all movements for the given MovementSlot
        // NOTE: MOTION_SLOT_DEFAULT will be autofilled with IDLE_MOTION_TYPE
        void Clear(MovementSlot slot);
        // Removes all movements with the given MovementGeneratorMode
        // NOTE: MOTION_SLOT_DEFAULT wont be affected
        void Clear(MovementGeneratorMode mode);
        // Removes all movements with the given MovementGeneratorPriority
        // NOTE: MOTION_SLOT_DEFAULT wont be affected
        void Clear(MovementGeneratorPriority priority);
        void PropagateSpeedChange();
        bool GetDestination(float &x, float &y, float &z);
        bool StopOnDeath();

        void MoveIdle();
        void MoveTargetedHome();
        MovementGenerator* MoveTargetedHomeForce();
        void MoveRandom(float wanderDistance = 0.0f);
        void MoveFollow(Unit* target, float dist, ChaseAngle angle, MovementSlot slot = MOTION_SLOT_ACTIVE);
        void MoveChase(Unit* target, Optional<ChaseRange> dist = {}, Optional<ChaseAngle> angle = {});
        void MoveChase(Unit* target, float dist, float angle) { MoveChase(target, ChaseRange(dist), ChaseAngle(angle)); }
        void MoveChase(Unit* target, float dist) { MoveChase(target, ChaseRange(dist)); }
        void MoveConfused();
        void MoveFleeing(Unit* enemy, uint32 time = 0);
        MovementGenerator* MovePoint(uint32 id, Position const& pos, uint32 moveOptions = MoveOptions::MOVE_PATHFINDING, Optional<float> finalOrient = {});
        MovementGenerator* MovePoint(uint32 id, float x, float y, float z, uint32 moveOptions = MoveOptions::MOVE_PATHFINDING, Optional<float> finalOrient = {});
        /*
         *  Makes the unit move toward the target until it is at a certain distance from it. The unit then stops.
         *  Only works in 2D.
         *  This method doesn't account for any movement done by the target. in other words, it only works if the target is stationary.
         */
        void MoveCloserAndStop(uint32 id, Unit* target, float distance);
        // These two movement types should only be used with creatures having landing/takeoff animations
        GenericMovementGenerator* MoveLand(uint32 id, Position const& pos, Optional<float> velocity = {});
        void MoveTakeoff(uint32 id, Position const& pos, Optional<float> velocity = {});
        void MoveCharge(float x, float y, float z, float speed = SPEED_CHARGE, uint32 id = EVENT_CHARGE, bool generatePath = false, Unit const* target = nullptr, Movement::SpellEffectExtraData const* spellEffectExtraData = nullptr);
        void MoveCharge(PathGenerator const& path, float speed = SPEED_CHARGE, Unit const* target = nullptr, Movement::SpellEffectExtraData const* spellEffectExtraData = nullptr);
        void MoveKnockbackFrom(Position const& origin, float speedXY, float speedZ, Movement::SpellEffectExtraData const* spellEffectExtraData = nullptr);
        void MoveJumpTo(float angle, float speedXY, float speedZ);
        void MoveJump(Position const& pos, float speedXY, float speedZ, uint32 id = EVENT_JUMP, bool hasOrientation = false, JumpArrivalCastArgs const* arrivalCast = nullptr, Movement::SpellEffectExtraData const* spellEffectExtraData = nullptr);
        void MoveJump(float x, float y, float z, float o, float speedXY, float speedZ, uint32 id = EVENT_JUMP, bool hasOrientation = false, JumpArrivalCastArgs const* arrivalCast = nullptr, Movement::SpellEffectExtraData const* spellEffectExtraData = nullptr);
        void MoveJumpWithGravity(Position const& pos, float speedXY, float gravity, uint32 id = EVENT_JUMP, bool hasOrientation = false, JumpArrivalCastArgs const* arrivalCast = nullptr, Movement::SpellEffectExtraData const* spellEffectExtraData = nullptr);
        GenericMovementGenerator* MoveCirclePath(float x, float y, float z, float radius, bool clockwise, uint8 stepCount);
        GenericMovementGenerator* MoveSmoothPath(uint32 pointId, Position const* pathPoints, size_t pathSize, bool walk = false, bool fly = false, Optional<float> velocity = {});
        // Walk along spline chain stored in DB (script_spline_chain_meta and script_spline_chain_waypoints)
        void MoveAlongSplineChain(uint32 pointId, uint16 dbChainId, bool walk);
        void MoveAlongSplineChain(uint32 pointId, std::vector<SplineChainLink> const& chain, bool walk);
        void ResumeSplineChain(SplineChainResumeInfo const& info);
        void MoveFall(uint32 id = 0);
        void MoveSeekAssistance(float x, float y, float z);
        void MoveSeekAssistanceDistract(uint32 timer);
        void MoveTaxiFlight(uint32 path, uint32 pathnode);
        void MoveDistract(uint32 time, float orientation);
        void MovePath(uint32 pathId, bool repeatable);
        void MovePath(WaypointPath& path, bool repeatable);
        void MoveRotate(uint32 id, uint32 time, RotateDirection direction);
        void MoveFormation(Unit* leader, float range, float angle, uint32 point1, uint32 point2);

        void LaunchMoveSpline(std::function<void(Movement::MoveSplineInit& init)>&& initializer, uint32 id = 0, MovementGeneratorPriority priority = MOTION_PRIORITY_NORMAL, MovementGeneratorType type = EFFECT_MOTION_TYPE);

        MovementGenerator* Move(uint32 p_Id, MoveTypes p_MoveType, uint32 p_Options = MoveOptions::MOVE_PATHFINDING, float p_Distance = 0.0f);
    private:
        typedef std::unique_ptr<MovementGenerator, MovementGeneratorDeleter> MovementGeneratorPointer;
        typedef std::multiset<MovementGenerator*, MovementGeneratorComparator> MotionMasterContainer;
        typedef std::unordered_multimap<uint32, MovementGenerator const*> MotionMasterUnitStatesContainer;

        void AddFlag(uint8 const flag) { _flags |= flag; }
        bool HasFlag(uint8 const flag) const { return (_flags & flag) != 0; }
        void RemoveFlag(uint8 const flag) { _flags &= ~flag; }

        void ResolveDelayedActions();
        void Remove(MotionMasterContainer::iterator iterator, bool active, bool movementInform);
        void Pop(bool active, bool movementInform);
        void DirectInitialize();
        void DirectClear();
        void DirectClearDefault();
        void DirectClear(std::function<bool(MovementGenerator*)> const& filter);
        void DirectAdd(MovementGenerator* movement, MovementSlot slot);

        void Delete(MovementGenerator* movement, bool active, bool movementInform);
        void DeleteDefault(bool active, bool movementInform);
        void AddBaseUnitState(MovementGenerator const* movement);
        void ClearBaseUnitState(MovementGenerator const* movement);
        void ClearBaseUnitStates();

        Unit* _owner;
        MovementGeneratorPointer _defaultGenerator;
        MotionMasterContainer _generators;
        MotionMasterUnitStatesContainer _baseUnitStatesMap;
        std::deque<DelayedAction> _delayedActions;
        uint8 _flags;
};

#endif // MOTIONMASTER_H
