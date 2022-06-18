-- splls
REPLACE INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (257044, 'aura_hun_rapid_fire');

DELETE FROM spell_script_names WHERE spell_id = 260309;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (260309, 'spell_master_marksman');

REPLACE INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (201453, 'aura_dh_metamorphosis_immunity');
REPLACE INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (204598, 'aura_dh_vengeance_sigil_of_flame');

DELETE FROM spell_script_names WHERE spell_id = 189111;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (189111, 'spell_infernal_strike_jump');

UPDATE areatrigger_create_properties SET scriptname = 'at_glaive_tempest' WHERE id = 21832;
