
-- Dumping structure for table auth.battlenet_account_runeforge_memories
CREATE TABLE IF NOT EXISTS `battlenet_account_runeforge_memories` (
  `battlenetAccountId` int(10) unsigned NOT NULL,
  `blobIndex` smallint(5) unsigned NOT NULL,
  `runeForgeMask` int(10) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`battlenetAccountId`,`blobIndex`) USING BTREE,
  CONSTRAINT `battlenet_account_runeforge_memories_ibfk_1` FOREIGN KEY (`battlenetAccountId`) REFERENCES `battlenet_accounts` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci ROW_FORMAT=DYNAMIC;