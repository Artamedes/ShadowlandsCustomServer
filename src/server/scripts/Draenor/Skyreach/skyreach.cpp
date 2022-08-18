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
#include "GenericMovementGenerator.h"
#include "CombatAI.h"

/*
 TODO: There seems to have other spells to cast here. For example:
 - Magma explosion supreme
 - Sun trinckets <- Need modelid and spell to cast. It's healing normaly.
 - Air trinckets
 - Cyclone trinckets ?
 - Do visual stuff when no one is attacking.
 - Need to see if the timers are good enough.
 */


struct npc_GossipIntroOutro : public ScriptedAI
{
public:
    npc_GossipIntroOutro(Creature* c) : ScriptedAI(c)
    {
    }

    enum class Gossip : uint32
    {
        Teleport = 1,
    };

    bool OnGossipSelect(Player* player, uint32 /*sender*/, uint32 /*action*/) override
    {
        CloseGossipMenuFor(player);
        player->TeleportTo(1116, 57.110f, 2527.114f, 79.4f, 0.35f);
        return true;
    }
};

class mob_GrandDefenseConstruct : public CreatureScript
{
public:
    // Entry: 76145
    mob_GrandDefenseConstruct()
        : CreatureScript("mob_GrandDefenseConstruct")
    {
    }

    enum class Spells : uint32
    {
        Smash = 152998,
        Burn = 152999
    };

    enum class Events : uint32
    {
        Smash = 1,
        Burn = 2,
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new mob_GrandDefenseConstructAI(creature);
    }

    struct mob_GrandDefenseConstructAI : public ScriptedAI
    {
        mob_GrandDefenseConstructAI(Creature* creature) : ScriptedAI(creature),
            m_Instance(creature->GetInstanceScript()),
            m_events()
        {
        }

        void Reset()
        {
            m_events.Reset();
        }

        void JustEngagedWith(Unit* /*who*/)
        {
            m_events.ScheduleEvent(uint32(Events::Smash), urand(5000, 7000));
            m_events.ScheduleEvent(uint32(Events::Burn), urand(10000, 12000));
        }

        void JustDied(Unit*)
        {
            // Monomania Achievement.
            if (IsHeroic() && m_Instance)
                m_Instance->SetData(Data::MonomaniaAchievementFail, 0);
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            m_events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            switch (m_events.ExecuteEvent())
            {
            case uint32(Events::Smash):
                m_events.ScheduleEvent(uint32(Events::Smash), 16000);
                me->CastSpell(me->GetVictim(), uint32(Spells::Smash));
                break;
            case uint32(Events::Burn):
                m_events.ScheduleEvent(uint32(Events::Burn), 18000);
                me->CastSpell(me->GetVictim(), uint32(Spells::Burn));
                break;
            default:
                break;
            }

            DoMeleeAttackIfReady();
        }

        InstanceScript* m_Instance;
        EventMap m_events;
    };
};

class mob_YoungKaliri : public CreatureScript
{
public:
    // Entry: 76121
    mob_YoungKaliri()
        : CreatureScript("mob_YoungKaliri")
    {
    }

    enum class Spells : uint32
    {
        Pierce = 153563,
    };

    enum class Events : uint32
    {
        Pierce = 1,
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new mob_YoungKaliriAI(creature);
    }

    struct mob_YoungKaliriAI : public ScriptedAI
    {
        mob_YoungKaliriAI(Creature* creature) : ScriptedAI(creature),
            m_Instance(creature->GetInstanceScript()),
            m_events(),
            m_Pos(),
            m_Home(),
            m_TargetGuid(ObjectGuid::Empty)
        {
            m_Pos = *me;
            m_Home = *me;
            me->SetSpeed(MOVE_FLIGHT, 15.0f);
            m_Pos.m_positionX += 13.0f * cos(me->GetOrientation());
            m_Pos.m_positionY += 13.0f * sin(me->GetOrientation());
        }

        void Reset()
        {
            m_events.Reset();
            m_events.ScheduleEvent(uint32(Events::Pierce), 500);
        }

        void JustEngagedWith(Unit* /*who*/)
        {
        }

        void MovementInform(uint32 /*p_TypeId*/, uint32 pointId)
        {
            switch (pointId)
            {
            case 0:
                me->SetSpeed(MOVE_FLIGHT, 5.0f);
                me->GetMotionMaster()->MoveBackward(1, m_Home.GetPositionX(), m_Home.GetPositionY(), m_Home.GetPositionZ(), 0.5f);
                if (Player* plr = ObjectAccessor::GetPlayer(*me, m_TargetGuid))
                    me->CastSpell(plr, uint32(Spells::Pierce));
                m_TargetGuid = ObjectGuid::Empty;
                break;
            case 1:
                me->SetSpeed(MOVE_FLIGHT, 15.0f);
                me->SetOrientation(m_Home.GetOrientation());
                m_events.ScheduleEvent(uint32(Events::Pierce), 500);
                break;
            }
        }

        void UpdateAI(const uint32 diff)
        {
            m_events.Update(diff);

            switch (m_events.ExecuteEvent())
            {
            case uint32(Events::Pierce):
                if (Player* plr = me->FindNearestPlayer(15.0f))
                {
                    if (me->isInFront(plr, float(M_PI) / 6))
                    {
                        m_TargetGuid = plr->GetGUID();
                        me->GetMotionMaster()->MovePoint(0, m_Pos);
                    }
                    else
                        m_events.ScheduleEvent(uint32(Events::Pierce), 500);
                }
                else
                    m_events.ScheduleEvent(uint32(Events::Pierce), 500);
                break;
            default:
                break;
            }
        }

        InstanceScript* m_Instance;
        EventMap m_events;
        Position m_Pos;
        Position m_Home;
        ObjectGuid m_TargetGuid;
    };
};

class mob_RadiantSupernova : public CreatureScript
{
public:
    // Entry: 79463
    mob_RadiantSupernova()
        : CreatureScript("mob_RadiantSupernova")
    {
    }

    enum class Spells : uint32
    {
        SolarWrath = 157020,
        SolarDetonation = 160303,
    };

    enum class Events : uint32
    {
        SolarWrath = 1,
        SolarDetonation = 2,
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new mob_RadiantSupernovaAI(creature);
    }

    struct mob_RadiantSupernovaAI : public ScriptedAI
    {
        mob_RadiantSupernovaAI(Creature* creature) : ScriptedAI(creature),
            m_Instance(creature->GetInstanceScript()),
            m_events()
        {
        }

        void Reset()
        {
            m_events.Reset();
        }

        void JustEngagedWith(Unit* /*who*/)
        {
            m_events.ScheduleEvent(uint32(Events::SolarWrath), urand(1000, 2000));
            m_events.ScheduleEvent(uint32(Events::SolarDetonation), urand(5000, 7000));
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            m_events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            switch (m_events.ExecuteEvent())
            {
            case uint32(Events::SolarWrath):
                m_events.ScheduleEvent(uint32(Events::SolarWrath), urand(1500, 2500));
                me->CastSpell(me->GetVictim(), uint32(Spells::SolarWrath));
                break;
            case uint32(Events::SolarDetonation):
                m_events.ScheduleEvent(uint32(Events::SolarDetonation), urand(5000, 7000));

                ApplyOnEveryPlayer(me, [](Unit* me, Player* plr) {
                    me->CastSpell(plr, uint32(Spells::SolarDetonation));
                });
                break;
            default:
                break;
            }

            DoMeleeAttackIfReady();
        }

        InstanceScript* m_Instance;
        EventMap m_events;
    };
};

class mob_DefenseConstruct : public CreatureScript
{
public:
    // Entry: 76087
    mob_DefenseConstruct()
        : CreatureScript("mob_DefenseConstruct")
    {
    }

    enum class Spells : uint32
    {
        Submerge = 169084,
        ProtectiveBarrier = 152973,
        SelfDestruct = 158644,
    };

    enum class Events : uint32
    {
        ProtectiveBarrier = 2,
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new mob_DefenseConstructAI(creature);
    }

    struct mob_DefenseConstructAI : public ScriptedAI
    {
        mob_DefenseConstructAI(Creature* creature) : ScriptedAI(creature),
            m_Instance(creature->GetInstanceScript()),
            m_events()
        {
        }

        void Reset()
        {
            m_events.Reset();

            me->AddAura(uint32(Spells::Submerge), me);
        }

        void JustEngagedWith(Unit* /*who*/)
        {
            me->RemoveAura(uint32(Spells::Submerge));
            m_events.ScheduleEvent(uint32(Events::ProtectiveBarrier), urand(5000, 7000));
        }

        void JustDied(Unit*)
        {
            me->CastSpell(me, RandomSpells::DespawnAreaTriggers, true);
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            m_events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            if (me->GetHealthPct() < 10.0f)
            {
                me->CastSpell(me, uint32(Spells::SelfDestruct));
                return;
            }

            switch (m_events.ExecuteEvent())
            {
            case uint32(Events::ProtectiveBarrier):
                me->CastSpell(me, uint32(Spells::ProtectiveBarrier));
                break;
            default:
                break;
            }

            DoMeleeAttackIfReady();
        }

        InstanceScript* m_Instance;
        EventMap m_events;
    };
};

class mob_SolarMagnifier : public CreatureScript
{
public:
    // Entry: 77559
    mob_SolarMagnifier()
        : CreatureScript("mob_SolarMagnifier")
    {
    }

