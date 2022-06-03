-- 
DELETE FROM `spell_script_names` WHERE `spell_id`=352188  AND `ScriptName`='spell_kyrian_effusive_anima_accelerator_aura';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (352188 , 'spell_kyrian_effusive_anima_accelerator_aura');
DELETE FROM `spell_script_names` WHERE `spell_id`=333950  AND `ScriptName`='spell_brons_call_to_action';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (333950 , 'spell_brons_call_to_action');
DELETE FROM `spell_script_names` WHERE `spell_id`=328908;
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (328908 , 'spell_combat_meditation_buff');
DELETE FROM `spell_script_names` WHERE `spell_id`=328266;
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (328266 , 'spell_combat_meditation');
DELETE FROM `spell_script_names` WHERE `spell_id`=351149;
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (351149 , 'spell_newfound_resolve');

UPDATE creature_template SET scriptname = 'npc_kyrian_goliath' WHERE entry = 171396;

UPDATE areatrigger_create_properties SET scriptname = 'areatrigger_combat_meditation' WHERE id = 20456;
UPDATE areatrigger_create_properties SET scriptname = 'areatrigger_newfound_resolve' WHERE id = 23044;