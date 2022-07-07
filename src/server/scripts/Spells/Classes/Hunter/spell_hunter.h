#pragma once

#include "SpellIncludes.h"

namespace Hunter
{
    enum eSpells
    {
        ArcaneShot = 185358,
        AspectOfTheCheetah = 186257,
        AspectOfTheTurtle = 1896265,
        Disengage = 781,
        EagleEye = 6197,
        Exhilaration = 109304,
        EyesOfTheBeast = 321297,
        FeignDeath = 5384,
        Flare = 1543,
        FreezingTrap = 187650,
        HuntersMark = 257284,
        KillShot = 53351,
        Misdirection = 34477,
        BeastLore = 1462,
        DismissPet = 2641,
        FeedPet = 6991,
        RevivePet = 982,
        ScareBeast = 1513,
        SteadyShot =56641,
        SurvivalOfTheFittest = 281195,
        TarTrap = 187698,
        TranquillizingShot = 19801,
    };

    enum eMarksman
    {
        AimedShot = 19434,
        Barrage = 120360,
        BindingShot = 109248,
        BurstingShot = 186387,
        ConcussiveShot = 5116,
        CounterShot = 147362,
        DoubleTaap = 260402,
        MultiShot = 257620,
        RapidFire = 257044,
        Trueshot = 288613,
        LoneWolf = 155228,
        SniperTraining = 193468,
        PreciseShots = 260240,
        TrickShots = 257621,
        TrickShotsProc = 257622,
    };

    enum eSurvival
    {
        AspectOfTheEagle = 186289,
        Carve = 187708,
        CoordinatedAssault = 266779,
        Harpoon = 190925,
        Intimidation = 19577,
        KillCommand = 259489,
        Muzzle = 187707,
        RaptorStrike = 186270,
        SerpentSting = 259491,
        WildfireBomb = 259495,
        SpiritBond = 263135,
    };

    enum eBeastMastery
    {
        AspectOfTheWild = 193530,
        BarbedShot = 217200,
        BeastialWrath = 19574,
        CobraShot = 193455,
        ConcussiveShotBM = 5116,
        CounterShotBM = 147362,
        IntimidationBM = 19577,
        KillCommandBM = 34026,
        MultiShotBM =2643,
        BeastCleave = 115939,
        ExoticBeasts = 53270,
        KindredSpirits = 56315,
        MasterOfBeasts = 76657,
        PackTactics = 321014,
        WildCall = 185789,
    };

    enum eLegendary
    {
        NesingwarysTrappingApparatus = 336743,
        NesingwarysTrappingApparatusProc = 336744,
        SoulforgeEmbers = 336745,
        SoulforgeEmbersProc = 336746,
        DireCommand = 336819,
        RylakstalkersPiercingFangs = 336844,
        RylakstalkersPiercingFangsProc = 336845,
    };

    enum eCovenant
    {
        ResonatingArrow = 308491,
        ResonatingArrowMissle = 308495,

        AmbuscadeConduit = 346747,
    };

    /// <summary>
    /// Applies the Ambuscade conduit after a trap is triggered if they have the conduit
    /// </summary>
    /// <param name="caster"></param>
    void ApplyAmbuscadeIfNeed(Unit* caster);
}
