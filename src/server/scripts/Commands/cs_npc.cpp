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

/* ScriptData
Name: npc_commandscript
%Complete: 100
Comment: All npc related commands
Category: commandscripts
EndScriptData */

#include "ScriptMgr.h"
#include "Chat.h"
#include "ChatCommand.h"
#include "CreatureAI.h"
#include "CreatureGroups.h"
#include "DatabaseEnv.h"
#include "DB2Stores.h"
#include "FollowMovementGenerator.h"
#include "GameTime.h"
#include "Language.h"
#include "Loot.h"
#include "Map.h"
#include "MotionMaster.h"
#include "MovementDefines.h"
#include "ObjectAccessor.h"
#include "ObjectMgr.h"
#include "Pet.h"
#include "PhasingHandler.h"
#include "Player.h"
#include "RBAC.h"
#include "SmartEnum.h"
#include "Transport.h"
#include "World.h"
#include "WorldSession.h"
#include "WaypointManager.h"
#include "LootMgr.h"

#include "ScriptedGossip.h"

struct MenuDatas
{
    uint32 EntryID = 0;
    std::string Name = "";
    std::string SubName = "";
    uint32 FactionID = 35;
    uint32 DisplayId = 1337;
    float Scale = 1.0f;
    uint32 MinLevel = 60;
    uint32 MaxLevel = 60;
};

static std::unordered_map<ObjectGuid::LowType, MenuDatas> _menuData;


class npc_playerscript : public PlayerScript
{
    public:
        npc_playerscript() : PlayerScript("npc_playerscript") { }

        static void ShowMenu(Player* player)
        {
            ClearGossipMenuFor(player);

            MenuDatas& l_Menu = _menuData[player->GetGUID().GetCounter()];

            std::ostringstream ss;
            auto CreateMenuOptionWithAction([&](uint32 p_ActionId, std::string p_Name, std::string p_Value)
            {
                ss.str("");
                ss.clear();
                ss << p_Name << ": " << p_Value;
                AddGossipItemFor(player, GossipOptionNpc::None, ss.str(), 0, p_ActionId, "", 0, true);
            });

            CreateMenuOptionWithAction(1, "EntryId", std::to_string(l_Menu.EntryID));
            CreateMenuOptionWithAction(2, "Name", l_Menu.Name);
            CreateMenuOptionWithAction(3, "SubName", l_Menu.SubName);
            CreateMenuOptionWithAction(4, "FactionID", std::to_string(l_Menu.FactionID));
            CreateMenuOptionWithAction(5, "DisplayId", std::to_string(l_Menu.DisplayId));
            CreateMenuOptionWithAction(6, "Scale", std::to_string(l_Menu.Scale));
            CreateMenuOptionWithAction(9, "MinLevel", std::to_string(l_Menu.MinLevel));
            CreateMenuOptionWithAction(10, "MaxLevel", std::to_string(l_Menu.MaxLevel));
            AddGossipItemFor(player, GossipOptionNpc::None, "Create", 0, 7);
            AddGossipItemFor(player, GossipOptionNpc::None, "Create and Spawn", 0, 8);

            player->PlayerTalkClass->GetGossipMenu().SetMenuId(56818);
            SendGossipMenuFor(player, 1, player->GetGUID());
        }

        void OnGossipSelect(Player* player, uint32 menu_id, uint32 /*sender*/, uint32 action)
        {
            if (menu_id != 56818)
                return;

            ShowMenu(player);

            switch (action)
            {
                case 7:
                case 8:
                {
                    MenuDatas& l_Menu = _menuData[player->GetGUID().GetCounter()];
                    if (l_Menu.EntryID == 0)
                        return;
                    auto l_Exists = sObjectMgr->GetCreatureTemplate(l_Menu.EntryID) != nullptr;
                    if (l_Exists)
                    {
                        ChatHandler(player).PSendSysMessage("Prevented overwrite creature %u", l_Menu.EntryID);
                        return;
                    }

                    CloseGossipMenuFor(player);

                    auto l_Stmt = WorldDatabase.GetPreparedStatement(WORLD_REP_CREATURE_TEMPLATE);
                    l_Stmt->setUInt32(0, l_Menu.EntryID);
                    l_Stmt->setString(1, l_Menu.Name);
                    l_Stmt->setString(2, l_Menu.SubName);
                    l_Stmt->setUInt32(3, l_Menu.FactionID);
                    l_Stmt->setUInt32(4, 1);
                    l_Stmt->setUInt32(5, 0);
                    l_Stmt->setUInt32(6, l_Menu.MinLevel);
                    l_Stmt->setUInt32(7, l_Menu.MaxLevel);
                    WorldDatabase.Query(l_Stmt);

                    l_Stmt = WorldDatabase.GetPreparedStatement(WORLD_REP_CREATURE_TEMPLATE_MODEL);
                    l_Stmt->setUInt32(0, l_Menu.EntryID);
                    l_Stmt->setUInt32(1, 0);
                    l_Stmt->setUInt32(2, l_Menu.DisplayId);
                    l_Stmt->setFloat(3, l_Menu.Scale);
                    l_Stmt->setFloat(4, 1.0f);
                    WorldDatabase.Query(l_Stmt);


                    WorldDatabasePreparedStatement* stmt = WorldDatabase.GetPreparedStatement(WORLD_SEL_CREATURE_TEMPLATE);
                    stmt->setUInt32(0, l_Menu.EntryID);
                    stmt->setUInt32(1, 0);
                    PreparedQueryResult result = WorldDatabase.Query(stmt);

                    if (!result)
                    {
                        return;
                    }


                    sObjectMgr->LoadCreatureTemplate(result->Fetch());
                    sObjectMgr->LoadCreatureTemplateModel(l_Menu.EntryID);

                    ChatHandler(player).PSendSysMessage("%s \"%s\" with entry %u", (l_Exists ? "overwrote" : "created"), l_Menu.Name.c_str(), l_Menu.EntryID);

                    if (action == 8)
                    {
                       // npc_commandscript::HandleNpcAddCommand(&ChatHandler(player), l_Menu.EntryID);
                        auto id = l_Menu.EntryID;
                        if (!sObjectMgr->GetCreatureTemplate(id))
                            break;

                        Player* chr = player;
                        Map* map = chr->GetMap();

                        if (Transport* trans = dynamic_cast<Transport*>(chr->GetTransport()))
                        {
                            ObjectGuid::LowType guid = sObjectMgr->GenerateCreatureSpawnId();
                            CreatureData& data = sObjectMgr->NewOrExistCreatureData(guid);
                            data.spawnId = guid;
                            data.spawnGroupData = sObjectMgr->GetDefaultSpawnGroup();
                            data.id = id;
                            data.spawnPoint.Relocate(chr->GetTransOffsetX(), chr->GetTransOffsetY(), chr->GetTransOffsetZ(), chr->GetTransOffsetO());
                            if (Creature* creature = trans->CreateNPCPassenger(guid, &data))
                            {
                                creature->SaveToDB(trans->GetGOInfo()->moTransport.SpawnMap, { map->GetDifficultyID() });
                                sObjectMgr->AddCreatureToGrid(&data);
                            }
                            break;
                        }

                        Creature* creature = Creature::CreateCreature(id, map, chr->GetPosition());
                        if (!creature)break;

                        PhasingHandler::InheritPhaseShift(creature, chr);
                        creature->SaveToDB(map->GetId(), { map->GetDifficultyID() });

                        ObjectGuid::LowType db_guid = creature->GetSpawnId();

                        // To call _LoadGoods(); _LoadQuests(); CreateTrainerSpells()
                        // current "creature" variable is deleted and created fresh new, otherwise old values might trigger asserts or cause undefined behavior
                        creature->CleanupsBeforeDelete();
                        delete creature;

                        creature = Creature::CreateCreatureFromDB(db_guid, map, true, true);
                        if (!creature)break;

                        sObjectMgr->AddCreatureToGrid(sObjectMgr->GetCreatureData(db_guid));
                    }
                    l_Menu.EntryID++;

                    break;
                }
            }
        }

        void OnGossipSelectCode(Player* player, uint32 menu_id, uint32 /*sender*/, uint32 action, const char* code)
        {
            if (menu_id != 56818)
                return;

            MenuDatas& l_Menu = _menuData[player->GetGUID().GetCounter()];

            if (!code)
            {
                switch (action)
                {
                    case 2:
                        l_Menu.Name = "";
                        break;
                    case 3:
                        l_Menu.SubName = "";
                        break;
                }

                ShowMenu(player);
                return;
            }

            switch (action)
            {
                case 1:
                    l_Menu.EntryID = atol(code);
                    break;
                case 2:
                    l_Menu.Name = (code);
                    break;
                case 3:
                    l_Menu.SubName = (code);
                    break;
                case 4:
                    l_Menu.FactionID = atol(code);
                    break;
                case 5:
                    l_Menu.DisplayId = atol(code);
                    break;
                case 6:
                    l_Menu.Scale = atof(code);
                    break;
                case 9:
                    l_Menu.MinLevel = atol(code);
                    break;
                case 10:
                    l_Menu.MaxLevel = atol(code);
                    break;
            }

            ShowMenu(player);
        }

};

using namespace Trinity::ChatCommands;

using CreatureSpawnId = Variant<Hyperlink<creature>, ObjectGuid::LowType>;
using CreatureEntry = Variant<Hyperlink<creature_entry>, uint32>;

// shared with cs_gobject.cpp, definitions are at the bottom of this file
bool HandleNpcSpawnGroup(ChatHandler* handler, std::vector<Variant<uint32, EXACT_SEQUENCE("force"), EXACT_SEQUENCE("ignorerespawn")>> const& opts);
bool HandleNpcDespawnGroup(ChatHandler* handler, std::vector<Variant<uint32, EXACT_SEQUENCE("removerespawntime")>> const& opts);

class npc_commandscript : public CommandScript
{
public:
    npc_commandscript() : CommandScript("npc_commandscript") { }

