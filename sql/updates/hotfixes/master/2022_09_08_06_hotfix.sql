

DROP TABLE IF EXISTS `trait_edge`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `trait_edge` (
  `ID` int(11) NOT NULL DEFAULT '0',
  `VisualStyle` int(11) NOT NULL DEFAULT '0',
  `LeftTraitNodeID` int(11) NOT NULL DEFAULT '0',
  `RightTraitNodeID` int(11) NOT NULL DEFAULT '0',
  `Type` int(11) NOT NULL DEFAULT '0',
  `VerifiedBuild` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`,`VerifiedBuild`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `trait_edge`
--

LOCK TABLES `trait_edge` WRITE;
/*!40000 ALTER TABLE `trait_edge` DISABLE KEYS */;
/*!40000 ALTER TABLE `trait_edge` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `trait_node`
--

DROP TABLE IF EXISTS `trait_node`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `trait_node` (
  `ID` int(11) NOT NULL DEFAULT '0',
  `TraitTreeID` int(11) NOT NULL DEFAULT '0',
  `PosX` int(11) NOT NULL DEFAULT '0',
  `PosY` int(11) NOT NULL DEFAULT '0',
  `Type` int(11) NOT NULL DEFAULT '0',
  `Flags` int(11) NOT NULL DEFAULT '0',
  `VerifiedBuild` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`,`VerifiedBuild`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `trait_node`
--

LOCK TABLES `trait_node` WRITE;
/*!40000 ALTER TABLE `trait_node` DISABLE KEYS */;
/*!40000 ALTER TABLE `trait_node` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `trait_node_entry`
--

DROP TABLE IF EXISTS `trait_node_entry`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `trait_node_entry` (
  `ID` int(11) NOT NULL DEFAULT '0',
  `TraitDefinitionID` int(11) NOT NULL DEFAULT '0',
  `MaxRanks` int(11) NOT NULL DEFAULT '0',
  `NodeEntryType` int(11) NOT NULL DEFAULT '0',
  `VerifiedBuild` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`,`VerifiedBuild`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `trait_node_entry`
--

LOCK TABLES `trait_node_entry` WRITE;
/*!40000 ALTER TABLE `trait_node_entry` DISABLE KEYS */;
/*!40000 ALTER TABLE `trait_node_entry` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `trait_node_entry_x_trait_cost`
--

DROP TABLE IF EXISTS `trait_node_entry_x_trait_cost`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `trait_node_entry_x_trait_cost` (
  `ID` int(11) NOT NULL DEFAULT '0',
  `TraitNodeEntryID` int(11) NOT NULL DEFAULT '0',
  `TraitCostID` int(11) NOT NULL DEFAULT '0',
  `VerifiedBuild` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`,`VerifiedBuild`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `trait_node_entry_x_trait_cost`
--

LOCK TABLES `trait_node_entry_x_trait_cost` WRITE;
/*!40000 ALTER TABLE `trait_node_entry_x_trait_cost` DISABLE KEYS */;
/*!40000 ALTER TABLE `trait_node_entry_x_trait_cost` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `trait_node_group`
--

DROP TABLE IF EXISTS `trait_node_group`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `trait_node_group` (
  `ID` int(11) NOT NULL DEFAULT '0',
  `TraitTreeID` int(11) NOT NULL DEFAULT '0',
  `Flags` int(11) NOT NULL DEFAULT '0',
  `VerifiedBuild` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`,`VerifiedBuild`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `trait_node_group`
--

LOCK TABLES `trait_node_group` WRITE;
/*!40000 ALTER TABLE `trait_node_group` DISABLE KEYS */;
/*!40000 ALTER TABLE `trait_node_group` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `trait_node_group_x_trait_cond`
--

DROP TABLE IF EXISTS `trait_node_group_x_trait_cond`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `trait_node_group_x_trait_cond` (
  `ID` int(11) NOT NULL DEFAULT '0',
  `TraitCondID` int(11) NOT NULL DEFAULT '0',
  `TraitNodeGroupID` int(11) NOT NULL DEFAULT '0',
  `VerifiedBuild` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`,`VerifiedBuild`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `trait_node_group_x_trait_cond`
--

LOCK TABLES `trait_node_group_x_trait_cond` WRITE;
/*!40000 ALTER TABLE `trait_node_group_x_trait_cond` DISABLE KEYS */;
/*!40000 ALTER TABLE `trait_node_group_x_trait_cond` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `trait_node_group_x_trait_cost`
--

DROP TABLE IF EXISTS `trait_node_group_x_trait_cost`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `trait_node_group_x_trait_cost` (
  `ID` int(11) NOT NULL DEFAULT '0',
  `TraitNodeGroupID` int(11) NOT NULL DEFAULT '0',
  `TraitCostID` int(11) NOT NULL DEFAULT '0',
  `VerifiedBuild` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`,`VerifiedBuild`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `trait_node_group_x_trait_cost`
--

LOCK TABLES `trait_node_group_x_trait_cost` WRITE;
/*!40000 ALTER TABLE `trait_node_group_x_trait_cost` DISABLE KEYS */;
/*!40000 ALTER TABLE `trait_node_group_x_trait_cost` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `trait_node_group_x_trait_node`
--

DROP TABLE IF EXISTS `trait_node_group_x_trait_node`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `trait_node_group_x_trait_node` (
  `ID` int(11) NOT NULL DEFAULT '0',
  `TraitNodeGroupID` int(11) NOT NULL DEFAULT '0',
  `TraitNodeID` int(11) NOT NULL DEFAULT '0',
  `Index` int(11) NOT NULL DEFAULT '0',
  `VerifiedBuild` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`,`VerifiedBuild`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `trait_node_group_x_trait_node`
--

LOCK TABLES `trait_node_group_x_trait_node` WRITE;
/*!40000 ALTER TABLE `trait_node_group_x_trait_node` DISABLE KEYS */;
/*!40000 ALTER TABLE `trait_node_group_x_trait_node` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `trait_node_x_trait_cond`
--

DROP TABLE IF EXISTS `trait_node_x_trait_cond`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `trait_node_x_trait_cond` (
  `ID` int(11) NOT NULL DEFAULT '0',
  `TraitCondID` int(11) NOT NULL DEFAULT '0',
  `TraitNodeID` int(11) NOT NULL DEFAULT '0',
  `VerifiedBuild` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`,`VerifiedBuild`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `trait_node_x_trait_cond`
--

LOCK TABLES `trait_node_x_trait_cond` WRITE;
/*!40000 ALTER TABLE `trait_node_x_trait_cond` DISABLE KEYS */;
/*!40000 ALTER TABLE `trait_node_x_trait_cond` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `trait_node_x_trait_node_entry`
--

DROP TABLE IF EXISTS `trait_node_x_trait_node_entry`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `trait_node_x_trait_node_entry` (
  `ID` int(11) NOT NULL DEFAULT '0',
  `TraitNodeID` int(11) NOT NULL DEFAULT '0',
  `TraitNodeEntryID` int(11) NOT NULL DEFAULT '0',
  `Index` int(11) NOT NULL DEFAULT '0',
  `VerifiedBuild` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`,`VerifiedBuild`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `trait_node_x_trait_node_entry`
--

LOCK TABLES `trait_node_x_trait_node_entry` WRITE;
/*!40000 ALTER TABLE `trait_node_x_trait_node_entry` DISABLE KEYS */;
/*!40000 ALTER TABLE `trait_node_x_trait_node_entry` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `trait_tree`
--

DROP TABLE IF EXISTS `trait_tree`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `trait_tree` (
  `Name` text,
  `ID` int(11) NOT NULL DEFAULT '0',
  `Field_10_0_0_44707_002` int(11) NOT NULL DEFAULT '0',
  `TraitTreeID` int(11) NOT NULL DEFAULT '0',
  `FirstTraitNodeID` int(11) NOT NULL DEFAULT '0',
  `PlayerConditionID` int(11) NOT NULL DEFAULT '0',
  `Flags` int(11) NOT NULL DEFAULT '0',
  `VerifiedBuild` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`,`VerifiedBuild`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `trait_tree`
--

LOCK TABLES `trait_tree` WRITE;
/*!40000 ALTER TABLE `trait_tree` DISABLE KEYS */;
/*!40000 ALTER TABLE `trait_tree` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `trait_tree_loadout`
--

DROP TABLE IF EXISTS `trait_tree_loadout`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `trait_tree_loadout` (
  `ID` int(11) NOT NULL DEFAULT '0',
  `TraitTreeID` int(11) NOT NULL DEFAULT '0',
  `Field_10_0_0_45232_002` int(11) NOT NULL DEFAULT '0',
  `VerifiedBuild` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`,`VerifiedBuild`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `trait_tree_loadout`
--

LOCK TABLES `trait_tree_loadout` WRITE;
/*!40000 ALTER TABLE `trait_tree_loadout` DISABLE KEYS */;
/*!40000 ALTER TABLE `trait_tree_loadout` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `trait_tree_loadout_entry`
--

DROP TABLE IF EXISTS `trait_tree_loadout_entry`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `trait_tree_loadout_entry` (
  `ID` int(11) NOT NULL DEFAULT '0',
  `TraitTreeLoadoutID` int(11) NOT NULL DEFAULT '0',
  `SelectedTraitNodeID` int(11) NOT NULL DEFAULT '0',
  `SelectedTraitNodeEntryID` int(11) NOT NULL DEFAULT '0',
  `NumPoints` int(11) NOT NULL DEFAULT '0',
  `OrderIndex` int(11) NOT NULL DEFAULT '0',
  `VerifiedBuild` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`,`VerifiedBuild`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `trait_tree_loadout_entry`
--

LOCK TABLES `trait_tree_loadout_entry` WRITE;
/*!40000 ALTER TABLE `trait_tree_loadout_entry` DISABLE KEYS */;
/*!40000 ALTER TABLE `trait_tree_loadout_entry` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `trait_tree_x_trait_currency`
--

DROP TABLE IF EXISTS `trait_tree_x_trait_currency`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `trait_tree_x_trait_currency` (
  `ID` int(11) NOT NULL DEFAULT '0',
  `Index` int(11) NOT NULL DEFAULT '0',
  `TraitTreeID` int(11) NOT NULL DEFAULT '0',
  `TraitCurrencyID` int(11) NOT NULL DEFAULT '0',
  `VerifiedBuild` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`,`VerifiedBuild`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `trait_tree_x_trait_currency`
--

LOCK TABLES `trait_tree_x_trait_currency` WRITE;
/*!40000 ALTER TABLE `trait_tree_x_trait_currency` DISABLE KEYS */;
/*!40000 ALTER TABLE `trait_tree_x_trait_currency` ENABLE KEYS */;
UNLOCK TABLES;



DROP TABLE IF EXISTS `runeforge_legendary_ability_locale`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `runeforge_legendary_ability_locale` (
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
-- Dumping data for table `runeforge_legendary_ability_locale`
--

LOCK TABLES `runeforge_legendary_ability_locale` WRITE;
/*!40000 ALTER TABLE `runeforge_legendary_ability_locale` DISABLE KEYS */;
/*!40000 ALTER TABLE `runeforge_legendary_ability_locale` ENABLE KEYS */;
UNLOCK TABLES;

--


--
-- Table structure for table `garr_talent_tree_locale`
--

DROP TABLE IF EXISTS `garr_talent_tree_locale`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `garr_talent_tree_locale` (
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
-- Dumping data for table `garr_talent_tree_locale`
--

LOCK TABLES `garr_talent_tree_locale` WRITE;
/*!40000 ALTER TABLE `garr_talent_tree_locale` DISABLE KEYS */;
/*!40000 ALTER TABLE `garr_talent_tree_locale` ENABLE KEYS */;
UNLOCK TABLES;


DROP TABLE IF EXISTS `chr_customization_req_locale`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `chr_customization_req_locale` (
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
-- Dumping data for table `chr_customization_req_locale`
--

LOCK TABLES `chr_customization_req_locale` WRITE;
/*!40000 ALTER TABLE `chr_customization_req_locale` DISABLE KEYS */;
/*!40000 ALTER TABLE `chr_customization_req_locale` ENABLE KEYS */;
UNLOCK TABLES;


--
-- Table structure for table `skill_line_ability`
--

DROP TABLE IF EXISTS `skill_line_ability`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `skill_line_ability` (
  `RaceMask` bigint(20) NOT NULL DEFAULT '0',
  `Field_10_0_0_44795_001` text,
  `Field_10_0_0_44795_002` text,
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
  `Field_10_0_0_44795_001_lang` text,
  `Field_10_0_0_44795_002_lang` text,
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
-- Dumping data for table `skill_line_ability_locale`
--

LOCK TABLES `skill_line_ability_locale` WRITE;
/*!40000 ALTER TABLE `skill_line_ability_locale` DISABLE KEYS */;
/*!40000 ALTER TABLE `skill_line_ability_locale` ENABLE KEYS */;
UNLOCK TABLES;

--


--
-- Table structure for table `renown_rewards_locale`
--

DROP TABLE IF EXISTS `renown_rewards_locale`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `renown_rewards_locale` (
  `ID` int(10) unsigned NOT NULL DEFAULT '0',
  `locale` varchar(4) NOT NULL,
  `Name_lang` text,
  `Description_lang` text,
  `ToastDescription_lang` text,
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
-- Dumping data for table `renown_rewards_locale`
--

LOCK TABLES `renown_rewards_locale` WRITE;
/*!40000 ALTER TABLE `renown_rewards_locale` DISABLE KEYS */;
/*!40000 ALTER TABLE `renown_rewards_locale` ENABLE KEYS */;
UNLOCK TABLES;


--
-- Table structure for table `vignette_locale`
--

DROP TABLE IF EXISTS `vignette_locale`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `vignette_locale` (
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
-- Dumping data for table `vignette_locale`
--

LOCK TABLES `vignette_locale` WRITE;
/*!40000 ALTER TABLE `vignette_locale` DISABLE KEYS */;
/*!40000 ALTER TABLE `vignette_locale` ENABLE KEYS */;
UNLOCK TABLES;

--

--
-- Table structure for table `soulbind_conduit_enhanced_socket`
--

DROP TABLE IF EXISTS `soulbind_conduit_enhanced_socket`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `soulbind_conduit_enhanced_socket` (
  `ID` int(10) unsigned NOT NULL DEFAULT '0',
  `GarrTalentID` int(10) unsigned NOT NULL DEFAULT '0',
  `PlayerConditionEntry` int(10) unsigned NOT NULL DEFAULT '0',
  `VerifiedBuild` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`,`VerifiedBuild`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `soulbind_conduit_enhanced_socket`
--

LOCK TABLES `soulbind_conduit_enhanced_socket` WRITE;
/*!40000 ALTER TABLE `soulbind_conduit_enhanced_socket` DISABLE KEYS */;
/*!40000 ALTER TABLE `soulbind_conduit_enhanced_socket` ENABLE KEYS */;
UNLOCK TABLES;


--
-- Table structure for table `soulbind_locale`
--

DROP TABLE IF EXISTS `soulbind_locale`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `soulbind_locale` (
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
-- Dumping data for table `soulbind_locale`
--

LOCK TABLES `soulbind_locale` WRITE;
/*!40000 ALTER TABLE `soulbind_locale` DISABLE KEYS */;
/*!40000 ALTER TABLE `soulbind_locale` ENABLE KEYS */;
UNLOCK TABLES;

--


--
-- Table structure for table `garr_talent_locale`
--

DROP TABLE IF EXISTS `garr_talent_locale`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `garr_talent_locale` (
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
-- Dumping data for table `garr_talent_locale`
--

LOCK TABLES `garr_talent_locale` WRITE;
/*!40000 ALTER TABLE `garr_talent_locale` DISABLE KEYS */;
/*!40000 ALTER TABLE `garr_talent_locale` ENABLE KEYS */;
UNLOCK TABLES;

--

--
-- Table structure for table `trait_definition`
--

DROP TABLE IF EXISTS `trait_definition`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `trait_definition` (
  `OverrideName` text,
  `OverrideSubtext` text,
  `OverrideDescription` text,
  `ID` int(11) NOT NULL DEFAULT '0',
  `SpellID` int(11) NOT NULL DEFAULT '0',
  `OverrideIcon` int(11) NOT NULL DEFAULT '0',
  `OverridesSpellID` int(11) NOT NULL DEFAULT '0',
  `Field_10_0_0_45232_007` int(11) NOT NULL DEFAULT '0',
  `VerifiedBuild` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`,`VerifiedBuild`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `trait_definition`
--

LOCK TABLES `trait_definition` WRITE;
/*!40000 ALTER TABLE `trait_definition` DISABLE KEYS */;
/*!40000 ALTER TABLE `trait_definition` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `trait_definition_locale`
--

DROP TABLE IF EXISTS `trait_definition_locale`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `trait_definition_locale` (
  `ID` int(10) unsigned NOT NULL DEFAULT '0',
  `locale` varchar(4) NOT NULL,
  `OverrideName_lang` text,
  `OverrideSubtext_lang` text,
  `OverrideDescription_lang` text,
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
-- Dumping data for table `trait_definition_locale`
--

LOCK TABLES `trait_definition_locale` WRITE;
/*!40000 ALTER TABLE `trait_definition_locale` DISABLE KEYS */;
/*!40000 ALTER TABLE `trait_definition_locale` ENABLE KEYS */;
UNLOCK TABLES;
