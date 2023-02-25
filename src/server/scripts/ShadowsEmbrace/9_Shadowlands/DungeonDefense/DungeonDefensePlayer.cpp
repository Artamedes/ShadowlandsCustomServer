#include "DungeonDefense.h"

class DungeonDefense_PlayerScript : public PlayerScript
{
public:
    DungeonDefense_PlayerScript() : PlayerScript("DungeonDefense_PlayerScript") { }

    void OnPlayerChoiceResponse(Player* player, uint32 choiceId, uint32 /*responseId*/) override
    {
        if (choiceId == PlayerChoiceID)
        {
            if (auto instance = player->GetInstanceScript())
            {
                if (instance->GetBossState(BossCrystal) == IN_PROGRESS)
                {
                    instance->SetData(SetDataNextStage, SetDataNextStage);
                }
            }
        }
    }
};

void AddSC_DungeonDefensePlayer()
{
    new DungeonDefense_PlayerScript();
}
