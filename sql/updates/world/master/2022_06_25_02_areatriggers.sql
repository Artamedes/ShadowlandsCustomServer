-- areatriggers
DELETE FROM `areatrigger_template` WHERE (`IsServerSide`=0 AND `Id` IN (16678,17994));
INSERT INTO `areatrigger_template` (`Id`, `IsServerSide`, `Type`, `Flags`, `Data0`, `Data1`, `Data2`, `Data3`, `Data4`, `Data5`, `VerifiedBuild`) VALUES
(16678, 0, 0, 2, 3, 3, 0, 0, 0, 0, 44232),
(17994, 0, 0, 0, 14, 14, 0, 0, 0, 0, 44232);


DELETE FROM `areatrigger_create_properties` WHERE `Id` IN (11987 /*SpellId : 257051*/, 13406 /*SpellId : 270829*/);
INSERT INTO `areatrigger_create_properties` (`Id`, `AreaTriggerId`, `MoveCurveId`, `ScaleCurveId`, `MorphCurveId`, `FacingCurveId`, `AnimId`, `AnimKitId`, `DecalPropertiesId`, `TimeToTarget`, `TimeToTargetScale`, `Shape`, `ShapeData0`, `ShapeData1`, `ShapeData2`, `ShapeData3`, `ShapeData4`, `ShapeData5`, `ShapeData6`, `ShapeData7`, `VerifiedBuild`) VALUES
(11987, 16678, 0, 5062, 0, 0, -1, 0, 0, 0, 6000, 0, 3, 3, 0, 0, 0, 0, 0, 0, 44232), -- SpellId : 257051
(13406, 17994, 0, 0, 0, 0, -1, 0, 0, 0, 4000, 0, 14, 14, 0, 0, 0, 0, 0, 0, 44232); -- SpellId : 270829


UPDATE areatrigger_create_properties SET ScriptName = 'at_rain_of_decay' WHERE Id = 11987;