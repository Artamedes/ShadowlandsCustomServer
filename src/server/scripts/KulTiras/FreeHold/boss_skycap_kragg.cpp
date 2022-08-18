/*
 * Copyright (C) 2008-2020 TrinityCore <https://www.trinitycore.org/>
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

#include "free_hold.h"
#include "Vehicle.h"

enum KraggSpells
{
    //SkyCap Kragg Intro
    SPELL_VILE_BOMBARDMENT_PERIODIC = 256042,
    SPELL_VILE_BOMBARDMENT_SELECT   = 256040,
    SPELL_VILE_BOMBARDMENT_INTRO    = 257272,
    SPELL_VILE_COATING_INTRO        = 257274,

    //Boss SkyCap Kragg
    //Phase One: Mounted Assault
    SPELL_CHARRRRRGE                = 255952,
    SPELL_CHARRRRRGE_DAMAGE         = 258773,
    SPELL_PISTOL_SHOT               = 255966,
    SPELL_SPAWN_PARROT              = 256056,

    //Phase Two: Death Rains From Above
    SPELL_TRIGGER_POOP              = 256052,
    SPELL_AZERITE_POWER_SHOT        = 256106,
    SPELL_AZERITE_POWER_SHOT_VISUAL = 256107,
    SPELL_REVITALIZING_BREW         = 256060,
    SPELL_REVITALIZING_BREW_MISSILE = 263274,
    SPELL_REVITALIZING_BREW_PLAYER  = 263297,
    SPELL_TRIGGER_DIVE_BOMB         = 268711,

    //Sharkbait
    SPELL_VILE_BOMBARDMENT          = 256005,
    SPELL_VILE_COATING              = 256016,

    //258353 End Fight Conversation

    //Heroic && Mythic Only
    SPELL_DIVE_BOMB_JUMP            = 268717,
    SPELL_DIVE_BOMB_DAMAGE          = 272046  ///Sharkbait will then charge across the arena in a straight line, dealing damage and knocking back all players in the path
};


enum KraggEvents
{
    EVENT_CHECK_PLAYER = 1,
    EVENT_VILE_BOMBARDMENT,
    EVENT_CHARRRRRGE,
    EVENT_PISTOL_SHOT,
    EVENT_AZERITE_POWDERSHOT,
    EVENT_REVITALIZING_BREW,
    EVENT_DEATH_RAINS_FROM_ABOVE,

    //Heroic Event
    EVENT_DIVE_BOMBS,
};

enum KraggModel
{
    SHARKBAIT_MODEL = 80438
};

enum KraggMovementPoint
{
   MOVEMENT_POINT_LAUNCH_BOMB,
   MOVEMENT_POINT_BOSS_APPEAR,
   MOVEMENT_POINT_FLY_AWAY,
   MOVEMENT_POINT_JUST_DEFEATED,
   MOVEMENT_POINT_DIVE_BOMB = 1004,
};

enum KraggTalk
{
    TALK_VILE_BOMBARDMENT = 0,          // Don't mind Sharkbait. He just needs ta... empty his hold!
                                        // Bombs away!
                                        // Watch out below, ye barnacle-bottomed swine!
                                        // Yer doom be at hand!

    TALK_INTRO = 0,                     // Avast, ye bilge suckers!
                                        // Best be gettin' yer wills in order!

    TALK_UNMOUNT,                       // Aaargh! Sharkbait, come about and blast their broadsides!

    TALK_RANDOM,                        // Well, looks like someone still ain't got their sea legs!
                                        // This one is goin' right in yer deadlights!
                                        // Ye won't soon be forgettin' that taste.
                                        // Here's a shot across yer poop deck!
                                        // I'll scuttle yer hides!
                                        // Ha Ha! Don't crack yer teacup!

    TALK_INTERRUPT,                     // It be bad fortune ta spill a man's drink.

    TALK_CHARGE,                        // Ramming speed!
                                        // No quarter!

    TALK_JUST_DIED                      // Guess I... be off... ta the locker...
};

///< Npc Shark Bait - 129743
struct npc_sharkbait_creature : public ScriptedAI
{
    npc_sharkbait_creature(Creature* creature) : ScriptedAI(creature) {}

    void InitializeAI() override
    {
        me->SetUnitFlag(UnitFlags(UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_UNINTERACTIBLE));
        me->SetEmoteState(EMOTE_STATE_FLY_SIT_GROUND);
        me->CastSpell(me, SPELL_VILE_BOMBARDMENT_PERIODIC);
        me->DisableEvadeMode();
        me->SetReactState(REACT_PASSIVE);

        me->AddDelayedEvent(4000, [this]()
        {
            if (Creature* kragg = me->FindNearestCreature(NPC_SKYCAP_KRAGG_INTRO, 10.0f))
            {
                kragg->CastSpell(me, VEHICLE_SPELL_RIDE_HARDCODED, true);
                kragg->SetEmoteState(EMOTE_STATE_READY_BOW);
                kraggGuid = kragg->GetGUID();
            }
        });

        me->AddDelayedEvent(5000, [this]()
        {
            Movement::MoveSplineInit Init(me);
            for (auto&& itr : KraggIntroPositions)
                Init.Path().push_back(itr);
            Init.SetVelocity(15.0f);
            Init.SetUncompressed();
            Init.SetSmooth();
            Init.SetFly();
            Init.Launch();

            me->AddDelayedEvent(me->movespline->Duration() + 1000, [this]()
            {
                Movement::MoveSplineInit Init(me);
                for (auto&& itr : KraggIntroCyclicPositions)
                    Init.Path().push_back(itr);
                Init.SetVelocity(7.0f);
                Init.SetUncompressed();
                Init.SetSmooth();
                Init.SetCyclic();
                Init.SetFly();
                Init.Launch();
            });
        });
    }

    void SpellHitTarget(WorldObject* target, SpellInfo const* spell) override
    {
        if (target->IsUnit() && spell && spell->Id == SPELL_VILE_BOMBARDMENT_SELECT)
        {
            if (Creature* kragg = ObjectAccessor::GetCreature(*me, kraggGuid))
                kragg->AI()->Talk(TALK_VILE_BOMBARDMENT);

            DoCast(target->ToUnit(), SPELL_VILE_BOMBARDMENT_INTRO, true);
        }
    }

    void DoAction(int32 action) override
    {
        if (action == FreeholdAction::ACTION_SKYCAP_APPEAR)
        {
            auto instance = me->GetInstanceScript();
            if (Creature* Skycap = instance ? instance->GetCreature(NPC_SKYCAP_KRAGG) : nullptr)
            {
                me->RemoveAurasDueToSpell(SPELL_VILE_BOMBARDMENT_PERIODIC);

                Movement::MoveSplineInit Init(me);
                for (auto&& itr : KraggDestPositions)
                    Init.Path().push_back(itr);
                Init.SetVelocity(15.0f);
                Init.SetUncompressed();
                Init.SetSmooth();
                Init.SetFly();
                Init.Launch();

                me->AddDelayedEvent(me->movespline->Duration() + 1000, [this]()
                {
                    auto instance = me->GetInstanceScript();
                    if (Creature* Skycap = instance ? instance->GetCreature(NPC_SKYCAP_KRAGG) : nullptr)
                    {
                        if (Vehicle* vehicle = me->GetVehicleKit())
                        {
                            if (Unit* passenger = vehicle->GetPassenger(0))
                                if (Creature* creature = passenger->ToCreature())
                                    creature->DespawnOrUnsummon();
                        }
                        me->DespawnOrUnsummon();
                        Skycap->SetVisible(true);
                        Skycap->SetReactState(REACT_AGGRESSIVE);
                    }
                });
            }
        }
    }

private:
    ObjectGuid kraggGuid;
};

///< Npc Skycap Kragg - 126832 
struct boss_skycap_kragg : public BossAI
{
    boss_skycap_kragg(Creature* creature) : BossAI(creature, FreeholdData::DATA_SKYCAP_KRAGG)
    {
        ApplyAllImmunities(true);
        static uint32 const SpellId = std::numeric_limits<uint32>::max();
        me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_INTERRUPT_CAST, false);
        me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_INTERRUPT, false);
        me->SetVisible(false);
        me->SetReactState(REACT_PASSIVE);
    }

    void Reset() override
    {
        _Reset();
        me->SetPowerType(POWER_ENERGY);
        me->SetMaxPower(POWER_ENERGY, 100);
        me->SetPower(POWER_ENERGY, 100);
        me->Mount(KraggModel::SHARKBAIT_MODEL);
        mountGUID = ObjectGuid::Empty;
    }

    void JustSummoned(Creature* summon) override
    {
        if (summon && summon->GetEntry() == NPC_SHARKBAIT_BOSS)
        {
            mountGUID = summon->GetGUID();
            summon->SetReactState(REACT_PASSIVE);
            summon->GetMotionMaster()->MovePoint(KraggMovementPoint::MOVEMENT_POINT_FLY_AWAY, -1755.f, -1051.221f, 120.1845f);
        }
    }

    void MovementInform(uint32 type, uint32 pointId) override
    {
        if (type != EFFECT_MOTION_TYPE)
            return;

        if (pointId == EVENT_JUMP)
            DoCastSelf(KraggSpells::SPELL_CHARRRRRGE_DAMAGE, true);
    }

    void JustEngagedWith(Unit* who) override
    {
        Talk(KraggTalk::TALK_INTRO);
        _JustEngagedWith(who);
        events.ScheduleEvent(KraggEvents::EVENT_CHARRRRRGE, 3s);
        events.ScheduleEvent(KraggEvents::EVENT_PISTOL_SHOT, 7s);
        damageEvents.ScheduleEventBelowHealthPct(KraggEvents::EVENT_DEATH_RAINS_FROM_ABOVE, 75);
    }

    void OnSpellCastInterrupt(SpellInfo const* spell)
    {
        if (spell && spell->Id == KraggSpells::SPELL_REVITALIZING_BREW)
        {
            Talk(KraggTalk::TALK_INTERRUPT);
            me->RemoveAurasDueToSpell(KraggSpells::SPELL_REVITALIZING_BREW);
            DoCastSelf(KraggSpells::SPELL_REVITALIZING_BREW_MISSILE, true);
        }
    }

    void OnSpellFinished(SpellInfo const* spell) override
    {
        if (spell && spell->Id == KraggSpells::SPELL_REVITALIZING_BREW)
        {
            me->ClearUnitState(UNIT_STATE_ROOT);
            DoStartMovement(me->GetVictim());
        }
    }

    void OnSuccessfulSpellCast(SpellInfo const* spell)
    {
        if (!spell)
            return;

        switch (spell->Id)
        {
        case KraggSpells::SPELL_TRIGGER_POOP:
            if (Creature* sharkbait = ObjectAccessor::GetCreature(*me, mountGUID))
                if (Unit* target = SelectTarget(SelectTargetMethod::Random))
                    sharkbait->CastSpell(target, KraggSpells::SPELL_VILE_BOMBARDMENT, true);
            break;

        case KraggSpells::SPELL_TRIGGER_DIVE_BOMB:
            if (Creature* sharkbait = ObjectAccessor::GetCreature(*me, mountGUID))
            {
                sharkbait->StopMoving();
                sharkbait->GetMotionMaster()->Clear();

                Position targetpos = me->GetRandomPoint(KraggMiddlePos, 27.0f);
                sharkbait->CastSpell(targetpos, KraggSpells::SPELL_DIVE_BOMB_JUMP);
            }
            break;

        case KraggSpells::SPELL_AZERITE_POWER_SHOT:
            DoCastSelf(KraggSpells::SPELL_AZERITE_POWER_SHOT_VISUAL, true);
            break;

        default:
            break;
        }
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        events.Update(diff);

        if (me->HasUnitState(UNIT_STATE_CASTING) || me->HasAura(KraggSpells::SPELL_REVITALIZING_BREW))
            return;

        while (uint32 eventId = events.ExecuteEvent())
        {
            ExecuteEvent(eventId);
            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;
        }

        DoMeleeAttackIfReady();
    }

    void ExecuteEvent(uint32 eventId) override
    {
        switch (eventId)
        {
        case KraggEvents::EVENT_CHARRRRRGE:
            Talk(KraggTalk::TALK_CHARGE);
            if (Unit* target = SelectTarget(SelectTargetMethod::Random))
                me->CastSpell(target, KraggSpells::SPELL_CHARRRRRGE);
            events.Repeat(8s);
            break;

        case KraggEvents::EVENT_PISTOL_SHOT:
            if (Unit* target = SelectTarget(SelectTargetMethod::Random))
                me->CastSpell(target, KraggSpells::SPELL_PISTOL_SHOT);
            events.Repeat(10s);
            break;

        case KraggEvents::EVENT_DEATH_RAINS_FROM_ABOVE:
            Talk(KraggTalk::TALK_UNMOUNT);
            me->Dismount();
            me->InterruptNonMeleeSpells(true);
            DoCastSelf(KraggSpells::SPELL_SPAWN_PARROT, true);
            events.Reset();
            events.ScheduleEvent(KraggEvents::EVENT_AZERITE_POWDERSHOT, 7s);
            events.ScheduleEvent(KraggEvents::EVENT_VILE_BOMBARDMENT, 7s);
            events.ScheduleEvent(KraggEvents::EVENT_REVITALIZING_BREW, 11s);
            if (IsHeroic() || IsMythic())
                events.ScheduleEvent(KraggEvents::EVENT_DIVE_BOMBS, 15s);
            break;

        case KraggEvents::EVENT_AZERITE_POWDERSHOT:
            Talk(KraggTalk::TALK_RANDOM);
            DoCastRandom(KraggSpells::SPELL_AZERITE_POWER_SHOT, 75.0f);
            events.Repeat(10s);
            break;

        case KraggEvents::EVENT_REVITALIZING_BREW:
            me->StopMoving();
            me->AddUnitState(UNIT_STATE_ROOT);
            DoCastSelf(KraggSpells::SPELL_REVITALIZING_BREW);
            events.Repeat(20s);
            break;

        case KraggEvents::EVENT_VILE_BOMBARDMENT:
            DoCastSelf(KraggSpells::SPELL_TRIGGER_POOP, true);
            events.Repeat(7s);
            break;

        case KraggEvents::EVENT_DIVE_BOMBS:
            DoCastSelf(KraggSpells::SPELL_TRIGGER_DIVE_BOMB, true);
            events.Repeat(17s);
            break;

        default:
            break;
        }
    }

    void EnterEvadeMode(EvadeReason /*why*/) override
    {
        if (Creature* sharkbait = ObjectAccessor::GetCreature(*me, mountGUID))
            sharkbait->DespawnOrUnsummon();

        _EnterEvadeMode();
        if (instance)
        {
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            instance->SetBossState(FreeholdData::DATA_SKYCAP_KRAGG, FAIL);
        }
        _DespawnAtEvade();
    }

    void JustDied(Unit* /*killer*/) override
    {
        Talk(KraggTalk::TALK_JUST_DIED);
        if (Creature* sharkbait = ObjectAccessor::GetCreature(*me, mountGUID))
        {
            sharkbait->StopMoving();
            sharkbait->GetMotionMaster()->MovePoint(MOVEMENT_POINT_JUST_DEFEATED, -1763.66f, -1011.15f, 89.43428f);
        }
        _JustDied();
    }

