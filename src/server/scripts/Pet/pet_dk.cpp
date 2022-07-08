/*
 * Copyright (C) 2008-2018 TrinityCore <https://www.trinitycore.org/>
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

/*
 * Ordered alphabetically using scriptname.
 * Scriptnames of files in this file should be prefixed with "npc_pet_dk_".
 */

#include "ScriptMgr.h"
#include "CellImpl.h"
#include "CombatAI.h"
#include "GridNotifiersImpl.h"
#include "MotionMaster.h"
#include "ScriptedCreature.h"
#include "SpellInfo.h"

enum DeathKnightSpells
{
    SPELL_GARGOYLE_STRIKE                       = 51963,
    SPELL_DK_RISEN_GHOUL_SELF_STUN              = 47466,

    // Risen Skulker
    SPELL_GEN_SKELETON_SPAWN_EFFECT             = 85374,
    SPELL_DK_RAISE_SKULKER                      = 196910,
    SPELL_DK_RAISE_SKULKER_VISUAL               = 198837,
    SPELL_DK_SKULKER_SHOT                       = 212423,
};

// NPC - 27829 
class npc_pet_dk_ebon_gargoyle : public ScriptedAI
{
public:
    npc_pet_dk_ebon_gargoyle(Creature* creature) : ScriptedAI(creature) {}

    void IsSummonedBy(WorldObject* owner) override
    {
        if (!owner)
            return;

        me->SetCanFly(true);

        owner->Variables.Set<uint8>("RUNE_REST", 0);
    }

    void UpdateAI(uint32 /*diff*/) override
    {
        Unit* owner = me->GetOwner();
        if (!owner)
            return;

        if (me->IsInEvadeMode() && !owner->IsInCombat())
            return;

        Unit* target = GetTarget();
        ObjectGuid newtargetGUID = owner->GetTarget();
        if ((newtargetGUID.IsEmpty() || newtargetGUID == _targetGUID) && (target && me->IsValidAttackTarget(target)))
        {
            CastSpellOnTarget(owner, target);
            return;
        }

        if (Unit* newTarget = ObjectAccessor::GetUnit(*me, newtargetGUID))
        {
            if (target != newTarget && me->IsValidAttackTarget(newTarget) && owner->IsInCombat())

                target = newTarget;
            CastSpellOnTarget(owner, target);
            return;
        }

        EnterEvadeMode(EVADE_REASON_NO_HOSTILES);
    }

    void EnterEvadeMode(EvadeReason /*reason*/) override
    {
        if (me->IsInEvadeMode() || !me->IsAlive())
            return;

        Unit* owner = me->GetOwner();

        me->CombatStop(true);
        me->SetReactState(REACT_ASSIST);
        if (owner && !me->HasUnitState(UNIT_STATE_FOLLOW))
        {
            me->GetMotionMaster()->Clear();
            me->FollowTarget(owner);
        }
    }

private:
    Unit * GetTarget() const
    {
        return ObjectAccessor::GetUnit(*me, _targetGUID);
    }

    void CastSpellOnTarget(Unit* owner, Unit* target)
    {
        if (target && me->IsValidAttackTarget(target))
        {
            _targetGUID = target->GetGUID();
            me->SetTarget(_targetGUID);
            if (me->GetDistance(target->GetPosition()) > 40.f)
            {
                me->GetMotionMaster()->MoveChase(target);
                return;
            }
            me->CastSpell(target, SPELL_GARGOYLE_STRIKE, false);
        }
    }

    ObjectGuid _targetGUID;
};

// Risen Skulker : 99541
// Last Update 8.0.1 Build 28153
struct npc_pet_dk_risen_skulker : public ScriptedAI
{
    npc_pet_dk_risen_skulker(Creature* creature) : ScriptedAI(creature) { }

    void IsSummonedBy(WorldObject* summoner) override
    {
        Player* player = summoner->ToPlayer();
        if (!player)
            return;

        DoCastSelf(SPELL_DK_RISEN_GHOUL_SELF_STUN, true);
        DoCast(me, SPELL_DK_RAISE_SKULKER_VISUAL, true);
        DoCast(me, SPELL_GEN_SKELETON_SPAWN_EFFECT, true);
    }

    void UpdateAI(uint32 /*diff*/) override
    {
        if (!UpdateVictim())
            return;

        DoSpellAttackIfReady(SPELL_DK_SKULKER_SHOT);
    }
};

void AddSC_deathknight_pet_scripts()
{
    RegisterCreatureAI(npc_pet_dk_ebon_gargoyle);
    RegisterCreatureAI(npc_pet_dk_risen_skulker);
}
