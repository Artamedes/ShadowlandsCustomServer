/// Copyright 2022-2023 Shadows Embrace
/// All Rights Reserved.
/// You may not share or personally use this code without explicit written permission
/// @author: Artamedes

#include "AreaTriggerAI.h"
#include "AzureVaults_SE.h"
#include "ScriptedCreature.h"
#include "SpellMgr.h"
#include "SpellScript.h"

enum eTalks
{
    TalkLeymorAwakens = 0,
};

enum eSpells : uint32
{
    ArcaneEruption  = 375749,
    LeyLineSprouts  = 374364,
    InfusedStrike   = 374789,
    EruptionFissure = 386660,
    ExplosiveBrand  = 374567,
    ConsumingStomp  = 374720,

    LeyLineSproutsMissle = 374362,
};

const Position LeymorHomePosition = { -5129.399902f, 1253.300049f, 555.588013f, 0.716251f };

struct boss_se_leymor_186644 : public BossAI
{
    public:
        boss_se_leymor_186644(Creature* creature) : BossAI(creature, DATA_LEYMOR)
        {
            ApplyAllImmunities(true);
        }

        void DoAction(int32 actionId) override
        {
            if (actionId == AVDFGlobalActions::ACTION_ARCANE_TENDERS_DEAD)
            {
                Talk(eTalks::TalkLeymorAwakens);
            }
        }

        void EnterEvadeMode(EvadeReason why) override
        {
            BossAI::EnterEvadeMode(why);

            if (instance)
                instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);

            _DespawnAtEvade();
        }

        void JustEngagedWith(Unit* who) override
        {
            BossAI::JustEngagedWith(who);

            if (instance)
                instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);

            scheduler.CancelAll();

            scheduler.Schedule(3600ms, [this](TaskContext context)
            {
                DoCast(eSpells::LeyLineSprouts);
                context.Repeat(48700ms);
            });
            scheduler.Schedule(10600ms, [this](TaskContext context)
            {
                DoCastVictim(eSpells::InfusedStrike);
                context.Repeat(48700ms);
            });
            scheduler.Schedule(20300ms, [this](TaskContext context)
            {
                DoCast(eSpells::EruptionFissure);
                context.Repeat(48700ms);
            });
            scheduler.Schedule(30100ms, [this](TaskContext context)
            {
                DoCast(eSpells::ExplosiveBrand);
                context.Repeat(48700ms);
            });
            scheduler.Schedule(45800ms, [this](TaskContext context)
            {
                DoCast(eSpells::ConsumingStomp);
                context.Repeat(48700ms);
            });
        }

        void JustDied(Unit* who) override
        {
            BossAI::JustDied(who);

            if (instance)
                instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
        }

        void UpdateAI(uint32 diff) override
        {
            if (!UpdateVictim())
                return;

            if (!me->HasUnitState(UNIT_STATE_CASTING))
                scheduler.Update(diff);

            DoMeleeAttackIfReady();
        }
};

/// ID - 374364 Ley-Line Sprouts
class spell_leyline_sprouts_374364 : public SpellScript
{
    PrepareSpellScript(spell_leyline_sprouts_374364);

    void HandleDummy(SpellEffIndex /*eff*/)
    {
        if (auto caster = GetCaster())
        {
            // Define radius and minimum distance between positions
            const float radius = 25.0f;
            const float minDistance = 6.0f;

            // Generate positions
            std::vector<Position> positions;
            while (positions.size() < 15)
            {
                // Generate a random position within the radius
                Position pos;
                caster->GetRandomPoint(LeymorHomePosition, radius, pos.m_positionX, pos.m_positionY, pos.m_positionZ);
                // Check if the new position is at least minDistance away from existing positions
                bool isValid = true;
                for (const auto& existingPos : positions)
                {
                    if (pos.GetExactDist(existingPos) < minDistance)
                    {
                        isValid = false;
                        break;
                    }
                }

                // Add the new position if it is valid
                if (isValid)
                    positions.push_back(pos);
            }

            // The positions vector now contains 8 valid positions within the radius
            // Lets now cast the spell

            for (auto const& pos : positions)
            {
                caster->CastSpell(pos, eSpells::LeyLineSproutsMissle, true);
            }
        }

    }

    void Register() override
    {
        OnEffectHit += SpellEffectFn(spell_leyline_sprouts_374364::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};


void AddSC_BossLeymor_SE()
{
    RegisterAzureVaultsCreatureAI(boss_se_leymor_186644);
    RegisterSpellScript(spell_leyline_sprouts_374364);

    sSpellMgr->ApplySpellFix({ eSpells::LeyLineSproutsMissle }, [](SpellInfo* spellInfo)
    {
        sSpellMgr->ApplySpellEffectFix(spellInfo, EFFECT_0, [](SpellEffectInfo* effectInfo)
        {
            effectInfo->TargetA = SpellImplicitTargetInfo(TARGET_DEST_DEST);
            effectInfo->RadiusEntry = sSpellRadiusStore.LookupEntry(EFFECT_RADIUS_45_YARDS);
            effectInfo->MaxRadiusEntry = sSpellRadiusStore.LookupEntry(EFFECT_RADIUS_45_YARDS);
        });
    });
}
