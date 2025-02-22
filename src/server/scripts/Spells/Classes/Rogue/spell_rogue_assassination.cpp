#include "spell_rogue.h"

using namespace Rogue;

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
            case Rupture:
            case Envenom:
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

/// ID: 340082 Doomblade
class spell_doomblade : public AuraScript
{
    PrepareAuraScript(spell_doomblade);

    enum eDoomblade
    {
        MutilatedFlesh = 340431,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == MutilateDmg && eventInfo.GetDamageInfo() && eventInfo.GetDamageInfo()->GetDamage();
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto caster = GetCaster())
        {
            if (auto target = eventInfo.GetActionTarget())
            {
                if (eventInfo.GetDamageInfo())
                    caster->CastSpell(target, MutilatedFlesh, CastSpellExtraArgs(true).AddSpellBP0(CalculatePct(eventInfo.GetDamageInfo()->GetDamage(), 45)));
            }
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_doomblade::CheckProc);
        OnProc += AuraProcFn(spell_doomblade::HandleProc);
    }
};

// 79134 - Venomous Wounds
class aura_rog_venomous_wounds : public AuraScript
{
    PrepareAuraScript(aura_rog_venomous_wounds);

    enum eVenomousWounds
    {
        VenomousVin = 51637,
    };

	bool CheckProc(ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();
        Unit* target = eventInfo.GetActionTarget();
        if (!caster || !target)
            return false;

        if (!eventInfo.GetSpellInfo())
            return false;

        switch (eventInfo.GetSpellInfo()->Id)
        {
            case Garrote:
            case Rupture:
            case InternalBleedingDot:
                if (target->HasAuraWithDispelFlagsFromCaster(caster, DISPEL_POISON, false))
                    return true;
            default:
                return false;
        }

		return false;
	}

    void HandleProc(ProcEventInfo& /*procInfo*/)
    {
        Unit* caster = GetCaster();
        if (!caster)
            return;

        caster->CastSpell(caster, VenomousVin, true);
    }

    void Register() override
    {
		DoCheckProc += AuraCheckProcFn(aura_rog_venomous_wounds::CheckProc);
        OnProc += AuraProcFn(aura_rog_venomous_wounds::HandleProc);
    }
};

constexpr uint32 MaimMangleConduit = 341538;

/// ID: 5374 Mutilate
class spell_mutilate_5374 : public SpellScript
{
    PrepareSpellScript(spell_mutilate_5374);

    void HandleDmg(SpellEffIndex /*eff*/)
    {
        if (auto caster = GetCaster())
        {
            if (auto hitUnit = GetHitUnit())
            {
                if (auto eff = caster->GetAuraEffect(MaimMangleConduit, EFFECT_0))
                {
                    if (hitUnit->HasAura(Garrote, caster->GetGUID()))
                    {
                        if (eff->ConduitRankEntry)
                        {
                            auto dmg = GetHitDamage();
                            AddPct(dmg, eff->ConduitRankEntry->AuraPointsOverride);
                            SetHitDamage(dmg);
                        }
                    }
                }
            }
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_mutilate_5374::HandleDmg, EFFECT_1, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

/// ID: 27576 Mutilate
class spell_mutilate_27576 : public SpellScript
{
    PrepareSpellScript(spell_mutilate_27576);

    void HandleDmg(SpellEffIndex /*eff*/)
    {
        if (auto caster = GetCaster())
        {
            if (auto hitUnit = GetHitUnit())
            {
                if (auto eff = caster->GetAuraEffect(MaimMangleConduit, EFFECT_0))
                {
                    if (hitUnit->HasAura(Garrote, caster->GetGUID()))
                    {
                        if (eff->ConduitRankEntry)
                        {
                            auto dmg = GetHitDamage();
                            AddPct(dmg, eff->ConduitRankEntry->AuraPointsOverride);
                            SetHitDamage(dmg);
                        }
                    }
                }
            }
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_mutilate_27576::HandleDmg, EFFECT_1, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

void AddSC_spell_rogue_assassination()
{
    RegisterSpellScript(aura_rog_poison_bomb);
    RegisterSpellScript(spell_doomblade);
    RegisterSpellScript(aura_rog_venomous_wounds);
    RegisterSpellScript(spell_mutilate_5374);
    RegisterSpellScript(spell_mutilate_27576);
        
    RegisterAreaTriggerAI(at_rogue_poison_bomb); // 16552
}
