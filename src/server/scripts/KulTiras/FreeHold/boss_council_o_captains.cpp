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

enum CouncilCaptainSpells
{
    SPELL_UNDER_ONE_BANNER          = 257821, // Cast if you fight with the 3 boss
    SPELL_BILGE_RAT_BREW            = 267351, // Cast to player in the event of Captain Eudora
    SPELL_FREEHOLD_KEYRING          = 258333, // Cast to murphy to recover the key in the event of Jolly
    SPELL_OPENING_FREEHOLD_JAIL     = 258334, // Idk if this is really the spell
    SPELL_PLAYING_HARD_TO_GET       = 258301,
    SPELL_SLEEPING                  = 258336,

    //Captain Raoul Fight
    SPELL_BLACKOUT_BARREL           = 258338,
    SPELL_BLACKOUT_BARREL_VEH_AURA  = 258875,
    SPELL_BLACKOUT_BARREL_CLEAR_AURA= 258878,
    SPELL_BARREL_SMASH              = 256589,

    //Captain Eudora Fight
    SPELL_POWDER_SHOT_TARGET_SELECT = 274830,
    SPELL_GRAPESHOT                 = 258381,
    SPELL_GRAPESHOT_FIRE            = 258352,

    //Captain Jolly Fight
    SPELL_CUTTING_SURGE_CAST        = 267522,
    SPELL_CUTTING_SURGE             = 267523,
    SPELL_WHIRLPOOL_OF_BLADES_TS    = 267531,
    SPELL_WHIRLPOOL_OF_BLADES       = 272397,
    SPELL_WHIRLPOOL_OF_BLADES_AT    = 272377,

    //Allied Captain Buff
    SPELL_TRADE_WINDS_VIGOR         = 281329, /// Casted by Captain Jolly if he is Allied
    SPELL_CHAIN_SHOT                = 272902, /// Casted by Captain Eudora if she is Allied
    SPELL_TAPPED_KEG                = 272884, /// Casted by Captain Raoul if he is Allied
    SPELL_TAPPED_KEG_BUFF           = 272900, 

    //Heroic & Mythic Only

    /*On Heroic and Mythic difficulty, the nearby bartender Rummy Mancomb will throw
    beverages to the location of a randomly selected boss. These beverages will 
    apply a buff to any boss or player that stands within them.*/

    SPELL_CONFIDENCE_BOOSTING_FREEHOLD_BREW     = 265086,
    SPELL_CONFIDENCE_BOOSTING_FREEHOLD_BREW_TS  = 265088,
    SPELL_INVIGORATING_FREEHOLD_BREW            = 264715,
    SPELL_INVIGORATING_FREEHOLD_BREW_TS         = 264608,
    SPELL_CAUSTIC_FREEHOLD_BREW                 = 265171,
    SPELL_CAUSTIC_FREEHOLD_BREW_TS              = 265168,
};

enum CouncilCaptainEvents
{
    //Raoul Enemy Events
    EVENT_BLACKOUT_BARREL = 1,
    EVENT_BARREL_SMASH,

    //Eudora Enemy Events
    EVENT_POWDER_SHOT,
    EVENT_GRAPESHOT,
    EVENT_GRAPESHOT_JUMP,
    EVENT_GRAPESHOT_FIRE,

    //Jolly Enemy Events
    EVENT_CUTTING_SURGE,
    EVENT_WHIRLPOOL_OF_BLADES,

    //Allied Buff
    EVENT_ALLIED_BUFF,

    //Blacktooth Knuckleduster
    EVENT_SHATTERING_BELLOW
};

enum CouncilOCaptainsData
{
    DATA_HAS_DIED,
    DATA_IN_COMBAT,
};

enum CouncilCaptainMovementPoint
{
    MOVEMENT_POINT_MURPHY_LAST_POSITION = 3,
    MOVEMENT_POINT_JUMP,
};

enum CouncilOCaptainsTexts
{
    TALK_INTRO = 0,         // Let's put your steel to the test!
                            // Bottoms up, scallywags!
                            // Your skulls will be excellent target practice.

    TALK_ABILITY,           // Surging steel!
                            // En guard!

    TALK_KILL,              // A fine coupe de grace.
                            // Right between the eyes.

    TALK_JUST_DIED,         // Bury me with my blade...
                            // Was this... last call...?
                            // Nice... shot...
                            // Awww, I still had bullets in the chamber.

    TALK_WIPE               // Will I ever meet an opponent who can match my skill?
};

///< Npc Bilge Rat Grok Jerk - 135978
struct npc_bilge_rat_grok_jerk : public ScriptedAI
{
    npc_bilge_rat_grok_jerk(Creature* creature) : ScriptedAI(creature) {}

