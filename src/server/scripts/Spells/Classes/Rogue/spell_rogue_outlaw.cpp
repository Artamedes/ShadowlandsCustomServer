#include "SpellIncludes.h"
#include "PathGenerator.h"

enum eOutlaw
{
    CountTheOdds = 341546,
    SleightOfHand = 341543,
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

void ApplyCountTheOdds(Unit* caster)
{
    if (caster && IsSpec(caster, SimpleTalentSpecs::Outlaw))
    {
        if (auto countTheOdds = caster->GetAuraEffect(CountTheOdds, EFFECT_0))
        {
            bool stealthed = caster->HasAuraType(AuraType::SPELL_AURA_MOD_STEALTH);

            uint32 chance = countTheOdds->GetAmount();
            uint32 duration = 5000;

            if (caster->HasAuraType(AuraType::SPELL_AURA_MOD_STEALTH))
            {
                chance *= 3;
                duration *= 3;
            }

            if (chance > 100)
                chance = 100;

            if (roll_chance_i(chance))
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
                    CastSpellExtraArgs args(true);
                    args.AddSpellMod(SPELLVALUE_DURATION, duration);
                    caster->CastSpell(caster, Trinity::Containers::SelectRandomContainerElement(NotHaveRTBBuffs), args);
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

void AddSC_spell_rogue_outlaw()
{
    RegisterSpellScript(spell_rog_roll_the_bones);
    RegisterSpellScript(spell_ambush);
    RegisterSpellScript(spell_dispatch);
    RegisterSpellScript(spell_grappling_hook);
}
