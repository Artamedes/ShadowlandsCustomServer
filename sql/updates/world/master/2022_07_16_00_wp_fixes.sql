
UPDATE creature SET position_x = 225.732, position_y = -2754.68, position_z = 102.78 WHERE guid = 1081654;

DELETE FROM waypoint_data WHERE id IN (10816540, 10816700);
DELETE FROM waypoint_data_addon WHERE pathid IN (10816540, 10816700);

REPLACE INTO `waypoint_data_addon` (`PathID`, `PointID`, `SplinePointIndex`, `PositionX`, `PositionY`, `PositionZ`) VALUES (10816540, 0, 0, 223.672, -2754.77, 102.778);
REPLACE INTO `waypoint_data_addon` (`PathID`, `PointID`, `SplinePointIndex`, `PositionX`, `PositionY`, `PositionZ`) VALUES (10816540, 0, 1, 227.133, -2754.74, 101.996);
REPLACE INTO `waypoint_data_addon` (`PathID`, `PointID`, `SplinePointIndex`, `PositionX`, `PositionY`, `PositionZ`) VALUES (10816540, 0, 2, 240.066, -2754.63, 100.709);
REPLACE INTO `waypoint_data_addon` (`PathID`, `PointID`, `SplinePointIndex`, `PositionX`, `PositionY`, `PositionZ`) VALUES (10816540, 0, 3, 258.56, -2754.47, 100.372);
REPLACE INTO `waypoint_data_addon` (`PathID`, `PointID`, `SplinePointIndex`, `PositionX`, `PositionY`, `PositionZ`) VALUES (10816540, 0, 4, 271.761, -2752.81, 100.933);
REPLACE INTO `waypoint_data_addon` (`PathID`, `PointID`, `SplinePointIndex`, `PositionX`, `PositionY`, `PositionZ`) VALUES (10816540, 0, 5, 281.37, -2745.61, 100.916);
REPLACE INTO `waypoint_data_addon` (`PathID`, `PointID`, `SplinePointIndex`, `PositionX`, `PositionY`, `PositionZ`) VALUES (10816540, 0, 6, 287.905, -2735.02, 100.773);
REPLACE INTO `waypoint_data_addon` (`PathID`, `PointID`, `SplinePointIndex`, `PositionX`, `PositionY`, `PositionZ`) VALUES (10816540, 0, 7, 290.44, -2724.16, 100.827);
REPLACE INTO `waypoint_data_addon` (`PathID`, `PointID`, `SplinePointIndex`, `PositionX`, `PositionY`, `PositionZ`) VALUES (10816540, 0, 8, 290.884, -2711.74, 100.991);
REPLACE INTO `waypoint_data_addon` (`PathID`, `PointID`, `SplinePointIndex`, `PositionX`, `PositionY`, `PositionZ`) VALUES (10816540, 0, 9, 289.661, -2687.78, 101.394);
REPLACE INTO `waypoint_data_addon` (`PathID`, `PointID`, `SplinePointIndex`, `PositionX`, `PositionY`, `PositionZ`) VALUES (10816540, 0, 10, 284.259, -2645.72, 101.361);
REPLACE INTO `waypoint_data_addon` (`PathID`, `PointID`, `SplinePointIndex`, `PositionX`, `PositionY`, `PositionZ`) VALUES (10816540, 0, 11, 287.881, -2611.95, 101.361);
REPLACE INTO `waypoint_data_addon` (`PathID`, `PointID`, `SplinePointIndex`, `PositionX`, `PositionY`, `PositionZ`) VALUES (10816540, 0, 12, 282.793, -2591.6, 101.361);
REPLACE INTO `waypoint_data_addon` (`PathID`, `PointID`, `SplinePointIndex`, `PositionX`, `PositionY`, `PositionZ`) VALUES (10816540, 0, 13, 261.158, -2568.25, 102.364);
REPLACE INTO `waypoint_data_addon` (`PathID`, `PointID`, `SplinePointIndex`, `PositionX`, `PositionY`, `PositionZ`) VALUES (10816540, 0, 14, 255.108, -2554.47, 103.573);
REPLACE INTO `waypoint_data_addon` (`PathID`, `PointID`, `SplinePointIndex`, `PositionX`, `PositionY`, `PositionZ`) VALUES (10816540, 1, 0, 253.689, -2554.27, 103.545);
REPLACE INTO `waypoint_data_addon` (`PathID`, `PointID`, `SplinePointIndex`, `PositionX`, `PositionY`, `PositionZ`) VALUES (10816540, 1, 1, 266.712, -2573.03, 101.782);
REPLACE INTO `waypoint_data_addon` (`PathID`, `PointID`, `SplinePointIndex`, `PositionX`, `PositionY`, `PositionZ`) VALUES (10816540, 1, 2, 284.678, -2596.07, 101.36);
REPLACE INTO `waypoint_data_addon` (`PathID`, `PointID`, `SplinePointIndex`, `PositionX`, `PositionY`, `PositionZ`) VALUES (10816540, 1, 3, 286.872, -2605.26, 101.36);
REPLACE INTO `waypoint_data_addon` (`PathID`, `PointID`, `SplinePointIndex`, `PositionX`, `PositionY`, `PositionZ`) VALUES (10816540, 1, 4, 283.386, -2649.31, 101.36);
REPLACE INTO `waypoint_data_addon` (`PathID`, `PointID`, `SplinePointIndex`, `PositionX`, `PositionY`, `PositionZ`) VALUES (10816540, 1, 5, 287.649, -2675.59, 101.36);
REPLACE INTO `waypoint_data_addon` (`PathID`, `PointID`, `SplinePointIndex`, `PositionX`, `PositionY`, `PositionZ`) VALUES (10816540, 1, 6, 292.811, -2706.96, 100.986);
REPLACE INTO `waypoint_data_addon` (`PathID`, `PointID`, `SplinePointIndex`, `PositionX`, `PositionY`, `PositionZ`) VALUES (10816540, 1, 7, 286.942, -2736.51, 100.788);
REPLACE INTO `waypoint_data_addon` (`PathID`, `PointID`, `SplinePointIndex`, `PositionX`, `PositionY`, `PositionZ`) VALUES (10816540, 1, 8, 268.475, -2750.89, 100.924);
REPLACE INTO `waypoint_data_addon` (`PathID`, `PointID`, `SplinePointIndex`, `PositionX`, `PositionY`, `PositionZ`) VALUES (10816540, 1, 9, 247.858, -2754.72, 100.709);

