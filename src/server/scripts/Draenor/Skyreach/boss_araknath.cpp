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

class mob_SkyreachArcanologist : public CreatureScript
{
public:
    // Entry: 76376
    mob_SkyreachArcanologist()
        : CreatureScript("mob_SkyreachArcanologist")
    {
    }

    enum class Spells : uint32
    {
        SOLAR_DETONATION = 160288, // 7 seconds.
        SOLAR_STORM = 159215, // 12 to 15 seconds.
        SOLAR_STORM_1 = 159216,
        SOLAR_STORM_2 = 159218,
        SOLAR_STORM_3 = 159221,
        SOLAR_STORM_DMG = 159226,
    };

    enum class Events : uint32
    {
        SOLAR_DETONATION = 1,
        SOLAR_STORM = 2,
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new mob_SkyreachArcanologistAI(creature);
    }

    struct mob_SkyreachArcanologistAI : public ScriptedAI
    {
        mob_SkyreachArcanologistAI(Creature* creature) : ScriptedAI(creature),
            m_instance(creature->GetInstanceScript()),
            m_events()
        {
        }

        void Reset()
        {
            m_events.Reset();

            if (m_instance)
                m_instance->SetData(Data::SkyreachArcanologistReset, 0);
        }

        void JustDied(Unit*)
        {
            if (m_instance)
                m_instance->SetData(Data::SkyreachArcanologistIsDead, 0);

            if (IsHeroic())
                m_instance->DoCompleteAchievement(uint32(Achievements::MagnifyEnhance));
        }

        void JustEngagedWith(Unit* /*who*/)
        {
            m_events.ScheduleEvent(uint32(Events::SOLAR_DETONATION), urand(2500, 7500));
            m_events.ScheduleEvent(uint32(Events::SOLAR_STORM), urand(5000, 10000));
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
            case uint32(Events::SOLAR_DETONATION):
                m_events.ScheduleEvent(uint32(Events::SOLAR_DETONATION), urand(6500, 7500));
                if (Player* plr = SelectRandomPlayerIncludedTank(me, 15.0f))
                    me->CastSpell(plr, uint32(Spells::SOLAR_DETONATION));
                break;
            case uint32(Events::SOLAR_STORM):
                m_events.ScheduleEvent(uint32(Events::SOLAR_STORM), urand(12000, 15000));
                me->CastSpell(me->GetVictim(), uint32(Spells::SOLAR_STORM));
                break;
            default:
                break;
            }

            DoMeleeAttackIfReady();
        }

        InstanceScript* m_instance;
        EventMap m_events;
    };
};

class boss_Araknath : public CreatureScript
{
public:
    // Entry: 76141
    boss_Araknath()
        : CreatureScript("boss_Araknath")
    {
    }

    enum class Spells : uint32
    {
        MELEE = 154121, // Every 2 seconds.
        SMASH = 154110, // Every 6 to 7 seconds.
        BURST = 154135, // Every 23 seconds.
        BREATH_OF_SINDRAGOSA = 155168,
        SUBMERGE = 154164,
        SUBMERGED = 154163,
    };

    enum class Events : uint32
    {
        SHUT_DOORS = 1,
        MELEE = 2,
        SMASH = 3,
        BURST = 4,
        ENERGIZE_START = 5,
        ENERGIZE_STOP = 6,
        Reset = 7
    };

    ScriptedAI* GetAI(Creature* creature) const
    {
        return new boss_AraknathAI(creature);
    }

    struct boss_AraknathAI : public BossAI
    {
        boss_AraknathAI(Creature* creature) : BossAI(creature, Data::Araknath),
            m_Initialized(false),
            m_InitializationTimer(0)
        {
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
            if (!me->IsAlive())
                return;

            me->ResetLootMode();
            events.Reset();
            summons.DespawnAll();

            me->RemoveAllAuras();
            me->CombatStop();
            me->AddAura(uint32(Spells::SUBMERGED), me);
            me->SetReactState(REACT_PASSIVE);

            events.ScheduleEvent(uint32(Events::Reset), 100);

            // We need time so that all the mobs are spawned.
            m_InitializationTimer = 500;
        }

        void JustDied(Unit* /*killer*/)
        {
            _JustDied();

            if (instance)
                instance->SetData(Data::AraknathSolarConstructorActivation, false);
        }

        void KilledUnit(Unit* /*victim*/)
        {
        }

        void JustReachedHome()
        {
            _JustReachedHome();

            if (instance)
            {
                instance->SetBossState(Data::Araknath, FAIL);
                instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            }
        }

        void JustEngagedWith(Unit* who)
        {
            _JustEngagedWith(who);
            events.ScheduleEvent(uint32(Events::MELEE), 2000);
            events.ScheduleEvent(uint32(Events::SMASH), urand(5500, 7000));
            events.ScheduleEvent(uint32(Events::BURST), urand(21500, 23000));
            events.ScheduleEvent(uint32(Events::ENERGIZE_START), 12000);
        }

