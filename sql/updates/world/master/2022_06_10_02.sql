-- 
DELETE FROM spell_script_names WHERE spell_id IN (367804, 367805);
insert INTO spell_script_names (spell_id, scriptname) VALUES
(367804, 'spell_item_cache_of_acquired_treasures'),
(367805, 'spell_item_cache_of_acquired_treasures_use');
DELETE FROM spell_script_names WHERE spell_id = 368649;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (368649, 'spell_acquired_sword');
DELETE FROM spell_script_names WHERE spell_id = 368650;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (368650, 'spell_acquired_axe');
