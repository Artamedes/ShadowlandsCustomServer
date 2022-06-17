-- splls
REPLACE INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (257044, 'aura_hun_rapid_fire');

DELETE FROM spell_script_names WHERE spell_id = 260309;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (260309, 'spell_master_marksman');
