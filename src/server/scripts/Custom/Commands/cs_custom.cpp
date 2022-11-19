#include "ScriptMgr.h"
#include "Chat.h"
#include "WorldSession.h"
#include "Player.h"
#include "ChatCommand.h"
#include "GossipDef.h"
#include "ScriptedGossip.h"
#include "HotfixDatabase.h"
#include "DB2Stores.h"
#include "CovenantPackets.h"
#include "QuestPackets.h"
#include "../MagicStone.h"
#include "CustomInstanceScript.h"
#include "../DungeonDefense/DungeonDefense.h"
#include "Item.h"
#include "QueryPackets.h"
#include "GameTime.h"
#include "LootMgr.h"
#include "SpellFormulaOverride.h"
#include "Torghast/AnimaPower.h"
#include "MiscPackets.h"

#ifdef WIN32
#include "windows.h"
#endif

using namespace Trinity::ChatCommands;

class cs_custom : public CommandScript
{
public:
    cs_custom() : CommandScript("cs_custom") { }

    ChatCommandTable GetCommands() const override
    {
        static ChatCommandTable commandTable =
        {
            { "start",            HandleStartCommand,          rbac::RBAC_PERM_INSTANT_LOGOUT,          Console::No },
            { "magicstone",       HandleReloadMagicStone,      rbac::RBAC_PERM_COMMAND_RELOAD_ALL_ITEM, Console::No },
            { "dungeon_defense",  HandleReloadDungeonDefense,  rbac::RBAC_PERM_COMMAND_RELOAD_ALL_ITEM, Console::No },
            { "instance_respawn", HandleReloadInstanceRespawn, rbac::RBAC_PERM_COMMAND_RELOAD_ALL_ITEM, Console::No },
            { "testpacket",       HandleTestCommand,           rbac::RBAC_PERM_COMMAND_RELOAD_ALL_ITEM, Console::No },
            { "testpacket2",      HandleTest2Command,          rbac::RBAC_PERM_COMMAND_RELOAD_ALL_ITEM, Console::No },
            { "testpacket3",      HandleTest3Command,          rbac::RBAC_PERM_COMMAND_RELOAD_ALL_ITEM, Console::No },
            { "testpacket4",      HandleTest4Command,          rbac::RBAC_PERM_COMMAND_RELOAD_ALL_ITEM, Console::No },
            { "testpacket5",      HandleTest5Command,          rbac::RBAC_PERM_COMMAND_RELOAD_ALL_ITEM, Console::No },
            { "testpacket6",      HandleTest6Command,          rbac::RBAC_PERM_COMMAND_RELOAD_ALL_ITEM, Console::No },
            { "testplayercondition",      HandleTestPlayerConditionCommand,          rbac::RBAC_PERM_COMMAND_RELOAD_ALL_ITEM, Console::No },
            { "commentator",      HandleCommentatorCommand,    rbac::RBAC_PERM_COMMAND_GM, Console::No },
            { "giveloot",         HandleGiveLootCommand,       rbac::RBAC_PERM_COMMAND_RELOAD_ALL_ITEM, Console::No },
            { "spellformulas",    HandleModifySpellFormulas,   rbac::RBAC_PERM_COMMAND_RELOAD_ALL_ITEM, Console::No },
            { "ilogout",           HandleLogoutCommand,   rbac::RBAC_PERM_COMMAND_RELOAD_ALL_ITEM, Console::No },
            { "animareset",     HandleResetAnima,   rbac::RBAC_PERM_COMMAND_RELOAD_ALL_ITEM, Console::No },
            { "SetAnimaPowerChoice",     HandleSetAnimaPowerChoice,   rbac::RBAC_PERM_COMMAND_RELOAD_ALL_ITEM, Console::No },

#ifdef WIN32
            { "gpscopy", HandleGPSCopyCommand,  rbac::RBAC_PERM_COMMAND_RELOAD_ALL_ITEM, Console::No },
#endif

        };
        return commandTable;
    }

