
ALTER TABLE `characters`
	ADD COLUMN `configId` INT(10) UNSIGNED NOT NULL DEFAULT '0' AFTER `covenant`;
	
	

-- Dumping structure for table characters.character_traits
CREATE TABLE IF NOT EXISTS `character_traits` (
  `Guid` bigint(20) unsigned NOT NULL DEFAULT '0',
  `ConfigID` int(10) unsigned NOT NULL DEFAULT '0',
  `SpecId` int(10) unsigned NOT NULL DEFAULT '0',
  `Type` int(10) unsigned NOT NULL DEFAULT '0',
  `Index` int(10) unsigned NOT NULL DEFAULT '0',
  `TalentGroup` int(10) unsigned NOT NULL DEFAULT '0',
  `ConfigName` text COLLATE utf8mb4_unicode_ci,
  PRIMARY KEY (`Guid`,`ConfigID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- Data exporting was unselected.

-- Dumping structure for table characters.character_traits_talents
CREATE TABLE IF NOT EXISTS `character_traits_talents` (
  `Guid` bigint(20) unsigned NOT NULL DEFAULT '0',
  `ConfigID` int(10) unsigned NOT NULL DEFAULT '0',
  `TraitNode` int(10) unsigned NOT NULL DEFAULT '0',
  `TraitNodeEntryID` int(10) unsigned NOT NULL DEFAULT '0',
  `Rank` int(10) unsigned NOT NULL DEFAULT '0',
  `Unk` int(10) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`Guid`,`ConfigID`,`TraitNode`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci ROW_FORMAT=DYNAMIC;
