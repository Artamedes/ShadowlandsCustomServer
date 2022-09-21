#pragma once

#include "SpellIncludes.h"

namespace Rogue
{

    enum eRogue : uint32
    {
        Vanish            = 1856,
        Rupture           = 1943,
        Sprint            = 2983,
        GrapplingHook     = 195457,
        MarkedForDeath    = 137619,
        SliceAndDice      = 315496,
        /// Covenant
        Flagellation      = 323654,
        Sepsis            = 328305,
        EchoingReprimand  = 323547,
        SerratedBoneSpike = 328547,

        Feint = 1966,
        Evasion = 5277,
        /// Conduits

        /// Legendaries
        InvigoratingShadowdustLegendary  = 340080,
        DeathlyShadows          = 340092,
        DeathlyShadowsOutlaw    = 341202,
        DeathlyShadowsAssa      = 350964,
        FinalityRuptureLegendary = 340601,
    };

    enum eAssassination
    {
        Vendetta = 79140,
        Envenom = 32645,
        Mutilate = 1329,
        MutilateDmg = 5374,

        Garrote = 703,
        InternalBleedingDot = 154953,
    };

    enum eOutlaw
    {
        /// Generators
        SinisterStrike = 193315,
        PistolShot = 185763,
        GhostlyStrike = 196937,
        /// Finishers
        Dispatch = 2098,
        BetweenTheEyes = 315341,
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

        AdrenalineRush = 13750,
        BladeFlurryDmg = 22482,
        MainGaucheDmg = 86392, ///< Mastery Proc
        KillingSpree = 51690,
        BladeRush = 271877,
        BladeFlurry = 13877,
        RollTheBones = 315508,

    };

    enum eSubtlety
    {
        ShadowBlades = 121471,
        FindWeaknesDebuff = 91021,
        ShurikenStorm = 197835,
    };

    enum eRogueTraits
    {
        SepsisNew = 385408,
    };

    enum eSubtletyTraits
    {
        TheFirstDance         = 382505,
        StiletoStaccato       = 382509,
        ImprovedShurikenStorm = 319951,
        Premeditation         = 343160,
        PremeditationEnergize = 343170,
        PremeditationProcAura = 343173,
        SilentStorm           = 385722,
        SilentStormProcAura   = 385727,
        ShadowedFinishers     = 382511,
        Gloomblade            = 200758,
        FadeToNothing         = 382514,
        FadeToNothingProc     = 386237,
        CloakedInShadows      = 382515,
        CloakedInShadowsBuff  = 386165,
        DeeperDaggersProc     = 383405,
        InvigoratingShadowdust = 382523,
        Finality              = 382525,
        FinalityBlackPowder   = 385948,
        FinalityEviscerate    = 385948,
        FinalityRupture       = 385951,
    };

    enum eOutlawTraits
    {
        LongArmOfTheOutlaw     = 381878,
        LongArmOfTheOutlawProc = 385835,
        KeepItRolling          = 381989,
        Dreadblades            = 343142,
        AceUpYourSleeve        = 381828,
        AceUpYourSleeveEnergize = 279714,
        SleightOfHandNew       = 381839,
    };

    enum eCovenant
    {
        SepticShock = 341309,
        SepsisAura = 347037,
        SepsisDmg = 328306,
    };

    enum eLegendary
    {
        ToxicOnslaught = 354473,
    };

    enum ePvPTalents
    {
        FloatLikeAButterfly = 354897,
    };

    void HandleGrudgeMatch(Unit* caster, Unit* target, uint32 auraId);
    void HandleGrudgeMatch(Unit* caster, Unit* target, Aura* dot);
}
