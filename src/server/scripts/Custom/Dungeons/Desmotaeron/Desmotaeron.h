#pragma once

#include "CustomInstanceScript.h"

enum Desmoteraon
{
    BossXarvius = 0,
    BossShirgantai,
    BossGeneralNephmir,
    BossEcidus,
    MalekosPart1,
    BossMaleakos,
    MaxBosses,

    NpcSpawnOfShirgantai = 707033,
};

enum DesmotareonVisuals
{
    SpawnBlastAnim = 353961,
    MawPortalIn    = 360358,
    FadeInEffect   = 337464,
    DisappearSpell = 209026,
    AppearEffect   = 351925, // blue appear
    HideSpell      = 362717,
    StygianLaden   = 337897,
    MawCosmetic    = 326326,
    HologramSpawn  = 253589, // spawns azeroth visual;
    HologramGreen  = 231696,

    EmpoweredBrokerWeatherChange = 353689,
    TheMist                      = 312242,
    IceAge                       = 354529,
    HeavyFogRain                 = 305422, ///< Cast on enter
    TeleportSpell                = 268256,
    TeleportSpell2               = 268270,
};

enum DesmotareonSpells
{
    VolatileFelBurst = 209019,

    /// Maw Eye
    FocusedAnnihilation = 348757,

    /// Brutes / Guards
    ColossalSmash       = 356088,
    DefilingDreadslam   = 357364,
    BeastialHowl        = 333929,
    BellowingRoar       = 335485,
    BlazingInferno      = 357181,
    TouchOfFlame        = 346121, ///< Aura on spawn/Reset
    RisingHeat          = 357194, ///< Ramp up on HP %

    ///< Guards
    IronShackles = 347163,

    /// Bosses
    RainOfDespair = 362391,

    /// General Nephmir
    OptimalCoreTemperature = 367555,
    SoulflameTorrent = 357327,
    GiantSlam = 218077,
    ChargedWeapons = 310835,
    Thunderclap = 277743,

    SpectralWingsGuard = 346495,

    MawInfused = 361640,
    PowerUp,

    // Misc
    SpectralAxe = 339658,
    AccursedStrength = 358260,
    MassiveStrike = 347091,
    DominationBolt = 363607,
};

enum DesmotareonActions
{
    ActionShirgantaiOrbClicked = 1,
    ActionSetGuidShirgantai,
};

void DoDelayedMawPortalSpawn(Creature* who, float dist = 5.0f);
