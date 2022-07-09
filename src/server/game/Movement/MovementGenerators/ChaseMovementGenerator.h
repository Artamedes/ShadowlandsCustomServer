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

#ifndef TRINITY_CHASEMOVEMENTGENERATOR_H
#define TRINITY_CHASEMOVEMENTGENERATOR_H

#include "MovementDefines.h"
#include "AbstractPursuer.h"
#include "MovementGenerator.h"
#include "Optional.h"
#include "Position.h"
#include "Timer.h"

class PathGenerator;
class Unit;

class ChaseMovementGenerator : public MovementGenerator, public AbstractPursuer
{
    public:
        explicit ChaseMovementGenerator(Unit* target, float range = {}, Optional<ChaseAngle> angle = {});
        ~ChaseMovementGenerator();

        void Initialize(Unit*) override;
        void Reset(Unit*) override;
        bool Update(Unit*, uint32) override;
        void Deactivate(Unit*) override;
        void Finalize(Unit*, bool, bool) override;
        MovementGeneratorType GetMovementGeneratorType() const override { return CHASE_MOTION_TYPE; }

        void UnitSpeedChanged() override { _lastTargetPosition.reset(); }

    private:
        void LaunchMovement(Unit* owner, float chaseRange, bool backward = false, bool mutualChase = false);

        static constexpr uint32 CHASE_MOVEMENT_INTERVAL = 400; // sniffed value (1 batch update cyclice)
        static constexpr uint32 REPOSITION_MOVEMENT_INTERVAL = 1200; // (3 batch update cycles) TODO: verify

        TimeTracker _nextMovementTimer;
        TimeTracker _nextRepositioningTimer;

        Optional<Position> _lastTargetPosition;
        float const _range;
        Optional<ChaseAngle> const _angle;
};

#endif
