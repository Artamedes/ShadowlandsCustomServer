-- monk fixes

DELETE FROM spell_script_names WHERE spell_id = 101546;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (101546, 'spell_spinning_crane_kick');
