#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "WorldSession.h"
#include "QuestPackets.h"
#include "../CustomInstanceScript.h"
#include "GossipDef.h"
#include "ScriptedGossip.h"
#include "TemporarySummon.h"
#include "Player.h"
#include "MotionMaster.h"
#include "Item.h"
#include "CellImpl.h"
#include "Cell.h"
#include "GridNotifiers.h"
#include "MoveSpline.h"
#include "ObjectMgr.h"
#include "Chat.h"
#include <sstream>

enum DarkmaulCitadel
{
    BossCrystal = 0,

    // Enemies
    Goblin     = 860000,
    Kobold     = 860001,
    Orc        = 860002,
    OrcBruiser = 860003,
    Beholder   = 860004,
    Ogre       = 860005,
    GoblinChef = 860007,

    // Friendlies
    RiftCrystal = 851000,
    // Summons
    Archer          = 851001,
    FireWizard      = 851002,
    Cannon          = 851003,
    FriendlyOgre    = 851007,
    TauntTotem      = 851004,
    SlowTotem       = 851006, // don't attack
    BombTotem       = 851005, // don't attack

    // Actions
    StartEventEASY = 1,
    Cleanup,
    StartStageOffset = 1000,
    LeftWaypoints = 2000,
    RightWaypoints = 2001,
    // Creature set data
    SetRiftEnergy = 3000,

    // Instance Set Data
    SetDataNextStage = 1337,
    SetMaxRiftEnergy,
    // Instance Get Data
    DataGetMaxEnergy = 5000,

    // PlayerChoice
    PlayerChoiceID = 682925854,

    // MapId
    DarkmaulMapId = 2236,

    // Spells
    CannonFireBall = 329420,
    Pyroblast = 147600,

    // Currencies
    RiftEssence       = 10177,
    AllotedRiftEnergy = 10178, // useless
    RiftEnergy        = 10179, // per instance currency
    DefensePoints     = 10180,

    // Broadcasts
    DefenderNpcTextId           = 851001,
    DungeonDefenseItemNpcTextId = 699999,

    // Temporary
    MaxRiftEnergyEasyMode = 500,
    RiftEssenceReward = 5000,
};

const std::unordered_map<uint32, uint32> CreatureHealths =
{
    // Enemies
    { Goblin,       200  },
    { Kobold,       200  },
    { Orc,          500  },
    { OrcBruiser,   850  },
    { Beholder,     1000 },
    { Ogre,         1750 },
    { GoblinChef,   400  },

    // Friendlies
    { RiftCrystal,  5000 },
    { Cannon,       100  },
    { FireWizard,   200  },
    { Archer,       250  },
    { FriendlyOgre, 2000 },
    { SlowTotem,    100  },
    { BombTotem,    500  },
    { TauntTotem,   1000 },

};

const std::unordered_map<uint32, float> CreatureDmgs =
{
    // Enemies
    { Goblin,       20.0f },
    { Kobold,       20.0f },
    { Orc,          50.0f },
    { OrcBruiser,   85.0f },
    { Beholder,     100.0f },
    { Ogre,         175.0f },
    { GoblinChef,   40.0f },

    // Friendlies
    { RiftCrystal,  500.0f  },
    { Cannon,       200.0f  },
    { FireWizard,   100.0f  },
    { Archer,       100.0f  },
    { FriendlyOgre, 225.0f  },
    { SlowTotem,    0.0f    },
    { BombTotem,    300.0f  },
    { TauntTotem,   0.0f    },
};

const std::unordered_map<uint32, uint32> CreatureRiftEnergyCosts
{
    // Friendlies
    { Cannon,       100  },
    { FireWizard,   75   },
    { Archer,       50   },
    { FriendlyOgre, 150  },
    { SlowTotem,    75   },
    { BombTotem,    75   },
    { TauntTotem,   75   },
};

const std::unordered_map<uint32, uint32> CreatureRiftEnergyReward
{
    { Kobold,       8  },
    { Goblin,       16 },
    { GoblinChef,   24 },
    { Orc,          30 },
    { OrcBruiser,   50 },
    { Beholder,     60 },
    { Ogre,         90 },
};

const Position CrystalSpawnPos = { 872.208f, -1877.28f, 207.632f, 2.08771f };
const Position EnemySpawnPos = { 913.561f, -1762.8f, 181.191f, 3.69085f };

const Position EnemyPointOne = { 886.193f, -1779.7f, 181.419f, 3.74321f };
const Position EnemyPointTwo = { 849.567f, -1808.24f, 181.49f, 4.28971f };
const Position EnemyPointThree = { 857.928f, -1850.06f, 184.705f, 5.22565f };

const Position EnemyPointRightOne = { 832.571f, -1901.04f, 196.241f, 5.03912f }; // right one
const Position EnemyPointRightTwo = { 865.323f, -1881.52f, 207.745f, 0.562353f }; // right two

const Position EnemyPointLeftOne = { 916.215f, -1854.46f, 196.256f, 2.75493f }; // left one
const Position EnemyPointLeftTwo = { 877.948f, -1873.99f, 207.624f, 3.69086f }; // left two

