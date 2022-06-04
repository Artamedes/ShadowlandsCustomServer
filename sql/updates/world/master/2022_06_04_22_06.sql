-- 
replace INTO `areatrigger_create_properties` (`Id`, `AreaTriggerId`, `MoveCurveId`, `ScaleCurveId`, `MorphCurveId`, `FacingCurveId`, `AnimId`, `AnimKitId`, `DecalPropertiesId`, `TimeToTarget`, `TimeToTargetScale`, `Shape`, `ShapeData0`, `ShapeData1`, `ShapeData2`, `ShapeData3`, `ShapeData4`, `ShapeData5`, `ShapeData6`, `ShapeData7`, `ScriptName`, `VerifiedBuild`) VALUES
(20004, 23951, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 40, 40, 0, 0, 0, 0, 0, 0, 'at_horn_of_the_wild_hunt', 43971), -- SpellId : 325270
(5977, 10665, 0, 0, 0, 0, -1, 0, 0, 0, 20000, 0, 6, 6, 0, 0, 0, 0, 0, 0, 'at_dh_shattered_souls', 43971);

replace INTO `areatrigger_template` (`Id`, `IsServerSide`, `Type`, `Flags`, `Data0`, `Data1`, `Data2`, `Data3`, `Data4`, `Data5`, `VerifiedBuild`) VALUES
(10665, 0, 0, 0, 6, 6, 0, 0, 0, 0, 43971),
(23951, 0, 0, 4, 40, 40, 0, 0, 0, 0, 43971);

DELETE FROM `spell_script_names` WHERE `spell_id`=258921 AND `ScriptName`='spell_dh_immolation_aura_damage';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (258921, 'spell_dh_immolation_aura_damage');

UPDATE `areatrigger_create_properties` SET `ScriptName`='at_dh_sigil_of_silence' WHERE  `Id`=6027;
UPDATE `areatrigger_create_properties` SET `ScriptName`='at_dh_sigil_of_flame' WHERE  `Id`=6039;
UPDATE `areatrigger_create_properties` SET `ScriptName`='at_dh_sigil_of_misery' WHERE  `Id`=6351;
UPDATE `areatrigger_create_properties` SET `ScriptName`='at_dh_sigil_of_chains' WHERE  `Id`=6031;