    void SpellHitTarget(WorldObject* target, SpellInfo const* spell) override
    {
        if (target && spell && spell->Id == FreeholdSpells::SPELL_BILGE_RAT_REGALIA && target->IsUnit())
            target->ToUnit()->RemoveAurasDueToSpell(CouncilCaptainSpells::SPELL_BILGE_RAT_BREW);
    }

    void OnSuccessfulSpellCast(SpellInfo const* spell) override
    {
        if (!instance)
            return;

        if (spell && spell->Id == FreeholdSpells::SPELL_BILGE_RAT_REGALIA)
            instance->SetData(DATA_COUNCIL_O_CAPTAIN_PRE_EVENT, 1);

        if (Creature* eudora = instance->GetCreature(NPC_CAPTAIN_EUDORA))
            eudora->SetFaction(FACTION_FRIENDLY);

        if (Creature* jolly = instance->GetCreature(NPC_CAPTAIN_JOLLY))
            jolly->SetFaction(FACTION_MONSTER_2);

        if (Creature* raoul = instance->GetCreature(NPC_CAPTAIN_RAOUL))
            raoul->SetFaction(FACTION_MONSTER_2);
    }

    void OnSpellClick(Unit* clicker, bool /*result*/) override
    {
        Map::PlayerList const& PlayerList = me->GetMap()->GetPlayers();
        if (!PlayerList.isEmpty())
        {
            for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
                if (Player* player = i->GetSource())
                    if (!player->HasAura(CouncilCaptainSpells::SPELL_BILGE_RAT_BREW))
                        return;
        }

        me->AddDelayedEvent(1000, [this]()
        {
            DoCastSelf(FreeholdSpells::SPELL_BILGE_RAT_REGALIA, true);
        });
    }
};

///< Npc Murphy - 130467
struct npc_freehold_murphy : public ScriptedAI
{
    npc_freehold_murphy(Creature* creature) : ScriptedAI(creature)
    {
        catched = false;
        position = 0;
    }

    void Reset() override
    {
        me->AddAura(CouncilCaptainSpells::SPELL_FREEHOLD_KEYRING);
        me->RemoveUnitFlag(UNIT_FLAG_UNINTERACTIBLE);
        me->SetNpcFlag(UNIT_NPC_FLAG_SPELLCLICK);
        me->SetSpeed(MOVE_RUN, 20.0f);
    }

    void MovementInform(uint32 type, uint32 pointId) override
    {
        if (type != POINT_MOTION_TYPE)
            return;

        me->SetNpcFlag(UNIT_NPC_FLAG_SPELLCLICK);

        if (position == MOVEMENT_POINT_MURPHY_LAST_POSITION)
        {
            me->SetStandState(UNIT_STAND_STATE_DEAD);
            me->CastSpell(me, SPELL_SLEEPING, true);
        }
    }

    void OnSpellClick(Unit* clicker, bool /*result*/) override
    {
        if (!clicker || catched)
            return;

        me->RemoveNpcFlag(UNIT_NPC_FLAG_SPELLCLICK);

        if (position == MOVEMENT_POINT_MURPHY_LAST_POSITION)
        {
            catched = true;
            clicker->CastSpell(clicker, CouncilCaptainSpells::SPELL_FREEHOLD_KEYRING);
            return;
        }

        me->GetMotionMaster()->MovePoint(position, MurphyRunningPositions[position]);
        position++;
    }

private:
    bool catched;
    uint8 position;
};

///< Npc Otis - 129441
struct npc_freehold_otis : public ScriptedAI
{
    npc_freehold_otis(Creature* creature) : ScriptedAI(creature)
    {
        firstmeet = true;
    }

    void OnSuccessfulSpellCast(SpellInfo const* spell) override
    {
        if (!instance)
            return;

        if (spell && spell->Id == FreeholdSpells::SPELL_CUTWATER_REGALIA)
            instance->SetData(DATA_COUNCIL_O_CAPTAIN_PRE_EVENT, 1);

        if (Creature* eudora = instance->GetCreature(NPC_CAPTAIN_EUDORA))
            eudora->SetFaction(FACTION_MONSTER_2);

        if (Creature* jolly = instance->GetCreature(NPC_CAPTAIN_JOLLY))
            jolly->SetFaction(FACTION_FRIENDLY);

        if (Creature* raoul = instance->GetCreature(NPC_CAPTAIN_RAOUL))
            raoul->SetFaction(FACTION_MONSTER_2);
    }

