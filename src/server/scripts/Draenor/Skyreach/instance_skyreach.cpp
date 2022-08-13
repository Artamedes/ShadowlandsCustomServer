/*
* Copyright (C) 2008-2018 TrinityCore <https://www.trinitycore.org/>
* Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
*
* This program is free software; you can redistribute it and/or modify it
* under the terms of the GNU General Public License as published by the
* Free Software Foundation; either version 2 of the License, or (at your
* option) any later version.
*
* This program is distributed in the hope that it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
* more details.
*
* You should have received a copy of the GNU General Public License along
* with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include "skyreach.hpp"
#include "ObjectAccessor.h"


enum MaxEncounter
{
    Number = 4,
};

static const DoorData k_DoorData[] =
{
    { DOOR_RANJIT_ENTRANCE,             Data::Ranjit,           DOOR_TYPE_ROOM,      },
    { DOOR_RANJIT_EXIT,                 Data::Ranjit,           DOOR_TYPE_PASSAGE,   },
    { DOOR_ARAKNATH_ENTRANCE_1,         Data::Araknath,         DOOR_TYPE_ROOM,      },
    { DOOR_ARAKNATH_ENTRANCE_2,         Data::Araknath,         DOOR_TYPE_ROOM,      },
    { DOOR_ARAKNATH_EXIT_1,             Data::Araknath,         DOOR_TYPE_PASSAGE,   },
    { DOOR_ARAKNATH_EXIT_2,             Data::Araknath,         DOOR_TYPE_PASSAGE,   },
    { DOOR_RUKHRAN_ENTRANCE,            Data::Rukhran,          DOOR_TYPE_ROOM,      },
    { DOOR_RUKHRAN_EXIT,                Data::Rukhran,          DOOR_TYPE_PASSAGE,   },
    { DOOR_HIGH_SAVE_VIRYX_ENTRANCE,    Data::HighSageViryx,    DOOR_TYPE_ROOM,      },
    { 0,                                0,                      DOOR_TYPE_ROOM,      }  // EOF
};

//static const BossScenarios k_ScenarioData[] =
//{
//    { Data::Ranjit,         ScenarioDatas::RanjitCriteriaId },
//    { Data::Araknath,       ScenarioDatas::AraknathCriteriaId },
//    { Data::Rukhran,        ScenarioDatas::RukhranCriteriaId },
//    { Data::HighSageViryx,  ScenarioDatas::ViryxCriteriaId },
//    { 0,                    0 }, // EOF
//};

class instance_Skyreach : public InstanceMapScript
{
public:
    instance_Skyreach() : InstanceMapScript("instance_Skyreach", 1209) { }

    struct instance_SkyreachInstanceMapScript : public InstanceScript
    {
        // Araknath part.
        ObjectGuid m_AraknathGuid;
        ObjectGuid m_SkyreachArcanologistGuid;
        std::list<ObjectGuid> m_SolarConstructorsGuid;
        ObjectGuid m_SelectedSolarConstructorGuid;
        ObjectGuid m_InteriorFocusGuid;
        ObjectGuid m_SolarConstructorEnergizerGuid;

        // Rukhran part.
        ObjectGuid m_RukhranGuid;
        ObjectGuid m_SkyreachRavenWhispererGuid;
        std::set<ObjectGuid> m_PileOfAshesGuid;
        std::set<ObjectGuid> m_SolarFlaresGuid;
        ObjectGuid m_CacheOfArakoanTreasuresGuid;

        // Wind maze zone.
        std::map<ObjectGuid, uint32> m_PlayerGuidToBlockId;
        std::vector<ObjectGuid> m_WindMazeBlockGuids;

        // High Sage Viryx.
        std::vector<ObjectGuid> m_MagnifyingGlassFocusGuids;
        ObjectGuid m_ReshadOutroGuid;

        // Achievements.
        std::map<ObjectGuid, uint32> m_ReadyForRaidingIVAchievements;
        bool m_HasFailedMonomaniaAchievement;

        instance_SkyreachInstanceMapScript(InstanceMap* map)
            : InstanceScript(map),
            m_AraknathGuid(ObjectGuid::Empty),
            m_SkyreachArcanologistGuid(ObjectGuid::Empty),
            m_SolarConstructorsGuid(),
            m_SelectedSolarConstructorGuid(ObjectGuid::Empty),
            m_InteriorFocusGuid(ObjectGuid::Empty),
            m_SolarConstructorEnergizerGuid(ObjectGuid::Empty),
            m_RukhranGuid(ObjectGuid::Empty),
            m_SkyreachRavenWhispererGuid(ObjectGuid::Empty),
            m_PileOfAshesGuid(),
            m_SolarFlaresGuid(),
            m_CacheOfArakoanTreasuresGuid(ObjectGuid::Empty),
            m_PlayerGuidToBlockId(),
            m_WindMazeBlockGuids(),
            m_MagnifyingGlassFocusGuids(),
            m_ReshadOutroGuid(ObjectGuid::Empty),
            m_HasFailedMonomaniaAchievement(false)
        {
            SetBossNumber(MaxEncounter::Number);
            LoadDoorData(k_DoorData);
            //LoadScenariosInfos(k_ScenarioData, map->IsChallengeMode() ? ScenarioDatas::ChallengeScenarioId : ScenarioDatas::ScenarioId);

            //for (uint32 i = Blocks::FirstStair; i <= Blocks::SecondStair; i++)
            //    m_WindMazeBlockGuids.push_back(MAKE_NEW_GUID(sObjectMgr->GenerateLowGuid(HIGHGUID_AREATRIGGER), 6452, HIGHGUID_AREATRIGGER));

            for (uint32 i = Blocks::FirstStair; i <= Blocks::SecondStair; i++)
                m_WindMazeBlockGuids.push_back(ObjectGuid::Empty);

            //instance->SetObjectVisibility(533.3f);
        }

        void OnCreatureCreate(Creature* creature)
        {
            switch (creature->GetEntry())
            {
            case BossEntries::RANJIT:
                break;
            case BossEntries::ARAKNATH:
                m_AraknathGuid = creature->GetGUID();
                break;
            case BossEntries::RUKHRAN:
                m_RukhranGuid = creature->GetGUID();
                if (GetBossState(Data::Rukhran) == EncounterState::SPECIAL)
                    SetData(Data::SkyreachRavenWhispererIsDead, 0);
                break;
            case MobEntries::SKYREACH_ARCANALOGIST:
                m_SkyreachArcanologistGuid = creature->GetGUID();
                break;
            case MobEntries::SkyreachDefenseConstruct:
                creature->RemoveUnitFlag(UNIT_FLAG_UNK_6);
                break;
            case MobEntries::SKYREACH_SOLAR_CONSTRUCTOR:
                m_SolarConstructorsGuid.emplace_front(creature->GetGUID());
                creature->DisableEvadeMode();
                creature->SetUnitFlag(UnitFlags(UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_REMOVE_CLIENT_CONTROL | UNIT_FLAG_IMMUNE_TO_PC));
                if (GetBossState(Data::Araknath) == EncounterState::NOT_STARTED || GetBossState(Data::Araknath) == EncounterState::TO_BE_DECIDED)
                {
                    creature->CastSpell(creature, uint32(RandomSpells::ENERGIZE_VISUAL_1));
                    creature->RemoveAura(RandomSpells::SUBMERGED);
                }
                else
                {
                    creature->AddAura(RandomSpells::SUBMERGED, creature);
                    creature->SetReactState(ReactStates::REACT_PASSIVE);
                    creature->GetThreatManager().ClearAllThreat ();
                    creature->GetThreatManager().ResetAllThreat();
                }
                break;
            case MobEntries::SKYREACH_RAVEN_WHISPERER:
                m_SkyreachRavenWhispererGuid = creature->GetGUID();
                break;
            case MobEntries::YoungKaliri:
                creature->SetDisableGravity(true);
                creature->SetCanFly(true);
                creature->SetAnimTier(AnimTier::Hover, true);
                creature->SetReactState(REACT_PASSIVE);
                creature->SetFaction(FACTION_MONSTER_2);
                creature->DisableEvadeMode();
                creature->SetUnitFlag(UnitFlags(UNIT_FLAG_REMOVE_CLIENT_CONTROL | UNIT_FLAG_NON_ATTACKABLE));
                break;
            case MobEntries::Arakkoa:
            case MobEntries::Kaliri:
            case MobEntries::Kaliri2:
                // Setting fly.
                creature->SetDisableGravity(true);
                creature->SetCanFly(true);
                creature->SetAnimTier(AnimTier::Hover, true);
                creature->SetReactState(REACT_PASSIVE);
                break;
            case MobEntries::PILE_OF_ASHES:
                creature->AddUnitState(UNIT_STATE_UNATTACKABLE);
                creature->SetUnitFlag(UNIT_FLAG_IMMUNE_TO_PC);
                creature->SetUnitFlag(UNIT_FLAG_IMMUNE_TO_NPC);
                m_PileOfAshesGuid.insert(creature->GetGUID());
                break;
            case MobEntries::SOLAR_FLARE:
                m_SolarFlaresGuid.insert(creature->GetGUID());
                break;
            case MobEntries::GrandDefenseConstruct:
            case MobEntries::RadiantSupernova:
            case MobEntries::AirFamiliar:
                creature->SetFaction(FACTION_MONSTER_2);
                break;
            case MobEntries::ArakkoaPincerBirdsController:
                creature->AddAura(16245, creature); // Freeze anim spell.
                creature->SetFaction(FACTION_MONSTER_2);
                creature->SetReactState(REACT_PASSIVE);
                creature->SetUnitFlag(UnitFlags(UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_REMOVE_CLIENT_CONTROL | UNIT_FLAG_IMMUNE_TO_PC));
                break;
            case MobEntries::SolarZealot:
                creature->SetFaction(FACTION_MONSTER_2);
                creature->SetDisableGravity(true);
                creature->SetCanFly(true);
                creature->SetAnimTier(AnimTier::Hover, true);
                creature->SetReactState(REACT_PASSIVE);
                creature->DisableEvadeMode();
                break;
            case MobEntries::DreadRavenHatchling:
                creature->SetFaction(FACTION_MONSTER_2);
                break;
            case MobEntries::SunConstructEnergizer:
                m_SolarConstructorEnergizerGuid = creature->GetGUID();
                creature->SetDisableGravity(true);
                creature->SetCanFly(true);
                creature->SetAnimTier(AnimTier::Hover, true);
                creature->SetReactState(REACT_PASSIVE);
                break;
            case MobEntries::InteriorFocus:
                m_InteriorFocusGuid = creature->GetGUID();
                creature->SetDisableGravity(true);
                creature->SetCanFly(true);
                creature->SetAnimTier(AnimTier::Hover, true);
                creature->SetReactState(REACT_PASSIVE);
                break;
            case MobEntries::AraokkoaMagnifyingConstructA:
                m_MagnifyingGlassFocusGuids.push_back(creature->GetGUID());
                creature->SetFaction(FACTION_MONSTER_2);
                creature->SetDisableGravity(true);
                creature->SetCanFly(true);
                creature->SetAnimTier(AnimTier::Hover, true);
                creature->SetReactState(REACT_PASSIVE);
                creature->DisableEvadeMode();
                break;
            case MobEntries::ArakkoaMagnifyingGlassFocus:
                creature->SetDisplayId(17519);
                creature->SetReactState(REACT_PASSIVE);
                creature->SetCanFly(false);
                creature->DisableEvadeMode();
                creature->SetDisableGravity(false);
                break;
            case MobEntries::ReshadOutro:
                m_ReshadOutroGuid = creature->GetGUID();
                creature->SetDisableGravity(true);
                creature->SetCanFly(true);
                creature->SetAnimTier(AnimTier::Hover, true);

                if (InstanceScript::GetBossState(Data::HighSageViryx) == EncounterState::DONE)
                {
                    creature->SetVisible(true);
                    creature->GetMotionMaster()->MovePoint(0, 1128.81f, 1814.251f, 262.171f);
                }
                else
                    creature->SetVisible(false);
                break;
            default:
                break;
            }
        }

        void OnGameObjectCreate(GameObject* gameObject)
        {
            switch (gameObject->GetEntry())
            {
            case GameObjectEntries::DOOR_RANJIT_ENTRANCE:
            case GameObjectEntries::DOOR_RANJIT_EXIT:
            case GameObjectEntries::DOOR_ARAKNATH_ENTRANCE_1:
            case GameObjectEntries::DOOR_ARAKNATH_ENTRANCE_2:
            case GameObjectEntries::DOOR_ARAKNATH_EXIT_1:
            case GameObjectEntries::DOOR_ARAKNATH_EXIT_2:
            case GameObjectEntries::DOOR_RUKHRAN_ENTRANCE:
            case GameObjectEntries::DOOR_RUKHRAN_EXIT:
            case GameObjectEntries::DOOR_HIGH_SAVE_VIRYX_ENTRANCE:
                AddDoor(gameObject, true);
                break;
            default:
                break;
            }
        }

        bool SetBossState(uint32 ID, EncounterState state, bool set) override
        {
            if (!InstanceScript::SetBossState(ID, state, set))
                return false;

            switch (ID)
            {
            case Data::Ranjit:
            {
                // Achievement handling.
                if (state == EncounterState::DONE && instance->IsHeroic())
                {
                    AchievementEntry const* l_AE = sAchievementStore.LookupEntry(uint32(Achievements::ReadyForRaidingIV));
                    if (!l_AE)
                        break;

                    for (auto guid : m_ReadyForRaidingIVAchievements)
                    {
                        if (Player* plr = ObjectAccessor::FindPlayer(guid.first))
                        {
                            if (guid.second == 0)
                                plr->CompletedAchievement(l_AE);
                        }
                    }
                }

                break;
            }
            case Data::Araknath:
            {
                switch (state)
                {
                case EncounterState::FAIL:
                {
                    if (Creature* skyreachArcanologist = instance->GetCreature(m_SkyreachArcanologistGuid))
                        skyreachArcanologist->Respawn();
                    break;
                }
                case EncounterState::DONE:
                {
                    if (instance->IsHeroic())
                        DoCompleteAchievement(uint32(Achievements::MagnifyEnhance));

                    for (ObjectGuid guid : m_SolarConstructorsGuid)
                    {
                        if (Creature* constructor = instance->GetCreature(guid))
                        {
                            constructor->CombatStop();
                            constructor->SetReactState(ReactStates::REACT_PASSIVE);
                            constructor->GetThreatManager().ClearAllThreat();
                            constructor->GetThreatManager().ResetAllThreat();
                        }
                    }

                    break;
                }
                default:
                    break;
                }

                break;
            }
            case Data::Rukhran:
            {
                switch (state)
                {
                case EncounterState::FAIL:
                {
                    if (Creature* rukhran = instance->GetCreature(m_RukhranGuid))
                    {
                        rukhran->GetMotionMaster()->Clear();
                        SetBossState(Data::Rukhran, EncounterState::SPECIAL, set);
                        rukhran->GetMotionMaster()->MovePoint(12, 918.92f, 1913.46f, 215.87f);
                    }
                    break;
                }
                default:
                    break;
                }

                break;
            }
            case Data::HighSageViryx:
            {
                switch (state)
                {
                case EncounterState::DONE:
                {
                    if (Creature* reshad = instance->GetCreature(m_ReshadOutroGuid))
                    {
                        reshad->SetVisible(true);
                        reshad->GetMotionMaster()->MovePoint(0, 1128.81f, 1814.251f, 262.171f);
                    }

                    if (instance->IsHeroic())
                        DoCompleteAchievement(uint32(Achievements::HeroicSkyreach));
                    else
                        DoCompleteAchievement(uint32(Achievements::Skyreach));

                    if (instance->IsHeroic() && !m_HasFailedMonomaniaAchievement)
                        DoCompleteAchievement(uint32(Achievements::Monomania));

                   // DoKilledMonsterKredit(ScenarioDatas::ScenarioDatas::DailyChallengeQuestID, ScenarioDatas::ScenarioDatas::DailyChallengeKillCredit);
                    break;
                }
                default:
                    break;
                }

                break;
            }
            default:
                break;
            }

            return true;
        }

        void SetData(uint32 type, uint32 data)
        {
            switch (type)
            {
            case Data::SkyreachRavenWhispererIsDead:
                if (Creature* rukhran = instance->GetCreature(m_RukhranGuid))
                {
                    if (GetBossState(Data::Rukhran) == EncounterState::NOT_STARTED)
                    {
                        rukhran->GetMotionMaster()->Clear();
                        rukhran->GetMotionMaster()->MovePoint(12, 918.92f, 1913.46f, 215.87f);
                        rukhran->DisableEvadeMode();
                        SetBossState(Data::Rukhran, EncounterState::SPECIAL, true);
                    }
                    else
                        rukhran->SetOrientation(5.4f);
                }
                break;
            case Data::SkyreachArcanologistIsDead:
                if (Creature* araknath = instance->GetCreature(m_AraknathGuid))
                {
                    SetBossState(Data::Araknath, EncounterState::SPECIAL, true);
                    araknath->RemoveAura(RandomSpells::SUBMERGED);
                    araknath->SetReactState(REACT_AGGRESSIVE);
                }

                for (ObjectGuid guid : m_SolarConstructorsGuid)
                {
                    if (Creature* constructor = instance->GetCreature(guid))
                    {
                        constructor->CastStop();
                        constructor->AddAura(RandomSpells::SUBMERGED, constructor);
                    }
                }

                if (Creature* interiorFocus = instance->GetCreature(m_InteriorFocusGuid))
                    interiorFocus->CastStop();
                if (Creature* solarConstructorEnergizer = instance->GetCreature(m_SolarConstructorEnergizerGuid))
                    solarConstructorEnergizer->CastStop();
                break;
            case Data::SkyreachArcanologistReset:
                if (GetBossState(Data::Araknath) == EncounterState::DONE)
                    break;

                if (Creature* araknath = instance->GetCreature(m_AraknathGuid))
                {
                    araknath->GetThreatManager().ResetAllThreat();

                    if (araknath->GetAI())
                        araknath->GetAI()->Reset();
                }

                for (ObjectGuid guid : m_SolarConstructorsGuid)
                {
                    if (Creature* constructor = instance->GetCreature(guid))
                    {
                        constructor->CastSpell(constructor, uint32(RandomSpells::ENERGIZE_VISUAL_1));
                        constructor->RemoveAura(RandomSpells::SUBMERGED);
                    }
                }

                if (Creature* interiorFocus = instance->GetCreature(m_InteriorFocusGuid))
                    interiorFocus->CastSpell(interiorFocus, uint32(RandomSpells::ENERGIZE_VISUAL_3));

                if (Creature* solarConstructorEnergizer = instance->GetCreature(m_SolarConstructorEnergizerGuid))
                    solarConstructorEnergizer->CastSpell(solarConstructorEnergizer, uint32(RandomSpells::ENERGIZE_VISUAL_3));
                break;
            case Data::AraknathSolarConstructorActivation:
                if (data)
                {
                    if (m_SolarConstructorsGuid.empty())
                        break;

                    auto randUnit = m_SolarConstructorsGuid.begin();
                    std::advance(randUnit, urand(0, m_SolarConstructorsGuid.size() - 1));
                    m_SelectedSolarConstructorGuid = *randUnit;

                    if (Creature* constructor = instance->GetCreature(m_SelectedSolarConstructorGuid))
                    {
                        constructor->RemoveAura(RandomSpells::SUBMERGED);
                        constructor->CastSpell(constructor, uint32(RandomSpells::ENERGIZE_HEAL));
                    }

                    // Visual part.
                    if (Creature* interiorFocus = instance->GetCreature(m_InteriorFocusGuid))
                        interiorFocus->CastSpell(interiorFocus, uint32(RandomSpells::ENERGIZE_VISUAL_3));

                    if (Creature* solarConstructorEnergizer = instance->GetCreature(m_SolarConstructorEnergizerGuid))
                        solarConstructorEnergizer->CastSpell(solarConstructorEnergizer, uint32(RandomSpells::ENERGIZE_VISUAL_2));
                }
                else
                {
                    if (Creature* constructor = instance->GetCreature(m_SelectedSolarConstructorGuid))
                    {
                        constructor->AddAura(RandomSpells::SUBMERGED, constructor);
                        constructor->CastStop();
                    }

                    // Visual part.
                    if (Creature* interiorFocus = instance->GetCreature(m_InteriorFocusGuid))
                        interiorFocus->CastStop();

                    if (Creature* solarConstructorEnergizer = instance->GetCreature(m_SolarConstructorEnergizerGuid))
                        solarConstructorEnergizer->CastStop();

                    m_SelectedSolarConstructorGuid = ObjectGuid::Empty;
                }
            case Data::StartingLensFlare:
            {
                if (m_MagnifyingGlassFocusGuids.empty())
                    break;

                auto itr = m_MagnifyingGlassFocusGuids.begin();
                std::advance(itr, m_MagnifyingGlassFocusGuids.size() - 1);

                if (Creature* creature = instance->GetCreature(*itr))
                    creature->CastSpell(creature, uint32(RandomSpells::LensFlare), true);

            } break;
            case Data::MonomaniaAchievementFail:
                m_HasFailedMonomaniaAchievement = true;
                break;
            default:
                break;
            }
        }

        void SetGuidData(uint32 type, ObjectGuid data)
        {
            enum class Spells : uint32
            {
                SOLAR_FLARE = 160964,
                DORMANT = 160641,
                SUMMON_SOLAR_FLARE = 153810,
            };

            switch (type)
            {
            case Data::SolarFlareDying:
                if (m_SolarFlaresGuid.find(data) == m_SolarFlaresGuid.end())
                    break;
                m_SolarFlaresGuid.erase(data);

                if (Unit* solarFlareDying = instance->GetCreature(data))
                {
                    uint32 l_SolarFlaresFormed = 0;
                    auto piles = SelectNearestCreatureListWithEntry(solarFlareDying, MobEntries::PILE_OF_ASHES, 5.0f);
                    for (auto pile : piles)
                    {
                        if (m_PileOfAshesGuid.find(pile->GetGUID()) == m_PileOfAshesGuid.end())
                            continue;
                        m_PileOfAshesGuid.erase(pile->GetGUID());

                        Position pos = *pile;
                        if (pile->ToCreature())
                        {
                            pile->CastSpell(pos, uint32(Spells::SUMMON_SOLAR_FLARE), true);
                            TempSummon* summon = pile->SummonCreature(MobEntries::SOLAR_FLARE, pos);
                            m_SolarFlaresGuid.insert(summon->GetGUID());
                            pile->ToCreature()->DespawnOrUnsummon(500ms);
                            ++l_SolarFlaresFormed;
                        }
                    }

                    if (l_SolarFlaresFormed >= 3)
                        DoCompleteAchievement(uint32(Achievements::ISawSolis));

                    // We summon a new pile of ashes.
                    solarFlareDying->CastSpell(solarFlareDying, uint32(Spells::DORMANT), true);

                    Position pos = *solarFlareDying;
                    TempSummon* sum = solarFlareDying->SummonCreature(MobEntries::PILE_OF_ASHES, pos);
                    sum->SetFaction(FACTION_MONSTER_2);
                    sum->SetReactState(REACT_PASSIVE);
                    sum->CastSpell(sum, uint32(Spells::DORMANT), true);
                    solarFlareDying->Kill(solarFlareDying, solarFlareDying);

                    if (solarFlareDying->ToCreature())
                        solarFlareDying->ToCreature()->DespawnOrUnsummon(500ms);
                }
                break;
            case Data::PlayerIsHittedByRanjitSpells:
                if (!instance->IsHeroic())
                    break;
                ++m_ReadyForRaidingIVAchievements[data];
                break;
            }
        }

        /// This is going to track for the players entering the dungeon for the first time to do the intro.
        GuidUnorderedSet _playersEntered;
        struct Position DreadRavenPos = { 1000.9827, 1872.9254, 277.5583, 1.4859924 };

        ///  Position: X: 1000.9827 Y : 1872.9254 Z : 278.0778 O : 1.609076
        void OnPlayerEnter(Player* player)
        {
            if (!player->IsInWorld())
                return;

            if (!_playersEntered.count(player->GetGUID()))
            {
                _playersEntered.insert(player->GetGUID());
                player->CastSpell(DreadRavenPos, RandomSpells::SUMMON_INTRO_DREAD_RAVEN, true);
            }

            InstanceScript::OnPlayerEnter(player);

            m_ReadyForRaidingIVAchievements[player->GetGUID()] = 0;
            m_PlayerGuidToBlockId[player->GetGUID()] = 0;
        }

        void Update(uint32 diff)
        {
            UpdateOperations(diff);
            if (true)
                return;

            // We check here if a player is in the WindMaze zone.
            Map::PlayerList const &playerList = instance->GetPlayers();
            if (!playerList.isEmpty())
            {
                for (Map::PlayerList::const_iterator i = playerList.begin(); i != playerList.end(); ++i)
                {
                    Player* plr = i->GetSource();
                    if (!plr)
                        continue;

                    // Is he in WindMaze zone ?
                    if (IsPointInBlock(Blocks::ConvexHull, *plr))
                    {
                        bool isInBlock = false;
                        uint32 i = Blocks::FirstStair;
                        for (; i <= Blocks::SecondStair; i++)
                        {
                            if (IsPointInBlock(i, *plr))
                            {
                                isInBlock = true;
                                break;
                            }
                        }

                        // If the player is in one of the blocks and if it doesn't have the Wind aura, add it.
                        if (isInBlock)
                        {
                            float magnitude = 1;
                            Position forceDir = CalculateForceVectorFromBlockId(i, magnitude);
                            if (!plr->HasAura(RandomSpells::Wind))
                            {
                                plr->AddAura(RandomSpells::Wind, plr);
                                // Apply force.
                                plr->ApplyMovementForce(m_WindMazeBlockGuids[i], forceDir , -3.0f, MovementForceType::Gravity);
                            }
                            else if (i != m_PlayerGuidToBlockId[plr->GetGUID()])
                            {
                                // Remove old force.
                                // Add new force.
                                if (plr->HasMovementForce(m_WindMazeBlockGuids[m_PlayerGuidToBlockId[plr->GetGUID()]]))
                                    plr->RemoveMovementForce(m_WindMazeBlockGuids[m_PlayerGuidToBlockId[plr->GetGUID()]]);

                                plr->ApplyMovementForce(m_WindMazeBlockGuids[i], forceDir, -3.0f, MovementForceType::Gravity);
                            }

                            m_PlayerGuidToBlockId[plr->GetGUID()] = i;
                        }
                        // Otherwise remove it if it has the Wind aura.
                        else if (plr->HasAura(RandomSpells::Wind))
                        {
                            if (plr->HasMovementForce(m_WindMazeBlockGuids[m_PlayerGuidToBlockId[plr->GetGUID()]]))
                                plr->RemoveMovementForce(m_WindMazeBlockGuids[m_PlayerGuidToBlockId[plr->GetGUID()]]);
                            plr->RemoveAura(RandomSpells::Wind);
                        }
                    }
                    // If player is out of the WindMaze zone and has the aura, remove it.
                    else if (plr->HasAura(RandomSpells::Wind))
                    {
                        if (plr->HasMovementForce(m_WindMazeBlockGuids[m_PlayerGuidToBlockId[plr->GetGUID()]]))
                            plr->RemoveMovementForce(m_WindMazeBlockGuids[m_PlayerGuidToBlockId[plr->GetGUID()]]);
                        plr->RemoveAura(RandomSpells::Wind);
                    }
                }
            }

            // Beam light intersection handler.
            if (!m_SelectedSolarConstructorGuid.IsEmpty())
            {
                if (instance)
                {
                    Map::PlayerList const &PlayerList = instance->GetPlayers();
                    if (PlayerList.isEmpty())
                        return;

                    Unit* araknath = instance->GetCreature(m_AraknathGuid);
                    Unit* selectedSolarConstructor = instance->GetCreature(m_SelectedSolarConstructorGuid);

                    if (!araknath || !selectedSolarConstructor)
                        return;

                    Player* closestPlayerInBeam = nullptr;
                    float closestDistance = std::numeric_limits<float>::max();
                    for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
                    {
                        if (DistanceFromLine(*araknath, *selectedSolarConstructor, *i->GetSource()) < 0.5f // If is in beam.
                            && dotProductXY(araknath->m_positionX - selectedSolarConstructor->m_positionX, araknath->m_positionY - i->GetSource()->m_positionY) > 0 // If player is between solar constructor and araknath.
                            && closestDistance > selectedSolarConstructor->GetDistance(i->GetSource()))
                        {
                            closestDistance = selectedSolarConstructor->GetDistance(i->GetSource());
                            closestPlayerInBeam = i->GetSource();
                        }
                    }

                    auto currentSpell = selectedSolarConstructor->GetCurrentSpell(CURRENT_CHANNELED_SPELL);
                    if (closestPlayerInBeam
                        && currentSpell
                        && currentSpell->GetUnitTarget()
                        && currentSpell->GetUnitTarget()->ToPlayer() != closestPlayerInBeam)
                        selectedSolarConstructor->CastSpell(closestPlayerInBeam, uint32(RandomSpells::ENERGIZE_DMG), CastSpellExtraArgs(false).SetOriginalCaster(m_AraknathGuid));
                    else if (!closestPlayerInBeam
                        && currentSpell
                        && currentSpell->GetUnitTarget()
                        && currentSpell->GetUnitTarget()->ToPlayer())
                        selectedSolarConstructor->CastSpell(selectedSolarConstructor, uint32(RandomSpells::ENERGIZE_HEAL));
                }
            }
        }
    };

    InstanceScript* GetInstanceScript(InstanceMap* map) const
    {
        return new instance_SkyreachInstanceMapScript(map);
    }
};


void AddSC_instance_Skyreach()
{
    new instance_Skyreach();
}