    static bool HandleSetAnimaPowerChoice(ChatHandler* handler, uint32 mawPowerId)
    {
        auto player = handler->GetPlayer();

        handler->PSendSysMessage("Generating maw power id for %u", mawPowerId);

        if (auto choice = player->GetAnimaPowerChoice())
        {
            choice->GeneratePowers(player, mawPowerId);
            WorldPackets::Quest::DisplayPlayerChoice packet;
            choice->BuildPacket(packet);
            player->PlayerTalkClass->GetInteractionData().Reset();
            player->PlayerTalkClass->GetInteractionData().PlayerChoiceId = 573;
            player->SendDirectMessage(packet.Write());
        }
        return true;
    }

    static bool HandleResetAnima(ChatHandler* handler)
    {
        handler->GetPlayer()->ResetAnimaPowerChoice();
        return true;
    }

    static bool HandleLogoutCommand(ChatHandler* handler)
    {
        handler->GetSession()->LogoutPlayer(true);
        return true;
    }

    static bool HandleModifySpellFormulas(ChatHandler* handler, Optional<uint32> SpellId)
    {
        if (SpellId.has_value())
        {
            if (auto spellInfo = sSpellMgr->GetSpellInfo(*SpellId))
            {
                handler->PSendSysMessage("Modifying formula for %u %s", *SpellId, spellInfo->SpellName->Str[0]);
                sSpellFormulaOverride->CreateMenuForSpell(handler->GetPlayer(), spellInfo);
            }
            return true;
        }

        sSpellFormulaOverride->CreateMenu(handler->GetPlayer());
        return true;
    }

    static bool HandleTestPlayerConditionCommand(ChatHandler* handler, uint32 PlayerConditionID)
    {
        if (auto condition = sPlayerConditionStore.LookupEntry(PlayerConditionID))
        {
            if (ConditionMgr::IsPlayerMeetingCondition(handler->getSelectedPlayerOrSelf(), condition))
                handler->PSendSysMessage("Meets %u", PlayerConditionID);
            else
                handler->PSendSysMessage("Not Meet %u", PlayerConditionID);
        }
        else
            handler->PSendSysMessage("Not Found %u", PlayerConditionID);
        return true;
    }

    static bool HandleGiveLootCommand(ChatHandler* handler, uint32 ReferenceLootId)
    {
        auto selectedPlayerOrSelf = handler->getSelectedPlayerOrSelf();

        auto loot = LootTemplates_Reference.GetLootFor(ReferenceLootId);
        if (!loot)
        {
            handler->PSendSysMessage("Not Exists Reference loot %u", ReferenceLootId);
            return true;
        }

        handler->PSendSysMessage("Giving %s loot %u", selectedPlayerOrSelf->GetName().c_str(), ReferenceLootId);

        Loot personalLoot(selectedPlayerOrSelf->GetMap(), selectedPlayerOrSelf->GetGUID(), LootType::LOOT_CORPSE, nullptr);
        //personalLoot.clear();
        if (personalLoot.FillLoot(ReferenceLootId, LootTemplates_Reference, selectedPlayerOrSelf, true, true, LOOT_MODE_DEFAULT, ItemContext::NONE, true, true))
        {
            auto index = 0;
            for (auto item : personalLoot.items)
            {
                selectedPlayerOrSelf->StoreLootItem(ObjectGuid::Empty, index, &personalLoot);
                ++index;
                if (item.type == LootItemType::Currency)
                {
                    //selectedPlayerOrSelf->ModifyCurrency(item.itemid, item.count);
                    handler->PSendSysMessage("Adding Currency %u x%u", item.itemid, (uint32)item.count);
                }
                else if (item.type == LootItemType::Item)
                {
                    handler->PSendSysMessage("Adding %s x%u", Item::GetItemLink(item.itemid).c_str(), (uint32)item.count);
                    //if (!selectedPlayerOrSelf->StoreNewItem(item.itemid, item.count))
                    {
                       // handler->PSendSysMessage("Sent to mailbox %s x%u", Item::GetItemLink(item.itemid).c_str(), (uint32)item.count);
                       // selectedPlayerOrSelf->SendItemRetrievalMail(item.itemid, (uint32)item.count, ItemContext::NONE);
                    }
                }
            }
        }


        return true;
    }

