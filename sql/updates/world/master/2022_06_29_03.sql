
DELETE FROM spell_script_names WHERE spell_id = 335232;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (335232, 'spell_ashen_juggernaut');

UPDATE areatrigger_create_properties SET scriptname = 'at_field_of_blossoms' WHERE id = 21827;

DELETE FROM spell_script_names WHERE scriptname = 'spell_bladestorm';
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (227847, 'spell_bladestorm');
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (152277, 'spell_bladestorm');

DELETE FROM spell_script_names WHERE spell_id = 339386;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (339386, 'spell_mortal_combo');