    void MoveInLineOfSight(Unit* unit) override
    {
        if (Player* player = unit->ToPlayer())
        {
            auto instance = me->GetInstanceScript();
            if (firstmeet && instance)
            {
                firstmeet = false;
                instance->DoPlayConversation(CONVERSATION_OTIS_INTRO);
            }
        }
    }

private:
    bool firstmeet;
};

///< Npc Freehold Jail - 130536
struct npc_freehold_jail : public ScriptedAI
{
    npc_freehold_jail(Creature* creature) : ScriptedAI(creature)
    {
        me->AddWorldEffect(8326);
        me->SetNpcFlag(UNIT_NPC_FLAG_SPELLCLICK);
    }

    void OnSpellClick(Unit* clicker, bool /*result*/) override
    {
        if (!clicker || !clicker->HasAura(SPELL_FREEHOLD_KEYRING))
            return;

        clicker->CastSpell(me, CouncilCaptainSpells::SPELL_OPENING_FREEHOLD_JAIL);
    }
};

///< Council o Captains
struct CouncilOCaptainsBaseAI : public BossAI
{
    CouncilOCaptainsBaseAI(Creature* creature) : BossAI(creature, FreeholdData::DATA_COUNCIL_O_CAPTAINS)
    {
        ApplyAllImmunities(true);
    }

    void Clean()
    {
        hasDied = false;
        hasEvade = false;
        inCombat = false;
    }

    void Initialize()
    {
        me->SetReactState(REACT_DEFENSIVE);
        me->RemoveAurasDueToSpell(CouncilCaptainSpells::SPELL_UNDER_ONE_BANNER);
    }

    void Reset() override
    {
        _Reset();
        Clean();
        Initialize();
    }

    void SetData(uint32 id, uint32 data) override
    {
        if (id == DATA_IN_COMBAT)
        {
            if (me->GetFaction() == FACTION_FRIENDLY)
                hasDied = true;

            inCombat = true;
            if (instance && !instance->GetData(DATA_COUNCIL_O_CAPTAIN_PRE_EVENT))
                DoCastSelf(CouncilCaptainSpells::SPELL_UNDER_ONE_BANNER, true);
        }
    }

    uint32 GetData(uint32 id) const override
    {
        if (id == DATA_HAS_DIED && hasDied)
            return 1;
        return 0;
    }

    void SetInCombatWithOtherCaptains(Creature* friendlyBoss)
    {
        std::list<Creature*> captains;

        if (Creature* raoul = instance->GetCreature(NPC_CAPTAIN_RAOUL))
            captains.push_back(raoul);

        if (Creature* jolly = instance->GetCreature(NPC_CAPTAIN_JOLLY))
            captains.push_back(jolly);

        if (Creature* eudora = instance->GetCreature(NPC_CAPTAIN_EUDORA))
            captains.push_back(eudora);

        for (Creature* captain : captains)
        {
            if (captain->GetEntry() == friendlyBoss->GetEntry())
                continue;

            friendlyBoss->SetInCombatWith(captain);
            captain->SetInCombatWith(friendlyBoss);
            friendlyBoss->GetThreatManager().AddThreat(captain, 0.0f);
        }
    }

    void JustEngagedWith(Unit* who) override
    {
        _JustEngagedWith(who);

        if (inCombat || !instance)
            return;

        instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me, 1);

