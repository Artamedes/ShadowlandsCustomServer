DELETE FROM `spell_target_position` WHERE `ID`=370111 AND `EffectIndex`=0;
INSERT INTO `spell_target_position` (`ID`, `EffectIndex`, `MapID`, `PositionX`, `PositionY`, `PositionZ`, `VerifiedBuild`) VALUES (370111, 0, 2570, 5818.53, -3054.56, 251.28, 0);

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` IN (187223);
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`, `user_type`) VALUES
(187223, 362355, 1, 1);

DELETE FROM `waypoints` WHERE `entry`=18722300;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `orientation`, `delay`, `point_comment`) VALUES (18722300, 1, 5801.85, -3036.9, 253.012, NULL, 0, 'Kodethi glide down');
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `orientation`, `delay`, `point_comment`) VALUES (18722300, 2, 5793.58, -3028.15, 242.641, NULL, 0, 'Kodethi glide down');
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `orientation`, `delay`, `point_comment`) VALUES (18722300, 3, 5781.06, -3016.72, 216.401, NULL, 0, 'Kodethi glide down');

UPDATE `conversation_actors` SET `CreatureId` = 187223 WHERE `ConversationId` = 18934 AND `Idx` = 1;

DELETE FROM `waypoints` WHERE `entry`=18722301;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (18722301 , 1, 5787.45, -3019.071, 210.44612, "Auto generated Tal Wp");
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (18722301 , 2, 5799.463, -2989.1719, 210.70503, "Auto generated Tal Wp");
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (18722301 , 3, 5814.3926, -2955.1562, 205.11745, "Auto generated Tal Wp");
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (18722301 , 4, 5818.5913, -2931.507, 205.09546, "Auto generated Tal Wp");
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (18722301 , 5, 5812.876, -2922.6511, 207.2366, "Auto generated Tal Wp");
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (18722301 , 6, 5814.37, -2914.19, 207.25298, "Auto generated Tal Wp");
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (18722301 , 7, 5815.007, -2915.8074, 207.30219, "Auto generated Tal Wp");

DELETE FROM `spell_target_position` WHERE `ID`=369744 AND `EffectIndex`=0;
INSERT INTO `spell_target_position` (`ID`, `EffectIndex`, `MapID`, `PositionX`, `PositionY`, `PositionZ`, `VerifiedBuild`) VALUES (369744, 0, 2570, 5819, -3055, 251, 0);

DELETE FROM spell_script_names WHERE spell_id = 369772;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (369772, 'spell_the_war_creche_upper_floor');
DELETE FROM spell_script_names WHERE spell_id = 370111;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (370111, 'spell_summon_kodethi_370111');
DELETE FROM spell_script_names WHERE spell_id = 389778;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (389778, 'spell_stasis_389778');

UPDATE quest_template SET `flags` = 40370184 WHERE `id` = 64864; -- before 39845896

DELETE FROM `quest_template_addon` WHERE `ID`=64864;
INSERT INTO `quest_template_addon` (`ID`, `MaxLevel`, `AllowableClasses`, `SourceSpellID`, `PrevQuestID`, `NextQuestID`, `ExclusiveGroup`, `BreadcrumbForQuestId`, `RewardMailTemplateID`, `RewardMailDelay`, `RequiredSkillID`, `RequiredSkillPoints`, `RequiredMinRepFaction`, `RequiredMaxRepFaction`, `RequiredMinRepValue`, `RequiredMaxRepValue`, `ProvidedItemCount`, `SpecialFlags`, `ScriptName`) VALUES (64864, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'quest_awkaken_dracthyr');

