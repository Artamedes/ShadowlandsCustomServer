-- few paths
DROP TABLE IF EXISTS `waypoint_data_addon`;
-- Dumping structure for table world.waypoint_data_addon
CREATE TABLE IF NOT EXISTS `waypoint_data_addon` (
  `PathID` int(10) unsigned NOT NULL DEFAULT '0',
  `PointID` int(10) unsigned NOT NULL DEFAULT '0',
  `SplinePointIndex` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `PositionX` float NOT NULL DEFAULT '0',
  `PositionY` float NOT NULL DEFAULT '0',
  `PositionZ` float NOT NULL DEFAULT '0',
  PRIMARY KEY (`PathID`,`PointID`,`SplinePointIndex`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

REPLACE INTO `creature_addon` (`guid`, `path_id`, `mount`, `MountCreatureID`, `bytes1`, `bytes2`, `emote`, `aiAnimKit`, `movementAnimKit`, `meleeAnimKit`, `visibilityDistanceType`, `auras`) VALUES (1081654, 10816540, 17906, 0, 0, 0, 0, 0, 0, 0, 0, NULL);
UPDATE creature SET movementtype = 2 WHERE guid = 1081654;