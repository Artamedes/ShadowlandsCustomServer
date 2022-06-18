-- rogue fixes
REPLACE INTO spell_script_names (spell_id, scriptname) VALUE (315496, 'spell_slice_and_dice_sl');

DELETE FROM spell_script_names WHERE spell_id = 345569;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (345569, 'spell_flagellation_after');

DELETE FROM spell_script_names WHERE spell_id = 354703;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (354703, 'spell_obedience');

DELETE FROM spell_script_names WHERE spell_id = 343142;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (343142, 'spell_dreadblades');


DELETE FROM spell_script_names WHERE spell_id = 343145;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (343145, 'spell_dreadblades_self_dmg');
