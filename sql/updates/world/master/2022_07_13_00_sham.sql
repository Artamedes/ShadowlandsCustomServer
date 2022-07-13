-- shaman

DELETE FROM spell_script_names WHERE spell_id = 336735;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (336735, 'spell_chains_of_devastation');

DELETE FROM spell_script_names WHERE spell_id = 336736;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (336736, 'spell_chains_of_devastation_chain_lightning');

DELETE FROM spell_script_names WHERE spell_id = 336737;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (336737, 'spell_chains_of_devastation_chain_heal');

UPDATE creature_template SET scriptname = 'npc_greater_earth_elemental' WHERE entry = 95072;

UPDATE `areatrigger_template` SET `Flags`='4' WHERE  `Id`=8382 AND `IsServerSide`=0;