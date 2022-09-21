
DELETE FROM `creature_template` WHERE `entry` IN (198071 /*Dragon Isles Adventurer*/, 198096 /*Valdrakken Flightmage*/);
INSERT INTO `creature_template` (`entry`, `KillCredit1`, `KillCredit2`, `name`, `femaleName`, `subname`, `TitleAlt`, `IconName`, `HealthScalingExpansion`, `RequiredExpansion`, `VignetteID`, `unit_class`, `WidgetSetID`, `WidgetSetUnitConditionID`, `rank`, `family`, `type`, `type_flags`, `type_flags2`, `HealthModifier`, `ManaModifier`, `RacialLeader`, `movementId`, `CreatureDifficultyID`, `VerifiedBuild`) VALUES
(198071, 0, 0, 'Dragon Isles Adventurer', '', NULL, NULL, NULL, 8, 0, 0, 1, 0, 0, 0, 0, 7, 0, 0, 1.35000002384185791, 1, 0, 0, 226439, 45632), -- Dragon Isles Adventurer
(198096, 0, 0, 'Valdrakken Flightmage', '', NULL, NULL, NULL, 9, 0, 0, 8, 0, 0, 0, 0, 7, 0, 0, 1.35000002384185791, 1, 0, 0, 226468, 45632); -- Valdrakken Flightmage

