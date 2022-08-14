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

enum FreeHoldTrashSpells
{
    //Irontide Enforcer
    BrutalBackhand               = 257426,
    ShatteringToss               = 274860,
    ShatteringTossLaunch         = 274862,
    ShatteringTossDmg            = 274890,
    //Irontide Mastiff          
    CripplingBite                = 257478,
    BestialWrath                 = 257476,
    //Irontide Corsair          
    PoisoningStrike              = 257436,
    //Irontide Crackshot        
    AzeriteGrenade               = 258672,
    Shoot                        = 268440,
    //Irontide Bonesaw          
    FilthyBlade                  = 258321,
    HealingBalm                  = 257397,
    //Blacktooth Brute          
    EarthShaker                  = 257747,
    //Cutwater Duelist          
    DuelistDash                  = 274400,
    //Irontide Oarsman          
    SeaSpoutDummy                = 258777,
    SeaSpout                     = 258778,
    //Bilge Rat Padfoot         
    PlagueStep                   = 257774,
    //Cutwater Knife Juggler    
    RicochetingThrow             = 272402,
    //Vermin Trapper            
    RatTrapsDummy                = 274383,
    RatTrapsMissile              = 274384,
    RatTrapsDamage               = 274389,
    //Soggy Shiprat             
    ScabrousBite                 = 274555,
    //BlacktoothKnuckleduster
    ShatteringBellow             = 257732,
    //Blacktooth Scrapper       
    BlindRage                    = 257739,
    BlindRageAura                = 257741,
    //Cutwater Harpooner        
    DraggingHarpoon              = 272412,
    //Irontide Crusher          
    BoulderThrow                 = 258181,
    GroundShatter                = 258199,
    //Irontide Officer          
    OiledBlade                   = 257908,
    //Irontide Ravager          
    PainfulMotivation            = 257899,
    //Irontide Stormcaller      
    LightningBolt                = 259092,
    ThunderingSquall             = 257736,
    //Irontide Buccaneers       
    BladeBarrage                 = 257870,
    //Bilge Rat Brinescale
    WaterBolt                    = 281420,
    FrostBlast                   = 257784,
};

enum FreeHoldTrashEvents
{
    //Irontide Enforcer
    EventBrutalBackhand = 1,
    EventShatteringToss,
    //Irontide Mastiff
    EventCripplingBite,
    EventBestialWrath,
    //Irontide Corsair
    EventPoisoningStrike,
    //Irontide Crackshot
    EventAzeriteGrenade,
    EventShoot,
    //Irontide Bonesaw
    EventFilthyBlade,
    EventHealingBalm,
    //Blacktooth Brute
    EventEarthShaker,
    //Cutwater Duelist
    EventDuelistDash,
    //Irontide Oarsman
    EventSeaSpout,
    //Bilge Rat Padfoot
    EventPlagueStep,
    //Cutwater Knife Juggler
    EventRicochetingThrow,
    //Vermin Trapper
    EventRatTraps,
    //Soggy Shiprat
    EventScabrousBite,
    //Blacktooth Knuckleduster
    EventShatteringBellow,
    //Blacktooth Scrapper
    EventBlindRage,
    //Cutwater Harponeer
    EventDraggingHarpoon,
    //Irontide Crusher
    EventBoulderThrow,
    EventGroundShatter,
    //Irontide Buccaneers
    EventBladeBarrage,
    //Irontide Stormcaller
    EventThunderingSquall,
    EventLightningBolt,
    //Irontide Ravager
    EventPainfulMotivation,
    //Irontide Officer
    EventOiledBlade,
};

struct FreeholdMobAI : public ScriptedAI
{
    FreeholdMobAI(Creature* creature) : ScriptedAI(creature) {}

    void Reset() override
    {
        events.Reset();
    }

    virtual void ExecuteEvent(uint32 eventId) {};

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        events.Update(diff);

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        while (uint32 eventId = events.ExecuteEvent())
        {
            ExecuteEvent(eventId);
            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;
        }

        DoMeleeAttackIfReady();
    }
};

///< Vermin Trapper - 130404
struct npc_vermin_trapper : public FreeholdMobAI
{
    npc_vermin_trapper(Creature* creature) : FreeholdMobAI(creature)
    {
        me->Mount(70619);
    }

    void JustEngagedWith(Unit* /*who*/) override
    {
        events.ScheduleEvent(FreeHoldTrashEvents::EventRatTraps, 1s);
    }

