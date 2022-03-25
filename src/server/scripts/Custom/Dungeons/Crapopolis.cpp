#include "ScriptMgr.h"
#include "SpellAuraEffects.h"
#include "ScriptedCreature.h"
#include "Creature.h"
#include "Player.h"
#include "../CustomInstanceScript.h";

struct npc_crapopolis_ai_base : public ScriptedAI
{
    public:
        npc_crapopolis_ai_base(Creature* p_Creature) : ScriptedAI(p_Creature) { RandomHealth = urand(80, 95); }

        EventMap events;
        uint32 RandomHealth = 0;

        void UpdateAI(uint32 p_Diff) override
        {
            if (!UpdateVictimCrapopolis())
                return;

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            RunAIEvents(p_Diff);

            DoMeleeAttackIfReady();
        }

        virtual void RunAIEvents(uint32 p_Diff)
        {

        }

        bool UpdateVictimCrapopolis()
        {
            if (!IsEngaged())
            {
                if (!me->HasReactState(REACT_PASSIVE))
                    if (Unit* victim = SelectVictimCrap())
                        if (victim != me->GetVictim())
                            AttackStart(victim);

                return false;
            }

            if (!me->IsAlive())
            {
                EngagementOver();
                return false;
            }

            if (!me->HasReactState(REACT_PASSIVE))
            {
                if (Unit* victim = me->SelectVictim())
                    if (victim != me->GetVictim())
                        AttackStart(victim);

                return me->GetVictim() != nullptr;
            }
            else if (!me->IsInCombat())
            {
                EnterEvadeMode(EVADE_REASON_NO_HOSTILES);
                return false;
            }
            else if (me->GetVictim())
                me->AttackStop();

            return true;
        }

        Unit* SelectVictimCrap()
        {
            Unit* target = me->SelectNearestTargetInAttackDistance(25.0f);

            if (target && me->_IsTargetAcceptable(target) && me->CanCreatureAttack(target))
            {
                if (!me->HasSpellFocus())
                    me->SetInFront(target);
                return target;
            }

            return nullptr;
        }

        void DamageTaken(Unit* p_Who, uint32& p_Damage, DamageEffectType /*damageType*/, SpellInfo const* /*spellInfo = nullptr*/) override
        {
            if (p_Who->IsCreature() && p_Who->GetEntry() >= 700200 && p_Who->GetEntry() <= 700220)
            {
                if (me->HealthBelowPctDamaged(RandomHealth, p_Damage))
                    p_Damage = 0;
            }
        }
};


struct npc_refreshment_vendor_700201 : public npc_crapopolis_ai_base
{
    npc_refreshment_vendor_700201(Creature* creature) : npc_crapopolis_ai_base(creature) {}


    void Reset() override
    {
        events.Reset();
    }

    void JustEngagedWith(Unit* /*who*/) override
    {
        events.ScheduleEvent(1, 1s);
        events.ScheduleEvent(2, 7s);
    }

    void RunAIEvents(uint32 diff) override
    {
        events.Update(diff);

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        switch (events.ExecuteEvent())
        {
            case 1:
                DoCastVictim(280604);
                events.Repeat(7s, 9s);
                break;

            case 2:
            {
                std::list<Unit*> unitList;
                me->GetFriendlyUnitListInRange(unitList, 30.0f, true);
                unitList.remove_if([this](Unit* unit) { return !unit || !unit->IsInCombat(); });
                if (Unit* target = Trinity::Containers::SelectRandomContainerElement(unitList))
                    me->CastSpell(target, 268129);
                events.Repeat(5s, 7s);
            } break;

            default:
                break;
        }
    }
};

struct npc_mawsworn_axeguard : public npc_crapopolis_ai_base
{
    public:
        npc_mawsworn_axeguard(Creature* creature) : npc_crapopolis_ai_base(creature) { }

        void Reset() override
        {
            me->SetEmoteState(EMOTE_STATE_READY1H);
            events.Reset();
        }

        void JustEngagedWith(Unit* /*who*/) override
        {
            me->SetEmoteState(EMOTE_STATE_NONE);
            events.ScheduleEvent(1, 8s, 12s);
            events.ScheduleEvent(2, 7s);
            events.ScheduleEvent(3, 15s, 20s);
        }


        void RunAIEvents(uint32 diff) override
        {
            events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            switch (events.ExecuteEvent())
            {
                case 1:
                    DoCastVictim(292903);
                    events.Repeat(15s, 20s);
                    break;
                case 2:
                    DoCastSelf(294165);
                    events.Repeat(15s, 20s);
                    break;
                case 3:
                    DoCastVictim(357110);
                    events.Repeat(15s, 20s);
                    break;
            }
        }
};

