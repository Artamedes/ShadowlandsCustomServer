#include "spell_warrior.h"

using namespace Warrior;

/// ID: 335253 Misshapen Mirror
class spell_misshapen_mirror : public AuraScript
{
    PrepareAuraScript(spell_misshapen_mirror);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == SpellReflection;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_misshapen_mirror::CheckProc);
    }
};
/// ID: 335266 Signet of Tormented Kings
class spell_signet_of_tormented_kings : public AuraScript
{
    PrepareAuraScript(spell_signet_of_tormented_kings);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetSpellInfo())
            return false;

        switch (eventInfo.GetSpellInfo()->Id)
        {
            case Bladestorm:
            case BladestormFury:
            case Ravager:
            case Recklessness:
            case Avatar:
                return true;
        }

        return false;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        auto caster = GetCaster();
        if (!caster)
            return;

        if (!eventInfo.GetSpellInfo())
            return;

        std::list<uint32> randSpells;
        if (caster->HasSpell(Ravager))
            randSpells.emplace_back(Ravager);
        else
        {
            if (!IsSpec(caster, SimpleTalentSpecs::Fury))
                randSpells.emplace_back(Bladestorm);
            else
                randSpells.emplace_back(BladestormFury);
        }
        randSpells.emplace_back(Recklessness);
        randSpells.emplace_back(Avatar);

        randSpells.remove_if([eventInfo](uint32 spellId) -> bool
        {
            return eventInfo.GetSpellInfo()->Id == spellId;
        });

        caster->CastSpell(caster, Trinity::Containers::SelectRandomContainerElement(randSpells), CastSpellExtraArgs(true).AddSpellBP0(TRIGGERED_FULL_MASK | TRIGGERED_DONT_CREATE_COOLDOWN | TRIGGERED_IGNORE_SPELL_AND_CATEGORY_CD));
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_signet_of_tormented_kings::CheckProc);
        OnProc += AuraProcFn(spell_signet_of_tormented_kings::HandleProc);
    }
};

/// ID: 335274 Battlelord
class spell_battlelord : public AuraScript
{
    PrepareAuraScript(spell_battlelord);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == Overpower;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto caster = GetCaster())
            caster->GetSpellHistory()->ResetCooldown(MortalStrike);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_battlelord::CheckProc);
        OnProc += AuraProcFn(spell_battlelord::HandleProc);
    }
};

/// ID: 335458 Enduring Blow
class spell_enduring_blow : public AuraScript
{
    PrepareAuraScript(spell_enduring_blow);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == MortalStrike;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto caster = GetCaster())
        {
            if (auto target = eventInfo.GetActionTarget())
            {
                caster->CastSpell(target, ColossusSmash, CastSpellExtraArgs(TRIGGERED_FULL_MASK | TRIGGERED_DONT_CREATE_COOLDOWN | TRIGGERED_IGNORE_SPELL_AND_CATEGORY_CD).AddSpellMod(SpellValueMod::SPELLVALUE_DURATION, 6000));
            }
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_enduring_blow::CheckProc);
        OnProc += AuraProcFn(spell_enduring_blow::HandleProc);
    }
};

/// ID: 335451 Exploiter
class spell_exploiter : public AuraScript
{
    PrepareAuraScript(spell_exploiter);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && (eventInfo.GetSpellInfo()->Id == Execute || eventInfo.GetSpellInfo()->Id == Condemn);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_exploiter::CheckProc);
    }
};

/// ID: 335555 Cadence of Fujieda
class spell_cadence_of_fujieda : public AuraScript
{
    PrepareAuraScript(spell_cadence_of_fujieda);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == Bloodthirst;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_cadence_of_fujieda::CheckProc);
    }
};

/// ID: 335567 Deathmaker
class spell_deathmaker : public AuraScript
{
    PrepareAuraScript(spell_deathmaker);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == Rampage;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto caster = GetCaster())
        {
            if (auto target = eventInfo.GetActionTarget())
            {
                caster->CastSpell(target, Siegebreaker, CastSpellExtraArgs(TRIGGERED_FULL_MASK_NO_CD).AddSpellMod(SpellValueMod::SPELLVALUE_DURATION, 6000));
            }
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_deathmaker::CheckProc);
        OnProc += AuraProcFn(spell_deathmaker::HandleProc);
    }
};

