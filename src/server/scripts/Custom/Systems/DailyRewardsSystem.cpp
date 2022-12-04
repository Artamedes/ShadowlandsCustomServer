#include "SpellMgr.h"
#include "Player.h"
#include "ScriptMgr.h"
#include "DatabaseEnv.h"
#include "GameObject.h"
#include "GameObjectAI.h"
#include "DatabaseEnv.h"
#include "ScriptedGossip.h"
#include "ObjectMgr.h"
#include "Chat.h"
#include "GameTime.h"
#include "WorldSession.h"
#include "HotfixPackets.h"
#include "World.h"
#include "Realm.h"
#include "QuestPackets.h"

constexpr uint32 DailyRewardsChoiceID = 682925853;

enum class RewardTypez : uint32
{
    Item = 0,
    Currency = 1,
};

struct Rewardz
{
public:
    RewardTypez Type;
    uint32 ObjectID;
    uint32 Count;

    void AppendToPlayerChoicePacket(WorldPackets::Quest::PlayerChoiceResponseReward& reward)
    {
        if (Type == RewardTypez::Item)
        {
            reward.Items.emplace_back();
            WorldPackets::Quest::PlayerChoiceResponseRewardEntry& rewardEntry = reward.Items.back();
            rewardEntry.Item.ItemID = ObjectID;
            rewardEntry.Quantity = Count;
        }
        else if (Type == RewardTypez::Currency)
        {
            reward.Currencies.emplace_back();
            WorldPackets::Quest::PlayerChoiceResponseRewardEntry& rewardEntry = reward.Currencies.back();
            rewardEntry.Item.ItemID = ObjectID;
            rewardEntry.Quantity = Count;
        }
    }
};

struct RewardTemplate
{
public:
    uint32 Day;
    uint32 ChoiceArtFileID;
    std::vector<Rewardz> Rewards;

    void AppendToPlayerChoicePacket(WorldPackets::Quest::PlayerChoiceResponse& playerChoiceResponse)
    {
        playerChoiceResponse.ChoiceArtFileID = ChoiceArtFileID;

        if (!Rewards.empty())
        {
            playerChoiceResponse.Reward.emplace();
            for (auto& reward : Rewards)
                reward.AppendToPlayerChoicePacket(*playerChoiceResponse.Reward);
        }
    }
};

class DailyRewards
{
public:
    static DailyRewards* instance()
    {
        static DailyRewards instance;
        return &instance;
    }

    void Load()
    {
        biggestId = 0;
        _rewardsContainer.clear();
        // z_daily_rewards
        auto result = WorldDatabase.Query("SELECT Day, ChoiceArtFileID FROM z_daily_rewards");
        if (!result)
            return;

        _rewardsContainer.reserve(result->GetRowCount());
        do
        {
            Field* fields = result->Fetch();

            RewardTemplate reward;

            reward.Day = fields[0].GetUInt32();
            reward.ChoiceArtFileID = fields[1].GetUInt32();

            _rewardsContainer[reward.Day] = reward;

            if (biggestId < reward.Day)
                biggestId = reward.Day;

        } while (result->NextRow());

        // z_daily_rewards_rewards
        auto query = WorldDatabase.Query("SELECT Day, RewardType, ObjectID, Count FROM z_daily_rewards_rewards");
        if (query)
        {
            do
            {
                auto fields = query->Fetch();

                Rewardz r;
                r.Type      = static_cast<RewardTypez>(fields[1].GetUInt32());
                r.ObjectID  = fields[2].GetUInt32();
                r.Count     = fields[3].GetUInt32();

                uint32 day   = fields[0].GetUInt32();

                auto itr = _rewardsContainer.find(day);
                if (itr != _rewardsContainer.end())
                {
                    itr->second.Rewards.push_back(r);
                }
            } while (query->NextRow());
        }
    }

    uint32 biggestId = 0;
    std::unordered_map<uint32, RewardTemplate> _rewardsContainer;

