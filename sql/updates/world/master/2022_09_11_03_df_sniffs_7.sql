
SET @CGUID := 230803 ;
SET @OGUID := 239554 ;


UPDATE `creature_equip_template` SET `VerifiedBuild`=45505 WHERE (`ID`=1 AND `CreatureID` IN (187629,195515,191314));

DELETE FROM `areatrigger_template` WHERE (`Id`=29975 AND `IsServerSide`=0);
INSERT INTO `areatrigger_template` (`Id`, `IsServerSide`, `Type`, `Flags`, `Data0`, `Data1`, `Data2`, `Data3`, `Data4`, `Data5`, `Data6`, `Data7`, `VerifiedBuild`) VALUES
(29975, 0, 0, 0, 500, 500, 0, 0, 0, 0, 0, 0, 45505);



UPDATE `conversation_actors` SET `VerifiedBuild`=45505 WHERE (`ConversationId`=18650 AND `Idx`=0);


UPDATE `conversation_line_template` SET `VerifiedBuild`=45505 WHERE `Id`=47956;


UPDATE `conversation_template` SET `VerifiedBuild`=45505 WHERE `Id`=18650;

DELETE FROM `gameobject_template_addon` WHERE `entry`=382536;
INSERT INTO `gameobject_template_addon` (`entry`, `faction`, `flags`, `WorldEffectID`, `AIAnimKitID`) VALUES
(382536, 0, 1, 0, 0); -- Oathstone

UPDATE `quest_poi` SET `VerifiedBuild`=45505 WHERE (`QuestID`=66783 AND `BlobIndex`=0 AND `Idx1`=5) OR (`QuestID`=66783 AND `BlobIndex`=0 AND `Idx1`=4) OR (`QuestID`=66783 AND `BlobIndex`=0 AND `Idx1`=3) OR (`QuestID`=66783 AND `BlobIndex`=0 AND `Idx1`=2) OR (`QuestID`=66783 AND `BlobIndex`=0 AND `Idx1`=1) OR (`QuestID`=66783 AND `BlobIndex`=0 AND `Idx1`=0);

UPDATE `quest_poi_points` SET `VerifiedBuild`=45505 WHERE (`QuestID`=66783 AND `Idx1`=5 AND `Idx2`=0) OR (`QuestID`=66783 AND `Idx1`=4 AND `Idx2`=0) OR (`QuestID`=66783 AND `Idx1`=3 AND `Idx2`=0) OR (`QuestID`=66783 AND `Idx1`=2 AND `Idx2`=0) OR (`QuestID`=66783 AND `Idx1`=1 AND `Idx2`=0) OR (`QuestID`=66783 AND `Idx1`=0 AND `Idx2`=0);

DELETE FROM `quest_request_items` WHERE `ID`=66783;
INSERT INTO `quest_request_items` (`ID`, `EmoteOnComplete`, `EmoteOnIncomplete`, `EmoteOnCompleteDelay`, `EmoteOnIncompleteDelay`, `CompletionText`, `VerifiedBuild`) VALUES
(66783, 0, 0, 0, 0, '', 0); -- Renewal of Vows

UPDATE `creature_questender` SET `VerifiedBuild`=45505 WHERE (`id`=188181 AND `quest`=66783);