    ChatCommandTable GetCommands() const override
    {
        static ChatCommandTable npcAddCommandTable =
        {
            { "formation",      HandleNpcAddFormationCommand,      rbac::RBAC_PERM_COMMAND_NPC_ADD_FORMATION,  Console::No },
            { "item",           HandleNpcAddVendorItemCommand,     rbac::RBAC_PERM_COMMAND_NPC_ADD_ITEM,       Console::No },
            { "move",           HandleNpcAddMoveCommand,           rbac::RBAC_PERM_COMMAND_NPC_ADD_MOVE,       Console::No },
            { "temp",           HandleNpcAddTempSpawnCommand,      rbac::RBAC_PERM_COMMAND_NPC_ADD_TEMP,       Console::No },
//          { "weapon",         HandleNpcAddWeaponCommand,         rbac::RBAC_PERM_COMMAND_NPC_ADD_WEAPON,     Console::No },
            { "",               HandleNpcAddCommand,               rbac::RBAC_PERM_COMMAND_NPC_ADD,            Console::No },
        };
        static ChatCommandTable npcSetCommandTable =
        {
            { "allowmove",      HandleNpcSetAllowMovementCommand,  rbac::RBAC_PERM_COMMAND_NPC_SET_ALLOWMOVE,  Console::No },
            { "entry",          HandleNpcSetEntryCommand,          rbac::RBAC_PERM_COMMAND_NPC_SET_ENTRY,      Console::No },
            { "factionid",      HandleNpcSetFactionIdCommand,      rbac::RBAC_PERM_COMMAND_NPC_SET_FACTIONID,  Console::No },
            { "flag",           HandleNpcSetFlagCommand,           rbac::RBAC_PERM_COMMAND_NPC_SET_FLAG,       Console::No },
            { "level",          HandleNpcSetLevelCommand,          rbac::RBAC_PERM_COMMAND_NPC_SET_LEVEL,      Console::No },
            { "link",           HandleNpcSetLinkCommand,           rbac::RBAC_PERM_COMMAND_NPC_SET_LINK,       Console::No },
            { "model",          HandleNpcSetModelCommand,          rbac::RBAC_PERM_COMMAND_NPC_SET_MODEL,      Console::No },
            { "scale",          HandleNpcSetScaleCommand,          rbac::RBAC_PERM_COMMAND_NPC_SET_MODEL,      Console::No },
            { "movetype",       HandleNpcSetMoveTypeCommand,       rbac::RBAC_PERM_COMMAND_NPC_SET_MOVETYPE,   Console::No },
            { "phase",          HandleNpcSetPhaseCommand,          rbac::RBAC_PERM_COMMAND_NPC_SET_PHASE,      Console::No },
            { "wanderdistance", HandleNpcSetWanderDistanceCommand, rbac::RBAC_PERM_COMMAND_NPC_SET_SPAWNDIST,  Console::No },
            { "spawntime",      HandleNpcSetSpawnTimeCommand,      rbac::RBAC_PERM_COMMAND_NPC_SET_SPAWNTIME,  Console::No },
            { "data",           HandleNpcSetDataCommand,           rbac::RBAC_PERM_COMMAND_NPC_SET_DATA,       Console::No },
            { "name",           HandleNpcSetNameCommand,           rbac::RBAC_PERM_COMMAND_NPC_SET_DATA,       Console::No },
            { "subname",        HandleNpcSetSubNameCommand,        rbac::RBAC_PERM_COMMAND_NPC_SET_DATA,       Console::No },
            { "aura",           HandleNpcSetAuraCommand,           rbac::RBAC_PERM_COMMAND_NPC_SET_DATA,       Console::No },
            { "boss",           HandleNpcSetBossCommand,           rbac::RBAC_PERM_COMMAND_NPC_SET_DATA,       Console::No },
            { "trigger",        HandleNpcSetTriggerCommand,        rbac::RBAC_PERM_COMMAND_NPC_SET_DATA,       Console::No },
        };
        static ChatCommandTable npcCommandTable =
        {
            { "add", npcAddCommandTable },
            { "set", npcSetCommandTable },
            { "addmulti",       HandleNpcAddMultiCommand,          rbac::RBAC_PERM_COMMAND_NPC_ADD,            Console::No },
            { "info",           HandleNpcInfoCommand,              rbac::RBAC_PERM_COMMAND_NPC_INFO,           Console::No },
            { "near",           HandleNpcNearCommand,              rbac::RBAC_PERM_COMMAND_NPC_NEAR,           Console::No },
            { "move",           HandleNpcMoveCommand,              rbac::RBAC_PERM_COMMAND_NPC_MOVE,           Console::No },
            { "playemote",      HandleNpcPlayEmoteCommand,         rbac::RBAC_PERM_COMMAND_NPC_PLAYEMOTE,      Console::No },
            { "say",            HandleNpcSayCommand,               rbac::RBAC_PERM_COMMAND_NPC_SAY,            Console::No },
            { "textemote",      HandleNpcTextEmoteCommand,         rbac::RBAC_PERM_COMMAND_NPC_TEXTEMOTE,      Console::No },
            { "whisper",        HandleNpcWhisperCommand,           rbac::RBAC_PERM_COMMAND_NPC_WHISPER,        Console::No },
            { "yell",           HandleNpcYellCommand,              rbac::RBAC_PERM_COMMAND_NPC_YELL,           Console::No },
            { "tame",           HandleNpcTameCommand,              rbac::RBAC_PERM_COMMAND_NPC_TAME,           Console::No },
            { "spawngroup",     HandleNpcSpawnGroup,               rbac::RBAC_PERM_COMMAND_NPC_SPAWNGROUP,     Console::No },
            { "despawngroup",   HandleNpcDespawnGroup,             rbac::RBAC_PERM_COMMAND_NPC_DESPAWNGROUP,   Console::No },
            { "delete",         HandleNpcDeleteCommand,            rbac::RBAC_PERM_COMMAND_NPC_DELETE,         Console::No },
            { "delete item",    HandleNpcDeleteVendorItemCommand,  rbac::RBAC_PERM_COMMAND_NPC_DELETE_ITEM,    Console::No },
            { "follow",         HandleNpcFollowCommand,            rbac::RBAC_PERM_COMMAND_NPC_FOLLOW,         Console::No },
            { "follow stop",    HandleNpcUnFollowCommand,          rbac::RBAC_PERM_COMMAND_NPC_FOLLOW,         Console::No },
            { "evade",          HandleNpcEvadeCommand,             rbac::RBAC_PERM_COMMAND_NPC_EVADE,          Console::No },
            { "showloot",       HandleNpcShowLootCommand,          rbac::RBAC_PERM_COMMAND_NPC_SHOWLOOT,       Console::No },
            { "clone",          HandleNpcCloneCommand,             rbac::RBAC_PERM_COMMAND_DEV,       Console::No },
            { "get",            HandleNpcGetCommand,               rbac::RBAC_PERM_COMMAND_NPC_SHOWLOOT,       Console::No },
            { "create",         HandleNpcCreateCommand,            rbac::RBAC_PERM_COMMAND_DEV,       Console::No },
            { "reload",         HandleNpcReloadCommand,            rbac::RBAC_PERM_COMMAND_DEV,       Console::No },
            { "wpadd",          HandleWpAddCommand,                rbac::RBAC_PERM_COMMAND_DEV, Console::No },
            { "relwp",          HandleRelWpCommand,                rbac::RBAC_PERM_COMMAND_DEV, Console::No },
            { "addleaderformation", HandleAddLeaderFormation,      rbac::RBAC_PERM_COMMAND_DEV, Console::No },
            { "addformation",   HandleAddFormationCommand,         rbac::RBAC_PERM_COMMAND_DEV, Console::No },
            { "addloot",        HandleAddLootCommand,              rbac::RBAC_PERM_COMMAND_DEV, Console::No },
            { "replace",        HandleNpcReplaceCommand,           rbac::RBAC_PERM_COMMAND_DEV, Console::No },
            { "allreplace",     HandleNpcReplaceAllCommand,        rbac::RBAC_PERM_COMMAND_DEV, Console::No },
            { "equip",          HandleNpcEquipCommand,             rbac::RBAC_PERM_COMMAND_DEV, Console::No },
        };
        static ChatCommandTable commandTable =
        {
            { "npc", npcCommandTable },
        };
        return commandTable;
    }

    static bool HandleNpcEquipCommand(ChatHandler* handler, Optional<uint32> itemId, Optional<uint32> itemId2)
    {
        auto creature = handler->getSelectedCreature();
        if (!creature)
            return true;

        if (itemId.has_value())
        {
            auto stmt = WorldDatabase.GetPreparedStatement(WORLD_REP_CREATURE_EQUIP_TEMPLATE);
            stmt->setUInt32(0, creature->GetEntry());
            stmt->setUInt32(1, 1);
            stmt->setUInt32(2, *itemId);
            WorldDatabase.Query(stmt);
        }

        sObjectMgr->LoadEquipmentTemplates();
        creature->LoadEquipment();
        creature->SaveToDB();

        // if (itemId.has_value())
        //     const_cast<CreatureData*>(creature->GetCreatureData())->equipmentId = 1;
        // else
        //     const_cast<CreatureData*>(creature->GetCreatureData())->equipmentId = 0;


        return true;
    }
    static bool HandleNpcSetTriggerCommand(ChatHandler* handler)
    {
        auto creature = handler->getSelectedCreature();
        if (!creature)
            return true;

        const_cast<CreatureTemplate*>(creature->GetCreatureTemplate())->flags_extra |= CREATURE_FLAG_EXTRA_TRIGGER;
        WorldDatabase.PExecute("UPDATE creature_template SET flags_extra = %u where entry = %u", creature->GetCreatureTemplate()->flags_extra, creature->GetEntry());
        handler->PSendSysMessage("Updated %s to be a trigger", creature->GetName().c_str());
        creature->UpdateObjectVisibility();
        return true;
    }

    static bool HandleNpcSetBossCommand(ChatHandler* handler)
    {
        auto creature = handler->getSelectedCreature();
        if (!creature)
            return true;

        const_cast<CreatureTemplate*>(creature->GetCreatureTemplate())->flags_extra |= CREATURE_FLAG_EXTRA_DUNGEON_BOSS;
        WorldDatabase.PExecute("UPDATE creature_template SET flags_extra = %u where entry = %u", creature->GetCreatureTemplate()->flags_extra, creature->GetEntry());
        handler->PSendSysMessage("Updated %s to be a boss, you may need to update InstanceScripts to use BossAI!", creature->GetName().c_str());
        return true;
    }

    static bool HandleNpcReplaceCommand(ChatHandler* handler, uint32 newEntry)
    {
        auto newCreature = sObjectMgr->GetCreatureTemplate(newEntry);
        if (!newCreature)
        {
            handler->SendSysMessage("not exist newEntry! Did you forgot to reload?");
            return true;
        }

        auto selected = handler->getSelectedCreature();
        if (!selected)
        {
            handler->SendSysMessage("Not selected a creature!");
            return true;
        }

        ObjectGuid::LowType spawnId = selected->GetSpawnId();
        handler->PSendSysMessage("%u spawnid replaced!", spawnId);
        WorldDatabase.PExecute("UPDATE creature set id = %u where guid = %u", newEntry, spawnId);
        auto data = const_cast<CreatureData*>(sObjectMgr->GetCreatureData(spawnId));
        data->id = newEntry;
        return true;
    }

    static bool HandleNpcReplaceAllCommand(ChatHandler* handler, uint32 newEntry)
    {
        auto newCreature = sObjectMgr->GetCreatureTemplate(newEntry);
        if (!newCreature)
        {
            handler->SendSysMessage("not exist newEntry! Did you forgot to reload?");
            return true;
        }

        auto selected = handler->getSelectedCreature();
        if (!selected)
        {
            handler->SendSysMessage("Not selected a creature!");
            return true;
        }

        ObjectGuid::LowType spawnId = selected->GetSpawnId();
        ObjectGuid::LowType entryId = selected->GetEntry();
        handler->PSendSysMessage("%u spawnid replaced!", spawnId);
        auto query = WorldDatabase.PQuery("SELECT guid from creature where id = %u and map = %u", entryId, handler->GetPlayer()->GetMapId());
        if (query)
        {
            do
            {
                Field* fields = query->Fetch();
                if (auto data = sObjectMgr->GetCreatureData(spawnId))
                {
                    const_cast<CreatureData*>(data)->id = newEntry;
                }
            } while (query->NextRow());
        }

        WorldDatabase.PExecute("UPDATE creature set id = %u where id = %u and map = %u", newEntry, entryId, handler->GetPlayer()->GetMapId());
        return true;
    }

    static bool HandleAddLootCommand(ChatHandler* handler, uint32 itemId, uint32 count, Optional<uint32> chance)
    {
        auto creature = handler->getSelectedCreature();
        if (!creature)
            return false;

        auto lootId = creature->GetCreatureTemplate()->lootid;
        if (!lootId)
        {
            lootId = creature->GetEntry();
            WorldDatabase.PQuery("UPDATE creature_template set lootid = %u where entry = %u", lootId, creature->GetEntry());
        }

        WorldDatabase.PQuery("REPLACE INTO creature_loot_template (Entry, Item, MinCount, MaxCount, Chance) VALUE (%u, %u, %u, %u, %u)", lootId, itemId, count, count, chance.value_or(100));
        LoadLootTemplates_Creature();
        LootTemplates_Creature.CheckLootRefs();
        handler->SendGlobalGMSysMessage("DB table `creature_loot_template` reloaded.");
        sConditionMgr->LoadConditions(true);
        handler->PSendSysMessage("added %u with count %u chance %u to %u", itemId, count, chance.value_or(100), lootId);
        return true;
    }

