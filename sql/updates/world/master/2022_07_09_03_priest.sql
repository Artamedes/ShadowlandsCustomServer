-- priest legends
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

DELETE FROM spell_script_names WHERE spell_id = 336266;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (336266, 'spell_flash_concentration');

DELETE FROM spell_script_names WHERE spell_id = 204883;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (204883, 'spell_circle_of_healing');

DELETE FROM spell_script_names WHERE spell_id = 27795;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (27795, 'spell_spirit_of_redemption_spirit');

DELETE FROM spell_script_names WHERE spell_id = 336214;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (336214, 'spell_eternal_call_to_the_void');

UPDATE creature_template set ScriptName = 'npc_void_lasher_175198' WHERE entry = 175198;

DELETE FROM spell_script_names WHERE spell_id = 335467;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (335467, 'spell_devouring_plague');


DELETE FROM spell_script_names WHERE spell_id = 342415;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (342415, 'spell_talbadars_stratagem');
