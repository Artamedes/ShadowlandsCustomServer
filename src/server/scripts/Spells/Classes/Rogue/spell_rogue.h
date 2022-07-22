#pragma once

#include "SpellIncludes.h"

namespace Rogue
{

    enum eRogue : uint32
    {
        Vanish            = 1856,
        Rupture           = 1943,
        /// Covenant
        Flagellation      = 323654,
        Sepsis            = 328305,
        EchoingReprimand  = 323547,
        SerratedBoneSpike = 328547,
        /// Conduits

        /// Legendaries
        InvigoratingShadowdust  = 340080,
        DeathlyShadows          = 340092,
        DeathlyShadowsOutlaw    = 341202,
        DeathlyShadowsAssa      = 350964,
        FinalityRupture         = 340601,
    };

    enum eAssassination
    {
        Vendetta = 79140,
    };

    enum eOutlaw
    {
        AdrenalineRush = 13750
    };

    enum eSubtlety
    {
        ShadowBlades = 121471,
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

    void HandleGrudgeMatch(Unit* caster, Unit* target, uint32 auraId);
    void HandleGrudgeMatch(Unit* caster, Unit* target, Aura* dot);
}
