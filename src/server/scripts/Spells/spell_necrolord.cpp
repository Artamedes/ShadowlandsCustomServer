#include "SpellMgr.h"
#include "Unit.h"
#include "SpellScript.h"
#include "SpellAuras.h"
#include "SpellAuraEffects.h"
#include "SpellHistory.h"
#include "Cell.h"
#include "CellImpl.h"
#include "GridNotifiers.h"

enum Necrolord
{
    Fleshcraft             = 324631,
    FleshcraftPeriodicAura = 350228, ///< Used in fleshcraft to eat the corpses to reduce CD.
    FleshcraftMissle       = 331180,
};

// 324631 
class spell_necrolord_fleshcraft : public AuraScript
{
    PrepareAuraScript(spell_necrolord_fleshcraft);

    enum eFleshcraft
    {
        FleshcraftAura = 324867,
        UltimateForm = 323095,
    };

    int32 amount = 0;

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
        Unit* target = GetTarget();
        if (!target)
            return;

        auto aura = target->GetAura(FleshcraftAura);
        if (!aura)
            aura = target->AddAura(FleshcraftAura);

        if (aura)
        {
            auto effect = aura->GetEffect(0);
            if (effect)
            {
                amount += target->GetMaxHealth() * 0.0666666666667;
                effect->SetAmount(amount);
                aura->SetNeedClientUpdateForTargets();
            }
        }
    }

    void HandleApply(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /* mode */)
    {
        if (!GetCaster())
            return;

        if (!GetCaster()->HasAura(UltimateForm))
            PreventDefaultAction();

        GetCaster()->CastSpell(GetCaster(), FleshcraftPeriodicAura, true);
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_necrolord_fleshcraft::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
        OnEffectApply += AuraEffectApplyFn(spell_necrolord_fleshcraft::HandleApply, EFFECT_2, SPELL_AURA_LINKED_2, AURA_EFFECT_HANDLE_REAL);
    }
};

// not needed
class spell_necrolord_fleshcraft_spellscript : public SpellScript
{
    PrepareSpellScript(spell_necrolord_fleshcraft_spellscript);

    enum Fleshcraft
    {
        FleshcraftAura = 324867,
        UltimateForm = 323095,
    };

    void HandleUltimateForm(SpellEffIndex eff)
    {
        if (GetCaster() && !GetCaster()->HasAura(UltimateForm))
            PreventHitEffect(eff);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_necrolord_fleshcraft_spellscript::HandleUltimateForm, EFFECT_2, SPELL_EFFECT_APPLY_AURA);
    }
};

/// ID - 323089 Travel with Bloop
class spell_travel_with_bloop : public AuraScript
{
    PrepareAuraScript(spell_travel_with_bloop);

    enum TravelWithBloop
    {
        SpeedSpell    = 323399,
        StackingSpell = 323396,
    };

    void HandlePeriodic(AuraEffect const* /*effect*/)
    {
        Unit* caster = GetCaster();
        if (!caster)
            return;

        if (caster->HasAura(SpeedSpell))
            return;

        if (!caster->isMoving())
        {
            bool grantSpeed = false;
            Aura* stackAura = caster->GetAura(StackingSpell);
            if (stackAura)
            {
                if (stackAura->GetStackAmount() >= 4)
                {
                    grantSpeed = true;
                }
            }

            caster->CastSpell(caster, StackingSpell, true);

            if (grantSpeed && stackAura)
            {
                stackAura->Remove();
                caster->CastSpell(caster, SpeedSpell, true);
            }
        }
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_travel_with_bloop::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
    }
};
/// ID: 323916 Sulfuric Emission
class spell_sulfuric_emission : public AuraScript
{
    PrepareAuraScript(spell_sulfuric_emission);

    enum SulfuricEmission
    {
        SulfuricEmissionFear = 324263,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetActionTarget())
            return false;

        if (!eventInfo.GetActionTarget()->HealthBelowPct(21))
            return false;

        return !eventInfo.GetActionTarget()->GetSpellHistory()->HasCooldown(SulfuricEmissionFear);
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();
        if (!eventInfo.GetActionTarget())
            return;

        eventInfo.GetActionTarget()->GetSpellHistory()->AddCooldown(SulfuricEmissionFear, 0, 60s);
        eventInfo.GetActionTarget()->CastSpell(eventInfo.GetActor(), SulfuricEmissionFear, true);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_sulfuric_emission::CheckProc);
        OnProc += AuraProcFn(spell_sulfuric_emission::HandleProc);
    }
};
    
class AnyUnitInRange
{
    public:
        AnyUnitInRange(WorldObject const* obj, float range, bool check3D = true) : i_obj(obj), i_range(range), i_check3D(check3D) { }

        bool operator()(Object* u) const;

    private:
        WorldObject const* i_obj;
        float i_range;
        bool i_check3D;
};

bool AnyUnitInRange::operator()(Object* u) const
{
    if (!u->IsUnit())
        return false;

    if (i_obj->IsWithinDistInMap(u->ToUnit(), i_range, i_check3D))
        return true;
    return false;
}

/// ID: 350228 Fleshcraft
class spell_fleshcraft_consume : public AuraScript
{
    PrepareAuraScript(spell_fleshcraft_consume);

    GuidUnorderedSet consumedCorpses;

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
        auto caster = GetCaster();
        if (!caster)
            return;

        if (caster->GetChannelSpellId() != Necrolord::Fleshcraft)
        {
            Remove();
            return;
        }

        std::list<Unit*> enemyCorpses;
        AnyUnitInRange check(caster, 10.0f, true);
        Trinity::UnitListSearcher<AnyUnitInRange> searcher(caster, enemyCorpses, check);
        Cell::VisitAllObjects(caster, searcher, 10.0f);
        enemyCorpses.remove_if([this, caster](Unit* unit)
        {
            return unit->IsFriendlyTo(caster) || unit->IsAlive() || consumedCorpses.count(unit->GetGUID());
        });

        for (auto enemy : enemyCorpses)
        {
            consumedCorpses.insert(enemy->GetGUID());
            caster->CastSpell(enemy, FleshcraftMissle, true);
        }
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_fleshcraft_consume::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

/// ID: 350229 Fleshcraft
class spell_fleshcraft_cdr : public SpellScript
{
    PrepareSpellScript(spell_fleshcraft_cdr);

    void HandleDummy(SpellEffIndex /*eff*/)
    {
        if (auto caster = GetCaster())
        {
            caster->GetSpellHistory()->ModifyCooldown(Fleshcraft, -1000);
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_fleshcraft_cdr::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};


void AddSC_spell_necrolord()
{
    RegisterSpellAndAuraScriptPairWithArgs(spell_necrolord_fleshcraft_spellscript, spell_necrolord_fleshcraft, "spell_necrolord_fleshcraft");
    RegisterSpellScript(spell_travel_with_bloop);
    RegisterSpellScript(spell_sulfuric_emission);
    RegisterSpellScript(spell_fleshcraft_consume);
    RegisterSpellScript(spell_fleshcraft_cdr);
}
