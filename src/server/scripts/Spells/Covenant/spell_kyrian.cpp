#include "SpellMgr.h"
#include "Unit.h"
#include "SpellScript.h"
#include "CovenantMgr.h"
#include "Player.h"
#include "SpellAuras.h"
#include "SpellHistory.h"
#include "AreaTriggerAI.h"
#include "AreaTrigger.h"
#include "Group.h"
#include "SpellAuraEffects.h"
#include "CellImpl.h"
#include "Cell.h"

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

    PhialOfSerenityItem              = 177278,
    PhialOfSerenitySpell             = 323436,
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
            me->FollowTarget(owner);
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
            Position pos = *actor;

            if (eventInfo.GetProcSpell())
            {
                if (eventInfo.GetProcSpell()->m_targets.GetDstPos())
                    pos = *eventInfo.GetProcSpell()->m_targets.GetDstPos();
                else if (auto targ = eventInfo.GetProcSpell()->m_targets.GetUnitTarget())
                    pos = *targ;
            }

            actor->CastSpell(pos, EffusiveProc, true);
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
        BronActive = 333961,
    };

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto actor = eventInfo.GetActor())
        {
            if (actor->HasAura(BronActive))
                return;

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
        }
        else
            currChance = 0;

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

/// ID: 351488 Spear of the Archon
class spell_spear_of_the_archon : public AuraScript
{
    PrepareAuraScript(spell_spear_of_the_archon);

    enum SpearOfTheArchon
    {
        CritSpell = 352720,
        SpeedSpell = 352719,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetActionTarget() || !eventInfo.GetActor())
            return false;

        return eventInfo.GetActionTarget()->HealthAbovePct(90);
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto actor = eventInfo.GetActor())
            actor->CastSpell(actor, CritSpell, true);
    }

    void HandleCombat(bool combat)
    {
        if (!GetTarget())
            return;

        if (combat)
            GetTarget()->RemoveAurasDueToSpell(SpeedSpell);
        else
            GetTarget()->CastSpell(GetTarget(), SpeedSpell, true);
    }

    void HandleApply(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (!GetTarget())
            return;

        if (GetTarget()->IsInCombat())
            GetTarget()->RemoveAurasDueToSpell(SpeedSpell);
        else
            GetTarget()->CastSpell(GetTarget(), SpeedSpell, true);
    }

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (!GetTarget())
            return;

        GetTarget()->RemoveAurasDueToSpell(SpeedSpell);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_spear_of_the_archon::CheckProc);
        OnProc += AuraProcFn(spell_spear_of_the_archon::HandleProc);
        OnEnterLeaveCombat += AuraEnterLeaveCombatFn(spell_spear_of_the_archon::HandleCombat);
        OnEffectApply += AuraEffectApplyFn(spell_spear_of_the_archon::HandleApply, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY, AURA_EFFECT_HANDLE_REAL);
        OnEffectRemove += AuraEffectApplyFn(spell_spear_of_the_archon::HandleRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

/// ID: 329791 Valiant Strikes
class spell_valiant_strikes : public AuraScript
{
    PrepareAuraScript(spell_valiant_strikes);

    enum ValiantStrikes
    {
        ValiantStrikesBuff = 330943,
        HealSpell          = 330945,
        LightOfThePath     = 351491,
        LightOfThePathBuff = 352981,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetHitMask() & ProcFlagsHit::PROC_HIT_CRITICAL && eventInfo.GetActor();
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto actor = eventInfo.GetActor())
        {
            actor->CastSpell(actor, ValiantStrikesBuff, true);

            if (auto aura = actor->GetAura(ValiantStrikesBuff))
            {
                aura->GetEffect(EFFECT_1)->SetAmount(aura->GetStackAmount());
            }
        }
    }

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (!GetCaster())
            return;

        GetCaster()->RemoveAurasDueToSpell(ValiantStrikesBuff);
    }

    uint32 updateTime = 0;

    void HandleUpdate(const uint32 diff)
    {
        if (updateTime >= 1000)
        {
            updateTime = 0;
            if (auto target = GetCaster())
            {
                if (auto player = target->ToPlayer())
                {
                    std::list<Player*> partyMembers;

                    if (auto group = player->GetGroup())
                    {
                        for (GroupReference* itr = group->GetFirstMember(); itr != nullptr; itr = itr->next())
                            if (Player* member = itr->GetSource())
                                partyMembers.push_back(member);
                    }
                    else
                        partyMembers.push_back(player);

                    if (!partyMembers.empty())
                    {
                        partyMembers.sort(Trinity::HealthPctOrderPred());
                        auto firstUnit = partyMembers.front();
                        if (firstUnit && firstUnit->HealthBelowPct(50))
                        {
                            auto buff = target->GetAura(ValiantStrikesBuff);
                            if (buff)
                            {
                                auto buffStacks = buff->GetStackAmount();
                                auto health = firstUnit->CountPctFromMaxHealth(buffStacks);
                                target->CastSpell(firstUnit, HealSpell, CastSpellExtraArgs(true).AddSpellBP0(health));

                                if (auto aura = target->GetAura(ValiantStrikesBuff))
                                {
                                    target->CastSpell(target, LightOfThePathBuff, true);
                                    firstUnit->CastSpell(firstUnit, LightOfThePathBuff, true);
                                }
                            }
                        }
                    }
                }
            }
        }
        else
            updateTime += diff;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_valiant_strikes::CheckProc);
        OnProc += AuraProcFn(spell_valiant_strikes::HandleProc);
        OnEffectRemove += AuraEffectApplyFn(spell_valiant_strikes::HandleRemove, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY, AURA_EFFECT_HANDLE_REAL);
        OnAuraUpdate += AuraUpdateFn(spell_valiant_strikes::HandleUpdate);
    }
};

