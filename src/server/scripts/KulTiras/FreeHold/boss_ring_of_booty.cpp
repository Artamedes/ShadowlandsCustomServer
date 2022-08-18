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
#include "MoveSpline.h"
#include "MoveSplineInit.h"
#include "ScriptedGossip.h"

enum RingOfBootySpells
{
    ///Lightning
    SPELL_GRABBING              = 257831,
    SPELL_PICKUP_PIG            = 257915,
    SPELL_SLIPPERY              = 257949,
    SPELL_GREASY                = 257829,
    SPELL_GREASY_DUMMY          = 257950,

    ///Ludwig Von Tortollan
    SPELL_BOUNCE                = 257904,
    SPELL_BOUNCE_DMG            = 257902,

    ///Trothak
    SPELL_FIREWORKS             = 268127,
    SPELL_RIDE_SHARK            = 256410,
    SPELL_RIGHT_SHARK_RIDING    = 256368,
    SPELL_LEFT_SHARK_RIDING     = 256402,
    SPELL_HAMMER_SHARK          = 256918,
    SPELL_SAWTOOTH_SHARK        = 256923,
    SPELL_RIPPER_PUNCH          = 256363,
    SPELL_SHARK_TORNADO         = 256405,
    SPELL_SHARK_TOSS            = 256424,
    SPELL_SHARK_TOSS_DMG        = 256477,
    SPELL_REARM_ONE             = 256489,
    SPELL_REARM_TWO             = 256494,
    SPELL_REARM_DMG             = 256706,

    SPELL_COSMETIC_BONFIRE      = 259096, //COSMETIC - Bonfire (DNT)
    SPELL_MOD_SCALE_MINUS_50    = 162428, //Mod Scale -50%
    SPELL_MOD_SCALE_MINUS_70    = 162457, //Mod Scale -70%
    SPELL_ON_FIRE               = 36301,  //On Fire

    ///Heroic && Mythic Only
    SPELL_FLAILING_SHARK_AURA   = 256550,
    SPELL_FLAILING_SHARK_JUMP   = 256551,
    SPELL_FLAILING_SHARK_DUMMY  = 256553,
    SPELL_THROW_CHUM_TS         = 272531,
    SPELL_THROW_CHUM_MISSILE    = 272534,
    SPELL_THROW_CHUM_AT         = 272548,
    SPELL_EAT_CHUM              = 272569,
    SPELL_BLOODY_MESS           = 272554,

    //TODO Full Stomach 290068
};

enum RingOfBootyEvents
{
    ///Ludwig Von Tortollan
    EVENT_SHELL_BOUNCE = 1,

    ///Trothak
    EVENT_RIPPER_PUNCH,
    EVENT_SHARK_TORNADO,
    EVENT_SHARK_TOSS,
    EVENT_REARM,
    EVENT_THROW_CHUM
};

enum RingOfBootyPoint
{
    MOVEMENT_POINT_PIG_CENTER = 1,
    MOVEMENT_POINT_PIG_RUN,
    MOVEMENT_POINT_LUDWIG_JUMP,
};

enum RingOfBootyAction
{
    ACTION_SECOND_EVENT,
    ACTION_THIRD_EVENT,
    ACTION_SHARK_TORNADO,
};

enum RingOfBootyTalks
{
    TALK_DAVEY_START,   /* Gather 'round and place yer bets! We got a new set of vict-- uh... competitors!
                         Take it away, Gurgthok and Wodin!*/
};

///< Npc Davey "Two Eyes" - 130086
struct npc_davey : public ScriptedAI
{
    npc_davey(Creature* creature) : ScriptedAI(creature)
    {
        eventStarted = false;
    }

