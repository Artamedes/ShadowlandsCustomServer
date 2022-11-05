#include "AreaTriggerAI.h"
#include "ScriptMgr.h"
#include "SpellScript.h"
#include "Player.h"

enum GameObjects
{
    GAMEOBJECT_STARTING_ROOM_COLLISION = 378473,
};

enum Spells
{
    SPELL_AWAKEN_ABANDON = 369744,
    SPELL_PLAYER_STASIS = 365560,
};

enum Npcs
{
    NPC_KODETHI = 181494,
    NPC_TETHALASH = 181680,
    NPC_AZURATHEL = 183380,
};

// 370111
class spell_summon_kodethi_370111 : public SpellScript
{
    PrepareSpellScript(spell_summon_kodethi_370111);

    void RelocateDest(SpellEffIndex /*effIndex*/)
    {
        GetHitDest()->Relocate({ 5818.533f, -3054.5625f, 251.27975f, 5.480333805084228515f });
    }

    void Register() override
    {
        OnEffectLaunch += SpellEffectFn(spell_summon_kodethi_370111::RelocateDest, EFFECT_0, SPELL_EFFECT_SUMMON);
    }
};

/// ID: 369772 The War Creche - Upper Floor
class spell_the_war_creche_upper_floor : public AuraScript
{
    PrepareAuraScript(spell_the_war_creche_upper_floor);

    enum Spells
    {
        
        SPELL_INTRO_SCENE = 389778,
        SPELL_SHAPESHIFT = 97709,
        SPELL_SUMMON_KODETHI = 370111,
    };

    enum Quests
    {
        QUESTS_AWAKEN_DRACTHYR = 64864,
    };

    enum Objectives
    {
        OBJECTIVE_KODETHI = 421735,
        OBJECTIVE_TETHALASH = 423680,
        OBJECTIVE_AZURATHEL = 422316,
    };

