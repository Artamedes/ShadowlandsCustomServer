-- deeper daggers
DELETE FROM spell_script_names WHERE spell_id = 341549;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (341549, 'spell_deeper_daggers');
DELETE FROM spell_script_names WHERE spell_id = 319175;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (319175, 'spell_black_powder');
DELETE FROM spell_script_names WHERE spell_id = 340089;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (340089, 'spell_finality');

DELETE FROM spell_script_names WHERE spell_id = 340603;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (340603, 'spell_finality_black_powder');
DELETE FROM spell_script_names WHERE spell_id = 340600;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (340600, 'spell_finality_eviscerate');

DELETE FROM `spell_proc` WHERE `SpellId` IN (340600);
INSERT INTO `spell_proc` (`SpellId`,`SchoolMask`,`SpellFamilyName`,`SpellFamilyMask0`,`SpellFamilyMask1`,`SpellFamilyMask2`,`SpellFamilyMask3`,`ProcFlags`,`ProcFlags2`,`SpellTypeMask`,`SpellPhaseMask`,`HitMask`,`AttributesMask`,`DisableEffectsMask`,`ProcsPerMinute`,`Chance`,`Cooldown`,`Charges`) VALUES
(340600,0x01,8,0x00000000,0x00000000,0x00000000,0x00000000,0x11000,0x4,0x1,0x2,0x1,0x0,0x0,0,0,0,0); -- Finality: Eviscerate

DELETE FROM `spell_proc` WHERE `SpellId` IN (340603);
INSERT INTO `spell_proc` (`SpellId`,`SchoolMask`,`SpellFamilyName`,`SpellFamilyMask0`,`SpellFamilyMask1`,`SpellFamilyMask2`,`SpellFamilyMask3`,`ProcFlags`,`ProcFlags2`,`SpellTypeMask`,`SpellPhaseMask`,`HitMask`,`AttributesMask`,`DisableEffectsMask`,`ProcsPerMinute`,`Chance`,`Cooldown`,`Charges`) VALUES
(340603,0x01,8,0x00000000,0x00000000,0x00000000,0x00000000,0x11000,0x4,0x1,0x2,0x1,0x0,0x0,0,0,0,0); -- Finality: Black Powder
DELETE FROM spell_script_names WHERE spell_id = 340091;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (340091, 'spell_the_rotten');
DELETE FROM spell_script_names WHERE spell_id = 341134;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (341134, 'spell_the_rotten_proc');
