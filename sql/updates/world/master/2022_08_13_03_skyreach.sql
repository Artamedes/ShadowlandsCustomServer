-- SKYREACH SCRIPTING
REPLACE INTO `instance_template` (`map`, `parent`, `script`) VALUES (1209, 0, 'instance_Skyreach');


UPDATE creature_template SET scriptname = 'npc_reshad_81273', vehicleid = 0 WHERE entry = 81273;
UPDATE creature_template SET scriptname = 'npc_dread_raven_81204', vehicleid = 3623 WHERE entry = 81204;

UPDATE `creature_template` SET `flags_extra`='128' WHERE  `entry`=76119;