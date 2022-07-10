
DELETE FROM spell_script_names WHERE spell_id = 589;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (589, 'spell_shadow_word_pain');


DELETE FROM spell_script_names WHERE spell_id = 204213;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (204213, 'spell_purge_the_wicked');


DELETE FROM spell_script_names WHERE spell_id = 341804;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (341804, 'spell_measured_contemplation');

DELETE FROM spell_script_names WHERE spell_id = 341824;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (341824, 'spell_measured_contemplation_proc');


DELETE FROM spell_script_names WHERE spell_id = 10060;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (10060, 'spell_power_infusion');

DELETE FROM spell_script_names WHERE spell_id = 336067;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (336067, 'spell_clarity_of_mind');

DELETE FROM spell_script_names WHERE spell_id = 336011;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (336011, 'spell_the_penitent_one');
DELETE FROM spell_script_names WHERE spell_id = 336009;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (336009, 'spell_the_penitent_one_proc');

DELETE FROM spell_script_names WHERE spell_id = 336400;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (336400, 'spell_divine_image');

UPDATE creature_template SET scriptname = 'npc_invoke_the_naaru' WHERE entry = 172309;

DELETE FROM spell_script_names WHERE spell_id = 196705;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (196705, 'spell_divine_image_proc');
