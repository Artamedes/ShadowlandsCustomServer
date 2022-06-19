#include "SpellIncludes.h"
#include "spell_rogue.h"
#include "PathGenerator.h"

enum eOutlaw
{
    /// Generators
    SinisterStrike = 193315,
    PistolShot     = 185763,
    GhostlyStrike  = 196937,
    /// Finishers
    Dispatch       = 2098,
    BetweenTheEyes = 315341,
    SliceAndDice   = 315496,
    /// Conduits
    CountTheOdds = 341546,
    SleightOfHand = 341543,
    /// Procs
    Opportunity = 195627,
    TornadoTriggerStack = 364234,
    TornadoTriggerBlast = 364556,
    /// Legendaries
    ConcealedBlunderbuss = 340088,
    ConcealedBlunderbussProc = 340587,
    GreenskinWickers = 340085,
    GreenskinWickersProc = 340573,

    MainGaucheDmg = 86392, ///< Mastery Proc
};

enum RollTheBones
{
    SPELL_ROGUE_SKULL_AND_CROSSBONES = 199603,
    SPELL_ROGUE_GRAND_MELEE          = 193358,
    SPELL_ROGUE_RUTHLESS_PRECISION   = 193357,
    SPELL_ROGUE_TRUE_BEARING         = 193359,
    SPELL_ROGUE_BURIED_TREASURE      = 199600,
    SPELL_ROGUE_BROADSIDE            = 193356,
};

static uint32 constexpr RTBSpells[] = { SPELL_ROGUE_SKULL_AND_CROSSBONES, SPELL_ROGUE_GRAND_MELEE, SPELL_ROGUE_RUTHLESS_PRECISION,
    SPELL_ROGUE_TRUE_BEARING, SPELL_ROGUE_BURIED_TREASURE, SPELL_ROGUE_BROADSIDE };

/// <summary>
/// Apples count the odds when you use a spell like Ambush or Dispatch
/// Calculates their conduit level to see what they roll
/// </summary>
/// <param name="caster">The caster who casted the spell</param>
void ApplyCountTheOdds(Unit* caster)
{
    if (caster && IsSpec(caster, SimpleTalentSpecs::Outlaw))
    {
        if (auto countTheOdds = caster->GetAuraEffect(CountTheOdds, EFFECT_0))
        {
            bool stealthed = caster->HasAuraType(AuraType::SPELL_AURA_MOD_STEALTH);

            float chance = countTheOdds->ConduitRankEntry ? countTheOdds->ConduitRankEntry->AuraPointsOverride : 0.0f;
            uint32 duration = 5000;

            if (caster->HasAuraType(AuraType::SPELL_AURA_MOD_STEALTH))
            {
                chance *= 3.0f;
                duration *= 3;
            }

            if (chance > 100.0f)
                chance = 100.0f;

            if (roll_chance_f(chance))
            {
                std::vector<uint32> NotHaveRTBBuffs;
                for (uint32 spellId : RTBSpells)
                {
                    if (!caster->GetAura(spellId))
                    {
                        NotHaveRTBBuffs.push_back(spellId);
                    }
                }

                if (!NotHaveRTBBuffs.empty())
                {
                    caster->CastSpell(caster, Trinity::Containers::SelectRandomContainerElement(NotHaveRTBBuffs), CastSpellExtraArgs(true).AddSpellMod(SpellValueMod::SPELLVALUE_DURATION, duration));
                }
            }
        }
    }
}

/// 315508 - Roll the Bones
/// Valid 9.2.5.44061
class spell_rog_roll_the_bones : public SpellScript
{
    PrepareSpellScript(spell_rog_roll_the_bones);