private:
    ObjectGuid mountGUID;
};

///< Npc Shark Bait - 126841
struct npc_sharkbait_boss : public ScriptedAI
{
    npc_sharkbait_boss(Creature* creature) : ScriptedAI(creature)
    {
        diveBomb = false;

        SharkbaitWaypointsCopy.clear();
        for (auto&& itr : SharkbaitWaypoints)
            SharkbaitWaypointsCopy.push_back(itr);
    }

    void RotatePathToNearestPosition()
    {
        if (instance && instance->GetBossState(DATA_SKYCAP_KRAGG) != DONE)
        {
            uint8 count = 0;
            uint8 rotation = 0;
            float min_dist = 75.0f;

            //Find nearest position in path
            for (auto&& itr : SharkbaitWaypointsCopy)
            {
                float distance = me->GetExactDist2d(itr.GetPositionX(), itr.GetPositionY());
                if (distance < min_dist)
                {
                    rotation = count;
                    min_dist = distance;
                }
                count++;
            }

            //Start moves from nearest position
            std::rotate(SharkbaitWaypointsCopy.begin(), SharkbaitWaypointsCopy.begin() + rotation, SharkbaitWaypointsCopy.end());

            //Do not start cycle from current position
            me->GetMotionMaster()->MovePoint(MOVEMENT_POINT_FLY_AWAY, SharkbaitWaypointsCopy.front());
        }
    }