/// ID: 334066 Mentorship
class spell_mentorship : public AuraScript
{
    PrepareAuraScript(spell_mentorship);

    enum Mentorship
    {
        MentorshipHealth = 334067,
    };

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
        auto target = GetCaster();
        if (!target)
            return;

        if (target->HealthAbovePct(90))
        {
            if (!target->HasAura(MentorshipHealth))
                target->CastSpell(target, MentorshipHealth, true);
        }
        else if (target->HasAura(MentorshipHealth))
            target->RemoveAura(MentorshipHealth);
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_mentorship::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
    }
};
/// ID: 323436 Purify Soul
class spell_purify_soul : public SpellScript
{
    PrepareSpellScript(spell_purify_soul);

    enum PurifySoul
    {
        PurifySoulId        = 323436,
        AscendantPhialAura  = 329776,
        AscendantPhialBuff  = 330752,
        PhialOfPatience     = 329777,
        PhialOfPatienceBuff = 330749,
        HopeSpringsEternal  = 351489,
        HopeSpringsBuff     = 353192,
        ChargedAdditive     = 331610,
        ChargedAdditiveKB   = 332336,
    };

    void HandleDummy(SpellEffIndex eff)
    {
        auto caster = GetCaster();
        if (!caster)
            return;

        if (caster->HasAura(AscendantPhialAura))
            caster->CastSpell(caster, AscendantPhialBuff, true);

        if (caster->HasAura(PhialOfPatience))
        {
            PreventHitDefaultEffect(eff);
            caster->CastSpell(caster, PhialOfPatienceBuff, true);
        }

        if (caster->HasAura(HopeSpringsEternal))
        {
            caster->CastSpell(caster, HopeSpringsBuff, true);

            Unit* lowestAlly = nullptr;
            std::list<Unit*> friendlyList;
            caster->GetFriendlyUnitListInRange(friendlyList, 40.0f, true);
            float lastHealth = 99.0f;
            for (auto unit : friendlyList)
            {
                if (unit->GetHealthPct() <= lastHealth)
                {
                    lastHealth = unit->GetHealthPct();
                    lowestAlly = unit;
                }
            }

            if (lowestAlly != nullptr)
            {
                lowestAlly->CastSpell(lowestAlly, PurifySoulId, CastSpellExtraArgs(TRIGGERED_FULL_MASK | TRIGGERED_DONT_CREATE_COOLDOWN));
                lowestAlly->CastSpell(lowestAlly, HopeSpringsBuff, true);
            }
        }

        if (caster->HasAura(ChargedAdditive))
        {
            caster->CastSpell(caster, ChargedAdditiveKB, true);
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_purify_soul::HandleDummy, EFFECT_0, SPELL_EFFECT_HEAL_PCT);
    }
};
/// ID: 329778 Pointed Courage
class spell_pointed_courage : public AuraScript
{
    PrepareAuraScript(spell_pointed_courage);

