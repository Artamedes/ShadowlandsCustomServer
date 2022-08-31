#include "ScriptedCreature.h"
#include "ObjectAccessor.h"
#include "ObjectMgr.h"
#include "SceneHelper.h"
#include "MotionMaster.h"
#include "MoveSplineInit.h"
#include <G3D/Vector3.h>

void SceneActionTalk::DoAction()
{
    if (Creature* actor = GetActor())
    {
        if (Unit* target = ObjectAccessor::GetUnit(*actor, targetGuid))
            actor->AI()->Talk(talkIndex, target);
        else
            actor->AI()->Talk(talkIndex);
    }
}

void SceneActionWhisper::DoAction()
{
    if (Creature* actor = GetActor())
    {
        if (Player* player = ObjectAccessor::GetPlayer(*actor, whisperGuid))
            actor->AI()->Talk(talkIndex, player);
    }
}

void SceneActionSummon::DoAction()
{
    if (!GetActor())
        return;

    if (Map* map = GetActionMap())
    {
        map->SummonCreature(summonEntry, summonPosition);
    }
}

void SceneActionCast::DoAction()
{
    if (Creature* actor = GetActor())
    {
        actor->CastSpell(actor, spellEntry);
    }
}

void SceneActionAI::DoAction()
{
    if (Creature* actor = GetActor())
    {
        actor->AI()->DoAction(actionId);
    }
}

void SceneActionMovePos::DoAction()
{
    if (Creature* actor = GetActor())
    {
        actor->GetMotionMaster()->MovePoint(0, position);
    }
}

void SceneActionMovePath::DoAction()
{
    if (Creature* actor = GetActor())
    {
        actor->GetMotionMaster()->MovePath(pathId, false);
    }
}

void SceneActionCastTarget::DoAction()
{
    if (Creature* actor = GetActor())
    {
        if (target)
            actor->CastSpell(target, spellEntry, triggered);
    }
}

void SceneActionForceCast::DoAction()
{
    if (caster)
    {
        if (target)
            caster->CastSpell(target, spellEntry, triggered);
    }
}

void SceneActionKillCreditMonster::DoAction()
{
    if (Creature* actor = GetActor())
    {
        if (target)
        {
            if (Player* player = target->ToPlayer())
            {
                for (uint32 i = 0; i < amount; i++)
                {
                    player->KilledMonsterCredit(creditEntry);
                }
            }
        }
    }
}

void SceneActionEmote::DoAction()
{
    if (Creature* actor = GetActor())
    {
        actor->HandleEmoteCommand((Emote)emoteId);
    }
}

void SceneActionDespawn::DoAction()
{
    if (Creature* actor = GetActor())
    {
        actor->ForcedDespawn(despawnTime);
    }
}

void SceneActionFace::DoAction()
{
    if (Creature* actor = GetActor())
    {
        if (target)
            actor->SetFacingToObject(target);
    }
}

void SceneActionAddUnitFlag::DoAction()
{
    if (Creature* actor = GetActor())
    {
        actor->SetUnitFlag(UnitFlags(newFlag));
    }
}

void SceneActionRemoveUnitFlag::DoAction()
{
    if (Creature* actor = GetActor())
    {
        actor->RemoveUnitFlag(UnitFlags(oldFlag));
    }
}

void SceneActionSetReact::DoAction()
{
    if (Creature* actor = GetActor())
    {
        actor->SetReactState(reactState);
    }
}

void SceneActionActivateGobject::DoAction()
{
    if (Creature* actor = GetActor())
    {
        if (GameObject* gobject = ObjectAccessor::GetGameObject(*actor, gobjectGuid))
        {
            gobject->UseDoorOrButton(timer);
        }
    }
}

void SceneActionMoveSpline::DoAction()
{
    if (Creature* actor = GetActor())
    {
        if (speed <= 0)
            return;

        Movement::MoveSplineInit l_Init(actor);

        for (const G3D::Vector3 pos : movePositions)
            l_Init.Path().push_back(pos);

        if (flying)
            l_Init.SetFly();

        l_Init.SetSmooth();

        l_Init.SetVelocity(speed);

        l_Init.Launch();
    }
}

void SceneActionFunction::DoAction()
{
    p_Function();
}