    void MovementInform(uint32 type, uint32 pointId) override
    {
        if (type != POINT_MOTION_TYPE && type != EFFECT_MOTION_TYPE)
            return;

        switch (pointId)
        {
        case KraggMovementPoint::MOVEMENT_POINT_FLY_AWAY:
        {
            me->AddDelayedEvent(1000, [this]()
            {
                Movement::MoveSplineInit Init(me);
                for (auto&& itr : SharkbaitWaypoints)
                    Init.Path().push_back(G3D::Vector3(itr.GetPositionX(), itr.GetPositionY(), itr.GetPositionZ()));
                Init.SetVelocity(7.0f);
                Init.SetUncompressed();
                Init.SetSmooth();
                Init.SetCyclic();
                Init.SetFly();
                Init.Launch();
            });
            break;
        }

        case KraggMovementPoint::MOVEMENT_POINT_DIVE_BOMB:
        {
            diveBomb = !diveBomb;
            if (diveBomb)
            {
                me->SetFacingTo(me->GetAngle(KraggMiddlePos));
                me->AddDelayedEvent(2000, [this]()
                {
                    Position targetpos = me->GetPositionWithDistInFront(50.0f);
                    me->UpdateAllowedPositionZ(targetpos.GetPositionX(), targetpos.GetPositionY(), targetpos.m_positionZ);
                    me->CastSpell(targetpos, KraggSpells::SPELL_DIVE_BOMB_DAMAGE, true);
                });
            }
            else
                me->AddDelayedEvent(1000, [this]() { RotatePathToNearestPosition(); });
            break;
        }

        case KraggMovementPoint::MOVEMENT_POINT_JUST_DEFEATED:
        {
            if (instance)
            {
                instance->DoPlayConversation(CONVERSATION_SHARKBAIT_OUTRO);
                me->SetFacingTo(float(M_PI_2));
                me->AddDelayedEvent(8000, [this]() { me->GetMotionMaster()->MovePoint(0, -1865.8f, -829.222f, 133.511f); });
                me->DespawnOrUnsummon(15s);
            }
            break;
        }

        default:
            break;
        }
    }

private:
    bool diveBomb;
    std::vector<Position> SharkbaitWaypointsCopy;
};