    void HandleApply(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Unit* target = GetTarget();
        if (Player* player = target->ToPlayer())
        {
            if (player->GetQuestStatus(QUESTS_AWAKEN_DRACTHYR) == QUEST_STATUS_NONE)
            {
                player->NearTeleportTo({5830.74f, -3066.08f, 251.04f}); // hackfix location
                player->CastSpell(player, SPELL_SHAPESHIFT, true);
                player->CastSpell(player, SPELL_PLAYER_STASIS, true);
                player->CastSpell(player, SPELL_INTRO_SCENE, true);
            }
            else if (player->GetQuestStatus(QUESTS_AWAKEN_DRACTHYR) == QUEST_STATUS_INCOMPLETE)
            {
                uint16 slot = player->FindQuestSlot(QUESTS_AWAKEN_DRACTHYR);
                if (slot >= MAX_QUEST_LOG_SIZE)
                    return;

                QuestObjective const* objKodethi = sObjectMgr->GetQuestObjective(OBJECTIVE_KODETHI);
                QuestObjective const* objTethalash = sObjectMgr->GetQuestObjective(OBJECTIVE_KODETHI);
                QuestObjective const* objAzurathel = sObjectMgr->GetQuestObjective(OBJECTIVE_KODETHI);
                if (!objKodethi || !objTethalash || !objAzurathel)
                    return;

                if (player->GetQuestSlotObjectiveData(slot, *objKodethi) == 0)
                {
                    player->NearTeleportTo({ 5830.74f, -3066.08f, 251.04f }); // hackfix location
                    player->SummonGameObject(GAMEOBJECT_STARTING_ROOM_COLLISION, { 5818.5297f, -3054.56f, 251.2799f, 5.48f }, { 0.f, 0.f, -0.39f, 0.9205f }, Seconds(0), GO_SUMMON_TIMED_OR_CORPSE_DESPAWN, player->GetGUID());

                    if (!player->GetSummonedCreatureByEntry(NPC_KODETHI))
                        player->CastSpell(player, SPELL_SUMMON_KODETHI, true);
                }

                if (player->GetQuestSlotObjectiveData(slot, *objTethalash) == 0)
                {
                    if (!player->GetSummonedCreatureByEntry(NPC_TETHALASH))
                        player->SummonCreature(NPC_TETHALASH, {5779.37f, -3038.77f, 210.49f, 2.48f}, TEMPSUMMON_MANUAL_DESPAWN, 0, 0, 0, player->GetGUID());
                }

                if (player->GetQuestSlotObjectiveData(slot, *objAzurathel) == 0)
                {
                    if (!player->GetSummonedCreatureByEntry(NPC_AZURATHEL))
                        player->SummonCreature(NPC_AZURATHEL, { 5800.2299f, -2905.87f, 207.1869f, 5.469f }, TEMPSUMMON_MANUAL_DESPAWN, 0, 0, 0, player->GetGUID());
                }
            }
        }
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_the_war_creche_upper_floor::HandleApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

/// ID: 389778 Stasis
class spell_stasis_389778 : public AuraScript
{
    PrepareAuraScript(spell_stasis_389778);

    enum Spells
    {
        SPELL_SUMMON_KODETHI = 370111,
        SPELL_ACCEPT_QUEST = 369919,
    };

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Unit* target = GetTarget();
        if (Player* player = target->ToPlayer())
        {
            // probably by an other spell
            player->RemoveAurasDueToSpell(SPELL_PLAYER_STASIS);

            player->CastSpell(player, SPELL_ACCEPT_QUEST, true);

            if (!player->GetSummonedCreatureByEntry(NPC_KODETHI))
            {
                player->CastSpell(player, SPELL_SUMMON_KODETHI, true);

                if (GameObject* go = player->SummonGameObject(GAMEOBJECT_STARTING_ROOM_COLLISION, { 5818.5297f, -3054.56f, 251.2799f, 5.48f }, { 0.f, 0.f, -0.39f, 0.9205f }, Seconds(0), GO_SUMMON_TIMED_OR_CORPSE_DESPAWN, player->GetGUID()))
                    player->AddGameObject(go);
            }

            if (!player->GetSummonedCreatureByEntry(NPC_TETHALASH))
                player->SummonCreature(NPC_TETHALASH, { 5779.37f, -3038.77f, 210.49f, 2.48f }, TEMPSUMMON_MANUAL_DESPAWN, 0, 0, 0, player->GetGUID());

            if (!player->GetSummonedCreatureByEntry(NPC_AZURATHEL))
                player->SummonCreature(NPC_AZURATHEL, { 5800.2299f, -2905.87, 207.1869, 5.469f }, TEMPSUMMON_MANUAL_DESPAWN, 0, 0, 0, player->GetGUID());
        }
    }

    void Register() override
    {
        OnEffectRemove += AuraEffectApplyFn(spell_stasis_389778::HandleRemove, EFFECT_0, SPELL_AURA_PLAY_SCENE, AURA_EFFECT_HANDLE_REAL);
    }
};

// 64864
struct quest_awkaken_dracthyr : public QuestScript
{
    quest_awkaken_dracthyr() : QuestScript("quest_awkaken_dracthyr") { }

    enum Objectives
    {
        OBJECTIVE_ALLY_AWAKENED = 421735,
    };

    enum Spells
    {
        SPELL_THE_WAR_CRECHE = 369772,
    };

    void OnQuestStatusChange(Player* player, Quest const* /*quest*/, QuestStatus /*oldStatus*/, QuestStatus newStatus)
    {
        if (newStatus == QUEST_STATUS_NONE)
        {
            player->CastSpell(player, SPELL_AWAKEN_ABANDON, true);

            player->RemoveAurasDueToSpell(SPELL_THE_WAR_CRECHE);
            player->AddAura(SPELL_THE_WAR_CRECHE);
        }
    }

    void OnQuestObjectiveChange(Player* player, Quest const* /*quest*/, QuestObjective const& objective, int32 oldAmount, int32 newAmount) override
    {
        if (oldAmount == 0 && newAmount == 1 && objective.ID == OBJECTIVE_ALLY_AWAKENED)
        {
            for (GameObject* go : player->GetGameObjects(0))
                if (go->GetEntry() == GAMEOBJECT_STARTING_ROOM_COLLISION)
                    go->DespawnOrUnsummon();
        }
    }
};

// 370064
class spell_lapisagos_intro_teleport_370064 : public SpellScript
{
    PrepareSpellScript(spell_lapisagos_intro_teleport_370064);

