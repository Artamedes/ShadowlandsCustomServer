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
#include "Vehicle.h"





class mob_SkyreachShieldConstruct : public CreatureScript
{
public:
    // Entry: 76292
    mob_SkyreachShieldConstruct()
        : CreatureScript("mob_SkyreachShieldConstruct")
    {
    }

    enum class Spells : uint32
    {
        Shielding = 154055,
        Submerged = 154163,
    };

    enum class Events : uint32
    {
        Shielding = 1,
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new mob_SkyreachShieldConstructAI(creature);
    }

    struct mob_SkyreachShieldConstructAI : public ScriptedAI
    {
        mob_SkyreachShieldConstructAI(Creature* creature) : ScriptedAI(creature),
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
            me->RemoveAura(uint32(Spells::Submerged));
            m_events.ScheduleEvent(uint32(Events::Shielding), 5000);
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
            case uint32(Events::Shielding):
                m_events.ScheduleEvent(uint32(Events::Shielding), 5000);
                me->CastSpell(me, uint32(Spells::Shielding));
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

static const std::size_t k_NumFallPoints = 13;
static const Position k_FallPoints[k_NumFallPoints] =
{
    { 1094.775f, 1715.610f, 275.72f},
    { 1094.993f, 1721.900f, 263.72f},
    { 1104.928f, 1724.705f, 263.72f},
    { 1141.754f, 1729.700f, 263.72f},
    { 1123.270f, 1735.448f, 263.72f},
    { 1132.028f, 1744.517f, 263.72f},
    { 1138.780f, 1753.942f, 263.72f},
    { 1144.525f, 1764.297f, 263.72f},
    { 1147.478f, 1773.486f, 263.72f},
    { 1149.241f, 1785.068f, 263.72f},
    { 1148.452f, 1798.171f, 263.72f},
    { 1146.030f, 1811.055f, 263.72f},
    { 1140.494f, 1822.770f, 263.72f}
};

class mob_SolarZealot : public CreatureScript
{
public:
    // Entry: 76267
    mob_SolarZealot()
        : CreatureScript("mob_SolarZealot")
    {
    }

    enum class Spells : uint32
    {
        JumpChargeDemonCreatorRideMe = 165834,
        ForceDemonCreatorToRideMe = 136522,
    };

    enum class Moves : uint32
    {
        ArrivedAtDestination = 0xBAB,
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new mob_SolarZealotAI(creature);
    }

    struct mob_SolarZealotAI : public ScriptedAI
    {
        mob_SolarZealotAI(Creature* creature) : ScriptedAI(creature),
            m_Reset(false)
        {
            me->SetSpeed(UnitMoveType::MOVE_WALK, 0.3f);
            me->SetSpeed(UnitMoveType::MOVE_RUN, 0.3f);
            me->SetSpeed(UnitMoveType::MOVE_FLIGHT, 0.3f);
        }

        void Reset()
        {
            events.Reset();
            m_Reset = true;
        }

        void MovementInform(uint32 type, uint32 id)
        {
            if (type != POINT_MOTION_TYPE)
                return;

            if (me->GetVehicle())
                me->GetVehicle()->RemoveAllPassengers();

            me->DespawnOrUnsummon();
        };

        void UpdateAI(const uint32 diff)
        {
            events.Update(diff);

            if (m_Reset)
            {
                m_Reset = false;
                if (me->ToTempSummon() && me->ToTempSummon()->GetSummoner() && me->ToTempSummon()->GetSummoner()->IsUnit())
                {
                    me->ToTempSummon()->GetSummoner()->ToUnit()->EnterVehicle(me, 0);
                }

                int l_ClosestPoint = 0;
                float closestDistance = k_FallPoints[0].GetExactDist2d(me);
                for (int i = 1; i < k_NumFallPoints; i++)
                {
                    if (k_FallPoints[i].GetExactDist2d(me) < closestDistance)
                    {
                        closestDistance = k_FallPoints[i].GetExactDist2d(me);
                        l_ClosestPoint = i;
                    }
                }

                me->GetMotionMaster()->MovePoint(uint32(Moves::ArrivedAtDestination), k_FallPoints[l_ClosestPoint], false);
            }
        }

        bool m_Reset;
    };
};

class mob_ArakkoaMagnifyingGlassFocus : public CreatureScript
{
public:
    // Entry: 76083
    mob_ArakkoaMagnifyingGlassFocus()
        : CreatureScript("mob_ArakkoaMagnifyingGlassFocus")
    {
    }

