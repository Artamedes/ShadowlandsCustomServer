#include "SpellIncludes.h"
#include "DB2Stores.h"
#include "CovenantMgr.h"
#include "Item.h"

/// ID: 366882 Incense of Infinity
class spell_incense_of_infinity : public SpellScript
{
    PrepareSpellScript(spell_incense_of_infinity);

    void HandleDummy(SpellEffIndex /*eff*/)
    {
        if (auto caster = GetCaster())
        {
            if (auto player = caster->ToPlayer())
            {
                auto covenantMgr = player->GetCovenantMgr();

                for (auto entry : sSoulbindConduitItemStore)
                {
                    auto entry2 = sSoulbindConduitStore.LookupEntry(entry->ConduitID);
                    if (entry2)
                    {
                        for (auto entry3 : sSpecSetMemberStore)
                        {
                            if (entry3->SpecSetID == entry2->SpecSetID)
                            {
                                auto entry4 = sChrSpecializationStore.LookupEntry(entry3->ChrSpecializationID);
                                if (entry4->ClassID == player->GetClass())
                                {
                                    auto item = Item::CreateItem(entry->ItemID, 1, ItemContext::NONE);
                                    if (item)
                                    {
                                        item->AddBonuses(5900); ///< (+55 ilvls) Item Level 200

                                        covenantMgr->LearnSoulbindConduit(item);
                                        delete item;
                                    }
                                }
                                break;
                            }
                        }
                    }
                }
            }
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_incense_of_infinity::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

void AddSC_spell_covenant()
{
    RegisterSpellScript(spell_incense_of_infinity);
}