    void HandleDummy(SpellEffIndex /*effIndex*/)
    {
        int32 currentDuration = 0;
        for (uint32 spellId : RTBSpells)
        {
            if (Aura* aura = GetCaster()->GetAura(spellId))
            {
                currentDuration = aura->GetDuration();
                GetCaster()->RemoveAura(aura);
            }
        }

        currentDuration = std::min(5000, currentDuration);

        std::vector<uint32> possibleBuffs(std::begin(RTBSpells), std::end(RTBSpells));
        Trinity::Containers::RandomShuffle(possibleBuffs);

        // https://www.icy-veins.com/wow/outlaw-rogue-pve-dps-rotation-cooldowns-abilities
        // 1 Roll the Bones buff  : 100.0 % chance;
        // 2 Roll the Bones buffs : 19 % chance;
        // 5 Roll the Bones buffs : 1 % chance.
        int32 chance = irand(1, 100);
        int32 numBuffs = 1;
        if (chance <= 1)
            numBuffs = 5;
        else if (chance <= 20)
            numBuffs = 2;

        if (numBuffs < 5)
            if (auto sleightOfHand = GetCaster()->GetAuraEffect(SleightOfHand, EFFECT_0))
                if (roll_chance_i(std::min(100, sleightOfHand->GetAmount())))
                    numBuffs++;

        for (int32 i = 0; i < numBuffs; ++i)
        {
            uint32 spellId = possibleBuffs[i];
            CastSpellExtraArgs args(true);
            args.AddSpellMod(SPELLVALUE_DURATION, GetSpellInfo()->GetDuration() + currentDuration);
            GetCaster()->CastSpell(GetCaster(), spellId, args);
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_rog_roll_the_bones::HandleDummy, EFFECT_0, SPELL_EFFECT_APPLY_AURA);
    }
};

/// ID: 8676 Ambush
/// Used for Count the Odds conduit
class spell_ambush : public SpellScript
{
    PrepareSpellScript(spell_ambush);

