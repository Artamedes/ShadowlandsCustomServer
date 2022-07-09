
ALTER TABLE `waypoint_data` ADD COLUMN `velocity` FLOAT DEFAULT 0 NOT NULL AFTER `orientation`;

ALTER TABLE `waypoint_data` 
ADD COLUMN `smoothTransition` tinyint UNSIGNED NOT NULL DEFAULT 0 AFTER `delay`;

UPDATE `waypoint_data` SET `smoothTransition`= 1 WHERE `delay` < 0;
UPDATE `waypoint_data` SET `delay`= 0 WHERE `delay` < 0;


ALTER TABLE `waypoint_data` 
MODIFY COLUMN `delay` int UNSIGNED NOT NULL DEFAULT 0 AFTER `velocity`;

DELETE FROM waypoint_data WHERE id = 10530340;
REPLACE INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `orientation`, `velocity`, `delay`, `smoothTransition`, `move_type`, `action`, `action_chance`, `wpguid`) VALUES (10530340, 1, 3874.9, 2827.95, 754.231, 0.98125, 0, 0, 0, 0, 0, 100, 1056188);
REPLACE INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `orientation`, `velocity`, `delay`, `smoothTransition`, `move_type`, `action`, `action_chance`, `wpguid`) VALUES (10530340, 2, 3848.45, 2790.41, 747.765, 4.09994, 0, 0, 1, 0, 0, 100, 1056194);
REPLACE INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `orientation`, `velocity`, `delay`, `smoothTransition`, `move_type`, `action`, `action_chance`, `wpguid`) VALUES (10530340, 3, 3874.2, 2827.88, 754.231, 0.955073, 0, 0, 0, 0, 0, 100, 1056201);
