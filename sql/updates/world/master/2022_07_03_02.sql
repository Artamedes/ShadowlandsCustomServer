-- hoa
UPDATE creature_template set ScriptName = 'npc_depraved_obliterator_165414' WHERE entry = 165414;
UPDATE creature_template set ScriptName = 'npc_sinstone_statue_165737' WHERE entry = 165737;

UPDATE creature_template SET ScriptName = 'boss_lord_chamberlain' WHERE entry = 164218;
UPDATE creature_template SET ScriptName = 'boss_echelon' WHERE entry = 164185;
UPDATE creature_template SET ScriptName = 'boss_high_adjudicator_aleez' WHERE entry = 165410;
UPDATE creature_template SET ScriptName = 'boss_halkias' WHERE entry = 165408;

REPLACE INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `SoundPlayType`, `BroadcastTextId`, `TextRange`, `comment`) VALUES (164218, 12, 0, 'Feel the weight of your sins.', 14, 0, 100, 0, 0, 0, 0, 0, 0, 'Lord Chamberlain to Player');

UPDATE creature SET wander_distance = 0, movementtype = 0 WHERE guid IN (459221, 459219);

DELETE FROM `creature_template_movement` WHERE `CreatureId`=175577;
INSERT INTO `creature_template_movement` (`CreatureId`, `Ground`, `Swim`, `Flight`, `Rooted`, `Chase`, `Random`, `InteractionPauseTimer`) VALUES (175577, 0, 0, 1, 0, 0, 0, 0);


UPDATE `areatrigger_create_properties` SET `ScriptName`='at_blood_torrent' WHERE  `Id`=19355;

UPDATE creature_template set ScriptName = 'npc_empty_anima_vessel_166034' WHERE entry = 166034;


DELETE FROM spell_script_names WHERE spell_id = 329340;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (329340, 'spell_anima_fountain');

