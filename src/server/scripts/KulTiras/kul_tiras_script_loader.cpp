/*
 * Copyright (C) 2017-2018 AshamaneProject <https://github.com/AshamaneProject>
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

/// Free Hold
void AddSC_free_hold();
void AddSC_instance_free_hold();
void AddSC_boss_skycap_kragg();
void AddSC_boss_ring_of_booty();
void AddSC_boss_harlan_sweete();
void AddSC_boss_council_o_captains();

// The name of this function should match:
// void Add${NameOfDirectory}Scripts()
void AddKulTirasScripts()
{
    /// Free Hold
    AddSC_free_hold();
    AddSC_instance_free_hold();
	AddSC_boss_skycap_kragg();
	AddSC_boss_ring_of_booty();
	AddSC_boss_harlan_sweete();
	AddSC_boss_council_o_captains();
}