    bool OnGossipHello(Player* player) override
    {
        if (player && !eventStarted)
        {
            AddGossipItemFor(player, 21844, 0, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
            SendGossipMenuFor(player, player->GetGossipTextId(me), me->GetGUID());
        }
        return true;
    }

    bool OnGossipSelect(Player* player, uint32 /*sender*/, uint32 /*action*/) override
    {
        if (!eventStarted && player)
            if (auto instance = player->GetInstanceScript())
        {
            eventStarted = true;
            Talk(RingOfBootyTalks::TALK_DAVEY_START);
            CloseGossipMenuFor(player);

            me->AddDelayedEvent(4 * IN_MILLISECONDS, [this]()
            {
                Movement::MoveSplineInit init(me);
                for (auto itr : DaveyLeavePath)
                    init.Path().push_back(itr);
                init.SetWalk(true);
                init.SetSmooth();
                init.Launch();
                me->DespawnOrUnsummon(Milliseconds(me->movespline->Duration()));
            });

            if (Creature* gurgthock = instance->GetCreature(NPC_GURGTHOCK))
            {
                gurgthock->AddDelayedEvent(10 * IN_MILLISECONDS, [this, instance]()
                {
                    if (instance)
                        instance->DoPlayConversation(CONVERSATION_RING_OF_BOOTY_INTRO);
                });

                gurgthock->AddDelayedEvent(64 * IN_MILLISECONDS, [this, instance]()
                {
                    if (instance)
                    {
                        if (Creature* ken = instance->GetCreature(NPC_KEN))
                            ken->HandleEmoteCommand(EMOTE_ONESHOT_BATTLE_ROAR);

                        if (Creature* lightning = instance->GetCreature(NPC_LIGHTNING))
                            lightning->GetMotionMaster()->MoveJump(ArenaMiddlePos, 10.0f, 17.79251f, RingOfBootyPoint::MOVEMENT_POINT_PIG_CENTER);
                    }
                });
            }
        }
        return true;
    }

private:
    bool eventStarted;
};

///< Npc Gurgthock - 129350
struct npc_gurgthock : public ScriptedAI
{
    npc_gurgthock(Creature* creature) : ScriptedAI(creature) {}

    void InitializeAI() override
    {
        auto instance = me->GetInstanceScript();
        if (instance && instance->GetBossState(FreeholdData::DATA_RING_OF_BOOTY) != DONE)
        {
            if (me->isDead())
                me->Respawn();

            if (Creature* lightning = instance->GetCreature(FreeholdCreature::NPC_LIGHTNING))
                if (lightning->isDead())
                    lightning->Respawn(true);

            if (Creature* davey = instance->GetCreature(FreeholdCreature::NPC_DAVEY))
                if (davey->isDead())
                    davey->Respawn(true);

            if (Creature* tortollan = instance->GetCreature(FreeholdCreature::NPC_LUDWIG_VON_TORTOLLAN))
                if (tortollan->isDead())
                    tortollan->Respawn(true);
        }
    }

    void DoAction(int32 const action) override
    {
        auto instance = me->GetInstanceScript();
        if (instance)
        {
            switch (action)
            {
                case RingOfBootyAction::ACTION_SECOND_EVENT:
                {
                    instance->DoPlayConversation(CONVERSATION_RING_OF_BOOTY_LUDWIG);

                    me->AddDelayedEvent(18 * IN_MILLISECONDS, [this, instance]()
                    {
                        if (Creature* ludwig = instance ? instance->GetCreature(NPC_LUDWIG_VON_TORTOLLAN) : nullptr)
                            ludwig->GetMotionMaster()->MoveJump(LudwigJumpPos, 10.0f, 13.37141f, RingOfBootyPoint::MOVEMENT_POINT_LUDWIG_JUMP);
                    });
                    break;
                }
                case RingOfBootyAction::ACTION_THIRD_EVENT:
                {
                    instance->DoPlayConversation(CONVERSATION_RING_OF_BOOTY_THROTHAK);
                    instance->instance->SummonCreature(NPC_TROTHAK, TrothakSpawnPos);
                    break;
                }
            }
        }
    }
};

///< Npc Lightning - 130099
struct npc_lightning : public ScriptedAI
{
    npc_lightning(Creature* creature) : ScriptedAI(creature)
    {
        me->SetUnitFlag(UnitFlags(UNIT_FLAG_UNINTERACTIBLE | UNIT_FLAG_NON_ATTACKABLE));
        me->SetSpeed(MOVE_RUN, 20.0f);
    }

    Creature* GetRandomTarget()
    {
        Trinity::Containers::RandomShuffle(shellTargets);
        for (Creature* target : shellTargets)
        {
            if (me->GetDistance(target) < 15.0f)
                continue;
            else return target;
        }
        return me;
    }

