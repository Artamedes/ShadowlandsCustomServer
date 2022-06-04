-- 
DELETE FROM spell_script_names WHERE spell_id = 351488;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (351488, 'spell_spear_of_the_archon');

DELETE FROM spell_script_names WHERE spell_id = 329791;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (329791, 'spell_valiant_strikes');

DELETE FROM spell_script_names WHERE spell_id = 334066;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (334066, 'spell_mentorship');

DELETE FROM spell_script_names WHERE spell_id = 323436;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (323436, 'spell_purify_soul');

DELETE FROM spell_script_names WHERE spell_id = 329778;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (329778, 'spell_pointed_courage');

DELETE FROM spell_script_names WHERE spell_id = 329779;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (329779, 'spell_bearers_pursuit');

DELETE FROM spell_script_names WHERE spell_id = 329784;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (329784, 'spell_cleansing_rites');

DELETE FROM spell_script_names WHERE spell_id = 330921;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (330921, 'spell_cleansing_rites_aura');

DELETE FROM spell_script_names WHERE spell_id = 329781;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (329781, 'spell_resonant_accolades');

DELETE FROM spell_script_names WHERE spell_id = 333882;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (333882, 'spell_forgelite_filter');

DELETE FROM spell_script_names WHERE spell_id = 331611;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (331611, 'spell_soulsteel_clamps');

DELETE FROM spell_script_names WHERE spell_id = 333935;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (333935, 'spell_hammer_of_genesis');

DELETE FROM spell_script_names WHERE spell_id = 352186;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (352186, 'spell_soulglow_spectrometer');

DELETE FROM spell_script_names WHERE spell_id = 352187;
INSERT INTO spell_script_names(spell_id, scriptname) VALUE(352187, 'spell_reactive_retrofitting');

DELETE FROM spell_script_names WHERE spell_id = 329786;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (329786, 'spell_road_of_trials');

DELETE FROM spell_script_names WHERE spell_id = 328257;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (328257, 'spell_let_go_of_the_past');

DELETE FROM spell_script_names WHERE spell_id = 351146;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (351146, 'spell_better_together');

UPDATE quest_objectives SET Description='Use the Magic Stone and speak to Thrall' WHERE  ID=700007;
