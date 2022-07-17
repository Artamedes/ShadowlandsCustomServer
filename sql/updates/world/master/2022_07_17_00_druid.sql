-- Druid fixes
DELETE FROM spell_script_names WHERE spell_id = 79577;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (79577, 'spell_eclipse');

DELETE FROM spell_script_names WHERE spell_id = 48518;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (48518, 'spell_eclipse_lunar');


DELETE FROM spell_script_names WHERE spell_id = 48517;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (48517, 'spell_eclipse_solar');

DELETE FROM spell_script_names WHERE scriptname = 'spell_balance_of_all_things';
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (339943, 'spell_balance_of_all_things');
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (339946, 'spell_balance_of_all_things');


DELETE FROM spell_script_names WHERE spell_id = 339800;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (339800, 'spell_oneths_perception');

DELETE FROM spell_script_names WHERE spell_id = 338661;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (338661, 'spell_oneths_clear_vision');

DELETE FROM spell_script_names WHERE spell_id = 339797;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (339797, 'spell_oneths_clear_vision_proc');

DELETE FROM spell_script_names WHERE spell_id = 338668;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (338668, 'spell_primordial_arcanic_pulsar');

DELETE FROM spell_script_names WHERE spell_id = 339949;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (339949, 'spell_timeworn_dreambinder');

DELETE FROM spell_script_names WHERE spell_id = 339139;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (339139, 'spell_apex_predators_craving');

DELETE FROM spell_script_names WHERE spell_id = 339140;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (339140, 'spell_apex_predators_craving_proc');

DELETE FROM spell_script_names WHERE spell_id = 339144;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (339144, 'spell_cat_eye_curio');

DELETE FROM creature WHERE guid = 1071506;
DELETE FROM creature_addon where guid = 1071506;

DELETE FROM spell_script_names WHERE spell_id = 339142;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (339142, 'spell_eye_of_fearful_symmetry_proc');

DELETE FROM spell_script_names WHERE spell_id = 339141;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (339141, 'spell_eye_of_fearful_symmetry');

DELETE FROM spell_script_names WHERE spell_id = 340053;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (340053, 'spell_frenzyband');

REPLACE INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (22812, 'aura_dru_barkskin');
REPLACE INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (363496, 'spell_architects_aligner');

DELETE FROM spell_script_names WHERE spell_id = 339056;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (339056, 'spell_ursocs_fury_remembered');


REPLACE INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (33763, 'aura_dru_lifebloom');
REPLACE INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (188550, 'aura_dru_lifebloom');

DELETE FROM spell_script_names WHERE spell_id = 364365;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (364365, 'spell_renewing_bloom');
