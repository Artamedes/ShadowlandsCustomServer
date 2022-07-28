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

    bool OnPlayerChoice(Player* player) override
    {
        if (auto choice = player->GetAnimaPowerChoice())
        {
            // send error
            //WorldPackets::Quest::DisplayPlayerChoice packet;
            //choice->BuildPacket(packet);
            //player->PlayerTalkClass->GetInteractionData().Reset();
            //player->PlayerTalkClass->GetInteractionData().PlayerChoiceId = 573;
            //player->SendDirectMessage(packet.Write());
            return true;
        }

        if (PlayerGuidSet.count(player->GetGUID()))
        {
            player->ConsumedAnimaPowers.insert(player->GetGUID());
            return true;
        }

        PlayerGuidSet.insert(player->GetGUID());
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
};

void AddSC_TorghastMain()
{
    RegisterGameObjectAI(go_plundered_anima);
}
