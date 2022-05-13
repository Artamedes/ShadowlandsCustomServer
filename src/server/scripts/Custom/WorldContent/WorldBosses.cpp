#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "World.h"
#include "ChatPackets.h"

enum WorldBosses
{
    FrozenInTime = 211187,
};

// 700150 - npc_nightmare_of_gul_dan_700150
struct npc_nightmare_of_gul_dan_700150 : public ScriptedAI
{
public:
    npc_nightmare_of_gul_dan_700150(Creature* creature) : ScriptedAI(creature) { ApplyAllImmunities(true); }

    enum GulDan
    {
        TalkAggro = 0,
        TalkDodge,
        TalkWeak,
        TalkActive,

        EventAnnihilationBlast = 1,
        EventHandOfDestruction,
        EventDarkDestruction,
        EventMeteor,
        EventThermalStrike,
        EventWaveOfHysteria,

        AnnihilationBlast = 246666,
        HandOfDescrution = 361789, // pull all players to me
        DarkDestruction = 341865,
        Meteor = 153561,
        ThermalStrike = 139894,
        DeathGrip = 191650,
        WaveOfHysteria = 314880,
    };

    void InitializeAI() override
    {
        me->SetReactState(REACT_PASSIVE);
        me->SetUnitFlag(UnitFlags::UNIT_FLAG_NON_ATTACKABLE);
        me->setActive(true);
        me->AddAura(FrozenInTime, me);
        me->SetRespawnCompatibilityMode(true);
    }

    void JustEngagedWith(Unit* who) override
    {
        if (!firstEngage && who)
        {
            firstEngage = true;
            WorldPackets::Chat::Chat packet;
            packet.Initialize(CHAT_MSG_MONSTER_EMOTE, LANG_UNIVERSAL, me, nullptr, "Nightmare of Gul'dan has been engaged by " + who->GetName());
            sWorld->SendGlobalMessage(packet.Write());
        }

        Talk(TalkAggro);

        // Start events
        events.ScheduleEvent(EventAnnihilationBlast, 5s, 20s);
        events.ScheduleEvent(EventHandOfDestruction, 20s, 20s);
        events.ScheduleEvent(EventDarkDestruction, 5s, 20s);
        events.ScheduleEvent(EventMeteor, 5s, 20s);
        events.ScheduleEvent(EventThermalStrike, 5s, 20s);
        events.ScheduleEvent(EventWaveOfHysteria, 5s, 20s);
    }

    void UpdateAI(uint32 diff) override
    {
        scheduler.Update(diff);

        if (!UpdateVictim())
            return;

        events.Update(diff);

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        if (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EventAnnihilationBlast:
                    DoCastVictim(AnnihilationBlast, true);
                    events.Repeat(20s);
                    break;
                case EventHandOfDestruction:
                {
                    std::list<Unit*> targets;
                    SelectTargetList(targets, 50, SelectTargetMethod::Random, 0, 100.0f, true, true);
                    for (auto target : targets)
                    {
                        target->CastSpell(me, DeathGrip, true);
                    }

                    DoCastAOE(HandOfDescrution, true);
                    events.Repeat(60s);
                    break;
                }
                case EventDarkDestruction:
                    DoCastAOE(DarkDestruction, true);
                    events.Repeat(20s);
                    break;
                case EventMeteor:
                    DoCastAOE(Meteor, true);
                    events.Repeat(20s);
                    break;
                case EventThermalStrike:
                    DoCastVictim(ThermalStrike, true);
                    events.Repeat(20s);
                    break;
                case EventWaveOfHysteria:
                    DoCastVictim(WaveOfHysteria, true);
                    events.Repeat(40s, 60s);
                    break;
            }

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;
        }

        DoMeleeAttackIfReady();
    }

    bool intro = false;
    bool firstEngage = false;

    void MoveInLineOfSight(Unit* who) override
    {
        ScriptedAI::MoveInLineOfSight(who);

        if (intro)
            return;

        if (who->IsPlayer() && who->GetDistance2d(me) <= 65.0f)
        {
            intro = true;

            WorldPackets::Chat::Chat packet;
            packet.Initialize(CHAT_MSG_MONSTER_EMOTE, LANG_UNIVERSAL, me, nullptr, "Nightmare of Gul'dan will be active in 60 seconds. Prepare for battle at \"A Dark Place!\"");
            sWorld->SendGlobalMessage(packet.Write());

            Seconds secs = 60s;

            if (who->IsPlayer() && who->ToPlayer()->IsGameMaster())
                secs = 1s;

            scheduler.Schedule(60s, [this](TaskContext context)
            {
                me->RemoveAurasDueToSpell(FrozenInTime);
                me->RemoveUnitFlag(UnitFlags::UNIT_FLAG_NON_ATTACKABLE);
                me->SetReactState(REACT_AGGRESSIVE);
                Talk(TalkActive);
            });
        }
    }

    void EnterEvadeMode(EvadeReason why) override
    {
        events.Reset();
        ScriptedAI::EnterEvadeMode(why);
        me->DespawnOrUnsummon(0s, 5s);
        Talk(TalkWeak);
    }

    EventMap events;
    TaskScheduler scheduler;
};


void AddSC_WorldBosses()
{
    RegisterCreatureAI(npc_nightmare_of_gul_dan_700150);
}
// UPDATE creature_template set ScriptName = 'npc_nightmare_of_gul_dan_700150' WHERE entry = 700150;
