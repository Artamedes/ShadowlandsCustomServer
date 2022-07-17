-- dk
DELETE FROM spell_script_names WHERE spell_id = 335177;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (335177, 'spell_phearomones');

DELETE FROM spell_script_names WHERE spell_id = 334501;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (334501, 'spell_bryndaors_might');


DELETE FROM spell_script_names WHERE scriptname = 'spell_dk_blodd_dancing_rune_weapon';

DELETE FROM spell_script_names WHERE spell_id = 334583;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (334583, 'spell_koltiras_favor');

DELETE FROM spell_script_names WHERE spell_id = 341724;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (341724, 'spell_rage_of_the_frozen_champion');

DELETE FROM spell_script_names WHERE spell_id = 334949;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (334949, 'spell_deadliest_coil');

DELETE FROM spell_script_names WHERE spell_id = 334898;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (334898, 'spell_deaths_certainty');


DELETE FROM spell_script_names WHERE spell_id = 334836;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (334836, 'spell_reanimated_shambler');

 UPDATE creature_template set ScriptName = 'npc_reanimated_shambling_horror_171587', minlevel = 60, maxlevel = 60 WHERE entry = 171587;

