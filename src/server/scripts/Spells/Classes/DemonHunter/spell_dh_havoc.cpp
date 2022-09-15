#include "spell_dh.h"

using namespace DH;

/// 21832
struct at_glaive_tempest : public AreaTriggerAI
{
public:
    at_glaive_tempest(AreaTrigger* at) : AreaTriggerAI(at)
    {
        at->SetPeriodicProcTimer(100); ///< Custom HASTe
    }

    enum eGlaiveTempest
    {
        GlaiveTempestDmg = 342857,
    };

    void OnPeriodicProc() override
    {
        auto caster = at->GetCaster();
        if (!caster)
            return;

        caster->CastSpell(*at, GlaiveTempestDmg, true);
    }
};

/// ID: 363736 Deadly Dance
class spell_deadly_dance : public AuraScript
{
    PrepareAuraScript(spell_deadly_dance);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetProcSpell() && eventInfo.GetProcSpell()->GetPowerCost(POWER_FURY);
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto spell = eventInfo.GetProcSpell())
        {
            if (auto cost = eventInfo.GetProcSpell()->GetPowerCost(POWER_FURY))
            {
                usedFury += cost->Amount;
                while (usedFury >= 60)
                {
                    usedFury -= 60;
                    if (auto caster = GetCaster())
                        caster->GetSpellHistory()->ModifyCooldown(Metamorphosis, -1000);
                }
            }
        }
    }

    uint32 usedFury = 0;

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_deadly_dance::CheckProc);
        OnProc += AuraProcFn(spell_deadly_dance::HandleProc);
    }
};

// ID - 339230 Serrated Glaive
class spell_dh_serrated_glaive : public AuraScript
{
    PrepareAuraScript(spell_dh_serrated_glaive);

    enum eSerratedGlaive
    {
        ExposedWound = 339229,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == ThrowGlaive)
            return true;
        return false;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();

        if (auto caster = GetCaster())
        {
            if (auto target = eventInfo.GetActionTarget())
            {
                if (auto eff = GetEffect(EFFECT_0))
                    if (eff->ConduitRankEntry)
                        caster->CastSpell(target, ExposedWound, CastSpellExtraArgs(true).AddSpellBP0(eff->ConduitRankEntry->AuraPointsOverride));
            }
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_dh_serrated_glaive::CheckProc);
        OnProc += AuraProcFn(spell_dh_serrated_glaive::HandleProc);
    }
};

/// ID - 388107 Ragefire
class spell_ragefire_388107 : public AuraScript
{
    PrepareAuraScript(spell_ragefire_388107);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == ImmolationAuraDmg;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto caster = GetCaster())
        {
            if (auto dmgInfo = eventInfo.GetDamageInfo())
            {
                if (auto aura = caster->GetAura(eHavocTraits::RagefireAura))
                    if (auto eff = aura->GetEffect(EFFECT_0))
                        eff->ChangeAmount(eff->GetAmount() + dmgInfo->GetDamage());
            }
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_ragefire_388107::CheckProc);
        OnProc += AuraProcFn(spell_ragefire_388107::HandleProc);
    }
};

/// ID - 213010 Charred Warblades
class spell_charred_warblades_213010 : public AuraScript
{
    PrepareAuraScript(spell_charred_warblades_213010);

    enum eCharredWarblades
    {
        CharredWarbladeHeal = 213011,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetDamageInfo() && eventInfo.GetSchoolMask() & SpellSchoolMask::SPELL_SCHOOL_MASK_FIRE;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto caster = GetCaster())
            if (auto dmgInfo = eventInfo.GetDamageInfo())
            {
                caster->CastSpell(caster, CharredWarbladeHeal, CastSpellExtraArgs(true).AddSpellBP0(CalculatePct(dmgInfo->GetDamage(), 5)));
            }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_charred_warblades_213010::CheckProc);
        OnProc += AuraProcFn(spell_charred_warblades_213010::HandleProc);
    }
};

void AddSC_spell_dh_havoc()
{
    RegisterAreaTriggerAI(at_glaive_tempest);
    RegisterSpellScript(spell_deadly_dance);
    RegisterSpellScript(spell_dh_serrated_glaive);
    RegisterSpellScript(spell_ragefire_388107);
    RegisterSpellScript(spell_charred_warblades_213010);
}
