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
        HeartOfTheWild = 319454,

        BearForm = 5487,
        /// Finishers
        SavageRoar = 52610,
        Rip = 1079,
        FerociousBite = 22568,
        Main = 22570,
    };

    enum eFeral
    {
        Thrash = 106832,
        Swipe = 213764,
        TigersFury = 5217,
        IncarninationKindOfTheJungle = 102543,
        Berserk = 106951,
        PrimalWrath = 285381,
    };

    enum eGuardian
    {
        Ironfur = 192081,
        FrenziedRegeneration = 22842,
        ThrashBear = 77758,
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
        Rejuvenation = 774,
        IncarnationTreeOfLife = 33891,
        Swiftmend = 18562,
        WildGrowth = 48438,
    };

    enum eLegendary
    {
        // All Specs
        OathOfTheElderDruid      = 338608,
        OathOfTheElderDruidCD    = 338643,

        /// Balance
        BalanceOfAllThings       = 339942,
        BalanceOfAllThingsArcane = 339946,
        BalanceOfAllThingsNature = 339943,
        /// Guardian
        TheNaturalOrdersWill     = 339063,
        /// Restoration
        VerdantInfusion          = 338829,
    };

    enum eAffinities
    {
        RestoBalanceAffinity      = 197632,
        RestoFeralAfffinity       = 197490,
        RestoGuardianAffinity     = 197491,
        GuardianBalanceAffinity   = 197488,
        GuardianFeralAffinity     = 202155,
        GuardianRestoAffinity     = 197492,
        FeralBalanceAffinity      = 197488,
        FeralGuardianAffinity     = 217615,
        FeralRestorationAfffinity = 197492,
        BalanceFeralAffinity      = 202157,
        BalanceGuardianAfffinity  = 197491,
        BalanceRestoAffinity      = 197492,
    };

    inline ShapeshiftForm GetAffinityShapeshiftForm(Unit* caster)
    {
        if (!caster)
            return ShapeshiftForm::FORM_NONE;

        auto spec = GetSpecializationId(caster);

        switch (spec)
        {
            case SimpleTalentSpecs::RDruid:
                if (caster->HasAura(RestoBalanceAffinity))
                    return ShapeshiftForm::FORM_MOONKIN_FORM;
                if (caster->HasAura(RestoGuardianAffinity))
                    return ShapeshiftForm::FORM_BEAR_FORM;
                if (caster->HasAura(RestoFeralAfffinity))
                    return ShapeshiftForm::FORM_NONE;
                break;
            case SimpleTalentSpecs::Guardian:
                if (caster->HasAura(GuardianBalanceAffinity))
                    return ShapeshiftForm::FORM_MOONKIN_FORM;
                if (caster->HasAura(GuardianFeralAffinity))
                    return ShapeshiftForm::FORM_CAT_FORM;
                if (caster->HasAura(GuardianRestoAffinity))
                    return ShapeshiftForm::FORM_NONE;
                break;
            case SimpleTalentSpecs::Feral:
                if (caster->HasAura(FeralBalanceAffinity))
                    return ShapeshiftForm::FORM_MOONKIN_FORM;
                if (caster->HasAura(FeralGuardianAffinity))
                    return ShapeshiftForm::FORM_BEAR_FORM;
                if (caster->HasAura(FeralRestorationAfffinity))
                    return ShapeshiftForm::FORM_NONE;
                break;
            case SimpleTalentSpecs::Balance:
                if (caster->HasAura(BalanceFeralAffinity))
                    return ShapeshiftForm::FORM_CAT_FORM;
                if (caster->HasAura(BalanceGuardianAfffinity))
                    return ShapeshiftForm::FORM_BEAR_FORM;
                if (caster->HasAura(BalanceRestoAffinity))
                    return ShapeshiftForm::FORM_NONE;
                break;
        }

        return ShapeshiftForm::FORM_NONE;
    }

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

    inline bool IsAffectedByClearcasting(uint32 spellId)
    {
        switch (spellId)
        {
            case Shred:
            case Thrash:
            case Swipe:
                return true;
            default:
                return false;
        }
    }
}
