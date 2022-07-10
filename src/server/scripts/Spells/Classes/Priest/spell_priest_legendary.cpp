#include "spell_priest.h"
#include "ScriptedCreature.h"
#include "ObjectAccessor.h"

using namespace Priest;

enum eMeasuredContemplation
{
    MeasuredContemplationProcAura = 341824,
    MeasuredContemplationVisual   = 343290,
};

/// ID: 341804 Measured Contemplation
class spell_measured_contemplation : public AuraScript
{
    PrepareAuraScript(spell_measured_contemplation);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && (eventInfo.GetSpellInfo()->Id == FlashHeal || eventInfo.GetSpellInfo()->Id == Shadowmend);
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        _nextCheckTime = GameTime::Now() + 15s;
    }

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
        auto now = GameTime::Now();

        if (now >= _nextCheckTime)
        {
            _nextCheckTime = GameTime::Now() + 15s;
            if (auto caster = GetCaster())
            {
                caster->CastSpell(caster, MeasuredContemplationProcAura, true);
                caster->CastSpell(caster, MeasuredContemplationVisual, true);
            }
        }
    }

    TimePoint _nextCheckTime;

    void Register() override
    {
        _nextCheckTime = GameTime::Now() + 15s;

        DoCheckProc += AuraCheckProcFn(spell_measured_contemplation::CheckProc);
        OnProc += AuraProcFn(spell_measured_contemplation::HandleProc);
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_measured_contemplation::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE);
    }
};

/// ID: 341824 Measured Contemplation
class spell_measured_contemplation_proc : public AuraScript
{
    PrepareAuraScript(spell_measured_contemplation_proc);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && (eventInfo.GetSpellInfo()->Id == FlashHeal || eventInfo.GetSpellInfo()->Id == Shadowmend);
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        ModStackAmount(-1);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_measured_contemplation_proc::CheckProc);
        OnProc += AuraProcFn(spell_measured_contemplation_proc::HandleProc);
    }
};

/// ID: 336067 Clarity of Mind
class spell_clarity_of_mind : public AuraScript
{
    PrepareAuraScript(spell_clarity_of_mind);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == SpiritShell;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        auto caster = GetCaster();
        if (!caster)
            return;

        std::list<Unit*> friendlies;
        caster->GetFriendlyUnitListInRange(friendlies, 40.0f);
        for (auto friendly : friendlies)
        {
            if (auto atonement = friendly->GetAura(AtonementAura, caster->GetGUID()))
                atonement->ModDuration(3000);
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_clarity_of_mind::CheckProc);
        OnProc += AuraProcFn(spell_clarity_of_mind::HandleProc);
    }
};

/// ID: 336011 The Penitent One
class spell_the_penitent_one : public AuraScript
{
    PrepareAuraScript(spell_the_penitent_one);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == PowerWordRadiance;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_the_penitent_one::CheckProc);
    }
};

/// ID: 336009 The Penitent One
class spell_the_penitent_one_proc : public AuraScript
{
    PrepareAuraScript(spell_the_penitent_one_proc);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == Penance;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        Remove();
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_the_penitent_one_proc::CheckProc);
        OnProc += AuraProcFn(spell_the_penitent_one_proc::HandleProc);
    }
};
/// ID: 336400 Divine Image
class spell_divine_image : public AuraScript
{
    PrepareAuraScript(spell_divine_image);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetSpellInfo())
            return false;

        if (auto spell = eventInfo.GetSpellInfo()->Id)
            if (spell == Salvation || spell == Chastise || spell == Sanctify || spell == Serenity)
                return true;

        return false;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_divine_image::CheckProc);
    }
};

struct npc_invoke_the_naaru : public ScriptedAI
{
    npc_invoke_the_naaru(Creature* p_Creature) : ScriptedAI(p_Creature) { }

    void JustEngagedWith(Unit* /*p_Target*/) override
    {
    }

    void Reset() override
    {
        me->SetReactState(REACT_PASSIVE);
    }
};

namespace Legion
{
    enum eSpells
    {
        HWChastise          = 88625,
        HWSanctify          = 34861,
        HWSerenity          = 2050,
        Renew               = 139,
        Heal                = 2060,
        FlashHeal           = 2061,
        PrayerOfHealing     = 596,
        PrayerOfMending     = 33076,
        DivineHymn          = 64843,
        Smite               = 585,
        HolyFire            = 14914,
        HolyNova            = 132157,

        ChastiseProcAura    = 196684,
        DamageHealProcAura  = 196705,

        SummonTuure         = 196685
    };

    /*
        @ http://www.wowhead.com/item=128825/tuure-beacon-of-the-naaru&bonus=0&spec=71#comments:id=2359192
        Your spell                                  T'uure's version
        Renew                                       Tranquil Light
        Heal & Flash Heal & Holy Word: Serenity     Healing Light
        Prayer of Healing & Holy Word: Sanctify     Dazzling Lights
        Prayer of Mending & Divine Hymn             Blessed Light
        Smite & Holy Fire & Holy Word: Chastise     Searing Light
        Holy Nova                                   Light Eruption
    */
    enum eDupeSpells
    {
        /// dupes
        TranquilLight   = 196816,
        HealingLight    = 196809,
        DazzlingLights  = 196810,
        BlessedLight    = 196813,
        SearingLight    = 196811,
        LightEruption   = 196812
    };
}

/// ID: 196705 Divine Image
class spell_divine_image_proc : public AuraScript
{
    PrepareAuraScript(spell_divine_image_proc);

    enum eNpcs
    {
        TuureId = 172309
    };

