#pragma once

#include "SpellIncludes.h"

namespace Mage
{
    enum eSpells
    {
        ArcaneExplosion    = 1449,
        ArcaneIntellect    = 1459,
        ConjureRefreshment = 19036,
        CounterSpell       = 2139,
        FrostNova          = 122,
        FrostBolt          = 116,
        IceBlock           = 45438,
        Invisiblity        = 66,
        MirrorImage        = 55342,
        Polymorph          = 118,
        RemoveCurpse       = 475,
        ShiftingPower      = 314791,
        SlowFall           = 130,
        Spellsteal         = 30449,
        TimeWarp           = 80353,
        AlterTime          = 108978,
        Shimmer            = 212653,
        ArcaneMisslesDmg   = 7268,
    };

    enum eFire
    {
        BlazingBarrier = 235313,
        Combustion = 190319,
        DragonsBreath = 331661,
        FireBlast = 108853,
        Fireball = 133,
        FlameStrike = 2120,
        PhoenixFlames = 257541,
        PyroBlast = 11366,
        Scorch = 2948,
        Cauterize = 86949,
        CriticalMass = 117216,
        HotStreak = 195283,
        Ignite = 12846,
        HotStreakBuff = 195283,
        Meteor = 153561,
    };

    enum eFrost
    {
        IceBarrier = 11426,
        IcyVeins = 12472,
        Flurry = 44614,
        FrozenOrb = 84714,
        IceLance = 30455,
        Blizzard = 190356,
        WintersChill = 228358,
        CometStorm = 153595,
        FrostStorm4pc = 364544,
        FrostStormDebuff = 363544,
        Frostbolt = 116,
        FrostboltDmg = 228597,
    };

    enum eArcane
    {
        ArcaneBlast = 30451,
        PrismaticBarrier = 235450,
        TouchOfTheMagi = 321507,
        ArcanePower = 12042,
    };

    enum eLegendary
    {
        ExpandedPotential = 327495, /// Prevent Hot Streak, Brain Freeze or Clearcasting from being consumed.
        ArcaneBombardment = 332892,
        SunKingsBlessing = 333313,
        SunKingsBlessingStacks = 333314,
        SunKingsBlessingProc = 333315,
        FreezingWinds = 327364,
        FreezingWindsProc = 327478,
        DeathsFathom = 354294, ///< Necrolord Legendary
    };

    enum eConduits
    {
        DivertedEnergy = 337136,
        DivertedEnergyHeal = 337137,
        ArcaneProdigy = 336873,
        NetherPrecision = 336886,
        NetherPrecisionBuff = 336889,
    };

    enum eCovenant
    {
        Deathborne = 324220
    };

    inline bool DropWinterChill(Unit* caster, Unit* target)
    {
        if (!caster || !target)
            return false;

        if (auto aur = target->GetAura(WintersChill, caster->GetGUID()))
        {
            aur->DropStack();
            return true;
        }

        return false;
    }

    inline void ApplyDivertedEnergyConduit(Unit* caster, uint32 absorbAmount)
    {
        if (!caster)
            return;

        if (auto eff = caster->GetAuraEffect(DivertedEnergy, EFFECT_0))
        {
            if (eff->ConduitRankEntry)
            {
                auto heal = CalculatePct(absorbAmount, eff->ConduitRankEntry->AuraPointsOverride);
                caster->CastSpell(caster, DivertedEnergyHeal, CastSpellExtraArgs(true).AddSpellBP0(heal));
            }
        }
    }
}
