/*
 * This file is part of the TrinityCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

// This is where scripts' loading functions should be declared:

// The name of this function should match:
// void Add${NameOfDirectory}Scripts()
void AddSC_LoginScript();
void AddSC_MallScripts();
void AddSC_item_upgrader();
void AddSC_MaelstromDungeon();
void AddSC_AutoLootSystem();
void AddSC_MagicStone();
void AddSC_npc_currency_exchange();
void AddSC_Crapopolis();
void AddSC_Skyhold();
void AddSC_CustomInstanceScript();
void AddSC_cs_custom();
void AddSC_NetherlightTemple();
void AddSC_Niskara();
void AddSC_item_enhancement_system();
void AddSC_TelegrusRift();
void AddSC_NazmirCustom();
void AddSC_Occularus();
void AddSC_PeakOfSerenity();
void AddSC_LostGlacier();
void AddSC_ElarianSanctuary();
void AddSC_ShadoPanMonastary();
void AddSC_LightDungeon3();
void AddSC_DailyRewardsSystem();
void AddSC_Torghast();
void AddSC_StabilityTest();
void AddSC_MawFinale();
void AddSC_TheUnderrot();
void AddSC_EyeOfAzshara();
void AddSC_DreadscarRift();
void AddSC_IronDocks();
void AddSC_Folnuna();
void AddSC_Meto();
void AddSC_Sotanathor();
void AddSC_WorldBosses();
// Dungeon Defense
void AddSC_DungeonDefenseMain();
void AddSC_DungeonDefenseAI();
void AddSC_DungeonDefenseItem();
void AddSC_DungeonDefensePlayer();
// Dungeons
void AddSC_CustomAffixes();
void AddSC_Desmotareon();
void AddSC_Desmotaeron_Spells();
void AddSC_boss_shirgantai();
void AddSC_instance_desmotareon();
void AddSC_boss_xarvius();
void AddSC_boss_maleakos();
void AddSC_boss_general_nephmir();
void AddSC_boss_ecidus();
// nazjatar
void AddSC_instance_nazjatar();
void AddSC_boss_khada();
void AddSC_boss_aartoszu();
void AddSC_boss_blackwater_behemoth();
void AddSC_boss_tarco();
void AddSC_boss_shassera();
void AddSC_boss_dhrana();
void AddSC_nazjatar();

// Items
void AddSC_item_currency_exchange();
void AddSC_npc_1v1arena();
void AddSC_GMTavern();
void AddSC_QuelTest();

// hoa
void AddSC_instance_halls_of_attonement();
void AddSC_halls_of_attonement();

void AddCustomScripts()
{
    AddSC_LoginScript();
    AddSC_MallScripts();
    AddSC_item_upgrader();
    AddSC_MaelstromDungeon();
    AddSC_AutoLootSystem();
    AddSC_MagicStone();
    AddSC_npc_currency_exchange();
    AddSC_Crapopolis();
    AddSC_Skyhold();
    AddSC_CustomInstanceScript();
    AddSC_cs_custom();
    AddSC_NetherlightTemple();
    AddSC_Niskara();
    AddSC_item_enhancement_system();
    AddSC_TelegrusRift();
    AddSC_NazmirCustom();
    AddSC_Occularus();
    AddSC_PeakOfSerenity();
    AddSC_LostGlacier();
    AddSC_ElarianSanctuary();
    AddSC_ShadoPanMonastary();
    AddSC_LightDungeon3();
    AddSC_DailyRewardsSystem();
    AddSC_Torghast();
    AddSC_StabilityTest();
    AddSC_MawFinale();
    AddSC_TheUnderrot();
    AddSC_EyeOfAzshara();
    AddSC_DreadscarRift();
    AddSC_IronDocks();
    AddSC_Folnuna();
    AddSC_Meto();
    AddSC_Sotanathor();
    AddSC_WorldBosses();
    // Dungeon Defense
    AddSC_DungeonDefenseMain();
    AddSC_DungeonDefenseAI();
    AddSC_DungeonDefenseItem();
    AddSC_DungeonDefensePlayer();
    // Dungs
    AddSC_CustomAffixes();
    AddSC_Desmotareon();
    AddSC_Desmotaeron_Spells();
    AddSC_boss_shirgantai();
    AddSC_instance_desmotareon();
    AddSC_boss_xarvius();
    AddSC_boss_maleakos();
    AddSC_boss_general_nephmir();
    AddSC_boss_ecidus();
    // nazjatar
    AddSC_instance_nazjatar();
    AddSC_boss_khada();
    AddSC_boss_aartoszu();
    AddSC_boss_blackwater_behemoth();
    AddSC_boss_tarco();
    AddSC_boss_shassera();
    AddSC_boss_dhrana();
    AddSC_nazjatar();
    // Items
    AddSC_item_currency_exchange();
    AddSC_npc_1v1arena();
    AddSC_GMTavern();
    AddSC_QuelTest();

    // hoa
    AddSC_instance_halls_of_attonement();
    AddSC_halls_of_attonement();
}
