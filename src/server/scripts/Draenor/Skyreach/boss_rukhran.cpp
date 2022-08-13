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



static const Position k_Waypoints[12] =
{
    { 929.272f, 1937.448f, 224.75f, 0.0f},
    { 910.023f, 1921.640f, 219.96f, 0.0f},
    { 896.675f, 1901.697f, 219.96f, 0.0f},
    { 898.726f, 1872.698f, 224.75f, 0.0f},
    { 876.896f, 1888.450f, 224.75f, 0.0f},
    { 895.448f, 1928.450f, 224.75f, 0.0f},


    { 895.448f, 1928.450f, 224.75f, 0.0f},
    { 876.896f, 1888.450f, 224.75f, 0.0f},
    { 898.726f, 1872.698f, 224.75f, 0.0f},
    { 896.675f, 1901.697f, 219.96f, 0.0f},
    { 910.023f, 1921.640f, 219.96f, 0.0f},
    { 929.272f, 1937.448f, 224.75f, 0.0f},
};

static const Position k_RandomSummonSolarFlare[] =
{
    { 939.31f, 1907.440f, 213.86f, 0.0f },
    { 938.64f, 1899.550f, 213.86f, 0.0f },
    { 942.61f, 1915.518f, 214.40f, 0.0f },
    { 933.88f, 1908.990f, 213.86f, 0.0f },
    { 926.94f, 1898.300f, 213.86f, 0.0f },
    { 918.43f, 1892.141f, 213.86f, 0.0f },
    { 913.15f, 1887.884f, 213.86f, 0.0f },
    { 920.61f, 1882.406f, 213.86f, 0.0f },
    { 917.99f, 1876.340f, 213.86f, 0.0f },
    { 918.28f, 1884.108f, 213.86f, 0.0f },
    { 909.16f, 1883.930f, 214.40f, 0.0f },
};

class mob_SolarFlare : public CreatureScript
{
public:
    // Entry: 76227
    mob_SolarFlare()
        : CreatureScript("mob_SolarFlare")
    {
    }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new mob_SolarFlareAI(creature);
    }

    enum class Spells : uint32
    {
        SUNSTRIKE = 153828,
        SUNBURST = 169810,
        SOLAR_FLARE = 160964,
        DORMANT = 160641,
        FIXATE = 176544,
    };

    enum class Events : uint32
    {
        UPDATE_POSITION = 1,
    };

    struct mob_SolarFlareAI : public ScriptedAI
    {
        mob_SolarFlareAI(Creature* creature) : ScriptedAI(creature),
            m_Instance(creature->GetInstanceScript()),
            m_events(),
            m_PlayerTargetGuid(ObjectGuid::Empty),
            m_IsKilledByPlayers(true)
        {
            me->SetFaction(FACTION_MONSTER_2);
            me->SetSpeed(MOVE_WALK, 0.35f);
            me->SetSpeed(MOVE_RUN, 0.3f);
            me->SetSpeed(MOVE_FLIGHT, 0.3f);
            me->SetCombatReach(0);
            me->SetBoundingRadius(0);
            me->SetReactState(REACT_PASSIVE);
        }

        void SpawnPileOfAshes()
        {
            // For each pile of ashes in range, we summon a new solar flare and we despawn the pile.
            m_PlayerTargetGuid = ObjectGuid::Empty;
            if (m_Instance)
                m_Instance->SetGuidData(Data::SolarFlareDying, me->GetGUID());
        }

        void Reset()
        {
            m_events.Reset();
            m_IsKilledByPlayers = true;

            if (Player* plr = SelectRandomPlayerIncludedTank(me, 100.0f, false))
            {
                m_PlayerTargetGuid = plr->GetGUID();
                me->GetThreatManager().AddThreat(plr, 1000000.0f);
                me->CastSpell(plr, uint32(Spells::FIXATE));
                m_events.ScheduleEvent(uint32(Events::UPDATE_POSITION), 500);
            }
        }

        void JustDied(Unit*)
        {
            // If creature dies, it spawns a new pile of ashes and it explodes.
            if (m_IsKilledByPlayers)
                me->CastSpell(me, uint32(Spells::SUNBURST), true);
            SpawnPileOfAshes();
        }

        void UpdateAI(const uint32 diff)
        {
            m_events.Update(diff);

            // If creature reaches the target, it spawns a new pile of ashes and explodes violently.
            if (Player* plr = ObjectAccessor::GetPlayer(*me, m_PlayerTargetGuid))
            {
                // It should be less than 2 but I don't know how to make the monsters touch players.
                if (plr->GetExactDist2d(me) < 0.2f)
                {
                    m_IsKilledByPlayers = false;
                    me->CastSpell(me, uint32(Spells::SUNSTRIKE), true);
                    SpawnPileOfAshes();
                }
            }

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case uint32(Events::UPDATE_POSITION):
                    if (Player* plr = ObjectAccessor::GetPlayer(*me, m_PlayerTargetGuid))
                    {
                        Position pos = *plr;
                        me->GetMotionMaster()->MovePoint(0, pos);
                        m_events.ScheduleEvent(uint32(Events::UPDATE_POSITION), 200);
                    }
                    break;
                }
            }
        }

        InstanceScript* m_Instance;
        EventMap m_events;
        ObjectGuid m_PlayerTargetGuid;
        bool m_IsKilledByPlayers;
    };
};

