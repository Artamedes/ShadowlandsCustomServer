/// Copyright 2022-2023 Shadows Embrace
/// All Rights Reserved.
/// You may not share or personally use this code without explicit written permission
/// @author: Artamedes

#include "AreaTriggerAI.h"
#include "AzureVaults_SE.h"
#include "ScriptedCreature.h"
#include "SpellMgr.h"
#include "SpellScript.h"

enum eSpells : uint32
{
    RPSceneTelashGreywingApproachConvo = 389379,
    IcePowerDNTPeriodic                = 389453, ///< Probably give him power
    IcePowerDNTAura                    = 389454,
    FrostBombDummyCast                 = 386781, ///< Needs a script
    FrostBombDummyAura                 = 386881, ///< Apply to all players from above and drop the areatrigger.
    FrostBombDMG                       = 386910, ///< On aura expire this damage is dealt.
    FrostBombDMGToFriends              = 390614, ///< This damage is dealt to friends.

    FrozenGround                       = 387149, // creates the AT
    FrozenGroundEffect                 = 387150, ///< Frozen Ground dmg

    VaultRuneAT                        = 388072, ///< Vault rune for dmg reduction

    IcyDevastator                      = 387151, ///< Channel on random player.

    AbsoluteZero                       = 387928,
    JumpToCenterDNT                    = 387981,
    ActivateVaultRuneDNT               = 390209,
    GlacialShield                      = 388084,
    AbsoluteZeroDmg                    = 388008,
    JumpToPlatformDNT                  = 388082,
};

enum eTalks : int32
{
    TalkAggro = 0,               ///< OK
    TalkFreeze,                  ///< OK
    TalkHerSecretsWillBeMine,    ///< OK
    TalkNowYouWillPlay,          ///< OK
    TalkCastingAbsoluteZero,     ///< OK
    TalkDeath,                   ///< OK
};

enum eActions : uint32
{
    ActionJumpToCenter   = 1,
    ActionJumpToPlatform = 2,
};

enum eDatas : uint32
{
    DataPlatformNumberToJumpTo = 1,
};

const Position JumpToCenterPosition = { -5336.8003f, 1066.6493f, 344.32678f };
const Position JumpToPlatformPosition_1 = { -5350.0835f, 1089.8976f, 340.5709f };
const Position JumpToPlatformPosition_2 = { -5309.79f, 1066.87f, 340.498f };
const Position JumpToPlatformPosition_3 = { -5350.76f, 1042.81f, 340.438f, 4.16653f };

struct boss_se_telash_greywing_186737 : public BossAI
{
    public:
        boss_se_telash_greywing_186737(Creature* creature) : BossAI(creature, DATA_TELASH_GREYWING)
        {
            ApplyAllImmunities(true);
        }
        
        void Reset() override
        {
            DoCastSelf(IcePowerDNTAura);
            DoCastSelf(IcePowerDNTPeriodic);

            me->SetPower(Powers::POWER_ENERGY, 60);
            me->SetMaxPower(Powers::POWER_ENERGY, 100);
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
            _textScheduler.CancelAll();
            _phasingScheduler.CancelAll();

            scheduler.Schedule(3500ms, [this](TaskContext context)
            {
                DoCast(FrostBombDummyCast);

                _textScheduler.Schedule(189ms, [this](TaskContext /*context*/)
                {
                    Talk(eTalks::TalkFreeze);
                });

                context.Repeat(15800ms);
            });
            scheduler.Schedule(14500ms, [this](TaskContext context)
            {
                Talk(eTalks::TalkHerSecretsWillBeMine);
                DoCastRandom(IcyDevastator, 40.0f);
                context.Repeat(23100ms);
            });

            Talk(eTalks::TalkAggro);
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

            _phasingScheduler.Update(diff);

            if (me->GetPower(POWER_ENERGY) == 100 && !_phasing && !me->HasUnitState(UNIT_STATE_CASTING))
            {
                _phasing = true;

                me->RemoveAurasDueToSpell(IcePowerDNTPeriodic);

                // Do his phase
                Talk(eTalks::TalkNowYouWillPlay);

              ///  me->SetReactState(REACT_PASSIVE); // lets stop following
                me->GetMotionMaster()->Clear();

                DoCastSelf(eSpells::AbsoluteZero);
                me->CastSpell(JumpToCenterPosition, eSpells::JumpToCenterDNT);
                DoCastSelf(eSpells::ActivateVaultRuneDNT);
                DoCastSelf(eSpells::GlacialShield);
            }

            if (_phasing)
                return;

            _textScheduler.Update(diff);
            if (!me->HasUnitState(UNIT_STATE_CASTING))
                scheduler.Update(diff);

            DoMeleeAttackIfReady();
        }

