-- outlaw

DELETE FROM spell_script_names WHERE spell_id = 195457;
INSERT INTO spell_script_names (spell_id, scriptname) VALUE (195457, 'spell_grappling_hook');
DELETE FROM `jump_charge_params` WHERE `id`=541;
INSERT INTO `jump_charge_params` (`id`, `speed`, `treatSpeedAsMoveTimeSeconds`, `jumpGravity`, `spellVisualId`, `progressCurveId`, `parabolicCurveId`) VALUES (541, 0.56, 1, 19.2911, 106218, 0, 0);
