-- fix dreadscar QUEST npc
UPDATE creature_template SET npcflag = 2 WHERE entry IN (703000);
UPDATE creature_template SET npcflag = 128 WHERE entry = 800002;