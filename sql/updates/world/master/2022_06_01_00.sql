-- 

UPDATE `areatrigger_create_properties` SET `ScriptName`='at_soothing_shade' WHERE  `Id`=21260;

DELETE FROM `spell_script_names` WHERE `spell_id`=336245 AND `ScriptName`='spell_token_of_appreciation';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (336245, 'spell_token_of_appreciation');
DELETE FROM `spell_script_names` WHERE `spell_id`=319983 AND `ScriptName`='spell_wasteland_propriety';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (319983, 'spell_wasteland_propriety');
DELETE FROM `spell_script_names` WHERE `spell_id`=351750 AND `ScriptName`='spell_party_favors';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (351750, 'spell_party_favors');
DELETE FROM `spell_script_names` WHERE `spell_id`=359040 AND `ScriptName`='spell_party_favors_item';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (359040, 'spell_party_favors_item');

DELETE FROM `spell_script_names` WHERE `spell_id`=319973 AND `ScriptName`='spell_built_for_war';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (319973, 'spell_built_for_war');