DELETE FROM `creature` WHERE `guid` BETWEEN @CGUID+0 AND @CGUID+58;
INSERT INTO `creature` (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnDifficulties`, `PhaseId`, `PhaseGroup`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `wander_distance`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`, `VerifiedBuild`) VALUES
(@CGUID+0, 195521, 2444, 13645, 13921, '0', '0', 0, 0, 0, -1138.66845703125, 5132.275390625, 20.04955673217773437, 2.76751112937927246, 7200, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Shikaar Hunter (Area: -0- - Difficulty: 0)
(@CGUID+1, 188181, 2444, 13645, 13921, '0', '0', 0, 0, 0, -1152.4166259765625, 5145.58154296875, 21.28801536560058593, 4.485785961151123046, 7200, 0, 0, 51910, 2790, 0, 0, 0, 0, 45505), -- Merithra (Area: -0- - Difficulty: 0)
(@CGUID+2, 190437, 2444, 13645, 13921, '0', '0', 0, 0, 0, -1183.0849609375, 5126.84423828125, 25.92088890075683593, 2.888539314270019531, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Dreamtail Nymph (Area: -0- - Difficulty: 0)
(@CGUID+3, 188601, 2444, 13645, 13921, '0', '0', 0, 0, 0, -1151.09033203125, 5130.27001953125, 20.57643318176269531, 2.223724126815795898, 7200, 0, 0, 51910, 0, 0, 0, 0, 0, 45505), -- Khanam Matra Sarest (Area: -0- - Difficulty: 0)
(@CGUID+4, 191210, 2444, 13645, 13921, '0', '0', 0, 0, 0, -1156.1805419921875, 5128.13818359375, 20.95659828186035156, 1.654351353645324707, 7200, 0, 0, 51910, 0, 0, 0, 0, 0, 45505), -- Tigari Khan (Area: -0- - Difficulty: 0) (Auras: )
(@CGUID+5, 190437, 2444, 13645, 13921, '0', '0', 0, 0, 0, -1131.3939208984375, 5103.07568359375, 22.95772743225097656, 0.052199747413396835, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Dreamtail Nymph (Area: -0- - Difficulty: 0)
(@CGUID+6, 195355, 2444, 13645, 13921, '0', '0', 0, 0, 0, -1145.54345703125, 5113.15283203125, 19.6410675048828125, 2.117749929428100585, 7200, 0, 0, 264578, 0, 0, 0, 0, 0, 45505), -- Hesthera (Area: -0- - Difficulty: 0)
(@CGUID+7, 190437, 2444, 13645, 13921, '0', '0', 0, 0, 0, -1156.46435546875, 5169.181640625, 25.67140388488769531, 0.7304421067237854, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Dreamtail Nymph (Area: -0- - Difficulty: 0)
-- (@CGUID+8, 191209, 0, 13645, 13921, '0', '0', 0, 0, 0, 0.524999976158142089, 0, 0.104999996721744537, 0, 7200, 0, 0, 57101, 0, 0, 0, 0, 0, 45505), -- Ohuna Feather (Area: -0- - Difficulty: 0) (Auras: 46598 - Ride Vehicle Hardcoded) - !!! on transport - transport template not found !!!
(@CGUID+9, 191314, 2444, 13645, 13921, '0', '0', 0, 0, 1, -1145.4635009765625, 5136.8046875, 20.56675338745117187, 2.704329252243041992, 7200, 0, 0, 62292, 0, 0, 0, 0, 0, 45505), -- Okir (Area: -0- - Difficulty: 0)
(@CGUID+10, 189715, 2444, 13645, 13921, '0', '0', 0, 0, 0, -1156.6822509765625, 5154.95166015625, 21.3944854736328125, 4.441327571868896484, 7200, 0, 0, 519100, 0, 0, 0, 0, 0, 45505), -- Gerithus (Area: -0- - Difficulty: 0)
(@CGUID+11, 194932, 2444, 13645, 13921, '0', '0', 0, 0, 0, -1141.2864990234375, 5126.30908203125, 20.00724220275878906, 2.64928603172302246, 7200, 0, 0, 132289, 3155, 0, 0, 0, 0, 45505), -- Ohn'ir Windsage (Area: -0- - Difficulty: 0)
(@CGUID+12, 194932, 2444, 13645, 13921, '0', '0', 0, 0, 0, -1134.782958984375, 5125.70654296875, 20.05399513244628906, 2.689342021942138671, 7200, 0, 0, 132289, 3155, 0, 0, 0, 0, 45505), -- Ohn'ir Windsage (Area: -0- - Difficulty: 0)
(@CGUID+13, 195521, 2444, 13645, 13921, '0', '0', 0, 0, 0, -1139.279541015625, 5121.572265625, 20.01914024353027343, 2.601165771484375, 7200, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Shikaar Hunter (Area: -0- - Difficulty: 0)
(@CGUID+14, 194932, 2444, 13645, 13921, '0', '0', 0, 0, 0, -1147.170166015625, 5123.9677734375, 20.021392822265625, 2.51767587661743164, 7200, 0, 0, 132289, 3155, 0, 0, 0, 0, 45505), -- Ohn'ir Windsage (Area: -0- - Difficulty: 0)
(@CGUID+15, 188335, 2444, 13645, 13921, '0', '0', 0, 0, 0, -1116.6441650390625, 5152.78369140625, 20.32801437377929687, 3.975255727767944335, 7200, 0, 0, 103820, 0, 0, 0, 0, 0, 45505), -- Aronus (Area: -0- - Difficulty: 0)
(@CGUID+16, 195688, 2444, 13645, 13921, '0', '0', 0, 0, 0, -1161.6041259765625, 5133.66943359375, 21.5996551513671875, 0.148995876312255859, 7200, 0, 0, 51910, 0, 0, 0, 0, 0, 45505), -- Captain Exposition (Area: -0- - Difficulty: 0)
-- (@CGUID+17, 181215, 0, 13645, 13921, '0', '0', 0, 0, 0, 0, 0, 0, 0, 7200, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Altan (Area: -0- - Difficulty: 0) (Auras: 46598 - Ride Vehicle Hardcoded) - !!! on transport - transport template not found !!!
(@CGUID+18, 188246, 2444, 13645, 13921, '0', '0', 0, 0, 0, -1147.3004150390625, 5134.3193359375, 20.64303398132324218, 2.799665212631225585, 7200, 0, 0, 51910, 0, 0, 0, 0, 0, 45505), -- Sansok Khan (Area: -0- - Difficulty: 0)
(@CGUID+19, 190437, 2444, 13645, 13921, '0', '0', 0, 0, 0, -1071.5726318359375, 5186.60107421875, 29.55170059204101562, 0.296392083168029785, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Dreamtail Nymph (Area: -0- - Difficulty: 0)
(@CGUID+20, 195356, 2444, 13645, 13921, '0', '0', 0, 0, 0, -1101.03125, 5159.95068359375, 22.34837722778320312, 3.841696023941040039, 7200, 0, 0, 264578, 0, 0, 0, 0, 0, 45505), -- Fernarus (Area: -0- - Difficulty: 0)
(@CGUID+21, 195515, 2444, 13645, 13921, '0', '0', 0, 0, 1, -1149.0989990234375, 5309.50341796875, 23.75857925415039062, 3.509075403213500976, 7200, 0, 0, 529156, 3155, 0, 0, 0, 0, 45505), -- Elder Boughweaver (Area: -0- - Difficulty: 0) (Auras: 13236 - Nature Channeling)
(@CGUID+22, 187629, 2444, 13645, 13921, '0', '0', 0, 0, 1, -1064.1961669921875, 5265.54345703125, 38.79330062866210937, 0.585788905620574951, 7200, 0, 0, 447730, 0, 0, 0, 0, 0, 45505), -- Elder Scaleguard (Area: -0- - Difficulty: 0) (Auras: )
(@CGUID+23, 190437, 2444, 13645, 13921, '0', '0', 0, 0, 0, -1287.53173828125, 5154.95849609375, 23.80098915100097656, 5.106032371520996093, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Dreamtail Nymph (Area: -0- - Difficulty: 0)
(@CGUID+24, 190437, 2444, 13645, 13921, '0', '0', 0, 0, 0, -1117.49609375, 5168.81640625, 25.28717613220214843, 4.953587532043457031, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Dreamtail Nymph (Area: -0- - Difficulty: 0)
(@CGUID+25, 195679, 2444, 13645, 13921, '0', '0', 0, 0, 0, -1240.1614990234375, 5165.1875, 23.3670654296875, 5.895205974578857421, 7200, 0, 0, 264578, 0, 0, 0, 0, 0, 45505), -- Green Dragon (Area: -0- - Difficulty: 0)
(@CGUID+26, 190437, 2444, 13645, 13921, '0', '0', 0, 0, 0, -1044.865234375, 5130.328125, 28.79628944396972656, 6.110866546630859375, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Dreamtail Nymph (Area: -0- - Difficulty: 0)
(@CGUID+27, 190437, 2444, 13645, 13921, '0', '0', 0, 0, 0, -1062.1656494140625, 5106.6767578125, 25.35725593566894531, 1.434087753295898437, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Dreamtail Nymph (Area: -0- - Difficulty: 0)
(@CGUID+28, 194932, 2444, 13645, 13921, '0', '0', 0, 0, 0, -1099.390625, 5141.7255859375, 20.80634498596191406, 3.199748992919921875, 7200, 0, 0, 132289, 3155, 0, 0, 0, 0, 45505), -- Ohn'ir Windsage (Area: -0- - Difficulty: 0)
(@CGUID+29, 190438, 2444, 13645, 13921, '0', '0', 0, 0, 0, -1133.333984375, 5054.166015625, -0.43072056770324707, 0.948048532009124755, 7200, 0, 0, 155730, 0, 0, 0, 0, 0, 45505), -- Jadeshell Tortoise (Area: -0- - Difficulty: 0)
(@CGUID+30, 195679, 2444, 13645, 13921, '0', '0', 0, 0, 0, -1220.9791259765625, 5151.40625, 21.03569221496582031, 5.959110736846923828, 7200, 0, 0, 264578, 0, 0, 0, 0, 0, 45505), -- Green Dragon (Area: -0- - Difficulty: 0)
(@CGUID+31, 194932, 2444, 13645, 13921, '0', '0', 0, 0, 0, -1150.40283203125, 5191.0390625, 22.57638931274414062, 4.417438030242919921, 7200, 0, 0, 132289, 3155, 0, 0, 0, 0, 45505), -- Ohn'ir Windsage (Area: -0- - Difficulty: 0)
(@CGUID+32, 195521, 2444, 13645, 13921, '0', '0', 0, 0, 0, -1103.4757080078125, 5145.6796875, 20.72747039794921875, 3.255542516708374023, 7200, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Shikaar Hunter (Area: -0- - Difficulty: 0)
(@CGUID+33, 190437, 2444, 13645, 13921, '0', '0', 0, 0, 0, -1089.8826904296875, 5082.9921875, 20.970672607421875, 5.610644817352294921, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Dreamtail Nymph (Area: -0- - Difficulty: 0)
(@CGUID+34, 194903, 2444, 13645, 13921, '0', '0', 0, 0, 0, -1097.6944580078125, 5136.2333984375, 20.91989707946777343, 3.082813501358032226, 7200, 0, 0, 519100, 0, 0, 0, 0, 0, 45505), -- Viranikus (Area: -0- - Difficulty: 0)
(@CGUID+35, 195521, 2444, 13645, 13921, '0', '0', 0, 0, 0, -1162.4617919921875, 5186.4365234375, 20.93764877319335937, 4.616278648376464843, 7200, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Shikaar Hunter (Area: -0- - Difficulty: 0)
(@CGUID+36, 190437, 2444, 13645, 13921, '0', '0', 0, 0, 0, -1042.1883544921875, 5048.44482421875, 17.39974784851074218, 2.753300189971923828, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Dreamtail Nymph (Area: -0- - Difficulty: 0)
(@CGUID+37, 190437, 2444, 13645, 13921, '0', '0', 0, 0, 0, -1099.3883056640625, 5119.86767578125, 25.35767555236816406, 3.478537559509277343, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Dreamtail Nymph (Area: -0- - Difficulty: 0)
(@CGUID+38, 195679, 2444, 13645, 13921, '0', '0', 0, 0, 0, -1221.32470703125, 5174.40185546875, 21.17467689514160156, 5.767394542694091796, 7200, 0, 0, 264578, 0, 0, 0, 0, 0, 45505), -- Green Dragon (Area: -0- - Difficulty: 0)
(@CGUID+39, 190437, 2444, 13645, 13921, '0', '0', 0, 0, 0, -1230.051513671875, 5132.32958984375, 25.56429100036621093, 0.826434493064880371, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Dreamtail Nymph (Area: -0- - Difficulty: 0)
(@CGUID+40, 190437, 2444, 13645, 13921, '0', '0', 0, 0, 0, -1262.400390625, 5133.1005859375, 29.52729606628417968, 2.136475086212158203, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Dreamtail Nymph (Area: -0- - Difficulty: 0)
(@CGUID+41, 195521, 2444, 13645, 13921, '0', '0', 0, 0, 0, -1103.19970703125, 5132.0537109375, 20.70941734313964843, 3.075957536697387695, 7200, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Shikaar Hunter (Area: -0- - Difficulty: 0)
(@CGUID+42, 194932, 2444, 13645, 13921, '0', '0', 0, 0, 0, -1164.298583984375, 5193.05810546875, 22.84263420104980468, 4.413965225219726562, 7200, 0, 0, 132289, 3155, 0, 0, 0, 0, 45505), -- Ohn'ir Windsage (Area: -0- - Difficulty: 0)
(@CGUID+43, 195679, 2444, 13645, 13921, '0', '0', 0, 0, 0, -1089.6041259765625, 5151.908203125, 24.0402984619140625, 3.416972637176513671, 7200, 0, 0, 264578, 0, 0, 0, 0, 0, 45505), -- Green Dragon (Area: -0- - Difficulty: 0)
(@CGUID+44, 195521, 2444, 13645, 13921, '0', '0', 0, 0, 0, -1154.1961669921875, 5187.7509765625, 21.40804481506347656, 4.559341907501220703, 7200, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Shikaar Hunter (Area: -0- - Difficulty: 0)
(@CGUID+45, 195358, 2444, 13645, 13921, '0', '0', 0, 0, 0, -1101.5538330078125, 5128.41943359375, 20.74261093139648437, 2.97065281867980957, 7200, 0, 0, 264578, 0, 0, 0, 0, 0, 45505), -- Berinus (Area: -0- - Difficulty: 0)
(@CGUID+46, 190437, 2444, 13645, 13921, '0', '0', 0, 0, 0, -1194.633056640625, 5190.1474609375, 26.03800010681152343, 5.634322166442871093, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Dreamtail Nymph (Area: -0- - Difficulty: 0)
(@CGUID+47, 195679, 2444, 13645, 13921, '0', '0', 0, 0, 0, -1234.5972900390625, 5143.1865234375, 23.27126884460449218, 0.026905383914709091, 7200, 0, 0, 264578, 0, 0, 0, 0, 0, 45505), -- Green Dragon (Area: -0- - Difficulty: 0)
(@CGUID+48, 195521, 2444, 13645, 13921, '0', '0', 0, 0, 0, -1157.998291015625, 5190.9384765625, 22.36931991577148437, 4.563798904418945312, 7200, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Shikaar Hunter (Area: -0- - Difficulty: 0)
(@CGUID+49, 190437, 2444, 13645, 13921, '0', '0', 0, 0, 0, -1253.5345458984375, 5176.7255859375, 30.39868927001953125, 0.254689455032348632, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Dreamtail Nymph (Area: -0- - Difficulty: 0)
(@CGUID+50, 187629, 2444, 13645, 13921, '0', '0', 0, 0, 1, -1037.515625, 5273.56689453125, 39.65468215942382812, 3.829662322998046875, 7200, 0, 0, 447730, 0, 0, 0, 0, 0, 45505), -- Elder Scaleguard (Area: -0- - Difficulty: 0) (Auras: )
-- (@CGUID+51, 181215, 0, 13645, 13921, '0', '0', 0, 0, 0, 0, 0, 0, 0, 7200, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Altan (Area: -0- - Difficulty: 0) (Auras: 46598 - Ride Vehicle Hardcoded) - !!! on transport - transport template not found !!!
(@CGUID+52, 191156, 2444, 13645, 13921, '0', '0', 0, 0, 0, -1156.1805419921875, 5128.140625, 20.956634521484375, 1.654352426528930664, 7200, 0, 0, 51910, 0, 0, 0, 0, 0, 45505), -- Tigari Khan (Area: -0- - Difficulty: 0) (Auras: )
(@CGUID+53, 190437, 2444, 13645, 13921, '0', '0', 0, 0, 0, -1109.7686767578125, 5272.068359375, 31.46386146545410156, 5.626540184020996093, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Dreamtail Nymph (Area: -0- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+54, 188601, 2444, 13645, 13921, '0', '0', 0, 0, 0, -1151.09033203125, 5130.27001953125, 20.65976715087890625, 2.223724126815795898, 7200, 0, 0, 51910, 0, 0, 0, 0, 0, 45505), -- Khanam Matra Sarest (Area: -0- - Difficulty: 0)
(@CGUID+55, 188105, 2444, 13645, 13921, '0', '0', 0, 0, 0, -1151.09033203125, 5130.26806640625, 20.57638931274414062, 2.223724126815795898, 7200, 0, 0, 51910, 0, 0, 0, 0, 0, 45505), -- Khanam Matra Sarest (Area: -0- - Difficulty: 0) (Auras: )
-- (@CGUID+56, 191208, 0, 13645, 13921, '0', '0', 0, 0, 0, -0.11500000208616256, 0, 0.115000002086162567, 5.846853256225585937, 7200, 0, 0, 57101, 0, 0, 0, 0, 0, 45505), -- Horn of the Khanam Matra (Area: -0- - Difficulty: 0) (Auras: 46598 - Ride Vehicle Hardcoded) - !!! on transport - transport template not found !!!
(@CGUID+57, 197600, 2444, 13645, 13921, '0', '0', 0, 0, 0, -1152.420166015625, 5145.580078125, 21.28803443908691406, 4.48579263687133789, 7200, 0, 0, 51910, 2790, 0, 0, 0, 0, 45505); -- Merithra (Area: -0- - Difficulty: 0) (Auras: )
-- (@CGUID+58, 197601, 0, 13645, 13921, '0', '0', 0, 0, 0, -0.42000001668930053, 0.489999979734420776, 0, 0, 7200, 0, 0, 57101, 0, 0, 0, 0, 0, 45505); -- Everblooming Soil (Area: -0- - Difficulty: 0) (Auras: 46598 - Ride Vehicle Hardcoded) - !!! on transport - transport template not found !!!
DELETE FROM `creature_addon` WHERE `guid` BETWEEN @CGUID+0 AND @CGUID+58;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `aiAnimKit`, `movementAnimKit`, `meleeAnimKit`, `visibilityDistanceType`, `auras`) VALUES
(@CGUID+2, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Dreamtail Nymph
(@CGUID+4, 0, 0, 0, 1, 0, 24697, 0, 0, 0, ''), -- Tigari Khan
(@CGUID+5, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Dreamtail Nymph
(@CGUID+7, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Dreamtail Nymph
-- (@CGUID+8, 0, 0, 0, 1, 0, 0, 0, 0, 0, '46598'), -- Ohuna Feather - 46598 - Ride Vehicle Hardcoded - !!! on transport - transport template not found !!!
-- (@CGUID+17, 0, 0, 0, 1, 0, 0, 0, 0, 0, '46598'), -- Altan - 46598 - Ride Vehicle Hardcoded - !!! on transport - transport template not found !!!
(@CGUID+19, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Dreamtail Nymph
(@CGUID+21, 0, 0, 0, 257, 0, 0, 0, 0, 0, '13236'), -- Elder Boughweaver - 13236 - Nature Channeling
(@CGUID+22, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Elder Scaleguard
(@CGUID+23, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Dreamtail Nymph
(@CGUID+24, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Dreamtail Nymph
(@CGUID+26, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Dreamtail Nymph
(@CGUID+27, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Dreamtail Nymph
(@CGUID+33, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Dreamtail Nymph
(@CGUID+36, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Dreamtail Nymph
(@CGUID+37, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Dreamtail Nymph
(@CGUID+39, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Dreamtail Nymph
(@CGUID+40, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Dreamtail Nymph
(@CGUID+46, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Dreamtail Nymph
(@CGUID+49, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Dreamtail Nymph
(@CGUID+50, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Elder Scaleguard
-- (@CGUID+51, 0, 0, 0, 1, 0, 0, 0, 0, 0, '46598'), -- Altan - 46598 - Ride Vehicle Hardcoded - !!! on transport - transport template not found !!!
(@CGUID+53, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Dreamtail Nymph
(@CGUID+55, 0, 0, 0, 1, 0, 24697, 0, 0, 0, ''), -- Khanam Matra Sarest
-- (@CGUID+56, 0, 0, 0, 1, 0, 0, 0, 0, 0, '46598'), -- Horn of the Khanam Matra - 46598 - Ride Vehicle Hardcoded - !!! on transport - transport template not found !!!
(@CGUID+57, 0, 0, 0, 1, 0, 22943, 0, 0, 0, ''); -- Merithra
-- (@CGUID+58, 0, 0, 0, 1, 0, 0, 0, 0, 0, '46598'); -- Everblooming Soil - 46598 - Ride Vehicle Hardcoded - !!! on transport - transport template not found !!!

DELETE FROM `gameobject` WHERE `guid` BETWEEN @OGUID+0 AND @OGUID+0;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnDifficulties`, `PhaseId`, `PhaseGroup`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `VerifiedBuild`) VALUES
(@OGUID+0, 382536, 2444, 13645, 13921, '0', '0', 0, -1170.5069580078125, 5140.7255859375, 20.63895606994628906, 5.942847728729248046, 0, 0, -0.16934871673583984, 0.985556185245513916, 7200, 255, 1, 45505); -- Oathstone (Area: -0- - Difficulty: 0)
DELETE FROM `gameobject_addon` WHERE `guid` BETWEEN @OGUID+0 AND @OGUID+0;


UPDATE `creature_template_scaling` SET `VerifiedBuild`=45505 WHERE (`DifficultyID`=0 AND `Entry` IN (197601,197600,191208,188105,191156,195358,194903,190438,195679,195515,195356,188246,188335,189715,191314,191209,195355,191210,188601,190437,188181));
UPDATE `creature_template_scaling` SET `ContentTuningID`=2468, `VerifiedBuild`=45505 WHERE (`Entry`=187629 AND `DifficultyID`=0);

DELETE FROM `creature_model_info` WHERE `DisplayID` IN (104431, 104441, 104382);
INSERT INTO `creature_model_info` (`DisplayID`, `BoundingRadius`, `CombatReach`, `DisplayID_Other_Gender`, `VerifiedBuild`) VALUES
(104431, 2.106381893157958984, 1.80000007152557373, 0, 45505),
(104441, 2.106381893157958984, 1.80000007152557373, 0, 45505),
(104382, 1.584961533546447753, 2.099999904632568359, 0, 45505);

UPDATE `creature_model_info` SET `VerifiedBuild`=45505 WHERE `DisplayID` IN (109623, 107412, 106223, 108916, 106227, 106432, 106968, 107414, 106842, 91239);
UPDATE `creature_model_info` SET `BoundingRadius`=0.75, `CombatReach`=15, `VerifiedBuild`=45505 WHERE `DisplayID`=106872;
UPDATE `creature_model_info` SET `BoundingRadius`=0.60000002384185791, `CombatReach`=12, `VerifiedBuild`=45505 WHERE `DisplayID`=108915;
UPDATE `creature_model_info` SET `BoundingRadius`=0.733282029628753662, `CombatReach`=1.60000002384185791 WHERE `DisplayID`=101442;

DELETE FROM `gossip_menu_option` WHERE (`MenuID`=28259 AND `OptionID` IN (54946,54948,54947)) OR (`MenuID`=28327 AND `OptionID` IN (56432,56431));
INSERT INTO `gossip_menu_option` (`MenuID`, `OptionID`, `OptionIcon`, `OptionText`, `OptionBroadcastTextId`, `OptionNpcFlag`, `Language`, `ActionMenuID`, `ActionPoiID`, `BoxCoded`, `BoxMoney`, `BoxText`, `BoxBroadcastTextID`, `VerifiedBuild`) VALUES
(28259, 54946, 0, '<Suggest she offer a child.>', 0, 1, 0, 0, 0, 0, 0, NULL, 0, 45505),
(28259, 54948, 0, '<Suggest she offer blood.>', 0, 1, 0, 0, 0, 0, 0, NULL, 0, 45505),
(28259, 54947, 0, '<Suggest she offer a verse.>', 0, 1, 0, 0, 0, 0, 0, NULL, 0, 45505),
(28327, 56432, 0, 'Here is proof of the unbroken lineage of Clan Teerai, direct descendants of the centaur Teera.', 0, 1, 0, 0, 0, 0, 0, NULL, 0, 45505),
(28327, 56431, 0, 'Here is a feather from Ohn\'ahra, lifted upon the wind.', 0, 1, 0, 0, 0, 0, 0, NULL, 0, 45505);



UPDATE `creature_template` SET `minlevel`=68, `maxlevel`=68 WHERE `entry`=187629; -- Elder Scaleguard
UPDATE `creature_template` SET `npcflag`=281474976710659 WHERE `entry`=188601; -- Khanam Matra Sarest

SET @GROUP_ID = 0;
SET @ID = 0;

replace INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) VALUES
(188181, @GROUP_ID+0, @ID+0, 'Ohn\'ahra\'s spirit blesses us all. I accept your offering.', 12, 0, 100, 2, 0, 205438, 0, 0, 'Merithra to Player'),
(188181, @GROUP_ID+1, @ID+0, 'I remember Teera well. You are... so much like her. I accept your offering.', 12, 0, 100, 2, 0, 205436, 0, 0, 'Merithra to Player'),
(188601, @GROUP_ID+0, @ID+0, 'A bloodline... I have an idea.', 12, 0, 100, 1, 0, 208477, 0, 0, 'Khanam Matra Sarest to Player'),
(188601, @GROUP_ID+1, @ID+0, 'The Khanam Matra draws a blade across her palm, allowing a few drops of her blood to fall into a cup.', 16, 0, 100, 1, 0, 208477, 0, 0, 'Khanam Matra Sarest to Player');

replace INTO `vehicle_template_accessory` (`entry`, `accessory_entry`, `seat_id`, `minion`, `description`, `summontype`, `summontimer`) VALUES
(197600, 197601, 0, 0, 'Merithra - Everblooming Soil', 0, 0), -- Merithra - Everblooming Soil
(188105, 191208, 0, 0, 'Khanam Matra Sarest - Horn of the Khanam Matra', 0, 0), -- Khanam Matra Sarest - Horn of the Khanam Matra
(191156, 181215, 0, 0, 'Tigari Khan - Altan', 0, 0), -- Tigari Khan - Altan
(191210, 191209, 1, 0, 'Tigari Khan - Ohuna Feather', 0, 0), -- Tigari Khan - Ohuna Feather
(191210, 181215, 0, 0, 'Tigari Khan - Altan', 0, 0); -- Tigari Khan - Altan

replace INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`, `user_type`) VALUES
(191209, 375472, 0, 0),
(191208, 375470, 0, 0),
(197601, 391289, 0, 0);


UPDATE `quest_template` SET `RewardBonusMoney`=1900, `VerifiedBuild`=45505 WHERE `ID`=66340; -- Into the Azure
UPDATE `quest_template` SET `RewardBonusMoney`=22950, `VerifiedBuild`=45505 WHERE `ID`=66783; -- Renewal of Vows
UPDATE `quest_template` SET `RewardBonusMoney`=15300 WHERE `ID`=65950;


UPDATE `quest_objectives` SET `VerifiedBuild`=45505 WHERE `ID` IN (430653, 430339, 428300, 428301, 428632, 428631, 428630, 428629, 428628, 428627, 428299);


UPDATE `quest_visual_effect` SET `VerifiedBuild`=45505 WHERE (`Index`=1 AND `ID` IN (430339,428300,428301,428299)) OR (`Index`=0 AND `ID` IN (430339,428300,428301,428299)) OR (`Index`=2 AND `ID` IN (428300,428301,428299));

