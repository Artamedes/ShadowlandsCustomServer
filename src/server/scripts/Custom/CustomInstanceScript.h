#pragma once

#include "ChallengeMode.h"
#include "ChallengeModeMgr.h"
#include "ScriptMgr.h"
#include "Player.h"
#include "InstanceScript.h"
#include "Map.h"
#include "DatabaseEnv.h"
#include "LootMgr.h"
#include "InstanceScenario.h"
#include "Chat.h"

struct CustomInstanceRespawnData
{
    uint32 CheckPoint;
    Position Pos;
};

enum SharedCustomInstanceData
{
    ShadowMilitiaRep      = 10000,
    MerchantAllianceRep   = 10002,
    LegionAssaultForceRep = 10004,
    LightBringersRep      = 10006,
    MawOppositionRep      = 10008,

    // Beguiling
    NpcEnchantedEmissary   = 155432,
    NpcVoidTouchedEmissary = 155433, // no move, immune to all cc, no reset health
    NpcEmisarryOfTheTides  = 155434, // resets health, all cc lasts max 8 seconds only, No DR
    SpellQueenDecreesBlowback   = 290027,
    SpellEnchanted              = 303632,
    SpellQueenDecreeHide        = 302420, // spell
    SpellVoidSight              = 302419,
    SpellQueenDecreeUnstoppable = 302417,
    TeleportTheEternalPalace    = 302415, // effect dummy, after cast, despawn

    // Prideful
    SpellPridefulSpawn = 340381,
    NpcPrideful = 173729,

    ActionSetActive = 1337,

    // currencies
    TransmogToken = 10181,
    PlagueSample  = 10182,
    IceFragment   = 10183,
    Gunpowder     = 10184,
    InfernalCore  = 10185,
};

class CustomInstanceRespawn
{
public:
    static CustomInstanceRespawn* instance()
    {
        static CustomInstanceRespawn instance;
        return &instance;
    }

    void LoadFromDB()
    {
        m_CustomInstanceRespawnData.clear();
        QueryResult result = WorldDatabase.Query("SELECT MapID, Checkpoint, X, Y, Z, O FROM z_custom_dungeon_respawn_checkpoints");
        if (!result)
            return;

        do
        {
            Field* fields = result->Fetch();

            CustomInstanceRespawnData data;

            data.CheckPoint = fields[1].GetUInt32();
            data.Pos = Position(fields[2].GetFloat(), fields[3].GetFloat(), fields[4].GetFloat(), fields[5].GetFloat());

            m_CustomInstanceRespawnData.insert({ fields[0].GetUInt32(), data });
        } while (result->NextRow());
    }

    CustomInstanceRespawnData const* GetRespawnData(uint32 MapId, uint32 CheckPoint)
    {
        auto itr = m_CustomInstanceRespawnData.equal_range(MapId);
        for (auto i = itr.first; i != itr.second; ++i)
        {
            if (i->second.CheckPoint == CheckPoint)
                return &i->second;
        }

        return nullptr;
    }

    std::multimap<uint32, CustomInstanceRespawnData> m_CustomInstanceRespawnData;
};

#define sCustomInstanceRespawn CustomInstanceRespawn::instance()

constexpr uint32 SetDataCheckpointId = 4000;

static void SetCheckpointId(WorldObject* obj, uint32 checkpoint)
{
    if (auto instance = obj->GetInstanceScript())
        instance->SetData(SetDataCheckpointId, checkpoint);
}

struct CustomInstanceScript : public InstanceScript
{
public:
    CustomInstanceScript(InstanceMap* map) : InstanceScript(map)
    {
    }

    bool HandlePlayerRepopRequest(Player* player) const
    {
        if (auto respawnData = sCustomInstanceRespawn->GetRespawnData(instance->GetId(), m_CheckpointId))
        {
            player->TeleportTo(WorldLocation(instance->GetId(), respawnData->Pos), TELE_REVIVE_AT_TELEPORT);
            //player->ResurrectPlayer(0.85f);
            return true;
        }

        return false;
    }

    bool HandleGetStartPosition(float& x, float& y, float& z, float& o) const
    {
        if (auto respawnData = sCustomInstanceRespawn->GetRespawnData(instance->GetId(), m_CheckpointId))
        {
            x = respawnData->Pos.GetPositionX();
            y = respawnData->Pos.GetPositionY();
            z = respawnData->Pos.GetPositionZ();
            o = respawnData->Pos.GetOrientation();
            return true;
        }

        return false;
    }

    void SetData(uint32 DataId, uint32 Value) override
    {
        if (DataId == SetDataCheckpointId)
            m_CheckpointId = Value;
    }

    void OnChallengeComplete() override
    {
        if (auto chest = instance->SummonGameObject(1200005, ChestSpawn, Quad, 0))
        {
            instance->DoOnPlayers([this, chest](Player* player)
            {
                auto loot = chest->GetLootFor(player, true);
                loot->FillLoot(GetLootIdForDungeon(), LootTemplates_Gameobject, player, true, false, chest->GetLootMode(), true, true, false, chest->GetGOInfo()->IsOploteChest());
            });

            ChestGuid = chest->GetGUID();

            chest->SetLootState(LootState::GO_ACTIVATED); // set activated
            chest->ForceUpdateFieldChange(chest->m_values.ModifyValue(&Object::m_objectData).ModifyValue(&UF::ObjectData::DynamicFlags)); // force update dynflags
        }
    }