///< Npc Revitalizing Brew - 134021
struct npc_revitalizing_brew : public ScriptedAI
{
    npc_revitalizing_brew(Creature* creature) : ScriptedAI(creature)
    {
        me->SetNpcFlag(UNIT_NPC_FLAG_SPELLCLICK);
    }

    void OnSpellClick(Unit* clicker, bool /*result*/) override
    {
        clicker->CastSpell(clicker, KraggSpells::SPELL_REVITALIZING_BREW_PLAYER);
        me->DespawnOrUnsummon();
    }
};

///< AreaTrigger Vile Bombardment Intro - AtID: 16712, SpellID: 257273
struct at_vile_bombardment : public AreaTriggerAI
{
    at_vile_bombardment(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger) {}

    void OnUnitEnter(Unit* unit)
    {
        Unit* caster = at->GetCaster();
        if (!caster || !unit)
            return;

        if (caster->IsValidAttackTarget(unit))
            unit->CastSpell(unit, KraggSpells::SPELL_VILE_COATING_INTRO, CastSpellExtraArgs(true).SetOriginalCaster(caster->GetGUID()));
    }

    void OnUnitExit(Unit* unit)
    {
        if (unit && unit->HasAura(KraggSpells::SPELL_VILE_COATING_INTRO))
            unit->RemoveAurasDueToSpell(KraggSpells::SPELL_VILE_COATING_INTRO);
    }
};