        for (uint32 entry : CouncilOCaptains)
        {
            if (Creature* captain = instance->GetCreature(entry))
            {
                captain->AI()->SetData(DATA_IN_COMBAT, 1);
                captain->SetReactState(REACT_AGGRESSIVE);

                if (captain->GetFaction() != FACTION_FRIENDLY)
                {
                    captain->SetFaction(FACTION_MONSTER_2);
                    captain->AI()->DoZoneInCombat();
                }
                else
                {
                    SetInCombatWithOtherCaptains(captain);
                }
            }
        }
        instance->DoPlayConversation(CONVERSATION_COUNCIL_O_CAPTAINS_INTRO);
    }

    bool CouncilOCaptainsDefeated()
    {
        if (!instance)
            return false;

        for (uint32 entry : CouncilOCaptains)
        {
            if (entry == me->GetEntry())
                continue;

            if (Creature* captain = instance->GetCreature(entry))
                if (!captain->AI()->GetData(DATA_HAS_DIED))
                    return false;
        }

        instance->SetBossState(DATA_COUNCIL_O_CAPTAINS, DONE);
        return true;
    }

    void DamageTaken(Unit* attacker, uint32& damage, DamageEffectType /*damageType*/, SpellInfo const* /*spellInfo = nullptr*/) override
    {
        if (hasDied)
        {
            damage = 0;
            return;
        }

        if (damage >= me->GetHealth())
        {
            if (CouncilOCaptainsDefeated())
            {
                for (uint32 entry : CouncilOCaptains)
                {
                    if (Creature* captain = instance->GetCreature(entry))
                    {
                        if (captain->GetFaction() == FACTION_FRIENDLY)
                        {
                            if (captain->GetEntry() == NPC_CAPTAIN_EUDORA)
                                instance->UpdateEncounterStateForKilledCreature(NPC_CAPTAIN_EUDORA, captain);

                            captain->GetMotionMaster()->MoveTargetedHome();
                            captain->DespawnOrUnsummon(10s);
                            captain->CombatStop();
                            instance->DoCombatStopOnPlayers();
                        }
                        else if (entry != me->GetEntry())
                        {
                            captain->RemoveUnitFlag(UnitFlags(UNIT_FLAG_UNINTERACTIBLE | UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC));
                            captain->RemoveUnitFlag2(UNIT_FLAG2_FEIGN_DEATH);
                            captain->RemoveUnitFlag3(UNIT_FLAG3_FAKE_DEAD);
                            attacker->Kill(attacker, captain);
                        }
                        instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, captain);
                    }
                }
            }
            else
            {
                hasDied = true;
                Talk(TALK_JUST_DIED);
                damage = me->GetHealth() - 1;
                events.Reset();
                me->CastStop();
                me->AttackStop();
                me->SetReactState(REACT_PASSIVE);
                me->SetUnitFlag(UnitFlags(UNIT_FLAG_UNINTERACTIBLE | UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC));
                me->SetUnitFlag2(UNIT_FLAG2_FEIGN_DEATH);
                me->SetUnitFlag3(UNIT_FLAG3_FAKE_DEAD);
            }
        }
    }

    bool UpdateVictim()
    {
        if (!instance || instance->GetBossState(DATA_COUNCIL_O_CAPTAINS) == DONE)
            return false;

        if (me->GetFaction() != FACTION_FRIENDLY)
            return BossAI::UpdateVictim();

        if (!me->IsInCombat())
            return false;

       // if (instance->IsWipe())
       // {
       //     EnterEvadeMode(EVADE_REASON_NO_HOSTILES);
       //     return true;
       // }

        bool hasTarget = false;

        for (uint32 entry : CouncilOCaptains)
        {
            if (entry == me->GetEntry())
                continue;

            if (Creature* captain = instance->GetCreature(entry))
            {
                if (!captain->AI()->GetData(DATA_HAS_DIED))
                {
                    AttackStart(captain);
                    hasTarget = true;
                    break;
                }
            }
        }

        if (!hasTarget)
            EnterEvadeMode(EVADE_REASON_NO_HOSTILES);
        
        return hasTarget;
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
            ExecuteEvent(eventId);
            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;
        }

        DoMeleeAttackIfReady();
    }

    void EnterEvadeMode(EvadeReason /*why*/) override
    {
        if (hasEvade)
            return;

        hasEvade = true;

        if (me->GetEntry() == NPC_CAPTAIN_JOLLY && !hasDied)
            Talk(TALK_WIPE);

        _EnterEvadeMode();
        if (instance)
        {
            for (uint32 itr : CouncilOCaptains)
            {
                if (itr == me->GetEntry())
                    continue;

                if (Creature* council = instance->GetCreature(itr))
                    council->AI()->EnterEvadeMode();
            }
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            instance->SetBossState(DATA_COUNCIL_O_CAPTAINS, FAIL);
        }
        _DespawnAtEvade();
    }

    void JustDied(Unit* killer) override
    {
        if (!hasDied)
            Talk(TALK_JUST_DIED);

        events.Reset();
        summons.DespawnAll();
        me->GetScheduler().CancelAll();
        me->RemoveAllAreaTriggers();

        if (me->GetEntry() == NPC_CAPTAIN_EUDORA && instance)
            instance->UpdateEncounterStateForKilledCreature(NPC_CAPTAIN_EUDORA, me);
    }

private:
    bool hasDied;
    bool hasEvade;
    bool inCombat;
};

///< Npc Captain Jolly - 126845
struct npc_council_o_captains_jolly : public CouncilOCaptainsBaseAI
{
    npc_council_o_captains_jolly(Creature* creature) : CouncilOCaptainsBaseAI(creature) {}

    void SpellHitTarget(WorldObject* target, SpellInfo const* spell) override
    {
        if (spell && spell->Id == CouncilCaptainSpells::SPELL_WHIRLPOOL_OF_BLADES_TS)
            DoCast(target->ToUnit(), spell->GetEffect(EFFECT_0).BasePoints);
    }

