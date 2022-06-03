#include "SpellMgr.h"
#include "Unit.h"
#include "SpellScript.h"
#include "CovenantMgr.h"
#include "Player.h"
#include "SpellAuras.h"
#include "SpellHistory.h"
#include "AreaTriggerAI.h"
#include "AreaTrigger.h"

enum Kyrian
{
    ShackleTheUnworthy               = 312202,
    ElysianDecree                    = 306830,
    KindredSpirits                   = 326434, // has 3 spells
    ResonatingArrow                  = 308491,
    RadiantSpark                     = 307443,
    WeaponsOfOrder                   = 310454,
    DivineToll                       = 304971,
    BoonOfTheAscended                = 325013,
    EchoingReprimand                 = 323547,
    VesperTotem                      = 324386,
    ScouringTithe                    = 312321,
    SpearOfBastion                   = 307865,

    // Druid Swaps
    KindredProtection                = 327037,
    KindredFocus                     = 327071,
    KindredEmpowerment               = 327022,
};

struct npc_kyrian_steward : public ScriptedAI
{
    public:
        npc_kyrian_steward(Creature* creature) : ScriptedAI(creature) { }

        void InitializeAI() override
        {

        }

        void IsSummonedBy(WorldObject* o) override
        {
            if (!o)
                return;
            auto owner = o->ToUnit();
            if (!owner)
                return;

            me->SetCreatorGUID(owner->GetGUID());
            me->GetMotionMaster()->MoveFollow(owner, PET_FOLLOW_DIST, me->GetFollowAngle());
            DoCastSelf(326346); // (Steward Name Override [DNT])
            DoCastSelf(326506); // (Steward Spawn VFX [DNT])
            DoCastSelf(324749); // (Carry Tray [DNT])
            DoCastSelf(324791); // (Carry Bottle[DNT])
            DoCastSelf(344432); // (At Your Service)
        }
        // 342477- ping steward bard

        void Reset() override
        {

        }

        uint32 OwnerCheck = 0;

        void UpdateAI(uint32 diff) override
        {
            if (OwnerCheck >= 1000)
            {
                OwnerCheck = 0;
                if (!me->GetOwner())
                {
                    me->DespawnOrUnsummon();
                    return;
                }
            }
            else
                OwnerCheck += diff;

            if (!gavePotsToOwner && me->GetOwner() && me->GetOwner()->IsPlayer())
            {
                if (me->GetDistance2d(me->GetOwner()) <= 3.0f)
                {
                    for (int i = 0; i < 3; ++i)
                    {
                        DoCast(me->GetOwner(), 324743, true);
                        me->GetOwner()->ToPlayer()->AddItem(177278, 1);
                    }
                    me->RemoveAurasDueToSpell(324791); // Carry Bottle
                    gavePotsToOwner = true;
                }
            }
        }

        enum MenuIds
        {
            IdMain = 40275, // Hoo! Can help? Can do many tasks, or just keep company!
            IdOne = 42480, // What can I do-hoo for you? Can help with one thing, so pick careful! Will take time for me to help again -- one hour. Very busy!
            IdTwo = 42481, // Hoo-ooo! Can help with one big task, but just one. Will take time for me to help again--a few hours. Busy busy!
        };

        bool OnGossipHello(Player* player) override
        {
            if (player == me->GetOwner())
            {
                ClearGossipMenuFor(player);
                AddGossipItemFor(player, GossipOptionIcon::None, "I need a favor. (1 hr cooldown)", 0, 7);
                AddGossipItemFor(player, GossipOptionIcon::None, "I have a special request. (4 hr cooldown)", 0, 3);
                AddGossipItemFor(player, GossipOptionIcon::None, "Tell one of my friends how great they are! (1 day cooldown)", 0, 6);
                AddGossipItemFor(player, GossipOptionIcon::None, "Can you play me a song?", 0, 2);
                AddGossipItemFor(player, GossipOptionIcon::None, "Thank you. See you later!", 0, 8);

                // (26712, 3, 0, 'Let\'s talk about something else.',                           0, 1, 1, 0, 25502, 0, 0, 0, NULL, 0, 42979),
                // (25502, 8, 0, 'Can you play me a song?',                                     0, 1, 1, 0, UNKNOWN, UNKNOWN, 0, 0, NULL, 0, 42979),
                // (25502, 1, 0, 'I have a special request. (4 hr cooldown)',                   0, 1, 1, 0, 26713, 0, 0, 0, NULL, 0, 42979),
                // (26713, 0, 0, 'I\'d like to change my talents.',                             0, 1, 1, 0, UNKNOWN, UNKNOWN, 0, 0, NULL, 0, 42979),
                // (26712, 0, 1, 'Would you please take these items off my hands?',             0, 3, 128, 0, UNKNOWN, UNKNOWN, 0, 0, NULL, 0, 42979),
                // (25502, 3, 0, 'Tell one of my friends how great they are! (1 day cooldown)', 0, 1, 1, 0, UNKNOWN, UNKNOWN, 0, 0, NULL, 0, 42979),
                // (25502, 0, 0, 'I need a favor. (1 hr cooldown)',                             0, 1, 1, 0, 26712, 0, 0, 0, NULL, 0, 42979),
                // (25502, 19, 0, 'Thank you. See you later!',                                  0, 1, 1, 0, UNKNOWN, UNKNOWN, 0, 0, NULL, 0, 42979),
                SendGossipMenuFor(player, IdMain, me);
            }
            return true;
        }

