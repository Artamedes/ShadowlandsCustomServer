-- 
DELETE FROM spell_script_names WHERE spell_id = 200806;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (200806, 'spell_exsanguinate');

DELETE FROM spell_script_names WHERE spell_id = 115834;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (115834, 'spell_shroud_of_concealment');

REPLACE INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES ('210824', 'aura_mage_touch_of_the_magi');