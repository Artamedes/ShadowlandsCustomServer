-- monk fixes
REPLACE INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (8647, 'aura_monk_mystic_touch');
REPLACE INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (116092, 'aura_monk_afterlife');

UPDATE `areatrigger_create_properties` SET `ScriptName`='at_monk_chi_sphere' WHERE  `Id`=2442;
UPDATE `areatrigger_create_properties` SET `ScriptName`='at_monk_heal_sphere' WHERE  `Id`=3319;

REPLACE INTO `areatrigger_create_properties` (`Id`, `AreaTriggerId`, `MoveCurveId`, `ScaleCurveId`, `MorphCurveId`, `FacingCurveId`, `AnimId`, `AnimKitId`, `DecalPropertiesId`, `TimeToTarget`, `TimeToTargetScale`, `Shape`, `ShapeData0`, `ShapeData1`, `ShapeData2`, `ShapeData3`, `ShapeData4`, `ShapeData5`, `ScriptName`, `TimeToTargetExtraScale`, `VerifiedBuild`) VALUES (2763, 2763, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 10, 0, 0, 0, 0, 'at_monk_windwalking', 0, 27481);
REPLACE INTO `areatrigger_template` (`Id`, `Type`, `Flags`, `Data0`, `Data1`, `Data2`, `Data3`, `Data4`, `Data5`, `ScriptName`, `VerifiedBuild`) VALUES (2763, 0, 4, 10, 10, 0, 0, 0, 0, 'at_monk_windwalking', 22810);


UPDATE `areatrigger_create_properties` SET `ScriptName`='at_monk_chi_burst_damage' WHERE  `Id`=1315;
UPDATE `areatrigger_create_properties` SET `ScriptName`='at_monk_chi_burst_heal' WHERE  `Id`=1316;

DELETE FROM spell_script_names WHERE scriptname = 'spell_monk_energizing_brew';
REPLACE INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (101643, 'aura_monk_transcendence');
