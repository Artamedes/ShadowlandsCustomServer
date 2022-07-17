#include "spell_dk.h"

using namespace DeathKnight;

/// ID: 335177 Phearomones
class spell_phearomones : public AuraScript
{
    PrepareAuraScript(spell_phearomones);

    enum ePhearomes
    {
        TrembleBeforeMe = 206961,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && (eventInfo.GetSpellInfo()->Id == DeathAndDecayDmg || eventInfo.GetSpellInfo()->Id == DefileDmg);
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto target = eventInfo.GetProcTarget())
            if (auto caster = GetCaster())
                caster->CastSpell(target, TrembleBeforeMe, true);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_phearomones::CheckProc);
        OnProc += AuraProcFn(spell_phearomones::HandleProc);
    }
};

/// ID: 334501 Bryndaor's Might
class spell_bryndaors_might : public AuraScript
{
    PrepareAuraScript(spell_bryndaors_might);

    enum eBryndaorsMight
    {
        EnergizeSpell = 334502,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == DeathStrike;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto procSpell = eventInfo.GetProcSpell())
        {
            if (auto caster = GetCaster())
            {
                if (auto healInfo = eventInfo.GetHealInfo())
                {
                    if (healInfo->GetHeal() >= caster->CountPctFromMaxHealth(10))
                    {
                        if (auto runicPower = procSpell->GetPowerCost(Powers::POWER_RUNIC_POWER))
                        {
                            uint32 totalRunicPoewr = runicPower->Amount + runicPower->OptionalAmount;
                            totalRunicPoewr = CalculatePct(totalRunicPoewr, 15) * 10;
                            caster->CastSpell(caster, EnergizeSpell, CastSpellExtraArgs(true).AddSpellBP0(totalRunicPoewr));
                        }
                    }
                }
            }
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_bryndaors_might::CheckProc);
        OnProc += AuraProcFn(spell_bryndaors_might::HandleProc);
    }
};

void AddSC_spell_dk_legendary()
{
    RegisterSpellScript(spell_phearomones);
    RegisterSpellScript(spell_bryndaors_might);
}