    void ExecuteEvent(uint32 eventId) override
    {
        if (eventId == FreeHoldTrashEvents::EventRatTraps)
        {
            DoCastVictim(FreeHoldTrashSpells::RatTrapsDummy);
            events.Repeat(12s);
        }
    }
};

///< Soggy Shiprat - 130024
struct npc_soggy_shiprat : public FreeholdMobAI
{
    npc_soggy_shiprat(Creature* creature) : FreeholdMobAI(creature) {}

    void JustEngagedWith(Unit* /*who*/) override
    {
        events.ScheduleEvent(FreeHoldTrashEvents::EventScabrousBite, 1s);
    }

    void ExecuteEvent(uint32 eventId) override
    {
        if (eventId == FreeHoldTrashEvents::EventScabrousBite)
        {
            DoCastVictim(FreeHoldTrashSpells::ScabrousBite);
            events.Repeat(7s);
        }
    }
};

///< Bilge Rat Padfoot - 129550
struct npc_bilge_rat_padfoot : public FreeholdMobAI
{
    npc_bilge_rat_padfoot(Creature* creature) : FreeholdMobAI(creature) {}

    void JustEngagedWith(Unit* /*who*/) override
    {
        events.ScheduleEvent(FreeHoldTrashEvents::EventPlagueStep, 1s);
    }

    void ExecuteEvent(uint32 eventId) override
    {
        if (eventId == FreeHoldTrashEvents::EventPlagueStep)
        {
            DoCastVictim(FreeHoldTrashSpells::PlagueStep);
            events.Repeat(10s);
        }
    }
};

///< Npc Bilge Rat Brinescale - 129600
struct npc_bilge_rat_brinescale : public FreeholdMobAI
{
    npc_bilge_rat_brinescale(Creature* creature) : FreeholdMobAI(creature) {}

    void JustEngagedWith(Unit* /*who*/) override
    {
        events.ScheduleEvent(WaterBolt, 1s);
        events.ScheduleEvent(FrostBlast, 5s);
    }

    void ExecuteEvent(uint32 eventId) override
    {
        switch (eventId)
        {
        case WaterBolt:
            DoCastVictim(WaterBolt);
            events.Repeat(3s);
            break;

        case FrostBlast:
            DoCastVictim(FrostBlast);
            events.Repeat(15s);
            break;

        default:
            break;
        }
    }
};

///< Npc Cutwater Duelist - 129559
struct npc_cutwater_duelist : public FreeholdMobAI
{
    npc_cutwater_duelist(Creature* creature) : FreeholdMobAI(creature) {}

    void JustEngagedWith(Unit* /*who*/) override
    {
        events.ScheduleEvent(FreeHoldTrashEvents::EventDuelistDash, 1s);
    }

    void ExecuteEvent(uint32 eventId) override
    {
        if (eventId == FreeHoldTrashEvents::EventDuelistDash)
        {
            DoCastVictim(FreeHoldTrashSpells::DuelistDash);
            events.Repeat(5s);
        }
    }
};

///< Npc Cutwater Knife Juggler - 129599
struct npc_cutwater_knife_juggler : public FreeholdMobAI
{
    npc_cutwater_knife_juggler(Creature* creature) : FreeholdMobAI(creature) {}

    void JustEngagedWith(Unit* /*who*/) override
    {
        events.ScheduleEvent(FreeHoldTrashEvents::EventRicochetingThrow, 1s);
    }

    void ExecuteEvent(uint32 eventId) override
    {
        if (eventId == FreeHoldTrashEvents::EventRicochetingThrow)
        {
            DoCastRandom(FreeHoldTrashSpells::RicochetingThrow, 75.0f);
            events.Repeat(7s);
        }
    }
};

///< Npc Cutwater Harpooner - 129601
struct npc_cutwater_harpooner : FreeholdMobAI
{
    npc_cutwater_harpooner(Creature* creature) : FreeholdMobAI(creature) {}

    void JustEngagedWith(Unit* /*who*/) override
    {
        events.ScheduleEvent(FreeHoldTrashEvents::EventDraggingHarpoon, 1s);
    }

    void ExecuteEvent(uint32 eventId) override
    {
        if (eventId == FreeHoldTrashEvents::EventDraggingHarpoon)
        {
            DoCastRandom(FreeHoldTrashSpells::DraggingHarpoon, 75.0f);
            events.Repeat(7s);
        }
    }
};