    void Reset() override
    {
        timer = 500;
        me->DisableEvadeMode();
        me->SetReactState(REACT_PASSIVE);
        GetCreatureListWithEntryInGrid(shellTargets, me, NPC_SHELL_TARGET, 75.0f);
    }

    void MovementInform(uint32 type, uint32 pointId) override
    {
        if (type == EFFECT_MOTION_TYPE && pointId == RingOfBootyPoint::MOVEMENT_POINT_PIG_CENTER)
        {
            me->SetAuraStack(RingOfBootySpells::SPELL_GREASY, me, 5);
            me->CastSpell(me, RingOfBootySpells::SPELL_GREASY_DUMMY, true);
            me->RemoveUnitFlag(UNIT_FLAG_UNINTERACTIBLE);
        }
    }

    void SpellHit(WorldObject* caster, SpellInfo const* spellInfo) override
    {
        if (spellInfo && spellInfo->Id == RingOfBootySpells::SPELL_GRABBING)
        {
            if (Aura* greasy = me->GetAura(SPELL_GREASY))
            {
                uint8 stacks = greasy->GetStackAmount();
                if (stacks > 1)
                {
                    stacks--;
                    greasy->SetStackAmount(stacks);
                    caster->CastSpell(caster, RingOfBootySpells::SPELL_SLIPPERY, true);
                }
                else if (caster)
                {
                    me->RemoveAurasDueToSpell(SPELL_GREASY);
                    me->RemoveAurasDueToSpell(SPELL_GREASY_DUMMY);
                    me->GetMotionMaster()->Clear();
                    me->RemoveNpcFlag(UNIT_NPC_FLAG_SPELLCLICK);
                    me->CastSpell(caster, SPELL_PICKUP_PIG, true);

                    me->GetScheduler().Schedule(Seconds(7), [this](TaskContext context)
                    {
                        if (instance)
                        {
                            if (Creature* gurgthock = instance->GetCreature(FreeholdCreature::NPC_GURGTHOCK))
                                gurgthock->AI()->DoAction(RingOfBootyAction::ACTION_SECOND_EVENT);
                        }

                        if (Creature* pig = GetContextCreature())
                        {
                            Movement::MoveSplineInit init(me);
                            for (auto itr : LightningLeavePath)
                                init.Path().push_back(itr);
                            init.SetSmooth();
                            init.Launch();

                            pig->DespawnOrUnsummon(Milliseconds(pig->movespline->Duration() + 1000));
                        }
                    });
                }
            }
        }
    }

    void UpdateAI(uint32 diff) override
    {
        if (timer <= diff)
        {
            timer = 2000;

            if (me->HasAura(SPELL_GREASY) && !me->isMoving())
            {
                me->GetMotionMaster()->Clear();
                me->GetMotionMaster()->MoveCloserAndStop(RingOfBootyPoint::MOVEMENT_POINT_PIG_RUN, GetRandomTarget(), frand(0.0f, 5.0f));
            }
        }
        else timer -= diff;
    }

private:
    uint32 timer;
    std::vector<Creature*> shellTargets;
};

///< Npc Ludwig Von Tortollan - 129699
struct npc_ludwig_von_tortollan : public ScriptedAI
{
    npc_ludwig_von_tortollan(Creature* creature) : ScriptedAI(creature)
    {
        ApplyAllImmunities(true);
        me->SetReactState(REACT_PASSIVE);
        me->SetFaction(FACTION_FRIENDLY);
    }

    void Reset() override
    {
        events.Reset();
    }

    void MovementInform(uint32 type, uint32 pointId) override
    {
        if (type == EFFECT_MOTION_TYPE && pointId == RingOfBootyPoint::MOVEMENT_POINT_LUDWIG_JUMP)
        {
            me->SetHomePosition(LudwigJumpPos);
            me->SetFacingTo(me->GetAngle(ArenaMiddlePos));

            me->GetScheduler().Schedule(Seconds(2), [this](TaskContext context)
            {
                if (Creature* ludwig = GetContextCreature())
                {
                    ludwig->HandleEmoteCommand(EMOTE_ONESHOT_BATTLE_ROAR);
                    ludwig->SetFaction(FACTION_MONSTER_2);
                    ludwig->SetReactState(REACT_AGGRESSIVE);
                }
            });
        }
    }

