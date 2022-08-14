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
#include "InstanceScript.h"
#include "AreaBoundary.h"
#include "GameEventMgr.h"

static BossBoundaryData const boundaries =
{
    { DATA_SKYCAP_KRAGG,        new CircleBoundary(KraggMiddlePos,         40.0f) },
    { DATA_COUNCIL_O_CAPTAINS,  new CircleBoundary(CouncilOCaptainsMiddle, 50.0f) },
    { DATA_RING_OF_BOOTY,       new CircleBoundary(ArenaMiddlePos,         35.0f) },
    { DATA_HARLAN_SWEETE,       new CircleBoundary(SweetesLandingCenter,   70.0f) }
};

EntranceData const entranceData[] =
{
    { DATA_SKYCAP_KRAGG,       6375 },
    { DATA_COUNCIL_O_CAPTAINS, 6376 }
};

struct instance_free_hold : public InstanceScript
{
    instance_free_hold(InstanceMap* map) : InstanceScript(map)
    {
        SetBossNumber(DATA_MAX_ENCOUNTERS);
        LoadBossBoundaries(boundaries);
        LoadEntranceData(entranceData);

        if (sGameEventMgr->IsActiveEvent(201))
        {
            InstanceScript::SetData(DATA_FRIENDLY_CAPTAIN, NPC_CAPTAIN_RAOUL);
            blacktooth_brawl_guids.clear();
            blactooth_brawl_started = false;
            friendly_captain = NPC_CAPTAIN_RAOUL;

            if (auto dummy = instance->SummonCreature(NPC_TRAINING_DUMMY, TrainingDummySpawnPosition))
            {
                dummy->DisableEvadeMode();
                dummy->SetReactState(REACT_PASSIVE);
            }

            for (auto&& itr : KnuckledusterSpawnPos)
                if (auto knukleduster = instance->SummonCreature(NPC_BLACKTOOTH_KDUSTER, itr))
                {
                    knukleduster->SetEmoteState(EMOTE_STATE_ATTACK_UNARMED);
                    knukleduster->AddWorldEffect(8326);
                }
        }
        else if (sGameEventMgr->IsActiveEvent(202))
        {
            InstanceScript::SetData(DATA_FRIENDLY_CAPTAIN, NPC_CAPTAIN_EUDORA);
            friendly_captain = NPC_CAPTAIN_EUDORA;

            for (auto&& itr : BilgeRatGrogJerkSpawnPos)
                if (auto knukleduster = instance->SummonCreature(NPC_BILGE_RAT_GROG_JERK, itr))
                    knukleduster->AddWorldEffect(8326);

            for (auto&& itr : BilgeRatPartyAnimal1SpawnPos)
                instance->SummonCreature(NPC_BILGE_RAT_PARTY_ANIMAL, itr);

            for (auto&& itr : BilgeRatPartyAnimal2SpawnPos)
                instance->SummonCreature(NPC_BILGE_RAT_PARTY_ANIMAL2, itr);
        }
        else
        {
            InstanceScript::SetData(DATA_FRIENDLY_CAPTAIN, NPC_CAPTAIN_JOLLY);
            friendly_captain = NPC_CAPTAIN_JOLLY;

            instance->SummonCreature(NPC_OTIS, OtisSpawnPosition);

            if (Creature* jail = instance->SummonCreature(NPC_FREEHOLD_JAIL, JailSpawnPosition))
                jail->AddWorldEffect(8318);

            if (Creature* murphy = instance->SummonCreature(NPC_MURPHY, MurphySpawnPosition))
                murphy->AddWorldEffect(8326);
        }
    }

