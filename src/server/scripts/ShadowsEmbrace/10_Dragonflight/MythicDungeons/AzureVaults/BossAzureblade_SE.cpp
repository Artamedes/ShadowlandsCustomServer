/// Copyright 2022-2023 Shadows Embrace
/// All Rights Reserved.
/// You may not share or personally use this code without explicit written permission
/// @author: Artamedes

#include "AreaTriggerAI.h"
#include "AzureVaults_SE.h"
#include "ScriptedCreature.h"
#include "SpellMgr.h"
#include "SpellScript.h"
#include "G3DPosition.hpp"

enum eSpells : uint32
{
    // OOC stuff
    DraconicIllusionRune04BossVisual = 377039,
    RPSceneAzurebladeApproachConvo   = 389382,
    ArcaneMana                       = 389248,

    // Combat actions
    SummonDraconicImage = 384223,
    ArcaneCleave        = 372222,
    AncientOrbVisual    = 385781, // should just be @caster
    AncientOrb          = 385578,
    AncientOrbDmg       = 385579,
    DraconicRitual      = 378734, // unk

    // phase
    OverwhelmingEnergy           = 384132,
    SummonIllusionDraconicRitual = 378742,
    AncientOrbFragment = 390461,
    AncientOrbFragmentDmg = 390462,

    AzurebladePlayerCheck = 397148, // some kind of anti wipe mechanism
};

enum eDatas
{
    DataAncientOrb = 1,
};

const Position RitualPos1 = { -5327.18f, 803.722f, 427.996f };
const Position RitualPos2 = { -5346.86f, 779.741f, 427.996f };
const Position RitualPos3 = { -5346.89f, 803.51f , 427.996f };
const Position RitualPos4 = { -5327.18f, 803.722f, 427.996f };

const Position AncientOrbPosSet1_1 = { -5338.006f, 791.6868f, 427.97284f, 2.600440263748168945f };
const Position AncientOrbPosSet1_2 = { -5337.4326f, 790.8677f, 427.97284f, 3.647784233093261718f };
const Position AncientOrbPosSet1_3 = { -5336.436f, 790.95483f, 427.97284f,  4.694810867309570312f };
const Position AncientOrbPosSet1_4 = { -5336.0137f, 791.86115f, 427.97284f, 5.742033004760742187f };
const Position AncientOrbPosSet1_5 = { -5336.587f, 792.6803f, 427.97284f, 0.506191432476043701f };
const Position AncientOrbPosSet1_6 = { -5337.5835f, 792.59314f, 427.97284f,  1.553217887878417968f};

const Position AncientOrbPosSet2_1 = { -5337.971f, 792.0496f, 427.97284f, 3.228870630264282226f };
const Position AncientOrbPosSet2_2 = { -5337.729f, 791.07935f, 427.97284f, 4.27584695816040039f };
const Position AncientOrbPosSet2_3 = { -5336.768f, 790.8037f, 427.97284f, 5.323379993438720703f };
const Position AncientOrbPosSet2_4 = { -5336.0483f, 791.49835f, 427.97284f, 0.087277710437774658f };
const Position AncientOrbPosSet2_5 = { -5336.2905f, 792.4686f, 427.97284f, 1.134253978729248046f };
const Position AncientOrbPosSet2_6 = { -5337.2515f, 792.74426f, 427.97284f, 2.18178725242614746f };



struct boss_se_azureblade_186739 : public BossAI
{
    public:
        boss_se_azureblade_186739(Creature* creature) : BossAI(creature, DATA_AZUREBLADE)
        {
            ApplyAllImmunities(true);
        }

        void Reset() override
        {
            BossAI::Reset();

            DoCastSelf(DraconicIllusionRune04BossVisual);

            me->SetPower(Powers::POWER_ENERGY, 50);
            me->SetMaxPower(Powers::POWER_ENERGY, 100);
        }

        void EnterEvadeMode(EvadeReason why) override
        {
            BossAI::EnterEvadeMode(why);

            if (instance)
                instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);

            _DespawnAtEvade();
            summons.DespawnAll();
        }

        void JustEngagedWith(Unit* who) override
        {
            BossAI::JustEngagedWith(who);

            if (instance)
                instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);

            scheduler.CancelAll();

            me->RemoveAurasDueToSpell(ArcaneMana);
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

            if (!me->HasUnitState(UNIT_STATE_CASTING) && !_phasing && me->GetPower(Powers::POWER_ENERGY) >= 100)
            {
                _phasing = true;
            }

            if (!me->HasUnitState(UNIT_STATE_CASTING))
                scheduler.Update(diff);

            DoMeleeAttackIfReady();
        }

        void OnUnitRelocation(Unit* who) override
        {
            if (_intro)
                return;

            if (!who->IsPlayer())
                return;

            if (who->GetDistance(me) >= 66.0f)
                return;

            // ensure boss state was not started - only checked once
            if (instance->GetBossState(DATA_AZUREBLADE) != NOT_STARTED)
            {
                _intro = true;
                return;
            }

            _intro = true;
            DoCastSelf(RPSceneAzurebladeApproachConvo);
        }

        void SetData(uint32 type, uint32 /*data*/) override
        {
            if (type == DataAncientOrb)
            {
                _ancinetOrbSwitch = !_ancinetOrbSwitch;
            }
        }

        uint32 GetData(uint32 type) const override
        {
            if (type == DataAncientOrb)
            {
                return _ancinetOrbSwitch ? 1 : 0;
            }

            return 0;
        }

    private:
        bool _phasing = false;
        bool _intro = false;
        bool _ancinetOrbSwitch = false;
};


