-- dh legendaries
DELETE FROM spell_script_names WHERE spell_id = 337541;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (337541, 'spell_spirit_of_the_darkness_flame');

DELETE FROM spell_script_names WHERE spell_id = 337542;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (337542, 'spell_spirit_of_the_darkness_flame_proc');

DELETE FROM `spell_proc` WHERE `SpellId` IN (337542);
INSERT INTO `spell_proc` (`SpellId`,`SchoolMask`,`SpellFamilyName`,`SpellFamilyMask0`,`SpellFamilyMask1`,`SpellFamilyMask2`,`SpellFamilyMask3`,`ProcFlags`,`ProcFlags2`,`SpellTypeMask`,`SpellPhaseMask`,`HitMask`,`AttributesMask`,`DisableEffectsMask`,`ProcsPerMinute`,`Chance`,`Cooldown`,`Charges`) VALUES
(337542,0x00,107,0x00000000,0x00000000,0x00000000,0x00000000,0x10000,0x4,0x0,0x6,0x0,0x0,0x0,0,0,0,0); -- Spirit of the Darkness Flame

DELETE FROM spell_script_names WHERE spell_id = 337544;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (337544, 'spell_razelikhs_defilement');

DELETE FROM spell_script_names WHERE spell_id = 357888;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (357888, 'spell_condensed_anima_sphere');


DELETE FROM spell_script_names WHERE spell_id = 327365;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (327365, 'spell_disciplinary_command');

DELETE FROM spell_script_names WHERE spell_id = 327489;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (327489, 'spell_expanded_potential');

DELETE FROM spell_script_names WHERE spell_id = 333373;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (333373, 'spell_triune_ward');


DELETE FROM spell_script_names WHERE spell_id = 332769;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (332769, 'spell_arcane_harmony');


DELETE FROM spell_script_names WHERE spell_id = 333030;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (333030, 'spell_fevered_incantation');


DELETE FROM spell_script_names WHERE spell_id = 333097;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (333097, 'spell_firestorm');

DELETE FROM spell_script_names WHERE spell_id = 333182;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (333182, 'spell_molten_skyfall_proc');

DELETE FROM spell_script_names WHERE spell_id = 333167;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (333167, 'spell_molten_skyfall');


DELETE FROM spell_script_names WHERE spell_id = 327511;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (327511, 'spell_slick_ice');

DELETE FROM spell_script_names WHERE spell_id = 327330;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (327330, 'spell_cold_front_proc');

DELETE FROM spell_script_names WHERE spell_id = 327284;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (327284, 'spell_cold_front');


DELETE FROM spell_script_names WHERE spell_id = 327492;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (327492, 'spell_glacial_fragments');