        bool OnGossipSelect(Player* player, uint32 menuId, uint32 gossipId) override
        {
            uint32 actionId = player->PlayerTalkClass->GetGossipOptionAction(gossipId);
            ClearGossipMenuFor(player);

            switch (actionId)
            {
                case 1:
                    return OnGossipHello(player);
                case 7:
                    AddGossipItemFor(player, GossipOptionIcon::None, "Would you please take these items off my hands?", 0, 5);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Let\'s talk about something else.", 0, 1);
                    SendGossipMenuFor(player, IdOne, me);
                    break;
                case 3:
                    AddGossipItemFor(player, GossipOptionIcon::None, "I\'d like to change my talents.", 0, 4);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Let\'s talk about something else.", 0, 1);
                    SendGossipMenuFor(player, IdTwo, me);
                    break;
                case 4:
                    CloseGossipMenuFor(player);
                    player->CastSpell(player, 325012, true);
                    break;
                case 5:
                    player->GetSession()->SendListInventory(me->GetGUID());
                    break;
                case 6: // tell my friend how great they are
                    CloseGossipMenuFor(player);
                    break;
                case 2: // play song
                    CloseGossipMenuFor(player);

                    break;
                case 8: // despawn
                    CloseGossipMenuFor(player);
                    DoCastSelf(324807); // dismiss
                    me->DespawnOrUnsummon(5s);
                    break;
            }

            return true;
        }

        bool gavePotsToOwner = false;
};

/// ID - 352188 Effusive Anima Accelerator
class spell_kyrian_effusive_anima_accelerator_aura : public AuraScript
{
    PrepareAuraScript(spell_kyrian_effusive_anima_accelerator_aura);

    enum EffusiveAnima
    {
        EffusiveProc = 353248,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetSpellInfo())
            return false;

        switch (eventInfo.GetSpellInfo()->Id)
        {
            case ShackleTheUnworthy:
            case ElysianDecree:
            case KindredSpirits:
            case ResonatingArrow:
            case RadiantSpark:
            case WeaponsOfOrder:
            case DivineToll:
            case BoonOfTheAscended:
            case EchoingReprimand:
            case VesperTotem:
            case ScouringTithe:
            case SpearOfBastion:
            case KindredProtection:
            case KindredFocus:
            case KindredEmpowerment:
                return true;

            default:
                return false;
        }

    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto actor = eventInfo.GetActor())
        {
            actor->CastSpell(actor, EffusiveProc, true);
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_kyrian_effusive_anima_accelerator_aura::CheckProc);
        OnProc += AuraProcFn(spell_kyrian_effusive_anima_accelerator_aura::HandleProc);
    }
};

// ID - 353248 Effusive Anima Accelerator
class spell_kyrian_effusive_anima_accelerator : public SpellScript
{
    PrepareSpellScript(spell_kyrian_effusive_anima_accelerator);

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        auto caster = GetCaster();
        if (!caster)
            return;
        if (targets.empty())
            return;

        int32 targetsSize = targets.size();
        // 1sec per 30sec of base CD

        auto ModifyCooldown([&](uint32 spellId)
        {
            auto spellInfo = sSpellMgr->GetSpellInfo(spellId);
            if (!spellInfo)
                return;

            if (caster->HasSpell(spellId))
            {
                int32 baseCDR = spellInfo->RecoveryTime / 30000; // 6 sec
                int32 cdr = baseCDR * targetsSize * 1000;
                caster->GetSpellHistory()->ModifyCooldown(spellId, -cdr);
            }
        });

