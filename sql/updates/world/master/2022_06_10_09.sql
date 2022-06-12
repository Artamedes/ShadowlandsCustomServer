-- desmoration BEGHIN
REPLACE INTO spell_script_names (spell_id, scriptname) VALUE (357640, 'spell_fiery_phlegm');
REPLACE INTO spell_script_names (spell_id, scriptname) VALUE (357643, 'spell_dark_discharge');
REPLACE INTO spell_script_names (spell_id, scriptname) VALUE (357644, 'spell_salty_spittle');
REPLACE INTO spell_script_names (spell_id, scriptname) VALUE (357181, 'spell_blazing_inferno');
UPDATE areatrigger_create_properties SET scriptname = 'at_fiery_phlegm' WHERE id = 23499;
UPDATE areatrigger_create_properties SET scriptname = 'at_dark_discharge' WHERE id = 23500;
UPDATE areatrigger_create_properties SET scriptname = 'at_salty_spittle' WHERE id = 23501;
UPDATE areatrigger_create_properties SET scriptname = 'at_defiling_dreadslam' WHERE id = 23468;
UPDATE areatrigger_create_properties SET scriptname = 'at_death_orb' WHERE id = 16766;

DELETE FROM spell_script_names WHERE spell_id = 297025;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (297025, 'spell_soul_echo');
DELETE FROM spell_script_names WHERE spell_id = 354240;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (354240, 'spell_ritual_of_slaughter');
DELETE FROM spell_script_names WHERE spell_id = 297111;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (297111, 'spell_death_orb');
DELETE FROM spell_script_names WHERE spell_id = 357329;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (357329, 'spell_soulflame_torrent');
UPDATE creature_template set ScriptName = 'npc_general_nephmir_707000' WHERE entry = 707000;

