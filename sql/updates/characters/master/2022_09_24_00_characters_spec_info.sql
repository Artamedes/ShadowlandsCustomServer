
-- Dumping structure for table characters.character_spec_info
CREATE TABLE IF NOT EXISTS `character_spec_info` (
  `Guid` bigint(20) unsigned NOT NULL DEFAULT '0',
  `SpecId` int(10) unsigned NOT NULL DEFAULT '0',
  `LoadoutID` int(10) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`Guid`,`SpecId`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci ROW_FORMAT=DYNAMIC;