struct npc_mawsworn_annihilator : public npc_crapopolis_ai_base
{
    public:
        npc_mawsworn_annihilator(Creature* creature) : npc_crapopolis_ai_base(creature) { }

        void Reset() override
        {
            me->SetEmoteState(EMOTE_STATE_READY1H);
            events.Reset();
        }

        void JustEngagedWith(Unit* /*who*/) override
        {
            me->SetEmoteState(EMOTE_STATE_NONE);
            events.ScheduleEvent(1, 8s, 12s);
            events.ScheduleEvent(2, 7s);
            events.ScheduleEvent(3, 17s);
            events.ScheduleEvent(4, 15s);
        }


        void RunAIEvents(uint32 diff) override
        {
            events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            switch (events.ExecuteEvent())
            {
                case 1:
                    DoCastVictim(364355);
                    events.Repeat(15s, 20s);
                    break;
                case 2:
                    DoCastSelf(356306);
                    events.Repeat(15s, 20s);
                    break;
                case 3:
                    DoCastSelf(294165);
                    events.Repeat(15s, 20s);
                    break;
                case 4:
                    DoCastSelf(292942);
                    events.Repeat(35s, 40s);
                    break;
            }
        }
};

struct npc_venture_co_war_machine : public npc_crapopolis_ai_base
{
    npc_venture_co_war_machine(Creature* creature) : npc_crapopolis_ai_base(creature) {}

    void Reset() override
    {
        events.Reset();
    }

    void JustEngagedWith(Unit* /*who*/) override
    {
        events.ScheduleEvent(1, 2s, 4s);
    }


    void RunAIEvents(uint32 diff) override
    {
        events.Update(diff);

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        if (events.ExecuteEvent() == 1)
        {
            DoCastVictim(269099);
            events.Repeat(6s, 10s);
        }

        DoMeleeAttackIfReady();
    }
};


struct spell_iced_spritzer : public AuraScript
{
    PrepareAuraScript(spell_iced_spritzer);

    void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        AuraRemoveMode removeMode = GetTargetApplication()->GetRemoveMode();
        if (removeMode != AURA_REMOVE_BY_EXPIRE)
            return;

        Unit* caster = GetCaster();
        Unit* victim = GetTarget();

        if (caster && victim)
            caster->CastSpell(victim, 280605);
    }

    void Register() override
    {
        OnEffectRemove += AuraEffectRemoveFn(spell_iced_spritzer::OnRemove, EFFECT_1, SPELL_AURA_MOD_INCREASE_SPEED, AURA_EFFECT_HANDLE_REAL);
    }
};


class instance_crapopolis : public InstanceMapScript
{
public:
    instance_crapopolis() : InstanceMapScript("instance_crapopolis", 2263) { }

    struct instance_maelstrom_invasion_InstanceMapScript : public CustomInstanceScript
    {
        public:
            instance_maelstrom_invasion_InstanceMapScript(InstanceMap* map) : CustomInstanceScript(map)
            {
                // SetHeaders(DataHeader);
                // SetBossNumber(EncounterCount);
            }

         //   void OnCreatureCreate(Creature* p_Creature) override
         //   {
         //       switch (p_Creature->GetEntry())
         //       {
         //           case 700214:
         //               mawswornDefilerGuid = p_Creature->GetGUID();
         //               break;
         //       }
         //   }
         //
         //   void OnGameObjectCreate(GameObject* p_GameObject) override
         //   {
         //       switch (p_GameObject->GetEntry())
         //       {
         //           // torghast portal
         //           case 368984:
         //               latestTorghastPortal = p_GameObject->GetGUID();
         //               break;
         //       }
         //   }
         //
         //   void OnUnitDeath(Unit* p_Unit) override
         //   {
         //       if (p_Unit->IsCreature())
         //       {
         //           switch (p_Unit->GetEntry())
         //           {
         //               case 700214:
         //                   m_Scheduler.Schedule(1s, [this](TaskContext context)
         //                   {
         //                       if (auto l_GameObject = instance->GetGameObject(latestTorghastPortal))
         //                       {
         //
         //                       }
         //                   });
         //                   break;
         //           }
         //       }
         //   }
         //
         //   void Update(uint32 diff) override
         //   {
         //       m_Scheduler.Update(diff);
         //   }

        private:
            ObjectGuid mawswornDefilerGuid;
            ObjectGuid latestTorghastPortal;
            TaskScheduler m_Scheduler;
    };

