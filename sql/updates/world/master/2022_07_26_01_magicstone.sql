
REPLACE INTO `z_magicstone_menus` (`MenuID`, `Ordering`, `GossipOptionIcon`, `Text`, `ExtraText`, `ActionID`, `ConditionID`) VALUES (0, 101, 0, '|TInterface\\ICONS\\achievement_mythicdungeons_shadowlands.BLP:30:30:-28:0|tCovenant', NULL, 60, 1);

REPLACE INTO `z_magicstone_actions` (`ActionID`, `Ordering`, `ActionType`, `Param1`, `Param2`, `Param3`, `Param4`, `Param5`, `ConditionID`, `Note`) VALUES (60, 0, 1, 60, 0, 0, 0, 0, 0, 'Covenant');
REPLACE INTO `z_magicstone_actions` (`ActionID`, `Ordering`, `ActionType`, `Param1`, `Param2`, `Param3`, `Param4`, `Param5`, `ConditionID`, `Note`) VALUES (62, 0, 7, 0, 0, 0, 0, 0, 0, 'Swap Cov');
REPLACE INTO `z_magicstone_actions` (`ActionID`, `Ordering`, `ActionType`, `Param1`, `Param2`, `Param3`, `Param4`, `Param5`, `ConditionID`, `Note`) VALUES (61, 0, 8, 0, 0, 0, 0, 0, 0, 'Swap Soulbind');

REPLACE INTO `z_magicstone_menus` (`MenuID`, `Ordering`, `GossipOptionIcon`, `Text`, `ExtraText`, `ActionID`, `ConditionID`) VALUES (60, 0, 0, '|TInterface\\ICONS\\achievement_mythicdungeons_shadowlands.BLP:30:30:-28:0|tSwap Covenant', NULL, 61, 0);
REPLACE INTO `z_magicstone_menus` (`MenuID`, `Ordering`, `GossipOptionIcon`, `Text`, `ExtraText`, `ActionID`, `ConditionID`) VALUES (60, 1, 0, '|TInterface\\ICONS\\spell_animabastion_beam.BLP:30:30:-28:0|tView Soulbinds', NULL, 62, 0);
REPLACE INTO `z_magicstone_menus` (`MenuID`, `Ordering`, `GossipOptionIcon`, `Text`, `ExtraText`, `ActionID`, `ConditionID`) VALUES (60, 2, 0, '|TInterface\\ICONS\\achievement_bg_returnxflags_def_wsg.BLP:30:30:-28:0|tReturn', NULL, 0, 0);
