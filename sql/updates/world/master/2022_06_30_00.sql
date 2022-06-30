-- fixes
DELETE FROM spell_script_names WHERE spell_id = 364470;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (364470, 'spell_heal_the_soul_proc');
DELETE FROM spell_script_names WHERE spell_id = 366779;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (366779, 'spell_heal_the_soul');