    static bool HandleAddFormationCommand(ChatHandler* handler, uint64 leaderGUID, Optional<float> distance, Optional<float> angle, Optional<uint32> groupai)
    {

        Creature* creature = handler->getSelectedCreature();

        if (!creature || !creature->GetSpawnId())
        {
            handler->SendSysMessage(LANG_SELECT_CREATURE);
            handler->SetSentErrorMessage(true);
            return false;
        }

        ObjectGuid::LowType lowguid = creature->GetSpawnId();
        if (creature->GetFormation())
        {
            handler->PSendSysMessage("Selected creature is already member of group " UI64FMTD, creature->GetFormation()->GetLeaderSpawnId());
            return false;
        }

        if (!lowguid)
            return false;

        Player* chr = handler->GetSession()->GetPlayer();

        float  followAngle = angle.value_or((creature->GetAbsoluteAngle(chr) - chr->GetOrientation()) * 180.0f / float(M_PI));
        float  followDist = distance.value_or(std::sqrt(std::pow(chr->GetPositionX() - creature->GetPositionX(), 2.f) + std::pow(chr->GetPositionY() - creature->GetPositionY(), 2.f)));
        uint32 groupAI = groupai.value_or(515);
        sFormationMgr->AddFormationMember(lowguid, followAngle, followDist, leaderGUID, groupAI);
        creature->SearchFormation();

        WorldDatabasePreparedStatement* stmt = WorldDatabase.GetPreparedStatement(WORLD_INS_CREATURE_FORMATION);
        stmt->setUInt64(0, leaderGUID);
        stmt->setUInt64(1, lowguid);
        stmt->setFloat(2, followDist);
        stmt->setFloat(3, followAngle );
        stmt->setUInt32(4, groupAI);

        WorldDatabase.Execute(stmt);

        handler->PSendSysMessage("Creature " UI64FMTD " added to formation with leader " UI64FMTD, lowguid, leaderGUID);
        return true;
    }

    static bool HandleAddLeaderFormation(ChatHandler* handler)
    {
        Creature* creature = handler->getSelectedCreature();
        if (!creature)
            return true;

        float followAngle = 0.0f;
        float followDist = 0.0f;
        uint64 leaderGUID = creature->GetSpawnId();
        uint32 groupAI = 515;

        sFormationMgr->AddFormationMember(creature->GetSpawnId(), followAngle, followDist, leaderGUID, groupAI);
        creature->SearchFormation();

        WorldDatabasePreparedStatement* stmt = WorldDatabase.GetPreparedStatement(WORLD_INS_CREATURE_FORMATION);
        stmt->setUInt64(0, leaderGUID);
        stmt->setUInt64(1, leaderGUID);
        stmt->setFloat(2, followDist);
        stmt->setFloat(3, followAngle);
        stmt->setUInt32(4, groupAI);

        WorldDatabase.Execute(stmt);

        handler->PSendSysMessage("Added formation for spawnid: %u", creature->GetSpawnId());
        return true;
    }

    static bool HandleRelWpCommand(ChatHandler* handler)
    {
        Creature* target = handler->getSelectedCreature();
        if (!target)
            return true;
        uint32 pathid = target->GetSpawnId() * 10;

        uint32 point = 0;
        // path_id -> ID of the Path
        // point   -> number of the waypoint (if not 0)

        if (!pathid)
        {
            handler->PSendSysMessage("%s%s|r", "|cffff33ff", "Current creature haven't loaded path.");
            return true;
        }

        handler->PSendSysMessage("%s%s|r|cff00ffff%u|r", "|cff00ff00", "Loading Path: ", pathid);
        sWaypointMgr->ReloadPath(pathid);

        auto guidLow = target->GetSpawnId();

        WorldDatabasePreparedStatement* stmt = WorldDatabase.GetPreparedStatement(WORLD_SEL_CREATURE_ADDON_BY_GUID);

        stmt->setUInt64(0, guidLow);

        PreparedQueryResult result = WorldDatabase.Query(stmt);

        if (result)
        {
            auto fields = result->Fetch();
            stmt = WorldDatabase.GetPreparedStatement(WORLD_UPD_CREATURE_ADDON_PATH);

            stmt->setUInt32(0, pathid);
            stmt->setStringView(1, fields[1].GetStringView());
            stmt->setUInt64(2, guidLow);
        }
        else
        {
            stmt = WorldDatabase.GetPreparedStatement(WORLD_INS_CREATURE_ADDON);

            stmt->setUInt64(0, guidLow);
            stmt->setUInt32(1, pathid);
            stmt->setStringView(2, "");
        }

        WorldDatabase.Query(stmt);

        stmt = WorldDatabase.GetPreparedStatement(WORLD_UPD_CREATURE_MOVEMENT_TYPE);

        stmt->setUInt8(0, uint8(WAYPOINT_MOTION_TYPE));
        stmt->setUInt64(1, guidLow);

        WorldDatabase.Query(stmt);

        target->LoadPath(pathid);
        target->SetDefaultMovementType(WAYPOINT_MOTION_TYPE);
        target->GetMotionMaster()->Initialize();
        target->Say("Path loaded.", LANG_UNIVERSAL);
        return true;
    }
    
    static bool HandleWpAddCommand(ChatHandler* handler, Optional<uint32> pathz)
    {
        Creature* target = handler->getSelectedCreature();
        uint32 pathid = pathz.value_or(0);
        if (target)
            pathid = target->GetSpawnId() * 10;

        uint32 point = 0;
        // path_id -> ID of the Path
        // point   -> number of the waypoint (if not 0)

        if (!pathid)
        {
            handler->PSendSysMessage("%s%s|r", "|cffff33ff", "Current creature haven't loaded path.");
            return true;
        }

        WorldDatabasePreparedStatement* stmt = WorldDatabase.GetPreparedStatement(WORLD_SEL_WAYPOINT_DATA_MAX_POINT);
        stmt->setUInt32(0, pathid);
        PreparedQueryResult result = WorldDatabase.Query(stmt);

        if (result)
            point = (*result)[0].GetUInt32();

        Player* player = handler->GetSession()->GetPlayer();
        //Map* map = player->GetMap();

        stmt = WorldDatabase.GetPreparedStatement(WORLD_INS_WAYPOINT_DATA);

        stmt->setUInt32(0, pathid);
        stmt->setUInt32(1, point + 1);
        stmt->setFloat(2, player->GetPositionX());
        stmt->setFloat(3, player->GetPositionY());
        stmt->setFloat(4, player->GetPositionZ());
        stmt->setFloat(5, player->GetOrientation());

        WorldDatabase.Execute(stmt);

        handler->PSendSysMessage("%s%s%u%s%u%s|r", "|cff00ff00", "PathID: |r|cff00ffff", pathid, "|r|cff00ff00: Waypoint |r|cff00ffff", point+1, "|r|cff00ff00 created. ");
        return true;
    }                                                           // HandleWpAddCommand

    //add spawn of creature
    static bool HandleNpcAddCommand(ChatHandler* handler, CreatureEntry id)
    {
        if (!sObjectMgr->GetCreatureTemplate(id))
            return false;

        Player* chr = handler->GetSession()->GetPlayer();
        Map* map = chr->GetMap();

        if (Transport* trans = dynamic_cast<Transport*>(chr->GetTransport()))
        {
            ObjectGuid::LowType guid = sObjectMgr->GenerateCreatureSpawnId();
            CreatureData& data = sObjectMgr->NewOrExistCreatureData(guid);
            data.spawnId = guid;
            data.spawnGroupData = sObjectMgr->GetDefaultSpawnGroup();
            data.id = id;
            data.spawnPoint.Relocate(chr->GetTransOffsetX(), chr->GetTransOffsetY(), chr->GetTransOffsetZ(), chr->GetTransOffsetO());
            if (Creature* creature = trans->CreateNPCPassenger(guid, &data))
            {
                creature->SaveToDB(trans->GetGOInfo()->moTransport.SpawnMap, { map->GetDifficultyID() });
                sObjectMgr->AddCreatureToGrid(&data);
            }
            return true;
        }

        Creature* creature = Creature::CreateCreature(id, map, chr->GetPosition());
        if (!creature)
            return false;

        PhasingHandler::InheritPhaseShift(creature, chr);
        creature->SaveToDB(map->GetId(), { map->GetDifficultyID() });

        ObjectGuid::LowType db_guid = creature->GetSpawnId();

        // To call _LoadGoods(); _LoadQuests(); CreateTrainerSpells()
        // current "creature" variable is deleted and created fresh new, otherwise old values might trigger asserts or cause undefined behavior
        creature->CleanupsBeforeDelete();
        delete creature;

        creature = Creature::CreateCreatureFromDB(db_guid, map, true, true);
        if (!creature)
            return false;

        sObjectMgr->AddCreatureToGrid(sObjectMgr->GetCreatureData(db_guid));
        return true;
    }

    static bool HandleNpcAddMultiCommand(ChatHandler* handler, std::string_view entries)
    {
        std::vector<uint32> entryIds;
        for (std::string_view token : Trinity::Tokenize(entries, ',', false))
            if (Optional<uint32> entryId = Trinity::StringTo<uint32>(token))
                entryIds.push_back(entryId.value());

        auto id = Trinity::Containers::SelectRandomContainerElement(entryIds);

        if (!sObjectMgr->GetCreatureTemplate(id))
            return false;

        Player* chr = handler->GetSession()->GetPlayer();
        Map* map = chr->GetMap();

        if (auto trans = dynamic_cast<Transport*>(chr->GetTransport()))
        {
            ObjectGuid::LowType guid = sObjectMgr->GenerateCreatureSpawnId();
            CreatureData& data = sObjectMgr->NewOrExistCreatureData(guid);
            data.spawnId = guid;
            data.spawnGroupData = sObjectMgr->GetDefaultSpawnGroup();
            data.id = id;
            data.spawnPoint.Relocate(chr->GetTransOffsetX(), chr->GetTransOffsetY(), chr->GetTransOffsetZ(), chr->GetTransOffsetO());
            if (Creature* creature = trans->CreateNPCPassenger(guid, &data))
            {
                creature->SaveToDB(trans->GetGOInfo()->moTransport.SpawnMap, { map->GetDifficultyID() });
                sObjectMgr->AddCreatureToGrid(&data);
            }
            return true;
        }

        Creature* creature = Creature::CreateCreature(id, map, chr->GetPosition());
        if (!creature)
            return false;

        PhasingHandler::InheritPhaseShift(creature, chr);
        creature->SaveToDB(map->GetId(), { map->GetDifficultyID() });

        ObjectGuid::LowType db_guid = creature->GetSpawnId();

        // To call _LoadGoods(); _LoadQuests(); CreateTrainerSpells()
        // current "creature" variable is deleted and created fresh new, otherwise old values might trigger asserts or cause undefined behavior
        creature->CleanupsBeforeDelete();
        delete creature;

        creature = Creature::CreateCreatureFromDB(db_guid, map, true, true);
        if (!creature)
            return false;

        sObjectMgr->AddCreatureToGrid(sObjectMgr->GetCreatureData(db_guid));
        return true;
    }
    //add item in vendorlist
    static bool HandleNpcAddVendorItemCommand(ChatHandler* handler, ItemTemplate const* item, Optional<uint32> mc, Optional<uint32> it, Optional<uint32> ec, Optional<bool> addMulti, Optional<std::string_view> bonusListIDs)
    {
        if (!item)
        {
            handler->SendSysMessage(LANG_COMMAND_NEEDITEMSEND);
            handler->SetSentErrorMessage(true);
            return false;
        }

        Creature* vendor = handler->getSelectedCreature();
        if (!vendor)
        {
            handler->SendSysMessage(LANG_SELECT_CREATURE);
            handler->SetSentErrorMessage(true);
            return false;
        }

        uint32 itemId = item->GetId();
        uint32 maxcount = mc.value_or(0);
        uint32 incrtime = it.value_or(0);
        uint32 extendedcost = ec.value_or(0);

        uint32 vendor_entry = addMulti.value_or(false) ? handler->GetSession()->GetPlayer()->PlayerTalkClass->GetInteractionData().VendorId : vendor->GetEntry();


        VendorItem vItem;
        vItem.item = itemId;
        vItem.maxcount = maxcount;
        vItem.incrtime = incrtime;
        vItem.ExtendedCost = extendedcost;
        vItem.Type = ITEM_VENDOR_TYPE_ITEM;

        if (bonusListIDs)
            for (std::string_view token : Trinity::Tokenize(*bonusListIDs, ';', false))
                if (Optional<int32> bonusListID = Trinity::StringTo<int32>(token))
                    vItem.BonusListIDs.push_back(*bonusListID);

        if (!sObjectMgr->IsVendorItemValid(vendor_entry, vItem, handler->GetSession()->GetPlayer()))
        {
            handler->SetSentErrorMessage(true);
            return false;
        }

        sObjectMgr->AddVendorItem(vendor_entry, vItem);

        handler->PSendSysMessage(LANG_ITEM_ADDED_TO_LIST, itemId, item->GetDefaultLocaleName(), maxcount, incrtime, extendedcost);
        return true;
    }

