-- runecarving
DELETE FROM `scene_template` WHERE `SceneId`=2597;
INSERT INTO `scene_template` (`SceneId`, `Flags`, `ScriptPackageID`, `Encrypted`) VALUES
(2597, 9, 3018, 0);

UPDATE creature_template set ScriptName = 'npc_runecarver_180509' WHERE entry = 180509;
