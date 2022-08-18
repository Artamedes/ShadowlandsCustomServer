-- Taking out the trash.
DELETE FROM `z_magicstone_menus` WHERE  `MenuID`=0 AND `Ordering`=8;
DELETE FROM `z_magicstone_menus` WHERE  `MenuID`=0 AND `Ordering`=9;
DELETE FROM `z_magicstone_menus` WHERE  `MenuID`=0 AND `Ordering`=10;
DELETE FROM `z_magicstone_menus` WHERE  `MenuID`=1 AND `Ordering`=2;

-- Remove from M+ Rotation
DELETE FROM z_custom_challenge_dungeons WHERE ChallengeID IN (30006, 30007, 30008);

-- Remove related quests.
DELETE FROM creature_queststarter WHERE quest IN (700026, 700027, 700028, 700029, 700030);
DELETE FROM creature_questender WHERE quest IN (700026, 700027, 700028, 700029, 700030);

-- Fix old quests
UPDATE `quest_template_addon` SET `PrevQuestID`='700025' WHERE  `ID`=700031;
UPDATE `quest_template_addon` SET `NextQuestID`='700031' WHERE  `ID`=700025;

UPDATE `conditions` SET `ConditionValue1`='700025', `Comment`='Check if quest 700025 is rewarded' WHERE  `SourceTypeOrReferenceId`=69 AND `SourceGroup`=0 AND `SourceEntry`=24 AND `SourceId`=0 AND `ElseGroup`=0 AND `ConditionTypeOrReference`=8 AND `ConditionTarget`=0 AND `ConditionValue1`=700030 AND `ConditionValue2`=0 AND `ConditionValue3`=0;
