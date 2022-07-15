-- sham fixes
DELETE FROM spell_script_names WHERE spell_id = 336738;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (336738, 'spell_deeply_rooted_elements');

DELETE FROM spell_script_names WHERE spell_id = 336215;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (336215, 'spell_echoes_of_great_sundering');

DELETE FROM spell_script_names WHERE spell_id = 336734;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (336734, 'spell_skybreakers_fiery_demise');
