-- relentless inuqisitior
DELETE FROM spell_script_names WHERE spell_id = 337297;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (337297, 'spell_relentless_inquisitor');

DELETE FROM spell_script_names WHERE spell_id = 337831;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (337831, 'spell_holy_avengers_engraved_sigil');

UPDATE creature_template set ScriptName = 'npc_guardian_of_the_forgotten_queen_114565' WHERE entry = 114565;

DELETE FROM spell_script_names WHERE spell_id = 340459;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (340459, 'spell_maraads_dying_breath_proc');


DELETE FROM spell_script_names WHERE spell_id = 337825;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (337825, 'spell_shock_barrier');

DELETE FROM spell_script_names WHERE spell_id = 337824;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (337824, 'spell_shock_barrier_periodic');


DELETE FROM spell_script_names WHERE spell_id = 356890;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (356890, 'spell_pal_divine_toll');


DELETE FROM spell_script_names WHERE spell_id = 355098;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (355098, 'spell_divine_resonance');

DELETE FROM spell_script_names WHERE spell_id = 337682;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (337682, 'spell_the_magistrates_judgment_proc');
DELETE FROM spell_script_names WHERE spell_id = 337681;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (337681, 'spell_the_magistrates_judgment');

DELETE FROM spell_script_names WHERE spell_id = 337600;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (337600, 'spell_uthers_devotion');

DELETE FROM spell_script_names WHERE spell_id = 317866;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (317866, 'spell_sanctified_wrath');
DELETE FROM `spell_proc` WHERE `SpellId` IN (317866);
INSERT INTO `spell_proc` (`SpellId`,`SchoolMask`,`SpellFamilyName`,`SpellFamilyMask0`,`SpellFamilyMask1`,`SpellFamilyMask2`,`SpellFamilyMask3`,`ProcFlags`,`ProcFlags2`,`SpellTypeMask`,`SpellPhaseMask`,`HitMask`,`AttributesMask`,`DisableEffectsMask`,`ProcsPerMinute`,`Chance`,`Cooldown`,`Charges`) VALUES
(317866,0x00,10,0x00000000,0x00000000,0x00000000,0x00000000,0x0,0x4,0x0,0x2,0x0,0x0,0x0,0,0,0,0); -- Sanctified Wrath
