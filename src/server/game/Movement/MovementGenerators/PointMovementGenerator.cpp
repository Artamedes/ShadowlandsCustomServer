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

#include "PointMovementGenerator.h"
#include "Creature.h"
#include "CreatureAI.h"
#include "Player.h"
#include "MotionMaster.h"
#include "MovementDefines.h"
#include "MoveSpline.h"
#include "MoveSplineInit.h"
#include "World.h"

//----- Point Movement Generator

template<class T>
PointMovementGenerator<T>::PointMovementGenerator(uint32 id, float x, float y, float z, uint32 p_MoveOptions, float speed /*= 0.0f*/, Optional<float> finalOrient /*= {}*/,
    Unit const* faceTarget /*= nullptr*/, Movement::SpellEffectExtraData const* spellEffectExtraData /*= nullptr*/)
    : _movementId(id), _destination(x, y, z), _speed(speed), moveOptions(p_MoveOptions), _finalOrient(finalOrient),
    i_faceTarget(faceTarget)
{
    this->Mode = MOTION_MODE_DEFAULT;
    this->Priority = MOTION_PRIORITY_NORMAL;
    this->Flags = MOVEMENTGENERATOR_FLAG_INITIALIZATION_PENDING;
    this->BaseUnitState = UNIT_STATE_ROAMING;

    if (spellEffectExtraData)
        this->i_spellEffectExtra = std::make_unique<Movement::SpellEffectExtraData>(*spellEffectExtraData);
}

template<class T>
MovementGeneratorType PointMovementGenerator<T>::GetMovementGeneratorType() const
{
    return POINT_MOTION_TYPE;
}

template<class T>
void PointMovementGenerator<T>::DoInitialize(T* owner)
{
    MovementGenerator::RemoveFlag(MOVEMENTGENERATOR_FLAG_INITIALIZATION_PENDING | MOVEMENTGENERATOR_FLAG_TRANSITORY | MOVEMENTGENERATOR_FLAG_DEACTIVATED);
    MovementGenerator::AddFlag(MOVEMENTGENERATOR_FLAG_INITIALIZED);

    if (_movementId == EVENT_CHARGE_PREPATH)
    {
        owner->AddUnitState(UNIT_STATE_ROAMING_MOVE);
        return;
    }

    if (owner->HasUnitState(UNIT_STATE_NOT_MOVE) || owner->IsMovementPreventedByCasting())
    {
        MovementGenerator::AddFlag(MOVEMENTGENERATOR_FLAG_INTERRUPTED);
        owner->StopMoving();
        return;
    }

    owner->AddUnitState(UNIT_STATE_ROAMING_MOVE);

    Movement::MoveSplineInit init(owner);
    init.MoveTo(_destination.GetPositionX(), _destination.GetPositionY(), _destination.GetPositionZ(), moveOptions & MOVE_PATHFINDING);

    if (moveOptions & MOVE_WALK_MODE)
        init.SetWalk(true);
    if (moveOptions & MOVE_RUN_MODE)
        init.SetWalk(false);
    if (moveOptions & MOVE_FLY_MODE)
        init.SetFly();
    if (moveOptions & MOVE_CYCLIC)
        init.SetCyclic();
    //if (moveOptions & MOVE_FALLING)
    //    init.SetFalling();
    //if (moveOptions & MOVE_FORCE_DESTINATION)
    //    init.SetForce();
    //if (moveOptions & MOVE_EXCLUDE_STEEP_SLOPES)
    //    init.SetSteep();
    //if (moveOptions & MOVE_STRAIGHT_PATH)
    //    init.SetStraight();
    if (moveOptions & MOVE_SMOOTH_PATH)
        init.SetSmooth();
    if (moveOptions & MOVE_CAN_SWIM)
        init.SetAnimation(AnimTier::Swim);
    if (moveOptions & MOVE_ANIMATION)
        init.SetAnimation(AnimTier::Hover);

    if (_speed > 0.0f)
        init.SetVelocity(_speed);
    if (i_faceTarget)
        init.SetFacing(i_faceTarget);
    if (i_spellEffectExtra)
        init.SetSpellEffectExtraData(*i_spellEffectExtra);
    if (_finalOrient)
        init.SetFacing(*_finalOrient);

    init.Launch();

    // Call for creature group update
    if (Creature* creature = owner->ToCreature())
        creature->SignalFormationMovement();
}

