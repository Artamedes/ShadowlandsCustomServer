#include "SpellIncludes.h"

enum eShamanCovenant
{
    FaeTransfusion         = 328923,
    FaeTransfusionDmg      = 328928,
    FaeTransfusionHeal     = 328930,
    FaeTransfusionBuffHeal = 328933,
};

enum eShaman
{
    SpiritWalk          = 58875,
    SpiritWalkersGrace  = 79206,
    FrostShock          = 196840,
    MaelstromWepAura    = 344179,
    LightningBolt       = 188196,
    EarthShock          = 8042,
    FlameShock          = 188389,
};

/// ID: 328923 Fae Transfusion
class spell_fae_transfusion_spellscript : public SpellScript
{
    PrepareSpellScript(spell_fae_transfusion_spellscript);

    void HandleDummy(SpellEffIndex /*eff*/)
    {
        if (auto caster = GetCaster())
        {
            if (auto hitDest = GetHitDest())
            {
                if (caster->Variables.Exist("FaeTransfusionDmg"))
                    caster->Variables.Remove("FaeTransfusionDmg");
                caster->Variables.Set("HitDestFaeTransfusion", Position(*hitDest));
            }
        }
    }

    void Register() override
    {
        OnEffectLaunch += SpellEffectFn(spell_fae_transfusion_spellscript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

/// ID: 328923 Fae Transfusion
class spell_fae_transfusion : public AuraScript
{
    PrepareAuraScript(spell_fae_transfusion);

    void HandlePeriodic(AuraEffect const* aurEff)
    {
        if (auto caster = GetCaster())
        {
            if (caster->Variables.Exist("HitDestFaeTransfusion"))
            {
                Position pos = caster->Variables.GetValue("HitDestFaeTransfusion", caster->GetPosition());
                caster->CastSpell(pos, FaeTransfusionDmg, true);

                if (caster->Variables.Exist("FaeTransfusionDmg"))
                {
                    int32 dam = caster->Variables.GetValue("FaeTransfusionDmg", 0);

                    if (auto aur = caster->GetAura(FaeTransfusionBuffHeal))
                    {
                        if (dam)
                        {
                            aur->GetEffect(EFFECT_0)->SetAmount(CalculatePct(dam, 60));
                            aur->SetNeedClientUpdateForTargets();
                        }
                    }
                }
            }
        }
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_fae_transfusion::HandlePeriodic, EFFECT_1, SPELL_AURA_PERIODIC_DUMMY);
    }
};

/// ID: 328930  Fae Transfusion
class spell_fae_transfusion_heal : public SpellScript
{
    PrepareSpellScript(spell_fae_transfusion_heal);

    void HandleHeal(SpellEffIndex /*eff*/)
    {
        if (auto caster = GetCaster())
        {
            if (caster->Variables.Exist("FaeTransfusionDmg"))
            {
                int32 dam = caster->Variables.GetValue("FaeTransfusionDmg", 0);

                if (dam)
                    SetHitHeal(CalculatePct(dam, 60));
            }
        }
    }

    void HandleDummy(SpellEffIndex /*eff*/)
    {
        if (auto caster = GetCaster())
        {
            caster->RemoveAurasDueToSpell(FaeTransfusionBuffHeal);
            if (caster->Variables.Exist("HitDestFaeTransfusion"))
                caster->Variables.Remove("HitDestFaeTransfusion");
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_fae_transfusion_heal::HandleHeal, EFFECT_0, SPELL_EFFECT_HEAL);
        OnEffectLaunch += SpellEffectFn(spell_fae_transfusion_heal::HandleDummy, EFFECT_1, SPELL_EFFECT_DUMMY);
    }
};

/// ID: 328928 Fae Transfusion
class spell_fae_transfusion_dmg : public SpellScript
{
    PrepareSpellScript(spell_fae_transfusion_dmg);

    void HandleDmg(SpellEffIndex /*eff*/)
    {
        if (auto caster = GetCaster())
        {
            int32 prevDmg = caster->Variables.GetValue("FaeTransfusionDmg", 0);
            caster->Variables.Set("FaeTransfusionDmg", prevDmg + GetHitDamage());
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_fae_transfusion_dmg::HandleDmg, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

/// ID: 338048 Spiritual Resonance
class spell_spiritual_resonance : public AuraScript
{
    PrepareAuraScript(spell_spiritual_resonance);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetSpellInfo())
            return false;

        return eventInfo.GetSpellInfo()->Id == Heroism || eventInfo.GetSpellInfo()->Id == Bloodlust;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto caster = GetCaster())
            if (auto eff = GetEffect(EFFECT_0))
                if (eff->ConduitRankEntry)
                {
                    uint32 currDuration = 0;
                    if (auto flame = caster->GetAura(FlameShock))
                        currDuration += flame->GetDuration();

                    if (IsSpec(caster, SimpleTalentSpecs::Enhancement))
                        caster->CastSpell(caster, SpiritWalk, CastSpellExtraArgs(true).AddSpellMod(SpellValueMod::SPELLVALUE_DURATION, eff->ConduitRankEntry->AuraPointsOverride));
                    else
                        caster->CastSpell(caster, SpiritWalkersGrace, CastSpellExtraArgs(true).AddSpellMod(SpellValueMod::SPELLVALUE_DURATION, eff->ConduitRankEntry->AuraPointsOverride));
                }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_spiritual_resonance::CheckProc);
        OnProc += AuraProcFn(spell_spiritual_resonance::HandleProc);
    }
};

// 344179 malestrom wep

/// ID: 338325 Chilled to the Core
class spell_chilled_to_the_core : public AuraScript
{
    PrepareAuraScript(spell_chilled_to_the_core);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetSpellInfo())
            return false;

