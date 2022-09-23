#include "spell_dh.h"

using namespace DH;

/// 21832
struct at_glaive_tempest : public AreaTriggerAI
{
public:
    at_glaive_tempest(AreaTrigger* at) : AreaTriggerAI(at)
    {
        // @todo: scale by haste
        at->SetPeriodicProcTimer(1000);

        if (auto caster = at->GetCaster())
            if (auto cycle = caster->GetAuraEffect(DH::eHavocTraits::CycleOfHatred, EFFECT_0))
                caster->GetSpellHistory()->ModifyCooldown(DH::eSpells::EyeBeam, -(cycle->GetAmount()));
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

/// ID - 388116 Shattered Destiny
class spell_shattered_destiny_388116 : public AuraScript
{
    PrepareAuraScript(spell_shattered_destiny_388116);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (auto procSpell = eventInfo.GetProcSpell())
            if (auto powerCost = procSpell->GetPowerCost(Powers::POWER_FURY))
                return powerCost->Amount > 0;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto procSpell = eventInfo.GetProcSpell())
            if (auto powerCost = procSpell->GetPowerCost(Powers::POWER_FURY))
                if (auto caster = GetCaster())
                {
                    _prevFury += powerCost->Amount;
                    auto furyReq = GetEffect(EFFECT_1)->GetAmount();
                    auto newDuration = GetEffect(EFFECT_0)->GetAmount();
                    auto duration = 0u;

                    while (_prevFury >= furyReq)
                    {
                        duration += newDuration;
                    }

                    if (duration > 0)
                    {
                        if (auto aura = caster->GetAura(MetaHavoc))
                            aura->ModDuration(duration);
                    }
                }
    }

    uint32 _prevFury = 0;

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_shattered_destiny_388116::CheckProc);
        OnProc += AuraProcFn(spell_shattered_destiny_388116::HandleProc);
    }
};

/// ID - 389977 Relentless Onslaught
class spell_relentless_onslaught_389977 : public AuraScript
{
    PrepareAuraScript(spell_relentless_onslaught_389977);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == ChaosStrike && roll_chance_i(GetEffect(EFFECT_0)->GetAmount());
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto caster = GetCaster())
            if (auto procSpell = eventInfo.GetProcSpell())
                if (auto target = eventInfo.GetActionTarget())
                    caster->CastSpell(target, procSpell->GetSpellInfo()->Id, true);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_relentless_onslaught_389977::CheckProc);
        OnProc += AuraProcFn(spell_relentless_onslaught_389977::HandleProc);
    }
};

/// ID - 388108 Initiative
class spell_initiative_388108 : public AuraScript
{
    PrepareAuraScript(spell_initiative_388108);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == VengefulRetreat)
        {
            _procTargets.clear();
            return false;
        }

        if (eventInfo.GetProcTarget() == GetCaster() && eventInfo.GetActor())
        {
            _procTargets.insert(eventInfo.GetActor()->GetGUID());
            return false;
        }

        if (auto procTarget = eventInfo.GetProcTarget())
            if (auto caster = GetCaster())
                if (caster != procTarget)
                    if (_procTargets.find(procTarget->GetGUID()) == _procTargets.end())
                    {
                        _procTargets.insert(procTarget->GetGUID());
                        return true;
                    }

        return false;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto caster = GetCaster())
        {
            caster->CastSpell(caster, eHavocTraits::InitiativeProc, true);

            for (auto itr = _procTargets.begin(); itr != _procTargets.end();)
            {
                auto unit = ObjectAccessor::GetUnit(*caster, *itr);
                if (!unit || !unit->IsInCombatWith(caster))
                    itr = _procTargets.erase(itr);
                else
                    ++itr;
            }
        }
    }

    GuidUnorderedSet _procTargets;

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_initiative_388108::CheckProc);
        OnProc += AuraProcFn(spell_initiative_388108::HandleProc);
    }
};

/// ID - 206476 Momentum
class spell_momentum_206476 : public AuraScript
{
    PrepareAuraScript(spell_momentum_206476);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetSpellInfo())
            return false;

        switch (eventInfo.GetSpellInfo()->Id)
        {
            case FelRush:
            case VengefulRetreat:
            case TheHuntNew:
                return true;
        }

        return false;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto caster = GetCaster())
            caster->CastSpell(caster, MomentumProc, true);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_momentum_206476::CheckProc);
        OnProc += AuraProcFn(spell_momentum_206476::HandleProc);
    }
};

void AddSC_spell_dh_havoc()
{
    RegisterAreaTriggerAI(at_glaive_tempest);
    RegisterSpellScript(spell_deadly_dance);
    RegisterSpellScript(spell_dh_serrated_glaive);
    RegisterSpellScript(spell_ragefire_388107);
    RegisterSpellScript(spell_charred_warblades_213010);
    RegisterSpellScript(spell_shattered_destiny_388116);
    RegisterSpellScript(spell_relentless_onslaught_389977);
    RegisterSpellScript(spell_initiative_388108);
    RegisterSpellScript(spell_momentum_206476);
}