template<class T>
void PointMovementGenerator<T>::DoReset(T* owner)
{
    MovementGenerator::RemoveFlag(MOVEMENTGENERATOR_FLAG_TRANSITORY | MOVEMENTGENERATOR_FLAG_DEACTIVATED);

    DoInitialize(owner);
}

template<class T>
bool PointMovementGenerator<T>::DoUpdate(T* owner, uint32 /*diff*/)
{
    if (!owner)
        return false;

    if (_movementId == EVENT_CHARGE_PREPATH)
    {
        if (owner->movespline->Finalized())
        {
            MovementGenerator::AddFlag(MOVEMENTGENERATOR_FLAG_INFORM_ENABLED);
            return false;
        }
        return true;
    }

    if (owner->HasUnitState(UNIT_STATE_NOT_MOVE) || owner->IsMovementPreventedByCasting())
    {
        MovementGenerator::AddFlag(MOVEMENTGENERATOR_FLAG_INTERRUPTED);
        owner->StopMoving();
        return true;
    }

    if ((MovementGenerator::HasFlag(MOVEMENTGENERATOR_FLAG_INTERRUPTED) && owner->movespline->Finalized()) || (MovementGenerator::HasFlag(MOVEMENTGENERATOR_FLAG_SPEED_UPDATE_PENDING) && !owner->movespline->Finalized()))
    {
        MovementGenerator::RemoveFlag(MOVEMENTGENERATOR_FLAG_INTERRUPTED | MOVEMENTGENERATOR_FLAG_SPEED_UPDATE_PENDING);

        owner->AddUnitState(UNIT_STATE_ROAMING_MOVE);

        Movement::MoveSplineInit init(owner);
        init.MoveTo(_destination.GetPositionX(), _destination.GetPositionY(), _destination.GetPositionZ(), moveOptions & MOVE_PATHFINDING);

        if (moveOptions & MOVE_WALK_MODE)
            init.SetWalk(true);
        if (moveOptions & MOVE_RUN_MODE)
            init.SetWalk(false);
        if (moveOptions & MOVE_FLY_MODE)
            init.SetFly();
        if (moveOptions & MOVE_CYCLIC)
            init.SetCyclic();
        //if (moveOptions & MOVE_FALLING)
        //    init.SetFalling();
        //if (moveOptions & MOVE_FORCE_DESTINATION)
        //    init.SetForce();
        //if (moveOptions & MOVE_EXCLUDE_STEEP_SLOPES)
        //    init.SetSteep();
        //if (moveOptions & MOVE_STRAIGHT_PATH)
        //    init.SetStraight();
        if (moveOptions & MOVE_SMOOTH_PATH)
            init.SetSmooth();
        if (moveOptions & MOVE_CAN_SWIM)
            init.SetAnimation(AnimTier::Swim);
        if (moveOptions & MOVE_ANIMATION)
            init.SetAnimation(AnimTier::Hover);

        if (_speed > 0.0f)
            init.SetVelocity(_speed);
        if (i_faceTarget)
            init.SetFacing(i_faceTarget);
        if (i_spellEffectExtra)
            init.SetSpellEffectExtraData(*i_spellEffectExtra);
        if (_finalOrient)
            init.SetFacing(*_finalOrient);

        if (_speed > 0.0f) // Default value for point motion type is 0.0, if 0.0 spline will use GetSpeed on unit
            init.SetVelocity(_speed);
        init.Launch();

        // Call for creature group update
        if (Creature* creature = owner->ToCreature())
            creature->SignalFormationMovement();
    }

    if (owner->movespline->Finalized())
    {
        MovementGenerator::RemoveFlag(MOVEMENTGENERATOR_FLAG_TRANSITORY);
        MovementGenerator::AddFlag(MOVEMENTGENERATOR_FLAG_INFORM_ENABLED);
        return false;
    }
    return true;
}