    enum class Spells : uint32
    {
        Submerge = 169084,
        Empower = 152917,
        SolarPulse = 174489,
        SelfDestruct = 158644,
    };

    enum class Events : uint32
    {
        Submerge = 1,
        Empower = 2,
        SolarPulse = 3,
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new mob_SolarMagnifierAI(creature);
    }

    struct mob_SolarMagnifierAI : public ScriptedAI
    {
        mob_SolarMagnifierAI(Creature* creature) : ScriptedAI(creature),
            m_Instance(creature->GetInstanceScript()),
            m_events()
        {
        }

        void Reset()
        {
            m_events.Reset();

            me->AddAura(uint32(Spells::Submerge), me);
        }

        void JustEngagedWith(Unit* /*who*/)
        {
            me->RemoveAura(uint32(Spells::Submerge));
            m_events.ScheduleEvent(uint32(Events::Empower), urand(4000, 5000));
            m_events.ScheduleEvent(uint32(Events::SolarPulse), urand(1500, 2000));
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            m_events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            if (me->GetHealthPct() < 10.0f)
            {
                me->CastSpell(me, uint32(Spells::SelfDestruct));
                return;
            }

            switch (m_events.ExecuteEvent())
            {
            case uint32(Events::Empower):
                m_events.ScheduleEvent(uint32(Events::Empower), urand(6000, 8000));

                if (Unit* friendUnit = SelectNearestFriendExcluededMe(me, 10.0f))
                {
                    if (friendUnit->GetEntry() != me->GetEntry())
                        me->CastSpell(friendUnit, uint32(Spells::Empower));
                }
                break;
            case uint32(Events::SolarPulse):
                m_events.ScheduleEvent(uint32(Events::SolarPulse), urand(2000, 3000));

                if (Unit* plr = SelectRandomPlayerIncludedTank(me, 20.0f))
                    me->CastSpell(plr, uint32(Spells::SolarPulse));
                break;
            default:
                break;
            }

            DoMeleeAttackIfReady();
        }

        InstanceScript* m_Instance;
        EventMap m_events;
    };
};

class mob_DreadRavenHatchling : public CreatureScript
{
public:
    // Entry: 76253
    mob_DreadRavenHatchling()
        : CreatureScript("mob_DreadRavenHatchling")
    {
    }

    enum class Spells : uint32
    {
        EXCITED = 157259,
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new mob_DreadRavenHatchlingAI(creature);
    }

    struct mob_DreadRavenHatchlingAI : public ScriptedAI
    {
        mob_DreadRavenHatchlingAI(Creature* creature) : ScriptedAI(creature),
            m_Instance(creature->GetInstanceScript()),
            m_events()
        {
        }

        void Reset()
        {
            m_events.Reset();
        }

        void JustEngagedWith(Unit* /*who*/)
        {
        }

        void SpellHit(WorldObject* /*caster*/, SpellInfo const* spell) override
        {
            if (spell->Id == uint32(Spells::EXCITED))
            {
                if (Player* plr = SelectRandomPlayerIncludedTank(me, 50.0f, false))
                {
                    me->GetThreatManager().AddThreat(plr, 10000.0f);
                    me->Attack(plr, true);
                }
            }
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            m_events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            DoMeleeAttackIfReady();
        }

        InstanceScript* m_Instance;
        EventMap m_events;
    };
};

class mob_SkyreachSunTalon : public CreatureScript
{
public:
    // Entry: 79093
    mob_SkyreachSunTalon()
        : CreatureScript("mob_SkyreachSunTalon")
    {
    }

    enum class Spells : uint32
    {
        EXPOSE_WEAKNESS = 152982,
        INVISIBILITY_DETECTION = 141048,
        FIXATED = 152838,
    };

    enum class Events : uint32
    {
        CHANGE_TARGET = 1, // Every 6 seconds.
        EXPOSE_WEAKNESS = 2, // Every 10 seconds.
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new mob_SkyreachSunTalonAI(creature);
    }

    struct mob_SkyreachSunTalonAI : public ScriptedAI
    {
        mob_SkyreachSunTalonAI(Creature* creature) : ScriptedAI(creature),
            m_Instance(creature->GetInstanceScript()),
            m_events()
        {
        }

        void Reset()
        {
            m_events.Reset();
        }

        void JustEngagedWith(Unit* /*who*/)
        {
            m_events.ScheduleEvent(uint32(Events::CHANGE_TARGET), 6000);
            m_events.ScheduleEvent(uint32(Events::EXPOSE_WEAKNESS), 10000);
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            m_events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            switch (m_events.ExecuteEvent())
            {
            case uint32(Events::CHANGE_TARGET):
                m_events.ScheduleEvent(uint32(Events::CHANGE_TARGET), 6000);
                me->CastSpell(me, uint32(Spells::INVISIBILITY_DETECTION), true);
                me->CastSpell(me->GetVictim(), uint32(Spells::FIXATED), true);
                me->GetThreatManager().ResetAllThreat();

                if (Player* plr = SelectRandomPlayerIncludedTank(me, 30.0f))
                {
                    me->GetThreatManager().AddThreat(plr, 1000.0f);
                    me->Attack(plr, true);
                }
                break;
            case uint32(Events::EXPOSE_WEAKNESS):
                m_events.ScheduleEvent(uint32(Events::EXPOSE_WEAKNESS), 10000);
                me->CastSpell(me->GetVictim(), uint32(Spells::EXPOSE_WEAKNESS));
                break;
            default:
                break;
            }


            DoMeleeAttackIfReady();
        }

        InstanceScript* m_Instance;
        EventMap m_events;
    };
};

class mob_AdornedBladetalon : public CreatureScript
{
public:
    // Entry: 79303
    mob_AdornedBladetalon()
        : CreatureScript("mob_AdornedBladetalon")
    {
    }

    enum class Spells : uint32
    {
        SLASH = 158083,
        PIERCING_RUSH = 138175,
    };

    enum class Events : uint32
    {
        SLASH = 1, // Every 2 to 5 seconds.
        PIERCING_RUSH = 2, // Every 2 to 5 seconds.
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new mob_AdornedBladetalonAI(creature);
    }

    struct mob_AdornedBladetalonAI : public ScriptedAI
    {
        mob_AdornedBladetalonAI(Creature* creature) : ScriptedAI(creature),
            m_Instance(creature->GetInstanceScript()),
            m_events()
        {
        }

        void Reset()
        {
            m_events.Reset();
        }

        void JustEngagedWith(Unit* /*who*/)
        {
            m_events.ScheduleEvent(uint32(Events::SLASH), urand(0, 4000));
            m_events.ScheduleEvent(uint32(Events::PIERCING_RUSH), urand(5000, 7000));
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            m_events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            switch (m_events.ExecuteEvent())
            {
            case uint32(Events::SLASH):
                m_events.ScheduleEvent(uint32(Events::SLASH), urand(2500, 5000));
                me->CastSpell(me->GetVictim(), uint32(Spells::SLASH));
                break;
            case uint32(Events::PIERCING_RUSH):
                m_events.ScheduleEvent(uint32(Events::PIERCING_RUSH), urand(2500, 5000));

                if (Player* plr = SelectRandomPlayerIncludedTank(me, 20.0f))
                    me->CastSpell(plr, uint32(Spells::PIERCING_RUSH));
                break;
            default:
                break;
            }


            DoMeleeAttackIfReady();
        }

        InstanceScript* m_Instance;
        EventMap m_events;
    };
};

class mob_DrivingGaleCaller : public CreatureScript
{
public:
    // Entry: 78932
    mob_DrivingGaleCaller()
        : CreatureScript("mob_DrivingGaleCaller")
    {
    }

    enum class Spells : uint32
    {
        DERVISH = 153905,
    };

    enum class Events : uint32
    {
        DERVISH = 1, // 20 seconds duration so heavy respawn.
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new mob_DrivingGaleCallerAI(creature);
    }

    struct mob_DrivingGaleCallerAI : public ScriptedAI
    {
        mob_DrivingGaleCallerAI(Creature* creature) : ScriptedAI(creature),
            m_Instance(creature->GetInstanceScript()),
            m_events()
        {
        }

        void Reset()
        {
            m_events.Reset();
        }

        void JustEngagedWith(Unit* /*who*/)
        {
            m_events.ScheduleEvent(uint32(Events::DERVISH), urand(5000, 7000));
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            m_events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            switch (m_events.ExecuteEvent())
            {
            case uint32(Events::DERVISH):
                m_events.ScheduleEvent(uint32(Events::DERVISH), urand(5000, 7000));
                me->CastSpell(me->GetVictim(), uint32(Spells::DERVISH));
                break;
            default:
                break;
            }

            DoMeleeAttackIfReady();
        }

        InstanceScript* m_Instance;
        EventMap m_events;
    };
};

class mob_AdeptOfTheDawn : public CreatureScript
{
public:
    // Entry: 79467
    mob_AdeptOfTheDawn()
        : CreatureScript("mob_AdeptOfTheDawn")
    {
    }

    enum class Spells : uint32
    {
        CRAFT_SUN_TRINCKET = 153521,
        FLASH_HEAL = 152894,
    };

    enum class Events : uint32
    {
        CRAFT_SUN_TRINCKET = 1, // 20 seconds duration so heavy respawn.
        FLASH_HEAL = 2          // Every 2 to 5 seconds.
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new mob_AdeptOfTheDawnAI(creature);
    }

    struct mob_AdeptOfTheDawnAI : public ScriptedAI
    {
        mob_AdeptOfTheDawnAI(Creature* creature) : ScriptedAI(creature),
            m_Instance(creature->GetInstanceScript()),
            m_events()
        {
        }