REPLACE INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `orientation`, `velocity`, `delay`, `smoothTransition`, `move_type`, `action`, `action_chance`, `wpguid`) VALUES (10816540, 0, 253.4, -2550.14, 103.943, 0, 0, 4000, 0, 0, 0, 0, 0);
REPLACE INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `orientation`, `velocity`, `delay`, `smoothTransition`, `move_type`, `action`, `action_chance`, `wpguid`) VALUES (10816540, 1, 224.779, -2754.37, 102.649, 0, 0, 4000, 0, 0, 0, 0, 0);
REPLACE INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `orientation`, `velocity`, `delay`, `smoothTransition`, `move_type`, `action`, `action_chance`, `wpguid`) VALUES (10816540, 2, 224.779, -2754.37, 102.649, 0, 0, 0, 0, 0, 0, 0, 0);

DELETE FROM creature WHERE guid IN (1081723, 1081722, 1081726, 1081706, 1081704);
DELETE FROM creature_addon WHERE guid IN (1081723, 1081722, 1081726, 1081706, 1081704);

UPDATE creature SET movementtype = 2 WHERE guid IN (1081671, 1081670);
REPLACE INTO `creature_addon` (`guid`, `path_id`, `mount`, `MountCreatureID`, `bytes1`, `bytes2`, `emote`, `aiAnimKit`, `movementAnimKit`, `meleeAnimKit`, `visibilityDistanceType`, `auras`) VALUES (1081670, 10816700, 0, 0, 0, 257, 0, 0, 0, 0, 0, NULL);

REPLACE INTO `creature_addon` (`guid`, `path_id`, `mount`, `MountCreatureID`, `bytes1`, `bytes2`, `emote`, `aiAnimKit`, `movementAnimKit`, `meleeAnimKit`, `visibilityDistanceType`, `auras`) VALUES (1081671, 10816700, 0, 0, 0, 257, 0, 0, 0, 0, 0, NULL);

