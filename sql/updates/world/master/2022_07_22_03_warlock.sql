-- warlock
REPLACE INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (118699, 'aura_warl_fear');

DELETE FROM spell_script_names WHERE spell_id = 339673;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (339673, 'spell_carnivorous_stalkers');