///< Areatrigger Vile Bombardment Boss - AtID: 16608, SpellID: 256035
struct at_boss_vile_bombardment : public AreaTriggerAI
{
    at_boss_vile_bombardment(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger)
    {
        at->SetPeriodicProcTimer(500);
    }

    void OnPeriodicProc() override
    {
        Unit* caster = at->GetCaster();
        if (!caster)
            return;

        for (ObjectGuid guid : at->GetInsideUnits())
        {
            if (Player* player = ObjectAccessor::GetPlayer(*caster, guid))
                if (!player->HasAura(KraggSpells::SPELL_VILE_COATING))
                    player->CastSpell(player, KraggSpells::SPELL_VILE_COATING, CastSpellExtraArgs(true).SetOriginalCaster(caster->GetGUID()));
        }
    }

    void OnUnitExit(Unit* unit)
    {
        if (unit && unit->HasAura(KraggSpells::SPELL_VILE_COATING))
        {
            if (Aura* aura = unit->GetAura(KraggSpells::SPELL_VILE_COATING))
            {
                if (aura->GetStackAmount() > 1)
                    unit->SetAuraStack(KraggSpells::SPELL_VILE_COATING, unit, aura->GetStackAmount() - 1);
                else
                    unit->RemoveAurasDueToSpell(KraggSpells::SPELL_VILE_COATING);
            }
        }
    }
};

