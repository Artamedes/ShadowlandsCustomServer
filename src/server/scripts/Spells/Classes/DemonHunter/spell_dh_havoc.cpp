#include "SpellIncludes.h"

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

void AddSC_spell_dh_havoc()
{
    RegisterAreaTriggerAI(at_glaive_tempest);
}