        void Reset()
        {
            m_events.Reset();
        }

        void JustEngagedWith(Unit* /*who*/)
        {
            // FIXME: Script Sun trinket.
            //m_events.ScheduleEvent(uint32(Events::CRAFT_SUN_TRINCKET), urand(3000, 5000));
            m_events.ScheduleEvent(uint32(Events::FLASH_HEAL), urand(5000, 8000));
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            m_events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            switch (m_events.ExecuteEvent())
            {
            case uint32(Events::CRAFT_SUN_TRINCKET):
                m_events.ScheduleEvent(uint32(Events::CRAFT_SUN_TRINCKET), urand(20000, 25000));
                me->CastSpell(me, uint32(Spells::CRAFT_SUN_TRINCKET));
                break;
            case uint32(Events::FLASH_HEAL):
                m_events.ScheduleEvent(uint32(Events::FLASH_HEAL), urand(5000, 8000));
                me->CastSpell(me, uint32(Spells::FLASH_HEAL));
                break;
            default:
                break;
            }

            DoMeleeAttackIfReady();
        }

        InstanceScript* m_Instance;
        EventMap m_events;
    };
};

class mob_SkyReachOverlord : public CreatureScript
{
public:
    // Entry: 75975
    mob_SkyReachOverlord()
        : CreatureScript("mob_SkyreachOverlord")
    {
    }

    enum class Spells : uint32
    {
        TORN_FEATHERS = 153178,
        BEAT_LOW_BORN_DNT = 178635, // Visual when not attacking.
    };

    enum class Events : uint32
    {
        TORN_FEATHERS = 1,
        BEAT_LOW_BORN_DNT = 2
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new mob_SkyReachOverlordAI(creature);
    }

    struct mob_SkyReachOverlordAI : public ScriptedAI
    {
        mob_SkyReachOverlordAI(Creature* creature) : ScriptedAI(creature),
            m_Instance(creature->GetInstanceScript()),
            m_events()
        {
        }

        void Reset()
        {
            m_events.Reset();
        }

        void JustEngagedWith(Unit* /*who*/)
        {
            m_events.ScheduleEvent(uint32(Events::TORN_FEATHERS), urand(1000, 3000));
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            m_events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            switch (m_events.ExecuteEvent())
            {
            case uint32(Events::TORN_FEATHERS):
                m_events.ScheduleEvent(uint32(Events::TORN_FEATHERS), 125000);
                me->CastSpell(me, uint32(Spells::TORN_FEATHERS));
                break;
            default:
                break;
            }

            DoMeleeAttackIfReady();
        }

        InstanceScript* m_Instance;
        EventMap m_events;
    };
};

class mob_WindFamiliar : public CreatureScript
{
public:
    // Entry: 76102
    mob_WindFamiliar()
        : CreatureScript("mob_WindFamiliar")
    {
    }

    enum class Spells : uint32
    {
        SERENE = 153716,
        WIND_BURST = 157352,
    };

    enum class Events : uint32
    {
        WIND_BURST = 1,
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new mob_WindFamiliarAI(creature);
    }

    struct mob_WindFamiliarAI : public ScriptedAI
    {
        mob_WindFamiliarAI(Creature* creature) : ScriptedAI(creature),
            m_Instance(creature->GetInstanceScript()),
            m_events()
        {
        }

        void Reset()
        {
            m_events.Reset();
        }

        void JustDied(Unit* /*killer*/)
        {
            // When dying, Serene aura release all the nearby friends from crowd-control.
            std::list<Unit*> targetList;
            float radius = 10.0f;

            Trinity::AnyFriendlyUnitInObjectRangeCheck check(me, me, radius);
            Trinity::UnitListSearcher<Trinity::AnyFriendlyUnitInObjectRangeCheck> searcher(me, targetList, check);
            Cell::VisitAllObjects(me, searcher, radius);

            for (Unit* unit : targetList)
            {
                if (unit)
                    unit->RemoveCharmAuras();
            }
        }

        void JustEngagedWith(Unit* /*who*/)
        {
            m_events.ScheduleEvent(uint32(Events::WIND_BURST), urand(4000, 6000));
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            m_events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            switch (m_events.ExecuteEvent())
            {
            case uint32(Events::WIND_BURST):
                m_events.ScheduleEvent(uint32(Events::WIND_BURST), urand(4000, 6000));
                me->CastSpell(me->GetVictim(), uint32(Spells::WIND_BURST));
                break;
            default:
                break;
            }
        }

        InstanceScript* m_Instance;
        EventMap m_events;
    };
};

class mob_SolarFamiliar : public CreatureScript
{
public:
    // Entry: 76097
    mob_SolarFamiliar()
        : CreatureScript("mob_SolarFamiliar")
    {
    }

    enum class Spells : uint32
    {
        EMPOWER = 159290,   // 2:40:45 - 2:40:52
        FLASH_BANG = 152953, // Something like every 10 seconds and when it dies.
    };

    enum class Events : uint32
    {
        EMPOWER = 1,
        FLASH_BANG = 2
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new mob_SolarFamiliarAI(creature);
    }

    struct mob_SolarFamiliarAI : public ScriptedAI
    {
        mob_SolarFamiliarAI(Creature* creature) : ScriptedAI(creature),
            m_Instance(creature->GetInstanceScript()),
            m_events()
        {
        }

        void Reset()
        {
            m_events.Reset();
        }

        void JustDied(Unit* /*killer*/)
        {
            // When Familiar dies, Flash Bang occures once again.
            me->CastSpell(me, uint32(Spells::FLASH_BANG));
        }

        void JustEngagedWith(Unit* /*who*/)
        {
            m_events.ScheduleEvent(uint32(Events::EMPOWER), urand(5000, 7000));
            m_events.ScheduleEvent(uint32(Events::FLASH_BANG), urand(5000, 8000));
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            m_events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            switch (m_events.ExecuteEvent())
            {
            case uint32(Events::FLASH_BANG):
                m_events.ScheduleEvent(uint32(Events::FLASH_BANG), urand(5000, 8000));
                me->CastSpell(me, uint32(Spells::FLASH_BANG));
                break;
            case uint32(Events::EMPOWER):
                m_events.ScheduleEvent(uint32(Events::EMPOWER), urand(5000, 7000));
                if (Unit* unit = SelectNearestFriendExcluededMe(me, 30.0f))
                    me->CastSpell(unit, uint32(Spells::EMPOWER));
                break;
            default:
                break;
            }
        }

        InstanceScript* m_Instance;
        EventMap m_events;
    };
};

class mob_SoaringChrakramMaster : public CreatureScript
{
public:
    // Entry: 76132
    mob_SoaringChrakramMaster()
        : CreatureScript("mob_SoaringChrakramMaster")
    {
    }

    enum class Spells : uint32
    {
        THROW_CHAKRAM_YELLOW = 169689,  // 2:40:57 - 2:40:58 2:41:00 - 2:41:06
        THROW_CHAKRAM_WHITE = 169690,   // 2:40:48 - 2:40:52 - 2:40:56 - 2:40:57
        THROW_CHAKRAM_2 = 169687,       // Launched with the two previous ones.
        THROW_CHAKRAM_DNT = 178612,
        SPINNING_BLADE = 153544,    // 2:40:16 - 2:40:35
        BLADE_DANCE = 153581,       // 2:40:56 - 2:41:17
    };

    enum class Events : uint32
    {
        THROW_CHAKRAM = 1,
        SPINNING_BLADE = 2,
        BLADE_DANCE = 3,
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new mob_SoaringChrakramMasterAI(creature);
    }

    struct mob_SoaringChrakramMasterAI : public ScriptedAI
    {
        mob_SoaringChrakramMasterAI(Creature* creature) : ScriptedAI(creature),
            m_Instance(creature->GetInstanceScript()),
            m_events()
        {
        }

        void Reset()
        {
            m_events.Reset();
        }

        void JustEngagedWith(Unit* /*who*/)
        {
            m_events.ScheduleEvent(uint32(Events::THROW_CHAKRAM), urand(2000, 3000));
            m_events.ScheduleEvent(uint32(Events::SPINNING_BLADE), urand(8000, 10000));
            m_events.ScheduleEvent(uint32(Events::BLADE_DANCE), urand(17000, 25000));
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            m_events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            switch (m_events.ExecuteEvent())
            {
            case uint32(Events::THROW_CHAKRAM):
                m_events.ScheduleEvent(uint32(Events::THROW_CHAKRAM), urand(2000, 3000));

                if (urand(0, 1) == 0)
                {
                    if (Player* plr = SelectFarEnoughPlayerIncludedTank(me, 5.0f))
                        me->CastSpell(plr, uint32(Spells::THROW_CHAKRAM_YELLOW));
                }
                else
                {
                    if (Player* plr = SelectFarEnoughPlayerIncludedTank(me, 5.0f))
                        me->CastSpell(plr, uint32(Spells::THROW_CHAKRAM_WHITE));
                }
                me->CastSpell(me->GetVictim(), uint32(Spells::THROW_CHAKRAM_2)); // Always launched with the two others.
                break;
            case uint32(Events::SPINNING_BLADE):
                m_events.ScheduleEvent(uint32(Events::SPINNING_BLADE), urand(8000, 10000));
                if (Player* plr = SelectRandomPlayerIncludedTank(me, 45.0f))
                    me->CastSpell(plr, uint32(Spells::SPINNING_BLADE));
                break;
            case uint32(Events::BLADE_DANCE):
                m_events.ScheduleEvent(uint32(Events::BLADE_DANCE), urand(17000, 25000));
                me->CastSpell(me->GetVictim(), uint32(Spells::BLADE_DANCE));
                break;
            default:
                break;
            }

            DoMeleeAttackIfReady();
        }

