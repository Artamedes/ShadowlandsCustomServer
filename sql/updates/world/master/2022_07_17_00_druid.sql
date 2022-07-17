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