UPDATE `creature_template` SET `VerifiedBuild`=45632 WHERE `entry` IN (50269, 36871, 15659, 151937, 14559, 6740, 14560, 14561, 167591, 29093, 51440, 176545, 165379, 175435, 68, 58154, 178792, 187734, 178804, 165403, 89, 165405, 44773, 156479, 2334, 35845, 32520, 99541, 43692, 43693, 21354, 43694, 1257, 164352, 164353, 185576, 175525, 175526, 1275, 92870, 173300, 173301, 3518, 173302, 164367, 1285, 173304, 164368, 32562, 1286, 1287, 173305, 1289, 1291, 1292, 1294, 1295, 173318, 1301, 1302, 1303, 167738, 173325, 173327, 12480, 12481, 173330, 1320, 1321, 43768, 43769, 1323, 1324, 1325, 1326, 173348, 173350, 1333, 173351, 173352, 173353, 173354, 173355, 2455, 173356, 2456, 1339, 29264, 173357, 2457, 1341, 177829, 173364, 173367, 173369, 148796, 173370, 6946, 173386, 173388, 43819, 43820, 62809, 50523, 50524, 43822, 50525, 153292, 103033, 62821, 62822, 3626, 277, 1395, 279, 284, 156666, 156667, 156668, 156669, 156670, 100820, 156671, 156672, 147741, 2532, 2533, 156681, 156683, 305, 156685, 156686, 146633, 156687, 308, 156688, 156689, 1427, 156690, 156691, 189085, 174564, 156692, 1431, 156694, 1432, 156696, 156698, 167880, 167881, 147785, 165657, 352, 156732, 156733, 156734, 156735, 62913, 87501, 87503, 156758, 164579, 156768, 189161, 156769, 49540, 156777, 164596, 171299, 61834, 61836, 62954, 61837, 61838, 50669, 173545, 156791, 173548, 416, 417, 31695, 31697, 28347, 28355, 62982, 26125, 173571, 31717, 150122, 61895, 61896, 168011, 170256, 173610, 155739, 165796, 482, 483, 18357, 164684, 164685, 18360, 18362, 12779, 12780, 4961, 12781, 188151, 12783, 12784, 17252, 12785, 12786, 12787, 31778, 18375, 18376, 7207, 4974, 7208, 53006, 4981, 166949, 170310, 6112, 60849, 18406, 69791, 164736, 149099, 69792, 175911, 2795, 59764, 8383, 73190, 6174, 49748, 48632, 164803, 1721, 111190, 174871, 31902, 140253, 31912, 55370, 143622, 52029, 52030, 148124, 44245, 44246, 172702, 29726, 44252, 176064, 176065, 176067, 162666, 23050, 61029, 69974, 69975, 4075, 5193, 181681, 49877, 164939, 164940, 164941, 164942, 164943, 166061, 164945, 164946, 164947, 164948, 24207, 164949, 164950, 148196, 164952, 164953, 164954, 164955, 164956, 164957, 164960, 164961, 61080, 164962, 61081, 175016, 175017, 175019, 175020, 176137, 170557, 176146, 140403, 140407, 148233, 175042, 182864, 73400, 175051, 168353, 46602, 175066, 175067, 176186, 170607, 175080, 176197, 175081, 175082, 175083, 38821, 35477, 8670, 176221, 170640, 176226, 169524, 1976, 19848, 176229, 176230, 159478, 176233, 188523, 149433, 176244, 32151, 32158, 149445, 171790, 171796, 114832, 8719, 149467, 4269, 171822, 85816, 85817, 85818, 85819, 162896, 158436, 158440, 162918, 54569, 175206, 175207, 175208, 63508, 175209, 175210, 175211, 175212, 175213, 162928, 176332, 175215, 162929, 175218, 84745, 175222, 162935, 84749, 84751, 52361, 31146, 165189, 166307, 166312, 167429, 164079, 42339, 174146, 164095, 164096, 164098, 164099, 164100, 54638, 82564, 52408, 164123, 163007, 11096, 54660, 43499, 149616, 149626, 56925, 2198, 51348, 42421, 5564, 5565, 173118, 196581);
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=1141; -- Angus Stern
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=71526; -- Elizabeth Birdsong
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=175416; -- Miggi
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=175420; -- Mangeclaw
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=165374; -- Yu'lon
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=179896; -- Finn
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=44774; -- Genevieve
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=2330; -- Karlee Chaddis
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=2331; -- Paige Chaddis
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=29142; -- Jelinek Sharpshear
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=5694; -- High Sorcerer Andromath
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=158753; -- Bella
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=158755; -- Rufus
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=3504; -- Gil
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=3505; -- Pat
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=3507; -- Andi
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=3508; -- Mikey
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=3509; -- Geoff
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=3510; -- Twain
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=3511; -- Steven
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=3512; -- Jimmy
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=3513; -- Miss Danna
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=3520; -- Ol' Emma
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=1297; -- Lina Stover
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=1298; -- Frederick Stover
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=1299; -- Lisbeth Schneider
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=1300; -- Lawrence Schneider
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=1307; -- Charys Yserian
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=1308; -- Owen Vaughn
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=1309; -- Wynne Larson
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=1310; -- Evan Larson
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=1311; -- Joachim Brenlow
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=1312; -- Ardwyn Cailen
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=1313; -- Maria Lumere
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=1314; -- Duncan Cullen
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=1315; -- Allan Hafgan
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=1316; -- Adair Gilroy
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=1317; -- Lucan Cordell
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=1318; -- Jessara Cordell
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=1319; -- Bryan Cross
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=1327; -- Reese Langston
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=1328; -- Elly Langston
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=50480; -- Isabel Jones
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=1346; -- Georgio Bolero
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=1347; -- Alexandra Bolero
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=2485; -- Larimaine Purdue
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=147714; -- Exodar Portal-Keeper
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=3627; -- Erich Lohan
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=3628; -- Steven Lohan
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=3629; -- David Langston
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=1402; -- Topper McNabb
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=1412; -- Squirrel
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=1413; -- Janey Anship
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=1414; -- Lisan Pierce
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=1415; -- Suzanne
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=1419; -- Fizzles
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=1428; -- Rema Schneider
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=1429; -- Thurman Schneider
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=331; -- Maginor Dumas
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=338; -- Mazen Mac'Nadir
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=340; -- Kendor Kabonka
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=1477; -- Christoph Faral
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=1478; -- Aedis Brom
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=23837; -- ELM General Purpose Bunny
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=46180; -- Ithurian Whitespire
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=61841; -- Brunn Goldenmug
UPDATE `creature_template` SET `VerifiedBuild`=45632 WHERE `entry`=85307; -- Sparkbright
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=2708; -- Archmage Malin
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=6089; -- Harry Burlguard
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=6090; -- Bartleby
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=141270; -- Pepper
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=149121; -- Summoned Guardian
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=149124; -- Arcane Golem
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=149131; -- Apprentice Mage
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=173706; -- Mummiaabu
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=5081; -- Connor Rivers
UPDATE `creature_template` SET `VerifiedBuild`=45632 WHERE `entry`=51998; -- Arthur Huwe
UPDATE `creature_template` SET `VerifiedBuild`=45632 WHERE `entry`=174922; -- Strategist Zo'rak
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=44237; -- Maegan Tillman
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=721; -- Rabbit
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=4078; -- Collin Mauren
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=176192; -- Xavier Carpenter
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=176203; -- Tanaya Perch
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=176220; -- Antoinette Jardin
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=155011; -- Daphne Funkybeats
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=176235; -- Erika Saka
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=176237; -- Sojurn Saka
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=149436; -- Northrend Adventurer
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=149469; -- Exodar Adventurer
UPDATE `creature_template` SET `VerifiedBuild`=45632 WHERE `entry`=918; -- Osborne the Night Man
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=5386; -- Acolyte Dellis
UPDATE `creature_template` SET `VerifiedBuild`=45632 WHERE `entry`=89174; -- Laluu
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=158456; -- Emma
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=42288; -- Robby Flay
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=158463; -- Wiley
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=52358; -- Craggle Wobbletop
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=52359; -- Toy Cart
UPDATE `creature_template` SET `VerifiedBuild`=45632 WHERE `entry`=13283; -- Lord Tony Romano
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=5482; -- Stephen Ryback
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=5483; -- Erika Tate
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=11068; -- Betty Quin
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=14423; -- Officer Jaxon
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=44582; -- Theresa Denman
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=44583; -- Terrance Denman
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=5493; -- Arnold Leland
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=5494; -- Catherine Leland
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=5497; -- Jennea Cannon
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=5498; -- Elsharin
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=5499; -- Lilyssia Nightbreeze
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=5500; -- Tel'Athir
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=14438; -- Officer Pomeroy
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=5503; -- Eldraeith
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=14439; -- Officer Brady
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=5566; -- Tannysa
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45632 WHERE `entry`=5567; -- Sellandus

