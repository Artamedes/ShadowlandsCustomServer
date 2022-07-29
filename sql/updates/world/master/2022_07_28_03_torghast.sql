DELETE FROM `creature_template_movement` WHERE `CreatureId`=156480;
INSERT INTO `creature_template_movement` (`CreatureId`, `Ground`, `Swim`, `Flight`, `Rooted`, `Chase`, `Random`, `InteractionPauseTimer`) VALUES (156480, 0, 0, 1, 0, 0, 0, 0);


UPDATE instance_template SET script = 'instance_old_torghast' WHERE map = 10001;
DELETE FROM `instance_template` WHERE `map`=2162;
INSERT INTO `instance_template` (`map`, `parent`, `script`) VALUES (2162, 0, 'instance_torghast');

DELETE FROM `world_state` WHERE `ID`=19143;
INSERT INTO `world_state` (`ID`, `DefaultValue`, `MapIDs`, `AreaIDs`, `ScriptName`, `Comment`) VALUES (19143, 2, '2162', NULL, '', 'Torghast Next Floor');
DELETE FROM `world_state` WHERE `ID`=19812;
INSERT INTO `world_state` (`ID`, `DefaultValue`, `MapIDs`, `AreaIDs`, `ScriptName`, `Comment`) VALUES (19812, 1, '2162', NULL, '', 'Torghast Current Floor');
