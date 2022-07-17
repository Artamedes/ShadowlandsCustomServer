#pragma once

#include "SpellIncludes.h"

namespace Druid
{
    enum eDruid
    {
        Barskin = 22812,
        CatForm = 768,
        Cyclone = 33786,
        Dash = 1850,
        EntanglingRoots = 339,
        Mangle = 33917,
        IronFur = 192081,
        Hibernate = 2637,
        Growl = 6795,
        Moonfire = 8921,
        Prowl = 5215,
        Rebirth = 20484,
        Regrowth = 8936,
        Revive = 50769,
        Shred = 5221,
        Soothe = 2908,
        StampedingRoar = 106898,
        TeleportMoonglade = 18960,
        TravelForm = 783,
        Wrath = 190984,
        AquaticForm = 276012,
        FlightForm = 276029,

        BearForm = 5487,
        /// Finishers
        SavageRoar = 52610,
        Rip = 1079,
        PrimalWrath = 285381,
        FerociousBite = 22568,
        Main = 22570,
    };

    enum eFeral
    {

    };

    enum eGuardian
    {

    };

    enum eBalance
    {
        CelestialAlignment = 194223,
        FuryOfElune = 202770,
        Innervate = 29166,
        MoonkinForm = 24858,
        RemoveCorruption = 2782,
        SolarBeam = 78675,
        Starfall = 191034,
        Starfire = 194153,
        Starsurge = 78674,
        Sunfire = 93402,
        Typhoon = 132469,
        AstralInfluence = 197524,
        MasteryTotalEclipse = 326085,
        ShootingStars = 202342,

        // Eclipse
        Eclipse      = 79577,
        EclipseSolar = 48517,
        EclipseLunar = 48518,

        EclipseSolarCount = 326053,
        EclipseLunarCount = 326055,
    };

    enum eRestoration
    {

    };

    enum eLegendary
    {
        /// Balance
        BalanceOfAllThings       = 339942,
        BalanceOfAllThingsArcane = 339946,
        BalanceOfAllThingsNature = 339943,
    };

    inline bool IsFinisher(uint32 spellId)
    {
        switch (spellId)
        {
            case SavageRoar:
            case Rip:
            case PrimalWrath:
            case FerociousBite:
            case Main:
                return true;
            default:
                return false;
        }
    }
}
