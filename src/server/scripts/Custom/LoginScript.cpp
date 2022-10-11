#include "Player.h"
#include "ScriptMgr.h"
#include "CovenantMgr.h"
#include "Item.h"
#include "GameTime.h"
#include "TemporarySummon.h"
#include "Chat.h"
#include "GitRevision.h"
#include "World.h"
#include "UpdateTime.h"

class LoginScript : public PlayerScript
{
    public:
        LoginScript() : PlayerScript("LoginScript") { }

        void OnCreate(Player* p_Player) override
        {
            /// @TODO: DF
            p_Player->StoreNewItemInBestSlots(184479, 1);
            p_Player->StoreNewItemInBestSlots(184479, 1);
            p_Player->StoreNewItemInBestSlots(184479, 1);
            p_Player->StoreNewItemInBestSlots(184479, 1);
            p_Player->StoreNewItemInBestSlots(184479, 1);
            p_Player->StoreNewItemInBestSlots(6948, 1);


            switch (p_Player->GetClass())
            {
                case CLASS_WARRIOR:
                {
                    p_Player->SetPrimarySpecialization(TALENT_SPEC_WARRIOR_FURY);
                    break;
                }
                case CLASS_PALADIN:
                {
                    p_Player->SetPrimarySpecialization(TALENT_SPEC_PALADIN_RETRIBUTION);
                    break;
                }
                case CLASS_HUNTER:
                {
                    p_Player->SetPrimarySpecialization(TalentSpecialization::TALENT_SPEC_HUNTER_MARKSMAN);
                    break;
                }
                case CLASS_ROGUE:
                {
                    p_Player->SetPrimarySpecialization(TalentSpecialization::TALENT_SPEC_ROGUE_ASSASSINATION);
                    break;
                }
                case CLASS_PRIEST:
                {
                    p_Player->SetPrimarySpecialization(TalentSpecialization::TALENT_SPEC_PRIEST_SHADOW);
                    break;
                }
                case CLASS_DEATH_KNIGHT:
                {
                    p_Player->SetPrimarySpecialization(TalentSpecialization::TALENT_SPEC_DEATHKNIGHT_FROST);
                    break;
                }
                case CLASS_SHAMAN:
                {
                    p_Player->SetPrimarySpecialization(TalentSpecialization::TALENT_SPEC_SHAMAN_ENHANCEMENT);
                    break;
                }
                case CLASS_MAGE:
                {
                    p_Player->SetPrimarySpecialization(TalentSpecialization::TALENT_SPEC_MAGE_FIRE);
                    break;
                }
                case CLASS_WARLOCK:
                {
                    p_Player->SetPrimarySpecialization(TalentSpecialization::TALENT_SPEC_WARLOCK_AFFLICTION);
                    break;
                }
                case CLASS_MONK:
                {
                    p_Player->SetPrimarySpecialization(TalentSpecialization::TALENT_SPEC_MONK_BATTLEDANCER);
                    break;
                }
                case CLASS_DRUID:
                {
                    p_Player->SetPrimarySpecialization(TalentSpecialization::TALENT_SPEC_DRUID_CAT);
                    break;
                }
                case CLASS_DEMON_HUNTER:
                {
                    p_Player->SetPrimarySpecialization(TalentSpecialization::TALENT_SPEC_DEMON_HUNTER_HAVOC);
                    break;
                }
            }
        }

        // Piggy
        std::unordered_map<ObjectGuid::LowType, TimePoint> m_emoteTimer;
        void OnTextEmote(Player* player, uint32 /*textEmote*/, uint32 emoteNum, ObjectGuid /*guid*/) override
        {
            if (emoteNum == 39)
            {
                auto key = player->GetGUID().GetCounter();
                auto itr = m_emoteTimer.find(key);
                auto now = GameTime::Now();
                if (itr == m_emoteTimer.end() || now > itr->second || player->IsGameMaster())
                {
                    m_emoteTimer[key] = now + 60s;
                    if (auto summ = player->SummonCreature(700018, *player, TEMPSUMMON_TIMED_DESPAWN, 5s))
                    {
                        player->PlayDistanceSound(2837);
                        summ->SetUnitFlag(UnitFlags::UNIT_FLAG_UNINTERACTIBLE);
                        summ->SetUnitFlag(UnitFlags::UNIT_FLAG_NON_ATTACKABLE);
                        summ->GetScheduler().Schedule(2s, [](TaskContext context)
                        {
                            auto summ = context.GetUnit();
                            summ->CastSpell(summ, 356777, true); // Fade out
                        });
                    }
                }
            }
        }

        void OnLogin(Player* p_Player, bool p_First) override
        {
            p_Player->SetPlayerLocalFlag(PlayerLocalFlags::PLAYER_LOCAL_FLAG_ACCOUNT_SECURED);
            if (p_First)
            {
                if (p_Player->GetRace() == RACE_WORGEN)
                {
                    p_Player->CastSpell(p_Player, 72857, true); // Two Forms
                }
                // Learn Riding
                p_Player->CastSpell(p_Player, 33389, true);
                p_Player->CastSpell(p_Player, 33392, true);
                p_Player->CastSpell(p_Player, 34092, true);
                p_Player->CastSpell(p_Player, 90266, true);
                p_Player->LearnSpell(359372, false); // mount
                p_Player->ResurrectPlayer(1.0f);
            }

            p_Player->RemoveAurasDueToSpell(141480); // Self stun
            p_Player->RemoveAurasDueToSpell(163091); // Self stun

            if (p_Player->GetQuestStatus(700036) == QUEST_STATUS_REWARDED && !p_Player->HasAchieved(700000))
            {
                if (auto achievEntry = sAchievementStore.LookupEntry(700000))
                    p_Player->CompletedAchievement(achievEntry);
            }

            ChatHandler(p_Player).PSendSysMessage("|cff62CBF5Dragonflight Beta v.%s-%s (%s branch) (%s)", GitRevision::GetCommitCount(), GitRevision::GetHash(), GitRevision::GetBranch(), GitRevision::GetPlatformStr());
            ChatHandler(p_Player).PSendSysMessage("|cff62CBF5Last update: %s", GitRevision::GetDate());
            ChatHandler(p_Player).PSendSysMessage("|cff62CBF5Uptime: %s", secsToTimeString(GameTime::GetUptime()).c_str());
            ChatHandler(p_Player).PSendSysMessage("|cff62CBF5World Diff: %ums Map Diff: %ums Average: %ums", sWorldUpdateTime.GetLastUpdateTime(), p_Player->GetMap()->LastMapDiffTime, p_Player->GetMap()->MapDiffAverage);

            // Add chisel
            if (!p_Player->HasItemCount(699998, 1))
                p_Player->AddItem(699998, 1);
        }

        void OnQuestStatusChange(Player* player, uint32 quest) override
        {
            if (quest != 700036)
                return;

            auto newStatus = player->GetQuestStatus(quest);

            if (newStatus == QUEST_STATUS_REWARDED)
            {
                player->ModifyCurrency(10186, 3);
                if (!player->HasAchieved(700000))
                    if (auto achievEntry = sAchievementStore.LookupEntry(700000))
                        player->CompletedAchievement(achievEntry);
            }
        }
};

void AddSC_LoginScript()
{
    new LoginScript();
}
