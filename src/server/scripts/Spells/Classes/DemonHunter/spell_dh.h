#pragma once

#include "SpellIncludes.h"

namespace DH
{
    enum eSpells
    {
        // General
        ConsumeMagic       = 278326,
        Disrupt            = 183752,
        Glide              = 131347,
        ImmolationAura     = 258920,
        Imprison           = 217832,
        SpectralSight      = 188501,
        ThrowGlaive        = 204157,
        Torment            = 185245,
        ChaosBrand         = 255260,
        DoubleJump         = 196055,
        ImmolationAuraDmg  = 258921,

        // Veng
        FelDevstation      = 212084,
        DemonSpikes        = 203720,
        FieryBrand         = 204021,
        InfernalStrike     = 189110,
        Shear              = 203782,
        SigilOfFlame       = 204596,
        SigilOfMisery      = 207684,
        SigilOfSilence     = 202137,
        SigilOfChains      = 202138,
        SoulCleave         = 228477,
        LastResort         = 209258,
        ShatteredSouls     = 204254,
        ThickSkin          = 320380,
        FelBlood           = 203747,
        RevelInPain        = 343014, ///< TODO!
        MetaVeng           = 187827,

        // Havoc
        DemonsBite         = 162243,
        FelRush            = 195072,
        BladeDance         = 188499,
        ChaosStrike        = 162794,
        EyeBeam            = 198013,
        MetaHavoc          = 191427,
        Felblade           = 232893,
        DemonBlades        = 203555,
        DemonBladesDmg     = 203796,
        GlaiveTempest      = 342817,
        ChaosNova          = 179057,
        Darkness           = 196718,
        VengefulRetreat    = 198793,
        ShatterdSoulsHavoc = 178940,
        DemonicPresence    = 185164,
        DemonicWards       = 278386,
        BladeDanceDmg      = 199552,
        DeathSweepDmg      = 210153,
        Metamorphosis      = 162264,

        FelDevstationDmg = 212105,
        EyeBeamDmg       = 198030,

        // Covenant
        ElysianDecree      = 306830,

        TheHuntNew         = 370965,
    };

    enum eCovenant
    {
        SinfulBrand = 317009,
        ShatteredSoulsNecrolord = 328951,
    };

    enum eTraits
    {
        BurningHatred = 320374,
    };

    enum eHavocTraits
    {
        RagefireProc          = 388107,
        RagefireAura          = 390192,
        RagefireDmg           = 390197,
        ChaoticTransformation = 388112,
        CycleOfHatred         = 258887,
        RestlessHunter        = 390142,
        RestlessHunterBuff    = 390212,
        InitiativeProc        = 391215,
        TacticalRetreat       = 389688,
        TacticalRetreatProc   = 389890,
        MomentumProc          = 208628,
        IsolatedPrey          = 388113,
        IsolatedPreyEyeBeam   = 357305,
        IsolatedPreyFelRush   = 357323,
        ChaosTheoryNew        = 389687,
        ChaosTheoryNewBuff    = 390195,
    };

    enum ePvpTalents
    {
        Glimpse = 354489,
        GlimpseAura = 354610,
        BloodMoon = 355995,
        BloodMoonLeech = 360258,
    };

    enum eDHCategoryIds
    {
        FelRushCategoryId = 1545,
    };
}
