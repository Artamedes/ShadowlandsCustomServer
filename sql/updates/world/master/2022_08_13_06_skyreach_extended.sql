REPLACE INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `SoundPlayType`, `BroadcastTextId`, `TextRange`, `comment`) VALUES (75964, 0, 0, 'I will slice the flesh from your bones!', 14, 0, 100, 0, 0, 0, 0, 0, 0, '');
REPLACE INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `SoundPlayType`, `BroadcastTextId`, `TextRange`, `comment`) VALUES (75964, 1, 0, 'You cannot outrun the wind!', 14, 0, 100, 0, 0, 0, 0, 0, 0, '');
REPLACE INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `SoundPlayType`, `BroadcastTextId`, `TextRange`, `comment`) VALUES (75964, 2, 0, 'I... perish....', 14, 0, 100, 0, 0, 0, 0, 0, 0, '');

DELETE FROM creature WHERE id = 76119;

UPDATE `areatrigger_create_properties` SET `ScriptName`='AreaTrigger_WindWall' WHERE  `Id`=3683;