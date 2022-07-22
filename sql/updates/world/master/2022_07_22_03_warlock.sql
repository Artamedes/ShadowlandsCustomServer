-- warlock
REPLACE INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (118699, 'aura_warl_fear');

DELETE FROM spell_script_names WHERE spell_id = 339673;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (339673, 'spell_carnivorous_stalkers');

REPLACE INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (30146, 'spell_war_summon');
REPLACE INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (688, 'spell_war_summon');
REPLACE INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (697, 'spell_war_summon');
REPLACE INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (712, 'spell_war_summon');
REPLACE INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (691, 'spell_war_summon');

UPDATE creature_template SET scriptname = 'npc_warlock_pet_felguard' WHERE entry = 17252;