DELETE FROM `creature_template_model` WHERE (`CreatureID`=198071 AND `Idx` IN (3,2,1,0)) OR (`CreatureID`=198096 AND `Idx` IN (1,0));
INSERT INTO `creature_template_model` (`CreatureID`, `Idx`, `CreatureDisplayID`, `DisplayScale`, `Probability`, `VerifiedBuild`) VALUES
(198071, 3, 109886, 1, 1, 45632), -- Dragon Isles Adventurer
(198071, 2, 109887, 1, 1, 45632), -- Dragon Isles Adventurer
(198071, 1, 109888, 1, 1, 45632), -- Dragon Isles Adventurer
(198071, 0, 109889, 1, 1, 45632), -- Dragon Isles Adventurer
(198096, 1, 104198, 1, 1, 45632), -- Valdrakken Flightmage
(198096, 0, 104187, 1, 1, 45632); -- Valdrakken Flightmage

UPDATE `creature_template_model` SET `VerifiedBuild`=45632 WHERE (`Idx`=0 AND `CreatureID` IN (164954,61895,6174,164079,60849,173327,156686,150122,147785,3513,159478,173318,43820,175526,156777,164962,162666,148796,1976,24207,168353,156734,188523,12781,173548,1324,352,164685,87503,31697,51440,2456,151937,12481,12480,176229,284,173386,149436,52030,149616,173118,1310,176220,158456,173364,1346,164803,176067,50523,31146,164098,51348,1339,43499,1328,1312,89174,166949,49748,175082,155739,189085,43768,174146,1309,21354,3505,5499,1413,2795,3508,175208,164100,156670,174871,1297,44252,149121,175211,14423,172702,1321,36871,32520,164367,175016,156672,156768,62809,85818,69791,173348,1402,173300,14438,164946,164952,87501,5694,305,155011,2485,1320,170557,171299,43769,103033,4981,18357,61838,12787,52359,5566,918,176186,175212,5497,1289,23050,165403,3628,31902,164579,156671,5500,170310,164596,2331,173354,82564,164960,156479,149626,1327,1302,18360,173304,1428,1294,3511,89,156691,52358,2457,167738,140403,61834,43694,1301,156669,167880,23837,165657,62822,308,1721,44773,69974,55370,176244,175051,162918,175206,164368,156791,85307,164949,164353,173706,167881,5483,156698,1414,417,29726,340,4974,148233,175080,92870,14560,156735,158755,174922,84745,338,140253,175019,164961,62913,50669,164940,35477,32562,1300,42288,5493,175435,179896,176146,146633,141270,158440,175525,1313,48632,164957,164095,52029,1285,12786,164352,12779,175081,2533,156696,164953,50480,1347,175416,173367,28347,61896,26125,176233,164942,175066,5565,1318,3507,4269,15659,156668,153292,173352,5193,5498,173610,49540,6112,176064,175911,12784,148124,140407,173369,176235,29142,18406,3509,164955,1299,1291,156681,162928,2532,1432,62821,58154,164939,18362,54660,164096,331,52361,164956,2198,50524,176192,170640,156758,31912,164099,175020,173545,61080,4075,147714,1477,168011,176230,42421,46180,1478,1319,3504,171796,31717,7208,44237,84749,5503,164943,277,163007,29093,2330,61841,175213,1431,164684,44583,84751,188151,54638,149469,182864,149131,19848,8719,416,14559,171790,12780,178792,1303,162896,175420,1141,156685,61081,187734,85816,1333,5564,147741,175207,50269,149445,1412,156688,43822,166312,35845,2708,158436,173330,1315,170607,164948,156666,176221,51998,1307,53006,156690,43692,43693,3629,173350,3627,164736,1257,44245,149467,175042,158463,56925,177829,8383,6946,279,1316,6740,143622,61029,173370,31695,482,164941,196581,1286,1295,111190,1326,1317,11096,171822,6090,173351,5567,62982,3520,3626,17252,175067,49877,14561,165405,162929,5386,28355,156732,164947,176197,1275,61837,165796,2334,99541,1323,181681,5482,173388,18376,178804,149433,73400,165374,32151,18375,156733,156687,3518,68,1415,63508,42339,8670,167429,156694,173571,85817,12785,43819,44582,173305,12783,165379,13283,44774,175215,4078,85819,156692,164945,2455,174564,156667,173357,189161,169524,5494,38821,5081,4961,29264,71526,73190,721,11068,149099,149124,52408,1287,173325,1308,69975,6089,175218,176137,1419,1298,175210,173302,50525,1292,100820,59764,32158,162935,164950,148196,483,69792,176203,1427,1311,176237,114832,176332,173301,31778,1395,165189,61836,156689,46602,1341,7207,1429,185576,176226,170256,1325,173356,14439,176065,166061,173353,156769,167591,173355,1314,166307,62954,175083,175222,175209,44246,156683,164123,3510,3512,54569,175017,176545,158753)) OR (`Idx`=1 AND `CreatureID` IN (147785,175526,148796,1976,156734,173548,149436,149616,173118,51348,175082,155739,175208,175211,32520,175016,173300,170310,149626,173304,140403,23837,55370,175206,148233,140253,175019,175525,26125,175066,49540,148124,140407,52361,156758,175020,173545,61080,4075,147714,42421,171796,175213,54638,149469,149131,147741,175207,149445,35845,170607,149467,175042,143622,111190,171822,173351,175067,99541,149433,73400,68,42339,175215,38821,721,149099,149124,175218,100820,162935,176332,170256,62954,175222,175209,175017)) OR (`Idx`=2 AND `CreatureID` IN (156734,149436,149616,173118,175082,175208,175211,175016,173300,173304,140403,175206,140253,175525,26125,175066,49540,156758,175020,4075,42421,171796,175213,149469,149131,175207,149445,170607,149467,175042,143622,173351,175067,99541,149433,68,42339,175215,149124,175218,100820,176332,62954,175222,175209,175017)) OR (`Idx`=3 AND `CreatureID` IN (149436,149616,173118,175208,175211,175016,173300,173304,140403,175206,140253,26125,175066,156758,175020,171796,149469,149131,175207,149445,170607,149467,175042,173351,175067,99541,149433,68,42339,175215,175218,176332,175222,175017)) OR (`Idx`=5 AND `CreatureID` IN (173118,175208,175211,175016,173300,140403,175206,140253,175207,175218,176332,175222)) OR (`Idx`=4 AND `CreatureID` IN (173118,175208,175211,175016,173300,173304,140403,175206,140253,149131,175207,170607,175042,175215,175218,176332,175222,175017)) OR (`Idx`=15 AND `CreatureID` IN (140403,140253)) OR (`Idx`=14 AND `CreatureID` IN (140403,140253)) OR (`Idx`=13 AND `CreatureID` IN (140403,140253)) OR (`Idx`=12 AND `CreatureID` IN (140403,140253)) OR (`Idx`=11 AND `CreatureID` IN (140403,140253,176332)) OR (`Idx`=10 AND `CreatureID` IN (140403,140253,176332)) OR (`Idx`=9 AND `CreatureID` IN (140403,140253,176332)) OR (`Idx`=8 AND `CreatureID` IN (140403,140253,176332)) OR (`Idx`=7 AND `CreatureID` IN (140403,140253,176332)) OR (`Idx`=6 AND `CreatureID` IN (140403,140253,176332)) OR (`Idx`=51 AND `CreatureID`=140253) OR (`Idx`=50 AND `CreatureID`=140253) OR (`Idx`=49 AND `CreatureID`=140253) OR (`Idx`=48 AND `CreatureID`=140253) OR (`Idx`=47 AND `CreatureID`=140253) OR (`Idx`=46 AND `CreatureID`=140253) OR (`Idx`=45 AND `CreatureID`=140253) OR (`Idx`=44 AND `CreatureID`=140253) OR (`Idx`=43 AND `CreatureID`=140253) OR (`Idx`=42 AND `CreatureID`=140253) OR (`Idx`=41 AND `CreatureID`=140253) OR (`Idx`=40 AND `CreatureID`=140253) OR (`Idx`=39 AND `CreatureID`=140253) OR (`Idx`=38 AND `CreatureID`=140253) OR (`Idx`=37 AND `CreatureID`=140253) OR (`Idx`=36 AND `CreatureID`=140253) OR (`Idx`=35 AND `CreatureID`=140253) OR (`Idx`=34 AND `CreatureID`=140253) OR (`Idx`=33 AND `CreatureID`=140253) OR (`Idx`=32 AND `CreatureID`=140253) OR (`Idx`=31 AND `CreatureID`=140253) OR (`Idx`=30 AND `CreatureID`=140253) OR (`Idx`=29 AND `CreatureID`=140253) OR (`Idx`=28 AND `CreatureID`=140253) OR (`Idx`=27 AND `CreatureID`=140253) OR (`Idx`=26 AND `CreatureID`=140253) OR (`Idx`=25 AND `CreatureID`=140253) OR (`Idx`=24 AND `CreatureID`=140253) OR (`Idx`=23 AND `CreatureID`=140253) OR (`Idx`=22 AND `CreatureID`=140253) OR (`Idx`=21 AND `CreatureID`=140253) OR (`Idx`=20 AND `CreatureID`=140253) OR (`Idx`=19 AND `CreatureID`=140253) OR (`Idx`=18 AND `CreatureID`=140253) OR (`Idx`=17 AND `CreatureID`=140253) OR (`Idx`=16 AND `CreatureID`=140253);



