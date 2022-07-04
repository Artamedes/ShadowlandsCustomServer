#include "halls_of_attonement.h"

enum eTalks
{
    TalkIntro           = 0,
    TalkAggro           = 1,
    TalkTelekenticToss  = 4,
    TalkRitualOfWoe1    = 8,
    TalkRitualOfWoe2    = 9,
    TalkDeath           = 11,
    TalkStigmaOfPride   = 12, ///< TODO
};

enum eSpells
{
    TelekineticToss       = 323142,
    StigmaOfPride         = 323437,
    DoorOfShadows         = 329104, /// (DstLocation)Location: X: -2209.73 Y : 5700.49 Z : 4223.37
    TelekineticOnslaught  = 329113,
    TelekineticReplusion  = 323129,
    RitualOfWoe           = 323392, /// (DstLocation) Location: X: -2209.73 Y: 5700.49 Z: 4223.37 hit entry 165737
    RitualOfWoeChannel    = 323393,
    RitualOfWoeTrigger    = 335345, // should trigger aoe dmg 323414
    RitualOfWoeDmg        = 335338, // probably the line spell
    RitualOfWoeCheckSpell = 323398, // blizz uses this i believe as it has TARGET_UNIT_LINE_CASTER_TO_DEST
};

const Position DoorOfShadowsLocation = { -2209.73f, 5700.49f, 4223.37f };

// 164218
struct boss_lord_chamberlain : public BossAI
{
public:
    boss_lord_chamberlain(Creature* creature) : BossAI(creature, HallsOfAttonement::BossLordChamberlain)
    {
        ApplyAllImmunities(true);
    }

    void JustEngagedWith(Unit* who) override
    {
        _JustEngagedWith(who);

        if (instance)
            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);

        Talk(TalkIntro);

        scheduler.Schedule(5s, [this](TaskContext context)
        {
            DoCastVictim(StigmaOfPride);
            Talk(TalkStigmaOfPride);
            context.Repeat(25s);
        });
    }

    void EnterEvadeMode(EvadeReason why) override
    {
        _EnterEvadeMode(why);
        _DespawnAtEvade(10s);

        if (instance)
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
    }

    void JustDied(Unit* who) override
    {
        _JustDied();

        if (instance)
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);

        Talk(TalkDeath);
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        scheduler.Update(diff);

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        DoMeleeAttackIfReady();
    }
};

// 165737 - npc_sinstone_statue_165737
struct npc_sinstone_statue_165737 : public ScriptedAI
{
public:
    npc_sinstone_statue_165737(Creature* creature) : ScriptedAI(creature) { }
};

// 19700
struct areatrigger_telekinetic_collision : public AreaTriggerAI
{
public:
    areatrigger_telekinetic_collision(AreaTrigger* at) : AreaTriggerAI(at) { }

    void OnUnitEnter(Unit* who) override
    {
        if (auto caster = at->GetCaster())
            if (caster->IsValidAttackTarget(who))
                caster->CastSpell(who, 323126, true);
    }
};

void AddSC_boss_lord_chamberlain()
{
    RegisterCreatureAI(boss_lord_chamberlain);
    RegisterCreatureAI(npc_sinstone_statue_165737);
}
