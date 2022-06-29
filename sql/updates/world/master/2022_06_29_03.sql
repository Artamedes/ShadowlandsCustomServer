
DELETE FROM spell_script_names WHERE spell_id = 335232;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (335232, 'spell_ashen_juggernaut');

UPDATE areatrigger_create_properties SET scriptname = 'at_field_of_blossoms' WHERE id = 21827;

DELETE FROM spell_script_names WHERE spell_id = 227847;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (227847, 'spell_bladestorm');
