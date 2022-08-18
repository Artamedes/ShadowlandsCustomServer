-- hotfixes for torghast
REPLACE INTO `hotfix_data` (`Id`, `UniqueId`, `TableHash`, `RecordId`, `Status`, `VerifiedBuild`) VALUES (10001, 10001, 3179597154, 10001, 1, 0);
REPLACE INTO `map` (`ID`, `Directory`, `MapName`, `MapDescription0`, `MapDescription1`, `PvpShortDescription`, `PvpLongDescription`, `CorpseX`, `CorpseY`, `MapType`, `InstanceType`, `ExpansionID`, `AreaTableID`, `LoadingScreenID`, `TimeOfDayOverride`, `ParentMapID`, `CosmeticParentMapID`, `TimeOffset`, `MinimapIconScale`, `CorpseMapID`, `MaxPlayers`, `WindSettingsID`, `ZmpFileDataID`, `WdtFileDataID`, `Flags1`, `Flags2`, `Flags3`, `VerifiedBuild`) VALUES (10001, '2162', 'Torghast, Tower of the Damned', NULL, NULL, NULL, NULL, 0, 0, 1, 1, 8, 0, 590, -1, -1, -1, 0, 1, -1, 0, 12, 0, 2461919, 428875357, 404751380, 0, 0);
DELETE FROM `map` WHERE  `ID`=2162;
REPLACE INTO `map_difficulty` (`ID`, `Message`, `DifficultyID`, `LockID`, `ResetInterval`, `MaxPlayers`, `ItemContext`, `ItemContextPickerID`, `Flags`, `ContentTuningID`, `MapID`, `VerifiedBuild`) VALUES (100021, NULL, 23, 0, 0, 5, 0, 0, 2, 0, 10001, 0);

DELETE FROM `map_difficulty` WHERE  `ID`=4747;