    void ScheduleTasks() override
    {
        if (me->GetFaction() == FACTION_FRIENDLY)
            events.ScheduleEvent(CouncilCaptainEvents::EVENT_ALLIED_BUFF, 8s);
        else
        {
            events.ScheduleEvent(CouncilCaptainEvents::EVENT_CUTTING_SURGE, 5s);
            events.ScheduleEvent(CouncilCaptainEvents::EVENT_WHIRLPOOL_OF_BLADES, 8s);
        }
    }

    void ExecuteEvent(uint32 eventId) override
    {
        switch (eventId)
        {
        case CouncilCaptainEvents::EVENT_CUTTING_SURGE:
            if (Unit* target = SelectTarget(SelectTargetMethod::Random, 0, 50.0f, true))
                me->CastSpell(target, CouncilCaptainSpells::SPELL_CUTTING_SURGE_CAST);
            events.Repeat(22s);
            break;

        case CouncilCaptainEvents::EVENT_WHIRLPOOL_OF_BLADES:
            DoCastSelf(CouncilCaptainSpells::SPELL_WHIRLPOOL_OF_BLADES_TS, true);
            events.Repeat(22s);
            break;

        case CouncilCaptainEvents::EVENT_ALLIED_BUFF:
            DoCastSelf(CouncilCaptainSpells::SPELL_TRADE_WINDS_VIGOR);
            events.Repeat(15s);
            break;

        default:
            break;
        }
    }
};

///< Npc Captain Eudora - 126848
struct npc_council_o_captains_eudora : public CouncilOCaptainsBaseAI
{
    npc_council_o_captains_eudora(Creature* creature) : CouncilOCaptainsBaseAI(creature) {}

    Position GetRandomPositionAround()
    {
        double angle = rand_norm() * 2.0 * M_PI;
        float dist = frand(15, 20);
        float x = CouncilOCaptainsMiddle.GetPositionX() + (float) (dist * std::sin(angle));
        float y = CouncilOCaptainsMiddle.GetPositionY() + (float) (dist * std::cos(angle));
        float z = CouncilOCaptainsMiddle.GetPositionZ();
        me->UpdateAllowedPositionZ(x, y, z);
        return { x, y, z };
    }

    float GetAngle() const
    {
        float dx = CouncilOCaptainsMiddle.GetPositionX() - me->GetPositionX();
        float dy = CouncilOCaptainsMiddle.GetPositionY() - me->GetPositionY();
        float ang = std::atan2(dy, dx);
        ang = (ang >= 0) ? ang : 2 * float(M_PI) + ang;
        return ang;
    }

    void ScheduleTasks() override
    {
        if (me->GetFaction() == FACTION_FRIENDLY)
            events.ScheduleEvent(CouncilCaptainEvents::EVENT_ALLIED_BUFF, 8s);
        else
        {
            events.ScheduleEvent(CouncilCaptainEvents::EVENT_POWDER_SHOT, 3s, 5s);
            events.ScheduleEvent(CouncilCaptainEvents::EVENT_GRAPESHOT_JUMP, 8s);
        }
    }

    void MovementInform(uint32 type, uint32 pointId) override
    {
        if (type != EFFECT_MOTION_TYPE)
            return;

        if (pointId == CouncilCaptainMovementPoint::MOVEMENT_POINT_JUMP)
        {
            _orientation = GetAngle() + float(M_PI / 4);
            me->SetOrientation(_orientation);
            me->SetFacingTo(_orientation);
            events.ScheduleEvent(CouncilCaptainEvents::EVENT_GRAPESHOT_FIRE, 1s);
        }
    }

    void ExecuteEvent(uint32 eventId) override
    {
        switch (eventId)
        {
        case CouncilCaptainEvents::EVENT_POWDER_SHOT:
            DoCastSelf(CouncilCaptainSpells::SPELL_POWDER_SHOT_TARGET_SELECT);
            events.Repeat(5s);
            break;

        case CouncilCaptainEvents::EVENT_GRAPESHOT_JUMP:
        {
            me->StopMoving();
            me->AttackStop();
            me->CastStop();
            me->SetReactState(REACT_PASSIVE);
            events.CancelEvent(CouncilCaptainEvents::EVENT_POWDER_SHOT);
            events.ScheduleEvent(CouncilCaptainEvents::EVENT_GRAPESHOT_JUMP, 15s);

            Position jumpDest = GetRandomPositionAround();
            me->GetMotionMaster()->MoveJump(jumpDest, me->GetExactDist(jumpDest), 10.0f, MOVEMENT_POINT_JUMP);
            break;
        }

        case CouncilCaptainEvents::EVENT_GRAPESHOT_FIRE:
        {
            if (grapershotcount < 6)
            {
                grapershotcount++;

                // This ability will always fire from Eudora's left to her right (Wowhead)
                me->SetFacingTo(_orientation);
                me->CastSpell(me, CouncilCaptainSpells::SPELL_GRAPESHOT_FIRE, true);
                _orientation -= float(M_PI / 12);
                events.Repeat(1s);
            }
            else
            {
                me->SetReactState(REACT_AGGRESSIVE);
                AttackStart(me->GetVictim());
                grapershotcount = 0;
                events.ScheduleEvent(CouncilCaptainEvents::EVENT_POWDER_SHOT, 1s);
            }
            break;
        }

        case CouncilCaptainEvents::EVENT_ALLIED_BUFF:
            DoCastVictim(CouncilCaptainSpells::SPELL_CHAIN_SHOT);
            events.Repeat(15s);
            break;

        default:
            break;
        }
    }

private:
    uint8 grapershotcount;
    float _orientation;
};

