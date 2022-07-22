-- mage
DELETE FROM spell_script_names WHERE spell_id = 336522;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (336522, 'spell_icy_propulsion');

DELETE FROM spell_script_names WHERE spell_id = 336889;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (336889, 'spell_nether_precision');

DELETE FROM spell_script_names WHERE spell_id = 263725;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (263725, 'aura_mage_clearcasting_proc');

DELETE FROM `spell_proc` WHERE `SpellId` IN (336889);
INSERT INTO `spell_proc` (`SpellId`,`SchoolMask`,`SpellFamilyName`,`SpellFamilyMask0`,`SpellFamilyMask1`,`SpellFamilyMask2`,`SpellFamilyMask3`,`ProcFlags`,`ProcFlags2`,`SpellTypeMask`,`SpellPhaseMask`,`HitMask`,`AttributesMask`,`DisableEffectsMask`,`ProcsPerMinute`,`Chance`,`Cooldown`,`Charges`) VALUES
(336889,0x00,3,0x00000000,0x00000000,0x00000000,0x00000000,0x0,0x4,0x0,0x4,0x0,0x0,0x0,0,0,0,0); -- Nether Precision

