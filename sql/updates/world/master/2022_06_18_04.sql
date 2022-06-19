-- more rogue fixes
DELETE FROM spell_script_names WHERE spell_id = 193315;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (193315, 'spell_sinister_strike');

DELETE FROM spell_script_names WHERE spell_id = 195627;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (195627, 'spell_opportunity');

DELETE FROM `spell_proc` WHERE `SpellId` IN (195627);
INSERT INTO `spell_proc` (`SpellId`,`SchoolMask`,`SpellFamilyName`,`SpellFamilyMask0`,`SpellFamilyMask1`,`SpellFamilyMask2`,`SpellFamilyMask3`,`ProcFlags`,`ProcFlags2`,`SpellTypeMask`,`SpellPhaseMask`,`HitMask`,`AttributesMask`,`DisableEffectsMask`,`ProcsPerMinute`,`Chance`,`Cooldown`,`Charges`) VALUES
(195627,0x01,8,0x00000000,0x00000000,0x00000000,0x00000000,0x0,0x0,0x1,0x2,0x0,0x0,0x0,0,101,0,0); -- Opportunity

DELETE FROM spell_script_names WHERE spell_id = 76806;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (76806, 'spell_mastery_main_gauche');

DELETE FROM spell_script_names WHERE spell_id = 364555;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (364555, 'spell_tornado_trigger');

DELETE FROM spell_script_names WHERE spell_id = 363592;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (363592, 'spell_tornado_trigger_4pc');

DELETE FROM spell_script_names WHERE spell_id = 185763;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (185763, 'spell_pistol_shot');

DELETE FROM spell_script_names WHERE spell_id = 340085;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (340085, 'spell_greenskins_wickers');

DELETE FROM spell_script_names WHERE spell_id = 340092;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (340092, 'spell_deathly_shadows');
