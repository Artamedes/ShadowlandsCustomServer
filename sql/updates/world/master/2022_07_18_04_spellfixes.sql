
-- Dumping structure for table world.z_spell_fixes
CREATE TABLE IF NOT EXISTS `z_spell_fixes` (
  `SpellID` int(10) unsigned NOT NULL,
  `EffectIndex` int(10) unsigned NOT NULL,
  `BonusCoefficient` float unsigned NOT NULL DEFAULT '0',
  `BonusCoefficientFromAP` float unsigned NOT NULL DEFAULT '0',
  `PvpMultiplierMod` float unsigned NOT NULL DEFAULT '0',
  `Comment` text COLLATE utf8mb4_unicode_ci,
  PRIMARY KEY (`SpellID`,`EffectIndex`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
