-- 
DELETE FROM spell_script_names WHERE spell_id = 3408;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (3408, 'spell_crippling_poison');

DELETE FROM spell_script_names WHERE spell_id = 315584;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (315584, 'spell_instant_poison');
REPLACE INTO spell_script_names (spell_id, scriptname) VALUE (282, 'spell_instant_poison');