/// ID: 335582 Reckless Defense
class spell_reckless_defense : public AuraScript
{
    PrepareAuraScript(spell_reckless_defense);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == Rampage;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto caster = GetCaster())
        {
            caster->GetSpellHistory()->ModifyCooldown(Recklessness, -1000);
            caster->GetSpellHistory()->ModifyCooldown(EnragedRegeneration, -1000);
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_reckless_defense::CheckProc);
        OnProc += AuraProcFn(spell_reckless_defense::HandleProc);
    }
};

/// ID: 335597 Will of the Berserker
class spell_will_of_the_berserker : public AuraScript
{
    PrepareAuraScript(spell_will_of_the_berserker);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == RagingBlow;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        RefreshDuration();
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_will_of_the_berserker::CheckProc);
        OnProc += AuraProcFn(spell_will_of_the_berserker::HandleProc);
    }
};

/// ID: 335718 Reprisal
class spell_reprisal : public AuraScript
{
    PrepareAuraScript(spell_reprisal);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && (eventInfo.GetSpellInfo()->Id == Charge || eventInfo.GetSpellInfo()->Id == Intervene);
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto caster = GetCaster())
            caster->CastSpell(caster, ShieldBlock, CastSpellExtraArgs(TRIGGERED_FULL_MASK_NO_CD));
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_reprisal::CheckProc);
        OnProc += AuraProcFn(spell_reprisal::HandleProc);
    }
};

/// ID: 335239 The Wall
class spell_the_wall_prot : public AuraScript
{
    PrepareAuraScript(spell_the_wall_prot);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == ShieldSlam;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto caster = GetCaster())
            caster->GetSpellHistory()->ModifyCooldown(ShieldWall, -5000);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_the_wall_prot::CheckProc);
        OnProc += AuraProcFn(spell_the_wall_prot::HandleProc);
    }
};

/// ID: 353577 Glory
class spell_warr_glory : public AuraScript
{
    PrepareAuraScript(spell_warr_glory);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetProcSpell())
            return false;

        auto caster = GetCaster();
        if (!caster)
            return false;

        if (!caster->HasAura(ConquerorsBanner))
            return false;

        if (eventInfo.GetProcSpell()->GetPowerCost(POWER_RAGE))
            return true;

        return false;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetProcSpell())
            return;

        auto caster = GetCaster();
        if (!caster)
            return;

        if (!caster->HasAura(ConquerorsBanner))
            return;

        auto rageCost = eventInfo.GetProcSpell()->GetPowerCost(POWER_RAGE);
        if (!rageCost)
            return;

        _rageSpent += rageCost->Amount / 10;

        uint32 requiredRage = [&]()
        {
            if (IsSpec(caster, SimpleTalentSpecs::Arms))
                return 20;
            else if (IsSpec(caster, SimpleTalentSpecs::ProtWarrior))
                return 10;
            return 25;
        }();

        uint32 durationToAdd = 0;
        while (_rageSpent >= requiredRage)
        {
            _rageSpent -= requiredRage;
            durationToAdd += 500;
        }

        if (durationToAdd)
            if (auto conqBanner = caster->GetAura(ConquerorsBanner))
                conqBanner->ModDuration(durationToAdd);
    }

    uint32 _rageSpent = 0;

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_warr_glory::CheckProc);
        OnProc += AuraProcFn(spell_warr_glory::HandleProc);
    }
};

void AddSC_spell_warrior_legendary()
{
    RegisterSpellScript(spell_misshapen_mirror);
    RegisterSpellScript(spell_signet_of_tormented_kings);
    RegisterSpellScript(spell_battlelord);
    RegisterSpellScript(spell_enduring_blow);
    RegisterSpellScript(spell_exploiter);
    RegisterSpellScript(spell_cadence_of_fujieda);
    RegisterSpellScript(spell_deathmaker);
    RegisterSpellScript(spell_reckless_defense);
    RegisterSpellScript(spell_will_of_the_berserker);
    RegisterSpellScript(spell_reprisal);
    RegisterSpellScript(spell_the_wall_prot);
    RegisterSpellScript(spell_warr_glory);
}