UPDATE `creature_template` SET `npcflag` = 16777216 WHERE `entry` = 181680;

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = 181680;
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`, `user_type`) VALUES
(181680, 362355, 1, 0);
DELETE FROM `conditions` WHERE (`SourceTypeOrReferenceId` = 18) AND (`SourceGroup` IN (181680));
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `Comment`) VALUES
(18, 181680, 362355, 0, 0, 48, 0, 423680, 0, 1, 1, 'Clicker hasn\'t quest objective 423680 < 1 or has rewarded the quest');

DELETE FROM `waypoints` WHERE `entry` = 18686400;
SET @Entry := 18686400;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 1, 5799.463, -2989.1719, 210.70503, "Auto generated Tal Wp");
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 2, 5807.7725, -2970.2239, 210.9907, "Auto generated Tal Wp");
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 3, 5814.3926, -2955.1562, 205.11745, "Auto generated Tal Wp");
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 4, 5818.5913, -2931.507, 205.09546, "Auto generated Tal Wp");
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 5, 5814.3613, -2921.809, 207.2366, "Auto generated Tal Wp");
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 6, 5805.21, -2921.18, 207.25299, "Auto generated Tal Wp");
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 7, 5803.7197, -2921.448, 207.25299, "Auto generated Tal Wp");

-- UPDATE `creature` SET `phaseid` =  WHERE `id` = 186946; kodethi
DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = 183380;
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`, `user_type`) VALUES
(183380, 362355, 1, 0);

UPDATE `creature_template` SET `npcflag` = 2 WHERE `entry` = 181056;

DELETE FROM `spell_script_names` WHERE `spell_id`=370064;
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (370064, 'spell_lapisagos_intro_teleport_370064');

DELETE FROM `spell_script_names` WHERE `spell_id`=370046;
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (370046, 'spell_lapisagos_intro_scene_370046');

SET @Entry := 18269600;
DELETE FROM `waypoints` WHERE `entry` = @Entry;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 1, 6021.5366, -3085.5886, 200.50485, "Auto generated Wp");
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 2, 6019.4243, -3082.6423, 204.3541, "Auto generated Wp");
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 3, 6041.989, -3067.9653, 193.2191, "Auto generated Wp");
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 4, 6029.4443, -3038.9463, 163.5376, "Auto generated Wp");
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 5, 6062.146, -3050.9358, 160.85034, "Auto generated Wp");
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 6, 6062.897, -3071.0278, 155.25246, "Auto generated Wp");
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 7, 6062.8613, -3073.3923, 156.4561, "Auto generated Wp");

SET @Entry := 18159700;
DELETE FROM `waypoints` WHERE `entry` = @Entry;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 1, 6022.1206, -3087.8315, 200.50189, "Auto generated Wp");
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 2, 6026.9194, -3084.5747, 204.3541, "Auto generated Wp");
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 3, 6038.3403, -3089.0886, 193.2191, "Auto generated Wp");
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 4, 6078.5054, -3084.4739, 163.5376, "Auto generated Wp");
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 5, 6061.1113, -3061.6667, 160.85034, "Auto generated Wp");
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 6, 6058.0225, -3074.1511, 155.25246, "Auto generated Wp");

SET @Entry := 18688300;
DELETE FROM `waypoints` WHERE `entry` = @Entry;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 1, 6141.46, -3231.0156, 133.24654, "Auto generated Wp");
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 2, 6131.06, -3235.4, 134.11908, "Auto generated Wp");
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 3, 6135.71, -3233.7239, 133.46577, "Auto generated Wp");
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 4, 6135.71, -3233.7239, 133.46577, "Auto generated Wp");

SET @Entry := 18105300;
DELETE FROM `waypoints` WHERE `entry` = @Entry;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 1, 6141.46, -3231.0156, 133.24654, "Auto generated Wp");
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 2, 6131.06, -3235.4, 134.11908, "Auto generated Wp");
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 3, 6136.1787, -3236.8508, 133.47145, "Auto generated Wp");
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 4, 6136.1787, -3236.8508, 133.47145, "Auto generated Wp");

SET @Entry := 18216800;
DELETE FROM `waypoints` WHERE `entry` = @Entry;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 1, 6141.46, -3231.0156, 133.24654, "Auto generated Wp");
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 2, 6132.23, -3228.9, 133.201, "Auto generated Wp");
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 3, 6136.9585, -3230.1128, 133.4561, "Auto generated Wp");
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 4, 6136.9585, -3230.1128, 133.4561, "Auto generated Wp");

