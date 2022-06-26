#include "SpellIncludes.h"

enum eHavoc
{
    Metamorphosis = 162264,
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

void AddSC_spell_dh_havoc()
{
    RegisterAreaTriggerAI(at_glaive_tempest);
    RegisterSpellScript(spell_deadly_dance);
}