void GiveRiftEnergyToPlayer(Player* player, uint32 reward)
{
    auto instance = player->GetInstanceScript();
    uint32 currCurrency = player->GetCurrency(RiftEnergy);
    uint32 maxCurrency = instance->GetData(DataGetMaxEnergy);
    if (currCurrency <= maxCurrency)
    {
        if (currCurrency + reward > maxCurrency)
        {
            uint32 prevReward = reward;
            reward = maxCurrency - currCurrency;
            uint32 diff = prevReward - reward;
            player->ModifyCurrency(RiftEssence, diff);
        }

        player->ModifyCurrency(RiftEnergy, reward);
    }
}

struct instance_darkmaul_citadel : public CustomInstanceScript
{
public:
    instance_darkmaul_citadel(InstanceMap* map) : CustomInstanceScript(map)
    {
        SetBossNumber(1);
    }

    ObjectGuid CrystalGuid;
    uint32 MaxRiftEnergy = MaxRiftEnergyEasyMode;

    void Load(char const* /*data*/) override
    {

    }

    void SaveToDB() override
    {

    }

    void OnCreatureCreate(Creature* creature) override
    {
        InstanceScript::OnCreatureCreate(creature);

        switch (creature->GetEntry())
        {
            case RiftCrystal:
                CrystalGuid = creature->GetGUID();
                AddObject(creature, BossCrystal, true);
                break;
        }
    }