///< Npc Blacktooth Brute - 129548
struct npc_blacktooth_brute : public FreeholdMobAI
{
    npc_blacktooth_brute(Creature* creature) : FreeholdMobAI(creature) {}

    void JustEngagedWith(Unit* /*who*/) override
    {
        events.ScheduleEvent(FreeHoldTrashEvents::EventEarthShaker, 1s);
    }

    void ExecuteEvent(uint32 eventId) override
    {
        if (eventId == FreeHoldTrashEvents::EventEarthShaker)
        {
            DoCastVictim(FreeHoldTrashSpells::EarthShaker);
            events.Repeat(5s);
        }
    }
};

///< Npc Blacktooth Knuckleduster - 129547
struct npc_blacktooth_knuckleduster : public FreeholdMobAI
{
    npc_blacktooth_knuckleduster(Creature* creature) : FreeholdMobAI(creature) {}

    void JustEngagedWith(Unit* /*who*/) override
    {
        if (me->IsSummon() && instance)
            instance->ProcessEvent(me, ACTION_BLACKTOOTH_BRAWL_ENGAGE, me);

        events.ScheduleEvent(FreeHoldTrashEvents::EventShatteringBellow, 3s, 5s);
    }

    void ExecuteEvent(uint32 eventId) override
    {
        if (eventId == FreeHoldTrashEvents::EventShatteringBellow)
        {
            DoCastSelf(FreeHoldTrashSpells::ShatteringBellow);
            events.Repeat(8s, 10s);
        }
    }
};

///< Npc Blacktooth Scrapper - 129529
struct npc_blacktooth_scrapper : public FreeholdMobAI
{
    npc_blacktooth_scrapper(Creature* creature) : FreeholdMobAI(creature) {}

    void JustEngagedWith(Unit* /*who*/) override
    {
        events.ScheduleEvent(FreeHoldTrashEvents::EventBlindRage, 1s);
    }

    //void OnSuccessfulSpellCast(SpellInfo const* spell) override
    //{
    //    if (spell && spell->Id == FreeHoldTrashSpells::BlindRage)
    //    {
    //    }
    //}

    void ExecuteEvent(uint32 eventId) override
    {
        if (eventId == FreeHoldTrashEvents::EventBlindRage)
        {
            if (Unit* target = SelectTarget(SelectTargetMethod::Random, 0, NonTankTargetSelector(me)))
            {
                targetGUID = target->GetGUID();
                me->CastSpell(target, FreeHoldTrashSpells::BlindRage);
                if (Unit* target = ObjectAccessor::GetUnit(*me, targetGUID))
                    me->GetMotionMaster()->MoveChase(target);
                events.Repeat(15s);
            }
        }
    }

private:
    ObjectGuid targetGUID;
};

///< Npc Irontide Oarsman - 127111
struct npc_irontide_oarsman : public FreeholdMobAI
{
    npc_irontide_oarsman(Creature* creature) : FreeholdMobAI(creature) {}

    void JustEngagedWith(Unit* /*who*/) override
    {
        events.ScheduleEvent(FreeHoldTrashEvents::EventSeaSpout, 1s);
    }

    void ExecuteEvent(uint32 eventId) override
    {
        if (eventId == FreeHoldTrashEvents::EventSeaSpout)
        {
            DoCastVictim(FreeHoldTrashSpells::SeaSpoutDummy);
            events.Repeat(8s);
        }
    }
};

///< Npc Irontide Enforcer - 129602
struct npc_irontide_enforcer : public FreeholdMobAI
{
    npc_irontide_enforcer(Creature* creature) : FreeholdMobAI(creature) {}

    void JustEngagedWith(Unit* /*who*/) override
    {
        events.ScheduleEvent(FreeHoldTrashEvents::EventBrutalBackhand, 1s);

        if (IsHeroic() || IsMythic())
            events.ScheduleEvent(FreeHoldTrashEvents::EventShatteringToss, 5s);
    }

    void ExecuteEvent(uint32 eventId) override
    {
        switch (eventId)
        {
        case FreeHoldTrashEvents::EventBrutalBackhand:
            DoCastVictim(FreeHoldTrashSpells::BrutalBackhand);
            events.Repeat(5s);
            break;

        case FreeHoldTrashEvents::EventShatteringToss:
            DoCastVictim(FreeHoldTrashSpells::ShatteringToss);
            events.Repeat(8s);
            break;

        default:
            break;
        }
    }
};

