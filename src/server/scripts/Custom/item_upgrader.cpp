#include "ScriptMgr.h"
#include "Item.h"
#include "Player.h"
#include "Spell.h"
#include "Chat.h"

// 700000
class item_upgrader : public ItemScript
{
    public:
        item_upgrader() : ItemScript("item_upgrader") { }

        bool OnUse(Player* player, Item* /*item*/, SpellCastTargets const& targets, ObjectGuid /*castId*/) override
        {
            if (!targets.GetItemTarget())
                return true;
            ChatHandler(player->GetSession()).PSendSysMessage("%s", targets.GetItemTarget()->GetTemplate()->GetName(LocaleConstant::LOCALE_enUS));

            return true;
        }

};

void AddSC_item_upgrader()
{
    new item_upgrader();
}
