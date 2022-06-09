#include "SpellIncludes.h"

enum Assassination
{
    Rupture = 1943,
    Envenom = 32645,
};


enum PoisonBomb
{
    PoisonBombAura = 255544,
    PoisonBombPool = 255545,
    PoisonBombDmg  = 255546,
};

/// 255544 - Poison Bomb
/// Last Update - 9.2.5.44061
class aura_rog_poison_bomb : public AuraScript
{
    PrepareAuraScript(aura_rog_poison_bomb);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        auto caster = GetCaster();
        if (!caster)
            return false;

        if (!eventInfo.GetSpellInfo())
            return false;

        switch (eventInfo.GetSpellInfo()->Id)
        {
            case Assassination::Rupture:
            case Assassination::Envenom:
                if (caster->Variables.Exist("CP"))
                {
                    auto cp = caster->Variables.GetValue<uint8>("CP", 0);
                    return roll_chance_i(cp * 4);
                }
                break;
            default:
                break;
        }

        return false;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();
        Unit* target = eventInfo.GetActionTarget();
        if (!caster || !target)
            return;

        caster->CastSpell(target, PoisonBombPool, true);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_rog_poison_bomb::CheckProc);
        OnProc += AuraProcFn(aura_rog_poison_bomb::HandleProc);
    }
};

/// 11866 - Poison Bomb
/// Last Update - 9.2.5.44061
struct at_rogue_poison_bomb : AreaTriggerAI
{
    at_rogue_poison_bomb(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger)
    {
        // How often should the action be executed
        ///< Custom HASTE - set periodic timer to 50, originally is 1000
        areatrigger->SetPeriodicProcTimer(50);
    }

    void OnPeriodicProc() override
    {
        if (Unit* caster = at->GetCaster())
            caster->CastSpell(at->GetPosition(), PoisonBombDmg, true);
    }
};

void AddSC_spell_rogue_assassination()
{
    RegisterSpellScript(aura_rog_poison_bomb);

    RegisterAreaTriggerAI(at_rogue_poison_bomb); // 16552
}
