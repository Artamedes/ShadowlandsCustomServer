-- more rogue fixes
DELETE FROM spell_script_names WHERE spell_id = 193315;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (193315, 'spell_sinister_strike');

DELETE FROM spell_script_names WHERE spell_id = 195627;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (195627, 'spell_opportunity');

DELETE FROM `spell_proc` WHERE `SpellId` IN (195627);
INSERT INTO `spell_proc` (`SpellId`,`SchoolMask`,`SpellFamilyName`,`SpellFamilyMask0`,`SpellFamilyMask1`,`SpellFamilyMask2`,`SpellFamilyMask3`,`ProcFlags`,`ProcFlags2`,`SpellTypeMask`,`SpellPhaseMask`,`HitMask`,`AttributesMask`,`DisableEffectsMask`,`ProcsPerMinute`,`Chance`,`Cooldown`,`Charges`) VALUES
(195627,0x00,8,0x00000000,0x00000000,0x00000000,0x00000000,0x10000,0x0,0x0,0x0,0x0,0x0,0x0,0,101,0,0); -- Opportunity