    void JustEngagedWith(Unit* /*who*/) override
    {
        events.ScheduleEvent(RingOfBootyEvents::EVENT_SHELL_BOUNCE, 7s);
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        events.Update(diff);

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        while (uint32 eventId = events.ExecuteEvent())
        {
            if (eventId == RingOfBootyEvents::EVENT_SHELL_BOUNCE)
            {
                if (Unit* target = SelectTarget(SelectTargetMethod::Random))
                    me->CastSpell(target, RingOfBootySpells::SPELL_BOUNCE);
                events.Repeat(6s);
                break;
            }
        }

        DoMeleeAttackIfReady();
    }

    void JustDied(Unit* /*killer*/) override
    {
        if (Creature* gurgthock = instance->GetCreature(FreeholdCreature::NPC_GURGTHOCK))
            gurgthock->AI()->DoAction(RingOfBootyAction::ACTION_THIRD_EVENT);
    }
};

///< Npc Trothak - 126969
struct boss_trothak : public BossAI
{
    boss_trothak(Creature* creature) : BossAI(creature, FreeholdData::DATA_RING_OF_BOOTY)
    {
        ApplyAllImmunities(true);
    }

    void InitializeAI() override
    {
        Movement::MoveSplineInit init(me);
        for (auto itr : TrothakIntroPath)
            init.Path().push_back(itr);
        init.SetWalk(true);
        init.SetVelocity(3.5f);
        init.SetSmooth();
        init.Launch();

        int32 timer = me->movespline->Duration();
        me->AddDelayedEvent(timer, [this]() { me->HandleEmoteCommand(EMOTE_ONESHOT_BATTLE_ROAR); });
        me->AddDelayedEvent(timer + 1000, [this]()
        {
            me->SetFaction(FACTION_MONSTER);
            me->SetReactState(REACT_AGGRESSIVE);
            me->SetHomePosition(me->GetPosition());
        });
        me->AddDelayedEvent(16 * IN_MILLISECONDS, [this]() { DoCastSelf(RingOfBootySpells::SPELL_FIREWORKS, true); });
        me->AddDelayedEvent(18 * IN_MILLISECONDS, [this]()
        {
            DoCastSelf(RingOfBootySpells::SPELL_FIREWORKS, true);

            if (!instance || !instance->instance)
                return;

            for (auto&& itr : BonfireSpawnPos)
                if (Creature* bonfire = instance->instance->SummonCreature(NPC_BONFIRE_SPAWN, itr))
                    bonfire->AddAura(urand(0, 1) ? SPELL_MOD_SCALE_MINUS_50 : SPELL_MOD_SCALE_MINUS_70);

            if (Creature* bonfire = instance->GetCreature(NPC_BONFIRE_SPAWN))
            {
                std::list<Creature*> fanatics;
                GetCreatureListWithEntryInGrid(fanatics, bonfire, NPC_BOOTY_FANATIC, 10.0f);

                for (Creature* fanatic : fanatics)
                {
                    fanatic->CastSpell(fanatic, RingOfBootySpells::SPELL_ON_FIRE, true);
                    fanatic->SetAIAnimKitId(644 /*Scared*/);
                    fanatic->GetMotionMaster()->MoveRandom(5.0f);
                    fanatic->DespawnOrUnsummon(10s);
                }
            }
        });
        me->AddDelayedEvent(20 * IN_MILLISECONDS, [this]() { DoCastSelf(RingOfBootySpells::SPELL_FIREWORKS, true); });
        me->AddDelayedEvent(22 * IN_MILLISECONDS, [this]() { DoCastSelf(RingOfBootySpells::SPELL_FIREWORKS, true); });
        Reset();
    }

    void Initialize()
    {
        me->SummonCreature(FreeholdCreature::NPC_HAMMER_SHARK, me->GetPosition());
        me->SummonCreature(FreeholdCreature::NPC_SAWTOOTH_SHARK, me->GetPosition());
    }

