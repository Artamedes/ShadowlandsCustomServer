 -- evoker starting zone
DELETE FROM `spell_area` WHERE `area` = 13806;
INSERT INTO `spell_area` (`area`, `spell`, `quest_start`, `quest_start_status`, `quest_end`, `quest_end_status`, `flags`, `aura_spell`, `racemask`, `gender`) VALUES
(13806, 369772, 0, 64, 0, 11, 3, 0, 0, 2);
DELETE FROM `phase_area` WHERE `AreaId` = 13769;
INSERT INTO `phase_area` (`AreaId`, `PhaseId`, `Comment`) VALUES
(13769, 17811, '13769 - 17811 // 13769 - 17811 // 13769 - 17811 // 13769 - 17811 // 13769 - 17811 // 13769 - 17811 // 13769 - 17811 // 13769 - 17811 // 13769 - 17811 // 13769 - 17811 // 13769 - 17811 // Azurathel in room'),
(13769, 17814, '13769 - 17814 // 13769 - 17814 // 13769 - 17814 // 13769 - 17814 // 13769 - 17814 // 13769 - 17814 // 13769 - 17814 // 13769 - 17814 // 13769 - 17814 // 13769 - 17814 // 13769 - 17814 // unk removed after arcane guardians completion'),
(13769, 17815, '13769 - 17815 // 13769 - 17815 // 13769 - 17815 // 13769 - 17815 // 13769 - 17815 // 13769 - 17815 // 13769 - 17815 // 13769 - 17815 // 13769 - 17815 // 13769 - 17815 // 13769 - 17815 // dragons at barrier after gearing up'),
(13769, 17820, '13769 - 17820 // 13769 - 17820 // 13769 - 17820 // 13769 - 17820 // 13769 - 17820 // 13769 - 17820 // 13769 - 17820 // 13769 - 17820 // 13769 - 17820 // 13769 - 17820 // 13769 - 17820 // commanders flew down'),
(13769, 17822, '13769 - 17822 // 13769 - 17822 // 13769 - 17822 // 13769 - 17822 // 13769 - 17822 // 13769 - 17822 // 13769 - 17822 // 13769 - 17822 // 13769 - 17822 // 13769 - 17822 // 13769 - 17822 // dragons bottom stairs'),
(13769, 17876, '13769 - 17876 // 13769 - 17876 // 13769 - 17876 // 13769 - 17876 // 13769 - 17876 // 13769 - 17876 // 13769 - 17876 // 13769 - 17876 // 13769 - 17876 // 13769 - 17876 // 13769 - 17876 // lapisagos'),
(13769, 18197, '13769 - 18197 // 13769 - 18197 // 13769 - 18197 // 13769 - 18197 // 13769 - 18197 // 13769 - 18197 // 13769 - 18197 // 13769 - 18197 // 13769 - 18197 // 13769 - 18197 // 13769 - 18197 // dracthyr talons'),
(13769, 19712, '13769 - 19712 // 13769 - 19712 // 13769 - 19712 // 13769 - 19712 // 13769 - 19712 // 13769 - 19712 // 13769 - 19712 // 13769 - 19712 // 13769 - 19712 // 13769 - 19712 // 13769 - 19712 // Tethalash in room');
DELETE FROM `conditions` WHERE (`SourceTypeOrReferenceId` = 26) AND (`SourceEntry` IN (13769));
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `Comment`) VALUES
(26, 17811, 13769, 0, 0, 48, 0, 422316, 0, 1, 0, 'Player has quest objective 422316 == 1 (but hasn\'t rewarded quest yet)'),
(26, 17811, 13769, 0, 1, 8, 0, 64864, 0, 0, 0, 'Player has quest Awaken, Dracthyr (64864) rewarded'),
(26, 17811, 13769, 0, 1, 47, 0, 64865, 66, 0, 1, 'Player doesn\'t have Gear Up (64865) in state complete, rewarded'),
(26, 17814, 13769, 0, 0, 47, 0, 64863, 66, 0, 1, 'Player doesn\'t have Arcane Guardians (64863) in state complete, rewarded'),
(26, 17815, 13769, 0, 0, 47, 0, 64865, 66, 0, 0, 'Player has Gear Up (64865) in state complete, rewarded'),
(26, 17815, 13769, 0, 0, 47, 0, 64866, 1, 0, 0, 'Player has Into the Cauldron (64866) in state none'),
(26, 17820, 13769, 0, 0, 47, 0, 64866, 8, 0, 0, 'Player has Into the Cauldron (64866) in state incomplete'),
(26, 17822, 13769, 0, 0, 47, 0, 64866, 66, 0, 0, 'Player has Into the Cauldron (64866) in state complete, rewarded'),
(26, 17876, 13769, 0, 0, 47, 0, 64866, 66, 0, 0, 'Player has Into the Cauldron (64866) in state complete, rewarded'),
(26, 18197, 13769, 0, 0, 47, 0, 64866, 8, 0, 0, 'Player has Into the Cauldron (64866) in state incomplete'),
(26, 19712, 13769, 0, 0, 48, 0, 423680, 0, 1, 0, 'Player has quest objective 423680 == 1 (but hasn\'t rewarded quest yet)'),
(26, 19712, 13769, 0, 1, 8, 0, 64864, 0, 0, 0, 'Player has quest Awaken, Dracthyr (64864) rewarded'),
(26, 19712, 13769, 0, 1, 47, 0, 64865, 66, 0, 1, 'Player doesn\'t have Gear Up (64865) in state complete, rewarded');
DELETE FROM `phase_area` WHERE `AreaId` = 14433;
INSERT INTO `phase_area` (`AreaId`, `PhaseId`, `Comment`) VALUES
(14433, 17815, '14433 - 17815 // 14433 - 17815 // 14433 - 17815 // 14433 - 17815 // 14433 - 17815 // 14433 - 17815 // 14433 - 17815 // 14433 - 17815 // 14433 - 17815 // 14433 - 17815 // 14433 - 17815 // 14433 - 17815 // dragons at barrier after gearing up'),
(14433, 17820, '14433 - 17820 // 14433 - 17820 // 14433 - 17820 // 14433 - 17820 // 14433 - 17820 // 14433 - 17820 // 14433 - 17820 // 14433 - 17820 // 14433 - 17820 // 14433 - 17820 // 14433 - 17820 // commanders flew down'),
(14433, 17822, '14433 - 17822 // 14433 - 17822 // 14433 - 17822 // 14433 - 17822 // 14433 - 17822 // 14433 - 17822 // 14433 - 17822 // 14433 - 17822 // 14433 - 17822 // 14433 - 17822 // 14433 - 17822 // dragons bottom stairs'),
(14433, 17876, '14433 - 17876 // 14433 - 17876 // 14433 - 17876 // 14433 - 17876 // 14433 - 17876 // 14433 - 17876 // 14433 - 17876 // 14433 - 17876 // 14433 - 17876 // 14433 - 17876 // 14433 - 17876 // lapisagos'),
(14433, 18197, '14433 - 18197 // 14433 - 18197 // 14433 - 18197 // 14433 - 18197 // 14433 - 18197 // 14433 - 18197 // 14433 - 18197 // 14433 - 18197 // 14433 - 18197 // 14433 - 18197 // 14433 - 18197 // dracthyr talons');
DELETE FROM `conditions` WHERE (`SourceTypeOrReferenceId` = 26) AND (`SourceEntry` IN (14433));
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `Comment`) VALUES
(26, 17815, 14433, 0, 0, 47, 0, 64865, 66, 0, 0, 'Player has Gear Up (64865) in state complete, rewarded'),
(26, 17815, 14433, 0, 0, 47, 0, 64866, 1, 0, 0, 'Player has Into the Cauldron (64866) in state none'),
(26, 17820, 14433, 0, 0, 47, 0, 64866, 8, 0, 0, 'Player has Into the Cauldron (64866) in state incomplete'),
(26, 17822, 14433, 0, 0, 47, 0, 64866, 66, 0, 0, 'Player has Into the Cauldron (64866) in state complete, rewarded'),
(26, 17876, 14433, 0, 0, 47, 0, 64866, 66, 0, 0, 'Player has Into the Cauldron (64866) in state complete, rewarded'),
(26, 18197, 14433, 0, 0, 47, 0, 64866, 8, 0, 0, 'Player has Into the Cauldron (64866) in state incomplete');
 -- the dragon at the door
 -- Lapisagos smart ai