//12548
struct achievement_i_am_in_charge_now : public AchievementCriteriaScript
{
public:
    achievement_i_am_in_charge_now() : AchievementCriteriaScript("achievement_i_am_in_charge_now") { }

    bool OnCheck(Player* /*player*/, Unit* /*target*/) override
    {
        //ACHIEVEMENT_I_M_IN_CHARGE_NOW
        return false;
    }
};

//12550
struct achievement_pecking_order : public AchievementCriteriaScript
{
public:
    achievement_pecking_order() : AchievementCriteriaScript("achievement_pecking_order") { }

    bool OnCheck(Player* /*player*/, Unit* /*target*/) override
    {
        //ACHIEVEMENT_PECKING_ORDER
        return false;
    }
};


void AddSC_boss_skycap_kragg()
{
    //Creatures
    RegisterCreatureAI(boss_skycap_kragg);
    RegisterCreatureAI(npc_sharkbait_boss);
    RegisterCreatureAI(npc_sharkbait_creature);
    RegisterCreatureAI(npc_revitalizing_brew);

    //Areatriggers
    RegisterAreaTriggerAI(at_vile_bombardment);
    RegisterAreaTriggerAI(at_boss_vile_bombardment);

    //Achievements
    new achievement_i_am_in_charge_now();
    new achievement_pecking_order();
}