    enum PointedCourage
    {
        Buff = 330511,
    };

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
        auto target = GetCaster();
        if (!target)
            return;

        std::list<Unit*> targetList;
        Trinity::AnyUnitInObjectRangeCheck check(target, 10.0f, true);
        Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(target, targetList, check);
        Cell::VisitWorldObjects(target, searcher, 10.0f);

        uint32 size = 0;

        for (auto unit : targetList)
        {
            if (unit != target)
                size++;
        }

        size = std::min(3u, size);

        if (size)
        {
            if (auto aur = target->GetAura(PointedCourage::Buff))
                aur->SetStackAmount(size);
            else if (auto aur = target->AddAura(PointedCourage::Buff, target))
                    aur->SetStackAmount(size);
        }
        else
            target->RemoveAurasDueToSpell(PointedCourage::Buff);
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_pointed_courage::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

/// ID: 329779 Bearer's Pursuit
class spell_bearers_pursuit : public AuraScript
{
    PrepareAuraScript(spell_bearers_pursuit);

    enum BearersPursuit
    {
        SlowAura = 321759,
    };

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto actor = eventInfo.GetActor())
        {
            if (auto target = eventInfo.GetActionTarget())
            {
                if (eventInfo.GetDamageInfo() && eventInfo.GetDamageInfo()->GetDamage())
                    actor->CastSpell(target, SlowAura, true);
            }
        }
    }

    void Register() override
    {
        OnProc += AuraProcFn(spell_bearers_pursuit::HandleProc);
    }
};

/// ID: 329784 Cleansing Rites
class spell_cleansing_rites : public AuraScript
{
    PrepareAuraScript(spell_cleansing_rites);

    enum CleansingRites
    {
        OOCShield = 330921,
        Shield = 330927,
    };

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
        auto target = GetCaster();
        if (target)
            return;

        if (target->HasAura(OOCShield) || target->HasAura(Shield))
            return;

        if (!target->IsInCombat())
        {
            target->CastSpell(target, OOCShield, true);
        }
        else
        {
            target->RemoveAurasDueToSpell(OOCShield);
        }
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_cleansing_rites::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

/// ID: 330921 Cleansing Rites
class spell_cleansing_rites_aura : public AuraScript
{
    PrepareAuraScript(spell_cleansing_rites_aura);

    enum CleansingRites
    {
        OOCShield = 330921,
        Shield = 330927,
    };

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        auto target = GetCaster();
        if (!target)
            return;

        target->CastSpell(target, Shield, CastSpellExtraArgs(true).AddSpellBP0(target->CountPctFromMaxHealth(10)));
    }

    void Register() override
    {
        OnEffectRemove += AuraEffectApplyFn(spell_cleansing_rites_aura::HandleRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

/// ID: 329781 Resonant Accolades
class spell_resonant_accolades : public AuraScript
{
    PrepareAuraScript(spell_resonant_accolades);

    enum ResonantAccolades
    {
        ResonantAccolades = 329781,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetActor())
            return false;

        if (!eventInfo.GetHealInfo())
            return false;

        auto target = eventInfo.GetActionTarget();
        if (!target)
            return false;

        return eventInfo.GetActor()->HealthAbovePct(70);
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        auto actor = eventInfo.GetActor();
        auto target = eventInfo.GetActionTarget();
        if (!target || !actor)
            return;

        if (!eventInfo.GetHealInfo())
            return;

        actor->CastSpell(target, ResonantAccolades, CastSpellExtraArgs(true).AddSpellBP0(eventInfo.GetHealInfo()->GetHeal() * 0.04f));
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_resonant_accolades::CheckProc);
        OnProc += AuraProcFn(spell_resonant_accolades::HandleProc);
    }
};

/// ID: 333882 Forgelite Filter
class spell_forgelite_filter : public SpellScript
{
    PrepareSpellScript(spell_forgelite_filter);

