-- priest
DELETE FROM spell_script_names WHERE spell_id = 325013;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (325013, 'spell_boon_of_the_ascended');
DELETE FROM spell_script_names WHERE spell_id = 325283;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (325283, 'spell_ascended_blast');


DELETE FROM `spell_proc` WHERE `SpellId` IN (328266);
INSERT INTO `spell_proc` (`SpellId`,`SchoolMask`,`SpellFamilyName`,`SpellFamilyMask0`,`SpellFamilyMask1`,`SpellFamilyMask2`,`SpellFamilyMask3`,`ProcFlags`,`ProcFlags2`,`SpellTypeMask`,`SpellPhaseMask`,`HitMask`,`AttributesMask`,`DisableEffectsMask`,`ProcsPerMinute`,`Chance`,`Cooldown`,`Charges`) VALUES
(328266,0x00,0,0x00000000,0x00000000,0x00000000,0x00000000,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0,0,0,0); -- Combat Meditation