class mob_SkyreachRavenWhisperer : public CreatureScript
{
public:
    // Entry: 76154
    mob_SkyreachRavenWhisperer()
        : CreatureScript("mob_SkyreachRavenWhisperer")
    {
    }

    enum class Spells : uint32
    {
        BLAZE_OF_GLORY = 153926
    };

    enum class Events : uint32
    {
        BLAZE_OF_GLORY = 1,
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new mob_SkyreachRavenWhispererAI(creature);
    }

    struct mob_SkyreachRavenWhispererAI : public ScriptedAI
    {
        mob_SkyreachRavenWhispererAI(Creature* creature) : ScriptedAI(creature),
            m_Instance(creature->GetInstanceScript())
        {
        }

        void Reset()
        {
            events.Reset();
        }

        void JustEngagedWith(Unit*)
        {
            events.ScheduleEvent(uint32(Events::BLAZE_OF_GLORY), 2000);
        }

        void JustDied(Unit*)
        {
            if (m_Instance)
                m_Instance->SetData(Data::SkyreachRavenWhispererIsDead, 0);
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            switch (events.ExecuteEvent())
            {
            case uint32(Events::BLAZE_OF_GLORY):
                me->CastSpell(me, uint32(Spells::BLAZE_OF_GLORY));
                events.ScheduleEvent(uint32(Events::BLAZE_OF_GLORY), 10000);
                break;
            }

            DoMeleeAttackIfReady();
        }

        InstanceScript* m_Instance;
    };
};

class boss_Rukhran : public CreatureScript
{
public:
    // Entry: 76143
    boss_Rukhran()
        : CreatureScript("boss_Rukhran")
    {
    }

    enum class Spells : uint32
    {
        PIERCE_ARMOR = 153794,
        SCREECH = 153896,
        SCREECH_DMG = 153898,
        WEAK = 160149,
        SUMMON_SOLAR_FLARE = 153810,
        QUILLS = 159382,
        QUILLS_DMG = 159381,
    };

    enum class Events : uint32
    {
        PIERCE_ARMOR = 1,    // Every 11 to 12 seconds.
        SUMMON_SOLAR_FLARE = 2,         // Every 15 to 16 seconds.
        QUILLS = 3
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_RukranAI(creature);
    }