    bool SetBossState(uint32 id, EncounterState state) override
    {
        if (id == BossCrystal)
        {
            if (state == EncounterState::IN_PROGRESS)
            {
                instance->DoOnPlayers([](Player* player)
                {
                    player->ModifyCurrency(RiftEnergy, MaxRiftEnergyEasyMode, true, false, true);
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
                        creature->AI()->DoAction(StartEventEASY);
            }
            else if (state == EncounterState::DONE)
            {
                if (auto oldCrystal = instance->GetCreature(CrystalGuid))
                {
                    uint32 RewardRiftEssence = (uint32)(static_cast<float>(RiftEssenceReward) * (std::min(10.0f, oldCrystal->GetHealthPct()) / 100.0f));
                    instance->DoOnPlayers([RewardRiftEssence, oldCrystal](Player* player)
                    {
                        uint32 riftEnergy = player->GetCurrency(RiftEnergy);
                        player->ModifyCurrency(RiftEnergy, 0, true, false, true);

                        ChatHandler(player).PSendSysMessage("|cffFFA600Crystal lived with %u%% HP! You've earned %u+(%u Bonus) Rift Essence!", (uint32)oldCrystal->GetHealthPct(), RewardRiftEssence, riftEnergy);
                        player->ModifyCurrency(RiftEssence, RewardRiftEssence + riftEnergy);
                    });
                }
            }
        }

        return InstanceScript::SetBossState(id, state);
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
    }

    uint32 GetData(uint32 id) const override
    {
        if (id == DataGetMaxEnergy)
            return MaxRiftEnergy;

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
        player->ModifyCurrency(RiftEnergy, 0, true, false, true);
    }

    void OnPlayerLeave(Player* player) override
    {
        player->ModifyCurrency(RiftEnergy, 0, true, false, true);
    }
};

class EnemyTargeterCheck
{
public:
    explicit EnemyTargeterCheck(Creature const* creature, float range) : _me(creature), _range(range) { }

    bool operator()(Unit* u) const;

private:
    Creature const* _me;
    float _range;
    EnemyTargeterCheck(EnemyTargeterCheck const&) = delete;
};

bool EnemyTargeterCheck::operator()(Unit* u) const
{
    if (u->isDead())
        return false;

    if (_me->AI() && !_me->AI()->CanForceAttack(u))
        return false;

    if (u->GetDistance2d(_me) >= _range)
        return false;

    return true;
}

struct dungeon_defense_base_ai : public ScriptedAI
{
public:
    dungeon_defense_base_ai(Creature* creature, bool canMelee, bool canMove = true, float range = 15.0f) : ScriptedAI(creature), CanMelee(canMelee), Range(range)
    {
        SetCombatMovement(canMove);
    }

    void InitializeAI() override
    {
        me->SetRegenerateHealth(false);
        me->SetUnitFlag(UnitFlags::UNIT_FLAG_IMMUNE_TO_PC);
        auto it = CreatureHealths.find(me->GetEntry());
        if (it != CreatureHealths.end())
        {
            me->SetMaxHealth(it->second);
            me->SetHealth(it->second);
        }
        me->UpdateDamagePhysical(WeaponAttackType::BASE_ATTACK);
    }

    float currDmg = 0.0f;

    void ModifyDamage(float& minDmg, float& maxDmg)
    {
        auto it = CreatureDmgs.find(me->GetEntry());
        if (it != CreatureDmgs.end())
        {
            minDmg = it->second;
            maxDmg = it->second;
            currDmg = it->second; // cache so we don't lookup everytime.
        }
    }

    virtual void DamageDealt(Unit* /*victim*/, uint32& damage, DamageEffectType /*damageType*/, SpellInfo const* /*spellInfo = nullptr*/)
    {
        damage = static_cast<uint32>(currDmg);
    }

    void UpdateAI(uint32 diff) override
    {
        if (me->isDead())
            return;

        scheduler.Update(diff);

        if (!UpdateVictimSpecial(diff))
            return;

        events.Update(diff);

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        if (uint32 eventId = events.ExecuteEvent())
        {
            ExecuteEvent(eventId);
            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;
        }

        if (CanMelee)
            DoMeleeAttackIfReady();
    }

    // leave empty
    void EnterEvadeMode(EvadeReason /*why*/) override
    {
    }

    int32 combatTimer = 100;

    bool UpdateVictimCustom()
    {
        if (!IsEngaged())
            return false;

        if (!me->IsAlive())
        {
            EngagementOver();
            return false;
        }

        if (Unit* victim = SelectTowerOrCrystal())
            if (victim != me->GetVictim())
                AttackStart(victim);

        return me->GetVictim() != nullptr;
    }

    virtual bool UpdateVictimSpecial(uint32 diff)
    {
        if (!UpdateVictimCustom())
        {
            if (!me->isDead())
            {
                combatTimer -= diff;
                if (combatTimer <= 0)
                {
                    combatTimer = 100;

                    if (auto target = SelectTowerOrCrystal())
                        AttackStart(target);
                    else if (IsCombatMovementAllowed() && me->GetFaction() == 35) // TODO: make IsDefender
                        me->GetMotionMaster()->MoveTargetedHome();
                }
            }
            return false;
        }

        return true;
    }

    Unit* SelectTowerOrCrystal()
    {
        std::list<Unit*> list;
        CellCoord p(Trinity::ComputeCellCoord(me->GetPositionX(), me->GetPositionY()));
        Cell cell(p);
        cell.SetNoCreate();

        EnemyTargeterCheck u_check(me, Range);
        Trinity::UnitListSearcher<EnemyTargeterCheck> searcher(me, list, u_check);

        TypeContainerVisitor<Trinity::UnitListSearcher<EnemyTargeterCheck>, WorldTypeMapContainer > world_unit_searcher(searcher);
        TypeContainerVisitor<Trinity::UnitListSearcher<EnemyTargeterCheck>, GridTypeMapContainer >  grid_unit_searcher(searcher);

        cell.Visit(p, world_unit_searcher, *me->GetMap(), *me, Range);
        cell.Visit(p, grid_unit_searcher, *me->GetMap(), *me, Range);

        Unit* closest = nullptr;
        float currDist = Range;

        for (auto unit : list)
        {
            float dist = me->GetDistance2d(unit);
            if (dist <= currDist)
            {
                currDist = dist;
                closest = unit;
            }
        }

        return closest;
    }

    virtual void ExecuteEvent(uint32 /*eventId*/) { }

    TaskScheduler scheduler;
    EventMap events;
    float Range;
    bool CanMelee = true;
};

// 851000 - npc_rift_crystal_851000
struct npc_rift_crystal_851000 : public BossAI
{
public:
    npc_rift_crystal_851000(Creature* creature) : BossAI(creature, BossCrystal) { }

    void InitializeAI()
    {
        me->SetRegenerateHealth(false);
        me->SetReactState(REACT_PASSIVE);
        SetCombatMovement(false);

        auto it = CreatureHealths.find(me->GetEntry());
        if (it != CreatureHealths.end())
        {
            me->SetMaxHealth(it->second);
            me->SetHealth(it->second);
        }

        Talk(4); // Click the Rift Crystal to start each round.
    }

    void Reset() override
    {

    }

    bool CanForceAttack(Unit const* target) const override
    {
        if (target->IsCreature())
        {
            switch (target->GetEntry())
            {
                case Goblin:
                case Kobold:
                case Orc:
                case OrcBruiser:
                case Beholder:
                case Ogre:
                case GoblinChef:
                    return true;
                default:
                    break;
            }
        }

        return false;
    }

    bool CanAIAttack(Unit const* target) const override
    {
        if (target->IsCreature())
        {
            switch (target->GetEntry())
            {
                case Goblin:
                case Kobold:
                case Orc:
                case OrcBruiser:
                case Beholder:
                case Ogre:
                case GoblinChef:
                    return true;
                default:
                    break;
            }
        }

        return false;
    }

    bool OnGossipHello(Player* player) override
    {
        if (IsStageActive)
            return true;

        ClearGossipMenuFor(player);
        WorldPackets::Quest::DisplayPlayerChoice displayPlayerChoice;
        displayPlayerChoice.SenderGUID = me->GetGUID();
        displayPlayerChoice.ChoiceID = PlayerChoiceID;
        displayPlayerChoice.Question = "Round Info";
        displayPlayerChoice.CloseChoiceFrame = false;
        displayPlayerChoice.HideWarboardHeader = false;
        displayPlayerChoice.KeepOpenAfterChoice = false;
        displayPlayerChoice.UiTextureKitID = 5260;
        displayPlayerChoice.SoundKitID = 80244; // 80244 brwaler upgrade

        WorldPackets::Quest::PlayerChoiceResponse playerChoiceResponse;

        playerChoiceResponse.ResponseID = 4412416;
        playerChoiceResponse.ResponseIdentifier = 335;
        playerChoiceResponse.ChoiceArtFileID = 3718821;
        playerChoiceResponse.UiTextureKitID = 5487;
        playerChoiceResponse.WidgetSetID = 120;
        playerChoiceResponse.Reward.emplace();

        playerChoiceResponse.Header = "Stage Info";
        playerChoiceResponse.SubHeader = "Stage Info";
        playerChoiceResponse.ButtonTooltip = "Click to start the next round!";
        playerChoiceResponse.Confirmation = "Confirmation";
        playerChoiceResponse.Answer = "Start Stage";
        playerChoiceResponse.SubHeader = "Stage " + std::to_string(Stage + 1);

        std::ostringstream ss;

        ss << "You will fight:\n";
        ss << "This should be converted into a DB Table!";

      //  playerChoiceResponse.Description = ss.str();

        displayPlayerChoice.Responses.push_back(playerChoiceResponse);
        
        player->PlayerTalkClass->GetInteractionData().PlayerChoiceId = PlayerChoiceID;
        player->GetSession()->SendPacket(displayPlayerChoice.Write());

        return true;
    }

    void DoAction(int32 actionId) override
    {
        if (actionId == Cleanup)
        {
            summons.DespawnAll();
            return;
        }

        if (actionId == StartEventEASY)
        {
            if (instance)
                instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);

            //DoAction(StartStageOffset);
            Stage = 0;
            MaxStages = 5;
            return;
        }

        if (actionId == StartStageOffset)
        {
            if (IsStageActive)
                return;

            Talk(5); // Round Starting!

            IsStageActive = true;
            me->RemoveNpcFlag(NPCFlags::UNIT_NPC_FLAG_GOSSIP);
            LastOffset = 0;

            switch (Stage)
            {
                // ----------------------
                // Stage 1:
                // 10x Kobold
                // 5x Goblin
                // 3x Orc
                // 1x Goblin Chief
                case 0:
                    for (int i = 0; i < 10; ++i)
                        SpawnDelayed(Kobold);
                    for (int i = 0; i < 5; ++i)
                        SpawnDelayed(Goblin);
                    for (int i = 0; i < 3; ++i)
                        SpawnDelayed(Orc);
                    SpawnDelayed(GoblinChef);
                    break;
                // ----------------------
                // Stage 2:
                // 10 Kobold
                // 6 Goblin
                // 4 Orc
                // 2 Gob Chief
                // 1 Orc Bruster
                case 1:
                    for (int i = 0; i < 10; ++i)
                        SpawnDelayed(Kobold);
                    for (int i = 0; i < 6; ++i)
                        SpawnDelayed(Goblin);
                    for (int i = 0; i < 4; ++i)
                        SpawnDelayed(Orc);
                    for (int i = 0; i < 2; ++i)
                        SpawnDelayed(GoblinChef);
                    SpawnDelayed(OrcBruiser);
                    break;
                // ------------------ 
                // Stage 3:
                // 12 Kobold
                // 8 Goblin
                // 6 Orc
                // 3 Gob Chief
                // 3 Orc Bruisers
                // 1 Beholder 
                case 2:
                    for (int i = 0; i < 12; ++i)
                        SpawnDelayed(Kobold);
                    for (int i = 0; i < 8; ++i)
                        SpawnDelayed(Goblin);
                    for (int i = 0; i < 6; ++i)
                        SpawnDelayed(Orc);
                    for (int i = 0; i < 3; ++i)
                        SpawnDelayed(GoblinChef);
                    for (int i = 0; i < 3; ++i)
                        SpawnDelayed(OrcBruiser);
                    SpawnDelayed(Beholder);
                    break;
                // ----------------
                // Stage 4:
                // 14 Kobold
                // 10 Goblin
                // 7 Orc
                // 4 Gob Chief
                // 5 Orc Bruisers
                // 2 Beholders
                case 3:
                    for (int i = 0; i < 14; ++i)
                        SpawnDelayed(Kobold);
                    for (int i = 0; i < 10; ++i)
                        SpawnDelayed(Goblin);
                    for (int i = 0; i < 7; ++i)
                        SpawnDelayed(Orc);
                    for (int i = 0; i < 3; ++i)
                        SpawnDelayed(GoblinChef);
                    for (int i = 0; i < 3; ++i)
                        SpawnDelayed(OrcBruiser);
                    for (int i = 0; i < 2; ++i)
                        SpawnDelayed(Beholder);
                    break;
                // -----------------
                // Stage 5:
                // 12 Kobold
                // 8 Goblin
                // 7 Orc
                // 4 Gob Chief
                // 5 Orc Bruisers
                // 2 Beholders
                // 1 Ogre 
                case 4:
                    for (int i = 0; i < 12; ++i)
                        SpawnDelayed(Kobold);
                    for (int i = 0; i < 8; ++i)
                        SpawnDelayed(Goblin);
                    for (int i = 0; i < 7; ++i)
                        SpawnDelayed(Orc);
                    for (int i = 0; i < 4; ++i)
                        SpawnDelayed(GoblinChef);
                    for (int i = 0; i < 5; ++i)
                        SpawnDelayed(OrcBruiser);
                    for (int i = 0; i < 2; ++i)
                        SpawnDelayed(Beholder);
                    SpawnDelayed(Ogre);
                    break;
            }
        }
    }

    void JustEngagedWith(Unit* /*who*/) override
    {
        Talk(0); // The Crystal is under attack!
    }

    void JustDied(Unit* /*who*/) override
    {
        Talk(3); // Game Over. Your Crystal has been destroyed.
        RemainingEnemies = 0;
        Stage = 0;
        MaxStages = 0;
        summons.DespawnAll();
        if (instance)
        {
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            instance->SetBossState(BossCrystal, EncounterState::FAIL);
        }
    }

    void EnterEvadeMode(EvadeReason /*why*/) override
    {
        //BossAI::EnterEvadeMode(why);
        //_DespawnAtEvade(3s);
        //
        //if (instance)
        //    instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
    }

    void SummonedCreatureDies(Creature* who, Unit* /*killer*/) override
    {
        switch (who->GetEntry())
        {
            case Goblin:
            case Kobold:
            case Orc:
            case OrcBruiser:
            case Beholder:
            case Ogre:
            case GoblinChef:
                break;
            default:
                return;
        }

        if (RemainingEnemies > 0)
        {
            --RemainingEnemies;

            if (RemainingEnemies == 0)
            {
                IsStageActive = false;
                if (Stage == MaxStages - 1)
                {
                    if (instance)
                        instance->SetBossState(BossCrystal, EncounterState::DONE);
                    Talk(7); // You've won!
                    summons.DespawnAll();
                }
                else
                {
                    Talk(6); // Round Complete!
                    Stage++;
                    DoAction(StartStageOffset + Stage);
                    me->SetNpcFlag(NPCFlags::UNIT_NPC_FLAG_GOSSIP);

                    if (instance)
                        instance->instance->DoOnPlayers([](Player* player)
                    {
                        GiveRiftEnergyToPlayer(player, 100);
                    });
                }
            }
        }
    }

    void UpdateAI(uint32 diff) override
    {
        scheduler.Update(diff);
    }

    bool Phase50 = false;
    bool Phase10 = false;

    void DamageTaken(Unit* /*attacker*/, uint32& /*damage*/, DamageEffectType /*damageType*/, SpellInfo const* /*spell*/) override
    {
        if (me->HealthBelowPct(51) && !Phase50)
        {
            Phase50 = true;
            Talk(1); // The Crystal is now at 50% health!
        }
        if (me->HealthBelowPct(11) && !Phase10)
        {
            Phase10 = true;
            Talk(2); // The Crystal is now at 10% health!
        }
    }

    bool left = false;
    void SpawnDelayed(uint32 entryId)
    {
        scheduler.Schedule(Milliseconds(LastOffset), [this, entryId](TaskContext context)
        {
            if (auto summ = DoSummon(entryId, EnemySpawnPos, 0s, TempSummonType::TEMPSUMMON_DEAD_DESPAWN))
            {
                if (auto ai = summ->AI())
                {
                    ai->DoAction(left ? LeftWaypoints : RightWaypoints);
                    left = !left;
                }
            }
        });
        LastOffset += 500;
        ++RemainingEnemies;
    }

    TaskScheduler scheduler;
    bool IsStageActive = false;
    uint32 Stage = 0;
    uint32 MaxStages = 5;
    uint32 LastOffset = 0;
    uint32 RemainingEnemies = 0;
};

// 850000 - npc_niybar_twistheart_850000
struct npc_niybar_twistheart_850000 : public ScriptedAI
{
public:
    npc_niybar_twistheart_850000(Creature* creature) : ScriptedAI(creature) { }

