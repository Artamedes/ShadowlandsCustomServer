-- dru conduits
DELETE FROM spell_script_names WHERE spell_id = 340540;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (340540, 'spell_ursine_vigor');
DELETE FROM `spell_proc` WHERE `SpellId` IN (340540);
INSERT INTO `spell_proc` (`SpellId`,`SchoolMask`,`SpellFamilyName`,`SpellFamilyMask0`,`SpellFamilyMask1`,`SpellFamilyMask2`,`SpellFamilyMask3`,`ProcFlags`,`ProcFlags2`,`SpellTypeMask`,`SpellPhaseMask`,`HitMask`,`AttributesMask`,`DisableEffectsMask`,`ProcsPerMinute`,`Chance`,`Cooldown`,`Charges`) VALUES
(340540,0x00,7,0x00000000,0x00000000,0x00000000,0x00000000,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0,0,0,0); -- Ursine Vigor

DELETE FROM spell_script_names WHERE spell_id = 340555;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (340555, 'spell_well_honed_instincts');
DELETE FROM spell_script_names WHERE spell_id = 340694;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (340694, 'spell_sudden_ambush');