    struct boss_RukranAI : public BossAI
    {
        boss_RukranAI(Creature* creature)
            : BossAI(creature, Data::Rukhran),
            m_WaypointId(0),
            m_CombatStarted(false),
            m_LastTarget(0)
        {
            me->SetDisableGravity(true);
            me->SetCanFly(true);
            me->SetAnimTier(AnimTier::Fly, true);
            me->SetPowerType(Powers::POWER_ENERGY);
            me->SetMaxPower(Powers::POWER_ENERGY, 100);
            me->SetPower(Powers::POWER_ENERGY, 100);

            me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
            me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_GRIP, true);
            me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_STUN, true);
            me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_FEAR, true);
            me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_ROOT, true);
            me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_FREEZE, true);
            me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_POLYMORPH, true);
            me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_HORROR, true);
            me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_SAPPED, true);
            me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_CHARM, true);
            me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_SNARE, true);
            me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_DISORIENTED, true);
            me->ApplySpellImmune(0, IMMUNITY_STATE, SPELL_AURA_MOD_CONFUSE, true);
        }

        void Reset()
        {
            events.Reset();

            m_CombatStarted = false;
            if (instance && instance->GetBossState(Data::Rukhran) != EncounterState::SPECIAL
                && instance->GetBossState(Data::Rukhran) != EncounterState::FAIL)
            {
                _Reset();

                m_WaypointId = 0;
                me->SetReactState(REACT_PASSIVE);
                me->GetMotionMaster()->MovePoint(m_WaypointId, k_Waypoints[0]);
                me->SetControlled(false, UNIT_STATE_ROOT);
            }
            else if (instance)
            {
                me->GetMotionMaster()->MovePoint(12, 918.92f, 1913.46f, 215.87f);
                instance->SetData(Data::SkyreachRavenWhispererIsDead, 0);
            }

            // Cleaning the summons.
            auto piles = SelectNearestCreatureListWithEntry(me, MobEntries::PILE_OF_ASHES, 50.0f);
            for (auto pile : piles)
            {
                if (pile->ToCreature())
                    pile->ToCreature()->DespawnOrUnsummon();
            }
            auto solarFlares = SelectNearestCreatureListWithEntry(me, MobEntries::SOLAR_FLARE, 50.0f);
            for (auto solarFlare : solarFlares)
            {
                if (solarFlare->ToCreature())
                    solarFlare->ToCreature()->DespawnOrUnsummon();
            }
            me->CastStop();
        }

        void MovementInform(uint32 type, uint32 id)
        {
            switch (type)
            {
            case POINT_MOTION_TYPE:
                if (id == 12)
                {
                    me->SetControlled(true, UNIT_STATE_ROOT);
                    me->SetReactState(REACT_AGGRESSIVE);
                    me->Attack(SelectRandomPlayerIncludedTank(me, 40.0f, false), true);
                    m_CombatStarted = true;
                    me->SetOrientation(5.4f);
                }
                else
                {
                    m_WaypointId = (m_WaypointId + 1) % 12;
                    me->GetMotionMaster()->MovePoint(m_WaypointId, k_Waypoints[m_WaypointId]);
                }
                break;
            }
        }

        void EnterEvadeMode(EvadeReason /*why*/) override
        {
            me->ClearInCombat();
            me->CombatStop();

            if (instance)
            {
                instance->SetBossState(Data::Rukhran, FAIL);
                instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            }
        }

        void JustReachedHome()
        {
            _JustReachedHome();
        }

        void JustDied(Unit* killer)
        {
            _JustDied();

            // Cleaning the summons.
            auto piles = SelectNearestCreatureListWithEntry(me, MobEntries::PILE_OF_ASHES, 50.0f);
            for (auto pile : piles)
            {
                if (pile->ToCreature())
                    pile->ToCreature()->DespawnOrUnsummon();
            }
            auto solarFlares = SelectNearestCreatureListWithEntry(me, MobEntries::SOLAR_FLARE, 50.0f);
            for (auto solarFlare : solarFlares)
            {
                if (solarFlare->ToCreature())
                    solarFlare->ToCreature()->DespawnOrUnsummon();
            }

            if (!me->GetMap()->IsChallengeMode())
                killer->SummonGameObject(GameObjectEntries::CACHE_OF_ARAKKOAN_TREASURES, { 925.22f, 1904.54f, 213.86f, 0.0f }, QuaternionData(), 0s);

            if (instance)
                instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
        }

        void KilledUnit(Unit* /*victim*/)
        {
        }

        void JustEngagedWith(Unit* who)
        {
            _JustEngagedWith(who);

            events.ScheduleEvent(uint32(Events::PIERCE_ARMOR), 6000);
            events.ScheduleEvent(uint32(Events::SUMMON_SOLAR_FLARE), 10000);

            if (instance && IsHeroic())
                events.ScheduleEvent(uint32(Events::QUILLS), 60000);

            if (instance)
                instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
        }

        void SpellHitTarget(WorldObject* t, SpellInfo const* spellInfo)
        {
            if (!t)
                return;

            auto target = t->ToUnit();
            if (!target)
                return;
            if ((spellInfo->Id == uint32(Spells::SCREECH_DMG) || spellInfo->Id == uint32(Spells::QUILLS_DMG)) && target)
            {
                me->AddAura(uint32(Spells::WEAK), target);
            }
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim() || (me->GetVictim() && me->GetVictim()->GetDistance(me) > 50.0f))
            {
                if (m_CombatStarted)
                {
                    Reset();
                    CreatureAI::EnterEvadeMode();
                }
                return;
            }

            events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
            {
                // Are we casting Screech ?
                if (Spell* l_Spell = me->GetCurrentSpell(CurrentSpellTypes::CURRENT_CHANNELED_SPELL))
                {
                    if (l_Spell->GetSpellInfo()->Id == uint32(Spells::SCREECH))
                    {
                        // Should we stop ?
                        Player* plr = me->FindNearestPlayer(15.0f);
                        if (plr && plr->IsWithinMeleeRange(me))
                            me->CastStop();
                    }
                }
                return;
            }

            // We check if someone is in melee range.
            if (me->GetVictim() && !me->IsWithinMeleeRange(me->GetVictim()))
            {
                Player* plr = me->FindNearestPlayer(15.0f);
                if (!plr || !plr->IsWithinMeleeRange(me))
                {
                    // We can't, so we cast Screech and Weak.
                    if (!me->HasAura(uint32(Spells::SCREECH)))
                        me->CastSpell(me, uint32(Spells::SCREECH));
                }
            }

            switch (events.ExecuteEvent())
            {
            case uint32(Events::SUMMON_SOLAR_FLARE):
                events.ScheduleEvent(uint32(Events::SUMMON_SOLAR_FLARE), urand(14000, 16000));

                if (SelectRandomPlayerIncludedTank(me, 30.0f))
                {
                    m_LastTarget = urand(0, 10) + 1;
                    Position pos = k_RandomSummonSolarFlare[m_LastTarget - 1];
                    me->CastSpell(pos, uint32(Spells::SUMMON_SOLAR_FLARE), false);
                }
                break;
            case uint32(Events::PIERCE_ARMOR):
                events.ScheduleEvent(uint32(Events::PIERCE_ARMOR), urand(10500, 13000));
                // We want to cast PierceArmor on the closest ennemy.
                if (me->GetVictim() && me->GetVictim()->IsWithinMeleeRange(me))
                    me->CastSpell(me->GetVictim(), uint32(Spells::PIERCE_ARMOR));
                else if (me->FindNearestPlayer(15.0f))
                    me->CastSpell(me->GetVictim(), uint32(Spells::PIERCE_ARMOR));
                break;
            case uint32(Events::QUILLS):
                events.ScheduleEvent(uint32(Events::QUILLS), 60000);
                me->CastSpell(me, uint32(Spells::QUILLS));
                break;
            default:
                break;
            }

            DoMeleeAttackIfReady();
        }

        uint32 m_WaypointId;
        bool m_CombatStarted;
        uint32 m_LastTarget;
    };
};

