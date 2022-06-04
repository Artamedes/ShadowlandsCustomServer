-- 

DELETE FROM spell_script_names WHERE spell_id = 319213;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (319213, 'spell_empowered_chrysalis');

DELETE FROM spell_script_names WHERE spell_id = 320267;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (320267, 'spell_soothing_voice');

DELETE FROM spell_script_names WHERE spell_id = 319191;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (319191, 'spell_field_of_blossoms');

DELETE FROM spell_script_names WHERE spell_id = 324701;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (324701, 'spell_flicker');

DELETE FROM spell_script_names WHERE spell_id = 325065;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (325065, 'spell_wild_hunts_charge');

DELETE FROM spell_script_names WHERE spell_id = 325072;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (325072, 'spell_vorkai_sharpening_techniques');

DELETE FROM spell_script_names WHERE spell_id = 325073;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (325073, 'spell_get_in_formation');

DELETE FROM spell_script_names WHERE spell_id = 325068;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (325068, 'spell_face_your_foes');

DELETE FROM spell_script_names WHERE spell_id = 325601;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (325601, 'spell_hold_the_line');

DELETE FROM spell_script_names WHERE spell_id = 352800;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (352800, 'spell_vorkai_ambush');

DELETE FROM spell_script_names WHERE spell_id = 325069;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (325069, 'spell_first_strike');


UPDATE areatrigger_create_properties SET scriptname = 'at_field_of_blossoms' WHERE id = 21827;