///< Npc Captain Raoul - 126847
struct npc_council_o_captains_raoul : public CouncilOCaptainsBaseAI
{
    npc_council_o_captains_raoul(Creature* creature) : CouncilOCaptainsBaseAI(creature) {}

    void JustSummoned(Creature* summon) override
    {
        if (summon && summon->GetEntry() == NPC_BLACKOUT_BARREL)
            summon->AI()->SetGUID(barreltargetGUID);
    }

    void ScheduleTasks() override
    {
        if (me->GetFaction() == FACTION_FRIENDLY)
            events.ScheduleEvent(CouncilCaptainEvents::EVENT_ALLIED_BUFF, 8s);
        else
        {
            events.ScheduleEvent(CouncilCaptainEvents::EVENT_BARREL_SMASH, 8s);
            events.ScheduleEvent(CouncilCaptainEvents::EVENT_BLACKOUT_BARREL, 22s);
        }
    }

    void ExecuteEvent(uint32 eventId) override
    {
        switch (eventId)
        {
        case CouncilCaptainEvents::EVENT_BLACKOUT_BARREL:
            if (Unit* target = SelectTarget(SelectTargetMethod::Random, 0, NonTankTargetSelector(me, true)))
            {
                barreltargetGUID = target->GetGUID();
                me->CastSpell(target, CouncilCaptainSpells::SPELL_BLACKOUT_BARREL, false);
            }
            events.Repeat(47s);
            break;

        case CouncilCaptainEvents::EVENT_BARREL_SMASH:
            DoCastSelf(CouncilCaptainSpells::SPELL_BARREL_SMASH, false);
            events.Repeat(22s);
            break;

        case CouncilCaptainEvents::EVENT_ALLIED_BUFF:
            DoCastSelf(CouncilCaptainSpells::SPELL_TAPPED_KEG);
            events.Repeat(15s);
            break;

        default:
            break;
        }
    }

private:
    ObjectGuid barreltargetGUID;
};

///< Npc Rummy Mancomb - 133219
struct npc_rummy_mancomb : public ScriptedAI
{
    npc_rummy_mancomb(Creature* creature) : ScriptedAI(creature) {}

    void Reset()
    {
        me->DisableEvadeMode();
        me->SetReactState(REACT_PASSIVE);
        me->SetUnitFlag(UnitFlags(UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC));
    }
};

///< Npc Blackout Barrel - 130896
struct npc_blackout_barrel : public ScriptedAI
{
    npc_blackout_barrel(Creature* creature) : ScriptedAI(creature) {}

    void IsSummonedBy(WorldObject* /*summoner*/) override
    {
        me->SetReactState(REACT_PASSIVE);
    }

    void SetGUID(ObjectGuid const& targetGUID, int32 id) override
    {
        if (Player* target = ObjectAccessor::GetPlayer(*me, targetGUID))
        {
            me->AddAura(CouncilCaptainSpells::SPELL_BLACKOUT_BARREL_VEH_AURA, target);
            me->EnterVehicle(target);
        }
    }

    void DamageTaken(Unit* attacker, uint32& damage, DamageEffectType /*damageType*/, SpellInfo const* /*spellInfo = nullptr*/) override
    {
        if (damage >= me->GetHealth())
            DoCastSelf(SPELL_BLACKOUT_BARREL_CLEAR_AURA, true);
    }

    void OnVehicleExited(Unit* vehicle) override
    {
        me->DespawnOrUnsummon();
    }
};

///< Npc Whirlpool of Blades - 138463
struct npc_whirlpool_of_blades : public ScriptedAI
{
    npc_whirlpool_of_blades(Creature* creature) : ScriptedAI(creature) {}

