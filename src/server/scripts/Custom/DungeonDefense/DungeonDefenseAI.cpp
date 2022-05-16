#include "DungeonDefense.h"

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
    dungeon_defense_base_ai(Creature* creature, bool canMelee, bool canMove = true) : ScriptedAI(creature), CanMelee(canMelee), Range(15.0f)
    {
        SetCombatMovement(canMove);
    }

    void InitializeAI() override
    {
        me->SetRegenerateHealth(false);
        me->SetUnitFlag(UnitFlags::UNIT_FLAG_IMMUNE_TO_PC);
        sDungeonDefenseMgr->InitializeCreature(me, Range);
        me->UpdateDamagePhysical(WeaponAttackType::BASE_ATTACK);
    }

    float _minDmg = 0.0f;
    float _maxDmg = 0.0f;

    void ModifyDamage(float& minDmg, float& maxDmg)
    {
        sDungeonDefenseMgr->InitializeCreatureDamage(me, minDmg, maxDmg);
        _minDmg = minDmg;
        _maxDmg = maxDmg;
    }

    virtual void DamageDealt(Unit* /*victim*/, uint32& damage, DamageEffectType /*damageType*/, SpellInfo const* /*spellInfo = nullptr*/)
    {
        damage = static_cast<uint32>(frand(_minDmg, _maxDmg));
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
                if (combatTimer >= 100)
                {
                    if (auto target = SelectTowerOrCrystal())
                    {
                        combatTimer = 0;
                        AttackStart(target);
                    }
                    else if (IsCombatMovementAllowed() && me->GetFaction() == 35) // TODO: make IsDefender
                    {
                        if (combatTimer >= 500)
                        {
                            me->GetMotionMaster()->MoveTargetedHome();
                            combatTimer = 0;
                        }
                        else
                            combatTimer += diff;
                    }
                }
                else
                    combatTimer += diff;
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

        float range = 0.0f;
        sDungeonDefenseMgr->InitializeCreature(me, range);

        Talk(4); // Click the Rift Crystal to start each round.
    }

    void Reset() override
    {

    }

    bool CanForceAttack(Unit const* target) const override
    {
        if (target->IsCreature())
        {
            switch (target->ToCreature()->GetOriginalEntry())
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
            switch (target->ToCreature()->GetOriginalEntry())
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

        if (instance)
        {
            auto difficulty = instance->GetData(DataGetCurrentDifficulty);
            auto pair = std::make_pair(difficulty, Stage);
            if (sDungeonDefenseMgr->m_StageStorage.count(pair))
            {
                auto range = sDungeonDefenseMgr->m_StageStorage.equal_range(pair);

                for (auto i = range.first; i != range.second; ++i)
                {
                    auto creatureTemplate = sObjectMgr->GetCreatureTemplate(i->second.NpcEntry);
                    if (creatureTemplate)
                    {
                        ss << creatureTemplate->Name << " x" << i->second.Amount << "\n";
                    }
                }
            }

            playerChoiceResponse.Description = ss.str();
        }



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

        if (actionId == StartEvent)
        {
            if (instance)
            {
                instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
                auto difficulty = instance->GetData(DataGetCurrentDifficulty);

                switch (difficulty)
                {

                }

                Stage = 0;
                MaxStages = 5;
            }
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

            if (instance)
            {
                auto difficulty = instance->GetData(DataGetCurrentDifficulty);
                auto pair = std::make_pair(difficulty, Stage);
                if (sDungeonDefenseMgr->m_StageStorage.count(pair))
                {
                    auto range = sDungeonDefenseMgr->m_StageStorage.equal_range(pair);

                    for (auto i = range.first; i != range.second; ++i)
                    {
                        for (uint32 x = 0; x < i->second.Amount; x++)
                        {
                            SpawnDelayed(i->second.NpcEntry);
                        }
                    }
                }
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

        summons.DoOnSummons([](Creature* summ)
        {
            if (!summ->IsAlive())
                return;

            if (summ->GetFaction() == 35)
                summ->SetEmoteState(Emote::EMOTE_STATE_CRY);
            else
                summ->SetEmoteState(Emote::EMOTE_ONESHOT_CHEER);
        });

        summons.DespawnAll(2s);
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

                    summons.DoOnSummons([](Creature* summ)
                    {
                        if (!summ->IsAlive())
                            return;

                        if (summ->GetFaction() == 35)
                            summ->SetEmoteState(Emote::EMOTE_ONESHOT_CHEER);
                        else
                            summ->SetEmoteState(Emote::EMOTE_STATE_CRY);
                    });

                    summons.DespawnAll(2s);
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
                        sDungeonDefenseMgr->GiveRiftEnergyToPlayer(player, 100);
                    });

                    summons.DoOnSummons([](Creature* summ)
                    {
                        if (!summ->IsAlive())
                            summ->DespawnOrUnsummon(1s);
                    });
                    summons.RemoveNotExisting();
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
                std::ostringstream ss;
                for (auto const& itr : sDungeonDefenseMgr->m_DefenseTemplates)
                {
                    uint32 diffId = itr.first;
                    uint32 rewardRiftEssence = itr.second.RewardRiftEssence;
                    uint32 maxRiftEnergy = itr.second.MaxRiftEnergy;
                    uint32 starRiftEnergy = itr.second.StartRiftEnergy;
                    uint32 maxDefensePoints = itr.second.MaxDefensePoints;

                    ss.clear();
                    ss.str("");
                    ss << "Start Event (" << sDungeonDefenseMgr->GetDifficultyText(diffId) << ") Awards up to " << rewardRiftEssence << " Rift Essence";
                    AddGossipItemFor(player, GossipOptionIcon::None, ss.str(), 0, 0, [this, instance, player, diffId, rewardRiftEssence, maxRiftEnergy, starRiftEnergy, maxDefensePoints](std::string /*callback*/)
                    {
                        if (instance)
                        {
                            if (instance->GetBossState(BossCrystal) != IN_PROGRESS)
                            {
                                instance->SetData(SetDifficulty, diffId);
                                instance->SetData(SetAwardRiftEssence, rewardRiftEssence);
                                instance->SetData(SetStartRiftEnergy, starRiftEnergy);
                                instance->SetData(SetMaxRiftEnergy, maxRiftEnergy);
                                instance->SetData(SetMaxDefensePoints, maxDefensePoints);
                                instance->SetData(SetDefensePoints, 0);
                                instance->SetBossState(BossCrystal, IN_PROGRESS);
                            }
                        }
                        CloseGossipMenuFor(player);
                        if (!player->HasItemCount(699999, 1))
                            player->AddItem(699999, 1);
                    });
                }
            }
            else if (instance->GetBossState(BossCrystal) == IN_PROGRESS)
            {
                AddGossipItemFor(player, GossipOptionIcon::None, "Forfeit", 0, 0, "Are you sure you want to forfeit the event?", 0, false, [this, player, instance](std::string /*callback*/)
                {
                    if (instance)
                    {
                        if (instance->GetBossState(BossCrystal) == IN_PROGRESS)
                        {
                            instance->SetBossState(BossCrystal, NOT_STARTED);
                        }
                    }
                    OnGossipHello(player);
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

struct npc_darkmaul_citadel_enemy_npc_ai : public dungeon_defense_base_ai
{
    npc_darkmaul_citadel_enemy_npc_ai(Creature* creature) : dungeon_defense_base_ai(creature, true) { }

    bool CanForceAttack(Unit const* target) const override
    {
        if (target->IsCreature())
        {
            switch (target->ToCreature()->GetOriginalEntry())
            {
                case Archer:
                case FireWizard:
                case Cannon:
                case FriendlyOgre:
                case TauntTotem:
                case SlowTotem:
                case BombTotem:
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
        sDungeonDefenseMgr->HandleCreatureDeath(me);
    }

    std::queue<Position> Path;
};

struct npc_darkmaul_citadel_defender_ai : public dungeon_defense_base_ai
{
    npc_darkmaul_citadel_defender_ai(Creature* creature, bool canMelee, bool canMove = true) : dungeon_defense_base_ai(creature, canMelee, canMove) { }

    bool CanForceAttack(Unit const* target) const override
    {
        if (target->IsCreature())
        {
            switch (target->ToCreature()->GetOriginalEntry())
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

    void JustDied(Unit* /*who*/) override
    {
        if (auto instance = me->GetInstanceScript())
            instance->SetData(SetRemoveDefensePoints, DefensePointsWorth);
    }

    uint32 BaseCost = 0;
    uint32 Invested = 0;
    uint32 CurrUpgrade = 1;
    uint32 MaxUpgrade = 0;
    uint32 NextUpgradeCost = 0;
    uint32 DefensePointsWorth = 0;
    std::queue<uint32> UpgradeEntries;

    void SetData(uint32 id, uint32 data) override
    {
        if (id == SetRiftEnergy)
        {
            BaseCost = data;
            Invested = data;
            NextUpgradeCost = data;

            if (auto defenseData = sDungeonDefenseMgr->GetDefenseDataForCreature(me))
            {
                for (auto upgrade : defenseData->UpgradeEntries)
                    UpgradeEntries.push(upgrade);
                MaxUpgrade = UpgradeEntries.size() + 1;
            }
        }
        else if (id == SetDefensePoints)
        {
            DefensePointsWorth = data;
        }
    }

    void UpdateStats()
    {
        if (!UpgradeEntries.empty())
        {
            me->UpdateEntry(UpgradeEntries.front());
            UpgradeEntries.pop();
            //auto healthPct = me->GetHealthPct();
            me->SetMaxHealth(me->GetMaxHealth() * 1.5f);
            _minDmg *= 1.5f;
            _maxDmg *= 1.5f;
            //me->SetHealth(me->CountPctFromMaxHealth(healthPct));
            me->SetFullHealth();
        }
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

            ss.clear();
            ss.str("");
            auto currDefensePoints = instance->GetData(DataGetDefensePoints);
            auto maxDefensePoints = instance->GetData(DataGetMaxDefensePoints);
            ss << "Defense Points: " << currDefensePoints << "/" << maxDefensePoints;
            AddGossipItemFor(player, GossipOptionIcon::None, ss.str(), 0, 0, [this, player](std::string /*callback*/)
            {
                OnGossipHello(player);
            });

            if (me->GetHealth() != me->GetMaxHealth() && me->GetHealthPct() >= 1.0f)
            {
                float FullHealthCost = Invested / 2.0f;
                float costPerPct = FullHealthCost * (1.0f / 100.0f);
                uint32 cost = costPerPct * (100.0f - me->GetHealthPct());

                if (cost > 0)
                {
                    ss.clear();
                    ss.str("");
                    ss << "Heal (" << me->GetHealth() << "/" << me->GetMaxHealth() << ")";

                    if (player->GetCurrency(RiftEnergy) >= cost)
                        ss << " Cost: " << cost;
                    else
                        ss << " |cffFF0000Cost: " << cost;

                    AddGossipItemFor(player, GossipOptionIcon::None, ss.str(), 0, 0, [this, player](std::string /*callback*/)
                    {
                        uint32 FullHealthCost = Invested / 2;
                        float costPerPct = FullHealthCost * (1.0f / 100.0f);
                        uint32 cost = costPerPct * (100.0f - me->GetHealthPct());
                        uint32 energy = player->GetCurrency(RiftEnergy);
                        if (energy >= cost)
                        {
                            player->ModifyCurrency(RiftEnergy, -static_cast<int32>(cost));
                            sDungeonDefenseMgr->SendRemovedRiftEnergyTo(player, cost);
                            me->SetFullHealth();
                        }
                        else
                        {
                            if (energy > 0 && energy < cost)
                            {
                                player->ModifyCurrency(RiftEnergy, -static_cast<int32>(energy));
                                sDungeonDefenseMgr->SendRemovedRiftEnergyTo(player, energy);
                                me->SetHealth(me->GetHealth() + me->CountPctFromMaxHealth(energy * costPerPct));
                            }
                        }

                        OnGossipHello(player);
                    });
                }
            }

            if (MaxUpgrade > 0)
            {
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
                            sDungeonDefenseMgr->SendRemovedRiftEnergyTo(player, NextUpgradeCost);

                            NextUpgradeCost += BaseCost;

                            CurrUpgrade++;
                            UpdateStats();
                        }
                    }

                    OnGossipHello(player);
                });
            }

            ss.clear();
            ss.str("");
            ss << "Sell for " << (uint32)((float)Invested * 0.75f) << "\nDefensePoints: " << DefensePointsWorth;
            AddGossipItemFor(player, GossipOptionIcon::None, ss.str(), 0, 0, "Are you sure you want to sell this defender?", 0, false, [this, player](std::string /*callback*/)
            {
                me->DespawnOrUnsummon();
                me->RemoveNpcFlag(NPCFlags::UNIT_NPC_FLAG_GOSSIP);
                // Sell
                sDungeonDefenseMgr->GiveRiftEnergyToPlayer(player, Invested * 0.75f);

                if (auto instance = me->GetInstanceScript())
                    instance->SetData(SetRemoveDefensePoints, DefensePointsWorth);

                CloseGossipMenuFor(player);
            });
        }

        SendGossipMenuFor(player, DefenderNpcTextId, me);
        return true;
    }
};

// 851001 - npc_archer_851001
struct npc_archer_851001 : public npc_darkmaul_citadel_defender_ai
{
public:
    npc_archer_851001(Creature* creature) : npc_darkmaul_citadel_defender_ai(creature, false, false) { }

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
    npc_fire_wizard_851002(Creature* creature) : npc_darkmaul_citadel_defender_ai(creature, false, false) { }

    int32 archerTimer = 1500;

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictimSpecial(diff))
            return;

        if (!me->HasUnitState(UNIT_STATE_CASTING) && me->GetVictim())
        {
            if (archerTimer >= 1500)
            {
                archerTimer = 0;
                DoCastVictim(Fireball, true); // Auto Shot
            }
            else
                archerTimer += diff;
        }
    }
};

// 851003 - npc_cannon_851003
struct npc_cannon_851003 : public npc_darkmaul_citadel_defender_ai
{
public:
    npc_cannon_851003(Creature* creature) : npc_darkmaul_citadel_defender_ai(creature, false, false) { }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictimSpecial(diff))
            return;

        if (!me->HasUnitState(UNIT_STATE_CASTING) && me->GetVictim())
            DoCastVictim(255998, CastSpellExtraArgs(TRIGGERED_DONT_CREATE_COOLDOWN));
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
        if (!me->HasUnitState(UNIT_STATE_CASTING))
        {
            auto args = CastSpellExtraArgs();
            args.SpecialDuration = 4000;
            me->CastSpell(me, 358239, args);
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

void AddSC_DungeonDefenseAI()
{
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
}