    void HandleDummy(SpellEffIndex /*eff*/)
    {
        if (auto caster = GetCaster())
        {
            if (auto player = caster->ToPlayer())
            {
                if (player->GetItemCount(PhialOfSerenityItem) >= 1)
                    if (!player->GetSpellHistory()->HasCooldown(PhialOfSerenitySpell))
                        player->CastSpell(player, PhialOfSerenitySpell, true);
            }
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_forgelite_filter::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

/// ID: 331611 Soulsteel Clamps
class spell_soulsteel_clamps : public AuraScript
{
    PrepareAuraScript(spell_soulsteel_clamps);

    enum SoulsteelClamps
    {
        Buff = 332506,
    };

    time_t LastMoveTime = 0;

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
        auto target = GetCaster();
        if (!target)
            return;

        auto CurrTime = GameTime::GetGameTime();

        if (target->isMoving())
        {
            LastMoveTime = CurrTime;

            if (auto aur = target->GetAura(Buff))
            {
                if (aur->GetDuration() == -1)
                {
                    aur->SetMaxDuration(4000);
                    aur->SetDuration(4000);
                }
            }
        }

        if (!LastMoveTime)
            LastMoveTime = CurrTime;
        else
        {
            auto diff = CurrTime - LastMoveTime;
            if (diff >= 4)
            {
                if (!target->HasAura(Buff))
                    target->CastSpell(target, Buff, true);

                if (auto aur = target->GetAura(Buff))
                {
                    if (aur->GetDuration() != -1)
                    {
                        aur->SetMaxDuration(-1);
                        aur->SetDuration(-1);
                    }
                }
            }
        }

    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_soulsteel_clamps::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE);
    }
};

/// ID: 333935 Hammer of Genesis
class spell_hammer_of_genesis : public AuraScript
{
    PrepareAuraScript(spell_hammer_of_genesis);

    enum HammerOfGensis
    {
        Buff = 333943,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetProcTarget() != nullptr && eventInfo.GetActor() != nullptr;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        auto target = eventInfo.GetProcTarget();
        if (!target)
            return;
        auto actor = eventInfo.GetActor();
        if (!actor)
            return;

        if (newUnits.count(target->GetGUID()))
            return;

        newUnits.insert(target->GetGUID());
        actor->CastSpell(actor, Buff, true);
    }

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
        auto target = GetCaster();
        if (!target)
            return;

        for (auto it = newUnits.begin(); it != newUnits.end(); )
        {
            auto unit = ObjectAccessor::GetUnit(*target, *it);
            if (!unit || unit->isDead() || !unit->IsInCombatWith(target))
            {
                it = newUnits.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }

    GuidUnorderedSet newUnits;

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_hammer_of_genesis::CheckProc);
        OnProc += AuraProcFn(spell_hammer_of_genesis::HandleProc);
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_hammer_of_genesis::HandlePeriodic, EFFECT_1, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
    }
};

/// ID: 352186 Soulglow Spectrometer
class spell_soulglow_spectrometer : public AuraScript
{
    PrepareAuraScript(spell_soulglow_spectrometer);

    enum SoulglowSpectormeter
    {
        Proc = 352939,
        ProcHeal = 352938,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetActor() && eventInfo.GetActionTarget();
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        auto target = eventInfo.GetProcTarget();
        if (!target)
            return;
        auto actor = eventInfo.GetActor();
        if (!actor)
            return;

        if (actor->IsValidAttackTarget(target))
            actor->CastSpell(target, Proc, true);
        else
            actor->CastSpell(target, ProcHeal, true);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_soulglow_spectrometer::CheckProc);
        OnProc += AuraProcFn(spell_soulglow_spectrometer::HandleProc);
    }
};

