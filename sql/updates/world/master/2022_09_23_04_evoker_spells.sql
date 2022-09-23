DELETE FROM `areatrigger_template` WHERE `Id` IN (27633, 28714);
DELETE FROM `areatrigger_create_properties` WHERE `id` IN (23318, 24713);

INSERT INTO `areatrigger_template` (`Id`, `IsServerSide`, `Type`, `Flags`, `Data0`, `Data1`, `Data2`, `Data3`, `Data4`, `Data5`, `Data6`, `Data7`, `VerifiedBuild`) VALUES
(28714, FALSE, 0, 0, 8, 8, 0, 0, 0, 0, 0, 0, 45505),
(27633, FALSE, 0, 2, 3, 3, 0, 0, 0, 0, 0, 0, 45505);
INSERT INTO `areatrigger_create_properties` (`id`, `AreaTriggerId`, `MoveCurveId`, `ScaleCurveId`, `MorphCurveId`, `FacingCurveId`, `AnimId`, `AnimKitId`, `DecalPropertiesId`, `TimeToTarget`, `TimeToTargetScale`, `VerifiedBuild`) VALUES
(23318, 27633, 0, 0, 0, 0, -1, 0, 0, 2000, 0, 45505), -- SpellId : 355913 CANNOT FIND PROPERTIES ID, USED SPELL ID AS KEY (NEEDS MANUAL CORRECTION)
(24713, 28714, 0, 0, 0, 0, -1, 0, 0, 12000, 0, 45505); -- SpellId : 369372 CANNOT FIND PROPERTIES ID, USED SPELL ID AS KEY (NEEDS MANUAL CORRECTION)

-- UPDATE `areatrigger_template` SET `scriptname` = "aretrigger_emerald_blossom_27633" WHERE `id` = 27633;
-- UPDATE `areatrigger_template` SET `scriptname` = "aretrigger_firestorm_28714" WHERE `id` = 28714;

UPDATE `areatrigger_create_properties` SET `scriptname` = "aretrigger_emerald_blossom_27633" WHERE `AreaTriggerId` = 27633;
UPDATE `areatrigger_create_properties` SET `scriptname` = "aretrigger_firestorm_28714" WHERE `AreaTriggerId` = 28714;

DELETE FROM spell_script_names WHERE spell_id = 361469;
INSERT INTO spell_script_names(spell_id, scriptname) VALUE(361469, 'spell_living_flame');

DELETE FROM spell_script_names WHERE spell_id = 375088;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (375088, 'spell_dragonrage');

DELETE FROM spell_script_names WHERE spell_id = 357210;
INSERT INTO spell_script_names(spell_id, scriptname) VALUE(357210, 'spell_deep_breath');

DELETE FROM spell_script_names WHERE spell_id = 362010;
INSERT INTO spell_script_names(spell_id, scriptname) VALUE(362010, 'spell_deep_breath_flight');