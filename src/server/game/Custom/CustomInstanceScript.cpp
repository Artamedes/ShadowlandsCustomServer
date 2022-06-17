#include "CustomInstanceScript.h"
#include "Mail.h"
#include "CharacterDatabase.h"
#include "DatabaseEnv.h"
#include "Item.h"

// so we can load from the db
void AddSC_CustomInstanceScript()
{
    sCustomInstanceRespawn->LoadFromDB();
}

void CustomInstanceScript::Update(uint32 ms)
{
    InstanceScript::Update(ms);

    if (EnemyForcesCriteriaTreeId)
    {
        if (auto instanceScenario = instance->GetInstanceScenario())
        {
            if (CriteriaTree const* tree = sCriteriaMgr->GetCriteriaTree(EnemyForcesCriteriaTreeId))
            {
                uint64 requiredCount = tree->Entry->Amount;

                uint64 progress = 0;
                CriteriaMgr::WalkCriteriaTree(tree, [this, &progress, instanceScenario](CriteriaTree const* criteriaTree)
                {
                    auto criteriaTreeDB2 = sCriteriaTreeStore.LookupEntry(criteriaTree->ID);

                    if (criteriaTree->Criteria && criteriaTreeDB2)
                        if (CriteriaProgress const* criteriaProgress = instanceScenario->GetCriteriaProgress(criteriaTree->Criteria))
                            progress += criteriaProgress->Counter * criteriaTreeDB2->Amount;
                });

                float currentCount = 0.0f;
                if (progress >= requiredCount)
                    currentCount = 100.0f;
                else
                    currentCount = (float)progress / (float)requiredCount * 100.0f;

                if (EnemyPercentPct != currentCount)
                {
                    if (IsPrideful)
                    {
                        if (EnemyPercentPct < 20.0f && currentCount >= 20.0f)
                        {
                            SpawnPrideful();
                        }
                        if (EnemyPercentPct < 40.0f && currentCount >= 40.0f)
                        {
                            SpawnPrideful();
                        }
                        if (EnemyPercentPct < 60.0f && currentCount >= 60.0f)
                        {
                            SpawnPrideful();
                        }
                        if (EnemyPercentPct < 80.0f && currentCount >= 80.0f)
                        {
                            SpawnPrideful();
                        }
                        if (EnemyPercentPct < 100.0f && currentCount >= 100.0f)
                        {
                            SpawnPrideful();
                        }
                    }

                    //instance->DoOnPlayers([this, currentCount](Player* player)
                    //{
                    //    if (player->IsGameMaster())
                    //        ChatHandler(player).PSendSysMessage("EnemyPct %f %f", EnemyPercentPct, currentCount);
                    //});
                    EnemyPercentPct = currentCount;
                }
            }
        }
    }

    if (IsChallenge())
    {
        if (CheckCompleteTimer >= 1000)
        {
            OnCompletedCriteriaTree(nullptr);
            CheckCompleteTimer = 0;
        }
        else
            CheckCompleteTimer += ms;
    }
}

void CustomInstanceScript::OnPlayerEnter(Player* player)
{
    InstanceScript::OnPlayerEnter(player);
    ///if (player->IsGameMaster())
    ///{
    ///    ChatHandler(player).PSendSysMessage("Instance Debug:");
    ///
    ///    if (auto instScenario = instance->GetInstanceScenario())
    ///    {
    ///        for (auto criteriaProgress : instScenario->_criteriaProgress)
    ///        {
    ///            if (auto criteria = sCriteriaStore.LookupEntry(criteriaProgress.first))
    ///            {
    ///                ChatHandler(player).PSendSysMessage("%u, %u ModifierTreeId: %u", criteriaProgress.first, (uint32)criteriaProgress.second.Counter, criteria->ModifierTreeId);
    ///            }
    ///        }
    ///    }
    ///}
}

void CustomInstanceScript::OnPlayerLeave(Player* player)
{
    InstanceScript::OnPlayerLeave(player);

    if (auto chest = instance->GetGameObject(ChestGuid))
    {
        auto loot = chest->GetLootFor(player);
        if (loot && !loot->empty())
        {
            bool hasLoot = false;

            for (auto item : loot->items)
            {
                if (item.is_looted)
                    continue;

                hasLoot = true;
                break;
            }

            if (hasLoot)
            {
                MailSender sender(MAIL_CREATURE, UI64LIT(34337) /* The Postmaster */);
                MailDraft draft("Recovered Item", "You left a completed M+ without fully looting the end chest. We recovered the items for you.");
                CharacterDatabaseTransaction trans = CharacterDatabase.BeginTransaction();

                for (auto item : loot->items)
                {
                    if (item.is_looted)
                        continue;

                    if (item.type == LootItemType::Currency)
                    {
                        player->ModifyCurrency(item.itemid, item.count);
                    }
                    else if (item.type == LootItemType::Item)
                    {
                        if (Item* itemObj = Item::CreateItem(item.itemid, item.count, item.context, player))
                        {
                            itemObj->SetBonuses(item.BonusListIDs);
                            itemObj->SaveToDB(trans);
                            draft.AddItem(itemObj);
                        }
                    }
                }

                draft.SendMailTo(trans, MailReceiver(player, player->GetGUID().GetCounter()), sender);
                CharacterDatabase.CommitTransaction(trans);

                ChatHandler(player).SendSysMessage("|cff00B9FFM+ Items sent to mailbox!");
                loot->clear();
            }
        }
    }

    player->RemoveAurasDueToSpell(340880); ///< Prideful buff
}

void CustomInstanceScript::NerfLeechIfNeed(Unit* who, int32& heal)
{
    if (IsChallenge())
    {
        if (auto challenge = GetChallenge())
        {
            int32 Effectiveness = GetLeechEffectiveness(challenge->GetChallengeLevel());

            if (Effectiveness > 0 && Effectiveness < 100)
                heal *= float(Effectiveness / 100.0f);
            else if (Effectiveness < 0)
                heal = 0;
        }
    }
}

void CustomInstanceScript::OnChallengeStart()
{
    if (HasAffix(Affixes::Beguiling))
        ActivateBeguiling();

    if (HasAffix(Affixes::Prideful))
        IsPrideful = true;

    if (auto challenge = GetChallenge())
    {
        auto effectiveness = GetLeechEffectiveness(challenge->GetChallengeLevel());

        if (effectiveness != 100)
        {
            instance->DoOnPlayers([effectiveness](Player* player)
            {
                ChatHandler(player).PSendSysMessage("|cffFF0000Leech will only have %u%% effectiveness in this challenge!", effectiveness);
            });
        }
    }
}

int32 CustomInstanceScript::GetLeechEffectiveness(uint32 level) const
{
    int32 Effectiveness = 100;

    if (level >= 5)
    {
        Effectiveness -= (level - 4) * 10;
    }

    return std::max(0, Effectiveness);
}
