-- world 6-16-22
REPLACE INTO spell_script_names VALUES (265259 , 'aura_pri_twist_of_fate_discipline');
DELETE FROM spell_script_names WHERE spell_id = 316958;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (316958, 'spell_ashen_hallow');
UPDATE areatrigger_create_properties SET scriptname = 'areatrigger_pal_ashen_hallow' WHERE id = 19042;

DELETE FROM spell_script_names WHERE spell_id = 336872;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (336872, 'spell_final_verdict');
DELETE FROM spell_script_names WHERE spell_id = 337228;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (337228, 'spell_final_verdict_proc');
DELETE FROM spell_script_names WHERE spell_id = 339374;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (339374, 'spell_truths_wake');


DELETE FROM spell_script_names WHERE spell_id = 339664;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (339664, 'spell_virtuous_command_proc');
DELETE FROM spell_script_names WHERE spell_id = 339518;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (339518, 'spell_virtuous_command');
DELETE FROM spell_script_names WHERE spell_id = 339531;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (339531, 'spell_templars_vindication');