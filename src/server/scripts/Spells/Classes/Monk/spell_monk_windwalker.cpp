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

void AddSC_spell_monk_windwalker()
{
    RegisterSpellScript(spell_spinning_crane_kick);

    new monk_mastery_combo_strike();
}