    void OnCreatureCreate(Creature* creature) override
    {
        InstanceScript::OnCreatureCreate(creature);
        
        switch (creature->GetEntry())
        {
        case NPC_SKYCAP_KRAGG_INTRO:
        case NPC_SHARKBAIT_INTRO:
            if (InstanceScript::GetBossState(DATA_SKYCAP_KRAGG) != DONE)
                if (creature->isDead())
                    creature->Respawn();
            break;

        case NPC_BLACKTOOTH_BRUTE:
        case NPC_BLACKTOOTH_SCRAPPER:
        case NPC_BLACKTOOTH_KDUSTER:
            if (friendly_captain == NPC_CAPTAIN_RAOUL)
                creatures_to_update.insert(creature->GetGUID());
            break;

        case NPC_BILGE_RAT_SWABBY:
        case NPC_BILGE_RAT_PADFOOT:
        case NPC_BILGE_RAT_BUCCANEER:
        case NPC_BILGE_RAT_BRINESCALE:
            if (friendly_captain == NPC_CAPTAIN_EUDORA)
                creatures_to_update.insert(creature->GetGUID());
            break;

        case NPC_CUTWATER_DUELIST:
        case NPC_CUTWATER_KNIFE_JUGGLER:
        case NPC_CUTWATER_HARPONEER:
            if (friendly_captain == NPC_CAPTAIN_JOLLY)
                creatures_to_update.insert(creature->GetGUID());
            break;
        default:
            break;
        }
    }

    void SetData(uint32 id, uint32 value) override
    {
        InstanceScript::SetData(id, value);

        if (id == DATA_COUNCIL_O_CAPTAIN_PRE_EVENT)
        {
            for (ObjectGuid guid : creatures_to_update)
            {
                if (Creature* creature = instance->GetCreature(guid))
                    if (creature->IsAlive())
                        creature->SetFaction(FACTION_FRIENDLY);
            }
        }
    }

    void ProcessEvent(WorldObject* src, uint32 id, WorldObject* invoker) override
    {
        switch (id)
        {
            case ACTION_BLACKTOOTH_BRAWL_ENGAGE:
            {
                if (!blactooth_brawl_started)
                {
                    blactooth_brawl_started = true;

                    if (Creature* knuckleduster = src->ToCreature())
                    {
                        knuckleduster->ToCreature()->AI()->Talk(0);
                        knuckleduster->ToCreature()->HandleEmoteCommand(EMOTE_ONESHOT_BATTLE_ROAR);
                    }

                    for (auto&& itr : BrutesSpawnPos)
                        if (Creature* brute = instance->SummonCreature(NPC_BLACKTOOTH_BRUTE, itr))
                        {
                            brute->AddWorldEffect(8326);
                            blacktooth_brawl_guids.insert(brute->GetGUID());
                        }

                    for (auto&& itr : ScrapperSpawnPos)
                        if (Creature* scrapper = instance->SummonCreature(NPC_BLACKTOOTH_SCRAPPER, itr))
                        {
                            scrapper->AddWorldEffect(8326);
                            blacktooth_brawl_guids.insert(scrapper->GetGUID());
                        }
                }

                for (auto summon : blacktooth_brawl_guids)
                    if (Creature* target = instance->GetCreature(summon))
                        if (target->IsAlive() && !target->IsInCombat() && target->AI())
                            target->AI()->DoZoneInCombat();
            }
            default:
                break;
        }

    }

    bool SetBossState(uint32 id, EncounterState state, bool step) override
    {
        if (!InstanceScript::SetBossState(id, state, step))
            return false;

        if (id == DATA_COUNCIL_O_CAPTAINS)
        {
            if (state == DONE && !instance->IsChallengeMode())
                instance->SummonGameObject(FreeholdGameObject::GO_COUNCIL_TRIBUTE, CouncilOCaptainCachePos, QuaternionData(0, 0, -0.9999819f, 0.006019935f), 7200);

            if (instance->IsHeroic() || instance->IsMythic())
            {
                if (state == FAIL || state == DONE)
                {
                    if (Creature* tender = InstanceScript::GetCreature(NPC_RUMMY_MANCOMB))
                        tender->RemoveAurasDueToSpell(SPELL_TENDING_BAR);
                }
                else if (state == IN_PROGRESS)
                    if (Creature* tender = InstanceScript::GetCreature(NPC_RUMMY_MANCOMB))
                        tender->CastSpell(tender, SPELL_TENDING_BAR, true);
            }
        }

        return true;
    }