    bool OnGossipHello(Player* player) override
    {
        ClearGossipMenuFor(player);

        player->PrepareQuestMenu(me->GetGUID());

        if (auto instance = me->GetInstanceScript())
        {
            if (instance->GetBossState(BossCrystal) != IN_PROGRESS)
            {
                AddGossipItemFor(player, GossipOptionIcon::None, "Start Event", 0, 0, [this, instance, player](std::string /*callback*/)
                {
                    if (instance)
                        if (instance->GetBossState(BossCrystal) != IN_PROGRESS)
                            instance->SetBossState(BossCrystal, IN_PROGRESS);
                    CloseGossipMenuFor(player);
                    if (!player->HasItemCount(699999, 1))
                        player->AddItem(699999, 1);
                });
            }
        }
        AddGossipItemFor(player, GossipOptionIcon::None, "How does this work?", 0, 0, [this, player](std::string /*callback*/)
        {
            ClearGossipMenuFor(player);
            AddGossipItemFor(player, GossipOptionIcon::None, "Okay", 0, 0, [this, player](std::string /*callback*/)
            {
                OnGossipHello(player);
            });
            SendGossipMenuFor(player, 8500000, me);
        });
        SendGossipMenuFor(player, me->GetEntry(), me);
        return true;
    }
};

class DarkmaulCitadel_PlayerScript : public PlayerScript
{
public:
    DarkmaulCitadel_PlayerScript() : PlayerScript("DarkmaulCitadel_PlayerScript") { }

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

struct npc_darkmaul_citadel_enemy_npc_ai : public dungeon_defense_base_ai
{
    npc_darkmaul_citadel_enemy_npc_ai(Creature* creature) : dungeon_defense_base_ai(creature, true) { }