    uint32 GetLootIdForDungeon() override
    {
        if (auto challenge = this->GetChallenge())
        {
            switch (challenge->GetChallengeLevel())
            {
                case MYTHIC_LEVEL_0:
                case MYTHIC_LEVEL_1:
                case MYTHIC_LEVEL_2:
                    return 1200005;
                case MYTHIC_LEVEL_3:
                    return 1200006;
                case MYTHIC_LEVEL_4:
                    return 1200007;
                case MYTHIC_LEVEL_5:
                    return 1200008;
                case MYTHIC_LEVEL_6:
                    return 1200009;
                case MYTHIC_LEVEL_7:
                    return 1200010;
                case MYTHIC_LEVEL_8:
                    return 1200011;
                case MYTHIC_LEVEL_9:
                    return 1200012;
                case MYTHIC_LEVEL_10:
                    return 1200013;
                case MYTHIC_LEVEL_11:
                    return 1200014;
                case MYTHIC_LEVEL_12:
                    return 1200015;
                case MYTHIC_LEVEL_13:
                    return 1200016;
                case MYTHIC_LEVEL_14:
                    return 1200017;
                case MYTHIC_LEVEL_15:
                default:
                    return 1200018;
            }
        }

        return 0;
    }

    void OnCreatureCreate(Creature* creature) override
    {
        InstanceScript::OnCreatureCreate(creature);

        switch (creature->GetEntry())
        {
            case NpcEnchantedEmissary:
                EnchantedEmissary = creature->GetGUID();
                creature->SetVisible(false);
                creature->SetReactState(REACT_PASSIVE);
                creature->SetUnitFlag(UnitFlags::UNIT_FLAG_IMMUNE_TO_PC);
                break;
            case NpcVoidTouchedEmissary:
                EmissaryOfTheTides = creature->GetGUID();
                creature->SetVisible(false);
                creature->SetReactState(REACT_PASSIVE);
                creature->SetUnitFlag(UnitFlags::UNIT_FLAG_IMMUNE_TO_PC);
                break;
            case NpcEmisarryOfTheTides:
                VoidTouchedEmissary = creature->GetGUID();
                creature->SetVisible(false);
                creature->SetReactState(REACT_PASSIVE);
                creature->SetUnitFlag(UnitFlags::UNIT_FLAG_IMMUNE_TO_PC);
                break;
        }
    }

    void OnChallengeStart() override
    {
        if (HasAffix(Affixes::Beguiling))
            ActivateBeguiling();

        if (HasAffix(Affixes::Prideful))
            IsPrideful = true;
    }

    bool HasAffix(Affixes affix)
    {
        if (auto challenge = GetChallenge())
        {
            if (challenge->HasAffix(affix))
                return true;
        }

        return false;
    }

    void ActivateBeguiling()
    {
        auto UpdateFlagsForCreature([](Creature* creature)
        {
            creature->SetVisible(true);
            creature->SetReactState(REACT_AGGRESSIVE);
            creature->RemoveUnitFlag(UnitFlags::UNIT_FLAG_IMMUNE_TO_PC);
            if (creature->AI())
                creature->AI()->DoAction(ActionSetActive);
        });

        if (auto emissary = instance->GetCreature(EnchantedEmissary))
            UpdateFlagsForCreature(emissary);
        if (auto emissary = instance->GetCreature(EmissaryOfTheTides))
            UpdateFlagsForCreature(emissary);
        if (auto emissary = instance->GetCreature(VoidTouchedEmissary))
            UpdateFlagsForCreature(emissary);
    }

    void Update(uint32 ms) override;

    Player* SelectRandomPlayerPrefNotGM()
    {
        std::list<Player*> players;
        for (MapReference const& ref : instance->GetPlayers())
            if (Player* player = ref.GetSource())
                players.push_back(player);

        Player* randPlayer = nullptr;
        Player* firstPlayer = nullptr;

        int i = 5;
        while (i > 0)
        {
            randPlayer = Trinity::Containers::SelectRandomContainerElement(players);
            if (!firstPlayer)
                firstPlayer = randPlayer;
            if (!randPlayer->IsGameMaster())
                break;

            i--;
        }

        return randPlayer ? randPlayer : firstPlayer;
    }

    void SpawnPrideful()
    {
        if (auto randPlayer = SelectRandomPlayerPrefNotGM())
        {
            randPlayer->CastSpell(randPlayer, SpellPridefulSpawn, true);
        }
    }

    void CreatureDiesForScript(Creature* creature, Unit* killer) override
    {
        InstanceScript::CreatureDiesForScript(creature, killer);

        instance->DoOnPlayers([creature](Player* player)
        {
            if (!creature->IsDungeonBoss() && creature->GetFaction() != 35)
                if (roll_chance_i(50))
                    player->ModifyCurrency(TransmogToken, urand(1, 2));
        });
    }

    void OnPlayerEnter(Player* player) override;
    void OnPlayerLeave(Player* player) override;

    // Beguiling Affix
    ObjectGuid EnchantedEmissary;
    ObjectGuid EmissaryOfTheTides;
    ObjectGuid VoidTouchedEmissary;

    /// Challenge
    float EnemyPercentPct = 0;
    uint32 EnemyForcesCriteriaTreeId = 0;
    bool IsPrideful = false;
    uint32 m_CheckpointId = 0;
    uint32 CheckCompleteTimer = 0;

    /// Challenge End Chest
    Position ChestSpawn;
    QuaternionData Quad;
    ObjectGuid ChestGuid;
};
