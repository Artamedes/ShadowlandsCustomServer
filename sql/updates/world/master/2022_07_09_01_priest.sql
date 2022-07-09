-- priest
DELETE FROM spell_script_names WHERE spell_id = 325013;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (325013, 'spell_boon_of_the_ascended');
DELETE FROM spell_script_names WHERE spell_id = 325283;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (325283, 'spell_ascended_blast');