template<class T>
void PointMovementGenerator<T>::DoDeactivate(T* owner)
{
    MovementGenerator::AddFlag(MOVEMENTGENERATOR_FLAG_DEACTIVATED);
    owner->ClearUnitState(UNIT_STATE_ROAMING_MOVE);
}

template<class T>
void PointMovementGenerator<T>::DoFinalize(T* owner, bool active, bool movementInform)
{
    MovementGenerator::AddFlag(MOVEMENTGENERATOR_FLAG_FINALIZED);
    if (active)
        owner->ClearUnitState(UNIT_STATE_ROAMING_MOVE);

    if (movementInform && MovementGenerator::HasFlag(MOVEMENTGENERATOR_FLAG_INFORM_ENABLED))
        MovementInform(owner);
}

template<class T>
void PointMovementGenerator<T>::MovementInform(T*) { }

template <>
void PointMovementGenerator<Creature>::MovementInform(Creature* owner)
{
    if (owner->AI())
        owner->AI()->MovementInform(POINT_MOTION_TYPE, _movementId);

    if (callbackFunc != nullptr)
        callbackFunc();

    while (!_callbacks.empty())
    {
        _callbacks.front();
        _callbacks.pop();
    }
}

template PointMovementGenerator<Player>::PointMovementGenerator(uint32, float, float, float, uint32, float, Optional<float>, Unit const*, Movement::SpellEffectExtraData const*);
template PointMovementGenerator<Creature>::PointMovementGenerator(uint32, float, float, float, uint32, float, Optional<float>, Unit const*, Movement::SpellEffectExtraData const*);
template MovementGeneratorType PointMovementGenerator<Player>::GetMovementGeneratorType() const;
template MovementGeneratorType PointMovementGenerator<Creature>::GetMovementGeneratorType() const;
template void PointMovementGenerator<Player>::DoInitialize(Player*);
template void PointMovementGenerator<Creature>::DoInitialize(Creature*);
template void PointMovementGenerator<Player>::DoReset(Player*);
template void PointMovementGenerator<Creature>::DoReset(Creature*);
template bool PointMovementGenerator<Player>::DoUpdate(Player*, uint32);
template bool PointMovementGenerator<Creature>::DoUpdate(Creature*, uint32);
template void PointMovementGenerator<Player>::DoDeactivate(Player*);
template void PointMovementGenerator<Creature>::DoDeactivate(Creature*);
template void PointMovementGenerator<Player>::DoFinalize(Player*, bool, bool);
template void PointMovementGenerator<Creature>::DoFinalize(Creature*, bool, bool);

//---- AssistanceMovementGenerator

void AssistanceMovementGenerator::Finalize(Unit* owner, bool active, bool movementInform)
{
    AddFlag(MOVEMENTGENERATOR_FLAG_FINALIZED);
    if (active)
        owner->ClearUnitState(UNIT_STATE_ROAMING_MOVE);

    if (movementInform && HasFlag(MOVEMENTGENERATOR_FLAG_INFORM_ENABLED))
    {
        Creature* ownerCreature = owner->ToCreature();
        ownerCreature->SetNoCallAssistance(false);
        ownerCreature->CallAssistance();
        if (ownerCreature->IsAlive())
            ownerCreature->GetMotionMaster()->MoveSeekAssistanceDistract(sWorld->getIntConfig(CONFIG_CREATURE_FAMILY_ASSISTANCE_DELAY));
    }
}

MovementGeneratorType AssistanceMovementGenerator::GetMovementGeneratorType() const
{
    return ASSISTANCE_MOTION_TYPE;
}
