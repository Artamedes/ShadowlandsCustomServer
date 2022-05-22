#include "ScriptMgr.h"
#include "Item.h"
#include "Player.h"

template<uint32 CurrencyID, uint32 CurrencyAmount>
class item_currency_exchange : public ItemScript
{
public:
    item_currency_exchange(char const* scriptName) : ItemScript(scriptName) { }

    bool OnUse(Player* player, Item* item, SpellCastTargets const& /*targets*/, ObjectGuid /*castId*/) override
    {
        auto itemCount = item->GetCount();
        auto itemSlot = item->GetSlot();

        player->ModifyCurrency(CurrencyID, itemCount * CurrencyAmount);
        player->DestroyItem(item->GetBagSlot(), itemSlot, true);
        return true;
    }
};

void AddSC_item_currency_exchange()
{
    new item_currency_exchange<1813, 20000>("item_currency_exchange_20k_anima");
    new item_currency_exchange<1813, 40000>("item_currency_exchange_40k_anima");
    new item_currency_exchange<1813, 80000>("item_currency_exchange_80k_anima");

    new item_currency_exchange<10176, 250>("item_currency_exchange_250_diamonds");
    new item_currency_exchange<10176, 500>("item_currency_exchange_500_diamonds");
    new item_currency_exchange<10176, 1000>("item_currency_exchange_1k_diamonds");
}