        InstanceScript* m_Instance;
        EventMap m_events;
    };
};

class mob_HeraldOfSunrise : public CreatureScript
{
public:
    // Entry: 78933
    mob_HeraldOfSunrise()
        : CreatureScript("mob_HeraldOfSunrise")
    {
    }

    enum class Spells : uint32
    {
        SOLAR_ZONE = 163330,    // 2:40:57 - 2:41:11
        MAGMA_EXPLOSION_SUPREME = 152864, // -FIXME: NOT WORKING
        SOLAR_HEAL = 152893,    // 2:41:08
        FLASH_HEAL = 152894,
    };

    enum class Events : uint32
    {
        SOLAR_ZONE = 1,
        SOLAR_HEAL = 2,
        FLASH_HEAL = 3
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new mob_HeraldOfSunriseAI(creature);
    }

    struct mob_HeraldOfSunriseAI : public ScriptedAI
    {
        mob_HeraldOfSunriseAI(Creature* creature) : ScriptedAI(creature),
            m_Instance(creature->GetInstanceScript()),
            m_events()
        {
        }

        void Reset()
        {
            m_events.Reset();
        }

        void JustEngagedWith(Unit* /*who*/)
        {
            m_events.ScheduleEvent(uint32(Events::SOLAR_ZONE), urand(14500, 17000));
            m_events.ScheduleEvent(uint32(Events::SOLAR_HEAL), urand(5500, 7000));
            m_events.ScheduleEvent(uint32(Events::FLASH_HEAL), urand(5500, 7000));
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            m_events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            switch (m_events.ExecuteEvent())
            {
            case uint32(Events::SOLAR_ZONE):
                m_events.ScheduleEvent(uint32(Events::SOLAR_ZONE), urand(14500, 17000));
                if (Unit* unit = SelectNearestFriendExcluededMe(me, 30.0f))
                    me->CastSpell(unit, uint32(Spells::SOLAR_ZONE));
                break;
            case uint32(Events::SOLAR_HEAL):
                m_events.ScheduleEvent(uint32(Events::SOLAR_HEAL), urand(5500, 7000));
                if (Unit* unit = SelectNearestFriendExcluededMe(me, 30.0f))
                    me->CastSpell(unit, uint32(Spells::SOLAR_HEAL));
                break;
            case uint32(Events::FLASH_HEAL):
                m_events.ScheduleEvent(uint32(Events::FLASH_HEAL), urand(5500, 7000));
                me->CastSpell(me, uint32(Spells::FLASH_HEAL));
                break;
            default:
                break;
            }

            DoMeleeAttackIfReady();
        }

        InstanceScript* m_Instance;
        EventMap m_events;
    };
};

// Entry: 77605
class mob_WhirlingDervish : public CreatureScript
{
public:
    mob_WhirlingDervish() : CreatureScript("mob_WhirlingDervish") { }

    enum class Spells : uint32
    {
        STORM = 156515,
        DERVISH = 153905,
    };

    enum class Events : uint32
    {
        STORM = 1,
        DERVISH = 2
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new mob_WhirlingDervishAI(creature);
    }

    struct mob_WhirlingDervishAI : public ScriptedAI
    {
        mob_WhirlingDervishAI(Creature* creature) : ScriptedAI(creature),
            m_Instance(creature->GetInstanceScript()),
            m_events()
        {
        }

        void Reset()
        {
            m_events.Reset();
        }

        void JustEngagedWith(Unit* /*who*/)
        {
            m_events.ScheduleEvent(uint32(Events::STORM), urand(8000, 13000));
            m_events.ScheduleEvent(uint32(Events::DERVISH), urand(5500, 7000));
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            m_events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            switch (m_events.ExecuteEvent())
            {
            case uint32(Events::STORM):
                m_events.ScheduleEvent(uint32(Events::STORM), urand(8000, 13000));
                me->CastSpell(me, uint32(Spells::STORM));
                break;
            case uint32(Events::DERVISH):
                m_events.ScheduleEvent(uint32(Events::DERVISH), urand(5500, 7000));
                me->CastSpell(me, uint32(Spells::DERVISH));
                break;
            default:
                break;
            }

            DoMeleeAttackIfReady();
        }

        InstanceScript* m_Instance;
        EventMap m_events;
    };
};

class mob_BloodedBladeFeather : public CreatureScript
{
public:
    // Entry: 76205
    mob_BloodedBladeFeather()
        : CreatureScript("mob_BloodedBladeFeather")
    {
    }

    enum class Spells : uint32
    {
        PIERCING_RUSH = 165731,
        DESPAWN_AREA_TRIGGERS = 138175,
    };

    enum class Events : uint32
    {
        PIERCING_RUSH = 1
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new mob_BloodedBladeFeatherAI(creature);
    }

    struct mob_BloodedBladeFeatherAI : public ScriptedAI
    {
        mob_BloodedBladeFeatherAI(Creature* creature) : ScriptedAI(creature),
            m_Instance(creature->GetInstanceScript()),
            m_events()
        {
        }

        void Reset()
        {
            m_events.Reset();
        }

        void JustEngagedWith(Unit* /*who*/)
        {
            m_events.ScheduleEvent(uint32(Events::PIERCING_RUSH), urand(5000, 13000));
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            m_events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            switch (m_events.ExecuteEvent())
            {
            case uint32(Events::PIERCING_RUSH):
                m_events.ScheduleEvent(uint32(Events::PIERCING_RUSH), urand(5000, 13000));
                me->CastSpell(me->GetVictim(), uint32(Spells::PIERCING_RUSH));
                break;
            default:
                break;
            }

            DoMeleeAttackIfReady();
        }

        InstanceScript* m_Instance;
        EventMap m_events;
    };
};

class mob_InitiateOfTheRisingSun : public CreatureScript
{
public:
    // Entry: 79466
    mob_InitiateOfTheRisingSun()
        : CreatureScript("mob_InitiateOfTheRisingSun")
    {
    }

    enum class Spells : uint32
    {
        MAGMA_EXPLOSION_SUPREME = 152864, // FIXME: NOT WORKING, Didn't see it in the sniffs.
        SOLAR_SHOWER = 160274,          // Around 10 seconds.
        FLASH_HEAL = 152894,            // Around 6 seconds.
        CONJURE_SUN_ORB_DNT = 178618, // Visual to do when closed to sun orbs.
    };

    enum class Events : uint32
    {
        SOLAR_SHOWER = 1,
        FLASH_HEAL = 2
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new mob_InitiateOfTheRisingSunAI(creature);
    }

    struct mob_InitiateOfTheRisingSunAI : public ScriptedAI
    {
        mob_InitiateOfTheRisingSunAI(Creature* creature) : ScriptedAI(creature),
            m_Instance(creature->GetInstanceScript()),
            m_events()
        {
        }

        void Reset()
        {
            m_events.Reset();
        }

        void JustEngagedWith(Unit* /*who*/)
        {
            m_events.ScheduleEvent(uint32(Events::SOLAR_SHOWER), urand(8000, 13000));
            m_events.ScheduleEvent(uint32(Events::FLASH_HEAL), urand(5500, 7000));
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            m_events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            switch (m_events.ExecuteEvent())
            {
            case uint32(Events::SOLAR_SHOWER):
                m_events.ScheduleEvent(uint32(Events::SOLAR_SHOWER), urand(8000, 13000));
                me->CastSpell(me, uint32(Spells::SOLAR_SHOWER));
                break;
            case uint32(Events::FLASH_HEAL):
                m_events.ScheduleEvent(uint32(Events::FLASH_HEAL), urand(5500, 7000));
                me->CastSpell(me, uint32(Spells::FLASH_HEAL));
                break;
            default:
                break;
            }

            DoMeleeAttackIfReady();
        }

        InstanceScript* m_Instance;
        EventMap m_events;
    };
};

class mob_DivingChakramSpinner : public CreatureScript
{
public:
    // Entry: 76116
    mob_DivingChakramSpinner()
        : CreatureScript("mob_DivingChakramSpinner")
    {
    }

    enum class Spells : uint32
    {
        THROW_CHAKRAM_YELLOW = 169689,  // 2:40:57 - 2:40:58 2:41:00 - 2:41:06
        THROW_CHAKRAM_WHITE = 169690,   // 2:40:48 - 2:40:52 - 2:40:56 - 2:40:57
        THROW_CHAKRAM_2 = 169687,       // Launched with the two previous ones.
        THROW_CHAKRAM_DNT = 178612,
        SPINNING_BLADE = 153544,    // 2:40:16 - 2:40:35
    };

    enum class Events : uint32
    {
        THROW_CHAKRAM = 1,
        SPINNING_BLADE = 2
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new mob_DivingChakramSpinnerAI(creature);
    }

    struct mob_DivingChakramSpinnerAI : public ScriptedAI
    {
        mob_DivingChakramSpinnerAI(Creature* creature) : ScriptedAI(creature),
            m_Instance(creature->GetInstanceScript()),
            m_events()
        {
        }

        void Reset()
        {
            m_events.Reset();
        }

