#pragma once

#include "SpellIncludes.h"

namespace Druid
{
    enum DruidSpells
    {
        BearForm = 5487,
        /// Finishers
        SavageRoar = 52610,
        Rip = 1079,
        PrimalWrath = 285381,
        FerociousBite = 22568,
        Main = 22570,
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
