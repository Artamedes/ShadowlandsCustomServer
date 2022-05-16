#include "CustomInstanceScript.h"

// so we can load from the db
void AddSC_CustomInstanceScript()
{
    sCustomInstanceRespawn->LoadFromDB();
}

void CustomInstanceScript::Update(uint32 ms)
{
    if (IsPrideful && EnemyForcesCriteriaTreeId)
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

                    EnemyPercentPct = currentCount;
                }
            }
        }
    }
}