// Summon Solar Flare - 153827
class spell_SummonSolarFlare : public SpellScriptLoader
{
public:
    spell_SummonSolarFlare()
        : SpellScriptLoader("spell_SummonSolarFlare")
    {
    }

    enum class Spells : uint32
    {
    };

    class spell_SummonSolarFlareSpellScript : public SpellScript
    {
        PrepareSpellScript(spell_SummonSolarFlareSpellScript)

            void HandleDummy(SpellEffIndex /*effIndex*/)
        {
            if (GetCaster())
            {
                GetCaster()->SummonCreature(MobEntries::SOLAR_FLARE, *GetHitDest());
            }
        }

        void Register()
        {
            OnEffectLaunchTarget += SpellEffectFn(spell_SummonSolarFlareSpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_SummonSolarFlareSpellScript();
    }
};

// Sunstrike - 153828
class spell_Sunstrike : public SpellScriptLoader
{
public:
    spell_Sunstrike()
        : SpellScriptLoader("spell_Sunstrike")
    {
    }

    enum class Spells : uint32
    {
    };

    class spell_SunstrikeSpellScript : public SpellScript
    {
        PrepareSpellScript(spell_SunstrikeSpellScript)

            void CheckTargetIn(std::list<WorldObject*>& unitList)
        {
            Unit* caster = GetCaster();
            unitList.remove_if([caster](WorldObject* obj) {
                return obj->GetExactDist2d(caster) > 10.0f;
            });
        }