struct at_se_ancient_orb_26351 : public AreaTriggerAI
{
    public:
        at_se_ancient_orb_26351(AreaTrigger* at) : AreaTriggerAI(at) { }

        bool InitSplines(std::vector<G3D::Vector3>& splinePoints, uint32& /*timeToTarget*/) override
        {
            // lets get a point every 3 yards for a total of 15 times
            Position pos = at->GetPosition();
            splinePoints.push_back(PositionToVector3(pos));

            for (int i = 0; i < 15; ++i)
            {
                pos = at->GetPosition();
                at->MovePosition(pos, 5.0f * i, 0.0f);
                splinePoints.push_back(PositionToVector3(pos));
            }
            
            return true;
        }
        
        void OnUnitEnter(Unit* who) override
        {
            if (auto caster = at->GetCaster())
                if (who->IsPlayer())
                    caster->CastSpell(who, AncientOrbDmg, true);
        }
};

/// ID - 390384 Ancient Orb Fragment
class spell_ancient_orb_fragment_390384 : public SpellScript
{
    PrepareSpellScript(spell_ancient_orb_fragment_390384);

    void HandleDummy(SpellEffIndex /*eff*/)
    {
        if (auto caster = GetCaster())
        {
            bool switchOrb = false;

            if (auto creature = caster->ToCreature())
            {
                if (auto ai = creature->GetAI())
                {
                    switchOrb = ai->GetData(DataAncientOrb) == 1;
                    ai->SetData(DataAncientOrb, 1);
                }
            }

            if (switchOrb)
            {
                caster->CastSpell(AncientOrbPosSet1_1, eSpells::AncientOrbFragment, true);
                caster->CastSpell(AncientOrbPosSet1_2, eSpells::AncientOrbFragment, true);
                caster->CastSpell(AncientOrbPosSet1_3, eSpells::AncientOrbFragment, true);
                caster->CastSpell(AncientOrbPosSet1_4, eSpells::AncientOrbFragment, true);
                caster->CastSpell(AncientOrbPosSet1_5, eSpells::AncientOrbFragment, true);
                caster->CastSpell(AncientOrbPosSet1_6, eSpells::AncientOrbFragment, true);
            }
            else
            {
                caster->CastSpell(AncientOrbPosSet2_1, eSpells::AncientOrbFragment, true);
                caster->CastSpell(AncientOrbPosSet2_2, eSpells::AncientOrbFragment, true);
                caster->CastSpell(AncientOrbPosSet2_3, eSpells::AncientOrbFragment, true);
                caster->CastSpell(AncientOrbPosSet2_4, eSpells::AncientOrbFragment, true);
                caster->CastSpell(AncientOrbPosSet2_5, eSpells::AncientOrbFragment, true);
                caster->CastSpell(AncientOrbPosSet2_6, eSpells::AncientOrbFragment, true);
            }
        }
    }

    void Register() override
    {
        OnEffectHit += SpellEffectFn(spell_ancient_orb_fragment_390384::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};


struct at_se_ancient_orb_fragment_26773 : public AreaTriggerAI
{
    public:
        at_se_ancient_orb_fragment_26773(AreaTrigger* at) : AreaTriggerAI(at) { }

        bool InitSplines(std::vector<G3D::Vector3>& splinePoints, uint32& /*timeToTarget*/) override
        {
            // lets get a point every 3 yards for a total of 15 times
            Position pos = at->GetPosition();
            splinePoints.push_back(PositionToVector3(pos));

            for (int i = 0; i < 15; ++i)
            {
                pos = at->GetPosition();
                at->MovePosition(pos, 5.0f * i, 0.0f);
                splinePoints.push_back(PositionToVector3(pos));
            }
            
            return true;
        }
        
        void OnUnitEnter(Unit* who) override
        {
            if (auto caster = at->GetCaster())
                if (who->IsPlayer())
                    caster->CastSpell(who, eSpells::AncientOrbFragmentDmg, true);
        }
};

void AddSC_BossAzureBlade_SE()
{
    RegisterAzureVaultsCreatureAI(boss_se_azureblade_186739);

    RegisterAreaTriggerAI(at_se_ancient_orb_26351);
    RegisterAreaTriggerAI(at_se_ancient_orb_fragment_26773);

    RegisterSpellScript(spell_ancient_orb_fragment_390384);
}