    void IsSummonedBy(WorldObject* summoner) override
    {
        me->SetUnitFlag(UnitFlags(UNIT_FLAG_UNINTERACTIBLE | UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_IMMUNE_TO_PC));
        me->DisableEvadeMode();
        me->SetReactState(REACT_PASSIVE);

        if (auto u = summoner->ToCreature())
            if (u->AI())
                if (Unit* target = u->AI()->SelectTarget(SelectTargetMethod::Random, 0, 0, true))
                    me->GetMotionMaster()->MoveFollow(target, 0, 0);
    }
};

const std::vector<uint32> FreeholdBrews =
{
    SPELL_CONFIDENCE_BOOSTING_FREEHOLD_BREW_TS,
    SPELL_INVIGORATING_FREEHOLD_BREW_TS,
    SPELL_CAUSTIC_FREEHOLD_BREW_TS
};

///< Spell Tending Bar - 264605
struct spell_tending_bar : public AuraScript
{
    PrepareAuraScript(spell_tending_bar);

    void HandleOnPeriodic(AuraEffect const* /*aurEff*/)
    {
        uint32 spell = Trinity::Containers::SelectRandomContainerElement(FreeholdBrews);

        if (Unit* caster = GetCaster())
           caster->CastSpell(caster, spell);
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_tending_bar::HandleOnPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

///< Spell Freehold Brew - 265088 / 264608 / 265168
struct spell_freehold_brew : public SpellScript
{
    PrepareSpellScript(spell_freehold_brew);

    void HandleOnEffectHitTarget(SpellEffIndex effIndex)
    {
        if (Unit* caster = GetCaster())
            if (Unit* target = GetHitUnit())
            {
                switch (GetSpellInfo()->Id)
                {
                case SPELL_CONFIDENCE_BOOSTING_FREEHOLD_BREW_TS:
                    caster->CastSpell(target, SPELL_CONFIDENCE_BOOSTING_FREEHOLD_BREW, true);
                    break;
                case SPELL_INVIGORATING_FREEHOLD_BREW_TS:
                    caster->CastSpell(target, SPELL_INVIGORATING_FREEHOLD_BREW, true);
                    break;
                case SPELL_CAUSTIC_FREEHOLD_BREW_TS:
                    caster->CastSpell(target, SPELL_CAUSTIC_FREEHOLD_BREW, true);
                    break;                   
                }
            }
    }

    void HandleTargets(std::list<WorldObject*>& targetsList)
    {
        targetsList.clear();

        uint32 target = Trinity::Containers::SelectRandomContainerElement(CouncilOCaptains);
        if (Unit* caster = GetCaster())
            if (caster->GetInstanceScript())
                targetsList.push_back(caster->GetInstanceScript()->GetCreature(target));
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_freehold_brew::HandleOnEffectHitTarget, EFFECT_0, SPELL_EFFECT_DUMMY);
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_freehold_brew::HandleTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ENTRY);
    }
};

///< Spell Powder Shot - 274830
struct spell_powder_shot_target_select : public SpellScript
{
    PrepareSpellScript(spell_powder_shot_target_select);

    void HandleOnEffectHitTarget(SpellEffIndex effIndex)
    {
        if (Unit* caster = GetCaster())
            if (Unit* target = GetHitUnit())
                caster->CastSpell(target, GetSpellInfo()->GetEffect(effIndex).BasePoints, true);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_powder_shot_target_select::HandleOnEffectHitTarget, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};


///< Spell Freehold Keyring - 258333
struct spell_freehold_keyring : public SpellScript
{
    PrepareSpellScript(spell_freehold_keyring);

    void HandleAfterCast()
    {
        if (Unit* caster = GetCaster())
            if (Creature* murphy = caster->FindNearestCreature(NPC_MURPHY, 10.0f))
            {
                murphy->SetUnitFlag(UNIT_FLAG_UNINTERACTIBLE);
                murphy->RemoveAurasDueToSpell(CouncilCaptainSpells::SPELL_FREEHOLD_KEYRING);
            }
    }

    void Register() override
    {
        AfterCast += SpellCastFn(spell_freehold_keyring::HandleAfterCast);
    }
};

///< Spell Opening - 258334
struct spell_freehold_jail_opening : public SpellScript
{
    PrepareSpellScript(spell_freehold_jail_opening);

