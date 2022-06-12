-- 

UPDATE `item_sparse` SET `Description`='|cff00FF00Increases itemlevel by 20,\nStacks with other empowerments|R' WHERE  `ID` IN (700008,700018, 700028);
DELETE FROM `item_bonus` WHERE `ID`=2699 AND `VerifiedBuild`=0;
INSERT INTO `item_bonus` (`ID`, `Value1`, `Value2`, `Value3`, `Value4`, `ParentItemBonusListID`, `Type`, `OrderIndex`, `VerifiedBuild`) VALUES (2699, 20, 0, 0, 0, 1522, 1, 0, 0);
DELETE FROM `item_bonus` WHERE `ID`=2700 AND `VerifiedBuild`=0;
INSERT INTO `item_bonus` (`ID`, `Value1`, `Value2`, `Value3`, `Value4`, `ParentItemBonusListID`, `Type`, `OrderIndex`, `VerifiedBuild`) VALUES (2700, 20, 0, 0, 0, 1523, 1, 0, 0);
DELETE FROM `item_bonus` WHERE `ID`=2701 AND `VerifiedBuild`=0;
INSERT INTO `item_bonus` (`ID`, `Value1`, `Value2`, `Value3`, `Value4`, `ParentItemBonusListID`, `Type`, `OrderIndex`, `VerifiedBuild`) VALUES (2701, 20, 0, 0, 0, 1524, 1, 0, 0);
DELETE FROM `hotfix_data` WHERE `Id`=67460 AND `TableHash`=2199425034 AND `RecordId`=2699;
INSERT INTO `hotfix_data` (`Id`, `UniqueId`, `TableHash`, `RecordId`, `Status`, `VerifiedBuild`) VALUES (67460, 4040857530, 2199425034, 2699, 1, 42423);
DELETE FROM `hotfix_data` WHERE `Id`=67460 AND `TableHash`=2199425034 AND `RecordId`=2700;
INSERT INTO `hotfix_data` (`Id`, `UniqueId`, `TableHash`, `RecordId`, `Status`, `VerifiedBuild`) VALUES (67460, 4040857530, 2199425034, 2700, 1, 42423);
DELETE FROM `hotfix_data` WHERE `Id`=67460 AND `TableHash`=2199425034 AND `RecordId`=2701;
INSERT INTO `hotfix_data` (`Id`, `UniqueId`, `TableHash`, `RecordId`, `Status`, `VerifiedBuild`) VALUES (67460, 4040857530, 2199425034, 2701, 1, 42423);

REPLACE INTO item_extended_cost (ID, RequiredArenaRating, ArenaBracket, Flags, MinFactionID, MinReputation, RequiredAchievement, ItemID1, ItemID2, ItemID3, ItemID4, ItemID5, ItemCount1, ItemCount2, ItemCount3, ItemCount4, ItemCount5, CurrencyID1, CurrencyID2, CurrencyID3, CurrencyID4, CurrencyID5, CurrencyCount1, CurrencyCount2, CurrencyCount3, CurrencyCount4, CurrencyCount5, VerifiedBuild) VALUES (10173, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10170, 0, 0, 0, 0, 50, 0, 0, 0, 0, 42423);
REPLACE INTO item_extended_cost (ID, RequiredArenaRating, ArenaBracket, Flags, MinFactionID, MinReputation, RequiredAchievement, ItemID1, ItemID2, ItemID3, ItemID4, ItemID5, ItemCount1, ItemCount2, ItemCount3, ItemCount4, ItemCount5, CurrencyID1, CurrencyID2, CurrencyID3, CurrencyID4, CurrencyID5, CurrencyCount1, CurrencyCount2, CurrencyCount3, CurrencyCount4, CurrencyCount5, VerifiedBuild) VALUES (10174, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10174, 0, 0, 0, 0, 75, 0, 0, 0, 0, 0);