        void JustEngagedWith(Unit* /*who*/)
        {
            m_events.ScheduleEvent(uint32(Events::THROW_CHAKRAM), urand(2000, 3000));
            m_events.ScheduleEvent(uint32(Events::SPINNING_BLADE), urand(8000, 10000));
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            m_events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            switch (m_events.ExecuteEvent())
            {
            case uint32(Events::THROW_CHAKRAM):
                m_events.ScheduleEvent(uint32(Events::THROW_CHAKRAM), urand(2000, 3000));

                if (urand(0, 1) == 0)
                {
                    if (Player* plr = SelectFarEnoughPlayerIncludedTank(me, 5.0f))
                        me->CastSpell(plr, uint32(Spells::THROW_CHAKRAM_YELLOW));
                }
                else
                {
                    if (Player* plr = SelectFarEnoughPlayerIncludedTank(me, 5.0f))
                        me->CastSpell(plr, uint32(Spells::THROW_CHAKRAM_WHITE));
                }
                me->CastSpell(me->GetVictim(), uint32(Spells::THROW_CHAKRAM_2)); // Always launched with the two others.
                break;
            case uint32(Events::SPINNING_BLADE):
                m_events.ScheduleEvent(uint32(Events::SPINNING_BLADE), urand(8000, 10000));
                if (Player* plr = SelectRandomPlayerIncludedTank(me, 45.0f))
                    me->CastSpell(plr, uint32(Spells::SPINNING_BLADE));
                break;
            default:
                break;
            }

            DoMeleeAttackIfReady();
        }

        InstanceScript* m_Instance;
        EventMap m_events;
    };
};

class mob_BlindingSolarFlare : public CreatureScript
{
public:
    // Entry: 79462
    mob_BlindingSolarFlare()
        : CreatureScript("mob_BlindingSolarFlare")
    {
    }

    enum class Spells : uint32
    {
        SOLAR_WRATH = 157020,           // 2:40:56 - 2:41:00 - 2:41:05 - 2:41:08
        SOLAR_DETONATION_2 = 160282,      // 2:41:05
        SOLAR_DETONATION = 160288,    // 2:40:59 - 2:41:12
    };

    enum class Texts : int32
    {
        SOLAR_DETONATION = 14061,
    };

    enum class Events : uint32
    {
        SOLAR_WRATH = 1,
        SOLAR_DETONATION = 2
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new mob_BlindingSolarFlareAI(creature);
    }

    struct mob_BlindingSolarFlareAI : public ScriptedAI
    {
        mob_BlindingSolarFlareAI(Creature* creature) : ScriptedAI(creature),
            m_Instance(creature->GetInstanceScript()),
            m_events()
        {
        }

        void Reset()
        {
            m_events.Reset();
        }

        void JustEngagedWith(Unit* /*who*/)
        {
            m_events.ScheduleEvent(uint32(Events::SOLAR_WRATH), urand(3000, 5000));
            m_events.ScheduleEvent(uint32(Events::SOLAR_DETONATION), urand(10000, 14000));
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            m_events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            switch (m_events.ExecuteEvent())
            {
            case uint32(Events::SOLAR_WRATH):
                m_events.ScheduleEvent(uint32(Events::SOLAR_WRATH), urand(3000, 5000));
                me->CastSpell(me->GetVictim(), uint32(Spells::SOLAR_WRATH));
                break;
            case uint32(Events::SOLAR_DETONATION):
                m_events.ScheduleEvent(uint32(Events::SOLAR_DETONATION), urand(10000, 14000));
                if (Player* plr = SelectRandomPlayerIncludedTank(me, 45.0f))
                {
                    me->CastSpell(plr, uint32(Spells::SOLAR_DETONATION));
                    plr->Whisper(int32(Texts::SOLAR_DETONATION), plr, true);
                }
                break;
            default:
                break;
            }

            DoMeleeAttackIfReady();
        }

        InstanceScript* m_Instance;
        EventMap m_events;
    };
};

// AreaTriggers for spells: 152973
class AreaTrigger_ProtectiveBarrier : public AreaTriggerEntityScript
{
public:
    AreaTrigger_ProtectiveBarrier()
        : AreaTriggerEntityScript("at_ProtectiveBarrier")
    {
    }

    struct AreaTrigger_ProtectiveBarrierAI : AreaTriggerAI
    {
        AreaTrigger_ProtectiveBarrierAI(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger) {}


        enum class Spells : uint32
        {
            ProtectiveBarrier = 152975,
            ProtectiveBarrier_at = 152973,
        };

        std::list<ObjectGuid> m_Targets;

        void OnRemove() override
        {
            for (auto guid : m_Targets)
            {
                Unit* target = ObjectAccessor::GetUnit(*at, guid);
                if (target && target->HasAura(uint32(Spells::ProtectiveBarrier)))
                    target->RemoveAura(uint32(Spells::ProtectiveBarrier));
            }
        }

        void OnUpdate(uint32 /*time*/) override
        {
            std::list<Unit*> targetList;
            float radius = 30.0f;

            Trinity::AnyFriendlyUnitInObjectRangeCheck check(at, at->GetCaster(), radius);
            Trinity::UnitListSearcher<Trinity::AnyFriendlyUnitInObjectRangeCheck> searcher(at, targetList, check);
            Cell::VisitAllObjects(at, searcher, radius);

            std::list<ObjectGuid> toRemove; // We need to do it in two phase, otherwise it will break iterators.
            for (auto guid : m_Targets)
            {
                Unit* target = ObjectAccessor::GetUnit(*at, guid);
                if (target && target->GetExactDist2d(at) > radius)
                {
                    if (target->HasAura(uint32(Spells::ProtectiveBarrier)))
                    {
                        toRemove.emplace_front(guid);
                        target->RemoveAura(uint32(Spells::ProtectiveBarrier));
                    }
                }
            }

            for (auto guid : toRemove)
            {
                m_Targets.remove(guid);
            }

            for (Unit* unit : targetList)
            {
                if (!unit
                    || unit->GetExactDist2d(at) > radius
                    || unit->HasAura(uint32(Spells::ProtectiveBarrier))
                    || unit->HasAura(uint32(Spells::ProtectiveBarrier_at)))
                    continue;

                at->GetCaster()->CastSpell(unit, uint32(Spells::ProtectiveBarrier), true);
                m_Targets.emplace_front(unit->GetGUID());
            }
        }
    };

    AreaTriggerAI* GetAI(AreaTrigger* areatrigger) const override
    {
        return new AreaTrigger_ProtectiveBarrierAI(areatrigger);
    }
};






// Flash Bang - 160066
class spell_FlashBang : public SpellScriptLoader
{
public:
    spell_FlashBang()
        : SpellScriptLoader("spell_FlashBang")
    {
    }

    enum class Spells : uint32
    {
    };

    class spell_FlashBangSpellScript : public SpellScript
    {
        PrepareSpellScript(spell_FlashBangSpellScript)

            void CheckTarget(std::list<WorldObject*>& unitList)
        {
            Unit* caster = GetCaster();
            unitList.remove_if([caster](WorldObject* obj) {
                return !obj->isInFront(caster);
            });
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_FlashBangSpellScript::CheckTarget, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_FlashBangSpellScript::CheckTarget, EFFECT_1, TARGET_UNIT_SRC_AREA_ENEMY);
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_FlashBangSpellScript::CheckTarget, EFFECT_2, TARGET_UNIT_SRC_AREA_ENEMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_FlashBangSpellScript();
    }
};






// AreaTriggers for spells: 159221
class areatrigger_solar_storm : public AreaTriggerEntityScript
{
public:

    areatrigger_solar_storm() : AreaTriggerEntityScript("areatrigger_solar_storm") { }

    struct areatrigger_solar_stormAI : AreaTriggerAI
    {
        areatrigger_solar_stormAI(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger) {}

        enum eSolarStromSpells
        {
            SOLAR_STORM_DAMAGE = 159226
        };

        std::set<ObjectGuid> m_Targets;

        void OnUpdate(uint32 /*time*/) override
        {
            if (Unit* caster = at->GetCaster())
            {
                std::list<Player*> playerList;
                at->GetPlayerListInGrid(playerList, 5.0f);

                std::set<ObjectGuid> targets;

                for (Player* player : playerList)
                {
                    targets.insert(player->GetGUID());

                    if (!player->HasAura(eSolarStromSpells::SOLAR_STORM_DAMAGE))
                    {
                        m_Targets.insert(player->GetGUID());
                        player->CastSpell(player, eSolarStromSpells::SOLAR_STORM_DAMAGE);
                    }
                }

                for (std::set<ObjectGuid>::iterator player = m_Targets.begin(); player != m_Targets.end();)
                {
                    if (targets.find((*player)) != targets.end())
                    {
                        ++player;
                        continue;
                    }

                    if (Unit* unit = ObjectAccessor::GetUnit(*caster, (*player)))
                    {
                        player = m_Targets.erase(player);
                        unit->RemoveAura(eSolarStromSpells::SOLAR_STORM_DAMAGE);

                        continue;
                    }

                    ++player;
                }
            }
        }

        void OnRemove() override
        {
            if (m_Targets.empty())
                return;

            for (ObjectGuid guid : m_Targets)
            {
                Unit* target = ObjectAccessor::GetUnit(*at, guid);
                if (target && target->HasAura(eSolarStromSpells::SOLAR_STORM_DAMAGE))
                    target->RemoveAura(eSolarStromSpells::SOLAR_STORM_DAMAGE);
            }
        }
    };

