#include "SpellIncludes.h"

enum eHavoc
{
    Metamorphosis = 162264,

    ThrowGlaive = 185123,
};

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

void AddSC_spell_dh_havoc()
{
    RegisterAreaTriggerAI(at_glaive_tempest);
    RegisterSpellScript(spell_deadly_dance);
    RegisterSpellScript(spell_dh_serrated_glaive);
}
