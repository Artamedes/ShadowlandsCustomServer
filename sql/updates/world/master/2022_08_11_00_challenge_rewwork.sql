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

-- Dumping structure for table world.z_group_challenge_level_info
CREATE TABLE IF NOT EXISTS `z_group_challenge_level_info` (
  `ChallengeLevel` int(10) unsigned NOT NULL DEFAULT '0',
  `BaseHPScaling` int(10) unsigned NOT NULL DEFAULT '1',
  `BaseDmgScaling` int(10) unsigned NOT NULL DEFAULT '1',
  `HPScalingPerPlayer` int(10) unsigned NOT NULL DEFAULT '1',
  `DMGScalingPerPlayer` int(10) unsigned NOT NULL DEFAULT '1',
  PRIMARY KEY (`ChallengeLevel`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- Dumping data for table world.z_group_challenge_level_info: ~0 rows (approximately)
/*!40000 ALTER TABLE `z_group_challenge_level_info` DISABLE KEYS */;
/*!40000 ALTER TABLE `z_group_challenge_level_info` ENABLE KEYS */;

-- Dumping structure for table world.z_solo_challenge_level_info
CREATE TABLE IF NOT EXISTS `z_solo_challenge_level_info` (
  `ChallengeLevel` int(10) unsigned NOT NULL DEFAULT '0',
  `BaseHPScaling` int(10) unsigned NOT NULL DEFAULT '1',
  `BaseDmgScaling` int(10) unsigned NOT NULL DEFAULT '1',
  `HPScalingPerPlayer` int(10) unsigned NOT NULL DEFAULT '1',
  `DMGScalingPerPlayer` int(10) unsigned NOT NULL DEFAULT '1',
  PRIMARY KEY (`ChallengeLevel`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci ROW_FORMAT=DYNAMIC;

-- Dumping data for table world.z_solo_challenge_level_info: ~0 rows (approximately)
/*!40000 ALTER TABLE `z_solo_challenge_level_info` DISABLE KEYS */;
/*!40000 ALTER TABLE `z_solo_challenge_level_info` ENABLE KEYS */;

/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;
/*!40014 SET FOREIGN_KEY_CHECKS=IFNULL(@OLD_FOREIGN_KEY_CHECKS, 1) */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40111 SET SQL_NOTES=IFNULL(@OLD_SQL_NOTES, 1) */;