    AreaTriggerAI* GetAI(AreaTrigger* areatrigger) const override
    {
        return new areatrigger_solar_stormAI(areatrigger);
    }
};

// Solar storm - 159215
class spell_SolarStorm : public SpellScriptLoader
{
public:
    spell_SolarStorm()
        : SpellScriptLoader("spell_SolarStorm")
    {
    }

    enum class Spells : uint32
    {
        SOLAR_STORM = 159215, // FIXME.
        SOLAR_STORM_1 = 159216,
        SOLAR_STORM_2 = 159218,
        SOLAR_STORM_3 = 159221,
        SOLAR_STORM_4 = 159226,
    };

    class spell_SolarStorm_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_SolarStorm_SpellScript)

            void HandleDummy(SpellEffIndex /*effIndex*/)
        {
            if (GetHitUnit() && GetCaster())
                GetCaster()->CastSpell(GetHitUnit(), uint32(Spells::SOLAR_STORM_1), true);
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_SolarStorm_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_SolarStorm_SpellScript();
    }
};

// AreaTriggers for spell 153583
class areatrigger_spinning_blade : public AreaTriggerEntityScript
{
public:

    areatrigger_spinning_blade() : AreaTriggerEntityScript("areatrigger_spinning_blade") { }

    struct areatrigger_spinning_bladeAI : AreaTriggerAI
    {
        areatrigger_spinning_bladeAI(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger) {}

        enum eSpinningBladeSpells
        {
            SPINNING_BLADE_DMG = 153123
        };

        std::set<ObjectGuid> m_Targets;

        void OnInitialize() override
        {
            Unit* caster = at->GetCaster();
            if (!caster)
                return;

            Position pos = caster->GetPosition();
            at->MovePositionToFirstCollision(pos, 30.0f, caster->GetOrientation());
            at->SetDestination(pos, 15000);
        }

        void OnUpdate(uint32 /*time*/) override
        {
            if (Unit* caster = at->GetCaster())
            {
                std::list<Player*> playerList;

                Trinity::AnyPlayerInObjectRangeCheck check(at, 2.0f);
                Trinity::PlayerListSearcher<Trinity::AnyPlayerInObjectRangeCheck> searcher(at, playerList, check);
                Cell::VisitAllObjects(at, searcher, 2.0f);

                std::set<ObjectGuid> targets;

                for (Player* player : playerList)
                {
                    targets.insert(player->GetGUID());

                    if (!player->HasAura(eSpinningBladeSpells::SPINNING_BLADE_DMG))
                    {
                        m_Targets.insert(player->GetGUID());
                        player->CastSpell(player, eSpinningBladeSpells::SPINNING_BLADE_DMG);
                    }

                    if (Player* plr = player->ToPlayer())
                    {
                        // We check if the caster is Ranjit.
                        if (at->GetInstanceScript() && at->GetCaster()->GetEntry() == BossEntries::RANJIT)
                            at->GetInstanceScript()->SetGuidData(Data::PlayerIsHittedByRanjitSpells, plr->GetGUID());
                    }
                }

                for (std::set<ObjectGuid>::iterator player = m_Targets.begin(); player != m_Targets.end();)
                {
                    if (targets.find((*player)) != targets.end())
                    {
                        ++player;
                        continue;
                    }

                    if (Unit* unit = ObjectAccessor::GetUnit(*caster, (*player)))
                    {
                        player = m_Targets.erase(player);
                        unit->RemoveAura(eSpinningBladeSpells::SPINNING_BLADE_DMG);

                        continue;
                    }

                    ++player;
                }
            }
        }

        void OnRemove() override
        {
            if (m_Targets.empty())
                return;

            for (ObjectGuid guid : m_Targets)
            {
                Unit* target = ObjectAccessor::GetUnit(*at, guid);
                if (target && target->HasAura(eSpinningBladeSpells::SPINNING_BLADE_DMG))
                    target->RemoveAura(eSpinningBladeSpells::SPINNING_BLADE_DMG);
            }
        }
    };

    AreaTriggerAI* GetAI(AreaTrigger* areatrigger) const override
    {
        return new areatrigger_spinning_bladeAI(areatrigger);
    }
};

// AreaTriggers for spells: 160935
class AreaTrigger_solar_zone : public AreaTriggerEntityScript
{

public:
    AreaTrigger_solar_zone()
        : AreaTriggerEntityScript("at_solar_zone") {}

    struct AreaTrigger_solar_zoneAI : AreaTriggerAI
    {
        AreaTrigger_solar_zoneAI(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger) {}

        enum class SolarHealSpells : uint32
        {
            SOLAR_ZONE_1 = 160935,
            SOLAR_ZONE_HEAL = 160281,
            SOLAR_ZONE_DMG = 158441,
        };

        std::list<ObjectGuid> m_Targets;

        void OnRemove() override
        {
            for (auto guid : m_Targets)
            {
                Unit* target = ObjectAccessor::GetUnit(*at, guid);
                if (target && target->HasAura(uint32(SolarHealSpells::SOLAR_ZONE_HEAL)))
                    target->RemoveAura(uint32(SolarHealSpells::SOLAR_ZONE_HEAL));

                if (target && target->HasAura(uint32(SolarHealSpells::SOLAR_ZONE_DMG)))
                    target->RemoveAura(uint32(SolarHealSpells::SOLAR_ZONE_DMG));
            }
        }

        void OnUpdate(uint32 /*time*/) override
        {
            std::list<Unit*> targetList;
            float radius = 6.0f;

            Trinity::AnyUnitInObjectRangeCheck check(at, radius);
            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(at, targetList, check);
            Cell::VisitAllObjects(at, searcher, radius);

            std::list<ObjectGuid> toRemove; // We need to do it in two phase, otherwise it will break iterators.
            for (auto unit : targetList)
            {
                ObjectGuid guid = unit->GetGUID();
                Unit* target = ObjectAccessor::GetUnit(*at, guid);
                if (target && target->GetExactDist2d(at) > radius)
                {
                    if (target->HasAura(uint32(SolarHealSpells::SOLAR_ZONE_HEAL)))
                    {
                        toRemove.emplace_front(guid);
                        target->RemoveAura(uint32(SolarHealSpells::SOLAR_ZONE_HEAL));
                    }
                    if (target->HasAura(uint32(SolarHealSpells::SOLAR_ZONE_DMG)))
                    {
                        toRemove.emplace_front(guid);
                        target->RemoveAura(uint32(SolarHealSpells::SOLAR_ZONE_DMG));
                    }
                }
            }

            for (auto guid : toRemove)
            {
                m_Targets.remove(guid);
            }

            for (Unit* unit : targetList)
            {
                if (!unit || unit->GetExactDist2d(at) > radius)
                    continue;

                if (unit->IsFriendlyTo(at->GetCaster()) && !unit->HasAura(uint32(SolarHealSpells::SOLAR_ZONE_HEAL)))
                {
                    at->GetCaster()->CastSpell(unit, uint32(SolarHealSpells::SOLAR_ZONE_HEAL), true);
                    m_Targets.emplace_front(unit->GetGUID());
                }
                else if (!unit->IsFriendlyTo(at->GetCaster()) && !unit->HasAura(uint32(SolarHealSpells::SOLAR_ZONE_DMG)))
                {
                    at->GetCaster()->CastSpell(unit, uint32(SolarHealSpells::SOLAR_ZONE_DMG), true);
                    m_Targets.emplace_front(unit->GetGUID());
                }
            }
        }
    };

    AreaTriggerAI* GetAI(AreaTrigger* areatrigger) const override
    {
        return new AreaTrigger_solar_zoneAI(areatrigger);
    }
};

// AreaTriggers for spells: 156840
class areatrigger_storm_zone : public AreaTriggerEntityScript
{
public:

    areatrigger_storm_zone() : AreaTriggerEntityScript("areatrigger_storm_zone") { }

    struct areatrigger_storm_zoneAI : AreaTriggerAI
    {
        areatrigger_storm_zoneAI(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger) {}

        enum eStormAreaTriggerSpells
        {
            STORM_DMG = 156841,
        };

        std::set<ObjectGuid> m_Targets;

        void OnUpdate(uint32 /*time*/) override
        {
            if (Unit* caster = at->GetCaster())
            {
                std::list<Player*> playerList;

                Trinity::AnyPlayerInObjectRangeCheck check(at, 2.0f);
                Trinity::PlayerListSearcher<Trinity::AnyPlayerInObjectRangeCheck> searcher(at, playerList, check);
                Cell::VisitAllObjects(at, searcher, 2.0f);

                std::set<ObjectGuid> targets;

                for (Player* player : playerList)
                {
                    targets.insert(player->GetGUID());

                    if (!player->HasAura(eStormAreaTriggerSpells::STORM_DMG))
                    {
                        m_Targets.insert(player->GetGUID());
                        player->CastSpell(player, eStormAreaTriggerSpells::STORM_DMG);
                    }
                }

                for (std::set<ObjectGuid>::iterator player = m_Targets.begin(); player != m_Targets.end();)
                {
                    if (targets.find((*player)) != targets.end())
                    {
                        ++player;
                        continue;
                    }

                    if (Unit* unit = ObjectAccessor::GetUnit(*caster, (*player)))
                    {
                        player = m_Targets.erase(player);
                        unit->RemoveAura(eStormAreaTriggerSpells::STORM_DMG);

                        continue;
                    }

                    ++player;
                }
            }
        }