    bool CanForceAttack(Unit const* target) const override
    {
        if (target->IsCreature())
        {
            switch (target->GetEntry())
            {
                case Archer:
                case FireWizard:
                case Cannon:
                case FriendlyOgre:
                case TauntTotem:
                case RiftCrystal:
                    return true;
                default:
                    break;
            }
        }

        return false;
    }

    bool CanAIAttack(Unit const* target) const override
    {
        return CanForceAttack(target);
    }

    void InitializeAI() override
    {
        dungeon_defense_base_ai::InitializeAI();
        me->SetReactState(REACT_DEFENSIVE);
    }

    void DoAction(int32 actionId) override
    {
        if (actionId == LeftWaypoints)
        {
            Path.push(EnemyPointOne);
            Path.push(EnemyPointTwo);
            Path.push(EnemyPointThree);
            Path.push(EnemyPointLeftOne);
            Path.push(EnemyPointLeftTwo);
        }
        else if (actionId == RightWaypoints)
        {
            Path.push(EnemyPointOne);
            Path.push(EnemyPointTwo);
            Path.push(EnemyPointThree);
            Path.push(EnemyPointRightOne);
            Path.push(EnemyPointRightTwo);
        }
        AccelerateWithPath();
    }

    void JustEngagedWith(Unit* /*who*/) override
    {
        me->SetHomePosition(*me);
    }

