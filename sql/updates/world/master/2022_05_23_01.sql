UPDATE `quest_template` SET `RewardNextQuest`='0' WHERE  `ID`=700022;

DELETE FROM creature_queststarter WHERE quest = 700009;
UPDATE creature_template SET lootid = 0 WHERE scriptname = 'npc_helya_mawfinale';
