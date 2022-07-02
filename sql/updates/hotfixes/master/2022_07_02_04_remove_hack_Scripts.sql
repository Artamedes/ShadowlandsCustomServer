-- remove hacks
DELETE FROM spell_script_names WHERE scriptname = 'spell_rog_slice_and_dice';
REPLACE INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (1943, 'aura_rog_rupture');