        void CheckTargetOut(std::list<WorldObject*>& unitList)
        {
            Unit* caster = GetCaster();
            unitList.remove_if([caster](WorldObject* obj) {
                return obj->GetExactDist2d(caster) < 10.0f;
            });
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_SunstrikeSpellScript::CheckTargetIn, EFFECT_0, TARGET_UNIT_DEST_AREA_ENEMY);
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_SunstrikeSpellScript::CheckTargetOut, EFFECT_2, TARGET_UNIT_DEST_AREA_ENEMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_SunstrikeSpellScript();
    }
};

// Summon Quills - 159381
class spell_Quills : public SpellScriptLoader
{
public:
    spell_Quills()
        : SpellScriptLoader("spell_Quills")
    {
    }

    enum class Spells : uint32
    {
        Quills = 156742,
    };

    class spell_QuillsSpellScript : public SpellScript
    {
        PrepareSpellScript(spell_QuillsSpellScript)

            void HandleDummy(SpellEffIndex /*effIndex*/)
        {
            Unit* caster = GetCaster();
            if (caster)
                caster->CastSpell(caster, uint32(Spells::Quills), true);
        }

        // This method is used to filter the targets that are behind the big pillar, in the Rukhran event, when
        // Rukhran is casting Quills (player should go behind the big pillar at the center of the platform to hide).
        void CheckTarget(std::list<WorldObject*>& unitList)
        {
            unitList.remove_if([this](WorldObject* object)
            {
                // ref and point should be vectors.
                auto isToTheRightFromRef = [](Position const& ref, Position const& point) -> bool {
                    return point.m_positionX * ref.m_positionY - point.m_positionY * ref.m_positionX > 0;
                };

                // Those both position are the extreme position of the pillar.
                // The three position refers to those points. We want to check if the player
                // is inside and far from the target for a certain distance.
                // O---------------- L
                //  \
                                    //   \        Player
//    \      x
//     \
                    //      \
                    //       \
                    //        R
                static const Position s_OriginPosition = { 918.919f, 1913.459f, 213.0f, 0.0f };
                static const Position s_RightPosition = { 936.999f, 1872.137f, 213.0f, 0.0f };
                static const Position s_LeftPosition = { 951.305f, 1882.338f, 213.0f, 0.0f };

                Position refLeftVect;
                Position refRightVect;
                Position playerVect;
                refLeftVect.m_positionX = s_LeftPosition.m_positionX - s_OriginPosition.m_positionX;
                refLeftVect.m_positionY = s_LeftPosition.m_positionY - s_OriginPosition.m_positionY;
                refLeftVect.m_positionZ = s_LeftPosition.m_positionZ;

                refRightVect.m_positionX = s_RightPosition.m_positionX - s_OriginPosition.m_positionX;
                refRightVect.m_positionY = s_RightPosition.m_positionY - s_OriginPosition.m_positionY;
                refRightVect.m_positionZ = s_RightPosition.m_positionZ;

                playerVect.m_positionX = object->GetPositionX() - s_OriginPosition.m_positionX;
                playerVect.m_positionY = object->GetPositionY() - s_OriginPosition.m_positionY;

                if (!isToTheRightFromRef(refLeftVect, playerVect) || isToTheRightFromRef(refRightVect, playerVect))
                    return false;

                if (GetCaster()->GetExactDist2d(object) < 30.0f)
                    return false;

                return true;
            });
        }

        void Register()
        {
            OnEffectLaunch += SpellEffectFn(spell_QuillsSpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_QuillsSpellScript::CheckTarget, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_QuillsSpellScript();
    }
};

void AddSC_boss_Rukhran()
{
    new boss_Rukhran();
    new mob_SkyreachRavenWhisperer();
    new mob_SolarFlare();
    new spell_SummonSolarFlare();
    new spell_Sunstrike();
    new spell_Quills();
}