SET @Entry := 18396000;
DELETE FROM `waypoints` WHERE `entry` = @Entry;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 1, 6141.46, -3231.0156, 133.24654, "Auto generated Wp");
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 2, 6135.7573, -3236.0579, 133.31839, "Auto generated Wp");
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 3, 6131.06, -3235.4, 134.11908, "Auto generated Wp");
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 4, 6137.5254, -3227.1702, 133.4561, "Auto generated Wp");

DELETE FROM `quest_template_addon` WHERE `ID`=64866;
INSERT INTO `quest_template_addon` (`ID`, `MaxLevel`, `AllowableClasses`, `SourceSpellID`, `PrevQuestID`, `NextQuestID`, `ExclusiveGroup`, `BreadcrumbForQuestId`, `RewardMailTemplateID`, `RewardMailDelay`, `RequiredSkillID`, `RequiredSkillPoints`, `RequiredMinRepFaction`, `RequiredMaxRepFaction`, `RequiredMinRepValue`, `RequiredMaxRepValue`, `ProvidedItemCount`, `SpecialFlags`, `ScriptName`) VALUES (64866, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'quest_into_the_cauldron');

SET @Entry := 18688301;
DELETE FROM `waypoints` WHERE `entry` = @Entry;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 1, 6176.848, -3241.1963, 150.7292, "Auto generated Wp");
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 2, 6200.388, -3247.1719, 164.03577, "Auto generated Wp");
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 3, 6204.2935, -3248.236, 163.8248, "Auto generated Wp");
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 4, 6214.416, -3250.908, 163.81918, "Auto generated Wp");
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 5, 6220.972, -3252.5417, 163.84348, "Auto generated Wp");
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 6, 6238.968, -3257.1614, 175.2584, "Auto generated Wp");
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 7, 6242.2334, -3258.0312, 177.39621, "Auto generated Wp");
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 8, 6256.1797, -3262.1614, 185.6875, "Auto generated Wp");
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 9, 6265.9707, -3264.0642, 185.53322, "Auto generated Wp");
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 10, 6276.1973, -3266.6997, 185.53294, "Auto generated Wp");
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 11, 6285.096, -3268.8074, 185.4254, "Auto generated Wp");
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 12, 6304.0396, -3269.996, 185.1469, "Auto generated Wp");
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 13, 6300.59, -3288.55, 185.06548, "Auto generated Wp");
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 14, 6301.0166, -3291.9722, 185.06548, "Auto generated Wp");

SET @Entry := 18105301;
DELETE FROM `waypoints` WHERE `entry` = @Entry;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 1, 6176.848, -3241.1963, 150.7292, "Auto generated Wp");
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 2, 6200.388, -3247.1719, 164.03577, "Auto generated Wp");
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 3, 6204.2935, -3248.236, 163.8248, "Auto generated Wp");
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 4, 6214.416, -3250.908, 163.81918, "Auto generated Wp");
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 5, 6220.972, -3252.5417, 163.84348, "Auto generated Wp");
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 6, 6238.968, -3257.1614, 175.2584, "Auto generated Wp");
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 7, 6256.1797, -3262.1614, 185.6875, "Auto generated Wp");
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 8, 6265.9707, -3264.0642, 185.53322, "Auto generated Wp");
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 9, 6276.1973, -3266.6997, 185.53294, "Auto generated Wp");
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 10, 6284.6963, -3270.496, 185.4254, "Auto generated Wp");
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 11, 6296.53, -3272.02, 185.486, "Auto generated Wp");
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 12, 6298.8193, -3285.552, 185.06548, "Auto generated Wp");

