

--
-- Table structure for table `gossip_n_p_c_option`
--

DROP TABLE IF EXISTS `gossip_n_p_c_option`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `gossip_n_p_c_option` (
  `ID` int(10) unsigned NOT NULL DEFAULT '0',
  `GossipNpcOption` int(10) unsigned NOT NULL DEFAULT '0',
  `LFGDungeonsID` int(10) unsigned NOT NULL DEFAULT '0',
  `TrainerID` int(10) unsigned NOT NULL DEFAULT '0',
  `GarrFollowerTypeID` int(10) unsigned NOT NULL DEFAULT '0',
  `CharShipmentID` int(10) unsigned NOT NULL DEFAULT '0',
  `GarrTalentTreeID` int(10) unsigned NOT NULL DEFAULT '0',
  `UiMapID` int(10) unsigned NOT NULL DEFAULT '0',
  `UiItemInteractionID` int(10) unsigned NOT NULL DEFAULT '0',
  `Field_10_0_0_45141_008` int(10) unsigned NOT NULL DEFAULT '0',
  `Field_10_0_0_45141_009` int(10) unsigned NOT NULL DEFAULT '0',
  `CovenantID` int(10) unsigned NOT NULL DEFAULT '0',
  `GossipIndex` int(10) unsigned NOT NULL DEFAULT '0',
  `TraitTreeID` int(10) unsigned NOT NULL DEFAULT '0',
  `ProfessionID` int(10) unsigned NOT NULL DEFAULT '0',
  `Field_10_0_2_46144_014` int(11) NOT NULL DEFAULT '0',
  `VerifiedBuild` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`,`VerifiedBuild`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `gossip_n_p_c_option`
--

LOCK TABLES `gossip_n_p_c_option` WRITE;
/*!40000 ALTER TABLE `gossip_n_p_c_option` DISABLE KEYS */;
/*!40000 ALTER TABLE `gossip_n_p_c_option` ENABLE KEYS */;
UNLOCK TABLES;


--
-- Table structure for table `campaign`
--

DROP TABLE IF EXISTS `campaign`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `campaign` (
  `ID` int(11) NOT NULL DEFAULT '0',
  `Title` text,
  `InternalTitle` text,
  `Description` text,
  `UiTextureKitID` int(11) NOT NULL DEFAULT '0',
  `RewardQuestID` int(11) NOT NULL DEFAULT '0',
  `Prerequisite` int(11) NOT NULL DEFAULT '0',
  `Field90135755007` int(11) NOT NULL DEFAULT '0',
  `Completed` int(11) NOT NULL DEFAULT '0',
  `OnlyStallIf` int(11) NOT NULL DEFAULT '0',
  `UiQuestDetailsThemeID` int(11) NOT NULL DEFAULT '0',
  `Flags` int(10) unsigned NOT NULL DEFAULT '0',
  `DisplayPriority` int(11) NOT NULL DEFAULT '0',
  `Field100245779012` int(11) NOT NULL DEFAULT '0',
  `VerifiedBuild` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`,`VerifiedBuild`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `campaign`
--

LOCK TABLES `campaign` WRITE;
/*!40000 ALTER TABLE `campaign` DISABLE KEYS */;
/*!40000 ALTER TABLE `campaign` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `campaign_locale`
--

DROP TABLE IF EXISTS `campaign_locale`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `campaign_locale` (
  `ID` int(10) unsigned NOT NULL DEFAULT '0',
  `locale` varchar(4) NOT NULL,
  `Title_lang` text,
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
-- Dumping data for table `campaign_locale`
--

LOCK TABLES `campaign_locale` WRITE;
/*!40000 ALTER TABLE `campaign_locale` DISABLE KEYS */;
/*!40000 ALTER TABLE `campaign_locale` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `campaign_x_quest_line`
--

DROP TABLE IF EXISTS `campaign_x_quest_line`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `campaign_x_quest_line` (
  `ID` int(11) NOT NULL DEFAULT '0',
  `CampaignID` int(10) unsigned NOT NULL DEFAULT '0',
  `QuestLineID` int(10) unsigned NOT NULL DEFAULT '0',
  `OrderIndex` int(10) unsigned NOT NULL DEFAULT '0',
  `VerifiedBuild` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`,`VerifiedBuild`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `campaign_x_quest_line`
--

LOCK TABLES `campaign_x_quest_line` WRITE;
/*!40000 ALTER TABLE `campaign_x_quest_line` DISABLE KEYS */;
/*!40000 ALTER TABLE `campaign_x_quest_line` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `quest_line`
--

DROP TABLE IF EXISTS `quest_line`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `quest_line` (
  `ID` int(11) NOT NULL DEFAULT '0',
  `Name` text,
  `Description` text,
  `QuestID` int(10) unsigned NOT NULL DEFAULT '0',
  `PlayerConditionID` int(11) NOT NULL DEFAULT '0',
  `VerifiedBuild` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`,`VerifiedBuild`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `quest_line`
--

LOCK TABLES `quest_line` WRITE;
/*!40000 ALTER TABLE `quest_line` DISABLE KEYS */;
/*!40000 ALTER TABLE `quest_line` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `quest_line_locale`
--

DROP TABLE IF EXISTS `quest_line_locale`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `quest_line_locale` (
  `ID` int(10) unsigned NOT NULL DEFAULT '0',
  `locale` varchar(4) NOT NULL,
  `Name_lang` text,
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
-- Dumping data for table `quest_line_locale`
--

LOCK TABLES `quest_line_locale` WRITE;
/*!40000 ALTER TABLE `quest_line_locale` DISABLE KEYS */;
/*!40000 ALTER TABLE `quest_line_locale` ENABLE KEYS */;
UNLOCK TABLES;

