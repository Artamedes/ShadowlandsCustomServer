#include "SpellIncludes.h"

enum eShadow
{
    MindFlay = 15407,
    MindSear = 48045,
    MindBlast = 8092,
};

/// ID: 341205 Dark Thoughts
class spell_dark_thoughts : public AuraScript
{
    PrepareAuraScript(spell_dark_thoughts);

    enum eDarkThoughts
    {
        DarkThoughtProc = 341207,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetSpellInfo())
            return false;

        switch (eventInfo.GetSpellInfo()->Id)
        {
            case eShadow::MindFlay:
            case eShadow::MindSear:
                return true;
            default:
                return false;
        }
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();

        if (auto caster = GetCaster())
        {
            caster->CastSpell(caster, DarkThoughtProc, true);
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_dark_thoughts::CheckProc);
        OnProc += AuraProcFn(spell_dark_thoughts::HandleProc);
    }
};

/// ID: 341207 Dark Thought
class spell_dark_thought : public AuraScript
{
    PrepareAuraScript(spell_dark_thought);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetSpellInfo())
            return false;

        switch (eventInfo.GetSpellInfo()->Id)
        {
            case eShadow::MindBlast:
                return true;
            default:
                return false;
        }
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();
        if (auto aur = GetAura())
            aur->Remove();
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_dark_thought::CheckProc);
        OnProc += AuraProcFn(spell_dark_thought::HandleProc);
    }
};
void AddSC_spell_priest_shadow()
{
    RegisterSpellScript(spell_dark_thoughts);
    RegisterSpellScript(spell_dark_thought);
}
