/// Copyright 2022-2023 Shadows Embrace
/// All Rights Reserved.
/// You may not share or personally use this code without explicit written permission
/// @author: Artamedes
///
/// @todo - need sniffs
/// Impelement Arcane Eruption
/// Implement Unleashed Destructions

#include "AreaTriggerAI.h"
#include "AzureVaults_SE.h"
#include "ScriptedCreature.h"
#include "SpellMgr.h"
#include "SpellScript.h"
#include "MoveSpline.h"

enum eSpells
{
    Energize = 394082,
    DragonSleeps = 385656,
    OppressiveMiasma = 388773,
    OppressiveMiasmaPeriodic = 388770,
    OppressiveMiasmaSlow = 388777,
    DragonStrike = 384978, ///< Tank Frontal
    BrittleDummy = 386746,  // cast at 75, 50, 25
    BrittleMissle = 386749, //  15 and 35 yards around boss triggers summon - 386752
    AbilityCallOutPlayerDeath = 388842, // unk
    CrystallineRoar = 384699,
    AbilityCallOutCrystalineRoar = 388837,
    ArcaneEruptionDummy = 385075, // summon 3 orbs?
    ArcaneEruptionDummy2 = 385037, // unk
    Cosmetic = 397492, // unk
    ArcaneEruptionDmg = 385078, // dealt after dummy cast

    CracklingVortexAT = 385159, // apply on the Orb npcs
    CracklingVortexFixate = 385245, // unknown, maybe casts on random players?
    CracklingVortex = 385267, // maybe also done by the orbs?

    UnleahedDestruction = 388804,

    // Detonating Crystal
    DetonatingCrystalAura = 386783,
    Fracture = 385331,
};

enum eTalks : uint32
{
    TalkEnage = 0,
    TalkAgony,
    TalkDeath,
};

const Position LastBossCenterPos { -5336.79f, 1064.61f, 157.716f, 0.464406f };

struct boss_se_umbreksul_186738 : public BossAI
{
    public:
        boss_se_umbreksul_186738(Creature* creature) : BossAI(creature, DATA_UMBRELSKUL)
        {
            ApplyAllImmunities(true);
        }

        void Reset() override
        {
            BossAI::Reset();

            me->SetPower(POWER_ENERGY, 50);
            me->SetMaxPower(POWER_ENERGY, 100);
        }

        void EnterEvadeMode(EvadeReason why) override
        {
            BossAI::EnterEvadeMode(why);

            if (instance)
                instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);

            summons.DespawnAll();
            _DespawnAtEvade();
        }

        void JustEngagedWith(Unit* who) override
        {
            BossAI::JustEngagedWith(who);

            if (instance)
                instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);

            scheduler.CancelAll();

            me->RemoveAurasDueToSpell(eSpells::DragonSleeps);
            DoCastSelf(Energize);
            DoCast(eSpells::OppressiveMiasma);

            scheduler.Schedule(7400ms, [this](TaskContext context)
            {
                DoCastVictim(DragonStrike);
                context.Repeat(15300ms);
            });
            scheduler.Schedule(12200ms, [this](TaskContext context)
            {
                DoCastVictim(CrystallineRoar);
                context.Repeat(105600ms);
            });
            scheduler.Schedule(54800ms, [this](TaskContext context)
            {
                DoCastVictim(UnleahedDestruction);
                context.Repeat(114100ms);
            });
        }

        void JustDied(Unit* who) override
        {
            BossAI::JustDied(who);

            if (instance)
                instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);

            Talk(eTalks::TalkDeath);
        }

        void UpdateAI(uint32 diff) override
        {
            if (!UpdateVictim())
                return;

            if (!me->HasUnitState(UNIT_STATE_CASTING) && me->GetPower(POWER_ENERGY) == 100)
            {
                me->SetPower(POWER_ENERGY, 0);
                DoCastSelf(eSpells::ArcaneEruptionDummy2);
                return;
            }

            if (!me->HasUnitState(UNIT_STATE_CASTING))
                scheduler.Update(diff);

            DoMeleeAttackIfReady();
        }

        void DamageTaken(Unit* /*attacker*/, uint32& damage, DamageEffectType /*damageType*/, SpellInfo const* /*spellInfo*/) override
        {
            if (!_brittle75 && me->HealthBelowPctDamaged(75, damage))
            {
                _brittle75 = true;
                DoCast(eSpells::BrittleDummy);
            }
            else if (!_brittle50 && me->HealthBelowPctDamaged(50, damage))
            {
                _brittle50 = true;
                DoCast(eSpells::BrittleDummy);
            }
            else if (!_brittle25 && me->HealthBelowPctDamaged(25, damage))
            {
                _brittle25 = true;
                DoCast(eSpells::BrittleDummy);
            }

        }

        void OnUnitRelocation(Unit* who) override
        {
            if (_intro)
                return;

            if (!who->IsPlayer())
                return;

            if (who->movespline && !who->movespline->Finalized())
                return;

            if (who->GetDistance(me) <= 30.0f)
            {
                _intro = true;
                me->RemoveAurasDueToSpell(eSpells::DragonSleeps);
                Talk(eTalks::TalkEnage);
            }
        }

    private:
        bool _brittle75 = false;
        bool _brittle50 = false;
        bool _brittle25 = false;
        bool _intro     = false;
};

