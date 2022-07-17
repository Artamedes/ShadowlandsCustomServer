#pragma once

#include "SpellIncludes.h"

namespace Paladin
{
    enum PaladinSpells
    {
        Judgement            = 20271,
        VanquishersHammer    = 328204, ///< Necrolord Spell
        WordOfGlory          = 85673,
        ShieldOfTheRighteous = 53600,
        CrusaderStrike       = 35395,
        BlindingLight        = 115750,
        CleanseToxins        = 213644,
        Rebuke               = 96231,

        /// Holy
        LightOfDawn = 85222,

        /// Protection
        JudgementProt = 275779,
    };

    enum eHoly
    {
        LightOfTheMartyr = 183998,
        HolyShock = 20473,
        HolyShockHeal = 25914,
    };

    enum eRetribution
    {
        /// Ret
        BladeOfJustice    = 184575,
        ExecutionSentence = 343527,
        DivineStorm       = 53385,
        FinalReckoning    = 343721,
        HandOfHindrance   = 183218,
        ShieldOfVengeance = 184662,
        TemplarsVerdict   = 85256,
        WakeOfAshes       = 255937,
        ArtOfWar          = 267344,
        MasteryHandOfLight = 267316,

    };

    enum eProtection
    {
        AvengersShield = 31935,
    };

    enum eLegendary
    {
        // Holy
        MaraadsDyingBreath         = 340458,
        MaraadsDyingBreathProc     = 340459,
        // Prot
        TheArdentProtectorsSanctum = 337838,
        BulwarkOfRighteousFury     = 337847,
        BulwarkOfRighteousFuryProc = 337848,
        // Retr
        VanguardsMomentum = 337638,
        VanguardsMomentumProc = 345046,
    };
}