    enum class Spells : uint32
    {
        LensFlare = 154044,
    };

    enum class Events : uint32
    {
        LensFlare = 1,
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new mob_ArakkoaMagnifyingGlassFocusI(creature);
    }

    struct mob_ArakkoaMagnifyingGlassFocusI : public ScriptedAI
    {
        mob_ArakkoaMagnifyingGlassFocusI(Creature* creature) : ScriptedAI(creature)
        {
            me->SetSpeed(UnitMoveType::MOVE_WALK, 0.9f);
            me->SetSpeed(UnitMoveType::MOVE_RUN, 0.9f);
            me->SetSpeed(UnitMoveType::MOVE_FLIGHT, 0.9f);
        }

        void Reset()
        {
            events.Reset();
            events.ScheduleEvent(uint32(Events::LensFlare), 100);

            if (me->GetInstanceScript())
                me->GetInstanceScript()->SetData(Data::StartingLensFlare, 0);
        }

        void UpdateAI(const uint32 diff)
        {
            events.Update(diff);

            if (events.ExecuteEvent() == uint32(Events::LensFlare))
            {
                if (me->ToTempSummon())
                {
                    if (me->ToTempSummon()->GetSummoner())
                    {
                        Position pos = *me->ToTempSummon()->GetSummoner();
                        pos.m_positionZ -= 1.5f;
                        me->GetMotionMaster()->MovePoint(0, pos);
                    }
                }
                events.ScheduleEvent(uint32(Events::LensFlare), 500);
            }
        }

        bool m_Reset;
    };
};

class boss_HighSageViryx : public CreatureScript
{
public:
    // Entry: 76266
    boss_HighSageViryx()
        : CreatureScript("boss_HighSageViryx")
    {
    }

    enum class Spells : uint32
    {
        CastDown = 156789,
        CastDown_Summon = 153955,
        CastDown_Visual = 165845,
        CastDown_2 = 153954,
        LensFlare = 154029,
        LensFlare_At = 154044,
        LensFlare_Dmg = 154043,
        SolarBurst = 154396,
        CallAdds = 154049,
    };

    enum class Texts : int32
    {
        CombatStart = -1603209,
        JustDied = -1603210,
        SpellCastDown = -1603211,
        SpellCallAdds = -1603212,
        SpellLensFlare = -1603216,
        KilledUnitA = -1603213,
        KilledUnitB = -1603214,
        Victory = -1603215,
    };

    enum class Events : uint32
    {
        LensFlare = 1,
        CastDown = 2,
        SolarBurst = 3,
        CallAdds = 4,
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_HighSageViryxAI(creature);
    }

    struct boss_HighSageViryxAI : public BossAI
    {
        boss_HighSageViryxAI(Creature* creature) : BossAI(creature, Data::HighSageViryx)
        {
        }

        void Reset()
        {
            _Reset();
        }

        void JustReachedHome()
        {
            _JustReachedHome();

            //DoScriptText(int32(Texts::Victory), me);
            if (instance)
            {
                instance->SetBossState(Data::HighSageViryx, FAIL);
                instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            }
        }

        void JustDied(Unit* /*killer*/)
        {
            _JustDied();

            me->CastSpell(me, RandomSpells::DespawnAreaTriggers, true);

            //DoScriptText(int32(Texts::JustDied), me);
            if (instance)
                instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);

            ApplyOnEveryPlayer(me, [](Unit* /*me*/, Player* plr) {
                if (plr)
                    plr->RemoveAura(uint32(Spells::LensFlare_Dmg));
            });
        }

        //void KilledUnit(Unit* /*victim*/)
        //{
        //    if (urand(0, 1))
        //        DoScriptText(int32(Texts::KilledUnitA), me);
        //    else
        //        DoScriptText(int32(Texts::KilledUnitB), me);
        //}

