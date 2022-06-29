-- keg of heavens
DELETE FROM spell_script_names WHERE spell_id = 366792;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (366792, 'spell_keg_of_the_heavens');

DELETE FROM spell_script_names WHERE spell_id = 366779;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (366779, 'spell_heal_the_soul');

DELETE FROM disables WHERE sourcetype = 0 AND entry IN (207400, 207401, 366779);