    InstanceScript* GetInstanceScript(InstanceMap* map) const override
    {
        return new instance_maelstrom_invasion_InstanceMapScript(map);
    }
};

struct npc_mawsworn_defiler : public npc_crapopolis_ai_base
{
    npc_mawsworn_defiler(Creature* creature) : npc_crapopolis_ai_base(creature) {}

    TaskScheduler scheduler;

    void Reset() override
    {
        events.Reset();
    }

    void JustEngagedWith(Unit* /*who*/) override
    {
        Talk(0);
        events.ScheduleEvent(1, 2s, 4s);
    }

    void JustDied(Unit* /*killer*/) override
    {
        Talk(1);
        scheduler.Schedule(5s, [this](TaskContext context)
        {
            Talk(2);
            if (auto instance = me->GetInstanceScript())
                instance->DoCastSpellOnPlayers(368230);
            me->SummonGameObject(368984, { 1029.028076f, -3572.835205f, 12.149024f }, {0.0f, 0.0f, -0.982807f, -0.184636f}, 10s, GOSummonType::GO_SUMMON_TIMED_DESPAWN);

            scheduler.Schedule(5s, [this](TaskContext context)
            {
                me->SummonCreature(700220, { 1029.028076f, -3572.835205f, 12.149024f, 2.73798f }, TempSummonType::TEMPSUMMON_MANUAL_DESPAWN);
            });
        });
    }

    void UpdateAI(uint32 diff) override
    {
        scheduler.Update(diff);
        npc_crapopolis_ai_base::UpdateAI(diff);
    }

    void RunAIEvents(uint32 diff) override
    {
        events.Update(diff);

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        if (uint32 l_EventId = events.ExecuteEvent())
        {
            switch (l_EventId)
            {

            }
        }

        DoMeleeAttackIfReady();
    }
};

struct npc_crap_warden_of_souls : public npc_crapopolis_ai_base
{
    npc_crap_warden_of_souls(Creature* creature) : npc_crapopolis_ai_base(creature) {}

    TaskScheduler scheduler;

    void InitializeAI() override
    {
        me->SetReactState(REACT_PASSIVE);
        me->AddUnitFlag(UNIT_FLAG_IMMUNE_TO_PC);
        me->AddUnitFlag(UNIT_FLAG_NON_ATTACKABLE);
        me->GetMotionMaster()->MovePoint(1, { 999.312012f, -3556.616699f, 12.931227f, 3.894261f });
    }

    void MovementInform(uint32 type, uint32 id) override
    {
        if (type == POINT_MOTION_TYPE && id == 1)
        {
            // Roar
            me->SetEmoteState(Emote::EMOTE_ONESHOT_ROAR);
            DoCast(357822);
            scheduler.Schedule(100ms, [this](TaskContext context)
                {
                    me->SetFacingTo(3.894261f);
                });
            scheduler.Schedule(2s, [this](TaskContext context)
            {
                me->SetEmoteState(Emote::EMOTE_ONESHOT_NONE);
                me->SetReactState(REACT_AGGRESSIVE);
                me->RemoveUnitFlag(UNIT_FLAG_IMMUNE_TO_PC);
                me->RemoveUnitFlag(UNIT_FLAG_NON_ATTACKABLE);
            });
        }
    }

    void Reset() override
    {
        events.Reset();
    }

    void JustEngagedWith(Unit* /*who*/) override
    {
        me->SetEmoteState(Emote::EMOTE_ONESHOT_NONE);
        events.ScheduleEvent(1, 2s, 4s);
        events.ScheduleEvent(2, 12s, 14s);
        events.ScheduleEvent(3, 12s, 14s);
    }

    void JustDied(Unit* /*killer*/) override
    {
        scheduler.Schedule(5s, [this](TaskContext context)
            {
                Talk(0);
                me->SummonGameObject(368984, { 1029.028076f, -3572.835205f, 12.149024f }, { 0.0f, 0.0f, -0.982807f, -0.184636f }, 10s, GOSummonType::GO_SUMMON_TIMED_DESPAWN);

                scheduler.Schedule(5s, [this](TaskContext context)
                    {
                        me->SummonCreature(700221, { 1029.028076f, -3572.835205f, 12.149024f, 2.73798f }, TempSummonType::TEMPSUMMON_MANUAL_DESPAWN);
                    });
            });
    }

    void UpdateAI(uint32 diff) override
    {
        scheduler.Update(diff);
        npc_crapopolis_ai_base::UpdateAI(diff);
    }