    void HandleDummy(SpellEffIndex /*eff*/)
    {
        if (GetCaster())
            ApplyCountTheOdds(GetCaster());
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_ambush::HandleDummy, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

/// ID: 2098 Dispatch
/// Used for Count the Odds Conduit
class spell_dispatch : public SpellScript
{
    PrepareSpellScript(spell_dispatch);

    void HandleDummy(SpellEffIndex /*eff*/)
    {
        if (GetCaster())
            ApplyCountTheOdds(GetCaster());
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_dispatch::HandleDummy, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

/// ID: 195457 Grappling Hook
/// 
class spell_grappling_hook : public SpellScript
{
    PrepareSpellScript(spell_grappling_hook);

    enum eGrapple
    {
        GrappleTrigger = 227180,
        Harpoon = 348486,
    };

    SpellCastResult CheckElevation()
    {
        if (WorldLocation const* dest = GetExplTargetDest())
        {
            if (GetCaster()->HasUnitMovementFlag(MOVEMENTFLAG_ROOT))
                return SPELL_FAILED_ROOTED;

            if (GetCaster()->GetMap()->Instanceable())
            {
                float range = GetSpellInfo()->GetMaxRange(true, GetCaster()) * 1.5f;

                PathGenerator generatedPath(GetCaster());
                generatedPath.SetPathLengthLimit(range);

                bool result = generatedPath.CalculatePath(dest->GetPositionX(), dest->GetPositionY(), dest->GetPositionZ(), false, true);
                if (generatedPath.GetPathType() & PATHFIND_SHORT)
                    return SPELL_FAILED_OUT_OF_RANGE;
                else if (!result || generatedPath.GetPathType() & PATHFIND_NOPATH)
                {
                    result = generatedPath.CalculatePath(dest->GetPositionX(), dest->GetPositionY(), dest->GetPositionZ(), false, false);
                    if (generatedPath.GetPathType() & PATHFIND_SHORT)
                        return SPELL_FAILED_OUT_OF_RANGE;
                    else if (!result || generatedPath.GetPathType() & PATHFIND_NOPATH)
                        return SPELL_FAILED_NOPATH;
                }
            }
            else if (dest->GetPositionZ() > GetCaster()->GetPositionZ() + 14.0f)
                return SPELL_FAILED_NOPATH;

            return SPELL_CAST_OK;
        }

        return SPELL_FAILED_NO_VALID_TARGETS;
    }

    void HandleDummy(SpellEffIndex /*eff*/)
    {
        auto caster = GetCaster();
        auto hitDest = GetHitDest();

        if (!caster || !hitDest)
            return;

        caster->CastSpell(*hitDest, GrappleTrigger, true);
    }

    void Register() override
    {
        OnCheckCast += SpellCheckCastFn(spell_grappling_hook::CheckElevation);
        OnEffectHit += SpellEffectFn(spell_grappling_hook::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

/// ID: 343142 Dreadblades
/// Used for preventing proccing from every spell. Should only proc from outlaw generators.
/// Also have to damage self on using finishing move.
class spell_dreadblades : public AuraScript
{
    PrepareAuraScript(spell_dreadblades);

    enum eDreadblades
    {
        DreadbladesEnergize = 343143,
        DreadbladesDmgSelf  = 343145,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetSpellInfo())
            return false;

        switch (eventInfo.GetSpellInfo()->Id)
        {
            /// Generators
            case SinisterStrike:
            case PistolShot:
            case GhostlyStrike:
            case EchoingReprimand:
            case Sepsis:
            case SerratedBoneSpike:
            /// Finishers
            case Dispatch:
            case BetweenTheEyes:
            case SliceAndDice:
                return true;
            default:
                return false;
        }
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();

        if (!eventInfo.GetSpellInfo())
            return;

        if (!eventInfo.GetActor())
            return;

        switch (eventInfo.GetSpellInfo()->Id)
        {
            case SinisterStrike:
            case PistolShot:
            case GhostlyStrike:
            case EchoingReprimand:
            case Sepsis:
            case SerratedBoneSpike:
            {
                eventInfo.GetActor()->CastSpell(eventInfo.GetActor(), DreadbladesEnergize, true);
                break;
            }
            case Dispatch:
            case BetweenTheEyes:
            case SliceAndDice:
            {
                eventInfo.GetActor()->CastSpell(eventInfo.GetActor(), DreadbladesDmgSelf, true);
                break;
            }
            default:
                break;
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_dreadblades::CheckProc);
        OnProc += AuraProcFn(spell_dreadblades::HandleProc);
    }
};

/// ID: 343145 Dreadblades
class spell_dreadblades_self_dmg : public SpellScript
{
    PrepareSpellScript(spell_dreadblades_self_dmg);

    void HandleDmg(SpellEffIndex /*eff*/)
    {
        if (auto caster = GetCaster())
        {
            SetHitDamage(caster->CountPctFromCurHealth(5));
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_dreadblades_self_dmg::HandleDmg, EFFECT_1, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

/// ID: 193315 Sinister Strike
class spell_sinister_strike : public SpellScript
{
    PrepareSpellScript(spell_sinister_strike);

    enum eSinisterStrike
    {
        WeaponMaster = 200733,
    };

    void HandleDummy(SpellEffIndex /*eff*/)
    {
        auto caster = GetCaster();
        if (!caster)
            return;
        auto hitUnit = GetHitUnit();
        if (!hitUnit)
            return;

        uint32 chance = 35.0f;
        if (caster->HasAura(WeaponMaster))
            chance += 10.0f;

        if (roll_chance_i(chance))
        {
            caster->CastSpell(hitUnit, SinisterStrike, true);
            caster->CastSpell(caster, Opportunity, true);

            if (caster->HasAura(ConcealedBlunderbuss) && roll_chance_i(40))
            {
                caster->CastSpell(caster, ConcealedBlunderbussProc, true);
            }
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_sinister_strike::HandleDummy, EFFECT_3, SPELL_EFFECT_DUMMY);
    }
};

/// ID: 195627 Opportunity
class spell_opportunity : public AuraScript
{
    PrepareAuraScript(spell_opportunity);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetDamageInfo() && eventInfo.GetDamageInfo()->GetDamage() > 0 && eventInfo.GetSpellInfo()->Id == PistolShot;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();
        Remove();
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_opportunity::CheckProc);
        OnProc += AuraProcFn(spell_opportunity::HandleProc);
    }
};

/// ID: 76806 Mastery: Main Gauche
class spell_mastery_main_gauche : public AuraScript
{
    PrepareAuraScript(spell_mastery_main_gauche);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetSpellInfo())
        {
            switch (eventInfo.GetSpellInfo()->Id)
            {
                case MainGaucheDmg:
                    return false;
                default:
                    break;
            }
        }

        return roll_chance_i(30);
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();
        if (auto target = eventInfo.GetActionTarget())
        {
            if (auto caster = GetCaster())
            {
                auto dam = CalculatePct(caster->GetTotalAttackPowerValue(WeaponAttackType::OFF_ATTACK), 145);
                caster->CastSpell(target, MainGaucheDmg, CastSpellExtraArgs(true).AddSpellBP0(dam));
            }
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_mastery_main_gauche::CheckProc);
        OnProc += AuraProcFn(spell_mastery_main_gauche::HandleProc);
    }
};

/// ID: 364555 Tornado Trigger
class spell_tornado_trigger : public AuraScript
{
    PrepareAuraScript(spell_tornado_trigger);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetSpellInfo())
            return false;

        return eventInfo.GetSpellInfo()->Id == MainGaucheDmg;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto caster = GetCaster())
        {
            if (auto target = eventInfo.GetActionTarget())
            {
                caster->CastSpell(target, PistolShot, true);
            }
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_tornado_trigger::CheckProc);
        OnProc += AuraProcFn(spell_tornado_trigger::HandleProc);
    }
};

/// ID: 363592 Tornado Trigger
class spell_tornado_trigger_4pc : public AuraScript
{
    PrepareAuraScript(spell_tornado_trigger_4pc);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == PistolShot && eventInfo.GetDamageInfo() && eventInfo.GetDamageInfo()->GetDamage();
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();
        if (auto caster = GetCaster())
        {
            if (auto target = eventInfo.GetActionTarget())
            {
                caster->CastSpell(caster, TornadoTriggerStack, true);

                if (auto aur = caster->GetAura(TornadoTriggerStack))
                {
                    if (aur->GetStackAmount() >= 6)
                    {
                        caster->CastSpell(caster, TornadoTriggerBlast, true);
                        aur->Remove();
                    }
                }
            }
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_tornado_trigger_4pc::CheckProc);
        OnProc += AuraProcFn(spell_tornado_trigger_4pc::HandleProc);
    }
};

/// ID: 185763 Pistol Shot
class spell_pistol_shot : public SpellScript
{
    PrepareSpellScript(spell_pistol_shot);