SET @ENTRY := 186854;
DELETE FROM `smart_scripts` WHERE `source_type` = 0 AND `entryOrGuid` = @ENTRY;
UPDATE `creature_template` SET `AIName` = 'SmartAI', `ScriptName` = '' WHERE `entry` = @ENTRY;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(@ENTRY, 0, 0, 0, 0, 0, 100, 0, 18000, 25000, 30000, 35000, 11, 376860, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Every 30 - 35 seconds (18 - 25s initially) (IC) - Self: Cast spell 376860 on Victim'),
(@ENTRY, 0, 1, 0, 0, 0, 100, 0, 5000, 12000, 20000, 25000, 11, 370072, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Every 20 - 25 seconds (5 - 12s initially) (IC) - Self: Cast spell 370072 on Victim'),
(@ENTRY, 0, 2, 0, 11, 0, 100, 0, 0, 0, 0, 0, 21, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'On respawn - Self: Disable combat based movement');


DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 22 AND `SourceEntry` = 186854 AND `SourceId` = 0;
 -- Obsidian Warder smart ai
SET @ENTRY := 187167;
DELETE FROM `smart_scripts` WHERE `source_type` = 0 AND `entryOrGuid` = @ENTRY;
UPDATE `creature_template` SET `AIName` = 'SmartAI', `ScriptName` = '' WHERE `entry` = @ENTRY;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(@ENTRY, 0, 0, 0, 60, 0, 100, 0, 7000, 11000, 7000, 11000, 11, 369842, 0, 0, 0, 0, 0, 19, 186854, 40, 0, 0, 0, 0, 0, 'Every 7 - 11 seconds - Self: Cast spell 369842 on Closest alive creature Lapisagos (186854) in 40 yards');


DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 22 AND `SourceEntry` = 187167 AND `SourceId` = 0;
 -- into the cauldron
 -- Scalecommander Azurathel smart ai
SET @ENTRY := 181594;
DELETE FROM `smart_scripts` WHERE `source_type` = 0 AND `entryOrGuid` = @ENTRY;
UPDATE `creature_template` SET `AIName` = 'SmartAI', `ScriptName` = '' WHERE `entry` = @ENTRY;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(@ENTRY, 0, 0, 0, 19, 0, 100, 0, 64866, 0, 0, 0, 85, 370046, 2, 0, 0, 0, 0, 16, 0, 0, 0, 0, 0, 0, 0, 'On player accepted quest Into the Cauldron (64866) - Player who accepted quest\'s party: Cast spell 370046 with flags triggered on self');


DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 22 AND `SourceEntry` = 181594 AND `SourceId` = 0;
 -- Scalecommander Azurathel smart ai
SET @ENTRY := 181597;
DELETE FROM `smart_scripts` WHERE `source_type` = 0 AND `entryOrGuid` = @ENTRY;
UPDATE `creature_template` SET `AIName` = 'SmartAI', `ScriptName` = '' WHERE `entry` = @ENTRY;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(@ENTRY, 0, 0, 1, 54, 0, 100, 0, 0, 0, 0, 0, 128, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'On just summoned - Self: Plays Anim with ID 0'),
(@ENTRY, 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 53, 1, 18159700, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'On just summoned - Self: Start path #18159700, run, do not repeat, Passive'),
(@ENTRY, 0, 2, 3, 58, 0, 100, 0, 2, 18159700, 0, 0, 128, 23587, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'On waypoint 2 of path 18159700 ended - Self: Plays Anim with ID 23587'),
(@ENTRY, 0, 3, 0, 61, 0, 100, 0, 0, 0, 0, 0, 119, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'On waypoint 2 of path 18159700 ended - Self: Set can Fly'),
(@ENTRY, 0, 4, 5, 58, 0, 100, 0, 5, 18159700, 0, 0, 128, 23587, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'On waypoint 5 of path 18159700 ended - Self: Plays Anim with ID 23587'),
(@ENTRY, 0, 5, 0, 61, 0, 100, 0, 0, 0, 0, 0, 119, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'On waypoint 5 of path 18159700 ended - Self: Set can Fly'),
(@ENTRY, 0, 6, 0, 58, 0, 100, 0, 6, 18159700, 0, 0, 41, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'On waypoint 6 of path 18159700 ended - Self: Despawn instantly');


DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 22 AND `SourceEntry` = 181597 AND `SourceId` = 0;
 -- Dracthyr Talon smart ai
SET @ENTRY := 187335;
DELETE FROM `smart_scripts` WHERE `source_type` = 0 AND `entryOrGuid` = @ENTRY;
UPDATE `creature_template` SET `AIName` = 'SmartAI', `ScriptName` = '' WHERE `entry` = @ENTRY;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(@ENTRY, 0, 0, 1, 8, 0, 100, 1, 361509, 0, 0, 0, 33, 182702, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'On spell 361509 hit - Caster: Give kill credit 182702'),
(@ENTRY, 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 41, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'On spell 361509 hit - Self: Despawn instantly');


DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 22 AND `SourceEntry` = 187335 AND `SourceId` = 0;
 -- Dracthyr Talon smart ai
SET @ENTRY := 187133;
DELETE FROM `smart_scripts` WHERE `source_type` = 0 AND `entryOrGuid` = @ENTRY;
UPDATE `creature_template` SET `AIName` = 'SmartAI', `ScriptName` = '' WHERE `entry` = @ENTRY;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(@ENTRY, 0, 0, 1, 8, 0, 100, 1, 361509, 0, 0, 0, 33, 182702, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'On spell 361509 hit - Caster: Give kill credit 182702'),
(@ENTRY, 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 41, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'On spell 361509 hit - Self: Despawn instantly');


DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 22 AND `SourceEntry` = 187133 AND `SourceId` = 0;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `Comment`) VALUES
(22, 1, 187133, 0, 0, 1, 1, 370226, 0, 0, 0, 'Object has aura of spell 370226, effect EFFECT_0');
 -- Kodethi smart ai
SET @ENTRY := 186865;
DELETE FROM `smart_scripts` WHERE `source_type` = 0 AND `entryOrGuid` = @ENTRY;
UPDATE `creature_template` SET `AIName` = 'SmartAI', `ScriptName` = '' WHERE `entry` = @ENTRY;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(@ENTRY, 0, 0, 0, 54, 0, 100, 0, 0, 0, 0, 0, 69, 1, 0, 0, 0, 0, 0, 8, 0, 0, 0, 6021.6, -3084.62, 200.51, 0, 'On just summoned - Self: Move to position (6021.6, -3084.62, 200.51, 0) (point id 1)'),
(@ENTRY, 0, 1, 0, 34, 0, 100, 0, 8, 1, 0, 0, 41, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'On movement of type POINT_MOTION_TYPE inform, point 1 - Self: Despawn instantly');


DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 22 AND `SourceEntry` = 186865 AND `SourceId` = 0;
 -- Dervishian smart ai
SET @ENTRY := 182069;
DELETE FROM `smart_scripts` WHERE `source_type` = 0 AND `entryOrGuid` = @ENTRY;
UPDATE `creature_template` SET `AIName` = 'SmartAI', `ScriptName` = '' WHERE `entry` = @ENTRY;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(@ENTRY, 0, 0, 1, 54, 0, 100, 0, 0, 0, 0, 0, 83, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'On just summoned - Self: Remove npc flags GOSSIP'),
(@ENTRY, 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 69, 1, 0, 0, 0, 0, 0, 8, 0, 0, 0, 6020.83, -3084.27, 200.503, 0, 'On just summoned - Self: Move to position (6020.83, -3084.27, 200.503, 0) (point id 1)'),
(@ENTRY, 0, 2, 0, 34, 0, 100, 0, 8, 1, 0, 0, 41, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'On movement of type POINT_MOTION_TYPE inform, point 1 - Self: Despawn instantly');


DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 22 AND `SourceEntry` = 182069 AND `SourceId` = 0;
 -- Scalecommander Cindrethresh smart ai
SET @ENTRY := 182696;
DELETE FROM `smart_scripts` WHERE `source_type` = 0 AND `entryOrGuid` = @ENTRY;
UPDATE `creature_template` SET `AIName` = 'SmartAI', `ScriptName` = '' WHERE `entry` = @ENTRY;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(@ENTRY, 0, 0, 1, 54, 0, 100, 0, 0, 0, 0, 0, 128, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'On just summoned - Self: Plays Anim with ID 0'),
(@ENTRY, 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 53, 1, 18269600, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'On just summoned - Self: Start path #18269600, run, do not repeat, Passive'),
(@ENTRY, 0, 2, 0, 58, 0, 100, 0, 7, 18269600, 0, 0, 41, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'On waypoint 7 of path 18269600 ended - Self: Despawn instantly'),
(@ENTRY, 0, 3, 4, 40, 0, 100, 0, 2, 18269600, 0, 0, 128, 23587, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'On wapoint 2 of path 18269600 reached - Self: Plays Anim with ID 23587'),
(@ENTRY, 0, 4, 0, 61, 0, 100, 0, 0, 0, 0, 0, 119, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'On wapoint 2 of path 18269600 reached - Self: Set can Fly'),
(@ENTRY, 0, 5, 6, 40, 0, 100, 0, 5, 18269600, 0, 0, 128, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'On wapoint 5 of path 18269600 reached - Self: Plays Anim with ID 0'),
(@ENTRY, 0, 6, 0, 61, 0, 100, 0, 0, 0, 0, 0, 119, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'On wapoint 5 of path 18269600 reached - Self: Set can not Fly');


DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 22 AND `SourceEntry` = 182696 AND `SourceId` = 0;
 -- Scalecommander Cindrethresh smart ai
SET @ENTRY := 186883;
DELETE FROM `smart_scripts` WHERE `source_type` = 0 AND `entryOrGuid` = @ENTRY;
UPDATE `creature_template` SET `AIName` = 'SmartAI', `ScriptName` = '' WHERE `entry` = @ENTRY;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(@ENTRY, 0, 0, 1, 38, 0, 100, 0, 1, 1, 0, 0, 119, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'On data[1] set to 1 - Self: Set can Fly'),
(@ENTRY, 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 53, 1, 18688300, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'On data[1] set to 1 - Self: Start path #18688300, run, do not repeat, Passive'),
(@ENTRY, 0, 2, 0, 58, 0, 100, 0, 4, 18688300, 0, 0, 41, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'On waypoint 4 of path 18688300 ended - Self: Despawn instantly'),
(@ENTRY, 0, 3, 0, 60, 0, 100, 0, 8000, 11000, 8000, 11000, 11, 369416, 0, 0, 0, 0, 0, 19, 186854, 40, 0, 0, 0, 0, 0, 'Every 8 - 11 seconds - Self: Cast spell 369416 on Closest alive creature Lapisagos (186854) in 40 yards'),
(@ENTRY, 0, 4, 5, 19, 0, 100, 0, 64871, 0, 0, 0, 134, 360713, 2, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'On player accepted quest The Dragon at the Door (64871) - Player who accepted quest: Cast spell 360713 with flags triggered on Player who accepted quest'),
(@ENTRY, 0, 5, 6, 61, 0, 100, 0, 0, 0, 0, 0, 134, 369887, 2, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'On player accepted quest The Dragon at the Door (64871) - Player who accepted quest: Cast spell 369887 with flags triggered on Player who accepted quest'),
(@ENTRY, 0, 6, 7, 61, 0, 100, 0, 0, 0, 0, 0, 134, 369892, 2, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'On player accepted quest The Dragon at the Door (64871) - Player who accepted quest: Cast spell 369892 with flags triggered on Player who accepted quest'),
(@ENTRY, 0, 7, 8, 61, 0, 100, 0, 0, 0, 0, 0, 12, 186883, 8, 0, 0, 3, 0, 8, 0, 0, 0, 6135.84, -3233.79, 133.119, 0.6781, 'On player accepted quest The Dragon at the Door (64871) - Action invoker: Summon creature Scalecommander Cindrethresh (186883) at (6135.84, -3233.79, 133.119, 0.6781) as summon type manual despawn, as personal spawn'),
(@ENTRY, 0, 8, 9, 61, 0, 100, 0, 0, 0, 0, 0, 12, 181053, 8, 0, 0, 3, 0, 8, 0, 0, 0, 6136.13, -3236.67, 133.311, 0.2881, 'On player accepted quest The Dragon at the Door (64871) - Action invoker: Summon creature Kodethi (181053) at (6136.13, -3236.67, 133.311, 0.2881) as summon type manual despawn, as personal spawn'),
(@ENTRY, 0, 9, 10, 61, 0, 100, 0, 0, 0, 0, 0, 12, 182168, 8, 0, 0, 3, 0, 8, 0, 0, 0, 6137.02, -3230.05, 133.118, 5.2674, 'On player accepted quest The Dragon at the Door (64871) - Action invoker: Summon creature Scalecommander Azurathel (182168) at (6137.02, -3230.05, 133.118, 5.2674) as summon type manual despawn, as personal spawn'),
(@ENTRY, 0, 10, 0, 61, 0, 100, 0, 0, 0, 0, 0, 12, 183960, 8, 0, 0, 3, 0, 8, 0, 0, 0, 6137.53, -3227.17, 133.234, 5.5836, 'On player accepted quest The Dragon at the Door (64871) - Action invoker: Summon creature Dervishian (183960) at (6137.53, -3227.17, 133.234, 5.5836) as summon type manual despawn, as personal spawn'),
(@ENTRY, 0, 11, 0, 38, 0, 100, 0, 1, 2, 0, 0, 53, 1, 18688301, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'On data[1] set to 2 - Self: Start path #18688301, run, do not repeat, Passive'),
(@ENTRY, 0, 12, 0, 58, 0, 100, 0, 14, 18688301, 0, 0, 41, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'On waypoint 14 of path 18688301 ended - Self: Despawn instantly'),
(@ENTRY, 0, 13, 0, 17, 0, 100, 0, 0, 0, 0, 0, 45, 1, 2, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'On summoned anyunit - Summon: Set creature data #1 to 2');


DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 22 AND `SourceEntry` = 186883 AND `SourceId` = 0;
 -- Kodethi smart ai
SET @ENTRY := 181053;
DELETE FROM `smart_scripts` WHERE `source_type` = 0 AND `entryOrGuid` = @ENTRY;
UPDATE `creature_template` SET `AIName` = 'SmartAI', `ScriptName` = '' WHERE `entry` = @ENTRY;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(@ENTRY, 0, 0, 1, 38, 0, 100, 0, 1, 1, 0, 0, 119, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'On data[1] set to 1 - Self: Set can Fly'),
(@ENTRY, 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 53, 1, 18105300, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'On data[1] set to 1 - Self: Start path #18105300, run, do not repeat, Passive'),
(@ENTRY, 0, 2, 0, 58, 0, 100, 0, 4, 18105300, 0, 0, 41, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'On waypoint 4 of path 18105300 ended - Self: Despawn instantly'),
(@ENTRY, 0, 3, 0, 60, 0, 100, 0, 5000, 10000, 9000, 15000, 11, 370262, 0, 0, 0, 0, 0, 1, 50, 0, 0, 0, 0, 0, 0, 'Every 9 - 15 seconds (5 - 10s initially) - Self: Cast spell 370262 on Self'),
(@ENTRY, 0, 4, 5, 10, 0, 100, 0, 1, 30, 5000, 5000, 28, 370262, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'On only non hostile unit in line of sight (OOC) - Self: Remove aura due to spell 370262'),
(@ENTRY, 0, 5, 0, 61, 0, 100, 0, 0, 0, 0, 0, 11, 364664, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'On only non hostile unit in line of sight (OOC) - Self: Cast spell 364664 on Unit in LOS'),
(@ENTRY, 0, 6, 0, 38, 0, 100, 0, 1, 2, 0, 0, 53, 1, 18105301, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'On data[1] set to 2 - Self: Start path #18105301, run, do not repeat, Passive'),
(@ENTRY, 0, 7, 0, 58, 0, 100, 0, 12, 18105301, 0, 0, 41, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'On waypoint 12 of path 18105301 ended - Self: Despawn instantly');


DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 22 AND `SourceEntry` = 181053 AND `SourceId` = 0;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `Comment`) VALUES
(22, 4, 181053, 0, 0, 29, 0, 186854, 50, 0, 0, 'There is creature Lapisagos (186854) within range 50 yards to Action invoker'),
(22, 5, 181053, 0, 0, 1, 1, 370262, 0, 0, 0, 'Object has aura of spell 370262, effect EFFECT_0'),
(22, 5, 181053, 0, 0, 38, 0, 80, 4, 0, 0, 'Action invoker\'s HP <= 80%%');
 -- Scalecommander Azurathel smart ai
