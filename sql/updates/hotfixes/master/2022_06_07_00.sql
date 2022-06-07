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

REPLACE INTO `vignette` (`ID`, `Name`, `PlayerConditionID`, `VisibleTrackingQuestID`, `QuestFeedbackEffectId`, `Flags`, `MaxHeight`, `MinHeight`, `VignetteType`, `RewardQuestID`, `UiWidgetSetID`, `VerifiedBuild`) VALUES (700104, 'Unknown Entity', 0, 0, 89, 0, 0, 0, 0, 0, 0, 0);
REPLACE INTO `vignette` (`ID`, `Name`, `PlayerConditionID`, `VisibleTrackingQuestID`, `QuestFeedbackEffectId`, `Flags`, `MaxHeight`, `MinHeight`, `VignetteType`, `RewardQuestID`, `UiWidgetSetID`, `VerifiedBuild`) VALUES (700105, 'Corrupted Granite Elemental', 0, 0, 89, 0, 0, 0, 0, 0, 0, 0);
REPLACE INTO `vignette` (`ID`, `Name`, `PlayerConditionID`, `VisibleTrackingQuestID`, `QuestFeedbackEffectId`, `Flags`, `MaxHeight`, `MinHeight`, `VignetteType`, `RewardQuestID`, `UiWidgetSetID`, `VerifiedBuild`) VALUES (700112, 'Sir Duke Iro', 0, 0, 89, 0, 0, 0, 0, 0, 0, 0);
REPLACE INTO `vignette` (`ID`, `Name`, `PlayerConditionID`, `VisibleTrackingQuestID`, `QuestFeedbackEffectId`, `Flags`, `MaxHeight`, `MinHeight`, `VignetteType`, `RewardQuestID`, `UiWidgetSetID`, `VerifiedBuild`) VALUES (700211, 'Mawsworn Annihilator', 0, 0, 89, 0, 0, 0, 0, 0, 0, 0);
REPLACE INTO `vignette` (`ID`, `Name`, `PlayerConditionID`, `VisibleTrackingQuestID`, `QuestFeedbackEffectId`, `Flags`, `MaxHeight`, `MinHeight`, `VignetteType`, `RewardQuestID`, `UiWidgetSetID`, `VerifiedBuild`) VALUES (700214, 'Mawsworn Defiler', 0, 0, 89, 0, 0, 0, 0, 0, 0, 0);
REPLACE INTO `vignette` (`ID`, `Name`, `PlayerConditionID`, `VisibleTrackingQuestID`, `QuestFeedbackEffectId`, `Flags`, `MaxHeight`, `MinHeight`, `VignetteType`, `RewardQuestID`, `UiWidgetSetID`, `VerifiedBuild`) VALUES (700220, 'Warden of Souls', 0, 0, 89, 0, 0, 0, 0, 0, 0, 0);
REPLACE INTO `vignette` (`ID`, `Name`, `PlayerConditionID`, `VisibleTrackingQuestID`, `QuestFeedbackEffectId`, `Flags`, `MaxHeight`, `MinHeight`, `VignetteType`, `RewardQuestID`, `UiWidgetSetID`, `VerifiedBuild`) VALUES (700221, 'Synod', 0, 0, 89, 0, 0, 0, 0, 0, 0, 0);
REPLACE INTO `vignette` (`ID`, `Name`, `PlayerConditionID`, `VisibleTrackingQuestID`, `QuestFeedbackEffectId`, `Flags`, `MaxHeight`, `MinHeight`, `VignetteType`, `RewardQuestID`, `UiWidgetSetID`, `VerifiedBuild`) VALUES (700303, 'Herald of Odyn', 0, 0, 89, 0, 0, 0, 0, 0, 0, 0);
REPLACE INTO `vignette` (`ID`, `Name`, `PlayerConditionID`, `VisibleTrackingQuestID`, `QuestFeedbackEffectId`, `Flags`, `MaxHeight`, `MinHeight`, `VignetteType`, `RewardQuestID`, `UiWidgetSetID`, `VerifiedBuild`) VALUES (700311, 'God-King Skovald', 0, 0, 89, 0, 0, 0, 0, 0, 0, 0);
REPLACE INTO `vignette` (`ID`, `Name`, `PlayerConditionID`, `VisibleTrackingQuestID`, `QuestFeedbackEffectId`, `Flags`, `MaxHeight`, `MinHeight`, `VignetteType`, `RewardQuestID`, `UiWidgetSetID`, `VerifiedBuild`) VALUES (700312, 'Odyn', 0, 0, 89, 0, 0, 0, 0, 0, 0, 0);
REPLACE INTO `vignette` (`ID`, `Name`, `PlayerConditionID`, `VisibleTrackingQuestID`, `QuestFeedbackEffectId`, `Flags`, `MaxHeight`, `MinHeight`, `VignetteType`, `RewardQuestID`, `UiWidgetSetID`, `VerifiedBuild`) VALUES (700313, 'Hymdall', 0, 0, 89, 0, 0, 0, 0, 0, 0, 0);
REPLACE INTO `vignette` (`ID`, `Name`, `PlayerConditionID`, `VisibleTrackingQuestID`, `QuestFeedbackEffectId`, `Flags`, `MaxHeight`, `MinHeight`, `VignetteType`, `RewardQuestID`, `UiWidgetSetID`, `VerifiedBuild`) VALUES (700314, 'Dyzall', 0, 0, 89, 0, 0, 0, 0, 0, 0, 0);
REPLACE INTO `vignette` (`ID`, `Name`, `PlayerConditionID`, `VisibleTrackingQuestID`, `QuestFeedbackEffectId`, `Flags`, `MaxHeight`, `MinHeight`, `VignetteType`, `RewardQuestID`, `UiWidgetSetID`, `VerifiedBuild`) VALUES (700316, 'Dark Ascended Corrus', 0, 0, 89, 0, 0, 0, 0, 0, 0, 0);
REPLACE INTO `vignette` (`ID`, `Name`, `PlayerConditionID`, `VisibleTrackingQuestID`, `QuestFeedbackEffectId`, `Flags`, `MaxHeight`, `MinHeight`, `VignetteType`, `RewardQuestID`, `UiWidgetSetID`, `VerifiedBuild`) VALUES (700400, 'Allmus', 0, 0, 89, 0, 0, 0, 0, 0, 0, 0);
REPLACE INTO `vignette` (`ID`, `Name`, `PlayerConditionID`, `VisibleTrackingQuestID`, `QuestFeedbackEffectId`, `Flags`, `MaxHeight`, `MinHeight`, `VignetteType`, `RewardQuestID`, `UiWidgetSetID`, `VerifiedBuild`) VALUES (700401, 'Mevra', 0, 0, 89, 0, 0, 0, 0, 0, 0, 0);
REPLACE INTO `vignette` (`ID`, `Name`, `PlayerConditionID`, `VisibleTrackingQuestID`, `QuestFeedbackEffectId`, `Flags`, `MaxHeight`, `MinHeight`, `VignetteType`, `RewardQuestID`, `UiWidgetSetID`, `VerifiedBuild`) VALUES (700402, 'Derza', 0, 0, 89, 0, 0, 0, 0, 0, 0, 0);
REPLACE INTO `vignette` (`ID`, `Name`, `PlayerConditionID`, `VisibleTrackingQuestID`, `QuestFeedbackEffectId`, `Flags`, `MaxHeight`, `MinHeight`, `VignetteType`, `RewardQuestID`, `UiWidgetSetID`, `VerifiedBuild`) VALUES (700411, 'Watcher of Death', 0, 0, 89, 0, 0, 0, 0, 0, 0, 0);
REPLACE INTO `vignette` (`ID`, `Name`, `PlayerConditionID`, `VisibleTrackingQuestID`, `QuestFeedbackEffectId`, `Flags`, `MaxHeight`, `MinHeight`, `VignetteType`, `RewardQuestID`, `UiWidgetSetID`, `VerifiedBuild`) VALUES (700506, 'Oglaz', 0, 0, 89, 0, 0, 0, 0, 0, 0, 0);
REPLACE INTO `vignette` (`ID`, `Name`, `PlayerConditionID`, `VisibleTrackingQuestID`, `QuestFeedbackEffectId`, `Flags`, `MaxHeight`, `MinHeight`, `VignetteType`, `RewardQuestID`, `UiWidgetSetID`, `VerifiedBuild`) VALUES (700507, 'Jaz\'golluth', 0, 0, 89, 0, 0, 0, 0, 0, 0, 0);
REPLACE INTO `vignette` (`ID`, `Name`, `PlayerConditionID`, `VisibleTrackingQuestID`, `QuestFeedbackEffectId`, `Flags`, `MaxHeight`, `MinHeight`, `VignetteType`, `RewardQuestID`, `UiWidgetSetID`, `VerifiedBuild`) VALUES (700508, 'Annaxin', 0, 0, 89, 0, 0, 0, 0, 0, 0, 0);
REPLACE INTO `vignette` (`ID`, `Name`, `PlayerConditionID`, `VisibleTrackingQuestID`, `QuestFeedbackEffectId`, `Flags`, `MaxHeight`, `MinHeight`, `VignetteType`, `RewardQuestID`, `UiWidgetSetID`, `VerifiedBuild`) VALUES (700511, 'Avatar of Gul\'dan', 0, 0, 89, 0, 0, 0, 0, 0, 0, 0);
REPLACE INTO `vignette` (`ID`, `Name`, `PlayerConditionID`, `VisibleTrackingQuestID`, `QuestFeedbackEffectId`, `Flags`, `MaxHeight`, `MinHeight`, `VignetteType`, `RewardQuestID`, `UiWidgetSetID`, `VerifiedBuild`) VALUES (700607, 'Void Reaper', 0, 0, 89, 0, 0, 0, 0, 0, 0, 0);
REPLACE INTO `vignette` (`ID`, `Name`, `PlayerConditionID`, `VisibleTrackingQuestID`, `QuestFeedbackEffectId`, `Flags`, `MaxHeight`, `MinHeight`, `VignetteType`, `RewardQuestID`, `UiWidgetSetID`, `VerifiedBuild`) VALUES (700616, 'Rarkon', 0, 0, 89, 0, 0, 0, 0, 0, 0, 0);
REPLACE INTO `vignette` (`ID`, `Name`, `PlayerConditionID`, `VisibleTrackingQuestID`, `QuestFeedbackEffectId`, `Flags`, `MaxHeight`, `MinHeight`, `VignetteType`, `RewardQuestID`, `UiWidgetSetID`, `VerifiedBuild`) VALUES (700620, 'Agony', 0, 0, 89, 0, 0, 0, 0, 0, 0, 0);
REPLACE INTO `vignette` (`ID`, `Name`, `PlayerConditionID`, `VisibleTrackingQuestID`, `QuestFeedbackEffectId`, `Flags`, `MaxHeight`, `MinHeight`, `VignetteType`, `RewardQuestID`, `UiWidgetSetID`, `VerifiedBuild`) VALUES (700626, 'Sorza', 0, 0, 89, 0, 0, 0, 0, 0, 0, 0);
REPLACE INTO `vignette` (`ID`, `Name`, `PlayerConditionID`, `VisibleTrackingQuestID`, `QuestFeedbackEffectId`, `Flags`, `MaxHeight`, `MinHeight`, `VignetteType`, `RewardQuestID`, `UiWidgetSetID`, `VerifiedBuild`) VALUES (700705, 'Betzalel', 0, 0, 89, 0, 0, 0, 0, 0, 0, 0);
REPLACE INTO `vignette` (`ID`, `Name`, `PlayerConditionID`, `VisibleTrackingQuestID`, `QuestFeedbackEffectId`, `Flags`, `MaxHeight`, `MinHeight`, `VignetteType`, `RewardQuestID`, `UiWidgetSetID`, `VerifiedBuild`) VALUES (700706, 'Ju-Won Brightdraft', 0, 0, 89, 0, 0, 0, 0, 0, 0, 0);
REPLACE INTO `vignette` (`ID`, `Name`, `PlayerConditionID`, `VisibleTrackingQuestID`, `QuestFeedbackEffectId`, `Flags`, `MaxHeight`, `MinHeight`, `VignetteType`, `RewardQuestID`, `UiWidgetSetID`, `VerifiedBuild`) VALUES (700707, 'Yin Li Loudlight', 0, 0, 89, 0, 0, 0, 0, 0, 0, 0);
REPLACE INTO `vignette` (`ID`, `Name`, `PlayerConditionID`, `VisibleTrackingQuestID`, `QuestFeedbackEffectId`, `Flags`, `MaxHeight`, `MinHeight`, `VignetteType`, `RewardQuestID`, `UiWidgetSetID`, `VerifiedBuild`) VALUES (700708, 'Zaphiel', 0, 0, 89, 0, 0, 0, 0, 0, 0, 0);
REPLACE INTO `vignette` (`ID`, `Name`, `PlayerConditionID`, `VisibleTrackingQuestID`, `QuestFeedbackEffectId`, `Flags`, `MaxHeight`, `MinHeight`, `VignetteType`, `RewardQuestID`, `UiWidgetSetID`, `VerifiedBuild`) VALUES (700712, 'Kang-Dae Whitegarden', 0, 0, 89, 0, 0, 0, 0, 0, 0, 0);
REPLACE INTO `vignette` (`ID`, `Name`, `PlayerConditionID`, `VisibleTrackingQuestID`, `QuestFeedbackEffectId`, `Flags`, `MaxHeight`, `MinHeight`, `VignetteType`, `RewardQuestID`, `UiWidgetSetID`, `VerifiedBuild`) VALUES (700713, 'Lord Darius', 0, 0, 89, 0, 0, 0, 0, 0, 0, 0);
REPLACE INTO `vignette` (`ID`, `Name`, `PlayerConditionID`, `VisibleTrackingQuestID`, `QuestFeedbackEffectId`, `Flags`, `MaxHeight`, `MinHeight`, `VignetteType`, `RewardQuestID`, `UiWidgetSetID`, `VerifiedBuild`) VALUES (700714, 'Rehael', 0, 0, 89, 0, 0, 0, 0, 0, 0, 0);
REPLACE INTO `vignette` (`ID`, `Name`, `PlayerConditionID`, `VisibleTrackingQuestID`, `QuestFeedbackEffectId`, `Flags`, `MaxHeight`, `MinHeight`, `VignetteType`, `RewardQuestID`, `UiWidgetSetID`, `VerifiedBuild`) VALUES (700715, 'Yofiel', 0, 0, 89, 0, 0, 0, 0, 0, 0, 0);
REPLACE INTO `vignette` (`ID`, `Name`, `PlayerConditionID`, `VisibleTrackingQuestID`, `QuestFeedbackEffectId`, `Flags`, `MaxHeight`, `MinHeight`, `VignetteType`, `RewardQuestID`, `UiWidgetSetID`, `VerifiedBuild`) VALUES (700721, 'Ernoch', 0, 0, 89, 0, 0, 0, 0, 0, 0, 0);
REPLACE INTO `vignette` (`ID`, `Name`, `PlayerConditionID`, `VisibleTrackingQuestID`, `QuestFeedbackEffectId`, `Flags`, `MaxHeight`, `MinHeight`, `VignetteType`, `RewardQuestID`, `UiWidgetSetID`, `VerifiedBuild`) VALUES (700722, 'Kairos', 0, 0, 89, 0, 0, 0, 0, 0, 0, 0);
REPLACE INTO `vignette` (`ID`, `Name`, `PlayerConditionID`, `VisibleTrackingQuestID`, `QuestFeedbackEffectId`, `Flags`, `MaxHeight`, `MinHeight`, `VignetteType`, `RewardQuestID`, `UiWidgetSetID`, `VerifiedBuild`) VALUES (700723, 'Allmus', 0, 0, 89, 0, 0, 0, 0, 0, 0, 0);
REPLACE INTO `vignette` (`ID`, `Name`, `PlayerConditionID`, `VisibleTrackingQuestID`, `QuestFeedbackEffectId`, `Flags`, `MaxHeight`, `MinHeight`, `VignetteType`, `RewardQuestID`, `UiWidgetSetID`, `VerifiedBuild`) VALUES (700724, 'Torzas', 0, 0, 89, 0, 0, 0, 0, 0, 0, 0);
REPLACE INTO `vignette` (`ID`, `Name`, `PlayerConditionID`, `VisibleTrackingQuestID`, `QuestFeedbackEffectId`, `Flags`, `MaxHeight`, `MinHeight`, `VignetteType`, `RewardQuestID`, `UiWidgetSetID`, `VerifiedBuild`) VALUES (700812, 'Sir Duke Iro', 0, 0, 89, 0, 0, 0, 0, 0, 0, 0);
REPLACE INTO `vignette` (`ID`, `Name`, `PlayerConditionID`, `VisibleTrackingQuestID`, `QuestFeedbackEffectId`, `Flags`, `MaxHeight`, `MinHeight`, `VignetteType`, `RewardQuestID`, `UiWidgetSetID`, `VerifiedBuild`) VALUES (700813, 'Mawsworn Annihilator', 0, 0, 89, 0, 0, 0, 0, 0, 0, 0);
REPLACE INTO `vignette` (`ID`, `Name`, `PlayerConditionID`, `VisibleTrackingQuestID`, `QuestFeedbackEffectId`, `Flags`, `MaxHeight`, `MinHeight`, `VignetteType`, `RewardQuestID`, `UiWidgetSetID`, `VerifiedBuild`) VALUES (700815, 'Maw Guardian', 0, 0, 89, 0, 0, 0, 0, 0, 0, 0);
REPLACE INTO `vignette` (`ID`, `Name`, `PlayerConditionID`, `VisibleTrackingQuestID`, `QuestFeedbackEffectId`, `Flags`, `MaxHeight`, `MinHeight`, `VignetteType`, `RewardQuestID`, `UiWidgetSetID`, `VerifiedBuild`) VALUES (700816, 'Urgoz', 0, 0, 89, 0, 0, 0, 0, 0, 0, 0);
REPLACE INTO `vignette` (`ID`, `Name`, `PlayerConditionID`, `VisibleTrackingQuestID`, `QuestFeedbackEffectId`, `Flags`, `MaxHeight`, `MinHeight`, `VignetteType`, `RewardQuestID`, `UiWidgetSetID`, `VerifiedBuild`) VALUES (700817, 'Dezgor', 0, 0, 89, 0, 0, 0, 0, 0, 0, 0);
REPLACE INTO `vignette` (`ID`, `Name`, `PlayerConditionID`, `VisibleTrackingQuestID`, `QuestFeedbackEffectId`, `Flags`, `MaxHeight`, `MinHeight`, `VignetteType`, `RewardQuestID`, `UiWidgetSetID`, `VerifiedBuild`) VALUES (701000, 'Mister Doctor', 0, 0, 89, 0, 0, 0, 0, 0, 0, 0);
REPLACE INTO `vignette` (`ID`, `Name`, `PlayerConditionID`, `VisibleTrackingQuestID`, `QuestFeedbackEffectId`, `Flags`, `MaxHeight`, `MinHeight`, `VignetteType`, `RewardQuestID`, `UiWidgetSetID`, `VerifiedBuild`) VALUES (701003, 'Ansid the Mechanic', 0, 0, 89, 0, 0, 0, 0, 0, 0, 0);
REPLACE INTO `vignette` (`ID`, `Name`, `PlayerConditionID`, `VisibleTrackingQuestID`, `QuestFeedbackEffectId`, `Flags`, `MaxHeight`, `MinHeight`, `VignetteType`, `RewardQuestID`, `UiWidgetSetID`, `VerifiedBuild`) VALUES (701005, 'Sporecaller Zancha', 0, 0, 89, 0, 0, 0, 0, 0, 0, 0);
REPLACE INTO `vignette` (`ID`, `Name`, `PlayerConditionID`, `VisibleTrackingQuestID`, `QuestFeedbackEffectId`, `Flags`, `MaxHeight`, `MinHeight`, `VignetteType`, `RewardQuestID`, `UiWidgetSetID`, `VerifiedBuild`) VALUES (703001, 'Goroth', 0, 0, 89, 0, 0, 0, 0, 0, 0, 0);
REPLACE INTO `vignette` (`ID`, `Name`, `PlayerConditionID`, `VisibleTrackingQuestID`, `QuestFeedbackEffectId`, `Flags`, `MaxHeight`, `MinHeight`, `VignetteType`, `RewardQuestID`, `UiWidgetSetID`, `VerifiedBuild`) VALUES (703012, 'Dolgonir', 0, 0, 89, 0, 0, 0, 0, 0, 0, 0);
REPLACE INTO `vignette` (`ID`, `Name`, `PlayerConditionID`, `VisibleTrackingQuestID`, `QuestFeedbackEffectId`, `Flags`, `MaxHeight`, `MinHeight`, `VignetteType`, `RewardQuestID`, `UiWidgetSetID`, `VerifiedBuild`) VALUES (703017, 'Kuryash', 0, 0, 89, 0, 0, 0, 0, 0, 0, 0);
REPLACE INTO `vignette` (`ID`, `Name`, `PlayerConditionID`, `VisibleTrackingQuestID`, `QuestFeedbackEffectId`, `Flags`, `MaxHeight`, `MinHeight`, `VignetteType`, `RewardQuestID`, `UiWidgetSetID`, `VerifiedBuild`) VALUES (705008, 'Marc', 0, 0, 89, 0, 0, 0, 0, 0, 0, 0);
REPLACE INTO `vignette` (`ID`, `Name`, `PlayerConditionID`, `VisibleTrackingQuestID`, `QuestFeedbackEffectId`, `Flags`, `MaxHeight`, `MinHeight`, `VignetteType`, `RewardQuestID`, `UiWidgetSetID`, `VerifiedBuild`) VALUES (705010, 'Felloc', 0, 0, 89, 0, 0, 0, 0, 0, 0, 0);
REPLACE INTO `vignette` (`ID`, `Name`, `PlayerConditionID`, `VisibleTrackingQuestID`, `QuestFeedbackEffectId`, `Flags`, `MaxHeight`, `MinHeight`, `VignetteType`, `RewardQuestID`, `UiWidgetSetID`, `VerifiedBuild`) VALUES (730501, 'Ice Dragon', 0, 0, 89, 0, 0, 0, 0, 0, 0, 0);
REPLACE INTO `vignette` (`ID`, `Name`, `PlayerConditionID`, `VisibleTrackingQuestID`, `QuestFeedbackEffectId`, `Flags`, `MaxHeight`, `MinHeight`, `VignetteType`, `RewardQuestID`, `UiWidgetSetID`, `VerifiedBuild`) VALUES (730504, 'Icehowl', 0, 0, 89, 0, 0, 0, 0, 0, 0, 0);
REPLACE INTO `vignette` (`ID`, `Name`, `PlayerConditionID`, `VisibleTrackingQuestID`, `QuestFeedbackEffectId`, `Flags`, `MaxHeight`, `MinHeight`, `VignetteType`, `RewardQuestID`, `UiWidgetSetID`, `VerifiedBuild`) VALUES (730505, 'Vision of Jaina', 0, 0, 89, 0, 0, 0, 0, 0, 0, 0);
REPLACE INTO `vignette` (`ID`, `Name`, `PlayerConditionID`, `VisibleTrackingQuestID`, `QuestFeedbackEffectId`, `Flags`, `MaxHeight`, `MinHeight`, `VignetteType`, `RewardQuestID`, `UiWidgetSetID`, `VerifiedBuild`) VALUES (730610, 'Mugarod', 0, 0, 89, 0, 0, 0, 0, 0, 0, 0);
REPLACE INTO `vignette` (`ID`, `Name`, `PlayerConditionID`, `VisibleTrackingQuestID`, `QuestFeedbackEffectId`, `Flags`, `MaxHeight`, `MinHeight`, `VignetteType`, `RewardQuestID`, `UiWidgetSetID`, `VerifiedBuild`) VALUES (730612, 'Skulloc', 0, 0, 89, 0, 0, 0, 0, 0, 0, 0);
REPLACE INTO `vignette` (`ID`, `Name`, `PlayerConditionID`, `VisibleTrackingQuestID`, `QuestFeedbackEffectId`, `Flags`, `MaxHeight`, `MinHeight`, `VignetteType`, `RewardQuestID`, `UiWidgetSetID`, `VerifiedBuild`) VALUES (730613, 'Shulloc', 0, 0, 89, 0, 0, 0, 0, 0, 0, 0);
REPLACE INTO `vignette` (`ID`, `Name`, `PlayerConditionID`, `VisibleTrackingQuestID`, `QuestFeedbackEffectId`, `Flags`, `MaxHeight`, `MinHeight`, `VignetteType`, `RewardQuestID`, `UiWidgetSetID`, `VerifiedBuild`) VALUES (740020, 'Great Gray', 0, 0, 89, 0, 0, 0, 0, 0, 0, 0);
REPLACE INTO `vignette` (`ID`, `Name`, `PlayerConditionID`, `VisibleTrackingQuestID`, `QuestFeedbackEffectId`, `Flags`, `MaxHeight`, `MinHeight`, `VignetteType`, `RewardQuestID`, `UiWidgetSetID`, `VerifiedBuild`) VALUES (740021, 'Great White', 0, 0, 89, 0, 0, 0, 0, 0, 0, 0);
REPLACE INTO `vignette` (`ID`, `Name`, `PlayerConditionID`, `VisibleTrackingQuestID`, `QuestFeedbackEffectId`, `Flags`, `MaxHeight`, `MinHeight`, `VignetteType`, `RewardQuestID`, `UiWidgetSetID`, `VerifiedBuild`) VALUES (740023, 'Whale Shark', 0, 0, 89, 0, 0, 0, 0, 0, 0, 0);
REPLACE INTO `vignette` (`ID`, `Name`, `PlayerConditionID`, `VisibleTrackingQuestID`, `QuestFeedbackEffectId`, `Flags`, `MaxHeight`, `MinHeight`, `VignetteType`, `RewardQuestID`, `UiWidgetSetID`, `VerifiedBuild`) VALUES (740024, 'Whale Shark', 0, 0, 89, 0, 0, 0, 0, 0, 0, 0);
REPLACE INTO `vignette` (`ID`, `Name`, `PlayerConditionID`, `VisibleTrackingQuestID`, `QuestFeedbackEffectId`, `Flags`, `MaxHeight`, `MinHeight`, `VignetteType`, `RewardQuestID`, `UiWidgetSetID`, `VerifiedBuild`) VALUES (740029, 'Bubble Shark', 0, 0, 89, 0, 0, 0, 0, 0, 0, 0);
REPLACE INTO `vignette` (`ID`, `Name`, `PlayerConditionID`, `VisibleTrackingQuestID`, `QuestFeedbackEffectId`, `Flags`, `MaxHeight`, `MinHeight`, `VignetteType`, `RewardQuestID`, `UiWidgetSetID`, `VerifiedBuild`) VALUES (740038, 'Mantid', 0, 0, 89, 0, 0, 0, 0, 0, 0, 0);
REPLACE INTO `vignette` (`ID`, `Name`, `PlayerConditionID`, `VisibleTrackingQuestID`, `QuestFeedbackEffectId`, `Flags`, `MaxHeight`, `MinHeight`, `VignetteType`, `RewardQuestID`, `UiWidgetSetID`, `VerifiedBuild`) VALUES (740039, 'Mantid', 0, 0, 89, 0, 0, 0, 0, 0, 0, 0);
REPLACE INTO `vignette` (`ID`, `Name`, `PlayerConditionID`, `VisibleTrackingQuestID`, `QuestFeedbackEffectId`, `Flags`, `MaxHeight`, `MinHeight`, `VignetteType`, `RewardQuestID`, `UiWidgetSetID`, `VerifiedBuild`) VALUES (740040, 'Mantid', 0, 0, 89, 0, 0, 0, 0, 0, 0, 0);
REPLACE INTO `vignette` (`ID`, `Name`, `PlayerConditionID`, `VisibleTrackingQuestID`, `QuestFeedbackEffectId`, `Flags`, `MaxHeight`, `MinHeight`, `VignetteType`, `RewardQuestID`, `UiWidgetSetID`, `VerifiedBuild`) VALUES (740042, 'Empowered Infernal', 0, 0, 89, 0, 0, 0, 0, 0, 0, 0);
REPLACE INTO `vignette` (`ID`, `Name`, `PlayerConditionID`, `VisibleTrackingQuestID`, `QuestFeedbackEffectId`, `Flags`, `MaxHeight`, `MinHeight`, `VignetteType`, `RewardQuestID`, `UiWidgetSetID`, `VerifiedBuild`) VALUES (740043, 'Blasphemy', 0, 0, 89, 0, 0, 0, 0, 0, 0, 0);
REPLACE INTO `vignette` (`ID`, `Name`, `PlayerConditionID`, `VisibleTrackingQuestID`, `QuestFeedbackEffectId`, `Flags`, `MaxHeight`, `MinHeight`, `VignetteType`, `RewardQuestID`, `UiWidgetSetID`, `VerifiedBuild`) VALUES (740049, 'Fel Beholder', 0, 0, 89, 0, 0, 0, 0, 0, 0, 0);
REPLACE INTO `vignette` (`ID`, `Name`, `PlayerConditionID`, `VisibleTrackingQuestID`, `QuestFeedbackEffectId`, `Flags`, `MaxHeight`, `MinHeight`, `VignetteType`, `RewardQuestID`, `UiWidgetSetID`, `VerifiedBuild`) VALUES (740050, 'Infernal Commander', 0, 0, 89, 0, 0, 0, 0, 0, 0, 0);
REPLACE INTO `vignette` (`ID`, `Name`, `PlayerConditionID`, `VisibleTrackingQuestID`, `QuestFeedbackEffectId`, `Flags`, `MaxHeight`, `MinHeight`, `VignetteType`, `RewardQuestID`, `UiWidgetSetID`, `VerifiedBuild`) VALUES (740051, 'Empowered Chamber Protector', 0, 0, 89, 0, 0, 0, 0, 0, 0, 0);
REPLACE INTO `vignette` (`ID`, `Name`, `PlayerConditionID`, `VisibleTrackingQuestID`, `QuestFeedbackEffectId`, `Flags`, `MaxHeight`, `MinHeight`, `VignetteType`, `RewardQuestID`, `UiWidgetSetID`, `VerifiedBuild`) VALUES (740055, 'Sand Mother', 0, 0, 89, 0, 0, 0, 0, 0, 0, 0);
REPLACE INTO `vignette` (`ID`, `Name`, `PlayerConditionID`, `VisibleTrackingQuestID`, `QuestFeedbackEffectId`, `Flags`, `MaxHeight`, `MinHeight`, `VignetteType`, `RewardQuestID`, `UiWidgetSetID`, `VerifiedBuild`) VALUES (740057, 'Sand Elemental', 0, 0, 89, 0, 0, 0, 0, 0, 0, 0);
REPLACE INTO `vignette` (`ID`, `Name`, `PlayerConditionID`, `VisibleTrackingQuestID`, `QuestFeedbackEffectId`, `Flags`, `MaxHeight`, `MinHeight`, `VignetteType`, `RewardQuestID`, `UiWidgetSetID`, `VerifiedBuild`) VALUES (740058, 'Sand Spirit', 0, 0, 89, 0, 0, 0, 0, 0, 0, 0);
REPLACE INTO `vignette` (`ID`, `Name`, `PlayerConditionID`, `VisibleTrackingQuestID`, `QuestFeedbackEffectId`, `Flags`, `MaxHeight`, `MinHeight`, `VignetteType`, `RewardQuestID`, `UiWidgetSetID`, `VerifiedBuild`) VALUES (740060, 'Opulence', 0, 0, 89, 0, 0, 0, 0, 0, 0, 0);