    static bool HandleCommentatorCommand(ChatHandler* handler, uint32 Action)
    {
        auto player = handler->GetPlayer();

        // This opcode can be used in three ways:
        // 0 - Request to turn commentator mode off
        // 1 - Request to turn commentator mode on
        // 2 - Request to toggle current commentator mode status
        switch (Action)
        {
            case 0:
                player->RemovePlayerFlag(PLAYER_FLAGS_COMMENTATOR | PLAYER_FLAGS_COMMENTATOR_UBER);
                break;
            case 1:
                player->SetPlayerFlag(PLAYER_FLAGS_COMMENTATOR | PLAYER_FLAGS_COMMENTATOR_UBER);
                break;
            case 2:
                player->ReplaceAllPlayerFlags(PLAYER_FLAGS_COMMENTATOR | PLAYER_FLAGS_COMMENTATOR_UBER);
                break;
            default:
                TC_LOG_ERROR("network.opcode", "WorldSession::HandleCommentatorModeOpcode: player %d sent an invalid commentator mode action", player->GetGUID().GetCounter());
                break;
        }
        return true;
    }

    static bool HandleTest6Command(ChatHandler* handler)
    {
        handler->GetPlayer()->SendPetTameFailure(PetTameFailureReason::PET_TAME_FAILURE_ACTIVE_SUMMON);
        handler->PSendSysMessage("ok done");

        if (true)
            return true;
        auto item = handler->GetPlayer()->GetItemByEntry(187219);
        WorldPackets::Misc::WeeklyRewardsResult packet;
        packet.TotalVaults = 8;
        packet.Vaults.resize(5);

        packet.Vaults[0].UnkUInt32 = 82;
        packet.Vaults[0].Rewards.resize(1);
        packet.Vaults[0].Rewards[0].UnkItemInt1 = 1;
        packet.Vaults[0].Rewards[0].Count = 1;
        packet.Vaults[0].Rewards[0].UnkInt64 = 4611686067268333540;
        packet.Vaults[0].Rewards[0].OpenTime = 1661272108;

        if (auto item = handler->GetPlayer()->GetItemByEntry(186815))
        {
            auto itemInst = WorldPackets::Item::ItemInstance();
            itemInst.Initialize(item);
            packet.Vaults[0].Rewards[0].Item = itemInst;
        }

        packet.Vaults[1].UnkUInt32 = 81;
        packet.Vaults[1].Rewards.resize(1);
        packet.Vaults[1].Rewards[0].UnkItemInt1 = 1;
        packet.Vaults[1].Rewards[0].Count = 1;
        packet.Vaults[1].Rewards[0].UnkInt64 = 4611686067268333519;
        packet.Vaults[1].Rewards[0].OpenTime = 1661272108;

        if (item = handler->GetPlayer()->GetItemByEntry(187219))
        {
            auto itemInst = WorldPackets::Item::ItemInstance();
            itemInst.Initialize(item);
            packet.Vaults[1].Rewards[0].Item = itemInst;
        }

        packet.Vaults[2].UnkUInt32 = 83;
        packet.Vaults[2].Rewards.resize(1);
        packet.Vaults[2].Rewards[0].UnkItemInt1 = 1;
        packet.Vaults[2].Rewards[0].Count = 1;
        packet.Vaults[2].Rewards[0].UnkInt64 = 4611686067268333547;
        packet.Vaults[2].Rewards[0].OpenTime = 1661272108;

        if (item = handler->GetPlayer()->GetItemByEntry(187219))
        {
            auto itemInst = WorldPackets::Item::ItemInstance();
            itemInst.Initialize(item);
            packet.Vaults[2].Rewards[0].Item = itemInst;
        }

        packet.Vaults[3].UnkUInt32 = 84;
        packet.Vaults[3].Rewards.resize(1);
        packet.Vaults[3].Rewards[0].UnkItemInt1 = 1;
        packet.Vaults[3].Rewards[0].Count = 1;
        packet.Vaults[3].Rewards[0].UnkInt64 = 4611686067268333551;
        packet.Vaults[3].Rewards[0].OpenTime = 1661272108;

        if (item = handler->GetPlayer()->GetItemByEntry(187219))
        {
            auto itemInst = WorldPackets::Item::ItemInstance();
            itemInst.Initialize(item);
            packet.Vaults[3].Rewards[0].Item = itemInst;
        }

        packet.Vaults[4].UnkUInt32 = 87;
        packet.Vaults[4].Rewards.resize(1);
        packet.Vaults[4].Rewards[0].UnkItemInt1 = 1;
        packet.Vaults[4].Rewards[0].Count = 6;
        packet.Vaults[4].Rewards[0].UnkInt64 = 4611686067268333555;
        packet.Vaults[4].Rewards[0].OpenTime = 1661272108;

        if (item = handler->GetPlayer()->GetItemByEntry(187219))
        {
            auto itemInst = WorldPackets::Item::ItemInstance();
            itemInst.Initialize(item);
            packet.Vaults[4].Rewards[0].Item = itemInst;
        }

        handler->GetSession()->SendPacket(packet.Write());

        {
            WorldPackets::Misc::WeeklyRewardsProgressResult result;

            result.UnkInt321 = 0;
            result.UnkInt323 = 7;
            result.VaultProgresses.resize(9);
            result.VaultProgresses[0].Index = 78;
            result.VaultProgresses[1].Index = 79;
            result.VaultProgresses[2].Index = 80;
            result.VaultProgresses[3].Index = 81;
            result.VaultProgresses[3].TotalCompleted = 0;
            result.VaultProgresses[3].UnkInt3 = -1;
            result.VaultProgresses[4].Index = 82;
            result.VaultProgresses[4].TotalCompleted = 0;
            result.VaultProgresses[4].UnkInt3 = -1;
            result.VaultProgresses[5].Index = 83;
            result.VaultProgresses[5].TotalCompleted = 0;
            result.VaultProgresses[5].UnkInt3 = -1;
            result.VaultProgresses[6].Index = 84;
            result.VaultProgresses[7].Index = 85;
            result.VaultProgresses[8].Index = 86;

            for (int i = 6; i <= 8; ++i)
            {
                result.VaultProgresses[i].UnkVaultVec.resize(31);
                result.VaultProgresses[i].UnkVaultVec[0].Unk1 = 2406;
                result.VaultProgresses[i].UnkVaultVec[0].Unk2 = 0;
                result.VaultProgresses[i].UnkVaultVec[1].Unk1 = 2405;
                result.VaultProgresses[i].UnkVaultVec[1].Unk2 = 0;
                result.VaultProgresses[i].UnkVaultVec[2].Unk1 = 2412;
                result.VaultProgresses[i].UnkVaultVec[2].Unk2 = 0;
                result.VaultProgresses[i].UnkVaultVec[3].Unk1 = 2407;
                result.VaultProgresses[i].UnkVaultVec[3].Unk2 = 0;
                result.VaultProgresses[i].UnkVaultVec[4].Unk1 = 2399;
                result.VaultProgresses[i].UnkVaultVec[4].Unk2 = 0;
                result.VaultProgresses[i].UnkVaultVec[5].Unk1 = 2398;
                result.VaultProgresses[i].UnkVaultVec[5].Unk2 = 0;
                result.VaultProgresses[i].UnkVaultVec[6].Unk1 = 2417;
                result.VaultProgresses[i].UnkVaultVec[6].Unk2 = 0;
                result.VaultProgresses[i].UnkVaultVec[7].Unk1 = 2418;
                result.VaultProgresses[i].UnkVaultVec[7].Unk2 = 0;
                result.VaultProgresses[i].UnkVaultVec[8].Unk1 = 2402;
                result.VaultProgresses[i].UnkVaultVec[8].Unk2 = 0;
                result.VaultProgresses[i].UnkVaultVec[9].Unk1 = 2383;
                result.VaultProgresses[i].UnkVaultVec[9].Unk2 = 0;
                result.VaultProgresses[i].UnkVaultVec[10].Unk1 = 2433;
                result.VaultProgresses[i].UnkVaultVec[10].Unk2 = 0;
                result.VaultProgresses[i].UnkVaultVec[11].Unk1 = 2431;
                result.VaultProgresses[i].UnkVaultVec[11].Unk2 = 0;
                result.VaultProgresses[i].UnkVaultVec[12].Unk1 = 2422;
                result.VaultProgresses[i].UnkVaultVec[12].Unk2 = 0;
                result.VaultProgresses[i].UnkVaultVec[13].Unk1 = 2432;
                result.VaultProgresses[i].UnkVaultVec[13].Unk2 = 0;
                result.VaultProgresses[i].UnkVaultVec[14].Unk1 = 2429;
                result.VaultProgresses[i].UnkVaultVec[14].Unk2 = 0;
                result.VaultProgresses[i].UnkVaultVec[15].Unk1 = 2430;
                result.VaultProgresses[i].UnkVaultVec[15].Unk2 = 0;
                result.VaultProgresses[i].UnkVaultVec[16].Unk1 = 2436;
                result.VaultProgresses[i].UnkVaultVec[16].Unk2 = 0;
                result.VaultProgresses[i].UnkVaultVec[17].Unk1 = 2435;
                result.VaultProgresses[i].UnkVaultVec[17].Unk2 = 0;
                result.VaultProgresses[i].UnkVaultVec[18].Unk1 = 2423;
                result.VaultProgresses[i].UnkVaultVec[18].Unk2 = 0;
                result.VaultProgresses[i].UnkVaultVec[19].Unk1 = 2434;
                result.VaultProgresses[i].UnkVaultVec[19].Unk2 = 0;
                result.VaultProgresses[i].UnkVaultVec[20].Unk1 = 2546;
                result.VaultProgresses[i].UnkVaultVec[20].Unk2 = 0;
                result.VaultProgresses[i].UnkVaultVec[21].Unk1 = 2553;
                result.VaultProgresses[i].UnkVaultVec[21].Unk2 = 0;
                result.VaultProgresses[i].UnkVaultVec[22].Unk1 = 2549;
                result.VaultProgresses[i].UnkVaultVec[22].Unk2 = 0;
                result.VaultProgresses[i].UnkVaultVec[23].Unk1 = 2544;
                result.VaultProgresses[i].UnkVaultVec[23].Unk2 = 0;
                result.VaultProgresses[i].UnkVaultVec[24].Unk1 = 2529;
                result.VaultProgresses[i].UnkVaultVec[24].Unk2 = 0;
                result.VaultProgresses[i].UnkVaultVec[25].Unk1 = 2543;
                result.VaultProgresses[i].UnkVaultVec[25].Unk2 = 0;
                result.VaultProgresses[i].UnkVaultVec[26].Unk1 = 2537;
                result.VaultProgresses[i].UnkVaultVec[26].Unk2 = 0;
                result.VaultProgresses[i].UnkVaultVec[27].Unk1 = 2540;
                result.VaultProgresses[i].UnkVaultVec[27].Unk2 = 0;
                result.VaultProgresses[i].UnkVaultVec[28].Unk1 = 2539;
                result.VaultProgresses[i].UnkVaultVec[28].Unk2 = 0;
                result.VaultProgresses[i].UnkVaultVec[29].Unk1 = 2512;
                result.VaultProgresses[i].UnkVaultVec[29].Unk2 = 0;
                result.VaultProgresses[i].UnkVaultVec[30].Unk1 = 2542;
                result.VaultProgresses[i].UnkVaultVec[30].Unk2 = 0;
            }

            handler->GetSession()->SendPacket(result.Write());
        }

        return true;
    }