/// ID: 352187 Reactive Retrofitting
class spell_reactive_retrofitting : public AuraScript
{
    PrepareAuraScript(spell_reactive_retrofitting);

    enum Reactive
    {
        Shield = 352789,
    };

    time_t NextMagicTime = 0;
    time_t NextPhysicalTime = 0;

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetDamageInfo())
            return false;

        if (!eventInfo.GetActor())
            return false;

        auto now = GameTime::GetGameTime();

        if (eventInfo.GetDamageInfo()->GetSchoolMask() == SPELL_SCHOOL_MASK_NORMAL || eventInfo.GetDamageInfo()->GetSchoolMask() == SPELL_SCHOOL_MASK_NONE)
        {
            return now >= NextPhysicalTime;
        }

        return now >= NextPhysicalTime;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        auto now = GameTime::GetGameTime();

        if (eventInfo.GetDamageInfo()->GetSchoolMask() == SPELL_SCHOOL_MASK_NORMAL || eventInfo.GetDamageInfo()->GetSchoolMask() == SPELL_SCHOOL_MASK_NONE)
        {
            eventInfo.GetActor()->CastSpell(eventInfo.GetActor(), Shield, CastSpellExtraArgs(true).AddSpellBP0(eventInfo.GetActor()->CountPctFromMaxHealth(6)));
            NextPhysicalTime = now + 30;
        }
        else
            NextMagicTime = now + 30;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_reactive_retrofitting::CheckProc);
        OnProc += AuraProcFn(spell_reactive_retrofitting::HandleProc);
    }
};

/// ID: 329786 Road of Trials
class spell_road_of_trials : public AuraScript
{
    PrepareAuraScript(spell_road_of_trials);

    enum RoadOfTrials
    {
        RoadOfTrialMSBuff = 330896,
    };

    void HandleProc(ProcEventInfo& eventInfo)
    {
        /// @TODO: If kill a big mob give more duration. Not sure what blizz does here.
        if (auto actor = eventInfo.GetActor())
            actor->CastSpell(actor, RoadOfTrialMSBuff, CastSpellExtraArgs(true).AddSpellBP0(10));
    }

    void Register() override
    {
        OnProc += AuraProcFn(spell_road_of_trials::HandleProc);
    }
};

/// ID: 328257 Let Go of the Past
class spell_let_go_of_the_past : public AuraScript
{
    PrepareAuraScript(spell_let_go_of_the_past);

    enum LetGoOfThePast
    {
        Buff = 328900,
    };

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetSpellInfo())
            return;

        if (LastSpellCasted != eventInfo.GetSpellInfo()->Id)
        {
            LastSpellCasted = eventInfo.GetSpellInfo()->Id;
            if (auto actor = eventInfo.GetActor())
                actor->CastSpell(actor, Buff, true);
        }
    }

    uint32 LastSpellCasted = 0;

    void Register() override
    {
        OnProc += AuraProcFn(spell_let_go_of_the_past::HandleProc);
    }
};
/// ID: 351146 Better Together
class spell_better_together : public AuraScript
{
    PrepareAuraScript(spell_better_together);

    enum BetterTogether
    {
        FriendBuff = 352498,
    };

    bool VerifyFriend(Unit* target)
    {
        auto player = ObjectAccessor::GetPlayer(*target, FriendGuid);
        if (!player || !player->HasAura(FriendBuff))
        {
            FriendGuid.Clear();
            return false;
        }

        return true;
    }

    void HandleUpdate(const uint32 diff)
    {
        if (updateTime >= 1000)
        {
            auto target = GetCaster();
            if (!target)
                return;

            if (!VerifyFriend(target) && !target->HasAura(FriendBuff))
            {
                if (auto player = target->SelectNearestPlayer(3.0f))
                {
                    FriendGuid = player->GetGUID();
                    player->CastSpell(target, FriendBuff, true);
                    target->CastSpell(player, FriendBuff, true);
                }
            }

            updateTime = 0;
        }
        else
            updateTime += diff;
    }

