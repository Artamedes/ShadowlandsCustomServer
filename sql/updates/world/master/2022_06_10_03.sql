-- 
DELETE FROM `spell_script_names` WHERE `spell_id`=315508 AND `ScriptName`='spell_rog_roll_the_bones';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (315508, 'spell_rog_roll_the_bones');

DELETE FROM spell_script_names WHERE spell_id IN (199603,193358,193357,193359,199600,193356,208244);

DELETE FROM spell_script_names WHERE spell_id = 8676;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (8676, 'spell_ambush');

DELETE FROM spell_script_names WHERE spell_id = 2098;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (2098, 'spell_dispatch');
