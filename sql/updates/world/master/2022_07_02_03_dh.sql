DELETE FROM `spell_proc` WHERE `SpellId` IN (337504);
INSERT INTO `spell_proc` (`SpellId`,`SchoolMask`,`SpellFamilyName`,`SpellFamilyMask0`,`SpellFamilyMask1`,`SpellFamilyMask2`,`SpellFamilyMask3`,`ProcFlags`,`ProcFlags2`,`SpellTypeMask`,`SpellPhaseMask`,`HitMask`,`AttributesMask`,`DisableEffectsMask`,`ProcsPerMinute`,`Chance`,`Cooldown`,`Charges`) VALUES
(337504,0x00,107,0x00000000,0x00000000,0x00000000,0x00000000,0x0,0x4,0x0,0x1,0x0,0x0,0x0,0,0,0,0); -- Collective Anguish

DELETE FROM spell_script_names WHERE spell_id = 337504;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (337504, 'spell_collective_anguish');

DELETE FROM spell_script_names WHERE spell_id = 346504;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (346504, 'spell_eye_beam_collective_anguish');

DELETE FROM spell_script_names WHERE spell_id = 337551;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (337551, 'spell_chaos_theory');

DELETE FROM spell_script_names WHERE spell_id = 346279;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (346279, 'spell_burning_wound');
