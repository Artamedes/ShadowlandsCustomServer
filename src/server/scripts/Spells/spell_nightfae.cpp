#include "SpellMgr.h"
#include "Unit.h"
#include "SpellScript.h"

// 320221 
class spell_nightfae_podtender : public AuraScript
{
    PrepareAuraScript(spell_nightfae_podtender);

    enum PodTender
    {
        SpellPod = 320224,
        DepletedShell = 320227,
    };

    void OnAbsorb(AuraEffect* aurEff, DamageInfo& dmgInfo, uint32& absorbAmount)
    {
        if (Unit* caster = GetCaster())
        {
            if (!caster->HasAura(DepletedShell) && dmgInfo.GetDamage() >= caster->GetHealth())
            {
                dmgInfo.AbsorbDamage(dmgInfo.GetDamage());
                PreventDefaultAction();
                caster->CastSpell(caster, SpellPod, true);
                caster->CastSpell(caster, DepletedShell, true);
            }
        }
    }

    void Register() override
    {
        OnEffectAbsorb += AuraEffectAbsorbOverkillFn(spell_nightfae_podtender::OnAbsorb, EFFECT_0);
    }
};

struct npc_regenerating_wild_seed_164589 : public ScriptedAI
{
    public:
        npc_regenerating_wild_seed_164589(Creature* creature) : ScriptedAI(creature) { }

        enum Seed
        {
            SpellWildSeedDeath = 348121,
            DepletedShell = 320227,
        };

        void InitializeAI() override
        {
            me->SetReactState(REACT_PASSIVE);
        }

        void IsSummonedBy(WorldObject* o) override
        {
            if (!o)
                return;

            auto unit = o->ToUnit();
            if (!unit)
                return;

            me->SetLevel(unit->GetLevel());
            me->UpdateLevelDependantStats();
        }

        void JustDied(Unit* /*who*/) override
        {
            if (auto owner = me->GetOwner())
            {
                owner->CastSpell(owner, SpellWildSeedDeath, true);
                me->DespawnOrUnsummon();
            }
        }
};

class unit_script_nightfae : public UnitScript
{
public:
    unit_script_nightfae() : UnitScript("player_script_nightfae") { }

    enum eSpells
    {
        WildHuntTactics = 325066,
        WildHuntTacticsMS = 343594,
        Stratagem = 353286,
        StratagemHealer = 353793,
        StratagemDamage = 353254,
    };

    void OnHeal(Unit* healer, Unit* reciever, uint32& gain) override
    {
        if (!healer || !reciever)
            return;

        if (reciever->HealthBelowPct(36))
        {
            if (healer->HasAura(WildHuntTactics))
            {
                AddPct(gain, 10);
                if (!healer->HasAura(Stratagem))
                    healer->CastSpell(healer, Stratagem, true);
                if (!healer->HasAura(WildHuntTacticsMS))
                    healer->CastSpell(healer, WildHuntTacticsMS, true);
                if (healer->HasAura(Stratagem))
                    healer->CastSpell(reciever, StratagemHealer, true);
            }
        }
    }

    void OnDamage(Unit* attacker, Unit* victim, uint32& damage)
    {
        if (!attacker || !victim)
            return;

        if (victim->HealthAbovePct(69))
        {
            if (attacker->HasAura(WildHuntTactics))
            {
                AddPct(damage, 10);
                if (!attacker->HasAura(Stratagem))
                    attacker->CastSpell(attacker, Stratagem, true);
                if (!attacker->HasAura(WildHuntTacticsMS))
                    attacker->CastSpell(attacker, WildHuntTacticsMS, true);
                if (attacker->HasAura(Stratagem))
                    attacker->CastSpell(victim, StratagemDamage, true);
            }
        }
    }
};

// 310143 
class spell_nightfae_soulshape : public AuraScript
{
    PrepareAuraScript(spell_nightfae_soulshape);

    void HandleApply(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /* mode */)
    {
        // Is this a soulbind? Check plz
        PreventDefaultAction();
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_nightfae_soulshape::HandleApply, EFFECT_5, SPELL_AURA_MOD_UNATTACKABLE, AURA_EFFECT_HANDLE_REAL);
    }
};


// cast 348121 on death
// 320227 - depleted shell

void AddSC_spell_nightfae()
{
    RegisterSpellScript(spell_nightfae_podtender);
    RegisterSpellScript(spell_nightfae_soulshape);

    RegisterCreatureAI(npc_regenerating_wild_seed_164589);

    new unit_script_nightfae();
}