REPLACE INTO `waypoint_data_addon` (`PathID`, `PointID`, `SplinePointIndex`, `PositionX`, `PositionY`, `PositionZ`) VALUES (10816700, 0, 0, 208.089, -2471.02, 107.395);
REPLACE INTO `waypoint_data_addon` (`PathID`, `PointID`, `SplinePointIndex`, `PositionX`, `PositionY`, `PositionZ`) VALUES (10816700, 0, 1, 194.101, -2473.46, 107.395);
REPLACE INTO `waypoint_data_addon` (`PathID`, `PointID`, `SplinePointIndex`, `PositionX`, `PositionY`, `PositionZ`) VALUES (10816700, 0, 2, 168.985, -2470.94, 107.368);
REPLACE INTO `waypoint_data_addon` (`PathID`, `PointID`, `SplinePointIndex`, `PositionX`, `PositionY`, `PositionZ`) VALUES (10816700, 0, 3, 160.08, -2467.79, 107.368);
REPLACE INTO `waypoint_data_addon` (`PathID`, `PointID`, `SplinePointIndex`, `PositionX`, `PositionY`, `PositionZ`) VALUES (10816700, 0, 4, 133.129, -2458.83, 107.368);
REPLACE INTO `waypoint_data_addon` (`PathID`, `PointID`, `SplinePointIndex`, `PositionX`, `PositionY`, `PositionZ`) VALUES (10816700, 0, 5, 110.079, -2468.07, 104.999);
REPLACE INTO `waypoint_data_addon` (`PathID`, `PointID`, `SplinePointIndex`, `PositionX`, `PositionY`, `PositionZ`) VALUES (10816700, 0, 6, 96.6645, -2488.93, 102.901);
REPLACE INTO `waypoint_data_addon` (`PathID`, `PointID`, `SplinePointIndex`, `PositionX`, `PositionY`, `PositionZ`) VALUES (10816700, 0, 7, 95.7811, -2500.51, 102.78);
REPLACE INTO `waypoint_data_addon` (`PathID`, `PointID`, `SplinePointIndex`, `PositionX`, `PositionY`, `PositionZ`) VALUES (10816700, 0, 8, 95.7004, -2524.49, 102.779);
REPLACE INTO `waypoint_data_addon` (`PathID`, `PointID`, `SplinePointIndex`, `PositionX`, `PositionY`, `PositionZ`) VALUES (10816700, 0, 9, 93.5068, -2549.75, 102.288);
REPLACE INTO `waypoint_data_addon` (`PathID`, `PointID`, `SplinePointIndex`, `PositionX`, `PositionY`, `PositionZ`) VALUES (10816700, 0, 10, 109.169, -2557.94, 102.779);
REPLACE INTO `waypoint_data_addon` (`PathID`, `PointID`, `SplinePointIndex`, `PositionX`, `PositionY`, `PositionZ`) VALUES (10816700, 0, 11, 137.08, -2556.82, 102.755);
REPLACE INTO `waypoint_data_addon` (`PathID`, `PointID`, `SplinePointIndex`, `PositionX`, `PositionY`, `PositionZ`) VALUES (10816700, 0, 12, 171.875, -2555.33, 102.778);
REPLACE INTO `waypoint_data_addon` (`PathID`, `PointID`, `SplinePointIndex`, `PositionX`, `PositionY`, `PositionZ`) VALUES (10816700, 0, 13, 207.955, -2554.21, 102.778);
REPLACE INTO `waypoint_data_addon` (`PathID`, `PointID`, `SplinePointIndex`, `PositionX`, `PositionY`, `PositionZ`) VALUES (10816700, 0, 14, 231.001, -2551.84, 103.09);
REPLACE INTO `waypoint_data_addon` (`PathID`, `PointID`, `SplinePointIndex`, `PositionX`, `PositionY`, `PositionZ`) VALUES (10816700, 0, 15, 243.264, -2544.19, 104.401);
REPLACE INTO `waypoint_data_addon` (`PathID`, `PointID`, `SplinePointIndex`, `PositionX`, `PositionY`, `PositionZ`) VALUES (10816700, 0, 16, 248.135, -2534.77, 105.728);
REPLACE INTO `waypoint_data_addon` (`PathID`, `PointID`, `SplinePointIndex`, `PositionX`, `PositionY`, `PositionZ`) VALUES (10816700, 0, 17, 249.91, -2510.78, 107.358);
REPLACE INTO `waypoint_data_addon` (`PathID`, `PointID`, `SplinePointIndex`, `PositionX`, `PositionY`, `PositionZ`) VALUES (10816700, 0, 18, 248.167, -2487.7, 107.388);
REPLACE INTO `waypoint_data_addon` (`PathID`, `PointID`, `SplinePointIndex`, `PositionX`, `PositionY`, `PositionZ`) VALUES (10816700, 0, 19, 217.816, -2470.14, 107.395);

REPLACE INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `orientation`, `velocity`, `delay`, `smoothTransition`, `move_type`, `action`, `action_chance`, `wpguid`) VALUES (10816710, 0, 225.559, -2469.2, 107.395, 0, 0, 0, 0, 0, 0, 0, 0);
REPLACE INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `orientation`, `velocity`, `delay`, `smoothTransition`, `move_type`, `action`, `action_chance`, `wpguid`) VALUES (10816700, 0, 208.089, -2471.02, 107.395, 0, 0, 0, 0, 0, 0, 0, 0);

