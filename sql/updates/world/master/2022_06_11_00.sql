-- 
INSERT ignore INTO `areatrigger_template` (`Id`, `IsServerSide`, `Type`, `Flags`, `Data0`, `Data1`, `Data2`, `Data3`, `Data4`, `Data5`, `VerifiedBuild`) VALUES
(11908, 0, 0, 0, 1, 1, 0, 0, 0, 0, 44061),
(23820, 0, 1, 16, 2.5, 3, 3, 2.5, 3, 3, 44061),
(21502, 0, 0, 4, 8, 8, 0, 0, 0, 0, 44061),
(23556, 0, 0, 0, 5, 5, 0, 0, 0, 0, 44061),
(21500, 0, 0, 0, 100, 100, 0, 0, 0, 0, 44061),
(21495, 0, 0, 0, 100, 100, 0, 0, 0, 0, 44061),
(26038, 0, 0, 0, 4, 4, 0, 0, 0, 0, 44061),
(10133, 0, 0, 0, 8, 8, 0, 0, 0, 0, 44061);


INSERT ignore INTO `areatrigger_create_properties` (`Id`, `AreaTriggerId`, `MoveCurveId`, `ScaleCurveId`, `MorphCurveId`, `FacingCurveId`, `AnimId`, `AnimKitId`, `DecalPropertiesId`, `TimeToTarget`, `TimeToTargetScale`, `Shape`, `ShapeData0`, `ShapeData1`, `ShapeData2`, `ShapeData3`, `ShapeData4`, `ShapeData5`, `ShapeData6`, `ShapeData7`, `VerifiedBuild`) VALUES
(7478, 11908, 0, 0, 0, 0, -1, 0, 0, 0, 90000, 0, 1, 1, 0, 0, 0, 0, 0, 0, 44061), -- SpellId : 216721
(17250, 21502, 0, 0, 0, 0, -1, 0, 365, 0, 18000, 0, 8, 8, 0, 0, 0, 0, 0, 0, 44061), -- SpellId : 301842
(17248, 21500, 0, 0, 0, 0, -1, 0, 0, 0, 9000, 0, 100, 100, 0, 0, 0, 0, 0, 0, 44061),-- SpellId : 301773 CANNOT FIND PROPERTIES ID, USED SPELL ID AS KEY (NEEDS MANUAL CORRECTION)
(17243, 21495, 0, 0, 0, 0, -1, 0, 0, 0, 9000, 0, 100, 100, 0, 0, 0, 0, 0, 0, 44061);


DELETE FROM spell_script_names WHERE spell_id = 310835;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (310835, 'spell_charged_weapons');
