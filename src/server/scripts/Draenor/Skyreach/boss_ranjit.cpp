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

class boss_Ranjit : public CreatureScript
{
public:
    // Entry: 75964
    boss_Ranjit()
        : CreatureScript("boss_Ranjit")
    {
    }

    enum Spells : uint32
    {
        // Windwall.
        WINDWALL = 153315,      // 2:43:38 - 2-43-52. Random target. Every 14s.
        WINDWALL_AT_1 = 153311,
        WINDWALL_AT_2 = 153314,
        WINDWALL_MISSLE_1 = 153593,
        WINDWALL_MISSILE_2 = 153594,
        WINDWALL_DMG = 153759,
        // Four winds. Arrived after 2 or 3 instances of WindWall.
        FOUR_WINDS = 156793,
        FOUR_WINDS_DMG = 153139,
        FOUR_WINDS_AT_1 = 156634,
        FOUR_WINDS_AT_2 = 156636,
        FOUR_WINDS_VISUAL_1 = 166623,
        FOUR_WINDS_VISUAL_2 = 166664,
        // Fan of blades.
        FAN_OF_BLADES = 153757, // 2:43:34 - 2:43:50, every 16s.
        // Piercing rush.
        PIERCING_RUSH = 165731, // 2:43:29 - 2:43:44, every 15s.
        LensFlare = 154029,
        // Spining Blade.
        SPINNING_BLADE = 153544
    };

    enum Texts : int32
    {
        COMBAT_START = -1603202,
        JUST_DIED = -1603203,
        FOUR_WINDS_1 = -1603204,
        FOUR_WINDS_2 = -1603205,
        KILL_PLAYER_1 = -1603206,
        KILL_PLAYER_2 = -1603207,
        VICTORY = -1603208
    };

    enum eTalks : uint32
    {
        TalkCombat = 0,
        TalkOutrun = 1,
        TalkDeath = 2,
    };

    enum RanjitEvents : uint32
    {
        WINDWALL_EVENT = 1,
        FOUR_WINDS_EVENT = 2,
        PIERCING_RUSH_EVENT = 3,
        FAN_OF_BLADES_EVENT = 4,
        LENS_FLARE_EVENT = 5,
        SPINNING_BLADE_EVENT = 6
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_RanjitAI(creature);
    }

    struct boss_RanjitAI : public BossAI
    {
        boss_RanjitAI(Creature* creature) : BossAI(creature, Data::Ranjit),
            m_countWindwalls(0)
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
            me->SetAnimTier(AnimTier::Fly, false);
            me->SetReactState(REACT_PASSIVE);
        }

        void Reset() override
        {
            BossAI::Reset();

            m_countWindwalls = 0;
            m_TriggerFourWinds[0].Clear();
            m_TriggerFourWinds[1].Clear();

            m_TriggerFourWinds[0] = me->SummonCreature(MobEntries::ArakkoaPincerBirdsController, 1165.871f, 1727.601f, 186.f, 0.0f, TEMPSUMMON_MANUAL_DESPAWN, 0)->GetGUID();
            m_TriggerFourWinds[1] = me->SummonCreature(MobEntries::ArakkoaPincerBirdsController, 1165.871f, 1727.601f, 189.4522f, 0.0f, TEMPSUMMON_MANUAL_DESPAWN, 0)->GetGUID();
        }

        void EnterEvadeMode(EvadeReason why) override
        {
            _EnterEvadeMode(why);
            _DespawnAtEvade(5s);
            if (instance)
            {
                instance->SetBossState(Data::Ranjit, FAIL);
                instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            }
        }

        void JustDied(Unit* killer) override
        {
            BossAI::JustDied(killer);

            Talk(TalkDeath);

            me->CastSpell(me, RandomSpells::DespawnAreaTriggers, true);

            if (instance)
                instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
        }

        //void KilledUnit(Unit* /*victim*/)
        //{
        //    if (urand(0, 1))
        //        DoScriptText(int32(Texts::KILL_PLAYER_1), me);
        //    else
        //        DoScriptText(int32(Texts::KILL_PLAYER_2), me);
        //}

        bool _isIntro = true;

