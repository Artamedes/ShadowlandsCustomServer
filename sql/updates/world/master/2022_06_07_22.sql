--
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=69 AND `SourceGroup`=0 AND `SourceEntry`=27 AND `SourceId`=0 AND `ElseGroup`=0 AND `ConditionTypeOrReference`=9 AND `ConditionTarget`=0 AND `ConditionValue1`=700036 AND `ConditionValue2`=0 AND `ConditionValue3`=0;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES (69, 0, 27, 0, 0, 9, 0, 700036, 0, 0, 0, 0, 0, '', 'Check if quest 700036 is active');
DELETE FROM `z_magicstone_actions` WHERE `ActionID`=57 AND `Ordering`=0;
INSERT INTO `z_magicstone_actions` (`ActionID`, `Ordering`, `ActionType`, `Param1`, `Param2`, `Param3`, `Param4`, `Param5`, `ConditionID`, `Note`) VALUES (57, 0, 2, 1935, 0, 0, 0, 0, 0, 'juno');
DELETE FROM `z_magicstone_menus` WHERE `MenuID`=0 AND `Ordering`=14;
INSERT INTO `z_magicstone_menus` (`MenuID`, `Ordering`, `GossipOptionIcon`, `ExtraText`, `Text`, `ActionID`, `ConditionID`) VALUES (0, 14, 0, NULL, '|TInterface\\ICONS\\inv_mawguardpet_red.BLP:30:30:-28:0|tJuno |cffFF0000(Quest)', 57, 27);
