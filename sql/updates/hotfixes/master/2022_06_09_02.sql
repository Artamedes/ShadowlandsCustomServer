-- primal wrath
DELETE FROM spell_script_names WHERE spell_id = 285381;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (285381, 'spell_primal_wrath');

UPDATE areatrigger_create_properties SET scriptname = 'at_warl_rain_of_fire' WHERE id = 5420;

UPDATE `spell_script_names` SET `spell_id`='285452 ' WHERE  `spell_id`=51505 AND `ScriptName`='spell_sha_lava_burst';

UPDATE areatrigger_create_properties SET scriptname = 'at_sha_earthquake_totem' WHERE id = 3691;

DELETE FROM `spell_script_names` WHERE `spell_id`=61882 AND `ScriptName`='aura_sha_earthquake';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (61882, 'aura_sha_earthquake');

DELETE FROM spell_script_names WHERE spell_id = 324143;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (324143, 'spell_conquerors_banner');
