#include "Torghast/AnimaPower.h"
#include "TorghastDefines.h"
#include "QuestPackets.h"
#include "Player.h"
#include "MoveSpline.h"
#include "GossipDef.h"
#include "SpellScript.h"
#include "Timer.h"
#include "SpellAuraEffects.h"

using namespace Torghast;

// Used by all anima powers
struct go_plundered_anima : public GameObjectAI
{
public:
    go_plundered_anima(GameObject* go ) : GameObjectAI(go) { }

    void InitializeAI() override
    {
        me->SetAnimKitId(2664, false);
        me->SetWorldEffectID(11493);
        // 0xFFFF0000 - dyn flags
        me->SetSpawnTrackingStateAnimID(1716);
        // flags - 0x2008020
        // GO_FLAG_NODESPAWN GO_FLAG_INTERACT_DISTANCE_IGNORES_MODEL
        // unk flag 0x2000000
        me->ReplaceAllFlags(GameObjectFlags(0x2008020));
    }

    void OnAddToWorld() override
    {
        me->SetAnimKitId(2664, false);
    }

    void SetGUID(ObjectGuid const& guid, int32 action) override
    {
        if (action == 1)
        {
            PlayerGuidSet.insert(guid);
            //m_PowersPerPlayer.erase(guid);
        }
    }

    bool OnPlayerChoice(Player* player) override
    {
        if (auto choice = player->GetAnimaPowerChoice())
        {
            // send error
            if (choice->GetGameObjectGUID() == me->GetGUID())
            {
                WorldPackets::Quest::DisplayPlayerChoice packet;
                choice->BuildPacket(packet);
                player->PlayerTalkClass->GetInteractionData().Reset();
                player->PlayerTalkClass->GetInteractionData().PlayerChoiceId = 573;
                player->SendDirectMessage(packet.Write());
            }
            return true;
        }

        if (PlayerGuidSet.count(player->GetGUID()))
        {
            player->ConsumedAnimaPowers.insert(player->GetGUID());
            me->UpdateDynamicFlagsForNearbyPlayers();
            return true;
        }

        /// TODO: reimplement this better, we have to get rid of unique ptr or make a constructor for anima powers
        // player already viewed this anima before. lets set their choice
        //auto it = m_PowersPerPlayer.find(player->GetGUID());
        //if (it != m_PowersPerPlayer.end())
        //{
        //    player->SetAnimaPowerChoice(it->second);
        //    return true;
        //}
        //else
        //    m_PowersPerPlayer[player->GetGUID()] =

        player->GenerateAnimaPowerChoice(me);

        // dynflags set to 0xFFFF0010
        me->UpdateDynamicFlagsForNearbyPlayers();

        WorldPacket data(SMSG_GAME_OBJECT_SET_STATE_LOCAL, 8 + 1);
        data << me->GetGUID();
        data << uint8(0);
        player->SendDirectMessage(&data);

        return true;
    }

    GuidUnorderedSet PlayerGuidSet;
    //std::unordered_map<ObjectGuid, AnimaPowerChoice*> m_PowersPerPlayer;
};

struct npc_box_of_many_things : public ScriptedAI
{
public:
    npc_box_of_many_things(Creature* creature) : ScriptedAI(creature) { }

    bool OnGossipHello(Player* player) override
    {
        WorldPacket data(SMSG_GARRISON_OPEN_TALENT_NPC, 23);
        data << me->GetGUID();
        data << uint32(461);
        data << uint32(0);
        player->SendDirectMessage(&data);
        return true;
    }
};

struct npc_next_floor : public ScriptedAI
{
public:
    npc_next_floor(Creature* creature) : ScriptedAI(creature) { }

    bool isActive = false;

    void InitializeAI() override
    {
        switch (me->GetSpawnId())
        {
            /// Break Floors
            case 461007:
                isActive = true;
                break;
        }
    }

    void DoAction(int32 actionId) override
    {
        if (actionId == 1)
        {
            isActive = true;
        }
    }

    void MoveInLineOfSight(Unit* who) override
    {
        if (!isActive)
            return;

        if (who->IsPlayer() && who->GetDistance(me) <= 3.7f && (!who->movespline || who->movespline->Finalized()))
        {
            who->CastSpell(who, Torghast::eSpells::NextFloorBlackout, true);
            who->SetOrientation(me->GetOrientation());
            Position l_CurrentPos = *who;

            l_CurrentPos.m_positionX -= 10.0f * std::cos(l_CurrentPos.GetOrientation());
            l_CurrentPos.m_positionY -= 10.0f * std::sin(l_CurrentPos.GetOrientation());
            l_CurrentPos.SetOrientation(l_CurrentPos.GetAngle(l_CurrentPos.m_positionX, l_CurrentPos.m_positionY));
            l_CurrentPos.m_positionZ += 10.0f;

          //  who->GetMotionMaster()->MovePoint(0, l_CurrentPos, MOVE_PATHFINDING | MOVE_WALK_MODE);
        }
    }
};
/// ID: 295040 Next Floor
class spell_next_floor : public AuraScript
{
    PrepareAuraScript(spell_next_floor);

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (auto caster = GetCaster())
        {
            if (auto instance = caster->GetInstanceScript())
            {
                caster->StopMoving();
                caster->GetMotionMaster()->Clear();
                instance->SetGuidData(eDatas::GotoNextFloor, caster->GetGUID());
            }
        }
    }

    void Register() override
    {
        OnEffectRemove += AuraEffectApplyFn(spell_next_floor::HandleRemove, EFFECT_0, SPELL_AURA_SCREEN_EFFECT, AURA_EFFECT_HANDLE_REAL);
    }
};

/// ID: 311180 Defender of Torghast
class spell_defender_of_torghast : public AuraScript
{
    PrepareAuraScript(spell_defender_of_torghast);

    void HandleUpdate(uint32 diff)
    {
        _timer.Update(diff);
        if (_timer.Passed())
        {
            _timer.Reset(500ms);

            if (auto caster = GetCaster())
            {
                if (auto instanceScript = caster->GetInstanceScript())
                {
                    if (auto floor = caster->GetMap()->GetWorldStateValue(eWorldStates::CurrentFloor))
                    {
                        if (auto torghastLevel = caster->GetMap()->GetWorldStateValue(eWorldStates::TorghastLevel))
                        {
                            auto amount = 15.0f * floor;

                            AddPct(amount, torghastLevel * 20);

                            /// Health
                            if (auto eff = GetEffect(EFFECT_0))
                                if (eff->GetAmount() != amount)
                                    eff->ChangeAmount(amount);

                            /// Dmg
                            if (auto eff = GetEffect(EFFECT_1))
                                if (eff->GetAmount() != amount)
                                    eff->ChangeAmount(amount);
                        }
                    }
                }
            }
        }
    }

    TimeTracker _timer;

    void Register() override
    {
        OnAuraUpdate += AuraUpdateFn(spell_defender_of_torghast::HandleUpdate);
    }
};

void AddSC_TorghastMain()
{
    RegisterGameObjectAI(go_plundered_anima);
    RegisterCreatureAI(npc_box_of_many_things);
    RegisterCreatureAI(npc_next_floor);

    RegisterSpellScript(spell_next_floor);
    RegisterSpellScript(spell_defender_of_torghast);
}