    //add move for creature
    static bool HandleNpcAddMoveCommand(ChatHandler* handler, CreatureSpawnId lowGuid)
    {
        // attempt check creature existence by DB data
        CreatureData const* data = sObjectMgr->GetCreatureData(lowGuid);
        if (!data)
        {
            handler->PSendSysMessage(LANG_COMMAND_CREATGUIDNOTFOUND, std::to_string(*lowGuid).c_str());
            handler->SetSentErrorMessage(true);
            return false;
        }

        // Update movement type
        WorldDatabasePreparedStatement* stmt = WorldDatabase.GetPreparedStatement(WORLD_UPD_CREATURE_MOVEMENT_TYPE);

        stmt->setUInt8(0, uint8(WAYPOINT_MOTION_TYPE));
        stmt->setUInt64(1, lowGuid);

        WorldDatabase.Execute(stmt);

        handler->SendSysMessage(LANG_WAYPOINT_ADDED);

        return true;
    }

    static bool HandleNpcSetAllowMovementCommand(ChatHandler* handler)
    {
        if (sWorld->getAllowMovement())
        {
            sWorld->SetAllowMovement(false);
            handler->SendSysMessage(LANG_CREATURE_MOVE_DISABLED);
        }
        else
        {
            sWorld->SetAllowMovement(true);
            handler->SendSysMessage(LANG_CREATURE_MOVE_ENABLED);
        }
        return true;
    }

    static bool HandleNpcSetEntryCommand(ChatHandler* handler, CreatureEntry newEntryNum)
    {
        if (!newEntryNum)
            return false;

        Unit* unit = handler->getSelectedUnit();
        if (!unit || unit->GetTypeId() != TYPEID_UNIT)
        {
            handler->SendSysMessage(LANG_SELECT_CREATURE);
            handler->SetSentErrorMessage(true);
            return false;
        }
        Creature* creature = unit->ToCreature();
        if (creature->UpdateEntry(newEntryNum))
            handler->SendSysMessage(LANG_DONE);
        else
            handler->SendSysMessage(LANG_ERROR);
        return true;
    }

    //change level of creature or pet
    static bool HandleNpcSetLevelCommand(ChatHandler* handler, uint8 lvl)
    {
        if (lvl < 1 || lvl > sWorld->getIntConfig(CONFIG_MAX_PLAYER_LEVEL) + 3)
        {
            handler->SendSysMessage(LANG_BAD_VALUE);
            handler->SetSentErrorMessage(true);
            return false;
        }

        Creature* creature = handler->getSelectedCreature();
        if (!creature || creature->IsPet())
        {
            handler->SendSysMessage(LANG_SELECT_CREATURE);
            handler->SetSentErrorMessage(true);
            return false;
        }

        creature->SetMaxHealth(100 + 30*lvl);
        creature->SetHealth(100 + 30*lvl);
        creature->SetLevel(lvl);
        creature->SaveToDB();

        return true;
    }

    static bool HandleNpcDeleteCommand(ChatHandler* handler, Optional<CreatureSpawnId> spawnIdArg)
    {
        ObjectGuid::LowType spawnId;
        if (spawnIdArg)
            spawnId = *spawnIdArg;
        else
        {
            Creature* creature = handler->getSelectedCreature();
            if (!creature || creature->IsPet() || creature->IsTotem())
            {
                handler->SendSysMessage(LANG_SELECT_CREATURE);
                handler->SetSentErrorMessage(true);
                return false;
            }
            if (TempSummon* summon = creature->ToTempSummon())
            {
                summon->UnSummon();
                handler->SendSysMessage(LANG_COMMAND_DELCREATMESSAGE);
                return true;
            }
            spawnId = creature->GetSpawnId();
        }

        if (Creature::DeleteFromDB(spawnId))
        {
            handler->SendSysMessage(LANG_COMMAND_DELCREATMESSAGE);
            return true;
        }
        else
        {
            handler->PSendSysMessage(LANG_COMMAND_CREATGUIDNOTFOUND, std::to_string(spawnId).c_str());
            handler->SetSentErrorMessage(true);
            return false;
        }
    }

