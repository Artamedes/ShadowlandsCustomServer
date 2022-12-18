
DROP TABLE IF EXISTS `battle_pet_breed_quality`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `battle_pet_breed_quality` (
  `ID` int(10) unsigned NOT NULL DEFAULT '0',
  `MaxQualityRoll` int(10) unsigned NOT NULL DEFAULT '0',
  `StateMultiplier` float NOT NULL DEFAULT '0',
  `QualityEnum` tinyint(4) NOT NULL DEFAULT '0',
  `VerifiedBuild` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`,`VerifiedBuild`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `character_loadout`
--

DROP TABLE IF EXISTS `character_loadout`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `character_loadout` (
  `ID` int(10) unsigned NOT NULL DEFAULT '0',
  `RaceMask` bigint(20) NOT NULL DEFAULT '0',
  `ChrClassID` tinyint(4) NOT NULL DEFAULT '0',
  `Purpose` int(11) NOT NULL DEFAULT '0',
  `ItemContext` tinyint(4) NOT NULL DEFAULT '0',
  `VerifiedBuild` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`,`VerifiedBuild`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;


DROP TABLE IF EXISTS `chr_race_x_chr_model`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `chr_race_x_chr_model` (
  `ID` int(10) unsigned NOT NULL DEFAULT '0',
  `ChrRacesID` int(11) NOT NULL DEFAULT '0',
  `ChrModelID` int(11) NOT NULL DEFAULT '0',
  `Sex` int(11) NOT NULL DEFAULT '0',
  `AllowedTransmogSlots` int(11) NOT NULL DEFAULT '0',
  `VerifiedBuild` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`,`VerifiedBuild`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;


DROP TABLE IF EXISTS `cinematic_camera`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `cinematic_camera` (
  `ID` int(10) unsigned NOT NULL DEFAULT '0',
  `OriginX` float NOT NULL DEFAULT '0',
  `OriginY` float NOT NULL DEFAULT '0',
  `OriginZ` float NOT NULL DEFAULT '0',
  `SoundID` int(10) unsigned NOT NULL DEFAULT '0',
  `OriginFacing` float NOT NULL DEFAULT '0',
  `FileDataID` int(10) unsigned NOT NULL DEFAULT '0',
  `ConversationID` int(10) unsigned NOT NULL DEFAULT '0',
  `VerifiedBuild` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`,`VerifiedBuild`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;


DROP TABLE IF EXISTS `currency_types`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `currency_types` (
  `ID` int(10) unsigned NOT NULL DEFAULT '0',
  `Name` text,
  `Description` text,
  `CategoryID` int(11) NOT NULL DEFAULT '0',
  `InventoryIconFileID` int(11) NOT NULL DEFAULT '0',
  `SpellWeight` int(10) unsigned NOT NULL DEFAULT '0',
  `SpellCategory` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `MaxQty` int(10) unsigned NOT NULL DEFAULT '0',
  `MaxEarnablePerWeek` int(10) unsigned NOT NULL DEFAULT '0',
  `Quality` tinyint(4) NOT NULL DEFAULT '0',
  `FactionID` int(11) NOT NULL DEFAULT '0',
  `ItemGroupSoundsID` int(11) NOT NULL DEFAULT '0',
  `XpQuestDifficulty` int(11) NOT NULL DEFAULT '0',
  `AwardConditionID` int(11) NOT NULL DEFAULT '0',
  `MaxQtyWorldStateID` int(11) NOT NULL DEFAULT '0',
  `RechargingAmountPerCycle` int(10) unsigned NOT NULL DEFAULT '0',
  `RechargingCycleDurationMS` int(10) unsigned NOT NULL DEFAULT '0',
  `Flags1` int(11) NOT NULL DEFAULT '0',
  `Flags2` int(11) NOT NULL DEFAULT '0',
  `VerifiedBuild` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`,`VerifiedBuild`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;


DROP TABLE IF EXISTS `faction_template`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `faction_template` (
  `ID` int(10) unsigned NOT NULL DEFAULT '0',
  `Faction` smallint(5) unsigned NOT NULL DEFAULT '0',
  `Flags` smallint(5) unsigned NOT NULL DEFAULT '0',
  `FactionGroup` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `FriendGroup` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `EnemyGroup` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `Enemies1` smallint(5) unsigned NOT NULL DEFAULT '0',
  `Enemies2` smallint(5) unsigned NOT NULL DEFAULT '0',
  `Enemies3` smallint(5) unsigned NOT NULL DEFAULT '0',
  `Enemies4` smallint(5) unsigned NOT NULL DEFAULT '0',
  `Enemies5` smallint(5) unsigned NOT NULL DEFAULT '0',
  `Enemies6` smallint(5) unsigned NOT NULL DEFAULT '0',
  `Enemies7` smallint(5) unsigned NOT NULL DEFAULT '0',
  `Enemies8` smallint(5) unsigned NOT NULL DEFAULT '0',
  `Friend1` smallint(5) unsigned NOT NULL DEFAULT '0',
  `Friend2` smallint(5) unsigned NOT NULL DEFAULT '0',
  `Friend3` smallint(5) unsigned NOT NULL DEFAULT '0',
  `Friend4` smallint(5) unsigned NOT NULL DEFAULT '0',
  `Friend5` smallint(5) unsigned NOT NULL DEFAULT '0',
  `Friend6` smallint(5) unsigned NOT NULL DEFAULT '0',
  `Friend7` smallint(5) unsigned NOT NULL DEFAULT '0',
  `Friend8` smallint(5) unsigned NOT NULL DEFAULT '0',
  `VerifiedBuild` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`,`VerifiedBuild`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;


DROP TABLE IF EXISTS `gossip_n_p_c_option`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `gossip_n_p_c_option` (
  `ID` int(10) unsigned NOT NULL DEFAULT '0',
  `GossipNpcOption` int(11) NOT NULL DEFAULT '0',
  `LFGDungeonsID` int(11) NOT NULL DEFAULT '0',
  `TrainerID` int(11) NOT NULL DEFAULT '0',
  `GarrFollowerTypeID` int(11) NOT NULL DEFAULT '0',
  `CharShipmentID` int(11) NOT NULL DEFAULT '0',
  `GarrTalentTreeID` int(11) NOT NULL DEFAULT '0',
  `UiMapID` int(11) NOT NULL DEFAULT '0',
  `UiItemInteractionID` int(11) NOT NULL DEFAULT '0',
  `Unknown_1000_8` int(11) NOT NULL DEFAULT '0',
  `Unknown_1000_9` int(11) NOT NULL DEFAULT '0',
  `CovenantID` int(11) NOT NULL DEFAULT '0',
  `GossipOptionID` int(11) NOT NULL DEFAULT '0',
  `TraitTreeID` int(11) NOT NULL DEFAULT '0',
  `ProfessionID` int(11) NOT NULL DEFAULT '0',
  `Unknown_1002_14` int(11) NOT NULL DEFAULT '0',
  `VerifiedBuild` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`,`VerifiedBuild`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;


DROP TABLE IF EXISTS `map`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `map` (
  `ID` int(10) unsigned NOT NULL DEFAULT '0',
  `Directory` text,
  `MapName` text,
  `MapDescription0` text,
  `MapDescription1` text,
  `PvpShortDescription` text,
  `PvpLongDescription` text,
  `CorpseX` float NOT NULL DEFAULT '0',
  `CorpseY` float NOT NULL DEFAULT '0',
  `MapType` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `InstanceType` tinyint(4) NOT NULL DEFAULT '0',
  `ExpansionID` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `AreaTableID` smallint(5) unsigned NOT NULL DEFAULT '0',
  `LoadingScreenID` smallint(6) NOT NULL DEFAULT '0',
  `TimeOfDayOverride` smallint(6) NOT NULL DEFAULT '0',
  `ParentMapID` smallint(6) NOT NULL DEFAULT '0',
  `CosmeticParentMapID` smallint(6) NOT NULL DEFAULT '0',
  `TimeOffset` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `MinimapIconScale` float NOT NULL DEFAULT '0',
  `CorpseMapID` smallint(6) NOT NULL DEFAULT '0',
  `MaxPlayers` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `WindSettingsID` smallint(6) NOT NULL DEFAULT '0',
  `ZmpFileDataID` int(11) NOT NULL DEFAULT '0',
  `WdtFileDataID` int(11) NOT NULL DEFAULT '0',
  `NavigationMaxDistance` int(10) unsigned NOT NULL DEFAULT '0',
  `Flags1` int(11) NOT NULL DEFAULT '0',
  `Flags2` int(11) NOT NULL DEFAULT '0',
  `Flags3` int(11) NOT NULL DEFAULT '0',
  `VerifiedBuild` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`,`VerifiedBuild`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;


DROP TABLE IF EXISTS `mount_capability`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `mount_capability` (
  `ID` int(10) unsigned NOT NULL DEFAULT '0',
  `Flags` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `ReqRidingSkill` smallint(5) unsigned NOT NULL DEFAULT '0',
  `ReqAreaID` smallint(5) unsigned NOT NULL DEFAULT '0',
  `ReqSpellAuraID` int(10) unsigned NOT NULL DEFAULT '0',
  `ReqSpellKnownID` int(11) NOT NULL DEFAULT '0',
  `ModSpellAuraID` int(11) NOT NULL DEFAULT '0',
  `ReqMapID` smallint(6) NOT NULL DEFAULT '0',
  `PlayerConditionID` int(11) NOT NULL DEFAULT '0',
  `FlightCapabilityID` int(11) NOT NULL DEFAULT '0',
  `VerifiedBuild` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`,`VerifiedBuild`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;


DROP TABLE IF EXISTS `player_condition`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `player_condition` (
  `ID` int(10) unsigned NOT NULL DEFAULT '0',
  `RaceMask` bigint(20) NOT NULL DEFAULT '0',
  `FailureDescription` text,
  `ClassMask` int(11) NOT NULL DEFAULT '0',
  `SkillLogic` int(10) unsigned NOT NULL DEFAULT '0',
  `LanguageID` int(11) NOT NULL DEFAULT '0',
  `MinLanguage` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `MaxLanguage` int(11) NOT NULL DEFAULT '0',
  `MaxFactionID` smallint(5) unsigned NOT NULL DEFAULT '0',
  `MaxReputation` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `ReputationLogic` int(10) unsigned NOT NULL DEFAULT '0',
  `CurrentPvpFaction` tinyint(4) NOT NULL DEFAULT '0',
  `PvpMedal` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `PrevQuestLogic` int(10) unsigned NOT NULL DEFAULT '0',
  `CurrQuestLogic` int(10) unsigned NOT NULL DEFAULT '0',
  `CurrentCompletedQuestLogic` int(10) unsigned NOT NULL DEFAULT '0',
  `SpellLogic` int(10) unsigned NOT NULL DEFAULT '0',
  `ItemLogic` int(10) unsigned NOT NULL DEFAULT '0',
  `ItemFlags` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `AuraSpellLogic` int(10) unsigned NOT NULL DEFAULT '0',
  `WorldStateExpressionID` smallint(5) unsigned NOT NULL DEFAULT '0',
  `WeatherID` int(11) NOT NULL DEFAULT '0',
  `PartyStatus` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `LifetimeMaxPVPRank` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `AchievementLogic` int(10) unsigned NOT NULL DEFAULT '0',
  `Gender` tinyint(4) NOT NULL DEFAULT '0',
  `NativeGender` tinyint(4) NOT NULL DEFAULT '0',
  `AreaLogic` int(10) unsigned NOT NULL DEFAULT '0',
  `LfgLogic` int(10) unsigned NOT NULL DEFAULT '0',
  `CurrencyLogic` int(10) unsigned NOT NULL DEFAULT '0',
  `QuestKillID` int(11) NOT NULL DEFAULT '0',
  `QuestKillLogic` int(10) unsigned NOT NULL DEFAULT '0',
  `MinExpansionLevel` tinyint(4) NOT NULL DEFAULT '0',
  `MaxExpansionLevel` tinyint(4) NOT NULL DEFAULT '0',
  `MinAvgItemLevel` int(11) NOT NULL DEFAULT '0',
  `MaxAvgItemLevel` int(11) NOT NULL DEFAULT '0',
  `MinAvgEquippedItemLevel` smallint(5) unsigned NOT NULL DEFAULT '0',
  `MaxAvgEquippedItemLevel` smallint(5) unsigned NOT NULL DEFAULT '0',
  `PhaseUseFlags` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `PhaseID` smallint(5) unsigned NOT NULL DEFAULT '0',
  `PhaseGroupID` int(10) unsigned NOT NULL DEFAULT '0',
  `Flags` int(11) NOT NULL DEFAULT '0',
  `ChrSpecializationIndex` tinyint(4) NOT NULL DEFAULT '0',
  `ChrSpecializationRole` tinyint(4) NOT NULL DEFAULT '0',
  `ModifierTreeID` int(10) unsigned NOT NULL DEFAULT '0',
  `PowerType` tinyint(4) NOT NULL DEFAULT '0',
  `PowerTypeComp` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `PowerTypeValue` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `WeaponSubclassMask` int(11) NOT NULL DEFAULT '0',
  `MaxGuildLevel` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `MinGuildLevel` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `MaxExpansionTier` tinyint(4) NOT NULL DEFAULT '0',
  `MinExpansionTier` tinyint(4) NOT NULL DEFAULT '0',
  `MinPVPRank` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `MaxPVPRank` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `ContentTuningID` int(11) NOT NULL DEFAULT '0',
  `CovenantID` int(11) NOT NULL DEFAULT '0',
  `TraitNodeEntryLogic` int(10) unsigned NOT NULL DEFAULT '0',
  `SkillID1` smallint(5) unsigned NOT NULL DEFAULT '0',
  `SkillID2` smallint(5) unsigned NOT NULL DEFAULT '0',
  `SkillID3` smallint(5) unsigned NOT NULL DEFAULT '0',
  `SkillID4` smallint(5) unsigned NOT NULL DEFAULT '0',
  `MinSkill1` smallint(5) unsigned NOT NULL DEFAULT '0',
  `MinSkill2` smallint(5) unsigned NOT NULL DEFAULT '0',
  `MinSkill3` smallint(5) unsigned NOT NULL DEFAULT '0',
  `MinSkill4` smallint(5) unsigned NOT NULL DEFAULT '0',
  `MaxSkill1` smallint(5) unsigned NOT NULL DEFAULT '0',
  `MaxSkill2` smallint(5) unsigned NOT NULL DEFAULT '0',
  `MaxSkill3` smallint(5) unsigned NOT NULL DEFAULT '0',
  `MaxSkill4` smallint(5) unsigned NOT NULL DEFAULT '0',
  `MinFactionID1` int(10) unsigned NOT NULL DEFAULT '0',
  `MinFactionID2` int(10) unsigned NOT NULL DEFAULT '0',
  `MinFactionID3` int(10) unsigned NOT NULL DEFAULT '0',
  `MinReputation1` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `MinReputation2` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `MinReputation3` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `PrevQuestID1` int(11) NOT NULL DEFAULT '0',
  `PrevQuestID2` int(11) NOT NULL DEFAULT '0',
  `PrevQuestID3` int(11) NOT NULL DEFAULT '0',
  `PrevQuestID4` int(11) NOT NULL DEFAULT '0',
  `CurrQuestID1` int(11) NOT NULL DEFAULT '0',
  `CurrQuestID2` int(11) NOT NULL DEFAULT '0',
  `CurrQuestID3` int(11) NOT NULL DEFAULT '0',
  `CurrQuestID4` int(11) NOT NULL DEFAULT '0',
  `CurrentCompletedQuestID1` int(11) NOT NULL DEFAULT '0',
  `CurrentCompletedQuestID2` int(11) NOT NULL DEFAULT '0',
  `CurrentCompletedQuestID3` int(11) NOT NULL DEFAULT '0',
  `CurrentCompletedQuestID4` int(11) NOT NULL DEFAULT '0',
  `SpellID1` int(11) NOT NULL DEFAULT '0',
  `SpellID2` int(11) NOT NULL DEFAULT '0',
  `SpellID3` int(11) NOT NULL DEFAULT '0',
  `SpellID4` int(11) NOT NULL DEFAULT '0',
  `ItemID1` int(11) NOT NULL DEFAULT '0',
  `ItemID2` int(11) NOT NULL DEFAULT '0',
  `ItemID3` int(11) NOT NULL DEFAULT '0',
  `ItemID4` int(11) NOT NULL DEFAULT '0',
  `ItemCount1` int(10) unsigned NOT NULL DEFAULT '0',
  `ItemCount2` int(10) unsigned NOT NULL DEFAULT '0',
  `ItemCount3` int(10) unsigned NOT NULL DEFAULT '0',
  `ItemCount4` int(10) unsigned NOT NULL DEFAULT '0',
  `Explored1` smallint(5) unsigned NOT NULL DEFAULT '0',
  `Explored2` smallint(5) unsigned NOT NULL DEFAULT '0',
  `Time1` int(10) unsigned NOT NULL DEFAULT '0',
  `Time2` int(10) unsigned NOT NULL DEFAULT '0',
  `AuraSpellID1` int(11) NOT NULL DEFAULT '0',
  `AuraSpellID2` int(11) NOT NULL DEFAULT '0',
  `AuraSpellID3` int(11) NOT NULL DEFAULT '0',
  `AuraSpellID4` int(11) NOT NULL DEFAULT '0',
  `AuraStacks1` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `AuraStacks2` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `AuraStacks3` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `AuraStacks4` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `Achievement1` smallint(5) unsigned NOT NULL DEFAULT '0',
  `Achievement2` smallint(5) unsigned NOT NULL DEFAULT '0',
  `Achievement3` smallint(5) unsigned NOT NULL DEFAULT '0',
  `Achievement4` smallint(5) unsigned NOT NULL DEFAULT '0',
  `AreaID1` smallint(5) unsigned NOT NULL DEFAULT '0',
  `AreaID2` smallint(5) unsigned NOT NULL DEFAULT '0',
  `AreaID3` smallint(5) unsigned NOT NULL DEFAULT '0',
  `AreaID4` smallint(5) unsigned NOT NULL DEFAULT '0',
  `LfgStatus1` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `LfgStatus2` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `LfgStatus3` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `LfgStatus4` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `LfgCompare1` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `LfgCompare2` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `LfgCompare3` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `LfgCompare4` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `LfgValue1` int(10) unsigned NOT NULL DEFAULT '0',
  `LfgValue2` int(10) unsigned NOT NULL DEFAULT '0',
  `LfgValue3` int(10) unsigned NOT NULL DEFAULT '0',
  `LfgValue4` int(10) unsigned NOT NULL DEFAULT '0',
  `CurrencyID1` int(10) unsigned NOT NULL DEFAULT '0',
  `CurrencyID2` int(10) unsigned NOT NULL DEFAULT '0',
  `CurrencyID3` int(10) unsigned NOT NULL DEFAULT '0',
  `CurrencyID4` int(10) unsigned NOT NULL DEFAULT '0',
  `CurrencyCount1` int(10) unsigned NOT NULL DEFAULT '0',
  `CurrencyCount2` int(10) unsigned NOT NULL DEFAULT '0',
  `CurrencyCount3` int(10) unsigned NOT NULL DEFAULT '0',
  `CurrencyCount4` int(10) unsigned NOT NULL DEFAULT '0',
  `QuestKillMonster1` int(10) unsigned NOT NULL DEFAULT '0',
  `QuestKillMonster2` int(10) unsigned NOT NULL DEFAULT '0',
  `QuestKillMonster3` int(10) unsigned NOT NULL DEFAULT '0',
  `QuestKillMonster4` int(10) unsigned NOT NULL DEFAULT '0',
  `QuestKillMonster5` int(10) unsigned NOT NULL DEFAULT '0',
  `QuestKillMonster6` int(10) unsigned NOT NULL DEFAULT '0',
  `MovementFlags1` int(11) NOT NULL DEFAULT '0',
  `MovementFlags2` int(11) NOT NULL DEFAULT '0',
  `TraitNodeEntryID1` int(11) NOT NULL DEFAULT '0',
  `TraitNodeEntryID2` int(11) NOT NULL DEFAULT '0',
  `TraitNodeEntryID3` int(11) NOT NULL DEFAULT '0',
  `TraitNodeEntryID4` int(11) NOT NULL DEFAULT '0',
  `TraitNodeEntryMinRank1` smallint(5) unsigned NOT NULL DEFAULT '0',
  `TraitNodeEntryMinRank2` smallint(5) unsigned NOT NULL DEFAULT '0',
  `TraitNodeEntryMinRank3` smallint(5) unsigned NOT NULL DEFAULT '0',
  `TraitNodeEntryMinRank4` smallint(5) unsigned NOT NULL DEFAULT '0',
  `TraitNodeEntryMaxRank1` smallint(5) unsigned NOT NULL DEFAULT '0',
  `TraitNodeEntryMaxRank2` smallint(5) unsigned NOT NULL DEFAULT '0',
  `TraitNodeEntryMaxRank3` smallint(5) unsigned NOT NULL DEFAULT '0',
  `TraitNodeEntryMaxRank4` smallint(5) unsigned NOT NULL DEFAULT '0',
  `VerifiedBuild` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`,`VerifiedBuild`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;


DROP TABLE IF EXISTS `pvp_talent`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `pvp_talent` (
  `Description` text,
  `ID` int(11) NOT NULL DEFAULT '0',
  `SpecID` int(11) NOT NULL DEFAULT '0',
  `SpellID` int(11) NOT NULL DEFAULT '0',
  `OverridesSpellID` int(11) NOT NULL DEFAULT '0',
  `Flags` int(11) NOT NULL DEFAULT '0',
  `ActionBarSpellID` int(11) NOT NULL DEFAULT '0',
  `PvpTalentCategoryID` int(11) NOT NULL DEFAULT '0',
  `LevelRequired` int(11) NOT NULL DEFAULT '0',
  `PlayerConditionID` int(11) NOT NULL DEFAULT '0',
  `VerifiedBuild` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`,`VerifiedBuild`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `pvp_talent`
--

LOCK TABLES `pvp_talent` WRITE;
/*!40000 ALTER TABLE `pvp_talent` DISABLE KEYS */;
/*!40000 ALTER TABLE `pvp_talent` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `pvp_talent_locale`
--

DROP TABLE IF EXISTS `pvp_talent_locale`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `pvp_talent_locale` (
  `ID` int(10) unsigned NOT NULL DEFAULT '0',
  `locale` varchar(4) NOT NULL,
  `Description_lang` text,
  `VerifiedBuild` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`,`locale`,`VerifiedBuild`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci
/*!50500 PARTITION BY LIST  COLUMNS(locale)
(PARTITION deDE VALUES IN ('deDE') ENGINE = InnoDB,
 PARTITION esES VALUES IN ('esES') ENGINE = InnoDB,
 PARTITION esMX VALUES IN ('esMX') ENGINE = InnoDB,
 PARTITION frFR VALUES IN ('frFR') ENGINE = InnoDB,
 PARTITION itIT VALUES IN ('itIT') ENGINE = InnoDB,
 PARTITION koKR VALUES IN ('koKR') ENGINE = InnoDB,
 PARTITION ptBR VALUES IN ('ptBR') ENGINE = InnoDB,
 PARTITION ruRU VALUES IN ('ruRU') ENGINE = InnoDB,
 PARTITION zhCN VALUES IN ('zhCN') ENGINE = InnoDB,
 PARTITION zhTW VALUES IN ('zhTW') ENGINE = InnoDB) */;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `pvp_talent_locale`
--

LOCK TABLES `pvp_talent_locale` WRITE;
/*!40000 ALTER TABLE `pvp_talent_locale` DISABLE KEYS */;
/*!40000 ALTER TABLE `pvp_talent_locale` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `pvp_talent_category`
--

DROP TABLE IF EXISTS `pvp_talent_category`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `pvp_talent_category` (
  `ID` int(10) unsigned NOT NULL DEFAULT '0',
  `TalentSlotMask` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `VerifiedBuild` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`,`VerifiedBuild`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `pvp_talent_category`
--

LOCK TABLES `pvp_talent_category` WRITE;
/*!40000 ALTER TABLE `pvp_talent_category` DISABLE KEYS */;
/*!40000 ALTER TABLE `pvp_talent_category` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `pvp_talent_slot_unlock`
--

DROP TABLE IF EXISTS `pvp_talent_slot_unlock`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `pvp_talent_slot_unlock` (
  `ID` int(10) unsigned NOT NULL DEFAULT '0',
  `Slot` tinyint(4) NOT NULL DEFAULT '0',
  `LevelRequired` int(11) NOT NULL DEFAULT '0',
  `DeathKnightLevelRequired` int(11) NOT NULL DEFAULT '0',
  `DemonHunterLevelRequired` int(11) NOT NULL DEFAULT '0',
  `VerifiedBuild` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`,`VerifiedBuild`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `pvp_talent_slot_unlock`
--

LOCK TABLES `pvp_talent_slot_unlock` WRITE;
/*!40000 ALTER TABLE `pvp_talent_slot_unlock` DISABLE KEYS */;
/*!40000 ALTER TABLE `pvp_talent_slot_unlock` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `pvp_tier`
--

DROP TABLE IF EXISTS `pvp_tier`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `pvp_tier` (
  `Name` text,
  `ID` int(10) unsigned NOT NULL DEFAULT '0',
  `MinRating` smallint(6) NOT NULL DEFAULT '0',
  `MaxRating` smallint(6) NOT NULL DEFAULT '0',
  `PrevTier` int(11) NOT NULL DEFAULT '0',
  `NextTier` int(11) NOT NULL DEFAULT '0',
  `BracketID` tinyint(4) NOT NULL DEFAULT '0',
  `Rank` tinyint(4) NOT NULL DEFAULT '0',
  `RankIconFileDataID` int(11) NOT NULL DEFAULT '0',
  `VerifiedBuild` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`,`VerifiedBuild`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `pvp_tier`
--

LOCK TABLES `pvp_tier` WRITE;
/*!40000 ALTER TABLE `pvp_tier` DISABLE KEYS */;
/*!40000 ALTER TABLE `pvp_tier` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `pvp_tier_locale`
--

DROP TABLE IF EXISTS `pvp_tier_locale`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `pvp_tier_locale` (
  `ID` int(10) unsigned NOT NULL DEFAULT '0',
  `locale` varchar(4) NOT NULL,
  `Name_lang` text,
  `VerifiedBuild` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`,`locale`,`VerifiedBuild`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci
/*!50500 PARTITION BY LIST  COLUMNS(locale)
(PARTITION deDE VALUES IN ('deDE') ENGINE = InnoDB,
 PARTITION esES VALUES IN ('esES') ENGINE = InnoDB,
 PARTITION esMX VALUES IN ('esMX') ENGINE = InnoDB,
 PARTITION frFR VALUES IN ('frFR') ENGINE = InnoDB,
 PARTITION itIT VALUES IN ('itIT') ENGINE = InnoDB,
 PARTITION koKR VALUES IN ('koKR') ENGINE = InnoDB,
 PARTITION ptBR VALUES IN ('ptBR') ENGINE = InnoDB,
 PARTITION ruRU VALUES IN ('ruRU') ENGINE = InnoDB,
 PARTITION zhCN VALUES IN ('zhCN') ENGINE = InnoDB,
 PARTITION zhTW VALUES IN ('zhTW') ENGINE = InnoDB) */;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `pvp_tier_locale`
--

LOCK TABLES `pvp_tier_locale` WRITE;
/*!40000 ALTER TABLE `pvp_tier_locale` DISABLE KEYS */;
/*!40000 ALTER TABLE `pvp_tier_locale` ENABLE KEYS */;
UNLOCK TABLES;


DROP TABLE IF EXISTS `skill_line_ability`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `skill_line_ability` (
  `RaceMask` bigint(20) NOT NULL DEFAULT '0',
  `AbilityVerb` text,
  `AbilityAllVerb` text,
  `ID` int(10) unsigned NOT NULL DEFAULT '0',
  `SkillLine` smallint(6) NOT NULL DEFAULT '0',
  `Spell` int(11) NOT NULL DEFAULT '0',
  `MinSkillLineRank` smallint(6) NOT NULL DEFAULT '0',
  `ClassMask` int(11) NOT NULL DEFAULT '0',
  `SupercedesSpell` int(11) NOT NULL DEFAULT '0',
  `AcquireMethod` tinyint(4) NOT NULL DEFAULT '0',
  `TrivialSkillLineRankHigh` smallint(6) NOT NULL DEFAULT '0',
  `TrivialSkillLineRankLow` smallint(6) NOT NULL DEFAULT '0',
  `Flags` int(11) NOT NULL DEFAULT '0',
  `NumSkillUps` tinyint(4) NOT NULL DEFAULT '0',
  `UniqueBit` smallint(6) NOT NULL DEFAULT '0',
  `TradeSkillCategoryID` smallint(6) NOT NULL DEFAULT '0',
  `SkillupSkillLineID` smallint(6) NOT NULL DEFAULT '0',
  `VerifiedBuild` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`,`VerifiedBuild`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `skill_line_ability`
--

LOCK TABLES `skill_line_ability` WRITE;
/*!40000 ALTER TABLE `skill_line_ability` DISABLE KEYS */;
/*!40000 ALTER TABLE `skill_line_ability` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `skill_line_ability_locale`
--

DROP TABLE IF EXISTS `skill_line_ability_locale`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `skill_line_ability_locale` (
  `ID` int(10) unsigned NOT NULL DEFAULT '0',
  `locale` varchar(4) NOT NULL,
  `AbilityVerb_lang` text,
  `AbilityAllVerb_lang` text,
  `VerifiedBuild` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`,`locale`,`VerifiedBuild`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci
/*!50500 PARTITION BY LIST  COLUMNS(locale)
(PARTITION deDE VALUES IN ('deDE') ENGINE = InnoDB,
 PARTITION esES VALUES IN ('esES') ENGINE = InnoDB,
 PARTITION esMX VALUES IN ('esMX') ENGINE = InnoDB,
 PARTITION frFR VALUES IN ('frFR') ENGINE = InnoDB,
 PARTITION itIT VALUES IN ('itIT') ENGINE = InnoDB,
 PARTITION koKR VALUES IN ('koKR') ENGINE = InnoDB,
 PARTITION ptBR VALUES IN ('ptBR') ENGINE = InnoDB,
 PARTITION ruRU VALUES IN ('ruRU') ENGINE = InnoDB,
 PARTITION zhCN VALUES IN ('zhCN') ENGINE = InnoDB,
 PARTITION zhTW VALUES IN ('zhTW') ENGINE = InnoDB) */;
/*!40101 SET character_set_client = @saved_cs_client */;


DROP TABLE IF EXISTS `sound_kit`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `sound_kit` (
  `ID` int(10) unsigned NOT NULL DEFAULT '0',
  `SoundType` int(11) NOT NULL DEFAULT '0',
  `VolumeFloat` float NOT NULL DEFAULT '0',
  `Flags` int(11) NOT NULL DEFAULT '0',
  `MinDistance` float NOT NULL DEFAULT '0',
  `DistanceCutoff` float NOT NULL DEFAULT '0',
  `EAXDef` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `SoundKitAdvancedID` int(10) unsigned NOT NULL DEFAULT '0',
  `VolumeVariationPlus` float NOT NULL DEFAULT '0',
  `VolumeVariationMinus` float NOT NULL DEFAULT '0',
  `PitchVariationPlus` float NOT NULL DEFAULT '0',
  `PitchVariationMinus` float NOT NULL DEFAULT '0',
  `DialogType` tinyint(4) NOT NULL DEFAULT '0',
  `PitchAdjust` float NOT NULL DEFAULT '0',
  `BusOverwriteID` smallint(5) unsigned NOT NULL DEFAULT '0',
  `MaxInstances` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `SoundMixGroupID` int(10) unsigned NOT NULL DEFAULT '0',
  `VerifiedBuild` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`,`VerifiedBuild`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;


DROP TABLE IF EXISTS `spell_aura_restrictions`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `spell_aura_restrictions` (
  `ID` int(10) unsigned NOT NULL DEFAULT '0',
  `DifficultyID` int(11) NOT NULL DEFAULT '0',
  `CasterAuraState` int(11) NOT NULL DEFAULT '0',
  `TargetAuraState` int(11) NOT NULL DEFAULT '0',
  `ExcludeCasterAuraState` int(11) NOT NULL DEFAULT '0',
  `ExcludeTargetAuraState` int(11) NOT NULL DEFAULT '0',
  `CasterAuraSpell` int(11) NOT NULL DEFAULT '0',
  `TargetAuraSpell` int(11) NOT NULL DEFAULT '0',
  `ExcludeCasterAuraSpell` int(11) NOT NULL DEFAULT '0',
  `ExcludeTargetAuraSpell` int(11) NOT NULL DEFAULT '0',
  `CasterAuraType` int(11) NOT NULL DEFAULT '0',
  `TargetAuraType` int(11) NOT NULL DEFAULT '0',
  `ExcludeCasterAuraType` int(11) NOT NULL DEFAULT '0',
  `ExcludeTargetAuraType` int(11) NOT NULL DEFAULT '0',
  `SpellID` int(10) unsigned NOT NULL DEFAULT '0',
  `VerifiedBuild` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`,`VerifiedBuild`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;



DROP TABLE IF EXISTS `spell_cooldowns`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `spell_cooldowns` (
  `ID` int(10) unsigned NOT NULL DEFAULT '0',
  `DifficultyID` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `CategoryRecoveryTime` int(11) NOT NULL DEFAULT '0',
  `RecoveryTime` int(11) NOT NULL DEFAULT '0',
  `StartRecoveryTime` int(11) NOT NULL DEFAULT '0',
  `AuraSpellID` int(11) NOT NULL DEFAULT '0',
  `SpellID` int(10) unsigned NOT NULL DEFAULT '0',
  `VerifiedBuild` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`,`VerifiedBuild`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;


DROP TABLE IF EXISTS `spell_power`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `spell_power` (
  `ID` int(10) unsigned NOT NULL DEFAULT '0',
  `OrderIndex` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `ManaCost` int(11) NOT NULL DEFAULT '0',
  `ManaCostPerLevel` int(11) NOT NULL DEFAULT '0',
  `ManaPerSecond` int(11) NOT NULL DEFAULT '0',
  `PowerDisplayID` int(10) unsigned NOT NULL DEFAULT '0',
  `AltPowerBarID` int(11) NOT NULL DEFAULT '0',
  `PowerCostPct` float NOT NULL DEFAULT '0',
  `PowerCostMaxPct` float NOT NULL DEFAULT '0',
  `OptionalCostPct` float NOT NULL DEFAULT '0',
  `PowerPctPerSecond` float NOT NULL DEFAULT '0',
  `PowerType` tinyint(4) NOT NULL DEFAULT '0',
  `RequiredAuraSpellID` int(11) NOT NULL DEFAULT '0',
  `OptionalCost` int(10) unsigned NOT NULL DEFAULT '0',
  `SpellID` int(10) unsigned NOT NULL DEFAULT '0',
  `VerifiedBuild` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`,`VerifiedBuild`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;


DROP TABLE IF EXISTS `spell_reagents`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `spell_reagents` (
  `ID` int(10) unsigned NOT NULL DEFAULT '0',
  `SpellID` int(11) NOT NULL DEFAULT '0',
  `Reagent1` int(11) NOT NULL DEFAULT '0',
  `Reagent2` int(11) NOT NULL DEFAULT '0',
  `Reagent3` int(11) NOT NULL DEFAULT '0',
  `Reagent4` int(11) NOT NULL DEFAULT '0',
  `Reagent5` int(11) NOT NULL DEFAULT '0',
  `Reagent6` int(11) NOT NULL DEFAULT '0',
  `Reagent7` int(11) NOT NULL DEFAULT '0',
  `Reagent8` int(11) NOT NULL DEFAULT '0',
  `ReagentCount1` smallint(6) NOT NULL DEFAULT '0',
  `ReagentCount2` smallint(6) NOT NULL DEFAULT '0',
  `ReagentCount3` smallint(6) NOT NULL DEFAULT '0',
  `ReagentCount4` smallint(6) NOT NULL DEFAULT '0',
  `ReagentCount5` smallint(6) NOT NULL DEFAULT '0',
  `ReagentCount6` smallint(6) NOT NULL DEFAULT '0',
  `ReagentCount7` smallint(6) NOT NULL DEFAULT '0',
  `ReagentCount8` smallint(6) NOT NULL DEFAULT '0',
  `ReagentRecraftCount1` smallint(6) NOT NULL DEFAULT '0',
  `ReagentRecraftCount2` smallint(6) NOT NULL DEFAULT '0',
  `ReagentRecraftCount3` smallint(6) NOT NULL DEFAULT '0',
  `ReagentRecraftCount4` smallint(6) NOT NULL DEFAULT '0',
  `ReagentRecraftCount5` smallint(6) NOT NULL DEFAULT '0',
  `ReagentRecraftCount6` smallint(6) NOT NULL DEFAULT '0',
  `ReagentRecraftCount7` smallint(6) NOT NULL DEFAULT '0',
  `ReagentRecraftCount8` smallint(6) NOT NULL DEFAULT '0',
  `ReagentSource1` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `ReagentSource2` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `ReagentSource3` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `ReagentSource4` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `ReagentSource5` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `ReagentSource6` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `ReagentSource7` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `ReagentSource8` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `VerifiedBuild` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`,`VerifiedBuild`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;


DROP TABLE IF EXISTS `spell_x_spell_visual`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `spell_x_spell_visual` (
  `ID` int(10) unsigned NOT NULL DEFAULT '0',
  `DifficultyID` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `SpellVisualID` int(10) unsigned NOT NULL DEFAULT '0',
  `Probability` float NOT NULL DEFAULT '0',
  `Flags` int(11) NOT NULL DEFAULT '0',
  `Priority` int(11) NOT NULL DEFAULT '0',
  `SpellIconFileID` int(11) NOT NULL DEFAULT '0',
  `ActiveIconFileID` int(11) NOT NULL DEFAULT '0',
  `ViewerUnitConditionID` smallint(5) unsigned NOT NULL DEFAULT '0',
  `ViewerPlayerConditionID` int(10) unsigned NOT NULL DEFAULT '0',
  `CasterUnitConditionID` smallint(5) unsigned NOT NULL DEFAULT '0',
  `CasterPlayerConditionID` int(10) unsigned NOT NULL DEFAULT '0',
  `SpellID` int(10) unsigned NOT NULL DEFAULT '0',
  `VerifiedBuild` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`,`VerifiedBuild`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;


DROP TABLE IF EXISTS `ui_map_link`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `ui_map_link` (
  `UiMinX` float NOT NULL DEFAULT '0',
  `UiMinY` float NOT NULL DEFAULT '0',
  `UiMaxX` float NOT NULL DEFAULT '0',
  `UiMaxY` float NOT NULL DEFAULT '0',
  `ID` int(10) unsigned NOT NULL DEFAULT '0',
  `ParentUiMapID` int(11) NOT NULL DEFAULT '0',
  `OrderIndex` int(11) NOT NULL DEFAULT '0',
  `ChildUiMapID` int(11) NOT NULL DEFAULT '0',
  `PlayerConditionID` int(11) NOT NULL DEFAULT '0',
  `OverrideHighlightFileDataID` int(11) NOT NULL DEFAULT '0',
  `OverrideHighlightAtlasID` int(11) NOT NULL DEFAULT '0',
  `Flags` int(11) NOT NULL DEFAULT '0',
  `VerifiedBuild` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`,`VerifiedBuild`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;