REPLACE INTO `waypoint_data_addon` (`PathID`, `PointID`, `SplinePointIndex`, `PositionX`, `PositionY`, `PositionZ`) VALUES (10816710, 0, 0, 227.223, -2469.67, 107.395);
REPLACE INTO `waypoint_data_addon` (`PathID`, `PointID`, `SplinePointIndex`, `PositionX`, `PositionY`, `PositionZ`) VALUES (10816710, 0, 1, 250.902, -2484.8, 107.388);
REPLACE INTO `waypoint_data_addon` (`PathID`, `PointID`, `SplinePointIndex`, `PositionX`, `PositionY`, `PositionZ`) VALUES (10816710, 0, 2, 253.831, -2497.2, 107.388);
REPLACE INTO `waypoint_data_addon` (`PathID`, `PointID`, `SplinePointIndex`, `PositionX`, `PositionY`, `PositionZ`) VALUES (10816710, 0, 3, 252.105, -2517.78, 107.227);
REPLACE INTO `waypoint_data_addon` (`PathID`, `PointID`, `SplinePointIndex`, `PositionX`, `PositionY`, `PositionZ`) VALUES (10816710, 0, 4, 249.08, -2531.68, 106.078);
REPLACE INTO `waypoint_data_addon` (`PathID`, `PointID`, `SplinePointIndex`, `PositionX`, `PositionY`, `PositionZ`) VALUES (10816710, 0, 5, 233.422, -2552.94, 103.15);
REPLACE INTO `waypoint_data_addon` (`PathID`, `PointID`, `SplinePointIndex`, `PositionX`, `PositionY`, `PositionZ`) VALUES (10816710, 0, 6, 214.49, -2556.27, 102.793);
REPLACE INTO `waypoint_data_addon` (`PathID`, `PointID`, `SplinePointIndex`, `PositionX`, `PositionY`, `PositionZ`) VALUES (10816710, 0, 7, 204.175, -2555.93, 102.78);
REPLACE INTO `waypoint_data_addon` (`PathID`, `PointID`, `SplinePointIndex`, `PositionX`, `PositionY`, `PositionZ`) VALUES (10816710, 0, 8, 178.388, -2557.41, 102.78);
REPLACE INTO `waypoint_data_addon` (`PathID`, `PointID`, `SplinePointIndex`, `PositionX`, `PositionY`, `PositionZ`) VALUES (10816710, 0, 9, 156.905, -2558.57, 102.779);
REPLACE INTO `waypoint_data_addon` (`PathID`, `PointID`, `SplinePointIndex`, `PositionX`, `PositionY`, `PositionZ`) VALUES (10816710, 0, 10, 131.12, -2558.25, 102.778);
REPLACE INTO `waypoint_data_addon` (`PathID`, `PointID`, `SplinePointIndex`, `PositionX`, `PositionY`, `PositionZ`) VALUES (10816710, 0, 11, 110.668, -2553.58, 102.778);
REPLACE INTO `waypoint_data_addon` (`PathID`, `PointID`, `SplinePointIndex`, `PositionX`, `PositionY`, `PositionZ`) VALUES (10816710, 0, 12, 100.382, -2539.91, 102.777);
REPLACE INTO `waypoint_data_addon` (`PathID`, `PointID`, `SplinePointIndex`, `PositionX`, `PositionY`, `PositionZ`) VALUES (10816710, 0, 13, 98.7491, -2518.14, 102.778);
REPLACE INTO `waypoint_data_addon` (`PathID`, `PointID`, `SplinePointIndex`, `PositionX`, `PositionY`, `PositionZ`) VALUES (10816710, 0, 14, 98.8187, -2492.88, 102.903);
REPLACE INTO `waypoint_data_addon` (`PathID`, `PointID`, `SplinePointIndex`, `PositionX`, `PositionY`, `PositionZ`) VALUES (10816710, 0, 15, 111.097, -2472.1, 105.016);
REPLACE INTO `waypoint_data_addon` (`PathID`, `PointID`, `SplinePointIndex`, `PositionX`, `PositionY`, `PositionZ`) VALUES (10816710, 0, 16, 124.649, -2464.98, 106.92);
REPLACE INTO `waypoint_data_addon` (`PathID`, `PointID`, `SplinePointIndex`, `PositionX`, `PositionY`, `PositionZ`) VALUES (10816710, 0, 17, 145.994, -2464.07, 107.369);
REPLACE INTO `waypoint_data_addon` (`PathID`, `PointID`, `SplinePointIndex`, `PositionX`, `PositionY`, `PositionZ`) VALUES (10816710, 0, 18, 177.929, -2474.07, 107.394);
REPLACE INTO `waypoint_data_addon` (`PathID`, `PointID`, `SplinePointIndex`, `PositionX`, `PositionY`, `PositionZ`) VALUES (10816710, 0, 19, 210.136, -2473.18, 107.394);
