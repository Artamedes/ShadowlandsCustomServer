
DROP TABLE IF EXISTS `quest_v2`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `quest_v2` (
  `ID` int(10) unsigned NOT NULL DEFAULT '0',
  `UniqueBitFlag` smallint(5) unsigned NOT NULL DEFAULT '0',
  `Field_10_0_2_45779_001` int(10) unsigned NOT NULL DEFAULT '0',
  `VerifiedBuild` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`,`VerifiedBuild`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;


DROP TABLE IF EXISTS `spell_aura_restrictions`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `spell_aura_restrictions` (
  `ID` int(10) unsigned NOT NULL DEFAULT '0',
  `DifficultyID` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `CasterAuraState` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `TargetAuraState` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `ExcludeCasterAuraState` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `ExcludeTargetAuraState` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `CasterAuraSpell` int(11) NOT NULL DEFAULT '0',
  `TargetAuraSpell` int(11) NOT NULL DEFAULT '0',
  `ExcludeCasterAuraSpell` int(11) NOT NULL DEFAULT '0',
  `ExcludeTargetAuraSpell` int(11) NOT NULL DEFAULT '0',
  `Field_10_0_2_45779_009` int(10) unsigned NOT NULL DEFAULT '0',
  `Field_10_0_2_45779_010` int(10) unsigned NOT NULL DEFAULT '0',
  `Field_10_0_2_45779_011` int(10) unsigned NOT NULL DEFAULT '0',
  `Field_10_0_2_45779_012` int(10) unsigned NOT NULL DEFAULT '0',
  `SpellID` int(10) unsigned NOT NULL DEFAULT '0',
  `VerifiedBuild` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`,`VerifiedBuild`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;



DROP TABLE IF EXISTS `sound_kit`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `sound_kit` (
  `ID` int(10) unsigned NOT NULL DEFAULT '0',
  `SoundType` int(11) NOT NULL DEFAULT '0',
  `VolumeFloat` float NOT NULL DEFAULT '0',
  `Flags` smallint(5) unsigned NOT NULL DEFAULT '0',
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
  `Field_10_0_2_45779_015` int(10) unsigned NOT NULL DEFAULT '0',
  `VerifiedBuild` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`,`VerifiedBuild`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;
