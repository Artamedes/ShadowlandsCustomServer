
SET @CGUID := 179410 ;
SET @OGUID := 167907 ;

DELETE FROM `creature_equip_template` WHERE (`ID`=1 AND `CreatureID` IN (187290,191126,187072,187060,192284,187058,185489,193304,197211,189814,189812,189815,187394,197732,190269,193791,193790,191891,187406,191016,190151,190093,195672));
INSERT INTO `creature_equip_template` (`CreatureID`, `ID`, `ItemID1`, `AppearanceModID1`, `ItemVisual1`, `ItemID2`, `AppearanceModID2`, `ItemVisual2`, `ItemID3`, `AppearanceModID3`, `ItemVisual3`, `VerifiedBuild`) VALUES
(187290, 1, 189547, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Alexstrasza the Life-Binder
(191126, 1, 192518, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Ruby Shrineguard
(187072, 1, 192518, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Ruby Shrineguard
(187060, 1, 192513, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Ruby Keeper
(192284, 1, 13723, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Kandrostrasz
(187058, 1, 94827, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Ruby Scaleguard
(185489, 1, 166996, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- King Drippy
(193304, 1, 89897, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Ru'kroszk
(197211, 1, 0, 0, 0, 0, 0, 0, 156850, 0, 0, 45505), -- Murghurgl the Invader
(189814, 1, 166997, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Cliffdrip Wavemender
(189812, 1, 0, 0, 0, 0, 0, 0, 156850, 0, 0, 45505), -- Cliffdrip Snapstrider
(189815, 1, 166995, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Cliffdrip Fallstriker
(187394, 1, 89897, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Scoutstrasza
(197732, 1, 192518, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Ruby Warden
(190269, 1, 191706, 0, 0, 193841, 0, 0, 0, 0, 0, 45505), -- Sendrax
(193791, 1, 191742, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Sundered Mercenary
(193790, 1, 191742, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Sundered Supplyhand
(191891, 1, 191706, 0, 0, 193841, 0, 0, 0, 0, 0, 45505), -- Sendrax
(187406, 1, 191706, 0, 0, 193841, 0, 0, 0, 0, 0, 45505), -- Sendrax
(191016, 1, 192155, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Uktulut Protector
(190151, 1, 113440, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Ruby Culler
(190093, 1, 113440, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Ruby Culler
(195672, 1, 192120, 0, 0, 0, 0, 0, 0, 0, 0, 45505); -- Qalashi Scoundrel


DELETE FROM `areatrigger_template` WHERE (`IsServerSide`=0 AND `Id` IN (28368,29681,30143,28875));
INSERT INTO `areatrigger_template` (`Id`, `IsServerSide`, `Type`, `Flags`, `Data0`, `Data1`, `Data2`, `Data3`, `Data4`, `Data5`, `Data6`, `Data7`, `VerifiedBuild`) VALUES
(28368, 0, 4, 2052, 1, 1, 2, 2, -0.5, -0.5, 0, 0, 45505),
(29681, 0, 0, 4, 8, 8, 0, 0, 0, 0, 0, 0, 45505),
(30143, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 45505),
(28875, 0, 0, 0, 20, 20, 0, 0, 0, 0, 0, 0, 45505);

UPDATE `areatrigger_template` SET `Data1`=5, `Data4`=5 WHERE (`Id`=24192 AND `IsServerSide`=0);
UPDATE `areatrigger_template` SET `Data1`=5, `Data4`=5 WHERE (`Id`=24192 AND `IsServerSide`=0);
UPDATE `areatrigger_template` SET `Flags`=1048, `Data0`=0, `Data1`=0, `VerifiedBuild`=45505 WHERE (`Id`=6095 AND `IsServerSide`=0);
UPDATE `areatrigger_template` SET `Flags`=1048, `Data0`=0, `Data1`=0, `VerifiedBuild`=45505 WHERE (`Id`=6095 AND `IsServerSide`=0);
UPDATE `areatrigger_template` SET `Flags`=1040, `Data0`=0, `Data1`=0, `VerifiedBuild`=45505 WHERE (`Id`=26240 AND `IsServerSide`=0);
UPDATE `areatrigger_template` SET `Flags`=1040, `Data0`=0, `Data1`=0, `VerifiedBuild`=45505 WHERE (`Id`=26240 AND `IsServerSide`=0);
UPDATE `areatrigger_template` SET `Flags`=1048, `Data0`=0, `Data1`=0, `VerifiedBuild`=45505 WHERE (`Id`=6095 AND `IsServerSide`=0);
UPDATE `areatrigger_template` SET `Flags`=1048, `Data0`=0, `Data1`=0, `VerifiedBuild`=45505 WHERE (`Id`=6095 AND `IsServerSide`=0);
UPDATE `areatrigger_template` SET `Data0`=40, `Data1`=40, `VerifiedBuild`=45505 WHERE (`Id`=11513 AND `IsServerSide`=0);
UPDATE `areatrigger_template` SET `VerifiedBuild`=45505 WHERE (`IsServerSide`=0 AND `Id` IN (10714,3282,3983,7020,26236));
UPDATE `areatrigger_template` SET `Flags`=1048, `Data0`=0, `Data1`=0, `VerifiedBuild`=45505 WHERE (`Id`=6095 AND `IsServerSide`=0);
UPDATE `areatrigger_template` SET `Data0`=40, `Data1`=40, `VerifiedBuild`=45505 WHERE (`Id`=11513 AND `IsServerSide`=0);
UPDATE `areatrigger_template` SET `Data0`=40, `Data1`=40, `VerifiedBuild`=45505 WHERE (`Id`=11513 AND `IsServerSide`=0);
UPDATE `areatrigger_template` SET `Data0`=40, `Data1`=40, `VerifiedBuild`=45505 WHERE (`Id`=11513 AND `IsServerSide`=0);
UPDATE `areatrigger_template` SET `Flags`=1048, `Data0`=0, `Data1`=0, `VerifiedBuild`=45505 WHERE (`Id`=6095 AND `IsServerSide`=0);
UPDATE `areatrigger_template` SET `Flags`=0 WHERE (`Id`=9228 AND `IsServerSide`=0);
UPDATE `areatrigger_template` SET `Data0`=40, `Data1`=40, `VerifiedBuild`=45505 WHERE (`Id`=11513 AND `IsServerSide`=0);
UPDATE `areatrigger_template` SET `Flags`=1048, `Data0`=0, `Data1`=0, `VerifiedBuild`=45505 WHERE (`Id`=6095 AND `IsServerSide`=0);
UPDATE `areatrigger_template` SET `Type`=0 WHERE (`Id`=28313 AND `IsServerSide`=0);
UPDATE `areatrigger_template` SET `Data0`=0, `Data1`=0 WHERE (`Id`=28313 AND `IsServerSide`=0);
UPDATE `areatrigger_template` SET `Data0`=0, `Data1`=0 WHERE (`Id`=28313 AND `IsServerSide`=0);
UPDATE `areatrigger_template` SET `Flags`=1040, `Data0`=0, `Data1`=0, `VerifiedBuild`=45505 WHERE (`Id`=26240 AND `IsServerSide`=0);
UPDATE `areatrigger_template` SET `Flags`=1048, `Data0`=0, `Data1`=0, `VerifiedBuild`=45505 WHERE (`Id`=6095 AND `IsServerSide`=0);
UPDATE `areatrigger_template` SET `Flags`=1040, `Data0`=0, `Data1`=0, `VerifiedBuild`=45505 WHERE (`Id`=26240 AND `IsServerSide`=0);
UPDATE `areatrigger_template` SET `Flags`=1040, `Data0`=0, `Data1`=0, `VerifiedBuild`=45505 WHERE (`Id`=26240 AND `IsServerSide`=0);
UPDATE `areatrigger_template` SET `Flags`=1048, `Data0`=0, `Data1`=0, `VerifiedBuild`=45505 WHERE (`Id`=6095 AND `IsServerSide`=0);
UPDATE `areatrigger_template` SET `Flags`=1048, `Data0`=0, `Data1`=0, `VerifiedBuild`=45505 WHERE (`Id`=6095 AND `IsServerSide`=0);
UPDATE `areatrigger_template` SET `Flags`=1048, `Data0`=0, `Data1`=0, `VerifiedBuild`=45505 WHERE (`Id`=6095 AND `IsServerSide`=0);
UPDATE `areatrigger_template` SET `Data1`=5, `Data4`=5 WHERE (`Id`=24192 AND `IsServerSide`=0);
UPDATE `areatrigger_template` SET `Data1`=5, `Data4`=5 WHERE (`Id`=24192 AND `IsServerSide`=0);
UPDATE `areatrigger_template` SET `Data1`=5, `Data4`=5 WHERE (`Id`=24192 AND `IsServerSide`=0);
UPDATE `areatrigger_template` SET `Data1`=5, `Data4`=5 WHERE (`Id`=24192 AND `IsServerSide`=0);
UPDATE `areatrigger_template` SET `Flags`=1040, `Data0`=0, `Data1`=0, `VerifiedBuild`=45505 WHERE (`Id`=26240 AND `IsServerSide`=0);
UPDATE `areatrigger_template` SET `Flags`=1048, `Data0`=0, `Data1`=0, `VerifiedBuild`=45505 WHERE (`Id`=6095 AND `IsServerSide`=0);
UPDATE `areatrigger_template` SET `Flags`=1048, `Data0`=0, `Data1`=0, `VerifiedBuild`=45505 WHERE (`Id`=9110 AND `IsServerSide`=0);
UPDATE `areatrigger_template` SET `Flags`=1048, `Data0`=0, `Data1`=0, `VerifiedBuild`=45505 WHERE (`Id`=9110 AND `IsServerSide`=0);
UPDATE `areatrigger_template` SET `Flags`=1048, `Data0`=0, `Data1`=0, `VerifiedBuild`=45505 WHERE (`Id`=9110 AND `IsServerSide`=0);
UPDATE `areatrigger_template` SET `Data1`=5, `Data4`=5 WHERE (`Id`=24192 AND `IsServerSide`=0);
UPDATE `areatrigger_template` SET `Data1`=5, `Data4`=5 WHERE (`Id`=24192 AND `IsServerSide`=0);
UPDATE `areatrigger_template` SET `Data1`=5, `Data4`=5 WHERE (`Id`=24192 AND `IsServerSide`=0);

DELETE FROM `areatrigger_create_properties` WHERE `Id` IN (2147871843 /*SpellId : 388195 CANNOT FIND PROPERTIES ID, USED SPELL ID AS KEY (NEEDS MANUAL CORRECTION)*/, 2147871853 /*SpellId : 388205 CANNOT FIND PROPERTIES ID, USED SPELL ID AS KEY (NEEDS MANUAL CORRECTION)*/, 2147839561 /*SpellId : 355913 CANNOT FIND PROPERTIES ID, USED SPELL ID AS KEY (NEEDS MANUAL CORRECTION)*/, 4202938181 /*SpellId : 4202938181 CANNOT FIND PROPERTIES ID, USED SPELL ID AS KEY (NEEDS MANUAL CORRECTION)*/, 3273613312 /*SpellId : 1126129664 CANNOT FIND PROPERTIES ID, USED SPELL ID AS KEY (NEEDS MANUAL CORRECTION)*/, 3796205263 /*SpellId : 3796205263 CANNOT FIND PROPERTIES ID, USED SPELL ID AS KEY (NEEDS MANUAL CORRECTION)*/, 2147687443 /*SpellId : 203795 CANNOT FIND PROPERTIES ID, USED SPELL ID AS KEY (NEEDS MANUAL CORRECTION)*/, 3557049726 /*SpellId : 3557049726 CANNOT FIND PROPERTIES ID, USED SPELL ID AS KEY (NEEDS MANUAL CORRECTION)*/, 2147687903 /*SpellId : 204255 CANNOT FIND PROPERTIES ID, USED SPELL ID AS KEY (NEEDS MANUAL CORRECTION)*/, 2787274821 /*SpellId : 639791173 CANNOT FIND PROPERTIES ID, USED SPELL ID AS KEY (NEEDS MANUAL CORRECTION)*/, 2147873811 /*SpellId : 390163 CANNOT FIND PROPERTIES ID, USED SPELL ID AS KEY (NEEDS MANUAL CORRECTION)*/, 2147853684 /*SpellId : 370036 CANNOT FIND PROPERTIES ID, USED SPELL ID AS KEY (NEEDS MANUAL CORRECTION)*/, 2147873362 /*SpellId : 389714 CANNOT FIND PROPERTIES ID, USED SPELL ID AS KEY (NEEDS MANUAL CORRECTION)*/, 2147685785 /*SpellId : 202137 CANNOT FIND PROPERTIES ID, USED SPELL ID AS KEY (NEEDS MANUAL CORRECTION)*/, 2147600680 /*SpellId : 117032 CANNOT FIND PROPERTIES ID, USED SPELL ID AS KEY (NEEDS MANUAL CORRECTION)*/, 2916304260 /*SpellId : 2916304260 CANNOT FIND PROPERTIES ID, USED SPELL ID AS KEY (NEEDS MANUAL CORRECTION)*/, 2147510221 /*SpellId : 26573 CANNOT FIND PROPERTIES ID, USED SPELL ID AS KEY (NEEDS MANUAL CORRECTION)*/, 2147839584 /*SpellId : 355936 CANNOT FIND PROPERTIES ID, USED SPELL ID AS KEY (NEEDS MANUAL CORRECTION)*/, 2147839337 /*SpellId : 355689 CANNOT FIND PROPERTIES ID, USED SPELL ID AS KEY (NEEDS MANUAL CORRECTION)*/, 2147866132 /*SpellId : 382484 CANNOT FIND PROPERTIES ID, USED SPELL ID AS KEY (NEEDS MANUAL CORRECTION)*/, 2147608151 /*SpellId : 124503 CANNOT FIND PROPERTIES ID, USED SPELL ID AS KEY (NEEDS MANUAL CORRECTION)*/, 2147853020 /*SpellId : 369372 CANNOT FIND PROPERTIES ID, USED SPELL ID AS KEY (NEEDS MANUAL CORRECTION)*/, 2147871847 /*SpellId : 388199 CANNOT FIND PROPERTIES ID, USED SPELL ID AS KEY (NEEDS MANUAL CORRECTION)*/, 3895673283 /*SpellId : 1748189635 CANNOT FIND PROPERTIES ID, USED SPELL ID AS KEY (NEEDS MANUAL CORRECTION)*/, 4165296101 /*SpellId : 4165296101 CANNOT FIND PROPERTIES ID, USED SPELL ID AS KEY (NEEDS MANUAL CORRECTION)*/, 2147713789 /*SpellId : 230141 CANNOT FIND PROPERTIES ID, USED SPELL ID AS KEY (NEEDS MANUAL CORRECTION)*/, 2147853860 /*SpellId : 370212 CANNOT FIND PROPERTIES ID, USED SPELL ID AS KEY (NEEDS MANUAL CORRECTION)*/, 2147849103 /*SpellId : 365455 CANNOT FIND PROPERTIES ID, USED SPELL ID AS KEY (NEEDS MANUAL CORRECTION)*/, 2147600492 /*SpellId : 116844 CANNOT FIND PROPERTIES ID, USED SPELL ID AS KEY (NEEDS MANUAL CORRECTION)*/, 3289121013 /*SpellId : 3289121013 CANNOT FIND PROPERTIES ID, USED SPELL ID AS KEY (NEEDS MANUAL CORRECTION)*/, 2147646919 /*SpellId : 163271 CANNOT FIND PROPERTIES ID, USED SPELL ID AS KEY (NEEDS MANUAL CORRECTION)*/, 2147874064 /*SpellId : 390416 CANNOT FIND PROPERTIES ID, USED SPELL ID AS KEY (NEEDS MANUAL CORRECTION)*/, 2147829182 /*SpellId : 345534 CANNOT FIND PROPERTIES ID, USED SPELL ID AS KEY (NEEDS MANUAL CORRECTION)*/);
INSERT INTO `areatrigger_create_properties` (`Id`, `AreaTriggerId`, `MoveCurveId`, `ScaleCurveId`, `MorphCurveId`, `FacingCurveId`, `AnimId`, `AnimKitId`, `DecalPropertiesId`, `TimeToTarget`, `TimeToTargetScale`, `Shape`, `ShapeData0`, `ShapeData1`, `ShapeData2`, `ShapeData3`, `ShapeData4`, `ShapeData5`, `ShapeData6`, `ShapeData7`, `VerifiedBuild`) VALUES
(2147871843, 24192, 0, 0, 0, 0, -1, 0, 0, 30000, 0, 1, 5, 4, 2.5, 5, 4, 2.5, 0, 0, 45505), -- SpellId : 388195 CANNOT FIND PROPERTIES ID, USED SPELL ID AS KEY (NEEDS MANUAL CORRECTION)
(2147871853, 24192, 0, 0, 0, 0, -1, 0, 0, 30000, 0, 1, 5, 5, 2.5, 5, 5, 2.5, 0, 0, 45505), -- SpellId : 388205 CANNOT FIND PROPERTIES ID, USED SPELL ID AS KEY (NEEDS MANUAL CORRECTION)
(2147839561, 27633, 0, 0, 0, 0, -1, 0, 0, 2000, 0, 0, 3, 3, 0, 0, 0, 0, 0, 0, 45505), -- SpellId : 355913 CANNOT FIND PROPERTIES ID, USED SPELL ID AS KEY (NEEDS MANUAL CORRECTION)
(4202938181, 6095, 0, 0, 0, 0, 163842063, 106233856, 2148267586, 4275250245, 327336002, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- SpellId : 4202938181 CANNOT FIND PROPERTIES ID, USED SPELL ID AS KEY (NEEDS MANUAL CORRECTION)
(3273613312, 6095, 0, 0, 0, 0, -1, 0, 1165846379, 1126178902, 1108842355, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- SpellId : 1126129664 CANNOT FIND PROPERTIES ID, USED SPELL ID AS KEY (NEEDS MANUAL CORRECTION)
(3796205263, 26240, 0, 0, 0, 0, -503355648, 1025383533, 3829539475, 2068152003, 3460502843, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- SpellId : 3796205263 CANNOT FIND PROPERTIES ID, USED SPELL ID AS KEY (NEEDS MANUAL CORRECTION)
(2147687443, 11266, 0, 0, 0, 0, -1, 0, 0, 20000, 0, 0, 4, 6, 0, 0, 0, 0, 0, 0, 45505), -- SpellId : 203795 CANNOT FIND PROPERTIES ID, USED SPELL ID AS KEY (NEEDS MANUAL CORRECTION)
(3557049726, 26240, 0, 0, 0, 0, -1, 0, 1570980385, 2234271102, 119489320, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- SpellId : 3557049726 CANNOT FIND PROPERTIES ID, USED SPELL ID AS KEY (NEEDS MANUAL CORRECTION)
(2147687903, 10665, 0, 0, 0, 0, -1, 0, 0, 20000, 0, 0, 4, 4, 0, 0, 0, 0, 0, 0, 45505), -- SpellId : 204255 CANNOT FIND PROPERTIES ID, USED SPELL ID AS KEY (NEEDS MANUAL CORRECTION)
(2787274821, 6095, 0, 0, 0, 0, -1, 0, 2099712322, 643640901, 388354883, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- SpellId : 639791173 CANNOT FIND PROPERTIES ID, USED SPELL ID AS KEY (NEEDS MANUAL CORRECTION)
(2147873811, 30889, 0, 0, 0, 0, -1, 0, 0, 1000, 0, 0, 8, 8, 0, 0, 0, 0, 0, 0, 45505), -- SpellId : 390163 CANNOT FIND PROPERTIES ID, USED SPELL ID AS KEY (NEEDS MANUAL CORRECTION)
(2147853684, 28857, 0, 33076, 0, 0, -1, 0, 492, 10000, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 45505), -- SpellId : 370036 CANNOT FIND PROPERTIES ID, USED SPELL ID AS KEY (NEEDS MANUAL CORRECTION)
(2147873362, 11513, 0, 0, 0, 0, -1, 0, 0, 8000, 0, 0, 40, 40, 0, 0, 0, 0, 0, 0, 45505), -- SpellId : 389714 CANNOT FIND PROPERTIES ID, USED SPELL ID AS KEY (NEEDS MANUAL CORRECTION)
(2147685785, 10714, 0, 0, 0, 0, -1, 0, 0, 2000, 0, 0, 8, 8, 0, 0, 0, 0, 0, 0, 45505), -- SpellId : 202137 CANNOT FIND PROPERTIES ID, USED SPELL ID AS KEY (NEEDS MANUAL CORRECTION)
(2147600680, 3319, 0, 0, 0, 0, -1, 0, 0, 30000, 0, 0, 3, 3, 0, 0, 0, 0, 0, 0, 45505), -- SpellId : 117032 CANNOT FIND PROPERTIES ID, USED SPELL ID AS KEY (NEEDS MANUAL CORRECTION)
(2916304260, 6095, 0, 0, 0, 0, -1, 0, 1811956308, 3142534532, 2935440142, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- SpellId : 2916304260 CANNOT FIND PROPERTIES ID, USED SPELL ID AS KEY (NEEDS MANUAL CORRECTION)
(2147510221, 9228, 0, 0, 0, 0, -1, 0, 0, 12000, 0, 0, 8, 8, 0, 0, 0, 0, 0, 0, 45505), -- SpellId : 26573 CANNOT FIND PROPERTIES ID, USED SPELL ID AS KEY (NEEDS MANUAL CORRECTION)
(2147839584, 28313, 0, 0, 0, 0, -1, 0, 0, 3123, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- SpellId : 355936 CANNOT FIND PROPERTIES ID, USED SPELL ID AS KEY (NEEDS MANUAL CORRECTION)
(2147839337, 29625, 0, 0, 0, 0, -1, 0, 0, 8000, 0, 0, 3, 3, 0, 0, 0, 0, 0, 0, 45505), -- SpellId : 355689 CANNOT FIND PROPERTIES ID, USED SPELL ID AS KEY (NEEDS MANUAL CORRECTION)
(2147866132, 9228, 0, 0, 0, 0, -1, 0, 0, 12000, 0, 0, 8, 8, 0, 0, 0, 0, 0, 0, 45505), -- SpellId : 382484 CANNOT FIND PROPERTIES ID, USED SPELL ID AS KEY (NEEDS MANUAL CORRECTION)
(2147608151, 3282, 0, 0, 0, 0, -1, 0, 0, 30000, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 45505), -- SpellId : 124503 CANNOT FIND PROPERTIES ID, USED SPELL ID AS KEY (NEEDS MANUAL CORRECTION)
(2147853020, 28714, 0, 0, 0, 0, -1, 0, 0, 12000, 0, 0, 8, 8, 0, 0, 0, 0, 0, 0, 45505), -- SpellId : 369372 CANNOT FIND PROPERTIES ID, USED SPELL ID AS KEY (NEEDS MANUAL CORRECTION)
(2147871847, 24192, 0, 0, 0, 0, -1, 0, 0, 30000, 0, 1, 5, 5, 2.5, 5, 5, 2.5, 0, 0, 45505), -- SpellId : 388199 CANNOT FIND PROPERTIES ID, USED SPELL ID AS KEY (NEEDS MANUAL CORRECTION)
(3895673283, 6700, 0, 0, 0, 0, 385876400, 168, 21251431, 842678711, 2261008945, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- SpellId : 1748189635 CANNOT FIND PROPERTIES ID, USED SPELL ID AS KEY (NEEDS MANUAL CORRECTION)
(4165296101, 6095, 0, 0, 0, 0, -1670718465, -2093146595, 3091340076, 3561316297, 1623346139, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- SpellId : 4165296101 CANNOT FIND PROPERTIES ID, USED SPELL ID AS KEY (NEEDS MANUAL CORRECTION)
(2147713789, 13112, 0, 0, 0, 0, -1, 0, 0, 30000, 0, 0, 4, 4, 0, 0, 0, 0, 0, 0, 45505), -- SpellId : 230141 CANNOT FIND PROPERTIES ID, USED SPELL ID AS KEY (NEEDS MANUAL CORRECTION)
(2147853860, 28875, 0, 0, 0, 0, -1, 0, 0, 6000, 0, 0, 20, 20, 0, 0, 0, 0, 0, 0, 45505), -- SpellId : 370212 CANNOT FIND PROPERTIES ID, USED SPELL ID AS KEY (NEEDS MANUAL CORRECTION)
(2147849103, 28443, 0, 0, 0, 0, -1, 0, 0, 15000, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 45505), -- SpellId : 365455 CANNOT FIND PROPERTIES ID, USED SPELL ID AS KEY (NEEDS MANUAL CORRECTION)
(2147600492, 3983, 0, 0, 0, 0, -1, 0, 0, 5000, 0, 0, 8, 8, 0, 0, 0, 0, 0, 0, 45505), -- SpellId : 116844 CANNOT FIND PROPERTIES ID, USED SPELL ID AS KEY (NEEDS MANUAL CORRECTION)
(3289121013, 9110, 0, 0, 0, 0, -1, 0, 1163321335, 3289139825, 1116637437, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- SpellId : 3289121013 CANNOT FIND PROPERTIES ID, USED SPELL ID AS KEY (NEEDS MANUAL CORRECTION)
(2147646919, 7020, 0, 0, 0, 0, -1, 0, 0, 120000, 0, 0, 3, 3, 0, 0, 0, 0, 0, 0, 45505), -- SpellId : 163271 CANNOT FIND PROPERTIES ID, USED SPELL ID AS KEY (NEEDS MANUAL CORRECTION)
(2147874064, 30903, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 5, 5, 0, 0, 0, 0, 0, 0, 45505), -- SpellId : 390416 CANNOT FIND PROPERTIES ID, USED SPELL ID AS KEY (NEEDS MANUAL CORRECTION)
(2147829182, 26236, 0, 0, 0, 0, -1, 0, 0, 8000, 0, 0, 5, 5, 0, 0, 0, 0, 0, 0, 45505), -- SpellId : 345534 CANNOT FIND PROPERTIES ID; USED SPELL ID AS KEY (NEEDS MANUAL CORRECTION)

UPDATE `areatrigger_create_properties` SET `AreaTriggerId`=29681, `ShapeData0`=8, `ShapeData1`=8, `VerifiedBuild`=45505 WHERE `Id`=2147483648; -- SpellId : 0 CANNOT FIND PROPERTIES ID, USED SPELL ID AS KEY (NEEDS MANUAL CORRECTION)
UPDATE `areatrigger_create_properties` SET `AreaTriggerId`=29681, `ShapeData0`=8, `ShapeData1`=8, `VerifiedBuild`=45505 WHERE `Id`=2147483648; -- SpellId : 0 CANNOT FIND PROPERTIES ID, USED SPELL ID AS KEY (NEEDS MANUAL CORRECTION)
UPDATE `areatrigger_create_properties` SET `AreaTriggerId`=29681, `ShapeData0`=8, `ShapeData1`=8, `VerifiedBuild`=45505 WHERE `Id`=2147483648; -- SpellId : 0 CANNOT FIND PROPERTIES ID, USED SPELL ID AS KEY (NEEDS MANUAL CORRECTION)
UPDATE `areatrigger_create_properties` SET `AreaTriggerId`=29681, `ShapeData0`=8, `ShapeData1`=8, `VerifiedBuild`=45505 WHERE `Id`=2147483648; -- SpellId : 0 CANNOT FIND PROPERTIES ID, USED SPELL ID AS KEY (NEEDS MANUAL CORRECTION)
UPDATE `areatrigger_create_properties` SET `AreaTriggerId`=29681, `ShapeData0`=8, `ShapeData1`=8, `VerifiedBuild`=45505 WHERE `Id`=2147483648; -- SpellId : 0 CANNOT FIND PROPERTIES ID, USED SPELL ID AS KEY (NEEDS MANUAL CORRECTION)

DELETE FROM `areatrigger_create_properties_polygon_vertex` WHERE (`AreaTriggerCreatePropertiesId`=2147839584 AND `Idx` IN (3,2,1,0));
INSERT INTO `areatrigger_create_properties_polygon_vertex` (`AreaTriggerCreatePropertiesId`, `Idx`, `VerticeX`, `VerticeY`, `VerticeTargetX`, `VerticeTargetY`, `VerifiedBuild`) VALUES
(2147839584, 3, 25, 25, NULL, NULL, 45505), -- SpellId : 355936 CANNOT FIND PROPERTIES ID, USED SPELL ID AS KEY (NEEDS MANUAL CORRECTION)
(2147839584, 2, 25, -25, NULL, NULL, 45505), -- SpellId : 355936 CANNOT FIND PROPERTIES ID, USED SPELL ID AS KEY (NEEDS MANUAL CORRECTION)
(2147839584, 1, 0, -1, NULL, NULL, 45505), -- SpellId : 355936 CANNOT FIND PROPERTIES ID, USED SPELL ID AS KEY (NEEDS MANUAL CORRECTION)
(2147839584, 0, 0, 1, NULL, NULL, 45505), -- SpellId : 355936 CANNOT FIND PROPERTIES ID; USED SPELL ID AS KEY (NEEDS MANUAL CORRECTION)


DELETE FROM `conversation_actors` WHERE (`Idx`=0 AND `ConversationId` IN (18461,18464,18808,18460,18813,18429,18812,19312,19323,18806,19244,18726,19240,18419,18455,18695,18811,18454,18456,18807,19207,18724,18810,18463,18876,19238,18809,18459,19206)) OR (`Idx`=1 AND `ConversationId` IN (18464,18813,18429,18726,18695,18724,18876)) OR (`Idx`=2 AND `ConversationId` IN (18726,18724));
INSERT INTO `conversation_actors` (`ConversationId`, `ConversationActorId`, `Idx`, `CreatureId`, `CreatureDisplayInfoId`, `NoActorObject`, `ActivePlayerObject`, `VerifiedBuild`) VALUES
(18461, 85593, 0, UNKNOWN, UNKNOWN, 0, 0, 45505), -- Full: 0x2020913180B9B6C0003D1E00001C6BC5 Creature/0 R2084/S15646 Map: 2444 Entry: 190171 (Ruby Egg Guardian) Low: 1862597
(18464, 86398, 1, UNKNOWN, UNKNOWN, 0, 0, 45505), -- Full: 0x2420913180BB4600003D1E00001C6E4F Vehicle/0 R2084/S15646 Map: 2444 Entry: 191768 (Majordomo Selistra) Low: 1863247
(18464, 0, 0, UNKNOWN, UNKNOWN, 0, 1, 45505), -- Full: 0x0800040000000000FFFFFFFFFFFFFFFF Player/0 R1/S16777215 Map: 0 (Eastern Kingdoms) Low: 1099511627775
(18808, 85593, 0, UNKNOWN, UNKNOWN, 0, 0, 45505), -- Full: 0x2020913180B9B6C0003D1E00001C6CEE Creature/0 R2084/S15646 Map: 2444 Entry: 190171 (Ruby Egg Guardian) Low: 1862894
(18460, 85593, 0, UNKNOWN, UNKNOWN, 0, 0, 45505), -- Full: 0x2020913180B9B6C0003D1E00001C6BC5 Creature/0 R2084/S15646 Map: 2444 Entry: 190171 (Ruby Egg Guardian) Low: 1862597
(18813, 86462, 1, UNKNOWN, UNKNOWN, 0, 0, 45505), -- Full: 0x2020913180B6E680003D1E00001C5920 Creature/0 R2084/S15646 Map: 2444 Entry: 187290 (Alexstrasza the Life-Binder) Low: 1857824
(18813, 86464, 0, UNKNOWN, UNKNOWN, 0, 0, 45505), -- Full: 0x0
(18429, 0, 1, UNKNOWN, UNKNOWN, 0, 0, 45505), -- Full: 0x2020913180B66AC0003D1E00001C6E2B Creature/0 R2084/S15646 Map: 2444 Entry: 186795 (Majordomo Selistra) Low: 1863211
(18429, 86469, 0, UNKNOWN, UNKNOWN, 0, 0, 45505), -- Full: 0x2020913180B9B2C0003D1E00001C6E2B Creature/0 R2084/S15646 Map: 2444 Entry: 190155 (Caretaker Azkra) Low: 1863211
(18812, 86461, 0, UNKNOWN, UNKNOWN, 0, 0, 45505), -- Full: 0x2020913180B58C00003D1E00001C5922 Creature/0 R2084/S15646 Map: 2444 Entry: 185904 (Mother Elion) Low: 1857826
(19312, 85584, 0, UNKNOWN, UNKNOWN, 0, 0, 45505), -- Full: 0x2020913180B9B2C0003D1E00001C591F Creature/0 R2084/S15646 Map: 2444 Entry: 190155 (Caretaker Azkra) Low: 1857823
(19323, 86335, 0, UNKNOWN, UNKNOWN, 0, 0, 45505), -- Full: 0x2020913180BA8C40003D1E00001C591F Creature/0 R2084/S15646 Map: 2444 Entry: 191025 (Lifecaller Tzadrak) Low: 1857823
(18806, 85593, 0, UNKNOWN, UNKNOWN, 0, 0, 45505), -- Full: 0x2020913180B9B6C0003D1E00001C6CEE Creature/0 R2084/S15646 Map: 2444 Entry: 190171 (Ruby Egg Guardian) Low: 1862894
(19244, 87267, 0, UNKNOWN, UNKNOWN, 0, 0, 45505), -- Full: 0x2020913180BD68C0003D1E00001C591F Creature/0 R2084/S15646 Map: 2444 Entry: 193955 (Lillistrazsa) Low: 1857823
(18726, 86334, 1, UNKNOWN, UNKNOWN, 0, 0, 45505), -- Full: 0x0
(18726, 86337, 2, UNKNOWN, UNKNOWN, 0, 0, 45505), -- Full: 0x0
(18726, 86335, 0, UNKNOWN, UNKNOWN, 0, 0, 45505), -- Full: 0x0
(19240, 87246, 0, UNKNOWN, UNKNOWN, 0, 0, 45505), -- Full: 0x2020913180BD7600003D1E00001C6EFA Creature/0 R2084/S15646 Map: 2444 Entry: 194008 (Lillistrazsa) Low: 1863418
(18419, 85591, 0, UNKNOWN, UNKNOWN, 0, 0, 45505), -- Full: 0x2020913180B70380003D1E00001C591F Creature/0 R2084/S15646 Map: 2444 Entry: 187406 (Sendrax) Low: 1857823
(18455, 86456, 0, UNKNOWN, UNKNOWN, 0, 0, 45505), -- Full: 0x2020913180BB64C0003D1E00001C6DE1 Creature/0 R2084/S15646 Map: 2444 Entry: 191891 (Sendrax) Low: 1863137
(18695, 86249, 1, UNKNOWN, UNKNOWN, 0, 0, 45505), -- Full: 0x2020913180B663C0003D1E00001C591F Creature/0 R2084/S15646 Map: 2444 Entry: 186767 (Majordomo Selistra) Low: 1857823
(18695, 86248, 0, UNKNOWN, UNKNOWN, 0, 0, 45505), -- Full: 0x2020913180BE3500003D1E00001C6AAA Creature/0 R2084/S15646 Map: 2444 Entry: 194772 (Wrathion) Low: 1862314
(18811, 86460, 0, UNKNOWN, UNKNOWN, 0, 0, 45505), -- Full: 0x2020913180B8D300003D1E00001C591F Creature/0 R2084/S15646 Map: 2444 Entry: 189260 (Zahkrana) Low: 1857823
(18454, 86456, 0, UNKNOWN, UNKNOWN, 0, 0, 45505), -- Full: 0x0
(18456, 86457, 0, UNKNOWN, UNKNOWN, 0, 0, 45505), -- Full: 0x2020913180BB64C0003D1E00001C6DF4 Creature/0 R2084/S15646 Map: 2444 Entry: 191891 (Sendrax) Low: 1863156
(18807, 86453, 0, UNKNOWN, UNKNOWN, 0, 0, 45505), -- Full: 0x2020913180B9CF40003D1E00001C6DCC Creature/0 R2084/S15646 Map: 2444 Entry: 190269 (Sendrax) Low: 1863116
(19207, 87703, 0, UNKNOWN, UNKNOWN, 0, 0, 45505), -- Full: 0x2020913180BDEB80003D1E00001C591F Creature/0 R2084/S15646 Map: 2444 Entry: 194478 (Clokkistrasz) Low: 1857823
(18724, 86332, 1, UNKNOWN, UNKNOWN, 0, 0, 45505), -- Full: 0x2020913180BA8900003D1E00001C6F70 Creature/0 R2084/S15646 Map: 2444 Entry: 191012 (Akora) Low: 1863536
(18724, 86336, 2, UNKNOWN, UNKNOWN, 0, 0, 45505), -- Full: 0x2020913180BA8940003D1E00001C591F Creature/0 R2084/S15646 Map: 2444 Entry: 191013 (Keshki) Low: 1857823
(18724, 86335, 0, UNKNOWN, UNKNOWN, 0, 0, 45505), -- Full: 0x2020913180BA8C40003D1E00001C591F Creature/0 R2084/S15646 Map: 2444 Entry: 191025 (Lifecaller Tzadrak) Low: 1857823
(18810, 86459, 0, UNKNOWN, UNKNOWN, 0, 0, 45505), -- Full: 0x2020913180B8D380003D1E00001C5921 Creature/0 R2084/S15646 Map: 2444 Entry: 189262 (Akxall) Low: 1857825
(18463, 85593, 0, UNKNOWN, UNKNOWN, 0, 0, 45505), -- Full: 0x2020913180B9B6C0003D1E00001C6BC5 Creature/0 R2084/S15646 Map: 2444 Entry: 190171 (Ruby Egg Guardian) Low: 1862597
(18876, 86468, 1, UNKNOWN, UNKNOWN, 0, 0, 45505), -- Full: 0x2020913180B7E240003D1E00001C591F Creature/0 R2084/S15646 Map: 2444 Entry: 188297 (Caretaker Ventraz) Low: 1857823
(18876, 85576, 0, UNKNOWN, UNKNOWN, 0, 0, 45505), -- Full: 0x2020913180B9A340003D1E00001C591F Creature/0 R2084/S15646 Map: 2444 Entry: 190093 (Ruby Culler) Low: 1857823
(19238, 87246, 0, UNKNOWN, UNKNOWN, 0, 0, 45505), -- Full: 0x2020913180BD7600003D1E00001C6EFA Creature/0 R2084/S15646 Map: 2444 Entry: 194008 (Lillistrazsa) Low: 1863418
(18809, 86458, 0, UNKNOWN, UNKNOWN, 0, 0, 45505), -- Full: 0x2020913180B8D340003D1E00001C591F Creature/0 R2084/S15646 Map: 2444 Entry: 189261 (Xius) Low: 1857823
(18459, 85593, 0, UNKNOWN, UNKNOWN, 0, 0, 45505), -- Full: 0x2020913180B9B6C0003D1E00001C6BC5 Creature/0 R2084/S15646 Map: 2444 Entry: 190171 (Ruby Egg Guardian) Low: 1862597
(19206, 88420, 0, UNKNOWN, UNKNOWN, 0, 0, 45505); -- Full: 0x2020913180BDEA80003D1E00001C591F Creature/0 R2084/S15646 Map: 2444 Entry: 194474 (Zhustostrasza) Low: 1857823


DELETE FROM `conversation_line_template` WHERE `Id` IN (47158, 47165, 47164, 47163, 47162, 47161, 47970, 47968, 48045, 47157, 48053, 48052, 48056, 47082, 48051, 49189, 49188, 49211, 48043, 49038, 49037, 47846, 47845, 47844, 51385, 49026, 47069, 47152, 47752, 47751, 47750, 47749, 48050, 47151, 47150, 47153, 48044, 48954, 47840, 47839, 47838, 50655, 48049, 47160, 48198, 48197, 49024, 48048, 47156, 48953);
INSERT INTO `conversation_line_template` (`Id`, `UiCameraID`, `ActorIdx`, `Flags`, `VerifiedBuild`) VALUES
(47158, 0, 0, 0, 45505),
(47165, 0, 1, 0, 45505),
(47164, 0, 1, 0, 45505),
(47163, 0, 1, 0, 45505),
(47162, 0, 1, 0, 45505),
(47161, 0, 1, 0, 45505),
(47970, 0, 1, 0, 45505),
(47968, 0, 0, 0, 45505),
(48045, 0, 0, 0, 45505),
(47157, 0, 0, 0, 45505),
(48053, 0, 1, 0, 45505),
(48052, 0, 0, 0, 45505),
(48056, 0, 1, 0, 45505),
(47082, 0, 0, 1, 45505),
(48051, 0, 0, 0, 45505),
(49189, 0, 0, 0, 45505),
(49188, 0, 0, 0, 45505),
(49211, 0, 0, 0, 45505),
(48043, 0, 0, 0, 45505),
(49038, 0, 0, 0, 45505),
(49037, 0, 0, 0, 45505),
(47846, 0, 1, 1, 45505),
(47845, 0, 2, 1, 45505),
(47844, 0, 1, 1, 45505),
(51385, 0, 0, 0, 45505),
(49026, 0, 0, 0, 45505),
(47069, 0, 0, 0, 45505),
(47152, 0, 0, 0, 45505),
(47752, 0, 1, 0, 45505),
(47751, 0, 0, 0, 45505),
(47750, 0, 1, 0, 45505),
(47749, 0, 0, 0, 45505),
(48050, 0, 0, 0, 45505),
(47151, 0, 0, 0, 45505),
(47150, 0, 0, 0, 45505),
(47153, 0, 0, 0, 45505),
(48044, 0, 0, 0, 45505),
(48954, 0, 0, 0, 45505),
(47840, 0, 1, 1, 45505),
(47839, 0, 2, 1, 45505),
(47838, 0, 1, 1, 45505),
(50655, 0, 0, 0, 45505),
(48049, 0, 0, 0, 45505),
(47160, 0, 0, 0, 45505),
(48198, 0, 1, 0, 45505),
(48197, 0, 0, 0, 45505),
(49024, 0, 0, 0, 45505),
(48048, 0, 0, 0, 45505),
(47156, 0, 0, 0, 45505),
(48953, 0, 0, 0, 45505);


DELETE FROM `conversation_template` WHERE `Id` IN (18724, 18811, 18812, 19240, 19206, 19207, 19238, 19244, 18810, 18809, 18726, 19323, 18813, 20007, 18464, 18429, 18808, 18456, 18454, 18455, 18807, 18806, 18461, 18463, 18460, 18459, 18419, 19312, 18876, 18695);
INSERT INTO `conversation_template` (`Id`, `FirstLineID`, `TextureKitId`, `VerifiedBuild`) VALUES
(18724, 50655, UNKNOWN, 45505),
(18811, 48050, UNKNOWN, 45505),
(18812, 48051, UNKNOWN, 45505),
(19240, 49026, UNKNOWN, 45505),
(19206, 48953, UNKNOWN, 45505),
(19207, 48954, UNKNOWN, 45505),
(19238, 49024, UNKNOWN, 45505),
(19244, 49037, UNKNOWN, 45505),
(18810, 48049, UNKNOWN, 45505),
(18809, 48048, UNKNOWN, 45505),
(18726, 51385, UNKNOWN, 45505),
(19323, 49211, UNKNOWN, 45505),
(18813, 48052, UNKNOWN, 45505),
(20007, UNKNOWN, UNKNOWN, 45505),
(18464, 47968, UNKNOWN, 45505),
(18429, 47082, UNKNOWN, 45505),
(18808, 48045, UNKNOWN, 45505),
(18456, 47153, UNKNOWN, 45505),
(18454, 47150, UNKNOWN, 45505),
(18455, 47152, UNKNOWN, 45505),
(18807, 48044, UNKNOWN, 45505),
(18806, 48043, UNKNOWN, 45505),
(18461, 47158, UNKNOWN, 45505),
(18463, 47160, UNKNOWN, 45505),
(18460, 47157, UNKNOWN, 45505),
(18459, 47156, UNKNOWN, 45505),
(18419, 47069, UNKNOWN, 45505),
(19312, 49188, UNKNOWN, 45505),
(18876, 48197, UNKNOWN, 45505),
(18695, 47749, UNKNOWN, 45505);


DELETE FROM `gameobject_template_addon` WHERE `entry` IN (377899 /*Hidden Hornswog Hostage*/, 379037 /*Soft Ruby Feather*/, 378849 /*Large Fish Sighting*/, 378850 /*Large Fish Sighting*/, 375105 /*Teleport Tether*/, 377298 /*Shimmery Jar of Fireflies*/, 377302 /*Gardener's Trusty Rake*/, 377301 /*Reinforced Hornstrider Lasso*/, 377300 /*Whelptender's Watering Can*/, 377266 /*Overgrown Weeds*/, 377265 /*Overgrown Weeds*/, 377231 /*Overgrown Weeds*/, 377230 /*Fallen Leaves*/, 379040 /*Glass Bead*/, 316739 /*Barrier (Wide)*/, 381341 /*Ancient Stone*/, 381617 /*Kolgar's Pack*/, 382069 /*Overripe Lifebinder's Gift*/, 382068 /*Barbed Tulip*/, 381396 /*Tuskarr Fishing Net*/, 375687 /*Water Keg*/, 376240 /*Climbing Gear*/, 375673 /*Climbing Gear*/, 381343 /*Ancient Stone*/, 376943 /*Dracuixote*/, 376944 /*The Lord of the Wings*/, 376946 /*Pride and Protodrakes*/, 380516 /*Glimmer of Wisdom*/, 380510 /*Dim Forge*/, 376199 /*Hatched Dragon Egg*/, 376945 /*The Red and the Black Flights*/, 376942 /*The Scales of Wrath*/, 376941 /*The Titanic Comedy*/, 381196 /*Titan-Touched Writhebark*/, 377499 /*On the Origin of Draconic Species*/, 379248 /*Draconium Deposit*/);
INSERT INTO `gameobject_template_addon` (`entry`, `faction`, `flags`, `WorldEffectID`, `AIAnimKitID`) VALUES
(377899, 0, 0, 2437, 0), -- Hidden Hornswog Hostage
(379037, 0, 2113540, 0, 0), -- Soft Ruby Feather
(378849, 0, 8192, 0, 0), -- Large Fish Sighting
(378850, 0, 8192, 0, 0), -- Large Fish Sighting
(375105, 190, 0, 0, 0), -- Teleport Tether
(377298, 0, 262149, 0, 0), -- Shimmery Jar of Fireflies
(377302, 0, 262148, 0, 0), -- Gardener's Trusty Rake
(377301, 0, 262148, 0, 0), -- Reinforced Hornstrider Lasso
(377300, 0, 262148, 0, 0), -- Whelptender's Watering Can
(377266, 0, 262144, 0, 0), -- Overgrown Weeds
(377265, 0, 262144, 0, 0), -- Overgrown Weeds
(377231, 0, 262144, 0, 0), -- Overgrown Weeds
(377230, 0, 262144, 0, 0), -- Fallen Leaves
(379040, 0, 2113540, 0, 0), -- Glass Bead
(316739, 0, 32, 0, 0), -- Barrier (Wide)
(381341, 0, 270336, 0, 0), -- Ancient Stone
(381617, 0, 2113540, 0, 0), -- Kolgar's Pack
(382069, 0, 278528, 20518, 0), -- Overripe Lifebinder's Gift
(382068, 0, 278528, 20518, 0), -- Barbed Tulip
(381396, 0, 8454144, 0, 0), -- Tuskarr Fishing Net
(375687, 0, 262144, 0, 0), -- Water Keg
(376240, 0, 262144, 0, 0), -- Climbing Gear
(375673, 0, 262144, 0, 0), -- Climbing Gear
(381343, 0, 270336, 0, 0), -- Ancient Stone
(376943, 0, 2113540, 0, 0), -- Dracuixote
(376944, 0, 2113540, 0, 0), -- The Lord of the Wings
(376946, 0, 2113540, 0, 0), -- Pride and Protodrakes
(380516, 0, 278528, 18512, 0), -- Glimmer of Wisdom
(380510, 0, 262144, 0, 0), -- Dim Forge
(376199, 0, 0, 0, 9340), -- Hatched Dragon Egg
(376945, 0, 2113540, 0, 0), -- The Red and the Black Flights
(376942, 0, 2113540, 0, 0), -- The Scales of Wrath
(376941, 0, 2113540, 0, 0), -- The Titanic Comedy
(381196, 0, 278528, 0, 0), -- Titan-Touched Writhebark
(377499, 0, 4, 0, 0), -- On the Origin of Draconic Species
(379248, 94, 278528, 0, 0); -- Draconium Deposit

UPDATE `gameobject_template_addon` SET `faction`=35, `flags`=0, `WorldEffectID`=2773 WHERE `entry` IN (268887, 241593, 268888); -- Fishing Bobber
UPDATE `gameobject_template_addon` SET `faction`=35 WHERE `entry`=35591; -- Fishing Bobber
UPDATE `gameobject_template_addon` SET `flags`=4 WHERE `entry`=380940; -- Broken Head


DELETE FROM `scene_template` WHERE `SceneId` IN (3008, 2920);
INSERT INTO `scene_template` (`SceneId`, `Flags`, `ScriptPackageID`, `Encrypted`) VALUES
(3008, 17, 3639, 0),
(2920, 17, 3657, 0);


DELETE FROM `quest_offer_reward` WHERE `ID` IN (66114 /*For the Benefit of the Queen*/, 66000 /*Library of Alexstrasza*/, 65998 /*Future of the Flights*/, 65997 /*Chasing Sendrax*/, 65996 /*Veteran Reinforcements*/, 66998 /*Fighting Fire with... Water*/, 65992 /*Blacktalon Intel*/, 65995 /*The Obsidian Citadel*/);
INSERT INTO `quest_offer_reward` (`ID`, `Emote1`, `Emote2`, `Emote3`, `Emote4`, `EmoteDelay1`, `EmoteDelay2`, `EmoteDelay3`, `EmoteDelay4`, `RewardText`, `VerifiedBuild`) VALUES
(66114, 0, 0, 0, 0, 0, 0, 0, 0, '', 45505), -- For the Benefit of the Queen
(66000, 0, 0, 0, 0, 0, 0, 0, 0, '', 45505), -- Library of Alexstrasza
(65998, 0, 0, 0, 0, 0, 0, 0, 0, '', 45505), -- Future of the Flights
(65997, 0, 0, 0, 0, 0, 0, 0, 0, '', 45505), -- Chasing Sendrax
(65996, 0, 0, 0, 0, 0, 0, 0, 0, '', 45505), -- Veteran Reinforcements
(66998, 0, 0, 0, 0, 0, 0, 0, 0, '', 45505), -- Fighting Fire with... Water
(65992, 0, 0, 0, 0, 0, 0, 0, 0, '', 45505), -- Blacktalon Intel
(65995, 0, 0, 0, 0, 0, 0, 0, 0, '', 45505); -- The Obsidian Citadel


DELETE FROM `quest_poi` WHERE (`QuestID`=70061 AND `BlobIndex`=0 AND `Idx1`=5) OR (`QuestID`=70061 AND `BlobIndex`=0 AND `Idx1`=4) OR (`QuestID`=70061 AND `BlobIndex`=0 AND `Idx1`=3) OR (`QuestID`=70061 AND `BlobIndex`=0 AND `Idx1`=2) OR (`QuestID`=70061 AND `BlobIndex`=0 AND `Idx1`=1) OR (`QuestID`=70061 AND `BlobIndex`=0 AND `Idx1`=0) OR (`QuestID`=70058 AND `BlobIndex`=0 AND `Idx1`=4) OR (`QuestID`=70058 AND `BlobIndex`=0 AND `Idx1`=3) OR (`QuestID`=70058 AND `BlobIndex`=0 AND `Idx1`=2) OR (`QuestID`=70058 AND `BlobIndex`=0 AND `Idx1`=1) OR (`QuestID`=70058 AND `BlobIndex`=0 AND `Idx1`=0) OR (`QuestID`=66825 AND `BlobIndex`=0 AND `Idx1`=2) OR (`QuestID`=66825 AND `BlobIndex`=0 AND `Idx1`=1) OR (`QuestID`=66825 AND `BlobIndex`=0 AND `Idx1`=0) OR (`QuestID`=68795 AND `BlobIndex`=0 AND `Idx1`=2) OR (`QuestID`=68795 AND `BlobIndex`=0 AND `Idx1`=1) OR (`QuestID`=68795 AND `BlobIndex`=0 AND `Idx1`=0) OR (`QuestID`=66115 AND `BlobIndex`=0 AND `Idx1`=5) OR (`QuestID`=66115 AND `BlobIndex`=0 AND `Idx1`=4) OR (`QuestID`=66115 AND `BlobIndex`=0 AND `Idx1`=3) OR (`QuestID`=66115 AND `BlobIndex`=0 AND `Idx1`=2) OR (`QuestID`=66115 AND `BlobIndex`=0 AND `Idx1`=1) OR (`QuestID`=66115 AND `BlobIndex`=0 AND `Idx1`=0) OR (`QuestID`=66114 AND `BlobIndex`=0 AND `Idx1`=2) OR (`QuestID`=66114 AND `BlobIndex`=0 AND `Idx1`=1) OR (`QuestID`=66114 AND `BlobIndex`=0 AND `Idx1`=0) OR (`QuestID`=70179 AND `BlobIndex`=0 AND `Idx1`=2) OR (`QuestID`=70179 AND `BlobIndex`=0 AND `Idx1`=1) OR (`QuestID`=70179 AND `BlobIndex`=0 AND `Idx1`=0) OR (`QuestID`=66001 AND `BlobIndex`=0 AND `Idx1`=6) OR (`QuestID`=66001 AND `BlobIndex`=2 AND `Idx1`=5) OR (`QuestID`=66001 AND `BlobIndex`=1 AND `Idx1`=4) OR (`QuestID`=66001 AND `BlobIndex`=0 AND `Idx1`=3) OR (`QuestID`=66001 AND `BlobIndex`=0 AND `Idx1`=2) OR (`QuestID`=66001 AND `BlobIndex`=0 AND `Idx1`=1) OR (`QuestID`=66001 AND `BlobIndex`=0 AND `Idx1`=0) OR (`QuestID`=66000 AND `BlobIndex`=0 AND `Idx1`=2) OR (`QuestID`=66000 AND `BlobIndex`=0 AND `Idx1`=1) OR (`QuestID`=66000 AND `BlobIndex`=0 AND `Idx1`=0) OR (`QuestID`=65999 AND `BlobIndex`=0 AND `Idx1`=2) OR (`QuestID`=65999 AND `BlobIndex`=0 AND `Idx1`=1) OR (`QuestID`=65999 AND `BlobIndex`=0 AND `Idx1`=0) OR (`QuestID`=65998 AND `BlobIndex`=0 AND `Idx1`=3) OR (`QuestID`=65998 AND `BlobIndex`=0 AND `Idx1`=2) OR (`QuestID`=65998 AND `BlobIndex`=0 AND `Idx1`=1) OR (`QuestID`=65998 AND `BlobIndex`=0 AND `Idx1`=0) OR (`QuestID`=65997 AND `BlobIndex`=1 AND `Idx1`=2) OR (`QuestID`=65997 AND `BlobIndex`=0 AND `Idx1`=1) OR (`QuestID`=65997 AND `BlobIndex`=0 AND `Idx1`=0) OR (`QuestID`=66998 AND `BlobIndex`=0 AND `Idx1`=2) OR (`QuestID`=66998 AND `BlobIndex`=0 AND `Idx1`=1) OR (`QuestID`=66998 AND `BlobIndex`=0 AND `Idx1`=0) OR (`QuestID`=65996 AND `BlobIndex`=0 AND `Idx1`=3) OR (`QuestID`=65996 AND `BlobIndex`=0 AND `Idx1`=2) OR (`QuestID`=65996 AND `BlobIndex`=0 AND `Idx1`=1) OR (`QuestID`=65996 AND `BlobIndex`=0 AND `Idx1`=0);
INSERT INTO `quest_poi` (`QuestID`, `BlobIndex`, `Idx1`, `ObjectiveIndex`, `QuestObjectiveID`, `QuestObjectID`, `MapID`, `UiMapID`, `Priority`, `Flags`, `WorldEffectID`, `PlayerConditionID`, `NavigationPlayerConditionID`, `SpawnTrackingID`, `AlwaysAllowMergingBlobs`, `VerifiedBuild`) VALUES
(70061, 0, 5, 32, 0, 0, 2444, 2022, 0, 0, 0, 0, 0, 2238978, 0, 45505), -- -Unknown-
(70061, 0, 4, 3, 429870, 194159, 2444, 2022, 0, 0, 0, 0, 0, 0, 0, 45505), -- -Unknown-
(70061, 0, 3, 2, 429862, 194142, 2444, 2022, 0, 0, 0, 0, 0, 0, 0, 45505), -- -Unknown-
(70061, 0, 2, 1, 429861, 193994, 2444, 2022, 0, 0, 0, 0, 0, 0, 0, 45505), -- -Unknown-
(70061, 0, 1, 0, 429779, 193979, 2444, 2022, 0, 0, 0, 0, 0, 2239618, 0, 45505), -- -Unknown-
(70061, 0, 0, -1, 0, 0, 2444, 2022, 0, 0, 0, 0, 0, 2212533, 0, 45505), -- -Unknown-
(70058, 0, 4, 32, 0, 0, 2444, 2022, 0, 0, 0, 0, 0, 2236986, 0, 45505), -- Friend on the Mend
(70058, 0, 3, 2, 430337, 198345, 2444, 2022, 1, 0, 0, 0, 0, 2237200, 0, 45505), -- Friend on the Mend
(70058, 0, 2, 1, 429774, 198344, 2444, 2022, 0, 2, 0, 0, 0, 0, 0, 45505), -- Friend on the Mend
(70058, 0, 1, 0, 429773, 198343, 2444, 2022, 0, 2, 0, 0, 0, 0, 0, 45505), -- Friend on the Mend
(70058, 0, 0, -1, 0, 0, 2444, 2022, 0, 2, 0, 0, 0, 2223531, 0, 45505), -- Friend on the Mend
(66825, 0, 2, 32, 0, 0, 2444, 2022, 0, 0, 0, 0, 0, 2205256, 0, 45505), -- -Unknown-
(66825, 0, 1, 31, 0, 0, 2444, 2022, 0, 2, 0, 0, 0, 0, 0, 45505), -- -Unknown-
(66825, 0, 0, -1, 0, 0, 2444, 2022, 0, 0, 0, 0, 0, 2205256, 0, 45505), -- -Unknown-
(68795, 0, 2, 32, 0, 0, 2444, 2022, 0, 0, 0, 0, 0, 2192635, 0, 45505), -- -Unknown-
(68795, 0, 1, 0, 429384, 193287, 2444, 2022, 0, 0, 0, 0, 0, 2224435, 0, 45505), -- -Unknown-
(68795, 0, 0, -1, 0, 0, 2444, 2022, 0, 0, 0, 0, 0, 2227086, 0, 45505), -- -Unknown-
(66115, 0, 5, 32, 0, 0, 2444, 2022, 0, 0, 0, 0, 0, 2192635, 0, 45505), -- -Unknown-
(66115, 0, 4, 3, 427107, 189260, 2444, 2022, 0, 0, 0, 0, 0, 2192674, 0, 45505), -- -Unknown-
(66115, 0, 3, 2, 427106, 185904, 2444, 2022, 0, 0, 0, 0, 0, 2170244, 0, 45505), -- -Unknown-
(66115, 0, 2, 1, 427109, 189262, 2444, 2022, 0, 0, 0, 0, 0, 2231844, 0, 45505), -- -Unknown-
(66115, 0, 1, 0, 427108, 189261, 2444, 2022, 0, 0, 0, 0, 0, 2192675, 0, 45505), -- -Unknown-
(66115, 0, 0, -1, 0, 0, 2444, 2022, 0, 0, 0, 0, 0, 2192674, 0, 45505), -- -Unknown-
(66114, 0, 2, 32, 0, 0, 2444, 2022, 0, 0, 0, 0, 0, 2196731, 0, 45505), -- For the Benefit of the Queen
(66114, 0, 1, 0, 429819, 191768, 2444, 2022, 0, 0, 0, 0, 0, 2212533, 0, 45505), -- For the Benefit of the Queen
(66114, 0, 0, -1, 0, 0, 2444, 2022, 0, 0, 0, 0, 0, 2192635, 0, 45505), -- For the Benefit of the Queen
(70179, 0, 2, 32, 0, 0, 2444, 2022, 0, 0, 0, 0, 0, 2242628, 0, 45505), -- A Two for One Deal
(70179, 0, 1, 0, 430094, 198511, 2444, 2022, 0, 2, 0, 0, 0, 0, 0, 45505), -- A Two for One Deal
(70179, 0, 0, -1, 0, 0, 2444, 2022, 0, 0, 0, 0, 0, 2242628, 0, 45505), -- A Two for One Deal
(66001, 0, 6, 32, 0, 0, 2444, 2022, 0, 2, 0, 0, 0, 0, 0, 45505), -- -Unknown-
(66001, 2, 5, 3, 427562, 190211, 2444, 2022, 0, 2, 0, 98660, 0, 0, 0, 45505), -- -Unknown-
(66001, 1, 4, 3, 427562, 190211, 2444, 2022, 0, 0, 0, 98659, 0, 2198020, 0, 45505), -- -Unknown-
(66001, 0, 3, 3, 427562, 190211, 2444, 2022, 0, 0, 0, 98658, 0, 2199171, 0, 45505), -- -Unknown-
(66001, 0, 2, 1, 427836, 191888, 2444, 2022, 0, 0, 0, 0, 0, 2198020, 0, 45505), -- -Unknown-
(66001, 0, 1, 0, 427620, 190269, 2444, 2022, 0, 0, 0, 0, 0, 2199679, 0, 45505), -- -Unknown-
(66001, 0, 0, -1, 0, 0, 2444, 2022, 0, 0, 0, 0, 0, 2196731, 0, 45505), -- -Unknown-
(66000, 0, 2, 32, 0, 0, 2444, 2022, 0, 0, 0, 0, 0, 2177503, 0, 45505), -- Library of Alexstrasza
(66000, 0, 1, 0, 427448, 189921, 2444, 2022, 0, 2, 0, 0, 0, 0, 0, 45505), -- Library of Alexstrasza
(66000, 0, 0, -1, 0, 0, 2444, 2022, 0, 0, 0, 0, 0, 2197022, 0, 45505), -- Library of Alexstrasza
(65999, 0, 2, 32, 0, 0, 2444, 2022, 0, 0, 0, 0, 0, 2197022, 0, 45505), -- Red in Tooth and Claw
(65999, 0, 1, 0, 427462, 189975, 2444, 2022, 0, 0, 0, 0, 0, 0, 0, 45505), -- Red in Tooth and Claw
(65999, 0, 0, -1, 0, 0, 2444, 2022, 0, 0, 0, 0, 0, 2197022, 0, 45505), -- Red in Tooth and Claw
(65998, 0, 3, 32, 0, 0, 2444, 2022, 0, 0, 0, 0, 0, 2197022, 0, 45505), -- Future of the Flights
(65998, 0, 2, 1, 427478, 186822, 2444, 2022, 0, 0, 0, 0, 0, 0, 0, 45505), -- Future of the Flights
(65998, 0, 1, 0, 427477, 191884, 2444, 2022, 0, 0, 0, 0, 0, 2212989, 0, 45505), -- Future of the Flights
(65998, 0, 0, -1, 0, 0, 2444, 2022, 0, 0, 0, 0, 0, 2197022, 0, 45505), -- Future of the Flights
(65997, 1, 2, 32, 0, 0, 2444, 2022, 0, 2, 0, 0, 0, 2198270, 0, 45505), -- Chasing Sendrax
(65997, 0, 1, 32, 0, 0, 2444, 2022, 0, 0, 0, 0, 0, 2198270, 0, 45505), -- Chasing Sendrax
(65997, 0, 0, 0, 427534, 187406, 2444, 2022, 0, 0, 0, 0, 0, 2197022, 0, 45505), -- Chasing Sendrax
(66998, 0, 2, 32, 0, 0, 2444, 2022, 0, 0, 0, 0, 0, 2188759, 0, 45505), -- Fighting Fire with... Water
(66998, 0, 1, 1, 428766, 192032, 2444, 2022, 0, 2, 0, 0, 0, 0, 1, 45505), -- Fighting Fire with... Water
(66998, 0, 0, -1, 0, 0, 2444, 2022, 0, 0, 0, 0, 0, 2188759, 0, 45505), -- Fighting Fire with... Water
(65996, 0, 3, 32, 0, 0, 2444, 2022, 0, 0, 0, 0, 0, 2244942, 0, 45505), -- Veteran Reinforcements
(65996, 0, 2, 2, 429977, 190155, 2444, 2022, 0, 0, 0, 0, 0, 2198270, 0, 45505), -- Veteran Reinforcements
(65996, 0, 1, 0, 429945, 190771, 2444, 2022, 0, 0, 0, 0, 0, 0, 0, 45505), -- Veteran Reinforcements
(65996, 0, 0, -1, 0, 0, 2444, 2022, 0, 0, 0, 0, 0, 2198270, 0, 45505); -- Veteran Reinforcements

DELETE FROM `quest_poi_points` WHERE (`QuestID`=70061 AND `Idx1`=5 AND `Idx2`=0) OR (`QuestID`=70061 AND `Idx1`=4 AND `Idx2`=2) OR (`QuestID`=70061 AND `Idx1`=4 AND `Idx2`=1) OR (`QuestID`=70061 AND `Idx1`=4 AND `Idx2`=0) OR (`QuestID`=70061 AND `Idx1`=3 AND `Idx2`=11) OR (`QuestID`=70061 AND `Idx1`=3 AND `Idx2`=10) OR (`QuestID`=70061 AND `Idx1`=3 AND `Idx2`=9) OR (`QuestID`=70061 AND `Idx1`=3 AND `Idx2`=8) OR (`QuestID`=70061 AND `Idx1`=3 AND `Idx2`=7) OR (`QuestID`=70061 AND `Idx1`=3 AND `Idx2`=6) OR (`QuestID`=70061 AND `Idx1`=3 AND `Idx2`=5) OR (`QuestID`=70061 AND `Idx1`=3 AND `Idx2`=4) OR (`QuestID`=70061 AND `Idx1`=3 AND `Idx2`=3) OR (`QuestID`=70061 AND `Idx1`=3 AND `Idx2`=2) OR (`QuestID`=70061 AND `Idx1`=3 AND `Idx2`=1) OR (`QuestID`=70061 AND `Idx1`=3 AND `Idx2`=0) OR (`QuestID`=70061 AND `Idx1`=2 AND `Idx2`=11) OR (`QuestID`=70061 AND `Idx1`=2 AND `Idx2`=10) OR (`QuestID`=70061 AND `Idx1`=2 AND `Idx2`=9) OR (`QuestID`=70061 AND `Idx1`=2 AND `Idx2`=8) OR (`QuestID`=70061 AND `Idx1`=2 AND `Idx2`=7) OR (`QuestID`=70061 AND `Idx1`=2 AND `Idx2`=6) OR (`QuestID`=70061 AND `Idx1`=2 AND `Idx2`=5) OR (`QuestID`=70061 AND `Idx1`=2 AND `Idx2`=4) OR (`QuestID`=70061 AND `Idx1`=2 AND `Idx2`=3) OR (`QuestID`=70061 AND `Idx1`=2 AND `Idx2`=2) OR (`QuestID`=70061 AND `Idx1`=2 AND `Idx2`=1) OR (`QuestID`=70061 AND `Idx1`=2 AND `Idx2`=0) OR (`QuestID`=70061 AND `Idx1`=1 AND `Idx2`=0) OR (`QuestID`=70061 AND `Idx1`=0 AND `Idx2`=0) OR (`QuestID`=70058 AND `Idx1`=4 AND `Idx2`=0) OR (`QuestID`=70058 AND `Idx1`=3 AND `Idx2`=0) OR (`QuestID`=70058 AND `Idx1`=2 AND `Idx2`=5) OR (`QuestID`=70058 AND `Idx1`=2 AND `Idx2`=4) OR (`QuestID`=70058 AND `Idx1`=2 AND `Idx2`=3) OR (`QuestID`=70058 AND `Idx1`=2 AND `Idx2`=2) OR (`QuestID`=70058 AND `Idx1`=2 AND `Idx2`=1) OR (`QuestID`=70058 AND `Idx1`=2 AND `Idx2`=0) OR (`QuestID`=70058 AND `Idx1`=1 AND `Idx2`=5) OR (`QuestID`=70058 AND `Idx1`=1 AND `Idx2`=4) OR (`QuestID`=70058 AND `Idx1`=1 AND `Idx2`=3) OR (`QuestID`=70058 AND `Idx1`=1 AND `Idx2`=2) OR (`QuestID`=70058 AND `Idx1`=1 AND `Idx2`=1) OR (`QuestID`=70058 AND `Idx1`=1 AND `Idx2`=0) OR (`QuestID`=70058 AND `Idx1`=0 AND `Idx2`=0) OR (`QuestID`=66825 AND `Idx1`=2 AND `Idx2`=0) OR (`QuestID`=66825 AND `Idx1`=1 AND `Idx2`=11) OR (`QuestID`=66825 AND `Idx1`=1 AND `Idx2`=10) OR (`QuestID`=66825 AND `Idx1`=1 AND `Idx2`=9) OR (`QuestID`=66825 AND `Idx1`=1 AND `Idx2`=8) OR (`QuestID`=66825 AND `Idx1`=1 AND `Idx2`=7) OR (`QuestID`=66825 AND `Idx1`=1 AND `Idx2`=6) OR (`QuestID`=66825 AND `Idx1`=1 AND `Idx2`=5) OR (`QuestID`=66825 AND `Idx1`=1 AND `Idx2`=4) OR (`QuestID`=66825 AND `Idx1`=1 AND `Idx2`=3) OR (`QuestID`=66825 AND `Idx1`=1 AND `Idx2`=2) OR (`QuestID`=66825 AND `Idx1`=1 AND `Idx2`=1) OR (`QuestID`=66825 AND `Idx1`=1 AND `Idx2`=0) OR (`QuestID`=66825 AND `Idx1`=0 AND `Idx2`=0) OR (`QuestID`=68795 AND `Idx1`=2 AND `Idx2`=0) OR (`QuestID`=68795 AND `Idx1`=1 AND `Idx2`=0) OR (`QuestID`=68795 AND `Idx1`=0 AND `Idx2`=0) OR (`QuestID`=66115 AND `Idx1`=5 AND `Idx2`=0) OR (`QuestID`=66115 AND `Idx1`=4 AND `Idx2`=0) OR (`QuestID`=66115 AND `Idx1`=3 AND `Idx2`=0) OR (`QuestID`=66115 AND `Idx1`=2 AND `Idx2`=0) OR (`QuestID`=66115 AND `Idx1`=1 AND `Idx2`=0) OR (`QuestID`=66115 AND `Idx1`=0 AND `Idx2`=0) OR (`QuestID`=66114 AND `Idx1`=2 AND `Idx2`=0) OR (`QuestID`=66114 AND `Idx1`=1 AND `Idx2`=0) OR (`QuestID`=66114 AND `Idx1`=0 AND `Idx2`=0) OR (`QuestID`=70179 AND `Idx1`=2 AND `Idx2`=0) OR (`QuestID`=70179 AND `Idx1`=1 AND `Idx2`=10) OR (`QuestID`=70179 AND `Idx1`=1 AND `Idx2`=9) OR (`QuestID`=70179 AND `Idx1`=1 AND `Idx2`=8) OR (`QuestID`=70179 AND `Idx1`=1 AND `Idx2`=7) OR (`QuestID`=70179 AND `Idx1`=1 AND `Idx2`=6) OR (`QuestID`=70179 AND `Idx1`=1 AND `Idx2`=5) OR (`QuestID`=70179 AND `Idx1`=1 AND `Idx2`=4) OR (`QuestID`=70179 AND `Idx1`=1 AND `Idx2`=3) OR (`QuestID`=70179 AND `Idx1`=1 AND `Idx2`=2) OR (`QuestID`=70179 AND `Idx1`=1 AND `Idx2`=1) OR (`QuestID`=70179 AND `Idx1`=1 AND `Idx2`=0) OR (`QuestID`=70179 AND `Idx1`=0 AND `Idx2`=0) OR (`QuestID`=66001 AND `Idx1`=6 AND `Idx2`=0) OR (`QuestID`=66001 AND `Idx1`=5 AND `Idx2`=0) OR (`QuestID`=66001 AND `Idx1`=4 AND `Idx2`=0) OR (`QuestID`=66001 AND `Idx1`=3 AND `Idx2`=0) OR (`QuestID`=66001 AND `Idx1`=2 AND `Idx2`=0) OR (`QuestID`=66001 AND `Idx1`=1 AND `Idx2`=0) OR (`QuestID`=66001 AND `Idx1`=0 AND `Idx2`=0) OR (`QuestID`=66000 AND `Idx1`=2 AND `Idx2`=0) OR (`QuestID`=66000 AND `Idx1`=1 AND `Idx2`=11) OR (`QuestID`=66000 AND `Idx1`=1 AND `Idx2`=10) OR (`QuestID`=66000 AND `Idx1`=1 AND `Idx2`=9) OR (`QuestID`=66000 AND `Idx1`=1 AND `Idx2`=8) OR (`QuestID`=66000 AND `Idx1`=1 AND `Idx2`=7) OR (`QuestID`=66000 AND `Idx1`=1 AND `Idx2`=6) OR (`QuestID`=66000 AND `Idx1`=1 AND `Idx2`=5) OR (`QuestID`=66000 AND `Idx1`=1 AND `Idx2`=4) OR (`QuestID`=66000 AND `Idx1`=1 AND `Idx2`=3) OR (`QuestID`=66000 AND `Idx1`=1 AND `Idx2`=2) OR (`QuestID`=66000 AND `Idx1`=1 AND `Idx2`=1) OR (`QuestID`=66000 AND `Idx1`=1 AND `Idx2`=0) OR (`QuestID`=66000 AND `Idx1`=0 AND `Idx2`=0) OR (`QuestID`=65999 AND `Idx1`=2 AND `Idx2`=0) OR (`QuestID`=65999 AND `Idx1`=1 AND `Idx2`=8) OR (`QuestID`=65999 AND `Idx1`=1 AND `Idx2`=7) OR (`QuestID`=65999 AND `Idx1`=1 AND `Idx2`=6) OR (`QuestID`=65999 AND `Idx1`=1 AND `Idx2`=5) OR (`QuestID`=65999 AND `Idx1`=1 AND `Idx2`=4) OR (`QuestID`=65999 AND `Idx1`=1 AND `Idx2`=3) OR (`QuestID`=65999 AND `Idx1`=1 AND `Idx2`=2) OR (`QuestID`=65999 AND `Idx1`=1 AND `Idx2`=1) OR (`QuestID`=65999 AND `Idx1`=1 AND `Idx2`=0) OR (`QuestID`=65999 AND `Idx1`=0 AND `Idx2`=0) OR (`QuestID`=65998 AND `Idx1`=3 AND `Idx2`=0) OR (`QuestID`=65998 AND `Idx1`=2 AND `Idx2`=5) OR (`QuestID`=65998 AND `Idx1`=2 AND `Idx2`=4) OR (`QuestID`=65998 AND `Idx1`=2 AND `Idx2`=3) OR (`QuestID`=65998 AND `Idx1`=2 AND `Idx2`=2) OR (`QuestID`=65998 AND `Idx1`=2 AND `Idx2`=1) OR (`QuestID`=65998 AND `Idx1`=2 AND `Idx2`=0) OR (`QuestID`=65998 AND `Idx1`=1 AND `Idx2`=0) OR (`QuestID`=65998 AND `Idx1`=0 AND `Idx2`=0) OR (`QuestID`=65997 AND `Idx1`=2 AND `Idx2`=0) OR (`QuestID`=65997 AND `Idx1`=1 AND `Idx2`=0) OR (`QuestID`=65997 AND `Idx1`=0 AND `Idx2`=0) OR (`QuestID`=66998 AND `Idx1`=2 AND `Idx2`=0) OR (`QuestID`=66998 AND `Idx1`=1 AND `Idx2`=11) OR (`QuestID`=66998 AND `Idx1`=1 AND `Idx2`=10) OR (`QuestID`=66998 AND `Idx1`=1 AND `Idx2`=9) OR (`QuestID`=66998 AND `Idx1`=1 AND `Idx2`=8) OR (`QuestID`=66998 AND `Idx1`=1 AND `Idx2`=7) OR (`QuestID`=66998 AND `Idx1`=1 AND `Idx2`=6) OR (`QuestID`=66998 AND `Idx1`=1 AND `Idx2`=5) OR (`QuestID`=66998 AND `Idx1`=1 AND `Idx2`=4) OR (`QuestID`=66998 AND `Idx1`=1 AND `Idx2`=3) OR (`QuestID`=66998 AND `Idx1`=1 AND `Idx2`=2) OR (`QuestID`=66998 AND `Idx1`=1 AND `Idx2`=1) OR (`QuestID`=66998 AND `Idx1`=1 AND `Idx2`=0) OR (`QuestID`=66998 AND `Idx1`=0 AND `Idx2`=0) OR (`QuestID`=65996 AND `Idx1`=3 AND `Idx2`=0) OR (`QuestID`=65996 AND `Idx1`=2 AND `Idx2`=0) OR (`QuestID`=65996 AND `Idx1`=1 AND `Idx2`=3) OR (`QuestID`=65996 AND `Idx1`=1 AND `Idx2`=2) OR (`QuestID`=65996 AND `Idx1`=1 AND `Idx2`=1) OR (`QuestID`=65996 AND `Idx1`=1 AND `Idx2`=0) OR (`QuestID`=65996 AND `Idx1`=0 AND `Idx2`=0);
INSERT INTO `quest_poi_points` (`QuestID`, `Idx1`, `Idx2`, `X`, `Y`, `Z`, `VerifiedBuild`) VALUES
(70061, 5, 0, 1618, -306, 332, 45505), -- -Unknown-
(70061, 4, 2, 1504, -271, 227, 45505), -- -Unknown-
(70061, 4, 1, 1525, -201, 193, 45505), -- -Unknown-
(70061, 4, 0, 1590, -280, 259, 45505), -- -Unknown-
(70061, 3, 11, 1527, -295, 162, 45505), -- -Unknown-
(70061, 3, 10, 1516, -288, 196, 45505), -- -Unknown-
(70061, 3, 9, 1498, -256, 259, 45505), -- -Unknown-
(70061, 3, 8, 1504, -217, 318, 45505), -- -Unknown-
(70061, 3, 7, 1541, -192, 162, 45505), -- -Unknown-
(70061, 3, 6, 1550, -188, 278, 45505), -- -Unknown-
(70061, 3, 5, 1592, -211, 198, 45505), -- -Unknown-
(70061, 3, 4, 1605, -266, 241, 45505), -- -Unknown-
(70061, 3, 3, 1593, -278, 228, 45505), -- -Unknown-
(70061, 3, 2, 1577, -293, 326, 45505), -- -Unknown-
(70061, 3, 1, 1571, -298, 262, 45505), -- -Unknown-
(70061, 3, 0, 1555, -305, 162, 45505), -- -Unknown-
(70061, 2, 11, 1531, -300, 260, 45505), -- -Unknown-
(70061, 2, 10, 1502, -277, 259, 45505), -- -Unknown-
(70061, 2, 9, 1493, -252, 228, 45505), -- -Unknown-
(70061, 2, 8, 1491, -234, 259, 45505), -- -Unknown-
(70061, 2, 7, 1516, -204, 160, 45505), -- -Unknown-
(70061, 2, 6, 1543, -190, 305, 45505), -- -Unknown-
(70061, 2, 5, 1581, -200, 193, 45505), -- -Unknown-
(70061, 2, 4, 1605, -230, 192, 45505), -- -Unknown-
(70061, 2, 3, 1605, -256, 161, 45505), -- -Unknown-
(70061, 2, 2, 1591, -284, 193, 45505), -- -Unknown-
(70061, 2, 1, 1572, -298, 211, 45505), -- -Unknown-
(70061, 2, 0, 1534, -302, 196, 45505), -- -Unknown-
(70061, 1, 0, 1571, -219, 312, 45505), -- -Unknown-
(70061, 0, 0, 1499, -318, 330, 45505), -- -Unknown-
(70058, 4, 0, 1627, -123, 334, 45505), -- Friend on the Mend
(70058, 3, 0, 1577, -117, 332, 45505), -- Friend on the Mend
(70058, 2, 5, 1499, -180, 332, 45505), -- Friend on the Mend
(70058, 2, 4, 1479, -138, 332, 45505), -- Friend on the Mend
(70058, 2, 3, 1545, -100, 331, 45505), -- Friend on the Mend
(70058, 2, 2, 1676, -164, 330, 45505), -- Friend on the Mend
(70058, 2, 1, 1630, -194, 331, 45505), -- Friend on the Mend
(70058, 2, 0, 1574, -155, 332, 45505), -- Friend on the Mend
(70058, 1, 5, 1625, -291, 332, 45505), -- Friend on the Mend
(70058, 1, 4, 1616, -263, 332, 45505), -- Friend on the Mend
(70058, 1, 3, 1643, -191, 331, 45505), -- Friend on the Mend
(70058, 1, 2, 1693, -188, 330, 45505), -- Friend on the Mend
(70058, 1, 1, 1706, -219, 331, 45505), -- Friend on the Mend
(70058, 1, 0, 1660, -291, 332, 45505), -- Friend on the Mend
(70058, 0, 0, 1641, -247, 331, 45505), -- Friend on the Mend
(66825, 2, 0, 1445, -284, 330, 45505), -- -Unknown-
(66825, 1, 11, 1421, -312, 0, 45505), -- -Unknown-
(66825, 1, 10, 1415, -296, 0, 45505), -- -Unknown-
(66825, 1, 9, 1421, -278, 0, 45505), -- -Unknown-
(66825, 1, 8, 1433, -266, 0, 45505), -- -Unknown-
(66825, 1, 7, 1447, -261, 0, 45505), -- -Unknown-
(66825, 1, 6, 1465, -260, 0, 45505), -- -Unknown-
(66825, 1, 5, 1477, -273, 0, 45505), -- -Unknown-
(66825, 1, 4, 1477, -292, 0, 45505), -- -Unknown-
(66825, 1, 3, 1472, -308, 0, 45505), -- -Unknown-
(66825, 1, 2, 1461, -318, 0, 45505), -- -Unknown-
(66825, 1, 1, 1448, -324, 0, 45505), -- -Unknown-
(66825, 1, 0, 1433, -320, 0, 45505), -- -Unknown-
(66825, 0, 0, 1445, -284, 330, 45505), -- -Unknown-
(68795, 2, 0, 1488, -319, 330, 45505), -- -Unknown-
(68795, 1, 0, 1804, -3, 312, 45505), -- -Unknown-
(68795, 0, 0, 1813, 55, 313, 45505), -- -Unknown-
(66115, 5, 0, 1488, -319, 330, 45505), -- -Unknown-
(66115, 4, 0, 1625, -354, 337, 45505), -- -Unknown-
(66115, 3, 0, 1717, -259, 337, 45505), -- -Unknown-
(66115, 2, 0, 1520, -82, 337, 45505), -- -Unknown-
(66115, 1, 0, 1433, -189, 337, 45505), -- -Unknown-
(66115, 0, 0, 1625, -354, 337, 45505), -- -Unknown-
(66114, 2, 0, 3722, 260, 70, 45505), -- For the Benefit of the Queen
(66114, 1, 0, 1499, -318, 330, 45505), -- For the Benefit of the Queen
(66114, 0, 0, 1488, -319, 330, 45505), -- For the Benefit of the Queen
(70179, 2, 0, 3732, 312, 77, 45505), -- A Two for One Deal
(70179, 1, 10, 3611, 447, 254, 45505), -- A Two for One Deal
(70179, 1, 9, 3578, 580, 195, 45505), -- A Two for One Deal
(70179, 1, 8, 3547, 681, 198, 45505), -- A Two for One Deal
(70179, 1, 7, 3584, 725, 198, 45505), -- A Two for One Deal
(70179, 1, 6, 3622, 755, 213, 45505), -- A Two for One Deal
(70179, 1, 5, 3704, 691, 57, 45505), -- A Two for One Deal
(70179, 1, 4, 3738, 556, 148, 45505), -- A Two for One Deal
(70179, 1, 3, 3746, 511, 100, 45505), -- A Two for One Deal
(70179, 1, 2, 3748, 455, 98, 45505), -- A Two for One Deal
(70179, 1, 1, 3718, 374, 77, 45505), -- A Two for One Deal
(70179, 1, 0, 3659, 328, 28, 45505), -- A Two for One Deal
(70179, 0, 0, 3732, 312, 77, 45505), -- A Two for One Deal
(66001, 6, 0, 4053, 249, 54, 45505), -- -Unknown-
(66001, 5, 0, 4226, 116, 0, 45505), -- -Unknown-
(66001, 4, 0, 4223, 112, 54, 45505), -- -Unknown-
(66001, 3, 0, 3735, 267, 70, 45505), -- -Unknown-
(66001, 2, 0, 4223, 112, 54, 45505), -- -Unknown-
(66001, 1, 0, 4199, 168, 51, 45505), -- -Unknown-
(66001, 0, 0, 3722, 260, 69, 45505), -- -Unknown-
(66000, 2, 0, 4059, 244, 56, 45505), -- Library of Alexstrasza
(66000, 1, 11, 4024, 48, 0, 45505), -- Library of Alexstrasza
(66000, 1, 10, 4004, 87, 0, 45505), -- Library of Alexstrasza
(66000, 1, 9, 4033, 175, 0, 45505), -- Library of Alexstrasza
(66000, 1, 8, 4062, 233, 0, 45505), -- Library of Alexstrasza
(66000, 1, 7, 4119, 344, 0, 45505), -- Library of Alexstrasza
(66000, 1, 6, 4164, 406, 0, 45505), -- Library of Alexstrasza
(66000, 1, 5, 4202, 421, 0, 45505), -- Library of Alexstrasza
(66000, 1, 4, 4256, 388, 0, 45505), -- Library of Alexstrasza
(66000, 1, 3, 4283, 352, 0, 45505), -- Library of Alexstrasza
(66000, 1, 2, 4307, 302, 0, 45505), -- Library of Alexstrasza
(66000, 1, 1, 4296, 225, 0, 45505), -- Library of Alexstrasza
(66000, 1, 0, 4117, 41, 0, 45505), -- Library of Alexstrasza
(66000, 0, 0, 4046, 251, 54, 45505), -- Library of Alexstrasza
(65999, 2, 0, 4046, 251, 54, 45505), -- Red in Tooth and Claw
(65999, 1, 8, 4023, 104, 44, 45505), -- Red in Tooth and Claw
(65999, 1, 7, 4014, 197, 41, 45505), -- Red in Tooth and Claw
(65999, 1, 6, 4016, 231, 54, 45505), -- Red in Tooth and Claw
(65999, 1, 5, 4184, 398, 59, 45505), -- Red in Tooth and Claw
(65999, 1, 4, 4287, 293, 65, 45505), -- Red in Tooth and Claw
(65999, 1, 3, 4310, 264, 58, 45505), -- Red in Tooth and Claw
(65999, 1, 2, 4262, 160, 64, 45505), -- Red in Tooth and Claw
(65999, 1, 1, 4223, 107, 54, 45505), -- Red in Tooth and Claw
(65999, 1, 0, 4129, 63, 51, 45505), -- Red in Tooth and Claw
(65999, 0, 0, 4046, 251, 54, 45505), -- Red in Tooth and Claw
(65998, 3, 0, 4045, 252, 54, 45505), -- Future of the Flights
(65998, 2, 5, 4051, 157, 38, 45505), -- Future of the Flights
(65998, 2, 4, 4051, 160, 38, 45505), -- Future of the Flights
(65998, 2, 3, 4209, 356, 41, 45505), -- Future of the Flights
(65998, 2, 2, 4211, 356, 41, 45505), -- Future of the Flights
(65998, 2, 1, 4206, 201, 38, 45505), -- Future of the Flights
(65998, 2, 0, 4116, 104, 41, 45505), -- Future of the Flights
(65998, 1, 0, 4051, 160, 38, 45505), -- Future of the Flights
(65998, 0, 0, 4045, 252, 54, 45505), -- Future of the Flights
(65997, 2, 0, 3735, 267, 70, 45505), -- Chasing Sendrax
(65997, 1, 0, 3735, 267, 70, 45505), -- Chasing Sendrax
(65997, 0, 0, 4046, 251, 54, 45505), -- Chasing Sendrax
(66998, 2, 0, 3519, -61, 35, 45505), -- Fighting Fire with... Water
(66998, 1, 11, 3595, -115, 0, 45505), -- Fighting Fire with... Water
(66998, 1, 10, 3578, -98, 0, 45505), -- Fighting Fire with... Water
(66998, 1, 9, 3566, -51, 0, 45505), -- Fighting Fire with... Water
(66998, 1, 8, 3585, -20, 0, 45505), -- Fighting Fire with... Water
(66998, 1, 7, 3646, 10, 0, 45505), -- Fighting Fire with... Water
(66998, 1, 6, 3676, 24, 0, 45505), -- Fighting Fire with... Water
(66998, 1, 5, 3720, 24, 0, 45505), -- Fighting Fire with... Water
(66998, 1, 4, 3747, 5, 0, 45505), -- Fighting Fire with... Water
(66998, 1, 3, 3737, -18, 0, 45505), -- Fighting Fire with... Water
(66998, 1, 2, 3699, -56, 0, 45505), -- Fighting Fire with... Water
(66998, 1, 1, 3710, -101, 0, 45505), -- Fighting Fire with... Water
(66998, 1, 0, 3631, -123, 0, 45505), -- Fighting Fire with... Water
(66998, 0, 0, 3519, -61, 35, 45505), -- Fighting Fire with... Water
(65996, 3, 0, 3611, -352, 106, 45505), -- Veteran Reinforcements
(65996, 2, 0, 3735, 267, 71, 45505), -- Veteran Reinforcements
(65996, 1, 3, 3523, 135, 36, 45505), -- Veteran Reinforcements
(65996, 1, 2, 3728, 270, 71, 45505), -- Veteran Reinforcements
(65996, 1, 1, 3477, -211, 38, 45505), -- Veteran Reinforcements
(65996, 1, 0, 3416, -221, 31, 45505), -- Veteran Reinforcements
(65996, 0, 0, 3735, 267, 71, 45505); -- Veteran Reinforcements


DELETE FROM `quest_greeting` WHERE (`ID`=194772 AND `Type`=0);
INSERT INTO `quest_greeting` (`ID`, `Type`, `GreetEmoteType`, `GreetEmoteDelay`, `Greeting`, `VerifiedBuild`) VALUES
(194772, 0, 0, 0, 'These giants might be the dragons\' ancient enemies... but they don\'t stand a chance against the likes of me.', 45505); -- 194772


DELETE FROM `quest_details` WHERE `ID` IN (70061 /*-Unknown-*/, 70058 /*Friend on the Mend*/, 66825 /*-Unknown-*/, 68795 /*-Unknown-*/, 66114 /*For the Benefit of the Queen*/, 70179 /*A Two for One Deal*/, 66000 /*Library of Alexstrasza*/, 65999 /*Red in Tooth and Claw*/, 65998 /*Future of the Flights*/, 65997 /*Chasing Sendrax*/, 66998 /*Fighting Fire with... Water*/, 65996 /*Veteran Reinforcements*/);
INSERT INTO `quest_details` (`ID`, `Emote1`, `Emote2`, `Emote3`, `Emote4`, `EmoteDelay1`, `EmoteDelay2`, `EmoteDelay3`, `EmoteDelay4`, `VerifiedBuild`) VALUES
(70061, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- -Unknown-
(70058, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Friend on the Mend
(66825, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- -Unknown-
(68795, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- -Unknown-
(66114, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- For the Benefit of the Queen
(70179, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- A Two for One Deal
(66000, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Library of Alexstrasza
(65999, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Red in Tooth and Claw
(65998, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Future of the Flights
(65997, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Chasing Sendrax
(66998, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Fighting Fire with... Water
(65996, 0, 0, 0, 0, 0, 0, 0, 0, 45505); -- Veteran Reinforcements


DELETE FROM `quest_request_items` WHERE `ID` IN (66825 /*-Unknown-*/, 66000 /*Library of Alexstrasza*/);
INSERT INTO `quest_request_items` (`ID`, `EmoteOnComplete`, `EmoteOnIncomplete`, `EmoteOnCompleteDelay`, `EmoteOnIncompleteDelay`, `CompletionText`, `VerifiedBuild`) VALUES
(66825, UNKNOWN, 0, UNKNOWN, 0, '', 0), -- -Unknown-
(66000, UNKNOWN, 1, UNKNOWN, 0, '', 0); -- Library of Alexstrasza


DELETE FROM `creature_queststarter` WHERE (`id`=194174 AND `quest`=70061) OR (`id`=193955 AND `quest`=70058) OR (`id`=191025 AND `quest`=66825) OR (`id`=187290 AND `quest` IN (68795,66115)) OR (`id`=186795 AND `quest`=66114) OR (`id`=194525 AND `quest`=70179) OR (`id`=190171 AND `quest`=66001) OR (`id`=187406 AND `quest` IN (65999,65998)) OR (`id`=190155 AND `quest`=65997) OR (`id`=188297 AND `quest`=66998) OR (`id`=186767 AND `quest`=65996);
INSERT INTO `creature_queststarter` (`id`, `quest`, `VerifiedBuild`) VALUES
(194174, 70061, 45505), -- -Unknown- offered Amella
(193955, 70058, 45505), -- Friend on the Mend offered Lillistrazsa
(191025, 66825, 45505), -- -Unknown- offered Lifecaller Tzadrak
(187290, 68795, 45505), -- -Unknown- offered Alexstrasza the Life-Binder
(187290, 66115, 45505), -- -Unknown- offered Alexstrasza the Life-Binder
(186795, 66114, 45505), -- For the Benefit of the Queen offered Majordomo Selistra
(194525, 70179, 45505), -- A Two for One Deal offered Apprentice Caretaker Zefren
(190171, 66001, 45505), -- -Unknown- offered Ruby Egg Guardian
(187406, 65999, 45505), -- Red in Tooth and Claw offered Sendrax
(187406, 65998, 45505), -- Future of the Flights offered Sendrax
(190155, 65997, 45505), -- Chasing Sendrax offered Caretaker Azkra
(188297, 66998, 45505), -- Fighting Fire with... Water offered Caretaker Ventraz
(186767, 65996, 45505); -- Veteran Reinforcements offered Majordomo Selistra


DELETE FROM `creature_questender` WHERE (`id`=191025 AND `quest`=66825) OR (`id`=189260 AND `quest`=66115) OR (`id`=187290 AND `quest`=66114) OR (`id`=186795 AND `quest`=66001) OR (`id`=190171 AND `quest` IN (66000,65999,65998)) OR (`id`=187406 AND `quest`=65997) OR (`id`=190155 AND `quest`=65996) OR (`id`=188297 AND `quest`=66998) OR (`id`=194772 AND `quest` IN (65992,65995,65993));
INSERT INTO `creature_questender` (`id`, `quest`, `VerifiedBuild`) VALUES
(191025, 66825, 45505), -- -Unknown- ended by Lifecaller Tzadrak
(189260, 66115, 45505), -- -Unknown- ended by Zahkrana
(187290, 66114, 45505), -- For the Benefit of the Queen ended by Alexstrasza the Life-Binder
(186795, 66001, 45505), -- -Unknown- ended by Majordomo Selistra
(190171, 66000, 45505), -- Library of Alexstrasza ended by Ruby Egg Guardian
(190171, 65999, 45505), -- Red in Tooth and Claw ended by Ruby Egg Guardian
(190171, 65998, 45505), -- Future of the Flights ended by Ruby Egg Guardian
(187406, 65997, 45505), -- Chasing Sendrax ended by Sendrax
(190155, 65996, 45505), -- Veteran Reinforcements ended by Caretaker Azkra
(188297, 66998, 45505), -- Fighting Fire with... Water ended by Caretaker Ventraz
(194772, 65992, 45505), -- Blacktalon Intel ended by Wrathion
(194772, 65995, 45505), -- The Obsidian Citadel ended by Wrathion
(194772, 65993, 45505); -- Killjoy ended by Wrathion


DELETE FROM `gameobject_queststarter` WHERE (`id`=377499 AND `quest`=66000);
INSERT INTO `gameobject_queststarter` (`id`, `quest`, `VerifiedBuild`) VALUES
(377499, 66000, 45505); -- Library of Alexstrasza offered by On the Origin of Draconic Species


DELETE FROM `creature` WHERE `guid` BETWEEN @CGUID+0 AND @CGUID+1332;
INSERT INTO `creature` (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnDifficulties`, `PhaseId`, `PhaseGroup`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `wander_distance`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`, `VerifiedBuild`) VALUES
(@CGUID+0, 190766, 2444, 13644, 13704, '0', '0', 0, 0, 1, 3763.824462890625, -461.512786865234375, 52.7592926025390625, 3.685034751892089843, 7200, 0, 0, 86626, 0, 0, 0, 0, 0, 45505), -- Qalashi Ragetamer (Area: -Unknown- - Difficulty: 0)
(@CGUID+1, 191611, 2444, 13644, 13704, '0', '0', 0, 0, 1, 3618.9375, -466.49981689453125, 58.80168533325195312, 4.293856143951416015, 7200, 0, 0, 383628, 0, 0, 0, 0, 0, 45505), -- Dragonhunter Igordan (Area: -Unknown- - Difficulty: 0)
(@CGUID+2, 191446, 2444, 13644, 13704, '0', '0', 0, 0, 1, 3541.132080078125, -474.94097900390625, 64.4123992919921875, 1.243002772331237792, 7200, 10, 0, 86626, 0, 1, 0, 0, 0, 45505), -- Qalashi Scoundrel (Area: -Unknown- - Difficulty: 0) (Auras: 369788 - -Unknown-) (possible waypoints or random movement)
(@CGUID+3, 186792, 2444, 13644, 13704, '0', '0', 0, 0, 1, 3531.478271484375, -395.8819580078125, 70.400146484375, 4.646027088165283203, 7200, 10, 0, 86626, 0, 1, 0, 0, 0, 45505), -- Qalashi Marauder (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+4, 194804, 2444, 13644, 13704, '0', '0', 0, 0, 1, 3599.319580078125, -338.630218505859375, 106.4963531494140625, 0.182366877794265747, 7200, 0, 0, 1058312, 0, 0, 0, 0, 0, 45505), -- Qalashi Rampager (Area: -Unknown- - Difficulty: 0) (Auras: 159474 - Permanent Feign Death (NO Stun, Untrackable, Immune))
(@CGUID+5, 192134, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3616.26513671875, -475.031402587890625, 60.3210906982421875, 4.101575374603271484, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Lava Snail (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+6, 191637, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3502.4853515625, -557.61981201171875, 82.3441162109375, 4.575929641723632812, 7200, 10, 0, 30938, 0, 1, 0, 0, 0, 45505), -- Lava Phoenix (Area: -Unknown- - Difficulty: 0) (Auras: 369897 - -Unknown-) (possible waypoints or random movement)
(@CGUID+7, 191509, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3755.67431640625, -568.629638671875, 97.639556884765625, 2.627561807632446289, 7200, 10, 0, 61876, 0, 1, 0, 0, 0, 45505), -- Blazing Dreadsquall (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+8, 191672, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3534.569580078125, -527.25347900390625, 122.8572311401367187, 1.894408226013183593, 7200, 10, 0, 37126, 0, 1, 0, 0, 0, 45505), -- Lava Tarantula (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+9, 180705, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3718.374267578125, -401.595489501953125, 58.17623519897460937, 5.35394144058227539, 7200, 0, 0, 46407, 0, 0, 0, 0, 0, 45505), -- Magmammoth Calf (Area: -Unknown- - Difficulty: 0) (Auras: 265075 - -Unknown-)
(@CGUID+10, 192138, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3539.5986328125, -486.892822265625, 63.35992431640625, 4.689931869506835937, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Lava Pincer (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+11, 191672, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3541.876708984375, -614.1639404296875, 117.0739212036132812, 5.238018989562988281, 7200, 10, 0, 37126, 0, 1, 0, 0, 0, 45505), -- Lava Tarantula (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+12, 186570, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3703.588623046875, -474.8507080078125, 42.47126007080078125, 1.770077466964721679, 7200, 0, 0, 37126, 0, 0, 0, 0, 0, 45505), -- Lava Elemental (Area: -Unknown- - Difficulty: 0) (Auras: 370034 - -Unknown-, 364588 - -Unknown-)
(@CGUID+13, 191672, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3601.068603515625, -645.7408447265625, 87.312744140625, 3.824530601501464843, 7200, 10, 0, 37126, 0, 1, 0, 0, 0, 45505), -- Lava Tarantula (Area: -Unknown- - Difficulty: 0) (Auras: 391254 - -Unknown-) (possible waypoints or random movement)
(@CGUID+14, 190766, 2444, 13644, 13704, '0', '0', 0, 0, 1, 3505.944580078125, -348.37152099609375, 72.0411376953125, 1.29057323932647705, 7200, 10, 0, 86626, 0, 1, 0, 0, 0, 45505), -- Qalashi Ragetamer (Area: -Unknown- - Difficulty: 0) (Auras: 369596 - -Unknown-) (possible waypoints or random movement)
(@CGUID+15, 193001, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3707.938720703125, -458.9427490234375, 46.7411346435546875, 3.183105945587158203, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Kindlet (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+16, 188299, 2444, 13644, 13704, '0', '0', 0, 0, 1, 3598.87060546875, -375.046875, 71.1240692138671875, 4.000319957733154296, 7200, 0, 0, 247504, 100, 0, 0, 0, 0, 45505), -- Talonstalker Kavia (Area: -Unknown- - Difficulty: 0) (Auras: 279802 - -Unknown-)
(@CGUID+17, 191637, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3563.62841796875, -498.977447509765625, 82.57538604736328125, 3.660918951034545898, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Lava Phoenix (Area: -Unknown- - Difficulty: 0) (Auras: 369897 - -Unknown-)
(@CGUID+18, 192138, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3629.932373046875, -554.77215576171875, 47.49852371215820312, 5.525869369506835937, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Lava Pincer (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+19, 192138, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3530.41650390625, -555.8104248046875, 120.3456268310546875, 6.111210823059082031, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Lava Pincer (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+20, 195678, 2444, 13644, 13704, '0', '0', 0, 0, 1, 3644.5927734375, -603.137451171875, 49.52606582641601562, 1.970691323280334472, 7200, 10, 0, 370409, 0, 1, 0, 0, 0, 45505), -- Qalashi Marauder (Area: -Unknown- - Difficulty: 0) (Auras: 392039 - -Unknown-) (possible waypoints or random movement)
(@CGUID+21, 186684, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3716.247314453125, -467.80035400390625, 48.7506256103515625, 3.408217191696166992, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Lava Phoenix (Area: -Unknown- - Difficulty: 0) (Auras: 369897 - -Unknown-)
(@CGUID+22, 180705, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3746.53125, -406.703125, 56.62290573120117187, 5.83321237564086914, 7200, 0, 0, 46407, 0, 0, 0, 0, 0, 45505), -- Magmammoth Calf (Area: -Unknown- - Difficulty: 0) (Auras: )
(@CGUID+23, 192138, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3554.082275390625, -407.404693603515625, 70.27346038818359375, 1.006377696990966796, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Lava Pincer (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+24, 193001, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3641.6669921875, -458.333984375, 62.05841827392578125, 1.229046344757080078, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Kindlet (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+25, 180705, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3714.1259765625, -614.92364501953125, 37.54404449462890625, 2.787117481231689453, 7200, 0, 0, 46407, 0, 0, 0, 0, 0, 45505), -- Magmammoth Calf (Area: -Unknown- - Difficulty: 0)
(@CGUID+26, 192138, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3489.82373046875, -505.489349365234375, 69.21445465087890625, 4.353043079376220703, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Lava Pincer (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+27, 191672, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3632.848388671875, -600.3778076171875, 83.80487823486328125, 2.690100669860839843, 7200, 10, 0, 37126, 0, 1, 0, 0, 0, 45505), -- Lava Tarantula (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+28, 193001, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3706.260986328125, -489.39447021484375, 46.4163818359375, 1.816083908081054687, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Kindlet (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+29, 193024, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3706.294921875, -557.76483154296875, 36.49339675903320312, 1.527593851089477539, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Emberling (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+30, 190766, 2444, 13644, 13704, '0', '0', 0, 0, 1, 3628.718017578125, -649.592041015625, 75.91265869140625, 5.901988983154296875, 7200, 0, 0, 86626, 0, 0, 0, 0, 0, 45505), -- Qalashi Ragetamer (Area: -Unknown- - Difficulty: 0) (Auras: 358419 - -Unknown-)
(@CGUID+31, 186684, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3709.3291015625, -619.3211669921875, 36.97375869750976562, 2.043801307678222656, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Lava Phoenix (Area: -Unknown- - Difficulty: 0) (Auras: 369897 - -Unknown-)
(@CGUID+32, 192138, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3728.24462890625, -410.462677001953125, 56.98302459716796875, 4.80385446548461914, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Lava Pincer (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+33, 191637, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3632.661376953125, -451.329864501953125, 107.1958694458007812, 3.616209745407104492, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Lava Phoenix (Area: -Unknown- - Difficulty: 0) (Auras: 369897 - -Unknown-)
(@CGUID+34, 186684, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3730.10595703125, -571.4757080078125, 44.4447174072265625, 4.452168464660644531, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Lava Phoenix (Area: -Unknown- - Difficulty: 0) (Auras: 369897 - -Unknown-)
(@CGUID+35, 186767, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3610.93408203125, -352.182281494140625, 106.124755859375, 0.863309979438781738, 7200, 0, 0, 185628, 0, 0, 0, 0, 0, 45505), -- Majordomo Selistra (Area: -Unknown- - Difficulty: 0)
(@CGUID+36, 192138, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3508.908447265625, -493.250518798828125, 134.9231414794921875, 3.439850091934204101, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Lava Pincer (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+37, 186684, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3716.748291015625, -478.848968505859375, 46.83298110961914062, 3.408217191696166992, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Lava Phoenix (Area: -Unknown- - Difficulty: 0) (Auras: 369897 - -Unknown-)
(@CGUID+38, 191672, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3484.651611328125, -480.410980224609375, 141.1498870849609375, 4.08988189697265625, 7200, 10, 0, 37126, 0, 1, 0, 0, 0, 45505), -- Lava Tarantula (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+39, 190767, 2444, 13644, 13704, '0', '0', 0, 0, 1, 3572.494873046875, -323.015625, 69.7676849365234375, 1.091915726661682128, 7200, 10, 0, 92814, 0, 1, 0, 0, 0, 45505), -- Qalashi Metalshaper (Area: -Unknown- - Difficulty: 0) (Auras: 370104 - -Unknown-) (possible waypoints or random movement)
(@CGUID+40, 190766, 2444, 13644, 13704, '0', '0', 0, 0, 1, 3500.650146484375, -566.02081298828125, 74.99288177490234375, 1.330419421195983886, 7200, 10, 0, 86626, 0, 1, 0, 0, 0, 45505), -- Qalashi Ragetamer (Area: -Unknown- - Difficulty: 0) (Auras: 369788 - -Unknown-) (possible waypoints or random movement)
(@CGUID+41, 190766, 2444, 13644, 13704, '0', '0', 0, 0, 1, 3507.259521484375, -339.09722900390625, 71.00475311279296875, 5.089531898498535156, 7200, 10, 0, 86626, 0, 1, 0, 0, 0, 45505), -- Qalashi Ragetamer (Area: -Unknown- - Difficulty: 0) (Auras: 369596 - -Unknown-) (possible waypoints or random movement)
(@CGUID+42, 186582, 2444, 13644, 13704, '0', '0', 0, 0, 1, 3625.8212890625, -340.526031494140625, 105.486602783203125, 5.339634895324707031, 7200, 0, 0, 61876, 0, 0, 0, 0, 0, 45505), -- Ruby Warden (Area: -Unknown- - Difficulty: 0)
(@CGUID+43, 192138, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3518.46533203125, -377.268280029296875, 70.621917724609375, 2.20659637451171875, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Lava Pincer (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+44, 193001, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3664.036376953125, -556.38800048828125, 38.37917709350585937, 4.210592269897460937, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Kindlet (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+45, 186792, 2444, 13644, 13704, '0', '0', 0, 0, 1, 3733.876708984375, -577.11285400390625, 44.16508102416992187, 3.933420658111572265, 7200, 0, 0, 86626, 0, 0, 0, 0, 0, 45505), -- Qalashi Marauder (Area: -Unknown- - Difficulty: 0)
(@CGUID+46, 191446, 2444, 13644, 13704, '0', '0', 0, 0, 1, 3552.3701171875, -339.5478515625, 69.4919891357421875, 0.974943339824676513, 7200, 10, 0, 86626, 0, 1, 0, 0, 0, 45505), -- Qalashi Scoundrel (Area: -Unknown- - Difficulty: 0) (Auras: ) (possible waypoints or random movement)
(@CGUID+47, 180705, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3724.491455078125, -386.828125, 56.66321563720703125, 0.556363105773925781, 7200, 0, 0, 46407, 0, 0, 0, 0, 0, 45505), -- Magmammoth Calf (Area: -Unknown- - Difficulty: 0) (Auras: 265075 - -Unknown-)
(@CGUID+48, 191637, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3491.161376953125, -564.86456298828125, 80.51245880126953125, 5.555799484252929687, 7200, 10, 0, 30938, 0, 1, 0, 0, 0, 45505), -- Lava Phoenix (Area: -Unknown- - Difficulty: 0) (Auras: 369897 - -Unknown-) (possible waypoints or random movement)
(@CGUID+49, 192134, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3626.08251953125, -453.751220703125, 60.21867752075195312, 4.219461917877197265, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Lava Snail (Area: -Unknown- - Difficulty: 0)
(@CGUID+50, 197260, 2444, 13644, 13704, '0', '0', 0, 0, 1, 3683.593017578125, -574.77777099609375, 38.14502716064453125, 5.500490188598632812, 7200, 0, 0, 92814, 0, 0, 0, 0, 0, 45505), -- Flameshaper Lorak (Area: -Unknown- - Difficulty: 0) (Auras: 390416 - -Unknown-, 358419 - -Unknown-)
(@CGUID+51, 186684, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3667.666748046875, -490.59375, 82.2779693603515625, 4.942965030670166015, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Lava Phoenix (Area: -Unknown- - Difficulty: 0) (Auras: 369897 - -Unknown-)
(@CGUID+52, 186792, 2444, 13644, 13704, '0', '0', 0, 0, 1, 3758.864501953125, -402.680572509765625, 56.796630859375, 2.989429235458374023, 7200, 10, 0, 86626, 0, 1, 0, 0, 0, 45505), -- Qalashi Marauder (Area: -Unknown- - Difficulty: 0) (Auras: ) (possible waypoints or random movement)
(@CGUID+53, 186792, 2444, 13644, 13704, '0', '0', 0, 0, 1, 3515.5244140625, -369.923614501953125, 70.82623291015625, 4.471271038055419921, 7200, 10, 0, 86626, 0, 1, 0, 0, 0, 45505), -- Qalashi Marauder (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+54, 194772, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3608.112060546875, -343.541656494140625, 106.124755859375, 0.200039610266685485, 7200, 0, 0, 928140, 0, 0, 0, 0, 0, 45505), -- Wrathion (Area: -Unknown- - Difficulty: 0)
(@CGUID+55, 190766, 2444, 13644, 13704, '0', '0', 0, 0, 1, 3643.91748046875, -625.123291015625, 73.855133056640625, 5.969136238098144531, 7200, 0, 0, 86626, 0, 0, 0, 0, 0, 45505), -- Qalashi Ragetamer (Area: -Unknown- - Difficulty: 0) (Auras: 358419 - -Unknown-)
(@CGUID+56, 191672, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3496.26708984375, -494.94854736328125, 137.030303955078125, 2.38532257080078125, 7200, 10, 0, 37126, 0, 1, 0, 0, 0, 45505), -- Lava Tarantula (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+57, 194222, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3701.2890625, -462.024322509765625, 46.080657958984375, 4.914885997772216796, 7200, 0, 0, 198000, 6015, 0, 0, 0, 0, 45505), -- Qalashi Flamemuzzler (Area: -Unknown- - Difficulty: 0) (Auras: 358419 - -Unknown-)
(@CGUID+58, 191509, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3569.193115234375, -480.71832275390625, 192.968719482421875, 4.560201644897460937, 7200, 10, 0, 61876, 0, 1, 0, 0, 0, 45505), -- Blazing Dreadsquall (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+59, 186792, 2444, 13644, 13704, '0', '0', 0, 0, 1, 3763.694580078125, -531.307861328125, 43.04582977294921875, 1.034738898277282714, 7200, 0, 0, 86626, 0, 0, 0, 0, 0, 45505), -- Qalashi Marauder (Area: -Unknown- - Difficulty: 0) (Auras: 375804 - -Unknown-)
(@CGUID+60, 191446, 2444, 13644, 13704, '0', '0', 0, 0, 1, 3622.7587890625, -518.4305419921875, 53.05862808227539062, 2.625463485717773437, 7200, 0, 0, 86626, 0, 0, 0, 0, 0, 45505), -- Qalashi Scoundrel (Area: -Unknown- - Difficulty: 0) (Auras: )
(@CGUID+61, 192138, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3630.5009765625, -600.51104736328125, 84.68000030517578125, 1.483561992645263671, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Lava Pincer (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+62, 186792, 2444, 13644, 13704, '0', '0', 0, 0, 1, 3784.901123046875, -520.53302001953125, 2.571539878845214843, 3.123740196228027343, 7200, 0, 0, 86626, 0, 0, 0, 0, 0, 45505), -- Qalashi Marauder (Area: -Unknown- - Difficulty: 0)
(@CGUID+63, 191672, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3602.90625, -607.4459228515625, 92.9390716552734375, 2.015380620956420898, 7200, 10, 0, 37126, 0, 1, 0, 0, 0, 45505), -- Lava Tarantula (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+64, 193001, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3647.90087890625, -534.8260498046875, 46.48180007934570312, 4.717271804809570312, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Kindlet (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+65, 191672, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3458.16845703125, -506.341400146484375, 141.0301055908203125, 6.264501094818115234, 7200, 10, 0, 37126, 0, 1, 0, 0, 0, 45505), -- Lava Tarantula (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+66, 180705, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3788.412353515625, -537.92724609375, 41.98509597778320312, 3.47388315200805664, 7200, 10, 0, 46407, 0, 1, 0, 0, 0, 45505), -- Magmammoth Calf (Area: -Unknown- - Difficulty: 0) (Auras: ) (possible waypoints or random movement)
(@CGUID+67, 191509, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3694.85693359375, -652.6265869140625, 93.76219940185546875, 0.631879091262817382, 7200, 10, 0, 61876, 0, 1, 0, 0, 0, 45505), -- Blazing Dreadsquall (Area: -Unknown- - Difficulty: 0) (Auras: 391254 - -Unknown-) (possible waypoints or random movement)
(@CGUID+68, 191509, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3663.14794921875, -653.45745849609375, 84.2823944091796875, 2.931033134460449218, 7200, 10, 0, 61876, 0, 1, 0, 0, 0, 45505), -- Blazing Dreadsquall (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+69, 191509, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3677.27734375, -655.88494873046875, 109.8520355224609375, 1.983636736869812011, 7200, 10, 0, 61876, 0, 1, 0, 0, 0, 45505), -- Blazing Dreadsquall (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+70, 194693, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3529.6953125, -469.3038330078125, 72.97292327880859375, 0, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Dragon Target [DNT] (Area: -Unknown- - Difficulty: 0)
(@CGUID+71, 192138, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3489.015625, -505.880859375, 136.13031005859375, 3.882699251174926757, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Lava Pincer (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+72, 192138, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3487.759033203125, -493.13250732421875, 139.08343505859375, 0.994824051856994628, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Lava Pincer (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
-- (@CGUID+73, 121541, UNKNOWN, 13644, 13704, '0', '0', 0, 0, 0, 0.208347395062446594, 0, 1.873889684677124023, 0, 7200, 0, 0, 2993, 0, 0, 0, 0, 0, 45505), -- Ban-Lu (Area: -Unknown- - Difficulty: 0) (Auras: 46598 - Ride Vehicle Hardcoded) - !!! on transport - transport template not found !!!
(@CGUID+74, 192138, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3485.572265625, -481.196746826171875, 140.910614013671875, 0.643061757087707519, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Lava Pincer (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+75, 194693, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3535.0078125, -413.09722900390625, 72.57091522216796875, 0, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Dragon Target [DNT] (Area: -Unknown- - Difficulty: 0)
(@CGUID+76, 192138, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3591.0478515625, -318.04876708984375, 69.6324310302734375, 0.540999948978424072, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Lava Pincer (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+77, 190767, 2444, 13644, 13704, '0', '0', 0, 0, 1, 3497.7431640625, -295.243072509765625, 62.89833450317382812, 2.650155305862426757, 7200, 0, 0, 92814, 0, 0, 0, 0, 0, 45505), -- Qalashi Metalshaper (Area: -Unknown- - Difficulty: 0) (Auras: 369596 - -Unknown-)
(@CGUID+78, 192138, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3499.25048828125, -346.901763916015625, 72.941192626953125, 2.38385319709777832, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Lava Pincer (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+79, 193923, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3561.8056640625, -268.821197509765625, 48.94141387939453125, 1.202330350875854492, 7200, 0, 0, 77345, 0, 0, 0, 0, 0, 45505), -- Mature Obsidian Hornswog (Area: -Unknown- - Difficulty: 0)
(@CGUID+80, 190767, 2444, 13644, 13704, '0', '0', 0, 0, 1, 3491.835205078125, -291.041656494140625, 62.72401809692382812, 5.665018558502197265, 7200, 0, 0, 92814, 0, 0, 0, 0, 0, 45505), -- Qalashi Metalshaper (Area: -Unknown- - Difficulty: 0) (Auras: 369596 - -Unknown-)
(@CGUID+81, 190766, 2444, 13644, 13704, '0', '0', 0, 0, 1, 3537.772705078125, -257.973968505859375, 64.42555999755859375, 1.026351332664489746, 7200, 0, 0, 86626, 0, 0, 0, 0, 0, 45505), -- Qalashi Ragetamer (Area: -Unknown- - Difficulty: 0)
(@CGUID+82, 193923, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3599.548583984375, -253.256942749023437, 56.89670944213867187, 1.664066076278686523, 7200, 0, 0, 77345, 0, 0, 0, 0, 0, 45505), -- Mature Obsidian Hornswog (Area: -Unknown- - Difficulty: 0) (Auras: 391254 - -Unknown-)
(@CGUID+83, 186767, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3595.360107421875, -417.27801513671875, 117.1829986572265625, 1.795920729637145996, 7200, 0, 0, 185628, 0, 0, 0, 0, 0, 45505), -- Majordomo Selistra (Area: -Unknown- - Difficulty: 0) (Auras: )
(@CGUID+84, 194772, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3564.7900390625, -409.1090087890625, 124.272003173828125, 1.019327163696289062, 7200, 0, 0, 928140, 0, 0, 0, 0, 0, 45505), -- Wrathion (Area: -Unknown- - Difficulty: 0) (Auras: )
(@CGUID+85, 191637, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3505.874267578125, -278.0069580078125, 124.0818862915039062, 1.346589088439941406, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Lava Phoenix (Area: -Unknown- - Difficulty: 0) (Auras: 369897 - -Unknown-)
(@CGUID+86, 192138, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3549.497314453125, -293.755615234375, 64.7631988525390625, 2.849928855895996093, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Lava Pincer (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+87, 191509, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3542.38037109375, -250.045181274414062, 151.778961181640625, 4.057164669036865234, 7200, 10, 0, 61876, 0, 1, 0, 0, 0, 45505), -- Blazing Dreadsquall (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+88, 191446, 2444, 13644, 13704, '0', '0', 0, 0, 1, 3539.424560546875, -483.135406494140625, 63.95479202270507812, 4.526741981506347656, 7200, 0, 0, 86626, 0, 0, 0, 0, 0, 45505), -- Qalashi Scoundrel (Area: -Unknown- - Difficulty: 0) (Auras: )
(@CGUID+89, 193923, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3582.579833984375, -234.84375, 50.68354415893554687, 4.334140777587890625, 7200, 0, 0, 77345, 0, 0, 0, 0, 0, 45505), -- Mature Obsidian Hornswog (Area: -Unknown- - Difficulty: 0)
(@CGUID+90, 193925, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3612.387451171875, -259.821990966796875, 58.31789779663085937, 3.098468780517578125, 7200, 10, 0, 21657, 0, 1, 0, 0, 0, 45505), -- Obsidian Swoglet (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+91, 193925, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3570.11328125, -254.712539672851562, 48.85555267333984375, 4.3625335693359375, 7200, 10, 0, 21657, 0, 1, 0, 0, 0, 45505), -- Obsidian Swoglet (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+92, 193001, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3612.1611328125, -250.886932373046875, 60.01981735229492187, 1.277468204498291015, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Kindlet (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+93, 190766, 2444, 13644, 13704, '0', '0', 0, 0, 1, 3610.9140625, -445.986114501953125, 63.28089141845703125, 3.083961725234985351, 7200, 0, 0, 86626, 0, 0, 0, 0, 0, 45505), -- Qalashi Ragetamer (Area: -Unknown- - Difficulty: 0) (Auras: )
(@CGUID+94, 193001, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3620.6640625, -473.376739501953125, 59.3001708984375, 5.818570137023925781, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Kindlet (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+95, 191611, 2444, 13644, 13704, '0', '0', 0, 0, 1, 3622.743896484375, -465.4757080078125, 58.7818603515625, 3.594662427902221679, 7200, 10, 0, 470256, 0, 1, 0, 0, 0, 45505), -- Dragonhunter Igordan (Area: -Unknown- - Difficulty: 0) (Auras: 369262 - -Unknown-) (possible waypoints or random movement)
-- (@CGUID+96, 121541, UNKNOWN, 13644, 13704, '0', '0', 0, 0, 0, 0.208347395062446594, 0, 1.873889684677124023, 0, 7200, 0, 0, 2993, 0, 0, 0, 0, 0, 45505), -- Ban-Lu (Area: -Unknown- - Difficulty: 0) (Auras: 46598 - Ride Vehicle Hardcoded) - !!! on transport - transport template not found !!!
(@CGUID+97, 190766, 2444, 13644, 13704, '0', '0', 0, 0, 1, 3479.243896484375, -251.498260498046875, 46.46277618408203125, 2.02091526985168457, 7200, 0, 0, 86626, 0, 0, 0, 0, 0, 45505), -- Qalashi Ragetamer (Area: -Unknown- - Difficulty: 0)
-- (@CGUID+98, 121541, UNKNOWN, 13644, 13704, '0', '0', 0, 0, 0, 0.208347395062446594, 0, 1.873889684677124023, 0, 7200, 10, 0, 2993, 0, 1, 0, 0, 0, 45505), -- Ban-Lu (Area: -Unknown- - Difficulty: 0) (Auras: 46598 - Ride Vehicle Hardcoded) - !!! on transport - transport template not found !!! (possible waypoints or random movement)
(@CGUID+99, 193926, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3655.09814453125, -212.23785400390625, 100.2227249145507812, 3.371479272842407226, 7200, 0, 0, 247504, 0, 0, 0, 0, 0, 45505), -- Elder Obsidian Hornswog (Area: -Unknown- - Difficulty: 0)
(@CGUID+100, 193923, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3644.592041015625, -208.435760498046875, 97.59088134765625, 4.261384963989257812, 7200, 0, 0, 77345, 0, 0, 0, 0, 0, 45505), -- Mature Obsidian Hornswog (Area: -Unknown- - Difficulty: 0)
(@CGUID+101, 192134, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3566.6669921875, -235.416015625, 47.32179641723632812, 0.622657060623168945, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Lava Snail (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+102, 192134, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3628.695068359375, -229.411605834960937, 86.3407440185546875, 4.159583091735839843, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Lava Snail (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+103, 194693, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3505.07470703125, -330.895843505859375, 73.3627471923828125, 0, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Dragon Target [DNT] (Area: -Unknown- - Difficulty: 0)
(@CGUID+104, 191637, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3475.237060546875, -227.638885498046875, 79.85549163818359375, 2.883334159851074218, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Lava Phoenix (Area: -Unknown- - Difficulty: 0) (Auras: 369897 - -Unknown-)
(@CGUID+105, 190771, 2444, 13644, 13704, '0', '0', 0, 0, 1, 3477.131103515625, -210.850692749023437, 38.07489776611328125, 4.949325084686279296, 7200, 0, 0, 55688, 0, 0, 0, 0, 0, 45505), -- Injured Ruby Culler (Area: -Unknown- - Difficulty: 0) (Auras: )
(@CGUID+106, 186697, 2444, 13644, 13704, '0', '0', 0, 0, 1, 3477.2109375, -215.526046752929687, 40.02930450439453125, 4.679757595062255859, 7200, 0, 0, 55688, 0, 0, 0, 0, 0, 45505), -- Ruby Culler (Area: -Unknown- - Difficulty: 0)
(@CGUID+107, 191637, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3771.616455078125, -371.640625, 122.41259765625, 5.913076400756835937, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Lava Phoenix (Area: -Unknown- - Difficulty: 0) (Auras: 369897 - -Unknown-)
(@CGUID+108, 186777, 2444, 13644, 13704, '0', '0', 0, 0, 1, 3806.919921875, -366.398529052734375, 60.0198822021484375, 4.463551521301269531, 7200, 0, 0, 210376, 0, 0, 0, 0, 0, 45505), -- Meatgrinder Sotok (Area: -Unknown- - Difficulty: 0)
(@CGUID+109, 192134, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3656.46044921875, -220.719284057617187, 99.96160888671875, 6.254239559173583984, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Lava Snail (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+110, 193923, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3603.564453125, -156.97265625, 96.90555572509765625, 3.435590267181396484, 7200, 0, 0, 77345, 0, 0, 0, 0, 0, 45505), -- Mature Obsidian Hornswog (Area: -Unknown- - Difficulty: 0)
(@CGUID+111, 192134, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3653.575927734375, -197.174148559570312, 102.3109588623046875, 2.613236904144287109, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Lava Snail (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+112, 193925, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3653.294189453125, -197.314239501953125, 102.314422607421875, 3.466069936752319335, 7200, 0, 0, 21657, 0, 0, 0, 0, 0, 45505), -- Obsidian Swoglet (Area: -Unknown- - Difficulty: 0)
(@CGUID+113, 192138, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3503.163818359375, -570.9031982421875, 74.953887939453125, 1.960538148880004882, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Lava Pincer (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+114, 186582, 2444, 13644, 13704, '0', '0', 0, 0, 1, 3539.837646484375, -636.97393798828125, 117.2486190795898437, 4.372395038604736328, 7200, 0, 0, 61876, 0, 0, 0, 0, 0, 45505), -- Ruby Warden (Area: -Unknown- - Difficulty: 0)
(@CGUID+115, 195672, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3519.164306640625, -628.63543701171875, 82.42303466796875, 3.079002857208251953, 7200, 0, 0, 86626, 0, 0, 0, 0, 0, 45505), -- Qalashi Scoundrel (Area: -Unknown- - Difficulty: 0)
(@CGUID+116, 186582, 2444, 13644, 13704, '0', '0', 0, 0, 1, 3493.200439453125, -626.10589599609375, 79.2444000244140625, 2.488896131515502929, 7200, 0, 0, 61876, 0, 0, 0, 0, 0, 45505), -- Ruby Warden (Area: -Unknown- - Difficulty: 0)
(@CGUID+117, 186684, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3725.10498046875, -624.2742919921875, 38.01509857177734375, 1.650642633438110351, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Lava Phoenix (Area: -Unknown- - Difficulty: 0) (Auras: 369897 - -Unknown-)
(@CGUID+118, 186684, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3791.126708984375, -489.739593505859375, 46.35873031616210937, 4.619627952575683593, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Lava Phoenix (Area: -Unknown- - Difficulty: 0) (Auras: 369897 - -Unknown-)
(@CGUID+119, 193001, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3652.598388671875, -617.90667724609375, 49.95966339111328125, 4.538438796997070312, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Kindlet (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+120, 186684, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3731.26220703125, -625.82464599609375, 55.78519821166992187, 4.942965030670166015, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Lava Phoenix (Area: -Unknown- - Difficulty: 0) (Auras: 369897 - -Unknown-)
(@CGUID+121, 191446, 2444, 13644, 13704, '0', '0', 0, 0, 1, 3790.0166015625, -498.744781494140625, 43.75803375244140625, 2.82337045669555664, 7200, 0, 0, 86626, 0, 0, 0, 0, 0, 45505), -- Qalashi Scoundrel (Area: -Unknown- - Difficulty: 0) (Auras: )
(@CGUID+122, 180705, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3694.757080078125, -640.87591552734375, 33.28435516357421875, 0.289445281028747558, 7200, 10, 0, 46407, 0, 1, 0, 0, 0, 45505), -- Magmammoth Calf (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+123, 191903, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3619.673583984375, -685.09552001953125, 35.48468780517578125, 0.140878558158874511, 7200, 0, 0, 247504, 0, 0, 0, 0, 0, 45505), -- Magmammoth Bull (Area: -Unknown- - Difficulty: 0) (Auras: 375948 - -Unknown-)
(@CGUID+124, 180705, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3762.785888671875, -618.10919189453125, 40.87220001220703125, 5.360579490661621093, 7200, 10, 0, 46407, 0, 1, 0, 0, 0, 45505), -- Magmammoth Calf (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+125, 190766, 2444, 13644, 13704, '0', '0', 0, 0, 1, 3726.9384765625, -640.1492919921875, 34.774322509765625, 4.982160568237304687, 7200, 0, 0, 86626, 0, 0, 0, 0, 0, 45505), -- Qalashi Ragetamer (Area: -Unknown- - Difficulty: 0)
(@CGUID+126, 192138, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3600.03466796875, -631.11273193359375, 90.69281005859375, 1.552859902381896972, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Lava Pincer (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+127, 190766, 2444, 13644, 13704, '0', '0', 0, 0, 1, 3647.361083984375, -677.1961669921875, 37.7931671142578125, 3.728502273559570312, 7200, 0, 0, 86626, 0, 0, 0, 0, 0, 45505), -- Qalashi Ragetamer (Area: -Unknown- - Difficulty: 0)
(@CGUID+128, 186684, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3793.989501953125, -517.18402099609375, 43.92433929443359375, 2.93472146987915039, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Lava Phoenix (Area: -Unknown- - Difficulty: 0) (Auras: 369897 - -Unknown-)
(@CGUID+129, 192138, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3625.93701171875, -634.0987548828125, 80.61583709716796875, 4.14224863052368164, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Lava Pincer (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+130, 193026, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3694.904296875, -622.241943359375, 36.24900436401367187, 1.25170302391052246, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Emberling (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+131, 180705, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3671.26904296875, -663.31768798828125, 38.02172470092773437, 1.196981191635131835, 7200, 0, 0, 46407, 0, 0, 0, 0, 0, 45505), -- Magmammoth Calf (Area: -Unknown- - Difficulty: 0)
(@CGUID+132, 186573, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3699.786865234375, -610.66839599609375, 35.11426162719726562, 1.639133572578430175, 7200, 0, 0, 15469, 0, 0, 0, 0, 0, 45505), -- Restless Lava (Area: -Unknown- - Difficulty: 0) (Auras: 370034 - -Unknown-, 375960 - -Unknown-)
(@CGUID+133, 191901, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3802.783203125, -530.5919189453125, 141.1842498779296875, 5.573146343231201171, 7200, 0, 0, 264578, 0, 0, 0, 0, 0, 45505), -- Blazing Dreadsquall (Area: -Unknown- - Difficulty: 0) (Auras: 391254 - -Unknown-)
(@CGUID+134, 186573, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3701.81201171875, -612.958251953125, 35.17275238037109375, 2.011730670928955078, 7200, 0, 0, 15469, 0, 0, 0, 0, 0, 45505), -- Restless Lava (Area: -Unknown- - Difficulty: 0) (Auras: 370034 - -Unknown-, 375960 - -Unknown-)
(@CGUID+135, 186573, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3703.00439453125, -613.61541748046875, 35.281005859375, 2.043177127838134765, 7200, 0, 0, 15469, 0, 0, 0, 0, 0, 45505), -- Restless Lava (Area: -Unknown- - Difficulty: 0) (Auras: 370034 - -Unknown-, 375960 - -Unknown-)
(@CGUID+136, 193001, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3728.6435546875, -614.3387451171875, 36.98925018310546875, 2.885198593139648437, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Kindlet (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+137, 190766, 2444, 13644, 13704, '0', '0', 0, 0, 1, 3817.4765625, -492.307281494140625, 43.82408523559570312, 0.585083723068237304, 7200, 0, 0, 86626, 0, 0, 0, 0, 0, 45505), -- Qalashi Ragetamer (Area: -Unknown- - Difficulty: 0) (Auras: 358419 - -Unknown-)
(@CGUID+138, 194693, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3704.27685546875, -463.895843505859375, 45.27442169189453125, 0, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Dragon Target [DNT] (Area: -Unknown- - Difficulty: 0)
(@CGUID+139, 191903, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3731.24658203125, -672.4288330078125, 37.70778274536132812, 1.802183985710144042, 7200, 0, 0, 247504, 0, 0, 0, 0, 0, 45505), -- Magmammoth Bull (Area: -Unknown- - Difficulty: 0) (Auras: 375948 - -Unknown-)
(@CGUID+140, 190766, 2444, 13644, 13704, '0', '0', 0, 0, 1, 3695.556396484375, -683.05902099609375, 37.08954620361328125, 0.480066746473312377, 7200, 0, 0, 86626, 0, 0, 0, 0, 0, 45505), -- Qalashi Ragetamer (Area: -Unknown- - Difficulty: 0)
(@CGUID+141, 191637, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3809.9921875, -475.00347900390625, 125.1110076904296875, 0.934529840946197509, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Lava Phoenix (Area: -Unknown- - Difficulty: 0) (Auras: 369897 - -Unknown-)
(@CGUID+142, 191637, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3808.75341796875, -436.989593505859375, 60.8887939453125, 2.381785869598388671, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Lava Phoenix (Area: -Unknown- - Difficulty: 0) (Auras: 369897 - -Unknown-)
(@CGUID+143, 191637, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3801.61376953125, -439.15625, 107.704437255859375, 2.410585880279541015, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Lava Phoenix (Area: -Unknown- - Difficulty: 0) (Auras: 369897 - -Unknown-)
(@CGUID+144, 186682, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3836.9677734375, -560.77142333984375, 61.87829971313476562, 3.292608261108398437, 7200, 0, 0, 46407, 0, 0, 0, 0, 0, 45505), -- Raging Tremors (Area: -Unknown- - Difficulty: 0)
(@CGUID+145, 180705, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3816.6416015625, -620.52716064453125, 34.34061431884765625, 4.795114517211914062, 7200, 10, 0, 46407, 0, 1, 0, 0, 0, 45505), -- Magmammoth Calf (Area: -Unknown- - Difficulty: 0) (Auras: 391254 - -Unknown-) (possible waypoints or random movement)
(@CGUID+146, 191901, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3857.247802734375, -516.26922607421875, 126.98663330078125, 0.69341820478439331, 7200, 0, 0, 264578, 0, 0, 0, 0, 0, 45505), -- Blazing Dreadsquall (Area: -Unknown- - Difficulty: 0)
(@CGUID+147, 193001, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3808.28857421875, -523.52655029296875, 43.47267532348632812, 4.099465847015380859, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Kindlet (Area: -Unknown- - Difficulty: 0)
(@CGUID+148, 193026, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3809.49609375, -484.347564697265625, 44.44350051879882812, 1.212939262390136718, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Emberling (Area: -Unknown- - Difficulty: 0)
(@CGUID+149, 191637, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3809.783935546875, -478.48944091796875, 150.9528350830078125, 1.32406318187713623, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Lava Phoenix (Area: -Unknown- - Difficulty: 0) (Auras: 369897 - -Unknown-)
(@CGUID+150, 190766, 2444, 13644, 13704, '0', '0', 0, 0, 1, 3762.54345703125, -669.43231201171875, 37.01374435424804687, 3.354351758956909179, 7200, 0, 0, 86626, 0, 0, 0, 0, 0, 45505), -- Qalashi Ragetamer (Area: -Unknown- - Difficulty: 0)
(@CGUID+151, 191637, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3805.884521484375, -560.7899169921875, 144.3847503662109375, 4.439650535583496093, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Lava Phoenix (Area: -Unknown- - Difficulty: 0) (Auras: 369897 - -Unknown-)
(@CGUID+152, 194693, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3728.09033203125, -573.42706298828125, 47.0456390380859375, 0, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Dragon Target [DNT] (Area: -Unknown- - Difficulty: 0)
(@CGUID+153, 191637, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3834.28125, -473.15972900390625, 135.922149658203125, 0.956892967224121093, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Lava Phoenix (Area: -Unknown- - Difficulty: 0) (Auras: 369897 - -Unknown-)
(@CGUID+154, 191903, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3819.231689453125, -651.4757080078125, 33.10630035400390625, 2.930966377258300781, 7200, 0, 0, 247504, 0, 0, 0, 0, 0, 45505), -- Magmammoth Bull (Area: -Unknown- - Difficulty: 0) (Auras: 375948 - -Unknown-)
(@CGUID+155, 191637, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3832.489501953125, -522.23956298828125, 145.00860595703125, 0, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Lava Phoenix (Area: -Unknown- - Difficulty: 0) (Auras: 369897 - -Unknown-)
(@CGUID+156, 186570, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3817.1650390625, -483.50347900390625, 43.4044647216796875, 5.207401275634765625, 7200, 0, 0, 37126, 0, 0, 0, 0, 0, 45505), -- Lava Elemental (Area: -Unknown- - Difficulty: 0) (Auras: 370034 - -Unknown-, 364588 - -Unknown-)
(@CGUID+157, 191637, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3827.335205078125, -472.868072509765625, 142.858123779296875, 2.049858570098876953, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Lava Phoenix (Area: -Unknown- - Difficulty: 0) (Auras: 369897 - -Unknown-)
(@CGUID+158, 190564, 2444, 13644, 13704, '0', '0', 0, 0, 1, 3811.327392578125, -539.5069580078125, 46.01338577270507812, 2.675950527191162109, 7200, 0, 0, 1322890, 0, 0, 0, 0, 0, 45505), -- Right (Area: -Unknown- - Difficulty: 0) (Auras: 279802 - -Unknown-)
(@CGUID+159, 186684, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3870.93310546875, -527.6788330078125, 91.45590972900390625, 6.1971588134765625, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Lava Phoenix (Area: -Unknown- - Difficulty: 0) (Auras: 369897 - -Unknown-)
(@CGUID+160, 186570, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3826.296142578125, -497.404510498046875, 43.222869873046875, 1.967713356018066406, 7200, 0, 0, 37126, 0, 0, 0, 0, 0, 45505), -- Lava Elemental (Area: -Unknown- - Difficulty: 0) (Auras: 370034 - -Unknown-, 364588 - -Unknown-)
(@CGUID+161, 190766, 2444, 13644, 13704, '0', '0', 0, 0, 1, 3792.16845703125, -660.45831298828125, 37.21382904052734375, 0.320470571517944335, 7200, 0, 0, 86626, 0, 0, 0, 0, 0, 45505), -- Qalashi Ragetamer (Area: -Unknown- - Difficulty: 0)
(@CGUID+162, 192138, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3809.72509765625, -426.01763916015625, 57.8248291015625, 5.651347160339355468, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Lava Pincer (Area: -Unknown- - Difficulty: 0)
(@CGUID+163, 186573, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3705.537353515625, -648.5291748046875, 32.18992233276367187, 1.805353760719299316, 7200, 10, 0, 15469, 0, 1, 0, 0, 0, 45505), -- Restless Lava (Area: -Unknown- - Difficulty: 0) (Auras: 370034 - -Unknown-, 375960 - -Unknown-) (possible waypoints or random movement)
(@CGUID+164, 192135, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3807.29248046875, -441.008697509765625, 108.1595840454101562, 0.858347475528717041, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Phoenix Hatchling (Area: -Unknown- - Difficulty: 0)
(@CGUID+165, 186573, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3703.721435546875, -643.8741455078125, 33.47736358642578125, 1.729748249053955078, 7200, 10, 0, 15469, 0, 1, 0, 0, 0, 45505), -- Restless Lava (Area: -Unknown- - Difficulty: 0) (Auras: 370034 - -Unknown-, 375960 - -Unknown-) (possible waypoints or random movement)
(@CGUID+166, 191637, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3866.107666015625, -449.609375, 105.5424575805664062, 1.066354155540466308, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Lava Phoenix (Area: -Unknown- - Difficulty: 0) (Auras: 369897 - -Unknown-)
(@CGUID+167, 192138, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3811.883544921875, -471.12158203125, 124.1743545532226562, 5.27721261978149414, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Lava Pincer (Area: -Unknown- - Difficulty: 0)
(@CGUID+168, 186728, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3888.367431640625, -440.959869384765625, 67.43228912353515625, 0.450729936361312866, 7200, 0, 0, 1058312, 0, 0, 0, 0, 0, 45505), -- Magmammoth Bull (Area: -Unknown- - Difficulty: 0)
(@CGUID+169, 186684, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3815.643798828125, -630.44512939453125, 100.7170333862304687, 2.178494930267333984, 7200, 10, 0, 30938, 0, 1, 0, 0, 0, 45505), -- Lava Phoenix (Area: -Unknown- - Difficulty: 0) (Auras: 369897 - -Unknown-) (possible waypoints or random movement)
(@CGUID+170, 186683, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3856.017333984375, -452.8701171875, 60.83687973022460937, 0.487660467624664306, 7200, 10, 0, 15469, 0, 1, 0, 0, 0, 45505), -- Restless Rocks (Area: -Unknown- - Difficulty: 0) (Auras: 375960 - -Unknown-) (possible waypoints or random movement)
(@CGUID+171, 192135, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3804.796875, -557.7274169921875, 145.0522003173828125, 4.036675930023193359, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Phoenix Hatchling (Area: -Unknown- - Difficulty: 0)
(@CGUID+172, 186573, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3701.818603515625, -628.38238525390625, 34.378509521484375, 1.757464289665222167, 7200, 10, 0, 15469, 0, 1, 0, 0, 0, 45505), -- Restless Lava (Area: -Unknown- - Difficulty: 0) (Auras: 370034 - -Unknown-, 375960 - -Unknown-) (possible waypoints or random movement)
(@CGUID+173, 193001, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3845.8330078125, -445.833984375, 62.00406265258789062, 4.697509288787841796, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Kindlet (Area: -Unknown- - Difficulty: 0)
(@CGUID+174, 186573, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3740.781494140625, -636.3271484375, 34.80295562744140625, 2.198840618133544921, 7200, 10, 0, 15469, 0, 1, 0, 0, 0, 45505), -- Restless Lava (Area: -Unknown- - Difficulty: 0) (Auras: 370034 - -Unknown-, 375960 - -Unknown-) (possible waypoints or random movement)
(@CGUID+175, 186573, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3743.126220703125, -637.6534423828125, 34.79880142211914062, 2.773787498474121093, 7200, 10, 0, 15469, 0, 1, 0, 0, 0, 45505), -- Restless Lava (Area: -Unknown- - Difficulty: 0) (Auras: 370034 - -Unknown-, 375960 - -Unknown-) (possible waypoints or random movement)
(@CGUID+176, 192138, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3795.591552734375, -380.902801513671875, 57.00307464599609375, 0.609956860542297363, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Lava Pincer (Area: -Unknown- - Difficulty: 0)
(@CGUID+177, 186728, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3906.979248046875, -562.47052001953125, 77.99356842041015625, 4.113388538360595703, 7200, 0, 0, 1058312, 0, 0, 0, 0, 0, 45505), -- Magmammoth Bull (Area: -Unknown- - Difficulty: 0) (Auras: 375948 - -Unknown-)
(@CGUID+178, 192134, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3867.171630859375, -434.4495849609375, 64.96778106689453125, 0.314458191394805908, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Lava Snail (Area: -Unknown- - Difficulty: 0)
(@CGUID+179, 186573, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3749.090087890625, -621.871826171875, 36.09075546264648437, 1.272225618362426757, 7200, 10, 0, 15469, 0, 1, 0, 0, 0, 45505), -- Restless Lava (Area: -Unknown- - Difficulty: 0) (Auras: 370034 - -Unknown-, 375960 - -Unknown-) (possible waypoints or random movement)
(@CGUID+180, 192135, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3860.6796875, -538.38543701171875, 79.33847808837890625, 0, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Phoenix Hatchling (Area: -Unknown- - Difficulty: 0)
(@CGUID+181, 191899, 2444, 13644, 13704, '0', '0', 0, 0, 1, 3916.139892578125, -486.417144775390625, 73.27605438232421875, 1.379645466804504394, 7200, 0, 0, 370409, 0, 0, 0, 0, 0, 45505), -- Qalashi Marauder (Area: -Unknown- - Difficulty: 0) (Auras: 375804 - -Unknown-)
(@CGUID+182, 192135, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3854.8779296875, -473.227447509765625, 115.5141220092773437, 3.957189798355102539, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Phoenix Hatchling (Area: -Unknown- - Difficulty: 0)
(@CGUID+183, 186683, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3872.142333984375, -447.875732421875, 63.30281829833984375, 0.384496897459030151, 7200, 10, 0, 15469, 0, 1, 0, 0, 0, 45505), -- Restless Rocks (Area: -Unknown- - Difficulty: 0) (Auras: 375960 - -Unknown-) (possible waypoints or random movement)
(@CGUID+184, 186683, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3871.148193359375, -448.3282470703125, 63.06206893920898437, 0.382319957017898559, 7200, 10, 0, 15469, 0, 1, 0, 0, 0, 45505), -- Restless Rocks (Area: -Unknown- - Difficulty: 0) (Auras: 375960 - -Unknown-) (possible waypoints or random movement)
(@CGUID+185, 192135, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3826.471435546875, -476.255218505859375, 142.7021942138671875, 2.647700786590576171, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Phoenix Hatchling (Area: -Unknown- - Difficulty: 0)
(@CGUID+186, 190563, 2444, 13644, 13704, '0', '0', 0, 0, 1, 3836.80126953125, -406.09027099609375, 57.97871017456054687, 3.636535882949829101, 7200, 0, 0, 1322890, 0, 0, 0, 0, 0, 45505), -- Left (Area: -Unknown- - Difficulty: 0) (Auras: 279802 - -Unknown-)
(@CGUID+187, 194693, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3811.70654296875, -489.411468505859375, 44.7160186767578125, 0, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Dragon Target [DNT] (Area: -Unknown- - Difficulty: 0)
(@CGUID+188, 192135, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3871.59375, -525.4930419921875, 91.42986297607421875, 5.948543071746826171, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Phoenix Hatchling (Area: -Unknown- - Difficulty: 0)
(@CGUID+189, 191637, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3923.169189453125, -479.529510498046875, 74.36600494384765625, 2.821416616439819335, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Lava Phoenix (Area: -Unknown- - Difficulty: 0) (Auras: 369897 - -Unknown-)
(@CGUID+190, 191898, 2444, 13644, 13704, '0', '0', 0, 0, 1, 3896.45751953125, -580.11456298828125, 78.66641998291015625, 1.827328443527221679, 7200, 0, 0, 370409, 0, 0, 0, 0, 0, 45505), -- Qalashi Ragetamer (Area: -Unknown- - Difficulty: 0)
(@CGUID+191, 192134, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3896.2802734375, -424.10546875, 72.86409759521484375, 1.10714876651763916, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Lava Snail (Area: -Unknown- - Difficulty: 0)
(@CGUID+192, 192135, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3850.323974609375, -540.493896484375, 134.814727783203125, 5.671937942504882812, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Phoenix Hatchling (Area: -Unknown- - Difficulty: 0)
(@CGUID+193, 186724, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3943.481689453125, -396.899322509765625, 85.66802978515625, 6.210420131683349609, 7200, 0, 0, 846648, 7196, 0, 0, 0, 0, 45505), -- Qalashi Flamemuzzler (Area: -Unknown- - Difficulty: 0)
(@CGUID+194, 186727, 2444, 13644, 13704, '0', '0', 0, 0, 1, 3952.22216796875, -463.728973388671875, 76.87442779541015625, 3.122063875198364257, 7200, 0, 0, 1058312, 0, 0, 0, 0, 0, 45505), -- Qalashi Rampager (Area: -Unknown- - Difficulty: 0)
(@CGUID+195, 186728, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3968.5, -404.65277099609375, 89.62152862548828125, 3.007966995239257812, 7200, 0, 0, 1058312, 0, 0, 0, 0, 0, 45505), -- Magmammoth Bull (Area: -Unknown- - Difficulty: 0) (Auras: 375948 - -Unknown-)
(@CGUID+196, 186682, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3911.776123046875, -329.751739501953125, 152.203155517578125, 1.31023263931274414, 7200, 0, 0, 46407, 0, 0, 0, 0, 0, 45505), -- Raging Tremors (Area: -Unknown- - Difficulty: 0)
(@CGUID+197, 193000, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3929.4423828125, -441.516326904296875, 75.74489593505859375, 6.243062019348144531, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Kindlet (Area: -Unknown- - Difficulty: 0)
(@CGUID+198, 191513, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3843.6767578125, -616.498779296875, 118.5308456420898437, 3.031155586242675781, 7200, 0, 0, 370409, 0, 0, 0, 0, 0, 45505), -- Captured Raven (Area: -Unknown- - Difficulty: 0) (Auras: 376065 - -Unknown-)
(@CGUID+199, 193026, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3928.218994140625, -425.06781005859375, 77.321044921875, 5.970763683319091796, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Emberling (Area: -Unknown- - Difficulty: 0)
(@CGUID+200, 192138, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3923.3740234375, -489.72991943359375, 74.14068603515625, 0.9822426438331604, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Lava Pincer (Area: -Unknown- - Difficulty: 0)
(@CGUID+201, 186777, 2444, 13644, 13704, '0', '0', 0, 0, 1, 3806.374267578125, -366.09375, 60.08023834228515625, 4.14318084716796875, 7200, 0, 0, 123752, 0, 0, 0, 0, 0, 45505), -- Meatgrinder Sotok (Area: -Unknown- - Difficulty: 0) (Auras: 392594 - -Unknown-)
(@CGUID+202, 192138, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3938.484130859375, -469.153564453125, 74.08968353271484375, 0.6416969895362854, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Lava Pincer (Area: -Unknown- - Difficulty: 0)
(@CGUID+203, 193001, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3944.359130859375, -415.965087890625, 82.72540283203125, 4.209322452545166015, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Kindlet (Area: -Unknown- - Difficulty: 0)
(@CGUID+204, 191898, 2444, 13644, 13704, '0', '0', 0, 0, 1, 3981.04248046875, -488.859375, 80.838623046875, 5.016844749450683593, 7200, 0, 0, 370409, 0, 0, 0, 0, 0, 45505), -- Qalashi Ragetamer (Area: -Unknown- - Difficulty: 0)
(@CGUID+205, 192135, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3936.717041015625, -487.67535400390625, 81.19842529296875, 2.54567885398864746, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Phoenix Hatchling (Area: -Unknown- - Difficulty: 0)
(@CGUID+206, 193001, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3941.088134765625, -370.771697998046875, 91.18010711669921875, 3.024141550064086914, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Kindlet (Area: -Unknown- - Difficulty: 0)
(@CGUID+207, 186682, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3906.671875, -288.7257080078125, 138.6894378662109375, 0.436858564615249633, 7200, 0, 0, 46407, 0, 0, 0, 0, 0, 45505), -- Raging Tremors (Area: -Unknown- - Difficulty: 0)
(@CGUID+208, 193923, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3890.850830078125, -272.227447509765625, 163.8975830078125, 0, 7200, 0, 0, 77345, 0, 0, 0, 0, 0, 45505), -- Mature Obsidian Hornswog (Area: -Unknown- - Difficulty: 0)
(@CGUID+209, 191898, 2444, 13644, 13704, '0', '0', 0, 0, 1, 4002.609375, -458.24456787109375, 80.21704864501953125, 1.384220242500305175, 7200, 0, 0, 370409, 0, 0, 0, 0, 0, 45505), -- Qalashi Ragetamer (Area: -Unknown- - Difficulty: 0) (Auras: 366375 - -Unknown-)
(@CGUID+210, 193918, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3937.5, -300, 144.504913330078125, 4.712388992309570312, 7200, 0, 0, 46407, 0, 0, 0, 0, 0, 45505), -- Obsidian Hornswog (Area: -Unknown- - Difficulty: 0)
(@CGUID+211, 186724, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3954.013916015625, -535.1649169921875, 80.50244140625, 0.697208106517791748, 7200, 0, 0, 846648, 7196, 0, 0, 0, 0, 45505), -- Qalashi Flamemuzzler (Area: -Unknown- - Difficulty: 0) (Auras: 364588 - -Unknown-, 391245 - -Unknown-)
(@CGUID+212, 193918, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3910.16162109375, -275.220001220703125, 158.1234283447265625, 5.76580047607421875, 7200, 0, 0, 46407, 0, 0, 0, 0, 0, 45505), -- Obsidian Hornswog (Area: -Unknown- - Difficulty: 0)
(@CGUID+213, 192134, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3961.15478515625, -359.439727783203125, 92.0838623046875, 0.687859952449798583, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Lava Snail (Area: -Unknown- - Difficulty: 0)
(@CGUID+214, 186684, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3889.48583984375, -562.47247314453125, 111.7817306518554687, 1.67140364646911621, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Lava Phoenix (Area: -Unknown- - Difficulty: 0) (Auras: 369897 - -Unknown-)
(@CGUID+215, 186573, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3973.47705078125, -424.044219970703125, 83.67711639404296875, 4.060683250427246093, 7200, 0, 0, 15469, 0, 0, 0, 0, 0, 45505), -- Restless Lava (Area: -Unknown- - Difficulty: 0) (Auras: 370034 - -Unknown-, 375960 - -Unknown-)
(@CGUID+216, 186573, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3972.86181640625, -424.80419921875, 83.57468414306640625, 4.045432090759277343, 7200, 0, 0, 15469, 0, 0, 0, 0, 0, 45505), -- Restless Lava (Area: -Unknown- - Difficulty: 0) (Auras: 370034 - -Unknown-, 375960 - -Unknown-)
(@CGUID+217, 186573, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3970.90625, -428.346282958984375, 83.12862396240234375, 3.883480072021484375, 7200, 0, 0, 15469, 0, 0, 0, 0, 0, 45505), -- Restless Lava (Area: -Unknown- - Difficulty: 0) (Auras: 370034 - -Unknown-, 375960 - -Unknown-)
(@CGUID+218, 186684, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3872.970458984375, -523.58331298828125, 91.6527099609375, 5.419068336486816406, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Lava Phoenix (Area: -Unknown- - Difficulty: 0) (Auras: 369897 - -Unknown-)
(@CGUID+219, 191672, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3558.205322265625, -658.72430419921875, 108.2770233154296875, 3.94356393814086914, 7200, 0, 0, 37126, 0, 0, 0, 0, 0, 45505), -- Lava Tarantula (Area: -Unknown- - Difficulty: 0) (Auras: 391254 - -Unknown-)
(@CGUID+220, 191446, 2444, 13644, 13704, '0', '0', 0, 0, 1, 3622.7587890625, -518.4305419921875, 53.05862808227539062, 2.625463485717773437, 7200, 0, 0, 86626, 0, 0, 0, 0, 0, 45505), -- Qalashi Scoundrel (Area: -Unknown- - Difficulty: 0) (Auras: )
(@CGUID+221, 186792, 2444, 13644, 13704, '0', '0', 0, 0, 1, 3746.092041015625, -449.3194580078125, 55.29071426391601562, 3.288785457611083984, 7200, 0, 0, 86626, 0, 0, 0, 0, 0, 45505), -- Qalashi Marauder (Area: -Unknown- - Difficulty: 0) (Auras: 375804 - -Unknown-)
(@CGUID+222, 194772, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3608.112060546875, -343.541656494140625, 106.2080917358398437, 0.200039610266685485, 7200, 10, 0, 928140, 0, 1, 0, 0, 0, 45505), -- Wrathion (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+223, 191611, 2444, 13644, 13704, '0', '0', 0, 0, 1, 3622.743896484375, -465.4757080078125, 58.7818603515625, 3.594662427902221679, 7200, 0, 0, 297004, 0, 0, 0, 0, 0, 45505), -- Dragonhunter Igordan (Area: -Unknown- - Difficulty: 0) (Auras: 369262 - -Unknown-)
(@CGUID+224, 192138, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3458.427490234375, -252.325576782226562, 47.3913726806640625, 6.006511688232421875, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Lava Pincer (Area: -Unknown- - Difficulty: 0)
-- (@CGUID+225, 121541, UNKNOWN, 13644, 13704, '0', '0', 0, 0, 0, 0.208347395062446594, 0, 1.873889684677124023, 0, 7200, 0, 0, 2993, 0, 0, 0, 0, 0, 45505), -- Ban-Lu (Area: -Unknown- - Difficulty: 0) (Auras: 46598 - Ride Vehicle Hardcoded) - !!! on transport - transport template not found !!!
(@CGUID+226, 186697, 2444, 13644, 13704, '0', '0', 0, 0, 1, 3420.125, -223.611114501953125, 33.02083206176757812, 5.830825328826904296, 7200, 0, 0, 55688, 0, 0, 0, 0, 0, 45505), -- Ruby Culler (Area: -Unknown- - Difficulty: 0)
(@CGUID+227, 191628, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3448.138916015625, -244.088546752929687, 44.00495529174804687, 0.110913731157779693, 7200, 0, 0, 24750, 0, 0, 0, 0, 0, 45505), -- Lava Snail (Area: -Unknown- - Difficulty: 0)
(@CGUID+228, 191672, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3500.8173828125, -183.580169677734375, 19.577789306640625, 0.239208400249481201, 7200, 10, 0, 37126, 0, 1, 0, 0, 0, 45505), -- Lava Tarantula (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+229, 191624, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3375.97216796875, -328.961822509765625, 56.43693923950195312, 1.541023731231689453, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Tranquil Vorquin (Area: -Unknown- - Difficulty: 0)
(@CGUID+230, 192138, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3507.35498046875, -214.481719970703125, 32.326019287109375, 5.745615005493164062, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Lava Pincer (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+231, 191629, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3513.400634765625, -199.498794555664062, 20.13743209838867187, 0.409779399633407592, 7200, 10, 0, 9281, 0, 1, 0, 0, 0, 45505), -- Lava Slug (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+232, 190771, 2444, 13644, 13704, '0', '0', 0, 0, 1, 3416.157958984375, -220.631942749023437, 32.57490921020507812, 4.949325084686279296, 7200, 0, 0, 55688, 0, 0, 0, 0, 0, 45505), -- Injured Ruby Culler (Area: -Unknown- - Difficulty: 0) (Auras: )
(@CGUID+233, 192138, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3507.76416015625, -195.028945922851562, 19.45673179626464843, 0.505842626094818115, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Lava Pincer (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+234, 191628, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3507.150146484375, -193.079864501953125, 19.24396705627441406, 0, 7200, 0, 0, 24750, 0, 0, 0, 0, 0, 45505), -- Lava Snail (Area: -Unknown- - Difficulty: 0)
(@CGUID+235, 192138, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3423.1962890625, -235.109375, 38.15274429321289062, 2.70008087158203125, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Lava Pincer (Area: -Unknown- - Difficulty: 0)
(@CGUID+236, 192138, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3575.81787109375, -185.542648315429687, 59.21867752075195312, 0.90512239933013916, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Lava Pincer (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+237, 191629, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3419.717529296875, -233.966217041015625, 38.47535324096679687, 0.762917041778564453, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Lava Slug (Area: -Unknown- - Difficulty: 0)
(@CGUID+238, 192138, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3490.7177734375, -176.064682006835937, 19.48081588745117187, 5.85003662109375, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Lava Pincer (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+239, 192138, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3513.58154296875, -166.673324584960937, 32.878997802734375, 1.740158796310424804, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Lava Pincer (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+240, 192138, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3446.560546875, -201.508285522460937, 35.69898605346679687, 2.597916126251220703, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Lava Pincer (Area: -Unknown- - Difficulty: 0)
(@CGUID+241, 192104, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3417.07421875, -228.720306396484375, 34.92950820922851562, 1.733696341514587402, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Magma Slug (Area: -Unknown- - Difficulty: 0)
(@CGUID+242, 191629, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3409.375, -234.375, 35.15274429321289062, 4.247991561889648437, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Lava Slug (Area: -Unknown- - Difficulty: 0)
(@CGUID+243, 191628, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3461.02294921875, -177.038330078125, 30.12584686279296875, 2.965697526931762695, 7200, 10, 0, 24750, 0, 1, 0, 0, 0, 45505), -- Lava Snail (Area: -Unknown- - Difficulty: 0) (Auras: 391254 - -Unknown-) (possible waypoints or random movement)
(@CGUID+244, 191629, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3414.0625, -240.103515625, 37.27774429321289062, 3.968919754028320312, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Lava Slug (Area: -Unknown- - Difficulty: 0)
(@CGUID+245, 191629, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3439.178466796875, -192.930618286132812, 30.49113082885742187, 5.637279510498046875, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Lava Slug (Area: -Unknown- - Difficulty: 0)
(@CGUID+246, 191624, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3351.053955078125, -342.170135498046875, 58.19898605346679687, 4.063301563262939453, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Tranquil Vorquin (Area: -Unknown- - Difficulty: 0)
(@CGUID+247, 192138, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3503.343994140625, -182.022689819335937, 19.37409782409667968, 0.955638110637664794, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Lava Pincer (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+248, 191677, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3390.835205078125, -185.659957885742187, 22.61593437194824218, 5.49226236343383789, 7200, 10, 0, 46407, 0, 1, 0, 0, 0, 45505), -- Magmammoth Calf (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+249, 191637, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3382.358642578125, -182.73785400390625, 45.16472625732421875, 2.268236160278320312, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505); -- Lava Phoenix (Area: -Unknown- - Difficulty: 0) (Auras: 369897 - -Unknown-)

INSERT INTO `creature` (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnDifficulties`, `PhaseId`, `PhaseGroup`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `wander_distance`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`, `VerifiedBuild`) VALUES
(@CGUID+250, 192138, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3482.96435546875, -162.775543212890625, 30.60262870788574218, 2.388486862182617187, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Lava Pincer (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+251, 191637, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3364.421142578125, -199.59722900390625, 51.45389556884765625, 1.008056044578552246, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Lava Phoenix (Area: -Unknown- - Difficulty: 0) (Auras: 369897 - -Unknown-)
(@CGUID+252, 191944, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3569.12451171875, -92.688079833984375, 41.600616455078125, 1.034584879875183105, 7200, 0, 0, 37126, 0, 0, 0, 0, 0, 45505), -- Erupting Lasher (Area: -Unknown- - Difficulty: 0) (Auras: )
(@CGUID+253, 191944, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3570.59423828125, -93.0991592407226562, 41.4786834716796875, 2.261658906936645507, 7200, 0, 0, 37126, 0, 0, 0, 0, 0, 45505), -- Erupting Lasher (Area: -Unknown- - Difficulty: 0)
(@CGUID+254, 191945, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3572.314208984375, -94.1458358764648437, 41.36062240600585937, 3.740171194076538085, 7200, 0, 0, 55688, 0, 0, 0, 0, 0, 45505), -- Cracked Elemental (Area: -Unknown- - Difficulty: 0) (Auras: 159474 - Permanent Feign Death (NO Stun, Untrackable, Immune), 376838 - -Unknown-)
(@CGUID+255, 191944, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3578.61376953125, -97.7766952514648437, 41.58325958251953125, 0.322167664766311645, 7200, 0, 0, 37126, 0, 0, 0, 0, 0, 45505), -- Erupting Lasher (Area: -Unknown- - Difficulty: 0)
(@CGUID+256, 191628, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3396.35400390625, -200.666107177734375, 26.6722259521484375, 4.937752723693847656, 7200, 10, 0, 24750, 0, 1, 0, 0, 0, 45505), -- Lava Snail (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+257, 191945, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3513.12158203125, -77.8107681274414062, 32.07472610473632812, 3.740170955657958984, 7200, 0, 0, 55688, 0, 0, 0, 0, 0, 45505), -- Cracked Elemental (Area: -Unknown- - Difficulty: 0) (Auras: 159474 - Permanent Feign Death (NO Stun, Untrackable, Immune), 376838 - -Unknown-)
(@CGUID+258, 191624, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3330.06640625, -328.128997802734375, 49.24435806274414062, 2.574713706970214843, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Tranquil Vorquin (Area: -Unknown- - Difficulty: 0) (Auras: 391254 - -Unknown-)
(@CGUID+259, 191624, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3331.891357421875, -330.43841552734375, 50.16750717163085937, 2.731698989868164062, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Tranquil Vorquin (Area: -Unknown- - Difficulty: 0)
(@CGUID+260, 191945, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3502.6259765625, -72.4826431274414062, 29.99623680114746093, 1.978789448738098144, 7200, 0, 0, 55688, 0, 0, 0, 0, 0, 45505), -- Cracked Elemental (Area: -Unknown- - Difficulty: 0) (Auras: 159474 - Permanent Feign Death (NO Stun, Untrackable, Immune), 376838 - -Unknown-)
(@CGUID+261, 192104, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3366.70947265625, -193.001922607421875, 22.11357688903808593, 2.399181365966796875, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Magma Slug (Area: -Unknown- - Difficulty: 0)
(@CGUID+262, 192138, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3538.1513671875, -117.65234375, 46.01660919189453125, 3.22833108901977539, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Lava Pincer (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+263, 191809, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3456.974365234375, -111.0499267578125, 33.44471359252929687, 4.189859390258789062, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Tiny Butterfly (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+264, 191629, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3390.461669921875, -134.460433959960937, 16.15251731872558593, 1.323753714561462402, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Lava Slug (Area: -Unknown- - Difficulty: 0)
(@CGUID+265, 188297, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3518.671875, -60.6180572509765625, 35.26909637451171875, 0.058239072561264038, 7200, 0, 0, 185628, 0, 0, 0, 0, 0, 45505), -- Caretaker Ventraz (Area: -Unknown- - Difficulty: 0) (Auras: 376071 - -Unknown-)
(@CGUID+266, 191629, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3400.7265625, -133.329666137695312, 18.84804725646972656, 3.064269781112670898, 7200, 10, 0, 9281, 0, 1, 0, 0, 0, 45505), -- Lava Slug (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+267, 191946, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3552.1337890625, -76.8506927490234375, 41.66770172119140625, 1.326421499252319335, 7200, 0, 0, 92814, 0, 0, 0, 0, 0, 45505), -- Cracked Elemental (Area: -Unknown- - Difficulty: 0) (Auras: 159474 - Permanent Feign Death (NO Stun, Untrackable, Immune), 376838 - -Unknown-)
(@CGUID+268, 191629, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3403.28662109375, -123.984214782714843, 15.41266441345214843, 1.791705012321472167, 7200, 10, 0, 9281, 0, 1, 0, 0, 0, 45505), -- Lava Slug (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+269, 190093, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3524.62841796875, -59.8020820617675781, 35.4416961669921875, 0.12980140745639801, 7200, 0, 0, 55688, 0, 0, 0, 0, 0, 45505), -- Ruby Culler (Area: -Unknown- - Difficulty: 0) (Auras: 369109 - -Unknown-, 376252 - -Unknown-)
(@CGUID+270, 190771, 2444, 13644, 13704, '0', '0', 0, 0, 1, 3519.3525390625, -55.7934036254882812, 34.55934906005859375, 6.04840850830078125, 7200, 0, 0, 55688, 0, 0, 0, 0, 0, 45505), -- Injured Ruby Culler (Area: -Unknown- - Difficulty: 0) (Auras: )
(@CGUID+271, 189094, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3393.1845703125, -115.02099609375, 10.41111660003662109, 0.82646799087524414, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Magma Slug (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+272, 192047, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3297.407470703125, -212.77838134765625, 4.332524299621582031, 5.713608741760253906, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Scruffy Ottuk (Area: -Unknown- - Difficulty: 0)
(@CGUID+273, 191624, 2444, 13644, 0, '0', '0', 0, 0, 0, 3248.40966796875, -264.34027099609375, 41.22629547119140625, 5.366614818572998046, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Tranquil Vorquin (Area: 0 - Difficulty: 0)
(@CGUID+274, 191625, 2444, 13644, 0, '0', '0', 0, 0, 0, 3321.95849609375, -319.629302978515625, 46.32415008544921875, 2.345842838287353515, 7200, 0, 0, 15469, 0, 0, 0, 0, 0, 45505), -- Vorquin Foal (Area: 0 - Difficulty: 0)
(@CGUID+275, 192069, 2444, 13644, 0, '0', '0', 0, 0, 0, 3348.194580078125, -341.61285400390625, 57.68854522705078125, 2.529478788375854492, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Vorquin Runt (Area: 0 - Difficulty: 0)
(@CGUID+276, 191625, 2444, 13644, 0, '0', '0', 0, 0, 0, 3315.526611328125, -319.567657470703125, 45.83034133911132812, 2.356194496154785156, 7200, 0, 0, 15469, 0, 0, 0, 0, 0, 45505), -- Vorquin Foal (Area: 0 - Difficulty: 0)
(@CGUID+277, 189103, 2444, 13644, 0, '0', '0', 0, 0, 0, 3282.528564453125, -214.601715087890625, 4.861393928527832031, 4.955946922302246093, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Scruffy Ottuk (Area: 0 - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+278, 190771, 2444, 13644, 0, '0', '0', 0, 0, 1, 3416.157958984375, -220.631942749023437, 32.65824127197265625, 4.949325084686279296, 7200, 0, 0, 55688, 0, 0, 0, 0, 0, 45505), -- Injured Ruby Culler (Area: 0 - Difficulty: 0) (Auras: )
(@CGUID+279, 191944, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3555.361083984375, -64.8405990600585937, 42.87295150756835937, 3.027950286865234375, 7200, 0, 0, 37126, 0, 0, 0, 0, 0, 45505), -- Erupting Lasher (Area: -Unknown- - Difficulty: 0)
(@CGUID+280, 191946, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3537.853271484375, -44.1215286254882812, 37.84247589111328125, 5.524001121520996093, 7200, 0, 0, 92814, 0, 0, 0, 0, 0, 45505), -- Cracked Elemental (Area: -Unknown- - Difficulty: 0) (Auras: 159474 - Permanent Feign Death (NO Stun, Untrackable, Immune), 376838 - -Unknown-)
-- (@CGUID+281, 142668, UNKNOWN, 13644, 13704, '0', '0', 0, 0, 0, 0.100000001490116119, -0.20000000298023223, 0.200000002980232238, 0, 7200, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Merchant Maku (Area: -Unknown- - Difficulty: 0) (Auras: 122729 - Grand Expedition Yak) - !!! on transport - transport template not found !!!
-- (@CGUID+282, 142666, UNKNOWN, 13644, 13704, '0', '0', 0, 0, 0, 0.100000001490116119, 0.200000002980232238, 0.200000002980232238, 0, 7200, 0, 0, 158747, 10794, 0, 0, 0, 0, 45505), -- Collector Unta (Area: -Unknown- - Difficulty: 0) (Auras: 122729 - Grand Expedition Yak) - !!! on transport - transport template not found !!!
(@CGUID+283, 192136, 2444, 13644, 13704, '0', '0', 0, 0, 0, 3515.972412109375, -73.4636764526367187, 33.24833297729492187, 1.111515522003173828, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Flame Flick (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+284, 190771, 2444, 13644, 13704, '0', '0', 0, 0, 1, 3477.131103515625, -210.850692749023437, 38.15822982788085937, 4.949325084686279296, 7200, 0, 0, 55688, 0, 0, 0, 0, 0, 45505), -- Injured Ruby Culler (Area: -Unknown- - Difficulty: 0) (Auras: )
(@CGUID+285, 191944, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3640.990478515625, -122.534721374511718, 43.4329833984375, 0.424357682466506958, 7200, 0, 0, 37126, 0, 0, 0, 0, 0, 45505), -- Erupting Lasher (Area: -Unknown- - Difficulty: 0) (Auras: 376804 - -Unknown-)
(@CGUID+286, 191983, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3527.186279296875, -59.9170417785644531, 35.62487411499023437, 3.823904752731323242, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 370034 - -Unknown-)
(@CGUID+287, 193925, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3578.1796875, -116.892356872558593, 103.2764892578125, 2.845915794372558593, 7200, 0, 0, 21657, 0, 0, 0, 0, 0, 45505), -- Obsidian Swoglet (Area: -Unknown- - Difficulty: 0)
(@CGUID+288, 191983, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3528.0576171875, -58.60888671875, 35.83021163940429687, 4.30187845230102539, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 370034 - -Unknown-)
(@CGUID+289, 192138, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3578.09375, -93.4309616088867187, 40.80490875244140625, 2.979582786560058593, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Lava Pincer (Area: -Unknown- - Difficulty: 0)
(@CGUID+290, 191983, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3527.876220703125, -60.5442390441894531, 35.82437515258789062, 2.964106321334838867, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 370034 - -Unknown-)
(@CGUID+291, 191983, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3571.521484375, -86.3191986083984375, 41.057342529296875, 2.446338653564453125, 7200, 10, 0, 9281, 0, 1, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 370034 - -Unknown-, 375720 - -Unknown-) (possible waypoints or random movement)
(@CGUID+292, 191983, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3527.775146484375, -61.6134796142578125, 35.89879989624023437, 3.919187307357788085, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 370034 - -Unknown-)
(@CGUID+293, 191945, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3645.033935546875, -118.659721374511718, 43.16529083251953125, 2.963100194931030273, 7200, 0, 0, 55688, 0, 0, 0, 0, 0, 45505), -- Cracked Elemental (Area: -Unknown- - Difficulty: 0) (Auras: 159474 - Permanent Feign Death (NO Stun, Untrackable, Immune), 376838 - -Unknown-)
(@CGUID+294, 191983, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3528.0732421875, -60.0210075378417968, 35.85021209716796875, 3.359259605407714843, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 370034 - -Unknown-)
(@CGUID+295, 191983, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3572.200439453125, -91.44891357421875, 41.1316986083984375, 3.22323012351989746, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 370034 - -Unknown-, 375720 - -Unknown-)
(@CGUID+296, 191945, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3530.111083984375, -32.7222213745117187, 38.73343658447265625, 2.339847564697265625, 7200, 0, 0, 55688, 0, 0, 0, 0, 0, 45505), -- Cracked Elemental (Area: -Unknown- - Difficulty: 0) (Auras: 159474 - Permanent Feign Death (NO Stun, Untrackable, Immune), 376838 - -Unknown-)
(@CGUID+297, 193925, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3590.669677734375, -124.115867614746093, 99.69950103759765625, 3.080322265625, 7200, 10, 0, 21657, 0, 1, 0, 0, 0, 45505), -- Obsidian Swoglet (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+298, 192138, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3569.621826171875, -68.7915878295898437, 42.68311309814453125, 5.148927688598632812, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Lava Pincer (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+299, 191983, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3565.4296875, -65.4099197387695312, 43.1376800537109375, 5.251208782196044921, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 375720 - -Unknown-, 370034 - -Unknown-)
(@CGUID+300, 192138, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3587.14892578125, -107.938980102539062, 100.6804733276367187, 0.348937898874282836, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Lava Pincer (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+301, 191983, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3545.728759765625, -59.9099998474121093, 40.80868148803710937, 6.118401050567626953, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 375720 - -Unknown-, 370034 - -Unknown-)
(@CGUID+302, 191983, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3542.48291015625, -59.3885841369628906, 39.99216461181640625, 0.156266435980796813, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 375720 - -Unknown-, 370034 - -Unknown-)
(@CGUID+303, 191983, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3562.850341796875, -67.59674072265625, 42.97068405151367187, 6.130902290344238281, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 370034 - -Unknown-, 375720 - -Unknown-)
(@CGUID+304, 191983, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3544.9208984375, -55.8949508666992187, 40.47484588623046875, 0.478576838970184326, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 370034 - -Unknown-, 375720 - -Unknown-)
(@CGUID+305, 191517, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3559.048828125, -44.6959342956542968, 43.11959075927734375, 1.361051201820373535, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 370034 - -Unknown-)
(@CGUID+306, 191983, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3561.28857421875, -49.6527900695800781, 42.943756103515625, 4.26702737808227539, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 370034 - -Unknown-, 375720 - -Unknown-)
(@CGUID+307, 191983, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3566.064208984375, -48.7604179382324218, 41.9912567138671875, 1.866758227348327636, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 370034 - -Unknown-, 375720 - -Unknown-)
(@CGUID+308, 191983, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3566.87060546875, -51.3194465637207031, 41.8884735107421875, 2.378679752349853515, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 370034 - -Unknown-, 375720 - -Unknown-)
(@CGUID+309, 191983, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3576.483642578125, -54.0190963745117187, 40.84659576416015625, 4.284098625183105468, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 375720 - -Unknown-, 370034 - -Unknown-)
(@CGUID+310, 192138, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3516.716796875, -25.257913589477539, 36.5547943115234375, 2.631033182144165039, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Lava Pincer (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+311, 191983, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3576.715576171875, -57.3347663879394531, 40.9545745849609375, 4.373636245727539062, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 375720 - -Unknown-, 370034 - -Unknown-)
(@CGUID+312, 191517, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3580.044921875, -66.0996932983398437, 40.1265106201171875, 5.967906951904296875, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 370034 - -Unknown-)
(@CGUID+313, 191517, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3574.871826171875, -61.4957733154296875, 40.868560791015625, 2.534532070159912109, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 370034 - -Unknown-)
(@CGUID+314, 192138, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3618.89501953125, -113.228485107421875, 59.13144302368164062, 0.984850943088531494, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Lava Pincer (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+315, 193026, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3534.66259765625, -21.1742153167724609, 40.70412445068359375, 1.179055690765380859, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Emberling (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+316, 191983, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3568.740478515625, -42.3402786254882812, 41.70661544799804687, 3.070740938186645507, 7200, 10, 0, 9281, 0, 1, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 370034 - -Unknown-, 376749 - -Unknown-, 375720 - -Unknown-, 376754 - -Unknown-) (possible waypoints or random movement)
(@CGUID+317, 191944, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3656.643310546875, -100.359382629394531, 62.77669906616210937, 3.185031652450561523, 7200, 0, 0, 37126, 0, 0, 0, 0, 0, 45505), -- Erupting Lasher (Area: -Unknown- - Difficulty: 0) (Auras: 376861 - -Unknown-)
(@CGUID+318, 191517, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3563.368408203125, -36.3986015319824218, 42.653076171875, 4.063765525817871093, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 370034 - -Unknown-)
(@CGUID+319, 192138, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3577.513427734375, -39.8688926696777343, 40.91326904296875, 4.100490570068359375, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Lava Pincer (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+320, 191983, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3568.740478515625, -42.3402786254882812, 41.70661544799804687, 4.388228416442871093, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 370034 - -Unknown-, 375720 - -Unknown-)
(@CGUID+321, 191917, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3638.32275390625, -45.4020004272460937, 40.5372467041015625, 2.787331819534301757, 7200, 0, 0, 54450, 6015, 0, 0, 0, 0, 45505), -- Erupting Magma (Area: -Unknown- - Difficulty: 0)
(@CGUID+322, 192136, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3537.732177734375, 18.42153358459472656, 49.0424957275390625, 4.76810455322265625, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Flame Flick (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+323, 191983, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3613.3095703125, -75.6638641357421875, 42.49169158935546875, 3.01265883445739746, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 370034 - -Unknown-, 375720 - -Unknown-)
(@CGUID+324, 192138, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3558.94921875, -1.3076789379119873, 92.13529205322265625, 5.634156227111816406, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Lava Pincer (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+325, 191983, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3613.45263671875, -77.1200637817382812, 42.67376327514648437, 1.683055877685546875, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 370034 - -Unknown-, 375720 - -Unknown-)
(@CGUID+326, 191983, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3614.12451171875, -74.5874481201171875, 42.4552001953125, 2.210349082946777343, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 370034 - -Unknown-, 375720 - -Unknown-)
(@CGUID+327, 191983, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3613.6533203125, -78.7469253540039062, 42.60076904296875, 3.819167137145996093, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 370034 - -Unknown-, 375720 - -Unknown-)
(@CGUID+328, 192138, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3607.228271484375, -47.1949844360351562, 44.38657379150390625, 0.285410910844802856, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Lava Pincer (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+329, 191983, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3614.494140625, -76.0277023315429687, 42.61047744750976562, 2.055222511291503906, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 370034 - -Unknown-, 375720 - -Unknown-)
(@CGUID+330, 191517, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3619.14990234375, -87.3497238159179687, 42.41497421264648437, 2.178423881530761718, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 370034 - -Unknown-)
(@CGUID+331, 191983, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3615.950927734375, -70.0483932495117187, 42.6187286376953125, 3.275225400924682617, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 370034 - -Unknown-, 375720 - -Unknown-)
(@CGUID+332, 191983, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3621.184326171875, -66.018768310546875, 42.28960418701171875, 3.459641933441162109, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 370034 - -Unknown-, 375720 - -Unknown-)
(@CGUID+333, 191792, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3428.0947265625, 41.76247787475585937, 3.89389801025390625, 3.233490228652954101, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Frog (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+334, 192138, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3630.65576171875, -117.431610107421875, 44.25812911987304687, 4.2301483154296875, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Lava Pincer (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+335, 191809, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3502.882080078125, 67.9023895263671875, 45.07749557495117187, 0.084786392748355865, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Tiny Butterfly (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+336, 191517, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3627.75, -55.675506591796875, 41.91270828247070312, 1.44905555248260498, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 370034 - -Unknown-)
(@CGUID+337, 191517, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3632.188720703125, -55.9390487670898437, 41.21860122680664062, 2.95606851577758789, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 370034 - -Unknown-)
(@CGUID+338, 193026, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3628.732666015625, -42.8165740966796875, 40.72808074951171875, 1.065873622894287109, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Emberling (Area: -Unknown- - Difficulty: 0)
(@CGUID+339, 192138, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3630.319580078125, -93.6119918823242187, 40.80685806274414062, 4.206514835357666015, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Lava Pincer (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+340, 191944, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3671.4931640625, -65.640625, 66.70629119873046875, 2.432164907455444335, 7200, 0, 0, 37126, 0, 0, 0, 0, 0, 45505), -- Erupting Lasher (Area: -Unknown- - Difficulty: 0) (Auras: 376861 - -Unknown-)
(@CGUID+341, 191983, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3616.72998046875, -80.4652786254882812, 42.38413619995117187, 3.070740938186645507, 7200, 10, 0, 9281, 0, 1, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 370034 - -Unknown-, 376749 - -Unknown-, 375720 - -Unknown-, 376754 - -Unknown-) (possible waypoints or random movement)
(@CGUID+342, 192138, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3645.17822265625, -35.6935691833496093, 41.0729827880859375, 4.956122398376464843, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Lava Pincer (Area: -Unknown- - Difficulty: 0)
(@CGUID+343, 193026, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3641.67822265625, -126.785499572753906, 44.84198379516601562, 1.018550395965576171, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Emberling (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+344, 191983, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3568.740478515625, -42.3402786254882812, 41.70661544799804687, 3.070740938186645507, 7200, 10, 0, 9281, 0, 1, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 376749 - -Unknown-) (possible waypoints or random movement)
(@CGUID+345, 191983, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3573.25, -41.2638893127441406, 41.01365280151367187, 3.070740938186645507, 7200, 10, 0, 9281, 0, 1, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 376749 - -Unknown-) (possible waypoints or random movement)
(@CGUID+346, 191944, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3698.447998046875, -89.6527786254882812, 66.5656280517578125, 0.620829701423645019, 7200, 0, 0, 37126, 0, 0, 0, 0, 0, 45505), -- Erupting Lasher (Area: -Unknown- - Difficulty: 0)
(@CGUID+347, 191944, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3701.94091796875, -75.9600677490234375, 69.09163665771484375, 5.764270305633544921, 7200, 0, 0, 37126, 0, 0, 0, 0, 0, 45505), -- Erupting Lasher (Area: -Unknown- - Difficulty: 0)
(@CGUID+348, 190771, 2444, 13644, 14106, '0', '0', 0, 0, 1, 3519.3525390625, -55.7934036254882812, 34.64268112182617187, 6.04840850830078125, 7200, 0, 0, 55688, 0, 0, 0, 0, 0, 45505), -- Injured Ruby Culler (Area: -Unknown- - Difficulty: 0) (Auras: )
(@CGUID+349, 191975, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3712.607666015625, -82.0520858764648437, 66.77093505859375, 3.876360893249511718, 7200, 0, 0, 185628, 0, 0, 0, 0, 0, 45505), -- Rocan the Mountain (Area: -Unknown- - Difficulty: 0) (Auras: 376852 - -Unknown-)
(@CGUID+350, 191944, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3717.411376953125, -94.048614501953125, 66.26992034912109375, 1.951669096946716308, 7200, 0, 0, 37126, 0, 0, 0, 0, 0, 45505), -- Erupting Lasher (Area: -Unknown- - Difficulty: 0)
(@CGUID+351, 192138, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3690.0732421875, -45.6750679016113281, 40.88100051879882812, 3.90648961067199707, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Lava Pincer (Area: -Unknown- - Difficulty: 0)
(@CGUID+352, 192138, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3692.9892578125, -20.0932788848876953, 44.07530975341796875, 1.665858387947082519, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Lava Pincer (Area: -Unknown- - Difficulty: 0)
(@CGUID+353, 191983, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3630.0859375, -65.859375, 40.50586700439453125, 3.070740938186645507, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 376749 - -Unknown-)
(@CGUID+354, 191983, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3572.24560546875, -47.0138893127441406, 41.10098648071289062, 3.070740938186645507, 7200, 10, 0, 9281, 0, 1, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 376749 - -Unknown-) (possible waypoints or random movement)
(@CGUID+355, 191983, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3561.728271484375, -48.5486106872558593, 42.77386474609375, 3.070740938186645507, 7200, 10, 0, 9281, 0, 1, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 376749 - -Unknown-) (possible waypoints or random movement)
(@CGUID+356, 193026, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3721.827392578125, -74.531951904296875, 67.66805267333984375, 0.544919133186340332, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Emberling (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+357, 192138, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3695.12841796875, -2.26240253448486328, 42.47831344604492187, 1.845286250114440917, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Lava Pincer (Area: -Unknown- - Difficulty: 0) (Auras: )
(@CGUID+358, 193024, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3719.575927734375, -32.7909393310546875, 41.28279876708984375, 4.97901153564453125, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Emberling (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+359, 191517, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3701.83544921875, 14.51260185241699218, 43.31183242797851562, 4.554483413696289062, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 370034 - -Unknown-)
(@CGUID+360, 191517, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3703.674560546875, 14.5395050048828125, 42.90985488891601562, 3.435440778732299804, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 370034 - -Unknown-)
(@CGUID+361, 191517, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3701.76220703125, 15.87750530242919921, 43.42617034912109375, 4.409253120422363281, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 370034 - -Unknown-)
(@CGUID+362, 192138, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3739.52099609375, -28.3667621612548828, 42.5438690185546875, 0.129537850618362426, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Lava Pincer (Area: -Unknown- - Difficulty: 0)
(@CGUID+363, 191517, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3703.113037109375, 12.50484848022460937, 42.91483688354492187, 3.131764411926269531, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 370034 - -Unknown-)
(@CGUID+364, 191517, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3704.285888671875, 10.58804130554199218, 43.00517654418945312, 2.61080026626586914, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 370034 - -Unknown-)
(@CGUID+365, 191517, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3701.96923828125, 14.69457912445068359, 43.2839202880859375, 4.534958362579345703, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 370034 - -Unknown-)
(@CGUID+366, 191517, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3701.685302734375, 16.0111541748046875, 43.47688674926757812, 4.612931728363037109, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 370034 - -Unknown-)
(@CGUID+367, 191517, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3701.7763671875, 15.86462593078613281, 43.42095184326171875, 4.40671539306640625, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 370034 - -Unknown-)
(@CGUID+368, 191517, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3699.93603515625, 14.25168991088867187, 43.81772613525390625, 4.942609786987304687, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 370034 - -Unknown-)
(@CGUID+369, 192138, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3721.0380859375, 15.35127449035644531, 41.74004745483398437, 1.85273134708404541, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Lava Pincer (Area: -Unknown- - Difficulty: 0)
(@CGUID+370, 192138, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3739.610107421875, 3.697503328323364257, 40.97271347045898437, 6.065697193145751953, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Lava Pincer (Area: -Unknown- - Difficulty: 0)
(@CGUID+371, 191517, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3692.067626953125, -6.56944465637207031, 45.74094390869140625, 3.070740938186645507, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 376749 - -Unknown-)
(@CGUID+372, 191517, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3701.669189453125, -25.1927089691162109, 40.87322998046875, 3.070740938186645507, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 376749 - -Unknown-)
(@CGUID+373, 191517, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3707.916748046875, -24.5069446563720703, 41.368255615234375, 3.070740938186645507, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 376749 - -Unknown-)
(@CGUID+374, 191517, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3695.6728515625, -2.31076383590698242, 42.1622161865234375, 3.070740938186645507, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 376749 - -Unknown-)
(@CGUID+375, 192138, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3760.02490234375, -12.7058076858520507, 45.44652938842773437, 1.915234923362731933, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Lava Pincer (Area: -Unknown- - Difficulty: 0)
(@CGUID+376, 191517, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3734.759521484375, 3.126736164093017578, 41.1242218017578125, 3.070740938186645507, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 370034 - -Unknown-, 376749 - -Unknown-)
(@CGUID+377, 191917, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3703.1015625, -9.41319465637207031, 40.60139083862304687, 3.993533849716186523, 7200, 0, 0, 54450, 6015, 0, 0, 0, 0, 45505), -- Erupting Magma (Area: -Unknown- - Difficulty: 0) (Auras: 376765 - -Unknown-)
(@CGUID+378, 191517, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3701.755126953125, 17, 43.611419677734375, 3.070740938186645507, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 370034 - -Unknown-, 376749 - -Unknown-)
(@CGUID+379, 191983, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3572.24560546875, -47.0138893127441406, 41.10098648071289062, 3.070740938186645507, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 376749 - -Unknown-)
(@CGUID+380, 191983, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3612.0791015625, -89.1875, 41.33245468139648437, 3.275730609893798828, 7200, 10, 0, 9281, 0, 1, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 376749 - -Unknown-) (possible waypoints or random movement)
(@CGUID+381, 191983, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3568.740478515625, -42.3402786254882812, 41.70661544799804687, 3.070740938186645507, 7200, 10, 0, 9281, 0, 1, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 370034 - -Unknown-, 376749 - -Unknown-, 375720 - -Unknown-, 376754 - -Unknown-) (possible waypoints or random movement)
(@CGUID+382, 191917, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3737.25341796875, 15.11805534362792968, 39.90391159057617187, 2.20362401008605957, 7200, 0, 0, 54450, 6015, 0, 0, 0, 0, 45505), -- Erupting Magma (Area: -Unknown- - Difficulty: 0) (Auras: 376765 - -Unknown-)
(@CGUID+383, 191944, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3570.341064453125, -98.5347213745117187, 41.94510650634765625, 1.201428174972534179, 7200, 0, 0, 37126, 0, 0, 0, 0, 0, 45505), -- Erupting Lasher (Area: -Unknown- - Difficulty: 0) (Auras: 376804 - -Unknown-)
(@CGUID+384, 191917, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3653.132080078125, -35.8350715637207031, 40.0736083984375, 4.429791450500488281, 7200, 0, 0, 54450, 6015, 0, 0, 0, 0, 45505), -- Erupting Magma (Area: -Unknown- - Difficulty: 0) (Auras: 376765 - -Unknown-)
(@CGUID+385, 191517, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3617.10498046875, -87.4965286254882812, 42.67136001586914062, 3.070740938186645507, 7200, 10, 0, 9281, 0, 1, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 370034 - -Unknown-, 376749 - -Unknown-) (possible waypoints or random movement)
(@CGUID+386, 191517, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3620.059814453125, -69.5972213745117187, 42.55204010009765625, 3.070740938186645507, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 370034 - -Unknown-, 376749 - -Unknown-)
(@CGUID+387, 191983, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3616.72998046875, -80.4652786254882812, 42.38413619995117187, 3.070740938186645507, 7200, 10, 0, 9281, 0, 1, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 370034 - -Unknown-, 376749 - -Unknown-, 375720 - -Unknown-, 376754 - -Unknown-) (possible waypoints or random movement)
(@CGUID+388, 191517, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3732.4384765625, -8.97569465637207031, 41.08647918701171875, 3.070740938186645507, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 376749 - -Unknown-)
(@CGUID+389, 191917, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3589.193603515625, -49.7013893127441406, 40.9361724853515625, 4.008167743682861328, 7200, 0, 0, 54450, 6015, 0, 0, 0, 0, 45505), -- Erupting Magma (Area: -Unknown- - Difficulty: 0) (Auras: 376765 - -Unknown-)
(@CGUID+390, 191517, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3729.374267578125, -13.6545143127441406, 40.22435379028320312, 3.070740938186645507, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 376749 - -Unknown-)
(@CGUID+391, 191983, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3630.0859375, -65.859375, 40.50586700439453125, 3.070740938186645507, 7200, 10, 0, 9281, 0, 1, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 370034 - -Unknown-, 376749 - -Unknown-, 375720 - -Unknown-, 376754 - -Unknown-) (possible waypoints or random movement)
(@CGUID+392, 191517, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3621.468994140625, -89.163604736328125, 41.79025650024414062, 1.527463793754577636, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 370034 - -Unknown-)
(@CGUID+393, 191517, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3572.609375, -61.05279541015625, 41.11241531372070312, 5.758034706115722656, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 370034 - -Unknown-)
(@CGUID+394, 191983, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3575.7890625, -60.1927070617675781, 40.75659942626953125, 3.033490896224975585, 7200, 10, 0, 9281, 0, 1, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 375720 - -Unknown-, 376754 - -Unknown-, 370034 - -Unknown-) (possible waypoints or random movement)
(@CGUID+395, 191517, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3570.080322265625, -62.2050857543945312, 41.47487258911132812, 6.092789173126220703, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 370034 - -Unknown-)
(@CGUID+396, 191517, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3562.849853515625, -44.3901519775390625, 43.18157196044921875, 0.88927692174911499, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 370034 - -Unknown-)
(@CGUID+397, 191983, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3528.11376953125, -60.8196372985839843, 35.95280075073242187, 2.857535600662231445, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 370034 - -Unknown-)
(@CGUID+398, 191983, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3528.11376953125, -60.8196372985839843, 35.95280075073242187, 2.857535600662231445, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 370034 - -Unknown-)
(@CGUID+399, 191517, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3748.5322265625, -23.8454856872558593, 41.41999435424804687, 3.070740938186645507, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 376749 - -Unknown-)
(@CGUID+400, 191517, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3641.625, -56.203125, 41.43701934814453125, 3.070740938186645507, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 376749 - -Unknown-)
(@CGUID+401, 191917, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3750.4150390625, -10.2239580154418945, 39.99354934692382812, 5.459714412689208984, 7200, 0, 0, 54450, 6015, 0, 0, 0, 0, 45505), -- Erupting Magma (Area: -Unknown- - Difficulty: 0) (Auras: 376765 - -Unknown-)
(@CGUID+402, 191517, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3719.974853515625, 16.12152862548828125, 41.601531982421875, 3.070740938186645507, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 376749 - -Unknown-)
(@CGUID+403, 191944, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3640.990478515625, -122.534721374511718, 43.4329833984375, 0.424357682466506958, 7200, 0, 0, 37126, 0, 0, 0, 0, 0, 45505), -- Erupting Lasher (Area: -Unknown- - Difficulty: 0) (Auras: 376804 - -Unknown-)
(@CGUID+404, 191517, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3563.770751953125, -39.6996536254882812, 42.63470077514648437, 3.070740938186645507, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 370034 - -Unknown-, 376749 - -Unknown-)
(@CGUID+405, 191983, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3572.24560546875, -47.0138893127441406, 41.10098648071289062, 3.070740938186645507, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 376749 - -Unknown-)
(@CGUID+406, 191983, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3566.064208984375, -48.7604179382324218, 41.90792465209960937, 3.070740938186645507, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 370034 - -Unknown-, 376749 - -Unknown-, 375720 - -Unknown-, 376754 - -Unknown-)
(@CGUID+407, 191983, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3630.0859375, -65.859375, 40.50586700439453125, 3.070740938186645507, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 376749 - -Unknown-)
(@CGUID+408, 191517, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3644.670166015625, -43.1458320617675781, 41.1295166015625, 3.070740938186645507, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 376749 - -Unknown-)
(@CGUID+409, 191917, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3635.037353515625, -80.5381927490234375, 40.98206710815429687, 2.468971967697143554, 7200, 0, 0, 54450, 6015, 0, 0, 0, 0, 45505), -- Erupting Magma (Area: -Unknown- - Difficulty: 0) (Auras: 376765 - -Unknown-)
(@CGUID+410, 191517, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3593.218017578125, -71.1284713745117187, 40.16930770874023437, 3.070740938186645507, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 376749 - -Unknown-)
(@CGUID+411, 191517, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3692.067626953125, -6.56944465637207031, 45.74094390869140625, 3.070740938186645507, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 376749 - -Unknown-)
(@CGUID+412, 191917, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3737.25341796875, 15.11805534362792968, 39.90391159057617187, 2.20362401008605957, 7200, 0, 0, 54450, 6015, 0, 0, 0, 0, 45505), -- Erupting Magma (Area: -Unknown- - Difficulty: 0) (Auras: 376765 - -Unknown-)
(@CGUID+413, 191983, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3572.24560546875, -47.0138893127441406, 41.10098648071289062, 3.070740938186645507, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 376749 - -Unknown-)
(@CGUID+414, 191983, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3630.0859375, -65.859375, 40.50586700439453125, 3.070740938186645507, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 376749 - -Unknown-)
(@CGUID+415, 191983, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3566.064208984375, -48.7604179382324218, 41.9912567138671875, 3.070740938186645507, 7200, 10, 0, 9281, 0, 1, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 376749 - -Unknown-) (possible waypoints or random movement)
(@CGUID+416, 191517, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3637.4375, -54.0885429382324218, 41.07251739501953125, 3.070740938186645507, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 376749 - -Unknown-)
(@CGUID+417, 191944, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3570.341064453125, -98.5347213745117187, 41.94510650634765625, 1.201428174972534179, 7200, 0, 0, 37126, 0, 0, 0, 0, 0, 45505), -- Erupting Lasher (Area: -Unknown- - Difficulty: 0) (Auras: 376804 - -Unknown-)
(@CGUID+418, 191944, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3625.94873046875, -107.623268127441406, 61.29153060913085937, 3.489230155944824218, 7200, 0, 0, 37126, 0, 0, 0, 0, 0, 45505), -- Erupting Lasher (Area: -Unknown- - Difficulty: 0) (Auras: )
(@CGUID+419, 191517, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3695.6728515625, -2.31076383590698242, 42.1622161865234375, 3.070740938186645507, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 370034 - -Unknown-, 376749 - -Unknown-)
(@CGUID+420, 191983, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3616.72998046875, -80.4652786254882812, 42.38413619995117187, 3.070740938186645507, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 376749 - -Unknown-)
(@CGUID+421, 191983, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3573.25, -41.2638893127441406, 41.01365280151367187, 3.070740938186645507, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 376749 - -Unknown-)
(@CGUID+422, 191983, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3573.25, -41.2638893127441406, 41.01365280151367187, 3.070740938186645507, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 376749 - -Unknown-)
(@CGUID+423, 191983, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3616.72998046875, -80.4652786254882812, 42.38413619995117187, 3.070740938186645507, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 376749 - -Unknown-)
(@CGUID+424, 191983, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3566.87060546875, -51.3194465637207031, 41.97180557250976562, 3.275730609893798828, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 376749 - -Unknown-)
(@CGUID+425, 191983, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3572.24560546875, -47.0138893127441406, 41.10098648071289062, 3.070740938186645507, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 376749 - -Unknown-)
(@CGUID+426, 191517, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3597.288330078125, -67.40625, 41.60798263549804687, 3.070740938186645507, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 376749 - -Unknown-)
(@CGUID+427, 191517, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3652.8056640625, -45.7378463745117187, 40.63788604736328125, 3.070740938186645507, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 370034 - -Unknown-, 376749 - -Unknown-)
(@CGUID+428, 191983, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3630.0859375, -65.859375, 40.50586700439453125, 3.070740938186645507, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 370034 - -Unknown-, 376749 - -Unknown-, 375720 - -Unknown-, 376754 - -Unknown-)
(@CGUID+429, 191517, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3641.625, -56.203125, 41.43701934814453125, 3.070740938186645507, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 370034 - -Unknown-, 376749 - -Unknown-)
(@CGUID+430, 188699, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3464.721435546875, 123.8663177490234375, 5.228034496307373046, 1.786593317985534667, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Carrion Phoenix (Area: -Unknown- - Difficulty: 0) (Auras: 369897 - -Unknown-)
(@CGUID+431, 190771, 2444, 13644, 14106, '0', '0', 0, 0, 1, 3522.612060546875, 135.407989501953125, 36.992218017578125, 1.652682662010192871, 7200, 0, 0, 55688, 0, 0, 0, 0, 0, 45505), -- Injured Ruby Culler (Area: -Unknown- - Difficulty: 0) (Auras: )
(@CGUID+432, 190151, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3524.387939453125, 139.048614501953125, 36.84012985229492187, 4.030763626098632812, 7200, 0, 0, 55688, 0, 0, 0, 0, 0, 45505), -- Ruby Culler (Area: -Unknown- - Difficulty: 0)
(@CGUID+433, 191983, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3576.483642578125, -54.0190963745117187, 40.84659576416015625, 3.070740938186645507, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 376749 - -Unknown-)
(@CGUID+434, 191792, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3388.09814453125, 29.70685005187988281, 3.960858821868896484, 0.403593719005584716, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Frog (Area: -Unknown- - Difficulty: 0)
(@CGUID+435, 191792, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3458.302734375, 102.4410400390625, 4.091845035552978515, 5.644608497619628906, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Frog (Area: -Unknown- - Difficulty: 0)
(@CGUID+436, 191809, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3375.166748046875, 33.37503433227539062, 10.69821643829345703, 1.947150707244873046, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Tiny Butterfly (Area: -Unknown- - Difficulty: 0)
(@CGUID+437, 192136, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3547.9169921875, 127.083984375, 41.57015228271484375, 2.037167549133300781, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Flame Flick (Area: -Unknown- - Difficulty: 0)
(@CGUID+438, 191629, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3551.499267578125, 116.814178466796875, 45.13973236083984375, 1.325626850128173828, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Lava Slug (Area: -Unknown- - Difficulty: 0)
(@CGUID+439, 191629, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3551.071533203125, 115.99365234375, 44.96297454833984375, 6.16666412353515625, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Lava Slug (Area: -Unknown- - Difficulty: 0)
(@CGUID+440, 188698, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3514.077880859375, 168.8027496337890625, 32.83827590942382812, 4.21213388442993164, 7200, 10, 0, 15469, 0, 1, 0, 0, 0, 45505), -- Dreadsquall Feaster (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+441, 191628, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3569.940185546875, 117.6850051879882812, 62.24602508544921875, 5.2144622802734375, 7200, 0, 0, 24750, 0, 0, 0, 0, 0, 45505), -- Lava Snail (Area: -Unknown- - Difficulty: 0)
(@CGUID+442, 188698, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3461.295166015625, 165.26910400390625, 14.84862613677978515, 2.269977331161499023, 7200, 0, 0, 15469, 0, 0, 0, 0, 0, 45505), -- Dreadsquall Feaster (Area: -Unknown- - Difficulty: 0)
(@CGUID+443, 188699, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3500.85595703125, 171.4270782470703125, 17.51514816284179687, 1.534541130065917968, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Carrion Phoenix (Area: -Unknown- - Difficulty: 0) (Auras: 369897 - -Unknown-)
(@CGUID+444, 188698, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3460.718505859375, 166.3055419921875, 4.8444671630859375, 2.624365806579589843, 7200, 0, 0, 15469, 0, 0, 0, 0, 0, 45505), -- Dreadsquall Feaster (Area: -Unknown- - Difficulty: 0)
(@CGUID+445, 191792, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3425.8564453125, 113.5950393676757812, 4.089872360229492187, 4.935205936431884765, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Frog (Area: -Unknown- - Difficulty: 0)
(@CGUID+446, 191809, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3416.488525390625, 100.9372100830078125, 8.48226165771484375, 0.21438726782798767, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Tiny Butterfly (Area: -Unknown- - Difficulty: 0)
(@CGUID+447, 191983, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3568.740478515625, -42.3402786254882812, 41.70661544799804687, 3.070740938186645507, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Erupting Droplet (Area: -Unknown- - Difficulty: 0) (Auras: 376749 - -Unknown-)
(@CGUID+448, 188699, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3472.553955078125, 190.12847900390625, 4.575980186462402343, 1.539376378059387207, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Carrion Phoenix (Area: -Unknown- - Difficulty: 0) (Auras: 369897 - -Unknown-)
(@CGUID+449, 188698, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3494.146484375, 191.605560302734375, 20.65620040893554687, 3.219459295272827148, 7200, 10, 0, 15469, 0, 1, 0, 0, 0, 45505), -- Dreadsquall Feaster (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+450, 191797, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3429.14892578125, 122.8875274658203125, 3.443510293960571289, 5.503312110900878906, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Steam Drip (Area: -Unknown- - Difficulty: 0)
(@CGUID+451, 191797, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3455.43359375, 166.353912353515625, 3.764177322387695312, 1.038507938385009765, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Steam Drip (Area: -Unknown- - Difficulty: 0)
(@CGUID+452, 188699, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3500.771728515625, 208.7708282470703125, 4.831307888031005859, 3.45720076560974121, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Carrion Phoenix (Area: -Unknown- - Difficulty: 0) (Auras: 369897 - -Unknown-)
(@CGUID+453, 191628, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3597.491455078125, 170.9849395751953125, 53.06978988647460937, 2.093176603317260742, 7200, 10, 0, 24750, 0, 1, 0, 0, 0, 45505), -- Lava Snail (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+454, 191629, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3554.839599609375, 211.5821990966796875, 37.68180465698242187, 3.380397319793701171, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Lava Slug (Area: -Unknown- - Difficulty: 0)
(@CGUID+455, 191629, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3553.67333984375, 210.6600189208984375, 38.23051071166992187, 0.892733335494995117, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Lava Slug (Area: -Unknown- - Difficulty: 0)
(@CGUID+456, 191797, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3505.833251953125, 218.03814697265625, 3.656382322311401367, 0.277429252862930297, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Steam Drip (Area: -Unknown- - Difficulty: 0)
(@CGUID+457, 191792, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3408.0966796875, 175.5411529541015625, 2.912998676300048828, 2.903008937835693359, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Frog (Area: -Unknown- - Difficulty: 0)
(@CGUID+458, 191629, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3562.578125, 217.35546875, 36.80836105346679687, 0.350541144609451293, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Lava Slug (Area: -Unknown- - Difficulty: 0)
(@CGUID+459, 192136, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3609.5009765625, 192.044525146484375, 51.0129547119140625, 4.38958740234375, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Flame Flick (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+460, 191628, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3561.284423828125, 232.5321197509765625, 32.79690933227539062, 2.296790122985839843, 7200, 0, 0, 24750, 0, 0, 0, 0, 0, 45505), -- Lava Snail (Area: -Unknown- - Difficulty: 0)
(@CGUID+461, 192136, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3538.79052734375, 247.6415252685546875, 7.093316078186035156, 1.210039496421813964, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Flame Flick (Area: -Unknown- - Difficulty: 0)
(@CGUID+462, 191016, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3413.987060546875, 190.7447967529296875, 6.358612060546875, 6.073509693145751953, 7200, 0, 0, 661445, 0, 0, 0, 0, 0, 45505), -- Uktulut Protector (Area: -Unknown- - Difficulty: 0) (Auras: )
(@CGUID+463, 191797, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3414.810791015625, 201.623565673828125, 4.097756862640380859, 2.022073268890380859, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Steam Drip (Area: -Unknown- - Difficulty: 0)
(@CGUID+464, 193217, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3497.268310546875, 263.127166748046875, 17.28539657592773437, 4.034723281860351562, 7200, 0, 0, 123752, 0, 0, 0, 0, 0, 45505), -- Drakewing (Area: -Unknown- - Difficulty: 0)
(@CGUID+465, 191016, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3395.048583984375, 168.7132415771484375, 5.696878910064697265, 4.972031593322753906, 7200, 0, 0, 661445, 0, 0, 0, 0, 0, 45505), -- Uktulut Protector (Area: -Unknown- - Difficulty: 0) (Auras: )
(@CGUID+466, 192104, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3617.868408203125, 199.211822509765625, 56.0561676025390625, 5.729297161102294921, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Magma Slug (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+467, 191016, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3402.335205078125, 182.6927032470703125, 6.141985416412353515, 3.167864561080932617, 7200, 0, 0, 661445, 0, 0, 0, 0, 0, 45505), -- Uktulut Protector (Area: -Unknown- - Difficulty: 0) (Auras: )
(@CGUID+468, 191628, 2444, 13644, 14106, '0', '0', 0, 0, 0, 3640.861328125, 181.595458984375, 85.9175872802734375, 4.7309417724609375, 7200, 10, 0, 24750, 0, 1, 0, 0, 0, 45505), -- Lava Snail (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+469, 191797, 2444, 13644, 0, '0', '0', 0, 0, 0, 3546.04248046875, 272.932281494140625, 3.825542211532592773, 0.149941802024841308, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Steam Drip (Area: 0 - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+470, 190771, 2444, 13644, 0, '0', '0', 0, 0, 1, 3522.612060546875, 135.407989501953125, 37.07555007934570312, 1.652682662010192871, 7200, 0, 0, 55688, 0, 0, 0, 0, 0, 45505), -- Injured Ruby Culler (Area: 0 - Difficulty: 0) (Auras: )
(@CGUID+471, 192104, 2444, 13644, 0, '0', '0', 0, 0, 0, 3604.36083984375, 260.420135498046875, 24.68145561218261718, 4.820997238159179687, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Magma Slug (Area: 0 - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+472, 191797, 2444, 13644, 0, '0', '0', 0, 0, 0, 3517.096435546875, 281.722076416015625, 4.104285717010498046, 1.831143617630004882, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Steam Drip (Area: 0 - Difficulty: 0)
(@CGUID+473, 191628, 2444, 13644, 0, '0', '0', 0, 0, 0, 3558.721923828125, 291.398529052734375, 7.229106903076171875, 0.264438033103942871, 7200, 0, 0, 24750, 0, 0, 0, 0, 0, 45505), -- Lava Snail (Area: 0 - Difficulty: 0)
(@CGUID+474, 192136, 2444, 13644, 0, '0', '0', 0, 0, 0, 3578.60986328125, 296.9835205078125, 11.45366859436035156, 1.298650503158569335, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Flame Flick (Area: 0 - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+475, 192104, 2444, 13644, 0, '0', '0', 0, 0, 0, 3571.970703125, 303.710296630859375, 7.686014175415039062, 0.152182132005691528, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Magma Slug (Area: 0 - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+476, 194517, 2444, 13644, 0, '0', '0', 0, 0, 0, 3652.321044921875, 325.454193115234375, 26.69110870361328125, 0.354766517877578735, 7200, 0, 0, 46407, 0, 0, 0, 0, 0, 45505), -- Crushing Elemental (Area: 0 - Difficulty: 0)
(@CGUID+477, 191809, 2444, 13644, 0, '0', '0', 0, 0, 0, 3666.237060546875, 252.2852783203125, 65.03766632080078125, 2.09124612808227539, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Tiny Butterfly (Area: 0 - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+478, 190155, 2444, 13644, 0, '0', '0', 0, 0, 0, 3735.421142578125, 267.196197509765625, 71.05229949951171875, 4.760540485382080078, 7200, 0, 0, 49500, 6015, 0, 0, 0, 0, 45505), -- Caretaker Azkra (Area: 0 - Difficulty: 0)
(@CGUID+479, 191553, 2444, 13644, 0, '0', '0', 0, 0, 0, 3655.50732421875, 323.1170654296875, 27.33440208435058593, 1.633724808692932128, 7200, 0, 0, 24750, 0, 0, 0, 0, 0, 45505), -- Wild Argali (Area: 0 - Difficulty: 0) (Auras: 391254 - -Unknown-, 391255 - -Unknown-)
(@CGUID+480, 194525, 2444, 13644, 0, '0', '0', 0, 0, 0, 3731.701416015625, 311.657989501953125, 76.6299285888671875, 2.473083257675170898, 7200, 0, 0, 49500, 6015, 0, 0, 0, 0, 45505), -- Apprentice Caretaker Zefren (Area: 0 - Difficulty: 0)
(@CGUID+481, 191553, 2444, 13644, 0, '0', '0', 0, 0, 0, 3649.55322265625, 333.929168701171875, 26.70890426635742187, 1.80704963207244873, 7200, 0, 0, 24750, 0, 0, 0, 0, 0, 45505), -- Wild Argali (Area: 0 - Difficulty: 0)
(@CGUID+482, 191809, 2444, 13644, 0, '0', '0', 0, 0, 0, 3632.162841796875, 335.38873291015625, 24.39586639404296875, 1.490635633468627929, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Tiny Butterfly (Area: 0 - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+483, 191629, 2444, 13644, 0, '0', '0', 0, 0, 0, 3748.967041015625, 207.16510009765625, 84.7570953369140625, 3.564677953720092773, 7200, 10, 0, 9281, 0, 1, 0, 0, 0, 45505), -- Lava Slug (Area: 0 - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+484, 191628, 2444, 13644, 0, '0', '0', 0, 0, 0, 3750.200439453125, 199.433502197265625, 88.77315521240234375, 4.656673908233642578, 7200, 10, 0, 24750, 0, 1, 0, 0, 0, 45505), -- Lava Snail (Area: 0 - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+485, 191554, 2444, 13644, 0, '0', '0', 0, 0, 0, 3635.539306640625, 337.396026611328125, 24.38716506958007812, 2.182579517364501953, 7200, 10, 0, 9281, 0, 1, 0, 0, 0, 45505), -- Argali Lamb (Area: 0 - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+486, 192137, 2444, 13644, 0, '0', '0', 0, 0, 0, 3746.718017578125, 203.7243194580078125, 86.0161285400390625, 3.139836549758911132, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Lava Flick (Area: 0 - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+487, 192137, 2444, 13644, 0, '0', '0', 0, 0, 0, 3754.3583984375, 179.2067718505859375, 100.7330093383789062, 1.369381666183471679, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Lava Flick (Area: 0 - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+488, 191629, 2444, 13644, 0, '0', '0', 0, 0, 0, 3759.257080078125, 207.8402862548828125, 84.7317047119140625, 2.148136138916015625, 7200, 10, 0, 9281, 0, 1, 0, 0, 0, 45505), -- Lava Slug (Area: 0 - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+489, 191809, 2444, 13644, 0, '0', '0', 0, 0, 0, 3634.921630859375, 342.465423583984375, 27.78380775451660156, 5.781973838806152343, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Tiny Butterfly (Area: 0 - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+490, 191629, 2444, 13644, 0, '0', '0', 0, 0, 0, 3759.006591796875, 209.79302978515625, 84.36988067626953125, 0.909324884414672851, 7200, 10, 0, 9281, 0, 1, 0, 0, 0, 45505), -- Lava Slug (Area: 0 - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+491, 191818, 2444, 13644, 0, '0', '0', 0, 0, 0, 3746.099365234375, 301.21038818359375, 78.26622772216796875, 3.793786287307739257, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Shaggy Rabbit (Area: 0 - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+492, 191554, 2444, 13644, 0, '0', '0', 0, 0, 0, 3630.661376953125, 347.402801513671875, 24.23944091796875, 2.800999641418457031, 7200, 10, 0, 9281, 0, 1, 0, 0, 0, 45505), -- Argali Lamb (Area: 0 - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+493, 191628, 2444, 13644, 0, '0', '0', 0, 0, 0, 3771.8837890625, 192.2312469482421875, 91.61666107177734375, 4.169991493225097656, 7200, 10, 0, 24750, 0, 1, 0, 0, 0, 45505), -- Lava Snail (Area: 0 - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+494, 191818, 2444, 13644, 0, '0', '0', 0, 0, 0, 3725.253662109375, 323.41754150390625, 78.087615966796875, 4.309127330780029296, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Shaggy Rabbit (Area: 0 - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+495, 191553, 2444, 13644, 0, '0', '0', 0, 0, 0, 3626.27880859375, 345.533660888671875, 22.51332283020019531, 4.301323413848876953, 7200, 10, 0, 24750, 0, 1, 0, 0, 0, 45505), -- Wild Argali (Area: 0 - Difficulty: 0) (Auras: 391254 - -Unknown-) (possible waypoints or random movement)
(@CGUID+496, 191553, 2444, 13644, 0, '0', '0', 0, 0, 0, 3763.203857421875, 296.386962890625, 83.13639068603515625, 3.808712959289550781, 7200, 10, 0, 24750, 0, 1, 0, 0, 0, 45505), -- Wild Argali (Area: 0 - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+497, 191553, 2444, 13644, 0, '0', '0', 0, 0, 0, 3762.193603515625, 291.33160400390625, 82.24008941650390625, 3.821702241897583007, 7200, 0, 0, 24750, 0, 0, 0, 0, 0, 45505), -- Wild Argali (Area: 0 - Difficulty: 0)
(@CGUID+498, 194517, 2444, 13644, 0, '0', '0', 0, 0, 0, 3655.721923828125, 395.097686767578125, 40.657440185546875, 5.516527652740478515, 7200, 0, 0, 46407, 0, 0, 0, 0, 0, 45505), -- Crushing Elemental (Area: 0 - Difficulty: 0)
(@CGUID+499, 191628, 2444, 13644, 0, '0', '0', 0, 0, 0, 3778.25, 215.2291717529296875, 83.934478759765625, 6.025813102722167968, 7200, 0, 0, 24750, 0, 0, 0, 0, 0, 45505); -- Lava Snail (Area: 0 - Difficulty: 0)

INSERT INTO `creature` (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnDifficulties`, `PhaseId`, `PhaseGroup`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `wander_distance`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`, `VerifiedBuild`) VALUES
(@CGUID+500, 192137, 2444, 13644, 0, '0', '0', 0, 0, 0, 3779.41162109375, 214.94598388671875, 84.149169921875, 4.525688648223876953, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Lava Flick (Area: 0 - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+501, 194517, 2444, 13644, 0, '0', '0', 0, 0, 0, 3718.14892578125, 376.8077392578125, 77.2982330322265625, 1.68994307518005371, 7200, 0, 0, 46407, 0, 0, 0, 0, 0, 45505), -- Crushing Elemental (Area: 0 - Difficulty: 0)
(@CGUID+502, 191629, 2444, 13644, 0, '0', '0', 0, 0, 0, 3803.393310546875, 215.986114501953125, 79.88266754150390625, 0, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Lava Slug (Area: 0 - Difficulty: 0)
(@CGUID+503, 191818, 2444, 13644, 0, '0', '0', 0, 0, 0, 3790.38720703125, 275.80218505859375, 79.48905181884765625, 0.159506663680076599, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Shaggy Rabbit (Area: 0 - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+504, 191818, 2444, 13644, 0, '0', '0', 0, 0, 0, 3701.477294921875, 364.490386962890625, 75.35266876220703125, 3.131827354431152343, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Shaggy Rabbit (Area: 0 - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+505, 192137, 2444, 13644, 0, '0', '0', 0, 0, 0, 3802.900634765625, 217.0055999755859375, 79.9713134765625, 5.043937206268310546, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Lava Flick (Area: 0 - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+506, 191628, 2444, 13644, 0, '0', '0', 0, 0, 0, 3793.2587890625, 206.295684814453125, 84.86013031005859375, 4.034143447875976562, 7200, 10, 0, 24750, 0, 1, 0, 0, 0, 45505), -- Lava Snail (Area: 0 - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+507, 190211, 2444, 13644, 0, '0', '0', 0, 0, 0, 3735.375, 267.399322509765625, 71.0466156005859375, 0, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Egg Returned to Safety Kill Credit [DNT] (Area: 0 - Difficulty: 0)
(@CGUID+508, 191629, 2444, 13644, 14107, '0', '0', 0, 0, 0, 3805.596435546875, 215.826385498046875, 81.6136627197265625, 0, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Lava Slug (Area: -Unknown- - Difficulty: 0)
(@CGUID+509, 191628, 2444, 13644, 14107, '0', '0', 0, 0, 0, 3805.173583984375, 187.782989501953125, 91.1300048828125, 4.994707584381103515, 7200, 0, 0, 24750, 0, 0, 0, 0, 0, 45505), -- Lava Snail (Area: -Unknown- - Difficulty: 0)
(@CGUID+510, 194517, 2444, 13644, 14107, '0', '0', 0, 0, 0, 3700.506591796875, 417.099456787109375, 70.7402496337890625, 0.509765684604644775, 7200, 0, 0, 46407, 0, 0, 0, 0, 0, 45505), -- Crushing Elemental (Area: -Unknown- - Difficulty: 0)
(@CGUID+511, 191629, 2444, 13644, 14107, '0', '0', 0, 0, 0, 3800.361328125, 183.0056304931640625, 98.6085662841796875, 5.539556503295898437, 7200, 10, 0, 9281, 0, 1, 0, 0, 0, 45505), -- Lava Slug (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+512, 194517, 2444, 13644, 14107, '0', '0', 0, 0, 0, 3727.3125, 417.178375244140625, 94.168548583984375, 1.673509597778320312, 7200, 10, 0, 46407, 0, 1, 0, 0, 0, 45505), -- Crushing Elemental (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+513, 194517, 2444, 13644, 14107, '0', '0', 0, 0, 0, 3655.276611328125, 421.12677001953125, 39.01617050170898437, 4.712523937225341796, 7200, 0, 0, 46407, 0, 0, 0, 0, 0, 45505), -- Crushing Elemental (Area: -Unknown- - Difficulty: 0) (Auras: 381535 - -Unknown-)
(@CGUID+514, 192137, 2444, 13644, 14107, '0', '0', 0, 0, 0, 3802.125244140625, 176.22821044921875, 100.2150650024414062, 2.800999641418457031, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Lava Flick (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+515, 191624, 2444, 13644, 14107, '0', '0', 0, 0, 0, 3872.9541015625, 264.12847900390625, 80.0463104248046875, 2.238474845886230468, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Tranquil Vorquin (Area: -Unknown- - Difficulty: 0)
(@CGUID+516, 191818, 2444, 13644, 14107, '0', '0', 0, 0, 0, 3846.281982421875, 212.3380279541015625, 83.501007080078125, 0.266641288995742797, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Shaggy Rabbit (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+517, 191812, 2444, 13644, 14107, '0', '0', 0, 0, 0, 3722.66455078125, 399.083953857421875, 93.0658111572265625, 5.257328987121582031, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Crumbling Pebbles (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+518, 191624, 2444, 13644, 14107, '0', '0', 0, 0, 0, 3900.98779296875, 227.61285400390625, 80.1219635009765625, 4.378533840179443359, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Tranquil Vorquin (Area: -Unknown- - Difficulty: 0)
(@CGUID+519, 191624, 2444, 13644, 14107, '0', '0', 0, 0, 0, 3906.671875, 273.755035400390625, 79.7897186279296875, 3.630825281143188476, 7200, 10, 0, 30938, 0, 1, 0, 0, 0, 45505), -- Tranquil Vorquin (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+520, 194517, 2444, 13644, 14107, '0', '0', 0, 0, 0, 3719.198486328125, 447.749908447265625, 71.38637542724609375, 4.256601333618164062, 7200, 0, 0, 46407, 0, 0, 0, 0, 0, 45505), -- Crushing Elemental (Area: -Unknown- - Difficulty: 0)
(@CGUID+521, 191818, 2444, 13644, 14107, '0', '0', 0, 0, 0, 3884.986083984375, 267.1065673828125, 79.63899993896484375, 5.12245798110961914, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Shaggy Rabbit (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+522, 191625, 2444, 13644, 14107, '0', '0', 0, 0, 0, 3895.4990234375, 270.895965576171875, 79.98303985595703125, 4.274610519409179687, 7200, 10, 0, 15469, 0, 1, 0, 0, 0, 45505), -- Vorquin Foal (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+523, 191817, 2444, 13644, 14107, '0', '0', 0, 0, 0, 3897.61181640625, 195.0724945068359375, 105.42852783203125, 5.793924808502197265, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Shores Snake (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+524, 194523, 2444, 13644, 14107, '0', '0', 0, 0, 0, 3688.815185546875, 454.557281494140625, 46.22644805908203125, 2.377318620681762695, 7200, 0, 0, 77345, 0, 0, 0, 0, 0, 45505), -- Raging Elemental (Area: -Unknown- - Difficulty: 0) (Auras: 364022 - -Unknown-)
(@CGUID+525, 194524, 2444, 13644, 14107, '0', '0', 0, 0, 0, 3748.3681640625, 454.5694580078125, 98.41986083984375, 2.728508710861206054, 7200, 0, 0, 185628, 0, 0, 0, 0, 0, 45505), -- Earthshatter Elemental (Area: -Unknown- - Difficulty: 0) (Auras: 377717 - -Unknown-)
(@CGUID+526, 191812, 2444, 13644, 14107, '0', '0', 0, 0, 0, 3686.79345703125, 415.999969482421875, 68.2410888671875, 4.966495037078857421, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Crumbling Pebbles (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+527, 191812, 2444, 13644, 14107, '0', '0', 0, 0, 0, 3714.548583984375, 426.892913818359375, 80.33771514892578125, 2.034168958663940429, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Crumbling Pebbles (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+528, 194517, 2444, 13644, 14107, '0', '0', 0, 0, 0, 3740.199951171875, 484.5128173828125, 85.05077362060546875, 5.439031600952148437, 7200, 0, 0, 46407, 0, 0, 0, 0, 0, 45505), -- Crushing Elemental (Area: -Unknown- - Difficulty: 0)
(@CGUID+529, 191812, 2444, 13644, 14107, '0', '0', 0, 0, 0, 3754.579833984375, 438.582733154296875, 111.2147216796875, 0.599296927452087402, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Crumbling Pebbles (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+530, 191823, 2444, 13644, 14107, '0', '0', 0, 0, 0, 3838.548583984375, 423.805572509765625, 208.020355224609375, 5.763760089874267578, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Vicious Proto-Drake (Area: -Unknown- - Difficulty: 0)
(@CGUID+531, 192058, 2444, 13644, 14107, '0', '0', 0, 0, 0, 3749.46240234375, 389.47509765625, 101.1937332153320312, 0.172692671418190002, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Igneoid (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+532, 194524, 2444, 13644, 14107, '0', '0', 0, 0, 0, 3696.650146484375, 481.59027099609375, 51.1324005126953125, 3.435793161392211914, 7200, 0, 0, 185628, 0, 0, 0, 0, 0, 45505), -- Earthshatter Elemental (Area: -Unknown- - Difficulty: 0) (Auras: 377717 - -Unknown-)
(@CGUID+533, 191624, 2444, 13644, 14107, '0', '0', 0, 0, 0, 3973.4345703125, 202.8065338134765625, 60.39299774169921875, 4.973934173583984375, 7200, 10, 0, 30938, 0, 1, 0, 0, 0, 45505), -- Tranquil Vorquin (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+534, 191818, 2444, 13644, 0, '0', '0', 0, 0, 0, 3938.87744140625, 309.582611083984375, 82.5101165771484375, 4.293995380401611328, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Shaggy Rabbit (Area: 0 - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+535, 191817, 2444, 13644, 0, '0', '0', 0, 0, 0, 3949.235107421875, 276.14581298828125, 80.9518585205078125, 4.66517496109008789, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Shores Snake (Area: 0 - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+536, 191624, 2444, 13644, 0, '0', '0', 0, 0, 0, 3994.15478515625, 309.57379150390625, 56.35289382934570312, 0.551296114921569824, 7200, 10, 0, 30938, 0, 1, 0, 0, 0, 45505), -- Tranquil Vorquin (Area: 0 - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+537, 192181, 2444, 13644, 0, '0', '0', 0, 0, 0, 3957.816162109375, 363.853515625, 96.1868133544921875, 5.779057025909423828, 7200, 10, 0, 37126, 0, 1, 0, 0, 0, 45505), -- Wild Rockfang (Area: 0 - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+538, 191798, 2444, 13644, 0, '0', '0', 0, 0, 0, 3842.7060546875, 330.90521240234375, 198.7335357666015625, 2.821176528930664062, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Stray Gust (Area: 0 - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+539, 191624, 2444, 13644, 0, '0', '0', 0, 0, 0, 3987.35595703125, 334.55035400390625, 59.3394775390625, 5.06618356704711914, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Tranquil Vorquin (Area: 0 - Difficulty: 0)
(@CGUID+540, 192181, 2444, 13644, 0, '0', '0', 0, 0, 0, 3947.708740234375, 403.75, 82.94855499267578125, 3.131972789764404296, 7200, 10, 0, 37126, 0, 1, 0, 0, 0, 45505), -- Wild Rockfang (Area: 0 - Difficulty: 0) (Auras: 391254 - -Unknown-) (possible waypoints or random movement)
(@CGUID+541, 191817, 2444, 13644, 0, '0', '0', 0, 0, 0, 3957.65380859375, 335.13897705078125, 81.372467041015625, 3.49736785888671875, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Shores Snake (Area: 0 - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+542, 195917, 2444, 13644, 0, '0', '0', 0, 0, 0, 4014.893310546875, 153.404510498046875, 37.58617401123046875, 2.716512680053710937, 7200, 10, 0, 68064, 0, 1, 0, 0, 0, 45505), -- Primal Revenant (Area: 0 - Difficulty: 0) (Auras: ) (possible waypoints or random movement)
(@CGUID+543, 192182, 2444, 13644, 0, '0', '0', 0, 0, 0, 3995.08251953125, 362.680572509765625, 92.6962890625, 0.194363892078399658, 7200, 0, 0, 68064, 0, 0, 0, 0, 0, 45505), -- Rockfang Hunter (Area: 0 - Difficulty: 0)
(@CGUID+544, 186834, 2444, 13644, 0, '0', '0', 0, 0, 0, 4006.067626953125, 159.28125, 35.37117385864257812, 2.775829792022705078, 7200, 0, 0, 77345, 0, 0, 0, 0, 0, 45505), -- Stubborn Hornswog (Area: 0 - Difficulty: 0)
(@CGUID+545, 191625, 2444, 13644, 0, '0', '0', 0, 0, 0, 3990.135498046875, 333.206939697265625, 58.62505722045898437, 5.5803680419921875, 7200, 10, 0, 15469, 0, 1, 0, 0, 0, 45505), -- Vorquin Foal (Area: 0 - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+546, 191817, 2444, 13644, 0, '0', '0', 0, 0, 0, 3951.554931640625, 370.945526123046875, 97.27332305908203125, 0.950353860855102539, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Shores Snake (Area: 0 - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+547, 191625, 2444, 13644, 0, '0', '0', 0, 0, 0, 3987.9521484375, 327.780364990234375, 59.23448944091796875, 5.14917755126953125, 7200, 10, 0, 15469, 0, 1, 0, 0, 0, 45505), -- Vorquin Foal (Area: 0 - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+548, 195915, 2444, 13644, 0, '0', '0', 0, 0, 0, 4052.654296875, 136.0477752685546875, 41.61108779907226562, 0.670468807220458984, 7200, 0, 0, 297004, 0, 0, 0, 0, 0, 45505), -- Firava the Rekindler (Area: 0 - Difficulty: 0) (Auras: )
(@CGUID+549, 186825, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4039.593017578125, 197.9322967529296875, 40.53679275512695312, 0.366995930671691894, 7200, 10, 0, 30938, 2568, 1, 0, 0, 0, 45505), -- Molten Primalist (Area: -Unknown- - Difficulty: 0) (Auras: 42459 - Dual Wield) (possible waypoints or random movement)
(@CGUID+550, 187406, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4045.020751953125, 252.467010498046875, 54.35757827758789062, 0.137664124369621276, 7200, 0, 0, 68064, 0, 0, 0, 0, 0, 45505), -- Sendrax (Area: -Unknown- - Difficulty: 0)
(@CGUID+551, 193001, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4032.81396484375, 188.7368927001953125, 38.1624908447265625, 2.583911895751953125, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Kindlet (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+552, 186684, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4085.007080078125, 232.7899322509765625, 66.44589996337890625, 1.987561821937561035, 7200, 10, 0, 30938, 0, 1, 0, 0, 0, 45505), -- Lava Phoenix (Area: -Unknown- - Difficulty: 0) (Auras: 369897 - -Unknown-) (possible waypoints or random movement)
(@CGUID+553, 186836, 2444, 13644, 13709, '0', '0', 0, 0, 0, 3983.065185546875, 67.13715362548828125, 35.73021697998046875, 0.574090182781219482, 7200, 0, 0, 216566, 0, 0, 0, 0, 0, 45505), -- Lava Burster (Area: -Unknown- - Difficulty: 0)
(@CGUID+554, 192181, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4043.651123046875, 380.5545654296875, 71.86808013916015625, 0.662842214107513427, 7200, 10, 0, 37126, 0, 1, 0, 0, 0, 45505), -- Wild Rockfang (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+555, 191817, 2444, 13644, 13709, '0', '0', 0, 0, 0, 3991.857421875, 371.6851806640625, 61.387542724609375, 5.16089630126953125, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Shores Snake (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+556, 193001, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4039.86328125, 169.655426025390625, 38.20720291137695312, 0.864717602729797363, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Kindlet (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+557, 193001, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4050.446044921875, 194.92852783203125, 37.56511306762695312, 0.69905555248260498, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Kindlet (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+558, 3300, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4054.663330078125, 304.604278564453125, 52.7260894775390625, 6.237863540649414062, 7200, 10, 0, 1, 0, 1, 0, 0, 0, 45505), -- Adder (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+559, 186833, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4063.525390625, 199.8656005859375, 35.75407791137695312, 0.924234330654144287, 7200, 10, 0, 24750, 0, 1, 0, 0, 0, 45505), -- Spiteful Snail (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+560, 186825, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4114.77880859375, 226.1770782470703125, 37.4360809326171875, 5.210281848907470703, 7200, 10, 0, 30938, 2568, 1, 0, 0, 0, 45505), -- Molten Primalist (Area: -Unknown- - Difficulty: 0) (Auras: 42459 - Dual Wield, 364117 - -Unknown-) (possible waypoints or random movement)
(@CGUID+561, 186825, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4119.97998046875, 234.890625, 37.5135955810546875, 6.23626565933227539, 7200, 10, 0, 30938, 2568, 1, 0, 0, 0, 45505), -- Molten Primalist (Area: -Unknown- - Difficulty: 0) (Auras: 42459 - Dual Wield, 364117 - -Unknown-) (possible waypoints or random movement)
(@CGUID+562, 191904, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4051.294189453125, 159.7708282470703125, 38.45930862426757812, 1.941360235214233398, 7200, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Ruby Dragon Eggs (Area: -Unknown- - Difficulty: 0)
(@CGUID+563, 188372, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4070.45751953125, 317.298614501953125, 50.31597137451171875, 2.73919081687927246, 7200, 0, 0, 24750, 0, 0, 0, 0, 0, 45505), -- Primal Tarasek (Area: -Unknown- - Difficulty: 0)
(@CGUID+564, 190080, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4066.068603515625, 319.166656494140625, 50.44097137451171875, 5.880783557891845703, 7200, 0, 0, 19800, 6015, 0, 0, 0, 0, 45505), -- Tarasek Elementalist (Area: -Unknown- - Difficulty: 0) (Auras: 369706 - -Unknown-)
(@CGUID+565, 193000, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4077.5302734375, 212.470703125, 37.15795516967773437, 3.193284988403320312, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Kindlet (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+566, 193001, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4073.4931640625, 189.015625, 37.72216415405273437, 4.431406974792480468, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Kindlet (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+567, 186684, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4126.7431640625, 192.2309112548828125, 52.50007247924804687, 3.618374586105346679, 7200, 10, 0, 30938, 0, 1, 0, 0, 0, 45505), -- Lava Phoenix (Area: -Unknown- - Difficulty: 0) (Auras: 369897 - -Unknown-) (possible waypoints or random movement)
(@CGUID+568, 186825, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4083.771728515625, 188.0677032470703125, 37.57247543334960937, 1.27814793586730957, 7200, 0, 0, 30938, 2568, 0, 0, 0, 0, 45505), -- Molten Primalist (Area: -Unknown- - Difficulty: 0) (Auras: 42459 - Dual Wield, 364220 - -Unknown-)
(@CGUID+569, 186834, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4127.4599609375, 193.4652862548828125, 35.6251373291015625, 2.775829792022705078, 7200, 0, 0, 77345, 0, 0, 0, 0, 0, 45505), -- Stubborn Hornswog (Area: -Unknown- - Difficulty: 0)
(@CGUID+570, 186823, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4124.48095703125, 269.701385498046875, 43.19445419311523437, 2.767912864685058593, 7200, 0, 0, 24750, 6015, 0, 0, 0, 0, 45505), -- Lavacaller Primalist (Area: -Unknown- - Difficulty: 0) (Auras: 364117 - -Unknown-)
(@CGUID+571, 186829, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4115.265625, 267.1007080078125, 46.23582077026367187, 0.826097667217254638, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Spiteful Slug (Area: -Unknown- - Difficulty: 0)
(@CGUID+572, 188666, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4162.90625, 233.732635498046875, 36.64218902587890625, 3.523369312286376953, 7200, 0, 0, 37126, 0, 0, 0, 0, 0, 45505), -- Unleashed Lavaburst (Area: -Unknown- - Difficulty: 0) (Auras: 376804 - -Unknown-)
(@CGUID+573, 191886, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4161.46728515625, 249.87847900390625, 40.49796295166015625, 1.70660257339477539, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Primalist Lava Conduit (Area: -Unknown- - Difficulty: 0)
(@CGUID+574, 188666, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4153.73193359375, 309.285858154296875, 42.65788650512695312, 2.693486690521240234, 7200, 0, 0, 37126, 0, 0, 0, 0, 0, 45505), -- Unleashed Lavaburst (Area: -Unknown- - Difficulty: 0)
(@CGUID+575, 186823, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4023.020751953125, 112.5243072509765625, 45.23695755004882812, 5.731539726257324218, 7200, 0, 0, 24750, 6015, 0, 0, 0, 0, 45505), -- Lavacaller Primalist (Area: -Unknown- - Difficulty: 0) (Auras: 387072 - -Unknown-, 364117 - -Unknown-)
(@CGUID+576, 186823, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4083.166259765625, 149.239105224609375, 40.72253799438476562, 3.400308132171630859, 7200, 0, 0, 24750, 6015, 0, 0, 0, 0, 45505), -- Lavacaller Primalist (Area: -Unknown- - Difficulty: 0) (Auras: )
(@CGUID+577, 179965, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4057.1875, 244.7135467529296875, 55.06705093383789062, 0, 7200, 0, 0, 49313, 0, 0, 0, 0, 0, 45505), -- Generic Bunny (Area: -Unknown- - Difficulty: 0)
(@CGUID+578, 186823, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4106.76416015625, 316.744781494140625, 49.92295074462890625, 1.108824729919433593, 7200, 0, 0, 24750, 6015, 0, 0, 0, 0, 45505), -- Lavacaller Primalist (Area: -Unknown- - Difficulty: 0) (Auras: 364026 - -Unknown-)
(@CGUID+579, 186829, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4121.18994140625, 272.78125, 46.01257705688476562, 4.935000896453857421, 7200, 10, 0, 9281, 0, 1, 0, 0, 0, 45505), -- Spiteful Slug (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+580, 191886, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4104.70751953125, 103.125, 42.53026962280273437, 0, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Primalist Lava Conduit (Area: -Unknown- - Difficulty: 0)
(@CGUID+581, 186823, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4030.522705078125, 113.8125, 44.17813491821289062, 4.041987895965576171, 7200, 0, 0, 24750, 6015, 0, 0, 0, 0, 45505), -- Lavacaller Primalist (Area: -Unknown- - Difficulty: 0) (Auras: 387072 - -Unknown-, 364117 - -Unknown-)
(@CGUID+582, 186684, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4178.06591796875, 296.4197998046875, 99.9967193603515625, 3.96056365966796875, 7200, 10, 0, 30938, 0, 1, 0, 0, 0, 45505), -- Lava Phoenix (Area: -Unknown- - Difficulty: 0) (Auras: 369897 - -Unknown-, 391254 - -Unknown-) (possible waypoints or random movement)
(@CGUID+583, 190080, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4151.09228515625, 285.373260498046875, 39.11469650268554687, 4.094286441802978515, 7200, 10, 0, 19800, 6015, 1, 0, 0, 0, 45505), -- Tarasek Elementalist (Area: -Unknown- - Difficulty: 0) (Auras: ) (possible waypoints or random movement)
(@CGUID+584, 194820, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4460.19873046875, 455.376739501953125, 576.83636474609375, 0, 7200, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Dragon Glyph (Area: -Unknown- - Difficulty: 0) (Auras: 384678 - -Unknown-)
(@CGUID+585, 191886, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4168.46533203125, 143.31597900390625, 44.3593292236328125, 1.70660257339477539, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Primalist Lava Conduit (Area: -Unknown- - Difficulty: 0)
(@CGUID+586, 186823, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4133.5537109375, 359.423614501953125, 55.88541412353515625, 4.933979988098144531, 7200, 0, 0, 24750, 6015, 0, 0, 0, 0, 45505), -- Lavacaller Primalist (Area: -Unknown- - Difficulty: 0) (Auras: 364117 - -Unknown-)
(@CGUID+587, 188667, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4205.72021484375, 276.090911865234375, 51.0944671630859375, 5.376345634460449218, 7200, 0, 0, 68064, 0, 0, 0, 0, 0, 45505), -- Swelling Fire Elemental (Area: -Unknown- - Difficulty: 0) (Auras: )
(@CGUID+588, 186823, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4139.52001953125, 164.4341583251953125, 37.63644027709960937, 5.339474678039550781, 7200, 0, 0, 24750, 6015, 0, 0, 0, 0, 45505), -- Lavacaller Primalist (Area: -Unknown- - Difficulty: 0)
(@CGUID+589, 186833, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4165.923828125, 217.545135498046875, 40.91631698608398437, 0.640269756317138671, 7200, 0, 0, 24750, 0, 0, 0, 0, 0, 45505), -- Spiteful Snail (Area: -Unknown- - Difficulty: 0)
(@CGUID+590, 186684, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4196.45068359375, 173.72222900390625, 67.59743499755859375, 3.345417737960815429, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Lava Phoenix (Area: -Unknown- - Difficulty: 0) (Auras: 369897 - -Unknown-)
(@CGUID+591, 193001, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4140.45654296875, 154.052825927734375, 38.59401702880859375, 5.096959114074707031, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Kindlet (Area: -Unknown- - Difficulty: 0)
(@CGUID+592, 191886, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4181.50244140625, 380.579864501953125, 61.45051956176757812, 1.70660257339477539, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Primalist Lava Conduit (Area: -Unknown- - Difficulty: 0)
(@CGUID+593, 186833, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4073.982666015625, 112.049224853515625, 35.741455078125, 1.134281635284423828, 7200, 10, 0, 24750, 0, 1, 0, 0, 0, 45505), -- Spiteful Snail (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+594, 188666, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4151.6708984375, 102.010406494140625, 38.8170318603515625, 2.067410945892333984, 7200, 0, 0, 37126, 0, 0, 0, 0, 0, 45505), -- Unleashed Lavaburst (Area: -Unknown- - Difficulty: 0) (Auras: 376765 - -Unknown-)
(@CGUID+595, 195917, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4081.098388671875, 75.4996490478515625, 40.99522018432617187, 0.738701999187469482, 7200, 0, 0, 68064, 0, 0, 0, 0, 0, 45505), -- Primal Revenant (Area: -Unknown- - Difficulty: 0) (Auras: )
(@CGUID+596, 194314, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4052.085205078125, 246.638885498046875, 54.33906173706054687, 1.374152779579162597, 7200, 0, 0, 19456, 0, 0, 0, 0, 0, 45505), -- Captain Exposition (Area: -Unknown- - Difficulty: 0) (Auras: 385839 - -Unknown-)
(@CGUID+597, 195917, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4117.783203125, 143.0208282470703125, 40.60277938842773437, 4.94258737564086914, 7200, 0, 0, 68064, 0, 0, 0, 0, 0, 45505), -- Primal Revenant (Area: -Unknown- - Difficulty: 0) (Auras: )
(@CGUID+598, 186684, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4156.921875, 110.65264892578125, 96.01434326171875, 2.377194404602050781, 7200, 10, 0, 30938, 0, 1, 0, 0, 0, 45505), -- Lava Phoenix (Area: -Unknown- - Difficulty: 0) (Auras: 369897 - -Unknown-) (possible waypoints or random movement)
(@CGUID+599, 190013, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4051.647705078125, 158.5746612548828125, 39.43366622924804687, 3.076980113983154296, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Ruby Dragon Egg (Area: -Unknown- - Difficulty: 0) (Auras: )
(@CGUID+600, 190013, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4162.884765625, 253.55035400390625, 40.90608978271484375, 4.411235332489013671, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Ruby Dragon Egg (Area: -Unknown- - Difficulty: 0)
(@CGUID+601, 190013, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4053.0390625, 159.517364501953125, 39.502655029296875, 5.937458992004394531, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Ruby Dragon Egg (Area: -Unknown- - Difficulty: 0) (Auras: )
(@CGUID+602, 190013, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4054.018310546875, 161.123260498046875, 39.568084716796875, 0, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Ruby Dragon Egg (Area: -Unknown- - Difficulty: 0) (Auras: )
(@CGUID+603, 190013, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4165.6494140625, 251.326385498046875, 41.16217803955078125, 4.756961822509765625, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Ruby Dragon Egg (Area: -Unknown- - Difficulty: 0)
(@CGUID+604, 190013, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4164.14599609375, 252.3072967529296875, 41.02919387817382812, 1.550756573677062988, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Ruby Dragon Egg (Area: -Unknown- - Difficulty: 0)
(@CGUID+605, 193001, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4152.390625, 291.933868408203125, 38.895263671875, 2.118043422698974609, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Kindlet (Area: -Unknown- - Difficulty: 0)
(@CGUID+606, 186825, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4109.08349609375, 73.16146087646484375, 46.1700286865234375, 3.606156349182128906, 7200, 0, 0, 30938, 2568, 0, 0, 0, 0, 45505), -- Molten Primalist (Area: -Unknown- - Difficulty: 0) (Auras: 42459 - Dual Wield)
(@CGUID+607, 186684, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4102.00341796875, 76.83853912353515625, 94.20147705078125, 1.776496291160583496, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Lava Phoenix (Area: -Unknown- - Difficulty: 0) (Auras: 369897 - -Unknown-)
(@CGUID+608, 186823, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4032.067626953125, 106.0347213745117187, 43.70887374877929687, 2.442488908767700195, 7200, 0, 0, 24750, 6015, 0, 0, 0, 0, 45505), -- Lavacaller Primalist (Area: -Unknown- - Difficulty: 0) (Auras: 387072 - -Unknown-, 364117 - -Unknown-)
(@CGUID+609, 186822, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4053.0390625, 159.517364501953125, 39.502655029296875, 5.937458992004394531, 7200, 0, 0, 23204, 0, 0, 0, 0, 0, 45505), -- Infused Ruby Whelpling (Area: -Unknown- - Difficulty: 0) (Auras: 376690 - -Unknown-)
(@CGUID+610, 186822, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4054.018310546875, 161.123260498046875, 39.568084716796875, 0, 7200, 0, 0, 23204, 0, 0, 0, 0, 0, 45505), -- Infused Ruby Whelpling (Area: -Unknown- - Difficulty: 0) (Auras: 376690 - -Unknown-)
(@CGUID+611, 186822, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4051.647705078125, 158.5746612548828125, 39.43366622924804687, 3.076980113983154296, 7200, 0, 0, 23204, 0, 0, 0, 0, 0, 45505), -- Infused Ruby Whelpling (Area: -Unknown- - Difficulty: 0) (Auras: 376690 - -Unknown-)
(@CGUID+612, 186823, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4024.572998046875, 105.5989608764648437, 44.73847198486328125, 0.993270158767700195, 7200, 0, 0, 24750, 6015, 0, 0, 0, 0, 45505), -- Lavacaller Primalist (Area: -Unknown- - Difficulty: 0) (Auras: 387072 - -Unknown-, 385552 - -Unknown-)
(@CGUID+613, 186823, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4188.4912109375, 180.859375, 49.96422576904296875, 5.898862838745117187, 7200, 10, 0, 24750, 6015, 1, 0, 0, 0, 45505), -- Lavacaller Primalist (Area: -Unknown- - Difficulty: 0) (Auras: 364220 - -Unknown-) (possible waypoints or random movement)
(@CGUID+614, 190080, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4148.16455078125, 128.5796966552734375, 36.36896896362304687, 3.447373151779174804, 7200, 0, 0, 19800, 6015, 0, 0, 0, 0, 45505), -- Tarasek Elementalist (Area: -Unknown- - Difficulty: 0) (Auras: )
(@CGUID+615, 190013, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4113.90625, 104.9756927490234375, 42.8160400390625, 0, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Ruby Dragon Egg (Area: -Unknown- - Difficulty: 0) (Auras: )
(@CGUID+616, 193001, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4068.75, 93.75, 36.952423095703125, 2.035193920135498046, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Kindlet (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+617, 186822, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4111.39306640625, 101.6390304565429687, 42.87614059448242187, 3.532984256744384765, 7200, 0, 0, 23204, 0, 0, 0, 0, 0, 45505), -- Infused Ruby Whelpling (Area: -Unknown- - Difficulty: 0) (Auras: 376690 - -Unknown-)
(@CGUID+618, 186822, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4111.90283203125, 100.9992446899414062, 42.85934829711914062, 3.880508661270141601, 7200, 0, 0, 23204, 0, 0, 0, 0, 0, 45505), -- Infused Ruby Whelpling (Area: -Unknown- - Difficulty: 0) (Auras: 376690 - -Unknown-)
(@CGUID+619, 193001, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4054.1337890625, 89.96929931640625, 39.54726028442382812, 2.041734695434570312, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Kindlet (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+620, 191891, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4198.9130859375, 167.467010498046875, 51.46799468994140625, 5.427973747253417968, 7200, 0, 0, 68064, 0, 0, 0, 0, 0, 45505), -- Sendrax (Area: -Unknown- - Difficulty: 0) (Auras: 112080 - Root Self)
(@CGUID+621, 190013, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4116.767578125, 104.5173568725585937, 42.81405258178710937, 5.937458992004394531, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Ruby Dragon Egg (Area: -Unknown- - Difficulty: 0) (Auras: )
(@CGUID+622, 190013, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4115.4775390625, 105.2048568725585937, 42.80624771118164062, 3.076980113983154296, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Ruby Dragon Egg (Area: -Unknown- - Difficulty: 0) (Auras: )
(@CGUID+623, 186822, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4112.45654296875, 99.76622772216796875, 42.7848358154296875, 3.615808010101318359, 7200, 0, 0, 23204, 0, 0, 0, 0, 0, 45505), -- Infused Ruby Whelpling (Area: -Unknown- - Difficulty: 0) (Auras: 376690 - -Unknown-)
(@CGUID+624, 186834, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4049.569580078125, 25.04340362548828125, 34.37921524047851562, 0.471487104892730712, 7200, 0, 0, 77345, 0, 0, 0, 0, 0, 45505), -- Stubborn Hornswog (Area: -Unknown- - Difficulty: 0)
(@CGUID+625, 186834, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4020.32470703125, 47.63194656372070312, 36.34406661987304687, 1.337960362434387207, 7200, 0, 0, 77345, 0, 0, 0, 0, 0, 45505), -- Stubborn Hornswog (Area: -Unknown- - Difficulty: 0)
(@CGUID+626, 193001, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4063.7587890625, 70.17992401123046875, 37.24892044067382812, 3.780623912811279296, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Kindlet (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+627, 186684, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4177.6337890625, 81.21701812744140625, 68.60773468017578125, 2.31830453872680664, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Lava Phoenix (Area: -Unknown- - Difficulty: 0) (Auras: 369897 - -Unknown-)
(@CGUID+628, 186834, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4180.2021484375, 72.5069427490234375, 35.26210403442382812, 2.372783184051513671, 7200, 0, 0, 77345, 0, 0, 0, 0, 0, 45505), -- Stubborn Hornswog (Area: -Unknown- - Difficulty: 0) (Auras: 391254 - -Unknown-)
(@CGUID+629, 186829, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4081.529541015625, 43.59027862548828125, 48.58345794677734375, 5.896003246307373046, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Spiteful Slug (Area: -Unknown- - Difficulty: 0)
(@CGUID+630, 186823, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4169.50341796875, 109.9184036254882812, 39.61035919189453125, 0.214975684881210327, 7200, 0, 0, 24750, 6015, 0, 0, 0, 0, 45505), -- Lavacaller Primalist (Area: -Unknown- - Difficulty: 0) (Auras: 364118 - -Unknown-)
(@CGUID+631, 190013, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4053.0390625, 159.517364501953125, 39.58598709106445312, 5.937458992004394531, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Ruby Dragon Egg (Area: -Unknown- - Difficulty: 0) (Auras: 384742 - -Unknown-)
(@CGUID+632, 186822, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4051.647705078125, 158.5746612548828125, 39.43366622924804687, 3.076980113983154296, 7200, 0, 0, 23204, 0, 0, 0, 0, 0, 45505), -- Infused Ruby Whelpling (Area: -Unknown- - Difficulty: 0) (Auras: 376690 - -Unknown-)
(@CGUID+633, 186829, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4084.05810546875, 40.28819656372070312, 50.38020706176757812, 3.821721315383911132, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Spiteful Slug (Area: -Unknown- - Difficulty: 0)
(@CGUID+634, 190013, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4051.647705078125, 158.5746612548828125, 39.516998291015625, 3.076980113983154296, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Ruby Dragon Egg (Area: -Unknown- - Difficulty: 0) (Auras: 384742 - -Unknown-)
(@CGUID+635, 186822, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4054.018310546875, 161.123260498046875, 39.568084716796875, 0, 7200, 0, 0, 23204, 0, 0, 0, 0, 0, 45505), -- Infused Ruby Whelpling (Area: -Unknown- - Difficulty: 0) (Auras: 376690 - -Unknown-)
(@CGUID+636, 186822, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4053.0390625, 159.517364501953125, 39.502655029296875, 5.937458992004394531, 7200, 0, 0, 23204, 0, 0, 0, 0, 0, 45505), -- Infused Ruby Whelpling (Area: -Unknown- - Difficulty: 0) (Auras: 376690 - -Unknown-)
(@CGUID+637, 190013, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4054.018310546875, 161.123260498046875, 39.65141677856445312, 0, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Ruby Dragon Egg (Area: -Unknown- - Difficulty: 0) (Auras: 384742 - -Unknown-)
(@CGUID+638, 193001, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4171.3017578125, 96.027862548828125, 37.781829833984375, 2.155245065689086914, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Kindlet (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+639, 186833, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4216.19091796875, 206.73614501953125, 36.39659881591796875, 2.14913487434387207, 7200, 10, 0, 24750, 0, 1, 0, 0, 0, 45505), -- Spiteful Snail (Area: -Unknown- - Difficulty: 0) (Auras: ) (possible waypoints or random movement)
(@CGUID+640, 186823, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4217.3037109375, 162.2083282470703125, 53.85965728759765625, 0.874675333499908447, 7200, 10, 0, 24750, 6015, 1, 0, 0, 0, 45505), -- Lavacaller Primalist (Area: -Unknown- - Difficulty: 0) (Auras: 364220 - -Unknown-) (possible waypoints or random movement)
(@CGUID+641, 186823, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4222.90625, 191.2552032470703125, 41.03125762939453125, 5.202621936798095703, 7200, 10, 0, 24750, 6015, 1, 0, 0, 0, 45505), -- Lavacaller Primalist (Area: -Unknown- - Difficulty: 0) (Auras: 364118 - -Unknown-) (possible waypoints or random movement)
(@CGUID+642, 190013, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4226.3828125, 188.8177032470703125, 42.42166900634765625, 5.937458992004394531, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Ruby Dragon Egg (Area: -Unknown- - Difficulty: 0)
(@CGUID+643, 190013, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4223.33251953125, 187.2447967529296875, 42.50934600830078125, 3.076980113983154296, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Ruby Dragon Egg (Area: -Unknown- - Difficulty: 0)
(@CGUID+644, 190013, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4224.876953125, 188.0243072509765625, 42.4669647216796875, 0, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Ruby Dragon Egg (Area: -Unknown- - Difficulty: 0)
(@CGUID+645, 188666, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4245.73291015625, 264.2991943359375, 55.320037841796875, 0.190002709627151489, 7200, 0, 0, 37126, 0, 0, 0, 0, 0, 45505), -- Unleashed Lavaburst (Area: -Unknown- - Difficulty: 0)
(@CGUID+646, 188666, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4169.1962890625, 268.70660400390625, 39.0670318603515625, 0.626132071018218994, 7200, 0, 0, 37126, 0, 0, 0, 0, 0, 45505), -- Unleashed Lavaburst (Area: -Unknown- - Difficulty: 0) (Auras: 376804 - -Unknown-)
(@CGUID+647, 188666, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4246.6806640625, 100.8975677490234375, 50.55934906005859375, 5.743051052093505859, 7200, 0, 0, 37126, 0, 0, 0, 0, 0, 45505), -- Unleashed Lavaburst (Area: -Unknown- - Difficulty: 0) (Auras: 376861 - -Unknown-)
(@CGUID+648, 180701, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4213.77099609375, 116.21875, 56.51517486572265625, 0, 7200, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- (Bunny) Sessile (Area: -Unknown- - Difficulty: 0) (Auras: )
(@CGUID+649, 186822, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4113.90625, 104.9756927490234375, 42.8160400390625, 0, 7200, 0, 0, 23204, 0, 0, 0, 0, 0, 45505), -- Infused Ruby Whelpling (Area: -Unknown- - Difficulty: 0) (Auras: 376690 - -Unknown-)
(@CGUID+650, 186822, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4116.767578125, 104.5173568725585937, 42.81405258178710937, 5.937458992004394531, 7200, 0, 0, 23204, 0, 0, 0, 0, 0, 45505), -- Infused Ruby Whelpling (Area: -Unknown- - Difficulty: 0) (Auras: 376690 - -Unknown-)
(@CGUID+651, 186822, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4115.4775390625, 105.2048568725585937, 42.80624771118164062, 3.076980113983154296, 7200, 0, 0, 23204, 0, 0, 0, 0, 0, 45505), -- Infused Ruby Whelpling (Area: -Unknown- - Difficulty: 0) (Auras: 376690 - -Unknown-)
(@CGUID+652, 186822, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4053.0390625, 159.517364501953125, 39.502655029296875, 5.937458992004394531, 7200, 0, 0, 23204, 0, 0, 0, 0, 0, 45505), -- Infused Ruby Whelpling (Area: -Unknown- - Difficulty: 0) (Auras: 376690 - -Unknown-)
(@CGUID+653, 186822, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4051.647705078125, 158.5746612548828125, 39.43366622924804687, 3.076980113983154296, 7200, 0, 0, 23204, 0, 0, 0, 0, 0, 45505), -- Infused Ruby Whelpling (Area: -Unknown- - Difficulty: 0) (Auras: 376690 - -Unknown-)
(@CGUID+654, 186822, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4054.018310546875, 161.123260498046875, 39.568084716796875, 0, 7200, 0, 0, 23204, 0, 0, 0, 0, 0, 45505), -- Infused Ruby Whelpling (Area: -Unknown- - Difficulty: 0) (Auras: 376690 - -Unknown-)
(@CGUID+655, 186822, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4113.90625, 104.9756927490234375, 42.8160400390625, 0, 7200, 0, 0, 23204, 0, 0, 0, 0, 0, 45505), -- Infused Ruby Whelpling (Area: -Unknown- - Difficulty: 0) (Auras: 376690 - -Unknown-)
(@CGUID+656, 186822, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4115.4775390625, 105.2048568725585937, 42.80624771118164062, 3.076980113983154296, 7200, 0, 0, 23204, 0, 0, 0, 0, 0, 45505), -- Infused Ruby Whelpling (Area: -Unknown- - Difficulty: 0) (Auras: 376690 - -Unknown-)
(@CGUID+657, 186822, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4116.767578125, 104.5173568725585937, 42.81405258178710937, 5.937458992004394531, 7200, 0, 0, 23204, 0, 0, 0, 0, 0, 45505), -- Infused Ruby Whelpling (Area: -Unknown- - Difficulty: 0) (Auras: 376690 - -Unknown-)
-- (@CGUID+658, 121541, UNKNOWN, 13644, 13709, '0', '0', 0, 0, 0, 0.208347395062446594, 0, 1.873889684677124023, 0, 7200, 10, 0, 2993, 0, 1, 0, 0, 0, 45505), -- Ban-Lu (Area: -Unknown- - Difficulty: 0) (Auras: 46598 - Ride Vehicle Hardcoded) - !!! on transport - transport template not found !!! (possible waypoints or random movement)
(@CGUID+659, 195917, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4089.623291015625, 235.0585784912109375, 43.60144805908203125, 1.593970298767089843, 7200, 0, 0, 68064, 0, 0, 0, 0, 0, 45505), -- Primal Revenant (Area: -Unknown- - Difficulty: 0)
(@CGUID+660, 186822, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4115.4775390625, 105.2048568725585937, 42.80624771118164062, 3.076980113983154296, 7200, 0, 0, 23204, 0, 0, 0, 0, 0, 45505), -- Infused Ruby Whelpling (Area: -Unknown- - Difficulty: 0) (Auras: 376690 - -Unknown-)
(@CGUID+661, 186822, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4113.90625, 104.9756927490234375, 42.8160400390625, 0, 7200, 0, 0, 23204, 0, 0, 0, 0, 0, 45505), -- Infused Ruby Whelpling (Area: -Unknown- - Difficulty: 0) (Auras: 376690 - -Unknown-)
(@CGUID+662, 186822, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4116.767578125, 104.5173568725585937, 42.81405258178710937, 5.937458992004394531, 7200, 0, 0, 23204, 0, 0, 0, 0, 0, 45505), -- Infused Ruby Whelpling (Area: -Unknown- - Difficulty: 0) (Auras: 376690 - -Unknown-)
(@CGUID+663, 191891, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4198.9130859375, 167.467010498046875, 51.46799468994140625, 5.427973747253417968, 7200, 0, 0, 68064, 0, 0, 0, 0, 0, 45505), -- Sendrax (Area: -Unknown- - Difficulty: 0) (Auras: 112080 - Root Self)
(@CGUID+664, 195915, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4027.546875, 109.2135391235351562, 49.32659149169921875, 0.681697845458984375, 7200, 0, 0, 210376, 0, 0, 0, 0, 0, 45505), -- Firava the Rekindler (Area: -Unknown- - Difficulty: 0) (Auras: )
(@CGUID+665, 186823, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4115.1630859375, 108.0347213745117187, 41.90966796875, 4.695329189300537109, 7200, 0, 0, 24750, 6015, 0, 0, 0, 0, 45505), -- Lavacaller Primalist (Area: -Unknown- - Difficulty: 0) (Auras: 364117 - -Unknown-)
(@CGUID+666, 195917, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4068.62939453125, 63.02951431274414062, 39.78319168090820312, 1.048205852508544921, 7200, 0, 0, 68064, 0, 0, 0, 0, 0, 45505), -- Primal Revenant (Area: -Unknown- - Difficulty: 0) (Auras: )
(@CGUID+667, 188666, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4152.94287109375, 56.16336441040039062, 42.44152069091796875, 5.293349742889404296, 7200, 10, 0, 37126, 0, 1, 0, 0, 0, 45505), -- Unleashed Lavaburst (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+668, 195917, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4190.7275390625, 127.7777786254882812, 48.26945114135742187, 2.431846380233764648, 7200, 0, 0, 68064, 0, 0, 0, 0, 0, 45505), -- Primal Revenant (Area: -Unknown- - Difficulty: 0) (Auras: )
(@CGUID+669, 186823, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4095.86279296875, 132.342010498046875, 37.26624679565429687, 4.661814212799072265, 7200, 10, 0, 24750, 6015, 1, 0, 0, 0, 45505), -- Lavacaller Primalist (Area: -Unknown- - Difficulty: 0) (Auras: 364118 - -Unknown-) (possible waypoints or random movement)
(@CGUID+670, 186823, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4139.63037109375, 164.6944427490234375, 37.60822677612304687, 1.660174131393432617, 7200, 0, 0, 24750, 6015, 0, 0, 0, 0, 45505), -- Lavacaller Primalist (Area: -Unknown- - Difficulty: 0) (Auras: 364118 - -Unknown-)
(@CGUID+671, 186823, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4112.11279296875, 53.3211822509765625, 50.15848159790039062, 2.218474388122558593, 7200, 0, 0, 24750, 6015, 0, 0, 0, 0, 45505), -- Lavacaller Primalist (Area: -Unknown- - Difficulty: 0) (Auras: 364153 - -Unknown-)
(@CGUID+672, 188666, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4048.794189453125, 181.51910400390625, 37.92954254150390625, 0.875000715255737304, 7200, 10, 0, 37126, 0, 1, 0, 0, 0, 45505), -- Unleashed Lavaburst (Area: -Unknown- - Difficulty: 0) (Auras: 376765 - -Unknown-) (possible waypoints or random movement)
-- (@CGUID+673, 121541, UNKNOWN, 13644, 13709, '0', '0', 0, 0, 0, 0.208347395062446594, 0, 1.873889684677124023, 0, 7200, 0, 0, 2993, 0, 0, 0, 0, 0, 45505), -- Ban-Lu (Area: -Unknown- - Difficulty: 0) (Auras: 46598 - Ride Vehicle Hardcoded) - !!! on transport - transport template not found !!!
(@CGUID+674, 180701, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4217.5791015625, 108.4253463745117187, 66.29642486572265625, 0, 7200, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- (Bunny) Sessile (Area: -Unknown- - Difficulty: 0) (Auras: )
(@CGUID+675, 190090, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4222.90380859375, 113.3940963745117187, 55.3089447021484375, 0, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Infused Dragon Egg (Area: -Unknown- - Difficulty: 0)
-- (@CGUID+676, 32641, UNKNOWN, 13644, 13709, '0', '0', 0, 0, 0, 0, 0, 0, 0, 7200, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Drix Blackwrench (Area: -Unknown- - Difficulty: 0) (Auras: 61424 - Traveler's Tundra Mammoth) - !!! on transport - transport template not found !!!
-- (@CGUID+677, 32642, UNKNOWN, 13644, 13709, '0', '0', 0, 0, 0, 0, 0, 0, 0, 7200, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Mojodishu (Area: -Unknown- - Difficulty: 0) (Auras: 61424 - Traveler's Tundra Mammoth) - !!! on transport - transport template not found !!!
(@CGUID+678, 180701, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4225.22412109375, 106.895843505859375, 55.93501663208007812, 1.359547972679138183, 7200, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- (Bunny) Sessile (Area: -Unknown- - Difficulty: 0) (Auras: )
(@CGUID+679, 188666, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4266.34619140625, 150.1510467529296875, 61.0211029052734375, 1.204334139823913574, 7200, 0, 0, 37126, 0, 0, 0, 0, 0, 45505), -- Unleashed Lavaburst (Area: -Unknown- - Difficulty: 0) (Auras: 376804 - -Unknown-)
(@CGUID+680, 186684, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4274.8662109375, 65.7100677490234375, 48.41875839233398437, 1.165212869644165039, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Lava Phoenix (Area: -Unknown- - Difficulty: 0) (Auras: 369897 - -Unknown-)
(@CGUID+681, 186822, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4053.0390625, 159.517364501953125, 39.502655029296875, 5.937458992004394531, 7200, 0, 0, 23204, 0, 0, 0, 0, 0, 45505), -- Infused Ruby Whelpling (Area: -Unknown- - Difficulty: 0) (Auras: 376690 - -Unknown-)
(@CGUID+682, 186833, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4234.509765625, 91.923614501953125, 51.53035354614257812, 4.444039344787597656, 7200, 0, 0, 24750, 0, 0, 0, 0, 0, 45505), -- Spiteful Snail (Area: -Unknown- - Difficulty: 0)
(@CGUID+683, 186822, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4051.647705078125, 158.5746612548828125, 39.43366622924804687, 3.076980113983154296, 7200, 0, 0, 23204, 0, 0, 0, 0, 0, 45505), -- Infused Ruby Whelpling (Area: -Unknown- - Difficulty: 0) (Auras: 376690 - -Unknown-)
(@CGUID+684, 186822, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4054.018310546875, 161.123260498046875, 39.568084716796875, 0, 7200, 0, 0, 23204, 0, 0, 0, 0, 0, 45505), -- Infused Ruby Whelpling (Area: -Unknown- - Difficulty: 0) (Auras: 376690 - -Unknown-)
(@CGUID+685, 186822, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4054.018310546875, 161.123260498046875, 39.568084716796875, 0, 7200, 0, 0, 23204, 0, 0, 0, 0, 0, 45505), -- Infused Ruby Whelpling (Area: -Unknown- - Difficulty: 0) (Auras: 376690 - -Unknown-)
(@CGUID+686, 186822, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4051.647705078125, 158.5746612548828125, 39.43366622924804687, 3.076980113983154296, 7200, 0, 0, 23204, 0, 0, 0, 0, 0, 45505), -- Infused Ruby Whelpling (Area: -Unknown- - Difficulty: 0) (Auras: 376690 - -Unknown-)
(@CGUID+687, 186822, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4053.0390625, 159.517364501953125, 39.502655029296875, 5.937458992004394531, 7200, 0, 0, 23204, 0, 0, 0, 0, 0, 45505), -- Infused Ruby Whelpling (Area: -Unknown- - Difficulty: 0) (Auras: 376690 - -Unknown-)
(@CGUID+688, 188372, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4246.60498046875, 127.2314682006835937, 52.57600784301757812, 2.443249225616455078, 7200, 0, 0, 24750, 0, 0, 0, 0, 0, 45505), -- Primal Tarasek (Area: -Unknown- - Difficulty: 0) (Auras: )
(@CGUID+689, 186822, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4113.90625, 104.9756927490234375, 42.8160400390625, 0, 7200, 0, 0, 23204, 0, 0, 0, 0, 0, 45505), -- Infused Ruby Whelpling (Area: -Unknown- - Difficulty: 0) (Auras: 376690 - -Unknown-)
(@CGUID+690, 190013, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4113.90625, 104.9756927490234375, 42.89937210083007812, 0, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Ruby Dragon Egg (Area: -Unknown- - Difficulty: 0) (Auras: 384742 - -Unknown-)
(@CGUID+691, 186822, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4115.4775390625, 105.2048568725585937, 42.80624771118164062, 3.076980113983154296, 7200, 0, 0, 23204, 0, 0, 0, 0, 0, 45505), -- Infused Ruby Whelpling (Area: -Unknown- - Difficulty: 0) (Auras: 376690 - -Unknown-)
(@CGUID+692, 186822, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4116.767578125, 104.5173568725585937, 42.81405258178710937, 5.937458992004394531, 7200, 0, 0, 23204, 0, 0, 0, 0, 0, 45505), -- Infused Ruby Whelpling (Area: -Unknown- - Difficulty: 0) (Auras: 376690 - -Unknown-)
(@CGUID+693, 190013, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4115.4775390625, 105.2048568725585937, 42.88957977294921875, 3.076980113983154296, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Ruby Dragon Egg (Area: -Unknown- - Difficulty: 0) (Auras: 384742 - -Unknown-)
(@CGUID+694, 190013, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4116.767578125, 104.5173568725585937, 42.8973846435546875, 5.937458992004394531, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Ruby Dragon Egg (Area: -Unknown- - Difficulty: 0) (Auras: 384742 - -Unknown-)
(@CGUID+695, 195915, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4027.546875, 109.2135391235351562, 49.32659149169921875, 0.681697845458984375, 7200, 10, 0, 210376, 0, 1, 0, 0, 0, 45505), -- Firava the Rekindler (Area: -Unknown- - Difficulty: 0) (Auras: ) (possible waypoints or random movement)
(@CGUID+696, 186573, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4212.32861328125, 204.127777099609375, 37.18971633911132812, 3.653716325759887695, 7200, 10, 0, 15469, 0, 1, 0, 0, 0, 45505), -- Restless Lava (Area: -Unknown- - Difficulty: 0) (Auras: 370034 - -Unknown-) (possible waypoints or random movement)
(@CGUID+697, 186573, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4213.4072265625, 201.1162872314453125, 37.76373672485351562, 4.123574256896972656, 7200, 10, 0, 15469, 0, 1, 0, 0, 0, 45505), -- Restless Lava (Area: -Unknown- - Difficulty: 0) (Auras: 370034 - -Unknown-) (possible waypoints or random movement)
(@CGUID+698, 186573, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4212.037109375, 200.6905364990234375, 37.96580886840820312, 4.503887176513671875, 7200, 10, 0, 15469, 0, 1, 0, 0, 0, 45505), -- Restless Lava (Area: -Unknown- - Difficulty: 0) (Auras: 370034 - -Unknown-) (possible waypoints or random movement)
(@CGUID+699, 186684, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4273.60888671875, 117.8814239501953125, 126.7891693115234375, 4.621470928192138671, 7200, 10, 0, 30938, 0, 1, 0, 0, 0, 45505), -- Lava Phoenix (Area: -Unknown- - Difficulty: 0) (Auras: 369897 - -Unknown-) (possible waypoints or random movement)
(@CGUID+700, 191891, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4198.9130859375, 167.467010498046875, 51.46799468994140625, 5.427973747253417968, 7200, 0, 0, 68064, 0, 0, 0, 0, 0, 45505), -- Sendrax (Area: -Unknown- - Difficulty: 0) (Auras: 112080 - Root Self)
(@CGUID+701, 186823, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4023.020751953125, 112.5243072509765625, 45.23695755004882812, 5.731539726257324218, 7200, 10, 0, 24750, 6015, 1, 0, 0, 0, 45505), -- Lavacaller Primalist (Area: -Unknown- - Difficulty: 0) (Auras: 387072 - -Unknown-) (possible waypoints or random movement)
(@CGUID+702, 195917, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4117.783203125, 143.0208282470703125, 40.60277938842773437, 4.94258737564086914, 7200, 0, 0, 68064, 0, 0, 0, 0, 0, 45505), -- Primal Revenant (Area: -Unknown- - Difficulty: 0) (Auras: )
(@CGUID+703, 186823, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4024.572998046875, 105.5989608764648437, 44.73847198486328125, 0.993270158767700195, 7200, 10, 0, 24750, 6015, 1, 0, 0, 0, 45505), -- Lavacaller Primalist (Area: -Unknown- - Difficulty: 0) (Auras: 387072 - -Unknown-) (possible waypoints or random movement)
(@CGUID+704, 186823, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4032.067626953125, 106.0347213745117187, 43.70887374877929687, 2.442488908767700195, 7200, 10, 0, 24750, 6015, 1, 0, 0, 0, 45505), -- Lavacaller Primalist (Area: -Unknown- - Difficulty: 0) (Auras: 387072 - -Unknown-) (possible waypoints or random movement)
(@CGUID+705, 186823, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4030.522705078125, 113.8125, 44.17813491821289062, 4.041987895965576171, 7200, 10, 0, 24750, 6015, 1, 0, 0, 0, 45505), -- Lavacaller Primalist (Area: -Unknown- - Difficulty: 0) (Auras: 387072 - -Unknown-) (possible waypoints or random movement)
(@CGUID+706, 186825, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4083.771728515625, 188.0677032470703125, 37.57247543334960937, 1.27814793586730957, 7200, 10, 0, 30938, 2568, 1, 0, 0, 0, 45505), -- Molten Primalist (Area: -Unknown- - Difficulty: 0) (Auras: 364220 - -Unknown-) (possible waypoints or random movement)
(@CGUID+707, 188372, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4244.181640625, 150.83160400390625, 57.26569366455078125, 1.621344804763793945, 7200, 10, 0, 24750, 0, 1, 0, 0, 0, 45505), -- Primal Tarasek (Area: -Unknown- - Difficulty: 0) (Auras: 369706 - -Unknown-) (possible waypoints or random movement)
(@CGUID+708, 186825, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4243.9755859375, 154.904510498046875, 56.86516571044921875, 4.891528129577636718, 7200, 10, 0, 30938, 2568, 1, 0, 0, 0, 45505), -- Molten Primalist (Area: -Unknown- - Difficulty: 0) (Auras: 42459 - Dual Wield) (possible waypoints or random movement)
(@CGUID+709, 186825, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4109.08349609375, 73.16146087646484375, 46.1700286865234375, 3.606156349182128906, 7200, 0, 0, 30938, 2568, 0, 0, 0, 0, 45505), -- Molten Primalist (Area: -Unknown- - Difficulty: 0) (Auras: 42459 - Dual Wield)
(@CGUID+710, 188666, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4048.794189453125, 181.51910400390625, 37.92954254150390625, 0.875000715255737304, 7200, 10, 0, 37126, 0, 1, 0, 0, 0, 45505), -- Unleashed Lavaburst (Area: -Unknown- - Difficulty: 0) (Auras: 376765 - -Unknown-) (possible waypoints or random movement)
(@CGUID+711, 195917, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4190.7275390625, 127.7777786254882812, 48.26945114135742187, 2.431846380233764648, 7200, 10, 0, 68064, 0, 1, 0, 0, 0, 45505), -- Primal Revenant (Area: -Unknown- - Difficulty: 0) (Auras: ) (possible waypoints or random movement)
(@CGUID+712, 186823, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4188.4912109375, 180.859375, 49.96422576904296875, 5.898862838745117187, 7200, 0, 0, 24750, 6015, 0, 0, 0, 0, 45505), -- Lavacaller Primalist (Area: -Unknown- - Difficulty: 0) (Auras: 364220 - -Unknown-)
(@CGUID+713, 190080, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4168.3740234375, 147.470489501953125, 43.88408660888671875, 2.199386119842529296, 7200, 10, 0, 19800, 6015, 1, 0, 0, 0, 45505), -- Tarasek Elementalist (Area: -Unknown- - Difficulty: 0) (Auras: ) (possible waypoints or random movement)
(@CGUID+714, 195917, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4068.62939453125, 63.02951431274414062, 39.78319168090820312, 1.048205852508544921, 7200, 0, 0, 68064, 0, 0, 0, 0, 0, 45505), -- Primal Revenant (Area: -Unknown- - Difficulty: 0) (Auras: )
(@CGUID+715, 195917, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4014.893310546875, 153.404510498046875, 37.58617401123046875, 2.716512680053710937, 7200, 0, 0, 68064, 0, 0, 0, 0, 0, 45505), -- Primal Revenant (Area: -Unknown- - Difficulty: 0) (Auras: )
(@CGUID+716, 186823, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4169.50341796875, 109.9184036254882812, 39.61035919189453125, 0.214975684881210327, 7200, 10, 0, 24750, 6015, 1, 0, 0, 0, 45505), -- Lavacaller Primalist (Area: -Unknown- - Difficulty: 0) (Auras: 364118 - -Unknown-) (possible waypoints or random movement)
(@CGUID+717, 186823, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4112.11279296875, 53.3211822509765625, 50.15848159790039062, 2.218474388122558593, 7200, 10, 0, 24750, 6015, 1, 0, 0, 0, 45505), -- Lavacaller Primalist (Area: -Unknown- - Difficulty: 0) (Auras: 364153 - -Unknown-) (possible waypoints or random movement)
(@CGUID+718, 186823, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4139.63037109375, 164.6944427490234375, 37.60822677612304687, 1.660174131393432617, 7200, 10, 0, 24750, 6015, 1, 0, 0, 0, 45505), -- Lavacaller Primalist (Area: -Unknown- - Difficulty: 0) (Auras: 364118 - -Unknown-) (possible waypoints or random movement)
(@CGUID+719, 186822, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4053.0390625, 159.517364501953125, 39.502655029296875, 5.937458992004394531, 7200, 0, 0, 23204, 0, 0, 0, 0, 0, 45505), -- Infused Ruby Whelpling (Area: -Unknown- - Difficulty: 0) (Auras: 376690 - -Unknown-)
(@CGUID+720, 186822, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4051.647705078125, 158.5746612548828125, 39.43366622924804687, 3.076980113983154296, 7200, 0, 0, 23204, 0, 0, 0, 0, 0, 45505), -- Infused Ruby Whelpling (Area: -Unknown- - Difficulty: 0) (Auras: 376690 - -Unknown-)
(@CGUID+721, 186822, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4054.018310546875, 161.123260498046875, 39.568084716796875, 0, 7200, 0, 0, 23204, 0, 0, 0, 0, 0, 45505), -- Infused Ruby Whelpling (Area: -Unknown- - Difficulty: 0) (Auras: 376690 - -Unknown-)
(@CGUID+722, 191891, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4198.9130859375, 167.467010498046875, 51.46799468994140625, 5.427973747253417968, 7200, 0, 0, 68064, 0, 0, 0, 0, 0, 45505), -- Sendrax (Area: -Unknown- - Difficulty: 0) (Auras: 112080 - Root Self)
(@CGUID+723, 186829, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4244.73291015625, 185.48785400390625, 49.1787109375, 1.719064116477966308, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Spiteful Slug (Area: -Unknown- - Difficulty: 0)
(@CGUID+724, 188666, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4281.31591796875, 208.501739501953125, 37.62152862548828125, 4.940534591674804687, 7200, 0, 0, 37126, 0, 0, 0, 0, 0, 45505), -- Unleashed Lavaburst (Area: -Unknown- - Difficulty: 0) (Auras: 376765 - -Unknown-)
(@CGUID+725, 188667, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4201.53271484375, 282.032562255859375, 50.24972152709960937, 6.152396678924560546, 7200, 0, 0, 68064, 0, 0, 0, 0, 0, 45505), -- Swelling Fire Elemental (Area: -Unknown- - Difficulty: 0)
(@CGUID+726, 186825, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4207.30126953125, 247.4566497802734375, 50.72551345825195312, 4.661996364593505859, 7200, 0, 0, 30938, 2568, 0, 0, 0, 0, 45505), -- Molten Primalist (Area: -Unknown- - Difficulty: 0) (Auras: 42459 - Dual Wield)
(@CGUID+727, 190080, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4151.09228515625, 285.373260498046875, 39.11469650268554687, 4.094286441802978515, 7200, 10, 0, 19800, 6015, 1, 0, 0, 0, 45505), -- Tarasek Elementalist (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+728, 193001, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4170.10888671875, 260.97247314453125, 40.61873245239257812, 1.191645145416259765, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Kindlet (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+729, 195917, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4266.27099609375, 238.3828887939453125, 52.53464126586914062, 2.503450870513916015, 7200, 0, 0, 68064, 0, 0, 0, 0, 0, 45505), -- Primal Revenant (Area: -Unknown- - Difficulty: 0) (Auras: )
(@CGUID+730, 188666, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4166.19287109375, 303.317718505859375, 39.7473297119140625, 6.141798973083496093, 7200, 10, 0, 37126, 0, 1, 0, 0, 0, 45505), -- Unleashed Lavaburst (Area: -Unknown- - Difficulty: 0) (Auras: 376765 - -Unknown-) (possible waypoints or random movement)
(@CGUID+731, 186825, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4243.06787109375, 185.6458282470703125, 49.23328399658203125, 2.27267622947692871, 7200, 0, 0, 30938, 2568, 0, 0, 0, 0, 45505), -- Molten Primalist (Area: -Unknown- - Difficulty: 0) (Auras: 42459 - Dual Wield)
-- (@CGUID+732, 121541, UNKNOWN, 13644, 13709, '0', '0', 0, 0, 0, 0.208347395062446594, 0, 1.873889684677124023, 0, 7200, 0, 0, 2993, 0, 0, 0, 0, 0, 45505), -- Ban-Lu (Area: -Unknown- - Difficulty: 0) (Auras: 46598 - Ride Vehicle Hardcoded) - !!! on transport - transport template not found !!!
(@CGUID+733, 188666, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4251.50537109375, 266.248260498046875, 56.1155548095703125, 0.358104616403579711, 7200, 0, 0, 37126, 0, 0, 0, 0, 0, 45505), -- Unleashed Lavaburst (Area: -Unknown- - Difficulty: 0) (Auras: 376861 - -Unknown-)
(@CGUID+734, 186822, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4053.0390625, 159.517364501953125, 39.502655029296875, 5.937458992004394531, 7200, 0, 0, 23204, 0, 0, 0, 0, 0, 45505), -- Infused Ruby Whelpling (Area: -Unknown- - Difficulty: 0) (Auras: 376690 - -Unknown-)
(@CGUID+735, 186822, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4054.018310546875, 161.123260498046875, 39.568084716796875, 0, 7200, 0, 0, 23204, 0, 0, 0, 0, 0, 45505), -- Infused Ruby Whelpling (Area: -Unknown- - Difficulty: 0) (Auras: 376690 - -Unknown-)
(@CGUID+736, 186822, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4051.647705078125, 158.5746612548828125, 39.43366622924804687, 3.076980113983154296, 7200, 0, 0, 23204, 0, 0, 0, 0, 0, 45505), -- Infused Ruby Whelpling (Area: -Unknown- - Difficulty: 0) (Auras: 376690 - -Unknown-)
(@CGUID+737, 186822, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4051.647705078125, 158.5746612548828125, 39.43366622924804687, 3.076980113983154296, 7200, 0, 0, 23204, 0, 0, 0, 0, 0, 45505), -- Infused Ruby Whelpling (Area: -Unknown- - Difficulty: 0) (Auras: 376690 - -Unknown-)
(@CGUID+738, 186822, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4053.0390625, 159.517364501953125, 39.502655029296875, 5.937458992004394531, 7200, 0, 0, 23204, 0, 0, 0, 0, 0, 45505), -- Infused Ruby Whelpling (Area: -Unknown- - Difficulty: 0) (Auras: 376690 - -Unknown-)
(@CGUID+739, 186822, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4054.018310546875, 161.123260498046875, 39.568084716796875, 0, 7200, 0, 0, 23204, 0, 0, 0, 0, 0, 45505), -- Infused Ruby Whelpling (Area: -Unknown- - Difficulty: 0) (Auras: 376690 - -Unknown-)
(@CGUID+740, 191891, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4198.9130859375, 167.467010498046875, 51.46799468994140625, 5.427973747253417968, 7200, 0, 0, 68064, 0, 0, 0, 0, 0, 45505), -- Sendrax (Area: -Unknown- - Difficulty: 0) (Auras: 112080 - Root Self)
(@CGUID+741, 193001, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4163.4296875, 54.57291793823242187, 38.47380828857421875, 5.261338710784912109, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Kindlet (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+742, 186822, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4115.4775390625, 105.2048568725585937, 42.80624771118164062, 3.076980113983154296, 7200, 0, 0, 23204, 0, 0, 0, 0, 0, 45505), -- Infused Ruby Whelpling (Area: -Unknown- - Difficulty: 0) (Auras: 376690 - -Unknown-)
(@CGUID+743, 186822, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4116.767578125, 104.5173568725585937, 42.81405258178710937, 5.937458992004394531, 7200, 0, 0, 23204, 0, 0, 0, 0, 0, 45505), -- Infused Ruby Whelpling (Area: -Unknown- - Difficulty: 0) (Auras: 376690 - -Unknown-)
(@CGUID+744, 186822, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4113.90625, 104.9756927490234375, 42.8160400390625, 0, 7200, 0, 0, 23204, 0, 0, 0, 0, 0, 45505), -- Infused Ruby Whelpling (Area: -Unknown- - Difficulty: 0) (Auras: 376690 - -Unknown-)
(@CGUID+745, 186825, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4114.77880859375, 226.1770782470703125, 37.4360809326171875, 5.210281848907470703, 7200, 0, 0, 30938, 2568, 0, 0, 0, 0, 45505), -- Molten Primalist (Area: -Unknown- - Difficulty: 0) (Auras: 364117 - -Unknown-)
(@CGUID+746, 186823, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4032.067626953125, 106.0347213745117187, 43.70887374877929687, 2.442488908767700195, 7200, 10, 0, 24750, 6015, 1, 0, 0, 0, 45505), -- Lavacaller Primalist (Area: -Unknown- - Difficulty: 0) (Auras: 387072 - -Unknown-) (possible waypoints or random movement)
(@CGUID+747, 186825, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4083.771728515625, 188.0677032470703125, 37.57247543334960937, 1.27814793586730957, 7200, 10, 0, 30938, 2568, 1, 0, 0, 0, 45505), -- Molten Primalist (Area: -Unknown- - Difficulty: 0) (Auras: 364220 - -Unknown-) (possible waypoints or random movement)
(@CGUID+748, 186823, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4030.522705078125, 113.8125, 44.17813491821289062, 4.041987895965576171, 7200, 10, 0, 24750, 6015, 1, 0, 0, 0, 45505), -- Lavacaller Primalist (Area: -Unknown- - Difficulty: 0) (Auras: 387072 - -Unknown-) (possible waypoints or random movement)
(@CGUID+749, 186823, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4217.3037109375, 162.2083282470703125, 53.85965728759765625, 0.874675333499908447, 7200, 10, 0, 24750, 6015, 1, 0, 0, 0, 45505); -- Lavacaller Primalist (Area: -Unknown- - Difficulty: 0) (Auras: 364220 - -Unknown-) (possible waypoints or random movement)

INSERT INTO `creature` (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnDifficulties`, `PhaseId`, `PhaseGroup`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `wander_distance`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`, `VerifiedBuild`) VALUES
(@CGUID+750, 186823, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4023.020751953125, 112.5243072509765625, 45.23695755004882812, 5.731539726257324218, 7200, 10, 0, 24750, 6015, 1, 0, 0, 0, 45505), -- Lavacaller Primalist (Area: -Unknown- - Difficulty: 0) (Auras: 387072 - -Unknown-, 364117 - -Unknown-) (possible waypoints or random movement)
(@CGUID+751, 186823, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4024.572998046875, 105.5989608764648437, 44.73847198486328125, 0.993270158767700195, 7200, 0, 0, 24750, 6015, 0, 0, 0, 0, 45505), -- Lavacaller Primalist (Area: -Unknown- - Difficulty: 0) (Auras: 387072 - -Unknown-, 385552 - -Unknown-)
(@CGUID+752, 186823, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4188.4912109375, 180.859375, 49.96422576904296875, 5.898862838745117187, 7200, 10, 0, 24750, 6015, 1, 0, 0, 0, 45505), -- Lavacaller Primalist (Area: -Unknown- - Difficulty: 0) (Auras: 364220 - -Unknown-) (possible waypoints or random movement)
(@CGUID+753, 186822, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4116.767578125, 104.5173568725585937, 42.81405258178710937, 3.515198945999145507, 7200, 0, 0, 23204, 0, 0, 0, 0, 0, 45505), -- Infused Ruby Whelpling (Area: -Unknown- - Difficulty: 0) (Auras: 376690 - -Unknown-)
(@CGUID+754, 186822, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4113.90625, 104.9756927490234375, 42.8160400390625, 0, 7200, 0, 0, 23204, 0, 0, 0, 0, 0, 45505), -- Infused Ruby Whelpling (Area: -Unknown- - Difficulty: 0) (Auras: 376690 - -Unknown-)
(@CGUID+755, 186822, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4115.4775390625, 105.2048568725585937, 42.80624771118164062, 3.781827449798583984, 7200, 0, 0, 23204, 0, 0, 0, 0, 0, 45505), -- Infused Ruby Whelpling (Area: -Unknown- - Difficulty: 0) (Auras: 376690 - -Unknown-)
(@CGUID+756, 195915, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4027.546875, 109.2135391235351562, 49.32659149169921875, 0.681697845458984375, 7200, 10, 0, 383628, 0, 1, 0, 0, 0, 45505), -- Firava the Rekindler (Area: -Unknown- - Difficulty: 0) (Auras: ) (possible waypoints or random movement)
(@CGUID+757, 186822, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4116.767578125, 104.5173568725585937, 42.81405258178710937, 5.937458992004394531, 7200, 0, 0, 23204, 0, 0, 0, 0, 0, 45505), -- Infused Ruby Whelpling (Area: -Unknown- - Difficulty: 0) (Auras: 376690 - -Unknown-)
(@CGUID+758, 186822, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4113.90625, 104.9756927490234375, 42.8160400390625, 0, 7200, 0, 0, 23204, 0, 0, 0, 0, 0, 45505), -- Infused Ruby Whelpling (Area: -Unknown- - Difficulty: 0) (Auras: 376690 - -Unknown-)
(@CGUID+759, 186822, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4115.4775390625, 105.2048568725585937, 42.80624771118164062, 3.076980113983154296, 7200, 0, 0, 23204, 0, 0, 0, 0, 0, 45505), -- Infused Ruby Whelpling (Area: -Unknown- - Difficulty: 0) (Auras: 376690 - -Unknown-)
(@CGUID+760, 188666, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4048.794189453125, 181.51910400390625, 37.92954254150390625, 0.875000715255737304, 7200, 10, 0, 37126, 0, 1, 0, 0, 0, 45505), -- Unleashed Lavaburst (Area: -Unknown- - Difficulty: 0) (Auras: 376765 - -Unknown-) (possible waypoints or random movement)
(@CGUID+761, 186823, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4115.1630859375, 108.0347213745117187, 41.90966796875, 4.695329189300537109, 7200, 10, 0, 24750, 6015, 1, 0, 0, 0, 45505), -- Lavacaller Primalist (Area: -Unknown- - Difficulty: 0) (Auras: 364117 - -Unknown-) (possible waypoints or random movement)
(@CGUID+762, 188666, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4151.6708984375, 102.010406494140625, 38.8170318603515625, 2.067410945892333984, 7200, 10, 0, 37126, 0, 1, 0, 0, 0, 45505), -- Unleashed Lavaburst (Area: -Unknown- - Difficulty: 0) (Auras: 376765 - -Unknown-) (possible waypoints or random movement)
(@CGUID+763, 6491, 2444, 13644, 13710, '0', '0', 0, 0, 0, 3276.62158203125, 197.890625, 81.462188720703125, 2.375572681427001953, 7200, 0, 0, 178590, 0, 0, 0, 0, 0, 45505), -- Spirit Healer (Area: -Unknown- - Difficulty: 0) (Auras: 9036 - Ghost, 10848 - Shroud of Death)
(@CGUID+764, 186822, 2444, 13644, 0, '0', '0', 0, 0, 0, 4053.71337890625, 161.41278076171875, 40.63134765625, 0.700303077697753906, 7200, 0, 0, 23204, 0, 0, 0, 0, 0, 45505), -- Infused Ruby Whelpling (Area: 0 - Difficulty: 0) (Auras: 376690 - -Unknown-)
(@CGUID+765, 186823, 2444, 13644, 0, '0', '0', 0, 0, 0, 4027.21240234375, 112.9930343627929687, 45.57647705078125, 0.2980671226978302, 7200, 0, 0, 24750, 6015, 0, 0, 0, 0, 45505), -- Lavacaller Primalist (Area: 0 - Difficulty: 0)
(@CGUID+766, 186823, 2444, 13644, 0, '0', '0', 0, 0, 0, 4031.52197265625, 110.2592849731445312, 45.34749221801757812, 1.418192267417907714, 7200, 0, 0, 24750, 6015, 0, 0, 0, 0, 45505), -- Lavacaller Primalist (Area: 0 - Difficulty: 0)
(@CGUID+767, 186822, 2444, 13644, 0, '0', '0', 0, 0, 0, 4053.24365234375, 160.2801513671875, 40.56427001953125, 0.734101772308349609, 7200, 0, 0, 23204, 0, 0, 0, 0, 0, 45505), -- Infused Ruby Whelpling (Area: 0 - Difficulty: 0) (Auras: 376690 - -Unknown-)
(@CGUID+768, 186823, 2444, 13644, 0, '0', '0', 0, 0, 0, 4030.522705078125, 113.8125, 44.17813491821289062, 0.403242498636245727, 7200, 0, 0, 24750, 6015, 0, 0, 0, 0, 45505), -- Lavacaller Primalist (Area: 0 - Difficulty: 0)
(@CGUID+769, 186822, 2444, 13644, 0, '0', '0', 0, 0, 0, 4051.55126953125, 159.0184326171875, 40.53943634033203125, 0.705067634582519531, 7200, 0, 0, 23204, 0, 0, 0, 0, 0, 45505), -- Infused Ruby Whelpling (Area: 0 - Difficulty: 0) (Auras: 376690 - -Unknown-)
(@CGUID+770, 186823, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4107.4365234375, 49.79166793823242187, 49.30619049072265625, 3.306659936904907226, 7200, 10, 0, 24750, 6015, 1, 0, 0, 0, 45505), -- Lavacaller Primalist (Area: -Unknown- - Difficulty: 0) (Auras: 364153 - -Unknown-) (possible waypoints or random movement)
(@CGUID+771, 186825, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4109.08349609375, 73.16146087646484375, 46.1700286865234375, 3.606156349182128906, 7200, 0, 0, 30938, 2568, 0, 0, 0, 0, 45505), -- Molten Primalist (Area: -Unknown- - Difficulty: 0) (Auras: 42459 - Dual Wield)
(@CGUID+772, 190080, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4155.06005859375, 126.3372573852539062, 37.28163909912109375, 5.001787662506103515, 7200, 0, 0, 19800, 6015, 0, 0, 0, 0, 45505), -- Tarasek Elementalist (Area: -Unknown- - Difficulty: 0)
(@CGUID+773, 195917, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4068.62939453125, 63.02951431274414062, 39.78319168090820312, 1.048205852508544921, 7200, 0, 0, 68064, 0, 0, 0, 0, 0, 45505), -- Primal Revenant (Area: -Unknown- - Difficulty: 0) (Auras: )
(@CGUID+774, 186823, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4095.86279296875, 132.342010498046875, 37.26624679565429687, 4.661814212799072265, 7200, 0, 0, 24750, 6015, 0, 0, 0, 0, 45505), -- Lavacaller Primalist (Area: -Unknown- - Difficulty: 0) (Auras: 364118 - -Unknown-)
(@CGUID+775, 188666, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4151.6708984375, 102.010406494140625, 38.8170318603515625, 2.067410945892333984, 7200, 0, 0, 37126, 0, 0, 0, 0, 0, 45505), -- Unleashed Lavaburst (Area: -Unknown- - Difficulty: 0) (Auras: 376765 - -Unknown-)
(@CGUID+776, 195917, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4089.6240234375, 235.02490234375, 43.59220504760742187, 1.593970298767089843, 7200, 10, 0, 68064, 0, 1, 0, 0, 0, 45505), -- Primal Revenant (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+777, 188666, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4234.62841796875, 139.080322265625, 52.67112350463867187, 3.071621656417846679, 7200, 0, 0, 37126, 0, 0, 0, 0, 0, 45505), -- Unleashed Lavaburst (Area: -Unknown- - Difficulty: 0) (Auras: )
(@CGUID+778, 195917, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4117.783203125, 143.0208282470703125, 40.60277938842773437, 4.94258737564086914, 7200, 10, 0, 68064, 0, 1, 0, 0, 0, 45505), -- Primal Revenant (Area: -Unknown- - Difficulty: 0) (Auras: ) (possible waypoints or random movement)
(@CGUID+779, 186823, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4115.1630859375, 108.0347213745117187, 41.90966796875, 4.695329189300537109, 7200, 10, 0, 24750, 6015, 1, 0, 0, 0, 45505), -- Lavacaller Primalist (Area: -Unknown- - Difficulty: 0) (Auras: 364117 - -Unknown-) (possible waypoints or random movement)
(@CGUID+780, 195917, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4190.7275390625, 127.7777786254882812, 48.26945114135742187, 2.431846380233764648, 7200, 0, 0, 68064, 0, 0, 0, 0, 0, 45505), -- Primal Revenant (Area: -Unknown- - Difficulty: 0) (Auras: )
(@CGUID+781, 188666, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4048.794189453125, 181.51910400390625, 37.92954254150390625, 0.875000715255737304, 7200, 0, 0, 37126, 0, 0, 0, 0, 0, 45505), -- Unleashed Lavaburst (Area: -Unknown- - Difficulty: 0) (Auras: 376765 - -Unknown-)
(@CGUID+782, 195915, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4027.546875, 109.2135391235351562, 49.32659149169921875, 0.681697845458984375, 7200, 10, 0, 123752, 0, 1, 0, 0, 0, 45505), -- Firava the Rekindler (Area: -Unknown- - Difficulty: 0) (Auras: ) (possible waypoints or random movement)
(@CGUID+783, 186823, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4139.63037109375, 164.6944427490234375, 37.60822677612304687, 1.660174131393432617, 7200, 0, 0, 24750, 6015, 0, 0, 0, 0, 45505), -- Lavacaller Primalist (Area: -Unknown- - Difficulty: 0) (Auras: 364118 - -Unknown-)
(@CGUID+784, 186823, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4023.020751953125, 112.5243072509765625, 45.23695755004882812, 5.731539726257324218, 7200, 0, 0, 24750, 6015, 0, 0, 0, 0, 45505), -- Lavacaller Primalist (Area: -Unknown- - Difficulty: 0) (Auras: 387072 - -Unknown-)
(@CGUID+785, 186823, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4032.067626953125, 106.0347213745117187, 43.70887374877929687, 2.442488908767700195, 7200, 0, 0, 24750, 6015, 0, 0, 0, 0, 45505), -- Lavacaller Primalist (Area: -Unknown- - Difficulty: 0) (Auras: 387072 - -Unknown-)
(@CGUID+786, 190080, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4168.3740234375, 147.470489501953125, 43.88408660888671875, 2.199386119842529296, 7200, 0, 0, 19800, 6015, 0, 0, 0, 0, 45505), -- Tarasek Elementalist (Area: -Unknown- - Difficulty: 0) (Auras: 391245 - -Unknown-)
(@CGUID+787, 186823, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4024.572998046875, 105.5989608764648437, 44.73847198486328125, 0.993270158767700195, 7200, 0, 0, 24750, 6015, 0, 0, 0, 0, 45505), -- Lavacaller Primalist (Area: -Unknown- - Difficulty: 0) (Auras: 387072 - -Unknown-)
(@CGUID+788, 186834, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4144.96337890625, 112.3559036254882812, 36.30234909057617187, 2.775829792022705078, 7200, 0, 0, 77345, 0, 0, 0, 0, 0, 45505), -- Stubborn Hornswog (Area: -Unknown- - Difficulty: 0)
(@CGUID+789, 186823, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4030.522705078125, 113.8125, 44.17813491821289062, 4.041987895965576171, 7200, 0, 0, 24750, 6015, 0, 0, 0, 0, 45505), -- Lavacaller Primalist (Area: -Unknown- - Difficulty: 0) (Auras: 387072 - -Unknown-)
(@CGUID+790, 186823, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4188.4912109375, 180.859375, 49.96422576904296875, 5.898862838745117187, 7200, 10, 0, 24750, 6015, 1, 0, 0, 0, 45505), -- Lavacaller Primalist (Area: -Unknown- - Difficulty: 0) (Auras: 364220 - -Unknown-) (possible waypoints or random movement)
(@CGUID+791, 188372, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4232.6845703125, 141.779632568359375, 52.81527328491210937, 2.682453870773315429, 7200, 0, 0, 24750, 0, 0, 0, 0, 0, 45505), -- Primal Tarasek (Area: -Unknown- - Difficulty: 0)
(@CGUID+792, 193001, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4140.27978515625, 153.513885498046875, 38.5968780517578125, 1.736579298973083496, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Kindlet (Area: -Unknown- - Difficulty: 0)
(@CGUID+793, 186823, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4139.63037109375, 164.6944427490234375, 37.60822677612304687, 1.660174131393432617, 7200, 0, 0, 24750, 6015, 0, 0, 0, 0, 45505), -- Lavacaller Primalist (Area: -Unknown- - Difficulty: 0) (Auras: 364118 - -Unknown-)
(@CGUID+794, 188666, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4266.34619140625, 150.1510467529296875, 61.0211029052734375, 1.204334139823913574, 7200, 10, 0, 37126, 0, 1, 0, 0, 0, 45505), -- Unleashed Lavaburst (Area: -Unknown- - Difficulty: 0) (Auras: 376804 - -Unknown-) (possible waypoints or random movement)
(@CGUID+795, 191891, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4198.9130859375, 167.467010498046875, 51.46799468994140625, 5.427973747253417968, 7200, 0, 0, 68064, 0, 0, 0, 0, 0, 45505), -- Sendrax (Area: -Unknown- - Difficulty: 0) (Auras: 112080 - Root Self)
(@CGUID+796, 188372, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4256.166015625, 121.5711822509765625, 52.56245040893554687, 0.338125050067901611, 7200, 0, 0, 24750, 0, 0, 0, 0, 0, 45505), -- Primal Tarasek (Area: -Unknown- - Difficulty: 0)
(@CGUID+797, 186825, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4114.77880859375, 226.1770782470703125, 37.4360809326171875, 5.210281848907470703, 7200, 0, 0, 30938, 2568, 0, 0, 0, 0, 45505), -- Molten Primalist (Area: -Unknown- - Difficulty: 0) (Auras: 42459 - Dual Wield, 364117 - -Unknown-)
(@CGUID+798, 186825, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4119.97998046875, 234.890625, 37.5135955810546875, 6.23626565933227539, 7200, 0, 0, 30938, 2568, 0, 0, 0, 0, 45505), -- Molten Primalist (Area: -Unknown- - Difficulty: 0) (Auras: 42459 - Dual Wield, 364117 - -Unknown-)
(@CGUID+799, 186823, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4222.90625, 191.2552032470703125, 41.03125762939453125, 5.202621936798095703, 7200, 10, 0, 24750, 6015, 1, 0, 0, 0, 45505), -- Lavacaller Primalist (Area: -Unknown- - Difficulty: 0) (Auras: 364118 - -Unknown-) (possible waypoints or random movement)
(@CGUID+800, 188666, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4169.1962890625, 268.70660400390625, 39.0670318603515625, 0.626132071018218994, 7200, 0, 0, 37126, 0, 0, 0, 0, 0, 45505), -- Unleashed Lavaburst (Area: -Unknown- - Difficulty: 0) (Auras: 376804 - -Unknown-)
(@CGUID+801, 186836, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4303.767578125, 205.6666717529296875, 35.62078475952148437, 3.015983104705810546, 7200, 0, 0, 216566, 0, 0, 0, 0, 0, 45505), -- Lava Burster (Area: -Unknown- - Difficulty: 0)
(@CGUID+802, 195917, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4247.361328125, 244.451171875, 50.37990188598632812, 2.878594636917114257, 7200, 0, 0, 68064, 0, 0, 0, 0, 0, 45505), -- Primal Revenant (Area: -Unknown- - Difficulty: 0)
(@CGUID+803, 186825, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4235.57958984375, 231.8226470947265625, 47.213165283203125, 1.749052643775939941, 7200, 0, 0, 30938, 2568, 0, 0, 0, 0, 45505), -- Molten Primalist (Area: -Unknown- - Difficulty: 0) (Auras: 42459 - Dual Wield)
(@CGUID+804, 186825, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4216.205078125, 243.5118255615234375, 50.69236373901367187, 1.231866121292114257, 7200, 0, 0, 30938, 2568, 0, 0, 0, 0, 45505), -- Molten Primalist (Area: -Unknown- - Difficulty: 0) (Auras: 42459 - Dual Wield)
(@CGUID+805, 188666, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4236.681640625, 268.849609375, 52.60345840454101562, 2.22481083869934082, 7200, 0, 0, 37126, 0, 0, 0, 0, 0, 45505), -- Unleashed Lavaburst (Area: -Unknown- - Difficulty: 0)
(@CGUID+806, 186829, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4264.52978515625, 187.8038177490234375, 42.03895187377929687, 3.666288137435913085, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Spiteful Slug (Area: -Unknown- - Difficulty: 0)
(@CGUID+807, 186823, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4237.14599609375, 232.9522552490234375, 47.20816421508789062, 4.257477283477783203, 7200, 0, 0, 24750, 6015, 0, 0, 0, 0, 45505), -- Lavacaller Primalist (Area: -Unknown- - Difficulty: 0)
(@CGUID+808, 191886, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4272.23681640625, 281.782989501953125, 56.60163116455078125, 2.39401412010192871, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Primalist Lava Conduit (Area: -Unknown- - Difficulty: 0)
(@CGUID+809, 186825, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4286.5634765625, 164.076385498046875, 62.48497772216796875, 4.336358547210693359, 7200, 10, 0, 30938, 2568, 1, 0, 0, 0, 45505), -- Molten Primalist (Area: -Unknown- - Difficulty: 0) (Auras: 42459 - Dual Wield) (possible waypoints or random movement)
(@CGUID+810, 186684, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4260.0302734375, 270.461822509765625, 125.8284988403320312, 3.539021015167236328, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Lava Phoenix (Area: -Unknown- - Difficulty: 0) (Auras: 369897 - -Unknown-)
(@CGUID+811, 186823, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4297.87255859375, 146.2569427490234375, 62.60462570190429687, 3.216908216476440429, 7200, 10, 0, 24750, 6015, 1, 0, 0, 0, 45505), -- Lavacaller Primalist (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+812, 193000, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4284.01708984375, 212.400726318359375, 39.2645416259765625, 3.099782943725585937, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Kindlet (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+813, 186823, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4263.421875, 270.81329345703125, 55.13034820556640625, 0.22604776918888092, 7200, 0, 0, 24750, 6015, 0, 0, 0, 0, 45505), -- Lavacaller Primalist (Area: -Unknown- - Difficulty: 0)
(@CGUID+814, 186684, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4281.1962890625, 95.6719818115234375, 196.5792083740234375, 2.402680635452270507, 7200, 10, 0, 30938, 0, 1, 0, 0, 0, 45505), -- Lava Phoenix (Area: -Unknown- - Difficulty: 0) (Auras: 369897 - -Unknown-) (possible waypoints or random movement)
(@CGUID+815, 186825, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4288.3662109375, 275.4530029296875, 55.0999298095703125, 4.022754669189453125, 7200, 0, 0, 30938, 2568, 0, 0, 0, 0, 45505), -- Molten Primalist (Area: -Unknown- - Difficulty: 0) (Auras: 42459 - Dual Wield)
(@CGUID+816, 188667, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4200.9150390625, 282.229156494140625, 50.14209365844726562, 2.202537059783935546, 7200, 0, 0, 68064, 0, 0, 0, 0, 0, 45505), -- Swelling Fire Elemental (Area: -Unknown- - Difficulty: 0) (Auras: )
(@CGUID+817, 186825, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4289.4072265625, 274.16314697265625, 55.09992599487304687, 3.560203790664672851, 7200, 0, 0, 30938, 2568, 0, 0, 0, 0, 45505), -- Molten Primalist (Area: -Unknown- - Difficulty: 0) (Auras: 42459 - Dual Wield)
(@CGUID+818, 186825, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4287.27783203125, 276.024169921875, 72.10443878173828125, 6.052458763122558593, 7200, 0, 0, 30938, 2568, 0, 0, 0, 0, 45505), -- Molten Primalist (Area: -Unknown- - Difficulty: 0) (Auras: 42459 - Dual Wield)
(@CGUID+819, 186834, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4230.8671875, 341.767364501953125, 35.37117385864257812, 2.775829792022705078, 7200, 0, 0, 77345, 0, 0, 0, 0, 0, 45505), -- Stubborn Hornswog (Area: -Unknown- - Difficulty: 0)
(@CGUID+820, 188372, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4279.712890625, 285.040496826171875, 71.996673583984375, 4.866171836853027343, 7200, 0, 0, 24750, 0, 0, 0, 0, 0, 45505), -- Primal Tarasek (Area: -Unknown- - Difficulty: 0)
(@CGUID+821, 186823, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4232.82568359375, 272.873260498046875, 52.81701278686523437, 0.604240894317626953, 7200, 10, 0, 24750, 6015, 1, 0, 0, 0, 45505), -- Lavacaller Primalist (Area: -Unknown- - Difficulty: 0) (Auras: 364118 - -Unknown-) (possible waypoints or random movement)
(@CGUID+822, 186823, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4272.43359375, 287.212493896484375, 72.0785980224609375, 5.413428306579589843, 7200, 0, 0, 24750, 6015, 0, 0, 0, 0, 45505), -- Lavacaller Primalist (Area: -Unknown- - Difficulty: 0)
(@CGUID+823, 188372, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4278.05029296875, 296.673919677734375, 72.1959686279296875, 4.183406829833984375, 7200, 0, 0, 24750, 0, 0, 0, 0, 0, 45505), -- Primal Tarasek (Area: -Unknown- - Difficulty: 0)
(@CGUID+824, 195917, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4183.77783203125, 349.40625, 60.16445541381835937, 5.647832870483398437, 7200, 0, 0, 68064, 0, 0, 0, 0, 0, 45505), -- Primal Revenant (Area: -Unknown- - Difficulty: 0) (Auras: )
(@CGUID+825, 186823, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4286.76171875, 288.93988037109375, 55.3030548095703125, 1.561219573020935058, 7200, 0, 0, 24750, 6015, 0, 0, 0, 0, 45505), -- Lavacaller Primalist (Area: -Unknown- - Difficulty: 0)
(@CGUID+826, 191891, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4198.9130859375, 167.467010498046875, 51.46799468994140625, 5.427973747253417968, 7200, 0, 0, 68064, 0, 0, 0, 0, 0, 45505), -- Sendrax (Area: -Unknown- - Difficulty: 0) (Auras: 112080 - Root Self)
(@CGUID+827, 186825, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4175.30126953125, 368.79339599609375, 58.65067291259765625, 4.870294094085693359, 7200, 0, 0, 30938, 2568, 0, 0, 0, 0, 45505), -- Molten Primalist (Area: -Unknown- - Difficulty: 0) (Auras: 42459 - Dual Wield)
(@CGUID+828, 186833, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4180.640625, 328.220489501953125, 41.27155303955078125, 2.284015893936157226, 7200, 0, 0, 24750, 0, 0, 0, 0, 0, 45505), -- Spiteful Snail (Area: -Unknown- - Difficulty: 0)
(@CGUID+829, 193001, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4192.84912109375, 337.08062744140625, 41.09222030639648437, 6.219560623168945312, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Kindlet (Area: -Unknown- - Difficulty: 0)
(@CGUID+830, 190080, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4203.2578125, 333.79119873046875, 40.10669708251953125, 1.187947034835815429, 7200, 0, 0, 19800, 6015, 0, 0, 0, 0, 45505), -- Tarasek Elementalist (Area: -Unknown- - Difficulty: 0)
(@CGUID+831, 191891, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4198.9130859375, 167.467010498046875, 51.46799468994140625, 5.427973747253417968, 7200, 10, 0, 68064, 0, 1, 0, 0, 0, 45505), -- Sendrax (Area: -Unknown- - Difficulty: 0) (Auras: 112080 - Root Self) (possible waypoints or random movement)
(@CGUID+832, 193001, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4243.08740234375, 362.3074951171875, 38.54860687255859375, 6.058592796325683593, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Kindlet (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+833, 188372, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4238.06689453125, 373.52508544921875, 43.58448410034179687, 1.176032185554504394, 7200, 0, 0, 24750, 0, 0, 0, 0, 0, 45505), -- Primal Tarasek (Area: -Unknown- - Difficulty: 0)
(@CGUID+834, 192186, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4352.1689453125, 338.33734130859375, 20.57475852966308593, 4.647717475891113281, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Territorial Axebeak (Area: -Unknown- - Difficulty: 0)
(@CGUID+835, 188372, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4198.6181640625, 380.758697509765625, 59.87088394165039062, 5.587551116943359375, 7200, 0, 0, 24750, 0, 0, 0, 0, 0, 45505), -- Primal Tarasek (Area: -Unknown- - Difficulty: 0) (Auras: )
(@CGUID+836, 186825, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4173.15478515625, 368.75494384765625, 58.40556716918945312, 3.143716096878051757, 7200, 0, 0, 30938, 2568, 0, 0, 0, 0, 45505), -- Molten Primalist (Area: -Unknown- - Difficulty: 0) (Auras: 42459 - Dual Wield)
(@CGUID+837, 186823, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4182.2421875, 390.153289794921875, 59.81317520141601562, 2.47151350975036621, 7200, 10, 0, 24750, 6015, 1, 0, 0, 0, 45505), -- Lavacaller Primalist (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+838, 192186, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4273.35693359375, 407.631683349609375, 74.626068115234375, 2.222629308700561523, 7200, 10, 0, 9281, 0, 1, 0, 0, 0, 45505), -- Territorial Axebeak (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+839, 193001, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4152.51904296875, 290.24127197265625, 38.97781753540039062, 4.244123458862304687, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Kindlet (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+840, 192186, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4263.48193359375, 397.113983154296875, 121.2982254028320312, 5.328652858734130859, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Territorial Axebeak (Area: -Unknown- - Difficulty: 0)
(@CGUID+841, 186825, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4236.3740234375, 230.7621612548828125, 46.87673568725585937, 0.435728311538696289, 7200, 0, 0, 30938, 2568, 0, 0, 0, 0, 45505), -- Molten Primalist (Area: -Unknown- - Difficulty: 0) (Auras: 42459 - Dual Wield)
(@CGUID+842, 190080, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4204.32275390625, 331.236114501953125, 38.72024917602539062, 5.129250049591064453, 7200, 0, 0, 19800, 6015, 0, 0, 0, 0, 45505), -- Tarasek Elementalist (Area: -Unknown- - Difficulty: 0) (Auras: 364117 - -Unknown-)
(@CGUID+843, 186823, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4238.84912109375, 232.1788177490234375, 46.59148025512695312, 3.516388893127441406, 7200, 0, 0, 24750, 6015, 0, 0, 0, 0, 45505), -- Lavacaller Primalist (Area: -Unknown- - Difficulty: 0) (Auras: 369643 - -Unknown-)
(@CGUID+844, 191891, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4198.9130859375, 167.467010498046875, 51.46799468994140625, 5.427973747253417968, 7200, 0, 0, 68064, 0, 0, 0, 0, 0, 45505), -- Sendrax (Area: -Unknown- - Difficulty: 0) (Auras: 112080 - Root Self)
(@CGUID+845, 188666, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4162.90625, 233.732635498046875, 36.64218902587890625, 3.523369312286376953, 7200, 0, 0, 37126, 0, 0, 0, 0, 0, 45505), -- Unleashed Lavaburst (Area: -Unknown- - Difficulty: 0) (Auras: 376804 - -Unknown-)
(@CGUID+846, 186823, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4124.48095703125, 269.701385498046875, 43.19445419311523437, 2.767912864685058593, 7200, 0, 0, 24750, 6015, 0, 0, 0, 0, 45505), -- Lavacaller Primalist (Area: -Unknown- - Difficulty: 0) (Auras: 364117 - -Unknown-)
(@CGUID+847, 195917, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4190.7275390625, 127.7777786254882812, 48.26945114135742187, 2.431846380233764648, 7200, 0, 0, 68064, 0, 0, 0, 0, 0, 45505), -- Primal Revenant (Area: -Unknown- - Difficulty: 0) (Auras: )
(@CGUID+848, 190080, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4166.703125, 149.7689361572265625, 43.26068496704101562, 2.199449062347412109, 7200, 10, 0, 19800, 6015, 1, 0, 0, 0, 45505), -- Tarasek Elementalist (Area: -Unknown- - Difficulty: 0) (Auras: ) (possible waypoints or random movement)
(@CGUID+849, 186825, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4284.82666015625, 277.289947509765625, 72.00018310546875, 2.855309247970581054, 7200, 0, 0, 30938, 2568, 0, 0, 0, 0, 45505), -- Molten Primalist (Area: -Unknown- - Difficulty: 0) (Auras: 42459 - Dual Wield)
(@CGUID+850, 186573, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4266.080078125, 210.1649322509765625, 37.87145233154296875, 2.783293485641479492, 7200, 0, 0, 15469, 0, 0, 0, 0, 0, 45505), -- Restless Lava (Area: -Unknown- - Difficulty: 0) (Auras: 370034 - -Unknown-)
(@CGUID+851, 186573, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4265.59130859375, 214.6163177490234375, 39.82741546630859375, 2.972561836242675781, 7200, 0, 0, 15469, 0, 0, 0, 0, 0, 45505), -- Restless Lava (Area: -Unknown- - Difficulty: 0) (Auras: 370034 - -Unknown-)
(@CGUID+852, 186573, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4269.791015625, 215.2100677490234375, 39.72488021850585937, 3.20586562156677246, 7200, 0, 0, 15469, 0, 0, 0, 0, 0, 45505), -- Restless Lava (Area: -Unknown- - Difficulty: 0) (Auras: 370034 - -Unknown-)
(@CGUID+853, 188666, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4166.19287109375, 303.317718505859375, 39.7473297119140625, 6.141798973083496093, 7200, 0, 0, 37126, 0, 0, 0, 0, 0, 45505), -- Unleashed Lavaburst (Area: -Unknown- - Difficulty: 0) (Auras: 376765 - -Unknown-)
(@CGUID+854, 186825, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4175.30126953125, 368.79339599609375, 58.65067291259765625, 4.870294094085693359, 7200, 0, 0, 30938, 2568, 0, 0, 0, 0, 45505), -- Molten Primalist (Area: -Unknown- - Difficulty: 0) (Auras: 42459 - Dual Wield)
(@CGUID+855, 191891, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4198.9130859375, 167.467010498046875, 51.46799468994140625, 5.427973747253417968, 7200, 0, 0, 68064, 0, 0, 0, 0, 0, 45505), -- Sendrax (Area: -Unknown- - Difficulty: 0) (Auras: 112080 - Root Self)
(@CGUID+856, 186823, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4133.5537109375, 359.423614501953125, 55.88541412353515625, 4.933979988098144531, 7200, 0, 0, 24750, 6015, 0, 0, 0, 0, 45505), -- Lavacaller Primalist (Area: -Unknown- - Difficulty: 0) (Auras: 364117 - -Unknown-, 391245 - -Unknown-)
(@CGUID+857, 186823, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4106.76416015625, 316.744781494140625, 49.92295074462890625, 1.108824729919433593, 7200, 0, 0, 24750, 6015, 0, 0, 0, 0, 45505), -- Lavacaller Primalist (Area: -Unknown- - Difficulty: 0) (Auras: 364026 - -Unknown-)
(@CGUID+858, 191891, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4198.9130859375, 167.467010498046875, 51.46799468994140625, 5.427973747253417968, 7200, 0, 0, 68064, 0, 0, 0, 0, 0, 45505), -- Sendrax (Area: -Unknown- - Difficulty: 0) (Auras: 112080 - Root Self)
(@CGUID+859, 192186, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4229.32568359375, 416.53753662109375, 129.9518280029296875, 4.033078193664550781, 7200, 10, 0, 9281, 0, 1, 0, 0, 0, 45505), -- Territorial Axebeak (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+860, 193790, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4261.34716796875, 428.861114501953125, 127.3357391357421875, 5.319936275482177734, 7200, 0, 0, 30938, 100, 0, 0, 0, 0, 45505), -- Sundered Supplyhand (Area: -Unknown- - Difficulty: 0)
(@CGUID+861, 193791, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4261.515625, 432.82464599609375, 127.2905426025390625, 5.846897125244140625, 7200, 10, 0, 30938, 100, 1, 0, 0, 0, 45505), -- Sundered Mercenary (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+862, 188372, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4070.45751953125, 317.298614501953125, 50.31597137451171875, 2.73919081687927246, 7200, 0, 0, 24750, 0, 0, 0, 0, 0, 45505), -- Primal Tarasek (Area: -Unknown- - Difficulty: 0)
(@CGUID+863, 190080, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4066.068603515625, 319.166656494140625, 50.44097137451171875, 5.880783557891845703, 7200, 0, 0, 19800, 6015, 0, 0, 0, 0, 45505), -- Tarasek Elementalist (Area: -Unknown- - Difficulty: 0) (Auras: 369706 - -Unknown-)
(@CGUID+864, 188666, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4048.794189453125, 181.51910400390625, 37.92954254150390625, 0.875000715255737304, 7200, 10, 0, 37126, 0, 1, 0, 0, 0, 45505), -- Unleashed Lavaburst (Area: -Unknown- - Difficulty: 0) (Auras: 376765 - -Unknown-) (possible waypoints or random movement)
(@CGUID+865, 193791, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4249.97412109375, 447.73089599609375, 126.7671051025390625, 4.443134784698486328, 7200, 0, 0, 30938, 100, 0, 0, 0, 0, 45505), -- Sundered Mercenary (Area: -Unknown- - Difficulty: 0) (Auras: 162443 - Cosmetic - SitGround and Drink Breakable)
(@CGUID+866, 193790, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4252.046875, 446.2100830078125, 126.7671051025390625, 2.655802249908447265, 7200, 0, 0, 30938, 100, 0, 0, 0, 0, 45505), -- Sundered Supplyhand (Area: -Unknown- - Difficulty: 0)
(@CGUID+867, 192181, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4049.49169921875, 518.9134521484375, 76.8679351806640625, 4.935086250305175781, 7200, 0, 0, 37126, 0, 0, 0, 0, 0, 45505), -- Wild Rockfang (Area: -Unknown- - Difficulty: 0)
(@CGUID+868, 192186, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4253.94091796875, 464.410247802734375, 134.631591796875, 2.125385999679565429, 7200, 10, 0, 9281, 0, 1, 0, 0, 0, 45505), -- Territorial Axebeak (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+869, 192186, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4264.18603515625, 468.53472900390625, 146.8282623291015625, 3.639915943145751953, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Territorial Axebeak (Area: -Unknown- - Difficulty: 0) (Auras: 258247 - -Unknown-)
(@CGUID+870, 192186, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4265.236328125, 466.78472900390625, 146.8277130126953125, 3.259823322296142578, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Territorial Axebeak (Area: -Unknown- - Difficulty: 0) (Auras: 258247 - -Unknown-)
(@CGUID+871, 192186, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4267.86376953125, 472.401031494140625, 132.1295013427734375, 4.213602542877197265, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Territorial Axebeak (Area: -Unknown- - Difficulty: 0) (Auras: 258247 - -Unknown-)
(@CGUID+872, 186823, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4232.82568359375, 272.873260498046875, 52.81701278686523437, 0.604240894317626953, 7200, 0, 0, 24750, 6015, 0, 0, 0, 0, 45505), -- Lavacaller Primalist (Area: -Unknown- - Difficulty: 0) (Auras: 364118 - -Unknown-)
(@CGUID+873, 186825, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4264.8525390625, 297.48785400390625, 58.10816192626953125, 4.085822582244873046, 7200, 10, 0, 30938, 2568, 1, 0, 0, 0, 45505), -- Molten Primalist (Area: -Unknown- - Difficulty: 0) (Auras: 42459 - Dual Wield) (possible waypoints or random movement)
(@CGUID+874, 188666, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4162.90625, 233.732635498046875, 36.64218902587890625, 3.523369312286376953, 7200, 0, 0, 37126, 0, 0, 0, 0, 0, 45505), -- Unleashed Lavaburst (Area: -Unknown- - Difficulty: 0) (Auras: 376804 - -Unknown-)
(@CGUID+875, 188667, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4200.9150390625, 282.229156494140625, 50.14209365844726562, 2.202537059783935546, 7200, 10, 0, 68064, 0, 1, 0, 0, 0, 45505), -- Swelling Fire Elemental (Area: -Unknown- - Difficulty: 0) (Auras: ) (possible waypoints or random movement)
(@CGUID+876, 186825, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4186.8505859375, 265.06597900390625, 44.8202362060546875, 5.894900321960449218, 7200, 10, 0, 30938, 2568, 1, 0, 0, 0, 45505), -- Molten Primalist (Area: -Unknown- - Difficulty: 0) (Auras: 42459 - Dual Wield) (possible waypoints or random movement)
(@CGUID+877, 186828, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4231.845703125, 352.6007080078125, 36.45833206176757812, 3.136598587036132812, 7200, 0, 0, 18563, 0, 0, 0, 0, 0, 45505), -- Hornswog (0.6/0.6 Melee) (Area: -Unknown- - Difficulty: 0)
(@CGUID+878, 186828, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4235.21435546875, 355.26214599609375, 36.60287094116210937, 4.309460639953613281, 7200, 0, 0, 18563, 0, 0, 0, 0, 0, 45505), -- Hornswog (0.6/0.6 Melee) (Area: -Unknown- - Difficulty: 0)
(@CGUID+879, 195915, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4072.462158203125, 153.26806640625, 41.97306442260742187, 1.465095877647399902, 7200, 0, 0, 123752, 0, 0, 0, 0, 0, 45505), -- Firava the Rekindler (Area: -Unknown- - Difficulty: 0) (Auras: )
(@CGUID+880, 186822, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4162.884765625, 253.55035400390625, 40.90608978271484375, 4.411235332489013671, 7200, 0, 0, 23204, 0, 0, 0, 0, 0, 45505), -- Infused Ruby Whelpling (Area: -Unknown- - Difficulty: 0) (Auras: 376690 - -Unknown-)
(@CGUID+881, 186822, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4164.14599609375, 252.3072967529296875, 41.02919387817382812, 1.550756573677062988, 7200, 0, 0, 23204, 0, 0, 0, 0, 0, 45505), -- Infused Ruby Whelpling (Area: -Unknown- - Difficulty: 0) (Auras: 376690 - -Unknown-)
(@CGUID+882, 186822, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4165.6494140625, 251.326385498046875, 41.16217803955078125, 4.756961822509765625, 7200, 0, 0, 23204, 0, 0, 0, 0, 0, 45505), -- Infused Ruby Whelpling (Area: -Unknown- - Difficulty: 0) (Auras: 376690 - -Unknown-)
(@CGUID+883, 186823, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4222.90625, 191.2552032470703125, 41.03125762939453125, 5.202621936798095703, 7200, 0, 0, 24750, 6015, 0, 0, 0, 0, 45505), -- Lavacaller Primalist (Area: -Unknown- - Difficulty: 0) (Auras: 364118 - -Unknown-)
(@CGUID+884, 186823, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4169.50341796875, 109.9184036254882812, 39.61035919189453125, 0.214975684881210327, 7200, 0, 0, 24750, 6015, 0, 0, 0, 0, 45505), -- Lavacaller Primalist (Area: -Unknown- - Difficulty: 0) (Auras: 364118 - -Unknown-)
(@CGUID+885, 191891, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4198.9130859375, 167.467010498046875, 51.46799468994140625, 5.427973747253417968, 7200, 0, 0, 68064, 0, 0, 0, 0, 0, 45505), -- Sendrax (Area: -Unknown- - Difficulty: 0) (Auras: 112080 - Root Self)
(@CGUID+886, 186822, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4056.129638671875, 162.0399017333984375, 39.7806396484375, 0.684543013572692871, 7200, 0, 0, 23204, 0, 0, 0, 0, 0, 45505), -- Infused Ruby Whelpling (Area: -Unknown- - Difficulty: 0) (Auras: 376690 - -Unknown-)
(@CGUID+887, 186822, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4055.04931640625, 161.27288818359375, 39.69599151611328125, 0.670608282089233398, 7200, 0, 0, 23204, 0, 0, 0, 0, 0, 45505), -- Infused Ruby Whelpling (Area: -Unknown- - Difficulty: 0) (Auras: 376690 - -Unknown-)
(@CGUID+888, 186822, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4057.03857421875, 163.1844635009765625, 39.75544357299804687, 2.822537422180175781, 7200, 0, 0, 23204, 0, 0, 0, 0, 0, 45505), -- Infused Ruby Whelpling (Area: -Unknown- - Difficulty: 0) (Auras: 376690 - -Unknown-)
(@CGUID+889, 190269, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4198.9130859375, 167.467010498046875, 51.55132675170898437, 5.427973747253417968, 7200, 0, 0, 68064, 0, 0, 0, 0, 0, 45505), -- Sendrax (Area: -Unknown- - Difficulty: 0)
(@CGUID+890, 195917, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4268.509765625, 236.72222900390625, 52.53775787353515625, 6.208758354187011718, 7200, 0, 0, 68064, 0, 0, 0, 0, 0, 45505), -- Primal Revenant (Area: -Unknown- - Difficulty: 0)
(@CGUID+891, 186823, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4232.82568359375, 272.873260498046875, 52.81701278686523437, 0.604240894317626953, 7200, 0, 0, 24750, 6015, 0, 0, 0, 0, 45505), -- Lavacaller Primalist (Area: -Unknown- - Difficulty: 0) (Auras: 364118 - -Unknown-)
(@CGUID+892, 186823, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4262.09716796875, 268.5657958984375, 72.10305023193359375, 5.311851024627685546, 7200, 10, 0, 24750, 6015, 1, 0, 0, 0, 45505), -- Lavacaller Primalist (Area: -Unknown- - Difficulty: 0) (Auras: 364153 - -Unknown-) (possible waypoints or random movement)
(@CGUID+893, 191891, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4198.9130859375, 167.467010498046875, 51.46799468994140625, 5.21964263916015625, 7200, 0, 0, 68064, 0, 0, 0, 0, 0, 45505), -- Sendrax (Area: -Unknown- - Difficulty: 0) (Auras: 112080 - Root Self)
(@CGUID+894, 190269, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4198.9130859375, 167.467010498046875, 51.46799468994140625, 5.427973747253417968, 7200, 0, 0, 68064, 0, 0, 0, 0, 0, 45505), -- Sendrax (Area: -Unknown- - Difficulty: 0)
(@CGUID+895, 191891, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4227.572265625, 115.9097213745117187, 54.76738739013671875, 5.427973747253417968, 7200, 0, 0, 68064, 0, 0, 0, 0, 0, 45505), -- Sendrax (Area: -Unknown- - Difficulty: 0) (Auras: 112080 - Root Self)
(@CGUID+896, 188372, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4244.181640625, 150.83160400390625, 57.26569366455078125, 1.285179734230041503, 7200, 0, 0, 24750, 0, 0, 0, 0, 0, 45505), -- Primal Tarasek (Area: -Unknown- - Difficulty: 0) (Auras: 369706 - -Unknown-)
(@CGUID+897, 186825, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4243.9755859375, 154.904510498046875, 56.86516571044921875, 4.891528129577636718, 7200, 0, 0, 30938, 2568, 0, 0, 0, 0, 45505), -- Molten Primalist (Area: -Unknown- - Difficulty: 0) (Auras: 42459 - Dual Wield)
(@CGUID+898, 186825, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4243.06787109375, 185.6458282470703125, 49.23328399658203125, 2.27267622947692871, 7200, 0, 0, 30938, 2568, 0, 0, 0, 0, 45505), -- Molten Primalist (Area: -Unknown- - Difficulty: 0) (Auras: 42459 - Dual Wield)
(@CGUID+899, 186825, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4083.771728515625, 188.0677032470703125, 37.57247543334960937, 1.27814793586730957, 7200, 10, 0, 30938, 2568, 1, 0, 0, 0, 45505), -- Molten Primalist (Area: -Unknown- - Difficulty: 0) (Auras: 42459 - Dual Wield, 364220 - -Unknown-) (possible waypoints or random movement)
(@CGUID+900, 186823, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4095.86279296875, 132.342010498046875, 37.26624679565429687, 4.661814212799072265, 7200, 10, 0, 24750, 6015, 1, 0, 0, 0, 45505), -- Lavacaller Primalist (Area: -Unknown- - Difficulty: 0) (Auras: 364118 - -Unknown-) (possible waypoints or random movement)
(@CGUID+901, 191891, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4227.572265625, 115.9097213745117187, 54.68405532836914062, 3.866752862930297851, 7200, 0, 0, 68064, 0, 0, 0, 0, 0, 45505), -- Sendrax (Area: -Unknown- - Difficulty: 0)
(@CGUID+902, 195915, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4027.546875, 109.2135391235351562, 49.32659149169921875, 0.681697845458984375, 7200, 10, 0, 297004, 0, 1, 0, 0, 0, 45505), -- Firava the Rekindler (Area: -Unknown- - Difficulty: 0) (Auras: ) (possible waypoints or random movement)
(@CGUID+903, 191891, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4227.572265625, 115.9097213745117187, 54.76738739013671875, 3.866752862930297851, 7200, 0, 0, 68064, 0, 0, 0, 0, 0, 45505), -- Sendrax (Area: -Unknown- - Difficulty: 0) (Auras: 376704 - -Unknown-)
(@CGUID+904, 186822, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4049.005859375, 162.0565338134765625, 39.30799484252929687, 2.800992012023925781, 7200, 0, 0, 23204, 0, 0, 0, 0, 0, 45505), -- Infused Ruby Whelpling (Area: -Unknown- - Difficulty: 0) (Auras: 376690 - -Unknown-)
(@CGUID+905, 186822, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4049.856201171875, 161.5518341064453125, 39.48648452758789062, 2.788698673248291015, 7200, 0, 0, 23204, 0, 0, 0, 0, 0, 45505), -- Infused Ruby Whelpling (Area: -Unknown- - Difficulty: 0) (Auras: 376690 - -Unknown-)
(@CGUID+906, 186822, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4050.255126953125, 162.3513641357421875, 39.41970062255859375, 2.846128463745117187, 7200, 0, 0, 23204, 0, 0, 0, 0, 0, 45505), -- Infused Ruby Whelpling (Area: -Unknown- - Difficulty: 0) (Auras: 376690 - -Unknown-)
(@CGUID+907, 191891, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4198.9130859375, 167.467010498046875, 51.46799468994140625, 5.427973747253417968, 7200, 0, 0, 68064, 0, 0, 0, 0, 0, 45505), -- Sendrax (Area: -Unknown- - Difficulty: 0) (Auras: 112080 - Root Self)
(@CGUID+908, 186823, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4285.056640625, 291.670135498046875, 55.26926040649414062, 0.763321638107299804, 7200, 0, 0, 24750, 6015, 0, 0, 0, 0, 45505), -- Lavacaller Primalist (Area: -Unknown- - Difficulty: 0)
(@CGUID+909, 190080, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4136.697265625, 386.211822509765625, 61.2968597412109375, 2.833315849304199218, 7200, 0, 0, 19800, 6015, 0, 0, 0, 0, 45505), -- Tarasek Elementalist (Area: -Unknown- - Difficulty: 0) (Auras: 391245 - -Unknown-)
(@CGUID+910, 186822, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4112.79345703125, 112.008636474609375, 42.26089096069335937, 1.848525404930114746, 7200, 0, 0, 23204, 0, 0, 0, 0, 0, 45505), -- Infused Ruby Whelpling (Area: -Unknown- - Difficulty: 0) (Auras: 376690 - -Unknown-)
(@CGUID+911, 186822, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4109.54541015625, 115.3218460083007812, 40.51051712036132812, 2.278467178344726562, 7200, 0, 0, 23204, 0, 0, 0, 0, 0, 45505), -- Infused Ruby Whelpling (Area: -Unknown- - Difficulty: 0) (Auras: 376690 - -Unknown-)
(@CGUID+912, 186822, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4109.03759765625, 115.799835205078125, 40.15565109252929687, 2.26917433738708496, 7200, 0, 0, 23204, 0, 0, 0, 0, 0, 45505), -- Infused Ruby Whelpling (Area: -Unknown- - Difficulty: 0) (Auras: 376690 - -Unknown-)
(@CGUID+913, 195917, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4117.783203125, 143.0208282470703125, 40.60277938842773437, 4.94258737564086914, 7200, 0, 0, 68064, 0, 0, 0, 0, 0, 45505), -- Primal Revenant (Area: -Unknown- - Difficulty: 0)
(@CGUID+914, 186823, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4217.3037109375, 162.2083282470703125, 53.85965728759765625, 0.874675333499908447, 7200, 0, 0, 24750, 6015, 0, 0, 0, 0, 45505), -- Lavacaller Primalist (Area: -Unknown- - Difficulty: 0) (Auras: 364220 - -Unknown-)
(@CGUID+915, 186684, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4085.007080078125, 232.7899322509765625, 66.44589996337890625, 1.987561821937561035, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Lava Phoenix (Area: -Unknown- - Difficulty: 0) (Auras: 369897 - -Unknown-)
(@CGUID+916, 191817, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4002.17724609375, 418.811004638671875, 63.6634521484375, 3.714937686920166015, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Shores Snake (Area: -Unknown- - Difficulty: 0)
(@CGUID+917, 186684, 2444, 13644, 13709, '0', '0', 0, 0, 0, 4126.7431640625, 192.2309112548828125, 52.50007247924804687, 3.618374586105346679, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Lava Phoenix (Area: -Unknown- - Difficulty: 0) (Auras: 369897 - -Unknown-)
(@CGUID+918, 192182, 2444, 13644, 13709, '0', '0', 0, 0, 0, 3944.819580078125, 464.58160400390625, 86.8093109130859375, 1.499875903129577636, 7200, 10, 0, 68064, 0, 1, 0, 0, 0, 45505), -- Rockfang Hunter (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+919, 191817, 2444, 13644, 13709, '0', '0', 0, 0, 0, 3969.8720703125, 435.560638427734375, 61.23737335205078125, 1.741838574409484863, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Shores Snake (Area: -Unknown- - Difficulty: 0)
(@CGUID+920, 191817, 2444, 13644, 13709, '0', '0', 0, 0, 0, 3946.962158203125, 422.50726318359375, 82.34033203125, 5.425889492034912109, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Shores Snake (Area: -Unknown- - Difficulty: 0)
-- (@CGUID+921, 62821, UNKNOWN, 13644, 13709, '0', '0', 0, 0, 0, -0.20000000298023223, 0, -0.20000000298023223, 0, 7200, 0, 0, 158747, 10794, 0, 0, 0, 0, 45505), -- Mystic Birdhat (Area: -Unknown- - Difficulty: 0) (Auras: 122729 - Grand Expedition Yak) - !!! on transport - transport template not found !!!
-- (@CGUID+922, 62822, UNKNOWN, 13644, 13709, '0', '0', 0, 0, 0, -0.20000000298023223, 0, -0.20000000298023223, 0, 7200, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Cousin Slowhands (Area: -Unknown- - Difficulty: 0) (Auras: 122729 - Grand Expedition Yak) - !!! on transport - transport template not found !!!
(@CGUID+923, 191553, 2444, 13644, 14107, '0', '0', 0, 0, 0, 3662.28564453125, 315.642364501953125, 28.83357810974121093, 0.620787084102630615, 7200, 0, 0, 24750, 0, 0, 0, 0, 0, 45505), -- Wild Argali (Area: -Unknown- - Difficulty: 0)
(@CGUID+924, 191553, 2444, 13644, 14107, '0', '0', 0, 0, 0, 3658.779541015625, 322.10589599609375, 27.86701202392578125, 4.927873611450195312, 7200, 0, 0, 24750, 0, 0, 0, 0, 0, 45505), -- Wild Argali (Area: -Unknown- - Difficulty: 0)
(@CGUID+925, 190155, 2444, 13644, 14107, '0', '0', 0, 0, 0, 3735.421142578125, 267.196197509765625, 71.1356353759765625, 4.760540485382080078, 7200, 0, 0, 49500, 6015, 0, 0, 0, 0, 45505), -- Caretaker Azkra (Area: -Unknown- - Difficulty: 0)
(@CGUID+926, 186795, 2444, 13644, 14107, '0', '0', 0, 0, 0, 3619.75, 124.1959991455078125, 120.3209991455078125, 1.500725746154785156, 7200, 0, 0, 185628, 0, 0, 0, 0, 0, 45505), -- Majordomo Selistra (Area: -Unknown- - Difficulty: 0)
(@CGUID+927, 191892, 2444, 13644, 14107, '0', '0', 0, 0, 0, 3735.74560546875, 262.555572509765625, 72.86126708984375, 0, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Infused Dragon Egg (Area: -Unknown- - Difficulty: 0) (Auras: )
(@CGUID+928, 191892, 2444, 13644, 14107, '0', '0', 0, 0, 0, 3735.74560546875, 262.555572509765625, 72.77793121337890625, 0, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Infused Dragon Egg (Area: -Unknown- - Difficulty: 0)
(@CGUID+929, 194524, 2444, 13644, 14107, '0', '0', 0, 0, 0, 3748.3681640625, 454.5694580078125, 98.41986083984375, 2.728508710861206054, 7200, 0, 0, 185628, 0, 0, 0, 0, 0, 45505), -- Earthshatter Elemental (Area: -Unknown- - Difficulty: 0) (Auras: 377717 - -Unknown-)
(@CGUID+930, 194517, 2444, 13644, 14107, '0', '0', 0, 0, 0, 3727.3740234375, 461.541229248046875, 73.8456878662109375, 4.407822132110595703, 7200, 0, 0, 46407, 0, 0, 0, 0, 0, 45505), -- Crushing Elemental (Area: -Unknown- - Difficulty: 0)
(@CGUID+931, 194523, 2444, 13644, 14107, '0', '0', 0, 0, 0, 3673.472412109375, 479.98272705078125, 42.1877593994140625, 2.268921136856079101, 7200, 0, 0, 77345, 0, 0, 0, 0, 0, 45505), -- Raging Elemental (Area: -Unknown- - Difficulty: 0) (Auras: 381535 - -Unknown-)
(@CGUID+932, 194517, 2444, 13644, 14107, '0', '0', 0, 0, 0, 3673.865478515625, 480.4154052734375, 42.24273300170898437, 2.430353164672851562, 7200, 0, 0, 46407, 0, 0, 0, 0, 0, 45505), -- Crushing Elemental (Area: -Unknown- - Difficulty: 0)
(@CGUID+933, 186795, 2444, 13644, 14107, '0', '0', 0, 0, 0, 3722.475830078125, 259.6319580078125, 69.86608123779296875, 0.407067358493804931, 7200, 0, 0, 185628, 0, 0, 0, 0, 0, 45505), -- Majordomo Selistra (Area: -Unknown- - Difficulty: 0)
(@CGUID+934, 191768, 2444, 13644, 14107, '0', '0', 0, 0, 0, 3722.475830078125, 259.6319580078125, 69.86608123779296875, 0.407067358493804931, 7200, 0, 0, 185628, 0, 0, 0, 0, 0, 45505), -- Majordomo Selistra (Area: -Unknown- - Difficulty: 0) (Auras: 374008 - -Unknown-, 360001 - -Unknown-)
(@CGUID+935, 190660, 2444, 13644, 0, '0', '0', 0, 0, 0, 3395.315185546875, 239.44097900390625, 88.9611053466796875, 0, 7200, 0, 0, 21657, 0, 0, 0, 0, 0, 45505), -- Cautious Duck (Area: 0 - Difficulty: 0)
(@CGUID+936, 190660, 2444, 13644, 0, '0', '0', 0, 0, 0, 3390.33935546875, 244.326385498046875, 89.29590606689453125, 3.78924727439880371, 7200, 0, 0, 21657, 0, 0, 0, 0, 0, 45505), -- Cautious Duck (Area: 0 - Difficulty: 0)
(@CGUID+937, 190660, 2444, 13644, 0, '0', '0', 0, 0, 0, 3366.25, 268.032989501953125, 65.7536773681640625, 0.96368718147277832, 7200, 0, 0, 21657, 0, 0, 0, 0, 0, 45505), -- Cautious Duck (Area: 0 - Difficulty: 0)
(@CGUID+938, 190660, 2444, 13644, 0, '0', '0', 0, 0, 0, 3314.817626953125, 179.6215362548828125, 145.399322509765625, 1.100801706314086914, 7200, 0, 0, 21657, 0, 0, 0, 0, 0, 45505), -- Cautious Duck (Area: 0 - Difficulty: 0)
(@CGUID+939, 190660, 2444, 13644, 0, '0', '0', 0, 0, 0, 3288.572998046875, 186.736114501953125, 123.5788040161132812, 1.983004093170166015, 7200, 0, 0, 21657, 0, 0, 0, 0, 0, 45505), -- Cautious Duck (Area: 0 - Difficulty: 0)
(@CGUID+940, 191809, 2444, 13644, 0, '0', '0', 0, 0, 0, 3265.330810546875, 172.404327392578125, 78.9240570068359375, 2.06351327896118164, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Tiny Butterfly (Area: 0 - Difficulty: 0)
(@CGUID+941, 191809, 2444, 13644, 0, '0', '0', 0, 0, 0, 3302.851318359375, 248.2823333740234375, 78.02587127685546875, 1.692067742347717285, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Tiny Butterfly (Area: 0 - Difficulty: 0)
(@CGUID+942, 191809, 2444, 13644, 0, '0', '0', 0, 0, 0, 3285.8984375, 226.5006866455078125, 80.7206878662109375, 3.483311176300048828, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Tiny Butterfly (Area: 0 - Difficulty: 0)
(@CGUID+943, 191809, 2444, 13644, 13710, '0', '0', 0, 0, 0, 3254.817626953125, 105.3966217041015625, 90.5669708251953125, 2.265586376190185546, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Tiny Butterfly (Area: -Unknown- - Difficulty: 0)
(@CGUID+944, 191809, 2444, 13644, 13710, '0', '0', 0, 0, 0, 3276.7021484375, 220.30780029296875, 79.3662567138671875, 5.417633056640625, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Tiny Butterfly (Area: -Unknown- - Difficulty: 0)
(@CGUID+945, 191809, 2444, 13644, 13710, '0', '0', 0, 0, 0, 3265.043212890625, 166.4258575439453125, 75.14426422119140625, 2.725332975387573242, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Tiny Butterfly (Area: -Unknown- - Difficulty: 0)
(@CGUID+946, 191809, 2444, 13644, 13710, '0', '0', 0, 0, 0, 3255.99560546875, 109.055633544921875, 82.44025421142578125, 2.563611030578613281, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Tiny Butterfly (Area: -Unknown- - Difficulty: 0)
(@CGUID+947, 191809, 2444, 13644, 13710, '0', '0', 0, 0, 0, 3368.24951171875, 121.4746017456054687, 32.26900100708007812, 3.435434341430664062, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Tiny Butterfly (Area: -Unknown- - Difficulty: 0)
(@CGUID+948, 191809, 2444, 13644, 13710, '0', '0', 0, 0, 0, 3360.56494140625, 126.9023361206054687, 28.71985816955566406, 5.985992908477783203, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Tiny Butterfly (Area: -Unknown- - Difficulty: 0)
(@CGUID+949, 191809, 2444, 13644, 13710, '0', '0', 0, 0, 0, 3307.222412109375, 35.51514053344726562, 76.9208526611328125, 0.614502549171447753, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Tiny Butterfly (Area: -Unknown- - Difficulty: 0)
(@CGUID+950, 191809, 2444, 13644, 13710, '0', '0', 0, 0, 0, 3362.97998046875, 101.163787841796875, 31.36626815795898437, 2.131372690200805664, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Tiny Butterfly (Area: -Unknown- - Difficulty: 0)
(@CGUID+951, 191809, 2444, 13644, 13710, '0', '0', 0, 0, 0, 3263.107177734375, 54.53620147705078125, 80.7375335693359375, 1.998549699783325195, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Tiny Butterfly (Area: -Unknown- - Difficulty: 0)
(@CGUID+952, 191796, 2444, 13644, 13710, '0', '0', 0, 0, 0, 3225.773193359375, 7.942324161529541015, 75.41327667236328125, 0.354171216487884521, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Tiny Drop (Area: -Unknown- - Difficulty: 0)
(@CGUID+953, 191796, 2444, 13644, 13710, '0', '0', 0, 0, 0, 3253.42626953125, -11.2447805404663085, 74.81682586669921875, 3.719148635864257812, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Tiny Drop (Area: -Unknown- - Difficulty: 0)
(@CGUID+954, 197732, 2444, 13644, 13710, '0', '0', 0, 0, 0, 3184.951416015625, 138.3645782470703125, 284.469696044921875, 5.811539649963378906, 7200, 0, 0, 61876, 0, 0, 0, 0, 0, 45505), -- Ruby Warden (Area: -Unknown- - Difficulty: 0)
(@CGUID+955, 191809, 2444, 13644, 13710, '0', '0', 0, 0, 0, 3273.341552734375, -49.2171592712402343, 83.872314453125, 2.526453971862792968, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Tiny Butterfly (Area: -Unknown- - Difficulty: 0)
(@CGUID+956, 191796, 2444, 13644, 13710, '0', '0', 0, 0, 0, 3220.281982421875, -24.3935184478759765, 74.84342193603515625, 5.88601541519165039, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Tiny Drop (Area: -Unknown- - Difficulty: 0)
(@CGUID+957, 191796, 2444, 13644, 13710, '0', '0', 0, 0, 0, 3232.850341796875, -15.9033746719360351, 74.66796112060546875, 1.845609784126281738, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Tiny Drop (Area: -Unknown- - Difficulty: 0)
(@CGUID+958, 191796, 2444, 13644, 13710, '0', '0', 0, 0, 0, 3238.9677734375, -44.9531707763671875, 74.6181640625, 4.67093515396118164, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Tiny Drop (Area: -Unknown- - Difficulty: 0)
(@CGUID+959, 191809, 2444, 13644, 13710, '0', '0', 0, 0, 0, 3172.615966796875, -29.2331676483154296, 92.84784698486328125, 2.586988449096679687, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Tiny Butterfly (Area: -Unknown- - Difficulty: 0)
(@CGUID+960, 191809, 2444, 13644, 13710, '0', '0', 0, 0, 0, 3141.468994140625, -24.3793010711669921, 95.30603790283203125, 4.813775062561035156, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Tiny Butterfly (Area: -Unknown- - Difficulty: 0)
(@CGUID+961, 191809, 2444, 13644, 13710, '0', '0', 0, 0, 0, 3136.23974609375, -64.2516021728515625, 92.93663787841796875, 0.127672016620635986, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Tiny Butterfly (Area: -Unknown- - Difficulty: 0)
(@CGUID+962, 191653, 2444, 13644, 13710, '0', '0', 0, 0, 0, 3241.413818359375, -132.09521484375, 4.104074478149414062, 4.091728687286376953, 7200, 0, 0, 37126, 0, 0, 0, 0, 0, 45505), -- Coastal Salamanther (Area: -Unknown- - Difficulty: 0)
(@CGUID+963, 191653, 2444, 13644, 13710, '0', '0', 0, 0, 0, 3175.45458984375, -132.099945068359375, 4.127840042114257812, 5.557575225830078125, 7200, 0, 0, 37126, 0, 0, 0, 0, 0, 45505), -- Coastal Salamanther (Area: -Unknown- - Difficulty: 0)
(@CGUID+964, 191553, 2444, 13644, 13710, '0', '0', 0, 0, 0, 3097.21337890625, -61.1506004333496093, 95.705474853515625, 3.928327083587646484, 7200, 0, 0, 24750, 0, 0, 0, 0, 0, 45505), -- Wild Argali (Area: -Unknown- - Difficulty: 0)
(@CGUID+965, 191554, 2444, 13644, 13710, '0', '0', 0, 0, 0, 3100.635009765625, -58.1967391967773437, 94.9165496826171875, 4.14450836181640625, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Argali Lamb (Area: -Unknown- - Difficulty: 0)
(@CGUID+966, 191624, 2444, 13644, 0, '0', '0', 0, 0, 0, 3162.394775390625, -213.579437255859375, 45.37289047241210937, 5.321115016937255859, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Tranquil Vorquin (Area: 0 - Difficulty: 0)
(@CGUID+967, 191553, 2444, 13644, 0, '0', '0', 0, 0, 0, 3093.330078125, -57.6786422729492187, 95.0989990234375, 3.95501875877380371, 7200, 0, 0, 24750, 0, 0, 0, 0, 0, 45505), -- Wild Argali (Area: 0 - Difficulty: 0)
(@CGUID+968, 191653, 2444, 13644, 0, '0', '0', 0, 0, 0, 3125.43994140625, -136.6749267578125, 4.936408042907714843, 0.566638708114624023, 7200, 0, 0, 37126, 0, 0, 0, 0, 0, 45505), -- Coastal Salamanther (Area: 0 - Difficulty: 0)
(@CGUID+969, 191624, 2444, 13644, 0, '0', '0', 0, 0, 0, 3213.078125, -227.835067749023437, 44.74393463134765625, 1.990824699401855468, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Tranquil Vorquin (Area: 0 - Difficulty: 0)
(@CGUID+970, 191792, 2444, 13644, 0, '0', '0', 0, 0, 0, 3251.663818359375, -113.081466674804687, 4.578073501586914062, 1.052982211112976074, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Frog (Area: 0 - Difficulty: 0)
(@CGUID+971, 191656, 2444, 13644, 0, '0', '0', 0, 0, 0, 3205.927978515625, -208.072830200195312, 4.739570140838623046, 3.701461315155029296, 7200, 0, 0, 15469, 0, 0, 0, 0, 0, 45505), -- Young Salamanther (Area: 0 - Difficulty: 0)
(@CGUID+972, 191792, 2444, 13644, 0, '0', '0', 0, 0, 0, 3220.089111328125, -138.123703002929687, 4.078271865844726562, 5.300829887390136718, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Frog (Area: 0 - Difficulty: 0)
(@CGUID+973, 191554, 2444, 13644, 0, '0', '0', 0, 0, 0, 3096.80517578125, -32.8313446044921875, 92.57326507568359375, 0.777111053466796875, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Argali Lamb (Area: 0 - Difficulty: 0)
(@CGUID+974, 191653, 2444, 13644, 0, '0', '0', 0, 0, 0, 3160.392578125, -197.108734130859375, 4.379649162292480468, 2.875027894973754882, 7200, 0, 0, 37126, 0, 0, 0, 0, 0, 45505), -- Coastal Salamanther (Area: 0 - Difficulty: 0)
(@CGUID+975, 191792, 2444, 13644, 0, '0', '0', 0, 0, 0, 3165.862060546875, -141.67718505859375, 4.221780776977539062, 5.88790750503540039, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Frog (Area: 0 - Difficulty: 0)
(@CGUID+976, 191656, 2444, 13644, 0, '0', '0', 0, 0, 0, 3175.8076171875, -182.5546875, 4.293354034423828125, 1.878341555595397949, 7200, 0, 0, 15469, 0, 0, 0, 0, 0, 45505), -- Young Salamanther (Area: 0 - Difficulty: 0)
(@CGUID+977, 191625, 2444, 13644, 0, '0', '0', 0, 0, 0, 3151.488037109375, -207.941802978515625, 46.95456695556640625, 4.341507911682128906, 7200, 0, 0, 15469, 0, 0, 0, 0, 0, 45505), -- Vorquin Foal (Area: 0 - Difficulty: 0)
(@CGUID+978, 191656, 2444, 13644, 0, '0', '0', 0, 0, 0, 3146.1044921875, -125.318359375, 8.688409805297851562, 2.245553255081176757, 7200, 0, 0, 15469, 0, 0, 0, 0, 0, 45505), -- Young Salamanther (Area: 0 - Difficulty: 0)
(@CGUID+979, 191809, 2444, 13644, 0, '0', '0', 0, 0, 0, 3087.4287109375, -36.4948997497558593, 96.91593170166015625, 4.625614166259765625, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Tiny Butterfly (Area: 0 - Difficulty: 0)
(@CGUID+980, 191792, 2444, 13644, 0, '0', '0', 0, 0, 0, 3296.31396484375, -109.676536560058593, 4.247035980224609375, 6.195353507995605468, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Frog (Area: 0 - Difficulty: 0)
(@CGUID+981, 191656, 2444, 13644, 0, '0', '0', 0, 0, 0, 3111.255126953125, -194.029281616210937, 4.246671199798583984, 4.626539230346679687, 7200, 0, 0, 15469, 0, 0, 0, 0, 0, 45505), -- Young Salamanther (Area: 0 - Difficulty: 0)
(@CGUID+982, 191653, 2444, 13644, 0, '0', '0', 0, 0, 0, 3122.998291015625, -193.928817749023437, 4.383857250213623046, 0.973470032215118408, 7200, 0, 0, 37126, 0, 0, 0, 0, 0, 45505), -- Coastal Salamanther (Area: 0 - Difficulty: 0)
(@CGUID+983, 191792, 2444, 13644, 0, '0', '0', 0, 0, 0, 3281.77392578125, -135.1162109375, 3.7055816650390625, 1.181315779685974121, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Frog (Area: 0 - Difficulty: 0)
(@CGUID+984, 192069, 2444, 13644, 0, '0', '0', 0, 0, 0, 3161.48583984375, -203.04742431640625, 44.85340118408203125, 3.236620187759399414, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Vorquin Runt (Area: 0 - Difficulty: 0)
(@CGUID+985, 191625, 2444, 13644, 0, '0', '0', 0, 0, 0, 3167.891845703125, -219.931396484375, 44.9432830810546875, 0.192708879709243774, 7200, 0, 0, 15469, 0, 0, 0, 0, 0, 45505), -- Vorquin Foal (Area: 0 - Difficulty: 0)
(@CGUID+986, 192059, 2444, 13644, 0, '0', '0', 0, 0, 0, 3145.5595703125, -194.726821899414062, 4.466571331024169921, 1.885581731796264648, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Palamanther (Area: 0 - Difficulty: 0)
(@CGUID+987, 191792, 2444, 13644, 0, '0', '0', 0, 0, 0, 3154.330810546875, -191.004608154296875, 4.158033370971679687, 3.767230510711669921, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Frog (Area: 0 - Difficulty: 0)
(@CGUID+988, 191792, 2444, 13644, 0, '0', '0', 0, 0, 0, 3231.169677734375, -206.83807373046875, 4.220354080200195312, 0.50275588035583496, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Frog (Area: 0 - Difficulty: 0)
(@CGUID+989, 191809, 2444, 13644, 0, '0', '0', 0, 0, 0, 3066.995849609375, -82.9331588745117187, 100.0983734130859375, 3.108901739120483398, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Tiny Butterfly (Area: 0 - Difficulty: 0)
(@CGUID+990, 191792, 2444, 13644, 0, '0', '0', 0, 0, 0, 3099.445068359375, -137.646438598632812, 4.111736297607421875, 3.365142822265625, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Frog (Area: 0 - Difficulty: 0)
(@CGUID+991, 191656, 2444, 13644, 0, '0', '0', 0, 0, 0, 3041.46875, -179.512161254882812, 5.329234123229980468, 0.963479399681091308, 7200, 0, 0, 15469, 0, 0, 0, 0, 0, 45505), -- Young Salamanther (Area: 0 - Difficulty: 0)
(@CGUID+992, 191653, 2444, 13644, 0, '0', '0', 0, 0, 0, 3023.265380859375, -153.687652587890625, 3.974349021911621093, 1.927248358726501464, 7200, 0, 0, 37126, 0, 0, 0, 0, 0, 45505), -- Coastal Salamanther (Area: 0 - Difficulty: 0)
(@CGUID+993, 191792, 2444, 13644, 0, '0', '0', 0, 0, 0, 3071.80859375, -164.7645263671875, 3.689693450927734375, 5.904856681823730468, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Frog (Area: 0 - Difficulty: 0)
(@CGUID+994, 191553, 2444, 13644, 0, '0', '0', 0, 0, 0, 3082.0712890625, -39.0494575500488281, 93.46173858642578125, 0.461441874504089355, 7200, 0, 0, 24750, 0, 0, 0, 0, 0, 45505), -- Wild Argali (Area: 0 - Difficulty: 0)
(@CGUID+995, 191624, 2444, 13644, 0, '0', '0', 0, 0, 0, 3112.914794921875, -291.955657958984375, 61.03830337524414062, 0.171794012188911437, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Tranquil Vorquin (Area: 0 - Difficulty: 0)
(@CGUID+996, 191818, 2444, 13644, 0, '0', '0', 0, 0, 0, 3118.8837890625, -241.155288696289062, 50.94234466552734375, 4.691478729248046875, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Shaggy Rabbit (Area: 0 - Difficulty: 0)
(@CGUID+997, 191653, 2444, 13644, 0, '0', '0', 0, 0, 0, 3027.38330078125, -181.157455444335937, 7.914703369140625, 3.849247455596923828, 7200, 0, 0, 37126, 0, 0, 0, 0, 0, 45505), -- Coastal Salamanther (Area: 0 - Difficulty: 0)
(@CGUID+998, 192103, 2444, 13644, 0, '0', '0', 0, 0, 0, 3086.183349609375, -234.6363525390625, 53.3967132568359375, 6.090578079223632812, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Pricklefury Hare (Area: 0 - Difficulty: 0)
(@CGUID+999, 191818, 2444, 13644, 0, '0', '0', 0, 0, 0, 3134.575927734375, -276.438568115234375, 51.92565155029296875, 3.316835403442382812, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505); -- Shaggy Rabbit (Area: 0 - Difficulty: 0)

INSERT INTO `creature` (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnDifficulties`, `PhaseId`, `PhaseGroup`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `wander_distance`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`, `VerifiedBuild`) VALUES
(@CGUID+1000, 191656, 2444, 13644, 0, '0', '0', 0, 0, 0, 3045.69677734375, -192.185409545898437, 13.29799270629882812, 6.14092111587524414, 7200, 0, 0, 15469, 0, 0, 0, 0, 0, 45505), -- Young Salamanther (Area: 0 - Difficulty: 0)
(@CGUID+1001, 192059, 2444, 13644, 0, '0', '0', 0, 0, 0, 3055.876708984375, -122.354240417480468, 4.740277767181396484, 2.402464151382446289, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Palamanther (Area: 0 - Difficulty: 0)
(@CGUID+1002, 191625, 2444, 13644, 0, '0', '0', 0, 0, 0, 3106.920166015625, -283.84521484375, 58.712982177734375, 4.2138214111328125, 7200, 0, 0, 15469, 0, 0, 0, 0, 0, 45505), -- Vorquin Foal (Area: 0 - Difficulty: 0)
(@CGUID+1003, 191809, 2444, 13644, 0, '0', '0', 0, 0, 0, 3043.71923828125, -233.590713500976562, 60.22411346435546875, 0.418412625789642333, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Tiny Butterfly (Area: 0 - Difficulty: 0)
(@CGUID+1004, 191818, 2444, 13644, 0, '0', '0', 0, 0, 0, 3128.37939453125, -290.946136474609375, 59.8440093994140625, 1.844669938087463378, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Shaggy Rabbit (Area: 0 - Difficulty: 0)
(@CGUID+1005, 191624, 2444, 13644, 0, '0', '0', 0, 0, 0, 3123.82666015625, -313.6455078125, 135.9144134521484375, 5.695590496063232421, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Tranquil Vorquin (Area: 0 - Difficulty: 0)
(@CGUID+1006, 191653, 2444, 13644, 0, '0', '0', 0, 0, 0, 2979.005126953125, -166.506942749023437, 4.383857250213623046, 3.244507789611816406, 7200, 0, 0, 37126, 0, 0, 0, 0, 0, 45505), -- Coastal Salamanther (Area: 0 - Difficulty: 0)
(@CGUID+1007, 191656, 2444, 13644, 0, '0', '0', 0, 0, 0, 2980.792236328125, -114.647705078125, 18.6865234375, 4.609164237976074218, 7200, 0, 0, 15469, 0, 0, 0, 0, 0, 45505), -- Young Salamanther (Area: 0 - Difficulty: 0)
(@CGUID+1008, 191323, 2444, 13644, 0, '0', '0', 0, 0, 0, 3110.3759765625, -287.640045166015625, 59.980682373046875, 2.378964900970458984, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Vorquin Runt (Area: 0 - Difficulty: 0)
(@CGUID+1009, 191792, 2444, 13644, 0, '0', '0', 0, 0, 0, 3038.107177734375, -127.393600463867187, 4.115411758422851562, 0.68075728416442871, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Frog (Area: 0 - Difficulty: 0)
(@CGUID+1010, 191809, 2444, 13644, 0, '0', '0', 0, 0, 0, 3016.736572265625, -213.810287475585937, 66.86919403076171875, 2.373526573181152343, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Tiny Butterfly (Area: 0 - Difficulty: 0)
(@CGUID+1011, 191809, 2444, 13644, 0, '0', '0', 0, 0, 0, 3056.049560546875, -48.9851188659667968, 99.6696624755859375, 0.038151744753122329, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Tiny Butterfly (Area: 0 - Difficulty: 0)
(@CGUID+1012, 191624, 2444, 13644, 0, '0', '0', 0, 0, 0, 3050.17529296875, -274.31597900390625, 146.0372467041015625, 2.238474845886230468, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Tranquil Vorquin (Area: 0 - Difficulty: 0)
(@CGUID+1013, 191809, 2444, 13644, 0, '0', '0', 0, 0, 0, 3016.54052734375, -228.714691162109375, 65.02864837646484375, 0.431146144866943359, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Tiny Butterfly (Area: 0 - Difficulty: 0)
(@CGUID+1014, 187394, 2444, 13644, 0, '0', '0', 0, 0, 0, 3034.27001953125, -322.680572509765625, 62.22104644775390625, 5.231734275817871093, 7200, 0, 0, 185628, 0, 0, 0, 0, 0, 45505), -- Scoutstrasza (Area: 0 - Difficulty: 0)
(@CGUID+1015, 191792, 2444, 13644, 0, '0', '0', 0, 0, 0, 2962.956298828125, -138.1180419921875, 4.349549293518066406, 3.566059350967407226, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Frog (Area: 0 - Difficulty: 0)
(@CGUID+1016, 191656, 2444, 13644, 0, '0', '0', 0, 0, 0, 2986.0712890625, -167.66796875, 4.17164468765258789, 1.59386909008026123, 7200, 0, 0, 15469, 0, 0, 0, 0, 0, 45505), -- Young Salamanther (Area: 0 - Difficulty: 0)
(@CGUID+1017, 191656, 2444, 13644, 0, '0', '0', 0, 0, 0, 2981.9169921875, -173.443359375, 9.625638961791992187, 1.460154414176940917, 7200, 0, 0, 15469, 0, 0, 0, 0, 0, 45505), -- Young Salamanther (Area: 0 - Difficulty: 0)
(@CGUID+1018, 191792, 2444, 13644, 0, '0', '0', 0, 0, 0, 2987.109375, -165.511367797851562, 4.145467758178710937, 0.53087019920349121, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Frog (Area: 0 - Difficulty: 0)
(@CGUID+1019, 191765, 2444, 13644, 0, '0', '0', 0, 0, 0, 2950.029541015625, -144.26910400390625, 3.776849746704101562, 3.648987054824829101, 7200, 0, 0, 238120, 0, 0, 0, 0, 0, 45505), -- Mean Duck (Area: 0 - Difficulty: 0)
(@CGUID+1020, 191765, 2444, 13644, 0, '0', '0', 0, 0, 0, 2941.678955078125, -143.975692749023437, 3.615005731582641601, 6.004453659057617187, 7200, 0, 0, 238120, 0, 0, 0, 0, 0, 45505), -- Mean Duck (Area: 0 - Difficulty: 0)
(@CGUID+1021, 191554, 2444, 13644, 0, '0', '0', 0, 0, 0, 2969.417724609375, -108.873794555664062, 113.949798583984375, 4.782567977905273437, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Argali Lamb (Area: 0 - Difficulty: 0)
(@CGUID+1022, 191553, 2444, 13644, 0, '0', '0', 0, 0, 0, 2988.97314453125, -88.7301788330078125, 108.6480255126953125, 1.599276661872863769, 7200, 0, 0, 24750, 0, 0, 0, 0, 0, 45505), -- Wild Argali (Area: 0 - Difficulty: 0)
(@CGUID+1023, 191765, 2444, 13644, 0, '0', '0', 0, 0, 0, 2944.5244140625, -147.75347900390625, 3.541638612747192382, 0.429155617952346801, 7200, 0, 0, 238120, 0, 0, 0, 0, 0, 45505), -- Mean Duck (Area: 0 - Difficulty: 0)
(@CGUID+1024, 191765, 2444, 13644, 0, '0', '0', 0, 0, 0, 2949.3369140625, -151.704864501953125, 3.718102455139160156, 2.021996498107910156, 7200, 0, 0, 238120, 0, 0, 0, 0, 0, 45505), -- Mean Duck (Area: 0 - Difficulty: 0)
(@CGUID+1025, 191765, 2444, 13644, 0, '0', '0', 0, 0, 0, 2943.335205078125, -153.199661254882812, 3.759656906127929687, 0.580100417137145996, 7200, 0, 0, 238120, 0, 0, 0, 0, 0, 45505), -- Mean Duck (Area: 0 - Difficulty: 0)
(@CGUID+1026, 191656, 2444, 13644, 0, '0', '0', 0, 0, 0, 2912.47998046875, -181.389236450195312, 4.257051467895507812, 2.011730432510375976, 7200, 0, 0, 15469, 0, 0, 0, 0, 0, 45505), -- Young Salamanther (Area: 0 - Difficulty: 0)
(@CGUID+1027, 191554, 2444, 13644, 0, '0', '0', 0, 0, 0, 2973.432861328125, -102.500801086425781, 113.8113784790039062, 6.212005138397216796, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Argali Lamb (Area: 0 - Difficulty: 0)
(@CGUID+1028, 191765, 2444, 13644, 0, '0', '0', 0, 0, 0, 2951.166748046875, -147.645828247070312, 3.776849746704101562, 2.390057086944580078, 7200, 0, 0, 238120, 0, 0, 0, 0, 0, 45505), -- Mean Duck (Area: 0 - Difficulty: 0)
(@CGUID+1029, 191792, 2444, 13644, 0, '0', '0', 0, 0, 0, 2914.54736328125, -142.937652587890625, 4.071407794952392578, 2.353168964385986328, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Frog (Area: 0 - Difficulty: 0)
(@CGUID+1030, 191553, 2444, 13644, 0, '0', '0', 0, 0, 0, 2958.317138671875, -101.73773193359375, 114.6646270751953125, 1.421590089797973632, 7200, 0, 0, 24750, 0, 0, 0, 0, 0, 45505), -- Wild Argali (Area: 0 - Difficulty: 0)
(@CGUID+1031, 191656, 2444, 13644, 0, '0', '0', 0, 0, 0, 2925.6064453125, -176.591796875, 4.138081550598144531, 5.721349239349365234, 7200, 0, 0, 15469, 0, 0, 0, 0, 0, 45505), -- Young Salamanther (Area: 0 - Difficulty: 0)
(@CGUID+1032, 189815, 2444, 13644, 0, '0', '0', 0, 0, 0, 2907.953125, -128.010421752929687, 5.004765033721923828, 4.077126502990722656, 7200, 0, 0, 24750, 0, 0, 0, 0, 0, 45505), -- Cliffdrip Fallstriker (Area: 0 - Difficulty: 0)
(@CGUID+1033, 189815, 2444, 13644, 0, '0', '0', 0, 0, 0, 2889.559326171875, -153.396759033203125, 4.139834403991699218, 2.00996255874633789, 7200, 0, 0, 24750, 0, 0, 0, 0, 0, 45505), -- Cliffdrip Fallstriker (Area: 0 - Difficulty: 0)
(@CGUID+1034, 189812, 2444, 13644, 0, '0', '0', 0, 0, 0, 2892.767822265625, -109.859947204589843, 5.521282672882080078, 2.229571342468261718, 7200, 0, 0, 55688, 0, 0, 0, 0, 0, 45505), -- Cliffdrip Snapstrider (Area: 0 - Difficulty: 0) (Auras: )
(@CGUID+1035, 191554, 2444, 13644, 0, '0', '0', 0, 0, 0, 2950.6220703125, -97.1266250610351562, 115.1455612182617187, 2.384721040725708007, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Argali Lamb (Area: 0 - Difficulty: 0)
(@CGUID+1036, 198034, 2444, 13644, 0, '0', '0', 0, 0, 0, 2886.191162109375, -20.1781158447265625, 5.290126323699951171, 0.975943446159362792, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Snappy (Area: 0 - Difficulty: 0) (Auras: )
(@CGUID+1037, 191792, 2444, 13644, 0, '0', '0', 0, 0, 0, 2900, -177.083984375, 4.311697006225585937, 5.733665943145751953, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Frog (Area: 0 - Difficulty: 0)
(@CGUID+1038, 192186, 2444, 13644, 0, '0', '0', 0, 0, 0, 2891.59814453125, -122.583343505859375, 7.822481155395507812, 4.620758533477783203, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Territorial Axebeak (Area: 0 - Difficulty: 0) (Auras: 258247 - -Unknown-)
(@CGUID+1039, 192186, 2444, 13644, 0, '0', '0', 0, 0, 0, 2897.263671875, -110.00787353515625, 39.61292266845703125, 5.813730716705322265, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Territorial Axebeak (Area: 0 - Difficulty: 0)
(@CGUID+1040, 188074, 2444, 13644, 0, '0', '0', 0, 0, 0, 2882.709716796875, -162.054656982421875, 4.139834403991699218, 2.623690605163574218, 7200, 0, 0, 21657, 0, 0, 0, 0, 0, 45505), -- Agitated Sidewalker (Area: 0 - Difficulty: 0)
(@CGUID+1041, 189814, 2444, 13644, 0, '0', '0', 0, 0, 0, 2903.350830078125, -128.217010498046875, 4.859871387481689453, 0, 7200, 0, 0, 19800, 6015, 0, 0, 0, 0, 45505), -- Cliffdrip Wavemender (Area: 0 - Difficulty: 0)
(@CGUID+1042, 188074, 2444, 13644, 0, '0', '0', 0, 0, 0, 2895.189453125, -133.92352294921875, 4.309389591217041015, 0.723884165287017822, 7200, 0, 0, 21657, 0, 0, 0, 0, 0, 45505), -- Agitated Sidewalker (Area: 0 - Difficulty: 0)
(@CGUID+1043, 189136, 2444, 13644, 0, '0', '0', 0, 0, 0, 2955.755126953125, -165.362228393554687, 4.111023902893066406, 5.429546833038330078, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Wild Duckling (Area: 0 - Difficulty: 0)
-- (@CGUID+1044, 197211, UNKNOWN, 13644, 0, '0', '0', 0, 0, 0, 0.17111179232597351, 0, 1.442221522331237792, 0, 7200, 0, 0, 77345, 0, 0, 0, 0, 0, 45505), -- Murghurgl the Invader (Area: 0 - Difficulty: 0) (Auras: 46598 - Ride Vehicle Hardcoded) - !!! on transport - transport template not found !!!
(@CGUID+1045, 191792, 2444, 13644, 0, '0', '0', 0, 0, 0, 2866.243408203125, -161.52874755859375, 4.208040237426757812, 5.718492984771728515, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Frog (Area: 0 - Difficulty: 0)
(@CGUID+1046, 192186, 2444, 13644, 0, '0', '0', 0, 0, 0, 2879.903564453125, -186.576385498046875, 22.94516563415527343, 2.298007011413574218, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Territorial Axebeak (Area: 0 - Difficulty: 0) (Auras: 258247 - -Unknown-)
(@CGUID+1047, 192186, 2444, 13644, 0, '0', '0', 0, 0, 0, 2863.771240234375, -164.881622314453125, 31.71683502197265625, 3.316731691360473632, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Territorial Axebeak (Area: 0 - Difficulty: 0)
(@CGUID+1048, 189815, 2444, 13644, 0, '0', '0', 0, 0, 0, 2867.20654296875, -160.100692749023437, 4.187401771545410156, 6.06439971923828125, 7200, 0, 0, 24750, 0, 0, 0, 0, 0, 45505), -- Cliffdrip Fallstriker (Area: 0 - Difficulty: 0) (Auras: 372653 - -Unknown-)
(@CGUID+1049, 189815, 2444, 13644, 0, '0', '0', 0, 0, 0, 2870.392333984375, -160.809036254882812, 4.213365077972412109, 2.922806978225708007, 7200, 0, 0, 24750, 0, 0, 0, 0, 0, 45505), -- Cliffdrip Fallstriker (Area: 0 - Difficulty: 0)
(@CGUID+1050, 192186, 2444, 13644, 0, '0', '0', 0, 0, 0, 2862.634521484375, -93.2100677490234375, 16.96149444580078125, 3.454545974731445312, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Territorial Axebeak (Area: 0 - Difficulty: 0) (Auras: 258247 - -Unknown-)
(@CGUID+1051, 188074, 2444, 13644, 0, '0', '0', 0, 0, 0, 2846.600341796875, -116.733047485351562, 5.27783966064453125, 0.758441507816314697, 7200, 0, 0, 21657, 0, 0, 0, 0, 0, 45505), -- Agitated Sidewalker (Area: 0 - Difficulty: 0)
(@CGUID+1052, 189815, 2444, 13644, 0, '0', '0', 0, 0, 0, 2853.44091796875, -128.0562744140625, 4.195461273193359375, 4.130990982055664062, 7200, 0, 0, 24750, 0, 0, 0, 0, 0, 45505), -- Cliffdrip Fallstriker (Area: 0 - Difficulty: 0)
(@CGUID+1053, 192103, 2444, 13644, 0, '0', '0', 0, 0, 0, 2902.8037109375, -255.166717529296875, 68.0044097900390625, 5.940352916717529296, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Pricklefury Hare (Area: 0 - Difficulty: 0)
(@CGUID+1054, 191818, 2444, 13644, 0, '0', '0', 0, 0, 0, 2891.749755859375, -243.668914794921875, 69.8737335205078125, 0.688184142112731933, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Shaggy Rabbit (Area: 0 - Difficulty: 0)
(@CGUID+1055, 189812, 2444, 13644, 0, '0', '0', 0, 0, 0, 2833.94580078125, -118.031715393066406, 4.153164863586425781, 6.150213241577148437, 7200, 0, 0, 55688, 0, 0, 0, 0, 0, 45505), -- Cliffdrip Snapstrider (Area: 0 - Difficulty: 0) (Auras: )
(@CGUID+1056, 192186, 2444, 13644, 0, '0', '0', 0, 0, 0, 2830.4677734375, -84.2258834838867187, 45.8999786376953125, 2.972629547119140625, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Territorial Axebeak (Area: 0 - Difficulty: 0)
(@CGUID+1057, 192047, 2444, 13644, 0, '0', '0', 0, 0, 0, 2820.02783203125, -162.284957885742187, 4.319515705108642578, 5.793709754943847656, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Scruffy Ottuk (Area: 0 - Difficulty: 0)
(@CGUID+1058, 189814, 2444, 13644, 0, '0', '0', 0, 0, 0, 2824.0478515625, -97.015625, 4.273128986358642578, 3.899453639984130859, 7200, 0, 0, 19800, 6015, 0, 0, 0, 0, 45505), -- Cliffdrip Wavemender (Area: 0 - Difficulty: 0)
(@CGUID+1059, 192103, 2444, 13644, 0, '0', '0', 0, 0, 0, 2941.2548828125, -277.374481201171875, 65.5425567626953125, 2.577709913253784179, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Pricklefury Hare (Area: 0 - Difficulty: 0)
(@CGUID+1060, 189815, 2444, 13644, 0, '0', '0', 0, 0, 0, 2838.9580078125, -91.3819808959960937, 4.255766868591308593, 1.270267367362976074, 7200, 0, 0, 24750, 0, 0, 0, 0, 0, 45505), -- Cliffdrip Fallstriker (Area: 0 - Difficulty: 0)
(@CGUID+1061, 189814, 2444, 13644, 0, '0', '0', 0, 0, 0, 2843.5791015625, -81.8784713745117187, 4.160999298095703125, 0.437776267528533935, 7200, 0, 0, 19800, 6015, 0, 0, 0, 0, 45505), -- Cliffdrip Wavemender (Area: 0 - Difficulty: 0)
(@CGUID+1062, 192103, 2444, 13644, 0, '0', '0', 0, 0, 0, 2856.225830078125, -244.92254638671875, 69.0560455322265625, 3.33547520637512207, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Pricklefury Hare (Area: 0 - Difficulty: 0)
(@CGUID+1063, 191624, 2444, 13644, 0, '0', '0', 0, 0, 0, 2855.435791015625, -221.72222900390625, 159.346588134765625, 4.92420196533203125, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Tranquil Vorquin (Area: 0 - Difficulty: 0)
(@CGUID+1064, 189814, 2444, 13644, 0, '0', '0', 0, 0, 0, 2919.9697265625, -0.09548611193895339, 4.584103107452392578, 0, 7200, 0, 0, 19800, 6015, 0, 0, 0, 0, 45505), -- Cliffdrip Wavemender (Area: 0 - Difficulty: 0)
(@CGUID+1065, 189815, 2444, 13644, 0, '0', '0', 0, 0, 0, 2879.255126953125, -19.9618053436279296, 5.958518505096435546, 3.315918445587158203, 7200, 0, 0, 24750, 0, 0, 0, 0, 0, 45505), -- Cliffdrip Fallstriker (Area: 0 - Difficulty: 0)
(@CGUID+1066, 192186, 2444, 13644, 0, '0', '0', 0, 0, 0, 2807.457275390625, -126.513679504394531, 29.23139381408691406, 4.841716289520263671, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Territorial Axebeak (Area: 0 - Difficulty: 0)
(@CGUID+1067, 189812, 2444, 13644, 0, '0', '0', 0, 0, 0, 2801.46875, -99.9739608764648437, 5.993253707885742187, 3.869153022766113281, 7200, 0, 0, 55688, 0, 0, 0, 0, 0, 45505), -- Cliffdrip Snapstrider (Area: 0 - Difficulty: 0) (Auras: )
(@CGUID+1068, 189814, 2444, 13644, 0, '0', '0', 0, 0, 0, 2877.346435546875, -18.3871536254882812, 6.383654117584228515, 1.688439369201660156, 7200, 0, 0, 19800, 6015, 0, 0, 0, 0, 45505), -- Cliffdrip Wavemender (Area: 0 - Difficulty: 0) (Auras: 391245 - -Unknown-)
(@CGUID+1069, 192186, 2444, 13644, 0, '0', '0', 0, 0, 0, 2824.638916015625, -64.4809036254882812, 15.06448554992675781, 3.454545974731445312, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Territorial Axebeak (Area: 0 - Difficulty: 0) (Auras: 258247 - -Unknown-)
(@CGUID+1070, 189812, 2444, 13644, 0, '0', '0', 0, 0, 0, 2800.197998046875, -79.0607681274414062, 4.357023239135742187, 5.911035060882568359, 7200, 0, 0, 55688, 0, 0, 0, 0, 0, 45505), -- Cliffdrip Snapstrider (Area: 0 - Difficulty: 0) (Auras: )
(@CGUID+1071, 189814, 2444, 13644, 0, '0', '0', 0, 0, 0, 2825.307373046875, -59.9322929382324218, 11.64409255981445312, 3.899453639984130859, 7200, 0, 0, 19800, 6015, 0, 0, 0, 0, 45505), -- Cliffdrip Wavemender (Area: 0 - Difficulty: 0)
(@CGUID+1072, 188074, 2444, 13644, 0, '0', '0', 0, 0, 0, 2785.0078125, -134.411178588867187, 3.804065704345703125, 3.581643342971801757, 7200, 0, 0, 21657, 0, 0, 0, 0, 0, 45505), -- Agitated Sidewalker (Area: 0 - Difficulty: 0)
(@CGUID+1073, 188074, 2444, 13644, 0, '0', '0', 0, 0, 0, 2797.736083984375, -60.4149322509765625, 7.352674484252929687, 5.899586677551269531, 7200, 0, 0, 21657, 0, 0, 0, 0, 0, 45505), -- Agitated Sidewalker (Area: 0 - Difficulty: 0)
(@CGUID+1074, 194821, 2444, 13644, 0, '0', '0', 0, 0, 0, 2448.03466796875, 55.45833206176757812, 190.1051025390625, 2.35733962059020996, 7200, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Dragon Glyph (Area: 0 - Difficulty: 0) (Auras: 384680 - -Unknown-)
(@CGUID+1075, 191818, 2444, 13644, 0, '0', '0', 0, 0, 0, 2835.833984375, -244.787109375, 69.2845611572265625, 5.972721099853515625, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Shaggy Rabbit (Area: 0 - Difficulty: 0)
(@CGUID+1076, 189812, 2444, 13644, 0, '0', '0', 0, 0, 0, 2777.885498046875, -87.862396240234375, 2.998123407363891601, 5.450494289398193359, 7200, 0, 0, 55688, 0, 0, 0, 0, 0, 45505), -- Cliffdrip Snapstrider (Area: 0 - Difficulty: 0) (Auras: )
(@CGUID+1077, 188074, 2444, 13644, 0, '0', '0', 0, 0, 0, 2742.634033203125, -112.139419555664062, 3.473181724548339843, 4.265248775482177734, 7200, 0, 0, 21657, 0, 0, 0, 0, 0, 45505), -- Agitated Sidewalker (Area: 0 - Difficulty: 0)
(@CGUID+1078, 192186, 2444, 13644, 0, '0', '0', 0, 0, 0, 2772.028564453125, -212.625, 42.2304840087890625, 3.096668243408203125, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Territorial Axebeak (Area: 0 - Difficulty: 0) (Auras: 258247 - -Unknown-)
(@CGUID+1079, 189815, 2444, 13644, 0, '0', '0', 0, 0, 0, 2751.824951171875, -78.159515380859375, 6.649188995361328125, 0.340745776891708374, 7200, 0, 0, 24750, 0, 0, 0, 0, 0, 45505), -- Cliffdrip Fallstriker (Area: 0 - Difficulty: 0)
(@CGUID+1080, 192186, 2444, 13644, 0, '0', '0', 0, 0, 0, 2772.613037109375, -88.9437332153320312, 33.99966812133789062, 5.546483993530273437, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Territorial Axebeak (Area: 0 - Difficulty: 0)
(@CGUID+1081, 188074, 2444, 13644, 0, '0', '0', 0, 0, 0, 2758.3330078125, -148.958984375, 5.526647567749023437, 2.186960458755493164, 7200, 0, 0, 21657, 0, 0, 0, 0, 0, 45505), -- Agitated Sidewalker (Area: 0 - Difficulty: 0)
(@CGUID+1082, 189815, 2444, 13644, 0, '0', '0', 0, 0, 0, 2736.849853515625, -140.407989501953125, 4.514068603515625, 3.180777788162231445, 7200, 0, 0, 24750, 0, 0, 0, 0, 0, 45505), -- Cliffdrip Fallstriker (Area: 0 - Difficulty: 0)
(@CGUID+1083, 192186, 2444, 13644, 0, '0', '0', 0, 0, 0, 2771.322021484375, -211.309036254882812, 42.420989990234375, 3.679033994674682617, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Territorial Axebeak (Area: 0 - Difficulty: 0) (Auras: 258247 - -Unknown-)
(@CGUID+1084, 192186, 2444, 13644, 0, '0', '0', 0, 0, 0, 2779.04345703125, -53.6944465637207031, 61.55617904663085937, 4.921809673309326171, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Territorial Axebeak (Area: 0 - Difficulty: 0) (Auras: 258247 - -Unknown-)
(@CGUID+1085, 189814, 2444, 13644, 0, '0', '0', 0, 0, 0, 2733.510498046875, -141.720489501953125, 4.727764606475830078, 0.335230201482772827, 7200, 0, 0, 19800, 6015, 0, 0, 0, 0, 45505), -- Cliffdrip Wavemender (Area: 0 - Difficulty: 0)
(@CGUID+1086, 192186, 2444, 13644, 0, '0', '0', 0, 0, 0, 2735.002685546875, -152.032989501953125, 16.2174835205078125, 1.487527847290039062, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Territorial Axebeak (Area: 0 - Difficulty: 0) (Auras: 258247 - -Unknown-)
(@CGUID+1087, 192186, 2444, 13644, 0, '0', '0', 0, 0, 0, 2771.029541015625, -62.5538215637207031, 34.56673049926757812, 3.007093429565429687, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Territorial Axebeak (Area: 0 - Difficulty: 0) (Auras: 258247 - -Unknown-)
(@CGUID+1088, 193304, 2444, 13644, 0, '0', '0', 0, 0, 0, 2647.80029296875, -108.190971374511718, 9.78125, 5.121613502502441406, 7200, 0, 0, 37126, 0, 0, 0, 0, 0, 45505), -- Ru'kroszk (Area: 0 - Difficulty: 0)
(@CGUID+1089, 189812, 2444, 13644, 0, '0', '0', 0, 0, 0, 2699.539306640625, -70.1348114013671875, 14.61717987060546875, 3.878619194030761718, 7200, 0, 0, 55688, 0, 0, 0, 0, 0, 45505), -- Cliffdrip Snapstrider (Area: 0 - Difficulty: 0) (Auras: )
(@CGUID+1090, 189815, 2444, 13644, 0, '0', '0', 0, 0, 0, 2709.177001953125, -72.5746536254882812, 11.50829505920410156, 1.070655703544616699, 7200, 0, 0, 24750, 0, 0, 0, 0, 0, 45505), -- Cliffdrip Fallstriker (Area: 0 - Difficulty: 0)
(@CGUID+1091, 188074, 2444, 13644, 0, '0', '0', 0, 0, 0, 2680.776611328125, -122.54644775390625, 5.063015460968017578, 5.51873016357421875, 7200, 0, 0, 21657, 0, 0, 0, 0, 0, 45505), -- Agitated Sidewalker (Area: 0 - Difficulty: 0)
(@CGUID+1092, 189637, 2444, 13644, 0, '0', '0', 0, 0, 0, 2727.536376953125, -187.274307250976562, 7.158390045166015625, 0.710285305976867675, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Curious Duckling (Area: 0 - Difficulty: 0)
(@CGUID+1093, 188074, 2444, 13644, 0, '0', '0', 0, 0, 0, 2703.593994140625, -180.357681274414062, 3.973408937454223632, 0.437577694654464721, 7200, 0, 0, 21657, 0, 0, 0, 0, 0, 45505), -- Agitated Sidewalker (Area: 0 - Difficulty: 0)
(@CGUID+1094, 188074, 2444, 13644, 0, '0', '0', 0, 0, 0, 2708.130859375, -84.0034027099609375, 10.72451496124267578, 1.276244401931762695, 7200, 0, 0, 21657, 0, 0, 0, 0, 0, 45505), -- Agitated Sidewalker (Area: 0 - Difficulty: 0)
(@CGUID+1095, 189814, 2444, 13644, 0, '0', '0', 0, 0, 0, 2711.1328125, -102.699653625488281, 7.795139312744140625, 2.339602470397949218, 7200, 0, 0, 19800, 6015, 0, 0, 0, 0, 45505), -- Cliffdrip Wavemender (Area: 0 - Difficulty: 0)
(@CGUID+1096, 189815, 2444, 13644, 0, '0', '0', 0, 0, 0, 2738.200439453125, -65.7013931274414062, 8.565706253051757812, 2.753025770187377929, 7200, 0, 0, 24750, 0, 0, 0, 0, 0, 45505), -- Cliffdrip Fallstriker (Area: 0 - Difficulty: 0)
(@CGUID+1097, 189637, 2444, 13644, 0, '0', '0', 0, 0, 0, 2730.26806640625, -180.447357177734375, 4.292988777160644531, 4.860022544860839843, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Curious Duckling (Area: 0 - Difficulty: 0)
(@CGUID+1098, 189637, 2444, 13644, 0, '0', '0', 0, 0, 0, 2720.0234375, -188.6717529296875, 4.926533699035644531, 3.666432857513427734, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Curious Duckling (Area: 0 - Difficulty: 0)
(@CGUID+1099, 189812, 2444, 13644, 0, '0', '0', 0, 0, 0, 2725.815673828125, -131.582321166992187, 3.152471065521240234, 4.410086631774902343, 7200, 0, 0, 55688, 0, 0, 0, 0, 0, 45505), -- Cliffdrip Snapstrider (Area: 0 - Difficulty: 0) (Auras: )
(@CGUID+1100, 192186, 2444, 13644, 0, '0', '0', 0, 0, 0, 2734.4658203125, -140.08343505859375, 27.20953750610351562, 0.051845289766788482, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Territorial Axebeak (Area: 0 - Difficulty: 0)
(@CGUID+1101, 189812, 2444, 13644, 0, '0', '0', 0, 0, 0, 2738.37060546875, -91.3399276733398437, 4.61922311782836914, 3.875898361206054687, 7200, 0, 0, 55688, 0, 0, 0, 0, 0, 45505), -- Cliffdrip Snapstrider (Area: 0 - Difficulty: 0) (Auras: )
(@CGUID+1102, 196827, 2444, 13644, 0, '0', '0', 0, 0, 0, 2647.501708984375, -111.760406494140625, 9.793738365173339843, 0.6841927170753479, 7200, 0, 0, 37126, 0, 0, 0, 0, 0, 45505), -- Crabtender Kad'irsza (Area: 0 - Difficulty: 0) (Auras: 369109 - -Unknown-)
(@CGUID+1103, 189815, 2444, 13644, 0, '0', '0', 0, 0, 0, 2707.00341796875, -99.3884201049804687, 8.794724464416503906, 0.948354065418243408, 7200, 0, 0, 24750, 0, 0, 0, 0, 0, 45505), -- Cliffdrip Fallstriker (Area: 0 - Difficulty: 0)
(@CGUID+1104, 192186, 2444, 13644, 0, '0', '0', 0, 0, 0, 2699.080810546875, -62.7725715637207031, 55.29821395874023437, 3.007093429565429687, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Territorial Axebeak (Area: 0 - Difficulty: 0) (Auras: 258247 - -Unknown-)
(@CGUID+1105, 188074, 2444, 13644, 0, '0', '0', 0, 0, 0, 2659.3837890625, -114.334953308105468, 9.162547111511230468, 3.38401651382446289, 7200, 0, 0, 21657, 0, 0, 0, 0, 0, 45505), -- Agitated Sidewalker (Area: 0 - Difficulty: 0)
(@CGUID+1106, 188074, 2444, 13644, 0, '0', '0', 0, 0, 0, 2674.697509765625, -181.223129272460937, 4.835790157318115234, 0.193374887108802795, 7200, 0, 0, 21657, 0, 0, 0, 0, 0, 45505), -- Agitated Sidewalker (Area: 0 - Difficulty: 0)
(@CGUID+1107, 192186, 2444, 13644, 0, '0', '0', 0, 0, 0, 2699.673583984375, -52.3368072509765625, 55.3076934814453125, 5.791688919067382812, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Territorial Axebeak (Area: 0 - Difficulty: 0) (Auras: 258247 - -Unknown-)
(@CGUID+1108, 192186, 2444, 13644, 0, '0', '0', 0, 0, 0, 2645.293701171875, -157.308441162109375, 28.48215103149414062, 5.062819480895996093, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Territorial Axebeak (Area: 0 - Difficulty: 0)
(@CGUID+1109, 188074, 2444, 13644, 0, '0', '0', 0, 0, 0, 2640.70068359375, -105.400444030761718, 10.04885101318359375, 0.921017885208129882, 7200, 0, 0, 21657, 0, 0, 0, 0, 0, 45505), -- Agitated Sidewalker (Area: 0 - Difficulty: 0)
(@CGUID+1110, 188074, 2444, 13644, 0, '0', '0', 0, 0, 0, 2640.54345703125, -111.310768127441406, 9.830542564392089843, 0, 7200, 0, 0, 21657, 0, 0, 0, 0, 0, 45505), -- Agitated Sidewalker (Area: 0 - Difficulty: 0)
(@CGUID+1111, 188074, 2444, 13644, 0, '0', '0', 0, 0, 0, 2652.424560546875, -105.251739501953125, 10.0232086181640625, 4.179713249206542968, 7200, 0, 0, 21657, 0, 0, 0, 0, 0, 45505), -- Agitated Sidewalker (Area: 0 - Difficulty: 0)
(@CGUID+1112, 188074, 2444, 13644, 0, '0', '0', 0, 0, 0, 2641.378662109375, -118.826210021972656, 9.097971916198730468, 3.492022514343261718, 7200, 0, 0, 21657, 0, 0, 0, 0, 0, 45505), -- Agitated Sidewalker (Area: 0 - Difficulty: 0)
(@CGUID+1113, 188074, 2444, 13644, 0, '0', '0', 0, 0, 0, 2635.59814453125, -106.081596374511718, 9.704560279846191406, 0, 7200, 0, 0, 21657, 0, 0, 0, 0, 0, 45505), -- Agitated Sidewalker (Area: 0 - Difficulty: 0)
(@CGUID+1114, 192013, 2444, 13644, 0, '0', '0', 0, 0, 0, 2747.3212890625, -207.222320556640625, 5.088388442993164062, 3.071528434753417968, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Wild Duckling (Area: 0 - Difficulty: 0)
(@CGUID+1115, 192059, 2444, 13644, 0, '0', '0', 0, 0, 0, 2639.17529296875, -177.902786254882812, 5.801563262939453125, 1.344079852104187011, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Palamanther (Area: 0 - Difficulty: 0)
(@CGUID+1116, 188074, 2444, 13644, 0, '0', '0', 0, 0, 0, 2633.15380859375, -112.444389343261718, 9.027506828308105468, 2.230552196502685546, 7200, 0, 0, 21657, 0, 0, 0, 0, 0, 45505), -- Agitated Sidewalker (Area: 0 - Difficulty: 0)
(@CGUID+1117, 186918, 2444, 13644, 0, '0', '0', 0, 0, 0, 2710.55224609375, -294.336822509765625, 99.5492095947265625, 5.269641399383544921, 7200, 0, 0, 29700, 6015, 0, 0, 0, 0, 45505), -- Turbulent Gust (Area: 0 - Difficulty: 0)
(@CGUID+1118, 187295, 2444, 13644, 0, '0', '0', 0, 0, 0, 2590.963623046875, -215.397567749023437, 80.59139251708984375, 2.470410108566284179, 7200, 0, 0, 309380, 0, 0, 0, 0, 0, 45505), -- Borrowed Otter Mount (Area: 0 - Difficulty: 0)
(@CGUID+1119, 192186, 2444, 13644, 0, '0', '0', 0, 0, 0, 2601.1630859375, -135.676071166992187, 39.00693130493164062, 3.413959503173828125, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Territorial Axebeak (Area: 0 - Difficulty: 0)
(@CGUID+1120, 192013, 2444, 13644, 0, '0', '0', 0, 0, 0, 2673.384521484375, -177.551467895507812, 4.440861701965332031, 3.513394355773925781, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Wild Duckling (Area: 0 - Difficulty: 0)
(@CGUID+1121, 185464, 2444, 13644, 0, '0', '0', 0, 0, 0, 2538.670166015625, -28.9184036254882812, 104.090087890625, 2.438958168029785156, 7200, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Handhold (Area: 0 - Difficulty: 0)
(@CGUID+1122, 185485, 2444, 13644, 0, '0', '0', 0, 0, 0, 2542.387939453125, -32.8177070617675781, 97.366455078125, 1.777555704116821289, 7200, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Handhold (Area: 0 - Difficulty: 0)
(@CGUID+1123, 192186, 2444, 13644, 0, '0', '0', 0, 0, 0, 2606.63134765625, -56.0373115539550781, 86.9435577392578125, 0.416390150785446166, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Territorial Axebeak (Area: 0 - Difficulty: 0)
(@CGUID+1124, 192186, 2444, 13644, 0, '0', '0', 0, 0, 0, 2626.417236328125, -16.5226192474365234, 104.5028610229492187, 0.772271513938903808, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Territorial Axebeak (Area: 0 - Difficulty: 0)
(@CGUID+1125, 186143, 2444, 13644, 0, '0', '0', 0, 0, 0, 2534.431396484375, -34.1041679382324218, 102.907989501953125, 2.434623956680297851, 7200, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Handhold (Area: 0 - Difficulty: 0)
(@CGUID+1126, 186917, 2444, 13644, 0, '0', '0', 0, 0, 0, 2686.029541015625, -301.411529541015625, 91.714263916015625, 4.501530170440673828, 7200, 0, 0, 29700, 6015, 0, 0, 0, 0, 45505), -- Turbulent Gust (Area: 0 - Difficulty: 0)
(@CGUID+1127, 186146, 2444, 13644, 0, '0', '0', 0, 0, 0, 2525.665771484375, -38.7413215637207031, 101.2582931518554687, 2.273267269134521484, 7200, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Handhold (Area: 0 - Difficulty: 0)
(@CGUID+1128, 186918, 2444, 13644, 0, '0', '0', 0, 0, 0, 2664.79931640625, -295.437103271484375, 98.09185028076171875, 4.511872291564941406, 7200, 0, 0, 29700, 6015, 0, 0, 0, 0, 45505), -- Turbulent Gust (Area: 0 - Difficulty: 0)
(@CGUID+1129, 187392, 2444, 13644, 0, '0', '0', 0, 0, 0, 2584.473876953125, -214.223953247070312, 80.0587158203125, 2.085892677307128906, 7200, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Tuskarr Pilgrim (Area: 0 - Difficulty: 0)
(@CGUID+1130, 185485, 2444, 13644, 0, '0', '0', 0, 0, 0, 2511.454833984375, -29.385416030883789, 120.517364501953125, 1.213655710220336914, 7200, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Handhold (Area: 0 - Difficulty: 0)
(@CGUID+1131, 186146, 2444, 13644, 0, '0', '0', 0, 0, 0, 2510.052001953125, -35.3923606872558593, 107.3871536254882812, 1.412771821022033691, 7200, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Handhold (Area: 0 - Difficulty: 0)
(@CGUID+1132, 180377, 2444, 13644, 0, '0', '0', 0, 0, 0, 2517.9775390625, -38.2708320617675781, 103.5007553100585937, 1.065777897834777832, 7200, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Handhold (Area: 0 - Difficulty: 0)
(@CGUID+1133, 192186, 2444, 13644, 0, '0', '0', 0, 0, 0, 2545.533935546875, -68.8229141235351562, 76.12439727783203125, 2.202602624893188476, 7200, 0, 0, 9281, 0, 0, 0, 0, 0, 45505), -- Territorial Axebeak (Area: 0 - Difficulty: 0) (Auras: 258247 - -Unknown-)
(@CGUID+1134, 180377, 2444, 13644, 0, '0', '0', 0, 0, 0, 2508.72998046875, -31.026041030883789, 113.9109725952148437, 1.491386175155639648, 7200, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Handhold (Area: 0 - Difficulty: 0)
(@CGUID+1135, 185484, 2444, 13644, 0, '0', '0', 0, 0, 0, 2502.095458984375, -36.1145820617675781, 98.89527130126953125, 0.990310311317443847, 7200, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Handhold (Area: 0 - Difficulty: 0)
(@CGUID+1136, 186918, 2444, 13644, 0, '0', '0', 0, 0, 0, 2689.275390625, -306.665252685546875, 107.2649002075195312, 2.14625096321105957, 7200, 0, 0, 29700, 6015, 0, 0, 0, 0, 45505), -- Turbulent Gust (Area: 0 - Difficulty: 0)
(@CGUID+1137, 185496, 2444, 13644, 0, '0', '0', 0, 0, 0, 2553.7119140625, -5.03472232818603515, 120.4308547973632812, 4.688458919525146484, 7200, 0, 0, 12375, 6015, 0, 0, 0, 0, 45505), -- Primal Dropling (Area: 0 - Difficulty: 0) (Auras: 367419 - -Unknown-)
(@CGUID+1138, 185496, 2444, 13644, 0, '0', '0', 0, 0, 0, 2557.396728515625, -4.63368082046508789, 120.4308547973632812, 4.486980915069580078, 7200, 0, 0, 12375, 6015, 0, 0, 0, 0, 45505), -- Primal Dropling (Area: 0 - Difficulty: 0) (Auras: 367419 - -Unknown-)
(@CGUID+1139, 185496, 2444, 13644, 0, '0', '0', 0, 0, 0, 2542.22216796875, -5.18923616409301757, 120.4308547973632812, 4.517799854278564453, 7200, 0, 0, 12375, 6015, 0, 0, 0, 0, 45505), -- Primal Dropling (Area: 0 - Difficulty: 0) (Auras: 367419 - -Unknown-)
(@CGUID+1140, 185496, 2444, 13644, 0, '0', '0', 0, 0, 0, 2541.44189453125, 12.57632350921630859, 120.496856689453125, 3.941914081573486328, 7200, 0, 0, 12375, 6015, 0, 0, 0, 0, 45505), -- Primal Dropling (Area: 0 - Difficulty: 0)
(@CGUID+1141, 185496, 2444, 13644, 0, '0', '0', 0, 0, 0, 2533.720458984375, 14.34483242034912109, 120.496856689453125, 5.427917957305908203, 7200, 0, 0, 12375, 6015, 0, 0, 0, 0, 45505), -- Primal Dropling (Area: 0 - Difficulty: 0)
-- (@CGUID+1142, 185489, UNKNOWN, 13644, 0, '0', '0', 0, 0, 0, -0.02809072658419609, -0.0003985894145444, 4.812167167663574218, 0, 7200, 0, 0, 77345, 0, 0, 0, 0, 0, 45505), -- King Drippy (Area: 0 - Difficulty: 0) (Auras: 46598 - Ride Vehicle Hardcoded) - !!! on transport - transport template not found !!!
(@CGUID+1143, 185490, 2444, 13644, 0, '0', '0', 0, 0, 0, 2518.013916015625, 73.47222137451171875, 122.5447921752929687, 4.786641597747802734, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Entranced Water Elemental (Area: 0 - Difficulty: 0) (Auras: )
(@CGUID+1144, 195120, 2444, 13644, 0, '0', '0', 0, 0, 0, 2043.90966796875, -126.5914306640625, 266.15313720703125, 4.156815528869628906, 7200, 10, 0, 37126, 2568, 1, 0, 0, 0, 45505), -- Ruby Skyguard (Area: 0 - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+1145, 185496, 2444, 13644, 0, '0', '0', 0, 0, 0, 2510.9697265625, 23.93477058410644531, 120.56011962890625, 0.248951062560081481, 7200, 0, 0, 12375, 6015, 0, 0, 0, 0, 45505), -- Primal Dropling (Area: 0 - Difficulty: 0)
(@CGUID+1146, 185496, 2444, 13644, 0, '0', '0', 0, 0, 0, 2503.52001953125, 21.58981704711914062, 120.4218597412109375, 0.126604080200195312, 7200, 0, 0, 12375, 6015, 0, 0, 0, 0, 45505), -- Primal Dropling (Area: 0 - Difficulty: 0)
(@CGUID+1147, 185496, 2444, 13644, 0, '0', '0', 0, 0, 0, 2539.126708984375, 27.95634651184082031, 120.496856689453125, 4.181730270385742187, 7200, 0, 0, 12375, 6015, 0, 0, 0, 0, 45505), -- Primal Dropling (Area: 0 - Difficulty: 0)
(@CGUID+1148, 195120, 2444, 13644, 0, '0', '0', 0, 0, 0, 2085.056396484375, 65.178009033203125, 250.9603118896484375, 3.738638877868652343, 7200, 10, 0, 37126, 2568, 1, 0, 0, 0, 45505), -- Ruby Skyguard (Area: 0 - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+1149, 195120, 2444, 13644, 0, '0', '0', 0, 0, 0, 2023.91357421875, -95.034149169921875, 213.411041259765625, 5.329906940460205078, 7200, 10, 0, 37126, 2568, 1, 0, 0, 0, 45505), -- Ruby Skyguard (Area: 0 - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+1150, 185496, 2444, 13644, 13729, '0', '0', 0, 0, 0, 2477.541015625, 29.68527030944824218, 120.4218597412109375, 5.949361324310302734, 7200, 0, 0, 12375, 6015, 0, 0, 0, 0, 45505), -- Primal Dropling (Area: -Unknown- - Difficulty: 0)
(@CGUID+1151, 195120, 2444, 13644, 13729, '0', '0', 0, 0, 0, 2080.9375, 213.51763916015625, 217.547607421875, 1.655877351760864257, 7200, 0, 0, 37126, 2568, 0, 0, 0, 0, 45505), -- Ruby Skyguard (Area: -Unknown- - Difficulty: 0)
(@CGUID+1152, 195120, 2444, 13644, 13729, '0', '0', 0, 0, 0, 1999.5477294921875, 79.78082275390625, 252.3831329345703125, 5.743367671966552734, 7200, 10, 0, 37126, 2568, 1, 0, 0, 0, 45505), -- Ruby Skyguard (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+1153, 195120, 2444, 13644, 13729, '0', '0', 0, 0, 0, 1945.4017333984375, 61.48233795166015625, 319.761749267578125, 1.391126871109008789, 7200, 10, 0, 37126, 2568, 1, 0, 0, 0, 45505), -- Ruby Skyguard (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+1154, 195120, 2444, 13644, 13729, '0', '0', 0, 0, 0, 1971.4974365234375, 160.946807861328125, 244.2483673095703125, 3.666767597198486328, 7200, 10, 0, 37126, 2568, 1, 0, 0, 0, 45505), -- Ruby Skyguard (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+1155, 195120, 2444, 13644, 13729, '0', '0', 0, 0, 0, 1934.85009765625, 126.2867431640625, 252.8267059326171875, 5.934159278869628906, 7200, 10, 0, 37126, 2568, 1, 0, 0, 0, 45505), -- Ruby Skyguard (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+1156, 195120, 2444, 13644, 13729, '0', '0', 0, 0, 0, 1887.0008544921875, 19.7003936767578125, 217.921630859375, 1.421347975730895996, 7200, 10, 0, 37126, 2568, 1, 0, 0, 0, 45505), -- Ruby Skyguard (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+1157, 195125, 2444, 13644, 13729, '0', '0', 0, 0, 0, 2134.3662109375, 92.5718994140625, 113.5808486938476562, 6.101418495178222656, 7200, 0, 0, 37126, 2568, 0, 0, 0, 0, 45505), -- Ruby Skyguard (Area: -Unknown- - Difficulty: 0)
(@CGUID+1158, 195120, 2444, 13644, 13729, '0', '0', 0, 0, 0, 2045.1741943359375, 382.6953125, 257.62298583984375, 1.266862273216247558, 7200, 0, 0, 37126, 2568, 0, 0, 0, 0, 45505), -- Ruby Skyguard (Area: -Unknown- - Difficulty: 0)
(@CGUID+1159, 191031, 2444, 13644, 13729, '0', '0', 0, 0, 0, 2233.557373046875, -9.87152767181396484, 74.8568572998046875, 3.050320863723754882, 7200, 0, 0, 18563, 0, 0, 0, 0, 0, 45505), -- Ruby Tender (Area: -Unknown- - Difficulty: 0) (Auras: 375039 - -Unknown-, 375042 - -Unknown-)
(@CGUID+1160, 191031, 2444, 13644, 13729, '0', '0', 0, 0, 0, 2202.25341796875, -7.97916650772094726, 77.12967681884765625, 1.624030232429504394, 7200, 0, 0, 18563, 0, 0, 0, 0, 0, 45505), -- Ruby Tender (Area: -Unknown- - Difficulty: 0) (Auras: 375039 - -Unknown-, 375042 - -Unknown-)
(@CGUID+1161, 191031, 2444, 13644, 13729, '0', '0', 0, 0, 0, 2164.2431640625, -19.7083339691162109, 80.54108428955078125, 0.363600850105285644, 7200, 0, 0, 18563, 0, 0, 0, 0, 0, 45505), -- Ruby Tender (Area: -Unknown- - Difficulty: 0) (Auras: 375039 - -Unknown-, 375042 - -Unknown-)
(@CGUID+1162, 195120, 2444, 13644, 13729, '0', '0', 0, 0, 0, 1816.4559326171875, 391.74066162109375, 266.153167724609375, 0.015473746694624423, 7200, 10, 0, 37126, 2568, 1, 0, 0, 0, 45505), -- Ruby Skyguard (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+1163, 195120, 2444, 13644, 13729, '0', '0', 0, 0, 0, 1804.096435546875, 407.342681884765625, 319.761749267578125, 6.246168136596679687, 7200, 10, 0, 37126, 2568, 1, 0, 0, 0, 45505), -- Ruby Skyguard (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
-- (@CGUID+1164, 62821, UNKNOWN, 13644, 0, '0', '0', 0, 0, 0, -0.20000000298023223, 0, -0.20000000298023223, 0, 7200, 0, 0, 158747, 10794, 0, 0, 0, 0, 45505), -- Mystic Birdhat (Area: 0 - Difficulty: 0) (Auras: 122729 - Grand Expedition Yak, 123236 - Grummle Booth A) - !!! on transport - transport template not found !!!
-- (@CGUID+1165, 62822, UNKNOWN, 13644, 0, '0', '0', 0, 0, 0, -0.20000000298023223, 0, -0.20000000298023223, 0, 7200, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Cousin Slowhands (Area: 0 - Difficulty: 0) (Auras: 122729 - Grand Expedition Yak, 123240 - Grummle Booth B) - !!! on transport - transport template not found !!!
(@CGUID+1166, 187292, 2444, 13644, 0, '0', '0', 0, 0, 0, 1832.7708740234375, 117.2569427490234375, 99.921905517578125, 0.117720238864421844, 7200, 0, 0, 185628, 0, 0, 0, 0, 0, 45505), -- Holthkastrasz (Area: 0 - Difficulty: 0)
(@CGUID+1167, 194818, 2444, 13644, 13728, '0', '0', 0, 0, 0, 1424.373291015625, 310.15625, 471.65789794921875, 0, 7200, 0, 0, 132289, 0, 0, 0, 0, 0, 45505), -- Dragon Glyph (Area: -Unknown- - Difficulty: 0) (Auras: 384674 - -Unknown-)
(@CGUID+1168, 192491, 2444, 13644, 13728, '0', '0', 0, 0, 0, 1748.670166015625, 43.0711822509765625, 312.537353515625, 5.018693923950195312, 7200, 0, 0, 37126, 0, 0, 0, 0, 0, 45505), -- Vaknai (Area: -Unknown- - Difficulty: 0)
(@CGUID+1169, 194076, 2444, 13644, 13728, '0', '0', 0, 0, 0, 1818.4166259765625, 39.1649322509765625, 313.464599609375, 6.038344860076904296, 7200, 0, 0, 264578, 0, 0, 0, 0, 0, 45505), -- Veritistrasz (Area: -Unknown- - Difficulty: 0)
(@CGUID+1170, 195120, 2444, 13644, 13728, '0', '0', 0, 0, 0, 1840.1822509765625, -372.2530517578125, 371.3392333984375, 1.89095461368560791, 7200, 10, 0, 37126, 2568, 1, 0, 0, 0, 45505), -- Ruby Skyguard (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+1171, 193757, 2444, 13644, 13728, '0', '0', 0, 0, 0, 1740.1649169921875, 29.484375, 312.53680419921875, 0.610740602016448974, 7200, 0, 0, 37126, 0, 0, 0, 0, 0, 45505), -- Tzurok (Area: -Unknown- - Difficulty: 0)
(@CGUID+1172, 187058, 2444, 13644, 13728, '0', '0', 0, 0, 0, 1752.21875, -21.7847232818603515, 312.53680419921875, 1.229514837265014648, 7200, 0, 0, 859879, 0, 0, 0, 0, 0, 45505), -- Ruby Scaleguard (Area: -Unknown- - Difficulty: 0)
(@CGUID+1173, 192498, 2444, 13644, 13728, '0', '0', 0, 0, 0, 1741.26220703125, 32.75694656372070312, 312.53680419921875, 4.64137887954711914, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Haephesta (Area: -Unknown- - Difficulty: 0)
(@CGUID+1174, 187058, 2444, 13644, 13728, '0', '0', 0, 0, 0, 1733.3992919921875, -7.20138883590698242, 312.53680419921875, 1.13189244270324707, 7200, 0, 0, 859879, 0, 0, 0, 0, 0, 45505), -- Ruby Scaleguard (Area: -Unknown- - Difficulty: 0)
(@CGUID+1175, 187058, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1681.2603759765625, -112.003471374511718, 332.09429931640625, 1.052616596221923828, 7200, 0, 0, 859879, 0, 0, 0, 0, 0, 45505), -- Ruby Scaleguard (Area: -Unknown- - Difficulty: 0)
(@CGUID+1176, 187058, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1658.9461669921875, -92.4913177490234375, 332.06158447265625, 0.656039893627166748, 7200, 0, 0, 859879, 0, 0, 0, 0, 0, 45505), -- Ruby Scaleguard (Area: -Unknown- - Difficulty: 0)
(@CGUID+1177, 192168, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1808.8211669921875, -105.680557250976562, 194.1358184814453125, 0.113800600171089172, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Docile Slyvern (Area: -Unknown- - Difficulty: 0)
(@CGUID+1178, 192284, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1684.58056640625, -83.9856643676757812, 320.01788330078125, 4.011723518371582031, 7200, 10, 0, 1322890, 0, 1, 0, 0, 0, 45505), -- Kandrostrasz (Area: -Unknown- - Difficulty: 0) (Auras: 373400 - -Unknown-, 360001 - -Unknown-) (possible waypoints or random movement)
(@CGUID+1179, 192103, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1672.7852783203125, -52.9821968078613281, 219.7085723876953125, 3.742033958435058593, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Pricklefury Hare (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+1180, 193955, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1628.453125, -123.208343505859375, 334.29669189453125, 4.772756099700927734, 7200, 0, 0, 15469, 0, 0, 0, 0, 0, 45505), -- Lillistrazsa (Area: -Unknown- - Difficulty: 0) (Auras: 382828 - -Unknown-)
(@CGUID+1181, 191954, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1573.34375, -117.482643127441406, 330.8780517578125, 1.580751776695251464, 7200, 10, 0, 37126, 0, 1, 0, 0, 0, 45505), -- Kskeiton (Area: -Unknown- - Difficulty: 0) (Auras: 364324 - -Unknown-) (possible waypoints or random movement)
(@CGUID+1182, 192512, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1644.7691650390625, -157.617431640625, 331.23284912109375, 3.01909041404724121, 7200, 10, 0, 29700, 6015, 1, 0, 0, 0, 45505), -- Boisterous Child (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+1183, 187060, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1660.091552734375, -202.526870727539062, 330.05987548828125, 1.400836706161499023, 7200, 10, 0, 1984335, 0, 1, 0, 0, 0, 45505), -- Ruby Keeper (Area: -Unknown- - Difficulty: 0) (Auras: ) (possible waypoints or random movement)
(@CGUID+1184, 187955, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1567.9271240234375, -121.210067749023437, 330.837127685546875, 3.45177316665649414, 7200, 0, 0, 61876, 0, 0, 0, 0, 0, 45505), -- Krendisc (Area: -Unknown- - Difficulty: 0)
(@CGUID+1185, 187072, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1530.873291015625, -84.4670181274414062, 336.020172119140625, 0.853787064552307128, 7200, 0, 0, 1984335, 0, 0, 0, 0, 0, 45505), -- Ruby Shrineguard (Area: -Unknown- - Difficulty: 0)
(@CGUID+1186, 194479, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1630.206298828125, -187.27288818359375, 333.10357666015625, 3.024189710617065429, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Sprightly Butterfly (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+1187, 194479, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1628.7674560546875, -189.243270874023437, 334.244354248046875, 0.51187753677368164, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Sprightly Butterfly (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+1188, 193097, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1670.2054443359375, -197.338058471679687, 329.544769287109375, 1.919156074523925781, 7200, 10, 0, 30938, 0, 1, 0, 0, 0, 45505), -- Peaceful Duck (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+1189, 189262, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1519.6510009765625, -82.7430572509765625, 337.409942626953125, 2.605971336364746093, 7200, 0, 0, 148500, 6015, 0, 0, 0, 0, 45505), -- Akxall (Area: -Unknown- - Difficulty: 0)
(@CGUID+1190, 191894, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1637.7742919921875, -243.907989501953125, 331.193115234375, 3.199731826782226562, 7200, 0, 0, 37126, 0, 0, 0, 0, 0, 45505), -- Krillonn (Area: -Unknown- - Difficulty: 0)
(@CGUID+1191, 187073, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1726.4271240234375, -242.303817749023437, 337.409912109375, 5.378292083740234375, 7200, 0, 0, 54450, 6015, 0, 0, 0, 0, 45505), -- Ruby Sitter (Area: -Unknown- - Difficulty: 0)
(@CGUID+1192, 188029, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1686.1614990234375, -201.508682250976562, 336.06866455078125, 0, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Sprightly Butterfly (Area: -Unknown- - Difficulty: 0)
(@CGUID+1193, 194478, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1628.7882080078125, -186.932296752929687, 332.229888916015625, 5.354987144470214843, 7200, 0, 0, 37126, 0, 0, 0, 0, 0, 45505), -- Clokkistrasz (Area: -Unknown- - Difficulty: 0)
(@CGUID+1194, 194474, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1630.189208984375, -188.803817749023437, 332.17718505859375, 2.2133941650390625, 7200, 0, 0, 37126, 0, 0, 0, 0, 0, 45505), -- Zhustostrasza (Area: -Unknown- - Difficulty: 0) (Auras: 377397 - -Unknown-)
(@CGUID+1195, 191126, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1700.37158203125, -247.177078247070312, 333.4708251953125, 3.466817378997802734, 7200, 0, 0, 1984335, 0, 0, 0, 0, 0, 45505), -- Ruby Shrineguard (Area: -Unknown- - Difficulty: 0) (Auras: 375277 - -Unknown-)
(@CGUID+1196, 195052, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1515.26220703125, -70.0815963745117187, 337.935546875, 3.718702316284179687, 7200, 0, 0, 54450, 6015, 0, 0, 0, 0, 45505), -- Sapphire Tender (Area: -Unknown- - Difficulty: 0) (Auras: 382158 - -Unknown-)
(@CGUID+1197, 193097, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1686.1353759765625, -203.402786254882812, 331.72723388671875, 4.180439949035644531, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Peaceful Duck (Area: -Unknown- - Difficulty: 0)
(@CGUID+1198, 192539, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1563.1353759765625, -121.345489501953125, 330.82916259765625, 0.20923924446105957, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Miguel Bright (Area: -Unknown- - Difficulty: 0)
(@CGUID+1199, 193979, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1570.7291259765625, -219.244796752929687, 312.4014892578125, 4.129144191741943359, 7200, 0, 0, 123750, 6015, 0, 0, 0, 0, 45505), -- Ruby Whelpling (Area: -Unknown- - Difficulty: 0)
(@CGUID+1200, 194099, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1571.68408203125, -214, 126.6987762451171875, 3.976648807525634765, 7200, 0, 0, 185628, 0, 0, 0, 0, 0, 45505), -- Urlostrasz (Area: -Unknown- - Difficulty: 0)
(@CGUID+1201, 191893, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1531.701416015625, -153.574661254882812, 331.125, 1.298164844512939453, 7200, 0, 0, 37126, 0, 0, 0, 0, 0, 45505), -- Zherrak (Area: -Unknown- - Difficulty: 0)
(@CGUID+1202, 193920, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1527.7864990234375, -165.666671752929687, 332.187255859375, 2.013515472412109375, 7200, 0, 0, 18563, 0, 0, 0, 0, 0, 45505), -- Kahtzar (Area: -Unknown- - Difficulty: 0) (Auras: 381919 - -Unknown-)
(@CGUID+1203, 185904, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1717.0711669921875, -260.3507080078125, 337.271270751953125, 3.076296091079711914, 7200, 0, 0, 148500, 6015, 0, 0, 0, 0, 45505), -- Mother Elion (Area: -Unknown- - Difficulty: 0)
(@CGUID+1204, 189448, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1534.796875, -158.892364501953125, 331.1295166015625, 4.987834930419921875, 7200, 0, 0, 264578, 0, 0, 0, 0, 0, 45505), -- Trellain (Area: -Unknown- - Difficulty: 0)
(@CGUID+1205, 187071, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1501.3853759765625, -55.3541679382324218, 345.064453125, 1.819666624069213867, 7200, 0, 0, 1587465, 35980, 0, 0, 0, 0, 45505), -- Nurse Sentry (Area: -Unknown- - Difficulty: 0)
(@CGUID+1206, 187072, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1770.015625, -253.67535400390625, 346.330535888671875, 6.272936344146728515, 7200, 0, 0, 1984335, 0, 0, 0, 0, 0, 45505), -- Ruby Shrineguard (Area: -Unknown- - Difficulty: 0)
(@CGUID+1207, 192574, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1532.079833984375, -150.649307250976562, 331.129791259765625, 4.718915462493896484, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Thomas Bright (Area: -Unknown- - Difficulty: 0)
(@CGUID+1208, 187072, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1494.673583984375, -76.4652786254882812, 337.935546875, 2.891666650772094726, 7200, 0, 0, 1984335, 0, 0, 0, 0, 0, 45505), -- Ruby Shrineguard (Area: -Unknown- - Difficulty: 0)
(@CGUID+1209, 187072, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1484.4757080078125, -102.359382629394531, 335.9853515625, 3.050760746002197265, 7200, 0, 0, 1984335, 0, 0, 0, 0, 0, 45505), -- Ruby Shrineguard (Area: -Unknown- - Difficulty: 0)
(@CGUID+1210, 192674, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1640.8316650390625, -247.421875, 331.202789306640625, 4.547551155090332031, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Mahra Treebender (Area: -Unknown- - Difficulty: 0)
(@CGUID+1211, 192512, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1505.6614990234375, -157.402786254882812, 334.142364501953125, 0.358221113681793212, 7200, 10, 0, 29700, 6015, 1, 0, 0, 0, 45505), -- Boisterous Child (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+1212, 193983, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1507.701171875, -155.384597778320312, 334.033599853515625, 4.139866828918457031, 7200, 10, 0, 29700, 6015, 1, 0, 0, 0, 45505), -- Boisterous Instigator (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+1213, 193737, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1623.298583984375, -302.7100830078125, 333.53399658203125, 3.743263483047485351, 7200, 0, 0, 54450, 6015, 0, 0, 0, 0, 45505), -- Ruby Tender (Area: -Unknown- - Difficulty: 0)
(@CGUID+1214, 193995, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1506.4444580078125, -127.295143127441406, 332.5252685546875, 4.408904552459716796, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Rathestrasz (Area: -Unknown- - Difficulty: 0)
(@CGUID+1215, 192512, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1508.4410400390625, -157.333328247070312, 334.317047119140625, 2.979575395584106445, 7200, 10, 0, 29700, 6015, 1, 0, 0, 0, 45505), -- Boisterous Child (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+1216, 193991, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1504.37158203125, -129.539932250976562, 332.553466796875, 1.177008032798767089, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Lyrastrasz (Area: -Unknown- - Difficulty: 0)
(@CGUID+1217, 186692, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1494.9212646484375, -166.370849609375, 334.7415771484375, 0.744460105895996093, 7200, 10, 0, 15469, 0, 1, 0, 0, 0, 45505), -- Ruby Swarmer (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+1218, 186692, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1490.289794921875, -176.03369140625, 334.938018798828125, 4.571260452270507812, 7200, 10, 0, 15469, 0, 1, 0, 0, 0, 45505), -- Ruby Swarmer (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+1219, 193988, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1500.9583740234375, -155.163192749023437, 333.497222900390625, 3.84906768798828125, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Andustrasza (Area: -Unknown- - Difficulty: 0)
(@CGUID+1220, 193987, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1498.6129150390625, -157.26910400390625, 333.4759521484375, 0.883330047130584716, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Valdestrasz (Area: -Unknown- - Difficulty: 0)
(@CGUID+1221, 187071, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1450.142333984375, -175.147567749023437, 331.337158203125, 0.220528915524482727, 7200, 0, 0, 1587465, 35980, 0, 0, 0, 0, 45505), -- Nurse Sentry (Area: -Unknown- - Difficulty: 0)
(@CGUID+1222, 192096, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1500.154541015625, -181.324661254882812, 333.802032470703125, 2.15389108657836914, 7200, 0, 0, 15469, 0, 0, 0, 0, 0, 45505), -- Ruby Dozer (Area: -Unknown- - Difficulty: 0) (Auras: 120703 - Cosmetic - Sleep Zzz Breakable)
(@CGUID+1223, 192305, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1500.359375, -180.75347900390625, 333.784759521484375, 2.293951034545898437, 7200, 0, 0, 51910, 0, 0, 0, 0, 0, 45505), -- Boots (Area: -Unknown- - Difficulty: 0) (Auras: 120703 - Cosmetic - Sleep Zzz Breakable)
(@CGUID+1224, 192096, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1500.8350830078125, -180.677078247070312, 333.7882080078125, 1.693925380706787109, 7200, 0, 0, 15469, 0, 0, 0, 0, 0, 45505), -- Ruby Dozer (Area: -Unknown- - Difficulty: 0) (Auras: 120703 - Cosmetic - Sleep Zzz Breakable)
(@CGUID+1225, 187072, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1628.859375, -332.567718505859375, 334.572784423828125, 1.959624171257019042, 7200, 0, 0, 1984335, 0, 0, 0, 0, 0, 45505), -- Ruby Shrineguard (Area: -Unknown- - Difficulty: 0)
(@CGUID+1226, 193077, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1551.5972900390625, -307.8663330078125, 429.6224365234375, 3.010369062423706054, 7200, 0, 0, 309380, 0, 0, 0, 0, 0, 45505), -- Ruby Percher (Area: -Unknown- - Difficulty: 0)
(@CGUID+1227, 193077, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1556.579833984375, -304.59375, 430.179443359375, 1.967398524284362792, 7200, 0, 0, 309380, 0, 0, 0, 0, 0, 45505), -- Ruby Percher (Area: -Unknown- - Difficulty: 0)
(@CGUID+1228, 193077, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1556.0555419921875, -312.609375, 432.488677978515625, 0.560792505741119384, 7200, 0, 0, 309380, 0, 0, 0, 0, 0, 45505), -- Ruby Percher (Area: -Unknown- - Difficulty: 0)
(@CGUID+1229, 187060, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1447.3255615234375, -221.914474487304687, 331.95458984375, 1.234213709831237792, 7200, 10, 0, 1984335, 0, 1, 0, 0, 0, 45505), -- Ruby Keeper (Area: -Unknown- - Difficulty: 0) (Auras: ) (possible waypoints or random movement)
(@CGUID+1230, 186692, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1488.10986328125, -181.231231689453125, 335.499420166015625, 4.530836105346679687, 7200, 10, 0, 15469, 0, 1, 0, 0, 0, 45505), -- Ruby Swarmer (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+1231, 187072, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1602.3228759765625, -349.671875, 334.48992919921875, 2.650208950042724609, 7200, 0, 0, 1984335, 0, 0, 0, 0, 0, 45505), -- Ruby Shrineguard (Area: -Unknown- - Difficulty: 0)
(@CGUID+1232, 189260, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1625.328125, -353.80902099609375, 337.58709716796875, 5.389840602874755859, 7200, 0, 0, 148500, 6015, 0, 0, 0, 0, 45505), -- Zahkrana (Area: -Unknown- - Difficulty: 0)
(@CGUID+1233, 189261, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1433.0260009765625, -188.595489501953125, 337.58709716796875, 2.636039018630981445, 7200, 0, 0, 148500, 6015, 0, 0, 0, 0, 45505), -- Xius (Area: -Unknown- - Difficulty: 0)
(@CGUID+1234, 197166, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1463.8819580078125, -271.078125, 332.173614501953125, 3.029262542724609375, 7200, 0, 0, 29700, 6015, 0, 0, 0, 0, 45505), -- Dragonspawn Apprentice (Area: -Unknown- - Difficulty: 0)
(@CGUID+1235, 191012, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1451.282958984375, -271.227447509765625, 330.09552001953125, 4.094276905059814453, 7200, 0, 0, 29700, 6015, 0, 0, 0, 0, 45505), -- Akora (Area: -Unknown- - Difficulty: 0) (Auras: 376364 - -Unknown-, 389776 - -Unknown-)
(@CGUID+1236, 191174, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1457.689208984375, -277.8819580078125, 330.095489501953125, 2.522814035415649414, 7200, 0, 0, 30938, 2568, 0, 0, 0, 0, 45505), -- Vaeros (Area: -Unknown- - Difficulty: 0) (Auras: 374830 - -Unknown-)
(@CGUID+1237, 197166, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1462.3524169921875, -267.763885498046875, 331.066986083984375, 3.438025951385498046, 7200, 0, 0, 29700, 6015, 0, 0, 0, 0, 45505), -- Dragonspawn Apprentice (Area: -Unknown- - Difficulty: 0)
(@CGUID+1238, 195050, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1428.1875, -175.102432250976562, 338.356597900390625, 3.562006235122680664, 7200, 0, 0, 54450, 6015, 0, 0, 0, 0, 45505), -- Bronze Tender (Area: -Unknown- - Difficulty: 0) (Auras: 382158 - -Unknown-)
(@CGUID+1239, 188107, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1588.5103759765625, -363.80902099609375, 334.892364501953125, 1.915074348449707031, 7200, 0, 0, 264578, 0, 0, 0, 0, 0, 45505), -- Tionistrasz (Area: -Unknown- - Difficulty: 0)
(@CGUID+1240, 193737, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1419.142333984375, -191.369796752929687, 338.5302734375, 1.198307394981384277, 7200, 0, 0, 54450, 6015, 0, 0, 0, 0, 45505), -- Ruby Tender (Area: -Unknown- - Difficulty: 0) (Auras: 382158 - -Unknown-)
(@CGUID+1241, 197166, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1456.0347900390625, -282.071197509765625, 330.095489501953125, 2.500579833984375, 7200, 0, 0, 29700, 6015, 0, 0, 0, 0, 45505), -- Dragonspawn Apprentice (Area: -Unknown- - Difficulty: 0)
(@CGUID+1242, 193737, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1496.0521240234375, -344.748260498046875, 329.7294921875, 3.267051935195922851, 7200, 0, 0, 54450, 6015, 0, 0, 0, 0, 45505), -- Ruby Tender (Area: -Unknown- - Difficulty: 0) (Auras: 382158 - -Unknown-)
(@CGUID+1243, 197166, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1435.3680419921875, -266.828125, 331.377349853515625, 5.105257987976074218, 7200, 0, 0, 29700, 6015, 0, 0, 0, 0, 45505), -- Dragonspawn Apprentice (Area: -Unknown- - Difficulty: 0)
(@CGUID+1244, 197956, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1521.68408203125, -356.954864501953125, 330.095489501953125, 1.164247751235961914, 7200, 0, 0, 92814, 0, 0, 0, 0, 0, 45505), -- Injured Shrineguard (Area: -Unknown- - Difficulty: 0)
(@CGUID+1245, 196774, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1546.2569580078125, -324.4444580078125, 332.574005126953125, 4.180690288543701171, 7200, 0, 0, 29700, 6015, 0, 0, 0, 0, 45505), -- Zoristrasz (Area: -Unknown- - Difficulty: 0)
(@CGUID+1246, 193737, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1628.373291015625, -371.3125, 338.62127685546875, 0.455959796905517578, 7200, 0, 0, 54450, 6015, 0, 0, 0, 0, 45505), -- Ruby Tender (Area: -Unknown- - Difficulty: 0) (Auras: 382158 - -Unknown-)
(@CGUID+1247, 192625, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1428.8785400390625, -246.076385498046875, 332.099090576171875, 3.867268323898315429, 7200, 0, 0, 1587465, 35980, 0, 0, 0, 0, 45505), -- Ruby Groundskeeper (Area: -Unknown- - Difficulty: 0)
(@CGUID+1248, 197956, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1531.25, -356.020843505859375, 330.299072265625, 0.797717928886413574, 7200, 0, 0, 92814, 0, 0, 0, 0, 0, 45505), -- Injured Shrineguard (Area: -Unknown- - Difficulty: 0)
(@CGUID+1249, 191013, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1445.189208984375, -269.921875, 330.09619140625, 4.523908615112304687, 7200, 0, 0, 29700, 6015, 0, 0, 0, 0, 45505), -- Keshki (Area: -Unknown- - Difficulty: 0) (Auras: 376365 - -Unknown-; 389802 - -Unknown-)

INSERT INTO `creature` (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnDifficulties`, `PhaseId`, `PhaseGroup`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `wander_distance`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`, `VerifiedBuild`) VALUES
(@CGUID+1250, 197166, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1434.3177490234375, -272.263885498046875, 331.23748779296875, 5.888491153717041015, 7200, 0, 0, 29700, 6015, 0, 0, 0, 0, 45505), -- Dragonspawn Apprentice (Area: -Unknown- - Difficulty: 0)
(@CGUID+1251, 191025, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1444.935791015625, -283.8507080078125, 330.178192138671875, 1.605217695236206054, 7200, 0, 0, 29700, 6015, 0, 0, 0, 0, 45505), -- Lifecaller Tzadrak (Area: -Unknown- - Difficulty: 0)
(@CGUID+1252, 197166, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1452.953125, -284.217010498046875, 330.095489501953125, 2.035978078842163085, 7200, 0, 0, 29700, 6015, 0, 0, 0, 0, 45505), -- Dragonspawn Apprentice (Area: -Unknown- - Difficulty: 0)
(@CGUID+1253, 191027, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1442.09033203125, -270.28125, 330.09576416015625, 4.740824222564697265, 7200, 0, 0, 37126, 0, 0, 0, 0, 0, 45505), -- Lasztak (Area: -Unknown- - Difficulty: 0) (Auras: 389833 - -Unknown-)
(@CGUID+1254, 197956, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1526.7135009765625, -358.369781494140625, 330.095458984375, 2.186363697052001953, 7200, 0, 0, 92814, 0, 0, 0, 0, 0, 45505), -- Injured Shrineguard (Area: -Unknown- - Difficulty: 0)
(@CGUID+1255, 191176, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1448.4254150390625, -270.2257080078125, 330.095855712890625, 4.418038845062255859, 7200, 0, 0, 37126, 2568, 0, 0, 0, 0, 45505), -- Dazakros (Area: -Unknown- - Difficulty: 0) (Auras: 389771 - -Unknown-)
(@CGUID+1256, 191980, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1522.685791015625, -358.536468505859375, 331.12701416015625, 0.001873518689535558, 7200, 0, 0, 37126, 0, 0, 0, 0, 0, 45505), -- Xolleth (Area: -Unknown- - Difficulty: 0) (Auras: 377397 - -Unknown-)
(@CGUID+1257, 195051, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1642.470458984375, -359.791656494140625, 338.656646728515625, 3.809826135635375976, 7200, 0, 0, 148500, 6015, 0, 0, 0, 0, 45505), -- Azure Tender (Area: -Unknown- - Difficulty: 0) (Auras: 382158 - -Unknown-)
(@CGUID+1258, 191982, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1527.328125, -358.52777099609375, 331.1236572265625, 3.14346623420715332, 7200, 0, 0, 37126, 0, 0, 0, 0, 0, 45505), -- Faramin (Area: -Unknown- - Difficulty: 0)
(@CGUID+1259, 187130, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1464.484375, -309.6475830078125, 329.510162353515625, 4.84638214111328125, 7200, 0, 0, 148500, 6015, 0, 0, 0, 0, 45505), -- Amella (Area: -Unknown- - Difficulty: 0)
(@CGUID+1260, 187290, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1487.501708984375, -319.477447509765625, 330.531463623046875, 0.811088085174560546, 7200, 0, 0, 18562800, 2568, 0, 0, 0, 0, 45505), -- Alexstrasza the Life-Binder (Area: -Unknown- - Difficulty: 0)
(@CGUID+1261, 193737, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1456.30908203125, -318.38714599609375, 328.68145751953125, 0.298733711242675781, 7200, 0, 0, 54450, 6015, 0, 0, 0, 0, 45505), -- Ruby Tender (Area: -Unknown- - Difficulty: 0) (Auras: 382158 - -Unknown-)
(@CGUID+1262, 187072, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1397.361083984375, -156.460067749023437, 348.248809814453125, 2.896404981613159179, 7200, 0, 0, 1984335, 0, 0, 0, 0, 0, 45505), -- Ruby Shrineguard (Area: -Unknown- - Difficulty: 0)
(@CGUID+1263, 186692, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1593.5972900390625, -358.6163330078125, 334.849945068359375, 5.706325054168701171, 7200, 0, 0, 15469, 0, 0, 0, 0, 0, 45505), -- Ruby Swarmer (Area: -Unknown- - Difficulty: 0) (Auras: 358422 - -Unknown-)
(@CGUID+1264, 187072, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1388.7691650390625, -179.904510498046875, 348.248809814453125, 2.547817945480346679, 7200, 0, 0, 1984335, 0, 0, 0, 0, 0, 45505), -- Ruby Shrineguard (Area: -Unknown- - Difficulty: 0)
(@CGUID+1265, 186692, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1586.0052490234375, -362.024322509765625, 334.124847412109375, 5.511927604675292968, 7200, 0, 0, 15469, 0, 0, 0, 0, 0, 45505), -- Ruby Swarmer (Area: -Unknown- - Difficulty: 0) (Auras: 358422 - -Unknown-)
(@CGUID+1266, 192096, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1426.5625, -240.609375, 333.09478759765625, 3.64649057388305664, 7200, 0, 0, 15469, 0, 0, 0, 0, 0, 45505), -- Ruby Dozer (Area: -Unknown- - Difficulty: 0) (Auras: 120703 - Cosmetic - Sleep Zzz Breakable)
(@CGUID+1267, 187072, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1507.02783203125, -390.477447509765625, 336.02020263671875, 4.744898319244384765, 7200, 0, 0, 1984335, 0, 0, 0, 0, 0, 45505), -- Ruby Shrineguard (Area: -Unknown- - Difficulty: 0)
(@CGUID+1268, 187072, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1419.986083984375, -310.251739501953125, 336.02020263671875, 3.501879453659057617, 7200, 0, 0, 1984335, 0, 0, 0, 0, 0, 45505), -- Ruby Shrineguard (Area: -Unknown- - Difficulty: 0)
(@CGUID+1269, 187072, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1629.76220703125, -390.25347900390625, 348.248809814453125, 4.13796091079711914, 7200, 0, 0, 1984335, 0, 0, 0, 0, 0, 45505), -- Ruby Shrineguard (Area: -Unknown- - Difficulty: 0)
(@CGUID+1270, 186692, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1585.7742919921875, -367.69964599609375, 334.49127197265625, 6.09452676773071289, 7200, 0, 0, 15469, 0, 0, 0, 0, 0, 45505), -- Ruby Swarmer (Area: -Unknown- - Difficulty: 0) (Auras: 358422 - -Unknown-)
(@CGUID+1271, 192096, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1427.732666015625, -241.954864501953125, 332.544708251953125, 0.763035058975219726, 7200, 0, 0, 15469, 0, 0, 0, 0, 0, 45505), -- Ruby Dozer (Area: -Unknown- - Difficulty: 0) (Auras: 120703 - Cosmetic - Sleep Zzz Breakable)
(@CGUID+1272, 187071, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1655.6771240234375, -383.607635498046875, 345.51300048828125, 5.512444019317626953, 7200, 0, 0, 1587465, 35980, 0, 0, 0, 0, 45505), -- Nurse Sentry (Area: -Unknown- - Difficulty: 0)
(@CGUID+1273, 188280, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1588.0478515625, -356.888885498046875, 333.2081298828125, 3.27478957176208496, 7200, 10, 0, 5, 0, 1, 0, 0, 0, 45505), -- Excited Vorquin (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+1274, 195125, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1251.9188232421875, -315.4517822265625, 367.328826904296875, 6.037309646606445312, 7200, 10, 0, 37126, 2568, 1, 0, 0, 0, 45505), -- Ruby Skyguard (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+1275, 190295, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1470.3385009765625, -265.260406494140625, 332.21441650390625, 0, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Akxall (Area: -Unknown- - Difficulty: 0)
(@CGUID+1276, 184394, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1532.875, -395.939239501953125, 333.160919189453125, 1.610318660736083984, 7200, 0, 0, 661445, 0, 0, 0, 0, 0, 45505), -- Agorithos 0 (Area: -Unknown- - Difficulty: 0)
(@CGUID+1277, 195125, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1539.3350830078125, -583.58990478515625, 371.339202880859375, 1.636972904205322265, 7200, 10, 0, 37126, 2568, 1, 0, 0, 0, 45505), -- Ruby Skyguard (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+1278, 187073, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1554.05908203125, -303.39410400390625, 160.58050537109375, 1.668964743614196777, 7200, 0, 0, 54450, 6015, 0, 0, 0, 0, 45505), -- Ruby Sitter (Area: -Unknown- - Difficulty: 0)
(@CGUID+1279, 191768, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1499.48095703125, -317.883697509765625, 329.661895751953125, 3.400523185729980468, 7200, 0, 0, 185628, 0, 0, 0, 0, 0, 45505), -- Majordomo Selistra (Area: -Unknown- - Difficulty: 0) (Auras: 384483 - -Unknown-)
(@CGUID+1280, 195125, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1513.2152099609375, -614.5850830078125, 317.57208251953125, 1.774627208709716796, 7200, 10, 0, 37126, 2568, 1, 0, 0, 0, 45505), -- Ruby Skyguard (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+1281, 194314, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1490.21533203125, -327.354156494140625, 330.949371337890625, 1.017815947532653808, 7200, 0, 0, 19456, 0, 0, 0, 0, 0, 45505), -- Captain Exposition (Area: -Unknown- - Difficulty: 0) (Auras: 385839 - -Unknown-)
(@CGUID+1282, 187073, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1494.1978759765625, -236.927078247070312, 160.5805206298828125, 6.196669578552246093, 7200, 0, 0, 54450, 6015, 0, 0, 0, 0, 45505), -- Ruby Sitter (Area: -Unknown- - Difficulty: 0)
(@CGUID+1283, 195125, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1193.714599609375, -397.277984619140625, 339.1116943359375, 0.341126173734664916, 7200, 10, 0, 37126, 2568, 1, 0, 0, 0, 45505), -- Ruby Skyguard (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+1284, 191027, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1442.09033203125, -270.28125, 330.179107666015625, 4.740824222564697265, 7200, 0, 0, 37126, 0, 0, 0, 0, 0, 45505), -- Lasztak (Area: -Unknown- - Difficulty: 0) (Auras: 337501 - -Unknown-)
(@CGUID+1285, 195125, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1400.8267822265625, -574.4691162109375, 247.7788238525390625, 1.377028465270996093, 7200, 10, 0, 37126, 2568, 1, 0, 0, 0, 45505), -- Ruby Skyguard (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+1286, 189881, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1388.732666015625, -173.53472900390625, 310.872467041015625, 2.876650810241699218, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Elemental Target [DNT] (Area: -Unknown- - Difficulty: 0)
(@CGUID+1287, 189881, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1380.85595703125, -180.701385498046875, 309.42913818359375, 2.876650810241699218, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Elemental Target [DNT] (Area: -Unknown- - Difficulty: 0)
(@CGUID+1288, 189881, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1398.7274169921875, -145.907989501953125, 300.786041259765625, 1.981395959854125976, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Elemental Target [DNT] (Area: -Unknown- - Difficulty: 0)
(@CGUID+1289, 189881, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1391.21875, -164.201385498046875, 278.48199462890625, 2.876650810241699218, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Elemental Target [DNT] (Area: -Unknown- - Difficulty: 0)
(@CGUID+1290, 192103, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1463.817138671875, -43.5778388977050781, 216.6270751953125, 2.341164588928222656, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Pricklefury Hare (Area: -Unknown- - Difficulty: 0)
(@CGUID+1291, 194174, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1618.21533203125, -306.34027099609375, 333.575469970703125, 6.184260368347167968, 7200, 0, 0, 148500, 6015, 0, 0, 0, 0, 45505), -- Amella (Area: -Unknown- - Difficulty: 0)
-- (@CGUID+1292, 121541, UNKNOWN, 13644, 13727, '0', '0', 0, 0, 0, 0.208347395062446594, 0, 1.873889684677124023, 0, 7200, 10, 0, 2993, 0, 1, 0, 0, 0, 45505), -- Ban-Lu (Area: -Unknown- - Difficulty: 0) (Auras: 46598 - Ride Vehicle Hardcoded) - !!! on transport - transport template not found !!! (possible waypoints or random movement)
(@CGUID+1293, 191179, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1706.829833984375, -258.227447509765625, 338.576171875, 3.407447576522827148, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Target Bunny (Area: -Unknown- - Difficulty: 0) (Auras: )
(@CGUID+1294, 191179, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1721.5711669921875, -247.774307250976562, 340.041259765625, 3.407447576522827148, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Target Bunny (Area: -Unknown- - Difficulty: 0) (Auras: )
(@CGUID+1295, 191179, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1736.876708984375, -265.873260498046875, 340.548583984375, 1.704125881195068359, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Target Bunny (Area: -Unknown- - Difficulty: 0) (Auras: )
(@CGUID+1296, 188029, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1642.3941650390625, -391.447906494140625, 354.578155517578125, 0, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Sprightly Butterfly (Area: -Unknown- - Difficulty: 0)
-- (@CGUID+1297, 121541, UNKNOWN, 13644, 13727, '0', '0', 0, 0, 0, 0.208347395062446594, 0, 1.873889684677124023, 0, 7200, 0, 0, 2993, 0, 0, 0, 0, 0, 45505), -- Ban-Lu (Area: -Unknown- - Difficulty: 0) (Auras: 46598 - Ride Vehicle Hardcoded) - !!! on transport - transport template not found !!!
(@CGUID+1298, 193994, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1543.1666259765625, -193.0625, 277.029296875, 4.999516963958740234, 7200, 0, 0, 21657, 2568, 0, 0, 0, 0, 45505), -- Agitated Weedling (Area: -Unknown- - Difficulty: 0)
(@CGUID+1299, 194142, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1566.2099609375, -198.58331298828125, 267.54412841796875, 1.323287606239318847, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Intrusive Pupstinger (Area: -Unknown- - Difficulty: 0)
(@CGUID+1300, 193994, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1591.4427490234375, -284.951385498046875, 194.5497589111328125, 2.426854610443115234, 7200, 0, 0, 21657, 2568, 0, 0, 0, 0, 45505), -- Agitated Weedling (Area: -Unknown- - Difficulty: 0)
(@CGUID+1301, 193994, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1494.0850830078125, -252.461807250976562, 228.21942138671875, 0, 7200, 0, 0, 21657, 2568, 0, 0, 0, 0, 45505), -- Agitated Weedling (Area: -Unknown- - Difficulty: 0)
(@CGUID+1302, 193994, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1581.3350830078125, -200.355911254882812, 192.96368408203125, 3.77857065200805664, 7200, 0, 0, 21657, 2568, 0, 0, 0, 0, 45505), -- Agitated Weedling (Area: -Unknown- - Difficulty: 0)
(@CGUID+1303, 194142, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1564.461181640625, -289.67950439453125, 325.845184326171875, 6.030774593353271484, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Intrusive Pupstinger (Area: -Unknown- - Difficulty: 0)
(@CGUID+1304, 193994, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1565.4774169921875, -196.663192749023437, 227.545166015625, 4.20952463150024414, 7200, 0, 0, 21657, 2568, 0, 0, 0, 0, 45505), -- Agitated Weedling (Area: -Unknown- - Difficulty: 0)
(@CGUID+1305, 194142, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1503.779541015625, -216.78125, 318.378509521484375, 2.289027929306030273, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Intrusive Pupstinger (Area: -Unknown- - Difficulty: 0)
(@CGUID+1306, 194142, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1536.4200439453125, -191.593734741210937, 278.597412109375, 1.094476222991943359, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Intrusive Pupstinger (Area: -Unknown- - Difficulty: 0)
(@CGUID+1307, 193994, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1543.3055419921875, -190.368057250976562, 305.059112548828125, 5.038052558898925781, 7200, 0, 0, 21657, 2568, 0, 0, 0, 0, 45505), -- Agitated Weedling (Area: -Unknown- - Difficulty: 0)
(@CGUID+1308, 193737, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1571.0242919921875, -212.84722900390625, 311.304718017578125, 4.26290750503540039, 7200, 0, 0, 54450, 6015, 0, 0, 0, 0, 45505), -- Ruby Tender (Area: -Unknown- - Difficulty: 0)
(@CGUID+1309, 193994, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1522.9375, -200.482635498046875, 227.3756866455078125, 4.999516963958740234, 7200, 0, 0, 21657, 2568, 0, 0, 0, 0, 45505), -- Agitated Weedling (Area: -Unknown- - Difficulty: 0)
(@CGUID+1310, 194142, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1516.671630859375, -283.509765625, 241.1867828369140625, 2.291513919830322265, 7200, 10, 0, 30938, 0, 1, 0, 0, 0, 45505), -- Intrusive Pupstinger (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+1311, 194142, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1591.7725830078125, -210.677078247070312, 198.4707794189453125, 1.238305449485778808, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Intrusive Pupstinger (Area: -Unknown- - Difficulty: 0)
(@CGUID+1312, 194142, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1512.338134765625, -242.158493041992187, 259.982269287109375, 0.913783669471740722, 7200, 10, 0, 30938, 0, 1, 0, 0, 0, 45505), -- Intrusive Pupstinger (Area: -Unknown- - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+1313, 193994, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1604.6441650390625, -242.645828247070312, 228.3162078857421875, 3.207360506057739257, 7200, 0, 0, 21657, 2568, 0, 0, 0, 0, 45505), -- Agitated Weedling (Area: -Unknown- - Difficulty: 0)
(@CGUID+1314, 194142, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1571.0029296875, -297.767852783203125, 262.91802978515625, 5.861703872680664062, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Intrusive Pupstinger (Area: -Unknown- - Difficulty: 0)
(@CGUID+1315, 193994, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1571.845458984375, -298.114593505859375, 212.325225830078125, 1.532795190811157226, 7200, 0, 0, 21657, 2568, 0, 0, 0, 0, 45505), -- Agitated Weedling (Area: -Unknown- - Difficulty: 0)
(@CGUID+1316, 194159, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1594.185791015625, -283.1875, 259.21502685546875, 1.570796370506286621, 7200, 0, 0, 464070, 0, 0, 0, 0, 0, 45505), -- Relentless Gust (Area: -Unknown- - Difficulty: 0) (Auras: 391958 - -Unknown-)
(@CGUID+1317, 193994, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1604.9757080078125, -229.736114501953125, 192.4488525390625, 3.77857065200805664, 7200, 0, 0, 21657, 2568, 0, 0, 0, 0, 45505), -- Agitated Weedling (Area: -Unknown- - Difficulty: 0)
(@CGUID+1318, 194195, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1594.185791015625, -283.1875, 264.5814208984375, 0, 7200, 0, 0, 3093800, 0, 0, 0, 0, 0, 45505), -- Lifeshrine Door (Area: -Unknown- - Difficulty: 0) (Auras: )
(@CGUID+1319, 194142, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1586.4271240234375, -263.90277099609375, 160.8731842041015625, 0.97767794132232666, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Intrusive Pupstinger (Area: -Unknown- - Difficulty: 0)
(@CGUID+1320, 194159, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1497.157958984375, -274.22222900390625, 226.5145111083984375, 1.570796370506286621, 7200, 0, 0, 464070, 0, 0, 0, 0, 0, 45505), -- Relentless Gust (Area: -Unknown- - Difficulty: 0) (Auras: 391958 - -Unknown-)
(@CGUID+1321, 194142, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1593.017333984375, -277.638885498046875, 227.62078857421875, 4.7563018798828125, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Intrusive Pupstinger (Area: -Unknown- - Difficulty: 0)
(@CGUID+1322, 193994, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1542.0260009765625, -301.20660400390625, 161.089874267578125, 1.278888821601867675, 7200, 0, 0, 21657, 2568, 0, 0, 0, 0, 45505), -- Agitated Weedling (Area: -Unknown- - Difficulty: 0)
(@CGUID+1323, 194142, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1552.4317626953125, -296.460693359375, 210.386932373046875, 3.101396799087524414, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505), -- Intrusive Pupstinger (Area: -Unknown- - Difficulty: 0)
(@CGUID+1324, 191812, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1560.2384033203125, -457.79608154296875, 232.28240966796875, 0.55063176155090332, 7200, 0, 0, 5, 0, 0, 0, 0, 0, 45505), -- Crumbling Pebbles (Area: -Unknown- - Difficulty: 0)
(@CGUID+1325, 193994, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1579.3802490234375, -296.498260498046875, 261.3828125, 1.138152480125427246, 7200, 0, 0, 21657, 2568, 0, 0, 0, 0, 45505), -- Agitated Weedling (Area: -Unknown- - Difficulty: 0)
(@CGUID+1326, 193994, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1554.6441650390625, -300.65277099609375, 291.72705078125, 1.138152480125427246, 7200, 0, 0, 21657, 2568, 0, 0, 0, 0, 45505), -- Agitated Weedling (Area: -Unknown- - Difficulty: 0)
(@CGUID+1327, 193994, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1505.94970703125, -280.432281494140625, 160.58551025390625, 0.6029396653175354, 7200, 0, 0, 21657, 2568, 0, 0, 0, 0, 45505), -- Agitated Weedling (Area: -Unknown- - Difficulty: 0)
(@CGUID+1328, 193061, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1437.5570068359375, -378.293212890625, 409.590576171875, 1.540895342826843261, 7200, 0, 0, 1322890, 0, 0, 0, 0, 0, 45505), -- Danastra (Area: -Unknown- - Difficulty: 0) (Auras: 373397 - -Unknown-, 360001 - -Unknown-)
-- (@CGUID+1329, 121541, UNKNOWN, 13644, 13727, '0', '0', 0, 0, 0, 0.208347395062446594, 0, 1.873889684677124023, 0, 7200, 0, 0, 2993, 0, 0, 0, 0, 0, 45505), -- Ban-Lu (Area: -Unknown- - Difficulty: 0) (Auras: 46598 - Ride Vehicle Hardcoded) - !!! on transport - transport template not found !!!
(@CGUID+1330, 194159, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1521.329833984375, -196.064239501953125, 193.026580810546875, 1.570796370506286621, 7200, 0, 0, 464070, 0, 0, 0, 0, 0, 45505), -- Relentless Gust (Area: -Unknown- - Difficulty: 0) (Auras: 391958 - -Unknown-)
(@CGUID+1331, 191012, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1451.282958984375, -271.227447509765625, 330.178863525390625, 4.094276905059814453, 7200, 0, 0, 29700, 6015, 0, 0, 0, 0, 45505), -- Akora (Area: -Unknown- - Difficulty: 0) (Auras: 376364 - -Unknown-)
(@CGUID+1332, 194142, 2444, 13644, 13727, '0', '0', 0, 0, 0, 1515.736083984375, -288.3975830078125, 195.7255706787109375, 4.37161874771118164, 7200, 0, 0, 30938, 0, 0, 0, 0, 0, 45505); -- Intrusive Pupstinger (Area: -Unknown- - Difficulty: 0)
DELETE FROM `creature_addon` WHERE `guid` BETWEEN @CGUID+0 AND @CGUID+1332;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `aiAnimKit`, `movementAnimKit`, `meleeAnimKit`, `visibilityDistanceType`, `auras`) VALUES
(@CGUID+2, 0, 0, 0, 1, 0, 0, 0, 0, 0, '369788'), -- Qalashi Scoundrel - 369788 - -Unknown-
(@CGUID+4, 0, 0, 262144, 1, 0, 0, 0, 0, 0, '159474'), -- Qalashi Rampager - 159474 - Permanent Feign Death (NO Stun, Untrackable, Immune)
(@CGUID+6, 0, 0, 0, 1, 0, 0, 0, 0, 0, '369897'), -- Lava Phoenix - 369897 - -Unknown-
(@CGUID+7, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Blazing Dreadsquall
(@CGUID+9, 0, 0, 0, 1, 0, 0, 0, 0, 0, '265075'), -- Magmammoth Calf - 265075 - -Unknown-
(@CGUID+12, 0, 0, 0, 1, 0, 0, 0, 0, 0, '370034 364588'), -- Lava Elemental - 370034 - -Unknown-, 364588 - -Unknown-
(@CGUID+13, 0, 0, 0, 1, 0, 0, 0, 0, 0, '391254'), -- Lava Tarantula - 391254 - -Unknown-
(@CGUID+14, 0, 0, 0, 0, 0, 0, 0, 0, 0, '369596'), -- Qalashi Ragetamer - 369596 - -Unknown-
(@CGUID+16, 0, 0, 0, 1, 0, 0, 0, 0, 0, '279802'), -- Talonstalker Kavia - 279802 - -Unknown-
(@CGUID+17, 0, 0, 0, 1, 0, 0, 0, 0, 0, '369897'), -- Lava Phoenix - 369897 - -Unknown-
(@CGUID+20, 0, 0, 0, 1, 0, 0, 0, 0, 0, '392039'), -- Qalashi Marauder - 392039 - -Unknown-
(@CGUID+21, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, '369897'), -- Lava Phoenix - 369897 - -Unknown-
(@CGUID+30, 0, 0, 0, 1, 0, 0, 0, 0, 0, '358419'), -- Qalashi Ragetamer - 358419 - -Unknown-
(@CGUID+31, 0, 0, 0, 1, 0, 0, 0, 0, 0, '369897'), -- Lava Phoenix - 369897 - -Unknown-
(@CGUID+33, 0, 0, 0, 1, 0, 0, 0, 0, 0, '369897'), -- Lava Phoenix - 369897 - -Unknown-
(@CGUID+34, 0, 0, 0, 1, 0, 0, 0, 0, 0, '369897'), -- Lava Phoenix - 369897 - -Unknown-
(@CGUID+37, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, '369897'), -- Lava Phoenix - 369897 - -Unknown-
(@CGUID+39, 0, 0, 0, 1, 0, 0, 0, 0, 0, '370104'), -- Qalashi Metalshaper - 370104 - -Unknown-
(@CGUID+40, 0, 0, 0, 1, 0, 0, 0, 0, 0, '369788'), -- Qalashi Ragetamer - 369788 - -Unknown-
(@CGUID+41, 0, 0, 0, 0, 0, 0, 0, 0, 0, '369596'), -- Qalashi Ragetamer - 369596 - -Unknown-
(@CGUID+47, 0, 0, 0, 1, 0, 0, 0, 0, 0, '265075'), -- Magmammoth Calf - 265075 - -Unknown-
(@CGUID+48, 0, 0, 0, 1, 0, 0, 0, 0, 0, '369897'), -- Lava Phoenix - 369897 - -Unknown-
(@CGUID+50, 0, 0, 0, 1, 0, 0, 0, 0, 0, '390416 358419'), -- Flameshaper Lorak - 390416 - -Unknown-, 358419 - -Unknown-
(@CGUID+51, 0, 0, 0, 1, 0, 0, 0, 0, 0, '369897'), -- Lava Phoenix - 369897 - -Unknown-
(@CGUID+53, 0, 0, 1, 1, 0, 0, 0, 0, 0, ''), -- Qalashi Marauder
(@CGUID+55, 0, 0, 0, 1, 0, 0, 0, 0, 0, '358419'), -- Qalashi Ragetamer - 358419 - -Unknown-
(@CGUID+57, 0, 0, 0, 1, 0, 0, 0, 0, 0, '358419'), -- Qalashi Flamemuzzler - 358419 - -Unknown-
(@CGUID+58, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Blazing Dreadsquall
(@CGUID+59, 0, 0, 0, 1, 0, 0, 0, 0, 0, '375804'), -- Qalashi Marauder - 375804 - -Unknown-
(@CGUID+67, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, '391254'), -- Blazing Dreadsquall - 391254 - -Unknown-
(@CGUID+68, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Blazing Dreadsquall
(@CGUID+69, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Blazing Dreadsquall
(@CGUID+70, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Dragon Target [DNT]
-- (@CGUID+73, 0, 0, 0, 1, 0, 0, 0, 0, 0, '46598'), -- Ban-Lu - 46598 - Ride Vehicle Hardcoded - !!! on transport - transport template not found !!!
(@CGUID+75, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Dragon Target [DNT]
(@CGUID+77, 0, 0, 0, 0, 0, 0, 0, 0, 0, '369596'), -- Qalashi Metalshaper - 369596 - -Unknown-
(@CGUID+80, 0, 0, 0, 0, 0, 0, 0, 0, 0, '369596'), -- Qalashi Metalshaper - 369596 - -Unknown-
(@CGUID+82, 0, 0, 0, 1, 0, 0, 0, 0, 0, '391254'), -- Mature Obsidian Hornswog - 391254 - -Unknown-
(@CGUID+85, 0, 0, 0, 1, 0, 0, 0, 0, 0, '369897'), -- Lava Phoenix - 369897 - -Unknown-
(@CGUID+87, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Blazing Dreadsquall
(@CGUID+95, 0, 0, 0, 1, 0, 0, 0, 0, 0, '369262'), -- Dragonhunter Igordan - 369262 - -Unknown-
-- (@CGUID+96, 0, 0, 0, 1, 0, 0, 0, 0, 0, '46598'), -- Ban-Lu - 46598 - Ride Vehicle Hardcoded - !!! on transport - transport template not found !!!
-- (@CGUID+98, 0, 0, 0, 1, 0, 0, 0, 0, 0, '46598'), -- Ban-Lu - 46598 - Ride Vehicle Hardcoded - !!! on transport - transport template not found !!!
(@CGUID+103, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Dragon Target [DNT]
(@CGUID+104, 0, 0, 0, 1, 0, 0, 0, 0, 0, '369897'), -- Lava Phoenix - 369897 - -Unknown-
(@CGUID+107, 0, 0, 0, 1, 0, 0, 0, 0, 0, '369897'), -- Lava Phoenix - 369897 - -Unknown-
(@CGUID+117, 0, 0, 0, 1, 0, 0, 0, 0, 0, '369897'), -- Lava Phoenix - 369897 - -Unknown-
(@CGUID+118, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, '369897'), -- Lava Phoenix - 369897 - -Unknown-
(@CGUID+120, 0, 0, 0, 1, 0, 0, 0, 0, 0, '369897'), -- Lava Phoenix - 369897 - -Unknown-
(@CGUID+123, 0, 0, 0, 1, 0, 0, 0, 0, 0, '375948'), -- Magmammoth Bull - 375948 - -Unknown-
(@CGUID+128, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, '369897'), -- Lava Phoenix - 369897 - -Unknown-
(@CGUID+132, 0, 0, 0, 1, 0, 0, 0, 0, 0, '370034 375960'), -- Restless Lava - 370034 - -Unknown-, 375960 - -Unknown-
(@CGUID+133, 0, 0, 0, 1, 0, 0, 0, 0, 0, '391254'), -- Blazing Dreadsquall - 391254 - -Unknown-
(@CGUID+134, 0, 0, 0, 1, 0, 0, 0, 0, 0, '370034 375960'), -- Restless Lava - 370034 - -Unknown-, 375960 - -Unknown-
(@CGUID+135, 0, 0, 0, 1, 0, 0, 0, 0, 0, '370034 375960'), -- Restless Lava - 370034 - -Unknown-, 375960 - -Unknown-
(@CGUID+137, 0, 0, 0, 1, 0, 0, 0, 0, 0, '358419'), -- Qalashi Ragetamer - 358419 - -Unknown-
(@CGUID+138, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Dragon Target [DNT]
(@CGUID+139, 0, 0, 0, 1, 0, 0, 0, 0, 0, '375948'), -- Magmammoth Bull - 375948 - -Unknown-
(@CGUID+141, 0, 0, 0, 1, 0, 0, 0, 0, 0, '369897'), -- Lava Phoenix - 369897 - -Unknown-
(@CGUID+142, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, '369897'), -- Lava Phoenix - 369897 - -Unknown-
(@CGUID+143, 0, 0, 0, 1, 0, 0, 0, 0, 0, '369897'), -- Lava Phoenix - 369897 - -Unknown-
(@CGUID+145, 0, 0, 0, 1, 0, 0, 0, 0, 0, '391254'), -- Magmammoth Calf - 391254 - -Unknown-
(@CGUID+149, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, '369897'), -- Lava Phoenix - 369897 - -Unknown-
(@CGUID+151, 0, 0, 0, 1, 0, 0, 0, 0, 0, '369897'), -- Lava Phoenix - 369897 - -Unknown-
(@CGUID+152, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Dragon Target [DNT]
(@CGUID+153, 0, 0, 0, 1, 0, 0, 0, 0, 0, '369897'), -- Lava Phoenix - 369897 - -Unknown-
(@CGUID+154, 0, 0, 0, 1, 0, 0, 0, 0, 0, '375948'), -- Magmammoth Bull - 375948 - -Unknown-
(@CGUID+155, 0, 0, 0, 1, 0, 0, 0, 0, 0, '369897'), -- Lava Phoenix - 369897 - -Unknown-
(@CGUID+156, 0, 0, 0, 1, 0, 0, 0, 0, 0, '370034 364588'), -- Lava Elemental - 370034 - -Unknown-, 364588 - -Unknown-
(@CGUID+157, 0, 0, 0, 1, 0, 0, 0, 0, 0, '369897'), -- Lava Phoenix - 369897 - -Unknown-
(@CGUID+158, 0, 0, 0, 1, 0, 0, 0, 0, 0, '279802'), -- Right - 279802 - -Unknown-
(@CGUID+159, 0, 0, 0, 1, 0, 0, 0, 0, 0, '369897'), -- Lava Phoenix - 369897 - -Unknown-
(@CGUID+160, 0, 0, 0, 1, 0, 0, 0, 0, 0, '370034 364588'), -- Lava Elemental - 370034 - -Unknown-, 364588 - -Unknown-
(@CGUID+163, 0, 0, 0, 1, 0, 0, 0, 0, 0, '370034 375960'), -- Restless Lava - 370034 - -Unknown-, 375960 - -Unknown-
(@CGUID+165, 0, 0, 0, 1, 0, 0, 0, 0, 0, '370034 375960'), -- Restless Lava - 370034 - -Unknown-, 375960 - -Unknown-
(@CGUID+166, 0, 0, 0, 1, 0, 0, 0, 0, 0, '369897'), -- Lava Phoenix - 369897 - -Unknown-
(@CGUID+169, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, '369897'), -- Lava Phoenix - 369897 - -Unknown-
(@CGUID+170, 0, 0, 0, 1, 0, 0, 0, 0, 0, '375960'), -- Restless Rocks - 375960 - -Unknown-
(@CGUID+172, 0, 0, 0, 1, 0, 0, 0, 0, 0, '370034 375960'), -- Restless Lava - 370034 - -Unknown-, 375960 - -Unknown-
(@CGUID+174, 0, 0, 0, 1, 0, 0, 0, 0, 0, '370034 375960'), -- Restless Lava - 370034 - -Unknown-, 375960 - -Unknown-
(@CGUID+175, 0, 0, 0, 1, 0, 0, 0, 0, 0, '370034 375960'), -- Restless Lava - 370034 - -Unknown-, 375960 - -Unknown-
(@CGUID+177, 0, 0, 0, 1, 0, 0, 0, 0, 0, '375948'), -- Magmammoth Bull - 375948 - -Unknown-
(@CGUID+179, 0, 0, 0, 1, 0, 0, 0, 0, 0, '370034 375960'), -- Restless Lava - 370034 - -Unknown-, 375960 - -Unknown-
(@CGUID+181, 0, 0, 0, 1, 0, 0, 0, 0, 0, '375804'), -- Qalashi Marauder - 375804 - -Unknown-
(@CGUID+183, 0, 0, 0, 1, 0, 0, 0, 0, 0, '375960'), -- Restless Rocks - 375960 - -Unknown-
(@CGUID+184, 0, 0, 0, 1, 0, 0, 0, 0, 0, '375960'), -- Restless Rocks - 375960 - -Unknown-
(@CGUID+185, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Phoenix Hatchling
(@CGUID+186, 0, 0, 8, 1, 0, 0, 0, 0, 0, '279802'), -- Left - 279802 - -Unknown-
(@CGUID+187, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Dragon Target [DNT]
(@CGUID+189, 0, 0, 0, 1, 0, 0, 0, 0, 0, '369897'), -- Lava Phoenix - 369897 - -Unknown-
(@CGUID+195, 0, 0, 0, 1, 0, 0, 0, 0, 0, '375948'), -- Magmammoth Bull - 375948 - -Unknown-
(@CGUID+198, 0, 0, 16777216, 1, 0, 0, 0, 0, 0, '376065'), -- Captured Raven - 376065 - -Unknown-
(@CGUID+201, 0, 0, 0, 1, 0, 0, 0, 0, 0, '392594'), -- Meatgrinder Sotok - 392594 - -Unknown-
(@CGUID+209, 0, 0, 0, 1, 0, 0, 0, 0, 0, '366375'), -- Qalashi Ragetamer - 366375 - -Unknown-
(@CGUID+211, 0, 0, 0, 1, 0, 0, 0, 0, 0, '364588 391245'), -- Qalashi Flamemuzzler - 364588 - -Unknown-, 391245 - -Unknown-
(@CGUID+214, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, '369897'), -- Lava Phoenix - 369897 - -Unknown-
(@CGUID+215, 0, 0, 0, 1, 0, 0, 0, 0, 0, '370034 375960'), -- Restless Lava - 370034 - -Unknown-, 375960 - -Unknown-
(@CGUID+216, 0, 0, 0, 1, 0, 0, 0, 0, 0, '370034 375960'), -- Restless Lava - 370034 - -Unknown-, 375960 - -Unknown-
(@CGUID+217, 0, 0, 0, 1, 0, 0, 0, 0, 0, '370034 375960'), -- Restless Lava - 370034 - -Unknown-, 375960 - -Unknown-
(@CGUID+218, 0, 0, 0, 1, 0, 0, 0, 0, 0, '369897'), -- Lava Phoenix - 369897 - -Unknown-
(@CGUID+219, 0, 0, 0, 1, 0, 0, 0, 0, 0, '391254'), -- Lava Tarantula - 391254 - -Unknown-
(@CGUID+221, 0, 0, 0, 1, 0, 0, 0, 0, 0, '375804'), -- Qalashi Marauder - 375804 - -Unknown-
(@CGUID+223, 0, 0, 0, 1, 0, 0, 0, 0, 0, '369262'), -- Dragonhunter Igordan - 369262 - -Unknown-
-- (@CGUID+225, 0, 0, 0, 1, 0, 0, 0, 0, 0, '46598'), -- Ban-Lu - 46598 - Ride Vehicle Hardcoded - !!! on transport - transport template not found !!!
(@CGUID+243, 0, 0, 0, 1, 0, 0, 0, 0, 0, '391254'), -- Lava Snail - 391254 - -Unknown-
(@CGUID+249, 0, 0, 0, 1, 0, 0, 0, 0, 0, '369897'), -- Lava Phoenix - 369897 - -Unknown-
(@CGUID+251, 0, 0, 0, 1, 0, 0, 0, 0, 0, '369897'), -- Lava Phoenix - 369897 - -Unknown-
(@CGUID+254, 0, 0, 262144, 1, 0, 0, 0, 0, 0, '159474 376838'), -- Cracked Elemental - 159474 - Permanent Feign Death (NO Stun, Untrackable, Immune), 376838 - -Unknown-
(@CGUID+257, 0, 0, 262144, 1, 0, 0, 0, 0, 0, '159474 376838'), -- Cracked Elemental - 159474 - Permanent Feign Death (NO Stun, Untrackable, Immune), 376838 - -Unknown-
(@CGUID+258, 0, 0, 0, 1, 0, 0, 0, 0, 0, '391254'), -- Tranquil Vorquin - 391254 - -Unknown-
(@CGUID+260, 0, 0, 262144, 1, 0, 0, 0, 0, 0, '159474 376838'), -- Cracked Elemental - 159474 - Permanent Feign Death (NO Stun, Untrackable, Immune), 376838 - -Unknown-
(@CGUID+263, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Tiny Butterfly
(@CGUID+265, 0, 0, 0, 1, 0, 0, 0, 0, 0, '376071'), -- Caretaker Ventraz - 376071 - -Unknown-
(@CGUID+267, 0, 0, 262144, 1, 0, 0, 0, 0, 0, '159474 376838'), -- Cracked Elemental - 159474 - Permanent Feign Death (NO Stun, Untrackable, Immune), 376838 - -Unknown-
(@CGUID+269, 0, 0, 0, 1, 0, 0, 0, 0, 0, '369109 376252'), -- Ruby Culler - 369109 - -Unknown-, 376252 - -Unknown-
(@CGUID+280, 0, 0, 262144, 1, 0, 0, 0, 0, 0, '159474 376838'), -- Cracked Elemental - 159474 - Permanent Feign Death (NO Stun, Untrackable, Immune), 376838 - -Unknown-
-- (@CGUID+281, 0, 0, 0, 1, 0, 0, 0, 0, 0, '122729'), -- Merchant Maku - 122729 - Grand Expedition Yak - !!! on transport - transport template not found !!!
-- (@CGUID+282, 0, 0, 0, 1, 0, 0, 0, 0, 0, '122729'), -- Collector Unta - 122729 - Grand Expedition Yak - !!! on transport - transport template not found !!!
(@CGUID+285, 0, 0, 0, 1, 0, 0, 0, 0, 0, '376804'), -- Erupting Lasher - 376804 - -Unknown-
(@CGUID+286, 0, 0, 0, 1, 0, 0, 0, 0, 0, '370034'), -- Erupting Droplet - 370034 - -Unknown-
(@CGUID+288, 0, 0, 0, 1, 0, 0, 0, 0, 0, '370034'), -- Erupting Droplet - 370034 - -Unknown-
(@CGUID+290, 0, 0, 0, 1, 0, 0, 0, 0, 0, '370034'), -- Erupting Droplet - 370034 - -Unknown-
(@CGUID+291, 0, 0, 0, 1, 0, 0, 0, 0, 0, '370034 375720'), -- Erupting Droplet - 370034 - -Unknown-, 375720 - -Unknown-
(@CGUID+292, 0, 0, 0, 1, 0, 0, 0, 0, 0, '370034'), -- Erupting Droplet - 370034 - -Unknown-
(@CGUID+293, 0, 0, 262144, 1, 0, 0, 0, 0, 0, '159474 376838'), -- Cracked Elemental - 159474 - Permanent Feign Death (NO Stun, Untrackable, Immune), 376838 - -Unknown-
(@CGUID+294, 0, 0, 0, 1, 0, 0, 0, 0, 0, '370034'), -- Erupting Droplet - 370034 - -Unknown-
(@CGUID+295, 0, 0, 0, 1, 0, 0, 0, 0, 0, '370034 375720'), -- Erupting Droplet - 370034 - -Unknown-, 375720 - -Unknown-
(@CGUID+296, 0, 0, 262144, 1, 0, 0, 0, 0, 0, '159474 376838'), -- Cracked Elemental - 159474 - Permanent Feign Death (NO Stun, Untrackable, Immune), 376838 - -Unknown-
(@CGUID+299, 0, 0, 0, 1, 0, 0, 0, 0, 0, '375720 370034'), -- Erupting Droplet - 375720 - -Unknown-, 370034 - -Unknown-
(@CGUID+301, 0, 0, 0, 1, 0, 0, 0, 0, 0, '375720 370034'), -- Erupting Droplet - 375720 - -Unknown-, 370034 - -Unknown-
(@CGUID+302, 0, 0, 0, 1, 0, 0, 0, 0, 0, '375720 370034'), -- Erupting Droplet - 375720 - -Unknown-, 370034 - -Unknown-
(@CGUID+303, 0, 0, 0, 1, 0, 0, 0, 0, 0, '370034 375720'), -- Erupting Droplet - 370034 - -Unknown-, 375720 - -Unknown-
(@CGUID+304, 0, 0, 0, 1, 0, 0, 0, 0, 0, '370034 375720'), -- Erupting Droplet - 370034 - -Unknown-, 375720 - -Unknown-
(@CGUID+305, 0, 0, 0, 1, 0, 0, 0, 0, 0, '370034'), -- Erupting Droplet - 370034 - -Unknown-
(@CGUID+306, 0, 0, 0, 1, 0, 0, 0, 0, 0, '370034 375720'), -- Erupting Droplet - 370034 - -Unknown-, 375720 - -Unknown-
(@CGUID+307, 0, 0, 0, 1, 0, 0, 0, 0, 0, '370034 375720'), -- Erupting Droplet - 370034 - -Unknown-, 375720 - -Unknown-
(@CGUID+308, 0, 0, 0, 1, 0, 0, 0, 0, 0, '370034 375720'), -- Erupting Droplet - 370034 - -Unknown-, 375720 - -Unknown-
(@CGUID+309, 0, 0, 0, 1, 0, 0, 0, 0, 0, '375720 370034'), -- Erupting Droplet - 375720 - -Unknown-, 370034 - -Unknown-
(@CGUID+311, 0, 0, 0, 1, 0, 0, 0, 0, 0, '375720 370034'), -- Erupting Droplet - 375720 - -Unknown-, 370034 - -Unknown-
(@CGUID+312, 0, 0, 0, 1, 0, 0, 0, 0, 0, '370034'), -- Erupting Droplet - 370034 - -Unknown-
(@CGUID+313, 0, 0, 0, 1, 0, 0, 0, 0, 0, '370034'), -- Erupting Droplet - 370034 - -Unknown-
(@CGUID+316, 0, 0, 0, 1, 0, 0, 0, 0, 0, '370034 376749 375720 376754'), -- Erupting Droplet - 370034 - -Unknown-, 376749 - -Unknown-, 375720 - -Unknown-, 376754 - -Unknown-
(@CGUID+317, 0, 0, 0, 1, 0, 0, 0, 0, 0, '376861'), -- Erupting Lasher - 376861 - -Unknown-
(@CGUID+318, 0, 0, 0, 1, 0, 0, 0, 0, 0, '370034'), -- Erupting Droplet - 370034 - -Unknown-
(@CGUID+320, 0, 0, 0, 1, 0, 0, 0, 0, 0, '370034 375720'), -- Erupting Droplet - 370034 - -Unknown-, 375720 - -Unknown-
(@CGUID+323, 0, 0, 0, 1, 0, 0, 0, 0, 0, '370034 375720'), -- Erupting Droplet - 370034 - -Unknown-, 375720 - -Unknown-
(@CGUID+325, 0, 0, 0, 1, 0, 0, 0, 0, 0, '370034 375720'), -- Erupting Droplet - 370034 - -Unknown-, 375720 - -Unknown-
(@CGUID+326, 0, 0, 0, 1, 0, 0, 0, 0, 0, '370034 375720'), -- Erupting Droplet - 370034 - -Unknown-, 375720 - -Unknown-
(@CGUID+327, 0, 0, 0, 1, 0, 0, 0, 0, 0, '370034 375720'), -- Erupting Droplet - 370034 - -Unknown-, 375720 - -Unknown-
(@CGUID+329, 0, 0, 0, 1, 0, 0, 0, 0, 0, '370034 375720'), -- Erupting Droplet - 370034 - -Unknown-, 375720 - -Unknown-
(@CGUID+330, 0, 0, 0, 1, 0, 0, 0, 0, 0, '370034'), -- Erupting Droplet - 370034 - -Unknown-
(@CGUID+331, 0, 0, 0, 1, 0, 0, 0, 0, 0, '370034 375720'), -- Erupting Droplet - 370034 - -Unknown-, 375720 - -Unknown-
(@CGUID+332, 0, 0, 0, 1, 0, 0, 0, 0, 0, '370034 375720'), -- Erupting Droplet - 370034 - -Unknown-, 375720 - -Unknown-
(@CGUID+335, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Tiny Butterfly
(@CGUID+336, 0, 0, 0, 1, 0, 0, 0, 0, 0, '370034'), -- Erupting Droplet - 370034 - -Unknown-
(@CGUID+337, 0, 0, 0, 1, 0, 0, 0, 0, 0, '370034'), -- Erupting Droplet - 370034 - -Unknown-
(@CGUID+340, 0, 0, 0, 1, 0, 0, 0, 0, 0, '376861'), -- Erupting Lasher - 376861 - -Unknown-
(@CGUID+341, 0, 0, 0, 1, 0, 0, 0, 0, 0, '370034 376749 375720 376754'), -- Erupting Droplet - 370034 - -Unknown-, 376749 - -Unknown-, 375720 - -Unknown-, 376754 - -Unknown-
(@CGUID+344, 0, 0, 0, 1, 0, 0, 0, 0, 0, '376749'), -- Erupting Droplet - 376749 - -Unknown-
(@CGUID+345, 0, 0, 0, 1, 0, 0, 0, 0, 0, '376749'), -- Erupting Droplet - 376749 - -Unknown-
(@CGUID+349, 0, 0, 0, 1, 0, 0, 0, 0, 0, '376852'), -- Rocan the Mountain - 376852 - -Unknown-
(@CGUID+353, 0, 0, 0, 1, 0, 0, 0, 0, 0, '376749'), -- Erupting Droplet - 376749 - -Unknown-
(@CGUID+354, 0, 0, 0, 1, 0, 0, 0, 0, 0, '376749'), -- Erupting Droplet - 376749 - -Unknown-
(@CGUID+355, 0, 0, 0, 1, 0, 0, 0, 0, 0, '376749'), -- Erupting Droplet - 376749 - -Unknown-
(@CGUID+359, 0, 0, 0, 1, 0, 0, 0, 0, 0, '370034'), -- Erupting Droplet - 370034 - -Unknown-
(@CGUID+360, 0, 0, 0, 1, 0, 0, 0, 0, 0, '370034'), -- Erupting Droplet - 370034 - -Unknown-
(@CGUID+361, 0, 0, 0, 1, 0, 0, 0, 0, 0, '370034'), -- Erupting Droplet - 370034 - -Unknown-
(@CGUID+363, 0, 0, 0, 1, 0, 0, 0, 0, 0, '370034'), -- Erupting Droplet - 370034 - -Unknown-
(@CGUID+364, 0, 0, 0, 1, 0, 0, 0, 0, 0, '370034'), -- Erupting Droplet - 370034 - -Unknown-
(@CGUID+365, 0, 0, 0, 1, 0, 0, 0, 0, 0, '370034'), -- Erupting Droplet - 370034 - -Unknown-
(@CGUID+366, 0, 0, 0, 1, 0, 0, 0, 0, 0, '370034'), -- Erupting Droplet - 370034 - -Unknown-
(@CGUID+367, 0, 0, 0, 1, 0, 0, 0, 0, 0, '370034'), -- Erupting Droplet - 370034 - -Unknown-
(@CGUID+368, 0, 0, 0, 1, 0, 0, 0, 0, 0, '370034'), -- Erupting Droplet - 370034 - -Unknown-
(@CGUID+371, 0, 0, 0, 1, 0, 0, 0, 0, 0, '376749'), -- Erupting Droplet - 376749 - -Unknown-
(@CGUID+372, 0, 0, 0, 1, 0, 0, 0, 0, 0, '376749'), -- Erupting Droplet - 376749 - -Unknown-
(@CGUID+373, 0, 0, 0, 1, 0, 0, 0, 0, 0, '376749'), -- Erupting Droplet - 376749 - -Unknown-
(@CGUID+374, 0, 0, 0, 1, 0, 0, 0, 0, 0, '376749'), -- Erupting Droplet - 376749 - -Unknown-
(@CGUID+376, 0, 0, 0, 1, 0, 0, 0, 0, 0, '370034 376749'), -- Erupting Droplet - 370034 - -Unknown-, 376749 - -Unknown-
(@CGUID+377, 0, 0, 0, 1, 0, 0, 0, 0, 0, '376765'), -- Erupting Magma - 376765 - -Unknown-
(@CGUID+378, 0, 0, 0, 1, 0, 0, 0, 0, 0, '370034 376749'), -- Erupting Droplet - 370034 - -Unknown-, 376749 - -Unknown-
(@CGUID+379, 0, 0, 0, 1, 0, 0, 0, 0, 0, '376749'), -- Erupting Droplet - 376749 - -Unknown-
(@CGUID+380, 0, 0, 0, 1, 0, 0, 0, 0, 0, '376749'), -- Erupting Droplet - 376749 - -Unknown-
(@CGUID+381, 0, 0, 0, 1, 0, 0, 0, 0, 0, '370034 376749 375720 376754'), -- Erupting Droplet - 370034 - -Unknown-, 376749 - -Unknown-, 375720 - -Unknown-, 376754 - -Unknown-
(@CGUID+382, 0, 0, 0, 1, 0, 0, 0, 0, 0, '376765'), -- Erupting Magma - 376765 - -Unknown-
(@CGUID+383, 0, 0, 0, 1, 0, 0, 0, 0, 0, '376804'), -- Erupting Lasher - 376804 - -Unknown-
(@CGUID+384, 0, 0, 0, 1, 0, 0, 0, 0, 0, '376765'), -- Erupting Magma - 376765 - -Unknown-
(@CGUID+385, 0, 0, 0, 1, 0, 0, 0, 0, 0, '370034 376749'), -- Erupting Droplet - 370034 - -Unknown-, 376749 - -Unknown-
(@CGUID+386, 0, 0, 0, 1, 0, 0, 0, 0, 0, '370034 376749'), -- Erupting Droplet - 370034 - -Unknown-, 376749 - -Unknown-
(@CGUID+387, 0, 0, 0, 1, 0, 0, 0, 0, 0, '370034 376749 375720 376754'), -- Erupting Droplet - 370034 - -Unknown-, 376749 - -Unknown-, 375720 - -Unknown-, 376754 - -Unknown-
(@CGUID+388, 0, 0, 0, 1, 0, 0, 0, 0, 0, '376749'), -- Erupting Droplet - 376749 - -Unknown-
(@CGUID+389, 0, 0, 0, 1, 0, 0, 0, 0, 0, '376765'), -- Erupting Magma - 376765 - -Unknown-
(@CGUID+390, 0, 0, 0, 1, 0, 0, 0, 0, 0, '376749'), -- Erupting Droplet - 376749 - -Unknown-
(@CGUID+391, 0, 0, 0, 1, 0, 0, 0, 0, 0, '370034 376749 375720 376754'), -- Erupting Droplet - 370034 - -Unknown-, 376749 - -Unknown-, 375720 - -Unknown-, 376754 - -Unknown-
(@CGUID+392, 0, 0, 0, 1, 0, 0, 0, 0, 0, '370034'), -- Erupting Droplet - 370034 - -Unknown-
(@CGUID+393, 0, 0, 0, 1, 0, 0, 0, 0, 0, '370034'), -- Erupting Droplet - 370034 - -Unknown-
(@CGUID+394, 0, 0, 0, 1, 0, 0, 0, 0, 0, '375720 376754 370034'), -- Erupting Droplet - 375720 - -Unknown-, 376754 - -Unknown-, 370034 - -Unknown-
(@CGUID+395, 0, 0, 0, 1, 0, 0, 0, 0, 0, '370034'), -- Erupting Droplet - 370034 - -Unknown-
(@CGUID+396, 0, 0, 0, 1, 0, 0, 0, 0, 0, '370034'), -- Erupting Droplet - 370034 - -Unknown-
(@CGUID+397, 0, 0, 0, 1, 0, 0, 0, 0, 0, '370034'), -- Erupting Droplet - 370034 - -Unknown-
(@CGUID+398, 0, 0, 0, 1, 0, 0, 0, 0, 0, '370034'), -- Erupting Droplet - 370034 - -Unknown-
(@CGUID+399, 0, 0, 0, 1, 0, 0, 0, 0, 0, '376749'), -- Erupting Droplet - 376749 - -Unknown-
(@CGUID+400, 0, 0, 0, 1, 0, 0, 0, 0, 0, '376749'), -- Erupting Droplet - 376749 - -Unknown-
(@CGUID+401, 0, 0, 0, 1, 0, 0, 0, 0, 0, '376765'), -- Erupting Magma - 376765 - -Unknown-
(@CGUID+402, 0, 0, 0, 1, 0, 0, 0, 0, 0, '376749'), -- Erupting Droplet - 376749 - -Unknown-
(@CGUID+403, 0, 0, 0, 1, 0, 0, 0, 0, 0, '376804'), -- Erupting Lasher - 376804 - -Unknown-
(@CGUID+404, 0, 0, 0, 1, 0, 0, 0, 0, 0, '370034 376749'), -- Erupting Droplet - 370034 - -Unknown-, 376749 - -Unknown-
(@CGUID+405, 0, 0, 0, 1, 0, 0, 0, 0, 0, '376749'), -- Erupting Droplet - 376749 - -Unknown-
(@CGUID+406, 0, 0, 0, 1, 0, 0, 0, 0, 0, '370034 376749 375720 376754'), -- Erupting Droplet - 370034 - -Unknown-, 376749 - -Unknown-, 375720 - -Unknown-, 376754 - -Unknown-
(@CGUID+407, 0, 0, 0, 1, 0, 0, 0, 0, 0, '376749'), -- Erupting Droplet - 376749 - -Unknown-
(@CGUID+408, 0, 0, 0, 1, 0, 0, 0, 0, 0, '376749'), -- Erupting Droplet - 376749 - -Unknown-
(@CGUID+409, 0, 0, 0, 1, 0, 0, 0, 0, 0, '376765'), -- Erupting Magma - 376765 - -Unknown-
(@CGUID+410, 0, 0, 0, 1, 0, 0, 0, 0, 0, '376749'), -- Erupting Droplet - 376749 - -Unknown-
(@CGUID+411, 0, 0, 0, 1, 0, 0, 0, 0, 0, '376749'), -- Erupting Droplet - 376749 - -Unknown-
(@CGUID+412, 0, 0, 0, 1, 0, 0, 0, 0, 0, '376765'), -- Erupting Magma - 376765 - -Unknown-
(@CGUID+413, 0, 0, 0, 1, 0, 0, 0, 0, 0, '376749'), -- Erupting Droplet - 376749 - -Unknown-
(@CGUID+414, 0, 0, 0, 1, 0, 0, 0, 0, 0, '376749'), -- Erupting Droplet - 376749 - -Unknown-
(@CGUID+415, 0, 0, 0, 1, 0, 0, 0, 0, 0, '376749'), -- Erupting Droplet - 376749 - -Unknown-
(@CGUID+416, 0, 0, 0, 1, 0, 0, 0, 0, 0, '376749'), -- Erupting Droplet - 376749 - -Unknown-
(@CGUID+417, 0, 0, 0, 1, 0, 0, 0, 0, 0, '376804'), -- Erupting Lasher - 376804 - -Unknown-
(@CGUID+419, 0, 0, 0, 1, 0, 0, 0, 0, 0, '370034 376749'), -- Erupting Droplet - 370034 - -Unknown-, 376749 - -Unknown-
(@CGUID+420, 0, 0, 0, 1, 0, 0, 0, 0, 0, '376749'), -- Erupting Droplet - 376749 - -Unknown-
(@CGUID+421, 0, 0, 0, 1, 0, 0, 0, 0, 0, '376749'), -- Erupting Droplet - 376749 - -Unknown-
(@CGUID+422, 0, 0, 0, 1, 0, 0, 0, 0, 0, '376749'), -- Erupting Droplet - 376749 - -Unknown-
(@CGUID+423, 0, 0, 0, 1, 0, 0, 0, 0, 0, '376749'), -- Erupting Droplet - 376749 - -Unknown-
(@CGUID+424, 0, 0, 0, 1, 0, 0, 0, 0, 0, '376749'), -- Erupting Droplet - 376749 - -Unknown-
(@CGUID+425, 0, 0, 0, 1, 0, 0, 0, 0, 0, '376749'), -- Erupting Droplet - 376749 - -Unknown-
(@CGUID+426, 0, 0, 0, 1, 0, 0, 0, 0, 0, '376749'), -- Erupting Droplet - 376749 - -Unknown-
(@CGUID+427, 0, 0, 0, 1, 0, 0, 0, 0, 0, '370034 376749'), -- Erupting Droplet - 370034 - -Unknown-, 376749 - -Unknown-
(@CGUID+428, 0, 0, 0, 1, 0, 0, 0, 0, 0, '370034 376749 375720 376754'), -- Erupting Droplet - 370034 - -Unknown-, 376749 - -Unknown-, 375720 - -Unknown-, 376754 - -Unknown-
(@CGUID+429, 0, 0, 0, 1, 0, 0, 0, 0, 0, '370034 376749'), -- Erupting Droplet - 370034 - -Unknown-, 376749 - -Unknown-
(@CGUID+430, 0, 0, 0, 1, 0, 0, 0, 0, 0, '369897'), -- Carrion Phoenix - 369897 - -Unknown-
(@CGUID+433, 0, 0, 0, 1, 0, 0, 0, 0, 0, '376749'), -- Erupting Droplet - 376749 - -Unknown-
(@CGUID+436, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Tiny Butterfly
(@CGUID+440, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Dreadsquall Feaster
(@CGUID+443, 0, 0, 0, 1, 0, 0, 0, 0, 0, '369897'), -- Carrion Phoenix - 369897 - -Unknown-
(@CGUID+446, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Tiny Butterfly
(@CGUID+447, 0, 0, 0, 1, 0, 0, 0, 0, 0, '376749'), -- Erupting Droplet - 376749 - -Unknown-
(@CGUID+448, 0, 0, 0, 1, 0, 0, 0, 0, 0, '369897'), -- Carrion Phoenix - 369897 - -Unknown-
(@CGUID+449, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Dreadsquall Feaster
(@CGUID+452, 0, 0, 0, 1, 0, 0, 0, 0, 0, '369897'), -- Carrion Phoenix - 369897 - -Unknown-
(@CGUID+462, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Uktulut Protector
(@CGUID+464, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Drakewing
(@CGUID+465, 0, 107330, 0, 257, 0, 0, 0, 0, 0, ''), -- Uktulut Protector
(@CGUID+467, 0, 0, 0, 257, 0, 25917, 0, 0, 0, ''), -- Uktulut Protector
(@CGUID+477, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Tiny Butterfly
(@CGUID+479, 0, 0, 0, 1, 0, 0, 0, 0, 0, '391254 391255'), -- Wild Argali - 391254 - -Unknown-, 391255 - -Unknown-
(@CGUID+482, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Tiny Butterfly
(@CGUID+489, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Tiny Butterfly
(@CGUID+495, 0, 0, 0, 1, 0, 0, 0, 0, 0, '391254'), -- Wild Argali - 391254 - -Unknown-
(@CGUID+513, 0, 0, 0, 1, 0, 0, 0, 0, 0, '381535'); -- Crushing Elemental - 381535 - -Unknown-

INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `aiAnimKit`, `movementAnimKit`, `meleeAnimKit`, `visibilityDistanceType`, `auras`) VALUES
(@CGUID+524, 0, 0, 0, 1, 0, 0, 0, 0, 0, '364022'), -- Raging Elemental - 364022 - -Unknown-
(@CGUID+525, 0, 0, 0, 1, 0, 0, 0, 0, 0, '377717'), -- Earthshatter Elemental - 377717 - -Unknown-
(@CGUID+532, 0, 0, 0, 1, 0, 0, 0, 0, 0, '377717'), -- Earthshatter Elemental - 377717 - -Unknown-
(@CGUID+540, 0, 0, 0, 1, 0, 0, 0, 0, 0, '391254'), -- Wild Rockfang - 391254 - -Unknown-
(@CGUID+549, 0, 0, 0, 1, 0, 0, 0, 0, 0, '42459'), -- Molten Primalist - 42459 - Dual Wield
(@CGUID+552, 0, 0, 0, 1, 0, 0, 0, 0, 0, '369897'), -- Lava Phoenix - 369897 - -Unknown-
(@CGUID+560, 0, 0, 0, 1, 0, 0, 0, 0, 0, '42459 364117'), -- Molten Primalist - 42459 - Dual Wield, 364117 - -Unknown-
(@CGUID+561, 0, 0, 0, 1, 0, 0, 0, 0, 0, '42459 364117'), -- Molten Primalist - 42459 - Dual Wield, 364117 - -Unknown-
(@CGUID+564, 0, 0, 0, 1, 0, 0, 0, 0, 0, '369706'), -- Tarasek Elementalist - 369706 - -Unknown-
(@CGUID+567, 0, 0, 0, 1, 0, 0, 0, 0, 0, '369897'), -- Lava Phoenix - 369897 - -Unknown-
(@CGUID+568, 0, 0, 0, 1, 0, 0, 0, 0, 0, '42459 364220'), -- Molten Primalist - 42459 - Dual Wield, 364220 - -Unknown-
(@CGUID+570, 0, 0, 0, 1, 0, 0, 0, 0, 0, '364117'), -- Lavacaller Primalist - 364117 - -Unknown-
(@CGUID+572, 0, 0, 0, 1, 0, 0, 0, 0, 0, '376804'), -- Unleashed Lavaburst - 376804 - -Unknown-
(@CGUID+575, 0, 0, 0, 1, 0, 0, 0, 0, 0, '387072 364117'), -- Lavacaller Primalist - 387072 - -Unknown-, 364117 - -Unknown-
(@CGUID+578, 0, 0, 0, 1, 0, 0, 0, 0, 0, '364026'), -- Lavacaller Primalist - 364026 - -Unknown-
(@CGUID+581, 0, 0, 0, 1, 0, 0, 0, 0, 0, '387072 364117'), -- Lavacaller Primalist - 387072 - -Unknown-, 364117 - -Unknown-
(@CGUID+582, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, '369897 391254'), -- Lava Phoenix - 369897 - -Unknown-, 391254 - -Unknown-
(@CGUID+584, 0, 0, 50331648, 1, 0, 0, 0, 0, 4, '384678'), -- Dragon Glyph - 384678 - -Unknown-
(@CGUID+586, 0, 0, 0, 1, 0, 0, 0, 0, 0, '364117'), -- Lavacaller Primalist - 364117 - -Unknown-
(@CGUID+590, 0, 0, 0, 1, 0, 0, 0, 0, 0, '369897'), -- Lava Phoenix - 369897 - -Unknown-
(@CGUID+594, 0, 0, 0, 1, 0, 0, 0, 0, 0, '376765'), -- Unleashed Lavaburst - 376765 - -Unknown-
(@CGUID+596, 0, 0, 0, 1, 0, 0, 0, 0, 0, '385839'), -- Captain Exposition - 385839 - -Unknown-
(@CGUID+598, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, '369897'), -- Lava Phoenix - 369897 - -Unknown-
(@CGUID+606, 0, 0, 0, 1, 0, 0, 0, 0, 0, '42459'), -- Molten Primalist - 42459 - Dual Wield
(@CGUID+607, 0, 0, 0, 1, 0, 0, 0, 0, 0, '369897'), -- Lava Phoenix - 369897 - -Unknown-
(@CGUID+608, 0, 0, 0, 1, 0, 0, 0, 0, 0, '387072 364117'), -- Lavacaller Primalist - 387072 - -Unknown-, 364117 - -Unknown-
(@CGUID+609, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, '376690'), -- Infused Ruby Whelpling - 376690 - -Unknown-
(@CGUID+610, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, '376690'), -- Infused Ruby Whelpling - 376690 - -Unknown-
(@CGUID+611, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, '376690'), -- Infused Ruby Whelpling - 376690 - -Unknown-
(@CGUID+612, 0, 0, 0, 1, 0, 0, 0, 0, 0, '387072 385552'), -- Lavacaller Primalist - 387072 - -Unknown-, 385552 - -Unknown-
(@CGUID+613, 0, 0, 0, 1, 0, 0, 0, 0, 0, '364220'), -- Lavacaller Primalist - 364220 - -Unknown-
(@CGUID+617, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, '376690'), -- Infused Ruby Whelpling - 376690 - -Unknown-
(@CGUID+618, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, '376690'), -- Infused Ruby Whelpling - 376690 - -Unknown-
(@CGUID+620, 0, 0, 0, 1, 0, 0, 0, 0, 0, '112080'), -- Sendrax - 112080 - Root Self
(@CGUID+623, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, '376690'), -- Infused Ruby Whelpling - 376690 - -Unknown-
(@CGUID+627, 0, 0, 0, 1, 0, 0, 0, 0, 0, '369897'), -- Lava Phoenix - 369897 - -Unknown-
(@CGUID+628, 0, 0, 0, 1, 0, 0, 0, 0, 0, '391254'), -- Stubborn Hornswog - 391254 - -Unknown-
(@CGUID+630, 0, 0, 0, 1, 0, 0, 0, 0, 0, '364118'), -- Lavacaller Primalist - 364118 - -Unknown-
(@CGUID+631, 0, 0, 0, 1, 0, 0, 0, 0, 0, '384742'), -- Ruby Dragon Egg - 384742 - -Unknown-
(@CGUID+632, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, '376690'), -- Infused Ruby Whelpling - 376690 - -Unknown-
(@CGUID+634, 0, 0, 0, 1, 0, 0, 0, 0, 0, '384742'), -- Ruby Dragon Egg - 384742 - -Unknown-
(@CGUID+635, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, '376690'), -- Infused Ruby Whelpling - 376690 - -Unknown-
(@CGUID+636, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, '376690'), -- Infused Ruby Whelpling - 376690 - -Unknown-
(@CGUID+637, 0, 0, 0, 1, 0, 0, 0, 0, 0, '384742'), -- Ruby Dragon Egg - 384742 - -Unknown-
(@CGUID+640, 0, 0, 0, 1, 0, 0, 0, 0, 0, '364220'), -- Lavacaller Primalist - 364220 - -Unknown-
(@CGUID+641, 0, 0, 0, 1, 0, 0, 0, 0, 0, '364118'), -- Lavacaller Primalist - 364118 - -Unknown-
(@CGUID+646, 0, 0, 0, 1, 0, 0, 0, 0, 0, '376804'), -- Unleashed Lavaburst - 376804 - -Unknown-
(@CGUID+647, 0, 0, 0, 1, 0, 0, 0, 0, 0, '376861'), -- Unleashed Lavaburst - 376861 - -Unknown-
(@CGUID+649, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, '376690'), -- Infused Ruby Whelpling - 376690 - -Unknown-
(@CGUID+650, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, '376690'), -- Infused Ruby Whelpling - 376690 - -Unknown-
(@CGUID+651, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, '376690'), -- Infused Ruby Whelpling - 376690 - -Unknown-
(@CGUID+652, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, '376690'), -- Infused Ruby Whelpling - 376690 - -Unknown-
(@CGUID+653, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, '376690'), -- Infused Ruby Whelpling - 376690 - -Unknown-
(@CGUID+654, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, '376690'), -- Infused Ruby Whelpling - 376690 - -Unknown-
(@CGUID+655, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, '376690'), -- Infused Ruby Whelpling - 376690 - -Unknown-
(@CGUID+656, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, '376690'), -- Infused Ruby Whelpling - 376690 - -Unknown-
(@CGUID+657, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, '376690'), -- Infused Ruby Whelpling - 376690 - -Unknown-
-- (@CGUID+658, 0, 0, 0, 1, 0, 0, 0, 0, 0, '46598'), -- Ban-Lu - 46598 - Ride Vehicle Hardcoded - !!! on transport - transport template not found !!!
(@CGUID+660, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, '376690'), -- Infused Ruby Whelpling - 376690 - -Unknown-
(@CGUID+661, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, '376690'), -- Infused Ruby Whelpling - 376690 - -Unknown-
(@CGUID+662, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, '376690'), -- Infused Ruby Whelpling - 376690 - -Unknown-
(@CGUID+663, 0, 0, 0, 1, 0, 0, 0, 0, 0, '112080'), -- Sendrax - 112080 - Root Self
(@CGUID+665, 0, 0, 0, 1, 0, 0, 0, 0, 0, '364117'), -- Lavacaller Primalist - 364117 - -Unknown-
(@CGUID+669, 0, 0, 0, 1, 0, 0, 0, 0, 0, '364118'), -- Lavacaller Primalist - 364118 - -Unknown-
(@CGUID+670, 0, 0, 0, 1, 0, 0, 0, 0, 0, '364118'), -- Lavacaller Primalist - 364118 - -Unknown-
(@CGUID+671, 0, 0, 0, 1, 0, 0, 0, 0, 0, '364153'), -- Lavacaller Primalist - 364153 - -Unknown-
(@CGUID+672, 0, 0, 0, 1, 0, 0, 0, 0, 0, '376765'), -- Unleashed Lavaburst - 376765 - -Unknown-
-- (@CGUID+673, 0, 0, 0, 1, 0, 0, 0, 0, 0, '46598'), -- Ban-Lu - 46598 - Ride Vehicle Hardcoded - !!! on transport - transport template not found !!!
-- (@CGUID+676, 0, 0, 0, 1, 0, 0, 0, 0, 0, '61424'), -- Drix Blackwrench - 61424 - Traveler's Tundra Mammoth - !!! on transport - transport template not found !!!
-- (@CGUID+677, 0, 0, 0, 1, 0, 0, 0, 0, 0, '61424'), -- Mojodishu - 61424 - Traveler's Tundra Mammoth - !!! on transport - transport template not found !!!
(@CGUID+679, 0, 0, 0, 1, 0, 0, 0, 0, 0, '376804'), -- Unleashed Lavaburst - 376804 - -Unknown-
(@CGUID+680, 0, 0, 0, 1, 0, 0, 0, 0, 0, '369897'), -- Lava Phoenix - 369897 - -Unknown-
(@CGUID+681, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, '376690'), -- Infused Ruby Whelpling - 376690 - -Unknown-
(@CGUID+683, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, '376690'), -- Infused Ruby Whelpling - 376690 - -Unknown-
(@CGUID+684, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, '376690'), -- Infused Ruby Whelpling - 376690 - -Unknown-
(@CGUID+685, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, '376690'), -- Infused Ruby Whelpling - 376690 - -Unknown-
(@CGUID+686, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, '376690'), -- Infused Ruby Whelpling - 376690 - -Unknown-
(@CGUID+687, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, '376690'), -- Infused Ruby Whelpling - 376690 - -Unknown-
(@CGUID+689, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, '376690'), -- Infused Ruby Whelpling - 376690 - -Unknown-
(@CGUID+690, 0, 0, 0, 1, 0, 0, 0, 0, 0, '384742'), -- Ruby Dragon Egg - 384742 - -Unknown-
(@CGUID+691, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, '376690'), -- Infused Ruby Whelpling - 376690 - -Unknown-
(@CGUID+692, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, '376690'), -- Infused Ruby Whelpling - 376690 - -Unknown-
(@CGUID+693, 0, 0, 0, 1, 0, 0, 0, 0, 0, '384742'), -- Ruby Dragon Egg - 384742 - -Unknown-
(@CGUID+694, 0, 0, 0, 1, 0, 0, 0, 0, 0, '384742'), -- Ruby Dragon Egg - 384742 - -Unknown-
(@CGUID+696, 0, 0, 0, 1, 0, 0, 0, 0, 0, '370034'), -- Restless Lava - 370034 - -Unknown-
(@CGUID+697, 0, 0, 0, 1, 0, 0, 0, 0, 0, '370034'), -- Restless Lava - 370034 - -Unknown-
(@CGUID+698, 0, 0, 0, 1, 0, 0, 0, 0, 0, '370034'), -- Restless Lava - 370034 - -Unknown-
(@CGUID+699, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, '369897'), -- Lava Phoenix - 369897 - -Unknown-
(@CGUID+700, 0, 0, 0, 1, 0, 0, 0, 0, 0, '112080'), -- Sendrax - 112080 - Root Self
(@CGUID+701, 0, 0, 0, 1, 0, 0, 0, 0, 0, '387072'), -- Lavacaller Primalist - 387072 - -Unknown-
(@CGUID+703, 0, 0, 0, 1, 0, 0, 0, 0, 0, '387072'), -- Lavacaller Primalist - 387072 - -Unknown-
(@CGUID+704, 0, 0, 0, 1, 0, 0, 0, 0, 0, '387072'), -- Lavacaller Primalist - 387072 - -Unknown-
(@CGUID+705, 0, 0, 0, 1, 0, 0, 0, 0, 0, '387072'), -- Lavacaller Primalist - 387072 - -Unknown-
(@CGUID+706, 0, 0, 0, 1, 0, 0, 0, 0, 0, '364220'), -- Molten Primalist - 364220 - -Unknown-
(@CGUID+707, 0, 0, 0, 1, 0, 0, 0, 0, 0, '369706'), -- Primal Tarasek - 369706 - -Unknown-
(@CGUID+708, 0, 0, 0, 1, 0, 0, 0, 0, 0, '42459'), -- Molten Primalist - 42459 - Dual Wield
(@CGUID+709, 0, 0, 0, 1, 0, 0, 0, 0, 0, '42459'), -- Molten Primalist - 42459 - Dual Wield
(@CGUID+710, 0, 0, 0, 1, 0, 0, 0, 0, 0, '376765'), -- Unleashed Lavaburst - 376765 - -Unknown-
(@CGUID+712, 0, 0, 0, 1, 0, 0, 0, 0, 0, '364220'), -- Lavacaller Primalist - 364220 - -Unknown-
(@CGUID+716, 0, 0, 0, 1, 0, 0, 0, 0, 0, '364118'), -- Lavacaller Primalist - 364118 - -Unknown-
(@CGUID+717, 0, 0, 0, 1, 0, 0, 0, 0, 0, '364153'), -- Lavacaller Primalist - 364153 - -Unknown-
(@CGUID+718, 0, 0, 0, 1, 0, 0, 0, 0, 0, '364118'), -- Lavacaller Primalist - 364118 - -Unknown-
(@CGUID+719, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, '376690'), -- Infused Ruby Whelpling - 376690 - -Unknown-
(@CGUID+720, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, '376690'), -- Infused Ruby Whelpling - 376690 - -Unknown-
(@CGUID+721, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, '376690'), -- Infused Ruby Whelpling - 376690 - -Unknown-
(@CGUID+722, 0, 0, 0, 1, 0, 0, 0, 0, 0, '112080'), -- Sendrax - 112080 - Root Self
(@CGUID+724, 0, 0, 0, 1, 0, 0, 0, 0, 0, '376765'), -- Unleashed Lavaburst - 376765 - -Unknown-
(@CGUID+726, 0, 0, 0, 1, 0, 0, 0, 0, 0, '42459'), -- Molten Primalist - 42459 - Dual Wield
(@CGUID+730, 0, 0, 0, 1, 0, 0, 0, 0, 0, '376765'), -- Unleashed Lavaburst - 376765 - -Unknown-
(@CGUID+731, 0, 0, 0, 1, 0, 0, 0, 0, 0, '42459'), -- Molten Primalist - 42459 - Dual Wield
-- (@CGUID+732, 0, 0, 0, 1, 0, 0, 0, 0, 0, '46598'), -- Ban-Lu - 46598 - Ride Vehicle Hardcoded - !!! on transport - transport template not found !!!
(@CGUID+733, 0, 0, 0, 1, 0, 0, 0, 0, 0, '376861'), -- Unleashed Lavaburst - 376861 - -Unknown-
(@CGUID+734, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, '376690'), -- Infused Ruby Whelpling - 376690 - -Unknown-
(@CGUID+735, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, '376690'), -- Infused Ruby Whelpling - 376690 - -Unknown-
(@CGUID+736, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, '376690'), -- Infused Ruby Whelpling - 376690 - -Unknown-
(@CGUID+737, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, '376690'), -- Infused Ruby Whelpling - 376690 - -Unknown-
(@CGUID+738, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, '376690'), -- Infused Ruby Whelpling - 376690 - -Unknown-
(@CGUID+739, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, '376690'), -- Infused Ruby Whelpling - 376690 - -Unknown-
(@CGUID+740, 0, 0, 0, 1, 0, 0, 0, 0, 0, '112080'), -- Sendrax - 112080 - Root Self
(@CGUID+742, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, '376690'), -- Infused Ruby Whelpling - 376690 - -Unknown-
(@CGUID+743, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, '376690'), -- Infused Ruby Whelpling - 376690 - -Unknown-
(@CGUID+744, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, '376690'), -- Infused Ruby Whelpling - 376690 - -Unknown-
(@CGUID+745, 0, 0, 0, 1, 0, 0, 0, 0, 0, '364117'), -- Molten Primalist - 364117 - -Unknown-
(@CGUID+746, 0, 0, 0, 1, 0, 0, 0, 0, 0, '387072'), -- Lavacaller Primalist - 387072 - -Unknown-
(@CGUID+747, 0, 0, 0, 1, 0, 0, 0, 0, 0, '364220'), -- Molten Primalist - 364220 - -Unknown-
(@CGUID+748, 0, 0, 0, 1, 0, 0, 0, 0, 0, '387072'), -- Lavacaller Primalist - 387072 - -Unknown-
(@CGUID+749, 0, 0, 0, 1, 0, 0, 0, 0, 0, '364220'), -- Lavacaller Primalist - 364220 - -Unknown-
(@CGUID+750, 0, 0, 0, 1, 0, 0, 0, 0, 0, '387072 364117'), -- Lavacaller Primalist - 387072 - -Unknown-, 364117 - -Unknown-
(@CGUID+751, 0, 0, 0, 1, 0, 0, 0, 0, 0, '387072 385552'), -- Lavacaller Primalist - 387072 - -Unknown-, 385552 - -Unknown-
(@CGUID+752, 0, 0, 0, 1, 0, 0, 0, 0, 0, '364220'), -- Lavacaller Primalist - 364220 - -Unknown-
(@CGUID+753, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, '376690'), -- Infused Ruby Whelpling - 376690 - -Unknown-
(@CGUID+754, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, '376690'), -- Infused Ruby Whelpling - 376690 - -Unknown-
(@CGUID+755, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, '376690'), -- Infused Ruby Whelpling - 376690 - -Unknown-
(@CGUID+757, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, '376690'), -- Infused Ruby Whelpling - 376690 - -Unknown-
(@CGUID+758, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, '376690'), -- Infused Ruby Whelpling - 376690 - -Unknown-
(@CGUID+759, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, '376690'), -- Infused Ruby Whelpling - 376690 - -Unknown-
(@CGUID+760, 0, 0, 0, 1, 0, 0, 0, 0, 0, '376765'), -- Unleashed Lavaburst - 376765 - -Unknown-
(@CGUID+761, 0, 0, 0, 1, 0, 0, 0, 0, 0, '364117'), -- Lavacaller Primalist - 364117 - -Unknown-
(@CGUID+762, 0, 0, 0, 1, 0, 0, 0, 0, 0, '376765'), -- Unleashed Lavaburst - 376765 - -Unknown-
(@CGUID+763, 0, 0, 65536, 1, 0, 0, 0, 0, 0, '9036 10848'), -- Spirit Healer - 9036 - Ghost, 10848 - Shroud of Death
(@CGUID+764, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, '376690'), -- Infused Ruby Whelpling - 376690 - -Unknown-
(@CGUID+767, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, '376690'), -- Infused Ruby Whelpling - 376690 - -Unknown-
(@CGUID+769, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, '376690'), -- Infused Ruby Whelpling - 376690 - -Unknown-
(@CGUID+770, 0, 0, 0, 1, 0, 0, 0, 0, 0, '364153'), -- Lavacaller Primalist - 364153 - -Unknown-
(@CGUID+771, 0, 0, 0, 1, 0, 0, 0, 0, 0, '42459'), -- Molten Primalist - 42459 - Dual Wield
(@CGUID+774, 0, 0, 0, 1, 0, 0, 0, 0, 0, '364118'), -- Lavacaller Primalist - 364118 - -Unknown-
(@CGUID+775, 0, 0, 0, 1, 0, 0, 0, 0, 0, '376765'), -- Unleashed Lavaburst - 376765 - -Unknown-
(@CGUID+779, 0, 0, 0, 1, 0, 0, 0, 0, 0, '364117'), -- Lavacaller Primalist - 364117 - -Unknown-
(@CGUID+781, 0, 0, 0, 1, 0, 0, 0, 0, 0, '376765'), -- Unleashed Lavaburst - 376765 - -Unknown-
(@CGUID+783, 0, 0, 0, 1, 0, 0, 0, 0, 0, '364118'), -- Lavacaller Primalist - 364118 - -Unknown-
(@CGUID+784, 0, 0, 0, 1, 0, 0, 0, 0, 0, '387072'), -- Lavacaller Primalist - 387072 - -Unknown-
(@CGUID+785, 0, 0, 0, 1, 0, 0, 0, 0, 0, '387072'), -- Lavacaller Primalist - 387072 - -Unknown-
(@CGUID+786, 0, 0, 0, 1, 0, 0, 0, 0, 0, '391245'), -- Tarasek Elementalist - 391245 - -Unknown-
(@CGUID+787, 0, 0, 0, 1, 0, 0, 0, 0, 0, '387072'), -- Lavacaller Primalist - 387072 - -Unknown-
(@CGUID+789, 0, 0, 0, 1, 0, 0, 0, 0, 0, '387072'), -- Lavacaller Primalist - 387072 - -Unknown-
(@CGUID+790, 0, 0, 0, 1, 0, 0, 0, 0, 0, '364220'), -- Lavacaller Primalist - 364220 - -Unknown-
(@CGUID+793, 0, 0, 0, 1, 0, 0, 0, 0, 0, '364118'), -- Lavacaller Primalist - 364118 - -Unknown-
(@CGUID+794, 0, 0, 0, 1, 0, 0, 0, 0, 0, '376804'), -- Unleashed Lavaburst - 376804 - -Unknown-
(@CGUID+795, 0, 0, 0, 1, 0, 0, 0, 0, 0, '112080'), -- Sendrax - 112080 - Root Self
(@CGUID+797, 0, 0, 0, 1, 0, 0, 0, 0, 0, '42459 364117'), -- Molten Primalist - 42459 - Dual Wield, 364117 - -Unknown-
(@CGUID+798, 0, 0, 0, 1, 0, 0, 0, 0, 0, '42459 364117'), -- Molten Primalist - 42459 - Dual Wield, 364117 - -Unknown-
(@CGUID+799, 0, 0, 0, 1, 0, 0, 0, 0, 0, '364118'), -- Lavacaller Primalist - 364118 - -Unknown-
(@CGUID+800, 0, 0, 0, 1, 0, 0, 0, 0, 0, '376804'), -- Unleashed Lavaburst - 376804 - -Unknown-
(@CGUID+803, 0, 0, 0, 1, 0, 0, 0, 0, 0, '42459'), -- Molten Primalist - 42459 - Dual Wield
(@CGUID+804, 0, 0, 0, 1, 0, 0, 0, 0, 0, '42459'), -- Molten Primalist - 42459 - Dual Wield
(@CGUID+809, 0, 0, 0, 1, 0, 0, 0, 0, 0, '42459'), -- Molten Primalist - 42459 - Dual Wield
(@CGUID+810, 0, 0, 0, 1, 0, 0, 0, 0, 0, '369897'), -- Lava Phoenix - 369897 - -Unknown-
(@CGUID+814, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, '369897'), -- Lava Phoenix - 369897 - -Unknown-
(@CGUID+815, 0, 0, 0, 1, 0, 0, 0, 0, 0, '42459'), -- Molten Primalist - 42459 - Dual Wield
(@CGUID+817, 0, 0, 0, 1, 0, 0, 0, 0, 0, '42459'), -- Molten Primalist - 42459 - Dual Wield
(@CGUID+818, 0, 0, 0, 1, 0, 0, 0, 0, 0, '42459'), -- Molten Primalist - 42459 - Dual Wield
(@CGUID+821, 0, 0, 0, 1, 0, 0, 0, 0, 0, '364118'), -- Lavacaller Primalist - 364118 - -Unknown-
(@CGUID+826, 0, 0, 0, 1, 0, 0, 0, 0, 0, '112080'), -- Sendrax - 112080 - Root Self
(@CGUID+827, 0, 0, 0, 1, 0, 0, 0, 0, 0, '42459'), -- Molten Primalist - 42459 - Dual Wield
(@CGUID+831, 0, 0, 0, 1, 0, 0, 0, 0, 0, '112080'), -- Sendrax - 112080 - Root Self
(@CGUID+834, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Territorial Axebeak
(@CGUID+836, 0, 0, 0, 1, 0, 0, 0, 0, 0, '42459'), -- Molten Primalist - 42459 - Dual Wield
(@CGUID+838, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Territorial Axebeak
(@CGUID+840, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Territorial Axebeak
(@CGUID+841, 0, 0, 0, 1, 0, 0, 0, 0, 0, '42459'), -- Molten Primalist - 42459 - Dual Wield
(@CGUID+842, 0, 0, 0, 1, 0, 0, 0, 0, 0, '364117'), -- Tarasek Elementalist - 364117 - -Unknown-
(@CGUID+843, 0, 0, 0, 1, 0, 0, 0, 0, 0, '369643'), -- Lavacaller Primalist - 369643 - -Unknown-
(@CGUID+844, 0, 0, 0, 1, 0, 0, 0, 0, 0, '112080'), -- Sendrax - 112080 - Root Self
(@CGUID+845, 0, 0, 0, 1, 0, 0, 0, 0, 0, '376804'), -- Unleashed Lavaburst - 376804 - -Unknown-
(@CGUID+846, 0, 0, 0, 1, 0, 0, 0, 0, 0, '364117'), -- Lavacaller Primalist - 364117 - -Unknown-
(@CGUID+849, 0, 0, 0, 1, 0, 0, 0, 0, 0, '42459'), -- Molten Primalist - 42459 - Dual Wield
(@CGUID+850, 0, 0, 0, 1, 0, 0, 0, 0, 0, '370034'), -- Restless Lava - 370034 - -Unknown-
(@CGUID+851, 0, 0, 0, 1, 0, 0, 0, 0, 0, '370034'), -- Restless Lava - 370034 - -Unknown-
(@CGUID+852, 0, 0, 0, 1, 0, 0, 0, 0, 0, '370034'), -- Restless Lava - 370034 - -Unknown-
(@CGUID+853, 0, 0, 0, 1, 0, 0, 0, 0, 0, '376765'), -- Unleashed Lavaburst - 376765 - -Unknown-
(@CGUID+854, 0, 0, 0, 1, 0, 0, 0, 0, 0, '42459'), -- Molten Primalist - 42459 - Dual Wield
(@CGUID+855, 0, 0, 0, 1, 0, 0, 0, 0, 0, '112080'), -- Sendrax - 112080 - Root Self
(@CGUID+856, 0, 0, 0, 1, 0, 0, 0, 0, 0, '364117 391245'), -- Lavacaller Primalist - 364117 - -Unknown-, 391245 - -Unknown-
(@CGUID+857, 0, 0, 0, 1, 0, 0, 0, 0, 0, '364026'), -- Lavacaller Primalist - 364026 - -Unknown-
(@CGUID+858, 0, 0, 0, 1, 0, 0, 0, 0, 0, '112080'), -- Sendrax - 112080 - Root Self
(@CGUID+859, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Territorial Axebeak
(@CGUID+860, 0, 0, 8, 1, 0, 0, 0, 0, 0, ''), -- Sundered Supplyhand
(@CGUID+863, 0, 0, 0, 1, 0, 0, 0, 0, 0, '369706'), -- Tarasek Elementalist - 369706 - -Unknown-
(@CGUID+864, 0, 0, 0, 1, 0, 0, 0, 0, 0, '376765'), -- Unleashed Lavaburst - 376765 - -Unknown-
(@CGUID+865, 0, 0, 0, 1, 0, 0, 0, 0, 0, '162443'), -- Sundered Mercenary - 162443 - Cosmetic - SitGround and Drink Breakable
(@CGUID+868, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Territorial Axebeak
(@CGUID+869, 0, 0, 0, 1, 0, 0, 0, 0, 0, '258247'), -- Territorial Axebeak - 258247 - -Unknown-
(@CGUID+870, 0, 0, 0, 1, 0, 0, 0, 0, 0, '258247'), -- Territorial Axebeak - 258247 - -Unknown-
(@CGUID+871, 0, 0, 0, 1, 0, 0, 0, 0, 0, '258247'), -- Territorial Axebeak - 258247 - -Unknown-
(@CGUID+872, 0, 0, 0, 1, 0, 0, 0, 0, 0, '364118'), -- Lavacaller Primalist - 364118 - -Unknown-
(@CGUID+873, 0, 0, 0, 1, 0, 0, 0, 0, 0, '42459'), -- Molten Primalist - 42459 - Dual Wield
(@CGUID+874, 0, 0, 0, 1, 0, 0, 0, 0, 0, '376804'), -- Unleashed Lavaburst - 376804 - -Unknown-
(@CGUID+876, 0, 0, 0, 1, 0, 0, 0, 0, 0, '42459'), -- Molten Primalist - 42459 - Dual Wield
(@CGUID+880, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, '376690'), -- Infused Ruby Whelpling - 376690 - -Unknown-
(@CGUID+881, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, '376690'), -- Infused Ruby Whelpling - 376690 - -Unknown-
(@CGUID+882, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, '376690'), -- Infused Ruby Whelpling - 376690 - -Unknown-
(@CGUID+883, 0, 0, 0, 1, 0, 0, 0, 0, 0, '364118'), -- Lavacaller Primalist - 364118 - -Unknown-
(@CGUID+884, 0, 0, 0, 1, 0, 0, 0, 0, 0, '364118'), -- Lavacaller Primalist - 364118 - -Unknown-
(@CGUID+885, 0, 0, 0, 1, 0, 0, 0, 0, 0, '112080'), -- Sendrax - 112080 - Root Self
(@CGUID+886, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, '376690'), -- Infused Ruby Whelpling - 376690 - -Unknown-
(@CGUID+887, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, '376690'), -- Infused Ruby Whelpling - 376690 - -Unknown-
(@CGUID+888, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, '376690'), -- Infused Ruby Whelpling - 376690 - -Unknown-
(@CGUID+891, 0, 0, 0, 1, 0, 0, 0, 0, 0, '364118'), -- Lavacaller Primalist - 364118 - -Unknown-
(@CGUID+892, 0, 0, 0, 1, 0, 0, 0, 0, 0, '364153'), -- Lavacaller Primalist - 364153 - -Unknown-
(@CGUID+893, 0, 0, 0, 1, 0, 0, 0, 0, 0, '112080'), -- Sendrax - 112080 - Root Self
(@CGUID+895, 0, 0, 0, 1, 0, 0, 0, 0, 0, '112080'), -- Sendrax - 112080 - Root Self
(@CGUID+896, 0, 0, 0, 1, 0, 0, 0, 0, 0, '369706'), -- Primal Tarasek - 369706 - -Unknown-
(@CGUID+897, 0, 0, 0, 1, 0, 0, 0, 0, 0, '42459'), -- Molten Primalist - 42459 - Dual Wield
(@CGUID+898, 0, 0, 1, 1, 0, 0, 0, 0, 0, '42459'), -- Molten Primalist - 42459 - Dual Wield
(@CGUID+899, 0, 0, 0, 1, 0, 0, 0, 0, 0, '42459 364220'), -- Molten Primalist - 42459 - Dual Wield, 364220 - -Unknown-
(@CGUID+900, 0, 0, 0, 1, 0, 0, 0, 0, 0, '364118'), -- Lavacaller Primalist - 364118 - -Unknown-
(@CGUID+903, 0, 0, 262144, 1, 0, 0, 0, 0, 0, '376704'), -- Sendrax - 376704 - -Unknown-
(@CGUID+904, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, '376690'), -- Infused Ruby Whelpling - 376690 - -Unknown-
(@CGUID+905, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, '376690'), -- Infused Ruby Whelpling - 376690 - -Unknown-
(@CGUID+906, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, '376690'), -- Infused Ruby Whelpling - 376690 - -Unknown-
(@CGUID+907, 0, 0, 0, 1, 0, 0, 0, 0, 0, '112080'), -- Sendrax - 112080 - Root Self
(@CGUID+909, 0, 0, 0, 1, 0, 0, 0, 0, 0, '391245'), -- Tarasek Elementalist - 391245 - -Unknown-
(@CGUID+910, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, '376690'), -- Infused Ruby Whelpling - 376690 - -Unknown-
(@CGUID+911, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, '376690'), -- Infused Ruby Whelpling - 376690 - -Unknown-
(@CGUID+912, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, '376690'), -- Infused Ruby Whelpling - 376690 - -Unknown-
(@CGUID+914, 0, 0, 0, 1, 0, 0, 0, 0, 0, '364220'), -- Lavacaller Primalist - 364220 - -Unknown-
(@CGUID+915, 0, 0, 0, 1, 0, 0, 0, 0, 0, '369897'), -- Lava Phoenix - 369897 - -Unknown-
(@CGUID+917, 0, 0, 0, 1, 0, 0, 0, 0, 0, '369897'), -- Lava Phoenix - 369897 - -Unknown-
-- (@CGUID+921, 0, 0, 0, 1, 0, 0, 0, 0, 0, '122729'), -- Mystic Birdhat - 122729 - Grand Expedition Yak - !!! on transport - transport template not found !!!
-- (@CGUID+922, 0, 0, 0, 1, 0, 0, 0, 0, 0, '122729'), -- Cousin Slowhands - 122729 - Grand Expedition Yak - !!! on transport - transport template not found !!!
(@CGUID+929, 0, 0, 0, 1, 0, 0, 0, 0, 0, '377717'), -- Earthshatter Elemental - 377717 - -Unknown-
(@CGUID+931, 0, 0, 0, 1, 0, 0, 0, 0, 0, '381535'), -- Raging Elemental - 381535 - -Unknown-
(@CGUID+934, 0, 0, 0, 1, 0, 0, 0, 0, 0, '374008 360001'), -- Majordomo Selistra - 374008 - -Unknown-, 360001 - -Unknown-
(@CGUID+940, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Tiny Butterfly
(@CGUID+941, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Tiny Butterfly
(@CGUID+942, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Tiny Butterfly
(@CGUID+943, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Tiny Butterfly
(@CGUID+944, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Tiny Butterfly
(@CGUID+945, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Tiny Butterfly
(@CGUID+946, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''); -- Tiny Butterfly

INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `aiAnimKit`, `movementAnimKit`, `meleeAnimKit`, `visibilityDistanceType`, `auras`) VALUES
(@CGUID+947, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Tiny Butterfly
(@CGUID+948, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Tiny Butterfly
(@CGUID+949, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Tiny Butterfly
(@CGUID+950, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Tiny Butterfly
(@CGUID+951, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Tiny Butterfly
(@CGUID+955, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Tiny Butterfly
(@CGUID+959, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Tiny Butterfly
(@CGUID+960, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Tiny Butterfly
(@CGUID+961, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Tiny Butterfly
(@CGUID+979, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Tiny Butterfly
(@CGUID+989, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Tiny Butterfly
(@CGUID+1003, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Tiny Butterfly
(@CGUID+1010, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Tiny Butterfly
(@CGUID+1011, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Tiny Butterfly
(@CGUID+1013, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Tiny Butterfly
(@CGUID+1019, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Mean Duck
(@CGUID+1020, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Mean Duck
(@CGUID+1023, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Mean Duck
(@CGUID+1024, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Mean Duck
(@CGUID+1025, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Mean Duck
(@CGUID+1028, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Mean Duck
(@CGUID+1038, 0, 0, 0, 1, 0, 0, 0, 0, 0, '258247'), -- Territorial Axebeak - 258247 - -Unknown-
(@CGUID+1039, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Territorial Axebeak
-- (@CGUID+1044, 0, 0, 0, 1, 0, 0, 0, 0, 0, '46598'), -- Murghurgl the Invader - 46598 - Ride Vehicle Hardcoded - !!! on transport - transport template not found !!!
(@CGUID+1046, 0, 0, 0, 1, 0, 0, 0, 0, 0, '258247'), -- Territorial Axebeak - 258247 - -Unknown-
(@CGUID+1047, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Territorial Axebeak
(@CGUID+1048, 0, 0, 0, 1, 0, 0, 0, 0, 0, '372653'), -- Cliffdrip Fallstriker - 372653 - -Unknown-
(@CGUID+1050, 0, 0, 0, 1, 0, 0, 0, 0, 0, '258247'), -- Territorial Axebeak - 258247 - -Unknown-
(@CGUID+1056, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Territorial Axebeak
(@CGUID+1066, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Territorial Axebeak
(@CGUID+1068, 0, 0, 0, 1, 0, 0, 0, 0, 0, '391245'), -- Cliffdrip Wavemender - 391245 - -Unknown-
(@CGUID+1069, 0, 0, 0, 1, 0, 0, 0, 0, 0, '258247'), -- Territorial Axebeak - 258247 - -Unknown-
(@CGUID+1074, 0, 0, 50331648, 1, 0, 0, 0, 0, 4, '384680'), -- Dragon Glyph - 384680 - -Unknown-
(@CGUID+1078, 0, 0, 0, 1, 0, 0, 0, 0, 0, '258247'), -- Territorial Axebeak - 258247 - -Unknown-
(@CGUID+1080, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Territorial Axebeak
(@CGUID+1083, 0, 0, 0, 1, 0, 0, 0, 0, 0, '258247'), -- Territorial Axebeak - 258247 - -Unknown-
(@CGUID+1084, 0, 0, 0, 1, 0, 0, 0, 0, 0, '258247'), -- Territorial Axebeak - 258247 - -Unknown-
(@CGUID+1086, 0, 0, 0, 1, 0, 0, 0, 0, 0, '258247'), -- Territorial Axebeak - 258247 - -Unknown-
(@CGUID+1087, 0, 0, 0, 1, 0, 0, 0, 0, 0, '258247'), -- Territorial Axebeak - 258247 - -Unknown-
(@CGUID+1088, 0, 0, 0, 0, 0, 0, 0, 0, 0, ''), -- Ru'kroszk
(@CGUID+1100, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Territorial Axebeak
(@CGUID+1102, 0, 0, 1, 1, 0, 0, 0, 0, 0, '369109'), -- Crabtender Kad'irsza - 369109 - -Unknown-
(@CGUID+1104, 0, 0, 0, 1, 0, 0, 0, 0, 0, '258247'), -- Territorial Axebeak - 258247 - -Unknown-
(@CGUID+1107, 0, 0, 0, 1, 0, 0, 0, 0, 0, '258247'), -- Territorial Axebeak - 258247 - -Unknown-
(@CGUID+1108, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Territorial Axebeak
(@CGUID+1117, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Turbulent Gust
(@CGUID+1119, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Territorial Axebeak
(@CGUID+1121, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Handhold
(@CGUID+1122, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Handhold
(@CGUID+1123, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Territorial Axebeak
(@CGUID+1124, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Territorial Axebeak
(@CGUID+1125, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Handhold
(@CGUID+1127, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Handhold
(@CGUID+1128, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Turbulent Gust
(@CGUID+1130, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Handhold
(@CGUID+1131, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Handhold
(@CGUID+1132, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Handhold
(@CGUID+1133, 0, 0, 0, 1, 0, 0, 0, 0, 0, '258247'), -- Territorial Axebeak - 258247 - -Unknown-
(@CGUID+1134, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Handhold
(@CGUID+1135, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Handhold
(@CGUID+1136, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Turbulent Gust
(@CGUID+1137, 0, 0, 0, 1, 0, 0, 0, 0, 0, '367419'), -- Primal Dropling - 367419 - -Unknown-
(@CGUID+1138, 0, 0, 0, 1, 0, 0, 0, 0, 0, '367419'), -- Primal Dropling - 367419 - -Unknown-
(@CGUID+1139, 0, 0, 0, 1, 0, 0, 0, 0, 0, '367419'), -- Primal Dropling - 367419 - -Unknown-
-- (@CGUID+1142, 0, 0, 0, 1, 0, 0, 0, 0, 0, '46598'), -- King Drippy - 46598 - Ride Vehicle Hardcoded - !!! on transport - transport template not found !!!
(@CGUID+1144, 0, 0, 50331648, 1, 0, 0, 0, 0, 4, ''), -- Ruby Skyguard
(@CGUID+1148, 0, 0, 50331648, 1, 0, 0, 0, 0, 4, ''), -- Ruby Skyguard
(@CGUID+1149, 0, 0, 50331648, 1, 0, 0, 0, 0, 4, ''), -- Ruby Skyguard
(@CGUID+1151, 0, 0, 50331648, 1, 0, 0, 0, 0, 4, ''), -- Ruby Skyguard
(@CGUID+1152, 0, 0, 50331648, 1, 0, 0, 0, 0, 4, ''), -- Ruby Skyguard
(@CGUID+1153, 0, 0, 50331648, 1, 0, 0, 0, 0, 4, ''), -- Ruby Skyguard
(@CGUID+1154, 0, 0, 50331648, 1, 0, 0, 0, 0, 4, ''), -- Ruby Skyguard
(@CGUID+1155, 0, 0, 50331648, 1, 0, 0, 0, 0, 4, ''), -- Ruby Skyguard
(@CGUID+1156, 0, 0, 50331648, 1, 0, 0, 0, 0, 4, ''), -- Ruby Skyguard
(@CGUID+1157, 0, 0, 50331648, 1, 0, 0, 0, 0, 3, ''), -- Ruby Skyguard
(@CGUID+1158, 0, 0, 50331648, 1, 0, 0, 0, 0, 4, ''), -- Ruby Skyguard
(@CGUID+1159, 0, 0, 0, 1, 0, 0, 0, 0, 0, '375039 375042'), -- Ruby Tender - 375039 - -Unknown-, 375042 - -Unknown-
(@CGUID+1160, 0, 0, 0, 1, 0, 0, 0, 0, 0, '375039 375042'), -- Ruby Tender - 375039 - -Unknown-, 375042 - -Unknown-
(@CGUID+1161, 0, 0, 0, 1, 0, 0, 0, 0, 0, '375039 375042'), -- Ruby Tender - 375039 - -Unknown-, 375042 - -Unknown-
(@CGUID+1162, 0, 0, 50331648, 1, 0, 0, 0, 0, 4, ''), -- Ruby Skyguard
(@CGUID+1163, 0, 0, 50331648, 1, 0, 0, 0, 0, 4, ''), -- Ruby Skyguard
-- (@CGUID+1164, 0, 0, 0, 1, 0, 0, 0, 0, 0, '122729 123236'), -- Mystic Birdhat - 122729 - Grand Expedition Yak, 123236 - Grummle Booth A - !!! on transport - transport template not found !!!
-- (@CGUID+1165, 0, 0, 0, 1, 0, 0, 0, 0, 0, '122729 123240'), -- Cousin Slowhands - 122729 - Grand Expedition Yak, 123240 - Grummle Booth B - !!! on transport - transport template not found !!!
(@CGUID+1167, 0, 0, 50331648, 1, 0, 0, 0, 0, 4, '384674'), -- Dragon Glyph - 384674 - -Unknown-
(@CGUID+1169, 0, 0, 1, 1, 0, 0, 0, 0, 0, ''), -- Veritistrasz
(@CGUID+1170, 0, 0, 50331648, 1, 0, 0, 0, 0, 4, ''), -- Ruby Skyguard
(@CGUID+1172, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Ruby Scaleguard
(@CGUID+1174, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Ruby Scaleguard
(@CGUID+1175, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Ruby Scaleguard
(@CGUID+1176, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Ruby Scaleguard
(@CGUID+1178, 0, 0, 0, 1, 0, 0, 0, 0, 0, '373400 360001'), -- Kandrostrasz - 373400 - -Unknown-, 360001 - -Unknown-
(@CGUID+1180, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, '382828'), -- Lillistrazsa - 382828 - -Unknown-
(@CGUID+1181, 0, 0, 0, 1, 0, 0, 0, 0, 0, '364324'), -- Kskeiton - 364324 - -Unknown-
(@CGUID+1183, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Ruby Keeper
(@CGUID+1185, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Ruby Shrineguard
(@CGUID+1186, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Sprightly Butterfly
(@CGUID+1187, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Sprightly Butterfly
(@CGUID+1192, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Sprightly Butterfly
(@CGUID+1193, 0, 0, 1, 1, 0, 0, 0, 0, 0, ''), -- Clokkistrasz
(@CGUID+1194, 0, 0, 1, 1, 0, 0, 0, 0, 0, '377397'), -- Zhustostrasza - 377397 - -Unknown-
(@CGUID+1195, 0, 0, 0, 257, 0, 0, 0, 0, 0, '375277'), -- Ruby Shrineguard - 375277 - -Unknown-
(@CGUID+1196, 0, 0, 0, 1, 0, 0, 0, 0, 0, '382158'), -- Sapphire Tender - 382158 - -Unknown-
(@CGUID+1197, 0, 0, 1, 1, 0, 0, 0, 0, 0, ''), -- Peaceful Duck
(@CGUID+1199, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Ruby Whelpling
(@CGUID+1202, 0, 0, 0, 1, 0, 0, 0, 0, 0, '381919'), -- Kahtzar - 381919 - -Unknown-
(@CGUID+1204, 0, 0, 0, 1, 0, 24419, 0, 0, 0, ''), -- Trellain
(@CGUID+1205, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Nurse Sentry
(@CGUID+1206, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Ruby Shrineguard
(@CGUID+1208, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Ruby Shrineguard
(@CGUID+1209, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Ruby Shrineguard
(@CGUID+1217, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Ruby Swarmer
(@CGUID+1218, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Ruby Swarmer
(@CGUID+1221, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Nurse Sentry
(@CGUID+1222, 0, 0, 0, 1, 0, 0, 0, 0, 0, '120703'), -- Ruby Dozer - 120703 - Cosmetic - Sleep Zzz Breakable
(@CGUID+1223, 0, 0, 0, 1, 0, 0, 0, 0, 0, '120703'), -- Boots - 120703 - Cosmetic - Sleep Zzz Breakable
(@CGUID+1224, 0, 0, 0, 1, 0, 0, 0, 0, 0, '120703'), -- Ruby Dozer - 120703 - Cosmetic - Sleep Zzz Breakable
(@CGUID+1225, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Ruby Shrineguard
(@CGUID+1226, 0, 0, 3, 1, 0, 0, 0, 0, 0, ''), -- Ruby Percher
(@CGUID+1227, 0, 0, 1, 1, 0, 0, 0, 0, 0, ''), -- Ruby Percher
(@CGUID+1228, 0, 0, 1, 1, 0, 0, 0, 0, 0, ''), -- Ruby Percher
(@CGUID+1229, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Ruby Keeper
(@CGUID+1230, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Ruby Swarmer
(@CGUID+1231, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Ruby Shrineguard
(@CGUID+1235, 0, 0, 0, 1, 0, 0, 0, 0, 0, '376364 389776'), -- Akora - 376364 - -Unknown-, 389776 - -Unknown-
(@CGUID+1236, 0, 0, 0, 1, 0, 0, 0, 0, 0, '374830'), -- Vaeros - 374830 - -Unknown-
(@CGUID+1238, 0, 0, 0, 1, 0, 0, 0, 0, 0, '382158'), -- Bronze Tender - 382158 - -Unknown-
(@CGUID+1239, 0, 0, 1, 1, 0, 0, 0, 0, 0, ''), -- Tionistrasz
(@CGUID+1240, 0, 0, 0, 1, 0, 0, 0, 0, 0, '382158'), -- Ruby Tender - 382158 - -Unknown-
(@CGUID+1242, 0, 0, 0, 1, 0, 0, 0, 0, 0, '382158'), -- Ruby Tender - 382158 - -Unknown-
(@CGUID+1245, 0, 0, 1, 1, 0, 0, 0, 0, 0, ''), -- Zoristrasz
(@CGUID+1246, 0, 0, 0, 1, 0, 0, 0, 0, 0, '382158'), -- Ruby Tender - 382158 - -Unknown-
(@CGUID+1247, 0, 0, 1, 257, 0, 0, 0, 0, 0, ''), -- Ruby Groundskeeper
(@CGUID+1249, 0, 0, 0, 1, 0, 0, 0, 0, 0, '376365 389802'), -- Keshki - 376365 - -Unknown-, 389802 - -Unknown-
(@CGUID+1253, 0, 0, 0, 1, 0, 0, 0, 0, 0, '389833'), -- Lasztak - 389833 - -Unknown-
(@CGUID+1255, 0, 0, 0, 1, 0, 0, 0, 0, 0, '389771'), -- Dazakros - 389771 - -Unknown-
(@CGUID+1256, 0, 0, 1, 1, 0, 0, 0, 0, 0, '377397'), -- Xolleth - 377397 - -Unknown-
(@CGUID+1257, 0, 0, 0, 1, 0, 0, 0, 0, 0, '382158'), -- Azure Tender - 382158 - -Unknown-
(@CGUID+1258, 0, 0, 1, 1, 0, 0, 0, 0, 0, ''), -- Faramin
(@CGUID+1261, 0, 0, 0, 1, 0, 0, 0, 0, 0, '382158'), -- Ruby Tender - 382158 - -Unknown-
(@CGUID+1262, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Ruby Shrineguard
(@CGUID+1263, 0, 0, 0, 1, 0, 0, 0, 0, 0, '358422'), -- Ruby Swarmer - 358422 - -Unknown-
(@CGUID+1264, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Ruby Shrineguard
(@CGUID+1265, 0, 0, 0, 1, 0, 0, 0, 0, 0, '358422'), -- Ruby Swarmer - 358422 - -Unknown-
(@CGUID+1266, 0, 0, 0, 1, 0, 0, 0, 0, 0, '120703'), -- Ruby Dozer - 120703 - Cosmetic - Sleep Zzz Breakable
(@CGUID+1267, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Ruby Shrineguard
(@CGUID+1268, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Ruby Shrineguard
(@CGUID+1269, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Ruby Shrineguard
(@CGUID+1270, 0, 0, 0, 1, 0, 0, 0, 0, 0, '358422'), -- Ruby Swarmer - 358422 - -Unknown-
(@CGUID+1271, 0, 0, 0, 1, 0, 0, 0, 0, 0, '120703'), -- Ruby Dozer - 120703 - Cosmetic - Sleep Zzz Breakable
(@CGUID+1272, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- Nurse Sentry
(@CGUID+1274, 0, 0, 50331648, 1, 0, 0, 0, 0, 3, ''), -- Ruby Skyguard
(@CGUID+1275, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Akxall
(@CGUID+1277, 0, 0, 50331648, 1, 0, 0, 0, 0, 3, ''), -- Ruby Skyguard
(@CGUID+1279, 0, 0, 0, 1, 0, 0, 0, 0, 0, '384483'), -- Majordomo Selistra - 384483 - -Unknown-
(@CGUID+1280, 0, 0, 50331648, 1, 0, 0, 0, 0, 3, ''), -- Ruby Skyguard
(@CGUID+1281, 0, 0, 0, 1, 0, 0, 0, 0, 0, '385839'), -- Captain Exposition - 385839 - -Unknown-
(@CGUID+1283, 0, 0, 50331648, 1, 0, 0, 0, 0, 3, ''), -- Ruby Skyguard
(@CGUID+1284, 0, 0, 0, 1, 0, 0, 0, 0, 0, '337501'), -- Lasztak - 337501 - -Unknown-
(@CGUID+1285, 0, 0, 50331648, 1, 0, 0, 0, 0, 3, ''), -- Ruby Skyguard
(@CGUID+1286, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Elemental Target [DNT]
(@CGUID+1287, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Elemental Target [DNT]
(@CGUID+1288, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Elemental Target [DNT]
(@CGUID+1289, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Elemental Target [DNT]
-- (@CGUID+1292, 0, 0, 0, 1, 0, 0, 0, 0, 0, '46598'), -- Ban-Lu - 46598 - Ride Vehicle Hardcoded - !!! on transport - transport template not found !!!
(@CGUID+1296, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Sprightly Butterfly
-- (@CGUID+1297, 0, 0, 0, 1, 0, 0, 0, 0, 0, '46598'), -- Ban-Lu - 46598 - Ride Vehicle Hardcoded - !!! on transport - transport template not found !!!
(@CGUID+1299, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Intrusive Pupstinger
(@CGUID+1303, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Intrusive Pupstinger
(@CGUID+1305, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Intrusive Pupstinger
(@CGUID+1306, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Intrusive Pupstinger
(@CGUID+1310, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Intrusive Pupstinger
(@CGUID+1311, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Intrusive Pupstinger
(@CGUID+1312, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Intrusive Pupstinger
(@CGUID+1314, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Intrusive Pupstinger
(@CGUID+1316, 0, 0, 0, 1, 0, 0, 0, 0, 0, '391958'), -- Relentless Gust - 391958 - -Unknown-
(@CGUID+1318, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Lifeshrine Door
(@CGUID+1319, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Intrusive Pupstinger
(@CGUID+1320, 0, 0, 0, 1, 0, 0, 0, 0, 0, '391958'), -- Relentless Gust - 391958 - -Unknown-
(@CGUID+1321, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Intrusive Pupstinger
(@CGUID+1323, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- Intrusive Pupstinger
(@CGUID+1328, 0, 0, 0, 1, 0, 0, 0, 0, 0, '373397 360001'), -- Danastra - 373397 - -Unknown-, 360001 - -Unknown-
-- (@CGUID+1329, 0, 0, 0, 1, 0, 0, 0, 0, 0, '46598'), -- Ban-Lu - 46598 - Ride Vehicle Hardcoded - !!! on transport - transport template not found !!!
(@CGUID+1330, 0, 0, 0, 1, 0, 0, 0, 0, 0, '391958'), -- Relentless Gust - 391958 - -Unknown-
(@CGUID+1331, 0, 0, 0, 1, 0, 0, 0, 0, 0, '376364'), -- Akora - 376364 - -Unknown-
(@CGUID+1332, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''); -- Intrusive Pupstinger

DELETE FROM `gameobject` WHERE `guid` BETWEEN @OGUID+0 AND @OGUID+285;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnDifficulties`, `PhaseId`, `PhaseGroup`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `VerifiedBuild`) VALUES
(@OGUID+0, 380940, 2444, 13644, 13704, '0', '0', 0, 3516.850830078125, -639.03643798828125, 82.07781982421875, 2.679995536804199218, 0, 0, 0.973484039306640625, 0.228754952549934387, 7200, 255, 1, 45505), -- Broken Head (Area: -Unknown- - Difficulty: 0)
(@OGUID+1, 382032, 2444, 13644, 13704, '0', '0', 0, 3624.6953125, -491.625, 52.565093994140625, 5.249528408050537109, 0, 0, -0.4941253662109375, 0.869390666484832763, 7200, 255, 1, 45505), -- Flowering Inferno Pod (Area: -Unknown- - Difficulty: 0)
(@OGUID+2, 382033, 2444, 13644, 13704, '0', '0', 0, 3790.467041015625, -527.8975830078125, 44.22656631469726562, 0, 0, 0, 0, 1, 7200, 255, 1, 45505), -- Djaradin Supply Jar (Area: -Unknown- - Difficulty: 0)
(@OGUID+3, 382033, 2444, 13644, 13704, '0', '0', 0, 3527.94873046875, -645.78643798828125, 82.16121673583984375, 0, 0, 0, 0, 1, 7200, 255, 1, 45505), -- Djaradin Supply Jar (Area: -Unknown- - Difficulty: 0)
(@OGUID+4, 382032, 2444, 13644, 13704, '0', '0', 0, 3539.81591796875, -311.618072509765625, 69.223724365234375, 5.249528408050537109, 0, 0, -0.4941253662109375, 0.869390666484832763, 7200, 255, 1, 45505), -- Flowering Inferno Pod (Area: -Unknown- - Difficulty: 0)
(@OGUID+5, 382032, 2444, 13644, 13704, '0', '0', 0, 3725.751708984375, -620.35418701171875, 36.46965408325195312, 5.249528408050537109, 0, 0, -0.4941253662109375, 0.869390666484832763, 7200, 255, 1, 45505), -- Flowering Inferno Pod (Area: -Unknown- - Difficulty: 0)
(@OGUID+6, 376626, 2444, 13644, 13704, '0', '0', 0, 3802.30810546875, -485.508697509765625, 45.09227371215820312, 5.085353851318359375, 0, 0, -0.56374740600585937, 0.825947284698486328, 7200, 255, 1, 45505), -- Djaradin Armaments (Area: -Unknown- - Difficulty: 0)
(@OGUID+7, 376626, 2444, 13644, 13704, '0', '0', 0, 3730.984375, -434.189239501953125, 57.16550827026367187, 0.920271754264831542, 0, 0, 0.444069862365722656, 0.895992159843444824, 7200, 255, 1, 45505), -- Djaradin Armaments (Area: -Unknown- - Difficulty: 0)
(@OGUID+8, 382032, 2444, 13644, 13704, '0', '0', 0, 3557.928955078125, -423.732635498046875, 72.1175079345703125, 5.249528408050537109, 0, 0, -0.4941253662109375, 0.869390666484832763, 7200, 255, 1, 45505), -- Flowering Inferno Pod (Area: -Unknown- - Difficulty: 0)
(@OGUID+9, 376580, 2444, 13644, 13704, '0', '0', 0, 3529.2666015625, -384.37152099609375, 70.32222747802734375, 2.486956596374511718, 0, 0, 0.946907997131347656, 0.321504652500152587, 7200, 255, 1, 45505), -- Djaradin Cache (Area: -Unknown- - Difficulty: 0)
(@OGUID+10, 382032, 2444, 13644, 13704, '0', '0', 0, 3714.8125, -521.92364501953125, 44.83993148803710937, 5.249528408050537109, 0, 0, -0.4941253662109375, 0.869390666484832763, 7200, 255, 1, 45505), -- Flowering Inferno Pod (Area: -Unknown- - Difficulty: 0)
(@OGUID+11, 380918, 2444, 13644, 13704, '0', '0', 0, 3165.6806640625, -455.836822509765625, 74.26529693603515625, 0.493266791105270385, 0, 0, 0.244140625, 0.969739854335784912, 7200, 255, 1, 45505), -- Broken Ornamented Statue (Area: -Unknown- - Difficulty: 0)
(@OGUID+12, 377314, 2444, 13644, 13704, '0', '0', 0, 3708.653564453125, -615.04339599609375, 36.96181488037109375, 1.009213685989379882, 0, 0, 0.483463287353515625, 0.875364661216735839, 7200, 255, 1, 45505), -- Dragon Parts [DNT] (Area: -Unknown- - Difficulty: 0)
(@OGUID+13, 377314, 2444, 13644, 13704, '0', '0', 0, 3671.092041015625, -658.55902099609375, 37.45673751831054687, 5.903156280517578125, 0, 0, -0.188873291015625, 0.982001483440399169, 7200, 255, 1, 45505), -- Dragon Parts [DNT] (Area: -Unknown- - Difficulty: 0)
(@OGUID+14, 382032, 2444, 13644, 13704, '0', '0', 0, 3594.362060546875, -527.11285400390625, 55.61263656616210937, 3.910686254501342773, 0, 0, -0.92696857452392578, 0.375138968229293823, 7200, 255, 1, 45505), -- Flowering Inferno Pod (Area: -Unknown- - Difficulty: 0)
(@OGUID+15, 376626, 2444, 13644, 13704, '0', '0', 0, 3652.217041015625, -605.857666015625, 49.77290725708007812, 3.850975751876831054, 0, 0, -0.93775367736816406, 0.347301095724105834, 7200, 255, 1, 45505), -- Djaradin Armaments (Area: -Unknown- - Difficulty: 0)
(@OGUID+16, 376626, 2444, 13644, 13704, '0', '0', 0, 3590.35498046875, -340.057281494140625, 71.66564178466796875, 2.569613933563232421, 0, 0, 0.959383010864257812, 0.282106786966323852, 7200, 255, 1, 45505), -- Djaradin Armaments (Area: -Unknown- - Difficulty: 0)
-- (@OGUID+17, 375073, 2444, 13644, 13704, '0', '0', 0, 0, 0, 0, 5.031595230102539062, 0, 0, -0.58574199676513671, 0.810497581958770751, 7200, 255, 1, 45505), -- 0 (Area: -Unknown- - Difficulty: 0) - !!! transport !!!
(@OGUID+18, 379205, 2444, 13644, 13704, '0', '0', 0, 3431.122314453125, -567.1944580078125, 70.9262847900390625, 6.099926471710205078, 0, 0, -0.09150123596191406, 0.995804965496063232, 7200, 255, 1, 45505), -- Anvil (Area: -Unknown- - Difficulty: 0)
(@OGUID+19, 379206, 2444, 13644, 13704, '0', '0', 0, 3415.82470703125, -550.9444580078125, 73.2314605712890625, 2.530723094940185546, 0, 0, 0.953716278076171875, 0.300707906484603881, 7200, 255, 1, 45505), -- Forge (Area: -Unknown- - Difficulty: 0)
(@OGUID+20, 381102, 2444, 13644, 13704, '0', '0', 0, 3763.616455078125, -652.16143798828125, 36.37935256958007812, 0, 0, 0, 0, 1, 7200, 255, 1, 45505), -- Tyrivite Deposit (Area: -Unknown- - Difficulty: 0)
(@OGUID+21, 377314, 2444, 13644, 13704, '0', '0', 0, 3874.132080078125, -527.09552001953125, 91.20778656005859375, 1.009213685989379882, 0, 0, 0.483463287353515625, 0.875364661216735839, 7200, 255, 1, 45505), -- Dragon Parts [DNT] (Area: -Unknown- - Difficulty: 0)
(@OGUID+22, 382033, 2444, 13644, 13704, '0', '0', 0, 3893.771728515625, -594.34375, 80.21234893798828125, 0, 0, 0, 0, 1, 7200, 255, 1, 45505), -- Djaradin Supply Jar (Area: -Unknown- - Difficulty: 0)
(@OGUID+23, 380579, 2444, 13644, 13704, '0', '0', 0, 4002.05126953125, -481.489593505859375, 81.00200653076171875, 1.924501895904541015, -0.62145566940307617, -0.30082321166992187, 0.713789939880371093, 0.117482639849185943, 7200, 255, 1, 45505), -- Spare Djaradin Tools (Area: -Unknown- - Difficulty: 0)
(@OGUID+24, 376580, 2444, 13644, 13704, '0', '0', 0, 3995.48779296875, -500.177093505859375, 82.17014312744140625, 1.797299623489379882, 0, 0, 0.782486915588378906, 0.622667014598846435, 7200, 255, 1, 45505), -- Djaradin Cache (Area: -Unknown- - Difficulty: 0)
-- (@OGUID+25, 375041, 2444, 13644, 13704, '0', '0', 0, 0, 0, 0, 5.547320842742919921, 0, 0, -0.35968685150146484, 0.933073103427886962, 7200, 255, 1, 45505), -- 0 (Area: -Unknown- - Difficulty: 0) - !!! transport !!!
(@OGUID+26, 382032, 2444, 13644, 13704, '0', '0', 0, 3362.178955078125, -234.803817749023437, 33.86033248901367187, 5.249528408050537109, 0, 0, -0.4941253662109375, 0.869390666484832763, 7200, 255, 1, 45505), -- Flowering Inferno Pod (Area: -Unknown- - Difficulty: 0)
(@OGUID+27, 382032, 2444, 13644, 13704, '0', '0', 0, 3415.130126953125, -163.5, 25.37510490417480468, 5.249528408050537109, 0, 0, -0.4941253662109375, 0.869390666484832763, 7200, 255, 1, 45505), -- Flowering Inferno Pod (Area: -Unknown- - Difficulty: 0)
(@OGUID+28, 381674, 2444, 13644, 13704, '0', '0', 0, 3454.591064453125, -109.784721374511718, 29.95908355712890625, 4.925380706787109375, 0, 0, -0.62793922424316406, 0.77826237678527832, 7200, 255, 1, 45505), -- Mature White Bell (Area: -Unknown- - Difficulty: 0)
(@OGUID+29, 382032, 2444, 13644, 13704, '0', '0', 0, 3401.22998046875, -125.489593505859375, 14.77068233489990234, 5.249528408050537109, 0, 0, -0.4941253662109375, 0.869390666484832763, 7200, 255, 1, 45505), -- Flowering Inferno Pod (Area: -Unknown- - Difficulty: 0)
(@OGUID+30, 382032, 2444, 13644, 13704, '0', '0', 0, 3404.486083984375, -68.454864501953125, 7.604725360870361328, 3.367955923080444335, 0, 0, -0.99360179901123046, 0.112940043210983276, 7200, 255, 1, 45505), -- Flowering Inferno Pod (Area: -Unknown- - Difficulty: 0)
(@OGUID+31, 382030, 2444, 13644, 0, '0', '0', 0, 3249.15966796875, -201.017364501953125, 4.221700191497802734, 6.129708766937255859, 0, 0, -0.07666301727294921, 0.997057080268859863, 7200, 255, 1, 45505), -- Nectar Filled Panthis (Area: 0 - Difficulty: 0)
(@OGUID+32, 381209, 2444, 13644, 0, '0', '0', 0, 3248.288330078125, -196.399307250976562, 4.254945278167724609, 2.062747955322265625, 0, 0, 0.858005523681640625, 0.513640463352203369, 7200, 255, 1, 45505), -- Hochenblume (Area: 0 - Difficulty: 0)
(@OGUID+33, 381209, 2444, 13644, 14106, '0', '0', 0, 3680.684814453125, -62.6006965637207031, 70.32111358642578125, 3.488220453262329101, 0, 0, -0.98501873016357421, 0.172447457909584045, 7200, 255, 1, 45505), -- Hochenblume (Area: -Unknown- - Difficulty: 0)
(@OGUID+34, 382031, 2444, 13644, 14106, '0', '0', 0, 3348.046875, 195.55035400390625, 13.37973308563232421, 4.925380706787109375, 0, 0, -0.62793922424316406, 0.77826237678527832, 7200, 255, 1, 45505), -- Oily Dropcap (Area: -Unknown- - Difficulty: 0)
(@OGUID+35, 382031, 2444, 13644, 14106, '0', '0', 0, 3375.502685546875, 230.0694427490234375, 12.15247058868408203, 4.925380706787109375, 0, 0, -0.62793922424316406, 0.77826237678527832, 7200, 255, 1, 45505), -- Oily Dropcap (Area: -Unknown- - Difficulty: 0)
(@OGUID+36, 379248, 2444, 13644, 14106, '0', '0', 0, 3383.79345703125, 256.166656494140625, 66.67520904541015625, 1.76278841495513916, 0, 0, 0.771626472473144531, 0.636075913906097412, 7200, 255, 1, 45505), -- Draconium Deposit (Area: -Unknown- - Difficulty: 0)
(@OGUID+37, 377209, 2444, 13644, 14106, '0', '0', 0, 3387.780517578125, 271.99652099609375, 19.34069252014160156, 0, 0, 0, 0, 1, 7200, 255, 1, 45505), -- Water Basin [DNT] (Area: -Unknown- - Difficulty: 0)
(@OGUID+38, 377210, 2444, 13644, 0, '0', '0', 0, 3382.37939453125, 273.407989501953125, 19.34069252014160156, 0, 0, 0, 0, 1, 7200, 255, 1, 45505), -- Filled Water Bucket [DNT] (Area: 0 - Difficulty: 0)
(@OGUID+39, 375241, 2444, 13644, 0, '0', '0', 0, 3567.375, 326, 4.166722774505615234, 3.498488664627075195, 0, 0, -0.98412036895751953, 0.17750231921672821, 7200, 255, 1, 45505), -- Bubble Poppy (Area: 0 - Difficulty: 0)
(@OGUID+40, 376634, 2444, 13644, 0, '0', '0', 0, 3743.624267578125, 643.95831298828125, 68.13543701171875, 1.380354642868041992, 0, 0, 0.636673927307128906, 0.771133124828338623, 7200, 255, 1, 45505), -- Rock Wall (Area: 0 - Difficulty: 0)
(@OGUID+41, 381674, 2444, 13644, 14107, '0', '0', 0, 3809.475830078125, 370.015625, 198.3910675048828125, 5.87701416015625, 0, 0, -0.20169258117675781, 0.979448914527893066, 7200, 255, 1, 45505), -- Mature White Bell (Area: -Unknown- - Difficulty: 0)
(@OGUID+42, 382032, 2444, 13644, 0, '0', '0', 0, 4018.470458984375, 148.4635467529296875, 38.21844100952148437, 5.249528408050537109, 0, 0, -0.4941253662109375, 0.869390666484832763, 7200, 255, 1, 45505), -- Flowering Inferno Pod (Area: 0 - Difficulty: 0)
(@OGUID+43, 377499, 2444, 13644, 0, '0', '0', 0, 4059.22314453125, 246.076385498046875, 56.10640335083007812, 2.57962346076965332, -0.18175983428955078, 0.179918289184570312, 0.920537948608398437, 0.295300990343093872, 7200, 255, 1, 45505), -- On the Origin of Draconic Species (Area: 0 - Difficulty: 0)
(@OGUID+44, 382032, 2444, 13644, 13709, '0', '0', 0, 4105.14599609375, 222.3125, 38.64167022705078125, 5.249528408050537109, 0, 0, -0.4941253662109375, 0.869390666484832763, 7200, 255, 1, 45505), -- Flowering Inferno Pod (Area: -Unknown- - Difficulty: 0)
(@OGUID+45, 376679, 2444, 13644, 13709, '0', '0', 0, 4028.014892578125, 109.4965286254882812, 46.4259796142578125, 6.269275188446044921, 0.005780220031738281, 0.073157310485839843, -0.00732326507568359, 0.997276782989501953, 7200, 255, 1, 45505), -- Ritual Circle (Area: -Unknown- - Difficulty: 0)
(@OGUID+46, 381196, 2444, 13644, 13709, '0', '0', 0, 4006.5869140625, 424.114593505859375, 64.2541961669921875, 2.14643716812133789, 0, 0, 0.878741264343261718, 0.47729840874671936, 7200, 255, 1, 45505), -- Titan-Touched Writhebark (Area: -Unknown- - Difficulty: 0)
(@OGUID+47, 382032, 2444, 13644, 13709, '0', '0', 0, 4072.0625, 90.6180572509765625, 37.691925048828125, 5.249528408050537109, 0, 0, -0.4941253662109375, 0.869390666484832763, 7200, 255, 1, 45505), -- Flowering Inferno Pod (Area: -Unknown- - Difficulty: 0)
(@OGUID+48, 381103, 2444, 13644, 13709, '0', '0', 0, 3995.229248046875, 442.696197509765625, 61.14264678955078125, 3.872232437133789062, 0, 0, -0.93400955200195312, 0.35724806785583496, 7200, 255, 1, 45505), -- Tyrivite Deposit (Area: -Unknown- - Difficulty: 0)
(@OGUID+49, 242514, 2444, 13644, 13709, '0', '0', 0, 4183.94970703125, 393.171875, 59.7875518798828125, 0, 0, 0, 0, 1, 7200, 255, 1, 45505), -- Books on Fire (Area: -Unknown- - Difficulty: 0)
(@OGUID+50, 242514, 2444, 13644, 13709, '0', '0', 0, 4106.19189453125, 71.703125, 45.41503524780273437, 6.075948715209960937, -0.06960916519165039, -0.14682674407958984, -0.11040401458740234, 0.98051387071609497, 7200, 255, 1, 45505), -- Books on Fire (Area: -Unknown- - Difficulty: 0)
(@OGUID+51, 382032, 2444, 13644, 13709, '0', '0', 0, 4139.24658203125, 85.3836822509765625, 42.14894485473632812, 5.249528408050537109, 0, 0, -0.4941253662109375, 0.869390666484832763, 7200, 255, 1, 45505), -- Flowering Inferno Pod (Area: -Unknown- - Difficulty: 0)
(@OGUID+52, 376941, 2444, 13644, 13709, '0', '0', 0, 4105.69775390625, 101.5052108764648437, 42.04103851318359375, 0.035713560879230499, -0.04755020141601562, -0.05471515655517578, 0.015189170837402343, 0.997253477573394775, 7200, 255, 0, 45505), -- The Titanic Comedy (Area: -Unknown- - Difficulty: 0)
(@OGUID+53, 376942, 2444, 13644, 13709, '0', '0', 0, 4180.89306640625, 398.2882080078125, 61.62721633911132812, 5.376305103302001953, 0, 0, -0.43806076049804687, 0.898945391178131103, 7200, 255, 0, 45505), -- The Scales of Wrath (Area: -Unknown- - Difficulty: 0)
(@OGUID+54, 376945, 2444, 13644, 13709, '0', '0', 0, 4104.9833984375, 55.36458206176757812, 47.80869293212890625, 0.717314183712005615, -0.13497543334960937, -0.13311576843261718, 0.331861495971679687, 0.924083173274993896, 7200, 255, 0, 45505), -- The Red and the Black Flights (Area: -Unknown- - Difficulty: 0)
(@OGUID+55, 380833, 2444, 13644, 13709, '0', '0', 0, 4217.8515625, 109.5486068725585937, 54.19260025024414062, 6.168157577514648437, 0.052248954772949218, -0.00300788879394531, -0.057403564453125, 0.996978342533111572, 7200, 255, 1, 45505), -- Primal Fire Conduit (Area: -Unknown- - Difficulty: 0)
(@OGUID+56, 377502, 2444, 13644, 13709, '0', '0', 0, 4213.57666015625, 116.1076431274414062, 54.73994064331054687, 2.548995256423950195, 0, 0, 0.956423759460449218, 0.291982173919677734, 7200, 255, 1, 45505), -- Primal Fire Conduit (Area: -Unknown- - Difficulty: 0)
(@OGUID+57, 376199, 2444, 13644, 13709, '0', '0', 0, 4221.4443359375, 114.876739501953125, 55.09367752075195312, 1.239801883697509765, 0, 0, 0.580954551696777343, 0.81393599510192871, 7200, 255, 1, 45505), -- Hatched Dragon Egg (Area: -Unknown- - Difficulty: 0)
(@OGUID+58, 377502, 2444, 13644, 13709, '0', '0', 0, 4225.1416015625, 106.7968826293945312, 54.17749786376953125, 0.766974985599517822, 0, 0, 0.374156951904296875, 0.927365362644195556, 7200, 255, 1, 45505), -- Primal Fire Conduit (Area: -Unknown- - Difficulty: 0)
(@OGUID+59, 376199, 2444, 13644, 13709, '0', '0', 0, 4221.4599609375, 113.3715286254882812, 55.61575698852539062, 1.841972827911376953, 0, 0, 0.796198844909667968, 0.605035066604614257, 7200, 255, 1, 45505), -- Hatched Dragon Egg (Area: -Unknown- - Difficulty: 0)
(@OGUID+60, 376199, 2444, 13644, 13709, '0', '0', 0, 4223.4990234375, 111.5850677490234375, 55.110870361328125, 4.503618240356445312, 0, 0, -0.77693557739257812, 0.629580140113830566, 7200, 255, 1, 45505), -- Hatched Dragon Egg (Area: -Unknown- - Difficulty: 0)
(@OGUID+61, 242514, 2444, 13644, 13709, '0', '0', 0, 4268.2333984375, 155.435760498046875, 61.07130813598632812, 0, 0, 0, 0, 1, 7200, 255, 1, 45505), -- Books on Fire (Area: -Unknown- - Difficulty: 0)
(@OGUID+62, 381207, 2444, 13644, 13709, '0', '0', 0, 4089.619873046875, -36.0208320617675781, 108.8417205810546875, 2.287114858627319335, 0, 0, 0.910113334655761718, 0.414359450340270996, 7200, 255, 1, 45505), -- Saxifrage (Area: -Unknown- - Difficulty: 0)
(@OGUID+63, 242514, 2444, 13644, 13709, '0', '0', 0, 4288.6005859375, 145.5572967529296875, 62.34528350830078125, 1.032573342323303222, 0, 0, 0.493654251098632812, 0.869658231735229492, 7200, 255, 1, 45505), -- Books on Fire (Area: -Unknown- - Difficulty: 0)
(@OGUID+64, 376646, 2444, 13644, 13710, '0', '0', 0, 3153.287353515625, 480.828125, 207.17138671875, 4.380497455596923828, 0, 0, -0.81419658660888671, 0.58058929443359375, 7200, 255, 1, 45505), -- Rock Wall (Area: -Unknown- - Difficulty: 0)
(@OGUID+65, 381103, 2444, 13644, 13710, '0', '0', 0, 3157.795166015625, 168.8368072509765625, 270.738555908203125, 4.328757286071777343, 0, 0, -0.82894229888916015, 0.559334099292755126, 7200, 255, 1, 45505), -- Tyrivite Deposit (Area: -Unknown- - Difficulty: 0)
(@OGUID+66, 381674, 2444, 13644, 13710, '0', '0', 0, 3232.798583984375, 194.501739501953125, 72.275543212890625, 4.925380706787109375, 0, 0, -0.62793922424316406, 0.77826237678527832, 7200, 255, 1, 45505), -- Mature White Bell (Area: -Unknown- - Difficulty: 0)
(@OGUID+67, 377212, 2444, 13644, 13710, '0', '0', 0, 3282.772705078125, 361.711822509765625, -1.00200355052947998, 1.775107860565185546, 0, 0, 0.775529861450195312, 0.631310880184173583, 7200, 255, 1, 45505), -- Tuskarr Mug (Area: -Unknown- - Difficulty: 0)
(@OGUID+68, 376562, 2444, 13644, 13710, '0', '0', 0, 3282.21875, 362.2882080078125, -0.96056938171386718, 3.10433053970336914, 0, 0, 0.999826431274414062, 0.018630025908350944, 7200, 255, 1, 45505), -- Tuskarr Tea Pot (Area: -Unknown- - Difficulty: 0)
(@OGUID+69, 380764, 2444, 13644, 13710, '0', '0', 0, 3342.967041015625, 337.270843505859375, 8.907260894775390625, 2.801248550415039062, 0, 0, 0.985555648803710937, 0.169351965188980102, 7200, 255, 1, 45505), -- Cooking Fire (Area: -Unknown- - Difficulty: 0)
(@OGUID+70, 377136, 2444, 13644, 13710, '0', '0', 0, 3282.166748046875, 362.28472900390625, -2.0761880874633789, 1.074146270751953125, 0, 0, 0.511623382568359375, 0.859209835529327392, 7200, 255, 1, 45505), -- Small Tuskarr Table [DNT] (Area: -Unknown- - Difficulty: 0)
(@OGUID+71, 380765, 2444, 13644, 13710, '0', '0', 0, 3342.201416015625, 340.817718505859375, 8.872967720031738281, 5.907940864562988281, 0, 0, -0.1865234375, 0.982450485229492187, 7200, 255, 1, 45505), -- Chair (Area: -Unknown- - Difficulty: 0)
(@OGUID+72, 377137, 2444, 13644, 13710, '0', '0', 0, 3281.64501953125, 360.532989501953125, -2.07595467567443847, 1.159745216369628906, 0, 0, 0.547917366027832031, 0.836532473564147949, 7200, 255, 1, 45505), -- Tuskarr Chair [DNT] (Area: -Unknown- - Difficulty: 0)
(@OGUID+73, 380766, 2444, 13644, 13710, '0', '0', 0, 3327.662353515625, 361.13714599609375, 8.712553024291992187, 6.038843154907226562, 0.006589412689208984, -0.03966999053955078, -0.12133312225341796, 0.99179697036743164, 7200, 255, 1, 45505), -- Mailbox (Area: -Unknown- - Difficulty: 0)
(@OGUID+74, 380767, 2444, 13644, 13710, '0', '0', 0, 3313.83935546875, 333.954864501953125, 10.15590953826904296, 2.984505891799926757, -0.00751829147338867, 0.004434585571289062, 0.996876716613769531, 0.078489594161510467, 7200, 255, 1, 45505), -- Forge (Area: -Unknown- - Difficulty: 0)
(@OGUID+75, 380768, 2444, 13644, 13710, '0', '0', 0, 3317.0546875, 326.041656494140625, 9.851044654846191406, 3.630291461944580078, 0, 0, -0.97029495239257812, 0.241925001144409179, 7200, 255, 1, 45505), -- Anvil (Area: -Unknown- - Difficulty: 0)
(@OGUID+76, 381907, 2444, 13644, 13710, '0', '0', 0, 3279.44970703125, 379.78125, 27.99651527404785156, 0, 0, 0, 0, 1, 7200, 255, 1, 45505), -- -Unknown- (Area: -Unknown- - Difficulty: 0)
(@OGUID+77, 376990, 2444, 13644, 13710, '0', '0', 0, 3282.212646484375, 379.829864501953125, 28.61167716979980468, 0, 0, 0, 0, 1, 7200, 255, 1, 45505), -- -Unknown- (Area: -Unknown- - Difficulty: 0)
(@OGUID+78, 377212, 2444, 13644, 13710, '0', '0', 0, 3281.6806640625, 362.90972900390625, -1.02840363979339599, 5.616824626922607421, 0, 0, -0.32705020904541015, 0.945006966590881347, 7200, 255, 1, 45505), -- Tuskarr Mug (Area: -Unknown- - Difficulty: 0)
(@OGUID+79, 376624, 2444, 13644, 13710, '0', '0', 0, 3317.00341796875, 326.09375, 9.87638092041015625, 3.624031543731689453, 0, 0, -0.97104740142822265, 0.238886833190917968, 7200, 255, 1, 45505), -- Tuskarr Anvil (Area: -Unknown- - Difficulty: 0)
(@OGUID+80, 382031, 2444, 13644, 13710, '0', '0', 0, 3301.407958984375, 211.6041717529296875, 17.91700172424316406, 4.925380706787109375, 0, 0, -0.62793922424316406, 0.77826237678527832, 7200, 255, 1, 45505), -- Oily Dropcap (Area: -Unknown- - Difficulty: 0)
(@OGUID+81, 377137, 2444, 13644, 13710, '0', '0', 0, 3282.75341796875, 363.170135498046875, -2.38858532905578613, 4.831556320190429687, 0, 0, -0.66374492645263671, 0.747958958148956298, 7200, 255, 1, 45505), -- Tuskarr Chair [DNT] (Area: -Unknown- - Difficulty: 0)
(@OGUID+82, 377202, 2444, 13644, 13710, '0', '0', 0, 3354.228271484375, 389.166656494140625, 9.439576148986816406, 0, 0, 0, 0, 1, 7200, 255, 1, 45505), -- Ipko's Favorite Toy (Area: -Unknown- - Difficulty: 0)
(@OGUID+83, 377136, 2444, 13644, 13710, '0', '0', 0, 3353.71875, 389.40972900390625, 8.444237709045410156, 1.442589402198791503, 0, 0, 0.660357475280761718, 0.750951409339904785, 7200, 255, 1, 45505), -- Small Tuskarr Table [DNT] (Area: -Unknown- - Difficulty: 0)
(@OGUID+84, 377137, 2444, 13644, 13710, '0', '0', 0, 3357.37158203125, 394.017364501953125, 9.418888092041015625, 2.930448532104492187, 0, 0, 0.994432449340820312, 0.105376027524471282, 7200, 255, 1, 45505), -- Tuskarr Chair [DNT] (Area: -Unknown- - Difficulty: 0)
(@OGUID+85, 377137, 2444, 13644, 13710, '0', '0', 0, 3358.811767578125, 396.6875, 9.375819206237792968, 0.114323519170284271, 0.056648731231689453, -0.0502777099609375, 0.059838294982910156, 0.995330333709716796, 7200, 255, 1, 45505), -- Tuskarr Chair [DNT] (Area: -Unknown- - Difficulty: 0)
-- (@OGUID+86, 380534, 2444, 13644, 0, '0', '0', 0, 0, 0, 0, 1.488187074661254882, 0, 0, 0.677305221557617187, 0.735702097415924072, 7200, 255, 1, 45505), -- 0 (Area: 0 - Difficulty: 0) - !!! transport !!!
(@OGUID+87, 358375, 2444, 13644, 0, '0', '0', 0, 4073.57568359375, 145.3867645263671875, 39.86272430419921875, 6.126626968383789062, 0, 0, -0.07819938659667968, 0.996937751770019531, 7200, 255, 1, 45505), -- Snow Patch (Area: 0 - Difficulty: 0)
(@OGUID+88, 358375, 2444, 13644, 13709, '0', '0', 0, 4175.20654296875, 159.823272705078125, 44.22476959228515625, 0.47175830602645874, 0, 0, 0.233697891235351562, 0.972309231758117675, 7200, 255, 1, 45505), -- Snow Patch (Area: -Unknown- - Difficulty: 0)
(@OGUID+89, 380510, 2444, 13644, 13709, '0', '0', 0, 4334.53662109375, 164.1024322509765625, 60.42443084716796875, 1.594602704048156738, -0.03744459152221679, 0.036563873291015625, 0.7144927978515625, 0.697682619094848632, 7200, 255, 1, 45505), -- Dim Forge (Area: -Unknown- - Difficulty: 0)
(@OGUID+90, 381207, 2444, 13644, 13709, '0', '0', 0, 4299.48779296875, 246.795135498046875, 53.696197509765625, 4.528452873229980468, 0, 0, -0.7690582275390625, 0.639178693294525146, 7200, 255, 1, 45505), -- Saxifrage (Area: -Unknown- - Difficulty: 0)
(@OGUID+91, 380516, 2444, 13644, 13709, '0', '0', 0, 4335.42041015625, 159.2465362548828125, 62.14502716064453125, 0.000000598323254052, 0.087072372436523437, 0.043453216552734375, -0.00380134582519531, 0.995246589183807373, 7200, 255, 1, 45505), -- Glimmer of Wisdom (Area: -Unknown- - Difficulty: 0)
(@OGUID+92, 380517, 2444, 13644, 13709, '0', '0', 0, 4334.5693359375, 161.984375, 62.06460189819335937, 1.594602704048156738, -0.03744459152221679, 0.036563873291015625, 0.7144927978515625, 0.697682619094848632, 7200, 255, 1, 45505), -- Dim Forge (Area: -Unknown- - Difficulty: 0)
(@OGUID+93, 380513, 2444, 13644, 13709, '0', '0', 0, 4335.42041015625, 159.2465362548828125, 61.63179397583007812, 0.000000598323254052, 0.087072372436523437, 0.043453216552734375, -0.00380134582519531, 0.995246589183807373, 7200, 255, 1, 45505), -- Slack Tub (Area: -Unknown- - Difficulty: 0)
(@OGUID+94, 242514, 2444, 13644, 13709, '0', '0', 0, 4276.9375, 280.0850830078125, 71.86435699462890625, 0, 0, 0, 0, 1, 7200, 255, 1, 45505), -- Books on Fire (Area: -Unknown- - Difficulty: 0)
(@OGUID+95, 376946, 2444, 13644, 13709, '0', '0', 0, 4289.91162109375, 296.7100830078125, 56.43330764770507812, 0.541750907897949218, 0.165633678436279296, -0.40160942077636718, 0.26497650146484375, 0.860850036144256591, 7200, 255, 0, 45505), -- Pride and Protodrakes (Area: -Unknown- - Difficulty: 0)
(@OGUID+96, 242514, 2444, 13644, 13709, '0', '0', 0, 4291.95849609375, 298.576385498046875, 56.16894149780273437, 0, 0, 0, 0, 1, 7200, 255, 1, 45505), -- Books on Fire (Area: -Unknown- - Difficulty: 0)
(@OGUID+97, 376944, 2444, 13644, 13709, '0', '0', 0, 4275.68505859375, 298.548614501953125, 72.00154876708984375, 0.343224585056304931, 0.005877494812011718, -0.05046272277832031, 0.170409202575683593, 0.984062850475311279, 7200, 255, 1, 45505), -- The Lord of the Wings (Area: -Unknown- - Difficulty: 0)
(@OGUID+98, 382032, 2444, 13644, 13709, '0', '0', 0, 4268.29931640625, 360.836822509765625, 40.32796478271484375, 5.249528408050537109, 0, 0, -0.4941253662109375, 0.869390666484832763, 7200, 255, 1, 45505), -- Flowering Inferno Pod (Area: -Unknown- - Difficulty: 0)
(@OGUID+99, 382032, 2444, 13644, 13709, '0', '0', 0, 4227.30126953125, 377.517364501953125, 44.95383071899414062, 5.249528408050537109, 0, 0, -0.4941253662109375, 0.869390666484832763, 7200, 255, 1, 45505), -- Flowering Inferno Pod (Area: -Unknown- - Difficulty: 0)
(@OGUID+100, 376943, 2444, 13644, 13709, '0', '0', 0, 4203.5244140625, 388.963531494140625, 61.07999038696289062, 1.758780241012573242, 0.52230691909790039, 0.63103485107421875, -0.36572265625, 0.44185677170753479, 7200, 255, 0, 45505), -- Dracuixote (Area: -Unknown- - Difficulty: 0)
(@OGUID+101, 381343, 2444, 13644, 13709, '0', '0', 0, 4293.97216796875, 495.020843505859375, 192.4932861328125, 3.709810256958007812, -0.22795391082763671, 0.74643707275390625, 0.186701774597167968, 0.596666693687438964, 7200, 255, 1, 45505), -- Ancient Stone (Area: -Unknown- - Difficulty: 0)
(@OGUID+102, 381103, 2444, 13644, 13709, '0', '0', 0, 4090.018310546875, 458.42535400390625, 198.27203369140625, 3.043032407760620117, 0, 0, 0.998785972595214843, 0.049260172992944717, 7200, 255, 1, 45505), -- Tyrivite Deposit (Area: -Unknown- - Difficulty: 0)
(@OGUID+103, 381674, 2444, 13644, 13709, '0', '0', 0, 4007.46533203125, 487.875, 56.838165283203125, 5.87701416015625, 0, 0, -0.20169258117675781, 0.979448914527893066, 7200, 255, 1, 45505), -- Mature White Bell (Area: -Unknown- - Difficulty: 0)
(@OGUID+104, 376634, 2444, 13644, 14107, '0', '0', 0, 3743.624267578125, 643.95831298828125, 68.13543701171875, 1.380354642868041992, 0, 0, 0.636673927307128906, 0.771133124828338623, 7200, 255, 1, 45505), -- Rock Wall (Area: -Unknown- - Difficulty: 0)
(@OGUID+105, 377022, 2444, 13644, 13710, '0', '0', 0, 1588.2503662109375, -199.557861328125, 124.4765396118164062, 4.022983551025390625, 0, 0, -0.90445518493652343, 0.426568657159805297, 7200, 255, 1, 45505), -- 10DG_Dragon_Small_Building_Door01 (Area: -Unknown- - Difficulty: 0)
(@OGUID+106, 381097, 2444, 13644, 13710, '0', '0', 0, 3096.869873046875, -163.40972900390625, 4.300518035888671875, 1.283524513244628906, 0, 0, 0.598608016967773437, 0.801042079925537109, 7200, 255, 1, 45505), -- Thousandbite Pirahna Swarm (Area: -Unknown- - Difficulty: 0)
(@OGUID+107, 381207, 2444, 13644, 0, '0', '0', 0, 3202.71435546875, -300.82464599609375, 115.9653701782226562, 5.672667980194091796, 0, 0, -0.30053997039794921, 0.953769207000732421, 7200, 255, 1, 45505), -- Saxifrage (Area: 0 - Difficulty: 0)
(@OGUID+108, 376646, 2444, 13644, 0, '0', '0', 0, 2821.0234375, -430.90972900390625, 239.7423858642578125, 1.821213364601135253, 0, 0, 0.789875984191894531, 0.613266646862030029, 7200, 255, 1, 45505), -- Rock Wall (Area: 0 - Difficulty: 0)
(@OGUID+109, 381105, 2444, 13644, 0, '0', '0', 0, 3191.959228515625, -320.857635498046875, 71.58072662353515625, 2.606505393981933593, 0, 0, 0.964423179626464843, 0.264363259077072143, 7200, 255, 1, 45505), -- Rich Tyrivite Deposit (Area: 0 - Difficulty: 0)
(@OGUID+110, 381209, 2444, 13644, 0, '0', '0', 0, 2992.57470703125, -169.286453247070312, 4.234588623046875, 2.265928983688354492, 0, 0, 0.905673027038574218, 0.423976808786392211, 7200, 255, 1, 45505), -- Hochenblume (Area: 0 - Difficulty: 0)
(@OGUID+111, 381209, 2444, 13644, 0, '0', '0', 0, 2891.3994140625, -210.92535400390625, 124.965728759765625, 5.651777267456054687, 0, 0, -0.31048583984375, 0.950578033924102783, 7200, 255, 1, 45505), -- Hochenblume (Area: 0 - Difficulty: 0)
(@OGUID+112, 381209, 2444, 13644, 0, '0', '0', 0, 2931.772705078125, 8.951389312744140625, 6.409000396728515625, 2.643381834030151367, 0, 0, 0.969133377075195312, 0.246537059545516967, 7200, 255, 1, 45505), -- Hochenblume (Area: 0 - Difficulty: 0)
(@OGUID+113, 381674, 2444, 13644, 0, '0', '0', 0, 2838.755126953125, -211.232635498046875, 156.2759552001953125, 4.925380706787109375, 0, 0, -0.62793922424316406, 0.77826237678527832, 7200, 255, 1, 45505), -- Mature White Bell (Area: 0 - Difficulty: 0)
(@OGUID+114, 381674, 2444, 13644, 0, '0', '0', 0, 2861.51220703125, -289.618072509765625, 181.4693145751953125, 4.444805145263671875, 0, 0, -0.79511070251464843, 0.606464326381683349, 7200, 255, 1, 45505), -- Mature White Bell (Area: 0 - Difficulty: 0)
(@OGUID+115, 381674, 2444, 13644, 0, '0', '0', 0, 2856.841064453125, -8.33680534362792968, 104.890380859375, 4.925380706787109375, 0, 0, -0.62793922424316406, 0.77826237678527832, 7200, 255, 1, 45505), -- Mature White Bell (Area: 0 - Difficulty: 0)
(@OGUID+116, 381674, 2444, 13644, 0, '0', '0', 0, 2848.47998046875, -299.399322509765625, 182.6333465576171875, 4.925380706787109375, 0, 0, -0.62793922424316406, 0.77826237678527832, 7200, 255, 1, 45505), -- Mature White Bell (Area: 0 - Difficulty: 0)
(@OGUID+117, 381102, 2444, 13644, 0, '0', '0', 0, 2846.651123046875, -285.01214599609375, 188.3256072998046875, 2.522643327713012695, 0, 0, 0.952493667602539062, 0.304558366537094116, 7200, 255, 1, 45505), -- Tyrivite Deposit (Area: 0 - Difficulty: 0)
(@OGUID+118, 382206, 2444, 13644, 0, '0', '0', 0, 2756.49560546875, -203.838546752929687, 4.389852046966552734, 2.862335443496704101, 0, 0, 0.990267753601074218, 0.139175355434417724, 7200, 255, 1, 45505), -- Campfire (Area: 0 - Difficulty: 0)
(@OGUID+119, 382207, 2444, 13644, 0, '0', '0', 0, 2755.632080078125, -206.072921752929687, 4.440041542053222656, 1.300270915031433105, 0, 0, 0.605294227600097656, 0.796001791954040527, 7200, 255, 1, 45505), -- Stool (Area: 0 - Difficulty: 0)
(@OGUID+120, 381209, 2444, 13644, 0, '0', '0', 0, 2668.338623046875, -177.670135498046875, 4.467635631561279296, 2.161880254745483398, 0, 0, 0.8824005126953125, 0.470499008893966674, 7200, 255, 1, 45505), -- Hochenblume (Area: 0 - Difficulty: 0)
(@OGUID+121, 381097, 2444, 13644, 0, '0', '0', 0, 2601.309814453125, -153.602432250976562, 4.3005523681640625, 2.748279094696044921, 0, 0, 0.980725288391113281, 0.195391669869422912, 7200, 255, 1, 45505), -- Thousandbite Pirahna Swarm (Area: 0 - Difficulty: 0)
(@OGUID+122, 375673, 2444, 13644, 0, '0', '0', 0, 2684.09033203125, -319.994781494140625, 90.07418060302734375, 1.560711145401000976, -0.06100845336914062, 0.123096466064453125, 0.692803382873535156, 0.70791858434677124, 7200, 255, 1, 45505), -- Climbing Gear (Area: 0 - Difficulty: 0)
(@OGUID+123, 376241, 2444, 13644, 0, '0', '0', 0, 2685.576416015625, -313.78472900390625, 88.28452301025390625, 1.92216503620147705, -0.07145118713378906, 0.049907684326171875, 0.816692352294921875, 0.570453763008117675, 7200, 255, 1, 45505), -- Crashed Gyrocopter (Area: 0 - Difficulty: 0)
(@OGUID+124, 375668, 2444, 13644, 0, '0', '0', 0, 2551.579833984375, -14.9722223281860351, 99.334136962890625, 4.4572906494140625, 0, 0, -0.79130935668945312, 0.611415982246398925, 7200, 255, 1, 45505), -- Misty Treasure Chest (Area: 0 - Difficulty: 0)
(@OGUID+125, 381674, 2444, 13644, 0, '0', '0', 0, 2508.007080078125, -109.416656494140625, 74.1145477294921875, 4.925380706787109375, 0, 0, -0.62793922424316406, 0.77826237678527832, 7200, 255, 1, 45505), -- Mature White Bell (Area: 0 - Difficulty: 0)
(@OGUID+126, 381207, 2444, 13644, 0, '0', '0', 0, 2518.007080078125, -4.33333349227905273, 123.2047805786132812, 3.152981519699096679, 0, 0, -0.99998378753662109, 0.00569428876042366, 7200, 255, 1, 45505), -- Saxifrage (Area: 0 - Difficulty: 0)
(@OGUID+127, 382026, 2444, 13644, 0, '0', '0', 0, 2459.036376953125, -31.875, 87.60453033447265625, 3.78736734390258789, 0, 0, -0.94832324981689453, 0.317305892705917358, 7200, 255, 1, 45505), -- Stool (Area: 0 - Difficulty: 0)
(@OGUID+128, 382027, 2444, 13644, 0, '0', '0', 0, 2457.22216796875, -32.6597213745117187, 87.589508056640625, 2.862335443496704101, 0, 0, 0.990267753601074218, 0.139175355434417724, 7200, 255, 1, 45505), -- Campfire (Area: 0 - Difficulty: 0)
(@OGUID+129, 376240, 2444, 13644, 0, '0', '0', 0, 2453.20654296875, -31.5069446563720703, 89.3977813720703125, 1.560711145401000976, -0.06100845336914062, 0.123096466064453125, 0.692803382873535156, 0.70791858434677124, 7200, 255, 1, 45505), -- Climbing Gear (Area: 0 - Difficulty: 0)
(@OGUID+130, 375687, 2444, 13644, 0, '0', '0', 0, 2447.638916015625, -27.2465286254882812, 87.63449859619140625, 4.706197738647460937, 0.030747890472412109, -0.03093814849853515, -0.70861721038818359, 0.704243600368499755, 7200, 255, 1, 45505), -- Water Keg (Area: 0 - Difficulty: 0)
(@OGUID+131, 382028, 2444, 13644, 0, '0', '0', 0, 2456.42529296875, -31.0017356872558593, 87.60590362548828125, 5.209811687469482421, 0, 0, -0.51129150390625, 0.859407365322113037, 7200, 255, 1, 45505), -- Stool (Area: 0 - Difficulty: 0)
(@OGUID+132, 381674, 2444, 13644, 0, '0', '0', 0, 2381.22216796875, -64.7118072509765625, 74.8305206298828125, 4.925380706787109375, 0, 0, -0.62793922424316406, 0.77826237678527832, 7200, 255, 1, 45505), -- Mature White Bell (Area: 0 - Difficulty: 0)
(@OGUID+133, 381103, 2444, 13644, 13729, '0', '0', 0, 2377.536376953125, -268.822906494140625, -3.79740405082702636, 2.332078218460083007, 0, 0, 0.919198036193847656, 0.393795579671859741, 7200, 255, 1, 45505), -- Tyrivite Deposit (Area: -Unknown- - Difficulty: 0)
(@OGUID+134, 382053, 2444, 13644, 13729, '0', '0', 0, 2300.876708984375, 60.58333206176757812, 67.26474761962890625, 3.394674062728881835, 0, 0, -0.99200439453125, 0.126203224062919616, 7200, 255, 1, 45505), -- Stool (Area: -Unknown- - Difficulty: 0)
(@OGUID+135, 382054, 2444, 13644, 13729, '0', '0', 0, 2298.673583984375, 56.734375, 67.19528961181640625, 1.771507501602172851, 0, 0, 0.774392127990722656, 0.632705986499786376, 7200, 255, 1, 45505), -- Stool (Area: -Unknown- - Difficulty: 0)
(@OGUID+136, 382052, 2444, 13644, 13729, '0', '0', 0, 2297.673583984375, 60.11458206176757812, 67.32662200927734375, 3.141592741012573242, 0, 0, -1, 0, 7200, 255, 1, 45505), -- Campfire (Area: -Unknown- - Difficulty: 0)
(@OGUID+137, 380868, 2444, 13644, 13729, '0', '0', 0, 2273.7587890625, 98.064239501953125, 68.89034271240234375, 4.40695810317993164, 0, 0, -0.80644416809082031, 0.59131026268005371, 7200, 255, 1, 45505), -- Scribe's Drafting Table (Area: -Unknown- - Difficulty: 0)
(@OGUID+138, 381674, 2444, 13644, 13729, '0', '0', 0, 2253.017333984375, 76.671875, 69.30884552001953125, 4.925380706787109375, 0, 0, -0.62793922424316406, 0.77826237678527832, 7200, 255, 1, 45505), -- Mature White Bell (Area: -Unknown- - Difficulty: 0)
(@OGUID+139, 381103, 2444, 13644, 13729, '0', '0', 0, 2201.3681640625, 49.46527862548828125, 48.17666244506835937, 0, 0, 0, 0, 1, 7200, 255, 1, 45505), -- Tyrivite Deposit (Area: -Unknown- - Difficulty: 0)
(@OGUID+140, 381674, 2444, 13644, 13729, '0', '0', 0, 2384.2744140625, 155.7239532470703125, 34.02557754516601562, 4.925380706787109375, 0, 0, -0.62793922424316406, 0.77826237678527832, 7200, 255, 1, 45505), -- Mature White Bell (Area: -Unknown- - Difficulty: 0)
(@OGUID+141, 382030, 2444, 13644, 13729, '0', '0', 0, 2133.75341796875, 75.1875, 35.6348419189453125, 6.129708766937255859, 0, 0, -0.07666301727294921, 0.997057080268859863, 7200, 255, 1, 45505), -- Nectar Filled Panthis (Area: -Unknown- - Difficulty: 0)
(@OGUID+142, 382030, 2444, 13644, 13729, '0', '0', 0, 2353.99658203125, 169.953125, 26.56694984436035156, 6.129708766937255859, 0, 0, -0.07666301727294921, 0.997057080268859863, 7200, 255, 1, 45505), -- Nectar Filled Panthis (Area: -Unknown- - Difficulty: 0)
(@OGUID+143, 381396, 2444, 13644, 13729, '0', '0', 0, 2252.907958984375, 215.7569427490234375, 16.4729766845703125, 0, 0, 0, 0, 1, 7200, 255, 1, 45505), -- Tuskarr Fishing Net (Area: -Unknown- - Difficulty: 0)
(@OGUID+144, 375241, 2444, 13644, 13729, '0', '0', 0, 2154.369873046875, 203.75, 17.2714691162109375, 1.67100989818572998, 0, 0, 0.741635322570800781, 0.670803308486938476, 7200, 255, 1, 45505), -- Bubble Poppy (Area: -Unknown- - Difficulty: 0)
(@OGUID+145, 377098, 2444, 13644, 13729, '0', '0', 0, 1999.69970703125, 148.84375, 99.33200836181640625, 2.634918689727783203, 0, 0, 0.968081474304199218, 0.250635772943496704, 7200, 255, 1, 45505), -- Overgrown Shrub (Area: -Unknown- - Difficulty: 0)
(@OGUID+146, 377098, 2444, 13644, 13729, '0', '0', 0, 1967.8541259765625, 157.6024322509765625, 92.21964263916015625, 0.44649633765220642, 0, 0, 0.221398353576660156, 0.975183427333831787, 7200, 255, 1, 45505), -- Overgrown Shrub (Area: -Unknown- - Difficulty: 0)
(@OGUID+147, 382068, 2444, 13644, 13729, '0', '0', 0, 1971.5382080078125, 39.44270706176757812, 89.17705535888671875, 4.925380706787109375, 0, 0, -0.62793922424316406, 0.77826237678527832, 7200, 255, 1, 45505), -- Barbed Tulip (Area: -Unknown- - Difficulty: 0)
(@OGUID+148, 377098, 2444, 13644, 13729, '0', '0', 0, 1966.9097900390625, 99.79166412353515625, 97.165252685546875, 3.100623607635498046, 0, 0, 0.999790191650390625, 0.020483093336224555, 7200, 255, 1, 45505), -- Overgrown Shrub (Area: -Unknown- - Difficulty: 0)
(@OGUID+149, 377098, 2444, 13644, 13729, '0', '0', 0, 1939.5538330078125, 69.9461822509765625, 97.30240631103515625, 3.56853342056274414, 0, 0, -0.97730159759521484, 0.211852744221687316, 7200, 255, 1, 45505), -- Overgrown Shrub (Area: -Unknown- - Difficulty: 0)
(@OGUID+150, 377098, 2444, 13644, 13729, '0', '0', 0, 1942.890625, 91.55902862548828125, 100.464996337890625, 0, 0, 0, 0, 1, 7200, 255, 1, 45505), -- Overgrown Shrub (Area: -Unknown- - Difficulty: 0)
(@OGUID+151, 381396, 2444, 13644, 13729, '0', '0', 0, 2129.288330078125, 297.958343505859375, 16.67403793334960937, 0, 0, 0, 0, 1, 7200, 255, 1, 45505), -- Tuskarr Fishing Net (Area: -Unknown- - Difficulty: 0)
(@OGUID+152, 377098, 2444, 13644, 13729, '0', '0', 0, 1921.5347900390625, 119.6909713745117187, 100.9580917358398437, 3.228023529052734375, 0, 0, -0.99906635284423828, 0.043201856315135955, 7200, 255, 1, 45505), -- Overgrown Shrub (Area: -Unknown- - Difficulty: 0)
(@OGUID+153, 377098, 2444, 13644, 13729, '0', '0', 0, 1917.9617919921875, 145.9427032470703125, 105.2597732543945312, 0, 0, 0, 0, 1, 7200, 255, 1, 45505), -- Overgrown Shrub (Area: -Unknown- - Difficulty: 0)
(@OGUID+154, 378092, 2444, 13644, 13729, '0', '0', 0, 1958.2379150390625, 206.40972900390625, 91.60800933837890625, 0.506144583225250244, 0, 0, 0.250379562377929687, 0.968147754669189453, 7200, 255, 1, 45505), -- Garden Bench (Area: -Unknown- - Difficulty: 0)
(@OGUID+155, 378089, 2444, 13644, 13729, '0', '0', 0, 1951.7691650390625, 211.83160400390625, 91.60727691650390625, 1.169370889663696289, 0, 0, 0.551937103271484375, 0.833885729312896728, 7200, 255, 1, 45505), -- Garden Bench (Area: -Unknown- - Difficulty: 0)
(@OGUID+156, 378465, 2444, 13644, 13729, '0', '0', 0, 1984.7725830078125, 251.0868072509765625, 95.46433258056640625, 1.95742189884185791, 0, 0, 0.829778671264648437, 0.558092594146728515, 7200, 255, 1, 45505), -- Green Dragon Book [DNT] (Area: -Unknown- - Difficulty: 0)
(@OGUID+157, 378466, 2444, 13644, 13729, '0', '0', 0, 1981.921875, 252.498260498046875, 95.61998748779296875, 0.501884400844573974, 0, 0, 0.248316764831542968, 0.968678891658782958, 7200, 255, 1, 45505), -- Green Dragon Book - Open [DNT] (Area: -Unknown- - Difficulty: 0)
(@OGUID+158, 377098, 2444, 13644, 13729, '0', '0', 0, 1961.0850830078125, 247.84722900390625, 99.35052490234375, 0, 0, 0, 0, 1, 7200, 255, 1, 45505), -- Overgrown Shrub (Area: -Unknown- - Difficulty: 0)
(@OGUID+159, 377098, 2444, 13644, 0, '0', '0', 0, 1896.2569580078125, 182.7118072509765625, 93.16732025146484375, 0, 0, 0, 0, 1, 7200, 255, 1, 45505), -- Overgrown Shrub (Area: 0 - Difficulty: 0)
(@OGUID+160, 377098, 2444, 13644, 0, '0', '0', 0, 1914.24658203125, 252.0364532470703125, 92.27323150634765625, 3.808272361755371093, 0, 0, -0.94495487213134765, 0.327200710773468017, 7200, 255, 1, 45505), -- Overgrown Shrub (Area: 0 - Difficulty: 0)
(@OGUID+161, 382069, 2444, 13644, 0, '0', '0', 0, 1876.282958984375, 184.2569427490234375, 91.46289825439453125, 4.925380706787109375, 0, 0, -0.62793922424316406, 0.77826237678527832, 7200, 255, 1, 45505), -- Overripe Lifebinder's Gift (Area: 0 - Difficulty: 0)
(@OGUID+162, 377098, 2444, 13644, 0, '0', '0', 0, 1893.7066650390625, 237.6527862548828125, 95.375, 2.790819883346557617, 0, 0, 0.984659194946289062, 0.174488648772239685, 7200, 255, 1, 45505), -- Overgrown Shrub (Area: 0 - Difficulty: 0)
(@OGUID+163, 377098, 2444, 13644, 0, '0', '0', 0, 1869.2864990234375, 235.3194427490234375, 99.71237945556640625, 0, 0, 0, 0, 1, 7200, 255, 1, 45505), -- Overgrown Shrub (Area: 0 - Difficulty: 0)
(@OGUID+164, 381097, 2444, 13644, 0, '0', '0', 0, 1995.079833984375, 336.005218505859375, 17.109100341796875, 3.102238655090332031, 0, 0, 0.999806404113769531, 0.01967567391693592, 7200, 255, 1, 45505), -- Thousandbite Pirahna Swarm (Area: 0 - Difficulty: 0)
(@OGUID+165, 375241, 2444, 13644, 0, '0', '0', 0, 2011.3472900390625, 351.4375, 16.54095077514648437, 3.878517389297485351, 0, 0, -0.93288230895996093, 0.360181331634521484, 7200, 255, 1, 45505), -- Bubble Poppy (Area: 0 - Difficulty: 0)
(@OGUID+166, 382030, 2444, 13644, 0, '0', '0', 0, 1974.685791015625, 338.795135498046875, 17.18120193481445312, 6.129708766937255859, 0, 0, -0.07666301727294921, 0.997057080268859863, 7200, 255, 1, 45505), -- Nectar Filled Panthis (Area: 0 - Difficulty: 0)
(@OGUID+167, 377098, 2444, 13644, 0, '0', '0', 0, 1823.8350830078125, 186.0104217529296875, 96.50433349609375, 3.100623607635498046, 0, 0, 0.999790191650390625, 0.020483093336224555, 7200, 255, 1, 45505), -- Overgrown Shrub (Area: 0 - Difficulty: 0)
(@OGUID+168, 377098, 2444, 13644, 0, '0', '0', 0, 1890.015625, 137.7621612548828125, 109.0876235961914062, 4.201750755310058593, 0, 0, -0.86276721954345703, 0.505601346492767333, 7200, 255, 1, 45505), -- Overgrown Shrub (Area: 0 - Difficulty: 0)
(@OGUID+169, 382068, 2444, 13644, 0, '0', '0', 0, 1786.548583984375, 239.3038177490234375, 87.88484954833984375, 0.485666543245315551, 0, 0, 0.240453720092773437, 0.970660626888275146, 7200, 255, 1, 45505), -- Barbed Tulip (Area: 0 - Difficulty: 0)
(@OGUID+170, 378093, 2444, 13644, 0, '0', '0', 0, 1811.2552490234375, 45.98784637451171875, 128.0253448486328125, 0.863936781883239746, 0, 0, 0.418659210205078125, 0.908143401145935058, 7200, 255, 1, 45505), -- Mailbox (Area: 0 - Difficulty: 0)
(@OGUID+171, 381230, 2444, 13644, 13728, '0', '0', 0, 1764.2628173828125, 14.858306884765625, 127.9871978759765625, 5.157448768615722656, 0, 0, -0.53361415863037109, 0.845728039741516113, 7200, 255, 1, 45505), -- Stool (Area: -Unknown- - Difficulty: 0)
(@OGUID+172, 381231, 2444, 13644, 13728, '0', '0', 0, 1759.6151123046875, 20.43587112426757812, 127.9871978759765625, 1.457348585128784179, 0, 0, 0.665881156921386718, 0.746057868003845214, 7200, 255, 1, 45505), -- Stool (Area: -Unknown- - Difficulty: 0)
(@OGUID+173, 381227, 2444, 13644, 13728, '0', '0', 0, 1761.39599609375, 19.0663604736328125, 127.9871978759765625, 0.410150706768035888, 0, 0, 0.203640937805175781, 0.979045629501342773, 7200, 255, 1, 45505), -- Stool (Area: -Unknown- - Difficulty: 0)
(@OGUID+174, 381234, 2444, 13644, 13728, '0', '0', 0, 1764.7813720703125, 11.81002044677734375, 127.9871978759765625, 1.448621988296508789, 0, 0, 0.662619590759277343, 0.748956084251403808, 7200, 255, 1, 45505), -- Stool (Area: -Unknown- - Difficulty: 0)
(@OGUID+175, 381228, 2444, 13644, 13728, '0', '0', 0, 1746.2027587890625, -9.54001235961914062, 127.9871978759765625, 5.035275459289550781, 0, 0, -0.58424949645996093, 0.811574101448059082, 7200, 255, 1, 45505), -- Stool (Area: -Unknown- - Difficulty: 0)
(@OGUID+176, 381229, 2444, 13644, 13728, '0', '0', 0, 1742.5634765625, 6.4710540771484375, 128.0560302734375, 1.867498993873596191, 0, 0, 0.80385589599609375, 0.594824075698852539, 7200, 255, 1, 45505), -- Stool (Area: -Unknown- - Difficulty: 0)
(@OGUID+177, 381225, 2444, 13644, 13728, '0', '0', 0, 1773.1405029296875, -11.6352081298828125, 127.9871902465820312, 6.065019607543945312, 0, 0, -0.10886669158935546, 0.994056344032287597, 7200, 255, 1, 45505), -- Stool (Area: -Unknown- - Difficulty: 0)
(@OGUID+178, 381226, 2444, 13644, 13728, '0', '0', 0, 1774.3302001953125, -10.4320068359375, 127.9871902465820312, 4.852017402648925781, 0, 0, -0.65605831146240234, 0.754710197448730468, 7200, 255, 1, 45505), -- Stool (Area: -Unknown- - Difficulty: 0)
(@OGUID+179, 381236, 2444, 13644, 13728, '0', '0', 0, 1737.7919921875, -1.10776901245117187, 127.9871978759765625, 3.132858037948608398, 0, 0, 0.999990463256835937, 0.004367320332676172, 7200, 255, 1, 45505), -- Stool (Area: -Unknown- - Difficulty: 0)
(@OGUID+180, 381232, 2444, 13644, 13728, '0', '0', 0, 1744.3118896484375, -9.2544097900390625, 127.9871978759765625, 4.337143898010253906, 0, 0, -0.82658958435058593, 0.56280517578125, 7200, 255, 1, 45505), -- Stool (Area: -Unknown- - Difficulty: 0)
(@OGUID+181, 381233, 2444, 13644, 13728, '0', '0', 0, 1738.603515625, -3.13222503662109375, 127.9871978759765625, 4.040439605712890625, 0, 0, -0.90069770812988281, 0.434446364641189575, 7200, 255, 1, 45505), -- Stool (Area: -Unknown- - Difficulty: 0)
(@OGUID+182, 381235, 2444, 13644, 13728, '0', '0', 0, 1744.0059814453125, 7.883434295654296875, 128.0560302734375, 3.010695457458496093, 0, 0, 0.997859001159667968, 0.065401896834373474, 7200, 255, 1, 45505), -- Stool (Area: -Unknown- - Difficulty: 0)
(@OGUID+183, 381617, 2444, 13644, 13728, '0', '0', 0, 1768.9583740234375, -27.635416030883789, 129.7213287353515625, 4.38429880142211914, -0.25253200531005859, -0.65752029418945312, -0.26594448089599609, 0.65815514326095581, 7200, 255, 1, 45505), -- Kolgar's Pack (Area: -Unknown- - Difficulty: 0)
(@OGUID+184, 381300, 2444, 13644, 13728, '0', '0', 0, 1782.81396484375, -11.5956344604492187, 127.9871902465820312, 2.312558174133300781, 0, 0, 0.915310859680175781, 0.402748137712478637, 7200, 255, 1, 45505), -- Bench (Area: -Unknown- - Difficulty: 0)
(@OGUID+185, 381301, 2444, 13644, 13728, '0', '0', 0, 1780.09912109375, -8.4153289794921875, 127.9871902465820312, 5.45415496826171875, 0, 0, -0.40274620056152343, 0.915311694145202636, 7200, 255, 1, 45505), -- Bench (Area: -Unknown- - Difficulty: 0)
(@OGUID+186, 381302, 2444, 13644, 13728, '0', '0', 0, 1748.189208984375, -2.5404052734375, 127.9871978759765625, 2.399827241897583007, 0, 0, 0.932007789611816406, 0.36243826150894165, 7200, 255, 1, 45505), -- Bench (Area: -Unknown- - Difficulty: 0)
(@OGUID+187, 381303, 2444, 13644, 13728, '0', '0', 0, 1753.354248046875, 10.19652175903320312, 127.9871978759765625, 5.532694816589355468, 0, 0, -0.3665008544921875, 0.93041771650314331, 7200, 255, 1, 45505), -- Bench (Area: -Unknown- - Difficulty: 0)
(@OGUID+188, 381304, 2444, 13644, 13728, '0', '0', 0, 1744.7628173828125, 0.4517974853515625, 127.9871978759765625, 5.550147056579589843, 0, 0, -0.358367919921875, 0.933580458164215087, 7200, 255, 1, 45505), -- Bench (Area: -Unknown- - Difficulty: 0)
(@OGUID+189, 381305, 2444, 13644, 13728, '0', '0', 0, 1756.71875, 7.049030303955078125, 127.9871978759765625, 2.417279243469238281, 0, 0, 0.9351348876953125, 0.354291886091232299, 7200, 255, 1, 45505), -- Bench (Area: -Unknown- - Difficulty: 0)
(@OGUID+190, 381209, 2444, 13644, 13728, '0', '0', 0, 1687.5572509765625, 183.0677032470703125, 109.4669570922851562, 2.410969018936157226, 0, 0, 0.934012413024902343, 0.357240557670593261, 7200, 255, 1, 45505), -- Hochenblume (Area: -Unknown- - Difficulty: 0)
(@OGUID+191, 381341, 2444, 13644, 13728, '0', '0', 0, 1807.810791015625, -186.164932250976562, 114.3824615478515625, 0.440298229455947875, 0.294483184814453125, -0.03682708740234375, 0.237067222595214843, 0.9250527024269104, 7200, 255, 1, 45505), -- Ancient Stone (Area: -Unknown- - Difficulty: 0)
(@OGUID+192, 377100, 2444, 13644, 13728, '0', '0', 0, 1626.4478759765625, 82.8836822509765625, 130.8115997314453125, 0, 0, 0, 0, 1, 7200, 255, 1, 45505), -- Unpollinated Flora (Area: -Unknown- - Difficulty: 0)
(@OGUID+193, 252248, 2444, 13644, 13728, '0', '0', 0, 1353.060791015625, -148.803817749023437, 140.8897247314453125, 5.658845901489257812, 0, 0, -0.30712413787841796, 0.95166945457458496, 7200, 255, 1, 45505), -- Instance Portal (Area: -Unknown- - Difficulty: 0)
(@OGUID+194, 377102, 2444, 13644, 13727, '0', '0', 0, 1596.623291015625, 82.04166412353515625, 125.878936767578125, 0, 0, 0, 0, 1, 7200, 255, 1, 45505), -- Unpollinated Flora (Area: -Unknown- - Difficulty: 0)
(@OGUID+195, 379209, 2444, 13644, 13727, '0', '0', 0, 1654.765625, -89.640625, 332.136138916015625, 0.54977881908416748, 0, 0, 0.271440505981445312, 0.962455213069915771, 7200, 255, 1, 45505), -- Brazier (Area: -Unknown- - Difficulty: 0)
(@OGUID+196, 379210, 2444, 13644, 13727, '0', '0', 0, 1683.7586669921875, -115.345489501953125, 332.14459228515625, 1.658064603805541992, 0, 0, 0.737277984619140625, 0.675589501857757568, 7200, 255, 1, 45505), -- Brazier (Area: -Unknown- - Difficulty: 0)
(@OGUID+197, 316739, 2444, 13644, 13727, '0', '0', 0, 1679.1788330078125, -506.598968505859375, 201.74005126953125, 1.500435233116149902, 0, 0, 0.681797981262207031, 0.731540501117706298, 7200, 255, 1, 45505), -- Barrier (Wide) (Area: -Unknown- - Difficulty: 0)
(@OGUID+198, 379040, 2444, 13644, 13727, '0', '0', 0, 1577.501708984375, -116.920143127441406, 332.289459228515625, 3.553405284881591796, 0, 0, -0.97887611389160156, 0.204454332590103149, 7200, 255, 1, 45505), -- Glass Bead (Area: -Unknown- - Difficulty: 0)
(@OGUID+199, 382069, 2444, 13644, 13727, '0', '0', 0, 1587.157958984375, -29.869791030883789, 160.812591552734375, 4.925380706787109375, 0, 0, -0.62793922424316406, 0.77826237678527832, 7200, 255, 1, 45505), -- Overripe Lifebinder's Gift (Area: -Unknown- - Difficulty: 0)
(@OGUID+200, 379213, 2444, 13644, 13727, '0', '0', 0, 1564.8819580078125, -121.383682250976562, 330.755218505859375, 0.287977516651153564, 0, 0, 0.143491744995117187, 0.989651501178741455, 7200, 255, 1, 45505), -- Anvil (Area: -Unknown- - Difficulty: 0)
(@OGUID+201, 379211, 2444, 13644, 13727, '0', '0', 0, 1565.579833984375, -113.727432250976562, 330.609771728515625, 2.181660413742065429, 0, 0, 0.887010574340820312, 0.461749136447906494, 7200, 255, 1, 45505), -- Forge (Area: -Unknown- - Difficulty: 0)
(@OGUID+202, 380869, 2444, 13644, 13727, '0', '0', 0, 1633.798583984375, -242.80035400390625, 330.991607666015625, 6.213373661041259765, 0, 0, -0.03489875793457031, 0.999390840530395507, 7200, 255, 1, 45505), -- Tailor's Work Table (Area: -Unknown- - Difficulty: 0)
(@OGUID+203, 376281, 2444, 13644, 13727, '0', '0', 0, 1733.2396240234375, -250.192703247070312, 338.215423583984375, 0.008726147934794425, 0, 0, 0.004363059997558593, 0.999990463256835937, 7200, 255, 1, 45505), -- Empty Egg Incubator (Area: -Unknown- - Difficulty: 0)
(@OGUID+204, 377230, 2444, 13644, 13727, '0', '0', 0, 1713.0416259765625, -253.720489501953125, 337.18792724609375, 5.544940948486328125, 0, 0, -0.36079692840576171, 0.932644426822662353, 7200, 255, 1, 45505), -- Fallen Leaves (Area: -Unknown- - Difficulty: 0)
(@OGUID+205, 377231, 2444, 13644, 13727, '0', '0', 0, 1721.93408203125, -248.366317749023437, 337.514068603515625, 3.841685295104980468, -0.27987146377563476, 0.032662391662597656, -0.9121561050415039, 0.297617822885513305, 7200, 255, 1, 45505), -- Overgrown Weeds (Area: -Unknown- - Difficulty: 0)
(@OGUID+206, 377230, 2444, 13644, 13727, '0', '0', 0, 1737.0208740234375, -244.05035400390625, 337.850921630859375, 3.095371723175048828, 0, 0, 0.99973297119140625, 0.023108396679162979, 7200, 255, 1, 45505), -- Fallen Leaves (Area: -Unknown- - Difficulty: 0)
(@OGUID+207, 376281, 2444, 13644, 13727, '0', '0', 0, 1732.376708984375, -252.413192749023437, 338.215484619140625, 0.008726147934794425, 0, 0, 0.004363059997558593, 0.999990463256835937, 7200, 255, 1, 45505), -- Empty Egg Incubator (Area: -Unknown- - Difficulty: 0)
(@OGUID+208, 380870, 2444, 13644, 13727, '0', '0', 0, 1528.0677490234375, -159.107635498046875, 331.185760498046875, 0.401424884796142578, 0, 0, 0.199367523193359375, 0.979924798011779785, 7200, 255, 1, 45505), -- Alchemist's Lab Bench (Area: -Unknown- - Difficulty: 0)
(@OGUID+209, 376281, 2444, 13644, 13727, '0', '0', 0, 1504.0191650390625, -72.3159713745117187, 338.28961181640625, 6.248279094696044921, 0, 0, -0.01745223999023437, 0.999847710132598876, 7200, 255, 1, 45505), -- Empty Egg Incubator (Area: -Unknown- - Difficulty: 0)
(@OGUID+210, 376281, 2444, 13644, 13727, '0', '0', 0, 1735.28125, -256.458343505859375, 338.215423583984375, 0.008726147934794425, 0, 0, 0.004363059997558593, 0.999990463256835937, 7200, 255, 1, 45505), -- Empty Egg Incubator (Area: -Unknown- - Difficulty: 0)
(@OGUID+211, 376281, 2444, 13644, 13727, '0', '0', 0, 1735.673583984375, -251.043411254882812, 338.215423583984375, 0.008726147934794425, 0, 0, 0.004363059997558593, 0.999990463256835937, 7200, 255, 1, 45505), -- Empty Egg Incubator (Area: -Unknown- - Difficulty: 0)
(@OGUID+212, 376283, 2444, 13644, 13727, '0', '0', 0, 1504.3646240234375, -78.5902786254882812, 338.333770751953125, 6.248279094696044921, 0, 0, -0.01745223999023437, 0.999847710132598876, 7200, 255, 1, 45505), -- Blue Dragon Egg Incubator (Area: -Unknown- - Difficulty: 0)
(@OGUID+213, 379212, 2444, 13644, 13727, '0', '0', 0, 1528.44970703125, -152.885421752929687, 331.024444580078125, 1.96349501609802246, 0, 0, 0.831469535827636718, 0.555570363998413085, 7200, 255, 1, 45505), -- Thomas's Crafting Table (Area: -Unknown- - Difficulty: 0)
(@OGUID+214, 376281, 2444, 13644, 13727, '0', '0', 0, 1503.6441650390625, -81.8402786254882812, 337.8509521484375, 6.248279094696044921, 0, 0, -0.01745223999023437, 0.999847710132598876, 7200, 255, 1, 45505), -- Empty Egg Incubator (Area: -Unknown- - Difficulty: 0)
(@OGUID+215, 377265, 2444, 13644, 13727, '0', '0', 0, 1707.7239990234375, -258.458343505859375, 336.0595703125, 3.840374231338500976, -0.11559295654296875, -0.00785446166992187, -0.93448257446289062, 0.336628675460815429, 7200, 255, 1, 45505), -- Overgrown Weeds (Area: -Unknown- - Difficulty: 0)
(@OGUID+216, 376281, 2444, 13644, 13727, '0', '0', 0, 1509.7916259765625, -81.0972213745117187, 337.850982666015625, 6.248279094696044921, 0, 0, -0.01745223999023437, 0.999847710132598876, 7200, 255, 1, 45505), -- Empty Egg Incubator (Area: -Unknown- - Difficulty: 0)
(@OGUID+217, 377266, 2444, 13644, 13727, '0', '0', 0, 1737.5972900390625, -266.189239501953125, 338.080963134765625, 2.832688331604003906, 0.217318058013916015, -0.16455841064453125, 0.945181846618652343, 0.179790630936622619, 7200, 255, 1, 45505), -- Overgrown Weeds (Area: -Unknown- - Difficulty: 0)
(@OGUID+218, 376283, 2444, 13644, 13727, '0', '0', 0, 1509.9774169921875, -74.8350677490234375, 338.192535400390625, 6.248279094696044921, 0, 0, -0.01745223999023437, 0.999847710132598876, 7200, 255, 1, 45505), -- Blue Dragon Egg Incubator (Area: -Unknown- - Difficulty: 0)
(@OGUID+219, 376281, 2444, 13644, 13727, '0', '0', 0, 1729.486083984375, -253.989578247070312, 338.215423583984375, 0.008726147934794425, 0, 0, 0.004363059997558593, 0.999990463256835937, 7200, 255, 1, 45505), -- Empty Egg Incubator (Area: -Unknown- - Difficulty: 0)
(@OGUID+220, 382069, 2444, 13644, 13727, '0', '0', 0, 1541.6197509765625, -200.513885498046875, 125.7078323364257812, 4.925380706787109375, 0, 0, -0.62793922424316406, 0.77826237678527832, 7200, 255, 1, 45505), -- Overripe Lifebinder's Gift (Area: -Unknown- - Difficulty: 0)
(@OGUID+221, 379167, 2444, 13644, 13727, '0', '0', 0, 1532.736083984375, -290.4288330078125, 128.113067626953125, 0.500112533569335937, -0.04297065734863281, 0.168247222900390625, 0.243699073791503906, 0.95417875051498413, 7200, 255, 1, 45505), -- Mysterious Glyph (Area: -Unknown- - Difficulty: 0)
(@OGUID+222, 376288, 2444, 13644, 13727, '0', '0', 0, 1421.2708740234375, -183.092010498046875, 338.204559326171875, 6.09602212905883789, 0.174454689025878906, -0.25870609283447265, -0.03855609893798828, 0.949289321899414062, 7200, 255, 1, 45505), -- Bronze Dragon Egg (Area: -Unknown- - Difficulty: 0)
(@OGUID+223, 376286, 2444, 13644, 13727, '0', '0', 0, 1422.2742919921875, -181.442703247070312, 338.546478271484375, 0.026179106906056404, 0, 0, 0.013089179992675781, 0.999914348125457763, 7200, 255, 1, 45505), -- Bronze Dragon Egg Incubator (Area: -Unknown- - Difficulty: 0)
(@OGUID+224, 376286, 2444, 13644, 13727, '0', '0', 0, 1419.576416015625, -179.84722900390625, 338.546478271484375, 0.026179106906056404, 0, 0, 0.013089179992675781, 0.999914348125457763, 7200, 255, 1, 45505), -- Bronze Dragon Egg Incubator (Area: -Unknown- - Difficulty: 0)
(@OGUID+225, 376286, 2444, 13644, 13727, '0', '0', 0, 1420.4305419921875, -184.626739501953125, 337.694305419921875, 0.026179106906056404, 0, 0, 0.013089179992675781, 0.999914348125457763, 7200, 255, 1, 45505), -- Bronze Dragon Egg Incubator (Area: -Unknown- - Difficulty: 0)
(@OGUID+226, 376288, 2444, 13644, 13727, '0', '0', 0, 1421.5521240234375, -178.163192749023437, 338.204559326171875, 5.941610336303710937, 0.263567924499511718, 0.113739013671875, -0.20149898529052734, 0.93647933006286621, 7200, 255, 1, 45505), -- Bronze Dragon Egg (Area: -Unknown- - Difficulty: 0)
(@OGUID+227, 376288, 2444, 13644, 13727, '0', '0', 0, 1422.845458984375, -179.22222900390625, 338.204559326171875, 0.026179106906056404, 0, 0, 0.013089179992675781, 0.999914348125457763, 7200, 255, 1, 45505), -- Bronze Dragon Egg (Area: -Unknown- - Difficulty: 0)
(@OGUID+228, 376288, 2444, 13644, 13727, '0', '0', 0, 1419.796875, -182.20660400390625, 338.204559326171875, 0.026179106906056404, 0, 0, 0.013089179992675781, 0.999914348125457763, 7200, 255, 1, 45505), -- Bronze Dragon Egg (Area: -Unknown- - Difficulty: 0)
(@OGUID+229, 377300, 2444, 13644, 13727, '0', '0', 0, 1443.796875, -279.864593505859375, 331.621978759765625, 1.151013612747192382, 0, 0, 0.544260025024414062, 0.838916540145874023, 7200, 255, 1, 45505), -- Whelptender's Watering Can (Area: -Unknown- - Difficulty: 0)
(@OGUID+230, 377301, 2444, 13644, 13727, '0', '0', 0, 1445.4427490234375, -279.763885498046875, 331.621978759765625, 0, 0, 0, 0, 1, 7200, 255, 1, 45505), -- Reinforced Hornstrider Lasso (Area: -Unknown- - Difficulty: 0)
(@OGUID+231, 377302, 2444, 13644, 13727, '0', '0', 0, 1446.7916259765625, -279.177093505859375, 331.656890869140625, 2.420129776000976562, 0.449417591094970703, 0.547280311584472656, -0.44933032989501953, 0.544619441032409667, 7200, 255, 1, 45505), -- Gardener's Trusty Rake (Area: -Unknown- - Difficulty: 0)
(@OGUID+232, 377298, 2444, 13644, 13727, '0', '0', 0, 1442.2760009765625, -280.19097900390625, 331.62188720703125, 0, 0, 0, 0, 1, 7200, 255, 0, 45505), -- Shimmery Jar of Fireflies (Area: -Unknown- - Difficulty: 0)
(@OGUID+233, 376289, 2444, 13644, 13727, '0', '0', 0, 1632.875, -364.01214599609375, 338.123687744140625, 6.236252784729003906, -0.05820131301879882, -0.06491470336914062, -0.02714252471923828, 0.995822250843048095, 7200, 255, 1, 45505), -- Green Dragon Egg (Area: -Unknown- - Difficulty: 0)
(@OGUID+234, 376284, 2444, 13644, 13727, '0', '0', 0, 1638.4617919921875, -364.526031494140625, 339.05194091796875, 0, 0, 0, 0, 1, 7200, 255, 1, 45505), -- Green Dragon Egg Incubator (Area: -Unknown- - Difficulty: 0)
(@OGUID+235, 376288, 2444, 13644, 13727, '0', '0', 0, 1418.5052490234375, -184.664932250976562, 338.204559326171875, 0.026179106906056404, 0, 0, 0.013089179992675781, 0.999914348125457763, 7200, 255, 1, 45505), -- Bronze Dragon Egg (Area: -Unknown- - Difficulty: 0)
(@OGUID+236, 376289, 2444, 13644, 13727, '0', '0', 0, 1636.7274169921875, -367.4600830078125, 338.15692138671875, 0, 0, 0, 0, 1, 7200, 255, 1, 45505), -- Green Dragon Egg (Area: -Unknown- - Difficulty: 0)
(@OGUID+237, 376288, 2444, 13644, 13727, '0', '0', 0, 1417.3680419921875, -178.423614501953125, 338.204559326171875, 0.026179106906056404, 0, 0, 0.013089179992675781, 0.999914348125457763, 7200, 255, 1, 45505), -- Bronze Dragon Egg (Area: -Unknown- - Difficulty: 0)
(@OGUID+238, 376289, 2444, 13644, 13727, '0', '0', 0, 1636.951416015625, -369.81597900390625, 338.356719970703125, 6.236252784729003906, -0.05820131301879882, -0.06491470336914062, -0.02714252471923828, 0.995822250843048095, 7200, 255, 1, 45505), -- Green Dragon Egg (Area: -Unknown- - Difficulty: 0)
(@OGUID+239, 376288, 2444, 13644, 13727, '0', '0', 0, 1418.73095703125, -178.305557250976562, 338.204559326171875, 0.162206888198852539, -0.16216182708740234, 0.529494285583496093, 0.144373893737792968, 0.820058226585388183, 7200, 255, 1, 45505), -- Bronze Dragon Egg (Area: -Unknown- - Difficulty: 0)
(@OGUID+240, 376289, 2444, 13644, 13727, '0', '0', 0, 1636.3004150390625, -365.203125, 338.093170166015625, 0, 0, 0, 0, 1, 7200, 255, 1, 45505), -- Green Dragon Egg (Area: -Unknown- - Difficulty: 0)
(@OGUID+241, 376284, 2444, 13644, 13727, '0', '0', 0, 1638.0364990234375, -366.8975830078125, 338.550628662109375, 0, 0, 0, 0, 1, 7200, 255, 1, 45505), -- Green Dragon Egg Incubator (Area: -Unknown- - Difficulty: 0)
(@OGUID+242, 376284, 2444, 13644, 13727, '0', '0', 0, 1634.87158203125, -363.61285400390625, 339.051971435546875, 0, 0, 0, 0, 1, 7200, 255, 1, 45505), -- Green Dragon Egg Incubator (Area: -Unknown- - Difficulty: 0)
(@OGUID+243, 376289, 2444, 13644, 13727, '0', '0', 0, 1633.03125, -367.94097900390625, 338.245513916015625, 6.236252784729003906, -0.05820131301879882, -0.06491470336914062, -0.02714252471923828, 0.995822250843048095, 7200, 255, 1, 45505), -- Green Dragon Egg (Area: -Unknown- - Difficulty: 0)
(@OGUID+244, 376286, 2444, 13644, 13727, '0', '0', 0, 1416.3385009765625, -180.279510498046875, 338.6392822265625, 0.026179106906056404, 0, 0, 0.013089179992675781, 0.999914348125457763, 7200, 255, 1, 45505), -- Bronze Dragon Egg Incubator (Area: -Unknown- - Difficulty: 0)
(@OGUID+245, 376289, 2444, 13644, 13727, '0', '0', 0, 1637.3697509765625, -365.536468505859375, 338.3111572265625, 0.00409805541858077, 0.255395412445068359, 0.040781974792480468, -0.00866889953613281, 0.965937316417694091, 7200, 255, 1, 45505), -- Green Dragon Egg (Area: -Unknown- - Difficulty: 0)
(@OGUID+246, 376284, 2444, 13644, 13727, '0', '0', 0, 1634.9114990234375, -368.930572509765625, 338.4088134765625, 0, 0, 0, 0, 1, 7200, 255, 1, 45505), -- Green Dragon Egg Incubator (Area: -Unknown- - Difficulty: 0)
(@OGUID+247, 376286, 2444, 13644, 13727, '0', '0', 0, 1416.88720703125, -183.729171752929687, 338.546661376953125, 0.026179106906056404, 0, 0, 0.013089179992675781, 0.999914348125457763, 7200, 255, 1, 45505), -- Bronze Dragon Egg Incubator (Area: -Unknown- - Difficulty: 0)
(@OGUID+248, 376284, 2444, 13644, 13727, '0', '0', 0, 1633.24658203125, -366.185760498046875, 338.429962158203125, 0, 0, 0, 0, 1, 7200, 255, 1, 45505), -- Green Dragon Egg Incubator (Area: -Unknown- - Difficulty: 0)
(@OGUID+249, 376289, 2444, 13644, 13727, '0', '0', 0, 1635.4271240234375, -366.796875, 338.193267822265625, 6.062668800354003906, -0.20768404006958007, 0.17212677001953125, -0.07138442993164062, 0.960283279418945312, 7200, 255, 1, 45505); -- Green Dragon Egg (Area: -Unknown- - Difficulty: 0)

INSERT INTO `gameobject` (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnDifficulties`, `PhaseId`, `PhaseGroup`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `VerifiedBuild`) VALUES
(@OGUID+250, 376288, 2444, 13644, 13727, '0', '0', 0, 1417.5416259765625, -181.625, 337.633941650390625, 0.026179106906056404, 0, 0, 0.013089179992675781, 0.999914348125457763, 7200, 255, 1, 45505), -- Bronze Dragon Egg (Area: -Unknown- - Difficulty: 0)
(@OGUID+251, 376289, 2444, 13644, 13727, '0', '0', 0, 1638.2725830078125, -368.854156494140625, 338.567352294921875, 6.236252784729003906, -0.05820131301879882, -0.06491470336914062, -0.02714252471923828, 0.995822250843048095, 7200, 255, 1, 45505), -- Green Dragon Egg (Area: -Unknown- - Difficulty: 0)
(@OGUID+252, 375105, 2444, 13644, 13727, '0', '0', 0, 1535.5504150390625, -397.3975830078125, 332.4608154296875, 1.594577670097351074, 0, 0, 0.715464591979980468, 0.698648989200592041, 7200, 255, 1, 45505), -- Teleport Tether (Area: -Unknown- - Difficulty: 0)
(@OGUID+253, 35591, 2444, 13644, 13727, '0', '0', 0, 1382.63720703125, -436.0924072265625, 0, 1.306928634643554687, 0, 0, 0.607940673828125, 0.793982446193695068, 7200, 255, 1, 45505), -- Fishing Bobber (Area: -Unknown- - Difficulty: 0)
(@OGUID+254, 35591, 2444, 13644, 13727, '0', '0', 0, 1331.219482421875, -408.03924560546875, 0, 0.980704724788665771, 0, 0, 0.470936775207519531, 0.882166981697082519, 7200, 255, 1, 45505), -- Fishing Bobber (Area: -Unknown- - Difficulty: 0)
(@OGUID+255, 378850, 2444, 13644, 13727, '0', '0', 0, 1429.5364990234375, -579.0555419921875, 0, 0.611103415489196777, 0, 0, 0.30081939697265625, 0.953681111335754394, 7200, 255, 1, 45505), -- Large Fish Sighting (Area: -Unknown- - Difficulty: 0)
(@OGUID+256, 378849, 2444, 13644, 13727, '0', '0', 0, 1428.2569580078125, -580.95831298828125, -0.40247350931167602, 3.054721355438232421, 0, 0, 0.999056816101074218, 0.043422043323516845, 7200, 255, 1, 45505), -- Large Fish Sighting (Area: -Unknown- - Difficulty: 0)
(@OGUID+257, 378850, 2444, 13644, 13727, '0', '0', 0, 1429.671875, -582.95660400390625, 0, 5.792013168334960937, 0, 0, -0.24312496185302734, 0.969994962215423583, 7200, 255, 1, 45505), -- Large Fish Sighting (Area: -Unknown- - Difficulty: 0)
(@OGUID+258, 35591, 2444, 13644, 13727, '0', '0', 0, 1332.6466064453125, -408.10321044921875, 0, 0.857925832271575927, 0, 0, 0.415927886962890625, 0.909397602081298828, 7200, 255, 1, 45505), -- Fishing Bobber (Area: -Unknown- - Difficulty: 0)
(@OGUID+259, 268888, 2444, 13644, 13727, '0', '0', 0, 1382.4150390625, -435.577545166015625, 0, 2.032178401947021484, 0, 0, 0.850054740905761718, 0.526694357395172119, 7200, 255, 1, 45505), -- Fishing Bobber (Area: -Unknown- - Difficulty: 0)
(@OGUID+260, 380835, 2444, 13644, 13727, '0', '0', 0, 1324.1961669921875, -139.965286254882812, 138.3463134765625, 1.213001728057861328, 0, 0, 0.569995880126953125, 0.821647584438323974, 7200, 255, 1, 45505), -- Meeting Stone (Area: -Unknown- - Difficulty: 0)
(@OGUID+261, 241593, 2444, 13644, 13727, '0', '0', 0, 1330.743408203125, -408.05767822265625, 0, 0.625954866409301757, 0, 0, 0.307892799377441406, 0.951421082019805908, 7200, 255, 1, 45505), -- Fishing Bobber (Area: -Unknown- - Difficulty: 0)
(@OGUID+262, 268887, 2444, 13644, 13727, '0', '0', 0, 1381.63916015625, -436.84124755859375, 0, 1.569741368293762207, 0, 0, 0.70673370361328125, 0.707479655742645263, 7200, 255, 1, 45505), -- Fishing Bobber (Area: -Unknown- - Difficulty: 0)
(@OGUID+263, 241593, 2444, 13644, 13727, '0', '0', 0, 1329.5704345703125, -409.12646484375, 0, 1.081366419792175292, 0, 0, 0.514721870422363281, 0.857357203960418701, 7200, 255, 1, 45505), -- Fishing Bobber (Area: -Unknown- - Difficulty: 0)
(@OGUID+264, 268888, 2444, 13644, 13727, '0', '0', 0, 1381.4615478515625, -435.930908203125, 0, 1.134297847747802734, 0, 0, 0.537229537963867187, 0.843436062335968017, 7200, 255, 1, 45505), -- Fishing Bobber (Area: -Unknown- - Difficulty: 0)
(@OGUID+265, 377101, 2444, 13644, 13727, '0', '0', 0, 1559.5625, 91.8368072509765625, 128.4889373779296875, 4.579417228698730468, 0, 0, -0.75252246856689453, 0.658566534519195556, 7200, 255, 1, 45505), -- Unpollinated Flora (Area: -Unknown- - Difficulty: 0)
(@OGUID+266, 382068, 2444, 13644, 13727, '0', '0', 0, 1497.138916015625, 96.5225677490234375, 158.751251220703125, 4.925380706787109375, 0, 0, -0.62793922424316406, 0.77826237678527832, 7200, 255, 1, 45505), -- Barbed Tulip (Area: -Unknown- - Difficulty: 0)
(@OGUID+267, 379037, 2444, 13644, 13727, '0', '0', 0, 1646.045166015625, -289.486114501953125, 331.816619873046875, 0.468743771314620971, 0, 0, 0.232232093811035156, 0.972660362720489501, 7200, 255, 1, 45505), -- Soft Ruby Feather (Area: -Unknown- - Difficulty: 0)
(@OGUID+268, 379037, 2444, 13644, 13727, '0', '0', 0, 1685.8629150390625, -223.786453247070312, 330.840240478515625, 1.794245362281799316, 0, 0, 0.781535148620605468, 0.623861253261566162, 7200, 255, 0, 45505), -- Soft Ruby Feather (Area: -Unknown- - Difficulty: 0)
(@OGUID+269, 379037, 2444, 13644, 13727, '0', '0', 0, 1651.046875, -278.666656494140625, 331.735626220703125, 5.461594581604003906, 0, 0, -0.3993387222290039, 0.916803479194641113, 7200, 255, 1, 45505), -- Soft Ruby Feather (Area: -Unknown- - Difficulty: 0)
(@OGUID+270, 379037, 2444, 13644, 13727, '0', '0', 0, 1662.204833984375, -213.657989501953125, 330.076080322265625, 6.202738761901855468, 0, 0, -0.04021263122558593, 0.999191164970397949, 7200, 255, 1, 45505), -- Soft Ruby Feather (Area: -Unknown- - Difficulty: 0)
(@OGUID+271, 379037, 2444, 13644, 13727, '0', '0', 0, 1681.1649169921875, -203.078125, 330.40521240234375, 4.904618263244628906, 0, 0, -0.63598442077636718, 0.771701931953430175, 7200, 255, 0, 45505), -- Soft Ruby Feather (Area: -Unknown- - Difficulty: 0)
(@OGUID+272, 379037, 2444, 13644, 13727, '0', '0', 0, 1676.8194580078125, -231.39410400390625, 333.083343505859375, 4.886186599731445312, 0, 0, -0.64306926727294921, 0.765807986259460449, 7200, 255, 1, 45505), -- Soft Ruby Feather (Area: -Unknown- - Difficulty: 0)
(@OGUID+273, 379037, 2444, 13644, 13727, '0', '0', 0, 1634.265625, -279.3975830078125, 332.33782958984375, 1.189154744148254394, 0, 0, 0.560158729553222656, 0.82838529348373413, 7200, 255, 1, 45505), -- Soft Ruby Feather (Area: -Unknown- - Difficulty: 0)
(@OGUID+274, 379037, 2444, 13644, 13727, '0', '0', 0, 1642.3941650390625, -257.6944580078125, 331.65350341796875, 3.451520919799804687, 0, 0, -0.98801708221435546, 0.154344573616981506, 7200, 255, 1, 45505), -- Soft Ruby Feather (Area: -Unknown- - Difficulty: 0)
(@OGUID+275, 379037, 2444, 13644, 13727, '0', '0', 0, 1666.2847900390625, -221.053817749023437, 330.11297607421875, 5.007913112640380859, 0, 0, -0.59529781341552734, 0.803505122661590576, 7200, 255, 1, 45505), -- Soft Ruby Feather (Area: -Unknown- - Difficulty: 0)
(@OGUID+276, 379037, 2444, 13644, 13727, '0', '0', 0, 1682.342041015625, -228.8125, 329.916656494140625, 3.451520919799804687, 0, 0, -0.98801708221435546, 0.154344573616981506, 7200, 255, 0, 45505), -- Soft Ruby Feather (Area: -Unknown- - Difficulty: 0)
(@OGUID+277, 379037, 2444, 13644, 13727, '0', '0', 0, 1630.782958984375, -269.69097900390625, 331.669403076171875, 5.503794670104980468, 0, 0, -0.37990665435791015, 0.925024807453155517, 7200, 255, 1, 45505), -- Soft Ruby Feather (Area: -Unknown- - Difficulty: 0)
(@OGUID+278, 379037, 2444, 13644, 13727, '0', '0', 0, 1664.9478759765625, -193.890625, 330.914947509765625, 0, 0, 0, 0, 1, 7200, 255, 0, 45505), -- Soft Ruby Feather (Area: -Unknown- - Difficulty: 0)
(@OGUID+279, 381097, 2444, 13644, 13727, '0', '0', 0, 1719.060791015625, -364.814239501953125, 198.9738006591796875, 5.347952842712402343, 0, 0, -0.4507598876953125, 0.892645239830017089, 7200, 255, 1, 45505), -- Thousandbite Pirahna Swarm (Area: -Unknown- - Difficulty: 0)
(@OGUID+280, 377901, 2444, 13644, 13727, '0', '0', 0, 1695.6597900390625, -489.0069580078125, 244.9618377685546875, 0.249934017658233642, 0.011022567749023437, -0.13834857940673828, 0.122559547424316406, 0.982709169387817382, 7200, 255, 1, 45505), -- Observant Riddles: A Field Guide (Area: -Unknown- - Difficulty: 0)
(@OGUID+281, 377899, 2444, 13644, 13727, '0', '0', 0, 1670.079833984375, -525.69268798828125, 239.667205810546875, 0.620159864425659179, 0, 0, 0.305134773254394531, 0.952309191226959228, 7200, 255, 1, 45505), -- Hidden Hornswog Hostage (Area: -Unknown- - Difficulty: 0)
(@OGUID+282, 35591, 2444, 13644, 13727, '0', '0', 0, 1382.244384765625, -435.09588623046875, 0, 1.82456362247467041, 0, 0, 0.790902137756347656, 0.611942648887634277, 7200, 255, 1, 45505), -- Fishing Bobber (Area: -Unknown- - Difficulty: 0)
(@OGUID+283, 35591, 2444, 13644, 13727, '0', '0', 0, 1380.521484375, -437.131561279296875, 0, 1.082340955734252929, 0, 0, 0.515139579772949218, 0.857106268405914306, 7200, 255, 1, 45505), -- Fishing Bobber (Area: -Unknown- - Difficulty: 0)
(@OGUID+284, 35591, 2444, 13644, 13727, '0', '0', 0, 1329.90625, -405.776031494140625, 0, 0.746210217475891113, 0, 0, 0.364508628845214843, 0.931200027465820312, 7200, 255, 1, 45505), -- Fishing Bobber (Area: -Unknown- - Difficulty: 0)
(@OGUID+285, 268888, 2444, 13644, 13727, '0', '0', 0, 1328.9263916015625, -406.7236328125, 0, 0.905317127704620361, 0, 0, 0.437357902526855468, 0.899287521839141845, 7200, 255, 1, 45505); -- Fishing Bobber (Area: -Unknown- - Difficulty: 0)
DELETE FROM `gameobject_addon` WHERE `guid` BETWEEN @OGUID+0 AND @OGUID+285;
INSERT INTO `gameobject_addon` (`guid`, `parent_rotation0`, `parent_rotation1`, `parent_rotation2`, `parent_rotation3`, `WorldEffectID`, `AIAnimKitID`) VALUES
(@OGUID+1, 0, 0, 0, 1, 20518, 0), -- Flowering Inferno Pod
(@OGUID+2, 0, 0, 0, 1, 20518, 0), -- Djaradin Supply Jar
(@OGUID+3, 0, 0, 0, 1, 20518, 0), -- Djaradin Supply Jar
(@OGUID+4, 0, 0, 0, 1, 20518, 0), -- Flowering Inferno Pod
(@OGUID+5, 0, 0, 0, 1, 20518, 0), -- Flowering Inferno Pod
(@OGUID+8, 0, 0, 0, 1, 20518, 0), -- Flowering Inferno Pod
(@OGUID+10, 0, 0, 0, 1, 20518, 0), -- Flowering Inferno Pod
(@OGUID+14, 0, 0, 0, 1, 20518, 0), -- Flowering Inferno Pod
(@OGUID+17, 0, 0, 0, 1, 20518, 0), -- Flowering Inferno Pod
(@OGUID+22, 0, 0, 0, 1, 20518, 0), -- Djaradin Supply Jar
(@OGUID+23, 0, 0, 0, 1, 19982, 0), -- Spare Djaradin Tools
(@OGUID+25, 0, 0, 0, 1, 20518, 0), -- Flowering Inferno Pod
(@OGUID+26, 0, 0, 0, 1, 20518, 0), -- Flowering Inferno Pod
(@OGUID+27, 0, 0, 0, 1, 20518, 0), -- Flowering Inferno Pod
(@OGUID+28, 0, 0, 0, 1, 20518, 0), -- Mature White Bell
(@OGUID+29, 0, 0, 0, 1, 20518, 0), -- Flowering Inferno Pod
(@OGUID+30, 0, 0, 0, 1, 20518, 0), -- Flowering Inferno Pod
(@OGUID+31, 0, 0, 0, 1, 20518, 0), -- Nectar Filled Panthis
(@OGUID+34, 0, 0, 0, 1, 20518, 0), -- Oily Dropcap
(@OGUID+35, 0, 0, 0, 1, 20518, 0), -- Oily Dropcap
(@OGUID+41, 0, 0, 0, 1, 20518, 0), -- Mature White Bell
(@OGUID+42, 0, 0, 0, 1, 20518, 0), -- Flowering Inferno Pod
(@OGUID+44, 0, 0, 0, 1, 20518, 0), -- Flowering Inferno Pod
(@OGUID+47, 0, 0, 0, 1, 20518, 0), -- Flowering Inferno Pod
(@OGUID+51, 0, 0, 0, 1, 20518, 0), -- Flowering Inferno Pod
(@OGUID+57, 0, 0, 0, 1, 0, 9340), -- Hatched Dragon Egg
(@OGUID+59, 0, 0, 0, 1, 0, 9340), -- Hatched Dragon Egg
(@OGUID+60, 0, 0, 0, 1, 0, 9340), -- Hatched Dragon Egg
(@OGUID+66, 0, 0, 0, 1, 20518, 0), -- Mature White Bell
(@OGUID+80, 0, 0, 0, 1, 20518, 0), -- Oily Dropcap
(@OGUID+91, 0, 0, 0, 1, 18512, 0), -- Glimmer of Wisdom
(@OGUID+98, 0, 0, 0, 1, 20518, 0), -- Flowering Inferno Pod
(@OGUID+99, 0, 0, 0, 1, 20518, 0), -- Flowering Inferno Pod
(@OGUID+103, 0, 0, 0, 1, 20518, 0), -- Mature White Bell
(@OGUID+105, 0, 0, 0.941175997257232666, 0.337916880846023559, 0, 0), -- 10DG_Dragon_Small_Building_Door01
(@OGUID+113, 0, 0, 0, 1, 20518, 0), -- Mature White Bell
(@OGUID+114, 0, 0, 0, 1, 20518, 0), -- Mature White Bell
(@OGUID+115, 0, 0, 0, 1, 20518, 0), -- Mature White Bell
(@OGUID+116, 0, 0, 0, 1, 20518, 0), -- Mature White Bell
(@OGUID+125, 0, 0, 0, 1, 20518, 0), -- Mature White Bell
(@OGUID+132, 0, 0, 0, 1, 20518, 0), -- Mature White Bell
(@OGUID+138, 0, 0, 0, 1, 20518, 0), -- Mature White Bell
(@OGUID+140, 0, 0, 0, 1, 20518, 0), -- Mature White Bell
(@OGUID+141, 0, 0, 0, 1, 20518, 0), -- Nectar Filled Panthis
(@OGUID+142, 0, 0, 0, 1, 20518, 0), -- Nectar Filled Panthis
(@OGUID+147, 0, 0, 0, 1, 20518, 0), -- Barbed Tulip
(@OGUID+161, 0, 0, 0, 1, 20518, 0), -- Overripe Lifebinder's Gift
(@OGUID+166, 0, 0, 0, 1, 20518, 0), -- Nectar Filled Panthis
(@OGUID+169, 0, 0, 0, 1, 20518, 0), -- Barbed Tulip
(@OGUID+171, 0, 0, 0.410718709230422973, 0.911762118339538574, 0, 0), -- Stool
(@OGUID+172, 0, 0, 0.410718709230422973, 0.911762118339538574, 0, 0), -- Stool
(@OGUID+173, 0, 0, 0.410718709230422973, 0.911762118339538574, 0, 0), -- Stool
(@OGUID+174, 0, 0, 0.410718709230422973, 0.911762118339538574, 0, 0), -- Stool
(@OGUID+175, 0, 0, 0.410718709230422973, 0.911762118339538574, 0, 0), -- Stool
(@OGUID+176, 0, 0, 0.410718709230422973, 0.911762118339538574, 0, 0), -- Stool
(@OGUID+177, 0, 0, 0.410718709230422973, 0.911762118339538574, 0, 0), -- Stool
(@OGUID+178, 0, 0, 0.410718709230422973, 0.911762118339538574, 0, 0), -- Stool
(@OGUID+179, 0, 0, 0.410718709230422973, 0.911762118339538574, 0, 0), -- Stool
(@OGUID+180, 0, 0, 0.410718709230422973, 0.911762118339538574, 0, 0), -- Stool
(@OGUID+181, 0, 0, 0.410718709230422973, 0.911762118339538574, 0, 0), -- Stool
(@OGUID+182, 0, 0, 0.410718709230422973, 0.911762118339538574, 0, 0), -- Stool
(@OGUID+184, 0, 0, 0.410718709230422973, 0.911762118339538574, 0, 0), -- Bench
(@OGUID+185, 0, 0, 0.410718709230422973, 0.911762118339538574, 0, 0), -- Bench
(@OGUID+186, 0, 0, 0.410718709230422973, 0.911762118339538574, 0, 0), -- Bench
(@OGUID+187, 0, 0, 0.410718709230422973, 0.911762118339538574, 0, 0), -- Bench
(@OGUID+188, 0, 0, 0.410718709230422973, 0.911762118339538574, 0, 0), -- Bench
(@OGUID+189, 0, 0, 0.410718709230422973, 0.911762118339538574, 0, 0), -- Bench
(@OGUID+199, 0, 0, 0, 1, 20518, 0), -- Overripe Lifebinder's Gift
(@OGUID+220, 0, 0, 0, 1, 20518, 0), -- Overripe Lifebinder's Gift
(@OGUID+253, 0, 0, 0, 1, 2773, 0), -- Fishing Bobber
(@OGUID+254, 0, 0, 0, 1, 2773, 0), -- Fishing Bobber
(@OGUID+258, 0, 0, 0, 1, 2773, 0), -- Fishing Bobber
(@OGUID+259, 0, 0, 0, 1, 2773, 0), -- Fishing Bobber
(@OGUID+261, 0, 0, 0, 1, 2773, 0), -- Fishing Bobber
(@OGUID+262, 0, 0, 0, 1, 2773, 0), -- Fishing Bobber
(@OGUID+263, 0, 0, 0, 1, 2773, 0), -- Fishing Bobber
(@OGUID+264, 0, 0, 0, 1, 2773, 0), -- Fishing Bobber
(@OGUID+266, 0, 0, 0, 1, 20518, 0), -- Barbed Tulip
(@OGUID+281, 0, 0, 0, 1, 2437, 0), -- Hidden Hornswog Hostage
(@OGUID+282, 0, 0, 0, 1, 2773, 0), -- Fishing Bobber
(@OGUID+283, 0, 0, 0, 1, 2773, 0), -- Fishing Bobber
(@OGUID+284, 0, 0, 0, 1, 2773, 0), -- Fishing Bobber
(@OGUID+285, 0, 0, 0, 1, 2773, 0); -- Fishing Bobber


DELETE FROM `creature_template_addon` WHERE `entry` IN (193061 /*193061 (Danastra) - -Unknown-, -Unknown-*/, 194195 /*194195 (Lifeshrine Door)*/, 194159 /*194159 (Relentless Gust) - -Unknown-*/, 194142 /*194142 (Intrusive Pupstinger)*/, 189881 /*189881 (Elemental Target [DNT])*/, 190295 /*190295 (Akxall)*/, 191982 /*191982 (Faramin)*/, 195051 /*195051 (Azure Tender) - -Unknown-*/, 191980 /*191980 (Xolleth) - -Unknown-*/, 191176 /*191176 (Dazakros) - -Unknown-*/, 191027 /*191027 (Lasztak) - -Unknown-*/, 191013 /*191013 (Keshki) - -Unknown-, -Unknown-*/, 192625 /*192625 (Ruby Groundskeeper)*/, 196774 /*196774 (Zoristrasz)*/, 193737 /*193737 (Ruby Tender) - -Unknown-*/, 188107 /*188107 (Tionistrasz)*/, 195050 /*195050 (Bronze Tender) - -Unknown-*/, 191174 /*191174 (Vaeros) - -Unknown-*/, 191012 /*191012 (Akora) - -Unknown-, -Unknown-*/, 193077 /*193077 (Ruby Percher)*/, 192305 /*192305 (Boots) - Cosmetic - Sleep Zzz Breakable*/, 192096 /*192096 (Ruby Dozer) - Cosmetic - Sleep Zzz Breakable*/, 186692 /*186692 (Ruby Swarmer)*/, 187071 /*187071 (Nurse Sentry)*/, 189448 /*189448 (Trellain)*/, 193920 /*193920 (Kahtzar) - -Unknown-*/, 193979 /*193979 (Ruby Whelpling)*/, 193097 /*193097 (Peaceful Duck)*/, 195052 /*195052 (Sapphire Tender) - -Unknown-*/, 191126 /*191126 (Ruby Shrineguard) - -Unknown-*/, 194474 /*194474 (Zhustostrasza) - -Unknown-*/, 194478 /*194478 (Clokkistrasz)*/, 188029 /*188029 (Sprightly Butterfly)*/, 194479 /*194479 (Sprightly Butterfly)*/, 187072 /*187072 (Ruby Shrineguard)*/, 187060 /*187060 (Ruby Keeper)*/, 191954 /*191954 (Kskeiton) - -Unknown-*/, 193955 /*193955 (Lillistrazsa) - -Unknown-*/, 192284 /*192284 (Kandrostrasz) - -Unknown-, -Unknown-*/, 187058 /*187058 (Ruby Scaleguard)*/, 194076 /*194076 (Veritistrasz)*/, 194818 /*194818 (Dragon Glyph) - -Unknown-*/, 191031 /*191031 (Ruby Tender) - -Unknown-, -Unknown-*/, 195125 /*195125 (Ruby Skyguard)*/, 195120 /*195120 (Ruby Skyguard)*/, 185489 /*185489 (King Drippy) - Ride Vehicle Hardcoded*/, 185496 /*185496 (Primal Dropling) - -Unknown-*/, 185484 /*185484 (Handhold)*/, 180377 /*180377 (Handhold)*/, 186146 /*186146 (Handhold)*/, 186143 /*186143 (Handhold)*/, 185485 /*185485 (Handhold)*/, 185464 /*185464 (Handhold)*/, 186918 /*186918 (Turbulent Gust)*/, 196827 /*196827 (Crabtender Kad'irsza) - -Unknown-*/, 193304 /*193304 (Ru'kroszk)*/, 194821 /*194821 (Dragon Glyph) - -Unknown-*/, 189814 /*189814 (Cliffdrip Wavemender) - -Unknown-*/, 189815 /*189815 (Cliffdrip Fallstriker) - -Unknown-*/, 197211 /*197211 (Murghurgl the Invader) - Ride Vehicle Hardcoded*/, 191765 /*191765 (Mean Duck)*/, 191768 /*191768 (Majordomo Selistra) - -Unknown-, -Unknown-*/, 193791 /*193791 (Sundered Mercenary) - Cosmetic - SitGround and Drink Breakable*/, 193790 /*193790 (Sundered Supplyhand)*/, 188372 /*188372 (Primal Tarasek) - -Unknown-*/, 190013 /*190013 (Ruby Dragon Egg) - -Unknown-*/, 186834 /*186834 (Stubborn Hornswog) - -Unknown-*/, 191891 /*191891 (Sendrax) - Root Self*/, 186822 /*186822 (Infused Ruby Whelpling) - -Unknown-*/, 194314 /*194314 (Captain Exposition) - -Unknown-*/, 194820 /*194820 (Dragon Glyph) - -Unknown-*/, 188666 /*188666 (Unleashed Lavaburst) - -Unknown-*/, 186823 /*186823 (Lavacaller Primalist) - -Unknown-*/, 190080 /*190080 (Tarasek Elementalist) - -Unknown-*/, 186825 /*186825 (Molten Primalist) - Dual Wield*/, 192181 /*192181 (Wild Rockfang) - -Unknown-*/, 194524 /*194524 (Earthshatter Elemental) - -Unknown-*/, 194523 /*194523 (Raging Elemental) - -Unknown-*/, 194517 /*194517 (Crushing Elemental) - -Unknown-*/, 191016 /*191016 (Uktulut Protector)*/, 188698 /*188698 (Dreadsquall Feaster)*/, 188699 /*188699 (Carrion Phoenix) - -Unknown-*/, 191917 /*191917 (Erupting Magma) - -Unknown-*/, 191975 /*191975 (Rocan the Mountain) - -Unknown-*/, 191517 /*191517 (Erupting Droplet) - -Unknown-*/, 191983 /*191983 (Erupting Droplet) - -Unknown-*/, 191944 /*191944 (Erupting Lasher) - -Unknown-*/, 190093 /*190093 (Ruby Culler) - -Unknown-, -Unknown-*/, 188297 /*188297 (Caretaker Ventraz) - -Unknown-*/, 191945 /*191945 (Cracked Elemental) - Permanent Feign Death (NO Stun, Untrackable, Immune), -Unknown-*/, 186777 /*186777 (Meatgrinder Sotok) - -Unknown-*/, 186683 /*186683 (Restless Rocks) - -Unknown-*/, 191901 /*191901 (Blazing Dreadsquall) - -Unknown-*/, 190767 /*190767 (Qalashi Metalshaper) - -Unknown-*/, 180705 /*180705 (Magmammoth Calf) - -Unknown-*/);
INSERT INTO `creature_template_addon` (`entry`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `aiAnimKit`, `movementAnimKit`, `meleeAnimKit`, `visibilityDistanceType`, `auras`) VALUES
(193061, 0, 0, 0, 1, 0, 0, 0, 0, 0, '373397 360001'), -- 193061 (Danastra) - -Unknown-, -Unknown-
(194195, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- 194195 (Lifeshrine Door)
(194159, 0, 0, 0, 1, 0, 0, 0, 0, 0, '391958'), -- 194159 (Relentless Gust) - -Unknown-
(194142, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- 194142 (Intrusive Pupstinger)
(189881, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- 189881 (Elemental Target [DNT])
(190295, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- 190295 (Akxall)
(191982, 0, 0, 1, 1, 0, 0, 0, 0, 0, ''), -- 191982 (Faramin)
(195051, 0, 0, 0, 1, 0, 0, 0, 0, 0, '382158'), -- 195051 (Azure Tender) - -Unknown-
(191980, 0, 0, 1, 1, 0, 0, 0, 0, 0, '377397'), -- 191980 (Xolleth) - -Unknown-
(191176, 0, 0, 0, 1, 0, 0, 0, 0, 0, '389771'), -- 191176 (Dazakros) - -Unknown-
(191027, 0, 0, 0, 1, 0, 0, 0, 0, 0, '389833'), -- 191027 (Lasztak) - -Unknown-
(191013, 0, 0, 0, 1, 0, 0, 0, 0, 0, '376365 389802'), -- 191013 (Keshki) - -Unknown-, -Unknown-
(192625, 0, 0, 1, 257, 0, 0, 0, 0, 0, ''), -- 192625 (Ruby Groundskeeper)
(196774, 0, 0, 1, 1, 0, 0, 0, 0, 0, ''), -- 196774 (Zoristrasz)
(193737, 0, 0, 0, 1, 0, 0, 0, 0, 0, '382158'), -- 193737 (Ruby Tender) - -Unknown-
(188107, 0, 0, 1, 1, 0, 0, 0, 0, 0, ''), -- 188107 (Tionistrasz)
(195050, 0, 0, 0, 1, 0, 0, 0, 0, 0, '382158'), -- 195050 (Bronze Tender) - -Unknown-
(191174, 0, 0, 0, 1, 0, 0, 0, 0, 0, '374830'), -- 191174 (Vaeros) - -Unknown-
(191012, 0, 0, 0, 1, 0, 0, 0, 0, 0, '376364 389776'), -- 191012 (Akora) - -Unknown-, -Unknown-
(193077, 0, 0, 3, 1, 0, 0, 0, 0, 0, ''), -- 193077 (Ruby Percher)
(192305, 0, 0, 0, 1, 0, 0, 0, 0, 0, '120703'), -- 192305 (Boots) - Cosmetic - Sleep Zzz Breakable
(192096, 0, 0, 0, 1, 0, 0, 0, 0, 0, '120703'), -- 192096 (Ruby Dozer) - Cosmetic - Sleep Zzz Breakable
(186692, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- 186692 (Ruby Swarmer)
(187071, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- 187071 (Nurse Sentry)
(189448, 0, 0, 0, 1, 0, 24419, 0, 0, 0, ''), -- 189448 (Trellain)
(193920, 0, 0, 0, 1, 0, 0, 0, 0, 0, '381919'), -- 193920 (Kahtzar) - -Unknown-
(193979, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- 193979 (Ruby Whelpling)
(193097, 0, 0, 1, 1, 0, 0, 0, 0, 0, ''), -- 193097 (Peaceful Duck)
(195052, 0, 0, 0, 1, 0, 0, 0, 0, 0, '382158'), -- 195052 (Sapphire Tender) - -Unknown-
(191126, 0, 0, 0, 257, 0, 0, 0, 0, 0, '375277'), -- 191126 (Ruby Shrineguard) - -Unknown-
(194474, 0, 0, 1, 1, 0, 0, 0, 0, 0, '377397'), -- 194474 (Zhustostrasza) - -Unknown-
(194478, 0, 0, 1, 1, 0, 0, 0, 0, 0, ''), -- 194478 (Clokkistrasz)
(188029, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- 188029 (Sprightly Butterfly)
(194479, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- 194479 (Sprightly Butterfly)
(187072, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- 187072 (Ruby Shrineguard)
(187060, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- 187060 (Ruby Keeper)
(191954, 0, 0, 0, 1, 0, 0, 0, 0, 0, '364324'), -- 191954 (Kskeiton) - -Unknown-
(193955, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, '382828'), -- 193955 (Lillistrazsa) - -Unknown-
(192284, 0, 0, 0, 1, 0, 0, 0, 0, 0, '373400 360001'), -- 192284 (Kandrostrasz) - -Unknown-, -Unknown-
(187058, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- 187058 (Ruby Scaleguard)
(194076, 0, 0, 1, 1, 0, 0, 0, 0, 0, ''), -- 194076 (Veritistrasz)
(194818, 0, 0, 50331648, 1, 0, 0, 0, 0, 4, '384674'), -- 194818 (Dragon Glyph) - -Unknown-
(191031, 0, 0, 0, 1, 0, 0, 0, 0, 0, '375039 375042'), -- 191031 (Ruby Tender) - -Unknown-, -Unknown-
(195125, 0, 0, 50331648, 1, 0, 0, 0, 0, 3, ''), -- 195125 (Ruby Skyguard)
(195120, 0, 0, 50331648, 1, 0, 0, 0, 0, 4, ''), -- 195120 (Ruby Skyguard)
(185489, 0, 0, 0, 1, 0, 0, 0, 0, 0, '46598'), -- 185489 (King Drippy) - Ride Vehicle Hardcoded
(185496, 0, 0, 0, 1, 0, 0, 0, 0, 0, '367419'), -- 185496 (Primal Dropling) - -Unknown-
(185484, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- 185484 (Handhold)
(180377, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- 180377 (Handhold)
(186146, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- 186146 (Handhold)
(186143, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- 186143 (Handhold)
(185485, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- 185485 (Handhold)
(185464, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- 185464 (Handhold)
(186918, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- 186918 (Turbulent Gust)
(196827, 0, 0, 1, 1, 0, 0, 0, 0, 0, '369109'), -- 196827 (Crabtender Kad'irsza) - -Unknown-
(193304, 0, 0, 0, 0, 0, 0, 0, 0, 0, ''), -- 193304 (Ru'kroszk)
(194821, 0, 0, 50331648, 1, 0, 0, 0, 0, 4, '384680'), -- 194821 (Dragon Glyph) - -Unknown-
(189814, 0, 0, 0, 1, 0, 0, 0, 0, 0, '391245'), -- 189814 (Cliffdrip Wavemender) - -Unknown-
(189815, 0, 0, 0, 1, 0, 0, 0, 0, 0, '372653'), -- 189815 (Cliffdrip Fallstriker) - -Unknown-
(197211, 0, 0, 0, 1, 0, 0, 0, 0, 0, '46598'), -- 197211 (Murghurgl the Invader) - Ride Vehicle Hardcoded
(191765, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- 191765 (Mean Duck)
(191768, 0, 0, 0, 1, 0, 0, 0, 0, 0, '374008 360001'), -- 191768 (Majordomo Selistra) - -Unknown-, -Unknown-
(193791, 0, 0, 0, 1, 0, 0, 0, 0, 0, '162443'), -- 193791 (Sundered Mercenary) - Cosmetic - SitGround and Drink Breakable
(193790, 0, 0, 8, 1, 0, 0, 0, 0, 0, ''), -- 193790 (Sundered Supplyhand)
(188372, 0, 0, 0, 1, 0, 0, 0, 0, 0, '369706'), -- 188372 (Primal Tarasek) - -Unknown-
(190013, 0, 0, 0, 1, 0, 0, 0, 0, 0, '384742'), -- 190013 (Ruby Dragon Egg) - -Unknown-
(186834, 0, 0, 0, 1, 0, 0, 0, 0, 0, '391254'), -- 186834 (Stubborn Hornswog) - -Unknown-
(191891, 0, 0, 0, 1, 0, 0, 0, 0, 0, '112080'), -- 191891 (Sendrax) - Root Self
(186822, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, '376690'), -- 186822 (Infused Ruby Whelpling) - -Unknown-
(194314, 0, 0, 0, 1, 0, 0, 0, 0, 0, '385839'), -- 194314 (Captain Exposition) - -Unknown-
(194820, 0, 0, 50331648, 1, 0, 0, 0, 0, 4, '384678'), -- 194820 (Dragon Glyph) - -Unknown-
(188666, 0, 0, 0, 1, 0, 0, 0, 0, 0, '376804'), -- 188666 (Unleashed Lavaburst) - -Unknown-
(186823, 0, 0, 0, 1, 0, 0, 0, 0, 0, '364117'), -- 186823 (Lavacaller Primalist) - -Unknown-
(190080, 0, 0, 0, 1, 0, 0, 0, 0, 0, '369706'), -- 190080 (Tarasek Elementalist) - -Unknown-
(186825, 0, 0, 0, 1, 0, 0, 0, 0, 0, '42459'), -- 186825 (Molten Primalist) - Dual Wield
(192181, 0, 0, 0, 1, 0, 0, 0, 0, 0, '391254'), -- 192181 (Wild Rockfang) - -Unknown-
(194524, 0, 0, 0, 1, 0, 0, 0, 0, 0, '377717'), -- 194524 (Earthshatter Elemental) - -Unknown-
(194523, 0, 0, 0, 1, 0, 0, 0, 0, 0, '364022'), -- 194523 (Raging Elemental) - -Unknown-
(194517, 0, 0, 0, 1, 0, 0, 0, 0, 0, '381535'), -- 194517 (Crushing Elemental) - -Unknown-
(191016, 0, 0, 0, 257, 0, 0, 0, 0, 0, ''), -- 191016 (Uktulut Protector)
(188698, 0, 0, 50331648, 1, 0, 0, 0, 0, 0, ''), -- 188698 (Dreadsquall Feaster)
(188699, 0, 0, 0, 1, 0, 0, 0, 0, 0, '369897'), -- 188699 (Carrion Phoenix) - -Unknown-
(191917, 0, 0, 0, 1, 0, 0, 0, 0, 0, '376765'), -- 191917 (Erupting Magma) - -Unknown-
(191975, 0, 0, 0, 1, 0, 0, 0, 0, 0, '376852'), -- 191975 (Rocan the Mountain) - -Unknown-
(191517, 0, 0, 0, 1, 0, 0, 0, 0, 0, '370034'), -- 191517 (Erupting Droplet) - -Unknown-
(191983, 0, 0, 0, 1, 0, 0, 0, 0, 0, '370034'), -- 191983 (Erupting Droplet) - -Unknown-
(191944, 0, 0, 0, 1, 0, 0, 0, 0, 0, '376804'), -- 191944 (Erupting Lasher) - -Unknown-
(190093, 0, 0, 0, 1, 0, 0, 0, 0, 0, '369109 376252'), -- 190093 (Ruby Culler) - -Unknown-, -Unknown-
(188297, 0, 0, 0, 1, 0, 0, 0, 0, 0, '376071'), -- 188297 (Caretaker Ventraz) - -Unknown-
(191945, 0, 0, 262144, 1, 0, 0, 0, 0, 0, '159474 376838'), -- 191945 (Cracked Elemental) - Permanent Feign Death (NO Stun, Untrackable, Immune), -Unknown-
(186777, 0, 0, 0, 1, 0, 0, 0, 0, 0, '392594'), -- 186777 (Meatgrinder Sotok) - -Unknown-
(186683, 0, 0, 0, 1, 0, 0, 0, 0, 0, '375960'), -- 186683 (Restless Rocks) - -Unknown-
(191901, 0, 0, 0, 1, 0, 0, 0, 0, 0, '391254'), -- 191901 (Blazing Dreadsquall) - -Unknown-
(190767, 0, 0, 0, 1, 0, 0, 0, 0, 0, '370104'), -- 190767 (Qalashi Metalshaper) - -Unknown-
(180705, 0, 0, 0, 1, 0, 0, 0, 0, 0, '265075'); -- 180705 (Magmammoth Calf) - -Unknown-

UPDATE `creature_template_addon` SET `auras`='391254 391255' WHERE `entry`=191553; -- 191553 (Wild Argali) - -Unknown-, -Unknown-
UPDATE `creature_template_addon` SET `auras`='364588 391245' WHERE `entry`=186724; -- 186724 (Qalashi Flamemuzzler) - -Unknown-, -Unknown-
UPDATE `creature_template_addon` SET `auras`='376065' WHERE `entry`=191513; -- 191513 (Captured Raven) - -Unknown-
UPDATE `creature_template_addon` SET `auras`='375804' WHERE `entry`=191899; -- 191899 (Qalashi Marauder) - -Unknown-
UPDATE `creature_template_addon` SET `auras`='375948' WHERE `entry`=186728; -- 186728 (Magmammoth Bull) - -Unknown-
UPDATE `creature_template_addon` SET `bytes1`=1, `auras`='' WHERE `entry`=186792; -- 186792 (Qalashi Marauder)
UPDATE `creature_template_addon` SET `auras`='369897' WHERE `entry`=186684; -- 186684 (Lava Phoenix) - -Unknown-
UPDATE `creature_template_addon` SET `bytes2`=0, `auras`='369596' WHERE `entry`=190766; -- 190766 (Qalashi Ragetamer) - -Unknown-
UPDATE `creature_template_addon` SET `auras`='391254' WHERE `entry`=191672; -- 191672 (Lava Tarantula) - -Unknown-
UPDATE `creature_template_addon` SET `bytes1`=0, `auras`='369788' WHERE `entry`=191446; -- 191446 (Qalashi Scoundrel) - -Unknown-


DELETE FROM `creature_template_scaling` WHERE (`DifficultyID`=0 AND `Entry` IN (193061,194195,194159,194142,193994,191179,194174,189881,184394,190295,188280,187290,187130,191982,195051,191980,191176,191027,191025,191013,192625,196774,197956,188107,195050,191174,191012,197166,189261,189260,193077,192305,192096,193987,193988,186692,193991,193995,193737,193983,192674,187071,189448,185904,193920,191893,194099,193979,195052,191126,194474,194478,188029,187073,191894,189262,193097,194479,187072,187955,187060,192512,191954,193955,192284,192498,187058,193757,194076,192491,194818,187292,191031,195125,195120,185490,185489,185496,185484,180377,187392,186146,186917,186143,185485,185464,187295,186918,192013,196827,189637,193304,194821,197211,189136,189814,188074,198034,189812,189815,191765,187394,191656,191653,197732,191796,190660,191768,191892,186795,190269,186828,193791,193790,190090,191891,186822,190013,194314,188667,194820,179965,191886,188666,186829,186823,190080,188372,191904,186833,186836,187406,186825,195915,186834,192182,195917,192181,192058,191823,194524,194523,190211,194525,190155,194517,191016,191797,188698,190151,188699,191975,191917,191517,191983,192136,190093,188297,191945,191944,186683,195672));
INSERT INTO `creature_template_scaling` (`Entry`, `DifficultyID`, `LevelScalingDeltaMin`, `LevelScalingDeltaMax`, `ContentTuningID`, `VerifiedBuild`) VALUES
(193061, 0, 0, 0, 2078, 45505),
(194195, 0, 0, 0, 2151, 45505),
(194159, 0, 0, 0, 2151, 45505),
(194142, 0, 0, 0, 2296, 45505),
(193994, 0, 0, 0, 2296, 45505),
(191179, 0, 0, 0, 2151, 45505),
(194174, 0, 0, 0, 2151, 45505),
(189881, 0, 0, 0, 2151, 45505),
(184394, 0, 0, 0, 2078, 45505),
(190295, 0, 0, 0, 2151, 45505),
(188280, 0, 0, 0, 81, 45505),
(187290, 0, 0, 0, 2151, 45505),
(187130, 0, 0, 0, 2151, 45505),
(191982, 0, 0, 0, 2151, 45505),
(195051, 0, 0, 0, 2151, 45505),
(191980, 0, 0, 0, 2151, 45505),
(191176, 0, 0, 0, 2293, 45505),
(191027, 0, 0, 0, 2296, 45505),
(191025, 0, 0, 0, 2296, 45505),
(191013, 0, 0, 0, 2295, 45505),
(192625, 0, 0, 0, 2456, 45505),
(196774, 0, 0, 0, 2296, 45505),
(197956, 0, 0, 0, 2309, 45505),
(188107, 0, 0, 0, 2078, 45505),
(195050, 0, 0, 0, 2151, 45505),
(191174, 0, 0, 0, 2295, 45505),
(191012, 0, 0, 0, 2295, 45505),
(197166, 0, 0, 0, 2296, 45505),
(189261, 0, 0, 0, 2151, 45505),
(189260, 0, 0, 0, 2151, 45505),
(193077, 0, 0, 0, 2151, 45505),
(192305, 0, 0, 0, 2152, 45505),
(192096, 0, 0, 0, 2151, 45505),
(193987, 0, 0, 0, 2296, 45505),
(193988, 0, 0, 0, 2296, 45505),
(186692, 0, 0, 0, 2151, 45505),
(193991, 0, 0, 0, 2296, 45505),
(193995, 0, 0, 0, 2296, 45505),
(193737, 0, 0, 0, 2151, 45505),
(193983, 0, 0, 0, 2151, 45505),
(192674, 0, 0, 0, 2151, 45505),
(187071, 0, 0, 0, 2456, 45505),
(189448, 0, 0, 0, 2078, 45505),
(185904, 0, 0, 0, 2151, 45505),
(193920, 0, 0, 0, 2151, 45505),
(191893, 0, 0, 0, 2151, 45505),
(194099, 0, 0, 0, 2151, 45505),
(193979, 0, 0, 0, 2151, 45505),
(195052, 0, 0, 0, 2151, 45505),
(191126, 0, 0, 0, 2456, 45505),
(194474, 0, 0, 0, 2296, 45505),
(194478, 0, 0, 0, 2296, 45505),
(188029, 0, 0, 0, 81, 45505),
(187073, 0, 0, 0, 2151, 45505),
(191894, 0, 0, 0, 2151, 45505),
(189262, 0, 0, 0, 2151, 45505),
(193097, 0, 0, 0, 2295, 45505),
(194479, 0, 0, 0, 81, 45505),
(187072, 0, 0, 0, 2456, 45505),
(187955, 0, 0, 0, 2151, 45505),
(187060, 0, 0, 0, 2456, 45505),
(192512, 0, 0, 0, 2151, 45505),
(191954, 0, 0, 0, 2151, 45505),
(193955, 0, 0, 0, 2296, 45505),
(192284, 0, 0, 0, 2078, 45505),
(192498, 0, 0, 0, 2151, 45505),
(187058, 0, 0, 0, 2456, 45505),
(193757, 0, 0, 0, 2151, 45505),
(194076, 0, 0, 0, 2078, 45505),
(192491, 0, 0, 0, 2151, 45505),
(194818, 0, 0, 0, 2078, 45505),
(187292, 0, 0, 0, 2151, 45505),
(191031, 0, 0, 0, 2295, 45505),
(195125, 0, 0, 0, 2151, 45505),
(195120, 0, 0, 0, 2151, 45505),
(185490, 0, 0, 0, 2151, 45505),
(185489, 0, 0, 0, 2151, 45505),
(185496, 0, 0, 0, 2151, 45505),
(185484, 0, 0, 0, 2078, 45505),
(180377, 0, 0, 0, 2078, 45505),
(187392, 0, 0, 0, 2078, 45505),
(186146, 0, 0, 0, 2078, 45505),
(186917, 0, 0, 0, 2151, 45505),
(186143, 0, 0, 0, 2078, 45505),
(185485, 0, 0, 0, 2078, 45505),
(185464, 0, 0, 0, 2078, 45505),
(187295, 0, 0, 0, 2151, 45505),
(186918, 0, 0, 0, 2151, 45505),
(192013, 0, 0, 0, 371, 45505),
(196827, 0, 0, 0, 2527, 45505),
(189637, 0, 0, 0, 81, 45505),
(193304, 0, 0, 0, 2527, 45505),
(194821, 0, 0, 0, 2078, 45505),
(197211, 0, 0, 0, 2527, 45505),
(189136, 0, 0, 0, 371, 45505),
(189814, 0, 0, 0, 2527, 45505),
(188074, 0, 0, 0, 2527, 45505),
(198034, 0, 0, 0, 2151, 45505),
(189812, 0, 0, 0, 2527, 45505),
(189815, 0, 0, 0, 2527, 45505),
(191765, 0, 0, 0, 2078, 45505),
(187394, 0, 0, 0, 2151, 45505),
(191656, 0, 0, 0, 2151, 45505),
(191653, 0, 0, 0, 2151, 45505),
(197732, 0, 0, 0, 2295, 45505),
(191796, 0, 0, 0, 81, 45505),
(190660, 0, 0, 0, 2306, 45505),
(191768, 0, 0, 0, 2151, 45505),
(191892, 0, 0, 0, 2285, 45505),
(186795, 0, 0, 0, 2151, 45505),
(190269, 0, 0, 0, 2285, 45505),
(186828, 0, 0, 0, 2151, 45505),
(193791, 0, 0, 0, 2472, 45505),
(193790, 0, 0, 0, 2472, 45505),
(190090, 0, 0, 0, 2285, 45505),
(191891, 0, 0, 0, 2285, 45505),
(186822, 0, 0, 0, 2151, 45505),
(190013, 0, 0, 0, 2285, 45505),
(194314, 0, 0, 0, 807, 45505),
(188667, 0, 0, 0, 2285, 45505),
(194820, 0, 0, 0, 2078, 45505),
(179965, 0, 0, 0, 2057, 45505),
(191886, 0, 0, 0, 2285, 45505),
(188666, 0, 0, 0, 2285, 45505),
(186829, 0, 0, 0, 2285, 45505),
(186823, 0, 0, 0, 2285, 45505),
(190080, 0, 0, 0, 2285, 45505),
(188372, 0, 0, 0, 2285, 45505),
(191904, 0, 0, 0, 2078, 45505),
(186833, 0, 0, 0, 2285, 45505),
(186836, 0, 0, 0, 2285, 45505),
(187406, 0, 0, 0, 2285, 45505),
(186825, 0, 0, 0, 2285, 45505),
(195915, 0, 0, 0, 2285, 45505),
(186834, 0, 0, 0, 2285, 45505),
(192182, 0, 0, 0, 2151, 45505),
(195917, 0, 0, 0, 2285, 45505),
(192181, 0, 0, 0, 2151, 45505),
(192058, 0, 0, 0, 371, 45505),
(191823, 0, 0, 0, 2151, 45505),
(194524, 0, 0, 0, 2272, 45505),
(194523, 0, 0, 0, 2272, 45505),
(190211, 0, 0, 0, 2285, 45505),
(194525, 0, 0, 0, 2285, 45505),
(190155, 0, 0, 0, 2285, 45505),
(194517, 0, 0, 0, 2272, 45505),
(191016, 0, 0, 0, 2456, 45505),
(191797, 0, 0, 0, 81, 45505),
(188698, 0, 0, 0, 2306, 45505),
(190151, 0, 0, 0, 2151, 45505),
(188699, 0, 0, 0, 2306, 45505),
(191975, 0, 0, 0, 2444, 45505),
(191917, 0, 0, 0, 2444, 45505),
(191517, 0, 0, 0, 2151, 45505),
(191983, 0, 0, 0, 2151, 45505),
(192136, 0, 0, 0, 81, 45505),
(190093, 0, 0, 0, 2151, 45505),
(188297, 0, 0, 0, 2151, 45505),
(191945, 0, 0, 0, 2151, 45505),
(191944, 0, 0, 0, 2444, 45505),
(186683, 0, 0, 0, 2297, 45505),
(195672, 0, 0, 0, 2297, 45505);

UPDATE `creature_template_scaling` SET `VerifiedBuild`=45505 WHERE (`DifficultyID`=0 AND `Entry` IN (192574,192539,192168,191323,192186,191817,191792,142666,142668,189103,192047));

DELETE FROM `creature_model_info` WHERE `DisplayID` IN (108061, 102550, 109830, 102693, 102034, 102803, 102667, 104335, 109779, 102721, 102656, 102646, 109777, 102664, 109850, 109778, 109615, 102676, 102660, 102675, 102708, 102679, 108069, 108070, 102807, 108361, 108362, 108363, 108364, 102666, 102765, 102752, 102750, 102802, 109616, 102348, 102684, 104200, 102762, 108588, 108589, 102674, 102663, 102763, 102695, 105602, 109608, 102768, 102767, 102685, 108383, 102712, 107204, 102779, 107747, 103464, 103415, 105794, 102699, 102751, 103321, 103324, 103413, 106636, 103318, 103279, 103857, 103859, 103281, 107219, 107221, 107222, 104626, 102778, 104625, 104627, 104634, 104631, 107469, 107063, 102966, 102968, 107679, 102892, 102970, 102965, 102967, 102889, 102888, 102886, 108782, 102518, 109447, 102890, 102887, 102893, 107804, 102891, 109446, 107678, 102964, 109030, 104520, 109032, 105443, 106705, 102700, 104536, 105650, 105770, 104537, 104580, 107691, 102517, 104525, 108677, 107528, 102497, 102491, 102587, 102588, 102589, 102739, 102456, 102736, 102478, 102495);
INSERT INTO `creature_model_info` (`DisplayID`, `BoundingRadius`, `CombatReach`, `DisplayID_Other_Gender`, `VerifiedBuild`) VALUES
(108061, 0.305999994277954101, 1.5, 0, 45505),
(102550, 2.65745854377746582, 2.599999904632568359, 0, 45505),
(109830, 1.85866093635559082, 0.899999976158142089, 0, 45505),
(102693, 1.358538508415222167, 1.80000007152557373, 0, 45505),
(102034, 1, 1.5, 0, 45505),
(102803, 1.584961533546447753, 2.099999904632568359, 0, 45505),
(102667, 1.132115364074707031, 1.5, 0, 45505),
(104335, 1.132115364074707031, 1.5, 0, 45505),
(109779, 1.755318164825439453, 1.5, 0, 45505),
(102721, 1.584961533546447753, 2.099999904632568359, 0, 45505),
(102656, 1.132115364074707031, 1.5, 0, 45505),
(102646, 1.132115364074707031, 1.5, 0, 45505),
(109777, 1.755318164825439453, 1.5, 0, 45505),
(102664, 1.343548059463500976, 4.02500009536743164, 0, 45505),
(109850, 0.421299993991851806, 1.65000009536743164, 0, 45505),
(109778, 1.755318164825439453, 1.5, 0, 45505),
(109615, 0.699999988079071044, 14, 0, 45505),
(102676, 1.358538508415222167, 1.80000007152557373, 0, 45505),
(102660, 1.132115364074707031, 1.5, 0, 45505),
(102675, 1.358538508415222167, 1.80000007152557373, 0, 45505),
(102708, 1.584961533546447753, 2.099999904632568359, 0, 45505),
(102679, 1.612257599830627441, 4.829999923706054687, 0, 45505),
(108069, 1.20000004768371582, 1.80000007152557373, 0, 45505),
(108070, 1.20000004768371582, 1.80000007152557373, 0, 45505),
(102807, 1.584961533546447753, 2.099999904632568359, 0, 45505),
(108361, 0.382999986410140991, 1.5, 0, 45505),
(108362, 0.382999986410140991, 1.5, 0, 45505),
(108363, 0.382999986410140991, 1.5, 0, 45505),
(108364, 0.382999986410140991, 1.5, 0, 45505),
(102666, 1.132115364074707031, 1.5, 0, 45505),
(102765, 2.106381893157958984, 1.80000007152557373, 0, 45505),
(102752, 2.106381893157958984, 1.80000007152557373, 0, 45505),
(102750, 2.106381893157958984, 1.80000007152557373, 0, 45505),
(102802, 1.584961533546447753, 2.099999904632568359, 0, 45505),
(109616, 1.584961533546447753, 2.099999904632568359, 0, 45505),
(102348, 1.584961533546447753, 2.099999904632568359, 0, 45505),
(102684, 1.358538508415222167, 1.80000007152557373, 0, 45505),
(104200, 1.132115364074707031, 1.5, 0, 45505),
(102762, 2.106381893157958984, 1.80000007152557373, 0, 45505),
(108588, 0.305999994277954101, 1.5, 0, 45505),
(108589, 0.388999998569488525, 1.5, 0, 45505),
(102674, 1.358538508415222167, 1.80000007152557373, 0, 45505),
(102663, 1.343548059463500976, 4.02500009536743164, 0, 45505),
(102763, 2.106381893157958984, 1.80000007152557373, 0, 45505),
(102695, 1.612257599830627441, 4.829999923706054687, 0, 45505),
(105602, 0.500797629356384277, 1, 0, 45505),
(109608, 1.880967140197753906, 5.634999752044677734, 0, 45505),
(102768, 2.106381893157958984, 1.80000007152557373, 0, 45505),
(102767, 2.106381893157958984, 1.80000007152557373, 0, 45505),
(102685, 1.358538508415222167, 1.80000007152557373, 0, 45505),
(108383, 0.347000002861022949, 1.5, 0, 45505),
(102712, 1.880967140197753906, 5.634999752044677734, 0, 45505),
(107204, 1.10000002384185791, 1.65000009536743164, 0, 45505),
(102779, 0.905692279338836669, 1.20000004768371582, 0, 45505),
(107747, 1, 1.5, 0, 45505),
(103464, 1.98572087287902832, 1.799999952316284179, 0, 45505),
(103415, 1.265631079673767089, 0.900000035762786865, 0, 45505),
(105794, 1.766154885292053222, 3.899999856948852539, 0, 45505),
(102699, 1.358538508415222167, 1.80000007152557373, 0, 45505),
(102751, 2.106381893157958984, 1.80000007152557373, 0, 45505),
(103321, 1.339599251747131347, 1.75, 0, 45505),
(103324, 1.339599251747131347, 1.75, 0, 45505),
(103413, 1.265631079673767089, 0.900000035762786865, 0, 45505),
(106636, 0.160127446055412292, 0, 0, 45505),
(103318, 1.339599251747131347, 1.75, 0, 45505),
(103279, 0.843754053115844726, 0.60000002384185791, 0, 45505),
(103857, 1.339599251747131347, 1.75, 0, 45505),
(103859, 2.105084657669067382, 2.75, 0, 45505),
(103281, 0.843754053115844726, 0.60000002384185791, 0, 45505),
(107219, 0.615700185298919677, 2.40000009536743164, 0, 45505),
(107221, 0.615700185298919677, 2.40000009536743164, 0, 45505),
(107222, 0.615700185298919677, 2.40000009536743164, 0, 45505),
(104626, 1.535885572433471679, 1, 0, 45505),
(102778, 0.905692279338836669, 1.20000004768371582, 0, 45505),
(104625, 1.535885572433471679, 1, 0, 45505),
(104627, 1.535885572433471679, 1, 0, 45505),
(104634, 1.535885572433471679, 1, 0, 45505),
(104631, 1.535885572433471679, 1, 0, 45505),
(107469, 0.722000002861022949, 2, 0, 45505),
(107063, 0.187199994921684265, 1.349999904632568359, 0, 45505),
(102966, 0.347000002861022949, 1.5, 0, 45505),
(102968, 0.305999994277954101, 1.5, 0, 45505),
(107679, 0.80699998140335083, 2.20000004768371582, 0, 45505),
(102892, 0.388999998569488525, 1.5, 0, 45505),
(102970, 0.305999994277954101, 1.5, 0, 45505),
(102965, 0.347000002861022949, 1.5, 0, 45505),
(102967, 0.305999994277954101, 1.5, 0, 45505),
(102889, 0.382999986410140991, 1.5, 0, 45505),
(102888, 0.382999986410140991, 1.5, 0, 45505),
(102886, 0.382999986410140991, 1.5, 0, 45505),
(108782, 1, 1, 0, 45505),
(102518, 2.238852739334106445, 0.60000002384185791, 0, 45505),
(109447, 0.80699998140335083, 2.20000004768371582, 0, 45505),
(102890, 0.305999994277954101, 1.5, 0, 45505),
(102887, 0.382999986410140991, 1.5, 0, 45505),
(102893, 0.388999998569488525, 1.5, 0, 45505),
(107804, 1.808132767677307128, 0, 0, 45505),
(102891, 0.305999994277954101, 1.5, 0, 45505),
(109446, 0.80699998140335083, 2.20000004768371582, 0, 45505),
(107678, 0.80699998140335083, 2.20000004768371582, 0, 45505),
(102964, 0.347000002861022949, 1.5, 0, 45505),
(109030, 0.774999976158142089, 2.5, 0, 45505),
(104520, 0.210000008344650268, 0.300000011920928955, 0, 45505),
(109032, 0.40299999713897705, 1.299999952316284179, 0, 45505),
(105443, 1.01156318187713623, 0, 0, 45505),
(106705, 0.599362134933471679, 0, 0, 45505),
(102700, 1.358538508415222167, 1.80000007152557373, 0, 45505),
(104536, 0.220635652542114257, 0.200000002980232238, 0, 45505),
(105650, 0.995880126953125, 1.5, 0, 45505),
(105770, 0.917803108692169189, 1.5, 0, 45505),
(104537, 0.220635652542114257, 0.200000002980232238, 0, 45505),
(104580, 5.041165828704833984, 9.600000381469726562, 0, 45505),
(107691, 4.450020313262939453, 10.5, 0, 45505),
(102517, 2.238852739334106445, 0.60000002384185791, 0, 45505),
(104525, 0.298513710498809814, 0.080000005662441253, 0, 45505),
(108677, 1.755318164825439453, 1.5, 0, 45505),
(107528, 1.358538508415222167, 1.80000007152557373, 0, 45505),
(102497, 3.367943525314331054, 2.099999904632568359, 0, 45505),
(102491, 3.367943525314331054, 2.099999904632568359, 0, 45505),
(102587, 0.870009303092956542, 0.75, 0, 45505),
(102588, 0.870009303092956542, 0.75, 0, 45505),
(102589, 0.870009303092956542, 0.75, 0, 45505),
(102739, 1.755318164825439453, 1.5, 0, 45505),
(102456, 2.496351242065429687, 2.25, 0, 45505),
(102736, 1.755318164825439453, 1.5, 0, 45505),
(102478, 2.405673980712890625, 1.5, 0, 45505),
(102495, 3.367943525314331054, 2.099999904632568359, 0, 45505);

UPDATE `creature_model_info` SET `BoundingRadius`=0.524999976158142089, `CombatReach`=1.5, `VerifiedBuild`=45505 WHERE `DisplayID`=80466;
UPDATE `creature_model_info` SET `BoundingRadius`=0.224760815501213073, `VerifiedBuild`=45505 WHERE `DisplayID`=104722;
UPDATE `creature_model_info` SET `BoundingRadius`=0.547203779220581054, `CombatReach`=1.5, `VerifiedBuild`=45505 WHERE `DisplayID`=28227;
UPDATE `creature_model_info` SET `BoundingRadius`=1.343548059463500976, `CombatReach`=4.02500009536743164, `VerifiedBuild`=45505 WHERE `DisplayID`=102650;
UPDATE `creature_model_info` SET `VerifiedBuild`=45505 WHERE `DisplayID` IN (103515, 63718, 107950, 107926, 107889, 100702, 102690, 100701, 15481, 102064, 102754, 102524, 102523, 100200, 103326, 104675, 106614, 106820, 103832, 106622, 103370, 78833, 103369, 22468, 78847, 5379, 103368, 28501, 103367, 104531, 104530, 104679, 102643, 22452, 104523, 104169, 104167, 105448, 102972, 104170, 102969, 102971, 107049, 127, 102963, 107050, 104522, 105444, 102449, 100231, 104521, 105445, 104518, 108322, 102564, 102645, 104516, 102647, 82113, 80919, 22469, 103833, 78846, 77687, 77690, 106610, 106708, 106611, 102506, 102593, 104027, 102493, 102586, 102583, 102603, 104026);
UPDATE `creature_model_info` SET `BoundingRadius`=1.535885572433471679, `CombatReach`=1, `VerifiedBuild`=45505 WHERE `DisplayID`=104632;
UPDATE `creature_model_info` SET `BoundingRadius`=1, `CombatReach`=2, `VerifiedBuild`=45505 WHERE `DisplayID`=16946;
UPDATE `creature_model_info` SET `BoundingRadius`=0.995880126953125, `CombatReach`=1.5, `VerifiedBuild`=45505 WHERE `DisplayID`=105656;
UPDATE `creature_model_info` SET `BoundingRadius`=1.492568492889404296, `CombatReach`=0.400000005960464477, `VerifiedBuild`=45505 WHERE `DisplayID`=102505;
UPDATE `creature_model_info` SET `BoundingRadius`=1.483340144157409667, `CombatReach`=3.5, `VerifiedBuild`=45505 WHERE `DisplayID`=106523;
UPDATE `creature_model_info` SET `BoundingRadius`=0.75, `CombatReach`=1.5 WHERE `DisplayID`=27823;

DELETE FROM `npc_vendor` WHERE (`entry`=188107 AND `item`=37460 AND `ExtendedCost`=0 AND `type`=1) OR (`entry`=191954 AND `item`=39505 AND `ExtendedCost`=0 AND `type`=1) OR (`entry`=191954 AND `item`=20815 AND `ExtendedCost`=0 AND `type`=1) OR (`entry`=191954 AND `item`=6532 AND `ExtendedCost`=0 AND `type`=1) OR (`entry`=191954 AND `item`=6530 AND `ExtendedCost`=0 AND `type`=1) OR (`entry`=191954 AND `item`=4400 AND `ExtendedCost`=0 AND `type`=1) OR (`entry`=191954 AND `item`=4399 AND `ExtendedCost`=0 AND `type`=1) OR (`entry`=191954 AND `item`=4289 AND `ExtendedCost`=0 AND `type`=1) OR (`entry`=191954 AND `item`=3371 AND `ExtendedCost`=0 AND `type`=20) OR (`entry`=191954 AND `item`=4340 AND `ExtendedCost`=0 AND `type`=1) OR (`entry`=191954 AND `item`=4342 AND `ExtendedCost`=0 AND `type`=1) OR (`entry`=191954 AND `item`=4341 AND `ExtendedCost`=0 AND `type`=1) OR (`entry`=191954 AND `item`=2325 AND `ExtendedCost`=0 AND `type`=1) OR (`entry`=191954 AND `item`=2604 AND `ExtendedCost`=0 AND `type`=1) OR (`entry`=191954 AND `item`=3857 AND `ExtendedCost`=0 AND `type`=1) OR (`entry`=191954 AND `item`=3466 AND `ExtendedCost`=0 AND `type`=1) OR (`entry`=191954 AND `item`=2880 AND `ExtendedCost`=0 AND `type`=1) OR (`entry`=191954 AND `item`=2678 AND `ExtendedCost`=0 AND `type`=5) OR (`entry`=191954 AND `item`=38426 AND `ExtendedCost`=0 AND `type`=1) OR (`entry`=191954 AND `item`=14341 AND `ExtendedCost`=0 AND `type`=1) OR (`entry`=191954 AND `item`=8343 AND `ExtendedCost`=0 AND `type`=1) OR (`entry`=191954 AND `item`=4291 AND `ExtendedCost`=0 AND `type`=1) OR (`entry`=191954 AND `item`=2321 AND `ExtendedCost`=0 AND `type`=1) OR (`entry`=191954 AND `item`=2320 AND `ExtendedCost`=0 AND `type`=1) OR (`entry`=191954 AND `item`=5956 AND `ExtendedCost`=0 AND `type`=1) OR (`entry`=191954 AND `item`=6217 AND `ExtendedCost`=0 AND `type`=1) OR (`entry`=191954 AND `item`=6256 AND `ExtendedCost`=0 AND `type`=1) OR (`entry`=191954 AND `item`=85663 AND `ExtendedCost`=0 AND `type`=1) OR (`entry`=191954 AND `item`=7005 AND `ExtendedCost`=0 AND `type`=1) OR (`entry`=191954 AND `item`=2901 AND `ExtendedCost`=0 AND `type`=1) OR (`entry`=191954 AND `item`=160059 AND `ExtendedCost`=0 AND `type`=1) OR (`entry`=191954 AND `item`=160298 AND `ExtendedCost`=0 AND `type`=1) OR (`entry`=191954 AND `item`=159959 AND `ExtendedCost`=0 AND `type`=1) OR (`entry`=191954 AND `item`=158205 AND `ExtendedCost`=0 AND `type`=1) OR (`entry`=191954 AND `item`=158186 AND `ExtendedCost`=0 AND `type`=20) OR (`entry`=191954 AND `item`=198487 AND `ExtendedCost`=0 AND `type`=1) OR (`entry`=191954 AND `item`=38682 AND `ExtendedCost`=0 AND `type`=1) OR (`entry`=191954 AND `item`=194784 AND `ExtendedCost`=0 AND `type`=1) OR (`entry`=191954 AND `item`=200860 AND `ExtendedCost`=0 AND `type`=1) OR (`entry`=191954 AND `item`=191474 AND `ExtendedCost`=0 AND `type`=1) OR (`entry`=191954 AND `item`=192833 AND `ExtendedCost`=0 AND `type`=1) OR (`entry`=191954 AND `item`=190452 AND `ExtendedCost`=0 AND `type`=1);
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `ExtendedCost`, `type`, `PlayerConditionID`, `IgnoreFiltering`, `VerifiedBuild`) VALUES
(188107, 1, 37460, 0, 0, 1, 0, 0, 45505), -- Rope Pet Leash
(191954, 41, 39505, 0, 0, 1, 0, 0, 45505), -- Virtuoso Inking Set
(191954, 40, 20815, 0, 0, 1, 0, 0, 45505), -- Jeweler's Kit
(191954, 39, 6532, 0, 0, 1, 0, 0, 45505), -- Bright Baubles
(191954, 38, 6530, 0, 0, 1, 0, 0, 45505), -- Nightcrawlers
(191954, 37, 4400, 0, 0, 1, 0, 0, 45505), -- Heavy Stock
(191954, 36, 4399, 0, 0, 1, 0, 0, 45505), -- Wooden Stock
(191954, 35, 4289, 0, 0, 1, 0, 0, 45505), -- Salt
(191954, 34, 3371, 0, 0, 20, 0, 0, 45505), -- 3371
(191954, 33, 4340, 0, 0, 1, 0, 0, 45505), -- Gray Dye
(191954, 32, 4342, 0, 0, 1, 0, 0, 45505), -- Purple Dye
(191954, 31, 4341, 0, 0, 1, 0, 0, 45505), -- Yellow Dye
(191954, 30, 2325, 0, 0, 1, 0, 0, 45505), -- Black Dye
(191954, 29, 2604, 0, 0, 1, 0, 0, 45505), -- Red Dye
(191954, 28, 3857, 0, 0, 1, 0, 0, 45505), -- Coal
(191954, 27, 3466, 0, 0, 1, 0, 0, 45505), -- Strong Flux
(191954, 26, 2880, 0, 0, 1, 0, 0, 45505), -- Weak Flux
(191954, 25, 2678, 0, 0, 5, 0, 0, 45505), -- 2678
(191954, 24, 38426, 0, 0, 1, 0, 0, 45505), -- Eternium Thread
(191954, 23, 14341, 0, 0, 1, 0, 0, 45505), -- Rune Thread
(191954, 22, 8343, 0, 0, 1, 0, 0, 45505), -- Heavy Silken Thread
(191954, 21, 4291, 0, 0, 1, 0, 0, 45505), -- Silken Thread
(191954, 20, 2321, 0, 0, 1, 0, 0, 45505), -- Fine Thread
(191954, 19, 2320, 0, 0, 1, 0, 0, 45505), -- Coarse Thread
(191954, 18, 5956, 0, 0, 1, 0, 0, 45505), -- Blacksmith Hammer
(191954, 17, 6217, 0, 0, 1, 0, 0, 45505), -- Copper Rod
(191954, 16, 6256, 0, 0, 1, 0, 0, 45505), -- Fishing Pole
(191954, 15, 85663, 0, 0, 1, 0, 0, 45505), -- Herbalist's Spade
(191954, 14, 7005, 0, 0, 1, 0, 0, 45505), -- Skinning Knife
(191954, 13, 2901, 0, 0, 1, 0, 0, 45505), -- Mining Pick
(191954, 12, 160059, 0, 0, 1, 0, 0, 45505), -- -Unknown-
(191954, 11, 160298, 0, 0, 1, 0, 0, 45505), -- -Unknown-
(191954, 10, 159959, 0, 0, 1, 0, 0, 45505), -- -Unknown-
(191954, 9, 158205, 0, 0, 1, 0, 0, 45505), -- -Unknown-
(191954, 8, 158186, 0, 0, 20, 0, 0, 45505), -- 158186
(191954, 7, 198487, 0, 0, 1, 0, 0, 45505), -- -Unknown-
(191954, 6, 38682, 0, 0, 1, 0, 0, 45505), -- Enchanting Vellum
(191954, 5, 194784, 0, 0, 1, 0, 0, 45505), -- -Unknown-
(191954, 4, 200860, 0, 0, 1, 0, 0, 45505), -- -Unknown-
(191954, 3, 191474, 0, 0, 1, 0, 0, 45505), -- -Unknown-
(191954, 2, 192833, 0, 0, 1, 0, 0, 45505), -- -Unknown-
(191954, 1, 190452, 0, 0, 1, 0, 0, 45505); -- -Unknown-


DELETE FROM `gossip_menu_option` WHERE (`MenuID`=28097 AND `OptionID` IN (56083,55225,56084)) OR (`MenuID`=29163 AND `OptionID`=56428) OR (`MenuID`=28120 AND `OptionID`=55289) OR (`MenuID`=28830 AND `OptionID` IN (56114,56115)) OR (`MenuID`=28123 AND `OptionID`=55290) OR (`MenuID`=28091 AND `OptionID`=54867) OR (`MenuID`=27972 AND `OptionID`=55258) OR (`MenuID`=29108 AND `OptionID` IN (56414,56415,56413)) OR (`MenuID`=28826 AND `OptionID` IN (56106,56105)) OR (`MenuID`=29579 AND `OptionID`=106916) OR (`MenuID`=29164 AND `OptionID`=56429) OR (`MenuID`=28825 AND `OptionID` IN (56103,56104)) OR (`MenuID`=27892 AND `OptionID`=55283) OR (`MenuID`=29761 AND `OptionID`=107094) OR (`MenuID`=28410 AND `OptionID` IN (54986,54985)) OR (`MenuID`=28835 AND `OptionID`=56117) OR (`MenuID`=28113 AND `OptionID`=55259) OR (`MenuID`=28118 AND `OptionID`=55288) OR (`MenuID`=28117 AND `OptionID`=54941);
INSERT INTO `gossip_menu_option` (`MenuID`, `OptionID`, `OptionIcon`, `OptionText`, `OptionBroadcastTextId`, `OptionNpcFlag`, `Language`, `ActionMenuID`, `ActionPoiID`, `BoxCoded`, `BoxMoney`, `BoxText`, `BoxBroadcastTextID`, `VerifiedBuild`) VALUES
(28097, 56083, 0, 'Why do the Primalists want dragon eggs?', 0, 1, 0, UNKNOWN, UNKNOWN, 0, 0, NULL, 0, 45505),
(29163, 56428, 0, 'Do you have any spare scraps of fabric?', 0, 1, 0, UNKNOWN, UNKNOWN, 0, 0, NULL, 0, 45505),
(28120, 55289, 0, '|cFF0000FF(Quest)|r Why are there so few eggs here?', 0, 1, 0, UNKNOWN, UNKNOWN, 0, 0, NULL, 0, 45505),
(28830, 56114, 0, 'Alexstrasza talking about oathstones', 0, 1, 0, UNKNOWN, UNKNOWN, 0, 0, NULL, 0, 45505),
(28123, 55290, 0, '|cFF0000FF(Quest)|r How do you care for these eggs?', 0, 1, 0, UNKNOWN, UNKNOWN, 0, 0, NULL, 0, 45505),
(28830, 56115, 0, 'Sendrax spying on the primalists', 0, 1, 0, UNKNOWN, UNKNOWN, 0, 0, NULL, 0, 45505),
(28091, 54867, 0, 'Anything to report?', 0, 1, 0, UNKNOWN, UNKNOWN, 0, 0, NULL, 0, 45505),
(27972, 55258, 0, '|cFF0000FF(Quest)|r Why do you stay here, if you have no eggs to rear?', 0, 1, 0, UNKNOWN, UNKNOWN, 0, 0, NULL, 0, 45505),
(29108, 56414, 0, 'Where can I find scraps of fabric?', 0, 1, 0, UNKNOWN, UNKNOWN, 0, 0, NULL, 0, 45505),
(29108, 56415, 0, 'Where can I find feathers?', 0, 1, 0, UNKNOWN, UNKNOWN, 0, 0, NULL, 0, 45505),
(28826, 56106, 0, 'Who are the Primalists?', 0, 1, 0, UNKNOWN, UNKNOWN, 0, 0, NULL, 0, 45505),
(29579, 106916, 0, 'Why do the djaradin hate dragons?', 0, 1, 0, UNKNOWN, UNKNOWN, 0, 0, NULL, 0, 45505),
(29164, 56429, 0, 'Do you have any spare scraps of fabric?', 0, 1, 0, UNKNOWN, UNKNOWN, 0, 0, NULL, 0, 45505),
(28825, 56103, 0, 'I want to ask about something else.', 149761, 1, 0, UNKNOWN, UNKNOWN, 0, 0, NULL, 0, 45505),
(28826, 56105, 0, 'I want to ask about something else.', 149761, 1, 0, UNKNOWN, UNKNOWN, 0, 0, NULL, 0, 45505),
(27892, 55283, 1, 'I want to browse your goods.', 3370, 128, 0, UNKNOWN, UNKNOWN, 0, 0, NULL, 0, 45505),
(29761, 107094, 0, '<Offer the rescued egg to Queen Alexstrasza.>', 0, 1, 0, UNKNOWN, UNKNOWN, 0, 0, NULL, 0, 45505),
(28410, 54986, 0, 'I\'d like to heal and revive my battle pets.', 64115, 1, 0, UNKNOWN, UNKNOWN, 0, 1000, 'A small fee for supplies is required.', 66369, 45505),
(28835, 56117, 0, 'I want to ask about something else.', 149761, 1, 0, UNKNOWN, UNKNOWN, 0, 0, NULL, 0, 45505),
(28113, 55259, 0, 'I am ready.', 35320, 1, 0, UNKNOWN, UNKNOWN, 0, 0, NULL, 0, 45505), -- OptionBroadcastTextID: 35320 - 35539 - 39152 - 52091 - 52966 - 68157 - 72264 - 98694 - 101165 - 102817 - 104314 - 105294 - 105455 - 105611 - 106714 - 107434 - 108067 - 110410 - 114311 - 115011 - 120845 - 120867 - 120960 - 122483 - 129525 - 130105 - 130536 - 132934 - 134034 - 136601 - 144577 - 152299 - 152826 - 162165 - 163727 - 163987 - 165913 - 169003
(28097, 55225, 0, '|cFF0000FF(Quest)|r What is happening here?', 0, 1, 0, UNKNOWN, UNKNOWN, 0, 0, NULL, 0, 45505),
(29108, 56413, 0, 'Where can I find a bead?', 0, 1, 0, UNKNOWN, UNKNOWN, 0, 0, NULL, 0, 45505),
(28410, 54985, 1, 'I\'m looking for a lost companion.', 56613, 128, 0, UNKNOWN, UNKNOWN, 0, 0, NULL, 0, 45505),
(28118, 55288, 0, '|cFF0000FF(Quest)|r What do you do here?', 0, 1, 0, UNKNOWN, UNKNOWN, 0, 0, NULL, 0, 45505),
(28097, 56084, 0, 'Who are the Primalists?', 0, 1, 0, UNKNOWN, UNKNOWN, 0, 0, NULL, 0, 45505),
(28117, 54941, 0, '|cFF0000FF(Quest)|r Take me with you to see the queen, please.', 0, 1, 0, UNKNOWN, UNKNOWN, 0, 0, NULL, 0, 45505),
(28825, 56104, 0, 'Why do the Primalists want dragon eggs?', 0, 1, 0, UNKNOWN, UNKNOWN, 0, 0, NULL, 0, 45505);


DELETE FROM `creature_template` WHERE `entry` IN (194174 /*Amella*/, 187290 /*Alexstrasza the Life-Binder*/, 197956 /*Injured Shrineguard*/, 187392 /*Tuskarr Pilgrim*/, 186917 /*Turbulent Gust*/, 186918 /*Turbulent Gust*/, 189637 /*Curious Duckling*/, 197211 /*Murghurgl the Invader*/, 189814 /*Cliffdrip Wavemender*/, 188074 /*Agitated Sidewalker*/, 198034 /*Snappy*/, 189812 /*Cliffdrip Snapstrider*/, 189815 /*Cliffdrip Fallstriker*/, 191765 /*Mean Duck*/, 187394 /*Scoutstrasza*/, 197732 /*Ruby Warden*/, 191892 /*Infused Dragon Egg*/, 186795 /*Majordomo Selistra*/, 190269 /*Sendrax*/, 186828 /*Hornswog (0.6/0.6 Melee)*/, 190090 /*Infused Dragon Egg*/, 188667 /*Swelling Fire Elemental*/);
INSERT INTO `creature_template` (`entry`, `gossip_menu_id`, `minlevel`, `maxlevel`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `BaseAttackTime`, `RangeAttackTime`, `unit_flags`, `unit_flags2`, `unit_flags3`, `dynamicflags`, `VehicleId`, `HoverHeight`) VALUES
(194174, 0, 62, 62, 3276, 2, 1, 1.142857193946838378, 2000, UNKNOWN, 33600, 2048, 0, 0, 0, 1), -- Amella
(187290, 0, 62, 62, 3276, 3, 1, 1.142857193946838378, 2000, UNKNOWN, 32768, 2048, 0, 0, 0, 1), -- Alexstrasza the Life-Binder
(197956, 0, 62, 62, 3276, 0, 1, 1.142857193946838378, 2000, UNKNOWN, 33536, 2048, 0, 0, 0, 1), -- Injured Shrineguard
(187392, 0, 70, 70, 35, 0, 1, 1.142857193946838378, 2000, UNKNOWN, 32768, 2048, 0, 0, 0, 1), -- Tuskarr Pilgrim
(186917, 0, 62, 62, 3305, 0, 1, 1.142857193946838378, 2000, UNKNOWN, 32768, 2048, 0, 0, 0, 1), -- Turbulent Gust
(186918, 0, 62, 62, 3305, 0, 1, 1.142857193946838378, 2000, UNKNOWN, 32768, 2048, 0, 0, 0, 1), -- Turbulent Gust
(189637, 0, 1, 1, 188, 0, 1, 1.142857193946838378, 2000, UNKNOWN, 32768, 2048, 0, 0, 0, 1), -- Curious Duckling
(197211, 0, 62, 62, 16, 0, 1, 1.142857193946838378, 2000, UNKNOWN, 32832, 2048, 0, 0, 0, 1), -- Murghurgl the Invader
(189814, 0, 62, 62, 16, 0, 1, 1.142857193946838378, 2000, UNKNOWN, 32768, 2048, 0, 0, 0, 1), -- Cliffdrip Wavemender
(188074, 0, 62, 62, 35, 0, 1, 1.142857193946838378, 2000, UNKNOWN, 32768, 16779264, 0, 0, 0, 1), -- Agitated Sidewalker
(198034, 0, 62, 62, 16, 0, 1, 1.142857193946838378, 2000, UNKNOWN, 32768, 2048, 0, 0, 8005, 1), -- Snappy
(189812, 0, 62, 62, 16, 0, 1, 1.142857193946838378, 2000, UNKNOWN, 32768, 2048, 0, 0, 0, 1), -- Cliffdrip Snapstrider
(189815, 0, 62, 62, 16, 0, 1, 1.142857193946838378, 2000, UNKNOWN, 32768, 2048, 0, 0, 0, 1), -- Cliffdrip Fallstriker
(191765, 0, 70, 70, 35, 0, 1, 1.142857193946838378, 2000, UNKNOWN, 32768, 2048, 0, 0, 0, 1.20000004768371582), -- Mean Duck
(187394, 0, 62, 62, 3276, 2, 1, 1.142857193946838378, 2000, UNKNOWN, 32832, 2048, 0, 0, 0, 1), -- Scoutstrasza
(197732, 0, 62, 62, 3277, 0, 1, 1.142857193946838378, 2000, UNKNOWN, 32832, 2048, 0, 0, 0, 1), -- Ruby Warden
(191892, 0, 62, 62, 3276, 0, 1, 1.142857193946838378, 2000, UNKNOWN, 33555200, 67110912, 0, 0, 0, 1), -- Infused Dragon Egg
(186795, 0, 62, 62, 3276, 1, 1, 1, 2000, UNKNOWN, 33600, 2048, 0, 0, 0, 1), -- Majordomo Selistra
(190269, 0, 62, 62, 3276, 0, 1, 1.142857193946838378, 2000, UNKNOWN, 33600, 2048, 0, 0, 0, 1), -- Sendrax
(186828, 0, 62, 62, 16, 0, 1, 1.142857193946838378, 2000, UNKNOWN, 32768, 2048, 0, 0, 0, 1), -- Hornswog (0.6/0.6 Melee)
(190090, 0, 62, 62, 3276, 16777216, 1, 1, 2000, UNKNOWN, 768, 67110912, 0, 0, 0, 1), -- Infused Dragon Egg
(188667, 0, 62, 62, 3320, 0, 0.699999988079071044, 0.800000011920928955, 2000, UNKNOWN, 32832, 2048, 0, 0, 0, 1); -- Swelling Fire Elemental


UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70, `faction`=3276, `speed_run`=1, `BaseAttackTime`=2000, `unit_flags`=33536, `unit_flags2`=2048 WHERE `entry`=193061; -- Danastra
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=190, `speed_walk`=0.5, `speed_run`=0.571428596973419189, `BaseAttackTime`=2000, `unit_flags`=256, `unit_flags2`=34816, `unit_flags3`=16777216 WHERE `entry`=194195; -- Lifeshrine Door
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=190, `speed_run`=1.428571462631225585, `BaseAttackTime`=1667, `unit_flags`=32768, `unit_flags2`=2048 WHERE `entry`=194159; -- Relentless Gust
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=190, `BaseAttackTime`=2000, `unit_flags`=32768, `unit_flags2`=2048 WHERE `entry`=194142; -- Intrusive Pupstinger
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=190, `BaseAttackTime`=2000, `unit_flags`=32768, `unit_flags2`=2048 WHERE `entry`=193994; -- Agitated Weedling
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=35, `BaseAttackTime`=2000, `unit_flags`=512, `unit_flags2`=34816, `unit_flags3`=16777216 WHERE `entry`=191179; -- Target Bunny
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=35, `BaseAttackTime`=2000, `unit_flags`=33554432, `unit_flags2`=100665344 WHERE `entry`=189881; -- Elemental Target [DNT]
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70, `faction`=35, `npcflag`=8192, `BaseAttackTime`=2000, `unit_flags`=33536, `unit_flags2`=2048 WHERE `entry`=184394; -- Agorithos 0
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3276, `BaseAttackTime`=2000, `unit_flags`=33554432, `unit_flags2`=100665344 WHERE `entry`=190295; -- Akxall
UPDATE `creature_template` SET `faction`=190, `BaseAttackTime`=2000, `unit_flags`=32768, `unit_flags2`=2048 WHERE `entry`=188280; -- Excited Vorquin
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3276, `npcflag`=1, `BaseAttackTime`=2000, `unit_flags`=33600, `unit_flags2`=2048 WHERE `entry`=187130; -- Amella
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3276, `BaseAttackTime`=2000, `unit_flags`=32768, `unit_flags2`=2048 WHERE `entry`=191982; -- Faramin
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3276, `BaseAttackTime`=2000, `unit_flags`=32832, `unit_flags2`=2048 WHERE `entry`=195051; -- Azure Tender
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3276, `BaseAttackTime`=2000, `unit_flags`=32768, `unit_flags2`=2048 WHERE `entry`=191980; -- Xolleth
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3276, `npcflag`=2, `BaseAttackTime`=2000, `unit_flags`=33536, `unit_flags2`=2048 WHERE `entry`=191176; -- Dazakros
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3276, `npcflag`=2, `BaseAttackTime`=2000, `unit_flags`=33536, `unit_flags2`=2048 WHERE `entry`=191027; -- Lasztak
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3276, `npcflag`=3, `BaseAttackTime`=2000, `unit_flags`=33536, `unit_flags2`=2048 WHERE `entry`=191025; -- Lifecaller Tzadrak
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3276, `npcflag`=2, `BaseAttackTime`=2000, `unit_flags`=33536, `unit_flags2`=2048 WHERE `entry`=191013; -- Keshki
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70, `faction`=3277, `BaseAttackTime`=2000, `unit_flags`=32832, `unit_flags2`=2048, `unit_flags3`=8388608 WHERE `entry`=192625; -- Ruby Groundskeeper
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3276, `BaseAttackTime`=2000, `unit_flags`=33280, `unit_flags2`=2048 WHERE `entry`=196774; -- Zoristrasz
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70, `faction`=3276, `npcflag`=129, `BaseAttackTime`=2000, `unit_flags`=32832, `unit_flags2`=2048, `HoverHeight`=7 WHERE `entry`=188107; -- Tionistrasz
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3276, `BaseAttackTime`=2000, `unit_flags`=32832, `unit_flags2`=2048 WHERE `entry`=195050; -- Bronze Tender
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3276, `npcflag`=2, `BaseAttackTime`=2000, `unit_flags`=33536, `unit_flags2`=2048 WHERE `entry`=191174; -- Vaeros
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3276, `npcflag`=2, `BaseAttackTime`=2000, `unit_flags`=33536, `unit_flags2`=2048 WHERE `entry`=191012; -- Akora
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3276, `BaseAttackTime`=2000, `unit_flags`=33536, `unit_flags2`=2048 WHERE `entry`=197166; -- Dragonspawn Apprentice
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3276, `npcflag`=1, `BaseAttackTime`=2000, `unit_flags`=33600, `unit_flags2`=2048, `dynamicflags`=128 WHERE `entry`=189261; -- Xius
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3276, `npcflag`=3, `BaseAttackTime`=2000, `unit_flags`=33600, `unit_flags2`=2048 WHERE `entry`=189260; -- Zahkrana
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3276, `speed_run`=1, `BaseAttackTime`=2000, `unit_flags`=33536, `unit_flags2`=2048, `unit_flags3`=16777216 WHERE `entry`=193077; -- Ruby Percher
UPDATE `creature_template` SET `minlevel`=65, `maxlevel`=65, `faction`=2028, `BaseAttackTime`=2000, `unit_flags`=32768, `unit_flags2`=2048 WHERE `entry`=192305; -- Boots
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3276, `BaseAttackTime`=2000, `unit_flags`=33536, `unit_flags2`=2048 WHERE `entry`=192096; -- Ruby Dozer
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3276, `npcflag`=1, `BaseAttackTime`=2000, `unit_flags`=33536, `unit_flags2`=2048 WHERE `entry`=193987; -- Valdestrasz
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3276, `npcflag`=1, `BaseAttackTime`=2000, `unit_flags`=33536, `unit_flags2`=2048 WHERE `entry`=193988; -- Andustrasza
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3276, `BaseAttackTime`=2000, `unit_flags`=33536, `unit_flags2`=2048 WHERE `entry`=186692; -- Ruby Swarmer
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3276, `npcflag`=1, `BaseAttackTime`=2000, `unit_flags`=33536, `unit_flags2`=2048 WHERE `entry`=193991; -- Lyrastrasz
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3276, `npcflag`=1, `BaseAttackTime`=2000, `unit_flags`=33536, `unit_flags2`=2048 WHERE `entry`=193995; -- Rathestrasz
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3277, `BaseAttackTime`=2000, `unit_flags`=32832, `unit_flags2`=2048 WHERE `entry`=193737; -- Ruby Tender
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3276, `BaseAttackTime`=2000, `unit_flags`=33280, `unit_flags2`=2048 WHERE `entry`=193983; -- Boisterous Instigator
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=2028, `npcflag`=3, `BaseAttackTime`=2000, `unit_flags`=33536, `unit_flags2`=2048 WHERE `entry`=192674; -- Mahra Treebender
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70, `faction`=3277, `BaseAttackTime`=2000, `unit_flags`=32832, `unit_flags2`=2048, `unit_flags3`=8388608 WHERE `entry`=187071; -- Nurse Sentry
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70, `faction`=3276, `npcflag`=129, `BaseAttackTime`=2000, `unit_flags`=32832, `unit_flags2`=34816 WHERE `entry`=189448; -- Trellain
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3276, `npcflag`=3, `BaseAttackTime`=2000, `unit_flags`=33600, `unit_flags2`=2048 WHERE `entry`=185904; -- Mother Elion
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3277, `npcflag`=1, `BaseAttackTime`=2000, `unit_flags`=32768, `unit_flags2`=2048 WHERE `entry`=193920; -- Kahtzar
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3276, `npcflag`=83, `BaseAttackTime`=2000, `unit_flags`=32768, `unit_flags2`=2048 WHERE `entry`=191893; -- Zherrak
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3276, `npcflag`=1, `speed_run`=1, `BaseAttackTime`=2000, `unit_flags`=33600, `unit_flags2`=2048, `VehicleId`=7779 WHERE `entry`=194099; -- Urlostrasz
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=35, `npcflag`=16777216, `speed_walk`=1.60000002384185791, `BaseAttackTime`=2000, `unit_flags2`=2048, `VehicleId`=7745 WHERE `entry`=193979; -- Ruby Whelpling
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3276, `BaseAttackTime`=2000, `unit_flags`=32832, `unit_flags2`=2048 WHERE `entry`=195052; -- Sapphire Tender
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70, `faction`=3276, `BaseAttackTime`=2000, `unit_flags`=32832, `unit_flags2`=2048 WHERE `entry`=191126; -- Ruby Shrineguard
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3276, `npcflag`=1, `BaseAttackTime`=2000, `unit_flags`=32768, `unit_flags2`=2048 WHERE `entry`=194474; -- Zhustostrasza
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3276, `npcflag`=1, `BaseAttackTime`=2000, `unit_flags`=32768, `unit_flags2`=2048 WHERE `entry`=194478; -- Clokkistrasz
UPDATE `creature_template` SET `faction`=188, `speed_walk`=0.400000005960464477, `speed_run`=0.285714298486709594, `BaseAttackTime`=2000, `unit_flags`=32768, `unit_flags2`=2048 WHERE `entry`=188029; -- Sprightly Butterfly
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3277, `BaseAttackTime`=2000, `unit_flags`=32832, `unit_flags2`=2048 WHERE `entry`=187073; -- Ruby Sitter
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3276, `npcflag`=83, `BaseAttackTime`=2000, `unit_flags`=32768, `unit_flags2`=2048 WHERE `entry`=191894; -- Krillonn
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3276, `npcflag`=1, `BaseAttackTime`=2000, `unit_flags`=33600, `unit_flags2`=2048, `dynamicflags`=128 WHERE `entry`=189262; -- Akxall
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=35, `BaseAttackTime`=2000, `unit_flags`=32768, `unit_flags2`=2048 WHERE `entry`=193097; -- Peaceful Duck
UPDATE `creature_template` SET `faction`=188, `speed_walk`=0.400000005960464477, `speed_run`=0.285714298486709594, `BaseAttackTime`=2000, `unit_flags`=32768, `unit_flags2`=2048, `unit_flags3`=16777216 WHERE `entry`=194479; -- Sprightly Butterfly
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70, `faction`=3277, `BaseAttackTime`=2000, `unit_flags`=32832, `unit_flags2`=2048 WHERE `entry`=187072; -- Ruby Shrineguard
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3276, `npcflag`=4225, `BaseAttackTime`=2000, `unit_flags`=32832, `unit_flags2`=2048 WHERE `entry`=187955; -- Krendisc
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70, `faction`=3277, `speed_run`=1.428571462631225585, `BaseAttackTime`=2000, `unit_flags`=32832, `unit_flags2`=2048, `unit_flags3`=8388608 WHERE `entry`=187060; -- Ruby Keeper
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3276, `BaseAttackTime`=2000, `unit_flags`=33280, `unit_flags2`=2048 WHERE `entry`=192512; -- Boisterous Child
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3276, `npcflag`=128, `BaseAttackTime`=2000, `unit_flags`=33536, `unit_flags2`=2048 WHERE `entry`=191954; -- Kskeiton
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3276, `npcflag`=2, `BaseAttackTime`=2000, `unit_flags`=33536, `unit_flags2`=2048 WHERE `entry`=193955; -- Lillistrazsa
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70, `faction`=3276, `BaseAttackTime`=2000, `unit_flags`=33536, `unit_flags2`=2048 WHERE `entry`=192284; -- Kandrostrasz
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=2028, `npcflag`=3, `BaseAttackTime`=2000, `unit_flags`=33536, `unit_flags2`=2048 WHERE `entry`=192498; -- Haephesta
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70, `faction`=3272, `BaseAttackTime`=2000, `unit_flags`=32832, `unit_flags2`=2048, `unit_flags3`=8388608 WHERE `entry`=187058; -- Ruby Scaleguard
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=2028, `BaseAttackTime`=2000, `unit_flags`=32768, `unit_flags2`=2048 WHERE `entry`=193757; -- Tzurok
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70, `faction`=3276, `npcflag`=3, `BaseAttackTime`=2000, `unit_flags`=33600, `unit_flags2`=2048 WHERE `entry`=194076; -- Veritistrasz
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3276, `npcflag`=8193, `BaseAttackTime`=2000, `unit_flags`=32768, `unit_flags2`=2048 WHERE `entry`=192491; -- Vaknai
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70, `faction`=35, `BaseAttackTime`=2000, `unit_flags`=33555200, `unit_flags2`=73402368, `unit_flags3`=16777216 WHERE `entry` IN (194818, 194821, 194820); -- Dragon Glyph
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3276, `npcflag`=1, `speed_run`=1, `BaseAttackTime`=2000, `unit_flags`=33600, `unit_flags2`=2048, `VehicleId`=7779 WHERE `entry`=187292; -- Holthkastrasz
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3276, `BaseAttackTime`=2000, `unit_flags`=32768, `unit_flags2`=2048 WHERE `entry`=191031; -- Ruby Tender
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3276, `speed_run`=1, `BaseAttackTime`=2000, `unit_flags`=33536, `unit_flags2`=2099200 WHERE `entry`=195125; -- Ruby Skyguard
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3276, `speed_run`=1, `BaseAttackTime`=2000, `unit_flags`=33536, `unit_flags2`=4196352 WHERE `entry`=195120; -- Ruby Skyguard
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=16, `BaseAttackTime`=2000, `unit_flags`=32768, `unit_flags2`=2048, `VehicleId`=7710 WHERE `entry`=185490; -- Entranced Water Elemental
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=16, `BaseAttackTime`=2000, `unit_flags`=32832, `unit_flags2`=2048 WHERE `entry`=185489; -- King Drippy
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=190, `BaseAttackTime`=2000, `unit_flags`=32768, `unit_flags2`=2048 WHERE `entry`=185496; -- Primal Dropling
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70, `faction`=35, `speed_run`=1, `BaseAttackTime`=2000, `unit_flags`=768, `unit_flags2`=67143680, `unit_flags3`=16777216, `VehicleId`=7559 WHERE `entry` IN (185484, 180377, 186146, 186143, 185464); -- Handhold
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70, `faction`=35, `speed_run`=1, `BaseAttackTime`=2000, `unit_flags`=768, `unit_flags2`=67143680, `unit_flags3`=16777216, `VehicleId`=7560 WHERE `entry`=185485; -- Handhold
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=1665, `BaseAttackTime`=2000, `unit_flags`=32832, `unit_flags2`=2048, `VehicleId`=7756 WHERE `entry`=187295; -- Borrowed Otter Mount
UPDATE `creature_template` SET `faction`=188, `speed_walk`=0.400000005960464477, `speed_run`=0.285714298486709594, `BaseAttackTime`=2000, `unit_flags`=33280, `unit_flags2`=2048 WHERE `entry`=192013; -- Wild Duckling
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3276, `npcflag`=3, `BaseAttackTime`=2000, `unit_flags`=32768, `unit_flags2`=2048 WHERE `entry`=196827; -- Crabtender Kad'irsza
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3276, `npcflag`=2, `BaseAttackTime`=2000, `unit_flags`=33536, `unit_flags2`=2048 WHERE `entry`=193304; -- Ru'kroszk
UPDATE `creature_template` SET `faction`=188, `npcflag`=1073741824, `speed_walk`=0.400000005960464477, `speed_run`=0.285714298486709594, `BaseAttackTime`=2000, `unit_flags`=33280, `unit_flags2`=2048 WHERE `entry`=189136; -- Wild Duckling
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=190, `BaseAttackTime`=2000, `unit_flags`=32768, `unit_flags2`=2048 WHERE `entry`=191656; -- Young Salamanther
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=16, `BaseAttackTime`=2000, `unit_flags`=32768, `unit_flags2`=2048 WHERE `entry`=191653; -- Coastal Salamanther
UPDATE `creature_template` SET `faction`=188, `BaseAttackTime`=2000, `unit_flags`=32768, `unit_flags2`=2048 WHERE `entry`=191796; -- Tiny Drop
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=2136, `BaseAttackTime`=2000, `unit_flags`=32768, `unit_flags2`=2048 WHERE `entry`=190660; -- Cautious Duck
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3276, `speed_run`=1, `BaseAttackTime`=2000, `unit_flags`=33600, `unit_flags2`=2048, `VehicleId`=7790 WHERE `entry`=191768; -- Majordomo Selistra
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=14, `BaseAttackTime`=2000, `unit_flags2`=2048 WHERE `entry`=193791; -- Sundered Mercenary
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=14, `BaseAttackTime`=2000, `unit_flags2`=2048 WHERE `entry`=193790; -- Sundered Supplyhand
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3276, `BaseAttackTime`=2000, `unit_flags`=33600, `unit_flags2`=2048 WHERE `entry`=191891; -- Sendrax
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=14, `BaseAttackTime`=2000, `unit_flags`=32768, `unit_flags2`=2048 WHERE `entry`=186822; -- Infused Ruby Whelpling
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3276, `speed_run`=1, `BaseAttackTime`=2000, `unit_flags`=768, `unit_flags2`=67110912 WHERE `entry`=190013; -- Ruby Dragon Egg
UPDATE `creature_template` SET `minlevel`=60, `maxlevel`=60, `faction`=35, `npcflag`=1, `BaseAttackTime`=2000, `unit_flags`=33536, `unit_flags2`=2048 WHERE `entry`=194314; -- Captain Exposition
UPDATE `creature_template` SET `minlevel`=60, `maxlevel`=60, `faction`=35, `BaseAttackTime`=2000, `unit_flags`=33554432, `unit_flags2`=100665344 WHERE `entry`=179965; -- Generic Bunny
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=14, `speed_run`=1, `BaseAttackTime`=2000, `unit_flags`=768, `unit_flags2`=67143680, `unit_flags3`=16777216 WHERE `entry`=191886; -- Primalist Lava Conduit
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3320, `BaseAttackTime`=2000, `unit_flags`=32768, `unit_flags2`=2048 WHERE `entry`=188666; -- Unleashed Lavaburst
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=190, `speed_walk`=1.399999976158142089, `speed_run`=0.5, `BaseAttackTime`=2000, `unit_flags`=32768, `unit_flags2`=16779264 WHERE `entry`=186829; -- Spiteful Slug
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3320, `BaseAttackTime`=2000, `unit_flags`=32784, `unit_flags2`=2048 WHERE `entry`=186823; -- Lavacaller Primalist
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3320, `BaseAttackTime`=2000, `unit_flags`=32768, `unit_flags2`=2048 WHERE `entry`=190080; -- Tarasek Elementalist
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3320, `BaseAttackTime`=2000, `unit_flags`=32768, `unit_flags2`=2048 WHERE `entry`=188372; -- Primal Tarasek
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70, `faction`=35, `BaseAttackTime`=2000, `unit_flags`=33555200, `unit_flags2`=100665344, `unit_flags3`=1 WHERE `entry`=191904; -- Ruby Dragon Eggs
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=190, `speed_run`=0.357142865657806396, `BaseAttackTime`=2000, `unit_flags`=32768, `unit_flags2`=16779264 WHERE `entry`=186833; -- Spiteful Snail
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=14, `speed_run`=1, `BaseAttackTime`=2000, `unit_flags`=32832, `unit_flags2`=2048 WHERE `entry`=186836; -- Lava Burster
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3276, `npcflag`=3, `BaseAttackTime`=2000, `unit_flags`=33600, `unit_flags2`=2048 WHERE `entry`=187406; -- Sendrax
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3320, `BaseAttackTime`=2000, `unit_flags`=32768, `unit_flags2`=2048 WHERE `entry`=186825; -- Molten Primalist
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3331, `BaseAttackTime`=2000, `unit_flags`=64, `unit_flags2`=2048 WHERE `entry`=195915; -- Firava the Rekindler
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=190, `BaseAttackTime`=2000, `unit_flags`=32832, `unit_flags2`=2048 WHERE `entry`=186834; -- Stubborn Hornswog
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=16, `speed_run`=0.992062866687774658, `BaseAttackTime`=2000, `unit_flags`=32832, `unit_flags2`=2048 WHERE `entry`=192182; -- Rockfang Hunter
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3331, `BaseAttackTime`=2000, `unit_flags`=32832, `unit_flags2`=2048 WHERE `entry`=195917; -- Primal Revenant
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=190, `speed_run`=0.992062866687774658, `BaseAttackTime`=2000, `unit_flags`=32832, `unit_flags2`=2048 WHERE `entry`=192181; -- Wild Rockfang
UPDATE `creature_template` SET `faction`=188, `speed_run`=0.857142865657806396, `BaseAttackTime`=2000, `unit_flags`=33280, `unit_flags2`=2048 WHERE `entry`=192058; -- Igneoid
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=16, `speed_run`=1, `BaseAttackTime`=2000, `unit_flags`=32768, `unit_flags2`=2048 WHERE `entry`=191823; -- Vicious Proto-Drake
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3306, `BaseAttackTime`=2000, `unit_flags`=32832, `unit_flags2`=2048 WHERE `entry`=194524; -- Earthshatter Elemental
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=16, `BaseAttackTime`=2000, `unit_flags`=32768, `unit_flags2`=2048 WHERE `entry`=194523; -- Raging Elemental
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=35, `BaseAttackTime`=2000, `unit_flags`=33555200, `unit_flags2`=2048, `unit_flags3`=16777216 WHERE `entry`=190211; -- Egg Returned to Safety Kill Credit [DNT]
UPDATE `creature_template` SET `unit_flags`=32768, `dynamicflags`=0 WHERE `entry`=191554; -- Argali Lamb
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3276, `npcflag`=3, `BaseAttackTime`=2000, `unit_flags`=33600, `unit_flags2`=2048 WHERE `entry`=194525; -- Apprentice Caretaker Zefren
UPDATE `creature_template` SET `unit_flags3`=0, `dynamicflags`=64 WHERE `entry`=191553; -- Wild Argali
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3276, `npcflag`=3, `BaseAttackTime`=2000, `unit_flags`=33600, `unit_flags2`=2048 WHERE `entry`=190155; -- Caretaker Azkra
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=16, `BaseAttackTime`=2000, `unit_flags`=32768, `unit_flags2`=2048 WHERE `entry`=194517; -- Crushing Elemental
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70, `faction`=1971, `speed_run`=1.428571462631225585, `BaseAttackTime`=2000, `unit_flags`=32768, `unit_flags2`=2048, `unit_flags3`=8388608 WHERE `entry`=191016; -- Uktulut Protector
UPDATE `creature_template` SET `faction`=188, `BaseAttackTime`=2000, `unit_flags`=32768, `unit_flags2`=2048 WHERE `entry`=191797; -- Steam Drip
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=16, `BaseAttackTime`=2000, `unit_flags`=32768, `unit_flags2`=2048 WHERE `entry`=188698; -- Dreadsquall Feaster
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3277, `npcflag`=1, `BaseAttackTime`=2000, `unit_flags`=32832, `unit_flags2`=2048 WHERE `entry`=190151; -- Ruby Culler
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=14, `BaseAttackTime`=2000, `unit_flags`=32768, `unit_flags2`=2048 WHERE `entry`=188699; -- Carrion Phoenix
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=35, `BaseAttackTime`=2000, `unit_flags`=33600 WHERE `entry`=191975; -- Rocan the Mountain
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3307, `BaseAttackTime`=2000, `unit_flags`=32832, `unit_flags2`=2048 WHERE `entry`=191917; -- Erupting Magma
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3310, `BaseAttackTime`=2000, `unit_flags`=32768, `unit_flags2`=16779264 WHERE `entry`=191517; -- Erupting Droplet
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3307, `BaseAttackTime`=2000, `unit_flags`=32768, `unit_flags2`=16779264 WHERE `entry`=191983; -- Erupting Droplet
UPDATE `creature_template` SET `faction`=188, `BaseAttackTime`=2000, `unit_flags`=32768, `unit_flags2`=2048 WHERE `entry`=192136; -- Flame Flick
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3278, `npcflag`=1, `BaseAttackTime`=2000, `unit_flags`=32768, `unit_flags2`=2048, `unit_flags3`=1048576 WHERE `entry`=190093; -- Ruby Culler
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3278, `npcflag`=2, `BaseAttackTime`=2000, `unit_flags`=33536, `unit_flags2`=2048 WHERE `entry`=188297; -- Caretaker Ventraz
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3309, `BaseAttackTime`=2000, `unit_flags`=536904448, `unit_flags2`=2049, `unit_flags3`=8192 WHERE `entry`=191945; -- Cracked Elemental
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3307, `BaseAttackTime`=2000, `unit_flags`=32768, `unit_flags2`=2048 WHERE `entry`=191944; -- Erupting Lasher
UPDATE `creature_template` SET `minlevel`=70, `maxlevel`=70, `faction`=3295, `BaseAttackTime`=2000, `unit_flags`=32832, `unit_flags2`=2048 WHERE `entry`=191899; -- Qalashi Marauder
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3309, `BaseAttackTime`=2000, `unit_flags`=32768, `unit_flags2`=2048 WHERE `entry`=186683; -- Restless Rocks
UPDATE `creature_template` SET `unit_flags`=32832 WHERE `entry`=186728; -- Magmammoth Bull
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3295, `BaseAttackTime`=2000, `unit_flags`=32832, `unit_flags2`=2048 WHERE `entry`=195672; -- Qalashi Scoundrel
UPDATE `creature_template` SET `dynamicflags`=128 WHERE `entry`=186777; -- Meatgrinder Sotok
UPDATE `creature_template` SET `npcflag`=16777216, `dynamicflags`=0 WHERE `entry`=190771; -- Injured Ruby Culler
UPDATE `creature_template` SET `minlevel`=62, `maxlevel`=62, `faction`=3295, `BaseAttackTime`=2000, `unit_flags`=32832, `unit_flags2`=2048 WHERE `entry`=194222; -- Qalashi Flamemuzzler
UPDATE `creature_template` SET `speed_run`=1.142857193946838378 WHERE `entry`=194772; -- Wrathion
UPDATE `creature_template` SET `speed_run`=1 WHERE `entry`=186767; -- Majordomo Selistra
UPDATE `creature_template` SET `unit_flags`=67141632, `dynamicflags`=64 WHERE `entry`=186684; -- Lava Phoenix
UPDATE `creature_template` SET `unit_flags`=67108864, `dynamicflags`=64 WHERE `entry`=180705; -- Magmammoth Calf
UPDATE `creature_template` SET `dynamicflags`=64 WHERE `entry`=191637; -- Lava Phoenix

SET @GROUP_ID = 0;
SET @ID = 0;
replace INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) VALUES
(186823, @GROUP_ID+0, @ID, 'Elements take you!', 12, 0, 100, 0, 0, 0, UNKNOWN, 0, 'Lavacaller Primalist to Player'),
(186823, @GROUP_ID+1, @ID, 'We shall return this world to its origins!', 12, 0, 100, 0, 0, 0, UNKNOWN, 0, 'Lavacaller Primalist to Player'),
(186823, @GROUP_ID+2, @ID, 'We will... retake... Azeroth...', 12, 0, 100, 0, 0, 0, UNKNOWN, 0, 'Lavacaller Primalist to Player'),
(186823, @GROUP_ID+3, @ID, 'Kyrakka... cannot be... stopped...', 12, 0, 100, 0, 0, 0, UNKNOWN, 0, 'Lavacaller Primalist to Player'),
(186823, @GROUP_ID+4, @ID, 'Twisted by the Titan\'s lies!', 12, 0, 100, 0, 0, 0, UNKNOWN, 0, 'Lavacaller Primalist to Player'),
(186823, @GROUP_ID+5, @ID, 'This world will be remade.', 12, 0, 100, 0, 0, 0, UNKNOWN, 0, 'Lavacaller Primalist to Player'),
(186825, @GROUP_ID+0, @ID, 'As it was before, so it will be again!', 12, 0, 100, 0, 0, 0, UNKNOWN, 0, 'Molten Primalist to Player'),
(186825, @GROUP_ID+1, @ID, 'First the eggs, then the Aspects!', 12, 0, 100, 0, 0, 0, UNKNOWN, 0, 'Molten Primalist to Sendrax'),
(190080, @GROUP_ID+0, @ID, 'For Kyrakka!', 12, 0, 100, 479, 0, 0, UNKNOWN, 0, 'Tarasek Elementalist to Player'),
(190155, @GROUP_ID+0, @ID, 'Are you looking for the young cadet, Sendrax? She hasn\'t returned yet.', 12, 0, 100, 1, 0, 0, UNKNOWN, 0, 'Caretaker Azkra to Player'),
(190771, @GROUP_ID+0, @ID, 'My life for the Life-Binder!', 12, 0, 100, 66, 0, 0, UNKNOWN, 0, 'Injured Ruby Culler to Player'),
(190771, @GROUP_ID+1, @ID, 'Thank you for your aid.', 12, 0, 100, 66, 0, 0, 99385, 0, 'Injured Ruby Culler to Player'),
(190771, @GROUP_ID+2, @ID, 'Is the Outpost safe? We must strike back!', 12, 0, 100, 1, 0, 0, UNKNOWN, 0, 'Injured Ruby Culler to Player'),
(194174, @GROUP_ID+0, @ID, 'What do you mean, \'the whelplings do not want to fly\'? This should be second nature to them!', 12, 0, 100, 1, 0, 205094, UNKNOWN, 0, 'Amella to Player');


DELETE FROM `quest_template` WHERE `ID` IN (70061 /*-Unknown-*/, 66825 /*-Unknown-*/, 68795 /*-Unknown-*/, 66115 /*-Unknown-*/, 70068 /*-Unknown-*/, 66001 /*-Unknown-*/, 70648 /*-Unknown-*/);
INSERT INTO `quest_template` (`ID`, `QuestType`, `QuestPackageID`, `ContentTuningID`, `QuestSortID`, `QuestInfoID`, `SuggestedGroupNum`, `RewardNextQuest`, `RewardXPDifficulty`, `RewardXPMultiplier`, `RewardMoneyDifficulty`, `RewardMoneyMultiplier`, `RewardBonusMoney`, `RewardSpell`, `RewardHonor`, `RewardKillHonor`, `StartItem`, `RewardArtifactXPDifficulty`, `RewardArtifactXPMultiplier`, `RewardArtifactCategoryID`, `Flags`, `FlagsEx`, `FlagsEx2`, `RewardSkillLineID`, `RewardNumSkillUps`, `PortraitGiver`, `PortraitGiverMount`, `PortraitGiverModelSceneID`, `PortraitTurnIn`, `RewardItem1`, `RewardItem2`, `RewardItem3`, `RewardItem4`, `RewardAmount1`, `RewardAmount2`, `RewardAmount3`, `RewardAmount4`, `ItemDrop1`, `ItemDrop2`, `ItemDrop3`, `ItemDrop4`, `ItemDropQuantity1`, `ItemDropQuantity2`, `ItemDropQuantity3`, `ItemDropQuantity4`, `RewardChoiceItemID1`, `RewardChoiceItemID2`, `RewardChoiceItemID3`, `RewardChoiceItemID4`, `RewardChoiceItemID5`, `RewardChoiceItemID6`, `RewardChoiceItemQuantity1`, `RewardChoiceItemQuantity2`, `RewardChoiceItemQuantity3`, `RewardChoiceItemQuantity4`, `RewardChoiceItemQuantity5`, `RewardChoiceItemQuantity6`, `RewardChoiceItemDisplayID1`, `RewardChoiceItemDisplayID2`, `RewardChoiceItemDisplayID3`, `RewardChoiceItemDisplayID4`, `RewardChoiceItemDisplayID5`, `RewardChoiceItemDisplayID6`, `POIContinent`, `POIx`, `POIy`, `POIPriority`, `RewardTitle`, `RewardArenaPoints`, `RewardFactionID1`, `RewardFactionID2`, `RewardFactionID3`, `RewardFactionID4`, `RewardFactionID5`, `RewardFactionValue1`, `RewardFactionValue2`, `RewardFactionValue3`, `RewardFactionValue4`, `RewardFactionValue5`, `RewardFactionCapIn1`, `RewardFactionCapIn2`, `RewardFactionCapIn3`, `RewardFactionCapIn4`, `RewardFactionCapIn5`, `RewardFactionOverride1`, `RewardFactionOverride2`, `RewardFactionOverride3`, `RewardFactionOverride4`, `RewardFactionOverride5`, `RewardFactionFlags`, `AreaGroupID`, `TimeAllowed`, `AllowableRaces`, `TreasurePickerID`, `Expansion`, `ManagedWorldStateID`, `QuestSessionBonus`, `LogTitle`, `LogDescription`, `QuestDescription`, `AreaDescription`, `QuestCompletionLog`, `RewardCurrencyID1`, `RewardCurrencyID2`, `RewardCurrencyID3`, `RewardCurrencyID4`, `RewardCurrencyQty1`, `RewardCurrencyQty2`, `RewardCurrencyQty3`, `RewardCurrencyQty4`, `PortraitGiverText`, `PortraitGiverName`, `PortraitTurnInText`, `PortraitTurnInName`, `AcceptedSoundKitID`, `CompleteSoundKitID`, `VerifiedBuild`) VALUES
(70061, 2, 0, 2296, 13644, 0, 0, 0, 5, 1, 5, 1, 7150, 0, 0, 0, 0, 0, 1, 0, 37748744, 8192, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2510, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 7, 7, 2500, 0, 0, 0, 0, 0, 0, 0, 18446744073709551615, 2180, 9, 0, 0, 'Training Wings', 'Guide a whelp to eliminate $2oa Agitated Weedlings, $3oa Intrusive Pupstingers, and $4oa Relentless Gust.', 'The dragons were gone from the Dragon Isles for a really long time, $p. To tell the truth... some of our skills have atrophied as they were passed down from generation to generation.\n\nThese whelps should be easy to teach, yet we\'re having some trouble wrangling them.\n\nSay.\n\nI saw that even Majordomo Selistra trusts you with the most crucial tasks. Would you lend us a hand and help one of our young?', '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', '', '', 890, 878, 45505), -- -Unknown-
(66825, 2, 0, 2296, 13644, 0, 0, 0, 3, 1, 3, 1, 3600, 0, 0, 0, 0, 0, 1, 0, 33554440, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2510, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 7, 7, 1500, 0, 0, 0, 0, 0, 0, 0, 18446744073709551615, 0, 9, 0, 0, 'A Ruby Lifecalling', 'Participate in the Lifecalling Ceremony at the Ruby Lifeshrine.', '$p! How fortunate you are here! We are about to begin a Lifecalling Ceremony and would be honored if you assisted us. \n\nA dragonspawn\'s Calling is very special. Some become masterful gardeners; others care for particular wildlife.\n\nThese young dragonspawn have finished their training and are ready to take on their first Callings. I know they would be thrilled to have you participate. When you\'re ready, please present each of the items on this table to them.', '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', '', '', 890, 878, 45505), -- -Unknown-
(68795, 2, 0, 2296, 13644, 0, 0, 0, 1, 1, 1, 1, 900, 376027, 0, 0, 0, 0, 1, 0, 39845896, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2510, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 7, 7, 400, 0, 0, 0, 0, 0, 0, 0, 18446744073709551615, 2066, 9, 0, 0, 'Dragonriding', 'Speak with Lord Andestrasz in the Ruby Lifeshrine.', 'One thing you may have already discovered about this place: the Dragon Isles are vast. \n\nSome of the younger dragons have expressed intense interest in exploring every corner and secret hiding place in this renewed land, even those places that are not readily reached from the ground. They are eager to work with you, and join you on your journey across the lands.\n\nSpeak with Lord Andestrasz, here in the Ruby Lifeshrine. He will explain more of what they intend.', '', 'Speak with Lord Andestrasz in the Ruby Lifeshrine.', 0, 0, 0, 0, 0, 0, 0, 0, '', '', '', '', 890, 878, 45505), -- -Unknown-
(66115, 2, 0, 2296, 13644, 0, 0, 0, 5, 1, 5, 1, 7150, 0, 0, 0, 0, 0, 1, 0, 37748744, 8192, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2510, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 7, 7, 2500, 0, 0, 0, 0, 0, 0, 0, 18446744073709551615, 2080, 9, 0, 0, 'The Mandate of the Red', 'Talk to the tenders at the Ruby Lifeshrine.', 'Our calling is care and compassion. We help the other flights not only for their own sake, but for dragonkind as a whole.\n\nPerhaps you would understand if you spoke to the dragonspawn here at the Ruby Lifeshrine.', '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', '', '', 890, 878, 45505), -- -Unknown-
(70068, 3, 0, 2521, 13646, 136, 3, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 34144256, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2510, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 7, 7, 10000, 0, 0, 0, 0, 0, 7652, 0, 18446744073709551615, 2188, 9, 0, 0, 'Cobalt Catastrophe', '', '', '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', '', '', 890, 878, 45505), -- -Unknown-
(66001, 2, 0, 2285, 13644, 0, 0, 0, 5, 1, 5, 1, 7150, 375925, 0, 0, 0, 0, 1, 0, 39845896, 8192, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2510, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 7, 7, 2500, 0, 0, 0, 0, 0, 0, 0, 18446744073709551615, 2079, 9, 0, 0, 'A Last Hope', 'Rescue the last Infused Dragon Egg.', 'A whole brood of whelplings, lost...\n\n<Sendrax straightens her back and sticks her chin up.>\n\nThere is one more location we have not checked yet. The large ritual site where that proto-dragon dropped off the eggs.\n\nLet us charge their cruel defenses together, $p, and save what we can.', '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', '', '', 890, 878, 45505), -- -Unknown-
(70648, 3, 0, 2285, 13644, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 34144256, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 18446744073709551615, 0, 9, 0, 0, 'Firava the Rekindler', '', '', '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', '', '', 890, 878, 45505); -- -Unknown-


UPDATE `quest_template` SET `RewardBonusMoney`=3600, `VerifiedBuild`=45505 WHERE `ID`=70058; -- Friend on the Mend
UPDATE `quest_template` SET `RewardBonusMoney`=3600, `VerifiedBuild`=45505 WHERE `ID`=66114; -- For the Benefit of the Queen
UPDATE `quest_template` SET `RewardBonusMoney`=7150, `VerifiedBuild`=45505 WHERE `ID`=70179; -- A Two for One Deal
UPDATE `quest_template` SET `RewardBonusMoney`=7150, `VerifiedBuild`=45505 WHERE `ID`=66000; -- Library of Alexstrasza
UPDATE `quest_template` SET `RewardBonusMoney`=7150, `VerifiedBuild`=45505 WHERE `ID`=65999; -- Red in Tooth and Claw
UPDATE `quest_template` SET `RewardBonusMoney`=7150, `VerifiedBuild`=45505 WHERE `ID`=65998; -- Future of the Flights
UPDATE `quest_template` SET `RewardBonusMoney`=900, `VerifiedBuild`=45505 WHERE `ID`=65997; -- Chasing Sendrax
UPDATE `quest_template` SET `RewardBonusMoney`=7150, `VerifiedBuild`=45505 WHERE `ID`=66998; -- Fighting Fire with... Water
UPDATE `quest_template` SET `RewardBonusMoney`=900, `VerifiedBuild`=45505 WHERE `ID`=65996; -- Veteran Reinforcements
UPDATE `quest_template` SET `VerifiedBuild`=45505 WHERE `ID`=71210;

DELETE FROM `quest_objectives` WHERE `ID` IN (429870 /*429870*/, 429862 /*429862*/, 429861 /*429861*/, 429779 /*429779*/, 431418 /*431418*/, 431417 /*431417*/, 431416 /*431416*/, 431415 /*431415*/, 430383 /*430383*/, 430382 /*430382*/, 430380 /*430380*/, 430388 /*430388*/, 431032 /*431032*/, 429384 /*429384*/, 427107 /*427107*/, 427106 /*427106*/, 427109 /*427109*/, 427108 /*427108*/, 430447 /*430447*/, 430446 /*430446*/, 430445 /*430445*/, 430444 /*430444*/, 430443 /*430443*/, 430442 /*430442*/, 430441 /*430441*/, 430440 /*430440*/, 430439 /*430439*/, 430438 /*430438*/, 430437 /*430437*/, 427562 /*427562*/, 428675 /*428675*/, 427836 /*427836*/, 427620 /*427620*/, 430776 /*430776*/);
INSERT INTO `quest_objectives` (`ID`, `QuestID`, `Type`, `Order`, `StorageIndex`, `ObjectID`, `Amount`, `Flags`, `Flags2`, `ProgressBarWeight`, `Description`, `VerifiedBuild`) VALUES
(429870, 70061, 0, 3, 3, 194159, 1, 0, 0, 0, '', 45505), -- 429870
(429862, 70061, 0, 2, 2, 194142, 6, 0, 0, 0, '', 45505), -- 429862
(429861, 70061, 0, 1, 1, 193994, 12, 2, 0, 0, '', 45505), -- 429861
(429779, 70061, 0, 0, 0, 193979, 1, 0, 0, 0, 'Ruby Whelpling chosen', 45505), -- 429779
(431418, 66825, 0, 8, 8, 191468, 1, 28, 0, 0, '[DNT] Can', 45505), -- 431418
(431417, 66825, 0, 7, 3, 191461, 1, 28, 0, 0, '[DNT] Lasso', 45505), -- 431417
(431416, 66825, 0, 6, 2, 191466, 1, 28, 0, 0, '[DNT] Jar', 45505), -- 431416
(431415, 66825, 0, 5, 1, 191467, 1, 28, 0, 0, '[DNT] Rake', 45505), -- 431415
(430383, 66825, 2, 4, 7, 377300, 1, 28, 0, 0, '[DNT] Watering Can presented', 45505), -- 430383
(430382, 66825, 2, 3, 6, 377301, 1, 28, 0, 0, '[DNT] Lasso presented', 45505), -- 430382
(430380, 66825, 2, 2, 5, 377298, 1, 28, 0, 0, '[DNT] Jar presented', 45505), -- 430380
(430388, 66825, 2, 1, 4, 377302, 1, 28, 0, 0, '[DNT] Rake presented', 45505), -- 430388
(431032, 66825, 0, 0, 0, 196830, 4, 0, 0, 0, 'Callings chosen', 45505), -- 431032
(429384, 68795, 0, 0, 0, 193287, 1, 0, 0, 0, 'Speak to Lord Andestrasz about Dragonriding', 45505), -- 429384
(427107, 66115, 0, 3, 1, 189260, 1, 2, 0, 0, 'Speak to Zahkrana', 45505), -- 427107
(427106, 66115, 0, 2, 0, 185904, 1, 2, 0, 0, 'Speak to Mother Elion', 45505), -- 427106
(427109, 66115, 0, 1, 3, 189262, 1, 2, 0, 0, 'Speak to Akxall', 45505), -- 427109
(427108, 66115, 0, 0, 2, 189261, 1, 0, 0, 0, 'Speak to Xius', 45505), -- 427108
(430447, 70068, 0, 10, 9, 190778, 25, 92, 0, 4, '', 45505), -- 430447
(430446, 70068, 0, 9, 8, 190779, 25, 92, 0, 4, '', 45505), -- 430446
(430445, 70068, 0, 8, 7, 184440, 25, 92, 0, 4, '', 45505), -- 430445
(430444, 70068, 0, 7, 6, 184444, 50, 92, 0, 2, '', 45505), -- 430444
(430443, 70068, 0, 6, 5, 184453, 50, 92, 0, 2, '', 45505), -- 430443
(430442, 70068, 0, 5, 4, 184461, 50, 92, 0, 2, '', 45505), -- 430442
(430441, 70068, 0, 4, 3, 190952, 50, 92, 0, 2, '', 45505), -- 430441
(430440, 70068, 0, 3, 2, 190776, 50, 92, 0, 2, '', 45505), -- 430440
(430439, 70068, 0, 2, 1, 190780, 50, 92, 0, 2, '', 45505), -- 430439
(430438, 70068, 0, 1, 0, 190947, 100, 92, 0, 1, '', 45505), -- 430438
(430437, 70068, 15, 0, -1, 0, 1, 0, 0, 0, 'Sundered Flame disrupted', 45505), -- 430437
(427562, 66001, 0, 3, 0, 190211, 1, 2, 0, 0, 'Carry the egg to safety', 45505), -- 427562
(428675, 66001, 0, 2, 3, 191889, 1, 28, 0, 0, 'Tanking', 45505), -- 428675
(427836, 66001, 0, 1, 2, 191888, 1, 2, 0, 0, 'Pick up the Infused Dragon Egg', 45505), -- 427836
(427620, 66001, 0, 0, 1, 190269, 1, 0, 0, 0, 'Meet Sendrax by the ritual site', 45505), -- 427620
(430776, 70648, 0, 0, 0, 195915, 1, 1, 0, 0, '', 45505); -- 430776

UPDATE `quest_objectives` SET `VerifiedBuild`=45505 WHERE `ID` IN (430335, 430334, 430333, 429787, 429786, 429785, 430337, 429774, 429773, 431403, 427086, 429819, 430094, 427713, 427712, 427711, 427710, 427709, 427692, 427448, 427462, 427657, 427655, 427654, 427478, 427477, 427534, 428768, 428767, 428766, 428679, 429977, 429945, 431605);
UPDATE `quest_objectives` SET `Description`='Erupting Cavern Guard Healed', `VerifiedBuild`=45505 WHERE `ID`=430207; -- 430207


DELETE FROM `quest_visual_effect` WHERE (`Index`=0 AND `ID` IN (429870,429862,429861,429779,430383,430382,430380,430388,429384,427106,427562,427836,427620)) OR (`Index`=2 AND `ID`=427562) OR (`Index`=1 AND `ID` IN (427562,427836));
INSERT INTO `quest_visual_effect` (`ID`, `Index`, `VisualEffect`, `VerifiedBuild`) VALUES
(429870, 0, 19902, 45505),
(429862, 0, 19902, 45505),
(429861, 0, 19902, 45505),
(429779, 0, 19902, 45505),
(430383, 0, 2099, 45505),
(430382, 0, 2099, 45505),
(430380, 0, 2099, 45505),
(430388, 0, 2099, 45505),
(429384, 0, 2099, 45505),
(427106, 0, 18845, 45505),
(427562, 2, 18841, 45505),
(427562, 1, 18840, 45505),
(427562, 0, 18839, 45505),
(427836, 1, 18838, 45505),
(427836, 0, 18837, 45505),
(427620, 0, 18836, 45505);

UPDATE `quest_visual_effect` SET `VerifiedBuild`=45505 WHERE (`Index`=0 AND `ID` IN (430335,430334,430333,429787,429786,429785,430337,431403,427086,430094,427448,427478,427477,427534)) OR (`Index`=2 AND `ID` IN (430094,427448)) OR (`Index`=1 AND `ID` IN (430094,427448,427477)) OR (`Index`=5 AND `ID`=427448) OR (`Index`=4 AND `ID`=427448) OR (`Index`=3 AND `ID`=427448);

DELETE FROM `quest_reward_display_spell` WHERE (`QuestID`=68795 AND `Idx`=0);
INSERT INTO `quest_reward_display_spell` (`QuestID`, `Idx`, `SpellID`, `PlayerConditionID`, `VerifiedBuild`) VALUES
(68795, 0, 376027, 0, 45505);


DELETE FROM `creature_template` WHERE `entry` IN (197732 /*Ruby Warden*/, 181040 /*Stella Stargazer*/, 190090 /*Infused Dragon Egg*/, 194575 /*Rising Tempest*/, 197956 /*Injured Shrineguard*/, 186795 /*Majordomo Selistra*/, 186828 /*Hornswog (0.6/0.6 Melee)*/, 198034 /*Snappy*/, 186917 /*Turbulent Gust*/, 186918 /*Turbulent Gust*/, 190269 /*Sendrax*/, 188074 /*Agitated Sidewalker*/, 197211 /*Murghurgl the Invader*/, 187290 /*Alexstrasza the Life-Binder*/, 191765 /*Mean Duck*/, 194008 /*Lillistrazsa*/, 187392 /*Tuskarr Pilgrim*/, 187394 /*Scoutstrasza*/, 189637 /*Curious Duckling*/, 191892 /*Infused Dragon Egg*/, 194174 /*Amella*/, 188667 /*Swelling Fire Elemental*/, 189812 /*Cliffdrip Snapstrider*/, 189814 /*Cliffdrip Wavemender*/, 189815 /*Cliffdrip Fallstriker*/, 192054 /*Bottled Water Elemental*/);
INSERT INTO `creature_template` (`entry`, `KillCredit1`, `KillCredit2`, `name`, `femaleName`, `subname`, `TitleAlt`, `IconName`, `HealthScalingExpansion`, `RequiredExpansion`, `VignetteID`, `unit_class`, `WidgetSetID`, `WidgetSetUnitConditionID`, `rank`, `family`, `type`, `type_flags`, `type_flags2`, `HealthModifier`, `ManaModifier`, `RacialLeader`, `movementId`, `CreatureDifficultyID`, `VerifiedBuild`) VALUES
(197732, 0, 0, 'Ruby Warden', '', NULL, NULL, NULL, 9, 0, 0, 1, 0, 0, 0, 0, 2, 0, 0, 2, 1, 0, 0, 226090, 45505), -- Ruby Warden
(181040, 0, 0, 'Stella Stargazer', '', NULL, NULL, NULL, 9, 0, 0, 8, 0, 0, 0, 0, 7, 0, 0, 1, 1, 0, 0, 204719, 45505), -- Stella Stargazer
(190090, 0, 0, 'Infused Dragon Egg', '', NULL, NULL, 'questinteract', 9, 0, 0, 1, 0, 0, 0, 0, 2, 1610612752, 83886086, 1, 1, 0, 0, 216779, 45505), -- Infused Dragon Egg
(194575, 0, 0, 'Rising Tempest', '', NULL, NULL, NULL, 9, 0, 0, 8, 0, 0, 0, 0, 4, 0, 0, 1, 1, 0, 0, 222806, 45505), -- Rising Tempest
(197956, 0, 0, 'Injured Shrineguard', '', NULL, NULL, NULL, 9, 0, 0, 1, 0, 0, 0, 0, 2, 0, 0, 3, 1, 0, 0, 226321, 45505), -- Injured Shrineguard
(186795, 0, 0, 'Majordomo Selistra', '', NULL, NULL, NULL, 9, 0, 0, 1, 0, 0, 1, 0, 2, 0, 32768, 6, 1, 0, 0, 211204, 45505), -- Majordomo Selistra
(186828, 0, 0, 'Hornswog (0.6/0.6 Melee)', '', '(T0) FIGHTER', NULL, NULL, 9, 0, 0, 1, 0, 0, 6, 303, 2, 1, 0, 0.60000002384185791, 1, 0, 0, 211239, 45505), -- Hornswog (0.6/0.6 Melee)
(198034, 0, 0, 'Snappy', '', NULL, NULL, NULL, 9, 0, 0, 1, 0, 0, 0, 8, 1, 2147483720, 0, 1, 1, 0, 0, 226402, 45505), -- Snappy
(186917, 0, 0, 'Turbulent Gust', '', NULL, NULL, NULL, 9, 0, 0, 8, 0, 0, 0, 0, 4, 0, 0, 1.20000004768371582, 1, 0, 0, 211360, 45505), -- Turbulent Gust
(186918, 0, 0, 'Turbulent Gust', '', NULL, NULL, NULL, 9, 0, 0, 8, 0, 0, 0, 0, 4, 0, 0, 1.20000004768371582, 1, 0, 0, 211361, 45505), -- Turbulent Gust
(190269, 0, 0, 'Sendrax', '', NULL, NULL, NULL, 9, 0, 0, 1, 0, 0, 0, 0, 2, 0, 32768, 2.20000004768371582, 1, 0, 0, 216960, 45505), -- Sendrax
(188074, 0, 0, 'Agitated Sidewalker', '', NULL, NULL, NULL, 9, 0, 0, 1, 0, 0, 6, 8, 1, 1, 0, 0.699999988079071044, 1, 0, 0, 214749, 45505), -- Agitated Sidewalker
(197211, 0, 0, 'Murghurgl the Invader', '', NULL, NULL, NULL, 9, 0, 0, 1, 0, 0, 0, 0, 7, 2147483720, 0, 2.5, 1, 0, 0, 225535, 45505), -- Murghurgl the Invader
(187290, 0, 0, 'Alexstrasza the Life-Binder', '', 'Queen of the Dragons', NULL, NULL, 9, 0, 0, 2, 0, 0, 1, 0, 2, 4, 32768, 600, 1, 0, 0, 213926, 45505), -- Alexstrasza the Life-Binder
(191765, 0, 0, 'Mean Duck', '', NULL, NULL, NULL, 9, 0, 0, 1, 0, 0, 0, 125, 1, 1, 0, 1.799999952316284179, 1, 0, 0, 219970, 45505), -- Mean Duck
(194008, 0, 0, 'Lillistrazsa', '', NULL, NULL, NULL, 9, 0, 0, 1, 0, 0, 0, 0, 2, 8388608, 0, 0.5, 1, 0, 0, 222237, 45505), -- Lillistrazsa
(187392, 0, 0, 'Tuskarr Pilgrim', '', NULL, NULL, NULL, 9, 0, 0, 1, 0, 0, 0, 0, 7, 0, 0, 1, 1, 0, 0, 214030, 45505), -- Tuskarr Pilgrim
(187394, 0, 0, 'Scoutstrasza', '', NULL, NULL, NULL, 9, 0, 0, 1, 0, 0, 1, 0, 2, 0, 0, 6, 1, 0, 0, 214032, 45505), -- Scoutstrasza
(189637, 0, 0, 'Curious Duckling', '', NULL, NULL, NULL, 9, 0, 0, 1, 0, 0, 6, 0, 8, 0, 0, 0.200000002980232238, 1, 0, 0, 216322, 45505), -- Curious Duckling
(191892, 0, 0, 'Infused Dragon Egg', '', NULL, NULL, NULL, 9, 0, 0, 1, 0, 0, 0, 0, 2, 1610612752, 83886086, 1, 1, 0, 0, 220097, 45505), -- Infused Dragon Egg
(194174, 0, 0, 'Amella', '', 'Head Egg-Tender', NULL, NULL, 9, 0, 0, 8, 0, 0, 0, 0, 2, 0, 0, 6, 1, 0, 0, 222403, 45505), -- Amella
(188667, 189975, 0, 'Swelling Fire Elemental', '', NULL, NULL, NULL, 9, 0, 0, 1, 0, 0, 0, 0, 4, 0, 0, 2.20000004768371582, 1, 0, 0, 215353, 45505), -- Swelling Fire Elemental
(189812, 193312, 0, 'Cliffdrip Snapstrider', '', NULL, NULL, NULL, 9, 0, 0, 1, 0, 0, 0, 0, 7, 0, 0, 1.799999952316284179, 1, 0, 0, 216497, 45505), -- Cliffdrip Snapstrider
(189814, 193312, 0, 'Cliffdrip Wavemender', '', NULL, NULL, NULL, 9, 0, 0, 8, 0, 0, 0, 0, 7, 0, 0, 0.800000011920928955, 1, 0, 0, 216499, 45505), -- Cliffdrip Wavemender
(189815, 193312, 0, 'Cliffdrip Fallstriker', '', NULL, NULL, NULL, 9, 0, 0, 1, 0, 0, 0, 0, 7, 0, 0, 0.800000011920928955, 1, 0, 0, 216500, 45505), -- Cliffdrip Fallstriker
(192054, 0, 0, 'Bottled Water Elemental', '', NULL, NULL, NULL, 9, 0, 0, 8, 0, 0, 0, 0, 4, 0, 0, 1.20000004768371582, 1, 0, 0, 220263, 45505); -- Bottled Water Elemental


UPDATE `creature_template` SET `VerifiedBuild`=45505 WHERE `entry` IN (191012, 191013, 191016, 192136, 191025, 191027, 191031, 185464, 192168, 192181, 192182, 185484, 192186, 185485, 193304, 185489, 185490, 184394, 194474, 191126, 194478, 194479, 190013, 179965, 136403, 186683, 186692, 192284, 194524, 191174, 194525, 191176, 191179, 192305, 196774, 190080, 195672, 190093, 186771, 196827, 191254, 190151, 190155, 190171, 186822, 186823, 186825, 186829, 186833, 186836, 187955, 191323, 190211, 189103, 189136, 192491, 182439, 188029, 192498, 192512, 190295, 192539, 195915, 195917, 192574, 188107, 194818, 194820, 194821, 185904, 189260, 189261, 189262, 193737, 192625, 191517, 193757, 187058, 187060, 187071, 187072, 187073, 69791, 69792, 180377, 193790, 192674, 193791, 197166, 187130, 188280, 188297, 191653, 191656, 189448, 193920, 195050, 195051, 195052, 193955, 188372, 186143, 186146, 193979, 193983, 193987, 193988, 193991, 193994, 187292, 193995, 187295, 191768, 195120, 195125, 190660, 191792, 191796, 191797, 142666, 142668, 191817, 191823, 194076, 194099, 187406, 191879, 191886, 191891, 191893, 191894, 191904, 191917, 194159, 193061, 191944, 191945, 191954, 193077, 194195, 191975, 191980, 193097, 191982, 191983, 192013, 188666, 192047, 188698, 188699, 192058, 194314, 192096, 189881);
UPDATE `creature_template` SET `unit_class`=8, `VerifiedBuild`=45505 WHERE `entry`=185496; -- Primal Dropling
UPDATE `creature_template` SET `HealthModifier`=1.5, `VerifiedBuild`=45505 WHERE `entry`=194517; -- Crushing Elemental
UPDATE `creature_template` SET `HealthModifier`=2.5, `VerifiedBuild`=45505 WHERE `entry`=194523; -- Raging Elemental
UPDATE `creature_template` SET `family`=303, `type_flags`=1, `VerifiedBuild`=45505 WHERE `entry`=186834; -- Stubborn Hornswog
UPDATE `creature_template` SET `type_flags`=524288, `VerifiedBuild`=45505 WHERE `entry`=194142; -- Intrusive Pupstinger


DELETE FROM `creature_template_model` WHERE (`Idx`=0 AND `CreatureID` IN (194575,194174,194008,187290,197956,181040,187392,186917,186918,189637,198034,197211,189814,189812,188074,189815,191765,187394,197732,191892,186795,190269,186828,190090,188667,192054)) OR (`Idx`=1 AND `CreatureID` IN (187290,197956,180377,186146,198034,188074,191765,197732,186795,192054)) OR (`Idx`=2 AND `CreatureID` IN (197956,198034,188074,191765,197732)) OR (`Idx`=13 AND `CreatureID`=198034) OR (`Idx`=12 AND `CreatureID`=198034) OR (`Idx`=11 AND `CreatureID`=198034) OR (`Idx`=10 AND `CreatureID`=198034) OR (`Idx`=9 AND `CreatureID`=198034) OR (`Idx`=8 AND `CreatureID`=198034) OR (`Idx`=7 AND `CreatureID` IN (198034,197732)) OR (`Idx`=6 AND `CreatureID` IN (198034,197732)) OR (`Idx`=5 AND `CreatureID` IN (198034,197732)) OR (`Idx`=4 AND `CreatureID` IN (198034,188074,191765,197732)) OR (`Idx`=3 AND `CreatureID` IN (198034,188074,191765,197732));
INSERT INTO `creature_template_model` (`CreatureID`, `Idx`, `CreatureDisplayID`, `DisplayScale`, `Probability`, `VerifiedBuild`) VALUES
(194575, 0, 102511, 1, 1, 45505), -- Rising Tempest
(194174, 0, 107296, 1, 1, 45505), -- Amella
(194008, 0, 102140, 1, 1, 45505), -- Lillistrazsa
(187290, 1, 92146, 1, 0, 45505), -- Alexstrasza the Life-Binder
(187290, 0, 28227, 1, 1, 45505), -- Alexstrasza the Life-Binder
(197956, 2, 109779, 1, 1, 45505), -- Injured Shrineguard
(197956, 1, 109778, 1, 1, 45505), -- Injured Shrineguard
(197956, 0, 109777, 1, 1, 45505), -- Injured Shrineguard
(181040, 0, 82258, 1, 1, 45505), -- Stella Stargazer
(180377, 1, 109897, 1, 0, 45505), -- Handhold
(187392, 0, 100200, 1.149999976158142089, 1, 45505), -- Tuskarr Pilgrim
(186146, 1, 109898, 1, 0, 45505), -- Handhold
(186917, 0, 102511, 1, 1, 45505), -- Turbulent Gust
(186918, 0, 102511, 1, 1, 45505), -- Turbulent Gust
(189637, 0, 104675, 1, 1, 45505), -- Curious Duckling
(198034, 13, 103862, 1, 1, 45505), -- Snappy
(198034, 12, 103859, 1, 1, 45505), -- Snappy
(198034, 11, 103426, 1, 1, 45505), -- Snappy
(198034, 10, 103416, 1, 1, 45505), -- Snappy
(198034, 9, 103417, 1, 1, 45505), -- Snappy
(198034, 8, 103418, 1, 1, 45505), -- Snappy
(198034, 7, 103419, 1, 1, 45505), -- Snappy
(198034, 6, 103420, 1, 1, 45505), -- Snappy
(198034, 5, 103421, 1, 1, 45505), -- Snappy
(198034, 4, 103422, 1, 1, 45505), -- Snappy
(198034, 3, 103423, 1, 1, 45505), -- Snappy
(198034, 2, 103424, 1, 1, 45505), -- Snappy
(198034, 1, 103425, 1, 1, 45505), -- Snappy
(198034, 0, 103427, 1, 1, 45505), -- Snappy
(197211, 0, 103413, 1, 1, 45505), -- Murghurgl the Invader
(189814, 0, 103279, 1, 1, 45505), -- Cliffdrip Wavemender
(189812, 0, 106820, 1, 1, 45505), -- Cliffdrip Snapstrider
(188074, 4, 103857, 1, 1, 45505), -- Agitated Sidewalker
(188074, 3, 103326, 1, 1, 45505), -- Agitated Sidewalker
(188074, 2, 103324, 1, 1, 45505), -- Agitated Sidewalker
(188074, 1, 103321, 1, 1, 45505), -- Agitated Sidewalker
(188074, 0, 103318, 1, 1, 45505), -- Agitated Sidewalker
(189815, 0, 103281, 1, 1, 45505), -- Cliffdrip Fallstriker
(191765, 4, 107218, 1, 1, 45505), -- Mean Duck
(191765, 3, 107219, 1, 1, 45505), -- Mean Duck
(191765, 2, 107220, 1, 1, 45505), -- Mean Duck
(191765, 1, 107221, 1, 1, 45505), -- Mean Duck
(191765, 0, 107222, 1, 1, 45505), -- Mean Duck
(187394, 0, 102778, 1, 1, 45505), -- Scoutstrasza
(197732, 7, 102726, 1, 1, 45505), -- Ruby Warden
(197732, 6, 102727, 1, 1, 45505), -- Ruby Warden
(197732, 5, 102728, 1, 1, 45505), -- Ruby Warden
(197732, 4, 102729, 1, 1, 45505), -- Ruby Warden
(197732, 3, 102734, 1, 1, 45505), -- Ruby Warden
(197732, 2, 102735, 1, 1, 45505), -- Ruby Warden
(197732, 1, 102736, 1, 1, 45505), -- Ruby Warden
(197732, 0, 102737, 1, 1, 45505), -- Ruby Warden
(191892, 0, 108782, 1, 1, 45505), -- Infused Dragon Egg
(186795, 1, 108032, 1, 0, 45505), -- Majordomo Selistra
(186795, 0, 107040, 1, 1, 45505), -- Majordomo Selistra
(190269, 0, 107673, 1, 1, 45505), -- Sendrax
(186828, 0, 103583, 1, 1, 45505), -- Hornswog (0.6/0.6 Melee)
(190090, 0, 108782, 1, 1, 45505), -- Infused Dragon Egg
(188667, 0, 102518, 1, 1, 45505), -- Swelling Fire Elemental
(192054, 1, 102510, 1, 1, 45505), -- Bottled Water Elemental
(192054, 0, 102509, 1, 1, 45505); -- Bottled Water Elemental

UPDATE `creature_template_model` SET `VerifiedBuild`=45505 WHERE (`Idx`=1 AND `CreatureID` IN (193061,191179,189881,190295,184394,188280,197166,193077,193987,193995,193991,193737,187071,194479,193097,191126,188029,187073,187072,192512,187060,192284,187058,194818,191031,185496,185485,194821,182439,191656,191653,191796,191768,192186,194820,186829,179965,186823,191904,190080,188372,186833,186825,192182,192181,194523,191817,194517,191016,191797,191792,189103,192047,191945,191944,186683,195672)) OR (`Idx`=0 AND `CreatureID` IN (193061,194195,193994,191179,189881,190295,184394,188280,191982,191980,195051,192625,191176,191027,191025,191013,188107,187130,197166,195050,191174,191012,189261,189260,193077,193988,193987,192305,192096,186692,193995,193991,193983,193737,191254,192674,192574,193920,191893,189448,187071,185904,194099,193979,186771,195052,194479,194478,194474,193097,192539,191894,191126,189262,188029,187073,187072,192512,187955,187060,193955,191954,192284,192168,192498,187058,193757,194076,192491,194818,187292,191031,195125,195120,185490,185489,185496,185484,180377,186146,186143,185485,185464,187295,192013,196827,193304,194821,189136,182439,191323,191656,191653,191796,190660,191768,193791,193790,192186,136403,191891,186822,191879,190013,194314,194820,191886,186829,179965,188666,186823,191904,190080,188372,186833,190171,187406,186836,186825,195915,195917,192182,186834,192181,192058,191823,194523,191817,190211,194525,190155,194517,191016,191797,188698,190151,188699,191975,191792,191917,191517,191983,192136,142668,142666,189103,192047,190093,188297,191945,191944,186683,195672,69791,69792)) OR (`Idx`=23 AND `CreatureID`=197166) OR (`Idx`=22 AND `CreatureID`=197166) OR (`Idx`=21 AND `CreatureID`=197166) OR (`Idx`=20 AND `CreatureID`=197166) OR (`Idx`=19 AND `CreatureID`=197166) OR (`Idx`=18 AND `CreatureID`=197166) OR (`Idx`=17 AND `CreatureID`=197166) OR (`Idx`=16 AND `CreatureID`=197166) OR (`Idx`=15 AND `CreatureID`=197166) OR (`Idx`=14 AND `CreatureID`=197166) OR (`Idx`=13 AND `CreatureID` IN (197166,182439,191792)) OR (`Idx`=12 AND `CreatureID` IN (197166,182439,191792)) OR (`Idx`=11 AND `CreatureID` IN (197166,182439,186825,191792)) OR (`Idx`=10 AND `CreatureID` IN (197166,182439,186825,191792)) OR (`Idx`=9 AND `CreatureID` IN (197166,182439,191656,191653,186825,192181,191792)) OR (`Idx`=8 AND `CreatureID` IN (197166,182439,191656,191653,186825,192181,191817,191792)) OR (`Idx`=7 AND `CreatureID` IN (197166,193737,187071,191126,187073,187072,187060,187058,182439,191656,191653,186823,186825,192181,191817,191016,191792,195672)) OR (`Idx`=6 AND `CreatureID` IN (197166,193737,187071,191126,187073,187072,187060,187058,182439,191656,191653,186823,186825,192181,191817,191016,191792,195672)) OR (`Idx`=5 AND `CreatureID` IN (197166,193737,187071,191126,187073,187072,187060,187058,182439,191656,191653,186823,186825,192181,191817,191016,191792,195672)) OR (`Idx`=4 AND `CreatureID` IN (197166,193737,187071,191126,187073,187072,192512,187060,187058,182439,191656,191653,186823,186825,192181,191817,191016,191792,191945,195672)) OR (`Idx`=3 AND `CreatureID` IN (197166,193737,187071,193097,191126,187073,187072,192512,187060,187058,185485,182439,191656,191653,192186,186823,186825,192181,194523,191817,194517,191016,191792,191945,186683,195672)) OR (`Idx`=2 AND `CreatureID` IN (197166,193077,193737,187071,194479,193097,191126,188029,187073,187072,192512,187060,187058,191031,185485,182439,191656,191653,191768,192186,186829,186823,186833,186825,192181,194523,191817,194517,191016,191792,189103,192047,191945,186683,195672));
UPDATE `creature_template_model` SET `CreatureDisplayID`=102550, `DisplayScale`=1.299999952316284179, `VerifiedBuild`=45505 WHERE (`CreatureID`=194159 AND `Idx`=0); -- Relentless Gust
UPDATE `creature_template_model` SET `CreatureDisplayID`=109830, `VerifiedBuild`=45505 WHERE (`CreatureID`=194142 AND `Idx`=0); -- Intrusive Pupstinger
UPDATE `creature_template_model` SET `CreatureDisplayID`=109850, `VerifiedBuild`=45505 WHERE (`CreatureID`=196774 AND `Idx`=0); -- Zoristrasz
UPDATE `creature_template_model` SET `CreatureDisplayID`=109738, `VerifiedBuild`=45505 WHERE (`CreatureID`=193988 AND `Idx`=1); -- Andustrasza
UPDATE `creature_template_model` SET `DisplayScale`=1, `VerifiedBuild`=45505 WHERE (`CreatureID`=194524 AND `Idx` IN (2,1,0)); -- Earthshatter Elemental


UPDATE `creature_questitem` SET `VerifiedBuild`=45505 WHERE (`CreatureEntry`=195915 AND `Idx`=0);


DELETE FROM `gameobject_template` WHERE `entry` IN (377899 /*Hidden Hornswog Hostage*/, 377901 /*Observant Riddles: A Field Guide*/, 379037 /*Soft Ruby Feather*/, 377101 /*Unpollinated Flora*/, 380835 /*Meeting Stone*/, 378850 /*Large Fish Sighting*/, 378849 /*Large Fish Sighting*/, 375105 /*Teleport Tether*/, 376284 /*Green Dragon Egg Incubator*/, 377302 /*Gardener's Trusty Rake*/, 377301 /*Reinforced Hornstrider Lasso*/, 377300 /*Whelptender's Watering Can*/, 377298 /*Shimmery Jar of Fireflies*/, 376289 /*Green Dragon Egg*/, 376288 /*Bronze Dragon Egg*/, 376286 /*Bronze Dragon Egg Incubator*/, 379167 /*Mysterious Glyph*/, 380870 /*Alchemist's Lab Bench*/, 379212 /*Thomas's Crafting Table*/, 377266 /*Overgrown Weeds*/, 377265 /*Overgrown Weeds*/, 376283 /*Blue Dragon Egg Incubator*/, 380869 /*Tailor's Work Table*/, 377231 /*Overgrown Weeds*/, 377230 /*Fallen Leaves*/, 376281 /*Empty Egg Incubator*/, 379213 /*Anvil*/, 379211 /*Forge*/, 379040 /*Glass Bead*/, 379210 /*Brazier*/, 379209 /*Brazier*/, 377102 /*Unpollinated Flora*/, 377100 /*Unpollinated Flora*/, 381341 /*Ancient Stone*/, 381617 /*Kolgar's Pack*/, 378093 /*Mailbox*/, 382069 /*Overripe Lifebinder's Gift*/, 378466 /*Green Dragon Book - Open [DNT]*/, 378465 /*Green Dragon Book [DNT]*/, 378092 /*Garden Bench*/, 378089 /*Garden Bench*/, 382068 /*Barbed Tulip*/, 377098 /*Overgrown Shrub*/, 381396 /*Tuskarr Fishing Net*/, 380868 /*Scribe's Drafting Table*/, 382052 /*Campfire*/, 382054 /*Stool*/, 382053 /*Stool*/, 382028 /*Stool*/, 376240 /*Climbing Gear*/, 375687 /*Water Keg*/, 382027 /*Campfire*/, 382026 /*Stool*/, 375668 /*Misty Treasure Chest*/, 376241 /*Crashed Gyrocopter*/, 375673 /*Climbing Gear*/, 382207 /*Stool*/, 382206 /*Campfire*/, 381343 /*Ancient Stone*/, 376943 /*Dracuixote*/, 376946 /*Pride and Protodrakes*/, 376944 /*The Lord of the Wings*/, 380517 /*Dim Forge*/, 380516 /*Glimmer of Wisdom*/, 380513 /*Slack Tub*/, 380510 /*Dim Forge*/, 377202 /*Ipko's Favorite Toy*/, 380765 /*Chair*/, 380764 /*Cooking Fire*/, 377137 /*Tuskarr Chair [DNT]*/, 380768 /*Anvil*/, 377212 /*Tuskarr Mug*/, 380766 /*Mailbox*/, 376624 /*Tuskarr Anvil*/, 380767 /*Forge*/, 376562 /*Tuskarr Tea Pot*/, 377136 /*Small Tuskarr Table [DNT]*/, 380833 /*Primal Fire Conduit*/, 377502 /*Primal Fire Conduit*/, 376199 /*Hatched Dragon Egg*/, 376945 /*The Red and the Black Flights*/, 376942 /*The Scales of Wrath*/, 376941 /*The Titanic Comedy*/, 242514 /*Books on Fire*/, 381196 /*Titan-Touched Writhebark*/, 376679 /*Ritual Circle*/, 377499 /*On the Origin of Draconic Species*/, 377210 /*Filled Water Bucket [DNT]*/, 379248 /*Draconium Deposit*/);
INSERT INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `IconName`, `castBarCaption`, `unk1`, `size`, `Data0`, `Data1`, `Data2`, `Data3`, `Data4`, `Data5`, `Data6`, `Data7`, `Data8`, `Data9`, `Data10`, `Data11`, `Data12`, `Data13`, `Data14`, `Data15`, `Data16`, `Data17`, `Data18`, `Data19`, `Data20`, `Data21`, `Data22`, `Data23`, `Data24`, `Data25`, `Data26`, `Data27`, `Data28`, `Data29`, `Data30`, `Data31`, `Data32`, `Data33`, `Data34`, `ContentTuningId`, `VerifiedBuild`) VALUES
(377899, 3, 18985, 'Hidden Hornswog Hostage', '', 'Collecting', '', 1, 2124, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 19676, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5139, 111816, 0, 0, 0, 0, 2151, 45505), -- Hidden Hornswog Hostage
(377901, 9, 74797, 'Observant Riddles: A Field Guide', 'interact', '', '', 1, 8599, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Observant Riddles: A Field Guide
(379037, 3, 6962, 'Soft Ruby Feather', 'questinteract', '', '', 2, 2124, 0, 0, 0, 0, 0, 0, 0, 70058, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 112180, 1, 0, 0, 0, 2296, 45505), -- Soft Ruby Feather
(377101, 5, 74980, 'Unpollinated Flora', '', '', '', 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2295, 45505), -- Unpollinated Flora
(380835, 23, 46089, 'Meeting Stone', '', '', '', 1, 110, 120, 14063, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2155, 45505), -- Meeting Stone
(378850, 5, 68795, 'Large Fish Sighting', '', '', '', 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Large Fish Sighting
(378849, 5, 74640, 'Large Fish Sighting', '', '', '', 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Large Fish Sighting
(375105, 5, 71300, 'Teleport Tether', '', '', '', 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Teleport Tether
(376284, 5, 74100, 'Green Dragon Egg Incubator', '', '', '', 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Green Dragon Egg Incubator
(377302, 10, 75233, 'Gardener\'s Trusty Rake', 'questinteract', '', '', 1, 0, 66825, 81132, 3000, 0, 0, 0, 0, 0, 0, 314986, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 56965, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Gardener's Trusty Rake
(377301, 10, 74581, 'Reinforced Hornstrider Lasso', 'questinteract', '', '', 1, 0, 66825, 81118, 3000, 0, 0, 0, 0, 0, 0, 314986, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 56965, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Reinforced Hornstrider Lasso
(377300, 10, 75230, 'Whelptender\'s Watering Can', 'questinteract', '', '', 1, 0, 66825, 81134, 3000, 0, 0, 0, 0, 0, 0, 314986, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 56965, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Whelptender's Watering Can
(377298, 10, 75229, 'Shimmery Jar of Fireflies', 'questinteract', '', '', 1, 0, 66825, 81133, 3000, 0, 0, 0, 0, 0, 0, 314986, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 56965, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Shimmery Jar of Fireflies
(376289, 5, 74108, 'Green Dragon Egg', '', '', '', 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Green Dragon Egg
(376288, 5, 74106, 'Bronze Dragon Egg', '', '', '', 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Bronze Dragon Egg
(376286, 5, 74102, 'Bronze Dragon Egg Incubator', '', '', '', 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Bronze Dragon Egg Incubator
(379167, 5, 76155, 'Mysterious Glyph', 'questinteract', '', '', 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Mysterious Glyph
(380870, 8, 76589, 'Alchemist\'s Lab Bench', '', '', '', 1, 2164, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Alchemist's Lab Bench
(379212, 8, 73015, 'Thomas\'s Crafting Table', '', '', '', 1, 2163, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Thomas's Crafting Table
(377266, 10, 75115, 'Overgrown Weeds', 'questinteract', 'Grabbing', '', 0.400000005960464477, 43, 0, 0, 3000, 0, 0, 0, 0, 0, 0, 375532, 0, 0, 0, 37379, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Overgrown Weeds
(377265, 10, 75115, 'Overgrown Weeds', 'questinteract', 'Grabbing', '', 0.400000005960464477, 43, 0, 0, 3000, 0, 0, 0, 0, 0, 0, 375531, 0, 0, 0, 37379, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Overgrown Weeds
(376283, 5, 74099, 'Blue Dragon Egg Incubator', '', '', '', 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Blue Dragon Egg Incubator
(380869, 8, 76167, 'Tailor\'s Work Table', '', '', '', 1, 2174, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Tailor's Work Table
(377231, 10, 75115, 'Overgrown Weeds', 'questinteract', 'Grabbing', '', 0.400000005960464477, 43, 0, 0, 3000, 0, 0, 0, 0, 0, 0, 375390, 0, 0, 0, 37379, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Overgrown Weeds
(377230, 10, 75131, 'Fallen Leaves', 'questinteract', 'Clearing', '', 1, 99, 0, 0, 3000, 0, 0, 0, 0, 0, 0, 374685, 0, 0, 0, 156031, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Fallen Leaves
(376281, 5, 74097, 'Empty Egg Incubator', '', '', '', 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Empty Egg Incubator
(379213, 8, 74348, 'Anvil', '', '', '', 1, 1, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Anvil
(379211, 8, 71261, 'Forge', '', '', '', 1, 3, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Forge
(379040, 3, 76099, 'Glass Bead', 'questinteract', '', '', 2, 2124, 0, 0, 0, 0, 0, 0, 0, 70058, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 112184, 1, 0, 0, 0, 2296, 45505), -- Glass Bead
(379210, 8, 75513, 'Brazier', '', '', '', 0.730000019073486328, 4, 10, 377066, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Brazier
(379209, 8, 75513, 'Brazier', '', '', '', 0.729999959468841552, 4, 10, 377066, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Brazier
(377102, 5, 74981, 'Unpollinated Flora', '', '', '', 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2295, 45505), -- Unpollinated Flora
(377100, 5, 74979, 'Unpollinated Flora', '', '', '', 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2295, 45505), -- Unpollinated Flora
(381341, 10, 74667, 'Ancient Stone', 'inspect', '', '', 0.5, 0, 0, 0, 0, 0, 0, 0, 8575, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 45505), -- Ancient Stone
(381617, 3, 14316, 'Kolgar\'s Pack', 'questinteract', 'Collecting', '', 1.5, 1691, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 19676, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 113241, 0, 0, 0, 0, 2295, 45505), -- Kolgar's Pack
(378093, 19, 74322, 'Mailbox', '', '', '', 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Mailbox
(382069, 50, 77638, 'Overripe Lifebinder\'s Gift', 'gatherherbs', '', '', 0.400000005960464477, 3427, 113627, 0, 1, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2214, 45505), -- Overripe Lifebinder's Gift
(378466, 5, 74797, 'Green Dragon Book - Open [DNT]', '', '', '', 0.75, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Green Dragon Book - Open [DNT]
(378465, 5, 74796, 'Green Dragon Book [DNT]', '', '', '', 0.75, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Green Dragon Book [DNT]
(378092, 7, 71141, 'Garden Bench', '', '', '', 1, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Garden Bench
(378089, 7, 71141, 'Garden Bench', '', '', '', 1, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Garden Bench
(382068, 50, 77636, 'Barbed Tulip', 'gatherherbs', '', '', 0.400000005960464477, 3427, 113270, 0, 1, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2214, 45505), -- Barbed Tulip
(377098, 10, 74977, 'Overgrown Shrub', 'questinteract', 'Pruning', '', 1, 3444, 0, 0, 3000, 0, 1, 0, 0, 0, 0, 374520, 0, 0, 0, 219232, 0, 0, 0, 0, 0, 0, 0, 98071, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2295, 45505), -- Overgrown Shrub
(381396, 10, 75598, 'Tuskarr Fishing Net', 'fishingcursor', '', '', 1, 0, 0, 0, 3000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 101631, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2214, 45505), -- Tuskarr Fishing Net
(380868, 8, 76640, 'Scribe\'s Drafting Table', '', '', '', 1, 2175, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Scribe's Drafting Table
(382052, 8, 75250, 'Campfire', '', '', '', 1, 4, 10, 2061, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Campfire
(382054, 7, 76729, 'Stool', '', '', '', 1, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Stool
(382053, 7, 76729, 'Stool', '', '', '', 1, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Stool
(382028, 7, 71292, 'Stool', '', '', '', 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Stool
(376240, 10, 12986, 'Climbing Gear', 'openhandglow', '', '', 2, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 356998, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 102902, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Climbing Gear
(375687, 10, 73189, 'Water Keg', '', 'Drinking', '', 1, 3399, 0, 0, 3000, 0, 0, 0, 0, 0, 0, 367177, 0, 0, 0, 21295, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Water Keg
(382027, 8, 70622, 'Campfire', '', '', '', 1, 4, 10, 249358, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Campfire
(382026, 7, 71292, 'Stool', '', '', '', 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Stool
(375668, 3, 73227, 'Misty Treasure Chest', 'questinteract', 'Collecting', '', 1, 3392, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 19676, 0, 0, 95636, 705, 3, 0, 0, 0, 0, 0, 0, 367344, 0, 0, 0, 109909, 0, 0, 0, 0, 2151, 45505), -- Misty Treasure Chest
(376241, 5, 9510, 'Crashed Gyrocopter', '', '', '', 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Crashed Gyrocopter
(375673, 10, 12986, 'Climbing Gear', 'openhandglow', '', '', 2, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 356998, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 95642, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Climbing Gear
(382207, 7, 71292, 'Stool', '', '', '', 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Stool
(382206, 8, 70622, 'Campfire', '', '', '', 1, 4, 10, 2061, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Campfire
(381343, 10, 74143, 'Ancient Stone', 'inspect', '', '', 0.5, 0, 0, 0, 0, 0, 0, 0, 8575, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 45505), -- Ancient Stone
(376943, 3, 74796, 'Dracuixote', 'questinteract', 'Collecting', '', 0.60000002384185791, 1691, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 19676, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 111696, 1, 0, 0, 0, 2285, 45505), -- Dracuixote
(376946, 3, 74799, 'Pride and Protodrakes', 'questinteract', 'Collecting', '', 1, 1691, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 19676, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 111699, 1, 0, 0, 0, 2285, 45505), -- Pride and Protodrakes
(376944, 3, 74797, 'The Lord of the Wings', 'questinteract', 'Collecting', '', 1, 1691, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 19676, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 111697, 1, 0, 0, 0, 2285, 45505), -- The Lord of the Wings
(380517, 8, 13717, 'Dim Forge', '', '', '', 1, 3, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Dim Forge
(380516, 50, 13717, 'Glimmer of Wisdom', 'lootall', 'Opening', '', 2, 1691, 112529, 0, 0, 0, 0, 60, 0, 0, 21400, 0, 100149, 0, 3, 384555, 0, 0, 5284, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2151, 45505), -- Glimmer of Wisdom
(380513, 5, 14851, 'Slack Tub', '', '', '', 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2151, 45505), -- Slack Tub
(380510, 10, 75034, 'Dim Forge', 'inspect', '', '', 1, 0, 0, 0, 3000, 0, 0, 0, 0, 0, 0, 384562, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 100252, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2151, 45505), -- Dim Forge
(377202, 5, 75074, 'Ipko\'s Favorite Toy', '', '', '', 1.5, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Ipko's Favorite Toy
(380765, 7, 75016, 'Chair', '', '', '', 1, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Chair
(380764, 8, 75300, 'Cooking Fire', '', '', '', 1, 4, 10, 2061, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Cooking Fire
(377137, 5, 75016, 'Tuskarr Chair [DNT]', '', '', '', 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Tuskarr Chair [DNT]
(380768, 8, 74458, 'Anvil', '', '', '', 1, 1, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Anvil
(377212, 5, 75080, 'Tuskarr Mug', '', '', '', 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Tuskarr Mug
(380766, 19, 75298, 'Mailbox', '', '', '', 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Mailbox
(376624, 8, 74458, 'Tuskarr Anvil', '', '', '', 1, 1, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Tuskarr Anvil
(380767, 8, 75301, 'Forge', '', '', '', 1, 3, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Forge
(376562, 5, 74428, 'Tuskarr Tea Pot', '', '', '', 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Tuskarr Tea Pot
(377136, 5, 75014, 'Small Tuskarr Table [DNT]', '', '', '', 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Small Tuskarr Table [DNT]
(380833, 5, 73998, 'Primal Fire Conduit', '', '', '', 1.240000009536743164, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Primal Fire Conduit
(377502, 5, 75227, 'Primal Fire Conduit', '', '', '', 1.5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Primal Fire Conduit
(376199, 5, 73988, 'Hatched Dragon Egg', 'questinteract', '', '', 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Hatched Dragon Egg
(376945, 3, 74798, 'The Red and the Black Flights', 'questinteract', 'Collecting', '', 1, 1691, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 19676, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 111698, 1, 0, 0, 0, 2285, 45505), -- The Red and the Black Flights
(376942, 3, 74537, 'The Scales of Wrath', 'questinteract', 'Collecting', '', 0.699999988079071044, 1691, 111695, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 19676, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 2285, 45505), -- The Scales of Wrath
(376941, 3, 74795, 'The Titanic Comedy', 'questinteract', 'Collecting', '', 1, 1691, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 19676, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 111694, 1, 0, 0, 0, 2285, 45505), -- The Titanic Comedy
(242514, 5, 7189, 'Books on Fire', '', '', '', 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Books on Fire
(381196, 50, 76841, 'Titan-Touched Writhebark', '', '', '', 1.5, 3381, 113527, 0, 0, 100, 175, 30, 0, 0, 0, 0, 0, 292, 1, 390412, 0, 0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2181, 45505), -- Titan-Touched Writhebark
(376679, 5, 74516, 'Ritual Circle', '', '', '', 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Ritual Circle
(377499, 2, 74796, 'On the Origin of Draconic Species', '', '', '', 1, 0, 25037, 0, 0, 0, 0, 0, 0, 0, 0, 100127, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- On the Origin of Draconic Species
(377210, 5, 75079, 'Filled Water Bucket [DNT]', '', '', '', 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Filled Water Bucket [DNT]
(379248, 50, 76199, 'Draconium Deposit', '', '', '', 1, 3396, 109866, 0, 0, 25, 50, 30, 0, 0, 0, 0, 0, 681, 1, 388670, 0, 0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2181, 45505); -- Draconium Deposit

UPDATE `gameobject_template` SET `VerifiedBuild`=45505 WHERE `entry` IN (268887, 241593, 316739, 252248, 381305, 381304, 381303, 381302, 381301, 381300, 381236, 381235, 381233, 381232, 381229, 381228, 381226, 381225, 381234, 381231, 381230, 381227, 358375, 376634, 377209, 382031, 381674);
UPDATE `gameobject_template` SET `ContentTuningId`=332, `VerifiedBuild`=45505 WHERE `entry`=268888; -- Fishing Bobber

DELETE FROM `gameobject_questitem` WHERE (`Idx`=0 AND `GameObjectEntry` IN (379037,379040,381617,376943,376946,376944,376945,376942,376941));
INSERT INTO `gameobject_questitem` (`GameObjectEntry`, `Idx`, `ItemId`, `VerifiedBuild`) VALUES
(379037, 0, 198343, 45505), -- Soft Ruby Feather
(379040, 0, 198345, 45505), -- Glass Bead
(381617, 0, 200129, 45505), -- Kolgar's Pack
(376943, 0, 192754, 45505), -- Dracuixote
(376946, 0, 192757, 45505), -- Pride and Protodrakes
(376944, 0, 192755, 45505), -- The Lord of the Wings
(376945, 0, 192756, 45505), -- The Red and the Black Flights
(376942, 0, 192753, 45505), -- The Scales of Wrath
(376941, 0, 192745, 45505); -- The Titanic Comedy



REPLACE INTO `vehicle_template_accessory` (`entry`, `accessory_entry`, `seat_id`, `minion`, `description`, `summontype`, `summontimer`) VALUES
(191210, 191209, 1, UNKNOWN, 'Tigari Khan - Ohuna Feather', UNKNOWN, UNKNOWN), -- Tigari Khan - Ohuna Feather
(191210, 181215, 0, UNKNOWN, 'Tigari Khan - Altan', UNKNOWN, UNKNOWN), -- Tigari Khan - Altan
(191197, 191195, 0, UNKNOWN, 'Sansok Khan - Shikaar Spear', UNKNOWN, UNKNOWN), -- Sansok Khan - Shikaar Spear
(191156, 181215, 0, UNKNOWN, 'Tigari Khan - Altan', UNKNOWN, UNKNOWN), -- Tigari Khan - Altan
(197600, 197601, 0, UNKNOWN, 'Merithra - Everblooming Soil', UNKNOWN, UNKNOWN), -- Merithra - Everblooming Soil
(188105, 191208, 0, UNKNOWN, 'Khanam Matra Sarest - Horn of the Khanam Matra', UNKNOWN, UNKNOWN), -- Khanam Matra Sarest - Horn of the Khanam Matra
(195094, 188180, 0, UNKNOWN, 'Stormbound Proto-Drake - Koroleth', UNKNOWN, UNKNOWN), -- Stormbound Proto-Drake - Koroleth
(190484, 190485, 0, UNKNOWN, 'Kyrakka - Erkhart Stormvein', UNKNOWN, UNKNOWN), -- Kyrakka - Erkhart Stormvein
(192926, 195367, 0, UNKNOWN, 'Trainer Frodrum - Roki', UNKNOWN, UNKNOWN), -- Trainer Frodrum - Roki
(187092, 181215, 0, UNKNOWN, 'Tigari Khan - Altan', UNKNOWN, UNKNOWN); -- Tigari Khan - Altan


REPLACE INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`, `user_type`) VALUES
(192687, 391971, UNKNOWN, UNKNOWN),
(192997, 379035, UNKNOWN, UNKNOWN),
(195669, 391971, UNKNOWN, UNKNOWN),
(196650, 391971, UNKNOWN, UNKNOWN),
(196651, 391971, UNKNOWN, UNKNOWN),
(190708, 262751, UNKNOWN, UNKNOWN),
(191097, 385014, UNKNOWN, UNKNOWN),
(194667, 384300, UNKNOWN, UNKNOWN),
(197728, 391605, UNKNOWN, UNKNOWN),
(197348, 390564, UNKNOWN, UNKNOWN),
(195054, 383139, UNKNOWN, UNKNOWN),
(195049, 383139, UNKNOWN, UNKNOWN),
(194161, 383139, UNKNOWN, UNKNOWN),
(194005, 383139, UNKNOWN, UNKNOWN),
(197569, 391971, UNKNOWN, UNKNOWN),
(197777, 224326, UNKNOWN, UNKNOWN),
(197775, 224326, UNKNOWN, UNKNOWN),
(193554, 381852, UNKNOWN, UNKNOWN),
(191195, 375466, UNKNOWN, UNKNOWN),
(191209, 375472, UNKNOWN, UNKNOWN),
(191208, 375470, UNKNOWN, UNKNOWN),
(197601, 391289, UNKNOWN, UNKNOWN);


DELETE FROM `quest_template` WHERE `ID`=66336;
INSERT INTO `quest_template` (`ID`, `QuestType`, `QuestPackageID`, `ContentTuningID`, `QuestSortID`, `QuestInfoID`, `SuggestedGroupNum`, `RewardNextQuest`, `RewardXPDifficulty`, `RewardXPMultiplier`, `RewardMoneyDifficulty`, `RewardMoneyMultiplier`, `RewardBonusMoney`, `RewardSpell`, `RewardHonor`, `RewardKillHonor`, `StartItem`, `RewardArtifactXPDifficulty`, `RewardArtifactXPMultiplier`, `RewardArtifactCategoryID`, `Flags`, `FlagsEx`, `FlagsEx2`, `RewardSkillLineID`, `RewardNumSkillUps`, `PortraitGiver`, `PortraitGiverMount`, `PortraitGiverModelSceneID`, `PortraitTurnIn`, `RewardItem1`, `RewardItem2`, `RewardItem3`, `RewardItem4`, `RewardAmount1`, `RewardAmount2`, `RewardAmount3`, `RewardAmount4`, `ItemDrop1`, `ItemDrop2`, `ItemDrop3`, `ItemDrop4`, `ItemDropQuantity1`, `ItemDropQuantity2`, `ItemDropQuantity3`, `ItemDropQuantity4`, `RewardChoiceItemID1`, `RewardChoiceItemID2`, `RewardChoiceItemID3`, `RewardChoiceItemID4`, `RewardChoiceItemID5`, `RewardChoiceItemID6`, `RewardChoiceItemQuantity1`, `RewardChoiceItemQuantity2`, `RewardChoiceItemQuantity3`, `RewardChoiceItemQuantity4`, `RewardChoiceItemQuantity5`, `RewardChoiceItemQuantity6`, `RewardChoiceItemDisplayID1`, `RewardChoiceItemDisplayID2`, `RewardChoiceItemDisplayID3`, `RewardChoiceItemDisplayID4`, `RewardChoiceItemDisplayID5`, `RewardChoiceItemDisplayID6`, `POIContinent`, `POIx`, `POIy`, `POIPriority`, `RewardTitle`, `RewardArenaPoints`, `RewardFactionID1`, `RewardFactionID2`, `RewardFactionID3`, `RewardFactionID4`, `RewardFactionID5`, `RewardFactionValue1`, `RewardFactionValue2`, `RewardFactionValue3`, `RewardFactionValue4`, `RewardFactionValue5`, `RewardFactionCapIn1`, `RewardFactionCapIn2`, `RewardFactionCapIn3`, `RewardFactionCapIn4`, `RewardFactionCapIn5`, `RewardFactionOverride1`, `RewardFactionOverride2`, `RewardFactionOverride3`, `RewardFactionOverride4`, `RewardFactionOverride5`, `RewardFactionFlags`, `AreaGroupID`, `TimeAllowed`, `AllowableRaces`, `TreasurePickerID`, `Expansion`, `ManagedWorldStateID`, `QuestSessionBonus`, `LogTitle`, `LogDescription`, `QuestDescription`, `AreaDescription`, `QuestCompletionLog`, `RewardCurrencyID1`, `RewardCurrencyID2`, `RewardCurrencyID3`, `RewardCurrencyID4`, `RewardCurrencyQty1`, `RewardCurrencyQty2`, `RewardCurrencyQty3`, `RewardCurrencyQty4`, `PortraitGiverText`, `PortraitGiverName`, `PortraitTurnInText`, `PortraitTurnInName`, `AcceptedSoundKitID`, `CompleteSoundKitID`, `VerifiedBuild`) VALUES
(66336, 2, 0, 2152, 13645, 0, 0, 0, 1, 1, 1, 1, 1900, 0, 0, 0, 0, 0, 1, 0, 37748744, 8192, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2503, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 7, 7, 800, 0, 0, 0, 0, 0, 0, 0, 18446744073709551615, 0, 9, 0, 0, 'The Isle of Emerald', 'Meet Merithra in the Ancient Bough.', 'Your part in this has not escaped me, mortal. It is large part due to your bravery that we were able to defeat the Primalists.\n\nI have invited the centaur to join me under the Ancient Bough. You, along with the Khanam Matra and her people, are welcome in our home.\n\nFollow this path through the archway across the water and into the trees beyond. I will wait for you there.', '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', '', '', 890, 878, 45505); -- -Unknown-

UPDATE `quest_template` SET `RewardBonusMoney`=22950, `VerifiedBuild`=45505 WHERE `ID`=66783; -- Renewal of Vows
UPDATE `quest_template` SET `RewardBonusMoney`=19100, `PortraitGiver`=107111, `PortraitGiverText`='This primalist leader seeks to destroy the green dragons\' sanctuary.', `PortraitGiverName`='Koroleth', `VerifiedBuild`=45505 WHERE `ID`=66337; -- Stormbreaker
UPDATE `quest_template` SET `RewardBonusMoney`=15300, `VerifiedBuild`=45505 WHERE `ID`=66784; -- Starve the Storm
UPDATE `quest_template` SET `RewardBonusMoney`=15300, `VerifiedBuild`=45505 WHERE `ID`=66335; -- Deconstruct Additional Pylons
UPDATE `quest_template` SET `RewardBonusMoney`=15300, `VerifiedBuild`=45505 WHERE `ID`=66333; -- Justice for Solethus
UPDATE `quest_template` SET `RewardBonusMoney`=30550, `VerifiedBuild`=45505 WHERE `ID`=66421; -- Bonus Objective: The Storm Scar
UPDATE `quest_template` SET `VerifiedBuild`=45505 WHERE `ID` IN (65266, 65020, 64599, 64527, 64438, 63949, 63861, 47148, 45539, 66650, 65717, 65649, 64833, 49135, 49076, 45088, 26137, 13178, 3861, 65764, 64598, 63892, 49077, 36589);
UPDATE `quest_template` SET `RewardBonusMoney`=775, `VerifiedBuild`=45505 WHERE `ID`=64304; -- New Opportunities Await
UPDATE `quest_template` SET `RewardBonusMoney`=390, `VerifiedBuild`=45505 WHERE `ID`=64216; -- Tower Knowledge
UPDATE `quest_template` SET `RewardBonusMoney`=975, `VerifiedBuild`=45505 WHERE `ID`=64106; -- A Unified Effort
UPDATE `quest_template` SET `RewardBonusMoney`=775, `VerifiedBuild`=45505 WHERE `ID`=63977; -- Insider Trading
UPDATE `quest_template` SET `RewardBonusMoney`=1050, `VerifiedBuild`=45505 WHERE `ID`=57532; -- Foraging for Fragments
UPDATE `quest_template` SET `RewardBonusMoney`=210, `VerifiedBuild`=45505 WHERE `ID`=49930; -- The Call for Allies
UPDATE `quest_template` SET `RewardBonusMoney`=470, `VerifiedBuild`=45505 WHERE `ID`=40329; -- Battle Pet Tamers: Warlords
UPDATE `quest_template` SET `Expansion`=9, `VerifiedBuild`=45505 WHERE `ID`=33137; -- The Celestial Tournament
UPDATE `quest_template` SET `RewardBonusMoney`=15300, `Expansion`=9, `VerifiedBuild`=45505 WHERE `ID`=32863; -- What We've Been Training For
UPDATE `quest_template` SET `RewardBonusMoney`=15300, `Expansion`=9, `VerifiedBuild`=45505 WHERE `ID`=31952; -- Battle Pet Tamers: Pandaria
UPDATE `quest_template` SET `RewardBonusMoney`=900 WHERE `ID`=65435;
UPDATE `quest_template` SET `RewardBonusMoney`=22950, `Expansion`=9, `VerifiedBuild`=45505 WHERE `ID`=57639; -- The Legend of Korrak
UPDATE `quest_template` SET `RewardBonusMoney`=775, `VerifiedBuild`=45505 WHERE `ID`=53207; -- The Warfront Looms
UPDATE `quest_template` SET `RewardBonusMoney`=7300, `VerifiedBuild`=45505 WHERE `ID`=70148; -- Without Purpose
UPDATE `quest_template` SET `RewardBonusMoney`=7300 WHERE `ID` IN (66000, 65999, 65998, 66439);
UPDATE `quest_template` SET `RewardBonusMoney`=7650, `VerifiedBuild`=45505 WHERE `ID`=66331; -- The Primalist Front
UPDATE `quest_template` SET `RewardBonusMoney`=7650, `VerifiedBuild`=45505 WHERE `ID`=70220; -- Shady Sanctuary
UPDATE `quest_template` SET `RewardBonusMoney`=1900, `VerifiedBuild`=45505 WHERE `ID`=66344; -- With the Wind At Our Backs
UPDATE `quest_template` SET `RewardBonusMoney`=1900, `VerifiedBuild`=45505 WHERE `ID`=66328; -- Green Dragon Down
UPDATE `quest_template` SET `RewardBonusMoney`=1900, `VerifiedBuild`=45505 WHERE `ID`=66329; -- Blowing of the Horn
UPDATE `quest_template` SET `RewardBonusMoney`=3650 WHERE `ID`=69911;
UPDATE `quest_template` SET `RewardBonusMoney`=15300 WHERE `ID` IN (71012, 69915, 65950);
UPDATE `quest_template` SET `RewardBonusMoney`=15300, `VerifiedBuild`=45505 WHERE `ID`=70739; -- Bloodlines, Sweets, and Teerai
UPDATE `quest_template` SET `ContentTuningID`=2226, `RewardBonusMoney`=15300, `VerifiedBuild`=45505 WHERE `ID`=70730; -- Shikaar Giver
UPDATE `quest_template` SET `RewardBonusMoney`=1900 WHERE `ID` IN (69919, 66671);
UPDATE `quest_template` SET `RewardBonusMoney`=5450, `VerifiedBuild`=45505 WHERE `ID`=67143; -- To Give One's Heart
UPDATE `quest_template` SET `RewardBonusMoney`=19100 WHERE `ID` IN (66958, 66459);
UPDATE `quest_template` SET `RewardBonusMoney`=30550 WHERE `ID`=66658;
UPDATE `quest_template` SET `RewardBonusMoney`=1550, `VerifiedBuild`=45505 WHERE `ID`=64607; -- Tazavesh: A Hard Bargain
UPDATE `quest_template` SET `RewardBonusMoney`=15300, `VerifiedBuild`=45505 WHERE `ID`=70244; -- Nokhud Can Come of This
UPDATE `quest_template` SET `RewardBonusMoney`=1900, `Flags`=37748744, `VerifiedBuild`=45505 WHERE `ID`=66327; -- Chasing the Wind
UPDATE `quest_template` SET `RewardBonusMoney`=1900, `VerifiedBuild`=45505 WHERE `ID`=66259; -- A Storm of Ill Tidings
UPDATE `quest_template` SET `RewardBonusMoney`=19100, `VerifiedBuild`=45505 WHERE `ID`=66258; -- Oh No, Ohn'ahra!


UPDATE `quest_objectives` SET `VerifiedBuild`=45505 WHERE `ID` IN (430653, 430339, 428300, 428301, 428632, 428631, 428630, 428629, 428628, 428627, 428299, 430338, 426824, 428367, 426808, 426807, 426806, 430505, 430501, 428625, 428624, 428623, 428622, 428621, 428356, 428355, 426898, 428354, 428353, 426897, 422649, 422651, 422653, 421930, 421208, 421023, 421167, 420864, 420756, 420622, 420337, 420336, 420335, 420334, 421948, 421947, 421946, 421945, 421944, 421943, 421942, 421941, 421940, 421939, 420917, 421394, 420319, 421393, 420374, 420373, 421171, 420320, 420318, 420044, 392630, 392627, 392629, 392625, 392628, 392624, 290090, 288101, 280702, 270923, 270529, 269341, 269340, 269270, 269269, 269268, 269267, 427707, 423183, 392814, 293812, 293682, 287539, 263590, 257847, 430021, 430020, 429984, 429983, 429982, 428351, 428350, 428349, 428348, 430259, 430602, 430258, 430257, 430255, 427268, 430209, 430208, 430507, 428006, 431039, 431042, 431041, 431040, 431128, 431047, 431216, 431350, 431215, 431352, 431359, 429153, 429098, 423291, 421231, 421230, 421205, 420120, 293996, 293995, 293994, 274942, 430229, 430228, 430227, 430226, 430219, 428597, 430327, 430326, 427253, 428902, 428871, 428869, 428864, 428860, 428859, 428858, 428857, 430830, 428856, 428839);

DELETE FROM `quest_visual_effect` WHERE (`ID`=430219 AND `Index`=0);
INSERT INTO `quest_visual_effect` (`ID`, `Index`, `VisualEffect`, `VerifiedBuild`) VALUES
(430219, 0, 2099, 45505);

UPDATE `quest_visual_effect` SET `VerifiedBuild`=45505 WHERE (`Index`=1 AND `ID` IN (430339,428300,428301,428299,428367,420335)) OR (`Index`=0 AND `ID` IN (430339,428300,428301,428299,430338,428367,426808,426807,426806,430505,422653,421930,421167,420337,420336,420335,420334,421171,420044,392624,270923,269341,269340,269270,269269,269268,269267,430021,430020,429984,429983,429982,428351,428350,428349,428348,430259,430602,430258,430257,430255,427268,430208,428006,431042,431040,431128,431047,431350,431215,431352,431359,429153,429098,293995,293994,430228,428597,430327,427253)) OR (`Index`=2 AND `ID` IN (428300,428301,428299));


UPDATE `quest_reward_display_spell` SET `VerifiedBuild`=45505 WHERE (`Idx`=0 AND `QuestID` IN (64216,70220));

DELETE FROM `creature_template` WHERE `entry` IN (191195 /*Shikaar Spear*/, 191197 /*Sansok Khan*/);
INSERT INTO `creature_template` (`entry`, `KillCredit1`, `KillCredit2`, `name`, `femaleName`, `subname`, `TitleAlt`, `IconName`, `HealthScalingExpansion`, `RequiredExpansion`, `VignetteID`, `unit_class`, `WidgetSetID`, `WidgetSetUnitConditionID`, `rank`, `family`, `type`, `type_flags`, `type_flags2`, `HealthModifier`, `ManaModifier`, `RacialLeader`, `movementId`, `CreatureDifficultyID`, `VerifiedBuild`) VALUES
(191195, 0, 0, 'Shikaar Spear', '', NULL, NULL, 'questinteract', 9, 0, 0, 1, 0, 0, 0, 0, 7, 1073741840, 117440518, 1.10000002384185791, 1, 0, 0, 219400, 45505), -- Shikaar Spear
(191197, 0, 0, 'Sansok Khan', '', NULL, NULL, NULL, 9, 0, 0, 1, 0, 0, 1, 0, 7, 0, 0, 1, 1, 0, 0, 219402, 45505); -- Sansok Khan

UPDATE `creature_template` SET `VerifiedBuild`=45505 WHERE `entry` IN (185726, 190282, 100820, 188068, 194796, 188106, 194834, 190383, 188150, 188156, 194873, 194875, 188180, 194899, 194901, 194902, 195024, 195044, 188343, 192833, 192834, 192853, 195094, 195136, 195137, 197418, 197419, 197420, 192961, 197447, 186303, 184091, 184092, 184093, 195342, 195361, 195368, 195374, 195377, 193144, 195388, 193165, 193169, 190945, 190946, 190948, 190951, 195433, 195435, 186492, 186494, 186495, 195449, 186502, 195455, 186518, 186519, 197705, 197707, 197708, 191097, 191158, 193396, 191235, 191249, 191251, 191259, 88403, 191325, 191343, 191354, 198068, 191358, 191370, 191371, 191426, 191434, 191482, 191483, 191486, 191494, 191495, 195984, 191533, 166949, 191652, 191802, 191808, 189599, 191919, 191927, 189697, 187507, 192065, 192079, 192081, 192085, 192087, 189853, 187671, 185445, 192199, 192206, 192237, 194556, 192319);
UPDATE `creature_template` SET `HealthScalingExpansion`=9, `VerifiedBuild`=45505 WHERE `entry`=194839; -- Hua Greenpaw
UPDATE `creature_template` SET `CreatureDifficultyID`=226175 WHERE `entry`=184422;
UPDATE `creature_template` SET `HealthModifier`=1, `VerifiedBuild`=45505 WHERE `entry`=194284; -- Sedentary Sediment

DELETE FROM `creature_template_model` WHERE (`Idx`=0 AND `CreatureID` IN (191197,191195));
INSERT INTO `creature_template_model` (`CreatureID`, `Idx`, `CreatureDisplayID`, `DisplayScale`, `Probability`, `VerifiedBuild`) VALUES
(191197, 0, 102115, 1, 1, 45505), -- Sansok Khan
(191195, 0, 105717, 1, 1, 45505); -- Shikaar Spear

UPDATE `creature_template_model` SET `VerifiedBuild`=45505 WHERE (`Idx`=1 AND `CreatureID` IN (188150,195137,191483,100820,191482,191371,191358,191652,191259,188343,190282,189853,193169,191158,197708,197707,195433,195377,195374,195368,195361,191927,191802,192081,191808,192079,192853,192834,190951,190948,191097,190945,190946,185445,187671,195449,192237)) OR (`Idx`=0 AND `CreatureID` IN (188150,195137,195136,191495,191483,100820,193165,184093,191482,191370,195094,188180,191371,184091,184092,191354,191358,191652,191259,191434,191235,191533,191426,191251,188343,197447,195455,191343,191249,191325,190282,187507,189853,186303,185726,193169,193144,198068,191158,197705,197708,197707,194556,188106,186502,195435,186495,186494,195433,186519,186518,186492,194899,194902,195388,194901,195377,195374,195368,195361,192087,192085,191927,191802,192081,192199,191919,191808,192206,192079,195984,192833,192853,192834,192961,192065,194875,194873,190951,190948,190383,189697,188156,193396,166949,194834,194796,191486,197420,197419,197418,188068,191097,190945,191494,190946,185445,195044,88403,194839,187671,195024,192319,195449,195342,192237)) OR (`Idx`=2 AND `CreatureID` IN (100820,191259,188343,190282,189853,193169,197708,197707,195377,195374,195368,195361,191802,192079,190945,190946)) OR (`Idx`=7 AND `CreatureID` IN (191259,188343,197708,197707,195374,195368,195361,190945,190946)) OR (`Idx`=6 AND `CreatureID` IN (191259,188343,197708,197707,195374,195368,195361,190945,190946)) OR (`Idx`=5 AND `CreatureID` IN (191259,188343,197708,197707,195377,195374,195368,195361,190945,190946)) OR (`Idx`=4 AND `CreatureID` IN (191259,188343,197708,197707,195377,195374,195368,195361,190945,190946)) OR (`Idx`=3 AND `CreatureID` IN (191259,188343,190282,189853,197708,197707,195377,195374,195368,195361,192079,190945,190946)) OR (`Idx`=9 AND `CreatureID` IN (197708,197707,195368,195361)) OR (`Idx`=8 AND `CreatureID` IN (197708,197707,195368,195361)) OR (`Idx`=11 AND `CreatureID` IN (197707,195368,195361)) OR (`Idx`=10 AND `CreatureID` IN (197707,195368,195361)) OR (`Idx`=12 AND `CreatureID` IN (195368,195361));
UPDATE `creature_template_model` SET `CreatureDisplayID`=91239, `VerifiedBuild`=45505 WHERE (`CreatureID`=189599 AND `Idx`=0); -- Merithra
UPDATE `creature_template_model` SET `CreatureDisplayID`=102642, `VerifiedBuild`=45505 WHERE (`CreatureID`=194284 AND `Idx`=3); -- Sedentary Sediment
UPDATE `creature_template_model` SET `CreatureDisplayID`=102643, `VerifiedBuild`=45505 WHERE (`CreatureID`=194284 AND `Idx`=2); -- Sedentary Sediment
UPDATE `creature_template_model` SET `CreatureDisplayID`=102644, `VerifiedBuild`=45505 WHERE (`CreatureID`=194284 AND `Idx`=1); -- Sedentary Sediment
UPDATE `creature_template_model` SET `CreatureDisplayID`=102645, `VerifiedBuild`=45505 WHERE (`CreatureID`=194284 AND `Idx`=0); -- Sedentary Sediment


UPDATE `creature_questitem` SET `VerifiedBuild`=45505 WHERE (`CreatureEntry`=191235 AND `Idx`=0) OR (`CreatureEntry`=192961 AND `Idx` IN (2,1,0));

DELETE FROM `gameobject_template` WHERE `entry` IN (380577 /*Lofty Malygite*/, 377283 /*Storm Corridor Portal*/, 377225 /*Dragon-Killer Ballista*/, 380915 /*Falconry Perch*/, 382109 /*Campfire*/, 380599 /*Catnip Frond*/, 381043 /*Lightning Bound Chest*/);
INSERT INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `IconName`, `castBarCaption`, `unk1`, `size`, `Data0`, `Data1`, `Data2`, `Data3`, `Data4`, `Data5`, `Data6`, `Data7`, `Data8`, `Data9`, `Data10`, `Data11`, `Data12`, `Data13`, `Data14`, `Data15`, `Data16`, `Data17`, `Data18`, `Data19`, `Data20`, `Data21`, `Data22`, `Data23`, `Data24`, `Data25`, `Data26`, `Data27`, `Data28`, `Data29`, `Data30`, `Data31`, `Data32`, `Data33`, `Data34`, `ContentTuningId`, `VerifiedBuild`) VALUES
(380577, 3, 64768, 'Lofty Malygite', '', 'Opening', '', 1, 43, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 21400, 0, 0, 100246, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5304, 112490, 0, 108, 0, 0, 2214, 45505), -- Lofty Malygite
(377283, 5, 74594, 'Storm Corridor Portal', '', '', '', 1.5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Storm Corridor Portal
(377225, 10, 75138, 'Dragon-Killer Ballista', 'questinteract', 'Destroying', '', 1, 2668, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 24585, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2253, 45505), -- Dragon-Killer Ballista
(380915, 5, 76672, 'Falconry Perch', '', '', '', 0.75, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Falconry Perch
(382109, 8, 70622, 'Campfire', '', '', '', 0.910000026226043701, 4, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45505), -- Campfire
(380599, 3, 76437, 'Catnip Frond', '', '', '', 0.75, 57, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 112509, 0, 0, 0, 0, 2437, 45505), -- Catnip Frond
(381043, 50, 8627, 'Lightning Bound Chest', '', '', '', 1, 3427, 112828, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2214, 45505); -- Lightning Bound Chest

UPDATE `gameobject_template` SET `VerifiedBuild`=45505 WHERE `entry` IN (380908, 377976, 380909, 380906, 381199, 377040, 377570, 377567, 377566, 377568, 378048);

DELETE FROM `scenario_poi` WHERE (`CriteriaTreeID`=138386 AND `BlobIndex`=0 AND `Idx1`=0) OR (`CriteriaTreeID`=138245 AND `BlobIndex`=0 AND `Idx1`=0) OR (`CriteriaTreeID`=138238 AND `BlobIndex`=0 AND `Idx1`=0);
INSERT INTO `scenario_poi` (`CriteriaTreeID`, `BlobIndex`, `Idx1`, `MapID`, `UiMapID`, `Priority`, `Flags`, `WorldEffectID`, `PlayerConditionID`, `VerifiedBuild`) VALUES
(138386, 0, 0, 2444, 2023, 0, 2, 0, 0, 45505),
(138245, 0, 0, 2444, 2023, 0, 2, 0, 0, 45505),
(138238, 0, 0, 2444, 2023, 0, 2, 0, 0, 45505);


