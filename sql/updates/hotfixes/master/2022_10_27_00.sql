
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




DROP TABLE IF EXISTS `battle_pet_species`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `battle_pet_species` (
  `Description` text,
  `SourceText` text,
  `ID` int(10) unsigned NOT NULL DEFAULT '0',
  `CreatureID` int(11) NOT NULL DEFAULT '0',
  `SummonSpellID` int(11) NOT NULL DEFAULT '0',
  `IconFileDataID` int(11) NOT NULL DEFAULT '0',
  `PetTypeEnum` tinyint(4) NOT NULL DEFAULT '0',
  `Flags` int(11) NOT NULL DEFAULT '0',
  `SourceTypeEnum` tinyint(4) NOT NULL DEFAULT '0',
  `CardUIModelSceneID` int(11) NOT NULL DEFAULT '0',
  `LoadoutUIModelSceneID` int(11) NOT NULL DEFAULT '0',
  `CovenantID` int(11) NOT NULL DEFAULT '0',
  `VerifiedBuild` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`,`VerifiedBuild`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `battle_pet_species`
--

LOCK TABLES `battle_pet_species` WRITE;
/*!40000 ALTER TABLE `battle_pet_species` DISABLE KEYS */;
/*!40000 ALTER TABLE `battle_pet_species` ENABLE KEYS */;
UNLOCK TABLES;