///< Npc Irontide Mastiff - 128551
struct npc_irontide_mastiff : public FreeholdMobAI
{
    npc_irontide_mastiff(Creature* creature) : FreeholdMobAI(creature) {}

    void JustEngagedWith(Unit* /*who*/) override
    {
        events.ScheduleEvent(FreeHoldTrashEvents::EventBestialWrath, 1s);
        events.ScheduleEvent(FreeHoldTrashEvents::EventCripplingBite, 3s);
    }

    void ExecuteEvent(uint32 eventId) override
    {
        switch (eventId)
        {
        case FreeHoldTrashEvents::EventCripplingBite:
            DoCastVictim(FreeHoldTrashSpells::CripplingBite);
            events.Repeat(5s);
            break;

        case FreeHoldTrashEvents::EventBestialWrath:
            DoCastVictim(FreeHoldTrashSpells::BestialWrath);
            events.Repeat(15s);
            break;

        default:
            break;
        }
    }
};

///< Npc Irontide Corsair - 126928
struct npc_irontide_corsair : public FreeholdMobAI
{
    npc_irontide_corsair(Creature* creature) : FreeholdMobAI(creature) {}

    void JustEngagedWith(Unit* /*who*/) override
    {
        events.ScheduleEvent(FreeHoldTrashEvents::EventPoisoningStrike, 1000);
    }

    void ExecuteEvent(uint32 eventId) override
    {
        if (eventId == FreeHoldTrashEvents::EventPoisoningStrike)
        {
            DoCastVictim(FreeHoldTrashSpells::PoisoningStrike);
            events.Repeat(5s);
        }
    }
};

///< Npc Irontide Crackshot - 126918
struct npc_irontide_crackshot : public FreeholdMobAI
{
    npc_irontide_crackshot(Creature* creature) : FreeholdMobAI(creature) {}

    void JustEngagedWith(Unit* /*who*/) override
    {
        events.ScheduleEvent(FreeHoldTrashEvents::EventAzeriteGrenade, 1s);
        events.ScheduleEvent(FreeHoldTrashEvents::EventShoot, 5s);
    }

    void ExecuteEvent(uint32 eventId) override
    {
        switch (eventId)
        {
        case FreeHoldTrashEvents::EventAzeriteGrenade:
            DoCastVictim(FreeHoldTrashSpells::AzeriteGrenade);
            events.Repeat(5s);
            break;

        case FreeHoldTrashEvents::EventShoot:
            DoCastVictim(FreeHoldTrashSpells::Shoot);
            events.Repeat(8s);
            break;

        default:
            break;
        }
    }
};

///< Npc Irontide Bonesaw - 129788
struct npc_irontide_bonesaw : public FreeholdMobAI
{
    npc_irontide_bonesaw(Creature* creature) : FreeholdMobAI(creature) {}

    void JustEngagedWith(Unit* /*who*/) override
    {
        events.ScheduleEvent(FreeHoldTrashEvents::EventFilthyBlade, 1s);
        events.ScheduleEvent(FreeHoldTrashEvents::EventHealingBalm, 10s);
    }

    void ExecuteEvent(uint32 eventId) override
    {
        switch (eventId)
        {
        case FreeHoldTrashEvents::EventFilthyBlade:
            DoCastVictim(FreeHoldTrashSpells::FilthyBlade);
            events.Repeat(5s);
            break;

        case FreeHoldTrashEvents::EventHealingBalm:
        {
            if (Unit * target = DoSelectLowestHpFriendly(30.0f))
                me->CastSpell(target, FreeHoldTrashSpells::HealingBalm);
            events.Repeat(10s);
            break;
        }

        default:
            break;
        }
    }
};

///< Npc Irontide Crusher - 130400
struct npc_irontide_crusher : public FreeholdMobAI
{
    npc_irontide_crusher(Creature* creature) : FreeholdMobAI(creature) {}

    void JustEngagedWith(Unit* /*who*/) override
    {
        events.ScheduleEvent(FreeHoldTrashEvents::EventBoulderThrow, 1s);
        events.ScheduleEvent(FreeHoldTrashEvents::EventGroundShatter, 5s);
    }

    void ExecuteEvent(uint32 eventId) override
    {
        switch (eventId)
        {
        case FreeHoldTrashEvents::EventBoulderThrow:
            DoCastVictim(FreeHoldTrashSpells::BoulderThrow);
            events.Repeat(7s);
            break;

        case FreeHoldTrashEvents::EventGroundShatter:
            DoCastVictim(FreeHoldTrashSpells::GroundShatter);
            events.Repeat(12s);
            break;

        default:
            break;
        }
    }
};

