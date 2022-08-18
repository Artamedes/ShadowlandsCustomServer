
DELETE FROM spell_script_names WHERE spell_id = 295040;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (295040, 'spell_next_floor');

UPDATE creature_template SET faction = 3218 WHERE entry IN (183985, 183988);


DELETE FROM spell_script_names WHERE spell_id = 311180;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (311180, 'spell_defender_of_torghast');

REPLACE INTO `world_state` (`ID`, `DefaultValue`, `MapIDs`, `AreaIDs`, `ScriptName`, `Comment`) VALUES (19143, 2, '2162', NULL, '', 'Torghast Next Floor');
REPLACE INTO `world_state` (`ID`, `DefaultValue`, `MapIDs`, `AreaIDs`, `ScriptName`, `Comment`) VALUES (19812, 1, '2162', NULL, '', 'Torghast Current Floor');
REPLACE INTO `world_state` (`ID`, `DefaultValue`, `MapIDs`, `AreaIDs`, `ScriptName`, `Comment`) VALUES (20700, 0, '2162', NULL, '', 'Torghast, Tower of the Damned - Test Chest - Encounter completed');
REPLACE INTO `world_state` (`ID`, `DefaultValue`, `MapIDs`, `AreaIDs`, `ScriptName`, `Comment`) VALUES (19811, 1, '2162', NULL, '', 'Torghast Level');
REPLACE INTO `world_state` (`ID`, `DefaultValue`, `MapIDs`, `AreaIDs`, `ScriptName`, `Comment`) VALUES (19207, 1, '2162', NULL, '', 'Torghast Type');

