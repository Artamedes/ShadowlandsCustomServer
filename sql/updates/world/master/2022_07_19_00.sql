-- 
DELETE FROM spell_script_names WHERE spell_id = 51514;
REPLACE INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (51514, 'aura_sha_hex');

REPLACE INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (199921, 'aura_trailblazer');

DELETE FROM `spell_proc` WHERE `SpellId` IN (336867);
INSERT INTO `spell_proc` (`SpellId`,`SchoolMask`,`SpellFamilyName`,`SpellFamilyMask0`,`SpellFamilyMask1`,`SpellFamilyMask2`,`SpellFamilyMask3`,`ProcFlags`,`ProcFlags2`,`SpellTypeMask`,`SpellPhaseMask`,`HitMask`,`AttributesMask`,`DisableEffectsMask`,`ProcsPerMinute`,`Chance`,`Cooldown`,`Charges`) VALUES
(336867,0x00,9,0x00000000,0x00000000,0x00000000,0x00000000,0x0,0x0,0x0,0x2,0x0,0x0,0x0,0,0,0,0); -- Surging Shots
