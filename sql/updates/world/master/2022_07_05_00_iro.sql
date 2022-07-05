DELETE FROM spell_script_names WHERE spell_id = 357888;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (357888, 'spell_condensed_anima_sphere');
DELETE FROM spell_script_names WHERE spell_id = 336777;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (336777, 'spell_grounding_surge');
DELETE FROM spell_script_names WHERE spell_id = 337240;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (337240, 'spell_artifice_of_the_archmage');
DELETE FROM `spell_proc` WHERE `SpellId` IN (337275);
INSERT INTO `spell_proc` (`SpellId`,`SchoolMask`,`SpellFamilyName`,`SpellFamilyMask0`,`SpellFamilyMask1`,`SpellFamilyMask2`,`SpellFamilyMask3`,`ProcFlags`,`ProcFlags2`,`SpellTypeMask`,`SpellPhaseMask`,`HitMask`,`AttributesMask`,`DisableEffectsMask`,`ProcsPerMinute`,`Chance`,`Cooldown`,`Charges`) VALUES
(337275,0x00,3,0x00000000,0x00000000,0x00000000,0x00000000,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0,0,0,0); -- Incantation of Swiftness
