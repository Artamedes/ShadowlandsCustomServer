#include "spell_priest.h"

using namespace Priest;

/// ID: 337748 Light's Inspiration
class spell_lights_inspiration : public AuraScript
{
    PrepareAuraScript(spell_lights_inspiration);

    enum eLightInspiration
    {
        ProcSpell = 337749,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetSpellInfo())
            return false;

        return eventInfo.GetSpellInfo()->Id == DesperatePrayer;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto caster = GetCaster())
            if (auto eff = GetEffect(EFFECT_0))
                if (eff->ConduitRankEntry)
                    caster->CastSpell(caster, ProcSpell, CastSpellExtraArgs(true).AddSpellBP0(eff->ConduitRankEntry->AuraPointsOverride));
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_lights_inspiration::CheckProc);
        OnProc += AuraProcFn(spell_lights_inspiration::HandleProc);
    }
};

/// ID: 337947 Resonant Words
class spell_resonant_words : public AuraScript
{
    PrepareAuraScript(spell_resonant_words);

    enum eResonantWords
    {
        ProcSpell = 337948,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetSpellInfo())
            return false;

        if (auto spell = eventInfo.GetSpellInfo()->Id)
            if (spell == Salvation || spell == Chastise || spell == Sanctify || spell == Serenity)
                return true;

        return false;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto caster = GetCaster())
            if (auto eff = GetEffect(EFFECT_0))
                if (eff->ConduitRankEntry)
                    caster->CastSpell(caster, ProcSpell, CastSpellExtraArgs(true).AddSpellBP0(eff->ConduitRankEntry->AuraPointsOverride));
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_resonant_words::CheckProc);
        OnProc += AuraProcFn(spell_resonant_words::HandleProc);
    }
};

/// ID: 325013 Boon of the Ascended
class spell_boon_of_the_ascended : public AuraScript
{
    PrepareAuraScript(spell_boon_of_the_ascended);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetProcSpell() && (eventInfo.GetSpellInfo()->Id == AscendedNova || eventInfo.GetSpellInfo()->Id == AscendedBlast);
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetProcSpell())
            return;

        switch (eventInfo.GetSpellInfo()->Id)
        {
            case AscendedNova:
                GetAura()->ModStackAmount(1, AURA_REMOVE_BY_DEFAULT, false, false);
                break;
            case AscendedBlast:
                GetAura()->ModStackAmount(5, AURA_REMOVE_BY_DEFAULT, false, false);
                break;
        }

    }

    void OnApplyRoot(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        PreventDefaultAction();
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_boon_of_the_ascended::OnApplyRoot, EFFECT_5, SPELL_AURA_MOD_ROOT, AURA_EFFECT_HANDLE_REAL);
        DoCheckProc += AuraCheckProcFn(spell_boon_of_the_ascended::CheckProc);
        OnProc += AuraProcFn(spell_boon_of_the_ascended::HandleProc);
    }
};

/// ID: 325283 Ascended Blast
class spell_ascended_blast : public SpellScript
{
    PrepareSpellScript(spell_ascended_blast);

    enum eEsecendedBlast
    {
        CourageousAscension = 337966,
        AscendedBlastHeal = 325315,
    };

    void HandleDummy(SpellEffIndex /*eff*/)
    {
        auto caster = GetCaster();
        if (!caster)
            return;

        if (auto conduit = caster->GetAuraEffect(CourageousAscension, EFFECT_0))
            if (conduit->ConduitRankEntry)
            {
                auto newDmg = GetHitDamage();
                AddPct(newDmg, conduit->ConduitRankEntry->AuraPointsOverride);
                SetHitDamage(newDmg);

                caster->CastSpell(caster, AscendedBlastHeal, CastSpellExtraArgs(true).AddSpellBP0(CalculatePct(newDmg, 120)));
            }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_ascended_blast::HandleDummy, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

void AddSC_spell_priest_covenant()
{
    RegisterSpellScript(spell_lights_inspiration);
    RegisterSpellScript(spell_resonant_words);
    RegisterSpellScript(spell_boon_of_the_ascended);
    RegisterSpellScript(spell_ascended_blast);
}
