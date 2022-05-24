UPDATE `quest_template` SET `RewardNextQuest`='0' WHERE  `ID`=700022;

-- remove deprecated quest
DELETE FROM creature_queststarter WHERE quest = 700009;
-- clear loot
UPDATE creature_template SET lootid = 0 WHERE scriptname = 'npc_helya_mawfinale';
-- fix text
UPDATE `quest_template` SET `QuestDescription`='This final fight is up to you, Champion.\r\n\r\nDefeat the General of the Mawsworn, and save this realm once and for all!' WHERE  `ID`=700034;
-- change condition for skoldus hall tele
UPDATE `conditions` SET `ConditionValue1`='700030', `Comment`='Check if quest 700030 is rewarded' WHERE  `SourceTypeOrReferenceId`=69 AND `SourceGroup`=0 AND `SourceEntry`=24 AND `SourceId`=0 AND `ElseGroup`=0 AND `ConditionTypeOrReference`=8 AND `ConditionTarget`=0 AND `ConditionValue1`=700031 AND `ConditionValue2`=0 AND `ConditionValue3`=0;

DELETE FROM spell_script_names WHERE spell_id = 342963;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (342963, 'spell_dog_dash_342963');