    uint32 updateTime = 0;
    ObjectGuid FriendGuid;

    void Register() override
    {
        OnAuraUpdate += AuraUpdateFn(spell_better_together::HandleUpdate);
    }
};

// 18264
struct at_elysian_decree : public AreaTriggerAI
{
public:
    at_elysian_decree(AreaTrigger* ai) : AreaTriggerAI(ai) { }

    enum ElysianDecree
    {
        Dmg = 307046,
        RepeatDecreeDmg = 339893,
        BlindFaith = 355893,
        BlindFaithVersa = 355894,
    };

    void OnCreate() override
    {
        if (auto caster = at->GetCaster())
            if (caster->HasAura(BlindFaith))
                caster->CastSpell(caster, BlindFaithVersa, true);
    }

    void OnUnitExit(Unit* who) override
    {
        if (!at->IsRemoved())
            return;

        auto caster = at->GetCaster();
        if (!caster)
            return;

        if (!caster->IsValidAttackTarget(who))
            return;

        caster->CastSpell(who, Dmg, true);
    }

    void OnRemove() override
    {
        if (auto caster = at->GetCaster())
            caster->CastSpell(*at, RepeatDecreeDmg, true);
    }
};

/// ID: 339894 Elysian Decree
class spell_elysian_decree : public SpellScript
{
    PrepareSpellScript(spell_elysian_decree);

    enum ElysianDecrees
    {
        RepeatDecree = 339895,
    };

    void HandleDMG(SpellEffIndex /*eff*/)
    {
        if (auto caster = GetCaster())
        {
            if (auto target = GetHitUnit())
            {
                if (auto aura = caster->GetAuraEffect(RepeatDecree, EFFECT_0))
                {
                    auto AP = caster->GetTotalAttackPowerValue(WeaponAttackType::BASE_ATTACK);
                    SetHitDamage(aura->GetAmount() + AP * 3.5f);
                }
            }
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_elysian_decree::HandleDMG, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

/// ID: 307046 Elysian Decree
class spell_elysian_decree_dmg : public SpellScript
{
    PrepareSpellScript(spell_elysian_decree_dmg);

    enum ElysianDecrees
    {
        RepeatDecree = 339895,
    };

    void HandleDummy(SpellEffIndex eff)
    {
        //if (auto caster = GetCaster())
        //    if (!caster->HasAura(RepeatDecree))
                PreventHitEffect(eff);
    }

    void Register() override
    {
        OnEffectLaunch += SpellEffectFn(spell_elysian_decree_dmg::HandleDummy, EFFECT_1, SPELL_EFFECT_TRIGGER_SPELL);
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
    RegisterSpellScript(spell_spear_of_the_archon);
    RegisterSpellScript(spell_valiant_strikes);
    RegisterSpellScript(spell_mentorship);
    RegisterSpellScript(spell_purify_soul);
    RegisterSpellScript(spell_pointed_courage);
    RegisterSpellScript(spell_bearers_pursuit);
    RegisterSpellScript(spell_cleansing_rites);
    RegisterSpellScript(spell_cleansing_rites_aura);
    RegisterSpellScript(spell_resonant_accolades);
    RegisterSpellScript(spell_forgelite_filter);
    RegisterSpellScript(spell_soulsteel_clamps);
    RegisterSpellScript(spell_hammer_of_genesis);
    RegisterSpellScript(spell_soulglow_spectrometer);
    RegisterSpellScript(spell_reactive_retrofitting);
    RegisterSpellScript(spell_road_of_trials);
    RegisterSpellScript(spell_let_go_of_the_past);
    RegisterSpellScript(spell_better_together);
    RegisterSpellScript(spell_elysian_decree);
    RegisterSpellScript(spell_elysian_decree_dmg);

    RegisterAreaTriggerAI(areatrigger_combat_meditation);
    RegisterAreaTriggerAI(areatrigger_newfound_resolve);
    RegisterAreaTriggerAI(at_elysian_decree);
}
