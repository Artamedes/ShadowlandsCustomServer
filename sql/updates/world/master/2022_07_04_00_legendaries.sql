-- dh legendaries
DELETE FROM spell_script_names WHERE spell_id = 337541;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (337541, 'spell_spirit_of_the_darkness_flame');

DELETE FROM spell_script_names WHERE spell_id = 337542;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (337542, 'spell_spirit_of_the_darkness_flame_proc');

DELETE FROM `spell_proc` WHERE `SpellId` IN (337542);
INSERT INTO `spell_proc` (`SpellId`,`SchoolMask`,`SpellFamilyName`,`SpellFamilyMask0`,`SpellFamilyMask1`,`SpellFamilyMask2`,`SpellFamilyMask3`,`ProcFlags`,`ProcFlags2`,`SpellTypeMask`,`SpellPhaseMask`,`HitMask`,`AttributesMask`,`DisableEffectsMask`,`ProcsPerMinute`,`Chance`,`Cooldown`,`Charges`) VALUES
(337542,0x00,107,0x00000000,0x00000000,0x00000000,0x00000000,0x10000,0x4,0x0,0x6,0x0,0x0,0x0,0,0,0,0); -- Spirit of the Darkness Flame
