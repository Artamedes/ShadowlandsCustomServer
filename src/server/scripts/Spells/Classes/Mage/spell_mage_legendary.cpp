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

        if (caster->GetSpellHistory()->HasCooldown(DmgBuff))
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

/// ID: 333097 Firestorm
class spell_firestorm : public AuraScript
{
    PrepareAuraScript(spell_firestorm);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == HotStreakBuff;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_firestorm::CheckProc);
    }
};
/// ID: 333167 Molten Skyfall
class spell_molten_skyfall : public AuraScript
{
    PrepareAuraScript(spell_molten_skyfall);

    enum eMoltenSkyfall
    {
        SkyfallProcCount = 333170,
        SkyfallProc = 333182,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && (eventInfo.GetSpellInfo()->Id == Fireball || eventInfo.GetSpellInfo()->Id == PyroBlast);
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        auto caster = GetCaster();
        if (!caster)
            return;

        caster->CastSpell(caster, SkyfallProcCount, true);

        if (auto aur = caster->GetAura(SkyfallProcCount))
            if (aur->GetStackAmount() >= aur->GetMaxStackAmount())
            {
                aur->Remove();
                caster->CastSpell(caster, SkyfallProc, true);
            }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_molten_skyfall::CheckProc);
        OnProc += AuraProcFn(spell_molten_skyfall::HandleProc);
    }
};

/// ID: 333182 Molten Skyfall
class spell_molten_skyfall_proc : public AuraScript
{
    PrepareAuraScript(spell_molten_skyfall_proc);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == Fireball;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        auto caster = GetCaster();
        auto target = eventInfo.GetActionTarget();
        if (!caster || !target)
            return;

        caster->CastSpell(target, Meteor, true);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_molten_skyfall_proc::CheckProc);
        OnProc += AuraProcFn(spell_molten_skyfall_proc::HandleProc);
    }
};

/// ID: 327511 Slick Ice
class spell_slick_ice : public AuraScript
{
    PrepareAuraScript(spell_slick_ice);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (auto caster = GetCaster())
            if (caster->HasAura(IcyVeins))
                return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == FrostBolt;

        return false;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_slick_ice::CheckProc);
    }
};
/// ID: 327284 Cold Front
class spell_cold_front : public AuraScript
{
    PrepareAuraScript(spell_cold_front);

    enum eColdfront
    {
        ColdfrontStacks = 327327,
        ColdfrontProc = 327330,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && (eventInfo.GetSpellInfo()->Id == FrostBolt || eventInfo.GetSpellInfo()->Id == Flurry);
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto caster = GetCaster())
        {
            caster->CastSpell(caster, ColdfrontStacks, true);
            if (auto aur = caster->GetAura(ColdfrontStacks))
                if (aur->GetStackAmount() >= 30)
                {
                    aur->Remove();
                    caster->CastSpell(caster, ColdfrontProc, true);
                }
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_cold_front::CheckProc);
        OnProc += AuraProcFn(spell_cold_front::HandleProc);
    }
};

/// ID: 327330 Cold Front
class spell_cold_front_proc : public AuraScript
{
    PrepareAuraScript(spell_cold_front_proc);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && (eventInfo.GetSpellInfo()->Id == FrostBolt || eventInfo.GetSpellInfo()->Id == Flurry);
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto caster = GetCaster())
            if (auto target = eventInfo.GetActionTarget())
            {
                caster->CastSpell(target, FrozenOrb, true);
                Remove();
            }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_cold_front_proc::CheckProc);
        OnProc += AuraProcFn(spell_cold_front_proc::HandleProc);
    }
};

/// ID: 327492 Glacial Fragments
class spell_glacial_fragments : public AuraScript
{
    PrepareAuraScript(spell_glacial_fragments);

    enum eGlacialFragments
    {
        ProcSpell = 327498,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == IceLance;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        auto caster = GetCaster();
        if (!caster)
            return;
        auto target = eventInfo.GetActionTarget();
        if (!target)
            return;

        caster->CastSpell(target, ProcSpell, true);
    }

    void HandleCalcProcChance(ProcEventInfo& eventInfo, float& chance)
    {
        if (!eventInfo.GetSpellInfo() || eventInfo.GetSpellInfo()->Id != IceLance)
            return;

        chance = 20;

        auto caster = GetCaster();
        if (!caster)
            return;
        auto target = eventInfo.GetActionTarget();
        if (!target)
            return;

        if (auto blizzardAT = caster->GetAreaTrigger(Blizzard))
        {
            if (blizzardAT->GetInsideUnits().count(target->GetGUID()))
                chance = 100;
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_glacial_fragments::CheckProc);
        OnProc += AuraProcFn(spell_glacial_fragments::HandleProc);
        OnCalcProcChance += AuraCalcProcChanceFn(spell_glacial_fragments::HandleCalcProcChance);
    }
};

void AddSC_spell_mage_legendary()
{
    RegisterSpellScript(spell_disciplinary_command);
    RegisterSpellScript(spell_expanded_potential);
    RegisterSpellScript(spell_arcane_harmony);
    RegisterSpellScript(spell_fevered_incantation);
    RegisterSpellScript(spell_firestorm);
    RegisterSpellScript(spell_molten_skyfall);
    RegisterSpellScript(spell_molten_skyfall_proc);
    RegisterSpellScript(spell_slick_ice);
    RegisterSpellScript(spell_cold_front);
    RegisterSpellScript(spell_cold_front_proc);
    RegisterSpellScript(spell_glacial_fragments);
}
