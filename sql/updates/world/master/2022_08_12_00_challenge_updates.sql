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

-- Dumping structure for table world.z_custom_challenge_dungeons
CREATE TABLE IF NOT EXISTS `z_custom_challenge_dungeons` (
  `Keystone` int(10) unsigned NOT NULL DEFAULT '0',
  `ChallengeID` int(10) unsigned NOT NULL DEFAULT '0',
  `Comment` text COLLATE utf8mb4_unicode_ci,
  PRIMARY KEY (`Keystone`,`ChallengeID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- Dumping data for table world.z_custom_challenge_dungeons: ~0 rows (approximately)
/*!40000 ALTER TABLE `z_custom_challenge_dungeons` DISABLE KEYS */;
REPLACE INTO `z_custom_challenge_dungeons` (`Keystone`, `ChallengeID`, `Comment`) VALUES
	(158923, 251, 'Group - Underrot'),
	(158923, 30001, 'Group - Dreadscar Rift'),
	(158923, 30012, 'Group - Lost Glacier'),
	(158923, 30013, 'Group - Iron Docks'),
	(180653, 251, 'Solo - Underrot'),
	(180653, 30001, 'Solo - Dreadscar Rift'),
	(180653, 30012, 'Solo - Lost Glacier'),
	(180653, 30013, 'Solo - Iron Docks'),
	(700019, 30002, 'Timewalk - Maelstrom Invasion'),
	(700019, 30003, 'Timewalk - Netherlight Temple'),
	(700019, 30004, 'Timewalk - Niskara'),
	(700019, 30005, 'Timewalk - Telogrus Rift'),
	(700019, 30006, 'Timewalk - Peak of Serenity'),
	(700019, 30007, 'Timewalk - Shado-Pan Monastary'),
	(700019, 30008, 'Timewalk - Elarian Sanctuary'),
	(700019, 30010, 'Timewalk - Crapopolis'),
	(700019, 30011, 'Timewalk - Skyhold');
/*!40000 ALTER TABLE `z_custom_challenge_dungeons` ENABLE KEYS */;

/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;
/*!40014 SET FOREIGN_KEY_CHECKS=IFNULL(@OLD_FOREIGN_KEY_CHECKS, 1) */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40111 SET SQL_NOTES=IFNULL(@OLD_SQL_NOTES, 1) */;

REPLACE INTO `item_script_names` (`Id`, `ScriptName`) VALUES (700019, 'item_challenge_key');