///< Npc Irontide Officer - 127106
struct npc_irontide_officer : public FreeholdMobAI
{
    npc_irontide_officer(Creature* creature) : FreeholdMobAI(creature)
    {
        me->Mount(76855);
    }

    void JustEngagedWith(Unit* /*who*/) override
    {
        events.ScheduleEvent(FreeHoldTrashEvents::EventOiledBlade, 1s);
    }

    void ExecuteEvent(uint32 eventId) override
    {
        if (eventId == FreeHoldTrashEvents::EventOiledBlade)
        {
            DoCastVictim(FreeHoldTrashSpells::OiledBlade);
            events.Repeat(10s);
        }
    }
};

///< Npc Irontide Ravager - 130012
struct npc_irontide_ravager : public FreeholdMobAI
{
    npc_irontide_ravager(Creature* creature) : FreeholdMobAI(creature) {}

    void JustEngagedWith(Unit* /*who*/) override
    {
        events.ScheduleEvent(FreeHoldTrashEvents::EventPainfulMotivation, 5s);
    }

    void ExecuteEvent(uint32 eventId) override
    {
        if (eventId == FreeHoldTrashEvents::EventPainfulMotivation)
        {
            DoCastVictim(FreeHoldTrashSpells::PainfulMotivation);
            events.Repeat(15s);
        }
    }
};

///< Npc Irontide Stormcaller - 126919
struct npc_irontide_stormcaller : public FreeholdMobAI
{
    npc_irontide_stormcaller(Creature* creature) : FreeholdMobAI(creature) {}

    void JustEngagedWith(Unit* /*who*/) override
    {
        events.ScheduleEvent(FreeHoldTrashEvents::EventLightningBolt, 1s);
        events.ScheduleEvent(FreeHoldTrashEvents::EventThunderingSquall, 5s);
    }

    void ExecuteEvent(uint32 eventId) override
    {
        switch (eventId)
        {
        case FreeHoldTrashEvents::EventLightningBolt:
            DoCastVictim(FreeHoldTrashSpells::LightningBolt);
            events.Repeat(8s);
            break;

        case FreeHoldTrashEvents::EventThunderingSquall:
            DoCastVictim(FreeHoldTrashSpells::ThunderingSquall);
            events.Repeat(5s);
            break;

        default:
            break;
        }
    }
};

///< Npc Irontide Buccaneer - 130011
struct npc_irontide_buccaneer : public FreeholdMobAI
{
    npc_irontide_buccaneer(Creature* creature) : FreeholdMobAI(creature) {}

    void JustEngagedWith(Unit* /*who*/) override
    {
        events.ScheduleEvent(FreeHoldTrashEvents::EventBladeBarrage, 1s);
    }

    void ExecuteEvent(uint32 eventId) override
    {
        if (eventId == FreeHoldTrashEvents::EventBladeBarrage)
        {
            DoCastVictim(FreeHoldTrashSpells::BladeBarrage);
            events.Repeat(8s);
        }
    }
};

///< Spell Sea Spout - 258777
struct spell_sea_spout : public SpellScript
{
    PrepareSpellScript(spell_sea_spout);

    void HandleAfterCast()
    {
        if (Unit* caster = GetCaster())
        {
            if (Unit* target = ObjectAccessor::GetUnit(*caster, caster->GetTarget()))
                caster->CastSpell(target, FreeHoldTrashSpells::SeaSpout);
        }
    }

    void Register() override
    {
        AfterCast += SpellCastFn(spell_sea_spout::HandleAfterCast);
    }
};

///< Spell Draggin Harpoon - 272413
struct spell_draggin_harpoon : public SpellScript
{
    PrepareSpellScript(spell_draggin_harpoon);

    enum HarpoonSpells
    {
        HarpoonEffectMoveToTarget = 272416
    };

    void HandleOnHit()
    {
        if (Unit* caster = GetCaster())
            if (Unit* target = GetHitUnit())
                target->CastSpell(caster, HarpoonEffectMoveToTarget);
    }

    void Register() override
    {
        OnHit += SpellHitFn(spell_draggin_harpoon::HandleOnHit);
    }
};

///< Spell Shattering Toss - 274861
struct spell_shattering_toss : public SpellScript
{
    PrepareSpellScript(spell_shattering_toss);

