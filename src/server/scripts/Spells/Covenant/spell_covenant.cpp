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

/// ID: 357888 Condensed Anima Sphere
class spell_condensed_anima_sphere : public AuraScript
{
    PrepareAuraScript(spell_condensed_anima_sphere);

    enum eCondensedAnimaSphere
    {
        SphereCD = 357946,
        HealSpell = 357945,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        // Check if we have the aura of the cooldown of this
        if (auto caster = GetCaster())
            return !caster->HasAura(SphereCD);

        return false;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto caster = GetCaster())
        {
            // Cast the CD spell
            caster->CastSpell(caster, SphereCD, true);

            // Heal us
            if (auto eff = GetEffect(EFFECT_0))
                if (eff->ConduitRankEntry)
                    caster->CastSpell(caster, HealSpell, CastSpellExtraArgs(true).AddSpellBP0(CalculatePct(eff->ConduitRankEntry->AuraPointsOverride, 10)));
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_condensed_anima_sphere::CheckProc);
        OnProc += AuraProcFn(spell_condensed_anima_sphere::HandleProc);
    }
};

void AddSC_spell_covenant()
{
    RegisterSpellScript(spell_incense_of_infinity);
    RegisterSpellScript(spell_condensed_anima_sphere);
}
