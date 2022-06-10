#include "SpellIncludes.h"
#include "spell_paladin.h"

using namespace Paladin;

/// ID: 328204 Vanquisher's Hammer
class spell_vanquishers_hammer : public AuraScript
{
    PrepareAuraScript(spell_vanquishers_hammer);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetSpellInfo())
            return false;

        auto caster = GetCaster();

        switch (GetSpecializationId(caster))
        {
            case SimpleTalentSpecs::HPally:
                return eventInfo.GetSpellInfo()->Id == PaladinSpells::WordOfGlory;
            case SimpleTalentSpecs::ProtPally:
                return eventInfo.GetSpellInfo()->Id == PaladinSpells::TemplarsVerdict;
            case SimpleTalentSpecs::Retribution:
                return eventInfo.GetSpellInfo()->Id == PaladinSpells::WordOfGlory;
            default:
                return false;
        }
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();
        if (auto caster = GetCaster())
        {
            if (auto hitUnit = eventInfo.GetActionTarget())
            {
                //caster->ModifyPower(Powers::POWER_HOLY_POWER, 3);

                switch (GetSpecializationId(caster))
                {
                    case SimpleTalentSpecs::HPally:
                        caster->Variables.Set("EmpoweredLightOfDawn", true);
                        caster->CastSpell(hitUnit, PaladinSpells::LightOfDawn, CastSpellExtraArgs(TRIGGERED_FULL_MASK));
                        break;
                    case SimpleTalentSpecs::ProtPally:
                        caster->Variables.Set("EmpoweredShieldOfTheRighteous", true);
                        caster->CastSpell(hitUnit, PaladinSpells::ShieldOfTheRighteous, CastSpellExtraArgs(TRIGGERED_FULL_MASK));
                        break;
                    case SimpleTalentSpecs::Retribution:
                        caster->Variables.Set("EmpoweredDivineStorm", true);
                        caster->CastSpell(hitUnit, PaladinSpells::DivineStorm, CastSpellExtraArgs(TRIGGERED_FULL_MASK));
                        break;
                }
            }
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_vanquishers_hammer::CheckProc);
        OnProc += AuraProcFn(spell_vanquishers_hammer::HandleProc);
    }
};

/// ID: 340192 Righteous Might Conduit
class spell_righteous_might : public AuraScript
{
    PrepareAuraScript(spell_righteous_might);

    enum RighteousMight
    {
        RighteousMightHeal = 340193,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetDamageInfo() && eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == PaladinSpells::VanquishersHammer;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();

        if (!eventInfo.GetDamageInfo())
            return;

        if (auto caster = GetCaster())
            caster->CastSpell(caster, RighteousMightHeal, CastSpellExtraArgs(true).AddSpellBP0(eventInfo.GetDamageInfo()->GetDamage() * 0.50f));
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_righteous_might::CheckProc);
        OnProc += AuraProcFn(spell_righteous_might::HandleProc);
    }
};

void AddSC_spell_paladin_covenant()
{
    RegisterSpellScript(spell_vanquishers_hammer);
    RegisterSpellScript(spell_righteous_might);
}