        void DoAction(int32 actionId) override
        {
            if (actionId == eActions::ActionJumpToCenter)
            {
                // ok start casting icy thing
                DoCast(AbsoluteZeroDmg);
                Talk(eTalks::TalkCastingAbsoluteZero);
            }
            else if (actionId == eActions::ActionJumpToPlatform)
            {
                if (instance)
                    instance->SetData(ACTION_DISABLE_VAULT_RUNE, 1);

                _phasingScheduler.Schedule(1000ms, [this](TaskContext /*context*/)
                {
                //    me->SetReactState(REACT_AGGRESSIVE);
                    UpdateVictim();
                    if (auto vicitm = me->GetVictim())
                        me->GetMotionMaster()->MoveChase(vicitm);
                    DoCastSelf(IcePowerDNTPeriodic);
                    me->RemoveAurasDueToSpell(eSpells::GlacialShield);
                    _phasing = false;
                });
            }
            else if (actionId == AVDFGlobalActions::ACTION_ARCANE_TENDERS_DEAD)
            {
                Talk(eTalks::TalkAggro);
            }
        }

        void OnSpellCast(SpellInfo const* spellInfo) override
        {
            if (spellInfo->Id == eSpells::AbsoluteZeroDmg)
            {
                _phasingScheduler.Schedule(300ms, [this](TaskContext /*context*/)
                {
                    if (positionToJumpTo == 0)
                        me->CastSpell(JumpToPlatformPosition_1, eSpells::JumpToPlatformDNT);
                    else if (positionToJumpTo == 1)
                        me->CastSpell(JumpToPlatformPosition_2, eSpells::JumpToPlatformDNT);
                    else if (positionToJumpTo == 2)
                        me->CastSpell(JumpToPlatformPosition_3, eSpells::JumpToPlatformDNT);

                    positionToJumpTo++;
                    if (positionToJumpTo > 2)
                        positionToJumpTo = 0;
                });
            }
        }

        bool CanCastSpellWhileMoving(SpellInfo const* info) const override
        {
            if (info->Id == IcyDevastator)
                return true;

            return false;
        }

        uint32 GetData(uint32 type) const override
        {
            if (type == eDatas::DataPlatformNumberToJumpTo)
                return positionToJumpTo;

            return 0;
        }

    private:
        TaskScheduler _textScheduler;
        TaskScheduler _phasingScheduler;
        bool _phasing = false;
        uint32 positionToJumpTo = 0;
};

/// ID - 386781 Frost Bomb
class spell_frost_bomb_386781 : public SpellScript
{
    PrepareSpellScript(spell_frost_bomb_386781);

