#include "SpellIncludes.h"

enum eAffliction
{
    MaleficRapture      = 324536,
    MaleficRaptureDmg   = 324540,
    Corruption          = 146739,
    Agony               = 980,
    UnstableAffliction  = 316099,
    ShadowBolt          = 686,
    DrainSoul           = 198590,
};

/// ID: 364437 Deliberate Malice 2pc
class spell_deliberate_malice : public AuraScript
{
    PrepareAuraScript(spell_deliberate_malice);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == MaleficRaptureDmg;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto caster = GetCaster())
        {
            if (auto target = eventInfo.GetActionTarget())
            {
                auto UpDuration([&](uint32 spell) -> void
                {
                    if (auto aura = target->GetAura(spell, caster->GetGUID()))
                    {
                        aura->ModDuration(2000);

                        for (auto eff : aura->GetAuraEffects())
                        {
                            if (eff && eff->GetAuraType() == SPELL_AURA_PERIODIC_DAMAGE)
                                eff->ResetPeriodic();
                        }
                    }
                });

                UpDuration(Corruption);
                UpDuration(Agony);
                UpDuration(UnstableAffliction);
            }
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_deliberate_malice::CheckProc);
        OnProc += AuraProcFn(spell_deliberate_malice::HandleProc);
    }
};

/// ID: 363953 Calamitous Crescendo 4pc
class spell_calamitous_crescendo : public AuraScript
{
    PrepareAuraScript(spell_calamitous_crescendo);

    enum eCalamitousCrescendo
    {
        ProcSpell = 364322,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetSpellInfo())
            return false;

        auto caster = GetCaster();
        if (!caster)
            return false;

        if (!eventInfo.GetActionTarget())
            return false;

        switch (eventInfo.GetSpellInfo()->Id)
        {
            case ShadowBolt:
            case DrainSoul:
                break;
            default:
                return false;
        }

        auto HasDot([&](uint32 spell) -> bool
        {
            if (eventInfo.GetActionTarget()->HasAura(spell, caster->GetGUID()))
                return true;
            return false;
        });

        if (!HasDot(Agony) || !HasDot(Corruption) || !HasDot(UnstableAffliction))
            return false;

        return true;

       //switch (eventInfo.GetSpellInfo()->Id)
       //{
       //    case ShadowBolt:
       //        return roll_chance_i(30);
       //    case DrainSoul:
       //        return roll_chance_i(20);
       //    default:
       //        return false;
       //}
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        auto caster = GetCaster();
        if (!caster)
            return;

        if (!eventInfo.GetActionTarget())
            return;

        caster->CastSpell(caster, ProcSpell, true);
    }

    void OnCalcProc(ProcEventInfo& eventInfo, float& chance)
    {
        if (!eventInfo.GetSpellInfo())
            return;

        switch (eventInfo.GetSpellInfo()->Id)
        {
            case ShadowBolt:
                chance = 30;
                break;
            case DrainSoul:
                chance = 20;
                break;
            default:
                chance = 0;
                break;
        }

    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_calamitous_crescendo::CheckProc);
        OnProc += AuraProcFn(spell_calamitous_crescendo::HandleProc);
        OnCalcProcChance += AuraCalcProcChanceFn(spell_calamitous_crescendo::OnCalcProc);
    }
};

const uint32 dotAuras[] = { 325640, Agony, Corruption, 278350, 205179, 316099 };

/// ID: 205180 Summon Darkglare
class spell_summon_darkglare : public SpellScript
{
    PrepareSpellScript(spell_summon_darkglare);

    void HandleAfterCast()
    {
        auto caster = GetCaster();
        if (!caster)
            return;

        std::list<Unit*> enemies;
        caster->GetAttackableUnitListInRange(enemies, 100.0f);
        for (auto enemy : enemies)
        {
            uint32 totalAuras = 0;
            for (auto dot : dotAuras)
                if (auto aura = enemy->GetAura(dot, caster->GetGUID()))
                {
                    aura->ModDuration(8000);
                    for (auto eff : aura->GetAuraEffects())
                    {
                        if (eff && eff->GetAuraType() == SPELL_AURA_PERIODIC_DAMAGE)
                            eff->ResetPeriodic();
                    }
                }
        }
    }

    void Register() override
    {
        AfterCast += SpellCastFn(spell_summon_darkglare::HandleAfterCast);
    }
};

/// ID: 316099 Unstable Affliction
class spell_unstable_affliction : public AuraScript
{
    PrepareAuraScript(spell_unstable_affliction);

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
        auto caster = GetCaster();
        if (!caster)
            return;
        if (auto corruptingLeer = caster->GetAuraEffect(339455, EFFECT_0))
            if (corruptingLeer->ConduitRankEntry)
                if (roll_chance_i(corruptingLeer->ConduitRankEntry->AuraPointsOverride))
                    caster->GetSpellHistory()->ModifyCooldown(205180, -5000);
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_unstable_affliction::HandlePeriodic, EFFECT_1, SPELL_AURA_PERIODIC_DAMAGE);
    }
};

void AddSC_spell_warlock_affliction()
{
    RegisterSpellScript(spell_deliberate_malice);
    RegisterSpellScript(spell_calamitous_crescendo);
    RegisterSpellScript(spell_summon_darkglare);
    RegisterSpellScript(spell_unstable_affliction);
}
