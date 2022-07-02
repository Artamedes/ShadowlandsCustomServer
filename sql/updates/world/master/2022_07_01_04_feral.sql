

DELETE FROM `spell_script_names` WHERE `spell_id`=155722 AND `ScriptName`='aura_dru_rake';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (155722, 'aura_dru_rake');
DELETE FROM `spell_proc` WHERE `SpellId` IN (319439);
INSERT INTO `spell_proc` (`SpellId`,`SchoolMask`,`SpellFamilyName`,`SpellFamilyMask0`,`SpellFamilyMask1`,`SpellFamilyMask2`,`SpellFamilyMask3`,`ProcFlags`,`ProcFlags2`,`SpellTypeMask`,`SpellPhaseMask`,`HitMask`,`AttributesMask`,`DisableEffectsMask`,`ProcsPerMinute`,`Chance`,`Cooldown`,`Charges`) VALUES
(319439,0x00,7,0x00000000,0x00000000,0x00000000,0x00000000,0x51010,0x0,0x1,0x2,0x0,0x0,0x0,0,0,0,0); -- Bloodtalons

DELETE FROM `spell_proc` WHERE `SpellId` IN (145152);
INSERT INTO `spell_proc` (`SpellId`,`SchoolMask`,`SpellFamilyName`,`SpellFamilyMask0`,`SpellFamilyMask1`,`SpellFamilyMask2`,`SpellFamilyMask3`,`ProcFlags`,`ProcFlags2`,`SpellTypeMask`,`SpellPhaseMask`,`HitMask`,`AttributesMask`,`DisableEffectsMask`,`ProcsPerMinute`,`Chance`,`Cooldown`,`Charges`) VALUES
(145152,0x00,7,0x00000000,0x00000000,0x00000000,0x00000000,0x11010,0x0,0x1,0x4,0x0,0x0,0x0,0,0,0,0); -- Bloodtalons

REPLACE INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (274837, 'spell_dru_feral_frenzy_periodic');
REPLACE INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (274837, 'aura_dru_feral_frenzy');

REPLACE INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (363498, 'spell_sickle_of_the_lion');

DELETE FROM `spell_proc` WHERE `SpellId` IN (363498);
INSERT INTO `spell_proc` (`SpellId`,`SchoolMask`,`SpellFamilyName`,`SpellFamilyMask0`,`SpellFamilyMask1`,`SpellFamilyMask2`,`SpellFamilyMask3`,`ProcFlags`,`ProcFlags2`,`SpellTypeMask`,`SpellPhaseMask`,`HitMask`,`AttributesMask`,`DisableEffectsMask`,`ProcsPerMinute`,`Chance`,`Cooldown`,`Charges`) VALUES
(363498,0x00,7,0x00000000,0x00000000,0x00000000,0x00000000,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0,0,0,0); -- Sickle of the Lion