    //del item from vendor list
    static bool HandleNpcDeleteVendorItemCommand(ChatHandler* handler, ItemTemplate const* item, Optional<bool> addMulti)
    {
        Creature* vendor = handler->getSelectedCreature();
        if (!vendor || !vendor->IsVendor())
        {
            handler->SendSysMessage(LANG_COMMAND_VENDORSELECTION);
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (!item)
        {
            handler->SendSysMessage(LANG_COMMAND_NEEDITEMSEND);
            handler->SetSentErrorMessage(true);
            return false;
        }

        uint32 itemId = item->GetId();
        if (!sObjectMgr->RemoveVendorItem(addMulti.value_or(false) ? handler->GetSession()->GetPlayer()->PlayerTalkClass->GetInteractionData().TrainerId : vendor->GetEntry(), itemId, ITEM_VENDOR_TYPE_ITEM))
        {
            handler->PSendSysMessage(LANG_ITEM_NOT_IN_LIST, itemId);
            handler->SetSentErrorMessage(true);
            return false;
        }

        handler->PSendSysMessage(LANG_ITEM_DELETED_FROM_LIST, itemId, item->GetDefaultLocaleName());
        return true;
    }

    //set faction of creature
    static bool HandleNpcSetFactionIdCommand(ChatHandler* handler, uint32 factionId)
    {
        if (!sFactionTemplateStore.LookupEntry(factionId))
        {
            handler->PSendSysMessage(LANG_WRONG_FACTION, factionId);
            handler->SetSentErrorMessage(true);
            return false;
        }

        Creature* creature = handler->getSelectedCreature();

        if (!creature)
        {
            handler->SendSysMessage(LANG_SELECT_CREATURE);
            handler->SetSentErrorMessage(true);
            return false;
        }

        creature->SetFaction(factionId);

        // Faction is set in creature_template - not inside creature

        // Update in memory..
        if (CreatureTemplate const* cinfo = creature->GetCreatureTemplate())
            const_cast<CreatureTemplate*>(cinfo)->faction = factionId;

        // ..and DB
        WorldDatabasePreparedStatement* stmt = WorldDatabase.GetPreparedStatement(WORLD_UPD_CREATURE_FACTION);

        stmt->setUInt16(0, uint16(factionId));
        stmt->setUInt32(1, creature->GetEntry());

        WorldDatabase.Execute(stmt);

        return true;
    }

    //set npcflag of creature
    static bool HandleNpcSetFlagCommand(ChatHandler* handler, uint32 npcFlags, Optional<uint32> npcFlags2)
    {
        Creature* creature = handler->getSelectedCreature();

        if (!creature)
        {
            handler->SendSysMessage(LANG_SELECT_CREATURE);
            handler->SetSentErrorMessage(true);
            return false;
        }

        uint32 npcFlag2 = npcFlags2.value_or(0);

        creature->ReplaceAllNpcFlags(static_cast<NPCFlags>(npcFlags));
        creature->ReplaceAllNpcFlags2(static_cast<NPCFlags2>(npcFlag2));

        WorldDatabasePreparedStatement* stmt = WorldDatabase.GetPreparedStatement(WORLD_UPD_CREATURE_NPCFLAG);

        stmt->setUInt64(0, uint64(npcFlags) | (uint64(npcFlag2) << 32));
        stmt->setUInt32(1, creature->GetEntry());

        WorldDatabase.Execute(stmt);

        handler->SendSysMessage(LANG_VALUE_SAVED_REJOIN);

        return true;
    }

    //set data of creature for testing scripting
    static bool HandleNpcSetDataCommand(ChatHandler* handler, uint32 data_1, uint32 data_2)
    {
        Creature* creature = handler->getSelectedCreature();

        if (!creature)
        {
            handler->SendSysMessage(LANG_SELECT_CREATURE);
            handler->SetSentErrorMessage(true);
            return false;
        }

        creature->AI()->SetData(data_1, data_2);
        std::string AIorScript = !creature->GetAIName().empty() ? "AI type: " + creature->GetAIName() : (!creature->GetScriptName().empty() ? "Script Name: " + creature->GetScriptName() : "No AI or Script Name Set");
        handler->PSendSysMessage(LANG_NPC_SETDATA, creature->GetGUID().ToString().c_str(), creature->GetName().c_str(), data_1, data_2, AIorScript.c_str());
        return true;
    }

    static bool HandleNpcSetNameCommand(ChatHandler* handler, Tail text)
    {
        Creature* creature = handler->getSelectedCreature();

        if (!creature)
        {
            handler->SendSysMessage(LANG_SELECT_CREATURE);
            handler->SetSentErrorMessage(true);
            return false;
        }

        handler->PSendSysMessage("Set the name of %s to %s", creature->GetName().c_str(), text);
        auto stmt = WorldDatabase.GetPreparedStatement(WORLD_UPD_CREATURE_TEMPLATE_NAME);
        stmt->setStringView(0, text);
        stmt->setUInt32(1, creature->GetEntry());
        WorldDatabase.Query(stmt);

        stmt = WorldDatabase.GetPreparedStatement(WORLD_SEL_CREATURE_TEMPLATE);
        stmt->setUInt32(0, creature->GetEntry());
        stmt->setUInt32(1, 0);
        PreparedQueryResult result = WorldDatabase.Query(stmt);

        if (!result)
        {
            handler->PSendSysMessage(LANG_COMMAND_CREATURETEMPLATE_NOTFOUND, creature->GetEntry());
            return true;
        }

        sObjectMgr->LoadCreatureTemplate(result->Fetch());
        sObjectMgr->LoadCreatureTemplateModel(creature->GetEntry());

        WorldPacket response = creature->GetCreatureTemplate()->BuildQueryData(handler->GetSession()->GetSessionDbLocaleIndex());
        handler->GetSession()->SendPacket(&response);

        creature->DestroyForNearbyPlayers();
        creature->UpdateObjectVisibility(true);

        return true;
    }

    static bool HandleNpcSetSubNameCommand(ChatHandler* handler, Tail text)
    {
        Creature* creature = handler->getSelectedCreature();

        if (!creature)
        {
            handler->SendSysMessage(LANG_SELECT_CREATURE);
            handler->SetSentErrorMessage(true);
            return false;
        }

        handler->PSendSysMessage("Set the subname of %s to %s", creature->GetName().c_str(), text);
        auto stmt = WorldDatabase.GetPreparedStatement(WORLD_UPD_CREATURE_TEMPLATE_SUBNAME);
        stmt->setStringView(0, text);
        stmt->setUInt32(1, creature->GetEntry());
        WorldDatabase.Query(stmt);

        stmt = WorldDatabase.GetPreparedStatement(WORLD_SEL_CREATURE_TEMPLATE);
        stmt->setUInt32(0, creature->GetEntry());
        stmt->setUInt32(1, 0);
        PreparedQueryResult result = WorldDatabase.Query(stmt);

        if (!result)
        {
            handler->PSendSysMessage(LANG_COMMAND_CREATURETEMPLATE_NOTFOUND, creature->GetEntry());
            return true;
        }

        sObjectMgr->LoadCreatureTemplate(result->Fetch());
        sObjectMgr->LoadCreatureTemplateModel(creature->GetEntry());

        WorldPacket response = creature->GetCreatureTemplate()->BuildQueryData(handler->GetSession()->GetSessionDbLocaleIndex());
        handler->GetSession()->SendPacket(&response);

        creature->DestroyForNearbyPlayers();
        creature->UpdateObjectVisibility(true);

        return true;
    }

    static bool HandleNpcSetAuraCommand(ChatHandler* handler, uint32 aura)
    {
        auto creature = handler->getSelectedCreature();

        auto guidLow = creature->GetSpawnId();

        WorldDatabasePreparedStatement* stmt = WorldDatabase.GetPreparedStatement(WORLD_SEL_CREATURE_ADDON_BY_GUID);

        stmt->setUInt64(0, guidLow);

        PreparedQueryResult result = WorldDatabase.Query(stmt);

        if (result)
        {
            auto fields = result->Fetch();
            auto pathid = fields[2].GetUInt32();
            stmt = WorldDatabase.GetPreparedStatement(WORLD_UPD_CREATURE_ADDON_PATH);

            stmt->setUInt32(0, pathid);

            std::ostringstream ss;
            ss << fields[1].GetStringView() << " " << aura;

            stmt->setStringView(1, ss.str());
            stmt->setUInt64(2, guidLow);
        }
        else
        {
            stmt = WorldDatabase.GetPreparedStatement(WORLD_INS_CREATURE_ADDON);

            stmt->setUInt64(0, guidLow);
            stmt->setUInt32(1, 0);
            stmt->setStringView(2, std::to_string(aura));
        }

        WorldDatabase.Query(stmt);

        creature->AddAura(aura, creature);

        return true;
    }

    //npc follow handling
    static bool HandleNpcFollowCommand(ChatHandler* handler)
    {
        Player* player = handler->GetSession()->GetPlayer();
        Creature* creature = handler->getSelectedCreature();

        if (!creature)
        {
            handler->PSendSysMessage(LANG_SELECT_CREATURE);
            handler->SetSentErrorMessage(true);
            return false;
        }

        // Follow player
        creature->FollowTarget(player);

        handler->PSendSysMessage(LANG_CREATURE_FOLLOW_YOU_NOW, creature->GetName().c_str());
        return true;
    }

    static bool HandleNpcInfoCommand(ChatHandler* handler)
    {
        Creature* target = handler->getSelectedCreature();

        if (!target)
        {
            handler->SendSysMessage(LANG_SELECT_CREATURE);
            handler->SetSentErrorMessage(true);
            return false;
        }

        CreatureTemplate const* cInfo = target->GetCreatureTemplate();

        uint32 faction = target->GetFaction();
        uint64 npcflags;
        memcpy(&npcflags, target->m_unitData->NpcFlags.begin(), sizeof(npcflags));
        uint32 mechanicImmuneMask = cInfo->MechanicImmuneMask;
        uint32 displayid = target->GetDisplayId();
        uint32 nativeid = target->GetNativeDisplayId();
        uint32 entry = target->GetEntry();

        int64 curRespawnDelay = target->GetRespawnCompatibilityMode() ? target->GetRespawnTimeEx() - GameTime::GetGameTime() : target->GetMap()->GetCreatureRespawnTime(target->GetSpawnId()) - GameTime::GetGameTime();

        if (curRespawnDelay < 0)
            curRespawnDelay = 0;
        std::string curRespawnDelayStr = secsToTimeString(uint64(curRespawnDelay), TimeFormat::ShortText);
        std::string defRespawnDelayStr = secsToTimeString(target->GetRespawnDelay(), TimeFormat::ShortText);

        handler->PSendSysMessage(LANG_NPCINFO_CHAR, target->GetName().c_str(), std::to_string(target->GetSpawnId()).c_str(), target->GetGUID().ToString().c_str(), entry, faction, std::to_string(npcflags).c_str(), displayid, nativeid);
        if (target->GetCreatureData() && target->GetCreatureData()->spawnGroupData->groupId)
        {
            SpawnGroupTemplateData const* const groupData = target->GetCreatureData()->spawnGroupData;
            handler->PSendSysMessage(LANG_SPAWNINFO_GROUP_ID, groupData->name.c_str(), groupData->groupId, groupData->flags, target->GetMap()->IsSpawnGroupActive(groupData->groupId));
        }
        handler->PSendSysMessage(LANG_SPAWNINFO_COMPATIBILITY_MODE, target->GetRespawnCompatibilityMode());
        handler->PSendSysMessage(LANG_NPCINFO_LEVEL, target->GetLevel());
        handler->PSendSysMessage(LANG_NPCINFO_EQUIPMENT, target->GetCurrentEquipmentId(), target->GetOriginalEquipmentId());
        handler->PSendSysMessage(LANG_NPCINFO_HEALTH, target->GetCreateHealth(), std::to_string(target->GetMaxHealth()).c_str(), std::to_string(target->GetHealth()).c_str());
        handler->PSendSysMessage(LANG_NPCINFO_MOVEMENT_DATA, target->GetMovementTemplate().ToString().c_str());

        handler->PSendSysMessage(LANG_NPCINFO_UNIT_FIELD_FLAGS, *target->m_unitData->Flags);
        for (UnitFlags flag : EnumUtils::Iterate<UnitFlags>())
            if (target->HasUnitFlag(flag))
                handler->PSendSysMessage("%s (0x%X)", EnumUtils::ToTitle(flag), flag);

        handler->PSendSysMessage(LANG_NPCINFO_UNIT_FIELD_FLAGS_2, *target->m_unitData->Flags2);
        for (UnitFlags2 flag : EnumUtils::Iterate<UnitFlags2>())
            if (target->HasUnitFlag2(flag))
                handler->PSendSysMessage("%s (0x%X)", EnumUtils::ToTitle(flag), flag);

        handler->PSendSysMessage(LANG_NPCINFO_UNIT_FIELD_FLAGS_3, *target->m_unitData->Flags3);
        for (UnitFlags3 flag : EnumUtils::Iterate<UnitFlags3>())
            if (target->HasUnitFlag3(flag))
                handler->PSendSysMessage("%s (0x%X)", EnumUtils::ToTitle(flag), flag);

        handler->PSendSysMessage(LANG_NPCINFO_DYNAMIC_FLAGS, target->GetDynamicFlags());
        handler->PSendSysMessage(LANG_COMMAND_RAWPAWNTIMES, defRespawnDelayStr.c_str(), curRespawnDelayStr.c_str());
        handler->PSendSysMessage(LANG_NPCINFO_LOOT,  cInfo->lootid, cInfo->pickpocketLootId, cInfo->SkinLootId);
        handler->PSendSysMessage(LANG_NPCINFO_DUNGEON_ID, target->GetInstanceId());

        if (CreatureData const* data = sObjectMgr->GetCreatureData(target->GetSpawnId()))
        {
            handler->PSendSysMessage(LANG_NPCINFO_PHASES, data->phaseId, data->phaseGroup);
            PhasingHandler::PrintToChat(handler, target);
        }

        handler->PSendSysMessage(LANG_NPCINFO_ARMOR, target->GetArmor());
        handler->PSendSysMessage(LANG_NPCINFO_POSITION, target->GetPositionX(), target->GetPositionY(), target->GetPositionZ());
        handler->PSendSysMessage(LANG_OBJECTINFO_AIINFO, target->GetAIName().c_str(), target->GetScriptName().c_str());
        handler->PSendSysMessage(LANG_NPCINFO_REACTSTATE, DescribeReactState(target->GetReactState()));
        if (CreatureAI const* ai = target->AI())
            handler->PSendSysMessage(LANG_OBJECTINFO_AITYPE, GetTypeName(*ai).c_str());
        handler->PSendSysMessage(LANG_NPCINFO_FLAGS_EXTRA, cInfo->flags_extra);
        for (CreatureFlagsExtra flag : EnumUtils::Iterate<CreatureFlagsExtra>())
            if (cInfo->flags_extra & flag)
                handler->PSendSysMessage("%s (0x%X)", EnumUtils::ToTitle(flag), flag);

        handler->PSendSysMessage(LANG_NPCINFO_NPC_FLAGS, target->m_unitData->NpcFlags[0]);
        for (NPCFlags flag : EnumUtils::Iterate<NPCFlags>())
            if (target->HasNpcFlag(flag))
                handler->PSendSysMessage("* %s (0x%X)", EnumUtils::ToTitle(flag), flag);

        for (NPCFlags2 flag : EnumUtils::Iterate<NPCFlags2>())
            if (target->HasNpcFlag2(flag))
                handler->PSendSysMessage("* %s (0x%X)", EnumUtils::ToTitle(flag), flag);

        handler->PSendSysMessage(LANG_NPCINFO_MECHANIC_IMMUNE, mechanicImmuneMask);
        for (Mechanics m : EnumUtils::Iterate<Mechanics>())
            if (m && (mechanicImmuneMask & (1 << (m - 1))))
                handler->PSendSysMessage("%s (0x%X)", EnumUtils::ToTitle(m), m);

        return true;
    }

    static bool HandleNpcNearCommand(ChatHandler* handler, Optional<float> dist)
    {
        float distance = dist.value_or(10.0f);
        uint32 count = 0;

        Player* player = handler->GetSession()->GetPlayer();

        WorldDatabasePreparedStatement* stmt = WorldDatabase.GetPreparedStatement(WORLD_SEL_CREATURE_NEAREST);
        stmt->setFloat(0, player->GetPositionX());
        stmt->setFloat(1, player->GetPositionY());
        stmt->setFloat(2, player->GetPositionZ());
        stmt->setUInt32(3, player->GetMapId());
        stmt->setFloat(4, player->GetPositionX());
        stmt->setFloat(5, player->GetPositionY());
        stmt->setFloat(6, player->GetPositionZ());
        stmt->setFloat(7, distance * distance);
        PreparedQueryResult result = WorldDatabase.Query(stmt);

        if (result)
        {
            do
            {
                Field* fields = result->Fetch();
                ObjectGuid::LowType guid = fields[0].GetUInt64();
                uint32 entry = fields[1].GetUInt32();
                float x = fields[2].GetFloat();
                float y = fields[3].GetFloat();
                float z = fields[4].GetFloat();
                uint16 mapId = fields[5].GetUInt16();

                CreatureTemplate const* creatureTemplate = sObjectMgr->GetCreatureTemplate(entry);
                if (!creatureTemplate)
                    continue;

                handler->PSendSysMessage(LANG_CREATURE_LIST_CHAT, std::to_string(guid).c_str(), std::to_string(guid).c_str(), creatureTemplate->Name.c_str(), x, y, z, mapId, "", "");

                ++count;
            }
            while (result->NextRow());
        }

        handler->PSendSysMessage(LANG_COMMAND_NEAR_NPC_MESSAGE, distance, count);

        return true;
    }

    //move selected creature
    static bool HandleNpcMoveCommand(ChatHandler* handler, Optional<CreatureSpawnId> spawnid)
    {
        Creature* creature = handler->getSelectedCreature();
        Player const* player = handler->GetSession()->GetPlayer();
        if (!player)
            return false;

        if (!spawnid && !creature)
            return false;

        ObjectGuid::LowType lowguid = spawnid ? *spawnid : creature->GetSpawnId();
        // Attempting creature load from DB data
        CreatureData const* data = sObjectMgr->GetCreatureData(lowguid);
        if (!data)
        {
            handler->PSendSysMessage(LANG_COMMAND_CREATGUIDNOTFOUND, std::to_string(lowguid).c_str());
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (player->GetMapId() != data->mapId)
        {
            handler->PSendSysMessage(LANG_COMMAND_CREATUREATSAMEMAP, std::to_string(lowguid).c_str());
            handler->SetSentErrorMessage(true);
            return false;
        }

        // update position in memory
        sObjectMgr->RemoveCreatureFromGrid(data);
        const_cast<CreatureData*>(data)->spawnPoint.Relocate(*player);
        sObjectMgr->AddCreatureToGrid(data);

        // update position in DB
        WorldDatabasePreparedStatement* stmt = WorldDatabase.GetPreparedStatement(WORLD_UPD_CREATURE_POSITION);
        stmt->setFloat(0, player->GetPositionX());
        stmt->setFloat(1, player->GetPositionY());
        stmt->setFloat(2, player->GetPositionZ());
        stmt->setFloat(3, player->GetOrientation());
        stmt->setUInt64(4, lowguid);
        WorldDatabase.Execute(stmt);

        // respawn selected creature at the new location
        if (creature)
            creature->DespawnOrUnsummon(0s, 1s);

        handler->PSendSysMessage(LANG_COMMAND_CREATUREMOVED);
        return true;
    }

    //play npc emote
    static bool HandleNpcPlayEmoteCommand(ChatHandler* handler, uint32 emote)
    {
        Creature* target = handler->getSelectedCreature();
        if (!target)
        {
            handler->SendSysMessage(LANG_SELECT_CREATURE);
            handler->SetSentErrorMessage(true);
            return false;
        }

        target->SetEmoteState(Emote(emote));

        return true;
    }

    //set model of creature
    static bool HandleNpcSetModelCommand(ChatHandler* handler, uint32 displayId)
    {
        Creature* creature = handler->getSelectedCreature();

        if (!creature || creature->IsPet())
        {
            handler->SendSysMessage(LANG_SELECT_CREATURE);
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (!sCreatureDisplayInfoStore.LookupEntry(displayId))
        {
            handler->PSendSysMessage(LANG_COMMAND_INVALID_PARAM, Trinity::ToString(displayId).c_str());
            handler->SetSentErrorMessage(true);
            return false;
        }

        creature->SetDisplayId(displayId);
        creature->SetNativeDisplayId(displayId);

        auto stmt = WorldDatabase.GetPreparedStatement(WORLD_UPD_CREATURE_TEMPLATE_MODEL);
        stmt->setUInt32(0, displayId);
        stmt->setUInt32(1, creature->GetEntry());
        stmt->setUInt32(2, 0);
        WorldDatabase.Query(stmt);

        creature->SaveToDB();

        stmt = WorldDatabase.GetPreparedStatement(WORLD_SEL_CREATURE_TEMPLATE);
        stmt->setUInt32(0, creature->GetEntry());
        stmt->setUInt32(1, 0);
        PreparedQueryResult result = WorldDatabase.Query(stmt);

        if (!result)
        {
            handler->PSendSysMessage(LANG_COMMAND_CREATURETEMPLATE_NOTFOUND, creature->GetEntry());
            return true;
        }

        sObjectMgr->LoadCreatureTemplate(result->Fetch());
        sObjectMgr->LoadCreatureTemplateModel(creature->GetEntry());

        return true;
    }

    static bool HandleNpcSetScaleCommand(ChatHandler* handler, float scale)
    {
        Creature* creature = handler->getSelectedCreature();

        if (!creature || creature->IsPet())
        {
            handler->SendSysMessage(LANG_SELECT_CREATURE);
            handler->SetSentErrorMessage(true);
            return false;
        }

        creature->SetObjectScale(scale);

        auto stmt = WorldDatabase.GetPreparedStatement(WORLD_UPD_CREATURE_TEMPLATE_SCALE);
        stmt->setFloat(0, scale);
        stmt->setUInt32(1, creature->GetEntry());
        stmt->setUInt32(2, 0);
        WorldDatabase.Query(stmt);

        creature->SaveToDB();

        stmt = WorldDatabase.GetPreparedStatement(WORLD_SEL_CREATURE_TEMPLATE);
        stmt->setUInt32(0, creature->GetEntry());
        stmt->setUInt32(1, 0);
        PreparedQueryResult result = WorldDatabase.Query(stmt);

        if (!result)
        {
            handler->PSendSysMessage(LANG_COMMAND_CREATURETEMPLATE_NOTFOUND, creature->GetEntry());
            return true;
        }

        sObjectMgr->LoadCreatureTemplate(result->Fetch());
        sObjectMgr->LoadCreatureTemplateModel(creature->GetEntry());

        return true;
    }

    /**HandleNpcSetMoveTypeCommand
    * Set the movement type for an NPC.<br/>
    * <br/>
    * Valid movement types are:
    * <ul>
    * <li> stay - NPC wont move </li>
    * <li> random - NPC will move randomly according to the wander_distance </li>
    * <li> way - NPC will move with given waypoints set </li>
    * </ul>
    * additional parameter: NODEL - so no waypoints are deleted, if you
    *                       change the movement type
    */
    static bool HandleNpcSetMoveTypeCommand(ChatHandler* handler, Optional<CreatureSpawnId> lowGuid, Variant<EXACT_SEQUENCE("stay"), EXACT_SEQUENCE("random"), EXACT_SEQUENCE("way")> type, Optional<EXACT_SEQUENCE("nodel")> nodel)
    {
        // 3 arguments:
        // GUID (optional - you can also select the creature)
        // stay|random|way (determines the kind of movement)
        // NODEL (optional - tells the system NOT to delete any waypoints)
        //        this is very handy if you want to do waypoints, that are
        //        later switched on/off according to special events (like escort
        //        quests, etc)

        bool doNotDelete = nodel.has_value();

        ObjectGuid::LowType lowguid = UI64LIT(0);
        Creature* creature = nullptr;

        if (!lowGuid)                                           // case .setmovetype $move_type (with selected creature)
        {
            creature = handler->getSelectedCreature();
            if (!creature || creature->IsPet())
                return false;
            lowguid = creature->GetSpawnId();
        }
        else                                                    // case .setmovetype #creature_guid $move_type (with selected creature)
        {
            lowguid = *lowGuid;

            if (lowguid)
                creature = handler->GetCreatureFromPlayerMapByDbGuid(lowguid);

            // attempt check creature existence by DB data
            if (!creature)
            {
                CreatureData const* data = sObjectMgr->GetCreatureData(lowguid);
                if (!data)
                {
                    handler->PSendSysMessage(LANG_COMMAND_CREATGUIDNOTFOUND, std::to_string(lowguid).c_str());
                    handler->SetSentErrorMessage(true);
                    return false;
                }
            }
            else
            {
                lowguid = creature->GetSpawnId();
            }
        }

        // now lowguid is low guid really existed creature
        // and creature point (maybe) to this creature or nullptr

        MovementGeneratorType move_type;
        switch (type.index())
        {
            case 0:
                move_type = IDLE_MOTION_TYPE;
                break;
            case 1:
                move_type = RANDOM_MOTION_TYPE;
                break;
            case 2:
                move_type = WAYPOINT_MOTION_TYPE;
                break;
            default:
                return false;
        }

        // update movement type
        //if (doNotDelete == false)
        //    WaypointMgr.DeletePath(lowguid);

        if (creature)
        {
            // update movement type
            if (doNotDelete == false)
                creature->LoadPath(0);

            creature->SetDefaultMovementType(move_type);
            creature->GetMotionMaster()->Initialize();
            if (creature->IsAlive())                            // dead creature will reset movement generator at respawn
            {
                creature->setDeathState(JUST_DIED);
                creature->Respawn();
            }
            creature->SaveToDB();
        }
        if (doNotDelete == false)
        {
            handler->PSendSysMessage(LANG_MOVE_TYPE_SET, EnumUtils::ToTitle(move_type));
        }
        else
        {
            handler->PSendSysMessage(LANG_MOVE_TYPE_SET_NODEL, EnumUtils::ToTitle(move_type));
        }

        return true;
    }

    //npc phase handling
    //change phase of creature
    static bool HandleNpcSetPhaseGroup(ChatHandler* handler, char const* args)
    {
        if (!*args)
            return false;

        int32 phaseGroupId = atoi(args);

        Creature* creature = handler->getSelectedCreature();
        if (!creature || creature->IsPet())
        {
            handler->SendSysMessage(LANG_SELECT_CREATURE);
            handler->SetSentErrorMessage(true);
            return false;
        }

        PhasingHandler::ResetPhaseShift(creature);
        PhasingHandler::AddPhaseGroup(creature, phaseGroupId, true);
        creature->SetDBPhase(-phaseGroupId);

        creature->SaveToDB();

        return true;
    }

    //npc phase handling
    //change phase of creature
    static bool HandleNpcSetPhaseCommand(ChatHandler* handler, uint32 phaseID)
    {
        if (phaseID == 0)
        {
            handler->SendSysMessage(LANG_PHASE_NOTFOUND);
            handler->SetSentErrorMessage(true);
            return false;
        }

        Creature* creature = handler->getSelectedCreature();
        if (!creature || creature->IsPet())
        {
            handler->SendSysMessage(LANG_SELECT_CREATURE);
            handler->SetSentErrorMessage(true);
            return false;
        }

        PhasingHandler::ResetPhaseShift(creature);
        PhasingHandler::AddPhase(creature, phaseID, true);
        creature->SetDBPhase(phaseID);

        creature->SaveToDB();

        return true;
    }

    //set spawn dist of creature
    static bool HandleNpcSetWanderDistanceCommand(ChatHandler* handler, float option)
    {
        if (option < 0.0f)
        {
            handler->SendSysMessage(LANG_BAD_VALUE);
            return false;
        }

        MovementGeneratorType mtype = IDLE_MOTION_TYPE;
        if (option > 0.0f)
            mtype = RANDOM_MOTION_TYPE;

        Creature* creature = handler->getSelectedCreature();
        ObjectGuid::LowType guidLow = UI64LIT(0);

        if (creature)
            guidLow = creature->GetSpawnId();
        else
            return false;

        creature->SetWanderDistance((float)option);
        creature->SetDefaultMovementType(mtype);
        creature->GetMotionMaster()->Initialize();
        if (creature->IsAlive())                                // dead creature will reset movement generator at respawn
        {
            creature->setDeathState(JUST_DIED);
            creature->Respawn();
        }

        WorldDatabasePreparedStatement* stmt = WorldDatabase.GetPreparedStatement(WORLD_UPD_CREATURE_WANDER_DISTANCE);

        stmt->setFloat(0, option);
        stmt->setUInt8(1, uint8(mtype));
        stmt->setUInt64(2, guidLow);

        WorldDatabase.Execute(stmt);

        handler->PSendSysMessage(LANG_COMMAND_WANDER_DISTANCE, option);
        return true;
    }

    //spawn time handling
    static bool HandleNpcSetSpawnTimeCommand(ChatHandler* handler, uint32 spawnTime)
    {
        Creature* creature = handler->getSelectedCreature();
        if (!creature)
            return false;

        WorldDatabasePreparedStatement* stmt = WorldDatabase.GetPreparedStatement(WORLD_UPD_CREATURE_SPAWN_TIME_SECS);
        stmt->setUInt32(0, spawnTime);
        stmt->setUInt64(1, creature->GetSpawnId());
        WorldDatabase.Execute(stmt);

        creature->SetRespawnDelay(spawnTime);
        handler->PSendSysMessage(LANG_COMMAND_SPAWNTIME, spawnTime);

        return true;
    }

    static bool HandleNpcSayCommand(ChatHandler* handler, Tail text)
    {
        if (text.empty())
            return false;

        Creature* creature = handler->getSelectedCreature();
        if (!creature)
        {
            handler->SendSysMessage(LANG_SELECT_CREATURE);
            handler->SetSentErrorMessage(true);
            return false;
        }

        creature->Say(text, LANG_UNIVERSAL);

        // make some emotes
        switch (text.back())
        {
            case '?':   creature->HandleEmoteCommand(EMOTE_ONESHOT_QUESTION);      break;
            case '!':   creature->HandleEmoteCommand(EMOTE_ONESHOT_EXCLAMATION);   break;
            default:    creature->HandleEmoteCommand(EMOTE_ONESHOT_TALK);          break;
        }

        return true;
    }

    //show text emote by creature in chat
    static bool HandleNpcTextEmoteCommand(ChatHandler* handler, Tail text)
    {
        if (text.empty())
            return false;

        Creature* creature = handler->getSelectedCreature();

        if (!creature)
        {
            handler->SendSysMessage(LANG_SELECT_CREATURE);
            handler->SetSentErrorMessage(true);
            return false;
        }

        creature->TextEmote(text);

        return true;
    }

    // npc unfollow handling
    static bool HandleNpcUnFollowCommand(ChatHandler* handler)
    {
        Player* player = handler->GetSession()->GetPlayer();
        Creature* creature = handler->getSelectedCreature();

        if (!creature)
        {
            handler->PSendSysMessage(LANG_SELECT_CREATURE);
            handler->SetSentErrorMessage(true);
            return false;
        }

        MovementGenerator* movement = creature->GetMotionMaster()->GetMovementGenerator([player](MovementGenerator const* a) -> bool
        {
            if (a->GetMovementGeneratorType() == FOLLOW_MOTION_TYPE)
            {
                FollowMovementGenerator* followMovement = dynamic_cast<FollowMovementGenerator*>(const_cast<MovementGenerator*>(a));
                return followMovement && followMovement->GetTarget() == player;
            }
            return false;
        });

        if (!movement)
        {
            handler->PSendSysMessage(LANG_CREATURE_NOT_FOLLOW_YOU, creature->GetName().c_str());
            handler->SetSentErrorMessage(true);
            return false;
        }

        creature->GetMotionMaster()->Remove(movement);
        handler->PSendSysMessage(LANG_CREATURE_NOT_FOLLOW_YOU_NOW, creature->GetName().c_str());
        return true;
    }

    // make npc whisper to player
    static bool HandleNpcWhisperCommand(ChatHandler* handler, Variant<Hyperlink<player>, std::string_view> recv, Tail text)
    {
        if (text.empty())
            return false;

        Creature* creature = handler->getSelectedCreature();
        if (!creature)
        {
            handler->SendSysMessage(LANG_SELECT_CREATURE);
            handler->SetSentErrorMessage(true);
            return false;
        }

        // check online security
        Player* receiver = ObjectAccessor::FindPlayerByName(recv);
        if (handler->HasLowerSecurity(receiver, ObjectGuid::Empty))
            return false;

        creature->Whisper(text, LANG_UNIVERSAL, receiver);
        return true;
    }

    static bool HandleNpcYellCommand(ChatHandler* handler, Tail text)
    {
        if (text.empty())
            return false;

        Creature* creature = handler->getSelectedCreature();
        if (!creature)
        {
            handler->SendSysMessage(LANG_SELECT_CREATURE);
            handler->SetSentErrorMessage(true);
            return false;
        }

        creature->Yell(text, LANG_UNIVERSAL);

        // make an emote
        creature->HandleEmoteCommand(EMOTE_ONESHOT_SHOUT);

        return true;
    }

    // add creature, temp only
    static bool HandleNpcAddTempSpawnCommand(ChatHandler* handler, Optional<std::string_view> lootStr, CreatureEntry id)
    {
        bool loot = false;
        if (lootStr)
        {
            if (StringEqualI(*lootStr, "loot"))
                loot = true;
            else if (StringEqualI(*lootStr, "noloot"))
                loot = false;
            else
                return false;
        }

        Player* chr = handler->GetSession()->GetPlayer();
        if (!sObjectMgr->GetCreatureTemplate(id))
            return false;

        chr->SummonCreature(id, chr->GetPosition(), loot ? TEMPSUMMON_CORPSE_TIMED_DESPAWN : TEMPSUMMON_CORPSE_DESPAWN, 30s);

        return true;
    }

    //npc tame handling
    static bool HandleNpcTameCommand(ChatHandler* handler)
    {
        Creature* creatureTarget = handler->getSelectedCreature();
        if (!creatureTarget || creatureTarget->IsPet())
        {
            handler->PSendSysMessage (LANG_SELECT_CREATURE);
            handler->SetSentErrorMessage (true);
            return false;
        }

        Player* player = handler->GetSession()->GetPlayer();

        if (!player->GetPetGUID().IsEmpty())
        {
            handler->SendSysMessage (LANG_YOU_ALREADY_HAVE_PET);
            handler->SetSentErrorMessage (true);
            return false;
        }

        CreatureTemplate const* cInfo = creatureTarget->GetCreatureTemplate();

        if (!cInfo->IsTameable (player->CanTameExoticPets()))
        {
            handler->PSendSysMessage (LANG_CREATURE_NON_TAMEABLE, cInfo->Entry);
            handler->SetSentErrorMessage (true);
            return false;
        }

        // Everything looks OK, create new pet
        Pet* pet = player->CreateTamedPetFrom(creatureTarget);
        if (!pet)
        {
            handler->PSendSysMessage (LANG_CREATURE_NON_TAMEABLE, cInfo->Entry);
            handler->SetSentErrorMessage (true);
            return false;
        }

        // place pet before player
        float x, y, z;
        player->GetClosePoint (x, y, z, creatureTarget->GetCombatReach(), CONTACT_DISTANCE);
        pet->Relocate(x, y, z, float(M_PI) - player->GetOrientation());

        // set pet to defensive mode by default (some classes can't control controlled pets in fact).
        pet->SetReactState(REACT_DEFENSIVE);

        // calculate proper level
        uint8 level = std::max<uint8>(player->GetLevel()-5, creatureTarget->GetLevel());

        // prepare visual effect for levelup
        pet->SetLevel(level - 1);

        // add to world
        pet->GetMap()->AddToMap(pet->ToCreature());

        // visual effect for levelup
        pet->SetLevel(level);

        // caster have pet now
        player->SetMinion(pet, true);

        pet->SavePetToDB(PET_SAVE_AS_CURRENT);
        player->PetSpellInitialize();

        return true;
    }

    static bool HandleNpcEvadeCommand(ChatHandler* handler, Optional<CreatureAI::EvadeReason> why, Optional<EXACT_SEQUENCE("force")> force)
    {
        Creature* creatureTarget = handler->getSelectedCreature();
        if (!creatureTarget || creatureTarget->IsPet())
        {
            handler->PSendSysMessage(LANG_SELECT_CREATURE);
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (!creatureTarget->AI())
        {
            handler->PSendSysMessage(LANG_CREATURE_NOT_AI_ENABLED);
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (force)
            creatureTarget->ClearUnitState(UNIT_STATE_EVADE);
        creatureTarget->AI()->EnterEvadeMode(why.value_or(CreatureAI::EVADE_REASON_OTHER));

        return true;
    }

    static void _ShowLootEntry(ChatHandler* handler, uint32 itemId, uint8 itemCount, bool alternateString = false)
    {
        ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(itemId);
        char const* name = nullptr;
        if (itemTemplate)
            name = itemTemplate->GetName(handler->GetSessionDbcLocale());
        if (!name)
            name = "Unknown item";
        handler->PSendSysMessage(alternateString ? LANG_COMMAND_NPC_SHOWLOOT_ENTRY_2 : LANG_COMMAND_NPC_SHOWLOOT_ENTRY,
            itemCount, ItemQualityColors[itemTemplate ? static_cast<ItemQualities>(itemTemplate->GetQuality()) : ITEM_QUALITY_POOR], itemId, name, itemId);
    }

    static void _IterateNotNormalLootMap(ChatHandler* handler, NotNormalLootItemMap const& map, std::vector<LootItem> const& items)
    {
        for (NotNormalLootItemMap::value_type const& pair : map)
        {
            if (!pair.second)
                continue;
            Player const* player = ObjectAccessor::FindConnectedPlayer(pair.first);
            handler->PSendSysMessage(LANG_COMMAND_NPC_SHOWLOOT_SUBLABEL, player ? player->GetName().c_str() : Trinity::StringFormat("Offline player (GUID %s)", pair.first.ToString().c_str()).c_str(), pair.second->size());

            for (auto it = pair.second->cbegin(); it != pair.second->cend(); ++it)
            {
                LootItem const& item = items[it->LootListId];
                if (!(it->is_looted) && !item.is_looted)
                    _ShowLootEntry(handler, item.itemid, item.count, true);
            }
        }
    }
    static bool HandleNpcShowLootCommand(ChatHandler* handler, Optional<EXACT_SEQUENCE("all")> all)
    {
        Creature* creatureTarget = handler->getSelectedCreature();
        if (!creatureTarget || creatureTarget->IsPet())
        {
            handler->PSendSysMessage(LANG_SELECT_CREATURE);
            handler->SetSentErrorMessage(true);
            return false;
        }

        Loot const* loot = creatureTarget->m_loot.get();
        if (!creatureTarget->isDead() || !loot || loot->isLooted())
        {
            handler->PSendSysMessage(LANG_COMMAND_NOT_DEAD_OR_NO_LOOT, creatureTarget->GetName().c_str());
            handler->SetSentErrorMessage(true);
            return false;
        }

        handler->PSendSysMessage(LANG_COMMAND_NPC_SHOWLOOT_HEADER, creatureTarget->GetName().c_str(), creatureTarget->GetEntry());
        handler->PSendSysMessage(LANG_COMMAND_NPC_SHOWLOOT_MONEY, loot->gold / GOLD, (loot->gold % GOLD) / SILVER, loot->gold % SILVER);

        if (!all)
        {
            handler->PSendSysMessage(LANG_COMMAND_NPC_SHOWLOOT_LABEL, "Standard items", loot->items.size());
            for (LootItem const& item : loot->items)
                if (!item.is_looted)
                    _ShowLootEntry(handler, item.itemid, item.count);
        }
        else
        {
            handler->PSendSysMessage(LANG_COMMAND_NPC_SHOWLOOT_LABEL, "Standard items", loot->items.size());
            for (LootItem const& item : loot->items)
                if (!item.is_looted && !item.freeforall && item.conditions.empty())
                    _ShowLootEntry(handler, item.itemid, item.count);

            if (!loot->GetPlayerFFAItems().empty())
            {
                handler->PSendSysMessage(LANG_COMMAND_NPC_SHOWLOOT_LABEL_2, "FFA items per allowed player");
                _IterateNotNormalLootMap(handler, loot->GetPlayerFFAItems(), loot->items);
            }
        }

        return true;
    }

    static bool HandleNpcCloneCommand(ChatHandler* handler, uint32 EntryID)
    {
        auto l_Creature = handler->getSelectedCreature();

        if (!l_Creature)
        {
            handler->PSendSysMessage("No creature selected");
            return true;
        }

        if (!EntryID)
        {
            handler->PSendSysMessage("Bad entryid");
            return true;
        }

        if (sObjectMgr->GetCreatureTemplate(EntryID))
        {
            handler->PSendSysMessage("Bad entryid (prevent overwrite)");
            return true;
        }

        auto l_Stmt = WorldDatabase.GetPreparedStatement(WORLD_REP_CREATURE_TEMPLATE);
        l_Stmt->setUInt32(0, EntryID);
        l_Stmt->setString(1, l_Creature->GetName());
        l_Stmt->setString(2, l_Creature->GetCreatureTemplate()->SubName);
        l_Stmt->setUInt32(3, l_Creature->GetFaction());
        l_Stmt->setUInt32(4, l_Creature->GetClass());
        l_Stmt->setUInt32(5, l_Creature->GetCreatureTemplate()->rank);
        l_Stmt->setUInt32(6, l_Creature->GetCreatureTemplate()->minlevel);
        l_Stmt->setUInt32(7, l_Creature->GetCreatureTemplate()->maxlevel);
        WorldDatabase.Query(l_Stmt);

        l_Stmt = WorldDatabase.GetPreparedStatement(WORLD_REP_CREATURE_TEMPLATE_MODEL);
        l_Stmt->setUInt32(0, EntryID);
        l_Stmt->setUInt32(1, 0);
        l_Stmt->setUInt32(2, l_Creature->GetDisplayId());
        l_Stmt->setFloat(3, l_Creature->GetObjectScale());
        l_Stmt->setFloat(4, 1.0f);
        WorldDatabase.Query(l_Stmt);

        int8 wepId = -1;
        if (auto weapon = sObjectMgr->GetEquipmentInfo(EntryID, wepId))
        {
            l_Stmt = WorldDatabase.GetPreparedStatement(WORLD_REP_CREATURE_EQUIP_TEMPLATE);
            l_Stmt->setUInt32(0, EntryID);
            l_Stmt->setUInt32(1, 0);
            l_Stmt->setUInt32(2, weapon->Items[0].ItemId);
            WorldDatabase.Query(l_Stmt);
        }


        WorldDatabasePreparedStatement* stmt = WorldDatabase.GetPreparedStatement(WORLD_SEL_CREATURE_TEMPLATE);
        stmt->setUInt32(0, EntryID);
        stmt->setUInt32(1, 0);
        PreparedQueryResult result = WorldDatabase.Query(stmt);

        if (!result)
        {
            handler->PSendSysMessage(LANG_COMMAND_CREATURETEMPLATE_NOTFOUND, EntryID);
            return true;
        }

        sObjectMgr->LoadCreatureTemplate(result->Fetch());
        sObjectMgr->LoadCreatureTemplateModel(EntryID);
        sObjectMgr->LoadEquipmentTemplates();

        handler->PSendSysMessage("Succesfully copied %u to %u", l_Creature->GetEntry(), EntryID);

        return true;
    }

    static bool HandleNpcAddFormationCommand(ChatHandler* handler, ObjectGuid::LowType leaderGUID)
    {
        Creature* creature = handler->getSelectedCreature();

        if (!creature || !creature->GetSpawnId())
        {
            handler->SendSysMessage(LANG_SELECT_CREATURE);
            handler->SetSentErrorMessage(true);
            return false;
        }

        ObjectGuid::LowType lowguid = creature->GetSpawnId();
        if (creature->GetFormation())
        {
            handler->PSendSysMessage("Selected creature is already member of group " UI64FMTD, creature->GetFormation()->GetLeaderSpawnId());
            return false;
        }

        if (!lowguid)
            return false;

        Player* chr = handler->GetSession()->GetPlayer();

        float  followAngle = (creature->GetAbsoluteAngle(chr) - chr->GetOrientation()) * 180.0f / float(M_PI);
        float  followDist  = std::sqrt(std::pow(chr->GetPositionX() - creature->GetPositionX(), 2.f) + std::pow(chr->GetPositionY() - creature->GetPositionY(), 2.f));
        uint32 groupAI     = 0;
        sFormationMgr->AddFormationMember(lowguid, followAngle, followDist, leaderGUID, groupAI);
        creature->SearchFormation();

        WorldDatabasePreparedStatement* stmt = WorldDatabase.GetPreparedStatement(WORLD_INS_CREATURE_FORMATION);
        stmt->setUInt64(0, leaderGUID);
        stmt->setUInt64(1, lowguid);
        stmt->setFloat (2, followAngle);
        stmt->setFloat (3, followDist);
        stmt->setUInt32(4, groupAI);

        WorldDatabase.Execute(stmt);

        handler->PSendSysMessage("Creature " UI64FMTD " added to formation with leader " UI64FMTD, lowguid, leaderGUID);

        return true;
    }

    static bool HandleNpcSetLinkCommand(ChatHandler* handler, ObjectGuid::LowType linkguid)
    {
        Creature* creature = handler->getSelectedCreature();

        if (!creature)
        {
            handler->SendSysMessage(LANG_SELECT_CREATURE);
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (!creature->GetSpawnId())
        {
            handler->PSendSysMessage("Selected %s isn't in creature table", creature->GetGUID().ToString().c_str());
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (!sObjectMgr->SetCreatureLinkedRespawn(creature->GetSpawnId(), linkguid))
        {
            handler->PSendSysMessage("Selected creature can't link with guid '" UI64FMTD "'", linkguid);
            handler->SetSentErrorMessage(true);
            return false;
        }

        handler->PSendSysMessage("LinkGUID '" UI64FMTD "' added to creature with DBTableGUID: '" UI64FMTD "'", linkguid, creature->GetSpawnId());
        return true;
    }



    static bool HandleNpcGetCommand(ChatHandler* p_Handler, char const* p_Args)
    {
        Creature* l_Creature = p_Handler->getSelectedCreature();

        if (!l_Creature)
        {
            p_Handler->SendSysMessage("You must select a creature to use this command!");
            return false;
        }

        const CreatureTemplate* p_Template = l_Creature->GetCreatureTemplate();

        p_Handler->PSendSysMessage("|cffFFBD00Entry: %u Name: %s LootID: %u", p_Template->Entry, p_Template->Name.c_str(), p_Template->lootid);
        p_Handler->PSendSysMessage("|cffFFBD00Guid: %s", l_Creature->GetGUID().ToString().c_str());
        p_Handler->PSendSysMessage("|cffFFBD00SpawnId: %u", l_Creature->GetSpawnId());
        p_Handler->PSendSysMessage("|cffFFBD00Displayid: %u", l_Creature->GetDisplayId());
        p_Handler->PSendSysMessage("|cffFFBD00FactionID: %u", l_Creature->GetFaction());
        PhasingHandler::PrintToChat(p_Handler, l_Creature);

        return true;
    }

    static bool HandleNpcCreateCommand(ChatHandler* p_Handler)
    {
        npc_playerscript::ShowMenu(p_Handler->GetPlayer());
        return true;
    }

    static bool HandleNpcReloadCommand(ChatHandler* p_Handler)
    {
        auto creature = p_Handler->getSelectedCreature();
        if (!creature)
            return true;

        uint32 entry = creature->GetEntry();
        WorldDatabasePreparedStatement* stmt = WorldDatabase.GetPreparedStatement(WORLD_SEL_CREATURE_TEMPLATE);
        stmt->setUInt32(0, entry);
        stmt->setUInt32(1, 0);
        PreparedQueryResult result = WorldDatabase.Query(stmt);

        if (!result)
        {
            p_Handler->PSendSysMessage(LANG_COMMAND_CREATURETEMPLATE_NOTFOUND, entry);
            return true;
        }

        CreatureTemplate const* cInfo = sObjectMgr->GetCreatureTemplate(entry);
        if (!cInfo)
        {
            p_Handler->PSendSysMessage(LANG_COMMAND_CREATURESTORAGE_NOTFOUND, entry);
            return true;
        }

        TC_LOG_INFO("misc", "Reloading creature template entry %u", entry);

        Field* fields = result->Fetch();
        sObjectMgr->LoadCreatureTemplate(fields);
        sObjectMgr->LoadCreatureTemplateModel(entry);
        sObjectMgr->CheckCreatureTemplate(cInfo);

        p_Handler->PSendSysMessage("%u reloaded", entry);

        return true;
    }

    /// @todo NpcCommands that need to be fixed :
    static bool HandleNpcAddWeaponCommand([[maybe_unused]] ChatHandler* handler, [[maybe_unused]] uint32 SlotID, [[maybe_unused]] ItemTemplate const* tmpItem)
    {
        /*
        if (!tmpItem)
            return;

        uint64 guid = handler->GetSession()->GetPlayer()->GetSelection();
        if (guid == 0)
        {
            handler->SendSysMessage(LANG_NO_SELECTION);
            handler->SetSentErrorMessage(true);
            return false;
        }

        Creature* creature = ObjectAccessor::GetCreature(*handler->GetSession()->GetPlayer(), guid);

        if (!creature)
        {
            handler->SendSysMessage(LANG_SELECT_CREATURE);
            handler->SetSentErrorMessage(true);
            return false;
        }

        switch (SlotID)
        {
            case 1:
                creature->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_DISPLAY, tmpItem->ItemId);
                break;
            case 2:
                creature->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_DISPLAY_01, tmpItem->ItemId);
                break;
            case 3:
                creature->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_DISPLAY_02, tmpItem->ItemId);
                break;
            default:
                handler->PSendSysMessage(LANG_ITEM_SLOT_NOT_EXIST, SlotID);
                handler->SetSentErrorMessage(true);
                return false;
        }

        handler->PSendSysMessage(LANG_ITEM_ADDED_TO_SLOT, tmpItem->ItemID, tmpItem->Name1, SlotID);
        */
        return true;
    }
};

void AddSC_npc_commandscript()
{
    new npc_commandscript();
    new npc_playerscript();
}

bool HandleNpcSpawnGroup(ChatHandler* handler, std::vector<Variant<uint32, EXACT_SEQUENCE("force"), EXACT_SEQUENCE("ignorerespawn")>> const& opts)
{
    if (opts.empty())
        return false;

    bool ignoreRespawn = false;
    bool force = false;
    uint32 groupId = 0;

    // Decode arguments
    for (auto const& variant : opts)
    {
        switch (variant.index())
        {
            case 0:
                groupId = variant.get<uint32>();
                break;
            case 1:
                force = true;
                break;
            case 2:
                ignoreRespawn = true;
                break;
        }
    }

    Player* player = handler->GetSession()->GetPlayer();

    std::vector <WorldObject*> creatureList;
    if (!player->GetMap()->SpawnGroupSpawn(groupId, ignoreRespawn, force, &creatureList))
    {
        handler->PSendSysMessage(LANG_SPAWNGROUP_BADGROUP, groupId);
        handler->SetSentErrorMessage(true);
        return false;
    }

    handler->PSendSysMessage(LANG_SPAWNGROUP_SPAWNCOUNT, creatureList.size());

    return true;
}

bool HandleNpcDespawnGroup(ChatHandler* handler, std::vector<Variant<uint32, EXACT_SEQUENCE("removerespawntime")>> const& opts)
{
    if (opts.empty())
        return false;

    bool deleteRespawnTimes = false;
    uint32 groupId = 0;

    // Decode arguments
    for (auto const& variant : opts)
    {
        if (variant.holds_alternative<uint32>())
            groupId = variant.get<uint32>();
        else
            deleteRespawnTimes = true;
    }

    Player* player = handler->GetSession()->GetPlayer();

    size_t n = 0;
    if (!player->GetMap()->SpawnGroupDespawn(groupId, deleteRespawnTimes, &n))
    {
        handler->PSendSysMessage(LANG_SPAWNGROUP_BADGROUP, groupId);
        handler->SetSentErrorMessage(true);
        return false;
    }
    handler->PSendSysMessage("Despawned a total of %zu objects.", n);

    return true;
}
