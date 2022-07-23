-- monk 2


DELETE FROM spell_script_names WHERE spell_id = 115203;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (115203, 'spell_fortifying_brew');

DELETE FROM `areatrigger_template` WHERE (`Id`=24192 AND `IsServerSide`=0);
INSERT INTO `areatrigger_template` (`Id`, `IsServerSide`, `Type`, `Flags`, `Data0`, `Data1`, `Data2`, `Data3`, `Data4`, `Data5`, `VerifiedBuild`) VALUES
(24192, 0, 1, 0, 5, 5, 2.5, 5, 5, 2.5, 44730);


DELETE FROM `areatrigger_create_properties` WHERE `Id` IN (20281 /*SpellId : 327195*/, 20280 /*SpellId : 327257*/);
INSERT INTO `areatrigger_create_properties` (`Id`, `AreaTriggerId`, `MoveCurveId`, `ScaleCurveId`, `MorphCurveId`, `FacingCurveId`, `AnimId`, `AnimKitId`, `DecalPropertiesId`, `TimeToTarget`, `TimeToTargetScale`, `Shape`, `ShapeData0`, `ShapeData1`, `ShapeData2`, `ShapeData3`, `ShapeData4`, `ShapeData5`, `ShapeData6`, `ShapeData7`, `VerifiedBuild`) VALUES
(20281, 24192, 0, 0, 0, 0, -1, 0, 0, 0, 30000, 1, 5, 4, 2.5, 5, 4, 2.5, 0, 0, 44730), -- SpellId : 327195
(20280, 24192, 0, 0, 0, 0, -1, 0, 0, 0, 30000, 1, 5, 5, 2.5, 5, 5, 2.5, 0, 0, 44730); -- SpellId : 327257