REPLACE INTO `hotfix_data` (`Id`, `UniqueId`, `TableHash`, `RecordId`, `Status`, `VerifiedBuild`) VALUES (538115, 538115, 4021368146, 700104, 1, 0);
REPLACE INTO `hotfix_data` (`Id`, `UniqueId`, `TableHash`, `RecordId`, `Status`, `VerifiedBuild`) VALUES (538115, 538115, 4021368146, 700105, 1, 0);
REPLACE INTO `hotfix_data` (`Id`, `UniqueId`, `TableHash`, `RecordId`, `Status`, `VerifiedBuild`) VALUES (538115, 538115, 4021368146, 700112, 1, 0);
REPLACE INTO `hotfix_data` (`Id`, `UniqueId`, `TableHash`, `RecordId`, `Status`, `VerifiedBuild`) VALUES (538115, 538115, 4021368146, 700211, 1, 0);
REPLACE INTO `hotfix_data` (`Id`, `UniqueId`, `TableHash`, `RecordId`, `Status`, `VerifiedBuild`) VALUES (538115, 538115, 4021368146, 700214, 1, 0);
REPLACE INTO `hotfix_data` (`Id`, `UniqueId`, `TableHash`, `RecordId`, `Status`, `VerifiedBuild`) VALUES (538115, 538115, 4021368146, 700220, 1, 0);
REPLACE INTO `hotfix_data` (`Id`, `UniqueId`, `TableHash`, `RecordId`, `Status`, `VerifiedBuild`) VALUES (538115, 538115, 4021368146, 700221, 1, 0);
REPLACE INTO `hotfix_data` (`Id`, `UniqueId`, `TableHash`, `RecordId`, `Status`, `VerifiedBuild`) VALUES (538115, 538115, 4021368146, 700303, 1, 0);
REPLACE INTO `hotfix_data` (`Id`, `UniqueId`, `TableHash`, `RecordId`, `Status`, `VerifiedBuild`) VALUES (538115, 538115, 4021368146, 700311, 1, 0);
REPLACE INTO `hotfix_data` (`Id`, `UniqueId`, `TableHash`, `RecordId`, `Status`, `VerifiedBuild`) VALUES (538115, 538115, 4021368146, 700312, 1, 0);
REPLACE INTO `hotfix_data` (`Id`, `UniqueId`, `TableHash`, `RecordId`, `Status`, `VerifiedBuild`) VALUES (538115, 538115, 4021368146, 700313, 1, 0);
REPLACE INTO `hotfix_data` (`Id`, `UniqueId`, `TableHash`, `RecordId`, `Status`, `VerifiedBuild`) VALUES (538115, 538115, 4021368146, 700314, 1, 0);
REPLACE INTO `hotfix_data` (`Id`, `UniqueId`, `TableHash`, `RecordId`, `Status`, `VerifiedBuild`) VALUES (538115, 538115, 4021368146, 700316, 1, 0);
REPLACE INTO `hotfix_data` (`Id`, `UniqueId`, `TableHash`, `RecordId`, `Status`, `VerifiedBuild`) VALUES (538115, 538115, 4021368146, 700400, 1, 0);
REPLACE INTO `hotfix_data` (`Id`, `UniqueId`, `TableHash`, `RecordId`, `Status`, `VerifiedBuild`) VALUES (538115, 538115, 4021368146, 700401, 1, 0);
REPLACE INTO `hotfix_data` (`Id`, `UniqueId`, `TableHash`, `RecordId`, `Status`, `VerifiedBuild`) VALUES (538115, 538115, 4021368146, 700402, 1, 0);
REPLACE INTO `hotfix_data` (`Id`, `UniqueId`, `TableHash`, `RecordId`, `Status`, `VerifiedBuild`) VALUES (538115, 538115, 4021368146, 700411, 1, 0);
REPLACE INTO `hotfix_data` (`Id`, `UniqueId`, `TableHash`, `RecordId`, `Status`, `VerifiedBuild`) VALUES (538115, 538115, 4021368146, 700506, 1, 0);
REPLACE INTO `hotfix_data` (`Id`, `UniqueId`, `TableHash`, `RecordId`, `Status`, `VerifiedBuild`) VALUES (538115, 538115, 4021368146, 700507, 1, 0);
REPLACE INTO `hotfix_data` (`Id`, `UniqueId`, `TableHash`, `RecordId`, `Status`, `VerifiedBuild`) VALUES (538115, 538115, 4021368146, 700508, 1, 0);
REPLACE INTO `hotfix_data` (`Id`, `UniqueId`, `TableHash`, `RecordId`, `Status`, `VerifiedBuild`) VALUES (538115, 538115, 4021368146, 700511, 1, 0);
REPLACE INTO `hotfix_data` (`Id`, `UniqueId`, `TableHash`, `RecordId`, `Status`, `VerifiedBuild`) VALUES (538115, 538115, 4021368146, 700607, 1, 0);
REPLACE INTO `hotfix_data` (`Id`, `UniqueId`, `TableHash`, `RecordId`, `Status`, `VerifiedBuild`) VALUES (538115, 538115, 4021368146, 700616, 1, 0);
REPLACE INTO `hotfix_data` (`Id`, `UniqueId`, `TableHash`, `RecordId`, `Status`, `VerifiedBuild`) VALUES (538115, 538115, 4021368146, 700620, 1, 0);
REPLACE INTO `hotfix_data` (`Id`, `UniqueId`, `TableHash`, `RecordId`, `Status`, `VerifiedBuild`) VALUES (538115, 538115, 4021368146, 700626, 1, 0);
REPLACE INTO `hotfix_data` (`Id`, `UniqueId`, `TableHash`, `RecordId`, `Status`, `VerifiedBuild`) VALUES (538115, 538115, 4021368146, 700705, 1, 0);
REPLACE INTO `hotfix_data` (`Id`, `UniqueId`, `TableHash`, `RecordId`, `Status`, `VerifiedBuild`) VALUES (538115, 538115, 4021368146, 700706, 1, 0);
REPLACE INTO `hotfix_data` (`Id`, `UniqueId`, `TableHash`, `RecordId`, `Status`, `VerifiedBuild`) VALUES (538115, 538115, 4021368146, 700707, 1, 0);
REPLACE INTO `hotfix_data` (`Id`, `UniqueId`, `TableHash`, `RecordId`, `Status`, `VerifiedBuild`) VALUES (538115, 538115, 4021368146, 700708, 1, 0);
REPLACE INTO `hotfix_data` (`Id`, `UniqueId`, `TableHash`, `RecordId`, `Status`, `VerifiedBuild`) VALUES (538115, 538115, 4021368146, 700712, 1, 0);
REPLACE INTO `hotfix_data` (`Id`, `UniqueId`, `TableHash`, `RecordId`, `Status`, `VerifiedBuild`) VALUES (538115, 538115, 4021368146, 700713, 1, 0);
REPLACE INTO `hotfix_data` (`Id`, `UniqueId`, `TableHash`, `RecordId`, `Status`, `VerifiedBuild`) VALUES (538115, 538115, 4021368146, 700714, 1, 0);
REPLACE INTO `hotfix_data` (`Id`, `UniqueId`, `TableHash`, `RecordId`, `Status`, `VerifiedBuild`) VALUES (538115, 538115, 4021368146, 700715, 1, 0);
REPLACE INTO `hotfix_data` (`Id`, `UniqueId`, `TableHash`, `RecordId`, `Status`, `VerifiedBuild`) VALUES (538115, 538115, 4021368146, 700721, 1, 0);
REPLACE INTO `hotfix_data` (`Id`, `UniqueId`, `TableHash`, `RecordId`, `Status`, `VerifiedBuild`) VALUES (538115, 538115, 4021368146, 700722, 1, 0);
REPLACE INTO `hotfix_data` (`Id`, `UniqueId`, `TableHash`, `RecordId`, `Status`, `VerifiedBuild`) VALUES (538115, 538115, 4021368146, 700723, 1, 0);
REPLACE INTO `hotfix_data` (`Id`, `UniqueId`, `TableHash`, `RecordId`, `Status`, `VerifiedBuild`) VALUES (538115, 538115, 4021368146, 700724, 1, 0);
REPLACE INTO `hotfix_data` (`Id`, `UniqueId`, `TableHash`, `RecordId`, `Status`, `VerifiedBuild`) VALUES (538115, 538115, 4021368146, 700812, 1, 0);
REPLACE INTO `hotfix_data` (`Id`, `UniqueId`, `TableHash`, `RecordId`, `Status`, `VerifiedBuild`) VALUES (538115, 538115, 4021368146, 700813, 1, 0);
REPLACE INTO `hotfix_data` (`Id`, `UniqueId`, `TableHash`, `RecordId`, `Status`, `VerifiedBuild`) VALUES (538115, 538115, 4021368146, 700815, 1, 0);
REPLACE INTO `hotfix_data` (`Id`, `UniqueId`, `TableHash`, `RecordId`, `Status`, `VerifiedBuild`) VALUES (538115, 538115, 4021368146, 700816, 1, 0);
REPLACE INTO `hotfix_data` (`Id`, `UniqueId`, `TableHash`, `RecordId`, `Status`, `VerifiedBuild`) VALUES (538115, 538115, 4021368146, 700817, 1, 0);
REPLACE INTO `hotfix_data` (`Id`, `UniqueId`, `TableHash`, `RecordId`, `Status`, `VerifiedBuild`) VALUES (538115, 538115, 4021368146, 701000, 1, 0);
REPLACE INTO `hotfix_data` (`Id`, `UniqueId`, `TableHash`, `RecordId`, `Status`, `VerifiedBuild`) VALUES (538115, 538115, 4021368146, 701003, 1, 0);
REPLACE INTO `hotfix_data` (`Id`, `UniqueId`, `TableHash`, `RecordId`, `Status`, `VerifiedBuild`) VALUES (538115, 538115, 4021368146, 701005, 1, 0);
REPLACE INTO `hotfix_data` (`Id`, `UniqueId`, `TableHash`, `RecordId`, `Status`, `VerifiedBuild`) VALUES (538115, 538115, 4021368146, 703001, 1, 0);
REPLACE INTO `hotfix_data` (`Id`, `UniqueId`, `TableHash`, `RecordId`, `Status`, `VerifiedBuild`) VALUES (538115, 538115, 4021368146, 703012, 1, 0);
REPLACE INTO `hotfix_data` (`Id`, `UniqueId`, `TableHash`, `RecordId`, `Status`, `VerifiedBuild`) VALUES (538115, 538115, 4021368146, 703017, 1, 0);
REPLACE INTO `hotfix_data` (`Id`, `UniqueId`, `TableHash`, `RecordId`, `Status`, `VerifiedBuild`) VALUES (538115, 538115, 4021368146, 705008, 1, 0);
REPLACE INTO `hotfix_data` (`Id`, `UniqueId`, `TableHash`, `RecordId`, `Status`, `VerifiedBuild`) VALUES (538115, 538115, 4021368146, 705010, 1, 0);
REPLACE INTO `hotfix_data` (`Id`, `UniqueId`, `TableHash`, `RecordId`, `Status`, `VerifiedBuild`) VALUES (538115, 538115, 4021368146, 730501, 1, 0);
REPLACE INTO `hotfix_data` (`Id`, `UniqueId`, `TableHash`, `RecordId`, `Status`, `VerifiedBuild`) VALUES (538115, 538115, 4021368146, 730504, 1, 0);
REPLACE INTO `hotfix_data` (`Id`, `UniqueId`, `TableHash`, `RecordId`, `Status`, `VerifiedBuild`) VALUES (538115, 538115, 4021368146, 730505, 1, 0);
REPLACE INTO `hotfix_data` (`Id`, `UniqueId`, `TableHash`, `RecordId`, `Status`, `VerifiedBuild`) VALUES (538115, 538115, 4021368146, 730610, 1, 0);
REPLACE INTO `hotfix_data` (`Id`, `UniqueId`, `TableHash`, `RecordId`, `Status`, `VerifiedBuild`) VALUES (538115, 538115, 4021368146, 730612, 1, 0);
REPLACE INTO `hotfix_data` (`Id`, `UniqueId`, `TableHash`, `RecordId`, `Status`, `VerifiedBuild`) VALUES (538115, 538115, 4021368146, 730613, 1, 0);
REPLACE INTO `hotfix_data` (`Id`, `UniqueId`, `TableHash`, `RecordId`, `Status`, `VerifiedBuild`) VALUES (538115, 538115, 4021368146, 740020, 1, 0);
REPLACE INTO `hotfix_data` (`Id`, `UniqueId`, `TableHash`, `RecordId`, `Status`, `VerifiedBuild`) VALUES (538115, 538115, 4021368146, 740021, 1, 0);
REPLACE INTO `hotfix_data` (`Id`, `UniqueId`, `TableHash`, `RecordId`, `Status`, `VerifiedBuild`) VALUES (538115, 538115, 4021368146, 740023, 1, 0);
REPLACE INTO `hotfix_data` (`Id`, `UniqueId`, `TableHash`, `RecordId`, `Status`, `VerifiedBuild`) VALUES (538115, 538115, 4021368146, 740024, 1, 0);
REPLACE INTO `hotfix_data` (`Id`, `UniqueId`, `TableHash`, `RecordId`, `Status`, `VerifiedBuild`) VALUES (538115, 538115, 4021368146, 740029, 1, 0);
REPLACE INTO `hotfix_data` (`Id`, `UniqueId`, `TableHash`, `RecordId`, `Status`, `VerifiedBuild`) VALUES (538115, 538115, 4021368146, 740038, 1, 0);
REPLACE INTO `hotfix_data` (`Id`, `UniqueId`, `TableHash`, `RecordId`, `Status`, `VerifiedBuild`) VALUES (538115, 538115, 4021368146, 740039, 1, 0);
REPLACE INTO `hotfix_data` (`Id`, `UniqueId`, `TableHash`, `RecordId`, `Status`, `VerifiedBuild`) VALUES (538115, 538115, 4021368146, 740040, 1, 0);
REPLACE INTO `hotfix_data` (`Id`, `UniqueId`, `TableHash`, `RecordId`, `Status`, `VerifiedBuild`) VALUES (538115, 538115, 4021368146, 740042, 1, 0);
REPLACE INTO `hotfix_data` (`Id`, `UniqueId`, `TableHash`, `RecordId`, `Status`, `VerifiedBuild`) VALUES (538115, 538115, 4021368146, 740043, 1, 0);
REPLACE INTO `hotfix_data` (`Id`, `UniqueId`, `TableHash`, `RecordId`, `Status`, `VerifiedBuild`) VALUES (538115, 538115, 4021368146, 740049, 1, 0);
REPLACE INTO `hotfix_data` (`Id`, `UniqueId`, `TableHash`, `RecordId`, `Status`, `VerifiedBuild`) VALUES (538115, 538115, 4021368146, 740050, 1, 0);
REPLACE INTO `hotfix_data` (`Id`, `UniqueId`, `TableHash`, `RecordId`, `Status`, `VerifiedBuild`) VALUES (538115, 538115, 4021368146, 740051, 1, 0);
REPLACE INTO `hotfix_data` (`Id`, `UniqueId`, `TableHash`, `RecordId`, `Status`, `VerifiedBuild`) VALUES (538115, 538115, 4021368146, 740055, 1, 0);
REPLACE INTO `hotfix_data` (`Id`, `UniqueId`, `TableHash`, `RecordId`, `Status`, `VerifiedBuild`) VALUES (538115, 538115, 4021368146, 740057, 1, 0);
REPLACE INTO `hotfix_data` (`Id`, `UniqueId`, `TableHash`, `RecordId`, `Status`, `VerifiedBuild`) VALUES (538115, 538115, 4021368146, 740058, 1, 0);
REPLACE INTO `hotfix_data` (`Id`, `UniqueId`, `TableHash`, `RecordId`, `Status`, `VerifiedBuild`) VALUES (538115, 538115, 4021368146, 740060, 1, 0);
