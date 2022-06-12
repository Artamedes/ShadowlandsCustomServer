-- spell fixes 6-11-22
DELETE FROM spell_script_names WHERE spell_id = 339371;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (339371, 'spell_expurgation');

DELETE FROM spell_script_names WHERE spell_id = 343527;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (343527, 'spell_execution_sentence');
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (343527, 'spell_execution_sentence_dmg');
-- buff arcane blast
DELETE FROM `z_spell_buffs` WHERE `SpellID`=44425;
INSERT INTO `z_spell_buffs` (`SpellID`, `Modifier`) VALUES (44425, 10);

DELETE FROM spell_script_names WHERE spell_id = 148022;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (148022, 'spell_icicle');
