-- Druid fixes
DELETE FROM spell_script_names WHERE spell_id = 79577;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (79577, 'spell_eclipse');

DELETE FROM spell_script_names WHERE spell_id = 48518;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (48518, 'spell_eclipse_lunar');


DELETE FROM spell_script_names WHERE spell_id = 48517;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (48517, 'spell_eclipse_solar');
