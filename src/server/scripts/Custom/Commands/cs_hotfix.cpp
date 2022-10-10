#include "Chat.h"
#include "ChatCommand.h"
#include "ScriptMgr.h"
#include "HotfixDatabase.h"
#include "ObjectMgr.h"
#include "DB2LoadInfo.h"
#include "HotfixPackets.h"
#include "World.h"
#include "Realm.h"

using namespace Trinity::ChatCommands;

static const std::string itemDB2 = "item";
static const std::string itemSparseDB2 = "itemsparse";
static const std::string itemXItemEffectDB2 = "itemxitemeffect";

class cs_hotfix : public CommandScript
{
public:
    cs_hotfix() : CommandScript("cs_hotfix") { }

    ChatCommandTable GetCommands() const override
    {
        static std::vector<ChatCommand> hotfixReloadCommandTable =
        {
            { "store",     rbac::RBAC_PERM_COMMAND_DEV,     true, &HandleHotfixReloadStoreCommand,     "" },
        };

        static std::vector<ChatCommand> hotfixCommandTable =
        {
            { "reload",   hotfixReloadCommandTable },
        };

        static ChatCommandTable commandTable =
        {
            { "hotfix", hotfixCommandTable },
        };
        return commandTable;
    }

    static bool HandleHotfixReloadStoreCommand(ChatHandler* handler, std::string table)
    {
        if (auto db2StorageBase = sDB2Manager.GetDB2StorageBaseByName(table))
        {
            try
            {
                std::vector<uint32> oldHotfixes;

                for (uint32 hotfix : db2StorageBase->GetLoadInfo()->Hotfixes)
                    oldHotfixes.push_back(hotfix);

                uint32 ms = getMSTime();
                handler->PSendSysMessage("Reloading %s!", table.c_str());
                db2StorageBase->LoadFromDB();
                if (table == itemDB2 || table == itemSparseDB2 || table == itemXItemEffectDB2)  
                {
                    handler->PSendSysMessage("Reloading item template!");
                    sObjectMgr->LoadItemTemplates();
                }
                handler->PSendSysMessage("Reloading %s in %ums", table.c_str(), GetMSTimeDiffToNow(ms));
                std::vector<uint32> diff;

                for (uint32 hotfix : db2StorageBase->GetLoadInfo()->Hotfixes)
                    if (std::find(oldHotfixes.begin(), oldHotfixes.end(), hotfix) == oldHotfixes.end())
                        diff.push_back(hotfix);

                if (!diff.empty())
                {
                    DB2Manager::HotfixContainer hotfixes;

                    for (uint32 hotfixRecord : diff)
                    {
                        handler->PSendSysMessage("Detected new record for %u, sending hotfix packet", hotfixRecord);
                        auto const& result = sDB2Manager.AddHotfixData(hotfixRecord, db2StorageBase->GetTableHash());
                        hotfixes[result.ID.PushID].push_back(result);
                    }

                    WorldPackets::Hotfix::AvailableHotfixes availableHotfixes(realm.Id.GetAddress(), hotfixes);

                    sWorld->SendGlobalMessage(availableHotfixes.Write());
                }


                //handler->GetSession()->SendAvailableHotfixes();
            }
            catch (std::system_error const& e)
            {
                if (e.code() == std::errc::no_such_file_or_directory)
                {
                    handler->PSendSysMessage(Trinity::StringFormat("File %s%s/%s does not exist", db2StorageBase->_path, localeNames[db2StorageBase->_locale], db2StorageBase->GetFileName().c_str()).c_str());
                }
                else
                    throw;
            }
            catch (std::exception const& e)
            {
                handler->PSendSysMessage(e.what());
                return true;
            }
        }
        else
            handler->PSendSysMessage("%s does not exist!", table);

        return true;
    }
};

void AddSC_cs_hotfix()
{
    new cs_hotfix();
}
