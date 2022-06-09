<<<<<<< HEAD
DELETE FROM `broadcast_text` WHERE `ID`=700073 AND `VerifiedBuild`=0;
INSERT INTO `broadcast_text` (`Text`, `Text1`, `ID`, `LanguageID`, `ConditionID`, `EmotesID`, `Flags`, `ChatBubbleDurationMs`, `VoiceOverPriorityID`, `SoundKitID1`, `SoundKitID2`, `EmoteID1`, `EmoteID2`, `EmoteID3`, `EmoteDelay1`, `EmoteDelay2`, `EmoteDelay3`, `VerifiedBuild`) VALUES ('Hey mon, looks like you\'re in quite a pickle.\r\nNot quite sure how ya got \'ere, but I can send ya back. Me an\' Thrall got a deal going on right now, so this one\'s free.', NULL, 700073, 0, 0, 0, 64, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
=======
-- 
DELETE FROM spell_script_names WHERE spell_id = 315175;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (315175, 'spell_grasping_tendrils');
DELETE FROM spell_script_names WHERE spell_id = 315169;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (315169, 'spell_eye_of_corruption');

DELETE FROM spell_script_names WHERE spell_id = 315184;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (315184, 'spell_grand_delusions');

DELETE FROM spell_script_names WHERE spell_id = 337612;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (337612, 'spell_inescapable_consequences');


replace INTO `areatrigger_template` (`Id`, `IsServerSide`, `Type`, `Flags`, `Data0`, `Data1`, `Data2`, `Data3`, `Data4`, `Data5`, `VerifiedBuild`) VALUES
(22815, 0, 4, 0, 5, 5, 4, 4, 0.300000011920928955, 0.300000011920928955, 33941);

replace INTO `areatrigger_create_properties` (`Id`, `AreaTriggerId`, `scriptname`, `MoveCurveId`, `ScaleCurveId`, `MorphCurveId`, `FacingCurveId`, `AnimId`, `AnimKitId`, `DecalPropertiesId`, `TimeToTarget`, `TimeToTargetScale`, `Shape`, `ShapeData0`, `ShapeData1`, `ShapeData2`, `ShapeData3`, `ShapeData4`, `ShapeData5`, `ShapeData6`, `ShapeData7`, `VerifiedBuild`) VALUES
(18755, 22815, 'at_eye_of_corruption', 0, 0, 0, 0, 0, 0, 0, 0, 8000, 4, 5, 5, 4, 4, 0.300000011920928955, 0.300000011920928955, 0, 0, 33941); -- SpellId : 315154

 UPDATE creature_template set ScriptName = 'npc_thing_from_beyond_161895', minlevel=60,maxlevel=60 WHERE entry = 161895;
DELETE FROM spell_script_names WHERE spell_id = 318392;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (318392, 'spell_grand_delusions_spawn');

DELETE FROM spell_script_names WHERE spell_id = 315161;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (315161, 'spell_eye_of_corruption_dmg');

DELETE FROM `npc_text` WHERE `ID`=688881;
INSERT INTO `npc_text` (`ID`, `Probability0`, `Probability1`, `Probability2`, `Probability3`, `Probability4`, `Probability5`, `Probability6`, `Probability7`, `BroadcastTextID0`, `BroadcastTextID1`, `BroadcastTextID2`, `BroadcastTextID3`, `BroadcastTextID4`, `BroadcastTextID5`, `BroadcastTextID6`, `BroadcastTextID7`, `VerifiedBuild`) VALUES (688881, 0, 0, 0, 0, 0, 0, 0, 0, 688881, 0, 0, 0, 0, 0, 0, 0, 0);
>>>>>>> 975aa79e (Corruptions part 1. Updates #91)
