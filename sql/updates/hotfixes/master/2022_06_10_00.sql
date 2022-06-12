-- 
DELETE FROM `item_bonus` WHERE `ID`=2699 AND `VerifiedBuild`=0;
INSERT INTO `item_bonus` (`ID`, `Value1`, `Value2`, `Value3`, `Value4`, `ParentItemBonusListID`, `Type`, `OrderIndex`, `VerifiedBuild`) VALUES (2699, 10, 0, 0, 0, 1522, 1, 0, 0);
DELETE FROM `item_bonus` WHERE `ID`=2700 AND `VerifiedBuild`=0;
INSERT INTO `item_bonus` (`ID`, `Value1`, `Value2`, `Value3`, `Value4`, `ParentItemBonusListID`, `Type`, `OrderIndex`, `VerifiedBuild`) VALUES (2700, 10, 0, 0, 0, 1523, 1, 0, 0);
DELETE FROM `item_bonus` WHERE `ID`=2701 AND `VerifiedBuild`=0;
INSERT INTO `item_bonus` (`ID`, `Value1`, `Value2`, `Value3`, `Value4`, `ParentItemBonusListID`, `Type`, `OrderIndex`, `VerifiedBuild`) VALUES (2701, 10, 0, 0, 0, 1524, 1, 0, 0);
DELETE FROM `hotfix_data` WHERE `Id`=67460 AND `TableHash`=2199425034 AND `RecordId`=2699;
INSERT INTO `hotfix_data` (`Id`, `UniqueId`, `TableHash`, `RecordId`, `Status`, `VerifiedBuild`) VALUES (67460, 4040857530, 2199425034, 2699, 1, 42423);
DELETE FROM `hotfix_data` WHERE `Id`=67460 AND `TableHash`=2199425034 AND `RecordId`=2700;
INSERT INTO `hotfix_data` (`Id`, `UniqueId`, `TableHash`, `RecordId`, `Status`, `VerifiedBuild`) VALUES (67460, 4040857530, 2199425034, 2700, 1, 42423);
DELETE FROM `hotfix_data` WHERE `Id`=67460 AND `TableHash`=2199425034 AND `RecordId`=2701;
INSERT INTO `hotfix_data` (`Id`, `UniqueId`, `TableHash`, `RecordId`, `Status`, `VerifiedBuild`) VALUES (67460, 4040857530, 2199425034, 2701, 1, 42423);
