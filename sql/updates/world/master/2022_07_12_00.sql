-- invokers delight

DELETE FROM spell_script_names WHERE spell_id = 337298;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (337298, 'spell_invokers_delight');

DELETE FROM spell_script_names WHERE spell_id = 338140;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (338140, 'spell_charred_passions_proc');

DELETE FROM spell_script_names WHERE spell_id = 338138;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (338138, 'spell_charred_passions');

DELETE FROM spell_script_names WHERE spell_id = 337225;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (337225, 'spell_yulons_whisper');

DELETE FROM spell_script_names WHERE spell_id = 337483;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (337483, 'spell_jade_ignition');

DELETE FROM spell_script_names WHERE spell_id = 337292;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (337292, 'spell_last_emperors_capacitor');

DELETE FROM spell_script_names WHERE spell_id = 337481;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (337481, 'spell_xuens_battlegear');

REPLACE INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (113656, 'aura_monk_fists_of_fury');
