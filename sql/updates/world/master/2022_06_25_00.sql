-- sham
DELETE FROM spell_script_names WHERE spell_id = 328923;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (328923, 'spell_fae_transfusion');

DELETE FROM spell_script_names WHERE spell_id = 328930 ;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (328930 , 'spell_fae_transfusion_heal');

DELETE FROM spell_script_names WHERE spell_id = 328928;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (328928, 'spell_fae_transfusion_dmg');
