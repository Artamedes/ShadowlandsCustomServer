/*
 * Copyright (C) 2008-2020 TrinityCore <https://www.trinitycore.org/>
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "ScriptMgr.h"
#include "AreaTrigger.h"
#include "AreaTriggerAI.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "CellImpl.h"
#include "GridNotifiersImpl.h"
#include "GossipDef.h"
#include "MoveSplineInit.h"
#include "SpellAuraEffects.h"
#include "G3D/Vector3.h"
#include "PhasingHandler.h"
#include "Position.h"
#include "MotionMaster.h"
#include "MoveSpline.h"
#include "MotionMaster.h"
#include "InstanceScript.h"
#include "ObjectAccessor.h"
#include "SpellScript.h"
#include "TemporarySummon.h"
#include "Vehicle.h"
#include "Containers.h"

enum FreeholdCreature
{
    //Skycap Kragg Intro  
    NPC_SKYCAP_KRAGG_INTRO       = 129732,
    NPC_SHARKBAIT_INTRO          = 129743,

    //Skycap Kragg
    NPC_SKYCAP_KRAGG             = 126832,
    NPC_SHARKBAIT_BOSS           = 126841,
    NPC_REVITALIZING_BREW        = 134021,

    //Council o Captains
    NPC_BILGE_RAT_GROG_JERK      = 135978,
    NPC_BILGE_RAT_PARTY_ANIMAL   = 138676,
    NPC_BILGE_RAT_PARTY_ANIMAL2  = 135938,
    NPC_MURPHY                   = 130467,
    NPC_OTIS                     = 129441,
    NPC_FREEHOLD_JAIL            = 130536,
    NPC_BLACKTOOTH_KDUSTER       = 129547,
    NPC_BLACKTOOTH_BRUTE         = 129548,
    NPC_BLACKTOOTH_SCRAPPER      = 129529,
    NPC_TRAINING_DUMMY           = 127019,
    NPC_CAPTAIN_JOLLY            = 126845,
    NPC_CAPTAIN_EUDORA           = 126848,
    NPC_CAPTAIN_RAOUL            = 126847,
    NPC_RUMMY_MANCOMB            = 133219,
    NPC_BLACKOUT_BARREL          = 130896,

    //Ring of Booty
    NPC_DAVEY                   = 130086,
    NPC_GUKGUK                  = 130090,
    NPC_GURGTHOCK               = 129350,
    NPC_KEN                     = 130172,
    NPC_LIGHTNING               = 130099,
    NPC_LUDWIG_VON_TORTOLLAN    = 129699,
    NPC_SHELL_TARGET            = 130157,
    NPC_TROTHAK                 = 126969,
    NPC_HAMMER_SHARK            = 129448,
    NPC_SAWTOOTH_SHARK          = 129359,
    NPC_BOOTY_FANATIC           = 136539,
    NPC_BONFIRE_SPAWN           = 131092,

    //Harlan Sweete
    NPC_HARLAN_SWEETE           = 126983,
    NPC_IRONTIDE_GRENADIER      = 129758,
    NPC_SWIFTWIND_SABER         = 129747,
    NPC_IRONTIDE_CANNON         = 130850,
    NPC_CHEST_O_BOOTY           = 144596,

    //Trash                
    NPC_IRONTIDE_ENFORCER       = 129602,
    NPC_BILGE_RAT_SWABBY        = 129526,
    NPC_BILGE_RAT_BUCCANEER     = 129527,
    NPC_BILGE_RAT_PADFOOT       = 129550,
    NPC_BILGE_RAT_BRINESCALE    = 129600,
    NPC_CUTWATER_DUELIST        = 129559,
    NPC_CUTWATER_KNIFE_JUGGLER  = 129599,
    NPC_CUTWATER_HARPONEER      = 129601,
};

enum FreeholdGameObject
{
    GO_COUNCIL_TRIBUTE = 288636
};

enum FreeholdAction
{
    ACTION_SKYCAP_APPEAR,
    ACTION_BLACKTOOTH_BRAWL_ENGAGE
};

enum FreeholdData
{
    DATA_SKYCAP_KRAGG,
    DATA_COUNCIL_O_CAPTAINS,
    DATA_RING_OF_BOOTY,
    DATA_HARLAN_SWEETE,
    DATA_MAX_ENCOUNTERS,

    DATA_SKYCAP_KRAGG_INTRO,
    DATA_BLACKTOOTH_BRAWL,
    DATA_FRIENDLY_CAPTAIN,
    DATA_COUNCIL_O_CAPTAIN_PRE_EVENT,
    SPELL_TENDING_BAR = 264605,
};

enum FreeholdConversations
{
    CONVERSATION_SHARKBAIT_OUTRO = 6422,
    CONVERSATION_OTIS_INTRO = 6354,
    CONVERSATION_OTIS_OUTRO = 6360,
    CONVERSATION_HORDE_JOIN_CAPTAIN_EUDORA = 9659,
    CONVERSATION_HORDE_JOIN_CAPTAIN_RAOUL = 9658,
    CONVERSATION_ALLIANCE_JOIN_CAPTAIN_EUDORA = 7308,
    CONVERSATION_ALLIANCE_JOIN_CAPTAIN_RAOUL = 7307,
    CONVERSATION_COUNCIL_O_CAPTAINS_INTRO = 9575,
    CONVERSATION_RING_OF_BOOTY_INTRO = 6363,
    CONVERSATION_RING_OF_BOOTY_LUDWIG = 6364,
    CONVERSATION_RING_OF_BOOTY_THROTHAK = 6366,
};

enum FreeholdAchievements
{
    ACHIEVEMENT_FREEHOLD_NORMAL     = 12831,
    ACHIEVEMENT_FREEHOLD_HEROIC     = 12832,
    ACHIEVEMENT_FREEHOLD_MYTHIC     = 12833,

    ACHIEVEMENT_I_M_IN_CHARGE_NOW   = 12548,
    ACHIEVEMENT_PECKING_ORDER       = 12550,
    ACHIEVEMENT_THAT_SWEETY_BOOTY   = 12998,
};

enum FreeholdSpells
{
    SPELL_CUTWATER_REGALIA   = 257800, // Cast if you become part of the crow of Jolly
    SPELL_BLACKTOOTH_REGALIA = 266950, // Cast if you become part of the crow of Raoul
    SPELL_BILGE_RAT_REGALIA  = 266952, // Cast if you become part of the crow of Eudora
};

// Skycap Kragg
const std::vector<G3D::Vector3> KraggIntroPositions =
{
    { -1657.0435f, -981.4340f, 102.0927f },
    { -1643.9879f, -979.0868f, 90.61387f },
    { -1632.0642f, -979.1337f, 81.74204f },
    { -1620.0226f, -983.4774f, 78.08494f },
    { -1603.8560f, -989.6198f, 80.15582f },
    { -1594.8490f, -989.9305f, 85.92368f },
    { -1594.6666f, -971.3524f, 87.62517f },
    { -1610.0798f, -954.2170f, 99.96946f },
    { -1630.0817f, -943.7170f, 105.6537f },
    { -1640.5469f, -963.7379f, 109.6153f },
    { -1657.3281f, -999.8247f, 107.0174f },
};

const std::vector<G3D::Vector3> KraggIntroCyclicPositions =
{
    { -1657.3281f, -999.8247f, 107.0174f },
    { -1644.8351f, -1010.504f, 110.3014f },
    { -1612.5295f, -1000.066f, 101.2151f },
    { -1599.6841f, -985.6233f, 97.48121f },
    { -1619.6354f, -968.7327f, 99.89742f },
    { -1638.0295f, -961.4583f, 104.1691f },
    { -1653.0642f, -969.9948f, 114.9134f },
    { -1663.7223f, -989.0868f, 109.3119f },
    { -1664.6216f, -1006.250f, 108.3127f },
    { -1676.7291f, -1017.668f, 106.9218f },
    { -1696.9045f, -1019.217f, 105.9798f },
    { -1707.9810f, -1012.014f, 107.3851f },
    { -1715.4341f, -987.1059f, 104.7159f },
    { -1713.0504f, -952.1337f, 100.4133f },
    { -1676.7067f, -949.5434f, 107.4092f },
    { -1662.6719f, -980.5243f, 108.4314f },
};

const std::vector<G3D::Vector3> KraggDestPositions =
{
    { -1714.9635f, -1005.2882f, 119.6295f },
    { -1727.9601f, -1009.9601f, 119.0932f },
    { -1777.4629f, -995.14557f, 89.46374f },
};

const std::vector<Position> SharkbaitWaypoints =
{
    { -1748.4614f, -1050.3566f, 120.1553f },
    { -1760.1532f, -1050.9215f, 120.1553f },
    { -1771.1713f, -1046.9692f, 120.1553f },
    { -1779.8380f, -1039.1013f, 120.1553f },
    { -1784.8342f, -1028.5157f, 120.1553f },
    { -1785.3992f, -1016.8240f, 120.1553f },
    { -1781.4469f, -1005.8060f, 120.1553f },
    { -1773.5790f, -997.13916f, 120.1553f },
    { -1762.9934f, -992.14294f, 120.1553f },
    { -1751.3016f, -991.57800f, 120.1553f },
    { -1740.2836f, -995.53033f, 120.1553f },
    { -1731.6168f, -1003.3982f, 120.1553f },
    { -1726.6206f, -1013.9838f, 120.1553f },
    { -1726.0557f, -1025.6755f, 120.1553f },
    { -1730.0079f, -1036.6936f, 120.1553f },
    { -1737.8759f, -1045.3604f, 120.1553f },
};



const Position KraggMiddlePos = { -1759.21f, -1012.75f,	88.1935f };

// Council o' Captains
const std::vector<uint32> CouncilOCaptains =
{
    NPC_CAPTAIN_EUDORA,
    NPC_CAPTAIN_JOLLY,
    NPC_CAPTAIN_RAOUL,
};

const std::vector<G3D::Vector3> OtisWayPoints
{
    { -1870.27f, -740.20f, 55.70f },
    { -1868.26f, -726.68f, 55.37f },
    { -1869.73f, -718.74f, 55.19f },
    { -1853.24f, -711.08f, 51.34f }
};

const std::vector<Position> MurphyRunningPositions = 
{
    { -1887.00f, -769.96f, 56.55f, 5.932f },
    { -1916.49f, -708.48f, 58.46f, 5.579f },
    { -1860.82f, -754.15f, 56.18f, 4.792f },
};

const std::vector<Position> BilgeRatGrogJerkSpawnPos =
{
    { -1910.76f, -771.680f, 57.6591f, 2.43837f },
    { -1878.20f, -742.123f, 56.9022f, 5.59740f },
    { -1915.24f, -700.866f, 69.3668f, 5.87583f },
    { -1906.99f, -706.599f, 58.5028f, 5.48091f },
    { -1848.53f, -737.024f, 56.6379f, 2.87102f },
};

const std::vector<Position> BilgeRatPartyAnimal1SpawnPos =
{
    { -1917.37f, -702.568f, 69.3089f, 6.23757f },
    { -1844.07f, -735.797f, 56.6329f, 3.01973f },
    { -1880.25f, -744.071f, 56.9252f, 5.66440f },
    { -1877.64f, -739.484f, 57.1710f, 5.13793f },
    { -1911.66f, -774.224f, 57.8754f, 1.89135f },
    { -1909.55f, -708.109f, 58.5002f, 5.95643f },
};

const std::vector<Position> BilgeRatPartyAnimal2SpawnPos =
{
    { -1908.24f, -771.445f, 57.6922f, 2.43221f },
    { -1904.14f, -705.623f, 58.5195f, 4.89960f },
    { -1850.19f, -740.307f, 56.6323f, 2.56050f },
    { -1881.17f, -739.859f, 59.2341f, 5.38436f },
    { -1915.94f, -705.191f, 70.5127f, 1.52423f },
};

const std::vector<Position> KnuckledusterSpawnPos =
{
    { -1881.940f, -747.3910f, 56.5521f, 1.31938f },
    { -1878.580f, -745.6680f, 56.6186f, 2.87700f },
};

const std::vector<Position> BrutesSpawnPos =
{
    { -1871.958f, -661.9445f, 61.6417f, 4.71230f },
    { -1933.830f, -742.4650f, 65.4280f, 0.00000f },
};

const std::vector<Position> ScrapperSpawnPos =
{
    { -1915.490f, -695.7690f, 69.4084f, 5.57197f },
    { -1903.670f, -779.2240f, 64.3228f, 1.55354f }
};

const Position TrainingDummySpawnPosition = { -1881.2865f, -744.9202f, 56.906f, 5.3425f };

const Position OtisSpawnPosition = { -1879.5469f, -742.712f, 57.3114f, 5.1083f };
const Position JailSpawnPosition = { -1879.5139f, -742.646f, 56.7203f, 4.5313f };
const Position MurphySpawnPosition = { -1869.1805f, -759.0139f, 55.2758f, 5.3588f };

const Position CouncilOCaptainsMiddle = { -1806.56f, -680.85f, 39.12f };
const Position CouncilOCaptainCachePos = { -1784.443f, -684.4028f, 38.51701f, 3.153633f };

// Ring of Booty
const Position ArenaMiddlePos = { -1809.7f, -489.708f, 35.0676f };
const Position LudwigJumpPos = { -1813.03f, -476.293f, 35.16f, 4.74f };
const Position TrothakSpawnPos = { -1847.755f, -428.2896f, 40.39227f, 2.16f };

const std::vector<Position> BonfireSpawnPos =
{
    { -1816.94f, -441.778f, 49.5807f },
    { -1821.90f, -446.229f, 49.5802f },
    { -1819.66f, -443.109f, 49.9878f },
};

const std::vector<G3D::Vector3> DaveyLeavePath =
{
    { -1813.711f, -476.3904f, 35.44132f },
    { -1813.461f, -474.3904f, 35.44132f },
    { -1813.211f, -471.6404f, 35.69132f },
    { -1812.766f, -467.6389f, 35.81348f },
    { -1812.337f, -451.5781f, 35.69004f },
    { -1812.419f, -440.5509f, 36.16941f },
    { -1812.434f, -438.9809f, 36.12925f },
};

const std::vector<G3D::Vector3> LightningLeavePath =
{
    { -1812.766f, -467.6389f, 35.81348f },
    { -1812.647f, -467.3657f, 35.97119f },
    { -1812.337f, -451.5781f, 35.69004f },
    { -1812.419f, -451.3009f, 35.91941f },
    { -1812.419f, -440.5509f, 36.16941f },
    { -1812.434f, -438.9809f, 36.12925f }
};

const std::vector<G3D::Vector3> TrothakIntroPath =
{
    { -1848.496f, -426.5137f, 40.02433f },
    { -1849.023f, -425.2413f, 39.72526f },
    { -1849.300f, -422.0695f, 39.92081f },
    { -1847.656f, -418.7552f, 40.24381f },
    { -1844.594f, -417.2292f, 39.90421f },
    { -1841.543f, -417.6649f, 39.95646f },
    { -1837.585f, -419.0104f, 40.02433f },
    { -1835.507f, -421.9948f, 40.14933f },
    { -1834.269f, -425.8403f, 40.27433f },
    { -1832.394f, -428.7379f, 39.96467f },
    { -1829.908f, -432.0365f, 40.16462f },
    { -1826.321f, -435.5226f, 40.03598f },
    { -1819.188f, -436.8420f, 38.55771f },
    { -1813.948f, -437.3299f, 36.53720f },
    { -1812.670f, -440.0430f, 35.94004f },
    { -1812.458f, -449.1024f, 35.69004f },
    { -1812.151f, -455.3455f, 35.69004f },
    { -1812.059f, -459.8160f, 35.81504f },
    { -1812.326f, -466.6840f, 35.91700f },
    { -1812.705f, -470.9462f, 35.69727f },
    { -1812.922f, -474.8958f, 35.39820f },
    { -1813.250f, -478.4740f, 34.94630f },
};

const Position GranadierSummonPos = { -1593.361f, -546.5816f, 90.46461f, 5.170496f };

const Position SweetesLandingCenter = { -1587.22f, -562.097f, 70.2824f };
