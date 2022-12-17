-- --------------------------------------------------------
-- Host:                         127.0.0.1
-- Server Version:               8.0.30 - MySQL Community Server - GPL
-- Server Betriebssystem:        Win64
-- HeidiSQL Version:             10.3.0.5771
-- --------------------------------------------------------

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!50503 SET NAMES utf8mb4 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;

-- Exportiere Struktur von Tabelle world.treasure_picker_bonus
CREATE TABLE IF NOT EXISTS `treasure_picker_bonus` (
  `treasure_picker` int NOT NULL DEFAULT '0',
  `id` int NOT NULL DEFAULT '0',
  `bonus_money` int NOT NULL DEFAULT '0',
  `unkbit` int NOT NULL DEFAULT '0',
  PRIMARY KEY (`treasure_picker`,`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- Exportiere Daten aus Tabelle world.treasure_picker_bonus: ~0 rows (ungefähr)
DELETE FROM `treasure_picker_bonus`;
/*!40000 ALTER TABLE `treasure_picker_bonus` DISABLE KEYS */;
/*!40000 ALTER TABLE `treasure_picker_bonus` ENABLE KEYS */;

-- Exportiere Struktur von Tabelle world.treasure_picker_currency
CREATE TABLE IF NOT EXISTS `treasure_picker_currency` (
  `treasure_picker` int NOT NULL DEFAULT '0',
  `bonus_id` int NOT NULL DEFAULT '0',
  `idx` int NOT NULL DEFAULT '0',
  `currency` int NOT NULL DEFAULT '0',
  `amount` int DEFAULT NULL,
  `money_reward` int DEFAULT NULL,
  PRIMARY KEY (`treasure_picker`,`bonus_id`,`idx`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- Exportiere Daten aus Tabelle world.treasure_picker_currency: ~0 rows (ungefähr)
DELETE FROM `treasure_picker_currency`;
/*!40000 ALTER TABLE `treasure_picker_currency` DISABLE KEYS */;
/*!40000 ALTER TABLE `treasure_picker_currency` ENABLE KEYS */;

-- Exportiere Struktur von Tabelle world.treasure_picker_entry
CREATE TABLE IF NOT EXISTS `treasure_picker_entry` (
  `id` int NOT NULL AUTO_INCREMENT,
  `money_reward` int DEFAULT NULL,
  `flags` int DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=2320 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- Exportiere Daten aus Tabelle world.treasure_picker_entry: ~0 rows (ungefähr)
DELETE FROM `treasure_picker_entry`;
/*!40000 ALTER TABLE `treasure_picker_entry` DISABLE KEYS */;
INSERT INTO `treasure_picker_entry` (`id`, `money_reward`, `flags`) VALUES
	(2057, 0, 0),
	(2058, 0, 0),
	(2059, 0, 0),
	(2060, 0, 0),
	(2061, 0, 0),
	(2062, 0, 0),
	(2063, 0, 0),
	(2064, 0, 0),
	(2068, 0, 0),
	(2069, 0, 0),
	(2070, 0, 0),
	(2071, 0, 0),
	(2072, 0, 0),
	(2073, 0, 0),
	(2074, 0, 0),
	(2168, 0, 0),
	(2319, 0, 16);
/*!40000 ALTER TABLE `treasure_picker_entry` ENABLE KEYS */;

-- Exportiere Struktur von Tabelle world.treasure_picker_item
CREATE TABLE IF NOT EXISTS `treasure_picker_item` (
  `treasure_picker` int NOT NULL DEFAULT '0',
  `bonus_id` tinyint NOT NULL DEFAULT '0',
  `idx` int NOT NULL DEFAULT '0',
  `item` int NOT NULL DEFAULT '0',
  `quantity` int DEFAULT NULL,
  `modifier_list` text,
  `modifier_value_list` text,
  `bonus_list` text,
  PRIMARY KEY (`treasure_picker`,`bonus_id`,`idx`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- Exportiere Daten aus Tabelle world.treasure_picker_item: ~0 rows (ungefähr)
DELETE FROM `treasure_picker_item`;
/*!40000 ALTER TABLE `treasure_picker_item` DISABLE KEYS */;
INSERT INTO `treasure_picker_item` (`treasure_picker`, `bonus_id`, `idx`, `item`, `quantity`, `modifier_list`, `modifier_value_list`, `bonus_list`) VALUES
	(2057, 0, 0, 193481, 1, '28', '2150', '8774'),
	(2058, 0, 0, 191805, 1, '28', '2150', '8774'),
	(2059, 0, 0, 191806, 1, '28', '2150', '8774'),
	(2060, 0, 0, 193914, 1, '28', '2150', '8774'),
	(2061, 0, 0, 191812, 1, '28', '2150', '8774'),
	(2062, 0, 0, 191811, 1, '28', '2150', '8774'),
	(2063, 0, 0, 191809, 1, '28', '2150', '8774'),
	(2064, 0, 0, 193916, 1, '28', '2150', '8774'),
	(2068, 0, 0, 194422, 1, '28', '2150', '8774'),
	(2069, 0, 0, 191807, 1, '28', '2150', '8774'),
	(2070, 0, 0, 194333, 1, '28', '2150', '8774'),
	(2071, 0, 0, 194335, 1, '28', '2150', '8774'),
	(2072, 0, 0, 191810, 1, '28', '2150', '8774'),
	(2073, 0, 0, 194109, 1, '28', '2150', '8774'),
	(2074, 0, 0, 191808, 1, '28', '2150', '8774'),
	(2168, 0, 0, 194676, 1, '28', '2150', ''),
	(2319, 0, 0, 201702, 1, '28', '872', '');
/*!40000 ALTER TABLE `treasure_picker_item` ENABLE KEYS */;

/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;
/*!40014 SET FOREIGN_KEY_CHECKS=IF(@OLD_FOREIGN_KEY_CHECKS IS NULL, 1, @OLD_FOREIGN_KEY_CHECKS) */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
