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
}
