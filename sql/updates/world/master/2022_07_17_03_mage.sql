
DELETE FROM spell_script_names WHERE spell_id = 336821;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (336821, 'spell_infernal_cascade');

DELETE FROM `spell_proc` WHERE `SpellId` IN (336821);