
DELETE FROM spell_script_names WHERE spell_id = 336821;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (336821, 'spell_infernal_cascade');

DELETE FROM `spell_proc` WHERE `SpellId` IN (336821);

REPLACE INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (190446, 'aura_mage_brain_freeze_aura');
DELETE FROM `spell_proc` WHERE `SpellId` IN (190446);
INSERT INTO `spell_proc` (`SpellId`,`SchoolMask`,`SpellFamilyName`,`SpellFamilyMask0`,`SpellFamilyMask1`,`SpellFamilyMask2`,`SpellFamilyMask3`,`ProcFlags`,`ProcFlags2`,`SpellTypeMask`,`SpellPhaseMask`,`HitMask`,`AttributesMask`,`DisableEffectsMask`,`ProcsPerMinute`,`Chance`,`Cooldown`,`Charges`) VALUES
(190446,0x00,3,0x00000000,0x00000000,0x00000000,0x00000000,0x0,0x4,0x0,0x4,0x0,0x0,0x0,0,0,0,0); -- Brain Freeze
REPLACE INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (116, 'spell_mage_frostbolt');

REPLACE INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (44544, 'aura_fingers_of_frost');

DELETE FROM spell_script_names WHERE spell_id = 363500;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (363500, 'spell_fiery_rush');

DELETE FROM spell_script_names WHERE spell_id = 363682;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (363682, 'spell_arcane_lucidity');

DELETE FROM spell_script_names WHERE spell_id = 363535;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (363535, 'spell_frost_storm');

DELETE FROM spell_script_names WHERE spell_id = 153596;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (153596, 'spell_comet_storm_dmg');
