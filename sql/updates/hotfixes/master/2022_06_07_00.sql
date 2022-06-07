-- Dumping structure for table hotfixes.vignette
CREATE TABLE IF NOT EXISTS `vignette` (
  `ID` int(10) unsigned NOT NULL DEFAULT '0',
  `Name` text COLLATE utf8mb4_unicode_ci,
  `PlayerConditionID` int(10) unsigned NOT NULL DEFAULT '0',
  `VisibleTrackingQuestID` int(10) unsigned NOT NULL DEFAULT '0',
  `QuestFeedbackEffectId` int(10) unsigned NOT NULL DEFAULT '0',
  `Flags` int(10) unsigned NOT NULL DEFAULT '0',
  `MaxHeight` float unsigned NOT NULL DEFAULT '0',
  `MinHeight` float unsigned NOT NULL DEFAULT '0',
  `VignetteType` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `RewardQuestID` int(10) unsigned NOT NULL DEFAULT '0',
  `UiWidgetSetID` int(10) unsigned NOT NULL DEFAULT '0',
  `VerifiedBuild` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`,`VerifiedBuild`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci ROW_FORMAT=DYNAMIC;