    void OnUnitDeath(Unit*  u) override
    {
        auto creature = u->ToCreature();
        if (!creature)
            return;

        if (creature->GetEntry() == NPC_IRONTIDE_ENFORCER && creature->GetHomePosition().GetExactDist(KraggMiddlePos) < 45.0f)
        {
            if (GetData(DATA_SKYCAP_KRAGG_INTRO))
            {
                if (Creature* sharkbait = InstanceScript::GetCreature(NPC_SHARKBAIT_INTRO))
                    if (sharkbait->AI())
                        sharkbait->GetAI()->DoAction(ACTION_SKYCAP_APPEAR);
            }
            else SetData(DATA_SKYCAP_KRAGG_INTRO, 1);
        }
        else if (creature->GetEntry() == NPC_BLACKTOOTH_KDUSTER && creature->IsSummon())
        {
            if (GetData(DATA_BLACKTOOTH_BRAWL))
            {
                creature->CastSpell(creature, SPELL_BLACKTOOTH_REGALIA, true);

                SetData(DATA_COUNCIL_O_CAPTAIN_PRE_EVENT, 1);

                if (Creature* eudora = GetCreature(NPC_CAPTAIN_EUDORA))
                    eudora->SetFaction(FACTION_ENEMY);

                if (Creature* jolly = GetCreature(NPC_CAPTAIN_JOLLY))
                    jolly->SetFaction(FACTION_ENEMY);

                if (Creature* raoul = GetCreature(NPC_CAPTAIN_RAOUL))
                    raoul->SetFaction(FACTION_FRIENDLY);
            }
            else SetData(DATA_BLACKTOOTH_BRAWL, 1);
        }
    }

    private:
        GuidUnorderedSet blacktooth_brawl_guids;
        GuidUnorderedSet creatures_to_update;
        bool blactooth_brawl_started;
        uint32 friendly_captain;
};

///< ID: 6422
struct conversation_sharkbait_outro : public ConversationScript
{
    conversation_sharkbait_outro() : ConversationScript("conversation_sharkbait_outro") {}

    void OnConversationCreate(Conversation* conversation, Unit* creator) override
    {
        if (InstanceScript* instance = creator->GetInstanceScript())
        {
            if (Creature* sharkbait = instance->GetCreature(NPC_SHARKBAIT_BOSS))
                conversation->AddActor(0, 0, sharkbait->GetGUID());
        }
    }
};;

///< ID: 6354
struct conversation_otis_intro : public ConversationScript
{
    conversation_otis_intro() : ConversationScript("conversation_otis_intro") {}

    void OnConversationCreate(Conversation* conversation, Unit* creator)
    {
        if (InstanceScript* instance = creator->GetInstanceScript())
        {
            if (Creature* otis = instance->GetCreature(NPC_OTIS))
                conversation->AddActor(0, 0, otis->GetGUID());
        }
    }
};

///< ID: 6360
struct conversation_otis_outro : public ConversationScript
{
    conversation_otis_outro() : ConversationScript("conversation_otis_outro") {}

    void OnConversationCreate(Conversation* conversation, Unit* creator)
    {
        if (InstanceScript* instance = creator->GetInstanceScript())
        {
            if (Creature* otis = instance->GetCreature(NPC_OTIS))
                conversation->AddActor(0, 0, otis->GetGUID());
        }
    }
};


void AddSC_instance_free_hold()
{
    RegisterInstanceScript(instance_free_hold, 1754);

    //Conversations
    new conversation_sharkbait_outro();
    new conversation_otis_intro();
    new conversation_otis_outro();
}
