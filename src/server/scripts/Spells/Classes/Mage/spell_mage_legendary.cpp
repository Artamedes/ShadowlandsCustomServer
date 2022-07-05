#include "spell_mage.h"

using namespace Mage;

/// ID: 327365 Disciplinary Command
class spell_disciplinary_command : public AuraScript
{
    PrepareAuraScript(spell_disciplinary_command);

    enum eDisciplinaryCommand
    {
        FrostBuff = 327366,
        FireBuff = 327368,
        ArcaneBuff = 327369,
        DmgBuff = 327371,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        auto caster = GetCaster();
        if (!caster)
            return false;
        return !caster->HasAura(DmgBuff) && eventInfo.GetSpellInfo() && (eventInfo.GetSchoolMask() & SPELL_SCHOOL_MASK_ARCANE || eventInfo.GetSchoolMask() & SPELL_SCHOOL_MASK_FROST || eventInfo.GetSchoolMask() & SPELL_SCHOOL_MASK_FIRE);
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        auto caster = GetCaster();
        if (!caster)
            return;

        if (eventInfo.GetSchoolMask() & SPELL_SCHOOL_MASK_ARCANE)
            caster->CastSpell(caster, ArcaneBuff, true);

        if (eventInfo.GetSchoolMask() & SPELL_SCHOOL_MASK_FROST)
            caster->CastSpell(caster, FrostBuff, true);

        if (eventInfo.GetSchoolMask() & SPELL_SCHOOL_MASK_FIRE)
            caster->CastSpell(caster, FireBuff, true);

        if (caster->HasAura(ArcaneBuff) && caster->HasAura(FrostBuff) && caster->HasAura(FireBuff))
            caster->CastSpell(caster, DmgBuff, true);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_disciplinary_command::CheckProc);
        OnProc += AuraProcFn(spell_disciplinary_command::HandleProc);
    }
};

/// ID: 327489 Expanded Potential
class spell_expanded_potential : public AuraScript
{
    PrepareAuraScript(spell_expanded_potential);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetSpellInfo())
            return false;

        switch (eventInfo.GetSpellInfo()->Id)
        {
            case FrostBolt:
            case Fireball:
            case ArcaneBlast:
                return true;
            default:
                return false;   
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_expanded_potential::CheckProc);
    }
};

/// ID: 333373 Triune Ward
class spell_triune_ward : public AuraScript
{
    PrepareAuraScript(spell_triune_ward);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetSpellInfo())
            return false;

        switch (eventInfo.GetSpellInfo()->Id)
        {
            case BlazingBarrier:
            case IceBarrier:
            case PrismaticBarrier:
                return true;
            default:
                return false;
        }
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        auto caster = GetCaster();
        if (!caster)
            return;

        caster->CastSpell(caster, BlazingBarrier, true);
        caster->CastSpell(caster, IceBarrier, true);
        caster->CastSpell(caster, PrismaticBarrier, true);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_triune_ward::CheckProc);
        OnProc += AuraProcFn(spell_triune_ward::HandleProc);
    }
};

/// ID: 332769 Arcane Harmony
class spell_arcane_harmony : public AuraScript
{
    PrepareAuraScript(spell_arcane_harmony);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == ArcaneMisslesDmg;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_arcane_harmony::CheckProc);
    }
};

/// ID: 333030 Fevered Incantation
class spell_fevered_incantation : public AuraScript
{
    PrepareAuraScript(spell_fevered_incantation);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetHitMask() & ProcFlagsHit::PROC_HIT_CRITICAL;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto caster = GetCaster())
            caster->CastSpell(caster, 333049, true);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_fevered_incantation::CheckProc);
        OnProc += AuraProcFn(spell_fevered_incantation::HandleProc);
    }
};

void AddSC_spell_mage_legendary()
{
    RegisterSpellScript(spell_disciplinary_command);
    RegisterSpellScript(spell_expanded_potential);
    RegisterSpellScript(spell_arcane_harmony);
    RegisterSpellScript(spell_fevered_incantation);
}
