#include "SpellIncludes.h"

/// ID: 101546 Spinning Crane Kick
class spell_spinning_crane_kick : public AuraScript
{
    PrepareAuraScript(spell_spinning_crane_kick);

    enum eSpinningCraneKick
    {
        DanceOfChiJi = 325202,
    };

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        auto caster = GetCaster();
        if (!caster)
            return;

        caster->RemoveAurasDueToSpell(DanceOfChiJi);
    }

    void Register() override
    {
        OnEffectRemove += AuraEffectApplyFn(spell_spinning_crane_kick::HandleRemove, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL, AURA_EFFECT_HANDLE_REAL);
    }
};

// 115636 - Mastery - Combo Strike
// very pig!
class monk_mastery_combo_strike : public UnitScript
{
public:
    monk_mastery_combo_strike() : UnitScript("monk_mastery_combo_strike") { }

    enum UsedSpells
    {
        SPELL_MONK_MASTERY_COMBO_STRIKE = 115636,
        SPELL_MONK_HIT_COMBO            = 196740,
        SPELL_MONK_HIT_COMBO_AURA       = 196741
    };

    void ModifySpellDamageTaken(Unit* /*target*/, Unit* attacker, int32& damage, SpellInfo const* spellInfo) override
    {
        if (!spellInfo)
            return;

        if (!attacker)
            return;

        if (attacker->GetClass() != CLASS_MONK)
            return;

        if (!IsSpec(attacker, SimpleTalentSpecs::Windwalker))
            return;

        if (Aura* aura = attacker->GetAura(SPELL_MONK_MASTERY_COMBO_STRIKE))
        {
            uint32 lastUsedSpellId = attacker->Variables.GetValue<uint32>("monk_mastery_combo_strike", uint32(0));
            if (lastUsedSpellId != spellInfo->Id)
            {
                AddPct(damage, aura->GetEffect(EFFECT_0)->GetAmount());
                attacker->Variables.Set("monk_mastery_combo_strike", spellInfo->Id);
                if (attacker->HasAura(SPELL_MONK_HIT_COMBO))
                    attacker->CastSpell(attacker, SPELL_MONK_HIT_COMBO_AURA, true);
            }
        }
    }
};

/// ID: 363734 Primordial Potential
class spell_primordial_potential : public AuraScript
{
    PrepareAuraScript(spell_primordial_potential);

    enum ePrimordialPotential
    {
        OffensiveAbilitiesUsed = 363911,
        PrimordialPower = 363924,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetProcSpell() && !eventInfo.GetProcSpell()->IsTriggered();
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        auto caster = GetCaster();
        if (!caster)
            return;

        caster->CastSpell(caster, OffensiveAbilitiesUsed, true);

        if (auto aura = caster->GetAura(OffensiveAbilitiesUsed))
        {
            if (aura->GetStackAmount() >= 10)
            {
                aura->Remove();
                caster->CastSpell(caster, PrimordialPower, CastSpellExtraArgs(true).AddSpellMod(SpellValueMod::SPELLVALUE_AURA_STACK, 3));
            }
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_primordial_potential::CheckProc);
        OnProc += AuraProcFn(spell_primordial_potential::HandleProc);
    }
};

/// ID: 363924 Primordial Power
class spell_primordial_power : public AuraScript
{
    PrepareAuraScript(spell_primordial_power);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetSpellInfo())
            return false;

        switch (eventInfo.GetSpellInfo()->Id)
        {
            case 100780: ///< - Tiger Palm
            case 100784: ///< - Blackout Kick
            case 107270: ///< - Spinning Crane Kick
            case 113656: ///< - Fists of Fury
            case 115181: ///< - Breath of Fire
            case 117418: ///< - Fists of Fury
            case 117952: ///< - Crackling Jade Lightning
            case 121253: ///< - Keg Smash
            case 123586: ///< - Flying Serpent Kick
            case 124081: ///< - Zen Pulse
            case 132467: ///< - Chi Wave
            case 148135: ///< - Chi Burst
            case 148187: ///< - Rushing Jade Wind
            case 158221: ///< - Whirling Dragon Punch
            case 185099: ///< - Rising Sun Kick
            case 196608: ///< - Eye of the Tiger
            case 196733: ///< - Special Delivery
            case 196748: ///< - Chi Orbit
            case 205523: ///< - Blackout Kick
            case 228649: ///< - Blackout Kick
            case 261947: ///< - Fist of the White Tiger
            case 261977: ///< - Fist of the White Tiger
            case 275673: ///< - Sunrise Technique
            case 287606: ///< - Fists of Insane Fury
            case 288636: ///< - Glory of the Dawn
            case 327264: ///< - Faeline Stomp(Night Fae)
            case 330901: ///< - Spinning Crane Kick
            case 330903: ///< - Spinning Crane Kick
            case 330907: ///< - Breath of Fire
            case 330911: ///< - Keg Smash
            case 331433: ///< - Tiger Palm
            case 331536: ///< - Corrosive Dosage
            case 337342: ///< - Chi Explosion
            case 345714: ///< - Fists of Fury
            case 345727: ///< - Faeline Stomp(Night Fae)
                return true;
            default:
                return false;
        }
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto aur = GetAura())
            aur->DropStack();
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_primordial_power::CheckProc);
        OnProc += AuraProcFn(spell_primordial_power::HandleProc);
    }
};

void AddSC_spell_monk_windwalker()
{
    RegisterSpellScript(spell_spinning_crane_kick);
    RegisterSpellScript(spell_primordial_potential);
    RegisterSpellScript(spell_primordial_power);

    new monk_mastery_combo_strike();
}
