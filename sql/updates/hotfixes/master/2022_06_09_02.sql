-- primal wrath
DELETE FROM spell_script_names WHERE spell_id = 285381;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (285381, 'spell_primal_wrath');

UPDATE areatrigger_create_properties SET scriptname = 'at_warl_rain_of_fire' WHERE id = 5420;

UPDATE `spell_script_names` SET `spell_id`='285452 ' WHERE  `spell_id`=51505 AND `ScriptName`='spell_sha_lava_burst';