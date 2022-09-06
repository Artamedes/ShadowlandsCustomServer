-- { 1549.18f, -246.875f, 126.009f, 0.880659f }, 

UPDATE playercreateinfo SET position_x = 1549.18, position_y = -246.875, position_z = 126.009, orientation = 0.880659, map = 2444;

REPLACE INTO `playercreateinfo` (`race`, `class`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `npe_map`, `npe_position_x`, `npe_position_y`, `npe_position_z`, `npe_orientation`, `npe_transport_guid`, `intro_movie_id`, `intro_scene_id`, `npe_intro_scene_id`) VALUES (52, 13, 1116, 1855.65, 4620.45, 340.895, 0.278168, 1116, 1855.65, 4620.45, 340.895, 0.278168, 0, NULL, NULL, 2236);
REPLACE INTO `playercreateinfo` (`race`, `class`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `npe_map`, `npe_position_x`, `npe_position_y`, `npe_position_z`, `npe_orientation`, `npe_transport_guid`, `intro_movie_id`, `intro_scene_id`, `npe_intro_scene_id`) VALUES (70, 13, 1116, 1855.65, 4620.45, 340.895, 0.278168, 1116, 1855.65, 4620.45, 340.895, 0.278168, 0, NULL, NULL, 2236);

REPLACE INTO `class_expansion_requirement` (`ClassID`, `RaceID`, `ActiveExpansionLevel`, `AccountExpansionLevel`) VALUES (13, 70, 0, 0);
REPLACE INTO `class_expansion_requirement` (`ClassID`, `RaceID`, `ActiveExpansionLevel`, `AccountExpansionLevel`) VALUES (13, 52, 0, 0);

-- --------------------------------------------------------
-- Host:                         127.0.0.1
-- Server version:               5.7.37-log - MySQL Community Server (GPL)
-- Server OS:                    Win64
-- HeidiSQL Version:             11.3.0.6295
-- --------------------------------------------------------

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!50503 SET NAMES utf8mb4 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

DROP TABLE if EXISTS `class_expansion_requirement`;