    void SendPacketToPlayer(Player* player, GameObject* go)
    {
        WorldPackets::Quest::DisplayPlayerChoice displayPlayerChoice;
        displayPlayerChoice.SenderGUID = go->GetGUID();
        displayPlayerChoice.ChoiceID = DailyRewardsChoiceID;
        displayPlayerChoice.CloseChoiceFrame = false;
        displayPlayerChoice.HideWarboardHeader = false;
        displayPlayerChoice.KeepOpenAfterChoice = false;

        displayPlayerChoice.UiTextureKitID = 5240;
        displayPlayerChoice.SoundKitID = 40319; // 80244 brwaler upgrade

        auto currDay = player->_daysLoggedIn;
        if (currDay > biggestId)
            currDay = biggestId;

        displayPlayerChoice.Question = "Rewards Chest Day: " + std::to_string(currDay);
        bool hasReward = HasRewardForPlayer(player);

        for (int i = 0; i < 2; ++i)
        {
            auto itr = _rewardsContainer.find(currDay + i);
            if (itr == _rewardsContainer.end())
                continue;

            WorldPackets::Quest::PlayerChoiceResponse playerChoiceResponse;
            playerChoiceResponse.ResponseID = 4412414;
            playerChoiceResponse.ResponseIdentifier = 335;
            playerChoiceResponse.Flags = 2;

            if (i == 0)
            {
                playerChoiceResponse.Header = "Today";
                playerChoiceResponse.ButtonTooltip = "";
                playerChoiceResponse.Confirmation = "Confirmation";
                playerChoiceResponse.Flags = !hasReward ? 5 : 0;
                playerChoiceResponse.Answer = "Claim";
                if (!hasReward)
                    playerChoiceResponse.ButtonTooltip = "You've already claimed this reward pack!";
                else
                    playerChoiceResponse.ButtonTooltip = "Click to Claim!";
                playerChoiceResponse.SubHeader = "";

            }
            else
            {
                playerChoiceResponse.Header = "Tommorow";
                playerChoiceResponse.Flags = 5; // don't allow
                playerChoiceResponse.SubHeader = "";
                playerChoiceResponse.Answer = "Login tommorow";

                time_t now = GameTime::GetGameTime();
                time_t next = sWorld->GetNextDailyQuestsResetTime();

                uint32 secondsDiff = next - now;
                uint32 hoursLeft = secondsDiff / 3600;
                uint32 minsLeft = secondsDiff / 60;

                std::ostringstream ss;

                if (hoursLeft >= 1)
                {
                    ss << "You can claim this reward in " << hoursLeft;

                    if (hoursLeft > 1)
                        ss << " hours.";
                    else
                        ss << " hour.";
                }
                else
                    ss << "You can claiam this reward in " << minsLeft << " minute(s).";

                playerChoiceResponse.ButtonTooltip = ss.str();
                playerChoiceResponse.Confirmation = "Confirmation";
            }

            itr->second.AppendToPlayerChoicePacket(playerChoiceResponse);
            displayPlayerChoice.Responses.push_back(playerChoiceResponse);
        }
        player->PlayerTalkClass->GetInteractionData().PlayerChoiceId = DailyRewardsChoiceID;
        player->SendDirectMessage(displayPlayerChoice.Write());
    }

    bool HasRewardForPlayer(Player* player) const
    {
        auto currDay = player->_daysLoggedIn;
        if (!currDay)
            return false;

        if (currDay > biggestId)
            currDay = biggestId;

        for (uint32 i = 0; i <= currDay; ++i)
        {
            if (!player->_rewardsClaimed.count(i))
                return true;
        }

        return false;
    }

