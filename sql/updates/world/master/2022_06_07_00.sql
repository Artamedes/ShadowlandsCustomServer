-- 
UPDATE creature_template SET vignetteid = entry WHERE flags_extra & 268435456 and entry >= 700000;