    void EnterEvadeMode(EvadeReason /*why*/) override
    {
        AccelerateWithPath();
    }
    void AccelerateWithPath()
    {
        if (!Path.empty())
        {
            me->GetMotionMaster()->MovePoint(1, Path.front(), MOVE_RUN_MODE | MOVE_PATHFINDING)->callbackFunc = [this]()
            {
                if (!Path.empty())
                {
                    Path.pop();
                    AccelerateWithPath();
                }
            };
        }
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictimSpecial(diff))
        {
            if (!me->GetVictim() && !me->isDead() && !me->isMoving() && !Path.empty())
                AccelerateWithPath();

            return;
        }

        if (CanMelee)
            DoMeleeAttackIfReady();
    }

    void JustDied(Unit* /*killer*/) override
    {
        if (auto instance = me->GetInstanceScript())
        {
            auto it = CreatureRiftEnergyReward.find(me->GetEntry());
            if (it != CreatureRiftEnergyReward.end())
            {
                uint32 reward = it->second;

                std::list<Player*> players;
                for (MapReference const& ref : instance->instance->GetPlayers())
                    if (Player* player = ref.GetSource())
                        players.push_back(player);

                Player* randPlayer = nullptr;

                int i = 5;
                while (i > 0)
                {
                    randPlayer = Trinity::Containers::SelectRandomContainerElement(players);
                    if (!randPlayer->IsGameMaster())
                        break;

                    i--;
                }

                if (randPlayer)
                {
                    GiveRiftEnergyToPlayer(randPlayer, reward);
                }
            }
        }
    }

    std::queue<Position> Path;
};

struct npc_darkmaul_citadel_defender_ai : public dungeon_defense_base_ai
{
    npc_darkmaul_citadel_defender_ai(Creature* creature, bool canMelee, bool canMove = true, float range = 15.0f) : dungeon_defense_base_ai(creature, canMelee, canMove, range) { }

    bool CanForceAttack(Unit const* target) const override
    {
        if (target->IsCreature())
        {
            switch (target->GetEntry())
            {
                case Goblin:
                case Kobold:
                case Orc:
                case OrcBruiser:
                case Beholder:
                case Ogre:
                case GoblinChef:
                    return true;
                default:
                    break;
            }
        }

        return false;
    }

    bool CanAIAttack(Unit const* target) const override
    {
        return CanForceAttack(target);
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictimSpecial(diff))
            return;

        if (CanMelee)
            DoMeleeAttackIfReady();
    }

    uint32 Invested = 0;
    uint32 CurrUpgrade = 1;
    uint32 MaxUpgrade = 3;
    uint32 NextUpgradeCost = 0;

    void SetData(uint32 id, uint32 data) override
    {
        if (id == SetRiftEnergy)
        {
            Invested = data;
            NextUpgradeCost = data;
        }
    }

    void UpdateStats()
    {
        auto healthPct = me->GetHealthPct();
        me->SetMaxHealth(me->GetMaxHealth() * 1.5f);
        currDmg *= 1.5f;
        me->UpdateDamagePhysical(WeaponAttackType::BASE_ATTACK);
        me->SetHealth(me->CountPctFromMaxHealth(healthPct));
    }

