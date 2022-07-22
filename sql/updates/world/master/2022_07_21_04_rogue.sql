-- rogue
DELETE FROM spell_script_names WHERE scriptname = 'spell_rog_sepsis_attack';

DELETE FROM spell_script_names WHERE spell_id = 347037;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (347037, 'spell_sepsis_proc');
