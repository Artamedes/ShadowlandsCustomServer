-- move as one
DELETE FROM spell_script_names WHERE spell_id = 319982;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (319982, 'spell_move_as_one');