    bool RewardPlayer(Player* player)
    {
        bool rewarded = false;
        auto currDay = player->_daysLoggedIn;
        if (!currDay)
            return false;

        if (currDay > biggestId)
            currDay = biggestId;

        for (uint32 i = 0; i <= currDay; ++i)
        {
            if (!player->_rewardsClaimed.count(i))
            {
                auto itr = _rewardsContainer.find(i);
                if (itr == _rewardsContainer.end())
                    continue;

                player->_rewardsClaimed.insert(i);

                for (auto reward : itr->second.Rewards)
                {
                    switch (reward.Type)
                    {
                        case RewardTypez::Item:
                            if (!player->AddItem(reward.ObjectID, reward.Count))
                                player->SendItemRetrievalMail(reward.ObjectID, reward.Count, ItemContext::NONE);
                            break;
                        case RewardTypez::Currency:
                            player->ModifyCurrency(reward.ObjectID, reward.Count);
                            break;
                    }
                }

                rewarded = true;
            }
        }

        if (rewarded)
        {
            player->SaveToDB();
            ChatHandler(player->GetSession()).SendSysMessage("|cff1DCDE5Claimed!");
            return true;
        }

        ChatHandler(player->GetSession()).SendSysMessage("No rewards to claim");
        return false;
    }
};

#define sDailyRewards DailyRewards::instance()

struct DailyRewardsSystem : public GameObjectAI
{
    public:
        DailyRewardsSystem(GameObject* object) : GameObjectAI(object) { }

        bool OnGossipHello(Player* player) override
        {
            //me->SetGoState(GOState::GO_STATE_ACTIVE);
            sDailyRewards->SendPacketToPlayer(player, me);
            return true;
        }
};

class DailyRewardsSystem_player_script : public PlayerScript
{
    public:
        DailyRewardsSystem_player_script() : PlayerScript("DailyRewardsSystem_player_script") { }

        // 719999
        void OnLogin(Player* player, bool first) override
        {
            if (first)
                return;

            auto now = GameTime::GetGameTime();
            auto diff = now - player->m_logoutTime;
            if (diff > 86400)
            {
                player->_daysLoggedIn = 0;
                player->_rewardsClaimed.clear();
                player->SaveToDB();
            }

            auto quest = sObjectMgr->GetQuestTemplate(719999);
            if (!quest)
                return;
            if (player->CanTakeQuest(quest, false) && player->CanAddQuest(quest, false))
            {
                player->AddQuestAndCheckCompletion(quest, player);
                player->RewardQuest(quest, LootItemType::Item, 0, player, false);
                player->_daysLoggedIn++;
                player->SaveToDB();
            }

            if (sDailyRewards->HasRewardForPlayer(player))
                ChatHandler(player).PSendSysMessage("|cff1DCDE5You have daily rewards available!");
        }

        void OnDailyReset(Player* player) override
        {
            auto quest = sObjectMgr->GetQuestTemplate(719999);
            if (!quest)
                return;
            if (player->CanTakeQuest(quest, false) && player->CanAddQuest(quest, false))
            {
                player->AddQuestAndCheckCompletion(quest, player);
                player->RewardQuest(quest, LootItemType::Item, 0, player, false);
                player->_daysLoggedIn++;
                player->SaveToDB();
            }

            if (sDailyRewards->HasRewardForPlayer(player))
                ChatHandler(player).PSendSysMessage("|cff1DCDE5You have daily rewards available!");
        }

        void OnPlayerChoiceResponse(Player* player, uint32 choiceId, uint32 /*responseId*/) override
        {
            // Daily rewards - DailyRewardsChoiceID
            if (choiceId == DailyRewardsChoiceID)
            {
                sDailyRewards->RewardPlayer(player);
            }
        }

};

struct npc_rewardsbot_700014 : public ScriptedAI
{
public:
    npc_rewardsbot_700014(Creature* creature) : ScriptedAI(creature) { }

    bool OnGossipHello(Player* player) override
    {
        //sDailyRewards->SendPacketToPlayer(player);
        return true;
    }
};

void AddSC_DailyRewardsSystem()
{
    sDailyRewards->Load();
    RegisterGameObjectAI(DailyRewardsSystem);
    new DailyRewardsSystem_player_script();
    RegisterCreatureAI(npc_rewardsbot_700014);
}
