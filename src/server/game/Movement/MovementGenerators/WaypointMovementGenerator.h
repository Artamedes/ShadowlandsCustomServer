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

#ifndef TRINITY_WAYPOINTMOVEMENTGENERATOR_H
#define TRINITY_WAYPOINTMOVEMENTGENERATOR_H

#include "MovementGenerator.h"
#include "PathMovementBase.h"
#include "Timer.h"

class Creature;
struct WaypointNode;
struct WaypointPath;

template<class T>
class WaypointMovementGenerator;

template<>
class WaypointMovementGenerator<Creature> : public MovementGeneratorMedium<Creature, WaypointMovementGenerator<Creature>>, public PathMovementBase<Creature, WaypointPath const*>
{
    public:
        explicit WaypointMovementGenerator(uint32 pathId = 0, bool repeating = true);
        explicit WaypointMovementGenerator(WaypointPath& path, bool repeating = true);
        ~WaypointMovementGenerator() { _path = nullptr; }

        MovementGeneratorType GetMovementGeneratorType() const override;

        void UnitSpeedChanged() override { AddFlag(MOVEMENTGENERATOR_FLAG_SPEED_UPDATE_PENDING); _recalculateSpeed = true; }
        void Pause(uint32 timer = 0) override;
        void Resume(uint32 overrideTimer = 0) override;
        bool GetResetPosition(Unit*, float& x, float& y, float& z) override;

        void DoInitialize(Creature*);
        void DoReset(Creature*);
        bool DoUpdate(Creature*, uint32);
        void DoDeactivate(Creature*);
        void DoFinalize(Creature*, bool, bool);

        std::string GetDebugInfo() const override;

    private:
        void ProcessWaypointArrival(Creature*, WaypointNode const&);
        void StartMove(Creature*, bool relaunch = false);
        bool IsAllowedToMove(Creature*);

        uint32 _lastSplineId;
        uint32 _pathId;
        int32 _waypointDelay;
        int32 _pauseTime;
        bool _waypointReached;
        bool _recalculateSpeed;
        bool _repeating;
        bool _loadedFromDB;
        bool _stalled;
        bool _hasBeenStalled;
        bool _done;
};

#endif