struct at_se_oppressive_miasma_26647 : public AreaTriggerAI
{
    public:
        at_se_oppressive_miasma_26647(AreaTrigger* at) : AreaTriggerAI(at) { }

        void OnUnitEnter(Unit* who) override
        {
            if (auto caster = at->GetCaster())
                caster->CastSpell(who, eSpells::OppressiveMiasmaPeriodic, true);
        }

        void OnUnitExit(Unit* who) override
        {
            who->RemoveAurasDueToSpell(eSpells::OppressiveMiasmaPeriodic);
        }
};

/// ID - 388770 Oppressive Miasma
class spell_oppressive_miasma_388770 : public AuraScript
{
    PrepareAuraScript(spell_oppressive_miasma_388770);

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
        if (auto target = GetTarget())
            if (auto caster = GetCaster())
                if (target->isMoving())
                    caster->CastSpell(target, eSpells::OppressiveMiasmaSlow, true);
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_oppressive_miasma_388770::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
    }
};

/// ID - 394082 Energize
class spell_energize_394082 : public AuraScript
{
    PrepareAuraScript(spell_energize_394082);

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
        if (auto caster = GetCaster())
            caster->EnergizeBySpell(caster, GetSpellInfo(), 2, POWER_ENERGY);
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_energize_394082::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
    }
};
/// ID - 385037 Arcane Eruption
class spell_arcane_eruption_385037 : public SpellScript
{
    PrepareSpellScript(spell_arcane_eruption_385037);

    void HandleDummy(SpellEffIndex /*eff*/)
    {
        // @todo: need to get creature_templates to finish this boss.
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_arcane_eruption_385037::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

/// ID - 386746 Brittle
class spell_brittle_386746 : public SpellScript
{
    PrepareSpellScript(spell_brittle_386746);

    void HandleDummy(SpellEffIndex /*eff*/)
    {
        auto caster = GetCaster();
        if (!caster)
            return;

        std::vector<Position> positions;

        while (positions.size() < 5)
        {
            Position pos = caster->GetPosition();
            caster->MovePositionToFirstCollision(pos, frand(5.0f, 35.0f), frand(0.0f, 2.0f * float(M_PI)));

            // ensure positions isn't outside of bosses radius
            if (LastBossCenterPos.GetExactDist(pos) > 40.0f)
                continue;

            // make sure z position isn't too high either
            if (pos.m_positionZ > 157.8f)
                continue;

            positions.push_back(pos);
        }

        for (auto const& pos : positions)
        {
            caster->CastSpell(pos, eSpells::BrittleMissle, true);
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_brittle_386746::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

struct npc_se_detonating_crystal_195138 : public ScriptedAI
{
    public:
        npc_se_detonating_crystal_195138(Creature* creature) : ScriptedAI(creature)
        {
            ApplyAllImmunities(true);
            me->SetReactState(REACT_PASSIVE);
            me->SetDisableGravity(true);
            me->SetControlled(true, UnitState::UNIT_STATE_ROOT);
        }

        void Reset() override
        {
            DoCastSelf(DetonatingCrystalAura);

            scheduler.Schedule(50ms, [this](TaskContext /*context*/)
            {
                DoCastSelf(Fracture);
            });
        }

        void UpdateAI(uint32 diff) override
        {
            scheduler.Update(diff);
        }

        void OnSpellCast(SpellInfo const* spellInfo) override
        {
            if (spellInfo->Id == Fracture)
                me->DespawnOrUnsummon();
        }
};

void AddSC_Umbrelskul_SE()
{
    RegisterAzureVaultsCreatureAI(boss_se_umbreksul_186738);
    RegisterAzureVaultsCreatureAI(npc_se_detonating_crystal_195138);

    RegisterAreaTriggerAI(at_se_oppressive_miasma_26647);

    RegisterSpellScript(spell_oppressive_miasma_388770);
    RegisterSpellScript(spell_energize_394082);
    RegisterSpellScript(spell_arcane_eruption_385037);
    RegisterSpellScript(spell_brittle_386746);
}
