
DELETE FROM `gameobject_template_addon` WHERE `entry` IN (357638 /*357638*/, 364378 /*364378*/, 349559 /*349559*/);
INSERT INTO `gameobject_template_addon` (`entry`, `faction`, `flags`, `WorldEffectID`, `AIAnimKitID`) VALUES
(357638, 35, 48, 0, 0), -- 357638
(364378, 35, 32, 0, 0), -- 364378
(349559, 0, 16, 0, 0); -- 349559


SET @CGUID = 461476;
SET @OGUID = 400319;

DELETE FROM `creature` WHERE `guid` BETWEEN @CGUID+0 AND @CGUID+10;
INSERT INTO `creature` (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnDifficulties`, `PhaseId`, `PhaseGroup`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `wander_distance`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`, `VerifiedBuild`) VALUES
(@CGUID+0, 175025, 2453, 13546, 13546, '0', '0', 0, 0, 0, 1710.157958984375, 2105.939208984375, 385.341827392578125, 2.75336456298828125, 120, 0, 0, 5460, 0, 0, 0, 0, 0, 44730), -- 175025 (Area: Torghast, Tower of the Damned - Difficulty: 0) (Auras: 341125 - Portal)
(@CGUID+1, 175026, 2453, 13546, 13546, '0', '0', 0, 0, 0, 1672.63720703125, 2068.600830078125, 398.882659912109375, 1.955920815467834472, 120, 0, 0, 5460, 0, 0, 0, 0, 0, 44730), -- 175026 (Area: Torghast, Tower of the Damned - Difficulty: 0) (Auras: 341125 - Portal)
(@CGUID+2, 175027, 2453, 13546, 13546, '0', '0', 0, 0, 0, 1646.140625, 2063.157958984375, 398.872589111328125, 1.570647120475769042, 120, 0, 0, 5460, 0, 0, 0, 0, 0, 44730), -- 175027 (Area: Torghast, Tower of the Damned - Difficulty: 0) (Auras: 341125 - Portal)
(@CGUID+3, 175000, 2453, 13546, 13546, '0', '0', 0, 0, 0, 1709.9271240234375, 2158.873291015625, 385.341827392578125, 3.53955388069152832, 120, 0, 0, 5460, 0, 0, 0, 0, 0, 44730), -- 175000 (Area: Torghast, Tower of the Damned - Difficulty: 0) (Auras: 341125 - Portal)
(@CGUID+4, 175127, 2453, 13546, 13546, '0', '0', 0, 0, 0, 1646.310791015625, 2211.447998046875, 371.654541015625, 1.550410389900207519, 120, 0, 0, 218400, 5751, 0, 0, 0, 0, 44730), -- 175127 (Area: Torghast, Tower of the Damned - Difficulty: 0)
(@CGUID+5, 177282, 2453, 13546, 13546, '0', '0', 0, 0, 0, 1643.9722900390625, 2221.8369140625, 377.03662109375, 1.4015427827835083, 120, 0, 0, 15979, 0, 0, 0, 0, 0, 44730), -- 177282 (Area: Torghast, Tower of the Damned - Difficulty: 0)
(@CGUID+6, 183179, 2453, 13546, 13546, '0', '0', 0, 0, 0, 1582.189208984375, 2159.68408203125, 385.34185791015625, 5.9575347900390625, 120, 0, 0, 5460, 0, 0, 0, 0, 0, 44730), -- 183179 (Area: Torghast, Tower of the Damned - Difficulty: 0) (Auras: 341125 - Portal)
(@CGUID+7, 184047, 2453, 13546, 13546, '0', '0', 0, 0, 0, 1582.189208984375, 2159.68408203125, 385.34185791015625, 5.9575347900390625, 120, 0, 0, 5460, 0, 0, 0, 0, 0, 44730), -- 184047 (Area: Torghast, Tower of the Damned - Difficulty: 0)
(@CGUID+8, 175009, 2453, 13546, 13546, '0', '0', 0, 0, 0, 1715.390625, 2132.52783203125, 385.341827392578125, 3.131809234619140625, 120, 0, 0, 5460, 0, 0, 0, 0, 0, 44730), -- 175009 (Area: Torghast, Tower of the Damned - Difficulty: 0) (Auras: 341125 - Portal)
(@CGUID+9, 175028, 2453, 13546, 13546, '0', '0', 0, 0, 0, 1619.6146240234375, 2068.505126953125, 398.87762451171875, 1.157867908477783203, 120, 0, 0, 5460, 0, 0, 0, 0, 0, 44730), -- 175028 (Area: Torghast, Tower of the Damned - Difficulty: 0) (Auras: 341125 - Portal)
(@CGUID+10, 175029, 2453, 13546, 13546, '0', '0', 0, 0, 0, 1576.6475830078125, 2133.053955078125, 385.342315673828125, 0.020753482356667518, 120, 0, 0, 5460, 0, 0, 0, 0, 0, 44730); -- 175029 (Area: Torghast; Tower of the Damned - Difficulty: 0) (Auras: 341125 - Portal)
DELETE FROM `creature_addon` WHERE `guid` BETWEEN @CGUID+0 AND @CGUID+10;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `aiAnimKit`, `movementAnimKit`, `meleeAnimKit`, `visibilityDistanceType`, `auras`) VALUES
(@CGUID+0, 0, 0, 50331648, 1, 0, 0, 0, 0, 4, '341125'), -- 175025 - 341125 - Portal
(@CGUID+1, 0, 0, 50331648, 1, 0, 0, 0, 0, 4, '341125'), -- 175026 - 341125 - Portal
(@CGUID+2, 0, 0, 50331648, 1, 0, 0, 0, 0, 4, '341125'), -- 175027 - 341125 - Portal
(@CGUID+3, 0, 0, 50331648, 1, 0, 0, 0, 0, 4, '341125'), -- 175000 - 341125 - Portal
(@CGUID+4, 0, 0, 0, 1, 0, 0, 0, 0, 4, ''), -- 175127
(@CGUID+5, 0, 0, 33554432, 1, 0, 0, 0, 0, 4, ''), -- 177282
(@CGUID+6, 0, 0, 50331648, 1, 0, 0, 0, 0, 4, '341125'), -- 183179 - 341125 - Portal
(@CGUID+7, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- 184047
(@CGUID+8, 0, 0, 50331648, 1, 0, 0, 0, 0, 4, '341125'), -- 175009 - 341125 - Portal
(@CGUID+9, 0, 0, 50331648, 1, 0, 0, 0, 0, 4, '341125'), -- 175028 - 341125 - Portal
(@CGUID+10, 0, 0, 50331648, 1, 0, 0, 0, 0, 4, '341125'); -- 175029 - 341125 - Portal

DELETE FROM `gameobject` WHERE `guid` BETWEEN @OGUID+0 AND @OGUID+8;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnDifficulties`, `PhaseId`, `PhaseGroup`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `VerifiedBuild`) VALUES
(@OGUID+0, 349559, 2453, 13546, 13546, '0', '0', 0, 1576.2864990234375, 2132.475830078125, 384.84588623046875, 3.136808395385742187, 0, 0, 0.999997138977050781, 0.002392079913988709, 120, 255, 1, 44730), -- 349559 (Area: Torghast, Tower of the Damned - Difficulty: 0)
(@OGUID+1, 364378, 2453, 13546, 13546, '0', '0', 0, 1601.079833984375, 2312.3681640625, 384.664764404296875, 6.259900093078613281, 0, 0, -0.0116424560546875, 0.99993222951889038, 120, 255, 1, 44730), -- 364378 (Area: Torghast, Tower of the Damned - Difficulty: 0)
(@OGUID+2, 349559, 2453, 13546, 13546, '0', '0', 0, 1619.4444580078125, 2067.947998046875, 398.69964599609375, 4.320078372955322265, 0, 0, -0.83136177062988281, 0.555731594562530517, 120, 255, 1, 44730), -- 349559 (Area: Torghast, Tower of the Damned - Difficulty: 0)
(@OGUID+3, 357638, 2453, 13546, 13546, '0', '0', 0, 1646.2864990234375, 2341.317626953125, 381.183929443359375, 4.712389945983886718, 0, 0, -0.70710659027099609, 0.707106947898864746, 120, 255, 1, 44730), -- 357638 (Area: Torghast, Tower of the Damned - Difficulty: 0)
(@OGUID+4, 349559, 2453, 13546, 13546, '0', '0', 0, 1581.6492919921875, 2105.75, 385.037200927734375, 3.535939693450927734, 0, 0, -0.98062419891357421, 0.195898324251174926, 120, 255, 1, 44730), -- 349559 (Area: Torghast, Tower of the Damned - Difficulty: 0)
(@OGUID+5, 326155, 2453, 13546, 13546, '0', '0', 0, 1646.2430419921875, 2211.44091796875, 371.571197509765625, 0, 0, 0, 0, 1, 120, 255, 1, 44730), -- 326155 (Area: Torghast, Tower of the Damned - Difficulty: 0)
(@OGUID+6, 349559, 2453, 13546, 13546, '0', '0', 0, 1581.609375, 2159.81591796875, 384.027130126953125, 2.757843017578125, 0, 0, 0.981648445129394531, 0.19069962203502655, 120, 255, 1, 44730), -- 349559 (Area: Torghast, Tower of the Damned - Difficulty: 0)
(@OGUID+7, 349559, 2453, 13546, 13546, '0', '0', 0, 1710.6597900390625, 2159.192626953125, 384.95782470703125, 0.398011445999145507, 0, 0, 0.197694778442382812, 0.980263590812683105, 120, 255, 1, 44730), -- 349559 (Area: Torghast, Tower of the Damned - Difficulty: 0)
(@OGUID+8, 364526, 2453, 13546, 13546, '0', '0', 0, 1672.0594482421875, 2231.381103515625, 371.64605712890625, 3.537853479385375976, 0, 0, -0.98043632507324218, 0.196836546063423156, 120, 255, 1, 44730); -- 364526 (Area: Torghast; Tower of the Damned - Difficulty: 0)
DELETE FROM `gameobject_addon` WHERE `guid` BETWEEN @OGUID+0 AND @OGUID+8;
INSERT INTO `gameobject_addon` (`guid`, `parent_rotation0`, `parent_rotation1`, `parent_rotation2`, `parent_rotation3`, `WorldEffectID`, `AIAnimKitID`) VALUES
(@OGUID+8, 0, 0, 1, -0.00000004371138828, 0, 0); -- 364526

DELETE FROM `creature_template_addon` WHERE `entry` IN (175029 /*175029 - Portal*/, 175028 /*175028 - Portal*/, 175009 /*175009 - Portal*/, 184047 /*184047*/, 183179 /*183179 - Portal*/, 177282 /*177282*/, 175127 /*175127*/, 175000 /*175000 - Portal*/, 175027 /*175027 - Portal*/, 175026 /*175026 - Portal*/, 175025 /*175025 - Portal*/);
INSERT INTO `creature_template_addon` (`entry`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `aiAnimKit`, `movementAnimKit`, `meleeAnimKit`, `visibilityDistanceType`, `auras`) VALUES
(175029, 0, 0, 50331648, 1, 0, 0, 0, 0, 4, '341125'), -- 175029 - Portal
(175028, 0, 0, 50331648, 1, 0, 0, 0, 0, 4, '341125'), -- 175028 - Portal
(175009, 0, 0, 50331648, 1, 0, 0, 0, 0, 4, '341125'), -- 175009 - Portal
(184047, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- 184047
(183179, 0, 0, 50331648, 1, 0, 0, 0, 0, 4, '341125'), -- 183179 - Portal
(177282, 0, 0, 33554432, 1, 0, 0, 0, 0, 4, ''), -- 177282
(175127, 0, 0, 0, 1, 0, 0, 0, 0, 4, ''), -- 175127
(175000, 0, 0, 50331648, 1, 0, 0, 0, 0, 4, '341125'), -- 175000 - Portal
(175027, 0, 0, 50331648, 1, 0, 0, 0, 0, 4, '341125'), -- 175027 - Portal
(175026, 0, 0, 50331648, 1, 0, 0, 0, 0, 4, '341125'), -- 175026 - Portal
(175025, 0, 0, 50331648, 1, 0, 0, 0, 0, 4, '341125'); -- 175025 - Portal


DELETE FROM `creature_template_scaling` WHERE (`DifficultyID`=0 AND `Entry` IN (175029,175028,175009,184047,183179,177282,175127,175000,175027,175026,175025));
INSERT INTO `creature_template_scaling` (`Entry`, `DifficultyID`, `LevelScalingDeltaMin`, `LevelScalingDeltaMax`, `ContentTuningID`, `VerifiedBuild`) VALUES
(175029, 0, 0, 0, 709, 44730),
(175028, 0, 0, 0, 709, 44730),
(175009, 0, 0, 0, 709, 44730),
(184047, 0, 0, 0, 709, 44730),
(183179, 0, 0, 0, 709, 44730),
(177282, 0, 0, 0, 742, 44730),
(175127, 0, 0, 0, 709, 44730),
(175000, 0, 0, 0, 709, 44730),
(175027, 0, 0, 0, 709, 44730),
(175026, 0, 0, 0, 709, 44730),
(175025, 0, 0, 0, 709, 44730);


DELETE FROM `creature_model_info` WHERE `DisplayID` IN (101379, 95276, 23767);
INSERT INTO `creature_model_info` (`DisplayID`, `BoundingRadius`, `CombatReach`, `DisplayID_Other_Gender`, `VerifiedBuild`) VALUES
(101379, 2.511666536331176757, 0, 0, 44730),
(95276, 0.733025848865509033, 0, 0, 44730),
(23767, 0.300000011920928955, 1, 0, 44730);


DELETE FROM `gossip_menu` WHERE (`MenuID`=27033 AND `TextID`=212797);
INSERT INTO `gossip_menu` (`MenuID`, `TextID`, `VerifiedBuild`) VALUES
(27033, 212797, 44730); -- 177282

DELETE FROM `gossip_menu_option` WHERE (`MenuID`=27033 AND `OptionID`=0);
INSERT INTO `gossip_menu_option` (`MenuID`, `OptionID`, `OptionIcon`, `OptionText`, `OptionBroadcastTextId`, `OptionType`, `OptionNpcFlag`, `Language`, `ActionMenuID`, `ActionPoiID`, `BoxCoded`, `BoxMoney`, `BoxText`, `BoxBroadcastTextID`, `VerifiedBuild`) VALUES
(27033, 0, 32, '[Open Torghast Tech Tree]', 0, 0, 0, 0, 0, 0, 0, 0, NULL, 0, 44730);



DELETE FROM `gameobject_template` WHERE `entry` IN (364526 /*364526*/, 364378 /*364378*/, 349559 /*349559*/, 326155 /*326155*/, 357638 /*357638*/);
INSERT INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `IconName`, `castBarCaption`, `unk1`, `size`, `Data0`, `Data1`, `Data2`, `Data3`, `Data4`, `Data5`, `Data6`, `Data7`, `Data8`, `Data9`, `Data10`, `Data11`, `Data12`, `Data13`, `Data14`, `Data15`, `Data16`, `Data17`, `Data18`, `Data19`, `Data20`, `Data21`, `Data22`, `Data23`, `Data24`, `Data25`, `Data26`, `Data27`, `Data28`, `Data29`, `Data30`, `Data31`, `Data32`, `Data33`, `Data34`, `ContentTuningId`, `VerifiedBuild`) VALUES
(364526, 23, 46089, 'Meeting Stone', '', '', '', 0.999999940395355224, 1, 60, 13546, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 709, 44730), -- 364526
(364378, 5, 63457, 'Portal to the Runecarver\'s Oubliette', '', '', '', 0.75, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 709, 44730), -- 364378
(349559, 0, 6391, 'Invisble Blocker Collision Wall', '', '', '', 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 709, 44730), -- 349559
(326155, 5, 37971, 'Collision Object', '', '', '', 0.5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 44730), -- 326155
(357638, 0, 66087, 'Exit Torghast', '', '', '', 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 709, 44730); -- 357638


DELETE FROM `creature_template_movement` WHERE `CreatureId`=177282;
-- INSERT INTO `creature_template_movement` (`CreatureId`, `Ground`, `Swim`, `Flight`, `Rooted`, `Chase`, `Random`, `InteractionPauseTimer`) VALUES (177282, 0, 0, 1, 0, 0, 0, 0);


UPDATE creature_template SET npcflag = 1, ScriptName = 'npc_box_of_many_things' WHERE entry = 177282;