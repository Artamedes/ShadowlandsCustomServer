-- paladin
DELETE FROM spell_script_names WHERE spell_id = 364304;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (364304, 'spell_glorious_purpose_2pc');

DELETE FROM spell_script_names WHERE spell_id = 363675;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (363675, 'spell_glorious_purpose_4pc');

DELETE FROM `spell_proc` WHERE `SpellId` IN (364304);
INSERT INTO `spell_proc` (`SpellId`,`SchoolMask`,`SpellFamilyName`,`SpellFamilyMask0`,`SpellFamilyMask1`,`SpellFamilyMask2`,`SpellFamilyMask3`,`ProcFlags`,`ProcFlags2`,`SpellTypeMask`,`SpellPhaseMask`,`HitMask`,`AttributesMask`,`DisableEffectsMask`,`ProcsPerMinute`,`Chance`,`Cooldown`,`Charges`) VALUES
(364304,0x00,10,0x00000000,0x00000000,0x00000000,0x00000000,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0,0,0,0); -- Glorious Purpose