DELETE FROM `gameobject_template` WHERE `entry` IN (383582 /*10FX_Valdrakken_Portal*/, 364430 /*Chair*/, 364429 /*Chair*/, 364439 /*Chair*/, 364426 /*Chair*/, 351981 /*Chair*/, 364438 /*Chair*/, 364433 /*Chair*/, 364435 /*Chair*/, 364434 /*Chair*/, 364428 /*Chair*/, 364431 /*Chair*/, 364432 /*Chair*/, 375407 /*Calmed Soul River*/, 377031 /*Soul River*/, 364437 /*Chair*/);
INSERT INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `IconName`, `castBarCaption`, `unk1`, `size`, `Data0`, `Data1`, `Data2`, `Data3`, `Data4`, `Data5`, `Data6`, `Data7`, `Data8`, `Data9`, `Data10`, `Data11`, `Data12`, `Data13`, `Data14`, `Data15`, `Data16`, `Data17`, `Data18`, `Data19`, `Data20`, `Data21`, `Data22`, `Data23`, `Data24`, `Data25`, `Data26`, `Data27`, `Data28`, `Data29`, `Data30`, `Data31`, `Data32`, `Data33`, `Data34`, `ContentTuningId`, `VerifiedBuild`) VALUES
(383582, 5, 77931, '10FX_Valdrakken_Portal', '', '', '', 0.999999761581420898, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45632), -- 10FX_Valdrakken_Portal
(364430, 7, 15617, 'Chair', '', '', '', 0.999999940395355224, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45632), -- Chair
(364429, 7, 32290, 'Chair', '', '', '', 0.999999940395355224, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45632), -- Chair
(364439, 7, 17820, 'Chair', '', '', '', 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45632), -- Chair
(364426, 7, 15617, 'Chair', '', '', '', 0.999999821186065673, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45632), -- Chair
(351981, 7, 32512, 'Chair', '', '', '', 0.999998748302459716, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45632), -- Chair
(364438, 7, 17820, 'Chair', '', '', '', 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45632), -- Chair
(364433, 7, 15617, 'Chair', '', '', '', 0.999999940395355224, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45632), -- Chair
(364435, 7, 15617, 'Chair', '', '', '', 0.999999940395355224, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45632), -- Chair
(364434, 7, 15618, 'Chair', '', '', '', 1.509765505790710449, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45632), -- Chair
(364428, 7, 15617, 'Chair', '', '', '', 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45632), -- Chair
(364431, 7, 15617, 'Chair', '', '', '', 0.999999940395355224, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45632), -- Chair
(364432, 7, 15617, 'Chair', '', '', '', 0.999999940395355224, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45632), -- Chair
(375407, 5, 72992, 'Calmed Soul River', '', '', '', 0.999999523162841796, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45632), -- Calmed Soul River
(377031, 5, 74881, 'Soul River', '', '', '', 0.999999761581420898, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45632), -- Soul River
(364437, 7, 62460, 'Chair', '', '', '', 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45632); -- Chair