    std::map<uint32, uint32> l_TuureSpellIds =
    {
        { Legion::eSpells::Renew,           Legion::eDupeSpells::TranquilLight },
        { Legion::eSpells::Heal,            Legion::eDupeSpells::HealingLight },
        { Legion::eSpells::FlashHeal,       Legion::eDupeSpells::HealingLight },
        { Legion::eSpells::HWSerenity,      Legion::eDupeSpells::HealingLight },
        { Legion::eSpells::PrayerOfHealing, Legion::eDupeSpells::DazzlingLights },
        { Legion::eSpells::HWSanctify,      Legion::eDupeSpells::DazzlingLights },
        { Legion::eSpells::PrayerOfMending, Legion::eDupeSpells::BlessedLight },
        { Legion::eSpells::DivineHymn,      Legion::eDupeSpells::BlessedLight },
        { Legion::eSpells::Smite,           Legion::eDupeSpells::SearingLight },
        { Legion::eSpells::HolyFire,        Legion::eDupeSpells::SearingLight },
        { Legion::eSpells::HWChastise,      Legion::eDupeSpells::SearingLight },
        { Legion::eSpells::HolyNova,        Legion::eDupeSpells::LightEruption }
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetProcSpell() && l_TuureSpellIds.find(eventInfo.GetSpellInfo()->Id) != l_TuureSpellIds.end();
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        auto l_Caster = GetCaster();
        if (!l_Caster)
            return;

        if (!eventInfo.GetProcSpell())
            return;

        if (!eventInfo.GetProcTarget())
            return;

        auto itr = l_TuureSpellIds.find(eventInfo.GetSpellInfo()->Id);
        if (itr == l_TuureSpellIds.end())
            return;

        std::list<TempSummon*> l_Tuures;
        l_Caster->GetAllMinionsByEntry(l_Tuures, eNpcs::TuureId);
        for (auto l_Itr : l_Tuures)
            l_Itr->CastSpell(eventInfo.GetProcTarget(), itr->second, true);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_divine_image_proc::CheckProc);
        OnProc += AuraProcFn(spell_divine_image_proc::HandleProc);
    }
};

/// ID: 336266 Flash Concentration
class spell_flash_concentration : public AuraScript
{
    PrepareAuraScript(spell_flash_concentration);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == FlashHeal;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_flash_concentration::CheckProc);
    }
};

/// ID: 336214 Eternal Call to the Void
class spell_eternal_call_to_the_void : public AuraScript
{
    PrepareAuraScript(spell_eternal_call_to_the_void);

    enum eCallToTheVoid
    {
        CallToTheVoidSumm = 344753,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && (eventInfo.GetSpellInfo()->Id == MindFlay || eventInfo.GetSpellInfo()->Id == MindSear);
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        auto caster = GetCaster();
        if (!caster)
            return;

        caster->CastSpell(caster, CallToTheVoidSumm, true);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_eternal_call_to_the_void::CheckProc);
        OnProc += AuraProcFn(spell_eternal_call_to_the_void::HandleProc);
    }
};

// 175198
// 175198 - npc_void_lasher_175198
struct npc_void_lasher_175198 : public ScriptedAI
{
public:
    npc_void_lasher_175198(Creature* creature) : ScriptedAI(creature) { SetCombatMovement(false); }

    void UpdateAI(uint32 diff) override
    {
        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        if (me->isDead())
            return;

        timer.Update(diff);

        auto owner = me->GetOwner();
        if (owner)
        {
            auto ownerTarget = ObjectAccessor::GetUnit(*me, owner->GetTarget());
            if (!ownerTarget)
                return;

            if (me->IsValidAttackTarget(ownerTarget))
                DoCast(ownerTarget, 193473);

            if (timer.Passed())
            {
                timer.Reset(1000);
                owner->EnergizeBySpell(owner, sSpellMgr->GetSpellInfo(193473), 3, Powers::POWER_INSANITY);
            }
        }
    }

    TimeTracker timer;
};
/// ID: 342415 Talbadar's Stratagem
class spell_talbadars_stratagem : public AuraScript
{
    PrepareAuraScript(spell_talbadars_stratagem);

    enum eTalbadars
    {
        MindBlastDmgBuff = 342416,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo()
            && (eventInfo.GetSpellInfo()->Id == ShadowWordPain || eventInfo.GetSpellInfo()->Id == DevouringPlague || eventInfo.GetSpellInfo()->Id == VampiricTouch)
            && eventInfo.GetDamageInfo() && eventInfo.GetDamageInfo()->GetDamageType() != DamageEffectType::DOT;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        auto target = eventInfo.GetProcTarget();
        auto caster = GetCaster();

        if (!target || !caster)
            return;

        if (target->HasAura(ShadowWordPain, caster->GetGUID()) && target->HasAura(DevouringPlague, caster->GetGUID()) && target->HasAura(VampiricTouch, caster->GetGUID()))
        {
            caster->CastSpell(caster, MindBlastDmgBuff, true);
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_talbadars_stratagem::CheckProc);
        OnProc += AuraProcFn(spell_talbadars_stratagem::HandleProc);
    }
};

void AddSC_spell_priest_legendary()
{
    RegisterSpellScript(spell_measured_contemplation);
    RegisterSpellScript(spell_measured_contemplation_proc);
    RegisterSpellScript(spell_clarity_of_mind);
    RegisterSpellScript(spell_the_penitent_one);
    RegisterSpellScript(spell_the_penitent_one_proc);
    RegisterSpellScript(spell_divine_image);
    RegisterSpellScript(spell_divine_image_proc);
    RegisterSpellScript(spell_flash_concentration);
    RegisterSpellScript(spell_eternal_call_to_the_void);
    RegisterSpellScript(spell_talbadars_stratagem);
    RegisterCreatureAI(npc_invoke_the_naaru);
    RegisterCreatureAI(npc_void_lasher_175198);
}