        void OnRemove() override
        {
            if (m_Targets.empty())
                return;

            for (ObjectGuid guid : m_Targets)
            {
                Unit* target = ObjectAccessor::GetUnit(*at, guid);
                if (target && target->HasAura(eStormAreaTriggerSpells::STORM_DMG))
                    target->RemoveAura(eStormAreaTriggerSpells::STORM_DMG);
            }
        }
    };

    AreaTriggerAI* GetAI(AreaTrigger* areatrigger) const override
    {
        return new areatrigger_storm_zoneAI(areatrigger);
    }
};

// AreaTriggers for spells: 153905
class areatrigger_dervish : public AreaTriggerEntityScript
{
public:

    areatrigger_dervish() : AreaTriggerEntityScript("areatrigger_dervish") { }

    struct areatrigger_dervishAI : AreaTriggerAI
    {
        areatrigger_dervishAI(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger) {}

        enum eDervishSpells
        {
            DERVISH_DMG = 153907
        };

        std::set<ObjectGuid> m_Targets;

        void OnInitialize() override
        {
            Unit* caster = at->GetCaster();
            if (!caster)
                return;

            Position pos = caster->GetPosition();
            at->MovePositionToFirstCollision(pos, 30.0f, caster->GetOrientation());
            at->SetDestination(pos, 15000);
        }

        void OnUpdate(uint32 /*time*/) override
        {
            if (Unit* caster = at->GetCaster())
            {
                std::list<Player*> playerList;

                Trinity::AnyPlayerInObjectRangeCheck check(at, 2.0f);
                Trinity::PlayerListSearcher<Trinity::AnyPlayerInObjectRangeCheck> searcher(at, playerList, check);
                Cell::VisitAllObjects(at, searcher, 2.0f);

                for (Player* player : playerList)
                {
                    if (!player->HasAura(eDervishSpells::DERVISH_DMG))
                    {
                        m_Targets.insert(player->GetGUID());
                        player->CastSpell(player, eDervishSpells::DERVISH_DMG);
                    }

                }
            }
        }

        void OnRemove() override
        {
            if (m_Targets.empty())
                return;

            for (ObjectGuid guid : m_Targets)
            {
                Unit* target = ObjectAccessor::GetUnit(*at, guid);
                if (target && target->HasAura(eDervishSpells::DERVISH_DMG))
                    target->RemoveAura(eDervishSpells::DERVISH_DMG);
            }
        }
    };

    AreaTriggerAI* GetAI(AreaTrigger* areatrigger) const override
    {
        return new areatrigger_dervishAI(areatrigger);
    }
};

// Spinning Blade - 153544
class spell_SpinningBlade : public SpellScriptLoader
{
public:
    spell_SpinningBlade() : SpellScriptLoader("spell_SpinningBlade") { }

    class spell_SpinningBlade_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_SpinningBlade_SpellScript)

            enum eSpiningBladeSpells
        {
            SPINNING_BLADE_9 = 153583,
        };

        void HandleAfterCast()
        {
            if (Unit* caster = GetCaster())
            {
                if (Unit* target = GetCaster()->GetAI()->SelectTarget(SelectTargetMethod::MaxThreat))
                {
                    caster->CastSpell(target, eSpiningBladeSpells::SPINNING_BLADE_9);
                }
            }
        }

        void Register()
        {
            AfterCast += SpellCastFn(spell_SpinningBlade_SpellScript::HandleAfterCast);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_SpinningBlade_SpellScript();
    }
};

// Blade Dance - 153581
class spell_BladeDance : public SpellScriptLoader
{
public:
    spell_BladeDance() : SpellScriptLoader("spell_BladeDance") { }

    enum class Spells : uint32
    {
        // Those are for Blade Dance
        SPINNING_BLADE_4 = 153535,
        SPINNING_BLADE_5 = 153536,
        SPINNING_BLADE_6 = 153537,
        SPINNING_BLADE_7 = 153538,
    };

    class spell_BladeDance_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_BladeDance_SpellScript)

            void HandleDummy(SpellEffIndex /*effIndex*/)
        {
            if (GetCaster() && GetHitUnit())
            {
                GetCaster()->CastSpell(GetHitUnit(), uint32(Spells::SPINNING_BLADE_4), true);
                GetCaster()->SetOrientation(GetCaster()->GetOrientation() + float(M_PI) / 2);
                GetCaster()->CastSpell(GetHitUnit(), uint32(Spells::SPINNING_BLADE_5), true);
                GetCaster()->SetOrientation(GetCaster()->GetOrientation() + float(M_PI) / 2);
                GetCaster()->CastSpell(GetHitUnit(), uint32(Spells::SPINNING_BLADE_6), true);
                GetCaster()->SetOrientation(GetCaster()->GetOrientation() + float(M_PI) / 2);
                GetCaster()->CastSpell(GetHitUnit(), uint32(Spells::SPINNING_BLADE_7), true);
                GetCaster()->SetOrientation(GetCaster()->GetOrientation() + float(M_PI) / 2);
            }
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_BladeDance_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_BladeDance_SpellScript();
    }
};

// Storm - 156515
class spell_Storm : public SpellScriptLoader
{
public:
    spell_Storm() : SpellScriptLoader("spell_Storm") { }

    enum eStormSpells
    {
        STORM = 156515,
        STORM_AT = 156840,
        STORM_DMG = 156841
    };

    class spell_Storm_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_Storm_SpellScript)

            void HandleAfterCast()
        {
            if (Unit* caster = GetCaster())
            {
                if (Unit* target = GetCaster()->GetAI()->SelectTarget(SelectTargetMethod::MaxThreat))
                {
                    caster->CastSpell(target, eStormSpells::STORM_AT);
                }
            }
        }

        void Register()
        {
            AfterCast += SpellCastFn(spell_Storm_SpellScript::HandleAfterCast);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_Storm_SpellScript();
    }
};

// Solar Detonation (Aura) - 160288
class spell_solar_detonation : public SpellScriptLoader
{
public:
    spell_solar_detonation() : SpellScriptLoader("spell_solar_detonation") { }

    class spell_solar_detonation_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_solar_detonation_AuraScript);

        enum eSolarDetonationSpells
        {
            SOLAR_DETONATION_DAMAGE = 160282
        };

        void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            AuraRemoveMode removeMode = GetTargetApplication()->GetRemoveMode();
            if (removeMode != AuraRemoveMode::AURA_REMOVE_BY_EXPIRE)
                return;

            if (Unit* caster = GetCaster())
            {
                if (Unit* target = GetTarget())
                    caster->CastSpell(target, eSolarDetonationSpells::SOLAR_DETONATION_DAMAGE);
            }
        }

        void Register() override
        {
            OnEffectRemove += AuraEffectRemoveFn(spell_solar_detonation_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_solar_detonation_AuraScript();
    }
};

const Position DreadRavenPos[] =
{  // sometimes blizz sends this, but this is buggy
   // { 994.82306f, 1800.4653f, 294.93112 },
   // { 1000.9827f, 1872.9254f, 277.5583  },
   // { 1007.1424f, 1945.3855f, 260.18546 },
   // { 930.7465f, 1787.5538f, 260.03345 },
   // { 1005.809f, 1675.7396f, 242.29807 },
   // { 1059.743f, 1649.1354f, 219.11612 },
   // { 1097.4879f, 1672.4236f, 206.83957 },
   // { 1112.2639f, 1727.9115f, 189.91101 },
   // { 1130.5659f, 1751.6564f, 178.36351 },
   // { 1154.4548f, 1770.3716f, 169.0056  },
   // { 1183.3281f, 1777.6581f, 166.64786 },
   // { 1210.1788f, 1762.099f, 183.83516 },
   // { 1217.783f, 1757.342f, 189.47287 },
   // { 1217.783f, 1757.342f, 189.47287 },
    { 1002.0567f,  1871.5894f, 277.6579f},
    { 1007.1424f,  1945.3855f, 265.7238f},
    { 1043.257f,   1933.4341f, 235.55037f},
    { 1066.356f,   1928.6545f, 233.9754f},
    { 1085.2257f,  1914.2692f, 245.27501f},
    { 1100.8177f,  1899.3524f, 250.52097f},
    { 1121.3785f,  1874.6459f, 245.52116f},
    { 1145.066f,   1839.6459f, 235.76405f},
    { 1146.6875f,  1794.6685f, 219.75612f},
    { 1188.8403f,  1774.0226f, 210.45837f},
    { 1223.724f,   1750.3525f, 187.60385f},
};

const Position DreadRavenOutroPos[] =
{
    { 1166.776, 1839.9307, 189.97726 },
    { 1017.2066, 1932.842, 198.42015 },
};

const Position ReshadSpawnPos = { 1002.0567, 1871.5894, 277.6579 };
const Position JumpPos = { 1231.5219, 1747.4839, 177.16148 };

/// 1000.9827, 1872.9254, 277.5583, 1.4859924
struct npc_dread_raven_81204 : public VehicleAI
{
public:
    npc_dread_raven_81204(Creature* creature) : VehicleAI(creature) { }

    enum eSpells
    {
        Cloak = 165848,
        EjectPassenger1 = 60603,
    };

