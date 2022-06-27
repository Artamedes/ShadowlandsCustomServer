
UPDATE `map` SET `InstanceType`='1' WHERE  `ID`=2456;
REPLACE INTO `map_difficulty` (`ID`, `Message`, `DifficultyID`, `LockID`, `ResetInterval`, `MaxPlayers`, `ItemContext`, `ItemContextPickerID`, `Flags`, `ContentTuningID`, `MapID`, `VerifiedBuild`) VALUES (100023, NULL, 8, 0, 0, 5, 0, 0, 0, 0, 2456, 0);
REPLACE INTO `map_difficulty` (`ID`, `Message`, `DifficultyID`, `LockID`, `ResetInterval`, `MaxPlayers`, `ItemContext`, `ItemContextPickerID`, `Flags`, `ContentTuningID`, `MapID`, `VerifiedBuild`) VALUES (100024, NULL, 23, 0, 0, 5, 0, 0, 2, 0, 2456, 0);

DELETE FROM `conversation_line` WHERE `ID`=700313 AND `VerifiedBuild`=0;
INSERT INTO `conversation_line` (`ID`, `BroadcastTextID`, `SpellVisualKitID`, `AdditionalDuration`, `NextConversationLineID`, `AnimKitID`, `SpeechType`, `StartAnimation`, `EndAnimation`, `VerifiedBuild`) VALUES (700313, 7003013, 0, 10000, 0, 0, 1, 60, 60, 0);

DELETE FROM `broadcast_text` WHERE `ID`=7003013 AND `VerifiedBuild`=0;
INSERT INTO `broadcast_text` (`Text`, `Text1`, `ID`, `LanguageID`, `ConditionID`, `EmotesID`, `Flags`, `ChatBubbleDurationMs`, `VoiceOverPriorityID`, `SoundKitID1`, `SoundKitID2`, `EmoteID1`, `EmoteID2`, `EmoteID3`, `EmoteDelay1`, `EmoteDelay2`, `EmoteDelay3`, `VerifiedBuild`) VALUES ('Champions! I require your aid at once. Use the portal to get to me, quickly!', NULL, 7003013, 0, 0, 0, 65, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

REPLACE INTO `broadcast_text` (`Text`, `Text1`, `ID`, `LanguageID`, `ConditionID`, `EmotesID`, `Flags`, `ChatBubbleDurationMs`, `VoiceOverPriorityID`, `SoundKitID1`, `SoundKitID2`, `EmoteID1`, `EmoteID2`, `EmoteID3`, `EmoteDelay1`, `EmoteDelay2`, `EmoteDelay3`, `VerifiedBuild`) VALUES ('We aren\'t safe here.', NULL, 707036, 0, 0, 0, 65, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
