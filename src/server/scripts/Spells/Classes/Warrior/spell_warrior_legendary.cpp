#include "spell_warrior.h"

using namespace Warrior;

/// ID: 335253 Misshapen Mirror
class spell_misshapen_mirror : public AuraScript
{
    PrepareAuraScript(spell_misshapen_mirror);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == SpellReflection;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_misshapen_mirror::CheckProc);
    }
};
/// ID: 335266 Signet of Tormented Kings
class spell_signet_of_tormented_kings : public AuraScript
{
    PrepareAuraScript(spell_signet_of_tormented_kings);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetSpellInfo())
            return false;

        switch (eventInfo.GetSpellInfo()->Id)
        {
            case Bladestorm:
            case BladestormFury:
            case Ravager:
            case Recklessness:
            case Avatar:
                return true;
        }

        return false;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        auto caster = GetCaster();
        if (!caster)
            return;

        if (!eventInfo.GetSpellInfo())
            return;


        std::list<uint32> randSpells;
        if (caster->HasSpell(Ravager))
            randSpells.emplace_back(Ravager);
        else
        {
            if (!IsSpec(caster, SimpleTalentSpecs::Fury))
                randSpells.emplace_back(Bladestorm);
            else
                randSpells.emplace_back(BladestormFury);
        }
        randSpells.emplace_back(Recklessness);
        randSpells.emplace_back(Avatar);

        randSpells.remove_if([eventInfo](uint32 spellId) -> bool
        {
            return eventInfo.GetSpellInfo()->Id == spellId;
        });

        caster->CastSpell(caster, Trinity::Containers::SelectRandomContainerElement(randSpells), CastSpellExtraArgs(true).AddSpellBP0(TRIGGERED_FULL_MASK | TRIGGERED_DONT_CREATE_COOLDOWN));
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_signet_of_tormented_kings::CheckProc);
        OnProc += AuraProcFn(spell_signet_of_tormented_kings::HandleProc);
    }
};

void AddSC_spell_warrior_legendary()
{
    RegisterSpellScript(spell_misshapen_mirror);
    RegisterSpellScript(spell_signet_of_tormented_kings);
}
