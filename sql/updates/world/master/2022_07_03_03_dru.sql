
DELETE FROM spell_script_names WHERE spell_id = 323546;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (323546, 'spell_ravenous_frenzy');
DELETE FROM `spell_proc` WHERE `SpellId` IN (323546);
INSERT INTO `spell_proc` (`SpellId`,`SchoolMask`,`SpellFamilyName`,`SpellFamilyMask0`,`SpellFamilyMask1`,`SpellFamilyMask2`,`SpellFamilyMask3`,`ProcFlags`,`ProcFlags2`,`SpellTypeMask`,`SpellPhaseMask`,`HitMask`,`AttributesMask`,`DisableEffectsMask`,`ProcsPerMinute`,`Chance`,`Cooldown`,`Charges`) VALUES
(323546,0x00,7,0x00000000,0x00000000,0x00000000,0x00000000,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0,0,0,0); -- Ravenous Frenzy (Venthyr)


DELETE FROM `areatrigger_template` WHERE (`Id`=11393 AND `IsServerSide`=0);
INSERT INTO `areatrigger_template` (`Id`, `IsServerSide`, `Type`, `Flags`, `Data0`, `Data1`, `Data2`, `Data3`, `Data4`, `Data5`, `VerifiedBuild`) VALUES
(11393, 0, 4, 16, 8, 8, 15, 15, -3, -3, 44325);


DELETE FROM `areatrigger_create_properties` WHERE `Id`=6887;
INSERT INTO `areatrigger_create_properties` (`Id`, `AreaTriggerId`, `MoveCurveId`, `ScaleCurveId`, `MorphCurveId`, `FacingCurveId`, `AnimId`, `AnimKitId`, `DecalPropertiesId`, `TimeToTarget`, `TimeToTargetScale`, `Shape`, `ShapeData0`, `ShapeData1`, `ShapeData2`, `ShapeData3`, `ShapeData4`, `ShapeData5`, `ShapeData6`, `ShapeData7`, `VerifiedBuild`) VALUES
(6887, 11393, 0, 0, 0, 0, -1, 0, 0, 179, 8000, 4, 8, 8, 15, 15, -3, -3, 0, 0, 44325); -- SpellId : 202770


DELETE FROM `areatrigger_create_properties_spline_point` WHERE (`AreaTriggerCreatePropertiesId`=6887 AND `Idx` IN (3,2,1,0));
INSERT INTO `areatrigger_create_properties_spline_point` (`AreaTriggerCreatePropertiesId`, `Idx`, `X`, `Y`, `Z`, `VerifiedBuild`) VALUES
(6887, 3, 1.250033974647521972, -0.00000046982538037, 0, 44325), -- SpellId : 202770
(6887, 2, 1.250033974647521972, -0.00000046982538037, 0, 44325), -- SpellId : 202770
(6887, 1, -0, -0, 0, 44325), -- SpellId : 202770
(6887, 0, -0, -0, 0, 44325); -- SpellId : 202770

UPDATE `areatrigger_create_properties` SET `ScriptName`='at_dru_fury_of_elune' WHERE  `Id`=6887;