        void JustEngagedWith(Unit* who)
        {
            _JustEngagedWith(who);

            //DoScriptText(int32(Texts::CombatStart), me);
            events.ScheduleEvent(uint32(Events::SolarBurst), 5000);
            events.ScheduleEvent(uint32(Events::CastDown), 11000);
            events.ScheduleEvent(uint32(Events::LensFlare), 27000);
            events.ScheduleEvent(uint32(Events::CallAdds), 29000);

            if (instance)
                instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
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
            case uint32(Events::CastDown):
                events.ScheduleEvent(uint32(Events::CastDown), 35000);
                //if (Player* plr = SelectRandomPlayerExcludedTank(me, 80.0f))
                if (Unit* plr = SelectTarget(SelectTargetMethod::Random))
                {
                    //DoScriptText(int32(Texts::SpellCastDown), me);
                    me->CastSpell(plr, uint32(Spells::CastDown));
                }
                break;
            case uint32(Events::LensFlare):
                if (Player* plr = SelectRandomPlayerIncludedTank(me, 80.0f))
                {
                    plr->CastSpell(plr, uint32(Spells::LensFlare), true);
                    //DoScriptText(int32(Texts::SpellLensFlare), me);
                }
                events.ScheduleEvent(uint32(Events::LensFlare), 27000);
                break;
            case uint32(Events::SolarBurst):
                me->CastSpell(me->GetVictim(), uint32(Spells::SolarBurst));
                events.ScheduleEvent(uint32(Events::SolarBurst), 21000);
                break;
            case uint32(Events::CallAdds):
                //DoScriptText(int32(Texts::SpellCallAdds), me);
                me->SummonCreature(SkyreachDefenseConstruct, 1080.45f, 1787.38f, 262.172f, 5.28156f, TempSummonType::TEMPSUMMON_MANUAL_DESPAWN);
                events.ScheduleEvent(uint32(Events::CallAdds), 60000);
                break;
            default:
                break;
            }

            DoMeleeAttackIfReady();
        }
    };
};

// Summon Cast Down - 165845
class spell_CastDown : public SpellScriptLoader
{
public:
    spell_CastDown()
        : SpellScriptLoader("spell_CastDown")
    {
    }

    enum class Spells : uint32
    {
        CastDown = 153955,
    };

    class spell_CastDownSpellScript : public SpellScript
    {
        PrepareSpellScript(spell_CastDownSpellScript)

            void HandleDummy(SpellEffIndex /*effIndex*/)
        {
            if (GetCaster() && GetHitUnit())
            {
                GetHitUnit()->CastSpell(GetHitUnit(), uint32(Spells::CastDown), true);
            }
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_CastDownSpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_CastDownSpellScript();
    }
};

// AreaTriggers for spells: 154044
class AreaTrigger_LensFlare : public AreaTriggerEntityScript
{
public:

    AreaTrigger_LensFlare() : AreaTriggerEntityScript("AreaTrigger_LensFlare") { }

    struct AreaTrigger_LensFlareAI : AreaTriggerAI
    {
        AreaTrigger_LensFlareAI(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger) {}

        enum eLensFlareSpells
        {
            LensFlare_Dmg = 154043
        };

        std::set<ObjectGuid> m_Targets;

        void OnUpdate(uint32 /*time*/) override
        {
            if (Unit* caster = at->GetCaster())
            {
                std::list<Player*> playerList;

                Trinity::AnyPlayerInObjectRangeCheck check(at, 5.0f);
                Trinity::PlayerListSearcher<Trinity::AnyPlayerInObjectRangeCheck> searcher(at, playerList, check);
                Cell::VisitAllObjects(at, searcher, 3.0f);

                std::set<ObjectGuid> targets;

                for (Player* player : playerList)
                {
                    targets.insert(player->GetGUID());

                    if (!player->HasAura(eLensFlareSpells::LensFlare_Dmg))
                    {
                        m_Targets.insert(player->GetGUID());
                        player->CastSpell(player, eLensFlareSpells::LensFlare_Dmg);
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
                        unit->RemoveAura(eLensFlareSpells::LensFlare_Dmg);

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
                if (target && target->HasAura(eLensFlareSpells::LensFlare_Dmg))
                    target->RemoveAura(eLensFlareSpells::LensFlare_Dmg);
            }
        }
    };

    AreaTriggerAI* GetAI(AreaTrigger* areatrigger) const override
    {
        return new AreaTrigger_LensFlareAI(areatrigger);
    }
};

void AddSC_boss_HighSaveViryx()
{
    new boss_HighSageViryx();
    new mob_SolarZealot();
    new mob_ArakkoaMagnifyingGlassFocus();
    new mob_SkyreachShieldConstruct();
    new spell_CastDown();
    new AreaTrigger_LensFlare();
}

