-- 
DELETE FROM spell_script_names WHERE spell_id = 323918;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (323918, 'spell_gristled_toes');

-- fix underrot difficulties
UPDATE `gameobject` SET `spawnDifficulties`='1,2,23,8' WHERE  map = 1841;

DELETE FROM spell_script_names WHERE spell_id = 351093;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (351093, 'spell_resilient_stitching');

DELETE FROM spell_script_names WHERE spell_id = 323919;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (323919, 'spell_gnashing_chompers');