        void JustEngagedWith(Unit* who) override
        {
            _JustEngagedWith(who);

            // Sniff sends this
            me->SetVirtualItem(0, 0);

            scheduler.Schedule(400ms, [this](TaskContext /*context*/)
            {
                me->SetAnimTier(AnimTier::Ground, false);
                me->SetStandState(UnitStandStateType::UNIT_STAND_STATE_STAND);
            });

            scheduler.Schedule(1s, [this](TaskContext /*context*/)
            {
                Talk(TalkCombat);
                me->SetReactState(REACT_AGGRESSIVE);
                _isIntro = false;
            });

            events.ScheduleEvent(RanjitEvents::WINDWALL_EVENT, 8s);
            events.ScheduleEvent(RanjitEvents::FAN_OF_BLADES_EVENT, 5s);
            events.ScheduleEvent(RanjitEvents::PIERCING_RUSH_EVENT, 1s);
            events.ScheduleEvent(RanjitEvents::SPINNING_BLADE_EVENT, 8s, 10s);

            //DoScriptText(int32(Texts::COMBAT_START), me);

            if (instance)
                instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
        }

        void UpdateAI(const uint32 diff)
        {
            scheduler.Update(diff);

            if (_isIntro)
                return;

            if (!UpdateVictim())
                return;

            events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            switch (events.ExecuteEvent())
            {
                case RanjitEvents::FOUR_WINDS_EVENT:
                    me->CastSpell(me->GetVictim(), Spells::FOUR_WINDS);

                    m_countWindwalls = 0;
                    Talk(eTalks::TalkOutrun);

                    if (IsHeroic())
                        events.ScheduleEvent(RanjitEvents::LENS_FLARE_EVENT, 14000);
                    break;
                case RanjitEvents::WINDWALL_EVENT:
                    events.ScheduleEvent(RanjitEvents::WINDWALL_EVENT, urand(19000, 26000));

                    if (Unit* unit = SelectRandomPlayerIncludedTank(me, 40.0f))
                        me->CastSpell(unit, Spells::WINDWALL);

                    if (m_countWindwalls++ == 2)
                        events.ScheduleEvent(RanjitEvents::FOUR_WINDS_EVENT, urand(2000, 3000));
                    break;
                case RanjitEvents::FAN_OF_BLADES_EVENT:
                    events.ScheduleEvent(RanjitEvents::FAN_OF_BLADES_EVENT, urand(15000, 17000));
                    me->CastSpell(me, Spells::FAN_OF_BLADES);
                    break;
                case RanjitEvents::SPINNING_BLADE_EVENT:
                    events.ScheduleEvent(RanjitEvents::SPINNING_BLADE_EVENT, urand(8000, 10000));
                    if (Player* target = SelectRandomPlayerIncludedTank(me, 45.0f))
                        me->CastSpell(target, Spells::SPINNING_BLADE);
                    break;
                case RanjitEvents::PIERCING_RUSH_EVENT:
                    events.ScheduleEvent(RanjitEvents::PIERCING_RUSH_EVENT, urand(13000, 16000));
                    if (Unit* unit = SelectRandomPlayerExcludedTank(me, 40.0f))
                        me->CastSpell(unit, Spells::PIERCING_RUSH);
                    break;
                case RanjitEvents::LENS_FLARE_EVENT:
                    if (Player* plr = SelectRandomPlayerIncludedTank(me, 80.0f))
                        plr->CastSpell(plr, Spells::LensFlare, true);
                    break;
                default:
                    break;
            }

            DoMeleeAttackIfReady();
        }

        uint32 m_countWindwalls;
        ObjectGuid m_TriggerFourWinds[2];
    };
};

// Windwall - 153315
class spell_Windwall : public SpellScriptLoader
{
public:
    spell_Windwall()
        : SpellScriptLoader("spell_Windwall")
    {
    }

    enum class Spells : uint32
    {
        // Clock and counter clock windwalls.
        WINDWALL_1 = 153593,
        WINDWALL_2 = 153594,
    };

    class spell_Windwall_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_Windwall_SpellScript);

        void HandleDummy(SpellEffIndex /*effIndex*/)
        {
            if (GetCaster())
            {
                Unit* target = nullptr;
                if ((target = SelectRandomPlayerIncludedTank(GetCaster(), 30.0f)))
                {
                    uint32 random = urand(0, 1);
                    if (random == 0)
                        GetCaster()->CastSpell(target, uint32(Spells::WINDWALL_1), true);
                    else
                        GetCaster()->CastSpell(target, uint32(Spells::WINDWALL_2), true);
                }
            }
        }

        void Register()
        {
            OnEffectHit += SpellEffectFn(spell_Windwall_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_Windwall_SpellScript();
    }
};