        void UpdateAI(const uint32 diff)
        {
            if (!m_Initialized && m_InitializationTimer <= 0)
            {
                m_Initialized = true;

                if (instance && (instance->GetBossState(Data::Araknath) == EncounterState::SPECIAL || instance->GetBossState(Data::Araknath) == EncounterState::IN_PROGRESS))
                    instance->SetData(Data::SkyreachArcanologistIsDead, 0);
            }
            else
                m_InitializationTimer -= diff;

            if (me->GetDistance(me->GetHomePosition()) > 23.0f && !me->IsInEvadeMode())
                EnterEvadeMode();

            if (!UpdateVictim())
                return;

            events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            switch (events.ExecuteEvent())
            {
            case uint32(Events::MELEE):
                events.ScheduleEvent(uint32(Events::MELEE), 2000);
                me->CastSpell(me->GetVictim(), uint32(Spells::MELEE));
                break;
            case uint32(Events::SMASH):
                events.ScheduleEvent(uint32(Events::SMASH), urand(5500, 7000));
                me->CastSpell(me, uint32(Spells::SMASH));

                events.CancelEvent(uint32(Events::MELEE));
                events.ScheduleEvent(uint32(Events::MELEE), 2000);
                break;
            case uint32(Events::BURST):
                events.ScheduleEvent(uint32(Events::BURST), urand(21500, 23000));
                me->CastSpell(me->GetVictim(), uint32(Spells::BURST));
                break;
            case uint32(Events::ENERGIZE_START):
                events.ScheduleEvent(uint32(Events::ENERGIZE_STOP), 12000);

                if (instance)
                    instance->SetData(Data::AraknathSolarConstructorActivation, true);
                break;
            case uint32(Events::ENERGIZE_STOP):
                events.ScheduleEvent(uint32(Events::ENERGIZE_START), 3000);

                if (instance)
                    instance->SetData(Data::AraknathSolarConstructorActivation, false);
                break;
            default:
                break;
            }
        }

        bool m_Initialized;
        int32 m_InitializationTimer;
    };
};

// Energize 154140
class spell_Energize : public SpellScriptLoader
{
public:
    spell_Energize()
        : SpellScriptLoader("spell_Energize")
    {
    }

    enum class Spells : uint32
    {
        ENERGIZE = 154139, // During 12 seconds, restart after 3 seconds.
        ENERGIZE_HEAL = 154149,
        ENERGIZE_DMG = 154150,
        ENERGIZE_VISUAL_1 = 154179,
    };

    class spell_EnergizeSpellScript : public SpellScript
    {
        PrepareSpellScript(spell_EnergizeSpellScript)

            void HandleDummy(SpellEffIndex /*effIndex*/)
        {
            if (Unit* caster = GetCaster())
                caster->CastSpell(caster, uint32(Spells::ENERGIZE_HEAL));
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_EnergizeSpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_EnergizeSpellScript();
    }
};

// Visual Energize - 154159
class spell_VisualEnergize : public SpellScriptLoader
{
public:
    spell_VisualEnergize()
        : SpellScriptLoader("spell_VisualEnergize")
    {
    }

    class spell_VisualEnergizeSpellScript : public SpellScript
    {
        PrepareSpellScript(spell_VisualEnergizeSpellScript)

            void CheckTarget(std::list<WorldObject*>& unitList)
        {
            Unit* caster = GetCaster();
            unitList.remove_if([caster](WorldObject* obj) {
                return !(obj->ToCreature()
                    && obj->ToCreature()->GetEntry() == 76142
                    && obj->ToCreature()->GetCurrentSpell(CURRENT_CHANNELED_SPELL));
            });
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_VisualEnergizeSpellScript::CheckTarget, EFFECT_0, TARGET_UNIT_SRC_AREA_ENTRY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_VisualEnergizeSpellScript();
    }
};

// Visual Energize - 154177
class spell_VisualEnergize2 : public SpellScriptLoader
{
public:
    spell_VisualEnergize2()
        : SpellScriptLoader("spell_VisualEnergize2")
    {
    }

    class spell_VisualEnergize2SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_VisualEnergize2SpellScript)

            void CheckTarget(std::list<WorldObject*>& unitList)
        {
            Unit* caster = GetCaster();
            unitList.remove_if([caster](WorldObject* obj) {
                if (!obj->ToCreature())
                    return true;

                if (caster->GetEntry() == 77543)
                    return obj->ToCreature()->GetEntry() != 76367;
                else
                    return obj->ToCreature()->GetEntry() != 76142;
            });
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_VisualEnergize2SpellScript::CheckTarget, EFFECT_0, TARGET_UNIT_SRC_AREA_ENTRY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_VisualEnergize2SpellScript();
    }
};

// AreaTriggers for spells: 154110
class AreaTrigger_Smash : public AreaTriggerEntityScript
{
    enum class Spells : uint32
    {
        SMASH = 154110,
        SMASH_2 = 154113,
        SMASH_DMG = 154132,
    };

public:
    AreaTrigger_Smash() : AreaTriggerEntityScript("AreaTrigger_Smash") { }

    struct AreaTrigger_SmashAI : AreaTriggerAI
    {
        AreaTrigger_SmashAI(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger) {}

        void OnUpdate(uint32 /*time*/) override
        {
            if (Unit* caster = at->GetCaster())
            {
                std::list<Unit*> targetList;
                static const float radius = 10.0f;

                Trinity::NearestAttackableUnitInObjectRangeCheck check(at, at->GetCaster(), radius);
                Trinity::UnitListSearcher<Trinity::NearestAttackableUnitInObjectRangeCheck> searcher(at, targetList, check);
                Cell::VisitAllObjects(at, searcher, radius);

                Position pos = *at;
                pos.m_positionX += radius * cos(at->GetOrientation());
                pos.m_positionY += radius * sin(at->GetOrientation());

                for (auto target : targetList)
                {
                    if (target && at->GetCaster())
                    {
                        caster->CastSpell(target, uint32(Spells::SMASH_DMG));
                    }
                }
            }
        }
    };

    AreaTriggerAI* GetAI(AreaTrigger* areatrigger) const override
    {
        return new AreaTrigger_SmashAI(areatrigger);
    }
};

void AddSC_boss_Araknath()
{
    new boss_Araknath();
    new mob_SkyreachArcanologist();
    new spell_Energize();
    new spell_VisualEnergize();
    new spell_VisualEnergize2();
    new AreaTrigger_Smash();
}

