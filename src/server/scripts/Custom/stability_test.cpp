/*
* Copyright (C) 2008-2012 TrinityCore <http://www.trinitycore.org/>
* Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
* Copyright (C) 2014-2018 RoG_WoW Source  <http://wow.rog.snet
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

#include <ScriptMgr.h>
#include "Channel.h"
#include "ChannelMgr.h"
#include "WorldSession.h"
#include "Player.h"
#include "SpellMgr.h"
#include "MotionMaster.h"
#include "CovenantMgr.h"
#include "SpellHistory.h"

#include <sstream>

class StabilityTest : public PlayerScript
{
public:
    StabilityTest() : PlayerScript("StabilityTest") {}

    enum eSpell
    {
        SPELL_TEST_HEAL = 5174
    };

    std::map<uint32, uint32> m_RandomEventTimer;

    void OnLogin(Player* player, bool /*firstLogin*/)
    {
        if (player->GetSession()->IsStabilityTest())
        {
            if (ChannelMgr* cMgr = ChannelMgr::ForTeam(player->GetTeam()))
                if (Channel* chn = cMgr->GetJoinChannel(0, "world"))
                    chn->JoinChannel(player, "");

            player->SetCommandStatusOn(CHEAT_GOD);

            m_RandomEventTimer[player->GetGUID().GetCounter()] = 1000;
        }
    }

    void OnUpdate(Player* player, uint32 diff)
    {
        if (!player || !player->GetSession())
            return;

        if (!player->GetSession()->IsStabilityTest())
            return;

        if (auto dimmy = player->FindNearestCreature(175450, 250.0f))
        {
            if (player->GetDistance(dimmy) >= 5.0f)
                player->GetMotionMaster()->MoveCloserAndStop(0, dimmy, 3.0f);
            else
            {
                player->Attack(dimmy, true);

                auto wep = player->GetWeaponForAttack(BASE_ATTACK);
                if (!wep)
                    player->StoreNewItemInBestSlots(182408, 2);

                if (player->HasUnitState(UNIT_STATE_CASTING))
                    return;

                if (player->GetCovenant()->GetCovenantID() != CovenantID::NightFae)
                {
                    player->GetCovenantMgr()->SetCovenant(CovenantID::NightFae);
                    player->GetCovenantMgr()->SetSoulbind(SoulbindID::Korayn);
                }

                for (auto spell : { 323639, 258920, 198013, 188499,  210152, 201427, 191427, 162794, 162243,  })
                {
                    if (!player->GetSpellHistory()->HasCooldown(spell))
                        if (player->CastSpell(player->GetSelectedUnit(), spell) == SPELL_CAST_OK)
                            break;
                }
            }
        }

        auto itr = m_RandomEventTimer.find(player->GetGUID().GetCounter());
        if (itr == m_RandomEventTimer.end())
            return;

        if (player->HasUnitState(UNIT_STATE_CASTING))
            return;

        if (itr->second < diff)
        {
            switch (urand(0, 10))
            {
                case 0:
                {
                    std::ostringstream text;
                    text << "[SAY] StabilityTest bot " << player->GetGUID().GetCounter();
                    player->Say(text.str(), Language::LANG_UNIVERSAL);
                    break;
                }
                case 1:
                {
                    std::ostringstream text;
                    text << "[CHANNEL] StabilityTest bot " << player->GetGUID().GetCounter();

                    if (ChannelMgr* channelManager = ChannelMgr::ForTeam(player->GetTeam()))
                    {
                        if (Channel* channel = channelManager->GetChannel(0, "world", player))
                            channel->Say(player->GetGUID(), text.str().c_str(), Language::LANG_UNIVERSAL);
                    }
                    break;
                }
                case 2:
                {
                    player->CastSpell(player, SPELL_TEST_HEAL, false);
                    break;
                }
                case 3:
                {
                    break;
                }
                default:
                {
                    //Position pos;
                    //pos = player->GetRandomNearPosition(150.0f);
                    //player->GetMotionMaster()->MovePoint(0, pos, true);
                    break;
                }
            }

            itr->second = 2000;
        }
        else
            itr->second -= diff;
    }
};

#ifndef __clang_analyzer__
void AddSC_StabilityTest()
{
    new StabilityTest();
};
#endif