        ModifyCooldown(ShackleTheUnworthy);
        ModifyCooldown(ElysianDecree);
        ModifyCooldown(KindredSpirits);
        ModifyCooldown(ResonatingArrow);
        ModifyCooldown(RadiantSpark);
        ModifyCooldown(WeaponsOfOrder);
        ModifyCooldown(DivineToll);
        ModifyCooldown(BoonOfTheAscended);
        ModifyCooldown(EchoingReprimand);
        ModifyCooldown(VesperTotem);
        ModifyCooldown(ScouringTithe);
        ModifyCooldown(SpearOfBastion);
        ModifyCooldown(KindredProtection);
        ModifyCooldown(KindredFocus);
        ModifyCooldown(KindredEmpowerment);
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_kyrian_effusive_anima_accelerator::FilterTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ENEMY);
    }
};

/// ID - 328738 Focusing Mantra
class spell_focusing_mantra : public SpellScript
{
    PrepareSpellScript(spell_focusing_mantra);

    enum FocusingMantra
    {
        PhialOfSerenitySpell = 323436,
    };
    
    void HandleDummy(SpellEffIndex /*eff*/)
    {
        if (Unit* caster = GetCaster())
        {
            caster->GetSpellHistory()->ModifyCooldown(PhialOfSerenitySpell, -1000);
        }
    }

    void Register()
    {
        OnEffectHitTarget += SpellEffectFn(spell_focusing_mantra::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

/// ID - 333950 Bron's Call to Action
class spell_brons_call_to_action : public AuraScript
{
    PrepareAuraScript(spell_brons_call_to_action);

    enum Bron
    {
        BronStackAura = 332514,
        BronsCallToAction = 334048,
    };

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto actor = eventInfo.GetActor())
        {
            actor->CastSpell(actor, BronStackAura, true);

            if (auto aur = actor->GetAura(BronStackAura))
            {
                if (aur->GetStackAmount() >= 74)
                {
                    aur->Remove();
                    actor->CastSpell(actor, BronsCallToAction, true);
                }
            }
        }
    }


    void Register() override
    {
        OnProc += AuraProcFn(spell_brons_call_to_action::HandleProc);
    }
};

// 171396
struct npc_kyrian_goliath : public ScriptedAI
{
    public:
        npc_kyrian_goliath(Creature* creature) : ScriptedAI(creature) { }

        enum BronSpells
        {
            BronKnockback = 333963,
            AnimaCannon = 332525,
            Smash = 341163,
            Heal = 332526,
        };

        void InitializeAI() override
        {
            scheduler.SetValidator([this]
            {
                return !me->HasUnitState(UNIT_STATE_CASTING);
            });
        }

        void JustEngagedWith(Unit* who) override
        {
            scheduler.CancelAll();

            DoCastAOE(BronKnockback);
            scheduler.Schedule(5s, [this](TaskContext context)
            {
                DoCastVictim(Smash, true);
                context.Repeat(5s);
            });
            scheduler.Schedule(7s, [this](TaskContext context)
            {
                std::list<Unit*> friendlyTargets;
                me->GetFriendlyUnitListInRange(friendlyTargets, 30.0f, true);
                if (!friendlyTargets.empty())
                {
                    friendlyTargets.sort(Trinity::HealthPctOrderPred());
                    DoCast(friendlyTargets.front(), Heal);
                }
                context.Repeat(10s);
            });
            scheduler.Schedule(7s, [this](TaskContext context)
            {
                DoCastVictim(AnimaCannon);
                context.Repeat(7s);
            });
        }

        void UpdateAI(uint32 diff) override
        {
            if (auto owner = me->GetOwner())
            {
                if (me->GetVictim() != owner->GetVictim())
                {
                    if (owner->GetVictim())
                        AttackStart(owner->GetVictim());
                }
            }

            if (!UpdateVictim())
                return;

            scheduler.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            DoMeleeAttackIfReady();
        }
    private:
        TaskScheduler scheduler;
};

/// ID - 328266 Combat Meditation
class spell_combat_meditation : public AuraScript
{
    PrepareAuraScript(spell_combat_meditation);

    enum CombatMeditation
    {
        CombatMeditationMastery = 328908,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetSpellInfo())
            return false;