    void Clean()
    {
        std::list<AreaTrigger*> atList;
        me->GetAreaTriggerListWithSpellIDInRange(atList, RingOfBootySpells::SPELL_THROW_CHUM_AT, 75.0f);
        for (AreaTrigger* at : atList)
            at->Remove();

        shark1GUID.Clear();
        shark2GUID.Clear();
    }

    void Reset() override
    {
        _Reset();
        Clean();
        Initialize();
    }

    void JustEngagedWith(Unit* /*who*/) override
    {
        events.ScheduleEvent(RingOfBootyEvents::EVENT_RIPPER_PUNCH, 3s);
        events.ScheduleEvent(RingOfBootyEvents::EVENT_SHARK_TOSS, 15s);
        events.ScheduleEvent(RingOfBootyEvents::EVENT_SHARK_TORNADO, 22s);

        if (IsHeroic() || IsMythic())
            events.ScheduleEvent(RingOfBootyEvents::EVENT_THROW_CHUM, 8s);
    }

    void MovementInform(uint32 type, uint32 pointId) override
    {
        if (pointId == EVENT_CHARGE)
        {
            me->RemoveAurasDueToSpell(SPELL_REARM_ONE);
            AttackStart(me->GetVictim());

            if (Creature* shark = ObjectAccessor::GetCreature(*me, shark2GUID))
            {
                shark2GUID = shark1GUID;
                shark->AddAura(RingOfBootySpells::SPELL_RIDE_SHARK, me);
            }
        }
    }

    void LaunchShark(uint8 seat)
    {
        if (Vehicle* vehicle = me->GetVehicleKit())
        {
            if (Unit* shark = vehicle->GetPassenger(seat))
            {
                shark2GUID = shark1GUID;
                shark1GUID = shark->GetGUID();
                shark->ExitVehicle();

                if (Unit* target = SelectTarget(SelectTargetMethod::Random))
                    shark->CastSpell(target, RingOfBootySpells::SPELL_SHARK_TOSS, false);
            }
        }
    }

    void DoAction(int32 action) override
    {
        if (action == ACTION_SHARK_TORNADO)
        {
            LaunchShark(1);
            events.ScheduleEvent(RingOfBootyEvents::EVENT_REARM, 1s);
            events.ScheduleEvent(RingOfBootyEvents::EVENT_REARM, 7s);
            events.ScheduleEvent(RingOfBootyEvents::EVENT_SHARK_TOSS, 15s);
            events.ScheduleEvent(RingOfBootyEvents::EVENT_SHARK_TORNADO, 20s);
        }
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        events.Update(diff);

        if (me->HasUnitState(UNIT_STATE_CASTING) || me->HasAura(RingOfBootySpells::SPELL_SHARK_TORNADO))
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
        case RingOfBootyEvents::EVENT_RIPPER_PUNCH:
            DoCast(SelectMeleeTarget(true), RingOfBootySpells::SPELL_RIPPER_PUNCH);
            events.Repeat(30s);
            break;

        case RingOfBootyEvents::EVENT_THROW_CHUM:
            DoCastSelf(RingOfBootySpells::SPELL_THROW_CHUM_TS);
            events.Repeat(6s);
            break;

        case RingOfBootyEvents::EVENT_SHARK_TORNADO:
            DoCastSelf(RingOfBootySpells::SPELL_SHARK_TORNADO);
            break;

        case RingOfBootyEvents::EVENT_SHARK_TOSS:
            LaunchShark(0);
            break;

        case RingOfBootyEvents::EVENT_REARM:
            if (Creature* shark = ObjectAccessor::GetCreature(*me, shark2GUID))
            {
                shark->StopMoving();
                me->AttackStop();
                me->CastStop();
                me->GetMotionMaster()->Clear();
                me->AddAura(RingOfBootySpells::SPELL_REARM_ONE);
                me->GetMotionMaster()->MoveCharge(shark->GetPositionX(), shark->GetPositionY(), shark->GetPositionZ());
            }
            break;

        default:
            break;
        }
    }

    private:
        ObjectGuid shark1GUID;
        ObjectGuid shark2GUID;
};

///< Npc Hammer Shark and Sawtooth Shark - 129448, 129359
struct npc_shark_trothak : public ScriptedAI
{
    npc_shark_trothak(Creature* creature) : ScriptedAI(creature) {}

