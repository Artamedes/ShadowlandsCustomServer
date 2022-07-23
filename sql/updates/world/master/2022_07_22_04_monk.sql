
DELETE FROM disables WHERE entry = 115203;
DELETE FROM spell_script_names WHERE spell_id = 115203;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (115203, 'spell_fortifying_brew');
