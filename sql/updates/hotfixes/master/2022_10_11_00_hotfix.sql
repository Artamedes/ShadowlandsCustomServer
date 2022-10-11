
DROP TABLE IF EXISTS `spell`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `spell` (
  `ID` int(11) NOT NULL DEFAULT '0',
  `NameSubtext` text,
  `Description` text,
  `AuraDescription` text,
  `VerifiedBuild` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`,`VerifiedBuild`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `spell`
--

LOCK TABLES `spell` WRITE;
/*!40000 ALTER TABLE `spell` DISABLE KEYS */;
/*!40000 ALTER TABLE `spell` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `spell_locale`
--

DROP TABLE IF EXISTS `spell_locale`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `spell_locale` (
  `ID` int(10) unsigned NOT NULL DEFAULT '0',
  `locale` varchar(4) NOT NULL,
  `NameSubtext_lang` text,
  `Description_lang` text,
  `AuraDescription_lang` text,
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
-- Dumping data for table `spell_locale`
--

LOCK TABLES `spell_locale` WRITE;
/*!40000 ALTER TABLE `spell_locale` DISABLE KEYS */;
/*!40000 ALTER TABLE `spell_locale` ENABLE KEYS */;
UNLOCK TABLES;


--
-- Table structure for table `char_start_outfit`
--

DROP TABLE IF EXISTS `char_start_outfit`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `char_start_outfit` (
  `ID` int(11) NOT NULL DEFAULT '0',
  `ClassID` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `SexID` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `OutfitID` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `PetDisplayID` int(10) unsigned NOT NULL DEFAULT '0',
  `PetFamilyID` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `ItemID1` int(11) NOT NULL DEFAULT '0',
  `ItemID2` int(11) NOT NULL DEFAULT '0',
  `ItemID3` int(11) NOT NULL DEFAULT '0',
  `ItemID4` int(11) NOT NULL DEFAULT '0',
  `ItemID5` int(11) NOT NULL DEFAULT '0',
  `ItemID6` int(11) NOT NULL DEFAULT '0',
  `ItemID7` int(11) NOT NULL DEFAULT '0',
  `ItemID8` int(11) NOT NULL DEFAULT '0',
  `ItemID9` int(11) NOT NULL DEFAULT '0',
  `ItemID10` int(11) NOT NULL DEFAULT '0',
  `ItemID11` int(11) NOT NULL DEFAULT '0',
  `ItemID12` int(11) NOT NULL DEFAULT '0',
  `ItemID13` int(11) NOT NULL DEFAULT '0',
  `ItemID14` int(11) NOT NULL DEFAULT '0',
  `ItemID15` int(11) NOT NULL DEFAULT '0',
  `ItemID16` int(11) NOT NULL DEFAULT '0',
  `ItemID17` int(11) NOT NULL DEFAULT '0',
  `ItemID18` int(11) NOT NULL DEFAULT '0',
  `ItemID19` int(11) NOT NULL DEFAULT '0',
  `ItemID20` int(11) NOT NULL DEFAULT '0',
  `ItemID21` int(11) NOT NULL DEFAULT '0',
  `ItemID22` int(11) NOT NULL DEFAULT '0',
  `ItemID23` int(11) NOT NULL DEFAULT '0',
  `ItemID24` int(11) NOT NULL DEFAULT '0',
  `RaceID` int(11) NOT NULL DEFAULT '0',
  `VerifiedBuild` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`,`VerifiedBuild`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `char_start_outfit`
--

LOCK TABLES `char_start_outfit` WRITE;
/*!40000 ALTER TABLE `char_start_outfit` DISABLE KEYS */;
/*!40000 ALTER TABLE `char_start_outfit` ENABLE KEYS */;
UNLOCK TABLES;