SET @ENTRY := 182168;
DELETE FROM `smart_scripts` WHERE `source_type` = 0 AND `entryOrGuid` = @ENTRY;
UPDATE `creature_template` SET `AIName` = 'SmartAI', `ScriptName` = '' WHERE `entry` = @ENTRY;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(@ENTRY, 0, 0, 1, 38, 0, 100, 0, 1, 1, 0, 0, 119, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'On data[1] set to 1 - Self: Set can Fly'),
(@ENTRY, 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 53, 1, 18216800, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'On data[1] set to 1 - Self: Start path #18216800, run, do not repeat, Passive'),
(@ENTRY, 0, 2, 0, 58, 0, 100, 0, 4, 182168, 0, 0, 41, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'On waypoint 4 of path 182168 ended - Self: Despawn instantly'),
(@ENTRY, 0, 3, 0, 60, 0, 100, 0, 7000, 11000, 6500, 13000, 11, 369416, 0, 0, 0, 0, 0, 19, 186854, 40, 0, 0, 0, 0, 0, 'Every 6.5 - 13 seconds (7 - 11s initially) - Self: Cast spell 369416 on Closest alive creature Lapisagos (186854) in 40 yards'),
(@ENTRY, 0, 4, 0, 38, 0, 100, 0, 1, 2, 0, 0, 53, 1, 18216801, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'On data[1] set to 2 - Self: Start path #18216801, run, do not repeat, Passive'),
(@ENTRY, 0, 5, 0, 58, 0, 100, 0, 21, 18216801, 0, 0, 41, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'On waypoint 21 of path 18216801 ended - Self: Despawn instantly');


DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 22 AND `SourceEntry` = 182168 AND `SourceId` = 0;
 -- Dervishian smart ai
SET @ENTRY := 183960;
DELETE FROM `smart_scripts` WHERE `source_type` = 0 AND `entryOrGuid` = @ENTRY;
UPDATE `creature_template` SET `AIName` = 'SmartAI', `ScriptName` = '' WHERE `entry` = @ENTRY;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(@ENTRY, 0, 0, 1, 38, 0, 100, 0, 1, 1, 0, 0, 119, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'On data[1] set to 1 - Self: Set can Fly'),
(@ENTRY, 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 53, 1, 18396000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'On data[1] set to 1 - Self: Start path #18396000, run, do not repeat, Passive'),
(@ENTRY, 0, 2, 0, 58, 0, 100, 0, 4, 18396000, 0, 0, 41, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'On waypoint 4 of path 18396000 ended - Self: Despawn instantly'),
(@ENTRY, 0, 3, 0, 60, 0, 100, 0, 5000, 8000, 10000, 15000, 11, 370262, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Every 10 - 15 seconds (5 - 8s initially) - Self: Cast spell 370262 on Self'),
(@ENTRY, 0, 4, 5, 10, 0, 100, 0, 1, 30, 5000, 5000, 28, 370262, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'On only non hostile unit in line of sight (OOC) - Self: Remove aura due to spell 370262'),
(@ENTRY, 0, 5, 0, 61, 0, 100, 0, 0, 0, 0, 0, 11, 364664, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'On only non hostile unit in line of sight (OOC) - Self: Cast spell 364664 on Unit in LOS'),
(@ENTRY, 0, 6, 0, 38, 0, 100, 0, 1, 2, 0, 0, 53, 1, 18396001, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'On data[1] set to 2 - Self: Start path #18396001, run, do not repeat, Passive'),
(@ENTRY, 0, 7, 0, 58, 0, 100, 0, 15, 18396001, 0, 0, 41, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'On waypoint 15 of path 18396001 ended - Self: Despawn instantly');


DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 22 AND `SourceEntry` = 183960 AND `SourceId` = 0;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `Comment`) VALUES
(22, 4, 183960, 0, 0, 29, 0, 186854, 50, 0, 0, 'There is creature Lapisagos (186854) within range 50 yards to Action invoker'),
(22, 5, 183960, 0, 0, 1, 1, 370262, 0, 0, 0, 'Object has aura of spell 370262, effect EFFECT_0'),
(22, 5, 183960, 0, 0, 38, 0, 70, 4, 0, 0, 'Action invoker\'s HP <= 70%%');
 -- trash
 -- Ancient Construct smart ai
