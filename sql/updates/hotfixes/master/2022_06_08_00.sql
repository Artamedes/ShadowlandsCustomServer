-- hotfix data
DELETE FROM `hotfix_data` WHERE `Id`=700000 AND `TableHash`=3538824359 AND `RecordId`=700000;
INSERT INTO `hotfix_data` (`Id`, `UniqueId`, `TableHash`, `RecordId`, `Status`, `VerifiedBuild`) VALUES (700000, 700000, 3538824359, 700000, 1, 0);
DELETE FROM `achievement` WHERE `ID`=700000 AND `VerifiedBuild`=42423;
INSERT INTO `achievement` (`Description`, `Title`, `Reward`, `ID`, `InstanceID`, `Faction`, `Supercedes`, `Category`, `MinimumCriteria`, `Points`, `Flags`, `UiOrder`, `IconFileID`, `RewardItemID`, `CriteriaTree`, `SharesCriteria`, `CovenantID`, `VerifiedBuild`) VALUES ('Complete the Campaign for Season 1', 'Campaign (Season 1)', 'Ability for new characters to skip the storyline', 700000, -1, -1, 0, 15422, 0, 20, 128, 28, 1530370, 0, 0, 0, 0, 42423);
