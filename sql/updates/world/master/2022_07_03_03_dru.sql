
DELETE FROM spell_script_names WHERE spell_id = 323546;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (323546, 'spell_ravenous_frenzy');
DELETE FROM `spell_proc` WHERE `SpellId` IN (323546);
INSERT INTO `spell_proc` (`SpellId`,`SchoolMask`,`SpellFamilyName`,`SpellFamilyMask0`,`SpellFamilyMask1`,`SpellFamilyMask2`,`SpellFamilyMask3`,`ProcFlags`,`ProcFlags2`,`SpellTypeMask`,`SpellPhaseMask`,`HitMask`,`AttributesMask`,`DisableEffectsMask`,`ProcsPerMinute`,`Chance`,`Cooldown`,`Charges`) VALUES
(323546,0x00,7,0x00000000,0x00000000,0x00000000,0x00000000,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0,0,0,0); -- Ravenous Frenzy (Venthyr)



UPDATE `areatrigger_create_properties` SET `ScriptName`='at_dru_fury_of_elune' WHERE  `Id`=6887;