SET @ENTRY := 185272;
DELETE FROM `smart_scripts` WHERE `source_type` = 0 AND `entryOrGuid` = @ENTRY;
UPDATE `creature_template` SET `AIName` = 'SmartAI', `ScriptName` = '' WHERE `entry` = @ENTRY;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(@ENTRY, 0, 0, 0, 0, 0, 100, 0, 5000, 9000, 15000, 20000, 11, 369107, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Every 15 - 20 seconds (5 - 9s initially) (IC) - Self: Cast spell 369107 on Victim'),
(@ENTRY, 0, 1, 0, 2, 0, 100, 1, 0, 50, 0, 0, 11, 375605, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'When health between 0%-50%% (once) - Self: Cast spell 375605 on Self');


DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 22 AND `SourceEntry` = 185272 AND `SourceId` = 0;
 -- Conjured Guardian smart ai
SET @ENTRY := 186853;
DELETE FROM `smart_scripts` WHERE `source_type` = 0 AND `entryOrGuid` = @ENTRY;
UPDATE `creature_template` SET `AIName` = 'SmartAI', `ScriptName` = '' WHERE `entry` = @ENTRY;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(@ENTRY, 0, 0, 0, 11, 0, 100, 0, 0, 0, 0, 0, 11, 369948, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'On respawn - Self: Cast spell 369948 on Self'),
(@ENTRY, 0, 1, 0, 0, 0, 100, 0, 3000, 5000, 20000, 30000, 86, 392337, 0, 1, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Every 20 - 30 seconds (3 - 5s initially) (IC) - Self: Cast spell 392337 at Victim');


DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 22 AND `SourceEntry` = 186853 AND `SourceId` = 0;
 -- spellclick
DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = 181680;
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`, `user_type`) VALUES
(181680, 362355, 1, 0);
DELETE FROM `conditions` WHERE (`SourceTypeOrReferenceId` = 18) AND (`SourceGroup` IN (181680));
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `Comment`) VALUES
(18, 181680, 362355, 0, 0, 48, 0, 423680, 0, 1, 1, 'Clicker hasn\'t quest objective 423680 < 1 or has rewarded the quest');
 -- awaken
 -- Kodethi smart ai
SET @ENTRY := 187223;
DELETE FROM `smart_scripts` WHERE `source_type` = 0 AND `entryOrGuid` = @ENTRY;
UPDATE `creature_template` SET `AIName` = 'SmartAI', `ScriptName` = '' WHERE `entry` = @ENTRY;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(@ENTRY, 0, 0, 1, 54, 0, 100, 0, 0, 0, 0, 0, 11, 382137, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'On just summoned - Self: Cast spell 382137 on Self'),
(@ENTRY, 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 82, 16777216, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'On just summoned - Self: Add npc flags SPELLCLICK'),
(@ENTRY, 0, 2, 3, 8, 0, 100, 0, 362357, 0, 0, 0, 11, 369497, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'On spell 362357 hit - Self: Cast spell 369497 on Self'),
(@ENTRY, 0, 3, 4, 61, 0, 100, 0, 0, 0, 0, 0, 83, 16777216, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'On spell 362357 hit - Self: Remove npc flags SPELLCLICK'),
(@ENTRY, 0, 4, 5, 61, 0, 100, 0, 0, 0, 0, 0, 128, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'On spell 362357 hit - Self: Plays Anim with ID 0'),
(@ENTRY, 0, 5, 0, 61, 0, 100, 0, 0, 0, 0, 0, 33, 181494, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'On spell 362357 hit - Caster: Give kill credit Dervishian (181494)'),
(@ENTRY, 0, 6, 7, 8, 0, 100, 0, 369496, 0, 0, 0, 85, 377481, 2, 0, 0, 0, 0, 23, 0, 0, 0, 0, 0, 0, 0, 'On spell 369496 hit - Owner/Summoner: Cast spell 377481 with flags triggered on self'),
(@ENTRY, 0, 7, 0, 61, 0, 100, 0, 0, 0, 0, 0, 67, 1, 7500, 7500, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'On spell 369496 hit - Trigger timed event timedEvent[1] in 7500 - 7500 ms // -meta_wait'),
(@ENTRY, 0, 8, 9, 59, 0, 100, 0, 1, 0, 0, 0, 69, 1, 0, 0, 0, 0, 0, 8, 0, 0, 0, 5807.68, -3043.2, 250.451, 0, 'On timed event timedEvent[1] triggered - Self: Move to position (5807.68, -3043.2, 250.451, 0) (point id 1)'),
(@ENTRY, 0, 9, 10, 61, 0, 100, 0, 0, 0, 0, 0, 119, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'On timed event timedEvent[1] triggered - Self: Set can Fly'),
(@ENTRY, 0, 10, 0, 61, 0, 100, 0, 0, 0, 0, 0, 126, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'On timed event timedEvent[1] triggered - Last action invoker: Remove all gameobjects'),
(@ENTRY, 0, 11, 12, 34, 0, 100, 0, 8, 1, 0, 0, 128, 23587, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'On movement of type POINT_MOTION_TYPE inform, point 1 - Self: Plays Anim with ID 23587'),
(@ENTRY, 0, 12, 0, 61, 0, 100, 0, 0, 0, 0, 0, 53, 1, 18722300, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'On movement of type POINT_MOTION_TYPE inform, point 1 - Self: Start path #18722300, run, do not repeat, Passive'),
(@ENTRY, 0, 13, 14, 34, 0, 100, 1, 2, 2, 0, 0, 128, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'On movement of type WAYPOINT_MOTION_TYPE inform, point 2 - Self: Plays Anim with ID 0'),
(@ENTRY, 0, 14, 0, 61, 0, 100, 0, 0, 0, 0, 0, 53, 1, 18722301, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'On movement of type WAYPOINT_MOTION_TYPE inform, point 2 - Self: Start path #18722301, run, do not repeat, Passive'),
(@ENTRY, 0, 15, 0, 58, 0, 100, 0, 7, 18722301, 0, 0, 41, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'On waypoint 7 of path 18722301 ended - Self: Despawn instantly');


DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 22 AND `SourceEntry` = 187223 AND `SourceId` = 0;
 -- Talon Kethahn smart ai
SET @ENTRY := 181712;
DELETE FROM `smart_scripts` WHERE `source_type` = 0 AND `entryOrGuid` = @ENTRY;
UPDATE `creature_template` SET `AIName` = 'SmartAI', `ScriptName` = '' WHERE `entry` = @ENTRY;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(@ENTRY, 0, 0, 0, 11, 0, 100, 0, 0, 2570, 0, 0, 19, 33554432, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'On respawn on map 2570 - Self: Remove UNIT_FLAGS to NOT_SELECTABLE'),
(@ENTRY, 0, 1, 0, 64, 0, 100, 0, 0, 0, 0, 0, 33, 181712, 3, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'On player opened gossip - Gossip player: Give kill credit Talon Kethahn (181712)');


DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 22 AND `SourceEntry` = 181712 AND `SourceId` = 0;
 -- Tethalash smart ai
SET @ENTRY := 181680;
DELETE FROM `smart_scripts` WHERE `source_type` = 0 AND `entryOrGuid` = @ENTRY;
UPDATE `creature_template` SET `AIName` = 'SmartAI', `ScriptName` = '' WHERE `entry` = @ENTRY;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(@ENTRY, 0, 0, 0, 11, 0, 100, 0, 0, 0, 0, 0, 75, 362331, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'On respawn - Self: Add aura 362331'),
(@ENTRY, 0, 1, 2, 8, 0, 100, 0, 362357, 0, 0, 0, 12, 186864, 8, 0, 0, 3, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'On spell 362357 hit - Action invoker: Summon creature Tethalash (186864) at Self\'s position, moved by offset (0, 0, 0, 0) as summon type manual despawn, as personal spawn'),
(@ENTRY, 0, 2, 3, 61, 0, 100, 0, 0, 0, 0, 0, 33, 181680, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'On spell 362357 hit - Caster: Give kill credit Tethalash (181680)'),
(@ENTRY, 0, 3, 0, 61, 0, 100, 0, 0, 0, 0, 0, 41, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'On spell 362357 hit - Self: Despawn instantly');


DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 22 AND `SourceEntry` = 181680 AND `SourceId` = 0;
 -- Tethalash smart ai
SET @ENTRY := 186864;
DELETE FROM `smart_scripts` WHERE `source_type` = 0 AND `entryOrGuid` = @ENTRY;
UPDATE `creature_template` SET `AIName` = 'SmartAI', `ScriptName` = '' WHERE `entry` = @ENTRY;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(@ENTRY, 0, 0, 1, 54, 0, 100, 0, 0, 0, 0, 0, 11, 362331, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'On just summoned - Self: Cast spell 362331 with flags triggered on Self'),
(@ENTRY, 0, 1, 2, 61, 0, 100, 0, 0, 0, 0, 0, 11, 369497, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'On just summoned - Self: Cast spell 369497 with flags triggered on Self'),
(@ENTRY, 0, 2, 0, 61, 0, 100, 0, 0, 0, 0, 0, 67, 1, 2500, 2500, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'On just summoned - Trigger timed event timedEvent[1] in 2500 - 2500 ms // -meta_wait'),
(@ENTRY, 0, 3, 4, 59, 0, 100, 0, 1, 0, 0, 0, 128, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'On timed event timedEvent[1] triggered - Self: Plays Anim with ID 0'),
(@ENTRY, 0, 4, 0, 61, 0, 100, 0, 0, 0, 0, 0, 53, 1, 18686400, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'On timed event timedEvent[1] triggered - Self: Start path #18686400, run, do not repeat, Passive'),
(@ENTRY, 0, 5, 0, 58, 0, 100, 0, 7, 18686400, 0, 0, 41, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'On waypoint 7 of path 18686400 ended - Self: Despawn instantly');


DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 22 AND `SourceEntry` = 186864 AND `SourceId` = 0;
 -- Scalecommander Azurathel smart ai
SET @ENTRY := 181056;
DELETE FROM `smart_scripts` WHERE `source_type` = 0 AND `entryOrGuid` = @ENTRY;
UPDATE `creature_template` SET `AIName` = 'SmartAI', `ScriptName` = '' WHERE `entry` = @ENTRY;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(@ENTRY, 0, 0, 1, 54, 0, 100, 0, 0, 0, 0, 0, 128, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'On just summoned - Self: Plays Anim with ID 0'),
(@ENTRY, 0, 1, 2, 61, 0, 100, 0, 0, 0, 0, 0, 59, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'On just summoned - Self: Set walk'),
(@ENTRY, 0, 2, 3, 61, 0, 100, 0, 0, 0, 0, 0, 83, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'On just summoned - Self: Remove npc flags QUESTGIVER'),
(@ENTRY, 0, 3, 0, 61, 0, 100, 0, 0, 0, 0, 0, 69, 1, 0, 0, 0, 0, 0, 8, 0, 0, 0, 5808.67, -2914.29, 207.253, 0, 'On just summoned - Self: Move to position (5808.67, -2914.29, 207.253, 0) (point id 1)'),
(@ENTRY, 0, 4, 0, 34, 0, 100, 0, 8, 1, 0, 0, 41, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'On movement of type POINT_MOTION_TYPE inform, point 1 - Self: Despawn instantly');


DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 22 AND `SourceEntry` = 181056 AND `SourceId` = 0;
 -- Scalecommander Azurathel smart ai
SET @ENTRY := 183380;
DELETE FROM `smart_scripts` WHERE `source_type` = 0 AND `entryOrGuid` = @ENTRY;
UPDATE `creature_template` SET `AIName` = 'SmartAI', `ScriptName` = '' WHERE `entry` = @ENTRY;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(@ENTRY, 0, 0, 1, 11, 0, 100, 0, 0, 0, 0, 0, 11, 362331, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'On respawn - Self: Cast spell 362331 with flags triggered on Self'),
(@ENTRY, 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 82, 16777216, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'On respawn - Self: Add npc flags SPELLCLICK'),
(@ENTRY, 0, 2, 3, 8, 0, 100, 0, 362357, 0, 0, 0, 12, 181056, 8, 0, 0, 3, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'On spell 362357 hit - Action invoker: Summon creature Scalecommander Azurathel (181056) at Self\'s position, moved by offset (0, 0, 0, 0) as summon type manual despawn, as personal spawn'),
(@ENTRY, 0, 3, 4, 61, 0, 100, 0, 0, 0, 0, 0, 33, 183380, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'On spell 362357 hit - Caster: Give kill credit Scalecommander Azurathel (183380)'),
(@ENTRY, 0, 4, 0, 61, 0, 100, 0, 0, 0, 0, 0, 41, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'On spell 362357 hit - Self: Despawn instantly');


DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 22 AND `SourceEntry` = 183380 AND `SourceId` = 0;
 -- General Purpose Bunny ZTO smart ai
SET @ENTRY := 55370;
DELETE FROM `smart_scripts` WHERE `source_type` = 0 AND `entryOrGuid` = @ENTRY;
UPDATE `creature_template` SET `AIName` = 'SmartAI', `ScriptName` = '' WHERE `entry` = @ENTRY;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(@ENTRY, 0, 0, 0, 11, 0, 100, 0, 0, 0, 13806, 0, 67, 0, 17000, 30000, 15000, 35000, 100, 0, 0, 0, 0, 0, 0, 0, 0, 'On respawn in zone 13806 - Trigger timed event timedEvent[0] in 17000 - 30000 ms and then trigger every 15000 - 35000 ms with 100% chance'),
(@ENTRY, 0, 1, 0, 59, 0, 100, 0, 0, 0, 0, 0, 11, 369927, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'On timed event timedEvent[0] triggered - Self: Cast spell 369927 on Self');


DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 22 AND `SourceEntry` = 55370 AND `SourceId` = 0;
