-- DEADLY DANCE

DELETE FROM spell_script_names WHERE spell_id = 363736;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (363736, 'spell_deadly_dance');

UPDATE `areatrigger_create_properties` SET `ScriptName`='at_dh_shattered_souls' WHERE  `Id`=3680;
UPDATE `areatrigger_create_properties` SET `ScriptName`='at_dh_shattered_souls' WHERE  `Id`=6659;