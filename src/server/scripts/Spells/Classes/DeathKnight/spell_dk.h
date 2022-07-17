#pragma once

#include "SpellIncludes.h"

namespace DeathKnight
{
    enum eDK
    {
        AntiMagicShhell = 48707,
        AntiMagicZone = 51052,
        ChainsOfIce = 45524,
        ControlUndead = 111673,
        DarkCommand =56222,
        DeathAndDecay = 43265,
        DeathCoil = 47541,
        DeathGrip = 49576,
        DeathStrike = 49998,
        DeathsAdvance = 48265,
        IceboundFortitude = 48792,
        Lichborne = 49039,
        MindFreeze = 47528,
        PathOfFrost = 3714,
        RaiseAlly = 61999,
        Runeforging = 53428,
        SacrificialPact = 327574,
        OnAPaleHorse = 51986,
        VeternOfTheThirdWar = 48263,
        Asphyxiate = 221562,
        DefileDmg = 156000,
        DeathAndDecayDmg = 52212,

        FrostFever = 55095,
        BloodPlague =55078,
        VirulentPlague = 191587,
        DarkSuccor = 178819,
    };

    enum eUnholy
    {
        Apocalypse = 275699,
        ArmyOfTheDead = 42650,
        DarkTransformation = 63560,
        Epidemic = 207317,
        FesteringStrike = 85948,
        Outbreak = 77575,
        RaiseDead = 46584,
        ScourgeStrike = 55090,
        MasteryDreadblade = 77515,
        RunicCorruption = 51462,
        SuddenDoom = 49530,
        Defile = 152280,
    };

    enum eFrost
    {
        BreathOfSindragosa = 152279,
        EmpowerRuneWeapon = 47568,
        FrostStrike = 49143,
        FrostwyrmsFury = 279302,
        HowllingBlast = 49184,
        Obliterate = 49020,
        PillarOfFrost = 51271,
        RemorselessWinter = 196770,
        KillingMachine = 51128,
        MasteryFrozenHeart = 77514,
        MightOfTheFrozenWastes = 81333,
        Rime = 59057,
        RimeProc = 59052,
        RunicEmpowerment = 81229,
    };

    enum eBlood
    {
        BloodBoil = 50842,
        DancingRuneWeapon = 49028,
        DeathsCaress = 195292,
        GorefiendsGrasp = 108199,
        HeartStrike = 206930,
        Marrowrend = 195182,
        RuneTap = 194679,
        VampricBlood = 55233,
        CrimsonScourge = 81136,
        MasteryBloodShield = 77513,
        Ossuary = 219786,
    };

    enum eLegendary
    {
        DeathsEmbrace = 334728,
        DeathsEmbraceHeal = 334729,
        GripOfTheEverlasting = 334724,
        GripOfTheEverlastingBuff = 334722,
        Phearomones = 335177,
        DeathTurf = 335180,
        Superstrain = 334974,

        // Blood
        CrimsonRuneWeapon = 334525,
        CrimsonRuneWeaponProc = 334526,
        GorefiendsDomination = 334580,
        GorefiendsDominationEnergize = 350914,
        VampiricAura = 334547,
        VampiricAuraBuff = 334555,

        // Frost
        AbsoluteZero = 334692,
        AbsoluteZeroStun = 334693,
        BitingCold = 334678,
        RageOfTheFrozenChampion = 341724,
        RageOfTheFrozenChampionEnergize = 341725,

        // Unholy
        FrenziedMontrosity = 334888,
        FrenziedMontrosityBuff = 334895,
    };

    enum eCovenant
    {

    };

    const uint32 SuperstrainSpells[] = { FrostFever, BloodPlague, VirulentPlague };
    inline void ApplySuperstrain(Unit* caster, Unit* target, uint32 spellId)
    {
        if (!caster || !target)
            return;

        if (!caster->HasAura(eLegendary::Superstrain))
            return;

        for (auto spell : SuperstrainSpells)
        {
            if (spell == spellId)
                continue;

            caster->CastSpell(target, spell, true);
        }
    }
}
