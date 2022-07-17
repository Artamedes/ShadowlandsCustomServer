#include "spell_druid.h"

using namespace Druid;

/// ID: 338661 Oneth's Clear Vision
class spell_oneths_clear_vision : public AuraScript
{
    PrepareAuraScript(spell_oneths_clear_vision);

    enum eOneths
    {
        OnethStarsurgeProc = 339797,
        OnethPerception,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && (eventInfo.GetSpellInfo()->Id == Starfall || eventInfo.GetSpellInfo()->Id == Starsurge);
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetSpellInfo())
        {
            if (eventInfo.GetSpellInfo()->Id == Starfall)
            {
                if (roll_chance_i(40))
                    if (auto caster = GetCaster())
                        caster->CastSpell(caster, OnethStarsurgeProc, true);
            }
            else if (eventInfo.GetSpellInfo()->Id == Starsurge)
            {
                if (roll_chance_i(20))
                    if (auto caster = GetCaster())
                        caster->CastSpell(caster, OnethPerception, true);
            }
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_oneths_clear_vision::CheckProc);
        OnProc += AuraProcFn(spell_oneths_clear_vision::HandleProc);
    }
};

/// ID: 339800 Oneth's Perception
class spell_oneths_perception : public AuraScript
{
    PrepareAuraScript(spell_oneths_perception);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == Starfall;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        Remove();
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_oneths_perception::CheckProc);
        OnProc += AuraProcFn(spell_oneths_perception::HandleProc);
    }
};

/// ID: 339797 Oneth's Clear Vision
class spell_oneths_clear_vision_proc : public AuraScript
{
    PrepareAuraScript(spell_oneths_clear_vision_proc);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == Starsurge;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        Remove();
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_oneths_clear_vision_proc::CheckProc);
        OnProc += AuraProcFn(spell_oneths_clear_vision_proc::HandleProc);
    }
};

/// ID: 338668 Primordial Arcanic Pulsar
class spell_primordial_arcanic_pulsar : public AuraScript
{
    PrepareAuraScript(spell_primordial_arcanic_pulsar);

    enum ePrimordialArcanicPulsar
    {
        PrimordialArcanicPulsarBuff = 338825,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetProcSpell() && eventInfo.GetProcSpell()->GetPowerCost(Powers::POWER_LUNAR_POWER);
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto caster = GetCaster())
        {
            if (auto power = eventInfo.GetProcSpell()->GetPowerCost(Powers::POWER_LUNAR_POWER))
            {
                if (auto buff = caster->GetAura(PrimordialArcanicPulsarBuff))
                {
                    buff->GetEffect(EFFECT_0)->ChangeAmount(buff->GetEffect(EFFECT_0)->GetAmount() + power->Amount / 10);
                    if (buff->GetEffect(EFFECT_0)->GetAmount() >= 300)
                    {
                        buff->GetEffect(EFFECT_0)->ChangeAmount(buff->GetEffect(EFFECT_0)->GetAmount() + -300);

                        uint32 currDuration = 0;

                        if (auto celes = caster->GetAura(CelestialAlignment))
                            currDuration += celes->GetDuration();

                        caster->CastSpell(caster, CelestialAlignment, CastSpellExtraArgs(TRIGGERED_FULL_MASK_NO_CD).AddSpellMod(SpellValueMod::SPELLVALUE_DURATION, 12000 + currDuration));
                    }
                }
                else
                    caster->CastSpell(caster, PrimordialArcanicPulsarBuff, CastSpellExtraArgs(true).AddSpellBP0(power->Amount / 10));
            }
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_primordial_arcanic_pulsar::CheckProc);
        OnProc += AuraProcFn(spell_primordial_arcanic_pulsar::HandleProc);
    }
};

/// ID: 339949 Timeworn Dreambinder
class spell_timeworn_dreambinder : public AuraScript
{
    PrepareAuraScript(spell_timeworn_dreambinder);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && (eventInfo.GetSpellInfo()->Id == Starfall || eventInfo.GetSpellInfo()->Id == Starsurge);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_timeworn_dreambinder::CheckProc);
    }
};

void AddSC_spell_druid_legendary()
{
    RegisterSpellScript(spell_oneths_clear_vision);
    RegisterSpellScript(spell_oneths_perception);
    RegisterSpellScript(spell_oneths_clear_vision_proc);
    RegisterSpellScript(spell_primordial_arcanic_pulsar);
    RegisterSpellScript(spell_timeworn_dreambinder);
}
