-- 
REPLACE INTO `item_extended_cost` (`ID`, `RequiredArenaRating`, `ArenaBracket`, `Flags`, `MinFactionID`, `MinReputation`, `RequiredAchievement`, `ItemID1`, `ItemID2`, `ItemID3`, `ItemID4`, `ItemID5`, `ItemCount1`, `ItemCount2`, `ItemCount3`, `ItemCount4`, `ItemCount5`, `CurrencyID1`, `CurrencyID2`, `CurrencyID3`, `CurrencyID4`, `CurrencyID5`, `CurrencyCount1`, `CurrencyCount2`, `CurrencyCount3`, `CurrencyCount4`, `CurrencyCount5`, `VerifiedBuild`) VALUES (800065, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10187, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0);
REPLACE INTO `hotfix_data` (`Id`, `UniqueId`, `TableHash`, `RecordId`, `Status`, `VerifiedBuild`) VALUES (800065, 800065, 3146089301, 800065, 1, 0);

UPDATE `currency_types` SET `InventoryIconFileID`='876916' WHERE  `ID`=10187;