    void HandleDummy(SpellEffIndex /*eff*/)
    {
        if (auto caster = GetCaster())
        {
            if (auto hitUnit = GetHitUnit())
            {
                if (auto aur = caster->GetAura(TornadoTriggerBlast))
                {
                    auto prevComboPoints = caster->GetComboPoints();
                    caster->SetPower(Powers::POWER_COMBO_POINTS, caster->GetMaxPower(Powers::POWER_COMBO_POINTS));
                    caster->CastSpell(hitUnit, BetweenTheEyes, true);
                    caster->SetPower(Powers::POWER_COMBO_POINTS, prevComboPoints);
                    aur->Remove();
                }
                if (auto aur = caster->GetAura(ConcealedBlunderbussProc))
                {
                    /// Fire 2 additional times
                    caster->CastSpell(hitUnit, PistolShot, true);
                    caster->CastSpell(hitUnit, PistolShot, true);
                    aur->Remove();
                }
                if (auto aur = caster->GetAura(GreenskinWickersProc))
                    aur->Remove();
            }
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_pistol_shot::HandleDummy, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

/// ID: 340085 Greenskin's Wickers
class spell_greenskins_wickers : public AuraScript
{
    PrepareAuraScript(spell_greenskins_wickers);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetProcSpell() && eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == BetweenTheEyes && roll_chance_i(std::min(100, eventInfo.GetProcSpell()->GetUsedComboPoints() * 20));
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto caster = GetCaster())
        {
            caster->CastSpell(caster, GreenskinWickersProc, true);
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_greenskins_wickers::CheckProc);
        OnProc += AuraProcFn(spell_greenskins_wickers::HandleProc);
    }
};

void AddSC_spell_rogue_outlaw()
{
    RegisterSpellScript(spell_rog_roll_the_bones);
    RegisterSpellScript(spell_ambush);
    RegisterSpellScript(spell_dispatch);
    RegisterSpellScript(spell_grappling_hook);
    RegisterSpellScript(spell_dreadblades);
    RegisterSpellScript(spell_dreadblades_self_dmg);
    RegisterSpellScript(spell_sinister_strike);
    RegisterSpellScript(spell_opportunity);
    RegisterSpellScript(spell_mastery_main_gauche);
    RegisterSpellScript(spell_tornado_trigger);
    RegisterSpellScript(spell_tornado_trigger_4pc);
    RegisterSpellScript(spell_pistol_shot);
    RegisterSpellScript(spell_greenskins_wickers);
}