        return eventInfo.GetSpellInfo()->Id == FrostShock;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto caster = GetCaster())
            if (auto eff = GetEffect(EFFECT_0))
                if (eff->ConduitRankEntry)
                    caster->CastSpell(caster, MaelstromWepAura, CastSpellExtraArgs(true).AddSpellMod(SPELLVALUE_AURA_STACK, 2));
    }

    void OnCalcProc(ProcEventInfo& eventInfo, float& chance)
    {
        chance = 0.0f;
        if (auto eff = GetEffect(EFFECT_0))
            if (eff->ConduitRankEntry)
                chance = eff->ConduitRankEntry->AuraPointsOverride;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_chilled_to_the_core::CheckProc);
        OnProc += AuraProcFn(spell_chilled_to_the_core::HandleProc);
        OnCalcProcChance += AuraCalcProcChanceFn(spell_chilled_to_the_core::OnCalcProc);
    }
};

/// ID: 345594 Pyroclastic Shock
class spell_pyroclastic_shock : public AuraScript
{
    PrepareAuraScript(spell_pyroclastic_shock);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetSpellInfo())
            return false;

        return eventInfo.GetSpellInfo()->Id == EarthShock;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto caster = GetCaster())
            if (auto eff = GetEffect(EFFECT_0))
                if (eff->ConduitRankEntry)
                    if (auto target = eventInfo.GetActionTarget())
                        if (target->HasAura(FlameShock))
                        {
                            uint32 currDuration = 0;

                            if (auto flame = target->GetAura(FlameShock))
                                currDuration += flame->GetDuration();

                            caster->CastSpell(target, FlameShock, CastSpellExtraArgs(true).AddSpellMod(SPELLVALUE_DURATION, 12000 + currDuration));
                        }
    }

    void OnCalcProc(ProcEventInfo& eventInfo, float& chance)
    {
        chance = 0.0f;
        if (auto eff = GetEffect(EFFECT_0))
            if (eff->ConduitRankEntry)
                chance = eff->ConduitRankEntry->AuraPointsOverride;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_pyroclastic_shock::CheckProc);
        OnProc += AuraProcFn(spell_pyroclastic_shock::HandleProc);
        OnCalcProcChance += AuraCalcProcChanceFn(spell_pyroclastic_shock::OnCalcProc);
    }
};

void AddSC_spell_shaman_covenant()
{
    RegisterSpellAndAuraScriptPairWithArgs(spell_fae_transfusion_spellscript, spell_fae_transfusion, "spell_fae_transfusion");
    RegisterSpellScript(spell_fae_transfusion_heal);
    RegisterSpellScript(spell_fae_transfusion_dmg);

    RegisterSpellScript(spell_spiritual_resonance);
    RegisterSpellScript(spell_chilled_to_the_core);
    RegisterSpellScript(spell_pyroclastic_shock);
}
