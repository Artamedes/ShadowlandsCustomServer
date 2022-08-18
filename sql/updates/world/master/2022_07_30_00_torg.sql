-- next floor
UPDATE creature_template SET scriptname = 'npc_next_floor' WHERE entry = 156480;
DELETE FROM gameobject_template WHERE entry = 368373;
DELETE FROM gameobject WHERE id IN (SELECT entry FROM gameobject_template WHERE scriptname = 'go_plundered_anima');
UPDATE `creature_template` SET `minlevel`='60', `maxlevel`='60', `faction`='3218' WHERE  `entry`=183931;