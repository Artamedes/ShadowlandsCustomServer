-- SKYREACH SCRIPTING
REPLACE INTO `instance_template` (`map`, `parent`, `script`) VALUES (1209, 0, 'instance_Skyreach');


UPDATE creature_template SET scriptname = 'npc_reshad_81273', vehicleid = 0 WHERE entry = 81273;
UPDATE creature_template SET scriptname = 'npc_dread_raven_81204', vehicleid = 3623 WHERE entry = 81204;

UPDATE `creature_template` SET `flags_extra`='128' WHERE  `entry`=76119;

REPLACE INTO `creature_template_movement` (`CreatureId`, `Ground`, `Swim`, `Flight`, `Rooted`, `Chase`, `Random`, `InteractionPauseTimer`) VALUES 
(81081, 0, 0, 1, 0, 0, 0, 0),
(76143, 0, 0, 1, 0, 0, 0, 0),
(84782, 0, 0, 1, 0, 0, 0, 0),
(81088, 0, 0, 1, 0, 0, 0, 0),
(81080, 0, 0, 1, 0, 0, 0, 0),
(81081, 0, 0, 1, 0, 0, 0, 0),
(81049, 0, 0, 1, 0, 0, 0, 0),
(81049, 0, 0, 1, 0, 0, 0, 0),
(76121, 0, 0, 1, 0, 0, 0, 0),
(76367, 0, 0, 1, 0, 0, 0, 0),
(79093, 0, 0, 1, 0, 0, 0, 0);

REPLACE INTO spell_script_names (spell_id, scriptname) VALUES (154177, 'spell_VisualEnergize2');
REPLACE INTO spell_script_names (spell_id, scriptname) VALUES (154159, 'spell_VisualEnergize');
REPLACE INTO spell_script_names (spell_id, scriptname) VALUES (153315, 'spell_Windwall');
REPLACE INTO spell_script_names (spell_id, scriptname) VALUES (156793, 'spell_FourWind');

REPLACE INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) VALUES (75964, 0, 0, 'I will slice the flesh from your bones!', 14, 0, 100, 0, 0, 0, 0, 0, '');
REPLACE INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) VALUES (75964, 0, 1, 'You cannot outrun the wind!', 14, 0, 100, 0, 0, 0, 0, 0, '');
REPLACE INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) VALUES (75964, 0, 2, 'I... perish....', 14, 0, 100, 0, 0, 0, 0, 0, '');