    bool OnGossipHello(Player* player) override
    {
        ClearGossipMenuFor(player);
        player->PrepareQuestMenu(me->GetGUID());

        if (auto instance = player->GetInstanceScript())
        {
            std::ostringstream ss;
            ss << "Rift Energy: " << player->GetCurrency(RiftEnergy) << "/" << instance->GetData(DataGetMaxEnergy);

            AddGossipItemFor(player, GossipOptionIcon::None, ss.str(), 0, 0, [this, player](std::string /*callback*/)
            {
                OnGossipHello(player);
            });

            if (me->GetHealth() != me->GetMaxHealth())
            {
                ss.clear();
                ss.str("");
                ss << "Heal (" << me->GetHealth() << "/" << me->GetMaxHealth() << ")";
                uint32 cost = ((me->GetMaxHealth() - me->GetHealth()) / 5);

                if (player->GetCurrency(RiftEnergy) >= cost)
                    ss << " Cost: " << cost;
                else
                    ss << " |cffFF0000Cost: " << cost;

                AddGossipItemFor(player, GossipOptionIcon::None, ss.str(), 0, 0, [this, player, cost](std::string /*callback*/)
                {
                    uint32 energy = player->GetCurrency(RiftEnergy);
                    if (energy >= cost)
                    {
                        player->ModifyCurrency(RiftEnergy, -static_cast<int32>(cost));
                        ChatHandler(player).PSendSysMessage("|cffFFA600-%u Rift Energy", cost);
                        me->SetFullHealth();
                    }
                    else
                    {
                        if (energy > 0 && energy < cost)
                        {
                            energy -= cost;

                            player->ModifyCurrency(RiftEnergy, -static_cast<int32>(energy));
                            ChatHandler(player).PSendSysMessage("|cffFFA600-%u Rift Energy", energy);
                            me->SetHealth(me->GetHealth() + energy * 5);
                        }
                    }

                    OnGossipHello(player);
                });
            }

            ss.clear();
            ss.str("");
            ss << "Upgrade (" << CurrUpgrade << "/" << MaxUpgrade << ")";

            if (CurrUpgrade == MaxUpgrade)
                ss << " MAX";
            else
            {
                if (player->GetCurrency(RiftEnergy) >= NextUpgradeCost)
                    ss << " Cost: " << NextUpgradeCost;
                else
                    ss << " |cffFF0000Cost: " << NextUpgradeCost;
            }

            AddGossipItemFor(player, GossipOptionIcon::None, ss.str(), 0, 0, [this, player](std::string /*callback*/)
            {
                if (player->GetCurrency(RiftEnergy) >= NextUpgradeCost)
                {
                    if (CurrUpgrade < MaxUpgrade)
                    {
                        Invested += NextUpgradeCost;
                        player->ModifyCurrency(RiftEnergy, -static_cast<int32>(NextUpgradeCost));
                        ChatHandler(player).PSendSysMessage("|cffFFA600-%u Rift Energy", NextUpgradeCost);
                        CurrUpgrade++;
                        UpdateStats();
                    }
                }

                OnGossipHello(player);
            });

            ss.clear();
            ss.str("");
            ss << "Sell for " << (uint32)((float)Invested * 0.75f);
            AddGossipItemFor(player, GossipOptionIcon::None, ss.str(), 0, 0, "Are you sure you want to sell this defender?", 0, false, [this, player](std::string /*callback*/)
            {
                me->DespawnOrUnsummon();
                me->RemoveNpcFlag(NPCFlags::UNIT_NPC_FLAG_GOSSIP);
                // Sell
                GiveRiftEnergyToPlayer(player, Invested * 0.75f);

                CloseGossipMenuFor(player);
            });
        }

        SendGossipMenuFor(player, DefenderNpcTextId, me);
        return true;
    }
};

class DarkmaulCitadel_DungeonDefenseSpawner_ItemScript : public ItemScript
{
public:
    DarkmaulCitadel_DungeonDefenseSpawner_ItemScript() : ItemScript("DarkmaulCitadel_DungeonDefenseSpawner_ItemScript") { }

    bool OnUse(Player* player, Item* item, SpellCastTargets const& /*targets*/, ObjectGuid /*castId*/) override
    {
        MainMenu(player, item);
        return true;
    }

    void MainMenu(Player* player, Item* item)
    {
        if (player->GetMapId() != DarkmaulMapId)
            return;

        ClearGossipMenuFor(player);

        if (auto instance = player->GetInstanceScript())
        {
            if (instance->GetBossState(BossCrystal) == IN_PROGRESS)
            {
                std::ostringstream ss;

                ss << "Rift Energy: " << player->GetCurrency(RiftEnergy) << "/" << instance->GetData(DataGetMaxEnergy);

                AddGossipItemFor(player, GossipOptionIcon::None, ss.str(), 0, 0, [this, player, item](std::string /*callback*/)
                {
                    MainMenu(player, item);
                });

                for (auto const& itr : CreatureRiftEnergyCosts)
                {
                    auto creatureTemplate = sObjectMgr->GetCreatureTemplate(itr.first);
                    if (!creatureTemplate)
                        continue;

                    uint32 cost = itr.second;
                    ss.clear();
                    ss.str("");
                    ss << "Spawn " << creatureTemplate->Name;

                    if (player->GetCurrency(RiftEnergy) >= cost)
                        ss << " Cost: " << cost;
                    else
                        ss << " |cffFF0000Cost: " << cost;

                    AddGossipItemFor(player, GossipOptionIcon::None, ss.str(), 0, 0, [this, player, item, creatureTemplate, cost](std::string /*callback*/)
                    {
                        if (auto instance = player->GetInstanceScript())
                        {
                            if (auto crystal = instance->GetCreature(BossCrystal))
                            {
                                if (player->GetCurrency(RiftEnergy) >= cost)
                                {
                                    player->ModifyCurrency(RiftEnergy, -static_cast<int32>(cost));
                                    ChatHandler(player).PSendSysMessage("|cffFFA600-%u Rift Energy", cost);
                                    if (auto defense = crystal->SummonCreature(creatureTemplate->Entry, *player, TEMPSUMMON_MANUAL_DESPAWN))
                                    {
                                        if (defense->AI())
                                            defense->AI()->SetData(SetRiftEnergy, cost);
                                    }
                                }
                            }
                        }
                        MainMenu(player, item);
                    });
                }
            }
        }
        SendGossipMenuFor(player, DungeonDefenseItemNpcTextId, item->GetGUID());
    }
};


