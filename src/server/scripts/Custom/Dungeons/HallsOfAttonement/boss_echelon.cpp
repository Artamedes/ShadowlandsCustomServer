#include "halls_of_attonement.h"

enum eTexts
{
    TalkAggro                       = 0,
    TalkBloodTorrent                = 1,
    TalkObeyMe                      = 2,
    TalkYourFaceIsCarved            = 3,
    TalkStoneShatteringLeapAlert    = 4,
    TalkStoneShatteringLeap         = 5,
    TalkFailureIsComplete           = 6,
    TalkTheGroundBleeds             = 7,
    TalkDeath                       = 8,
    TalkToMySide                    = 9,
    TalkYouNeverStoodAChance        = 10,
    TalkObeyMeMinions               = 11,
};

enum eSpells
{
    GrandEntrance      = 330708, // Need to script jump charge id 450
    AnchorHere         = 45313,
    BloodTorrent       = 326389,
    StoneCall          = 319733,
    CurseOfStone       = 328206,
    CurseOfStoneMissle = 327411,
    StoneShatteringLeap = 319941,
    StoneShatteringLeapDummy = 319962, // must cast 344874 shattered on dummy script.
    Shattered           = 344874,
};

// 164185
struct boss_echelon : public BossAI
{
public:
    boss_echelon(Creature* creature) : BossAI(creature, HallsOfAttonement::BossEchelon) { }

    void JustEngagedWith(Unit* who) override
    {
        _JustEngagedWith(who);

        if (instance)
            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);

        scheduler.Schedule(10s, [this](TaskContext context)
        {
            if (auto target = SelectTarget(SelectTargetMethod::Random, 0, 40.0f, true))
                DoCast(target, BloodTorrent);
            Talk(RAND(TalkBloodTorrent, TalkTheGroundBleeds));
            context.Repeat(10s);
        });

        Talk(TalkAggro);
    }

    void EnterEvadeMode(EvadeReason why) override
    {
        _EnterEvadeMode(why);
        _DespawnAtEvade(10s);

        if (instance)
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);

        Talk(TalkYouNeverStoodAChance);
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

// 19355
struct at_blood_torrent : public AreaTriggerAI
{
public:
    at_blood_torrent(AreaTrigger* at) : AreaTriggerAI(at)
    {
        at->SetPeriodicProcTimer(100);
    }

    enum eBloodTorrent
    {
        BloodTorrentAura = 319703,
    };

    void OnUnitEnter(Unit* who) override
    {
        if (auto caster = at->GetCaster())
            if (caster->IsValidAttackTarget(who))
                caster->CastSpell(who, BloodTorrentAura, true);
    }

    void OnUnitExit(Unit* who) override
    {
        if (auto caster = at->GetCaster())
            who->RemoveAurasDueToSpell(BloodTorrentAura, caster->GetGUID());
    }

    void OnPeriodicProc() override
    {
        if (auto caster = at->GetCaster())
        {
            for (auto guid : at->GetInsideUnits())
            {
                if (auto unit = ObjectAccessor::GetUnit(*at, guid))
                {
                    if (unit->IsValidAttackTarget(caster))
                        if (!unit->HasAura(BloodTorrentAura, caster->GetGUID()))
                            caster->CastSpell(unit, BloodTorrentAura, true);
                }
            }
        }
    }
};

void AddSC_boss_echelon()
{
    RegisterCreatureAI(boss_echelon);
    RegisterAreaTriggerAI(at_blood_torrent);
}