-- Dumping structure for table world.class_expansion_requirement
CREATE TABLE IF NOT EXISTS `class_expansion_requirement` (
  `Primary` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `ClassID` tinyint(3) unsigned NOT NULL,
  `RaceID` tinyint(3) unsigned NOT NULL,
  `ActiveExpansionLevel` tinyint(3) unsigned DEFAULT '0',
  `AccountExpansionLevel` tinyint(3) unsigned DEFAULT '0',
  PRIMARY KEY (`Primary`) USING BTREE
) ENGINE=InnoDB AUTO_INCREMENT=223 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- Dumping data for table world.class_expansion_requirement: ~0 rows (approximately)
/*!40000 ALTER TABLE `class_expansion_requirement` DISABLE KEYS */;
INSERT INTO `class_expansion_requirement` (`Primary`, `ClassID`, `RaceID`, `ActiveExpansionLevel`, `AccountExpansionLevel`) VALUES
	(1, 13, 70, 0, 0),
	(2, 13, 52, 0, 0),
	(3, 1, 1, 0, 0),
	(4, 2, 1, 0, 0),
	(5, 4, 1, 0, 0),
	(6, 5, 1, 0, 0),
	(7, 8, 1, 0, 0),
	(8, 9, 1, 0, 0),
	(9, 6, 1, 2, 0),
	(10, 3, 1, 0, 0),
	(11, 10, 1, 4, 0),
	(12, 1, 8, 0, 0),
	(13, 4, 8, 0, 0),
	(14, 3, 8, 0, 0),
	(15, 5, 8, 0, 0),
	(16, 7, 8, 0, 0),
	(17, 8, 8, 0, 0),
	(18, 6, 8, 2, 0),
	(19, 11, 8, 0, 0),
	(20, 9, 8, 0, 0),
	(21, 10, 8, 4, 0),
	(22, 1, 11, 0, 0),
	(23, 2, 11, 0, 0),
	(24, 3, 11, 0, 0),
	(25, 5, 11, 0, 0),
	(26, 8, 11, 0, 0),
	(27, 7, 11, 0, 0),
	(28, 6, 11, 2, 0),
	(29, 10, 11, 4, 0),
	(30, 4, 11, 0, 0),
	(31, 3, 10, 0, 0),
	(32, 4, 10, 0, 0),
	(33, 5, 10, 0, 0),
	(34, 8, 10, 0, 0),
	(35, 9, 10, 0, 0),
	(36, 2, 10, 0, 0),
	(37, 6, 10, 2, 0),
	(38, 1, 10, 0, 0),
	(39, 10, 10, 4, 0),
	(40, 12, 10, 0, 0),
	(41, 1, 4, 0, 0),
	(42, 3, 4, 0, 0),
	(43, 4, 4, 0, 0),
	(44, 5, 4, 0, 0),
	(45, 11, 4, 0, 0),
	(46, 6, 4, 2, 0),
	(47, 8, 4, 0, 0),
	(48, 10, 4, 4, 0),
	(49, 12, 4, 0, 0),
	(50, 1, 3, 0, 0),
	(51, 2, 3, 0, 0),
	(52, 3, 3, 0, 0),
	(53, 5, 3, 0, 0),
	(54, 4, 3, 0, 0),
	(55, 6, 3, 2, 0),
	(56, 8, 3, 0, 0),
	(57, 7, 3, 0, 0),
	(58, 9, 3, 0, 0),
	(59, 10, 3, 4, 0),
	(60, 1, 25, 0, 0),
	(61, 7, 25, 0, 0),
	(62, 4, 25, 0, 0),
	(63, 5, 25, 0, 0),
	(64, 10, 25, 4, 0),
	(65, 8, 25, 0, 0),
	(66, 3, 25, 0, 0),
	(67, 6, 25, 2, 8),
	(68, 1, 6, 0, 0),
	(69, 3, 6, 0, 0),
	(70, 7, 6, 0, 0),
	(71, 11, 6, 0, 0),
	(72, 6, 6, 2, 0),
	(73, 5, 6, 0, 0),
	(74, 2, 6, 0, 0),
	(75, 10, 6, 4, 0),
	(76, 8, 6, 0, 0),
	(77, 4, 6, 0, 0),
	(78, 1, 2, 0, 0),
	(79, 3, 2, 0, 0),
	(80, 4, 2, 0, 0),
	(81, 7, 2, 0, 0),
	(82, 9, 2, 0, 0),
	(83, 6, 2, 2, 0),
	(84, 8, 2, 0, 0),
	(85, 10, 2, 4, 0),
	(86, 5, 2, 0, 0),
	(87, 1, 7, 0, 0),
	(88, 4, 7, 0, 0),
	(89, 8, 7, 0, 0),
	(90, 9, 7, 0, 0),
	(91, 6, 7, 2, 0),
	(92, 5, 7, 0, 0),
	(93, 10, 7, 4, 0),
	(94, 3, 7, 0, 0),
	(95, 6, 9, 2, 0),
	(96, 3, 9, 0, 0),
	(97, 8, 9, 0, 0),
	(98, 5, 9, 0, 0),
	(99, 4, 9, 0, 0),
	(100, 7, 9, 0, 0),
	(101, 9, 9, 0, 0),
	(102, 1, 9, 0, 0),
	(103, 7, 31, 7, 7),
	(104, 11, 31, 7, 7),
	(105, 3, 31, 7, 7),
	(106, 8, 31, 7, 7),
	(107, 5, 31, 7, 7),
	(108, 4, 31, 7, 7),
	(109, 1, 31, 7, 7),
	(110, 10, 31, 7, 7),
	(111, 2, 31, 7, 7),
	(112, 6, 31, 7, 8),
	(113, 2, 30, 6, 7),
	(114, 3, 30, 6, 7),
	(115, 8, 30, 6, 7),
	(116, 5, 30, 6, 7),
	(117, 1, 30, 6, 7),
	(118, 6, 30, 6, 8),
	(119, 4, 30, 6, 7),
	(120, 3, 28, 6, 7),
	(121, 11, 28, 6, 7),
	(122, 7, 28, 6, 7),
	(123, 1, 28, 6, 7),
	(124, 10, 28, 6, 7),
	(125, 6, 28, 6, 8),
	(126, 8, 28, 6, 7),
	(127, 4, 28, 6, 7),
	(128, 5, 28, 6, 7),
	(129, 6, 22, 2, 0),
	(130, 11, 22, 0, 0),
	(131, 3, 22, 0, 0),
	(132, 8, 22, 0, 0),
	(133, 4, 22, 0, 0),
	(134, 5, 22, 0, 0),
	(135, 9, 22, 0, 0),
	(136, 1, 22, 0, 0),
	(137, 1, 34, 7, 7),
	(138, 3, 34, 7, 7),
	(139, 8, 34, 7, 7),
	(140, 10, 34, 7, 7),
	(141, 2, 34, 7, 7),
	(142, 5, 34, 7, 7),
	(143, 4, 34, 7, 7),
	(144, 7, 34, 7, 7),
	(145, 9, 34, 7, 7),
	(146, 6, 34, 7, 8),
	(147, 1, 35, 7, 7),
	(148, 4, 35, 7, 7),
	(149, 10, 35, 7, 7),
	(150, 3, 35, 7, 7),
	(151, 5, 35, 7, 7),
	(152, 8, 35, 7, 7),
	(153, 9, 35, 7, 7),
	(154, 7, 35, 7, 7),
	(155, 6, 35, 7, 8),
	(156, 1, 36, 7, 7),
	(157, 3, 36, 7, 7),
	(158, 8, 36, 7, 7),
	(159, 10, 36, 7, 7),
	(160, 5, 36, 7, 7),
	(161, 4, 36, 7, 7),
	(162, 7, 36, 7, 7),
	(163, 6, 36, 7, 8),
	(164, 3, 24, 0, 0),
	(165, 8, 24, 0, 0),
	(166, 10, 24, 4, 0),
	(167, 5, 24, 0, 0),
	(168, 4, 24, 0, 0),
	(169, 7, 24, 0, 0),
	(170, 1, 24, 0, 0),
	(171, 6, 24, 2, 8),
	(172, 1, 26, 0, 0),
	(173, 3, 26, 0, 0),
	(174, 4, 26, 0, 0),
	(175, 5, 26, 0, 0),
	(176, 7, 26, 0, 0),
	(177, 8, 26, 0, 0),
	(178, 10, 26, 4, 0),
	(179, 6, 26, 2, 8),
	(180, 1, 37, 7, 7),
	(181, 4, 37, 7, 7),
	(182, 10, 37, 7, 7),
	(183, 3, 37, 7, 7),
	(184, 5, 37, 7, 7),
	(185, 8, 37, 7, 7),
	(186, 9, 37, 7, 7),
	(187, 6, 37, 7, 8),
	(188, 8, 27, 6, 7),
	(189, 3, 27, 6, 7),
	(190, 10, 27, 6, 7),
	(191, 5, 27, 6, 7),
	(192, 4, 27, 6, 7),
	(193, 9, 27, 6, 7),
	(194, 1, 27, 6, 7),
	(195, 6, 27, 6, 8),
	(196, 13, 70, 0, 0),
	(197, 13, 52, 0, 0),
	(198, 8, 29, 6, 7),
	(199, 9, 29, 6, 7),
	(200, 3, 29, 6, 7),
	(201, 10, 29, 6, 7),
	(202, 5, 29, 6, 7),
	(203, 4, 29, 6, 7),
	(204, 1, 29, 6, 7),
	(205, 6, 29, 6, 8),
	(206, 1, 32, 7, 7),
	(207, 3, 32, 7, 7),
	(208, 4, 32, 7, 7),
	(209, 5, 32, 7, 7),
	(210, 8, 32, 7, 7),
	(211, 7, 32, 7, 7),
	(212, 11, 32, 7, 7),
	(213, 10, 32, 7, 7),
	(214, 6, 32, 7, 8),
	(215, 1, 5, 0, 0),
	(216, 4, 5, 0, 0),
	(217, 5, 5, 0, 0),
	(218, 8, 5, 0, 0),
	(219, 9, 5, 0, 0),
	(220, 6, 5, 2, 0),
	(221, 3, 5, 0, 0),
	(222, 10, 5, 4, 0);