// 851001 - npc_archer_851001
struct npc_archer_851001 : public npc_darkmaul_citadel_defender_ai
{
public:
    npc_archer_851001(Creature* creature) : npc_darkmaul_citadel_defender_ai(creature, false, false, 25.0f) { }

    int32 archerTimer = 1000;

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictimSpecial(diff))
            return;

        if (!me->HasUnitState(UNIT_STATE_CASTING) && me->GetVictim())
        {
            if (archerTimer >= 1000)
            {
                archerTimer = 0;
                DoCastVictim(75, true); // Auto Shot
            }
            else
                archerTimer += diff;
        }
    }
};

// 851002 - npc_fire_wizard_851002
struct npc_fire_wizard_851002 : public npc_darkmaul_citadel_defender_ai
{
public:
    npc_fire_wizard_851002(Creature* creature) : npc_darkmaul_citadel_defender_ai(creature, false, false, 40.0f) { }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictimSpecial(diff))
            return;

        if (!me->HasUnitState(UNIT_STATE_CASTING) && me->GetVictim())
            DoCastVictim(Pyroblast);
    }
};

// 851003 - npc_cannon_851003
struct npc_cannon_851003 : public npc_darkmaul_citadel_defender_ai
{
public:
    npc_cannon_851003(Creature* creature) : npc_darkmaul_citadel_defender_ai(creature, false, false, 40.0f) { }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictimSpecial(diff))
            return;

        if (!me->HasUnitState(UNIT_STATE_CASTING) && me->GetVictim())
            DoCastVictim(CannonFireBall);
    }
};

// 851004 - npc_taunt_totem_851004
struct npc_taunt_totem_851004 : public npc_darkmaul_citadel_defender_ai
{
public:
    npc_taunt_totem_851004(Creature* creature) : npc_darkmaul_citadel_defender_ai(creature, false, false) { }

    int32 tauntTimer = 1000;

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictimSpecial(diff))
            return;

        if (!me->HasUnitState(UNIT_STATE_CASTING) && me->GetVictim())
        {
            if (tauntTimer >= 1000)
            {
                tauntTimer = 0;
                DoCastAOE(29060, true);
            }
            else
                tauntTimer += diff;
        }
    }
};

// 851005 - npc_bomb_totem_851005
struct npc_bomb_totem_851005 : public npc_darkmaul_citadel_defender_ai
{
public:
    npc_bomb_totem_851005(Creature* creature) : npc_darkmaul_citadel_defender_ai(creature, false, false) { }

    int32 bombTimer = 1000;

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictimSpecial(diff))
            return;

        if (!me->HasUnitState(UNIT_STATE_CASTING) && me->GetVictim())
        {
            DoCastSelf(358239);
        }
    }
};

// 851006 - npc_slow_totem_851006
struct npc_slow_totem_851006 : public npc_darkmaul_citadel_defender_ai
{
public:
    npc_slow_totem_851006(Creature* creature) : npc_darkmaul_citadel_defender_ai(creature, false, false) { }

    int32 slowTimer = 1000;

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictimSpecial(diff))
            return;

        if (!me->HasUnitState(UNIT_STATE_CASTING) && me->GetVictim())
        {
            if (slowTimer >= 1000)
            {
                slowTimer = 0;
                DoCastAOE(246, true);
            }
            else
                slowTimer += diff;
        }
    }
};

// 851007 - npc_friendly_ogre_851007
struct npc_friendly_ogre_851007 : public npc_darkmaul_citadel_defender_ai
{
public:
    npc_friendly_ogre_851007(Creature* creature) : npc_darkmaul_citadel_defender_ai(creature, true, true) { }
};

void AddSC_DarkmaulCitadel()
{
    // InstanceScript
    RegisterInstanceScript(instance_darkmaul_citadel, DarkmaulMapId);

    // CreatureAI
    RegisterCreatureAI(npc_rift_crystal_851000);
    RegisterCreatureAI(npc_niybar_twistheart_850000);
    RegisterCreatureAI(npc_darkmaul_citadel_enemy_npc_ai); // remove after enemies scripted (should inherit this)
    RegisterCreatureAI(npc_friendly_ogre_851007);
    RegisterCreatureAI(npc_bomb_totem_851005);
    RegisterCreatureAI(npc_slow_totem_851006);
    RegisterCreatureAI(npc_fire_wizard_851002);
    RegisterCreatureAI(npc_archer_851001);
    RegisterCreatureAI(npc_taunt_totem_851004);
    RegisterCreatureAI(npc_cannon_851003);

    // Misc
    new DarkmaulCitadel_DungeonDefenseSpawner_ItemScript();
    new DarkmaulCitadel_PlayerScript();
}