    static bool HandleReloadDungeonDefense(ChatHandler* handler)
    {
        handler->PSendSysMessage("Reloading dungeon defense data, you may have to reset your instance");
        sDungeonDefenseMgr->LoadFromDB();
        return true;
    }

    static bool HandleTestCommand(ChatHandler* handler, Optional<uint32> CovenantID)
    {
        WorldPackets::Covenant::CovenantPreviewOpenNpc packet;
        packet.NpcGUID = handler->GetPlayer()->GetGUID();
        packet.CovenantID = CovenantID.value_or(0);
        handler->GetSession()->SendPacket(packet.Write());
        return true;
    }
    static bool HandleTest2Command(ChatHandler* handler, Optional<uint32> CovenantID)
    {
        WorldPacket data(SMSG_WORLD_MAP_OPEN_NPC, 20);
        data << handler->GetPlayer()->GetGUID();
        data << uint32(CovenantID.value_or(0));
        handler->GetSession()->SendPacket(&data);
        return true;
    }
    static bool HandleTest3Command(ChatHandler* handler, uint32 CovenantID)
    {
        handler->GetPlayer()->SetCurrentConfigID(CovenantID);
        return true;
    }
    static bool HandleTest4Command(ChatHandler* handler, Optional<uint32> flag)
    {
        auto player = handler->GetPlayer();
        WorldPackets::Quest::DisplayPlayerChoice displayPlayerChoice;

        displayPlayerChoice.SenderGUID = player->GetGUID();
        displayPlayerChoice.ChoiceID = 682925852;
        displayPlayerChoice.Question = "Are you sure you want to upgrade?";
        displayPlayerChoice.CloseChoiceFrame = false;
        displayPlayerChoice.HideWarboardHeader = false;
        displayPlayerChoice.KeepOpenAfterChoice = false;

        displayPlayerChoice.UiTextureKitID = 5260;
        displayPlayerChoice.SoundKitID = 80244; // 80244 brwaler upgrade

        for (int i = 0; i < 1; ++i)
        {
            WorldPackets::Quest::PlayerChoiceResponse playerChoiceResponse;

            playerChoiceResponse.ResponseID = 4412414;
            playerChoiceResponse.ResponseIdentifier = 335;
            playerChoiceResponse.Flags = 2;
            playerChoiceResponse.ChoiceArtFileID = flag.value_or(1274664);
            playerChoiceResponse.UiTextureKitID = 5487;
            playerChoiceResponse.Reward.emplace();
            playerChoiceResponse.RewardQuestID = 591918;
            if (i == 0)
            {
                playerChoiceResponse.Header = "Requirements";
                //playerChoiceResponse.SubHeader = "Requirements";
                playerChoiceResponse.ButtonTooltip = "Clicking this will consume the requirements!";
                playerChoiceResponse.Confirmation = "Confirmation";
                playerChoiceResponse.Flags = 0;
                playerChoiceResponse.Answer = "Requirements";
                playerChoiceResponse.ButtonTooltip = "|cffFF0000Not enough x...";
                playerChoiceResponse.SubHeader = "Consumes";
            }
            else
            {
                playerChoiceResponse.Header = "Rewards";
                //playerChoiceResponse.SubHeader = "Rewards";
                playerChoiceResponse.SubHeader = "Awards";
                playerChoiceResponse.Answer = "Upgrade";
                playerChoiceResponse.ButtonTooltip = "Are you sure you want to upgrade?";
                playerChoiceResponse.Confirmation = "Confirmation";
            }

            playerChoiceResponse.Reward.emplace();
            playerChoiceResponse.Reward->Money = 400000;
            for (int i = 0; i < 2; ++i)
            {
                if (auto item = player->GetItemByEntry(i == 0 ? 183021 : 175921))
                {

                    {
                        playerChoiceResponse.Reward->Items.emplace_back();
                        WorldPackets::Quest::PlayerChoiceResponseRewardEntry& rewardEntry = playerChoiceResponse.Reward->Items.back();
                        rewardEntry.Item.ItemID = item->GetEntry();
                        rewardEntry.Item.Initialize(item);
                    }
                }
            }

            playerChoiceResponse.Reward->Currencies.emplace_back();
            WorldPackets::Quest::PlayerChoiceResponseRewardEntry& rewardEntry = playerChoiceResponse.Reward->Currencies.back();
            rewardEntry.Item.ItemID = 1813;
            rewardEntry.Quantity = 500;

            displayPlayerChoice.Responses.push_back(playerChoiceResponse);
        }


        handler->GetSession()->SendPacket(displayPlayerChoice.Write());
        return true;
    }
    static bool HandleTest5Command(ChatHandler* handler, uint32 unk1, uint32 unk2, uint32 unk3)
    {   //
        //WorldPackets::Garrison::GarrisonResearchTalentResult result;
        //result.GarrTypeID = CovenantMgr::TheShadowlands;
        //result.UnkBit = true;
        //result.UnkInt1 = 0;
        //result.talent.GarrTalentID = 2078;
        //result.talent.Rank = 1;
        //result.talent.ResearchStartTime = 1662496826;
        //result.talent.Flags = 1;
        //
        //handler->GetSession()->SendPacket(result.Write());

        return true;
    }