    void RunAIEvents(uint32 diff) override
    {
        events.Update(diff);

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        if (uint32 l_EventId = events.ExecuteEvent())
        {
            switch (l_EventId)
            {
            case 1:
                DoCastVictim(357920);
                events.Repeat(10s, 15s);
                break;
            case 2:
                DoCastVictim(356885);
                events.Repeat(20s, 25s);
                break;
            case 3:
                DoCastVictim(341675);
                events.Repeat(10s, 15s);
                break;
            }
        }

        DoMeleeAttackIfReady();
    }
};


struct npc_crap_synod : public npc_crapopolis_ai_base
{
    npc_crap_synod(Creature* creature) : npc_crapopolis_ai_base(creature) {}

    TaskScheduler scheduler;

    void InitializeAI() override
    {
        me->SetReactState(REACT_PASSIVE);
        me->AddUnitFlag(UNIT_FLAG_IMMUNE_TO_PC);
        me->AddUnitFlag(UNIT_FLAG_NON_ATTACKABLE);
        me->GetMotionMaster()->MovePoint(1, { 999.312012f, -3556.616699f, 12.931227f, 3.894261f });
    }

    void MovementInform(uint32 type, uint32 id) override
    {
        if (type == POINT_MOTION_TYPE && id == 1)
        {
            // Roar
            DoCast(357822);
            scheduler.Schedule(100ms, [this](TaskContext context)
                {
                    me->SetFacingTo(3.894261f);
                });
            scheduler.Schedule(2s, [this](TaskContext context)
            {
                me->SetReactState(REACT_AGGRESSIVE);
                me->RemoveUnitFlag(UNIT_FLAG_IMMUNE_TO_PC);
                me->RemoveUnitFlag(UNIT_FLAG_NON_ATTACKABLE);
            });
        }
    }

    void Reset() override
    {
        events.Reset();
    }

    void JustEngagedWith(Unit* /*who*/) override
    {
        DoCast(274968);
        events.ScheduleEvent(1, 2s, 4s);
        events.ScheduleEvent(2, 12s, 14s);
        events.ScheduleEvent(3, 12s, 24s);
        events.ScheduleEvent(4, 12s, 24s);
    }

    //void JustDied(Unit* /*killer*/) override
    //{
    //}

    void UpdateAI(uint32 diff) override
    {
        scheduler.Update(diff);
        npc_crapopolis_ai_base::UpdateAI(diff);
    }

    void RunAIEvents(uint32 diff) override
    {
        events.Update(diff);

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        if (uint32 l_EventId = events.ExecuteEvent())
        {
            switch (l_EventId)
            {
            case 1:
                DoCastVictim(310392);
                events.Repeat(6s, 7s);
                break;
            case 2:
                DoCastVictim(357110);
                events.Repeat(20s, 25s);
                break;
            case 3:
                DoCastVictim(278222);
                events.Repeat(10s, 15s);
                break;
            case 4:
                DoCastVictim(299150);
                events.Repeat(10s, 15s);
                break;
            }
        }

        DoMeleeAttackIfReady();
    }
};

struct npc_trade_prince_gallywix_700200 : public ScriptedAI
{
    public:
        npc_trade_prince_gallywix_700200(Creature* creature) : ScriptedAI(creature) { }

        bool OnGossipHello(Player* player) override
        {
            ClearGossipMenuFor(player);
            player->PrepareQuestMenu(me->GetGUID());
            SendGossipMenuFor(player, me->GetEntry(), me);
            return true;
        }
        bool OnGossipSelect(Player* player, uint32 menuid, uint32 gossipid) override
        {
            uint32 action = player->PlayerTalkClass->GetGossipOptionAction(gossipid);
            CloseGossipMenuFor(player);
            switch (action)
            {
                case 1:
                    me->RemoveNpcFlag(UNIT_NPC_FLAG_GOSSIP);
                    me->RemoveNpcFlag(UNIT_NPC_FLAG_QUESTGIVER);
                    DoCast(359361); // Banshee Form
                    break;
            }
            return true;
        }
};

void AddSC_Crapopolis()
{
    RegisterCreatureAI(npc_crapopolis_ai_base);
    RegisterCreatureAI(npc_refreshment_vendor_700201);
    RegisterSpellScript(spell_iced_spritzer);
    RegisterCreatureAI(npc_mawsworn_axeguard);
    RegisterCreatureAI(npc_mawsworn_annihilator);
    RegisterCreatureAI(npc_venture_co_war_machine);
    new instance_crapopolis();
    RegisterCreatureAI(npc_mawsworn_defiler);
    RegisterCreatureAI(npc_crap_warden_of_souls);
    RegisterCreatureAI(npc_crap_synod);
    RegisterCreatureAI(npc_trade_prince_gallywix_700200);
}
