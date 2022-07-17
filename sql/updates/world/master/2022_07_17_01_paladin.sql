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
