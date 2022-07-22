
DELETE FROM spell_script_names WHERE spell_id = 355886;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (355886, 'spell_agony_gaze');

DELETE FROM spell_script_names WHERE spell_id = 342357;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (342357, 'spell_fodder_to_the_flame');

UPDATE creature_template SET scriptname = 'npc_condemed_demon', minlevel=60,maxlevel=60 WHERE entry IN (169421, 169425, 169426, 169428, 169429, 169430);
