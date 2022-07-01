 
UPDATE creature_template set ScriptName = 'npc_void_orb_154074' WHERE entry = 154074;
 UPDATE creature_template set ScriptName = 'npc_hand_of_darkness_154990' WHERE entry = 154990;
 
 
DELETE FROM spell_script_names WHERE spell_id = 304804;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (304804, 'spell_spew_ichor');
UPDATE creature_template set ScriptName = 'npc_shirakess_apprentice_145333' WHERE entry = 145333;
UPDATE creature_template set ScriptName = 'npc_shirakess_voidreaver_152827' WHERE entry = 152827;
UPDATE creature_template set ScriptName = 'npc_shirakess_overseer_149004' WHERE entry = 149004;
UPDATE creature_template set ScriptName = 'npc_shirakess_subjugator_152724' WHERE entry = 152724;
UPDATE creature_template set ScriptName = 'npc_elder_mindbreaker_152744' WHERE entry = 152744;
UPDATE creature_template set ScriptName = 'npc_dark_witness_154992' WHERE entry = 154992;


DELETE FROM spell_script_names WHERE spell_id = 301644;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (301644, 'spell_void_power');
