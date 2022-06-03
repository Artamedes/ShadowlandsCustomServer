-- 
REPLACE INTO `char_base_info` (id, raceid, `classid`) VALUES (301, 24, 1);
REPLACE INTO `char_base_info` (id, raceid, `classid`) VALUES (302, 24, 2);
REPLACE INTO `char_base_info` (id, raceid, `classid`) VALUES (303, 24, 3);
REPLACE INTO `char_base_info` (id, raceid, `classid`) VALUES (304, 24, 4);
REPLACE INTO `char_base_info` (id, raceid, `classid`) VALUES (305, 24, 5);
REPLACE INTO `char_base_info` (id, raceid, `classid`) VALUES (306, 24, 6);
REPLACE INTO `char_base_info` (id, raceid, `classid`) VALUES (307, 24, 7);
REPLACE INTO `char_base_info` (id, raceid, `classid`) VALUES (308, 24, 8);
REPLACE INTO `char_base_info` (id, raceid, `classid`) VALUES (309, 24, 9);
REPLACE INTO `char_base_info` (id, raceid, `classid`) VALUES (310, 24, 10);
REPLACE INTO `char_base_info` (id, raceid, `classid`) VALUES (311, 24, 11);
REPLACE INTO `char_base_info` (id, raceid, `classid`) VALUES (312, 24, 12);

REPLACE INTO `hotfix_data` (`Id`, `UniqueId`, `TableHash`, `RecordId`, `Status`, `VerifiedBuild`) select 2500, 2500, 812099832, id, 1, 0 FROM char_base_info WHERE id >= 301;
