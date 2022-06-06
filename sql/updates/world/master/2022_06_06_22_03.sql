-- fix mortal dance pvp talent crash
DELETE FROM spell_script_names WHERE spell_id = 328725;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (328725, 'spell_mortal_dance');
