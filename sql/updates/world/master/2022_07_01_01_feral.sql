-- druid fixes
DELETE FROM `spell_script_names` WHERE `spell_id`=16974 AND `ScriptName`='aura_dru_predatory_swiftness';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (16974, 'aura_dru_predatory_swiftness');

DELETE FROM `spell_script_names` WHERE `spell_id`=69369 AND `ScriptName`='spell_dru_predatory_swiftness_aura';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (69369, 'spell_dru_predatory_swiftness_aura');
