DELETE FROM spell_script_names WHERE spell_id = 337099;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (337099, 'spell_rising_sun_revival');
DELETE FROM `spell_proc` WHERE `SpellId` IN (337099);
INSERT INTO `spell_proc` (`SpellId`,`SchoolMask`,`SpellFamilyName`,`SpellFamilyMask0`,`SpellFamilyMask1`,`SpellFamilyMask2`,`SpellFamilyMask3`,`ProcFlags`,`ProcFlags2`,`SpellTypeMask`,`SpellPhaseMask`,`HitMask`,`AttributesMask`,`DisableEffectsMask`,`ProcsPerMinute`,`Chance`,`Cooldown`,`Charges`) VALUES
(337099,0x00,53,0x00000000,0x00000000,0x00000000,0x00000000,0x4010,0x0,0x0,0x1,0x0,0x0,0x0,0,0,0,0); -- Rising Sun Revival
