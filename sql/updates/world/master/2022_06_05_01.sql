--
UPDATE `areatrigger_create_properties` SET `ScriptName`='at_hun_binding_shot' WHERE  `Id`=5972;

DELETE FROM `areatrigger_template` WHERE (`IsServerSide`=0 AND `Id` IN (3841,9181,9170,3678,6966,5972,2947));
INSERT INTO `areatrigger_template` (`Id`, `IsServerSide`, `Type`, `Flags`, `Data0`, `Data1`, `Data2`, `Data3`, `Data4`, `Data5`, `VerifiedBuild`) VALUES
(3841, 0, 4, 0, 8, 8, 10, 10, 5, 5, 43971),
(9181, 0, 4, 0, 3, 3, 4, 4, 1, 1, 43971),
(9170, 0, 4, 0, 3, 3, 4, 4, 1, 1, 43971),
(3678, 0, 4, 0, 10, 10, 7, 7, 3, 3, 43971),
(6966, 0, 4, 0, 3, 3, 4, 4, 0.300000011920928955, 0.300000011920928955, 43971);

DELETE FROM `areatrigger_create_properties` WHERE `Id` IN (4436 /*SpellId : 187700*/, 4435 /*SpellId : 187699*/, 4424 /*SpellId : 187651*/, 510 /*SpellId : 132950*/, 2392 /*SpellId : 162496*/, 1524 /*SpellId : 109248*/, 304 /*SpellId : 342130*/);
INSERT INTO `areatrigger_create_properties` (`Id`, `AreaTriggerId`, `MoveCurveId`, `ScaleCurveId`, `MorphCurveId`, `FacingCurveId`, `AnimId`, `AnimKitId`, `DecalPropertiesId`, `TimeToTarget`, `TimeToTargetScale`, `Shape`, `ShapeData0`, `ShapeData1`, `ShapeData2`, `ShapeData3`, `ShapeData4`, `ShapeData5`, `ShapeData6`, `ShapeData7`, `ScriptName`, `VerifiedBuild`) VALUES
(4436, 3841, 0, 0, 0, 0, -1, 0, 0, 0, 30000, 4, 8, 8, 10, 10, 5, 5, 0, 0, 'at_hun_tar_trap_activated', 43971), -- SpellId : 187700
(4435, 9181, 0, 0, 0, 0, 153, 0, 0, 0, 60000, 4, 3, 3, 4, 4, 1, 1, 0, 0, 'at_hun_tar_trap_not_activated', 43971), -- SpellId : 187699
(4424, 9170, 0, 0, 0, 0, -1, 0, 0, 0, 60000, 4, 3, 3, 4, 4, 1, 1, 0, 0, 'at_hun_freezing_trap', 43971), -- SpellId : 187651
(510, 3678, 0, 0, 0, 0, -1, 0, 0, 0, 20000, 4, 10, 10, 7, 7, 3, 3, 0, 0, 'at_hun_flare', 43971), -- SpellId : 132950
(2392, 6966, 0, 0, 0, 0, -1, 0, 0, 0, 60000, 4, 3, 3, 4, 4, 0.300000011920928955, 0.300000011920928955, 0, 0, 'at_hunter_steeltrap', 43971); -- SpellId : 162496