#pragma once

#include "SpellIncludes.h"

namespace Warrior
{
    enum eWarrior : uint32
    {
        BattleShout = 6673,
        BerserkerRage = 18499,
        ChallengingShout = 1161,
        Charge = 100,
        Execute = 281000,
        Hamstring = 1715,
        HeroicLeap = 6544,
        HeroicThrow = 57755,
        IgnorePain = 190456,
        Intervene = 3411,
        IntimidatingShout = 5246,
        Pummel = 6552,
        RallyingCry = 97462,
        ShatteringThrow = 64382,
        ShieldBlock = 2565,
        ShieldSlam = 23922,
        Slam = 1464,
        SpellReflection = 23920,
        Taunt = 355,
        Whirlwind = 1680,
        Avatar = 107574,
        PiercingHowl = 12323,
    };

    enum eArms : uint32
    {
        Bladestorm = 227847,
        DieByTheSword = 118038,
        ImpendingVictory = 202168,
        MortalStrike = 12294,
        Overpower = 7384,
        SweepingStrikes = 260708,
        Warbreaker = 262161,
        MasteryDeepWounds = 262111,
        SeasonedSoldier = 279423,
        Tactician = 184783,
        Ravager = 152277,
        ColossusSmash = 167105,
    };

    enum eFury : uint32
    {
        BladestormFury = 46924,
        Bloodthirst = 23881,
        EnragedRegeneration = 184364,
        RagingBlow = 85288,
        Rampage = 184367,
        Recklessness = 1719,
        Enrage = 184361,
        MasteryUnshackledFury = 76856,
        SingleMindedFury = 81099,
        TitansGrip = 46917,
        Siegebreaker = 280772,
    };

    enum eProtection : uint32
    {
        DemoralizingShout = 1160,
        Devastate =20243,
        LastStand = 12975,
        Revenge = 6572,
        ShieldWall = 871,
        Shockwave = 46968,
        ThunderClap = 6343,
        DeepwoundsProt = 115768,
        MasteryCriticalBlock = 76857,
        Riptose = 161798,
        Vanguard = 71,
    };

    enum eLegendary : uint32
    {
        // Covenant
        ElysianMight = 357996,
        ElsyianMightCritBuff = 311193,
        NaturesFury = 354161,
        NaturesFuryDmg = 354163,
        Glory = 353577,
        SinfulSurge = 354131,

        // Arms
        BattleLordProc = 346369,
        Unhinged = 335282, ///< Cast random MS
        UnhingedTargetFinder = 335285,

        // Fury
        WillOfTheBerserker = 335594,
        WillOfTheBerserkerProc = 335597,

        // Prot
        ThunderLord = 335229,
        UnbreakableWill = 335629,
        UnbreakableWillProc = 335635,

    };

    enum eCovenant
    {
        SpearOfBastion = 307865,
        Condemn = 330334,
        ConquerorsBanner = 324143,
        AncientAftershock = 325886,
    };

    enum ePvpTalents
    {
        DeathSentenceCD = 368439,
        Slaughterhouse = 352998,
        SlaughterhouseDebuff = 354788,
        Demolition = 329033,
    };
}
