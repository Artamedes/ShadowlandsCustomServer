ALTER TABLE `campaign`
	ADD COLUMN `Field1002` INT(10) NOT NULL DEFAULT '0' AFTER `Field100245779012`;


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
  `Field1002` int(11) NOT NULL DEFAULT '0',
  `VerifiedBuild` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`,`VerifiedBuild`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;


DROP TABLE IF EXISTS `journal_instance`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `journal_instance` (
  `ID` int(11) NOT NULL DEFAULT '0',
  `Name` text,
  `Description` text,
  `MapID` smallint(5) unsigned NOT NULL DEFAULT '0',
  `BackgroundFileDataID` int(11) NOT NULL DEFAULT '0',
  `ButtonFileDataID` int(11) NOT NULL DEFAULT '0',
  `ButtonSmallFileDataID` int(11) NOT NULL DEFAULT '0',
  `LoreFileDataID` int(11) NOT NULL DEFAULT '0',
  `Flags` int(11) NOT NULL DEFAULT '0',
  `AreaID` smallint(5) unsigned NOT NULL DEFAULT '0',
  `VerifiedBuild` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`,`VerifiedBuild`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;