UPDATE `gameobject_template` SET `VerifiedBuild`=45632 WHERE `entry` IN (197118, 369526, 197007, 209039, 353750, 105175, 197056, 197189, 201504, 353488, 357315, 197074, 353489, 292774, 201524, 354681, 201502, 201547, 197008, 270011, 357578, 357270, 197085, 357267, 353487, 250672, 201513, 201516, 197068, 202259, 201537, 197045, 205107, 197186, 197082, 197125, 197021, 197054, 357263, 201497, 201558, 357269, 357323, 352746, 197124, 202260, 203978, 197048, 197092, 197183, 200313, 355054, 365154, 200306, 357289, 353486, 357306, 201538, 311875, 357266, 197011, 197047, 201556, 206110, 369529, 369535, 357262, 353478, 364419, 200308, 357316, 197051, 197012, 201550, 175758, 357277, 365157, 197174, 197181, 201505, 200311, 197062, 357313, 197073, 197098, 202253, 201530, 357294, 203800, 197059, 200315, 197050, 292771, 201508, 201528, 357326, 197070, 197150, 357302, 201540, 197139, 375073, 197044, 197193, 353476, 201541, 197065, 353490, 197071, 201529, 197137, 201552, 200310, 323842, 357293, 201560, 358584, 203801, 197149, 323844, 197017, 197185, 201515, 201545, 353822, 376419, 369533, 201543, 345445, 209692, 197030, 200314, 201511, 197187, 364499, 202258, 357272, 197061, 202257, 322639, 197063, 197175, 201519, 201514, 358585, 357318, 357322, 205106, 197140, 201554, 357287, 197060, 259008, 353494, 353823, 369536, 197184, 203762, 197131, 357307, 197031, 354922, 197057, 197177, 201503, 197080, 197188, 197178, 357305, 369530, 197136, 201506, 201542, 367758, 202256, 365155, 200317, 197090, 201533, 197116, 197066, 197138, 357321, 197058, 354923, 201498, 357310, 354924, 207661, 355972, 201559, 353482, 364497, 369528, 293422, 197013, 380543, 357340, 197119, 201551, 357324, 175729, 357300, 197022, 197121, 357314, 353493, 197055, 353477, 197077, 197191, 353481, 357282, 197083, 197078, 197024, 303148, 197120, 197134, 335930, 124374, 197032, 323845, 201536, 201525, 197173, 200316, 353480, 201510, 205190, 353492, 357311, 200312, 200309, 281339, 201501, 201507, 201527, 369531, 197135, 357271, 364424, 197192, 367759, 197084, 364427, 201522, 357299, 357292, 197123, 197148, 201520, 357286, 201535, 197093, 358587, 105174, 197117, 197179, 357274, 369527, 200307, 201555, 197023, 357301, 201534, 197172, 201509, 354921, 345444, 201500, 201549, 357278, 197122, 357308, 201532, 369532, 353406, 358586, 197014, 197146, 201521, 201526, 369534, 197147, 197099, 323846, 201553, 197052, 197067, 357285, 201539, 197190, 197089, 332224, 197081, 259114, 201523, 323840, 197079, 201518, 197064, 197046, 293696, 353484, 201544, 357264, 197009, 201499, 358588, 357275, 357325, 365156, 357319, 353485, 353483, 191083, 323841, 353479, 197049, 201557, 357298, 197091, 278802, 357303, 197180, 323843, 197126, 197075, 357273, 357095, 197132, 357288, 197133, 197182, 357327, 197076, 352745, 355063, 201531, 197053, 197069, 357291, 364423, 197176, 197072, 294556, 190536, 201548, 353491, 364422, 357320, 201512, 364436, 179706, 201546);


UPDATE `gameobject_questitem` SET `VerifiedBuild`=45632 WHERE (`Idx`=0 AND `GameObjectEntry` IN (105175,203800,203801,203762,105174,278802));