/*!40000 ALTER TABLE `class_expansion_requirement` ENABLE KEYS */;

/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;
/*!40014 SET FOREIGN_KEY_CHECKS=IFNULL(@OLD_FOREIGN_KEY_CHECKS, 1) */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40111 SET SQL_NOTES=IFNULL(@OLD_SQL_NOTES, 1) */;
REPLACE INTO `race_unlock_requirement` (`raceID`, `expansion`, `achievementId`) VALUES (52, 0, 0);
REPLACE INTO `race_unlock_requirement` (`raceID`, `expansion`, `achievementId`) VALUES (70, 0, 0);

REPLACE INTO `player_classlevelstats` (`class`, `level`, `str`, `agi`, `sta`, `inte`, `VerifiedBuild`) VALUES (13, 1, 17, 12, 23, 14, 41079);
REPLACE INTO `player_classlevelstats` (`class`, `level`, `str`, `agi`, `sta`, `inte`, `VerifiedBuild`) VALUES (13, 2, 18, 13, 25, 15, 0);
REPLACE INTO `player_classlevelstats` (`class`, `level`, `str`, `agi`, `sta`, `inte`, `VerifiedBuild`) VALUES (13, 3, 20, 14, 27, 16, 0);
REPLACE INTO `player_classlevelstats` (`class`, `level`, `str`, `agi`, `sta`, `inte`, `VerifiedBuild`) VALUES (13, 4, 22, 15, 29, 18, 0);
REPLACE INTO `player_classlevelstats` (`class`, `level`, `str`, `agi`, `sta`, `inte`, `VerifiedBuild`) VALUES (13, 5, 24, 17, 31, 19, 0);
REPLACE INTO `player_classlevelstats` (`class`, `level`, `str`, `agi`, `sta`, `inte`, `VerifiedBuild`) VALUES (13, 6, 26, 18, 33, 20, 0);
REPLACE INTO `player_classlevelstats` (`class`, `level`, `str`, `agi`, `sta`, `inte`, `VerifiedBuild`) VALUES (13, 7, 28, 20, 34, 22, 0);
REPLACE INTO `player_classlevelstats` (`class`, `level`, `str`, `agi`, `sta`, `inte`, `VerifiedBuild`) VALUES (13, 8, 29, 21, 36, 23, 0);
REPLACE INTO `player_classlevelstats` (`class`, `level`, `str`, `agi`, `sta`, `inte`, `VerifiedBuild`) VALUES (13, 9, 31, 22, 38, 24, 0);
REPLACE INTO `player_classlevelstats` (`class`, `level`, `str`, `agi`, `sta`, `inte`, `VerifiedBuild`) VALUES (13, 10, 33, 23, 40, 26, 40906);
REPLACE INTO `player_classlevelstats` (`class`, `level`, `str`, `agi`, `sta`, `inte`, `VerifiedBuild`) VALUES (13, 11, 36, 25, 42, 27, 40120);
REPLACE INTO `player_classlevelstats` (`class`, `level`, `str`, `agi`, `sta`, `inte`, `VerifiedBuild`) VALUES (13, 12, 39, 27, 43, 29, 40120);
REPLACE INTO `player_classlevelstats` (`class`, `level`, `str`, `agi`, `sta`, `inte`, `VerifiedBuild`) VALUES (13, 13, 43, 30, 45, 30, 40120);
REPLACE INTO `player_classlevelstats` (`class`, `level`, `str`, `agi`, `sta`, `inte`, `VerifiedBuild`) VALUES (13, 14, 46, 32, 46, 31, 40120);
REPLACE INTO `player_classlevelstats` (`class`, `level`, `str`, `agi`, `sta`, `inte`, `VerifiedBuild`) VALUES (13, 15, 48, 33, 48, 33, 40120);
REPLACE INTO `player_classlevelstats` (`class`, `level`, `str`, `agi`, `sta`, `inte`, `VerifiedBuild`) VALUES (13, 16, 50, 35, 50, 34, 40120);
REPLACE INTO `player_classlevelstats` (`class`, `level`, `str`, `agi`, `sta`, `inte`, `VerifiedBuild`) VALUES (13, 17, 52, 36, 51, 35, 40120);
REPLACE INTO `player_classlevelstats` (`class`, `level`, `str`, `agi`, `sta`, `inte`, `VerifiedBuild`) VALUES (13, 18, 54, 37, 52, 37, 40120);
REPLACE INTO `player_classlevelstats` (`class`, `level`, `str`, `agi`, `sta`, `inte`, `VerifiedBuild`) VALUES (13, 19, 56, 39, 54, 38, 40120);
REPLACE INTO `player_classlevelstats` (`class`, `level`, `str`, `agi`, `sta`, `inte`, `VerifiedBuild`) VALUES (13, 20, 58, 40, 55, 39, 40120);
REPLACE INTO `player_classlevelstats` (`class`, `level`, `str`, `agi`, `sta`, `inte`, `VerifiedBuild`) VALUES (13, 21, 60, 41, 57, 41, 0);
REPLACE INTO `player_classlevelstats` (`class`, `level`, `str`, `agi`, `sta`, `inte`, `VerifiedBuild`) VALUES (13, 22, 62, 43, 59, 42, 0);
REPLACE INTO `player_classlevelstats` (`class`, `level`, `str`, `agi`, `sta`, `inte`, `VerifiedBuild`) VALUES (13, 23, 64, 44, 61, 44, 0);
REPLACE INTO `player_classlevelstats` (`class`, `level`, `str`, `agi`, `sta`, `inte`, `VerifiedBuild`) VALUES (13, 24, 66, 46, 63, 45, 0);
REPLACE INTO `player_classlevelstats` (`class`, `level`, `str`, `agi`, `sta`, `inte`, `VerifiedBuild`) VALUES (13, 25, 68, 47, 65, 46, 0);
REPLACE INTO `player_classlevelstats` (`class`, `level`, `str`, `agi`, `sta`, `inte`, `VerifiedBuild`) VALUES (13, 26, 70, 48, 67, 48, 0);
REPLACE INTO `player_classlevelstats` (`class`, `level`, `str`, `agi`, `sta`, `inte`, `VerifiedBuild`) VALUES (13, 27, 72, 50, 69, 49, 0);
REPLACE INTO `player_classlevelstats` (`class`, `level`, `str`, `agi`, `sta`, `inte`, `VerifiedBuild`) VALUES (13, 28, 74, 51, 71, 51, 0);
REPLACE INTO `player_classlevelstats` (`class`, `level`, `str`, `agi`, `sta`, `inte`, `VerifiedBuild`) VALUES (13, 29, 77, 53, 73, 52, 0);
REPLACE INTO `player_classlevelstats` (`class`, `level`, `str`, `agi`, `sta`, `inte`, `VerifiedBuild`) VALUES (13, 30, 79, 55, 75, 54, 0);
REPLACE INTO `player_classlevelstats` (`class`, `level`, `str`, `agi`, `sta`, `inte`, `VerifiedBuild`) VALUES (13, 31, 82, 56, 78, 56, 0);
REPLACE INTO `player_classlevelstats` (`class`, `level`, `str`, `agi`, `sta`, `inte`, `VerifiedBuild`) VALUES (13, 32, 84, 58, 80, 57, 36949);
REPLACE INTO `player_classlevelstats` (`class`, `level`, `str`, `agi`, `sta`, `inte`, `VerifiedBuild`) VALUES (13, 33, 87, 60, 83, 59, 36949);
REPLACE INTO `player_classlevelstats` (`class`, `level`, `str`, `agi`, `sta`, `inte`, `VerifiedBuild`) VALUES (13, 34, 90, 62, 86, 61, 36949);
REPLACE INTO `player_classlevelstats` (`class`, `level`, `str`, `agi`, `sta`, `inte`, `VerifiedBuild`) VALUES (13, 35, 93, 64, 88, 63, 37474);
REPLACE INTO `player_classlevelstats` (`class`, `level`, `str`, `agi`, `sta`, `inte`, `VerifiedBuild`) VALUES (13, 36, 96, 66, 91, 65, 37474);
REPLACE INTO `player_classlevelstats` (`class`, `level`, `str`, `agi`, `sta`, `inte`, `VerifiedBuild`) VALUES (13, 37, 99, 68, 94, 67, 0);
REPLACE INTO `player_classlevelstats` (`class`, `level`, `str`, `agi`, `sta`, `inte`, `VerifiedBuild`) VALUES (13, 38, 102, 71, 97, 70, 0);
REPLACE INTO `player_classlevelstats` (`class`, `level`, `str`, `agi`, `sta`, `inte`, `VerifiedBuild`) VALUES (13, 39, 106, 73, 101, 72, 0);
REPLACE INTO `player_classlevelstats` (`class`, `level`, `str`, `agi`, `sta`, `inte`, `VerifiedBuild`) VALUES (13, 40, 109, 76, 104, 74, 0);
REPLACE INTO `player_classlevelstats` (`class`, `level`, `str`, `agi`, `sta`, `inte`, `VerifiedBuild`) VALUES (13, 41, 113, 78, 108, 77, 0);
REPLACE INTO `player_classlevelstats` (`class`, `level`, `str`, `agi`, `sta`, `inte`, `VerifiedBuild`) VALUES (13, 42, 117, 81, 112, 80, 0);
REPLACE INTO `player_classlevelstats` (`class`, `level`, `str`, `agi`, `sta`, `inte`, `VerifiedBuild`) VALUES (13, 43, 121, 84, 116, 82, 0);
REPLACE INTO `player_classlevelstats` (`class`, `level`, `str`, `agi`, `sta`, `inte`, `VerifiedBuild`) VALUES (13, 44, 126, 87, 120, 85, 0);
REPLACE INTO `player_classlevelstats` (`class`, `level`, `str`, `agi`, `sta`, `inte`, `VerifiedBuild`) VALUES (13, 45, 130, 90, 124, 88, 0);
REPLACE INTO `player_classlevelstats` (`class`, `level`, `str`, `agi`, `sta`, `inte`, `VerifiedBuild`) VALUES (13, 46, 135, 93, 128, 92, 41031);
REPLACE INTO `player_classlevelstats` (`class`, `level`, `str`, `agi`, `sta`, `inte`, `VerifiedBuild`) VALUES (13, 47, 140, 96, 133, 95, 41488);
REPLACE INTO `player_classlevelstats` (`class`, `level`, `str`, `agi`, `sta`, `inte`, `VerifiedBuild`) VALUES (13, 48, 145, 100, 138, 98, 0);
REPLACE INTO `player_classlevelstats` (`class`, `level`, `str`, `agi`, `sta`, `inte`, `VerifiedBuild`) VALUES (13, 49, 150, 103, 143, 102, 0);
REPLACE INTO `player_classlevelstats` (`class`, `level`, `str`, `agi`, `sta`, `inte`, `VerifiedBuild`) VALUES (13, 50, 155, 107, 148, 106, 41079);
REPLACE INTO `player_classlevelstats` (`class`, `level`, `str`, `agi`, `sta`, `inte`, `VerifiedBuild`) VALUES (13, 51, 193, 133, 187, 131, 0);
REPLACE INTO `player_classlevelstats` (`class`, `level`, `str`, `agi`, `sta`, `inte`, `VerifiedBuild`) VALUES (13, 52, 208, 143, 204, 141, 0);
REPLACE INTO `player_classlevelstats` (`class`, `level`, `str`, `agi`, `sta`, `inte`, `VerifiedBuild`) VALUES (13, 53, 224, 154, 223, 152, 0);
REPLACE INTO `player_classlevelstats` (`class`, `level`, `str`, `agi`, `sta`, `inte`, `VerifiedBuild`) VALUES (13, 54, 241, 166, 244, 164, 0);
REPLACE INTO `player_classlevelstats` (`class`, `level`, `str`, `agi`, `sta`, `inte`, `VerifiedBuild`) VALUES (13, 55, 260, 179, 267, 177, 0);
REPLACE INTO `player_classlevelstats` (`class`, `level`, `str`, `agi`, `sta`, `inte`, `VerifiedBuild`) VALUES (13, 56, 280, 193, 292, 190, 0);
REPLACE INTO `player_classlevelstats` (`class`, `level`, `str`, `agi`, `sta`, `inte`, `VerifiedBuild`) VALUES (13, 57, 299, 206, 317, 203, 0);
REPLACE INTO `player_classlevelstats` (`class`, `level`, `str`, `agi`, `sta`, `inte`, `VerifiedBuild`) VALUES (13, 58, 319, 220, 343, 217, 0);
REPLACE INTO `player_classlevelstats` (`class`, `level`, `str`, `agi`, `sta`, `inte`, `VerifiedBuild`) VALUES (13, 59, 340, 235, 372, 231, 0);
REPLACE INTO `player_classlevelstats` (`class`, `level`, `str`, `agi`, `sta`, `inte`, `VerifiedBuild`) VALUES (13, 60, 450, 310, 414, 306, 40120);

REPLACE INTO `player_racestats` (`race`, `str`, `agi`, `sta`, `inte`) VALUES (52, -2, 1, -1, 2);
REPLACE INTO `player_racestats` (`race`, `str`, `agi`, `sta`, `inte`) VALUES (70, -2, 1, -1, 2);
