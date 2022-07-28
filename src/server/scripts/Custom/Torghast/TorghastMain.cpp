#include "Torghast/AnimaPower.h"
#include "TorghastDefines.h"
#include "QuestPackets.h"
#include "Player.h"
#include "GossipDef.h"

using namespace Torghast;

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

void AddSC_TorghastMain()
{
    RegisterGameObjectAI(go_plundered_anima);
}