        switch (eventInfo.GetSpellInfo()->Id)
        {
            case ShackleTheUnworthy:
            case ElysianDecree:
            case KindredSpirits:
            case ResonatingArrow:
            case RadiantSpark:
            case WeaponsOfOrder:
            case DivineToll:
            case BoonOfTheAscended:
            case EchoingReprimand:
            case VesperTotem:
            case ScouringTithe:
            case SpearOfBastion:
            case KindredProtection:
            case KindredFocus:
            case KindredEmpowerment:
                return true;

            default:
                return false;
        }

    }

    void HandleProc(AuraEffect* /*aurEff*/, ProcEventInfo& eventInfo)
    {
        if (auto actor = eventInfo.GetActor())
        {
            actor->CastSpell(actor, CombatMeditationMastery);
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_combat_meditation::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_combat_meditation::HandleProc, EFFECT_0, SPELL_AURA_PROC_TRIGGER_SPELL);
    }
};

/// ID - 328908 Combat Meditation (Level 60)
class spell_combat_meditation_buff : public AuraScript
{
    PrepareAuraScript(spell_combat_meditation_buff);

    enum CombatMeditation
    {
        MissleAnimaOrb = 328917,
    };

    void HandlePeriodic(AuraEffect const* effect)
    {
        Unit* caster = GetCaster();
        if (!caster)
            return;

        caster->CastSpell(caster, MissleAnimaOrb, true);
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_combat_meditation_buff::HandlePeriodic, EFFECT_1, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
    }
};

/// 20456
struct areatrigger_combat_meditation : public AreaTriggerAI
{
public:
    areatrigger_combat_meditation(AreaTrigger* at) : AreaTriggerAI(at) { }

    enum CombatMeditation
    {
        CombatMeditationMastery = 328908,
    };

    bool consumed = false;

    void OnUnitEnter(Unit* who) override
    {
        if (consumed)
            return;

        if (who == at->GetOwner())
        {
            consumed = true;
            if (auto aura = who->GetAura(CombatMeditationMastery))
            {
                aura->ModDuration(3000);
            }
            else
            {
                if (auto aura = who->AddAura(CombatMeditationMastery, who))
                {
                    aura->SetDuration(3000);
                }
            }
            at->Remove();
        }
    }
};

/// ID - 351149 Newfound Resolve
class spell_newfound_resolve : public AuraScript
{
    PrepareAuraScript(spell_newfound_resolve);

    enum NewfoundResolveProc
    {
        ProcMissle = 352918,
    };

    uint32 currChance = 0;

    void HandlePeriodic(AuraEffect const* effect)
    {
        Unit* caster = GetCaster();
        if (!caster)
            return;

        if (caster->IsInCombat())
        {
            //  Proc rate: Deck of Cards Deck Size: 30 Success Cards: 1 1 card is "drawn" every 3 seconds while in combat.
            currChance += 3;

            if (roll_chance_i(std::min(100u, currChance)))
            {
                currChance = 0;
                caster->CastSpell(caster, ProcMissle, true);
            }
            else
                currChance += 3;
        }

    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_newfound_resolve::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

// 23044
struct areatrigger_newfound_resolve : public AreaTriggerAI
{
public:
    areatrigger_newfound_resolve(AreaTrigger* at) : AreaTriggerAI(at) { }

    enum NewfoundResolve
    {
        NewfoundResolveBuff = 352917,
    };

    void OnUpdate(uint32 diff) override
    {
        if (auto owner = at->GetOwner())
        {
            if (owner->HasInLine(at, at->GetObjectSize(), at->GetObjectSize()))
            {
                owner->CastSpell(owner, NewfoundResolveBuff, true);
                at->Remove();
            }
        }
    }
};

void AddSC_spell_kyrian()
{
    RegisterCreatureAI(npc_kyrian_steward);
    RegisterCreatureAI(npc_kyrian_goliath);

    RegisterSpellScript(spell_kyrian_effusive_anima_accelerator_aura);
    RegisterSpellScript(spell_kyrian_effusive_anima_accelerator);
    RegisterSpellScript(spell_focusing_mantra);
    RegisterSpellScript(spell_brons_call_to_action);
    RegisterSpellScript(spell_combat_meditation);
    RegisterSpellScript(spell_combat_meditation_buff);
    RegisterSpellScript(spell_newfound_resolve);

    RegisterAreaTriggerAI(areatrigger_combat_meditation);
    RegisterAreaTriggerAI(areatrigger_newfound_resolve);
}
