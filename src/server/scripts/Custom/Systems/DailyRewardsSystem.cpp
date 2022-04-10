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

enum class RewardTypez : uint32
{
    Item = 0,
    Currency = 1,
};

struct Rewardz
{
    RewardTypez Type;
    uint32 ObjectID;
    uint32 Count;
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
        _rewardsContainer.clear();
        // z_daily_rewards
        auto query = WorldDatabase.Query("SELECT Day, RewardType, ObjectID, Count FROM z_daily_rewards");
        if (query)
        {
            do
            {
                auto fields = query->Fetch();

                Rewardz r;
                r.Type = static_cast<RewardTypez>(fields[1].GetUInt32());
                r.ObjectID = fields[2].GetUInt32();
                r.Count = fields[3].GetUInt32();

                uint32 id = fields[0].GetUInt32();

                _rewardsContainer.insert({ id, r });

                if (biggestId < id)
                    biggestId = id;

            } while (query->NextRow());
        }
    }

    uint32 biggestId = 0;
    std::unordered_multimap<uint32, Rewardz> _rewardsContainer;

    void RewardPlayer(Player* player)
    {
        bool rewarded = false;
        for (uint32 i = 0; i < std::min(biggestId, player->_daysLoggedIn); ++i)
        {
            if (!player->_rewardsClaimed.count(i))
            {
                player->_rewardsClaimed.insert(i);
                rewarded = true;

                auto rewardsRange = _rewardsContainer.equal_range(i);
                for (auto itr = rewardsRange.first; itr != rewardsRange.second; ++itr)
                {
                    switch (itr->second.Type)
                    {
                        case RewardTypez::Item:
                            if (!player->AddItem(itr->second.ObjectID, itr->second.Count))
                                player->SendItemRetrievalMail(itr->second.ObjectID, itr->second.Count, ItemContext::NONE);
                            break;
                        case RewardTypez::Currency:
                            player->ModifyCurrency(itr->second.ObjectID, itr->second.Count);
                            break;
                    }
                }
            }
        }
        if (rewarded)
        {
            player->SaveToDB();
        }
        else
            ChatHandler(player->GetSession()).PSendSysMessage("No rewards to claim");
    }
};

#define sDailyRewards DailyRewards::instance()

struct DailyRewardsSystem : public GameObjectAI
{
    public:
        DailyRewardsSystem(GameObject* object) : GameObjectAI(object) { }

        bool OnGossipHello(Player* player) override
        {
            ClearGossipMenuFor(player);
            AddGossipItemFor(player, GossipOptionIcon::None, "Claim rewards", 0, 0);
            SendGossipMenuFor(player, me->GetEntry(), me);
            return true;
        }

        bool OnGossipSelect(Player* player, uint32 menuId, uint32 gossipId) override
        {
            CloseGossipMenuFor(player);
            sDailyRewards->RewardPlayer(player);
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
                player->SaveToDB();
            }

            auto quest = sObjectMgr->GetQuestTemplate(719999);
            if (player->CanTakeQuest(quest, false) && player->CanAddQuest(quest, false))
            {
                player->AddQuestAndCheckCompletion(quest, player);
                player->RewardQuest(quest, LootItemType::Item, 0, player, false);
                player->_daysLoggedIn++;
                player->SaveToDB();
            }
        }

        void OnDailyReset(Player* player) override
        {
            auto quest = sObjectMgr->GetQuestTemplate(719999);
            if (player->CanTakeQuest(quest, false) && player->CanAddQuest(quest, false))
            {
                player->AddQuestAndCheckCompletion(quest, player);
                player->RewardQuest(quest, LootItemType::Item, 0, player, false);
                player->_daysLoggedIn++;
                player->SaveToDB();
            }
        }
};

struct npc_rewardsbot_700014 : public ScriptedAI
{
public:
    npc_rewardsbot_700014(Creature* creature) : ScriptedAI(creature) { }

    bool OnGossipHello(Player* player) override
    {
        auto tableHash = 35137211;
        DB2Manager::HotfixContainer container;
        DB2Manager::HotfixRecord record;
      
        record.TableHash = tableHash;
        record.RecordID = 700014;
        record.ID = {-1, 700014};
        record.HotfixStatus = DB2Manager::HotfixRecord::Status::Valid;
     //
     //   container[0].push_back(record);
     //   WorldPackets::Hotfix::AvailableHotfixes availableHotfixes(realm.Id.Realm, container);
     //   player->GetSession()->SendPacket(availableHotfixes.Write());

   //     WorldPackets::Hotfix::DBReply dbReply;
   //     dbReply.TableHash = tableHash;
   //     dbReply.RecordID = 700014;
   //
        DB2StorageBase const* store = sDB2Manager.GetStorage(tableHash);
        BroadcastTextEntry* entry = new BroadcastTextEntry();

        LocalizedString string;

        time_t const now = GameTime::GetGameTime();
        auto dailyRewardTime = sWorld->GetNextDailyQuestsResetTime();

        auto diff = dailyRewardTime - now;

        auto hours = diff / 3600;

        std::ostringstream ss;
        ss << "Hello, $n!\n";
        ss << "Your current stats are :\n";
        ss << "Logged in every day for the past : " << player->_daysLoggedIn << " Day(s).\n";
        //ss << "Current daily reward : X\n";
        ss << "Reward available in " << hours << " hours\n";

        string.Str[0] = ss.str().c_str();

        entry->ID = 700014;
        entry->Text = string;
        entry->Text1 = string;
        entry->LanguageID = 0;
        entry->ConditionID = 0;
        entry->EmotesID = 0;
        entry->Flags = 0;
        entry->ChatBubbleDurationMs = 0;
        entry->VoiceOverPriorityID = 0;
        entry->SoundKitID[0] = 0;
        entry->SoundKitID[1] = 0;
        entry->EmoteID[0] = 0;
        entry->EmoteID[1] = 0;
        entry->EmoteID[2] = 0;
        entry->EmoteDelay[0] = 0;
        entry->EmoteDelay[1] = 0;
        entry->EmoteDelay[2] = 0;

      //  dbReply.Status = DB2Manager::HotfixRecord::Status::Valid;
      //  dbReply.Timestamp = GameTime::GetGameTime();
    //    store->WriteRecord(700014, LocaleConstant::LOCALE_enUS, dbReply.Data);
      //  store->WriteRecordData(reinterpret_cast<char const*>(entry), LOCALE_enUS, dbReply.Data);

        //player->GetSession()->SendPacket(dbReply.Write());


        WorldPackets::Hotfix::HotfixConnect hotfixQueryResponse;
        hotfixQueryResponse.Hotfixes.resize(1);
        hotfixQueryResponse.Hotfixes[0].Record = record;

        std::size_t pos = hotfixQueryResponse.HotfixContent.size();
        store->WriteRecordData(reinterpret_cast<char const*>(entry), LOCALE_enUS, hotfixQueryResponse.HotfixContent);
        hotfixQueryResponse.Hotfixes[0].Size = hotfixQueryResponse.HotfixContent.size() - pos;
        player->GetSession()->SendPacket(hotfixQueryResponse.Write());

        delete entry;

        ClearGossipMenuFor(player);
        SendGossipMenuFor(player, me->GetEntry(), me);

        player->GetScheduler().Schedule(100ms, [player, this](TaskContext context)
            {
                ClearGossipMenuFor(player);
                SendGossipMenuFor(player, me->GetEntry(), me);
            });
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