// Four wind - 156793
class spell_FourWind : public SpellScriptLoader
{
public:
    spell_FourWind()
        : SpellScriptLoader("spell_FourWind")
    {
    }

    enum class Spells : uint32
    {
        // Four winds. Arrived after 2 or 3 instances of WindWall.
        FOUR_WINDS = 156793,
        FOUR_WINDS_DMG = 153139,
        FOUR_WINDS_AT_1 = 156634,
        FOUR_WINDS_AT_2 = 156636,
        FOUR_WINDS_VISUAL_1 = 166623,
        FOUR_WINDS_VISUAL_2 = 166664
    };

    class spell_FourWind_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_FourWind_SpellScript);

        void HandleTriggerMissible(SpellEffIndex /*effIndex*/)
        {
            static const uint32 k_spells1[2] =
            {
                uint32(Spells::FOUR_WINDS_AT_1),
                uint32(Spells::FOUR_WINDS_VISUAL_1)
            };
            static const uint32 k_spells2[2] =
            {
                uint32(Spells::FOUR_WINDS_AT_2),
                uint32(Spells::FOUR_WINDS_VISUAL_2)
            };
            if (GetCaster())
            {
                std::list<Unit*> target = SelectNearestCreatureListWithEntry(GetCaster(), MobEntries::ArakkoaPincerBirdsController, 40.0f);
                if (target.empty())
                    return;

                uint32 random = urand(0, 1);
                uint32 i = 0;
                for (Unit* trigger : target)
                {
                    trigger->SetOrientation(0);
                    if (random == 0)
                        trigger->CastSpell(trigger, k_spells1[i], true);
                    else
                        trigger->CastSpell(trigger, k_spells2[i], true);
                    ++i;
                }
            }
        }

        void Register()
        {
            OnEffectHit += SpellEffectFn(spell_FourWind_SpellScript::HandleTriggerMissible, EFFECT_0, SPELL_EFFECT_TRIGGER_MISSILE);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_FourWind_SpellScript();
    }
};

// AreaTriggers for spells: 153311, 153314
class AreaTrigger_WindWall : public AreaTriggerEntityScript
{
public:
    AreaTrigger_WindWall() : AreaTriggerEntityScript("AreaTrigger_WindWall") {}

    struct AreaTrigger_WindWallAI : AreaTriggerAI
    {
        AreaTrigger_WindWallAI(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger)
        {
            m_angle = 0;
            m_targets.clear();
            m_Last = 60000;
            m_IsSpellAt2 = 0;
        }

        enum eWindwallSpells
        {
            WINDWALL_DMG = 153759,
            WINDWALL_AT_1 = 153311,
            WINDWALL_AT_2 = 153314,
        };

        float m_angle;
        std::list<ObjectGuid> m_targets;
        uint32 m_Last;
        uint32 m_IsSpellAt2;

        bool IsInWind(Unit const* unit, AreaTrigger const* area) const
        {
            static const float radius = 2.0f;

            float X1 = area->GetPositionX() + cos(m_angle);
            float X2 = area->GetPositionX() + cos(m_angle - float(M_PI));
            float Y1 = area->GetPositionY() + sin(m_angle);
            float Y2 = area->GetPositionY() + sin(m_angle - float(M_PI));

            float dx = X2 - X1;
            float dy = Y2 - Y1;

            return std::abs(dy * unit->GetPositionX() - dx * unit->GetPositionY() - X1 * Y2 + X2 * Y1) / std::sqrt(dx * dx + dy * dy) < radius;
        }

        void OnRemove() override
        {
            for (auto guid : m_targets)
            {
                Unit* target = ObjectAccessor::GetUnit(*at, guid);
                if (target && target->HasAura(eWindwallSpells::WINDWALL_DMG))
                {
                    target->RemoveAura(eWindwallSpells::WINDWALL_DMG);
                }
            }
        }

        void OnCreate() override
        {
            m_angle = at->GetOrientation();
            m_IsSpellAt2 = at->GetSpellId() == (eWindwallSpells::WINDWALL_AT_2);
        }

