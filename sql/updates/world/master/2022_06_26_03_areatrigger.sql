-- areatrigger example
DELETE FROM `areatrigger_template` WHERE (`IsServerSide`=0 AND `Id` IN (15997,15410));
INSERT INTO `areatrigger_template` (`Id`, `IsServerSide`, `Type`, `Flags`, `Data0`, `Data1`, `Data2`, `Data3`, `Data4`, `Data5`, `VerifiedBuild`) VALUES
(15997, 0, 0, 0, 4, 4, 0, 0, 0, 0, 44232);


DELETE FROM `areatrigger_create_properties` WHERE `Id` IN (11208 /*SpellId : 249881*/);
INSERT INTO `areatrigger_create_properties` (`Id`, `AreaTriggerId`, `MoveCurveId`, `ScaleCurveId`, `MorphCurveId`, `FacingCurveId`, `AnimId`, `AnimKitId`, `DecalPropertiesId`, `TimeToTarget`, `TimeToTargetScale`, `Shape`, `ShapeData0`, `ShapeData1`, `ShapeData2`, `ShapeData3`, `ShapeData4`, `ShapeData5`, `ShapeData6`, `ShapeData7`, `VerifiedBuild`) VALUES
(11208, 15997, 0, 0, 0, 0, -1, 0, 25, 0, 20000, 0, 4, 4, 0, 0, 0, 0, 0, 0, 44232); -- SpellId : 249881

UPDATE areatrigger_create_properties SET scriptname = 'at_blistering_wave' WHERE id = 11208;

DELETE FROM spell_script_names WHERE spell_id = 249879;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (249879, 'spell_blistering_wave');
