-- --------------------------------------------------------
-- Host:                         127.0.0.1
-- Server version:               5.7.37-log - MySQL Community Server (GPL)
-- Server OS:                    Win64
-- HeidiSQL Version:             11.3.0.6295
-- --------------------------------------------------------

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES latin1 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

-- Dumping structure for table hotfixes.garr_talent_cost
CREATE TABLE IF NOT EXISTS `garr_talent_cost` (
  `MoneyQuantity` bigint(20) NOT NULL DEFAULT '0',
  `ID` int(10) unsigned NOT NULL DEFAULT '0',
  `GarrTalentTreeID` int(11) NOT NULL DEFAULT '0',
  `GarrTalentID` int(11) NOT NULL DEFAULT '0',
  `RankIndex` int(11) NOT NULL DEFAULT '0',
  `GarrTalentRankID` int(11) NOT NULL DEFAULT '0',
  `CostType` int(11) NOT NULL DEFAULT '0',
  `CurrencyTypesID` int(11) NOT NULL DEFAULT '0',
  `CurrencyQuantity` int(11) NOT NULL DEFAULT '0',
  `VerifiedBuild` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`,`VerifiedBuild`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci ROW_FORMAT=DYNAMIC;

-- Data exporting was unselected.

/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;
/*!40014 SET FOREIGN_KEY_CHECKS=IFNULL(@OLD_FOREIGN_KEY_CHECKS, 1) */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40111 SET SQL_NOTES=IFNULL(@OLD_SQL_NOTES, 1) */;