        void OnUpdate(uint32 /*time*/) override
        {
            if (Unit*caster = at->GetCaster())
            {
                static const float rotSpeed[2] =
                {
                    0.015f,
                    0.022f
                };
                static const int32 start[2] =
                {
                    55000,
                    37000
                };
                static const float dist = 10.0f;

                // Update targets.
                std::list<Unit*> targetList;

                Trinity::NearestAttackableUnitInObjectRangeCheck check(at, at->GetCaster(), dist);
                Trinity::UnitListSearcher<Trinity::NearestAttackableUnitInObjectRangeCheck> searcher(at, targetList, check);
                Cell::VisitAllObjects(at, searcher, dist);

                std::list<ObjectGuid> toRemove; // We need to do it in two phase, otherwise it will break iterators.
                for (auto guid : m_targets)
                {
                    Unit* target = ObjectAccessor::GetUnit(*at, guid);
                    if (target && (target->GetExactDist2d(at) > dist || !IsInWind(target, at)))
                    {
                        if (target->HasAura(eWindwallSpells::WINDWALL_DMG))
                        {
                            toRemove.emplace_front(guid);
                            target->RemoveAura(eWindwallSpells::WINDWALL_DMG);
                        }
                    }
                }

                for (auto guid : toRemove)
                {
                    m_targets.remove(guid);
                }

                for (Unit* unit : targetList)
                {
                    if (!unit
                        || unit->GetExactDist2d(at) > dist
                        || unit->HasAura(eWindwallSpells::WINDWALL_DMG)
                        || !IsInWind(unit, at))
                        continue;

                    caster->CastSpell(unit, (eWindwallSpells::WINDWALL_DMG));
                    m_targets.emplace_front(unit->GetGUID());

                    // Achievement handling.
                    if (Player* plr = unit->ToPlayer())
                    {
                        // We check if the caster is Ranjit.
                        if (at->GetInstanceScript() && at->GetCaster()->GetEntry() == BossEntries::RANJIT)
                            at->GetInstanceScript()->SetGuidData(Data::PlayerIsHittedByRanjitSpells, plr->GetGUID());
                    }
                }

                // Update rotation.
                if (at->GetDuration() > start[m_IsSpellAt2] || (m_Last - at->GetDuration() < 100))
                    return;

                if (m_IsSpellAt2)
                    m_angle += rotSpeed[m_IsSpellAt2];
                else
                    m_angle -= rotSpeed[m_IsSpellAt2];

                // We are staying in [0, 2pi]
                if (m_angle > 2 * float(M_PI))
                    m_angle -= 2 * float(M_PI);
                if (m_angle < 0)
                    m_angle += 2 * float(M_PI);

                m_Last = at->GetDuration();
            }
        }
    };

    AreaTriggerAI* GetAI(AreaTrigger* areatrigger) const override
    {
        return new AreaTrigger_WindWallAI(areatrigger);
    }
};

// AreaTriggers for spells: 156634, 156636
class AreaTrigger_FourWinds : public AreaTriggerEntityScript
{
public:
    AreaTrigger_FourWinds() : AreaTriggerEntityScript("AreaTrigger_FourWinds") {}

    struct AreaTrigger_FourWindsAI : AreaTriggerAI
    {
        AreaTrigger_FourWindsAI(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger)
        {
            m_angle = 0;
            m_targets.clear();
            m_Last = 60000;
            m_IsSpellAt2 = 0;
        }

        enum eFourWindsSpells
        {
            // Four winds. Arrived after 2 or 3 instances of WindWall.
            FOUR_WINDS = 156793,
            FOUR_WINDS_DMG = 153139,
            FOUR_WINDS_AT_1 = 156634,
            FOUR_WINDS_AT_2 = 156636,
            FOUR_WINDS_VISUAL_1 = 166623,
            FOUR_WINDS_VISUAL_2 = 166664
        };

        float m_angle;
        std::list<ObjectGuid> m_targets;
        uint32 m_Last;
        uint32 m_IsSpellAt2;

        bool IsInWind(Unit const* unit, AreaTrigger const* area) const
        {
            static const float radius = 3.0f;

            float X1 = area->GetPositionX() + cos(m_angle);
            float X2 = area->GetPositionX() + cos(m_angle - float(M_PI));
            float Y1 = area->GetPositionY() + sin(m_angle);
            float Y2 = area->GetPositionY() + sin(m_angle - float(M_PI));

            float dx = X2 - X1;
            float dy = Y2 - Y1;

            bool b1 = std::abs(dy * unit->GetPositionX() - dx * unit->GetPositionY() - X1 * Y2 + X2 * Y1) / std::sqrt(dx * dx + dy * dy) < radius;

            X1 = area->GetPositionX() + cos(m_angle + float(M_PI) / 2);
            X2 = area->GetPositionX() + cos(m_angle - float(M_PI) / 2);
            Y1 = area->GetPositionY() + sin(m_angle + float(M_PI) / 2);
            Y2 = area->GetPositionY() + sin(m_angle - float(M_PI) / 2);

            dx = X2 - X1;
            dy = Y2 - Y1;

            bool b2 = std::abs(dy * unit->GetPositionX() - dx * unit->GetPositionY() - X1 * Y2 + X2 * Y1) / std::sqrt(dx * dx + dy * dy) < radius;

            return b1 || b2;
        }

