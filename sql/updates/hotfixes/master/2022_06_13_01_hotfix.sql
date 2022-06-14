-- Dumping structure for table hotfixes.runeforge_legendary_ability
CREATE TABLE IF NOT EXISTS `runeforge_legendary_ability` (
  `Name` text COLLATE utf8mb4_unicode_ci,
  `ID` int(10) unsigned NOT NULL DEFAULT '0',
  `SpecSetID` int(11) unsigned NOT NULL DEFAULT '0',
  `InventoryTypeMask` int(11) unsigned NOT NULL DEFAULT '0',
  `SpellID` int(10) unsigned NOT NULL DEFAULT '0',
  `ItemBonusListID` int(11) unsigned NOT NULL DEFAULT '0',
  `PlayerConditionID` int(10) unsigned NOT NULL DEFAULT '0',
  `Unk` int(10) unsigned NOT NULL DEFAULT '0',
  `UnlockItemID` int(10) unsigned NOT NULL DEFAULT '0',
  `CovenantID` int(10) unsigned NOT NULL DEFAULT '0',
  `PlayerConditionID2` int(10) unsigned NOT NULL DEFAULT '0',
  `VerifiedBuild` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`,`VerifiedBuild`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci ROW_FORMAT=DYNAMIC;