    void HandleDummy(SpellEffIndex /*eff*/)
    {
        if (auto caster = GetCaster())
        {
            //std::list<Unit*> playersInRange;
            //caster->GetAttackableUnitListInRange(playersInRange, 40.0f);
            //playersInRange.remove_if([](Unit* who) -> bool
            //{
            //    return !who->IsPlayer();
            //});
            //
            //for (auto unit : playersInRange)
            //{
            //    caster->CastSpell(unit, eSpells::FrostBombDummyAura, true);
            //}
            if (auto hitUnit = GetHitUnit())
                if (hitUnit->IsPlayer())
                    caster->CastSpell(hitUnit, eSpells::FrostBombDummyAura, true);
        }

    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_frost_bomb_386781::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

/// ID - 386881 Frost Bomb
class spell_frost_bomb_386881 : public AuraScript
{
    PrepareAuraScript(spell_frost_bomb_386881);

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (auto target = GetTarget())
        {
            if (auto caster = GetCaster())
            {
                caster->CastSpell(target, eSpells::FrozenGround, true);
            }
        }
    }

    void Register() override
    {
        OnEffectRemove += AuraEffectRemoveFn(spell_frost_bomb_386881::HandleRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
    }
};

struct at_se_frost_bomb_26505 : public AreaTriggerAI
{
    public:
        at_se_frost_bomb_26505(AreaTrigger* at) : AreaTriggerAI(at) { }

        void OnUnitEnter(Unit* who) override
        {
            if (who->IsPlayer())
                if (auto caster = at->GetCaster())
                    caster->CastSpell(who, eSpells::FrozenGroundEffect, true);
        }

        void OnUnitExit(Unit* who) override
        {
            if (auto caster = at->GetCaster())
                if (!who->IsInsideAreaTrigger(26505))
                    who->RemoveAurasDueToSpell(eSpells::FrozenGroundEffect);
        }
};

struct at_se_vault_rune_26586 : public AreaTriggerAI
{
    public:
        at_se_vault_rune_26586(AreaTrigger* at) : AreaTriggerAI(at) { }

        void OnUnitEnter(Unit* who) override
        {
            if (who->IsPlayer())
                if (auto caster = at->GetCaster())
                    caster->CastSpell(who, eSpells::VaultRuneAT, true);
        }

        void OnUnitExit(Unit* who) override
        {
            if (auto caster = at->GetCaster())
                who->RemoveAurasDueToSpell(eSpells::VaultRuneAT);
        }
};

/// ID - 390209 Activate Vault Rune [DNT]
class spell_activate_vault_rune_dnt_390209 : public SpellScript
{
    PrepareSpellScript(spell_activate_vault_rune_dnt_390209);

    void HandleDummy(SpellEffIndex /*eff*/)
    {
        if (auto caster = GetCaster())
        {
            // Activate the next vault rune.
            if (auto instance = caster->GetInstanceScript())
                instance->SetData(ACTION_ACTIVATE_VAULT_RUNE, 1);
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_activate_vault_rune_dnt_390209::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

/// ID - 389453 Ice Power [DNT]
class spell_ice_power_dnt_389453 : public AuraScript
{
    PrepareAuraScript(spell_ice_power_dnt_389453);

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
        if (auto caster = GetCaster())
        {
            if (caster->IsEngaged())
                caster->EnergizeBySpell(caster, GetSpellInfo(), 2, Powers::POWER_ENERGY);
        }
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_ice_power_dnt_389453::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

/// ID - 387981 Jump to Center [DNT]
class spell_jump_to_center_dnt_387981 : public SpellScript
{
    PrepareSpellScript(spell_jump_to_center_dnt_387981);

    void HandleJumpCharge(Optional<JumpArrivalCastArgs>& arrivalCast)
    {
        auto caster = GetCaster();
        if (!caster)
            return;

        if (!arrivalCast.has_value())
            arrivalCast.emplace();

        arrivalCast->OverridePos = JumpToCenterPosition;

        arrivalCast->Callbacks.push([caster]()
        {
            if (auto creature = caster->ToCreature())
                if (auto ai = creature->AI())
                    ai->DoAction(eActions::ActionJumpToCenter);
        });
    }

    void Register() override
    {
        OnJumpCharge += SpellJumpChargeFn(spell_jump_to_center_dnt_387981::HandleJumpCharge);
    }
};

/// ID - 388082 Jump to Platform [DNT]
class spell_jump_to_platform_dnt_388082 : public SpellScript
{
    PrepareSpellScript(spell_jump_to_platform_dnt_388082);

    void HandleJumpCharge(Optional<JumpArrivalCastArgs>& arrivalCast)
    {
        auto caster = GetCaster();
        if (!caster)
            return;

        if (!arrivalCast.has_value())
            arrivalCast.emplace();

        if (auto creature = caster->ToCreature())
        {
            if (auto ai = creature->AI())
            {
                uint32 positionToJumpTo = ai->GetData(eDatas::DataPlatformNumberToJumpTo);

                if (positionToJumpTo == 0)
                    arrivalCast->OverridePos = JumpToPlatformPosition_1;
                else if (positionToJumpTo == 1)
                    arrivalCast->OverridePos = JumpToPlatformPosition_2;
                else if (positionToJumpTo == 2)
                    arrivalCast->OverridePos = JumpToPlatformPosition_3;
            }
        }
        
        arrivalCast->Callbacks.push([caster]()
        {
            if (auto creature = caster->ToCreature())
                if (auto ai = creature->AI())
                    ai->DoAction(eActions::ActionJumpToPlatform);
        });
    }

    void Register() override
    {
        OnJumpCharge += SpellJumpChargeFn(spell_jump_to_platform_dnt_388082::HandleJumpCharge);
    }
};

void AddSC_BossTelashGreywing_SE()
{
    RegisterAzureVaultsCreatureAI(boss_se_telash_greywing_186737);

    RegisterSpellScript(spell_frost_bomb_386781);
    RegisterSpellScript(spell_frost_bomb_386881);
    RegisterSpellScript(spell_activate_vault_rune_dnt_390209);
    RegisterSpellScript(spell_ice_power_dnt_389453);
    RegisterSpellScript(spell_jump_to_center_dnt_387981);
    RegisterSpellScript(spell_jump_to_platform_dnt_388082);

    RegisterAreaTriggerAI(at_se_frost_bomb_26505);
    RegisterAreaTriggerAI(at_se_vault_rune_26586);

    //sSpellMgr->ApplySpellFix({ eSpells::JumpToCenterDNT }, [](SpellInfo* spellInfo)
    //{
    //    sSpellMgr->ApplySpellEffectFix(spellInfo, EFFECT_0, [](SpellEffectInfo* effectInfo)
    //    {
    //        effectInfo->TargetA = SpellImplicitTargetInfo(TARGET_DEST_DEST);
    //    });
    //});
    //
    //sSpellMgr->ApplySpellFix({ eSpells::JumpToPlatformDNT }, [](SpellInfo* spellInfo)
    //{
    //    sSpellMgr->ApplySpellEffectFix(spellInfo, EFFECT_0, [](SpellEffectInfo* effectInfo)
    //    {
    //        effectInfo->TargetA = SpellImplicitTargetInfo(TARGET_DEST_DEST);
    //    });
    //});
}
