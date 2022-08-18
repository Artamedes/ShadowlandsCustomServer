-- wind proper fix
UPDATE creature_template SET scriptname = 'npc_wind_76152' WHERE entry = 76152;
DELETE FROM gameobject WHERE id = 238852;

UPDATE `creature` SET `position_x`='1010.0382', `position_y`='1924.0156', `position_z`='227.24365', `orientation`='2.544507026672363281' WHERE  `guid`=2693;

UPDATE areatrigger_create_properties SET scriptname = 'at_skyreach_wind_maze' WHERE areatriggerid IN (6313,
6316,
6444,
6319,
6447,
6450,
6453,
6712,
6315,
6443,
6318,
6446,
6452,
6308,
6449,
6711,
6314,
6442,
6093,
6317,
6445,
6448,
6451,
6454,
6710);