--
DELETE FROM `areatrigger_template` WHERE (`IsServerSide`=0 AND `Id` IN (16552,26038));
INSERT INTO `areatrigger_template` (`Id`, `IsServerSide`, `Type`, `Flags`, `Data0`, `Data1`, `Data2`, `Data3`, `Data4`, `Data5`, `VerifiedBuild`) VALUES
(16552, 0, 4, 0, 6, 6, 2, 2, 0.300000011920928955, 0.300000011920928955, 44061);
DELETE FROM `areatrigger_create_properties` WHERE `Id` IN (11866 /*SpellId : 255545*/, 21827 /*SpellId : 342761*/);
INSERT INTO `areatrigger_create_properties` (`Id`, `AreaTriggerId`, `ScriptName`, `MoveCurveId`, `ScaleCurveId`, `MorphCurveId`, `FacingCurveId`, `AnimId`, `AnimKitId`, `DecalPropertiesId`, `TimeToTarget`, `TimeToTargetScale`, `Shape`, `ShapeData0`, `ShapeData1`, `ShapeData2`, `ShapeData3`, `ShapeData4`, `ShapeData5`, `ShapeData6`, `ShapeData7`, `VerifiedBuild`) VALUES
(11866, 16552, 'at_rogue_poison_bomb', 0, 0, 0, 0, -1, 0, 0, 0, 2000, 4, 6, 6, 2, 2, 0.300000011920928955, 0.300000011920928955, 0, 0, 44061); -- SpellId : 255545