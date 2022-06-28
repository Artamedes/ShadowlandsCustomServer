-- elite mythic
REPLACE INTO `item_name_description` (`ID`, `Description`, `Color`, `VerifiedBuild`) VALUES (40003, 'Elite Mythic', 16758272, 0);
REPLACE INTO `item_bonus_list` (`ID`, `Flags`, `VerifiedBuild`) VALUES (30100, 0, 0);
REPLACE INTO `item_bonus` (`ID`, `Value1`, `Value2`, `Value3`, `Value4`, `ParentItemBonusListID`, `Type`, `OrderIndex`, `VerifiedBuild`) VALUES (30100, 40003, 0, 0, 0, 30100, 4, 0, 0);
REPLACE INTO `item_bonus` (`ID`, `Value1`, `Value2`, `Value3`, `Value4`, `ParentItemBonusListID`, `Type`, `OrderIndex`, `VerifiedBuild`) VALUES (30101, 3, 0, 0, 0, 30100, 7, 0, 0);

REPLACE INTO `hotfix_data` (`Id`, `UniqueId`, `TableHash`, `RecordId`, `Status`, `VerifiedBuild`) VALUES (40003, 40003, 2199425034, 30100, 1, 0);
REPLACE INTO `hotfix_data` (`Id`, `UniqueId`, `TableHash`, `RecordId`, `Status`, `VerifiedBuild`) VALUES (40003, 40003, 2199425034, 30101, 1, 0);
REPLACE INTO `hotfix_data` (`Id`, `UniqueId`, `TableHash`, `RecordId`, `Status`, `VerifiedBuild`) VALUES (40003, 40003, 2518885667, 30100, 1, 0);
REPLACE INTO `hotfix_data` (`Id`, `UniqueId`, `TableHash`, `RecordId`, `Status`, `VerifiedBuild`) VALUES (40003, 40003, 1891821565, 40003, 1, 0);