SET @Entry := 18216801;
DELETE FROM `waypoints` WHERE `entry` = @Entry;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 1, 6176.848, -3241.1963, 150.7292, "Auto generated Wp");
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 2, 6180.5957, -3242.4548, 152.99255, "Auto generated Wp");
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 3, 6200.388, -3247.1719, 164.03577, "Auto generated Wp");
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 4, 6214.416, -3250.908, 163.81918, "Auto generated Wp");
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 5, 6238.968, -3257.1614, 175.2584, "Auto generated Wp");
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 6, 6242.2334, -3258.0312, 177.39621, "Auto generated Wp");
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 7, 6256.1797, -3262.1614, 185.6875, "Auto generated Wp");
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 8, 6265.9707, -3264.0642, 185.53322, "Auto generated Wp");
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 9, 6276.1973, -3266.6997, 185.53294, "Auto generated Wp");
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 10, 6285.096, -3268.8074, 185.4254, "Auto generated Wp");
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 11, 6308.052, -3271.781, 185.08377, "Auto generated Wp");
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 12, 6285.096, -3268.8074, 185.4254, "Auto generated Wp");
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 13, 6308.052, -3271.781, 185.08377, "Auto generated Wp");
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 14, 6308.198, -3270.9917, 185.06546, "Auto generated Wp");
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 15, 6308.2217, -3270.865, 185.1919, "Auto generated Wp");
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 16, 6308.299, -3270.4487, 185.04918, "Auto generated Wp");
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 17, 6308.3257, -3270.3035, 185.23366, "Auto generated Wp");
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 18, 6308.428, -3269.7507, 185.19514, "Auto generated Wp");
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 19, 6308.4624, -3269.5674, 185.06543, "Auto generated Wp");
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 20, 6309.543, -3263.7422, 185.06548, "Auto generated Wp");
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 21, 6313.3257, -3258.7744, 185.23363, "Auto generated Wp");

SET @Entry := 18396001;
DELETE FROM `waypoints` WHERE `entry` = @Entry;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 1, 6176.848, -3241.1963, 150.7292, "Auto generated Wp");
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 2, 6180.5957, -3242.4548, 152.99255, "Auto generated Wp");
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 3, 6200.388, -3247.1719, 164.03577, "Auto generated Wp");
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 4, 6204.2935, -3248.236, 163.8248, "Auto generated Wp");
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 5, 6214.416, -3250.908, 163.81918, "Auto generated Wp");
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 6, 6238.968, -3257.1614, 175.2584, "Auto generated Wp");
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 7, 6242.2334, -3258.0312, 177.39621, "Auto generated Wp");
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 8, 6256.1797, -3262.1614, 185.6875, "Auto generated Wp");
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 9, 6265.9707, -3264.0642, 185.53322, "Auto generated Wp");
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 10, 6276.1973, -3266.6997, 185.53294, "Auto generated Wp");
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 11, 6285.096, -3268.8074, 185.4254, "Auto generated Wp");
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 12, 6299.514, -3271.5798, 185.20839, "Auto generated Wp");
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 13, 6300.38, -3266.95, 185.65306, "Auto generated Wp");
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 14, 6303.1772, -3261.9548, 185.3544, "Auto generated Wp");
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (@Entry , 15, 6303.1772, -3261.9548, 185.3544, "Auto generated Wp");

DELETE FROM `areatrigger` WHERE `SpawnId`=7;
INSERT INTO `areatrigger` (`SpawnId`, `AreaTriggerId`, `IsServerSide`, `MapId`, `PosX`, `PosY`, `PosZ`, `Orientation`, `PhaseUseFlags`, `PhaseId`, `PhaseGroup`, `Shape`, `ShapeData0`, `ShapeData1`, `ShapeData2`, `ShapeData3`, `ShapeData4`, `ShapeData5`, `ShapeData6`, `ShapeData7`, `ScriptName`, `Comment`) VALUES (7, 7, 1, 2570, 6058.14, -3068.98, 173.61, 5.4418, 0, 0, 0, 0, 30, 30, 0, 0, 0, 0, 0, 0, 'into_the_cauldron_at', 'Into the Cauldron');
DELETE FROM `areatrigger_template` WHERE `Id`=7 AND `IsServerSide`=1;
INSERT INTO `areatrigger_template` (`Id`, `IsServerSide`, `Type`, `Flags`, `Data0`, `Data1`, `Data2`, `Data3`, `Data4`, `Data5`, `Data6`, `Data7`, `ScriptName`, `VerifiedBuild`) VALUES (7, 1, 0, 0, 30, 30, 0, 0, 0, 0, 0, 0, NULL, 0);

UPDATE `quest_template` SET `FlagsEx2` = 8 WHERE `id` = 64865