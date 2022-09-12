# TrinityCore - WowPacketParser
# File name: RogueDFPt1.pkt
# Detected build: V9_2_7_45505
# Targeted database: Shadowlands
# Parsing date: 09/10/2022 17:38:30

SET @CGUID := 176082;
SET @OGUID := 167540;




UPDATE `areatrigger_template` SET `Type`=0 WHERE (`IsServerSide`=0 AND `Id` IN (28714,2947,29625,27633,9225,23299,23297));
UPDATE `areatrigger_template` SET `Flags`=0, `VerifiedBuild`=45505 WHERE (`Id`=8382 AND `IsServerSide`=0);
UPDATE `areatrigger_template` SET `Type`=0, `Flags`=1024, `Data2`=0, `Data3`=0, `Data4`=0, `Data5`=0 WHERE (`Id`=13120 AND `IsServerSide`=0);
UPDATE `areatrigger_template` SET `Type`=0, `Flags`=1024, `Data2`=0, `Data3`=0, `Data4`=0, `Data5`=0 WHERE (`Id`=13120 AND `IsServerSide`=0);
UPDATE `areatrigger_template` SET `Type`=0, `Flags`=1024, `Data2`=0, `Data3`=0, `Data4`=0, `Data5`=0 WHERE (`Id`=13120 AND `IsServerSide`=0);
UPDATE `areatrigger_template` SET `Type`=0, `Flags`=1024, `Data2`=0, `Data3`=0, `Data4`=0, `Data5`=0 WHERE (`Id`=13120 AND `IsServerSide`=0);
UPDATE `areatrigger_template` SET `Type`=0, `Flags`=1024, `Data2`=0, `Data3`=0, `Data4`=0, `Data5`=0 WHERE (`Id`=13120 AND `IsServerSide`=0);
UPDATE `areatrigger_template` SET `VerifiedBuild`=45505 WHERE (`IsServerSide`=0 AND `Id` IN (9482,3678));
UPDATE `areatrigger_template` SET `Type`=0, `Flags`=1024, `Data2`=0, `Data4`=0, `Data5`=0 WHERE (`Id`=27842 AND `IsServerSide`=0);
UPDATE `areatrigger_template` SET `Type`=0, `Flags`=1040, `Data3`=0, `Data4`=0 WHERE (`Id`=6700 AND `IsServerSide`=0);
UPDATE `areatrigger_template` SET `Type`=0, `Flags`=1048, `Data2`=0, `Data3`=0, `Data5`=0 WHERE (`Id`=29741 AND `IsServerSide`=0);
UPDATE `areatrigger_template` SET `Type`=0, `Flags`=1024, `Data2`=0, `Data4`=0, `Data5`=0 WHERE (`Id`=27842 AND `IsServerSide`=0);
UPDATE `areatrigger_template` SET `Type`=0, `Data0`=7, `Data1`=7, `Data5`=0 WHERE (`Id`=28313 AND `IsServerSide`=0);
UPDATE `areatrigger_template` SET `Type`=3, `Data5`=0 WHERE (`Id`=28313 AND `IsServerSide`=0);

DELETE FROM `conversation_actors` WHERE (`Idx`=0 AND `ConversationId` IN (17865,17866,19082,19080,19423,19081,17844)) OR (`Idx`=3 AND `ConversationId`=19423) OR (`Idx`=2 AND `ConversationId`=19423) OR (`Idx`=1 AND `ConversationId`=19423);
INSERT INTO `conversation_actors` (`ConversationId`, `ConversationActorId`, `Idx`, `CreatureId`, `CreatureDisplayInfoId`, `NoActorObject`, `ActivePlayerObject`, `VerifiedBuild`) VALUES
(17865, 83898, 0, 0, 0, 0, 0, 45505), -- Full: 0x0
(17866, 83899, 0, 0, 0, 0, 0, 45505), -- Full: 0x2020900020B476C000367400001BFEE4 Creature/0 R2084/S13940 Map: 1 (Kalimdor) Entry: 184795 (Cataloger Kieule) Low: 1834724
(19082, 87045, 0, 0, 0, 0, 0, 45505), -- Full: 0x202090002003380000367400001BFEB0 Creature/0 R2084/S13940 Map: 1 (Kalimdor) Entry: 3296 (Orgrimmar Grunt) Low: 1834672
(19080, 87045, 0, 0, 0, 0, 0, 45505), -- Full: 0x202090002003380000367400001BFEC1 Creature/0 R2084/S13940 Map: 1 (Kalimdor) Entry: 3296 (Orgrimmar Grunt) Low: 1834689
(19423, 87599, 3, 0, 0, 0, 0, 45505), -- Full: 0x2020900020BCEA80002BC400001BFF15 Creature/0 R2084/S11204 Map: 1 (Kalimdor) Entry: 193450 (Archmage Khadgar) Low: 1834773
(19423, 87522, 2, 0, 0, 0, 0, 45505), -- Full: 0x2020900020B9C7C0002BC400001BFF15 Creature/0 R2084/S11204 Map: 1 (Kalimdor) Entry: 190239 (Ebyssian) Low: 1834773
(19423, 87521, 1, 0, 0, 0, 0, 45505), -- Full: 0x2020900020C0A7C0002BC400001BFF15 Creature/0 R2084/S11204 Map: 1 (Kalimdor) Entry: 197279 (Naleidea Rivergleam) Low: 1834773
(19423, 0, 0, 0, 0, 0, 1, 45505), -- Full: 0x0800040000000000FFFFFFFFFFFFFFFF Player/0 R1/S16777215 Map: 0 (Eastern Kingdoms) Low: 1099511627775
(19081, 87045, 0, 0, 0, 0, 0, 45505), -- Full: 0x202090002003380000367400001BFECF Creature/0 R2084/S13940 Map: 1 (Kalimdor) Entry: 3296 (Orgrimmar Grunt) Low: 1834703
(17844, 64220, 0, 190239, 63690, 0, 0, 45505);


DELETE FROM `conversation_line_template` WHERE `Id` IN (45494, 45493, 45495, 48699, 48695, 49750, 49523, 49522, 49837, 48697, 45414, 45413);
INSERT INTO `conversation_line_template` (`Id`, `UiCameraID`, `ActorIdx`, `Flags`, `VerifiedBuild`) VALUES
(45494, 0, 0, 0, 45505),
(45493, 0, 0, 0, 45505),
(45495, 0, 0, 0, 45505),
(48699, 0, 0, 0, 45505),
(48695, 0, 0, 0, 45505),
(49750, 0, 3, 0, 45505),
(49523, 0, 2, 0, 45505),
(49522, 0, 1, 0, 45505),
(49837, 0, 0, 0, 45505),
(48697, 0, 0, 0, 45505),
(45414, 1221, 0, 0, 45505),
(45413, 1221, 0, 0, 45505);


DELETE FROM `conversation_template` WHERE `Id` IN (19423, 17866, 19081, 17865, 19080, 19082, 17844);
INSERT INTO `conversation_template` (`Id`, `FirstLineID`, `TextureKitId`, `VerifiedBuild`) VALUES
(19423, 49837, 0, 45505),
(17866, 45495, 0, 45505),
(19081, 48697, 0, 45505),
(17865, 45493, 0, 45505),
(19080, 48695, 0, 45505),
(19082, 48699, 0, 45505),
(17844, 45413, 0, 45505);


DELETE FROM `gameobject_template_addon` WHERE `entry` IN (376704 /*Reliquary Pillow*/, 376708 /*Reliquary Crate*/, 355504 /*Portal*/, 355229 /*Portal to Oribos*/, 325890 /*Hyper-Compressed Ocean*/, 380543 /*Fire Wall*/, 245730 /*Reinforced Gate*/, 246039 /*Protective Barrier*/, 376419 /*Under Construction*/, 376514 /*Sleeping Mat*/);
INSERT INTO `gameobject_template_addon` (`entry`, `faction`, `flags`, `WorldEffectID`, `AIAnimKitID`) VALUES
(376704, 190, 0, 0, 0), -- Reliquary Pillow
(376708, 190, 0, 0, 0), -- Reliquary Crate
(355504, 2110, 8192, 0, 0), -- Portal
(355229, 1735, 0, 0, 3503), -- Portal to Oribos
(325890, 1816, 8388608, 0, 0), -- Hyper-Compressed Ocean
(380543, 0, 92307504, 0, 0), -- Fire Wall
(245730, 0, 32, 0, 0), -- Reinforced Gate
(246039, 0, 34, 0, 0), -- Protective Barrier
(376419, 1375, 8192, 0, 0), -- Under Construction
(376514, 1375, 0, 0, 0); -- Sleeping Mat

UPDATE `gameobject_template_addon` SET `faction`=1734, `WorldEffectID`=2773 WHERE `entry`=187376; -- NPC Fishing Bobber
UPDATE `gameobject_template_addon` SET `faction`=83 WHERE `entry`=35591; -- Fishing Bobber
UPDATE `gameobject_template_addon` SET `WorldEffectID`=16227 WHERE `entry` IN (207146, 207150, 207149, 207148, 207147); -- Barbershop Chair
UPDATE `gameobject_template_addon` SET `faction`=29 WHERE `entry`=259114; -- [DNT] Command Table Collision Cylinder
UPDATE `gameobject_template_addon` SET `WorldEffectID`=8830 WHERE `entry`=281340; -- Warchief's Command Board


DELETE FROM `scene_template` WHERE `SceneId`=3003;
INSERT INTO `scene_template` (`SceneId`, `Flags`, `ScriptPackageID`, `Encrypted`) VALUES
(3003, 27, 3582, 1);


DELETE FROM `quest_offer_reward` WHERE `ID` IN (65439 /*Whispers on the Winds*/, 65443 /*Expeditionary Coordination*/, 65437 /*Aspectral Invitation*/, 65435 /*The Dragon Isles Await*/);
INSERT INTO `quest_offer_reward` (`ID`, `Emote1`, `Emote2`, `Emote3`, `Emote4`, `EmoteDelay1`, `EmoteDelay2`, `EmoteDelay3`, `EmoteDelay4`, `RewardText`, `VerifiedBuild`) VALUES
(65439, 0, 0, 0, 0, 0, 0, 0, 0, '', 45505), -- Whispers on the Winds
(65443, 0, 0, 0, 0, 0, 0, 0, 0, '', 45505), -- Expeditionary Coordination
(65437, 0, 0, 0, 0, 0, 0, 0, 0, '', 45505), -- Aspectral Invitation
(65435, 0, 0, 0, 0, 0, 0, 0, 0, '', 45505); -- The Dragon Isles Await


DELETE FROM `quest_poi` WHERE (`QuestID`=70045 AND `BlobIndex`=0 AND `Idx1`=1) OR (`QuestID`=70045 AND `BlobIndex`=0 AND `Idx1`=0) OR (`QuestID`=65439 AND `BlobIndex`=0 AND `Idx1`=2) OR (`QuestID`=65439 AND `BlobIndex`=0 AND `Idx1`=1) OR (`QuestID`=65439 AND `BlobIndex`=0 AND `Idx1`=0) OR (`QuestID`=65443 AND `BlobIndex`=0 AND `Idx1`=4) OR (`QuestID`=65443 AND `BlobIndex`=0 AND `Idx1`=3) OR (`QuestID`=65443 AND `BlobIndex`=0 AND `Idx1`=2) OR (`QuestID`=65443 AND `BlobIndex`=0 AND `Idx1`=1) OR (`QuestID`=65443 AND `BlobIndex`=0 AND `Idx1`=0) OR (`QuestID`=65437 AND `BlobIndex`=0 AND `Idx1`=2) OR (`QuestID`=65437 AND `BlobIndex`=0 AND `Idx1`=1) OR (`QuestID`=65437 AND `BlobIndex`=0 AND `Idx1`=0);
INSERT INTO `quest_poi` (`QuestID`, `BlobIndex`, `Idx1`, `ObjectiveIndex`, `QuestObjectiveID`, `QuestObjectID`, `MapID`, `UiMapID`, `Priority`, `Flags`, `WorldEffectID`, `PlayerConditionID`, `NavigationPlayerConditionID`, `SpawnTrackingID`, `AlwaysAllowMergingBlobs`, `VerifiedBuild`) VALUES
(70045, 0, 1, 32, 0, 0, 1, 1, 0, 0, 0, 0, 0, 2246709, 0, 45505), -- Truths and Revelations
(70045, 0, 0, -1, 0, 0, 1, 85, 0, 0, 0, 0, 0, 2239044, 0, 45505), -- Truths and Revelations
(65439, 0, 2, 32, 0, 0, 1, 1, 0, 2, 0, 0, 0, 0, 0, 45505), -- Whispers on the Winds
(65439, 0, 1, 0, 429443, 193469, 1, 1, 0, 2, 0, 0, 0, 0, 0, 45505), -- Whispers on the Winds
(65439, 0, 0, -1, 0, 0, 1, 1, 0, 2, 0, 0, 0, 0, 0, 45505), -- Whispers on the Winds
(65443, 0, 4, 32, 0, 0, 1, 85, 0, 0, 0, 0, 0, 2212373, 0, 45505), -- Expeditionary Coordination
(65443, 0, 3, 2, 422987, 184780, 1, 85, 0, 2, 0, 0, 0, 0, 0, 45505), -- Expeditionary Coordination
(65443, 0, 2, 1, 422989, 184782, 1, 85, 0, 2, 0, 0, 0, 0, 0, 45505), -- Expeditionary Coordination
(65443, 0, 1, 0, 422988, 184781, 1, 85, 0, 2, 0, 0, 0, 0, 0, 45505), -- Expeditionary Coordination
(65443, 0, 0, -1, 0, 0, 1, 1, 0, 2, 0, 0, 0, 0, 0, 45505), -- Expeditionary Coordination
(65437, 0, 2, 32, 0, 0, 1, 85, 0, 2, 0, 0, 0, 2158408, 0, 45505), -- Aspectral Invitation
(65437, 0, 1, 0, 422958, 184790, 1, 85, 0, 2, 0, 0, 0, 2158408, 0, 45505), -- Aspectral Invitation
(65437, 0, 0, -1, 0, 0, 1, 85, 0, 2, 0, 0, 0, 2158408, 0, 45505); -- Aspectral Invitation

UPDATE `quest_poi` SET `VerifiedBuild`=45505 WHERE (`QuestID`=56120 AND `BlobIndex`=0 AND `Idx1`=1) OR (`QuestID`=56120 AND `BlobIndex`=0 AND `Idx1`=0) OR (`QuestID`=50598 AND `BlobIndex`=0 AND `Idx1`=0) OR (`QuestID`=50602 AND `BlobIndex`=0 AND `Idx1`=0) OR (`QuestID`=65435 AND `BlobIndex`=0 AND `Idx1`=0);
DELETE FROM `quest_poi_points` WHERE (`QuestID`=70045 AND `Idx1`=1 AND `Idx2`=0) OR (`QuestID`=70045 AND `Idx1`=0 AND `Idx2`=0) OR (`QuestID`=65439 AND `Idx1`=2 AND `Idx2`=0) OR (`QuestID`=65439 AND `Idx1`=1 AND `Idx2`=0) OR (`QuestID`=65439 AND `Idx1`=0 AND `Idx2`=0) OR (`QuestID`=65443 AND `Idx1`=4 AND `Idx2`=0) OR (`QuestID`=65443 AND `Idx1`=3 AND `Idx2`=0) OR (`QuestID`=65443 AND `Idx1`=2 AND `Idx2`=0) OR (`QuestID`=65443 AND `Idx1`=1 AND `Idx2`=0) OR (`QuestID`=65443 AND `Idx1`=0 AND `Idx2`=0) OR (`QuestID`=65437 AND `Idx1`=2 AND `Idx2`=0) OR (`QuestID`=65437 AND `Idx1`=1 AND `Idx2`=0) OR (`QuestID`=65437 AND `Idx1`=0 AND `Idx2`=0);
INSERT INTO `quest_poi_points` (`QuestID`, `Idx1`, `Idx2`, `X`, `Y`, `Z`, `VerifiedBuild`) VALUES
(70045, 1, 0, 1360, -4919, 62, 45505), -- Truths and Revelations
(70045, 0, 0, 1632, -4362, 64, 45505), -- Truths and Revelations
(65439, 2, 0, 1354, -4919, 0, 45505), -- Whispers on the Winds
(65439, 1, 0, 1354, -4924, 0, 45505), -- Whispers on the Winds
(65439, 0, 0, 1354, -4911, 0, 45505), -- Whispers on the Winds
(65443, 4, 0, 2049, -4275, 95, 45505), -- Expeditionary Coordination
(65443, 3, 0, 1898, -4749, 46, 45505), -- Expeditionary Coordination
(65443, 2, 0, 1826, -4178, 152, 45505), -- Expeditionary Coordination
(65443, 1, 0, 1858, -4497, 23, 45505), -- Expeditionary Coordination
(65443, 0, 0, 1349, -4911, 0, 45505), -- Expeditionary Coordination
(65437, 2, 0, 2044, -4273, 95, 45505), -- Aspectral Invitation
(65437, 1, 0, 2044, -4273, 95, 45505), -- Aspectral Invitation
(65437, 0, 0, 2043, -4270, 95, 45505); -- Aspectral Invitation

UPDATE `quest_poi_points` SET `VerifiedBuild`=45505 WHERE (`QuestID`=56120 AND `Idx1`=1 AND `Idx2`=0) OR (`QuestID`=56120 AND `Idx1`=0 AND `Idx2`=0) OR (`QuestID`=50598 AND `Idx1`=0 AND `Idx2`=0) OR (`QuestID`=50602 AND `Idx1`=0 AND `Idx2`=0) OR (`QuestID`=65435 AND `Idx1`=0 AND `Idx2`=0);

DELETE FROM `quest_details` WHERE `ID` IN (70045 /*Truths and Revelations*/, 65439 /*Whispers on the Winds*/, 65443 /*Expeditionary Coordination*/, 65437 /*Aspectral Invitation*/);
INSERT INTO `quest_details` (`ID`, `Emote1`, `Emote2`, `Emote3`, `Emote4`, `EmoteDelay1`, `EmoteDelay2`, `EmoteDelay3`, `EmoteDelay4`, `VerifiedBuild`) VALUES
(70045, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Truths and Revelations
(65439, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Whispers on the Winds
(65443, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Expeditionary Coordination
(65437, 0, 0, 0, 0, 0, 0, 0, 0, 45505); -- Aspectral Invitation

UPDATE `quest_details` SET `VerifiedBuild`=45505 WHERE `ID`=65435;

DELETE FROM `creature_queststarter` WHERE (`id`=193889 AND `quest`=70045) OR (`id`=193450 AND `quest`=65439) OR (`id`=184793 AND `quest`=65443) OR (`id`=190239 AND `quest`=65437);
INSERT INTO `creature_queststarter` (`id`, `quest`, `VerifiedBuild`) VALUES
(193889, 70045, 45505), -- Truths and Revelations offered Kodethi
(193450, 65439, 45505), -- Whispers on the Winds offered Archmage Khadgar
(184793, 65443, 45505), -- Expeditionary Coordination offered Naleidea Rivergleam
(190239, 65437, 45505); -- Aspectral Invitation offered Ebyssian


DELETE FROM `creature_questender` WHERE (`id`=190239 AND `quest` IN (65439,65437,65435)) OR (`id`=197279 AND `quest`=65443);
INSERT INTO `creature_questender` (`id`, `quest`, `VerifiedBuild`) VALUES
(190239, 65439, 45505), -- Whispers on the Winds ended by Ebyssian
(197279, 65443, 45505), -- Expeditionary Coordination ended by Naleidea Rivergleam
(190239, 65437, 45505), -- Aspectral Invitation ended by Ebyssian
(190239, 65435, 45505); -- The Dragon Isles Await ended by Ebyssian



DELETE FROM `creature` WHERE `guid` BETWEEN @CGUID+0 AND @CGUID+829;
INSERT INTO `creature` (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnDifficulties`, `PhaseId`, `PhaseGroup`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `wander_distance`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`, `VerifiedBuild`) VALUES
(@CGUID+0, 175135, 1, 1637, 5170, '0', '0', 0, 0, 1, 1664.267333984375, -4345.51416015625, 26.37074661254882812, 3.670068740844726562, 120, 0, 0, 33072250, 338700, 0, 0, 0, 0, 45505), -- Rokhan (Area: Valley of Strength - Difficulty: 0)
(@CGUID+1, 135202, 1, 1637, 5170, '0', '0', 0, 0, 0, 1578.1510009765625, -4456.71728515625, 15.71327495574951171, 0, 120, 0, 0, 17723, 2434, 0, 0, 0, 0, 45505), -- Meet your team (Area: Valley of Strength - Difficulty: 0)
(@CGUID+2, 100636, 1, 1637, 5170, '0', '0', 0, 0, 1, 1605.9254150390625, -4376.51025390625, 21.8164825439453125, 3.64670419692993164, 120, 0, 0, 81645, 0, 0, 0, 0, 0, 45505), -- High Overlord Saurfang (Area: Valley of Strength - Difficulty: 0) (Auras: )
(@CGUID+3, 49743, 1, 1637, 5170, '0', '0', 0, 0, 0, 1592.8656005859375, -4439.90869140625, 13.32641029357910156, 0.92016148567199707, 120, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Dung Beetle (Area: Valley of Strength - Difficulty: 0)
(@CGUID+4, 62195, 1, 1637, 5170, '0', '0', 0, 0, 1, 1511.5364990234375, -4399.8837890625, 22.75157546997070312, 3.876850843429565429, 120, 0, 0, 396867, 0, 0, 0, 0, 0, 45505), -- Shang'gok (Area: Valley of Strength - Difficulty: 0) (Auras: )
(@CGUID+5, 3342, 1, 1637, 5170, '0', '0', 0, 0, 1, 1627.989990234375, -4386.1298828125, 21.06553459167480468, 4.642575740814208984, 120, 0, 0, 145518, 0, 0, 0, 0, 0, 45505), -- Shan'ti (Area: Valley of Strength - Difficulty: 0) (Auras: )
(@CGUID+6, 38821, 1, 1637, 5170, '0', '0', 0, 0, 0, 1749.2099609375, -4280.22021484375, 104.7573394775390625, 1.710422635078430175, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Dave's Industrial Light and Magic Bunny (Medium)(Sessile) (Area: Valley of Strength - Difficulty: 0)
(@CGUID+7, 3370, 1, 1637, 5170, '0', '0', 0, 0, 1, 1565.15625, -4318.783203125, 23.31942176818847656, 5.391697883605957031, 120, 0, 0, 158747, 0, 0, 0, 0, 0, 45505), -- Urtrun Clanbringer (Area: Valley of Strength - Difficulty: 0) (Auras: )
(@CGUID+8, 51346, 1, 1637, 5170, '0', '0', 0, 0, 1, 1726.1009521484375, -4214.6005859375, 132.698333740234375, 2.864931344985961914, 120, 10, 0, 198434, 0, 1, 0, 0, 0, 45505), -- Orgrimmar Wind Rider (Area: Valley of Strength - Difficulty: 0) (Auras: ) (possible waypoints or random movement)
(@CGUID+9, 3296, 1, 1637, 5170, '0', '0', 0, 0, 1, 1436.56005859375, -4402.509765625, 74.002532958984375, 2.635447263717651367, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Orgrimmar Grunt (Area: Valley of Strength - Difficulty: 0) (Auras: )
(@CGUID+10, 3296, 1, 1637, 5170, '0', '0', 0, 0, 1, 1543.950439453125, -4329.189453125, 88.64775848388671875, 4.013505935668945312, 120, 10, 0, 198434, 0, 1, 0, 0, 0, 45505), -- Orgrimmar Grunt (Area: Valley of Strength - Difficulty: 0) (Auras: ) (possible waypoints or random movement)
(@CGUID+11, 49750, 1, 1637, 5170, '0', '0', 0, 0, 1, 1598.6180419921875, -4365.58154296875, 21.18857002258300781, 3.630284786224365234, 120, 0, 0, 5742, 0, 0, 0, 0, 0, 45505), -- Warchief's Herald (Area: Valley of Strength - Difficulty: 0) (Auras: )
(@CGUID+12, 44877, 1, 1637, 5170, '0', '0', 0, 0, 1, 1517.1400146484375, -4346.64990234375, 20.64493370056152343, 4.956735134124755859, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Grunt Soran (Area: Valley of Strength - Difficulty: 0) (Auras: )
(@CGUID+13, 102529, 1, 1637, 5170, '0', '0', 0, 0, 1, 1458.3055419921875, -4419.236328125, 25.53692626953125, 0.023553529754281044, 120, 0, 0, 35916, 0, 0, 0, 0, 0, 45505), -- Kor'vas Bloodthorn (Area: Valley of Strength - Difficulty: 0) (Auras: 222589 - Glaive Anim Replacement)
(@CGUID+14, 38821, 1, 1637, 5170, '0', '0', 0, 0, 0, 1738.2900390625, -4270.419921875, 108.159332275390625, 0.226892799139022827, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Dave's Industrial Light and Magic Bunny (Medium)(Sessile) (Area: Valley of Strength - Difficulty: 0)
(@CGUID+15, 51346, 1, 1637, 5170, '0', '0', 0, 0, 1, 1720.9337158203125, -4226.8994140625, 132.698333740234375, 2.802049160003662109, 120, 10, 0, 198434, 0, 1, 0, 0, 0, 45505), -- Orgrimmar Wind Rider (Area: Valley of Strength - Difficulty: 0) (Auras: ) (possible waypoints or random movement)
(@CGUID+16, 74228, 1, 1637, 5170, '0', '0', 0, 0, 1, 1541.801025390625, -4327.0693359375, 89.358612060546875, 4.001094818115234375, 120, 10, 0, 198434, 0, 1, 0, 0, 0, 45505), -- Darkspear Headhunter (Area: Valley of Strength - Difficulty: 0) (Auras: ) (possible waypoints or random movement)
(@CGUID+17, 74228, 1, 1637, 5170, '0', '0', 0, 0, 1, 1577.9005126953125, -4398.45751953125, 15.83656024932861328, 1.379724502563476562, 120, 10, 0, 198434, 0, 1, 0, 0, 0, 45505), -- Darkspear Headhunter (Area: Valley of Strength - Difficulty: 0) (Auras: ) (possible waypoints or random movement)
(@CGUID+18, 97296, 1, 1637, 5170, '0', '0', 0, 0, 1, 1464.467041015625, -4420.01904296875, 25.53692436218261718, 0.059084359556436538, 120, 0, 0, 47894, 19005, 0, 0, 0, 0, 45505), -- Archmage Khadgar (Area: Valley of Strength - Difficulty: 0)
(@CGUID+19, 49837, 1, 1637, 5170, '0', '0', 0, 0, 0, 1514.5147705078125, -4458.99169921875, 26.09406471252441406, 0.844569683074951171, 120, 10, 0, 27, 0, 1, 0, 0, 0, 45505), -- Spiny Lizard (Area: Valley of Strength - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+20, 51346, 1, 1637, 5170, '0', '0', 0, 0, 1, 1716.4248046875, -4220.61669921875, 131.4888153076171875, 2.755834579467773437, 120, 10, 0, 198434, 0, 1, 0, 0, 0, 45505), -- Orgrimmar Wind Rider (Area: Valley of Strength - Difficulty: 0) (Auras: ) (possible waypoints or random movement)
(@CGUID+21, 51346, 1, 1637, 5170, '0', '0', 0, 0, 1, 1680.3695068359375, -4307.45361328125, 114.30615234375, 5.317573070526123046, 120, 10, 0, 198434, 0, 1, 0, 0, 0, 45505), -- Orgrimmar Wind Rider (Area: Valley of Strength - Difficulty: 0) (Auras: ) (possible waypoints or random movement)
(@CGUID+22, 49743, 1, 1637, 5170, '0', '0', 0, 0, 0, 1565.7540283203125, -4386.91943359375, 16.61726760864257812, 5.716676235198974609, 120, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Dung Beetle (Area: Valley of Strength - Difficulty: 0) (Auras: )
(@CGUID+23, 62114, 1, 1637, 5170, '0', '0', 0, 0, 0, 1585.2791748046875, -4470.83056640625, 75.2471923828125, 5.241640090942382812, 120, 10, 0, 27, 0, 1, 0, 0, 0, 45505), -- Spiny Lizard (Area: Valley of Strength - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+24, 3296, 1, 1637, 5170, '0', '0', 0, 0, 1, 1548.75, -4321.06005859375, 26.04043388366699218, 5.654866695404052734, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Orgrimmar Grunt (Area: Valley of Strength - Difficulty: 0) (Auras: )
(@CGUID+25, 3296, 1, 1637, 5170, '0', '0', 0, 0, 1, 1484.949951171875, -4425.240234375, 25.4232330322265625, 0.174532920122146606, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Orgrimmar Grunt (Area: Valley of Strength - Difficulty: 0) (Auras: )
(@CGUID+26, 51346, 1, 1637, 5170, '0', '0', 0, 0, 1, 1677.893310546875, -4317.98095703125, 113.4948654174804687, 5.40872049331665039, 120, 10, 0, 198434, 0, 1, 0, 0, 0, 45505), -- Orgrimmar Wind Rider (Area: Valley of Strength - Difficulty: 0) (Auras: ) (possible waypoints or random movement)
(@CGUID+27, 5188, 1, 1637, 5170, '0', '0', 0, 0, 1, 1564.68408203125, -4314.08349609375, 23.34388923645019531, 5.161811351776123046, 120, 0, 0, 138903, 0, 0, 0, 0, 0, 45505), -- Garyl (Area: Valley of Strength - Difficulty: 0)
(@CGUID+28, 49837, 1, 1637, 5170, '0', '0', 0, 0, 0, 1522.5018310546875, -4476.251953125, 71.6837310791015625, 3.606009244918823242, 120, 10, 0, 27, 0, 1, 0, 0, 0, 45505), -- Spiny Lizard (Area: Valley of Strength - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+29, 28960, 1, 1637, 5170, '0', '0', 0, 0, 0, 1615.3941650390625, -4371.078125, 24.70599365234375, 0, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Totally Generic Bunny (JSB) (Area: Valley of Strength - Difficulty: 0)
(@CGUID+30, 51346, 1, 1637, 5170, '0', '0', 0, 0, 1, 1691.5067138671875, -4105.9677734375, 77.09151458740234375, 0.235791623592376708, 120, 10, 0, 198434, 0, 1, 0, 0, 0, 45505), -- Orgrimmar Wind Rider (Area: Valley of Strength - Difficulty: 0) (Auras: ) (possible waypoints or random movement)
(@CGUID+31, 46572, 1, 1637, 5170, '0', '0', 0, 0, 0, 1558.5521240234375, -4326.05224609375, 23.31404304504394531, 5.805724620819091796, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Goram (Area: Valley of Strength - Difficulty: 0) (Auras: )
(@CGUID+32, 51346, 1, 1637, 5170, '0', '0', 0, 0, 1, 1735.4805908203125, -4106.78369140625, 153.798187255859375, 0.487764894962310791, 120, 10, 0, 198434, 0, 1, 0, 0, 0, 45505), -- Orgrimmar Wind Rider (Area: Valley of Strength - Difficulty: 0) (Auras: ) (possible waypoints or random movement)
(@CGUID+33, 49837, 1, 1637, 5170, '0', '0', 0, 0, 0, 1507.439697265625, -4381.28515625, 22.84084892272949218, 5.348597526550292968, 120, 10, 0, 27, 0, 1, 0, 0, 0, 45505), -- Spiny Lizard (Area: Valley of Strength - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+34, 3296, 1, 1637, 5170, '0', '0', 0, 0, 1, 1438.989990234375, -4404.0400390625, 25.38923454284667968, 3.106686115264892578, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Orgrimmar Grunt (Area: Valley of Strength - Difficulty: 0) (Auras: )
(@CGUID+35, 44871, 1, 1637, 5170, '0', '0', 0, 0, 1, 1626.4000244140625, -4442.7998046875, 17.17063331604003906, 0.767944872379302978, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Grunt Grimful (Area: Valley of Strength - Difficulty: 0) (Auras: )
(@CGUID+36, 62114, 1, 1637, 5170, '0', '0', 0, 0, 0, 1515.9195556640625, -4380.4375, 21.37733268737792968, 0.777111053466796875, 120, 0, 0, 27, 0, 0, 0, 0, 0, 45505), -- Spiny Lizard (Area: Valley of Strength - Difficulty: 0)
(@CGUID+37, 5817, 1, 1637, 5170, '0', '0', 0, 0, 1, 1537.3299560546875, -4445.31005859375, 24.10203361511230468, 1.745329260826110839, 120, 0, 0, 138903, 0, 0, 0, 0, 0, 45505), -- Shimra (Area: Valley of Strength - Difficulty: 0)
(@CGUID+38, 44876, 1, 1637, 5170, '0', '0', 0, 0, 1, 1512.1400146484375, -4356.18017578125, 20.63793373107910156, 0.209439516067504882, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Grunt Koma (Area: Valley of Strength - Difficulty: 0) (Auras: )
(@CGUID+39, 49743, 1, 1637, 5170, '0', '0', 0, 0, 0, 1505.431640625, -4462.20751953125, 28.22981834411621093, 4.061553955078125, 120, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Dung Beetle (Area: Valley of Strength - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+40, 51195, 1, 1637, 5170, '0', '0', 0, 0, 0, 1558.095458984375, -4319.66650390625, 23.34388923645019531, 5.370631217956542968, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Kor'kron Annihilator (Area: Valley of Strength - Difficulty: 0)
(@CGUID+41, 3296, 1, 1637, 5170, '0', '0', 0, 0, 1, 1579.736083984375, -4417.796875, 15.32118034362792968, 3.909874677658081054, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Orgrimmar Grunt (Area: Valley of Strength - Difficulty: 0) (Auras: )
(@CGUID+42, 38821, 1, 1637, 5170, '0', '0', 0, 0, 0, 1747.5999755859375, -4263.2099609375, 110.7983322143554687, 4.555309295654296875, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Dave's Industrial Light and Magic Bunny (Medium)(Sessile) (Area: Valley of Strength - Difficulty: 0)
(@CGUID+43, 49837, 1, 1637, 5170, '0', '0', 0, 0, 0, 1556.25, -4383.333984375, 16.99226760864257812, 5.97881174087524414, 120, 0, 0, 27, 0, 0, 0, 0, 0, 45505), -- Spiny Lizard (Area: Valley of Strength - Difficulty: 0) (Auras: )
(@CGUID+44, 44878, 1, 1637, 5170, '0', '0', 0, 0, 1, 1520.4200439453125, -4361.4599609375, 20.71596908569335937, 0.139626339077949523, 120, 10, 0, 198434, 0, 1, 0, 0, 0, 45505), -- Grunt Karus (Area: Valley of Strength - Difficulty: 0) (Auras: ) (possible waypoints or random movement)
(@CGUID+45, 189398, 1, 1637, 5170, '0', '0', 0, 0, 0, 1555.3194580078125, -4471.56103515625, 73.49481201171875, 1.60393834114074707, 120, 0, 0, 20648, 2434, 0, 0, 0, 0, 45505), -- Kodethi (Area: Valley of Strength - Difficulty: 0)
(@CGUID+46, 3296, 1, 1637, 5170, '0', '0', 0, 0, 1, 1585.816650390625, -4344.23193359375, 21.17727851867675781, 4.473964691162109375, 120, 10, 0, 198434, 0, 1, 0, 0, 0, 45505), -- Orgrimmar Grunt (Area: Valley of Strength - Difficulty: 0) (Auras: ) (possible waypoints or random movement)
(@CGUID+47, 3296, 1, 1637, 5170, '0', '0', 0, 0, 1, 1575.8900146484375, -4387.3798828125, 16.46013450622558593, 3.525565147399902343, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Orgrimmar Grunt (Area: Valley of Strength - Difficulty: 0) (Auras: )
(@CGUID+48, 188656, 1, 1637, 5170, '0', '0', 0, 0, 1, 1602.34033203125, -4359.41845703125, 21.20301055908203125, 0, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Worker (Area: Valley of Strength - Difficulty: 0) (Auras: 327198 - -0-)
(@CGUID+49, 49837, 1, 1637, 5170, '0', '0', 0, 0, 0, 1508.718017578125, -4344.0849609375, 79.87003326416015625, 0.076461821794509887, 120, 10, 0, 27, 0, 1, 0, 0, 0, 45505), -- Spiny Lizard (Area: Valley of Strength - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+50, 38821, 1, 1637, 5170, '0', '0', 0, 0, 0, 1757.3399658203125, -4274.419921875, 114.4453353881835937, 2.408554315567016601, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Dave's Industrial Light and Magic Bunny (Medium)(Sessile) (Area: Valley of Strength - Difficulty: 0)
(@CGUID+51, 51346, 1, 1637, 5170, '0', '0', 0, 0, 1, 1791.2025146484375, -4335.55322265625, 119.2516098022460937, 1.891965508460998535, 120, 10, 0, 198434, 0, 1, 0, 0, 0, 45505), -- Orgrimmar Wind Rider (Area: Valley of Strength - Difficulty: 0) (Auras: ) (possible waypoints or random movement)
(@CGUID+52, 3296, 1, 1637, 5170, '0', '0', 0, 0, 1, 1468.7314453125, -4391.87353515625, 73.9037628173828125, 4.808934688568115234, 120, 10, 0, 198434, 0, 1, 0, 0, 0, 45505), -- Orgrimmar Grunt (Area: Valley of Strength - Difficulty: 0) (Auras: ) (possible waypoints or random movement)
(@CGUID+53, 32520, 1, 1637, 5170, '0', '0', 0, 0, 0, 1655.84375, -4348.64404296875, 109.4137954711914062, 0, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Totally Generic Bunny (All Phase) (Area: Valley of Strength - Difficulty: 0)
(@CGUID+54, 44852, 1, 1637, 5170, '0', '0', 0, 0, 0, 1509.5999755859375, -4352.77978515625, 21.22693443298339843, 5.8817596435546875, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Rilgiz (Area: Valley of Strength - Difficulty: 0) (Auras: )
(@CGUID+55, 51346, 1, 1637, 5170, '0', '0', 0, 0, 1, 1622.952880859375, -4407.4326171875, 45.10591888427734375, 6.059626579284667968, 120, 10, 0, 198434, 0, 1, 0, 0, 0, 45505), -- Orgrimmar Wind Rider (Area: Valley of Strength - Difficulty: 0) (Auras: ) (possible waypoints or random movement)
(@CGUID+56, 44854, 1, 1637, 5170, '0', '0', 0, 0, 0, 1513.1600341796875, -4346.47998046875, 21.23633384704589843, 5.777040004730224609, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Kixa (Area: Valley of Strength - Difficulty: 0) (Auras: )
(@CGUID+57, 49743, 1, 1637, 5170, '0', '0', 0, 0, 0, 1522.605224609375, -4381.76611328125, 20.70095634460449218, 1.212959527969360351, 120, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Dung Beetle (Area: Valley of Strength - Difficulty: 0) (Auras: ) (possible waypoints or random movement)
(@CGUID+58, 3296, 1, 1637, 5170, '0', '0', 0, 0, 1, 1539.760009765625, -4413.759765625, 18.40273475646972656, 3.159045934677124023, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Orgrimmar Grunt (Area: Valley of Strength - Difficulty: 0) (Auras: )
(@CGUID+59, 51346, 1, 1637, 5170, '0', '0', 0, 0, 1, 1722.1134033203125, -4378.81396484375, 57.43156814575195312, 1.17848825454711914, 120, 10, 0, 198434, 0, 1, 0, 0, 0, 45505), -- Orgrimmar Wind Rider (Area: Valley of Strength - Difficulty: 0) (Auras: ) (possible waypoints or random movement)
(@CGUID+60, 44856, 1, 1637, 5170, '0', '0', 0, 0, 0, 1514.02001953125, -4361.43994140625, 21.12293434143066406, 1.099557399749755859, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Perixa (Area: Valley of Strength - Difficulty: 0) (Auras: )
(@CGUID+61, 5606, 1, 1637, 5170, '0', '0', 0, 0, 1, 1571.095458984375, -4457.095703125, 16.12346076965332031, 1.361356854438781738, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Goma (Area: Valley of Strength - Difficulty: 0)
(@CGUID+62, 51346, 1, 1637, 5170, '0', '0', 0, 0, 1, 1668.7486572265625, -4315.12744140625, 114.3056716918945312, 5.311072349548339843, 120, 10, 0, 198434, 0, 1, 0, 0, 0, 45505), -- Orgrimmar Wind Rider (Area: Valley of Strength - Difficulty: 0) (Auras: ) (possible waypoints or random movement)
(@CGUID+63, 3296, 1, 1637, 5170, '0', '0', 0, 0, 1, 1548.1510009765625, -4361.12841796875, 17.83566665649414062, 5.707226753234863281, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Orgrimmar Grunt (Area: Valley of Strength - Difficulty: 0) (Auras: )
(@CGUID+64, 5609, 1, 1637, 5170, '0', '0', 0, 0, 1, 1571.623291015625, -4454.60791015625, 16.12351608276367187, 4.537856101989746093, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Zazo (Area: Valley of Strength - Difficulty: 0)
(@CGUID+65, 49837, 1, 1637, 5170, '0', '0', 0, 0, 0, 1587.4959716796875, -4366.9501953125, 20.98015213012695312, 1.868149638175964355, 120, 0, 0, 27, 0, 0, 0, 0, 0, 45505), -- Spiny Lizard (Area: Valley of Strength - Difficulty: 0) (Auras: )
(@CGUID+66, 6929, 1, 1637, 5170, '0', '0', 0, 0, 1, 1573.265625, -4439.158203125, 16.13972854614257812, 1.902408838272094726, 120, 0, 0, 138903, 0, 0, 0, 0, 0, 45505), -- Innkeeper Gryshka (Area: Valley of Strength - Difficulty: 0)
(@CGUID+67, 3296, 1, 1637, 5170, '0', '0', 0, 0, 1, 1603.7760009765625, -4433.205078125, 14.06594276428222656, 2.323195219039916992, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Orgrimmar Grunt (Area: Valley of Strength - Difficulty: 0) (Auras: )
(@CGUID+68, 5610, 1, 1637, 5170, '0', '0', 0, 0, 1, 1574.326416015625, -4464.03466796875, 16.12826347351074218, 6.038839340209960937, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Kozish (Area: Valley of Strength - Difficulty: 0)
(@CGUID+69, 187758, 1, 1637, 5170, '0', '0', 0, 0, 0, 1606.55908203125, -4350.74658203125, 21.2030029296875, 2.427687644958496093, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Zaa'je (Area: Valley of Strength - Difficulty: 0) (Auras: )
(@CGUID+70, 5611, 1, 1637, 5170, '0', '0', 0, 0, 1, 1582.795166015625, -4464.37158203125, 16.13210678100585937, 1.972222089767456054, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Barkeep Morag (Area: Valley of Strength - Difficulty: 0)
(@CGUID+71, 62114, 1, 1637, 5170, '0', '0', 0, 0, 0, 1601.8475341796875, -4446.125, 13.32306575775146484, 5.373506069183349609, 120, 0, 0, 27, 0, 0, 0, 0, 0, 45505), -- Spiny Lizard (Area: Valley of Strength - Difficulty: 0)
(@CGUID+72, 72559, 1, 1637, 5170, '0', '0', 0, 0, 1, 1546.4830322265625, -4325.498046875, 26.05979347229003906, 1.588249564170837402, 120, 0, 0, 4137, 0, 0, 0, 0, 0, 45505), -- Thunder Bluff Protector (Area: Valley of Strength - Difficulty: 0) (Auras: )
(@CGUID+73, 5613, 1, 1637, 5170, '0', '0', 0, 0, 1, 1586.501708984375, -4456.87841796875, 23.2503662109375, 5.445427417755126953, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Doyo'da (Area: Valley of Strength - Difficulty: 0)
(@CGUID+74, 38821, 1, 1637, 5170, '0', '0', 0, 0, 0, 1744.9100341796875, -4275.58984375, 118.8193359375, 0.837758064270019531, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Dave's Industrial Light and Magic Bunny (Medium)(Sessile) (Area: Valley of Strength - Difficulty: 0)
(@CGUID+75, 5614, 1, 1637, 5170, '0', '0', 0, 0, 1, 1588.4149169921875, -4458.8056640625, 23.2507781982421875, 2.356194496154785156, 120, 0, 0, 134935, 0, 0, 0, 0, 0, 45505), -- Sarok (Area: Valley of Strength - Difficulty: 0)
(@CGUID+76, 188157, 1, 1637, 5170, '0', '0', 0, 0, 0, 1607.263916015625, -4452.19970703125, 13.17923355102539062, 0, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Worker (Area: Valley of Strength - Difficulty: 0) (Auras: 221098 - Sleeping Sleep)
(@CGUID+77, 62114, 1, 1637, 5170, '0', '0', 0, 0, 0, 1563.8927001953125, -4311.6708984375, 23.60515785217285156, 5.216579914093017578, 120, 0, 0, 27, 0, 0, 0, 0, 0, 45505), -- Spiny Lizard (Area: Valley of Strength - Difficulty: 0)
(@CGUID+78, 38821, 1, 1637, 5170, '0', '0', 0, 0, 0, 1755.0999755859375, -4263.2001953125, 112.0113372802734375, 4.084070205688476562, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Dave's Industrial Light and Magic Bunny (Medium)(Sessile) (Area: Valley of Strength - Difficulty: 0)
(@CGUID+79, 51346, 1, 1637, 5170, '0', '0', 0, 0, 1, 1713.69677734375, -4120.43896484375, 156.187896728515625, 0.370868861675262451, 120, 10, 0, 198434, 0, 1, 0, 0, 0, 45505), -- Orgrimmar Wind Rider (Area: Valley of Strength - Difficulty: 0) (Auras: ) (possible waypoints or random movement)
(@CGUID+80, 14375, 1, 1637, 5170, '0', '0', 0, 0, 1, 1517.2552490234375, -4355.0712890625, 20.59891510009765625, 1.880690455436706542, 120, 10, 0, 529156, 0, 1, 0, 0, 0, 45505), -- Scout Stronghand (Area: Valley of Strength - Difficulty: 0) (Auras: 18950 - Invisibility and Stealth Detection) (possible waypoints or random movement)
(@CGUID+81, 51346, 1, 1637, 5170, '0', '0', 0, 0, 1, 1710.02783203125, -4111.1494140625, 156.2385406494140625, 0.464068084955215454, 120, 10, 0, 198434, 0, 1, 0, 0, 0, 45505), -- Orgrimmar Wind Rider (Area: Valley of Strength - Difficulty: 0) (Auras: ) (possible waypoints or random movement)
(@CGUID+82, 3313, 1, 1637, 5170, '0', '0', 0, 0, 1, 1528.8900146484375, -4442.89013671875, 24.10243415832519531, 0.802851438522338867, 120, 0, 0, 138903, 0, 0, 0, 0, 0, 45505), -- Trak'gen (Area: Valley of Strength - Difficulty: 0)
(@CGUID+83, 88701, 1, 1637, 5170, '0', '0', 0, 0, 1, 1571.3021240234375, -4464.18212890625, 23.25068855285644531, 5.375614166259765625, 120, 0, 0, 152132, 0, 0, 0, 0, 0, 45505), -- Grunt Meena (Area: Valley of Strength - Difficulty: 0)
(@CGUID+84, 88702, 1, 1637, 5170, '0', '0', 0, 0, 1, 1577.8680419921875, -4462.79541015625, 16.11969566345214843, 5.078907966613769531, 120, 0, 0, 152132, 0, 0, 0, 0, 0, 45505), -- Grunt Nolo (Area: Valley of Strength - Difficulty: 0)
(@CGUID+85, 88703, 1, 1637, 5170, '0', '0', 0, 0, 1, 1606.3199462890625, -4423.52001953125, 13.65909957885742187, 3.020823955535888671, 120, 10, 0, 198434, 0, 1, 0, 0, 0, 45505), -- Grunt Arhung (Area: Valley of Strength - Difficulty: 0) (Auras: ) (possible waypoints or random movement)
(@CGUID+86, 3296, 1, 1637, 5170, '0', '0', 0, 0, 1, 1577.298583984375, -4420.048828125, 15.18402767181396484, 0.317569166421890258, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Orgrimmar Grunt (Area: Valley of Strength - Difficulty: 0) (Auras: )
(@CGUID+87, 51346, 1, 1637, 5170, '0', '0', 0, 0, 1, 1805.1771240234375, -4365.9609375, 119.991058349609375, 1.810403823852539062, 120, 10, 0, 198434, 0, 1, 0, 0, 0, 45505), -- Orgrimmar Wind Rider (Area: Valley of Strength - Difficulty: 0) (Auras: ) (possible waypoints or random movement)
(@CGUID+88, 149270, 1, 1637, 5170, '0', '0', 0, 0, 1, 1441.7100830078125, -4434.00341796875, 25.74127578735351562, 1.77606201171875, 120, 0, 0, 142872, 7196, 0, 0, 0, 0, 45505), -- Orgrimmar Guardian Mage (Area: Valley of Strength - Difficulty: 0) (Auras: 18950 - Invisibility and Stealth Detection)
(@CGUID+89, 3296, 1, 1637, 5170, '0', '0', 0, 0, 1, 1483.050048828125, -4410.64990234375, 25.42313385009765625, 0.069813169538974761, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Orgrimmar Grunt (Area: Valley of Strength - Difficulty: 0) (Auras: )
(@CGUID+90, 6466, 1, 1637, 5170, '0', '0', 0, 0, 1, 1576.40625, -4464.60595703125, 23.25018310546875, 3.285095453262329101, 120, 0, 0, 13228900, 0, 0, 0, 0, 0, 45505), -- Gamon (Area: Valley of Strength - Difficulty: 0) (Auras: 162443 - Cosmetic - SitGround and Drink Breakable)
(@CGUID+91, 74228, 1, 1637, 5170, '0', '0', 0, 0, 1, 1550.949951171875, -4322.509765625, 26.04453468322753906, 2.600540637969970703, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Darkspear Headhunter (Area: Valley of Strength - Difficulty: 0) (Auras: )
(@CGUID+92, 44851, 1, 1637, 5170, '0', '0', 0, 0, 1, 1518.7919921875, -4353.876953125, 17.59816169738769531, 2.400022268295288085, 120, 10, 0, 132289, 0, 1, 0, 0, 0, 45505), -- Mezlik (Area: Valley of Strength - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+93, 3296, 1, 1637, 5170, '0', '0', 0, 0, 1, 1581.1199951171875, -4396.8701171875, 16.03733444213867187, 3.59537816047668457, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Orgrimmar Grunt (Area: Valley of Strength - Difficulty: 0) (Auras: )
(@CGUID+94, 51346, 1, 1637, 5170, '0', '0', 0, 0, 1, 1803.28271484375, -4366.7099609375, 119.9894332885742187, 2.073613643646240234, 120, 10, 0, 198434, 0, 1, 0, 0, 0, 45505), -- Orgrimmar Wind Rider (Area: Valley of Strength - Difficulty: 0) (Auras: ) (possible waypoints or random movement)
(@CGUID+95, 3296, 1, 1637, 5170, '0', '0', 0, 0, 1, 1538.300048828125, -4397.97021484375, 18.26213455200195312, 3.263765573501586914, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Orgrimmar Grunt (Area: Valley of Strength - Difficulty: 0) (Auras: )
(@CGUID+96, 168459, 1, 1637, 5170, '0', '0', 0, 0, 1, 1510.1666259765625, -4419.1181640625, 22.68142509460449218, 3.29705047607421875, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Orgrimmar Grunt (Area: Valley of Strength - Difficulty: 0) (Auras: )
(@CGUID+97, 74228, 1, 1637, 5170, '0', '0', 0, 0, 1, 1540.719970703125, -4320.43017578125, 28.56663322448730468, 4.206243515014648437, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Darkspear Headhunter (Area: Valley of Strength - Difficulty: 0) (Auras: 55701 - Cosmetic - Sleep Zzz Breakable)
(@CGUID+98, 44853, 1, 1637, 5170, '0', '0', 0, 0, 0, 1522.719970703125, -4345.490234375, 21.12343406677246093, 4.24114990234375, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Branzlit (Area: Valley of Strength - Difficulty: 0) (Auras: )
(@CGUID+99, 3296, 1, 1637, 5170, '0', '0', 0, 0, 1, 1450.7900390625, -4416.4501953125, 25.39343452453613281, 4.712388992309570312, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Orgrimmar Grunt (Area: Valley of Strength - Difficulty: 0) (Auras: )
(@CGUID+100, 137762, 1, 1637, 5170, '0', '0', 0, 0, 0, 1578.23095703125, -4456.22900390625, 15.71592140197753906, 0, 120, 0, 0, 17723, 2434, 0, 0, 0, 0, 45505), -- Take a potion (Area: Valley of Strength - Difficulty: 0)
(@CGUID+101, 49837, 1, 1637, 5170, '0', '0', 0, 0, 0, 1559.740234375, -4388.50927734375, 16.87831878662109375, 1.202190876007080078, 120, 0, 0, 27, 0, 0, 0, 0, 0, 45505), -- Spiny Lizard (Area: Valley of Strength - Difficulty: 0) (Auras: )
(@CGUID+102, 14392, 1, 1637, 5170, '0', '0', 0, 0, 1, 1531.3350830078125, -4421.517578125, 20.85962104797363281, 2.30383467674255371, 120, 0, 0, 2116624, 0, 0, 0, 0, 0, 45505), -- Overlord Natoj (Area: Valley of Strength - Difficulty: 0) (Auras: )
(@CGUID+103, 51346, 1, 1637, 5170, '0', '0', 0, 0, 1, 1416.4810791015625, -4778.1669921875, 84.31089019775390625, 2.122618675231933593, 120, 10, 0, 198434, 0, 1, 0, 0, 0, 45505), -- Orgrimmar Wind Rider (Area: Valley of Strength - Difficulty: 0) (Auras: ) (possible waypoints or random movement)
(@CGUID+104, 51346, 1, 1637, 5170, '0', '0', 0, 0, 1, 1426.1649169921875, -4780.6328125, 84.31130218505859375, 2.13027048110961914, 120, 10, 0, 198434, 0, 1, 0, 0, 0, 45505), -- Orgrimmar Wind Rider (Area: Valley of Strength - Difficulty: 0) (Auras: ) (possible waypoints or random movement)
(@CGUID+105, 149296, 1, 1637, 5170, '0', '0', 0, 0, 0, 1436.9300537109375, -4418.0400390625, 25.45359992980957031, 4.828911781311035156, 120, 0, 0, 2584, 0, 0, 0, 0, 0, 45505), -- Northrend Adventurer (Area: Valley of Strength - Difficulty: 0)
(@CGUID+106, 51346, 1, 1637, 5170, '0', '0', 0, 0, 1, 1406.7926025390625, -4775.6943359375, 84.31145477294921875, 2.115067005157470703, 120, 10, 0, 198434, 0, 1, 0, 0, 0, 45505), -- Orgrimmar Wind Rider (Area: Valley of Strength - Difficulty: 0) (Auras: ) (possible waypoints or random movement)
(@CGUID+107, 51346, 1, 1637, 5170, '0', '0', 0, 0, 1, 1397.0933837890625, -4773.11083984375, 83.3171539306640625, 2.124743461608886718, 120, 10, 0, 198434, 0, 1, 0, 0, 0, 45505), -- Orgrimmar Wind Rider (Area: Valley of Strength - Difficulty: 0) (Auras: 95230 - Horde Flag) (possible waypoints or random movement)
(@CGUID+108, 149371, 1, 1637, 5170, '0', '0', 0, 0, 0, 1473.4493408203125, -4480.5888671875, -2.75318026542663574, 0.117063038051128387, 120, 0, 0, 5283, 0, 0, 0, 0, 0, 45505), -- Draenor Adventurer (Area: Valley of Strength - Difficulty: 0) (Auras: )
(@CGUID+109, 51346, 1, 1637, 5170, '0', '0', 0, 0, 1, 1385.035888671875, -4766.72314453125, 86.4286956787109375, 2.087941646575927734, 120, 10, 0, 198434, 0, 1, 0, 0, 0, 45505), -- Orgrimmar Wind Rider (Area: Valley of Strength - Difficulty: 0) (Auras: ) (possible waypoints or random movement)
(@CGUID+110, 51346, 1, 1637, 5170, '0', '0', 0, 0, 1, 1375.4383544921875, -4765.0498046875, 87.89620208740234375, 2.112772464752197265, 120, 10, 0, 198434, 0, 1, 0, 0, 0, 45505), -- Orgrimmar Wind Rider (Area: Valley of Strength - Difficulty: 0) (Auras: ) (possible waypoints or random movement)
(@CGUID+111, 51346, 1, 1637, 5170, '0', '0', 0, 0, 1, 1362.5196533203125, -4756.58349609375, 90.23015594482421875, 2.06467294692993164, 120, 10, 0, 198434, 0, 1, 0, 0, 0, 45505), -- Orgrimmar Wind Rider (Area: Valley of Strength - Difficulty: 0) (Auras: ) (possible waypoints or random movement)
(@CGUID+112, 49743, 1, 1637, 5170, '0', '0', 0, 0, 0, 1605.485107421875, -4336.97265625, 21.23225784301757812, 4.685144901275634765, 120, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Dung Beetle (Area: Valley of Strength - Difficulty: 0) (Auras: ) (possible waypoints or random movement)
(@CGUID+113, 45339, 1, 1637, 5170, '0', '0', 0, 0, 1, 1640.6700439453125, -4343.68017578125, 26.8484344482421875, 6.056292533874511718, 120, 0, 0, 142872, 7196, 0, 0, 0, 0, 45505), -- Dark Cleric Cecille (Area: Valley of Strength - Difficulty: 0)
(@CGUID+114, 44865, 1, 1637, 5170, '0', '0', 0, 0, 0, 1643.719970703125, -4443.31982421875, 18.61603355407714843, 1.570796370506286621, 120, 0, 0, 396867, 0, 0, 0, 0, 0, 45505), -- Auctioneer Fazdran (Area: Valley of Strength - Difficulty: 0) (Auras: )
(@CGUID+115, 44866, 1, 1637, 5170, '0', '0', 0, 0, 0, 1637.4200439453125, -4448.2099609375, 18.61663436889648437, 2.408554315567016601, 120, 0, 0, 396867, 0, 0, 0, 0, 0, 45505), -- Auctioneer Drezmit (Area: Valley of Strength - Difficulty: 0) (Auras: )
(@CGUID+116, 44867, 1, 1637, 5170, '0', '0', 0, 0, 0, 1640.1700439453125, -4445.1201171875, 18.61683464050292968, 2.251474618911743164, 120, 0, 0, 396867, 0, 0, 0, 0, 0, 45505), -- Auctioneer Ralinza (Area: Valley of Strength - Difficulty: 0) (Auras: )
(@CGUID+117, 44868, 1, 1637, 5170, '0', '0', 0, 0, 0, 1635.4599609375, -4451.18994140625, 18.61623382568359375, 3.176499128341674804, 120, 0, 0, 66145, 0, 0, 0, 0, 0, 45505), -- Auctioneer Xifa (Area: Valley of Strength - Difficulty: 0) (Auras: )
(@CGUID+118, 3144, 1, 1637, 5170, '0', '0', 0, 0, 1, 1648.564208984375, -4362.3349609375, 26.8519744873046875, 0.802851438522338867, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Eitrigg (Area: Valley of Strength - Difficulty: 0)
(@CGUID+119, 44872, 1, 1637, 5170, '0', '0', 0, 0, 1, 1635.199951171875, -4433.9599609375, 17.17273330688476562, 3.926990747451782226, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Grunt Wabang (Area: Valley of Strength - Difficulty: 0) (Auras: )
(@CGUID+120, 197767, 1, 1637, 5170, '0', '0', 0, 0, 0, 1608.7222900390625, -4318.796875, 21.22546195983886718, 4.550391197204589843, 120, 0, 0, 105831, 7196, 0, 0, 0, 0, 45505), -- Aetheil (Area: Valley of Strength - Difficulty: 0) (Auras: )
(@CGUID+121, 197770, 1, 1637, 5170, '0', '0', 0, 0, 0, 1609.296875, -4318.453125, 21.2144622802734375, 4.549518108367919921, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Rips (Area: Valley of Strength - Difficulty: 0) (Auras: )
(@CGUID+122, 188655, 1, 1637, 5170, '0', '0', 0, 0, 1, 1624.060791015625, -4345.93212890625, 21.2030029296875, 4.57482767105102539, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Worker (Area: Valley of Strength - Difficulty: 0) (Auras: )
(@CGUID+123, 197771, 1, 1637, 5170, '0', '0', 0, 0, 0, 1608.1007080078125, -4318.81103515625, 21.26303482055664062, 5.085934162139892578, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Yuyu (Area: Valley of Strength - Difficulty: 0) (Auras: )
(@CGUID+124, 49837, 1, 1637, 5170, '0', '0', 0, 0, 0, 1560.41845703125, -4307.74853515625, 90.2518463134765625, 0.817035853862762451, 120, 10, 0, 27, 0, 1, 0, 0, 0, 45505), -- Spiny Lizard (Area: Valley of Strength - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+125, 46142, 1, 1637, 5170, '0', '0', 0, 0, 1, 1641.699951171875, -4346.22998046875, 26.85003471374511718, 6.161012172698974609, 120, 0, 0, 264578, 0, 0, 0, 0, 0, 45505), -- Forsaken Delegation Deathguard (Area: Valley of Strength - Difficulty: 0) (Auras: 18950 - Invisibility and Stealth Detection)
(@CGUID+126, 46142, 1, 1637, 5170, '0', '0', 0, 0, 1, 1643.1700439453125, -4341.97998046875, 26.85293388366699218, 0.209439516067504882, 120, 0, 0, 264578, 0, 0, 0, 0, 0, 45505), -- Forsaken Delegation Deathguard (Area: Valley of Strength - Difficulty: 0) (Auras: 18950 - Invisibility and Stealth Detection)
(@CGUID+127, 4047, 1, 1637, 5170, '0', '0', 0, 0, 1, 1640.2430419921875, -4352.4462890625, 26.8533172607421875, 5.742133140563964843, 120, 0, 0, 178590, 0, 0, 0, 0, 0, 45505), -- Zor Lonetree (Area: Valley of Strength - Difficulty: 0)
(@CGUID+128, 46556, 1, 1637, 5170, '0', '0', 0, 0, 1, 1655.420166015625, -4353.29541015625, 64.61993408203125, 0.680678427219390869, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Jamus'Vaz (Area: Valley of Strength - Difficulty: 0)
(@CGUID+129, 27489, 1, 1637, 5170, '0', '0', 0, 0, 0, 1634.5191650390625, -4382.18603515625, 21.19016075134277343, 5.148721218109130859, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Ray'ma (Area: Valley of Strength - Difficulty: 0) (Auras: )
(@CGUID+130, 3312, 1, 1637, 5170, '0', '0', 0, 0, 1, 1650, -4388.02978515625, 21.1768341064453125, 4.502949237823486328, 120, 0, 0, 165361, 0, 0, 0, 0, 0, 45505), -- Olvia (Area: Valley of Strength - Difficulty: 0) (Auras: )
(@CGUID+131, 49622, 1, 1637, 5170, '0', '0', 0, 0, 1, 1637.4774169921875, -4349.05029296875, 26.856201171875, 5.497786998748779296, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Shok Narnes (Area: Valley of Strength - Difficulty: 0)
(@CGUID+132, 89830, 1, 1637, 5170, '0', '0', 0, 0, 1, 1636.59375, -4381.390625, 21.19601249694824218, 5.026548385620117187, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Brew Vendor (Area: Valley of Strength - Difficulty: 0)
(@CGUID+133, 51346, 1, 1637, 5170, '0', '0', 0, 0, 1, 1904.8939208984375, -4208.36767578125, 99.9112396240234375, 3.912693262100219726, 120, 10, 0, 198434, 0, 1, 0, 0, 0, 45505), -- Orgrimmar Wind Rider (Area: Valley of Strength - Difficulty: 0) (Auras: ) (possible waypoints or random movement)
(@CGUID+134, 51346, 1, 1637, 5170, '0', '0', 0, 0, 1, 1913.3099365234375, -4204.46875, 100.6111068725585937, 3.722504138946533203, 120, 10, 0, 198434, 0, 1, 0, 0, 0, 45505), -- Orgrimmar Wind Rider (Area: Valley of Strength - Difficulty: 0) (Auras: ) (possible waypoints or random movement)
(@CGUID+135, 51346, 1, 1637, 5170, '0', '0', 0, 0, 1, 1913.760009765625, -4206.85693359375, 100.4984817504882812, 3.567786931991577148, 120, 10, 0, 198434, 0, 1, 0, 0, 0, 45505), -- Orgrimmar Wind Rider (Area: Valley of Strength - Difficulty: 0) (Auras: ) (possible waypoints or random movement)
(@CGUID+136, 51346, 1, 1637, 5170, '0', '0', 0, 0, 1, 1964.837158203125, -4347.9794921875, 206.7968597412109375, 4.511224746704101562, 120, 10, 0, 198434, 0, 1, 0, 0, 0, 45505), -- Orgrimmar Wind Rider (Area: Valley of Strength - Difficulty: 0) (Auras: ) (possible waypoints or random movement)
(@CGUID+137, 51346, 1, 1637, 5170, '0', '0', 0, 0, 1, 1960.110107421875, -4339.84033203125, 207.8887481689453125, 4.482083320617675781, 120, 10, 0, 198434, 0, 1, 0, 0, 0, 45505), -- Orgrimmar Wind Rider (Area: Valley of Strength - Difficulty: 0) (Auras: ) (possible waypoints or random movement)
(@CGUID+138, 3296, 1, 1637, 5170, '0', '0', 0, 0, 1, 1642.174560546875, -4331.76025390625, 63.584564208984375, 3.698613643646240234, 120, 10, 0, 198434, 0, 1, 0, 0, 0, 45505), -- Orgrimmar Grunt (Area: Valley of Strength - Difficulty: 0) (Auras: ) (possible waypoints or random movement)
(@CGUID+139, 51346, 1, 1637, 5170, '0', '0', 0, 0, 1, 1967.8397216796875, -4373.43359375, 206.1285552978515625, 4.540511131286621093, 120, 10, 0, 198434, 0, 1, 0, 0, 0, 45505), -- Orgrimmar Wind Rider (Area: Valley of Strength - Difficulty: 0) (Auras: ) (possible waypoints or random movement)
(@CGUID+140, 42594, 1, 1637, 5170, '0', '0', 0, 0, 1, 1509.7222900390625, -4384.62255859375, 22.62817764282226562, 2.237717151641845703, 120, 0, 0, 145518, 0, 0, 0, 0, 0, 45505), -- Orgrimmar Thief (Area: Valley of Strength - Difficulty: 0) (Auras: )
(@CGUID+141, 44338, 1, 1637, 5170, '0', '0', 0, 0, 0, 1657.3433837890625, -4395.2431640625, 20.88818550109863281, 2.71822667121887207, 120, 10, 0, 27, 0, 1, 0, 0, 0, 45505), -- White Chicken (Area: Valley of Strength - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+142, 44338, 1, 1637, 5170, '0', '0', 0, 0, 0, 1663.2923583984375, -4393.83251953125, 21.00134468078613281, 4.069786548614501953, 120, 10, 0, 27, 0, 1, 0, 0, 0, 45505), -- White Chicken (Area: Valley of Strength - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+143, 44338, 1, 1637, 5170, '0', '0', 0, 0, 0, 1661.181640625, -4395.623046875, 20.94861030578613281, 2.329993724822998046, 120, 10, 0, 27, 0, 1, 0, 0, 0, 45505), -- White Chicken (Area: Valley of Strength - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+144, 49837, 1, 1637, 5170, '0', '0', 0, 0, 0, 1672.7042236328125, -4458.52197265625, 97.09394073486328125, 4.070891380310058593, 120, 10, 0, 27, 0, 1, 0, 0, 0, 45505), -- Spiny Lizard (Area: Valley of Strength - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+145, 51346, 1, 1637, 5170, '0', '0', 0, 0, 1, 1984.753662109375, -4429.2861328125, 131.7974395751953125, 4.317180156707763671, 120, 10, 0, 198434, 0, 1, 0, 0, 0, 45505), -- Orgrimmar Wind Rider (Area: Valley of Strength - Difficulty: 0) (Auras: ) (possible waypoints or random movement)
(@CGUID+146, 51346, 1, 1637, 5170, '0', '0', 0, 0, 1, 1995.334228515625, -4416.2197265625, 130.8736419677734375, 4.118787765502929687, 120, 10, 0, 198434, 0, 1, 0, 0, 0, 45505), -- Orgrimmar Wind Rider (Area: Valley of Strength - Difficulty: 0) (Auras: ) (possible waypoints or random movement)
(@CGUID+147, 51346, 1, 1637, 5170, '0', '0', 0, 0, 1, 1996.623046875, -4417.6904296875, 130.92041015625, 4.033052444458007812, 120, 10, 0, 198434, 0, 1, 0, 0, 0, 45505), -- Orgrimmar Wind Rider (Area: Valley of Strength - Difficulty: 0) (Auras: ) (possible waypoints or random movement)
(@CGUID+148, 58155, 1, 1637, 5170, '0', '0', 0, 0, 1, 1654.2413330078125, -4344.21337890625, 64.61993408203125, 6.056292533874511718, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Rugok (Area: Valley of Strength - Difficulty: 0)
(@CGUID+149, 45337, 1, 1637, 5170, '0', '0', 0, 0, 1, 1664.300048828125, -4361.81982421875, 26.81973457336425781, 2.251474618911743164, 120, 0, 0, 105831, 7196, 0, 0, 0, 0, 45505), -- Tyelis (Area: Valley of Strength - Difficulty: 0)
(@CGUID+150, 74228, 1, 1637, 5170, '0', '0', 0, 0, 1, 1673.9300537109375, -4433.27001953125, 21.63343429565429687, 0.715584993362426757, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Darkspear Headhunter (Area: Valley of Strength - Difficulty: 0) (Auras: )
(@CGUID+151, 17098, 1, 1637, 5170, '0', '0', 0, 0, 0, 1664.719970703125, -4365.1298828125, 26.81423377990722656, 2.216568231582641601, 120, 0, 0, 111123, 7196, 0, 0, 0, 0, 45505), -- Ambassador Dawnsinger (Area: Valley of Strength - Difficulty: 0)
(@CGUID+152, 74228, 1, 1637, 5170, '0', '0', 0, 0, 1, 1675.699951171875, -4431.75, 21.6349334716796875, 3.839724302291870117, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Darkspear Headhunter (Area: Valley of Strength - Difficulty: 0) (Auras: )
(@CGUID+153, 72654, 1, 1637, 5170, '0', '0', 0, 0, 0, 1672.376708984375, -4438.51416015625, 21.64096641540527343, 1.724887847900390625, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- General Purpose Stalker (RKS) (Area: Valley of Strength - Difficulty: 0)
(@CGUID+154, 3314, 1, 1637, 5170, '0', '0', 0, 0, 1, 1639.75, -4316.7099609375, 21.20283317565917968, 2.059488534927368164, 120, 0, 0, 138903, 0, 0, 0, 0, 0, 45505), -- Urtharo (Area: Valley of Strength - Difficulty: 0)
(@CGUID+155, 49837, 1, 1637, 5170, '0', '0', 0, 0, 0, 1638.2939453125, -4482.1884765625, 96.39807891845703125, 2.228826284408569335, 120, 10, 0, 27, 0, 1, 0, 0, 0, 45505), -- Spiny Lizard (Area: Valley of Strength - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+156, 3323, 1, 1637, 5170, '0', '0', 0, 0, 1, 1673.2900390625, -4382.72021484375, 21.19343376159667968, 5.201081275939941406, 120, 0, 0, 138903, 0, 0, 0, 0, 0, 45505), -- Horthus (Area: Valley of Strength - Difficulty: 0) (Auras: )
(@CGUID+157, 72559, 1, 1637, 5170, '0', '0', 0, 0, 1, 1679.1500244140625, -4441.35986328125, 22.74723434448242187, 3.543018341064453125, 120, 0, 0, 4137, 0, 0, 0, 0, 0, 45505), -- Thunder Bluff Protector (Area: Valley of Strength - Difficulty: 0) (Auras: 55701 - Cosmetic - Sleep Zzz Breakable)
(@CGUID+158, 47571, 1, 1637, 5170, '0', '0', 0, 0, 1, 1668.5699462890625, -4359.83984375, 26.85773468017578125, 2.513274192810058593, 120, 0, 0, 132289, 100, 0, 0, 0, 0, 45505), -- Belloc Brightblade (Area: Valley of Strength - Difficulty: 0) (Auras: 10022 - Deadly Poison)
(@CGUID+159, 46555, 1, 1637, 5170, '0', '0', 0, 0, 1, 1653.34033203125, -4348.73291015625, 64.61993408203125, 0.471238881349563598, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Gunra (Area: Valley of Strength - Difficulty: 0)
(@CGUID+160, 74228, 1, 1637, 5170, '0', '0', 0, 0, 1, 1663.0799560546875, -4336.77978515625, 63.66833114624023437, 0.03490658476948738, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Darkspear Headhunter (Area: Valley of Strength - Difficulty: 0) (Auras: )
(@CGUID+161, 52034, 1, 1637, 5170, '0', '0', 0, 0, 0, 1663.35595703125, -4353.0849609375, 64.61993408203125, 2.199114799499511718, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Togar (Area: Valley of Strength - Difficulty: 0)
(@CGUID+162, 3296, 1, 1637, 5170, '0', '0', 0, 0, 1, 1670.3399658203125, -4351.52001953125, 63.66833114624023437, 0.959931075572967529, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Orgrimmar Grunt (Area: Valley of Strength - Difficulty: 0) (Auras: )
(@CGUID+163, 35068, 1, 1637, 5170, '0', '0', 0, 0, 1, 1660.7708740234375, -4334.87841796875, 26.84811782836914062, 5.113814830780029296, 120, 0, 0, 165361, 3155, 0, 0, 0, 0, 45505), -- Gotura Fourwinds (Area: Valley of Strength - Difficulty: 0)
(@CGUID+164, 49743, 1, 1637, 5170, '0', '0', 0, 0, 0, 1622.46875, -4316.7626953125, 21.25053024291992187, 0.353495627641677856, 120, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Dung Beetle (Area: Valley of Strength - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+165, 46140, 1, 1637, 5170, '0', '0', 0, 0, 1, 1666.9300537109375, -4362.5498046875, 26.83043479919433593, 2.146754980087280273, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Silvermoon Delegation Guardian (Area: Valley of Strength - Difficulty: 0)
(@CGUID+166, 23128, 1, 1637, 5170, '0', '0', 0, 0, 1, 1661.75, -4363.419921875, 26.82673454284667968, 2.513274192810058593, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Master Pyreanor (Area: Valley of Strength - Difficulty: 0)
(@CGUID+167, 46140, 1, 1637, 5170, '0', '0', 0, 0, 1, 1661.1199951171875, -4365.72021484375, 26.83423423767089843, 2.234021425247192382, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Silvermoon Delegation Guardian (Area: Valley of Strength - Difficulty: 0)
(@CGUID+168, 135201, 1, 1637, 5170, '0', '0', 0, 0, 0, 1661.498291015625, -4347.0537109375, 26.41945457458496093, 0, 120, 0, 0, 17723, 2434, 0, 0, 0, 0, 45505), -- Talk to Sylvanas (Area: Valley of Strength - Difficulty: 0)
(@CGUID+169, 49837, 1, 1637, 5170, '0', '0', 0, 0, 0, 1672.5521240234375, -4317.18212890625, 21.36966896057128906, 0.005500116385519504, 120, 10, 0, 27, 0, 1, 0, 0, 0, 45505), -- Spiny Lizard (Area: Valley of Strength - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+170, 49837, 1, 1637, 5170, '0', '0', 0, 0, 0, 1693.7435302734375, -4338.35791015625, 21.34128952026367187, 3.909168720245361328, 120, 10, 0, 27, 0, 1, 0, 0, 0, 45505), -- Spiny Lizard (Area: Valley of Strength - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+171, 3296, 1, 1637, 5170, '0', '0', 0, 0, 1, 1719.260009765625, -4424.919921875, 110.297332763671875, 3.682644605636596679, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Orgrimmar Grunt (Area: Valley of Strength - Difficulty: 0) (Auras: )
(@CGUID+172, 74228, 1, 1637, 5170, '0', '0', 0, 0, 1, 1735.4786376953125, -4381.5361328125, 33.50394439697265625, 4.674567222595214843, 120, 10, 0, 198434, 0, 1, 0, 0, 0, 45505), -- Darkspear Headhunter (Area: Valley of Strength - Difficulty: 0) (Auras: ) (possible waypoints or random movement)
(@CGUID+173, 49837, 1, 1637, 5170, '0', '0', 0, 0, 0, 1728.8304443359375, -4432.43017578125, 40.66321182250976562, 1.993968963623046875, 120, 10, 0, 27, 0, 1, 0, 0, 0, 45505), -- Spiny Lizard (Area: Valley of Strength - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+174, 3296, 1, 1637, 5170, '0', '0', 0, 0, 1, 1730.9100341796875, -4379.0498046875, 32.77203369140625, 3.682644605636596679, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Orgrimmar Grunt (Area: Valley of Strength - Difficulty: 0) (Auras: )
(@CGUID+175, 14376, 1, 1637, 5170, '0', '0', 0, 0, 1, 1719.3267822265625, -4339.72314453125, 31.30179786682128906, 1.821386218070983886, 120, 10, 0, 529156, 0, 1, 0, 0, 0, 45505), -- Scout Manslayer (Area: Valley of Strength - Difficulty: 0) (Auras: 18950 - Invisibility and Stealth Detection) (possible waypoints or random movement)
(@CGUID+176, 49131, 1, 1637, 5170, '0', '0', 0, 0, 0, 1804.420166015625, -4377.67724609375, 103.086212158203125, 1.326450228691101074, 120, 0, 0, 577, 0, 0, 0, 0, 0, 45505), -- Goblin Hot Rod (Area: Valley of Strength - Difficulty: 0)
(@CGUID+177, 3296, 1, 1637, 5170, '0', '0', 0, 0, 1, 1715.6600341796875, -4419.3798828125, 110.297332763671875, 3.822271108627319335, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Orgrimmar Grunt (Area: Valley of Strength - Difficulty: 0) (Auras: )
(@CGUID+178, 74228, 1, 1637, 5170, '0', '0', 0, 0, 1, 1744.29638671875, -4388.5419921875, 42.23920440673828125, 3.755022525787353515, 120, 10, 0, 198434, 0, 1, 0, 0, 0, 45505), -- Darkspear Headhunter (Area: Valley of Strength - Difficulty: 0) (Auras: ) (possible waypoints or random movement)
(@CGUID+179, 62198, 1, 1637, 5170, '0', '0', 0, 0, 0, 1742.435791015625, -4412.3837890625, 36.87793731689453125, 1.561093330383300781, 120, 0, 0, 396867, 3155, 0, 0, 0, 0, 45505), -- Omakka Wolfbrother (Area: Valley of Strength - Difficulty: 0)
(@CGUID+180, 3296, 1, 1637, 5170, '0', '0', 0, 0, 1, 1742.40625, -4410.39404296875, 36.96831130981445312, 4.745508670806884765, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Orgrimmar Grunt (Area: Valley of Strength - Difficulty: 0) (Auras: )
(@CGUID+181, 51346, 1, 1637, 5170, '0', '0', 0, 0, 1, 1845.380615234375, -4697.74951171875, 129.8416900634765625, 2.08522963523864746, 120, 10, 0, 198434, 0, 1, 0, 0, 0, 45505), -- Orgrimmar Wind Rider (Area: Valley of Strength - Difficulty: 0) (Auras: ) (possible waypoints or random movement)
(@CGUID+182, 51346, 1, 1637, 5170, '0', '0', 0, 0, 1, 1846.82421875, -4702.02490234375, 129.8258514404296875, 2.035493373870849609, 120, 10, 0, 198434, 0, 1, 0, 0, 0, 45505), -- Orgrimmar Wind Rider (Area: Valley of Strength - Difficulty: 0) (Auras: ) (possible waypoints or random movement)
(@CGUID+183, 51346, 1, 1637, 5170, '0', '0', 0, 0, 1, 1846.099853515625, -4702.328125, 129.8296051025390625, 1.987813591957092285, 120, 10, 0, 198434, 0, 1, 0, 0, 0, 45505), -- Orgrimmar Wind Rider (Area: Valley of Strength - Difficulty: 0) (Auras: ) (possible waypoints or random movement)
-- (@CGUID+184, 62821, 0, 1637, 5170, '0', '0', 0, 0, 0, -0.20000000298023223, 0, -0.20000000298023223, 0, 120, 0, 0, 158747, 10794, 0, 0, 0, 0, 45505), -- Mystic Birdhat (Area: Valley of Strength - Difficulty: 0) (Auras: 122729 - Grand Expedition Yak) - !!! on transport - transport template not found !!!
-- (@CGUID+185, 62822, 0, 1637, 5170, '0', '0', 0, 0, 0, -0.20000000298023223, 0, -0.20000000298023223, 0, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Cousin Slowhands (Area: Valley of Strength - Difficulty: 0) (Auras: 122729 - Grand Expedition Yak) - !!! on transport - transport template not found !!!
(@CGUID+186, 3319, 1, 1637, 5170, '0', '0', 0, 0, 0, 1583.739990234375, -4288.97998046875, 21.62443351745605468, 6.248278617858886718, 120, 0, 0, 138903, 0, 0, 0, 0, 0, 45505), -- Sana (Area: Valley of Strength - Difficulty: 0)
(@CGUID+187, 46359, 1, 1637, 5170, '0', '0', 0, 0, 1, 1596.219970703125, -4288.39013671875, 21.59883308410644531, 2.862339973449707031, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Punra (Area: Valley of Strength - Difficulty: 0)
(@CGUID+188, 46512, 1, 1637, 5170, '0', '0', 0, 0, 0, 1587.68994140625, -4288.740234375, 21.59673309326171875, 3.263765573501586914, 120, 0, 0, 152132, 0, 0, 0, 0, 0, 45505), -- Naros (Area: Valley of Strength - Difficulty: 0)
(@CGUID+189, 3296, 1, 1637, 5170, '0', '0', 0, 0, 1, 1614.739990234375, -4291.33984375, 20.56683349609375, 1.01229095458984375, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Orgrimmar Grunt (Area: Valley of Strength - Difficulty: 0) (Auras: )
(@CGUID+190, 46357, 1, 1637, 5170, '0', '0', 0, 0, 1, 1574.9930419921875, -4281.40625, 21.59869003295898437, 5.934119224548339843, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Gonto (Area: Valley of Strength - Difficulty: 0)
(@CGUID+191, 46358, 1, 1637, 5170, '0', '0', 0, 0, 1, 1584.8900146484375, -4273.22998046875, 21.63783454895019531, 4.764749050140380859, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Lutah (Area: Valley of Strength - Difficulty: 0)
(@CGUID+192, 37072, 1, 1637, 5170, '0', '0', 0, 0, 1, 1591.3900146484375, -4275.7001953125, 21.54633331298828125, 1.047197580337524414, 120, 0, 0, 178590, 0, 0, 0, 0, 0, 45505), -- Rogg (Area: Valley of Strength - Difficulty: 0)
(@CGUID+193, 10880, 1, 1637, 5170, '0', '0', 0, 0, 0, 1694.11767578125, -4406.869140625, 31.30964088439941406, 3.590827465057373046, 120, 10, 0, 132289, 0, 1, 0, 0, 0, 45505), -- Warcaller Gorlach (Area: Valley of Strength - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+194, 62115, 1, 1637, 5170, '0', '0', 0, 0, 0, 1523.25, -4382.43603515625, 20.5555267333984375, 0, 120, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Dung Beetle (Area: Valley of Strength - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+195, 31723, 613, 1637, 5170, '0', '0', 0, 0, 1, -10.755157470703125, -12.8128557205200195, -16.7745208740234375, 4.537856101989746093, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Crewman Barrowswizzle (Area: Valley of Strength - Difficulty: 0)
(@CGUID+196, 31724, 613, 1637, 5170, '0', '0', 0, 0, 1, 5.776269912719726562, -2.00468897819519042, -17.7218532562255859, 1.640609502792358398, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Crewman Paltertop (Area: Valley of Strength - Difficulty: 0)
(@CGUID+197, 31725, 613, 1637, 5170, '0', '0', 0, 0, 1, 10.69841194152832031, -7.82192087173461914, -16.6006126403808593, 3.281219005584716796, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Sky-Captain LaFontaine (Area: Valley of Strength - Difficulty: 0)
(@CGUID+198, 31726, 613, 1637, 5170, '0', '0', 0, 0, 1, -3.45306801795959472, -13.789586067199707, -17.6110668182373046, 1.431169986724853515, 120, 0, 0, 264578, 0, 0, 0, 0, 0, 45505), -- Grunt Gritch (Area: Valley of Strength - Difficulty: 0)
(@CGUID+199, 31727, 613, 1637, 5170, '0', '0', 0, 0, 1, -3.38307595252990722, -1.91392505168914794, -17.6198005676269531, 4.729842185974121093, 120, 0, 0, 264578, 0, 0, 0, 0, 0, 45505), -- Grunt Grikee (Area: Valley of Strength - Difficulty: 0)
(@CGUID+200, 25075, 613, 1637, 5170, '0', '0', 0, 0, 0, 9.445420265197753906, -7.84947490692138671, -16.6006126403808593, 0.05235987901687622, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Zeppelin Controls (Area: Valley of Strength - Difficulty: 0) (Auras: )
(@CGUID+201, 31720, 613, 1637, 5170, '0', '0', 0, 0, 1, -16.5685329437255859, -5.08333110809326171, -15.9421186447143554, 1.989675283432006835, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Crewman Shubbscoop (Area: Valley of Strength - Difficulty: 0)
-- (@CGUID+202, 121541, 0, 1637, 5170, '0', '0', 0, 0, 0, -0.12034186720848083, 0, 0.910663068294525146, 0, 120, 0, 0, 2993, 0, 0, 0, 0, 0, 45505), -- Ban-Lu (Area: Valley of Strength - Difficulty: 0) (Auras: 46598 - Ride Vehicle Hardcoded) - !!! on transport - transport template not found !!!
-- (@CGUID+203, 62821, 0, 1637, 5170, '0', '0', 0, 0, 0, -0.20000000298023223, 0, -0.20000000298023223, 0, 120, 0, 0, 158747, 10794, 0, 0, 0, 0, 45505), -- Mystic Birdhat (Area: Valley of Strength - Difficulty: 0) (Auras: 122729 - Grand Expedition Yak) - !!! on transport - transport template not found !!!
-- (@CGUID+204, 62822, 0, 1637, 5170, '0', '0', 0, 0, 0, -0.20000000298023223, 0, -0.20000000298023223, 0, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Cousin Slowhands (Area: Valley of Strength - Difficulty: 0) (Auras: 122729 - Grand Expedition Yak) - !!! on transport - transport template not found !!!
(@CGUID+205, 3296, 1, 1637, 5170, '0', '0', 0, 0, 1, 1464.805419921875, -4420.57177734375, 25.40854454040527343, 0.115767449140548706, 120, 10, 0, 198434, 0, 1, 0, 0, 0, 45505), -- Orgrimmar Grunt (Area: Valley of Strength - Difficulty: 0) (Auras: ) (possible waypoints or random movement)
(@CGUID+206, 49837, 1, 1637, 5170, '0', '0', 0, 0, 0, 1597.2083740234375, -4395.84033203125, 17.555694580078125, 4.844776630401611328, 120, 0, 0, 27, 0, 0, 0, 0, 0, 45505), -- Spiny Lizard (Area: Valley of Strength - Difficulty: 0) (Auras: )
-- (@CGUID+207, 158637, 0, 1637, 5170, '0', '0', 0, 0, 0, 0, 0, 0, 0, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Guiding Orb (Area: Valley of Strength - Difficulty: 0) (Auras: 46598 - Ride Vehicle Hardcoded) - !!! on transport - transport template not found !!!
-- (@CGUID+208, 121541, 0, 1637, 5170, '0', '0', 0, 0, 0, -0.12034186720848083, 0, 0.910663068294525146, 0, 120, 10, 0, 2993, 0, 1, 0, 0, 0, 45505), -- Ban-Lu (Area: Valley of Strength - Difficulty: 0) (Auras: 46598 - Ride Vehicle Hardcoded) - !!! on transport - transport template not found !!! (possible waypoints or random movement)
(@CGUID+209, 49837, 1, 1637, 5170, '0', '0', 0, 0, 0, 1559.6875, -4388.3994140625, 16.94536781311035156, 6.094019412994384765, 120, 0, 0, 27, 0, 0, 0, 0, 0, 45505), -- Spiny Lizard (Area: Valley of Strength - Difficulty: 0) (Auras: )
(@CGUID+210, 49837, 1, 1637, 5170, '0', '0', 0, 0, 0, 1509.43408203125, -4382.51220703125, 22.59342384338378906, 2.28811812400817871, 120, 10, 0, 27, 0, 1, 0, 0, 0, 45505), -- Spiny Lizard (Area: Valley of Strength - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+211, 23635, 1, 1637, 5170, '0', '0', 0, 0, 1, 1670.2193603515625, -4409.4755859375, 22.69095230102539062, 3.246606111526489257, 120, 10, 0, 2297, 0, 1, 0, 0, 0, 45505), -- Krixx (Area: Valley of Strength - Difficulty: 0) (Auras: ) (possible waypoints or random movement)
-- (@CGUID+212, 62821, 0, 1637, 5170, '0', '0', 0, 0, 0, -0.20000000298023223, 0, -0.20000000298023223, 0, 120, 0, 0, 158747, 10794, 0, 0, 0, 0, 45505), -- Mystic Birdhat (Area: Valley of Strength - Difficulty: 0) (Auras: 122729 - Grand Expedition Yak) - !!! on transport - transport template not found !!!
-- (@CGUID+213, 62822, 0, 1637, 5170, '0', '0', 0, 0, 0, -0.20000000298023223, 0, -0.20000000298023223, 0, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Cousin Slowhands (Area: Valley of Strength - Difficulty: 0) (Auras: 122729 - Grand Expedition Yak) - !!! on transport - transport template not found !!!
(@CGUID+214, 49743, 1, 1637, 5170, '0', '0', 0, 0, 0, 1565.13720703125, -4386.36474609375, 16.59819793701171875, 4.068141937255859375, 120, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Dung Beetle (Area: Valley of Strength - Difficulty: 0)
(@CGUID+215, 14377, 1, 1637, 5170, '0', '0', 0, 0, 1, 1670.340576171875, -4408.79638671875, 22.63269996643066406, 3.18445587158203125, 120, 10, 0, 529156, 0, 1, 0, 0, 0, 45505), -- Scout Tharr (Area: Valley of Strength - Difficulty: 0) (Auras: 18950 - Invisibility and Stealth Detection) (possible waypoints or random movement)
(@CGUID+216, 49743, 1, 1637, 5170, '0', '0', 0, 0, 0, 1515.9288330078125, -4381.736328125, 21.5364227294921875, 5.170680999755859375, 120, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Dung Beetle (Area: Valley of Strength - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+217, 3084, 647, 1637, 5170, '0', '0', 0, 0, 1, -5.20674419403076171, -11.3431806564331054, -17.6101226806640625, 4.712388992309570312, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Bluffwatcher (Area: Valley of Strength - Difficulty: 0) (Auras: )
(@CGUID+218, 31723, 613, 1637, 5170, '0', '0', 0, 0, 1, -10.755157470703125, -12.8128557205200195, -16.7745208740234375, 4.537856101989746093, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Crewman Barrowswizzle (Area: Valley of Strength - Difficulty: 0)
(@CGUID+219, 31724, 613, 1637, 5170, '0', '0', 0, 0, 1, 5.776269912719726562, -2.00468897819519042, -17.7218532562255859, 1.640609502792358398, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Crewman Paltertop (Area: Valley of Strength - Difficulty: 0)
(@CGUID+220, 31725, 613, 1637, 5170, '0', '0', 0, 0, 1, 10.69841194152832031, -7.82192087173461914, -16.6006126403808593, 3.281219005584716796, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Sky-Captain LaFontaine (Area: Valley of Strength - Difficulty: 0)
(@CGUID+221, 31726, 613, 1637, 5170, '0', '0', 0, 0, 1, -3.45306801795959472, -13.789586067199707, -17.6110668182373046, 1.431169986724853515, 120, 0, 0, 264578, 0, 0, 0, 0, 0, 45505), -- Grunt Gritch (Area: Valley of Strength - Difficulty: 0)
(@CGUID+222, 31727, 613, 1637, 5170, '0', '0', 0, 0, 1, -3.38307595252990722, -1.91392505168914794, -17.6198005676269531, 4.729842185974121093, 120, 0, 0, 264578, 0, 0, 0, 0, 0, 45505), -- Grunt Grikee (Area: Valley of Strength - Difficulty: 0)
(@CGUID+223, 25075, 613, 1637, 5170, '0', '0', 0, 0, 0, 9.445420265197753906, -7.84947490692138671, -16.6006126403808593, 0.05235987901687622, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Zeppelin Controls (Area: Valley of Strength - Difficulty: 0) (Auras: )
(@CGUID+224, 31720, 613, 1637, 5170, '0', '0', 0, 0, 1, -16.5685329437255859, -5.08333110809326171, -15.9421186447143554, 1.989675283432006835, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Crewman Shubbscoop (Area: Valley of Strength - Difficulty: 0)
(@CGUID+225, 49743, 1, 1637, 5170, '0', '0', 0, 0, 0, 1638.7105712890625, -4457.0283203125, 97.01953125, 4.412012577056884765, 120, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Dung Beetle (Area: Valley of Strength - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+226, 62115, 1, 1637, 5170, '0', '0', 0, 0, 0, 1671.5560302734375, -4459.84814453125, 97.2185211181640625, 2.197757720947265625, 120, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Dung Beetle (Area: Valley of Strength - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+227, 74228, 1, 1637, 5170, '0', '0', 0, 0, 1, 1761.97998046875, -4391.81982421875, 109.7133331298828125, 0.610865235328674316, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Darkspear Headhunter (Area: Valley of Strength - Difficulty: 0) (Auras: )
(@CGUID+228, 51346, 1, 1637, 5170, '0', '0', 0, 0, 1, 1981.55810546875, -4620.09423828125, 70.4389190673828125, 3.547045469284057617, 120, 10, 0, 198434, 0, 1, 0, 0, 0, 45505), -- Orgrimmar Wind Rider (Area: Valley of Strength - Difficulty: 0) (Auras: ) (possible waypoints or random movement)
(@CGUID+229, 3296, 1, 1637, 5170, '0', '0', 0, 0, 1, 1706.1400146484375, -4308.47021484375, 31.43703460693359375, 4.921828269958496093, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Orgrimmar Grunt (Area: Valley of Strength - Difficulty: 0) (Auras: )
(@CGUID+230, 3296, 1, 1637, 5170, '0', '0', 0, 0, 1, 1734.3912353515625, -4289.32177734375, 101.5674514770507812, 2.263518571853637695, 120, 10, 0, 198434, 0, 1, 0, 0, 0, 45505), -- Orgrimmar Grunt (Area: Valley of Strength - Difficulty: 0) (Auras: ) (possible waypoints or random movement)
(@CGUID+231, 49837, 1, 1637, 5170, '0', '0', 0, 0, 0, 1779.890625, -4331.33154296875, 101.5342636108398437, 0.521058857440948486, 120, 10, 0, 27, 0, 1, 0, 0, 0, 45505), -- Spiny Lizard (Area: Valley of Strength - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+232, 3296, 1, 1637, 5170, '0', '0', 0, 0, 1, 1687.3800048828125, -4281.14013671875, 28.85983467102050781, 4.084070205688476562, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Orgrimmar Grunt (Area: Valley of Strength - Difficulty: 0) (Auras: )
(@CGUID+233, 44158, 1, 1637, 5170, '0', '0', 0, 0, 2, 1717.47998046875, -4280.68994140625, 102.0893325805664062, 1.553343057632446289, 120, 0, 0, 1914, 0, 0, 0, 0, 0, 45505), -- Orgrimmar Skyway Peon (Area: Valley of Strength - Difficulty: 0)
(@CGUID+234, 55382, 1, 1637, 5170, '0', '0', 0, 0, 0, 1765.77783203125, -4345.20654296875, 101.8379058837890625, 0.453785598278045654, 120, 0, 0, 105831, 7196, 0, 0, 0, 0, 45505), -- Darkmoon Faire Mystic Mage (Area: Valley of Strength - Difficulty: 0)
(@CGUID+235, 3296, 1, 1637, 5170, '0', '0', 0, 0, 1, 1759.050048828125, -4302.3701171875, 7.234433650970458984, 5.323254108428955078, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Orgrimmar Grunt (Area: Valley of Strength - Difficulty: 0) (Auras: )
(@CGUID+236, 3296, 1, 1637, 5170, '0', '0', 0, 0, 1, 1708.4271240234375, -4280.876953125, 101.5560684204101562, 5.951572895050048828, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Orgrimmar Grunt (Area: Valley of Strength - Difficulty: 0) (Auras: )
(@CGUID+237, 47246, 1, 1637, 5170, '0', '0', 0, 0, 1, 1757.6199951171875, -4349.509765625, -7.8115243911743164, 0.977384388446807861, 120, 0, 0, 142872, 7196, 0, 0, 0, 0, 45505), -- Ureda (Area: Valley of Strength - Difficulty: 0)
(@CGUID+238, 47247, 1, 1637, 5170, '0', '0', 0, 0, 1, 1764.56005859375, -4349.509765625, -7.79922723770141601, 5.829399585723876953, 120, 0, 0, 132289, 7196, 0, 0, 0, 0, 45505), -- Marud (Area: Valley of Strength - Difficulty: 0) (Auras: 79865 - Frost Armor)
(@CGUID+239, 47248, 1, 1637, 5170, '0', '0', 0, 0, 1, 1756, -4343.5400390625, -7.85525465011596679, 2.635447263717651367, 120, 10, 0, 132289, 7196, 1, 0, 0, 0, 45505), -- Gija (Area: Valley of Strength - Difficulty: 0) (Auras: 79849 - Molten Armor) (possible waypoints or random movement)
(@CGUID+240, 3329, 1, 1637, 5170, '0', '0', 0, 0, 1, 1769.719970703125, -4370.60986328125, -16.1284656524658203, 5.654866695404052734, 120, 0, 0, 138903, 0, 0, 0, 0, 0, 45505), -- Kor'jus (Area: Valley of Strength - Difficulty: 0)
(@CGUID+241, 47253, 1, 1637, 5170, '0', '0', 0, 0, 1, 1769.1300048828125, -4328.990234375, -8.19605731964111328, 0.069813169538974761, 120, 0, 0, 142872, 7196, 0, 0, 0, 0, 45505), -- Rundok (Area: Valley of Strength - Difficulty: 0)
(@CGUID+242, 141310, 1, 1637, 5170, '0', '0', 0, 0, 0, 1775.248291015625, -4344.60400390625, -7.37277460098266601, 1.156342983245849609, 120, 0, 0, 14178, 5751, 0, 0, 0, 0, 45505), -- Associate Telemancer Rafcav (Area: Valley of Strength - Difficulty: 0)
(@CGUID+243, 3331, 1, 1637, 5170, '0', '0', 0, 0, 1, 1750.258056640625, -4321.05908203125, 6.141550540924072265, 0.872664630413055419, 120, 0, 0, 138903, 0, 0, 0, 0, 0, 45505), -- Kareth (Area: Valley of Strength - Difficulty: 0)
(@CGUID+244, 3296, 1, 1637, 5170, '0', '0', 0, 0, 1, 1779.014892578125, -4383.89990234375, 102.4732437133789062, 2.425144195556640625, 120, 10, 0, 198434, 0, 1, 0, 0, 0, 45505), -- Orgrimmar Grunt (Area: Valley of Strength - Difficulty: 0) (Auras: ) (possible waypoints or random movement)
(@CGUID+245, 3296, 1, 1637, 5170, '0', '0', 0, 0, 1, 1730.510009765625, -4285.490234375, 17.79123306274414062, 2.007128715515136718, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Orgrimmar Grunt (Area: Valley of Strength - Difficulty: 0) (Auras: )
(@CGUID+246, 44919, 1, 1637, 5170, '0', '0', 0, 0, 1, 1799.5400390625, -4357.08984375, 102.8703384399414062, 4.590215682983398437, 120, 0, 0, 165361, 0, 0, 0, 0, 0, 45505), -- Maztha (Area: Valley of Strength - Difficulty: 0)
(@CGUID+247, 3216, 1, 1637, 5170, '0', '0', 0, 0, 1, 1800.548583984375, -4374.52978515625, -17.1281490325927734, 4.572762489318847656, 120, 0, 0, 152132, 0, 0, 0, 0, 0, 45505), -- Arnak Fireblade (Area: Valley of Strength - Difficulty: 0)
(@CGUID+248, 74228, 1, 1637, 5170, '0', '0', 0, 0, 1, 1804.68994140625, -4410.81982421875, -17.633066177368164, 1.710422635078430175, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Darkspear Headhunter (Area: Valley of Strength - Difficulty: 0) (Auras: )
(@CGUID+249, 14881, 1, 1637, 5170, '0', '0', 0, 0, 0, 1798.4930419921875, -4419.73779296875, 102.8904495239257812, 0.783415138721466064, 120, 0, 0, 5, 0, 0, 0, 0, 0, 45505); -- Spider (Area: Valley of Strength - Difficulty: 0)

INSERT INTO `creature` (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnDifficulties`, `PhaseId`, `PhaseGroup`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `wander_distance`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`, `VerifiedBuild`) VALUES
(@CGUID+250, 3310, 1, 1637, 5170, '0', '0', 0, 0, 1, 1799.949951171875, -4370.14013671875, 102.9333343505859375, 1.064650893211364746, 120, 0, 0, 396867, 0, 0, 0, 0, 0, 45505), -- Doras (Area: Valley of Strength - Difficulty: 0) (Auras: )
(@CGUID+251, 14881, 1, 1637, 5170, '0', '0', 0, 0, 0, 1802.060791015625, -4420.94775390625, 104.2365264892578125, 0.783415138721466064, 120, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Spider (Area: Valley of Strength - Difficulty: 0)
(@CGUID+252, 50323, 1, 1637, 5170, '0', '0', 0, 0, 1, 1806.8021240234375, -4377.9462890625, 103.1601028442382812, 5.916666030883789062, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Frizzo Villamar (Area: Valley of Strength - Difficulty: 0)
(@CGUID+253, 3296, 1, 1637, 5170, '0', '0', 0, 0, 1, 1795.7099609375, -4342.56005859375, -10.7252674102783203, 0.383972436189651489, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Orgrimmar Grunt (Area: Valley of Strength - Difficulty: 0) (Auras: )
(@CGUID+254, 49837, 1, 1637, 5170, '0', '0', 0, 0, 0, 1767.89697265625, -4446.54150390625, 102.0092391967773437, 3.07868051528930664, 120, 10, 0, 27, 0, 1, 0, 0, 0, 45505), -- Spiny Lizard (Area: Valley of Strength - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+255, 50488, 1, 1637, 5170, '0', '0', 0, 0, 1, 1809.560791015625, -4382.66845703125, 103.14422607421875, 2.076941728591918945, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Stone Guard Nargol (Area: Valley of Strength - Difficulty: 0)
(@CGUID+256, 44158, 1, 1637, 5170, '0', '0', 0, 0, 0, 1798.739990234375, -4383.1298828125, 103.357086181640625, 2.264623403549194335, 120, 10, 0, 1914, 0, 1, 0, 0, 0, 45505), -- Orgrimmar Skyway Peon (Area: Valley of Strength - Difficulty: 0) (Auras: 81245 - Orc Carrying Logs) (possible waypoints or random movement)
(@CGUID+257, 20492, 1, 1637, 5170, '0', '0', 0, 0, 0, 1797.68994140625, -4344.9599609375, 102.3963394165039062, 4.537856101989746093, 120, 0, 0, 1914, 0, 0, 0, 0, 0, 45505), -- Swift Yellow Wind Rider (Area: Valley of Strength - Difficulty: 0)
-- (@CGUID+258, 62821, 0, 1637, 5170, '0', '0', 0, 0, 0, -0.20000000298023223, 0, -0.20000000298023223, 0, 120, 0, 0, 158747, 10794, 0, 0, 0, 0, 45505), -- Mystic Birdhat (Area: Valley of Strength - Difficulty: 0) (Auras: 122729 - Grand Expedition Yak, 123236 - Grummle Booth A) - !!! on transport - transport template not found !!!
-- (@CGUID+259, 62822, 0, 1637, 5170, '0', '0', 0, 0, 0, -0.20000000298023223, 0, -0.20000000298023223, 0, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Cousin Slowhands (Area: Valley of Strength - Difficulty: 0) (Auras: 122729 - Grand Expedition Yak, 123240 - Grummle Booth B) - !!! on transport - transport template not found !!!
(@CGUID+260, 63626, 1, 1637, 5170, '0', '0', 0, 0, 0, 1799.375, -4420.59228515625, 102.8434295654296875, 1.095773577690124511, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Varzok (Area: Valley of Strength - Difficulty: 0)
(@CGUID+261, 62194, 1, 1637, 5170, '0', '0', 0, 0, 1, 1730.5399169921875, -4496.72900390625, 31.2299346923828125, 4.492234706878662109, 120, 0, 0, 396867, 100, 0, 0, 0, 0, 45505), -- Ukos Bloodwhisper (Area: Valley of Strength - Difficulty: 0)
(@CGUID+262, 42506, 1, 1637, 5170, '0', '0', 0, 0, 1, 1762.2847900390625, -4489.65283203125, 45.049896240234375, 3.455751895904541015, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Marogg (Area: Valley of Strength - Difficulty: 0)
(@CGUID+263, 50477, 1, 1637, 5170, '0', '0', 0, 0, 1, 1811.6336669921875, -4376.7275390625, 103.337158203125, 3.40339207649230957, 120, 0, 0, 105831, 7196, 0, 0, 0, 0, 45505), -- Champion Uru'zin (Area: Valley of Strength - Difficulty: 0)
(@CGUID+264, 49837, 1, 1637, 5170, '0', '0', 0, 0, 0, 1805.756591796875, -4437.3701171875, 103.4642410278320312, 5.370059013366699218, 120, 10, 0, 27, 0, 1, 0, 0, 0, 45505), -- Spiny Lizard (Area: Valley of Strength - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+265, 46709, 1, 1637, 5170, '0', '0', 0, 0, 1, 1772.1800537109375, -4482.509765625, 45.63864898681640625, 0.879462242126464843, 120, 10, 0, 145518, 0, 1, 0, 0, 0, 45505), -- Arugi (Area: Valley of Strength - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+266, 74228, 1, 1637, 5170, '0', '0', 0, 0, 1, 1814.6400146484375, -4406, -17.8347663879394531, 2.338741064071655273, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Darkspear Headhunter (Area: Valley of Strength - Difficulty: 0) (Auras: )
(@CGUID+267, 3296, 1, 1637, 5170, '0', '0', 0, 0, 1, 1776.707763671875, -4501.02197265625, 44.9395904541015625, 2.839626789093017578, 120, 10, 0, 198434, 0, 1, 0, 0, 0, 45505), -- Orgrimmar Grunt (Area: Valley of Strength - Difficulty: 0) (Auras: ) (possible waypoints or random movement)
(@CGUID+268, 14499, 1, 1637, 5170, '0', '0', 0, 0, 0, 1801.841552734375, -4497.9951171875, 24.34192276000976562, 1.198682188987731933, 120, 10, 0, 41, 0, 1, 0, 0, 0, 45505), -- Horde Orphan (Area: Valley of Strength - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+269, 3367, 1, 1637, 5170, '0', '0', 0, 0, 1, 1743.44580078125, -4504.34423828125, 30.11760330200195312, 2.380054950714111328, 120, 10, 0, 138903, 0, 1, 0, 0, 0, 45505), -- Felika (Area: Valley of Strength - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+270, 62115, 1, 1637, 5170, '0', '0', 0, 0, 0, 1690.5224609375, -4486.3505859375, 95.28633880615234375, 0.765321016311645507, 120, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Dung Beetle (Area: Valley of Strength - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+271, 49837, 1, 1637, 5170, '0', '0', 0, 0, 0, 1671.8695068359375, -4491.29248046875, 95.974273681640625, 2.267371654510498046, 120, 10, 0, 27, 0, 1, 0, 0, 0, 45505), -- Spiny Lizard (Area: Valley of Strength - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+272, 49743, 1, 1637, 5170, '0', '0', 0, 0, 0, 1789.56396484375, -4420.63671875, 103.6205368041992187, 4.226910591125488281, 120, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Dung Beetle (Area: Valley of Strength - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+273, 14451, 1, 1637, 5170, '0', '0', 0, 0, 0, 1818.5799560546875, -4514.4599609375, 23.58583450317382812, 4.921828269958496093, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Orphan Matron Battlewail (Area: Valley of Strength - Difficulty: 0)
(@CGUID+274, 49837, 1, 1637, 5170, '0', '0', 0, 0, 0, 1751.473388671875, -4558.8115234375, 95.30213165283203125, 5.34593057632446289, 120, 10, 0, 27, 0, 1, 0, 0, 0, 45505), -- Spiny Lizard (Area: Valley of Strength - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+275, 2857, 1, 1637, 5170, '0', '0', 0, 0, 1, 1825.1400146484375, -4489.22021484375, 23.68383407592773437, 5.829399585723876953, 120, 0, 0, 134935, 0, 0, 0, 0, 0, 45505), -- Thund (Area: Valley of Strength - Difficulty: 0)
(@CGUID+276, 62199, 1, 1637, 5170, '0', '0', 0, 0, 0, 1807.28125, -4515.36962890625, 23.2215728759765625, 4.26976776123046875, 120, 0, 0, 65, 126, 0, 0, 0, 0, 45505), -- Gogu (Area: Valley of Strength - Difficulty: 0)
(@CGUID+277, 62200, 1, 1637, 5170, '0', '0', 0, 0, 0, 1808.126708984375, -4515.4130859375, 23.29487037658691406, 4.20536661148071289, 120, 0, 0, 56, 115, 0, 0, 0, 0, 45505), -- Sasi (Area: Valley of Strength - Difficulty: 0)
(@CGUID+278, 14499, 1, 1637, 5170, '0', '0', 0, 0, 0, 1809.322021484375, -4493.98291015625, 24.31583786010742187, 0.651271045207977294, 120, 10, 0, 27, 0, 1, 0, 0, 0, 45505), -- Horde Orphan (Area: Valley of Strength - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+279, 54472, 1, 1637, 5170, '0', '0', 0, 0, 1, 1721.032958984375, -4513.22216796875, 31.25615119934082031, 0.290519982576370239, 120, 0, 0, 317493, 21588, 0, 0, 0, 0, 45505), -- Vaultkeeper Jazra (Area: Valley of Strength - Difficulty: 0) (Auras: 101667 - Arcane Vault Sphere)
(@CGUID+280, 54473, 1, 1637, 5170, '0', '0', 0, 0, 1, 1727.328125, -4519.50341796875, 32.64420318603515625, 1.29154360294342041, 120, 0, 0, 317493, 21588, 0, 0, 0, 0, 45505), -- Warpweaver Dushar (Area: Valley of Strength - Difficulty: 0) (Auras: )
(@CGUID+281, 3369, 1, 1637, 5170, '0', '0', 0, 0, 1, 1772.4200439453125, -4511.52001953125, 27.86450767517089843, 3.898036003112792968, 120, 10, 0, 138903, 0, 1, 0, 0, 0, 45505), -- Gotri (Area: Valley of Strength - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+282, 49743, 1, 1637, 5170, '0', '0', 0, 0, 0, 1703.952880859375, -4519.3125, 89.574249267578125, 3.632596492767333984, 120, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Dung Beetle (Area: Valley of Strength - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+283, 57801, 1, 1637, 5170, '0', '0', 0, 0, 1, 1727.3680419921875, -4507.533203125, 30.77355384826660156, 4.817108631134033203, 120, 0, 0, 6618, 8040, 0, 0, 0, 0, 45505), -- Thaumaturge Altha (Area: Valley of Strength - Difficulty: 0)
(@CGUID+284, 14499, 1, 1637, 5170, '0', '0', 0, 0, 0, 1812.6700439453125, -4494.27001953125, 24.41623306274414062, 5.096361160278320312, 120, 0, 0, 27, 0, 0, 0, 0, 0, 45505), -- Horde Orphan (Area: Valley of Strength - Difficulty: 0)
(@CGUID+285, 68979, 1, 1637, 5170, '0', '0', 0, 0, 1, 1733.0816650390625, -4514.705078125, 30.76891517639160156, 2.84880685806274414, 120, 0, 0, 317493, 21588, 0, 0, 0, 0, 45505), -- Voidbinder Zorlan (Area: Valley of Strength - Difficulty: 0)
(@CGUID+286, 14498, 1, 1637, 5170, '0', '0', 0, 0, 1, 1810.56005859375, -4502.169921875, 24.41543388366699218, 5.148721218109130859, 120, 0, 0, 145518, 0, 0, 0, 0, 0, 45505), -- Tosamina (Area: Valley of Strength - Difficulty: 0)
(@CGUID+287, 14499, 1, 1637, 5170, '0', '0', 0, 0, 0, 1812.5699462890625, -4496.77978515625, 24.40493392944335937, 1.186823844909667968, 120, 0, 0, 41, 0, 0, 0, 0, 0, 45505), -- Horde Orphan (Area: Valley of Strength - Difficulty: 0)
(@CGUID+288, 52809, 1, 1637, 5170, '0', '0', 0, 0, 0, 1793.5274658203125, -4526.8427734375, 23.5264892578125, 3.258209705352783203, 120, 0, 0, 132289, 3155, 0, 0, 0, 0, 45505), -- Blax Bottlerocket (Area: Valley of Strength - Difficulty: 0) (Auras: )
-- (@CGUID+289, 52812, 0, 1637, 5170, '0', '0', 0, 0, 0, 0.899999976158142089, -0.10000000149011611, 0, 0, 120, 0, 0, 1914, 0, 0, 0, 0, 0, 45505), -- Toy Cart (Area: Valley of Strength - Difficulty: 0) (Auras: 46598 - Ride Vehicle Hardcoded, 96847 - Blue Doll State) - !!! on transport - transport template not found !!!
(@CGUID+290, 46708, 1, 1637, 5170, '0', '0', 0, 0, 0, 1779.300048828125, -4487.72021484375, 45.63865280151367187, 3.211405754089355468, 120, 10, 0, 132289, 0, 1, 0, 0, 0, 45505), -- Suja (Area: Valley of Strength - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+291, 52032, 1, 1637, 5170, '0', '0', 0, 0, 1, 1833.1336669921875, -4469.65087890625, 47.69504928588867187, 5.811946392059326171, 120, 0, 0, 105831, 7196, 0, 0, 0, 0, 45505), -- Sinzi Sparkscribe (Area: Valley of Strength - Difficulty: 0)
(@CGUID+292, 62114, 1, 1637, 5170, '0', '0', 0, 0, 0, 1789.6036376953125, -4478, 109.2106704711914062, 1.942123055458068847, 120, 10, 0, 27, 0, 1, 0, 0, 0, 45505), -- Spiny Lizard (Area: Valley of Strength - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+293, 3296, 1, 1637, 5170, '0', '0', 0, 0, 1, 1796.990966796875, -4533.99365234375, 23.30989646911621093, 0.179393857717514038, 120, 10, 0, 198434, 0, 1, 0, 0, 0, 45505), -- Orgrimmar Grunt (Area: Valley of Strength - Difficulty: 0) (Auras: ) (possible waypoints or random movement)
(@CGUID+294, 14499, 1, 1637, 5170, '0', '0', 0, 0, 0, 1804.699951171875, -4502.4501953125, 24.43733406066894531, 3.96189737319946289, 120, 0, 0, 34, 0, 0, 0, 0, 0, 45505), -- Horde Orphan (Area: Valley of Strength - Difficulty: 0)
-- (@CGUID+295, 52810, 0, 1637, 5170, '0', '0', 0, 0, 0, -0.17499999701976776, 0, 0.5, 0, 120, 10, 0, 1914, 0, 1, 0, 0, 0, 45505), -- Toy Cart Bunny (Area: Valley of Strength - Difficulty: 0) (Auras: 46598 - Ride Vehicle Hardcoded, 96850 - Toy Cart Contents, 16245 - Freeze Anim, 97577 - Handle State) - !!! on transport - transport template not found !!! (possible waypoints or random movement)
(@CGUID+296, 14499, 1, 1637, 5170, '0', '0', 0, 0, 0, 1814.3199462890625, -4496.009765625, 24.43963432312011718, 2.635447263717651367, 120, 0, 0, 27, 0, 0, 0, 0, 0, 45505), -- Horde Orphan (Area: Valley of Strength - Difficulty: 0)
(@CGUID+297, 49737, 1, 1637, 5170, '0', '0', 0, 0, 1, 1763.763916015625, -4494.328125, 45.04059600830078125, 3.612831592559814453, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Shazdar (Area: Valley of Strength - Difficulty: 0)
(@CGUID+298, 3368, 1, 1637, 5170, '0', '0', 0, 0, 1, 1773.6500244140625, -4490.16015625, 45.63865280151367187, 4.520402908325195312, 120, 0, 0, 138903, 0, 0, 0, 0, 0, 45505), -- Borstan (Area: Valley of Strength - Difficulty: 0)
(@CGUID+299, 3412, 1, 1637, 5167, '0', '0', 0, 0, 1, 1833.0999755859375, -4485.35986328125, 23.59177398681640625, 0.795732736587524414, 120, 10, 0, 145518, 0, 1, 0, 0, 0, 45505), -- Nogg (Area: The Drag - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+300, 3413, 1, 1637, 5167, '0', '0', 0, 0, 1, 1834.239990234375, -4493.419921875, 23.68383407592773437, 3.089232683181762695, 120, 0, 0, 138903, 0, 0, 0, 0, 0, 45505), -- Sovik (Area: The Drag - Difficulty: 0)
(@CGUID+301, 3363, 1, 1637, 5167, '0', '0', 0, 0, 1, 1801.010009765625, -4563.080078125, 23.08343315124511718, 1.553343057632446289, 120, 0, 0, 145518, 0, 0, 0, 0, 0, 45505), -- Magar (Area: The Drag - Difficulty: 0)
(@CGUID+302, 3364, 1, 1637, 5167, '0', '0', 0, 0, 0, 1807.0400390625, -4563.02978515625, 22.99802207946777343, 1.65806281566619873, 120, 10, 0, 138903, 0, 1, 0, 0, 0, 45505), -- Borya (Area: The Drag - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+303, 62115, 1, 1637, 5167, '0', '0', 0, 0, 0, 1737.1722412109375, -4548.6845703125, 91.412933349609375, 5.149187564849853515, 120, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Dung Beetle (Area: The Drag - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+304, 11017, 1, 1637, 5167, '0', '0', 0, 0, 1, 1830.800048828125, -4494.97998046875, 23.68383407592773437, 0.890117883682250976, 120, 0, 0, 165361, 0, 0, 0, 0, 0, 45505), -- Roxxik (Area: The Drag - Difficulty: 0)
(@CGUID+305, 3315, 1, 1637, 5167, '0', '0', 0, 0, 1, 1791.280029296875, -4566.02978515625, 23.08343315124511718, 0.680678427219390869, 120, 0, 0, 138903, 0, 0, 0, 0, 0, 45505), -- Tor'phan (Area: The Drag - Difficulty: 0)
(@CGUID+306, 3317, 1, 1637, 5167, '0', '0', 0, 0, 0, 1814.780029296875, -4563.10009765625, 22.99802207946777343, 2.286381244659423828, 120, 0, 0, 138903, 0, 0, 0, 0, 0, 45505), -- Ollanus (Area: The Drag - Difficulty: 0)
(@CGUID+307, 49743, 1, 1637, 5167, '0', '0', 0, 0, 0, 1794.0877685546875, -4453.7412109375, 105.7982635498046875, 5.051760196685791015, 120, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Dung Beetle (Area: The Drag - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+308, 46718, 1, 1637, 5167, '0', '0', 0, 0, 0, 1837.9871826171875, -4464.3515625, 54.23462295532226562, 2.848134756088256835, 120, 10, 0, 105831, 7196, 1, 0, 0, 0, 45505), -- Moraka (Area: The Drag - Difficulty: 0) (Auras: 79849 - Molten Armor) (possible waypoints or random movement)
(@CGUID+309, 15476, 1, 1637, 5167, '0', '0', 0, 0, 0, 1800.8541259765625, -4420.65283203125, 102.9233322143554687, 1.084395527839660644, 120, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Scorpid (Area: The Drag - Difficulty: 0)
(@CGUID+310, 15476, 1, 1637, 5167, '0', '0', 0, 0, 0, 1797.7135009765625, -4420.501953125, 103.904296875, 1.648120641708374023, 120, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Scorpid (Area: The Drag - Difficulty: 0)
(@CGUID+311, 46716, 1, 1637, 5167, '0', '0', 0, 0, 1, 1838.719970703125, -4464.1298828125, 47.68993377685546875, 0, 120, 0, 0, 105831, 7196, 0, 0, 0, 0, 45505), -- Nerog (Area: The Drag - Difficulty: 0) (Auras: 79865 - Frost Armor)
(@CGUID+312, 5639, 1, 1637, 5170, '0', '0', 0, 0, 1, 1790.5528564453125, -4357.6025390625, -13.5725765228271484, 4.598822593688964843, 120, 0, 0, 145518, 0, 0, 0, 0, 0, 45505), -- Craven Drok (Area: Valley of Strength - Difficulty: 0)
(@CGUID+313, 44158, 1, 1637, 5170, '0', '0', 0, 0, 1, 1772.6085205078125, -4306.14404296875, 100.9663238525390625, 5.167040824890136718, 120, 10, 0, 1914, 0, 1, 0, 0, 0, 45505), -- Orgrimmar Skyway Peon (Area: Valley of Strength - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+314, 44158, 1, 1637, 5170, '0', '0', 0, 0, 2, 1756.56005859375, -4314.14990234375, 101.4449996948242187, 3.787364482879638671, 120, 10, 0, 1914, 0, 1, 0, 0, 0, 45505), -- Orgrimmar Skyway Peon (Area: Valley of Strength - Difficulty: 0) (Auras: 81245 - Orc Carrying Logs) (possible waypoints or random movement)
(@CGUID+315, 44158, 1, 1637, 5170, '0', '0', 0, 0, 3, 1801.71533203125, -4345.11572265625, 102.163543701171875, 4.430567741394042968, 120, 10, 0, 1914, 0, 1, 0, 0, 0, 45505), -- Orgrimmar Skyway Peon (Area: Valley of Strength - Difficulty: 0) (Auras: 82614 - Bailing Hay) (possible waypoints or random movement)
(@CGUID+316, 44948, 1, 1637, 5170, '0', '0', 0, 0, 0, 1805.56005859375, -4339.89990234375, 101.9895172119140625, 3.804817676544189453, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Wind Rider Cub (Area: Valley of Strength - Difficulty: 0)
(@CGUID+317, 44158, 1, 1637, 5170, '0', '0', 0, 0, 1, 1813.7099609375, -4353.580078125, 102.7278213500976562, 1.710422635078430175, 120, 10, 0, 1914, 0, 1, 0, 0, 0, 45505), -- Orgrimmar Skyway Peon (Area: Valley of Strength - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+318, 44918, 1, 1637, 5170, '0', '0', 0, 0, 0, 1806.93994140625, -4340.669921875, 102.1333389282226562, 4.258603572845458984, 120, 0, 0, 165361, 0, 0, 0, 0, 0, 45505), -- Drakma (Area: Valley of Strength - Difficulty: 0)
(@CGUID+319, 20486, 1, 1637, 5170, '0', '0', 0, 0, 0, 1824.47998046875, -4344.22998046875, 102.8033370971679687, 4.258603572845458984, 120, 0, 0, 1914, 0, 0, 0, 0, 0, 45505), -- Blue Wind Rider (Area: Valley of Strength - Difficulty: 0)
(@CGUID+320, 20488, 1, 1637, 5170, '0', '0', 0, 0, 0, 1821.5699462890625, -4344.22021484375, 102.6963348388671875, 4.904375076293945312, 120, 0, 0, 1914, 0, 0, 0, 0, 0, 45505), -- Tawny Wind Rider (Area: Valley of Strength - Difficulty: 0)
(@CGUID+321, 20490, 1, 1637, 5170, '0', '0', 0, 0, 0, 1792.8699951171875, -4310.77001953125, 101.2273330688476562, 2.059488534927368164, 120, 0, 0, 1914, 0, 0, 0, 0, 0, 45505), -- Swift Purple Wind Rider (Area: Valley of Strength - Difficulty: 0)
(@CGUID+322, 20491, 1, 1637, 5170, '0', '0', 0, 0, 0, 1793.3900146484375, -4328.91015625, 101.6143341064453125, 2.600540637969970703, 120, 0, 0, 1914, 0, 0, 0, 0, 0, 45505), -- Swift Red Wind Rider (Area: Valley of Strength - Difficulty: 0)
(@CGUID+323, 20489, 1, 1637, 5170, '0', '0', 0, 0, 0, 1792.9100341796875, -4324.81982421875, 101.4443359375, 3.874630928039550781, 120, 0, 0, 1914, 0, 0, 0, 0, 0, 45505), -- Swift Green Wind Rider (Area: Valley of Strength - Difficulty: 0)
(@CGUID+324, 20493, 1, 1637, 5170, '0', '0', 0, 0, 0, 1819.1600341796875, -4345.93994140625, 102.7053375244140625, 5.811946392059326171, 120, 0, 0, 1914, 0, 0, 0, 0, 0, 45505), -- Green Wind Rider (Area: Valley of Strength - Difficulty: 0)
(@CGUID+325, 44158, 1, 1637, 5170, '0', '0', 0, 0, 3, 1828.5, -4336.22998046875, 102.4020233154296875, 0.78539818525314331, 120, 0, 0, 1914, 0, 0, 0, 0, 0, 45505), -- Orgrimmar Skyway Peon (Area: Valley of Strength - Difficulty: 0) (Auras: 82614 - Bailing Hay)
(@CGUID+326, 49743, 1, 1637, 5170, '0', '0', 0, 0, 0, 1765.282470703125, -4296.91064453125, 101.0084609985351562, 1.29737555980682373, 120, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Dung Beetle (Area: Valley of Strength - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+327, 9564, 1, 1637, 5170, '0', '0', 0, 0, 1, 1839.0885009765625, -4393.62158203125, 135.316162109375, 5.427973747253417968, 120, 0, 0, 2297, 0, 0, 0, 0, 0, 45505), -- Frezza (Area: Valley of Strength - Difficulty: 0)
(@CGUID+328, 3296, 1, 1637, 5170, '0', '0', 0, 0, 1, 1844.001708984375, -4391.017578125, 103.7353973388671875, 2.460914134979248046, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Orgrimmar Grunt (Area: Valley of Strength - Difficulty: 0) (Auras: )
(@CGUID+329, 49743, 1, 1637, 5170, '0', '0', 0, 0, 0, 1853.052978515625, -4337.8671875, 101.8258895874023437, 0.425219058990478515, 120, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Dung Beetle (Area: Valley of Strength - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+330, 3296, 1, 1637, 5170, '0', '0', 0, 0, 1, 1879.3599853515625, -4371.97021484375, 100.7203369140625, 3.263765573501586914, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Orgrimmar Grunt (Area: Valley of Strength - Difficulty: 0) (Auras: )
(@CGUID+331, 49743, 1, 1637, 5170, '0', '0', 0, 0, 0, 1845.84375, -4336.994140625, 102.1152420043945312, 1.246958017349243164, 120, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Dung Beetle (Area: Valley of Strength - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+332, 44158, 1, 1637, 5170, '0', '0', 0, 0, 2, 1845.8900146484375, -4383.4599609375, 103.7353363037109375, 1.047197580337524414, 120, 0, 0, 1914, 0, 0, 0, 0, 0, 45505), -- Orgrimmar Skyway Peon (Area: Valley of Strength - Difficulty: 0)
(@CGUID+333, 44158, 1, 1637, 5170, '0', '0', 0, 0, 0, 1855.8699951171875, -4398.009765625, 105.1283340454101562, 4.799655437469482421, 120, 0, 0, 1914, 0, 0, 0, 0, 0, 45505), -- Orgrimmar Skyway Peon (Area: Valley of Strength - Difficulty: 0)
(@CGUID+334, 44158, 1, 1637, 5170, '0', '0', 0, 0, 0, 1800.0999755859375, -4308.31005859375, 101.2254867553710937, 1.867502331733703613, 120, 0, 0, 1914, 0, 0, 0, 0, 0, 45505), -- Orgrimmar Skyway Peon (Area: Valley of Strength - Difficulty: 0) (Auras: 82612 - Orc Carrying Hay Bail)
(@CGUID+335, 141528, 1, 1637, 5170, '0', '0', 0, 0, 0, 1844.4947509765625, -4389.32470703125, 135.3163299560546875, 4.533868312835693359, 120, 0, 0, 17723, 0, 0, 0, 0, 0, 45505), -- Clara Spelldriver (Area: Valley of Strength - Difficulty: 0)
(@CGUID+336, 3296, 1, 1637, 5170, '0', '0', 0, 0, 1, 1739.170166015625, -4285.033203125, 101.2182693481445312, 4.101523876190185546, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Orgrimmar Grunt (Area: Valley of Strength - Difficulty: 0) (Auras: )
(@CGUID+337, 44158, 1, 1637, 5170, '0', '0', 0, 0, 0, 1793.8199462890625, -4295.14990234375, 100.922332763671875, 3.630284786224365234, 120, 0, 0, 1914, 0, 0, 0, 0, 0, 45505), -- Orgrimmar Skyway Peon (Area: Valley of Strength - Difficulty: 0)
(@CGUID+338, 44158, 1, 1637, 5170, '0', '0', 0, 0, 0, 1855.27001953125, -4408.169921875, 103.9550018310546875, 5.310171127319335937, 120, 10, 0, 1914, 0, 1, 0, 0, 0, 45505), -- Orgrimmar Skyway Peon (Area: Valley of Strength - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+339, 3296, 1, 1637, 5170, '0', '0', 0, 0, 1, 1840.265625, -4395.205078125, 103.736114501953125, 2.356194496154785156, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Orgrimmar Grunt (Area: Valley of Strength - Difficulty: 0) (Auras: )
(@CGUID+340, 187775, 1, 1637, 5170, '0', '0', 0, 0, 0, 1761.013916015625, -4284.35595703125, 101.300079345703125, 4.160478591918945312, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Kanyaku (Area: Valley of Strength - Difficulty: 0) (Auras: 370841 - -0-)
(@CGUID+341, 44158, 1, 1637, 5170, '0', '0', 0, 0, 1, 1834, -4348.8701171875, 103.41033935546875, 2.216568231582641601, 120, 0, 0, 1914, 0, 0, 0, 0, 0, 45505), -- Orgrimmar Skyway Peon (Area: Valley of Strength - Difficulty: 0)
(@CGUID+342, 130911, 1, 1637, 5170, '0', '0', 0, 0, 0, 1847.935791015625, -4390.57275390625, 135.3160858154296875, 4.90349578857421875, 120, 0, 0, 396867, 0, 0, 0, 0, 0, 45505), -- Charles Gastly (Area: Valley of Strength - Difficulty: 0)
(@CGUID+343, 3296, 1, 1637, 5170, '0', '0', 0, 0, 1, 1866.0694580078125, -4392.09912109375, 135.316131591796875, 3.944444179534912109, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Orgrimmar Grunt (Area: Valley of Strength - Difficulty: 0) (Auras: )
(@CGUID+344, 49743, 1, 1637, 5170, '0', '0', 0, 0, 0, 1774.9154052734375, -4277.09423828125, 101.0674896240234375, 3.477985143661499023, 120, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Dung Beetle (Area: Valley of Strength - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+345, 26537, 1, 1637, 5170, '0', '0', 0, 0, 1, 1761.234375, -4285.36279296875, 133.19049072265625, 2.687807083129882812, 120, 0, 0, 2297, 0, 0, 0, 0, 0, 45505), -- Greeb Ramrocket (Area: Valley of Strength - Difficulty: 0)
(@CGUID+346, 43062, 1, 1637, 5170, '0', '0', 0, 0, 0, 1837.5, -4398.77001953125, 103.6391220092773437, 2.181661605834960937, 120, 10, 0, 1914, 0, 1, 0, 0, 0, 45505), -- Bort (Area: Valley of Strength - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+347, 3189, 1, 1637, 5170, '0', '0', 0, 0, 1, 1805.3199462890625, -4285.91015625, 7.114563465118408203, 3.141592741012573242, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Kor'ghan (Area: Valley of Strength - Difficulty: 0)
(@CGUID+348, 5909, 1, 1637, 5170, '0', '0', 0, 0, 0, 1838.469970703125, -4341.240234375, -15.230966567993164, 3.333578824996948242, 120, 0, 0, 152132, 0, 0, 0, 0, 0, 45505), -- Cazul (Area: Valley of Strength - Difficulty: 0)
(@CGUID+349, 3296, 1, 1637, 5170, '0', '0', 0, 0, 1, 1734.7274169921875, -4280.3818359375, 101.2387847900390625, 3.787364482879638671, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Orgrimmar Grunt (Area: Valley of Strength - Difficulty: 0) (Auras: )
(@CGUID+350, 44735, 1, 1637, 5170, '0', '0', 0, 0, 1, 1863.4599609375, -4297.75, 23.87613487243652343, 6.143558979034423828, 120, 0, 0, 142872, 7196, 0, 0, 0, 0, 45505), -- Seer Liwatha (Area: Valley of Strength - Difficulty: 0)
(@CGUID+351, 12136, 1, 1637, 5170, '0', '0', 0, 0, 1, 1870.376708984375, -4416.251953125, 135.3162384033203125, 2.286381244659423828, 120, 0, 0, 2297, 0, 0, 0, 0, 0, 45505), -- Snurk Bucksquick (Area: Valley of Strength - Difficulty: 0)
(@CGUID+352, 3334, 1, 1637, 5170, '0', '0', 0, 0, 1, 1810.8316650390625, -4271.04541015625, 7.300124645233154296, 3.944444179534912109, 120, 0, 0, 138903, 0, 0, 0, 0, 0, 45505), -- Rekkul (Area: Valley of Strength - Difficulty: 0)
(@CGUID+353, 3296, 1, 1637, 5170, '0', '0', 0, 0, 1, 1881.1099853515625, -4382.43994140625, 100.7253341674804687, 3.351032257080078125, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Orgrimmar Grunt (Area: Valley of Strength - Difficulty: 0) (Auras: )
(@CGUID+354, 45230, 1, 1637, 5170, '0', '0', 0, 0, 1, 1868.6500244140625, -4299.75, 23.98883438110351562, 3.141592741012573242, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Orgrimmar Brave (Area: Valley of Strength - Difficulty: 0) (Auras: )
(@CGUID+355, 3296, 1, 1637, 5170, '0', '0', 0, 0, 1, 1736.359375, -4282.41162109375, 133.190460205078125, 0.733038306236267089, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Orgrimmar Grunt (Area: Valley of Strength - Difficulty: 0) (Auras: )
(@CGUID+356, 47233, 1, 1637, 5170, '0', '0', 0, 0, 1, 1773.2099609375, -4282.9599609375, 7.975483417510986328, 1.239183783531188964, 120, 0, 0, 178590, 100, 0, 0, 0, 0, 45505), -- Gordul (Area: Valley of Strength - Difficulty: 0) (Auras: 10022 - Deadly Poison)
(@CGUID+357, 3296, 1, 1637, 5170, '0', '0', 0, 0, 1, 1843.6500244140625, -4396.60009765625, 4.932103633880615234, 2.652900457382202148, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Orgrimmar Grunt (Area: Valley of Strength - Difficulty: 0) (Auras: )
(@CGUID+358, 88704, 1, 1637, 5170, '0', '0', 0, 0, 1, 1843.890625, -4353.77783203125, -14.5776443481445312, 3.31612563133239746, 120, 0, 0, 165361, 0, 0, 0, 0, 0, 45505), -- Gran'dul (Area: Valley of Strength - Difficulty: 0)
(@CGUID+359, 88705, 1, 1637, 5170, '0', '0', 0, 0, 1, 1848.7882080078125, -4360.64599609375, -14.6395387649536132, 2.81739211082458496, 120, 0, 0, 165361, 0, 0, 0, 0, 0, 45505), -- Kranosh (Area: Valley of Strength - Difficulty: 0)
(@CGUID+360, 88706, 1, 1637, 5170, '0', '0', 0, 0, 1, 1838.72998046875, -4348.16015625, -14.5401668548583984, 3.420845270156860351, 120, 0, 0, 126997, 7196, 0, 0, 0, 0, 45505), -- Murgul (Area: Valley of Strength - Difficulty: 0)
(@CGUID+361, 5816, 1, 1637, 5170, '0', '0', 0, 0, 1, 1821.530029296875, -4300.2900390625, -12.105966567993164, 4.328416347503662109, 120, 0, 0, 138903, 0, 0, 0, 0, 0, 45505), -- Katis (Area: Valley of Strength - Difficulty: 0)
(@CGUID+362, 5875, 1, 1637, 5170, '0', '0', 0, 0, 1, 1850.34033203125, -4357.45849609375, -14.7192506790161132, 3.033954143524169921, 120, 0, 0, 152132, 0, 0, 0, 0, 0, 45505), -- Mordak Darkfist (Area: Valley of Strength - Difficulty: 0)
(@CGUID+363, 3328, 1, 1637, 5170, '0', '0', 0, 0, 1, 1772.530029296875, -4277.8798828125, 8.066233634948730468, 5.358160972595214843, 120, 0, 0, 165361, 0, 0, 0, 0, 0, 45505), -- Ormok (Area: Valley of Strength - Difficulty: 0)
(@CGUID+364, 3330, 1, 1637, 5170, '0', '0', 0, 0, 1, 1825.199951171875, -4303.72998046875, -12.0777673721313476, 2.129301786422729492, 120, 0, 0, 138903, 0, 0, 0, 0, 0, 45505), -- Muragus (Area: Valley of Strength - Difficulty: 0)
(@CGUID+365, 47254, 1, 1637, 5170, '0', '0', 0, 0, 0, 1838.9000244140625, -4346.22998046875, -14.6526670455932617, 3.40339207649230957, 120, 0, 0, 88898, 2375, 0, 0, 0, 0, 45505), -- Gizput (Area: Valley of Strength - Difficulty: 0)
(@CGUID+366, 3335, 1, 1637, 5170, '0', '0', 0, 0, 1, 1846.06005859375, -4324.10986328125, -15.4842662811279296, 3.59537816047668457, 120, 0, 0, 138903, 0, 0, 0, 0, 0, 45505), -- Hagrus (Area: Valley of Strength - Difficulty: 0)
(@CGUID+367, 45230, 1, 1637, 5170, '0', '0', 0, 0, 1, 1869.9200439453125, -4304.490234375, 23.64813423156738281, 5.934119224548339843, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Orgrimmar Brave (Area: Valley of Strength - Difficulty: 0) (Auras: )
(@CGUID+368, 3327, 1, 1637, 5170, '0', '0', 0, 0, 1, 1777.260009765625, -4280.41015625, 7.776883602142333984, 3.211405754089355468, 120, 0, 0, 152132, 0, 0, 0, 0, 0, 45505), -- Gest (Area: Valley of Strength - Difficulty: 0)
(@CGUID+369, 42548, 1, 1637, 5170, '0', '0', 0, 0, 0, 1896.1199951171875, -4341.85986328125, 24.04454421997070312, 4.577981948852539062, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Muddy Crawfish (Area: Valley of Strength - Difficulty: 0)
(@CGUID+370, 45230, 1, 1637, 5170, '0', '0', 0, 0, 1, 1886.5999755859375, -4319.6298828125, 24.03733444213867187, 0.837758064270019531, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Orgrimmar Brave (Area: Valley of Strength - Difficulty: 0) (Auras: )
(@CGUID+371, 3296, 1, 1637, 5170, '0', '0', 0, 0, 1, 1868.56005859375, -4297.10986328125, 23.98883438110351562, 3.159045934677124023, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Orgrimmar Grunt (Area: Valley of Strength - Difficulty: 0) (Auras: )
(@CGUID+372, 44725, 1, 1637, 5170, '0', '0', 0, 0, 1, 1863.8800048828125, -4292.68994140625, 23.90463447570800781, 5.550147056579589843, 120, 0, 0, 178590, 3155, 0, 0, 0, 0, 45505), -- Sunwalker Atohmo (Area: Valley of Strength - Difficulty: 0)
(@CGUID+373, 44726, 1, 1637, 5170, '0', '0', 0, 0, 1, 1888.949951171875, -4285.25, 23.70173454284667968, 3.839724302291870117, 120, 0, 0, 178590, 3155, 0, 0, 0, 0, 45505), -- Shalla Whiteleaf (Area: Valley of Strength - Difficulty: 0)
(@CGUID+374, 3296, 1, 1637, 5170, '0', '0', 0, 0, 1, 1889.5330810546875, -4358.80517578125, 40.64067459106445312, 2.2597503662109375, 120, 10, 0, 198434, 0, 1, 0, 0, 0, 45505), -- Orgrimmar Grunt (Area: Valley of Strength - Difficulty: 0) (Auras: ) (possible waypoints or random movement)
(@CGUID+375, 45230, 1, 1637, 5170, '0', '0', 0, 0, 1, 1889.9000244140625, -4292.3701171875, 23.51333427429199218, 5.078907966613769531, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Orgrimmar Brave (Area: Valley of Strength - Difficulty: 0) (Auras: )
(@CGUID+376, 45230, 1, 1637, 5170, '0', '0', 0, 0, 1, 1886.030029296875, -4288.5, 23.94393348693847656, 1.274090290069580078, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Orgrimmar Brave (Area: Valley of Strength - Difficulty: 0) (Auras: )
(@CGUID+377, 133271, 1, 1637, 5170, '0', '0', 0, 0, 1, 1893.3978271484375, -4307.60546875, 23.70066070556640625, 3.290417194366455078, 120, 10, 0, 132289, 0, 1, 0, 0, 0, 45505), -- Highmountain Pathfinder (Area: Valley of Strength - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+378, 49743, 1, 1637, 5170, '0', '0', 0, 0, 0, 1876.1085205078125, -4393.45263671875, 102.721435546875, 6.023146629333496093, 120, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Dung Beetle (Area: Valley of Strength - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+379, 3296, 1, 1637, 5170, '0', '0', 0, 0, 1, 1883.0400390625, -4287.72021484375, 23.94393348693847656, 1.308996915817260742, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Orgrimmar Grunt (Area: Valley of Strength - Difficulty: 0) (Auras: )
(@CGUID+380, 44743, 1, 1637, 5170, '0', '0', 0, 0, 1, 1872.8900146484375, -4281.4599609375, 23.90983390808105468, 4.921828269958496093, 120, 0, 0, 178590, 0, 0, 0, 0, 0, 45505), -- Nohi Plainswalker (Area: Valley of Strength - Difficulty: 0)
(@CGUID+381, 44740, 1, 1637, 5170, '0', '0', 0, 0, 1, 1884.1492919921875, -4282.3994140625, 23.75743484497070312, 4.677482128143310546, 120, 0, 0, 178590, 0, 0, 0, 0, 0, 45505), -- Sahi Cloudsinger (Area: Valley of Strength - Difficulty: 0)
(@CGUID+382, 44745, 1, 1637, 5170, '0', '0', 0, 0, 0, 1897.4100341796875, -4291.5, 24.01813316345214843, 0, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Sunwalker Atohmo's Kodo (Area: Valley of Strength - Difficulty: 0)
(@CGUID+383, 3296, 1, 1637, 5170, '0', '0', 0, 0, 1, 1876.3800048828125, -4290.740234375, 23.58663368225097656, 2.164208173751831054, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Orgrimmar Grunt (Area: Valley of Strength - Difficulty: 0) (Auras: )
(@CGUID+384, 44723, 1, 1637, 5170, '0', '0', 0, 0, 1, 1868.0899658203125, -4284.31982421875, 23.89853477478027343, 5.602506637573242187, 120, 0, 0, 178590, 0, 0, 0, 0, 0, 45505), -- Nahu Ragehoof (Area: Valley of Strength - Difficulty: 0)
(@CGUID+385, 45230, 1, 1637, 5170, '0', '0', 0, 0, 1, 1875.199951171875, -4286.6298828125, 23.97823333740234375, 2.199114799499511718, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Orgrimmar Brave (Area: Valley of Strength - Difficulty: 0) (Auras: )
(@CGUID+386, 42548, 1, 1637, 5170, '0', '0', 0, 0, 0, 1910.9207763671875, -4333.076171875, 18.93877410888671875, 4.104806900024414062, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Muddy Crawfish (Area: Valley of Strength - Difficulty: 0)
(@CGUID+387, 45230, 1, 1637, 5170, '0', '0', 0, 0, 1, 1871.3900146484375, -4289.10986328125, 23.97823333740234375, 2.199114799499511718, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Orgrimmar Brave (Area: Valley of Strength - Difficulty: 0) (Auras: )
(@CGUID+388, 42548, 1, 1637, 5170, '0', '0', 0, 0, 0, 1941.3572998046875, -4337.1220703125, 24.06873512268066406, 2.535453081130981445, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Muddy Crawfish (Area: Valley of Strength - Difficulty: 0)
(@CGUID+389, 174147, 1, 1637, 5170, '0', '0', 0, 0, 1, 1930.7117919921875, -4319.8369140625, 26.87274551391601562, 0.329966723918914794, 120, 0, 0, 11342, 5751, 0, 0, 0, 0, 45505), -- Archivist Sylvia (Area: Valley of Strength - Difficulty: 0)
(@CGUID+390, 4953, 1, 1637, 5170, '0', '0', 0, 0, 0, 1920.8330078125, -4354.166015625, 24.24162864685058593, 3.644678354263305664, 120, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Water Snake (Area: Valley of Strength - Difficulty: 0)
(@CGUID+391, 141912, 1, 1637, 5170, '0', '0', 0, 0, 1, 1910.76220703125, -4308.21728515625, 24.22046661376953125, 4.054365158081054687, 120, 0, 0, 17723, 0, 0, 0, 0, 0, 45505), -- Traveling Warrior (Area: Valley of Strength - Difficulty: 0)
(@CGUID+392, 54113, 1, 1637, 5170, '0', '0', 0, 0, 0, 1941.39599609375, -4345.75927734375, 23.92590141296386718, 2.936199188232421875, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Spooks (Area: Valley of Strength - Difficulty: 0)
(@CGUID+393, 4953, 1, 1637, 5170, '0', '0', 0, 0, 0, 1925.377685546875, -4293.69677734375, 24.66371726989746093, 5.811259269714355468, 120, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Water Snake (Area: Valley of Strength - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+394, 141920, 1, 1637, 5170, '0', '0', 0, 0, 1, 1909.467041015625, -4310.1875, 24.02230262756347656, 0.768239915370941162, 120, 0, 0, 17723, 0, 0, 0, 0, 0, 45505), -- Traveling Son (Area: Valley of Strength - Difficulty: 0)
(@CGUID+395, 47663, 1, 1637, 0, '0', '0', 0, 0, 1, 1932.4658203125, -4388.7158203125, 23.41394615173339843, 4.736302375793457031, 120, 10, 0, 529156, 0, 1, 0, 0, 0, 45505), -- Scout Obrok (Area: 0 - Difficulty: 0) (Auras: 18950 - Invisibility and Stealth Detection) (possible waypoints or random movement)
(@CGUID+396, 45230, 1, 1637, 0, '0', '0', 0, 0, 1, 1931.0552978515625, -4269.00439453125, 28.30804824829101562, 1.026691794395446777, 120, 10, 0, 198434, 0, 1, 0, 0, 0, 45505), -- Orgrimmar Brave (Area: 0 - Difficulty: 0) (Auras: ) (possible waypoints or random movement)
(@CGUID+397, 3296, 1, 1637, 0, '0', '0', 0, 0, 1, 1927.739990234375, -4391.97021484375, 23.32620048522949218, 0.03490658476948738, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Orgrimmar Grunt (Area: 0 - Difficulty: 0) (Auras: )
(@CGUID+398, 54004, 1, 1637, 0, '0', '0', 0, 0, 0, 1943.5035400390625, -4343.3818359375, 24.1249237060546875, 4.293509960174560546, 120, 0, 0, 27, 0, 0, 0, 0, 0, 45505), -- Jaga (Area: 0 - Difficulty: 0) (Auras: 89302 - Generic Quest Invisibility 27)
(@CGUID+399, 42548, 1, 1637, 0, '0', '0', 0, 0, 0, 1943.0972900390625, -4316.49853515625, 16.30869293212890625, 5.282872676849365234, 120, 10, 0, 132289, 0, 1, 0, 0, 0, 45505), -- Muddy Crawfish (Area: 0 - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+400, 42548, 1, 1637, 0, '0', '0', 0, 0, 0, 1968.75, -4314.515625, 14.69309616088867187, 4.694291114807128906, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Muddy Crawfish (Area: 0 - Difficulty: 0)
(@CGUID+401, 44787, 1, 1637, 0, '0', '0', 0, 0, 0, 1919.8199462890625, -4231.18994140625, 37.05063247680664062, 1.29154360294342041, 120, 0, 0, 396867, 0, 0, 0, 0, 0, 45505), -- Auctioneer Sowata (Area: 0 - Difficulty: 0)
(@CGUID+402, 176094, 1, 1637, 0, '0', '0', 0, 0, 0, 1951.657958984375, -4366.79150390625, 24.02135848999023437, 5.449243545532226562, 120, 0, 0, 84665, 7196, 0, 0, 0, 0, 45505), -- Max Catstalker (Area: 0 - Difficulty: 0)
(@CGUID+403, 176095, 1, 1637, 0, '0', '0', 0, 0, 0, 1950.4913330078125, -4369.92041015625, 23.78588485717773437, 0.27999463677406311, 120, 0, 0, 105831, 100, 0, 0, 0, 0, 45505), -- Luke Catstalker (Area: 0 - Difficulty: 0)
(@CGUID+404, 184812, 1, 1637, 0, '0', '0', 0, 0, 0, 1896.4853515625, -4232.72265625, 136.3614654541015625, 5.105566024780273437, 120, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Restless Explorer (Area: 0 - Difficulty: 0) (Auras: 371800 - -0-, 369509 - -0-)
(@CGUID+405, 42548, 1, 1637, 0, '0', '0', 0, 0, 0, 1957.37060546875, -4277.791015625, 16.61449623107910156, 4.112342357635498046, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Muddy Crawfish (Area: 0 - Difficulty: 0)
(@CGUID+406, 3296, 1, 1637, 0, '0', '0', 0, 0, 1, 1958.9000244140625, -4365.52001953125, 106.2683334350585937, 0.261799395084381103, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Orgrimmar Grunt (Area: 0 - Difficulty: 0) (Auras: )
(@CGUID+407, 3296, 1, 1637, 0, '0', '0', 0, 0, 1, 1957.68994140625, -4358.68017578125, 106.2683334350585937, 0.261799395084381103, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Orgrimmar Grunt (Area: 0 - Difficulty: 0) (Auras: )
(@CGUID+408, 42548, 1, 1637, 0, '0', '0', 0, 0, 0, 1961.931640625, -4293.6064453125, 14.41054248809814453, 2.90601205825805664, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Muddy Crawfish (Area: 0 - Difficulty: 0)
(@CGUID+409, 50088, 1, 1637, 0, '0', '0', 0, 0, 0, 2048.72216796875, -4391.4775390625, 99.131927490234375, 0, 120, 0, 0, 2758, 0, 0, 0, 0, 0, 45505), -- Waters of Farseeing (Area: 0 - Difficulty: 0)
(@CGUID+410, 176012, 1, 1637, 0, '0', '0', 0, 0, 0, 1955.2396240234375, -4369.72900390625, 23.686767578125, 2.844300746917724609, 120, 0, 0, 105831, 7196, 0, 0, 0, 0, 45505), -- Ric Catstalker (Area: 0 - Difficulty: 0)
(@CGUID+411, 44781, 1, 1637, 0, '0', '0', 0, 0, 1, 1904.1099853515625, -4211.93994140625, 37.06293106079101562, 2.827433347702026367, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Opuno Ironhorn (Area: 0 - Difficulty: 0)
(@CGUID+412, 45230, 1, 1637, 0, '0', '0', 0, 0, 1, 1930.06005859375, -4230.6298828125, 36.7061309814453125, 5.183627605438232421, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Orgrimmar Brave (Area: 0 - Difficulty: 0) (Auras: )
(@CGUID+413, 74228, 1, 1637, 0, '0', '0', 0, 0, 1, 1961.18994140625, -4390.93994140625, 28.96618270874023437, 3.089232683181762695, 120, 10, 0, 198434, 0, 1, 0, 0, 0, 45505), -- Darkspear Headhunter (Area: 0 - Difficulty: 0) (Auras: ) (possible waypoints or random movement)
(@CGUID+414, 45230, 1, 1637, 0, '0', '0', 0, 0, 1, 1941.6700439453125, -4229.8798828125, 36.5233306884765625, 4.502949237823486328, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Orgrimmar Brave (Area: 0 - Difficulty: 0) (Auras: )
(@CGUID+415, 3322, 1, 1637, 0, '0', '0', 0, 0, 1, 1908.449951171875, -4217.18994140625, 37.06913375854492187, 1.256637096405029296, 120, 0, 0, 138903, 0, 0, 0, 0, 0, 45505), -- Kaja (Area: 0 - Difficulty: 0)
(@CGUID+416, 47321, 1, 1637, 0, '0', '0', 0, 0, 1, 2029.8499755859375, -4327.33984375, 95.55423736572265625, 5.06145477294921875, 120, 0, 0, 2206, 19394, 0, 0, 0, 0, 45505), -- Zugra Flamefist (Area: 0 - Difficulty: 0) (Auras: 32783 - Arcane Channeling)
(@CGUID+417, 47335, 1, 1637, 0, '0', '0', 0, 0, 1, 2027.0899658203125, -4330.759765625, 95.5110321044921875, 4.817108631134033203, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Baradin Grunt (Area: 0 - Difficulty: 0)
(@CGUID+418, 47336, 1, 1637, 0, '0', '0', 0, 0, 1, 2034.530029296875, -4328.18994140625, 95.55423736572265625, 5.427973747253417968, 120, 0, 0, 2758, 0, 0, 0, 0, 0, 45505), -- Baradin Grunt (Area: 0 - Difficulty: 0)
(@CGUID+419, 3296, 1, 1637, 0, '0', '0', 0, 0, 1, 2002.948486328125, -4364.34814453125, 94.19234466552734375, 6.128769874572753906, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Orgrimmar Grunt (Area: 0 - Difficulty: 0) (Auras: )
(@CGUID+420, 49837, 1, 1637, 0, '0', '0', 0, 0, 0, 2006.4453125, -4266.8583984375, 94.99468231201171875, 6.258419513702392578, 120, 0, 0, 27, 0, 0, 0, 0, 0, 45505), -- Spiny Lizard (Area: 0 - Difficulty: 0)
(@CGUID+421, 3296, 1, 1637, 0, '0', '0', 0, 0, 1, 1999.9100341796875, -4369.2099609375, 93.870635986328125, 6.17846536636352539, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Orgrimmar Grunt (Area: 0 - Difficulty: 0) (Auras: )
(@CGUID+422, 49837, 1, 1637, 0, '0', '0', 0, 0, 0, 2017.2086181640625, -4280.4580078125, 96.192413330078125, 6.093770503997802734, 120, 0, 0, 27, 0, 0, 0, 0, 0, 45505), -- Spiny Lizard (Area: 0 - Difficulty: 0)
(@CGUID+423, 44779, 1, 1637, 0, '0', '0', 0, 0, 1, 1974.469970703125, -4234.240234375, 37.17523193359375, 2.268928050994873046, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Owato (Area: 0 - Difficulty: 0)
(@CGUID+424, 44780, 1, 1637, 0, '0', '0', 0, 0, 1, 1977.1500244140625, -4227.14990234375, 37.17523193359375, 3.31612563133239746, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Isashi (Area: 0 - Difficulty: 0)
-- (@CGUID+425, 62821, 0, 1637, 0, '0', '0', 0, 0, 0, -0.20000000298023223, 0, -0.20000000298023223, 0, 120, 0, 0, 158747, 10794, 0, 0, 0, 0, 45505), -- Mystic Birdhat (Area: 0 - Difficulty: 0) (Auras: 122729 - Grand Expedition Yak, 123236 - Grummle Booth A) - !!! on transport - transport template not found !!!
(@CGUID+426, 58193, 1, 1637, 0, '0', '0', 0, 0, 1, 2018.90625, -4271.486328125, 95.5316314697265625, 0.314159274101257324, 120, 0, 0, 3307225, 0, 0, 0, 0, 0, 45505), -- Wyrmrest Protector (Area: 0 - Difficulty: 0) (Auras: )
(@CGUID+427, 49743, 1, 1637, 0, '0', '0', 0, 0, 0, 2003.284912109375, -4342.04736328125, 93.54019927978515625, 0.908211231231689453, 120, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Dung Beetle (Area: 0 - Difficulty: 0)
-- (@CGUID+428, 62822, 0, 1637, 0, '0', '0', 0, 0, 0, -0.20000000298023223, 0, -0.20000000298023223, 0, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Cousin Slowhands (Area: 0 - Difficulty: 0) (Auras: 122729 - Grand Expedition Yak, 123240 - Grummle Booth B) - !!! on transport - transport template not found !!!
(@CGUID+429, 58199, 1, 1637, 0, '0', '0', 0, 0, 0, 2029.4635009765625, -4269.65966796875, 95.53729248046875, 5.497786998748779296, 120, 0, 0, 1322890, 0, 0, 0, 0, 0, 45505), -- Lord Itharius (Area: 0 - Difficulty: 0)
(@CGUID+430, 45230, 1, 1637, 0, '0', '0', 0, 0, 1, 1957.5799560546875, -4216.6201171875, 37.30613327026367187, 3.159045934677124023, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Orgrimmar Brave (Area: 0 - Difficulty: 0) (Auras: )
(@CGUID+431, 184666, 1, 1637, 0, '0', '0', 0, 0, 1, 2044.796875, -4282.97216796875, 95.5453643798828125, 2.117783069610595703, 120, 0, 0, 618760, 0, 0, 0, 0, 0, 45505), -- Mayla Highmountain (Area: 0 - Difficulty: 0) (Auras: )
(@CGUID+432, 49837, 1, 1637, 0, '0', '0', 0, 0, 0, 2048.859375, -4267.390625, 95.43766021728515625, 1.981575250625610351, 120, 0, 0, 27, 0, 0, 0, 0, 0, 45505), -- Spiny Lizard (Area: 0 - Difficulty: 0)
(@CGUID+433, 184793, 1, 1637, 0, '0', '0', 0, 0, 0, 2048.5244140625, -4274.97412109375, 95.5296173095703125, 3.681994915008544921, 120, 0, 0, 92814, 0, 0, 0, 0, 0, 45505), -- Naleidea Rivergleam (Area: 0 - Difficulty: 0) (Auras: 378042 - -0-)
(@CGUID+434, 184786, 1, 1637, 0, '0', '0', 0, 0, 0, 2043.107666015625, -4272.26025390625, 95.53094482421875, 4.502070426940917968, 120, 0, 0, 309380, 2568, 0, 0, 0, 0, 45505), -- Scalecommander Cindrethresh (Area: 0 - Difficulty: 0) (Auras: )
(@CGUID+435, 190239, 1, 1637, 0, '0', '0', 0, 0, 0, 2046.4444580078125, -4272.77783203125, 95.52838134765625, 4.30653238296508789, 120, 0, 0, 20648, 2434, 0, 0, 0, 0, 45505), -- Ebyssian (Area: 0 - Difficulty: 0) (Auras: )
(@CGUID+436, 44770, 1, 1637, 0, '0', '0', 0, 0, 1, 1950.0799560546875, -4200.31982421875, 36.99593353271484375, 3.490658521652221679, 120, 0, 0, 396867, 0, 0, 0, 0, 0, 45505), -- Tatepi (Area: 0 - Difficulty: 0)
(@CGUID+437, 184664, 1, 1637, 0, '0', '0', 0, 0, 0, 2047.85595703125, -4281.0693359375, 95.5394439697265625, 2.460927963256835937, 120, 0, 0, 928140, 0, 0, 0, 0, 0, 45505), -- Baine Bloodhoof (Area: 0 - Difficulty: 0) (Auras: )
(@CGUID+438, 49837, 1, 1637, 5171, '0', '0', 0, 0, 0, 2041.8126220703125, -4214.85498046875, 101.6393966674804687, 3.461395263671875, 120, 0, 0, 27, 0, 0, 0, 0, 0, 45505), -- Spiny Lizard (Area: Valley of Wisdom - Difficulty: 0)
(@CGUID+439, 49837, 1, 1637, 5171, '0', '0', 0, 0, 0, 2052.7705078125, -4260.4560546875, 95.44954681396484375, 4.860857009887695312, 120, 0, 0, 27, 0, 0, 0, 0, 0, 45505), -- Spiny Lizard (Area: Valley of Wisdom - Difficulty: 0)
(@CGUID+440, 49743, 1, 1637, 5171, '0', '0', 0, 0, 0, 2058.71484375, -4245.4580078125, 97.171356201171875, 2.947673320770263671, 120, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Dung Beetle (Area: Valley of Wisdom - Difficulty: 0)
(@CGUID+441, 45230, 1, 1637, 5171, '0', '0', 0, 0, 1, 1945.760009765625, -4196, 37.11663055419921875, 4.066617012023925781, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Orgrimmar Brave (Area: Valley of Wisdom - Difficulty: 0) (Auras: )
(@CGUID+442, 58193, 1, 1637, 5171, '0', '0', 0, 0, 1, 2061.057373046875, -4265.4755859375, 95.57759857177734375, 4.398229598999023437, 120, 0, 0, 3307225, 0, 0, 0, 0, 0, 45505), -- Wyrmrest Protector (Area: Valley of Wisdom - Difficulty: 0) (Auras: )
(@CGUID+443, 62115, 1, 1637, 5171, '0', '0', 0, 0, 0, 2027.4920654296875, -4232.5458984375, 96.1151885986328125, 3.184002399444580078, 120, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Dung Beetle (Area: Valley of Wisdom - Difficulty: 0)
(@CGUID+444, 51230, 1, 1637, 5171, '0', '0', 0, 0, 0, 2038.1302490234375, -4372.44091796875, 99.04035186767578125, 5.846852779388427734, 120, 0, 0, 2758, 1067, 0, 0, 0, 0, 45505), -- Earthmender (Area: Valley of Wisdom - Difficulty: 0)
(@CGUID+445, 62114, 1, 1637, 5171, '0', '0', 0, 0, 0, 2044.770751953125, -4188.5263671875, 109.262847900390625, 4.288346290588378906, 120, 0, 0, 27, 0, 0, 0, 0, 0, 45505), -- Spiny Lizard (Area: Valley of Wisdom - Difficulty: 0)
(@CGUID+446, 49743, 1, 1637, 5171, '0', '0', 0, 0, 0, 2019.660888671875, -4204.712890625, 105.7768020629882812, 6.058574199676513671, 120, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Dung Beetle (Area: Valley of Wisdom - Difficulty: 0)
(@CGUID+447, 49743, 1, 1637, 5171, '0', '0', 0, 0, 0, 2059.490478515625, -4203.599609375, 107.7250595092773437, 2.472018718719482421, 120, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Dung Beetle (Area: Valley of Wisdom - Difficulty: 0)
(@CGUID+448, 51230, 1, 1637, 5171, '0', '0', 0, 0, 0, 2050.197998046875, -4366.7744140625, 99.0231781005859375, 4.625122547149658203, 120, 0, 0, 2758, 1067, 0, 0, 0, 0, 45505), -- Earthmender (Area: Valley of Wisdom - Difficulty: 0)
(@CGUID+449, 184793, 1, 1637, 0, '0', '0', 0, 0, 0, 2048.5244140625, -4274.97412109375, 95.61295318603515625, 3.681994915008544921, 120, 0, 0, 92814, 0, 0, 0, 0, 0, 45505), -- Naleidea Rivergleam (Area: 0 - Difficulty: 0) (Auras: 378042 - -0-)
(@CGUID+450, 49743, 1, 1637, 5171, '0', '0', 0, 0, 0, 2034.7530517578125, -4176.16259765625, 109.8497161865234375, 2.889704465866088867, 120, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Dung Beetle (Area: Valley of Wisdom - Difficulty: 0)
(@CGUID+451, 44782, 1, 1637, 5171, '0', '0', 0, 0, 1, 1910.1700439453125, -4191.2998046875, 37.27473068237304687, 5.16617441177368164, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Rento (Area: Valley of Wisdom - Difficulty: 0)
(@CGUID+452, 72939, 1, 1637, 5171, '0', '0', 0, 0, 1, 1938.56005859375, -4183.41015625, 37.06303024291992187, 4.642575740814208984, 120, 0, 0, 178590, 0, 0, 0, 0, 0, 45505), -- Terga Earthbreaker (Area: Valley of Wisdom - Difficulty: 0)
(@CGUID+453, 44785, 1, 1637, 5171, '0', '0', 0, 0, 1, 1922.6099853515625, -4182.52978515625, 37.96703338623046875, 5.113814830780029296, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Miwana (Area: Valley of Wisdom - Difficulty: 0)
(@CGUID+454, 161223, 1, 1637, 5171, '0', '0', 0, 0, 0, 1944.0416259765625, -4190.97216796875, 37.12030029296875, 2.937377214431762695, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Torkhan (Area: Valley of Wisdom - Difficulty: 0) (Auras: 313952 - -0-)
(@CGUID+455, 44788, 1, 1637, 5171, '0', '0', 0, 0, 0, 1915.52001953125, -4190.4599609375, 37.06293106079101562, 4.921828269958496093, 120, 0, 0, 138903, 0, 0, 0, 0, 0, 45505), -- Lonto (Area: Valley of Wisdom - Difficulty: 0)
(@CGUID+456, 49837, 1, 1637, 5171, '0', '0', 0, 0, 0, 2024.421875, -4147.998046875, 106.18701171875, 0.01975143514573574, 120, 0, 0, 27, 0, 0, 0, 0, 0, 45505), -- Spiny Lizard (Area: Valley of Wisdom - Difficulty: 0)
(@CGUID+457, 13417, 1, 1637, 5171, '0', '0', 0, 0, 1, 1937.739990234375, -4194.02978515625, 37.1006317138671875, 1.553343057632446289, 120, 0, 0, 165361, 0, 0, 0, 0, 0, 45505), -- Sagorne Creststrider (Area: Valley of Wisdom - Difficulty: 0)
(@CGUID+458, 3403, 1, 1637, 5171, '0', '0', 0, 0, 1, 1933.43994140625, -4185.58984375, 37.45333099365234375, 5.462880611419677734, 120, 0, 0, 152132, 0, 0, 0, 0, 0, 45505), -- Sian'tsu (Area: Valley of Wisdom - Difficulty: 0)
(@CGUID+459, 133271, 1, 1637, 5171, '0', '0', 0, 0, 1, 1941.513916015625, -4183.62841796875, 37.45322418212890625, 3.444181203842163085, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Highmountain Pathfinder (Area: Valley of Wisdom - Difficulty: 0)
(@CGUID+460, 5892, 1, 1637, 5171, '0', '0', 0, 0, 1, 1932.300048828125, -4188.0400390625, 37.04493331909179687, 6.003932476043701171, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Searn Firewarder (Area: Valley of Wisdom - Difficulty: 0)
(@CGUID+461, 15188, 1, 1637, 5171, '0', '0', 0, 0, 0, 1896.1099853515625, -4200.93994140625, 37.324432373046875, 5.864306449890136718, 120, 0, 0, 1984335, 47325, 0, 0, 0, 0, 45505), -- Cenarion Emissary Blackhoof (Area: Valley of Wisdom - Difficulty: 0)
(@CGUID+462, 49837, 1, 1637, 5171, '0', '0', 0, 0, 0, 1902.4322509765625, -4198.490234375, 37.433685302734375, 2.326243162155151367, 120, 0, 0, 27, 0, 0, 0, 0, 0, 45505), -- Spiny Lizard (Area: Valley of Wisdom - Difficulty: 0)
(@CGUID+463, 49743, 1, 1637, 5171, '0', '0', 0, 0, 0, 1944.03515625, -4238.61328125, 34.62599945068359375, 5.797251224517822265, 120, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Dung Beetle (Area: Valley of Wisdom - Difficulty: 0)
(@CGUID+464, 44783, 1, 1637, 5171, '0', '0', 0, 0, 0, 1899.8199462890625, -4181.77978515625, 37.96703338623046875, 0.296705961227416992, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Hiwahi Three-Feathers (Area: Valley of Wisdom - Difficulty: 0)
(@CGUID+465, 3296, 1, 1637, 5171, '0', '0', 0, 0, 1, 1847.938720703125, -4246.4365234375, 39.96334457397460937, 6.043956756591796875, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Orgrimmar Grunt (Area: Valley of Wisdom - Difficulty: 0) (Auras: )
(@CGUID+466, 184812, 1, 1637, 5171, '0', '0', 0, 0, 0, 1845.048828125, -4187.8369140625, 150.5210418701171875, 5.201863288879394531, 120, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Restless Explorer (Area: Valley of Wisdom - Difficulty: 0) (Auras: 371800 - -0-, 369509 - -0-)
(@CGUID+467, 187711, 1, 1637, 5171, '0', '0', 0, 0, 0, 1817.095458984375, -4172.62158203125, 143.748992919921875, 6.258188247680664062, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Handhold (Area: Valley of Wisdom - Difficulty: 0) (Auras: )
(@CGUID+468, 189091, 1, 1637, 5171, '0', '0', 0, 0, 0, 1819.453125, -4178.7275390625, 147.3402252197265625, 0.011959724128246307, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Handhold (Area: Valley of Wisdom - Difficulty: 0)
(@CGUID+469, 62115, 1, 1637, 5171, '0', '0', 0, 0, 0, 1906.477783203125, -4126.88427734375, 110.1611175537109375, 1.217955708503723144, 120, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Dung Beetle (Area: Valley of Wisdom - Difficulty: 0)
(@CGUID+470, 3296, 1, 1637, 5171, '0', '0', 0, 0, 1, 1839.6961669921875, -4179.65625, 153.04583740234375, 2.590437173843383789, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Orgrimmar Grunt (Area: Valley of Wisdom - Difficulty: 0) (Auras: )
(@CGUID+471, 184796, 1, 1637, 5171, '0', '0', 0, 0, 0, 1826.3472900390625, -4177.671875, 153.4531097412109375, 4.108884811401367187, 120, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Pathfinder Tacha (Area: Valley of Wisdom - Difficulty: 0)
(@CGUID+472, 187709, 1, 1637, 5171, '0', '0', 0, 0, 0, 1816.75, -4169.13525390625, 140.593505859375, 0.147794783115386962, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Handhold (Area: Valley of Wisdom - Difficulty: 0) (Auras: )
(@CGUID+473, 3296, 1, 1637, 5171, '0', '0', 0, 0, 1, 1836.623291015625, -4176.81787109375, 154.474151611328125, 5.349128246307373046, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Orgrimmar Grunt (Area: Valley of Wisdom - Difficulty: 0) (Auras: )
(@CGUID+474, 184801, 1, 1637, 5171, '0', '0', 0, 0, 1, 1825.7413330078125, -4175.99853515625, 153.4183197021484375, 3.34790349006652832, 120, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Kenzou (Area: Valley of Wisdom - Difficulty: 0)
(@CGUID+475, 184800, 1, 1637, 5171, '0', '0', 0, 0, 1, 1827.8507080078125, -4178.07275390625, 153.81591796875, 3.635515689849853515, 120, 0, 0, 30938, 100, 0, 0, 0, 0, 45505), -- Omi (Area: Valley of Wisdom - Difficulty: 0)
(@CGUID+476, 3296, 1, 1637, 5171, '0', '0', 0, 0, 1, 1791.030029296875, -4239.4501953125, 41.0986328125, 0.645771801471710205, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Orgrimmar Grunt (Area: Valley of Wisdom - Difficulty: 0) (Auras: )
(@CGUID+477, 189091, 1, 1637, 5171, '0', '0', 0, 0, 0, 1810.4913330078125, -4166.77099609375, 127.66680908203125, 6.189778804779052734, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Handhold (Area: Valley of Wisdom - Difficulty: 0)
(@CGUID+478, 184812, 1, 1637, 5171, '0', '0', 0, 0, 0, 1805.34375, -4177.35791015625, 119.7398147583007812, 2.388741970062255859, 120, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Restless Explorer (Area: Valley of Wisdom - Difficulty: 0)
-- (@CGUID+479, 184812, 0, 1637, 5171, '0', '0', 0, 0, 0, -1.07944238185882568, -0.08654337376356124, 0.519945383071899414, 0, 120, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Restless Explorer (Area: Valley of Wisdom - Difficulty: 0) (Auras: 371800 - -0-, 371801 - -0-) - !!! on transport - transport template not found !!!
(@CGUID+480, 184812, 1, 1637, 5171, '0', '0', 0, 0, 0, 1801.1007080078125, -4154.875, 120.8067779541015625, 0, 120, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Restless Explorer (Area: Valley of Wisdom - Difficulty: 0)
(@CGUID+481, 187710, 1, 1637, 5171, '0', '0', 0, 0, 0, 1808.8992919921875, -4171.3818359375, 123.441436767578125, 0.187539801001548767, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Handhold (Area: Valley of Wisdom - Difficulty: 0)
(@CGUID+482, 187711, 1, 1637, 5171, '0', '0', 0, 0, 0, 1815.77783203125, -4164.89404296875, 135.899444580078125, 0.299243420362472534, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Handhold (Area: Valley of Wisdom - Difficulty: 0) (Auras: )
(@CGUID+483, 184812, 1, 1637, 5171, '0', '0', 0, 0, 0, 1803.5416259765625, -4154.65625, 120.92938232421875, 3.139564275741577148, 120, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Restless Explorer (Area: Valley of Wisdom - Difficulty: 0) (Auras: 371815 - -0-)
(@CGUID+484, 29143, 1, 1637, 5171, '0', '0', 0, 0, 0, 1784.0699462890625, -4208.02001953125, 40.31103134155273437, 4.450589656829833984, 120, 0, 0, 132289, 100, 0, 0, 0, 0, 45505), -- Bebri Coifcurl (Area: Valley of Wisdom - Difficulty: 0)
(@CGUID+485, 184812, 1, 1637, 5171, '0', '0', 0, 0, 0, 1805.017333984375, -4175.00341796875, 119.856964111328125, 4.175426959991455078, 120, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Restless Explorer (Area: Valley of Wisdom - Difficulty: 0) (Auras: 371815 - -0-)
(@CGUID+486, 184812, 1, 1637, 5171, '0', '0', 0, 0, 0, 1797.1771240234375, -4157.75, 120.4986190795898437, 0.162083014845848083, 120, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Restless Explorer (Area: Valley of Wisdom - Difficulty: 0)
(@CGUID+487, 184812, 1, 1637, 5171, '0', '0', 0, 0, 0, 1799.1927490234375, -4157.42041015625, 120.5660324096679687, 3.30367588996887207, 120, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Restless Explorer (Area: Valley of Wisdom - Difficulty: 0) (Auras: 371815 - -0-)
(@CGUID+488, 49837, 1, 1637, 0, '0', '0', 0, 0, 0, 1806.263427734375, -4120.88134765625, 123.8018035888671875, 0.3485012948513031, 120, 0, 0, 27, 0, 0, 0, 0, 0, 45505), -- Spiny Lizard (Area: 0 - Difficulty: 0)
(@CGUID+489, 49743, 1, 1637, 0, '0', '0', 0, 0, 0, 1791.0587158203125, -4159.1669921875, 120.2454071044921875, 1.551103591918945312, 120, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Dung Beetle (Area: 0 - Difficulty: 0)
-- (@CGUID+490, 62821, 0, 1637, 0, '0', '0', 0, 0, 0, -0.20000000298023223, 0, -0.20000000298023223, 0, 120, 0, 0, 158747, 10794, 0, 0, 0, 0, 45505), -- Mystic Birdhat (Area: 0 - Difficulty: 0) (Auras: 122729 - Grand Expedition Yak, 123236 - Grummle Booth A) - !!! on transport - transport template not found !!!
-- (@CGUID+491, 62822, 0, 1637, 0, '0', '0', 0, 0, 0, -0.20000000298023223, 0, -0.20000000298023223, 0, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Cousin Slowhands (Area: 0 - Difficulty: 0) (Auras: 122729 - Grand Expedition Yak, 123240 - Grummle Booth B) - !!! on transport - transport template not found !!!
(@CGUID+492, 3296, 1, 1637, 0, '0', '0', 0, 0, 1, 1836.623291015625, -4176.81787109375, 154.5574798583984375, 5.349128246307373046, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Orgrimmar Grunt (Area: 0 - Difficulty: 0) (Auras: )
(@CGUID+493, 179897, 1, 1637, 0, '0', '0', 0, 0, 0, 1777.1319580078125, -4217.50341796875, 40.94379806518554687, 5.080800056457519531, 120, 0, 0, 105831, 7196, 0, 0, 0, 0, 45505), -- Ca'nees (Area: 0 - Difficulty: 0)
(@CGUID+494, 62114, 1, 1637, 0, '0', '0', 0, 0, 0, 1804.5460205078125, -4101.240234375, 126.1707534790039062, 0.640110015869140625, 120, 0, 0, 27, 0, 0, 0, 0, 0, 45505), -- Spiny Lizard (Area: 0 - Difficulty: 0)
(@CGUID+495, 74228, 1, 1637, 0, '0', '0', 0, 0, 1, 1745.0799560546875, -4197.10986328125, 51.95073318481445312, 4.642575740814208984, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Darkspear Headhunter (Area: 0 - Difficulty: 0) (Auras: )
(@CGUID+496, 184800, 1, 1637, 0, '0', '0', 0, 0, 1, 1827.8507080078125, -4178.07275390625, 153.8992462158203125, 3.635515689849853515, 120, 0, 0, 30938, 100, 0, 0, 0, 0, 45505), -- Omi (Area: 0 - Difficulty: 0)
(@CGUID+497, 184801, 1, 1637, 0, '0', '0', 0, 0, 1, 1825.7413330078125, -4175.99853515625, 153.50164794921875, 3.34790349006652832, 120, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Kenzou (Area: 0 - Difficulty: 0)
(@CGUID+498, 3404, 1, 1637, 0, '0', '0', 0, 0, 1, 1758.030029296875, -4112.259765625, 51.78143310546875, 2.408554315567016601, 120, 0, 0, 145518, 0, 0, 0, 0, 0, 45505), -- Jandi (Area: 0 - Difficulty: 0)
(@CGUID+499, 3405, 1, 1637, 0, '0', '0', 0, 0, 1, 1753.6500244140625, -4112.35986328125, 51.71129608154296875, 1.867502331733703613, 120, 0, 0, 138903, 0, 0, 0, 0, 0, 45505); -- Zeal'aya (Area: 0 - Difficulty: 0)

INSERT INTO `creature` (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnDifficulties`, `PhaseId`, `PhaseGroup`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `wander_distance`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`, `VerifiedBuild`) VALUES
(@CGUID+500, 184796, 1, 1637, 0, '0', '0', 0, 0, 0, 1826.3472900390625, -4177.671875, 153.53643798828125, 4.108884811401367187, 120, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Pathfinder Tacha (Area: 0 - Difficulty: 0)
(@CGUID+501, 3296, 1, 1637, 0, '0', '0', 0, 0, 1, 1760.15625, -4257.38916015625, 133.1902313232421875, 3.839724302291870117, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Orgrimmar Grunt (Area: 0 - Difficulty: 0) (Auras: )
(@CGUID+502, 44160, 1, 1637, 0, '0', '0', 0, 0, 0, 1749.010009765625, -4264.740234375, 101.914337158203125, 4.590215682983398437, 120, 0, 0, 1914, 0, 0, 0, 0, 0, 45505), -- Suspicious Peon (Area: 0 - Difficulty: 0)
(@CGUID+503, 34765, 1, 1637, 0, '0', '0', 0, 0, 1, 1736.5364990234375, -4254.71728515625, 133.19049072265625, 5.427973747253417968, 120, 0, 0, 2297, 0, 0, 0, 0, 0, 45505), -- Zelli Hotnozzle (Area: 0 - Difficulty: 0)
(@CGUID+504, 7010, 1, 1637, 0, '0', '0', 0, 0, 1, 1841.4000244140625, -4464.68017578125, 47.72103118896484375, 2.94960641860961914, 120, 0, 0, 116414, 7196, 0, 0, 0, 0, 45505), -- Zilzibin Drumlore (Area: 0 - Difficulty: 0)
(@CGUID+505, 49743, 1, 1637, 0, '0', '0', 0, 0, 0, 1877.618896484375, -4430.62744140625, 109.8187789916992187, 1.547707676887512207, 120, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Dung Beetle (Area: 0 - Difficulty: 0)
(@CGUID+506, 49743, 1, 1637, 0, '0', '0', 0, 0, 0, 1824.8531494140625, -4444.61767578125, 106.5075759887695312, 0.510211884975433349, 120, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Dung Beetle (Area: 0 - Difficulty: 0)
(@CGUID+507, 3372, 1, 1637, 0, '0', '0', 0, 0, 0, 1845.77001953125, -4472.5, 56.39583206176757812, 4.450589656829833984, 120, 0, 0, 138903, 0, 0, 0, 0, 0, 45505), -- Sarlek (Area: 0 - Difficulty: 0)
(@CGUID+508, 3371, 1, 1637, 0, '0', '0', 0, 0, 0, 1844.949951171875, -4475.4599609375, 56.41413116455078125, 1.274090290069580078, 120, 0, 0, 138903, 0, 0, 0, 0, 0, 45505), -- Tamaro (Area: 0 - Difficulty: 0)
(@CGUID+509, 46742, 1, 1637, 0, '0', '0', 0, 0, 1, 1902.510009765625, -4456.830078125, 53.49833297729492187, 2.39110112190246582, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Brunda (Area: 0 - Difficulty: 0)
(@CGUID+510, 49743, 1, 1637, 0, '0', '0', 0, 0, 0, 1863.0152587890625, -4439.09423828125, 109.77801513671875, 3.340777158737182617, 120, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Dung Beetle (Area: 0 - Difficulty: 0)
(@CGUID+511, 46741, 1, 1637, 0, '0', '0', 0, 0, 1, 1900.800048828125, -4463.85009765625, 53.43439865112304687, 3.967051267623901367, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Muraga (Area: 0 - Difficulty: 0)
(@CGUID+512, 3296, 1, 1637, 0, '0', '0', 0, 0, 1, 1885.0899658203125, -4470.830078125, 23.26653480529785156, 5.113814830780029296, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Orgrimmar Grunt (Area: 0 - Difficulty: 0) (Auras: )
-- (@CGUID+513, 62821, 0, 1637, 0, '0', '0', 0, 0, 0, -0.20000000298023223, 0, -0.20000000298023223, 0, 120, 0, 0, 158747, 10794, 0, 0, 0, 0, 45505), -- Mystic Birdhat (Area: 0 - Difficulty: 0) (Auras: 122729 - Grand Expedition Yak, 123236 - Grummle Booth A) - !!! on transport - transport template not found !!!
-- (@CGUID+514, 62822, 0, 1637, 0, '0', '0', 0, 0, 0, -0.20000000298023223, 0, -0.20000000298023223, 0, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Cousin Slowhands (Area: 0 - Difficulty: 0) (Auras: 122729 - Grand Expedition Yak, 123240 - Grummle Booth B) - !!! on transport - transport template not found !!!
(@CGUID+515, 197679, 1, 1637, 0, '0', '0', 0, 0, 1, 1857.921875, -4495.45654296875, 23.90436553955078125, 2.704936504364013671, 120, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Shuga Blastcaps (Area: 0 - Difficulty: 0)
(@CGUID+516, 197680, 1, 1637, 0, '0', '0', 0, 0, 1, 1859.4132080078125, -4492.5400390625, 23.90436553955078125, 2.188175201416015625, 120, 0, 0, 309380, 0, 0, 0, 0, 0, 45505), -- Jack the Hammer (Area: 0 - Difficulty: 0) (Auras: 296495 - -0-)
(@CGUID+517, 3296, 1, 1637, 0, '0', '0', 0, 0, 1, 1896.8499755859375, -4470.85986328125, 23.61293411254882812, 4.468042850494384765, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Orgrimmar Grunt (Area: 0 - Difficulty: 0) (Auras: )
(@CGUID+518, 3296, 1, 1637, 0, '0', '0', 0, 0, 1, 1871.248291015625, -4493.94775390625, 23.64376449584960937, 4.31719827651977539, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Orgrimmar Grunt (Area: 0 - Difficulty: 0) (Auras: )
(@CGUID+519, 3296, 1, 1637, 0, '0', '0', 0, 0, 1, 1853.77001953125, -4527.02001953125, 24.466400146484375, 2.0245819091796875, 120, 10, 0, 198434, 0, 1, 0, 0, 0, 45505), -- Orgrimmar Grunt (Area: 0 - Difficulty: 0) (Auras: ) (possible waypoints or random movement)
(@CGUID+520, 4953, 1, 1637, 0, '0', '0', 0, 0, 0, 1875.922119140625, -4493.7314453125, 23.33468818664550781, 3.899201869964599609, 120, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Water Snake (Area: 0 - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+521, 42548, 1, 1637, 0, '0', '0', 0, 0, 0, 1840.4566650390625, -4511.39306640625, 23.72379112243652343, 2.855802774429321289, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Muddy Crawfish (Area: 0 - Difficulty: 0)
(@CGUID+522, 3345, 1, 1637, 0, '0', '0', 0, 0, 1, 1912.0035400390625, -4436.75537109375, 24.87609291076660156, 2.862339973449707031, 120, 0, 0, 145518, 0, 0, 0, 0, 0, 45505), -- Godan (Area: 0 - Difficulty: 0)
(@CGUID+523, 184787, 1, 1637, 0, '0', '0', 0, 0, 0, 1859.1927490234375, -4499.30908203125, 23.90436744689941406, 4.438096046447753906, 120, 0, 0, 92814, 0, 0, 0, 0, 0, 45505), -- Boss Magor (Area: 0 - Difficulty: 0)
(@CGUID+524, 42548, 1, 1637, 0, '0', '0', 0, 0, 0, 1880.0380859375, -4485.0146484375, 22.74533271789550781, 2.885756969451904296, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Muddy Crawfish (Area: 0 - Difficulty: 0)
(@CGUID+525, 197682, 1, 1637, 0, '0', '0', 0, 0, 0, 1863.10595703125, -4494.84912109375, 23.90436744689941406, 4.901748180389404296, 120, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Enchantress Quinni (Area: 0 - Difficulty: 0)
(@CGUID+526, 3296, 1, 1637, 0, '0', '0', 0, 0, 1, 1869.1458740234375, -4497.423828125, 23.69157600402832031, 0.733060657978057861, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Orgrimmar Grunt (Area: 0 - Difficulty: 0) (Auras: )
(@CGUID+527, 190535, 1, 1637, 0, '0', '0', 0, 0, 0, 1856.7569580078125, -4494.77587890625, 24.5209808349609375, 5.742427349090576171, 120, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Quizla Blastcaps (Area: 0 - Difficulty: 0) (Auras: 374211 - -0-)
(@CGUID+528, 62196, 1, 1637, 0, '0', '0', 0, 0, 1, 1888.095458984375, -4550.53466796875, 30.41864013671875, 6.261966228485107421, 120, 0, 0, 132289, 3155, 0, 0, 0, 0, 45505), -- Flekky Nox (Area: 0 - Difficulty: 0) (Auras: 79865 - Frost Armor)
(@CGUID+529, 62197, 1, 1637, 0, '0', '0', 0, 0, 1, 1890.435791015625, -4550.6162109375, 30.473388671875, 3.161437511444091796, 120, 0, 0, 132289, 3155, 0, 0, 0, 0, 45505), -- Zazzle (Area: 0 - Difficulty: 0) (Auras: 94218 - Grit's Flamethrower Backpack)
(@CGUID+530, 3346, 1, 1637, 0, '0', '0', 0, 0, 0, 1919.1700439453125, -4434.08984375, 24.88133430480957031, 2.094395160675048828, 120, 0, 0, 145518, 0, 0, 0, 0, 0, 45505), -- Kithas (Area: 0 - Difficulty: 0)
(@CGUID+531, 46181, 1, 1637, 0, '0', '0', 0, 0, 1, 1918.18994140625, -4432.3798828125, 24.91533470153808593, 5.201081275939941406, 120, 0, 0, 317493, 21588, 0, 0, 0, 0, 45505), -- Enchanter Farendin (Area: 0 - Difficulty: 0)
(@CGUID+532, 3296, 1, 1637, 0, '0', '0', 0, 0, 1, 1915.6068115234375, -4481.17578125, 25.29152870178222656, 2.546637773513793945, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Orgrimmar Grunt (Area: 0 - Difficulty: 0) (Auras: )
(@CGUID+533, 11066, 1, 1637, 0, '0', '0', 0, 0, 1, 1912.3800048828125, -4430.72998046875, 24.872833251953125, 4.014257431030273437, 120, 0, 0, 138903, 0, 0, 0, 0, 0, 45505), -- Jhag (Area: 0 - Difficulty: 0)
(@CGUID+534, 3321, 1, 1637, 0, '0', '0', 0, 0, 0, 1839.9791259765625, -4552.51025390625, 24.63405418395996093, 1.692969322204589843, 120, 0, 0, 138903, 0, 0, 0, 0, 0, 45505), -- Morgum (Area: 0 - Difficulty: 0)
(@CGUID+535, 3366, 1, 1637, 0, '0', '0', 0, 0, 1, 1856.9722900390625, -4555.94775390625, 25.06409835815429687, 3.892084121704101562, 120, 0, 0, 138903, 0, 0, 0, 0, 0, 45505), -- Tamar (Area: 0 - Difficulty: 0) (Auras: )
(@CGUID+536, 3296, 1, 1637, 5167, '0', '0', 0, 0, 1, 1914.719970703125, -4555.93017578125, 36.035430908203125, 3.700098037719726562, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Orgrimmar Grunt (Area: The Drag - Difficulty: 0) (Auras: )
(@CGUID+537, 3348, 1, 1637, 5167, '0', '0', 0, 0, 1, 1955.1400146484375, -4467.10009765625, 26.00103378295898437, 3.752457857131958007, 120, 0, 0, 138903, 0, 0, 0, 0, 0, 45505), -- Kor'geld (Area: The Drag - Difficulty: 0)
(@CGUID+538, 3347, 1, 1637, 5167, '0', '0', 0, 0, 1, 1956.239990234375, -4474.93994140625, 25.95720672607421875, 2.862339973449707031, 120, 0, 0, 145518, 0, 0, 0, 0, 0, 45505), -- Yelmak (Area: The Drag - Difficulty: 0)
(@CGUID+539, 3351, 1, 1637, 5167, '0', '0', 0, 0, 1, 1947.6300048828125, -4501.06005859375, 27.68583488464355468, 2.426007747650146484, 120, 0, 0, 138903, 0, 0, 0, 0, 0, 45505), -- Magenius (Area: The Drag - Difficulty: 0) (Auras: )
(@CGUID+540, 8659, 1, 1637, 5167, '0', '0', 0, 0, 1, 1954.888916015625, -4459.5068359375, 54.99825668334960937, 2.652900457382202148, 120, 0, 0, 165361, 100, 0, 0, 0, 0, 45505), -- Jes'rimon (Area: The Drag - Difficulty: 0)
(@CGUID+541, 5811, 1, 1637, 5167, '0', '0', 0, 0, 1, 1847.7257080078125, -4565.61474609375, 25.06409835815429687, 0.01745329238474369, 120, 0, 0, 138903, 0, 0, 0, 0, 0, 45505), -- Kamari (Area: The Drag - Difficulty: 0) (Auras: )
(@CGUID+542, 3225, 1, 1637, 5167, '0', '0', 0, 0, 0, 1852.279541015625, -4572.8994140625, 25.06409835815429687, 5.393067359924316406, 120, 0, 0, 1914, 0, 0, 0, 0, 0, 45505), -- Corrupted Mottled Boar (Area: The Drag - Difficulty: 0) (Auras: 65985 - Permanent Feign Death (Root Silence Pacify))
(@CGUID+543, 3296, 1, 1637, 5167, '0', '0', 0, 0, 1, 1905.8499755859375, -4562.08984375, 36.035430908203125, 0.575958669185638427, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Orgrimmar Grunt (Area: The Drag - Difficulty: 0) (Auras: )
(@CGUID+544, 7088, 1, 1637, 5167, '0', '0', 0, 0, 1, 1852.907958984375, -4570.05908203125, 25.06409835815429687, 4.555309295654296875, 120, 0, 0, 145518, 0, 0, 0, 0, 0, 45505), -- Thuwd (Area: The Drag - Difficulty: 0) (Auras: )
(@CGUID+545, 6986, 1, 1637, 5167, '0', '0', 0, 0, 1, 1932.3333740234375, -4516.34033203125, 29.3632354736328125, 3.40339207649230957, 120, 0, 0, 158747, 0, 0, 0, 0, 0, 45505), -- Dran Droffers (Area: The Drag - Difficulty: 0) (Auras: )
(@CGUID+546, 6987, 1, 1637, 5167, '0', '0', 0, 0, 1, 1928.767333984375, -4518.77783203125, 29.3632354736328125, 0.959931075572967529, 120, 0, 0, 152132, 0, 0, 0, 0, 0, 45505), -- Malton Droffers (Area: The Drag - Difficulty: 0) (Auras: )
(@CGUID+547, 188169, 1, 1637, 5167, '0', '0', 0, 0, 0, 1834.4913330078125, -4565.91650390625, 25.05693435668945312, 0, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Worker (Area: The Drag - Difficulty: 0) (Auras: 221098 - Sleeping Sleep)
(@CGUID+548, 3350, 1, 1637, 5167, '0', '0', 0, 0, 1, 1942.25, -4499.4501953125, 27.59177398681640625, 2.007128715515136718, 120, 10, 0, 138903, 0, 1, 0, 0, 0, 45505), -- Asoran (Area: The Drag - Difficulty: 0) (Auras: ) (possible waypoints or random movement)
(@CGUID+549, 3316, 1, 1637, 5167, '0', '0', 0, 0, 0, 1863.6597900390625, -4565.51220703125, 25.06409835815429687, 3.298672199249267578, 120, 0, 0, 138903, 0, 0, 0, 0, 0, 45505), -- Handor (Area: The Drag - Difficulty: 0) (Auras: )
(@CGUID+550, 3365, 1, 1637, 5167, '0', '0', 0, 0, 0, 1850.1822509765625, -4565.55224609375, 25.06409835815429687, 3.193952560424804687, 120, 0, 0, 145518, 0, 0, 0, 0, 0, 45505), -- Karolek (Area: The Drag - Difficulty: 0) (Auras: )
(@CGUID+551, 1420, 1, 1637, 5167, '0', '0', 0, 0, 0, 1881.2049560546875, -4489.45166015625, 23.25778388977050781, 2.162006616592407226, 120, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Toad (Area: The Drag - Difficulty: 0)
(@CGUID+552, 49837, 1, 1637, 5167, '0', '0', 0, 0, 0, 1843.004638671875, -4578.26123046875, 86.0833740234375, 4.587958335876464843, 120, 10, 0, 27, 0, 1, 0, 0, 0, 45505), -- Spiny Lizard (Area: The Drag - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+553, 61369, 1, 1637, 5167, '0', '0', 0, 0, 0, 1844.72021484375, -4514.06884765625, 24.12210845947265625, 1.860680460929870605, 120, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Toad (Area: The Drag - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+554, 3296, 1, 1637, 5167, '0', '0', 0, 0, 1, 1871.248291015625, -4493.94775390625, 23.72709846496582031, 4.31719827651977539, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Orgrimmar Grunt (Area: The Drag - Difficulty: 0) (Auras: )
(@CGUID+555, 2855, 1, 1637, 5167, '0', '0', 0, 0, 1, 1809.5699462890625, -4574.22998046875, 22.99802207946777343, 5.306100368499755859, 120, 10, 0, 134935, 0, 1, 0, 0, 0, 45505), -- Snang (Area: The Drag - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+556, 3296, 1, 1637, 5167, '0', '0', 0, 0, 1, 1935.72998046875, -4559.58984375, 66.534637451171875, 0.453785598278045654, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Orgrimmar Grunt (Area: The Drag - Difficulty: 0) (Auras: )
(@CGUID+557, 153285, 1, 1637, 5167, '0', '0', 0, 0, 0, 1925.126708984375, -4569.1337890625, 68.1976318359375, 5.98647928237915039, 120, 0, 0, 13228900, 0, 0, 0, 0, 0, 45505), -- Training Dummy (Area: The Drag - Difficulty: 0) (Auras: 98892 - Training Dummy Marker, 61573 - Banner of the Alliance)
(@CGUID+558, 197679, 1, 1637, 5167, '0', '0', 0, 0, 1, 1857.921875, -4495.45654296875, 23.98769950866699218, 2.704936504364013671, 120, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Shuga Blastcaps (Area: The Drag - Difficulty: 0)
(@CGUID+559, 197680, 1, 1637, 5167, '0', '0', 0, 0, 1, 1859.4132080078125, -4492.5400390625, 23.98769950866699218, 2.188175201416015625, 120, 0, 0, 309380, 0, 0, 0, 0, 0, 45505), -- Jack the Hammer (Area: The Drag - Difficulty: 0) (Auras: 296495 - -0-)
(@CGUID+560, 184787, 1, 1637, 5167, '0', '0', 0, 0, 0, 1859.1927490234375, -4499.30908203125, 23.987701416015625, 4.438096046447753906, 120, 0, 0, 92814, 0, 0, 0, 0, 0, 45505), -- Boss Magor (Area: The Drag - Difficulty: 0)
(@CGUID+561, 197682, 1, 1637, 5167, '0', '0', 0, 0, 0, 1863.10595703125, -4494.84912109375, 23.987701416015625, 4.901748180389404296, 120, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Enchantress Quinni (Area: The Drag - Difficulty: 0)
(@CGUID+562, 190535, 1, 1637, 5167, '0', '0', 0, 0, 0, 1856.7569580078125, -4494.77587890625, 24.60431480407714843, 5.742427349090576171, 120, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Quizla Blastcaps (Area: The Drag - Difficulty: 0) (Auras: 374211 - -0-)
(@CGUID+563, 49837, 1, 1637, 5167, '0', '0', 0, 0, 0, 1846.0625, -4612.5185546875, 86.0192108154296875, 0.129831776022911071, 120, 10, 0, 27, 0, 1, 0, 0, 0, 45505), -- Spiny Lizard (Area: The Drag - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+564, 3296, 1, 1637, 5167, '0', '0', 0, 0, 1, 1904.0111083984375, -4602.0947265625, 35.95209884643554687, 3.735928058624267578, 120, 10, 0, 198434, 0, 1, 0, 0, 0, 45505), -- Orgrimmar Grunt (Area: The Drag - Difficulty: 0) (Auras: ) (possible waypoints or random movement)
(@CGUID+565, 3296, 1, 1637, 5167, '0', '0', 0, 0, 1, 1938.6700439453125, -4558.60009765625, 66.53473663330078125, 3.490658521652221679, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Orgrimmar Grunt (Area: The Drag - Difficulty: 0) (Auras: )
(@CGUID+566, 3296, 1, 1637, 5167, '0', '0', 0, 0, 1, 1889.719970703125, -4611.89990234375, 66.415435791015625, 0.663225114345550537, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Orgrimmar Grunt (Area: The Drag - Difficulty: 0) (Auras: )
(@CGUID+567, 153285, 1, 1637, 5167, '0', '0', 0, 0, 0, 1899.9097900390625, -4623.2119140625, 66.5340423583984375, 2.146754980087280273, 120, 0, 0, 13228900, 0, 0, 0, 0, 0, 45505), -- Training Dummy (Area: The Drag - Difficulty: 0) (Auras: )
(@CGUID+568, 31146, 1, 1637, 5167, '0', '0', 0, 0, 0, 1955.185791015625, -4559.703125, 66.53455352783203125, 3.804817676544189453, 120, 0, 0, 185204600, 0, 0, 0, 0, 0, 45505), -- Raider's Training Dummy (Area: The Drag - Difficulty: 0) (Auras: )
(@CGUID+569, 31146, 1, 1637, 5167, '0', '0', 0, 0, 0, 1959.4583740234375, -4565.86474609375, 66.53436279296875, 3.735004663467407226, 120, 0, 0, 185204600, 0, 0, 0, 0, 0, 45505), -- Raider's Training Dummy (Area: The Drag - Difficulty: 0) (Auras: 98892 - Training Dummy Marker, 61573 - Banner of the Alliance)
(@CGUID+570, 153285, 1, 1637, 5167, '0', '0', 0, 0, 0, 1914.826416015625, -4613.47900390625, 66.53199005126953125, 2.234021425247192382, 120, 0, 0, 13228900, 0, 0, 0, 0, 0, 45505), -- Training Dummy (Area: The Drag - Difficulty: 0) (Auras: )
(@CGUID+571, 153285, 1, 1637, 5167, '0', '0', 0, 0, 0, 1905.0364990234375, -4619.86474609375, 66.52356719970703125, 2.146754980087280273, 120, 0, 0, 13228900, 0, 0, 0, 0, 0, 45505), -- Training Dummy (Area: The Drag - Difficulty: 0) (Auras: 98892 - Training Dummy Marker, 61573 - Banner of the Alliance)
(@CGUID+572, 72559, 1, 1637, 5167, '0', '0', 0, 0, 1, 1913.6180419921875, -4611.6318359375, 66.4293212890625, 5.358160972595214843, 120, 0, 0, 4137, 0, 0, 0, 0, 0, 45505), -- Thunder Bluff Protector (Area: The Drag - Difficulty: 0) (Auras: )
(@CGUID+573, 153285, 1, 1637, 5167, '0', '0', 0, 0, 0, 1910.07470703125, -4616.6630859375, 66.53116607666015625, 2.146754980087280273, 120, 0, 0, 13228900, 0, 0, 0, 0, 0, 45505), -- Training Dummy (Area: The Drag - Difficulty: 0) (Auras: 98892 - Training Dummy Marker, 61573 - Banner of the Alliance)
(@CGUID+574, 62114, 1, 1637, 5167, '0', '0', 0, 0, 0, 1845.921142578125, -4616.57763671875, 85.9921722412109375, 4.022623062133789062, 120, 10, 0, 27, 0, 1, 0, 0, 0, 45505), -- Spiny Lizard (Area: The Drag - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+575, 74228, 1, 1637, 5167, '0', '0', 0, 0, 1, 1916.5999755859375, -4631.77978515625, 36.035430908203125, 3.735004663467407226, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Darkspear Headhunter (Area: The Drag - Difficulty: 0) (Auras: )
(@CGUID+576, 31146, 1, 1637, 5167, '0', '0', 0, 0, 0, 1963.0052490234375, -4571.25341796875, 66.5341949462890625, 3.630284786224365234, 120, 0, 0, 185204600, 0, 0, 0, 0, 0, 45505), -- Raider's Training Dummy (Area: The Drag - Difficulty: 0) (Auras: 98892 - Training Dummy Marker, 61573 - Banner of the Alliance)
(@CGUID+577, 4953, 1, 1637, 5167, '0', '0', 0, 0, 0, 1975.5230712890625, -4602.19384765625, 36.44805145263671875, 4.906217575073242187, 120, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Water Snake (Area: The Drag - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+578, 49837, 1, 1637, 5167, '0', '0', 0, 0, 0, 1932.5306396484375, -4637.154296875, 33.31078338623046875, 4.762725830078125, 120, 10, 0, 27, 0, 1, 0, 0, 0, 45505), -- Spiny Lizard (Area: The Drag - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+579, 161203, 1, 1637, 5167, '0', '0', 0, 0, 0, 1935.6131591796875, -4635.73681640625, 33.0948028564453125, 5.22383737564086914, 120, 10, 0, 132289, 0, 1, 0, 0, 0, 45505), -- River (Area: The Drag - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+580, 49837, 1, 1637, 5167, '0', '0', 0, 0, 0, 1828.2930908203125, -4631.2861328125, 89.0324859619140625, 6.187243938446044921, 120, 10, 0, 27, 0, 1, 0, 0, 0, 45505), -- Spiny Lizard (Area: The Drag - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+581, 49750, 1, 1637, 5167, '0', '0', 0, 0, 1, 1916.1129150390625, -4666.28125, 34.25650405883789062, 0.279252678155899047, 120, 0, 0, 5742, 0, 0, 0, 0, 0, 45505), -- Warchief's Herald (Area: The Drag - Difficulty: 0)
(@CGUID+582, 42548, 1, 1637, 5167, '0', '0', 0, 0, 0, 1973.596923828125, -4597.8935546875, 35.73958587646484375, 2.603150606155395507, 120, 10, 0, 132289, 0, 1, 0, 0, 0, 45505), -- Muddy Crawfish (Area: The Drag - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+583, 49837, 1, 1637, 5167, '0', '0', 0, 0, 0, 1898.5101318359375, -4657.201171875, 36.25708770751953125, 0.451552093029022216, 120, 0, 0, 27, 0, 0, 0, 0, 0, 45505), -- Spiny Lizard (Area: The Drag - Difficulty: 0)
(@CGUID+584, 62114, 1, 1637, 5167, '0', '0', 0, 0, 0, 1935.4534912109375, -4652.75146484375, 33.41286468505859375, 4.685870170593261718, 120, 10, 0, 27, 0, 1, 0, 0, 0, 45505), -- Spiny Lizard (Area: The Drag - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+585, 160452, 1, 1637, 5167, '0', '0', 0, 0, 0, 1947.3211669921875, -4630.83837890625, 34.31444549560546875, 2.804193496704101562, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Nilsa (Area: The Drag - Difficulty: 0)
(@CGUID+586, 49743, 1, 1637, 5167, '0', '0', 0, 0, 0, 1938.590576171875, -4629.36767578125, 34.13811111450195312, 2.93672037124633789, 120, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Dung Beetle (Area: The Drag - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+587, 3296, 1, 1637, 5167, '0', '0', 0, 0, 1, 1907.5, -4637.9599609375, 36.035430908203125, 0.593411922454833984, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Orgrimmar Grunt (Area: The Drag - Difficulty: 0) (Auras: )
(@CGUID+588, 46621, 1, 1637, 5167, '0', '0', 0, 0, 0, 1875.199951171875, -4672.83984375, 39.06473159790039062, 4.677482128143310546, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Pank (Area: The Drag - Difficulty: 0) (Auras: )
(@CGUID+589, 3359, 1, 1637, 5167, '0', '0', 0, 0, 0, 1898.2708740234375, -4669.11474609375, 35.37531280517578125, 6.17846536636352539, 120, 0, 0, 138903, 0, 0, 0, 0, 0, 45505), -- Kiro (Area: The Drag - Difficulty: 0)
-- (@CGUID+590, 152561, 0, 1637, 5167, '0', '0', 0, 0, 0, -0.00705206487327814, 0.007241555489599704, 3.027451276779174804, 0, 120, 0, 0, 20592, 0, 0, 0, 0, 0, 45505), -- Hyper-Compressed Ocean Target (Area: The Drag - Difficulty: 0) (Auras: 46598 - Ride Vehicle Hardcoded) - !!! on transport - transport template not found !!!
(@CGUID+591, 158789, 1, 1637, 5167, '0', '0', 0, 0, 0, 1907.4288330078125, -4664.6025390625, 34.860565185546875, 5.472680091857910156, 120, 0, 0, 132289, 3155, 0, 0, 0, 0, 45505), -- Thex (Area: The Drag - Difficulty: 0)
(@CGUID+592, 3296, 1, 1637, 5167, '0', '0', 0, 0, 1, 1872.02001953125, -4676.330078125, 38.58443069458007812, 5.672319889068603515, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Orgrimmar Grunt (Area: The Drag - Difficulty: 0) (Auras: )
(@CGUID+593, 46620, 1, 1637, 5167, '0', '0', 0, 0, 0, 1867.6800537109375, -4677.759765625, 39.1956329345703125, 0, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Vink (Area: The Drag - Difficulty: 0) (Auras: )
(@CGUID+594, 46622, 1, 1637, 5167, '0', '0', 0, 0, 1, 1876.696044921875, -4682.0302734375, 35.55994796752929687, 6.160448551177978515, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Vuvanzi (Area: The Drag - Difficulty: 0)
(@CGUID+595, 3296, 1, 1637, 5167, '0', '0', 0, 0, 1, 1904.87255859375, -4683.90869140625, 38.59177780151367187, 0.129205435514450073, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Orgrimmar Grunt (Area: The Drag - Difficulty: 0) (Auras: )
(@CGUID+596, 180684, 1, 1637, 5167, '0', '0', 0, 0, 0, 1985.420166015625, -4606.890625, 38.56592559814453125, 4.824874401092529296, 120, 0, 0, 99, 0, 0, 0, 0, 0, 45505), -- Olive (Area: The Drag - Difficulty: 0)
(@CGUID+597, 42548, 1, 1637, 5167, '0', '0', 0, 0, 0, 1964.4447021484375, -4652.87646484375, 26.28212547302246093, 3.124461174011230468, 120, 10, 0, 132289, 0, 1, 0, 0, 0, 45505), -- Muddy Crawfish (Area: The Drag - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+598, 4953, 1, 1637, 5167, '0', '0', 0, 0, 0, 1980.092041015625, -4602.7392578125, 36.5160064697265625, 4.956894397735595703, 120, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Water Snake (Area: The Drag - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+599, 62193, 1, 1637, 5167, '0', '0', 0, 0, 1, 1968.6163330078125, -4660.15478515625, 32.79130935668945312, 1.078697443008422851, 120, 0, 0, 132289, 3155, 0, 0, 0, 0, 45505), -- Rok'kal (Area: The Drag - Difficulty: 0) (Auras: 116562 - Fishing)
(@CGUID+600, 42548, 1, 1637, 5167, '0', '0', 0, 0, 0, 1987.4141845703125, -4640.384765625, 18.78774070739746093, 4.790925502777099609, 120, 10, 0, 132289, 0, 1, 0, 0, 0, 45505), -- Muddy Crawfish (Area: The Drag - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+601, 46618, 1, 1637, 5167, '0', '0', 0, 0, 0, 1875.25, -4690.419921875, 39.04693222045898437, 1.570796370506286621, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Fibi (Area: The Drag - Difficulty: 0) (Auras: )
(@CGUID+602, 3296, 1, 1637, 5167, '0', '0', 0, 0, 1, 1871.1300048828125, -4687.06982421875, 38.59243392944335937, 0.820304751396179199, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Orgrimmar Grunt (Area: The Drag - Difficulty: 0) (Auras: )
(@CGUID+603, 49743, 1, 1637, 5167, '0', '0', 0, 0, 0, 1826.35498046875, -4636.0732421875, 89.771514892578125, 4.581789970397949218, 120, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Dung Beetle (Area: The Drag - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+604, 46619, 1, 1637, 5167, '0', '0', 0, 0, 0, 1867.56005859375, -4684.77001953125, 39.15643310546875, 6.230825424194335937, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Binzella (Area: The Drag - Difficulty: 0) (Auras: )
(@CGUID+605, 62114, 1, 1637, 5167, '0', '0', 0, 0, 0, 1837.5482177734375, -4686.9208984375, 104.604949951171875, 1.600977778434753417, 120, 10, 0, 27, 0, 1, 0, 0, 0, 45505), -- Spiny Lizard (Area: The Drag - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+606, 3296, 1, 1637, 5167, '0', '0', 0, 0, 1, 1930.3785400390625, -4725.8212890625, 36.05551910400390625, 1.403896570205688476, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Orgrimmar Grunt (Area: The Drag - Difficulty: 0) (Auras: )
(@CGUID+607, 46642, 1, 1637, 5167, '0', '0', 0, 0, 1, 1907.3004150390625, -4746.57275390625, 38.6134796142578125, 0.831709980964660644, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Innkeeper Nufa (Area: The Drag - Difficulty: 0)
(@CGUID+608, 3296, 1, 1637, 5167, '0', '0', 0, 0, 1, 1931.5225830078125, -4722.720703125, 35.99286651611328125, 4.096959590911865234, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Orgrimmar Grunt (Area: The Drag - Difficulty: 0) (Auras: )
(@CGUID+609, 42548, 1, 1637, 5167, '0', '0', 0, 0, 0, 1977.4857177734375, -4709.154296875, 22.74675941467285156, 5.463887214660644531, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Muddy Crawfish (Area: The Drag - Difficulty: 0)
(@CGUID+610, 42638, 1, 1637, 5167, '0', '0', 0, 0, 0, 1897.4757080078125, -4741.72900390625, 39.01667022705078125, 4.625122547149658203, 120, 0, 0, 1914, 0, 0, 0, 0, 0, 45505), -- Herezegor Flametusk (Area: The Drag - Difficulty: 0)
(@CGUID+611, 3332, 1, 1637, 5167, '0', '0', 0, 0, 1, 2000.46533203125, -4662.0712890625, 28.57512855529785156, 1.500983119010925292, 120, 0, 0, 145518, 0, 0, 0, 0, 0, 45505), -- Lumak (Area: The Drag - Difficulty: 0)
(@CGUID+612, 62114, 1, 1637, 5167, '0', '0', 0, 0, 0, 1842.99755859375, -4711.19873046875, 115.8793487548828125, 3.293615579605102539, 120, 10, 0, 27, 0, 1, 0, 0, 0, 45505), -- Spiny Lizard (Area: The Drag - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+613, 42548, 1, 1637, 5167, '0', '0', 0, 0, 0, 2000.93994140625, -4631.43408203125, 21.9348297119140625, 5.584285736083984375, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Muddy Crawfish (Area: The Drag - Difficulty: 0)
(@CGUID+614, 62114, 1, 1637, 5167, '0', '0', 0, 0, 0, 1916.89794921875, -4770.173828125, 37.17268753051757812, 4.48907327651977539, 120, 0, 0, 27, 0, 0, 0, 0, 0, 45505), -- Spiny Lizard (Area: The Drag - Difficulty: 0)
(@CGUID+615, 176261, 1, 1637, 5167, '0', '0', 0, 0, 0, 1900.171875, -4756.984375, 46.13097381591796875, 5.95241403579711914, 120, 0, 0, 2993, 0, 0, 0, 0, 0, 45505), -- Barra the Quick (Area: The Drag - Difficulty: 0)
(@CGUID+616, 184797, 1, 1637, 5167, '0', '0', 0, 0, 0, 1897.6805419921875, -4750.97412109375, 46.13046646118164062, 1.389263033866882324, 120, 0, 0, 24750, 6015, 0, 0, 0, 0, 45505), -- Lorewalker Lali (Area: The Drag - Difficulty: 0)
(@CGUID+617, 42548, 1, 1637, 5167, '0', '0', 0, 0, 0, 2003.3565673828125, -4677.6572265625, 29.47059822082519531, 0.709427952766418457, 120, 10, 0, 132289, 0, 1, 0, 0, 0, 45505), -- Muddy Crawfish (Area: The Drag - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+618, 42709, 1, 1637, 5167, '0', '0', 0, 0, 0, 1903.1649169921875, -4756.53125, 39.012176513671875, 1.01229095458984375, 120, 0, 0, 1914, 0, 0, 0, 0, 0, 45505), -- Gravy (Area: The Drag - Difficulty: 0)
(@CGUID+619, 3333, 1, 1637, 5167, '0', '0', 0, 0, 1, 2001.361083984375, -4667.46728515625, 28.57512474060058593, 0.069813169538974761, 120, 0, 0, 138903, 0, 0, 0, 0, 0, 45505), -- Shankys (Area: The Drag - Difficulty: 0)
(@CGUID+620, 49743, 1, 1637, 5167, '0', '0', 0, 0, 0, 1894.556884765625, -4724.28076171875, 39.22309112548828125, 0.197658717632293701, 120, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Dung Beetle (Area: The Drag - Difficulty: 0)
(@CGUID+621, 175084, 1, 1637, 5167, '0', '0', 0, 0, 0, 1904.345458984375, -4758.01904296875, 46.13068771362304687, 2.649031400680541992, 120, 0, 0, 2993, 0, 0, 0, 0, 0, 45505), -- Lando'sal (Area: The Drag - Difficulty: 0)
(@CGUID+622, 35845, 1, 1637, 5167, '0', '0', 0, 0, 0, 1915.4583740234375, -4734.32275390625, 39.01977157592773437, 1.01229095458984375, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Dave's Industrial Light and Magic Bunny (Small)(Sessile) (Area: The Drag - Difficulty: 0)
(@CGUID+623, 184795, 1, 1637, 5167, '0', '0', 0, 0, 0, 1899.501708984375, -4749.16650390625, 46.1301422119140625, 3.297562360763549804, 120, 0, 0, 30938, 2568, 0, 0, 0, 0, 45505), -- Cataloger Kieule (Area: The Drag - Difficulty: 0)
(@CGUID+624, 184798, 1, 1637, 5167, '0', '0', 0, 0, 1, 1896.23095703125, -4747.423828125, 46.13079071044921875, 0, 120, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Chronicler Laz'Kini (Area: The Drag - Difficulty: 0)
(@CGUID+625, 65076, 1, 1637, 5168, '0', '0', 0, 0, 0, 1998.4166259765625, -4720.98095703125, 26.96154212951660156, 3.840173959732055664, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Great Brown Dragon Turtle (Area: Valley of Honor - Difficulty: 0)
(@CGUID+626, 65078, 1, 1637, 5168, '0', '0', 0, 0, 0, 2005.313720703125, -4717.9423828125, 29.53586578369140625, 5.563714504241943359, 120, 10, 0, 132289, 0, 1, 0, 0, 0, 45505), -- Great Purple Dragon Turtle (Area: Valley of Honor - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+627, 153285, 1, 1637, 5168, '0', '0', 0, 0, 0, 1942.69970703125, -4771.390625, 57.8877410888671875, 5.302379608154296875, 120, 0, 0, 13228900, 0, 0, 0, 0, 0, 45505), -- Training Dummy (Area: Valley of Honor - Difficulty: 0) (Auras: 98892 - Training Dummy Marker, 61573 - Banner of the Alliance)
(@CGUID+628, 66022, 1, 1637, 5168, '0', '0', 0, 0, 0, 2009.267333984375, -4721.24853515625, 29.59772109985351562, 1.031698465347290039, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Turtlemaster Odai (Area: Valley of Honor - Difficulty: 0)
(@CGUID+629, 168621, 1, 1637, 5168, '0', '0', 0, 0, 1, 1942.6944580078125, -4769.8837890625, 39.19588470458984375, 5.44761514663696289, 120, 0, 0, 142872, 7196, 0, 0, 0, 0, 45505), -- Martin Goodchilde (Area: Valley of Honor - Difficulty: 0)
(@CGUID+630, 7951, 1, 1637, 5168, '0', '0', 0, 0, 1, 2012.2257080078125, -4680.1181640625, 28.30364799499511718, 1.780235767364501953, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Zas'Tysh (Area: Valley of Honor - Difficulty: 0)
(@CGUID+631, 169166, 1, 1637, 5168, '0', '0', 0, 0, 0, 1969.6285400390625, -4767.3037109375, 39.125762939453125, 4.160536766052246093, 120, 0, 0, 118, 0, 0, 0, 0, 0, 45505), -- Provisioner Jin'hake (Area: Valley of Honor - Difficulty: 0)
(@CGUID+632, 168597, 1, 1637, 5168, '0', '0', 0, 0, 1, 1936.75, -4779.24853515625, 39.19588851928710937, 0, 120, 0, 0, 178590, 3155, 0, 0, 0, 0, 45505), -- Avaros Dawnglaive (Area: Valley of Honor - Difficulty: 0) (Auras: 79976 - Retribution Aura)
(@CGUID+633, 42548, 1, 1637, 5168, '0', '0', 0, 0, 0, 2006.4881591796875, -4728.09521484375, 28.12136077880859375, 4.709587574005126953, 120, 10, 0, 132289, 0, 1, 0, 0, 0, 45505), -- Muddy Crawfish (Area: Valley of Honor - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+634, 70301, 1, 1637, 5168, '0', '0', 0, 0, 0, 2010.890625, -4722.8662109375, 29.42734146118164062, 0.383237391710281372, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Softpaws (Area: Valley of Honor - Difficulty: 0)
(@CGUID+635, 49743, 1, 1637, 5168, '0', '0', 0, 0, 0, 1932.7802734375, -4748.49658203125, 37.50825881958007812, 1.470384716987609863, 120, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Dung Beetle (Area: Valley of Honor - Difficulty: 0)
(@CGUID+636, 153285, 1, 1637, 5168, '0', '0', 0, 0, 0, 1935.5989990234375, -4778.23095703125, 57.8879852294921875, 5.302379608154296875, 120, 0, 0, 13228900, 0, 0, 0, 0, 0, 45505), -- Training Dummy (Area: Valley of Honor - Difficulty: 0) (Auras: 98892 - Training Dummy Marker, 61573 - Banner of the Alliance)
(@CGUID+637, 15186, 1, 1637, 5168, '0', '0', 0, 0, 0, 2013.859375, -4680.1875, 28.40093803405761718, 1.93731546401977539, 120, 0, 0, 27, 0, 0, 0, 0, 0, 45505), -- Murky (Area: Valley of Honor - Difficulty: 0) (Auras: 24983 - Baby Murloc Passive)
(@CGUID+638, 168596, 1, 1637, 5168, '0', '0', 0, 0, 1, 1940.18408203125, -4789.30712890625, 39.19588851928710937, 0.653445959091186523, 120, 0, 0, 178590, 0, 0, 0, 0, 0, 45505), -- Gormok Ogrefist (Area: Valley of Honor - Difficulty: 0)
(@CGUID+639, 65071, 1, 1637, 5168, '0', '0', 0, 0, 0, 1994.4251708984375, -4726.56640625, 25.62939643859863281, 5.468535423278808593, 120, 10, 0, 132289, 0, 1, 0, 0, 0, 45505), -- Great Green Dragon Turtle (Area: Valley of Honor - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+640, 3296, 1, 1637, 5168, '0', '0', 0, 0, 1, 1930.3785400390625, -4725.8212890625, 36.13885116577148437, 1.403896570205688476, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Orgrimmar Grunt (Area: Valley of Honor - Difficulty: 0) (Auras: )
(@CGUID+641, 46667, 1, 1637, 5168, '0', '0', 0, 0, 1, 1952.607666015625, -4801.8369140625, 58.2175140380859375, 4.648665428161621093, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Blademaster Ronakada (Area: Valley of Honor - Difficulty: 0) (Auras: 79064 - Horde Banner)
(@CGUID+642, 65074, 1, 1637, 5168, '0', '0', 0, 0, 0, 2009.5086669921875, -4732.73291015625, 27.37105178833007812, 3.83367466926574707, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Great Blue Dragon Turtle (Area: Valley of Honor - Difficulty: 0)
(@CGUID+643, 168553, 1, 1637, 5168, '0', '0', 0, 0, 1, 1985.37158203125, -4774.75, 39.19588851928710937, 3.910434722900390625, 120, 0, 0, 178590, 3155, 0, 0, 0, 0, 45505), -- Telotha Pinegrove (Area: Valley of Honor - Difficulty: 0)
(@CGUID+644, 34955, 1, 1637, 5168, '0', '0', 0, 0, 1, 1957.5260009765625, -4806.6025390625, 84.3666839599609375, 5.619960308074951171, 120, 0, 0, 6614450, 0, 0, 0, 0, 0, 45505), -- Karg Skullgore (Area: Valley of Honor - Difficulty: 0)
(@CGUID+645, 49573, 1, 1637, 5168, '0', '0', 0, 0, 1, 1960.5867919921875, -4808.90966796875, 84.3666839599609375, 2.478367567062377929, 120, 0, 0, 5291550, 359800, 0, 0, 0, 0, 45505), -- Karba Blazemaw (Area: Valley of Honor - Difficulty: 0) (Auras: 12544 - Frost Armor)
(@CGUID+646, 3354, 1, 1637, 5168, '0', '0', 0, 0, 1, 1950.2552490234375, -4806.9931640625, 58.21931076049804687, 0.959908723831176757, 120, 0, 0, 165361, 0, 0, 0, 0, 0, 45505), -- Sorek (Area: Valley of Honor - Difficulty: 0)
(@CGUID+647, 65008, 1, 1637, 5168, '0', '0', 0, 0, 0, 2022.2413330078125, -4712.98779296875, 28.75003433227539062, 2.629947185516357421, 120, 0, 0, 1914, 0, 0, 0, 0, 0, 45505), -- Huojin Monk (Area: Valley of Honor - Difficulty: 0)
(@CGUID+648, 35364, 1, 1637, 5168, '0', '0', 0, 0, 1, 1972.6180419921875, -4798.15625, 84.3666839599609375, 3.525565147399902343, 120, 0, 0, 324093, 100, 0, 0, 0, 0, 45505), -- Slahtz (Area: Valley of Honor - Difficulty: 0)
(@CGUID+649, 168628, 1, 1637, 5168, '0', '0', 0, 0, 1, 1986.9375, -4783.2275390625, 39.19588851928710937, 3.1147308349609375, 120, 0, 0, 178590, 3155, 0, 0, 0, 0, 45505), -- Hretar Riverspeaker (Area: Valley of Honor - Difficulty: 0) (Auras: 79892 - Water Shield)
(@CGUID+650, 168551, 1, 1637, 5168, '0', '0', 0, 0, 1, 1981.095458984375, -4791.67724609375, 39.19588851928710937, 1.94215548038482666, 120, 0, 0, 178590, 0, 0, 0, 0, 0, 45505), -- Tamanji (Area: Valley of Honor - Difficulty: 0)
(@CGUID+651, 13842, 1, 1637, 5168, '0', '0', 0, 0, 1, 1973.050048828125, -4793.8798828125, 39.19593048095703125, 2.007128715515136718, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Frostwolf Ambassador Rokhstrom (Area: Valley of Honor - Difficulty: 0)
(@CGUID+652, 62445, 1, 1637, 5168, '0', '0', 0, 0, 0, 2023.1771240234375, -4704.49462890625, 28.58363914489746093, 2.697362422943115234, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Ji Firepaw (Area: Valley of Honor - Difficulty: 0)
(@CGUID+653, 171689, 1, 1637, 5168, '0', '0', 0, 0, 0, 1978.795166015625, -4785.30712890625, 38.85229110717773437, 4.481142520904541015, 120, 0, 0, 178590, 0, 0, 0, 0, 0, 45505), -- Nathoka Bloodfang (Area: Valley of Honor - Difficulty: 0)
(@CGUID+654, 3296, 1, 1637, 5168, '0', '0', 0, 0, 1, 2013.25, -4724.89013671875, 29.24913406372070312, 1.378810048103332519, 120, 0, 0, 198434, 0, 0, 0, 0, 0, 45505), -- Orgrimmar Grunt (Area: Valley of Honor - Difficulty: 0) (Auras: )
(@CGUID+655, 153285, 1, 1637, 5168, '0', '0', 0, 0, 0, 1984.40283203125, -4774.23095703125, 57.8973388671875, 3.887519598007202148, 120, 0, 0, 13228900, 0, 0, 0, 0, 0, 45505), -- Training Dummy (Area: Valley of Honor - Difficulty: 0) (Auras: 61573 - Banner of the Alliance, 98892 - Training Dummy Marker)
(@CGUID+656, 68869, 1, 1637, 5168, '0', '0', 0, 0, 0, 2018.892333984375, -4702.828125, 28.65670394897460937, 1.337966203689575195, 120, 0, 0, 27, 0, 0, 0, 0, 0, 45505), -- Luo Luo (Area: Valley of Honor - Difficulty: 0) (Auras: 19231 - Panda)
(@CGUID+657, 3353, 1, 1637, 5168, '0', '0', 0, 0, 1, 1953.6007080078125, -4807.359375, 58.21784591674804687, 1.429387211799621582, 120, 0, 0, 178590, 0, 0, 0, 0, 0, 45505), -- Grezz Ragefist (Area: Valley of Honor - Difficulty: 0)
(@CGUID+658, 153285, 1, 1637, 5168, '0', '0', 0, 0, 0, 1988.75, -4780.11279296875, 57.8973388671875, 4.120785713195800781, 120, 0, 0, 13228900, 0, 0, 0, 0, 0, 45505), -- Training Dummy (Area: Valley of Honor - Difficulty: 0) (Auras: 98892 - Training Dummy Marker, 61573 - Banner of the Alliance)
(@CGUID+659, 65008, 1, 1637, 5168, '0', '0', 0, 0, 0, 2017.8819580078125, -4711.01904296875, 28.90924072265625, 5.843567848205566406, 120, 0, 0, 1914, 0, 0, 0, 0, 0, 45505), -- Huojin Monk (Area: Valley of Honor - Difficulty: 0)
(@CGUID+660, 168623, 1, 1637, 5168, '0', '0', 0, 0, 1, 1936.7742919921875, -4804.111328125, 39.19588470458984375, 5.535372734069824218, 120, 0, 0, 142872, 7196, 0, 0, 0, 0, 45505), -- Kazak Darkscream (Area: Valley of Honor - Difficulty: 0)
(@CGUID+661, 65065, 1, 1637, 5168, '0', '0', 0, 0, 0, 2016.3824462890625, -4750.8193359375, 25.56546974182128906, 1.195510029792785644, 120, 0, 0, 2758, 0, 0, 0, 0, 0, 45505), -- Red Dragon Turtle (Area: Valley of Honor - Difficulty: 0)
(@CGUID+662, 69333, 1, 1637, 5168, '0', '0', 0, 0, 1, 2020.4288330078125, -4699.125, 28.59227943420410156, 6.155805110931396484, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Disciple Jusi (Area: Valley of Honor - Difficulty: 0)
(@CGUID+663, 46985, 1, 1637, 5168, '0', '0', 0, 0, 0, 1952.421875, -4804.74853515625, 58.21883010864257812, 4.625122547149658203, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- [DNT] Generic Target Bunny (Area: Valley of Honor - Difficulty: 0)
(@CGUID+664, 31146, 1, 1637, 5168, '0', '0', 0, 0, 0, 1935.6875, -4823.9599609375, 57.8973388671875, 0.788360118865966796, 120, 0, 0, 185204600, 0, 0, 0, 0, 0, 45505), -- Raider's Training Dummy (Area: Valley of Honor - Difficulty: 0) (Auras: 98892 - Training Dummy Marker, 61573 - Banner of the Alliance)
(@CGUID+665, 171691, 1, 1637, 5168, '0', '0', 0, 0, 0, 1955.576416015625, -4816.8193359375, 39.091217041015625, 2.812179803848266601, 120, 0, 0, 178590, 0, 0, 0, 0, 0, 45505), -- Alpheus Cain (Area: Valley of Honor - Difficulty: 0)
(@CGUID+666, 153285, 1, 1637, 5168, '0', '0', 0, 0, 0, 1931.5364990234375, -4820.767578125, 57.8973388671875, 1.324450135231018066, 120, 0, 0, 13228900, 0, 0, 0, 0, 0, 45505), -- Training Dummy (Area: Valley of Honor - Difficulty: 0) (Auras: 98892 - Training Dummy Marker, 61573 - Banner of the Alliance)
(@CGUID+667, 168626, 1, 1637, 5168, '0', '0', 0, 0, 1, 1981.201416015625, -4805.51025390625, 39.195892333984375, 4.23126983642578125, 120, 0, 0, 142872, 7196, 0, 0, 0, 0, 45505), -- Feenix Arcshine (Area: Valley of Honor - Difficulty: 0) (Auras: 79849 - Molten Armor)
(@CGUID+668, 168598, 1, 1637, 5168, '0', '0', 0, 0, 1, 1935.8367919921875, -4818.9287109375, 39.19588470458984375, 0.90503692626953125, 120, 0, 0, 178590, 100, 0, 0, 0, 0, 45505), -- Thega Graveblade (Area: Valley of Honor - Difficulty: 0)
(@CGUID+669, 153285, 1, 1637, 5168, '0', '0', 0, 0, 0, 1938.484375, -4827.7724609375, 57.8973388671875, 0.226893350481986999, 120, 0, 0, 13228900, 0, 0, 0, 0, 0, 45505), -- Training Dummy (Area: Valley of Honor - Difficulty: 0) (Auras: 98892 - Training Dummy Marker, 61573 - Banner of the Alliance)
(@CGUID+670, 184795, 1, 1637, 8621, '0', '0', 0, 0, 0, 1899.501708984375, -4749.16650390625, 46.21347427368164062, 2.311077594757080078, 120, 0, 0, 30938, 2568, 0, 0, 0, 0, 45505), -- Cataloger Kieule (Area: -0- - Difficulty: 0)
(@CGUID+671, 184797, 1, 1637, 8621, '0', '0', 0, 0, 0, 1897.6805419921875, -4750.97412109375, 46.21379852294921875, 1.389263033866882324, 120, 0, 0, 24750, 6015, 0, 0, 0, 0, 45505), -- Lorewalker Lali (Area: -0- - Difficulty: 0)
(@CGUID+672, 184798, 1, 1637, 8621, '0', '0', 0, 0, 1, 1896.23095703125, -4747.423828125, 46.21412277221679687, 0, 120, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Chronicler Laz'Kini (Area: -0- - Difficulty: 0)
(@CGUID+673, 43239, 1, 1637, 5168, '0', '0', 0, 0, 1, 2010.300048828125, -4648.93017578125, 28.53823471069335937, 3.455751895904541015, 120, 0, 0, 145518, 0, 0, 0, 0, 0, 45505), -- Razgar (Area: Valley of Honor - Difficulty: 0)
(@CGUID+674, 49743, 1, 1637, 0, '0', '0', 0, 0, 0, 1754.4031982421875, -4575.3955078125, 98.1407623291015625, 3.134184122085571289, 120, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Dung Beetle (Area: 0 - Difficulty: 0)
(@CGUID+675, 62115, 1, 1637, 5167, '0', '0', 0, 0, 0, 1658.14111328125, -4497.71630859375, 95.84789276123046875, 3.227351665496826171, 120, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Dung Beetle (Area: The Drag - Difficulty: 0)
(@CGUID+676, 40891, 1, 1637, 0, '0', '0', 0, 0, 0, 1431.203125, -4660.890625, 35.722381591796875, 0.208417922258377075, 120, 0, 0, 1914, 0, 0, 0, 0, 0, 45505), -- Dranosh'ar Laborer (Area: 0 - Difficulty: 0)
(@CGUID+677, 40891, 1, 1637, 0, '0', '0', 0, 0, 0, 1415.5069580078125, -4652.2412109375, 35.19838333129882812, 5.131268024444580078, 120, 0, 0, 1914, 0, 0, 0, 0, 0, 45505), -- Dranosh'ar Laborer (Area: 0 - Difficulty: 0)
(@CGUID+678, 71100, 1, 1637, 0, '0', '0', 0, 0, 1, 1416.796875, -4655.55224609375, 38.40125656127929687, 3.412110567092895507, 120, 0, 0, 276, 0, 0, 0, 0, 0, 45505), -- Underpaid Engineer (Area: 0 - Difficulty: 0)
(@CGUID+679, 40891, 1, 1637, 0, '0', '0', 0, 0, 0, 1412.3992919921875, -4657.17529296875, 35.0973968505859375, 0.405246824026107788, 120, 0, 0, 1914, 0, 0, 0, 0, 0, 45505), -- Dranosh'ar Laborer (Area: 0 - Difficulty: 0)
(@CGUID+680, 3197, 1, 14, 817, '0', '0', 0, 0, 1, 1486.3914794921875, -4750.70947265625, 8.957477569580078125, 4.822737693786621093, 120, 10, 0, 1914, 852, 1, 0, 0, 0, 45505), -- Burning Blade Fanatic (Area: Skull Rock - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+681, 100663, 1, 14, 817, '0', '0', 0, 0, 0, 1392.4566650390625, -4728.92529296875, 29.28268814086914062, 2.255516290664672851, 120, 0, 0, 5443, 0, 0, 0, 0, 0, 45505), -- Sen'jin Villager (Area: Skull Rock - Difficulty: 0)
-- (@CGUID+682, 184807, 0, 14, 817, '0', '0', 0, 0, 0, 21.346771240234375, -0.52653843164443969, 4.566155433654785156, 3.041264533996582031, 120, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- The Defiant Dragonscale (Area: Skull Rock - Difficulty: 0) - !!! on transport - transport template not found !!!
(@CGUID+683, 4311, 1, 14, 817, '0', '0', 0, 0, 1, 1322.1163330078125, -4395.15625, 25.83328437805175781, 2.298407554626464843, 120, 0, 0, 5715, 0, 0, 0, 0, 0, 45505), -- Holgar Stormaxe (Area: Skull Rock - Difficulty: 0)
(@CGUID+684, 3198, 1, 14, 817, '0', '0', 0, 0, 1, 1422.8040771484375, -4741.63427734375, 2.086278200149536132, 2.063915729522705078, 120, 10, 0, 1531, 2175, 1, 0, 0, 0, 45505), -- Burning Blade Apprentice (Area: Skull Rock - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+685, 3198, 1, 14, 817, '0', '0', 0, 0, 1, 1460.739013671875, -4717.8330078125, -2.53377389907836914, 5.094307899475097656, 120, 10, 0, 1531, 2175, 1, 0, 0, 0, 45505), -- Burning Blade Apprentice (Area: Skull Rock - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+686, 3197, 1, 14, 817, '0', '0', 0, 0, 1, 1483.6246337890625, -4732.8203125, -2.81463193893432617, 5.485886573791503906, 120, 10, 0, 1914, 852, 1, 0, 0, 0, 45505), -- Burning Blade Fanatic (Area: Skull Rock - Difficulty: 0) (possible waypoints or random movement)
-- (@CGUID+687, 184286, 0, 14, 817, '0', '0', 0, 0, 1, 13.50767040252685546, -0.1015472412109375, 34.94892501831054687, 3.305320262908935546, 120, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Captain Caspartine (Area: Skull Rock - Difficulty: 0) (Auras: 372498 - -0-) - !!! on transport - transport template not found !!!
(@CGUID+688, 3197, 1, 14, 817, '0', '0', 0, 0, 1, 1503.6939697265625, -4681.06689453125, 12.46898269653320312, 1.670261979103088378, 120, 10, 0, 1914, 852, 1, 0, 0, 0, 45505), -- Burning Blade Fanatic (Area: Skull Rock - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+689, 100502, 1, 14, 817, '0', '0', 0, 0, 0, 1394.625, -4742.15283203125, 29.062774658203125, 4.694327831268310546, 120, 0, 0, 5443, 0, 0, 0, 0, 0, 45505), -- Concerned Citizen (Area: Skull Rock - Difficulty: 0)
(@CGUID+690, 3197, 1, 14, 817, '0', '0', 0, 0, 1, 1425.6226806640625, -4704.75927734375, -1.8028116226196289, 6.164172649383544921, 120, 10, 0, 1914, 852, 1, 0, 0, 0, 45505), -- Burning Blade Fanatic (Area: Skull Rock - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+691, 3198, 1, 14, 817, '0', '0', 0, 0, 1, 1524.4764404296875, -4700.21826171875, 11.10800647735595703, 5.571674346923828125, 120, 10, 0, 1531, 2175, 1, 0, 0, 0, 45505), -- Burning Blade Apprentice (Area: Skull Rock - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+692, 3198, 1, 14, 817, '0', '0', 0, 0, 1, 1449.20556640625, -4687.75830078125, -5.38782310485839843, 6.208623886108398437, 120, 10, 0, 1531, 2175, 1, 0, 0, 0, 45505), -- Burning Blade Apprentice (Area: Skull Rock - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+693, 3204, 1, 14, 817, '0', '0', 0, 0, 1, 1496.7332763671875, -4744.52294921875, 18.40007591247558593, 0.720967054367065429, 120, 10, 0, 1531, 2175, 1, 0, 0, 0, 45505), -- Gazz'uz (Area: Skull Rock - Difficulty: 0) (Auras: 20798 - Demon Skin) (possible waypoints or random movement)
(@CGUID+694, 3197, 1, 14, 817, '0', '0', 0, 0, 1, 1450.8831787109375, -4739.5205078125, -1.97778308391571044, 0.597437679767608642, 120, 10, 0, 1914, 852, 1, 0, 0, 0, 45505), -- Burning Blade Fanatic (Area: Skull Rock - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+695, 3197, 1, 14, 817, '0', '0', 0, 0, 1, 1509.148193359375, -4733.177734375, 14.60222816467285156, 5.991121768951416015, 120, 10, 0, 1914, 852, 1, 0, 0, 0, 45505), -- Burning Blade Fanatic (Area: Skull Rock - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+696, 3127, 1, 14, 817, '0', '0', 0, 0, 0, 1435.6854248046875, -4745.005859375, 33.32684707641601562, 5.911384105682373046, 120, 10, 0, 1914, 0, 1, 0, 0, 0, 45505), -- Venomtail Scorpid (Area: Skull Rock - Difficulty: 0) (possible waypoints or random movement)
-- (@CGUID+697, 197611, 0, 14, 817, '0', '0', 0, 0, 0, 10.09525203704833984, -0.01989407092332839, 34.86106109619140625, 0, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- (Bunny) Sessile + Gigantic AOI (Area: Skull Rock - Difficulty: 0) - !!! on transport - transport template not found !!!
(@CGUID+698, 5822, 1, 14, 817, '0', '0', 0, 0, 1, 1470.186767578125, -4695.2880859375, 6.530092716217041015, 4.15388345718383789, 120, 0, 0, 2871, 1704, 0, 0, 0, 0, 45505), -- Felweaver Scornn (Area: Skull Rock - Difficulty: 0) (Auras: 79934 - Demon Armor)
(@CGUID+699, 100679, 1, 14, 817, '0', '0', 0, 0, 0, 1419.71533203125, -4816.35791015625, 20.26388931274414062, 3.63524794578552246, 120, 0, 0, 5443, 0, 0, 0, 0, 0, 45505), -- Citizen of Kezan (Area: Skull Rock - Difficulty: 0)
(@CGUID+700, 62116, 1, 14, 817, '0', '0', 0, 0, 0, 1424.6151123046875, -4760.953125, 29.50067520141601562, 2.449069976806640625, 120, 10, 0, 1, 0, 1, 0, 0, 0, 45505), -- Creepy Crawly (Area: Skull Rock - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+701, 100682, 1, 14, 817, '0', '0', 0, 0, 0, 1417.8992919921875, -4816.4130859375, 20.26388931274414062, 5.497325420379638671, 120, 0, 0, 5443, 0, 0, 0, 0, 0, 45505), -- Silvermoon Citizen (Area: Skull Rock - Difficulty: 0)
(@CGUID+702, 3198, 1, 14, 817, '0', '0', 0, 0, 1, 1481.288330078125, -4776.4306640625, 5.94380044937133789, 1.064269781112670898, 120, 10, 0, 1531, 2175, 1, 0, 0, 0, 45505), -- Burning Blade Apprentice (Area: Skull Rock - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+703, 3197, 1, 14, 817, '0', '0', 0, 0, 1, 1466.3804931640625, -4805.427734375, 11.12401390075683593, 5.867664813995361328, 120, 10, 0, 1914, 852, 1, 0, 0, 0, 45505), -- Burning Blade Fanatic (Area: Skull Rock - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+704, 100664, 1, 14, 817, '0', '0', 0, 0, 0, 1360.498291015625, -4720.28125, 28.3014373779296875, 1.294256806373596191, 120, 0, 0, 5443, 0, 0, 0, 0, 0, 45505), -- Thunder Bluff Native (Area: Skull Rock - Difficulty: 0)
(@CGUID+705, 100502, 1, 14, 817, '0', '0', 0, 0, 0, 1370.28125, -4765.81787109375, 27.15451431274414062, 5.427757740020751953, 120, 0, 0, 5443, 0, 0, 0, 0, 0, 45505), -- Concerned Citizen (Area: Skull Rock - Difficulty: 0)
(@CGUID+706, 100679, 1, 14, 817, '0', '0', 0, 0, 0, 1360.498291015625, -4718.10400390625, 28.34027862548828125, 3.635247707366943359, 120, 0, 0, 5443, 0, 0, 0, 0, 0, 45505), -- Citizen of Kezan (Area: Skull Rock - Difficulty: 0)
(@CGUID+707, 3100, 1, 14, 817, '0', '0', 0, 0, 0, 1440.429931640625, -4793.728515625, 29.54688835144042968, 1.936427235603332519, 120, 10, 0, 1914, 0, 1, 0, 0, 0, 45505), -- Elder Mottled Boar (Area: Skull Rock - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+708, 100682, 1, 14, 817, '0', '0', 0, 0, 0, 1371.236083984375, -4767.640625, 26.97916793823242187, 1.864340066909790039, 120, 0, 0, 5443, 0, 0, 0, 0, 0, 45505), -- Silvermoon Citizen (Area: Skull Rock - Difficulty: 0)
(@CGUID+709, 100663, 1, 14, 817, '0', '0', 0, 0, 0, 1358.6805419921875, -4718.15966796875, 28.289306640625, 5.497325420379638671, 120, 0, 0, 5443, 0, 0, 0, 0, 0, 45505), -- Sen'jin Villager (Area: Skull Rock - Difficulty: 0)
(@CGUID+710, 5951, 1, 14, 817, '0', '0', 0, 0, 0, 1450.28125, -4766.44775390625, 35.38848114013671875, 0.868871986865997314, 120, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Hare (Area: Skull Rock - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+711, 3197, 1, 14, 817, '0', '0', 0, 0, 1, 1520.1429443359375, -4777.595703125, 9.978816986083984375, 1.075734138488769531, 120, 0, 0, 1914, 852, 0, 0, 0, 0, 45505), -- Burning Blade Fanatic (Area: Skull Rock - Difficulty: 0)
(@CGUID+712, 100664, 1, 14, 817, '0', '0', 0, 0, 0, 1419.484375, -4818.60791015625, 19.83225059509277343, 1.294256806373596191, 120, 0, 0, 5443, 0, 0, 0, 0, 0, 45505), -- Thunder Bluff Native (Area: Skull Rock - Difficulty: 0)
(@CGUID+713, 3198, 1, 14, 817, '0', '0', 0, 0, 1, 1530.131103515625, -4751.1630859375, 13.91964244842529296, 0.849450588226318359, 120, 0, 0, 1531, 2175, 0, 0, 0, 0, 45505), -- Burning Blade Apprentice (Area: Skull Rock - Difficulty: 0)
(@CGUID+714, 3198, 1, 14, 817, '0', '0', 0, 0, 1, 1491.0714111328125, -4821.38818359375, 8.769270896911621093, 3.891985893249511718, 120, 0, 0, 1531, 2175, 0, 0, 0, 0, 45505), -- Burning Blade Apprentice (Area: Skull Rock - Difficulty: 0)
(@CGUID+715, 3198, 1, 14, 817, '0', '0', 0, 0, 1, 1502.2569580078125, -4800.548828125, 9.631378173828125, 1.227255940437316894, 120, 0, 0, 1531, 2175, 0, 0, 0, 0, 45505), -- Burning Blade Apprentice (Area: Skull Rock - Difficulty: 0)
(@CGUID+716, 3198, 1, 14, 817, '0', '0', 0, 0, 1, 1419.9320068359375, -4771.32421875, 4.636091232299804687, 5.484477519989013671, 120, 10, 0, 1531, 2175, 1, 0, 0, 0, 45505), -- Burning Blade Apprentice (Area: Skull Rock - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+717, 3197, 1, 14, 817, '0', '0', 0, 0, 1, 1444.420166015625, -4784.98974609375, 8.355298995971679687, 1.755842328071594238, 120, 10, 0, 1914, 852, 1, 0, 0, 0, 45505), -- Burning Blade Fanatic (Area: Skull Rock - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+718, 100664, 1, 14, 817, '0', '0', 0, 0, 0, 1401.373291015625, -4838.9931640625, 17.3308563232421875, 3.187578678131103515, 120, 0, 0, 5443, 0, 0, 0, 0, 0, 45505), -- Thunder Bluff Native (Area: Skull Rock - Difficulty: 0)
(@CGUID+719, 100502, 1, 14, 817, '0', '0', 0, 0, 0, 1399.373291015625, -4839.47900390625, 17.63541793823242187, 0.467811405658721923, 120, 0, 0, 5443, 0, 0, 0, 0, 0, 45505), -- Concerned Citizen (Area: Skull Rock - Difficulty: 0)
(@CGUID+720, 100679, 1, 14, 817, '0', '0', 0, 0, 0, 1425.8385009765625, -4840.67724609375, 15.32624435424804687, 4.070081710815429687, 120, 0, 0, 5443, 0, 0, 0, 0, 0, 45505), -- Citizen of Kezan (Area: Skull Rock - Difficulty: 0)
(@CGUID+721, 3100, 1, 14, 817, '0', '0', 0, 0, 0, 1361.3023681640625, -4810.81689453125, 28.02761650085449218, 2.285034656524658203, 120, 10, 0, 1914, 0, 1, 0, 0, 0, 45505), -- Elder Mottled Boar (Area: Skull Rock - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+722, 100663, 1, 14, 817, '0', '0', 0, 0, 0, 1413.890625, -4866.767578125, 12.44843578338623046, 0.142056211829185485, 120, 0, 0, 5443, 0, 0, 0, 0, 0, 45505), -- Sen'jin Villager (Area: Skull Rock - Difficulty: 0)
(@CGUID+723, 40891, 1, 14, 817, '0', '0', 0, 0, 0, 1398.453125, -4888.92529296875, 11.424652099609375, 5.248237133026123046, 120, 0, 0, 1914, 0, 0, 0, 0, 0, 45505), -- Dranosh'ar Laborer (Area: Skull Rock - Difficulty: 0)
(@CGUID+724, 100502, 1, 14, 817, '0', '0', 0, 0, 0, 1435.15625, -4884.44970703125, 10.70486068725585937, 2.593064546585083007, 120, 0, 0, 5443, 0, 0, 0, 0, 0, 45505), -- Concerned Citizen (Area: Skull Rock - Difficulty: 0)
(@CGUID+725, 5951, 1, 14, 817, '0', '0', 0, 0, 0, 1379.0596923828125, -4754.890625, 27.35931777954101562, 3.963643550872802734, 120, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Hare (Area: Skull Rock - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+726, 100682, 1, 14, 817, '0', '0', 0, 0, 0, 1415.717041015625, -4875.28125, 11.61281681060791015, 1.252553939819335937, 120, 0, 0, 5443, 0, 0, 0, 0, 0, 45505), -- Silvermoon Citizen (Area: Skull Rock - Difficulty: 0)
(@CGUID+727, 3100, 1, 14, 817, '0', '0', 0, 0, 0, 1350.134521484375, -4869.7392578125, 17.3697967529296875, 2.423222064971923828, 120, 0, 0, 1914, 0, 0, 0, 0, 0, 45505), -- Elder Mottled Boar (Area: Skull Rock - Difficulty: 0)
(@CGUID+728, 3198, 1, 14, 817, '0', '0', 0, 0, 1, 1480.5885009765625, -4854.953125, 11.38019847869873046, 3.989474296569824218, 120, 0, 0, 1531, 2175, 0, 0, 0, 0, 45505), -- Burning Blade Apprentice (Area: Skull Rock - Difficulty: 0)
(@CGUID+729, 100502, 1, 14, 817, '0', '0', 0, 0, 0, 1433.2291259765625, -4883.7275390625, 10.86631965637207031, 6.156482696533203125, 120, 0, 0, 5443, 0, 0, 0, 0, 0, 45505), -- Concerned Citizen (Area: Skull Rock - Difficulty: 0)
(@CGUID+730, 184813, 1, 14, 817, '0', '0', 0, 0, 0, 1360.506591796875, -4911.55224609375, 61.7478179931640625, 5.523959159851074218, 120, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Brave Researcher (Area: Skull Rock - Difficulty: 0) (Auras: 372740 - -0-)
(@CGUID+731, 184814, 1, 14, 817, '0', '0', 0, 0, 0, 1372.5791015625, -4920.53125, 61.79407882690429687, 2.30572366714477539, 120, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Rugged Artisan (Area: Skull Rock - Difficulty: 0) (Auras: 374319 - -0-)
(@CGUID+732, 184813, 1, 14, 817, '0', '0', 0, 0, 0, 1375.2603759765625, -4924.23291015625, 67.24890899658203125, 4.600368022918701171, 120, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Brave Researcher (Area: Skull Rock - Difficulty: 0) (Auras: 374107 - -0-)
(@CGUID+733, 184813, 1, 14, 817, '0', '0', 0, 0, 0, 1348.1458740234375, -4914.26904296875, 61.41501617431640625, 2.090243816375732421, 120, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Brave Researcher (Area: Skull Rock - Difficulty: 0) (Auras: 374107 - -0-)
(@CGUID+734, 189554, 1, 14, 817, '0', '0', 0, 0, 0, 1372.7222900390625, -4928.00537109375, 61.83269500732421875, 0.651329278945922851, 120, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Expedition Supplier (Area: Skull Rock - Difficulty: 0)
(@CGUID+735, 189554, 1, 14, 817, '0', '0', 0, 0, 0, 1358.8038330078125, -4907.48779296875, 61.83115005493164062, 2.527886390686035156, 120, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Expedition Supplier (Area: Skull Rock - Difficulty: 0)
(@CGUID+736, 190239, 1, 14, 817, '0', '0', 0, 0, 0, 1358.920166015625, -4915.26416015625, 61.83115005493164062, 0.048508413136005401, 120, 0, 0, 20648, 2434, 0, 0, 0, 0, 45505), -- Ebyssian (Area: Skull Rock - Difficulty: 0) (Auras: )
(@CGUID+737, 189554, 1, 14, 817, '0', '0', 0, 0, 0, 1362.5086669921875, -4904.57470703125, 61.83115005493164062, 0.775142848491668701, 120, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Expedition Supplier (Area: Skull Rock - Difficulty: 0)
-- (@CGUID+738, 194115, 0, 14, 817, '0', '0', 0, 0, 0, -12.9304828643798828, 32.82219314575195312, 10.5721282958984375, 3.4627685546875, 120, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Airship Worker (Area: Skull Rock - Difficulty: 0) (Auras: 384573 - -0-) - !!! on transport - transport template not found !!!
(@CGUID+739, 189554, 1, 14, 817, '0', '0', 0, 0, 0, 1369.300048828125, -4901.10009765625, 61.74779891967773437, 5.956945419311523437, 120, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Expedition Supplier (Area: Skull Rock - Difficulty: 0) (Auras: 372737 - -0-)
(@CGUID+740, 184808, 1, 14, 817, '0', '0', 0, 0, 0, 1346.060791015625, -4918.34716796875, 61.796630859375, 3.386372089385986328, 120, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Pathfinder Tacha (Area: Skull Rock - Difficulty: 0)
(@CGUID+741, 189554, 1, 14, 817, '0', '0', 0, 0, 0, 1378.8599853515625, -4922.85986328125, 61.74779891967773437, 4.258603572845458984, 120, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Expedition Supplier (Area: Skull Rock - Difficulty: 0) (Auras: 372729 - -0-)
(@CGUID+742, 184810, 1, 14, 817, '0', '0', 0, 0, 0, 1344.01220703125, -4918.90283203125, 61.796630859375, 0.167863309383392333, 120, 0, 0, 92814, 0, 0, 0, 0, 0, 45505), -- Boss Magor (Area: Skull Rock - Difficulty: 0)
(@CGUID+743, 184812, 1, 14, 817, '0', '0', 0, 0, 0, 1364.52001953125, -4927.56982421875, 61.98540115356445312, 4.118977069854736328, 120, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Restless Explorer (Area: Skull Rock - Difficulty: 0) (Auras: 372471 - -0-)
(@CGUID+744, 184813, 1, 14, 817, '0', '0', 0, 0, 0, 1346.0699462890625, -4915.3798828125, 62.09349822998046875, 1.570796370506286621, 120, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Brave Researcher (Area: Skull Rock - Difficulty: 0)
(@CGUID+745, 189075, 1, 14, 817, '0', '0', 0, 0, 0, 1381.013671875, -4930.4375, 75.305267333984375, 2.709979534149169921, 120, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Seagull (Area: Skull Rock - Difficulty: 0) (Auras: )
(@CGUID+746, 184814, 1, 14, 817, '0', '0', 0, 0, 0, 1370.3499755859375, -4925.7001953125, 61.74779891967773437, 0.610865235328674316, 120, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Rugged Artisan (Area: Skull Rock - Difficulty: 0) (Auras: 374209 - -0-)
(@CGUID+747, 184812, 1, 14, 817, '0', '0', 0, 0, 0, 1369.239990234375, -4905.43994140625, 61.74779891967773437, 5.811946392059326171, 120, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Restless Explorer (Area: Skull Rock - Difficulty: 0) (Auras: 374128 - -0-)
(@CGUID+748, 180701, 1, 14, 817, '0', '0', 0, 0, 0, 1350.9566650390625, -4908.13037109375, 68.4517364501953125, 0, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- (Bunny) Sessile (Area: Skull Rock - Difficulty: 0)
(@CGUID+749, 197279, 1, 14, 817, '0', '0', 0, 0, 0, 1362, -4913.40087890625, 61.83115005493164062, 0.031519044190645217, 120, 0, 0, 92814, 0, 0, 0, 0, 0, 45505); -- Naleidea Rivergleam (Area: Skull Rock - Difficulty: 0) (Auras: 378042 - -0-)

INSERT INTO `creature` (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnDifficulties`, `PhaseId`, `PhaseGroup`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `wander_distance`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`, `VerifiedBuild`) VALUES
(@CGUID+750, 195899, 1, 14, 817, '0', '0', 0, 0, 0, 1372.298583984375, -4898.2744140625, 62.13742828369140625, 2.096327543258666992, 120, 0, 0, 63886, 0, 0, 0, 0, 0, 45505), -- Storm Huntress Suhrakka (Area: Skull Rock - Difficulty: 0)
(@CGUID+751, 189554, 1, 14, 817, '0', '0', 0, 0, 0, 1357.607666015625, -4906.49853515625, 61.83115005493164062, 5.6043243408203125, 120, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Expedition Supplier (Area: Skull Rock - Difficulty: 0)
(@CGUID+752, 197288, 1, 14, 817, '0', '0', 0, 0, 0, 1344.3385009765625, -4924.8681640625, 61.8052978515625, 1.089758038520812988, 120, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Skarukaru (Area: Skull Rock - Difficulty: 0)
(@CGUID+753, 40891, 1, 14, 817, '0', '0', 0, 0, 0, 1393.40625, -4899.5556640625, 11.42539405822753906, 0.552769958972930908, 120, 0, 0, 1914, 0, 0, 0, 0, 0, 45505), -- Dranosh'ar Laborer (Area: Skull Rock - Difficulty: 0)
(@CGUID+754, 3100, 1, 14, 817, '0', '0', 0, 0, 0, 1302.405029296875, -4864.470703125, 13.732147216796875, 0.792989492416381835, 120, 0, 0, 1914, 0, 0, 0, 0, 0, 45505), -- Elder Mottled Boar (Area: Skull Rock - Difficulty: 0)
(@CGUID+755, 3108, 1, 14, 817, '0', '0', 0, 0, 0, 1423.362548828125, -4940.193359375, 0.628554821014404296, 4.166159629821777343, 120, 0, 0, 1914, 0, 0, 0, 0, 0, 45505), -- Encrusted Surf Crawler (Area: Skull Rock - Difficulty: 0)
(@CGUID+756, 195357, 1, 14, 817, '0', '0', 0, 0, 0, 1395.875, -4913.84716796875, 11.42539405822753906, 0.119815617799758911, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Grok Thickfoot (Area: Skull Rock - Difficulty: 0)
(@CGUID+757, 184812, 1, 14, 817, '0', '0', 0, 0, 0, 1387.111083984375, -4904.10400390625, 11.730438232421875, 5.200512409210205078, 120, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Restless Explorer (Area: Skull Rock - Difficulty: 0) (Auras: 374128 - -0-)
(@CGUID+758, 184814, 1, 14, 817, '0', '0', 0, 0, 0, 1410.935791015625, -4914.09033203125, 11.42539405822753906, 2.769029140472412109, 120, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Rugged Artisan (Area: Skull Rock - Difficulty: 0)
(@CGUID+759, 184812, 1, 14, 817, '0', '0', 0, 0, 0, 1383.9635009765625, -4900.69775390625, 11.730438232421875, 5.279878616333007812, 120, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Restless Explorer (Area: Skull Rock - Difficulty: 0) (Auras: 372471 - -0-)
(@CGUID+760, 184814, 1, 14, 817, '0', '0', 0, 0, 0, 1408.703125, -4913.59033203125, 11.42539405822753906, 0.048546232283115386, 120, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Rugged Artisan (Area: Skull Rock - Difficulty: 0)
-- (@CGUID+761, 195677, 0, 14, 817, '0', '0', 0, 0, 0, -17.7150688171386718, 7.48239898681640625, 7.211911678314208984, 0.005124845542013645, 120, 0, 0, 30938, 2568, 0, 0, 0, 0, 45505), -- Dracthyr Soldier (Area: Skull Rock - Difficulty: 0) - !!! on transport - transport template not found !!!
-- (@CGUID+762, 194055, 0, 14, 817, '0', '0', 0, 0, 0, -6.09365606307983398, 28.36237907409667968, 34.33063507080078125, 5.242101669311523437, 120, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Dahanu Highwing (Area: Skull Rock - Difficulty: 0) - !!! on transport - transport template not found !!!
-- (@CGUID+763, 194056, 0, 14, 817, '0', '0', 0, 0, 0, -4.28675127029418945, 31.00005722045898437, 38.38167953491210937, 4.238356590270996093, 120, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Dragon Kite (Area: Skull Rock - Difficulty: 0) (Auras: ) - !!! on transport - transport template not found !!!
-- (@CGUID+764, 194115, 0, 14, 817, '0', '0', 0, 0, 0, 19.95859718322753906, 29.34128761291503906, 36.52104949951171875, 2.215337276458740234, 120, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Airship Worker (Area: Skull Rock - Difficulty: 0) (Auras: 384573 - -0-) - !!! on transport - transport template not found !!!
(@CGUID+765, 184813, 1, 14, 817, '0', '0', 0, 0, 0, 1389.8125, -4913.765625, 11.730438232421875, 5.053530693054199218, 120, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Brave Researcher (Area: Skull Rock - Difficulty: 0)
(@CGUID+766, 184809, 1, 14, 817, '0', '0', 0, 0, 0, 1348.6875, -4925.6806640625, 62.39379119873046875, 4.755497932434082031, 120, 0, 0, 30938, 2568, 0, 0, 0, 0, 45505), -- Cataloger Kieule (Area: Skull Rock - Difficulty: 0)
(@CGUID+767, 184813, 1, 14, 817, '0', '0', 0, 0, 0, 1390.4271240234375, -4916.923828125, 11.73043727874755859, 1.842307209968566894, 120, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Brave Researcher (Area: Skull Rock - Difficulty: 0)
(@CGUID+768, 184812, 1, 14, 817, '0', '0', 0, 0, 0, 1384.2291259765625, -4902.798828125, 11.730438232421875, 1.604533195495605468, 120, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Restless Explorer (Area: Skull Rock - Difficulty: 0)
(@CGUID+769, 3300, 1, 14, 817, '0', '0', 0, 0, 0, 1302.5748291015625, -4873.2626953125, 13.900634765625, 4.278414249420166015, 120, 0, 0, 1, 0, 0, 0, 0, 0, 45505), -- Adder (Area: Skull Rock - Difficulty: 0)
(@CGUID+770, 40891, 1, 14, 817, '0', '0', 0, 0, 0, 1390.046875, -4919.32275390625, 11.730438232421875, 3.205438613891601562, 120, 0, 0, 1914, 0, 0, 0, 0, 0, 45505), -- Dranosh'ar Laborer (Area: Skull Rock - Difficulty: 0)
(@CGUID+771, 184813, 1, 14, 817, '0', '0', 0, 0, 0, 1387.93408203125, -4914.98779296875, 11.730438232421875, 5.502615928649902343, 120, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Brave Researcher (Area: Skull Rock - Difficulty: 0)
(@CGUID+772, 40891, 1, 14, 817, '0', '0', 0, 0, 0, 1417.9947509765625, -4906.95849609375, 11.42538928985595703, 4.225354194641113281, 120, 0, 0, 1914, 0, 0, 0, 0, 0, 45505), -- Dranosh'ar Laborer (Area: Skull Rock - Difficulty: 0)
(@CGUID+773, 40891, 1, 14, 817, '0', '0', 0, 0, 0, 1401.8472900390625, -4919.99462890625, 11.42539405822753906, 5.65106201171875, 120, 0, 0, 1914, 0, 0, 0, 0, 0, 45505), -- Dranosh'ar Laborer (Area: Skull Rock - Difficulty: 0)
(@CGUID+774, 41621, 1, 14, 817, '0', '0', 0, 0, 1, 1373.7447509765625, -4913.73291015625, 12.95809364318847656, 0.330367803573608398, 120, 0, 0, 264578, 0, 0, 0, 0, 0, 45505), -- Commander Thorak (Area: Skull Rock - Difficulty: 0)
(@CGUID+775, 3100, 1, 14, 817, '0', '0', 0, 0, 0, 1342.8023681640625, -4941.28759765625, 7.342071533203125, 3.741515636444091796, 120, 0, 0, 1914, 0, 0, 0, 0, 0, 45505), -- Elder Mottled Boar (Area: Skull Rock - Difficulty: 0)
(@CGUID+776, 195385, 1, 14, 817, '0', '0', 0, 0, 0, 1398.5833740234375, -4915.09716796875, 11.42539405822753906, 2.782611370086669921, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Adventurous Tailor (Area: Skull Rock - Difficulty: 0)
(@CGUID+777, 40891, 1, 14, 817, '0', '0', 0, 0, 0, 1415.0260009765625, -4914.4130859375, 11.42540931701660156, 0.733038306236267089, 120, 0, 0, 1914, 0, 0, 0, 0, 0, 45505), -- Dranosh'ar Laborer (Area: Skull Rock - Difficulty: 0)
-- (@CGUID+778, 195677, 0, 14, 4982, '0', '0', 0, 0, 0, 14.61053752899169921, 13.90614604949951171, 35.09305953979492187, 2.718717813491821289, 120, 0, 0, 30938, 2568, 0, 0, 0, 0, 45505), -- Dracthyr Soldier (Area: The Dranosh'ar Blockade - Difficulty: 0) - !!! on transport - transport template not found !!!
-- (@CGUID+779, 194581, 0, 14, 4982, '0', '0', 0, 0, 1, 23.41773223876953125, 18.86626625061035156, 35.76625823974609375, 0.834208965301513671, 120, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Trauga Bloodhelm (Area: The Dranosh'ar Blockade - Difficulty: 0) (Auras: 369560 - -0-) - !!! on transport - transport template not found !!!
-- (@CGUID+780, 194582, 0, 14, 4982, '0', '0', 0, 0, 1, 24.88162040710449218, 20.47985458374023437, 35.93605422973632812, 3.810148239135742187, 120, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Mathog Hideflayer (Area: The Dranosh'ar Blockade - Difficulty: 0) - !!! on transport - transport template not found !!!
(@CGUID+781, 62116, 1, 14, 4982, '0', '0', 0, 0, 0, 1329.954345703125, -4883.9072265625, 15.18458175659179687, 4.083736419677734375, 120, 0, 0, 1, 0, 0, 0, 0, 0, 45505), -- Creepy Crawly (Area: The Dranosh'ar Blockade - Difficulty: 0)
-- (@CGUID+782, 194563, 0, 14, 4982, '0', '0', 0, 0, 1, 17.57465934753417968, 1.062452554702758789, 6.68238067626953125, 2.4339447021484375, 120, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Arandil Featherdawn (Area: The Dranosh'ar Blockade - Difficulty: 0) (Auras: 369706 - -0-) - !!! on transport - transport template not found !!!
-- (@CGUID+783, 195677, 0, 14, 4982, '0', '0', 0, 0, 0, 22.54070472717285156, 7.73870086669921875, 7.10140228271484375, 3.189305543899536132, 120, 0, 0, 30938, 2568, 0, 0, 0, 0, 45505), -- Dracthyr Soldier (Area: The Dranosh'ar Blockade - Difficulty: 0) - !!! on transport - transport template not found !!!
-- (@CGUID+784, 195677, 0, 14, 4982, '0', '0', 0, 0, 0, -17.6516532897949218, -7.72363185882568359, 7.30670785903930664, 6.017193317413330078, 120, 0, 0, 30938, 2568, 0, 0, 0, 0, 45505), -- Dracthyr Soldier (Area: The Dranosh'ar Blockade - Difficulty: 0) - !!! on transport - transport template not found !!!
(@CGUID+785, 3108, 1, 14, 4982, '0', '0', 0, 0, 0, 1377.845458984375, -4966.32275390625, 0.745430588722229003, 2.890658855438232421, 120, 0, 0, 1914, 0, 0, 0, 0, 0, 45505), -- Encrusted Surf Crawler (Area: The Dranosh'ar Blockade - Difficulty: 0)
(@CGUID+786, 160526, 1, 14, 4982, '0', '0', 0, 0, 1, 1385.2379150390625, -4960.8525390625, 0.42774289846420288, 5.321443557739257812, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Neri Sharpfin (Area: The Dranosh'ar Blockade - Difficulty: 0)
-- (@CGUID+787, 194577, 0, 14, 4982, '0', '0', 0, 0, 0, -55.8327713012695312, -2.95953965187072753, 12.91195583343505859, 1.297724843025207519, 120, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Rinka (Area: The Dranosh'ar Blockade - Difficulty: 0) - !!! on transport - transport template not found !!!
-- (@CGUID+788, 194361, 0, 14, 4982, '0', '0', 0, 0, 0, 10.04618453979492187, 3.30335402488708496, 34.78131866455078125, 3.627112388610839843, 120, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Rathamaresh (Area: The Dranosh'ar Blockade - Difficulty: 0) - !!! on transport - transport template not found !!!
-- (@CGUID+789, 194115, 0, 14, 4982, '0', '0', 0, 0, 0, 39.37465667724609375, 22.38262557983398437, 37.01980209350585937, 2.826815128326416015, 120, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Airship Worker (Area: The Dranosh'ar Blockade - Difficulty: 0) - !!! on transport - transport template not found !!!
-- (@CGUID+790, 194561, 0, 14, 4982, '0', '0', 0, 0, 1, 16.83992576599121093, 2.159106969833374023, 6.618637561798095703, 5.516880989074707031, 120, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Talanath Goldcrest (Area: The Dranosh'ar Blockade - Difficulty: 0) - !!! on transport - transport template not found !!!
(@CGUID+791, 49837, 1, 14, 4982, '0', '0', 0, 0, 0, 1338.899658203125, -4976.03515625, 3.14525604248046875, 2.404566287994384765, 120, 0, 0, 27, 0, 0, 0, 0, 0, 45505), -- Spiny Lizard (Area: The Dranosh'ar Blockade - Difficulty: 0)
-- (@CGUID+792, 194576, 0, 14, 4982, '0', '0', 0, 0, 0, 47.16939926147460937, 4.256745338439941406, 10.14251136779785156, 0, 120, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Vernell Bartlett (Area: The Dranosh'ar Blockade - Difficulty: 0) (Auras: 384513 - -0-) - !!! on transport - transport template not found !!!
(@CGUID+793, 3127, 1, 14, 4982, '0', '0', 0, 0, 0, 1266.551513671875, -4882.84228515625, 13.65640163421630859, 3.856020450592041015, 120, 10, 0, 1914, 0, 1, 0, 0, 0, 45505), -- Venomtail Scorpid (Area: The Dranosh'ar Blockade - Difficulty: 0) (possible waypoints or random movement)
-- (@CGUID+794, 194115, 0, 14, 4982, '0', '0', 0, 0, 0, 25.9432830810546875, -2.56642794609069824, 33.08763885498046875, 6.19434356689453125, 120, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Airship Worker (Area: The Dranosh'ar Blockade - Difficulty: 0) (Auras: 372741 - -0-) - !!! on transport - transport template not found !!!
-- (@CGUID+795, 194050, 0, 14, 4982, '0', '0', 0, 0, 1, 8.572060585021972656, -25.0048465728759765, 35.07341384887695312, 2.205574512481689453, 120, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Zalanti (Area: The Dranosh'ar Blockade - Difficulty: 0) - !!! on transport - transport template not found !!!
(@CGUID+796, 160527, 1, 14, 4982, '0', '0', 0, 0, 0, 1368.24658203125, -4980.13037109375, 0.596736371517181396, 0.718879878520965576, 120, 0, 0, 529156, 0, 0, 0, 0, 0, 45505), -- Mak (Area: The Dranosh'ar Blockade - Difficulty: 0)
-- (@CGUID+797, 194569, 0, 14, 4982, '0', '0', 0, 0, 0, 17.632354736328125, -17.140756607055664, 9.783819198608398437, 4.560237884521484375, 120, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Si'va (Area: The Dranosh'ar Blockade - Difficulty: 0) - !!! on transport - transport template not found !!!
(@CGUID+798, 160528, 1, 14, 4982, '0', '0', 0, 0, 1, 1370.453125, -4977.30712890625, 0.676474690437316894, 3.796824216842651367, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Poen Gillbrack (Area: The Dranosh'ar Blockade - Difficulty: 0)
(@CGUID+799, 160529, 1, 14, 4982, '0', '0', 0, 0, 1, 1382.260009765625, -4993.83984375, -6.28149986267089843, 3.162021398544311523, 120, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Vim Brineheart (Area: The Dranosh'ar Blockade - Difficulty: 0)
(@CGUID+800, 160530, 1, 14, 4982, '0', '0', 0, 0, 0, 1364.5347900390625, -4970.4599609375, 2.228539705276489257, 0.061699051409959793, 120, 0, 0, 1058312, 0, 0, 0, 0, 0, 45505), -- Friend Pronk (Area: The Dranosh'ar Blockade - Difficulty: 0)
-- (@CGUID+801, 194115, 0, 14, 4982, '0', '0', 0, 0, 0, 40.02476119995117187, -6.89236640930175781, 10.13622093200683593, 3.952769994735717773, 120, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Airship Worker (Area: The Dranosh'ar Blockade - Difficulty: 0) - !!! on transport - transport template not found !!!
-- (@CGUID+802, 189609, 0, 14, 4982, '0', '0', 0, 0, 1, 41.32387924194335937, 5.686937332153320312, 30.22188758850097656, 3.557700872421264648, 120, 0, 0, 61875, 6015, 0, 0, 0, 0, 45505), -- Quartermaster Furlein (Area: The Dranosh'ar Blockade - Difficulty: 0) - !!! on transport - transport template not found !!!
(@CGUID+803, 3108, 1, 14, 4982, '0', '0', 0, 0, 0, 1350.802734375, -4982.85791015625, 1.530167818069458007, 4.35819244384765625, 120, 0, 0, 1914, 0, 0, 0, 0, 0, 45505), -- Encrusted Surf Crawler (Area: The Dranosh'ar Blockade - Difficulty: 0)
(@CGUID+804, 3127, 1, 14, 4982, '0', '0', 0, 0, 0, 1269.9056396484375, -4934.8291015625, 8.064279556274414062, 5.502465248107910156, 120, 0, 0, 1914, 0, 0, 0, 0, 0, 45505), -- Venomtail Scorpid (Area: The Dranosh'ar Blockade - Difficulty: 0)
-- (@CGUID+805, 194583, 0, 14, 4982, '0', '0', 0, 0, 0, 9.124380111694335937, -11.7298345565795898, 34.74383926391601562, 3.254860162734985351, 120, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Krakz Cloudgrease (Area: The Dranosh'ar Blockade - Difficulty: 0) - !!! on transport - transport template not found !!!
-- (@CGUID+806, 194073, 0, 14, 4982, '0', '0', 0, 0, 0, 9.446832656860351562, -10.128575325012207, 34.72960281372070312, 3.124699592590332031, 120, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Lux Fizzlegig (Area: The Dranosh'ar Blockade - Difficulty: 0) (Auras: 386130 - -0-) - !!! on transport - transport template not found !!!
(@CGUID+807, 49837, 1, 14, 4982, '0', '0', 0, 0, 0, 1264.567626953125, -4917.13671875, 9.465484619140625, 3.538788557052612304, 120, 10, 0, 27, 0, 1, 0, 0, 0, 45505), -- Spiny Lizard (Area: The Dranosh'ar Blockade - Difficulty: 0) (possible waypoints or random movement)
-- (@CGUID+808, 195677, 0, 14, 4982, '0', '0', 0, 0, 0, 22.57594871520996093, -7.50803804397583007, 7.079740047454833984, 3.155659914016723632, 120, 0, 0, 30938, 2568, 0, 0, 0, 0, 45505), -- Dracthyr Soldier (Area: The Dranosh'ar Blockade - Difficulty: 0) - !!! on transport - transport template not found !!!
-- (@CGUID+809, 194115, 0, 14, 4982, '0', '0', 0, 0, 0, 36.14715957641601562, 9.66092681884765625, 10.12293243408203125, 2.090878486633300781, 120, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Airship Worker (Area: The Dranosh'ar Blockade - Difficulty: 0) - !!! on transport - transport template not found !!!
-- (@CGUID+810, 194115, 0, 14, 4982, '0', '0', 0, 0, 0, -21.6720428466796875, -14.4881544113159179, 34.01686477661132812, 3.271959304809570312, 120, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Airship Worker (Area: The Dranosh'ar Blockade - Difficulty: 0) (Auras: 272990 - -0-) - !!! on transport - transport template not found !!!
-- (@CGUID+811, 195677, 0, 14, 4982, '0', '0', 0, 0, 0, 14.99721622467041015, -13.2631568908691406, 35.08994293212890625, 3.155659914016723632, 120, 0, 0, 30938, 2568, 0, 0, 0, 0, 45505), -- Dracthyr Soldier (Area: The Dranosh'ar Blockade - Difficulty: 0) - !!! on transport - transport template not found !!!
-- (@CGUID+812, 194115, 0, 14, 4982, '0', '0', 0, 0, 0, 20.37371253967285156, -24.1911430358886718, 35.9413909912109375, 5.340992450714111328, 120, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Airship Worker (Area: The Dranosh'ar Blockade - Difficulty: 0) - !!! on transport - transport template not found !!!
(@CGUID+813, 3127, 1, 14, 4982, '0', '0', 0, 0, 0, 1286.7880859375, -4954.94677734375, 6.197255611419677734, 1.924076318740844726, 120, 0, 0, 1914, 0, 0, 0, 0, 0, 45505), -- Venomtail Scorpid (Area: The Dranosh'ar Blockade - Difficulty: 0)
(@CGUID+814, 3108, 1, 14, 4982, '0', '0', 0, 0, 0, 1381.9990234375, -4984.1591796875, -3.49495649337768554, 1.314915060997009277, 120, 0, 0, 1914, 0, 0, 0, 0, 0, 45505), -- Encrusted Surf Crawler (Area: The Dranosh'ar Blockade - Difficulty: 0)
(@CGUID+815, 3108, 1, 14, 4982, '0', '0', 0, 0, 0, 1317.51220703125, -5006.580078125, 0.752588331699371337, 1.902408838272094726, 120, 0, 0, 1914, 0, 0, 0, 0, 0, 45505), -- Encrusted Surf Crawler (Area: The Dranosh'ar Blockade - Difficulty: 0)
-- (@CGUID+816, 194116, 0, 14, 4982, '0', '0', 0, 0, 0, 35.9036407470703125, -24.8679447174072265, 36.79015731811523437, 4.939443111419677734, 120, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Shin Summerhill (Area: The Dranosh'ar Blockade - Difficulty: 0) - !!! on transport - transport template not found !!!
-- (@CGUID+817, 194065, 0, 14, 4982, '0', '0', 0, 0, 0, 37.98187255859375, -23.8073158264160156, 36.90619659423828125, 5.143558979034423828, 120, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Ketuna Skyflame (Area: The Dranosh'ar Blockade - Difficulty: 0) - !!! on transport - transport template not found !!!
(@CGUID+818, 49837, 1, 14, 4982, '0', '0', 0, 0, 0, 1311.9892578125, -5000.56103515625, 0.878026485443115234, 3.746428728103637695, 120, 0, 0, 27, 0, 0, 0, 0, 0, 45505), -- Spiny Lizard (Area: The Dranosh'ar Blockade - Difficulty: 0)
(@CGUID+819, 49743, 1, 14, 4982, '0', '0', 0, 0, 0, 1370.52685546875, -4961.486328125, 2.190871238708496093, 4.084624290466308593, 120, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Dung Beetle (Area: The Dranosh'ar Blockade - Difficulty: 0)
(@CGUID+820, 3108, 1, 14, 4982, '0', '0', 0, 0, 0, 1344.0660400390625, -5013.60302734375, -2.46634793281555175, 2.534627437591552734, 120, 0, 0, 1914, 0, 0, 0, 0, 0, 45505), -- Encrusted Surf Crawler (Area: The Dranosh'ar Blockade - Difficulty: 0)
(@CGUID+821, 193450, 1, 14, 4982, '0', '0', 0, 0, 1, 1358.949951171875, -4919.47021484375, 61.73649978637695312, 3.490658521652221679, 120, 0, 0, 1587465, 7196, 0, 0, 0, 0, 45505), -- Archmage Khadgar (Area: The Dranosh'ar Blockade - Difficulty: 0) (Auras: 152821 - Invisible Man Transform)
(@CGUID+822, 190239, 1, 14, 4982, '0', '0', 0, 0, 0, 1358.920166015625, -4915.26416015625, 61.91448211669921875, 0.048508413136005401, 120, 0, 0, 20648, 2434, 0, 0, 0, 0, 45505), -- Ebyssian (Area: The Dranosh'ar Blockade - Difficulty: 0)
(@CGUID+823, 197279, 1, 14, 4982, '0', '0', 0, 0, 0, 1362, -4913.40087890625, 61.91448211669921875, 0.031519044190645217, 120, 0, 0, 92814, 0, 0, 0, 0, 0, 45505), -- Naleidea Rivergleam (Area: The Dranosh'ar Blockade - Difficulty: 0) (Auras: 378042 - -0-)
(@CGUID+824, 193889, 1, 14, 4982, '0', '0', 0, 0, 0, 1322.5982666015625, -4888.5810546875, 73.8008575439453125, 5.383309364318847656, 120, 0, 0, 30938, 2568, 0, 0, 0, 0, 45505), -- Kodethi (Area: The Dranosh'ar Blockade - Difficulty: 0)
(@CGUID+825, 193450, 1, 14, 4982, '0', '0', 0, 0, 1, 1363.8992919921875, -4919.16650390625, 61.83115386962890625, 0.627760887145996093, 120, 0, 0, 1587465, 7196, 0, 0, 0, 0, 45505), -- Archmage Khadgar (Area: The Dranosh'ar Blockade - Difficulty: 0)
(@CGUID+826, 193889, 1, 14, 4982, '0', '0', 0, 0, 0, 1360.4896240234375, -4919.43408203125, 61.83045578002929687, 0.457875162363052368, 120, 0, 0, 30938, 2568, 0, 0, 0, 0, 45505), -- Kodethi (Area: The Dranosh'ar Blockade - Difficulty: 0)
(@CGUID+827, 193889, 1, 14, 4982, '0', '0', 0, 0, 0, 1360.4896240234375, -4919.43408203125, 61.913787841796875, 0.457875162363052368, 120, 0, 0, 30938, 2568, 0, 0, 0, 0, 45505), -- Kodethi (Area: The Dranosh'ar Blockade - Difficulty: 0)
(@CGUID+828, 62116, 1, 14, 4982, '0', '0', 0, 0, 0, 1339.6165771484375, -4775.005859375, 24.99402427673339843, 3.807178020477294921, 120, 0, 0, 1, 0, 0, 0, 0, 0, 45505), -- Creepy Crawly (Area: The Dranosh'ar Blockade - Difficulty: 0)
(@CGUID+829, 40891, 1, 14, 4982, '0', '0', 0, 0, 0, 1343.2135009765625, -4699.4775390625, 37.12169265747070312, 3.605631828308105468, 120, 0, 0, 1914, 0, 0, 0, 0, 0, 45505); -- Dranosh'ar Laborer (Area: The Dranosh'ar Blockade - Difficulty: 0) (Auras: 55701 - Cosmetic - Sleep Zzz Breakable)
DELETE FROM `creature_addon` WHERE `guid` BETWEEN @CGUID+0 AND @CGUID+829;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `aiAnimKit`, `movementAnimKit`, `meleeAnimKit`, `visibilityDistanceType`, `auras`) VALUES
(@CGUID+0, 0, 0, 0, 257, 0, 0, 0, 0, 3, ''), -- Rokhan
(@CGUID+2, 0, 0, 0, 1, 0, 0, 0, 0, 3, ''), -- High Overlord Saurfang
(@CGUID+4, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Shang'gok
(@CGUID+5, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Shan'ti
(@CGUID+6, 0, 0, 0, 1, 0, 0, 0, 0, 4, ''), -- Dave's Industrial Light and Magic Bunny (Medium)(Sessile)
(@CGUID+7, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Urtrun Clanbringer
(@CGUID+8, 0, 17719, 50331648, 257, 0, 0, 0, 0, 4, ''), -- Orgrimmar Wind Rider
(@CGUID+9, 0, 0, 0, 256, 0, 0, 0, 0, 0, ''), -- Orgrimmar Grunt
(@CGUID+10, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Orgrimmar Grunt
(@CGUID+12, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Grunt Soran
(@CGUID+13, 0, 0, 0, 1, 0, 0, 0, 0, 0, '222589'), -- Kor'vas Bloodthorn - 222589 - Glaive Anim Replacement
(@CGUID+14, 0, 0, 0, 1, 0, 0, 0, 0, 4, ''), -- Dave's Industrial Light and Magic Bunny (Medium)(Sessile)
(@CGUID+15, 0, 17719, 50331648, 257, 0, 0, 0, 0, 4, ''), -- Orgrimmar Wind Rider
(@CGUID+16, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Darkspear Headhunter
(@CGUID+17, 0, 0, 0, 256, 0, 0, 0, 0, 0, ''), -- Darkspear Headhunter
(@CGUID+20, 0, 17719, 50331648, 257, 0, 0, 0, 0, 4, ''), -- Orgrimmar Wind Rider
(@CGUID+21, 0, 17719, 50331648, 257, 0, 0, 0, 0, 4, ''), -- Orgrimmar Wind Rider
(@CGUID+24, 0, 0, 0, 256, 0, 0, 0, 0, 0, ''), -- Orgrimmar Grunt
(@CGUID+25, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Orgrimmar Grunt
(@CGUID+26, 0, 17719, 50331648, 257, 0, 0, 0, 0, 4, ''), -- Orgrimmar Wind Rider
(@CGUID+27, 0, 0, 0, 256, 0, 0, 0, 0, 0, ''), -- Garyl
(@CGUID+29, 0, 0, 0, 1, 0, 0, 0, 0, 3, ''), -- Totally Generic Bunny (JSB)
(@CGUID+30, 0, 17719, 50331648, 257, 0, 0, 0, 0, 4, ''), -- Orgrimmar Wind Rider
(@CGUID+31, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Goram
(@CGUID+32, 0, 17719, 50331648, 257, 0, 0, 0, 0, 4, ''), -- Orgrimmar Wind Rider
(@CGUID+34, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Orgrimmar Grunt
(@CGUID+35, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Grunt Grimful
(@CGUID+37, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Shimra
(@CGUID+38, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Grunt Koma
(@CGUID+41, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Orgrimmar Grunt
(@CGUID+42, 0, 0, 0, 1, 0, 0, 0, 0, 4, ''), -- Dave's Industrial Light and Magic Bunny (Medium)(Sessile)
(@CGUID+44, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Grunt Karus
(@CGUID+46, 0, 0, 0, 256, 0, 0, 0, 0, 0, ''), -- Orgrimmar Grunt
(@CGUID+47, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Orgrimmar Grunt
(@CGUID+48, 0, 0, 0, 1, 0, 0, 0, 0, 0, '327198'), -- Worker - 327198 - -0-
(@CGUID+50, 0, 0, 0, 1, 0, 0, 0, 0, 4, ''), -- Dave's Industrial Light and Magic Bunny (Medium)(Sessile)
(@CGUID+51, 0, 17719, 50331648, 257, 0, 0, 0, 0, 4, ''), -- Orgrimmar Wind Rider
(@CGUID+52, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Orgrimmar Grunt
(@CGUID+53, 0, 0, 0, 1, 0, 0, 0, 0, 5, ''), -- Totally Generic Bunny (All Phase)
(@CGUID+54, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Rilgiz
(@CGUID+55, 0, 17719, 50331648, 257, 0, 0, 0, 0, 4, ''), -- Orgrimmar Wind Rider
(@CGUID+56, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Kixa
(@CGUID+58, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Orgrimmar Grunt
(@CGUID+59, 0, 17719, 50331648, 257, 0, 0, 0, 0, 4, ''), -- Orgrimmar Wind Rider
(@CGUID+60, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Perixa
(@CGUID+61, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Goma
(@CGUID+62, 0, 17719, 50331648, 257, 0, 0, 0, 0, 4, ''), -- Orgrimmar Wind Rider
(@CGUID+63, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Orgrimmar Grunt
(@CGUID+64, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Zazo
(@CGUID+66, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Innkeeper Gryshka
(@CGUID+67, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Orgrimmar Grunt
(@CGUID+68, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Kozish
(@CGUID+70, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Barkeep Morag
(@CGUID+72, 0, 0, 0, 256, 0, 0, 0, 0, 0, ''), -- Thunder Bluff Protector
(@CGUID+73, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Doyo'da
(@CGUID+74, 0, 0, 0, 1, 0, 0, 0, 0, 4, ''), -- Dave's Industrial Light and Magic Bunny (Medium)(Sessile)
(@CGUID+75, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Sarok
(@CGUID+76, 0, 0, 0, 1, 0, 0, 0, 0, 0, '221098'), -- Worker - 221098 - Sleeping Sleep
(@CGUID+78, 0, 0, 0, 1, 0, 0, 0, 0, 4, ''), -- Dave's Industrial Light and Magic Bunny (Medium)(Sessile)
(@CGUID+79, 0, 17719, 50331648, 257, 0, 0, 0, 0, 4, ''), -- Orgrimmar Wind Rider
(@CGUID+80, 0, 0, 0, 257, 0, 0, 0, 0, 0, '18950'), -- Scout Stronghand - 18950 - Invisibility and Stealth Detection
(@CGUID+81, 0, 17719, 50331648, 257, 0, 0, 0, 0, 4, ''), -- Orgrimmar Wind Rider
(@CGUID+82, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Trak'gen
(@CGUID+83, 0, 0, 1, 257, 0, 0, 0, 0, 0, ''), -- Grunt Meena
(@CGUID+84, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Grunt Nolo
(@CGUID+85, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Grunt Arhung
(@CGUID+86, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Orgrimmar Grunt
(@CGUID+87, 0, 17719, 50331648, 257, 0, 0, 0, 0, 4, ''), -- Orgrimmar Wind Rider
(@CGUID+88, 0, 0, 0, 257, 0, 0, 0, 0, 0, '18950'), -- Orgrimmar Guardian Mage - 18950 - Invisibility and Stealth Detection
(@CGUID+89, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Orgrimmar Grunt
(@CGUID+90, 0, 0, 0, 1, 0, 0, 0, 0, 0, '162443'), -- Gamon - 162443 - Cosmetic - SitGround and Drink Breakable
(@CGUID+91, 0, 0, 0, 256, 0, 0, 0, 0, 0, ''), -- Darkspear Headhunter
(@CGUID+92, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Mezlik
(@CGUID+93, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Orgrimmar Grunt
(@CGUID+94, 0, 17719, 50331648, 257, 0, 0, 0, 0, 4, ''), -- Orgrimmar Wind Rider
(@CGUID+95, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Orgrimmar Grunt
(@CGUID+97, 0, 0, 3, 1, 0, 0, 0, 0, 0, '55701'), -- Darkspear Headhunter - 55701 - Cosmetic - Sleep Zzz Breakable
(@CGUID+98, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Branzlit
(@CGUID+99, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Orgrimmar Grunt
(@CGUID+102, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Overlord Natoj
(@CGUID+103, 0, 17719, 50331648, 257, 0, 0, 0, 0, 4, ''), -- Orgrimmar Wind Rider
(@CGUID+104, 0, 17719, 50331648, 257, 0, 0, 0, 0, 4, ''), -- Orgrimmar Wind Rider
(@CGUID+105, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Northrend Adventurer
(@CGUID+106, 0, 17719, 50331648, 257, 0, 0, 0, 0, 4, ''), -- Orgrimmar Wind Rider
(@CGUID+107, 0, 17719, 50331648, 257, 0, 0, 0, 0, 4, '95230'), -- Orgrimmar Wind Rider - 95230 - Horde Flag
(@CGUID+108, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Draenor Adventurer
(@CGUID+109, 0, 17719, 50331648, 257, 0, 0, 0, 0, 4, ''), -- Orgrimmar Wind Rider
(@CGUID+110, 0, 17719, 50331648, 257, 0, 0, 0, 0, 4, ''), -- Orgrimmar Wind Rider
(@CGUID+111, 0, 17719, 50331648, 257, 0, 0, 0, 0, 4, ''), -- Orgrimmar Wind Rider
(@CGUID+113, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Dark Cleric Cecille
(@CGUID+114, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Auctioneer Fazdran
(@CGUID+115, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Auctioneer Drezmit
(@CGUID+116, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Auctioneer Ralinza
(@CGUID+117, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Auctioneer Xifa
(@CGUID+118, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Eitrigg
(@CGUID+119, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Grunt Wabang
(@CGUID+123, 0, 0, 1, 1, 0, 0, 0, 0, 0, ''), -- Yuyu
(@CGUID+125, 0, 0, 0, 257, 0, 0, 0, 0, 0, '18950'), -- Forsaken Delegation Deathguard - 18950 - Invisibility and Stealth Detection
(@CGUID+126, 0, 0, 0, 257, 0, 0, 0, 0, 0, '18950'), -- Forsaken Delegation Deathguard - 18950 - Invisibility and Stealth Detection
(@CGUID+127, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Zor Lonetree
(@CGUID+130, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Olvia
(@CGUID+131, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Shok Narnes
(@CGUID+133, 0, 17719, 50331648, 257, 0, 0, 0, 0, 4, ''), -- Orgrimmar Wind Rider
(@CGUID+134, 0, 17719, 50331648, 257, 0, 0, 0, 0, 4, ''), -- Orgrimmar Wind Rider
(@CGUID+135, 0, 17719, 50331648, 257, 0, 0, 0, 0, 4, ''), -- Orgrimmar Wind Rider
(@CGUID+136, 0, 17719, 50331648, 257, 0, 0, 0, 0, 4, ''), -- Orgrimmar Wind Rider
(@CGUID+137, 0, 17719, 50331648, 257, 0, 0, 0, 0, 4, ''), -- Orgrimmar Wind Rider
(@CGUID+138, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Orgrimmar Grunt
(@CGUID+139, 0, 17719, 50331648, 257, 0, 0, 0, 0, 4, ''), -- Orgrimmar Wind Rider
(@CGUID+145, 0, 17719, 50331648, 257, 0, 0, 0, 0, 4, ''), -- Orgrimmar Wind Rider
(@CGUID+146, 0, 17719, 50331648, 257, 0, 0, 0, 0, 4, ''), -- Orgrimmar Wind Rider
(@CGUID+147, 0, 17719, 50331648, 257, 0, 0, 0, 0, 4, ''), -- Orgrimmar Wind Rider
(@CGUID+149, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Tyelis
(@CGUID+150, 0, 0, 0, 256, 0, 0, 0, 0, 0, ''), -- Darkspear Headhunter
(@CGUID+151, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Ambassador Dawnsinger
(@CGUID+152, 0, 0, 0, 256, 0, 0, 0, 0, 0, ''), -- Darkspear Headhunter
(@CGUID+154, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Urtharo
(@CGUID+156, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Horthus
(@CGUID+157, 0, 0, 3, 1, 0, 0, 0, 0, 0, '55701'), -- Thunder Bluff Protector - 55701 - Cosmetic - Sleep Zzz Breakable
(@CGUID+158, 0, 0, 0, 256, 0, 0, 0, 0, 0, '10022'), -- Belloc Brightblade - 10022 - Deadly Poison
(@CGUID+160, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Darkspear Headhunter
(@CGUID+162, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Orgrimmar Grunt
(@CGUID+163, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Gotura Fourwinds
(@CGUID+165, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Silvermoon Delegation Guardian
(@CGUID+166, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Master Pyreanor
(@CGUID+167, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Silvermoon Delegation Guardian
(@CGUID+171, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Orgrimmar Grunt
(@CGUID+172, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Darkspear Headhunter
(@CGUID+174, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Orgrimmar Grunt
(@CGUID+175, 0, 0, 0, 257, 0, 0, 0, 0, 0, '18950'), -- Scout Manslayer - 18950 - Invisibility and Stealth Detection
(@CGUID+176, 0, 0, 0, 1, 0, 0, 0, 0, 3, ''), -- Goblin Hot Rod
(@CGUID+177, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Orgrimmar Grunt
(@CGUID+178, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Darkspear Headhunter
(@CGUID+179, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Omakka Wolfbrother
(@CGUID+180, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Orgrimmar Grunt
(@CGUID+181, 0, 17719, 50331648, 257, 0, 0, 0, 0, 4, ''), -- Orgrimmar Wind Rider
(@CGUID+182, 0, 17719, 50331648, 257, 0, 0, 0, 0, 4, ''), -- Orgrimmar Wind Rider
(@CGUID+183, 0, 17719, 50331648, 257, 0, 0, 0, 0, 4, ''), -- Orgrimmar Wind Rider
-- (@CGUID+184, 0, 0, 0, 1, 0, 0, 0, 0, 0, '122729'), -- Mystic Birdhat - 122729 - Grand Expedition Yak - !!! on transport - transport template not found !!!
-- (@CGUID+185, 0, 0, 0, 1, 0, 0, 0, 0, 0, '122729'), -- Cousin Slowhands - 122729 - Grand Expedition Yak - !!! on transport - transport template not found !!!
(@CGUID+186, 0, 0, 0, 256, 0, 0, 0, 0, 0, ''), -- Sana
(@CGUID+187, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Punra
(@CGUID+188, 0, 0, 0, 256, 0, 0, 0, 0, 0, ''), -- Naros
(@CGUID+189, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Orgrimmar Grunt
(@CGUID+190, 0, 0, 0, 256, 0, 0, 0, 0, 0, ''), -- Gonto
(@CGUID+191, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Lutah
(@CGUID+192, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Rogg
(@CGUID+193, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Warcaller Gorlach
-- (@CGUID+202, 0, 0, 0, 1, 0, 0, 0, 0, 0, '46598'), -- Ban-Lu - 46598 - Ride Vehicle Hardcoded - !!! on transport - transport template not found !!!
-- (@CGUID+203, 0, 0, 0, 1, 0, 0, 0, 0, 0, '122729'), -- Mystic Birdhat - 122729 - Grand Expedition Yak - !!! on transport - transport template not found !!!
-- (@CGUID+204, 0, 0, 0, 1, 0, 0, 0, 0, 0, '122729'), -- Cousin Slowhands - 122729 - Grand Expedition Yak - !!! on transport - transport template not found !!!
(@CGUID+205, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Orgrimmar Grunt
-- (@CGUID+207, 0, 0, 0, 1, 0, 0, 0, 0, 0, '46598'), -- Guiding Orb - 46598 - Ride Vehicle Hardcoded - !!! on transport - transport template not found !!!
-- (@CGUID+208, 0, 0, 0, 1, 0, 0, 0, 0, 0, '46598'), -- Ban-Lu - 46598 - Ride Vehicle Hardcoded - !!! on transport - transport template not found !!!
(@CGUID+211, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Krixx
-- (@CGUID+212, 0, 0, 0, 1, 0, 0, 0, 0, 0, '122729'), -- Mystic Birdhat - 122729 - Grand Expedition Yak - !!! on transport - transport template not found !!!
-- (@CGUID+213, 0, 0, 0, 1, 0, 0, 0, 0, 0, '122729'), -- Cousin Slowhands - 122729 - Grand Expedition Yak - !!! on transport - transport template not found !!!
(@CGUID+215, 0, 0, 0, 257, 0, 0, 0, 0, 0, '18950'), -- Scout Tharr - 18950 - Invisibility and Stealth Detection
(@CGUID+217, 0, 0, 0, 258, 0, 0, 0, 0, 0, ''), -- Bluffwatcher
(@CGUID+227, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Darkspear Headhunter
(@CGUID+228, 0, 17719, 50331648, 257, 0, 0, 0, 0, 4, ''), -- Orgrimmar Wind Rider
(@CGUID+229, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Orgrimmar Grunt
(@CGUID+230, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Orgrimmar Grunt
(@CGUID+232, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Orgrimmar Grunt
(@CGUID+233, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Orgrimmar Skyway Peon
(@CGUID+235, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Orgrimmar Grunt
(@CGUID+236, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Orgrimmar Grunt
(@CGUID+237, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Ureda
(@CGUID+238, 0, 0, 0, 257, 0, 0, 0, 0, 0, '79865'), -- Marud - 79865 - Frost Armor
(@CGUID+239, 0, 0, 0, 257, 0, 0, 0, 0, 0, '79849'), -- Gija - 79849 - Molten Armor
(@CGUID+240, 0, 0, 8, 257, 0, 0, 0, 0, 0, ''), -- Kor'jus
(@CGUID+241, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Rundok
(@CGUID+242, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Associate Telemancer Rafcav
(@CGUID+243, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Kareth
(@CGUID+244, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Orgrimmar Grunt
(@CGUID+245, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Orgrimmar Grunt
(@CGUID+246, 0, 17699, 0, 1, 0, 0, 0, 0, 0, ''), -- Maztha
(@CGUID+247, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Arnak Fireblade
(@CGUID+248, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Darkspear Headhunter
(@CGUID+250, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Doras
(@CGUID+252, 0, 0, 0, 256, 0, 0, 0, 0, 0, ''), -- Frizzo Villamar
(@CGUID+253, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Orgrimmar Grunt
(@CGUID+255, 0, 29260, 0, 256, 0, 0, 0, 0, 0, ''), -- Stone Guard Nargol
(@CGUID+256, 0, 0, 0, 257, 0, 0, 0, 0, 0, '81245'), -- Orgrimmar Skyway Peon - 81245 - Orc Carrying Logs
-- (@CGUID+258, 0, 0, 0, 1, 0, 0, 0, 0, 0, '122729 123236'), -- Mystic Birdhat - 122729 - Grand Expedition Yak, 123236 - Grummle Booth A - !!! on transport - transport template not found !!!
-- (@CGUID+259, 0, 0, 0, 1, 0, 0, 0, 0, 0, '122729 123240'), -- Cousin Slowhands - 122729 - Grand Expedition Yak, 123240 - Grummle Booth B - !!! on transport - transport template not found !!!
(@CGUID+261, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Ukos Bloodwhisper
(@CGUID+262, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Marogg
(@CGUID+263, 0, 29261, 0, 256, 0, 0, 0, 0, 0, ''), -- Champion Uru'zin
(@CGUID+265, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Arugi
(@CGUID+266, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Darkspear Headhunter
(@CGUID+267, 0, 0, 0, 256, 0, 0, 0, 0, 0, ''), -- Orgrimmar Grunt
(@CGUID+269, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Felika
(@CGUID+275, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Thund
(@CGUID+279, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, '101667'), -- Vaultkeeper Jazra - 101667 - Arcane Vault Sphere
(@CGUID+281, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Gotri
(@CGUID+286, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Tosamina
(@CGUID+288, 0, 0, 0, 257, 0, 1348, 0, 0, 0, ''), -- Blax Bottlerocket
-- (@CGUID+289, 0, 0, 0, 1, 0, 0, 0, 0, 0, '46598 96847'), -- Toy Cart - 46598 - Ride Vehicle Hardcoded, 96847 - Blue Doll State - !!! on transport - transport template not found !!!
(@CGUID+290, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Suja
(@CGUID+291, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Sinzi Sparkscribe
(@CGUID+293, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Orgrimmar Grunt
-- (@CGUID+295, 0, 0, 0, 1, 0, 0, 0, 0, 3, '46598 96850 16245 97577'), -- Toy Cart Bunny - 46598 - Ride Vehicle Hardcoded, 96850 - Toy Cart Contents, 16245 - Freeze Anim, 97577 - Handle State - !!! on transport - transport template not found !!!
(@CGUID+297, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Shazdar
(@CGUID+298, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Borstan
(@CGUID+301, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Magar
(@CGUID+302, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Borya
(@CGUID+305, 0, 0, 0, 256, 0, 0, 0, 0, 0, ''), -- Tor'phan
(@CGUID+306, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Ollanus
(@CGUID+308, 0, 0, 0, 257, 0, 0, 0, 0, 0, '79849'), -- Moraka - 79849 - Molten Armor
(@CGUID+311, 0, 0, 0, 257, 0, 0, 0, 0, 0, '79865'), -- Nerog - 79865 - Frost Armor
(@CGUID+312, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Craven Drok
(@CGUID+313, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Orgrimmar Skyway Peon
(@CGUID+314, 0, 0, 0, 257, 0, 0, 0, 0, 0, '81245'), -- Orgrimmar Skyway Peon - 81245 - Orc Carrying Logs
(@CGUID+315, 0, 0, 0, 257, 0, 0, 0, 0, 0, '82614'), -- Orgrimmar Skyway Peon - 82614 - Bailing Hay
(@CGUID+317, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Orgrimmar Skyway Peon
(@CGUID+318, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Drakma
(@CGUID+325, 0, 0, 0, 257, 0, 0, 0, 0, 0, '82614'), -- Orgrimmar Skyway Peon - 82614 - Bailing Hay
(@CGUID+327, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Frezza
(@CGUID+328, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Orgrimmar Grunt
(@CGUID+330, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Orgrimmar Grunt
(@CGUID+332, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Orgrimmar Skyway Peon
(@CGUID+333, 0, 0, 1, 257, 0, 0, 0, 0, 0, ''), -- Orgrimmar Skyway Peon
(@CGUID+334, 0, 0, 0, 257, 0, 0, 0, 0, 0, '82612'), -- Orgrimmar Skyway Peon - 82612 - Orc Carrying Hay Bail
(@CGUID+335, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Clara Spelldriver
(@CGUID+336, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Orgrimmar Grunt
(@CGUID+337, 0, 0, 1, 257, 0, 0, 0, 0, 0, ''), -- Orgrimmar Skyway Peon
(@CGUID+338, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Orgrimmar Skyway Peon
(@CGUID+339, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Orgrimmar Grunt
(@CGUID+340, 0, 0, 0, 1, 0, 0, 0, 0, 0, '370841'), -- Kanyaku - 370841 - -0-
(@CGUID+341, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Orgrimmar Skyway Peon
(@CGUID+342, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Charles Gastly
(@CGUID+343, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Orgrimmar Grunt
(@CGUID+346, 0, 0, 1, 257, 0, 0, 0, 0, 0, ''), -- Bort
(@CGUID+347, 0, 0, 1, 257, 0, 0, 0, 0, 0, ''), -- Kor'ghan
(@CGUID+348, 0, 0, 1, 257, 0, 0, 0, 0, 0, ''), -- Cazul
(@CGUID+349, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Orgrimmar Grunt
(@CGUID+350, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Seer Liwatha
(@CGUID+351, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Snurk Bucksquick
(@CGUID+352, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Rekkul
(@CGUID+353, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Orgrimmar Grunt
(@CGUID+354, 0, 0, 1, 257, 0, 0, 0, 0, 0, ''), -- Orgrimmar Brave
(@CGUID+355, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Orgrimmar Grunt
(@CGUID+356, 0, 0, 0, 256, 0, 0, 0, 0, 0, '10022'), -- Gordul - 10022 - Deadly Poison
(@CGUID+357, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Orgrimmar Grunt
(@CGUID+358, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Gran'dul
(@CGUID+359, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Kranosh
(@CGUID+360, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Murgul
(@CGUID+361, 0, 0, 0, 258, 0, 0, 0, 0, 0, ''), -- Katis
(@CGUID+362, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''); -- Mordak Darkfist

INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `aiAnimKit`, `movementAnimKit`, `meleeAnimKit`, `visibilityDistanceType`, `auras`) VALUES
(@CGUID+363, 0, 0, 0, 256, 0, 0, 0, 0, 0, ''), -- Ormok
(@CGUID+364, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Muragus
(@CGUID+366, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Hagrus
(@CGUID+367, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Orgrimmar Brave
(@CGUID+368, 0, 0, 0, 256, 0, 0, 0, 0, 0, ''), -- Gest
(@CGUID+370, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Orgrimmar Brave
(@CGUID+371, 0, 0, 1, 257, 0, 0, 0, 0, 0, ''), -- Orgrimmar Grunt
(@CGUID+372, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Sunwalker Atohmo
(@CGUID+373, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Shalla Whiteleaf
(@CGUID+374, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Orgrimmar Grunt
(@CGUID+375, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Orgrimmar Brave
(@CGUID+376, 0, 0, 1, 257, 0, 0, 0, 0, 0, ''), -- Orgrimmar Brave
(@CGUID+377, 0, 0, 0, 0, 0, 0, 0, 0, 0, ''), -- Highmountain Pathfinder
(@CGUID+379, 0, 0, 1, 257, 0, 0, 0, 0, 0, ''), -- Orgrimmar Grunt
(@CGUID+380, 0, 0, 0, 258, 0, 0, 0, 0, 0, ''), -- Nohi Plainswalker
(@CGUID+381, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Sahi Cloudsinger
(@CGUID+383, 0, 0, 1, 257, 0, 0, 0, 0, 0, ''), -- Orgrimmar Grunt
(@CGUID+384, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Nahu Ragehoof
(@CGUID+385, 0, 0, 1, 257, 0, 0, 0, 0, 0, ''), -- Orgrimmar Brave
(@CGUID+387, 0, 0, 1, 257, 0, 0, 0, 0, 0, ''), -- Orgrimmar Brave
(@CGUID+394, 0, 0, 0, 2, 0, 0, 0, 0, 0, ''), -- Traveling Son
(@CGUID+395, 0, 0, 0, 257, 0, 0, 0, 0, 0, '18950'), -- Scout Obrok - 18950 - Invisibility and Stealth Detection
(@CGUID+396, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Orgrimmar Brave
(@CGUID+397, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Orgrimmar Grunt
(@CGUID+398, 0, 0, 65536, 1, 0, 0, 0, 0, 0, '89302'), -- Jaga - 89302 - Generic Quest Invisibility 27
(@CGUID+401, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Auctioneer Sowata
(@CGUID+404, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, '371800 369509'), -- Restless Explorer - 371800 - -0-, 369509 - -0-
(@CGUID+406, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Orgrimmar Grunt
(@CGUID+407, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Orgrimmar Grunt
(@CGUID+409, 0, 0, 0, 1, 0, 0, 0, 0, 3, ''), -- Waters of Farseeing
(@CGUID+410, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Ric Catstalker
(@CGUID+411, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Opuno Ironhorn
(@CGUID+412, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Orgrimmar Brave
(@CGUID+413, 0, 0, 0, 256, 0, 0, 0, 0, 0, ''), -- Darkspear Headhunter
(@CGUID+414, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Orgrimmar Brave
(@CGUID+415, 0, 0, 0, 258, 0, 0, 0, 0, 0, ''), -- Kaja
(@CGUID+416, 0, 0, 0, 1, 0, 0, 0, 0, 0, '32783'), -- Zugra Flamefist - 32783 - Arcane Channeling
(@CGUID+419, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Orgrimmar Grunt
(@CGUID+421, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Orgrimmar Grunt
(@CGUID+423, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Owato
(@CGUID+424, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Isashi
-- (@CGUID+425, 0, 0, 0, 1, 0, 0, 0, 0, 0, '122729 123236'), -- Mystic Birdhat - 122729 - Grand Expedition Yak, 123236 - Grummle Booth A - !!! on transport - transport template not found !!!
-- (@CGUID+428, 0, 0, 0, 1, 0, 0, 0, 0, 0, '122729 123240'), -- Cousin Slowhands - 122729 - Grand Expedition Yak, 123240 - Grummle Booth B - !!! on transport - transport template not found !!!
(@CGUID+430, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Orgrimmar Brave
(@CGUID+431, 0, 0, 0, 0, 0, 0, 0, 0, 0, ''), -- Mayla Highmountain
(@CGUID+433, 0, 0, 0, 0, 0, 0, 0, 0, 0, '378042'), -- Naleidea Rivergleam - 378042 - -0-
(@CGUID+436, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Tatepi
(@CGUID+441, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Orgrimmar Brave
(@CGUID+449, 0, 63626, 0, 1, 0, 0, 0, 0, 0, '378042'), -- Naleidea Rivergleam - 378042 - -0-
(@CGUID+451, 0, 0, 0, 256, 0, 0, 0, 0, 0, ''), -- Rento
(@CGUID+452, 0, 0, 0, 256, 0, 0, 0, 0, 0, ''), -- Terga Earthbreaker
(@CGUID+453, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Miwana
(@CGUID+454, 0, 0, 0, 1, 0, 0, 0, 0, 0, '313952'), -- Torkhan - 313952 - -0-
(@CGUID+455, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Lonto
(@CGUID+457, 0, 0, 0, 256, 0, 0, 0, 0, 0, ''), -- Sagorne Creststrider
(@CGUID+458, 0, 0, 1, 257, 0, 0, 0, 0, 0, ''), -- Sian'tsu
(@CGUID+459, 0, 0, 1, 0, 0, 0, 0, 0, 0, ''), -- Highmountain Pathfinder
(@CGUID+460, 0, 0, 0, 256, 0, 0, 0, 0, 0, ''), -- Searn Firewarder
(@CGUID+464, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Hiwahi Three-Feathers
(@CGUID+465, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Orgrimmar Grunt
(@CGUID+466, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, '371800 369509'), -- Restless Explorer - 371800 - -0-, 369509 - -0-
(@CGUID+467, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Handhold
(@CGUID+468, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Handhold
(@CGUID+470, 0, 17719, 0, 0, 0, 0, 0, 0, 0, ''), -- Orgrimmar Grunt
(@CGUID+471, 0, 0, 0, 0, 0, 0, 0, 0, 0, ''), -- Pathfinder Tacha
(@CGUID+472, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Handhold
(@CGUID+473, 0, 17719, 0, 0, 0, 0, 0, 0, 0, ''), -- Orgrimmar Grunt
(@CGUID+476, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Orgrimmar Grunt
(@CGUID+477, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Handhold
-- (@CGUID+479, 0, 0, 0, 1, 0, 0, 0, 0, 0, '371800 371801'), -- Restless Explorer - 371800 - -0-, 371801 - -0- - !!! on transport - transport template not found !!!
(@CGUID+481, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Handhold
(@CGUID+482, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Handhold
(@CGUID+483, 0, 0, 0, 1, 0, 0, 0, 0, 0, '371815'), -- Restless Explorer - 371815 - -0-
(@CGUID+484, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Bebri Coifcurl
(@CGUID+485, 0, 0, 0, 1, 0, 0, 0, 0, 0, '371815'), -- Restless Explorer - 371815 - -0-
(@CGUID+487, 0, 0, 0, 1, 0, 0, 0, 0, 0, '371815'), -- Restless Explorer - 371815 - -0-
-- (@CGUID+490, 0, 0, 0, 1, 0, 0, 0, 0, 0, '122729 123236'), -- Mystic Birdhat - 122729 - Grand Expedition Yak, 123236 - Grummle Booth A - !!! on transport - transport template not found !!!
-- (@CGUID+491, 0, 0, 0, 1, 0, 0, 0, 0, 0, '122729 123240'), -- Cousin Slowhands - 122729 - Grand Expedition Yak, 123240 - Grummle Booth B - !!! on transport - transport template not found !!!
(@CGUID+492, 0, 17719, 0, 257, 0, 0, 0, 0, 0, ''), -- Orgrimmar Grunt
(@CGUID+495, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Darkspear Headhunter
(@CGUID+498, 0, 0, 1, 257, 0, 0, 0, 0, 0, ''), -- Jandi
(@CGUID+499, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Zeal'aya
(@CGUID+501, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Orgrimmar Grunt
(@CGUID+504, 0, 0, 0, 256, 0, 0, 0, 0, 0, ''), -- Zilzibin Drumlore
(@CGUID+507, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Sarlek
(@CGUID+508, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Tamaro
(@CGUID+509, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Brunda
(@CGUID+511, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Muraga
(@CGUID+512, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Orgrimmar Grunt
-- (@CGUID+513, 0, 0, 0, 1, 0, 0, 0, 0, 0, '122729 123236'), -- Mystic Birdhat - 122729 - Grand Expedition Yak, 123236 - Grummle Booth A - !!! on transport - transport template not found !!!
-- (@CGUID+514, 0, 0, 0, 1, 0, 0, 0, 0, 0, '122729 123240'), -- Cousin Slowhands - 122729 - Grand Expedition Yak, 123240 - Grummle Booth B - !!! on transport - transport template not found !!!
(@CGUID+516, 0, 0, 0, 1, 0, 0, 0, 0, 0, '296495'), -- Jack the Hammer - 296495 - -0-
(@CGUID+517, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Orgrimmar Grunt
(@CGUID+518, 0, 0, 0, 0, 0, 0, 0, 0, 0, ''), -- Orgrimmar Grunt
(@CGUID+519, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Orgrimmar Grunt
(@CGUID+522, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Godan
(@CGUID+523, 0, 0, 0, 0, 0, 0, 0, 0, 0, ''), -- Boss Magor
(@CGUID+526, 0, 0, 0, 0, 0, 0, 0, 0, 0, ''), -- Orgrimmar Grunt
(@CGUID+527, 0, 0, 0, 1, 0, 16996, 0, 0, 0, '374211'), -- Quizla Blastcaps - 374211 - -0-
(@CGUID+528, 0, 0, 0, 257, 0, 0, 0, 0, 0, '79865'), -- Flekky Nox - 79865 - Frost Armor
(@CGUID+529, 0, 0, 0, 258, 0, 0, 0, 0, 0, '94218'), -- Zazzle - 94218 - Grit's Flamethrower Backpack
(@CGUID+530, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Kithas
(@CGUID+531, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Enchanter Farendin
(@CGUID+532, 0, 0, 0, 256, 0, 0, 0, 0, 0, ''), -- Orgrimmar Grunt
(@CGUID+533, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Jhag
(@CGUID+534, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Morgum
(@CGUID+535, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Tamar
(@CGUID+536, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Orgrimmar Grunt
(@CGUID+537, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Kor'geld
(@CGUID+538, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Yelmak
(@CGUID+539, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Magenius
(@CGUID+540, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Jes'rimon
(@CGUID+541, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Kamari
(@CGUID+542, 0, 0, 0, 1, 0, 0, 0, 0, 0, '65985'), -- Corrupted Mottled Boar - 65985 - Permanent Feign Death (Root Silence Pacify)
(@CGUID+543, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Orgrimmar Grunt
(@CGUID+544, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Thuwd
(@CGUID+545, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Dran Droffers
(@CGUID+546, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Malton Droffers
(@CGUID+547, 0, 0, 0, 1, 0, 0, 0, 0, 0, '221098'), -- Worker - 221098 - Sleeping Sleep
(@CGUID+548, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Asoran
(@CGUID+549, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Handor
(@CGUID+550, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Karolek
(@CGUID+554, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Orgrimmar Grunt
(@CGUID+555, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Snang
(@CGUID+556, 0, 0, 0, 256, 0, 0, 0, 0, 0, ''), -- Orgrimmar Grunt
(@CGUID+557, 0, 0, 0, 1, 0, 0, 0, 0, 0, '98892 61573'), -- Training Dummy - 98892 - Training Dummy Marker, 61573 - Banner of the Alliance
(@CGUID+559, 0, 0, 0, 1, 0, 0, 0, 0, 0, '296495'), -- Jack the Hammer - 296495 - -0-
(@CGUID+562, 0, 0, 0, 1, 0, 16996, 0, 0, 0, '374211'), -- Quizla Blastcaps - 374211 - -0-
(@CGUID+564, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Orgrimmar Grunt
(@CGUID+565, 0, 0, 0, 256, 0, 0, 0, 0, 0, ''), -- Orgrimmar Grunt
(@CGUID+566, 0, 0, 1, 257, 0, 0, 0, 0, 0, ''), -- Orgrimmar Grunt
(@CGUID+569, 0, 0, 0, 1, 0, 0, 0, 0, 0, '98892 61573'), -- Raider's Training Dummy - 98892 - Training Dummy Marker, 61573 - Banner of the Alliance
(@CGUID+571, 0, 0, 0, 1, 0, 0, 0, 0, 0, '98892 61573'), -- Training Dummy - 98892 - Training Dummy Marker, 61573 - Banner of the Alliance
(@CGUID+572, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Thunder Bluff Protector
(@CGUID+573, 0, 0, 0, 1, 0, 0, 0, 0, 0, '98892 61573'), -- Training Dummy - 98892 - Training Dummy Marker, 61573 - Banner of the Alliance
(@CGUID+575, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Darkspear Headhunter
(@CGUID+576, 0, 0, 0, 1, 0, 0, 0, 0, 0, '98892 61573'), -- Raider's Training Dummy - 98892 - Training Dummy Marker, 61573 - Banner of the Alliance
(@CGUID+587, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Orgrimmar Grunt
(@CGUID+588, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Pank
(@CGUID+589, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Kiro
-- (@CGUID+590, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, '46598'), -- Hyper-Compressed Ocean Target - 46598 - Ride Vehicle Hardcoded - !!! on transport - transport template not found !!!
(@CGUID+592, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Orgrimmar Grunt
(@CGUID+593, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Vink
(@CGUID+594, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Vuvanzi
(@CGUID+595, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Orgrimmar Grunt
(@CGUID+596, 0, 0, 1, 1, 0, 0, 0, 0, 0, ''), -- Olive
(@CGUID+599, 0, 0, 1, 257, 0, 0, 0, 0, 0, '116562'), -- Rok'kal - 116562 - Fishing
(@CGUID+601, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Fibi
(@CGUID+602, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Orgrimmar Grunt
(@CGUID+604, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Binzella
(@CGUID+606, 0, 0, 0, 0, 0, 0, 0, 0, 0, ''), -- Orgrimmar Grunt
(@CGUID+607, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Innkeeper Nufa
(@CGUID+608, 0, 0, 0, 0, 0, 0, 0, 0, 0, ''), -- Orgrimmar Grunt
(@CGUID+610, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Herezegor Flametusk
(@CGUID+611, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Lumak
(@CGUID+618, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Gravy
(@CGUID+619, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Shankys
(@CGUID+623, 0, 0, 0, 0, 0, 0, 0, 0, 0, ''), -- Cataloger Kieule
(@CGUID+624, 0, 0, 0, 0, 0, 0, 0, 0, 0, ''), -- Chronicler Laz'Kini
(@CGUID+627, 0, 0, 0, 1, 0, 0, 0, 0, 0, '98892 61573'), -- Training Dummy - 98892 - Training Dummy Marker, 61573 - Banner of the Alliance
(@CGUID+632, 0, 0, 0, 1, 0, 0, 0, 0, 0, '79976'), -- Avaros Dawnglaive - 79976 - Retribution Aura
(@CGUID+634, 0, 0, 1, 257, 0, 0, 0, 0, 0, ''), -- Softpaws
(@CGUID+636, 0, 0, 0, 1, 0, 0, 0, 0, 0, '98892 61573'), -- Training Dummy - 98892 - Training Dummy Marker, 61573 - Banner of the Alliance
(@CGUID+637, 0, 0, 0, 1, 0, 0, 0, 0, 0, '24983'), -- Murky - 24983 - Baby Murloc Passive
(@CGUID+639, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Great Green Dragon Turtle
(@CGUID+640, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Orgrimmar Grunt
(@CGUID+641, 0, 0, 0, 256, 0, 0, 0, 0, 0, '79064'), -- Blademaster Ronakada - 79064 - Horde Banner
(@CGUID+644, 0, 0, 0, 256, 0, 0, 0, 0, 0, ''), -- Karg Skullgore
(@CGUID+645, 0, 0, 0, 256, 0, 0, 0, 0, 0, '12544'), -- Karba Blazemaw - 12544 - Frost Armor
(@CGUID+646, 0, 0, 1, 256, 0, 0, 0, 0, 0, ''), -- Sorek
(@CGUID+648, 0, 0, 0, 0, 0, 0, 0, 0, 0, ''), -- Slahtz
(@CGUID+649, 0, 0, 0, 1, 0, 0, 0, 0, 0, '79892'), -- Hretar Riverspeaker - 79892 - Water Shield
(@CGUID+651, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Frostwolf Ambassador Rokhstrom
(@CGUID+654, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Orgrimmar Grunt
(@CGUID+655, 0, 0, 0, 1, 0, 0, 0, 0, 0, '61573 98892'), -- Training Dummy - 61573 - Banner of the Alliance, 98892 - Training Dummy Marker
(@CGUID+656, 0, 0, 0, 1, 0, 0, 0, 0, 0, '19231'), -- Luo Luo - 19231 - Panda
(@CGUID+657, 0, 0, 1, 256, 0, 0, 0, 0, 0, ''), -- Grezz Ragefist
(@CGUID+658, 0, 0, 0, 1, 0, 0, 0, 0, 0, '98892 61573'), -- Training Dummy - 98892 - Training Dummy Marker, 61573 - Banner of the Alliance
(@CGUID+661, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Red Dragon Turtle
(@CGUID+662, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Disciple Jusi
(@CGUID+664, 0, 0, 0, 1, 0, 0, 0, 0, 0, '98892 61573'), -- Raider's Training Dummy - 98892 - Training Dummy Marker, 61573 - Banner of the Alliance
(@CGUID+665, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Alpheus Cain
(@CGUID+666, 0, 0, 0, 1, 0, 0, 0, 0, 0, '98892 61573'), -- Training Dummy - 98892 - Training Dummy Marker, 61573 - Banner of the Alliance
(@CGUID+667, 0, 0, 0, 1, 0, 0, 0, 0, 0, '79849'), -- Feenix Arcshine - 79849 - Molten Armor
(@CGUID+669, 0, 0, 0, 1, 0, 0, 0, 0, 0, '98892 61573'), -- Training Dummy - 98892 - Training Dummy Marker, 61573 - Banner of the Alliance
(@CGUID+673, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Razgar
(@CGUID+676, 0, 0, 8, 257, 0, 0, 0, 0, 0, ''), -- Dranosh'ar Laborer
(@CGUID+677, 0, 0, 8, 257, 0, 0, 0, 0, 0, ''), -- Dranosh'ar Laborer
(@CGUID+679, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Dranosh'ar Laborer
(@CGUID+681, 0, 0, 0, 256, 0, 0, 0, 0, 0, ''), -- Sen'jin Villager
-- (@CGUID+682, 0, 0, 0, 1, 0, 0, 0, 0, 4, ''), -- The Defiant Dragonscale - !!! on transport - transport template not found !!!
(@CGUID+683, 0, 2328, 0, 257, 0, 0, 0, 0, 4, ''), -- Holgar Stormaxe
-- (@CGUID+687, 0, 0, 0, 257, 0, 0, 0, 0, 4, '372498'), -- Captain Caspartine - 372498 - -0- - !!! on transport - transport template not found !!!
(@CGUID+689, 0, 0, 0, 256, 0, 0, 0, 0, 0, ''), -- Concerned Citizen
(@CGUID+693, 0, 0, 0, 1, 0, 0, 0, 0, 0, '20798'), -- Gazz'uz - 20798 - Demon Skin
-- (@CGUID+697, 0, 0, 50331648, 1, 0, 0, 0, 0, 4, ''), -- (Bunny) Sessile + Gigantic AOI - !!! on transport - transport template not found !!!
(@CGUID+698, 0, 0, 0, 1, 0, 0, 0, 0, 0, '79934'), -- Felweaver Scornn - 79934 - Demon Armor
(@CGUID+699, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Citizen of Kezan
(@CGUID+701, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Silvermoon Citizen
(@CGUID+704, 0, 0, 0, 0, 0, 0, 0, 0, 0, ''), -- Thunder Bluff Native
(@CGUID+705, 0, 0, 0, 256, 0, 0, 0, 0, 0, ''), -- Concerned Citizen
(@CGUID+706, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Citizen of Kezan
(@CGUID+708, 0, 0, 0, 256, 0, 0, 0, 0, 0, ''), -- Silvermoon Citizen
(@CGUID+709, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Sen'jin Villager
(@CGUID+712, 0, 0, 0, 0, 0, 0, 0, 0, 0, ''), -- Thunder Bluff Native
(@CGUID+718, 0, 0, 0, 0, 0, 0, 0, 0, 0, ''), -- Thunder Bluff Native
(@CGUID+719, 0, 0, 0, 256, 0, 0, 0, 0, 0, ''), -- Concerned Citizen
(@CGUID+720, 0, 0, 0, 256, 0, 0, 0, 0, 0, ''), -- Citizen of Kezan
(@CGUID+722, 0, 0, 0, 256, 0, 0, 0, 0, 0, ''), -- Sen'jin Villager
(@CGUID+723, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Dranosh'ar Laborer
(@CGUID+724, 0, 0, 0, 256, 0, 0, 0, 0, 0, ''), -- Concerned Citizen
(@CGUID+726, 0, 0, 0, 256, 0, 0, 0, 0, 0, ''), -- Silvermoon Citizen
(@CGUID+729, 0, 0, 0, 256, 0, 0, 0, 0, 0, ''), -- Concerned Citizen
(@CGUID+730, 0, 0, 0, 1, 0, 0, 0, 0, 0, '372740'), -- Brave Researcher - 372740 - -0-
(@CGUID+731, 0, 0, 0, 1, 0, 0, 0, 0, 0, '374319'), -- Rugged Artisan - 374319 - -0-
(@CGUID+732, 0, 0, 0, 1, 0, 0, 0, 0, 0, '374107'), -- Brave Researcher - 374107 - -0-
(@CGUID+733, 0, 0, 0, 1, 0, 0, 0, 0, 0, '374107'), -- Brave Researcher - 374107 - -0-
-- (@CGUID+738, 0, 0, 0, 257, 0, 0, 0, 0, 0, '384573'), -- Airship Worker - 384573 - -0- - !!! on transport - transport template not found !!!
(@CGUID+739, 0, 0, 0, 1, 0, 0, 0, 0, 0, '372737'), -- Expedition Supplier - 372737 - -0-
(@CGUID+741, 0, 0, 0, 1, 0, 0, 0, 0, 0, '372729'), -- Expedition Supplier - 372729 - -0-
(@CGUID+742, 0, 0, 0, 0, 0, 0, 0, 0, 0, ''), -- Boss Magor
(@CGUID+743, 0, 0, 0, 1, 0, 0, 0, 0, 0, '372471'), -- Restless Explorer - 372471 - -0-
(@CGUID+745, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Seagull
(@CGUID+746, 0, 0, 0, 1, 0, 0, 0, 0, 0, '374209'), -- Rugged Artisan - 374209 - -0-
(@CGUID+747, 0, 0, 0, 1, 0, 0, 0, 0, 0, '374128'), -- Restless Explorer - 374128 - -0-
(@CGUID+749, 0, 0, 0, 0, 0, 0, 0, 0, 0, '378042'), -- Naleidea Rivergleam - 378042 - -0-
(@CGUID+752, 0, 0, 0, 0, 0, 25783, 0, 0, 0, ''), -- Skarukaru
(@CGUID+753, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Dranosh'ar Laborer
(@CGUID+757, 0, 0, 0, 1, 0, 0, 0, 0, 0, '374128'), -- Restless Explorer - 374128 - -0-
(@CGUID+759, 0, 0, 0, 1, 0, 0, 0, 0, 0, '372471'), -- Restless Explorer - 372471 - -0-
-- (@CGUID+762, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Dahanu Highwing - !!! on transport - transport template not found !!!
-- (@CGUID+763, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Dragon Kite - !!! on transport - transport template not found !!!
-- (@CGUID+764, 0, 0, 0, 257, 0, 0, 0, 0, 0, '384573'), -- Airship Worker - 384573 - -0- - !!! on transport - transport template not found !!!
(@CGUID+770, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Dranosh'ar Laborer
(@CGUID+772, 0, 0, 8, 257, 0, 0, 0, 0, 0, ''), -- Dranosh'ar Laborer
(@CGUID+773, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Dranosh'ar Laborer
-- (@CGUID+779, 0, 0, 0, 256, 0, 0, 0, 0, 0, '369560'), -- Trauga Bloodhelm - 369560 - -0- - !!! on transport - transport template not found !!!
-- (@CGUID+780, 0, 0, 0, 256, 0, 0, 0, 0, 0, ''), -- Mathog Hideflayer - !!! on transport - transport template not found !!!
-- (@CGUID+782, 0, 0, 0, 257, 0, 0, 0, 0, 0, '369706'), -- Arandil Featherdawn - 369706 - -0- - !!! on transport - transport template not found !!!
(@CGUID+786, 0, 90766, 0, 1, 0, 0, 0, 0, 0, ''), -- Neri Sharpfin
-- (@CGUID+787, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Rinka - !!! on transport - transport template not found !!!
-- (@CGUID+788, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Rathamaresh - !!! on transport - transport template not found !!!
-- (@CGUID+789, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Airship Worker - !!! on transport - transport template not found !!!
-- (@CGUID+790, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Talanath Goldcrest - !!! on transport - transport template not found !!!
-- (@CGUID+792, 0, 0, 0, 257, 0, 0, 0, 0, 0, '384513'), -- Vernell Bartlett - 384513 - -0- - !!! on transport - transport template not found !!!
-- (@CGUID+794, 0, 0, 0, 257, 0, 0, 0, 0, 0, '372741'), -- Airship Worker - 372741 - -0- - !!! on transport - transport template not found !!!
-- (@CGUID+795, 0, 0, 0, 256, 0, 14580, 0, 0, 0, ''), -- Zalanti - !!! on transport - transport template not found !!!
-- (@CGUID+797, 0, 0, 8, 257, 0, 0, 0, 0, 0, ''), -- Si'va - !!! on transport - transport template not found !!!
(@CGUID+798, 0, 0, 0, 0, 0, 0, 0, 0, 0, ''), -- Poen Gillbrack
(@CGUID+799, 0, 0, 0, 0, 0, 0, 0, 0, 0, ''); -- Vim Brineheart

INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `aiAnimKit`, `movementAnimKit`, `meleeAnimKit`, `visibilityDistanceType`, `auras`) VALUES
(@CGUID+800, 0, 0, 8, 1, 0, 0, 0, 0, 0, ''), -- Friend Pronk
-- (@CGUID+801, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Airship Worker - !!! on transport - transport template not found !!!
-- (@CGUID+802, 0, 0, 0, 256, 0, 0, 0, 0, 0, ''), -- Quartermaster Furlein - !!! on transport - transport template not found !!!
-- (@CGUID+805, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Krakz Cloudgrease - !!! on transport - transport template not found !!!
-- (@CGUID+806, 0, 0, 0, 257, 0, 0, 0, 0, 0, '386130'), -- Lux Fizzlegig - 386130 - -0- - !!! on transport - transport template not found !!!
-- (@CGUID+809, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Airship Worker - !!! on transport - transport template not found !!!
-- (@CGUID+810, 0, 0, 0, 257, 0, 0, 0, 0, 0, '272990'), -- Airship Worker - 272990 - -0- - !!! on transport - transport template not found !!!
-- (@CGUID+812, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Airship Worker - !!! on transport - transport template not found !!!
-- (@CGUID+816, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Shin Summerhill - !!! on transport - transport template not found !!!
-- (@CGUID+817, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Ketuna Skyflame - !!! on transport - transport template not found !!!
(@CGUID+821, 0, 0, 0, 0, 0, 0, 0, 0, 0, '152821'), -- Archmage Khadgar - 152821 - Invisible Man Transform
(@CGUID+823, 0, 0, 0, 1, 0, 0, 0, 0, 0, '378042'), -- Naleidea Rivergleam - 378042 - -0-
(@CGUID+825, 0, 0, 0, 0, 0, 0, 0, 0, 0, ''), -- Archmage Khadgar
(@CGUID+829, 0, 0, 3, 257, 0, 0, 0, 0, 0, '55701'); -- Dranosh'ar Laborer - 55701 - Cosmetic - Sleep Zzz Breakable

DELETE FROM `gameobject` WHERE `guid` BETWEEN @OGUID+0 AND @OGUID+367;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnDifficulties`, `PhaseId`, `PhaseGroup`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `VerifiedBuild`) VALUES
(@OGUID+0, 223814, 1, 1637, 5170, '0', '0', 0, 1476.76318359375, -4418.4150390625, 25.47278594970703125, 0.113445065915584564, 0, 0, 0.056692123413085937, 0.998391687870025634, 120, 255, 0, 45505), -- Doodad_OGRaid_FrontGate_Back (Area: Valley of Strength - Difficulty: 0)
(@OGUID+1, 204213, 1, 1637, 5170, '0', '0', 0, 1541.7603759765625, -4411.75, 18.03300094604492187, 0.366325199604034423, 0.022677898406982421, -0.00975227355957031, 0.182361602783203125, 0.982921600341796875, 120, 255, 1, 45505), -- Brazier (Area: Valley of Strength - Difficulty: 0)
(@OGUID+2, 204647, 1, 1637, 5170, '0', '0', 0, 1480.9228515625, -4435.85302734375, 77.544647216796875, 5.535692214965820312, 0.050455570220947265, 0.026835441589355468, -0.3660135269165039, 0.928853154182434082, 120, 255, 1, 45505), -- Bonfire (Area: Valley of Strength - Difficulty: 0)
(@OGUID+3, 204650, 1, 1637, 5170, '0', '0', 0, 1444.8687744140625, -4429.4345703125, 21.53079986572265625, 3.197998285293579101, 0, 0, -0.99960231781005859, 0.028199035674333572, 120, 255, 1, 45505), -- Fire Pit (Area: Valley of Strength - Difficulty: 0)
(@OGUID+4, 204651, 1, 1637, 5170, '0', '0', 0, 1453.132568359375, -4416.236328125, 25.37168121337890625, 4.823145866394042968, 0, 0, -0.66688442230224609, 0.745161175727844238, 120, 255, 1, 45505), -- Fire Pit (Area: Valley of Strength - Difficulty: 0)
(@OGUID+5, 205108, 1, 1637, 5170, '0', '0', 0, 1521.7017822265625, -4365.11962890625, 20.5829315185546875, 1.073378324508666992, 0, 0, 0.511293411254882812, 0.859406232833862304, 120, 255, 1, 45505), -- Guild Vault (Area: Valley of Strength - Difficulty: 0)
(@OGUID+6, 205109, 1, 1637, 5170, '0', '0', 0, 1529.7437744140625, -4350.30810546875, 20.5829315185546875, 4.214973926544189453, 0, 0, -0.859405517578125, 0.51129460334777832, 120, 255, 1, 45505), -- Guild Vault (Area: Valley of Strength - Difficulty: 0)
(@OGUID+7, 204201, 1, 1637, 5170, '0', '0', 0, 1580.970458984375, -4400.859375, 15.56239986419677734, 2.985360383987426757, 0.02144479751586914, 0.004129409790039062, 0.996722221374511718, 0.077896550297737121, 120, 255, 1, 45505), -- Brazier (Area: Valley of Strength - Difficulty: 0)
(@OGUID+8, 204202, 1, 1637, 5170, '0', '0', 0, 1553.439208984375, -4408.84033203125, 17.43939971923828125, 1.954571723937988281, 0.022496700286865234, 0.0136871337890625, 0.8288421630859375, 0.55886244773864746, 120, 255, 1, 45505), -- Brazier (Area: Valley of Strength - Difficulty: 0)
(@OGUID+9, 204600, 1, 1637, 5170, '0', '0', 0, 1598.9027099609375, -4367.609375, 50.11901092529296875, 3.625617742538452148, 0, 0, -0.97085762023925781, 0.239656955003738403, 120, 255, 1, 45505), -- Torch (Area: Valley of Strength - Difficulty: 0)
(@OGUID+10, 204601, 1, 1637, 5170, '0', '0', 0, 1609.23193359375, -4387.244140625, 50.11901092529296875, 3.625617742538452148, 0, 0, -0.97085762023925781, 0.239656955003738403, 120, 255, 1, 45505), -- Torch (Area: Valley of Strength - Difficulty: 0)
(@OGUID+11, 204207, 1, 1637, 5170, '0', '0', 0, 1575.7291259765625, -4335.859375, 21.70960044860839843, 1.069890737533569335, 0.008472919464111328, 0.008359909057617187, 0.509729385375976562, 0.860252439975738525, 120, 255, 1, 45505), -- Brazier (Area: Valley of Strength - Difficulty: 0)
(@OGUID+12, 204602, 1, 1637, 5170, '0', '0', 0, 1617.7686767578125, -4353.26123046875, 58.1649322509765625, 3.625617742538452148, 0, 0, -0.97085762023925781, 0.239656955003738403, 120, 255, 1, 45505), -- Torch (Area: Valley of Strength - Difficulty: 0)
(@OGUID+13, 204208, 1, 1637, 5170, '0', '0', 0, 1560.0208740234375, -4358.4599609375, 18.34234046936035156, 1.635905623435974121, 0.024140834808349609, -0.02702713012695312, 0.729188919067382812, 0.683352231979370117, 120, 255, 1, 45505), -- Brazier (Area: Valley of Strength - Difficulty: 0)
(@OGUID+14, 204603, 1, 1637, 5170, '0', '0', 0, 1631.673095703125, -4379.31396484375, 58.1649322509765625, 3.625617742538452148, 0, 0, -0.97085762023925781, 0.239656955003738403, 120, 255, 1, 45505), -- Torch (Area: Valley of Strength - Difficulty: 0)
(@OGUID+15, 204662, 1, 1637, 5170, '0', '0', 0, 1472.22314453125, -4369.646484375, 77.90445709228515625, 5.532454967498779296, 0, 0, -0.36661243438720703, 0.930373787879943847, 120, 255, 1, 45505), -- Bonfire (Area: Valley of Strength - Difficulty: 0)
(@OGUID+16, 204210, 1, 1637, 5170, '0', '0', 0, 1624.529541015625, -4403.640625, 15.17715167999267578, 0.169216230511665344, 0.015128612518310546, -0.00515174865722656, 0.084589958190917968, 0.996287643909454345, 120, 255, 1, 45505), -- Brazier (Area: Valley of Strength - Difficulty: 0)
(@OGUID+17, 204663, 1, 1637, 5170, '0', '0', 0, 1491.4395751953125, -4432.83642578125, 30.35234832763671875, 0.113445065915584564, 0, 0, 0.056692123413085937, 0.998391687870025634, 120, 255, 1, 45505), -- Sconce (Area: Valley of Strength - Difficulty: 0)
(@OGUID+18, 204211, 1, 1637, 5170, '0', '0', 0, 1576.3802490234375, -4415.3193359375, 15.20740127563476562, 1.708440184593200683, 0.024060726165771484, 0.0095672607421875, 0.753985404968261718, 0.656380712985992431, 120, 255, 1, 45505), -- Brazier (Area: Valley of Strength - Difficulty: 0)
(@OGUID+19, 204664, 1, 1637, 5170, '0', '0', 0, 1487.47412109375, -4401.37109375, 30.29399299621582031, 0.113445065915584564, 0, 0, 0.056692123413085937, 0.998391687870025634, 120, 255, 1, 45505), -- Sconce (Area: Valley of Strength - Difficulty: 0)
(@OGUID+20, 204212, 1, 1637, 5170, '0', '0', 0, 1540.2100830078125, -4399.55029296875, 18.08880043029785156, 5.078719615936279296, 0.013491630554199218, -0.02261543273925781, -0.566070556640625, 0.823936104774475097, 120, 255, 1, 45505), -- Brazier (Area: Valley of Strength - Difficulty: 0)
(@OGUID+21, 204214, 1, 1637, 5170, '0', '0', 0, 1630.079833984375, -4422.69091796875, 15.33180046081542968, 1.588251471519470214, 0, 0, 0.713251113891601562, 0.700908601284027099, 120, 255, 1, 45505), -- Brazier (Area: Valley of Strength - Difficulty: 0)
(@OGUID+22, 204215, 1, 1637, 5170, '0', '0', 0, 1613.5504150390625, -4437.5693359375, 13.10140037536621093, 1.457348585128784179, 0, 0, 0.665881156921386718, 0.746057868003845214, 120, 255, 1, 45505), -- Brazier (Area: Valley of Strength - Difficulty: 0)
(@OGUID+23, 206725, 1, 1637, 5170, '0', '0', 0, 1607.1597900390625, -4381.77099609375, 20.79739952087402343, 2.993224143981933593, 0, 0, 0.997249603271484375, 0.074116282165050506, 120, 255, 1, 45505), -- Mailbox (Area: Valley of Strength - Difficulty: 0)
(@OGUID+24, 204163, 1, 1637, 5170, '0', '0', 0, 1504.69970703125, -4447.3994140625, 25.09849929809570312, 3.743737697601318359, 0, 0, -0.95501899719238281, 0.296544641256332397, 120, 255, 1, 45505), -- Bonfire (Area: Valley of Strength - Difficulty: 0)
(@OGUID+25, 206726, 1, 1637, 5170, '0', '0', 0, 1607.6805419921875, -4424.80908203125, 13.60109996795654296, 3.918267250061035156, 0, 0, -0.92553997039794921, 0.378649920225143432, 120, 255, 1, 45505), -- Mailbox (Area: Valley of Strength - Difficulty: 0)
(@OGUID+26, 206610, 1, 1637, 5170, '0', '0', 0, 1755.3138427734375, -4396.5966796875, 42.3477935791015625, 3.744939327239990234, 0, 0, -0.95484066009521484, 0.297118335962295532, 120, 255, 24, 45505), -- 0 (Area: Valley of Strength - Difficulty: 0)
(@OGUID+27, 223739, 1, 1637, 5170, '0', '0', 0, 1395.5986328125, -4368.45654296875, 25.47356033325195312, 3.255058050155639648, 0, 0, -0.99839115142822265, 0.056702151894569396, 120, 255, 0, 45505), -- The Gates of Orgrimmar (Area: Valley of Strength - Difficulty: 0)
(@OGUID+28, 206727, 1, 1637, 5170, '0', '0', 0, 1547.69970703125, -4363.8505859375, 17.51819992065429687, 2.146752834320068359, 0, 0, 0.878816604614257812, 0.477159708738327026, 120, 255, 1, 45505), -- Mailbox (Area: Valley of Strength - Difficulty: 0)
(@OGUID+29, 206608, 1, 1637, 5170, '0', '0', 0, 1704.7816162109375, -4265.9599609375, 34.88367843627929687, 3.976282596588134765, 0, 0, -0.91416835784912109, 0.405334681272506713, 120, 255, 24, 45505), -- 0 (Area: Valley of Strength - Difficulty: 0)
(@OGUID+30, 206609, 1, 1637, 5170, '0', '0', 0, 1902.046142578125, -4373.10302734375, 43.99676895141601562, 5.707206249237060546, 0, 0, -0.28402519226074218, 0.958816826343536376, 120, 255, 24, 45505), -- 0 (Area: Valley of Strength - Difficulty: 0)
(@OGUID+31, 205142, 1, 1637, 5170, '0', '0', 0, 1522.6199951171875, -4345.60009765625, 20.54870033264160156, 4.206246376037597656, 0, 0, -0.86162853240966796, 0.50753939151763916, 120, 255, 1, 45505), -- Generic Human Chair Low End - Prop (Unusable) (Area: Valley of Strength - Difficulty: 0)
(@OGUID+32, 180007, 1, 1637, 5170, '0', '0', 0, 1604.01220703125, -4359.47216796875, 21.1196746826171875, 0, 0, 0, 0, 1, 120, 255, 1, 45505), -- Excavation Stake (Area: Valley of Strength - Difficulty: 0)
(@OGUID+33, 205142, 1, 1637, 5170, '0', '0', 0, 1513.3699951171875, -4346.58984375, 20.66990089416503906, 5.6897735595703125, 0, 0, -0.29237174987792968, 0.956304728984832763, 120, 255, 1, 45505), -- Generic Human Chair Low End - Prop (Unusable) (Area: Valley of Strength - Difficulty: 0)
(@OGUID+34, 180007, 1, 1637, 5170, '0', '0', 0, 1607.0677490234375, -4355.26904296875, 21.11966896057128906, 0, 0, 0, 0, 1, 120, 255, 1, 45505), -- Excavation Stake (Area: Valley of Strength - Difficulty: 0)
(@OGUID+35, 205142, 1, 1637, 5170, '0', '0', 0, 1509.72998046875, -4352.85986328125, 20.66990089416503906, 5.759587764739990234, 0, 0, -0.25881862640380859, 0.965925931930541992, 120, 255, 1, 45505), -- Generic Human Chair Low End - Prop (Unusable) (Area: Valley of Strength - Difficulty: 0)
(@OGUID+36, 203969, 1, 1637, 5170, '0', '0', 0, 1566.736083984375, -4376.125, 16.24643898010253906, 1.343901276588439941, 0, 0, 0.622513771057128906, 0.78260880708694458, 120, 255, 1, 45505), -- Prickly Pear Fruit (Area: Valley of Strength - Difficulty: 0)
(@OGUID+37, 376794, 1, 1637, 5170, '0', '0', 0, 1565.2603759765625, -4482.171875, 72.77443695068359375, 1.395826101303100585, 0, 0, 0.642620086669921875, 0.766184985637664794, 120, 255, 1, 45505), -- Crates (Area: Valley of Strength - Difficulty: 0)
(@OGUID+38, 223814, 1, 1637, 5170, '0', '0', 0, 1476.76318359375, -4418.4150390625, 25.47278594970703125, 0.113445065915584564, 0, 0, 0.056692123413085937, 0.998391687870025634, 120, 255, 0, 45505), -- Doodad_OGRaid_FrontGate_Back (Area: Valley of Strength - Difficulty: 0)
(@OGUID+39, 204647, 1, 1637, 5170, '0', '0', 0, 1480.9228515625, -4435.85302734375, 77.544647216796875, 5.535692214965820312, 0.050455570220947265, 0.026835441589355468, -0.3660135269165039, 0.928853154182434082, 120, 255, 1, 45505), -- Bonfire (Area: Valley of Strength - Difficulty: 0)
(@OGUID+40, 376514, 1, 1637, 5170, '0', '0', 0, 1607.296875, -4451.99658203125, 13.101348876953125, 0, 0, 0, 0, 1, 120, 255, 1, 45505), -- Sleeping Mat (Area: Valley of Strength - Difficulty: 0)
(@OGUID+41, 376794, 1, 1637, 5170, '0', '0', 0, 1544.6129150390625, -4480.70849609375, 72.88687896728515625, 1.395826101303100585, 0, 0, 0.642620086669921875, 0.766184985637664794, 120, 255, 1, 45505), -- Crates (Area: Valley of Strength - Difficulty: 0)
(@OGUID+42, 204650, 1, 1637, 5170, '0', '0', 0, 1444.8687744140625, -4429.4345703125, 21.53079986572265625, 3.197998285293579101, 0, 0, -0.99960231781005859, 0.028199035674333572, 120, 255, 1, 45505), -- Fire Pit (Area: Valley of Strength - Difficulty: 0)
-- (@OGUID+43, 186238, 1, 1637, 5170, '0', '0', 0, 0, 0, 0, 3.868974208831787109, 0, 0, -0.93459033966064453, 0.355725884437561035, 120, 255, 1, 45505), -- 0 (Area: Valley of Strength - Difficulty: 0) - !!! transport !!!
(@OGUID+44, 205108, 1, 1637, 5170, '0', '0', 0, 1521.7017822265625, -4365.11962890625, 20.5829315185546875, 1.073378324508666992, 0, 0, 0.511293411254882812, 0.859406232833862304, 120, 255, 1, 45505), -- Guild Vault (Area: Valley of Strength - Difficulty: 0)
(@OGUID+45, 376796, 1, 1637, 5170, '0', '0', 0, 1556.1978759765625, -4477.64404296875, 73.0437469482421875, 1.749738931655883789, 0, 0, 0.767459869384765625, 0.641097009181976318, 120, 255, 1, 45505), -- Tent (Area: Valley of Strength - Difficulty: 0)
(@OGUID+46, 205109, 1, 1637, 5170, '0', '0', 0, 1529.7437744140625, -4350.30810546875, 20.5829315185546875, 4.214973926544189453, 0, 0, -0.859405517578125, 0.51129460334777832, 120, 255, 1, 45505), -- Guild Vault (Area: Valley of Strength - Difficulty: 0)
(@OGUID+47, 204201, 1, 1637, 5170, '0', '0', 0, 1580.970458984375, -4400.859375, 15.56239986419677734, 2.985360383987426757, 0.02144479751586914, 0.004129409790039062, 0.996722221374511718, 0.077896550297737121, 120, 255, 1, 45505), -- Brazier (Area: Valley of Strength - Difficulty: 0)
(@OGUID+48, 204202, 1, 1637, 5170, '0', '0', 0, 1553.439208984375, -4408.84033203125, 17.43939971923828125, 1.954571723937988281, 0.022496700286865234, 0.0136871337890625, 0.8288421630859375, 0.55886244773864746, 120, 255, 1, 45505), -- Brazier (Area: Valley of Strength - Difficulty: 0)
(@OGUID+49, 376803, 1, 1637, 5170, '0', '0', 0, 1558.7742919921875, -4470.53125, 73.4806365966796875, 1.72045755386352539, 0, 0, 0.757991790771484375, 0.652264058589935302, 120, 255, 1, 45505), -- Banner (Area: Valley of Strength - Difficulty: 0)
(@OGUID+50, 204600, 1, 1637, 5170, '0', '0', 0, 1598.9027099609375, -4367.609375, 50.11901092529296875, 3.625617742538452148, 0, 0, -0.97085762023925781, 0.239656955003738403, 120, 255, 1, 45505), -- Torch (Area: Valley of Strength - Difficulty: 0)
(@OGUID+51, 376803, 1, 1637, 5170, '0', '0', 0, 1551.91845703125, -4471.609375, 73.3820953369140625, 1.72045755386352539, 0, 0, 0.757991790771484375, 0.652264058589935302, 120, 255, 1, 45505), -- Banner (Area: Valley of Strength - Difficulty: 0)
(@OGUID+52, 204601, 1, 1637, 5170, '0', '0', 0, 1609.23193359375, -4387.244140625, 50.11901092529296875, 3.625617742538452148, 0, 0, -0.97085762023925781, 0.239656955003738403, 120, 255, 1, 45505), -- Torch (Area: Valley of Strength - Difficulty: 0)
(@OGUID+53, 204207, 1, 1637, 5170, '0', '0', 0, 1575.7291259765625, -4335.859375, 21.70960044860839843, 1.069890737533569335, 0.008472919464111328, 0.008359909057617187, 0.509729385375976562, 0.860252439975738525, 120, 255, 1, 45505), -- Brazier (Area: Valley of Strength - Difficulty: 0)
(@OGUID+54, 204602, 1, 1637, 5170, '0', '0', 0, 1617.7686767578125, -4353.26123046875, 58.1649322509765625, 3.625617742538452148, 0, 0, -0.97085762023925781, 0.239656955003738403, 120, 255, 1, 45505), -- Torch (Area: Valley of Strength - Difficulty: 0)
(@OGUID+55, 204208, 1, 1637, 5170, '0', '0', 0, 1560.0208740234375, -4358.4599609375, 18.34234046936035156, 1.635905623435974121, 0.024140834808349609, -0.02702713012695312, 0.729188919067382812, 0.683352231979370117, 120, 255, 1, 45505), -- Brazier (Area: Valley of Strength - Difficulty: 0)
(@OGUID+56, 204603, 1, 1637, 5170, '0', '0', 0, 1631.673095703125, -4379.31396484375, 58.1649322509765625, 3.625617742538452148, 0, 0, -0.97085762023925781, 0.239656955003738403, 120, 255, 1, 45505), -- Torch (Area: Valley of Strength - Difficulty: 0)
(@OGUID+57, 203969, 1, 1637, 5170, '0', '0', 0, 1483.6353759765625, -4375.39404296875, 27.01883697509765625, 2.513273954391479492, 0, 0, 0.951056480407714843, 0.309017121791839599, 120, 255, 1, 45505), -- Prickly Pear Fruit (Area: Valley of Strength - Difficulty: 0)
(@OGUID+58, 204662, 1, 1637, 5170, '0', '0', 0, 1472.22314453125, -4369.646484375, 77.90445709228515625, 5.532454967498779296, 0, 0, -0.36661243438720703, 0.930373787879943847, 120, 255, 1, 45505), -- Bonfire (Area: Valley of Strength - Difficulty: 0)
(@OGUID+59, 204210, 1, 1637, 5170, '0', '0', 0, 1624.529541015625, -4403.640625, 15.17715167999267578, 0.169216230511665344, 0.015128612518310546, -0.00515174865722656, 0.084589958190917968, 0.996287643909454345, 120, 255, 1, 45505), -- Brazier (Area: Valley of Strength - Difficulty: 0)
(@OGUID+60, 204663, 1, 1637, 5170, '0', '0', 0, 1491.4395751953125, -4432.83642578125, 30.35234832763671875, 0.113445065915584564, 0, 0, 0.056692123413085937, 0.998391687870025634, 120, 255, 1, 45505), -- Sconce (Area: Valley of Strength - Difficulty: 0)
(@OGUID+61, 204211, 1, 1637, 5170, '0', '0', 0, 1576.3802490234375, -4415.3193359375, 15.20740127563476562, 1.708440184593200683, 0.024060726165771484, 0.0095672607421875, 0.753985404968261718, 0.656380712985992431, 120, 255, 1, 45505), -- Brazier (Area: Valley of Strength - Difficulty: 0)
(@OGUID+62, 204664, 1, 1637, 5170, '0', '0', 0, 1487.47412109375, -4401.37109375, 30.29399299621582031, 0.113445065915584564, 0, 0, 0.056692123413085937, 0.998391687870025634, 120, 255, 1, 45505), -- Sconce (Area: Valley of Strength - Difficulty: 0)
(@OGUID+63, 376419, 1, 1637, 5170, '0', '0', 0, 1464.282958984375, -4501.0712890625, 18.40486335754394531, 3.271494388580322265, 0, 0, -0.99789142608642578, 0.064905144274234771, 120, 255, 1, 45505), -- Under Construction (Area: Valley of Strength - Difficulty: 0)
(@OGUID+64, 204212, 1, 1637, 5170, '0', '0', 0, 1540.2100830078125, -4399.55029296875, 18.08880043029785156, 5.078719615936279296, 0.013491630554199218, -0.02261543273925781, -0.566070556640625, 0.823936104774475097, 120, 255, 1, 45505), -- Brazier (Area: Valley of Strength - Difficulty: 0)
(@OGUID+65, 204213, 1, 1637, 5170, '0', '0', 0, 1541.7603759765625, -4411.75, 18.03300094604492187, 0.366325199604034423, 0.022677898406982421, -0.00975227355957031, 0.182361602783203125, 0.982921600341796875, 120, 255, 1, 45505), -- Brazier (Area: Valley of Strength - Difficulty: 0)
(@OGUID+66, 204214, 1, 1637, 5170, '0', '0', 0, 1630.079833984375, -4422.69091796875, 15.33180046081542968, 1.588251471519470214, 0, 0, 0.713251113891601562, 0.700908601284027099, 120, 255, 1, 45505), -- Brazier (Area: Valley of Strength - Difficulty: 0)
(@OGUID+67, 205142, 1, 1637, 5170, '0', '0', 0, 1514.06005859375, -4361.22998046875, 20.54879951477050781, 1.064649581909179687, 0, 0, 0.507537841796875, 0.861629426479339599, 120, 255, 1, 45505), -- Generic Human Chair Low End - Prop (Unusable) (Area: Valley of Strength - Difficulty: 0)
(@OGUID+68, 204215, 1, 1637, 5170, '0', '0', 0, 1613.5504150390625, -4437.5693359375, 13.10140037536621093, 1.457348585128784179, 0, 0, 0.665881156921386718, 0.746057868003845214, 120, 255, 1, 45505), -- Brazier (Area: Valley of Strength - Difficulty: 0)
(@OGUID+69, 179965, 1, 1637, 5170, '0', '0', 0, 1765.3992919921875, -4346.70166015625, 101.7874526977539062, 0.645771682262420654, 0, 0, 0.317304611206054687, 0.948323667049407958, 120, 255, 1, 45505), -- Darkmoon Faire Banner (Area: Valley of Strength - Difficulty: 0)
(@OGUID+70, 246039, 1, 1637, 5170, '0', '0', 0, 1609.1788330078125, -4374.72216796875, 23.73969841003417968, 0.470744222402572631, 0, 0, 0.233204841613769531, 0.972427666187286376, 120, 255, 1, 45505), -- Protective Barrier (Area: Valley of Strength - Difficulty: 0)
(@OGUID+71, 281340, 1, 1637, 5170, '0', '0', 0, 1600.9896240234375, -4369.73974609375, 21.06940078735351562, 3.630291461944580078, 0, 0, -0.97029495239257812, 0.241925001144409179, 120, 255, 0, 45505), -- Warchief's Command Board (Area: Valley of Strength - Difficulty: 0)
(@OGUID+72, 266354, 1, 1637, 5170, '0', '0', 0, 1603.5838623046875, -4424.0546875, 13.65676498413085937, 3.499690055847167968, 0, 0, -0.98401355743408203, 0.178093522787094116, 120, 255, 1, 45505), -- Basic Campfire (Area: Valley of Strength - Difficulty: 0)
(@OGUID+73, 245730, 1, 1637, 5170, '0', '0', 0, 1609.7760009765625, -4374.2099609375, 23.41293144226074218, 3.613091230392456054, 0, 0, -0.97233963012695312, 0.23357151448726654, 120, 255, 1, 45505), -- Reinforced Gate (Area: Valley of Strength - Difficulty: 0)
(@OGUID+74, 203969, 1, 1637, 5170, '0', '0', 0, 1613.638916015625, -4387.53662109375, 20.9925079345703125, 6.073746204376220703, 0, 0, -0.10452842712402343, 0.994521915912628173, 120, 255, 1, 45505), -- Prickly Pear Fruit (Area: Valley of Strength - Difficulty: 0)
(@OGUID+75, 206725, 1, 1637, 5170, '0', '0', 0, 1607.1597900390625, -4381.77099609375, 20.79739952087402343, 2.993224143981933593, 0, 0, 0.997249603271484375, 0.074116282165050506, 120, 255, 1, 45505), -- Mailbox (Area: Valley of Strength - Difficulty: 0)
(@OGUID+76, 204163, 1, 1637, 5170, '0', '0', 0, 1504.69970703125, -4447.3994140625, 25.09849929809570312, 3.743737697601318359, 0, 0, -0.95501899719238281, 0.296544641256332397, 120, 255, 1, 45505), -- Bonfire (Area: Valley of Strength - Difficulty: 0)
(@OGUID+77, 206726, 1, 1637, 5170, '0', '0', 0, 1607.6805419921875, -4424.80908203125, 13.60109996795654296, 3.918267250061035156, 0, 0, -0.92553997039794921, 0.378649920225143432, 120, 255, 1, 45505), -- Mailbox (Area: Valley of Strength - Difficulty: 0)
(@OGUID+78, 223739, 1, 1637, 5170, '0', '0', 0, 1395.5986328125, -4368.45654296875, 25.47356033325195312, 3.255058050155639648, 0, 0, -0.99839115142822265, 0.056702151894569396, 120, 255, 0, 45505), -- The Gates of Orgrimmar (Area: Valley of Strength - Difficulty: 0)
(@OGUID+79, 206727, 1, 1637, 5170, '0', '0', 0, 1547.69970703125, -4363.8505859375, 17.51819992065429687, 2.146752834320068359, 0, 0, 0.878816604614257812, 0.477159708738327026, 120, 255, 1, 45505), -- Mailbox (Area: Valley of Strength - Difficulty: 0)
(@OGUID+80, 203969, 1, 1637, 5170, '0', '0', 0, 1583.7708740234375, -4436.11474609375, 13.29214763641357421, 1.588248729705810546, 0, 0, 0.713250160217285156, 0.700909554958343505, 120, 255, 1, 45505), -- Prickly Pear Fruit (Area: Valley of Strength - Difficulty: 0)
(@OGUID+81, 206995, 1, 1637, 5170, '0', '0', 0, 1654.1302490234375, -4388.05908203125, 20.97699928283691406, 2.635444164276123046, 0, 0, 0.96814727783203125, 0.250381410121917724, 120, 255, 1, 45505), -- Smoker (Area: Valley of Strength - Difficulty: 0)
(@OGUID+82, 204199, 1, 1637, 5170, '0', '0', 0, 1611.7708740234375, -4311.38037109375, 20.70730018615722656, 3.973746061325073242, -0.00871753692626953, 0.00730133056640625, -0.9146432876586914, 0.404101938009262084, 120, 255, 1, 45505), -- Brazier (Area: Valley of Strength - Difficulty: 0)
(@OGUID+83, 204209, 1, 1637, 5170, '0', '0', 0, 1650.329833984375, -4422.17041015625, 16.87849998474121093, 5.999874591827392578, -0.01801586151123046, -0.02881336212158203, -0.14152431488037109, 0.989351332187652587, 120, 255, 1, 45505), -- Brazier (Area: Valley of Strength - Difficulty: 0)
(@OGUID+84, 204604, 1, 1637, 5170, '0', '0', 0, 1626.5377197265625, -4324.669921875, 58.1649322509765625, 3.625617742538452148, 0, 0, -0.97085762023925781, 0.239656955003738403, 120, 255, 1, 45505), -- Torch (Area: Valley of Strength - Difficulty: 0)
(@OGUID+85, 206110, 1, 1637, 5170, '0', '0', 0, 1897.6300048828125, -4196.580078125, 37.25239944458007812, 5.340708732604980468, 0, 0, -0.45398998260498046, 0.891006767749786376, 120, 255, 1, 45505), -- Portal to Moonglade (Area: Valley of Strength - Difficulty: 0)
(@OGUID+86, 204609, 1, 1637, 5170, '0', '0', 0, 1660.1513671875, -4388.31787109375, 58.1649322509765625, 3.625617742538452148, 0, 0, -0.97085762023925781, 0.239656955003738403, 120, 255, 1, 45505), -- Torch (Area: Valley of Strength - Difficulty: 0)
(@OGUID+87, 269949, 1, 1637, 5170, '0', '0', 0, 1641.756591796875, -4449.62646484375, 18.52683448791503906, 2.356189966201782226, 0, 0, 0.923878669738769531, 0.38268551230430603, 120, 255, 1, 45505), -- Auction Materials (Area: Valley of Strength - Difficulty: 0)
(@OGUID+88, 380543, 1, 1637, 5170, '0', '0', 0, 1532.99072265625, -4392.548828125, 19.93498992919921875, 4.716695308685302734, 0, 0, -0.7055826187133789, 0.708627641201019287, 120, 255, 1, 45505), -- Fire Wall (Area: Valley of Strength - Difficulty: 0)
(@OGUID+89, 380543, 1, 1637, 5170, '0', '0', 0, 1532.94775390625, -4382.548828125, 19.93498992919921875, 4.716695308685302734, 0, 0, -0.7055826187133789, 0.708627641201019287, 120, 255, 1, 45505), -- Fire Wall (Area: Valley of Strength - Difficulty: 0)
(@OGUID+90, 204205, 1, 1637, 5170, '0', '0', 0, 1700.34033203125, -4397.25, 33.53960037231445312, 4.016735553741455078, 0.010371685028076171, 0.014613151550292968, -0.9055795669555664, 0.423797756433486938, 120, 255, 1, 45505), -- Brazier (Area: Valley of Strength - Difficulty: 0)
(@OGUID+91, 204605, 1, 1637, 5170, '0', '0', 0, 1652.9798583984375, -4310.80078125, 58.1649322509765625, 3.625617742538452148, 0, 0, -0.97085762023925781, 0.239656955003738403, 120, 255, 1, 45505), -- Torch (Area: Valley of Strength - Difficulty: 0)
(@OGUID+92, 259114, 1, 1637, 5170, '0', '0', 0, 1663.35595703125, -4353.0849609375, 64.61993408203125, 2.199114561080932617, 0, 0, 0.8910064697265625, 0.453990638256072998, 120, 255, 1, 45505), -- [DNT] Command Table Collision Cylinder (Area: Valley of Strength - Difficulty: 0)
(@OGUID+93, 175787, 1, 1637, 5170, '0', '0', 0, 1667.861083984375, -4340.37353515625, 28.40361976623535156, 2.967041015625, 0, 0, 0.996193885803222656, 0.087165042757987976, 120, 255, 1, 45505), -- Unadorned Stake (Area: Valley of Strength - Difficulty: 0)
(@OGUID+94, 175788, 1, 1637, 5170, '0', '0', 0, 1670.888916015625, -4346.13525390625, 28.40999794006347656, 3.263772249221801757, 0, 0, -0.99813461303710937, 0.061051756143569946, 120, 255, 1, 45505), -- Unadorned Stake (Area: Valley of Strength - Difficulty: 0)
(@OGUID+95, 204608, 1, 1637, 5170, '0', '0', 0, 1686.4818115234375, -4374.63525390625, 58.1649322509765625, 3.625617742538452148, 0, 0, -0.97085762023925781, 0.239656955003738403, 120, 255, 1, 45505), -- Torch (Area: Valley of Strength - Difficulty: 0)
(@OGUID+96, 204610, 1, 1637, 5170, '0', '0', 0, 1675.1302490234375, -4340.033203125, 28.418731689453125, 3.625617742538452148, 0, 0, -0.97085762023925781, 0.239656955003738403, 120, 255, 1, 45505), -- Grommash Throne (Area: Valley of Strength - Difficulty: 0)
(@OGUID+97, 204194, 1, 1637, 5170, '0', '0', 0, 1643.6597900390625, -4297.27978515625, 21.05319976806640625, 0.452342957258224487, -0.01491260528564453, -0.01652908325195312, 0.223965644836425781, 0.974342763423919677, 120, 255, 1, 45505), -- Brazier (Area: Valley of Strength - Difficulty: 0)
(@OGUID+98, 204195, 1, 1637, 5170, '0', '0', 0, 1730.2899169921875, -4360.470703125, 31.56350135803222656, 5.179685115814208984, -0.01212596893310546, -0.00368881225585937, -0.52420425415039062, 0.851498246192932128, 120, 255, 1, 45505), -- Brazier (Area: Valley of Strength - Difficulty: 0)
(@OGUID+99, 204196, 1, 1637, 5170, '0', '0', 0, 1705.7100830078125, -4327.69970703125, 31.29900169372558593, 2.272064208984375, 0.004366874694824218, -0.00318431854248046, 0.906953811645507812, 0.421195447444915771, 120, 255, 1, 45505), -- Brazier (Area: Valley of Strength - Difficulty: 0)
(@OGUID+100, 204200, 1, 1637, 5170, '0', '0', 0, 1706.640625, -4407.8193359375, 33.50049972534179687, 4.024084091186523437, -0.00241470336914062, 0.032370567321777343, -0.90359306335449218, 0.427160292863845825, 120, 255, 1, 45505), -- Brazier (Area: Valley of Strength - Difficulty: 0)
(@OGUID+101, 204606, 1, 1637, 5170, '0', '0', 0, 1681.1776123046875, -4320.015625, 58.1649322509765625, 3.625617742538452148, 0, 0, -0.97085762023925781, 0.239656955003738403, 120, 255, 1, 45505), -- Torch (Area: Valley of Strength - Difficulty: 0)
(@OGUID+102, 204607, 1, 1637, 5170, '0', '0', 0, 1695.030517578125, -4346.10595703125, 58.1649322509765625, 3.625617742538452148, 0, 0, -0.97085762023925781, 0.239656955003738403, 120, 255, 1, 45505), -- Torch (Area: Valley of Strength - Difficulty: 0)
(@OGUID+103, 206729, 1, 1637, 5170, '0', '0', 0, 1734.28125, -4385.19287109375, 33.26840972900390625, 6.213373661041259765, 0, 0, -0.03489875793457031, 0.999390840530395507, 120, 255, 1, 45505), -- Mailbox (Area: Valley of Strength - Difficulty: 0)
-- (@OGUID+104, 175080, 1, 1637, 5170, '0', '0', 0, 0, 0, 0, 4.127437591552734375, 0, 0, -0.88095378875732421, 0.473202288150787353, 120, 255, 1, 45505), -- 0 (Area: Valley of Strength - Difficulty: 0) - !!! transport !!!
(@OGUID+105, 204611, 1, 1637, 5170, '0', '0', 0, 1585.1591796875, -4284.56982421875, 57.89687347412109375, 4.729844093322753906, 0, 0, -0.70090866088867187, 0.713251054286956787, 120, 255, 1, 45505), -- Fire (Area: Valley of Strength - Difficulty: 0)
(@OGUID+106, 202590, 1, 1637, 5170, '0', '0', 0, 1585.5067138671875, -4283.8662109375, 21.44008636474609375, 4.729844093322753906, 0, 0, -0.70090866088867187, 0.713251054286956787, 120, 255, 1, 45505), -- Anvil (Area: Valley of Strength - Difficulty: 0)
(@OGUID+107, 203969, 1, 1637, 5170, '0', '0', 0, 1629.611083984375, -4286.6318359375, 20.79396438598632812, 5.619962215423583984, 0, 0, -0.32556724548339843, 0.945518851280212402, 120, 255, 1, 45505), -- Prickly Pear Fruit (Area: Valley of Strength - Difficulty: 0)
-- (@OGUID+108, 186238, 1, 1637, 5170, '0', '0', 0, 0, 0, 0, 3.325084447860717773, 0, 0, -0.99579429626464843, 0.091617166996002197, 120, 255, 1, 45505), -- 0 (Area: Valley of Strength - Difficulty: 0) - !!! transport !!!
-- (@OGUID+109, 190549, 1, 1637, 5170, '0', '0', 0, 0, 0, 0, 2.459702491760253906, 0, 0, 0.942439079284667968, 0.334377914667129516, 120, 255, 1, 45505), -- 0 (Area: Valley of Strength - Difficulty: 0) - !!! transport !!!
(@OGUID+110, 204632, 1, 1637, 5170, '0', '0', 0, 1754.1168212890625, -4353.6728515625, -7.90767669677734375, 4.35459756851196289, 0, 0, -0.82164669036865234, 0.569997072219848632, 120, 255, 1, 45505), -- Brazier (Area: Valley of Strength - Difficulty: 0)
(@OGUID+111, 206530, 1, 1637, 5170, '0', '0', 0, 1743.1123046875, -4327.4482421875, 6.110582351684570312, 2.617989301681518554, 0, 0, 0.965925216674804687, 0.258821308612823486, 120, 255, 1, 45505), -- Brazier (Area: Valley of Strength - Difficulty: 0)
(@OGUID+112, 204191, 1, 1637, 5170, '0', '0', 0, 1707.1805419921875, -4305.8505859375, 31.13640022277832031, 2.879789113998413085, 0, 0, 0.991444587707519531, 0.130528271198272705, 120, 255, 1, 45505), -- Brazier (Area: Valley of Strength - Difficulty: 0)
(@OGUID+113, 204192, 1, 1637, 5170, '0', '0', 0, 1714.4896240234375, -4306.48974609375, 31.19750022888183593, 1.308995485305786132, 0, 0, 0.608760833740234375, 0.793353796005249023, 120, 255, 1, 45505), -- Brazier (Area: Valley of Strength - Difficulty: 0)
(@OGUID+114, 204197, 1, 1637, 5170, '0', '0', 0, 1671.890625, -4292.27099609375, 25.60580062866210937, 3.721304893493652343, 0.01981973648071289, -0.00385093688964843, -0.95813751220703125, 0.285595595836639404, 120, 255, 1, 45505), -- Brazier (Area: Valley of Strength - Difficulty: 0)
(@OGUID+115, 204203, 1, 1637, 5170, '0', '0', 0, 1737.420166015625, -4442.220703125, 38.8583984375, 1.713568687438964843, 0.015055656433105468, -0.02430438995361328, 0.755279541015625, 0.654778897762298583, 120, 255, 1, 45505), -- Brazier (Area: Valley of Strength - Difficulty: 0)
(@OGUID+116, 204204, 1, 1637, 5170, '0', '0', 0, 1747.94970703125, -4442.72900390625, 38.67910003662109375, 1.765920281410217285, 0.007376670837402343, -0.0263223648071289, 0.7721099853515625, 0.634900689125061035, 120, 255, 1, 45505), -- Brazier (Area: Valley of Strength - Difficulty: 0)
(@OGUID+117, 207414, 1, 1637, 5170, '0', '0', 0, 2048.52783203125, -4391.53662109375, 99.42253875732421875, 3.124123096466064453, 0, 0, 0.99996185302734375, 0.008734640665352344, 120, 255, 1, 45505), -- Waters of Farseeing (Area: Valley of Strength - Difficulty: 0)
(@OGUID+118, 210181, 1, 1637, 5170, '0', '0', 0, 2039.904541015625, -4261.876953125, 95.43408203125, 4.869470596313476562, 0, 0, -0.64944744110107421, 0.760406434535980224, 120, 255, 1, 45505), -- Deathwing Trophy (0.7) (Area: Valley of Strength - Difficulty: 0)
(@OGUID+119, 209124, 1, 1637, 5170, '0', '0', 0, 1771.814208984375, -4350.1494140625, 105.5579681396484375, 0.942476630210876464, 0, 0, 0.453989982604980468, 0.891006767749786376, 120, 255, 1, 45505), -- Come Visit the Darkmoon Faire! (Area: Valley of Strength - Difficulty: 0)
(@OGUID+120, 206736, 1, 1637, 5170, '0', '0', 0, 1693.4600830078125, -4285.34033203125, 29.88190078735351562, 3.9793548583984375, 0, 0, -0.9135446548461914, 0.406738430261611938, 120, 255, 1, 45505), -- Mailbox (Area: Valley of Strength - Difficulty: 0)
(@OGUID+121, 206741, 1, 1637, 5170, '0', '0', 0, 1711.7708740234375, -4277.390625, 101.7239990234375, 3.543023586273193359, 0, 0, -0.97992420196533203, 0.199370384216308593, 120, 255, 1, 45505), -- Mailbox (Area: Valley of Strength - Difficulty: 0)
(@OGUID+122, 204633, 1, 1637, 5170, '0', '0', 0, 1764.58447265625, -4352.4921875, -7.90767669677734375, 5.017822265625, 0, 0, -0.5913095474243164, 0.806444704532623291, 120, 255, 1, 45505), -- Brazier (Area: Valley of Strength - Difficulty: 0)
(@OGUID+123, 204634, 1, 1637, 5170, '0', '0', 0, 1757.6793212890625, -4339.416015625, -8.11644744873046875, 5.017822265625, 0, 0, -0.5913095474243164, 0.806444704532623291, 120, 255, 1, 45505), -- Brazier (Area: Valley of Strength - Difficulty: 0)
(@OGUID+124, 206539, 1, 1637, 5170, '0', '0', 0, 1766.0552978515625, -4321.81640625, 6.37014007568359375, 3.541460990905761718, 0, 0, -0.98007965087890625, 0.198604762554168701, 120, 255, 1, 45505), -- Brazier (Area: Valley of Strength - Difficulty: 0)
(@OGUID+125, 206545, 1, 1637, 5170, '0', '0', 0, 1763.3497314453125, -4318.9375, 6.309940338134765625, 3.980193853378295898, 0, 0, -0.91337394714355468, 0.4071216881275177, 120, 255, 1, 45505), -- The Slow Blade (Area: Valley of Strength - Difficulty: 0)
(@OGUID+126, 206546, 1, 1637, 5170, '0', '0', 0, 1767.4578857421875, -4333.3564453125, -8.18587875366210937, 3.544665813446044921, 0, 0, -0.97976016998291015, 0.200174912810325622, 120, 255, 1, 45505), -- Arcane Enclave (Area: Valley of Strength - Difficulty: 0)
(@OGUID+127, 197323, 1, 1637, 5170, '0', '0', 0, 1767.0709228515625, -4329.80029296875, -8.27419281005859375, 4.328419685363769531, 0, 0, -0.82903671264648437, 0.559194147586822509, 120, 255, 1, 45505), -- Brazier (Area: Valley of Strength - Difficulty: 0)
(@OGUID+128, 202717, 1, 1637, 5170, '0', '0', 0, 1732.8375244140625, -4285.39404296875, 16.91876602172851562, 3.735006093978881835, 0, 0, -0.95630455017089843, 0.292372345924377441, 120, 255, 1, 45505), -- Brazier (Area: Valley of Strength - Difficulty: 0)
(@OGUID+129, 209114, 1, 1637, 5170, '0', '0', 0, 1765.6492919921875, -4346.65625, 104.9563369750976562, 0.977383077144622802, 0, 0, 0.469470977783203125, 0.882947921752929687, 120, 255, 1, 45505), -- Balloon Bunch 01 (Area: Valley of Strength - Difficulty: 0)
(@OGUID+130, 197279, 1, 1637, 5170, '0', '0', 0, 1760.77685546875, -4301.35205078125, 7.196001052856445312, 3.735006093978881835, 0, 0, -0.95630455017089843, 0.292372345924377441, 120, 255, 1, 45505), -- Brazier (Area: Valley of Strength - Difficulty: 0)
(@OGUID+131, 197284, 1, 1637, 5170, '0', '0', 0, 1779.7064208984375, -4369.447265625, -16.1218948364257812, 3.735006093978881835, 0, 0, -0.95630455017089843, 0.292372345924377441, 120, 255, 1, 45505), -- Brazier (Area: Valley of Strength - Difficulty: 0)
(@OGUID+132, 197287, 1, 1637, 5170, '0', '0', 0, 1780.75634765625, -4365.23876953125, -15.9128952026367187, 6.265733242034912109, 0, 0, -0.00872611999511718, 0.999961912631988525, 120, 255, 1, 45505), -- Dark Earth (Area: Valley of Strength - Difficulty: 0)
(@OGUID+133, 206529, 1, 1637, 5170, '0', '0', 0, 1799.9520263671875, -4371.73876953125, -17.2928810119628906, 3.377224683761596679, 0, 0, -0.99306774139404296, 0.117543503642082214, 120, 255, 1, 45505), -- Brazier (Area: Valley of Strength - Difficulty: 0)
(@OGUID+134, 197313, 1, 1637, 5170, '0', '0', 0, 1797.7720947265625, -4397.3232421875, -17.5951347351074218, 3.735006093978881835, 0, 0, -0.95630455017089843, 0.292372345924377441, 120, 255, 1, 45505), -- Brazier (Area: Valley of Strength - Difficulty: 0)
(@OGUID+135, 105576, 1, 1637, 5170, '0', '0', 0, 1805.623291015625, -4374.11474609375, -17.0474224090576171, 5.515241622924804687, 0, 0, -0.37460613250732421, 0.927184045314788818, 120, 255, 1, 45505), -- Summoning Circle (Area: Valley of Strength - Difficulty: 0)
(@OGUID+136, 207646, 1, 1637, 5170, '0', '0', 0, 1730.390625, -4498.62841796875, 30.93424797058105468, 3.324855566024780273, 0, 0, -0.9958047866821289, 0.091503240168094635, 120, 255, 1, 45505), -- Mailbox (Area: Valley of Strength - Difficulty: 0)
(@OGUID+137, 212212, 1, 1637, 5170, '0', '0', 0, 1811.4930419921875, -4370.85791015625, -15.96942138671875, 2.952159404754638671, 0, 0, 0.995517730712890625, 0.094575114548206329, 120, 255, 1, 45505), -- Legacy of the Masters (Part 1) (Area: Valley of Strength - Difficulty: 0)
(@OGUID+138, 202798, 1, 1637, 5170, '0', '0', 0, 1768.550048828125, -4483.07373046875, 45.61966705322265625, 3.735006093978881835, 0, 0, -0.95630455017089843, 0.292372345924377441, 120, 255, 1, 45505), -- Smoked Meat Rack (Area: Valley of Strength - Difficulty: 0)
(@OGUID+139, 202799, 1, 1637, 5170, '0', '0', 0, 1775.98486328125, -4480.5205078125, 45.72623443603515625, 3.735006093978881835, 0, 0, -0.95630455017089843, 0.292372345924377441, 120, 255, 1, 45505), -- Burning Embers (Area: Valley of Strength - Difficulty: 0)
(@OGUID+140, 197315, 1, 1637, 5170, '0', '0', 0, 1818.090087890625, -4402.2099609375, -17.6068115234375, 2.687806606292724609, 0, 0, 0.974370002746582031, 0.224951311945915222, 120, 255, 1, 45505), -- Meeting Stone (Area: Valley of Strength - Difficulty: 0)
(@OGUID+141, 208534, 1, 1637, 5170, '0', '0', 0, 1760.3629150390625, -4485.0400390625, 44.74652862548828125, 3.141367912292480468, -0.06247377395629882, 0.036800384521484375, 0.997364997863769531, 0.002416868926957249, 120, 255, 1, 45505), -- Campfire (Area: Valley of Strength - Difficulty: 0)
(@OGUID+142, 204939, 1, 1637, 5170, '0', '0', 0, 1804.9736328125, -4510.28515625, 24.47103309631347656, 0.152036190032958984, 0, 0, 0.075944900512695312, 0.997112035751342773, 120, 255, 1, 45505), -- Brazier (Area: Valley of Strength - Difficulty: 0)
(@OGUID+143, 259114, 1, 1637, 5170, '0', '0', 0, 1733.0816650390625, -4514.705078125, 30.76891517639160156, 2.848805665969848632, 0, 0, 0.9893035888671875, 0.145871117711067199, 120, 255, 1, 45505), -- [DNT] Command Table Collision Cylinder (Area: Valley of Strength - Difficulty: 0)
(@OGUID+144, 210058, 1, 1637, 5170, '0', '0', 0, 1735.2393798828125, -4514.38623046875, 30.76676368713378906, 6.152286052703857421, 0, 0, -0.06540298461914062, 0.997858941555023193, 120, 255, 1, 45505), -- Forge (Area: Valley of Strength - Difficulty: 0)
(@OGUID+145, 210059, 1, 1637, 5170, '0', '0', 0, 1726.8841552734375, -4505.84130859375, 30.75733566284179687, 0.113446973264217376, 0, 0, 0.056693077087402343, 0.998391628265380859, 120, 255, 1, 45505), -- Anvil (Area: Valley of Strength - Difficulty: 0)
(@OGUID+146, 259114, 1, 1637, 5170, '0', '0', 0, 1721.032958984375, -4513.22216796875, 31.25615119934082031, 0.290519893169403076, 0, 0, 0.144749641418457031, 0.989468336105346679, 120, 255, 1, 45505), -- [DNT] Command Table Collision Cylinder (Area: Valley of Strength - Difficulty: 0)
(@OGUID+147, 202800, 1, 1637, 5170, '0', '0', 0, 1786.565185546875, -4508.625, 27.73431015014648437, 4.293513298034667968, 0, 0, -0.8386697769165039, 0.544640243053436279, 120, 255, 1, 45505), -- Brazier (Area: Valley of Strength - Difficulty: 0)
(@OGUID+148, 202801, 1, 1637, 5170, '0', '0', 0, 1778.72412109375, -4495.89501953125, 27.8087158203125, 4.092797279357910156, 0, 0, -0.88901710510253906, 0.457874000072479248, 120, 255, 1, 45505), -- Burning Embers (Area: Valley of Strength - Difficulty: 0)
(@OGUID+149, 202809, 1, 1637, 5170, '0', '0', 0, 1833.41455078125, -4472.2431640625, 47.6503753662109375, 3.45575571060180664, 0, 0, -0.98768806457519531, 0.156436234712600708, 120, 255, 1, 45505), -- Brazier (Area: Valley of Strength - Difficulty: 0)
(@OGUID+150, 208269, 1, 1637, 5170, '0', '0', 0, 1825.669189453125, -4484.974609375, 23.64171791076660156, 2.411572694778442382, 0, 0, 0.93412017822265625, 0.356958627700805664, 120, 255, 1, 45505), -- Forge (Area: Valley of Strength - Difficulty: 0)
(@OGUID+151, 208270, 1, 1637, 5170, '0', '0', 0, 1829.75732421875, -4485.36083984375, 23.58223724365234375, 0.958117663860321044, 0, 0, 0.460944175720214843, 0.887429118156433105, 120, 255, 1, 45505), -- Anvil (Area: Valley of Strength - Difficulty: 0)
(@OGUID+152, 203969, 1, 1637, 5170, '0', '0', 0, 1762.3004150390625, -4500.15966796875, 29.75385856628417968, 5.619962215423583984, 0, 0, -0.32556724548339843, 0.945518851280212402, 120, 255, 1, 45505), -- Prickly Pear Fruit (Area: Valley of Strength - Difficulty: 0)
(@OGUID+153, 259114, 1, 1637, 5170, '0', '0', 0, 1727.3680419921875, -4507.533203125, 30.77355384826660156, 4.817109584808349609, 0, 0, -0.66913032531738281, 0.74314504861831665, 120, 255, 1, 45505), -- [DNT] Command Table Collision Cylinder (Area: Valley of Strength - Difficulty: 0)
(@OGUID+154, 207630, 1, 1637, 5170, '0', '0', 0, 1778.107666015625, -4499.45849609375, 44.93404388427734375, 0.017452461645007133, 0, 0, 0.008726119995117187, 0.999961912631988525, 120, 255, 1, 45505), -- Mailbox (Area: Valley of Strength - Difficulty: 0)
(@OGUID+155, 204693, 1, 1637, 5170, '0', '0', 0, 1748.220458984375, -4500.72900390625, 29.79990005493164062, 2.631497859954833984, 0.012664794921875, -0.02503871917724609, 0.967171669006347656, 0.25257006287574768, 120, 255, 1, 45505), -- Brazier (Area: Valley of Strength - Difficulty: 0)
(@OGUID+156, 207633, 1, 1637, 5170, '0', '0', 0, 1795.3038330078125, -4523.54541015625, 23.55860710144042968, 0.479964137077331542, 0, 0, 0.237685203552246093, 0.971342265605926513, 120, 255, 1, 45505), -- Mailbox (Area: Valley of Strength - Difficulty: 0)
(@OGUID+157, 204695, 1, 1637, 5170, '0', '0', 0, 1779.560791015625, -4538.3193359375, 23.81369972229003906, 3.258188486099243164, -0.00647258758544921, 0.023867607116699218, -0.99800300598144531, 0.058124441653490066, 120, 255, 1, 45505), -- Brazier (Area: Valley of Strength - Difficulty: 0)
(@OGUID+158, 204696, 1, 1637, 5170, '0', '0', 0, 1802.69970703125, -4521.55029296875, 23.30240058898925781, 3.729416131973266601, -0.0132155418395996, -0.01012992858886718, -0.95695877075195312, 0.289745748043060302, 120, 255, 1, 45505), -- Brazier (Area: Valley of Strength - Difficulty: 0)
(@OGUID+159, 186722, 1, 1637, 5170, '0', '0', 0, 1803.8900146484375, -4503.240234375, 24.36479949951171875, 0.733038187026977539, 0, 0, 0.358367919921875, 0.933580458164215087, 120, 255, 1, 45505), -- Yellow Ragdoll (Area: Valley of Strength - Difficulty: 0)
(@OGUID+160, 259114, 1, 1637, 5170, '0', '0', 0, 1727.328125, -4519.50341796875, 32.64420318603515625, 1.291541695594787597, 0, 0, 0.60181427001953125, 0.798636078834533691, 120, 255, 1, 45505), -- [DNT] Command Table Collision Cylinder (Area: Valley of Strength - Difficulty: 0)
(@OGUID+161, 204936, 1, 1637, 5170, '0', '0', 0, 1825.521728515625, -4495.5146484375, 23.65651321411132812, 0.187869623303413391, 0, 0, 0.093796730041503906, 0.995591342449188232, 120, 255, 1, 45505), -- Brazier (Area: Valley of Strength - Difficulty: 0)
(@OGUID+162, 204938, 1, 1637, 5170, '0', '0', 0, 1818.3194580078125, -4505.34521484375, 24.47344970703125, 0.852078020572662353, 0, 0, 0.413267135620117187, 0.910609841346740722, 120, 255, 1, 45505), -- Burning Embers (Area: Valley of Strength - Difficulty: 0)
(@OGUID+163, 202802, 1, 1637, 5167, '0', '0', 0, 1790.8736572265625, -4558.0673828125, 23.07546043395996093, 3.735006093978881835, 0, 0, -0.95630455017089843, 0.292372345924377441, 120, 255, 1, 45505), -- Brazier (Area: The Drag - Difficulty: 0)
(@OGUID+164, 204681, 1, 1637, 5167, '0', '0', 0, 1821.689208984375, -4532.970703125, 23.35370063781738281, 0.249127700924873352, 0.000787734985351562, 0.003031730651855468, 0.124238014221191406, 0.992247521877288818, 120, 255, 1, 45505), -- Brazier (Area: The Drag - Difficulty: 0)
(@OGUID+165, 202803, 1, 1637, 5167, '0', '0', 0, 1815.3291015625, -4556.6083984375, 23.07546043395996093, 4.520402908325195312, 0, 0, -0.77162456512451171, 0.636078238487243652, 120, 255, 1, 45505), -- Brazier (Area: The Drag - Difficulty: 0)
(@OGUID+166, 202804, 1, 1637, 5167, '0', '0', 0, 1796.322265625, -4575.34228515625, 23.07546043395996093, 3.735006093978881835, 0, 0, -0.95630455017089843, 0.292372345924377441, 120, 255, 1, 45505), -- Brazier (Area: The Drag - Difficulty: 0)
(@OGUID+167, 193981, 1, 1637, 5167, '0', '0', 0, 1836.219970703125, -4459.5, 49.06280136108398437, 4.956737518310546875, 0, 0, -0.61566066741943359, 0.788011372089385986, 120, 255, 1, 45505), -- Lexicon of Power (Area: The Drag - Difficulty: 0)
(@OGUID+168, 204937, 1, 1637, 5167, '0', '0', 0, 1837.299560546875, -4490.89501953125, 23.65651321411132812, 0.842367768287658691, 0, 0, 0.408841133117675781, 0.912605583667755126, 120, 255, 1, 45505), -- Brazier (Area: The Drag - Difficulty: 0)
(@OGUID+169, 197207, 1, 1637, 5170, '0', '0', 0, 1834.1390380859375, -4407.47412109375, 5.33437347412109375, 3.141592741012573242, 0, 0, -1, 0, 120, 255, 1, 45505), -- Mailbox (Area: Valley of Strength - Difficulty: 0)
(@OGUID+170, 197310, 1, 1637, 5170, '0', '0', 0, 1831.509033203125, -4405.1083984375, 4.956727981567382812, 3.463985443115234375, -0.02164173126220703, -0.00908660888671875, -0.98674392700195312, 0.160578653216361999, 120, 255, 1, 45505), -- Brazier (Area: Valley of Strength - Difficulty: 0)
(@OGUID+171, 206538, 1, 1637, 5170, '0', '0', 0, 1777.7449951171875, -4312.04833984375, 5.640611648559570312, 4.48549652099609375, 0, 0, -0.7826080322265625, 0.622514784336090087, 120, 255, 1, 45505), -- Brazier (Area: Valley of Strength - Difficulty: 0)
(@OGUID+172, 197312, 1, 1637, 5170, '0', '0', 0, 1817.1962890625, -4359.3310546875, -9.6055145263671875, 3.735006093978881835, 0, 0, -0.95630455017089843, 0.292372345924377441, 120, 255, 1, 45505), -- Brazier (Area: Valley of Strength - Difficulty: 0)
(@OGUID+173, 206549, 1, 1637, 5170, '0', '0', 0, 1769.71484375, -4293.4912109375, 7.154603958129882812, 1.802743077278137207, 0, 0, 0.784178733825683593, 0.620535016059875488, 120, 255, 1, 45505), -- Shadowswift Brotherhood (Area: Valley of Strength - Difficulty: 0)
(@OGUID+174, 293684, 1, 1637, 5170, '0', '0', 0, 1842.263916015625, -4389.0224609375, 135.2330169677734375, 0.286221921443939208, 0, 0, 0.142622947692871093, 0.989777088165283203, 120, 255, 1, 45505), -- Portal to Undercity (Area: Valley of Strength - Difficulty: 0)
(@OGUID+175, 203969, 1, 1637, 5170, '0', '0', 0, 1795.7864990234375, -4293.57666015625, 100.8059768676757812, 5.95157480239868164, 0, 0, -0.16504669189453125, 0.986285746097564697, 120, 255, 1, 45505), -- Prickly Pear Fruit (Area: Valley of Strength - Difficulty: 0)
(@OGUID+176, 205056, 1, 1637, 5170, '0', '0', 0, 1838.7725830078125, -4388.72412109375, 135.2330169677734375, 5.570709228515625, 0, 0, -0.34875106811523437, 0.937215387821197509, 120, 255, 1, 45505), -- Construction Blockade (Area: Valley of Strength - Difficulty: 0)
(@OGUID+177, 203969, 1, 1637, 5170, '0', '0', 0, 1852.673583984375, -4418.7099609375, 104.0621337890625, 1.291541695594787597, 0, 0, 0.60181427001953125, 0.798636078834533691, 120, 255, 1, 45505), -- Prickly Pear Fruit (Area: Valley of Strength - Difficulty: 0)
(@OGUID+178, 203969, 1, 1637, 5170, '0', '0', 0, 1866.5399169921875, -4312.31787109375, 24.70046424865722656, 3.94444584846496582, 0, 0, -0.92050457000732421, 0.3907318115234375, 120, 255, 1, 45505), -- Prickly Pear Fruit (Area: Valley of Strength - Difficulty: 0)
(@OGUID+179, 206740, 1, 1637, 5170, '0', '0', 0, 1879.8194580078125, -4381.1005859375, 100.5049972534179687, 2.312562942504882812, 0, 0, 0.915311813354492187, 0.40274590253829956, 120, 255, 1, 45505), -- Mailbox (Area: Valley of Strength - Difficulty: 0)
(@OGUID+180, 212212, 1, 1637, 5170, '0', '0', 0, 1845.515625, -4366.60791015625, -14.598027229309082, 2.952159404754638671, 0, 0, 0.995517730712890625, 0.094575114548206329, 120, 255, 1, 45505), -- Legacy of the Masters (Part 1) (Area: Valley of Strength - Difficulty: 0)
(@OGUID+181, 197307, 1, 1637, 5170, '0', '0', 0, 1850.2774658203125, -4359.296875, -14.8203125, 3.377224683761596679, 0, 0, -0.99306774139404296, 0.117543503642082214, 120, 255, 1, 45505), -- Brazier (Area: Valley of Strength - Difficulty: 0)
(@OGUID+182, 197309, 1, 1637, 5170, '0', '0', 0, 1844.3536376953125, -4394.24169921875, 4.818790435791015625, 3.735006093978881835, 0, 0, -0.95630455017089843, 0.292372345924377441, 120, 255, 1, 45505), -- Brazier (Area: Valley of Strength - Difficulty: 0)
(@OGUID+183, 197311, 1, 1637, 5170, '0', '0', 0, 1832.173828125, -4344.95263671875, -15.1037521362304687, 3.735006093978881835, 0, 0, -0.95630455017089843, 0.292372345924377441, 120, 255, 1, 45505), -- Brazier (Area: Valley of Strength - Difficulty: 0)
(@OGUID+184, 206547, 1, 1637, 5170, '0', '0', 0, 1806.923828125, -4290.0908203125, 6.13816070556640625, 3.436542510986328125, 0, 0, -0.98914527893066406, 0.146940812468528747, 120, 255, 1, 45505), -- Rekkul's Poisons (Area: Valley of Strength - Difficulty: 0)
(@OGUID+185, 197314, 1, 1637, 5170, '0', '0', 0, 1835.818115234375, -4364.607421875, -14.8244171142578125, 2.95832991600036621, 0, 0, 0.995804786682128906, 0.091503240168094635, 120, 255, 1, 45505), -- Darkfire Enclave (Area: Valley of Strength - Difficulty: 0)
(@OGUID+186, 206548, 1, 1637, 5170, '0', '0', 0, 1818.320068359375, -4316.23046875, -11.5067901611328125, 3.368377685546875, 0, 0, -0.99357795715332031, 0.11314963549375534, 120, 255, 1, 45505), -- Ironwood Staves and Wands (Area: Valley of Strength - Difficulty: 0)
(@OGUID+187, 197259, 1, 1637, 5170, '0', '0', 0, 1854.91259765625, -4422.2919921875, 7.091920852661132812, 3.735006093978881835, 0, 0, -0.95630455017089843, 0.292372345924377441, 120, 255, 1, 45505), -- Brazier (Area: Valley of Strength - Difficulty: 0)
(@OGUID+188, 197322, 1, 1637, 5170, '0', '0', 0, 1804.617919921875, -4309.212890625, -11.5113792419433593, 4.328419685363769531, 0, 0, -0.82903671264648437, 0.559194147586822509, 120, 255, 1, 45505), -- Brazier (Area: Valley of Strength - Difficulty: 0)
(@OGUID+189, 197276, 1, 1637, 5170, '0', '0', 0, 1775.827392578125, -4277.6982421875, 7.995021820068359375, 2.696528911590576171, 0, 0, 0.975341796875, 0.220699742436408996, 120, 255, 1, 45505), -- Brazier (Area: Valley of Strength - Difficulty: 0)
(@OGUID+190, 197278, 1, 1637, 5170, '0', '0', 0, 1803.9063720703125, -4294.52783203125, 5.972806930541992187, 3.735006093978881835, 0, 0, -0.95630455017089843, 0.292372345924377441, 120, 255, 1, 45505), -- Brazier (Area: Valley of Strength - Difficulty: 0)
(@OGUID+191, 197280, 1, 1637, 5170, '0', '0', 0, 1793.7529296875, -4300.583984375, 4.60311126708984375, 4.48549652099609375, 0, 0, -0.7826080322265625, 0.622514784336090087, 120, 255, 1, 45505), -- Brazier (Area: Valley of Strength - Difficulty: 0)
(@OGUID+192, 197285, 1, 1637, 5170, '0', '0', 0, 1827.5013427734375, -4325.017578125, -15.3716087341308593, 4.328419685363769531, 0, 0, -0.82903671264648437, 0.559194147586822509, 120, 255, 1, 45505), -- Brazier (Area: Valley of Strength - Difficulty: 0)
(@OGUID+193, 197286, 1, 1637, 5170, '0', '0', 0, 1831.6678466796875, -4339.24365234375, -15.3923110961914062, 3.735006093978881835, 0, 0, -0.95630455017089843, 0.292372345924377441, 120, 255, 1, 45505), -- Shadowdeep Reagents (Area: Valley of Strength - Difficulty: 0)
(@OGUID+194, 206730, 1, 1637, 5170, '0', '0', 0, 1867.2899169921875, -4321.6806640625, 23.75259971618652343, 3.586656570434570312, 0, 0, -0.975341796875, 0.220699742436408996, 120, 255, 1, 45505), -- Mailbox (Area: Valley of Strength - Difficulty: 0)
(@OGUID+195, 237942, 1, 1637, 5170, '0', '0', 0, 1890.2586669921875, -4414.05224609375, 15.01573562622070312, 4.031611442565917968, -0.08796453475952148, -0.08504199981689453, -0.89385890960693359, 0.43133091926574707, 120, 255, 1, 45505), -- Engraved Stone Plaque (Area: Valley of Strength - Difficulty: 0)
(@OGUID+196, 197260, 1, 1637, 5170, '0', '0', 0, 1888.1422119140625, -4416.78466796875, 12.19525909423828125, 3.351046562194824218, 0, 0, -0.99452114105224609, 0.104535527527332305, 120, 255, 1, 45505), -- Brazier (Area: Valley of Strength - Difficulty: 0)
(@OGUID+197, 204688, 1, 1637, 5170, '0', '0', 0, 1882.75, -4301.5, 22.92819976806640625, 0.593411982059478759, 0, 0, 0.292371749877929687, 0.956304728984832763, 120, 255, 1, 45505), -- Bonfire (Area: Valley of Strength - Difficulty: 0)
(@OGUID+198, 204720, 1, 1637, 5170, '0', '0', 0, 1837.1805419921875, -4247.3994140625, 40.81399917602539062, 0.047778129577636718, -0.0052495002746582, 0.000280380249023437, 0.023888587951660156, 0.999700784683227539, 120, 255, 1, 45505), -- Brazier (Area: Valley of Strength - Difficulty: 0)
(@OGUID+199, 204721, 1, 1637, 5170, '0', '0', 0, 1900.6302490234375, -4258.02978515625, 30.90690040588378906, 5.90230417251586914, -0.01010751724243164, -0.00106048583984375, -0.18931007385253906, 0.981864750385284423, 120, 255, 1, 45505), -- Brazier (Area: Valley of Strength - Difficulty: 0)
(@OGUID+200, 204726, 1, 1637, 5170, '0', '0', 0, 1927.3802490234375, -4364.92041015625, 23.65620040893554687, 5.063550472259521484, -0.00446796417236328, -0.0288848876953125, -0.57219600677490234, 0.819595873355865478, 120, 255, 1, 45505), -- Brazier (Area: Valley of Strength - Difficulty: 0)
(@OGUID+201, 204727, 1, 1637, 5170, '0', '0', 0, 1914.0504150390625, -4292.84033203125, 24.34020042419433593, 4.104609966278076171, -0.00712203979492187, 0.007249832153320312, -0.88626480102539062, 0.46306738257408142, 120, 255, 1, 45505), -- Brazier (Area: Valley of Strength - Difficulty: 0)
(@OGUID+202, 204719, 1, 1637, 0, '0', '0', 0, 1839.890625, -4235.86962890625, 40.55649948120117187, 3.155946016311645507, -0.00785589218139648, -0.00896167755126953, -0.99990272521972656, 0.007246495224535465, 120, 255, 1, 45505), -- Brazier (Area: 0 - Difficulty: 0)
(@OGUID+203, 207634, 1, 1637, 0, '0', '0', 0, 1928.4896240234375, -4399.09375, 23.48713874816894531, 5.20981597900390625, 0, 0, -0.51128959655761718, 0.859408497810363769, 120, 255, 1, 45505), -- Mailbox (Area: 0 - Difficulty: 0)
(@OGUID+204, 204700, 1, 1637, 0, '0', '0', 0, 1939.9305419921875, -4363.3994140625, 23.73520088195800781, 5.038416862487792968, -0.01381349563598632, -0.00126075744628906, -0.58299541473388671, 0.812357008457183837, 120, 255, 1, 45505), -- Brazier (Area: 0 - Difficulty: 0)
(@OGUID+205, 203969, 1, 1637, 0, '0', '0', 0, 1930.4930419921875, -4252.17724609375, 31.31423568725585937, 1.221729278564453125, 0, 0, 0.573575973510742187, 0.819152355194091796, 120, 255, 1, 45505), -- Prickly Pear Fruit (Area: 0 - Difficulty: 0)
(@OGUID+206, 204699, 1, 1637, 0, '0', '0', 0, 1929.689208984375, -4406.5693359375, 23.4850006103515625, 4.986055850982666015, -0.00473737716674804, -0.01596260070800781, -0.60388660430908203, 0.796896338462829589, 120, 255, 1, 45505), -- Brazier (Area: 0 - Difficulty: 0)
(@OGUID+207, 206738, 1, 1637, 0, '0', '0', 0, 1901.7291259765625, -4211.27099609375, 36.97869873046875, 4.424411773681640625, 0, 0, -0.80125331878662109, 0.598325252532958984, 120, 255, 1, 45505), -- Anvil (Area: 0 - Difficulty: 0)
(@OGUID+208, 206739, 1, 1637, 0, '0', '0', 0, 1904.310791015625, -4216.63037109375, 36.922698974609375, 3.577930212020874023, 0, 0, -0.97629547119140625, 0.216442063450813293, 120, 255, 1, 45505), -- Forge (Area: 0 - Difficulty: 0)
(@OGUID+209, 50804, 1, 1637, 0, '0', '0', 0, 1961.9119873046875, -4228.79150390625, 37.20825576782226562, 2.364918231964111328, 0, 0, 0.925539970397949218, 0.378649920225143432, 120, 255, 1, 45505), -- Burning Embers (Area: 0 - Difficulty: 0)
(@OGUID+210, 206595, 1, 1637, 0, '0', '0', 0, 2031.219970703125, -4330.8701171875, 95.47100067138671875, 0, 0, 0, 0, 1, 120, 255, 1, 45505), -- Portal to Tol Barad (Area: 0 - Difficulty: 0)
(@OGUID+211, 205091, 1, 1637, 0, '0', '0', 0, 1955.0103759765625, -4212.970703125, 37.10789871215820312, 3.368495941162109375, 0, 0, -0.99357128143310546, 0.113208353519439697, 120, 255, 1, 45505), -- Guild Vault (Area: 0 - Difficulty: 0)
(@OGUID+212, 50803, 1, 1637, 0, '0', '0', 0, 1964.2410888671875, -4222.31201171875, 37.20825576782226562, 2.495818138122558593, 0, 0, 0.948323249816894531, 0.317305892705917358, 120, 255, 1, 45505), -- Burning Embers (Area: 0 - Difficulty: 0)
(@OGUID+213, 50805, 1, 1637, 0, '0', '0', 0, 1980.750732421875, -4232.69091796875, 37.20825576782226562, 2.426007747650146484, 0, 0, 0.936672210693359375, 0.350207358598709106, 120, 255, 1, 45505), -- Burning Embers (Area: 0 - Difficulty: 0)
(@OGUID+214, 206508, 1, 1637, 0, '0', '0', 0, 2039.189208984375, -4320.61962890625, 95.41300201416015625, 5.297073841094970703, 0, 0, -0.47332000732421875, 0.880890548229217529, 120, 255, 1, 45505), -- Bonfire (Area: 0 - Difficulty: 0)
(@OGUID+215, 207635, 1, 1637, 0, '0', '0', 0, 2001.9896240234375, -4369.28662109375, 94.15111541748046875, 6.213373661041259765, 0, 0, -0.03489875793457031, 0.999390840530395507, 120, 255, 1, 45505), -- Mailbox (Area: 0 - Difficulty: 0)
(@OGUID+216, 207687, 1, 1637, 0, '0', '0', 0, 2039.670166015625, -4356.2880859375, 98.00434112548828125, 2.469640016555786132, 0.006290435791015625, -0.02392101287841796, 0.943706512451171875, 0.329857915639877319, 120, 255, 1, 45505), -- Portal to Uldum (Area: 0 - Difficulty: 0)
(@OGUID+217, 207690, 1, 1637, 5171, '0', '0', 0, 2063.3369140625, -4362.2900390625, 98.1101837158203125, 3.988081216812133789, 0, 0, -0.91176128387451171, 0.410720497369766235, 120, 255, 1, 45505), -- Portal to Vashj'ir (Area: Valley of Wisdom - Difficulty: 0)
(@OGUID+218, 205090, 1, 1637, 5171, '0', '0', 0, 1921.2899169921875, -4190.69091796875, 36.87599945068359375, 4.825844764709472656, 0, 0, -0.6658782958984375, 0.746060371398925781, 120, 255, 1, 45505), -- Mailbox (Area: Valley of Wisdom - Difficulty: 0)
(@OGUID+219, 3301, 1, 1637, 5171, '0', '0', 0, 1920.10546875, -4175.15478515625, 37.93421554565429687, 5.026549339294433593, 0, 0, -0.5877847671508789, 0.809017360210418701, 120, 255, 1, 45505), -- Burning Embers (Area: Valley of Wisdom - Difficulty: 0)
(@OGUID+220, 204689, 1, 1637, 5171, '0', '0', 0, 1937.6302490234375, -4189.1494140625, 36.95830154418945312, 2.495818138122558593, 0, 0, 0.948323249816894531, 0.317305892705917358, 120, 255, 1, 45505), -- Bonfire (Area: Valley of Wisdom - Difficulty: 0)
(@OGUID+221, 203969, 1, 1637, 5171, '0', '0', 0, 1890.8055419921875, -4190.98779296875, 37.07113265991210937, 0.383971005678176879, 0, 0, 0.190808296203613281, 0.981627285480499267, 120, 255, 1, 45505), -- Prickly Pear Fruit (Area: Valley of Wisdom - Difficulty: 0)
(@OGUID+222, 204722, 1, 1637, 5171, '0', '0', 0, 1787.2603759765625, -4225.580078125, 40.45119857788085937, 5.692877769470214843, -0.01083993911743164, -0.00167560577392578, -0.29091453552246093, 0.956686139106750488, 120, 255, 1, 45505), -- Brazier (Area: Valley of Wisdom - Difficulty: 0)
(@OGUID+223, 207147, 1, 1637, 5171, '0', '0', 0, 1790.6197509765625, -4205.1806640625, 40.47301101684570312, 5.881760597229003906, 0, 0, -0.19936752319335937, 0.979924798011779785, 120, 255, 1, 45505), -- Barbershop Chair (Area: Valley of Wisdom - Difficulty: 0)
(@OGUID+224, 207148, 1, 1637, 5171, '0', '0', 0, 1786.19970703125, -4199.96044921875, 40.5210113525390625, 0.860993266105651855, 0, 0, 0.417322158813476562, 0.908758580684661865, 120, 255, 1, 45505), -- Barbershop Chair (Area: Valley of Wisdom - Difficulty: 0)
(@OGUID+225, 207149, 1, 1637, 5171, '0', '0', 0, 1783.0400390625, -4200.720703125, 40.51891708374023437, 1.911136388778686523, 0, 0, 0.816641807556152343, 0.577144801616668701, 120, 255, 1, 45505), -- Barbershop Chair (Area: Valley of Wisdom - Difficulty: 0)
(@OGUID+226, 207150, 1, 1637, 5171, '0', '0', 0, 1779.020751953125, -4203.69140625, 40.515716552734375, 2.713986396789550781, 0, 0, 0.977231025695800781, 0.212178006768226623, 120, 255, 1, 45505), -- Barbershop Chair (Area: Valley of Wisdom - Difficulty: 0)
(@OGUID+227, 203969, 1, 1637, 5171, '0', '0', 0, 1792.9305419921875, -4219.2119140625, 40.92210769653320312, 2.600535154342651367, 0, 0, 0.963629722595214843, 0.26724100112915039, 120, 255, 1, 45505), -- Prickly Pear Fruit (Area: Valley of Wisdom - Difficulty: 0)
(@OGUID+228, 206732, 1, 1637, 5171, '0', '0', 0, 1788.8194580078125, -4239.84033203125, 40.83969879150390625, 3.036874771118164062, 0, 0, 0.998629570007324218, 0.05233500525355339, 120, 255, 1, 45505), -- Mailbox (Area: Valley of Wisdom - Difficulty: 0)
(@OGUID+229, 207146, 1, 1637, 0, '0', '0', 0, 1778.2794189453125, -4207.220703125, 40.5231170654296875, 3.516847848892211914, 0, 0, -0.98244953155517578, 0.186528548598289489, 120, 255, 1, 45505), -- Barbershop Chair (Area: 0 - Difficulty: 0)
(@OGUID+230, 206733, 1, 1637, 0, '0', '0', 0, 1735, -4197.359375, 51.77339935302734375, 3.831001043319702148, 0, 0, -0.94117546081542968, 0.337918221950531005, 120, 255, 1, 45505), -- Mailbox (Area: 0 - Difficulty: 0)
(@OGUID+231, 204723, 1, 1637, 0, '0', '0', 0, 1739.890625, -4217.8505859375, 48.87749862670898437, 3.502643346786499023, -0.02431631088256835, 0.005864143371582031, -0.98348331451416015, 0.179262071847915649, 120, 255, 1, 45505), -- Brazier (Area: 0 - Difficulty: 0)
(@OGUID+232, 203969, 1, 1637, 0, '0', '0', 0, 1740.49658203125, -4134.44775390625, 54.16951751708984375, 3.630291461944580078, 0, 0, -0.97029495239257812, 0.241925001144409179, 120, 255, 1, 45505), -- Prickly Pear Fruit (Area: 0 - Difficulty: 0)
(@OGUID+233, 197257, 1, 1637, 0, '0', '0', 0, 1749.85107421875, -4258.8046875, 27.57547569274902343, 3.735006093978881835, 0, 0, -0.95630455017089843, 0.292372345924377441, 120, 255, 1, 45505), -- Brazier (Area: 0 - Difficulty: 0)
(@OGUID+234, 203969, 1, 1637, 0, '0', '0', 0, 1912.8663330078125, -4419.05224609375, 25.15072059631347656, 5.6897735595703125, 0, 0, -0.29237174987792968, 0.956304728984832763, 120, 255, 1, 45505), -- Prickly Pear Fruit (Area: 0 - Difficulty: 0)
(@OGUID+235, 202808, 1, 1637, 0, '0', '0', 0, 1840.9189453125, -4458.85546875, 47.72420501708984375, 3.735006093978881835, 0, 0, -0.95630455017089843, 0.292372345924377441, 120, 255, 1, 45505), -- Brazier (Area: 0 - Difficulty: 0)
(@OGUID+236, 35591, 1, 1637, 0, '0', '0', 0, 1848.23388671875, -4478.90087890625, 21.92966079711914062, 5.492579460144042968, 0, 0, -0.38508796691894531, 0.92287987470626831, 120, 255, 1, 45505), -- Fishing Bobber (Area: 0 - Difficulty: 0)
(@OGUID+237, 203969, 1, 1637, 0, '0', '0', 0, 1880.3646240234375, -4474.30908203125, 23.49345970153808593, 6.178466320037841796, 0, 0, -0.05233573913574218, 0.998629570007324218, 120, 255, 1, 45505), -- Prickly Pear Fruit (Area: 0 - Difficulty: 0)
(@OGUID+238, 202810, 1, 1637, 0, '0', '0', 0, 1916.26806640625, -4428.35693359375, 24.85906791687011718, 4.1538848876953125, 0, 0, -0.8746194839477539, 0.484810054302215576, 120, 255, 1, 45505), -- Brazier (Area: 0 - Difficulty: 0)
(@OGUID+239, 197261, 1, 1637, 0, '0', '0', 0, 1887.9820556640625, -4451.58642578125, 19.59604263305664062, 3.569199085235595703, 0, 0, -0.97723102569580078, 0.212178006768226623, 120, 255, 1, 45505), -- Brazier (Area: 0 - Difficulty: 0)
(@OGUID+240, 207632, 1, 1637, 0, '0', '0', 0, 1883.107666015625, -4476.87158203125, 23.60117721557617187, 1.736601948738098144, 0, 0, 0.763232231140136718, 0.646124243736267089, 120, 255, 1, 45505), -- Mailbox (Area: 0 - Difficulty: 0)
(@OGUID+241, 202815, 1, 1637, 0, '0', '0', 0, 1909.5401611328125, -4461.66943359375, 53.53421783447265625, 4.651303291320800781, 0, 0, -0.72837066650390625, 0.685183286666870117, 120, 255, 1, 45505), -- Burning Embers (Area: 0 - Difficulty: 0)
(@OGUID+242, 204679, 1, 1637, 0, '0', '0', 0, 1923.8194580078125, -4452.720703125, 23.75609970092773437, 4.584630966186523437, -0.02281665802001953, -0.02362537384033203, -0.75034046173095703, 0.660235106945037841, 120, 255, 1, 45505), -- Brazier (Area: 0 - Difficulty: 0)
(@OGUID+243, 204680, 1, 1637, 0, '0', '0', 0, 1875.2291259765625, -4511.63037109375, 23.51070022583007812, 4.045221328735351562, 0.006555080413818359, 0.004502296447753906, -0.89962387084960937, 0.436593204736709594, 120, 255, 1, 45505), -- Brazier (Area: 0 - Difficulty: 0)
(@OGUID+244, 204698, 1, 1637, 0, '0', '0', 0, 1900.9896240234375, -4475.830078125, 24.46699905395507812, 3.240732908248901367, 0.01130533218383789, -0.04243659973144531, -0.99782752990722656, 0.049107477068901062, 120, 255, 1, 45505), -- Brazier (Area: 0 - Difficulty: 0)
(@OGUID+245, 204706, 1, 1637, 0, '0', '0', 0, 1901.9305419921875, -4507.080078125, 25.96389961242675781, 4.052303791046142578, 0.004828453063964843, 0.007885932922363281, -0.89804935455322265, 0.439797580242156982, 120, 255, 1, 45505), -- Brazier (Area: 0 - Difficulty: 0)
(@OGUID+246, 208054, 1, 1637, 0, '0', '0', 0, 1931.9757080078125, -4464.82275390625, 24.13924789428710937, 1.928588032722473144, 0, 0, 0.821646690368652343, 0.569997072219848632, 120, 255, 1, 45505), -- Mailbox (Area: 0 - Difficulty: 0)
(@OGUID+247, 203969, 1, 1637, 0, '0', '0', 0, 1856.0625, -4537.30224609375, 24.78924751281738281, 1.466075778007507324, 0, 0, 0.669130325317382812, 0.74314504861831665, 120, 255, 1, 45505), -- Prickly Pear Fruit (Area: 0 - Difficulty: 0)
(@OGUID+248, 204678, 1, 1637, 0, '0', '0', 0, 1935.140625, -4457.44970703125, 23.73180007934570312, 1.401047110557556152, -0.01023387908935546, 0.017774581909179687, 0.644426345825195312, 0.764391303062438964, 120, 255, 1, 45505), -- Brazier (Area: 0 - Difficulty: 0)
(@OGUID+249, 204694, 1, 1637, 0, '0', '0', 0, 1854.7291259765625, -4529.25, 24.5316009521484375, 4.165752410888671875, -0.02363348007202148, 0.021259307861328125, -0.87143707275390625, 0.489476203918457031, 120, 255, 1, 45505); -- Brazier (Area: 0 - Difficulty: 0)

INSERT INTO `gameobject` (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnDifficulties`, `PhaseId`, `PhaseGroup`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `VerifiedBuild`) VALUES
(@OGUID+250, 202817, 1, 1637, 0, '0', '0', 0, 1922.7191162109375, -4518.3076171875, 29.33587837219238281, 4.223697185516357421, 0, 0, -0.85716724395751953, 0.515038192272186279, 120, 255, 1, 45505), -- Brazier (Area: 0 - Difficulty: 0)
(@OGUID+251, 204940, 1, 1637, 5167, '0', '0', 0, 1941.1064453125, -4504.33154296875, 27.59749221801757812, 2.790262699127197265, 0, 0, 0.984610557556152343, 0.174762919545173645, 120, 255, 1, 45505), -- Brazier (Area: The Drag - Difficulty: 0)
(@OGUID+252, 209045, 1, 1637, 5167, '0', '0', 0, 1934.7100830078125, -4512.6650390625, 29.50701522827148437, 5.218535900115966796, 0, 0, -0.507537841796875, 0.861629426479339599, 120, 255, 1, 45505), -- Shady Lady Figurine (Area: The Drag - Difficulty: 0)
(@OGUID+253, 204941, 1, 1637, 5167, '0', '0', 0, 1953.278076171875, -4495.64892578125, 27.67189788818359375, 2.589545726776123046, 0, 0, 0.962146759033203125, 0.272531807422637939, 120, 255, 1, 45505), -- Burning Embers (Area: The Drag - Difficulty: 0)
(@OGUID+254, 204707, 1, 1637, 5167, '0', '0', 0, 1892.170166015625, -4554.61962890625, 30.85650062561035156, 0.986111819744110107, 0, 0, 0.47332000732421875, 0.880890548229217529, 120, 255, 1, 45505), -- Brazier (Area: The Drag - Difficulty: 0)
(@OGUID+255, 204708, 1, 1637, 5167, '0', '0', 0, 1911.94970703125, -4541.0693359375, 30.84029769897460937, 1.343903779983520507, 0, 0, 0.622514724731445312, 0.782608091831207275, 120, 255, 1, 45505), -- Brazier (Area: The Drag - Difficulty: 0)
(@OGUID+256, 209045, 1, 1637, 5167, '0', '0', 0, 1933.7725830078125, -4512.1474609375, 29.27992820739746093, 3.298687219619750976, 0, 0, -0.99691677093505859, 0.078466430306434631, 120, 255, 1, 45505), -- Shady Lady Figurine (Area: The Drag - Difficulty: 0)
(@OGUID+257, 209050, 1, 1637, 5167, '0', '0', 0, 1935.904541015625, -4520.60791015625, 29.43332290649414062, 3.333590030670166015, 0, 0, -0.99539566040039062, 0.095851235091686248, 120, 255, 1, 45505), -- Shady Lady Falcon (Area: The Drag - Difficulty: 0)
(@OGUID+258, 209050, 1, 1637, 5167, '0', '0', 0, 1935.6458740234375, -4518.8974609375, 29.27992820739746093, 3.194002151489257812, 0, 0, -0.99965667724609375, 0.026201646775007247, 120, 255, 1, 45505), -- Shady Lady Falcon (Area: The Drag - Difficulty: 0)
(@OGUID+259, 376514, 1, 1637, 5167, '0', '0', 0, 1834.140625, -4565.59033203125, 24.98375511169433593, 0, 0, 0, 0, 1, 120, 255, 1, 45505), -- Sleeping Mat (Area: The Drag - Difficulty: 0)
(@OGUID+260, 209050, 1, 1637, 5167, '0', '0', 0, 1935.876708984375, -4519.986328125, 29.42612075805664062, 2.321286916732788085, 0, 0, 0.917059898376464843, 0.398749500513076782, 120, 255, 1, 45505), -- Shady Lady Falcon (Area: The Drag - Difficulty: 0)
(@OGUID+261, 202811, 1, 1637, 5167, '0', '0', 0, 1956.633544921875, -4468.498046875, 43.11188507080078125, 4.668757438659667968, 0, 0, -0.72236347198486328, 0.691513597965240478, 120, 255, 1, 45505), -- Brazier (Area: The Drag - Difficulty: 0)
(@OGUID+262, 202813, 1, 1637, 5167, '0', '0', 0, 1955.923828125, -4470.76025390625, 25.96005630493164062, 4.668757438659667968, 0, 0, -0.72236347198486328, 0.691513597965240478, 120, 255, 1, 45505), -- Brazier (Area: The Drag - Difficulty: 0)
(@OGUID+263, 202814, 1, 1637, 5167, '0', '0', 0, 1956.3345947265625, -4468.8916015625, 35.93848800659179687, 4.310965538024902343, 0, 0, -0.83388519287109375, 0.55193793773651123, 120, 255, 1, 45505), -- Burning Embers (Area: The Drag - Difficulty: 0)
(@OGUID+264, 209045, 1, 1637, 5167, '0', '0', 0, 1933.2882080078125, -4512.8505859375, 29.27992820739746093, 4.049167633056640625, 0, 0, -0.89879322052001953, 0.438372820615768432, 120, 255, 1, 45505), -- Shady Lady Figurine (Area: The Drag - Difficulty: 0)
(@OGUID+265, 209045, 1, 1637, 5167, '0', '0', 0, 1935.6180419921875, -4513.0693359375, 29.50572776794433593, 3.298687219619750976, 0, 0, -0.99691677093505859, 0.078466430306434631, 120, 255, 1, 45505), -- Shady Lady Figurine (Area: The Drag - Difficulty: 0)
(@OGUID+266, 209050, 1, 1637, 5167, '0', '0', 0, 1935.85595703125, -4517.31787109375, 29.27992820739746093, 2.478367090225219726, 0, 0, 0.94551849365234375, 0.325568377971649169, 120, 255, 1, 45505), -- Shady Lady Falcon (Area: The Drag - Difficulty: 0)
(@OGUID+267, 203969, 1, 1637, 5167, '0', '0', 0, 1919.0677490234375, -4536.70166015625, 31.46887588500976562, 0.401424884796142578, 0, 0, 0.199367523193359375, 0.979924798011779785, 120, 255, 1, 45505), -- Prickly Pear Fruit (Area: The Drag - Difficulty: 0)
(@OGUID+268, 209049, 1, 1637, 5167, '0', '0', 0, 1930.8646240234375, -4521.6474609375, 29.27992820739746093, 1.727874636650085449, 0, 0, 0.760405540466308593, 0.649448513984680175, 120, 255, 1, 45505), -- Shady Lady Croc (Area: The Drag - Difficulty: 0)
(@OGUID+269, 209050, 1, 1637, 5167, '0', '0', 0, 1935.017333984375, -4519.35791015625, 29.27992820739746093, 3.682650327682495117, 0, 0, -0.96362972259521484, 0.26724100112915039, 120, 255, 1, 45505), -- Shady Lady Falcon (Area: The Drag - Difficulty: 0)
(@OGUID+270, 202816, 1, 1637, 5167, '0', '0', 0, 1933.063232421875, -4511.02294921875, 29.33587837219238281, 3.569199085235595703, 0, 0, -0.97723102569580078, 0.212178006768226623, 120, 255, 1, 45505), -- Brazier (Area: The Drag - Difficulty: 0)
(@OGUID+271, 207631, 1, 1637, 5167, '0', '0', 0, 1895.185791015625, -4553.25537109375, 30.78155517578125, 6.213373661041259765, 0, 0, -0.03489875793457031, 0.999390840530395507, 120, 255, 1, 45505), -- Mailbox (Area: The Drag - Difficulty: 0)
(@OGUID+272, 204612, 1, 1637, 5167, '0', '0', 0, 1895.028564453125, -4559.29443359375, 61.75275421142578125, 6.095720291137695312, 0, 0, -0.09359550476074218, 0.995610296726226806, 120, 255, 1, 45505), -- Bonfire (Area: The Drag - Difficulty: 0)
(@OGUID+273, 204613, 1, 1637, 5167, '0', '0', 0, 1916.7314453125, -4544.65576171875, 61.75275421142578125, 2.92983412742614746, 0, 0, 0.9944000244140625, 0.105681590735912323, 120, 255, 1, 45505), -- Bonfire (Area: The Drag - Difficulty: 0)
(@OGUID+274, 202805, 1, 1637, 5167, '0', '0', 0, 1813.311279296875, -4574.19921875, 23.07546043395996093, 3.735006093978881835, 0, 0, -0.95630455017089843, 0.292372345924377441, 120, 255, 1, 45505), -- Brazier (Area: The Drag - Difficulty: 0)
(@OGUID+275, 195222, 1, 1637, 5167, '0', '0', 0, 1922.3975830078125, -4572.111328125, 65.67560577392578125, 6.03883981704711914, 0, 0, -0.12186908721923828, 0.9925462007522583, 120, 255, 1, 45505), -- Stage (Area: The Drag - Difficulty: 0)
(@OGUID+276, 35591, 1, 1637, 5167, '0', '0', 0, 1851.368408203125, -4477.85400390625, 21.92966079711914062, 4.794604301452636718, 0, 0, -0.67745018005371093, 0.735568702220916748, 120, 255, 1, 45505), -- Fishing Bobber (Area: The Drag - Difficulty: 0)
(@OGUID+277, 195222, 1, 1637, 5167, '0', '0', 0, 1930.3524169921875, -4566.8818359375, 65.6829071044921875, 2.897245407104492187, 0, 0, 0.99254608154296875, 0.121869951486587524, 120, 255, 1, 45505), -- Stage (Area: The Drag - Difficulty: 0)
(@OGUID+278, 204614, 1, 1637, 5167, '0', '0', 0, 1883.053955078125, -4607.1796875, 38.221343994140625, 2.144448757171630859, 0, 0, 0.878266334533691406, 0.478171765804290771, 120, 255, 1, 45505), -- Bonfire (Area: The Drag - Difficulty: 0)
(@OGUID+279, 204616, 1, 1637, 5167, '0', '0', 0, 1894.5623779296875, -4608.92431640625, 49.58268356323242187, 2.164205789566040039, 0, 0, 0.882946968078613281, 0.469472706317901611, 120, 255, 1, 45505), -- Torch (Area: The Drag - Difficulty: 0)
(@OGUID+280, 204617, 1, 1637, 5167, '0', '0', 0, 1928.66357421875, -4585.92236328125, 49.58269119262695312, 2.164205789566040039, 0, 0, 0.882946968078613281, 0.469472706317901611, 120, 255, 1, 45505), -- Torch (Area: The Drag - Difficulty: 0)
(@OGUID+281, 204619, 1, 1637, 5167, '0', '0', 0, 1916.1461181640625, -4583.716796875, 35.89393997192382812, 1.359052658081054687, 0, 0, 0.628424644470214843, 0.777870476245880126, 120, 255, 1, 45505), -- Bonfire (Area: The Drag - Difficulty: 0)
(@OGUID+282, 204615, 1, 1637, 5167, '0', '0', 0, 1940.6500244140625, -4587.9404296875, 38.221343994140625, 2.144448757171630859, 0, 0, 0.878266334533691406, 0.478171765804290771, 120, 255, 1, 45505), -- Bonfire (Area: The Drag - Difficulty: 0)
(@OGUID+283, 204618, 1, 1637, 5167, '0', '0', 0, 1907.17626953125, -4611.486328125, 35.89393997192382812, 1.359052658081054687, 0, 0, 0.628424644470214843, 0.777870476245880126, 120, 255, 1, 45505), -- Bonfire (Area: The Drag - Difficulty: 0)
(@OGUID+284, 204635, 1, 1637, 5167, '0', '0', 0, 1934.1571044921875, -4612.7587890625, 70.71018218994140625, 4.500646591186523437, 0, 0, -0.77787017822265625, 0.628425002098083496, 120, 255, 1, 45505), -- Bonfire (Area: The Drag - Difficulty: 0)
(@OGUID+285, 204636, 1, 1637, 5167, '0', '0', 0, 1976.27490234375, -4584.35009765625, 71.62149810791015625, 2.92983412742614746, 0, 0, 0.9944000244140625, 0.105681590735912323, 120, 255, 1, 45505), -- Bonfire (Area: The Drag - Difficulty: 0)
(@OGUID+286, 204637, 1, 1637, 5167, '0', '0', 0, 1885.260009765625, -4645.74072265625, 70.77020263671875, 5.921322345733642578, 0, 0, -0.17994594573974609, 0.983676493167877197, 120, 255, 1, 45505), -- Bonfire (Area: The Drag - Difficulty: 0)
(@OGUID+287, 204638, 1, 1637, 5167, '0', '0', 0, 1858.30078125, -4663.63818359375, 71.54546356201171875, 4.317927837371826171, 0, 0, -0.83195877075195312, 0.554837405681610107, 120, 255, 1, 45505), -- Bonfire (Area: The Drag - Difficulty: 0)
(@OGUID+288, 203969, 1, 1637, 5167, '0', '0', 0, 1943.904541015625, -4622.08837890625, 34.85605621337890625, 1.500982880592346191, 0, 0, 0.681998252868652343, 0.731353819370269775, 120, 255, 1, 45505), -- Prickly Pear Fruit (Area: The Drag - Difficulty: 0)
(@OGUID+289, 205109, 1, 1637, 5167, '0', '0', 0, 1884.5577392578125, -4674.00390625, 38.53533172607421875, 4.660029888153076171, 0, 0, -0.72537422180175781, 0.688354730606079101, 120, 255, 1, 45505), -- Guild Vault (Area: The Drag - Difficulty: 0)
(@OGUID+290, 325890, 1, 1637, 5167, '0', '0', 0, 1822.7620849609375, -4648.90673828125, 94.39881134033203125, 0, 0, 0, 0, 1, 120, 255, 1, 45505), -- Hyper-Compressed Ocean (Area: The Drag - Difficulty: 0)
(@OGUID+291, 203969, 1, 1637, 5167, '0', '0', 0, 1893.19970703125, -4651.2744140625, 36.44156265258789062, 5.95157480239868164, 0, 0, -0.16504669189453125, 0.986285746097564697, 120, 255, 1, 45505), -- Prickly Pear Fruit (Area: The Drag - Difficulty: 0)
(@OGUID+292, 281340, 1, 1637, 5167, '0', '0', 0, 1914.140625, -4661.890625, 33.60919952392578125, 0.27925160527229309, 0, 0, 0.139172554016113281, 0.990268170833587646, 120, 255, 1, 45505), -- Warchief's Command Board (Area: The Drag - Difficulty: 0)
(@OGUID+293, 204684, 1, 1637, 5167, '0', '0', 0, 1927.1492919921875, -4635.05029296875, 33.25770187377929687, 0.549776852130889892, 0, 0, 0.271439552307128906, 0.962455451488494873, 120, 255, 1, 45505), -- Brazier (Area: The Drag - Difficulty: 0)
(@OGUID+294, 204685, 1, 1637, 5167, '0', '0', 0, 1906.84033203125, -4649.13037109375, 33.507598876953125, 0.663225173950195312, 0, 0, 0.325568199157714843, 0.945518553256988525, 120, 255, 1, 45505), -- Brazier (Area: The Drag - Difficulty: 0)
(@OGUID+295, 339239, 1, 1637, 5167, '0', '0', 0, 1948.626708984375, -4623.21875, 34.51961135864257812, 4.905241012573242187, 0.005166530609130859, 0.027632713317871093, -0.63523483276367187, 0.771807253360748291, 120, 255, 1, 45505), -- Vulpera Caravan (Area: The Drag - Difficulty: 0)
(@OGUID+296, 207636, 1, 1637, 5167, '0', '0', 0, 1909.732666015625, -4647.09716796875, 33.44169235229492187, 3.141592741012573242, 0, 0, -1, 0, 120, 255, 1, 45505), -- Mailbox (Area: The Drag - Difficulty: 0)
(@OGUID+297, 205142, 1, 1637, 5167, '0', '0', 0, 1875.199951171875, -4673.22998046875, 38.5010986328125, 4.660029888153076171, 0, 0, -0.72537422180175781, 0.688354730606079101, 120, 255, 1, 45505), -- Generic Human Chair Low End - Prop (Unusable) (Area: The Drag - Difficulty: 0)
(@OGUID+298, 205142, 1, 1637, 5167, '0', '0', 0, 1867.9200439453125, -4677.72998046875, 38.62220001220703125, 6.230826377868652343, 0, 0, -0.02617645263671875, 0.999657332897186279, 120, 255, 1, 45505), -- Generic Human Chair Low End - Prop (Unusable) (Area: The Drag - Difficulty: 0)
(@OGUID+299, 207638, 1, 1637, 5167, '0', '0', 0, 1909.1978759765625, -4679.2568359375, 35.30212783813476562, 3.412121534347534179, 0, 0, -0.99086570739746093, 0.134852290153503417, 120, 255, 1, 45505), -- Mailbox (Area: The Drag - Difficulty: 0)
(@OGUID+300, 204701, 1, 1637, 5167, '0', '0', 0, 1936.220458984375, -4667.05029296875, 33.15909957885742187, 2.62986159324645996, 0.018093585968017578, -0.01508426666259765, 0.967122077941894531, 0.253219276666641235, 120, 255, 1, 45505), -- Brazier (Area: The Drag - Difficulty: 0)
(@OGUID+301, 205108, 1, 1637, 5167, '0', '0', 0, 1883.6756591796875, -4690.83447265625, 38.53533172607421875, 1.518436193466186523, 0, 0, 0.6883544921875, 0.725374460220336914, 120, 255, 1, 45505), -- Guild Vault (Area: The Drag - Difficulty: 0)
(@OGUID+302, 205142, 1, 1637, 5167, '0', '0', 0, 1867.6400146484375, -4684.68994140625, 38.62220001220703125, 0, 0, 0, 0, 1, 120, 255, 1, 45505), -- Generic Human Chair Low End - Prop (Unusable) (Area: The Drag - Difficulty: 0)
(@OGUID+303, 187376, 1, 1637, 5167, '0', '0', 0, 1978.06591796875, -4642.52783203125, 26.74469757080078125, 1.078695654869079589, 0, 0, 0.513576507568359375, 0.858043789863586425, 120, 255, 1, 45505), -- NPC Fishing Bobber (Area: The Drag - Difficulty: 0)
(@OGUID+304, 205142, 1, 1637, 5167, '0', '0', 0, 1875.219970703125, -4690.31982421875, 38.5010986328125, 1.500982880592346191, 0, 0, 0.681998252868652343, 0.731353819370269775, 120, 255, 1, 45505), -- Generic Human Chair Low End - Prop (Unusable) (Area: The Drag - Difficulty: 0)
(@OGUID+305, 207640, 1, 1637, 5167, '0', '0', 0, 1968.2257080078125, -4686.5537109375, 31.29800033569335937, 2.809975385665893554, 0, 0, 0.986285209655761718, 0.165049895644187927, 120, 255, 1, 45505), -- Mailbox (Area: The Drag - Difficulty: 0)
(@OGUID+306, 204702, 1, 1637, 5167, '0', '0', 0, 1914.970458984375, -4690.580078125, 35.52119827270507812, 2.254613161087036132, -0.00928258895874023, -0.03274726867675781, 0.902654647827148437, 0.429017543792724609, 120, 255, 1, 45505), -- Brazier (Area: The Drag - Difficulty: 0)
(@OGUID+307, 204713, 1, 1637, 5167, '0', '0', 0, 1954.44970703125, -4716.8505859375, 37.17369842529296875, 5.420626640319824218, -0.00188684463500976, -0.01607418060302734, -0.4179086685180664, 0.908344864845275878, 120, 255, 1, 45505), -- Brazier (Area: The Drag - Difficulty: 0)
(@OGUID+308, 204714, 1, 1637, 5167, '0', '0', 0, 1943.59033203125, -4723.02978515625, 37.22490310668945312, 5.465998172760009765, -0.0173807144165039, -0.03643321990966796, -0.3970499038696289, 0.916908860206604003, 120, 255, 1, 45505), -- Brazier (Area: The Drag - Difficulty: 0)
(@OGUID+309, 382172, 1, 1637, 5167, '0', '0', 0, 1895.8697509765625, -4745.3974609375, 46.8444976806640625, 5.893294334411621093, 0, 0, -0.19371318817138671, 0.981058180332183837, 120, 255, 1, 45505), -- Idol (Area: The Drag - Difficulty: 0)
(@OGUID+310, 207637, 1, 1637, 5167, '0', '0', 0, 1926.579833984375, -4725.501953125, 35.91756820678710937, 4.145159721374511718, 0, 0, -0.87672615051269531, 0.48098987340927124, 120, 255, 1, 45505), -- Mailbox (Area: The Drag - Difficulty: 0)
(@OGUID+311, 349789, 1, 1637, 5167, '0', '0', 0, 1928.9718017578125, -4759.556640625, 76.2653045654296875, 0.619591057300567626, 0, 0, 0.304863929748535156, 0.952395915985107421, 120, 255, 1, 45505), -- Doodad_WinterOrc_Small_Brazier_02_2 (Area: The Drag - Difficulty: 0)
(@OGUID+312, 382167, 1, 1637, 5167, '0', '0', 0, 1894.967041015625, -4751.95849609375, 47.19874954223632812, 2.354811429977416992, 0.405690193176269531, 0.646290779113769531, -0.38125419616699218, 0.521889805793762207, 120, 255, 1, 45505), -- Scroll (Area: The Drag - Difficulty: 0)
(@OGUID+313, 382171, 1, 1637, 5167, '0', '0', 0, 1895.7864990234375, -4750.15625, 46.8444976806640625, 0.505086719989776611, 0, 0, 0.249867439270019531, 0.96828007698059082, 120, 255, 1, 45505), -- Jewels (Area: The Drag - Difficulty: 0)
(@OGUID+314, 382173, 1, 1637, 5167, '0', '0', 0, 1894.5, -4747.55224609375, 46.03210067749023437, 6.240077018737792968, -0.00374221801757812, -0.17360782623291015, -0.0212249755859375, 0.984579026699066162, 120, 255, 1, 45505), -- Tablet (Area: The Drag - Difficulty: 0)
(@OGUID+315, 204682, 1, 1637, 5167, '0', '0', 0, 1948.8004150390625, -4741.23974609375, 37.14519882202148437, 0.846484839916229248, 0, 0, 0.410718917846679687, 0.911761999130249023, 120, 255, 1, 45505), -- Brazier (Area: The Drag - Difficulty: 0)
(@OGUID+316, 382162, 1, 1637, 5167, '0', '0', 0, 1894.8228759765625, -4750.8349609375, 48.24264907836914062, 0, 0, 0, 0, 1, 120, 255, 1, 45505), -- Lamp (Area: The Drag - Difficulty: 0)
(@OGUID+317, 382163, 1, 1637, 5167, '0', '0', 0, 1894.532958984375, -4752.21875, 47.09788894653320312, 5.620455741882324218, 0.430964469909667968, 0.560596466064453125, -0.43096446990966796, 0.560598671436309814, 120, 255, 1, 45505), -- Scroll (Area: The Drag - Difficulty: 0)
(@OGUID+318, 382164, 1, 1637, 5167, '0', '0', 0, 1896.24658203125, -4753.88916015625, 46.08704376220703125, 0.284268021583557128, 0, 0, 0.141655921936035156, 0.989915966987609863, 120, 255, 1, 45505), -- Scroll (Area: The Drag - Difficulty: 0)
(@OGUID+319, 382165, 1, 1637, 5167, '0', '0', 0, 1895.9149169921875, -4754.03662109375, 46.83065032958984375, 4.972391128540039062, 0, 0, -0.60947418212890625, 0.792805910110473632, 120, 255, 1, 45505), -- Scroll (Area: The Drag - Difficulty: 0)
(@OGUID+320, 382169, 1, 1637, 5167, '0', '0', 0, 1894.890625, -4750.81787109375, 46.04754257202148437, 3.464095115661621093, 0, 0, -0.98702716827392578, 0.160553231835365295, 120, 255, 1, 45505), -- Books (Area: The Drag - Difficulty: 0)
(@OGUID+321, 382170, 1, 1637, 5167, '0', '0', 0, 1894.7864990234375, -4753.40478515625, 48.63379287719726562, 0.423007547855377197, 0, 0, 0.209930419921875, 0.977716326713562011, 120, 255, 1, 45505), -- Scrolls (Area: The Drag - Difficulty: 0)
(@OGUID+322, 382174, 1, 1637, 5167, '0', '0', 0, 1894.53125, -4748.955078125, 46.03210067749023437, 5.65583038330078125, -0.05358076095581054, -0.16517448425292968, -0.30387115478515625, 0.936754405498504638, 120, 255, 1, 45505), -- Tablet (Area: The Drag - Difficulty: 0)
(@OGUID+323, 351924, 1, 1637, 5168, '0', '0', 0, 1948.2198486328125, -4778.31787109375, 38.81164169311523437, 5.272964954376220703, 0, 0, -0.48390388488769531, 0.875121116638183593, 120, 255, 1, 45505), -- Chair (Area: Valley of Honor - Difficulty: 0)
(@OGUID+324, 351925, 1, 1637, 5168, '0', '0', 0, 1948.83984375, -4781.63623046875, 38.81164169311523437, 1.771130800247192382, 0, 0, 0.774272918701171875, 0.632851839065551757, 120, 255, 1, 45505), -- Chair (Area: Valley of Honor - Difficulty: 0)
(@OGUID+325, 204683, 1, 1637, 5168, '0', '0', 0, 1979.279541015625, -4743.640625, 37.25, 0.584683895111083984, 0, 0, 0.288195610046386718, 0.957571566104888916, 120, 255, 1, 45505), -- Brazier (Area: Valley of Honor - Difficulty: 0)
(@OGUID+326, 203969, 1, 1637, 5168, '0', '0', 0, 1981.9913330078125, -4753.23095703125, 37.50444412231445312, 5.95157480239868164, 0, 0, -0.16504669189453125, 0.986285746097564697, 120, 255, 1, 45505), -- Prickly Pear Fruit (Area: Valley of Honor - Difficulty: 0)
(@OGUID+327, 204705, 1, 1637, 5168, '0', '0', 0, 2018, -4682.22900390625, 28.45929908752441406, 3.938857555389404296, -0.01278924942016601, -0.01126384735107421, -0.92142486572265625, 0.388182669878005981, 120, 255, 1, 45505), -- Brazier (Area: Valley of Honor - Difficulty: 0)
(@OGUID+328, 349788, 1, 1637, 5168, '0', '0', 0, 1995.8150634765625, -4764.8173828125, 76.2653045654296875, 2.364918231964111328, 0, 0, 0.925539970397949218, 0.378649920225143432, 120, 255, 1, 45505), -- Doodad_WinterOrc_Small_Brazier_01_2 (Area: Valley of Honor - Difficulty: 0)
(@OGUID+329, 351430, 1, 1637, 5168, '0', '0', 0, 1940.800048828125, -4792.1962890625, 39.04814910888671875, 0.793568789958953857, 0, 0, 0.386454582214355468, 0.92230844497680664, 120, 255, 1, 45505), -- 6OR_WOODENDUMMY01 (Area: Valley of Honor - Difficulty: 0)
(@OGUID+330, 351919, 1, 1637, 5168, '0', '0', 0, 1944.9091796875, -4809.98388671875, 38.8376007080078125, 2.751257658004760742, 0, 0, 0.981015205383300781, 0.193930819630622863, 120, 255, 1, 45505), -- Chair (Area: Valley of Honor - Difficulty: 0)
(@OGUID+331, 351921, 1, 1637, 5168, '0', '0', 0, 1959.092529296875, -4794.6455078125, 39.19965744018554687, 0.679298877716064453, 0, 0, 0.333156585693359375, 0.942871510982513427, 120, 255, 1, 45505), -- Chair (Area: Valley of Honor - Difficulty: 0)
(@OGUID+332, 351922, 1, 1637, 5168, '0', '0', 0, 1975.5511474609375, -4780.6640625, 38.81164169311523437, 4.1927337646484375, 0, 0, -0.86503791809082031, 0.501706480979919433, 120, 255, 1, 45505), -- Chair (Area: Valley of Honor - Difficulty: 0)
(@OGUID+333, 351923, 1, 1637, 5168, '0', '0', 0, 1974.602294921875, -4783.7880859375, 38.81164169311523437, 1.423908591270446777, 0, 0, 0.653314590454101562, 0.757086575031280517, 120, 255, 1, 45505), -- Chair (Area: Valley of Honor - Difficulty: 0)
(@OGUID+334, 351926, 1, 1637, 5168, '0', '0', 0, 1962.3011474609375, -4793.89990234375, 39.20597076416015625, 3.117354393005371093, 0, 0, 0.999926567077636718, 0.012118821963667869, 120, 255, 1, 45505), -- Chair (Area: Valley of Honor - Difficulty: 0)
(@OGUID+335, 204703, 1, 1637, 5168, '0', '0', 0, 2022, -4728.9306640625, 28.65960121154785156, 3.20585489273071289, -0.0145421028137207, -0.00109195709228515, -0.99937725067138671, 0.032131168991327285, 120, 255, 1, 45505), -- Brazier (Area: Valley of Honor - Difficulty: 0)
(@OGUID+336, 349790, 1, 1637, 5168, '0', '0', 0, 1924.2581787109375, -4836.76806640625, 76.2653045654296875, 0.619591057300567626, 0, 0, 0.304863929748535156, 0.952395915985107421, 120, 255, 1, 45505), -- Doodad_WinterOrc_Small_Brazier_03_2 (Area: Valley of Honor - Difficulty: 0)
(@OGUID+337, 351918, 1, 1637, 5168, '0', '0', 0, 1981.8658447265625, -4804.435546875, 39.1158447265625, 4.473770618438720703, 0, 0, -0.78624439239501953, 0.617915689945220947, 120, 255, 1, 45505), -- Chair (Area: Valley of Honor - Difficulty: 0)
(@OGUID+338, 351920, 1, 1637, 5168, '0', '0', 0, 1973.496826171875, -4813.59521484375, 38.81476593017578125, 0.770869970321655273, 0, 0, 0.375962257385253906, 0.926634967327117919, 120, 255, 1, 45505), -- Chair (Area: Valley of Honor - Difficulty: 0)
(@OGUID+339, 187376, 1, 1637, 5168, '0', '0', 0, 1978.06591796875, -4642.52783203125, 26.74469757080078125, 1.078695654869079589, 0, 0, 0.513576507568359375, 0.858043789863586425, 120, 255, 1, 45505), -- NPC Fishing Bobber (Area: Valley of Honor - Difficulty: 0)
-- (@OGUID+340, 175080, 1, 1637, 5168, '0', '0', 0, 0, 0, 0, 4.127908706665039062, 0, 0, -0.88084220886230468, 0.473409950733184814, 120, 255, 1, 45505), -- 0 (Area: Valley of Honor - Difficulty: 0) - !!! transport !!!
(@OGUID+341, 323850, 1, 1637, 0, '0', '0', 0, 1448.6434326171875, -4531.02099609375, 19.84333038330078125, 1.946041464805603027, 0, 0, 0.826589584350585937, 0.56280517578125, 120, 255, 1, 45505), -- Portal to Azsuna (Area: 0 - Difficulty: 0)
(@OGUID+342, 1731, 1, 14, 817, '0', '0', 0, 1438.91845703125, -4681.48779296875, -5.09225988388061523, 0, 0, 0, 0, 1, 120, 255, 1, 45505), -- Copper Vein (Area: Skull Rock - Difficulty: 0)
(@OGUID+343, 207889, 1, 14, 817, '0', '0', 0, 2936.058837890625, -4993.609375, 126.7327194213867187, 6.051208972930908203, 0, 0, -0.11572837829589843, 0.993280887603759765, 120, 255, 24, 45505), -- 0 (Area: Skull Rock - Difficulty: 0)
(@OGUID+344, 203471, 1, 14, 817, '0', '0', 0, 1492.359375, -5010.5693359375, 10.487701416015625, 4.860742568969726562, 0, 0, -0.65275955200195312, 0.757565200328826904, 120, 255, 1, 45505), -- Gooblin Boat (Area: Skull Rock - Difficulty: 0)
(@OGUID+345, 152614, 1, 14, 817, '0', '0', 0, 2263.702392578125, -5565.5595703125, 33.93857574462890625, 5.183629035949707031, 0, 0, -0.52249813079833984, 0.852640450000762939, 120, 255, 24, 45505), -- 0 (Area: Skull Rock - Difficulty: 0)
(@OGUID+346, 1731, 1, 14, 817, '0', '0', 0, 1471.220458984375, -4749.328125, 9.143307685852050781, 0, 0, 0, 0, 1, 120, 255, 1, 45505), -- Copper Vein (Area: Skull Rock - Difficulty: 0)
(@OGUID+347, 1731, 1, 14, 817, '0', '0', 0, 1520.842041015625, -4687.046875, 8.9249420166015625, 0, 0, 0, 0, 1, 120, 255, 1, 45505), -- Copper Vein (Area: Skull Rock - Difficulty: 0)
(@OGUID+348, 204172, 1, 14, 817, '0', '0', 0, 1388.079833984375, -4673.73974609375, 31.69370269775390625, 3.251642942428588867, 0, 0, -0.99848651885986328, 0.054997246712446212, 120, 255, 1, 45505), -- Brazier (Area: Skull Rock - Difficulty: 0)
-- (@OGUID+349, 375041, 1, 14, 817, '0', '0', 0, 0, 0, 0, 4.975605964660644531, 0, 0, -0.60819911956787109, 0.793784499168395996, 120, 255, 1, 45505), -- 0 (Area: Skull Rock - Difficulty: 0) - !!! transport !!!
(@OGUID+350, 1731, 1, 14, 817, '0', '0', 0, 1427.6666259765625, -4741.6650390625, -0.29331600666046142, 0, 0, 0, 0, 1, 120, 255, 1, 45505), -- Copper Vein (Area: Skull Rock - Difficulty: 0)
(@OGUID+351, 355504, 1, 14, 817, '0', '0', 0, 1359.8896484375, -4919.12841796875, 61.8638458251953125, 3.490667104721069335, 0, 0, -0.98480701446533203, 0.173652306199073791, 120, 255, 1, 45505), -- Portal (Area: Skull Rock - Difficulty: 0)
(@OGUID+352, 204171, 1, 14, 817, '0', '0', 0, 1367.9896240234375, -4771.23974609375, 26.84569931030273437, 6.044143199920654296, 0.017004013061523437, 0.005869865417480468, -0.11934375762939453, 0.992690026760101318, 120, 255, 1, 45505), -- Brazier (Area: Skull Rock - Difficulty: 0)
(@OGUID+353, 204170, 1, 14, 817, '0', '0', 0, 1439.4896240234375, -4855.52978515625, 15.15410041809082031, 2.919991254806518554, 0, 0, 0.993867874145507812, 0.110574141144752502, 120, 255, 1, 45505), -- Brazier (Area: Skull Rock - Difficulty: 0)
(@OGUID+354, 204167, 1, 14, 817, '0', '0', 0, 1402.859375, -4865.80908203125, 14.50570011138916015, 5.738711357116699218, -0.01343870162963867, 0.023556709289550781, -0.2684335708618164, 0.962916374206542968, 120, 255, 1, 45505), -- Brazier (Area: Skull Rock - Difficulty: 0)
-- (@OGUID+355, 376708, 0, 14, 817, '0', '0', 0, -52.8783378601074218, 1.732030034065246582, 12.77374267578125, 3.416499614715576171, 0, 0, -0.99056816101074218, 0.137020975351333618, 120, 255, 1, 45505), -- Reliquary Crate (Area: Skull Rock - Difficulty: 0) - !!! on transport - transport template not found !!!
-- (@OGUID+356, 376840, 0, 14, 817, '0', '0', 0, -51.9497222900390625, 2.944993019104003906, 12.72313499450683593, 5.899599075317382812, 0, 0, -0.19061946868896484, 0.981664001941680908, 120, 255, 1, 45505), -- Reliquary Jar (Area: Skull Rock - Difficulty: 0) - !!! on transport - transport template not found !!!
-- (@OGUID+357, 376674, 0, 14, 817, '0', '0', 0, -54.4086112976074218, 1.037235260009765625, 12.84708213806152343, 5.899599075317382812, 0, 0, -0.19061946868896484, 0.981664001941680908, 120, 255, 1, 45505), -- Reliquary Crate (Area: Skull Rock - Difficulty: 0) - !!! on transport - transport template not found !!!
(@OGUID+358, 204169, 1, 14, 817, '0', '0', 0, 1414.0399169921875, -4930.390625, 10.88969993591308593, 4.647882461547851562, -0.00471973419189453, 0.024222373962402343, -0.72913169860839843, 0.683928370475769042, 120, 255, 1, 45505), -- Brazier (Area: Skull Rock - Difficulty: 0)
-- (@OGUID+359, 376708, 0, 14, 817, '0', '0', 0, -53.6231231689453125, 2.328609943389892578, 12.812957763671875, 3.416499614715576171, 0, 0, -0.99056816101074218, 0.137020975351333618, 120, 255, 1, 45505), -- Reliquary Crate (Area: Skull Rock - Difficulty: 0) - !!! on transport - transport template not found !!!
-- (@OGUID+360, 376708, 0, 14, 4982, '0', '0', 0, -54.3126411437988281, -1.3646780252456665, 12.84527587890625, 5.899599075317382812, 0, 0, -0.19061946868896484, 0.981664001941680908, 120, 255, 1, 45505), -- Reliquary Crate (Area: The Dranosh'ar Blockade - Difficulty: 0) - !!! on transport - transport template not found !!!
-- (@OGUID+361, 376846, 0, 14, 4982, '0', '0', 0, 53.14555740356445312, 2.638839960098266601, 31.86487770080566406, 2.975310802459716796, 0, 0, 0.996545791625976562, 0.083045139908790588, 120, 255, 1, 45505), -- Reliquary Pillows (Area: The Dranosh'ar Blockade - Difficulty: 0) - !!! on transport - transport template not found !!!
-- (@OGUID+362, 186238, 1, 14, 4982, '0', '0', 0, 0, 0, 0, 2.39718484878540039, 0, 0, 0.931528091430664062, 0.363669395446777343, 120, 255, 1, 45505), -- 0 (Area: The Dranosh'ar Blockade - Difficulty: 0) - !!! transport !!!
(@OGUID+363, 203471, 1, 14, 4982, '0', '0', 0, 1492.359375, -5010.5693359375, 10.487701416015625, 4.860742568969726562, 0, 0, -0.65275955200195312, 0.757565200328826904, 120, 255, 1, 45505), -- Gooblin Boat (Area: The Dranosh'ar Blockade - Difficulty: 0)
(@OGUID+364, 204167, 1, 14, 4982, '0', '0', 0, 1402.859375, -4865.80908203125, 14.50570011138916015, 5.738711357116699218, -0.01343870162963867, 0.023556709289550781, -0.2684335708618164, 0.962916374206542968, 120, 255, 1, 45505), -- Brazier (Area: The Dranosh'ar Blockade - Difficulty: 0)
(@OGUID+365, 204168, 1, 14, 4982, '0', '0', 0, 1387.829833984375, -4937.94970703125, 11.15979957580566406, 3.740308761596679687, -0.01888799667358398, 0.017002105712890625, -0.95530128479003906, 0.29453974962234497, 120, 255, 1, 45505), -- Brazier (Area: The Dranosh'ar Blockade - Difficulty: 0)
(@OGUID+366, 204169, 1, 14, 4982, '0', '0', 0, 1414.0399169921875, -4930.390625, 10.88969993591308593, 4.647882461547851562, -0.00471973419189453, 0.024222373962402343, -0.72913169860839843, 0.683928370475769042, 120, 255, 1, 45505), -- Brazier (Area: The Dranosh'ar Blockade - Difficulty: 0)
(@OGUID+367, 204170, 1, 14, 4982, '0', '0', 0, 1439.4896240234375, -4855.52978515625, 15.15410041809082031, 2.919991254806518554, 0, 0, 0.993867874145507812, 0.110574141144752502, 120, 255, 1, 45505); -- Brazier (Area: The Dranosh'ar Blockade - Difficulty: 0)
DELETE FROM `gameobject_addon` WHERE `guid` BETWEEN @OGUID+0 AND @OGUID+367;
INSERT INTO `gameobject_addon` (`guid`, `parent_rotation0`, `parent_rotation1`, `parent_rotation2`, `parent_rotation3`, `WorldEffectID`, `AIAnimKitID`) VALUES
(@OGUID+0, 0, 0, 0.998391687870025634, -0.05669287219643592, 0, 0), -- Doodad_OGRaid_FrontGate_Back
(@OGUID+2, 0, 0, 0.998391687870025634, -0.05669287219643592, 0, 0), -- Bonfire
(@OGUID+3, 0, 0, 0.998391687870025634, -0.05669287219643592, 0, 0), -- Fire Pit
(@OGUID+4, 0, 0, 0.998391687870025634, -0.05669287219643592, 0, 0), -- Fire Pit
(@OGUID+5, 0, 0, 0.511293411254882812, 0.859406232833862304, 0, 0), -- Guild Vault
(@OGUID+6, 0, 0, 0.511293411254882812, 0.859406232833862304, 0, 0), -- Guild Vault
(@OGUID+9, 0, 0, -0.51703834533691406, 0.855962216854095458, 0, 0), -- Torch
(@OGUID+10, 0, 0, -0.51703834533691406, 0.855962216854095458, 0, 0), -- Torch
(@OGUID+12, 0, 0, -0.51703834533691406, 0.855962216854095458, 0, 0), -- Torch
(@OGUID+14, 0, 0, -0.51703834533691406, 0.855962216854095458, 0, 0), -- Torch
(@OGUID+15, 0, 0, 0.998391687870025634, -0.05669287219643592, 0, 0), -- Bonfire
(@OGUID+17, 0, 0, 0.998391687870025634, -0.05669287219643592, 0, 0), -- Sconce
(@OGUID+19, 0, 0, 0.998391687870025634, -0.05669287219643592, 0, 0), -- Sconce
(@OGUID+26, 0, 0, 0.956304728984832763, -0.29237172007560729, 0, 0), -- 0
(@OGUID+27, 0, 0, 0.998391687870025634, -0.05669287219643592, 0, 0), -- The Gates of Orgrimmar
(@OGUID+29, 0, 0, 0.956304728984832763, -0.29237172007560729, 0, 0), -- 0
(@OGUID+30, 0, 0, 0.956304728984832763, -0.29237172007560729, 0, 0), -- 0
(@OGUID+38, 0, 0, 0.998391687870025634, -0.05669287219643592, 0, 0), -- Doodad_OGRaid_FrontGate_Back
(@OGUID+39, 0, 0, 0.998391687870025634, -0.05669287219643592, 0, 0), -- Bonfire
(@OGUID+42, 0, 0, 0.998391687870025634, -0.05669287219643592, 0, 0), -- Fire Pit
(@OGUID+43, 0, 0, 0.998391687870025634, -0.05669287219643592, 0, 0), -- Fire Pit
(@OGUID+44, 0, 0, 0.511293411254882812, 0.859406232833862304, 0, 0), -- Guild Vault
(@OGUID+46, 0, 0, 0.511293411254882812, 0.859406232833862304, 0, 0), -- Guild Vault
(@OGUID+50, 0, 0, -0.51703834533691406, 0.855962216854095458, 0, 0), -- Torch
(@OGUID+52, 0, 0, -0.51703834533691406, 0.855962216854095458, 0, 0), -- Torch
(@OGUID+54, 0, 0, -0.51703834533691406, 0.855962216854095458, 0, 0), -- Torch
(@OGUID+56, 0, 0, -0.51703834533691406, 0.855962216854095458, 0, 0), -- Torch
(@OGUID+58, 0, 0, 0.998391687870025634, -0.05669287219643592, 0, 0), -- Bonfire
(@OGUID+60, 0, 0, 0.998391687870025634, -0.05669287219643592, 0, 0), -- Sconce
(@OGUID+62, 0, 0, 0.998391687870025634, -0.05669287219643592, 0, 0), -- Sconce
(@OGUID+71, 0, 0, 0, 1, 8830, 0), -- Warchief's Command Board
(@OGUID+78, 0, 0, 0.998391687870025634, -0.05669287219643592, 0, 0), -- The Gates of Orgrimmar
(@OGUID+84, 0, 0, -0.51703834533691406, 0.855962216854095458, 0, 0), -- Torch
(@OGUID+86, 0, 0, -0.51703834533691406, 0.855962216854095458, 0, 0), -- Torch
(@OGUID+87, 0, 0, 0.923879504203796386, -0.38268348574638366, 0, 0), -- Auction Materials
(@OGUID+88, 0, 0, -0.705582857131958, 0.70862746238708496, 0, 0), -- Fire Wall
(@OGUID+89, 0, 0, -0.705582857131958, 0.70862746238708496, 0, 0), -- Fire Wall
(@OGUID+91, 0, 0, -0.51703834533691406, 0.855962216854095458, 0, 0), -- Torch
(@OGUID+95, 0, 0, -0.51703834533691406, 0.855962216854095458, 0, 0), -- Torch
(@OGUID+96, 0, 0, -0.51703834533691406, 0.855962216854095458, 0, 0), -- Grommash Throne
(@OGUID+101, 0, 0, -0.51703834533691406, 0.855962216854095458, 0, 0), -- Torch
(@OGUID+102, 0, 0, -0.51703834533691406, 0.855962216854095458, 0, 0), -- Torch
(@OGUID+105, 0, 0, -0.7009093165397644, 0.713250398635864257, 0, 0), -- Fire
(@OGUID+106, 0, 0, -0.7009093165397644, 0.713250398635864257, 0, 0), -- Anvil
(@OGUID+109, 0, 0, 0.956304728984832763, -0.29237172007560729, 0, 0), -- Brazier
(@OGUID+110, 0, 0, 0.956304728984832763, -0.29237172007560729, 0, 0), -- Brazier
(@OGUID+111, 0, 0, 0.956304728984832763, -0.29237172007560729, 0, 0), -- Brazier
(@OGUID+122, 0, 0, 0.956304728984832763, -0.29237172007560729, 0, 0), -- Brazier
(@OGUID+123, 0, 0, 0.956304728984832763, -0.29237172007560729, 0, 0), -- Brazier
(@OGUID+124, 0, 0, 0.956304728984832763, -0.29237172007560729, 0, 0), -- Brazier
(@OGUID+125, 0, 0, 0.956304728984832763, -0.29237172007560729, 0, 0), -- The Slow Blade
(@OGUID+126, 0, 0, 0.956304728984832763, -0.29237172007560729, 0, 0), -- Arcane Enclave
(@OGUID+127, 0, 0, 0.956304728984832763, -0.29237172007560729, 0, 0), -- Brazier
(@OGUID+128, 0, 0, 0.956304728984832763, -0.29237172007560729, 0, 0), -- Brazier
(@OGUID+130, 0, 0, 0.956304728984832763, -0.29237172007560729, 0, 0), -- Brazier
(@OGUID+131, 0, 0, 0.956304728984832763, -0.29237172007560729, 0, 0), -- Brazier
(@OGUID+132, 0, 0, 0.956304728984832763, -0.29237172007560729, 0, 0), -- Dark Earth
(@OGUID+133, 0, 0, 0.956304728984832763, -0.29237172007560729, 0, 0), -- Brazier
(@OGUID+134, 0, 0, 0.956304728984832763, -0.29237172007560729, 0, 0), -- Brazier
(@OGUID+138, 0, 0, 0.956304728984832763, -0.29237172007560729, 0, 0), -- Smoked Meat Rack
(@OGUID+139, 0, 0, 0.956304728984832763, -0.29237172007560729, 0, 0), -- Burning Embers
(@OGUID+140, 0, 0, 0.956304728984832763, -0.29237172007560729, 0, 0), -- Meeting Stone
(@OGUID+142, 0, 0, 0.956304728984832763, -0.29237172007560729, 0, 0), -- Brazier
(@OGUID+144, 0, 0, 0.358368098735809326, 0.933580398559570312, 0, 0), -- Forge
(@OGUID+145, 0, 0, 0.358368098735809326, 0.933580398559570312, 0, 0), -- Anvil
(@OGUID+147, 0, 0, 0.956304728984832763, -0.29237172007560729, 0, 0), -- Brazier
(@OGUID+148, 0, 0, 0.956304728984832763, -0.29237172007560729, 0, 0), -- Burning Embers
(@OGUID+149, 0, 0, 0.956304728984832763, -0.29237172007560729, 0, 0), -- Brazier
(@OGUID+150, 0, 0, 0.956304728984832763, -0.29237172007560729, 0, 0), -- Forge
(@OGUID+151, 0, 0, 0.956304728984832763, -0.29237172007560729, 0, 0), -- Anvil
(@OGUID+161, 0, 0, 0.956304728984832763, -0.29237172007560729, 0, 0), -- Brazier
(@OGUID+162, 0, 0, 0.956304728984832763, -0.29237172007560729, 0, 0), -- Burning Embers
(@OGUID+163, 0, 0, 0.956304728984832763, -0.29237172007560729, 0, 0), -- Brazier
(@OGUID+165, 0, 0, 0.956304728984832763, -0.29237172007560729, 0, 0), -- Brazier
(@OGUID+166, 0, 0, 0.956304728984832763, -0.29237172007560729, 0, 0), -- Brazier
(@OGUID+168, 0, 0, 0.956304728984832763, -0.29237172007560729, 0, 0), -- Brazier
(@OGUID+169, 0, 0, 0.956304728984832763, -0.29237172007560729, 0, 0), -- Mailbox
(@OGUID+170, 0, 0, 0.956304728984832763, -0.29237172007560729, 0, 0), -- Brazier
(@OGUID+171, 0, 0, 0.956304728984832763, -0.29237172007560729, 0, 0), -- Brazier
(@OGUID+172, 0, 0, 0.956304728984832763, -0.29237172007560729, 0, 0), -- Brazier
(@OGUID+173, 0, 0, 0.956304728984832763, -0.29237172007560729, 0, 0), -- Shadowswift Brotherhood
(@OGUID+181, 0, 0, 0.956304728984832763, -0.29237172007560729, 0, 0), -- Brazier
(@OGUID+182, 0, 0, 0.956304728984832763, -0.29237172007560729, 0, 0), -- Brazier
(@OGUID+183, 0, 0, 0.956304728984832763, -0.29237172007560729, 0, 0), -- Brazier
(@OGUID+184, 0, 0, 0.956304728984832763, -0.29237172007560729, 0, 0), -- Rekkul's Poisons
(@OGUID+185, 0, 0, 0.956304728984832763, -0.29237172007560729, 0, 0), -- Darkfire Enclave
(@OGUID+186, 0, 0, 0.956304728984832763, -0.29237172007560729, 0, 0), -- Ironwood Staves and Wands
(@OGUID+187, 0, 0, 0.956304728984832763, -0.29237172007560729, 0, 0), -- Brazier
(@OGUID+188, 0, 0, 0.956304728984832763, -0.29237172007560729, 0, 0), -- Brazier
(@OGUID+189, 0, 0, 0.956304728984832763, -0.29237172007560729, 0, 0), -- Brazier
(@OGUID+190, 0, 0, 0.956304728984832763, -0.29237172007560729, 0, 0), -- Brazier
(@OGUID+191, 0, 0, 0.956304728984832763, -0.29237172007560729, 0, 0), -- Brazier
(@OGUID+192, 0, 0, 0.956304728984832763, -0.29237172007560729, 0, 0), -- Brazier
(@OGUID+193, 0, 0, 0.956304728984832763, -0.29237172007560729, 0, 0), -- Shadowdeep Reagents
(@OGUID+196, 0, 0, 0.956304728984832763, -0.29237172007560729, 0, 0), -- Brazier
(@OGUID+209, 0, 0, 0.983254909515380859, 0.182235434651374816, 0, 0), -- Burning Embers
(@OGUID+212, 0, 0, 0.983254909515380859, 0.182235434651374816, 0, 0), -- Burning Embers
(@OGUID+213, 0, 0, 0.983254909515380859, 0.182235434651374816, 0, 0), -- Burning Embers
(@OGUID+219, 0, 0, -0.58778542280197143, 0.809016883373260498, 0, 0), -- Burning Embers
(@OGUID+223, 0, 0, 0.956304728984832763, -0.29237172007560729, 16227, 0), -- Barbershop Chair
(@OGUID+224, 0, 0, 0.956304728984832763, -0.29237172007560729, 16227, 0), -- Barbershop Chair
(@OGUID+225, 0, 0, 0.956304728984832763, -0.29237172007560729, 16227, 0), -- Barbershop Chair
(@OGUID+226, 0, 0, 0.956304728984832763, -0.29237172007560729, 16227, 0), -- Barbershop Chair
(@OGUID+229, 0, 0, 0.956304728984832763, -0.29237172007560729, 16227, 0), -- Barbershop Chair
(@OGUID+233, 0, 0, 0.956304728984832763, -0.29237172007560729, 0, 0), -- Brazier
(@OGUID+235, 0, 0, 0.956304728984832763, -0.29237172007560729, 0, 0), -- Brazier
(@OGUID+236, 0, 0, 0, 1, 2773, 0), -- Fishing Bobber
(@OGUID+238, 0, 0, 0.956304728984832763, -0.29237172007560729, 0, 0), -- Brazier
(@OGUID+239, 0, 0, 0.956304728984832763, -0.29237172007560729, 0, 0), -- Brazier
(@OGUID+241, 0, 0, 0.956304728984832763, -0.29237172007560729, 0, 0), -- Burning Embers
(@OGUID+250, 0, 0, 0.956304728984832763, -0.29237172007560729, 0, 0), -- Brazier
(@OGUID+251, 0, 0, 0.956304728984832763, -0.29237172007560729, 0, 0), -- Brazier
(@OGUID+253, 0, 0, 0.956304728984832763, -0.29237172007560729, 0, 0), -- Burning Embers
(@OGUID+261, 0, 0, 0.956304728984832763, -0.29237172007560729, 0, 0), -- Brazier
(@OGUID+262, 0, 0, 0.956304728984832763, -0.29237172007560729, 0, 0), -- Brazier
(@OGUID+263, 0, 0, 0.956304728984832763, -0.29237172007560729, 0, 0), -- Burning Embers
(@OGUID+270, 0, 0, 0.956304728984832763, -0.29237172007560729, 0, 0), -- Brazier
(@OGUID+272, 0, 0, 0.956304728984832763, -0.29237172007560729, 0, 0), -- Bonfire
(@OGUID+273, 0, 0, 0.956304728984832763, -0.29237172007560729, 0, 0), -- Bonfire
(@OGUID+274, 0, 0, 0.956304728984832763, -0.29237172007560729, 0, 0), -- Brazier
(@OGUID+276, 0, 0, 0, 1, 2773, 0), -- Fishing Bobber
(@OGUID+278, 0, 0, 0.956304728984832763, -0.29237172007560729, 0, 0), -- Bonfire
(@OGUID+279, 0, 0, 0.956304728984832763, -0.29237172007560729, 0, 0), -- Torch
(@OGUID+280, 0, 0, 0.956304728984832763, -0.29237172007560729, 0, 0), -- Torch
(@OGUID+281, 0, 0, 0.956304728984832763, -0.29237172007560729, 0, 0), -- Bonfire
(@OGUID+282, 0, 0, 0.956304728984832763, -0.29237172007560729, 0, 0), -- Bonfire
(@OGUID+283, 0, 0, 0.956304728984832763, -0.29237172007560729, 0, 0), -- Bonfire
(@OGUID+284, 0, 0, 0.956304728984832763, -0.29237172007560729, 0, 0), -- Bonfire
(@OGUID+285, 0, 0, 0.956304728984832763, -0.29237172007560729, 0, 0), -- Bonfire
(@OGUID+286, 0, 0, 0.956304728984832763, -0.29237172007560729, 0, 0), -- Bonfire
(@OGUID+287, 0, 0, 0.956304728984832763, -0.29237172007560729, 0, 0), -- Bonfire
(@OGUID+289, 0, 0, 0.6883544921875, 0.725374460220336914, 0, 0), -- Guild Vault
(@OGUID+292, 0, 0, 0, 1, 8830, 0), -- Warchief's Command Board
(@OGUID+301, 0, 0, 0.6883544921875, 0.725374460220336914, 0, 0), -- Guild Vault
(@OGUID+303, 0, 0, 0, 1, 2773, 0), -- NPC Fishing Bobber
(@OGUID+311, 0, 0, 0.678800821304321289, 0.734322428703308105, 0, 0), -- Doodad_WinterOrc_Small_Brazier_02_2
(@OGUID+323, 0, 0, 0.678800821304321289, 0.734322428703308105, 0, 0), -- Chair
(@OGUID+324, 0, 0, 0.678800821304321289, 0.734322428703308105, 0, 0), -- Chair
(@OGUID+328, 0, 0, 0.678800821304321289, 0.734322428703308105, 0, 0), -- Doodad_WinterOrc_Small_Brazier_01_2
(@OGUID+329, 0, 0, 0.678800821304321289, 0.734322428703308105, 0, 0), -- 6OR_WOODENDUMMY01
(@OGUID+330, 0, 0, 0.678800821304321289, 0.734322428703308105, 0, 0), -- Chair
(@OGUID+331, 0, 0, 0.678800821304321289, 0.734322428703308105, 0, 0), -- Chair
(@OGUID+332, 0, 0, 0.678800821304321289, 0.734322428703308105, 0, 0), -- Chair
(@OGUID+333, 0, 0, 0.678800821304321289, 0.734322428703308105, 0, 0), -- Chair
(@OGUID+334, 0, 0, 0.678800821304321289, 0.734322428703308105, 0, 0), -- Chair
(@OGUID+336, 0, 0, 0.678800821304321289, 0.734322428703308105, 0, 0), -- Doodad_WinterOrc_Small_Brazier_03_2
(@OGUID+337, 0, 0, 0.678800821304321289, 0.734322428703308105, 0, 0), -- Chair
(@OGUID+338, 0, 0, 0.678800821304321289, 0.734322428703308105, 0, 0), -- Chair
(@OGUID+339, 0, 0, 0, 1, 2773, 0), -- NPC Fishing Bobber
(@OGUID+340, 0, 0, 0.998391687870025634, -0.05669287219643592, 0, 3503), -- Portal to Oribos
(@OGUID+341, 0, 0, 0.998391687870025634, -0.05669287219643592, 0, 3503), -- Portal to Azsuna
(@OGUID+343, 0, 0, 1, -0.00000004371138828, 0, 0), -- 0
(@OGUID+344, 0, 0, 0, 1, 0, 0), -- Gooblin Boat
(@OGUID+345, 0, 0, -0.52249842882156372, 0.852640211582183837, 0, 0), -- 0
(@OGUID+363, 0, 0, 0, 1, 0, 0); -- Gooblin Boat


DELETE FROM `creature_template_addon` WHERE `entry` IN (193450 /*193450 (Archmage Khadgar) - Invisible Man Transform*/, 194065 /*194065 (Ketuna Skyflame)*/, 194116 /*194116 (Shin Summerhill)*/, 194073 /*194073 (Lux Fizzlegig) - -0-*/, 194583 /*194583 (Krakz Cloudgrease)*/, 189609 /*189609 (Quartermaster Furlein)*/, 160530 /*160530 (Friend Pronk)*/, 160529 /*160529 (Vim Brineheart)*/, 160528 /*160528 (Poen Gillbrack)*/, 194569 /*194569 (Si'va)*/, 194050 /*194050 (Zalanti)*/, 194576 /*194576 (Vernell Bartlett) - -0-*/, 194561 /*194561 (Talanath Goldcrest)*/, 194361 /*194361 (Rathamaresh)*/, 194577 /*194577 (Rinka)*/, 160526 /*160526 (Neri Sharpfin)*/, 194563 /*194563 (Arandil Featherdawn) - -0-*/, 194582 /*194582 (Mathog Hideflayer)*/, 194581 /*194581 (Trauga Bloodhelm) - -0-*/, 194056 /*194056 (Dragon Kite)*/, 194055 /*194055 (Dahanu Highwing)*/, 197288 /*197288 (Skarukaru)*/, 197279 /*197279 (Naleidea Rivergleam) - -0-*/, 189075 /*189075 (Seagull)*/, 184810 /*184810 (Boss Magor)*/, 189554 /*189554 (Expedition Supplier) - -0-*/, 194115 /*194115 (Airship Worker) - -0-*/, 184814 /*184814 (Rugged Artisan) - -0-*/, 184813 /*184813 (Brave Researcher) - -0-*/, 100664 /*100664 (Thunder Bluff Native)*/, 100682 /*100682 (Silvermoon Citizen)*/, 100679 /*100679 (Citizen of Kezan)*/, 5822 /*5822 (Felweaver Scornn) - Demon Armor*/, 197611 /*197611 ((Bunny) Sessile + Gigantic AOI)*/, 3204 /*3204 (Gazz'uz) - Demon Skin*/, 100502 /*100502 (Concerned Citizen)*/, 184286 /*184286 (Captain Caspartine) - -0-*/, 184807 /*184807 (The Defiant Dragonscale)*/, 100663 /*100663 (Sen'jin Villager)*/, 168626 /*168626 (Feenix Arcshine) - Molten Armor*/, 171691 /*171691 (Alpheus Cain)*/, 168628 /*168628 (Hretar Riverspeaker) - Water Shield*/, 168597 /*168597 (Avaros Dawnglaive) - Retribution Aura*/, 184798 /*184798 (Chronicler Laz'Kini)*/, 184795 /*184795 (Cataloger Kieule)*/, 180684 /*180684 (Olive)*/, 152561 /*152561 (Hyper-Compressed Ocean Target) - Ride Vehicle Hardcoded*/, 153285 /*153285 (Training Dummy) - Training Dummy Marker, Banner of the Alliance*/, 188169 /*188169 (Worker) - Sleeping Sleep*/, 190535 /*190535 (Quizla Blastcaps) - -0-*/, 184787 /*184787 (Boss Magor)*/, 197680 /*197680 (Jack the Hammer) - -0-*/, 187710 /*187710 (Handhold)*/, 187709 /*187709 (Handhold)*/, 184796 /*184796 (Pathfinder Tacha)*/, 189091 /*189091 (Handhold)*/, 187711 /*187711 (Handhold)*/, 161223 /*161223 (Torkhan) - -0-*/, 184793 /*184793 (Naleidea Rivergleam) - -0-*/, 184666 /*184666 (Mayla Highmountain)*/, 176012 /*176012 (Ric Catstalker)*/, 184812 /*184812 (Restless Explorer) - -0-, -0-*/, 141920 /*141920 (Traveling Son)*/, 187775 /*187775 (Kanyaku) - -0-*/, 141528 /*141528 (Clara Spelldriver)*/, 141310 /*141310 (Associate Telemancer Rafcav)*/, 197771 /*197771 (Yuyu)*/, 149371 /*149371 (Draenor Adventurer)*/, 149296 /*149296 (Northrend Adventurer)*/, 149270 /*149270 (Orgrimmar Guardian Mage) - Invisibility and Stealth Detection*/, 188157 /*188157 (Worker) - Sleeping Sleep*/, 188656 /*188656 (Worker) - -0-*/, 102529 /*102529 (Kor'vas Bloodthorn) - Glaive Anim Replacement*/, 100636 /*100636 (High Overlord Saurfang)*/, 175135 /*175135 (Rokhan)*/);
INSERT INTO `creature_template_addon` (`entry`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `aiAnimKit`, `movementAnimKit`, `meleeAnimKit`, `visibilityDistanceType`, `auras`) VALUES
(193450, 0, 0, 0, 0, 0, 0, 0, 0, 0, '152821'), -- 193450 (Archmage Khadgar) - Invisible Man Transform
(194065, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- 194065 (Ketuna Skyflame)
(194116, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- 194116 (Shin Summerhill)
(194073, 0, 0, 0, 257, 0, 0, 0, 0, 0, '386130'), -- 194073 (Lux Fizzlegig) - -0-
(194583, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- 194583 (Krakz Cloudgrease)
(189609, 0, 0, 0, 256, 0, 0, 0, 0, 0, ''), -- 189609 (Quartermaster Furlein)
(160530, 0, 0, 8, 1, 0, 0, 0, 0, 0, ''), -- 160530 (Friend Pronk)
(160529, 0, 0, 0, 0, 0, 0, 0, 0, 0, ''), -- 160529 (Vim Brineheart)
(160528, 0, 0, 0, 0, 0, 0, 0, 0, 0, ''), -- 160528 (Poen Gillbrack)
(194569, 0, 0, 8, 257, 0, 0, 0, 0, 0, ''), -- 194569 (Si'va)
(194050, 0, 0, 0, 256, 0, 14580, 0, 0, 0, ''), -- 194050 (Zalanti)
(194576, 0, 0, 0, 257, 0, 0, 0, 0, 0, '384513'), -- 194576 (Vernell Bartlett) - -0-
(194561, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- 194561 (Talanath Goldcrest)
(194361, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- 194361 (Rathamaresh)
(194577, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- 194577 (Rinka)
(160526, 0, 90766, 0, 1, 0, 0, 0, 0, 0, ''), -- 160526 (Neri Sharpfin)
(194563, 0, 0, 0, 257, 0, 0, 0, 0, 0, '369706'), -- 194563 (Arandil Featherdawn) - -0-
(194582, 0, 0, 0, 256, 0, 0, 0, 0, 0, ''), -- 194582 (Mathog Hideflayer)
(194581, 0, 0, 0, 256, 0, 0, 0, 0, 0, '369560'), -- 194581 (Trauga Bloodhelm) - -0-
(194056, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- 194056 (Dragon Kite)
(194055, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- 194055 (Dahanu Highwing)
(197288, 0, 0, 0, 0, 0, 25783, 0, 0, 0, ''), -- 197288 (Skarukaru)
(197279, 0, 0, 0, 0, 0, 0, 0, 0, 0, '378042'), -- 197279 (Naleidea Rivergleam) - -0-
(189075, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- 189075 (Seagull)
(184810, 0, 0, 0, 0, 0, 0, 0, 0, 0, ''), -- 184810 (Boss Magor)
(189554, 0, 0, 0, 1, 0, 0, 0, 0, 0, '372737'), -- 189554 (Expedition Supplier) - -0-
(194115, 0, 0, 0, 257, 0, 0, 0, 0, 0, '384573'), -- 194115 (Airship Worker) - -0-
(184814, 0, 0, 0, 1, 0, 0, 0, 0, 0, '374319'), -- 184814 (Rugged Artisan) - -0-
(184813, 0, 0, 0, 1, 0, 0, 0, 0, 0, '372740'), -- 184813 (Brave Researcher) - -0-
(100664, 0, 0, 0, 0, 0, 0, 0, 0, 0, ''), -- 100664 (Thunder Bluff Native)
(100682, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- 100682 (Silvermoon Citizen)
(100679, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- 100679 (Citizen of Kezan)
(5822, 0, 0, 0, 1, 0, 0, 0, 0, 0, '79934'), -- 5822 (Felweaver Scornn) - Demon Armor
(197611, 0, 0, 50331648, 1, 0, 0, 0, 0, 4, ''), -- 197611 ((Bunny) Sessile + Gigantic AOI)
(3204, 0, 0, 0, 1, 0, 0, 0, 0, 0, '20798'), -- 3204 (Gazz'uz) - Demon Skin
(100502, 0, 0, 0, 256, 0, 0, 0, 0, 0, ''), -- 100502 (Concerned Citizen)
(184286, 0, 0, 0, 257, 0, 0, 0, 0, 4, '372498'), -- 184286 (Captain Caspartine) - -0-
(184807, 0, 0, 0, 1, 0, 0, 0, 0, 4, ''), -- 184807 (The Defiant Dragonscale)
(100663, 0, 0, 0, 256, 0, 0, 0, 0, 0, ''), -- 100663 (Sen'jin Villager)
(168626, 0, 0, 0, 1, 0, 0, 0, 0, 0, '79849'), -- 168626 (Feenix Arcshine) - Molten Armor
(171691, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- 171691 (Alpheus Cain)
(168628, 0, 0, 0, 1, 0, 0, 0, 0, 0, '79892'), -- 168628 (Hretar Riverspeaker) - Water Shield
(168597, 0, 0, 0, 1, 0, 0, 0, 0, 0, '79976'), -- 168597 (Avaros Dawnglaive) - Retribution Aura
(184798, 0, 0, 0, 0, 0, 0, 0, 0, 0, ''), -- 184798 (Chronicler Laz'Kini)
(184795, 0, 0, 0, 0, 0, 0, 0, 0, 0, ''), -- 184795 (Cataloger Kieule)
(180684, 0, 0, 1, 1, 0, 0, 0, 0, 0, ''), -- 180684 (Olive)
(152561, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, '46598'), -- 152561 (Hyper-Compressed Ocean Target) - Ride Vehicle Hardcoded
(153285, 0, 0, 0, 1, 0, 0, 0, 0, 0, '98892 61573'), -- 153285 (Training Dummy) - Training Dummy Marker, Banner of the Alliance
(188169, 0, 0, 0, 1, 0, 0, 0, 0, 0, '221098'), -- 188169 (Worker) - Sleeping Sleep
(190535, 0, 0, 0, 1, 0, 16996, 0, 0, 0, '374211'), -- 190535 (Quizla Blastcaps) - -0-
(184787, 0, 0, 0, 0, 0, 0, 0, 0, 0, ''), -- 184787 (Boss Magor)
(197680, 0, 0, 0, 1, 0, 0, 0, 0, 0, '296495'), -- 197680 (Jack the Hammer) - -0-
(187710, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- 187710 (Handhold)
(187709, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- 187709 (Handhold)
(184796, 0, 0, 0, 0, 0, 0, 0, 0, 0, ''), -- 184796 (Pathfinder Tacha)
(189091, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- 189091 (Handhold)
(187711, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- 187711 (Handhold)
(161223, 0, 0, 0, 1, 0, 0, 0, 0, 0, '313952'), -- 161223 (Torkhan) - -0-
(184793, 0, 0, 0, 0, 0, 0, 0, 0, 0, '378042'), -- 184793 (Naleidea Rivergleam) - -0-
(184666, 0, 0, 0, 0, 0, 0, 0, 0, 0, ''), -- 184666 (Mayla Highmountain)
(176012, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- 176012 (Ric Catstalker)
(184812, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, '371800 369509'), -- 184812 (Restless Explorer) - -0-, -0-
(141920, 0, 0, 0, 2, 0, 0, 0, 0, 0, ''), -- 141920 (Traveling Son)
(187775, 0, 0, 0, 1, 0, 0, 0, 0, 0, '370841'), -- 187775 (Kanyaku) - -0-
(141528, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- 141528 (Clara Spelldriver)
(141310, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- 141310 (Associate Telemancer Rafcav)
(197771, 0, 0, 1, 1, 0, 0, 0, 0, 0, ''), -- 197771 (Yuyu)
(149371, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- 149371 (Draenor Adventurer)
(149296, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- 149296 (Northrend Adventurer)
(149270, 0, 0, 0, 257, 0, 0, 0, 0, 0, '18950'), -- 149270 (Orgrimmar Guardian Mage) - Invisibility and Stealth Detection
(188157, 0, 0, 0, 1, 0, 0, 0, 0, 0, '221098'), -- 188157 (Worker) - Sleeping Sleep
(188656, 0, 0, 0, 1, 0, 0, 0, 0, 0, '327198'), -- 188656 (Worker) - -0-
(102529, 0, 0, 0, 1, 0, 0, 0, 0, 0, '222589'), -- 102529 (Kor'vas Bloodthorn) - Glaive Anim Replacement
(100636, 0, 0, 0, 1, 0, 0, 0, 0, 3, ''), -- 100636 (High Overlord Saurfang)
(175135, 0, 0, 0, 257, 0, 0, 0, 0, 3, ''); -- 175135 (Rokhan)


UPDATE `creature_template_addon` SET `mount`=2328, `visibilityDistanceType`=4 WHERE `entry`=4311; -- 4311 (Holgar Stormaxe)
UPDATE `creature_template_addon` SET `bytes1`=0 WHERE `entry`=68869; -- 68869 (Luo Luo) - Panda
UPDATE `creature_template_addon` SET `bytes2`=256 WHERE `entry`=46667; -- 46667 (Blademaster Ronakada) - Horde Banner
UPDATE `creature_template_addon` SET `auras`='98892 61573' WHERE `entry`=31146; -- 31146 (Raider's Training Dummy) - Training Dummy Marker, Banner of the Alliance
UPDATE `creature_template_addon` SET `bytes1`=0 WHERE `entry`=7088; -- 7088 (Thuwd)
UPDATE `creature_template_addon` SET `bytes2`=256 WHERE `entry`=7010; -- 7010 (Zilzibin Drumlore)
UPDATE `creature_template_addon` SET `visibilityDistanceType`=3 WHERE `entry`=50088; -- 50088 (Waters of Farseeing)
UPDATE `creature_template_addon` SET `bytes1`=1 WHERE `entry`=45230; -- 45230 (Orgrimmar Brave)
UPDATE `creature_template_addon` SET `auras`='' WHERE `entry`=43062; -- 43062 (Bort)
UPDATE `creature_template_addon` SET `visibilityDistanceType`=3, `auras`='46598 96850 16245 97577' WHERE `entry`=52810; -- 52810 (Toy Cart Bunny) - Ride Vehicle Hardcoded, Toy Cart Contents, Freeze Anim, Handle State
UPDATE `creature_template_addon` SET `auras`='46598 96847' WHERE `entry`=52812; -- 52812 (Toy Cart) - Ride Vehicle Hardcoded, Blue Doll State
UPDATE `creature_template_addon` SET `aiAnimKit`=1348 WHERE `entry`=52809; -- 52809 (Blax Bottlerocket)
UPDATE `creature_template_addon` SET `auras`='' WHERE `entry`=44158; -- 44158 (Orgrimmar Skyway Peon)
UPDATE `creature_template_addon` SET `bytes2`=256 WHERE `entry`=46357; -- 46357 (Gonto)
UPDATE `creature_template_addon` SET `visibilityDistanceType`=3 WHERE `entry`=49131; -- 49131 (Goblin Hot Rod)
UPDATE `creature_template_addon` SET `bytes1`=0, `bytes2`=256, `auras`='' WHERE `entry`=72559; -- 72559 (Thunder Bluff Protector)
UPDATE `creature_template_addon` SET `bytes2`=256 WHERE `entry`=3296; -- 3296 (Orgrimmar Grunt)
UPDATE `creature_template_addon` SET `auras`='' WHERE `entry`=38821; -- 38821 (Dave's Industrial Light and Magic Bunny (Medium)(Sessile))

DELETE FROM `creature_template_scaling` WHERE (`DifficultyID`=0 AND `Entry` IN (193889,193450,194065,194116,194073,194583,189609,194569,194050,194576,194561,194361,194577,194563,194582,194581,195385,184809,194056,194055,195677,195357,197288,195899,197279,180701,189075,184810,184808,194115,189554,184813,197611,184286,184807,184798,184795,184797,188169,190535,197682,184787,197680,197679,187710,184800,184801,187709,184796,189091,187711,184664,190239,184786,184793,184666,184812,187775,197771,188655,197770,197767,188157,187758,188656,189398,97296,102529));
INSERT INTO `creature_template_scaling` (`Entry`, `DifficultyID`, `LevelScalingDeltaMin`, `LevelScalingDeltaMax`, `ContentTuningID`, `VerifiedBuild`) VALUES
(193889, 0, 0, 0, 2151, 45505),
(193450, 0, 0, 0, 2078, 45505),
(194065, 0, 0, 0, 2151, 45505),
(194116, 0, 0, 0, 2151, 45505),
(194073, 0, 0, 0, 2151, 45505),
(194583, 0, 0, 0, 2151, 45505),
(189609, 0, 0, 0, 2151, 45505),
(194569, 0, 0, 0, 2151, 45505),
(194050, 0, 0, 0, 2151, 45505),
(194576, 0, 0, 0, 2151, 45505),
(194561, 0, 0, 0, 2151, 45505),
(194361, 0, 0, 0, 2151, 45505),
(194577, 0, 0, 0, 2151, 45505),
(194563, 0, 0, 0, 2151, 45505),
(194582, 0, 0, 0, 2151, 45505),
(194581, 0, 0, 0, 2151, 45505),
(195385, 0, 0, 0, 2424, 45505),
(184809, 0, 0, 0, 2151, 45505),
(194056, 0, 0, 0, 2151, 45505),
(194055, 0, 0, 0, 2151, 45505),
(195677, 0, 0, 0, 2151, 45505),
(195357, 0, 0, 0, 2424, 45505),
(197288, 0, 0, 0, 2151, 45505),
(195899, 0, 0, 0, 2172, 45505),
(197279, 0, 0, 0, 2151, 45505),
(180701, 0, 0, 0, 2078, 45505),
(189075, 0, 0, 0, 81, 45505),
(184810, 0, 0, 0, 2151, 45505),
(184808, 0, 0, 0, 2151, 45505),
(194115, 0, 0, 0, 2151, 45505),
(189554, 0, 0, 0, 2151, 45505),
(184813, 0, 0, 0, 2151, 45505),
(197611, 0, 0, 0, 2078, 45505),
(184286, 0, 0, 0, 2151, 45505),
(184807, 0, 0, 0, 2151, 45505),
(184798, 0, 0, 0, 2151, 45505),
(184795, 0, 0, 0, 2151, 45505),
(184797, 0, 0, 0, 2151, 45505),
(188169, 0, 0, 0, 866, 45505),
(190535, 0, 0, 0, 2151, 45505),
(197682, 0, 0, 0, 2307, 45505),
(184787, 0, 0, 0, 2151, 45505),
(197680, 0, 0, 0, 2307, 45505),
(197679, 0, 0, 0, 2307, 45505),
(187710, 0, 0, 0, 2078, 45505),
(184800, 0, 0, 0, 2151, 45505),
(184801, 0, 0, 0, 2151, 45505),
(187709, 0, 0, 0, 2078, 45505),
(184796, 0, 0, 0, 2151, 45505),
(189091, 0, 0, 0, 2078, 45505),
(187711, 0, 0, 0, 2078, 45505),
(184664, 0, 0, 0, 2151, 45505),
(190239, 0, 0, 0, 2150, 45505),
(184786, 0, 0, 0, 2151, 45505),
(184793, 0, 0, 0, 2151, 45505),
(184666, 0, 0, 0, 2151, 45505),
(184812, 0, 0, 0, 2151, 45505),
(187775, 0, 0, 0, 866, 45505),
(197771, 0, 0, 0, 293, 45505),
(188655, 0, 0, 0, 866, 45505),
(197770, 0, 0, 0, 293, 45505),
(197767, 0, 0, 0, 293, 45505),
(188157, 0, 0, 0, 866, 45505),
(187758, 0, 0, 0, 866, 45505),
(188656, 0, 0, 0, 866, 45505),
(189398, 0, 0, 0, 2150, 45505),
(97296, 0, 0, 0, 773, 45505),
(102529, 0, 0, 0, 699, 45505);

UPDATE `creature_template_scaling` SET `VerifiedBuild`=45505 WHERE (`DifficultyID`=0 AND `Entry` IN (160530,160529,160528,160527,160526,41621,3300,3108,184814,5951,3100,100664,100682,62116,100679,5822,3127,3204,100502,3198,4311,100663,3197,71100,40891,43239,168598,168626,171691,46985,69333,65065,168623,3353,68869,171689,62445,13842,168551,168628,35364,65008,3354,49573,34955,168553,65074,46667,65071,168596,15186,70301,168597,169166,7951,168621,66022,65078,65076,35845,175084,3333,42709,176261,3332,42638,46642,46619,46618,62193,180684,46622,46620,158789,152561,3359,46621,160452,161203,31146,153285,2855,61369,1420,3365,3316,3350,6987,6986,7088,3225,5811,8659,3351,3347,3348,3366,3321,11066,46181,3346,62197,62196,3345,46741,46742,3371,3372,7010,34765,44160,3405,3404,179897,29143,44783,15188,5892,3403,13417,44788,161223,44785,72939,44782,51230,44770,58199,58193,44780,44779,47336,47335,47321,3322,44781,176012,50088,176095,176094,44787,54004,47663,141920,54113,141912,4953,174147,44723,44745,44740,44743,133271,44726,44725,42548,3327,3335,47254,3330,3328,5875,5816,88706,88705,88704,47233,45230,3334,12136,44735,5909,3189,43062,26537,130911,141528,9564,20493,20489,20491,20490,20488,20486,44918,44948,5639,46716,15476,46718,3317,3315,11017,3364,3363,3413,3412,3368,49737,52810,52032,46708,52812,52809,14498,68979,57801,3369,54473,54472,62200,62199,2857,14451,3367,14499,46709,50477,42506,62194,63626,20492,50488,50323,3310,14881,3216,44919,3331,141310,47253,3329,47248,47247,47246,55382,44158,3084,14377,23635,158637,121541,31720,25075,31727,31726,31725,31724,31723,62115,10880,37072,46358,46357,46512,46359,3319,62822,62821,62198,49131,14376,135201,23128,46140,35068,52034,46555,47571,3323,3314,72654,17098,58155,44338,42594,89830,49622,3312,27489,46556,4047,44872,3144,44868,44867,44866,44865,149371,149296,14392,137762,44853,168459,44851,6466,149270,88703,88702,88701,3313,14375,5614,5613,72559,5611,5610,6929,5609,5606,44856,44854,44852,32520,44878,51195,44876,5817,44871,46572,28960,5188,62114,49837,74228,44877,49750,3296,51346,3370,38821,3342,62195,49743,100636,135202));
UPDATE `creature_template_scaling` SET `ContentTuningID`=866, `VerifiedBuild`=45505 WHERE (`DifficultyID`=0 AND `Entry` IN (45337,45339));
UPDATE `creature_template_scaling` SET `ContentTuningID`=883, `VerifiedBuild`=45505 WHERE (`Entry`=46142 AND `DifficultyID`=0);
UPDATE `creature_template_scaling` SET `ContentTuningID`=2148, `VerifiedBuild`=45505 WHERE (`Entry`=175135 AND `DifficultyID`=0);

DELETE FROM `creature_model_info` WHERE `DisplayID` IN (107041, 108379, 108394, 108386, 108387, 108389, 86940, 108634, 83251, 108388, 108626, 108375, 108393, 108628, 108624, 108392, 108483, 108629, 104841, 108625, 108632, 108631, 104842, 108885, 108867, 108390, 108376, 104840, 108799, 108801, 109493, 108858, 103903, 108870, 108391, 108869, 108862, 106884, 81933, 106349, 101799, 101484, 108775, 105596, 108780, 108798, 101649, 106352, 105598, 108776, 102033, 105169, 108802, 109709, 106383, 106345, 106382, 104821);
INSERT INTO `creature_model_info` (`DisplayID`, `BoundingRadius`, `CombatReach`, `DisplayID_Other_Gender`, `VerifiedBuild`) VALUES
(107041, 0.411357432603836059, 0, 0, 45505),
(108379, 0.698000013828277587, 3, 0, 45505),
(108394, 0.347222000360488891, 1.5, 0, 45505),
(108386, 0.305999994277954101, 1.5, 0, 45505),
(108387, 0.305999994277954101, 1.5, 0, 45505),
(108389, 0.305999994277954101, 1.5, 0, 45505),
(86940, 0.305999994277954101, 1.5, 0, 45505),
(108634, 0.305999994277954101, 1.5, 0, 45505),
(83251, 0.305999994277954101, 1.5, 0, 45505),
(108388, 0.305999994277954101, 1.5, 0, 45505),
(108626, 0.305999994277954101, 1.5, 0, 45505),
(108375, 0.347222000360488891, 1.5, 0, 45505),
(108393, 0.382999986410140991, 1.5, 0, 45505),
(108628, 0.382999986410140991, 1.5, 0, 45505),
(108624, 0.382999986410140991, 1.5, 0, 45505),
(108392, 0.382999986410140991, 1.5, 0, 45505),
(108483, 0.722000002861022949, 2, 0, 45505),
(108629, 0.305999994277954101, 1.5, 0, 45505),
(104841, 0.722000002861022949, 2, 0, 45505),
(108625, 0.382999986410140991, 1.5, 0, 45505),
(108632, 0.372000008821487426, 1.5, 0, 45505),
(108631, 0.236000001430511474, 1.5, 0, 45505),
(104842, 0.722000002861022949, 2, 0, 45505),
(108885, 0.698000013828277587, 3, 0, 45505),
(108867, 0.388999998569488525, 1.5, 0, 45505),
(108390, 0.382999986410140991, 1.5, 0, 45505),
(108376, 0.722000002861022949, 3, 0, 45505),
(104840, 0.722000002861022949, 2, 0, 45505),
(108799, 0.305999994277954101, 1.5, 0, 45505),
(108801, 0.388999998569488525, 1.5, 0, 45505),
(109493, 0.187199994921684265, 1.349999904632568359, 0, 45505),
(108858, 0.372000008821487426, 1.5, 0, 45505),
(103903, 0.120000004768371582, 1.5, 0, 45505),
(108870, 0.382999986410140991, 1.5, 0, 45505),
(108391, 0.382999986410140991, 1.5, 0, 45505),
(108869, 0.698000013828277587, 3, 0, 45505),
(108862, 0.382999986410140991, 1.5, 0, 45505),
(106884, 0.388999998569488525, 1.5, 0, 45505),
(81933, 0.347222000360488891, 1.5, 0, 45505),
(106349, 0.305999994277954101, 1.5, 0, 45505),
(101799, 0.22152663767337799, 0, 0, 45505),
(101484, 0.305999994277954101, 1.5, 0, 45505),
(108775, 0.382999986410140991, 1.5, 0, 45505),
(105596, 1.235417366027832031, 8, 0, 45505),
(108780, 0.305999994277954101, 1.5, 0, 45505),
(108798, 0.305999994277954101, 1.5, 0, 45505),
(101649, 2.108910322189331054, 8, 0, 45505),
(106352, 0.305999994277954101, 1.5, 0, 45505),
(105598, 0.971067428588867187, 6, 0, 45505),
(108776, 0.382999986410140991, 1.5, 0, 45505),
(102033, 0.685899972915649414, 1.899999976158142089, 0, 45505),
(105169, 0.382999986410140991, 1.5, 0, 45505),
(108802, 0.382999986410140991, 1.5, 0, 45505),
(109709, 0.382999986410140991, 1.5, 0, 45505),
(106383, 0.305999994277954101, 1.5, 0, 45505),
(106345, 0.305999994277954101, 1.5, 0, 45505),
(106382, 0.305999994277954101, 1.5, 0, 45505),
(104821, 0.722000002861022949, 2, 0, 45505);

UPDATE `creature_model_info` SET `VerifiedBuild`=45505 WHERE `DisplayID` IN (32172, 93309, 92324, 92325, 91243, 91373, 32529, 43667, 63612, 108876, 32171, 105247, 28029, 85326, 36461, 27319, 60340, 43666, 86335, 30787, 36793, 29349, 33829, 3000, 7624, 1560, 36789, 64311, 193, 29473, 60400, 15730, 16800, 46940, 37365, 4594, 2732, 240, 30441, 4193, 4191, 4515, 36806, 32170, 46126, 32173, 35301, 96906, 96915, 97757, 47465, 43721, 96914, 1374, 46986, 72325, 39637, 13843, 96884, 96916, 29795, 45864, 1375, 36545, 29496, 96885, 43724, 35216, 43722, 96903, 15369, 47982, 96905, 96364, 15352, 96913, 44740, 43726, 43725, 99385, 1333, 33032, 42350, 100444, 1332, 32982, 35198, 35184, 35183, 42384, 1987, 35187, 35185, 93637, 35186, 85697, 79390, 27510, 28048, 4384, 901, 1387, 1316, 99819, 5770, 5769, 5846, 99817, 99820, 1372, 1368, 99821, 1388, 99816, 10589, 34932, 99823, 42388, 42387, 89548, 81830, 1366, 18269, 82193, 99810, 35244, 1393, 1394, 6839, 29396, 99509, 4358, 108804, 25955, 80608, 80609, 34114, 15322, 4534, 82820, 4231, 13341, 34111, 94494, 34109, 51000, 34113, 33194, 26741, 30272, 34066, 63690, 63703, 24806, 26749, 34108, 34107, 35545, 35544, 35538, 99428, 99429, 100150, 100158, 100157, 34110, 32936, 99822, 2956, 38631, 87513, 1986, 91667, 32938, 99426, 34045, 30501, 99403, 34059, 83228, 9392, 34046, 34047, 32937, 1327, 2141, 99454, 4449, 1330, 1328, 99461, 99457, 99455, 61027, 61026, 99460, 8572, 1334, 12229, 34049, 4545, 99459, 4368, 24164, 81476, 64307, 15467, 33699, 17701, 17720, 17719, 17721, 17699, 17700, 34184, 33701, 99456, 35241, 5905, 15470, 35242, 99813, 1315, 10472, 1386, 99812, 7136, 99818, 1390, 1381, 38419, 22769, 99809, 99808, 33303, 38047, 99815, 47231, 14589, 39809, 99814, 38804, 38800, 38418, 20545, 4386, 14499, 99811, 14616, 35237, 31760, 99807, 42386, 5705, 17722, 33700, 37020, 37437, 44816, 1311, 20923, 99462, 99449, 34185, 99458, 86393, 35504, 1329, 35500, 35499, 35498, 39120, 33698, 7511, 9391, 14415, 8848, 93574, 27823, 27686, 22873, 4602, 27687, 27685, 27684, 10186, 4382, 35052, 35051, 35133, 35053, 1319, 42722, 42720, 42389, 31988, 14414, 89803, 21264, 89802, 29569, 37724, 35141, 35695, 1323, 1314, 16850, 34406, 40012, 304, 33065, 24981, 36559, 1312, 22493, 35140, 4514, 14369, 7118, 73093, 8000, 82115, 34157, 34156, 34155, 34154, 34412, 90312, 90255, 51613, 34141, 31738, 34136, 5205, 99452, 90245, 8001, 61024, 61023, 1313, 14413, 3609, 3608, 49770, 3606, 7137, 4260, 5706, 36584, 3605, 3604, 34144, 34143, 34139, 36598, 1310, 99451, 37138, 15468, 1318, 4356, 9133, 35148, 21342, 36585, 3128, 37330, 4601, 4259, 37331, 36583, 65834, 31737, 99507, 37329, 66159, 1320, 36615, 99453, 37328, 1392, 21072, 1358, 42385, 8971, 14732, 11686, 24079);
UPDATE `creature_model_info` SET `BoundingRadius`=1.210245490074157714, `VerifiedBuild`=45505 WHERE `DisplayID`=22992;
UPDATE `creature_model_info` SET `BoundingRadius`=1.066211700439453125, `CombatReach`=1.392857074737548828, `VerifiedBuild`=45505 WHERE `DisplayID`=999;
UPDATE `creature_model_info` SET `DisplayID_Other_Gender`=0, `VerifiedBuild`=45505 WHERE `DisplayID` IN (4190, 4192);
UPDATE `creature_model_info` SET `BoundingRadius`=0.25, `CombatReach`=0.5, `VerifiedBuild`=45505 WHERE `DisplayID`=89308;
UPDATE `creature_model_info` SET `BoundingRadius`=0.548862099647521972, `VerifiedBuild`=45505 WHERE `DisplayID`=744;
UPDATE `creature_model_info` SET `BoundingRadius`=0.465000003576278686, `VerifiedBuild`=45505 WHERE `DisplayID`=30262;
UPDATE `creature_model_info` SET `CombatReach`=1.5, `DisplayID_Other_Gender`=0, `VerifiedBuild`=45505 WHERE `DisplayID`=2588;
UPDATE `creature_model_info` SET `BoundingRadius`=0.21263308823108673, `CombatReach`=0, `VerifiedBuild`=45505 WHERE `DisplayID`=30413;
UPDATE `creature_model_info` SET `BoundingRadius`=0.800000011920928955, `VerifiedBuild`=45505 WHERE `DisplayID`=79383;


DELETE FROM `gossip_menu_option` WHERE (`MenuID`=27579 AND `OptionID`=53883) OR (`MenuID`=28626 AND `OptionID`=55626) OR (`MenuID`=21043 AND `OptionID` IN (46950,46949)) OR (`MenuID`=27578 AND `OptionID`=53882) OR (`MenuID`=28582 AND `OptionID`=55582) OR (`MenuID`=27576 AND `OptionID`=54035);
INSERT INTO `gossip_menu_option` (`MenuID`, `OptionID`, `OptionIcon`, `OptionText`, `OptionBroadcastTextId`, `OptionNpcFlag`, `Language`, `ActionMenuID`, `ActionPoiID`, `BoxCoded`, `BoxMoney`, `BoxText`, `BoxBroadcastTextID`, `VerifiedBuild`) VALUES
(27579, 53883, 0, 'We need artisans for an expedition to the Dragon Isles. Will you join us?', 0, 1, 0, 0, 0, 0, 0, NULL, 0, 45505),
(28626, 55626, 0, '<Ask Khadgar what happened.>', 0, 1, 0, 0, 0, 0, 0, NULL, 0, 45505),
(21043, 46950, 1, 'I would like to buy from you.', 2583, 128, 0, 0, 0, 0, 0, NULL, 0, 45505), -- OptionBroadcastTextID: 2583 - 6399 - 7142 - 9992 - 14967
(27578, 53882, 0, 'We need explorers for an expedition to the Dragon Isles. Will you join us?', 0, 1, 0, 0, 0, 0, 0, NULL, 0, 45505),
(21043, 46949, 34, 'I want to transmogrify my gear.', 130510, 268435456, 0, 0, 0, 0, 0, NULL, 0, 45505),
(28582, 55582, 0, '<Listen to Ebonhorn.>', 0, 1, 0, 0, 0, 0, 0, NULL, 0, 45505),
(27576, 54035, 0, 'We need scholars for an expedition to the Dragon Isles. Will you join us?', 0, 1, 0, 0, 0, 0, 0, NULL, 0, 45505);


DELETE FROM `creature_template` WHERE `entry` IN (197771 /*Yuyu*/, 197770 /*Rips*/, 197767 /*Aetheil*/);
INSERT INTO `creature_template` (`entry`, `gossip_menu_id`, `minlevel`, `maxlevel`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `BaseAttackTime`, `RangeAttackTime`, `unit_flags`, `unit_flags2`, `unit_flags3`, `dynamicflags`, `VehicleId`, `HoverHeight`) VALUES
(197771, 0, 70, 70, 83, 16777216, 0.280000001192092895, 0.100000001490116119, 2000, 0, 33024, 2048, 0, 0, 0, 1), -- Yuyu
(197770, 0, 70, 70, 83, 16777216, 0.280000001192092895, 0.100000001490116119, 2000, 0, 33024, 2048, 0, 0, 0, 1), -- Rips
(197767, 0, 70, 70, 83, 0, 1, 1.142857193946838378, 2000, 0, 33536, 2048, 0, 0, 0, 1); -- Aetheil


UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=35, `BaseAttackTime`=2000, `unit_flags`=33536, `unit_flags2`=2048 WHERE `entry`=193889; -- Kodethi
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70, `faction`=2110, `npcflag`=3, `BaseAttackTime`=2000, `unit_flags`=33536, `unit_flags2`=2048 WHERE `entry`=193450; -- Archmage Khadgar
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3270, `npcflag`=1, `BaseAttackTime`=2000, `unit_flags`=32768, `unit_flags2`=2048 WHERE `entry`=194065; -- Ketuna Skyflame
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3270, `npcflag`=1, `BaseAttackTime`=2000, `unit_flags`=32768, `unit_flags2`=2048 WHERE `entry`=194116; -- Shin Summerhill
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3270, `npcflag`=640, `BaseAttackTime`=2000, `unit_flags`=32768, `unit_flags2`=2048 WHERE `entry`=194073; -- Lux Fizzlegig
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3270, `npcflag`=1, `BaseAttackTime`=2000, `unit_flags`=32768, `unit_flags2`=2048 WHERE `entry`=194583; -- Krakz Cloudgrease
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3270, `BaseAttackTime`=2000, `unit_flags`=32768, `unit_flags2`=2048 WHERE `entry`=189609; -- Quartermaster Furlein
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70, `faction`=3148, `BaseAttackTime`=2000, `unit_flags`=32768, `unit_flags2`=2048 WHERE `entry`=160530; -- Friend Pronk
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70, `faction`=3148, `BaseAttackTime`=2000, `unit_flags`=32768, `unit_flags2`=2048 WHERE `entry`=160529; -- Vim Brineheart
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70, `faction`=3148, `BaseAttackTime`=2000, `unit_flags`=32768, `unit_flags2`=2048 WHERE `entry`=160528; -- Poen Gillbrack
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3270, `npcflag`=1, `BaseAttackTime`=2000, `unit_flags`=32768, `unit_flags2`=2048 WHERE `entry`=194569; -- Si'va
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70, `faction`=3148, `BaseAttackTime`=2000, `unit_flags`=32768, `unit_flags2`=2048 WHERE `entry`=160527; -- Mak
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3270, `npcflag`=1, `BaseAttackTime`=2000, `unit_flags`=32768, `unit_flags2`=34816 WHERE `entry`=194050; -- Zalanti
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3270, `npcflag`=1, `BaseAttackTime`=2000, `unit_flags`=32768, `unit_flags2`=2048 WHERE `entry`=194576; -- Vernell Bartlett
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3270, `npcflag`=1, `BaseAttackTime`=2000, `unit_flags`=32768, `unit_flags2`=2048 WHERE `entry`=194561; -- Talanath Goldcrest
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3270, `BaseAttackTime`=2000, `unit_flags`=32768, `unit_flags2`=2048 WHERE `entry`=194361; -- Rathamaresh
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3270, `npcflag`=1, `BaseAttackTime`=2000, `unit_flags`=32768, `unit_flags2`=2048 WHERE `entry`=194577; -- Rinka
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70, `faction`=3148, `speed_run`=2, `BaseAttackTime`=2000, `unit_flags`=32768, `unit_flags2`=2048 WHERE `entry`=160526; -- Neri Sharpfin
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3270, `npcflag`=1, `BaseAttackTime`=2000, `unit_flags`=32768, `unit_flags2`=2048 WHERE `entry`=194563; -- Arandil Featherdawn
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3270, `npcflag`=1, `BaseAttackTime`=2000, `unit_flags`=32768, `unit_flags2`=2048 WHERE `entry`=194582; -- Mathog Hideflayer
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3270, `npcflag`=1, `BaseAttackTime`=2000, `unit_flags`=32768, `unit_flags2`=2048 WHERE `entry`=194581; -- Trauga Bloodhelm
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70, `faction`=2028, `BaseAttackTime`=2000, `unit_flags`=33536, `unit_flags2`=2048 WHERE `entry`=195385; -- Adventurous Tailor
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70, `unit_flags3`=8388608 WHERE `entry`=41621; -- Commander Thorak
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3270, `npcflag`=1, `BaseAttackTime`=2000, `unit_flags`=33536, `unit_flags2`=2048 WHERE `entry` IN (184809, 184795); -- Cataloger Kieule
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=35, `BaseAttackTime`=2000, `unit_flags`=33536, `unit_flags2`=67110912, `unit_flags3`=16777216 WHERE `entry`=194056; -- Dragon Kite
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3270, `npcflag`=1, `BaseAttackTime`=2000, `unit_flags`=32768, `unit_flags2`=2048 WHERE `entry`=194055; -- Dahanu Highwing
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3270, `BaseAttackTime`=2000, `unit_flags`=33536, `unit_flags2`=2048 WHERE `entry`=195677; -- Dracthyr Soldier
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70, `faction`=2028, `npcflag`=1, `BaseAttackTime`=2000, `unit_flags2`=2048 WHERE `entry`=195357; -- Grok Thickfoot
UPDATE `creature_template` SET `minlevel`=30, `maxlevel`=30 WHERE `entry`=3108; -- Encrusted Surf Crawler
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3270, `npcflag`=1, `BaseAttackTime`=2000, `unit_flags`=33536, `unit_flags2`=34816 WHERE `entry`=197288; -- Skarukaru
UPDATE `creature_template` SET `minlevel`=60, `maxlevel`=60, `faction`=1735, `npcflag`=128, `BaseAttackTime`=2000, `unit_flags`=33024, `unit_flags2`=2048 WHERE `entry`=195899; -- Storm Huntress Suhrakka
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3270, `npcflag`=2, `BaseAttackTime`=2000, `unit_flags`=33536, `unit_flags2`=2048 WHERE `entry` IN (197279, 184793); -- Naleidea Rivergleam
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70, `faction`=35, `BaseAttackTime`=2000, `unit_flags`=33555200, `unit_flags2`=100665344, `unit_flags3`=1 WHERE `entry`=180701; -- (Bunny) Sessile
UPDATE `creature_template` SET `faction`=188, `BaseAttackTime`=2000, `unit_flags`=33536, `unit_flags2`=2048 WHERE `entry`=189075; -- Seagull
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3270, `npcflag`=4224, `BaseAttackTime`=2000, `unit_flags`=33536, `unit_flags2`=2048 WHERE `entry`=184810; -- Boss Magor
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3270, `npcflag`=1, `BaseAttackTime`=2000, `unit_flags`=33536, `unit_flags2`=2048 WHERE `entry` IN (184808, 184796); -- Pathfinder Tacha
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3270, `BaseAttackTime`=2000, `unit_flags`=32768, `unit_flags2`=2048 WHERE `entry`=194115; -- Airship Worker
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3270, `BaseAttackTime`=2000, `unit_flags`=33536, `unit_flags2`=2048 WHERE `entry`=189554; -- Expedition Supplier
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3270, `BaseAttackTime`=2000, `unit_flags`=33536, `unit_flags2`=2048 WHERE `entry`=184813; -- Brave Researcher
UPDATE `creature_template` SET `unit_flags`=0 WHERE `entry`=3100; -- Elder Mottled Boar
UPDATE `creature_template` SET `minlevel`=45, `maxlevel`=45, `faction`=2714, `BaseAttackTime`=2000, `unit_flags`=768, `unit_flags2`=2048 WHERE `entry`=100664; -- Thunder Bluff Native
UPDATE `creature_template` SET `minlevel`=45, `maxlevel`=45, `faction`=2714, `BaseAttackTime`=2000, `unit_flags`=512, `unit_flags2`=2048 WHERE `entry`=100682; -- Silvermoon Citizen
UPDATE `creature_template` SET `minlevel`=45, `maxlevel`=45, `faction`=2714, `BaseAttackTime`=2000, `unit_flags`=512, `unit_flags2`=2048 WHERE `entry`=100679; -- Citizen of Kezan
UPDATE `creature_template` SET `minlevel`=30, `maxlevel`=30 WHERE `entry`=5822; -- Felweaver Scornn
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70, `faction`=35, `BaseAttackTime`=2000, `unit_flags`=33554432, `unit_flags2`=104859648, `unit_flags3`=1 WHERE `entry`=197611; -- (Bunny) Sessile + Gigantic AOI
UPDATE `creature_template` SET `minlevel`=30, `maxlevel`=30 WHERE `entry`=3204; -- Gazz'uz
UPDATE `creature_template` SET `minlevel`=45, `maxlevel`=45, `faction`=2714, `BaseAttackTime`=2000, `unit_flags`=512, `unit_flags2`=2048 WHERE `entry`=100502; -- Concerned Citizen
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3270, `BaseAttackTime`=2000, `unit_flags`=32768, `unit_flags2`=4196352 WHERE `entry`=184286; -- Captain Caspartine
UPDATE `creature_template` SET `minlevel`=30, `maxlevel`=30 WHERE `entry`=3198; -- Burning Blade Apprentice
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=35, `BaseAttackTime`=2000, `unit_flags`=33554432, `unit_flags2`=104859648, `unit_flags3`=1 WHERE `entry`=184807; -- The Defiant Dragonscale
UPDATE `creature_template` SET `minlevel`=45, `maxlevel`=45, `faction`=2714, `BaseAttackTime`=2000, `unit_flags`=512, `unit_flags2`=2048 WHERE `entry`=100663; -- Sen'jin Villager
UPDATE `creature_template` SET `minlevel`=30, `maxlevel`=30 WHERE `entry`=3197; -- Burning Blade Fanatic
UPDATE `creature_template` SET `gossip_menu_id`=0, `minlevel`=70, `maxlevel`=70 WHERE `entry`=43239; -- Razgar
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=168598; -- Thega Graveblade
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=168626; -- Feenix Arcshine
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=171691; -- Alpheus Cain
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=46985; -- [DNT] Generic Target Bunny
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=69333; -- Disciple Jusi
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=168623; -- Kazak Darkscream
UPDATE `creature_template` SET `gossip_menu_id`=0, `minlevel`=70, `maxlevel`=70 WHERE `entry`=3353; -- Grezz Ragefist
UPDATE `creature_template` SET `unit_flags2`=2048 WHERE `entry`=68869; -- Luo Luo
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=171689; -- Nathoka Bloodfang
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=62445; -- Ji Firepaw
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=13842; -- Frostwolf Ambassador Rokhstrom
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=168551; -- Tamanji
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=168628; -- Hretar Riverspeaker
UPDATE `creature_template` SET `gossip_menu_id`=0, `minlevel`=70, `maxlevel`=70 WHERE `entry`=35364; -- Slahtz
UPDATE `creature_template` SET `gossip_menu_id`=0, `minlevel`=70, `maxlevel`=70 WHERE `entry`=3354; -- Sorek
UPDATE `creature_template` SET `gossip_menu_id`=0, `minlevel`=70, `maxlevel`=70 WHERE `entry`=49573; -- Karba Blazemaw
UPDATE `creature_template` SET `gossip_menu_id`=0, `minlevel`=70, `maxlevel`=70 WHERE `entry`=34955; -- Karg Skullgore
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=168553; -- Telotha Pinegrove
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=65074; -- Great Blue Dragon Turtle
UPDATE `creature_template` SET `gossip_menu_id`=0, `minlevel`=70, `maxlevel`=70 WHERE `entry`=46667; -- Blademaster Ronakada
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=65071; -- Great Green Dragon Turtle
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=168596; -- Gormok Ogrefist
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=70301; -- Softpaws
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=168597; -- Avaros Dawnglaive
UPDATE `creature_template` SET `minlevel`=10 WHERE `entry`=169166; -- Provisioner Jin'hake
UPDATE `creature_template` SET `gossip_menu_id`=0, `minlevel`=70, `maxlevel`=70 WHERE `entry`=7951; -- Zas'Tysh
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=168621; -- Martin Goodchilde
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=66022; -- Turtlemaster Odai
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=65078; -- Great Purple Dragon Turtle
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=65076; -- Great Brown Dragon Turtle
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=1734, `BaseAttackTime`=2000, `unit_flags`=33536, `unit_flags2`=2048 WHERE `entry`=184798; -- Chronicler Laz'Kini
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=35845; -- Dave's Industrial Light and Magic Bunny (Small)(Sessile)
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=3333; -- Shankys
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=35, `BaseAttackTime`=2000, `unit_flags`=33536, `unit_flags2`=2048 WHERE `entry`=184797; -- Lorewalker Lali
UPDATE `creature_template` SET `gossip_menu_id`=0, `minlevel`=70, `maxlevel`=70 WHERE `entry`=3332; -- Lumak
UPDATE `creature_template` SET `gossip_menu_id`=0 WHERE `entry`=42638; -- Herezegor Flametusk
UPDATE `creature_template` SET `gossip_menu_id`=0, `minlevel`=70, `maxlevel`=70 WHERE `entry`=46642; -- Innkeeper Nufa
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=46619; -- Binzella
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=46618; -- Fibi
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=62193; -- Rok'kal
UPDATE `creature_template` SET `minlevel`=9, `maxlevel`=9, `faction`=35, `BaseAttackTime`=2000, `unit_flags`=33536, `unit_flags2`=2048 WHERE `entry`=180684; -- Olive
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=46622; -- Vuvanzi
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=46620; -- Vink
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=158789; -- Thex
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=3359; -- Kiro
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=46621; -- Pank
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=160452; -- Nilsa
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=161203; -- River
UPDATE `creature_template` SET `minlevel`=73, `maxlevel`=73 WHERE `entry`=31146; -- Raider's Training Dummy
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70, `unit_flags3`=8388609 WHERE `entry`=153285; -- Training Dummy
UPDATE `creature_template` SET `gossip_menu_id`=0, `minlevel`=70, `maxlevel`=70 WHERE `entry`=2855; -- Snang
UPDATE `creature_template` SET `gossip_menu_id`=0, `minlevel`=70, `maxlevel`=70, `npcflag`=81 WHERE `entry`=3365; -- Karolek
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=3316; -- Handor
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=3350; -- Asoran
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70, `faction`=29, `BaseAttackTime`=2000, `unit_flags`=33536, `unit_flags2`=2048, `dynamicflags`=128 WHERE `entry` IN (188169, 188157); -- Worker
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=6987; -- Malton Droffers
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=6986; -- Dran Droffers
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70, `npcflag`=80 WHERE `entry`=7088; -- Thuwd
UPDATE `creature_template` SET `gossip_menu_id`=0, `minlevel`=70, `maxlevel`=70 WHERE `entry`=5811; -- Kamari
UPDATE `creature_template` SET `gossip_menu_id`=0, `minlevel`=70, `maxlevel`=70 WHERE `entry`=8659; -- Jes'rimon
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=3351; -- Magenius
UPDATE `creature_template` SET `gossip_menu_id`=0, `minlevel`=70, `maxlevel`=70 WHERE `entry`=3347; -- Yelmak
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=3348; -- Kor'geld
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=3366; -- Tamar
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=3321; -- Morgum
UPDATE `creature_template` SET `gossip_menu_id`=0, `minlevel`=70, `maxlevel`=70 WHERE `entry`=11066; -- Jhag
UPDATE `creature_template` SET `gossip_menu_id`=0, `minlevel`=70, `maxlevel`=70 WHERE `entry`=46181; -- Enchanter Farendin
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=3346; -- Kithas
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=62197; -- Zazzle
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=62196; -- Flekky Nox
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3270, `BaseAttackTime`=2000, `unit_flags`=33536, `unit_flags2`=2048 WHERE `entry`=190535; -- Quizla Blastcaps
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=83, `BaseAttackTime`=2000, `unit_flags`=33536, `unit_flags2`=2048 WHERE `entry`=197682; -- Enchantress Quinni
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=1735, `npcflag`=1, `BaseAttackTime`=2000, `unit_flags`=33536, `unit_flags2`=2048 WHERE `entry`=184787; -- Boss Magor
UPDATE `creature_template` SET `gossip_menu_id`=0, `minlevel`=70, `maxlevel`=70, `npcflag`=83 WHERE `entry`=3345; -- Godan
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=83, `BaseAttackTime`=2000, `unit_flags`=33536, `unit_flags2`=2048 WHERE `entry`=197680; -- Jack the Hammer
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=83, `BaseAttackTime`=2000, `unit_flags`=33536, `unit_flags2`=2048 WHERE `entry`=197679; -- Shuga Blastcaps
UPDATE `creature_template` SET `gossip_menu_id`=0, `minlevel`=70, `maxlevel`=70, `npcflag`=81 WHERE `entry`=46741; -- Muraga
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=46742; -- Brunda
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=3371; -- Tamaro
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=3372; -- Sarlek
UPDATE `creature_template` SET `gossip_menu_id`=0, `minlevel`=70, `maxlevel`=70 WHERE `entry`=7010; -- Zilzibin Drumlore
UPDATE `creature_template` SET `gossip_menu_id`=0 WHERE `entry`=34765; -- Zelli Hotnozzle
UPDATE `creature_template` SET `gossip_menu_id`=0 WHERE `entry`=44160; -- Suspicious Peon
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=3405; -- Zeal'aya
UPDATE `creature_template` SET `gossip_menu_id`=0, `minlevel`=70, `maxlevel`=70, `npcflag`=81 WHERE `entry`=3404; -- Jandi
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70, `faction`=714, `npcflag`=128, `BaseAttackTime`=2000, `unit_flags2`=2048 WHERE `entry`=179897; -- Ca'nees
UPDATE `creature_template` SET `gossip_menu_id`=0, `minlevel`=70, `maxlevel`=70, `npcflag`=1125899906842625 WHERE `entry`=29143; -- Bebri Coifcurl
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70, `faction`=35, `speed_run`=1, `BaseAttackTime`=2000, `unit_flags`=768, `unit_flags2`=67143680, `unit_flags3`=16777216, `VehicleId`=7559 WHERE `entry` IN (187710, 187709, 187711); -- Handhold
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=2980, `BaseAttackTime`=2000, `unit_flags`=33536, `unit_flags2`=2048 WHERE `entry`=184800; -- Omi
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=2980, `BaseAttackTime`=2000, `unit_flags`=33536, `unit_flags2`=2048 WHERE `entry`=184801; -- Kenzou
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70, `faction`=35, `speed_run`=1, `BaseAttackTime`=2000, `unit_flags`=768, `unit_flags2`=67143680, `unit_flags3`=16777216, `VehicleId`=7560 WHERE `entry`=189091; -- Handhold
UPDATE `creature_template` SET `gossip_menu_id`=0, `minlevel`=70, `maxlevel`=70, `npcflag`=81 WHERE `entry`=44783; -- Hiwahi Three-Feathers
UPDATE `creature_template` SET `gossip_menu_id`=0, `minlevel`=70, `maxlevel`=70, `unit_flags3`=8388608 WHERE `entry`=15188; -- Cenarion Emissary Blackhoof
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=5892; -- Searn Firewarder
UPDATE `creature_template` SET `gossip_menu_id`=0, `minlevel`=70, `maxlevel`=70 WHERE `entry`=3403; -- Sian'tsu
UPDATE `creature_template` SET `gossip_menu_id`=0, `minlevel`=70, `maxlevel`=70 WHERE `entry`=13417; -- Sagorne Creststrider
UPDATE `creature_template` SET `gossip_menu_id`=0, `minlevel`=70, `maxlevel`=70 WHERE `entry`=44788; -- Lonto
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=161223; -- Torkhan
UPDATE `creature_template` SET `gossip_menu_id`=0, `minlevel`=70, `maxlevel`=70 WHERE `entry`=44785; -- Miwana
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=72939; -- Terga Earthbreaker
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70, `npcflag`=80 WHERE `entry`=44782; -- Rento
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=104, `BaseAttackTime`=2000, `unit_flags`=33536, `unit_flags2`=2048 WHERE `entry`=184664; -- Baine Bloodhoof
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=44770; -- Tatepi
UPDATE `creature_template` SET `minlevel`=60, `maxlevel`=60, `faction`=35, `npcflag`=3, `BaseAttackTime`=2000, `unit_flags`=33536, `unit_flags2`=2048 WHERE `entry`=190239; -- Ebyssian
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=1735, `npcflag`=2, `BaseAttackTime`=2000, `unit_flags`=33536, `unit_flags2`=2048 WHERE `entry`=184786; -- Scalecommander Cindrethresh
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=2785, `BaseAttackTime`=2000, `unit_flags`=33536, `unit_flags2`=2048 WHERE `entry`=184666; -- Mayla Highmountain
UPDATE `creature_template` SET `gossip_menu_id`=0, `minlevel`=70, `maxlevel`=70 WHERE `entry`=58199; -- Lord Itharius
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=58193; -- Wyrmrest Protector
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=44780; -- Isashi
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=44779; -- Owato
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=47335; -- Baradin Grunt
UPDATE `creature_template` SET `gossip_menu_id`=0 WHERE `entry`=47321; -- Zugra Flamefist
UPDATE `creature_template` SET `gossip_menu_id`=0, `minlevel`=70, `maxlevel`=70 WHERE `entry`=3322; -- Kaja
UPDATE `creature_template` SET `gossip_menu_id`=0, `minlevel`=70, `maxlevel`=70 WHERE `entry`=44781; -- Opuno Ironhorn
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=176012; -- Ric Catstalker
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3270, `BaseAttackTime`=2000, `unit_flags`=33536, `unit_flags2`=2048 WHERE `entry`=184812; -- Restless Explorer
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=176095; -- Luke Catstalker
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=176094; -- Max Catstalker
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=44787; -- Auctioneer Sowata
UPDATE `creature_template` SET `minlevel`=1, `maxlevel`=1 WHERE `entry`=54004; -- Jaga
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70, `unit_flags3`=8388608 WHERE `entry`=47663; -- Scout Obrok
UPDATE `creature_template` SET `minlevel`=60, `maxlevel`=60 WHERE `entry`=141920; -- Traveling Son
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=54113; -- Spooks
UPDATE `creature_template` SET `minlevel`=60, `maxlevel`=60 WHERE `entry`=141912; -- Traveling Warrior
UPDATE `creature_template` SET `minlevel`=60, `maxlevel`=60 WHERE `entry`=174147; -- Archivist Sylvia
UPDATE `creature_template` SET `gossip_menu_id`=0, `minlevel`=70, `maxlevel`=70 WHERE `entry`=44723; -- Nahu Ragehoof
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=44745; -- Sunwalker Atohmo's Kodo
UPDATE `creature_template` SET `gossip_menu_id`=0, `minlevel`=70, `maxlevel`=70 WHERE `entry`=44740; -- Sahi Cloudsinger
UPDATE `creature_template` SET `gossip_menu_id`=0, `minlevel`=70, `maxlevel`=70 WHERE `entry`=44743; -- Nohi Plainswalker
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=133271; -- Highmountain Pathfinder
UPDATE `creature_template` SET `gossip_menu_id`=0, `minlevel`=70, `maxlevel`=70 WHERE `entry`=44726; -- Shalla Whiteleaf
UPDATE `creature_template` SET `gossip_menu_id`=0, `minlevel`=70, `maxlevel`=70 WHERE `entry`=44725; -- Sunwalker Atohmo
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=42548; -- Muddy Crawfish
UPDATE `creature_template` SET `gossip_menu_id`=0, `minlevel`=70, `maxlevel`=70 WHERE `entry`=3327; -- Gest
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=3335; -- Hagrus
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=47254; -- Gizput
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=3330; -- Muragus
UPDATE `creature_template` SET `gossip_menu_id`=0, `minlevel`=70, `maxlevel`=70 WHERE `entry`=3328; -- Ormok
UPDATE `creature_template` SET `gossip_menu_id`=0, `minlevel`=70, `maxlevel`=70 WHERE `entry`=5875; -- Mordak Darkfist
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=5816; -- Katis
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=88706; -- Murgul
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=88705; -- Kranosh
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=88704; -- Gran'dul
UPDATE `creature_template` SET `gossip_menu_id`=0, `minlevel`=70, `maxlevel`=70 WHERE `entry`=47233; -- Gordul
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70, `unit_flags3`=8388608 WHERE `entry`=45230; -- Orgrimmar Brave
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=3334; -- Rekkul
UPDATE `creature_template` SET `gossip_menu_id`=0 WHERE `entry`=12136; -- Snurk Bucksquick
UPDATE `creature_template` SET `gossip_menu_id`=0, `minlevel`=70, `maxlevel`=70 WHERE `entry`=44735; -- Seer Liwatha
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=5909; -- Cazul
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=3189; -- Kor'ghan
UPDATE `creature_template` SET `gossip_menu_id`=0 WHERE `entry`=43062; -- Bort
UPDATE `creature_template` SET `gossip_menu_id`=0 WHERE `entry`=26537; -- Greeb Ramrocket
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=130911; -- Charles Gastly
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70, `faction`=29, `BaseAttackTime`=2000, `unit_flags`=33536, `unit_flags2`=2048, `dynamicflags`=128 WHERE `entry`=187775; -- Kanyaku
UPDATE `creature_template` SET `minlevel`=60, `maxlevel`=60 WHERE `entry`=141528; -- Clara Spelldriver
UPDATE `creature_template` SET `gossip_menu_id`=0 WHERE `entry`=9564; -- Frezza
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=44918; -- Drakma
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=44948; -- Wind Rider Cub
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=5639; -- Craven Drok
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70, `npcflag`=80 WHERE `entry`=46716; -- Nerog
UPDATE `creature_template` SET `unit_flags`=256 WHERE `entry`=15476; -- Scorpid
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=46718; -- Moraka
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=3317; -- Ollanus
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=3315; -- Tor'phan
UPDATE `creature_template` SET `gossip_menu_id`=0, `minlevel`=70, `maxlevel`=70 WHERE `entry`=11017; -- Roxxik
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=3364; -- Borya
UPDATE `creature_template` SET `gossip_menu_id`=0, `minlevel`=70, `maxlevel`=70, `npcflag`=81 WHERE `entry`=3363; -- Magar
UPDATE `creature_template` SET `gossip_menu_id`=0, `minlevel`=70, `maxlevel`=70 WHERE `entry`=3413; -- Sovik
UPDATE `creature_template` SET `gossip_menu_id`=0, `minlevel`=70, `maxlevel`=70 WHERE `entry`=3412; -- Nogg
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=3368; -- Borstan
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=49737; -- Shazdar
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=52032; -- Sinzi Sparkscribe
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=46708; -- Suja
UPDATE `creature_template` SET `gossip_menu_id`=0, `minlevel`=70, `maxlevel`=70 WHERE `entry`=52809; -- Blax Bottlerocket
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=14498; -- Tosamina
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=68979; -- Voidbinder Zorlan
UPDATE `creature_template` SET `gossip_menu_id`=0, `minlevel`=35, `maxlevel`=35 WHERE `entry`=57801; -- Thaumaturge Altha
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=3369; -- Gotri
UPDATE `creature_template` SET `gossip_menu_id`=0, `minlevel`=70, `maxlevel`=70 WHERE `entry`=54473; -- Warpweaver Dushar
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=54472; -- Vaultkeeper Jazra
UPDATE `creature_template` SET `minlevel`=6, `maxlevel`=6 WHERE `entry`=62199; -- Gogu
UPDATE `creature_template` SET `gossip_menu_id`=0, `minlevel`=70, `maxlevel`=70 WHERE `entry`=2857; -- Thund
UPDATE `creature_template` SET `gossip_menu_id`=0, `minlevel`=70, `maxlevel`=70 WHERE `entry`=14451; -- Orphan Matron Battlewail
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=3367; -- Felika
UPDATE `creature_template` SET `minlevel`=1, `maxlevel`=3 WHERE `entry`=14499; -- Horde Orphan
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=46709; -- Arugi
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=50477; -- Champion Uru'zin
UPDATE `creature_template` SET `gossip_menu_id`=0, `minlevel`=70, `maxlevel`=70 WHERE `entry`=42506; -- Marogg
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=62194; -- Ukos Bloodwhisper
UPDATE `creature_template` SET `gossip_menu_id`=0, `minlevel`=70, `maxlevel`=70 WHERE `entry`=63626; -- Varzok
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=50488; -- Stone Guard Nargol
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=50323; -- Frizzo Villamar
UPDATE `creature_template` SET `gossip_menu_id`=0, `minlevel`=70, `maxlevel`=70 WHERE `entry`=3310; -- Doras
UPDATE `creature_template` SET `unit_flags`=33024 WHERE `entry`=14881; -- Spider
UPDATE `creature_template` SET `gossip_menu_id`=0, `minlevel`=70, `maxlevel`=70 WHERE `entry`=3216; -- Arnak Fireblade
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=44919; -- Maztha
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=3331; -- Kareth
UPDATE `creature_template` SET `minlevel`=60, `maxlevel`=60 WHERE `entry`=141310; -- Associate Telemancer Rafcav
UPDATE `creature_template` SET `gossip_menu_id`=0, `minlevel`=70, `maxlevel`=70 WHERE `entry`=47253; -- Rundok
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=3329; -- Kor'jus
UPDATE `creature_template` SET `gossip_menu_id`=0, `minlevel`=70, `maxlevel`=70 WHERE `entry`=47248; -- Gija
UPDATE `creature_template` SET `gossip_menu_id`=0, `minlevel`=70, `maxlevel`=70 WHERE `entry`=47247; -- Marud
UPDATE `creature_template` SET `gossip_menu_id`=0, `minlevel`=70, `maxlevel`=70 WHERE `entry`=47246; -- Ureda
UPDATE `creature_template` SET `gossip_menu_id`=0, `minlevel`=70, `maxlevel`=70 WHERE `entry`=55382; -- Darkmoon Faire Mystic Mage
UPDATE `creature_template` SET `gossip_menu_id`=0 WHERE `entry`=44158; -- Orgrimmar Skyway Peon
UPDATE `creature_template` SET `gossip_menu_id`=0, `minlevel`=70, `maxlevel`=70, `faction`=83 WHERE `entry`=3084; -- Bluffwatcher
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70, `unit_flags3`=8388608 WHERE `entry`=14377; -- Scout Tharr
UPDATE `creature_template` SET `gossip_menu_id`=0 WHERE `entry`=23635; -- Krixx
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70, `unit_flags3`=16777216 WHERE `entry`=158637; -- Guiding Orb
UPDATE `creature_template` SET `gossip_menu_id`=0, `minlevel`=70, `maxlevel`=70 WHERE `entry`=31720; -- Crewman Shubbscoop
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=25075; -- Zeppelin Controls
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70, `unit_flags3`=8388608 WHERE `entry`=31727; -- Grunt Grikee
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70, `unit_flags3`=8388608 WHERE `entry`=31726; -- Grunt Gritch
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=31725; -- Sky-Captain LaFontaine
UPDATE `creature_template` SET `gossip_menu_id`=0, `minlevel`=70, `maxlevel`=70 WHERE `entry`=31724; -- Crewman Paltertop
UPDATE `creature_template` SET `gossip_menu_id`=0, `minlevel`=70, `maxlevel`=70 WHERE `entry`=31723; -- Crewman Barrowswizzle
UPDATE `creature_template` SET `gossip_menu_id`=0, `minlevel`=70, `maxlevel`=70 WHERE `entry`=10880; -- Warcaller Gorlach
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70, `npcflag`=80 WHERE `entry`=37072; -- Rogg
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=46358; -- Lutah
UPDATE `creature_template` SET `gossip_menu_id`=0, `minlevel`=70, `maxlevel`=70, `npcflag`=81 WHERE `entry`=46357; -- Gonto
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=46512; -- Naros
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=46359; -- Punra
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=3319; -- Sana
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=62198; -- Omakka Wolfbrother
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70, `unit_flags3`=8388608 WHERE `entry`=14376; -- Scout Manslayer
UPDATE `creature_template` SET `minlevel`=60, `maxlevel`=60, `unit_flags3`=16777216 WHERE `entry`=135201; -- Talk to Sylvanas
UPDATE `creature_template` SET `gossip_menu_id`=0, `minlevel`=70, `maxlevel`=70 WHERE `entry`=23128; -- Master Pyreanor
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70, `unit_flags`=32768, `unit_flags3`=8388608 WHERE `entry`=46140; -- Silvermoon Delegation Guardian
UPDATE `creature_template` SET `gossip_menu_id`=0, `minlevel`=70, `maxlevel`=70 WHERE `entry`=35068; -- Gotura Fourwinds
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=52034; -- Togar
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=46555; -- Gunra
UPDATE `creature_template` SET `gossip_menu_id`=0, `minlevel`=70, `maxlevel`=70 WHERE `entry`=47571; -- Belloc Brightblade
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=3323; -- Horthus
UPDATE `creature_template` SET `gossip_menu_id`=0, `minlevel`=70, `maxlevel`=70 WHERE `entry`=3314; -- Urtharo
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=72654; -- General Purpose Stalker (RKS)
UPDATE `creature_template` SET `gossip_menu_id`=0, `minlevel`=70, `maxlevel`=70 WHERE `entry`=17098; -- Ambassador Dawnsinger
UPDATE `creature_template` SET `gossip_menu_id`=0, `minlevel`=70, `maxlevel`=70 WHERE `entry`=45337; -- Tyelis
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=58155; -- Rugok
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=42594; -- Orgrimmar Thief
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70, `npcflag`=1 WHERE `entry`=89830; -- Brew Vendor
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=49622; -- Shok Narnes
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=3312; -- Olvia
UPDATE `creature_template` SET `gossip_menu_id`=0, `minlevel`=70, `maxlevel`=70 WHERE `entry`=27489; -- Ray'ma
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=46556; -- Jamus'Vaz
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=4047; -- Zor Lonetree
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70, `unit_flags3`=8388608 WHERE `entry`=46142; -- Forsaken Delegation Deathguard
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70, `faction`=29, `BaseAttackTime`=2000, `unit_flags`=33536, `unit_flags2`=2048 WHERE `entry` IN (188655, 188656); -- Worker
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70, `unit_flags3`=8388608 WHERE `entry`=44872; -- Grunt Wabang
UPDATE `creature_template` SET `gossip_menu_id`=0, `minlevel`=70, `maxlevel`=70 WHERE `entry`=3144; -- Eitrigg
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=44868; -- Auctioneer Xifa
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=44867; -- Auctioneer Ralinza
UPDATE `creature_template` SET `gossip_menu_id`=0, `minlevel`=70, `maxlevel`=70 WHERE `entry`=44866; -- Auctioneer Drezmit
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=44865; -- Auctioneer Fazdran
UPDATE `creature_template` SET `gossip_menu_id`=0, `minlevel`=70, `maxlevel`=70 WHERE `entry`=45339; -- Dark Cleric Cecille
UPDATE `creature_template` SET `gossip_menu_id`=0, `minlevel`=70, `maxlevel`=70 WHERE `entry`=14392; -- Overlord Natoj
UPDATE `creature_template` SET `minlevel`=60, `maxlevel`=60, `unit_flags3`=16777216 WHERE `entry`=137762; -- Take a potion
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=44853; -- Branzlit
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=168459; -- Orgrimmar Grunt
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=44851; -- Mezlik
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=6466; -- Gamon
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=149270; -- Orgrimmar Guardian Mage
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70, `unit_flags3`=8388608 WHERE `entry`=88703; -- Grunt Arhung
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=88702; -- Grunt Nolo
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=88701; -- Grunt Meena
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=3313; -- Trak'gen
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70, `unit_flags3`=8388608 WHERE `entry`=14375; -- Scout Stronghand
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=5614; -- Sarok
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=5613; -- Doyo'da
UPDATE `creature_template` SET `minlevel`=35, `maxlevel`=35, `unit_flags3`=8388608 WHERE `entry`=72559; -- Thunder Bluff Protector
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=5611; -- Barkeep Morag
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70, `faction`=29, `npcflag`=3, `BaseAttackTime`=2000, `unit_flags`=33536, `unit_flags2`=2048 WHERE `entry`=187758; -- Zaa'je
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=5610; -- Kozish
UPDATE `creature_template` SET `gossip_menu_id`=0, `minlevel`=70, `maxlevel`=70 WHERE `entry`=6929; -- Innkeeper Gryshka
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=5609; -- Zazo
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=5606; -- Goma
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=44856; -- Perixa
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=44854; -- Kixa
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=44852; -- Rilgiz
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=32520; -- Totally Generic Bunny (All Phase)
UPDATE `creature_template` SET `minlevel`=60, `maxlevel`=60, `faction`=35, `npcflag`=2, `BaseAttackTime`=2000, `unit_flags2`=2048 WHERE `entry`=189398; -- Kodethi
UPDATE `creature_template` SET `gossip_menu_id`=0, `minlevel`=70, `maxlevel`=70, `unit_flags3`=8388608 WHERE `entry`=44878; -- Grunt Karus
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=51195; -- Kor'kron Annihilator
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70, `unit_flags3`=8388608 WHERE `entry`=44876; -- Grunt Koma
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=5817; -- Shimra
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70, `unit_flags3`=8388608 WHERE `entry`=44871; -- Grunt Grimful
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=46572; -- Goram
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=28960; -- Totally Generic Bunny (JSB)
UPDATE `creature_template` SET `gossip_menu_id`=0, `minlevel`=70, `maxlevel`=70 WHERE `entry`=5188; -- Garyl
UPDATE `creature_template` SET `minlevel`=45, `maxlevel`=45 WHERE `entry`=97296; -- Archmage Khadgar
UPDATE `creature_template` SET `gossip_menu_id`=0, `minlevel`=70, `maxlevel`=70 WHERE `entry`=74228; -- Darkspear Headhunter
UPDATE `creature_template` SET `minlevel`=45, `maxlevel`=45, `faction`=2838, `npcflag`=2, `BaseAttackTime`=1000, `unit_flags`=32832, `unit_flags2`=2048 WHERE `entry`=102529; -- Kor'vas Bloodthorn
UPDATE `creature_template` SET `gossip_menu_id`=0, `minlevel`=70, `maxlevel`=70, `unit_flags3`=8388608 WHERE `entry`=44877; -- Grunt Soran
UPDATE `creature_template` SET `gossip_menu_id`=0 WHERE `entry`=49750; -- Warchief's Herald
UPDATE `creature_template` SET `gossip_menu_id`=0, `minlevel`=70, `maxlevel`=70 WHERE `entry`=3296; -- Orgrimmar Grunt
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70, `unit_flags3`=8388608 WHERE `entry`=51346; -- Orgrimmar Wind Rider
UPDATE `creature_template` SET `gossip_menu_id`=0, `minlevel`=70, `maxlevel`=70 WHERE `entry`=3370; -- Urtrun Clanbringer
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=38821; -- Dave's Industrial Light and Magic Bunny (Medium)(Sessile)
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=3342; -- Shan'ti
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70 WHERE `entry`=62195; -- Shang'gok
UPDATE `creature_template` SET `minlevel`=45, `maxlevel`=45, `faction`=1665, `npcflag`=3, `BaseAttackTime`=2000, `unit_flags`=33536, `unit_flags2`=35653632, `unit_flags3`=1048576 WHERE `entry`=100636; -- High Overlord Saurfang
UPDATE `creature_template` SET `minlevel`=60, `maxlevel`=60, `unit_flags3`=16777216 WHERE `entry`=135202; -- Meet your team
UPDATE `creature_template` SET `minlevel`=73, `maxlevel`=73 WHERE `entry`=175135; -- Rokhan


SET @GROUP_ID = 0;
SET @ID = 0;
REPLACE INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) VALUES
(3296, @GROUP_ID+0, @ID, 'What do dragons eat, anyway?', 12, 0, 100, 4, 0, 0, 0, 0, 'Orgrimmar Grunt to Player'),
(3296, @GROUP_ID+1, @ID, 'Amazing!', 12, 0, 100, 4, 0, 0, 0, 0, 'Orgrimmar Grunt to Player'), -- BroadcastTextID: 41615 - 124042
(3296, @GROUP_ID+2, @ID, 'I guess those wings aren\'t just for show!', 12, 0, 100, 4, 0, 0, 0, 0, 'Orgrimmar Grunt to Player'),
(3296, @GROUP_ID+3, @ID, 'Do a barrel roll!', 12, 0, 100, 4, 0, 0, 168079, 0, 'Orgrimmar Grunt to Player'),
(3296, @GROUP_ID+4, @ID, 'Could I have one of your scales? For crafting purposes, of course.', 12, 0, 100, 25, 0, 0, 0, 0, 'Orgrimmar Grunt to Player'),
(3296, @GROUP_ID+5, @ID, 'Do you know Alexstrasza?', 12, 0, 100, 6, 0, 0, 0, 0, 'Orgrimmar Grunt to Player'),
(3296, @GROUP_ID+6, @ID, 'Why haven\'t we seen your people before?', 12, 0, 100, 4, 0, 0, 0, 0, 'Orgrimmar Grunt to Player'),
(3296, @GROUP_ID+7, @ID, 'Dragons don\'t belong here!', 12, 0, 100, 603, 0, 0, 0, 0, 'Orgrimmar Grunt to Player'),
(3296, @GROUP_ID+8, @ID, 'I won\'t forget what Deathwing did to this city.', 12, 0, 100, 603, 0, 0, 0, 0, 'Orgrimmar Grunt to Player'),
(3296, @GROUP_ID+9, @ID, 'I\'m not afraid of you, dragon!', 12, 0, 100, 14, 0, 0, 0, 0, 'Orgrimmar Grunt to Player'),
(3296, @GROUP_ID+10, @ID, 'Showoff. Walk like a normal person!', 12, 0, 100, 5, 0, 0, 0, 0, 'Orgrimmar Grunt to Player'),
(3296, @GROUP_ID+11, @ID, 'So you can fly!', 12, 0, 100, 6, 0, 0, 0, 0, 'Orgrimmar Grunt to Player'),
(3296, @GROUP_ID+12, @ID, 'Keep those talons where I can see them!', 12, 0, 100, 6, 0, 0, 0, 0, 'Orgrimmar Grunt to Player'),
(47335, @GROUP_ID+0, @ID, 'Victory in Tol Barad is ours! While the Alliance offensive is crippled, we need your immediate efforts to gather resources and secure the island!', 14, 0, 100, 0, 0, 0, 50895, 0, 'Baradin Grunt'),
(88703, @GROUP_ID+0, @ID, 'What is it like to fly?', 12, 0, 100, 1, 0, 0, 0, 0, 'Grunt Arhung to Player'),
(184793, @GROUP_ID+0, @ID, 'Hail adventurer, I shall help you prepare for the Dragon Isles.', 12, 0, 100, 3, 0, 204288, 0, 0, 'Naleidea Rivergleam to Player'),
(184793, @GROUP_ID+1, @ID, 'I shall meet you at the zeppelin once you\'ve gathered our future expeditionary members.', 12, 0, 100, 4, 0, 204289, 0, 0, 'Naleidea Rivergleam to Player'),
(184796, @GROUP_ID+0, @ID, 'Join the expedition? We\'ll do more than join. We\'ll lead the way!', 12, 0, 100, 1, 0, 204345, 0, 0, 'Pathfinder Tacha to Player'),
(190239, @GROUP_ID+0, @ID, 'Ah, here is the hero I spoke of.', 12, 0, 100, 1, 0, 204334, 0, 0, 'Ebyssian to Player'),
(193889, @GROUP_ID+0, @ID, 'It is good you have returned, $p. I have news.', 12, 0, 100, 1, 0, 203528, 0, 0, 'Kodethi to Player'),
(193889, @GROUP_ID+1, @ID, 'Scalecommander Emberthal awaits your arrival atop Grommash Hold. Let us not keep her waiting.', 12, 0, 100, 1, 0, 203527, 0, 0, 'Kodethi to Player'),
(197279, @GROUP_ID+0, @ID, 'You made quick work of gathering our expedition members. I admire efficiency in my traveling companions.', 12, 0, 100, 0, 0, 204290, 0, 0, 'Naleidea Rivergleam to Player');


UPDATE `quest_template` SET `RewardBonusMoney`=875, `VerifiedBuild`=45505 WHERE `ID`=70045; -- Truths and Revelations
UPDATE `quest_template` SET `RewardBonusMoney`=875, `VerifiedBuild`=45505 WHERE `ID`=65439; -- Whispers on the Winds
UPDATE `quest_template` SET `RewardBonusMoney`=7050, `VerifiedBuild`=45505 WHERE `ID`=65443; -- Expeditionary Coordination
UPDATE `quest_template` SET `RewardBonusMoney`=875, `VerifiedBuild`=45505 WHERE `ID`=65437; -- Aspectral Invitation
UPDATE `quest_template` SET `VerifiedBuild`=45505 WHERE `ID` IN (59926, 29611, 26293, 25924, 13618, 44543, 44281, 57562, 54748, 58744, 56308, 46736, 46735, 46277, 56120, 57565, 50598, 57567, 50602);
UPDATE `quest_template` SET `RewardBonusMoney`=600, `VerifiedBuild`=45505 WHERE `ID`=57094; -- The Price of Victory
UPDATE `quest_template` SET `RewardBonusMoney`=100, `VerifiedBuild`=45505 WHERE `ID`=50242; -- A Choice of Allies
UPDATE `quest_template` SET `RewardBonusMoney`=600, `VerifiedBuild`=45505 WHERE `ID`=58778; -- Getting Ahead
UPDATE `quest_template` SET `RewardBonusMoney`=600, `VerifiedBuild`=45505 WHERE `ID`=58776; -- Hatching Problems
UPDATE `quest_template` SET `RewardBonusMoney`=875, `VerifiedBuild`=45505 WHERE `ID`=65435; -- The Dragon Isles Await


UPDATE `quest_objectives` SET `VerifiedBuild`=45505 WHERE `ID` IN (429443, 422987, 422989, 422988, 422958, 397237, 391634, 395999, 352819, 296760, 296759, 296758, 254560, 266797, 286696, 286487, 286486, 286485, 286484, 392645, 394878, 395020, 395181, 390565, 390564, 395333, 390563, 390562, 390561, 390560, 390559, 390558, 390567, 390557, 390556, 390555, 394933, 394943, 289536, 289535, 289167, 390280, 392894, 336162, 337022);


UPDATE `quest_visual_effect` SET `VerifiedBuild`=45505 WHERE (`Index`=0 AND `ID` IN (429443,422987,422989,422988,422958,397237,391634,395999,352819,296760,296759,296758,286486,286485,286484,394878,390565,390564,390556)) OR (`Index`=5 AND `ID` IN (286486,390564,390556)) OR (`Index`=4 AND `ID` IN (286486,390564,390556)) OR (`Index`=3 AND `ID` IN (286486,390564,390556)) OR (`Index`=2 AND `ID` IN (286486,390564,390556)) OR (`Index`=1 AND `ID` IN (286486,390564,390556)) OR (`Index`=6 AND `ID` IN (390564,390556)) OR (`Index`=17 AND `ID`=390556) OR (`Index`=16 AND `ID`=390556) OR (`Index`=15 AND `ID`=390556) OR (`Index`=14 AND `ID`=390556) OR (`Index`=13 AND `ID`=390556) OR (`Index`=12 AND `ID`=390556) OR (`Index`=11 AND `ID`=390556) OR (`Index`=10 AND `ID`=390556) OR (`Index`=9 AND `ID`=390556) OR (`Index`=8 AND `ID`=390556) OR (`Index`=7 AND `ID`=390556);

DELETE FROM `creature_template` WHERE `entry` IN (197767 /*Aetheil*/, 197770 /*Rips*/, 197771 /*Yuyu*/);
INSERT INTO `creature_template` (`entry`, `KillCredit1`, `KillCredit2`, `name`, `femaleName`, `subname`, `TitleAlt`, `IconName`, `HealthScalingExpansion`, `RequiredExpansion`, `VignetteID`, `unit_class`, `WidgetSetID`, `WidgetSetUnitConditionID`, `rank`, `family`, `type`, `type_flags`, `type_flags2`, `HealthModifier`, `ManaModifier`, `RacialLeader`, `movementId`, `CreatureDifficultyID`, `VerifiedBuild`) VALUES
(197767, 0, 0, 'Aetheil', '', NULL, NULL, NULL, 6, 0, 0, 8, 0, 0, 0, 0, 7, 0, 0, 1, 1, 0, 0, 226125, 45505), -- Aetheil
(197770, 0, 0, 'Rips', '', NULL, NULL, 'openhandglow', 6, 0, 0, 1, 0, 0, 0, 52, 1, 0, 0, 1, 1, 0, 62, 226128, 45505), -- Rips
(197771, 0, 0, 'Yuyu', '', NULL, NULL, 'openhandglow', 6, 0, 0, 1, 0, 0, 0, 52, 1, 0, 0, 1, 1, 0, 62, 226129, 45505); -- Yuyu


UPDATE `creature_template` SET `VerifiedBuild`=45505 WHERE `entry`=44740; -- Sahi Cloudsinger
UPDATE `creature_template` SET `VerifiedBuild`=45505 WHERE `entry`=44743; -- Nohi Plainswalker
UPDATE `creature_template` SET `VerifiedBuild`=45505 WHERE `entry` IN (42506, 152121, 44745, 46985, 100679, 100682, 44770, 58193, 58199, 44779, 44780, 44781, 44782, 44783, 44785, 42548, 44787, 44788, 35845, 29143, 42594, 190239, 44851, 44852, 44853, 44854, 44856, 44865, 44866, 44867, 44868, 44871, 44872, 65008, 42638, 44876, 44877, 44878, 161203, 29238, 161223, 62809, 44918, 44919, 62821, 62822, 65065, 65071, 65074, 65076, 65078, 42709, 44948, 6929, 188157, 188169, 6986, 47253, 6987, 47254, 7010, 305, 54004, 47321, 89830, 20486, 20488, 20489, 20490, 47335, 20491, 49573, 47336, 20492, 20493, 31695, 7088, 141310, 31697, 190535, 31717, 31720, 31723, 31724, 74228, 31725, 49622, 31726, 31727, 416, 417, 13842, 197279, 54113, 197288, 152561, 31778, 25075, 4953, 45230, 49737, 49743, 49750, 43062, 52032, 52034, 31902, 47571, 31912, 141528, 175084, 9564, 2855, 2857, 49837, 40891, 27489, 175135, 175156, 175165, 168459, 47663, 5188, 43239, 195357, 121541, 188655, 188656, 197611, 195385, 103673, 168551, 168553, 54472, 54473, 38821, 58965, 168596, 168597, 168598, 197679, 197680, 197682, 32151, 168621, 3084, 168623, 168626, 184286, 168628, 3100, 3108, 50088, 3127, 3144, 103822, 179897, 12136, 3189, 14375, 70301, 14376, 14377, 3197, 3198, 3204, 61369, 14392, 72559, 3216, 141912, 135201, 135202, 3225, 141920, 63626, 14451, 50269, 195677, 3296, 3300, 193450, 72654, 3310, 3312, 14498, 3313, 14499, 3314, 3315, 3316, 3317, 3319, 3321, 3322, 3323, 3329, 3330, 3331, 3332, 3333, 3334, 3335, 3342, 97296, 3345, 3346, 50323, 3347, 3348, 3350, 3351, 3359, 3363, 3364, 3365, 3366, 3367, 3368, 5606, 3369, 3370, 3371, 5609, 3372, 5610, 5611, 5613, 5614, 66022, 130911, 5639, 189075, 3404, 3405, 153285, 3412, 3413, 189085, 189091, 32520, 34765, 184650, 21354, 184664, 184666, 7951, 32562, 50477, 23635, 50488, 195899, 37072, 133271, 137762, 5811, 5816, 5817, 5822, 72934, 184786, 184787, 41621, 52809, 184793, 52810, 184795, 52812, 184796, 184797, 184798, 184800, 184801, 184807, 184808, 184809, 184810, 184812, 184813, 184814, 169166, 34955, 46140, 5875, 46142, 5892, 1420, 5909, 17098, 46181, 88701, 88702, 14881, 88703, 88706, 5951, 189398, 193889, 35068, 26125, 176012, 176094, 176095, 46357, 46358, 46359, 160452, 149270, 189554, 169428, 149296, 44158, 44160, 194050, 194055, 194056, 171689, 171691, 194065, 194073, 160526, 160527, 160528, 189609, 160529, 160530, 62114, 62115, 62116, 180684, 149371, 194115, 194116, 12922, 180701, 71100, 68869, 15186, 15188, 46512, 176261, 62193, 62194, 62195, 62196, 62197, 62198, 62199, 62200, 35364, 4047, 46555, 46556, 46572, 44338, 1860, 102529, 57801, 46618, 46619, 46620, 46621, 46622, 165189, 174147, 46642, 174170, 26537, 10880, 8659, 46708, 46709, 46716, 46718, 194361, 51195, 6466, 46741, 46742, 51230, 60199, 187709, 187710, 187711, 15476, 31146, 11017, 100502, 4311, 187758, 187775, 28960, 11066, 51346, 20029, 31216, 71486, 49131, 194561, 194563, 194569, 194576, 194577, 194581, 158789, 194582, 194583, 100636, 69333, 58155, 13417, 100663, 100664);
UPDATE `creature_template` SET `VerifiedBuild`=45505 WHERE `entry`=47233; -- Gordul
UPDATE `creature_template` SET `VerifiedBuild`=45505 WHERE `entry`=47246; -- Ureda
UPDATE `creature_template` SET `VerifiedBuild`=45505 WHERE `entry`=47247; -- Marud
UPDATE `creature_template` SET `VerifiedBuild`=45505 WHERE `entry`=47248; -- Gija
UPDATE `creature_template` SET `VerifiedBuild`=45505 WHERE `entry`=45337; -- Tyelis
UPDATE `creature_template` SET `VerifiedBuild`=45505 WHERE `entry`=45339; -- Dark Cleric Cecille
UPDATE `creature_template` SET `VerifiedBuild`=45505 WHERE `entry`=23128; -- Master Pyreanor
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45505 WHERE `entry`=61167; -- Mountain Cottontail
UPDATE `creature_template` SET `VerifiedBuild`=45505 WHERE `entry`=3327; -- Gest
UPDATE `creature_template` SET `VerifiedBuild`=45505 WHERE `entry`=3328; -- Ormok
UPDATE `creature_template` SET `VerifiedBuild`=45505 WHERE `entry`=3353; -- Grezz Ragefist
UPDATE `creature_template` SET `VerifiedBuild`=45505 WHERE `entry`=3354; -- Sorek
UPDATE `creature_template` SET `VerifiedBuild`=45505 WHERE `entry`=3403; -- Sian'tsu
UPDATE `creature_template` SET `VerifiedBuild`=45505 WHERE `entry`=72939; -- Terga Earthbreaker
UPDATE `creature_template` SET `VerifiedBuild`=45505 WHERE `entry`=88704; -- Gran'dul
UPDATE `creature_template` SET `VerifiedBuild`=45505 WHERE `entry`=88705; -- Kranosh
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45505 WHERE `entry`=55382; -- Darkmoon Faire Mystic Mage
UPDATE `creature_template` SET `VerifiedBuild`=45505 WHERE `entry`=68979; -- Voidbinder Zorlan
UPDATE `creature_template` SET `VerifiedBuild`=45505 WHERE `entry`=46667; -- Blademaster Ronakada
UPDATE `creature_template` SET `VerifiedBuild`=45505 WHERE `entry`=62445; -- Ji Firepaw
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45505 WHERE `entry`=158637; -- Guiding Orb
UPDATE `creature_template` SET `VerifiedBuild`=45505 WHERE `entry`=44723; -- Nahu Ragehoof
UPDATE `creature_template` SET `VerifiedBuild`=45505 WHERE `entry`=44725; -- Sunwalker Atohmo
UPDATE `creature_template` SET `VerifiedBuild`=45505 WHERE `entry`=44726; -- Shalla Whiteleaf
UPDATE `creature_template` SET `VerifiedBuild`=45505 WHERE `entry`=44735; -- Seer Liwatha

DELETE FROM `creature_template_model` WHERE (`Idx`=0 AND `CreatureID` IN (197771,197770,197767));
INSERT INTO `creature_template_model` (`CreatureID`, `Idx`, `CreatureDisplayID`, `DisplayScale`, `Probability`, `VerifiedBuild`) VALUES
(197771, 0, 73093, 0.60000002384185791, 1, 45505), -- Yuyu
(197770, 0, 79383, 0.75, 1, 45505), -- Rips
(197767, 0, 109709, 1, 1, 45505); -- Aetheil

UPDATE `creature_template_model` SET `VerifiedBuild`=45505 WHERE (`Idx`=1 AND `CreatureID` IN (193889,3300,195677,194115,189554,180701,184814,184813,100682,100679,100664,100663,100502,184807,197611,3198,3197,71100,40891,46985,72934,65008,35845,169428,44160,189091,51230,58193,184812,50088,4953,133271,42548,45230,15476,52810,14499,14881,55382,44158,3084,103822,26125,62115,61167,72654,46140,42594,89830,46142,149371,184650,149296,38821,49743,72559,32520,28960,74228,189398,149270,168459,62114,51346,3296,49837)) OR (`Idx`=0 AND `CreatureID` IN (193889,193450,194116,194065,160529,160528,160527,194583,194576,194569,194073,194050,189609,160530,194577,194563,194561,194361,160526,194582,194581,3108,3300,195677,197288,195385,195357,194056,194055,184809,41621,197279,195899,194115,189554,189075,184810,184808,180701,184814,184813,100682,100679,100664,62116,5951,3100,100663,3127,175165,184286,3204,100502,5822,184807,4311,175156,197611,3198,3197,71100,40891,43239,60199,31216,103673,174170,171691,168626,168598,46985,69333,65065,62445,49573,35364,34955,171689,168628,168623,168553,168551,72934,68869,65074,65008,46667,13842,12922,3354,3353,169166,168621,168597,168596,70301,66022,65078,65076,65071,15186,7951,184798,184797,184795,176261,175084,42709,35845,3333,46642,42638,3332,62193,46619,46618,180684,46620,46622,152121,160452,158789,152561,46621,3359,161203,31146,169428,416,153285,2855,61369,1420,188169,7088,5811,3365,3351,3348,3347,3225,8659,6987,6986,3350,3316,62197,62196,46181,11066,3366,3346,3321,3345,197682,197680,197679,190535,184787,46742,46741,3372,3371,7010,44160,34765,3405,3404,179897,187710,29143,189091,187711,187709,184801,184800,184796,44783,15188,161223,72939,44788,44785,44782,13417,5892,3403,51230,184793,184786,184666,184664,44770,44780,58199,58193,47336,47335,47321,44779,44781,3322,184812,176095,176094,176012,50088,44787,54004,47663,174147,141920,141912,54113,4953,133271,44745,44743,44740,44726,44725,44723,42548,88706,88705,88704,47254,5909,5875,5816,3335,3334,3330,3328,45230,3327,44735,47233,3189,12136,187775,141528,130911,43062,26537,9564,44948,44918,20493,20491,20490,20489,20488,20486,5639,46716,15476,46718,3317,11017,3413,3412,3364,3363,3315,52812,52809,62200,62199,52810,52032,14498,14451,2857,68979,57801,54473,54472,49737,46708,3369,3368,14499,3367,62194,50477,46709,42506,63626,50488,50323,44919,20492,14881,3310,3216,141310,47253,55382,47248,47247,47246,44158,3331,3329,3084,14377,23635,417,158637,58965,103822,26125,121541,31727,31726,31725,31724,31723,31720,25075,62115,10880,46358,37072,46357,46512,46359,3319,1860,61167,62822,62821,29238,62198,49131,14376,135201,72654,58155,52034,47571,46555,46140,45337,35068,23128,17098,3323,3314,44338,42594,189085,46556,188655,89830,49622,46142,45339,44872,44868,44867,44866,44865,27489,4047,3312,3144,149371,184650,190239,149296,175135,44852,14392,5610,5613,137762,188157,88701,135202,44877,14375,44871,6466,44854,3370,38821,49743,88703,100636,72559,46572,187758,5188,3342,49750,32520,102529,44878,6929,5609,3313,28960,5817,44853,5614,74228,62195,189398,5606,44851,88702,149270,168459,188656,5611,165189,44856,62114,44876,51346,97296,51195,3296,49837,20029,21354,305,32562,32151,31902,31778,31697,31717,31695,50269,71486,31912,62809)) OR (`Idx`=2 AND `CreatureID` IN (3300,195677,194115,189554,184814,184813,100682,100679,100664,100663,100502,71100,40891,65008,169428,44160,189091,51230,58193,184812,4953,133271,42548,45230,15476,14499,44158,3084,103822,26125,62115,61167,46140,89830,46142,149371,149296,49743,74228,168459,62114,51346,3296,49837)) OR (`Idx`=3 AND `CreatureID` IN (195677,194115,189554,184814,184813,100682,100679,100664,100663,100502,71100,40891,65008,169428,44160,189091,51230,58193,184812,4953,133271,42548,45230,15476,14499,44158,3084,103822,26125,62115,61167,46140,89830,46142,149371,149296,49743,74228,168459,62114,51346,3296,49837)) OR (`Idx`=7 AND `CreatureID` IN (194115,184814,184813,184812,46140)) OR (`Idx`=6 AND `CreatureID` IN (194115,189554,184814,184813,184812,46140)) OR (`Idx`=5 AND `CreatureID` IN (194115,189554,184814,184813,184812,45230,46140,3296)) OR (`Idx`=4 AND `CreatureID` IN (194115,189554,184814,184813,184812,45230,46140,3296)) OR (`Idx`=9 AND `CreatureID` IN (184814,184812)) OR (`Idx`=8 AND `CreatureID` IN (184814,184812)) OR (`Idx`=11 AND `CreatureID`=184812) OR (`Idx`=10 AND `CreatureID`=184812);


UPDATE `creature_questitem` SET `VerifiedBuild`=45505 WHERE (`Idx`=0 AND `CreatureEntry` IN (3108,3127,3198,3197,42594)) OR (`Idx`=1 AND `CreatureEntry` IN (3198,3197));

DELETE FROM `gameobject_template` WHERE `entry` IN (376849 /*Reliquary Arcwine*/, 376848 /*Reliquary Pillows*/, 376847 /*Reliquary Pillows*/, 376846 /*Reliquary Pillows*/, 376845 /*Reliquary Chair*/, 376704 /*Reliquary Pillow*/, 376842 /*Telescope*/, 376837 /*Reliquary Barrel*/, 376674 /*Reliquary Crate*/, 376840 /*Reliquary Jar*/, 376839 /*Reliquary Jar*/, 376708 /*Reliquary Crate*/, 375041 /*The Defiant Dragonscale*/, 382174 /*Tablet*/, 382173 /*Tablet*/, 382171 /*Jewels*/, 382170 /*Scrolls*/, 382169 /*Books*/, 382167 /*Scroll*/, 382165 /*Scroll*/, 382164 /*Scroll*/, 382163 /*Scroll*/, 382162 /*Lamp*/, 382172 /*Idol*/, 380543 /*Fire Wall*/, 376794 /*Crates*/, 376514 /*Sleeping Mat*/, 376419 /*Under Construction*/, 376796 /*Tent*/, 376803 /*Banner*/);
INSERT INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `IconName`, `castBarCaption`, `unk1`, `size`, `Data0`, `Data1`, `Data2`, `Data3`, `Data4`, `Data5`, `Data6`, `Data7`, `Data8`, `Data9`, `Data10`, `Data11`, `Data12`, `Data13`, `Data14`, `Data15`, `Data16`, `Data17`, `Data18`, `Data19`, `Data20`, `Data21`, `Data22`, `Data23`, `Data24`, `Data25`, `Data26`, `Data27`, `Data28`, `Data29`, `Data30`, `Data31`, `Data32`, `Data33`, `Data34`, `ContentTuningId`, `VerifiedBuild`) VALUES
(376849, 5, 34494, 'Reliquary Arcwine', '', '', '', 0.800000011920928955, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Reliquary Arcwine
(376848, 5, 36376, 'Reliquary Pillows', '', '', '', 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Reliquary Pillows
(376847, 5, 74699, 'Reliquary Pillows', '', '', '', 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Reliquary Pillows
(376846, 5, 37520, 'Reliquary Pillows', '', '', '', 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Reliquary Pillows
(376845, 5, 34334, 'Reliquary Chair', '', '', '', 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Reliquary Chair
(376704, 5, 74541, 'Reliquary Pillow', '', '', '', 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Reliquary Pillow
(376842, 5, 74696, 'Telescope', '', '', '', 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Telescope
(376837, 5, 74692, 'Reliquary Barrel', '', '', '', 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Reliquary Barrel
(376674, 5, 72869, 'Reliquary Crate', '', '', '', 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Reliquary Crate
(376840, 5, 74694, 'Reliquary Jar', '', '', '', 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Reliquary Jar
(376839, 5, 74693, 'Reliquary Jar', '', '', '', 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Reliquary Jar
(376708, 5, 74546, 'Reliquary Crate', '', '', '', 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Reliquary Crate
(375041, 15, 75394, 'The Defiant Dragonscale', '', '', '', 1, 8658, 30, 1, 0, 0, 61, 2523, 21511, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- The Defiant Dragonscale
(382174, 5, 47840, 'Tablet', '', '', '', 0.60000002384185791, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Tablet
(382173, 5, 46283, 'Tablet', '', '', '', 0.60000002384185791, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Tablet
(382171, 5, 34985, 'Jewels', '', '', '', 0.60000002384185791, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Jewels
(382170, 5, 35102, 'Scrolls', '', '', '', 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Scrolls
(382169, 5, 36367, 'Books', '', '', '', 0.60000002384185791, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Books
(382167, 5, 77697, 'Scroll', '', '', '', 0.60000002384185791, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Scroll
(382165, 5, 12800, 'Scroll', '', '', '', 0.800000011920928955, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Scroll
(382164, 5, 11756, 'Scroll', '', '', '', 0.319999992847442626, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Scroll
(382163, 5, 77696, 'Scroll', '', '', '', 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Scroll
(382162, 5, 12323, 'Lamp', '', '', '', 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Lamp
(382172, 5, 42336, 'Idol', '', '', '', 0.100000001490116119, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Idol
(380543, 0, 75845, 'Fire Wall', '', '', '', 0.75, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Fire Wall
(376794, 5, 74613, 'Crates', '', '', '', 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Crates
(376514, 5, 50355, 'Sleeping Mat', '', '', '', 0.60000002384185791, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Sleeping Mat
(376419, 5, 9725, 'Under Construction', '', '', '', 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Under Construction
(376796, 5, 74627, 'Tent', '', '', '', 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Tent
(376803, 5, 74638, 'Banner', '', '', '', 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505); -- Banner

UPDATE `gameobject_template` SET `VerifiedBuild`=45505 WHERE `entry` IN (1619, 204360, 1618, 196475, 204168, 204169, 204167, 204170, 355504, 204171, 203471, 58595, 204172, 207889, 152614, 1731, 323850, 355229, 351920, 351918, 349790, 204705, 204703, 351926, 351923, 351922, 351921, 351919, 351430, 349788, 351925, 351924, 204683, 349789, 204682, 207637, 204714, 204713, 207640, 204702, 187376, 207638, 204701, 339239, 325890, 207636, 204685, 204684, 204638, 204637, 204636, 204635, 204618, 204615, 204619, 204617, 204616, 204614, 202805, 195222, 204941, 202814, 202813, 209050, 209049, 209045, 207631, 204940, 204708, 204707, 204613, 204612, 202816, 202811, 202817, 208054, 204706, 204694, 204678, 204680, 204698, 204679, 202815, 207632, 202810, 197261, 35591, 202808, 197257, 206733, 204723, 207146, 207150, 207149, 207148, 207147, 206732, 204722, 205090, 204689, 3301, 207690, 207687, 205091, 50803, 207635, 206595, 206508, 50805, 206739, 206738, 50804, 204699, 207634, 204719, 204700, 204727, 204726, 204721, 204720, 237942, 204688, 197260, 197314, 197307, 197286, 197285, 197259, 197311, 197322, 206548, 197276, 206547, 197278, 197309, 206730, 197280, 206740, 293684, 205056, 206549, 197312, 206538, 197310, 197207, 204937, 193981, 202804, 202803, 204681, 202802, 208270, 208269, 207633, 204939, 204938, 204936, 204696, 204695, 202809, 210059, 210058, 207630, 204693, 202801, 202800, 186722, 212212, 208534, 207646, 202799, 202798, 197315, 206529, 197313, 105576, 197323, 197287, 197284, 197279, 209124, 209114, 206741, 206736, 206546, 206545, 206539, 204634, 204633, 202717, 210181, 207414, 206530, 204632, 204631, 204204, 204203, 204197, 204192, 204191, 190549, 204611, 202590, 190942, 175080, 206729, 204607, 204606, 204200, 204196, 204195, 204194, 204605, 204205, 259114, 204610, 204608, 175788, 175787, 206110, 204604, 269949, 206995, 204609, 204209, 204199, 266354, 180007, 179965, 281340, 186238, 203969, 205142, 223739, 206608, 206609, 206610, 204603, 204602, 204214, 204662, 204650, 204210, 204647, 204215, 204651, 204601, 204207, 204600, 206725, 206726, 205109, 204208, 204663, 204163, 204664, 204201, 206727, 205108, 204211, 204202, 204212, 223814, 204213);
UPDATE `gameobject_template` SET `Data2`=1, `ContentTuningId`=356, `VerifiedBuild`=45505 WHERE `entry`=245730; -- Reinforced Gate
UPDATE `gameobject_template` SET `ContentTuningId`=356, `VerifiedBuild`=45505 WHERE `entry`=246039; -- Protective Barrier


UPDATE `gameobject_questitem` SET `VerifiedBuild`=45505 WHERE (`Idx`=0 AND `GameObjectEntry` IN (204360,58595,203969));


