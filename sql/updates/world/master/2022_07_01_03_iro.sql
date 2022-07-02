DELETE FROM spell_script_names WHERE spell_id = 338089;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (338089, 'spell_fleeting_wind');
DELETE FROM `spell_proc` WHERE `SpellId` IN (338089);
INSERT INTO `spell_proc` (`SpellId`,`SchoolMask`,`SpellFamilyName`,`SpellFamilyMask0`,`SpellFamilyMask1`,`SpellFamilyMask2`,`SpellFamilyMask3`,`ProcFlags`,`ProcFlags2`,`SpellTypeMask`,`SpellPhaseMask`,`HitMask`,`AttributesMask`,`DisableEffectsMask`,`ProcsPerMinute`,`Chance`,`Cooldown`,`Charges`) VALUES
(338089,0x00,15,0x00000000,0x00000000,0x00000000,0x00000000,0x0,0x4,0x0,0x1,0x0,0x0,0x0,0,0,0,0); -- Fleeting Wind