    void HandleAfterCast()
    {
        if (Unit* caster = GetCaster())
        {
            if (Creature* jail = caster->FindNearestCreature(NPC_FREEHOLD_JAIL, 10.0f))
            {
                jail->PlayOneShotAnimKitId(2560);
                jail->DespawnOrUnsummon(3s);
            }

            if (Creature* otis = caster->FindNearestCreature(NPC_OTIS, 10.0f))
            {
                otis->CastSpell(otis, FreeholdSpells::SPELL_CUTWATER_REGALIA, true);

                if (InstanceScript* instance = caster->GetInstanceScript())
                    instance->DoPlayConversation(CONVERSATION_OTIS_OUTRO);

                otis->SetWalk(false);
                otis->GetMotionMaster()->MovePoint(0, -1877.7715f, -745.1250f, 56.47368f);
                
                otis->GetScheduler().Schedule(Seconds(1), [this](TaskContext context)
                {
                    if (Creature* otis = GetContextCreature())
                        otis->HandleEmoteCommand(EMOTE_ONESHOT_CHEER);
                })
                .Schedule(Seconds(14), [this](TaskContext context)
                {
                    if (Creature* otis = GetContextCreature())
                    {
                        Movement::MoveSplineInit init(otis);
                        for (auto itr : OtisWayPoints)
                            init.Path().push_back(itr);
                        init.SetSmooth();
                        init.Launch();
                    }
                }) 
                .Schedule(Seconds(25), [this](TaskContext context)
                {
                    if (Creature* otis = GetContextCreature())
                    {
                        otis->HandleEmoteCommand(EMOTE_ONESHOT_LAUGH_NO_SOUND);
                        otis->DespawnOrUnsummon(3s);
                    }
                });
            }
        }
    }

    void Register() override
    {
        AfterCast += SpellCastFn(spell_freehold_jail_opening::HandleAfterCast);
    }
};

///< Areatrigger Tapped Keg - SpellID: 272884, AtID: 13674
struct at_tapped_keg : AreaTriggerAI
{
    at_tapped_keg(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger) { }

    void OnUnitEnter(Unit* unit)
    {
        if (unit && unit->IsPlayer())
            if (!unit->HasAura(CouncilCaptainSpells::SPELL_TAPPED_KEG_BUFF))
                unit->CastSpell(unit, CouncilCaptainSpells::SPELL_TAPPED_KEG_BUFF, true);
    }

    void OnUnitExit(Unit* unit)
    {
        if (unit && unit->HasAura(CouncilCaptainSpells::SPELL_TAPPED_KEG_BUFF))
            unit->RemoveAurasDueToSpell(CouncilCaptainSpells::SPELL_TAPPED_KEG_BUFF);
    }
};

///< Areatrigger Whirlpool of Blades - SpellID: 272377, AtID: 13632
struct at_whirlpool_of_blades : AreaTriggerAI
{
    at_whirlpool_of_blades(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger) {}

    void OnInitialize() override
    {
        at->SetPeriodicProcTimer(1000);

        if (InstanceScript* instance = at->GetInstanceScript())
            if (Creature* jolly = instance->GetCreature(NPC_CAPTAIN_JOLLY))
                JollyGuid = jolly->GetGUID();
    }

    void OnPeriodicProc() override
    {
        if (Unit* caster = at->GetCaster())
        {
            for (ObjectGuid guid : at->GetInsideUnits())
            {
                if (Player* player = ObjectAccessor::GetPlayer(*caster, guid))
                    player->CastSpell(player, CouncilCaptainSpells::SPELL_WHIRLPOOL_OF_BLADES, CastSpellExtraArgs(true).SetOriginalCaster(JollyGuid));

                else if (guid == JollyGuid && caster->IsCreature())
                    caster->ToCreature()->DespawnOrUnsummon(1s);
            }
        }
    }

private:
    ObjectGuid JollyGuid;
};


void AddSC_boss_council_o_captains()
{
    //Creatures
    RegisterCreatureAI(npc_council_o_captains_jolly);
    RegisterCreatureAI(npc_council_o_captains_eudora);
    RegisterCreatureAI(npc_council_o_captains_raoul);
    RegisterCreatureAI(npc_rummy_mancomb);
    RegisterCreatureAI(npc_blackout_barrel);
    RegisterCreatureAI(npc_bilge_rat_grok_jerk);
    RegisterCreatureAI(npc_freehold_otis);
    RegisterCreatureAI(npc_freehold_jail);
    RegisterCreatureAI(npc_freehold_murphy);

    //Spells
    RegisterSpellScript(spell_powder_shot_target_select);
    RegisterSpellScript(spell_freehold_keyring);
    RegisterSpellScript(spell_freehold_jail_opening);
    RegisterSpellScript(spell_freehold_brew);

    //Auras
    RegisterSpellScript(spell_tending_bar);

    //Areatriggers
    RegisterAreaTriggerAI(at_tapped_keg);
    RegisterAreaTriggerAI(at_whirlpool_of_blades);
}