        void OnRemove() override
        {
            for (auto guid : m_targets)
            {
                Unit* target = ObjectAccessor::GetUnit(*at, guid);
                if (target && target->HasAura(eFourWindsSpells::FOUR_WINDS_DMG))
                {
                    target->RemoveAura(eFourWindsSpells::FOUR_WINDS_DMG);
                }
            }
        }

        void OnCreate() override
        {
            m_IsSpellAt2 = at->GetSpellId() == (eFourWindsSpells::FOUR_WINDS_AT_2);
            m_angle = (m_IsSpellAt2 ? float(M_PI) / +72 : float(M_PI) / 7) + (m_IsSpellAt2 ? float(M_PI) / 36 : -float(M_PI) / 72); // Magic values ! Taken from tests IG.
        }

        void OnUpdate(uint32 /*time*/) override
        {
            if (Unit* caster = at->GetCaster())
            {
                static const float rotSpeed[2] =
                {
                    0.014f,
                    0.014f
                };
                static const float dist = 45.0f;

                // Update targets.
                std::list<Unit*> targetList;

                Trinity::NearestAttackableUnitInObjectRangeCheck check(at, at->GetCaster(), dist);
                Trinity::UnitListSearcher<Trinity::NearestAttackableUnitInObjectRangeCheck> searcher(at, targetList, check);
                Cell::VisitAllObjects(at, searcher, dist);

                std::list<ObjectGuid> toRemove; // We need to do it in two phase, otherwise it will break iterators.
                for (auto guid : m_targets)
                {
                    Unit* target = ObjectAccessor::GetUnit(*at, guid);
                    if (target && (target->GetExactDist2d(at) > dist || !IsInWind(target, at)))
                    {
                        if (target->HasAura(eFourWindsSpells::FOUR_WINDS_DMG))
                        {
                            toRemove.emplace_front(guid);
                            target->RemoveAura(eFourWindsSpells::FOUR_WINDS_DMG);
                        }
                    }
                }

                for (auto guid : toRemove)
                {
                    m_targets.remove(guid);
                }

                for (Unit* unit : targetList)
                {
                    if (!unit
                        || unit->GetExactDist2d(at) > dist
                        || unit->HasAura(eFourWindsSpells::FOUR_WINDS_DMG)
                        || !IsInWind(unit, at))
                        continue;

                    caster->CastSpell(unit, (eFourWindsSpells::FOUR_WINDS_DMG));
                    m_targets.emplace_front(unit->GetGUID());

                    // Achievement handling.
                    if (Player* plr = unit->ToPlayer())
                    {
                        // We check if the caster is Ranjit.
                        if (at->GetInstanceScript() && at->GetCaster()->GetEntry() == BossEntries::RANJIT)
                            at->GetInstanceScript()->SetGuidData(Data::PlayerIsHittedByRanjitSpells, plr->GetGUID());
                    }
                }

                // Update rotation.
                if ((m_Last - at->GetDuration() < 100))
                    return;

                if (m_IsSpellAt2)
                    m_angle -= rotSpeed[m_IsSpellAt2];
                else
                    m_angle += rotSpeed[m_IsSpellAt2];

                // We are staying in [0, 2pi]
                if (m_angle > 2 * float(M_PI))
                    m_angle -= 2 * float(M_PI);
                if (m_angle < 0)
                    m_angle += 2 * float(M_PI);

                m_Last = at->GetDuration();
            }
        }
    };

    AreaTriggerAI* GetAI(AreaTrigger* areatrigger) const override
    {
        return new AreaTrigger_FourWindsAI(areatrigger);
    }
};

void AddSC_boss_ranjit()
{
    new boss_Ranjit();

    new spell_Windwall();
    new spell_FourWind();
    new AreaTrigger_WindWall();
    new AreaTrigger_FourWinds();
}

