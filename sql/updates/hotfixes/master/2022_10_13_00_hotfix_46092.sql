
--
-- Table structure for table `currency_types`
--

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
  `Field_10_0_2_46091_014` int(10) unsigned NOT NULL DEFAULT '0',
  `Field_10_0_2_46091_015` int(10) unsigned NOT NULL DEFAULT '0',
  `Flags1` int(11) NOT NULL DEFAULT '0',
  `Flags2` int(11) NOT NULL DEFAULT '0',
  `VerifiedBuild` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`,`VerifiedBuild`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `currency_types`
--

LOCK TABLES `currency_types` WRITE;
/*!40000 ALTER TABLE `currency_types` DISABLE KEYS */;
/*!40000 ALTER TABLE `currency_types` ENABLE KEYS */;
UNLOCK TABLES;




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
  `RequiredQuality1` smallint(6) NOT NULL DEFAULT '0',
  `RequiredQuality2` smallint(6) NOT NULL DEFAULT '0',
  `RequiredQuality3` smallint(6) NOT NULL DEFAULT '0',
  `RequiredQuality4` smallint(6) NOT NULL DEFAULT '0',
  `RequiredQuality5` smallint(6) NOT NULL DEFAULT '0',
  `RequiredQuality6` smallint(6) NOT NULL DEFAULT '0',
  `RequiredQuality7` smallint(6) NOT NULL DEFAULT '0',
  `RequiredQuality8` smallint(6) NOT NULL DEFAULT '0',
  `Field_10_0_2_46091_0041` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `Field_10_0_2_46091_0042` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `Field_10_0_2_46091_0043` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `Field_10_0_2_46091_0044` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `Field_10_0_2_46091_0045` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `Field_10_0_2_46091_0046` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `Field_10_0_2_46091_0047` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `Field_10_0_2_46091_0048` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `VerifiedBuild` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`,`VerifiedBuild`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `spell_reagents`
--

LOCK TABLES `spell_reagents` WRITE;
/*!40000 ALTER TABLE `spell_reagents` DISABLE KEYS */;
/*!40000 ALTER TABLE `spell_reagents` ENABLE KEYS */;
UNLOCK TABLES;
