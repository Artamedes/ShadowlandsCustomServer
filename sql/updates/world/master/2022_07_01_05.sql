-- blessed hummer
DELETE FROM `areatrigger_template` WHERE (`Id`=10698 AND `IsServerSide`=0);
INSERT INTO `areatrigger_template` (`Id`, `IsServerSide`, `Type`, `Flags`, `Data0`, `Data1`, `Data2`, `Data3`, `Data4`, `Data5`, `VerifiedBuild`) VALUES
(10698, 0, 0, 0, 3, 3, 0, 0, 0, 0, 44325);


DELETE FROM `areatrigger_create_properties` WHERE `Id`=6006;
INSERT INTO `areatrigger_create_properties` (`Id`, `AreaTriggerId`, `MoveCurveId`, `ScaleCurveId`, `MorphCurveId`, `FacingCurveId`, `AnimId`, `AnimKitId`, `DecalPropertiesId`, `TimeToTarget`, `TimeToTargetScale`, `Shape`, `ShapeData0`, `ShapeData1`, `ShapeData2`, `ShapeData3`, `ShapeData4`, `ShapeData5`, `ShapeData6`, `ShapeData7`, `VerifiedBuild`) VALUES
(6006, 10698, 0, 0, 0, 0, -1, 0, 0, 5000, 5000, 0, 3, 3, 0, 0, 0, 0, 0, 0, 44325); -- SpellId : 204019