    void IsSummonedBy(WorldObject* summoner) override
    {
        ObjectGuid summonerGuid = summoner ? summoner->GetGUID() : ObjectGuid::Empty;
        me->AddDelayedEvent(1 * IN_MILLISECONDS, [this, summonerGuid]() -> void
        {
            if (Unit* summoner = ObjectAccessor::GetUnit(*me, summonerGuid))
            {
                if (me->GetEntry() == FreeholdCreature::NPC_HAMMER_SHARK)
                    me->CastSpell(me, RingOfBootySpells::SPELL_HAMMER_SHARK, true);

                else if (me->GetEntry() == FreeholdCreature::NPC_SAWTOOTH_SHARK)
                    me->CastSpell(me, RingOfBootySpells::SPELL_SAWTOOTH_SHARK, true);

                me->AddAura(RingOfBootySpells::SPELL_RIDE_SHARK, summoner);
            }
        });
    }

    void MovementInform(uint32 type, uint32 pointId) override
    {
        if (pointId == EVENT_JUMP)
        {
            DoCastSelf(RingOfBootySpells::SPELL_SHARK_TOSS_DMG, true);
            DoCastSelf(RingOfBootySpells::SPELL_FLAILING_SHARK_AURA, true);
            me->SetReactState(REACT_AGGRESSIVE);
            DoZoneInCombat();
        }
    }

    void OnVehicleEntered(Unit* vehicle) override
    {
        me->SetReactState(REACT_PASSIVE);
        me->CombatStop();
        me->RemoveAurasDueToSpell(RingOfBootySpells::SPELL_FLAILING_SHARK_AURA);
        me->RemoveAurasDueToSpell(RingOfBootySpells::SPELL_BLOODY_MESS);

        if (me->GetEntry() == NPC_SAWTOOTH_SHARK)
            vehicle->CastSpell(vehicle, RingOfBootySpells::SPELL_LEFT_SHARK_RIDING, true);
        else
            vehicle->CastSpell(vehicle, RingOfBootySpells::SPELL_RIGHT_SHARK_RIDING, true);
    }

    void OnSuccessfulSpellCast(SpellInfo const* spell) override
    {
        if (spell && spell->Id == RingOfBootySpells::SPELL_FLAILING_SHARK_DUMMY)
        {
            if (Unit* target = SelectTarget(SelectTargetMethod::Random))
                me->CastSpell(target, RingOfBootySpells::SPELL_FLAILING_SHARK_JUMP, true);
        }
    }
};

///< Spell Shark Tornado - 256405
struct spell_shart_tornado : public AuraScript
{
    PrepareAuraScript(spell_shart_tornado);

    void HandleOnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* caster = GetCaster())
            if (auto creature = caster->ToCreature())
                if (creature->AI())
                    creature->AI()->DoAction(ACTION_SHARK_TORNADO);
    }

    void Register() override
    {
        OnEffectRemove += AuraEffectRemoveFn(spell_shart_tornado::HandleOnRemove, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL, AURA_EFFECT_HANDLE_REAL);
    }
};

///< Spell Throw Chum - 272531
struct spell_throw_chum : public SpellScript
{
    PrepareSpellScript(spell_throw_chum);

    void HandleOnEffectHitTarget(SpellEffIndex effIndex)
    {
        if (Unit* target = GetHitUnit())
        {
            Position pos = target->GetRandomPoint(ArenaMiddlePos, frand(5.0f, 25.0f));
            target->CastSpell(pos, RingOfBootySpells::SPELL_THROW_CHUM_MISSILE, true);
        }         
    }

    void HandleTargets(std::list<WorldObject*>& targetsList)
    {
        targetsList.remove_if([this](WorldObject* obj)->bool
        {
            return !obj || obj->GetEntry() != NPC_BOOTY_FANATIC;
        });
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_throw_chum::HandleOnEffectHitTarget, EFFECT_0, SPELL_EFFECT_DUMMY);
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_throw_chum::HandleTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ENTRY);
    }
};

///< Areatriger Shell Bounce - SpellId: 257905, AtId: 16776
struct at_shell_bounce: AreaTriggerAI
{
    at_shell_bounce(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger) {}

