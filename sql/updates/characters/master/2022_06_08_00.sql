-- Dumping structure for table characters.account_achievement
CREATE TABLE IF NOT EXISTS `account_achievement` (
  `account` int(10) unsigned NOT NULL DEFAULT '0',
  `achievement` int(10) unsigned NOT NULL,
  `first_guid` bigint(20) unsigned NOT NULL DEFAULT '0',
  `date` bigint(20) NOT NULL DEFAULT '0',
  PRIMARY KEY (`account`,`achievement`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci ROW_FORMAT=DYNAMIC;