    void InitializeAI() override
    {
        me->SetDisableGravity(true);
        me->SetExtraUnitMovementFlags(MOVEMENTFLAG2_NO_STRAFE | MOVEMENTFLAG2_NO_JUMPING | MOVEMENTFLAG2_FULL_SPEED_TURNING | MOVEMENTFLAG2_FULL_SPEED_PITCHING);
        me->SetAnimTier(AnimTier::Fly, false);
        me->GetMotionMaster()->MoveSmoothPath(0, DreadRavenPos, 11, false, true, 15.99684)->callbackFunc = [this]()
        {
            DoCast(EjectPassenger1);

            if (auto tempSumm = me->ToTempSummon())
                if (auto unitOwner = tempSumm->GetOwner())
                    unitOwner->GetScheduler().Schedule(50ms, [this](TaskContext context)
                {
                    context.GetUnit()->CastSpell(JumpPos, JUMP_TO_JUMpoint, true);
                });

            scheduler.Schedule(1500ms, [this](TaskContext /*context*/)
            {
                me->GetMotionMaster()->MoveSmoothPath(0, DreadRavenOutroPos, 2, false, true, 7.499771f)->callbackFunc = [this]()
                {

                };
            });
        };
    }

    void UpdateAI(uint32 diff) override
    {
        scheduler.Update(diff);
    }

    void IsSummonedBy(WorldObject* who) override
    {
        if (auto unit = who->ToUnit())
        {
            // cast 46598
            unit->EnterVehicle(me);
            DoCast(eSpells::Cloak);
            // needed because of VehicleJoinEvent
            scheduler.Schedule(10ms, [this, unit](TaskContext /*context*/)
            {
                if (unit)
                    unit->CastSpell(ReshadSpawnPos, RandomSpells::INTRO_NARRATOR, true);
            });
        }
    }
};

struct npc_reshad_81273 : public ScriptedAI
{
public:
    npc_reshad_81273(Creature* creature) : ScriptedAI(creature) { }

    enum eTalks : uint32
    {
        TalkIntro1 = 0, ///< Ah, Skyreach. I have not been this close to her in many years.
        TalkIntro2,     ///< The High Sage will be well protected. We can fly no closer.
        TalkIntro3,     ///< Destroy their false sun, that we may meet again in the shade.
    };

    void InitializeAI() override
    {
        me->SetDisableGravity(true);
        me->SetExtraUnitMovementFlags(MOVEMENTFLAG2_NO_STRAFE | MOVEMENTFLAG2_NO_JUMPING | MOVEMENTFLAG2_FULL_SPEED_TURNING | MOVEMENTFLAG2_FULL_SPEED_PITCHING);
    }

    void UpdateAI(uint32 diff) override
    {
        scheduler.Update(diff);
    }

    void IsSummonedBy(WorldObject* who) override
    {
        if (auto unit = who->ToUnit())
        {
            // cast 46598
            if (auto vehicle = unit->GetVehicleBase())
                me->EnterVehicle(vehicle);

            scheduler.Schedule(3s, [this, unit](TaskContext /*context*/)
            {
                Talk(TalkIntro1, unit);

                scheduler.Schedule(11s, [this, unit](TaskContext /*context*/)
                {
                    Talk(TalkIntro2, unit);

                    scheduler.Schedule(9s, [this, unit](TaskContext /*context*/)
                    {
                        Talk(TalkIntro3, unit);
                    });
                });
            });
        }
    }
};

const Position WindMazeSpawnPos = { 1010.704f, 1923.7721f, 227.16031f, 2.530723f };
const QuaternionData WindMazeQ = { 0.0f, 0.0f, 0.9537163f, 0.3007079f };

struct npc_wind_76152 : public ScriptedAI
{
public:
    npc_wind_76152(Creature* creature) : ScriptedAI(creature) { }

    enum eWind
    {
        SetupWindRampA = 153622,
        WindMaze = 238852,
    };

    void InitializeAI() override
    {
        /// Setup all our areatriggers
        DoCastSelf(SetupWindRampA, true);
        me->SummonGameObject(WindMaze, WindMazeSpawnPos, WindMazeQ, 0s, GOSummonType::GO_SUMMON_TIMED_DESPAWN);
    }

    void UpdateAI(uint32 /*diff*/) override
    {

    }
};

const std::unordered_map<uint32, Position> AreaTriggerRelocatePositions =
{
     { 6313, { 1025.7179f,  1917.1328f, 225.0f, 2.544507f } },
     { 6316, { 1024.7979f,  1933.9662f, 225.0f, 2.544507f } },
     { 6444, { 1013.1467f,  1912.8689f, 225.0f, 2.544507f } },
     { 6319, { 1009.0156f,  1940.7865f, 225.0f, 2.544507f } },
     { 6447, { 1024.6841f,  1942.645f,  225.0f, 2.544507f } },
     { 6450, { 1000.283f,   1945.1997f, 225.0f, 2.544507f } },
     { 6453, { 988.05383f,  1926.5669f, 225.0f, 2.544507f } },
     { 6712, { 995.14496f,  1931.5521f, 225.0f, 2.544507f } },
     { 6315, { 1027.2614f,  1928.698f,  225.0f, 2.544507f } },
     { 6443, { 998.3429f,   1936.1875f, 225.0f, 2.544507f } },
     { 6318, { 1015.62415f, 1940.251f,  225.0f, 2.544507f } },
     { 6446, { 1017.67535f, 1945.9548f, 225.0f, 2.544507f } },
     { 6452, { 989.6875f,   1934.3906f, 225.0f, 2.544507f } },
     { 6308, { 1006.0834f,  1905.5312f, 220.0f, 2.544507f } },
     { 6449, { 1033.283f,   1925.7866f, 225.0f, 2.544507f } },
     { 6711, { 993.5834f,   1925.8013f, 225.0f, 2.544507f } },
     { 6314, { 996.56683f,  1913.8994f, 225.0f, 2.544507f } },
     { 6442, { 1003.1814f,  1939.5382f, 225.0f, 2.544507f } },
     { 6093, { 974.78125f,  1906.967f, 210.661f, 2.544507f } },
     { 6317, { 1020.61975f, 1937.6824f, 225.0f, 2.544507f } },
     { 6445, { 1009.0972f,  1946.7267f, 225.0f, 2.544507f } },
     { 6448, { 1030.0243f,  1937.2675f, 225.0f, 2.544507f } },
     { 6451, { 993.88806f,  1940.9324f, 225.0f, 2.544507f } },
     { 6454, { 990.28564f,  1914.1598f, 225.0f, 2.544507f } },
     { 6710, { 994.1649f,   1919.4783f, 225.0f, 2.544507f } },
};

struct at_skyreach_wind_maze : public AreaTriggerAI
{
public:
    at_skyreach_wind_maze(AreaTrigger* at) : AreaTriggerAI(at)
    {
        auto it = AreaTriggerRelocatePositions.find(at->GetEntry());
        if (it != AreaTriggerRelocatePositions.end())
            at->Relocate(it->second);
    }

    void OnUnitEnter(Unit* who) override
    {
        if (who->IsPlayer())
        {
            auto l_Plr = who->ToPlayer();
            if (IsPointInBlock(Blocks::ConvexHull, *l_Plr))
            {
                bool l_IsInBlock = false;
                uint32 i = Blocks::FirstStair;
                for (; i <= Blocks::SecondStair; i++)
                {
                    if (IsPointInBlock(i, *l_Plr))
                    {
                        l_IsInBlock = true;
                        break;
                    }
                }

                // If the player is in one of the blocks and if it doesn't have the Wind aura, add it.
                if (l_IsInBlock)
                {
                    float l_Magnitude = 1;
                    Position l_ForceDir = CalculateForceVectorFromBlockId(i, l_Magnitude);
                    l_Plr->CastSpell(l_Plr, RandomSpells::Wind, true);
                    l_Plr->ApplyMovementForce(at->GetGUID(), *at, l_Magnitude, MovementForceType::SingleDirectional, l_ForceDir);
                }
            }
        }
    }

    void OnUnitExit(Unit* who) override
    {
        if (who->IsPlayer())
        {
            who->RemoveMovementForce(at->GetGUID());
            who->RemoveAura(RandomSpells::Wind);
        }
    }
};

void AddSC_skyreach()
{
    // Mobs.
    new mob_BlindingSolarFlare();
    new mob_DivingChakramSpinner();
    new mob_InitiateOfTheRisingSun();
    new mob_WhirlingDervish();
    new mob_BloodedBladeFeather();
    new mob_HeraldOfSunrise();
    new mob_SoaringChrakramMaster();
    new mob_SolarFamiliar();
    new mob_SkyReachOverlord();
    new mob_AdeptOfTheDawn();
    new mob_WindFamiliar();
    new mob_DrivingGaleCaller();
    new mob_AdornedBladetalon();
    new mob_SkyreachSunTalon();
    new mob_DreadRavenHatchling();
    new mob_SolarMagnifier();
    new mob_DefenseConstruct();
    new mob_RadiantSupernova();
    new mob_YoungKaliri();
    new mob_GrandDefenseConstruct();
    RegisterCreatureAI(npc_GossipIntroOutro);
    RegisterCreatureAI(npc_reshad_81273);
    RegisterCreatureAI(npc_dread_raven_81204);
    RegisterCreatureAI(npc_wind_76152);

    // Spells.
    new spell_SpinningBlade();
    new spell_Storm();
    new spell_BladeDance();
    new spell_SolarStorm();
    new spell_FlashBang();
    new spell_solar_detonation();

    //Areatrigers
    new AreaTrigger_solar_zone();
    new areatrigger_spinning_blade();
    new AreaTrigger_ProtectiveBarrier();
    new areatrigger_solar_storm();
    new areatrigger_storm_zone();
    new areatrigger_dervish();

    RegisterAreaTriggerAI(at_skyreach_wind_maze);
}