    void OnInitialize() override
    {
        if (Unit* caster = at->GetCaster())
        {
            std::list<Creature*> shellTargets;
            Creature* target = nullptr;
            for (uint8 i = 0; i < 4; i++)
            {
                std::list<Creature*> posibleTargets;
                GetCreatureListWithEntryInGrid(posibleTargets, caster, NPC_SHELL_TARGET, 75.0f);
                if (target)
                {
                    posibleTargets.remove_if([target](Creature* creature)
                    {
                        return !creature || target->GetDistance(creature) < 15.0f;
                    });
                }
                target = Trinity::Containers::SelectRandomContainerElement(posibleTargets);
                shellTargets.push_back(target);
            }

            std::vector<G3D::Vector3> splinePoints;
            splinePoints.push_back(G3D::Vector3(caster->GetPositionX(), caster->GetPositionY(), caster->GetPositionZ()));

            for (Creature* itr : shellTargets)
                splinePoints.push_back(G3D::Vector3(itr->GetPositionX(), itr->GetPositionY(), itr->GetPositionZ()));
            at->InitSplines(splinePoints, at->GetDuration());
        }
    }

    void OnUnitEnter(Unit * unit) override
    {
        Unit* caster = at->GetCaster();
        if (!caster || !unit)
            return;

        if (caster->IsValidAttackTarget(unit))
            unit->CastSpell(unit, SPELL_BOUNCE_DMG, CastSpellExtraArgs(true).SetOriginalCaster(caster->GetGUID()));
    }
};

///< Areatriger Rearm - SpellId: 256494, AtId: 11954
struct at_rearm_trothak : AreaTriggerAI
{
    at_rearm_trothak(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger) { }

    void OnUnitEnter(Unit* unit) override
    {
        if (Unit* caster = at->GetCaster())
            if (unit && caster->IsValidAttackTarget(unit))
                caster->CastSpell(unit, RingOfBootySpells::SPELL_REARM_DMG, true);
    }
};

///< Areatriger Bloody Mess - SpellId: 272548, AtId: 18163
struct at_bloody_mess : AreaTriggerAI
{
    at_bloody_mess(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger) {}

    void OnUnitEnter(Unit* unit)
    {
        if (unit->IsPlayer())
        {
            if (!unit->HasAura(RingOfBootySpells::SPELL_BLOODY_MESS))
                unit->CastSpell(unit, RingOfBootySpells::SPELL_BLOODY_MESS, true);
        }
        else if (unit->IsCreature() && !unit->IsOnVehicle() || (unit->GetEntry() == NPC_SAWTOOTH_SHARK || unit->GetEntry() == NPC_HAMMER_SHARK))
        {
            unit->CastSpell(at->GetPosition(), RingOfBootySpells::SPELL_EAT_CHUM);

            //8.0.1 Any sharks moving through the area consume the chum and have their movement slowed until they are picked up.
            if (!unit->HasAura(RingOfBootySpells::SPELL_BLOODY_MESS))
                unit->CastSpell(unit, RingOfBootySpells::SPELL_BLOODY_MESS, true);

            //TODO
            //8.1.x Any sharks moving through the area consume the chum and stop flailing for 3s.
            //Spell Full Stomach

            at->Remove();
        }
    }

    void OnUnitExit(Unit* unit)
    {
        if (unit && unit->HasAura(RingOfBootySpells::SPELL_BLOODY_MESS))
            unit->RemoveAurasDueToSpell(RingOfBootySpells::SPELL_BLOODY_MESS);
    }
};


void AddSC_boss_ring_of_booty()
{
    //Creatures
    RegisterCreatureAI(npc_davey);
    RegisterCreatureAI(npc_gurgthock);
    RegisterCreatureAI(npc_lightning);
    RegisterCreatureAI(npc_ludwig_von_tortollan);
    RegisterCreatureAI(boss_trothak);
    RegisterCreatureAI(npc_shark_trothak);

    //Spells
    RegisterSpellScript(spell_throw_chum);

    //Auras
    RegisterSpellScript(spell_shart_tornado);

    //Areatriggers
    RegisterAreaTriggerAI(at_shell_bounce);
    RegisterAreaTriggerAI(at_rearm_trothak);
    RegisterAreaTriggerAI(at_bloody_mess);
}