    // Teleports and revives the player at their homebind.
    // Useful if the player somehow gets stuck.
    static bool HandleStartCommand(ChatHandler* handler)
    {
        auto player = handler->GetPlayer();
        player->TeleportTo(player->m_homebind, TELE_REVIVE_AT_TELEPORT);
        return true;
    }

#ifdef WIN32
    static bool HandleGPSCopyCommand(ChatHandler* handler, Optional<uint32> keep)
    {
        std::ostringstream ss;

        auto player = handler->GetPlayer();

        ss << "{ " << player->GetPositionX() << "f, " << player->GetPositionY() << "f, " << player->GetPositionZ() << "f, " << player->GetOrientation() << "f }, ";
        const char* output = ss.str().c_str();
        const size_t len = strlen(output) + 1;
        HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, len);
        memcpy(GlobalLock(hMem), output, len);
        GlobalUnlock(hMem);
        OpenClipboard(0);
        if (!keep.has_value())
            EmptyClipboard();
        SetClipboardData(CF_TEXT, hMem);
        CloseClipboard();
        handler->SendSysMessage(ss.str().c_str());
        return true;
    }
#endif

    static bool HandleReloadInstanceRespawn(ChatHandler* handler, char const* /*args*/)
    {
        TC_LOG_INFO("misc", "Reloading HandleReloadBroadcastText table...");
        handler->SendSysMessage("Loading broadcast_text");
        sCustomInstanceRespawn->LoadFromDB();
        return true;
    }

    static bool HandleReloadMagicStone(ChatHandler* handler, char const* /*args*/)
    {
        handler->SendSysMessage("Loading magic stone!");
        TC_LOG_INFO("misc", "Reloading HandleReloadMagicStone table...");
        sMagicStoneMgr->LoadFromDB();
        return true;
    }
};

void AddSC_cs_custom()
{
    new cs_custom();
}
