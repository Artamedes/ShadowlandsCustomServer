
DROP TABLE IF EXISTS `skill_line`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `skill_line` (
  `DisplayName` text,
  `AlternateVerb` text,
  `Description` text,
  `HordeDisplayName` text,
  `OverrideSourceInfoDisplayName` text,
  `ID` int(10) unsigned NOT NULL DEFAULT '0',
  `CategoryID` tinyint(4) NOT NULL DEFAULT '0',
  `SpellIconFileID` int(11) NOT NULL DEFAULT '0',
  `CanLink` tinyint(4) NOT NULL DEFAULT '0',
  `ParentSkillLineID` int(10) unsigned NOT NULL DEFAULT '0',
  `ParentTierIndex` int(11) NOT NULL DEFAULT '0',
  `Flags` smallint(5) unsigned NOT NULL DEFAULT '0',
  `SpellBookSpellID` int(11) NOT NULL DEFAULT '0',
  `AllianceSharedStringID` int(11) NOT NULL DEFAULT '0',
  `HordeSharedStringID` int(11) NOT NULL DEFAULT '0',
  `VerifiedBuild` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`,`VerifiedBuild`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;


--
-- Table structure for table `spell_power`
--

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
  `PowerPctPerSecond` float NOT NULL DEFAULT '0',
  `Field_10_0_2_45969_009` float NOT NULL DEFAULT '0',
  `PowerType` tinyint(4) NOT NULL DEFAULT '0',
  `RequiredAuraSpellID` int(11) NOT NULL DEFAULT '0',
  `OptionalCost` int(10) unsigned NOT NULL DEFAULT '0',
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
  `Field_10_0_2_45969_006` int(11) NOT NULL DEFAULT '0',
  `OverrideHighlightFileDataID` int(11) NOT NULL DEFAULT '0',
  `OverrideHighlightAtlasID` int(11) NOT NULL DEFAULT '0',
  `Flags` int(11) NOT NULL DEFAULT '0',
  `VerifiedBuild` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`,`VerifiedBuild`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;


DROP TABLE IF EXISTS `trait_node`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `trait_node` (
  `ID` int(11) NOT NULL DEFAULT '0',
  `TraitTreeID` int(11) NOT NULL DEFAULT '0',
  `PosX` int(11) NOT NULL DEFAULT '0',
  `PosY` int(11) NOT NULL DEFAULT '0',
  `Type` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `Flags` int(11) NOT NULL DEFAULT '0',
  `VerifiedBuild` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`,`VerifiedBuild`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;


DROP TABLE IF EXISTS `trait_cond`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `trait_cond` (
  `ID` int(11) NOT NULL DEFAULT '0',
  `CondType` int(11) NOT NULL DEFAULT '0',
  `TraitTreeID` int(11) NOT NULL DEFAULT '0',
  `Field_10_0_0_44649_003` int(11) NOT NULL DEFAULT '0',
  `Field_10_0_0_44649_004` int(11) NOT NULL DEFAULT '0',
  `AchievementID` int(11) NOT NULL DEFAULT '0',
  `SpecSetID` int(11) NOT NULL DEFAULT '0',
  `TraitNodeGroupID` int(11) NOT NULL DEFAULT '0',
  `TraitNodeID` int(11) NOT NULL DEFAULT '0',
  `TraitCurrencyID` int(11) NOT NULL DEFAULT '0',
  `SpentAmountRequired` int(11) NOT NULL DEFAULT '0',
  `Flags` int(11) NOT NULL DEFAULT '0',
  `RequiredLevel` int(11) NOT NULL DEFAULT '0',
  `FreeSharedStringID` int(11) NOT NULL DEFAULT '0',
  `SpendMoreSharedStringID` int(11) NOT NULL DEFAULT '0',
  `VerifiedBuild` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`,`VerifiedBuild`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;
