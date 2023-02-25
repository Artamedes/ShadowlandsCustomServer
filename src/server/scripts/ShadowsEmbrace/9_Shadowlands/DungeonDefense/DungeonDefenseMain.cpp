
#include "DungeonDefense.h"
#include <sstream>

struct instance_darkmaul_citadel : public CustomInstanceScript
{
public:
    instance_darkmaul_citadel(InstanceMap* map) : CustomInstanceScript(map)
    {
        SetBossNumber(1);
    }

    ObjectGuid CrystalGuid;
    uint32 StartRiftEnergy = 0;
    uint32 MaxRiftEnergy = 0;
    uint32 AwardRiftEssence = 0;
    uint32 CurrentDifficulty = DifficultyEasy;
    uint32 DefensePoints = 0;
    uint32 MaxDefensePoints = 1000;

    void OnCreatureCreate(Creature* creature) override
    {
        CustomInstanceScript::OnCreatureCreate(creature);

        switch (creature->GetEntry())
        {
            case RiftCrystal:
                CrystalGuid = creature->GetGUID();
                AddObject(creature, BossCrystal, true);
                break;
        }
    }

    bool SetBossState(uint32 id, EncounterState state, bool /*forced = false*/) override
    {
        if (id == BossCrystal)
        {
            if (state == EncounterState::IN_PROGRESS)
            {
                instance->DoOnPlayers([this](Player* player)
                {
                    player->ModifyCurrency(RiftEnergy, StartRiftEnergy);
                });

                if (auto oldCrystal = instance->GetCreature(CrystalGuid))
                {
                    if (oldCrystal->AI())
                        oldCrystal->AI()->DoAction(Cleanup);
                    oldCrystal->DespawnOrUnsummon();
                }

                if (auto creature = instance->SummonCreature(RiftCrystal, CrystalSpawnPos))
                {
                    creature->SetTempSummonType(TempSummonType::TEMPSUMMON_CORPSE_DESPAWN);
                }

                if (auto creature = instance->GetCreature(CrystalGuid))
                    if (creature->AI())
                        creature->AI()->DoAction(StartEvent);
            }
            else if (state == EncounterState::DONE)
            {
                if (auto oldCrystal = instance->GetCreature(CrystalGuid))
                {
                    uint32 RewardRiftEssence = (uint32)(static_cast<float>(AwardRiftEssence) * (std::max(10.0f, oldCrystal->GetHealthPct()) / 100.0f));
                    instance->DoOnPlayers([RewardRiftEssence, oldCrystal](Player* player)
                    {
                        uint32 riftEnergy = player->GetCurrencyQuantity(RiftEnergy);
                        player->ModifyCurrency(RiftEnergy, 0);

                        ChatHandler(player).PSendSysMessage("|cffFFA600Crystal lived with %u%% HP! You've earned %u+(%u Bonus) Rift Essence!", (uint32)oldCrystal->GetHealthPct(), RewardRiftEssence, riftEnergy);
                        player->ModifyCurrency(RiftEssence, RewardRiftEssence + riftEnergy);
                    });
                }
            }
            else if (state == EncounterState::NOT_STARTED)
            {
                if (auto oldCrystal = instance->GetCreature(CrystalGuid))
                {
                    if (oldCrystal->AI())
                        oldCrystal->AI()->DoAction(Cleanup);
                    oldCrystal->DespawnOrUnsummon();
                }
            }
        }

        return InstanceScript::SetBossState(id, state, true); // force
    }

    void SetData(uint32 id, uint32 data) override
    {
        if (id == SetDataNextStage && data == SetDataNextStage)
        {
            if (auto creature = instance->GetCreature(CrystalGuid))
                if (auto ai = creature->AI())
                    ai->DoAction(StartStageOffset);
        }
        else if (id == SetMaxRiftEnergy)
        {
            MaxRiftEnergy = data;
        }
        else if (id == SetDifficulty)
        {
            CurrentDifficulty = data;
        }
        else if (id == SetStartRiftEnergy)
        {
            StartRiftEnergy = data;
        }
        else if (id == SetAwardRiftEssence)
        {
            AwardRiftEssence = data;
        }
        else if (id == SetDefensePoints)
        {
            DefensePoints = data;
        }
        else if (id == SetMaxDefensePoints)
        {
            MaxDefensePoints = data;
        }
        else if (id == SetAddDefensePoints)
        {
            DefensePoints += data;
        }
        else if (id == SetRemoveDefensePoints)
        {
            DefensePoints -= data;
        }
    }

    uint32 GetData(uint32 id) const override
    {
        if (id == DataGetMaxEnergy)
            return MaxRiftEnergy;
        else if (id == DataGetCurrentDifficulty)
            return CurrentDifficulty;
        else if (id == DataGetDefensePoints)
            return DefensePoints;
        else if (id == DataGetMaxDefensePoints)
            return MaxDefensePoints;

        return InstanceScript::GetData(id);
    }

    ObjectGuid GetGuidData(uint32 type) const override
    {
        if (type == BossCrystal)
            return CrystalGuid;

        return InstanceScript::GetGuidData(type);
    }

    void OnPlayerEnter(Player* player) override
    {
        player->ModifyCurrency(RiftEnergy, 0);
    }

    void OnPlayerLeave(Player* player) override
    {
        player->ModifyCurrency(RiftEnergy, 0);
    }
};

void AddSC_DungeonDefenseMain()
{
    sDungeonDefenseMgr->LoadFromDB();
    // InstanceScript
    RegisterInstanceScript(instance_darkmaul_citadel, DarkmaulMapId);
}
