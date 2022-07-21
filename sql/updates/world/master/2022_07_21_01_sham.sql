DELETE FROM spell_script_names WHERE spell_id = 327162;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (327162, 'spell_primordial_wave_327162');

DELETE FROM spell_script_names WHERE spell_id = 327161;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (327161, 'spell_primordial_wave');

DELETE FROM spell_script_names WHERE spell_id = 327163;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (327163, 'spell_primordial_wave_327163');

DELETE FROM spell_script_names WHERE spell_id = 327164;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (327164, 'spell_primordial_wave_327164');

DELETE FROM `spell_proc` WHERE `SpellId` IN (327164);
INSERT INTO `spell_proc` (`SpellId`,`SchoolMask`,`SpellFamilyName`,`SpellFamilyMask0`,`SpellFamilyMask1`,`SpellFamilyMask2`,`SpellFamilyMask3`,`ProcFlags`,`ProcFlags2`,`SpellTypeMask`,`SpellPhaseMask`,`HitMask`,`AttributesMask`,`DisableEffectsMask`,`ProcsPerMinute`,`Chance`,`Cooldown`,`Charges`) VALUES
(327164,0x00,11,0x00000000,0x00000000,0x00000000,0x00000000,0x0,0x4,0x0,0x2,0x0,0x0,0x0,0,100,0,0); -- Primordial Wave (Necrolord)
