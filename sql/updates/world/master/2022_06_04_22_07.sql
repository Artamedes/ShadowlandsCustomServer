-- 
DELETE FROM spell_script_names WHERE spell_id = 350228;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (350228, 'spell_fleshcraft_consume');

DELETE FROM spell_script_names WHERE spell_id = 350229;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (350229, 'spell_fleshcraft_cdr');

DELETE FROM spell_script_names WHERE spell_id = 323510;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (323510, 'spell_volatile_solvent_undead');

DELETE FROM spell_script_names WHERE spell_id = 323074;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (323074, 'spell_volatile_solvent');

DELETE FROM spell_script_names WHERE spell_id = 323090;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (323090, 'spell_plagueys_preemptive_strike');

DELETE FROM spell_script_names WHERE spell_id = 352108;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (352108, 'spell_viscous_trail');

DELETE FROM spell_script_names WHERE spell_id = 352110;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (352110, 'spell_kevins_oozeling');

DELETE FROM spell_script_names WHERE spell_id = 352500;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (352500, 'spell_kevins_oozeling_proc');

DELETE FROM spell_script_names WHERE spell_id = 339894;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (339894, 'spell_elysian_decree');

DELETE FROM spell_script_names WHERE spell_id = 307046;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (307046, 'spell_elysian_decree_dmg');

UPDATE `areatrigger_create_properties` SET `ScriptName`='at_viscous_trail' WHERE  `Id`=22903;
UPDATE `areatrigger_create_properties` SET `ScriptName`='at_elysian_decree' WHERE  `Id`=18264;

UPDATE creature_template set ScriptName = 'npc_kevin_s_oozeling_178601' WHERE entry = 178601;