    void HandleOnEffectHitTarget(SpellEffIndex /*effIndex*/)
    {
        if (Player* target = GetHitPlayer())
            if (Unit* caster = GetCaster())
                caster->CastSpell(target, FreeHoldTrashSpells::ShatteringTossLaunch, true);
    }

    void HandleTargets(std::list<WorldObject*> & targetsList)
    {
        if (Unit* caster = GetCaster())
        {
            targetsList.remove_if([caster](WorldObject * obj)->bool
            {
                return (!obj || !obj->IsPlayer() || obj->GetGUID() == caster->GetGUID());
            });
        }
        Trinity::Containers::RandomResize(targetsList, GetSpellInfo()->MaxAffectedTargets);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_shattering_toss::HandleOnEffectHitTarget, EFFECT_0, SPELL_EFFECT_DUMMY);
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_shattering_toss::HandleTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ALLY);
    }
};

///< Spell Shattering Toss - 274862
struct spell_shattering_toss_launch : public SpellScript
{
    PrepareSpellScript(spell_shattering_toss_launch);

    void HandleAfterCast()
    {
        if (Unit* caster = GetCaster())
            if (Creature* enforcer = caster->FindNearestCreature(NPC_IRONTIDE_ENFORCER, 75.0f))
                caster->CastSpell(caster, FreeHoldTrashSpells::ShatteringTossDmg, CastSpellExtraArgs(true).SetOriginalCaster(enforcer->GetGUID()));
    }

    void Register() override
    {
        AfterCast += SpellCastFn(spell_shattering_toss_launch::HandleAfterCast);
    }
};

///< spell Rat Traps - 274383
struct spell_rat_trap : public SpellScript
{
    PrepareSpellScript(spell_rat_trap);

    void HandleAfterCast()
    {
        if (Unit* caster = GetCaster())
        {
            std::list<Player*> list = caster->SelectNearestPlayers(40.0f, true);
            for (Player* player : list)
                caster->CastSpell(player, FreeHoldTrashSpells::RatTrapsMissile);
        }
    }

    void Register() override
    {
        AfterCast += SpellCastFn(spell_rat_trap::HandleAfterCast);
    }
};

///< Areatrigger Rat Trap - SpellID: 274386, AtID: 18327
struct at_rat_trap : AreaTriggerAI
{
    at_rat_trap(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger) {}

    void OnUnitEnter(Unit* unit) override
    {
        Unit* caster = at->GetCaster();
        if (!caster || !unit)
            return;

        if (caster->IsValidAttackTarget(unit))
            unit->CastSpell(unit, FreeHoldTrashSpells::RatTrapsDamage, CastSpellExtraArgs(true).SetOriginalCaster(caster->GetGUID()));
    }
};


void AddSC_free_hold()
{
    //Creatures
    RegisterCreatureAI(npc_irontide_buccaneer);
    RegisterCreatureAI(npc_irontide_stormcaller);
    RegisterCreatureAI(npc_irontide_ravager);
    RegisterCreatureAI(npc_irontide_enforcer);
    RegisterCreatureAI(npc_irontide_crackshot);
    RegisterCreatureAI(npc_irontide_corsair);
    RegisterCreatureAI(npc_irontide_mastiff);
    RegisterCreatureAI(npc_irontide_officer);
    RegisterCreatureAI(npc_irontide_oarsman);
    RegisterCreatureAI(npc_irontide_crusher);
    RegisterCreatureAI(npc_irontide_bonesaw);
    RegisterCreatureAI(npc_cutwater_duelist);
    RegisterCreatureAI(npc_cutwater_harpooner);
    RegisterCreatureAI(npc_cutwater_knife_juggler);
    RegisterCreatureAI(npc_blacktooth_knuckleduster);
    RegisterCreatureAI(npc_blacktooth_brute);
    RegisterCreatureAI(npc_blacktooth_scrapper);
    RegisterCreatureAI(npc_bilge_rat_padfoot);
    RegisterCreatureAI(npc_bilge_rat_brinescale);
    RegisterCreatureAI(npc_vermin_trapper);
    RegisterCreatureAI(npc_soggy_shiprat);

    //Areatriggers
    RegisterAreaTriggerAI(at_rat_trap);

    //Spells
    RegisterSpellScript(spell_shattering_toss);
    //RegisterSpellScript(spell_shattering_toss_launch);
    RegisterSpellScript(spell_sea_spout);
    RegisterSpellScript(spell_rat_trap);
    RegisterSpellScript(spell_draggin_harpoon);
}