    void RelocateDest(SpellEffIndex /*effIndex*/)
    {
        GetHitDest()->Relocate({ 6009.6606f, -3102.7588f, 200.10481f, 5.410520553588867187f });
    }

    void Register() override
    {
        OnEffectLaunch += SpellEffectFn(spell_lapisagos_intro_teleport_370064::RelocateDest, EFFECT_0, SPELL_EFFECT_TELEPORT_UNITS);
    }
};


// spell warning glide 369820

/// ID: 370046 
class spell_lapisagos_intro_scene_370046 : public AuraScript
{
    PrepareAuraScript(spell_lapisagos_intro_scene_370046);

    enum Spells
    {
        SPELL_LAPISAGOS_INTRO_TP = 370064,
        SPELL_BIND = 377710,
    };

    enum Npcs : uint32
    {
        NPC_AZURATHEL = 181597,
        NPC_KODETHI = 186865,
        NPC_DERVISHIAN = 182069,
        NPC_CINDRETHTHRESH = 182696,
    };

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Unit* target = GetTarget();

        if (Player* player = target->ToPlayer())
        {
            player->CastSpell(player, SPELL_LAPISAGOS_INTRO_TP, true);

            player->SummonCreature(NPC_AZURATHEL, { 6009.64f, -3107.12f, 200.576f, 5.4105f }, TEMPSUMMON_MANUAL_DESPAWN, 0, 0, 0, player->GetGUID());
            player->SummonCreature(NPC_KODETHI, { 6005.67f, -3101.92f, 200.128f, 5.4105f }, TEMPSUMMON_MANUAL_DESPAWN, 0, 0, 0, player->GetGUID());
            player->SummonCreature(NPC_DERVISHIAN, { 6006.22f, -3106.34f, 200.482f, 1.8677f }, TEMPSUMMON_MANUAL_DESPAWN, 0, 0, 0, player->GetGUID());
            player->SummonCreature(NPC_CINDRETHTHRESH, { 6012.11f, -3105.18f, 200.55f, 5.2094f }, TEMPSUMMON_MANUAL_DESPAWN, 0, 0, 0, player->GetGUID());
        }
    }

    void Register() override
    {
        OnEffectRemove += AuraEffectApplyFn(spell_lapisagos_intro_scene_370046::HandleRemove, EFFECT_0, SPELL_AURA_PLAY_SCENE, AURA_EFFECT_HANDLE_REAL);
    }
};

// 64866
struct quest_into_the_cauldron : public QuestScript
{
    quest_into_the_cauldron() : QuestScript("quest_into_the_cauldron") { }

    void OnQuestStatusChange(Player* player, Quest const* /*quest*/, QuestStatus /*oldStatus*/, QuestStatus newStatus)
    {
        if (newStatus == QUEST_STATUS_COMPLETE)
        {
            int dragons[] = {186883, 181053, 182168, 183960};
            for (int dragon : dragons)
            {
                if (Creature* summon = player->SummonCreature(dragon, { 6095.41f, -3225.99f, 141.191f, 3.6078f }, TEMPSUMMON_MANUAL_DESPAWN, 0, 0, 0, player->GetGUID()))
                    if (UnitAI* ai = summon->AI())
                        ai->SetData(1, 1);
            }
        }
    }
};

// custom at
struct into_the_cauldron_at : public AreaTriggerAI
{
    into_the_cauldron_at(AreaTrigger* at) : AreaTriggerAI(at) {}

    enum Credits
    {
        GLIDE_DOWN_CREDIT = 181597,
    };

    void OnUnitEnter(Unit* unit) override
    {
        if (Player* player = unit->ToPlayer())
            player->KilledMonsterCredit(GLIDE_DOWN_CREDIT);
    }
};

void AddSC_the_forbidden_reach()
{
    RegisterSpellScript(spell_the_war_creche_upper_floor);
    RegisterSpellScript(spell_summon_kodethi_370111);
    RegisterSpellScript(spell_stasis_389778);
    new quest_awkaken_dracthyr();
    RegisterSpellScript(spell_lapisagos_intro_teleport_370064);
    RegisterSpellScript(spell_lapisagos_intro_scene_370046);
    new quest_into_the_cauldron();
    RegisterAreaTriggerAI(into_the_cauldron_at);
}
